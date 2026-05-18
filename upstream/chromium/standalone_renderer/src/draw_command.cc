#include "html_css_renderer/draw_command.h"

#include <utility>

namespace html_css_renderer {

Color Color::Rgba(float red, float green, float blue, float alpha) {
  return Color{red, green, blue, alpha};
}

DrawCommand DrawCommand::Save() {
  DrawCommand command;
  command.type = DrawCommandType::kSave;
  return command;
}

DrawCommand DrawCommand::Restore() {
  DrawCommand command;
  command.type = DrawCommandType::kRestore;
  return command;
}

DrawCommand DrawCommand::Transform(Matrix4 matrix) {
  DrawCommand command;
  command.type = DrawCommandType::kTransform;
  command.transform = matrix;
  return command;
}

DrawCommand DrawCommand::ClipRect(Rect clip) {
  DrawCommand command;
  command.type = DrawCommandType::kClipRect;
  command.rect = clip;
  return command;
}

DrawCommand DrawCommand::ClipRRect(Rect clip, float radius_x, float radius_y) {
  DrawCommand command;
  command.type = DrawCommandType::kClipRRect;
  command.rect = clip;
  command.radius_x = radius_x;
  command.radius_y = radius_y;
  command.corner_radii = {
      Point{radius_x, radius_y},
      Point{radius_x, radius_y},
      Point{radius_x, radius_y},
      Point{radius_x, radius_y},
  };
  command.clip_difference = false;
  return command;
}

DrawCommand DrawCommand::ClipRRect(Rect clip,
                                   std::array<Point, 4> corner_radii,
                                   bool difference) {
  DrawCommand command;
  command.type = DrawCommandType::kClipRRect;
  command.rect = clip;
  command.corner_radii = corner_radii;
  command.radius_x = corner_radii[0].x;
  command.radius_y = corner_radii[0].y;
  command.clip_difference = difference;
  return command;
}

DrawCommand DrawCommand::ClipPath(std::vector<uint8_t> path_bytes,
                                  bool difference) {
  DrawCommand command;
  command.type = DrawCommandType::kClipPath;
  command.path_bytes = std::move(path_bytes);
  command.clip_difference = difference;
  return command;
}

DrawCommand DrawCommand::SaveLayer(Rect bounds, float opacity) {
  DrawCommand command;
  command.type = DrawCommandType::kSaveLayer;
  command.rect = bounds;
  command.opacity = opacity;
  return command;
}

DrawCommand DrawCommand::FillRect(Rect bounds, Color fill) {
  DrawCommand command;
  command.type = DrawCommandType::kFillRect;
  command.rect = bounds;
  command.color = fill;
  return command;
}

DrawCommand DrawCommand::StrokeRect(Rect bounds, Color stroke, float width) {
  DrawCommand command;
  command.type = DrawCommandType::kStrokeRect;
  command.rect = bounds;
  command.color = stroke;
  command.stroke_width = width;
  return command;
}

DrawCommand DrawCommand::FillRectShader(Rect bounds,
                                        std::vector<uint8_t> shader_bytes,
                                        Color modulation) {
  DrawCommand command;
  command.type = DrawCommandType::kFillRectShader;
  command.rect = bounds;
  command.shader_bytes = std::move(shader_bytes);
  command.color = modulation;
  return command;
}

DrawCommand DrawCommand::FillRRect(Rect bounds,
                                   float radius_x,
                                   float radius_y,
                                   Color fill) {
  DrawCommand command;
  command.type = DrawCommandType::kFillRRect;
  command.rect = bounds;
  command.radius_x = radius_x;
  command.radius_y = radius_y;
  command.color = fill;
  return command;
}

DrawCommand DrawCommand::FillRRectShader(Rect bounds,
                                         float radius_x,
                                         float radius_y,
                                         std::vector<uint8_t> shader_bytes,
                                         Color modulation) {
  DrawCommand command;
  command.type = DrawCommandType::kFillRRectShader;
  command.rect = bounds;
  command.radius_x = radius_x;
  command.radius_y = radius_y;
  command.shader_bytes = std::move(shader_bytes);
  command.color = modulation;
  return command;
}

DrawCommand DrawCommand::StrokeRRect(Rect bounds,
                                     float radius_x,
                                     float radius_y,
                                     Color stroke,
                                     float width) {
  DrawCommand command;
  command.type = DrawCommandType::kStrokeRRect;
  command.rect = bounds;
  command.radius_x = radius_x;
  command.radius_y = radius_y;
  command.color = stroke;
  command.stroke_width = width;
  return command;
}

DrawCommand DrawCommand::FillPath(std::vector<uint8_t> path_bytes,
                                  Color fill,
                                  float stroke_width,
                                  std::vector<uint8_t> shader_bytes) {
  DrawCommand command;
  command.type = DrawCommandType::kFillPath;
  command.path_bytes = std::move(path_bytes);
  command.color = fill;
  command.stroke_width = stroke_width;
  command.shader_bytes = std::move(shader_bytes);
  return command;
}

DrawCommand DrawCommand::DrawImage(std::string id, Rect destination) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawImage;
  command.resource_id = std::move(id);
  command.rect = destination;
  return command;
}

