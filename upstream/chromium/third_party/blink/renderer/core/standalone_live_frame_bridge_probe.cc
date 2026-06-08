// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/testing/dummy_page_holder.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <array>
#include <functional>
#include <iomanip>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <utility>
#include <string>
#include <unordered_map>
#include <vector>

#include "cc/paint/paint_op.h"
#include "cc/paint/paint_op_buffer_iterator.h"
#include "cc/paint/paint_record.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "base/time/time.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkPathBuilder.h"
#include "third_party/skia/include/core/SkPathEffect.h"
#include "third_party/skia/include/core/SkSerialProcs.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/core/SkStream.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "third_party/skia/include/core/SkTypeface.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/node.h"
#include "third_party/blink/renderer/core/dom/shadow_root.h"
#include "third_party/blink/renderer/core/dom/text.h"
#include "third_party/blink/renderer/core/animation/animation_clock.h"
#include "third_party/blink/renderer/core/animation/document_animations.h"
#include "third_party/blink/renderer/core/animation/document_timeline.h"
#include "third_party/blink/renderer/core/animation/pending_animations.h"
#include "third_party/blink/renderer/core/core_initializer.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/root_frame_viewport.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/frame/visual_viewport.h"
#include "third_party/blink/renderer/core/css/post_style_update_scope.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html/html_body_element.h"
#include "third_party/blink/renderer/core/html/html_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/html/html_html_element.h"
#include "third_party/blink/renderer/core/html/html_image_element.h"
#include "third_party/blink/renderer/core/html/html_style_element.h"
#include "third_party/blink/renderer/core/html/forms/html_input_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/html_text_area_element.h"
#include "third_party/blink/renderer/core/html/forms/text_control_element.h"
#include "third_party/blink/renderer/core/loader/resource/image_resource_content.h"
#include "third_party/blink/renderer/core/layout/layout_box.h"
#include "third_party/blink/renderer/core/layout/layout_image.h"
#include "third_party/blink/renderer/core/layout/list/layout_list_item.h"
#include "third_party/blink/renderer/core/layout/block_node.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/layout/table/layout_table.h"
#include "third_party/blink/renderer/core/layout/table/layout_table_column.h"
#include "third_party/blink/renderer/core/layout/table/table_layout_algorithm_types.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/layout/physical_box_fragment.h"
#include "third_party/blink/renderer/core/layout/physical_fragment.h"
#include "third_party/blink/renderer/core/layout/physical_fragment_link.h"
#include "third_party/blink/renderer/core/paint/object_paint_properties.h"
#include "third_party/blink/renderer/core/paint/paint_layer.h"
#include "third_party/blink/renderer/core/paint/paint_layer_paint_order_iterator.h"
#include "third_party/blink/renderer/core/paint/paint_layer_scrollable_area.h"
#include "third_party/blink/renderer/core/scroll/scrollable_area.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/style_image.h"
#include "third_party/blink/renderer/platform/graphics/compositor_filter_operations.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_display_item.h"
#include "third_party/blink/renderer/platform/graphics/paint/geometry_mapper.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_chunk.h"
#include "third_party/blink/renderer/platform/geometry/length.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/wtf.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/point_f.h"
#include "ui/gfx/geometry/rect_conversions.h"
#include "ui/gfx/geometry/skia_conversions.h"

namespace blink::standalone_renderer_probe {

enum StandaloneFilterOperationType {
  kStandaloneFilterGrayscale = 0,
  kStandaloneFilterSepia = 1,
  kStandaloneFilterSaturate = 2,
  kStandaloneFilterHueRotate = 3,
  kStandaloneFilterInvert = 4,
  kStandaloneFilterBrightness = 5,
  kStandaloneFilterContrast = 6,
  kStandaloneFilterOpacity = 7,
  kStandaloneFilterBlur = 8,
  kStandaloneFilterDropShadow = 9,
  kStandaloneFilterColorMatrix = 10,
};

extern "C" bool g_standalone_blink_saw_font_draw_text;
extern "C" int g_standalone_blink_viewport_width;
extern "C" int g_standalone_blink_viewport_height;
extern "C" int g_standalone_css_animation_timeline_update_called;
extern "C" int g_standalone_css_animation_update_called;
extern "C" int g_standalone_css_transition_update_called;
extern "C" int g_standalone_document_animations_update_called;
extern "C" int g_standalone_page_animator_service_called;
extern "C" uint64_t
StandaloneRendererRegisterSameProcessTypefaceForSkTextBlob(SkTypeface*);
extern "C" int StandaloneRendererSameProcessTypefaceResourceCount();
extern "C" int StandaloneRendererTextBlobReplayDiagnosticsEnabled();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupAttemptCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupSuccessCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupFailureCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeAttemptCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeSuccessCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeFailureCount();
extern "C" uint64_t StandaloneRendererDiagnosticTypefaceFallbackCount();
extern "C" int StandaloneRendererSameProcessTypefaceFamilyAt(int,
                                                              char*,
                                                              int);
extern "C" int StandaloneRendererFontResolutionDiagnosticCount();
extern "C" int StandaloneRendererFontResolutionDiagnosticJsonAt(int,
                                                                 char*,
                                                                 int);
extern "C" void StandaloneRendererResetImageReachabilityDiagnostics();
extern "C" int StandaloneRendererImageResourceContentFetchCalled();
extern "C" int StandaloneRendererLayoutImageSetResourceCalled();
extern "C" int StandaloneRendererLayoutImageResourceInitializeCalled();
extern "C" int StandaloneRendererLayoutImageResourceSetResourceCalled();
extern "C" int StandaloneRendererLayoutImageResourceNaturalDimensionsCalled();
extern "C" int StandaloneRendererLayoutImageResourceGetImageCalled();
extern "C" int StandaloneRendererLayoutImageResourceMaybeAnimatedCalled();
extern "C" int StandaloneRendererLayoutImageResourceMaybeAnimatedNullImage();
extern "C" int StandaloneRendererLayoutImagePaintCalled();
extern "C" int StandaloneRendererLayoutImagePaintReplacedCalled();
extern "C" int StandaloneRendererImagePainterPaintReplacedCalled();
extern "C" int StandaloneRendererImageResourceContentFetchLastUrl(char*, int);
extern "C" int g_standalone_text_decoration_painter_constructed;
extern "C" int g_standalone_text_decoration_begin_called;
extern "C" int g_standalone_text_decoration_except_line_through_called;
extern "C" int g_standalone_text_decoration_only_line_through_called;
extern "C" int g_standalone_decoration_line_painter_paint_called;
extern "C" int g_standalone_html_factory_create_html_count;
extern "C" int g_standalone_html_factory_create_body_count;
extern "C" int g_standalone_layout_html_body_placement_count;
extern "C" float g_standalone_layout_html_body_margin_inline_start;
extern "C" float g_standalone_layout_html_body_margin_block_start;
extern "C" float g_standalone_layout_html_body_child_bfc_line;
extern "C" float g_standalone_layout_html_body_child_bfc_block;
extern "C" float g_standalone_layout_html_body_parent_bfc_line;
extern "C" float g_standalone_layout_html_body_parent_bfc_block;
extern "C" float g_standalone_layout_html_body_logical_inline_offset;
extern "C" float g_standalone_layout_html_body_logical_block_offset;
extern "C" int g_standalone_layout_body_first_child_placement_count;
extern "C" float g_standalone_layout_body_child_margin_inline_start;
extern "C" float g_standalone_layout_body_child_margin_block_start;
extern "C" float g_standalone_layout_body_child_bfc_line;
extern "C" float g_standalone_layout_body_child_bfc_block;
extern "C" float g_standalone_layout_body_parent_bfc_line;
extern "C" float g_standalone_layout_body_parent_bfc_block;
extern "C" float g_standalone_layout_body_child_logical_inline_offset;
extern "C" float g_standalone_layout_body_child_logical_block_offset;
extern "C" float g_standalone_layout_body_previous_margin_strut_sum;
extern "C" float g_standalone_layout_body_previous_logical_block_offset;
extern "C" int g_standalone_oof_layout_part_run_called;
extern "C" int g_standalone_oof_candidate_count;
extern "C" int g_standalone_oof_descendant_collected;
extern "C" int g_standalone_oof_layout_attempted;
extern "C" int g_standalone_oof_fragment_created;
extern "C" int g_standalone_oof_candidate_repropagated;
extern "C" int g_standalone_oof_candidate_dropped_at_root;
extern "C" int g_standalone_oof_unsupported_inline_containing_block;
extern "C" int g_standalone_oof_layout_null_results;
extern "C" int g_standalone_oof_zero_size_fragments;
extern "C" int g_standalone_oof_safety_limit_hit;
extern "C" void StandaloneRendererResetOutOfFlowDiagnostics();
extern "C" void StandaloneRendererResetMediaQueryDiagnostics();
extern "C" void StandaloneRendererResetListItemFactoryDiagnostics();
extern "C" int StandaloneRendererListItemFactoryDiagnosticValue(int);
extern "C" int StandaloneRendererMediaQueryDiagnosticsJsonSize();
extern "C" int StandaloneRendererMediaQueryDiagnosticsJson(char*, int);
extern "C" int StandaloneRendererMediaQueryDiagnosticCount();
extern "C" int StandaloneRendererMediaQueryDiagnosticFieldAt(int,
                                                             int,
                                                             char*,
                                                             int);

void ResetStandaloneStackingPaintProvenanceForProbe();
std::string StandaloneStackingPaintProvenanceJsonForProbe();

namespace {

struct StandaloneTypefacePayload {
  char magic[4] = {'B', 'S', 'T', 'F'};
  uint32_t version = 1;
  uint64_t typeface_resource_id = 0;
};

struct LiveFramePaintProbeResult {
  int lifecycle_reached_paint_clean = 0;
  int paint_chunk_count = 0;
  int display_item_count = 0;
};

struct ImageReachabilityDiagnostics {
  int html_image_element_count = 0;
  bool img_src_detected_from_dom = false;
  bool img_src_detected_from_source_scan = false;
  bool real_html_image_element_class_linked = false;
  bool image_loader_present = false;
  bool image_loader_update_called = false;
  std::string image_loader_request_url;
  bool layout_object_created = false;
  std::string layout_object_type = "not_reached";
  bool layout_image_resource_created = false;
  int element_natural_width = 0;
  int element_natural_height = 0;
  int loader_natural_width = 0;
  int loader_natural_height = 0;
  int loader_resource_width = 0;
  int loader_resource_height = 0;
  bool loader_content_present = false;
  bool loader_content_has_image = false;
  bool loader_content_error = false;
  std::string width_attr;
  std::string height_attr;
  int computed_display = -1;
  int computed_visibility = -1;
  std::string computed_width;
  std::string computed_height;
  bool layout_is_box = false;
  bool layout_is_layout_image = false;
  int layout_box_width = 0;
  int layout_box_height = 0;
  int layout_content_width = 0;
  int layout_content_height = 0;
  int layout_viewport_x = 0;
  int layout_viewport_y = 0;
  int layout_viewport_width = 0;
  int layout_viewport_height = 0;
  int physical_fragment_count = 0;
  bool paint_layer_present = false;
  bool object_paint_properties_present = false;
};

struct LiveExportedGlyph {
  uint32_t glyph_id = 0;
  float x = 0.0f;
  float y = 0.0f;
};

struct LiveExportedDrawLooperLayer {
  float offset_x = 0.0f;
  float offset_y = 0.0f;
  float blur_sigma = 0.0f;
  float r = 0.0f;
  float g = 0.0f;
  float b = 0.0f;
  float a = 1.0f;
  uint32_t flags = 0;
};

struct LiveExportedFilterOperation {
  int type = kStandaloneFilterGrayscale;
  float amount = 0.0f;
  float offset_x = 0.0f;
  float offset_y = 0.0f;
  float color_r = 0.0f;
  float color_g = 0.0f;
  float color_b = 0.0f;
  float color_a = 1.0f;
  std::array<float, 20> matrix = {};
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
  bool has_clip_rrect = false;
  float clip_rrect_x = 0.0f;
  float clip_rrect_y = 0.0f;
  float clip_rrect_width = 0.0f;
  float clip_rrect_height = 0.0f;
  float clip_rrect_top_left_x = 0.0f;
  float clip_rrect_top_left_y = 0.0f;
  float clip_rrect_top_right_x = 0.0f;
  float clip_rrect_top_right_y = 0.0f;
  float clip_rrect_bottom_right_x = 0.0f;
  float clip_rrect_bottom_right_y = 0.0f;
  float clip_rrect_bottom_left_x = 0.0f;
  float clip_rrect_bottom_left_y = 0.0f;
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
  bool effect_has_unsupported_filter = false;
  bool effect_has_backdrop_filter = false;
  bool effect_has_blend_mode = false;
  int effect_blend_mode = static_cast<int>(SkBlendMode::kSrcOver);
  uint64_t effect_output_clip_id = 0;
  std::vector<LiveExportedFilterOperation> effect_filter_operations;
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
  int stroke_cap = static_cast<int>(cc::PaintFlags::kButt_Cap);
  int stroke_join = static_cast<int>(cc::PaintFlags::kMiter_Join);
  float stroke_miter = 4.0f;
  float radius_x = 0.0f;
  float radius_y = 0.0f;
  std::array<SkVector, 4> corner_radii = {};
  std::vector<LiveExportedGlyph> glyphs;
  int mask_width = 0;
  int mask_height = 0;
  std::vector<uint8_t> path_bytes;
  std::vector<uint8_t> path_effect_bytes;
  std::vector<uint8_t> text_blob_bytes;
  std::vector<uint8_t> shader_bytes;
  std::vector<uint8_t> alpha_mask;
  std::vector<uint8_t> rgba_pixels;
  float src_x = 0.0f;
  float src_y = 0.0f;
  float src_width = 0.0f;
  float src_height = 0.0f;
  std::string sampling_options = "filter=nearest,mipmap=none";
  std::vector<LiveExportedDrawLooperLayer> draw_looper_layers;
  std::string debug_label;
  bool save_layer_bounds_unset = false;
};

struct LiveHitTestEntry {
  std::string element_id;
  DisplayItemClientId paint_client_id = kInvalidDisplayItemClientId;
  int paint_order = -1;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

struct LiveScrollableElementEntry {
  std::string element_id;
  DisplayItemClientId paint_client_id = kInvalidDisplayItemClientId;
  int paint_order = -1;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float scroll_x = 0.0f;
  float scroll_y = 0.0f;
  float max_scroll_x = 0.0f;
  float max_scroll_y = 0.0f;
  bool can_scroll_x = false;
  bool can_scroll_y = false;
};

struct LiveElementScrollOffset {
  float x = 0.0f;
  float y = 0.0f;
};

struct LiveElementScrollDiagnostic {
  std::string element_id;
  float requested_x = 0.0f;
  float requested_y = 0.0f;
  float applied_x = 0.0f;
  float applied_y = 0.0f;
  float max_x = 0.0f;
  float max_y = 0.0f;
  int contents_width = 0;
  int contents_height = 0;
  int visible_width = 0;
  int visible_height = 0;
  bool element_present = false;
  bool layout_box_present = false;
  bool scrollable_area_present = false;
  bool changed = false;
  std::string status = "not_requested";
};

struct EmptyClipChunkForStandaloneRenderer {
  gfx::Rect chunk_bounds;
  gfx::RectF clip_rect;
  std::optional<SkRRect> clip_rrect;
};

struct LiveFramePaintProbeCache {
  DummyPageHolder* holder = nullptr;
  LiveFramePaintProbeResult result;
  std::string body_html;
  std::string requested_element_attributes_serialized;
  std::unordered_map<std::string, std::string>
      requested_element_attributes_by_id_and_name;
  std::string requested_hovered_element_id;
  std::string requested_active_element_id;
  std::vector<LiveExportedDrawOp> exported_draw_ops;
  std::vector<LiveExportedChunkPropertyState> chunk_property_states;
  std::vector<std::string> chunk_stable_keys;
  std::vector<std::string> chunk_id_strings;
  std::vector<LiveHitTestEntry> hit_test_entries;
  std::vector<LiveScrollableElementEntry> scrollable_element_entries;
  std::vector<std::string> artifact_audit_lines;
  std::string raw_paint_artifact_audit_json;
  std::string sticky_position_diagnostics_json;
  int sticky_update_scroll_area_count = 0;
  int sticky_update_consumed_descendant_count = 0;
  int sticky_update_constrained_after_count = 0;
  int sticky_update_consumed_horizontal_count = 0;
  int sticky_update_consumed_vertical_count = 0;
  std::string requested_element_scroll_offsets_serialized;
  std::unordered_map<std::string, LiveElementScrollOffset>
      requested_element_scroll_offsets_by_id;
  std::vector<LiveElementScrollDiagnostic> element_scroll_diagnostics;
  int viewport_width = 320;
  int viewport_height = 200;
  float requested_scroll_x = 0.0f;
  float requested_scroll_y = 0.0f;
  float applied_scroll_x = 0.0f;
  float applied_scroll_y = 0.0f;
  float max_scroll_x = 0.0f;
  float max_scroll_y = 0.0f;
  int scroll_contents_width = 0;
  int scroll_contents_height = 0;
  int scroll_visible_width = 0;
  int scroll_visible_height = 0;
  int frame_view_width = 0;
  int frame_view_height = 0;
  int frame_layout_width = 0;
  int frame_layout_height = 0;
  int visual_viewport_width = 0;
  int visual_viewport_height = 0;
  int layout_view_border_width = 0;
  int layout_view_border_height = 0;
  int layout_view_scroll_width = 0;
  int layout_view_scroll_height = 0;
  int layout_view_fragment_count = 0;
  bool scroll_area_is_root_frame_viewport = false;
  bool scroll_offset_requested = false;
  bool scroll_offset_applied = false;
  bool scroll_offset_changed = false;
  std::string scroll_offset_status = "not_requested";
  bool element_scroll_offset_requested = false;
  bool element_scroll_offset_applied = false;
  bool element_scroll_offset_changed = false;
  double requested_animation_time_ms = 0.0;
  double applied_animation_time_ms = 0.0;
  bool animation_time_requested = false;
  bool animation_time_applied = false;
  std::string animation_time_status = "not_requested";
  double timing_total_ms = 0.0;
  double timing_input_setup_ms = 0.0;
  double timing_html_document_setup_ms = 0.0;
  double timing_style_update_ms = 0.0;
  double timing_layout_lifecycle_ms = 0.0;
  double timing_prepaint_and_paint_lifecycle_ms = 0.0;
  double timing_paint_artifact_generation_ms = 0.0;
  double timing_paint_artifact_audit_ms = 0.0;
  double timing_paint_artifact_extraction_ms = 0.0;
  bool timing_cache_hit = false;
  bool disable_retained_extraction = false;
  bool force_oracle_bitmap = false;
  bool trace_stages = false;
  std::string lifecycle_stop;
  ImageReachabilityDiagnostics image_reachability;
  bool initialized = false;
};

bool RectsMatchForStandaloneRenderer(const gfx::Rect& a, const gfx::Rect& b) {
  return a.x() == b.x() && a.y() == b.y() && a.width() == b.width() &&
         a.height() == b.height();
}

LiveFramePaintProbeCache& ProbeCache() {
  static LiveFramePaintProbeCache* cache = new LiveFramePaintProbeCache();
  return *cache;
}

using StandaloneProbeClock = std::chrono::steady_clock;

double StandaloneProbeElapsedMs(StandaloneProbeClock::time_point start,
                                StandaloneProbeClock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}

void TraceLiveFrameProbeStage(const char* stage) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.trace_stages) {
    return;
  }
  std::fprintf(stderr, "live_probe.stage=%s\n", stage ? stage : "(null)");
  std::fflush(stderr);
}

void TraceLiveFrameProbeStagef(const char* format,
                               wtf_size_t first,
                               wtf_size_t second = 0) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.trace_stages) {
    return;
  }
  char buffer[256];
  std::snprintf(buffer, sizeof(buffer), format,
                static_cast<unsigned long>(first),
                static_cast<unsigned long>(second));
  TraceLiveFrameProbeStage(buffer);
}

void ApplyDocumentScrollOffsetForStandaloneRenderer(LocalFrameView& frame_view) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.applied_scroll_x = 0.0f;
  cache.applied_scroll_y = 0.0f;
  cache.max_scroll_x = 0.0f;
  cache.max_scroll_y = 0.0f;
  cache.scroll_contents_width = 0;
  cache.scroll_contents_height = 0;
  cache.scroll_visible_width = 0;
  cache.scroll_visible_height = 0;
  cache.frame_view_width = frame_view.Size().width();
  cache.frame_view_height = frame_view.Size().height();
  cache.frame_layout_width = frame_view.GetLayoutSize().width();
  cache.frame_layout_height = frame_view.GetLayoutSize().height();
  cache.visual_viewport_width = 0;
  cache.visual_viewport_height = 0;
  if (Page* page = frame_view.GetFrame().GetPage()) {
    page->GetVisualViewport().SetSize(
        gfx::Size(cache.viewport_width, cache.viewport_height));
    const gfx::Size visual_viewport_size = page->GetVisualViewport().Size();
    cache.visual_viewport_width = visual_viewport_size.width();
    cache.visual_viewport_height = visual_viewport_size.height();
  }
  cache.layout_view_border_width = 0;
  cache.layout_view_border_height = 0;
  cache.layout_view_scroll_width = 0;
  cache.layout_view_scroll_height = 0;
  cache.layout_view_fragment_count = 0;
  if (LayoutView* layout_view = frame_view.GetLayoutView()) {
    if (layout_view->PhysicalFragmentCount()) {
      layout_view->SetScrollableOverflowFromLayoutResults();
      if (PaintLayerScrollableArea* layout_viewport =
              layout_view->GetScrollableArea()) {
        layout_viewport->UpdateAfterOverflowRecalc();
      }
    }
    if (!frame_view.GetRootFrameViewport() && layout_view->GetScrollableArea()) {
      frame_view.InitializeRootScroller();
    }
    const PhysicalRect border_box = layout_view->PhysicalBorderBoxRect();
    cache.layout_view_border_width = border_box.Width().ToInt();
    cache.layout_view_border_height = border_box.Height().ToInt();
    cache.layout_view_scroll_width = layout_view->ScrollWidth().ToInt();
    cache.layout_view_scroll_height = layout_view->ScrollHeight().ToInt();
    cache.layout_view_fragment_count =
        static_cast<int>(layout_view->PhysicalFragmentCount());
  }
  cache.scroll_area_is_root_frame_viewport = false;
  cache.scroll_offset_applied = false;
  cache.scroll_offset_changed = false;
  cache.scroll_offset_status = cache.scroll_offset_requested ? "requested"
                                                             : "not_requested";
  ScrollableArea* viewport = frame_view.GetScrollableArea();
  if (!viewport) {
    cache.scroll_offset_status = "frame_scrollable_area_missing";
    return;
  }
  cache.scroll_area_is_root_frame_viewport =
      static_cast<ScrollableArea*>(frame_view.GetRootFrameViewport()) ==
      viewport;
  const ScrollOffset maximum = viewport->MaximumScrollOffset();
  cache.max_scroll_x = maximum.x();
  cache.max_scroll_y = maximum.y();
  const gfx::Size contents_size = viewport->ContentsSize();
  cache.scroll_contents_width = contents_size.width();
  cache.scroll_contents_height = contents_size.height();
  const gfx::Rect visible_rect =
      viewport->VisibleContentRect(kExcludeScrollbars);
  cache.scroll_visible_width = visible_rect.width();
  cache.scroll_visible_height = visible_rect.height();
  if (cache.scroll_offset_requested) {
    const ScrollOffset requested_offset = viewport->ScrollPositionToOffset(
        gfx::PointF(cache.requested_scroll_x, cache.requested_scroll_y));
    const ScrollOffset clamped_offset =
        viewport->ClampScrollOffset(requested_offset);
    cache.scroll_offset_changed = viewport->SetScrollOffset(
        clamped_offset, mojom::blink::ScrollType::kProgrammatic,
        cc::ScrollSourceType::kAbsoluteScroll,
        mojom::blink::ScrollBehavior::kInstant);
    cache.scroll_offset_status = "applied_to_frame_scrollable_area";
  }
  const gfx::PointF applied_position = viewport->ScrollPosition();
  cache.applied_scroll_x = applied_position.x();
  cache.applied_scroll_y = applied_position.y();
  cache.scroll_offset_applied = true;
}

bool LifecycleStopEqualsForStandaloneRenderer(const char* value) {
  const std::string& lifecycle_stop = ProbeCache().lifecycle_stop;
  return !lifecycle_stop.empty() && lifecycle_stop == value;
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

void AppendDrawLooperLayers(const cc::PaintFlags& flags,
                            LiveExportedDrawOp& exported) {
  const sk_sp<cc::DrawLooper>& looper = flags.getLooper();
  if (!looper) {
    return;
  }
  looper->ForEachLayer([&exported](SkPoint offset, float blur_sigma,
                                   SkColor4f color, uint32_t flags) {
    LiveExportedDrawLooperLayer layer;
    layer.offset_x = offset.fX;
    layer.offset_y = offset.fY;
    layer.blur_sigma = blur_sigma;
    layer.r = color.fR;
    layer.g = color.fG;
    layer.b = color.fB;
    layer.a = color.fA;
    layer.flags = flags;
    exported.draw_looper_layers.push_back(layer);
  });
}

void AppendStrokeStyle(const cc::PaintFlags& flags,
                       LiveExportedDrawOp& exported) {
  exported.stroke_cap = static_cast<int>(flags.getStrokeCap());
  exported.stroke_join = static_cast<int>(flags.getStrokeJoin());
  exported.stroke_miter = flags.getStrokeMiter();
}

std::vector<uint8_t> SerializePathEffectBytes(const cc::PaintFlags& flags) {
  SkPaint paint = flags.ToSkPaint();
  sk_sp<SkPathEffect> path_effect = paint.refPathEffect();
  if (!path_effect) {
    return {};
  }
  sk_sp<SkData> data = path_effect->serialize();
  if (!data || data->isEmpty()) {
    return {};
  }
  const auto* bytes = static_cast<const uint8_t*>(data->data());
  return std::vector<uint8_t>(bytes, bytes + data->size());
}

void AppendFillRectOp(float x,
                      float y,
                      float width,
                      float height,
                      const SkColor4f& color,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops,
                      const cc::PaintFlags* flags = nullptr) {
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
  if (flags) {
    AppendDrawLooperLayers(*flags, exported);
  }
  exported_draw_ops.push_back(exported);
}

void AppendSkRectFillOp(const SkRect& rect,
                        float translate_x,
                        float translate_y,
                        const SkColor4f& color,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops,
                        const cc::PaintFlags* flags = nullptr) {
  if (!rect.isFinite()) {
    return;
  }
  AppendFillRectOp(translate_x + rect.x(), translate_y + rect.y(),
                   rect.width(), rect.height(), color, exported_draw_ops,
                   flags);
}

void AppendSkIRectFillOp(const SkIRect& rect,
                         float translate_x,
                         float translate_y,
                         const SkColor4f& color,
                         std::vector<LiveExportedDrawOp>& exported_draw_ops,
                         const cc::PaintFlags* flags = nullptr) {
  AppendFillRectOp(translate_x + static_cast<float>(rect.x()),
                   translate_y + static_cast<float>(rect.y()),
                   static_cast<float>(rect.width()),
                   static_cast<float>(rect.height()), color,
                   exported_draw_ops, flags);
}

void AppendStrokeRectOp(float x,
                        float y,
                        float width,
                        float height,
                        SkScalar stroke_width,
                        const SkColor4f& color,
                        std::vector<LiveExportedDrawOp>& exported_draw_ops,
                        const cc::PaintFlags* flags = nullptr) {
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
  if (flags) {
    AppendStrokeStyle(*flags, exported);
    exported.path_effect_bytes = SerializePathEffectBytes(*flags);
  }
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
                   std::vector<LiveExportedDrawOp>& exported_draw_ops,
                   const cc::PaintFlags* flags = nullptr) {
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
  if (flags) {
    AppendDrawLooperLayers(*flags, exported);
    if (stroke) {
      AppendStrokeStyle(*flags, exported);
      exported.path_effect_bytes = SerializePathEffectBytes(*flags);
    }
  }
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
    exported.save_layer_bounds_unset = true;
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

std::vector<LiveExportedFilterOperation> ExportFilterOperationsForStandaloneRenderer(
    const CompositorFilterOperations* filters,
    bool* has_unsupported_operation) {
  std::vector<LiveExportedFilterOperation> exported;
  if (has_unsupported_operation) {
    *has_unsupported_operation = false;
  }
  if (!filters) {
    return exported;
  }
  for (const cc::FilterOperation& operation :
       filters->AsCcFilterOperations().operations()) {
    LiveExportedFilterOperation out;
    switch (operation.type()) {
      case cc::FilterOperation::SATURATE:
        out.type = kStandaloneFilterSaturate;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::BRIGHTNESS:
        out.type = kStandaloneFilterBrightness;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::GRAYSCALE:
      case cc::FilterOperation::SEPIA:
      case cc::FilterOperation::HUE_ROTATE:
      case cc::FilterOperation::INVERT:
      case cc::FilterOperation::CONTRAST:
      case cc::FilterOperation::OPACITY:
      case cc::FilterOperation::BLUR:
      case cc::FilterOperation::DROP_SHADOW:
      case cc::FilterOperation::COLOR_MATRIX:
      case cc::FilterOperation::ZOOM:
      case cc::FilterOperation::REFERENCE:
      case cc::FilterOperation::SATURATING_BRIGHTNESS:
      case cc::FilterOperation::ALPHA_THRESHOLD:
      case cc::FilterOperation::OFFSET:
        if (has_unsupported_operation) {
          *has_unsupported_operation = true;
        }
        continue;
    }
    exported.push_back(out);
  }
  return exported;
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
  hash = HashCombineForStandaloneRenderer(hash, state.has_clip_rrect ? 1u : 0u);
  if (state.has_clip_rrect) {
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_y));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_width));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_height));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_top_left_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_top_left_y));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_top_right_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_top_right_y));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_bottom_right_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_bottom_right_y));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_bottom_left_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(state.clip_rrect_bottom_left_y));
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
      hash, state.effect_has_unsupported_filter ? 1u : 0u);
  for (const LiveExportedFilterOperation& operation :
       state.effect_filter_operations) {
    hash = HashCombineForStandaloneRenderer(hash,
                                            static_cast<uint64_t>(operation.type));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.amount));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.offset_x));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.offset_y));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.color_r));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.color_g));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.color_b));
    hash = HashCombineForStandaloneRenderer(
        hash, HashFloatForStandaloneRenderer(operation.color_a));
    for (float value : operation.matrix) {
      hash = HashCombineForStandaloneRenderer(
          hash, HashFloatForStandaloneRenderer(value));
    }
  }
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

uint32_t TransformChainDepthForStandaloneRenderer(
    const TransformPaintPropertyNode& transform);
uint32_t ClipChainDepthForStandaloneRenderer(const ClipPaintPropertyNode& clip);
uint32_t EffectChainDepthForStandaloneRenderer(
    const EffectPaintPropertyNode& effect);

const FloatRoundedRect* RoundedClipInChainForStandaloneRenderer(
    const ClipPaintPropertyNode& clip) {
  const auto* node = &clip;
  const auto* root = &PropertyTreeState::Root().Clip();
  uint32_t depth = 0;
  while (node && depth < 256) {
    const FloatRoundedRect& paint_clip = node->PaintClipRect();
    if (paint_clip.IsRounded()) {
      return &paint_clip;
    }
    if (node == root) {
      break;
    }
    node = node->UnaliasedParent();
    ++depth;
  }
  return nullptr;
}

