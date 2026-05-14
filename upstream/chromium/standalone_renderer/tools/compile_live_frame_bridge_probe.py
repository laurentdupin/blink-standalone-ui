#!/usr/bin/env python3
"""Compile the live Blink frame bridge probe without full Ninja regeneration.

The local Chromium checkout can regenerate the global Ninja graph, but doing so
is still very expensive and often pulls unrelated Chrome/PDF/GPU targets into
iteration. This helper uses an existing compile-command dump as a toolchain
template and compiles only the real-Blink live-frame island:

  DummyPageHolder -> Document mutation -> lifecycle -> PaintArtifact access.
"""

from __future__ import annotations

import argparse
import pathlib
import subprocess
import sys

import relink_blink_tree_builder_probe as relink


TEMPLATE_COMMAND_DUMP = "blink_dom_link_probe.commands.txt"
TEMPLATE_SOURCE = "../../standalone_renderer/tests/blink_dom_link_probe.cc"
TEMPLATE_OBJECT = "obj/standalone_renderer/blink_dom_link_probe/blink_dom_link_probe.obj"
RUNTIME_ADAPTER_COMMAND_DUMP = "html_css_renderer_blink_cli.commands.txt"
RUNTIME_ADAPTER_SOURCE = "../../standalone_renderer/src/blink_runtime_adapter.cc"
SMOKE_SOURCE = "../../standalone_renderer/tests/live_frame_bridge_link_probe.cc"
SMOKE_OBJECT = (
    "obj/standalone_renderer/blink_live_frame_bridge_probe/"
    "live_frame_bridge_link_probe.obj"
)

LIVE_BRIDGE_SOURCES = (
    (
        "../../third_party/blink/renderer/core/standalone_live_frame_bridge_probe.cc",
        "obj/standalone_renderer/blink_live_frame_bridge_probe/"
        "standalone_live_frame_bridge_probe.obj",
    ),
    (
        "../../third_party/blink/renderer/core/testing/dummy_page_holder.cc",
        "obj/standalone_renderer/blink_live_frame_bridge_probe/"
        "dummy_page_holder.obj",
    ),
)