DrawCommand DrawCommand::DrawImageRect(std::string id,
                                       Rect source,
                                       Rect destination,
                                       std::string sampling_options,
                                       std::string blend_mode,
                                       std::string src_rect_constraint,
                                       float image_alpha,
                                       std::string paint_flags_summary) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawImageRect;
  command.resource_id = std::move(id);
  command.source_rect = source;
  command.rect = destination;
  command.sampling_options = std::move(sampling_options);
  command.blend_mode = std::move(blend_mode);
  command.src_rect_constraint = std::move(src_rect_constraint);
  command.image_alpha = image_alpha;
  command.paint_flags_summary = std::move(paint_flags_summary);
  return command;
}

DrawCommand DrawCommand::DrawGlyphRun(GlyphRun run) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawGlyphRun;
  command.glyph_run = std::move(run);
  return command;
}

DrawCommand DrawCommand::DrawTextBlob(std::vector<uint8_t> blob_bytes,
                                      Point origin,
                                      Color fill) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawTextBlob;
  command.text_blob_bytes = std::move(blob_bytes);
  command.rect = Rect{origin.x, origin.y, 0.0f, 0.0f};
  command.color = fill;
  return command;
}

DrawCommand DrawCommand::DrawText(std::string value,
                                  Point origin,
                                  Color fill,
                                  float font_size) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawText;
  command.text = std::move(value);
  command.rect = Rect{origin.x, origin.y, 0.0f, font_size};
  command.color = fill;
  command.glyph_run.font_size = font_size;
  return command;
}

DrawCommand DrawCommand::Diagnostic(std::string message) {
  DrawCommand command;
  command.type = DrawCommandType::kDiagnostic;
  command.text = std::move(message);
  return command;
}

const char* ToString(DrawCommandType type) {
  switch (type) {
    case DrawCommandType::kSave:
      return "Save";
    case DrawCommandType::kRestore:
      return "Restore";
    case DrawCommandType::kTransform:
      return "Transform";
    case DrawCommandType::kClipRect:
      return "ClipRect";
    case DrawCommandType::kClipRRect:
      return "ClipRRect";
    case DrawCommandType::kClipPath:
      return "ClipPath";
    case DrawCommandType::kSaveLayer:
      return "SaveLayer";
    case DrawCommandType::kFillRect:
      return "FillRect";
    case DrawCommandType::kStrokeRect:
      return "StrokeRect";
    case DrawCommandType::kFillRectShader:
      return "FillRectShader";
    case DrawCommandType::kFillRRect:
      return "FillRRect";
    case DrawCommandType::kStrokeRRect:
      return "StrokeRRect";
    case DrawCommandType::kFillRRectShader:
      return "FillRRectShader";
    case DrawCommandType::kFillPath:
      return "FillPath";
    case DrawCommandType::kDrawImage:
      return "DrawImage";
    case DrawCommandType::kDrawImageRect:
      return "DrawImageRect";
    case DrawCommandType::kDrawGlyphRun:
      return "DrawGlyphRun";
    case DrawCommandType::kDrawTextBlob:
      return "DrawTextBlob";
    case DrawCommandType::kDrawText:
      return "DrawText";
    case DrawCommandType::kDiagnostic:
      return "Diagnostic";
  }
  return "Unknown";
}

}  // namespace html_css_renderer
