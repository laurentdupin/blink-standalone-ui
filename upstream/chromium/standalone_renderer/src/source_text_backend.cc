#include "html_css_renderer/source_text_backend.h"

#include <algorithm>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

#if defined(HTML_CSS_RENDERER_HAS_SOURCE_TEXT_BACKEND)
#include <hb.h>
#include <hb-ot.h>

#include <ft2build.h>
#include FT_FREETYPE_H
#endif

namespace html_css_renderer {

#if defined(HTML_CSS_RENDERER_HAS_SOURCE_TEXT_BACKEND)
namespace {

class HarfbuzzFreetypeTextBackend final : public SourceTextBackend {
 public:
  HarfbuzzFreetypeTextBackend() {
    if (FT_Init_FreeType(&library_) != 0) {
      library_ = nullptr;
    }
  }

  ~HarfbuzzFreetypeTextBackend() override {
    for (auto& entry : fonts_) {
      if (entry.second.face) {
        FT_Done_Face(entry.second.face);
      }
    }
    if (library_) {
      FT_Done_FreeType(library_);
    }
  }

  bool RegisterFont(const FontAsset& asset) override {
    if (!library_ || asset.font_id.empty() || asset.bytes.empty()) {
      return false;
    }

    LoadedFont loaded;
    loaded.asset = asset;
    if (FT_New_Memory_Face(
            library_, loaded.asset.bytes.data(),
            static_cast<FT_Long>(loaded.asset.bytes.size()), 0,
            &loaded.face) != 0) {
      return false;
    }

    if (FT_Select_Charmap(loaded.face, FT_ENCODING_UNICODE) != 0 &&
        loaded.face->num_charmaps > 0) {
      FT_Set_Charmap(loaded.face, loaded.face->charmaps[0]);
    }

    auto existing = fonts_.find(asset.font_id);
    if (existing != fonts_.end() && existing->second.face) {
      FT_Done_Face(existing->second.face);
    }
    fonts_[asset.font_id] = std::move(loaded);
    return true;
  }

  std::optional<std::string> MatchFont(const FontQuery& query) override {
    if (!query.family.empty()) {
      const auto by_family = fonts_.find(query.family);
      if (by_family != fonts_.end()) {
        return by_family->first;
      }
    }
    if (fonts_.empty()) {
      return std::nullopt;
    }
    return fonts_.begin()->first;
  }

  TextShapeResult ShapeText(const TextShapeInput& input) override {
    TextShapeResult result;
    result.glyph_run.font_id = input.font_id;
    result.glyph_run.font_size = input.font_size;
    result.glyph_run.color = input.color;

    const auto font = fonts_.find(input.font_id);
    if (font == fonts_.end()) {
      result.diagnostics.push_back("missing font for shaping: " + input.font_id);
      return result;
    }

    hb_blob_t* blob = hb_blob_create(
        reinterpret_cast<const char*>(font->second.asset.bytes.data()),
        static_cast<unsigned int>(font->second.asset.bytes.size()),
        HB_MEMORY_MODE_READONLY, nullptr, nullptr);
    hb_face_t* face = hb_face_create(blob, 0);
    hb_font_t* hb_font = hb_font_create(face);
    const int scale = static_cast<int>(std::max(1.0f, input.font_size) * 64.0f);
    hb_font_set_scale(hb_font, scale, scale);
    hb_ot_font_set_funcs(hb_font);

    hb_buffer_t* buffer = hb_buffer_create();
    hb_buffer_add_utf8(buffer, input.text.c_str(), -1, 0, -1);
    switch (input.direction) {
      case TextDirection::kLeftToRight:
        hb_buffer_set_direction(buffer, HB_DIRECTION_LTR);
        break;
      case TextDirection::kRightToLeft:
        hb_buffer_set_direction(buffer, HB_DIRECTION_RTL);
        break;
      case TextDirection::kAuto:
        break;
    }
    hb_buffer_guess_segment_properties(buffer);
    hb_shape(hb_font, buffer, nullptr, 0);

    unsigned int glyph_count = 0;
    hb_glyph_info_t* infos = hb_buffer_get_glyph_infos(buffer, &glyph_count);
    hb_glyph_position_t* positions =
        hb_buffer_get_glyph_positions(buffer, &glyph_count);

    float x = input.origin.x;
    float y = input.origin.y;
    result.glyph_run.glyph_ids.reserve(glyph_count);
    result.glyph_run.positions.reserve(glyph_count);
    for (unsigned int i = 0; i < glyph_count; ++i) {
      result.glyph_run.glyph_ids.push_back(infos[i].codepoint);
      result.glyph_run.positions.push_back(
          Point{x + positions[i].x_offset / 64.0f,
                y - positions[i].y_offset / 64.0f});
      x += positions[i].x_advance / 64.0f;
      y -= positions[i].y_advance / 64.0f;
    }

    hb_buffer_destroy(buffer);
    hb_font_destroy(hb_font);
    hb_face_destroy(face);
    hb_blob_destroy(blob);
    return result;
  }

