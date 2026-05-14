// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string_view>
#include <cmath>

#include "base/feature_list.h"
#include "components/subresource_filter/core/common/memory_mapped_ruleset.h"
#include "components/subresource_filter/core/common/scoped_rule.h"
#include "skia/ext/skcms_ext.h"
#include "ui/gfx/color_conversions.h"
#include "ui/gfx/geometry/cubic_bezier.h"
#include "ui/gfx/geometry/decomposed_transform.h"
#include "ui/gfx/geometry/quaternion.h"
#include "ui/gfx/geometry/quad_f.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/rect_f.h"
#include "ui/gfx/geometry/size_conversions.h"
#include "ui/gfx/geometry/transform.h"
#include "ui/gfx/geometry/vector2d_f.h"
#include "ui/gfx/geometry/vector3d_f.h"
#include "third_party/blink/renderer/core/css/style_color.h"
#include "third_party/blink/renderer/core/css/css_value_pool.h"
#include "third_party/blink/renderer/core/css/rule_feature_set.h"
#include "third_party/blink/renderer/core/css/css_crossfade_value.h"
#include "third_party/blink/renderer/core/css/css_image_generator_value.h"
#include "third_party/blink/renderer/core/css/css_image_set_option_value.h"
#include "third_party/blink/renderer/core/css/css_image_set_type_value.h"
#include "third_party/blink/renderer/core/css/css_image_set_value.h"
#include "third_party/blink/renderer/core/css/css_initial_value.h"
#include "third_party/blink/renderer/core/css/css_numeric_literal_value.h"
#include "third_party/blink/renderer/core/css/css_paint_value.h"
#include "third_party/blink/renderer/core/css/css_path_value.h"
#include "third_party/blink/renderer/core/css/css_quad_value.h"
#include "third_party/blink/renderer/core/css/css_url_data.h"
#include "third_party/blink/renderer/core/css/css_url_pattern_value.h"
#include "third_party/blink/renderer/core/css/css_value.h"
#include "third_party/blink/renderer/core/css/css_color_channel_keywords.h"
#include "third_party/blink/renderer/core/css/basic_shape_functions.h"
#include "third_party/blink/renderer/core/css/container_query_evaluator.h"
#include "third_party/blink/renderer/core/css/counter_style.h"
#include "third_party/blink/renderer/core/css/counter_style_map.h"
#include "third_party/blink/renderer/core/css/counters_attachment_context.h"
#include "third_party/blink/renderer/core/css/cascade_layer.h"
#include "third_party/blink/renderer/core/css/font_size_functions.h"
#include "third_party/blink/renderer/core/css/property_registration.h"
#include "third_party/blink/renderer/core/css/parser/font_variant_alternates_parser.h"
#include "third_party/blink/renderer/core/css/parser/css_variable_parser.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_context.h"
#include "third_party/blink/renderer/core/css/cssom/cross_thread_unit_value.h"
#include "third_party/blink/renderer/core/css/cssom/cross_thread_unsupported_value.h"
#include "third_party/blink/renderer/core/css/cssom/cross_thread_unparsed_value.h"
#include "third_party/blink/renderer/core/css/cssom/css_style_value.h"
#include "third_party/blink/renderer/core/css/cssom/prepopulated_computed_style_property_map.h"
#include "third_party/blink/renderer/core/css/cssom/css_keyword_value.h"
#include "third_party/blink/renderer/core/css/cssom/style_value_factory.h"
#include "third_party/blink/renderer/core/css/properties/longhand.h"
#include "third_party/blink/renderer/core/css/resolver/filter_operation_resolver.h"
#include "third_party/blink/renderer/core/css/resolver/element_style_resources.h"
#include "third_party/blink/renderer/core/css/resolver/style_adjuster.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver_state.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/css/style_rule.h"
#include "third_party/blink/renderer/core/frame/deprecation/deprecation.h"
#include "third_party/blink/renderer/core/style/style_mask_source_image.h"
#include "third_party/blink/renderer/core/style/style_path.h"
#include "third_party/blink/renderer/core/style/scoped_css_name.h"
#include "third_party/blink/renderer/core/style/filter_operation.h"
#include "third_party/blink/renderer/core/content_capture/content_capture_manager.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_context.h"
#include "third_party/blink/renderer/core/dom/flat_tree_traversal.h"
#include "third_party/blink/renderer/core/dom/nth_index_cache.h"
#include "third_party/blink/renderer/core/dom/pseudo_element.h"
#include "third_party/blink/renderer/core/editing/editing_behavior.h"
#include "third_party/blink/renderer/core/editing/ephemeral_range.h"
#include "third_party/blink/renderer/core/editing/iterators/text_iterator_behavior.h"
#include "third_party/blink/renderer/core/editing/iterators/text_iterator.h"
#include "third_party/blink/renderer/core/editing/editor.h"
#include "third_party/blink/renderer/core/editing/frame_selection.h"
#include "third_party/blink/renderer/core/editing/layout_selection.h"
#include "third_party/blink/renderer/core/editing/position.h"
#include "third_party/blink/renderer/core/editing/position_with_affinity.h"
#include "third_party/blink/renderer/core/editing/text_affinity.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/event_handler_registry.h"
#include "third_party/blink/renderer/core/frame/frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/html/html_summary_element.h"
#include "third_party/blink/renderer/core/html/forms/html_input_element.h"
#include "third_party/blink/renderer/core/html/forms/html_opt_group_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/option_list.h"
#include "third_party/blink/renderer/core/html/shadow/shadow_element_names.h"
#include "third_party/blink/renderer/core/layout/inline/abstract_inline_text_box.h"
#include "third_party/blink/renderer/core/layout/inline/fragment_item.h"
#include "third_party/blink/renderer/core/layout/inline/inline_cursor.h"
#include "third_party/blink/renderer/core/layout/inline/offset_mapping.h"
#include "third_party/blink/renderer/core/layout/anchor_position_scroll_data.h"
#include "third_party/blink/renderer/core/layout/block_node.h"
#include "third_party/blink/renderer/core/layout/custom_scrollbar.h"
#include "third_party/blink/renderer/core/layout/forms/layout_text_control.h"
#include "third_party/blink/renderer/core/layout/forms/layout_fieldset.h"
#include "third_party/blink/renderer/core/layout/ink_overflow.h"
#include "third_party/blink/renderer/core/layout/layout_block.h"
#include "third_party/blink/renderer/core/layout/layout_block_flow.h"
#include "third_party/blink/renderer/core/layout/disable_layout_side_effects_scope.h"
#include "third_party/blink/renderer/core/layout/grid/layout_grid.h"
#include "third_party/blink/renderer/core/layout/grid/grid_line_resolver.h"
#include "third_party/blink/renderer/core/layout/grid_lanes/layout_grid_lanes.h"
#include "third_party/blink/renderer/core/layout/gap/gap_geometry.h"
#include "third_party/blink/renderer/core/layout/layout_invalidation_reason.h"
#include "third_party/blink/renderer/core/layout/layout_theme.h"
#include "third_party/blink/renderer/core/layout/layout_theme_font_provider.h"
#include "third_party/blink/renderer/core/layout/layout_replaced.h"
#include "third_party/blink/renderer/core/layout/layout_counter.h"
#include "third_party/blink/renderer/core/layout/layout_image.h"
#include "third_party/blink/renderer/core/layout/layout_image_resource.h"
#include "third_party/blink/renderer/core/layout/layout_image_resource_style_image.h"
#include "third_party/blink/renderer/core/layout/layout_quote.h"
#include "third_party/blink/renderer/core/layout/list/list_marker.h"
#include "third_party/blink/renderer/core/layout/layout_text_fragment.h"
#include "third_party/blink/renderer/core/layout/table/layout_table_cell.h"
#include "third_party/blink/renderer/core/layout/layout_text_combine.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/layout/hit_test_location.h"
#include "third_party/blink/renderer/core/layout/layout_result.h"
#include "third_party/blink/renderer/core/layout/measure_cache.h"
#include "third_party/blink/renderer/core/layout/min_max_sizes.h"
#include "third_party/blink/renderer/core/layout/outline_rect_collector.h"
#include "third_party/blink/renderer/core/layout/physical_box_fragment.h"
#include "third_party/blink/renderer/core/layout/physical_fragment.h"
#include "third_party/blink/renderer/core/layout/scroll_anchor.h"
#include "third_party/blink/renderer/core/layout/scrollable_overflow_calculator.h"
#include "third_party/blink/renderer/core/layout/shapes/shape_outside_info.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_text.h"
#include "third_party/blink/renderer/core/layout/svg/transform_helper.h"
#include "third_party/blink/renderer/core/svg/svg_path_byte_stream_builder.h"
#include "third_party/blink/renderer/core/svg/svg_path_utilities.h"
#include "third_party/blink/renderer/core/layout/hit_test_result.h"
#include "third_party/blink/renderer/core/layout/anchor_map.h"
#include "third_party/blink/renderer/core/layout/anchor_scope.h"
#include "third_party/blink/renderer/core/loader/resource/image_resource_content.h"
#include "third_party/blink/renderer/core/overscroll/overscroll_area_tracker.h"
#include "third_party/blink/renderer/core/paint/block_paint_invalidator.h"
#include "third_party/blink/renderer/core/paint/box_paint_invalidator.h"
#include "third_party/blink/renderer/core/paint/box_fragment_painter.h"
#include "third_party/blink/renderer/core/paint/fragment_data.h"
#include "third_party/blink/renderer/core/paint/inline_paint_context.h"
#include "third_party/blink/renderer/core/paint/object_paint_invalidator.h"
#include "third_party/blink/renderer/core/paint/outline_painter.h"
#include "third_party/blink/renderer/core/paint/paint_layer.h"
#include "third_party/blink/renderer/core/paint/pre_paint_disable_side_effects_scope.h"
#include "third_party/blink/renderer/core/paint/paint_layer_scrollable_area.h"
#include "third_party/blink/renderer/core/paint/timing/image_element_timing.h"
#include "third_party/blink/renderer/core/paint/timing/paint_timing_detector.h"
#include "third_party/blink/renderer/core/paint/text_overflow_post_layout_snapshot.h"
#include "third_party/blink/renderer/core/page/chrome_client.h"
#include "third_party/blink/renderer/core/scroll/scroll_alignment.h"
#include "third_party/blink/renderer/core/scroll/scroll_into_view_util.h"
#include "third_party/blink/renderer/core/svg/svg_resource.h"
#include "third_party/blink/renderer/core/layout/svg/svg_resources.h"
#include "third_party/blink/renderer/core/page/scrolling/sticky_position_scrolling_constraints.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/bindings/exception_state.h"
#include "third_party/blink/renderer/platform/bindings/wrapper_type_info.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/theme/web_theme_engine_helper.h"
#include "third_party/blink/renderer/platform/text/platform_locale.h"
#include "third_party/blink/renderer/platform/text/writing_mode.h"
#include "third_party/blink/renderer/platform/transforms/affine_transform.h"
#include "third_party/blink/renderer/platform/graphics/paint/geometry_mapper.h"
#include "third_party/blink/renderer/platform/graphics/paint/clip_paint_property_node.h"
#include "third_party/blink/renderer/platform/graphics/paint/effect_paint_property_node.h"
#include "third_party/blink/renderer/platform/graphics/paint/transform_paint_property_node.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/transforms/transform_operations.h"
#include "third_party/blink/renderer/platform/wtf/text/text_offset_map.h"
#include "third_party/blink/renderer/platform/graphics/compositor_filter_operations.h"
#include "third_party/blink/renderer/platform/heap/thread_state.h"
#include "third_party/blink/renderer/platform/fonts/font_cache.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_context.h"
#include "third_party/blink/renderer/core/scroll/scrollbar.h"
#include "third_party/blink/renderer/core/layout/outline_utils.h"
#include "third_party/blink/renderer/core/layout/geometry/physical_rect.h"
#include "third_party/blink/renderer/core/layout/geometry/transform_state.h"
#include "third_party/blink/renderer/core/layout/geometry/writing_mode_converter.h"
#include "third_party/blink/renderer/platform/graphics/image.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_image_cache.h"
#include "third_party/blink/renderer/platform/graphics/generated_image.h"
#include "third_party/blink/renderer/platform/graphics/gradient_generated_image.h"
#include "third_party/blink/renderer/platform/graphics/gradient.h"
#include "third_party/blink/renderer/platform/graphics/filters/filter.h"
#include "third_party/blink/renderer/platform/instrumentation/instance_counters.h"
#include "third_party/blink/renderer/platform/fonts/font.h"
#include "third_party/blink/renderer/platform/fonts/font_platform_data.h"
#include "third_party/blink/renderer/platform/fonts/simple_font_data.h"
#include "third_party/blink/renderer/platform/fonts/font_variant_alternates.h"
#include "third_party/blink/renderer/platform/fonts/opentype/open_type_math_support.h"
#include "third_party/blink/renderer/platform/geometry/length.h"
#include "third_party/blink/renderer/platform/text/character_break_iterator.h"
#include "third_party/blink/renderer/platform/timer.h"
#include "third_party/blink/renderer/platform/wtf/text/text_offset_map.h"
#include "base/task/delayed_task_handle.h"
#include "base/task/task_runner.h"
#include "cc/base/region.h"
#include "ui/gfx/geometry/transform.h"

namespace subresource_filter {

ScopedRule::ScopedRule(const ScopedRule&) : ruleset_(nullptr), rule_(nullptr) {}
ScopedRule::~ScopedRule() = default;
MemoryMappedRuleset::~MemoryMappedRuleset() = default;

}  // namespace subresource_filter

namespace url {

Parsed::Parsed() = default;
Parsed::Parsed(const Parsed&) = default;
Parsed& Parsed::operator=(const Parsed&) = default;
Parsed::~Parsed() = default;

}  // namespace url

namespace base {

DelayedTaskHandle::DelayedTaskHandle() = default;
DelayedTaskHandle::~DelayedTaskHandle() = default;

void TaskRunnerTraits::Destruct(const TaskRunner*) {}

}  // namespace base

namespace gfx {

std::tuple<float, float, float> LabToXYZD50(float l, float a, float b) {
  return {l, a, b};
}
std::tuple<float, float, float> XYZD50ToLab(float x, float y, float z) {
  return {x, y, z};
}
std::tuple<float, float, float> OklabToXYZD50(float l, float a, float b, bool) {
  return {l, a, b};
}
std::tuple<float, float, float> XYZD50ToOklab(float x, float y, float z) {
  return {x, y, z};
}
std::tuple<float, float, float> LchToLab(float l, float c, float h) {
  return {l, c, h};
}
std::tuple<float, float, float> LabToLch(float l, float a, float b) {
  return {l, a, b};
}
std::tuple<float, float, float> SRGBToSRGBLegacy(float r, float g, float b) {
  return {r * 255.0f, g * 255.0f, b * 255.0f};
}
std::tuple<float, float, float> SRGBLegacyToSRGB(float r, float g, float b) {
  return {r / 255.0f, g / 255.0f, b / 255.0f};
}
std::tuple<float, float, float> XYZD50ToSRGB(float x, float y, float z) {
  return {x, y, z};
}
std::tuple<float, float, float> SRGBToXYZD50(float r, float g, float b) {
  return {r, g, b};
}
std::tuple<float, float, float> HSLToSRGB(float h, float s, float l) {
  return {h, s, l};
}
std::tuple<float, float, float> SRGBToHSL(float r, float g, float b) {
  return {r, g, b};
}
std::tuple<float, float, float> HWBToSRGB(float h, float w, float b) {
  return {h, w, b};
}
std::tuple<float, float, float> SRGBToHWB(float r, float g, float b) {
  return {r, g, b};
}

}  // namespace gfx

