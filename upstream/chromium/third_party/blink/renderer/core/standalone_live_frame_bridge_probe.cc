// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/testing/dummy_page_holder.h"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <array>
#include <iomanip>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <utility>
#include <string>
#include <vector>

#include "cc/paint/paint_op.h"
#include "cc/paint/paint_op_buffer_iterator.h"
#include "cc/paint/paint_record.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkPathBuilder.h"
#include "third_party/skia/include/core/SkSerialProcs.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/node.h"
#include "third_party/blink/renderer/core/dom/text.h"
#include "third_party/blink/renderer/core/core_initializer.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html/html_body_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/html/html_style_element.h"
#include "third_party/blink/renderer/core/layout/layout_box.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_display_item.h"
#include "third_party/blink/renderer/platform/graphics/paint/geometry_mapper.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_chunk.h"
#include "third_party/blink/renderer/platform/geometry/length.h"
#include "third_party/blink/renderer/platform/wtf/wtf.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/rect_conversions.h"
#include "ui/gfx/geometry/skia_conversions.h"

namespace blink::standalone_renderer_probe {

extern "C" bool g_standalone_blink_saw_font_draw_text;
extern "C" int g_standalone_blink_viewport_width;
extern "C" int g_standalone_blink_viewport_height;

namespace {

struct LiveFramePaintProbeResult {
  int lifecycle_reached_paint_clean = 0;
  int paint_chunk_count = 0;
  int display_item_count = 0;
};

struct LiveExportedGlyph {
  uint32_t glyph_id = 0;
  float x = 0.0f;
  float y = 0.0f;
};

struct LiveExportedChunkPropertyState {
  uint64_t state_hash = 0;
  std::array<float, 16> transform_to_root = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f,
  };
  bool has_clip_rect = false;
  float clip_x = 0.0f;
  float clip_y = 0.0f;
  float clip_width = 0.0f;
  float clip_height = 0.0f;
  bool transform_is_2d = true;
  bool transform_has_perspective = false;
  bool transform_has_non_translation = false;
  uint64_t transform_node_id = 0;
  uint64_t transform_parent_id = 0;
  uint32_t transform_chain_depth = 0;
  uint64_t clip_node_id = 0;
  uint64_t clip_parent_id = 0;
  uint64_t clip_local_transform_id = 0;
  uint32_t clip_chain_depth = 0;
  bool clip_has_rounded_clip = false;
  bool clip_has_path_clip = false;
  uint64_t effect_node_id = 0;
  uint64_t effect_parent_id = 0;
  uint32_t effect_chain_depth = 0;
  float effect_opacity = 1.0f;
  bool effect_has_non_default_opacity = false;
  bool effect_has_filter = false;
  bool effect_has_backdrop_filter = false;
  bool effect_has_blend_mode = false;
  uint64_t effect_output_clip_id = 0;
  uint64_t scroll_node_id = 0;
  uint64_t scroll_parent_id = 0;
  bool has_scroll_offset = false;
  float scroll_offset_x = 0.0f;
  float scroll_offset_y = 0.0f;
  float scroll_container_x = 0.0f;
  float scroll_container_y = 0.0f;
  float scroll_container_width = 0.0f;
  float scroll_container_height = 0.0f;
  float scroll_contents_x = 0.0f;
  float scroll_contents_y = 0.0f;
  float scroll_contents_width = 0.0f;
  float scroll_contents_height = 0.0f;
};

struct LiveExportedDrawOp {
  int type = 0;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 1.0f;
  float font_size = 0.0f;
  float radius_x = 0.0f;
  float radius_y = 0.0f;
  std::array<SkVector, 4> corner_radii = {};
  std::vector<LiveExportedGlyph> glyphs;
  int mask_width = 0;
  int mask_height = 0;
  std::vector<uint8_t> path_bytes;
  std::vector<uint8_t> text_blob_bytes;
  std::vector<uint8_t> shader_bytes;
  std::vector<uint8_t> alpha_mask;
  std::vector<uint8_t> rgba_pixels;
  std::string debug_label;
};

struct LiveFramePaintProbeCache {
  DummyPageHolder* holder = nullptr;
  LiveFramePaintProbeResult result;
  std::string body_html;
  std::vector<LiveExportedDrawOp> exported_draw_ops;
  std::vector<LiveExportedChunkPropertyState> chunk_property_states;
  std::vector<std::string> artifact_audit_lines;
  std::string raw_paint_artifact_audit_json;
  int viewport_width = 320;
  int viewport_height = 200;
  bool initialized = false;
};

LiveFramePaintProbeCache& ProbeCache() {
  static LiveFramePaintProbeCache* cache = new LiveFramePaintProbeCache();
  return *cache;
}

void TraceLiveFrameProbeStage(const char* stage) {
}

void DumpNodeForStandaloneRenderer(const Node& node, int depth) {
  const String node_name = node.nodeName();
  const String text = node.textContent();
  if (const auto* text_node = DynamicTo<Text>(node)) {
  }
  if (const auto* element = DynamicTo<Element>(node)) {
    const String namespace_uri = element->namespaceURI();
    if (const ComputedStyle* style = element->GetComputedStyle()) {
      const LayoutObject* layout_object = element->GetLayoutObject();
      PhysicalOffset physical_location;
      PhysicalOffset paint_offset;
      PhysicalSize stitched_size;
      if (const auto* box = DynamicTo<LayoutBox>(layout_object)) {
        physical_location = box->PhysicalLocation();
        paint_offset = box->FirstFragment().PaintOffset();
        stitched_size = box->StitchedSize();
      }
    }
  }
  if (depth >= 4) {
    return;
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    DumpNodeForStandaloneRenderer(*child, depth + 1);
  }
}

void AppendSkColor(LiveExportedDrawOp& op, const SkColor4f& color) {
  op.r = color.fR;
  op.g = color.fG;
  op.b = color.fB;
  op.a = color.fA;
}

void AppendFillRectOp(float x,
                      float y,
                      float width,
                      float height,
                      const SkColor4f& color,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 1;
  exported.x = x;
  exported.y = y;
  exported.width = width;
  exported.height = height;
  AppendSkColor(exported, color);
  exported_draw_ops.push_back(exported);
}

void AppendSkRectFillOp(const SkRect& rect,
                        float translate_x,
                        float translate_y,
                        const SkColor4f& color,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!rect.isFinite()) {
    return;
  }
  AppendFillRectOp(translate_x + rect.x(), translate_y + rect.y(),
                   rect.width(), rect.height(), color, exported_draw_ops);
}

void AppendSkIRectFillOp(const SkIRect& rect,
                         float translate_x,
                         float translate_y,
                         const SkColor4f& color,
                         std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  AppendFillRectOp(translate_x + static_cast<float>(rect.x()),
                   translate_y + static_cast<float>(rect.y()),
                   static_cast<float>(rect.width()),
                   static_cast<float>(rect.height()), color,
                   exported_draw_ops);
}

void AppendStrokeRectOp(float x,
                        float y,
                        float width,
                        float height,
                        SkScalar stroke_width,
                        const SkColor4f& color,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 4;
  exported.x = x;
  exported.y = y;
  exported.width = width;
  exported.height = height;
  exported.font_size = stroke_width > 0.0f ? stroke_width : 1.0f;
  AppendSkColor(exported, color);
  exported_draw_ops.push_back(exported);
}

void AppendRRectOp(float x,
                   float y,
                   float width,
                   float height,
                   float radius_x,
                   float radius_y,
                   SkScalar stroke_width,
                   const SkColor4f& color,
                   bool stroke,
                   std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = stroke ? 6 : 5;
  exported.x = x;
  exported.y = y;
  exported.width = width;
  exported.height = height;
  exported.radius_x = radius_x;
  exported.radius_y = radius_y;
  exported.font_size = stroke_width > 0.0f ? stroke_width : 1.0f;
  AppendSkColor(exported, color);
  exported_draw_ops.push_back(exported);
}

void AppendSaveOp(std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  LiveExportedDrawOp exported;
  exported.type = 8;
  exported_draw_ops.push_back(exported);
}

void AppendRestoreOp(std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  LiveExportedDrawOp exported;
  exported.type = 9;
  exported_draw_ops.push_back(exported);
}

