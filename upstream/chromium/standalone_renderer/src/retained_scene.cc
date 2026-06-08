#include "html_css_renderer/retained_scene.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <functional>
#include <optional>
#include <string>
#include <unordered_set>
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

uint64_t HashColor(Color color);

uint64_t HashFilterOperation(const FilterOperationSnapshot& operation) {
  uint64_t hash = static_cast<uint64_t>(operation.kind);
  hash = HashCombine(hash, HashFloat(operation.amount));
  hash = HashCombine(hash, HashFloat(operation.offset.x));
  hash = HashCombine(hash, HashFloat(operation.offset.y));
  hash = HashCombine(hash, HashColor(operation.color));
  for (float value : operation.matrix) {
    hash = HashCombine(hash, HashFloat(value));
  }
  return hash;
}

bool NearlyEqual(float a, float b) {
  return std::fabs(a - b) <= 0.01f;
}

bool SameFilterOperations(
    const std::vector<FilterOperationSnapshot>& a,
    const std::vector<FilterOperationSnapshot>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i].kind != b[i].kind ||
        !NearlyEqual(a[i].amount, b[i].amount) ||
        !NearlyEqual(a[i].offset.x, b[i].offset.x) ||
        !NearlyEqual(a[i].offset.y, b[i].offset.y) ||
        !NearlyEqual(a[i].color.r, b[i].color.r) ||
        !NearlyEqual(a[i].color.g, b[i].color.g) ||
        !NearlyEqual(a[i].color.b, b[i].color.b) ||
        !NearlyEqual(a[i].color.a, b[i].color.a)) {
      return false;
    }
    for (size_t value_index = 0; value_index < a[i].matrix.size();
         ++value_index) {
      if (!NearlyEqual(a[i].matrix[value_index], b[i].matrix[value_index])) {
        return false;
      }
    }
  }
  return true;
}

bool NeedsGroupedOpacityLayer(const PaintPropertyStateSnapshot& state) {
  return state.effect_has_non_default_opacity && state.effect_opacity >= 0.0f &&
         state.effect_opacity < 1.0f;
}

bool HasSupportedEffectFilter(const PaintPropertyStateSnapshot& state) {
  return state.effect_has_filter && !state.effect_has_unsupported_filter &&
         !state.effect_filter_operations.empty();
}

bool NeedsGroupedEffectLayer(const PaintPropertyStateSnapshot& state) {
  return NeedsGroupedOpacityLayer(state) || HasSupportedEffectFilter(state);
}

bool SameEffectGroup(const PaintPropertyStateSnapshot& a,
                     const PaintPropertyStateSnapshot& b) {
  return NeedsGroupedEffectLayer(a) && NeedsGroupedEffectLayer(b) &&
         a.effect_node_id == b.effect_node_id &&
         NearlyEqual(a.effect_opacity, b.effect_opacity) &&
         SameFilterOperations(a.effect_filter_operations,
                              b.effect_filter_operations);
}

constexpr int kSkBlendModeSrcOver = 3;
constexpr int kSkBlendModeDstIn = 6;

const char* BlendModeNameForSaveLayer(int blend_mode) {
  switch (blend_mode) {
    case kSkBlendModeDstIn:
      return "dst_in";
    case kSkBlendModeSrcOver:
    default:
      return "src_over";
  }
}

bool IsStandaloneMaskBlendChunk(const RetainedPaintChunk& chunk) {
  const PaintPropertyStateSnapshot& state = chunk.property_state;
  return state.effect_has_blend_mode &&
         state.effect_blend_mode == kSkBlendModeDstIn &&
         !state.effect_has_non_default_opacity && !state.effect_has_filter &&
         !state.effect_has_backdrop_filter && state.effect_parent_id != 0;
}

bool CanStartStandaloneMaskGroup(const RetainedPaintChunk& content,
                                 const RetainedPaintChunk& mask) {
  const PaintPropertyStateSnapshot& content_state = content.property_state;
  return IsStandaloneMaskBlendChunk(mask) &&
         content_state.effect_node_id == mask.property_state.effect_parent_id &&
         !content_state.effect_has_blend_mode &&
         !content_state.effect_has_filter &&
         !content_state.effect_has_backdrop_filter;
}

bool IsVisualCommandType(DrawCommandType type) {
  switch (type) {
    case DrawCommandType::kFillRect:
    case DrawCommandType::kStrokeRect:
    case DrawCommandType::kFillRectShader:
    case DrawCommandType::kFillRRect:
    case DrawCommandType::kStrokeRRect:
    case DrawCommandType::kFillRRectShader:
    case DrawCommandType::kFillPath:
    case DrawCommandType::kDrawImage:
    case DrawCommandType::kDrawImageRect:
    case DrawCommandType::kDrawGlyphRun:
    case DrawCommandType::kDrawTextBlob:
    case DrawCommandType::kDrawText:
      return true;
    case DrawCommandType::kSave:
    case DrawCommandType::kRestore:
    case DrawCommandType::kTransform:
    case DrawCommandType::kClipRect:
    case DrawCommandType::kClipRRect:
    case DrawCommandType::kClipPath:
    case DrawCommandType::kSaveLayer:
    case DrawCommandType::kDiagnostic:
      return false;
  }
  return false;
}

bool HasVisualCommands(const RetainedPaintChunk* chunk) {
  if (!chunk) {
    return false;
  }
  for (const DrawCommand& command : chunk->commands) {
    if (IsVisualCommandType(command.type)) {
      return true;
    }
  }
  return false;
}

struct ExactChunkMatchSignature {
  RetainedChunkKind kind = RetainedChunkKind::kAnonymous;
  Rect placement_bounds;
  uint64_t content_hash = 0;
  uint64_t resource_hash = 0;
  uint64_t property_state_hash = 0;
  bool ignores_scroll_offset = false;
};

