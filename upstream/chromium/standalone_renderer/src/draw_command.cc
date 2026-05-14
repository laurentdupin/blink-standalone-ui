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

DrawCommand DrawCommand::FillPath(std::string path_data, Color fill) {
  DrawCommand command;
  command.type = DrawCommandType::kFillPath;
  command.path_data = std::move(path_data);
  command.color = fill;
  return command;
}

DrawCommand DrawCommand::DrawImage(std::string id, Rect destination) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawImage;
  command.resource_id = std::move(id);
  command.rect = destination;
  return command;
}

DrawCommand DrawCommand::DrawGlyphRun(GlyphRun run) {
  DrawCommand command;
  command.type = DrawCommandType::kDrawGlyphRun;
  command.glyph_run = std::move(run);
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
    case DrawCommandType::kSaveLayer:
      return "SaveLayer";
    case DrawCommandType::kFillRect:
      return "FillRect";
    case DrawCommandType::kStrokeRect:
      return "StrokeRect";
    case DrawCommandType::kFillRRect:
      return "FillRRect";
    case DrawCommandType::kStrokeRRect:
      return "StrokeRRect";
    case DrawCommandType::kFillPath:
      return "FillPath";
    case DrawCommandType::kDrawImage:
      return "DrawImage";
    case DrawCommandType::kDrawGlyphRun:
      return "DrawGlyphRun";
    case DrawCommandType::kDrawText:
      return "DrawText";
    case DrawCommandType::kDiagnostic:
      return "Diagnostic";
  }
  return "Unknown";
}

}  // namespace html_css_renderer
