#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_H_

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace html_css_renderer {

struct Color {
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 1.0f;

  static Color Rgba(float red, float green, float blue, float alpha = 1.0f);
};

struct Point {
  float x = 0.0f;
  float y = 0.0f;
};

struct Size {
  float width = 0.0f;
  float height = 0.0f;
};

struct Rect {
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

struct Matrix4 {
  std::array<float, 16> values = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
  };
};

enum class DrawCommandType {
  kSave,
  kRestore,
  kTransform,
  kClipRect,
  kSaveLayer,
  kFillRect,
  kStrokeRect,
  kFillRRect,
  kStrokeRRect,
  kFillPath,
  kDrawImage,
  kDrawGlyphRun,
  kDrawText,
  kDiagnostic,
};

struct GlyphRun {
  std::string font_id;
  float font_size = 16.0f;
  std::vector<uint32_t> glyph_ids;
  std::vector<Point> positions;
  Color color;
};

struct DrawCommand {
  DrawCommandType type = DrawCommandType::kDiagnostic;
  Rect rect;
  Matrix4 transform;
  Color color;
  float stroke_width = 1.0f;
  float radius_x = 0.0f;
  float radius_y = 0.0f;
  float opacity = 1.0f;
  std::string text;
  std::string path_data;
  std::string resource_id;
  GlyphRun glyph_run;

  static DrawCommand Save();
  static DrawCommand Restore();
  static DrawCommand Transform(Matrix4 matrix);
  static DrawCommand ClipRect(Rect clip);
  static DrawCommand SaveLayer(Rect bounds, float opacity);
  static DrawCommand FillRect(Rect bounds, Color fill);
  static DrawCommand StrokeRect(Rect bounds, Color stroke, float width);
  static DrawCommand FillRRect(Rect bounds, float radius_x, float radius_y,
                               Color fill);
  static DrawCommand StrokeRRect(Rect bounds, float radius_x, float radius_y,
                                 Color stroke, float width);
  static DrawCommand FillPath(std::string path_data, Color fill);
  static DrawCommand DrawImage(std::string id, Rect destination);
  static DrawCommand DrawGlyphRun(GlyphRun run);
  static DrawCommand DrawText(std::string value, Point origin, Color fill,
                              float font_size);
  static DrawCommand Diagnostic(std::string message);
};

using DrawCommandList = std::vector<DrawCommand>;

const char* ToString(DrawCommandType type);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_H_
