#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RETAINED_SCENE_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RETAINED_SCENE_H_

#include <cstdint>
#include <optional>
#include <string>
#include <vector>

#include "html_css_renderer/draw_command.h"
#include "html_css_renderer/paint_translator.h"
#include "html_css_renderer/render_frame.h"

namespace html_css_renderer {

enum class RetainedChunkKind {
  kDocument,
  kElement,
  kText,
  kImage,
  kEffect,
  kAnonymous,
};

enum class RetainedChunkChangeKind {
  kRetained,
  kAdded,
  kRemoved,
  kMoved,
  kPresentationChanged,
  kContentChanged,
};

struct RetainedPaintChunk {
  std::string key;
  RetainedChunkKind kind = RetainedChunkKind::kAnonymous;
  Rect bounds;
  Rect placement_bounds;
  std::string element_id;
  bool ignores_scroll_offset = false;
  DrawCommandList commands;
  uint64_t content_hash = 0;
  uint64_t resource_hash = 0;
};

struct RetainedScene {
  std::vector<RetainedPaintChunk> chunks;
};

struct RetainedChunkDiff {
  std::string key;
  RetainedChunkChangeKind kind = RetainedChunkChangeKind::kRetained;
  std::optional<Rect> previous_bounds;
  std::optional<Rect> current_bounds;
};

struct RetainedSceneDiff {
  std::vector<RetainedChunkDiff> chunks;
  int retained_count = 0;
  int added_count = 0;
  int removed_count = 0;
  int moved_count = 0;
  int presentation_changed_count = 0;
  int content_changed_count = 0;
};

struct PresentationChunkUpdate {
  std::string key;
  RetainedChunkChangeKind change_kind = RetainedChunkChangeKind::kRetained;
  bool requires_redraw = false;
  bool requires_placement_update = false;
  std::optional<Rect> previous_bounds;
  std::optional<Rect> current_bounds;
};

struct PresentationUpdatePlan {
  bool requires_full_redraw = true;
  bool allows_scroll_translation_reuse = false;
  Point scroll_translation_delta;
  Rect viewport_bounds;
  std::vector<Rect> dirty_rects;
  std::vector<PresentationChunkUpdate> chunk_updates;
};

RetainedPaintChunk MakeRetainedPaintChunk(std::string key,
                                          RetainedChunkKind kind,
                                          Rect bounds,
                                          DrawCommandList commands);
RetainedScene MakeSingleChunkScene(std::string key,
                                   Rect bounds,
                                   DrawCommandList commands);
RetainedScene MakeRetainedSceneFromPaintArtifact(
    const PaintArtifact& paint_artifact,
    const PaintTranslator& translator);
RetainedSceneDiff DiffRetainedScenes(const RetainedScene& current,
                                     const RetainedScene* previous);
PresentationUpdatePlan PlanPresentationUpdate(const RetainedScene& current,
                                              const RetainedScene* previous,
                                              Size viewport,
                                              Point current_scroll_offset,
                                              Point previous_scroll_offset);
DrawCommandList FlattenRetainedScene(const RetainedScene& scene);
RenderFrame BuildRenderFrame(const RetainedScene& scene,
                             const LoadCommandList& load_commands,
                             const PresentationUpdatePlan& plan);
Rect UnionRectBounds(Rect a, Rect b);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RETAINED_SCENE_H_