namespace skcms {

Vector3 Matrix3x3_apply(const skcms_Matrix3x3&, const Vector3& v) {
  return v;
}
Vector3 Matrix3x3_apply_inverse(const skcms_Matrix3x3&,
                                const Vector3& v,
                                bool* succeeded) {
  if (succeeded) {
    *succeeded = true;
  }
  return v;
}
Vector3 TransferFunction_apply(const skcms_TransferFunction&,
                               const Vector3& v) {
  return v;
}
Vector3 TransferFunction_apply_inverse(const skcms_TransferFunction&,
                                       const Vector3& v,
                                       bool* succeeded) {
  if (succeeded) {
    *succeeded = true;
  }
  return v;
}

}  // namespace skcms

bool SkColorSpacePrimaries::toXYZD50(skcms_Matrix3x3* toXYZD50) const {
  if (toXYZD50) {
    *toXYZD50 = {{
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
    }};
  }
  return true;
}

namespace blink {

namespace features {

extern constinit const base::Feature kBakedGamutMapping(
    "BakedGamutMapping",
    base::FEATURE_DISABLED_BY_DEFAULT,
    base::internal::FeatureMacroHandshake::kSecret);

}  // namespace features

namespace font_family_names {

const AtomicString& kMonospace = *new AtomicString("monospace");
const AtomicString& kCursive = *new AtomicString("cursive");
const AtomicString& kSerif = *new AtomicString("serif");
const AtomicString& kSansSerif = *new AtomicString("sans-serif");
const AtomicString& kFantasy = *new AtomicString("fantasy");
const AtomicString& kMath = *new AtomicString("math");
const AtomicString& kSystemUi = *new AtomicString("system-ui");

}  // namespace font_family_names

namespace keywords {

const AtomicString& kCircle = *new AtomicString("circle");
const AtomicString& kDecimal = *new AtomicString("decimal");
const AtomicString& kDisc = *new AtomicString("disc");
const AtomicString& kInternalPrintFooter =
    *new AtomicString("-internal-print-footer");
const AtomicString& kInternalPrintHeader =
    *new AtomicString("-internal-print-header");
const AtomicString& kInternalPrintPageNumber =
    *new AtomicString("-internal-print-page-number");
const AtomicString& kSquare = *new AtomicString("square");
const AtomicString& kDisclosureOpen = *new AtomicString("disclosure-open");
const AtomicString& kDisclosureClosed =
    *new AtomicString("disclosure-closed");

}  // namespace keywords

namespace shadow_element_names {

const AtomicString kPseudoInternalInputSuggested(
    "pseudo-internal-input-suggested");
const AtomicString kIdSpinButton("-webkit-inner-spin-button");

}  // namespace shadow_element_names

bool RuntimeEnabledFeaturesBase::is_first_line_on_list_item_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_text_overflow_clip_with_selection_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_disable_ellipsis_when_scrolled_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_use_original_dom_offsets_for_offset_map_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_corners_shorthand_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_spacing_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_single_axis_scroll_containers_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_layout_ignore_margins_for_sticky_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_overlay_property_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_safe_printable_inset_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_svg_path_length_css_property_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_functions_enabled_ = true;
bool RuntimeEnabledFeaturesBase::is_css_ruby_overhang_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_initial_target_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_target_group_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_decoration_skip_spaces_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_fit_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scoped_view_transitions_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_offset_path_transform_update_fix_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_polygon_rounding_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_transform_full_size_kana_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_transform_full_width_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_transform_multi_keyword_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_overflow_string_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_paint_api_arguments_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_timeline_scope_all_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_overlay_global_rule_removal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_overscroll_behavior_chain_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_align_match_parent_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_appearance_base_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_decoration_skip_ink_all_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_user_select_contain_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_resize_auto_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_view_transition_auto_name_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_css_shape_outside_path_and_shape_support_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_shape_outside_rect_and_xywh_support_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_indent_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_indent_as_primitive_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_css_shape_ellipse_circle_position_serialization_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_forced_colors_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_event_trigger_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_animation_trigger_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_route_matching_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_border_shape_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_caret_animation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_caret_shape_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_multicol_column_wrapping_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_dynamic_range_limit_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_responsive_iframes_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_hanging_punctuation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_image_animation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_overscroll_gestures_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_margin_trim_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scrollbar_width_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_ident_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_url_request_modifiers_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_alpha_color_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_contrast_color_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_light_dark_image_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_cross_fade_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_hex_alpha_color_enabled_ = true;
bool RuntimeEnabledFeaturesBase::is_css_typed_arithmetic_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_progress_notation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_random_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_media_progress_notation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_container_progress_notation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_pseudo_elements_focusable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_scroll_markers_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scrollbar_color_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_font_style_oblique_zero_degree_as_normal_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_font_family_serialization_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_background_clip_border_area_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_color_space_rec_2100_linear_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_color_space_display_p_3_linear_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_font_format_avar_2_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_line_clamp_line_breaking_ellipsis_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_display_contents_focusable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_quote_first_line_style_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_flex_wrap_balance_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_letter_and_word_spacing_percentage_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_disable_anchor_center_on_align_justify_items_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_side_relative_background_position_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_decouple_computed_border_width_from_style_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_alt_counter_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_counter_reset_reversed_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_layout_api_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_position_sticky_static_scroll_position_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_html_printing_artifact_annotations_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_blink_geometry_mapper_viewport_fast_path_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_fix_visual_rect_remote_viewport_transform_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_layout_box_rect_getters_use_fragments_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_visual_rect_mapping_fix_for_expansion_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_anchor_with_transforms_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_stacking_context_is_not_stacked_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_revert_rule_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_composite_clip_path_animation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_search_text_highlight_pseudo_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_composite_bg_color_animation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_line_clamp_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_timeline_trigger_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_grid_lanes_layout_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_font_size_adjust_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_font_language_override_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_text_emphasis_position_auto_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_accent_color_keyword_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_non_standard_appearance_value_slider_vertical_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scroll_timeline_named_range_scroll_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_outline_draw_auto_style_zero_width_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_grid_gap_suppression_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_gap_decoration_enabled_ = false;

bool RuntimeEnabledFeaturesBase::CanvasDrawElementEnabled(
    const FeatureContext*) {
  return false;
}

String CSSStyleValue::toString() const {
  const CSSValue* value = ToCSSValue();
  return value ? value->CssText() : g_empty_string;
}

bool CSSValue::operator==(const CSSValue& other) const {
  return this == &other;
}

bool CSSValue::HasRandomFunctions() const {
  return false;
}

CSSInitialValue* CSSInitialValue::Create() {
  return nullptr;
}

CSSStyleValue* CrossThreadUnparsedValue::ToCSSStyleValue() {
  return nullptr;
}

std::unique_ptr<CrossThreadStyleValue> CrossThreadUnparsedValue::IsolatedCopy()
    const {
  return std::make_unique<CrossThreadUnparsedValue>(value_);
}

bool CrossThreadUnparsedValue::operator==(
    const CrossThreadStyleValue& other) const {
  if (auto* o = DynamicTo<CrossThreadUnparsedValue>(other)) {
    return value_ == o->value_;
  }
  return false;
}

CSSStyleValue* CrossThreadUnitValue::ToCSSStyleValue() {
  return nullptr;
}

std::unique_ptr<CrossThreadStyleValue> CrossThreadUnitValue::IsolatedCopy()
    const {
  return std::make_unique<CrossThreadUnitValue>(value_, unit_);
}

bool CrossThreadUnitValue::operator==(
    const CrossThreadStyleValue& other) const {
  if (auto* o = DynamicTo<CrossThreadUnitValue>(other)) {
    return value_ == o->value_ && unit_ == o->unit_;
  }
  return false;
}

CSSStyleValue* CrossThreadUnsupportedValue::ToCSSStyleValue() {
  return nullptr;
}

std::unique_ptr<CrossThreadStyleValue>
CrossThreadUnsupportedValue::IsolatedCopy() const {
  return std::make_unique<CrossThreadUnsupportedValue>(value_);
}

bool CrossThreadUnsupportedValue::operator==(
    const CrossThreadStyleValue& other) const {
  if (auto* o = DynamicTo<CrossThreadUnsupportedValue>(other)) {
    return value_ == o->value_;
  }
  return false;
}

CSSStyleValue* StyleValueFactory::CssValueToStyleValue(
    const CSSPropertyName&,
    const CSSValue&) {
  return nullptr;
}

String ToString(unsigned value) {
  return String::Number(value);
}

}  // namespace blink

namespace color_utils {

float GetContrastRatio(SkColor color_a, SkColor color_b) {
  auto luminance = [](SkColor color) {
    const float r = SkColorGetR(color) / 255.0f;
    const float g = SkColorGetG(color) / 255.0f;
    const float b = SkColorGetB(color) / 255.0f;
    return 0.2126f * r + 0.7152f * g + 0.0722f * b;
  };
  const float a = luminance(color_a);
  const float b = luminance(color_b);
  const float lighter = std::max(a, b);
  const float darker = std::min(a, b);
  return (lighter + 0.05f) / (darker + 0.05f);
}

}  // namespace color_utils