LIVE_CORE_ISLAND_SOURCES = (
    "core/page/chrome_client.cc",
    "core/page/page.cc",
    "core/frame/settings.cc",
    "core/frame/policy_container.cc",
    "core/frame/local_dom_window.cc",
    "core/frame/local_frame.cc",
    "core/frame/local_frame_view.cc",
    "core/frame/root_frame_viewport.cc",
    "core/frame/viewport_data.cc",
    "core/frame/layout_subtree_root_list.cc",
    "core/dom/character_data.cc",
    "core/dom/container_node.cc",
    "core/dom/document.cc",
    "core/dom/document_init.cc",
    "core/dom/document_parser.cc",
    "core/dom/document_fragment.cc",
    "core/dom/dom_implementation.cc",
    "core/dom/comment.cc",
    "core/dom/document_type.cc",
    "core/dom/xml_document.cc",
    "core/dom/element.cc",
    "core/dom/element_data.cc",
    "core/dom/element_rare_data_vector.cc",
    "core/dom/node.cc",
    "core/dom/child_node_list.cc",
    "core/dom/document_lifecycle.cc",
    "core/dom/empty_node_list.cc",
    "core/dom/flat_tree_traversal.cc",
    "core/dom/live_node_list_base.cc",
    "core/dom/live_node_list.cc",
    "core/dom/node_lists_node_data.cc",
    "core/dom/node_traversal.cc",
    "core/dom/nth_index_cache.cc",
    "core/dom/shadow_root.cc",
    "core/dom/tree_ordered_map.cc",
    "core/dom/id_target_observer.cc",
    "core/dom/id_target_observer_registry.cc",
    "core/dom/slot_assignment.cc",
    "core/dom/slot_assignment_engine.cc",
    "core/dom/space_split_string.cc",
    "core/dom/tag_collection.cc",
    "core/dom/text.cc",
    "core/dom/tree_scope.cc",
    "core/dom/tree_scope_adopter.cc",
    "core/dom/decoded_data_document_parser.cc",
    "core/dom/scriptable_document_parser.cc",
    "core/dom/user_action_element_set.cc",
    "core/dom/names_map.cc",
    "core/dom/layout_tree_builder_traversal.cc",
    "core/dom/layout_tree_builder.cc",
    "core/dom/whitespace_attacher.cc",
    "core/dom/events/event_target.cc",
    "core/dom/events/event_target_impl.cc",
    "core/css/cascade_layer.cc",
    "core/css/cascade_layer_map.cc",
    "core/css/check_pseudo_has_cache_scope.cc",
    "core/css/active_style_sheets.cc",
    "core/css/container_query_set.cc",
    "core/css/container_query.cc",
    "core/css/container_selector.cc",
    "core/css/container_query_evaluator.cc",
    "core/css/counter_style.cc",
    "core/css/counter_style_map.cc",
    "core/css/abstract_property_set_css_style_declaration.cc",
    "core/css/css_global_rule_set.cc",
    "core/css/css_keyframes_rule.cc",
    "core/css/css_crossfade_value.cc",
    "core/css/css_default_style_sheets.cc",
    "core/css/css_identifier_value.cc",
    "core/css/css_image_generator_value.cc",
    "core/css/css_image_set_option_value.cc",
    "core/css/css_image_set_type_value.cc",
    "core/css/css_image_set_value.cc",
    "core/css/css_path_value.cc",
    "core/css/css_position_try_rule.cc",
    "core/css/css_property_value_set.cc",
    "core/css/css_selector.cc",
    "core/css/css_selector_list.cc",
    "core/css/css_quad_value.cc",
    "core/css/css_style_sheet.cc",
    "core/css/css_url_data.cc",
    "core/css/css_url_pattern_value.cc",
    "core/css/css_value_pool.cc",
    "core/css/inline_css_style_declaration.cc",
    "core/css/cssom/inline_style_property_map.cc",
    "core/css/document_style_environment_variables.cc",
    "core/css/element_rule_collector.cc",
    "core/css/invalidation/invalidation_set.cc",
    "core/css/invalidation/invalidation_flags.cc",
    "core/css/invalidation/pending_invalidations.cc",
    "core/css/invalidation/rule_invalidation_data.cc",
    "core/css/layout_tree_rebuild_root.cc",
    "core/css/media_query.cc",
    "core/css/media_query_evaluator.cc",
    "core/css/mixin_map.cc",
    "core/css/navigation_query.cc",
    "core/css/out_of_flow_data.cc",
    "core/css/parser/container_query_parser.cc",
    "core/css/parser/css_lazy_property_parser.cc",
    "core/css/parser/css_lazy_parsing_state.cc",
    "core/css/parser/css_at_rule_id.cc",
    "core/css/parser/css_parser.cc",
    "core/css/parser/css_parser_context.cc",
    "core/css/parser/css_parser_impl.cc",
    "core/css/parser/css_parser_token.cc",
    "core/css/parser/css_parser_token_stream.cc",
    "core/css/parser/css_selector_parser.cc",
    "core/css/parser/css_supports_parser.cc",
    "core/css/parser/css_tokenizer.cc",
    "core/css/parser/css_tokenizer_input_stream.cc",
    "core/css/parser/navigation_parser.cc",
    "core/css/property_registration.cc",
    "core/css/random_caching_key.cc",
    "core/css/resolver/scoped_style_resolver.cc",
    "core/css/resolver/element_resolve_context.cc",
    "core/css/resolver/font_builder.cc",
    "core/css/resolver/style_resolver.cc",
    "core/css/resolver/style_resolver_stats.cc",
    "core/css/resolver/style_rule_usage_tracker.cc",
    "core/css/resolver/viewport_style_resolver.cc",
    "core/css/rule_feature_set.cc",
    "core/css/rule_set.cc",
    "core/css/rule_set_diff.cc",
    "core/css/scroll_target_group_scope.cc",
    "core/css/selector_filter.cc",
    "core/css/style_scope.cc",
    "core/css/style_scope_data.cc",
    "core/css/style_scope_frame.cc",
    "core/css/style_engine.cc",
    "core/css/style_environment_variables.cc",
    "core/css/style_image_cache.cc",
    "core/css/style_invalidation_root.cc",
    "core/css/style_rule.cc",
    "core/css/style_sheet_collection.cc",
    "core/css/style_sheet_candidate.cc",
    "core/css/style_rule_counter_style.cc",
    "core/css/style_rule_font_feature_values.cc",
    "core/css/style_rule_font_palette_values.cc",
    "core/css/style_rule_import.cc",
    "core/css/style_rule_keyframe.cc",
    "core/css/style_rule_route.cc",
    "core/css/part_names.cc",
    "core/css/style_rule_view_transition.cc",
    "core/css/style_sheet_contents.cc",
    "core/css/style_sheet_list.cc",
    "core/css/ua_counter_style_map.cc",
    "core/css/style_recalc_root.cc",
    "core/css/style_recalc_change.cc",
    "core/css/style_traversal_root.cc",
    "core/css/style_containment_scope.cc",
    "core/css/try_value_flips.cc",
    "core/css/successful_position_fallback.cc",
    "core/html/document_all_name_collection.cc",
    "core/html/document_name_collection.cc",
    "core/html/html_collection.cc",
    "core/html/html_dimension.cc",
    "core/html/html_element.cc",
    "core/html/html_body_element.cc",
    "core/html/html_br_element.cc",
    "core/html/html_div_element.cc",
    "core/html/html_heading_element.cc",
    "core/html/html_html_element.cc",
    "core/html/html_paragraph_element.cc",
    "core/html/html_title_element.cc",
    "core/html/html_unknown_element.cc",
    "core/html/list_item_ordinal.cc",
    "core/html/forms/form_controller.cc",
    "core/html/parser/html_document_parser.cc",
    "core/html/parser/fragment_parser.cc",
    "core/html/parser/html_parser_options.cc",
    "core/html/parser/patch.cc",
    "core/html/parser/html_tokenizer.cc",
    "core/html/parser/html_tree_builder.cc",
    "core/html/html_name_collection.cc",
    "core/html/html_slot_element.cc",
    "core/html/html_tag_collection.cc",
    "core/html/window_name_collection.cc",
    "core/html/forms/labels_node_list.cc",
    "core/html/shadow/shadow_element_utils.cc",
    "core/layout/layout_br.cc",
    "core/layout/layout_input_node.cc",
    "core/layout/layout_result.cc",
    "core/layout/constraint_space.cc",
    "core/layout/box_fragment_builder.cc",
    "core/layout/fragment_builder.cc",
    "core/layout/physical_fragment.cc",
    "core/layout/physical_fragment_rare_data.cc",
    "core/layout/physical_box_fragment.cc",
    "core/layout/block_node.cc",
    "core/layout/block_layout_algorithm.cc",
    "core/layout/block_layout_algorithm_utils.cc",
    "core/layout/block_child_iterator.cc",
    "core/layout/block_break_token.cc",
    "core/layout/break_token.cc",
    "core/layout/layout_box.cc",
    "core/layout/layout_box_hot.cc",
    "core/layout/space_utils.cc",
    "core/layout/layout_block.cc",
    "core/layout/layout_block_flow.cc",
    "core/layout/layout_utils.cc",
    "core/layout/layout_inline.cc",
    "core/layout/layout_text.cc",
    "core/layout/layout_text_combine.cc",
    "core/layout/layout_text_fragment.cc",
    "core/layout/logical_box_fragment.cc",
    "core/layout/layout_object.cc",
    "core/layout/layout_object_child_list.cc",
    "core/layout/depth_ordered_layout_object_list.cc",
    "core/layout/hit_test_cache.cc",
    "core/layout/hit_test_location.cc",
    "core/layout/layout_view.cc",
    "core/layout/layout_quote.cc",
    "core/layout/outline_rect_collector.cc",
    "core/layout/geometry/bfc_offset.cc",
    "core/layout/geometry/bfc_rect.cc",
    "core/layout/geometry/margin_strut.cc",
    "core/layout/floats_utils.cc",
    "core/layout/length_utils.cc",
    "core/layout/fragmentation_utils.cc",
    "core/layout/grid/grid_item.cc",
    "core/layout/grid/grid_line_resolver.cc",
    "core/layout/grid/grid_named_line_collection.cc",
    "core/layout/grid/grid_placement.cc",
    "core/layout/grid/grid_track_collection.cc",
    "core/layout/grid/grid_track_sizing_algorithm.cc",
    "core/layout/relative_utils.cc",
    "core/layout/anchor_map.cc",
    "core/layout/oof_positioned_node.cc",
    "core/layout/transform_utils.cc",
    "core/layout/ink_overflow.cc",
    "core/layout/line_clamp_data.cc",
    "core/layout/scrollable_overflow_calculator.cc",
    "core/layout/simplified_layout_algorithm.cc",
    "core/layout/text_decoration_offset.cc",
    "core/layout/shapes/shape_outside_info.cc",
    "core/layout/svg/layout_svg_inline_text.cc",
    "core/layout/inline/fragment_items.cc",
    "core/layout/inline/fragment_item.cc",
    "core/layout/inline/fragment_items_builder.cc",
    "core/layout/inline/inline_box_state.cc",
    "core/layout/inline/inline_child_layout_context.cc",
    "core/layout/inline/inline_cursor.cc",
    "core/layout/inline/inline_caret_position.cc",
    "core/layout/inline/inline_layout_algorithm.cc",
    "core/layout/inline/inline_node.cc",
    "core/layout/inline/inline_node_data.cc",
    "core/layout/inline/inline_break_token.cc",
    "core/layout/inline/inline_item.cc",
    "core/layout/inline/inline_item_result.cc",
    "core/layout/inline/inline_item_segment.cc",
    "core/layout/inline/inline_items_builder.cc",
    "core/layout/inline/inline_items_data.cc",
    "core/layout/inline/line_box_fragment_builder.cc",
    "core/layout/inline/line_breaker.cc",
    "core/layout/inline/line_break_candidate.cc",
    "core/layout/inline/line_info.cc",
    "core/layout/inline/line_truncator.cc",
    "core/layout/inline/line_widths.cc",
    "core/layout/inline/paragraph_line_breaker.cc",
    "core/layout/inline/score_line_breaker.cc",
    "core/layout/inline/justification_utils.cc",
    "core/layout/inline/logical_line_item.cc",
    "core/layout/inline/logical_line_container.cc",
    "core/layout/inline/offset_mapping.cc",
    "core/layout/inline/offset_mapping_builder.cc",
    "core/layout/inline/physical_line_box_fragment.cc",
    "core/layout/inline/ruby_utils.cc",
    "core/layout/inline/text_auto_space.cc",
    "core/layout/inline/hyphen_result.cc",
    "core/layout/exclusions/exclusion_area.cc",
    "core/layout/exclusions/exclusion_space.cc",
    "core/layout/exclusions/layout_opportunity.cc",
    "core/layout/positioned_float.cc",
    "core/layout/inline/fit_text_utils.cc",
    "core/layout/inline/initial_letter_utils.cc",
    "core/layout/inline/line_utils.cc",
    "core/layout/inline/logical_line_builder.cc",
    "core/layout/inline/transformed_string.cc",
    "core/layout/svg/svg_text_layout_attributes_builder.cc",
    "core/layout/list/layout_inline_list_item.cc",
    "core/layout/list/layout_list_item.cc",
    "core/layout/list/layout_outside_list_marker.cc",
    "core/layout/list/unpositioned_list_marker.cc",
    "core/layout/list/list_marker.cc",
    "core/layout/geometry/transform_state.cc",
    "core/layout/geometry/logical_rect.cc",
    "core/paint/border_shape_painter.cc",
    "core/paint/border_shape_utils.cc",
    "core/paint/box_border_painter.cc",
    "core/paint/box_fragment_painter.cc",
    "core/paint/box_painter_base.cc",
    "core/paint/box_painter.cc",
    "core/paint/box_background_paint_context.cc",
    "core/paint/box_decoration_data.cc",
    "core/paint/box_model_object_painter.cc",
    "core/paint/box_reflection_utils.cc",
    "core/paint/contoured_border_geometry.cc",
    "core/paint/cull_rect_updater.cc",
    "core/paint/fragment_data_iterator.cc",
    "core/paint/fragment_data.cc",
    "core/paint/frame_painter.cc",
    "core/paint/fieldset_painter.cc",
    "core/paint/fragment_painter.cc",
    "core/paint/frame_set_painter.cc",
    "core/paint/gap_decorations_painter.cc",
    "core/paint/geometry_box_utils.cc",
    "core/paint/hit_testing_transform_state.cc",
    "core/paint/inline_box_fragment_painter.cc",
    "core/paint/object_painter.cc",
    "core/paint/outline_painter.cc",
    "core/paint/nine_piece_image_painter.cc",
    "core/paint/clip_rect.cc",
    "core/paint/paint_layer_clipper.cc",
    "core/paint/paint_layer.cc",
    "core/paint/paint_layer_paint_order_iterator.cc",
    "core/paint/paint_layer_painter.cc",
    "core/paint/paint_layer_resource_info.cc",
    "core/paint/paint_property_tree_builder.cc",
    "core/paint/paint_invalidator.cc",
    "core/paint/object_paint_invalidator.cc",
    "core/paint/pre_paint_tree_walk.cc",
    "core/paint/scrollable_area_painter.cc",
    "core/paint/scoped_paint_state.cc",
    "core/paint/scoped_svg_paint_state.cc",
    "core/paint/table_painters.cc",
    "core/paint/text_decoration_info.cc",
    "core/paint/text_fragment_painter.cc",
    "core/paint/text_painter.cc",
    "core/paint/theme_painter.cc",
    "core/paint/theme_painter_default.cc",
    "core/paint/url_metadata_utils.cc",
    "core/paint/view_painter.cc",
    "core/view_transition/view_transition_utils.cc",
    "core/scroll/scroll_alignment.cc",
    "core/scroll/scroll_animator_base.cc",
    "core/scroll/scroll_into_view_util.cc",
    "core/scroll/scrollable_area.cc",
    "core/layout/scroll_anchor.cc",
    "core/route_matching/route_match_state.cc",
    "core/css/css_initial_color_value.cc",
    "core/css/css_property_equality.cc",
    "core/css/css_attr_type.cc",
    "core/css/css_cyclic_variable_value.cc",
    "core/css/css_invalid_variable_value.cc",
    "core/css/page_rule_collector.cc",
    "core/css/parser/css_if_parser.cc",
    "core/css/parser/css_property_parser.cc",
    "core/css/parser/at_rule_descriptor_parser.cc",
    "core/css/parser/conditional_parser.cc",
    "core/css/parser/media_query_parser.cc",
    "core/css/conditional_exp_node.cc",
    "core/css/if_condition.cc",
    "core/css/media_list.cc",
    "core/css/parser/css_variable_parser.cc",
    "core/css/properties/css_parsing_utils.cc",
    "core/css/properties/css_property_ref.cc",
    "core/css/properties/longhands/custom_property.cc",
    "core/css/properties/longhands/longhands_custom.cc",
    "core/css/properties/longhands/variable.cc",
    "core/css/resolver/cascade_expansion.cc",
    "core/css/resolver/cascade_map.cc",
    "core/css/resolver/cascade_resolver.cc",
    "core/css/resolver/match_result.cc",
    "core/css/resolver/matched_properties_cache.cc",
    "core/css/resolver/match_request.cc",
    "core/css/resolver/style_builder.cc",
    "core/css/resolver/style_cascade.cc",
    "core/css/resolver/style_resolver_state.cc",
    "core/css/counters_attachment_context.cc",
    "core/css/post_style_update_scope.cc",
    "core/css/resolver/selector_filter_parent_scope.cc",
    "core/animation/element_animations.cc",
    "core/animation/animation_effect.cc",
    "core/animation/css/css_animation_update.cc",
    "core/animation/css/css_keyframe_effect_model.cc",
    "core/animation/css/css_timeline_map.cc",
    "core/animation/css_default_interpolation_type.cc",
    "core/animation/animation_input_helpers.cc",
    "core/animation/css_color_interpolation_type.cc",
    "core/animation/css_interpolation_environment.cc",
    "core/animation/color_property_functions.cc",
    "core/animation/deferred_timeline.cc",
    "core/animation/effect_model.cc",
    "core/animation/effect_stack.cc",
    "core/animation/inert_effect.cc",
    "core/animation/interpolable_style_color.cc",
    "core/animation/interpolable_color.cc",
    "core/animation/interpolable_length.cc",
    "core/animation/interpolable_transform_list.cc",
    "core/animation/interpolable_value.cc",
    "core/animation/interpolation_effect.cc",
    "core/animation/invalidatable_interpolation.cc",
    "core/animation/keyframe.cc",
    "core/animation/keyframe_effect_model.cc",
    "core/animation/sampled_effect.cc",
    "core/animation/string_keyframe.cc",
    "core/animation/timing_calculations.cc",
    "core/animation/transition_interpolation.cc",
    "core/animation/transition_keyframe.cc",
    "core/animation/underlying_value_owner.cc",
    "core/animation/animation_timeline.cc",
    "core/animation/scroll_snapshot_timeline.cc",
    "core/animation/scroll_timeline.cc",
    "core/animation/view_timeline.cc",
    "core/dom/events/event.cc",
    "core/events/animation_event.cc",
    "core/events/transition_event.cc",
    "core/css/css_keyframe_shorthand_value.cc",
    "core/style/computed_style.cc",
    "core/style/basic_shapes.cc",
    "core/style/border_edge.cc",
    "core/style/shadow_list.cc",
    "core/style/shadow_data.cc",
    "core/style/style_ray.cc",
    "core/style/style_shape.cc",
    "core/style/style_base_data.cc",
    "core/style/position_area.cc",
    "core/svg/svg_path_byte_stream_builder.cc",
    "core/svg/svg_path_byte_stream_source.cc",
    "core/svg/svg_path_parser.cc",
    "core/svg/svg_path_string_builder.cc",
    "core/svg/svg_path_string_source.cc",
    "core/svg/svg_path_utilities.cc",
    "core/standalone_renderer_probe.cc",
)
LIVE_CORE_STANDALONE_SOURCES = (
    "../../standalone_renderer/src/render_frame.cc",
    "../../standalone_renderer/src/retained_scene.cc",
    "../../standalone_renderer/src/live_core_initializer_stub.cc",
    "../../standalone_renderer/src/live_empty_clients_stub.cc",
    "../../standalone_renderer/src/associated_interface_provider_standalone.cc",
    "../../standalone_renderer/src/web_history_item_standalone.cc",
    "../../standalone_renderer/src/content_security_policy_standalone.cc",
    "../../standalone_renderer/src/file_chooser_standalone.cc",
    "../../standalone_renderer/src/inspector_trace_events_standalone.cc",
    "../../standalone_renderer/src/history_item_standalone.cc",
    "../../standalone_renderer/src/network_feature_standalone.cc",
    "../../standalone_renderer/src/generated_name_atoms_standalone.cc",
    "../../standalone_renderer/src/url_network_standalone.cc",
    "../../standalone_renderer/src/document_loader_standalone.cc",
    "../../standalone_renderer/src/live_boundary_value_standalone.cc",
    "../../standalone_renderer/src/live_link_boundary_stubs.cc",
    "../../standalone_renderer/src/live_trace_origin_compat.cc",
)
LIVE_SUPPORT_SOURCES = (
    "../../base/substring_set_matcher/matcher_string_pattern.cc",
    "../../base/substring_set_matcher/substring_set_matcher.cc",
    "../../components/viz/common/view_transition_element_resource_id.cc",
    "../../third_party/blink/common/permissions_policy/policy_value.cc",
    "../../third_party/blink/common/input/web_input_event.cc",
    "../../third_party/blink/common/input/web_mouse_event.cc",
    "../../third_party/blink/renderer/core/execution_context/agent_cluster_key.cc",
    "../../third_party/blink/renderer/core/dom/qualified_name.cc",
    "../../third_party/blink/renderer/core/html/html_head_element.cc",
    "../../third_party/blink/renderer/platform/exported/web_url.cc",
    "../../third_party/blink/renderer/platform/loader/fetch/resource_loader_options.cc",
    "../../third_party/blink/renderer/platform/loader/fetch/text_resource_decoder_options.cc",
    "../../third_party/blink/renderer/platform/loader/fetch/fetch_context.cc",
    "../../third_party/blink/renderer/platform/json/json_values.cc",
    "../../third_party/blink/renderer/platform/text/bidi_paragraph.cc",
    "../../third_party/blink/renderer/platform/text/character.cc",
    "../../third_party/blink/renderer/platform/text/character_break_iterator.cc",
    "../../third_party/blink/renderer/platform/text/text_break_iterator.cc",
    "../../third_party/blink/renderer/platform/text/text_break_iterator_icu.cc",
    "../../third_party/blink/renderer/platform/text/text_break_iterator_internal_icu.cc",
    "../../third_party/blink/renderer/platform/text/icu_error.cc",
    "../../third_party/blink/renderer/platform/graphics/graphics_context.cc",
    "../../third_party/blink/renderer/platform/graphics/graphics_context_state.cc",
    "../../third_party/blink/renderer/platform/graphics/box_reflection.cc",
    "../../third_party/blink/renderer/platform/graphics/platform_focus_ring.cc",
    "../../third_party/blink/renderer/platform/graphics/compositor_element_id.cc",
    "../../third_party/blink/renderer/platform/graphics/compositor_filter_operations.cc",
    "../../third_party/blink/renderer/platform/graphics/compositing/chunk_to_layer_mapper.cc",
    "../../third_party/blink/renderer/platform/graphics/compositing/paint_chunks_to_cc_layer.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/clip_paint_property_node.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/effect_paint_property_node.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/geometry_mapper_clip_cache.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/geometry_mapper.cc",
    "../../third_party/blink/renderer/platform/graphics/paint_invalidation_reason.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/scroll_paint_property_node.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/scrollbar_display_item.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_record_builder.cc",
    "../../third_party/blink/renderer/platform/graphics/touch_action_rect.cc",
    "../../third_party/blink/renderer/platform/graphics/styled_stroke_data.cc",
    "../../third_party/blink/renderer/core/style/filter_operation.cc",
    "../../third_party/blink/renderer/platform/fonts/font_variant_alternates.cc",
    "../../third_party/blink/renderer/platform/fonts/font_height.cc",
    "../../third_party/blink/renderer/platform/fonts/font_metrics.cc",
    "../../third_party/blink/renderer/platform/fonts/font_fallback_iterator.cc",
    "../../third_party/blink/renderer/platform/fonts/script_run_iterator.cc",
    "../../third_party/blink/renderer/platform/fonts/symbols_iterator.cc",
    "../../third_party/blink/renderer/platform/fonts/small_caps_iterator.cc",
    "../../third_party/blink/renderer/platform/fonts/unicode_range_set.cc",
    "../../third_party/blink/renderer/platform/fonts/utf16_text_iterator.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/harfbuzz_shaper.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/font_features.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/harfbuzz_face.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/case_mapping_harfbuzz_buffer_filler.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/glyph_data_range.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/han_kerning.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/harfbuzz_font_cache.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/shape_result_bloberizer.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/shape_result.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/shape_result_cursor.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/shape_result_spacing.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/shape_result_view.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/shaping_line_breaker.cc",
    "../../third_party/blink/renderer/platform/fonts/shaping/run_segmenter.cc",
    "../../third_party/blink/renderer/platform/fonts/orientation_iterator.cc",
    "../../third_party/blink/renderer/platform/fonts/opentype/open_type_caps_support.cc",
    "../../third_party/blink/renderer/platform/fonts/opentype/open_type_baseline_metrics.cc",
    "../../third_party/blink/renderer/platform/fonts/opentype/open_type_vertical_data.cc",
    "../../third_party/blink/renderer/platform/fonts/opentype/color_table_lookup.cc",
    "../../third_party/blink/renderer/platform/fonts/skia/skia_text_metrics.cc",
    "../../third_party/blink/renderer/platform/text/layout_locale.cc",
    "../../third_party/blink/renderer/platform/text/locale_to_script_mapping.cc",
    "../../third_party/blink/renderer/platform/text/justification_opportunity.cc",
    "../../third_party/blink/renderer/platform/wtf/text/text_offset_map.cc",
    "../../third_party/blink/renderer/core/svg/svg_enumeration.cc",
    "../../third_party/blink/renderer/core/svg/svg_enumeration_map.cc",
    "../../third_party/blink/renderer/core/svg/svg_length_context.cc",
    "../../third_party/blink/renderer/core/svg/svg_length.cc",
    "../../third_party/blink/renderer/core/svg/svg_length_functions.cc",
    "../../cc/input/scroll_utils.cc",
    "../../cc/input/scroll_snap_data.cc",
    "../../cc/input/snap_selection_strategy.cc",
    "../../generated/blink_live/gen/third_party/blink/renderer/core/trustedtypes/trusted_types_names.cc",
    "../../net/cookies/site_for_cookies.cc",
    "../../services/network/public/cpp/fetch_retry_options.cc",
    "../../third_party/blink/renderer/platform/weborigin/sandboxed_opaque_security_origin_creator.cc",
    "../../third_party/blink/renderer/platform/weborigin/security_origin.cc",
    "../../third_party/blink/renderer/platform/transforms/transform_operations.cc",
    "../../third_party/blink/renderer/platform/transforms/interpolated_transform_operation.cc",
    "../../ui/gfx/geometry/box_f.cc",
    "../../ui/gfx/geometry/axis_transform2d.cc",
    "../../ui/gfx/geometry/decomposed_transform.cc",
    "../../ui/gfx/geometry/matrix44.cc",
    "../../ui/gfx/geometry/point3_f.cc",
    "../../ui/gfx/geometry/transform.cc",
    "../../ui/gfx/geometry/transform_util.cc",
    "../../ui/gfx/geometry/vector2d_f.cc",
    "../../ui/gfx/geometry/vector3d_f.cc",
    "../../cc/input/hit_test_opaqueness.cc",
    "../../cc/layers/touch_action_region.cc",
    "../../cc/trees/sticky_position_constraint.cc",
    "../../base/check_op.cc",
    "../../base/strings/string_util.cc",
    "../../base/strings/string_util_constants.cc",
    "../../base/strings/string_number_conversions.cc",
    "../../base/strings/utf_string_conversion_utils.cc",
    "../../base/json/string_escape.cc",
    "../../third_party/abseil-cpp/absl/container/internal/raw_hash_set.cc",
    "../../third_party/abseil-cpp/absl/hash/internal/city.cc",
    "../../third_party/abseil-cpp/absl/hash/internal/hash.cc",
    "../../third_party/perfetto/src/tracing/debug_annotation.cc",
    "../../third_party/abseil-cpp/absl/base/internal/hardening.cc",
    "../../third_party/abseil-cpp/absl/base/internal/raw_logging.cc",
    "../../third_party/abseil-cpp/absl/numeric/int128.cc",
    "../../third_party/abseil-cpp/absl/strings/ascii.cc",
    "../../third_party/abseil-cpp/absl/strings/charconv.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/charconv_bigint.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/charconv_parse.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/memutil.cc",
    "../../third_party/abseil-cpp/absl/strings/match.cc",
    "../../third_party/abseil-cpp/absl/strings/numbers.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/utf8.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/str_format/arg.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/str_format/bind.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/str_format/extension.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/str_format/float_conversion.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/str_format/output.cc",
    "../../third_party/abseil-cpp/absl/strings/internal/str_format/parser.cc",
    "gen/third_party/blink/renderer/core/event_target_names.cc",
    "gen/third_party/blink/renderer/core/event_type_names.cc",
    "gen/third_party/blink/renderer/core/keywords.cc",
    "gen/third_party/blink/renderer/core/css/css_property_names.cc",
    "gen/third_party/blink/renderer/core/css/parser/at_rule_descriptors.cc",
    "../../third_party/blink/renderer/core/css/basic_shape_functions.cc",
    "../../third_party/blink/renderer/core/svg/svg_path_builder.cc",
    "../../third_party/blink/renderer/core/layout/geometry/box_strut.cc",
    "../../third_party/blink/renderer/core/layout/geometry/axis.cc",
    "../../third_party/blink/renderer/platform/geometry/contoured_rect.cc",
    "../../third_party/blink/renderer/platform/geometry/float_rounded_rect.cc",
    "../../third_party/blink/renderer/platform/geometry/path.cc",
    "../../third_party/blink/renderer/platform/geometry/path_builder.cc",
    "../../third_party/blink/renderer/platform/graphics/path_traversal_state.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/cull_rect.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/drawing_recorder.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/display_item.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/display_item_list.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/drawing_display_item.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/foreign_layer_display_item.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/geometry_mapper_transform_cache.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/hit_test_data.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/ignore_paint_timing_scope.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_artifact.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_chunk.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_chunker.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_controller.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_controller_debug_data.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_property_node.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/paint_under_invalidation_checker.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/property_tree_state.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/region_capture_data.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/tracked_element_data.cc",
    "../../third_party/blink/renderer/platform/graphics/paint/transform_paint_property_node.cc",
    "../../ui/gfx/geometry/insets_f.cc",
    "../../ui/gfx/geometry/point_f.cc",
    "../../ui/gfx/geometry/quad_f.cc",
    "../../ui/gfx/geometry/rect_conversions.cc",
    "../../ui/gfx/geometry/rect.cc",
    "../../ui/gfx/geometry/rect_f.cc",
    "../../ui/gfx/geometry/size_f.cc",
    "../../ui/gfx/geometry/triangle_f.cc",
    "../../ui/gfx/geometry/cubic_bezier.cc",
)

