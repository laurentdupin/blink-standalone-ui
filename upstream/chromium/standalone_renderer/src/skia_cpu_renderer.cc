#include "html_css_renderer/skia_cpu_renderer.h"

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <optional>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "cc/paint/filter_operations.h"
#include "cc/paint/paint_filter.h"
#include "cc/paint/render_surface_filters.h"
#include "html_css_renderer/render_frame.h"
#include "third_party/skia/include/core/SkBlendMode.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkFlattenable.h"
#include "third_party/skia/include/core/SkFont.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkMatrix.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkRRect.h"
#include "third_party/skia/include/core/SkRect.h"
#include "third_party/skia/include/core/SkRegion.h"
#include "third_party/skia/include/core/SkSamplingOptions.h"
#include "third_party/skia/include/core/SkSerialProcs.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkStream.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/skia/include/core/SkSurfaceProps.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "third_party/skia/include/core/SkTypeface.h"
#include "third_party/skia/include/core/SkBlurTypes.h"
#include "third_party/skia/include/core/SkColorFilter.h"
#include "third_party/skia/include/core/SkColorSpace.h"
#include "third_party/skia/include/core/SkMaskFilter.h"
#include "third_party/skia/include/core/SkPathEffect.h"
#include "html_css_renderer/typeface_resource_registry.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/rect.h"

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

std::vector<CpuReplayCommandTimingRecord>& CpuReplayCommandTimingRecords() {
  static auto* records =
      new std::vector<CpuReplayCommandTimingRecord>();
  return *records;
}

SkiaCpuSurfaceDiagnostics& LastSurfaceDiagnostics() {
  static auto* diagnostics = new SkiaCpuSurfaceDiagnostics();
  return *diagnostics;
}

std::mutex& ShaderCacheMutex() {
  static auto* mutex = new std::mutex();
  return *mutex;
}

struct CachedShader {
  std::vector<uint8_t> bytes;
  sk_sp<SkShader> shader;
};

std::unordered_map<uint64_t, std::vector<CachedShader>>& ShaderCache() {
  static auto* cache =
      new std::unordered_map<uint64_t, std::vector<CachedShader>>();
  return *cache;
}

std::mutex& ShaderRectImageCacheMutex() {
  static auto* mutex = new std::mutex();
  return *mutex;
}

struct CachedShaderRectImage {
  std::vector<uint8_t> shader_bytes;
  int left = 0;
  int top = 0;
  int width = 0;
  int height = 0;
  uint8_t alpha = 255;
  sk_sp<SkImage> image;
  size_t byte_count = 0;
};

std::unordered_map<uint64_t, std::vector<CachedShaderRectImage>>&
ShaderRectImageCache() {
  static auto* cache =
      new std::unordered_map<uint64_t, std::vector<CachedShaderRectImage>>();
  return *cache;
}

using CpuReplayProfileClock = std::chrono::steady_clock;

struct CpuReplayCommandTimingAccumulator {
  uint64_t count = 0;
  double elapsed_ms = 0.0;
};

constexpr size_t kDrawCommandTypeCount = 20;

size_t DrawCommandTypeIndex(DrawCommandType type) {
  const size_t index = static_cast<size_t>(type);
  return index < kDrawCommandTypeCount ? index
                                       : kDrawCommandTypeCount - 1;
}

uint64_t HashBytesForCache(const std::vector<uint8_t>& bytes) {
  uint64_t hash = 1469598103934665603ull;
  for (uint8_t byte : bytes) {
    hash ^= byte;
    hash *= 1099511628211ull;
  }
  return hash;
}

uint8_t ClampByte(float value) {
  const float clamped = std::max(0.0f, std::min(1.0f, value));
  return static_cast<uint8_t>(clamped * 255.0f + 0.5f);
}

SkColor ToSkColor(Color color) {
  return SkColorSetARGB(ClampByte(color.a), ClampByte(color.r),
                        ClampByte(color.g), ClampByte(color.b));
}

SkColor4f ToSkColor4f(Color color) {
  return SkColor4f{std::max(0.0f, std::min(1.0f, color.r)),
                   std::max(0.0f, std::min(1.0f, color.g)),
                   std::max(0.0f, std::min(1.0f, color.b)),
                   std::max(0.0f, std::min(1.0f, color.a))};
}

SkRect ToSkRect(Rect rect) {
  return SkRect::MakeXYWH(rect.x, rect.y, rect.width, rect.height);
}

SkRRect ToSkRRect(const DrawCommand& command) {
  SkVector radii[4] = {
      SkVector::Make(command.corner_radii[0].x, command.corner_radii[0].y),
      SkVector::Make(command.corner_radii[1].x, command.corner_radii[1].y),
      SkVector::Make(command.corner_radii[2].x, command.corner_radii[2].y),
      SkVector::Make(command.corner_radii[3].x, command.corner_radii[3].y),
  };
  return SkRRect::MakeRectRadii(ToSkRect(command.rect), radii);
}

float ParseFloatAfter(const std::string& text,
                      const char* key,
                      float fallback) {
  const size_t position = text.find(key);
  if (position == std::string::npos) {
    return fallback;
  }
  const char* begin = text.c_str() + position + std::strlen(key);
  char* end = nullptr;
  const float parsed = std::strtof(begin, &end);
  return end != begin ? parsed : fallback;
}

int ParseIntAfter(const std::string& text, const char* key, int fallback) {
  const size_t position = text.find(key);
  if (position == std::string::npos) {
    return fallback;
  }
  const char* begin = text.c_str() + position + std::strlen(key);
  char* end = nullptr;
  const long parsed = std::strtol(begin, &end, 10);
  return end != begin ? static_cast<int>(parsed) : fallback;
}

SkSamplingOptions ParseSamplingOptions(const std::string& options) {
  if (options.rfind("aniso=", 0) == 0) {
    const int max_aniso = ParseIntAfter(options, "aniso=", 0);
    if (max_aniso > 0) {
      return SkSamplingOptions::Aniso(max_aniso);
    }
  }
  if (options.rfind("cubic=", 0) == 0) {
    return SkSamplingOptions(
        SkCubicResampler{ParseFloatAfter(options, "B", 0.0f),
                         ParseFloatAfter(options, "C", 0.0f)});
  }

  const SkFilterMode filter =
      options.find("filter=linear") != std::string::npos
          ? SkFilterMode::kLinear
          : SkFilterMode::kNearest;
  SkMipmapMode mipmap = SkMipmapMode::kNone;
  if (options.find("mipmap=linear") != std::string::npos) {
    mipmap = SkMipmapMode::kLinear;
  } else if (options.find("mipmap=nearest") != std::string::npos) {
    mipmap = SkMipmapMode::kNearest;
  }
  return SkSamplingOptions(filter, mipmap);
}

