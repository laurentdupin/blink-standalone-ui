#include "html_css_renderer/retained_scene.h"

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

namespace html_css_renderer {
namespace {

uint64_t HashCombine(uint64_t seed, uint64_t value) {
  return seed ^ (value + 0x9e3779b97f4a7c15ull + (seed << 6) + (seed >> 2));
}

uint64_t HashFloat(float value) {
  static_assert(sizeof(float) == sizeof(uint32_t));
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

uint64_t HashString(const std::string& value) {
  uint64_t hash = 1469598103934665603ull;
  for (const char c : value) {
    hash ^= static_cast<unsigned char>(c);
    hash *= 1099511628211ull;
  }
  return hash;
}

uint64_t HashRect(Rect rect) {
  uint64_t hash = 0;
  hash = HashCombine(hash, HashFloat(rect.x));
  hash = HashCombine(hash, HashFloat(rect.y));
  hash = HashCombine(hash, HashFloat(rect.width));
  hash = HashCombine(hash, HashFloat(rect.height));
  return hash;
}

uint64_t HashMatrix(Matrix4 matrix) {
  uint64_t hash = 0;
  for (const float value : matrix.values) {
    hash = HashCombine(hash, HashFloat(value));
  }
  return hash;
}

uint64_t HashPropertyState(PaintPropertyStateSnapshot state) {
  uint64_t hash = state.state_hash;
  hash = HashCombine(hash, HashMatrix(state.transform_to_root));
  hash = HashCombine(hash, state.transform_is_2d ? 1u : 0u);
  hash = HashCombine(hash, state.transform_has_perspective ? 1u : 0u);
  hash = HashCombine(hash, state.transform_has_non_translation ? 1u : 0u);
  hash = HashCombine(hash, state.transform_node_id);
  hash = HashCombine(hash, state.transform_parent_id);
  hash = HashCombine(hash, state.transform_chain_depth);
  hash = HashCombine(hash, state.has_clip_rect ? 1u : 0u);
  if (state.has_clip_rect) {
    hash = HashCombine(hash, HashRect(state.clip_rect));
  }
  hash = HashCombine(hash, state.clip_node_id);
  hash = HashCombine(hash, state.clip_parent_id);
  hash = HashCombine(hash, state.clip_local_transform_id);
  hash = HashCombine(hash, state.clip_chain_depth);
  hash = HashCombine(hash, state.clip_has_rounded_clip ? 1u : 0u);
  hash = HashCombine(hash, state.clip_has_path_clip ? 1u : 0u);
  hash = HashCombine(hash, state.effect_node_id);
  hash = HashCombine(hash, state.effect_parent_id);
  hash = HashCombine(hash, state.effect_chain_depth);
  hash = HashCombine(hash, HashFloat(state.effect_opacity));
  hash = HashCombine(hash, state.effect_has_non_default_opacity ? 1u : 0u);
  hash = HashCombine(hash, state.effect_has_filter ? 1u : 0u);
  hash = HashCombine(hash, state.effect_has_backdrop_filter ? 1u : 0u);
  hash = HashCombine(hash, state.effect_has_blend_mode ? 1u : 0u);
  hash = HashCombine(hash, state.effect_output_clip_id);
  hash = HashCombine(hash, state.scroll_node_id);
  hash = HashCombine(hash, state.scroll_parent_id);
  hash = HashCombine(hash, state.has_scroll_offset ? 1u : 0u);
  hash = HashCombine(hash, HashFloat(state.scroll_offset_x));
  hash = HashCombine(hash, HashFloat(state.scroll_offset_y));
  hash = HashCombine(hash, HashRect(state.scroll_container_rect));
  hash = HashCombine(hash, HashRect(state.scroll_contents_rect));
  return hash;
}

uint64_t HashColor(Color color) {
  uint64_t hash = 0;
  hash = HashCombine(hash, HashFloat(color.r));
  hash = HashCombine(hash, HashFloat(color.g));
  hash = HashCombine(hash, HashFloat(color.b));
  hash = HashCombine(hash, HashFloat(color.a));
  return hash;
}

uint64_t HashCommandContent(const DrawCommand& command) {
  uint64_t hash = static_cast<uint64_t>(command.type);
  hash = HashCombine(hash, HashRect(command.rect));
  hash = HashCombine(hash, HashColor(command.color));
  hash = HashCombine(hash, HashFloat(command.stroke_width));
  hash = HashCombine(hash, HashFloat(command.opacity));
  hash = HashCombine(hash, HashString(command.text));
  hash = HashCombine(hash, HashString(command.path_data));
  hash = HashCombine(hash, HashString(command.resource_id));
  hash = HashCombine(hash, HashString(command.glyph_run.font_id));
  hash = HashCombine(hash, HashFloat(command.glyph_run.font_size));
  for (const uint32_t glyph_id : command.glyph_run.glyph_ids) {
    hash = HashCombine(hash, glyph_id);
  }
  for (const Point position : command.glyph_run.positions) {
    hash = HashCombine(hash, HashFloat(position.x));
    hash = HashCombine(hash, HashFloat(position.y));
  }
  return hash;
}

uint64_t HashCommandResources(const DrawCommand& command) {
  uint64_t hash = HashString(command.resource_id);
  hash = HashCombine(hash, HashString(command.glyph_run.font_id));
  return hash;
}

bool SameRect(Rect a, Rect b) {
  return a.x == b.x && a.y == b.y && a.width == b.width &&
         a.height == b.height;
}

bool IsEmpty(Rect rect) {
  return rect.width <= 0.0f || rect.height <= 0.0f;
}

bool Intersects(Rect a, Rect b) {
  if (IsEmpty(a) || IsEmpty(b)) {
    return false;
  }
  return a.x < b.x + b.width && a.x + a.width > b.x &&
         a.y < b.y + b.height && a.y + a.height > b.y;
}

Point MapPoint(const Matrix4& matrix, Point point) {
  return Point{
      matrix.values[0] * point.x + matrix.values[4] * point.y +
          matrix.values[12],
      matrix.values[1] * point.x + matrix.values[5] * point.y +
          matrix.values[13],
  };
}

Rect UnionRects(Rect a, Rect b) {
  const float left = std::min(a.x, b.x);
  const float top = std::min(a.y, b.y);
  const float right = std::max(a.x + a.width, b.x + b.width);
  const float bottom = std::max(a.y + a.height, b.y + b.height);
  return Rect{left, top, std::max(0.0f, right - left),
              std::max(0.0f, bottom - top)};
}

Rect IntersectRects(Rect a, Rect b) {
  const float left = std::max(a.x, b.x);
  const float top = std::max(a.y, b.y);
  const float right = std::min(a.x + a.width, b.x + b.width);
  const float bottom = std::min(a.y + a.height, b.y + b.height);
  return Rect{left, top, std::max(0.0f, right - left),
              std::max(0.0f, bottom - top)};
}

Rect MapRectConservatively(Rect rect,
                           const PaintPropertyStateSnapshot& property_state,
                           Rect viewport) {
  if (!property_state.transform_is_2d ||
      property_state.transform_has_perspective) {
    return viewport;
  }
  const Point p0 = MapPoint(property_state.transform_to_root,
                            Point{rect.x, rect.y});
  const Point p1 = MapPoint(property_state.transform_to_root,
                            Point{rect.x + rect.width, rect.y});
  const Point p2 = MapPoint(property_state.transform_to_root,
                            Point{rect.x + rect.width, rect.y + rect.height});
  const Point p3 = MapPoint(property_state.transform_to_root,
                            Point{rect.x, rect.y + rect.height});
  const float left = std::min(std::min(p0.x, p1.x), std::min(p2.x, p3.x));
  const float top = std::min(std::min(p0.y, p1.y), std::min(p2.y, p3.y));
  const float right = std::max(std::max(p0.x, p1.x), std::max(p2.x, p3.x));
  const float bottom = std::max(std::max(p0.y, p1.y), std::max(p2.y, p3.y));
  Rect mapped{left, top, std::max(0.0f, right - left),
              std::max(0.0f, bottom - top)};
  if (property_state.has_clip_rect) {
    mapped = IntersectRects(mapped, property_state.clip_rect);
  }
  return IntersectRects(mapped, viewport);
}

Rect Translate(Rect rect, Point delta) {
  rect.x += delta.x;
  rect.y += delta.y;
  return rect;
}

void RecordChange(RetainedSceneDiff& diff, RetainedChunkDiff chunk_diff) {
  switch (chunk_diff.kind) {
    case RetainedChunkChangeKind::kRetained:
      ++diff.retained_count;
      break;
    case RetainedChunkChangeKind::kAdded:
      ++diff.added_count;
      break;
    case RetainedChunkChangeKind::kRemoved:
      ++diff.removed_count;
      break;
    case RetainedChunkChangeKind::kMoved:
      ++diff.moved_count;
      break;
    case RetainedChunkChangeKind::kPresentationChanged:
      ++diff.presentation_changed_count;
      break;
    case RetainedChunkChangeKind::kContentChanged:
      ++diff.content_changed_count;
      break;
  }
  diff.chunks.push_back(std::move(chunk_diff));
}

}  // namespace

RetainedPaintChunk MakeRetainedPaintChunk(std::string key,
                                          RetainedChunkKind kind,
                                          Rect bounds,
                                          DrawCommandList commands) {
  return MakeRetainedPaintChunk(std::move(key), kind, bounds,
                                PaintPropertyStateSnapshot{},
                                std::move(commands));
}

RetainedPaintChunk MakeRetainedPaintChunk(
    std::string key,
    RetainedChunkKind kind,
    Rect bounds,
    PaintPropertyStateSnapshot property_state,
    DrawCommandList commands) {
  RetainedPaintChunk chunk;
  chunk.key = std::move(key);
  chunk.stable_key = chunk.key;
  chunk.chunk_id_string = chunk.key;
  chunk.kind = kind;
  chunk.bounds = bounds;
  chunk.placement_bounds = bounds;
  chunk.property_state = property_state;
  if (chunk.property_state.state_hash == 0) {
    chunk.property_state.state_hash = HashPropertyState(chunk.property_state);
  }
  chunk.commands = std::move(commands);
  for (const DrawCommand& command : chunk.commands) {
    chunk.content_hash = HashCombine(chunk.content_hash,
                                     HashCommandContent(command));
    chunk.resource_hash = HashCombine(chunk.resource_hash,
                                      HashCommandResources(command));
  }
  chunk.content_hash = HashCombine(chunk.content_hash, HashRect(chunk.bounds));
  chunk.content_hash = HashCombine(chunk.content_hash,
                                   HashString(chunk.element_id));
  chunk.resource_hash = HashCombine(chunk.resource_hash,
                                    HashString(chunk.element_id));
  return chunk;
}

RetainedScene MakeSingleChunkScene(std::string key,
                                   Rect bounds,
                                   DrawCommandList commands) {
  RetainedScene scene;
  scene.chunks.push_back(MakeRetainedPaintChunk(
      std::move(key), RetainedChunkKind::kDocument, bounds,
      std::move(commands)));
  return scene;
}

RetainedScene MakeRetainedSceneFromPaintArtifact(
    const PaintArtifact& paint_artifact,
    const PaintTranslator& translator) {
  RetainedScene scene;
  for (const PaintArtifactChunk& artifact_chunk : paint_artifact.chunks) {
    PaintTranslationResult translated =
        translator.TranslatePaintRecord(artifact_chunk.paint_record_ops);
    scene.chunks.push_back(MakeRetainedPaintChunk(
        artifact_chunk.chunk_id, RetainedChunkKind::kDocument,
        artifact_chunk.bounds, std::move(translated.draw_commands)));
  }
  return scene;
}

RetainedSceneDiff DiffRetainedScenes(const RetainedScene& current,
                                     const RetainedScene* previous) {
  RetainedSceneDiff diff;
  std::unordered_map<std::string, const RetainedPaintChunk*> previous_by_key;
  if (previous) {
    for (const RetainedPaintChunk& chunk : previous->chunks) {
      previous_by_key[chunk.key] = &chunk;
    }
  }

  for (const RetainedPaintChunk& current_chunk : current.chunks) {
    const auto found = previous_by_key.find(current_chunk.key);
    if (found == previous_by_key.end()) {
      RecordChange(diff, RetainedChunkDiff{
                             current_chunk.key,
                             RetainedChunkChangeKind::kAdded,
                             std::nullopt,
                             current_chunk.placement_bounds,
                         });
      continue;
    }

    const RetainedPaintChunk& previous_chunk = *found->second;
    RetainedChunkChangeKind kind = RetainedChunkChangeKind::kRetained;
    if (current_chunk.content_hash != previous_chunk.content_hash ||
        current_chunk.resource_hash != previous_chunk.resource_hash) {
      kind = RetainedChunkChangeKind::kContentChanged;
    } else if (current_chunk.property_state.state_hash !=
               previous_chunk.property_state.state_hash) {
      kind = RetainedChunkChangeKind::kPresentationChanged;
    } else if (!SameRect(current_chunk.placement_bounds,
                         previous_chunk.placement_bounds)) {
      kind = RetainedChunkChangeKind::kMoved;
    } else if (current_chunk.ignores_scroll_offset !=
               previous_chunk.ignores_scroll_offset) {
      kind = RetainedChunkChangeKind::kPresentationChanged;
    }

    RecordChange(diff, RetainedChunkDiff{
                           current_chunk.key,
                           kind,
                           previous_chunk.placement_bounds,
                           current_chunk.placement_bounds,
                       });
    previous_by_key.erase(found);
  }

  for (const auto& entry : previous_by_key) {
    RecordChange(diff, RetainedChunkDiff{
                           entry.first,
                           RetainedChunkChangeKind::kRemoved,
                           entry.second->placement_bounds,
                           std::nullopt,
                       });
  }

  return diff;
}

PresentationUpdatePlan PlanPresentationUpdate(const RetainedScene& current,
                                              const RetainedScene* previous,
                                              Size viewport,
                                              Point current_scroll_offset,
                                              Point previous_scroll_offset) {
  PresentationUpdatePlan plan;
  plan.viewport_bounds = Rect{0.0f, 0.0f, viewport.width, viewport.height};
  plan.scroll_translation_delta =
      Point{previous_scroll_offset.x - current_scroll_offset.x,
            previous_scroll_offset.y - current_scroll_offset.y};
  plan.allows_scroll_translation_reuse =
      previous != nullptr &&
      (plan.scroll_translation_delta.x != 0.0f ||
       plan.scroll_translation_delta.y != 0.0f);

  const RetainedSceneDiff diff = DiffRetainedScenes(current, previous);
  plan.requires_full_redraw = previous == nullptr || diff.added_count > 0 ||
                              diff.removed_count > 0 ||
                              diff.content_changed_count > 0 ||
                              diff.presentation_changed_count > 0;

  for (const RetainedChunkDiff& chunk_diff : diff.chunks) {
    PresentationChunkUpdate update;
    update.key = chunk_diff.key;
    update.change_kind = chunk_diff.kind;
    update.previous_bounds = chunk_diff.previous_bounds;
    update.current_bounds = chunk_diff.current_bounds;
    update.requires_placement_update =
        chunk_diff.kind == RetainedChunkChangeKind::kMoved ||
        chunk_diff.kind == RetainedChunkChangeKind::kAdded ||
        chunk_diff.kind == RetainedChunkChangeKind::kRemoved;
    update.requires_redraw =
        chunk_diff.kind == RetainedChunkChangeKind::kAdded ||
        chunk_diff.kind == RetainedChunkChangeKind::kRemoved ||
        chunk_diff.kind == RetainedChunkChangeKind::kContentChanged ||
        chunk_diff.kind == RetainedChunkChangeKind::kPresentationChanged;

    if (plan.allows_scroll_translation_reuse &&
        chunk_diff.kind == RetainedChunkChangeKind::kRetained &&
        chunk_diff.current_bounds &&
        Intersects(*chunk_diff.current_bounds, plan.viewport_bounds)) {
      const Rect translated =
          Translate(*chunk_diff.current_bounds, plan.scroll_translation_delta);
      update.requires_redraw = !Intersects(translated, plan.viewport_bounds);
    }

    if (update.requires_redraw) {
      const RetainedPaintChunk* previous_chunk = nullptr;
      const RetainedPaintChunk* current_chunk = nullptr;
      if (previous) {
        for (const RetainedPaintChunk& candidate : previous->chunks) {
          if (candidate.key == chunk_diff.key) {
            previous_chunk = &candidate;
            break;
          }
        }
      }
      for (const RetainedPaintChunk& candidate : current.chunks) {
        if (candidate.key == chunk_diff.key) {
          current_chunk = &candidate;
          break;
        }
      }
      if (chunk_diff.previous_bounds) {
        plan.dirty_rects.push_back(MapRectConservatively(
            *chunk_diff.previous_bounds,
            previous_chunk ? previous_chunk->property_state
                           : PaintPropertyStateSnapshot{},
            plan.viewport_bounds));
      }
      if (chunk_diff.current_bounds) {
        plan.dirty_rects.push_back(MapRectConservatively(
            *chunk_diff.current_bounds,
            current_chunk ? current_chunk->property_state
                          : PaintPropertyStateSnapshot{},
            plan.viewport_bounds));
      }
    }
    plan.chunk_updates.push_back(std::move(update));
  }

  if (plan.dirty_rects.empty() && !plan.requires_full_redraw) {
    return plan;
  }

  if (plan.requires_full_redraw) {
    plan.dirty_rects.clear();
    plan.dirty_rects.push_back(plan.viewport_bounds);
  }
  return plan;
}

DrawCommandList FlattenRetainedScene(const RetainedScene& scene) {
  DrawCommandList commands;
  for (const RetainedPaintChunk& chunk : scene.chunks) {
    commands.insert(commands.end(), chunk.commands.begin(),
                    chunk.commands.end());
  }
  return commands;
}

RenderFrame BuildRenderFrame(const RetainedScene& scene,
                             const LoadCommandList& load_commands,
                             const PresentationUpdatePlan& plan) {
  RenderFrame frame;
  frame.damage_rects = plan.dirty_rects;
  frame.requires_full_redraw = plan.requires_full_redraw;
  for (const Rect dirty : frame.damage_rects) {
    frame.damage_bounds = UnionRectBounds(frame.damage_bounds, dirty);
  }

  frame.resource_commands.reserve(load_commands.size());
  for (const LoadCommand& command : load_commands) {
    frame.resource_commands.push_back(
        ResourceCommand::FromLoadCommand(command));
  }

  for (const RetainedPaintChunk& retained_chunk : scene.chunks) {
    SceneChunk chunk;
    chunk.debug_index = retained_chunk.debug_index;
    chunk.stable_key = retained_chunk.stable_key.empty()
                           ? retained_chunk.key
                           : retained_chunk.stable_key;
    chunk.chunk_id = retained_chunk.key;
    chunk.bounds = retained_chunk.placement_bounds;
    chunk.property_state = retained_chunk.property_state;
    chunk.content_hash = retained_chunk.content_hash;
    chunk.resource_hash = retained_chunk.resource_hash;
    chunk.commands = retained_chunk.commands;
    chunk.retained_from_previous_frame = true;
    for (const PresentationChunkUpdate& update : plan.chunk_updates) {
      if (update.key == retained_chunk.key) {
        chunk.retained_from_previous_frame =
            update.change_kind == RetainedChunkChangeKind::kRetained ||
            update.change_kind == RetainedChunkChangeKind::kMoved;
        if (update.requires_redraw && update.current_bounds) {
          chunk.damage_bounds =
              UnionRectBounds(chunk.damage_bounds, *update.current_bounds);
        }
        if (update.requires_redraw && update.previous_bounds) {
          chunk.damage_bounds =
              UnionRectBounds(chunk.damage_bounds, *update.previous_bounds);
        }
        break;
      }
    }
    if (chunk.damage_bounds.width <= 0.0f ||
        chunk.damage_bounds.height <= 0.0f) {
      chunk.damage_bounds = frame.requires_full_redraw ? chunk.bounds : Rect{};
    }

    frame.scene_commands.push_back(
        SceneCommand::BeginChunk(chunk.chunk_id, chunk.bounds));
    for (const DrawCommand& command : chunk.commands) {
      frame.scene_commands.push_back(SceneCommand::Draw(command));
    }
    frame.scene_commands.push_back(SceneCommand::EndChunk(chunk.chunk_id));
    frame.scene_chunks.push_back(std::move(chunk));
  }

  RenderPass root_pass;
  root_pass.pass_id = "root";
  root_pass.viewport = plan.viewport_bounds;
  root_pass.first_scene_command = 0;
  root_pass.scene_command_count = frame.scene_commands.size();
  root_pass.clear_before_render = frame.requires_full_redraw;
  frame.render_passes.push_back(root_pass);
  return frame;
}

Rect UnionRectBounds(Rect a, Rect b) {
  if (IsEmpty(a)) {
    return b;
  }
  if (IsEmpty(b)) {
    return a;
  }
  const float left = std::min(a.x, b.x);
  const float top = std::min(a.y, b.y);
  const float right = std::max(a.x + a.width, b.x + b.width);
  const float bottom = std::max(a.y + a.height, b.y + b.height);
  return Rect{left, top, right - left, bottom - top};
}

}  // namespace html_css_renderer