bool operator==(const ExactChunkMatchSignature& left,
                const ExactChunkMatchSignature& right) {
  return left.kind == right.kind &&
         left.placement_bounds.x == right.placement_bounds.x &&
         left.placement_bounds.y == right.placement_bounds.y &&
         left.placement_bounds.width == right.placement_bounds.width &&
         left.placement_bounds.height == right.placement_bounds.height &&
         left.content_hash == right.content_hash &&
         left.resource_hash == right.resource_hash &&
         left.property_state_hash == right.property_state_hash &&
         left.ignores_scroll_offset == right.ignores_scroll_offset;
}

struct ExactChunkMatchSignatureHash {
  size_t operator()(const ExactChunkMatchSignature& signature) const {
    uint64_t hash = 0;
    hash = HashCombine(hash, static_cast<uint64_t>(signature.kind));
    hash = HashCombine(hash, HashRect(signature.placement_bounds));
    hash = HashCombine(hash, signature.content_hash);
    hash = HashCombine(hash, signature.resource_hash);
    hash = HashCombine(hash, signature.property_state_hash);
    hash = HashCombine(hash, signature.ignores_scroll_offset ? 1u : 0u);
    return static_cast<size_t>(hash);
  }
};

ExactChunkMatchSignature BuildExactChunkMatchSignature(
    const RetainedPaintChunk& chunk) {
  return ExactChunkMatchSignature{
      chunk.kind,
      chunk.placement_bounds,
      chunk.content_hash,
      chunk.resource_hash,
      chunk.property_state.state_hash,
      chunk.ignores_scroll_offset,
  };
}

Rect MapRectToRootConservatively(Rect rect,
                                 const PaintPropertyStateSnapshot& state);

Rect InflateForDrawLooperLayers(Rect rect, const DrawCommand& command) {
  Rect bounds = rect;
  for (const DrawLooperLayer& layer : command.draw_looper_layers) {
    const float blur_outset = std::max(0.0f, layer.blur_sigma * 3.0f);
    Rect layer_bounds{rect.x + layer.offset_x - blur_outset,
                      rect.y + layer.offset_y - blur_outset,
                      rect.width + blur_outset * 2.0f,
                      rect.height + blur_outset * 2.0f};
    bounds = UnionRectBounds(bounds, layer_bounds);
  }
  return bounds;
}

Rect LocalOpacityLayerContributionBounds(const RetainedPaintChunk& chunk) {
  Rect bounds = chunk.placement_bounds;
  for (const DrawCommand& command : chunk.commands) {
    if (!IsVisualCommandType(command.type) || command.rect.width <= 0.0f ||
        command.rect.height <= 0.0f || command.draw_looper_layers.empty()) {
      continue;
    }
    bounds = UnionRectBounds(bounds,
                             InflateForDrawLooperLayers(command.rect, command));
  }
  return bounds;
}

Rect OpacityLayerContributionBounds(const RetainedPaintChunk& chunk) {
  Rect bounds =
      MapRectToRootConservatively(LocalOpacityLayerContributionBounds(chunk),
                                  chunk.property_state);
  if (chunk.property_state.has_clip_rect) {
    bounds = UnionRectBounds(bounds, chunk.property_state.clip_rect);
  }
  if (chunk.property_state.has_clip_rrect) {
    bounds = UnionRectBounds(bounds, chunk.property_state.clip_rrect);
  }
  return bounds;
}

std::optional<size_t> FindFollowingStandaloneMaskChunk(
    const std::vector<RetainedPaintChunk>& chunks,
    size_t content_index) {
  if (content_index >= chunks.size() || !HasVisualCommands(&chunks[content_index])) {
    return std::nullopt;
  }
  const uint64_t content_effect_node_id =
      chunks[content_index].property_state.effect_node_id;
  for (size_t next_index = content_index + 1; next_index < chunks.size();
       ++next_index) {
    if (CanStartStandaloneMaskGroup(chunks[content_index],
                                    chunks[next_index])) {
      return next_index;
    }
    if (IsStandaloneMaskBlendChunk(chunks[next_index])) {
      return std::nullopt;
    }
    if (HasVisualCommands(&chunks[next_index]) &&
        chunks[next_index].property_state.effect_node_id !=
            content_effect_node_id) {
      return std::nullopt;
    }
  }
  return std::nullopt;
}