std::optional<SkRRect> RoundedClipRRectForStandaloneRenderer(
    const ClipPaintPropertyNode& clip,
    const gfx::RectF& clip_rect) {
  const FloatRoundedRect* rounded_clip =
      RoundedClipInChainForStandaloneRenderer(clip);
  if (!rounded_clip) {
    return std::nullopt;
  }
  const FloatRoundedRect::Radii& radii = rounded_clip->GetRadii();
  SkVector sk_radii[4] = {
      SkVector::Make(radii.TopLeft().width(), radii.TopLeft().height()),
      SkVector::Make(radii.TopRight().width(), radii.TopRight().height()),
      SkVector::Make(radii.BottomRight().width(),
                     radii.BottomRight().height()),
      SkVector::Make(radii.BottomLeft().width(), radii.BottomLeft().height()),
  };
  SkRRect rrect;
  rrect.setRectRadii(SkRect::MakeXYWH(clip_rect.x(), clip_rect.y(),
                                      clip_rect.width(), clip_rect.height()),
                     sk_radii);
  if (rrect.isEmpty()) {
    return std::nullopt;
  }
  return rrect;
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
  if (const auto* parent = chunk_state.Transform().UnaliasedParent()) {
    state.transform_parent_id = reinterpret_cast<uintptr_t>(parent);
  }
  state.clip_node_id = reinterpret_cast<uintptr_t>(&chunk_state.Clip());
  if (const auto* parent = chunk_state.Clip().UnaliasedParent()) {
    state.clip_parent_id = reinterpret_cast<uintptr_t>(parent);
  }
  state.clip_local_transform_id =
      reinterpret_cast<uintptr_t>(&chunk_state.Clip().LocalTransformSpace().Unalias());
  state.effect_node_id = reinterpret_cast<uintptr_t>(&chunk_state.Effect());
  if (const auto* parent = chunk_state.Effect().UnaliasedParent()) {
    state.effect_parent_id = reinterpret_cast<uintptr_t>(parent);
  }
  state.effect_chain_depth =
      EffectChainDepthForStandaloneRenderer(chunk_state.Effect());
  state.transform_chain_depth =
      TransformChainDepthForStandaloneRenderer(chunk_state.Transform());
  state.clip_chain_depth = ClipChainDepthForStandaloneRenderer(chunk_state.Clip());
  state.effect_opacity = chunk_state.Effect().Opacity();
  state.effect_has_non_default_opacity = state.effect_opacity != 1.0f;
  state.effect_has_filter = chunk_state.Effect().Filter() != nullptr;
  state.effect_filter_operations = ExportFilterOperationsForStandaloneRenderer(
      chunk_state.Effect().Filter(), &state.effect_has_unsupported_filter);
  state.effect_has_backdrop_filter =
      chunk_state.Effect().BackdropFilter() != nullptr;
  state.effect_has_blend_mode =
      chunk_state.Effect().BlendMode() != SkBlendMode::kSrcOver;
  state.effect_blend_mode = static_cast<int>(chunk_state.Effect().BlendMode());
  state.effect_output_clip_id =
      chunk_state.Effect().OutputClip()
          ? reinterpret_cast<uintptr_t>(&chunk_state.Effect().OutputClip()->Unalias())
          : 0;
  if (const auto* scroll = chunk_state.Transform().ScrollNode()) {
    state.scroll_node_id = reinterpret_cast<uintptr_t>(scroll);
    if (const auto* parent = scroll->UnaliasedParent()) {
      state.scroll_parent_id = reinterpret_cast<uintptr_t>(parent);
    }
    state.scroll_container_x = scroll->ContainerRect().x();
    state.scroll_container_y = scroll->ContainerRect().y();
    state.scroll_container_width = scroll->ContainerRect().width();
    state.scroll_container_height = scroll->ContainerRect().height();
    const gfx::Rect contents = scroll->ContentsRect();
    state.scroll_contents_x = contents.x();
    state.scroll_contents_y = contents.y();
    state.scroll_contents_width = contents.width();
    state.scroll_contents_height = contents.height();
  }
  state.clip_has_rounded_clip =
      chunk_state.Clip().PaintClipRect().IsRounded() ||
      chunk_state.Clip().LayoutClipRect().HasRadius();
  state.clip_has_path_clip = chunk_state.Clip().ClipPath().has_value();
  if (!clip.IsInfinite()) {
    const gfx::RectF& rect = clip.Rect();
    state.has_clip_rect = true;
    state.clip_x = rect.x();
    state.clip_y = rect.y();
    state.clip_width = rect.width();
    state.clip_height = rect.height();
  }
  if (state.has_clip_rect) {
    if (const FloatRoundedRect* rounded_clip =
            RoundedClipInChainForStandaloneRenderer(chunk_state.Clip())) {
      const FloatRoundedRect::Radii& radii = rounded_clip->GetRadii();
      state.has_clip_rrect = true;
      state.clip_rrect_x = state.clip_x;
      state.clip_rrect_y = state.clip_y;
      state.clip_rrect_width = state.clip_width;
      state.clip_rrect_height = state.clip_height;
      state.clip_rrect_top_left_x = radii.TopLeft().width();
      state.clip_rrect_top_left_y = radii.TopLeft().height();
      state.clip_rrect_top_right_x = radii.TopRight().width();
      state.clip_rrect_top_right_y = radii.TopRight().height();
      state.clip_rrect_bottom_right_x = radii.BottomRight().width();
      state.clip_rrect_bottom_right_y = radii.BottomRight().height();
      state.clip_rrect_bottom_left_x = radii.BottomLeft().width();
      state.clip_rrect_bottom_left_y = radii.BottomLeft().height();
    }
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

SkRect SkRectFromGfxRectForStandaloneRenderer(const gfx::Rect& rect) {
  return SkRect::MakeXYWH(static_cast<SkScalar>(rect.x()),
                          static_cast<SkScalar>(rect.y()),
                          static_cast<SkScalar>(rect.width()),
                          static_cast<SkScalar>(rect.height()));
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
                       flags.getColor4f(), exported_draw_ops, &flags);
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
                       exported_draw_ops, &flags);
    return;
  }
  AppendSkIRectFillOp(rect, translate_x, translate_y, flags.getColor4f(),
                      exported_draw_ops, &flags);
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
                exported_draw_ops, &flags);
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
  AppendStrokeStyle(flags, exported);
  exported.path_bytes.resize(path_byte_count);
  path.writeToMemory(exported.path_bytes.data());

  if (flags.HasShader()) {
    exported.shader_bytes = SerializeShaderBytes(flags);
  }
  exported.path_effect_bytes = SerializePathEffectBytes(flags);

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
  {
    SkTextBlob::Iter iter(*text_op.blob);
    SkTextBlob::Iter::Run run;
    while (iter.next(&run)) {
      if (run.fTypeface) {
        StandaloneRendererRegisterSameProcessTypefaceForSkTextBlob(
            run.fTypeface);
      }
    }
  }
  SkSerialProcs procs;
  procs.fTypefaceProc = [](SkTypeface* typeface,
                           void*) -> sk_sp<const SkData> {
    if (!typeface) {
      return nullptr;
    }
    StandaloneTypefacePayload payload;
    payload.typeface_resource_id =
        StandaloneRendererRegisterSameProcessTypefaceForSkTextBlob(typeface);
    if (payload.typeface_resource_id == 0) {
      return nullptr;
    }
    return SkData::MakeWithCopy(&payload, sizeof(payload));
  };
  sk_sp<SkData> serialized_blob = text_op.blob->serialize(procs);
  if (serialized_blob && serialized_blob->size() > 0) {
    LiveExportedDrawOp exported;
    exported.type = 18;
    exported.x = text_op.x;
    exported.y = text_op.y;
    AppendSkColor(exported, text_op.flags.getColor4f());
    AppendDrawLooperLayers(text_op.flags, exported);
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

bool AppendPaintImageResourceOp(
    const cc::PaintImage& paint_image,
    const SkRect& src,
    const SkRect& dst,
    const SkSamplingOptions& sampling,
    float translate_x,
    float translate_y,
    const char* debug_label,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!src.isFinite() || !dst.isFinite() || src.width() <= 0.0f ||
      src.height() <= 0.0f || dst.width() <= 0.0f || dst.height() <= 0.0f) {
    return false;
  }

  sk_sp<SkImage> image = paint_image.GetSwSkImage();
  if (!image || image->width() <= 0 || image->height() <= 0) {
    return false;
  }

  constexpr int kMaxImagePixels = 16 * 1024 * 1024;
  if (static_cast<int64_t>(image->width()) * image->height() >
      kMaxImagePixels) {
    return false;
  }

  std::vector<uint8_t> rgba_pixels(static_cast<size_t>(image->width()) *
                                   static_cast<size_t>(image->height()) * 4u);
  SkImageInfo info =
      SkImageInfo::Make(image->width(), image->height(), kRGBA_8888_SkColorType,
                        kPremul_SkAlphaType);
  if (!image->readPixels(nullptr, info, rgba_pixels.data(),
                         static_cast<size_t>(image->width()) * 4u, 0, 0)) {
    return false;
  }

  LiveExportedDrawOp exported;
  exported.type = 22;
  exported.x = translate_x + dst.x();
  exported.y = translate_y + dst.y();
  exported.width = dst.width();
  exported.height = dst.height();
  exported.mask_width = image->width();
  exported.mask_height = image->height();
  exported.src_x = src.x();
  exported.src_y = src.y();
  exported.src_width = src.width();
  exported.src_height = src.height();
  if (sampling.isAniso()) {
    exported.sampling_options =
        "aniso=" + std::to_string(sampling.maxAniso);
  } else if (sampling.useCubic) {
    exported.sampling_options = "cubic=B" + std::to_string(sampling.cubic.B) +
                                ",C" + std::to_string(sampling.cubic.C);
  } else {
    exported.sampling_options =
        std::string("filter=") +
        (sampling.filter == SkFilterMode::kLinear ? "linear" : "nearest") +
        ",mipmap=" +
        (sampling.mipmap == SkMipmapMode::kLinear
             ? "linear"
             : sampling.mipmap == SkMipmapMode::kNearest ? "nearest"
                                                         : "none");
  }
  exported.rgba_pixels = std::move(rgba_pixels);
  exported.debug_label = debug_label ? debug_label : "DrawImageRectOp";
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
        const SkRect src = SkRect::MakeWH(
            static_cast<SkScalar>(image_op.image.width()),
            static_cast<SkScalar>(image_op.image.height()));
        const SkRect dst =
            SkRect::MakeXYWH(image_op.left, image_op.top, src.width(),
                             src.height());
        if (!AppendPaintImageResourceOp(image_op.image, src, dst,
                                        image_op.sampling, translate_x,
                                        translate_y, "DrawImageOp",
                                        exported_draw_ops)) {
          mark_unsupported(op);
        }
        break;
      }
      case cc::PaintOpType::kDrawImageRect: {
        const auto& image_op = static_cast<const cc::DrawImageRectOp&>(op);
        if (!AppendPaintImageResourceOp(image_op.image, image_op.src,
                                        image_op.dst, image_op.sampling,
                                        translate_x, translate_y,
                                        "DrawImageRectOp",
                                        exported_draw_ops)) {
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
      case cc::PaintOpType::kDrawOval: {
        const auto& oval_op = static_cast<const cc::DrawOvalOp&>(op);
        SkPath path = SkPathBuilder().addOval(oval_op.oval).detach();
        AppendSkPathOpWithFlags(path, translate_x, translate_y, oval_op.flags,
                                exported_draw_ops);
        break;
      }
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
  std::optional<EmptyClipChunkForStandaloneRenderer> empty_clip_chunk;
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
      empty_clip_chunk.reset();
      continue;
    }
    const FloatClipRect clip = GeometryMapper::LocalToAncestorClipRect(
        chunk_state, PropertyTreeState::Root());
    FloatClipRect effective_clip = clip;
    std::optional<SkRRect> effective_clip_rrect;
    const bool has_display_items = chunk.begin_index != chunk.end_index;
    if (has_display_items && clip.IsInfinite() && empty_clip_chunk &&
        RectsMatchForStandaloneRenderer(empty_clip_chunk->chunk_bounds,
                                        chunk.bounds)) {
      effective_clip = FloatClipRect(empty_clip_chunk->clip_rect);
      effective_clip_rrect = empty_clip_chunk->clip_rrect;
    }
    AppendBeginChunkOp(chunk_index, chunk.bounds, exported_draw_ops);
    AppendSaveOp(exported_draw_ops);
    AppendChunkPropertyStateForStandaloneRenderer(chunk_index, chunk_state,
                                                  projection, effective_clip,
                                                  property_states);
    if (effective_clip_rrect) {
      AppendClipRRectOp(*effective_clip_rrect, 0.0f, 0.0f,
                        SkClipOp::kIntersect, exported_draw_ops);
    }
    if (!effective_clip.IsInfinite()) {
      AppendClipRectOp(effective_clip.Rect(), exported_draw_ops);
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
    if (!has_display_items && !clip.IsInfinite() && !chunk.bounds.IsEmpty()) {
      empty_clip_chunk =
          EmptyClipChunkForStandaloneRenderer{
              chunk.bounds, clip.Rect(),
              RoundedClipRRectForStandaloneRenderer(chunk_state.Clip(),
                                                    clip.Rect())};
    } else {
      empty_clip_chunk.reset();
    }
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
  const EffectPaintPropertyNode* active_opacity_effect = nullptr;
  for (wtf_size_t chunk_index = 0; chunk_index < chunks.size();
       ++chunk_index) {
    const PaintChunk& chunk = chunks[chunk_index];
    const PropertyTreeState chunk_state = chunk.properties.Unalias();
    const EffectPaintPropertyNode* chunk_effect = &chunk_state.Effect();
    const float effect_opacity = chunk_effect->Opacity();
    const bool needs_effect_opacity_layer =
        effect_opacity >= 0.0f && effect_opacity < 1.0f;
    if (active_opacity_effect &&
        (!needs_effect_opacity_layer ||
         chunk_effect != active_opacity_effect)) {
      canvas->restore();
      active_opacity_effect = nullptr;
    }
    if (needs_effect_opacity_layer && !active_opacity_effect) {
      gfx::Rect opacity_layer_bounds = chunk.bounds;
      for (wtf_size_t next_chunk_index = chunk_index + 1;
           next_chunk_index < chunks.size(); ++next_chunk_index) {
        const PaintChunk& next_chunk = chunks[next_chunk_index];
        const PropertyTreeState next_chunk_state =
            next_chunk.properties.Unalias();
        const EffectPaintPropertyNode* next_effect =
            &next_chunk_state.Effect();
        if (next_effect != chunk_effect ||
            next_effect->Opacity() != effect_opacity) {
          break;
        }
        opacity_layer_bounds.Union(next_chunk.bounds);
      }
      SkPaint layer_paint;
      layer_paint.setAlphaf(effect_opacity);
      canvas->saveLayer(SkRectFromGfxRectForStandaloneRenderer(
                            opacity_layer_bounds),
                        &layer_paint);
      active_opacity_effect = chunk_effect;
    }
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
  if (active_opacity_effect) {
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

Element* FindElementByClassForStandaloneRenderer(Node& node,
                                                 const AtomicString& class_name) {
  if (auto* element = DynamicTo<Element>(node)) {
    if (element->HasClassName(class_name)) {
      return element;
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    if (Element* found =
            FindElementByClassForStandaloneRenderer(*child, class_name)) {
      return found;
    }
  }
  return nullptr;
}

Element* FindElementByTagForStandaloneRenderer(Node& node,
                                               const QualifiedName& tag_name) {
  if (auto* element = DynamicTo<Element>(node)) {
    if (element->HasTagName(tag_name)) {
      return element;
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    if (Element* found =
            FindElementByTagForStandaloneRenderer(*child, tag_name)) {
      return found;
    }
  }
  return nullptr;
}

Element* FindElementByAttributeForStandaloneRenderer(
    Node& node,
    const AtomicString& attribute_name) {
  if (auto* element = DynamicTo<Element>(node)) {
    if (element->hasAttribute(attribute_name)) {
      return element;
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    if (Element* found =
            FindElementByAttributeForStandaloneRenderer(*child,
                                                        attribute_name)) {
      return found;
    }
  }
  return nullptr;
}

Element* FindElementByAttributeValueForStandaloneRenderer(
    Node& node,
    const AtomicString& attribute_name,
    const AtomicString& attribute_value) {
  if (auto* element = DynamicTo<Element>(node)) {
    if (element->getAttribute(attribute_name) == attribute_value) {
      return element;
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    if (Element* found = FindElementByAttributeValueForStandaloneRenderer(
            *child, attribute_name, attribute_value)) {
      return found;
    }
  }
  return nullptr;
}

std::string JsonStringForStandaloneRenderer(const std::string& value);
std::string BlinkStringToStdStringForStandaloneRenderer(const String& value);
std::string RectJsonForStandaloneRenderer(const gfx::Rect& rect);
std::string PhysicalRectJsonForStandaloneRenderer(const PhysicalRect& rect);
std::string PhysicalOffsetJsonForStandaloneRenderer(const PhysicalOffset& offset);
std::string GfxRectJsonForStandaloneRenderer(const gfx::Rect& rect);
std::string GfxRectFJsonForStandaloneRenderer(const gfx::RectF& rect);
uint64_t NodeIdForStandaloneRenderer(const void* node);

gfx::RectF HitTestRectForStandaloneRenderer(Element& element,
                                            LayoutObject& layout_object) {
  const gfx::RectF client_rect =
      element.GetBoundingClientRectNoLifecycleUpdate();
  const auto* box = DynamicTo<LayoutBox>(&layout_object);
  if (!box || !layout_object.View()) {
    return client_rect;
  }

  PhysicalRect mapped_border_box = box->PhysicalBorderBoxRect();
  if (!layout_object.MapToVisualRectInAncestorSpace(layout_object.View(),
                                                    mapped_border_box)) {
    return client_rect;
  }

  const gfx::RectF clipped_rect(mapped_border_box.X().ToFloat(),
                                mapped_border_box.Y().ToFloat(),
                                mapped_border_box.Width().ToFloat(),
                                mapped_border_box.Height().ToFloat());
  if (clipped_rect.width() <= 0.0f || clipped_rect.height() <= 0.0f) {
    return gfx::RectF();
  }
  return clipped_rect;
}

void CollectLiveHitTestEntriesForStandaloneRenderer(
    Node* node,
    std::vector<LiveHitTestEntry>& entries) {
  if (!node || entries.size() >= 4096) {
    return;
  }
  if (auto* element = DynamicTo<Element>(node)) {
    const AtomicString& id = element->GetIdAttribute();
    if (!id.empty() && element->GetLayoutObject()) {
      const gfx::RectF rect = HitTestRectForStandaloneRenderer(
          *element, *element->GetLayoutObject());
      if (rect.width() > 0.0f && rect.height() > 0.0f) {
        LiveHitTestEntry entry;
        entry.element_id =
            BlinkStringToStdStringForStandaloneRenderer(String(id));
        entry.paint_client_id = element->GetLayoutObject()->Id();
        entry.x = rect.x();
        entry.y = rect.y();
        entry.width = rect.width();
        entry.height = rect.height();
        entries.push_back(std::move(entry));
      }
    }
  }
  for (Node* child = node->firstChild(); child && entries.size() < 4096;
       child = child->nextSibling()) {
    CollectLiveHitTestEntriesForStandaloneRenderer(child, entries);
  }
}

void CollectLiveScrollableElementEntriesForStandaloneRenderer(
    Node* node,
    std::vector<LiveScrollableElementEntry>& entries) {
  if (!node || entries.size() >= 512) {
    return;
  }
  if (auto* element = DynamicTo<Element>(node)) {
    const AtomicString& id = element->GetIdAttribute();
    LayoutObject* layout_object = element->GetLayoutObject();
    auto* box = DynamicTo<LayoutBox>(layout_object);
    if (!id.empty() && box && box->IsScrollContainer()) {
      PaintLayerScrollableArea* scrollable_area = box->GetScrollableArea();
      if (scrollable_area) {
        scrollable_area->UpdateAfterOverflowRecalc();
        const ScrollOffset maximum = scrollable_area->MaximumScrollOffset();
        const bool can_scroll_x = maximum.x() > 0.001f;
        const bool can_scroll_y = maximum.y() > 0.001f;
        const gfx::RectF rect =
            HitTestRectForStandaloneRenderer(*element, *layout_object);
        if ((can_scroll_x || can_scroll_y) && rect.width() > 0.0f &&
            rect.height() > 0.0f) {
          const gfx::PointF scroll_position = scrollable_area->ScrollPosition();
          LiveScrollableElementEntry entry;
          entry.element_id =
              BlinkStringToStdStringForStandaloneRenderer(String(id));
          entry.paint_client_id = layout_object->Id();
          entry.x = rect.x();
          entry.y = rect.y();
          entry.width = rect.width();
          entry.height = rect.height();
          entry.scroll_x = scroll_position.x();
          entry.scroll_y = scroll_position.y();
          entry.max_scroll_x = maximum.x();
          entry.max_scroll_y = maximum.y();
          entry.can_scroll_x = can_scroll_x;
          entry.can_scroll_y = can_scroll_y;
          entries.push_back(std::move(entry));
        }
      }
    }
  }
  for (Node* child = node->firstChild(); child && entries.size() < 512;
       child = child->nextSibling()) {
    CollectLiveScrollableElementEntriesForStandaloneRenderer(child, entries);
  }
}

std::string JsonStringForStandaloneRenderer(const std::string& value);

std::string StickyPositionDiagnosticsJsonForStandaloneRenderer(Node* node) {
  struct StickyEntry {
    std::string element_id;
    bool has_constraints = false;
    float offset_x = 0.0f;
    float offset_y = 0.0f;
  };

  struct StickyDiagnostics {
    int source_sticky_count = 0;
    int layout_sticky_count = 0;
    int constrained_sticky_count = 0;
    int fragment_sticky_descendant_count = 0;
    int consumed_sticky_descendant_count = 0;
    int pending_sticky_descendant_count = 0;
    int scroll_container_count = 0;
    int scroll_container_with_consumed_sticky_count = 0;
    std::vector<StickyEntry> entries;
  };

  StickyDiagnostics diagnostics;
  std::function<void(Node*)> walk = [&](Node* current) {
    if (!current) {
      return;
    }
    if (auto* element = DynamicTo<Element>(current)) {
      LayoutObject* layout_object = element->GetLayoutObject();
      if (layout_object &&
          layout_object->StyleRef().HasStickyConstrainedPosition()) {
        ++diagnostics.source_sticky_count;
      }
      if (auto* box_model = DynamicTo<LayoutBoxModelObject>(layout_object)) {
        if (box_model->StyleRef().HasStickyConstrainedPosition()) {
          ++diagnostics.layout_sticky_count;
          const bool has_constraints = box_model->HasStickyConstraints();
          if (has_constraints) {
            ++diagnostics.constrained_sticky_count;
          }
          if (diagnostics.entries.size() < 16) {
            const PhysicalOffset offset = box_model->StickyPositionOffset();
            StickyEntry entry;
            entry.element_id = BlinkStringToStdStringForStandaloneRenderer(
                String(element->GetIdAttribute()));
            entry.has_constraints = has_constraints;
            entry.offset_x = offset.left.ToFloat();
            entry.offset_y = offset.top.ToFloat();
            diagnostics.entries.push_back(std::move(entry));
          }
        }
      }
      if (auto* box = DynamicTo<LayoutBox>(layout_object)) {
        if (box->IsScrollContainer()) {
          ++diagnostics.scroll_container_count;
        }
        bool scroll_container_has_consumed_sticky = false;
        for (const auto& fragment : box->PhysicalFragments()) {
          for (const auto& item : fragment.StickyDescendants()) {
            ++diagnostics.fragment_sticky_descendant_count;
            if (item.GetIfConsumed()) {
              ++diagnostics.consumed_sticky_descendant_count;
              scroll_container_has_consumed_sticky = true;
            }
            if (item.GetIfPending()) {
              ++diagnostics.pending_sticky_descendant_count;
            }
          }
        }
        if (box->IsScrollContainer() && scroll_container_has_consumed_sticky) {
          ++diagnostics.scroll_container_with_consumed_sticky_count;
        }
      }
    }
    for (Node* child = current->firstChild(); child; child = child->nextSibling()) {
      walk(child);
    }
  };
  walk(node);

  std::ostringstream json;
  json << "{\"source_sticky_count\":" << diagnostics.source_sticky_count
       << ",\"layout_sticky_count\":" << diagnostics.layout_sticky_count
       << ",\"constrained_sticky_count\":"
       << diagnostics.constrained_sticky_count
       << ",\"fragment_sticky_descendant_count\":"
       << diagnostics.fragment_sticky_descendant_count
       << ",\"consumed_sticky_descendant_count\":"
       << diagnostics.consumed_sticky_descendant_count
       << ",\"pending_sticky_descendant_count\":"
       << diagnostics.pending_sticky_descendant_count
       << ",\"scroll_container_count\":" << diagnostics.scroll_container_count
       << ",\"scroll_container_with_consumed_sticky_count\":"
       << diagnostics.scroll_container_with_consumed_sticky_count
       << ",\"entries\":[";
  for (size_t i = 0; i < diagnostics.entries.size(); ++i) {
    if (i) {
      json << ",";
    }
    const StickyEntry& entry = diagnostics.entries[i];
    json << "{\"element_id\":"
         << JsonStringForStandaloneRenderer(entry.element_id)
         << ",\"has_constraints\":"
         << (entry.has_constraints ? "true" : "false")
         << ",\"sticky_offset\":{\"x\":" << entry.offset_x
         << ",\"y\":" << entry.offset_y << "}}";
  }
  json << "]}";
  return json.str();
}

void SortLiveHitTestEntriesByPaintOrderForStandaloneRenderer(
    const PaintArtifact& artifact,
    std::vector<LiveHitTestEntry>& entries) {
  if (entries.empty()) {
    return;
  }

  std::unordered_map<DisplayItemClientId, int> last_paint_order_by_client;
  const DisplayItemList& display_items = artifact.GetDisplayItemList();
  for (wtf_size_t item_index = 0; item_index < display_items.size();
       ++item_index) {
    const DisplayItem& item = display_items[item_index];
    if (!item.IsDrawing()) {
      continue;
    }
    const DisplayItemClientId paint_client_id = item.ClientId();
    if (paint_client_id == kInvalidDisplayItemClientId) {
      continue;
    }
    last_paint_order_by_client[paint_client_id] = static_cast<int>(item_index);
  }

  for (LiveHitTestEntry& entry : entries) {
    const auto order = last_paint_order_by_client.find(entry.paint_client_id);
    if (order != last_paint_order_by_client.end()) {
      entry.paint_order = order->second;
    }
  }

  std::stable_sort(entries.begin(), entries.end(),
                   [](const LiveHitTestEntry& a,
                      const LiveHitTestEntry& b) {
                     return a.paint_order < b.paint_order;
                   });
}

void SortLiveScrollableElementEntriesByPaintOrderForStandaloneRenderer(
    const PaintArtifact& artifact,
    std::vector<LiveScrollableElementEntry>& entries) {
  if (entries.empty()) {
    return;
  }

  std::unordered_map<DisplayItemClientId, int> last_paint_order_by_client;
  const DisplayItemList& display_items = artifact.GetDisplayItemList();
  for (wtf_size_t item_index = 0; item_index < display_items.size();
       ++item_index) {
    const DisplayItem& item = display_items[item_index];
    if (!item.IsDrawing()) {
      continue;
    }
    const DisplayItemClientId paint_client_id = item.ClientId();
    if (paint_client_id == kInvalidDisplayItemClientId) {
      continue;
    }
    last_paint_order_by_client[paint_client_id] = static_cast<int>(item_index);
  }

  for (LiveScrollableElementEntry& entry : entries) {
    const auto order = last_paint_order_by_client.find(entry.paint_client_id);
    if (order != last_paint_order_by_client.end()) {
      entry.paint_order = order->second;
    }
  }

  std::stable_sort(entries.begin(), entries.end(),
                   [](const LiveScrollableElementEntry& a,
                      const LiveScrollableElementEntry& b) {
                     return a.paint_order < b.paint_order;
                   });
}

namespace {

struct StandaloneStackingPaintEvent {
  int sequence = 0;
  std::string source;
  std::string layout_object;
  std::string tag;
  std::string class_name;
  int phase = -1;
  int children_to_visit = -1;
  int visit_index = -1;
  int z_index = 0;
  int raw_z_index = 0;
  bool has_auto_z_index = false;
  bool allows_z_index = false;
  bool is_stacked = false;
  bool is_stacking_context = false;
  bool has_layer = false;
  bool layer_self_painting = false;
  bool has_visible_content = false;
  bool has_visible_self_painting_descendant = false;
  bool has_self_painting_descendant = false;
  float fragment_width = -1.0f;
  float fragment_height = -1.0f;
};

std::vector<StandaloneStackingPaintEvent>&
StandaloneStackingPaintEventsForProbe() {
  static std::vector<StandaloneStackingPaintEvent>* events =
      new std::vector<StandaloneStackingPaintEvent>();
  return *events;
}

int& StandaloneStackingPaintEventSequenceForProbe() {
  static int* sequence = new int(0);
  return *sequence;
}

std::string ElementTagForStandalonePaintEvent(const LayoutObject& object) {
  Node* node = object.GetNode();
  if (auto* element = DynamicTo<Element>(node)) {
    return BlinkStringToStdStringForStandaloneRenderer(element->tagName());
  }
  return "";
}

std::string ElementClassForStandalonePaintEvent(const LayoutObject& object) {
  Node* node = object.GetNode();
  if (auto* element = DynamicTo<Element>(node)) {
    return BlinkStringToStdStringForStandaloneRenderer(
        element->getAttribute(html_names::kClassAttr));
  }
  return "";
}

StandaloneStackingPaintEvent MakeStandaloneStackingPaintEvent(
    const char* source,
    const LayoutObject& object,
    int phase,
    int children_to_visit,
    int visit_index) {
  StandaloneStackingPaintEvent event;
  event.sequence = StandaloneStackingPaintEventSequenceForProbe()++;
  event.source = source ? source : "";
  event.layout_object =
      BlinkStringToStdStringForStandaloneRenderer(object.DebugName());
  event.tag = ElementTagForStandalonePaintEvent(object);
  event.class_name = ElementClassForStandalonePaintEvent(object);
  event.phase = phase;
  event.children_to_visit = children_to_visit;
  event.visit_index = visit_index;
  event.z_index = object.StyleRef().EffectiveZIndex();
  event.raw_z_index = object.StyleRef().ZIndex();
  event.has_auto_z_index = object.StyleRef().HasAutoZIndex();
  event.allows_z_index = object.StyleRef().AllowsZIndex();
  event.is_stacked = object.IsStacked();
  event.is_stacking_context = object.IsStackingContext();
  if (auto* box_model_object = DynamicTo<LayoutBoxModelObject>(&object)) {
    event.has_layer = box_model_object->Layer();
    if (PaintLayer* layer = box_model_object->Layer()) {
      event.layer_self_painting = layer->IsSelfPaintingLayer();
      event.has_visible_content = layer->HasVisibleContent();
      event.has_visible_self_painting_descendant =
          layer->HasVisibleSelfPaintingDescendant();
      event.has_self_painting_descendant =
          layer->HasSelfPaintingLayerDescendant();
    }
  }
  return event;
}

}  // namespace

std::string PhysicalSizeJsonForStandaloneRenderer(const PhysicalSize& size) {
  std::ostringstream json;
  json << "{\"width\":" << size.width.ToFloat()
       << ",\"height\":" << size.height.ToFloat() << "}";
  return json.str();
}

std::string PhysicalBoxStrutJsonForStandaloneRenderer(
    const PhysicalBoxStrut& strut) {
  std::ostringstream json;
  json << "{\"top\":" << strut.top.ToFloat()
       << ",\"right\":" << strut.right.ToFloat()
       << ",\"bottom\":" << strut.bottom.ToFloat()
       << ",\"left\":" << strut.left.ToFloat() << "}";
  return json.str();
}

std::string LayoutParentChainJsonForStandaloneRenderer(
    const LayoutObject* layout_object) {
  std::ostringstream json;
  json << "[";
  int depth = 0;
  for (const LayoutObject* current = layout_object; current && depth < 12;
       current = current->Parent(), ++depth) {
    if (depth > 0) {
      json << ",";
    }
    json << JsonStringForStandaloneRenderer(
        BlinkStringToStdStringForStandaloneRenderer(current->DebugName()));
  }
  json << "]";
  return json.str();
}

std::string FragmentEvidenceJsonForStandaloneRenderer(const LayoutBox& box) {
  std::ostringstream json;
  json << "{\"physical_fragment_count\":" << box.PhysicalFragmentCount();
  const PhysicalBoxFragment* fragment = box.GetPhysicalFragment(0);
  if (!fragment) {
    json << ",\"first_fragment_present\":false}";
    return json.str();
  }
  json << ",\"first_fragment_present\":true"
       << ",\"first_fragment_size\":"
       << PhysicalSizeJsonForStandaloneRenderer(fragment->Size())
       << ",\"first_fragment_margins\":"
       << PhysicalBoxStrutJsonForStandaloneRenderer(fragment->Margins())
       << ",\"first_fragment_content_rect\":"
       << PhysicalRectJsonForStandaloneRenderer(fragment->ContentRect())
       << ",\"offset_from_root_fragmentation_context\":"
       << PhysicalOffsetJsonForStandaloneRenderer(
              fragment->OffsetFromRootFragmentationContext())
       << ",\"children\":[";
  int child_index = 0;
  for (const PhysicalFragmentLink& child_link : fragment->Children()) {
    if (child_index > 0) {
      json << ",";
    }
    const PhysicalFragment* child_fragment = child_link.get();
    json << "{\"index\":" << child_index
         << ",\"offset\":"
         << PhysicalOffsetJsonForStandaloneRenderer(child_link.Offset());
    if (child_fragment) {
      const LayoutObject* child_object = child_fragment->GetLayoutObject();
      json << ",\"layout_object\":"
           << JsonStringForStandaloneRenderer(
                  child_object ? BlinkStringToStdStringForStandaloneRenderer(
                                     child_object->DebugName())
                               : std::string())
           << ",\"size\":"
           << PhysicalSizeJsonForStandaloneRenderer(child_fragment->Size());
    } else {
      json << ",\"layout_object\":null,\"size\":null";
    }
    json << "}";
    ++child_index;
    if (child_index >= 16) {
      break;
    }
  }
  json << "]}";
  return json.str();
}

std::string LayoutChainEvidenceJsonForStandaloneRenderer(
    const LayoutObject* layout_object) {
  std::ostringstream json;
  json << "[";
  std::vector<const LayoutObject*> chain;
  for (const LayoutObject* current = layout_object; current;
       current = current->Parent()) {
    chain.push_back(current);
  }
  for (wtf_size_t i = chain.size(); i > 0; --i) {
    const LayoutObject* current = chain[i - 1];
    if (i != chain.size()) {
      json << ",";
    }
    json << "{\"name\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    current->DebugName()))
         << ",\"pointer\":\"0x" << std::hex
         << reinterpret_cast<uintptr_t>(current) << std::dec << "\"";
    if (const Node* node = current->GetNode()) {
      json << ",\"node_name\":"
           << JsonStringForStandaloneRenderer(
                  BlinkStringToStdStringForStandaloneRenderer(
                      node->nodeName()));
    } else {
      json << ",\"node_name\":null";
    }
    if (const auto* box = DynamicTo<LayoutBox>(current)) {
      const PhysicalRect local_rect(PhysicalOffset(), box->StitchedSize());
      const PhysicalOffset root_offset =
          current->OffsetFromAncestor(current->View());
      json << ",\"is_box\":true"
           << ",\"local_layout_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(local_rect)
           << ",\"root_offset\":"
           << PhysicalOffsetJsonForStandaloneRenderer(root_offset)
           << ",\"root_space_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(
                  PhysicalRect(root_offset, box->StitchedSize()))
           << ",\"fragment\":"
           << FragmentEvidenceJsonForStandaloneRenderer(*box);
    } else {
      json << ",\"is_box\":false";
    }
    if (LayoutBlock* containing_block = current->ContainingBlock()) {
      json << ",\"containing_block\":"
           << JsonStringForStandaloneRenderer(
                  BlinkStringToStdStringForStandaloneRenderer(
                      containing_block->DebugName()));
    } else {
      json << ",\"containing_block\":null";
    }
    json << "}";
  }
  json << "]";
  return json.str();
}

std::string DocumentEvidenceJsonForStandaloneRenderer(Document& document) {
  std::ostringstream json;
  json << "{\"compat_mode\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  document.compatMode()))
       << ",\"doctype_present\":"
       << (document.doctype() ? "true" : "false")
       << ",\"url\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  document.Url().GetString()))
       << ",\"base_url\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  document.BaseURL().GetString()));
  if (document.GetLayoutView()) {
    const gfx::Size layout_size = document.GetLayoutView()->GetLayoutSize();
    json << ",\"layout_view_present\":true"
         << ",\"layout_view_size\":{\"width\":" << layout_size.width()
         << ",\"height\":" << layout_size.height() << "}"
         << ",\"layout_view_origin_status\":\"not exported\""
         << ",\"initial_containing_block_status\":\"not exported\"";
  } else {
    json << ",\"layout_view_present\":false"
         << ",\"layout_view_size\":null"
         << ",\"layout_view_origin_status\":\"layout view unavailable\""
         << ",\"initial_containing_block_status\":\"layout view unavailable\"";
  }
  json << ",\"scroll_offset_status\":\"not exported\""
       << ",\"html_element_factory_create_html_count\":"
       << g_standalone_html_factory_create_html_count
       << ",\"html_element_factory_create_body_count\":"
       << g_standalone_html_factory_create_body_count
       << ",\"layout_child_placement_breadcrumbs\":{"
       << "\"html_to_body\":{\"count\":"
       << g_standalone_layout_html_body_placement_count
       << ",\"margin_inline_start\":"
       << g_standalone_layout_html_body_margin_inline_start
       << ",\"margin_block_start\":"
       << g_standalone_layout_html_body_margin_block_start
       << ",\"child_bfc_line\":"
       << g_standalone_layout_html_body_child_bfc_line
       << ",\"child_bfc_block\":"
       << g_standalone_layout_html_body_child_bfc_block
       << ",\"parent_bfc_line\":"
       << g_standalone_layout_html_body_parent_bfc_line
       << ",\"parent_bfc_block\":"
       << g_standalone_layout_html_body_parent_bfc_block
       << ",\"logical_inline_offset\":"
       << g_standalone_layout_html_body_logical_inline_offset
       << ",\"logical_block_offset\":"
       << g_standalone_layout_html_body_logical_block_offset << "}"
       << ",\"body_to_first_child\":{\"count\":"
       << g_standalone_layout_body_first_child_placement_count
       << ",\"margin_inline_start\":"
       << g_standalone_layout_body_child_margin_inline_start
       << ",\"margin_block_start\":"
       << g_standalone_layout_body_child_margin_block_start
       << ",\"child_bfc_line\":"
       << g_standalone_layout_body_child_bfc_line
       << ",\"child_bfc_block\":"
       << g_standalone_layout_body_child_bfc_block
       << ",\"parent_bfc_line\":"
       << g_standalone_layout_body_parent_bfc_line
       << ",\"parent_bfc_block\":"
       << g_standalone_layout_body_parent_bfc_block
       << ",\"logical_inline_offset\":"
       << g_standalone_layout_body_child_logical_inline_offset
       << ",\"logical_block_offset\":"
       << g_standalone_layout_body_child_logical_block_offset
       << ",\"previous_margin_strut_sum\":"
       << g_standalone_layout_body_previous_margin_strut_sum
       << ",\"previous_logical_block_offset\":"
       << g_standalone_layout_body_previous_logical_block_offset << "}}}";
  return json.str();
}

std::string ElementEvidenceJsonForStandaloneRenderer(Element* element) {
  if (!element) {
    return "{\"present\":false}";
  }
  std::ostringstream json;
  const bool is_html_element = IsA<HTMLElement>(element);
  const auto* html_element =
      is_html_element ? To<HTMLElement>(element) : nullptr;
  json << "{\"present\":true";
  json << ",\"tag_name\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(element->tagName()))
       << ",\"element_interface\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(element->nodeName()))
       << ",\"is_html_element\":"
       << (is_html_element ? "true" : "false")
       << ",\"html_element_is_body_virtual\":"
       << (html_element && html_element->IsHTMLBodyElement() ? "true"
                                                             : "false")
       << ",\"is_html_body_element\":"
       << (DynamicTo<HTMLBodyElement>(element) ? "true" : "false")
       << ",\"is_html_html_element\":"
       << (DynamicTo<HTMLHtmlElement>(element) ? "true" : "false")
       << ",\"is_html_image_element\":"
       << (DynamicTo<HTMLImageElement>(element) ? "true" : "false")
       << ",\"id\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  element->GetIdAttribute()))
       << ",\"class\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  element->getAttribute(html_names::kClassAttr)));
  if (const ComputedStyle* style = element->GetComputedStyle()) {
    json << ",\"computed_style\":{\"opacity\":" << style->Opacity()
         << ",\"display\":" << static_cast<int>(style->Display())
         << ",\"position\":" << static_cast<int>(style->GetPosition())
         << ",\"box_sizing\":" << static_cast<int>(style->BoxSizing())
         << ",\"font_size\":" << style->FontSize()
         << ",\"width\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->LogicalWidth().ToString()))
         << ",\"height\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->LogicalHeight().ToString()))
         << ",\"margin\":{\"top\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->MarginTop().ToString()))
         << ",\"right\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->MarginRight().ToString()))
         << ",\"bottom\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->MarginBottom().ToString()))
         << ",\"left\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->MarginLeft().ToString()))
         << "},\"padding\":{\"top\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->PaddingTop().ToString()))
         << ",\"right\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->PaddingRight().ToString()))
         << ",\"bottom\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->PaddingBottom().ToString()))
         << ",\"left\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->PaddingLeft().ToString()))
         << "},\"border_width\":{\"top\":" << style->BorderTopWidth()
         << ",\"right\":" << style->BorderRightWidth()
         << ",\"bottom\":" << style->BorderBottomWidth()
         << ",\"left\":" << style->BorderLeftWidth() << "}"
         << ",\"has_opacity\":" << (style->HasOpacity() ? "true" : "false")
         << ",\"has_transform\":" << (style->HasTransform() ? "true" : "false")
         << ",\"has_transform_operations\":"
         << (style->HasTransformOperations() ? "true" : "false")
         << ",\"has_non_translation_transform\":"
         << (style->HasTransform() && style->HasTransformOperations() &&
                     !style->Transform().IsIdentityOrTranslation()
                 ? "true"
                 : "false")
         << ",\"overflow_x\":" << static_cast<int>(style->OverflowX())
         << ",\"overflow_y\":" << static_cast<int>(style->OverflowY())
         << ",\"has_border_radius\":"
         << (style->HasBorderRadius() ? "true" : "false")
<< ",\"text_decoration_line\":"
         << static_cast<int>(style->GetTextDecorationLine())
         << ",\"text_decoration_style\":"
         << static_cast<int>(style->TextDecorationStyle())
         << ",\"has_applied_text_decorations\":"
         << (style->HasAppliedTextDecorations() ? "true" : "false")
         << ",\"text_decoration_color_status\":\"computed_style_accessible\""
         << ",\"text_decoration_thickness_status\":\"computed_style_accessible\""
         << ",\"has_background_image\":"
         << (style->BackgroundLayers().GetImage() ? "true" : "false")
         << "}";
  } else {
    json << ",\"computed_style\":{\"status\":\"unavailable\"}";
  }
  if (LayoutObject* layout_object = element->GetLayoutObject()) {
    json << ",\"layout\":{\"object_type\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    layout_object->DebugName()))
         << ",\"is_box\":"
         << (layout_object->IsBox() ? "true" : "false")
         << ",\"is_scroll_container\":"
         << (layout_object->IsScrollContainer() ? "true" : "false")
         << ",\"is_document_body\":"
         << (element == element->GetDocument().body() ? "true" : "false")
         << ",\"is_document_element\":"
         << (element == element->GetDocument().documentElement() ? "true"
                                                                 : "false")
         << ",\"parent_layout_chain\":"
         << LayoutParentChainJsonForStandaloneRenderer(layout_object)
         << ",\"layout_chain\":"
         << LayoutChainEvidenceJsonForStandaloneRenderer(layout_object);
    if (const auto* box = DynamicTo<LayoutBox>(layout_object)) {
      PhysicalRect local_layout_rect(PhysicalOffset(), box->StitchedSize());
      const PhysicalOffset local_to_root_offset =
          layout_object->OffsetFromAncestor(layout_object->View());
      PhysicalRect root_space_physical_rect(local_to_root_offset,
                                            box->StitchedSize());
      PhysicalRect local_to_absolute_rect =
          layout_object->LocalToAbsoluteRect(local_layout_rect);
      const gfx::Rect absolute_bounding_box_rect =
          layout_object->AbsoluteBoundingBoxRect();
      const gfx::RectF absolute_bounding_box_rect_f =
          layout_object->AbsoluteBoundingBoxRectF();
      PhysicalRect visual_overflow_mapped_to_view = box->VisualOverflowRect();
      const bool visual_overflow_mapped =
          layout_object->MapToVisualRectInAncestorSpace(
              layout_object->View(), visual_overflow_mapped_to_view);
      const gfx::RectF visual_overflow_mapped_to_view_f(
          visual_overflow_mapped_to_view.X().ToFloat(),
          visual_overflow_mapped_to_view.Y().ToFloat(),
          visual_overflow_mapped_to_view.Width().ToFloat(),
          visual_overflow_mapped_to_view.Height().ToFloat());
      const gfx::RectF dom_client_rect =
          element->GetBoundingClientRectNoLifecycleUpdate();
      gfx::Rect root_space_rect = gfx::ToEnclosingRect(gfx::RectF(
          root_space_physical_rect.X().ToFloat(),
          root_space_physical_rect.Y().ToFloat(),
          root_space_physical_rect.Width().ToFloat(),
          root_space_physical_rect.Height().ToFloat()));
      gfx::RectF root_space_rect_f(root_space_physical_rect.X().ToFloat(),
                                   root_space_physical_rect.Y().ToFloat(),
                                   root_space_physical_rect.Width().ToFloat(),
                                   root_space_physical_rect.Height().ToFloat());
      PhysicalRect paint_visual_rect = box->VisualOverflowRect();
      paint_visual_rect.Move(local_to_root_offset);
      json << ",\"rect_coordinate_spaces\":{"
           << "\"local_layout_rect\":\"local_layout_object_coordinates\","
           << "\"border_box_rect\":\"local_layout_object_coordinates\","
           << "\"visual_overflow_rect\":\"local_layout_object_coordinates\","
           << "\"scrollable_overflow_rect\":\"local_layout_object_coordinates\","
           << "\"root_space_rect\":\"absolute_root_frame_coordinates\","
           << "\"viewport_rect\":\"viewport_cssom_client_rect\","
           << "\"dom_client_rect_equivalent\":\"viewport_cssom_client_rect\","
           << "\"paint_visual_rect\":\"absolute_root_frame_coordinates\"}"
           << ",\"layout_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(local_layout_rect)
           << ",\"local_layout_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(local_layout_rect)
           << ",\"border_box_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(box->PhysicalBorderBoxRect())
           << ",\"visual_overflow_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(box->VisualOverflowRect())
           << ",\"scrollable_overflow_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(box->ScrollableOverflowRect())
           << ",\"root_space_rect\":"
           << GfxRectJsonForStandaloneRenderer(root_space_rect)
           << ",\"root_space_rect_f\":"
           << GfxRectFJsonForStandaloneRenderer(root_space_rect_f)
           << ",\"viewport_rect\":"
           << GfxRectFJsonForStandaloneRenderer(dom_client_rect)
           << ",\"dom_client_rect_equivalent\":"
           << GfxRectFJsonForStandaloneRenderer(dom_client_rect)
           << ",\"visual_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(paint_visual_rect)
           << ",\"paint_visual_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(paint_visual_rect)
           << ",\"coordinate_mapping\":{\"local_to_root_offset\":"
           << PhysicalOffsetJsonForStandaloneRenderer(local_to_root_offset)
           << ",\"scroll_offset_applied\":false"
           << ",\"page_scale_applied\":false"
           << ",\"transform_applied\":false"
           << ",\"source\":\"Element::GetBoundingClientRectNoLifecycleUpdate for viewport_rect; LayoutObject::OffsetFromAncestor(LayoutView) for root_space_rect\"}"
           << ",\"rect_candidates\":{"
           << "\"dom_client_rect_no_lifecycle\":"
           << GfxRectFJsonForStandaloneRenderer(dom_client_rect)
           << ",\"absolute_bounding_box_rect\":"
           << GfxRectJsonForStandaloneRenderer(absolute_bounding_box_rect)
           << ",\"absolute_bounding_box_rect_f\":"
           << GfxRectFJsonForStandaloneRenderer(absolute_bounding_box_rect_f)
           << ",\"offset_from_layout_view_rect\":"
           << GfxRectFJsonForStandaloneRenderer(root_space_rect_f)
           << ",\"local_to_absolute_rect\":"
           << PhysicalRectJsonForStandaloneRenderer(local_to_absolute_rect)
           << ",\"visual_overflow_mapped_to_layout_view\":"
           << GfxRectFJsonForStandaloneRenderer(
                  visual_overflow_mapped_to_view_f)
           << ",\"visual_overflow_mapped_to_layout_view_success\":"
           << (visual_overflow_mapped ? "true" : "false")
           << ",\"paint_visual_rect_root\":"
           << PhysicalRectJsonForStandaloneRenderer(paint_visual_rect)
           << ",\"fragment_accumulated_rect\":null"
           << ",\"paint_chunk_bounds_root\":null}"
           << ",\"viewport_scroll_offset_applied\":false";
    } else {
      json << ",\"layout_rect\":null,\"border_box_rect\":null"
              ",\"visual_overflow_rect\":null,"
              "\"scrollable_overflow_rect\":null";
    }
    const ObjectPaintProperties* properties =
        layout_object->FirstFragment().PaintProperties();
    if (properties) {
      const auto* transform = properties->Transform();
      const auto* rotate = properties->Rotate();
      const auto* effect = properties->Effect();
      const auto* overflow_clip = properties->OverflowClip();
      const auto* inner_radius_clip = properties->InnerBorderRadiusClip();
      json << ",\"object_paint_properties\":{\"present\":true"
           << ",\"transform_present\":"
           << (transform ? "true" : "false")
           << ",\"rotate_present\":" << (rotate ? "true" : "false")
           << ",\"effect_present\":" << (effect ? "true" : "false")
           << ",\"effect_opacity\":"
           << (effect ? std::to_string(effect->Opacity()) : "1")
           << ",\"effect_has_non_default_opacity\":"
           << (effect && effect->Opacity() != 1.0f ? "true" : "false")
           << ",\"overflow_clip_present\":"
           << (overflow_clip ? "true" : "false")
           << ",\"inner_border_radius_clip_present\":"
           << (inner_radius_clip ? "true" : "false")
           << ",\"scroll_translation_present\":"
           << (properties->ScrollTranslation() ? "true" : "false")
           << ",\"scroll_present\":"
           << (properties->Scroll() ? "true" : "false")
           << "}";
    } else {
      json << ",\"object_paint_properties\":{\"present\":false}";
    }
    json << "}";
  } else {
    json << ",\"layout\":{\"object_type\":null,"
            "\"object_paint_properties\":{\"present\":false}}";
  }
  json << "}";
  return json.str();
}

std::string PageEvidenceJsonForStandaloneRenderer(Document& document) {
  Element* body = document.body();
  Element* html = document.documentElement();
  Element* card = body ? FindElementByClassForStandaloneRenderer(
                             *body, AtomicString("card"))
                       : nullptr;
  Element* child = body ? FindElementByClassForStandaloneRenderer(
                              *body, AtomicString("child"))
                        : nullptr;
  Element* box = body ? FindElementByClassForStandaloneRenderer(
                            *body, AtomicString("box"))
                      : nullptr;
  Element* fixture_target = body ? FindElementByClassForStandaloneRenderer(
                                       *body, AtomicString("fixture-target"))
                                 : nullptr;
  Element* debug_id =
      body ? FindElementByAttributeForStandaloneRenderer(
                 *body, AtomicString("data-debug-id"))
           : nullptr;
  Element* img =
      body ? FindElementByTagForStandaloneRenderer(*body, html_names::kImgTag)
           : nullptr;
  Element* table =
      body ? FindElementByTagForStandaloneRenderer(*body, html_names::kTableTag)
           : nullptr;
  std::ostringstream json;
  json << "{\"document\":" << DocumentEvidenceJsonForStandaloneRenderer(document)
       << ",\"html\":" << ElementEvidenceJsonForStandaloneRenderer(html)
       << ",\"body\":" << ElementEvidenceJsonForStandaloneRenderer(body)
       << ",\"card\":" << ElementEvidenceJsonForStandaloneRenderer(card)
       << ",\"child\":" << ElementEvidenceJsonForStandaloneRenderer(child)
       << ",\"box\":" << ElementEvidenceJsonForStandaloneRenderer(box)
       << ",\"fixture-target\":"
       << ElementEvidenceJsonForStandaloneRenderer(fixture_target)
       << ",\"data-debug-id\":"
       << ElementEvidenceJsonForStandaloneRenderer(debug_id)
       << ",\"img\":" << ElementEvidenceJsonForStandaloneRenderer(img)
       << ",\"table\":" << ElementEvidenceJsonForStandaloneRenderer(table)
       << "}";
  return json.str();
}

std::string OpacityElementDiagnosticsJsonForStandaloneRenderer(
    const char* selector,
    Element* element) {
  std::ostringstream json;
  json << "{\"selector\":"
       << JsonStringForStandaloneRenderer(selector ? selector : "");
  if (!element) {
    json << ",\"present\":false,\"first_missing_stage\":\"element_not_found\"}";
    return json.str();
  }
  json << ",\"present\":true"
       << ",\"tag_name\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(element->tagName()))
       << ",\"id\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  element->GetIdAttribute()))
       << ",\"class\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  element->getAttribute(html_names::kClassAttr)))
       << ",\"data_debug_id\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  element->getAttribute(AtomicString("data-debug-id"))));

  const ComputedStyle* style = element->GetComputedStyle();
  if (style) {
    json << ",\"computed_style\":{\"opacity\":" << style->Opacity()
         << ",\"has_opacity\":" << (style->HasOpacity() ? "true" : "false")
         << ",\"display\":" << static_cast<int>(style->Display())
         << ",\"position\":" << static_cast<int>(style->GetPosition())
         << ",\"is_stacking_context_without_containment\":"
         << (style->IsStackingContextWithoutContainment() ? "true" : "false")
         << "}";
  } else {
    json << ",\"computed_style\":null";
  }

  LayoutObject* layout_object = element->GetLayoutObject();
  if (!layout_object) {
    json << ",\"layout_object_present\":false"
         << ",\"first_missing_stage\":\"layout_object_missing\"}";
    return json.str();
  }

  json << ",\"layout_object_present\":true"
       << ",\"layout_object_type\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  layout_object->DebugName()))
       << ",\"layout_flags\":{\"has_layer\":"
       << (layout_object->HasLayer() ? "true" : "false")
       << ",\"is_stacked\":" << (layout_object->IsStacked() ? "true" : "false")
       << ",\"is_stacking_context\":"
       << (layout_object->IsStackingContext() ? "true" : "false")
       << ",\"needs_paint_property_update\":"
       << (layout_object->NeedsPaintPropertyUpdate() ? "true" : "false")
       << "}";

  if (auto* box_model = DynamicTo<LayoutBoxModelObject>(layout_object)) {
    json << ",\"box_model\":{\"layer_type_required\":"
         << static_cast<int>(box_model->LayerTypeRequired())
         << ",\"has_self_painting_layer\":"
         << (box_model->HasSelfPaintingLayer() ? "true" : "false");
    PaintLayer* layer = box_model->Layer();
    json << ",\"paint_layer_present\":" << (layer ? "true" : "false");
    if (layer) {
      json << ",\"paint_layer\":{\"is_self_painting\":"
           << (layer->IsSelfPaintingLayer() ? "true" : "false")
           << ",\"has_visible_content\":"
           << (layer->HasVisibleContent() ? "true" : "false")
           << ",\"has_visible_self_painting_descendant\":"
           << (layer->HasVisibleSelfPaintingDescendant() ? "true" : "false")
           << ",\"has_self_painting_descendant\":"
           << (layer->HasSelfPaintingLayerDescendant() ? "true" : "false")
           << "}";
    }
    json << "}";
  }

  const ObjectPaintProperties* properties =
      layout_object->FirstFragment().PaintProperties();
  if (properties) {
    const auto* effect = properties->Effect();
    json << ",\"object_paint_properties\":{\"present\":true"
         << ",\"effect_present\":" << (effect ? "true" : "false")
         << ",\"effect_opacity\":"
         << (effect ? std::to_string(effect->Opacity()) : "1")
         << ",\"effect_has_non_default_opacity\":"
         << (effect && effect->Opacity() != 1.0f ? "true" : "false")
         << "}";
  } else {
    json << ",\"object_paint_properties\":{\"present\":false}";
  }

  std::string missing_stage = "ok";
  if (style && style->Opacity() != 1.0f) {
    if (!layout_object->HasLayer()) {
      missing_stage = "opacity_layout_object_has_no_paint_layer";
    } else if (!properties) {
      missing_stage = "opacity_object_paint_properties_missing";
    } else if (!properties->Effect()) {
      missing_stage = "opacity_effect_node_missing";
    } else if (properties->Effect()->Opacity() == 1.0f) {
      missing_stage = "opacity_effect_node_default_opacity";
    }
  }
  json << ",\"first_missing_stage\":"
       << JsonStringForStandaloneRenderer(missing_stage) << "}";
  return json.str();
}

std::string OpacityDiagnosticsJsonForStandaloneRenderer(Document& document) {
  Element* body = document.body();
  Element* debug_opacity =
      body ? FindElementByAttributeForStandaloneRenderer(
                 *body, AtomicString("data-debug-id"))
           : nullptr;
  Element* stage =
      body ? FindElementByClassForStandaloneRenderer(*body,
                                                     AtomicString("stage"))
           : nullptr;
  Element* clip_stage =
      body ? FindElementByClassForStandaloneRenderer(
                 *body, AtomicString("clip-stage"))
           : nullptr;
  Element* fade =
      body ? FindElementByClassForStandaloneRenderer(*body,
                                                     AtomicString("fade"))
           : nullptr;
  std::ostringstream json;
  json << "{\"runtime\":{\"stacking_context_is_not_stacked_enabled\":"
       << (RuntimeEnabledFeatures::StackingContextIsNotStackedEnabled()
               ? "true"
               : "false")
       << "},\"targets\":["
       << OpacityElementDiagnosticsJsonForStandaloneRenderer(
              "[data-debug-id]", debug_opacity)
       << ","
       << OpacityElementDiagnosticsJsonForStandaloneRenderer(".stage", stage)
       << ","
       << OpacityElementDiagnosticsJsonForStandaloneRenderer(".clip-stage",
                                                            clip_stage)
       << ","
       << OpacityElementDiagnosticsJsonForStandaloneRenderer(".fade", fade)
       << "]}";
  return json.str();
}

std::string OverflowClipElementDiagnosticsJsonForStandaloneRenderer(
    const char* selector,
    Element* element) {
  std::ostringstream json;
  json << "{\"selector\":\"" << selector << "\"";
  if (!element) {
    json << ",\"present\":false,\"first_missing_stage\":\"element_not_found\"}";
    return json.str();
  }
  json << ",\"present\":true";
  const ComputedStyle* style = element->GetComputedStyle();
  if (style) {
    json << ",\"computed_overflow\":{\"x\":" << static_cast<int>(style->OverflowX())
         << ",\"y\":" << static_cast<int>(style->OverflowY()) << "}"
         << ",\"computed_border_radius_present\":"
         << (style->HasBorderRadius() ? "true" : "false")
         << ",\"border_width\":{\"top\":" << style->BorderTopWidth()
         << ",\"right\":" << style->BorderRightWidth()
         << ",\"bottom\":" << style->BorderBottomWidth()
         << ",\"left\":" << style->BorderLeftWidth() << "}"
         << ",\"display\":" << static_cast<int>(style->Display())
         << ",\"position\":" << static_cast<int>(style->GetPosition())
         << ",\"scrolls_overflow_x\":"
         << (style->ScrollsOverflowX() ? "true" : "false")
         << ",\"scrolls_overflow_y\":"
         << (style->ScrollsOverflowY() ? "true" : "false");
  } else {
    json << ",\"computed_overflow\":null";
  }

  LayoutObject* layout_object = element->GetLayoutObject();
  if (!layout_object) {
    json << ",\"layout_object_type\":null"
         << ",\"first_missing_stage\":\"layout_object_missing\"}";
    return json.str();
  }
  json << ",\"layout_object_type\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  layout_object->DebugName()));
  json << ",\"layout_flags\":{\"has_non_visible_overflow\":"
       << (layout_object->HasNonVisibleOverflow() ? "true" : "false")
       << ",\"is_scroll_container\":"
       << (layout_object->IsScrollContainer() ? "true" : "false")
       << ",\"should_clip_overflow_either_axis\":"
       << (layout_object->ShouldClipOverflowAlongEitherAxis() ? "true"
                                                              : "false")
       << ",\"should_clip_overflow_both_axis\":"
       << (layout_object->ShouldClipOverflowAlongBothAxis() ? "true"
                                                            : "false")
       << ",\"needs_paint_property_update\":"
       << (layout_object->NeedsPaintPropertyUpdate() ? "true" : "false")
       << "}";
  const auto* box = DynamicTo<LayoutBox>(layout_object);
  if (!box) {
    json << ",\"layout_rect\":null"
         << ",\"first_missing_stage\":\"layout_box_missing\"}";
    return json.str();
  }

  json << ",\"layout_rect\":"
       << PhysicalRectJsonForStandaloneRenderer(box->PhysicalBorderBoxRect())
       << ",\"border_box\":"
       << PhysicalRectJsonForStandaloneRenderer(box->PhysicalBorderBoxRect())
       << ",\"padding_box\":"
       << PhysicalRectJsonForStandaloneRenderer(box->PhysicalPaddingBoxRect())
       << ",\"content_box\":"
       << PhysicalRectJsonForStandaloneRenderer(box->PhysicalContentBoxRect())
       << ",\"scrollable_overflow_rect\":"
       << PhysicalRectJsonForStandaloneRenderer(box->ScrollableOverflowRect())
       << ",\"visual_overflow_rect\":"
       << PhysicalRectJsonForStandaloneRenderer(box->VisualOverflowRect())
       << ",\"self_visual_overflow_rect\":"
       << PhysicalRectJsonForStandaloneRenderer(box->SelfVisualOverflowRect());

  PaintLayer* layer = layout_object->EnclosingLayer();
  PaintLayerScrollableArea* scrollable_area =
      box->GetScrollableArea()
          ? box->GetScrollableArea()
          : (layer ? layer->GetScrollableArea() : nullptr);
  json << ",\"paint_layer_present\":" << (layer ? "true" : "false")
       << ",\"paint_layer_self_painting\":"
       << (layer && layer->IsSelfPaintingLayer() ? "true" : "false")
       << ",\"scrollable_area_present\":"
       << (scrollable_area ? "true" : "false");
  if (scrollable_area) {
    json << ",\"scroll_container_rect\":null"
         << ",\"scroll_contents_size\":null"
         << ",\"scroll_width\":null,\"scroll_height\":null"
         << ",\"scroll_offset\":null,\"scrollable_axes\":null"
         << ",\"scrollable_area_metadata_status\":\"inaccessible\""
         << ",\"scrollable_area_metadata_reason\":\"standalone optional "
            "PaintLayerScrollableArea geometry methods are unsafe on "
            "scroll/auto overflow reducers; using raw property-tree scroll "
            "nodes and LayoutBox overflow rects instead\"";
  } else {
    json << ",\"scroll_container_rect\":null"
         << ",\"scroll_contents_size\":null"
         << ",\"scroll_width\":null,\"scroll_height\":null"
         << ",\"scroll_offset\":null,\"scrollable_axes\":0";
  }

  const ObjectPaintProperties* properties =
      layout_object->FirstFragment().PaintProperties();
  if (properties) {
    const auto* overflow_clip = properties->OverflowClip();
    const auto* inner_radius_clip = properties->InnerBorderRadiusClip();
    json << ",\"object_paint_properties\":{\"present\":true"
         << ",\"overflow_clip_present\":"
         << (overflow_clip ? "true" : "false")
         << ",\"inner_border_radius_clip_present\":"
         << (inner_radius_clip ? "true" : "false")
         << ",\"scroll_translation_present\":"
         << (properties->ScrollTranslation() ? "true" : "false")
         << ",\"scroll_node_present\":"
         << (properties->Scroll() ? "true" : "false")
         << ",\"clip_node_id\":" << NodeIdForStandaloneRenderer(overflow_clip)
         << ",\"inner_border_radius_clip_node_id\":"
         << NodeIdForStandaloneRenderer(inner_radius_clip) << "}";
  } else {
    json << ",\"object_paint_properties\":{\"present\":false}";
  }

  std::string missing_stage = "ok";
  if (style && (style->OverflowX() != EOverflow::kVisible ||
                style->OverflowY() != EOverflow::kVisible)) {
    if (!scrollable_area) {
      missing_stage = "paint_layer_scrollable_area_missing";
    } else if (!properties) {
      missing_stage = "object_paint_properties_missing";
    } else if (!properties->OverflowClip()) {
      missing_stage = "overflow_clip_property_missing";
    }
  }
  json << ",\"first_missing_stage\":"
       << JsonStringForStandaloneRenderer(missing_stage) << "}";
  return json.str();
}

std::string OverflowClipDiagnosticsJsonForStandaloneRenderer(Document& document) {
  Element* body = document.body();
  Element* container =
      body ? FindElementByAttributeValueForStandaloneRenderer(
                 *body, AtomicString("data-debug-id"),
                 AtomicString("container"))
           : nullptr;
  Element* child =
      body ? FindElementByAttributeValueForStandaloneRenderer(
                 *body, AtomicString("data-debug-id"), AtomicString("child"))
           : nullptr;
  if (!container) {
    container = body ? FindElementByClassForStandaloneRenderer(
                           *body, AtomicString("fixture-target"))
                     : nullptr;
  }
  if (!container) {
    container = body ? FindElementByClassForStandaloneRenderer(
                           *body, AtomicString("card"))
                     : nullptr;
  }
  if (!container) {
    container = body ? FindElementByClassForStandaloneRenderer(
                           *body, AtomicString("box"))
                     : nullptr;
  }
  if (!container) {
    container = body ? FindElementByClassForStandaloneRenderer(
                           *body, AtomicString("clip"))
                     : nullptr;
  }
  if (!child) {
    child = body ? FindElementByClassForStandaloneRenderer(
                       *body, AtomicString("child"))
                 : nullptr;
  }
  std::ostringstream json;
  json << "{\"containers\":["
       << OverflowClipElementDiagnosticsJsonForStandaloneRenderer(
              "[data-debug-id=container] or .fixture-target", container)
       << "],\"children\":["
       << OverflowClipElementDiagnosticsJsonForStandaloneRenderer(
              "[data-debug-id=child] or .child", child)
       << "]}";
  return json.str();
}

std::string LengthDiagnosticsJsonForStandaloneRenderer(const Length& length);

std::string OutOfFlowElementEvidenceJsonForStandaloneRenderer(
    Document& document) {
  Element* body = document.body();
  Element* target =
      body ? FindElementByClassForStandaloneRenderer(
                 *body, AtomicString("fixture-target"))
           : nullptr;
  if (!target && body) {
    target = FindElementByAttributeForStandaloneRenderer(
        *body, AtomicString("data-debug-id"));
  }
  std::ostringstream json;
  json << "{\"target_present\":" << (target ? "true" : "false");
  if (!target) {
    json << ",\"first_missing_stage\":\"element_not_found\"}";
    return json.str();
  }
  json << ",\"tag_name\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(target->tagName()))
       << ",\"class\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  target->getAttribute(html_names::kClassAttr)));
  const ComputedStyle* style = target->GetComputedStyle();
  if (style) {
    json << ",\"computed_style\":{\"position\":"
         << static_cast<int>(style->GetPosition())
         << ",\"display\":" << static_cast<int>(style->Display())
         << ",\"visibility\":"
         << static_cast<int>(style->Visibility())
         << ",\"width\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->LogicalWidth().ToString()))
         << ",\"width_length\":"
         << LengthDiagnosticsJsonForStandaloneRenderer(style->LogicalWidth())
         << ",\"min_width_length\":"
         << LengthDiagnosticsJsonForStandaloneRenderer(style->LogicalMinWidth())
         << ",\"max_width_length\":"
         << LengthDiagnosticsJsonForStandaloneRenderer(style->LogicalMaxWidth())
         << ",\"height\":"
         << JsonStringForStandaloneRenderer(
                BlinkStringToStdStringForStandaloneRenderer(
                    style->LogicalHeight().ToString()))
         << "}";
  } else {
    json << ",\"computed_style\":{\"status\":\"unavailable\"}";
  }
  LayoutObject* layout_object = target->GetLayoutObject();
  json << ",\"layout_object_present\":"
       << (layout_object ? "true" : "false");
  if (!layout_object) {
    json << ",\"oof_layout_part_run_called\":"
         << (g_standalone_oof_layout_part_run_called > 0 ? "true" : "false")
         << ",\"oof_descendant_collected\":"
         << (g_standalone_oof_descendant_collected > 0 ? "true" : "false")
         << ",\"oof_candidate_count\":" << g_standalone_oof_candidate_count
         << ",\"oof_layout_attempted\":"
         << (g_standalone_oof_layout_attempted > 0 ? "true" : "false")
         << ",\"oof_fragment_created\":"
         << (g_standalone_oof_fragment_created > 0 ? "true" : "false")
         << ",\"candidate_repropagated\":"
         << g_standalone_oof_candidate_repropagated
         << ",\"candidate_dropped_at_root\":"
         << g_standalone_oof_candidate_dropped_at_root
         << ",\"unsupported_inline_containing_block\":"
         << g_standalone_oof_unsupported_inline_containing_block
         << ",\"layout_null_results\":"
         << g_standalone_oof_layout_null_results
         << ",\"zero_size_fragments\":"
         << g_standalone_oof_zero_size_fragments
         << ",\"safety_limit_hit\":"
         << (g_standalone_oof_safety_limit_hit ? "true" : "false")
         << ",\"unsupported_inset_forms\":[]"
         << ",\"candidate_repropagation_warnings\":"
         << (g_standalone_oof_unsupported_inline_containing_block > 0
                 ? "[\"standalone OOF subset does not support inline containing block absolute positioning yet\"]"
                 : "[]")
         << ",\"first_missing_stage\":\"layout_object_missing\"}";
    return json.str();
  }
  LayoutBlock* containing_block = layout_object->ContainingBlock();
  json << ",\"layout_object_type\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(
                  layout_object->DebugName()))
       << ",\"is_box\":" << (layout_object->IsBox() ? "true" : "false")
       << ",\"has_layer\":" << (layout_object->HasLayer() ? "true" : "false")
       << ",\"has_self_painting_layer\":";
  if (auto* box_model_object = DynamicTo<LayoutBoxModelObject>(layout_object)) {
    json << (box_model_object->HasSelfPaintingLayer() ? "true" : "false");
    if (PaintLayer* layer = box_model_object->Layer()) {
      json << ",\"paint_layer\":{\"is_self_painting\":"
           << (layer->IsSelfPaintingLayer() ? "true" : "false")
           << ",\"layout_object_is_stacked\":"
           << (layer->GetLayoutObject().IsStacked() ? "true" : "false")
           << ",\"layout_object_is_stacking_context\":"
           << (layer->GetLayoutObject().IsStackingContext() ? "true"
                                                            : "false")
           << ",\"has_visible_content\":"
           << (layer->HasVisibleContent() ? "true" : "false")
           << ",\"has_visible_self_painting_descendant\":"
           << (layer->HasVisibleSelfPaintingDescendant() ? "true" : "false")
           << ",\"has_self_painting_descendant\":"
           << (layer->HasSelfPaintingLayerDescendant() ? "true" : "false");
      if (PaintLayer* parent_layer = layer->Parent()) {
        int paint_order_index = 0;
        int paint_order_visit_count = 0;
        bool parent_iterator_visits_target = false;
        PaintLayerPaintOrderIterator iterator(parent_layer, kAllChildren);
        while (PaintLayer* ordered_child = iterator.Next()) {
          ++paint_order_visit_count;
          if (ordered_child == layer) {
            parent_iterator_visits_target = true;
            paint_order_index = paint_order_visit_count - 1;
          }
        }
        json << ",\"parent\":{\"layout_object\":"
             << JsonStringForStandaloneRenderer(
                    BlinkStringToStdStringForStandaloneRenderer(
                        parent_layer->GetLayoutObject().DebugName()))
             << ",\"is_self_painting\":"
             << (parent_layer->IsSelfPaintingLayer() ? "true" : "false")
             << ",\"layout_object_is_stacking_context\":"
             << (parent_layer->GetLayoutObject().IsStackingContext() ? "true"
                                                                      : "false")
             << ",\"has_visible_content\":"
             << (parent_layer->HasVisibleContent() ? "true" : "false")
             << ",\"has_visible_self_painting_descendant\":"
             << (parent_layer->HasVisibleSelfPaintingDescendant() ? "true"
                                                                  : "false")
             << ",\"has_self_painting_descendant\":"
             << (parent_layer->HasSelfPaintingLayerDescendant() ? "true"
                                                                : "false")
             << ",\"paint_order_visit_count\":" << paint_order_visit_count
             << ",\"paint_order_visits_target\":"
             << (parent_iterator_visits_target ? "true" : "false")
             << ",\"paint_order_index\":"
             << (parent_iterator_visits_target ? paint_order_index : -1)
             << "}";
      } else {
        json << ",\"parent\":null";
      }
      if (PaintLayer* previous_sibling = layer->PreviousSibling()) {
        json << ",\"previous_sibling\":"
             << JsonStringForStandaloneRenderer(
                    BlinkStringToStdStringForStandaloneRenderer(
                        previous_sibling->GetLayoutObject().DebugName()));
      } else {
        json << ",\"previous_sibling\":null";
      }
      if (PaintLayer* next_sibling = layer->NextSibling()) {
        json << ",\"next_sibling\":"
             << JsonStringForStandaloneRenderer(
                    BlinkStringToStdStringForStandaloneRenderer(
                        next_sibling->GetLayoutObject().DebugName()));
      } else {
        json << ",\"next_sibling\":null";
      }
      json << "}";
    } else {
      json << ",\"paint_layer\":null";
    }
  } else {
    json << "false";
    json << ",\"paint_layer\":null";
  }
  json
       << ",\"containing_block\":";
  if (containing_block) {
    json << JsonStringForStandaloneRenderer(
        BlinkStringToStdStringForStandaloneRenderer(
            containing_block->DebugName()));
  } else {
    json << "null";
  }
  json << ",\"containing_block_fragments\":";
  if (containing_block && containing_block->PhysicalFragmentCount() > 0) {
    json << "[";
    for (wtf_size_t i = 0; i < containing_block->PhysicalFragmentCount(); ++i) {
      if (i) {
        json << ",";
      }
      const PhysicalBoxFragment* fragment = containing_block->GetPhysicalFragment(i);
      json << "{\"index\":" << i
           << ",\"has_oof_fragment_child\":"
           << (fragment && fragment->HasOutOfFlowFragmentChild() ? "true"
                                                                 : "false")
           << ",\"child_count\":"
           << (fragment ? static_cast<int>(fragment->Children().size()) : 0)
           << ",\"size\":"
           << (fragment ? PhysicalSizeJsonForStandaloneRenderer(fragment->Size())
                        : "null")
           << "}";
    }
    json << "]";
  } else {
    json << "[]";
  }
  LayoutObject* parent_object = layout_object->Parent();
  json << ",\"layout_parent\":";
  if (parent_object) {
    json << JsonStringForStandaloneRenderer(
        BlinkStringToStdStringForStandaloneRenderer(parent_object->DebugName()));
  } else {
    json << "null";
  }
  json << ",\"layout_parent_fragments\":";
  auto* parent_box = DynamicTo<LayoutBox>(parent_object);
  if (parent_box && parent_box->PhysicalFragmentCount() > 0) {
    json << "[";
    for (wtf_size_t i = 0; i < parent_box->PhysicalFragmentCount(); ++i) {
      if (i) {
        json << ",";
      }
      const PhysicalBoxFragment* fragment = parent_box->GetPhysicalFragment(i);
      json << "{\"index\":" << i
           << ",\"has_oof_fragment_child\":"
           << (fragment && fragment->HasOutOfFlowFragmentChild() ? "true"
                                                                 : "false")
           << ",\"child_count\":"
           << (fragment ? static_cast<int>(fragment->Children().size()) : 0)
           << ",\"size\":"
           << (fragment ? PhysicalSizeJsonForStandaloneRenderer(fragment->Size())
                        : "null")
           << "}";
    }
    json << "]";
  } else {
    json << "[]";
  }
  if (const auto* box = DynamicTo<LayoutBox>(layout_object)) {
    const PhysicalOffset local_to_root_offset =
        layout_object->OffsetFromAncestor(layout_object->View());
    const gfx::Rect absolute_bounding_box_rect =
        layout_object->AbsoluteBoundingBoxRect();
    json << ",\"box_geometry\":{\"stitched_size\":"
         << PhysicalSizeJsonForStandaloneRenderer(box->StitchedSize())
         << ",\"border_box_rect\":"
         << PhysicalRectJsonForStandaloneRenderer(box->PhysicalBorderBoxRect())
         << ",\"local_to_root_offset\":"
         << PhysicalOffsetJsonForStandaloneRenderer(local_to_root_offset)
         << ",\"absolute_bounding_box_rect\":"
         << GfxRectJsonForStandaloneRenderer(absolute_bounding_box_rect)
         << "}";
  } else {
    json << ",\"box_geometry\":{\"status\":\"not_a_layout_box\"}";
  }
  json << ",\"paint_artifact_display_items_seen_by_audit\":\"see "
          "raw_display_item_count and chunks[].display_items\","
       << "\"oof_layout_part_run_called\":"
       << (g_standalone_oof_layout_part_run_called > 0 ? "true" : "false")
       << ",\"oof_descendant_collected\":"
       << (g_standalone_oof_descendant_collected > 0 ? "true" : "false")
       << ",\"oof_candidate_count\":" << g_standalone_oof_candidate_count
       << ",\"oof_layout_attempted\":"
       << (g_standalone_oof_layout_attempted > 0 ? "true" : "false")
       << ",\"oof_fragment_created\":"
       << (g_standalone_oof_fragment_created > 0 ? "true" : "false")
       << ",\"candidate_repropagated\":"
       << g_standalone_oof_candidate_repropagated
       << ",\"candidate_dropped_at_root\":"
       << g_standalone_oof_candidate_dropped_at_root
       << ",\"unsupported_inline_containing_block\":"
       << g_standalone_oof_unsupported_inline_containing_block
       << ",\"layout_null_results\":"
       << g_standalone_oof_layout_null_results
       << ",\"zero_size_fragments\":"
       << g_standalone_oof_zero_size_fragments
       << ",\"safety_limit_hit\":"
       << (g_standalone_oof_safety_limit_hit ? "true" : "false")
       << ",\"unsupported_inset_forms\":[]"
       << ",\"candidate_repropagation_warnings\":"
       << (g_standalone_oof_candidate_dropped_at_root > 0
               ? "[\"dropped out-of-flow candidate at LayoutView because its containing block is not represented by the current standalone subset; likely inline containing block support\"]"
               : "[]")
       << ",\"first_missing_stage\":\"see_paint_artifact_display_items\"}";
  return json.str();
}

std::string LengthDiagnosticsJsonForStandaloneRenderer(const Length& length) {
  std::ostringstream json;
  json << "{\"text\":"
       << JsonStringForStandaloneRenderer(
              BlinkStringToStdStringForStandaloneRenderer(length.ToString()))
       << ",\"type\":" << static_cast<int>(length.GetType())
       << ",\"is_auto\":" << (length.IsAuto() ? "true" : "false")
       << ",\"is_fixed\":" << (length.IsFixed() ? "true" : "false")
       << ",\"is_fit_content\":"
       << (length.IsFitContent() ? "true" : "false")
       << ",\"has_fit_content\":"
       << (length.HasFitContent() ? "true" : "false")
       << ",\"has_min_content\":"
       << (length.HasMinContent() ? "true" : "false")
       << ",\"has_max_content\":"
       << (length.HasMaxContent() ? "true" : "false")
       << ",\"has_content_or_intrinsic\":"
       << (length.HasContentOrIntrinsic() ? "true" : "false") << "}";
  return json.str();
}

bool HasUnsupportedInlineContainingBlockOofForStandaloneRenderer(
    Document& document) {
  Element* body = document.body();
  Element* target =
      body ? FindElementByClassForStandaloneRenderer(
                 *body, AtomicString("fixture-target"))
           : nullptr;
  if (!target || !target->GetComputedStyle() ||
      target->GetComputedStyle()->GetPosition() != EPosition::kAbsolute) {
    return false;
  }
  for (Element* parent = target->parentElement(); parent;
       parent = parent->parentElement()) {
    const ComputedStyle* style = parent->GetComputedStyle();
    if (!style) {
      continue;
    }
    if (style->Display() == EDisplay::kInlineBlock) {
      return true;
    }
  }
  return false;
}

bool SourceMentionsInlineContainingBlockOofForStandaloneRenderer(
    const std::string& input_html) {
  std::string lowered = input_html;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                 [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
  return lowered.find("position: absolute") != std::string::npos &&
         lowered.find("display: inline-block") != std::string::npos;
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

std::string MediaQueryDiagnosticsJsonForStandaloneRenderer(
    LiveFramePaintProbeCache& cache) {
  auto field_at = [](int index, int field) {
    std::array<char, 512> buffer{};
    const int copied = StandaloneRendererMediaQueryDiagnosticFieldAt(
        index, field, buffer.data(), static_cast<int>(buffer.size()));
    if (copied <= 0) {
      return std::string();
    }
    return std::string(buffer.data(), static_cast<size_t>(copied));
  };
  auto source_expected_value = [&](const std::string& feature) {
    if (feature.empty()) {
      return std::string();
    }
    std::string lower = cache.body_html;
    std::transform(lower.begin(), lower.end(), lower.begin(),
                   [](unsigned char c) {
                     return static_cast<char>(std::tolower(c));
                   });
    const std::string needle = feature + ":";
    size_t feature_pos = lower.find(needle);
    if (feature_pos == std::string::npos) {
      return std::string();
    }
    size_t value_start = feature_pos + needle.size();
    while (value_start < lower.size() &&
           std::isspace(static_cast<unsigned char>(lower[value_start]))) {
      ++value_start;
    }
    size_t value_end = value_start;
    while (value_end < lower.size() && lower[value_end] != ')' &&
           lower[value_end] != '{' && lower[value_end] != ',' &&
           !std::isspace(static_cast<unsigned char>(lower[value_end]))) {
      ++value_end;
    }
    if (value_end <= value_start) {
      return std::string();
    }
    while (value_end > value_start &&
           (std::isspace(static_cast<unsigned char>(cache.body_html[value_end - 1])) ||
            cache.body_html[value_end - 1] == ';')) {
      --value_end;
    }
    return cache.body_html.substr(value_start, value_end - value_start);
  };
  std::ostringstream queries;
  queries << "[";
  const int trace_count = StandaloneRendererMediaQueryDiagnosticCount();
  for (int i = 0; i < trace_count; ++i) {
    if (i) {
      queries << ",";
    }
    const std::string feature = field_at(i, 0);
    std::string expected_value = field_at(i, 1);
    if (expected_value.empty()) {
      expected_value = source_expected_value(feature);
    }
    const std::string actual_value = field_at(i, 2);
    const std::string result = field_at(i, 3);
    const std::string unsupported = field_at(i, 4);
    queries << "{\"text\":\"(" << JsonEscapeForStandaloneRenderer(feature);
    if (!expected_value.empty()) {
      queries << ": " << JsonEscapeForStandaloneRenderer(expected_value);
    }
    queries << ")\",\"parsed\":true"
            << ",\"evaluation_result\":"
            << (result == "true"    ? "true"
                : result == "false" ? "false"
                                     : "null")
            << ",\"features\":[{\"name\":"
            << JsonStringForStandaloneRenderer(feature)
            << ",\"expected_value\":"
            << JsonStringForStandaloneRenderer(expected_value)
            << ",\"actual_value\":"
            << JsonStringForStandaloneRenderer(actual_value)
            << ",\"match\":"
            << (result == "true"    ? "true"
                : result == "false" ? "false"
                                     : "null")
            << "}],\"unsupported_features\":";
    if (unsupported.empty()) {
      queries << "[]";
    } else {
      queries << "[{\"name\":" << JsonStringForStandaloneRenderer(feature)
              << ",\"reason\":" << JsonStringForStandaloneRenderer(unsupported)
              << "}]";
    }
    queries << ",\"error\":\"\"}";
  }
  queries << "]";
  const std::string orientation =
      cache.viewport_width >= cache.viewport_height ? "landscape" : "portrait";
  std::ostringstream json;
  json << "{\"viewport\":{\"width\":" << cache.viewport_width
       << ",\"height\":" << cache.viewport_height << "}"
       << ",\"device_scale_factor\":1"
       << ",\"media_values\":{\"viewport_width\":" << cache.viewport_width
       << ",\"viewport_height\":" << cache.viewport_height
       << ",\"device_width\":" << cache.viewport_width
       << ",\"device_height\":" << cache.viewport_height
       << ",\"orientation\":" << JsonStringForStandaloneRenderer(orientation)
       << ",\"hover\":\"none\""
       << ",\"pointer\":\"none\""
       << ",\"any_hover\":\"none\""
       << ",\"any_pointer\":\"none\""
       << ",\"prefers_color_scheme\":\"light\""
       << ",\"prefers_reduced_motion\":\"no-preference\"}"
       << ",\"queries\":" << queries.str() << "}";
  return json.str();
}

struct ListMarkerDiagnosticsForStandaloneRenderer {
  int layout_list_item_count = 0;
  int marker_layout_object_count = 0;
  int marker_pseudo_element_count = 0;
  int dom_li_count = 0;
  int computed_list_item_count = 0;
  int dom_li_with_layout_object_count = 0;
  int dynamic_layout_list_item_count = 0;
  std::vector<std::string> li_layout_object_debug_names;
};

void CollectListMarkerDiagnosticsForStandaloneRenderer(
    const LayoutObject* object,
    ListMarkerDiagnosticsForStandaloneRenderer& diagnostics) {
  if (!object) {
    return;
  }
  const std::string debug_name = BlinkStringToStdStringForStandaloneRenderer(
      object->DebugName());
  if (debug_name.find("LayoutListItem") != std::string::npos ||
      debug_name.find("LayoutInlineListItem") != std::string::npos) {
    ++diagnostics.layout_list_item_count;
  }
  if (debug_name.find("ListMarker") != std::string::npos) {
    ++diagnostics.marker_layout_object_count;
  }
  for (const LayoutObject* child = object->SlowFirstChild(); child;
       child = child->NextSibling()) {
    CollectListMarkerDiagnosticsForStandaloneRenderer(child, diagnostics);
  }
}

void CollectListMarkerDomDiagnosticsForStandaloneRenderer(
    Node* node,
    ListMarkerDiagnosticsForStandaloneRenderer& diagnostics) {
  if (!node) {
    return;
  }
  if (auto* element = DynamicTo<Element>(node)) {
    if (element->HasTagName(html_names::kLiTag)) {
      ++diagnostics.dom_li_count;
      if (const ComputedStyle* style = element->GetComputedStyle()) {
        if (style->IsDisplayListItem()) {
          ++diagnostics.computed_list_item_count;
        }
      }
      if (LayoutObject* layout_object = element->GetLayoutObject()) {
        ++diagnostics.dom_li_with_layout_object_count;
        diagnostics.li_layout_object_debug_names.push_back(
            BlinkStringToStdStringForStandaloneRenderer(
                layout_object->DebugName()));
        if (DynamicTo<LayoutListItem>(layout_object)) {
          ++diagnostics.dynamic_layout_list_item_count;
        }
      }
    }
  }
  for (Node* child = node->firstChild(); child; child = child->nextSibling()) {
    CollectListMarkerDomDiagnosticsForStandaloneRenderer(child, diagnostics);
  }
}

std::string ListMarkerDiagnosticsJsonForStandaloneRenderer(Document& document,
                                                           const std::string& html) {
  ListMarkerDiagnosticsForStandaloneRenderer diagnostics;
  if (LayoutView* view = document.GetLayoutView()) {
    CollectListMarkerDiagnosticsForStandaloneRenderer(view, diagnostics);
  }
  CollectListMarkerDomDiagnosticsForStandaloneRenderer(&document, diagnostics);
  Element* body = document.body();
  if (body) {
    if (Element* marker = body->GetPseudoElement(kPseudoIdMarker)) {
      if (marker->GetLayoutObject()) {
        ++diagnostics.marker_pseudo_element_count;
      }
    }
  }
  std::string lower_html = html;
  std::transform(lower_html.begin(), lower_html.end(), lower_html.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  int li_source_count = 0;
  size_t pos = 0;
  while ((pos = lower_html.find("<li", pos)) != std::string::npos) {
    ++li_source_count;
    pos += 3;
  }
  std::ostringstream json;
  json << "{\"source_li_count\":" << li_source_count
       << ",\"dom_li_count\":" << diagnostics.dom_li_count
       << ",\"computed_list_item_count\":"
       << diagnostics.computed_list_item_count
       << ",\"dom_li_with_layout_object_count\":"
       << diagnostics.dom_li_with_layout_object_count
       << ",\"dynamic_layout_list_item_count\":"
       << diagnostics.dynamic_layout_list_item_count
       << ",\"layout_list_item_count\":"
       << diagnostics.layout_list_item_count
       << ",\"marker_layout_object_count\":"
       << diagnostics.marker_layout_object_count
       << ",\"marker_pseudo_element_count\":"
       << diagnostics.marker_pseudo_element_count
       << ",\"layout_object_factory\":{\"calls\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(0)
       << ",\"li_calls\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(1)
       << ",\"display_list_item_calls\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(2)
       << ",\"li_display_list_item_calls\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(3)
       << ",\"returned_layout_list_item\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(4)
       << ",\"returned_block_flow_for_li\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(5)
       << ",\"backdrop_skips\":"
       << StandaloneRendererListItemFactoryDiagnosticValue(6) << "}"
       << ",\"li_layout_object_debug_names\":[";
  for (size_t i = 0; i < diagnostics.li_layout_object_debug_names.size(); ++i) {
    if (i) {
      json << ",";
    }
    json << JsonStringForStandaloneRenderer(
        diagnostics.li_layout_object_debug_names[i]);
  }
  json << "]"
       << ",\"first_missing_stage\":";
  if (li_source_count == 0) {
    json << "\"no_list_items_in_source\"";
  } else if (diagnostics.dom_li_count == 0) {
    json << "\"list_item_dom_nodes_not_created\"";
  } else if (diagnostics.computed_list_item_count == 0) {
    json << "\"list_item_computed_display_not_list_item\"";
  } else if (diagnostics.dynamic_layout_list_item_count == 0) {
    json << "\"list_item_layout_object_not_created\"";
  } else if (diagnostics.marker_layout_object_count == 0) {
    json << "\"marker_pseudo_layout_object_not_created\"";
  } else {
    json << "\"marker_layout_present\"";
  }
  json << "}";
  return json.str();
}

std::string DisplayNameForTableDiagnostics(EDisplay display) {
  switch (display) {
    case EDisplay::kTable:
      return "table";
    case EDisplay::kInlineTable:
      return "inline-table";
    case EDisplay::kTableColumnGroup:
      return "table-column-group";
    case EDisplay::kTableColumn:
      return "table-column";
    case EDisplay::kTableRowGroup:
      return "table-row-group";
    case EDisplay::kTableHeaderGroup:
      return "table-header-group";
    case EDisplay::kTableFooterGroup:
      return "table-footer-group";
    case EDisplay::kTableRow:
      return "table-row";
    case EDisplay::kTableCell:
      return "table-cell";
    case EDisplay::kTableCaption:
      return "table-caption";
    default:
      return std::to_string(static_cast<int>(display));
  }
}

int CountLowercaseTokenForStandaloneRenderer(const std::string& lower_html,
                                             const char* token) {
  int count = 0;
  size_t pos = 0;
  while ((pos = lower_html.find(token, pos)) != std::string::npos) {
    ++count;
    pos += std::strlen(token);
  }
  return count;
}

int CountLowercaseStartTagForStandaloneRenderer(const std::string& lower_html,
                                                const char* tag_name) {
  const std::string prefix = std::string("<") + tag_name;
  int count = 0;
  size_t pos = 0;
  while ((pos = lower_html.find(prefix, pos)) != std::string::npos) {
    const size_t after = pos + prefix.size();
    if (after < lower_html.size()) {
      const char next = lower_html[after];
      if (std::isalnum(static_cast<unsigned char>(next)) || next == '-' ||
          next == '_') {
        pos = after;
        continue;
      }
    }
    ++count;
    pos = after;
  }
  return count;
}

struct TableColumnElementDiagnosticForStandaloneRenderer {
  std::string tag_name;
  std::string debug_id;
  std::string width_attr;
  std::string span_attr;
  std::string computed_display;
  std::string layout_object_type;
  std::string parent_layout_object_type;
  bool layout_object_present = false;
  bool layout_table_column_object = false;
  bool production_failsoft_skipped = false;
};

struct TableColumnDiagnosticsForStandaloneRenderer {
  int source_table_count = 0;
  int source_colgroup_count = 0;
  int source_col_count = 0;
  int dom_table_count = 0;
  int dom_colgroup_count = 0;
  int dom_col_count = 0;
  int dom_tbody_like_count = 0;
  int dom_tr_count = 0;
  int dom_cell_count = 0;
  int computed_table_column_group_count = 0;
  int computed_table_column_count = 0;
  int computed_css_table_column_group_count = 0;
  int computed_css_table_column_count = 0;
  int colgroup_with_layout_object_count = 0;
  int col_with_layout_object_count = 0;
  int layout_table_count = 0;
  int layout_table_column_count = 0;
  int layout_table_section_count = 0;
  int layout_table_row_count = 0;
  int layout_table_cell_count = 0;
  int layout_table_caption_count = 0;
  int production_failsoft_skipped_column_count = 0;
  int column_width_hint_count = 0;
  bool fixed_table_layout_requested = false;
  std::vector<TableColumnElementDiagnosticForStandaloneRenderer> column_elements;
};

void CollectTableColumnLayoutDiagnosticsForStandaloneRenderer(
    const LayoutObject* object,
    TableColumnDiagnosticsForStandaloneRenderer& diagnostics) {
  if (!object) {
    return;
  }
  const std::string debug_name = BlinkStringToStdStringForStandaloneRenderer(
      object->DebugName());
  if (debug_name.find("LayoutTableCol") != std::string::npos ||
      debug_name.find("LayoutTableColumn") != std::string::npos) {
    ++diagnostics.layout_table_column_count;
  } else if (debug_name.find("LayoutTableSection") != std::string::npos) {
    ++diagnostics.layout_table_section_count;
  } else if (debug_name.find("LayoutTableRow") != std::string::npos) {
    ++diagnostics.layout_table_row_count;
  } else if (debug_name.find("LayoutTableCell") != std::string::npos) {
    ++diagnostics.layout_table_cell_count;
  } else if (debug_name.find("LayoutTableCaption") != std::string::npos) {
    ++diagnostics.layout_table_caption_count;
  } else if (debug_name.find("LayoutTable") != std::string::npos) {
    ++diagnostics.layout_table_count;
  }
  for (const LayoutObject* child = object->SlowFirstChild(); child;
       child = child->NextSibling()) {
    CollectTableColumnLayoutDiagnosticsForStandaloneRenderer(child,
                                                            diagnostics);
  }
}

void CollectTableColumnDomDiagnosticsForStandaloneRenderer(
    Node* node,
    TableColumnDiagnosticsForStandaloneRenderer& diagnostics) {
  if (!node) {
    return;
  }
  if (auto* element = DynamicTo<Element>(node)) {
    const bool is_table = element->HasTagName(html_names::kTableTag);
    const bool is_colgroup = element->HasTagName(html_names::kColgroupTag);
    const bool is_col = element->HasTagName(html_names::kColTag);
    const bool is_tbody_like = element->HasTagName(html_names::kTbodyTag) ||
                               element->HasTagName(html_names::kTheadTag) ||
                               element->HasTagName(html_names::kTfootTag);
    const bool is_tr = element->HasTagName(html_names::kTrTag);
    const bool is_cell = element->HasTagName(html_names::kTdTag) ||
                         element->HasTagName(html_names::kThTag);
    const ComputedStyle* style = element->GetComputedStyle();
    const bool computed_column_group =
        style && style->Display() == EDisplay::kTableColumnGroup;
    const bool computed_column =
        style && style->Display() == EDisplay::kTableColumn;
    const bool is_column_diagnostic_element =
        is_colgroup || is_col || computed_column_group || computed_column;
    if (is_table) {
      ++diagnostics.dom_table_count;
    }
    if (is_colgroup) {
      ++diagnostics.dom_colgroup_count;
    }
    if (is_col) {
      ++diagnostics.dom_col_count;
    }
    if (is_tbody_like) {
      ++diagnostics.dom_tbody_like_count;
    }
    if (is_tr) {
      ++diagnostics.dom_tr_count;
    }
    if (is_cell) {
      ++diagnostics.dom_cell_count;
    }

    if (style && style->IsFixedTableLayout()) {
      diagnostics.fixed_table_layout_requested = true;
    }
    if (style) {
      if (computed_column_group) {
        ++diagnostics.computed_table_column_group_count;
        if (!is_colgroup) {
          ++diagnostics.computed_css_table_column_group_count;
        }
      }
      if (computed_column) {
        ++diagnostics.computed_table_column_count;
        if (!is_col) {
          ++diagnostics.computed_css_table_column_count;
        }
      }
    }

    if (is_column_diagnostic_element) {
      TableColumnElementDiagnosticForStandaloneRenderer item;
      item.tag_name = BlinkStringToStdStringForStandaloneRenderer(
          element->tagName());
      item.debug_id = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(AtomicString("data-debug-id")));
      item.width_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kWidthAttr));
      item.span_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kSpanAttr));
      if (!item.width_attr.empty()) {
        ++diagnostics.column_width_hint_count;
      }
      if (style) {
        item.computed_display = DisplayNameForTableDiagnostics(style->Display());
      } else {
        item.computed_display = "style_unavailable";
      }
      if (LayoutObject* layout_object = element->GetLayoutObject()) {
        item.layout_object_present = true;
        item.layout_object_type = BlinkStringToStdStringForStandaloneRenderer(
            layout_object->DebugName());
        item.layout_table_column_object =
            DynamicTo<LayoutTableColumn>(layout_object) != nullptr;
        if (layout_object->Parent()) {
          item.parent_layout_object_type =
              BlinkStringToStdStringForStandaloneRenderer(
                  layout_object->Parent()->DebugName());
        }
        if (is_colgroup) {
          ++diagnostics.colgroup_with_layout_object_count;
        }
        if (is_col) {
          ++diagnostics.col_with_layout_object_count;
        }
      } else {
        item.layout_object_type = "null";
        item.production_failsoft_skipped =
            computed_column_group || computed_column;
        if (item.production_failsoft_skipped) {
          ++diagnostics.production_failsoft_skipped_column_count;
        }
      }
      diagnostics.column_elements.push_back(std::move(item));
    }
  }

  for (Node* child = node->firstChild(); child; child = child->nextSibling()) {
    CollectTableColumnDomDiagnosticsForStandaloneRenderer(child, diagnostics);
  }
}

std::string TableGroupedChildrenSummaryJsonForStandaloneRenderer(
    Element* table_element) {
  if (!table_element) {
    return "{\"table_present\":false}";
  }
  LayoutObject* layout_object = table_element->GetLayoutObject();
  auto* layout_table = DynamicTo<LayoutTable>(layout_object);
  if (!layout_table) {
    std::ostringstream missing;
    missing << "{\"table_present\":true,\"layout_table_present\":false"
            << ",\"layout_object_type\":";
    if (layout_object) {
      missing << JsonStringForStandaloneRenderer(
          BlinkStringToStdStringForStandaloneRenderer(
              layout_object->DebugName()));
    } else {
      missing << "null";
    }
    missing << "}";
    return missing.str();
  }

  TableGroupedChildren grouped_children{BlockNode(layout_table)};
  int rows = 0;
  int cells = 0;
  for (const BlockNode& section : grouped_children.bodies) {
    for (LayoutInputNode row = section.FirstChild(); row;
         row = row.NextSibling()) {
      if (row.Style().Display() != EDisplay::kTableRow) {
        continue;
      }
      ++rows;
      BlockNode row_block = To<BlockNode>(row);
      for (LayoutInputNode cell = row_block.FirstChild(); cell;
           cell = cell.NextSibling()) {
        if (cell.Style().Display() == EDisplay::kTableCell) {
          ++cells;
        }
      }
    }
  }

  std::ostringstream json;
  json << "{\"table_present\":true,\"layout_table_present\":true"
       << ",\"columns_count\":" << grouped_children.columns.size()
       << ",\"captions_count\":" << grouped_children.captions.size()
       << ",\"headers_count\":" << (grouped_children.header ? 1 : 0)
       << ",\"footers_count\":" << (grouped_children.footer ? 1 : 0)
       << ",\"bodies_count\":" << grouped_children.bodies.size()
       << ",\"rows_count\":" << rows
       << ",\"cells_count\":" << cells << "}";
  return json.str();
}

std::string TableColumnDiagnosticsJsonForStandaloneRenderer(
    Document& document,
    const std::string& html) {
  TableColumnDiagnosticsForStandaloneRenderer diagnostics;
  std::string lower_html = html;
  std::transform(lower_html.begin(), lower_html.end(), lower_html.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  diagnostics.source_table_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "table");
  diagnostics.source_colgroup_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "colgroup");
  diagnostics.source_col_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "col");
  if (LayoutView* view = document.GetLayoutView()) {
    CollectTableColumnLayoutDiagnosticsForStandaloneRenderer(view,
                                                            diagnostics);
  }
  CollectTableColumnDomDiagnosticsForStandaloneRenderer(&document,
                                                       diagnostics);

  Element* table = document.body()
                       ? FindElementByTagForStandaloneRenderer(
                             *document.body(), html_names::kTableTag)
                       : nullptr;
  if (!table && document.body()) {
    table = FindElementByAttributeValueForStandaloneRenderer(
        *document.body(), AtomicString("data-debug-id"),
        AtomicString("table"));
  }
  std::ostringstream json;
  json << "{\"real_layout_table_column_creation_enabled\":true"
       << ",\"production_failsoft_active\":false"
       << ",\"source\":{\"table_count\":" << diagnostics.source_table_count
       << ",\"colgroup_count\":" << diagnostics.source_colgroup_count
       << ",\"col_count\":" << diagnostics.source_col_count << "}"
       << ",\"dom\":{\"table_count\":" << diagnostics.dom_table_count
       << ",\"colgroup_count\":" << diagnostics.dom_colgroup_count
       << ",\"col_count\":" << diagnostics.dom_col_count
       << ",\"tbody_like_count\":" << diagnostics.dom_tbody_like_count
       << ",\"tr_count\":" << diagnostics.dom_tr_count
       << ",\"cell_count\":" << diagnostics.dom_cell_count << "}"
       << ",\"computed\":{\"table_column_group_count\":"
       << diagnostics.computed_table_column_group_count
       << ",\"table_column_count\":"
       << diagnostics.computed_table_column_count
       << ",\"css_table_column_group_count\":"
       << diagnostics.computed_css_table_column_group_count
       << ",\"css_table_column_count\":"
       << diagnostics.computed_css_table_column_count
       << ",\"fixed_table_layout_requested\":"
       << (diagnostics.fixed_table_layout_requested ? "true" : "false")
       << "}"
       << ",\"layout_counts\":{\"layout_table\":"
       << diagnostics.layout_table_count
       << ",\"layout_table_column\":"
       << diagnostics.layout_table_column_count
       << ",\"layout_table_section\":"
       << diagnostics.layout_table_section_count
       << ",\"layout_table_row\":" << diagnostics.layout_table_row_count
       << ",\"layout_table_cell\":" << diagnostics.layout_table_cell_count
       << ",\"layout_table_caption\":"
       << diagnostics.layout_table_caption_count << "}"
       << ",\"table_grouped_children\":"
       << TableGroupedChildrenSummaryJsonForStandaloneRenderer(table)
       << ",\"column_width_hint_count\":"
       << diagnostics.column_width_hint_count
       << ",\"production_failsoft_skipped_column_count\":"
       << diagnostics.production_failsoft_skipped_column_count
       << ",\"column_elements\":[";
  for (size_t i = 0; i < diagnostics.column_elements.size(); ++i) {
    if (i) {
      json << ",";
    }
    const auto& item = diagnostics.column_elements[i];
    json << "{\"tag_name\":"
         << JsonStringForStandaloneRenderer(item.tag_name)
         << ",\"data_debug_id\":"
         << JsonStringForStandaloneRenderer(item.debug_id)
         << ",\"width_attr\":"
         << JsonStringForStandaloneRenderer(item.width_attr)
         << ",\"span_attr\":"
         << JsonStringForStandaloneRenderer(item.span_attr)
         << ",\"computed_display\":"
         << JsonStringForStandaloneRenderer(item.computed_display)
         << ",\"layout_object_present\":"
         << (item.layout_object_present ? "true" : "false")
         << ",\"layout_object_type\":"
         << JsonStringForStandaloneRenderer(item.layout_object_type)
         << ",\"parent_layout_object_type\":"
         << JsonStringForStandaloneRenderer(item.parent_layout_object_type)
         << ",\"layout_table_column_object\":"
         << (item.layout_table_column_object ? "true" : "false")
         << ",\"production_failsoft_skipped\":"
         << (item.production_failsoft_skipped ? "true" : "false")
         << "}";
  }
  json << "],\"first_missing_stage\":";
  if (diagnostics.production_failsoft_skipped_column_count > 0) {
    json << "\"standalone_table_column_layout_object_failsoft\"";
  } else if (diagnostics.source_colgroup_count == 0 &&
             diagnostics.source_col_count == 0 &&
             diagnostics.computed_table_column_group_count == 0 &&
             diagnostics.computed_table_column_count == 0) {
    json << "\"no_table_columns_in_source\"";
  } else if (diagnostics.dom_colgroup_count == 0 &&
             diagnostics.dom_col_count == 0 &&
             diagnostics.computed_table_column_group_count == 0 &&
             diagnostics.computed_table_column_count == 0) {
    json << "\"table_column_dom_nodes_not_created\"";
  } else if (diagnostics.computed_table_column_group_count == 0 &&
             diagnostics.computed_table_column_count == 0) {
    json << "\"table_column_computed_display_missing\"";
  } else if (diagnostics.layout_table_column_count == 0) {
    json << "\"layout_table_column_object_not_created\"";
  } else {
    json << "\"layout_table_column_present\"";
  }
  json << ",\"diagnostic_experiment\":{\"last_known_native_path\":"
       << "\"LayoutTableColumn constructed/inserted; TableGroupedChildren "
          "grouped native table as columns=1 bodies=1; no "
          "TableLayoutAlgorithm::Layout breadcrumb before timeout\","
       << "\"css_display_table_column_contrast\":"
       << "\"CSS display:table-column reaches layout/prepaint/paint with "
          "real column creation, so the blocker is native col/colgroup "
          "attachment/grouping/presentation, not generic table-column "
          "display\"}}";
  return json.str();
}

struct FormControlElementDiagnosticForStandaloneRenderer {
  std::string tag_name;
  std::string debug_id;
  std::string type_attr;
  std::string value_attr;
  std::string element_interface;
  std::string computed_display;
  std::string layout_object_type;
  std::string parent_layout_object_type;
  std::string first_missing_stage;
  std::string standalone_support_status;
  std::string unsupported_closure_boundary;
  bool layout_object_present = false;
  bool checked = false;
  bool user_agent_shadow_root_present = false;
  bool text_control_inner_editor_present = false;
  bool placeholder_attr_present = false;
  bool placeholder_visible = false;
  int user_agent_shadow_child_count = 0;
  int shadow_layout_object_count = 0;
  int shadow_layout_text_count = 0;
  int option_count = 0;
  int selected_option_count = 0;
};

struct FormControlDiagnosticsForStandaloneRenderer {
  int source_input_count = 0;
  int source_select_count = 0;
  int source_option_count = 0;
  int source_optgroup_count = 0;
  int source_textarea_count = 0;
  int source_button_count = 0;
  int dom_input_count = 0;
  int dom_select_count = 0;
  int dom_option_count = 0;
  int dom_optgroup_count = 0;
  int dom_textarea_count = 0;
  int dom_button_count = 0;
  int controls_with_layout_object_count = 0;
  int controls_with_user_agent_shadow_root_count = 0;
  int controls_with_shadow_layout_text_count = 0;
  bool input_missing_value_text_stage = false;
  bool unsupported_input_type_stage = false;
  bool temporal_input_type_stage = false;
  bool select_missing_shadow_stage = false;
  bool select_picker_icon_stage = false;
  bool textarea_missing_shadow_stage = false;
  std::vector<FormControlElementDiagnosticForStandaloneRenderer> controls;
};

bool IsStandaloneSupportedTextInputTypeForDiagnostics(
    const std::string& type_attr) {
  if (type_attr.empty()) {
    return true;
  }
  std::string lower_type = type_attr;
  std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return lower_type == "text" || lower_type == "search" ||
         lower_type == "password";
}

bool IsStandaloneSupportedCheckableInputTypeForDiagnostics(
    const std::string& type_attr) {
  std::string lower_type = type_attr;
  std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return lower_type == "checkbox" || lower_type == "radio";
}

bool IsStandaloneTemporalInputTypeForDiagnostics(
    const std::string& type_attr) {
  std::string lower_type = type_attr;
  std::transform(lower_type.begin(), lower_type.end(), lower_type.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return lower_type == "date" || lower_type == "time" ||
         lower_type == "datetime-local" || lower_type == "month" ||
         lower_type == "week";
}

void CollectShadowLayoutDiagnosticsForStandaloneRenderer(
    Node* node,
    FormControlElementDiagnosticForStandaloneRenderer& item) {
  if (!node) {
    return;
  }
  if (LayoutObject* layout_object = node->GetLayoutObject()) {
    ++item.shadow_layout_object_count;
    const std::string debug_name = BlinkStringToStdStringForStandaloneRenderer(
        layout_object->DebugName());
    if (debug_name.find("LayoutText") != std::string::npos) {
      ++item.shadow_layout_text_count;
    }
  }
  for (Node* child = node->firstChild(); child; child = child->nextSibling()) {
    CollectShadowLayoutDiagnosticsForStandaloneRenderer(child, item);
  }
}

void CollectFormControlDomDiagnosticsForStandaloneRenderer(
    Node* node,
    FormControlDiagnosticsForStandaloneRenderer& diagnostics) {
  if (!node) {
    return;
  }
  if (auto* element = DynamicTo<Element>(node)) {
    const bool is_input = element->HasTagName(html_names::kInputTag);
    const bool is_select = element->HasTagName(html_names::kSelectTag);
    const bool is_option = element->HasTagName(html_names::kOptionTag);
    const bool is_optgroup = element->HasTagName(html_names::kOptgroupTag);
    const bool is_textarea = element->HasTagName(html_names::kTextareaTag);
    const bool is_button = element->HasTagName(html_names::kButtonTag);
    if (is_input) {
      ++diagnostics.dom_input_count;
    }
    if (is_select) {
      ++diagnostics.dom_select_count;
    }
    if (is_option) {
      ++diagnostics.dom_option_count;
    }
    if (is_optgroup) {
      ++diagnostics.dom_optgroup_count;
    }
    if (is_textarea) {
      ++diagnostics.dom_textarea_count;
    }
    if (is_button) {
      ++diagnostics.dom_button_count;
    }

    if (is_input || is_select || is_textarea || is_button) {
      FormControlElementDiagnosticForStandaloneRenderer item;
      item.tag_name = BlinkStringToStdStringForStandaloneRenderer(
          element->tagName());
      item.debug_id = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(AtomicString("data-debug-id")));
      item.type_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kTypeAttr));
      item.value_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kValueAttr));
      item.placeholder_attr_present =
          element->FastHasAttribute(html_names::kPlaceholderAttr);
      if (auto* input = DynamicTo<HTMLInputElement>(element)) {
        item.element_interface = "HTMLInputElement";
        item.checked = input->Checked();
      } else if (auto* select = DynamicTo<HTMLSelectElement>(element)) {
        item.element_interface = "HTMLSelectElement";
      } else if (auto* textarea = DynamicTo<HTMLTextAreaElement>(element)) {
        item.element_interface = "HTMLTextAreaElement";
        item.value_attr = BlinkStringToStdStringForStandaloneRenderer(
            textarea->Value());
        item.placeholder_visible =
            item.placeholder_attr_present && item.value_attr.empty();
      } else if (auto* text_control =
                     DynamicTo<TextControlElement>(element)) {
        item.element_interface = "TextControlElement";
        item.value_attr = BlinkStringToStdStringForStandaloneRenderer(
            text_control->Value());
      } else {
        item.element_interface = "HTMLElement";
      }
      if (auto* text_control = DynamicTo<TextControlElement>(element)) {
        item.text_control_inner_editor_present =
            text_control->InnerEditorElement();
      }
      if (const ComputedStyle* style = element->GetComputedStyle()) {
        item.computed_display = DisplayNameForTableDiagnostics(style->Display());
      } else {
        item.computed_display = "style_unavailable";
      }
      if (LayoutObject* layout_object = element->GetLayoutObject()) {
        item.layout_object_present = true;
        ++diagnostics.controls_with_layout_object_count;
        item.layout_object_type = BlinkStringToStdStringForStandaloneRenderer(
            layout_object->DebugName());
        if (layout_object->Parent()) {
          item.parent_layout_object_type =
              BlinkStringToStdStringForStandaloneRenderer(
                  layout_object->Parent()->DebugName());
        }
      } else {
        item.layout_object_type = "null";
      }
      if (ShadowRoot* shadow_root = element->UserAgentShadowRoot()) {
        item.user_agent_shadow_root_present = true;
        ++diagnostics.controls_with_user_agent_shadow_root_count;
        for (Node* child = shadow_root->firstChild(); child;
             child = child->nextSibling()) {
          ++item.user_agent_shadow_child_count;
          CollectShadowLayoutDiagnosticsForStandaloneRenderer(child, item);
        }
        if (item.shadow_layout_text_count > 0) {
          ++diagnostics.controls_with_shadow_layout_text_count;
        }
      }
      if (is_select) {
        for (Node* child = element->firstChild(); child;
             child = child->nextSibling()) {
          if (auto* child_element = DynamicTo<Element>(child)) {
            if (child_element->HasTagName(html_names::kOptionTag)) {
              ++item.option_count;
              if (child_element->FastHasAttribute(html_names::kSelectedAttr)) {
                ++item.selected_option_count;
              }
            }
          }
        }
      }

      const bool is_supported_checkable_input =
          is_input &&
          IsStandaloneSupportedCheckableInputTypeForDiagnostics(item.type_attr);
      const bool is_temporal_input =
          is_input &&
          IsStandaloneTemporalInputTypeForDiagnostics(item.type_attr);
      if (is_input && is_supported_checkable_input &&
          item.layout_object_present) {
        item.first_missing_stage = "checkable_control_layout_present";
        item.standalone_support_status = "supported_checkable_input";
      } else if (is_temporal_input) {
        item.first_missing_stage =
            "temporal_input_type_requires_date_time_view_or_chooser_path";
        item.standalone_support_status =
            "unsupported_temporal_input_normalized_to_text_subset";
        item.unsupported_closure_boundary =
            "BaseTemporalInputType::CreateView selects "
            "ChooserOnlyTemporalInputTypeView or "
            "MultipleFieldsTemporalInputTypeView; both require date/time "
            "shadow edit fields, picker indicator/chooser plumbing, and "
            "browser-facing DateTimeChooser support that is intentionally "
            "outside the standalone subset";
        diagnostics.temporal_input_type_stage = true;
        diagnostics.unsupported_input_type_stage = true;
      } else if (is_input &&
          !IsStandaloneSupportedTextInputTypeForDiagnostics(item.type_attr)) {
        item.first_missing_stage =
            "unsupported_input_type_normalized_to_text_subset";
        item.standalone_support_status =
            "unsupported_input_normalized_to_text_subset";
        item.unsupported_closure_boundary =
            "InputType::Create is narrowed to text/search/password/"
            "checkbox/radio/default in standalone; browser-facing input "
            "families remain fail-soft";
        diagnostics.unsupported_input_type_stage = true;
      } else if (is_input && !item.user_agent_shadow_root_present) {
        item.first_missing_stage =
            "input_user_agent_shadow_root_missing_or_not_real_input_element";
        item.standalone_support_status = "text_input_shadow_missing";
        diagnostics.input_missing_value_text_stage = !item.value_attr.empty();
      } else if (is_input && item.shadow_layout_text_count == 0 &&
                 !item.value_attr.empty()) {
        item.first_missing_stage =
            "input_value_shadow_layout_text_missing";
        item.standalone_support_status = "text_input_value_layout_missing";
        diagnostics.input_missing_value_text_stage = true;
      } else if (is_select && !item.user_agent_shadow_root_present) {
        item.first_missing_stage =
            "select_user_agent_shadow_root_missing_or_not_real_select_element";
        item.standalone_support_status = "select_shadow_missing";
        diagnostics.select_missing_shadow_stage = true;
      } else if (is_select && item.option_count == 0) {
        item.first_missing_stage = "select_option_dom_missing";
        item.standalone_support_status = "select_option_dom_missing";
#if HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL
      } else if (is_select) {
        item.first_missing_stage = "select_picker_icon_theme_pseudo_failsoft";
        item.standalone_support_status =
            "closed_select_value_layout_supported_picker_icon_failsoft";
        item.unsupported_closure_boundary =
            "Closed/basic select UA shadow, option text, layout, and paint are "
            "enabled; ::picker-icon remains disabled because the real pseudo "
            "path previously failed during style recalc and depends on "
            "browser/theme-backed control machinery absent from standalone";
        diagnostics.select_picker_icon_stage = true;
#endif
      } else if (is_textarea && !item.user_agent_shadow_root_present) {
        item.first_missing_stage = "textarea_text_control_shadow_not_linked";
        item.standalone_support_status = "textarea_shadow_missing";
        diagnostics.textarea_missing_shadow_stage = true;
      } else {
        item.first_missing_stage = "control_layout_present";
        item.standalone_support_status = "supported_control_layout_present";
      }
      diagnostics.controls.push_back(std::move(item));
    }
  }

  for (Node* child = node->firstChild(); child; child = child->nextSibling()) {
    CollectFormControlDomDiagnosticsForStandaloneRenderer(child, diagnostics);
  }
}