LIVE_SUPPORT_LIBS = (
    "obj/cc/base/cc_base.lib",
    "obj/cc/paint/cc_paint.lib",
    "obj/skia/skia.lib",
    "obj/skia/skia_switches.lib",
    "obj/skia/public/mojom/skia_shared_typemap_traits.lib",
    "obj/mojo/public/cpp/bindings/bindings_base.lib",
    "obj/mojo/public/cpp/base/mojo_base_lib.lib",
    "obj/mojo/public/cpp/base/mojo_base_shared_typemap_traits.lib",
    "obj/components/crash/core/common/crash_key_lib.lib",
    "obj/third_party/crashpad/crashpad/client/client.lib",
    "obj/third_party/crashpad/crashpad/util/util.lib",
    "obj/build/rust/cxx_cppdeps.lib",
    "obj/build/rust/allocator/allocator_impls.lib",
    "obj/build/rust/allocator/alloc_error_handler_impl.lib",
    "obj/skia/libbridge_rust_side_e866329c.rlib",
    "obj/skia/librust_bmp_ffi_e866329c.rlib",
    "obj/skia/librust_exif_ffi_e866329c.rlib",
    "obj/skia/librust_icc_ffi_e866329c.rlib",
    "obj/skia/librust_png_ffi_e866329c.rlib",
    "obj/skia/libskia_rust_common.rlib",
    "obj/third_party/expat/expat.lib",
    "obj/third_party/freetype/freetype.lib",
    "obj/third_party/libjpeg_turbo/libjpeg.lib",
    "obj/third_party/libjpeg_turbo/libjpeg12.lib",
    "obj/third_party/libjpeg_turbo/libjpeg16.lib",
    "obj/third_party/libjpeg_turbo/simd.lib",
    "obj/third_party/libjpeg_turbo/simd_asm.lib",
    "obj/third_party/zlib/zlib.lib",
    "obj/ui/gfx/geometry/geometry_skia.lib",
    "obj/ui/gfx/geometry/geometry.lib",
    "obj/third_party/icu/icui18n.lib",
    "obj/third_party/icu/icuuc.lib",
    "obj/third_party/harfbuzz/harfbuzz.lib",
    "Advapi32.lib",
    "Ntdll.lib",
    "Userenv.lib",
    "Ws2_32.lib",
    "User32.lib",
)

