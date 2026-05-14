#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_TEXT_ENGINE_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_TEXT_ENGINE_H_

#include <optional>
#include <string>
#include <vector>

#include "html_css_renderer/draw_command.h"
#include "html_css_renderer/load_command.h"

namespace html_css_renderer {

enum class TextDirection {
  kAuto,
  kLeftToRight,
  kRightToLeft,
};

struct FontAsset {
  std::string font_id;
  std::string resource_id;
  std::string mime_type;
  std::vector<uint8_t> bytes;
};

struct FontQuery {
  std::string family;
  float weight = 400.0f;
  float stretch = 100.0f;
  bool italic = false;
  std::string locale;
};

struct TextShapeInput {
  std::string text;
  FontQuery font_query;
  std::string font_id;
  float font_size = 16.0f;
  TextDirection direction = TextDirection::kAuto;
  Point origin;
  Color color;
};

struct TextShapeResult {
  GlyphRun glyph_run;
  std::vector<std::string> diagnostics;
};

struct GlyphRasterInput {
  GlyphRun glyph_run;
  std::string atlas_id;
};

struct GlyphRasterResult {
  std::vector<GlyphAtlasUpdate> atlas_updates;
  std::vector<std::string> diagnostics;
};

class FontProvider {
 public:
  virtual ~FontProvider() = default;
  virtual bool RegisterFont(const FontAsset& asset) = 0;
  virtual std::optional<std::string> MatchFont(const FontQuery& query) = 0;
};

class TextShaper {
 public:
  virtual ~TextShaper() = default;
  virtual TextShapeResult ShapeText(const TextShapeInput& input) = 0;
};

class GlyphRasterizer {
 public:
  virtual ~GlyphRasterizer() = default;
  virtual GlyphRasterResult RasterizeGlyphs(
      const GlyphRasterInput& input) = 0;
};

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_TEXT_ENGINE_H_