namespace blink {

namespace mojom {

std::ostream& operator<<(std::ostream& stream, WebFeature) {
  return stream << "WebFeature";
}

}  // namespace mojom

std::ostream& operator<<(std::ostream& stream,
                         PaintInvalidationReason reason) {
  return stream << static_cast<int>(reason);
}

void Deprecation::CountDeprecation(ExecutionContext*, WebFeature) {}

void CounterStyle::Trace(Visitor* visitor) const {
  visitor->Trace(style_rule_);
  visitor->Trace(cascade_layer_);
  visitor->Trace(extended_style_);
  visitor->Trace(fallback_style_);
  visitor->Trace(speak_as_style_);
}

const AtomicString& LayoutThemeFontProvider::SystemFontFamily(CSSValueID) {
  return font_family_names::kSansSerif;
}

float LayoutThemeFontProvider::SystemFontSize(CSSValueID,
                                              const Document*) {
  return 16.0f;
}

String FontCache::FirstAvailableOrFirst(const String& families) {
  if (families.empty()) {
    return families;
  }
  wtf_size_t comma = families.find(',');
  return comma == kNotFound ? families : families.substr(0, comma).StripWhiteSpace();
}

FontOrientation ComputedStyleBuilder::ComputeFontOrientation() const {
  return FontOrientation::kHorizontal;
}

ReferenceFilterOperation::ReferenceFilterOperation(const AtomicString& url,
                                                   SVGResource* resource)
    : FilterOperation(OperationType::kReference),
      url_(url),
      resource_(resource) {}

void ReferenceFilterOperation::Trace(Visitor* visitor) const {
  visitor->Trace(resource_);
  visitor->Trace(filter_);
  FilterOperation::Trace(visitor);
}

gfx::RectF ReferenceFilterOperation::MapRect(const gfx::RectF& rect) const {
  return rect;
}

void ReferenceFilterOperation::AddClient(SVGResourceClient&) {}

void ReferenceFilterOperation::RemoveClient(SVGResourceClient&) {}

bool ReferenceFilterOperation::IsEqualAssumingSameType(
    const FilterOperation& o) const {
  const auto& other = To<ReferenceFilterOperation>(o);
  return url_ == other.url_ && resource_ == other.resource_ &&
         filter_.Get() == other.filter_.Get();
}

GapSegmentState GapGeometry::GetIntersectionGapSegmentState(
    GridTrackSizingDirection,
    wtf_size_t,
    wtf_size_t) const {
  return GapSegmentState();
}

BlockedStatus GapGeometry::GetIntersectionBlockedStatus(
    GridTrackSizingDirection,
    wtf_size_t,
    wtf_size_t,
    const Vector<GapIntersection>&) const {
  return BlockedStatus();
}

const TransformPaintPropertyNodeOrAlias& FragmentData::ContentsTransform()
    const {
  return LocalBorderBoxProperties().Transform();
}

const ClipPaintPropertyNodeOrAlias& FragmentData::ContentsClip() const {
  return LocalBorderBoxProperties().Clip();
}

const EffectPaintPropertyNodeOrAlias& FragmentData::ContentsEffect() const {
  return LocalBorderBoxProperties().Effect();
}

void FragmentData::RareData::Trace(Visitor* visitor) const {
  visitor->Trace(layer);
  visitor->Trace(x_sticky_constraints);
  visitor->Trace(y_sticky_constraints);
  visitor->Trace(additional_fragments);
  visitor->Trace(paint_properties);
  visitor->Trace(local_border_box_properties);
}

bool LocalFrameView::MapToVisualRectInRemoteRootFrame(PhysicalRect&,
                                                      bool,
                                                      bool,
                                                      bool) {
  return true;
}

bool LocalFrameView::NeedsLayout() const {
  return false;
}

void LocalFrameView::ClearLayoutSubtreeRoot(const LayoutObject&) {}

bool LocalFrameView::RemovePendingTransformUpdate(const LayoutObject&) {
  return false;
}

bool LocalFrameView::RemovePendingOpacityUpdate(const LayoutObject&) {
  return false;
}

void LocalFrameView::SetIntersectionObservationState(
    IntersectionObservationState) {}

void LocalFrameView::AddBackgroundAttachmentFixedObject(LayoutBoxModelObject&) {}

void LocalFrameView::RemoveBackgroundAttachmentFixedObject(
    LayoutBoxModelObject&) {}

bool LayoutSelection::IsSelected(const LayoutObject&) {
  return false;
}

void StyleAdjuster::AdjustStyleForCombinedText(ComputedStyleBuilder&) {}

OverscrollAreaTracker* Element::GetOverscrollAreaTracker() const {
  return nullptr;
}

const VectorOf<Element>& OverscrollAreaTracker::DOMSortedElements() {
  static const VectorOf<Element> empty;
  return empty;
}

EventHandlerRegistry& LocalFrame::GetEventHandlerRegistry() const {
  alignas(EventHandlerRegistry) static char registry_storage[sizeof(EventHandlerRegistry)];
  return *reinterpret_cast<EventHandlerRegistry*>(registry_storage);
}

const EventTargetSet* EventHandlerRegistry::EventHandlerTargets(
    EventHandlerClass) const {
  return nullptr;
}

void EventHandlerRegistry::DidAddEventHandler(EventTarget&,
                                              EventHandlerClass) {}

void EventHandlerRegistry::DidRemoveEventHandler(EventTarget&,
                                                 EventHandlerClass) {}

void PaintTimingDetector::ReportIgnoredContent() {}

void PaintTimingDetector::NotifyImageFinished(const LayoutObject&,
                                              const MediaTiming*) {}

void PaintTimingDetector::NotifyImageRemoved(const LayoutObject&,
                                             const ImageResourceContent*) {}

void ScrollAnchor::Clear() {}

bool ScrollAnchor::RefersTo(const LayoutObject*) const {
  return false;
}

void ScrollAnchor::NotifyRemoved(LayoutObject*) {}

void Node::FocusabilityLost() {}

void Node::SetNeedsStyleRecalc(StyleChangeType,
                               const StyleChangeReasonForTracing&) {}

HeapHashSet<Member<TreeScope>> Node::GetAncestorTreeScopes() const {
  return {};
}

bool Element::MayBeImplicitAnchor() const {
  return false;
}

const ComputedStyle* Element::CachedStyleForPseudoElement(
    PseudoId,
    const AtomicString&) {
  return nullptr;
}

const ComputedStyle* Element::UncachedStyleForPseudoElement(
    const StyleRequest&) {
  return nullptr;
}

void Element::SetIsAdRelated(AdProvenance) {}

Element* Document::scrollingElement() {
  return nullptr;
}

Element* Document::ScrollingElementNoLayout() {
  return nullptr;
}

bool Document::hidden() const {
  return false;
}

bool ExecutionContext::IsContextPaused() const {
  return false;
}

const ComputedStyle* ComputedStyle::AddCachedPseudoElementStyle(
    const ComputedStyle* pseudo_style,
    PseudoId,
    const AtomicString&) const {
  return pseudo_style;
}

const ComputedStyle* ComputedStyle::ReplaceCachedPseudoElementStyle(
    const ComputedStyle* pseudo_style,
    PseudoId,
    const AtomicString&) const {
  return pseudo_style;
}

InterpolationQuality ComputedStyle::GetInterpolationQuality() const {
  return kInterpolationMedium;
}

bool ComputedStyle::operator==(const ComputedStyle& other) const {
  return this == &other;
}

void ComputedStyle::ApplyTransform(
    gfx::Transform&,
    const LayoutBox*,
    const gfx::RectF&,
    ApplyTransformOperations,
    ApplyTransformOrigin,
    ApplyMotionPath,
    ApplyIndependentTransformProperties) const {}

void ComputedStyle::ApplyTransform(
    gfx::Transform&,
    const LayoutBox*,
    const PhysicalRect&,
    ApplyTransformOperations,
    ApplyTransformOrigin,
    ApplyMotionPath,
    ApplyIndependentTransformProperties) const {}

const CounterDirectiveMap* ComputedStyle::GetCounterDirectives() const {
  return nullptr;
}

Color ComputedStyle::GetInternalVisitedCurrentColor(bool*) const {
  return Color::kBlack;
}

Color ComputedStyle::GetInternalForcedCurrentColor(bool*) const {
  return Color::kBlack;
}

Color ComputedStyle::ResolvedColor(const StyleColor&, bool*) const {
  return Color::kBlack;
}

StyleColor ComputedStyle::DecorationColorIncludingFallback(bool) const {
  return StyleColor(Color::kBlack);
}

StyleScrollbarColor* ComputedStyle::UsedScrollbarColor() const {
  return nullptr;
}

TextDecorationLine ComputedStyle::TextDecorationsInEffect() const {
  return TextDecorationLine::kNone;
}

bool ComputedStyle::HasBackground() const {
  return false;
}

TextEmphasisMark ComputedStyle::GetTextEmphasisMark() const {
  return TextEmphasisMark::kNone;
}

void ComputedStyleBuilder::SetUsedColorScheme(
    ColorSchemeFlags,
    mojom::blink::PreferredColorScheme,
    bool) {}

Color LayoutTheme::TapHighlightColor() {
  return Color::kTransparent;
}

LayoutTheme& LayoutTheme::GetTheme() {
  alignas(LayoutTheme) static unsigned char storage[sizeof(LayoutTheme)] = {};
  return *reinterpret_cast<LayoutTheme*>(storage);
}

gfx::RectF TransformHelper::ComputeReferenceBox(const LayoutObject&) {
  return gfx::RectF();
}

bool Longhand::ApplyParentValueIfZoomChanged(StyleResolverState&) const {
  return false;
}

void StyleResolverState::SetPositionAnchor(const StylePositionAnchor&) {}

void StyleResolverState::SetPositionAreaOffsets(
    const std::optional<PositionAreaOffsets>&) {}

void StyleResolverState::SetTextOrientation(ETextOrientation) {}

void StyleResolverState::SetWritingMode(WritingMode) {}

void StyleResolverState::SetTextSizeAdjust(TextSizeAdjust) {}

void StyleResolverState::SetZoom(float) {}

const LayoutLocale* LayoutLocale::Get(const AtomicString&) {
  return nullptr;
}

bool Element::HasElementFlag(ElementFlags) const {
  return false;
}

DisplayLockContext* Element::GetDisplayLockContextFromRareData() const {
  return nullptr;
}

bool DisplayLockContext::ActivatableDisplayLocksForced() const {
  return false;
}

bool DisplayLockContext::IsScreenReaderActive() const {
  return false;
}

bool DisplayLockContext::ShouldActivateForScreenReader() const {
  return false;
}

bool TreeScope::IsInclusiveAncestorTreeScopeOf(const TreeScope&) const {
  return false;
}

Document* Node::ownerDocument() const {
  return nullptr;
}

std::ostream& operator<<(std::ostream& stream, const Node&) {
  return stream << "Node";
}

std::ostream& operator<<(std::ostream& stream, TextDirection direction) {
  return stream << static_cast<int>(direction);
}

const gfx::Transform& TransformState::AccumulatedTransform() const {
  static const gfx::Transform* identity = new gfx::Transform();
  return *identity;
}

HitTestLocation::HitTestLocation(const PhysicalRect& rect)
    : point_(rect.offset),
      bounding_box_(rect),
      transformed_point_(gfx::PointF(rect.offset)),
      transformed_rect_(gfx::QuadF(gfx::RectF(gfx::PointF(rect.offset),
                                              gfx::SizeF(rect.size)))),
      is_rect_based_(true),
      is_rectilinear_(true) {}

HitTestLocation::HitTestLocation(const HitTestLocation&) = default;

HitTestResult::HitTestResult()
    : hit_test_request_(HitTestRequest::kReadOnly),
      cacheable_(true),
      is_over_embedded_content_view_(false) {}

void HitTestResult::SetInnerNode(Node* node) {
  inner_node_ = node;
  inner_possibly_pseudo_node_ = node;
}

ImageElementTiming& ImageElementTiming::From(LocalDOMWindow&) {
  alignas(ImageElementTiming) static char timing_storage[sizeof(ImageElementTiming)];
  return *reinterpret_cast<ImageElementTiming*>(timing_storage);
}

void ImageElementTiming::NotifyImageFinished(
    const LayoutObject&,
    const ImageResourceContent*) {}

void ImageElementTiming::NotifyImageRemoved(
    const LayoutObject*,
    const ImageResourceContent*) {}

bool ImageResourceContent::ErrorOccurred() const {
  return true;
}

const std::optional<AdProvenance>& ImageResourceContent::GetAdProvenance()
    const {
  static const std::optional<AdProvenance>* provenance =
      new std::optional<AdProvenance>();
  return *provenance;
}

bool ThreadState::IsSweepingOnOwningThread() const {
  return false;
}

bool LayoutGrid::HasCachedPlacementData() const {
  return false;
}

const GridPlacementData& LayoutGrid::CachedPlacementData() const {
  return *static_cast<const GridPlacementData*>(nullptr);
}

Vector<LayoutUnit> LayoutGrid::GridTrackPositions(
    GridTrackSizingDirection) const {
  return {};
}

Vector<LayoutUnit, 1> LayoutGrid::TrackSizesForComputedStyle(
    GridTrackSizingDirection) const {
  return {};
}

wtf_size_t LayoutGrid::ExplicitGridStartForDirection(
    GridTrackSizingDirection) const {
  return 0;
}

wtf_size_t LayoutGrid::ExplicitGridEndForDirection(
    GridTrackSizingDirection) const {
  return 0;
}

wtf_size_t LayoutGrid::AutoRepeatCountForDirection(
    GridTrackSizingDirection) const {
  return 0;
}

bool LayoutGridLanes::HasCachedPlacementData() const {
  return false;
}

const GridPlacementData& LayoutGridLanes::CachedPlacementData() const {
  return *static_cast<const GridPlacementData*>(nullptr);
}

Vector<LayoutUnit> LayoutGridLanes::GridTrackPositions(
    GridTrackSizingDirection) const {
  return {};
}

Vector<LayoutUnit, 1> LayoutGridLanes::TrackSizesForComputedStyle(
    GridTrackSizingDirection) const {
  return {};
}

wtf_size_t LayoutGridLanes::ExplicitGridStartForDirection(
    GridTrackSizingDirection) const {
  return 0;
}

wtf_size_t LayoutGridLanes::ExplicitGridEndForDirection(
    GridTrackSizingDirection) const {
  return 0;
}

wtf_size_t LayoutGridLanes::AutoRepeatCountForDirection(
    GridTrackSizingDirection) const {
  return 0;
}

wtf_size_t GridLineResolver::SubgridSpanSize(GridTrackSizingDirection) const {
  return 0;
}

KURL::KURL()
    : is_valid_(false), protocol_is_in_http_family_(false), string_() {}

KURL::KURL(const KURL& other)
    : is_valid_(other.is_valid_),
      protocol_is_in_http_family_(other.protocol_is_in_http_family_),
      protocol_(other.protocol_),
      parsed_(other.parsed_),
      string_(other.string_) {}

KURL::~KURL() = default;

KURL& KURL::operator=(const KURL& other) {
  if (this != &other) {
    is_valid_ = other.is_valid_;
    protocol_is_in_http_family_ = other.protocol_is_in_http_family_;
    protocol_ = other.protocol_;
    parsed_ = other.parsed_;
    string_ = other.string_;
    inner_url_.reset();
  }
  return *this;
}

KURL::KURL(const StringView& string)
    : is_valid_(!string.IsNull()),
      protocol_is_in_http_family_(false),
      string_(AtomicString(string.ToString())) {}

KURL::KURL(const KURL&, const StringView& relative)
    : KURL(relative) {}

KURL::KURL(const KURL&, const StringView& relative, const TextEncoding&)
    : KURL(relative) {}

StringView KURL::FragmentIdentifier() const {
  return StringView();
}

bool KURL::IsNull() const {
  return string_.IsNull();
}

bool KURL::IsEmpty() const {
  return string_.empty();
}

bool KURL::IsValid() const {
  return is_valid_;
}

String DecodeUrlEscapeSequences(const StringView& string, DecodeUrlMode) {
  return string.ToString();
}

const KURL& NullUrl() {
  DEFINE_STATIC_LOCAL(KURL, null_url, ());
  return null_url;
}

bool operator==(const KURL& a, const KURL& b) {
  return a.GetString() == b.GetString();
}

bool ProtocolIs(const StringView& url, const char* protocol) {
  String prefix = String(protocol) + ":";
  return url.ToString().StartsWithIgnoringAsciiCase(prefix);
}

Referrer::Referrer()
    : referrer(Referrer::NoReferrer()),
      referrer_policy(network::mojom::ReferrerPolicy::kDefault) {}

CSSUrlData::CSSUrlData(const AtomicString& unresolved_url,
                       const KURL& resolved_url,
                       const Referrer& referrer,
                       bool is_from_origin_clean_style_sheet,
                       bool is_ad_related,
                       const CSSUrlRequestModifiers& modifiers)
    : relative_url_(unresolved_url),
      absolute_url_(resolved_url.GetString()),
      referrer_(referrer),
      is_local_(unresolved_url.StartsWithIgnoringAsciiCase("#")),
      is_from_origin_clean_style_sheet_(is_from_origin_clean_style_sheet),
      is_ad_related_(is_ad_related),
      potentially_dangling_markup_(false),
      modifiers_(modifiers) {}

CSSUrlData::CSSUrlData(base::PassKey<CSSUrlData>,
                       const AtomicString& unresolved_url,
                       const AtomicString& resolved_url,
                       const Referrer& referrer,
                       bool is_from_origin_clean_style_sheet,
                       bool is_ad_related,
                       bool is_local,
                       bool potentially_dangling_markup,
                       const CSSUrlRequestModifiers& modifiers)
    : relative_url_(unresolved_url),
      absolute_url_(resolved_url),
      referrer_(referrer),
      is_local_(is_local),
      is_from_origin_clean_style_sheet_(is_from_origin_clean_style_sheet),
      is_ad_related_(is_ad_related),
      potentially_dangling_markup_(potentially_dangling_markup),
      modifiers_(modifiers) {}

CSSUrlData::CSSUrlData(const AtomicString& resolved_url)
    : relative_url_(resolved_url),
      absolute_url_(resolved_url),
      referrer_(Referrer()),
      is_local_(resolved_url.StartsWithIgnoringAsciiCase("#")),
      is_from_origin_clean_style_sheet_(true),
      is_ad_related_(false),
      potentially_dangling_markup_(false),
      modifiers_(CSSUrlRequestModifiers()) {}

bool CSSUrlData::ReResolveUrl(const Document&) const {
  return false;
}

const CSSUrlData* CSSUrlData::MakeResolved(const KURL&,
                                           const TextEncoding&) const {
  return this;
}

bool CSSUrlData::IsLocal(const Document&) const {
  return is_local_;
}

String CSSUrlData::CssText() const {
  return relative_url_.GetString();
}

bool CSSUrlData::operator==(const CSSUrlData& other) const {
  return relative_url_ == other.relative_url_ && absolute_url_ == other.absolute_url_;
}

CSSURLPatternValue::CSSURLPatternValue(const AtomicString& url_string)
    : CSSValue(kURLPatternClass), url_string_(url_string) {}

CSSURLPatternValue::~CSSURLPatternValue() = default;

String CSSURLPatternValue::CustomCSSText() const {
  return url_string_;
}

bool CSSURLPatternValue::Equals(const CSSURLPatternValue& other) const {
  return url_string_ == other.url_string_;
}

void CSSURLPatternValue::TraceAfterDispatch(Visitor* visitor) const {
  CSSValue::TraceAfterDispatch(visitor);
}

ExternalSVGResourceDocumentContent::ExternalSVGResourceDocumentContent(
    const KURL&,
    const CSSUrlRequestModifiers&) {}

void ExternalSVGResourceDocumentContent::Load(Document&,
                                              CrossOriginAttributeValue) {}

void ExternalSVGResourceDocumentContent::LoadWithoutCSP(Document&) {}

void ExternalSVGResourceDocumentContent::Trace(Visitor* visitor) const {
  SVGResource::Trace(visitor);
}

bool ExternalSVGResourceDocumentContent::IsLoading() const {
  return false;
}

Element* ExternalSVGResourceDocumentContent::ResolveTarget() {
  return nullptr;
}

void ExternalSVGResourceDocumentContent::ResourceNotifyFinished(
    SVGResourceDocumentContent*) {}

void ExternalSVGResourceDocumentContent::ResourceContentChanged(
    SVGResourceDocumentContent*) {}

bool RuntimeEnabledFeaturesBase::OriginTrialsSampleAPIEnabled(
    const FeatureContext*) {
  return false;
}

const NamedColor* FindColor(std::string_view str) {
  static constexpr NamedColor kNamedColors[] = {
      {"black", 0xff000000},
      {"blue", 0xff0000ff},
      {"cyan", 0xff00ffff},
      {"gray", 0xff808080},
      {"green", 0xff008000},
      {"grey", 0xff808080},
      {"magenta", 0xffff00ff},
      {"red", 0xffff0000},
      {"transparent", 0x00000000},
      {"white", 0xffffffff},
      {"yellow", 0xffffff00},
  };
  for (const auto& color : kNamedColors) {
    if (str == color.name) {
      return &color;
    }
  }
  return nullptr;
}

void CSSUrlRequestModifiers::AppendCssText(StringBuilder&) const {}

void CSSImageGeneratorValue::AddClient(const ImageResourceObserver*) {}

void CSSImageGeneratorValue::RemoveClient(const ImageResourceObserver*) {}

scoped_refptr<Image> CSSImageGeneratorValue::GetImage(
    const ImageResourceObserver&,
    const Node&,
    const ComputedStyle&,
    const ContainerSizes&,
    const gfx::SizeF&) {
  return nullptr;
}

bool CSSImageGeneratorValue::KnownToBeOpaque(const Document&,
                                             const ComputedStyle&) const {
  return false;
}

bool CSSImageGeneratorValue::IsUsingCustomProperty(
    const AtomicString&,
    const Document&) const {
  return false;
}

bool CSSImageGeneratorValue::IsUsingCurrentColor() const {
  return false;
}

bool CSSImageGeneratorValue::IsUsingContainerRelativeUnits() const {
  return false;
}

void CSSImageGeneratorValue::TraceAfterDispatch(Visitor* visitor) const {
  visitor->Trace(clients_);
  CSSValue::TraceAfterDispatch(visitor);
}

Image* CSSImageGeneratorValue::GetImage(const ImageResourceObserver*,
                                        const gfx::SizeF&) const {
  return nullptr;
}

void CSSImageGeneratorValue::PutImage(const gfx::SizeF&,
                                      scoped_refptr<Image>) const {}

CSSImageGeneratorValue::CSSImageGeneratorValue(ClassType class_type)
    : CSSValue(class_type) {}

CSSImageGeneratorValue::~CSSImageGeneratorValue() = default;

CSSImageSetValue::CSSImageSetValue()
    : CSSValueList(kImageSetClass, kCommaSeparator) {}

CSSImageSetValue::~CSSImageSetValue() = default;

CSSImageSetTypeValue::CSSImageSetTypeValue(const String& type)
    : CSSValue(kImageSetTypeClass), type_(type) {}

CSSImageSetTypeValue::~CSSImageSetTypeValue() = default;

CSSImageSetOptionValue::CSSImageSetOptionValue(
    const CSSValue* image,
    const CSSPrimitiveValue* resolution,
    const CSSImageSetTypeValue* type)
    : CSSValue(kImageSetOptionClass),
      image_(image),
      resolution_(resolution),
      type_(type) {}

CSSImageSetOptionValue::~CSSImageSetOptionValue() = default;

namespace cssvalue {

CSSCrossfadeValue::CSSCrossfadeValue(
    bool is_prefixed_variant,
    HeapVector<std::pair<Member<CSSValue>, Member<CSSPrimitiveValue>>>
        image_and_percentages)
    : CSSImageGeneratorValue(kCrossfadeClass),
      is_prefixed_variant_(is_prefixed_variant),
      image_and_percentages_(std::move(image_and_percentages)) {}

CSSCrossfadeValue::~CSSCrossfadeValue() = default;

}  // namespace cssvalue

CSSPaintValue::CSSPaintValue(CSSCustomIdentValue* name)
    : CSSImageGeneratorValue(kPaintClass),
      name_(name),
      off_thread_paint_state_(OffThreadPaintState::kUnknown) {}

CSSPaintValue::CSSPaintValue(CSSCustomIdentValue* name,
                             HeapVector<Member<CSSVariableData>>&& arguments)
    : CSSImageGeneratorValue(kPaintClass),
      name_(name),
      argument_variable_data_(std::move(arguments)),
      off_thread_paint_state_(OffThreadPaintState::kUnknown) {}

CSSPaintValue::~CSSPaintValue() = default;

bool StyleMaskSourceImage::HasSVGMask() const {
  return false;
}

CSSVariableData* CSSVariableParser::ConsumeUnparsedDeclaration(
    CSSParserTokenStream&,
    bool,
    bool,
    bool,
    bool,
    bool,
    bool& important,
    const CSSParserContext&) {
  important = false;
  return nullptr;
}

CounterStyleMap* CounterStyleMap::GetUACounterStyleMap() {
  return nullptr;
}

CounterStyle* CounterStyleMap::FindCounterStyleAcrossScopes(
    const AtomicString&) const {
  return nullptr;
}

SVGResource::SVGResource() = default;
SVGResource::~SVGResource() = default;
void SVGResource::AddClient(SVGResourceClient&) {}
void SVGResource::RemoveClient(SVGResourceClient&) {}
void SVGResource::Trace(Visitor*) const {}

bool CSSValue::HasFailedOrCanceledSubresources() const {
  return false;
}

bool CSSValue::MayContainUrl() const {
  return false;
}

void CSSValue::ReResolveUrl(const Document&) const {}

CSSValue* CSSValue::Create(const Length& value, float zoom) {
  float pixels = value.IsFixed() ? value.Pixels() : 0.0f;
  return CSSNumericLiteralValue::Create(pixels / zoom,
                                        CSSPrimitiveValue::UnitType::kPixels);
}

String CSSValue::CssText() const {
  return String();
}

unsigned CSSValue::Hash() const {
  return static_cast<unsigned>(GetClassType());
}

CSSUnparsedDeclarationValue* CSSVariableParser::ParseUniversalSyntaxValue(
    StringView,
    const CSSParserContext&,
    bool) {
  return nullptr;
}

BasicShape* BasicShapeForValue(const StyleResolverState&, const CSSValue&) {
  return nullptr;
}

CSSValue* ValueForBasicShape(const ComputedStyle&, const BasicShape*) {
  return nullptr;
}

FilterOperation::OperationType FilterOperationResolver::FilterOperationForType(
    CSSValueID) {
  return FilterOperation::OperationType::kReference;
}

FilterOperations FilterOperationResolver::CreateFilterOperations(
    StyleResolverState&,
    const CSSValue&,
    CSSPropertyID) {
  return FilterOperations();
}

FilterOperations FilterOperationResolver::CreateOffscreenFilterOperations(
    const CSSValue&,
    const Font*) {
  return FilterOperations();
}

double FilterOperationResolver::ResolveNumericArgumentForFunction(
    const CSSFunctionValue&,
    const CSSLengthResolver&) {
  return 0.0;
}

Vector<int> CountersAttachmentContext::GetCounterValues(
    const LayoutObject&,
    const AtomicString&,
    bool) {
  return {};
}

const CounterStyle& StyleEngine::FindCounterStyleAcrossScopes(
    const AtomicString&,
    const TreeScope*) const {
  return *static_cast<const CounterStyle*>(nullptr);
}

String LayoutCounter::GenerateCounterText(Vector<int>,
                                          const CounterStyle*,
                                          const AtomicString&) {
  return String();
}

LayoutCounter::LayoutCounter(Document& document, const CounterContentData& data)
    : LayoutText(&document, String()), counter_(&data) {}

LayoutCounter::~LayoutCounter() = default;

void LayoutCounter::Trace(Visitor* visitor) const {
  visitor->Trace(counter_);
  LayoutText::Trace(visitor);
}

void LayoutCounter::UpdateCounter(Vector<int>) {}

bool LayoutCounter::IsDirectionalSymbolMarker() const {
  return false;
}

const AtomicString& LayoutCounter::Separator() const {
  return g_null_atom;
}

const AtomicString& LayoutCounter::ListStyle(const LayoutObject*,
                                             const ComputedStyle&) {
  return g_null_atom;
}

void LayoutCounter::WillBeDestroyed() {
  LayoutText::WillBeDestroyed();
}

LayoutQuote::LayoutQuote(LayoutObject& owner, const QuoteType type)
    : LayoutInline(nullptr), type_(type), depth_(0), owning_pseudo_(nullptr) {}

LayoutQuote::~LayoutQuote() = default;

void LayoutQuote::Trace(Visitor* visitor) const {
  visitor->Trace(owning_pseudo_);
  LayoutInline::Trace(visitor);
}

void LayoutQuote::UpdateText() {}

void LayoutQuote::WillBeDestroyed() {
  LayoutInline::WillBeDestroyed();
}

void LayoutQuote::StyleDidChange(StyleDifference,
                                 const ComputedStyle*,
                                 const StyleChangeContext&) {}

void LayoutQuote::WillBeRemovedFromTree() {}

String LayoutQuote::ComputeText() const {
  return String();
}

scoped_refptr<const QuotesData> LayoutQuote::GetQuotesData() const {
  return nullptr;
}

LayoutTextFragment* LayoutQuote::FindFragmentChild() const {
  return nullptr;
}

LayoutTextFragment::LayoutTextFragment(Node* node,
                                       const String& text,
                                       int start_offset,
                                       int length)
    : LayoutText(node, text),
      start_(start_offset),
      fragment_length_(length),
      is_remaining_text_layout_object_(false),
      content_string_(text) {}

LayoutTextFragment::~LayoutTextFragment() = default;

LayoutTextFragment* LayoutTextFragment::Create(Node* node,
                                               const String& text,
                                               int start_offset,
                                               int length) {
  return MakeGarbageCollected<LayoutTextFragment>(node, text, start_offset,
                                                  length);
}

LayoutTextFragment* LayoutTextFragment::CreateAnonymous(Document& document,
                                                        const String& text) {
  return MakeGarbageCollected<LayoutTextFragment>(&document, text, 0,
                                                  text.length());
}

LayoutTextFragment* LayoutTextFragment::CreateAnonymous(Document& document,
                                                        const String& text,
                                                        unsigned start,
                                                        unsigned length) {
  return MakeGarbageCollected<LayoutTextFragment>(&document, text, start,
                                                  length);
}

void LayoutTextFragment::Trace(Visitor* visitor) const {
  LayoutText::Trace(visitor);
}

void LayoutTextFragment::SetContentString(const String& text) {
  content_string_ = text;
}

String LayoutTextFragment::CompleteText() const {
  return content_string_;
}

String LayoutTextFragment::OriginalText() const {
  return content_string_;
}

void LayoutTextFragment::SetTextFragment(String text,
                                         unsigned start,
                                         unsigned length) {
  content_string_ = text;
  start_ = start;
  fragment_length_ = length;
}

void LayoutTextFragment::TransformAndSecureOriginalText() {}

Text* LayoutTextFragment::AssociatedTextNode() const {
  return nullptr;
}

LayoutText* LayoutTextFragment::GetFirstLetterPart() const {
  return nullptr;
}

String LayoutTextFragment::PlainText() const {
  return content_string_;
}

void LayoutTextFragment::WillBeDestroyed() {
  LayoutText::WillBeDestroyed();
}

UChar LayoutTextFragment::PreviousCharacter() const {
  return 0;
}

void LayoutTextFragment::TextDidChange() {}

void LayoutTextFragment::UpdateHitTestResult(HitTestResult&,
                                             const PhysicalOffset&) const {}

DOMNodeId LayoutTextFragment::OwnerNodeId(bool) const {
  return kInvalidDOMNodeId;
}

SVGResource* StyleResolverState::GetSVGResource(
    CSSPropertyID,
    const cssvalue::CSSURIValue&) {
  return nullptr;
}

CSSToLengthConversionData StyleResolverState::FontSizeConversionData() {
  return CSSToLengthConversionData(GetStyledElement());
}

CSSToLengthConversionData StyleResolverState::UnzoomedLengthConversionData() {
  return CSSToLengthConversionData(GetStyledElement());
}

EInsideLink StyleResolverState::InsideLink() const {
  return EInsideLink::kNotInsideLink;
}

void Document::CountUse(mojom::WebFeature) const {}
void Document::CountUse(mojom::WebFeature) {}

const ui::ColorProvider* Document::GetColorProviderForPainting(
    mojom::blink::ColorScheme) const {
  return nullptr;
}

bool Document::IsInWebAppScope() const {
  return false;
}

bool Document::IsInitialProfile() const {
  return false;
}

HarfBuzzFace* FontPlatformData::GetHarfBuzzFace() const {
  return nullptr;
}

bool OpenTypeMathSupport::HasMathData(const HarfBuzzFace*) {
  return false;
}

std::optional<float> OpenTypeMathSupport::MathConstant(
    const HarfBuzzFace*,
    OpenTypeMathSupport::MathConstants) {
  return std::nullopt;
}

float FontSizeFunctions::GetComputedSizeFromSpecifiedSize(
    const Document*,
    float zoom_factor,
    bool,
    float specified_size,
    ApplyMinimumFontSize) {
  return specified_size * zoom_factor;
}

float FontSizeFunctions::FontSizeForKeyword(const Document*,
                                            unsigned keyword,
                                            bool) {
  static constexpr float kKeywordSizes[] = {9, 10, 13, 16, 18, 24, 32, 48};
  if (keyword == 0 ||
      keyword > sizeof(kKeywordSizes) / sizeof(kKeywordSizes[0])) {
    return 16.0f;
  }
  return kKeywordSizes[keyword - 1];
}

int FontSizeFunctions::LegacyFontSize(const Document*,
                                      int pixel_font_size,
                                      bool) {
  if (pixel_font_size <= 9) {
    return 1;
  }
  if (pixel_font_size <= 10) {
    return 2;
  }
  if (pixel_font_size <= 13) {
    return 3;
  }
  if (pixel_font_size <= 16) {
    return 4;
  }
  if (pixel_font_size <= 18) {
    return 5;
  }
  if (pixel_font_size <= 24) {
    return 6;
  }
  return 7;
}

std::optional<float> FontSizeFunctions::FontAspectValue(
    const SimpleFontData*,
    FontSizeAdjust::Metric) {
  return std::nullopt;
}

std::optional<float> FontSizeFunctions::MetricsMultiplierAdjustedFontSize(
    const SimpleFontData*,
    const FontDescription&) {
  return std::nullopt;
}

double FontSizeFunctions::SnapToClosestFontScaleBucket(double raw_font_scale) {
  return raw_font_scale;
}

void ShapeOutsideInfo::Trace(Visitor*) const {}

std::ostream& operator<<(std::ostream& stream, WritingMode) {
  return stream;
}

template <>
std::ostream& operator<<(std::ostream& stream,
                         const FixedPoint<6, int>&) {
  return stream;
}

const PhysicalFragment* PhysicalFragment::PostLayout() const {
  return this;
}

const BlockBreakToken* FindPreviousBreakToken(const PhysicalBoxFragment&) {
  return nullptr;
}

void LayoutResult::Trace(Visitor*) const {}

void FrameSelection::LayoutBlockWillBeDestroyed(const LayoutBlock&) {}

void LayoutSVGText::SetNeedsTextMetricsUpdate() {}

void BoxFragmentPainter::Paint(const PaintInfo&) {}

bool BoxFragmentPainter::NodeAtPoint(HitTestResult&,
                                     const HitTestLocation&,
                                     const PhysicalOffset&,
                                     HitTestPhase) {
  return false;
}

void BlockPaintInvalidator::InvalidatePaint(const PaintInvalidatorContext&) {}

void PhysicalBoxFragment::RecalcInkOverflow() {}

void Scrollbar::SetNeedsPaintInvalidation(ScrollbarPart) {}

AnchorScopedName* ToAnchorScopedName(const ScopedCSSName&,
                                     const LayoutObject&) {
  return nullptr;
}

const LayoutObject* AnchorMap::AnchorLayoutObject(const LayoutBox&,
                                                  const AnchorKey&) const {
  return nullptr;
}

void DisplayLockContext::SetAnchorPositioningRenderStateMayHaveChanged() {}

void DisplayLockContext::DidLayoutChildren() {}

const TrackedElementSubRects* Element::GetTrackedElementSubRects() const {
  return nullptr;
}

bool HasPaintedOutline(const ComputedStyle&, const Node*) {
  return false;
}

void InlineCursor::MoveToIncludingCulledInline(const LayoutObject&) {}

bool BoxFragmentPainter::NodeAtPoint(HitTestResult&,
                                     const HitTestLocation&,
                                     const PhysicalOffset&,
                                     const PhysicalOffset&,
                                     HitTestPhase) {
  return false;
}

HitTestLocation::HitTestLocation(const HitTestLocation& other,
                                 const PhysicalOffset&)
    : HitTestLocation(other) {}

bool HitTestLocation::Intersects(const PhysicalRect&) const {
  return false;
}

ListBasedHitTestBehavior HitTestResult::AddNodeToListBasedTestResult(
    Node*,
    const HitTestLocation&,
    const cc::Region&) {
  return kStopHitTesting;
}

PhysicalRect FragmentItem::InkOverflowRect() const {
  return PhysicalRect();
}

PhysicalRect FragmentItem::SelfInkOverflowRect() const {
  return PhysicalRect();
}

void FragmentItems::DirtyLinesFromChangedChild(const LayoutObject&,
                                               const LayoutBlockFlow&) {}

void FragmentItems::LayoutObjectWillBeMoved(const LayoutObject&) {}

void UnionOutlineRectCollector::AddRect(const PhysicalRect&) {}

void UnionOutlineRectCollector::Combine(OutlineRectCollector*,
                                        const PhysicalOffset&) {}

void UnionOutlineRectCollector::Combine(OutlineRectCollector*,
                                        const LayoutObject&,
                                        const LayoutBoxModelObject*,
                                        const PhysicalOffset&) {}

void VectorOutlineRectCollector::Combine(OutlineRectCollector*,
                                         const PhysicalOffset&) {}

void VectorOutlineRectCollector::Combine(OutlineRectCollector*,
                                         const LayoutObject&,
                                         const LayoutBoxModelObject*,
                                         const PhysicalOffset&) {}

TextOverflowPostLayoutSnapshot::TextOverflowPostLayoutSnapshot(
    PaintLayerScrollableArea&)
    : PostLayoutSnapshotClient(nullptr) {}

PostLayoutSnapshotClient::PostLayoutSnapshotClient(LocalFrame*) {}

void PostLayoutSnapshotClient::UpdateSnapshotForServiceAnimations() {
  UpdateSnapshot();
}

bool TextOverflowPostLayoutSnapshot::UpdateSnapshot() {
  return false;
}

bool TextOverflowPostLayoutSnapshot::ShouldScheduleNextService() {
  return false;
}

void TextOverflowPostLayoutSnapshot::Trace(Visitor*) const {}

void InlineCursor::MoveToFirstLine() {}

InlineCursor InlineCursor::CursorForDescendants() const {
  return InlineCursor();
}

void InlineCursor::MoveToNextSkippingChildren() {}

void InlineCursor::MoveToNextLine() {}

void ComputedStyle::ClearCachedPseudoElementStyles() const {}

EditingBehavior Editor::Behavior() const {
  return EditingBehavior(mojom::blink::EditingBehavior::kEditingWindowsBehavior);
}

void LayoutBlockFlow::StyleDidChange(StyleDifference,
                                     const ComputedStyle*,
                                     const StyleChangeContext&) {}

bool LayoutBlockFlow::CreatesNewFormattingContext() const {
  return false;
}

PhysicalRect LayoutTextCombine::AdjustRectForBoundingBox(
    const PhysicalRect& rect) const {
  return rect;
}

PhysicalOffset LayoutTextCombine::AdjustOffsetForHitTest(
    const PhysicalOffset& offset) const {
  return offset;
}

bool LayoutTextCombine::NeedsAffineTransformInPaint() const {
  return false;
}

void StyleAdjuster::AdjustStyleForTextCombine(ComputedStyleBuilder&) {}

void Font::WillUseFontData(const String&) const {}

Font::Font() = default;

Font::Font(const FontDescription& description)
    : font_description_(description) {}

Font::Font(const FontDescription& description, FontSelector*)
    : font_description_(description) {}

bool Font::operator==(const Font&) const {
  return true;
}

bool Font::IsFallbackValid() const {
  return true;
}

FontFallbackList* Font::EnsureFontFallbackList() const {
  alignas(FontFallbackList) static char fallback_storage[sizeof(FontFallbackList)];
  return reinterpret_cast<FontFallbackList*>(fallback_storage);
}

FontFallbackList::FontFallbackList(FontSelector* font_selector)
    : font_selector_(font_selector) {}

void FontFallbackList::Trace(Visitor*) const {}

bool FontFallbackList::ShouldSkipDrawing() const {
  return false;
}

const SimpleFontData* FontFallbackList::DeterminePrimarySimpleFontData(
    const FontDescription&,
    UChar32,
    bool) {
  return nullptr;
}

const SimpleFontData* FontFallbackList::DeterminePrimarySimpleFontDataCore(
    const FontDescription&,
    UChar32,
    bool) {
  return nullptr;
}

bool ComputedStyle::CalculateIsStackingContextWithoutContainment() const {
  return false;
}

TimerBase::TimerBase(scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : web_task_runner_(std::move(task_runner)) {}

TimerBase::~TimerBase() = default;

void TimerBase::Start(base::TimeDelta,
                      std::optional<base::TimeDelta>,
                      const base::Location& location,
                      bool) {
  location_ = location;
}

void TimerBase::Stop() {
  next_fire_time_ = base::TimeTicks::Max();
}

base::TimeDelta TimerBase::NextFireInterval() const {
  return base::TimeDelta();
}

void TimerBase::MoveToNewTaskRunner(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner) {
  web_task_runner_ = std::move(task_runner);
}

void TimerBase::SetTaskRunnerForTesting(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    const base::TickClock*) {
  web_task_runner_ = std::move(task_runner);
}

void TimerBase::RunInternal() {}

base::TimeTicks TimerBase::TimerCurrentTimeTicks() const {
  return base::TimeTicks();
}

void TimerBase::SetNextFireTime(base::TimeTicks next_fire_time) {
  next_fire_time_ = next_fire_time;
}

ContentCaptureManager::ContentCaptureManager(LocalFrame&) {}
ContentCaptureManager::~ContentCaptureManager() = default;
void ContentCaptureManager::ScheduleTaskIfNeeded(const Node&) {}
void ContentCaptureManager::OnLayoutTextWillBeDestroyed(const Node&) {}
void ContentCaptureManager::OnScrollPositionChanged() {}
void ContentCaptureManager::NotifyInputEvent(WebInputEvent::Type,
                                             const LocalFrame&) {}
void ContentCaptureManager::OnNodeTextChanged(Node&) {}
void ContentCaptureManager::OnFrameWasShown() {}
void ContentCaptureManager::OnFrameWasHidden() {}
void ContentCaptureManager::Shutdown() {}
void ContentCaptureManager::Trace(Visitor*) const {}
ContentCaptureTask* ContentCaptureManager::CreateContentCaptureTask() {
  return nullptr;
}

ContentCaptureManager* LocalFrame::GetOrResetContentCaptureManager() {
  return nullptr;
}

scoped_refptr<base::SingleThreadTaskRunner> Document::GetTaskRunner(TaskType) {
  return nullptr;
}

Document::StyleAndLayoutTreeUpdate Document::CalculateStyleAndLayoutTreeUpdate()
    const {
  return StyleAndLayoutTreeUpdate::kFull;
}

AbstractInlineTextBox* AbstractInlineTextBox::GetOrCreate(
    const InlineCursor&) {
  return nullptr;
}

void AbstractInlineTextBox::WillDestroy(const InlineCursor&) {}

const OffsetMapping* OffsetMapping::GetFor(const LayoutObject*) {
  return nullptr;
}

base::span<const OffsetMappingUnit> OffsetMapping::GetMappingUnitsForNode(
    const Node&) const {
  return {};
}

base::span<const OffsetMappingUnit>
OffsetMapping::GetMappingUnitsForTextContentOffsetRange(unsigned,
                                                        unsigned) const {
  return {};
}

const OffsetMappingUnit* OffsetMapping::GetLastMappingUnit(unsigned) const {
  return nullptr;
}

Position OffsetMapping::GetLastPosition(unsigned) const {
  return Position();
}

std::optional<unsigned> OffsetMapping::GetTextContentOffset(
    const Position&) const {
  return std::nullopt;
}

Position OffsetMapping::StartOfNextNonCollapsedContent(
    const Position&) const {
  return Position();
}

Position OffsetMapping::EndOfLastNonCollapsedContent(const Position&) const {
  return Position();
}

bool OffsetMapping::IsBeforeNonCollapsedContent(const Position&) const {
  return false;
}

bool OffsetMapping::IsAfterNonCollapsedContent(const Position&) const {
  return false;
}

std::optional<UChar> OffsetMapping::GetCharacterBefore(const Position&) const {
  return std::nullopt;
}

const Node* OffsetMappingUnit::AssociatedNode() const {
  return nullptr;
}

unsigned OffsetMappingUnit::ConvertTextContentToLastDOMOffset(
    unsigned offset) const {
  return offset;
}

TextIteratorBehavior::TextIteratorBehavior() {
  values_.all = 0;
}

void LayoutView::RegisterVariableLengthTransformResult(
    const LayoutText&,
    const VariableLengthTransformResult&) {}

void LayoutView::UnregisterVariableLengthTransformResult(const LayoutText&) {}

VariableLengthTransformResult LayoutView::GetVariableLengthTransformResult(
    const LayoutText&) {
  return VariableLengthTransformResult();
}

ChromeClient& Frame::GetChromeClient() const {
  DEFINE_STATIC_LOCAL(ChromeClient, chrome_client, ());
  return chrome_client;
}

FontVariantAlternates::FontVariantAlternates() = default;

void FontVariantAlternates::SetStylistic(AtomicString value) {
  stylistic_ = value;
}

void FontVariantAlternates::SetHistoricalForms() {
  historical_forms_ = true;
}

void FontVariantAlternates::SetSwash(AtomicString value) {
  swash_ = value;
}

void FontVariantAlternates::SetOrnaments(AtomicString value) {
  ornaments_ = value;
}

void FontVariantAlternates::SetAnnotation(AtomicString value) {
  annotation_ = value;
}

void FontVariantAlternates::SetStyleset(Vector<AtomicString> value) {
  styleset_ = std::move(value);
}

void FontVariantAlternates::SetCharacterVariant(Vector<AtomicString> value) {
  character_variant_ = std::move(value);
}

bool FontVariantAlternates::IsNormal() const {
  return !historical_forms_ && !stylistic_ && !swash_ && !ornaments_ &&
         !annotation_ && styleset_.empty() && character_variant_.empty();
}

scoped_refptr<FontVariantAlternates> FontVariantAlternates::Resolve(
    ResolverFunction,
    ResolverFunction,
    ResolverFunction,
    ResolverFunction,
    ResolverFunction,
    ResolverFunction) const {
  return base::AdoptRef(new FontVariantAlternates());
}

const ResolvedFontFeatures& FontVariantAlternates::GetResolvedFontFeatures()
    const {
  return resolved_features_;
}

unsigned FontVariantAlternates::GetHash() const {
  return historical_forms_ ? 1u : 0u;
}

bool FontVariantAlternates::operator==(
    const FontVariantAlternates& other) const {
  return historical_forms_ == other.historical_forms_ &&
         stylistic_ == other.stylistic_ && swash_ == other.swash_ &&
         ornaments_ == other.ornaments_ && annotation_ == other.annotation_ &&
         styleset_ == other.styleset_ &&
         character_variant_ == other.character_variant_;
}

void PaintLayerScrollableArea::ClampScrollOffsetAfterOverflowChange() {}

void PaintLayerScrollableArea::UpdateAfterOverflowRecalc() {}

int PaintLayerScrollableArea::HypotheticalScrollbarThickness(
    ScrollbarOrientation,
    bool) const {
  return 0;
}

bool PaintLayerScrollableArea::HitTestOverflowControls(HitTestResult&,
                                                       const gfx::Point&) {
  return false;
}

void PaintLayerScrollableArea::SetTickmarksOverride(Vector<gfx::Rect>) {}

void PaintLayer::UpdateTransform() {}

void PaintLayer::UpdateScrollingAfterLayout() {}

bool PaintLayer::PaintsWithFilters() const {
  return false;
}

gfx::RectF PaintLayer::MapRectForFilter(const gfx::RectF& rect) const {
  return rect;
}

PhysicalRect PaintLayer::MapRectForFilter(const PhysicalRect& rect) const {
  return rect;
}

std::optional<LayoutUnit> Element::LastRememberedInlineSize() const {
  return std::nullopt;
}

std::optional<LayoutUnit> Element::LastRememberedBlockSize() const {
  return std::nullopt;
}

bool ComputedStyle::ApplyControlFixedSize(const Node*) const {
  return false;
}

bool Element::SupportsBaseAppearance(AppearanceValue) const {
  return false;
}

bool IsSliderContainer(const Element&) {
  return false;
}

bool HTMLInputElement::IsTextField() const {
  return false;
}

mojom::blink::FormControlType HTMLInputElement::FormControlType() const {
  return mojom::blink::FormControlType::kInputText;
}

bool HTMLInputElement::GetSizeWithDecoration(int&) const {
  return false;
}

HTMLInputElement* HTMLInputElement::UploadButton() const {
  return nullptr;
}

float ComputeTextWidth(const StringView&, const ComputedStyle&) {
  return 0.0f;
}

namespace layout_text_control {

int ScrollbarThickness(const LayoutBox&) {
  return 0;
}

float GetAvgCharWidth(const ComputedStyle&) {
  return 8.0f;
}

bool HasValidAvgCharWidth(const Font&) {
  return false;
}

}  // namespace layout_text_control

ShadowRoot* Element::UserAgentShadowRoot() const {
  return nullptr;
}

Locale& Element::GetLocale() const {
  class StandaloneLocale final : public Locale {
   public:
    StandaloneLocale() = default;
    String DateFormat() override { return String(); }
    String MonthFormat() override { return String(); }
    String ShortMonthFormat() override { return String(); }
    String TimeFormat() override { return String(); }
    String ShortTimeFormat() override { return String(); }
    String DateTimeFormatWithSeconds() override { return String(); }
    String DateTimeFormatWithoutSeconds() override { return String(); }
    const Vector<String>& ShortMonthLabels() override { return EmptyLabels(); }
    const Vector<String>& StandAloneMonthLabels() override {
      return EmptyLabels();
    }
    const Vector<String>& ShortStandAloneMonthLabels() override {
      return EmptyLabels();
    }
    const Vector<String>& TimeAMPMLabels() override { return EmptyLabels(); }
    const Vector<String>& MonthLabels() override { return EmptyLabels(); }
    const Vector<String>& WeekDayShortLabels() override { return EmptyLabels(); }
    unsigned FirstDayOfWeek() override { return 0; }
    bool IsRTL() override { return false; }

   private:
    const Vector<String>& EmptyLabels() {
      static Vector<String>* labels = new Vector<String>;
      return *labels;
    }
    void InitializeLocaleData() override {}
  };
  static StandaloneLocale* locale = new StandaloneLocale;
  return *locale;
}

Element* TreeScope::getElementById(const AtomicString&) const {
  return nullptr;
}

LayoutBox* Node::GetLayoutBox() const {
  return nullptr;
}

WebThemeEngine* WebThemeEngineHelper::GetNativeThemeEngine() {
  return nullptr;
}

PhysicalOffset LocalFrameView::ConvertFromRootFrame(
    const PhysicalOffset& offset) const {
  return offset;
}

PhysicalRect LocalFrameView::ConvertToRootFrame(
    const PhysicalRect& rect) const {
  return rect;
}

ScrollableArea* LocalFrameView::GetScrollableArea() {
  return nullptr;
}

const mojom::blink::ScrollAlignment& ScrollAlignment::ToEdgeIfNeeded() {
  DEFINE_STATIC_LOCAL(mojom::blink::ScrollAlignment, alignment, ());
  return alignment;
}

namespace scroll_into_view_util {

mojom::blink::ScrollIntoViewParamsPtr CreateScrollIntoViewParams(
    const mojom::blink::ScrollAlignment&,
    const mojom::blink::ScrollAlignment&,
    mojom::blink::ScrollType,
    bool,
    mojom::blink::ScrollBehavior,
    bool,
    bool) {
  return std::make_unique<mojom::blink::ScrollIntoViewParams>();
}

bool ScrollRectToVisible(const LayoutObject&,
                         const PhysicalRect&,
                         mojom::blink::ScrollIntoViewParamsPtr,
                         const LayoutObject*,
                         bool,
                         bool,
                         ScrollPromiseResolver*) {
  return false;
}

}  // namespace scroll_into_view_util

bool LayoutBox::IsUserScrollable() const {
  return false;
}

ListBasedHitTestBehavior HitTestResult::AddNodeToListBasedTestResult(
    Node*,
    const HitTestLocation&,
    const PhysicalRect&) {
  return kStopHitTesting;
}

Image* ImageResourceContent::GetImage() const {
  return nullptr;
}

void BoxPaintInvalidator::InvalidatePaint() {}

void CustomScrollbar::ClearPaintFlags() {}

PhysicalRect LayoutReplaced::PreSnappedRectForPersistentSizing(
    const PhysicalRect& rect) {
  return rect;
}

AnchorPositionScrollData* Element::GetAnchorPositionScrollData() const {
  return nullptr;
}

PhysicalOffset
AnchorPositionScrollData::SpeculativeDefaultAnchorRememberedOffsetIncludingChained()
    const {
  return PhysicalOffset();
}

void MeasureCache::Clear() {}

void MeasureCache::Add(const LayoutResult*) {}

void MeasureCache::InvalidateItems() {}

void MeasureCache::SetFragmentChildrenInvalid(const LayoutResult*) {}

const LayoutResult* MeasureCache::Find(
    const BlockNode&,
    const ConstraintSpace&,
    std::optional<FragmentGeometry>*) {
  return nullptr;
}

const LayoutResult* MeasureCache::GetLastForTesting() const {
  return nullptr;
}

void LayoutTableCell::InvalidateLayoutResultCacheAfterMeasure() const {}

void FragmentItems::ClearAssociatedFragments(LayoutObject*) {}

void FragmentItems::FinalizeAfterLayout(
    const HeapVector<Member<const LayoutResult>, 1>&,
    LayoutBlockFlow&) {}

void FragmentItems::CheckAllItemsAreValid() const {}

void FragmentItems::LayoutObjectWillBeDestroyed(const LayoutObject&) {}

const LayoutResult* LayoutResult::CloneWithPostLayoutFragments(
    const LayoutResult& result) {
  return &result;
}

unsigned BoxFragmentIndex(const PhysicalBoxFragment&) {
  return 0;
}

PhysicalOffset LayoutView::OffsetForFixedPosition() const {
  return PhysicalOffset();
}

PositionWithAffinity PhysicalBoxFragment::PositionForPoint(
    PhysicalOffset) const {
  return PositionWithAffinity();
}

PhysicalBoxFragment::AllowPostLayoutScope::AllowPostLayoutScope() = default;
PhysicalBoxFragment::AllowPostLayoutScope::~AllowPostLayoutScope() = default;

PhysicalBoxFragment::MutableForStyleRecalc
PhysicalBoxFragment::GetMutableForStyleRecalc() const {
  return MutableForStyleRecalc(base::PassKey<PhysicalBoxFragment>(),
                               const_cast<PhysicalBoxFragment&>(*this));
}

PhysicalBoxFragment::MutableForStyleRecalc::MutableForStyleRecalc(
    base::PassKey<PhysicalBoxFragment>,
    PhysicalBoxFragment& fragment)
    : fragment_(fragment) {}

void PhysicalBoxFragment::MutableForStyleRecalc::SetScrollableOverflow(
    const PhysicalRect&) {}

PhysicalRect ScrollableOverflowCalculator::RecalculateScrollableOverflowForFragment(
    const PhysicalBoxFragment&,
    bool) {
  return PhysicalRect();
}

const PhysicalBoxFragment* FragmentItem::BoxItem::PostLayout() const {
  return nullptr;
}

LayoutBox* PhysicalBoxFragment::MutableOwnerLayoutBox() const {
  return nullptr;
}

unsigned InkOverflow::read_unset_as_none_ = 0;

PhysicalRect PhysicalBoxFragment::ContentsInkOverflowRect() const {
  return PhysicalRect();
}

PhysicalRect PhysicalBoxFragment::SelfInkOverflowRect() const {
  return PhysicalRect();
}

bool ShapeOutsideInfo::IsEnabledFor(const LayoutBox&) {
  return false;
}

TextDirection FragmentItem::ResolvedDirection() const {
  return TextDirection::kLtr;
}

bool ComputedStyle::IsRenderedInTopLayer(const Element&) const {
  return false;
}

void ScrollAnchor::ClearSelf() {}

LayoutBox* LayoutFieldset::FindInFlowLegend(const LayoutBlock&) {
  return nullptr;
}

bool HTMLSummaryElement::IsMainSummary() const {
  return false;
}

ListMarker::ListStyleCategory ListMarker::GetListStyleCategory(
    Document&,
    const ComputedStyle&) {
  return ListStyleCategory::kNone;
}

unsigned PropertyRegistration::GetViewportUnitFlags() const {
  return 0;
}

void PropertyRegistration::Trace(Visitor*) const {}

void ScopedCSSName::Trace(Visitor*) const {}

void ScopedCSSNameList::Trace(Visitor*) const {}

FontVariantAlternatesParser::FontVariantAlternatesParser()
    : alternates_list_(nullptr) {}

FontVariantAlternatesParser::ParseResult
FontVariantAlternatesParser::ConsumeAlternates(CSSParserTokenStream&,
                                               const CSSParserContext&,
                                               CSSParserLocalContext&) {
  return ParseResult::kUnknownValue;
}

CSSValue* FontVariantAlternatesParser::FinalizeValue() {
  return nullptr;
}

PaintLayer::PaintLayer(LayoutBoxModelObject* layout_object)
    : is_root_layer_(false),
      has_visible_content_(false),
      needs_descendant_dependent_flags_update_(false),
      needs_visual_overflow_recalc_(false),
      has_visible_self_painting_descendant_(false),
      needs_cull_rect_update_(false),
      forces_children_cull_rect_update_(false),
      descendant_needs_cull_rect_update_(false),
      previous_paint_result_(kMayBeClippedByCullRect),
      needs_paint_phase_descendant_outlines_(false),
      needs_paint_phase_float_(false),
      has_non_isolated_descendant_with_blend_mode_(false),
      has_fixed_position_descendant_(false),
      has_non_contained_absolute_position_descendant_(false),
      has_stacked_descendant_in_current_stacking_context_(false),
      filter_on_effect_node_dirty_(false),
      backdrop_filter_on_effect_node_dirty_(false),
      has_filter_that_moves_pixels_(false),
      is_under_svg_hidden_container_(false),
      has_self_painting_layer_descendant_(false),
      has_backdrop_filter_descendant_(false),
      needs_reorder_overlay_overflow_controls_(false),
      static_inline_edge_(InlineEdge::kInlineStart),
      static_block_edge_(BlockEdge::kBlockStart),
#if DCHECK_IS_ON()
      layer_list_mutation_allowed_(true),
#endif
      layout_object_(layout_object),
      parent_(nullptr),
      previous_(nullptr),
      next_(nullptr),
      first_(nullptr),
      last_(nullptr),
      static_inline_position_(0),
      static_block_position_(0) {}
PaintLayer::~PaintLayer() = default;
void PaintLayer::AddChild(PaintLayer*, PaintLayer*) {}
void PaintLayer::RemoveChild(PaintLayer*) {}
void PaintLayer::RemoveOnlyThisLayerAfterStyleChange(const ComputedStyle*) {}
void PaintLayer::InsertOnlyThisLayerAfterStyleChange() {}
void PaintLayer::StyleDidChange(StyleDifference, const ComputedStyle*) {}
void PaintLayer::DirtyVisibleContentStatus() {}
void PaintLayer::SetNeedsVisualOverflowRecalc() {}
void PaintLayer::SetNeedsCompositingInputsUpdate() {}
void PaintLayer::SetNeedsRepaint() {}
void PaintLayer::ScrollContainerStatusChanged() {}
void PaintLayer::UpdateFilters(StyleDifference,
                               const ComputedStyle*,
                               const ComputedStyle&) {}
void PaintLayer::UpdateBackdropFilters(const ComputedStyle*,
                                       const ComputedStyle&) {}
void PaintLayer::UpdateClipPath(const ComputedStyle*, const ComputedStyle&) {}
const PaintLayer* PaintLayer::ContainingScrollContainerLayer(bool*) const {
  return nullptr;
}
gfx::RectF PaintLayer::FilterReferenceBox() const {
  return gfx::RectF();
}
gfx::Transform PaintLayer::CurrentTransform() const {
  return gfx::Transform();
}

void LocalFrameView::ScheduleRelayout() {}
void LocalFrameView::ScheduleRelayoutOfSubtree(LayoutObject*) {}
PhysicalRect LocalFrameView::DocumentToFrame(const PhysicalRect& rect) const {
  return rect;
}
void LocalFrameView::AdjustViewSize() {}
void LocalFrameView::ScheduleVisualUpdateForPaintInvalidationIfNeeded() {}
bool LocalFrameView::IsInPerformLayout() const {
  return false;
}
LayoutUnit LocalFrameView::BarCaretWidth() const {
  return LayoutUnit();
}

Element& PseudoElement::UltimateOriginatingElement() const {
  return const_cast<PseudoElement&>(*this);
}

void PhysicalBoxFragment::InvalidateInkOverflow() {}

bool CompositorFilterOperations::IsEmpty() const {
  return true;
}

LocalFrame& LocalFrame::LocalFrameRoot() const {
  return const_cast<LocalFrame&>(*this);
}

LayoutView* LocalFrame::ContentLayoutObject() const {
  return nullptr;
}

String Node::ToString() const {
  return String();
}

String Node::DebugName() const {
  return String();
}

DOMNodeId Node::GetDomNodeId() {
  return 0;
}

HTMLFrameOwnerElement* Document::LocalOwner() const {
  return nullptr;
}

Page* Document::GetPage() const {
  return nullptr;
}

LocalFrameView* Document::View() const {
  return nullptr;
}

bool Document::InvalidationDisallowed() const {
  return false;
}

Element* Document::ViewportDefiningElement() const {
  return nullptr;
}

bool Document::StandardizedBrowserZoomEnabled() const {
  return false;
}

AXObjectCache* Document::ExistingAXObjectCache() const {
  return nullptr;
}

StyleResolver& Document::GetStyleResolver() const {
  return *static_cast<StyleResolver*>(nullptr);
}

CSSStyleSheet& Document::ElementSheet() {
  return *static_cast<CSSStyleSheet*>(nullptr);
}

Settings* Document::GetSettings() const {
  return nullptr;
}

PaintInvalidationReason
ObjectPaintInvalidatorWithContext::ComputePaintInvalidationReason() {
  return PaintInvalidationReason::kNone;
}

void ObjectPaintInvalidatorWithContext::InvalidatePaintWithComputedReason(
    PaintInvalidationReason) {}

void TransformState::ApplyTransform(const gfx::Transform&,
                                    TransformAccumulation) {}

void TransformState::Flatten() {}

void TransformState::Move(const PhysicalOffset&, TransformAccumulation) {}

const FragmentData& FragmentDataList::at(unsigned) const {
  return *static_cast<const FragmentData*>(nullptr);
}

unsigned FragmentDataList::size() const {
  return 0;
}

template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate() = default;

template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const Node* anchor_node,
                                             int offset)
    : anchor_node_(const_cast<Node*>(anchor_node)), offset_(offset) {}

template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const Node* anchor_node,
                                             PositionAnchorType anchor_type)
    : anchor_node_(const_cast<Node*>(anchor_node)), anchor_type_(anchor_type) {}