LIVE_SUPPORT_OBJECT_GLOBS = (
    "obj/skia/skia_core_and_effects/*.obj",
    "obj/skia/bridge_rust_side_cxx_generated/*.obj",
    "obj/skia/skcms_TransformBaseline_and_public/*.obj",
    "obj/skia/skcms_TransformHsw/*.obj",
    "obj/skia/skcms_TransformSkx/*.obj",
    "obj/skia/*_ffi_cpp/*.obj",
    "obj/skia/*_ffi_cxx_generated/*.obj",
    "obj/third_party/zlib/zlib_adler32_simd/*.obj",
    "obj/third_party/zlib/zlib_crc32_simd/*.obj",
    "obj/third_party/zlib/zlib_data_chunk_simd/*.obj",
    "obj/third_party/rust/**/*.rlib",
    "obj/build/rust/allocator/*.rlib",
    "local_rustc_sysroot/lib/rustlib/x86_64-pc-windows-msvc/lib/*.rlib",
)

LIVE_SUPPORT_OBJECTS = (
    "obj/buildtools/third_party/libc++/libc++/condition_variable.obj",
    "obj/buildtools/third_party/libc++/libc++/thread.obj",
)

EXTRA_INCLUDES = (
    "-I../../standalone_renderer/stubs",
    "-Igen/third_party/perfetto",
    "-I../../third_party/perfetto/include",
    "-I../../third_party/boringssl/src/include",
    "-I../../third_party/crashpad/crashpad",
    "-I../../third_party/libxml/win32/include",
    "-I../../third_party/libxml/src/include",
    "-I../../third_party/harfbuzz/src/src",
    "-I../../third_party/perfetto/include/perfetto/base/build_configs/bazel",
)