void AppendClipRectOp(const gfx::RectF& rect,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (rect.width() <= 0.0f || rect.height() <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 10;
  exported.x = rect.x();
  exported.y = rect.y();
  exported.width = rect.width();
  exported.height = rect.height();
  exported_draw_ops.push_back(exported);
}

void AppendClipRRectOp(const SkRRect& rrect,
                       float translate_x,
                       float translate_y,
                       SkClipOp clip_op,
                       std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  const SkRect& rect = rrect.getBounds();
  if (!rect.isFinite() || rect.width() <= 0.0f || rect.height() <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 15;
  exported.x = translate_x + rect.x();
  exported.y = translate_y + rect.y();
  exported.width = rect.width();
  exported.height = rect.height();
  for (size_t i = 0; i < exported.corner_radii.size(); ++i) {
    exported.corner_radii[i] =
        rrect.radii(static_cast<SkRRect::Corner>(i));
  }
  exported.radius_x = exported.corner_radii[0].x();
  exported.radius_y = exported.corner_radii[0].y();
  exported.font_size = clip_op == SkClipOp::kDifference ? 1.0f : 0.0f;
  exported_draw_ops.push_back(exported);
}

void AppendSaveLayerAlphaOp(const SkRect& bounds,
                            float translate_x,
                            float translate_y,
                            float alpha,
                            int fallback_width,
                            int fallback_height,
                            std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  LiveExportedDrawOp exported;
  exported.type = 16;
  if (bounds.fLeft == SK_ScalarInfinity) {
    exported.x = 0.0f;
    exported.y = 0.0f;
    exported.width = static_cast<float>(fallback_width);
    exported.height = static_cast<float>(fallback_height);
  } else {
    exported.x = translate_x + bounds.x();
    exported.y = translate_y + bounds.y();
    exported.width = bounds.width();
    exported.height = bounds.height();
  }
  exported.font_size = std::max(0.0f, std::min(1.0f, alpha));
  exported_draw_ops.push_back(exported);
}

void AppendClipPathOp(const SkPath& path,
                      float translate_x,
                      float translate_y,
                      SkClipOp clip_op,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  SkPath translated_path = path.makeOffset(translate_x, translate_y);
  const size_t byte_count = translated_path.writeToMemory(nullptr);
  if (byte_count == 0) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 17;
  exported.font_size = clip_op == SkClipOp::kDifference ? 1.0f : 0.0f;
  exported.path_bytes.resize(byte_count);
  translated_path.writeToMemory(exported.path_bytes.data());
  exported_draw_ops.push_back(std::move(exported));
}

std::vector<uint8_t> SerializeShaderBytes(const cc::PaintFlags& flags) {
  SkPaint paint = flags.ToSkPaint();
  sk_sp<SkShader> shader = paint.refShader();
  if (!shader) {
    return {};
  }
  SkSerialProcs procs;
  sk_sp<SkData> data = shader->serialize(&procs);
  if (!data || data->size() == 0) {
    return {};
  }
  const uint8_t* bytes = static_cast<const uint8_t*>(data->data());
  return std::vector<uint8_t>(bytes, bytes + data->size());
}

uint64_t HashCombineForStandaloneRenderer(uint64_t seed, uint64_t value) {
  return seed ^ (value + 0x9e3779b97f4a7c15ull + (seed << 6) + (seed >> 2));
}

uint64_t HashFloatForStandaloneRenderer(float value) {
  static_assert(sizeof(float) == sizeof(uint32_t));
  uint32_t bits = 0;
  std::memcpy(&bits, &value, sizeof(bits));
  return bits;
}

uint64_t HashChunkPropertyStateForStandaloneRenderer(
    const LiveExportedChunkPropertyState& state) {
  uint64_t hash = 0;
  for (const float value : state.transform_to_root) {
    hash = HashCombineForStandaloneRenderer(hash,
                                            HashFloatForStandaloneRenderer(value));
  }
  hash = HashCombineForStandaloneRenderer(hash, state.transform_is_2d ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(
      hash, state.transform_has_perspective ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(
      hash, state.transform_has_non_translation ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(hash, state.transform_node_id);
  hash = HashCombineForStandaloneRenderer(hash, state.transform_parent_id);
  hash = HashCombineForStandaloneRenderer(hash, state.transform_chain_depth);
  hash = HashCombineForStandaloneRenderer(hash, state.has_clip_rect ? 1u : 0u);
  if (state.has_clip_rect) {
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_y));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_width));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_height));
  }
  hash = HashCombineForStandaloneRenderer(hash, state.clip_node_id);
  hash = HashCombineForStandaloneRenderer(hash, state.clip_parent_id);
  hash = HashCombineForStandaloneRenderer(hash, state.clip_local_transform_id);
  hash = HashCombineForStandaloneRenderer(hash, state.clip_chain_depth);
  hash = HashCombineForStandaloneRenderer(hash, state.clip_has_rounded_clip ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(hash, state.clip_has_path_clip ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(hash, state.effect_node_id);
  hash = HashCombineForStandaloneRenderer(hash, state.effect_parent_id);
  hash = HashCombineForStandaloneRenderer(hash, state.effect_chain_depth);
  hash = HashCombineForStandaloneRenderer(
      hash, HashFloatForStandaloneRenderer(state.effect_opacity));
  hash = HashCombineForStandaloneRenderer(
      hash, state.effect_has_non_default_opacity ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(hash, state.effect_has_filter ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(
      hash, state.effect_has_backdrop_filter ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(hash, state.effect_has_blend_mode ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(hash, state.effect_output_clip_id);
  hash = HashCombineForStandaloneRenderer(hash, state.scroll_node_id);
  hash = HashCombineForStandaloneRenderer(hash, state.scroll_parent_id);
  hash = HashCombineForStandaloneRenderer(hash, state.has_scroll_offset ? 1u : 0u);
  hash = HashCombineForStandaloneRenderer(
      hash, HashFloatForStandaloneRenderer(state.scroll_offset_x));
  hash = HashCombineForStandaloneRenderer(
      hash, HashFloatForStandaloneRenderer(state.scroll_offset_y));
  return hash;
}

void AppendChunkPropertyStateForStandaloneRenderer(
    wtf_size_t chunk_index,
    const PropertyTreeState& chunk_state,
    const gfx::Transform& projection,
    const FloatClipRect& clip,
    std::vector<LiveExportedChunkPropertyState>& property_states) {
  if (property_states.size() <= chunk_index) {
    property_states.resize(chunk_index + 1);
  }
  LiveExportedChunkPropertyState state;
  state.transform_to_root[0] = static_cast<float>(projection.rc(0, 0));
  state.transform_to_root[4] = static_cast<float>(projection.rc(0, 1));
  state.transform_to_root[12] = static_cast<float>(projection.rc(0, 3));
  state.transform_to_root[1] = static_cast<float>(projection.rc(1, 0));
  state.transform_to_root[5] = static_cast<float>(projection.rc(1, 1));
  state.transform_to_root[13] = static_cast<float>(projection.rc(1, 3));
  state.transform_is_2d = projection.Is2dTransform();
  state.transform_has_perspective = !projection.Is2dTransform();
  state.transform_has_non_translation =
      projection.rc(0, 0) != 1.0 || projection.rc(0, 1) != 0.0 ||
      projection.rc(1, 0) != 0.0 || projection.rc(1, 1) != 1.0;
  state.transform_node_id =
      reinterpret_cast<uintptr_t>(&chunk_state.Transform());
  state.clip_node_id = reinterpret_cast<uintptr_t>(&chunk_state.Clip());
  state.effect_node_id = reinterpret_cast<uintptr_t>(&chunk_state.Effect());
  state.transform_chain_depth = state.transform_node_id ? 1u : 0u;
  state.clip_chain_depth = state.clip_node_id ? 1u : 0u;
  state.effect_chain_depth = state.effect_node_id ? 1u : 0u;
  if (!clip.IsInfinite()) {
    const gfx::RectF& rect = clip.Rect();
    state.has_clip_rect = true;
    state.clip_x = rect.x();
    state.clip_y = rect.y();
    state.clip_width = rect.width();
    state.clip_height = rect.height();
  }
  state.state_hash = HashChunkPropertyStateForStandaloneRenderer(state);
  property_states[chunk_index] = state;
}

void AppendTranslateOp(float x,
                       float y,
                       std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (x == 0.0f && y == 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 11;
  exported.x = x;
  exported.y = y;
  exported_draw_ops.push_back(exported);
}

void AppendMatrix2dOp(const gfx::Transform& transform,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (transform.IsIdentity()) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 14;
  exported.x = static_cast<float>(transform.rc(0, 0));
  exported.y = static_cast<float>(transform.rc(0, 1));
  exported.width = static_cast<float>(transform.rc(0, 3));
  exported.height = static_cast<float>(transform.rc(1, 0));
  exported.r = static_cast<float>(transform.rc(1, 1));
  exported.g = static_cast<float>(transform.rc(1, 3));
  exported_draw_ops.push_back(exported);
}

void AppendSkM44Op(const SkM44& matrix,
                   std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (matrix == SkM44()) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = 14;
  exported.x = matrix.rc(0, 0);
  exported.y = matrix.rc(0, 1);
  exported.width = matrix.rc(0, 3);
  exported.height = matrix.rc(1, 0);
  exported.r = matrix.rc(1, 1);
  exported.g = matrix.rc(1, 3);
  exported.debug_label = "retained_matrix_2d_from_paint_record";
  exported_draw_ops.push_back(exported);
}

void AppendBeginChunkOp(wtf_size_t chunk_index,
                        const gfx::Rect& bounds,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  LiveExportedDrawOp exported;
  exported.type = 12;
  exported.x = static_cast<float>(bounds.x());
  exported.y = static_cast<float>(bounds.y());
  exported.width = static_cast<float>(bounds.width());
  exported.height = static_cast<float>(bounds.height());
  exported.font_size = static_cast<float>(chunk_index);
  exported_draw_ops.push_back(exported);
}

void AppendEndChunkOp(std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  LiveExportedDrawOp exported;
  exported.type = 13;
  exported_draw_ops.push_back(exported);
}

void AppendSkRectOpWithFlags(
    const SkRect& rect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!rect.isFinite()) {
    return;
  }
  if (flags.HasShader() && flags.getStyle() != cc::PaintFlags::kStroke_Style) {
    std::vector<uint8_t> shader_bytes = SerializeShaderBytes(flags);
    if (!shader_bytes.empty()) {
      LiveExportedDrawOp exported;
      exported.type = 19;
      exported.x = translate_x + rect.x();
      exported.y = translate_y + rect.y();
      exported.width = rect.width();
      exported.height = rect.height();
      AppendSkColor(exported, flags.getColor4f());
      exported.shader_bytes = std::move(shader_bytes);
      exported_draw_ops.push_back(std::move(exported));
      return;
    }
    const int bitmap_width = SkScalarCeilToInt(rect.width());
    const int bitmap_height = SkScalarCeilToInt(rect.height());
    if (bitmap_width > 0 && bitmap_height > 0) {
      std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                       static_cast<size_t>(bitmap_height) * 4u);
      SkImageInfo info =
          SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                            kPremul_SkAlphaType);
      sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
          info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
      if (surface) {
        SkCanvas* canvas = surface->getCanvas();
        canvas->clear(SK_ColorTRANSPARENT);
        canvas->translate(-rect.x(), -rect.y());
        canvas->drawRect(rect, flags.ToSkPaint());
        LiveExportedDrawOp exported;
        exported.type = 7;
        exported.x = translate_x + rect.x();
        exported.y = translate_y + rect.y();
        exported.width = static_cast<float>(bitmap_width);
        exported.height = static_cast<float>(bitmap_height);
        exported.mask_width = bitmap_width;
        exported.mask_height = bitmap_height;
        exported.rgba_pixels = std::move(rgba_pixels);
        exported.debug_label = "DrawRectOp shader";
        exported_draw_ops.push_back(std::move(exported));
        return;
      }
    }
  }
  if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
    AppendStrokeRectOp(translate_x + rect.x(), translate_y + rect.y(),
                       rect.width(), rect.height(), flags.getStrokeWidth(),
                       flags.getColor4f(), exported_draw_ops);
    return;
  }
  AppendSkRectFillOp(rect, translate_x, translate_y, flags.getColor4f(),
                     exported_draw_ops);
}

void AppendSkIRectOpWithFlags(
    const SkIRect& rect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
    AppendStrokeRectOp(translate_x + static_cast<float>(rect.x()),
                       translate_y + static_cast<float>(rect.y()),
                       static_cast<float>(rect.width()),
                       static_cast<float>(rect.height()),
                       flags.getStrokeWidth(), flags.getColor4f(),
                       exported_draw_ops);
    return;
  }
  AppendSkIRectFillOp(rect, translate_x, translate_y, flags.getColor4f(),
                      exported_draw_ops);
}

void AppendSkRRectOpWithFlags(
    const SkRRect& rrect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  const SkRect rect = rrect.rect();
  if (!rect.isFinite()) {
    return;
  }
  const SkVector radii = rrect.getSimpleRadii();
  if (flags.HasShader() && flags.getStyle() != cc::PaintFlags::kStroke_Style) {
    std::vector<uint8_t> shader_bytes = SerializeShaderBytes(flags);
    if (!shader_bytes.empty()) {
      LiveExportedDrawOp exported;
      exported.type = 20;
      exported.x = translate_x + rect.x();
      exported.y = translate_y + rect.y();
      exported.width = rect.width();
      exported.height = rect.height();
      exported.radius_x = radii.x();
      exported.radius_y = radii.y();
      AppendSkColor(exported, flags.getColor4f());
      exported.shader_bytes = std::move(shader_bytes);
      exported_draw_ops.push_back(std::move(exported));
      return;
    }
    const int bitmap_width = SkScalarCeilToInt(rect.width());
    const int bitmap_height = SkScalarCeilToInt(rect.height());
    if (bitmap_width > 0 && bitmap_height > 0) {
      std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                       static_cast<size_t>(bitmap_height) * 4u);
      SkImageInfo info =
          SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                            kPremul_SkAlphaType);
      sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
          info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
      if (surface) {
        SkCanvas* canvas = surface->getCanvas();
        canvas->clear(SK_ColorTRANSPARENT);
        canvas->translate(-rect.x(), -rect.y());
        canvas->drawRRect(rrect, flags.ToSkPaint());
        LiveExportedDrawOp exported;
        exported.type = 7;
        exported.x = translate_x + rect.x();
        exported.y = translate_y + rect.y();
        exported.width = static_cast<float>(bitmap_width);
        exported.height = static_cast<float>(bitmap_height);
        exported.mask_width = bitmap_width;
        exported.mask_height = bitmap_height;
        exported.rgba_pixels = std::move(rgba_pixels);
        exported.debug_label = "DrawRRectOp shader";
        exported_draw_ops.push_back(std::move(exported));
        return;
      }
    }
  }
  AppendRRectOp(translate_x + rect.x(), translate_y + rect.y(), rect.width(),
                rect.height(), radii.x(), radii.y(), flags.getStrokeWidth(),
                flags.getColor4f(),
                flags.getStyle() == cc::PaintFlags::kStroke_Style,
                exported_draw_ops);
}