template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const PositionTemplate&) = default;

template <typename Strategy>
PositionTemplate<Strategy>& PositionTemplate<Strategy>::operator=(
    const PositionTemplate&) = default;

template <typename Strategy>
bool PositionTemplate<Strategy>::operator<=(
    const PositionTemplate<Strategy>& other) const {
  return *this == other || IsNull() || other.IsNotNull();
}

template <typename Strategy>
bool PositionTemplate<Strategy>::IsConnected() const {
  return anchor_node_;
}

template <typename Strategy>
bool PositionTemplate<Strategy>::IsValidFor(const Document&) const {
  return true;
}

template <typename Strategy>
PositionTemplate<Strategy> PositionTemplate<Strategy>::BeforeNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(&anchor_node,
                                    PositionAnchorType::kBeforeAnchor);
}

template <typename Strategy>
PositionTemplate<Strategy> PositionTemplate<Strategy>::AfterNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(&anchor_node,
                                    PositionAnchorType::kAfterAnchor);
}

template <typename Strategy>
PositionTemplate<Strategy> PositionTemplate<Strategy>::FirstPositionInOrBeforeNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(&anchor_node, 0);
}

template <typename Strategy>
PositionTemplate<Strategy> PositionTemplate<Strategy>::LastPositionInOrAfterNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(&anchor_node,
                                    PositionAnchorType::kAfterChildren);
}