Rect StandaloneMaskGroupBounds(const std::vector<RetainedPaintChunk>& chunks,
                               size_t first_content_index,
                               size_t mask_index) {
  Rect bounds = OpacityLayerContributionBounds(chunks[first_content_index]);
  for (size_t index = first_content_index + 1; index <= mask_index; ++index) {
    bounds = UnionRectBounds(bounds, OpacityLayerContributionBounds(chunks[index]));
  }
  return bounds;
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
  hash = HashCombine(hash, state.has_clip_rrect ? 1u : 0u);
  if (state.has_clip_rrect) {
    hash = HashCombine(hash, HashRect(state.clip_rrect));
    for (const Point radius : state.clip_rrect_radii) {
      hash = HashCombine(hash, HashFloat(radius.x));
      hash = HashCombine(hash, HashFloat(radius.y));
    }
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
  hash = HashCombine(hash, state.effect_has_unsupported_filter ? 1u : 0u);
  for (const FilterOperationSnapshot& operation :
       state.effect_filter_operations) {
    hash = HashCombine(hash, HashFilterOperation(operation));
  }
  hash = HashCombine(hash, state.effect_has_backdrop_filter ? 1u : 0u);
  hash = HashCombine(hash, state.effect_has_blend_mode ? 1u : 0u);
  hash = HashCombine(hash, static_cast<uint64_t>(state.effect_blend_mode));
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
  hash = HashCombine(hash, static_cast<uint64_t>(command.stroke_cap));
  hash = HashCombine(hash, static_cast<uint64_t>(command.stroke_join));
  hash = HashCombine(hash, HashFloat(command.stroke_miter));
  hash = HashCombine(hash, HashFloat(command.opacity));
  hash = HashCombine(hash, HashFloat(command.radius_x));
  hash = HashCombine(hash, HashFloat(command.radius_y));
  for (const Point radius : command.corner_radii) {
    hash = HashCombine(hash, HashFloat(radius.x));
    hash = HashCombine(hash, HashFloat(radius.y));
  }
  for (const FilterOperationSnapshot& operation : command.filter_operations) {
    hash = HashCombine(hash, HashFilterOperation(operation));
  }
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

float EffectiveContributionOpacity(const RetainedPaintChunk& chunk) {
  return chunk.property_state.effect_has_non_default_opacity
             ? chunk.property_state.effect_opacity
             : 1.0f;
}

bool SupportsContributionLocalization(const RetainedPaintChunk& chunk) {
  const PaintPropertyStateSnapshot& state = chunk.property_state;
  return state.transform_is_2d && !state.transform_has_perspective &&
         !state.transform_has_non_translation && !state.has_clip_rect &&
         !state.has_clip_rrect && !state.clip_has_path_clip &&
         !state.effect_has_filter && !state.effect_has_backdrop_filter &&
         !state.effect_has_blend_mode;
}

struct VisualContributionSignature {
  uint64_t command_hash = 0;
  uint64_t resource_hash = 0;
  uint64_t opacity_hash = 0;
};

bool operator==(const VisualContributionSignature& left,
                const VisualContributionSignature& right) {
  return left.command_hash == right.command_hash &&
         left.resource_hash == right.resource_hash &&
         left.opacity_hash == right.opacity_hash;
}

struct VisualContributionSignatureHash {
  size_t operator()(const VisualContributionSignature& signature) const {
    uint64_t hash = 0;
    hash = HashCombine(hash, signature.command_hash);
    hash = HashCombine(hash, signature.resource_hash);
    hash = HashCombine(hash, signature.opacity_hash);
    return static_cast<size_t>(hash);
  }
};

struct VisualContribution {
  VisualContributionSignature signature;
  Rect bounds;
};

std::vector<VisualContribution> CollectVisualContributions(
    const RetainedPaintChunk* chunk) {
  std::vector<VisualContribution> contributions;
  if (!chunk || !SupportsContributionLocalization(*chunk)) {
    return contributions;
  }
  const uint64_t opacity_hash = HashFloat(EffectiveContributionOpacity(*chunk));
  for (const DrawCommand& command : chunk->commands) {
    if (!IsVisualCommandType(command.type) || IsEmpty(command.rect)) {
      continue;
    }
    contributions.push_back(VisualContribution{
        VisualContributionSignature{
            HashCommandContent(command),
            HashCommandResources(command),
            opacity_hash,
        },
        command.rect,
    });
  }
  return contributions;
}

using ContributionCountMap =
    std::unordered_map<VisualContributionSignature,
                       int,
                       VisualContributionSignatureHash>;

ContributionCountMap BuildContributionCounts(const RetainedScene& scene) {
  ContributionCountMap counts;
  for (const RetainedPaintChunk& chunk : scene.chunks) {
    for (const VisualContribution& contribution :
         CollectVisualContributions(&chunk)) {
      ++counts[contribution.signature];
    }
  }
  return counts;
}

bool HasNonDefaultOpacity(const RetainedPaintChunk* chunk) {
  return chunk && chunk->property_state.effect_has_non_default_opacity &&
         chunk->property_state.effect_opacity >= 0.0f &&
         chunk->property_state.effect_opacity < 1.0f;
}

Rect ConsumeContributionDamageBounds(const RetainedPaintChunk* chunk,
                                     ContributionCountMap* remaining_counts) {
  Rect bounds;
  if (!chunk || !remaining_counts) {
    return bounds;
  }
  for (const VisualContribution& contribution :
       CollectVisualContributions(chunk)) {
    auto found = remaining_counts->find(contribution.signature);
    if (found == remaining_counts->end() || found->second <= 0) {
      continue;
    }
    bounds = UnionRectBounds(bounds, contribution.bounds);
    --found->second;
  }
  return bounds;
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

Rect MapRectToRootConservatively(Rect rect,
                                 const PaintPropertyStateSnapshot& state) {
  if (!state.transform_is_2d || state.transform_has_perspective) {
    return rect;
  }
  const Point p0 = MapPoint(state.transform_to_root, Point{rect.x, rect.y});
  const Point p1 = MapPoint(state.transform_to_root,
                            Point{rect.x + rect.width, rect.y});
  const Point p2 = MapPoint(state.transform_to_root,
                            Point{rect.x + rect.width, rect.y + rect.height});
  const Point p3 = MapPoint(state.transform_to_root,
                            Point{rect.x, rect.y + rect.height});
  const float left = std::min(std::min(p0.x, p1.x), std::min(p2.x, p3.x));
  const float top = std::min(std::min(p0.y, p1.y), std::min(p2.y, p3.y));
  const float right = std::max(std::max(p0.x, p1.x), std::max(p2.x, p3.x));
  const float bottom = std::max(std::max(p0.y, p1.y), std::max(p2.y, p3.y));
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

std::vector<Rect> NormalizeDirtyRects(std::vector<Rect> rects,
                                      Rect viewport) {
  std::vector<Rect> normalized;
  for (Rect rect : rects) {
    rect = IntersectRects(rect, viewport);
    if (!IsEmpty(rect)) {
      normalized.push_back(rect);
    }
  }

  bool merged = true;
  while (merged) {
    merged = false;
    for (size_t i = 0; i < normalized.size() && !merged; ++i) {
      for (size_t j = i + 1; j < normalized.size(); ++j) {
        if (!Intersects(normalized[i], normalized[j]) &&
            !SameRect(normalized[i], normalized[j])) {
          continue;
        }
        normalized[i] = UnionRects(normalized[i], normalized[j]);
        normalized.erase(normalized.begin() + static_cast<std::ptrdiff_t>(j));
        merged = true;
        break;
      }
    }
  }
  return normalized;
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

Rect OutsetRect(Rect rect, float amount) {
  rect.x -= amount;
  rect.y -= amount;
  rect.width += amount * 2.0f;
  rect.height += amount * 2.0f;
  return rect;
}

bool IsZero(Point point) {
  return NearlyEqual(point.x, 0.0f) && NearlyEqual(point.y, 0.0f);
}

Matrix4 TranslationMatrix(Point delta) {
  Matrix4 matrix;
  matrix.values[12] = delta.x;
  matrix.values[13] = delta.y;
  return matrix;
}

using ScrollNodeIdSet = std::unordered_set<uint64_t>;

bool IsDocumentScrollPresentationChunk(const RetainedPaintChunk& chunk) {
  const PaintPropertyStateSnapshot& state = chunk.property_state;
  if (chunk.kind != RetainedChunkKind::kDocument ||
      state.scroll_node_id == 0 ||
      state.transform_has_non_translation ||
      state.transform_has_perspective ||
      state.clip_chain_depth != 0 ||
      state.transform_chain_depth > 2) {
    return false;
  }
  if (state.scroll_container_rect.width > 0.0f ||
      state.scroll_container_rect.height > 0.0f ||
      state.scroll_contents_rect.width > 0.0f ||
      state.scroll_contents_rect.height > 0.0f) {
    return false;
  }
  return true;
}

ScrollNodeIdSet CollectDocumentScrollPresentationNodeIds(
    const RetainedScene& scene) {
  ScrollNodeIdSet scroll_node_ids;
  for (const RetainedPaintChunk& chunk : scene.chunks) {
    if (IsDocumentScrollPresentationChunk(chunk)) {
      scroll_node_ids.insert(chunk.property_state.scroll_node_id);
    }
  }
  return scroll_node_ids;
}

Point PresentationScrollOffsetDelta(const RetainedPaintChunk& chunk,
                                    Point current_scroll_offset,
                                    const ScrollNodeIdSet& scroll_node_ids) {
  if (chunk.property_state.scroll_node_id == 0 || IsZero(current_scroll_offset)) {
    return Point{};
  }
  if (!scroll_node_ids.contains(chunk.property_state.scroll_node_id)) {
    return Point{};
  }
  return Point{-current_scroll_offset.x, -current_scroll_offset.y};
}

bool IsRootDocumentScrollReuseChunk(const RetainedPaintChunk& chunk) {
  const PaintPropertyStateSnapshot& state = chunk.property_state;
  return chunk.kind == RetainedChunkKind::kDocument &&
         state.scroll_node_id == 0 &&
         state.transform_chain_depth <= 1 &&
         !state.transform_has_non_translation;
}

bool TransformAlreadyIncludesPresentationScroll(
    const PaintPropertyStateSnapshot& property_state,
    Point delta) {
  if (!property_state.transform_is_2d ||
      property_state.transform_has_perspective ||
      property_state.transform_has_non_translation ||
      property_state.scroll_node_id == 0) {
    return false;
  }
  return NearlyEqual(property_state.transform_to_root.values[12], delta.x) &&
         NearlyEqual(property_state.transform_to_root.values[13], delta.y);
}

bool CanTranslateImageClipCommandsForPresentation(
    const DrawCommandList& commands) {
  bool has_image = false;
  for (const DrawCommand& command : commands) {
    switch (command.type) {
      case DrawCommandType::kSave:
      case DrawCommandType::kRestore:
      case DrawCommandType::kClipRect:
      case DrawCommandType::kClipRRect:
        break;
      case DrawCommandType::kDrawImage:
      case DrawCommandType::kDrawImageRect:
        has_image = true;
        break;
      case DrawCommandType::kTransform:
      case DrawCommandType::kClipPath:
      case DrawCommandType::kSaveLayer:
      case DrawCommandType::kFillRect:
      case DrawCommandType::kStrokeRect:
      case DrawCommandType::kFillRectShader:
      case DrawCommandType::kFillRRect:
      case DrawCommandType::kStrokeRRect:
      case DrawCommandType::kFillRRectShader:
      case DrawCommandType::kFillPath:
      case DrawCommandType::kDrawGlyphRun:
      case DrawCommandType::kDrawTextBlob:
      case DrawCommandType::kDrawText:
      case DrawCommandType::kDiagnostic:
        return false;
    }
  }
  return has_image;
}

DrawCommandList TranslateImageClipCommandsForPresentation(
    const DrawCommandList& source,
    Point delta) {
  DrawCommandList commands;
  commands.reserve(source.size());
  for (DrawCommand command : source) {
    switch (command.type) {
      case DrawCommandType::kDrawImage:
      case DrawCommandType::kDrawImageRect:
        command.rect = Translate(command.rect, delta);
        break;
      case DrawCommandType::kSave:
      case DrawCommandType::kRestore:
      case DrawCommandType::kClipRect:
      case DrawCommandType::kClipRRect:
      case DrawCommandType::kTransform:
      case DrawCommandType::kClipPath:
      case DrawCommandType::kSaveLayer:
      case DrawCommandType::kFillRect:
      case DrawCommandType::kStrokeRect:
      case DrawCommandType::kFillRectShader:
      case DrawCommandType::kFillRRect:
      case DrawCommandType::kStrokeRRect:
      case DrawCommandType::kFillRRectShader:
      case DrawCommandType::kFillPath:
      case DrawCommandType::kDrawGlyphRun:
      case DrawCommandType::kDrawTextBlob:
      case DrawCommandType::kDrawText:
      case DrawCommandType::kDiagnostic:
        break;
    }
    commands.push_back(std::move(command));
  }
  return commands;
}

PaintPropertyStateSnapshot TranslatePropertyStateForPresentation(
    PaintPropertyStateSnapshot property_state,
    Point delta) {
  if (IsZero(delta)) {
    return property_state;
  }
  const bool clip_already_in_presented_space =
      TransformAlreadyIncludesPresentationScroll(property_state, delta);
  if (!clip_already_in_presented_space) {
    if (property_state.has_clip_rect) {
      property_state.clip_rect = Translate(property_state.clip_rect, delta);
    }
    if (property_state.has_clip_rrect) {
      property_state.clip_rrect = Translate(property_state.clip_rrect, delta);
    }
  }
  if (property_state.scroll_container_rect.width > 0.0f ||
      property_state.scroll_container_rect.height > 0.0f) {
    property_state.scroll_container_rect =
        Translate(property_state.scroll_container_rect, delta);
  }
  if (property_state.scroll_contents_rect.width > 0.0f ||
      property_state.scroll_contents_rect.height > 0.0f) {
    property_state.scroll_contents_rect =
        Translate(property_state.scroll_contents_rect, delta);
  }
  return property_state;
}

Rect PlacementBoundsForPresentation(const RetainedPaintChunk& chunk,
                                    Point current_scroll_offset,
                                    const ScrollNodeIdSet& scroll_node_ids) {
  return Translate(chunk.placement_bounds,
                   PresentationScrollOffsetDelta(chunk, current_scroll_offset,
                                                 scroll_node_ids));
}

PaintPropertyStateSnapshot PropertyStateForPresentation(
    const RetainedPaintChunk& chunk,
    Point current_scroll_offset,
    const ScrollNodeIdSet& scroll_node_ids) {
  return TranslatePropertyStateForPresentation(
      chunk.property_state,
      PresentationScrollOffsetDelta(chunk, current_scroll_offset,
                                    scroll_node_ids));
}

DrawCommandList CommandsForPresentation(const RetainedPaintChunk& chunk,
                                        Point current_scroll_offset,
                                        const ScrollNodeIdSet& scroll_node_ids) {
  const Point delta =
      PresentationScrollOffsetDelta(chunk, current_scroll_offset,
                                    scroll_node_ids);
  if (IsZero(delta)) {
    return chunk.commands;
  }
  if (TransformAlreadyIncludesPresentationScroll(chunk.property_state, delta) &&
      CanTranslateImageClipCommandsForPresentation(chunk.commands)) {
    return TranslateImageClipCommandsForPresentation(chunk.commands, delta);
  }
  DrawCommandList commands;
  commands.reserve(chunk.commands.size() + 3);
  commands.push_back(DrawCommand::Save());
  commands.push_back(DrawCommand::Transform(TranslationMatrix(delta)));
  commands.insert(commands.end(), chunk.commands.begin(), chunk.commands.end());
  commands.push_back(DrawCommand::Restore());
  return commands;
}

RetainedPaintChunk ChunkForPresentation(const RetainedPaintChunk& chunk,
                                        Point current_scroll_offset,
                                        const ScrollNodeIdSet& scroll_node_ids) {
  const Point delta =
      PresentationScrollOffsetDelta(chunk, current_scroll_offset,
                                    scroll_node_ids);
  if (IsZero(delta)) {
    return chunk;
  }
  RetainedPaintChunk presented = chunk;
  presented.bounds = Translate(presented.bounds, delta);
  presented.placement_bounds = Translate(presented.placement_bounds, delta);
  presented.property_state =
      TranslatePropertyStateForPresentation(presented.property_state, delta);
  presented.commands =
      CommandsForPresentation(chunk, current_scroll_offset, scroll_node_ids);
  return presented;
}

bool ShouldLocalizeRootSpaceCommands(const RetainedPaintChunk& chunk) {
  const PaintPropertyStateSnapshot& state = chunk.property_state;
  return state.transform_is_2d && !state.transform_has_perspective &&
         state.transform_has_non_translation && state.effect_chain_depth == 0 &&
         !state.effect_has_non_default_opacity && chunk.bounds.width > 0.0f &&
         chunk.bounds.height > 0.0f;
}

void LocalizeRect(Rect& rect, Point origin) {
  rect.x -= origin.x;
  rect.y -= origin.y;
}

DrawCommand LocalizeRootSpaceCommand(DrawCommand command, Point origin) {
  switch (command.type) {
    case DrawCommandType::kClipRect:
    case DrawCommandType::kClipRRect:
    case DrawCommandType::kSaveLayer:
    case DrawCommandType::kFillRect:
    case DrawCommandType::kStrokeRect:
    case DrawCommandType::kFillRectShader:
    case DrawCommandType::kFillRRect:
    case DrawCommandType::kStrokeRRect:
    case DrawCommandType::kFillRRectShader:
    case DrawCommandType::kDrawImage:
    case DrawCommandType::kDrawImageRect:
    case DrawCommandType::kDrawTextBlob:
    case DrawCommandType::kDrawText:
      LocalizeRect(command.rect, origin);
      break;
    case DrawCommandType::kDrawGlyphRun:
      for (Point& position : command.glyph_run.positions) {
        position.x -= origin.x;
        position.y -= origin.y;
      }
      break;
    case DrawCommandType::kSave:
    case DrawCommandType::kRestore:
    case DrawCommandType::kTransform:
    case DrawCommandType::kClipPath:
    case DrawCommandType::kFillPath:
    case DrawCommandType::kDiagnostic:
      break;
  }
  return command;
}

DrawCommandList LocalizeRootSpaceCommandsForTransform(
    const RetainedPaintChunk& chunk) {
  if (!ShouldLocalizeRootSpaceCommands(chunk)) {
    return chunk.commands;
  }

  DrawCommandList commands;
  commands.reserve(chunk.commands.size());
  const Point origin{chunk.bounds.x, chunk.bounds.y};
  for (const DrawCommand& command : chunk.commands) {
    commands.push_back(LocalizeRootSpaceCommand(command, origin));
  }
  return commands;
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

std::vector<Rect> ComputeScrollExposedRects(Rect viewport, Point delta);
const RetainedPaintChunk* FindChunkByKey(const RetainedScene& scene,
                                         const std::string& key);

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
  std::unordered_map<ExactChunkMatchSignature,
                     std::vector<const RetainedPaintChunk*>,
                     ExactChunkMatchSignatureHash>
      previous_by_exact_signature;
  if (previous) {
    for (const RetainedPaintChunk& chunk : previous->chunks) {
      previous_by_key[chunk.key] = &chunk;
      previous_by_exact_signature[BuildExactChunkMatchSignature(chunk)]
          .push_back(&chunk);
    }
  }

  for (const RetainedPaintChunk& current_chunk : current.chunks) {
    const auto found = previous_by_key.find(current_chunk.key);
    const RetainedPaintChunk* matched_previous_chunk = nullptr;
    if (found != previous_by_key.end()) {
      matched_previous_chunk = found->second;
      auto signature_found = previous_by_exact_signature.find(
          BuildExactChunkMatchSignature(*matched_previous_chunk));
      if (signature_found != previous_by_exact_signature.end()) {
        auto& candidates = signature_found->second;
        candidates.erase(std::remove(candidates.begin(), candidates.end(),
                                     matched_previous_chunk),
                         candidates.end());
        if (candidates.empty()) {
          previous_by_exact_signature.erase(signature_found);
        }
      }
      previous_by_key.erase(found);
    } else {
      auto signature_found = previous_by_exact_signature.find(
          BuildExactChunkMatchSignature(current_chunk));
      if (signature_found != previous_by_exact_signature.end() &&
          !signature_found->second.empty()) {
        matched_previous_chunk = signature_found->second.back();
        signature_found->second.pop_back();
        if (signature_found->second.empty()) {
          previous_by_exact_signature.erase(signature_found);
        }
        previous_by_key.erase(matched_previous_chunk->key);
      }
    }
    if (!matched_previous_chunk) {
      RecordChange(diff, RetainedChunkDiff{
                             current_chunk.key,
                             std::string(),
                             current_chunk.key,
                             RetainedChunkChangeKind::kAdded,
                             std::nullopt,
                             current_chunk.placement_bounds,
                         });
      continue;
    }

    const RetainedPaintChunk& previous_chunk = *matched_previous_chunk;
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
                           previous_chunk.key,
                           current_chunk.key,
                           kind,
                           previous_chunk.placement_bounds,
                           current_chunk.placement_bounds,
                       });
  }

  for (const auto& entry : previous_by_key) {
    RecordChange(diff, RetainedChunkDiff{
                           entry.first,
                           entry.first,
                           std::string(),
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
  plan.current_scroll_offset = current_scroll_offset;
  plan.viewport_bounds = Rect{0.0f, 0.0f, viewport.width, viewport.height};
  const ScrollNodeIdSet current_document_scroll_node_ids =
      CollectDocumentScrollPresentationNodeIds(current);
  const ScrollNodeIdSet previous_document_scroll_node_ids =
      previous ? CollectDocumentScrollPresentationNodeIds(*previous)
               : ScrollNodeIdSet{};
  plan.scroll_translation_delta =
      Point{previous_scroll_offset.x - current_scroll_offset.x,
            previous_scroll_offset.y - current_scroll_offset.y};
  plan.allows_scroll_translation_reuse =
      previous != nullptr &&
      (plan.scroll_translation_delta.x != 0.0f ||
       plan.scroll_translation_delta.y != 0.0f);
  if (plan.allows_scroll_translation_reuse) {
    plan.scroll_exposed_rects = ComputeScrollExposedRects(
        plan.viewport_bounds, plan.scroll_translation_delta);
  }

  const RetainedSceneDiff diff = DiffRetainedScenes(current, previous);
  bool has_opacity_transition = false;
  for (const RetainedChunkDiff& chunk_diff : diff.chunks) {
    const RetainedPaintChunk* previous_chunk =
        previous && !chunk_diff.previous_key.empty()
            ? FindChunkByKey(*previous, chunk_diff.previous_key)
            : nullptr;
    const RetainedPaintChunk* current_chunk =
        !chunk_diff.current_key.empty()
            ? FindChunkByKey(current, chunk_diff.current_key)
            : nullptr;
    if (HasNonDefaultOpacity(previous_chunk) || HasNonDefaultOpacity(current_chunk)) {
      has_opacity_transition = true;
      break;
    }
  }
  ContributionCountMap previous_contribution_excess;
  ContributionCountMap current_contribution_excess;
  if (has_opacity_transition && previous != nullptr) {
    const ContributionCountMap previous_counts = BuildContributionCounts(*previous);
    const ContributionCountMap current_counts = BuildContributionCounts(current);
    for (const auto& entry : previous_counts) {
      const int current_count =
          current_counts.count(entry.first) ? current_counts.at(entry.first) : 0;
      if (entry.second > current_count) {
        previous_contribution_excess[entry.first] = entry.second - current_count;
      }
    }
    for (const auto& entry : current_counts) {
      const int previous_count =
          previous_counts.count(entry.first) ? previous_counts.at(entry.first) : 0;
      if (entry.second > previous_count) {
        current_contribution_excess[entry.first] = entry.second - previous_count;
      }
    }
  }
  // Post-first-frame changes can be represented as local damage because
  // incremental replay now clears and redraws only the dirty region against
  // the current full scene command list.
  plan.requires_full_redraw = previous == nullptr;

  for (const RetainedChunkDiff& chunk_diff : diff.chunks) {
    PresentationChunkUpdate update;
    update.key = chunk_diff.key;
    update.previous_key =
        chunk_diff.previous_key.empty() ? chunk_diff.key : chunk_diff.previous_key;
    update.current_key =
        chunk_diff.current_key.empty() ? chunk_diff.key : chunk_diff.current_key;
    update.change_kind = chunk_diff.kind;
    const RetainedPaintChunk* previous_chunk =
        previous ? FindChunkByKey(*previous, update.previous_key) : nullptr;
    const RetainedPaintChunk* current_chunk =
        FindChunkByKey(current, update.current_key);
    update.previous_bounds =
        previous_chunk ? PlacementBoundsForPresentation(*previous_chunk,
                                                        previous_scroll_offset,
                                                        previous_document_scroll_node_ids)
                       : chunk_diff.previous_bounds;
    update.current_bounds =
        current_chunk ? PlacementBoundsForPresentation(*current_chunk,
                                                       current_scroll_offset,
                                                       current_document_scroll_node_ids)
                      : chunk_diff.current_bounds;
    update.requires_placement_update =
        chunk_diff.kind == RetainedChunkChangeKind::kMoved ||
        chunk_diff.kind == RetainedChunkChangeKind::kAdded ||
        chunk_diff.kind == RetainedChunkChangeKind::kRemoved;
    update.requires_redraw =
        chunk_diff.kind == RetainedChunkChangeKind::kAdded ||
        chunk_diff.kind == RetainedChunkChangeKind::kRemoved ||
        chunk_diff.kind == RetainedChunkChangeKind::kContentChanged ||
        chunk_diff.kind == RetainedChunkChangeKind::kPresentationChanged;
    const bool scroll_reuse_candidate =
        plan.allows_scroll_translation_reuse &&
        chunk_diff.kind == RetainedChunkChangeKind::kRetained &&
        update.current_bounds &&
        Intersects(*update.current_bounds, plan.viewport_bounds) &&
        current_chunk != nullptr;
    if (scroll_reuse_candidate) {
      if (IsRootDocumentScrollReuseChunk(*current_chunk)) {
        update.requires_redraw = false;
      } else if (current_chunk->property_state.scroll_node_id == 0) {
        update.requires_redraw = true;
      } else {
        update.requires_redraw = false;
      }
    }

    if (update.requires_redraw) {
      Rect previous_contribution_bounds;
      Rect current_contribution_bounds;
      const bool previous_supports_contribution_localization =
          previous_chunk && SupportsContributionLocalization(*previous_chunk);
      const bool current_supports_contribution_localization =
          current_chunk && SupportsContributionLocalization(*current_chunk);
      if (has_opacity_transition) {
        previous_contribution_bounds =
            ConsumeContributionDamageBounds(previous_chunk,
                                            &previous_contribution_excess);
        current_contribution_bounds =
            ConsumeContributionDamageBounds(current_chunk,
                                            &current_contribution_excess);
      }
      if (!scroll_reuse_candidate && update.previous_bounds &&
          HasVisualCommands(previous_chunk)) {
        if (has_opacity_transition &&
            previous_supports_contribution_localization) {
          if (!IsEmpty(previous_contribution_bounds)) {
            plan.dirty_rects.push_back(MapRectConservatively(
                previous_contribution_bounds,
                previous_chunk
                    ? PropertyStateForPresentation(*previous_chunk,
                                                  previous_scroll_offset,
                                                  previous_document_scroll_node_ids)
                    : PaintPropertyStateSnapshot{},
                plan.viewport_bounds));
          }
        } else {
          plan.dirty_rects.push_back(MapRectConservatively(
              *update.previous_bounds,
              previous_chunk ? PropertyStateForPresentation(*previous_chunk,
                                                            previous_scroll_offset,
                                                            previous_document_scroll_node_ids)
                             : PaintPropertyStateSnapshot{},
              plan.viewport_bounds));
        }
      }
      if (update.current_bounds && HasVisualCommands(current_chunk)) {
        if (has_opacity_transition &&
            current_supports_contribution_localization) {
          if (!IsEmpty(current_contribution_bounds)) {
            plan.dirty_rects.push_back(MapRectConservatively(
                current_contribution_bounds,
                current_chunk ? PropertyStateForPresentation(*current_chunk,
                                                             current_scroll_offset,
                                                             current_document_scroll_node_ids)
                              : PaintPropertyStateSnapshot{},
                plan.viewport_bounds));
          }
        } else {
          Rect current_bounds = *update.current_bounds;
          if (scroll_reuse_candidate && current_chunk &&
              current_chunk->property_state.scroll_node_id == 0 &&
              !IsRootDocumentScrollReuseChunk(*current_chunk)) {
            current_bounds = OutsetRect(current_bounds, 1.0f);
          }
          plan.dirty_rects.push_back(MapRectConservatively(
              current_bounds,
              current_chunk ? PropertyStateForPresentation(*current_chunk,
                                                           current_scroll_offset,
                                                           current_document_scroll_node_ids)
                            : PaintPropertyStateSnapshot{},
              plan.viewport_bounds));
        }
      }
    }
    plan.chunk_updates.push_back(std::move(update));
  }

  for (const Rect& rect : plan.scroll_exposed_rects) {
    plan.dirty_rects.push_back(rect);
  }

  plan.dirty_rects =
      NormalizeDirtyRects(std::move(plan.dirty_rects), plan.viewport_bounds);

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
  frame.allows_scroll_translation_reuse =
      plan.allows_scroll_translation_reuse;
  frame.scroll_translation_delta = plan.scroll_translation_delta;
  for (const Rect dirty : frame.damage_rects) {
    frame.damage_bounds = UnionRectBounds(frame.damage_bounds, dirty);
  }

  frame.resource_commands.reserve(load_commands.size());
  for (const LoadCommand& command : load_commands) {
    frame.resource_commands.push_back(
        ResourceCommand::FromLoadCommand(command));
  }

  bool effect_layer_open = false;
  uint64_t active_effect_node_id = 0;
  float active_effect_opacity = 1.0f;
  std::vector<FilterOperationSnapshot> active_filter_operations;
  bool mask_group_open = false;
  std::optional<size_t> active_mask_chunk_index;
  const ScrollNodeIdSet document_scroll_node_ids =
      CollectDocumentScrollPresentationNodeIds(scene);
  for (size_t chunk_index = 0; chunk_index < scene.chunks.size();
       ++chunk_index) {
    const RetainedPaintChunk presented_chunk =
        ChunkForPresentation(scene.chunks[chunk_index],
                             plan.current_scroll_offset,
                             document_scroll_node_ids);
    const RetainedPaintChunk& retained_chunk = presented_chunk;
    const bool needs_effect_layer =
        NeedsGroupedEffectLayer(retained_chunk.property_state);
    if (effect_layer_open &&
        (!needs_effect_layer ||
         retained_chunk.property_state.effect_node_id !=
             active_effect_node_id ||
         !NearlyEqual(retained_chunk.property_state.effect_opacity,
                      active_effect_opacity) ||
         !SameFilterOperations(retained_chunk.property_state
                                   .effect_filter_operations,
                               active_filter_operations))) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Restore()));
      effect_layer_open = false;
    }
    if (needs_effect_layer && !effect_layer_open) {
      Rect effect_bounds = OpacityLayerContributionBounds(retained_chunk);
      for (size_t next_index = chunk_index + 1; next_index < scene.chunks.size();
           ++next_index) {
        if (!SameEffectGroup(retained_chunk.property_state,
                             scene.chunks[next_index].property_state)) {
          break;
        }
        effect_bounds = UnionRectBounds(
            effect_bounds,
            OpacityLayerContributionBounds(scene.chunks[next_index]));
      }
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::SaveLayer(
          effect_bounds, retained_chunk.property_state.effect_opacity,
          "src_over",
          retained_chunk.property_state.effect_filter_operations)));
      effect_layer_open = true;
      active_effect_node_id = retained_chunk.property_state.effect_node_id;
      active_effect_opacity = retained_chunk.property_state.effect_opacity;
      active_filter_operations =
          retained_chunk.property_state.effect_filter_operations;
    }

    if (!mask_group_open && !effect_layer_open) {
      if (std::optional<size_t> mask_index =
              FindFollowingStandaloneMaskChunk(scene.chunks, chunk_index)) {
        const Rect mask_group_bounds =
            StandaloneMaskGroupBounds(scene.chunks, chunk_index, *mask_index);
        frame.scene_commands.push_back(SceneCommand::Draw(
            DrawCommand::SaveLayer(mask_group_bounds, 1.0f)));
        mask_group_open = true;
        active_mask_chunk_index = mask_index;
      }
    }
    const bool is_active_mask_chunk =
        mask_group_open && active_mask_chunk_index &&
        *active_mask_chunk_index == chunk_index;
    if (is_active_mask_chunk) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::SaveLayer(
          retained_chunk.placement_bounds, 1.0f,
          BlendModeNameForSaveLayer(retained_chunk.property_state
                                        .effect_blend_mode))));
    }

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
    chunk.commands = LocalizeRootSpaceCommandsForTransform(retained_chunk);
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
    const bool has_chunk_property_clip =
        retained_chunk.property_state.has_clip_rect ||
        retained_chunk.property_state.has_clip_rrect;
    if (has_chunk_property_clip) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Save()));
    }
    if (retained_chunk.property_state.has_clip_rect) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::ClipRect(
          retained_chunk.property_state.clip_rect)));
    }
    if (retained_chunk.property_state.has_clip_rrect) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::ClipRRect(
          retained_chunk.property_state.clip_rrect,
          retained_chunk.property_state.clip_rrect_radii, false)));
    }
    for (const DrawCommand& command : chunk.commands) {
      frame.scene_commands.push_back(SceneCommand::Draw(command));
    }
    if (has_chunk_property_clip) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Restore()));
    }
    frame.scene_commands.push_back(SceneCommand::EndChunk(chunk.chunk_id));
    if (is_active_mask_chunk) {
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Restore()));
      frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Restore()));
      mask_group_open = false;
      active_mask_chunk_index.reset();
    }
    frame.scene_chunks.push_back(std::move(chunk));
  }
  if (mask_group_open) {
    frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Restore()));
  }
  if (effect_layer_open) {
    frame.scene_commands.push_back(SceneCommand::Draw(DrawCommand::Restore()));
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

std::vector<Rect> ComputeScrollExposedRects(Rect viewport, Point delta) {
  std::vector<Rect> rects;
  if (delta.x == 0.0f && delta.y == 0.0f) {
    return rects;
  }
  if (std::abs(delta.x) >= viewport.width ||
      std::abs(delta.y) >= viewport.height) {
    rects.push_back(viewport);
    return rects;
  }
  if (delta.x > 0.0f) {
    rects.push_back(Rect{viewport.x, viewport.y,
                         std::min(delta.x, viewport.width), viewport.height});
  } else if (delta.x < 0.0f) {
    const float width = std::min(-delta.x, viewport.width);
    rects.push_back(Rect{viewport.x + viewport.width - width, viewport.y,
                         width, viewport.height});
  }
  if (delta.y > 0.0f) {
    rects.push_back(Rect{viewport.x, viewport.y, viewport.width,
                         std::min(delta.y, viewport.height)});
  } else if (delta.y < 0.0f) {
    const float height = std::min(-delta.y, viewport.height);
    rects.push_back(Rect{viewport.x, viewport.y + viewport.height - height,
                         viewport.width, height});
  }
  return rects;
}

const RetainedPaintChunk* FindChunkByKey(const RetainedScene& scene,
                                         const std::string& key) {
  for (const RetainedPaintChunk& chunk : scene.chunks) {
    if (chunk.key == key) {
      return &chunk;
    }
  }
  return nullptr;
}

}  // namespace html_css_renderer
