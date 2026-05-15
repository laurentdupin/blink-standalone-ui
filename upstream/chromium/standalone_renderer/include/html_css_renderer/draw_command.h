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
  kClipRRect,
  kClipPath,
  kSaveLayer,
  kFillRect,
  kStrokeRect,
  kFillRectShader,
  kFillRRect,
  kStrokeRRect,
  kFillRRectShader,
  kFillPath,
  kDrawImage,
  kDrawGlyphRun,
  kDrawTextBlob,
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
  std::array<Point, 4> corner_radii = {};
  bool clip_difference = false;
  float opacity = 1.0f;
  std::string text;
  std::string path_data;
  std::vector<uint8_t> path_bytes;
  std::vector<uint8_t> text_blob_bytes;
  std::vector<uint8_t> shader_bytes;
  std::string resource_id;
  GlyphRun glyph_run;

  static DrawCommand Save();
  static DrawCommand Restore();
  static DrawCommand Transform(Matrix4 matrix);
  static DrawCommand ClipRect(Rect clip);
  static DrawCommand ClipRRect(Rect clip, float radius_x, float radius_y);
  static DrawCommand ClipRRect(Rect clip,
                               std::array<Point, 4> corner_radii,
                               bool difference = false);
  static DrawCommand ClipPath(std::vector<uint8_t> path_bytes,
                              bool difference = false);
  static DrawCommand SaveLayer(Rect bounds, float opacity);
  static DrawCommand FillRect(Rect bounds, Color fill);
  static DrawCommand StrokeRect(Rect bounds, Color stroke, float width);
  static DrawCommand FillRectShader(Rect bounds,
                                    std::vector<uint8_t> shader_bytes,
                                    Color modulation);
  static DrawCommand FillRRect(Rect bounds, float radius_x, float radius_y,
                               Color fill);
  static DrawCommand StrokeRRect(Rect bounds, float radius_x, float radius_y,
                                 Color stroke, float width);
  static DrawCommand FillRRectShader(Rect bounds,
                                     float radius_x,
                                     float radius_y,
                                     std::vector<uint8_t> shader_bytes,
                                     Color modulation);
  static DrawCommand FillPath(std::vector<uint8_t> path_bytes,
                              Color fill,
                              float stroke_width = 0.0f,
                              std::vector<uint8_t> shader_bytes = {});
  static DrawCommand DrawImage(std::string id, Rect destination);
  static DrawCommand DrawGlyphRun(GlyphRun run);
  static DrawCommand DrawTextBlob(std::vector<uint8_t> blob_bytes,
                                  Point origin,
                                  Color fill);
  static DrawCommand DrawText(std::string value, Point origin, Color fill,
                              float font_size);
  static DrawCommand Diagnostic(std::string message);
};

using DrawCommandList = std::vector<DrawCommand>;

const char* ToString(DrawCommandType type);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_H_