template class PositionTemplate<EditingStrategy>;

template <typename Strategy>
PositionWithAffinityTemplate<Strategy>::PositionWithAffinityTemplate(
    const PositionTemplate<Strategy>& position,
    TextAffinity affinity)
    : position_(position), affinity_(affinity) {}

template <typename Strategy>
PositionWithAffinityTemplate<Strategy>::PositionWithAffinityTemplate(
    const PositionTemplate<Strategy>& position)
    : PositionWithAffinityTemplate(position, TextAffinity::kDefault) {}

template <typename Strategy>
PositionWithAffinityTemplate<Strategy>::PositionWithAffinityTemplate()
    : affinity_(TextAffinity::kDefault) {}

template <typename Strategy>
PositionWithAffinityTemplate<Strategy>::~PositionWithAffinityTemplate() =
    default;

template class PositionWithAffinityTemplate<EditingStrategy>;

template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate() = default;

template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate(
    const PositionTemplate<Strategy>& position)
    : start_position_(position), end_position_(position) {}

template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate(
    const PositionTemplate<Strategy>& start,
    const PositionTemplate<Strategy>& end)
    : start_position_(start), end_position_(end) {}

template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate(
    const EphemeralRangeTemplate& other) = default;

template <typename Strategy>
EphemeralRangeTemplate<Strategy>::~EphemeralRangeTemplate() = default;