EXTRA_ARGS = (
    "-DINSIDE_BLINK=1",
    "-DHTML_CSS_RENDERER_STANDALONE=1",
    "-DSTANDALONE_RENDERER_GN_PROBE=1",
    "/Gy",
    "/FI../../standalone_renderer/stubs/third_party/blink/public/mojom/use_counter/metrics/web_feature.mojom-shared.h",
    "/FI../../standalone_renderer/stubs/standalone_live_blink_namespace_forwards.h",
)


def compile_template_command(commands: list[str]) -> str:
    normalized_template = TEMPLATE_SOURCE.replace("\\", "/")
    for command in commands:
        if "clang-cl.exe" in command and normalized_template in command.replace(
            "\\", "/"
        ):
            return command
    raise RuntimeError(f"missing template compile command for {TEMPLATE_SOURCE}")


def read_commands(path: pathlib.Path) -> list[str]:
    data = path.read_bytes()
    if data.startswith(b"\xff\xfe") or data.startswith(b"\xfe\xff"):
        return data.decode("utf-16", errors="replace").splitlines()
    return data.decode("utf-8-sig", errors="replace").splitlines()


def live_compile_args(template_command: str, source: str, obj: str) -> list[str]:
    args = [
        arg
        for arg in relink.split_command_line(template_command)
        if not arg.lower().startswith("/showincludes")
    ]
    args = [
        arg
        for arg in args
        if arg != "-I../../standalone_renderer/stubs"
        and arg != "/I../../standalone_renderer/stubs"
    ]
    args = [
        arg.replace(TEMPLATE_SOURCE, source).replace(TEMPLATE_OBJECT, obj)
        for arg in args
    ]

    for include in reversed(EXTRA_INCLUDES):
        if include not in args:
            try:
                root_index = args.index("-I../..")
            except ValueError:
                root_index = len(args) - 1
            args.insert(root_index + 1, include)

    for extra in EXTRA_ARGS:
        if extra not in args:
            args.append(extra)
    if source.endswith("standalone_renderer/src/live_trace_origin_compat.cc"):
        args = [
            arg
            for arg in args
            if arg not in ("-DSTANDALONE_RENDERER_GN_PROBE=1",
                           "/DSTANDALONE_RENDERER_GN_PROBE=1",
                           "-I../../standalone_renderer/stubs",
                           "/I../../standalone_renderer/stubs",
                           "/FI../../standalone_renderer/stubs/third_party/blink/public/mojom/use_counter/metrics/web_feature.mojom-shared.h",
                           "/FI../../standalone_renderer/stubs/standalone_live_blink_namespace_forwards.h")
        ]
    if source.endswith("core/dom/element.cc") or source.endswith(
        "core/paint/paint_layer.cc"
    ):
        html_element_stubs = (
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/canvas/html_canvas_element.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/media/html_video_element.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/svg/svg_a_element.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/svg/svg_stop_element.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/svg/svg_use_element.h",
        )
        for stub in html_element_stubs:
            if stub not in args:
                args.append(stub)
    if source.endswith("core/dom/text.cc"):
        svg_foreign_object_stub = (
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/svg/svg_foreign_object_element.h"
        )
        if svg_foreign_object_stub not in args:
            args.append(svg_foreign_object_stub)
    if (source.endswith("core/dom/events/event_target.cc") or
            source.endswith("core/dom/events/event.cc")):
        worker_scope_stubs = (
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/workers/worker_or_worklet_global_scope.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/workers/worker_global_scope.h",
        )
        for worker_global_scope_stub in worker_scope_stubs:
            if worker_global_scope_stub not in args:
                args.append(worker_global_scope_stub)
    if (source.endswith("core/css/style_engine.cc") or
            source.endswith("core/css/resolver/style_resolver.cc")):
        text_track_stub = (
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/track/text_track.h"
        )
        if text_track_stub not in args:
            args.append(text_track_stub)
    if source.endswith("core/css/resolver/style_resolver.cc"):
        style_resolver_forced_headers = (
            "/FI../../third_party/blink/renderer/core/page/chrome_client.h",
            "/FI../../third_party/blink/renderer/core/mathml/mathml_fraction_element.h",
            "/FI../../third_party/blink/renderer/core/mathml/mathml_operator_element.h",
            "/FI../../third_party/blink/renderer/core/mathml/mathml_padded_element.h",
            "/FI../../third_party/blink/renderer/core/mathml/mathml_space_element.h",
        )
        for forced_header in style_resolver_forced_headers:
            if forced_header not in args:
                args.append(forced_header)
    if source.endswith("core/css/resolver/element_resolve_context.cc"):
        pseudo_element_header = (
            "/FI../../third_party/blink/renderer/core/dom/pseudo_element.h"
        )
        if pseudo_element_header not in args:
            args.append(pseudo_element_header)
    if source.endswith("core/html/parser/html_document_parser.cc"):
        parser_forced_headers = (
            "/FI../../third_party/blink/renderer/core/frame/csp/"
            "content_security_policy.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "bindings/core/v8/script_streamer.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/parser/background_html_scanner.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/parser/html_preload_scanner.h",
        )
        for forced_header in parser_forced_headers:
            if forced_header not in args:
                args.append(forced_header)
    if source.endswith("standalone_renderer/src/live_link_boundary_stubs.cc"):
        parser_boundary_forced_headers = (
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/parser/background_html_scanner.h",
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "core/html/parser/html_preload_scanner.h",
        )
        for forced_header in parser_boundary_forced_headers:
            if forced_header not in args:
                args.append(forced_header)
    if source.endswith("core/dom/scriptable_document_parser.cc"):
        script_streamer_stub = (
            "/FI../../standalone_renderer/stubs/third_party/blink/renderer/"
            "bindings/core/v8/script_streamer.h"
        )
        if script_streamer_stub not in args:
            args.append(script_streamer_stub)
    return args