std::string FormControlDiagnosticsJsonForStandaloneRenderer(
    Document& document,
    const std::string& html) {
  FormControlDiagnosticsForStandaloneRenderer diagnostics;
  std::string lower_html = html;
  std::transform(lower_html.begin(), lower_html.end(), lower_html.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  diagnostics.source_input_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "input");
  diagnostics.source_select_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "select");
  diagnostics.source_option_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "option");
  diagnostics.source_optgroup_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "optgroup");
  diagnostics.source_textarea_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "textarea");
  diagnostics.source_button_count =
      CountLowercaseStartTagForStandaloneRenderer(lower_html, "button");
  CollectFormControlDomDiagnosticsForStandaloneRenderer(&document,
                                                       diagnostics);

  std::ostringstream json;
  json << "{\"source\":{\"input_count\":" << diagnostics.source_input_count
       << ",\"select_count\":" << diagnostics.source_select_count
       << ",\"option_count\":" << diagnostics.source_option_count
       << ",\"optgroup_count\":" << diagnostics.source_optgroup_count
       << ",\"textarea_count\":" << diagnostics.source_textarea_count
       << ",\"button_count\":" << diagnostics.source_button_count << "}"
       << ",\"dom\":{\"input_count\":" << diagnostics.dom_input_count
       << ",\"select_count\":" << diagnostics.dom_select_count
       << ",\"option_count\":" << diagnostics.dom_option_count
       << ",\"optgroup_count\":" << diagnostics.dom_optgroup_count
       << ",\"textarea_count\":" << diagnostics.dom_textarea_count
       << ",\"button_count\":" << diagnostics.dom_button_count << "}"
       << ",\"controls_with_layout_object_count\":"
       << diagnostics.controls_with_layout_object_count
       << ",\"controls_with_user_agent_shadow_root_count\":"
       << diagnostics.controls_with_user_agent_shadow_root_count
       << ",\"controls_with_shadow_layout_text_count\":"
       << diagnostics.controls_with_shadow_layout_text_count
       << ",\"standalone_source_status\":{"
