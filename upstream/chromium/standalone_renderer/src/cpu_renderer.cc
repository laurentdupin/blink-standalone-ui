#include "html_css_renderer/cpu_renderer.h"

#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>
#include <utility>

namespace html_css_renderer {
namespace {

uint8_t ClampByte(float value) {
  const float clamped = std::max(0.0f, std::min(1.0f, value));
  return static_cast<uint8_t>(std::round(clamped * 255.0f));
}

uint32_t PackRgba(Color color) {
  return (static_cast<uint32_t>(ClampByte(color.r)) << 24) |
         (static_cast<uint32_t>(ClampByte(color.g)) << 16) |
         (static_cast<uint32_t>(ClampByte(color.b)) << 8) |
         static_cast<uint32_t>(ClampByte(color.a));
}

Color UnpackRgba(uint32_t packed) {
  return Color::Rgba(((packed >> 24) & 0xff) / 255.0f,
                     ((packed >> 16) & 0xff) / 255.0f,
                     ((packed >> 8) & 0xff) / 255.0f,
                     (packed & 0xff) / 255.0f);
}

uint32_t BlendOver(uint32_t destination, Color source) {
  const Color dst = UnpackRgba(destination);
  const float src_a = std::max(0.0f, std::min(1.0f, source.a));
  const float inv_a = 1.0f - src_a;
  return PackRgba(Color::Rgba(source.r * src_a + dst.r * inv_a,
                             source.g * src_a + dst.g * inv_a,
                             source.b * src_a + dst.b * inv_a,
                             src_a + dst.a * inv_a));
}

int FloorToInt(float value) {
  return static_cast<int>(std::floor(value));
}

int CeilToInt(float value) {
  return static_cast<int>(std::ceil(value));
}

struct PixelRect {
  int left = 0;
  int top = 0;
  int right = 0;
  int bottom = 0;
};

struct CpuGlyphMask {
  Rect bounds;
  int width = 0;
  int height = 0;
  std::vector<uint8_t> pixels;
};

using CpuGlyphAtlas = std::unordered_map<std::string, CpuGlyphMask>;

std::string GlyphKey(const std::string& font_id, uint32_t glyph_id) {
  return font_id + "#" + std::to_string(glyph_id);
}

PixelRect ClipRectToImage(Rect rect, const CpuImage& image) {
  PixelRect clipped;
  clipped.left = std::max(0, FloorToInt(rect.x));
  clipped.top = std::max(0, FloorToInt(rect.y));
  clipped.right = std::min(image.width, CeilToInt(rect.x + rect.width));
  clipped.bottom = std::min(image.height, CeilToInt(rect.y + rect.height));
  if (clipped.right < clipped.left) {
    clipped.right = clipped.left;
  }
  if (clipped.bottom < clipped.top) {
    clipped.bottom = clipped.top;
  }
  return clipped;
}

PixelRect Intersect(PixelRect a, PixelRect b) {
  PixelRect result;
  result.left = std::max(a.left, b.left);
  result.top = std::max(a.top, b.top);
  result.right = std::min(a.right, b.right);
  result.bottom = std::min(a.bottom, b.bottom);
  if (result.right < result.left) {
    result.right = result.left;
  }
  if (result.bottom < result.top) {
    result.bottom = result.top;
  }
  return result;
}

PixelRect FullImageClip(const CpuImage& image) {
  return PixelRect{0, 0, image.width, image.height};
}

void FillRect(CpuImage& image, Rect rect, Color color, PixelRect clip) {
  const PixelRect clipped = Intersect(ClipRectToImage(rect, image), clip);
  for (int y = clipped.top; y < clipped.bottom; ++y) {
    for (int x = clipped.left; x < clipped.right; ++x) {
      uint32_t& pixel = image.pixels_rgba[y * image.width + x];
      pixel = BlendOver(pixel, color);
    }
  }
}

void StrokeRect(CpuImage& image,
                Rect rect,
                Color color,
                float width,
                PixelRect clip) {
  const float stroke = std::max(1.0f, width);
  FillRect(image, Rect{rect.x, rect.y, rect.width, stroke}, color, clip);
  FillRect(image, Rect{rect.x, rect.y + rect.height - stroke, rect.width,
                       stroke},
           color, clip);
  FillRect(image, Rect{rect.x, rect.y, stroke, rect.height}, color, clip);
  FillRect(image, Rect{rect.x + rect.width - stroke, rect.y, stroke,
                       rect.height},
           color, clip);
}

Color ImagePlaceholderColor(const std::string& resource_id) {
  uint32_t hash = 2166136261u;
  for (const unsigned char c : resource_id) {
    hash ^= c;
    hash *= 16777619u;
  }
  const float r = 0.25f + ((hash >> 0) & 0xff) / 510.0f;
  const float g = 0.25f + ((hash >> 8) & 0xff) / 510.0f;
  const float b = 0.25f + ((hash >> 16) & 0xff) / 510.0f;
  return Color::Rgba(r, g, b, 1.0f);
}

void DrawGlyphMask(CpuImage& image,
                   const CpuGlyphMask& mask,
                   Point origin,
                   Color color,
                   PixelRect clip) {
  const int left = FloorToInt(origin.x + mask.bounds.x);
  const int top = FloorToInt(origin.y + mask.bounds.y);
  for (int row = 0; row < mask.height; ++row) {
    const int y = top + row;
    if (y < clip.top || y >= clip.bottom || y < 0 || y >= image.height) {
      continue;
    }
    for (int col = 0; col < mask.width; ++col) {
      const int x = left + col;
      if (x < clip.left || x >= clip.right || x < 0 || x >= image.width) {
        continue;
      }
      const uint8_t coverage =
          mask.pixels[static_cast<size_t>(row * mask.width + col)];
      if (coverage == 0) {
        continue;
      }
      Color source = color;
      source.a *= coverage / 255.0f;
      uint32_t& pixel = image.pixels_rgba[y * image.width + x];
      pixel = BlendOver(pixel, source);
    }
  }
}

void DrawGlyphRunWithAtlas(CpuImage& image,
                           const DrawCommand& command,
                           const CpuGlyphAtlas& atlas,
                           PixelRect clip) {
  const size_t count = std::min(command.glyph_run.glyph_ids.size(),
                                command.glyph_run.positions.size());
  for (size_t i = 0; i < count; ++i) {
    const auto found = atlas.find(GlyphKey(command.glyph_run.font_id,
                                          command.glyph_run.glyph_ids[i]));
    if (found == atlas.end()) {
      continue;
    }
    DrawGlyphMask(image, found->second, command.glyph_run.positions[i],
                  command.glyph_run.color, clip);
  }
}

CpuImage CreateClearedImage(Size viewport, CpuRenderOptions options) {
  CpuImage image;
  image.width = std::max(1, CeilToInt(viewport.width));
  image.height = std::max(1, CeilToInt(viewport.height));
  image.pixels_rgba.assign(static_cast<size_t>(image.width * image.height),
                           PackRgba(options.clear_color));
  return image;
}

void RasterizeDrawCommandsWithAtlasInto(CpuImage& image,
                                        const DrawCommandList& commands,
                                        const CpuGlyphAtlas& atlas) {
  std::vector<PixelRect> clip_stack;
  clip_stack.push_back(FullImageClip(image));

  for (const DrawCommand& command : commands) {
    const PixelRect current_clip = clip_stack.back();
    switch (command.type) {
      case DrawCommandType::kFillRect:
        FillRect(image, command.rect, command.color, current_clip);
        break;
      case DrawCommandType::kStrokeRect:
        StrokeRect(image, command.rect, command.color, command.stroke_width,
                   current_clip);
        break;
      case DrawCommandType::kFillRectShader:
        FillRect(image, command.rect, command.color, current_clip);
        break;
      case DrawCommandType::kFillRRect:
        FillRect(image, command.rect, command.color, current_clip);
        break;
      case DrawCommandType::kStrokeRRect:
        StrokeRect(image, command.rect, command.color, command.stroke_width,
                   current_clip);
        break;
      case DrawCommandType::kFillRRectShader:
        FillRect(image, command.rect, command.color, current_clip);
        break;
      case DrawCommandType::kDrawImage:
        FillRect(image, command.rect,
                 ImagePlaceholderColor(command.resource_id), current_clip);
        StrokeRect(image, command.rect, Color::Rgba(0.0f, 0.0f, 0.0f, 0.35f),
                   1.0f, current_clip);
        break;
      case DrawCommandType::kDrawText:
        break;
        break;
      case DrawCommandType::kDrawGlyphRun:
        DrawGlyphRunWithAtlas(image, command, atlas, current_clip);
        break;
      case DrawCommandType::kDrawTextBlob:
        break;
      case DrawCommandType::kSave:
        clip_stack.push_back(current_clip);
        break;
      case DrawCommandType::kRestore:
        if (clip_stack.size() > 1) {
          clip_stack.pop_back();
        }
        break;
      case DrawCommandType::kClipRect:
        clip_stack.back() =
            Intersect(current_clip, ClipRectToImage(command.rect, image));
        break;
      case DrawCommandType::kClipRRect:
        clip_stack.back() =
            Intersect(current_clip, ClipRectToImage(command.rect, image));
        break;
      case DrawCommandType::kClipPath:
        break;
      case DrawCommandType::kTransform:
      case DrawCommandType::kSaveLayer:
      case DrawCommandType::kFillPath:
      case DrawCommandType::kDiagnostic:
        break;
    }
  }
}

CpuImage RasterizeDrawCommandsWithAtlas(const DrawCommandList& commands,
                                        Size viewport,
                                        const CpuGlyphAtlas& atlas,
                                        CpuRenderOptions options) {
  CpuImage image = CreateClearedImage(viewport, options);
  RasterizeDrawCommandsWithAtlasInto(image, commands, atlas);
  return image;
}

CpuGlyphAtlas BuildGlyphAtlas(const LoadCommandList& load_commands) {
  CpuGlyphAtlas atlas;
  for (const LoadCommand& command : load_commands) {
    if (command.type != LoadCommandType::kGlyphAtlasUpdate) {
      continue;
    }
    const GlyphAtlasUpdate& update = command.glyph_atlas_update;
    if (update.format != PixelFormat::kAlpha8 || update.bounds.width <= 0.0f ||
        update.bounds.height <= 0.0f) {
      continue;
    }
    CpuGlyphMask mask;
    mask.bounds = update.bounds;
    mask.width = FloorToInt(update.bounds.width);
    mask.height = FloorToInt(update.bounds.height);
    if (mask.width <= 0 || mask.height <= 0 ||
        update.pixels.size() <
            static_cast<size_t>(mask.width * mask.height)) {
      continue;
    }
    mask.pixels = update.pixels;
    atlas[GlyphKey(update.font_id, update.glyph_id)] = std::move(mask);
  }
  return atlas;
}

CpuGlyphAtlas BuildGlyphAtlas(const std::vector<ResourceCommand>& commands) {
  return BuildGlyphAtlas(FlattenResourceCommands(commands));
}

}  // namespace

CpuImage RasterizeDrawCommands(const DrawCommandList& commands,
                               Size viewport,
                               CpuRenderOptions options) {
  return RasterizeDrawCommandsWithAtlas(commands, viewport, {}, options);
}

CpuImage RasterizeRenderResult(const RenderResult& result,
                               CpuRenderOptions options) {
  const CpuGlyphAtlas atlas = BuildGlyphAtlas(result.frame.resource_commands);
  const DrawCommandList draw_commands =
      FlattenSceneDrawCommands(result.frame.scene_commands);
  return RasterizeDrawCommandsWithAtlas(draw_commands,
                                        result.successor_snapshot.viewport,
                                        atlas, options);
}

CpuImage RasterizeRenderResultIncremental(const RenderResult& result,
                                          const CpuImage* previous,
                                          CpuRenderOptions options) {
  const int width =
      std::max(1, CeilToInt(result.successor_snapshot.viewport.width));
  const int height =
      std::max(1, CeilToInt(result.successor_snapshot.viewport.height));
  if (result.frame.requires_full_redraw || !previous || previous->width != width ||
      previous->height != height ||
      previous->pixels_rgba.size() != static_cast<size_t>(width * height)) {
    return RasterizeRenderResult(result, options);
  }

  CpuImage image = *previous;
  const CpuGlyphAtlas atlas = BuildGlyphAtlas(result.frame.resource_commands);
  const DrawCommandList draw_commands =
      FlattenSceneDrawCommands(result.frame.scene_commands);
  RasterizeDrawCommandsWithAtlasInto(image, draw_commands, atlas);
  return image;
}

}  // namespace html_css_renderer