template <typename Strategy>
EphemeralRangeTemplate<Strategy> EphemeralRangeTemplate<Strategy>::RangeOfContents(
    const Node&) {
  return EphemeralRangeTemplate<Strategy>();
}

template <typename Strategy>
bool EphemeralRangeTemplate<Strategy>::IsValid() const {
  return true;
}

template class EphemeralRangeTemplate<EditingStrategy>;

String PlainText(const EphemeralRange&, const TextIteratorBehavior&) {
  return String();
}

class AccompaniedFragmentIterator {
 public:
  const FragmentData* GetFragmentData() const { return nullptr; }
  InlineCursor* Cursor() { return nullptr; }
  bool Advance();
  const PhysicalBoxFragment* GetPhysicalBoxFragment() const;
};

bool AccompaniedFragmentIterator::Advance() {
  return false;
}

const PhysicalBoxFragment*
AccompaniedFragmentIterator::GetPhysicalBoxFragment() const {
  return nullptr;
}

TextOffsetRange FragmentItem::TextOffset() const {
  return TextOffsetRange();
}

bool FragmentItem::IsGeneratedText() const {
  return false;
}

AffineTransform FragmentItem::BuildSvgTransformForBoundingBox() const {
  return AffineTransform();
}

float FragmentItem::SvgScalingFactor() const {
  return 1.0f;
}

PhysicalRect FragmentItem::LocalVisualRectFor(const LayoutObject&) {
  return PhysicalRect();
}

bool FragmentItem::HasSvgTransformForBoundingBox() const {
  return false;
}

void FragmentItem::InvalidateInkOverflow() {}

void FragmentData::SetLayer(PaintLayer*) {}

FragmentData::RareData& FragmentData::EnsureRareData() {
  return *static_cast<FragmentData::RareData*>(nullptr);
}

void FragmentData::RareData::EnsureId() {}

PropertyTreeStateOrAlias FragmentData::LocalBorderBoxPropertiesFallback()
    const {
  return PropertyTreeStateOrAlias::Root();
}

const EffectPaintPropertyNode& EffectPaintPropertyNode::Root() {
  alignas(EffectPaintPropertyNode) static char storage[sizeof(EffectPaintPropertyNode)];
  return *reinterpret_cast<const EffectPaintPropertyNode*>(storage);
}

const ClipPaintPropertyNode& ClipPaintPropertyNode::Root() {
  alignas(ClipPaintPropertyNode) static char storage[sizeof(ClipPaintPropertyNode)];
  return *reinterpret_cast<const ClipPaintPropertyNode*>(storage);
}

const TransformPaintPropertyNode& TransformPaintPropertyNode::Root() {
  alignas(TransformPaintPropertyNode) static char storage[sizeof(TransformPaintPropertyNode)];
  return *reinterpret_cast<const TransformPaintPropertyNode*>(storage);
}

PhysicalRect InlineCursor::CurrentLocalRect(unsigned, unsigned) const {
  return PhysicalRect();
}

PositionWithAffinity InlineCursor::PositionForPointInChild(
    const PhysicalOffset&) const {
  return PositionWithAffinity();
}

void InlineCursor::MoveToLastForSameLayoutObject() {}

PhysicalRect InlineCursor::CurrentLocalSelectionRectForText(
    const LayoutSelectionStatus&) const {
  return PhysicalRect();
}

StringView InlineCursorPosition::Text(const InlineCursor&) const {
  return StringView();
}

InlineCursor::InlineCursor(const LayoutBlockFlow&) {}