#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
       << "\"html_input_element_source_linked\":true,"
       << "\"html_text_area_element_source_linked\":true,"
       << "\"html_select_element_source_linked\":true,"
       << "\"text_control_shadow_subtree_stubbed\":false,"
       << "\"text_input_subset_enabled\":true,"
       << "\"textarea_text_control_enabled\":true,"
#if HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL
       << "\"select_control_subset_enabled\":true,"
       << "\"native_select_shadow_path_unsafe_in_prior_experiment\":false,"
       << "\"select_picker_icon_pseudo_failsoft\":true,"
       << "\"select_picker_icon_failsoft_reason\":\"standalone does not "
          "provide browser/theme-backed picker icon pseudo machinery\","
#else
       << "\"select_control_subset_enabled\":false,"
       << "\"native_select_shadow_path_unsafe_in_prior_experiment\":true,"
       << "\"select_picker_icon_pseudo_failsoft\":false,"
#endif
       << "\"enabled_input_type_names\":[\"text\",\"search\",\"password\","
          "\"checkbox\",\"radio\",\"empty-default-to-text\"],"
       << "\"unsupported_input_behavior\":\"unsupported input types normalize "
          "to the standalone text-control subset rather than linking "
          "file/date/color/range/chooser UI paths\","
       << "\"temporal_input_support_status\":\"unsupported_failsoft\","
       << "\"temporal_input_blocker\":\"BaseTemporalInputType::CreateView "
          "selects ChooserOnlyTemporalInputTypeView or "
          "MultipleFieldsTemporalInputTypeView. The closed/static date-time "
          "path still requires DateTimeEditElement or DateTimeChooser/"
          "picker-indicator plumbing, including browser-facing chooser UI "
          "hooks that are intentionally out of scope for standalone.\","
       << "\"standalone_guards\":["
       << "\"InputType factory is narrowed to text/search/password/checkbox/"
          "radio/default\","
       << "\"numeric range/step validation and spin-button paths are no-op\","
       << "\"datalist/browser chooser paths are disabled\","
       << "\"text-control selection/editing APIs use cached selection only\","
       << "\"opaque ranges are unsupported in standalone text input\"],"