void AppendSkPathOpWithFlags(
    const SkPath& path,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  const SkRect bounds = path.getBounds();
  if (!bounds.isFinite()) {
    return;
  }

  const size_t path_byte_count = path.writeToMemory(nullptr);
  if (path_byte_count == 0) {
    return;
  }

  LiveExportedDrawOp exported;
  exported.type = 21;
  exported.x = translate_x;
  exported.y = translate_y;
  exported.width = bounds.width();
  exported.height = bounds.height();
  exported.font_size = flags.getStyle() == cc::PaintFlags::kStroke_Style
                           ? std::max<SkScalar>(1.0f, flags.getStrokeWidth())
                           : 0.0f;
  AppendSkColor(exported, flags.getColor4f());
  exported.path_bytes.resize(path_byte_count);
  path.writeToMemory(exported.path_bytes.data());

  if (flags.HasShader()) {
    exported.shader_bytes = SerializeShaderBytes(flags);
  }

  exported_draw_ops.push_back(std::move(exported));
}
void AppendTextBlobOp(const cc::DrawTextBlobOp& text_op,
                      int fallback_x,
                      int fallback_y,
                      int fallback_width,
                      int fallback_height,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!text_op.blob) {
    return;
  }
  SkSerialProcs procs;
  sk_sp<SkData> serialized_blob = text_op.blob->serialize(procs);
  if (serialized_blob && serialized_blob->size() > 0) {
    LiveExportedDrawOp exported;
    exported.type = 18;
    exported.x = text_op.x;
    exported.y = text_op.y;
    AppendSkColor(exported, text_op.flags.getColor4f());
    const uint8_t* bytes =
        static_cast<const uint8_t*>(serialized_blob->data());
    exported.text_blob_bytes.assign(bytes, bytes + serialized_blob->size());
    exported_draw_ops.push_back(std::move(exported));
    return;
  }
  const float absolute_x = text_op.x;
  const float absolute_y = text_op.y;
  const SkRect bounds = text_op.blob->bounds().makeOffset(absolute_x,
                                                          absolute_y);
  SkIRect ibounds = bounds.roundOut();
  if (ibounds.width() <= 0 || ibounds.height() <= 0) {
    ibounds = SkIRect::MakeXYWH(fallback_x, fallback_y, fallback_width,
                                fallback_height);
  }
  float export_offset_x = 0.0f;
  float export_offset_y = 0.0f;
  if (fallback_width > 0 && fallback_height > 0) {
    const SkIRect fallback_bounds =
        SkIRect::MakeXYWH(fallback_x, fallback_y, fallback_width,
                          fallback_height);
    SkIRect intersection;
    if (!intersection.intersect(ibounds, fallback_bounds)) {
      export_offset_x = static_cast<float>(fallback_x);
      export_offset_y = static_cast<float>(fallback_y);
    }
  }
  const int mask_width = std::max(0, ibounds.width());
  const int mask_height = std::max(0, ibounds.height());
  if (mask_width <= 0 || mask_height <= 0) {
    return;
  }

  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(mask_width) *
                                   static_cast<size_t>(mask_height) * 4u,
                                   0);
  SkImageInfo mask_info = SkImageInfo::MakeN32Premul(mask_width, mask_height);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      mask_info, rgba_pixels.data(), static_cast<size_t>(mask_width) * 4u);
  if (!surface) {
    return;
  }
  SkCanvas* canvas = surface->getCanvas();
  canvas->clear(SK_ColorTRANSPARENT);
  canvas->translate(-static_cast<SkScalar>(ibounds.left()),
                    -static_cast<SkScalar>(ibounds.top()));
  text_op.Raster(canvas, cc::PlaybackParams());
  int outline_path_count = 0;
  int nonempty_outline_path_count = 0;

  std::vector<uint8_t> mask_pixels(static_cast<size_t>(mask_width) *
                                       static_cast<size_t>(mask_height),
                                   0);
  size_t nonzero_alpha_count = 0;
  for (int row = 0; row < mask_height; ++row) {
    for (int col = 0; col < mask_width; ++col) {
      const size_t pixel_index =
          static_cast<size_t>(row) * static_cast<size_t>(mask_width) +
          static_cast<size_t>(col);
      const size_t rgba_offset = pixel_index * 4u;
      const uint8_t alpha = rgba_pixels[rgba_offset + 3u];
      const uint8_t color_coverage =
          std::max(rgba_pixels[rgba_offset + 0u],
                   std::max(rgba_pixels[rgba_offset + 1u],
                            rgba_pixels[rgba_offset + 2u]));
      const uint8_t coverage = alpha != 0 ? alpha : color_coverage;
      mask_pixels[pixel_index] = coverage;
      if (coverage != 0) {
        ++nonzero_alpha_count;
      }
    }
  }

  LiveExportedDrawOp bitmap_export;
  bitmap_export.type = 7;
  AppendSkColor(bitmap_export, text_op.flags.getColor4f());
  bitmap_export.x = export_offset_x + static_cast<float>(ibounds.left());
  bitmap_export.y = export_offset_y + static_cast<float>(ibounds.top());
  bitmap_export.width = static_cast<float>(mask_width);
  bitmap_export.height = static_cast<float>(mask_height);
  bitmap_export.mask_width = mask_width;
  bitmap_export.mask_height = mask_height;
  bitmap_export.rgba_pixels = std::move(rgba_pixels);
  bitmap_export.debug_label = "DrawTextBlobOp fallback";
  exported_draw_ops.push_back(std::move(bitmap_export));
}

bool AppendPaintOpBitmapResource(
    const cc::PaintOp& op,
    SkRect bounds,
    float translate_x,
    float translate_y,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!bounds.isFinite() || bounds.width() <= 0.0f ||
      bounds.height() <= 0.0f) {
    return false;
  }
  constexpr int kMaxOpBitmapPixels = 4 * 1024 * 1024;
  bounds.roundOut(&bounds);
  const int bitmap_width = SkScalarCeilToInt(bounds.width());
  const int bitmap_height = SkScalarCeilToInt(bounds.height());
  if (bitmap_width <= 0 || bitmap_height <= 0 ||
      static_cast<int64_t>(bitmap_width) *
              static_cast<int64_t>(bitmap_height) >
          kMaxOpBitmapPixels) {
    return false;
  }

  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                   static_cast<size_t>(bitmap_height) * 4u);
  SkImageInfo info =
      SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
  if (!surface) {
    return false;
  }

  SkCanvas* canvas = surface->getCanvas();
  canvas->clear(SK_ColorTRANSPARENT);
  canvas->translate(-bounds.x(), -bounds.y());
  op.Raster(canvas, cc::PlaybackParams());

  LiveExportedDrawOp exported;
  exported.type = 7;
  exported.x = translate_x + bounds.x();
  exported.y = translate_y + bounds.y();
  exported.width = static_cast<float>(bitmap_width);
  exported.height = static_cast<float>(bitmap_height);
  exported.mask_width = bitmap_width;
  exported.mask_height = bitmap_height;
  exported.rgba_pixels = std::move(rgba_pixels);
  exported.debug_label = cc::PaintOpTypeToString(op.GetType());
  exported_draw_ops.push_back(std::move(exported));
  return true;
}

bool SkM44IsIdentityOr2dTranslation(const SkM44& matrix) {
  return matrix.rc(0, 0) == 1.0f && matrix.rc(0, 1) == 0.0f &&
         matrix.rc(0, 2) == 0.0f && matrix.rc(1, 0) == 0.0f &&
         matrix.rc(1, 1) == 1.0f && matrix.rc(1, 2) == 0.0f &&
         matrix.rc(2, 0) == 0.0f && matrix.rc(2, 1) == 0.0f &&
         matrix.rc(2, 2) == 1.0f && matrix.rc(2, 3) == 0.0f &&
         matrix.rc(3, 0) == 0.0f && matrix.rc(3, 1) == 0.0f &&
         matrix.rc(3, 2) == 0.0f && matrix.rc(3, 3) == 1.0f;
}

gfx::Transform DirectTransformToRootForStandaloneRenderer(
    const PropertyTreeState& state,
    uint32_t* chain_depth,
    bool* has_non_translation);

