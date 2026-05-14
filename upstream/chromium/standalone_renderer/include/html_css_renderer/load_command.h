#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_LOAD_COMMAND_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_LOAD_COMMAND_H_

#include <cstdint>
#include <string>
#include <vector>

#include "html_css_renderer/draw_command.h"

namespace html_css_renderer {

enum class LoadCommandType {
  kLoadImage,
  kLoadFont,
  kGlyphAtlasUpdate,
};

enum class PixelFormat {
  kUnknown,
  kRgba8888,
  kAlpha8,
};

struct FontLoadInfo {
  std::string font_id;
  std::string resource_id;
  std::string mime_type;
  uint64_t bytes_hash = 0;
  size_t byte_count = 0;
};

struct ImageLoadInfo {
  std::string image_id;
  std::string resource_id;
  std::string mime_type;
  uint64_t bytes_hash = 0;
  size_t byte_count = 0;
  PixelFormat decoded_format = PixelFormat::kUnknown;
  Size decoded_size;
  std::vector<uint8_t> decoded_pixels;
};

struct GlyphAtlasUpdate {
  std::string atlas_id;
  std::string font_id;
  uint32_t glyph_id = 0;
  Rect bounds;
  PixelFormat format = PixelFormat::kAlpha8;
  std::vector<uint8_t> pixels;
};

struct LoadCommand {
  LoadCommandType type = LoadCommandType::kLoadImage;
  FontLoadInfo font;
  ImageLoadInfo image;
  GlyphAtlasUpdate glyph_atlas_update;

  static LoadCommand LoadFont(FontLoadInfo info);
  static LoadCommand LoadImage(ImageLoadInfo info);
  static LoadCommand UpdateGlyphAtlas(GlyphAtlasUpdate update);
};

using LoadCommandList = std::vector<LoadCommand>;

const char* ToString(LoadCommandType type);
const char* ToString(PixelFormat format);
uint64_t HashBytes(const std::vector<uint8_t>& bytes);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_LOAD_COMMAND_H_