#if HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL
       << "\"remaining_unsupported_controls\":[\"file\",\"color\","
          "\"date/time\",\"range\"],"
       << "\"production_policy\":\"real Blink text input and closed/basic "
          "select subsets, real textarea text-control layout, and real "
          "checkbox/radio input types are enabled; picker-icon/popup/browser-"
          "facing controls remain fail-soft\""
#else
       << "\"remaining_unsupported_controls\":[\"select\",\"file\","
          "\"color\",\"date/time\",\"range\"],"
       << "\"production_policy\":\"real Blink text input subset is enabled; "
         "real textarea text-control layout and real checkbox/radio input "
         "types are enabled; non-text browser-facing controls remain "
         "fail-soft\""
#endif
#else
       << "\"html_input_element_source_linked\":false,"
       << "\"html_select_element_source_linked\":true,"
       << "\"text_control_shadow_subtree_stubbed\":true,"
       << "\"native_select_shadow_path_unsafe_in_prior_experiment\":true,"
       << "\"text_input_subset_blocked\":true,"
       << "\"text_input_blocker\":\"real HTMLInputElement requires a "
          "standalone text-only InputType/TextControlElement source subset; "
          "the current generated input_type_names stub and text-control "
          "stubs only support the reduced non-text path\","
       << "\"text_input_sources_needed\":["
       << "\"core/html/forms/html_input_element.cc\","
       << "\"core/html/forms/input_type.cc\","
       << "\"core/html/forms/input_type_view.cc\","
       << "\"core/html/forms/base_text_input_type.cc\","
       << "\"core/html/forms/text_input_type.cc\","
       << "\"core/html/forms/text_field_input_type.cc\","
       << "\"core/html/forms/text_control_element.cc\","
       << "\"core/html/forms/text_control_inner_elements.cc\","
       << "\"core/layout/forms/layout_text_control.cc\","
       << "\"core/layout/forms/layout_text_control_single_line.cc\","
       << "\"core/layout/forms/layout_text_control_inner_editor.cc\"],"
       << "\"non_text_closure_blockers\":["
       << "\"reduced input_type_names.h exposes only image/file\","
       << "\"InputType::Create and NormalizeTypeName enumerate all browser "
          "input types\","
       << "\"html_input_element.cc references file/date/color/radio/datalist "
          "paths unconditionally\","
       << "\"date_time_chooser.mojom-blink.h is absent in standalone\","
       << "\"TextEvent and AX command stubs are missing members needed by the "
         "full input closure\"],"
       << "\"temporal_input_support_status\":\"blocked_until_text_input_subset_"
          "is_linked\","
       << "\"production_policy\":\"keep generic fail-soft control layout "
          "until a Blink-owned text-only source subset is linked\""
#endif
       << "}"
       << ",\"controls\":[";
  for (size_t i = 0; i < diagnostics.controls.size(); ++i) {
    if (i) {
      json << ",";
    }
    const auto& item = diagnostics.controls[i];
    json << "{\"tag_name\":" << JsonStringForStandaloneRenderer(item.tag_name)
         << ",\"data_debug_id\":"
         << JsonStringForStandaloneRenderer(item.debug_id)
         << ",\"type_attr\":" << JsonStringForStandaloneRenderer(item.type_attr)
         << ",\"value_length\":" << item.value_attr.size()
         << ",\"element_interface\":"
         << JsonStringForStandaloneRenderer(item.element_interface)
         << ",\"checked\":" << (item.checked ? "true" : "false")
         << ",\"computed_display\":"
         << JsonStringForStandaloneRenderer(item.computed_display)
         << ",\"layout_object_present\":"
         << (item.layout_object_present ? "true" : "false")
         << ",\"layout_object_type\":"
         << JsonStringForStandaloneRenderer(item.layout_object_type)
         << ",\"parent_layout_object_type\":"
         << JsonStringForStandaloneRenderer(item.parent_layout_object_type)
         << ",\"standalone_support_status\":"
         << JsonStringForStandaloneRenderer(item.standalone_support_status)
         << ",\"unsupported_closure_boundary\":"
         << JsonStringForStandaloneRenderer(item.unsupported_closure_boundary)
         << ",\"user_agent_shadow_root_present\":"
         << (item.user_agent_shadow_root_present ? "true" : "false")
         << ",\"text_control_inner_editor_present\":"
         << (item.text_control_inner_editor_present ? "true" : "false")
         << ",\"placeholder_attr_present\":"
         << (item.placeholder_attr_present ? "true" : "false")
         << ",\"placeholder_visible\":"
         << (item.placeholder_visible ? "true" : "false")
         << ",\"user_agent_shadow_child_count\":"
         << item.user_agent_shadow_child_count
         << ",\"shadow_layout_object_count\":"
         << item.shadow_layout_object_count
         << ",\"shadow_layout_text_count\":" << item.shadow_layout_text_count
         << ",\"option_count\":" << item.option_count
         << ",\"selected_option_count\":" << item.selected_option_count
         << ",\"first_missing_stage\":"
         << JsonStringForStandaloneRenderer(item.first_missing_stage) << "}";
  }
  json << "],\"first_missing_stage\":";
  if (diagnostics.source_input_count == 0 &&
      diagnostics.source_select_count == 0 &&
      diagnostics.source_textarea_count == 0 &&
      diagnostics.source_button_count == 0) {
    json << "\"no_form_controls_in_source\"";
  } else if (diagnostics.dom_input_count + diagnostics.dom_select_count +
                 diagnostics.dom_textarea_count + diagnostics.dom_button_count ==
             0) {
    json << "\"form_control_dom_nodes_not_created\"";
  } else if (diagnostics.controls_with_layout_object_count == 0) {
    json << "\"form_control_layout_objects_not_created\"";
  } else if (diagnostics.input_missing_value_text_stage) {
    json << "\"input_value_text_not_in_shadow_layout\"";
  } else if (diagnostics.select_missing_shadow_stage) {
    json << "\"select_shadow_tree_not_created_or_real_select_path_disabled\"";
  } else if (diagnostics.temporal_input_type_stage) {
    json << "\"temporal_input_type_requires_date_time_view_or_chooser_path\"";
  } else if (diagnostics.unsupported_input_type_stage) {
    json << "\"unsupported_input_type_normalized_to_text_subset\"";
  } else if (diagnostics.select_picker_icon_stage) {
    json << "\"select_picker_icon_theme_pseudo_failsoft\"";
  } else if (diagnostics.textarea_missing_shadow_stage) {
    json << "\"textarea_text_control_shadow_not_linked\"";
  } else {
    json << "\"form_control_layout_present\"";
  }
  json << "}";
  return json.str();
}

std::string BackgroundLayerDiagnosticsJsonForStandaloneRenderer(
    const char* name,
    const Document& document,
    const ComputedStyle* style,
    const ImageResourceObserver* primary_client,
    const ImageResourceObserver* alternate_client,
    const Node* node) {
  std::ostringstream json;
  json << "{\"name\":" << JsonStringForStandaloneRenderer(name);
  if (!style) {
    json << ",\"present\":false}";
    return json.str();
  }

  const FillLayer& layers = style->BackgroundLayers();
  const StyleImage* image = layers.GetImage();
  int layer_count = 0;
  int image_layer_count = 0;
  for (const FillLayer* layer = &layers; layer; layer = layer->Next()) {
    ++layer_count;
    if (layer->GetImage()) {
      ++image_layer_count;
    }
  }

  json << ",\"present\":true"
       << ",\"has_background\":" << (style->HasBackground() ? "true" : "false")
       << ",\"has_background_image\":"
       << (style->HasBackgroundImage() ? "true" : "false")
       << ",\"layer_count\":" << layer_count
       << ",\"image_layer_count\":" << image_layer_count
       << ",\"first_layer_clip\":" << static_cast<int>(layers.Clip())
       << ",\"first_layer_attachment\":" << static_cast<int>(layers.Attachment())
       << ",\"first_image_present\":" << (image ? "true" : "false");
  if (!image) {
    json << "}";
    return json.str();
  }

  json << ",\"first_image_can_render\":"
       << (image->CanRender() ? "true" : "false")
       << ",\"first_image_is_pending\":"
       << (image->IsPendingImage() ? "true" : "false")
       << ",\"first_image_is_generated\":"
       << (image->IsGeneratedImage() ? "true" : "false")
       << ",\"first_image_is_loaded\":"
       << (image->IsLoaded() ? "true" : "false");

  const gfx::SizeF target_size(
      document.GetLayoutView() ? document.GetLayoutView()->ViewWidth() : 0,
      document.GetLayoutView() ? document.GetLayoutView()->ViewHeight() : 0);
  json << ",\"diagnostic_target_size\":[" << target_size.width() << ","
       << target_size.height() << "]";
  if (primary_client && node) {
    scoped_refptr<Image> primary_image =
        image->GetImage(*primary_client, *node, *style, target_size);
    json << ",\"primary_client_get_image\":"
         << (primary_image ? "true" : "false");
  } else {
    json << ",\"primary_client_get_image\":null";
  }
  if (alternate_client && node) {
    scoped_refptr<Image> alternate_image =
        image->GetImage(*alternate_client, *node, *style, target_size);
    json << ",\"alternate_client_get_image\":"
         << (alternate_image ? "true" : "false");
  } else {
    json << ",\"alternate_client_get_image\":null";
  }
  json << "}";
  return json.str();
}