SkBlendMode ParseBlendMode(const std::string& blend_mode) {
  if (blend_mode == "clear")
    return SkBlendMode::kClear;
  if (blend_mode == "src")
    return SkBlendMode::kSrc;
  if (blend_mode == "dst")
    return SkBlendMode::kDst;
  if (blend_mode == "dst_over")
    return SkBlendMode::kDstOver;
  if (blend_mode == "src_in")
    return SkBlendMode::kSrcIn;
  if (blend_mode == "dst_in")
    return SkBlendMode::kDstIn;
  if (blend_mode == "src_out")
    return SkBlendMode::kSrcOut;
  if (blend_mode == "dst_out")
    return SkBlendMode::kDstOut;
  if (blend_mode == "src_atop")
    return SkBlendMode::kSrcATop;
  if (blend_mode == "dst_atop")
    return SkBlendMode::kDstATop;
  if (blend_mode == "xor")
    return SkBlendMode::kXor;
  if (blend_mode == "plus")
    return SkBlendMode::kPlus;
  if (blend_mode == "multiply")
    return SkBlendMode::kMultiply;
  if (blend_mode == "screen")
    return SkBlendMode::kScreen;
  if (blend_mode == "overlay")
    return SkBlendMode::kOverlay;
  if (blend_mode == "darken")
    return SkBlendMode::kDarken;
  if (blend_mode == "lighten")
    return SkBlendMode::kLighten;
  if (blend_mode == "color_dodge")
    return SkBlendMode::kColorDodge;
  if (blend_mode == "color_burn")
    return SkBlendMode::kColorBurn;
  if (blend_mode == "hard_light")
    return SkBlendMode::kHardLight;
  if (blend_mode == "soft_light")
    return SkBlendMode::kSoftLight;
  if (blend_mode == "difference")
    return SkBlendMode::kDifference;
  if (blend_mode == "exclusion")
    return SkBlendMode::kExclusion;
  if (blend_mode == "hue")
    return SkBlendMode::kHue;
  if (blend_mode == "saturation")
    return SkBlendMode::kSaturation;
  if (blend_mode == "color")
    return SkBlendMode::kColor;
  if (blend_mode == "luminosity")
    return SkBlendMode::kLuminosity;
  return SkBlendMode::kSrcOver;
}

gfx::Rect ToGfxRectEnclosing(Rect rect) {
  const int left = static_cast<int>(std::floor(rect.x));
  const int top = static_cast<int>(std::floor(rect.y));
  const int right = static_cast<int>(std::ceil(rect.x + rect.width));
  const int bottom = static_cast<int>(std::ceil(rect.y + rect.height));
  return gfx::Rect(left, top, std::max(0, right - left),
                   std::max(0, bottom - top));
}

cc::FilterOperations ToCcFilterOperations(
    const std::vector<FilterOperationSnapshot>& operations) {
  cc::FilterOperations filters;
  for (const FilterOperationSnapshot& operation : operations) {
    switch (operation.kind) {
      case FilterOperationKind::kGrayscale:
        filters.Append(
            cc::FilterOperation::CreateGrayscaleFilter(operation.amount));
        break;
      case FilterOperationKind::kSepia:
        filters.Append(cc::FilterOperation::CreateSepiaFilter(operation.amount));
        break;
      case FilterOperationKind::kSaturate:
        filters.Append(
            cc::FilterOperation::CreateSaturateFilter(operation.amount));
        break;
      case FilterOperationKind::kHueRotate:
        filters.Append(
            cc::FilterOperation::CreateHueRotateFilter(operation.amount));
        break;
      case FilterOperationKind::kInvert:
        filters.Append(
            cc::FilterOperation::CreateInvertFilter(operation.amount));
        break;
      case FilterOperationKind::kBrightness:
        filters.Append(
            cc::FilterOperation::CreateBrightnessFilter(operation.amount));
        break;
      case FilterOperationKind::kContrast:
        filters.Append(
            cc::FilterOperation::CreateContrastFilter(operation.amount));
        break;
      case FilterOperationKind::kOpacity:
        filters.Append(
            cc::FilterOperation::CreateOpacityFilter(operation.amount));
        break;
      case FilterOperationKind::kBlur:
        filters.Append(cc::FilterOperation::CreateBlurFilter(operation.amount));
        break;
      case FilterOperationKind::kDropShadow:
        filters.Append(cc::FilterOperation::CreateDropShadowFilter(
            gfx::Point(static_cast<int>(std::lround(operation.offset.x)),
                       static_cast<int>(std::lround(operation.offset.y))),
            operation.amount,
            SkColor4f{operation.color.r, operation.color.g, operation.color.b,
                      operation.color.a}));
        break;
      case FilterOperationKind::kColorMatrix:
        filters.Append(
            cc::FilterOperation::CreateColorMatrixFilter(operation.matrix));
        break;
    }
  }
  return filters;
}

Rect FromSkIRect(const SkIRect& rect) {
  return Rect{static_cast<float>(rect.x()), static_cast<float>(rect.y()),
              static_cast<float>(rect.width()),
              static_cast<float>(rect.height())};
}

SkIRect ToSkIRectClamped(Rect rect, int width, int height) {
  const int left = std::max(0, static_cast<int>(std::floor(rect.x)));
  const int top = std::max(0, static_cast<int>(std::floor(rect.y)));
  const int right = std::min(
      width, static_cast<int>(std::ceil(rect.x + rect.width)));
  const int bottom = std::min(
      height, static_cast<int>(std::ceil(rect.y + rect.height)));
  return SkIRect::MakeLTRB(left, top, std::max(left, right),
                           std::max(top, bottom));
}

bool IsEmpty(const SkIRect& rect) {
  return rect.isEmpty();
}

uint64_t PixelArea(const SkIRect& rect) {
  if (IsEmpty(rect)) {
    return 0;
  }
  return static_cast<uint64_t>(rect.width()) *
         static_cast<uint64_t>(rect.height());
}

uint64_t DamagePixelArea(const std::vector<Rect>& damage_rects,
                         int width,
                         int height) {
  uint64_t pixels = 0;
  for (const Rect& damage_rect : damage_rects) {
    pixels += PixelArea(ToSkIRectClamped(damage_rect, width, height));
  }
  return pixels;
}

