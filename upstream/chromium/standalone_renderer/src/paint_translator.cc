#include "html_css_renderer/paint_translator.h"

#include <algorithm>
#include <utility>

namespace html_css_renderer {
namespace {

bool IsDrawable(DrawCommandType type) {
  return type == DrawCommandType::kFillRect ||
         type == DrawCommandType::kStrokeRect ||
         type == DrawCommandType::kFillRRect ||
         type == DrawCommandType::kStrokeRRect ||
         type == DrawCommandType::kFillPath ||
         type == DrawCommandType::kDrawImage ||
         type == DrawCommandType::kDrawGlyphRun ||
         type == DrawCommandType::kDrawText;
}

Rect UnionRects(Rect a, Rect b) {
  if (a.width <= 0.0f || a.height <= 0.0f) {
    return b;
  }
  if (b.width <= 0.0f || b.height <= 0.0f) {
    return a;
  }

  const float left = std::min(a.x, b.x);
  const float top = std::min(a.y, b.y);
  const float right = std::max(a.x + a.width, b.x + b.width);
  const float bottom = std::max(a.y + a.height, b.y + b.height);
  return Rect{left, top, right - left, bottom - top};
}

Rect CommandBounds(const DrawCommand& command) {
  if (command.type == DrawCommandType::kDrawGlyphRun &&
      !command.glyph_run.positions.empty()) {
    Rect bounds{command.glyph_run.positions.front().x,
                command.glyph_run.positions.front().y,
                command.glyph_run.font_size,
                command.glyph_run.font_size};
    for (const auto& point : command.glyph_run.positions) {
      bounds = UnionRects(
          bounds,
          Rect{point.x, point.y, command.glyph_run.font_size,
               command.glyph_run.font_size});
    }
    return bounds;
  }
  return command.rect;
}

void AppendDiagnostic(PaintTranslationResult& result, std::string message) {
  result.diagnostics.push_back(message);
  result.draw_commands.push_back(DrawCommand::Diagnostic(std::move(message)));
}

}  // namespace

PaintTranslationResult PaintTranslator::Translate(
    const std::vector<PaintOp>& paint_ops) const {
  PaintTranslationResult result;
  int save_depth = 0;

  for (const auto& op : paint_ops) {
    DrawCommand command;
    switch (op.type) {
      case PaintOpType::kSave:
        ++save_depth;
        command = DrawCommand::Save();
        break;
      case PaintOpType::kRestore:
        if (save_depth == 0) {
          AppendDiagnostic(result, "ignored unmatched paint restore");
          continue;
        }
        --save_depth;
        command = DrawCommand::Restore();
        break;
      case PaintOpType::kTransform:
        command = DrawCommand::Transform(op.transform);
        break;
      case PaintOpType::kClipRect:
        command = DrawCommand::ClipRect(op.rect);
        break;
      case PaintOpType::kSaveLayer:
        ++save_depth;
        command = DrawCommand::SaveLayer(op.rect, op.opacity);
        break;
      case PaintOpType::kFillRect:
        command = DrawCommand::FillRect(op.rect, op.color);
        break;
      case PaintOpType::kStrokeRect:
        command = DrawCommand::StrokeRect(op.rect, op.color, op.stroke_width);
        break;
      case PaintOpType::kFillPath:
        command = DrawCommand::FillPath(op.path_data, op.color);
        break;
      case PaintOpType::kDrawImage:
        command = DrawCommand::DrawImage(op.resource_id, op.rect);
        break;
      case PaintOpType::kDrawGlyphRun:
        command = DrawCommand::DrawGlyphRun(op.glyph_run);
        break;
      case PaintOpType::kDrawText:
        command =
            DrawCommand::DrawText(op.text, Point{op.rect.x, op.rect.y},
                                  op.color, op.glyph_run.font_size);
        break;
    }

    if (IsDrawable(command.type)) {
      result.damage_bounds =
          UnionRects(result.damage_bounds, CommandBounds(command));
    }
    result.draw_commands.push_back(std::move(command));
  }

  while (save_depth > 0) {
    --save_depth;
    AppendDiagnostic(result, "auto-restored unbalanced paint save");
    result.draw_commands.push_back(DrawCommand::Restore());
  }

  return result;
}

PaintTranslationResult PaintTranslator::TranslatePaintRecord(
    const std::vector<PaintRecordOp>& paint_record_ops) const {
  std::vector<PaintOp> paint_ops;
  paint_ops.reserve(paint_record_ops.size());

  for (const auto& record_op : paint_record_ops) {
    switch (record_op.type) {
      case PaintRecordOpType::kSave:
        paint_ops.push_back(PaintSave());
        break;
      case PaintRecordOpType::kRestore:
        paint_ops.push_back(PaintRestore());
        break;
      case PaintRecordOpType::kConcat:
        paint_ops.push_back(PaintTransform(record_op.matrix));
        break;
      case PaintRecordOpType::kClipRect:
        paint_ops.push_back(PaintClipRect(record_op.rect));
        break;
      case PaintRecordOpType::kSaveLayer:
        paint_ops.push_back(PaintSaveLayer(record_op.rect, record_op.opacity));
        break;
      case PaintRecordOpType::kDrawRect:
      case PaintRecordOpType::kDrawIRect:
        paint_ops.push_back(PaintFillRect(record_op.rect, record_op.color));
        break;
      case PaintRecordOpType::kDrawPath:
        paint_ops.push_back(
            PaintFillPath(record_op.path_data, record_op.color));
        break;
      case PaintRecordOpType::kDrawImageRect:
        paint_ops.push_back(
            PaintDrawImage(record_op.resource_id, record_op.rect));
        break;
      case PaintRecordOpType::kDrawTextBlob:
        paint_ops.push_back(PaintDrawGlyphRun(record_op.glyph_run));
        break;
      case PaintRecordOpType::kUnsupported:
        break;
    }
  }

  PaintTranslationResult result = Translate(paint_ops);
  for (const auto& record_op : paint_record_ops) {
    if (record_op.type == PaintRecordOpType::kUnsupported) {
      AppendDiagnostic(
          result,
          "ignored unsupported paint record op: " + record_op.source_debug_name);
    }
  }
  return result;
}

PaintTranslationResult PaintTranslator::TranslatePaintArtifact(
    const PaintArtifact& paint_artifact) const {
  PaintTranslationResult result;
  for (const PaintArtifactChunk& chunk : paint_artifact.chunks) {
    PaintTranslationResult chunk_result =
        TranslatePaintRecord(chunk.paint_record_ops);
    result.damage_bounds =
        UnionRects(result.damage_bounds, chunk_result.damage_bounds);
    result.draw_commands.insert(result.draw_commands.end(),
                                chunk_result.draw_commands.begin(),
                                chunk_result.draw_commands.end());
    result.diagnostics.insert(result.diagnostics.end(),
                              chunk_result.diagnostics.begin(),
                              chunk_result.diagnostics.end());
  }
  result.diagnostics.push_back(
      "translated Blink paint artifact package: " +
      std::to_string(paint_artifact.chunks.size()) + " chunk(s)");
  return result;
}

PaintOp PaintSave() {
  PaintOp op;
  op.type = PaintOpType::kSave;
  return op;
}

PaintOp PaintRestore() {
  PaintOp op;
  op.type = PaintOpType::kRestore;
  return op;
}

PaintOp PaintTransform(Matrix4 matrix) {
  PaintOp op;
  op.type = PaintOpType::kTransform;
  op.transform = matrix;
  return op;
}

PaintOp PaintClipRect(Rect rect) {
  PaintOp op;
  op.type = PaintOpType::kClipRect;
  op.rect = rect;
  return op;
}

PaintOp PaintSaveLayer(Rect bounds, float opacity) {
  PaintOp op;
  op.type = PaintOpType::kSaveLayer;
  op.rect = bounds;
  op.opacity = opacity;
  return op;
}

PaintOp PaintFillRect(Rect rect, Color color) {
  PaintOp op;
  op.type = PaintOpType::kFillRect;
  op.rect = rect;
  op.color = color;
  return op;
}

PaintOp PaintStrokeRect(Rect rect, Color color, float stroke_width) {
  PaintOp op;
  op.type = PaintOpType::kStrokeRect;
  op.rect = rect;
  op.color = color;
  op.stroke_width = stroke_width;
  return op;
}

PaintOp PaintFillPath(std::string path_data, Color color) {
  PaintOp op;
  op.type = PaintOpType::kFillPath;
  op.path_data = std::move(path_data);
  op.color = color;
  return op;
}

PaintOp PaintDrawImage(std::string resource_id, Rect destination) {
  PaintOp op;
  op.type = PaintOpType::kDrawImage;
  op.resource_id = std::move(resource_id);
  op.rect = destination;
  return op;
}

PaintOp PaintDrawGlyphRun(GlyphRun glyph_run) {
  PaintOp op;
  op.type = PaintOpType::kDrawGlyphRun;
  op.glyph_run = std::move(glyph_run);
  return op;
}

PaintOp PaintDrawText(std::string text,
                      Point origin,
                      Color color,
                      float font_size) {
  PaintOp op;
  op.type = PaintOpType::kDrawText;
  op.text = std::move(text);
  op.rect = Rect{origin.x, origin.y, 0.0f, font_size};
  op.color = color;
  op.glyph_run.font_size = font_size;
  return op;
}

PaintRecordOp PaintRecordSave() {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kSave;
  return op;
}

PaintRecordOp PaintRecordRestore() {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kRestore;
  return op;
}

PaintRecordOp PaintRecordConcat(Matrix4 matrix) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kConcat;
  op.matrix = matrix;
  return op;
}