InlineCursor::InlineCursor(const PhysicalBoxFragment&) {}

PhysicalRect InlineCursor::CurrentRectInFirstContainerFragment() const {
  return PhysicalRect();
}

const LayoutBlockFlow* InlineCursor::GetLayoutBlockFlow() const {
  return nullptr;
}

void InlineCursor::MoveToNext() {}

void InlineCursor::MoveTo(const LayoutObject&) {}

void InlineCursor::MoveToNextForSameLayoutObject() {}

void InlineCursorPosition::RecalcInkOverflow(const InlineCursor&,
                                             InlinePaintContext*) const {}

InlinePaintContext::ScopedInlineBoxAncestors::ScopedInlineBoxAncestors(
    const InlineCursor&,
    InlinePaintContext*) {}

void InlinePaintContext::ClearLineBox() {}

bool InlineNode::SetTextWithOffset(LayoutText*, String, const TextDiffRange&) {
  return false;
}

Position LayoutTextFragment::PositionForCaretOffset(unsigned) const {
  return Position();
}

std::optional<unsigned> LayoutTextFragment::CaretOffsetForPosition(
    const Position&) const {
  return std::nullopt;
}

ShadowRoot* Node::ContainingShadowRoot() const {
  return nullptr;
}

void Element::SetHasBeenHeuristicCustomPasswordCSS() {}

PseudoElement* Element::GetPseudoElement(PseudoId, const AtomicString&) const {
  return nullptr;
}

Element* Element::ImplicitAnchorElement() const {
  return nullptr;
}

ElementAnimations* Element::GetElementAnimations() const {
  return nullptr;
}

AnchorPositionScrollData& Element::EnsureAnchorPositionScrollData() {
  return *static_cast<AnchorPositionScrollData*>(nullptr);
}

void Element::RemoveAnchorPositionScrollData() {}

ContainerQueryEvaluator& Element::EnsureContainerQueryEvaluator() {
  return *static_cast<ContainerQueryEvaluator*>(nullptr);
}

void ContainerQueryEvaluator::Trace(Visitor*) const {}

Element* ContainerQueryEvaluator::FindContainer(Element*,
                                                const ContainerSelector&,
                                                const TreeScope*) {
  return nullptr;
}

LayoutImage* LayoutImage::CreateAnonymous(Document&) {
  return nullptr;
}

void LayoutImage::SetImageResource(LayoutImageResource*) {}

LayoutImageResource::LayoutImageResource() = default;

LayoutImageResource::~LayoutImageResource() = default;

void LayoutImageResource::Trace(Visitor*) const {}

void LayoutImageResource::Initialize(LayoutObject* layout_object) {
  layout_object_ = layout_object;
}

void LayoutImageResource::Shutdown() {
  layout_object_ = nullptr;
  cached_image_ = nullptr;
}

scoped_refptr<Image> LayoutImageResource::GetImage(const gfx::SizeF&) const {
  return nullptr;
}

NaturalSizingInfo LayoutImageResource::GetNaturalDimensions(float) const {
  return NaturalSizingInfo::None();
}

RespectImageOrientationEnum LayoutImageResource::ImageOrientation() const {
  return kDoNotRespectImageOrientation;
}

LayoutImageResourceStyleImage::LayoutImageResourceStyleImage(
    StyleImage* style_image) {
  style_image_ = style_image;
}

LayoutImageResourceStyleImage::~LayoutImageResourceStyleImage() = default;

void LayoutImageResourceStyleImage::Trace(Visitor*) const {}

void LayoutImageResourceStyleImage::Initialize(LayoutObject* layout_object) {
  layout_object_ = layout_object;
}

void LayoutImageResourceStyleImage::Shutdown() {
  layout_object_ = nullptr;
  style_image_ = nullptr;
}

scoped_refptr<Image> LayoutImageResourceStyleImage::GetImage(
    const gfx::SizeF&) const {
  return nullptr;
}

NaturalSizingInfo LayoutImageResourceStyleImage::GetNaturalDimensions(
    float) const {
  return NaturalSizingInfo::None();
}

RespectImageOrientationEnum LayoutImageResourceStyleImage::ImageOrientation()
    const {
  return kDoNotRespectImageOrientation;
}

std::optional<double> ContainerQueryEvaluator::Width() const {
  return std::nullopt;
}

std::optional<double> ContainerQueryEvaluator::Height() const {
  return std::nullopt;
}

bool PhysicalFragment::IsImplicitAnchor() const {
  return false;
}

const GCedHeapVector<SplitAxisItem<LayoutBoxModelObject>>&
PhysicalFragment::StickyDescendants() const {
  return *static_cast<const GCedHeapVector<
      SplitAxisItem<LayoutBoxModelObject>>*>(nullptr);
}

ShapeOutsideInfo::InfoMap& ShapeOutsideInfo::GetInfoMap() {
  return *static_cast<ShapeOutsideInfo::InfoMap*>(nullptr);
}

void MeasureCache::LayoutObjectWillBeDestroyed() {}

void PaintLayerScrollableArea::SetScrollOffsetUnconditionally(
    const ScrollOffset&,
    mojom::blink::ScrollType) {}

void PaintLayerScrollableArea::EnqueueForSnapUpdateIfNeeded() {}

int PaintLayerScrollableArea::VerticalScrollbarWidth(
    OverlayScrollbarClipBehavior) const {
  return 0;
}

int PaintLayerScrollableArea::HorizontalScrollbarHeight(
    OverlayScrollbarClipBehavior) const {
  return 0;
}

LayoutUnit PaintLayerScrollableArea::ScrollWidth() const {
  return LayoutUnit();
}

LayoutUnit PaintLayerScrollableArea::ScrollHeight() const {
  return LayoutUnit();
}

gfx::Vector2d PaintLayerScrollableArea::ScrollOffsetInt() const {
  return gfx::Vector2d();
}

ScrollOffset PaintLayerScrollableArea::GetScrollOffset() const {
  return ScrollOffset();
}

PhysicalAxes PaintLayerScrollableArea::ScrollableAxes() const {
  return PhysicalAxes();
}

void PrepopulatedComputedStylePropertyMap::UpdateStyle(
    const Document&,
    const ComputedStyle&) {}

void StyleResolverState::UpdateLengthConversionData() const {}

const CSSValue& StyleResolverState::ResolveGradients(
    const CSSValue& value) const {
  return value;
}

CSSValue& StyleResolverState::ResolveGradients(CSSValue& value) const {
  return value;
}

const FontDescription& StyleResolverState::ParentFontDescription() const {
  static const FontDescription description;
  return description;
}

StyleImage* ElementStyleResources::GetStyleImage(CSSPropertyID,
                                                 const CSSValue&) {
  return nullptr;
}

bool HTMLInputElement::IsButton() const {
  return false;
}

bool CSSQuadValue::HasRandomFunctions() const {
  return false;
}

void StyleRuleBase::Trace(Visitor*) const {}

void CSSValue::Trace(Visitor*) const {}

CSSValuePool& CssValuePool() {
  alignas(CSSValuePool) static unsigned char storage[sizeof(CSSValuePool)] = {};
  return *reinterpret_cast<CSSValuePool*>(storage);
}

const RuleInvalidationData& RuleFeatureSet::GetRuleInvalidationData() const {
  alignas(RuleInvalidationData) static unsigned char
      storage[sizeof(RuleInvalidationData)] = {};
  return *reinterpret_cast<RuleInvalidationData*>(storage);
}

int OutlinePainter::OutlineOutsetExtent(const ComputedStyle&,
                                        const LayoutObject::OutlineInfo&) {
  return 0;
}

const LayoutResult* BlockNode::Layout(const ConstraintSpace&,
                                      const BlockBreakToken*,
                                      const EarlyBreak*,
                                      const ColumnSpannerPath*) const {
  return nullptr;
}

MinMaxSizesResult BlockNode::ComputeMinMaxSizes(
    WritingMode,
    const SizeType,
    const ConstraintSpace&,
    const MinMaxSizesFloatInput) const {
  return MinMaxSizesResult();
}

void LayoutResult::CopyMutableOutOfFlowData(const LayoutResult&) const {}

unsigned DisableLayoutSideEffectsScope::count_ = 0;

bool Frame::IsMainFrame() const {
  return true;
}

Page* Frame::GetPage() const {
  return nullptr;
}

LayoutEmbeddedContent* Frame::OwnerLayoutObject() const {
  return nullptr;
}

InputMethodController& LocalFrame::GetInputMethodController() const {
  return *static_cast<InputMethodController*>(nullptr);
}

String Locale::QueryString(int) {
  return String();
}

const std::optional<float>& SimpleFontData::IdeographicInlineSize() const {
  static const std::optional<float>* value = new std::optional<float>();
  return *value;
}

Color ComputedStyle::GetInternalForcedVisitedCurrentColor(bool*) const {
  return blink::Color();
}

EScrollbarWidth ComputedStyle::UsedScrollbarWidth() const {
  return EScrollbarWidth::kAuto;
}

bool ComputedStyle::HasCustomScrollbarStyle(Element*) const {
  return false;
}

float ComputedStyle::ComputedLineHeight(const Length&, const Font&) {
  return 0.0f;
}

bool ComputedStyle::ShadowListHasCurrentColor(const ShadowList*) {
  return false;
}

bool ComputedStyle::GapRuleColorIsTransparent(
    const GapDataList<StyleColor>&) const {
  return true;
}

bool ComputedStyle::ShouldApplyAnyContainment(const Element&,
                                              const DisplayStyle&,
                                              unsigned) {
  return false;
}

LayoutUnit ComputedStyle::ComputedLineHeightAsFixed() const {
  return LayoutUnit();
}

String ComputedStyle::ApplyTextTransform(const String& text,
                                         UChar,
                                         TextOffsetMap*) const {
  return text;
}

Color ComputedStyle::GetCurrentColor(bool*) const {
  return blink::Color();
}

Color ComputedStyle::VisitedDependentColor(const Longhand&, bool*) const {
  return blink::Color();
}

StyleDifference ComputedStyle::VisualInvalidationDiff(
    const Document&,
    const ComputedStyle&) const {
  return StyleDifference();
}

bool ComputedStyle::MarkerShouldBeInside(const Element&,
                                         const DisplayStyle&) const {
  return false;
}

const ComputedStyle* ComputedStyle::GetCachedPseudoElementStyle(
    PseudoId,
    const AtomicString&) const {
  return nullptr;
}

const ComputedGridTrackList& ComputedStyle::ComputedGridTemplate(
    const Member<ComputedGridTrackList>&) {
  return *static_cast<const ComputedGridTrackList*>(nullptr);
}

gfx::SizeF LayoutView::LargeViewportSizeForViewportUnits() const {
  return gfx::SizeF();
}

gfx::SizeF LayoutView::SmallViewportSizeForViewportUnits() const {
  return gfx::SizeF();
}

gfx::SizeF LayoutView::DynamicViewportSizeForViewportUnits() const {
  return gfx::SizeF();
}

ColorChannelKeyword CSSValueIDToColorChannelKeyword(CSSValueID) {
  return ColorChannelKeyword::kR;
}

CSSValueID ColorChannelKeywordToCSSValueID(ColorChannelKeyword) {
  return CSSValueID::kInvalid;
}

CSSPropertyID ResolveCSSPropertyAlias(CSSPropertyID property_id) {
  return property_id;
}

int ResolveCSSPropertyAlias(int property_id) {
  return property_id;
}

ComputedStyleBuilder::ComputedStyleBuilder(const ComputedStyle& style)
    : ComputedStyleBuilderBase(style) {}

const ComputedStyle* ComputedStyleBuilder::TakeStyle() {
  return nullptr;
}

Image::Image(ImageObserver*, bool is_multipart)
    : image_observer_disabled_(false),
      image_observer_(nullptr),
      stable_image_id_(0),
      is_multipart_(is_multipart) {}
Image::~Image() = default;

Image::SizeAvailability Image::SetData(scoped_refptr<SharedBuffer>, bool) {
  return kSizeUnavailable;
}

String Image::FilenameExtension() const {
  return String();
}

const AtomicString& Image::MimeType() const {
  return g_null_atom;
}

mojom::blink::ImageAnimationPolicy Image::AnimationPolicy() {
  return mojom::blink::ImageAnimationPolicy::kImageAnimationPolicyAllowed;
}

scoped_refptr<Image> Image::ImageForDefaultFrame() {
  return this;
}

bool Image::ApplyShader(cc::PaintFlags&,
                        const SkMatrix&,
                        const gfx::RectF&,
                        const ImageDrawOptions&) {
  return false;
}

void PaintLayer::UpdateOffsetPath(const ComputedStyle*, const ComputedStyle&) {}

void PaintLayer::Trace(Visitor*) const {}

String PaintLayer::DebugName() const {
  return String();
}

DOMNodeId PaintLayer::OwnerNodeId(bool) const {
  return 0;
}

std::unique_ptr<Gradient> Gradient::CreateLinear(
    const gfx::PointF&,
    const gfx::PointF&,
    SpreadMethod,
    PremultipliedAlpha,
    DegenerateHandling) {
  return nullptr;
}

std::unique_ptr<Gradient> Gradient::CreateRadial(const gfx::PointF&,
                                                 float,
                                                 const gfx::PointF&,
                                                 float,
                                                 float,
                                                 SpreadMethod,
                                                 PremultipliedAlpha,
                                                 DegenerateHandling) {
  return nullptr;
}

std::unique_ptr<Gradient> Gradient::CreateConic(const gfx::PointF&,
                                                float,
                                                float,
                                                float,
                                                SpreadMethod,
                                                PremultipliedAlpha,
                                                DegenerateHandling) {
  return nullptr;
}

void Gradient::AddColorStops(const Vector<Gradient::ColorStop>&) {}

const CSSValue& CSSValue::PopulateWithTreeScope(const TreeScope*) const {
  return *this;
}

void Image::DrawPattern(GraphicsContext&,
                        const cc::PaintFlags&,
                        const gfx::RectF&,
                        const ImageTilingInfo&,
                        const ImageDrawOptions&) {}

HTMLBodyElement* Document::FirstBodyElement() const {
  return nullptr;
}

unsigned PrePaintDisableSideEffectsScope::count_ = 0;

gfx::RectF SVGResources::ReferenceBoxForEffects(
    const LayoutObject&,
    GeometryBox,
    ForeignObjectQuirk) {
  return gfx::RectF();
}

PhysicalOffset StickyPositionScrollingConstraints::StickyOffset() const {
  return PhysicalOffset();
}

StickyPositionScrollingConstraints::PerAxisData::PerAxisData(
    PhysicalAxis axis,
    const PhysicalRect&,
    const PhysicalRect&,
    const PhysicalRect&,
    const LayoutObject* location_container,
    const LayoutBox* sticky_container,
    const PaintLayer* containing_scroll_container_layer,
    bool is_fixed_to_view,
    std::optional<LayoutUnit> min_inset,
    std::optional<LayoutUnit> max_inset,
    std::optional<LayoutUnit> min_inset_for_get_computed_style,
    std::optional<LayoutUnit> max_inset_for_get_computed_style)
    : axis(axis),
      min_inset(min_inset),
      max_inset(max_inset),
      min_inset_for_get_computed_style(min_inset_for_get_computed_style),
      max_inset_for_get_computed_style(max_inset_for_get_computed_style),
      location_container(location_container),
      sticky_container(sticky_container),
      containing_scroll_container_layer(containing_scroll_container_layer),
      is_fixed_to_view(is_fixed_to_view) {}

void StickyPositionScrollingConstraints::PerAxisData::Trace(Visitor*) const {}

ContainerNode* FlatTreeTraversal::TraverseParent(const Node&) {
  return nullptr;
}

LayoutBoxModelObject* Node::GetLayoutBoxModelObject() const {
  return nullptr;
}

PhysicalOffset PhysicalBoxFragment::OffsetFromOwnerLayoutBox() const {
  return PhysicalOffset();
}

void LayoutBlockFlow::Trace(Visitor*) const {}