uint64_t RegionPixelArea(const std::vector<SkIRect>& clips) {
  SkRegion region;
  for (const SkIRect& clip : clips) {
    if (!IsEmpty(clip)) {
      region.op(clip, SkRegion::kUnion_Op);
    }
  }
  uint64_t pixels = 0;
  for (SkRegion::Iterator it(region); !it.done(); it.next()) {
    pixels += PixelArea(it.rect());
  }
  return pixels;
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

sk_sp<SkShader> DeserializeShaderUncached(const std::vector<uint8_t>& bytes) {
  if (bytes.empty()) {
    return nullptr;
  }
  SkDeserialProcs procs = {};
  sk_sp<SkFlattenable> flattenable = SkFlattenable::Deserialize(
      SkFlattenable::kSkShader_Type, bytes.data(), bytes.size(), &procs);
  if (!flattenable ||
      flattenable->getFlattenableType() != SkFlattenable::kSkShader_Type) {
    return nullptr;
  }
  return sk_sp<SkShader>(static_cast<SkShader*>(flattenable.release()));
}

sk_sp<SkShader> DeserializeShader(const std::vector<uint8_t>& bytes) {
  if (bytes.empty()) {
    return nullptr;
  }
  const uint64_t hash = HashBytesForCache(bytes);
  {
    std::lock_guard<std::mutex> lock(ShaderCacheMutex());
    const auto found = ShaderCache().find(hash);
    if (found != ShaderCache().end()) {
      for (const CachedShader& cached : found->second) {
        if (cached.bytes == bytes) {
          return cached.shader;
        }
      }
    }
  }

  sk_sp<SkShader> shader = DeserializeShaderUncached(bytes);
  if (!shader) {
    return nullptr;
  }
  {
    std::lock_guard<std::mutex> lock(ShaderCacheMutex());
    auto& cache = ShaderCache();
    size_t entry_count = 0;
    for (const auto& bucket : cache) {
      entry_count += bucket.second.size();
    }
    constexpr size_t kMaxShaderCacheEntries = 256;
    if (entry_count >= kMaxShaderCacheEntries) {
      cache.clear();
    }
    auto& bucket = cache[hash];
    for (const CachedShader& cached : bucket) {
      if (cached.bytes == bytes) {
        return cached.shader;
      }
    }
    bucket.push_back(CachedShader{bytes, shader});
  }
  return shader;
}

sk_sp<SkPathEffect> DeserializePathEffect(const std::vector<uint8_t>& bytes) {
  if (bytes.empty()) {
    return nullptr;
  }
  return SkPathEffect::Deserialize(bytes.data(), bytes.size());
}

const char* ColorTypeName(SkColorType color_type) {
  switch (color_type) {
    case kRGBA_8888_SkColorType:
      return "rgba_8888";
    case kBGRA_8888_SkColorType:
      return "bgra_8888";
    default:
      return "other";
  }
}

const char* AlphaTypeName(SkAlphaType alpha_type) {
  switch (alpha_type) {
    case kOpaque_SkAlphaType:
      return "opaque";
    case kPremul_SkAlphaType:
      return "premul";
    case kUnpremul_SkAlphaType:
      return "unpremul";
    default:
      return "unknown";
  }
}

const char* PixelGeometryName(SkPixelGeometry geometry) {
  switch (geometry) {
    case kUnknown_SkPixelGeometry:
      return "unknown";
    case kRGB_H_SkPixelGeometry:
      return "rgb_h";
    case kBGR_H_SkPixelGeometry:
      return "bgr_h";
    case kRGB_V_SkPixelGeometry:
      return "rgb_v";
    case kBGR_V_SkPixelGeometry:
      return "bgr_v";
  }
  return "unknown";
}

void ApplyPathEffect(const DrawCommand& command,
                     SkPaint& paint,
                     CommandCoverageRecord* coverage) {
  if (command.path_effect_bytes.empty()) {
    return;
  }
  if (coverage) {
    coverage->path_effect_resource_present = true;
    coverage->path_effect_byte_count = command.path_effect_bytes.size();
  }
  sk_sp<SkPathEffect> path_effect =
      DeserializePathEffect(command.path_effect_bytes);
  if (!path_effect) {
    if (coverage) {
      coverage->skipped = true;
      coverage->skip_reason = "path_effect_deserialize_failed";
    }
    return;
  }
  if (coverage) {
    coverage->path_effect_deserialize_success = true;
  }
  paint.setPathEffect(std::move(path_effect));
}

void ApplyStrokeStyle(const DrawCommand& command, SkPaint& paint) {
  paint.setStrokeCap(static_cast<SkPaint::Cap>(command.stroke_cap));
  paint.setStrokeJoin(static_cast<SkPaint::Join>(command.stroke_join));
  paint.setStrokeMiter(command.stroke_miter);
}

bool QuickRejectBoundedDraw(SkCanvas& canvas,
                            const DrawCommand& command,
                            SkRect bounds) {
  if (!command.draw_looper_layers.empty()) {
    return false;
  }
  if (command.stroke_width > 0.0f) {
    const float outset = command.stroke_width * 0.5f + 1.0f;
    bounds.outset(outset, outset);
  }
  return canvas.quickReject(bounds);
}

bool RectCoversActiveDeviceClip(SkCanvas& canvas, SkRect local_rect) {
  SkIRect device_clip;
  if (!canvas.getDeviceClipBounds(&device_clip) || device_clip.isEmpty()) {
    return false;
  }
  SkMatrix inverse;
  if (!canvas.getTotalMatrix().invert(&inverse)) {
    return false;
  }
  SkRect local_clip = SkRect::Make(device_clip);
  inverse.mapRect(&local_clip);
  return local_rect.contains(local_clip);
}

bool IsUnitScaleTranslation(const SkMatrix& matrix) {
  return matrix.getScaleX() == 1.0f && matrix.getScaleY() == 1.0f &&
         matrix.getSkewX() == 0.0f && matrix.getSkewY() == 0.0f &&
         matrix.getPerspX() == 0.0f && matrix.getPerspY() == 0.0f &&
         matrix.get(SkMatrix::kMPersp2) == 1.0f;
}

bool IntegralRect(SkRect rect,
                  int* left,
                  int* top,
                  int* width,
                  int* height) {
  const float rounded_left = std::round(rect.left());
  const float rounded_top = std::round(rect.top());
  const float rounded_width = std::round(rect.width());
  const float rounded_height = std::round(rect.height());
  constexpr float kTolerance = 0.01f;
  if (std::abs(rect.left() - rounded_left) > kTolerance ||
      std::abs(rect.top() - rounded_top) > kTolerance ||
      std::abs(rect.width() - rounded_width) > kTolerance ||
      std::abs(rect.height() - rounded_height) > kTolerance) {
    return false;
  }
  *left = static_cast<int>(rounded_left);
  *top = static_cast<int>(rounded_top);
  *width = static_cast<int>(rounded_width);
  *height = static_cast<int>(rounded_height);
  return *width > 0 && *height > 0;
}

uint64_t HashShaderRectImageKey(const std::vector<uint8_t>& shader_bytes,
                                int left,
                                int top,
                                int width,
                                int height,
                                uint8_t alpha) {
  uint64_t hash = HashBytesForCache(shader_bytes);
  auto combine = [&hash](uint64_t value) {
    hash ^= value + 0x9e3779b97f4a7c15ull + (hash << 6) + (hash >> 2);
  };
  combine(static_cast<uint32_t>(left));
  combine(static_cast<uint32_t>(top));
  combine(static_cast<uint32_t>(width));
  combine(static_cast<uint32_t>(height));
  combine(alpha);
  return hash;
}

sk_sp<SkImage> FindCachedShaderRectImage(
    uint64_t hash,
    const std::vector<uint8_t>& shader_bytes,
    int left,
    int top,
    int width,
    int height,
    uint8_t alpha) {
  std::lock_guard<std::mutex> lock(ShaderRectImageCacheMutex());
  const auto found = ShaderRectImageCache().find(hash);
  if (found == ShaderRectImageCache().end()) {
    return nullptr;
  }
  for (const CachedShaderRectImage& cached : found->second) {
    if (cached.left == left && cached.top == top && cached.width == width &&
        cached.height == height && cached.alpha == alpha &&
        cached.shader_bytes == shader_bytes) {
      return cached.image;
    }
  }
  return nullptr;
}

void StoreCachedShaderRectImage(uint64_t hash,
                                std::vector<uint8_t> shader_bytes,
                                int left,
                                int top,
                                int width,
                                int height,
                                uint8_t alpha,
                                sk_sp<SkImage> image) {
  if (!image) {
    return;
  }
  const size_t byte_count =
      static_cast<size_t>(width) * static_cast<size_t>(height) * 4u;
  std::lock_guard<std::mutex> lock(ShaderRectImageCacheMutex());
  size_t total_bytes = 0;
  for (const auto& bucket : ShaderRectImageCache()) {
    for (const CachedShaderRectImage& cached : bucket.second) {
      total_bytes += cached.byte_count;
    }
  }
  constexpr size_t kMaxShaderRectImageCacheBytes = 64u * 1024u * 1024u;
  if (total_bytes + byte_count > kMaxShaderRectImageCacheBytes) {
    ShaderRectImageCache().clear();
  }
  ShaderRectImageCache()[hash].push_back(CachedShaderRectImage{
      std::move(shader_bytes), left, top, width, height, alpha, std::move(image),
      byte_count});
}

sk_sp<SkImage> CreateShaderRectImage(SkRect rect,
                                     sk_sp<SkShader> shader,
                                     uint8_t alpha,
                                     int left,
                                     int top,
                                     int width,
                                     int height) {
  SkImageInfo info =
      SkImageInfo::Make(width, height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  sk_sp<SkSurface> surface = SkSurfaces::Raster(info);
  if (!surface) {
    return nullptr;
  }
  SkCanvas* cache_canvas = surface->getCanvas();
  cache_canvas->translate(-static_cast<float>(left), -static_cast<float>(top));
  SkPaint paint;
  paint.setAntiAlias(true);
  paint.setStyle(SkPaint::kFill_Style);
  paint.setShader(std::move(shader));
  paint.setColor(SkColorSetARGB(alpha, 255, 255, 255));
  cache_canvas->drawRect(rect, paint);
  return surface->makeImageSnapshot();
}

sk_sp<SkImage> GetOrCreateShaderRectImage(const DrawCommand& command,
                                          SkRect rect,
                                          sk_sp<SkShader> shader,
                                          uint8_t alpha) {
  int left = 0;
  int top = 0;
  int width = 0;
  int height = 0;
  if (!IntegralRect(rect, &left, &top, &width, &height)) {
    return nullptr;
  }
  constexpr int kMinCachedArea = 256 * 256;
  constexpr int kMaxCachedDimension = 2048;
  if (width > kMaxCachedDimension || height > kMaxCachedDimension ||
      width * height < kMinCachedArea) {
    return nullptr;
  }
  const uint64_t hash = HashShaderRectImageKey(
      command.shader_bytes, left, top, width, height, alpha);
  if (sk_sp<SkImage> cached =
          FindCachedShaderRectImage(hash, command.shader_bytes, left, top,
                                    width, height, alpha)) {
    return cached;
  }
  sk_sp<SkImage> image =
      CreateShaderRectImage(rect, shader, alpha, left, top, width, height);
  if (image) {
    StoreCachedShaderRectImage(hash, command.shader_bytes, left, top, width,
                               height, alpha, image);
  }
  return image;
}

uint64_t CountChangedPixels(const std::vector<uint8_t>& before,
                            const uint8_t* after,
                            size_t after_size) {
  const size_t byte_count = std::min(before.size(), after_size);
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

void ResetCpuReplayCommandTimingDiagnostics() {
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  CpuReplayCommandTimingRecords().clear();
}

void StoreCpuReplayCommandTimings(
    const std::array<CpuReplayCommandTimingAccumulator,
                     kDrawCommandTypeCount>& timings) {
  std::vector<CpuReplayCommandTimingRecord> records;
  records.reserve(kDrawCommandTypeCount);
  for (size_t i = 0; i < timings.size(); ++i) {
    if (timings[i].count == 0) {
      continue;
    }
    CpuReplayCommandTimingRecord record;
    record.command_type = ToString(static_cast<DrawCommandType>(i));
    record.count = timings[i].count;
    record.elapsed_ms = timings[i].elapsed_ms;
    records.push_back(std::move(record));
  }
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  CpuReplayCommandTimingRecords() = std::move(records);
}

void BlitPreviousPixelsTranslated(const CpuImage& previous,
                                  uint8_t* pixels,
                                  int width,
                                  int height,
                                  Point delta) {
  const size_t expected_byte_count =
      static_cast<size_t>(width) * static_cast<size_t>(height) * 4u;
  const int dx = static_cast<int>(std::lround(delta.x));
  const int dy = static_cast<int>(std::lround(delta.y));
  const int src_left = std::max(0, -dx);
  const int src_top = std::max(0, -dy);
  const int dst_left = std::max(0, dx);
  const int dst_top = std::max(0, dy);
  const int copy_width = std::min(width - src_left, width - dst_left);
  const int copy_height = std::min(height - src_top, height - dst_top);
  if (copy_width <= 0 || copy_height <= 0) {
    return;
  }
  if (previous.pixels_rgba_bytes.size() == expected_byte_count) {
    for (int row = 0; row < copy_height; ++row) {
      const size_t src_offset =
          (static_cast<size_t>(src_top + row) * width + src_left) * 4u;
      const size_t dst_offset =
          (static_cast<size_t>(dst_top + row) * width + dst_left) * 4u;
      std::copy_n(previous.pixels_rgba_bytes.data() + src_offset,
                  static_cast<size_t>(copy_width) * 4u,
                  pixels + dst_offset);
    }
    return;
  }
  for (int row = 0; row < copy_height; ++row) {
    for (int col = 0; col < copy_width; ++col) {
      const size_t src_index =
          static_cast<size_t>(src_top + row) * width + (src_left + col);
      const uint32_t packed = previous.pixels_rgba[src_index];
      const size_t dst_index =
          static_cast<size_t>(dst_top + row) * width + (dst_left + col);
      const size_t offset = dst_index * 4u;
      pixels[offset + 0] = static_cast<uint8_t>((packed >> 24) & 0xff);
      pixels[offset + 1] = static_cast<uint8_t>((packed >> 16) & 0xff);
      pixels[offset + 2] = static_cast<uint8_t>((packed >> 8) & 0xff);
      pixels[offset + 3] = static_cast<uint8_t>(packed & 0xff);
    }
  }
}

void CopyPreviousPixelsToSkiaBytes(const CpuImage& previous,
                                   uint8_t* pixels,
                                   int width,
                                   int height) {
  const size_t expected_byte_count =
      static_cast<size_t>(width) * static_cast<size_t>(height) * 4u;
  if (previous.pixels_rgba_bytes.size() == expected_byte_count) {
    std::copy(previous.pixels_rgba_bytes.begin(),
              previous.pixels_rgba_bytes.end(), pixels);
    return;
  }
  for (size_t i = 0; i < previous.pixels_rgba.size(); ++i) {
    const uint32_t packed = previous.pixels_rgba[i];
    const size_t offset = i * 4u;
    pixels[offset + 0] = static_cast<uint8_t>((packed >> 24) & 0xff);
    pixels[offset + 1] = static_cast<uint8_t>((packed >> 16) & 0xff);
    pixels[offset + 2] = static_cast<uint8_t>((packed >> 8) & 0xff);
    pixels[offset + 3] = static_cast<uint8_t>(packed & 0xff);
  }
}

template <typename DrawProc>
void DrawWithLooperLayers(SkCanvas& canvas,
                          const DrawCommand& command,
                          const SkPaint& base_paint,
                          DrawProc draw_proc) {
  if (command.draw_looper_layers.empty()) {
    draw_proc(canvas, base_paint);
    return;
  }

  constexpr uint32_t kPostTransformFlag = 1u << 0;
  constexpr uint32_t kOverrideAlphaFlag = 1u << 1;
  constexpr uint32_t kDontModifyPaintFlag = 1u << 2;

  for (auto layer_it = command.draw_looper_layers.rbegin();
       layer_it != command.draw_looper_layers.rend(); ++layer_it) {
    const DrawLooperLayer& layer = *layer_it;
    SkAutoCanvasRestore auto_restore(&canvas, true);
    SkPaint paint(base_paint);
    if (!(layer.flags & kDontModifyPaintFlag)) {
      if (layer.flags & kOverrideAlphaFlag) {
        paint.setAlpha(0xFF);
      }
      if (layer.blur_sigma > 0.0f) {
        paint.setMaskFilter(SkMaskFilter::MakeBlur(
            kNormal_SkBlurStyle, layer.blur_sigma,
            !(layer.flags & kPostTransformFlag)));
      }
      paint.setColorFilter(SkColorFilters::Blend(
          ToSkColor4f(layer.color), SkColorSpace::MakeSRGB(),
          SkBlendMode::kSrcIn));
    }
    if (layer.flags & kPostTransformFlag) {
      canvas.setMatrix(canvas.getLocalToDevice().postTranslate(
          layer.offset_x, layer.offset_y));
    } else {
      canvas.translate(layer.offset_x, layer.offset_y);
    }
    draw_proc(canvas, paint);
  }
}

uint32_t PackRgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  return (static_cast<uint32_t>(r) << 24) |
         (static_cast<uint32_t>(g) << 16) |
         (static_cast<uint32_t>(b) << 8) | static_cast<uint32_t>(a);
}

void BlitPreviousImageTranslated(const CpuImage& previous,
                                 CpuImage& destination,
                                 Point delta) {
  const int dx = static_cast<int>(std::lround(delta.x));
  const int dy = static_cast<int>(std::lround(delta.y));
  const int src_left = std::max(0, -dx);
  const int src_top = std::max(0, -dy);
  const int dst_left = std::max(0, dx);
  const int dst_top = std::max(0, dy);
  const int copy_width = std::min(previous.width - src_left,
                                  destination.width - dst_left);
  const int copy_height = std::min(previous.height - src_top,
                                   destination.height - dst_top);
  if (copy_width <= 0 || copy_height <= 0) {
    return;
  }
  for (int row = 0; row < copy_height; ++row) {
    const size_t src_offset =
        static_cast<size_t>(src_top + row) * previous.width + src_left;
    const size_t dst_offset =
        static_cast<size_t>(dst_top + row) * destination.width + dst_left;
    std::copy_n(
        previous.pixels_rgba.begin() + static_cast<std::ptrdiff_t>(src_offset),
        copy_width,
        destination.pixels_rgba.begin() +
            static_cast<std::ptrdiff_t>(dst_offset));
  }
}

void CopySkiaPixelsToCpuImageRect(const uint8_t* pixels,
                                  const SkIRect& rect,
                                  CpuImage& image) {
  for (int y = rect.top(); y < rect.bottom(); ++y) {
    for (int x = rect.left(); x < rect.right(); ++x) {
      const size_t index = static_cast<size_t>(y) * image.width + x;
      const size_t offset = index * 4u;
      image.pixels_rgba[index] =
          PackRgba(pixels[offset + 0], pixels[offset + 1],
                   pixels[offset + 2], pixels[offset + 3]);
    }
  }
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
  sk_sp<SkImage> image;
  size_t byte_count = 0;
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
    image.byte_count = std::min(
        image.pixels.size(), static_cast<size_t>(image.width) *
                                 static_cast<size_t>(image.height) * 4u);
    SkImageInfo info = SkImageInfo::Make(image.width, image.height,
                                         kRGBA_8888_SkColorType,
                                         kPremul_SkAlphaType);
    sk_sp<SkData> pixel_data =
        SkData::MakeWithCopy(image.pixels.data(), image.byte_count);
    if (pixel_data) {
      image.image = SkImages::RasterFromData(
          info, std::move(pixel_data), static_cast<size_t>(image.width) * 4u);
    }
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
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
      paint.setStyle(SkPaint::kFill_Style);
      DrawWithLooperLayers(canvas, command, paint,
                           [&](SkCanvas& layer_canvas,
                               const SkPaint& layer_paint) {
                             layer_canvas.drawRect(ToSkRect(command.rect),
                                                   layer_paint);
                           });
      break;
    case DrawCommandType::kStrokeRect:
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
      paint.setStyle(SkPaint::kStroke_Style);
      paint.setStrokeWidth(command.stroke_width);
      ApplyStrokeStyle(command, paint);
      ApplyPathEffect(command, paint, coverage);
      DrawWithLooperLayers(canvas, command, paint,
                           [&](SkCanvas& layer_canvas,
                               const SkPaint& layer_paint) {
                             layer_canvas.drawRect(ToSkRect(command.rect),
                                                   layer_paint);
                           });
      break;
    case DrawCommandType::kFillRectShader:
      {
        const SkRect rect = ToSkRect(command.rect);
        const bool fill_active_clip = RectCoversActiveDeviceClip(canvas, rect);
        if (!fill_active_clip &&
            QuickRejectBoundedDraw(canvas, command, rect)) {
          break;
        }
        if (coverage) {
          coverage->shader_resource_present = !command.shader_bytes.empty();
          coverage->shader_byte_count = command.shader_bytes.size();
        }
        if (sk_sp<SkShader> shader = DeserializeShader(command.shader_bytes)) {
          if (coverage) {
            coverage->shader_deserialize_success = true;
          }
          const uint8_t alpha = ClampByte(command.color.a);
          if (fill_active_clip &&
              IsUnitScaleTranslation(canvas.getTotalMatrix())) {
            if (sk_sp<SkImage> image =
                    GetOrCreateShaderRectImage(command, rect, shader, alpha)) {
              canvas.drawImageRect(image, rect, SkSamplingOptions(), nullptr);
              break;
            }
          }
          paint.setStyle(SkPaint::kFill_Style);
          paint.setShader(std::move(shader));
          paint.setColor(SkColorSetARGB(alpha, 255, 255, 255));
          if (fill_active_clip) {
            canvas.drawPaint(paint);
          } else {
            canvas.drawRect(rect, paint);
          }
        } else if (coverage) {
          coverage->skipped = true;
          coverage->skip_reason = "shader_deserialize_failed";
        }
        break;
      }
    case DrawCommandType::kFillRRect:
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
      paint.setStyle(SkPaint::kFill_Style);
      DrawWithLooperLayers(canvas, command, paint,
                           [&](SkCanvas& layer_canvas,
                               const SkPaint& layer_paint) {
                              layer_canvas.drawRRect(ToSkRRect(command),
                                                     layer_paint);
                            });
      break;
    case DrawCommandType::kStrokeRRect:
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
      paint.setStyle(SkPaint::kStroke_Style);
      paint.setStrokeWidth(command.stroke_width);
      ApplyStrokeStyle(command, paint);
      ApplyPathEffect(command, paint, coverage);
      DrawWithLooperLayers(canvas, command, paint,
                           [&](SkCanvas& layer_canvas,
                               const SkPaint& layer_paint) {
                              layer_canvas.drawRRect(ToSkRRect(command),
                                                     layer_paint);
                            });
      break;
    case DrawCommandType::kFillRRectShader:
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
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
        canvas.drawRRect(ToSkRRect(command), paint);
      } else if (coverage) {
        coverage->skipped = true;
        coverage->skip_reason = "shader_deserialize_failed";
      }
      break;
   case DrawCommandType::kClipRect:
     canvas.clipRect(ToSkRect(command.rect));
     break;
   case DrawCommandType::kClipRRect: {
     canvas.clipRRect(ToSkRRect(command),
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
      {
        SkPaint layer_paint;
        layer_paint.setAlphaf(
            std::max(0.0f, std::min(1.0f, command.opacity)));
        layer_paint.setBlendMode(ParseBlendMode(command.blend_mode));
        if (!command.filter_operations.empty()) {
          cc::FilterOperations filter_operations =
              ToCcFilterOperations(command.filter_operations);
          sk_sp<cc::PaintFilter> paint_filter =
              cc::RenderSurfaceFilters::BuildImageFilter(
                  filter_operations, ToGfxRectEnclosing(command.rect));
          if (paint_filter) {
            layer_paint.setImageFilter(
                cc::PaintFilter::GetSkFilter(paint_filter.get()));
          }
        }
        if (command.save_layer_bounds_unset &&
            (command.rect.width <= 0.0f || command.rect.height <= 0.0f)) {
          canvas.saveLayer(nullptr, &layer_paint);
        } else {
          canvas.saveLayer(ToSkRect(command.rect), &layer_paint);
        }
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
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
      if (const auto found = images.find(command.resource_id);
          found != images.end()) {
        const ImageResource& resource = found->second;
        if (coverage) {
          coverage->image_resource_present = true;
          coverage->image_byte_count = resource.byte_count;
          coverage->image_resource_cache_hit = static_cast<bool>(resource.image);
          coverage->image_resource_cache_miss = !resource.image;
          coverage->image_width = resource.width;
          coverage->image_height = resource.height;
        }
        if (resource.image) {
          canvas.drawImageRect(resource.image, ToSkRect(command.rect),
                               ParseSamplingOptions(command.sampling_options),
                               nullptr);
        }
      }
      break;
    case DrawCommandType::kDrawImageRect:
      if (QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
      if (const auto found = images.find(command.resource_id);
          found != images.end()) {
        const ImageResource& resource = found->second;
        if (coverage) {
          coverage->image_resource_present = true;
          coverage->image_byte_count = resource.byte_count;
          coverage->image_resource_cache_hit = static_cast<bool>(resource.image);
          coverage->image_resource_cache_miss = !resource.image;
          coverage->image_width = resource.width;
          coverage->image_height = resource.height;
        }
        if (resource.image) {
          SkPaint image_paint;
          image_paint.setAlphaf(
              std::max(0.0f, std::min(1.0f, command.image_alpha)));
          image_paint.setBlendMode(ParseBlendMode(command.blend_mode));
          const SkCanvas::SrcRectConstraint constraint =
              command.src_rect_constraint == "fast"
                  ? SkCanvas::kFast_SrcRectConstraint
                  : SkCanvas::kStrict_SrcRectConstraint;
          canvas.drawImageRect(resource.image, ToSkRect(command.source_rect),
                               ToSkRect(command.rect),
                               ParseSamplingOptions(command.sampling_options),
                               &image_paint, constraint);
        }
      }
      break;
    case DrawCommandType::kDrawGlyphRun:
      DrawGlyphRunWithSkia(canvas, glyphs, command.glyph_run);
      break;
    case DrawCommandType::kDrawTextBlob: {
      if (command.rect.width > 0.0f && command.rect.height > 0.0f &&
          QuickRejectBoundedDraw(canvas, command, ToSkRect(command.rect))) {
        break;
      }
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
        DrawWithLooperLayers(canvas, command, paint,
                             [&](SkCanvas& layer_canvas,
                                 const SkPaint& layer_paint) {
                               layer_canvas.drawTextBlob(
                                   blob, command.rect.x, command.rect.y,
                                   layer_paint);
                             });
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
        if (command.stroke_width > 0.0f) {
          ApplyStrokeStyle(command, paint);
        }
        ApplyPathEffect(command, paint, coverage);
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
        DrawWithLooperLayers(canvas, command, paint,
                             [&](SkCanvas& layer_canvas,
                                 const SkPaint& layer_paint) {
                               layer_canvas.drawPath(*path, layer_paint);
                             });
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
                                                  const GlyphAtlas& glyphs,
                                                  const CpuImage* previous,
                                                  const Point* scroll_translation_delta,
                                                  bool clear_before_render,
                                                  const std::vector<Rect>* damage_rects) {
  CpuImage image;
  image.width = std::max(1, static_cast<int>(viewport.width));
  image.height = std::max(1, static_cast<int>(viewport.height));
  const bool incremental_base =
      !clear_before_render && previous && previous->width == image.width &&
      previous->height == image.height &&
      previous->pixels_rgba.size() ==
          static_cast<size_t>(image.width) * image.height;
  if (incremental_base) {
    if (scroll_translation_delta) {
      image.pixels_rgba.assign(
          static_cast<size_t>(image.width) * image.height,
          PackRgba(ClampByte(options.clear_color.r),
                   ClampByte(options.clear_color.g),
                   ClampByte(options.clear_color.b),
                   ClampByte(options.clear_color.a)));
      BlitPreviousImageTranslated(*previous, image, *scroll_translation_delta);
    } else {
      image.pixels_rgba = previous->pixels_rgba;
    }
  } else {
    image.pixels_rgba.resize(static_cast<size_t>(image.width) * image.height);
  }

  SkImageInfo info =
      SkImageInfo::Make(image.width, image.height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  const size_t pixel_byte_count =
      static_cast<size_t>(image.width) * image.height * 4u;
  std::vector<uint8_t> pixel_bytes(pixel_byte_count);
  uint8_t* pixels = pixel_bytes.data();
  SkSurfaceProps surface_props(0, kRGB_H_SkPixelGeometry);
  {
    std::lock_guard<std::mutex> lock(CommandCoverageMutex());
    auto& diagnostics = LastSurfaceDiagnostics();
    diagnostics.color_type = ColorTypeName(info.colorType());
    diagnostics.alpha_type = AlphaTypeName(info.alphaType());
    diagnostics.pixel_geometry = PixelGeometryName(surface_props.pixelGeometry());
    diagnostics.surface_props_flags = surface_props.flags();
    diagnostics.use_device_independent_fonts =
        surface_props.isUseDeviceIndependentFonts();
  }
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      info, pixels, static_cast<size_t>(image.width) * 4u,
      &surface_props);
  if (!surface) {
    return RasterizeDrawCommands(commands, viewport, options);
  }

  SkCanvas* canvas = surface->getCanvas();
  if (previous && previous->width == image.width &&
      previous->height == image.height &&
      previous->pixels_rgba.size() == image.pixels_rgba.size()) {
    if (scroll_translation_delta) {
      BlitPreviousPixelsTranslated(*previous, pixels, image.width,
                                   image.height, *scroll_translation_delta);
    } else {
      CopyPreviousPixelsToSkiaBytes(*previous, pixels, image.width,
                                    image.height);
    }
  }
  if (clear_before_render) {
    canvas->clear(ToSkColor(options.clear_color));
  }
  std::vector<SkIRect> damage_clips;
  if (!clear_before_render && damage_rects) {
    damage_clips.reserve(damage_rects->size());
    SkPaint clear_paint;
    clear_paint.setBlendMode(SkBlendMode::kSrc);
    clear_paint.setColor(ToSkColor(options.clear_color));
    for (const Rect& damage_rect : *damage_rects) {
      const SkIRect clip = ToSkIRectClamped(damage_rect, image.width,
                                            image.height);
      if (IsEmpty(clip)) {
        continue;
      }
      damage_clips.push_back(clip);
      canvas->save();
      canvas->clipIRect(clip);
      canvas->drawIRect(clip, clear_paint);
      canvas->restore();
    }
  }
  image.damage_clip_count = damage_clips.size();
  for (const SkIRect& clip : damage_clips) {
    image.raw_damage_area += PixelArea(clip);
  }
  image.coalesced_damage_area = RegionPixelArea(damage_clips);
  if (damage_rects && !clear_before_render) {
    image.command_replay_count_before_grouping =
        static_cast<uint64_t>(commands.size()) *
        static_cast<uint64_t>(damage_clips.size());
  } else {
    image.command_replay_count_before_grouping =
        static_cast<uint64_t>(commands.size());
  }
  int save_depth = 0;
  if (options.debug_command_coverage) {
    ResetCommandCoverageDiagnostics();
  }
  std::array<CpuReplayCommandTimingAccumulator, kDrawCommandTypeCount>
      command_timings = {};
  if (options.profile_command_timings) {
    ResetCpuReplayCommandTimingDiagnostics();
  }
  auto replay_commands = [&](bool measure_coverage) {
    const CpuReplayProfileClock::time_point replay_start =
        CpuReplayProfileClock::now();
    image.command_replay_count_after_grouping +=
        static_cast<uint64_t>(commands.size());
    for (size_t command_index = 0; command_index < commands.size();
         ++command_index) {
      const DrawCommand& command = commands[command_index];
      std::vector<uint8_t> before_pixels;
      CommandCoverageRecord coverage;
      CommandCoverageRecord* coverage_ptr = nullptr;
      if (measure_coverage) {
        before_pixels.assign(pixels, pixels + pixel_byte_count);
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
      CpuReplayProfileClock::time_point command_timing_start;
      if (options.profile_command_timings) {
        command_timing_start = CpuReplayProfileClock::now();
      }
      DrawCommandWithSkia(*canvas, command, images, glyphs,
                          options.strict_text_blob_typefaces, &save_depth,
                          coverage_ptr);
      if (options.profile_command_timings) {
        const double elapsed_ms =
            std::chrono::duration<double, std::milli>(
                CpuReplayProfileClock::now() - command_timing_start)
                .count();
        CpuReplayCommandTimingAccumulator& timing =
            command_timings[DrawCommandTypeIndex(command.type)];
        ++timing.count;
        timing.elapsed_ms += elapsed_ms;
      }
      if (measure_coverage) {
        coverage.save_depth_after = save_depth;
        coverage.pixels_changed =
            CountChangedPixels(before_pixels, pixels, pixel_byte_count);
        StoreCommandCoverage(std::move(coverage));
      }
    }
    image.cpu_replay_ms += std::chrono::duration<double, std::milli>(
                               CpuReplayProfileClock::now() - replay_start)
                               .count();
  };
  if (damage_rects && !clear_before_render && damage_clips.empty()) {
    image.raster_skipped = true;
  } else if (!damage_clips.empty() && !clear_before_render) {
    if (damage_clips.size() == 1) {
      image.replay_group_count = 1;
      canvas->save();
      canvas->clipIRect(damage_clips.front());
      replay_commands(options.debug_command_coverage);
      while (save_depth > 0) {
        canvas->restore();
        --save_depth;
      }
      canvas->restore();
    } else {
      struct ReplayClipGroup {
        std::vector<SkIRect> clips;
        SkIRect bounds;
        uint64_t pixel_area = 0;
      };
      auto clip_area = [](const SkIRect& clip) -> uint64_t {
        return static_cast<uint64_t>(std::max(0, clip.width())) *
               static_cast<uint64_t>(std::max(0, clip.height()));
      };
      auto union_clips = [](const SkIRect& a, const SkIRect& b) {
        SkIRect out = a;
        out.join(b);
        return out;
      };
      auto clips_overlap = [](const ReplayClipGroup& a,
                              const ReplayClipGroup& b) {
        for (const SkIRect& clip_a : a.clips) {
          for (const SkIRect& clip_b : b.clips) {
            if (SkIRect::Intersects(clip_a, clip_b)) {
              return true;
            }
          }
        }
        return false;
      };
      const uint64_t viewport_area = static_cast<uint64_t>(image.width) *
                                     static_cast<uint64_t>(image.height);
      const uint64_t max_added_group_pixels = viewport_area / 8u;
      constexpr double kMaxReplayGroupBoundsToDamageAreaRatio = 1.25;

      // Reduce duplicate command replay for nearby disjoint damage clips without
      // changing the damage clips copied back into the retained frame.
      const CpuReplayProfileClock::time_point grouping_start =
          CpuReplayProfileClock::now();
      std::vector<ReplayClipGroup> replay_groups;
      replay_groups.reserve(damage_clips.size());
      for (const SkIRect& clip : damage_clips) {
        replay_groups.push_back(ReplayClipGroup{{clip}, clip, clip_area(clip)});
      }
      if (!options.disable_damage_clip_grouping) {
        bool merged_group = true;
        while (merged_group) {
          merged_group = false;
          size_t best_i = 0;
          size_t best_j = 0;
          SkIRect best_bounds;
          uint64_t best_added_pixels = 0;
          bool have_best = false;
          for (size_t i = 0; i < replay_groups.size(); ++i) {
            for (size_t j = i + 1; j < replay_groups.size(); ++j) {
              if (clips_overlap(replay_groups[i], replay_groups[j])) {
                continue;
              }
              const SkIRect bounds =
                  union_clips(replay_groups[i].bounds, replay_groups[j].bounds);
              const uint64_t damage_area =
                  replay_groups[i].pixel_area + replay_groups[j].pixel_area;
              const uint64_t bounds_area = clip_area(bounds);
              if (bounds_area < damage_area) {
                continue;
              }
              const uint64_t added_pixels = bounds_area - damage_area;
              if (added_pixels > max_added_group_pixels ||
                  static_cast<double>(bounds_area) >
                      static_cast<double>(damage_area) *
                          kMaxReplayGroupBoundsToDamageAreaRatio) {
                continue;
              }
              if (!have_best || added_pixels < best_added_pixels) {
                best_i = i;
                best_j = j;
                best_bounds = bounds;
                best_added_pixels = added_pixels;
                have_best = true;
              }
            }
          }
          if (have_best) {
            replay_groups[best_i].clips.insert(
                replay_groups[best_i].clips.end(),
                replay_groups[best_j].clips.begin(),
                replay_groups[best_j].clips.end());
            replay_groups[best_i].bounds = best_bounds;
            replay_groups[best_i].pixel_area +=
                replay_groups[best_j].pixel_area;
            replay_groups.erase(replay_groups.begin() +
                                static_cast<std::ptrdiff_t>(best_j));
            merged_group = true;
          }
        }
      }
      image.damage_grouping_ms =
          std::chrono::duration<double, std::milli>(
              CpuReplayProfileClock::now() - grouping_start)
              .count();
      image.replay_group_count = replay_groups.size();

      for (size_t group_index = 0; group_index < replay_groups.size();
           ++group_index) {
        const ReplayClipGroup& group = replay_groups[group_index];
        canvas->save();
        if (group.clips.size() == 1) {
          canvas->clipIRect(group.clips.front());
        } else {
          const CpuReplayProfileClock::time_point region_start =
              CpuReplayProfileClock::now();
          SkRegion damage_region;
          for (const SkIRect& clip : group.clips) {
            damage_region.op(clip, SkRegion::kUnion_Op);
          }
          canvas->clipRegion(damage_region);
          image.skregion_clip_ms += std::chrono::duration<double, std::milli>(
                                        CpuReplayProfileClock::now() -
                                        region_start)
                                        .count();
        }
        replay_commands(options.debug_command_coverage && group_index == 0);
        while (save_depth > 0) {
          canvas->restore();
          --save_depth;
        }
        canvas->restore();
      }
    }
  } else {
    image.replay_group_count = commands.empty() ? 0 : 1;
    replay_commands(options.debug_command_coverage);
  }
  while (save_depth > 0) {
    canvas->restore();
    --save_depth;
  }
  if (options.profile_command_timings) {
    StoreCpuReplayCommandTimings(command_timings);
  }

  const CpuReplayProfileClock::time_point copyback_start =
      CpuReplayProfileClock::now();
  if (damage_rects) {
    for (const SkIRect& clip : damage_clips) {
      CopySkiaPixelsToCpuImageRect(pixels, clip, image);
    }
  } else {
    for (int y = 0; y < image.height; ++y) {
      for (int x = 0; x < image.width; ++x) {
        const size_t offset = (static_cast<size_t>(y) * image.width + x) * 4u;
        image.pixels_rgba[static_cast<size_t>(y) * image.width + x] =
            PackRgba(pixels[offset + 0], pixels[offset + 1],
                     pixels[offset + 2], pixels[offset + 3]);
      }
    }
  }
  image.copyback_ms = std::chrono::duration<double, std::milli>(
                          CpuReplayProfileClock::now() - copyback_start)
                          .count();
  image.pixels_rgba_bytes = std::move(pixel_bytes);

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

std::vector<CpuReplayCommandTimingRecord>
SnapshotCpuReplayCommandTimingDiagnostics() {
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  return CpuReplayCommandTimingRecords();
}

SkiaCpuSurfaceDiagnostics SnapshotSkiaCpuSurfaceDiagnostics() {
  std::lock_guard<std::mutex> lock(CommandCoverageMutex());
  return LastSurfaceDiagnostics();
}

CpuImage RasterizeDrawCommandsWithSkiaCpu(const DrawCommandList& commands,
                                          Size viewport,
                                          CpuRenderOptions options) {
  const ImageAtlas images;
  const GlyphAtlas glyphs;
  CpuImage image = RasterizeDrawCommandsWithSkiaCpuInternal(
      commands, viewport, options, images, glyphs, nullptr, nullptr, true,
      nullptr);
  image.raster_pixels_touched =
      static_cast<uint64_t>(image.width) * static_cast<uint64_t>(image.height);
  image.damage_pixels = image.raster_pixels_touched;
  return image;
}

CpuImage RasterizeRenderResultWithSkiaCpu(const RenderResult& result,
                                          CpuRenderOptions options) {
  const DrawCommandList commands =
      FlattenSceneDrawCommands(result.frame.scene_commands);
  const ImageAtlas images = BuildImageAtlas(result.frame.resource_commands);
  const GlyphAtlas glyphs = BuildGlyphAtlas(result.frame.resource_commands);
  CpuImage image = RasterizeDrawCommandsWithSkiaCpuInternal(
      commands, result.successor_snapshot.viewport, options, images, glyphs,
      nullptr, nullptr, true, nullptr);
  image.raster_pixels_touched =
      static_cast<uint64_t>(image.width) * static_cast<uint64_t>(image.height);
  image.damage_pixels = image.raster_pixels_touched;
  return image;
}

CpuImage RasterizeRenderResultIncrementalWithSkiaCpu(
    const RenderResult& result,
    const CpuImage* previous,
    CpuRenderOptions options) {
  const int width =
      std::max(1, static_cast<int>(result.successor_snapshot.viewport.width));
  const int height =
      std::max(1, static_cast<int>(result.successor_snapshot.viewport.height));
  if (result.frame.requires_full_redraw || !previous || previous->width != width ||
      previous->height != height ||
      previous->pixels_rgba.size() != static_cast<size_t>(width * height)) {
    return RasterizeRenderResultWithSkiaCpu(result, options);
  }
  if (result.frame.damage_rects.empty()) {
    CpuImage image = *previous;
    image.raster_pixels_touched = 0;
    image.damage_pixels = 0;
    image.raw_damage_area = 0;
    image.coalesced_damage_area = 0;
    image.command_replay_count_before_grouping = 0;
    image.command_replay_count_after_grouping = 0;
    image.damage_clip_count = 0;
    image.replay_group_count = 0;
    image.damage_grouping_ms = 0.0;
    image.skregion_clip_ms = 0.0;
    image.cpu_replay_ms = 0.0;
    image.copyback_ms = 0.0;
    image.raster_skipped = true;
    image.partial_raster = false;
    return image;
  }

  const DrawCommandList commands =
      FlattenSceneDrawCommands(result.frame.scene_commands);
  const ImageAtlas images = BuildImageAtlas(result.frame.resource_commands);
  const GlyphAtlas glyphs = BuildGlyphAtlas(result.frame.resource_commands);
  CpuImage image = RasterizeDrawCommandsWithSkiaCpuInternal(
      commands, result.successor_snapshot.viewport, options, images, glyphs,
      previous,
      result.frame.allows_scroll_translation_reuse
          ? &result.frame.scroll_translation_delta
          : nullptr,
      false, &result.frame.damage_rects);
  image.damage_pixels =
      DamagePixelArea(result.frame.damage_rects, image.width, image.height);
  image.raster_pixels_touched = image.damage_pixels;
  image.partial_raster =
      image.damage_pixels > 0 &&
      image.damage_pixels <
      static_cast<uint64_t>(image.width) * static_cast<uint64_t>(image.height);
  image.raster_skipped = image.raster_skipped || image.damage_pixels == 0;
  return image;
}

CpuImage RasterizeRenderResultDamageWithSkiaCpu(
    const RenderResult& result,
    CpuRenderOptions options) {
  const int width =
      std::max(1, static_cast<int>(result.successor_snapshot.viewport.width));
  const int height =
      std::max(1, static_cast<int>(result.successor_snapshot.viewport.height));
  if (result.frame.requires_full_redraw || result.frame.damage_rects.empty()) {
    return RasterizeRenderResultWithSkiaCpu(result, options);
  }
  const DrawCommandList commands =
      FlattenSceneDrawCommands(result.frame.scene_commands);
  const ImageAtlas images = BuildImageAtlas(result.frame.resource_commands);
  const GlyphAtlas glyphs = BuildGlyphAtlas(result.frame.resource_commands);
  CpuImage image = RasterizeDrawCommandsWithSkiaCpuInternal(
      commands, result.successor_snapshot.viewport, options, images, glyphs,
      nullptr, nullptr, false, &result.frame.damage_rects);
  image.width = width;
  image.height = height;
  image.damage_pixels = DamagePixelArea(result.frame.damage_rects, width,
                                        height);
  image.raster_pixels_touched = image.damage_pixels;
  image.partial_raster =
      image.damage_pixels > 0 &&
      image.damage_pixels <
      static_cast<uint64_t>(width) * static_cast<uint64_t>(height);
  image.raster_skipped = image.raster_skipped || image.damage_pixels == 0;
  return image;
}

}  // namespace html_css_renderer
