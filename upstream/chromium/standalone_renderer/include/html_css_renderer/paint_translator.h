#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_PAINT_TRANSLATOR_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_PAINT_TRANSLATOR_H_

#include <string>
#include <vector>

#include "html_css_renderer/draw_command.h"

namespace html_css_renderer {

enum class PaintOpType {
  kSave,
  kRestore,
  kTransform,
  kClipRect,
  kSaveLayer,
  kFillRect,
  kStrokeRect,
  kFillPath,
  kDrawImage,
  kDrawGlyphRun,
  kDrawText,
};

enum class PaintRecordOpType {
  kSave,
  kRestore,
  kConcat,
  kClipRect,
  kSaveLayer,
  kDrawRect,
  kDrawIRect,
  kDrawPath,
  kDrawImageRect,
  kDrawTextBlob,
  kUnsupported,
};

struct PaintOp {
  PaintOpType type = PaintOpType::kFillRect;
  Rect rect;
  Matrix4 transform;
  Color color;
  float stroke_width = 1.0f;
  float opacity = 1.0f;
  std::string text;
  std::string path_data;
  std::string resource_id;
  GlyphRun glyph_run;
};

struct PaintRecordOp {
  PaintRecordOpType type = PaintRecordOpType::kUnsupported;
  Rect rect;
  Rect source_rect;
  Matrix4 matrix;
  Color color;
  float stroke_width = 1.0f;
  float opacity = 1.0f;
  std::string path_data;
  std::string resource_id;
  GlyphRun glyph_run;
  std::string source_debug_name;
};

struct PaintArtifactChunk {
  std::string chunk_id;
  Rect bounds;
  std::vector<PaintRecordOp> paint_record_ops;
};

struct PaintArtifact {
  std::vector<PaintArtifactChunk> chunks;
};

struct PaintTranslationResult {
  DrawCommandList draw_commands;
  Rect damage_bounds;
  std::vector<std::string> diagnostics;
};

class PaintTranslator {
 public:
  PaintTranslationResult Translate(const std::vector<PaintOp>& paint_ops) const;
  PaintTranslationResult TranslatePaintRecord(
      const std::vector<PaintRecordOp>& paint_record_ops) const;
  PaintTranslationResult TranslatePaintArtifact(
      const PaintArtifact& paint_artifact) const;
};

PaintOp PaintSave();
PaintOp PaintRestore();
PaintOp PaintTransform(Matrix4 matrix);
PaintOp PaintClipRect(Rect rect);
PaintOp PaintSaveLayer(Rect bounds, float opacity);
PaintOp PaintFillRect(Rect rect, Color color);
PaintOp PaintStrokeRect(Rect rect, Color color, float stroke_width);
PaintOp PaintFillPath(std::string path_data, Color color);
PaintOp PaintDrawImage(std::string resource_id, Rect destination);
PaintOp PaintDrawGlyphRun(GlyphRun glyph_run);
PaintOp PaintDrawText(std::string text,
                      Point origin,
                      Color color,
                      float font_size);

PaintRecordOp PaintRecordSave();
PaintRecordOp PaintRecordRestore();
PaintRecordOp PaintRecordConcat(Matrix4 matrix);
PaintRecordOp PaintRecordClipRect(Rect rect);
PaintRecordOp PaintRecordSaveLayer(Rect bounds, float opacity);
PaintRecordOp PaintRecordDrawRect(Rect rect, Color color);
PaintRecordOp PaintRecordDrawPath(std::string path_data, Color color);
PaintRecordOp PaintRecordDrawImageRect(std::string resource_id,
                                       Rect source,
                                       Rect destination);
PaintRecordOp PaintRecordDrawTextBlob(GlyphRun glyph_run);
PaintRecordOp PaintRecordUnsupported(std::string source_debug_name);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_PAINT_TRANSLATOR_H_