std::string RootBackgroundDiagnosticsJsonForStandaloneRenderer(
    Document& document) {
  LayoutView* layout_view = document.GetLayoutView();
  Element* html = document.documentElement();
  HTMLElement* body = document.body();
  const LayoutBox* root_box = layout_view ? &layout_view->RootBox() : nullptr;
  const Node* node = html ? static_cast<const Node*>(html)
                          : static_cast<const Node*>(&document);
  std::ostringstream json;
  json << "{\"layout_view_present\":" << (layout_view ? "true" : "false")
       << ",\"root_box_present\":" << (root_box ? "true" : "false");
  if (layout_view) {
    json << ",\"layout_view_size\":[" << layout_view->ViewWidth() << ","
         << layout_view->ViewHeight() << "]";
  } else {
    json << ",\"layout_view_size\":[0,0]";
  }
  json << ",\"styles\":["
       << BackgroundLayerDiagnosticsJsonForStandaloneRenderer(
              "viewport", document,
              layout_view ? &layout_view->StyleRef() : nullptr, layout_view,
              root_box, node)
       << ","
       << BackgroundLayerDiagnosticsJsonForStandaloneRenderer(
              "html", document, html ? html->GetComputedStyle() : nullptr,
              html ? html->GetLayoutObject() : nullptr, layout_view, node)
       << ","
       << BackgroundLayerDiagnosticsJsonForStandaloneRenderer(
              "body", document, body ? body->GetComputedStyle() : nullptr,
              body ? body->GetLayoutObject() : nullptr, layout_view, node)
       << "]}";
  return json.str();
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

std::string GfxRectJsonForStandaloneRenderer(const gfx::Rect& rect) {
  std::ostringstream out;
  out << "[" << rect.x() << "," << rect.y() << "," << rect.width() << ","
      << rect.height() << "]";
  return out.str();
}

std::string GfxRectFJsonForStandaloneRenderer(const gfx::RectF& rect) {
  return RectFJsonForStandaloneRenderer(rect);
}
std::string PhysicalRectJsonForStandaloneRenderer(const PhysicalRect& rect) {
  std::ostringstream out;
  out << "[" << rect.X().ToFloat() << "," << rect.Y().ToFloat() << ","
      << rect.Width().ToFloat() << "," << rect.Height().ToFloat() << "]";
  return out.str();
}

std::string PhysicalOffsetJsonForStandaloneRenderer(
    const PhysicalOffset& offset) {
  std::ostringstream out;
  out << "[" << offset.left.ToFloat() << "," << offset.top.ToFloat() << "]";
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

uint64_t NodeIdForStandaloneRenderer(const void* node) {
  return static_cast<uint64_t>(reinterpret_cast<uintptr_t>(node));
}

uint32_t TransformChainDepthForStandaloneRenderer(
    const TransformPaintPropertyNode& transform) {
  uint32_t depth = 0;
  const auto* node = &transform;
  const auto* root = &PropertyTreeState::Root().Transform();
  while (node && node != root && depth < 256) {
    ++depth;
    node = node->UnaliasedParent();
  }
  return depth;
}

uint32_t ClipChainDepthForStandaloneRenderer(
    const ClipPaintPropertyNode& clip) {
  uint32_t depth = 0;
  const auto* node = &clip;
  const auto* root = &PropertyTreeState::Root().Clip();
  while (node && node != root && depth < 256) {
    ++depth;
    node = node->UnaliasedParent();
  }
  return depth;
}

uint32_t EffectChainDepthForStandaloneRenderer(
    const EffectPaintPropertyNode& effect) {
  uint32_t depth = 0;
  const auto* node = &effect;
  const auto* root = &PropertyTreeState::Root().Effect();
  while (node && node != root && depth < 256) {
    ++depth;
    node = node->UnaliasedParent();
  }
  return depth;
}

std::string TransformChainJsonForStandaloneRenderer(
    const TransformPaintPropertyNode& transform) {
  std::ostringstream out;
  out << "[";
  bool first = true;
  const auto* node = &transform;
  const auto* root = &PropertyTreeState::Root().Transform();
  uint32_t depth = 0;
  while (node && depth < 256) {
    if (!first) {
      out << ",";
    }
    first = false;
    const gfx::Transform matrix = node->Matrix();
    const gfx::Transform matrix_with_origin = node->MatrixWithOriginApplied();
    const bool has_non_translation =
        !SkM44IsIdentityOr2dTranslation(gfx::TransformToSkM44(matrix_with_origin));
    const gfx::Point3F& origin = node->Origin();
    const auto* parent = node->UnaliasedParent();
    out << "{\"id\":" << NodeIdForStandaloneRenderer(node)
        << ",\"parent_id\":" << NodeIdForStandaloneRenderer(parent)
        << ",\"matrix\":" << MatrixJsonForStandaloneRenderer(matrix)
        << ",\"matrix_with_origin_applied\":"
        << MatrixJsonForStandaloneRenderer(matrix_with_origin)
        << ",\"origin\":[" << origin.x() << "," << origin.y() << ","
        << origin.z() << "]"
        << ",\"is_identity\":" << (node->IsIdentity() ? "true" : "false")
        << ",\"is_identity_or_2d_translation\":"
        << (node->IsIdentityOr2dTranslation() ? "true" : "false")
        << ",\"has_non_translation\":"
        << (has_non_translation ? "true" : "false")
        << ",\"has_perspective_or_3d\":"
        << (!matrix_with_origin.Is2dTransform() ? "true" : "false")
        << ",\"associated_scroll_node_id\":"
        << NodeIdForStandaloneRenderer(node->ScrollNode())
        << ",\"nearest_scroll_translation_node_id\":null"
        << ",\"compositor_element_id\":\"inaccessible\"}";
    ++depth;
    if (node == root) {
      break;
    }
    node = parent;
  }
  out << "]";
  return out.str();
}

std::string ClipChainJsonForStandaloneRenderer(
    const ClipPaintPropertyNode& clip) {
  std::ostringstream out;
  out << "[";
  bool first = true;
  const auto* node = &clip;
  const auto* root = &PropertyTreeState::Root().Clip();
  uint32_t depth = 0;
  while (node && depth < 256) {
    if (!first) {
      out << ",";
    }
    first = false;
    const auto* parent = node->UnaliasedParent();
    const FloatClipRect& layout_clip = node->LayoutClipRect();
    const FloatRoundedRect& paint_clip = node->PaintClipRect();
    out << "{\"id\":" << NodeIdForStandaloneRenderer(node)
        << ",\"parent_id\":" << NodeIdForStandaloneRenderer(parent)
        << ",\"local_transform_space_id\":"
        << NodeIdForStandaloneRenderer(&node->LocalTransformSpace().Unalias())
        << ",\"paint_clip_rect\":"
        << RectFJsonForStandaloneRenderer(paint_clip.Rect())
        << ",\"layout_clip_rect\":"
        << (layout_clip.IsInfinite()
                ? "null"
                : RectFJsonForStandaloneRenderer(layout_clip.Rect()))
        << ",\"has_rounded_clip\":"
        << (paint_clip.IsRounded() || layout_clip.HasRadius() ? "true"
                                                              : "false")
        << ",\"has_path_clip\":"
        << (node->ClipPath().has_value() ? "true" : "false")
        << ",\"pixel_moving_filter_id\":"
        << NodeIdForStandaloneRenderer(node->PixelMovingFilter()) << "}";
    ++depth;
    if (node == root) {
      break;
    }
    node = parent;
  }
  out << "]";
  return out.str();
}

const char* FilterOperationNameForStandaloneRenderer(int type) {
  switch (type) {
    case kStandaloneFilterGrayscale:
      return "grayscale";
    case kStandaloneFilterSepia:
      return "sepia";
    case kStandaloneFilterSaturate:
      return "saturate";
    case kStandaloneFilterHueRotate:
      return "hue_rotate";
    case kStandaloneFilterInvert:
      return "invert";
    case kStandaloneFilterBrightness:
      return "brightness";
    case kStandaloneFilterContrast:
      return "contrast";
    case kStandaloneFilterOpacity:
      return "opacity";
    case kStandaloneFilterBlur:
      return "blur";
    case kStandaloneFilterDropShadow:
      return "drop_shadow";
    case kStandaloneFilterColorMatrix:
      return "color_matrix";
    default:
      return "unknown";
  }
}

std::string FilterOperationsJsonForStandaloneRenderer(
    const CompositorFilterOperations* filters) {
  bool has_unsupported_operation = false;
  std::vector<LiveExportedFilterOperation> operations =
      ExportFilterOperationsForStandaloneRenderer(filters,
                                                  &has_unsupported_operation);
  std::ostringstream out;
  out << "{\"supported\":[";
  for (size_t i = 0; i < operations.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    const LiveExportedFilterOperation& operation = operations[i];
    out << "{\"type\":\""
        << FilterOperationNameForStandaloneRenderer(operation.type)
        << "\",\"amount\":" << operation.amount
        << ",\"offset\":[" << operation.offset_x << ","
        << operation.offset_y << "]"
        << ",\"color\":[" << operation.color_r << ","
        << operation.color_g << "," << operation.color_b << ","
        << operation.color_a << "]";
    if (operation.type == kStandaloneFilterColorMatrix) {
      out << ",\"matrix\":[";
      for (size_t value_index = 0; value_index < operation.matrix.size();
           ++value_index) {
        if (value_index > 0) {
          out << ",";
        }
        out << operation.matrix[value_index];
      }
      out << "]";
    }
    out << "}";
  }
  out << "],\"unsupported\":" << (has_unsupported_operation ? "true" : "false")
      << "}";
  return out.str();
}

std::string EffectChainJsonForStandaloneRenderer(
    const EffectPaintPropertyNode& effect) {
  std::ostringstream out;
  out << "[";
  bool first = true;
  const auto* node = &effect;
  const auto* root = &PropertyTreeState::Root().Effect();
  uint32_t depth = 0;
  while (node && depth < 256) {
    if (!first) {
      out << ",";
    }
    first = false;
    const auto* parent = node->UnaliasedParent();
    out << "{\"id\":" << NodeIdForStandaloneRenderer(node)
        << ",\"parent_id\":" << NodeIdForStandaloneRenderer(parent)
        << ",\"local_transform_space_id\":"
        << NodeIdForStandaloneRenderer(&node->LocalTransformSpace().Unalias())
        << ",\"output_clip_id\":"
        << NodeIdForStandaloneRenderer(node->OutputClip()
                                           ? &node->OutputClip()->Unalias()
                                           : nullptr)
        << ",\"opacity\":" << node->Opacity()
        << ",\"blend_mode\":" << static_cast<int>(node->BlendMode())
        << ",\"has_real_effects\":"
        << (node->HasRealEffects() ? "true" : "false")
        << ",\"has_non_default_opacity\":"
        << (node->Opacity() != 1.0f ? "true" : "false")
        << ",\"has_filter\":" << (node->Filter() ? "true" : "false")
        << ",\"filter_operations\":"
        << FilterOperationsJsonForStandaloneRenderer(node->Filter())
        << ",\"has_backdrop_filter\":"
        << (node->BackdropFilter() ? "true" : "false")
        << ",\"may_have_opacity\":"
        << (node->MayHaveOpacity() ? "true" : "false")
        << ",\"may_have_filter\":"
        << (node->MayHaveFilter() ? "true" : "false")
        << ",\"may_have_backdrop_filter\":"
        << (node->MayHaveBackdropFilter() ? "true" : "false")
        << ",\"draws_content\":"
        << (node->DrawsContent() ? "true" : "false") << "}";
    ++depth;
    if (node == root) {
      break;
    }
    node = parent;
  }
  out << "]";
  return out.str();
}

std::string ScrollJsonForStandaloneRenderer(const ScrollPaintPropertyNode* scroll) {
  if (!scroll) {
    return "null";
  }
  const auto* parent = scroll->UnaliasedParent();
  std::ostringstream out;
  out << "{\"id\":" << NodeIdForStandaloneRenderer(scroll)
      << ",\"parent_id\":" << NodeIdForStandaloneRenderer(parent)
      << ",\"container_rect\":"
      << RectJsonForStandaloneRenderer(scroll->ContainerRect())
      << ",\"contents_rect\":"
      << RectJsonForStandaloneRenderer(scroll->ContentsRect())
      << ",\"overflow_clip_node_id\":"
      << NodeIdForStandaloneRenderer(scroll->OverflowClipNode())
      << ",\"compositor_element_id\":\"inaccessible\"}";
  return out.str();
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
  int retained_supported_visual_op_count = 0;
  int retained_unsupported_visual_op_count = 0;
  int diagnostic_bitmap_fallback_visual_op_count = 0;
  int text_blob_count = 0;
  int image_count = 0;
  int shader_count = 0;
  int path_count = 0;
  int filter_count = 0;
  int draw_looper_count = 0;
  int draw_looper_layer_count = 0;
  int path_effect_count = 0;
  bool has_non_text_visual_paint = false;
  bool has_non_translation_transform = false;
  bool has_effect_opacity = false;
};

bool IsPaintOpCurrentlyExtracted(cc::PaintOpType type);

int DrawLooperLayerCountForStandaloneRenderer(const cc::PaintFlags& flags) {
  const sk_sp<cc::DrawLooper>& looper = flags.getLooper();
  if (!looper) {
    return 0;
  }
  int count = 0;
  looper->ForEachLayer([&count](SkPoint, float, SkColor4f, uint32_t) {
    ++count;
  });
  return count;
}

void AppendPaintRecordAuditJson(const cc::PaintRecord& record,
                                RawPaintRecordAudit& audit,
                                std::ostringstream* paint_ops_json,
                                bool top_level,
                                int depth = 0,
                                bool* first_paint_op = nullptr) {
  bool local_first_paint_op = true;
  if (!first_paint_op) {
    first_paint_op = &local_first_paint_op;
  }
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
      if (!IsPaintOpCurrentlyExtracted(op.GetType())) {
        ++audit.retained_unsupported_visual_op_count;
      } else if (op.GetType() == cc::PaintOpType::kDrawArc ||
                 op.GetType() == cc::PaintOpType::kDrawArcLite) {
        ++audit.diagnostic_bitmap_fallback_visual_op_count;
      } else {
        ++audit.retained_supported_visual_op_count;
      }
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
    const bool has_path_effect = flags && flags->getPathEffect();
    if (has_path_effect) {
      ++audit.path_effect_count;
    }
    const int draw_looper_layer_count =
        flags ? DrawLooperLayerCountForStandaloneRenderer(*flags) : 0;
    if (draw_looper_layer_count > 0) {
      ++audit.draw_looper_count;
      audit.draw_looper_layer_count += draw_looper_layer_count;
    }

    if (paint_ops_json) {
      if (!*first_paint_op) {
        *paint_ops_json << ",";
      }
      *first_paint_op = false;
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
                      << ",\"has_draw_looper\":"
                      << (draw_looper_layer_count > 0 ? "true" : "false")
                      << ",\"draw_looper_layer_count\":"
                      << draw_looper_layer_count
                      << ",\"has_path_effect\":"
                      << (has_path_effect ? "true" : "false")
                      << ",\"bounds_or_geometry\":"
                      << PaintOpGeometryJsonForStandaloneRenderer(op) << "}";
    }

    if (op.GetType() == cc::PaintOpType::kDrawRecord) {
      AppendPaintRecordAuditJson(
          static_cast<const cc::DrawRecordOp&>(op).record, audit,
          paint_ops_json, false, depth + 1, first_paint_op);
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

std::string ExtractHtmlAttributeForStandaloneRenderer(
    const std::string& tag,
    const std::string& attribute_name);

std::map<std::string, int> ImageSchemeHistogramForStandaloneRenderer(
    const std::string& html) {
  std::map<std::string, int> histogram;
  std::string lower = LowerAsciiForStandaloneRenderer(html);
  size_t offset = 0;
  while (true) {
    const size_t img = lower.find("<img", offset);
    if (img == std::string::npos) {
      break;
    }
    const size_t tag_end = lower.find('>', img);
    const std::string tag =
        html.substr(img, tag_end == std::string::npos ? std::string::npos
                                                      : tag_end - img + 1);
    const std::string src = ExtractHtmlAttributeForStandaloneRenderer(tag, "src");
    const size_t colon = src.find(':');
    const std::string scheme =
        colon == std::string::npos ? std::string("relative_or_empty")
                                   : LowerAsciiForStandaloneRenderer(src.substr(0, colon));
    ++histogram[scheme];
    offset = tag_end == std::string::npos ? html.size() : tag_end + 1;
  }
  return histogram;
}

std::vector<std::string> ImageSrcListForStandaloneRenderer(
    const std::string& html) {
  std::vector<std::string> sources;
  std::string lower = LowerAsciiForStandaloneRenderer(html);
  size_t offset = 0;
  while (true) {
    const size_t img = lower.find("<img", offset);
    if (img == std::string::npos) {
      break;
    }
    const size_t tag_end = lower.find('>', img);
    const std::string tag =
        html.substr(img, tag_end == std::string::npos ? std::string::npos
                                                      : tag_end - img + 1);
    sources.push_back(ExtractHtmlAttributeForStandaloneRenderer(tag, "src"));
    offset = tag_end == std::string::npos ? html.size() : tag_end + 1;
  }
  return sources;
}

void CollectImageReachabilityFromNodeForStandaloneRenderer(
    const Node& node,
    ImageReachabilityDiagnostics& diagnostics) {
  if (const auto* element = DynamicTo<Element>(node)) {
    if (element->HasTagName(html_names::kImgTag)) {
      ++diagnostics.html_image_element_count;
      const AtomicString src =
          element->FastGetAttribute(html_names::kSrcAttr);
      if (!src.empty()) {
        diagnostics.img_src_detected_from_dom = true;
        diagnostics.image_loader_request_url = src.Utf8();
      }
      diagnostics.width_attr =
          BlinkStringToStdStringForStandaloneRenderer(
              element->FastGetAttribute(html_names::kWidthAttr));
      diagnostics.height_attr =
          BlinkStringToStdStringForStandaloneRenderer(
              element->FastGetAttribute(html_names::kHeightAttr));
      if (const ComputedStyle* style = element->GetComputedStyle()) {
        diagnostics.computed_display = static_cast<int>(style->Display());
        diagnostics.computed_visibility =
            static_cast<int>(style->Visibility());
        diagnostics.computed_width = BlinkStringToStdStringForStandaloneRenderer(
            style->LogicalWidth().ToString());
        diagnostics.computed_height =
            BlinkStringToStdStringForStandaloneRenderer(
                style->LogicalHeight().ToString());
      }
      if (const auto* image_element = DynamicTo<HTMLImageElement>(element)) {
        diagnostics.element_natural_width =
            static_cast<int>(image_element->naturalWidth());
        diagnostics.element_natural_height =
            static_cast<int>(image_element->naturalHeight());
        diagnostics.loader_natural_width = diagnostics.element_natural_width;
        diagnostics.loader_natural_height = diagnostics.element_natural_height;
        if (ImageResourceContent* content = image_element->CachedImage()) {
          diagnostics.image_loader_present = true;
          diagnostics.loader_content_present = true;
          diagnostics.loader_content_has_image = content->HasImage();
          diagnostics.loader_content_error = content->ErrorOccurred();
          if (Image* image = content->GetImage()) {
            const gfx::Size resource_size = image->Size(kRespectImageOrientation);
            diagnostics.loader_resource_width = resource_size.width();
            diagnostics.loader_resource_height = resource_size.height();
          }
        }
      }
      if (const LayoutObject* layout_object = element->GetLayoutObject()) {
        diagnostics.layout_object_created = true;
        diagnostics.layout_object_type = layout_object->DebugName().Utf8();
        diagnostics.layout_is_layout_image = layout_object->IsLayoutImage();
        diagnostics.paint_layer_present = layout_object->HasLayer();
        diagnostics.object_paint_properties_present =
            layout_object->FirstFragment().PaintProperties();
        if (const auto* box = DynamicTo<LayoutBox>(layout_object)) {
          diagnostics.layout_is_box = true;
          diagnostics.layout_box_width = box->StitchedSize().width.ToInt();
          diagnostics.layout_box_height = box->StitchedSize().height.ToInt();
          const PhysicalRect content_rect = box->PhysicalContentBoxRect();
          diagnostics.layout_content_width = content_rect.Width().ToInt();
          diagnostics.layout_content_height = content_rect.Height().ToInt();
          const gfx::RectF dom_rect =
              element->GetBoundingClientRectNoLifecycleUpdate();
          diagnostics.layout_viewport_x = static_cast<int>(std::round(dom_rect.x()));
          diagnostics.layout_viewport_y = static_cast<int>(std::round(dom_rect.y()));
          diagnostics.layout_viewport_width =
              static_cast<int>(std::round(dom_rect.width()));
          diagnostics.layout_viewport_height =
              static_cast<int>(std::round(dom_rect.height()));
          diagnostics.physical_fragment_count =
              static_cast<int>(box->PhysicalFragments().Size());
        }
      }
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    CollectImageReachabilityFromNodeForStandaloneRenderer(*child,
                                                          diagnostics);
  }
}

ImageReachabilityDiagnostics CollectImageReachabilityForStandaloneRenderer(
    Document& document,
    const std::string& html) {
  ImageReachabilityDiagnostics diagnostics;
  diagnostics.img_src_detected_from_source_scan =
      !ImageSrcListForStandaloneRenderer(html).empty();
  if (Node* root = document.documentElement()) {
    CollectImageReachabilityFromNodeForStandaloneRenderer(*root, diagnostics);
  }
  diagnostics.image_loader_update_called =
      StandaloneRendererImageResourceContentFetchCalled() > 0;
  diagnostics.layout_image_resource_created =
      StandaloneRendererLayoutImageResourceInitializeCalled() > 0 ||
      StandaloneRendererLayoutImageSetResourceCalled() > 0;
  diagnostics.real_html_image_element_class_linked =
      diagnostics.layout_image_resource_created ||
      diagnostics.layout_object_type.find("LayoutImage") != std::string::npos ||
      StandaloneRendererImageResourceContentFetchCalled() > 0;
  diagnostics.image_loader_present =
      diagnostics.real_html_image_element_class_linked ||
      StandaloneRendererImageResourceContentFetchCalled() > 0;
  char last_url[2048] = {};
  if (StandaloneRendererImageResourceContentFetchLastUrl(
          last_url, static_cast<int>(sizeof(last_url))) > 0) {
    diagnostics.image_loader_request_url = last_url;
  }
  return diagnostics;
}

std::string FirstMissingImageStageForStandaloneRenderer(
    const ImageReachabilityDiagnostics& diagnostics) {
  if (!diagnostics.img_src_detected_from_source_scan) {
    return "no_img_src_in_input";
  }
  if (diagnostics.html_image_element_count == 0) {
    return "html_img_not_present_in_dom";
  }
  if (!diagnostics.img_src_detected_from_dom) {
    return "img_src_not_present_on_dom_element";
  }
  if (!diagnostics.real_html_image_element_class_linked) {
    return "real_HTMLImageElement_class_not_linked";
  }
  if (!diagnostics.image_loader_present) {
    return "ImageLoader_not_present";
  }
  if (!diagnostics.image_loader_update_called) {
    return "ImageLoader_UpdateFromElement_or_ImageResourceContent_Fetch_not_called";
  }
  if (StandaloneRendererImageResourceContentFetchCalled() == 0) {
    return "ImageResourceContent_Fetch_not_called";
  }
  if (StandaloneRendererImageResourceContentFetchCalled() > 0 &&
      StandaloneRendererLayoutImageResourceSetResourceCalled() == 0) {
    return "LayoutImageResource_SetImageResource_not_called";
  }
  if (!diagnostics.layout_object_created) {
    return "LayoutObject_not_created";
  }
  if (!diagnostics.layout_image_resource_created) {
    return "LayoutImageResource_not_created";
  }
  if (StandaloneRendererLayoutImagePaintCalled() == 0) {
    return "LayoutImage_Paint_not_called";
  }
  if (StandaloneRendererLayoutImagePaintReplacedCalled() == 0) {
    return "LayoutImage_PaintReplaced_not_called";
  }
  if (StandaloneRendererImagePainterPaintReplacedCalled() == 0) {
    return "ImagePainter_PaintReplaced_not_called";
  }
  if (StandaloneRendererLayoutImageResourceGetImageCalled() == 0) {
    return "LayoutImageResource_GetImage_not_called";
  }
  if (StandaloneRendererLayoutImageResourceNaturalDimensionsCalled() == 0) {
    return "LayoutImageResource_GetNaturalDimensions_not_called";
  }
  return "none";
}

std::string SchemeForStandaloneRenderer(const std::string& url);
std::vector<std::string> ExtractStyleElementTextForStandaloneRenderer(
    const std::string& html);

std::vector<std::string> CssUrlListForStandaloneRenderer(
    const std::string& html) {
  std::vector<std::string> urls;
  for (const std::string& style :
       ExtractStyleElementTextForStandaloneRenderer(html)) {
    const std::string lower = LowerAsciiForStandaloneRenderer(style);
    size_t offset = 0;
    while (true) {
      const size_t url_pos = lower.find("url(", offset);
      if (url_pos == std::string::npos) {
        break;
      }
      size_t value_start = url_pos + 4;
      while (value_start < style.size() &&
             std::isspace(static_cast<unsigned char>(style[value_start]))) {
        ++value_start;
      }
      char quote = 0;
      if (value_start < style.size() &&
          (style[value_start] == '"' || style[value_start] == '\'')) {
        quote = style[value_start++];
      }
      size_t value_end = value_start;
      while (value_end < style.size()) {
        if (quote != 0 && style[value_end] == quote) {
          break;
        }
        if (quote == 0 && style[value_end] == ')') {
          break;
        }
        ++value_end;
      }
      urls.push_back(style.substr(value_start, value_end - value_start));
      offset = value_end == std::string::npos ? style.size() : value_end + 1;
    }
  }
  return urls;
}

std::map<std::string, int> CssImageSchemeHistogramForStandaloneRenderer(
    const std::string& html) {
  std::map<std::string, int> histogram;
  for (const std::string& url : CssUrlListForStandaloneRenderer(html)) {
    ++histogram[SchemeForStandaloneRenderer(url)];
  }
  return histogram;
}

std::string SchemeForStandaloneRenderer(const std::string& url) {
  const size_t colon = url.find(':');
  if (colon == std::string::npos) {
    return "relative_or_empty";
  }
  return LowerAsciiForStandaloneRenderer(url.substr(0, colon));
}

int EncodedDataBytesForStandaloneRenderer(const std::string& url) {
  if (SchemeForStandaloneRenderer(url) != "data") {
    return 0;
  }
  const size_t comma = url.find(',');
  if (comma == std::string::npos || comma + 1 >= url.size()) {
    return 0;
  }
  return static_cast<int>(url.size() - comma - 1);
}

std::string TruncatedUrlForStandaloneRenderer(const std::string& url) {
  constexpr size_t kMaxUrlForAudit = 96;
  if (url.size() <= kMaxUrlForAudit) {
    return url;
  }
  return url.substr(0, kMaxUrlForAudit) + "...";
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

std::unordered_map<std::string, std::string>
ParseElementAttributesForStandaloneRenderer(const std::string& serialized) {
  std::unordered_map<std::string, std::string> output;
  size_t line_start = 0;
  while (line_start < serialized.size()) {
    size_t line_end = serialized.find('\n', line_start);
    if (line_end == std::string::npos) {
      line_end = serialized.size();
    }
    const std::string line = serialized.substr(line_start, line_end - line_start);
    if (!line.empty()) {
      const size_t equals = line.find('=');
      if (equals != std::string::npos) {
        output[line.substr(0, equals)] = line.substr(equals + 1);
      } else {
        output[line] = std::string();
      }
    }
    line_start = line_end + 1;
  }
  return output;
}

void ApplyElementAttributesForStandaloneRenderer(
    Document& document,
    const std::unordered_map<std::string, std::string>& attributes) {
  for (const auto& [key, value] : attributes) {
    const size_t separator = key.find(':');
    if (separator == std::string::npos || separator == 0 ||
        separator + 1 >= key.size()) {
      continue;
    }
    Element* element =
        document.getElementById(AtomicString(String::FromUtf8(
            key.substr(0, separator))));
    if (!element) {
      continue;
    }
    const AtomicString attribute_name(
        String::FromUtf8(key.substr(separator + 1)));
    if (value.empty()) {
      element->removeAttribute(attribute_name);
    } else {
      element->setAttribute(attribute_name, AtomicString(String::FromUtf8(value)));
    }
  }
}

Element* ElementByIdForStandaloneRenderer(Document& document,
                                          const std::string& element_id) {
  if (element_id.empty()) {
    return nullptr;
  }
  return document.getElementById(
      AtomicString(String::FromUtf8(element_id)));
}

bool ParseStandaloneFloat(const std::string& value, float* output) {
  char* end = nullptr;
  const float parsed = std::strtof(value.c_str(), &end);
  if (end == value.c_str() || *end != '\0') {
    return false;
  }
  *output = parsed;
  return true;
}

std::unordered_map<std::string, LiveElementScrollOffset>
ParseElementScrollOffsetsForStandaloneRenderer(
    const std::string& serialized) {
  std::unordered_map<std::string, LiveElementScrollOffset> output;
  size_t line_start = 0;
  while (line_start < serialized.size()) {
    size_t line_end = serialized.find('\n', line_start);
    if (line_end == std::string::npos) {
      line_end = serialized.size();
    }
    const std::string line =
        serialized.substr(line_start, line_end - line_start);
    if (!line.empty()) {
      const size_t equals = line.find('=');
      const size_t comma =
          equals == std::string::npos ? std::string::npos
                                      : line.find(',', equals + 1);
      float x = 0.0f;
      float y = 0.0f;
      if (equals != std::string::npos && comma != std::string::npos &&
          equals > 0 &&
          ParseStandaloneFloat(line.substr(equals + 1, comma - equals - 1),
                               &x) &&
          ParseStandaloneFloat(line.substr(comma + 1), &y)) {
        output[line.substr(0, equals)] = LiveElementScrollOffset{x, y};
      }
    }
    line_start = line_end + 1;
  }
  return output;
}

void ApplyElementScrollOffsetsForStandaloneRenderer(Document& document) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.element_scroll_diagnostics.clear();
  cache.element_scroll_offset_applied = false;
  cache.element_scroll_offset_changed = false;
  cache.element_scroll_offset_requested =
      !cache.requested_element_scroll_offsets_by_id.empty();
  if (!cache.element_scroll_offset_requested) {
    return;
  }

  std::vector<std::pair<std::string, LiveElementScrollOffset>> ordered(
      cache.requested_element_scroll_offsets_by_id.begin(),
      cache.requested_element_scroll_offsets_by_id.end());
  std::sort(ordered.begin(), ordered.end(),
            [](const auto& lhs, const auto& rhs) {
              return lhs.first < rhs.first;
            });

  for (const auto& [element_id, requested] : ordered) {
    LiveElementScrollDiagnostic diagnostic;
    diagnostic.element_id = element_id;
    diagnostic.requested_x = requested.x;
    diagnostic.requested_y = requested.y;
    diagnostic.status = "requested";

    Element* element = ElementByIdForStandaloneRenderer(document, element_id);
    if (!element) {
      diagnostic.status = "element_not_found";
      cache.element_scroll_diagnostics.push_back(std::move(diagnostic));
      continue;
    }
    diagnostic.element_present = true;

    auto* box = DynamicTo<LayoutBox>(element->GetLayoutObject());
    if (!box) {
      diagnostic.status = "layout_box_missing";
      cache.element_scroll_diagnostics.push_back(std::move(diagnostic));
      continue;
    }
    diagnostic.layout_box_present = true;

    PaintLayer* layer = box->EnclosingLayer();
    PaintLayerScrollableArea* scrollable_area =
        box->GetScrollableArea()
            ? box->GetScrollableArea()
            : (layer ? layer->GetScrollableArea() : nullptr);
    if (!scrollable_area) {
      diagnostic.status = "scrollable_area_missing";
      cache.element_scroll_diagnostics.push_back(std::move(diagnostic));
      continue;
    }
    diagnostic.scrollable_area_present = true;
    scrollable_area->UpdateAfterOverflowRecalc();

    const ScrollOffset maximum = scrollable_area->MaximumScrollOffset();
    diagnostic.max_x = maximum.x();
    diagnostic.max_y = maximum.y();
    const gfx::Size contents_size = scrollable_area->ContentsSize();
    diagnostic.contents_width = contents_size.width();
    diagnostic.contents_height = contents_size.height();
    const gfx::Rect visible_rect =
        scrollable_area->VisibleContentRect(kExcludeScrollbars);
    diagnostic.visible_width = visible_rect.width();
    diagnostic.visible_height = visible_rect.height();

    const ScrollOffset requested_offset =
        scrollable_area->ScrollPositionToOffset(
            gfx::PointF(requested.x, requested.y));
    const ScrollOffset clamped_offset =
        scrollable_area->ClampScrollOffset(requested_offset);
    diagnostic.changed = scrollable_area->SetScrollOffset(
        clamped_offset, mojom::blink::ScrollType::kProgrammatic,
        cc::ScrollSourceType::kAbsoluteScroll,
        mojom::blink::ScrollBehavior::kInstant);
    const gfx::PointF applied_position = scrollable_area->ScrollPosition();
    diagnostic.applied_x = applied_position.x();
    diagnostic.applied_y = applied_position.y();
    diagnostic.status = "applied_to_element_scrollable_area";
    cache.element_scroll_offset_applied = true;
    cache.element_scroll_offset_changed =
        cache.element_scroll_offset_changed || diagnostic.changed;
    cache.element_scroll_diagnostics.push_back(std::move(diagnostic));
  }
}

std::string ElementScrollDiagnosticsJsonForStandaloneRenderer(
    const LiveFramePaintProbeCache& cache) {
  std::ostringstream json;
  json << "{\"requested_count\":"
       << cache.requested_element_scroll_offsets_by_id.size()
       << ",\"requested_non_empty\":"
       << (cache.element_scroll_offset_requested ? "true" : "false")
       << ",\"applied_to_blink\":"
       << (cache.element_scroll_offset_applied ? "true" : "false")
       << ",\"changed\":"
       << (cache.element_scroll_offset_changed ? "true" : "false")
       << ",\"entries\":[";
  for (size_t i = 0; i < cache.element_scroll_diagnostics.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    const LiveElementScrollDiagnostic& diagnostic =
        cache.element_scroll_diagnostics[i];
    json << "{\"element_id\":"
         << JsonStringForStandaloneRenderer(diagnostic.element_id)
         << ",\"requested\":{\"x\":" << diagnostic.requested_x
         << ",\"y\":" << diagnostic.requested_y << "}"
         << ",\"applied\":{\"x\":" << diagnostic.applied_x
         << ",\"y\":" << diagnostic.applied_y << "}"
         << ",\"maximum\":{\"x\":" << diagnostic.max_x
         << ",\"y\":" << diagnostic.max_y << "}"
         << ",\"contents_size\":{\"width\":" << diagnostic.contents_width
         << ",\"height\":" << diagnostic.contents_height << "}"
         << ",\"visible_size\":{\"width\":" << diagnostic.visible_width
         << ",\"height\":" << diagnostic.visible_height << "}"
         << ",\"element_present\":"
         << (diagnostic.element_present ? "true" : "false")
         << ",\"layout_box_present\":"
         << (diagnostic.layout_box_present ? "true" : "false")
         << ",\"scrollable_area_present\":"
         << (diagnostic.scrollable_area_present ? "true" : "false")
         << ",\"changed\":"
         << (diagnostic.changed ? "true" : "false")
         << ",\"status\":"
         << JsonStringForStandaloneRenderer(diagnostic.status) << "}";
  }
  json << "]}";
  return json.str();
}

std::string ScrollableElementEntriesJsonForStandaloneRenderer(
    const LiveFramePaintProbeCache& cache) {
  std::ostringstream json;
  json << "[";
  for (size_t i = 0; i < cache.scrollable_element_entries.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    const LiveScrollableElementEntry& entry =
        cache.scrollable_element_entries[i];
    json << "{\"element_id\":"
         << JsonStringForStandaloneRenderer(entry.element_id)
         << ",\"bounds\":{\"x\":" << entry.x << ",\"y\":" << entry.y
         << ",\"width\":" << entry.width << ",\"height\":" << entry.height
         << "},\"scroll_offset\":{\"x\":" << entry.scroll_x
         << ",\"y\":" << entry.scroll_y
         << "},\"max_scroll_offset\":{\"x\":" << entry.max_scroll_x
         << ",\"y\":" << entry.max_scroll_y
         << "},\"can_scroll_x\":"
         << (entry.can_scroll_x ? "true" : "false")
         << ",\"can_scroll_y\":"
         << (entry.can_scroll_y ? "true" : "false")
         << ",\"paint_order\":" << entry.paint_order << "}";
  }
  json << "]";
  return json.str();
}

void ApplyInteractionStateForStandaloneRenderer(
    Document& document,
    const std::string& hovered_element_id,
    const std::string& active_element_id) {
  document.UpdateHoverActiveState(/*is_active=*/false,
                                  /*update_active_chain=*/true, nullptr);

  Element* active_element =
      ElementByIdForStandaloneRenderer(document, active_element_id);
  Element* hovered_element =
      ElementByIdForStandaloneRenderer(document, hovered_element_id);

  if (active_element) {
    document.UpdateHoverActiveState(/*is_active=*/true,
                                    /*update_active_chain=*/true,
                                    active_element);
    if (hovered_element && hovered_element != active_element) {
      document.UpdateHoverActiveState(/*is_active=*/true,
                                      /*update_active_chain=*/false,
                                      hovered_element);
    }
    return;
  }

  if (hovered_element) {
    document.UpdateHoverActiveState(/*is_active=*/false,
                                    /*update_active_chain=*/false,
                                    hovered_element);
  }
}

void ApplyAnimationTimeForStandaloneRenderer(Document& document) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.animation_time_requested) {
    return;
  }

  const base::TimeTicks animation_time =
      document.Timeline().CalculateZeroTime() +
      base::Milliseconds(cache.requested_animation_time_ms);
  document.GetAnimationClock().SetAllowedToDynamicallyUpdateTime(false);
  document.GetAnimationClock().UpdateTime(animation_time);
  document.GetDocumentAnimations().UpdateAnimationTimingForAnimationFrame();
  for (Animation* animation : document.Timeline().GetAnimations()) {
    if (animation) {
      animation->Update(kTimingUpdateForAnimationFrame);
    }
  }
  cache.applied_animation_time_ms = cache.requested_animation_time_ms;
  cache.animation_time_applied = true;
  cache.animation_time_status = "applied_to_document_animation_clock";
}

bool UpdateLifecycleToLayoutCleanForStandaloneRenderer(
    LocalFrameView& frame_view,
    DocumentUpdateReason reason) {
  Document* document = frame_view.GetFrame().GetDocument();
  if (!document) {
    return frame_view.UpdateLifecycleToLayoutClean(reason);
  }

  bool reached_layout_clean = false;
  PostStyleUpdateScope post_style_update_scope(*document);
  do {
    reached_layout_clean =
        frame_view.UpdateLifecycleToLayoutClean(reason) ||
        reached_layout_clean;
  } while (post_style_update_scope.Apply());
  return reached_layout_clean;
}

bool UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
    LocalFrameView& frame_view,
    DocumentUpdateReason reason) {
  Document* document = frame_view.GetFrame().GetDocument();
  if (!document) {
    return frame_view.UpdateAllLifecyclePhasesExceptPaint(reason);
  }

  bool reached_prepaint_clean = false;
  PostStyleUpdateScope post_style_update_scope(*document);
  do {
    reached_prepaint_clean =
        frame_view.UpdateAllLifecyclePhasesExceptPaint(reason) ||
        reached_prepaint_clean;
  } while (post_style_update_scope.Apply());
  return reached_prepaint_clean;
}

bool UpdateAllLifecyclePhasesForTestForStandaloneRenderer(
    LocalFrameView& frame_view) {
  Document* document = frame_view.GetFrame().GetDocument();
  if (!document) {
    return frame_view.UpdateAllLifecyclePhasesForTest();
  }

  bool reached_paint_clean = false;
  PostStyleUpdateScope post_style_update_scope(*document);
  do {
    reached_paint_clean =
        frame_view.UpdateAllLifecyclePhasesForTest() || reached_paint_clean;
  } while (post_style_update_scope.Apply());
  return reached_paint_clean;
}

void ExecutePendingStickyUpdatesForStandaloneRenderer(
    LocalFrameView& frame_view) {
  frame_view.ExecutePendingStickyUpdates();
}

void UpdateStickyConstraintsForScrollableAreaForStandaloneRenderer(
    PaintLayerScrollableArea* scrollable_area) {
  if (!scrollable_area) {
    return;
  }
  LiveFramePaintProbeCache& cache = ProbeCache();
  ++cache.sticky_update_scroll_area_count;
  scrollable_area->UpdateAfterOverflowRecalc();
  scrollable_area->UpdateAllStickyConstraints();
  if (LayoutBox* layout_box = scrollable_area->GetLayoutBox()) {
    for (const auto& fragment : layout_box->PhysicalFragments()) {
      for (const auto& item : fragment.StickyDescendants()) {
        if (auto* sticky_descendant = item.GetIfConsumed()) {
          ++cache.sticky_update_consumed_descendant_count;
          if (item.ConsumedAxes() & kPhysicalAxesHorizontal) {
            ++cache.sticky_update_consumed_horizontal_count;
          }
          if (item.ConsumedAxes() & kPhysicalAxesVertical) {
            ++cache.sticky_update_consumed_vertical_count;
          }
          if (sticky_descendant->HasStickyConstraints()) {
            ++cache.sticky_update_constrained_after_count;
          }
        }
      }
    }
  }
}

void UpdateStickyConstraintsForNodeTreeForStandaloneRenderer(Node* node) {
  if (!node) {
    return;
  }
  if (auto* element = DynamicTo<Element>(node)) {
    if (auto* box = DynamicTo<LayoutBox>(element->GetLayoutObject())) {
      UpdateStickyConstraintsForScrollableAreaForStandaloneRenderer(
          box->GetScrollableArea());
    }
  }
  for (Node* child = node->firstChild(); child; child = child->nextSibling()) {
    UpdateStickyConstraintsForNodeTreeForStandaloneRenderer(child);
  }
}

void UpdateStickyConstraintsForStandaloneRenderer(LocalFrameView& frame_view,
                                                  Document& document) {
  ExecutePendingStickyUpdatesForStandaloneRenderer(frame_view);
  if (LayoutView* layout_view = frame_view.GetLayoutView()) {
    UpdateStickyConstraintsForScrollableAreaForStandaloneRenderer(
        layout_view->GetScrollableArea());
  }
  UpdateStickyConstraintsForNodeTreeForStandaloneRenderer(&document);
}

std::string AnimationRuntimeDiagnosticsJsonForStandaloneRenderer(
    const std::string& body_html,
    const LiveFramePaintProbeCache& cache) {
  const std::string lower_html = LowerAsciiForStandaloneRenderer(body_html);
  const int keyframes_count =
      CountLowercaseTokenForStandaloneRenderer(lower_html, "@keyframes");
  const int animation_declaration_count =
      CountLowercaseTokenForStandaloneRenderer(lower_html, "animation:");
  const int transition_declaration_count =
      CountLowercaseTokenForStandaloneRenderer(lower_html, "transition:");
  const int request_animation_frame_count =
      CountLowercaseTokenForStandaloneRenderer(lower_html,
                                               "requestanimationframe");
  const bool has_css_animation =
      keyframes_count > 0 || animation_declaration_count > 0;
  const bool css_animation_update_stubbed =
      has_css_animation &&
      g_standalone_css_animation_update_called > 0;
  std::string first_missing_stage;
  if (has_css_animation && css_animation_update_stubbed) {
    first_missing_stage =
        "real_css_animations_calculate_animation_update_not_linked";
  } else if (transition_declaration_count > 0 &&
             g_standalone_css_transition_update_called > 0) {
    first_missing_stage =
        "real_css_animations_calculate_transition_update_not_linked";
  } else if (has_css_animation && cache.animation_time_requested &&
             !cache.animation_time_applied) {
    first_missing_stage = "animation_time_not_applied";
  } else if (request_animation_frame_count > 0) {
    first_missing_stage = "scripted_animation_runtime_not_supported";
  }
  std::ostringstream json;
  json << "{\"source_counts\":{\"keyframes\":" << keyframes_count
       << ",\"animation_declarations\":" << animation_declaration_count
       << ",\"transition_declarations\":" << transition_declaration_count
       << ",\"request_animation_frame_calls\":"
       << request_animation_frame_count << "}"
       << ",\"stub_counters\":{\"css_timeline_update\":"
       << g_standalone_css_animation_timeline_update_called
       << ",\"css_animation_update\":"
       << g_standalone_css_animation_update_called
       << ",\"css_transition_update\":"
       << g_standalone_css_transition_update_called
       << ",\"document_animations_update\":"
       << g_standalone_document_animations_update_called
       << ",\"page_animator_service\":"
       << g_standalone_page_animator_service_called << "}"
       << ",\"real_css_animation_update_linked\":true"
       << ",\"real_document_timeline_linked\":true"
       << ",\"real_page_animator_linked\":false"
       << ",\"css_animation_creation_status\":"
       << JsonStringForStandaloneRenderer(
              has_css_animation ? "linked_main_thread_css_animation_path"
                                : "not_requested")
       << ",\"css_transition_creation_status\":"
       << JsonStringForStandaloneRenderer(
              transition_declaration_count > 0
                  ? "linked_main_thread_css_transition_path"
                  : "not_requested")
       << ",\"first_missing_stage\":"
       << JsonStringForStandaloneRenderer(first_missing_stage) << "}";
  return json.str();
}

void BuildPaintArtifactAudit(const PaintArtifact& artifact,
                             LiveFramePaintProbeCache& cache) {
  TraceLiveFrameProbeStage("paint audit begin");
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  TraceLiveFrameProbeStage("paint audit before chunks/items");
  const PaintChunks& chunks = artifact.GetPaintChunks();
  const DisplayItemList& items = artifact.GetDisplayItemList();
  const wtf_size_t chunk_count = chunks.size();
  const wtf_size_t display_item_count = items.size();
  TraceLiveFrameProbeStage("paint audit after chunks/items");
  cache.artifact_audit_lines.push_back(
      "paint_artifact_audit summary chunks=" + std::to_string(chunk_count) +
      " display_items=" + std::to_string(display_item_count));

  std::map<std::string, int> total_op_histogram;
  std::map<std::string, int> total_recursive_op_histogram;
  std::map<std::string, int> total_unsupported_histogram;
  std::map<std::string, int> total_fallback_histogram;
  int total_op_count = 0;
  int total_recursive_op_count = 0;
  int total_drawing_item_count = 0;
  int total_non_drawing_item_count = 0;
  RawPaintRecordAudit total_raw_audit;
  bool total_has_clip_state = false;
  int effect_opacity_chunk_count = 0;
  int grouped_opacity_layer_count = 0;
  int nested_opacity_chunk_count = 0;
  int effect_opacity_chunk_with_clip_count = 0;
  const bool artifact_audit_safe_mode = false;
  std::ostringstream chunks_json;
  chunks_json << "[";
  for (wtf_size_t chunk_index = 0; chunk_index < chunk_count; ++chunk_index) {
    TraceLiveFrameProbeStagef("paint audit before chunk %lu", chunk_index);
    const PaintChunk& chunk = chunks[chunk_index];
    TraceLiveFrameProbeStagef("paint audit after chunk %lu", chunk_index);
    const wtf_size_t chunk_begin_index = chunk.begin_index;
    const wtf_size_t chunk_end_index = chunk.end_index;
    if (chunk_begin_index == chunk_end_index) {
      if (chunk_index > 0) {
        chunks_json << ",";
      }
      const std::string empty_chunk_id =
          BlinkStringToStdStringForStandaloneRenderer(chunk.id.ToString());
      if (cache.chunk_stable_keys.size() <= chunk_index) {
        cache.chunk_stable_keys.resize(chunk_index + 1);
        cache.chunk_id_strings.resize(chunk_index + 1);
      }
      const std::string empty_stable_key =
          !empty_chunk_id.empty()
              ? "blink-chunk:id=" + empty_chunk_id + ":empty"
              : "blink-chunk:empty:debug-index=" +
                    std::to_string(chunk_index);
      cache.chunk_stable_keys[chunk_index] = empty_stable_key;
      cache.chunk_id_strings[chunk_index] = empty_chunk_id;
      const gfx::Rect empty_chunk_bounds = chunk.bounds;
      const gfx::Rect empty_chunk_drawable_bounds = chunk.drawable_bounds;
      chunks_json << "{\"index\":" << chunk_index << ",\"paint_chunk_id\":"
                  << JsonStringForStandaloneRenderer(empty_chunk_id)
                  << ",\"stable_key\":"
                  << JsonStringForStandaloneRenderer(empty_stable_key)
                  << ",\"begin_index\":" << chunk_begin_index
                  << ",\"end_index\":" << chunk_end_index
                  << ",\"bounds\":"
                  << RectJsonForStandaloneRenderer(empty_chunk_bounds)
                  << ",\"drawable_bounds\":"
                  << RectJsonForStandaloneRenderer(empty_chunk_drawable_bounds)
                  << ",\"empty\":true"
                  << ",\"metadata_warnings\":["
                  << "{\"field\":\"display_items\",\"status\":\"empty\","
                  << "\"reason\":\"PaintChunk has an empty display item range; "
                     "bounds are exported but there is no PaintRecord to audit\"}],"
                  << "\"property_state\":{\"status\":\"not_collected\","
                  << "\"reason\":\"empty PaintChunk has no display item or "
                     "PaintOp evidence; chunk bounds remain exported\"}"
                  << ",\"op_histogram\":{},\"recursive_op_histogram\":{}"
                  << ",\"unsupported_ops\":{},\"fallback_rasterized_ops\":{}"
                  << ",\"display_items\":[]}";
      cache.artifact_audit_lines.push_back(
          "paint_artifact_audit chunk index=" + std::to_string(chunk_index) +
          " empty display_range=[" + std::to_string(chunk_begin_index) + "," +
          std::to_string(chunk_end_index) + ")");
      continue;
    }
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

    TraceLiveFrameProbeStagef("paint audit before chunk begin index %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit after chunk begin index %lu %lu",
                              chunk_index, chunk_begin_index);
    TraceLiveFrameProbeStagef("paint audit before chunk end index %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit after chunk end index %lu %lu",
                              chunk_index, chunk_end_index);
    TraceLiveFrameProbeStagef("paint audit before item loop %lu", chunk_index);
    for (wtf_size_t item_index = chunk_begin_index;
         item_index < chunk_end_index && item_index < display_item_count;
         ++item_index) {
      TraceLiveFrameProbeStagef("paint audit before item %lu %lu", chunk_index,
                                item_index);
      const DisplayItem& item = items[item_index];
      TraceLiveFrameProbeStagef("paint audit after item %lu %lu", chunk_index,
                                item_index);
      if (!first_display_item) {
        display_items_json << ",";
      }
      first_display_item = false;
      TraceLiveFrameProbeStagef("paint audit before item id %lu %lu",
                                chunk_index, item_index);
      const std::string item_id =
          BlinkStringToStdStringForStandaloneRenderer(item.GetId().ToString());
      TraceLiveFrameProbeStagef("paint audit after item id %lu %lu",
                                chunk_index, item_index);
      TraceLiveFrameProbeStagef("paint audit before item type %lu %lu",
                                chunk_index, item_index);
      const std::string item_type =
          std::to_string(static_cast<int>(item.GetType()));
      TraceLiveFrameProbeStagef("paint audit after item type %lu %lu",
                                chunk_index, item_index);
      TraceLiveFrameProbeStagef("paint audit before item visual rect %lu %lu",
                                chunk_index, item_index);
      const gfx::Rect item_visual_rect = item.VisualRect();
      TraceLiveFrameProbeStagef("paint audit after item visual rect %lu %lu",
                                chunk_index, item_index);
      TraceLiveFrameProbeStagef("paint audit before item is_drawing %lu %lu",
                                chunk_index, item_index);
      const bool item_is_drawing = item.IsDrawing();
      TraceLiveFrameProbeStagef("paint audit after item is_drawing %lu %lu",
                                chunk_index, item_index);
      display_items_json << "{\"index\":" << item_index << ",\"id\":"
                         << JsonStringForStandaloneRenderer(item_id)
                         << ",\"type\":"
                         << JsonStringForStandaloneRenderer(item_type)
                         << ",\"client_debug_name\":null"
                         << ",\"client_owner_node_id\":null"
                         << ",\"visual_rect\":"
                         << RectJsonForStandaloneRenderer(item_visual_rect)
                         << ",\"is_drawing\":"
                         << (item_is_drawing ? "true" : "false");
      if (!item_is_drawing) {
        ++non_drawing_item_count;
        display_items_json
            << ",\"paint_record_op_histogram\":{},\"recursive_paint_record_op_histogram\":{},\"paint_ops\":[]}";
        continue;
      }
      ++drawing_item_count;
      TraceLiveFrameProbeStagef("paint audit before dynamic drawing %lu %lu",
                                chunk_index, item_index);
      const auto* drawing = DynamicTo<DrawingDisplayItem>(item);
      TraceLiveFrameProbeStagef("paint audit after dynamic drawing %lu %lu",
                                chunk_index, item_index);
      if (!drawing) {
        display_items_json
            << ",\"paint_record_op_histogram\":{},\"recursive_paint_record_op_histogram\":{},\"paint_ops\":[]}";
        continue;
      }
      RawPaintRecordAudit item_audit;
      std::ostringstream paint_ops_json;
      paint_ops_json << "[";
      TraceLiveFrameProbeStagef("paint audit before paint record %lu %lu",
                                chunk_index, item_index);
      AppendPaintRecordAuditJson(drawing->GetPaintRecord(), item_audit,
                                 &paint_ops_json, true);
      TraceLiveFrameProbeStagef("paint audit after paint record %lu %lu",
                                chunk_index, item_index);
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
      chunk_raw_audit.retained_supported_visual_op_count +=
          item_audit.retained_supported_visual_op_count;
      chunk_raw_audit.retained_unsupported_visual_op_count +=
          item_audit.retained_unsupported_visual_op_count;
      chunk_raw_audit.diagnostic_bitmap_fallback_visual_op_count +=
          item_audit.diagnostic_bitmap_fallback_visual_op_count;
      chunk_raw_audit.text_blob_count += item_audit.text_blob_count;
      chunk_raw_audit.image_count += item_audit.image_count;
      chunk_raw_audit.shader_count += item_audit.shader_count;
      chunk_raw_audit.path_count += item_audit.path_count;
      chunk_raw_audit.filter_count += item_audit.filter_count;
      chunk_raw_audit.draw_looper_count += item_audit.draw_looper_count;
      chunk_raw_audit.draw_looper_layer_count +=
          item_audit.draw_looper_layer_count;
      chunk_raw_audit.path_effect_count += item_audit.path_effect_count;
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
    TraceLiveFrameProbeStagef("paint audit after item loop %lu", chunk_index);
    display_items_json << "]";
    TraceLiveFrameProbeStagef("paint audit after display items json %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before total histograms %lu",
                              chunk_index);
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
    total_raw_audit.retained_supported_visual_op_count +=
        chunk_raw_audit.retained_supported_visual_op_count;
    total_raw_audit.retained_unsupported_visual_op_count +=
        chunk_raw_audit.retained_unsupported_visual_op_count;
    total_raw_audit.diagnostic_bitmap_fallback_visual_op_count +=
        chunk_raw_audit.diagnostic_bitmap_fallback_visual_op_count;
    total_raw_audit.text_blob_count += chunk_raw_audit.text_blob_count;
    total_raw_audit.image_count += chunk_raw_audit.image_count;
    total_raw_audit.shader_count += chunk_raw_audit.shader_count;
    total_raw_audit.path_count += chunk_raw_audit.path_count;
    total_raw_audit.filter_count += chunk_raw_audit.filter_count;
    total_raw_audit.draw_looper_count += chunk_raw_audit.draw_looper_count;
    total_raw_audit.draw_looper_layer_count +=
        chunk_raw_audit.draw_looper_layer_count;
    total_raw_audit.path_effect_count += chunk_raw_audit.path_effect_count;
    total_raw_audit.has_non_text_visual_paint |=
        chunk_raw_audit.has_non_text_visual_paint;
    total_raw_audit.has_non_translation_transform |=
        chunk_raw_audit.has_non_translation_transform;
    total_raw_audit.has_effect_opacity |= chunk_raw_audit.has_effect_opacity;
    TraceLiveFrameProbeStagef("paint audit after total histograms %lu",
                              chunk_index);

    if (chunk_index > 0) {
      chunks_json << ",";
    }
    TraceLiveFrameProbeStagef("paint audit before chunk id %lu", chunk_index);
    const std::string chunk_id =
        BlinkStringToStdStringForStandaloneRenderer(chunk.id.ToString());
    TraceLiveFrameProbeStagef("paint audit after chunk id %lu", chunk_index);
    TraceLiveFrameProbeStagef("paint audit before chunk state %lu",
                              chunk_index);
    const PropertyTreeState chunk_state = chunk.properties.Unalias();
    TraceLiveFrameProbeStagef("paint audit after chunk state %lu",
                              chunk_index);
    uint32_t transform_chain_depth = 0;
    bool projection_has_non_translation = false;
    TraceLiveFrameProbeStagef("paint audit before transform projection %lu",
                              chunk_index);
    gfx::Transform projection = DirectTransformToRootForStandaloneRenderer(
        chunk_state, &transform_chain_depth, &projection_has_non_translation);
    TraceLiveFrameProbeStagef("paint audit after transform projection %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before clip depth %lu",
                              chunk_index);
    const uint32_t clip_chain_depth =
        projection_has_non_translation
            ? 0
            : ClipChainDepthForStandaloneRenderer(chunk_state.Clip());
    TraceLiveFrameProbeStagef("paint audit after clip depth %lu", chunk_index);
    TraceLiveFrameProbeStagef("paint audit before effect depth %lu",
                              chunk_index);
    const uint32_t effect_chain_depth =
        EffectChainDepthForStandaloneRenderer(chunk_state.Effect());
    TraceLiveFrameProbeStagef("paint audit after effect depth %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before effect opacity %lu",
                              chunk_index);
    const float effect_opacity = chunk_state.Effect().Opacity();
    TraceLiveFrameProbeStagef("paint audit after effect opacity %lu",
                              chunk_index);
    if (effect_opacity != 1.0f) {
      chunk_raw_audit.has_effect_opacity = true;
      total_raw_audit.has_effect_opacity = true;
      ++effect_opacity_chunk_count;
      ++grouped_opacity_layer_count;
      if (effect_chain_depth > 1) {
        ++nested_opacity_chunk_count;
      }
    }
    TraceLiveFrameProbeStagef("paint audit before clip metadata %lu",
                              chunk_index);
    const bool clip_has_path = chunk_state.Clip().ClipPath().has_value();
    const bool clip_paint_rect_rounded =
        chunk_state.Clip().PaintClipRect().IsRounded();
    const bool clip_layout_rect_has_radius =
        chunk_state.Clip().LayoutClipRect().HasRadius();
    TraceLiveFrameProbeStagef("paint audit after clip metadata %lu",
                              chunk_index);
    if (projection_has_non_translation) {
      chunk_raw_audit.has_non_translation_transform = true;
      total_raw_audit.has_non_translation_transform = true;
    }
    if (!projection_has_non_translation &&
        (clip_chain_depth > 0 || clip_has_path || clip_paint_rect_rounded ||
         clip_layout_rect_has_radius)) {
      total_has_clip_state = true;
      if (effect_opacity != 1.0f) {
        ++effect_opacity_chunk_with_clip_count;
      }
    }
    const bool has_projection = true;
    std::optional<FloatClipRect> clip;
    if (!projection_has_non_translation) {
      TraceLiveFrameProbeStagef("paint audit before local clip rect %lu",
                                chunk_index);
      clip = GeometryMapper::LocalToAncestorClipRect(
          chunk_state, PropertyTreeState::Root());
      TraceLiveFrameProbeStagef("paint audit after local clip rect %lu",
                                chunk_index);
    }
    TraceLiveFrameProbeStagef("paint audit before property fingerprint %lu",
                              chunk_index);
    const std::string property_fingerprint =
        chunk_id + ":" + std::to_string(chunk.begin_index) + ":" +
        std::to_string(chunk.end_index) + ":" +
        (has_projection ? MatrixJsonForStandaloneRenderer(projection) : "");
    TraceLiveFrameProbeStagef("paint audit after property fingerprint %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before property hash %lu",
                              chunk_index);
    const uint64_t property_hash =
        HashStringForStandaloneRenderer(property_fingerprint);
    TraceLiveFrameProbeStagef("paint audit after property hash %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before stable key %lu",
                              chunk_index);
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
    TraceLiveFrameProbeStagef("paint audit after stable key %lu", chunk_index);
    TraceLiveFrameProbeStagef("paint audit before cache resize %lu",
                              chunk_index);
    if (cache.chunk_stable_keys.size() <= chunk_index) {
      cache.chunk_stable_keys.resize(chunk_index + 1);
      cache.chunk_id_strings.resize(chunk_index + 1);
    }
    cache.chunk_stable_keys[chunk_index] = stable_key;
    cache.chunk_id_strings[chunk_index] = chunk_id;
    TraceLiveFrameProbeStagef("paint audit after cache resize %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before chunk bounds %lu",
                              chunk_index);
    const gfx::Rect chunk_bounds = chunk.bounds;
    TraceLiveFrameProbeStagef("paint audit after chunk bounds %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before chunk drawable bounds %lu",
                              chunk_index);
    const gfx::Rect chunk_drawable_bounds = chunk.drawable_bounds;
    TraceLiveFrameProbeStagef("paint audit after chunk drawable bounds %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before chunk flags %lu",
                              chunk_index);
    const bool chunk_has_text = chunk.has_text;
    const bool chunk_is_cacheable = chunk.is_cacheable;
    TraceLiveFrameProbeStagef("paint audit after chunk flags %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before can match old chunk %lu",
                              chunk_index);
    const bool chunk_can_match_old = chunk.CanMatchOldChunk();
    TraceLiveFrameProbeStagef("paint audit after can match old chunk %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before chunk json strings %lu",
                              chunk_index);
    const std::string chunk_id_json =
        JsonStringForStandaloneRenderer(chunk_id);
    const std::string stable_key_json =
        JsonStringForStandaloneRenderer(stable_key);
    const std::string chunk_bounds_json =
        RectJsonForStandaloneRenderer(chunk_bounds);
    const std::string chunk_drawable_bounds_json =
        RectJsonForStandaloneRenderer(chunk_drawable_bounds);
    const std::string projection_json =
        has_projection ? MatrixJsonForStandaloneRenderer(projection) : "null";
    const std::string clip_json =
        clip && !clip->IsInfinite()
            ? RectFJsonForStandaloneRenderer(clip->Rect())
            : "null";
    TraceLiveFrameProbeStagef("paint audit before tree chain json %lu",
                              chunk_index);
    const std::string transform_chain_json =
        projection_has_non_translation
            ? "[{\"status\":\"isolated\",\"reason\":\"transform chain under transformed overflow crash reducer is summarized in property_state only\"}]"
            : TransformChainJsonForStandaloneRenderer(chunk_state.Transform());
    TraceLiveFrameProbeStagef("paint audit after transform chain json %lu",
                              chunk_index);
    const std::string clip_chain_json =
        projection_has_non_translation
            ? "[{\"status\":\"inaccessible\",\"reason\":\"clip chain detail under non-translation transform is isolated because current Blink standalone probe crashes while walking transformed overflow clip state\"}]"
            : ClipChainJsonForStandaloneRenderer(chunk_state.Clip());
    TraceLiveFrameProbeStagef("paint audit after clip chain json %lu",
                              chunk_index);
    const std::string effect_chain_json =
        projection_has_non_translation
            ? "[{\"status\":\"isolated\",\"reason\":\"effect chain under transformed overflow crash reducer is summarized in property_state only\"}]"
            : EffectChainJsonForStandaloneRenderer(chunk_state.Effect());
    TraceLiveFrameProbeStagef("paint audit after effect chain json %lu",
                              chunk_index);
    const std::string scroll_json =
        ScrollJsonForStandaloneRenderer(chunk_state.Transform().ScrollNode());
    TraceLiveFrameProbeStagef("paint audit after scroll json %lu",
                              chunk_index);
    const std::string chunk_op_histogram_json =
        MapToJsonObject(chunk_op_histogram);
    const std::string chunk_recursive_op_histogram_json =
        MapToJsonObject(chunk_recursive_op_histogram);
    const std::string chunk_unsupported_histogram_json =
        MapToJsonObject(chunk_unsupported_histogram);
    const std::string chunk_fallback_histogram_json =
        MapToJsonObject(chunk_fallback_histogram);
    const std::string display_items_json_string = display_items_json.str();
    TraceLiveFrameProbeStagef("paint audit after remaining chunk json strings %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit after chunk json strings %lu",
                              chunk_index);
    TraceLiveFrameProbeStagef("paint audit before chunk json %lu",
                              chunk_index);
    chunks_json << "{\"index\":" << chunk_index << ",\"paint_chunk_id\":"
                << chunk_id_json
                << ",\"stable_key\":"
                << stable_key_json
                << ",\"begin_index\":" << chunk_begin_index
                << ",\"end_index\":" << chunk_end_index
                << ",\"bounds\":" << chunk_bounds_json
                << ",\"drawable_bounds\":"
                << chunk_drawable_bounds_json
                << ",\"has_text\":" << (chunk_has_text ? "true" : "false")
                << ",\"is_cacheable\":"
                << (chunk_is_cacheable ? "true" : "false")
                << ",\"can_match_old_chunk\":"
                << (chunk_can_match_old ? "true" : "false")
                << ",\"client_debug_name\":null,\"client_owner_node_id\":null"
                << ",\"property_state\":{\"state_hash\":" << property_hash
                << ",\"transform_to_root\":"
                << projection_json
                << ",\"transform_is_2d\":"
                << (has_projection && projection.Is2dTransform() ? "true"
                                                                 : "false")
                << ",\"transform_has_non_translation\":"
                << (projection_has_non_translation ? "true" : "false")
                << ",\"transform_chain_depth\":" << transform_chain_depth
                << ",\"has_clip_rect\":"
                << (clip && !clip->IsInfinite() ? "true" : "false")
                << ",\"clip_rect\":"
                << clip_json
                << ",\"clip_has_rounded_clip\":"
                << (clip_paint_rect_rounded ? "true" : "false")
                << ",\"clip_chain_depth\":" << clip_chain_depth
                << ",\"effect_chain_depth\":" << effect_chain_depth
                << ",\"effect_opacity\":" << effect_opacity
                << ",\"effect_has_non_default_opacity\":"
                << (effect_opacity != 1.0f ? "true" : "false")
                << "},\"property_tree\":{\"transform_chain\":"
                << transform_chain_json
                << ",\"clip_chain\":"
                << clip_chain_json
                << ",\"effect_chain\":"
                << effect_chain_json
                << ",\"scroll\":"
                << scroll_json
                << ",\"inaccessible_fields\":["
                << "{\"field\":\"nearest_scroll_translation_node_id\",\"status\":\"inaccessible\",\"reason\":\"not exported by current TransformPaintPropertyNode access boundary\",\"required_header_or_friend_access\":\"transform_paint_property_node.h\"},"
                << "{\"field\":\"compositor_element_id_debug\",\"status\":\"inaccessible\",\"reason\":\"not stringified in standalone audit\",\"required_header_or_friend_access\":\"CompositorElementId formatting\"}]}"
                << ",\"op_histogram\":" << chunk_op_histogram_json
                << ",\"recursive_op_histogram\":"
                << chunk_recursive_op_histogram_json
                << ",\"unsupported_ops\":"
                << chunk_unsupported_histogram_json
                << ",\"fallback_rasterized_ops\":"
                << chunk_fallback_histogram_json
                << ",\"display_items\":" << display_items_json_string << "}";

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
  TraceLiveFrameProbeStage("paint audit after chunk loop");
  chunks_json << "]";
  TraceLiveFrameProbeStage("paint audit after chunks json close");

  cache.artifact_audit_lines.push_back(
      "paint_artifact_audit totals paint_ops=" +
      std::to_string(total_op_count) + " ops=" +
      MapToJsonObject(total_op_histogram) + " unsupported=" +
      MapToJsonObject(total_unsupported_histogram));
  TraceLiveFrameProbeStage("paint audit after totals line");

  const std::string lowered_input =
      LowerAsciiForStandaloneRenderer(cache.body_html);
  TraceLiveFrameProbeStage("paint audit after lowered input");
  const std::map<std::string, int> image_scheme_histogram =
      ImageSchemeHistogramForStandaloneRenderer(cache.body_html);
  TraceLiveFrameProbeStage("paint audit after image scheme histogram");
  const std::map<std::string, int> css_image_scheme_histogram =
      CssImageSchemeHistogramForStandaloneRenderer(cache.body_html);
  TraceLiveFrameProbeStage("paint audit after css image scheme histogram");
  const std::string page_evidence_json =
      "{\"status\":\"inaccessible\",\"field\":\"page_evidence\","
      "\"reason\":\"optional PageEvidenceJsonForStandaloneRenderer walk is "
      "disabled in the raw PaintArtifact audit because absolute/fixed pages "
      "exposed it as an unsafe metadata access; use --dump-page-setup for "
      "coordinate-correct element evidence\"}";
  const std::string out_of_flow_evidence_json =
      cache.holder
          ? OutOfFlowElementEvidenceJsonForStandaloneRenderer(
                cache.holder->GetDocument())
          : "{\"target_present\":false,\"first_missing_stage\":\"document_unavailable\"}";
  const std::string overflow_clip_diagnostics_json =
      cache.holder
          ? OverflowClipDiagnosticsJsonForStandaloneRenderer(
                cache.holder->GetDocument())
          : "{\"containers\":[],\"children\":[],\"first_missing_stage\":\"document_unavailable\"}";
  const std::string opacity_diagnostics_json =
      cache.holder
          ? OpacityDiagnosticsJsonForStandaloneRenderer(
                cache.holder->GetDocument())
          : "{\"targets\":[],\"first_missing_stage\":\"document_unavailable\"}";
  const std::string media_query_diagnostics_json =
      MediaQueryDiagnosticsJsonForStandaloneRenderer(cache);
  const std::string list_marker_diagnostics_json =
      cache.holder
          ? ListMarkerDiagnosticsJsonForStandaloneRenderer(
                cache.holder->GetDocument(), cache.body_html)
          : "{\"source_li_count\":0,\"layout_list_item_count\":0,"
            "\"marker_layout_object_count\":0,"
            "\"marker_pseudo_element_count\":0,"
            "\"first_missing_stage\":\"document_unavailable\"}";
  const std::string table_column_diagnostics_json =
      cache.holder
          ? TableColumnDiagnosticsJsonForStandaloneRenderer(
                cache.holder->GetDocument(), cache.body_html)
          : "{\"real_layout_table_column_creation_enabled\":true,"
            "\"production_failsoft_active\":false,"
            "\"first_missing_stage\":\"document_unavailable\"}";
  const std::string form_control_diagnostics_json =
      cache.holder
          ? FormControlDiagnosticsJsonForStandaloneRenderer(
                cache.holder->GetDocument(), cache.body_html)
          : "{\"first_missing_stage\":\"document_unavailable\"}";
  const std::string animation_runtime_diagnostics_json =
      AnimationRuntimeDiagnosticsJsonForStandaloneRenderer(cache.body_html,
                                                           cache);
  const std::string root_background_diagnostics_json =
      cache.holder
          ? RootBackgroundDiagnosticsJsonForStandaloneRenderer(
                cache.holder->GetDocument())
          : "{\"layout_view_present\":false,\"root_box_present\":false,"
            "\"styles\":[]}";
  TraceLiveFrameProbeStage("paint audit after page evidence");
  const bool evidence_has_non_translation_transform =
      page_evidence_json.find("\"has_non_translation_transform\":true") !=
      std::string::npos;
  const bool evidence_has_effect_opacity =
      page_evidence_json.find("\"effect_has_non_default_opacity\":true") !=
          std::string::npos ||
      page_evidence_json.find("\"has_opacity\":true") != std::string::npos;
  const bool evidence_has_clip =
      page_evidence_json.find("\"overflow_clip_present\":true") !=
          std::string::npos ||
      page_evidence_json.find("\"inner_border_radius_clip_present\":true") !=
          std::string::npos ||
      page_evidence_json.find("\"is_scroll_container\":true") !=
          std::string::npos;
  const bool opacity_style_without_effect_chunk =
      (evidence_has_effect_opacity ||
       lowered_input.find("opacity") != std::string::npos) &&
      effect_opacity_chunk_count == 0;
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
       << ",\"document_scroll_diagnostics\":{\"requested\":{\"x\":"
       << cache.requested_scroll_x << ",\"y\":" << cache.requested_scroll_y
       << "},\"applied\":{\"x\":" << cache.applied_scroll_x
       << ",\"y\":" << cache.applied_scroll_y
       << "},\"maximum\":{\"x\":" << cache.max_scroll_x
       << ",\"y\":" << cache.max_scroll_y
       << "},\"contents_size\":{\"width\":" << cache.scroll_contents_width
       << ",\"height\":" << cache.scroll_contents_height
       << "},\"visible_size\":{\"width\":" << cache.scroll_visible_width
       << ",\"height\":" << cache.scroll_visible_height
       << "},\"frame_view_size\":{\"width\":" << cache.frame_view_width
       << ",\"height\":" << cache.frame_view_height
       << "},\"frame_layout_size\":{\"width\":" << cache.frame_layout_width
       << ",\"height\":" << cache.frame_layout_height
       << "},\"visual_viewport_size\":{\"width\":"
       << cache.visual_viewport_width << ",\"height\":"
       << cache.visual_viewport_height
       << "},\"layout_view_border_box\":{\"width\":"
       << cache.layout_view_border_width << ",\"height\":"
       << cache.layout_view_border_height
       << "},\"layout_view_scroll_size\":{\"width\":"
       << cache.layout_view_scroll_width << ",\"height\":"
       << cache.layout_view_scroll_height
       << "},\"layout_view_fragment_count\":"
       << cache.layout_view_fragment_count
       << ",\"scroll_area_is_root_frame_viewport\":"
       << (cache.scroll_area_is_root_frame_viewport ? "true" : "false")
       << ",\"requested_non_zero\":"
       << (cache.scroll_offset_requested ? "true" : "false")
       << ",\"applied_to_blink\":"
       << (cache.scroll_offset_applied ? "true" : "false")
       << ",\"changed\":"
       << (cache.scroll_offset_changed ? "true" : "false")
       << ",\"status\":"
       << JsonStringForStandaloneRenderer(cache.scroll_offset_status) << "}"
       << ",\"element_scroll_diagnostics\":"
       << ElementScrollDiagnosticsJsonForStandaloneRenderer(cache)
       << ",\"scrollable_element_entries\":"
       << ScrollableElementEntriesJsonForStandaloneRenderer(cache)
       << ",\"sticky_position_diagnostics\":"
       << (cache.sticky_position_diagnostics_json.empty()
               ? "{}"
               : cache.sticky_position_diagnostics_json)
       << ",\"sticky_update_diagnostics\":{\"scroll_area_count\":"
       << cache.sticky_update_scroll_area_count
       << ",\"consumed_descendant_count\":"
       << cache.sticky_update_consumed_descendant_count
       << ",\"constrained_after_count\":"
       << cache.sticky_update_constrained_after_count
       << ",\"consumed_horizontal_count\":"
       << cache.sticky_update_consumed_horizontal_count
       << ",\"consumed_vertical_count\":"
       << cache.sticky_update_consumed_vertical_count << "}"
       << ",\"animation_time_diagnostics\":{\"requested_ms\":"
       << cache.requested_animation_time_ms << ",\"applied_ms\":"
       << cache.applied_animation_time_ms << ",\"requested_non_zero\":"
       << (cache.animation_time_requested ? "true" : "false")
       << ",\"applied_to_blink\":"
       << (cache.animation_time_applied ? "true" : "false")
       << ",\"status\":"
       << JsonStringForStandaloneRenderer(cache.animation_time_status)
       << ",\"standalone_supported_interpolation_groups\":[\"opacity\","
          "\"color\",\"transform\"]"
       << ",\"unsupported_interpolation_policy\":\"no-op\""
       << ",\"first_missing_stage\":"
       << JsonStringForStandaloneRenderer(
              cache.animation_time_requested && !cache.animation_time_applied
                  ? "animation_time_not_applied"
                  : "")
       << "}"
       << ",\"render_timing_diagnostics\":{\"mode\":\"in_process_probe_chrono\","
       << "\"warm_or_cold\":\"cold_or_rebuilt_probe_state\","
       << "\"cache_hit\":" << (cache.timing_cache_hit ? "true" : "false")
       << ",\"input_setup_ms\":" << cache.timing_input_setup_ms
       << ",\"html_parse_document_setup_ms\":"
       << cache.timing_html_document_setup_ms
       << ",\"style_update_ms\":" << cache.timing_style_update_ms
       << ",\"layout_lifecycle_ms\":"
       << cache.timing_layout_lifecycle_ms
       << ",\"prepaint_paint_lifecycle_ms\":"
       << cache.timing_prepaint_and_paint_lifecycle_ms
       << ",\"paint_artifact_generation_ms\":"
       << cache.timing_paint_artifact_generation_ms
       << ",\"paint_artifact_audit_json_ms\":"
       << cache.timing_paint_artifact_audit_ms
       << ",\"paint_artifact_extraction_ms\":"
       << cache.timing_paint_artifact_extraction_ms
       << ",\"total_probe_ms\":" << cache.timing_total_ms
       << ",\"caveat\":\"probe timings exclude process startup and CPU replay; "
          "PaintArtifact extraction is reported by the caller after audit "
          "serialization in some paths\"}"
       << ",\"device_scale_factor\":1"
       << ",\"media_query_diagnostics\":"
       << media_query_diagnostics_json
       << ",\"list_marker_diagnostics\":"
       << list_marker_diagnostics_json
       << ",\"table_column_diagnostics\":"
       << table_column_diagnostics_json
       << ",\"form_control_diagnostics\":"
       << form_control_diagnostics_json
       << ",\"animation_runtime_diagnostics\":"
       << animation_runtime_diagnostics_json
       << ",\"root_background_diagnostics\":"
       << root_background_diagnostics_json
       << ",\"paint_artifact_audit_safe_mode\":"
       << (artifact_audit_safe_mode ? "true" : "false")
       << ",\"paint_artifact_audit_safe_mode_reason\":"
       << JsonStringForStandaloneRenderer(
              artifact_audit_safe_mode
                  ? "out_of_flow_or_fixed_position_chunk_metadata_skipped"
                  : "")
       << ",\"metadata_safety\":{\"mode\":\"field_level\","
       << "\"source_string_safe_mode\":false,"
       << "\"page_evidence\":{\"status\":\"inaccessible\","
       << "\"reason\":\"optional page-evidence walk disabled; chunk, "
          "display-item, PaintOp, bounds, and property-state metadata are "
          "still collected field-by-field\"}}"
       << ",\"scrollbar_chrome_policy\":{"
       << "\"standalone_paints_scrollbars\":false,"
       << "\"standalone_paints_resizers\":false,"
       << "\"content_overflow_clip_preserved\":true,"
       << "\"scroll_background_failsoft_enabled\":true}"
       << ",\"overflow_clip_diagnostics\":"
       << overflow_clip_diagnostics_json
       << ",\"stacking_paint_provenance\":"
       << StandaloneStackingPaintProvenanceJsonForProbe()
       << ",\"raw_chunk_count\":" << chunk_count
       << ",\"raw_display_item_count\":" << display_item_count
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
       << ",\"filter_count\":" << total_raw_audit.filter_count
       << ",\"draw_looper_count\":" << total_raw_audit.draw_looper_count
       << ",\"draw_looper_layer_count\":"
       << total_raw_audit.draw_looper_layer_count
       << ",\"path_effect_count\":" << total_raw_audit.path_effect_count
       << "}"
       << ",\"typeface_resources\":{\"count\":"
       << StandaloneRendererSameProcessTypefaceResourceCount()
       << ",\"same_process_only\":true"
       << ",\"raw_pointer_payloads\":0"
       << ",\"lookup_attempt_count\":"
       << StandaloneRendererSameProcessTypefaceLookupAttemptCount()
       << ",\"lookup_success_count\":"
       << StandaloneRendererSameProcessTypefaceLookupSuccessCount()
       << ",\"lookup_failure_count\":"
       << StandaloneRendererSameProcessTypefaceLookupFailureCount()
       << ",\"families\":[";
  for (int i = 0; i < StandaloneRendererSameProcessTypefaceResourceCount();
       ++i) {
    char family[256] = {};
    if (StandaloneRendererSameProcessTypefaceFamilyAt(i, family,
                                                       sizeof(family)) <= 0) {
      continue;
    }
    if (i > 0) {
      json << ",";
    }
    json << JsonStringForStandaloneRenderer(family);
  }
  json << "]}"
       << ",\"font_resolution_diagnostics\":{\"count\":"
       << StandaloneRendererFontResolutionDiagnosticCount()
       << ",\"entries\":[";
  for (int i = 0; i < StandaloneRendererFontResolutionDiagnosticCount(); ++i) {
    char entry[2048] = {};
    if (StandaloneRendererFontResolutionDiagnosticJsonAt(
            i, entry, sizeof(entry)) <= 0) {
      continue;
    }
    if (i > 0) {
      json << ",";
    }
    json << entry;
  }
  json << "]}"
       << ",\"extraction_text_blob_resources\":{\"enabled\":"
       << (StandaloneRendererTextBlobReplayDiagnosticsEnabled() ? "true"
                                                                 : "false")
       << ",\"strict_typeface_payloads\":true"
       << ",\"raw_blob_count\":"
       << total_raw_audit.text_blob_count
       << ",\"retained_blob_count\":" << total_raw_audit.text_blob_count
       << ",\"deserialize_attempt_count\":"
       << StandaloneRendererTextBlobDeserializeAttemptCount()
       << ",\"deserialize_success_count\":"
       << StandaloneRendererTextBlobDeserializeSuccessCount()
       << ",\"deserialize_failure_count\":"
       << StandaloneRendererTextBlobDeserializeFailureCount()
       << ",\"typeface_resource_count\":"
       << StandaloneRendererSameProcessTypefaceResourceCount()
       << ",\"typeface_lookup_attempt_count\":"
       << StandaloneRendererSameProcessTypefaceLookupAttemptCount()
       << ",\"typeface_lookup_success_count\":"
       << StandaloneRendererSameProcessTypefaceLookupSuccessCount()
       << ",\"typeface_lookup_failure_count\":"
       << StandaloneRendererSameProcessTypefaceLookupFailureCount()
       << ",\"diagnostic_typeface_fallback_count\":"
       << StandaloneRendererDiagnosticTypefaceFallbackCount()
       << ",\"same_process_only\":true"
       << ",\"raw_pointer_payloads\":0"
       << ",\"failures\":[]}"
       << ",\"resource_provider\":";
  html_css_renderer::StandaloneResourceProviderDiagnostics provider_diagnostics =
      html_css_renderer::GetStandaloneResourceProviderDiagnostics();
  json << "{\"request_count\":" << provider_diagnostics.request_count
       << ",\"image_request_count\":"
       << provider_diagnostics.image_request_count
       << ",\"data_png_request_count\":"
       << provider_diagnostics.data_png_request_count
       << ",\"success_count\":" << provider_diagnostics.success_count
       << ",\"failure_count\":" << provider_diagnostics.failure_count
       << ",\"requests\":[";
  for (size_t i = 0; i < provider_diagnostics.requests.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    const auto& request = provider_diagnostics.requests[i];
    json << "{\"url_prefix\":"
         << JsonStringForStandaloneRenderer(request.url_prefix)
         << ",\"initiator\":"
         << JsonStringForStandaloneRenderer(request.initiator)
         << ",\"source_kind\":"
         << JsonStringForStandaloneRenderer(request.source_kind)
         << ",\"mime_type\":"
         << JsonStringForStandaloneRenderer(request.mime_type)
         << ",\"resolved_path\":"
         << JsonStringForStandaloneRenderer(request.resolved_path)
         << ",\"cache_key\":"
         << JsonStringForStandaloneRenderer(request.cache_key)
         << ",\"encoded_bytes\":" << request.encoded_bytes
         << ",\"decoded_width\":" << request.decoded_width
         << ",\"decoded_height\":" << request.decoded_height
         << ",\"status\":"
         << JsonStringForStandaloneRenderer(request.status)
         << ",\"error\":"
         << JsonStringForStandaloneRenderer(request.error) << "}";
  }
  json << "]}";
  json
       << ",\"image_reachability\":{\"html_image_element_count\":"
       << cache.image_reachability.html_image_element_count
       << ",\"img_src_detected_from_dom\":"
       << (cache.image_reachability.img_src_detected_from_dom ? "true"
                                                              : "false")
       << ",\"img_src_detected_from_source_scan\":"
       << (cache.image_reachability.img_src_detected_from_source_scan ? "true"
                                                                      : "false")
       << ",\"real_html_image_element_class_linked\":"
       << (cache.image_reachability.real_html_image_element_class_linked
               ? "true"
               : "false")
       << ",\"image_loader_present\":"
       << (cache.image_reachability.image_loader_present ? "true" : "false")
       << ",\"image_loader_update_called\":"
       << (cache.image_reachability.image_loader_update_called ? "true"
                                                               : "false")
       << ",\"image_loader_request_url\":"
       << JsonStringForStandaloneRenderer(
              TruncatedUrlForStandaloneRenderer(
                  cache.image_reachability.image_loader_request_url))
       << ",\"image_resource_content_fetch_called\":"
       << StandaloneRendererImageResourceContentFetchCalled()
       << ",\"provider_request_count\":";
  json << provider_diagnostics.request_count;
  json << ",\"layout_object_created\":"
       << (cache.image_reachability.layout_object_created ? "true" : "false")
       << ",\"layout_object_type\":"
       << JsonStringForStandaloneRenderer(
              cache.image_reachability.layout_object_type)
       << ",\"layout_image_resource_created\":"
       << (cache.image_reachability.layout_image_resource_created ? "true"
                                                                  : "false")
       << ",\"layout_image_resource_initialize_called\":"
       << StandaloneRendererLayoutImageResourceInitializeCalled()
       << ",\"layout_image_resource_set_resource_called\":"
       << StandaloneRendererLayoutImageResourceSetResourceCalled()
       << ",\"layout_image_set_resource_called\":"
       << StandaloneRendererLayoutImageSetResourceCalled()
       << ",\"natural_dimensions_called\":"
       << StandaloneRendererLayoutImageResourceNaturalDimensionsCalled()
       << ",\"get_image_called\":"
       << StandaloneRendererLayoutImageResourceGetImageCalled()
       << ",\"maybe_animated_called\":"
       << StandaloneRendererLayoutImageResourceMaybeAnimatedCalled()
       << ",\"maybe_animated_null_image\":"
       << StandaloneRendererLayoutImageResourceMaybeAnimatedNullImage()
       << ",\"layout_image_paint_called\":"
       << StandaloneRendererLayoutImagePaintCalled()
       << ",\"layout_image_paint_replaced_called\":"
       << StandaloneRendererLayoutImagePaintReplacedCalled()
       << ",\"image_painter_paint_replaced_called\":"
       << StandaloneRendererImagePainterPaintReplacedCalled()
       << ",\"first_missing_stage\":"
       << JsonStringForStandaloneRenderer(
              FirstMissingImageStageForStandaloneRenderer(
                  cache.image_reachability))
       << "}"
       << ",\"image_diagnostics\":{\"image_element_count\":";
  int image_element_count = 0;
  for (const auto& [scheme, count] : image_scheme_histogram) {
    image_element_count += count;
  }
  int provider_decoded_width = 0;
  int provider_decoded_height = 0;
  std::string provider_image_status;
  for (const auto& request : provider_diagnostics.requests) {
    if (request.initiator == "img") {
      provider_decoded_width = request.decoded_width;
      provider_decoded_height = request.decoded_height;
      provider_image_status = request.status;
      break;
    }
  }
  json << image_element_count << ",\"src_scheme_histogram\":"
       << MapToJsonObject(image_scheme_histogram)
       << ",\"resource_load_status\":\""
       << (image_element_count > 0 && total_raw_audit.image_count == 0
               ? "no Blink image paint emitted; standalone image element/loader ownership path is not fully linked"
               : "not_applicable_or_painted")
       << "\",\"decode_status\":\"unknown\",\"layout_status\":\"unknown\"}"
       << ",\"image_size_diagnostics\":{\"element_natural_width\":"
       << cache.image_reachability.element_natural_width
       << ",\"element_natural_height\":"
       << cache.image_reachability.element_natural_height
       << ",\"loader_natural_width\":"
       << cache.image_reachability.loader_natural_width
       << ",\"loader_natural_height\":"
       << cache.image_reachability.loader_natural_height
       << ",\"loader_resource_width\":"
       << cache.image_reachability.loader_resource_width
       << ",\"loader_resource_height\":"
       << cache.image_reachability.loader_resource_height
       << ",\"loader_content_present\":"
       << (cache.image_reachability.loader_content_present ? "true" : "false")
       << ",\"loader_content_has_image\":"
       << (cache.image_reachability.loader_content_has_image ? "true" : "false")
       << ",\"loader_content_error\":"
       << (cache.image_reachability.loader_content_error ? "true" : "false")
       << ",\"provider_decoded_width\":" << provider_decoded_width
       << ",\"provider_decoded_height\":" << provider_decoded_height
       << ",\"layout_intrinsic_width\":"
       << cache.image_reachability.loader_resource_width
       << ",\"layout_intrinsic_height\":"
       << cache.image_reachability.loader_resource_height
       << ",\"width_attr\":"
       << JsonStringForStandaloneRenderer(cache.image_reachability.width_attr)
       << ",\"height_attr\":"
       << JsonStringForStandaloneRenderer(cache.image_reachability.height_attr)
       << ",\"computed_display\":"
       << cache.image_reachability.computed_display
       << ",\"computed_visibility\":"
       << cache.image_reachability.computed_visibility
       << ",\"computed_width\":"
       << JsonStringForStandaloneRenderer(
              cache.image_reachability.computed_width)
       << ",\"computed_height\":"
       << JsonStringForStandaloneRenderer(
              cache.image_reachability.computed_height)
       << ",\"layout_box_size\":["
       << cache.image_reachability.layout_box_width << ","
       << cache.image_reachability.layout_box_height << "]"
       << ",\"layout_content_size\":["
       << cache.image_reachability.layout_content_width << ","
       << cache.image_reachability.layout_content_height << "]"
       << ",\"layout_viewport_rect\":["
       << cache.image_reachability.layout_viewport_x << ","
       << cache.image_reachability.layout_viewport_y << ","
       << cache.image_reachability.layout_viewport_width << ","
       << cache.image_reachability.layout_viewport_height << "]"
       << ",\"physical_fragment_count\":"
       << cache.image_reachability.physical_fragment_count
       << ",\"paint_layer_present\":"
       << (cache.image_reachability.paint_layer_present ? "true" : "false")
       << ",\"object_paint_properties_present\":"
       << (cache.image_reachability.object_paint_properties_present ? "true"
                                                                    : "false")
       << ",\"paint_image_width\":" << provider_decoded_width
       << ",\"paint_image_height\":" << provider_decoded_height
       << ",\"get_natural_dimensions_called\":"
       << StandaloneRendererLayoutImageResourceNaturalDimensionsCalled()
       << ",\"size_source_used_for_layout\":"
       << JsonStringForStandaloneRenderer(
              cache.image_reachability.loader_natural_width > 0 &&
                      cache.image_reachability.loader_natural_height > 0
                  ? "loader_natural_size"
                  : provider_decoded_width > 0 && provider_decoded_height > 0
                        ? "provider_decoded_size_available_element_natural_size_not_observed"
                        : "unknown")
       << ",\"provider_status\":"
       << JsonStringForStandaloneRenderer(provider_image_status) << "}"
       << ",\"image_pipeline\":{\"image_element_count\":"
       << image_element_count << ",\"images\":[";
  const std::vector<std::string> image_sources =
      ImageSrcListForStandaloneRenderer(cache.body_html);
  for (size_t i = 0; i < image_sources.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    const std::string& src = image_sources[i];
    const bool has_image_paint = total_raw_audit.image_count > 0;
    json << "{\"src_scheme\":"
         << JsonStringForStandaloneRenderer(SchemeForStandaloneRenderer(src))
         << ",\"current_src\":"
         << JsonStringForStandaloneRenderer(
                TruncatedUrlForStandaloneRenderer(src))
         << ",\"complete\":\"unknown\""
         << ",\"natural_width\":"
         << cache.image_reachability.element_natural_width
         << ",\"natural_height\":"
         << cache.image_reachability.element_natural_height
         << ",\"loader_natural_width\":"
         << cache.image_reachability.loader_natural_width
         << ",\"loader_natural_height\":"
         << cache.image_reachability.loader_natural_height
         << ",\"loader_resource_width\":"
         << cache.image_reachability.loader_resource_width
         << ",\"loader_resource_height\":"
         << cache.image_reachability.loader_resource_height
         << ",\"provider_decoded_width\":" << provider_decoded_width
         << ",\"provider_decoded_height\":" << provider_decoded_height
         << ",\"layout_object_type\":"
         << JsonStringForStandaloneRenderer(
                cache.image_reachability.layout_object_type)
         << ",\"is_layout_image\":"
         << (cache.image_reachability.layout_is_layout_image ? "true"
                                                             : "false")
         << ",\"is_layout_box\":"
         << (cache.image_reachability.layout_is_box ? "true" : "false")
         << ",\"width_attr\":"
         << JsonStringForStandaloneRenderer(cache.image_reachability.width_attr)
         << ",\"height_attr\":"
         << JsonStringForStandaloneRenderer(cache.image_reachability.height_attr)
         << ",\"computed_width\":"
         << JsonStringForStandaloneRenderer(
                cache.image_reachability.computed_width)
         << ",\"computed_height\":"
         << JsonStringForStandaloneRenderer(
                cache.image_reachability.computed_height)
         << ",\"layout_box_size\":["
         << cache.image_reachability.layout_box_width << ","
         << cache.image_reachability.layout_box_height << "]"
         << ",\"layout_content_size\":["
         << cache.image_reachability.layout_content_width << ","
         << cache.image_reachability.layout_content_height << "]"
         << ",\"layout_viewport_rect\":["
         << cache.image_reachability.layout_viewport_x << ","
         << cache.image_reachability.layout_viewport_y << ","
         << cache.image_reachability.layout_viewport_width << ","
         << cache.image_reachability.layout_viewport_height << "]"
         << ",\"paint_layer_present\":"
         << (cache.image_reachability.paint_layer_present ? "true" : "false")
         << ",\"object_paint_properties_present\":"
         << (cache.image_reachability.object_paint_properties_present ? "true"
                                                                      : "false")
         << ",\"layout_image_paint_called\":"
         << StandaloneRendererLayoutImagePaintCalled()
         << ",\"layout_image_paint_replaced_called\":"
         << StandaloneRendererLayoutImagePaintReplacedCalled()
         << ",\"image_painter_paint_replaced_called\":"
         << StandaloneRendererImagePainterPaintReplacedCalled()
         << ",\"cached_image_present\":"
         << (cache.image_reachability.loader_content_present ? "true" : "false")
         << ",\"image_resource_content_present\":"
         << (cache.image_reachability.loader_content_present ||
                     StandaloneRendererImageResourceContentFetchCalled() > 0
                 ? "true"
                 : "false")
         << ",\"encoded_data_bytes\":"
         << EncodedDataBytesForStandaloneRenderer(src)
         << ",\"decode_status\":"
         << JsonStringForStandaloneRenderer(
                has_image_paint
                    ? "painted"
                    : (provider_image_status == "success" &&
                       cache.image_reachability.layout_object_type.find("LayoutImage") !=
                           std::string::npos
                           ? "provider_success_layout_image_but_no_image_paint"
                           : "provider_or_layout_not_ready_for_image_paint"))
         << ",\"paint_status\":"
         << JsonStringForStandaloneRenderer(
                has_image_paint
                    ? "image paint emitted"
                    : (provider_image_status == "success" &&
                       cache.image_reachability.layout_object_type.find("LayoutImage") !=
                           std::string::npos
                           ? "no image paint emitted; ImagePainter/GetImage not entered for this layout path"
                           : "no image paint emitted"))
         << ",\"blocker_file\":"
         << JsonStringForStandaloneRenderer(
                has_image_paint
                    ? ""
                    : (provider_image_status == "success" &&
                       cache.image_reachability.layout_object_type.find("LayoutImage") !=
                           std::string::npos
                           ? "upstream/chromium/third_party/blink/renderer/core/paint/image_painter.cc"
                           : "upstream/chromium/third_party/blink/renderer/core/html/html_image_element.cc"))
         << ",\"blocker_functions\":["
         << JsonStringForStandaloneRenderer(
                "HTMLImageElement::CreateLayoutObject(const ComputedStyle&)")
         << ","
         << JsonStringForStandaloneRenderer(
                "ImageLoader::UpdateFromElement(UpdateFromElementBehavior, UpdateType)")
         << ","
         << JsonStringForStandaloneRenderer(
                "ImageResourceContent::Fetch(FetchParameters&, ResourceFetcher*)")
         << ","
         << JsonStringForStandaloneRenderer(
                "LayoutImageResource::SetImageResource(ImageResourceContent*)")
         << "]}";
  }
  json << "]}";
  int css_image_count = 0;
  for (const auto& [scheme, count] : css_image_scheme_histogram) {
    css_image_count += count;
  }
  json << ",\"css_image_diagnostics\":{\"background_image_present\":"
       << (lowered_input.find("background-image") != std::string::npos ||
                   lowered_input.find("url(") != std::string::npos
               ? "true"
               : "false")
       << ",\"url_scheme_histogram\":"
       << MapToJsonObject(css_image_scheme_histogram)
       << ",\"css_image_url_count\":" << css_image_count
       << ",\"style_image_presence\":\"unknown_at_current_access_boundary\""
       << ",\"resource_status\":\""
       << (css_image_count > 0 && total_raw_audit.image_count == 0
               ? "no image-backed Blink paint observed"
               : "not_applicable_or_image_painted")
       << "\",\"paint_status\":\""
       << (css_image_count > 0 && total_raw_audit.image_count == 0
               ? "fallback/background rect paint only or image resource blocked"
               : "not_applicable_or_image_painted")
       << "\",\"raw_paint_ops\":{\"DrawImageOp\":"
       << total_recursive_op_histogram["DrawImageOp"]
       << ",\"DrawImageRectOp\":"
       << total_recursive_op_histogram["DrawImageRectOp"]
       << ",\"DrawRectOp\":" << total_recursive_op_histogram["DrawRectOp"]
       << "},\"blocker_file\":\""
       << (css_image_count > 0 && total_raw_audit.image_count == 0
               ? "upstream/chromium/standalone_renderer/src/live_link_boundary_stubs.cc"
               : "")
       << "\"}"
       << ",\"effect_opacity_diagnostics\":{"
       << "\"effect_opacity_chunk_count\":" << effect_opacity_chunk_count
       << ",\"grouped_opacity_layer_count\":" << grouped_opacity_layer_count
       << ",\"nested_opacity_chunk_count\":" << nested_opacity_chunk_count
       << ",\"effect_opacity_chunk_with_clip_count\":"
       << effect_opacity_chunk_with_clip_count
       << ",\"replay_strategy\":\"chunk_saveLayer_for_non_default_effect_opacity\""
       << ",\"stacking_context_is_not_stacked_enabled\":"
       << (RuntimeEnabledFeatures::StackingContextIsNotStackedEnabled()
               ? "true"
               : "false")
       << ",\"unsupported_effect_reason\":"
       << JsonStringForStandaloneRenderer(
              opacity_style_without_effect_chunk
                  ? "style_or_layout_evidence_has_opacity_but_no_non_default_PaintArtifact_effect_chunk_was_exported"
                  : "")
       << "}"
       << ",\"opacity_element_diagnostics\":"
       << opacity_diagnostics_json
       << ",\"text_decoration_diagnostics\":{"
       << "\"text_decoration_painter_constructed\":"
       << g_standalone_text_decoration_painter_constructed
       << ",\"text_decoration_begin_called\":"
       << g_standalone_text_decoration_begin_called
       << ",\"paint_except_line_through_called\":"
       << g_standalone_text_decoration_except_line_through_called
       << ",\"paint_only_line_through_called\":"
       << g_standalone_text_decoration_only_line_through_called
       << ",\"decoration_line_painter_paint_called\":"
       << g_standalone_decoration_line_painter_paint_called
       << ",\"stubbed_noop_path_active\":false"
       << ",\"blocker_file\":\"\""
       << "}"
       << ",\"page_evidence\":" << page_evidence_json
       << ",\"out_of_flow_diagnostics\":" << out_of_flow_evidence_json
       << ",\"chunks\":" << chunks_json.str()
       << ",\"self_checks\":{\"css_applied\":\"unknown\""
       << ",\"has_text_paint\":"
       << (total_raw_audit.text_blob_count > 0 ? "true" : "false")
       << ",\"has_non_text_paint\":"
       << (total_raw_audit.has_non_text_visual_paint ? "true" : "false")
       << ",\"has_shader_paint\":"
       << (total_raw_audit.shader_count > 0 ? "true" : "false")
       << ",\"has_clip_state\":"
       << (total_has_clip_state || evidence_has_clip ? "true" : "false")
       << ",\"has_non_translation_transform\":"
       << (total_raw_audit.has_non_translation_transform ||
                   evidence_has_non_translation_transform
               ? "true"
               : "false")
       << ",\"has_effect_opacity\":"
       << (total_raw_audit.has_effect_opacity || evidence_has_effect_opacity
               ? "true"
               : "false")
       << ",\"raw_visual_op_count\":" << total_raw_audit.visual_op_count
       << ",\"retained_supported_visual_op_count\":"
       << total_raw_audit.retained_supported_visual_op_count
       << ",\"retained_unsupported_visual_op_count\":"
       << total_raw_audit.retained_unsupported_visual_op_count
       << ",\"diagnostic_bitmap_fallback_visual_op_count\":"
       << total_raw_audit.diagnostic_bitmap_fallback_visual_op_count
       << ",\"raw_ops_lost_during_retained_extraction\":";
  int visual_unsupported_ops = 0;
  for (const auto& [name, count] : total_unsupported_histogram) {
    visual_unsupported_ops += count;
  }
  int fallback_ops = 0;
  for (const auto& [name, count] : total_fallback_histogram) {
    fallback_ops += count;
  }
  const int raw_ops_lost =
      std::max(0, total_raw_audit.visual_op_count -
                      total_raw_audit.retained_supported_visual_op_count -
                      total_raw_audit.retained_unsupported_visual_op_count -
                      total_raw_audit.diagnostic_bitmap_fallback_visual_op_count);
  json << raw_ops_lost
       << ",\"visual_unsupported_ops\":" << visual_unsupported_ops
       << ",\"diagnostic_bitmap_fallback_ops\":" << fallback_ops << "}"
       << ",\"lost_raw_ops\":[]"
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
  if (cache.disable_retained_extraction) {
    cache.artifact_audit_lines.push_back(
        "paint_op_extraction disabled reason=audit_only_or_disable_retained_extraction");
    TraceLiveFrameProbeStage("export skipped retained extraction");
    return;
  }
  if (cache.force_oracle_bitmap) {
    cache.artifact_audit_lines.push_back(
        "paint_op_extraction mode=skia_paint_record_oracle requested=true");
    if (AppendPaintArtifactOracleBitmapOp(artifact, cache.viewport_width,
                                          cache.viewport_height,
                                          cache.exported_draw_ops)) {
      TraceLiveFrameProbeStage("export requested oracle bitmap done");
      return;
    }
    cache.artifact_audit_lines.push_back(
        "paint_op_extraction mode=skia_paint_record_oracle failed");
    TraceLiveFrameProbeStage("export requested oracle bitmap failed");
    return;
  }
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
  const auto total_start = StandaloneProbeClock::now();
  EnsureWtfInitializedForStandaloneRenderer();
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string input_html = body_html ? body_html : "";
  if (cache.initialized && cache.body_html == input_html) {
    cache.timing_cache_hit = true;
    return cache.result;
  }
  const auto setup_start = StandaloneProbeClock::now();
  html_css_renderer::ResetStandaloneResourceProviderDiagnostics();
  StandaloneRendererResetImageReachabilityDiagnostics();
  StandaloneRendererResetOutOfFlowDiagnostics();
  StandaloneRendererResetMediaQueryDiagnostics();
  StandaloneRendererResetListItemFactoryDiagnostics();
  ResetStandaloneStackingPaintProvenanceForProbe();
  g_standalone_css_animation_timeline_update_called = 0;
  g_standalone_css_animation_update_called = 0;
  g_standalone_css_transition_update_called = 0;
  g_standalone_document_animations_update_called = 0;
  g_standalone_page_animator_service_called = 0;
  cache.image_reachability = ImageReachabilityDiagnostics();
  cache.timing_total_ms = 0.0;
  cache.timing_input_setup_ms = 0.0;
  cache.timing_html_document_setup_ms = 0.0;
  cache.timing_style_update_ms = 0.0;
  cache.timing_layout_lifecycle_ms = 0.0;
  cache.timing_prepaint_and_paint_lifecycle_ms = 0.0;
  cache.timing_paint_artifact_generation_ms = 0.0;
  cache.timing_paint_artifact_audit_ms = 0.0;
  cache.timing_paint_artifact_extraction_ms = 0.0;
  cache.timing_cache_hit = false;
  cache.hit_test_entries.clear();
  cache.scrollable_element_entries.clear();
  cache.sticky_update_scroll_area_count = 0;
  cache.sticky_update_consumed_descendant_count = 0;
  cache.sticky_update_constrained_after_count = 0;
  cache.sticky_update_consumed_horizontal_count = 0;
  cache.sticky_update_consumed_vertical_count = 0;
  LiveFramePaintProbeResult result;
  TraceLiveFrameProbeStage("before DummyPageHolder");
  if (!cache.holder) {
    cache.holder = new DummyPageHolder(
        gfx::Size(cache.viewport_width, cache.viewport_height));
  }
  TraceLiveFrameProbeStage("after DummyPageHolder");
  Document& document = cache.holder->GetDocument();
  TraceLiveFrameProbeStage("after GetDocument");
  cache.timing_input_setup_ms =
      StandaloneProbeElapsedMs(setup_start, StandaloneProbeClock::now());

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
  const auto html_setup_start = StandaloneProbeClock::now();
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
  ApplyElementAttributesForStandaloneRenderer(
      document, cache.requested_element_attributes_by_id_and_name);
  TraceLiveFrameProbeStage("after SetInnerHTML");
  cache.timing_html_document_setup_ms =
      StandaloneProbeElapsedMs(html_setup_start, StandaloneProbeClock::now());
  cache.image_reachability =
      CollectImageReachabilityForStandaloneRenderer(document, input_html);
  if (LifecycleStopEqualsForStandaloneRenderer("html")) {
    result.lifecycle_reached_paint_clean = 0;
    cache.body_html = input_html;
    cache.raw_paint_artifact_audit_json =
        "{\"source\":\"real Blink PaintArtifact\",\"lifecycle_stop\":\"html\","
        "\"status\":\"stopped_after_html\"}";
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  DumpNodeForStandaloneRenderer(*document.body(), 0);

  LocalFrameView& frame_view = cache.holder->GetFrameView();
  if (Settings* settings = document.GetSettings()) {
    settings->SetDefaultFontSize(16);
    settings->SetDefaultFixedFontSize(13);
  }
  TraceLiveFrameProbeStage("before active style update");
  const auto style_update_start = StandaloneProbeClock::now();
  document.GetStyleEngine().UpdateActiveStyle();
  TraceLiveFrameProbeStage("after active style update");
  cache.timing_style_update_ms =
      StandaloneProbeElapsedMs(style_update_start, StandaloneProbeClock::now());
  if (LifecycleStopEqualsForStandaloneRenderer("style")) {
    result.lifecycle_reached_paint_clean = 0;
    cache.body_html = input_html;
    cache.raw_paint_artifact_audit_json =
        "{\"source\":\"real Blink PaintArtifact\",\"lifecycle_stop\":\"style\","
        "\"status\":\"stopped_after_style\"}";
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  if (LifecycleStopEqualsForStandaloneRenderer("layout")) {
    TraceLiveFrameProbeStage("before layout lifecycle update");
    result.lifecycle_reached_paint_clean =
        UpdateLifecycleToLayoutCleanForStandaloneRenderer(
            frame_view, DocumentUpdateReason::kTest)
            ? 1
            : 0;
    UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
    TraceLiveFrameProbeStage("after layout lifecycle update");
    cache.image_reachability =
        CollectImageReachabilityForStandaloneRenderer(document, input_html);
    cache.body_html = input_html;
    cache.raw_paint_artifact_audit_json =
        "{\"source\":\"real Blink PaintArtifact\",\"lifecycle_stop\":\"layout\","
        "\"status\":\"stopped_after_layout\"}";
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  TraceLiveFrameProbeStage("before required layout lifecycle update");
  const auto layout_lifecycle_start = StandaloneProbeClock::now();
  if (cache.animation_time_requested) {
    document.UpdateStyleAndLayoutTree();
  }
  UpdateLifecycleToLayoutCleanForStandaloneRenderer(
      frame_view, DocumentUpdateReason::kTest);
  if (cache.animation_time_requested) {
    TraceLiveFrameProbeStage("before standalone animation time apply");
    document.GetPendingAnimations().Update(nullptr, false);
    ApplyAnimationTimeForStandaloneRenderer(document);
    if (cache.animation_time_applied) {
      document.UpdateStyleAndLayoutTree();
      UpdateLifecycleToLayoutCleanForStandaloneRenderer(
          frame_view, DocumentUpdateReason::kTest);
    }
    TraceLiveFrameProbeStage("after standalone animation time apply");
  }
  UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
  TraceLiveFrameProbeStage("after required layout lifecycle update");
  ApplyInteractionStateForStandaloneRenderer(
      document, cache.requested_hovered_element_id,
      cache.requested_active_element_id);
  frame_view.SetNeedsUpdateGeometries();
  frame_view.UpdateGeometry();
  TraceLiveFrameProbeStage("before document scroll offset apply");
  ApplyDocumentScrollOffsetForStandaloneRenderer(frame_view);
  TraceLiveFrameProbeStage("after document scroll offset apply");
  TraceLiveFrameProbeStage("before element scroll offset apply");
  ApplyElementScrollOffsetsForStandaloneRenderer(document);
  TraceLiveFrameProbeStage("after element scroll offset apply");
  UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
  cache.timing_layout_lifecycle_ms = StandaloneProbeElapsedMs(
      layout_lifecycle_start, StandaloneProbeClock::now());
  if (g_standalone_oof_unsupported_inline_containing_block > 0 &&
      g_standalone_oof_fragment_created == 0) {
    cache.image_reachability =
        CollectImageReachabilityForStandaloneRenderer(document, input_html);
    cache.body_html = input_html;
    cache.raw_paint_artifact_audit_json =
        std::string("{\"source\":\"real Blink PaintArtifact\",") +
        "\"status\":\"stopped_after_layout_due_to_unsupported_oof\","
        "\"reason\":\"standalone OOF subset does not support inline "
        "containing-block absolute positioning yet\","
        "\"out_of_flow_diagnostics\":" +
        OutOfFlowElementEvidenceJsonForStandaloneRenderer(document) + "}";
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  if (LifecycleStopEqualsForStandaloneRenderer("prepaint")) {
    TraceLiveFrameProbeStage("before prepaint lifecycle update");
    result.lifecycle_reached_paint_clean =
        UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
            frame_view, DocumentUpdateReason::kTest)
            ? 1
            : 0;
    TraceLiveFrameProbeStage("after prepaint lifecycle update");
    cache.image_reachability =
        CollectImageReachabilityForStandaloneRenderer(document, input_html);
    cache.body_html = input_html;
    cache.raw_paint_artifact_audit_json =
        "{\"source\":\"real Blink PaintArtifact\","
        "\"lifecycle_stop\":\"prepaint\","
        "\"status\":\"stopped_after_prepaint\"}";
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  TraceLiveFrameProbeStage("before lifecycle update");
  const auto paint_lifecycle_start = StandaloneProbeClock::now();
  result.lifecycle_reached_paint_clean =
      UpdateAllLifecyclePhasesForTestForStandaloneRenderer(frame_view) ? 1 : 0;
  TraceLiveFrameProbeStage("after lifecycle update");
  TraceLiveFrameProbeStage("before post-lifecycle document scroll offset apply");
  ApplyDocumentScrollOffsetForStandaloneRenderer(frame_view);
  TraceLiveFrameProbeStage("after post-lifecycle document scroll offset apply");
  TraceLiveFrameProbeStage("before post-lifecycle element scroll offset apply");
  ApplyElementScrollOffsetsForStandaloneRenderer(document);
  TraceLiveFrameProbeStage("after post-lifecycle element scroll offset apply");
  UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
  if (cache.scroll_offset_changed || cache.element_scroll_offset_changed) {
    TraceLiveFrameProbeStage("before post-scroll lifecycle update");
    result.lifecycle_reached_paint_clean =
        UpdateAllLifecyclePhasesForTestForStandaloneRenderer(frame_view) ? 1
                                                                         : 0;
    TraceLiveFrameProbeStage("after post-scroll lifecycle update");
  }
  cache.timing_prepaint_and_paint_lifecycle_ms =
      StandaloneProbeElapsedMs(paint_lifecycle_start,
                               StandaloneProbeClock::now());
  cache.image_reachability =
      CollectImageReachabilityForStandaloneRenderer(document, input_html);
  cache.hit_test_entries.clear();
  CollectLiveHitTestEntriesForStandaloneRenderer(&document,
                                                 cache.hit_test_entries);
  cache.scrollable_element_entries.clear();
  CollectLiveScrollableElementEntriesForStandaloneRenderer(
      &document, cache.scrollable_element_entries);
  cache.sticky_position_diagnostics_json =
      StickyPositionDiagnosticsJsonForStandaloneRenderer(&document);
  if (LifecycleStopEqualsForStandaloneRenderer("paint")) {
    cache.body_html = input_html;
    cache.raw_paint_artifact_audit_json =
        "{\"source\":\"real Blink PaintArtifact\",\"lifecycle_stop\":\"paint\","
        "\"status\":\"stopped_after_paint\"}";
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  if (document.GetLayoutView()) {
    const gfx::Size view_size = document.GetLayoutView()->GetLayoutSize();
  }
  DumpNodeForStandaloneRenderer(*document.body(), 0);
  const auto paint_artifact_start = StandaloneProbeClock::now();
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
  SortLiveHitTestEntriesByPaintOrderForStandaloneRenderer(
      artifact, cache.hit_test_entries);
  SortLiveScrollableElementEntriesByPaintOrderForStandaloneRenderer(
      artifact, cache.scrollable_element_entries);
  cache.timing_paint_artifact_generation_ms =
      StandaloneProbeElapsedMs(paint_artifact_start,
                               StandaloneProbeClock::now());
  cache.body_html = input_html;
  cache.timing_total_ms =
      StandaloneProbeElapsedMs(total_start, StandaloneProbeClock::now());
  const auto audit_start = StandaloneProbeClock::now();
  BuildPaintArtifactAudit(artifact, cache);
  cache.timing_paint_artifact_audit_ms =
      StandaloneProbeElapsedMs(audit_start, StandaloneProbeClock::now());
  if (LifecycleStopEqualsForStandaloneRenderer("artifact")) {
    cache.body_html = input_html;
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  const auto extraction_start = StandaloneProbeClock::now();
  ExportDrawOpsForStandaloneRenderer(artifact, cache);
  cache.timing_paint_artifact_extraction_ms =
      StandaloneProbeElapsedMs(extraction_start, StandaloneProbeClock::now());
  cache.timing_total_ms =
      StandaloneProbeElapsedMs(total_start, StandaloneProbeClock::now());
  cache.result = result;
  cache.initialized = true;
  return result;
}

}  // namespace

void ResetStandaloneStackingPaintProvenanceForProbe() {
  StandaloneStackingPaintEventsForProbe().clear();
  StandaloneStackingPaintEventSequenceForProbe() = 0;
}

void RecordStandalonePaintLayerProvenanceForProbe(const char* source,
                                                  const PaintLayer& layer,
                                                  int phase,
                                                  int children_to_visit,
                                                  int visit_index) {
  auto& events = StandaloneStackingPaintEventsForProbe();
  if (events.size() >= 512) {
    return;
  }
  events.push_back(MakeStandaloneStackingPaintEvent(
      source, layer.GetLayoutObject(), phase, children_to_visit, visit_index));
}

void RecordStandaloneFragmentPaintProvenanceForProbe(
    const char* source,
    const LayoutObject* layout_object,
    int phase,
    bool fragment_has_self_painting_layer,
    bool fragment_can_traverse,
    float fragment_width,
    float fragment_height) {
  if (!layout_object) {
    return;
  }
  auto& events = StandaloneStackingPaintEventsForProbe();
  if (events.size() >= 512) {
    return;
  }
  StandaloneStackingPaintEvent event = MakeStandaloneStackingPaintEvent(
      source, *layout_object, phase, -1, -1);
  event.has_visible_content =
      event.has_visible_content || fragment_has_self_painting_layer;
  event.has_visible_self_painting_descendant =
      event.has_visible_self_painting_descendant || fragment_can_traverse;
  event.fragment_width = fragment_width;
  event.fragment_height = fragment_height;
  events.push_back(std::move(event));
}

std::string StandaloneStackingPaintProvenanceJsonForProbe() {
  const auto& events = StandaloneStackingPaintEventsForProbe();
  std::ostringstream json;
  json << "{\"event_count\":" << events.size() << ",\"events\":[";
  bool first = true;
  for (const StandaloneStackingPaintEvent& event : events) {
    if (!first) {
      json << ",";
    }
    first = false;
    json << "{\"sequence\":" << event.sequence
         << ",\"source\":" << JsonStringForStandaloneRenderer(event.source)
         << ",\"layout_object\":"
         << JsonStringForStandaloneRenderer(event.layout_object)
         << ",\"tag\":" << JsonStringForStandaloneRenderer(event.tag)
         << ",\"class\":"
         << JsonStringForStandaloneRenderer(event.class_name)
         << ",\"phase\":" << event.phase
         << ",\"children_to_visit\":" << event.children_to_visit
         << ",\"visit_index\":" << event.visit_index
         << ",\"z_index\":" << event.z_index
         << ",\"raw_z_index\":" << event.raw_z_index
         << ",\"has_auto_z_index\":"
         << (event.has_auto_z_index ? "true" : "false")
         << ",\"allows_z_index\":"
         << (event.allows_z_index ? "true" : "false")
         << ",\"is_stacked\":" << (event.is_stacked ? "true" : "false")
         << ",\"is_stacking_context\":"
         << (event.is_stacking_context ? "true" : "false")
         << ",\"has_layer\":" << (event.has_layer ? "true" : "false")
         << ",\"layer_self_painting\":"
         << (event.layer_self_painting ? "true" : "false")
         << ",\"has_visible_content\":"
         << (event.has_visible_content ? "true" : "false")
         << ",\"has_visible_self_painting_descendant\":"
         << (event.has_visible_self_painting_descendant ? "true" : "false")
         << ",\"has_self_painting_descendant\":"
         << (event.has_self_painting_descendant ? "true" : "false")
         << ",\"fragment_size\":[" << event.fragment_width << ","
         << event.fragment_height << "]"
         << "}";
  }
  json << "]}";
  return json.str();
}

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
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
    float x,
    float y) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool requested = std::abs(x) > 0.001f || std::abs(y) > 0.001f;
  if (cache.scroll_offset_requested == requested &&
      std::abs(cache.requested_scroll_x - x) <= 0.001f &&
      std::abs(cache.requested_scroll_y - y) <= 0.001f) {
    return;
  }
  cache.requested_scroll_x = x;
  cache.requested_scroll_y = y;
  cache.applied_scroll_x = 0.0f;
  cache.applied_scroll_y = 0.0f;
  cache.max_scroll_x = 0.0f;
  cache.max_scroll_y = 0.0f;
  cache.scroll_offset_requested = requested;
  cache.scroll_offset_applied = false;
  cache.scroll_offset_changed = false;
  cache.scroll_offset_status = requested ? "requested" : "not_requested";
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetElementScrollOffsetsForStandaloneRenderer(
    const char* serialized_offsets) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string value = serialized_offsets ? serialized_offsets : "";
  if (cache.requested_element_scroll_offsets_serialized == value) {
    return;
  }
  cache.requested_element_scroll_offsets_serialized = value;
  cache.requested_element_scroll_offsets_by_id =
      ParseElementScrollOffsetsForStandaloneRenderer(value);
  cache.element_scroll_diagnostics.clear();
  cache.element_scroll_offset_requested =
      !cache.requested_element_scroll_offsets_by_id.empty();
  cache.element_scroll_offset_applied = false;
  cache.element_scroll_offset_changed = false;
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetAnimationTimeForStandaloneRenderer(
    double time_ms) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const double clamped_time_ms = std::max(0.0, time_ms);
  const bool requested = clamped_time_ms > 0.001;
  if (cache.animation_time_requested == requested &&
      std::abs(cache.requested_animation_time_ms - clamped_time_ms) <= 0.001) {
    return;
  }
  cache.requested_animation_time_ms = clamped_time_ms;
  cache.applied_animation_time_ms = 0.0;
  cache.animation_time_requested = requested;
  cache.animation_time_applied = false;
  cache.animation_time_status = requested ? "pending" : "not_requested";
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetElementAttributesForStandaloneRenderer(
    const char* serialized_attributes) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string value = serialized_attributes ? serialized_attributes : "";
  if (cache.requested_element_attributes_serialized == value) {
    return;
  }
  cache.requested_element_attributes_serialized = value;
  cache.requested_element_attributes_by_id_and_name =
      ParseElementAttributesForStandaloneRenderer(value);
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
    const char* hovered_element_id,
    const char* active_element_id) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string hovered = hovered_element_id ? hovered_element_id : "";
  const std::string active = active_element_id ? active_element_id : "";
  if (cache.requested_hovered_element_id == hovered &&
      cache.requested_active_element_id == active) {
    return;
  }
  cache.requested_hovered_element_id = hovered;
  cache.requested_active_element_id = active;
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetDisableRetainedExtractionForStandaloneRenderer(
    int disabled) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool value = disabled != 0;
  if (cache.disable_retained_extraction == value) {
    return;
  }
  cache.disable_retained_extraction = value;
  cache.initialized = false;
  cache.body_html.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetForceOracleBitmapForStandaloneRenderer(
    int enabled) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool value = enabled != 0;
  if (cache.force_oracle_bitmap == value) {
    return;
  }
  cache.force_oracle_bitmap = value;
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
    int enabled) {
  ProbeCache().trace_stages = enabled != 0;
}

int StandaloneBlinkLiveFrameBridgeTraceStagesEnabledForStandaloneRenderer() {
  return ProbeCache().trace_stages ? 1 : 0;
}

void StandaloneBlinkLiveFrameBridgeSetLifecycleStopForStandaloneRenderer(
    const char* lifecycle_stop) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const std::string value = lifecycle_stop ? lifecycle_stop : "";
  if (cache.lifecycle_stop == value) {
    return;
  }
  cache.lifecycle_stop = value;
  cache.initialized = false;
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

int StandaloneBlinkLiveFrameBridgeHitTestEntryCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().hit_test_entries.size());
}

int StandaloneBlinkLiveFrameBridgeHitTestEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    float* x,
    float* y,
    float* width,
    float* height) {
  RunLiveFramePaintProbe(body_html);
  const auto& entries = ProbeCache().hit_test_entries;
  if (index < 0 || index >= static_cast<int>(entries.size())) {
    return 0;
  }
  const LiveHitTestEntry& entry = entries[static_cast<size_t>(index)];
  if (element_id && element_id_capacity > 0) {
    const size_t copied =
        std::min(entry.element_id.size(),
                 static_cast<size_t>(element_id_capacity - 1));
    std::memcpy(element_id, entry.element_id.data(), copied);
    element_id[copied] = '\0';
  }
  if (x) {
    *x = entry.x;
  }
  if (y) {
    *y = entry.y;
  }
  if (width) {
    *width = entry.width;
  }
  if (height) {
    *height = entry.height;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeScrollableElementEntryCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().scrollable_element_entries.size());
}

int StandaloneBlinkLiveFrameBridgeScrollableElementEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    float* x,
    float* y,
    float* width,
    float* height,
    float* scroll_x,
    float* scroll_y,
    float* max_scroll_x,
    float* max_scroll_y,
    int* can_scroll_x,
    int* can_scroll_y) {
  RunLiveFramePaintProbe(body_html);
  const auto& entries = ProbeCache().scrollable_element_entries;
  if (index < 0 || index >= static_cast<int>(entries.size())) {
    return 0;
  }
  const LiveScrollableElementEntry& entry =
      entries[static_cast<size_t>(index)];
  if (element_id && element_id_capacity > 0) {
    const size_t copied =
        std::min(entry.element_id.size(),
                 static_cast<size_t>(element_id_capacity - 1));
    std::memcpy(element_id, entry.element_id.data(), copied);
    element_id[copied] = '\0';
  }
  if (x) {
    *x = entry.x;
  }
  if (y) {
    *y = entry.y;
  }
  if (width) {
    *width = entry.width;
  }
  if (height) {
    *height = entry.height;
  }
  if (scroll_x) {
    *scroll_x = entry.scroll_x;
  }
  if (scroll_y) {
    *scroll_y = entry.scroll_y;
  }
  if (max_scroll_x) {
    *max_scroll_x = entry.max_scroll_x;
  }
  if (max_scroll_y) {
    *max_scroll_y = entry.max_scroll_y;
  }
  if (can_scroll_x) {
    *can_scroll_x = entry.can_scroll_x ? 1 : 0;
  }
  if (can_scroll_y) {
    *can_scroll_y = entry.can_scroll_y ? 1 : 0;
  }
  return 1;
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

int StandaloneBlinkLiveFrameBridgePaintChunkDrawableBoundsAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* x,
    int* y,
    int* width,
    int* height) {
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
    *x = chunk.drawable_bounds.x();
  }
  if (y) {
    *y = chunk.drawable_bounds.y();
  }
  if (width) {
    *width = chunk.drawable_bounds.width();
  }
  if (height) {
    *height = chunk.drawable_bounds.height();
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

int StandaloneBlinkLiveFrameBridgePaintChunkPropertyMetadataAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    uint64_t* transform_node_id,
    uint64_t* transform_parent_id,
    uint32_t* transform_chain_depth,
    uint64_t* scroll_node_id,
    uint32_t* clip_chain_depth,
    uint32_t* effect_chain_depth,
    uint64_t* effect_node_id,
    uint64_t* effect_parent_id,
    float* effect_opacity,
    int* effect_has_non_default_opacity,
    int* effect_has_filter,
    int* effect_has_backdrop_filter,
    int* effect_has_blend_mode,
    int* effect_blend_mode,
    uint64_t* effect_output_clip_id) {
  RunLiveFramePaintProbe(body_html);
  const auto& states = ProbeCache().chunk_property_states;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= states.size()) {
    return 0;
  }
  const LiveExportedChunkPropertyState& state =
      states[static_cast<size_t>(chunk_index)];
  if (transform_node_id) {
    *transform_node_id = state.transform_node_id;
  }
  if (transform_parent_id) {
    *transform_parent_id = state.transform_parent_id;
  }
  if (transform_chain_depth) {
    *transform_chain_depth = state.transform_chain_depth;
  }
  if (scroll_node_id) {
    *scroll_node_id = state.scroll_node_id;
  }
  if (clip_chain_depth) {
    *clip_chain_depth = state.clip_chain_depth;
  }
  if (effect_chain_depth) {
    *effect_chain_depth = state.effect_chain_depth;
  }
  if (effect_node_id) {
    *effect_node_id = state.effect_node_id;
  }
  if (effect_parent_id) {
    *effect_parent_id = state.effect_parent_id;
  }
  if (effect_opacity) {
    *effect_opacity = state.effect_opacity;
  }
  if (effect_has_non_default_opacity) {
    *effect_has_non_default_opacity =
        state.effect_has_non_default_opacity ? 1 : 0;
  }
  if (effect_has_filter) {
    *effect_has_filter = state.effect_has_filter ? 1 : 0;
  }
  if (effect_has_backdrop_filter) {
    *effect_has_backdrop_filter = state.effect_has_backdrop_filter ? 1 : 0;
  }
  if (effect_has_blend_mode) {
    *effect_has_blend_mode = state.effect_has_blend_mode ? 1 : 0;
  }
  if (effect_blend_mode) {
    *effect_blend_mode = state.effect_blend_mode;
  }
  if (effect_output_clip_id) {
    *effect_output_clip_id = state.effect_output_clip_id;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgePaintChunkFilterOperationCountForStandaloneRenderer(
    const char* body_html,
    int chunk_index) {
  RunLiveFramePaintProbe(body_html);
  const auto& states = ProbeCache().chunk_property_states;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= states.size()) {
    return 0;
  }
  return static_cast<int>(
      states[static_cast<size_t>(chunk_index)].effect_filter_operations.size());
}

int StandaloneBlinkLiveFrameBridgePaintChunkHasUnsupportedFilterForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* has_unsupported_filter) {
  RunLiveFramePaintProbe(body_html);
  const auto& states = ProbeCache().chunk_property_states;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= states.size()) {
    return 0;
  }
  if (has_unsupported_filter) {
    *has_unsupported_filter =
        states[static_cast<size_t>(chunk_index)].effect_has_unsupported_filter
            ? 1
            : 0;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgePaintChunkFilterOperationAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int operation_index,
    int* type,
    float* amount,
    float* offset_x,
    float* offset_y,
    float* color_r,
    float* color_g,
    float* color_b,
    float* color_a,
    float* matrix20) {
  RunLiveFramePaintProbe(body_html);
  const auto& states = ProbeCache().chunk_property_states;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= states.size()) {
    return 0;
  }
  const std::vector<LiveExportedFilterOperation>& operations =
      states[static_cast<size_t>(chunk_index)].effect_filter_operations;
  if (operation_index < 0 ||
      static_cast<size_t>(operation_index) >= operations.size()) {
    return 0;
  }
  const LiveExportedFilterOperation& operation =
      operations[static_cast<size_t>(operation_index)];
  if (type) {
    *type = operation.type;
  }
  if (amount) {
    *amount = operation.amount;
  }
  if (offset_x) {
    *offset_x = operation.offset_x;
  }
  if (offset_y) {
    *offset_y = operation.offset_y;
  }
  if (color_r) {
    *color_r = operation.color_r;
  }
  if (color_g) {
    *color_g = operation.color_g;
  }
  if (color_b) {
    *color_b = operation.color_b;
  }
  if (color_a) {
    *color_a = operation.color_a;
  }
  if (matrix20) {
    std::memcpy(matrix20, operation.matrix.data(),
                operation.matrix.size() * sizeof(float));
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgePaintChunkRoundedClipAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int* has_rounded_clip,
    float* clip_x,
    float* clip_y,
    float* clip_width,
    float* clip_height,
    float* top_left_x,
    float* top_left_y,
    float* top_right_x,
    float* top_right_y,
    float* bottom_right_x,
    float* bottom_right_y,
    float* bottom_left_x,
    float* bottom_left_y) {
  RunLiveFramePaintProbe(body_html);
  const auto& states = ProbeCache().chunk_property_states;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= states.size()) {
    return 0;
  }
  const LiveExportedChunkPropertyState& state =
      states[static_cast<size_t>(chunk_index)];
  if (has_rounded_clip) {
    *has_rounded_clip = state.has_clip_rrect ? 1 : 0;
  }
  if (clip_x) {
    *clip_x = state.clip_rrect_x;
  }
  if (clip_y) {
    *clip_y = state.clip_rrect_y;
  }
  if (clip_width) {
    *clip_width = state.clip_rrect_width;
  }
  if (clip_height) {
    *clip_height = state.clip_rrect_height;
  }
  if (top_left_x) {
    *top_left_x = state.clip_rrect_top_left_x;
  }
  if (top_left_y) {
    *top_left_y = state.clip_rrect_top_left_y;
  }
  if (top_right_x) {
    *top_right_x = state.clip_rrect_top_right_x;
  }
  if (top_right_y) {
    *top_right_y = state.clip_rrect_top_right_y;
  }
  if (bottom_right_x) {
    *bottom_right_x = state.clip_rrect_bottom_right_x;
  }
  if (bottom_right_y) {
    *bottom_right_y = state.clip_rrect_bottom_right_y;
  }
  if (bottom_left_x) {
    *bottom_left_x = state.clip_rrect_bottom_left_x;
  }
  if (bottom_left_y) {
    *bottom_left_y = state.clip_rrect_bottom_left_y;
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

int StandaloneBlinkLiveFrameBridgeChunkStableKeyAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& keys = ProbeCache().chunk_stable_keys;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= keys.size() ||
      !buffer || buffer_size <= 0) {
    return 0;
  }
  const std::string& key = keys[static_cast<size_t>(chunk_index)];
  const int copy_count =
      std::min(static_cast<int>(key.size()), buffer_size - 1);
  std::memcpy(buffer, key.data(), static_cast<size_t>(copy_count));
  buffer[copy_count] = '\0';
  return copy_count;
}