  GlyphRasterResult RasterizeGlyphs(const GlyphRasterInput& input) override {
    GlyphRasterResult result;
    const auto font = fonts_.find(input.glyph_run.font_id);
    if (font == fonts_.end()) {
      result.diagnostics.push_back("missing font for raster: " +
                                   input.glyph_run.font_id);
      return result;
    }

    if (FT_Set_Pixel_Sizes(font->second.face, 0,
                           static_cast<FT_UInt>(std::max(
                               1.0f, input.glyph_run.font_size))) != 0) {
      result.diagnostics.push_back("failed to set font pixel size: " +
                                   input.glyph_run.font_id);
      return result;
    }

    for (const uint32_t glyph_id : input.glyph_run.glyph_ids) {
      if (FT_Load_Glyph(font->second.face, glyph_id,
                        FT_LOAD_RENDER | FT_LOAD_TARGET_NORMAL) != 0) {
        result.diagnostics.push_back("failed to raster glyph");
        continue;
      }

      const FT_GlyphSlot slot = font->second.face->glyph;
      const FT_Bitmap& bitmap = slot->bitmap;
      GlyphAtlasUpdate update;
      update.atlas_id = input.atlas_id.empty() ? "default" : input.atlas_id;
      update.font_id = input.glyph_run.font_id;
      update.glyph_id = glyph_id;
      update.format = PixelFormat::kAlpha8;
      update.bounds = Rect{static_cast<float>(slot->bitmap_left),
                           static_cast<float>(-slot->bitmap_top),
                           static_cast<float>(bitmap.width),
                           static_cast<float>(bitmap.rows)};
      update.pixels.resize(static_cast<size_t>(bitmap.width * bitmap.rows));
      for (unsigned int row = 0; row < bitmap.rows; ++row) {
        const unsigned char* source =
            bitmap.buffer + row * std::abs(bitmap.pitch);
        std::copy(source, source + bitmap.width,
                  update.pixels.begin() + row * bitmap.width);
      }
      result.atlas_updates.push_back(std::move(update));
    }
    return result;
  }

 private:
  struct LoadedFont {
    FontAsset asset;
    FT_Face face = nullptr;
  };

  FT_Library library_ = nullptr;
  std::unordered_map<std::string, LoadedFont> fonts_;
};

}  // namespace
#endif  // defined(HTML_CSS_RENDERER_HAS_SOURCE_TEXT_BACKEND)

bool IsSourceTextBackendAvailable() {
#if defined(HTML_CSS_RENDERER_HAS_SOURCE_TEXT_BACKEND)
  return true;
#else
  return false;
#endif
}

std::unique_ptr<SourceTextBackend> CreateSourceTextBackend() {
#if defined(HTML_CSS_RENDERER_HAS_SOURCE_TEXT_BACKEND)
  return std::make_unique<HarfbuzzFreetypeTextBackend>();
#else
  return nullptr;
#endif
}

}  // namespace html_css_renderer