def compile_source(
    out_dir: pathlib.Path,
    template_command: str,
    source: str,
    obj: str,
    timeout: int,
) -> int:
    args = live_compile_args(template_command, source, obj)
    executable = relink.resolve_executable(out_dir, args[0])
    obj_path = out_dir / obj
    source_path = out_dir / source
    if obj_path.exists() and source_path.exists():
        dependency_paths = [
            source_path,
        ]
        newest_input = max(
            path.stat().st_mtime for path in dependency_paths if path.exists()
        )
        if obj_path.stat().st_mtime >= newest_input:
            print(f"{source} SKIP")
            return 0
    (out_dir / pathlib.Path(obj).parent).mkdir(parents=True, exist_ok=True)
    rsp_path = out_dir / ("direct.live_frame." + pathlib.Path(obj).stem + ".rsp")
    rsp_path.write_text(subprocess.list2cmdline(args[1:]), encoding="utf-8")
    result = subprocess.run(
        [str(executable), "@" + str(rsp_path.resolve())],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    print(f"{source} EXIT {result.returncode}")
    if result.stdout:
        print(result.stdout[-50000:])
    return result.returncode


def compile_runtime_adapter(
    out_dir: pathlib.Path,
    commands: list[str],
    timeout: int,
) -> int:
    normalized_source = RUNTIME_ADAPTER_SOURCE.replace("\\", "/")
    matches = [
        command
        for command in commands
        if "clang-cl.exe" in command and normalized_source in command.replace("\\", "/")
    ]
    if not matches:
        print(f"missing compile command for {RUNTIME_ADAPTER_SOURCE}")
        return 2
    args = [
        arg
        for arg in relink.split_command_line(matches[0])
        if not arg.lower().startswith("/showincludes")
    ]
    live_define = "/DHTML_CSS_RENDERER_HAS_LIVE_BLINK_RUNTIME=1"
    if live_define not in args:
        args.append(live_define)
    tree_define = "/DHTML_CSS_RENDERER_HAS_BLINK_TREE_BUILDER_BRIDGE=1"
    if tree_define not in args:
        args.append(tree_define)
    obj = (
        "obj/standalone_renderer/blink_live_frame_bridge_probe/"
        "blink_runtime_adapter.live.obj"
    )
    args = [
        arg if not arg.startswith("/Fo") else "/Fo" + obj
        for arg in args
    ]
    executable = relink.resolve_executable(out_dir, args[0])
    (out_dir / pathlib.Path(obj).parent).mkdir(parents=True, exist_ok=True)
    rsp_path = out_dir / "direct.live_frame.blink_runtime_adapter.rsp"
    rsp_path.write_text(subprocess.list2cmdline(args[1:]), encoding="utf-8")
    result = subprocess.run(
        [str(executable), "@" + str(rsp_path.resolve())],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    print(f"{RUNTIME_ADAPTER_SOURCE} live-adapter EXIT {result.returncode}")
    if result.stdout:
        print(result.stdout[-50000:])
    return result.returncode


def compile_smoke_main(
    out_dir: pathlib.Path,
    template_command: str,
    timeout: int,
) -> int:
    return compile_source(out_dir, template_command, SMOKE_SOURCE, SMOKE_OBJECT,
                          timeout)


def compile_live_core_island(
    out_dir: pathlib.Path,
    template_command: str,
    timeout: int,
) -> int:
    for source_path in LIVE_CORE_STANDALONE_SOURCES:
        obj_name = pathlib.Path(source_path).name.replace(".cc", ".obj")
        obj_path = (
            "obj/standalone_renderer/blink_live_frame_bridge_probe/"
            f"{obj_name}"
        )
        exit_code = compile_source(out_dir, template_command, source_path,
                                   obj_path, timeout)
        if exit_code:
            return exit_code
    for source_path in LIVE_SUPPORT_SOURCES:
        obj_name = (
            source_path.removeprefix("../../")
            .replace("/", "_")
            .replace("\\", "_")
            .replace(".cc", ".obj")
        )
        obj_path = (
            "obj/standalone_renderer/blink_live_frame_bridge_probe/"
            f"{obj_name}"
        )
        exit_code = compile_source(out_dir, template_command, source_path,
                                   obj_path, timeout)
        if exit_code:
            return exit_code
    for source in LIVE_CORE_ISLAND_SOURCES:
        source_path = "../../third_party/blink/renderer/" + source
        obj_name = source.replace("/", "_").replace(".cc", ".obj")
        obj_path = (
            "obj/standalone_renderer/blink_live_frame_bridge_probe/"
            f"{obj_name}"
        )
        exit_code = compile_source(out_dir, template_command, source_path,
                                   obj_path, timeout)
        if exit_code:
            return exit_code
    return 0


def collect_existing_support_inputs(
    out_dir: pathlib.Path,
    command_sets: list[list[str]],
) -> list[str]:
    inputs: list[str] = []
    skip_fragments = (
        "render_blink_cli.obj",
        "blink_tree_builder_link_probe.obj",
        "blink_dom_link_probe.obj",
        "live_frame_bridge_link_probe.obj",
        "standalone_core_probe/standalone_renderer_probe.obj",
        "standalone_core_probe/html_tokenizer.obj",
        "standalone_core_probe/css_parser_token.obj",
        "standalone_core_probe/css_parser_token_stream.obj",
        "standalone_core_probe/css_tokenizer.obj",
        "standalone_core_probe/css_tokenizer_input_stream.obj",
        "standalone_core_tree_builder_probe/html_tree_builder.obj",
        "standalone_core_tree_builder_probe/core_css_properties_css_parsing_utils.obj",
        "standalone_core_tree_builder_probe/core_css_properties_longhands_longhands_custom.obj",
        "standalone_core_tree_builder_probe/core_css_css_identifier_value.obj",
        "standalone_core_tree_builder_probe/core_css_resolver_font_builder.obj",
        "standalone_tree_builder_dom_shim.obj",
        "core_standalone_layout_link_stubs.obj",
        "standalone_renderer_probe_base_shim.obj",
        "standalone_renderer_probe_css_parser_context_shim.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_input_node.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_result.obj",
        "standalone_core_tree_builder_probe/core_layout_constraint_space.obj",
        "standalone_core_tree_builder_probe/core_layout_box_fragment_builder.obj",
        "standalone_core_tree_builder_probe/core_layout_fragment_builder.obj",
        "standalone_core_tree_builder_probe/core_layout_physical_box_fragment.obj",
        "standalone_core_tree_builder_probe/core_layout_block_node.obj",
        "standalone_core_tree_builder_probe/core_layout_block_layout_algorithm.obj",
        "standalone_core_tree_builder_probe/core_layout_block_layout_algorithm_utils.obj",
        "standalone_core_tree_builder_probe/core_layout_block_child_iterator.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_box.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_block.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_block_flow.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_inline.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_replaced.obj",
        "standalone_core_tree_builder_probe/core_layout_natural_sizing_info.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_text.obj",
        "standalone_core_tree_builder_probe/core_layout_floats_utils.obj",
        "standalone_core_tree_builder_probe/core_layout_length_utils.obj",
        "standalone_core_tree_builder_probe/core_layout_fragmentation_utils.obj",
        "standalone_core_tree_builder_probe/core_layout_relative_utils.obj",
        "standalone_core_tree_builder_probe/core_layout_ink_overflow.obj",
        "standalone_core_tree_builder_probe/core_layout_line_clamp_data.obj",
        "standalone_core_tree_builder_probe/core_layout_shapes_shape_outside_info.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_fragment_items.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_fragment_item.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_fragment_items_builder.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_box_state.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_child_layout_context.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_cursor.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_caret_position.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_layout_algorithm.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_node.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_inline_node_data.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_line_box_fragment_builder.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_line_breaker.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_line_info.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_line_truncator.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_line_widths.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_paragraph_line_breaker.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_score_line_breaker.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_justification_utils.obj",
        "standalone_core_tree_builder_probe/core_layout_inline_logical_line_container.obj",
        "standalone_core_tree_builder_probe/core_layout_flex_layout_flexible_box.obj",
        "standalone_core_tree_builder_probe/core_layout_grid_layout_grid.obj",
        "standalone_core_tree_builder_probe/core_layout_grid_lanes_layout_grid_lanes.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_image.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_object.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_object_child_list.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_ruby_as_block.obj",
        "standalone_core_tree_builder_probe/core_layout_layout_text_combine.obj",
        "standalone_core_tree_builder_probe/core_layout_list_layout_inline_list_item.obj",
        "standalone_core_tree_builder_probe/core_layout_list_layout_inside_list_marker.obj",
        "standalone_core_tree_builder_probe/core_layout_list_layout_list_item.obj",
        "standalone_core_tree_builder_probe/core_layout_list_layout_outside_list_marker.obj",
        "standalone_core_tree_builder_probe/core_layout_list_layout_outside_list_marker.obj",
        "standalone_core_tree_builder_probe/core_layout_list_unpositioned_list_marker.obj",
        "standalone_core_tree_builder_probe/core_layout_mathml_layout_mathml_block.obj",
        "standalone_core_tree_builder_probe/core_layout_table_layout_table.obj",
        "standalone_core_tree_builder_probe/core_layout_table_layout_table_caption.obj",
        "standalone_core_tree_builder_probe/core_layout_table_layout_table_cell.obj",
        "standalone_core_tree_builder_probe/core_layout_table_layout_table_column.obj",
        "standalone_core_tree_builder_probe/core_layout_table_layout_table_row.obj",
        "standalone_core_tree_builder_probe/core_layout_table_layout_table_section.obj",
    )
    for commands in command_sets:
        for item in relink.collect_link_inputs(out_dir, commands):
            normalized = item.replace("\\", "/")
            if any(skip in normalized for skip in skip_fragments):
                continue
            if item not in inputs:
                inputs.append(item)
    for source, obj in LIVE_BRIDGE_SOURCES:
        if obj not in inputs and (out_dir / obj).exists():
            inputs.append(obj)
    for source in LIVE_CORE_ISLAND_SOURCES:
        obj_name = source.replace("/", "_").replace(".cc", ".obj")
        obj = (
            "obj/standalone_renderer/blink_live_frame_bridge_probe/"
            f"{obj_name}"
        )
        if obj not in inputs and (out_dir / obj).exists():
            inputs.append(obj)
    for source in LIVE_CORE_STANDALONE_SOURCES:
        obj_name = pathlib.Path(source).name.replace(".cc", ".obj")
        obj = (
            "obj/standalone_renderer/blink_live_frame_bridge_probe/"
            f"{obj_name}"
        )
        if obj not in inputs and (out_dir / obj).exists():
            inputs.append(obj)
    for source in LIVE_SUPPORT_SOURCES:
        obj_name = (
            source.removeprefix("../../")
            .replace("/", "_")
            .replace("\\", "_")
            .replace(".cc", ".obj")
        )
        obj = (
            "obj/standalone_renderer/blink_live_frame_bridge_probe/"
            f"{obj_name}"
        )
        if obj not in inputs and (out_dir / obj).exists():
            inputs.append(obj)
    for lib in LIVE_SUPPORT_LIBS:
        if lib.lower().endswith(".lib") and "/" not in lib and "\\" not in lib:
            if lib not in inputs:
                inputs.append(lib)
        elif lib not in inputs and (out_dir / lib).exists():
            inputs.append(lib)
    for obj in LIVE_SUPPORT_OBJECTS:
        if obj not in inputs and (out_dir / obj).exists():
            inputs.append(obj)
    for pattern in LIVE_SUPPORT_OBJECT_GLOBS:
        for path in sorted(out_dir.glob(pattern)):
            obj = path.relative_to(out_dir).as_posix()
            if obj not in inputs:
                inputs.append(obj)
    if SMOKE_OBJECT not in inputs and (out_dir / SMOKE_OBJECT).exists():
        inputs.insert(0, SMOKE_OBJECT)
    return inputs


def link_smoke_probe(
    out_dir: pathlib.Path,
    cli_commands: list[str],
    tree_commands: list[str],
    timeout: int,
    allow_unresolved: bool,
) -> int:
    link_commands = [
        command
        for command in cli_commands
        if "lld-link.exe" in command and "html_css_renderer_blink_cli.exe" in command
    ]
    if not link_commands:
        print("missing template link command for html_css_renderer_blink_cli.exe")
        return 2
    args = relink.split_command_line(link_commands[-1])
    executable = relink.resolve_executable(out_dir, args[0])
    link_args: list[str] = []
    for arg in args[1:]:
      lower = arg.lower()
      if arg.startswith("@"):
          continue
      if lower.startswith("/out:"):
          link_args.append("/OUT:live_frame_bridge_link_probe.exe")
          continue
      if "html_css_renderer_blink_cli" in arg:
          continue
      link_args.append(arg)
    if allow_unresolved and "/force:unresolved" not in link_args:
        link_args.append("/force:unresolved")
    if "/OPT:REF" not in link_args and "/opt:ref" not in [arg.lower() for arg in link_args]:
        link_args.append("/OPT:REF")
    inputs = collect_existing_support_inputs(out_dir, [cli_commands, tree_commands])
    rsp_path = out_dir / "live_frame_bridge_link_probe.rsp"
    rsp_path.write_text(subprocess.list2cmdline(inputs), encoding="utf-8")
    result = subprocess.run(
        [str(executable)] + link_args + ["@" + str(rsp_path.resolve()),
                                         "/errorlimit:0"],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    if result.stdout:
        print(result.stdout[-50000:])
    print(f"LIVE LINK EXIT {result.returncode}")
    return result.returncode


def run_smoke_probe(out_dir: pathlib.Path, timeout: int) -> int:
    result = subprocess.run(
        [str((out_dir / "live_frame_bridge_link_probe.exe").resolve())],
        cwd=out_dir,
        shell=False,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        errors="replace",
        timeout=timeout,
    )
    if result.stdout:
        print(result.stdout)
    print(f"LIVE RUN EXIT {result.returncode}")
    return result.returncode


def main(argv: list[str]) -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--out-dir", default="generated/blink_live")
    parser.add_argument("--commands", default=TEMPLATE_COMMAND_DUMP)
    parser.add_argument("--runtime-adapter-commands",
                        default=RUNTIME_ADAPTER_COMMAND_DUMP)
    parser.add_argument("--also-compile-runtime-adapter",
                        action="store_true")
    parser.add_argument("--also-link-smoke", action="store_true")
    parser.add_argument("--also-compile-core-island", action="store_true")
    parser.add_argument("--allow-unresolved", action="store_true")
    parser.add_argument("--compile-timeout", type=int, default=120)
    parser.add_argument("--link-timeout", type=int, default=120)
    parser.add_argument("--run-timeout", type=int, default=10)
    parser.add_argument("--no-run", action="store_true")
    args = parser.parse_args(argv)

    out_dir = pathlib.Path(args.out_dir)
    commands_path = out_dir / args.commands
    commands = read_commands(commands_path)
    template_command = compile_template_command(commands)

    for source, obj in LIVE_BRIDGE_SOURCES:
        exit_code = compile_source(
            out_dir, template_command, source, obj, args.compile_timeout
        )
        if exit_code:
            return exit_code
    if args.also_link_smoke:
        exit_code = compile_smoke_main(out_dir, template_command,
                                       args.compile_timeout)
        if exit_code:
            return exit_code
    if args.also_compile_core_island:
        exit_code = compile_live_core_island(out_dir, template_command,
                                             args.compile_timeout)
        if exit_code:
            return exit_code
    if args.also_compile_runtime_adapter:
        runtime_commands = read_commands(out_dir / args.runtime_adapter_commands)
        exit_code = compile_runtime_adapter(out_dir, runtime_commands,
                                            args.compile_timeout)
        if exit_code:
            return exit_code
    if args.also_link_smoke:
        runtime_commands = read_commands(out_dir / args.runtime_adapter_commands)
        tree_commands = read_commands(
            out_dir / "blink_tree_builder_link_probe.commands.txt")
        exit_code = link_smoke_probe(out_dir, runtime_commands, tree_commands,
                                     args.link_timeout, args.allow_unresolved)
        if exit_code:
            return exit_code
        if not args.no_run:
            return run_smoke_probe(out_dir, args.run_timeout)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