int StandaloneBlinkLiveFrameBridgeChunkIdStringAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ids = ProbeCache().chunk_id_strings;
  if (chunk_index < 0 || static_cast<size_t>(chunk_index) >= ids.size() ||
      !buffer || buffer_size <= 0) {
    return 0;
  }
  const std::string& id = ids[static_cast<size_t>(chunk_index)];
  const int copy_count =
      std::min(static_cast<int>(id.size()), buffer_size - 1);
  std::memcpy(buffer, id.data(), static_cast<size_t>(copy_count));
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
    int* stroke_cap,
    int* stroke_join,
    float* stroke_miter,
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
  if (stroke_cap) {
    *stroke_cap = op.stroke_cap;
  }
  if (stroke_join) {
    *stroke_join = op.stroke_join;
  }
  if (stroke_miter) {
    *stroke_miter = op.stroke_miter;
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

int StandaloneBlinkLiveFrameBridgeExportedSaveLayerBoundsUnsetAtForStandaloneRenderer(
    const char* body_html,
    int op_index) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  return op.save_layer_bounds_unset ? 1 : 0;
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

int StandaloneBlinkLiveFrameBridgeExportedDrawLooperLayerCountForStandaloneRenderer(
    const char* body_html,
    int op_index) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  return static_cast<int>(
      ops[static_cast<size_t>(op_index)].draw_looper_layers.size());
}