bool AppendPaintRecordExtractedOps(
    const cc::PaintRecord& record,
    float initial_translate_x,
    float initial_translate_y,
    int fallback_width,
    int fallback_height,
    std::vector<LiveExportedDrawOp>& exported_draw_ops,
    std::vector<std::string>& diagnostics,
    bool suppress_clip_ops_for_non_translation_transform = false) {
  struct PaintRecordState {
    int save_marker = 0;
  };
  std::vector<PaintRecordState> state_stack;
  float translate_x = 0.0f;
  float translate_y = 0.0f;
  bool complete = true;
  if (initial_translate_x != 0.0f || initial_translate_y != 0.0f) {
    AppendTranslateOp(initial_translate_x, initial_translate_y,
                      exported_draw_ops);
  }

  const auto mark_unsupported = [&](const cc::PaintOp& op) {
    complete = false;
    diagnostics.push_back(
        "paint_op_extraction unsupported op=" +
        std::string(cc::PaintOpTypeToString(op.GetType())));
  };

  for (const cc::PaintOp& op : record) {
    switch (op.GetType()) {
      case cc::PaintOpType::kNoop:
        break;
      case cc::PaintOpType::kSave:
        state_stack.push_back({});
        AppendSaveOp(exported_draw_ops);
        break;
      case cc::PaintOpType::kSaveLayer: {
        const auto& save_layer_op = static_cast<const cc::SaveLayerOp&>(op);
        state_stack.push_back({});
        AppendSaveLayerAlphaOp(save_layer_op.bounds, 0.0f, 0.0f, 255,
                               fallback_width, fallback_height,
                               exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kSaveLayerAlpha: {
        const auto& save_layer_op =
            static_cast<const cc::SaveLayerAlphaOp&>(op);
        if (!save_layer_op.IsValid()) {
          mark_unsupported(op);
          break;
        }
        state_stack.push_back({});
        AppendSaveLayerAlphaOp(save_layer_op.bounds, 0.0f, 0.0f,
                               save_layer_op.alpha, fallback_width,
                               fallback_height, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kRestore:
        if (!state_stack.empty()) {
          state_stack.pop_back();
        }
        AppendRestoreOp(exported_draw_ops);
        break;
      case cc::PaintOpType::kTranslate: {
        const auto& translate_op = static_cast<const cc::TranslateOp&>(op);
        AppendTranslateOp(translate_op.dx, translate_op.dy, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kScale: {
        const auto& scale_op = static_cast<const cc::ScaleOp&>(op);
        AppendSkM44Op(SkM44::Scale(scale_op.sx, scale_op.sy),
                      exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kRotate: {
        const auto& rotate_op = static_cast<const cc::RotateOp&>(op);
        AppendSkM44Op(SkM44::Rotate({0.0f, 0.0f, 1.0f}, rotate_op.degrees),
                      exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kConcat: {
        const auto& concat_op = static_cast<const cc::ConcatOp&>(op);
        if (!concat_op.matrix.isFinite()) {
          mark_unsupported(op);
          break;
        }
        AppendSkM44Op(concat_op.matrix, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kSetMatrix: {
        const auto& matrix_op = static_cast<const cc::SetMatrixOp&>(op);
        if (!matrix_op.matrix.isFinite()) {
          mark_unsupported(op);
          break;
        }
        AppendSkM44Op(matrix_op.matrix, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kClipRect: {
        if (suppress_clip_ops_for_non_translation_transform) {
          diagnostics.push_back(
              "paint_op_extraction retained transform but suppressed ClipRect "
              "inside non-translation chunk");
          break;
        }
        const auto& clip_op = static_cast<const cc::ClipRectOp&>(op);
        if (clip_op.op != SkClipOp::kIntersect || !clip_op.rect.isFinite()) {
          mark_unsupported(op);
          break;
        }
        AppendClipRectOp(
            gfx::RectF(clip_op.rect.x(), clip_op.rect.y(), clip_op.rect.width(),
                       clip_op.rect.height()),
            exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kClipRRect: {
        if (suppress_clip_ops_for_non_translation_transform) {
          diagnostics.push_back(
              "paint_op_extraction retained transform but suppressed ClipRRect "
              "inside non-translation chunk");
          break;
        }
        const auto& clip_op = static_cast<const cc::ClipRRectOp&>(op);
        if ((clip_op.op != SkClipOp::kIntersect &&
             clip_op.op != SkClipOp::kDifference) ||
            !clip_op.rrect.isValid()) {
          diagnostics.push_back(
              "paint_op_extraction unsupported ClipRRect detail op=" +
              std::to_string(static_cast<int>(clip_op.op)) +
              " valid=" + std::to_string(clip_op.rrect.isValid() ? 1 : 0) +
              " type=" + std::to_string(clip_op.rrect.getType()));
          mark_unsupported(op);
          break;
        }
        AppendClipRRectOp(clip_op.rrect, translate_x, translate_y, clip_op.op,
                          exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kClipPath: {
        if (suppress_clip_ops_for_non_translation_transform) {
          diagnostics.push_back(
              "paint_op_extraction retained transform but suppressed ClipPath "
              "inside non-translation chunk");
          break;
        }
        const auto& clip_op = static_cast<const cc::ClipPathOp&>(op);
        if ((clip_op.op != SkClipOp::kIntersect &&
             clip_op.op != SkClipOp::kDifference) ||
            !clip_op.IsValid()) {
          mark_unsupported(op);
          break;
        }
        AppendClipPathOp(clip_op.path, translate_x, translate_y, clip_op.op,
                         exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kSaveLayerFilters:
        mark_unsupported(op);
        break;
      case cc::PaintOpType::kDrawColor: {
        const auto& color_op = static_cast<const cc::DrawColorOp&>(op);
        AppendFillRectOp(0.0f, 0.0f, static_cast<float>(fallback_width),
                         static_cast<float>(fallback_height), color_op.color,
                         exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawImage: {
        const auto& image_op = static_cast<const cc::DrawImageOp&>(op);
        if (!AppendPaintOpBitmapResource(
                op,
                SkRect::MakeXYWH(image_op.left, image_op.top,
                                 static_cast<SkScalar>(image_op.image.width()),
                                 static_cast<SkScalar>(
                                     image_op.image.height())),
                translate_x, translate_y, exported_draw_ops)) {
          mark_unsupported(op);
        }
        break;
      }
      case cc::PaintOpType::kDrawImageRect: {
        const auto& image_op = static_cast<const cc::DrawImageRectOp&>(op);
        if (!AppendPaintOpBitmapResource(op, image_op.dst, translate_x,
                                         translate_y, exported_draw_ops)) {
          mark_unsupported(op);
        }
        break;
      }
      case cc::PaintOpType::kDrawIRect:
        AppendSkIRectOpWithFlags(static_cast<const cc::DrawIRectOp&>(op).rect,
                                 translate_x, translate_y,
                                 static_cast<const cc::DrawIRectOp&>(op).flags,
                                 exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawDRRect: {
        const auto& drrect_op = static_cast<const cc::DrawDRRectOp&>(op);
        SkPath path = SkPathBuilder(SkPathFillType::kEvenOdd)
                          .addRRect(drrect_op.outer)
                          .addRRect(drrect_op.inner)
                          .detach();
        AppendSkPathOpWithFlags(path, translate_x, translate_y,
                                drrect_op.flags, exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawRect:
        AppendSkRectOpWithFlags(static_cast<const cc::DrawRectOp&>(op).rect,
                                translate_x, translate_y,
                                static_cast<const cc::DrawRectOp&>(op).flags,
                                exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawArc: {
        const auto& arc_op = static_cast<const cc::DrawArcOp&>(op);
        if (!AppendPaintOpBitmapResource(op, arc_op.oval, translate_x,
                                         translate_y, exported_draw_ops)) {
          mark_unsupported(op);
        }
        break;
      }
      case cc::PaintOpType::kDrawArcLite: {
        const auto& arc_op = static_cast<const cc::DrawArcLiteOp&>(op);
        if (!AppendPaintOpBitmapResource(op, arc_op.oval, translate_x,
                                         translate_y, exported_draw_ops)) {
          mark_unsupported(op);
        }
        break;
      }
      case cc::PaintOpType::kDrawLine: {
        const auto& line_op = static_cast<const cc::DrawLineOp&>(op);
        SkPath path = SkPathBuilder()
                          .moveTo(line_op.x0, line_op.y0)
                          .lineTo(line_op.x1, line_op.y1)
                          .detach();
        cc::PaintFlags flags = line_op.flags;
        flags.setStyle(cc::PaintFlags::kStroke_Style);
        AppendSkPathOpWithFlags(path, translate_x, translate_y, flags,
                                exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawLineLite: {
        const auto& line_op = static_cast<const cc::DrawLineLiteOp&>(op);
        SkPath path = SkPathBuilder()
                          .moveTo(line_op.x0, line_op.y0)
                          .lineTo(line_op.x1, line_op.y1)
                          .detach();
        cc::PaintFlags flags(line_op.core_paint_flags);
        flags.setStyle(cc::PaintFlags::kStroke_Style);
        AppendSkPathOpWithFlags(path, translate_x, translate_y, flags,
                                exported_draw_ops);
        break;
      }
      case cc::PaintOpType::kDrawRRect:
        AppendSkRRectOpWithFlags(
            static_cast<const cc::DrawRRectOp&>(op).rrect, translate_x,
            translate_y, static_cast<const cc::DrawRRectOp&>(op).flags,
            exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawOval:
        AppendSkRectOpWithFlags(static_cast<const cc::DrawOvalOp&>(op).oval,
                                translate_x, translate_y,
                                static_cast<const cc::DrawOvalOp&>(op).flags,
                                exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawPath:
        AppendSkPathOpWithFlags(static_cast<const cc::DrawPathOp&>(op).path,
                                translate_x, translate_y,
                                static_cast<const cc::DrawPathOp&>(op).flags,
                                exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawTextBlob:
        AppendTextBlobOp(static_cast<const cc::DrawTextBlobOp&>(op),
                         static_cast<int>(translate_x),
                         static_cast<int>(translate_y), fallback_width,
                         fallback_height, exported_draw_ops);
        break;
      case cc::PaintOpType::kDrawRecord:
        if (!AppendPaintRecordExtractedOps(
                static_cast<const cc::DrawRecordOp&>(op).record, translate_x,
                translate_y, fallback_width, fallback_height,
                exported_draw_ops, diagnostics,
                suppress_clip_ops_for_non_translation_transform)) {
          complete = false;
        }
        break;
      default:
        mark_unsupported(op);
        break;
    }
  }

  return complete;
}

bool AppendPaintArtifactExtractedOps(
    const PaintArtifact& artifact,
    int viewport_width,
    int viewport_height,
    std::vector<LiveExportedDrawOp>& exported_draw_ops,
    std::vector<LiveExportedChunkPropertyState>& property_states,
    std::vector<std::string>& diagnostics) {
  const DisplayItemList& display_items = artifact.GetDisplayItemList();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  bool complete = true;
  for (wtf_size_t chunk_index = 0; chunk_index < chunks.size();
       ++chunk_index) {
    const PaintChunk& chunk = chunks[chunk_index];
    const PropertyTreeState chunk_state = chunk.properties.Unalias();
    bool projection_has_non_translation = false;
    gfx::Transform projection = DirectTransformToRootForStandaloneRenderer(
        chunk_state, nullptr, &projection_has_non_translation);
    if (!projection.Is2dTransform()) {
      diagnostics.push_back(
          "paint_op_extraction unsupported chunk transform at index=" +
          std::to_string(chunk_index));
      complete = false;
      continue;
    }
    AppendBeginChunkOp(chunk_index, chunk.bounds, exported_draw_ops);
    AppendSaveOp(exported_draw_ops);
    const FloatClipRect clip =
        projection_has_non_translation
            ? FloatClipRect()
            : GeometryMapper::LocalToAncestorClipRect(
                  chunk_state, PropertyTreeState::Root());
    AppendChunkPropertyStateForStandaloneRenderer(chunk_index, chunk_state,
                                                  projection, clip,
                                                  property_states);
    if (!clip.IsInfinite()) {
      AppendClipRectOp(clip.Rect(), exported_draw_ops);
    }
    AppendMatrix2dOp(projection, exported_draw_ops);
    for (wtf_size_t item_index = chunk.begin_index;
         item_index < chunk.end_index && item_index < display_items.size();
         ++item_index) {
      const auto* drawing =
          DynamicTo<DrawingDisplayItem>(display_items[item_index]);
      if (!drawing) {
        continue;
      }
      if (!AppendPaintRecordExtractedOps(
              drawing->GetPaintRecord(), 0.0f, 0.0f, viewport_width,
              viewport_height, exported_draw_ops, diagnostics,
              projection_has_non_translation)) {
        complete = false;
      }
    }
    AppendRestoreOp(exported_draw_ops);
    AppendEndChunkOp(exported_draw_ops);
  }
  return complete && !exported_draw_ops.empty();
}

bool AppendPaintArtifactOracleBitmapOp(
    const PaintArtifact& artifact,
    int viewport_width,
    int viewport_height,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (viewport_width <= 0 || viewport_height <= 0) {
    return false;
  }
  constexpr int kMaxBitmapExportDimension = 4096;
  constexpr int kMaxBitmapExportPixels = 16 * 1024 * 1024;
  const int bitmap_width =
      std::min(viewport_width, kMaxBitmapExportDimension);
  const int bitmap_height =
      std::min(viewport_height, kMaxBitmapExportDimension);
  if (bitmap_width <= 0 || bitmap_height <= 0 ||
      static_cast<int64_t>(bitmap_width) *
              static_cast<int64_t>(bitmap_height) >
          kMaxBitmapExportPixels) {
    return false;
  }

  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(bitmap_width) *
                                   static_cast<size_t>(bitmap_height) * 4u);
  SkImageInfo info =
      SkImageInfo::Make(bitmap_width, bitmap_height, kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  sk_sp<SkSurface> surface = SkSurfaces::WrapPixels(
      info, rgba_pixels.data(), static_cast<size_t>(bitmap_width) * 4u);
  if (!surface) {
    return false;
  }

  SkCanvas* canvas = surface->getCanvas();
  canvas->clear(SK_ColorTRANSPARENT);

  const DisplayItemList& display_items = artifact.GetDisplayItemList();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  for (wtf_size_t chunk_index = 0; chunk_index < chunks.size();
       ++chunk_index) {
    const PaintChunk& chunk = chunks[chunk_index];
    const PropertyTreeState chunk_state = chunk.properties.Unalias();
    gfx::Transform projection;
    if (!GeometryMapper::SourceToDestinationProjection(
            chunk_state.Transform(), PropertyTreeState::Root().Transform(),
            projection)) {
      continue;
    }

    canvas->save();
    const FloatClipRect clip = GeometryMapper::LocalToAncestorClipRect(
        chunk_state, PropertyTreeState::Root());
    if (!clip.IsInfinite()) {
      const gfx::RectF& clip_rect = clip.Rect();
      canvas->clipRect(
          SkRect::MakeXYWH(clip_rect.x(), clip_rect.y(),
                           clip_rect.width(), clip_rect.height()),
          SkClipOp::kIntersect, true);
    }
    canvas->concat(gfx::TransformToSkM44(projection));
    for (wtf_size_t item_index = chunk.begin_index;
         item_index < chunk.end_index && item_index < display_items.size();
         ++item_index) {
      const auto* drawing = DynamicTo<DrawingDisplayItem>(display_items[item_index]);
      if (!drawing) {
        continue;
      }
      drawing->GetPaintRecord().Playback(canvas);
    }
    canvas->restore();
  }

  LiveExportedDrawOp exported;
  exported.type = 7;
  exported.x = 0.0f;
  exported.y = 0.0f;
  exported.width = static_cast<float>(bitmap_width);
  exported.height = static_cast<float>(bitmap_height);
  exported.mask_width = bitmap_width;
  exported.mask_height = bitmap_height;
  exported.rgba_pixels = std::move(rgba_pixels);
  exported_draw_ops.push_back(std::move(exported));
  return true;
}

bool IsPaintOpCurrentlyExtracted(cc::PaintOpType type) {
  switch (type) {
    case cc::PaintOpType::kSave:
    case cc::PaintOpType::kRestore:
    case cc::PaintOpType::kSaveLayer:
    case cc::PaintOpType::kSaveLayerAlpha:
    case cc::PaintOpType::kSaveLayerFilters:
    case cc::PaintOpType::kTranslate:
    case cc::PaintOpType::kScale:
    case cc::PaintOpType::kRotate:
    case cc::PaintOpType::kConcat:
    case cc::PaintOpType::kSetMatrix:
    case cc::PaintOpType::kClipRect:
    case cc::PaintOpType::kClipRRect:
    case cc::PaintOpType::kClipPath:
    case cc::PaintOpType::kDrawColor:
    case cc::PaintOpType::kDrawRect:
    case cc::PaintOpType::kDrawIRect:
    case cc::PaintOpType::kDrawRRect:
    case cc::PaintOpType::kDrawDRRect:
    case cc::PaintOpType::kDrawOval:
    case cc::PaintOpType::kDrawArc:
    case cc::PaintOpType::kDrawArcLite:
    case cc::PaintOpType::kDrawLine:
    case cc::PaintOpType::kDrawLineLite:
    case cc::PaintOpType::kDrawPath:
    case cc::PaintOpType::kDrawImage:
    case cc::PaintOpType::kDrawImageRect:
    case cc::PaintOpType::kDrawTextBlob:
    case cc::PaintOpType::kDrawRecord:
    case cc::PaintOpType::kNoop:
      return true;
    default:
      return false;
  }
}

void AppendPaintRecordAudit(const cc::PaintRecord& record,
                            std::map<std::string, int>& op_histogram,
                            std::map<std::string, int>& unsupported_histogram,
                            int& op_count) {
  for (const cc::PaintOp& op : record) {
    const std::string op_name = cc::PaintOpTypeToString(op.GetType());
    ++op_histogram[op_name];
    ++op_count;
    if (!IsPaintOpCurrentlyExtracted(op.GetType())) {
      ++unsupported_histogram[op_name];
    }
    if (op.GetType() == cc::PaintOpType::kDrawRecord) {
      AppendPaintRecordAudit(static_cast<const cc::DrawRecordOp&>(op).record,
                             op_histogram, unsupported_histogram, op_count);
    }
  }
}

std::string MapToJsonObject(const std::map<std::string, int>& values) {
  std::string json = "{";
  bool first = true;
  for (const auto& [key, value] : values) {
    if (!first) {
      json += ",";
    }
    first = false;
    json += "\"";
    json += key;
    json += "\":";
    json += std::to_string(value);
  }
  json += "}";
  return json;
}

std::string JsonEscapeForStandaloneRenderer(const std::string& value) {
  std::ostringstream out;
  for (const unsigned char c : value) {
    switch (c) {
      case '"':
        out << "\\\"";
        break;
      case '\\':
        out << "\\\\";
        break;
      case '\b':
        out << "\\b";
        break;
      case '\f':
        out << "\\f";
        break;
      case '\n':
        out << "\\n";
        break;
      case '\r':
        out << "\\r";
        break;
      case '\t':
        out << "\\t";
        break;
      default:
        if (c < 0x20) {
          out << "\\u" << std::hex << std::setw(4) << std::setfill('0')
              << static_cast<int>(c) << std::dec;
        } else {
          out << static_cast<char>(c);
        }
        break;
    }
  }
  return out.str();
}

std::string JsonStringForStandaloneRenderer(const std::string& value) {
  return "\"" + JsonEscapeForStandaloneRenderer(value) + "\"";
}

std::string BlinkStringToStdStringForStandaloneRenderer(const String& value) {
  return value.Utf8();
}

std::string RectJsonForStandaloneRenderer(const gfx::Rect& rect) {
  std::ostringstream out;
  out << "[" << rect.x() << "," << rect.y() << "," << rect.width() << ","
      << rect.height() << "]";
  return out.str();
}

std::string RectFJsonForStandaloneRenderer(const gfx::RectF& rect) {
  std::ostringstream out;
  out << "[" << rect.x() << "," << rect.y() << "," << rect.width() << ","
      << rect.height() << "]";
  return out.str();
}

std::string SkRectJsonForStandaloneRenderer(const SkRect& rect) {
  std::ostringstream out;
  out << "[" << rect.x() << "," << rect.y() << "," << rect.width() << ","
      << rect.height() << "]";
  return out.str();
}

std::string MatrixJsonForStandaloneRenderer(const gfx::Transform& transform) {
  SkM44 matrix = gfx::TransformToSkM44(transform);
  std::ostringstream out;
  out << "[";
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      if (row != 0 || col != 0) {
        out << ",";
      }
      out << matrix.rc(row, col);
    }
  }
  out << "]";
  return out.str();
}

std::string MatrixJsonForStandaloneRenderer(const SkM44& matrix) {
  std::ostringstream out;
  out << "[";
  for (int row = 0; row < 4; ++row) {
    for (int col = 0; col < 4; ++col) {
      if (row != 0 || col != 0) {
        out << ",";
      }
      out << matrix.rc(row, col);
    }
  }
  out << "]";
  return out.str();
}

bool SkM44IsIdentityOr2dTranslation(const SkM44& matrix);

gfx::Transform DirectTransformToRootForStandaloneRenderer(
    const PropertyTreeState& state,
    uint32_t* chain_depth,
    bool* has_non_translation) {
  std::vector<const TransformPaintPropertyNode*> chain;
  const auto* node = &state.Transform();
  const auto* root = &PropertyTreeState::Root().Transform();
  while (node && node != root && chain.size() < 64) {
    chain.push_back(node);
    node = node->UnaliasedParent();
  }
  gfx::Transform transform;
  if (chain_depth) {
    *chain_depth = static_cast<uint32_t>(chain.size());
  }
  if (has_non_translation) {
    *has_non_translation = false;
  }
  for (auto it = chain.rbegin(); it != chain.rend(); ++it) {
    const TransformPaintPropertyNode* transform_node = *it;
    gfx::Transform local = transform_node->MatrixWithOriginApplied();
    if (has_non_translation &&
        !SkM44IsIdentityOr2dTranslation(gfx::TransformToSkM44(local))) {
      *has_non_translation = true;
    }
    transform.PreConcat(local);
  }
  return transform;
}

uint64_t HashStringForStandaloneRenderer(const std::string& value) {
  uint64_t hash = 1469598103934665603ull;
  for (const unsigned char c : value) {
    hash ^= c;
    hash *= 1099511628211ull;
  }
  return hash;
}

bool IsVisualPaintOpForStandaloneRenderer(cc::PaintOpType type) {
  switch (type) {
    case cc::PaintOpType::kDrawColor:
    case cc::PaintOpType::kDrawRect:
    case cc::PaintOpType::kDrawIRect:
    case cc::PaintOpType::kDrawRRect:
    case cc::PaintOpType::kDrawDRRect:
    case cc::PaintOpType::kDrawOval:
    case cc::PaintOpType::kDrawArc:
    case cc::PaintOpType::kDrawArcLite:
    case cc::PaintOpType::kDrawLine:
    case cc::PaintOpType::kDrawLineLite:
    case cc::PaintOpType::kDrawPath:
    case cc::PaintOpType::kDrawImage:
    case cc::PaintOpType::kDrawImageRect:
    case cc::PaintOpType::kDrawTextBlob:
    case cc::PaintOpType::kDrawRecord:
    case cc::PaintOpType::kDrawVertices:
    case cc::PaintOpType::kDrawSlug:
    case cc::PaintOpType::kDrawSkottie:
    case cc::PaintOpType::kDrawScrollingContents:
      return true;
    default:
      return false;
  }
}

const cc::PaintFlags* PaintFlagsForStandaloneRenderer(const cc::PaintOp& op) {
  switch (op.GetType()) {
    case cc::PaintOpType::kDrawDRRect:
      return &static_cast<const cc::DrawDRRectOp&>(op).flags;
    case cc::PaintOpType::kDrawImage:
      return &static_cast<const cc::DrawImageOp&>(op).flags;
    case cc::PaintOpType::kDrawImageRect:
      return &static_cast<const cc::DrawImageRectOp&>(op).flags;
    case cc::PaintOpType::kDrawIRect:
      return &static_cast<const cc::DrawIRectOp&>(op).flags;
    case cc::PaintOpType::kDrawLine:
      return &static_cast<const cc::DrawLineOp&>(op).flags;
    case cc::PaintOpType::kDrawArc:
      return &static_cast<const cc::DrawArcOp&>(op).flags;
    case cc::PaintOpType::kDrawOval:
      return &static_cast<const cc::DrawOvalOp&>(op).flags;
    case cc::PaintOpType::kDrawPath:
      return &static_cast<const cc::DrawPathOp&>(op).flags;
    case cc::PaintOpType::kDrawRect:
      return &static_cast<const cc::DrawRectOp&>(op).flags;
    case cc::PaintOpType::kDrawRRect:
      return &static_cast<const cc::DrawRRectOp&>(op).flags;
    case cc::PaintOpType::kDrawTextBlob:
      return &static_cast<const cc::DrawTextBlobOp&>(op).flags;
    default:
      return nullptr;
  }
}

std::string PaintOpGeometryJsonForStandaloneRenderer(const cc::PaintOp& op) {
  switch (op.GetType()) {
    case cc::PaintOpType::kDrawRect:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawRectOp&>(op).rect);
    case cc::PaintOpType::kDrawIRect: {
      const SkIRect& rect = static_cast<const cc::DrawIRectOp&>(op).rect;
      return SkRectJsonForStandaloneRenderer(
          SkRect::MakeXYWH(rect.x(), rect.y(), rect.width(), rect.height()));
    }
    case cc::PaintOpType::kDrawRRect:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawRRectOp&>(op).rrect.rect());
    case cc::PaintOpType::kDrawDRRect:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawDRRectOp&>(op).outer.rect());
    case cc::PaintOpType::kDrawOval:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawOvalOp&>(op).oval);
    case cc::PaintOpType::kDrawArc:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawArcOp&>(op).oval);
    case cc::PaintOpType::kDrawArcLite:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawArcLiteOp&>(op).oval);
    case cc::PaintOpType::kDrawImage: {
      const auto& image = static_cast<const cc::DrawImageOp&>(op);
      return SkRectJsonForStandaloneRenderer(SkRect::MakeXYWH(
          image.left, image.top, static_cast<SkScalar>(image.image.width()),
          static_cast<SkScalar>(image.image.height())));
    }
    case cc::PaintOpType::kDrawImageRect:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::DrawImageRectOp&>(op).dst);
    case cc::PaintOpType::kDrawTextBlob: {
      const auto& text = static_cast<const cc::DrawTextBlobOp&>(op);
      return SkRectJsonForStandaloneRenderer(
          SkRect::MakeXYWH(text.x, text.y, 0.0f, 0.0f));
    }
    case cc::PaintOpType::kClipRect:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::ClipRectOp&>(op).rect);
    case cc::PaintOpType::kClipRRect:
      return SkRectJsonForStandaloneRenderer(
          static_cast<const cc::ClipRRectOp&>(op).rrect.rect());
    case cc::PaintOpType::kTranslate: {
      const auto& translate = static_cast<const cc::TranslateOp&>(op);
      return "[" + std::to_string(translate.dx) + "," +
             std::to_string(translate.dy) + "]";
    }
    case cc::PaintOpType::kScale: {
      const auto& scale = static_cast<const cc::ScaleOp&>(op);
      return "[" + std::to_string(scale.sx) + "," +
             std::to_string(scale.sy) + "]";
    }
    case cc::PaintOpType::kRotate:
      return "[" +
             std::to_string(static_cast<const cc::RotateOp&>(op).degrees) +
             "]";
    case cc::PaintOpType::kConcat:
      return MatrixJsonForStandaloneRenderer(
          static_cast<const cc::ConcatOp&>(op).matrix);
    case cc::PaintOpType::kSetMatrix:
      return MatrixJsonForStandaloneRenderer(
          static_cast<const cc::SetMatrixOp&>(op).matrix);
    default:
      return "null";
  }
}

struct RawPaintRecordAudit {
  std::map<std::string, int> top_level_histogram;
  std::map<std::string, int> recursive_histogram;
  std::map<std::string, int> unsupported_histogram;
  std::map<std::string, int> fallback_histogram;
  int paint_op_count = 0;
  int recursive_paint_op_count = 0;
  int visual_op_count = 0;
  int text_blob_count = 0;
  int image_count = 0;
  int shader_count = 0;
  int path_count = 0;
  int filter_count = 0;
  bool has_non_text_visual_paint = false;
  bool has_non_translation_transform = false;
  bool has_effect_opacity = false;
};

bool IsPaintOpCurrentlyExtracted(cc::PaintOpType type);

void AppendPaintRecordAuditJson(const cc::PaintRecord& record,
                                RawPaintRecordAudit& audit,
                                std::ostringstream* paint_ops_json,
                                bool top_level,
                                int depth = 0) {
  bool first = true;
  for (const cc::PaintOp& op : record) {
    const std::string op_name = cc::PaintOpTypeToString(op.GetType());
    if (top_level) {
      ++audit.top_level_histogram[op_name];
      ++audit.paint_op_count;
    }
    ++audit.recursive_histogram[op_name];
    ++audit.recursive_paint_op_count;
    if (!IsPaintOpCurrentlyExtracted(op.GetType())) {
      ++audit.unsupported_histogram[op_name];
    }
    if (IsVisualPaintOpForStandaloneRenderer(op.GetType())) {
      ++audit.visual_op_count;
      if (op.GetType() != cc::PaintOpType::kDrawTextBlob &&
          op.GetType() != cc::PaintOpType::kDrawRecord) {
        audit.has_non_text_visual_paint = true;
      }
    }
    if (op.GetType() == cc::PaintOpType::kDrawTextBlob) {
      ++audit.text_blob_count;
    }
    if (op.GetType() == cc::PaintOpType::kDrawImage ||
        op.GetType() == cc::PaintOpType::kDrawImageRect) {
      ++audit.image_count;
      ++audit.fallback_histogram[op_name];
    }
    if (op.GetType() == cc::PaintOpType::kDrawPath ||
        op.GetType() == cc::PaintOpType::kClipPath) {
      ++audit.path_count;
    }
    if (op.GetType() == cc::PaintOpType::kDrawArc ||
        op.GetType() == cc::PaintOpType::kDrawArcLite) {
      ++audit.fallback_histogram[op_name];
    }
    if (op.GetType() == cc::PaintOpType::kSaveLayerAlpha) {
      const auto& layer = static_cast<const cc::SaveLayerAlphaOp&>(op);
      if (layer.alpha != 255) {
        audit.has_effect_opacity = true;
      }
    }
    if (op.GetType() == cc::PaintOpType::kSaveLayerFilters) {
      ++audit.filter_count;
    }
    if (op.GetType() == cc::PaintOpType::kScale ||
        op.GetType() == cc::PaintOpType::kRotate ||
        op.GetType() == cc::PaintOpType::kConcat ||
        op.GetType() == cc::PaintOpType::kSetMatrix) {
      audit.has_non_translation_transform = true;
    }

    const cc::PaintFlags* flags = PaintFlagsForStandaloneRenderer(op);
    if (flags && flags->HasShader()) {
      ++audit.shader_count;
    }
    if (flags && flags->getImageFilter()) {
      ++audit.filter_count;
    }

    if (paint_ops_json) {
      if (!first) {
        *paint_ops_json << ",";
      }
      first = false;
      *paint_ops_json << "{\"type\":" << JsonStringForStandaloneRenderer(op_name)
                      << ",\"depth\":" << depth
                      << ",\"accounting\":\""
                      << (op.GetType() == cc::PaintOpType::kNoop
                              ? "intentionally_nonvisual"
                              : IsPaintOpCurrentlyExtracted(op.GetType())
                                    ? "retained_supported"
                                    : "retained_unsupported")
                      << "\",\"has_flags\":" << (flags ? "true" : "false")
                      << ",\"has_shader\":"
                      << (flags && flags->HasShader() ? "true" : "false")
                      << ",\"has_image_filter\":"
                      << (flags && flags->getImageFilter() ? "true" : "false")
                      << ",\"has_color_filter\":"
                      << (flags && flags->getColorFilter() ? "true" : "false")
                      << ",\"bounds_or_geometry\":"
                      << PaintOpGeometryJsonForStandaloneRenderer(op) << "}";
    }

    if (op.GetType() == cc::PaintOpType::kDrawRecord) {
      AppendPaintRecordAuditJson(
          static_cast<const cc::DrawRecordOp&>(op).record, audit,
          paint_ops_json, false, depth + 1);
    }
  }
}

std::string LowerAsciiForStandaloneRenderer(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return value;
}

std::vector<std::string> ExtractStyleElementTextForStandaloneRenderer(
    const std::string& html) {
  std::vector<std::string> styles;
  std::string lower = LowerAsciiForStandaloneRenderer(html);
  size_t search_offset = 0;
  while (true) {
    const size_t open = lower.find("<style", search_offset);
    if (open == std::string::npos) {
      break;
    }
    const size_t open_end = lower.find('>', open);
    if (open_end == std::string::npos) {
      break;
    }
    const size_t close = lower.find("</style>", open_end + 1);
    if (close == std::string::npos) {
      break;
    }
    styles.push_back(html.substr(open_end + 1, close - open_end - 1));
    search_offset = close + 8;
  }
  return styles;
}

std::string RemoveStyleElementBlocksForStandaloneRenderer(
    const std::string& html) {
  std::string lower = LowerAsciiForStandaloneRenderer(html);
  std::string output;
  size_t search_offset = 0;
  while (true) {
    const size_t open = lower.find("<style", search_offset);
    if (open == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    const size_t open_end = lower.find('>', open);
    if (open_end == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    const size_t close = lower.find("</style>", open_end + 1);
    if (close == std::string::npos) {
      output += html.substr(search_offset);
      break;
    }
    output += html.substr(search_offset, open - search_offset);
    search_offset = close + 8;
  }
  return output;
}

std::string ExtractHtmlAttributeForStandaloneRenderer(
    const std::string& tag,
    const std::string& attribute_name) {
  const std::string lower = LowerAsciiForStandaloneRenderer(tag);
  const std::string needle =
      LowerAsciiForStandaloneRenderer(attribute_name) + "=";
  const size_t name = lower.find(needle);
  if (name == std::string::npos) {
    return std::string();
  }
  size_t value_start = name + needle.size();
  if (value_start >= tag.size()) {
    return std::string();
  }
  const char quote = tag[value_start];
  if (quote == '"' || quote == '\'') {
    ++value_start;
    const size_t value_end = tag.find(quote, value_start);
    if (value_end == std::string::npos) {
      return std::string();
    }
    return tag.substr(value_start, value_end - value_start);
  }
  size_t value_end = value_start;
  while (value_end < tag.size() &&
         !std::isspace(static_cast<unsigned char>(tag[value_end])) &&
         tag[value_end] != '>') {
    ++value_end;
  }
  return tag.substr(value_start, value_end - value_start);
}

void BuildPaintArtifactAudit(const PaintArtifact& artifact,
                             LiveFramePaintProbeCache& cache) {
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  const DisplayItemList& items = artifact.GetDisplayItemList();
  cache.artifact_audit_lines.push_back(
      "paint_artifact_audit summary chunks=" + std::to_string(chunks.size()) +
      " display_items=" + std::to_string(items.size()));

  std::map<std::string, int> total_op_histogram;
  std::map<std::string, int> total_recursive_op_histogram;
  std::map<std::string, int> total_unsupported_histogram;
  std::map<std::string, int> total_fallback_histogram;
  int total_op_count = 0;
  int total_recursive_op_count = 0;
  int total_drawing_item_count = 0;
  int total_non_drawing_item_count = 0;
  RawPaintRecordAudit total_raw_audit;
  std::ostringstream chunks_json;
  chunks_json << "[";
  for (wtf_size_t chunk_index = 0; chunk_index < chunks.size();
       ++chunk_index) {
    const PaintChunk& chunk = chunks[chunk_index];
    std::map<std::string, int> chunk_op_histogram;
    std::map<std::string, int> chunk_recursive_op_histogram;
    std::map<std::string, int> chunk_unsupported_histogram;
    std::map<std::string, int> chunk_fallback_histogram;
    int chunk_op_count = 0;
    int chunk_recursive_op_count = 0;
    int drawing_item_count = 0;
    int non_drawing_item_count = 0;
    RawPaintRecordAudit chunk_raw_audit;
    std::ostringstream display_items_json;
    display_items_json << "[";
    bool first_display_item = true;

    for (wtf_size_t item_index = chunk.begin_index;
         item_index < chunk.end_index && item_index < items.size();
         ++item_index) {
      const DisplayItem& item = items[item_index];
      if (!first_display_item) {
        display_items_json << ",";
      }
      first_display_item = false;
      const std::string item_id =
          BlinkStringToStdStringForStandaloneRenderer(item.GetId().ToString());
      const std::string item_type =
          std::to_string(static_cast<int>(item.GetType()));
      display_items_json << "{\"index\":" << item_index << ",\"id\":"
                         << JsonStringForStandaloneRenderer(item_id)
                         << ",\"type\":"
                         << JsonStringForStandaloneRenderer(item_type)
                         << ",\"client_debug_name\":null"
                         << ",\"client_owner_node_id\":null"
                         << ",\"visual_rect\":"
                         << RectJsonForStandaloneRenderer(item.VisualRect())
                         << ",\"is_drawing\":"
                         << (item.IsDrawing() ? "true" : "false");
      if (!item.IsDrawing()) {
        ++non_drawing_item_count;
        display_items_json
            << ",\"paint_record_op_histogram\":{},\"recursive_paint_record_op_histogram\":{},\"paint_ops\":[]}";
        continue;
      }
      ++drawing_item_count;
      const auto* drawing = DynamicTo<DrawingDisplayItem>(item);
      if (!drawing) {
        display_items_json
            << ",\"paint_record_op_histogram\":{},\"recursive_paint_record_op_histogram\":{},\"paint_ops\":[]}";
        continue;
      }
      RawPaintRecordAudit item_audit;
      std::ostringstream paint_ops_json;
      paint_ops_json << "[";
      AppendPaintRecordAuditJson(drawing->GetPaintRecord(), item_audit,
                                 &paint_ops_json, true);
      paint_ops_json << "]";
      for (const auto& [name, count] : item_audit.top_level_histogram) {
        chunk_op_histogram[name] += count;
      }
      for (const auto& [name, count] : item_audit.recursive_histogram) {
        chunk_recursive_op_histogram[name] += count;
      }
      for (const auto& [name, count] : item_audit.unsupported_histogram) {
        chunk_unsupported_histogram[name] += count;
      }
      for (const auto& [name, count] : item_audit.fallback_histogram) {
        chunk_fallback_histogram[name] += count;
      }
      chunk_op_count += item_audit.paint_op_count;
      chunk_recursive_op_count += item_audit.recursive_paint_op_count;
      chunk_raw_audit.visual_op_count += item_audit.visual_op_count;
      chunk_raw_audit.text_blob_count += item_audit.text_blob_count;
      chunk_raw_audit.image_count += item_audit.image_count;
      chunk_raw_audit.shader_count += item_audit.shader_count;
      chunk_raw_audit.path_count += item_audit.path_count;
      chunk_raw_audit.filter_count += item_audit.filter_count;
      chunk_raw_audit.has_non_text_visual_paint |=
          item_audit.has_non_text_visual_paint;
      chunk_raw_audit.has_non_translation_transform |=
          item_audit.has_non_translation_transform;
      chunk_raw_audit.has_effect_opacity |= item_audit.has_effect_opacity;
      display_items_json << ",\"paint_record_op_histogram\":"
                         << MapToJsonObject(item_audit.top_level_histogram)
                         << ",\"recursive_paint_record_op_histogram\":"
                         << MapToJsonObject(item_audit.recursive_histogram)
                         << ",\"paint_ops\":" << paint_ops_json.str() << "}";
    }
    display_items_json << "]";
    for (const auto& [name, count] : chunk_op_histogram) {
      total_op_histogram[name] += count;
    }
    for (const auto& [name, count] : chunk_recursive_op_histogram) {
      total_recursive_op_histogram[name] += count;
    }
    for (const auto& [name, count] : chunk_unsupported_histogram) {
      total_unsupported_histogram[name] += count;
    }
    for (const auto& [name, count] : chunk_fallback_histogram) {
      total_fallback_histogram[name] += count;
    }
    total_op_count += chunk_op_count;
    total_recursive_op_count += chunk_recursive_op_count;
    total_drawing_item_count += drawing_item_count;
    total_non_drawing_item_count += non_drawing_item_count;
    total_raw_audit.visual_op_count += chunk_raw_audit.visual_op_count;
    total_raw_audit.text_blob_count += chunk_raw_audit.text_blob_count;
    total_raw_audit.image_count += chunk_raw_audit.image_count;
    total_raw_audit.shader_count += chunk_raw_audit.shader_count;
    total_raw_audit.path_count += chunk_raw_audit.path_count;
    total_raw_audit.filter_count += chunk_raw_audit.filter_count;
    total_raw_audit.has_non_text_visual_paint |=
        chunk_raw_audit.has_non_text_visual_paint;
    total_raw_audit.has_non_translation_transform |=
        chunk_raw_audit.has_non_translation_transform;
    total_raw_audit.has_effect_opacity |= chunk_raw_audit.has_effect_opacity;

    if (chunk_index > 0) {
      chunks_json << ",";
    }
    const std::string chunk_id =
        BlinkStringToStdStringForStandaloneRenderer(chunk.id.ToString());
    const PropertyTreeState chunk_state = chunk.properties.Unalias();
    uint32_t transform_chain_depth = 0;
    bool projection_has_non_translation = false;
    gfx::Transform projection = DirectTransformToRootForStandaloneRenderer(
        chunk_state, &transform_chain_depth, &projection_has_non_translation);
    const bool has_projection = true;
    std::optional<FloatClipRect> clip;
    if (!projection_has_non_translation) {
      clip = GeometryMapper::LocalToAncestorClipRect(
          chunk_state, PropertyTreeState::Root());
    }
    const std::string property_fingerprint =
        chunk_id + ":" + std::to_string(chunk.begin_index) + ":" +
        std::to_string(chunk.end_index) + ":" +
        (has_projection ? MatrixJsonForStandaloneRenderer(projection) : "");
    const uint64_t property_hash =
        HashStringForStandaloneRenderer(property_fingerprint);
    const std::string stable_key =
        !chunk_id.empty()
            ? "blink-chunk:id=" + chunk_id + ":state=" +
                  std::to_string(property_hash)
            : "blink-chunk:fingerprint=" +
                  std::to_string(HashStringForStandaloneRenderer(
                      std::to_string(chunk.begin_index) + ":" +
                      std::to_string(chunk.end_index))) +
                  ":state=" + std::to_string(property_hash) +
                  ":debug-index=" + std::to_string(chunk_index);
    chunks_json << "{\"index\":" << chunk_index << ",\"paint_chunk_id\":"
                << JsonStringForStandaloneRenderer(chunk_id)
                << ",\"stable_key\":"
                << JsonStringForStandaloneRenderer(stable_key)
                << ",\"begin_index\":" << chunk.begin_index
                << ",\"end_index\":" << chunk.end_index
                << ",\"bounds\":" << RectJsonForStandaloneRenderer(chunk.bounds)
                << ",\"drawable_bounds\":"
                << RectJsonForStandaloneRenderer(chunk.drawable_bounds)
                << ",\"has_text\":" << (chunk.has_text ? "true" : "false")
                << ",\"is_cacheable\":"
                << (chunk.is_cacheable ? "true" : "false")
                << ",\"can_match_old_chunk\":"
                << (chunk.CanMatchOldChunk() ? "true" : "false")
                << ",\"client_debug_name\":null,\"client_owner_node_id\":null"
                << ",\"property_state\":{\"state_hash\":" << property_hash
                << ",\"transform_to_root\":"
                << (has_projection ? MatrixJsonForStandaloneRenderer(projection)
                                   : "null")
                << ",\"transform_is_2d\":"
                << (has_projection && projection.Is2dTransform() ? "true"
                                                                 : "false")
                << ",\"transform_has_non_translation\":"
                << (projection_has_non_translation ? "true" : "false")
                << ",\"transform_chain_depth\":" << transform_chain_depth
                << ",\"has_clip_rect\":"
                << (clip && !clip->IsInfinite() ? "true" : "false")
                << ",\"clip_rect\":"
                << (clip && !clip->IsInfinite()
                        ? RectFJsonForStandaloneRenderer(clip->Rect())
                        : "null")
                << "},\"property_tree\":{\"transform_chain\":[],"
                << "\"clip_chain\":[],\"effect_chain\":[],\"scroll\":null,"
                << "\"inaccessible_fields\":["
                << "\"raw transform/clip/effect/scroll ancestor fields are not exposed through the current standalone probe boundary; add accessors near blink_property_tree_snapshot in standalone_live_frame_bridge_probe.cc\"]}"
                << ",\"op_histogram\":" << MapToJsonObject(chunk_op_histogram)
                << ",\"recursive_op_histogram\":"
                << MapToJsonObject(chunk_recursive_op_histogram)
                << ",\"unsupported_ops\":"
                << MapToJsonObject(chunk_unsupported_histogram)
                << ",\"fallback_rasterized_ops\":"
                << MapToJsonObject(chunk_fallback_histogram)
                << ",\"display_items\":" << display_items_json.str() << "}";

    cache.artifact_audit_lines.push_back(
        "paint_artifact_audit chunk index=" + std::to_string(chunk_index) +
        " bounds=(" + std::to_string(chunk.bounds.x()) + "," +
        std::to_string(chunk.bounds.y()) + " " +
        std::to_string(chunk.bounds.width()) + "x" +
        std::to_string(chunk.bounds.height()) + ") drawable_bounds=(" +
        std::to_string(chunk.drawable_bounds.x()) + "," +
        std::to_string(chunk.drawable_bounds.y()) + " " +
        std::to_string(chunk.drawable_bounds.width()) + "x" +
        std::to_string(chunk.drawable_bounds.height()) + ") display_range=[" +
        std::to_string(chunk.begin_index) + "," +
        std::to_string(chunk.end_index) + ") drawing_items=" +
        std::to_string(drawing_item_count) + " non_drawing_items=" +
        std::to_string(non_drawing_item_count) + " paint_ops=" +
        std::to_string(chunk_op_count) + " has_text=" +
        std::to_string(chunk.has_text ? 1 : 0) + " ops=" +
        MapToJsonObject(chunk_op_histogram) + " unsupported=" +
        MapToJsonObject(chunk_unsupported_histogram));
  }
  chunks_json << "]";

  cache.artifact_audit_lines.push_back(
      "paint_artifact_audit totals paint_ops=" +
      std::to_string(total_op_count) + " ops=" +
      MapToJsonObject(total_op_histogram) + " unsupported=" +
      MapToJsonObject(total_unsupported_histogram));

  const std::string lowered_input =
      LowerAsciiForStandaloneRenderer(cache.body_html);
  std::vector<std::string> warnings;
  if (lowered_input.find("linear-gradient") != std::string::npos &&
      total_raw_audit.shader_count == 0) {
    warnings.push_back(
        "expected_feature_missing feature=box_gradient_background reason=raw Blink PaintArtifact audit did not expose shader-backed paint for linear-gradient input");
  }
  if (lowered_input.find("border") != std::string::npos &&
      !total_raw_audit.has_non_text_visual_paint) {
    warnings.push_back(
        "expected_feature_missing feature=box_border_or_background reason=raw Blink PaintArtifact audit found no non-text visual paint ops");
  }
  if (total_raw_audit.text_blob_count == 0 &&
      lowered_input.find("hello") != std::string::npos) {
    warnings.push_back(
        "expected_feature_missing feature=text reason=raw Blink PaintArtifact audit found no DrawTextBlob");
  }
  if (total_raw_audit.image_count == 0 &&
      lowered_input.find("<img") != std::string::npos) {
    warnings.push_back(
        "expected_feature_missing feature=image reason=raw Blink PaintArtifact audit found no DrawImage/DrawImageRect; standalone live embedder does not yet feed data/local image resources into Blink image loading");
  }
  if (lowered_input.find("transform") != std::string::npos &&
      !total_raw_audit.has_non_translation_transform) {
    warnings.push_back(
        "expected_feature_missing feature=non_translation_transform reason=raw audit did not finish transform evidence; transformed overflow currently remains a live extraction crash blocker");
  }

  std::ostringstream json;
  json << "{\"source\":\"real Blink PaintArtifact\""
       << ",\"viewport\":{\"width\":" << cache.viewport_width
       << ",\"height\":" << cache.viewport_height << "}"
       << ",\"device_scale_factor\":1"
       << ",\"raw_chunk_count\":" << chunks.size()
       << ",\"raw_display_item_count\":" << items.size()
       << ",\"raw_drawing_display_item_count\":" << total_drawing_item_count
       << ",\"raw_non_drawing_display_item_count\":"
       << total_non_drawing_item_count
       << ",\"raw_paint_op_histogram\":"
       << MapToJsonObject(total_op_histogram)
       << ",\"recursive_raw_blink_paint_op_histogram\":"
       << MapToJsonObject(total_recursive_op_histogram)
       << ",\"unsupported_raw_op_histogram\":"
       << MapToJsonObject(total_unsupported_histogram)
       << ",\"fallback_rasterized_raw_op_histogram\":"
       << MapToJsonObject(total_fallback_histogram)
       << ",\"resource_summary\":{\"text_blob_count\":"
       << total_raw_audit.text_blob_count
       << ",\"image_count\":" << total_raw_audit.image_count
       << ",\"shader_count\":" << total_raw_audit.shader_count
       << ",\"path_count\":" << total_raw_audit.path_count
       << ",\"filter_count\":" << total_raw_audit.filter_count << "}"
       << ",\"chunks\":" << chunks_json.str()
       << ",\"self_checks\":{\"css_applied\":\"unknown\""
       << ",\"has_text_paint\":"
       << (total_raw_audit.text_blob_count > 0 ? "true" : "false")
       << ",\"has_non_text_paint\":"
       << (total_raw_audit.has_non_text_visual_paint ? "true" : "false")
       << ",\"has_shader_paint\":"
       << (total_raw_audit.shader_count > 0 ? "true" : "false")
       << ",\"has_clip_state\":false"
       << ",\"has_non_translation_transform\":"
       << (total_raw_audit.has_non_translation_transform ? "true" : "false")
       << ",\"has_effect_opacity\":"
       << (total_raw_audit.has_effect_opacity ? "true" : "false")
       << ",\"raw_ops_lost_during_retained_extraction\":\"unknown\""
       << ",\"visual_unsupported_ops\":";
  int visual_unsupported_ops = 0;
  for (const auto& [name, count] : total_unsupported_histogram) {
    visual_unsupported_ops += count;
  }
  int fallback_ops = 0;
  for (const auto& [name, count] : total_fallback_histogram) {
    fallback_ops += count;
  }
  json << visual_unsupported_ops
       << ",\"diagnostic_bitmap_fallback_ops\":" << fallback_ops << "}"
       << ",\"warnings\":[";
  for (size_t i = 0; i < warnings.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    json << JsonStringForStandaloneRenderer(warnings[i]);
  }
  json << "]}";
  cache.raw_paint_artifact_audit_json = json.str();
}

void InstallStyleElementsForStandaloneRenderer(Document& document,
                                               Element& head,
                                               const std::string& head_html) {
  const std::vector<std::string> style_texts =
      ExtractStyleElementTextForStandaloneRenderer(head_html);
  if (style_texts.empty()) {
    head.SetInnerHTMLWithoutTrustedTypes(String::FromUtf8(head_html));
    return;
  }

  head.SetInnerHTMLWithoutTrustedTypes(String());
  for (const std::string& css : style_texts) {
    auto* style = MakeGarbageCollected<HTMLStyleElement>(
        document, CreateElementFlags::ByCreateElement());
    style->setTextContent(String::FromUtf8(css));
    head.appendChild(style);
  }
}

void ExportDrawOpsForStandaloneRenderer(const PaintArtifact& artifact,
                                        LiveFramePaintProbeCache& cache) {
  TraceLiveFrameProbeStage("export begin");
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  std::vector<std::string> extraction_diagnostics;
  if (AppendPaintArtifactExtractedOps(artifact, cache.viewport_width,
                                      cache.viewport_height,
                                      cache.exported_draw_ops,
                                      cache.chunk_property_states,
                                      extraction_diagnostics)) {
    cache.artifact_audit_lines.push_back(
        "paint_op_extraction mode=retained_ops exported_draw_ops=" +
        std::to_string(cache.exported_draw_ops.size()));
    TraceLiveFrameProbeStage("export extracted ops done");
    return;
  }
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.artifact_audit_lines.insert(cache.artifact_audit_lines.end(),
                                    extraction_diagnostics.begin(),
                                    extraction_diagnostics.end());
  cache.artifact_audit_lines.push_back(
      "paint_op_extraction mode=oracle_bitmap reason=incomplete");
  if (AppendPaintArtifactOracleBitmapOp(artifact, cache.viewport_width,
                                        cache.viewport_height,
                                        cache.exported_draw_ops)) {
    TraceLiveFrameProbeStage("export oracle bitmap done");
    return;
  }
  TraceLiveFrameProbeStage("export oracle bitmap failed");
  cache.exported_draw_ops.clear();
cache.chunk_property_states.clear();
}

void EnsureWtfInitializedForStandaloneRenderer() {
  static bool initialized = false;
  if (!initialized) {
    blink::InitializeWtf();
    blink::Length::Initialize();
    blink::CoreInitializer::GetInstance().Initialize();
    initialized = true;
  }
}

LiveFramePaintProbeResult RunLiveFramePaintProbe(const char* body_html) {
  EnsureWtfInitializedForStandaloneRenderer();
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string input_html = body_html ? body_html : "";
  if (cache.initialized && cache.body_html == input_html) {
    return cache.result;
  }
  LiveFramePaintProbeResult result;
  TraceLiveFrameProbeStage("before DummyPageHolder");
  if (!cache.holder) {
    cache.holder = new DummyPageHolder(
        gfx::Size(cache.viewport_width, cache.viewport_height));
  }
  TraceLiveFrameProbeStage("after DummyPageHolder");
  Document& document = cache.holder->GetDocument();
  TraceLiveFrameProbeStage("after GetDocument");

  if (!document.documentElement() || !document.body()) {
    TraceLiveFrameProbeStage("missing body");
    return result;
  }

  Element* head = document.head();
  if (!head) {
    head = document.CreateRawElement(html_names::kHeadTag,
                                     CreateElementFlags::ByCreateElement());
    if (document.body()) {
      document.documentElement()->ParserInsertBefore(head, *document.body());
    } else {
      document.documentElement()->ParserAppendChild(head);
    }
  }

  TraceLiveFrameProbeStage("before SetInnerHTML");
  g_standalone_blink_saw_font_draw_text = false;
  const std::string head_open = "<head>";
  const std::string head_close = "</head>";
  const std::string body_close = "</body>";
  const size_t head_start = input_html.find(head_open);
  const size_t head_end = input_html.find(head_close);
  const size_t body_start =
      head_end == std::string::npos
          ? std::string::npos
          : input_html.find("<body", head_end + head_close.size());
  if (head_start != std::string::npos && head_end != std::string::npos &&
      body_start != std::string::npos) {
    const size_t head_content_start = head_start + head_open.size();
    const std::string head_html =
        input_html.substr(head_content_start, head_end - head_content_start);
    const size_t body_open_end = input_html.find('>', body_start);
    const size_t body_content_start =
        body_open_end == std::string::npos ? input_html.size()
                                           : body_open_end + 1;
    size_t body_end = input_html.rfind(body_close);
    if (body_end == std::string::npos || body_end < body_content_start) {
      body_end = input_html.size();
    }
    const std::string body_open_tag =
        body_open_end == std::string::npos
            ? std::string()
            : input_html.substr(body_start, body_open_end - body_start + 1);
    const std::string body_fragment =
        input_html.substr(body_content_start, body_end - body_content_start);
    InstallStyleElementsForStandaloneRenderer(document, *head, head_html);
    const std::string body_class =
        ExtractHtmlAttributeForStandaloneRenderer(body_open_tag, "class");
    if (!body_class.empty()) {
      document.body()->setAttribute(html_names::kClassAttr,
                                    AtomicString(String::FromUtf8(body_class)));
    }
    const std::string body_id =
        ExtractHtmlAttributeForStandaloneRenderer(body_open_tag, "id");
    if (!body_id.empty()) {
      document.body()->setAttribute(html_names::kIdAttr,
                                    AtomicString(String::FromUtf8(body_id)));
    }
    String body_string = String::FromUtf8(body_fragment);
    if (!body_fragment.empty() && body_string.empty()) {
      body_string = String(body_fragment);
    }
    document.body()->SetInnerHTMLWithoutTrustedTypes(body_string);
  } else {
    InstallStyleElementsForStandaloneRenderer(document, *head, input_html);
    const std::string body_fragment =
        RemoveStyleElementBlocksForStandaloneRenderer(input_html);
    document.body()->SetInnerHTMLWithoutTrustedTypes(
        String::FromUtf8(body_fragment));
  }
  TraceLiveFrameProbeStage("after SetInnerHTML");
  DumpNodeForStandaloneRenderer(*document.body(), 0);

  LocalFrameView& frame_view = cache.holder->GetFrameView();
  if (Settings* settings = document.GetSettings()) {
    settings->SetDefaultFontSize(16);
    settings->SetDefaultFixedFontSize(13);
  }
  TraceLiveFrameProbeStage("before active style update");
  document.GetStyleEngine().UpdateActiveStyle();
  TraceLiveFrameProbeStage("after active style update");
  TraceLiveFrameProbeStage("before lifecycle update");
  result.lifecycle_reached_paint_clean =
      frame_view.UpdateAllLifecyclePhasesForTest() ? 1 : 0;
  TraceLiveFrameProbeStage("after lifecycle update");
  if (document.GetLayoutView()) {
    const gfx::Size view_size = document.GetLayoutView()->GetLayoutSize();
  }
  DumpNodeForStandaloneRenderer(*document.body(), 0);
  const PaintArtifact& artifact = frame_view.GetPaintArtifact();
  TraceLiveFrameProbeStage("after GetPaintArtifact");
  TraceLiveFrameProbeStage("before paint chunk count");
  result.paint_chunk_count =
      static_cast<int>(artifact.GetPaintChunks().size());
  TraceLiveFrameProbeStage("after paint chunk count");
  TraceLiveFrameProbeStage("before display item count");
  result.display_item_count =
      static_cast<int>(artifact.GetDisplayItemList().size());
  TraceLiveFrameProbeStage("after display item count");
  cache.body_html = input_html;
  BuildPaintArtifactAudit(artifact, cache);
  ExportDrawOpsForStandaloneRenderer(artifact, cache);
  cache.result = result;
  cache.initialized = true;
  return result;
}

}  // namespace

void StandaloneBlinkLiveFrameBridgeSetViewportForStandaloneRenderer(
    int width,
    int height) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const int clamped_width = std::max(1, width);
  const int clamped_height = std::max(1, height);
  if (cache.viewport_width == clamped_width &&
      cache.viewport_height == clamped_height) {
    return;
  }
  cache.viewport_width = clamped_width;
  cache.viewport_height = clamped_height;
  g_standalone_blink_viewport_width = clamped_width;
  g_standalone_blink_viewport_height = clamped_height;
  delete cache.holder;
  cache.holder = nullptr;
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

int StandaloneBlinkLiveFrameBridgeRecipeVersionForStandaloneRenderer() {
  return 1;
}

int StandaloneBlinkLiveFrameBridgeUsesDummyPageHolderForStandaloneRenderer() {
  return 1;
}

int StandaloneBlinkLiveFrameBridgeUsesLocalFrameViewPaintArtifactForStandaloneRenderer() {
  return 1;
}

int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).paint_chunk_count;
}

int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).display_item_count;
}

int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).lifecycle_reached_paint_clean;
}

int StandaloneBlinkLiveFrameBridgePaintChunkMetadataAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* x,
    int* y,
    int* width,
    int* height,
    int* begin_display_item_index,
    int* end_display_item_index,
    int* has_text) {
  EnsureWtfInitializedForStandaloneRenderer();
  RunLiveFramePaintProbe(body_html);
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.initialized || !cache.holder) {
    return 0;
  }
  LocalFrameView& frame_view = cache.holder->GetFrameView();
  const PaintArtifact& artifact = frame_view.GetPaintArtifact();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  if (chunk_index < 0 ||
      static_cast<wtf_size_t>(chunk_index) >= chunks.size()) {
    return 0;
  }
  const PaintChunk& chunk = chunks[static_cast<wtf_size_t>(chunk_index)];
  if (x) {
    *x = chunk.bounds.x();
  }
  if (y) {
    *y = chunk.bounds.y();
  }
  if (width) {
    *width = chunk.bounds.width();
  }
  if (height) {
    *height = chunk.bounds.height();
  }
  if (begin_display_item_index) {
    *begin_display_item_index = static_cast<int>(chunk.begin_index);
  }
  if (end_display_item_index) {
    *end_display_item_index = static_cast<int>(chunk.end_index);
  }
  if (has_text) {
    *has_text = (chunk.has_text || g_standalone_blink_saw_font_draw_text) ? 1 : 0;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgePaintChunkPropertyStateAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    uint64_t* state_hash,
    float* transform16,
    int* has_clip_rect,
    float* clip_x,
    float* clip_y,
    float* clip_width,
    float* clip_height) {
  RunLiveFramePaintProbe(body_html);
  const auto& states = ProbeCache().chunk_property_states;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= states.size()) {
    return 0;
  }
  const LiveExportedChunkPropertyState& state =
      states[static_cast<size_t>(chunk_index)];
  if (state_hash) {
    *state_hash = state.state_hash;
  }
  if (transform16) {
    std::memcpy(transform16, state.transform_to_root.data(),
                state.transform_to_root.size() * sizeof(float));
  }
  if (has_clip_rect) {
    *has_clip_rect = state.has_clip_rect ? 1 : 0;
  }
  if (clip_x) {
    *clip_x = state.clip_x;
  }
  if (clip_y) {
    *clip_y = state.clip_y;
  }
  if (clip_width) {
    *clip_width = state.clip_width;
  }
  if (clip_height) {
    *clip_height = state.clip_height;
  }
  return 1;
}
int StandaloneBlinkLiveFrameBridgeExportedDrawOpCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().exported_draw_ops.size());
}

int StandaloneBlinkLiveFrameBridgeArtifactAuditLineCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().artifact_audit_lines.size());
}

int StandaloneBlinkLiveFrameBridgeArtifactAuditLineAtForStandaloneRenderer(
    const char* body_html,
    int line_index,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const std::vector<std::string>& lines = ProbeCache().artifact_audit_lines;
  if (line_index < 0 || static_cast<size_t>(line_index) >= lines.size() ||
      !buffer || buffer_size <= 0) {
    return 0;
  }
  const std::string& line = lines[static_cast<size_t>(line_index)];
  const int copy_count =
      std::min(static_cast<int>(line.size()), buffer_size - 1);
  std::memcpy(buffer, line.data(), static_cast<size_t>(copy_count));
  buffer[copy_count] = '\0';
  return copy_count;
}

int StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonSizeForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().raw_paint_artifact_audit_json.size());
}

int StandaloneBlinkLiveFrameBridgeRawPaintArtifactAuditJsonForStandaloneRenderer(
    const char* body_html,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const std::string& json = ProbeCache().raw_paint_artifact_audit_json;
  if (!buffer || buffer_size <= 0) {
    return 0;
  }
  const int copy_count =
      std::min(static_cast<int>(json.size()), buffer_size - 1);
  std::memcpy(buffer, json.data(), static_cast<size_t>(copy_count));
  buffer[copy_count] = '\0';
  return copy_count;
}

int StandaloneBlinkLiveFrameBridgeExportedDrawOpAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* type,
    float* x,
    float* y,
    float* width,
    float* height,
    float* r,
    float* g,
    float* b,
    float* a,
    float* font_size,
    float* radius_x,
    float* radius_y,
    int* glyph_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (type) {
    *type = op.type;
  }
  if (x) {
    *x = op.x;
  }
  if (y) {
    *y = op.y;
  }
  if (width) {
    *width = op.width;
  }
  if (height) {
    *height = op.height;
  }
  if (r) {
    *r = op.r;
  }
  if (g) {
    *g = op.g;
  }
  if (b) {
    *b = op.b;
  }
  if (a) {
    *a = op.a;
  }
  if (font_size) {
    *font_size = op.font_size;
  }
  if (radius_x) {
    *radius_x = op.radius_x;
  }
  if (radius_y) {
    *radius_y = op.radius_y;
  }
  if (glyph_count) {
    *glyph_count = static_cast<int>(op.glyphs.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedGlyphAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int glyph_index,
    uint32_t* glyph_id,
    float* x,
    float* y) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (glyph_index < 0 || static_cast<size_t>(glyph_index) >= op.glyphs.size()) {
    return 0;
  }
  const LiveExportedGlyph& glyph = op.glyphs[static_cast<size_t>(glyph_index)];
  if (glyph_id) {
    *glyph_id = glyph.glyph_id;
  }
  if (x) {
    *x = glyph.x;
  }
  if (y) {
    *y = glyph.y;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedRRectRadiiAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    float* top_left_x,
    float* top_left_y,
    float* top_right_x,
    float* top_right_y,
    float* bottom_right_x,
    float* bottom_right_y,
    float* bottom_left_x,
    float* bottom_left_y) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 15) {
    return 0;
  }
  if (top_left_x) {
    *top_left_x = op.corner_radii[0].x();
  }
  if (top_left_y) {
    *top_left_y = op.corner_radii[0].y();
  }
  if (top_right_x) {
    *top_right_x = op.corner_radii[1].x();
  }
  if (top_right_y) {
    *top_right_y = op.corner_radii[1].y();
  }
  if (bottom_right_x) {
    *bottom_right_x = op.corner_radii[2].x();
  }
  if (bottom_right_y) {
    *bottom_right_y = op.corner_radii[2].y();
  }
  if (bottom_left_x) {
    *bottom_left_x = op.corner_radii[3].x();
  }
  if (bottom_left_y) {
    *bottom_left_y = op.corner_radii[3].y();
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedTextMaskInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* width,
    int* height,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 3 || op.mask_width <= 0 || op.mask_height <= 0 ||
      op.alpha_mask.empty()) {
    return 0;
  }
  if (width) {
    *width = op.mask_width;
  }
  if (height) {
    *height = op.mask_height;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.alpha_mask.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedTextMaskBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 3 || op.alpha_mask.empty() ||
      destination_size < static_cast<int>(op.alpha_mask.size())) {
    return 0;
  }
  std::memcpy(destination, op.alpha_mask.data(), op.alpha_mask.size());
  return static_cast<int>(op.alpha_mask.size());
}

int StandaloneBlinkLiveFrameBridgeExportedPathInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if ((op.type != 17 && op.type != 21) || op.path_bytes.empty()) {
    return 0;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.path_bytes.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedPathBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if ((op.type != 17 && op.type != 21) || op.path_bytes.empty() ||
      destination_size < static_cast<int>(op.path_bytes.size())) {
    return 0;
  }
  std::memcpy(destination, op.path_bytes.data(), op.path_bytes.size());
  return static_cast<int>(op.path_bytes.size());
}

int StandaloneBlinkLiveFrameBridgeExportedTextBlobInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 18 || op.text_blob_bytes.empty()) {
    return 0;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.text_blob_bytes.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedTextBlobBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 18 || op.text_blob_bytes.empty() ||
      destination_size < static_cast<int>(op.text_blob_bytes.size())) {
    return 0;
  }
  std::memcpy(destination, op.text_blob_bytes.data(), op.text_blob_bytes.size());
  return static_cast<int>(op.text_blob_bytes.size());
}

int StandaloneBlinkLiveFrameBridgeExportedDebugLabelAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !buffer || buffer_size <= 0) {
    return 0;
  }
  const std::string& label = ops[static_cast<size_t>(op_index)].debug_label;
  if (label.empty()) {
    buffer[0] = '\0';
    return 0;
  }
  std::snprintf(buffer, static_cast<size_t>(buffer_size), "%s",
                label.c_str());
  return static_cast<int>(std::strlen(buffer));
}

int StandaloneBlinkLiveFrameBridgeExportedShaderInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if ((op.type != 19 && op.type != 20 && op.type != 21) ||
      op.shader_bytes.empty()) {
    return 0;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.shader_bytes.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedShaderBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if ((op.type != 19 && op.type != 20 && op.type != 21) ||
      op.shader_bytes.empty() ||
      destination_size < static_cast<int>(op.shader_bytes.size())) {
    return 0;
  }
  std::memcpy(destination, op.shader_bytes.data(), op.shader_bytes.size());
  return static_cast<int>(op.shader_bytes.size());
}

int StandaloneBlinkLiveFrameBridgeExportedBitmapInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* width,
    int* height,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 7 || op.mask_width <= 0 || op.mask_height <= 0 ||
      op.rgba_pixels.empty()) {
    return 0;
  }
  if (width) {
    *width = op.mask_width;
  }
  if (height) {
    *height = op.mask_height;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.rgba_pixels.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedBitmapBytesAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() ||
      !destination || destination_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 7 || op.rgba_pixels.empty() ||
      destination_size < static_cast<int>(op.rgba_pixels.size())) {
    return 0;
  }
  std::memcpy(destination, op.rgba_pixels.data(), op.rgba_pixels.size());
  return static_cast<int>(op.rgba_pixels.size());
}

}  // namespace blink::standalone_renderer_probe