PaintRecordOp PaintRecordClipRect(Rect rect) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kClipRect;
  op.rect = rect;
  return op;
}

PaintRecordOp PaintRecordSaveLayer(Rect bounds, float opacity) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kSaveLayer;
  op.rect = bounds;
  op.opacity = opacity;
  return op;
}

PaintRecordOp PaintRecordDrawRect(Rect rect, Color color) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kDrawRect;
  op.rect = rect;
  op.color = color;
  return op;
}

PaintRecordOp PaintRecordDrawPath(std::string path_data, Color color) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kDrawPath;
  op.path_data = std::move(path_data);
  op.color = color;
  return op;
}

PaintRecordOp PaintRecordDrawImageRect(std::string resource_id,
                                       Rect source,
                                       Rect destination) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kDrawImageRect;
  op.resource_id = std::move(resource_id);
  op.source_rect = source;
  op.rect = destination;
  return op;
}

PaintRecordOp PaintRecordDrawTextBlob(GlyphRun glyph_run) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kDrawTextBlob;
  op.glyph_run = std::move(glyph_run);
  return op;
}

PaintRecordOp PaintRecordUnsupported(std::string source_debug_name) {
  PaintRecordOp op;
  op.type = PaintRecordOpType::kUnsupported;
  op.source_debug_name = std::move(source_debug_name);
  return op;
}

}  // namespace html_css_renderer