int StandaloneBlinkLiveFrameBridgeExportedDrawLooperLayerAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int layer_index,
    float* offset_x,
    float* offset_y,
    float* blur_sigma,
    float* r,
    float* g,
    float* b,
    float* a,
    uint32_t* flags) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const auto& layers = ops[static_cast<size_t>(op_index)].draw_looper_layers;
  if (layer_index < 0 || static_cast<size_t>(layer_index) >= layers.size()) {
    return 0;
  }
  const LiveExportedDrawLooperLayer& layer =
      layers[static_cast<size_t>(layer_index)];
  if (offset_x) {
    *offset_x = layer.offset_x;
  }
  if (offset_y) {
    *offset_y = layer.offset_y;
  }
  if (blur_sigma) {
    *blur_sigma = layer.blur_sigma;
  }
  if (r) {
    *r = layer.r;
  }
  if (g) {
    *g = layer.g;
  }
  if (b) {
    *b = layer.b;
  }
  if (a) {
    *a = layer.a;
  }
  if (flags) {
    *flags = layer.flags;
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

int StandaloneBlinkLiveFrameBridgeExportedPathEffectInfoAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* byte_count) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.path_effect_bytes.empty()) {
    return 0;
  }
  if (byte_count) {
    *byte_count = static_cast<int>(op.path_effect_bytes.size());
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedPathEffectBytesAtForStandaloneRenderer(
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
  if (op.path_effect_bytes.empty() ||
      destination_size < static_cast<int>(op.path_effect_bytes.size())) {
    return 0;
  }
  std::memcpy(destination, op.path_effect_bytes.data(),
              op.path_effect_bytes.size());
  return static_cast<int>(op.path_effect_bytes.size());
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
  if ((op.type != 7 && op.type != 22) || op.mask_width <= 0 ||
      op.mask_height <= 0 ||
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
  if ((op.type != 7 && op.type != 22) || op.rgba_pixels.empty() ||
      destination_size < static_cast<int>(op.rgba_pixels.size())) {
    return 0;
  }
  std::memcpy(destination, op.rgba_pixels.data(), op.rgba_pixels.size());
  return static_cast<int>(op.rgba_pixels.size());
}

int StandaloneBlinkLiveFrameBridgeExportedImageSourceRectAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    float* src_x,
    float* src_y,
    float* src_width,
    float* src_height) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() || !src_x ||
      !src_y || !src_width || !src_height) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 22) {
    return 0;
  }
  *src_x = op.src_x;
  *src_y = op.src_y;
  *src_width = op.src_width;
  *src_height = op.src_height;
  return 1;
}

int StandaloneBlinkLiveFrameBridgeExportedImageSamplingOptionsAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size() || !buffer ||
      buffer_size <= 0) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (op.type != 22) {
    return 0;
  }
  const int copy_count =
      std::min(static_cast<int>(op.sampling_options.size()), buffer_size - 1);
  std::memcpy(buffer, op.sampling_options.data(),
              static_cast<size_t>(copy_count));
  buffer[copy_count] = '\0';
  return copy_count;
}

}  // namespace blink::standalone_renderer_probe
