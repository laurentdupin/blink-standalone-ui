#include "html_css_renderer/skia_cpu_renderer.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <optional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "html_css_renderer/render_frame.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkFlattenable.h"
#include "third_party/skia/include/core/SkFont.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkMatrix.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkRRect.h"
#include "third_party/skia/include/core/SkRect.h"
#include "third_party/skia/include/core/SkSerialProcs.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkStream.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "third_party/skia/include/core/SkTypeface.h"
#include "html_css_renderer/typeface_resource_registry.h"

namespace html_css_renderer {
namespace {

std::mutex& CommandCoverageMutex() {
  static auto* mutex = new std::mutex();
  return *mutex;
}

std::vector<CommandCoverageRecord>& CommandCoverageRecords() {
  static auto* records = new std::vector<CommandCoverageRecord>();
  return *records;
}

uint8_t ClampByte(float value) {
  const float clamped = std::max(0.0f, std::min(1.0f, value));
  return static_cast<uint8_t>(clamped * 255.0f + 0.5f);
}

SkColor ToSkColor(Color color) {
  return SkColorSetARGB(ClampByte(color.a), ClampByte(color.r),
                        ClampByte(color.g), ClampByte(color.b));
}

SkRect ToSkRect(Rect rect) {
  return SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
}

Rect FromSkIRect(const SkIRect& rect) {
  return Rect{static_cast<float>(rect.x()), static_cast<float>(rect.y()),
              static_cast<float>(rect.width()),
              static_cast<float>(rect.height())};
}

std::array<float, 9> SnapshotMatrix(const SkMatrix& matrix) {
  std::array<float, 9> values = {};
  for (int i = 0; i < 9; ++i) {
    values[static_cast<size_t>(i)] = matrix[i];
  }
  return values;
}

SkMatrix ToSkMatrix(const Matrix4& matrix) {
  const auto& m = matrix.values;
  return SkMatrix::MakeAll(m[0], m[4], m[12], m[1], m[5], m[13], m[3], m[7],
                           m[15]);
}

sk_sp<SkShader> DeserializeShader(const std::vector<uint8_t>& bytes) {
  if (bytes.empty()) {
    return nullptr;
  }
  SkDeserialProcs procs;
  sk_sp<SkFlattenable> flattenable = SkFlattenable::Deserialize(
      SkFlattenable::kSkShader_Type, bytes.data(), bytes.size(), &procs);
  if (!flattenable ||
      flattenable->getFlattenableType() != SkFlattenable::kSkShader_Type) {
    return nullptr;
  }
  return sk_sp<SkShader>(static_cast<SkShader*>(flattenable.release()));
}

uint64_t CountChangedPixels(const std::vector<uint8_t>& before,
                            const std::vector<uint8_t>& after) {
  const size_t byte_count = std::min(before.size(), after.size());
  uint64_t changed = 0;
  for (size_t i = 0; i + 3 < byte_count; i += 4) {
    if (before[i] != after[i] || before[i + 1] != after[i + 1] ||
        before[i + 2] != after[i + 2] || before[i + 3] != after[i + 3]) {
      ++changed;
    }
  }
  return changed;
}

void StoreCommandCoverage(CommandCoverageRecord record) {
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  CommandCoverageRecords().push_back(std::move(record));
}

uint32_t PackRgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return (static_cast<uint32_t>(r) << 24) |
         (static_cast<uint32_t>(g) << 16) |
         (static_cast<uint32_t>(b) << 8) | static_cast<uint32_t>(a);
}

int FloorToInt(float value) {
  return static_cast<int>(std::floor(value));
}

struct GlyphMask {
  Rect bounds;
  int width = 0;
  int height = 0;
  std::vector<uint8_t> pixels;
};

using GlyphAtlas = std::unordered_map<std::string, GlyphMask>;

struct ImageResource {
  int width = 0;
  int height = 0;
  std::vector<uint8_t> pixels;
};

using ImageAtlas = std::unordered_map<std::string, ImageResource>;

std::string GlyphKey(const std::string& font_id, uint32_t glyph_id) {
  return font_id + "#" + std::to_string(glyph_id);
}

GlyphAtlas BuildGlyphAtlas(const std::vector<ResourceCommand>& commands) {
  GlyphAtlas atlas;
  for (const ResourceCommand& resource : commands) {
    if (resource.type != ResourceCommandType::kCreateOrUpdateGlyphAtlas ||
        resource.load_command.type != LoadCommandType::kGlyphAtlasUpdate) {
      continue;
    }
    const GlyphAtlasUpdate& update = resource.load_command.glyph_atlas_update;
    if (update.format != PixelFormat::kAlpha8 || update.bounds.width <= 0.0f ||
        update.bounds.height <= 0.0f) {
      continue;
    }
    GlyphMask mask;
    mask.bounds = update.bounds;
    mask.width = FloorToInt(update.bounds.width);
    mask.height = FloorToInt(update.bounds.height);
    if (mask.width <= 0 || mask.height <= 0 ||
        update.pixels.size() < static_cast<size_t>(mask.width * mask.height)) {
      continue;
    }
    mask.pixels = update.pixels;
    atlas[GlyphKey(update.font_id, update.glyph_id)] = std::move(mask);
  }
  return atlas;
}

ImageAtlas BuildImageAtlas(const std::vector<ResourceCommand>& commands) {
  ImageAtlas atlas;
  for (const ResourceCommand& resource : commands) {
    if (resource.type != ResourceCommandType::kCreateOrUpdateImage ||
        resource.load_command.type != LoadCommandType::kLoadImage) {
      continue;
    }
    const ImageLoadInfo& update = resource.load_command.image;
    if (update.decoded_format != PixelFormat::kRgba8888 ||
        update.decoded_size.width <= 0.0f ||
        update.decoded_size.height <= 0.0f) {
      continue;
    }
    ImageResource image;
    image.width = FloorToInt(update.decoded_size.width);
    image.height = FloorToInt(update.decoded_size.height);
    if (image.width <= 0 || image.height <= 0 ||
        update.decoded_pixels.size() <
            static_cast<size_t>(image.width * image.height * 4)) {
      continue;
    }
    image.pixels = update.decoded_pixels;
    atlas[update.image_id] = std::move(image);
  }
  return atlas;
}

void DrawGlyphRunWithSkia(SkCanvas& canvas,
                          const GlyphAtlas& atlas,
                          const GlyphRun& run) {
  SkPaint paint;
  paint.setAntiAlias(true);
  paint.setColor(ToSkColor(run.color));

  const size_t count = std::min(run.glyph_ids.size(), run.positions.size());
  for (size_t i = 0; i < count; ++i) {
    const auto found = atlas.find(GlyphKey(run.font_id, run.glyph_ids[i]));
    if (found == atlas.end()) {
      continue;
    }
    const GlyphMask& mask = found->second;
    if (mask.width <= 0 || mask.height <= 0 ||
        mask.pixels.size() <
            static_cast<size_t>(mask.width * mask.height)) {
      continue;
    }

    SkBitmap bitmap;
    SkImageInfo info = SkImageInfo::MakeA8(mask.width, mask.height);
    if (!bitmap.installPixels(info, const_cast<uint8_t*>(mask.pixels.data()),
                              static_cast<size_t>(mask.width))) {
      continue;
    }
    const Point origin = run.positions[i];
    const SkRect dst = SkRect::MakeXYWH(origin.x + mask.bounds.x,
                                       origin.y + mask.bounds.y,
                                       static_cast<float>(mask.width),
                                       static_cast<float>(mask.height));
    canvas.drawImageRect(bitmap.asImage(), dst, SkSamplingOptions(), &paint);
  }
}

void DrawCommandWithSkia(SkCanvas& canvas,
                         const DrawCommand& command,
                         const ImageAtlas& images,
                         const GlyphAtlas& glyphs,
                         bool strict_text_blob_typefaces,
                         int* save_depth,
                         CommandCoverageRecord* coverage) {
  SkPaint paint;
  paint.setAntiAlias(true);
  paint.setColor(ToSkColor(command.color));

  switch (command.type) {
    case DrawCommandType::kFillRect:
      paint.setStyle(SkPaint::kFill_Style);
      canvas.drawRect(ToSkRect(command.rect), paint);
      break;
    case DrawCommandType::kStrokeRect:
      paint.setStyle(SkPaint::kStroke_Style);
      paint.setStrokeWidth(command.stroke_width);
      canvas.drawRect(ToSkRect(command.rect), paint);
      break;
    case DrawCommandType::kFillRectShader:
      if (coverage) {
        coverage->shader_resource_present = !command.shader_bytes.empty();
        coverage->shader_byte_count = command.shader_bytes.size();
      }
      if (sk_sp<SkShader> shader = DeserializeShader(command.shader_bytes)) {
        if (coverage) {
          coverage->shader_deserialize_success = true;
        }
        paint.setStyle(SkPaint::kFill_Style);
        paint.setShader(std::move(shader));
        paint.setColor(SkColorSetARGB(ClampByte(command.color.a), 255, 255,
                                      255));
        canvas.drawRect(ToSkRect(command.rect), paint);
      } else if (coverage) {
        coverage->skipped = true;
        coverage->skip_reason = "shader_deserialize_failed";
      }
      break;
    case DrawCommandType::kFillRRect:
      paint.setStyle(SkPaint::kFill_Style);
      canvas.drawRoundRect(ToSkRect(command.rect), command.radius_x,
                           command.radius_y, paint);
      break;
    case DrawCommandType::kStrokeRRect:
      paint.setStyle(SkPaint::kStroke_Style);
      paint.setStrokeWidth(command.stroke_width);
      canvas.drawRoundRect(ToSkRect(command.rect), command.radius_x,
                           command.radius_y, paint);
      break;
    case DrawCommandType::kFillRRectShader:
      if (coverage) {
        coverage->shader_resource_present = !command.shader_bytes.empty();
        coverage->shader_byte_count = command.shader_bytes.size();
      }
      if (sk_sp<SkShader> shader = DeserializeShader(command.shader_bytes)) {
        if (coverage) {
          coverage->shader_deserialize_success = true;
        }
        paint.setStyle(SkPaint::kFill_Style);
        paint.setShader(std::move(shader));
        paint.setColor(SkColorSetARGB(ClampByte(command.color.a), 255, 255,
                                      255));
        canvas.drawRoundRect(ToSkRect(command.rect), command.radius_x,
                             command.radius_y, paint);
      } else if (coverage) {
        coverage->skipped = true;
        coverage->skip_reason = "shader_deserialize_failed";
      }
      break;
   case DrawCommandType::kClipRect:
     canvas.clipRect(ToSkRect(command.rect));
     break;
   case DrawCommandType::kClipRRect: {
     SkVector radii[4] = {
         SkVector::Make(command.corner_radii[0].x, command.corner_radii[0].y),
         SkVector::Make(command.corner_radii[1].x, command.corner_radii[1].y),
         SkVector::Make(command.corner_radii[2].x, command.corner_radii[2].y),
         SkVector::Make(command.corner_radii[3].x, command.corner_radii[3].y),
     };
     canvas.clipRRect(SkRRect::MakeRectRadii(ToSkRect(command.rect), radii),
                      command.clip_difference ? SkClipOp::kDifference
                                              : SkClipOp::kIntersect,
                      true);
     break;
   }
   case DrawCommandType::kClipPath: {
     std::optional<SkPath> path =
         SkPath::ReadFromMemory(command.path_bytes.data(),
                                command.path_bytes.size());
     if (path) {
       canvas.clipPath(*path,
                       command.clip_difference ? SkClipOp::kDifference
                                               : SkClipOp::kIntersect,
                       true);
     }
     break;
   }
    case DrawCommandType::kSave:
      canvas.save();
      ++*save_depth;
      break;
    case DrawCommandType::kRestore:
      if (*save_depth > 0) {
        canvas.restore();
        --*save_depth;
      }
      break;
    case DrawCommandType::kSaveLayer:
      if (command.opacity < 1.0f) {
        SkPaint layer_paint;
        layer_paint.setAlphaf(std::max(0.0f, std::min(1.0f, command.opacity)));
        canvas.saveLayer(ToSkRect(command.rect), &layer_paint);
      } else {
        canvas.saveLayer(ToSkRect(command.rect), nullptr);
      }
      ++*save_depth;
      break;
    case DrawCommandType::kTransform:
      canvas.concat(ToSkMatrix(command.transform));
      break;
    case DrawCommandType::kDrawText: {
      break;
    }
    case DrawCommandType::kDrawImage:
      if (const auto found = images.find(command.resource_id);
          found != images.end()) {
        const ImageResource& resource = found->second;
        SkBitmap bitmap;
        SkImageInfo info = SkImageInfo::Make(
            resource.width, resource.height, kRGBA_8888_SkColorType,
            kPremul_SkAlphaType);
        if (bitmap.installPixels(info,
                                 const_cast<uint8_t*>(resource.pixels.data()),
                                 static_cast<size_t>(resource.width) * 4u)) {
          canvas.drawImageRect(bitmap.asImage(), ToSkRect(command.rect),
                               SkSamplingOptions(), nullptr);
        }
      }
      break;
    case DrawCommandType::kDrawImageRect:
      if (const auto found = images.find(command.resource_id);
          found != images.end()) {
        const ImageResource& resource = found->second;
        SkBitmap bitmap;
        SkImageInfo info = SkImageInfo::Make(
            resource.width, resource.height, kRGBA_8888_SkColorType,
            kPremul_SkAlphaType);
        if (bitmap.installPixels(info,
                                 const_cast<uint8_t*>(resource.pixels.data()),
                                 static_cast<size_t>(resource.width) * 4u)) {
          canvas.drawImageRect(bitmap.asImage(), ToSkRect(command.source_rect),
                               ToSkRect(command.rect), SkSamplingOptions(),
                               nullptr, SkCanvas::kStrict_SrcRectConstraint);
        }
      }
      break;
    case DrawCommandType::kDrawGlyphRun:
      DrawGlyphRunWithSkia(canvas, glyphs, command.glyph_run);
      break;
    case DrawCommandType::kDrawTextBlob: {
      if (coverage) {
        coverage->text_blob_resource_present = !command.text_blob_bytes.empty();
        coverage->text_blob_byte_count = command.text_blob_bytes.size();
      }
      SkDeserialProcs procs;
      procs.fTypefaceCtx = const_cast<bool*>(&strict_text_blob_typefaces);
      procs.fTypefaceStreamProc = [](SkStream& stream,
                                     void* ctx) -> sk_sp<SkTypeface> {
        const bool strict_text_blob_typefaces =
            ctx && *static_cast<const bool*>(ctx);
        struct Payload {
          char magic[4];
          uint32_t version;
          uint64_t typeface_resource_id;
        } payload = {};
        if (stream.read(&payload, sizeof(payload)) != sizeof(payload) ||
            std::memcmp(payload.magic, "BSTF", 4) != 0 ||
            payload.version != 1) {
          if (!strict_text_blob_typefaces &&
              StandaloneRendererSameProcessTypefaceResourceCount() == 1) {
            RecordDiagnosticTypefaceFallback();
            return sk_ref_sp(
                StandaloneRendererLookupSameProcessTypefaceForSkTextBlob(1));
          }
          return nullptr;
        }
        auto* typeface =
            StandaloneRendererLookupSameProcessTypefaceForSkTextBlob(
                payload.typeface_resource_id);
        if (!typeface) {
          return nullptr;
        }
        return sk_ref_sp(typeface);
      };
      RecordTextBlobDeserializeAttempt();
      sk_sp<SkTextBlob> blob = SkTextBlob::Deserialize(
          command.text_blob_bytes.data(), command.text_blob_bytes.size(),
          procs);
      if (blob) {
        RecordTextBlobDeserializeSuccess();
        if (coverage) {
          coverage->text_blob_deserialize_success = true;
        }
        paint.setColor(ToSkColor(command.color));
        canvas.drawTextBlob(blob, command.rect.x, command.rect.y, paint);
      } else {
        RecordTextBlobDeserializeFailure();
        if (coverage) {
          coverage->skipped = true;
          coverage->skip_reason = "text_blob_deserialize_failed";
        }
      }
      break;
    }
    case DrawCommandType::kFillPath: {
      std::optional<SkPath> path =
          SkPath::ReadFromMemory(command.path_bytes.data(),
                                 command.path_bytes.size());
      if (path) {
        paint.setStyle(command.stroke_width > 0.0f ? SkPaint::kStroke_Style
                                                   : SkPaint::kFill_Style);
        paint.setStrokeWidth(command.stroke_width > 0.0f ? command.stroke_width
                                                         : 1.0f);
        if (sk_sp<SkShader> shader = DeserializeShader(command.shader_bytes)) {
          paint.setShader(std::move(shader));
          paint.setColor(SkColorSetARGB(ClampByte(command.color.a), 255, 255,
                                        255));
          if (coverage) {
            coverage->shader_resource_present = true;
            coverage->shader_byte_count = command.shader_bytes.size();
            coverage->shader_deserialize_success = true;
          }
        } else {
          paint.setColor(ToSkColor(command.color));
          if (coverage && !command.shader_bytes.empty()) {
            coverage->shader_resource_present = true;
            coverage->shader_byte_count = command.shader_bytes.size();
            coverage->skipped = true;
            coverage->skip_reason = "path_shader_deserialize_failed";
          }
        }
        canvas.save();
        canvas.translate(command.rect.x, command.rect.y);
        canvas.drawPath(*path, paint);
        canvas.restore();
      }
      break;
    }
    case DrawCommandType::kDiagnostic:
      break;
  }
}

CpuImage RasterizeDrawCommandsWithSkiaCpuInternal(const DrawCommandList& commands,
                                                  Size viewport,
                                                  CpuRenderOptions options,
                                                  const ImageAtlas& images,
                                                  const GlyphAtlas& glyphs) {
  CpuImage image;
  image.width = std::max(1, static_cast<int>(viewport.width));
  image.height = std::max(1, static_cast<int>(viewport.height));
  image.pixels_rgba.resize(static_cast<size_t>(image.width) * image.height);

  SkImageInfo info =
      SkImageInfo::Make(image.width, image.height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  std::vector<uint8_t> pixels(static_cast<size_t>(image.width) * image.height *
                              4u);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      info, pixels.data(), static_cast<size_t>(image.width) * 4u);
  if (!surface) {
    return RasterizeDrawCommands(commands, viewport, options);
  }

  SkCanvas* canvas = surface->getCanvas();
  canvas->clear(ToSkColor(options.clear_color));
  int save_depth = 0;
  if (options.debug_command_coverage) {
    ResetCommandCoverageDiagnostics();
  }
  for (size_t command_index = 0; command_index < commands.size();
       ++command_index) {
    const DrawCommand& command = commands[command_index];
    std::vector<uint8_t> before_pixels;
    CommandCoverageRecord coverage;
    CommandCoverageRecord* coverage_ptr = nullptr;
    if (options.debug_command_coverage) {
      before_pixels = pixels;
      coverage_ptr = &coverage;
      coverage.command_index = static_cast<int>(command_index);
      coverage.command_type = ToString(command.type);
      coverage.bounds = command.rect;
      coverage.active_matrix = SnapshotMatrix(canvas->getTotalMatrix());
      SkIRect clip_bounds;
      if (canvas->getDeviceClipBounds(&clip_bounds)) {
        coverage.has_active_clip = true;
        coverage.active_clip_bounds = FromSkIRect(clip_bounds);
      }
      coverage.save_depth_before = save_depth;
    }
    DrawCommandWithSkia(*canvas, command, images, glyphs,
                        options.strict_text_blob_typefaces, &save_depth,
                        coverage_ptr);
    if (options.debug_command_coverage) {
      coverage.save_depth_after = save_depth;
      coverage.pixels_changed = CountChangedPixels(before_pixels, pixels);
      StoreCommandCoverage(std::move(coverage));
    }
  }
  while (save_depth > 0) {
    canvas->restore();
    --save_depth;
  }

  for (int y = 0; y < image.height; ++y) {
    for (int x = 0; x < image.width; ++x) {
      const size_t offset = (static_cast<size_t>(y) * image.width + x) * 4u;
      image.pixels_rgba[static_cast<size_t>(y) * image.width + x] =
          PackRgba(pixels[offset + 0], pixels[offset + 1], pixels[offset + 2],
                   pixels[offset + 3]);
    }
  }

  return image;
}

}  // namespace

void ResetCommandCoverageDiagnostics() {
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  CommandCoverageRecords().clear();
}

std::vector<CommandCoverageRecord> SnapshotCommandCoverageDiagnostics() {
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  return CommandCoverageRecords();
}

CpuImage RasterizeDrawCommandsWithSkiaCpu(const DrawCommandList& commands,
                                          Size viewport,
                                          CpuRenderOptions options) {
  const ImageAtlas images;
  const GlyphAtlas glyphs;
  return RasterizeDrawCommandsWithSkiaCpuInternal(commands, viewport, options,
                                                 images, glyphs);
}

CpuImage RasterizeRenderResultWithSkiaCpu(const RenderResult& result,
                                          CpuRenderOptions options) {
  const DrawCommandList commands =
      FlattenSceneDrawCommands(result.frame.scene_commands);
  const ImageAtlas images = BuildImageAtlas(result.frame.resource_commands);
  const GlyphAtlas glyphs = BuildGlyphAtlas(result.frame.resource_commands);
  CpuImage image = RasterizeDrawCommandsWithSkiaCpuInternal(
      commands, result.successor_snapshot.viewport, options, images, glyphs);
  return image;
}

}  // namespace html_css_renderer