bool LayoutBox::MayIntersect(const HitTestResult&,
                             const HitTestLocation&,
                             const PhysicalOffset&) const {
  return false;
}

const PhysicalBoxFragment* PhysicalBoxFragment::PostLayout() const {
  return this;
}

const PhysicalBoxFragment* LayoutBox::GetPhysicalFragment(wtf_size_t) const {
  return nullptr;
}

void PhysicalBoxFragment::AddSelfOutlineRects(
    const PhysicalOffset&,
    OutlineType,
    OutlineRectCollector&,
    LayoutObject::OutlineInfo*) const {}

const LayoutBox* PhysicalBoxFragment::OwnerLayoutBox() const {
  return nullptr;
}

void PhysicalBoxFragment::AssertFragmentTreeChildren(bool) const {}

void ObjectPaintInvalidator::InvalidateDisplayItemClient(
    const DisplayItemClient&,
    PaintInvalidationReason) {}

void ObjectPaintInvalidator::SlowSetPaintingLayerNeedsRepaint() {}

void BoxFragmentPainter::PaintTextClipMask(const PaintInfo&,
                                           const gfx::Rect&,
                                           const PhysicalOffset&,
                                           bool) {}

PhysicalRect BoxFragmentPainter::AdjustRectForScrolledContent(
    GraphicsContext&,
    const PhysicalBoxStrut&,
    const PhysicalRect& rect) const {
  return rect;
}

BoxPainterBase::FillLayerInfo BoxFragmentPainter::GetFillLayerInfo(
    const Color& color,
    const FillLayer& fill_layer,
    BackgroundBleedAvoidance bleed_avoidance,
    bool is_painting_background_in_contents_space,
    PaintFlags paint_flags) const {
  return BoxPainterBase::FillLayerInfo(
      *static_cast<const Document*>(nullptr),
      *static_cast<const ComputedStyle*>(nullptr), false, color, fill_layer,
      bleed_avoidance, PhysicalBoxSides(), false,
      is_painting_background_in_contents_space, paint_flags);
}

BoxPainterBase::FillLayerInfo::FillLayerInfo(
    const Document&,
    const ComputedStyle&,
    bool,
    Color bg_color,
    const FillLayer&,
    BackgroundBleedAvoidance,
    PhysicalBoxSides sides,
    bool,
    bool,
    PaintFlags)
    : image(nullptr),
      color(bg_color),
      respect_image_orientation(kDoNotRespectImageOrientation),
      sides_to_include(sides),
      is_bottom_layer(false),
      is_border_fill(false),
      is_clipped_with_local_scrolling(false),
      is_rounded_fill(false),
      is_printing(false),
      should_paint_image(false),
      should_paint_color(false),
      should_paint_color_with_paint_worklet_image(false) {}

LogicalOffset WritingModeConverter::SlowToLogical(
    const PhysicalOffset& offset,
    const PhysicalSize&) const {
  return LogicalOffset(offset.left, offset.top);
}

LogicalRect WritingModeConverter::SlowToLogical(const PhysicalRect& rect) const {
  return LogicalRect(SlowToLogical(rect.offset, rect.size),
                     ToLogical(rect.size));
}

PhysicalRect WritingModeConverter::SlowToPhysical(
    const LogicalRect& rect) const {
  PhysicalSize physical_size = ToPhysical(rect.size);
  return PhysicalRect(ToPhysical(rect.offset, physical_size), physical_size);
}

PhysicalOffset WritingModeConverter::SlowToPhysical(
    const LogicalOffset& offset,
    const PhysicalSize&) const {
  return PhysicalOffset(offset.inline_offset, offset.block_offset);
}

void ExceptionState::ThrowTypeError(const char*) {}

const WrapperTypeInfo& CSSKeywordValue::wrapper_type_info_ =
    *static_cast<const WrapperTypeInfo*>(nullptr);
const WrapperTypeInfo& CSSStyleValue::wrapper_type_info_ =
    *static_cast<const WrapperTypeInfo*>(nullptr);

unsigned LengthOfGraphemeCluster(const StringView& string, unsigned offset) {
  return offset < string.length() ? 1u : 0u;
}

LayoutSelectionStatus FrameSelection::ComputeLayoutSelectionStatus(
    const InlineCursor&) const {
  return LayoutSelectionStatus(0, 0, SelectSoftLineBreak::kNotSelected);
}

std::ostream& operator<<(std::ostream& ostream, const Position&) {
  return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const FragmentItem*) {
  return ostream;
}

unsigned NthIndexCache::NthChildIndex(
    Element&,
    const CSSSelectorList*,
    const SelectorChecker*,
    const SelectorChecker::SelectorCheckingContext*) {
  return 1;
}

unsigned NthIndexCache::NthLastChildIndex(
    Element&,
    const CSSSelectorList*,
    const SelectorChecker*,
    const SelectorChecker::SelectorCheckingContext*) {
  return 1;
}

double StyleEngine::GetCachedRandomBaseValue(const RandomCacheKey&,
                                             const Element*) {
  return 0.5;
}

void CascadeLayer::Trace(Visitor*) const {}

void Filter::Trace(Visitor*) const {}

Locale::~Locale() = default;

bool TransformOperations::operator==(const TransformOperations&) const {
  return true;
}

bool RuntimeEnabledFeaturesBase::
    is_decouple_resolved_column_rule_width_from_style_enabled_ = false;

TextOffsetMap::TextOffsetMap(wtf_size_t,
                             const TextOffsetMap&,
                             wtf_size_t,
                             const TextOffsetMap&,
                             wtf_size_t) {}

void TextOffsetMap::Append(wtf_size_t source, wtf_size_t target) {
  entries_.push_back(Entry(source, target));
}

void TextOffsetMap::Append(const icu::Edits&) {}

template <>
String FixedPoint<6, int>::ToString() const {
  return String();
}

CSSValue* StylePath::ComputedCSSValue() const {
  return nullptr;
}

SVGPathByteStreamBuilder::SVGPathByteStreamBuilder() = default;

SVGPathByteStream SVGPathByteStreamBuilder::CopyByteStream() {
  return SVGPathByteStream();
}

void SVGPathByteStreamBuilder::EmitSegment(const PathSegmentData&) {}

SVGParsingError BuildByteStreamFromString(const StringView&,
                                          SVGPathByteStreamBuilder&) {
  return SVGParsingError(SVGParseStatus::kParsingFailed);
}

namespace cssvalue {

CSSPathValue::CSSPathValue(SVGPathByteStream,
                           WindRule,
                           PathSerializationFormat)
    : CSSValue(kBasicShapePathClass),
      serialization_format_(kNoTransformation),
      style_path_(nullptr) {}

}  // namespace cssvalue

std::array<std::atomic_int, InstanceCounters::kCounterTypeLength>
    InstanceCounters::counters_;
int InstanceCounters::node_counter_ = 0;

void ShowTree(const Node*) {}

}  // namespace blink

namespace logging {

void SetLogItems(bool, bool, bool, bool) {}

}  // namespace logging

namespace base {

AtomicFlag::~AtomicFlag() {}

namespace internal {

WeakReference::WeakReference() = default;
WeakReference::Flag::~Flag() {}
WeakReferenceOwner::~WeakReferenceOwner() {}
WeakPtrFactoryBase::~WeakPtrFactoryBase() {}

}  // namespace internal

File::~File() {}
FilePath::~FilePath() {}
FileTracing::ScopedEnabler::~ScopedEnabler() {}
MemoryMappedFile::~MemoryMappedFile() {}

namespace win {

void VerifierTraits::StopTracking(void*, const void*, const void*, const void*) {}

bool HandleTraits::CloseHandle(void*) {
  return true;
}

}  // namespace win

bool DelayedTaskHandle::IsValid() const {
  return false;
}

}  // namespace base

namespace cc {

PaintImage::PaintImage() = default;
const int PaintImage::kInvalidId = 0;
const int PaintImage::kInvalidContentId = 0;
Region::Region() = default;
Region::~Region() = default;

void Region::Union(const gfx::Rect&) {}

}  // namespace cc

namespace gfx {

HDRMetadata::HDRMetadata() = default;

bool Vector2dF::IsZero() const {
  return x() == 0 && y() == 0;
}

void Vector2dF::Add(const Vector2dF& other) {
  set_x(x() + other.x());
  set_y(y() + other.y());
}

void Vector2dF::Subtract(const Vector2dF& other) {
  set_x(x() - other.x());
  set_y(y() - other.y());
}

double Vector2dF::LengthSquared() const {
  return static_cast<double>(x()) * x() + static_cast<double>(y()) * y();
}

float Vector2dF::Length() const {
  return std::sqrt(static_cast<float>(LengthSquared()));
}

float Vector2dF::SlopeAngleRadians() const {
  return std::atan2(y(), x());
}

void Vector2dF::Scale(float x_scale, float y_scale) {
  set_x(x() * x_scale);
  set_y(y() * y_scale);
}

Vector2dF ScaleVector2d(const Vector2dF& vector, float x_scale, float y_scale) {
  return Vector2dF(vector.x() * x_scale, vector.y() * y_scale);
}

PointF ScalePoint(const PointF& point, float x_scale, float y_scale) {
  return PointF(point.x() * x_scale, point.y() * y_scale);
}

SizeF ScaleSize(const SizeF& size, float x_scale, float y_scale) {
  return SizeF(size.width() * x_scale, size.height() * y_scale);
}

Size ToRoundedSize(const SizeF& size) {
  return Size(static_cast<int>(std::round(size.width())),
              static_cast<int>(std::round(size.height())));
}

Rect ToEnclosingRect(const RectF& rect) {
  const int left = static_cast<int>(std::floor(rect.x()));
  const int top = static_cast<int>(std::floor(rect.y()));
  const int right = static_cast<int>(std::ceil(rect.right()));
  const int bottom = static_cast<int>(std::ceil(rect.bottom()));
  return Rect(left, top, right - left, bottom - top);
}

bool Rect::Contains(int point_x, int point_y) const {
  return point_x >= x() && point_x < right() && point_y >= y() &&
         point_y < bottom();
}

void Rect::Union(const Rect& rect) {
  const int left = std::min(x(), rect.x());
  const int top = std::min(y(), rect.y());
  const int right_edge = std::max(right(), rect.right());
  const int bottom_edge = std::max(bottom(), rect.bottom());
  SetRect(left, top, right_edge - left, bottom_edge - top);
}

void RectF::Offset(float horizontal, float vertical) {
  SetRect(x() + horizontal, y() + vertical, width(), height());
}

void RectF::Union(const RectF& rect) {
  UnionEvenIfEmpty(rect);
}

void RectF::UnionEvenIfEmpty(const RectF& rect) {
  const float left = std::min(x(), rect.x());
  const float top = std::min(y(), rect.y());
  const float right_edge = std::max(right(), rect.right());
  const float bottom_edge = std::max(bottom(), rect.bottom());
  SetRect(left, top, right_edge - left, bottom_edge - top);
}

PointF RectF::CenterPoint() const {
  return PointF(x() + width() / 2.0f, y() + height() / 2.0f);
}

void QuadF::Scale(float x_scale, float y_scale) {
  p1_.Scale(x_scale, y_scale);
  p2_.Scale(x_scale, y_scale);
  p3_.Scale(x_scale, y_scale);
  p4_.Scale(x_scale, y_scale);
}

CubicBezier::CubicBezier(double, double, double, double) {}
CubicBezier::CubicBezier(const CubicBezier&) {}
double CubicBezier::Solve(double x) const { return x; }
double CubicBezier::SolveCurveX(double x, double) const { return x; }
double CubicBezier::Slope(double) const { return 0; }
double CubicBezier::GetX1() const { return 0; }
double CubicBezier::GetY1() const { return 0; }
double CubicBezier::GetX2() const { return 1; }
double CubicBezier::GetY2() const { return 1; }
double CubicBezier::ToFinite(double value) { return value; }

void Transform::Zoom(float) {}
void Transform::Scale(float, float) {}
void Transform::Scale3d(float, float, float) {}
void Transform::Translate(float, float) {}
void Transform::PostTranslate(float, float) {}
void Transform::Translate3d(float, float, float) {}
void Transform::RotateAboutZAxis(double) {}
void Transform::RotateAbout(const Vector3dF&, double) {}
void Transform::Skew(double, double) {}
void Transform::PreConcat(const Transform&) {}
void Transform::ApplyPerspectiveDepth(double) {}
void Transform::ApplyTransformOrigin(float, float, float) {}
bool Transform::Accumulate(const Transform&) { return true; }
bool Transform::Blend(const Transform&, double) { return true; }
bool Transform::Is2dTransform() const { return true; }
bool Transform::Is2dProportionalUpscaleAndOr2dTranslation() const {
  return true;
}
bool Transform::Creates3d() const { return false; }
bool Transform::Preserves2dAxisAlignment() const { return true; }
Matrix44 Transform::GetFullMatrix() const { return Matrix44(); }
std::optional<DecomposedTransform> Transform::Decompose() const {
  return DecomposedTransform();
}
Transform Transform::Compose(const DecomposedTransform&) {
  return Transform();
}
Transform Transform::operator*(const Transform&) const { return *this; }
PointF Transform::MapPoint(const PointF& point) const { return point; }
RectF Transform::MapRect(const RectF& rect) const { return rect; }
QuadF Transform::MapQuad(const QuadF& quad) const { return quad; }

bool Vector3dF::IsZero() const {
  return x() == 0 && y() == 0 && z() == 0;
}

double Vector3dF::LengthSquared() const {
  return static_cast<double>(x()) * x() + static_cast<double>(y()) * y() +
         static_cast<double>(z()) * z();
}

bool Vector3dF::GetNormalized(Vector3dF* out) const {
  if (out) {
    *out = *this;
  }
  return !IsZero();
}

float DotProduct(const Vector3dF& lhs, const Vector3dF& rhs) {
  return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

Quaternion Quaternion::FromAxisAngle(double x,
                                     double y,
                                     double z,
                                     double angle) {
  return Quaternion(x, y, z, angle);
}

Quaternion Quaternion::Slerp(const Quaternion& q, double) const {
  return q;
}

}  // namespace gfx

namespace cppgc::internal {

PersistentRegion& WeakPersistentPolicy::GetPersistentRegion(const void*) {
  return *static_cast<PersistentRegion*>(nullptr);
}

PersistentRegion& StrongPersistentPolicy::GetPersistentRegion(const void*) {
  return *static_cast<PersistentRegion*>(nullptr);
}

bool PersistentRegion::IsCreationThread() {
  return true;
}

PersistentNode* PersistentRegionBase::RefillFreeListAndAllocateNode(
    void*,
    TraceRootCallback) {
  return nullptr;
}

void FatalImpl(const char*, v8::SourceLocation) {}

void DCheckImpl(const char*, v8::SourceLocation) {}

void WriteBarrier::SteeleMarkingBarrierSlowWithSentinelCheck(const void*) {}

}  // namespace cppgc::internal

namespace cppgc::subtle {

bool HeapState::IsMarking(const HeapHandle&) {
  return false;
}

bool HeapState::IsInAtomicPause(const HeapHandle&) {
  return false;
}

}  // namespace cppgc::subtle

SkRegion::SkRegion() = default;
SkRegion::~SkRegion() = default;

float skcms_TransferFunction_eval(const skcms_TransferFunction*, float value) {
  return value;
}

bool skcms_TransferFunction_invert(const skcms_TransferFunction* source,
                                   skcms_TransferFunction* destination) {
  if (source && destination) {
    *destination = *source;
  }
  return true;
}

bool skcms_AdaptToXYZD50(float, float, skcms_Matrix3x3*) {
  return false;
}

template <>
SkColor SkColor4f::toSkColor() const {
  return SkColorSetARGB(static_cast<unsigned>(fA * 255.0f),
                        static_cast<unsigned>(fR * 255.0f),
                        static_cast<unsigned>(fG * 255.0f),
                        static_cast<unsigned>(fB * 255.0f));
}

void ShowTree(const blink::Node*) {}
