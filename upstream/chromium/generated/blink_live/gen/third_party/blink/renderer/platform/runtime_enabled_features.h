// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/runtime_enabled_features.h.tmpl
// and input files:
//   ../../third_party/blink/renderer/platform/runtime_enabled_features.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_ENABLED_FEATURES_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_ENABLED_FEATURES_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/protected_memory.h"
#include "third_party/blink/renderer/platform/platform_export.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"

#define ASSERT_ORIGIN_TRIAL(feature) \
  static_assert(std::is_same<decltype(::blink::RuntimeEnabledFeatures::     \
                                          feature##EnabledByRuntimeFlag()), \
                             bool>(),                                       \
                #feature " must be part of an origin trial");

namespace blink {

class FeatureContext;

// A class that stores static enablers for all experimental features.

class PLATFORM_EXPORT RuntimeEnabledFeaturesBase {
  STATIC_ONLY(RuntimeEnabledFeaturesBase);
 public:
  class PLATFORM_EXPORT Backup {
   public:
    explicit Backup();
    void Restore();

   private:
    bool is_about_blank_page_respects_dark_mode_on_user_action_enabled_;
    bool is_accelerated_2d_canvas_enabled_;
    bool is_accelerated_small_canvases_enabled_;
    bool is_accessibility_aria_virtual_content_enabled_;
    bool is_accessibility_custom_element_role_none_enabled_;
    bool is_accessibility_expose_display_none_enabled_;
    bool is_accessibility_implicit_actions_enabled_;
    bool is_accessibility_min_role_tabbable_enabled_;
    bool is_accessibility_os_level_bold_text_enabled_;
    bool is_accessibility_prohibited_names_enabled_;
    bool is_accessibility_serialization_size_metrics_enabled_;
    bool is_accessibility_use_ax_position_for_document_markers_enabled_;
    bool is_access_key_label_enabled_;
    bool is_address_space_enabled_;
    bool is_ad_interest_group_api_enabled_;
    bool is_adjust_dom_offset_to_layout_offset_for_secure_text_enabled_;
    bool is_adjust_end_of_next_paragraph_if_moved_paragraph_is_updated_enabled_;
    bool is_ad_tagging_enabled_;
    bool is_ai_classifier_api_enabled_;
    bool is_ai_page_content_anchored_offscreen_non_actionability_enabled_;
    bool is_ai_page_content_build_on_load_for_testing_enabled_;
    bool is_ai_page_content_check_geometry_enabled_;
    bool is_ai_page_content_convert_node_text_to_utf_8_enabled_;
    bool is_ai_page_content_element_css_redaction_enabled_;
    bool is_ai_page_content_include_svg_subtree_enabled_;
    bool is_ai_page_content_outer_box_map_to_ancestor_space_enabled_;
    bool is_ai_page_content_paid_content_annotation_enabled_;
    bool is_ai_page_content_visual_viewport_clamp_enabled_;
    bool is_ai_prompt_api_enabled_;
    bool is_ai_prompt_api_for_extension_enabled_;
    bool is_ai_prompt_api_for_workers_enabled_;
    bool is_ai_prompt_api_legacy_identifiers_enabled_;
    bool is_ai_prompt_api_legacy_params_enabled_;
    bool is_ai_prompt_api_multimodal_input_enabled_;
    bool is_ai_prompt_api_params_enabled_;
    bool is_ai_prompt_api_structured_output_enabled_;
    bool is_ai_prompt_api_tool_use_enabled_;
    bool is_ai_proofreading_api_enabled_;
    bool is_ai_rewriter_api_enabled_;
    bool is_ai_rewriter_api_for_workers_enabled_;
    bool is_ai_summarization_api_enabled_;
    bool is_ai_summarization_api_for_workers_enabled_;
    bool is_ai_summarization_performance_preference_enabled_;
    bool is_ai_writer_api_enabled_;
    bool is_ai_writer_api_for_workers_enabled_;
    bool is_align_zoom_to_center_enabled_;
    bool is_all_images_painted_sent_to_element_timing_enabled_;
    bool is_allow_content_initiated_data_url_navigations_enabled_;
    bool is_allow_preloading_with_csp_meta_tag_enabled_;
    bool is_allow_same_site_none_cookies_in_sandbox_enabled_;
    bool is_allow_skipping_editing_boundary_to_merge_end_enabled_;
    bool is_allow_svg_use_to_reference_external_document_root_enabled_;
    bool is_allow_synthetic_timing_for_canvas_capture_enabled_;
    bool is_allow_ur_ns_in_iframes_enabled_;
    bool is_ancestor_origins_stored_on_document_enabled_;
    bool is_ancestor_revealing_new_spec_enabled_;
    bool is_anchor_focus_ring_fix_enabled_;
    bool is_anchor_position_adjustment_without_overflow_enabled_;
    bool is_android_downloadable_fonts_matching_enabled_;
    bool is_animation_progress_api_enabled_;
    bool is_animation_trigger_enabled_;
    bool is_animation_worklet_enabled_;
    bool is_anonymous_iframe_enabled_;
    bool is_aom_aria_relationship_properties_enabled_;
    bool is_aom_aria_relationship_properties_aria_owns_enabled_;
    bool is_appearance_base_enabled_;
    bool is_approximate_geolocation_permission_enabled_;
    bool is_approximate_geolocation_permission_api_enabled_;
    bool is_approximate_geolocation_web_visible_api_enabled_;
    bool is_app_title_enabled_;
    bool is_aria_actions_enabled_;
    bool is_aria_notify_enabled_;
    bool is_aria_notify_v_2_enabled_;
    bool is_aria_row_col_index_text_enabled_;
    bool is_async_set_cookie_enabled_;
    bool is_attribution_reporting_enabled_;
    bool is_audio_context_async_state_transitions_enabled_;
    bool is_audio_context_playback_stats_enabled_;
    bool is_audio_context_playout_stats_enabled_;
    bool is_audio_context_set_sink_id_enabled_;
    bool is_audio_output_devices_enabled_;
    bool is_audio_video_tracks_enabled_;
    bool is_authenticator_passwords_only_immediate_requests_enabled_;
    bool is_author_specified_layout_scroll_snap_behavior_enabled_;
    bool is_auto_dark_mode_enabled_;
    bool is_autofill_enabled_;
    bool is_autofill_event_enabled_;
    bool is_automation_controlled_enabled_;
    bool is_auto_picture_in_picture_video_heuristics_enabled_;
    bool is_avoid_forced_layout_on_invisible_document_close_enabled_;
    bool is_avoid_merging_styled_span_with_siblings_enabled_;
    bool is_avoid_normalizing_visible_positions_when_start_equals_end_enabled_;
    bool is_backface_visibility_interop_enabled_;
    bool is_back_forward_cache_enabled_;
    bool is_back_forward_cache_experiment_http_header_enabled_;
    bool is_back_forward_cache_not_restored_reasons_enabled_;
    bool is_back_forward_cache_restoration_performance_entry_enabled_;
    bool is_back_forward_cache_update_not_restored_reasons_name_enabled_;
    bool is_background_clip_text_decoration_enabled_;
    bool is_background_fetch_enabled_;
    bool is_background_page_freeze_opt_out_enabled_;
    bool is_barcode_detector_enabled_;
    bool is_base_appearance_inline_sizing_enabled_;
    bool is_bidi_caret_affinity_enabled_;
    bool is_blink_extension_chrome_os_enabled_;
    bool is_blink_extension_chrome_os_isolated_web_app_set_shape_enabled_;
    bool is_blink_extension_chrome_os_kiosk_enabled_;
    bool is_blink_extension_web_view_enabled_;
    bool is_blink_extension_web_view_media_integrity_enabled_;
    bool is_blink_geometry_mapper_viewport_fast_path_enabled_;
    bool is_blink_lifecycle_script_forbidden_enabled_;
    bool is_blink_runtime_call_stats_enabled_;
    bool is_blob_bytes_enabled_;
    bool is_blocking_focus_without_user_activation_enabled_;
    bool is_block_select_popup_unfocused_window_enabled_;
    bool is_boundary_event_dispatch_tracks_node_removal_enabled_;
    bool is_browser_initiated_automatic_picture_in_picture_enabled_;
    bool is_browser_verified_user_activation_keyboard_enabled_;
    bool is_browser_verified_user_activation_mouse_enabled_;
    bool is_buffered_bytes_consumer_limit_size_enabled_;
    bool is_bypass_pepc_security_for_testing_enabled_;
    bool is_cache_control_rfc_7234_parsing_enabled_;
    bool is_cache_control_rfc_7234_parsing_metrics_enabled_;
    bool is_cache_storage_code_cache_hint_enabled_;
    bool is_cache_style_adjuster_enabled_;
    bool is_call_exit_node_without_layout_object_enabled_;
    bool is_canvas_2d_canvas_filter_enabled_;
    bool is_canvas_2d_gpu_transfer_enabled_;
    bool is_canvas_2d_layers_enabled_;
    bool is_canvas_2d_layers_with_options_enabled_;
    bool is_canvas_2d_mesh_enabled_;
    bool is_canvas_draw_element_enabled_;
    bool is_canvas_floating_point_enabled_;
    bool is_canvas_global_hdr_headroom_enabled_;
    bool is_canvas_gradient_css_color_4_enabled_;
    bool is_canvas_hdr_enabled_;
    bool is_canvas_text_metrics_precise_bounds_enabled_;
    bool is_canvas_tone_mapping_enabled_;
    bool is_canvas_uses_arc_paint_op_enabled_;
    bool is_capability_delegation_display_capture_request_enabled_;
    bool is_capture_controller_enabled_;
    bool is_captured_mouse_events_enabled_;
    bool is_captured_surface_control_enabled_;
    bool is_captured_surface_resolution_enabled_;
    bool is_capture_handle_enabled_;
    bool is_caret_with_text_affinity_upstream_enabled_;
    bool is_cct_new_rfm_push_behavior_enabled_;
    bool is_checkable_input_type_layout_inline_enabled_;
    bool is_check_for_canonical_position_in_idle_spell_check_enabled_;
    bool is_check_visibility_extra_properties_enabled_;
    bool is_clamp_word_boundary_to_content_editable_scope_enabled_;
    bool is_clear_current_target_after_dispatch_enabled_;
    bool is_clear_focus_within_on_subtree_removal_enabled_;
    bool is_clear_target_only_if_in_shadow_tree_enabled_;
    bool is_click_focus_doesnt_persist_status_bubble_enabled_;
    bool is_clipboard_event_target_can_be_focused_element_enabled_;
    bool is_clipboard_event_target_uses_container_node_enabled_;
    bool is_clipboard_item_with_dom_string_support_enabled_;
    bool is_clip_element_visible_bounds_in_local_root_enabled_;
    bool is_clip_path_nested_raster_optimization_enabled_;
    bool is_coalesce_selectionchange_event_enabled_;
    bool is_coep_reflection_enabled_;
    bool is_collapse_zero_width_space_when_reuse_item_enabled_;
    bool is_color_input_accepts_css_colors_enabled_;
    bool is_color_space_display_p_3_linear_enabled_;
    bool is_color_space_predefined_linear_spaces_enabled_;
    bool is_color_space_rec_2100_linear_enabled_;
    bool is_command_event_not_composed_enabled_;
    bool is_comma_separated_container_queries_enabled_;
    bool is_composed_path_return_target_being_dispatched_enabled_;
    bool is_composite_bg_color_animation_enabled_;
    bool is_composite_box_shadow_animation_enabled_;
    bool is_composite_clip_path_animation_enabled_;
    bool is_composited_animations_cancelled_asynchronously_enabled_;
    bool is_composited_selection_update_enabled_;
    bool is_compositing_decision_at_animation_phase_boundaries_enabled_;
    bool is_composition_foreground_markers_enabled_;
    bool is_compositor_event_trigger_enabled_;
    bool is_compositor_timeline_trigger_enabled_;
    bool is_compression_dictionary_transport_enabled_;
    bool is_computed_accessibility_info_enabled_;
    bool is_compute_inline_contents_safe_retarget_enabled_;
    bool is_compute_pressure_enabled_;
    bool is_compute_pressure_own_contribution_estimate_enabled_;
    bool is_connection_allowlist_enabled_;
    bool is_consider_sub_or_super_script_ancestor_align_for_caret_selection_enabled_;
    bool is_contacts_manager_enabled_;
    bool is_contacts_manager_extra_properties_enabled_;
    bool is_container_name_only_enabled_;
    bool is_container_timing_enabled_;
    bool is_content_index_enabled_;
    bool is_context_menu_enabled_;
    bool is_controlled_frame_enabled_;
    bool is_controlled_frame_web_request_security_info_enabled_;
    bool is_cookie_store_api_max_age_enabled_;
    bool is_cookie_store_api_whitespace_stripping_enabled_;
    bool is_coop_restrict_properties_enabled_;
    bool is_correct_template_form_parsing_enabled_;
    bool is_cors_rfc_1918_enabled_;
    bool is_cpu_performance_enabled_;
    bool is_crash_reporting_storage_api_enabled_;
    bool is_create_inline_contents_exclude_out_of_flow_enabled_;
    bool is_csp_hashes_v_1_enabled_;
    bool is_csp_report_hash_enabled_;
    bool is_css_accent_color_keyword_enabled_;
    bool is_css_active_caption_maps_to_canvas_enabled_;
    bool is_css_alpha_color_function_enabled_;
    bool is_css_alt_counter_enabled_;
    bool is_css_anchor_with_transforms_enabled_;
    bool is_css_animation_iteration_composite_enabled_;
    bool is_css_argument_grammar_enabled_;
    bool is_css_at_rule_counter_style_image_symbols_enabled_;
    bool is_css_at_rule_counter_style_speak_as_descriptor_enabled_;
    bool is_css_background_clip_border_area_enabled_;
    bool is_css_border_shape_enabled_;
    bool is_css_calc_simplification_and_serialization_enabled_;
    bool is_css_caret_animation_enabled_;
    bool is_css_caret_shape_enabled_;
    bool is_css_case_sensitive_selector_enabled_;
    bool is_css_ch_unit_spec_compliant_fallback_enabled_;
    bool is_css_color_typed_om_enabled_;
    bool is_css_container_progress_notation_enabled_;
    bool is_css_container_style_queries_range_enabled_;
    bool is_css_contrast_color_enabled_;
    bool is_css_corners_shorthand_enabled_;
    bool is_css_counter_reset_reversed_enabled_;
    bool is_css_cross_fade_enabled_;
    bool is_css_custom_media_enabled_;
    bool is_css_dynamic_range_limit_enabled_;
    bool is_css_enumerated_custom_properties_enabled_;
    bool is_css_font_family_serialization_enabled_;
    bool is_css_font_size_adjust_enabled_;
    bool is_css_functions_enabled_;
    bool is_css_gap_decoration_enabled_;
    bool is_css_grid_gap_suppression_enabled_;
    bool is_css_grid_lanes_layout_enabled_;
    bool is_css_hanging_punctuation_enabled_;
    bool is_css_hex_alpha_color_enabled_;
    bool is_css_ident_function_enabled_;
    bool is_css_image_animation_enabled_;
    bool is_css_inherit_function_enabled_;
    bool is_css_keyframes_rule_length_enabled_;
    bool is_css_lang_extended_ranges_enabled_;
    bool is_css_layout_api_enabled_;
    bool is_css_letter_and_word_spacing_percentage_enabled_;
    bool is_css_light_dark_image_enabled_;
    bool is_css_line_clamp_enabled_;
    bool is_css_line_clamp_line_breaking_ellipsis_enabled_;
    bool is_css_line_clamp_lines_and_height_enabled_;
    bool is_css_list_counter_accounting_enabled_;
    bool is_css_logical_combination_pseudo_enabled_;
    bool is_css_marker_nested_pseudo_element_enabled_;
    bool is_css_media_progress_notation_enabled_;
    bool is_css_mixins_enabled_;
    bool is_css_nested_pseudo_elements_enabled_;
    bool is_cssom_get_computed_style_pseudo_element_requires_colon_enabled_;
    bool is_css_overscroll_behavior_chain_enabled_;
    bool is_css_paint_api_arguments_enabled_;
    bool is_css_parser_ignore_charset_for_urls_enabled_;
    bool is_css_polygon_rounding_enabled_;
    bool is_css_position_sticky_static_scroll_position_enabled_;
    bool is_css_progress_notation_enabled_;
    bool is_css_pseudo_column_enabled_;
    bool is_css_pseudo_element_backdrop_enabled_;
    bool is_css_pseudo_element_interface_enabled_;
    bool is_css_pseudo_element_view_transitions_enabled_;
    bool is_css_pseudo_has_slotted_enabled_;
    bool is_css_pseudo_playing_paused_enabled_;
    bool is_css_pseudo_scroll_buttons_enabled_;
    bool is_css_pseudo_scroll_markers_enabled_;
    bool is_css_random_function_enabled_;
    bool is_css_random_function_typed_om_enabled_;
    bool is_css_resize_auto_enabled_;
    bool is_css_resource_integrity_enforcement_enabled_;
    bool is_css_revert_rule_enabled_;
    bool is_css_ruby_overhang_enabled_;
    bool is_css_safe_printable_inset_enabled_;
    bool is_css_scopeified_parent_pseudo_class_enabled_;
    bool is_css_scope_import_enabled_;
    bool is_css_scrolled_container_queries_enabled_;
    bool is_css_scroll_initial_target_enabled_;
    bool is_css_scroll_marker_group_modes_enabled_;
    bool is_css_scroll_marker_target_before_after_enabled_;
    bool is_css_scroll_snap_change_event_enabled_;
    bool is_css_scroll_snap_changing_event_enabled_;
    bool is_css_scroll_snap_event_constructor_exposed_enabled_;
    bool is_css_scroll_snap_events_enabled_;
    bool is_css_scroll_target_group_enabled_;
    bool is_css_scroll_target_group_aria_current_enabled_;
    bool is_css_shape_ellipse_circle_position_serialization_enabled_;
    bool is_css_shape_outside_path_and_shape_support_enabled_;
    bool is_css_shape_outside_rect_and_xywh_support_enabled_;
    bool is_css_style_sheet_init_base_url_enabled_;
    bool is_css_supports_at_rule_function_enabled_;
    bool is_css_supports_for_import_rules_enabled_;
    bool is_css_supports_named_feature_function_enabled_;
    bool is_css_system_accent_color_enabled_;
    bool is_css_text_align_match_parent_enabled_;
    bool is_css_text_decoration_skip_ink_all_enabled_;
    bool is_css_text_decoration_skip_spaces_enabled_;
    bool is_css_text_fit_enabled_;
    bool is_css_text_fit_reshaping_enabled_;
    bool is_css_text_indent_enabled_;
    bool is_css_text_indent_as_primitive_enabled_;
    bool is_css_text_spacing_enabled_;
    bool is_css_text_transform_full_size_kana_enabled_;
    bool is_css_text_transform_full_width_enabled_;
    bool is_css_text_transform_multi_keyword_enabled_;
    bool is_css_timeline_scope_all_enabled_;
    bool is_css_timeline_scope_global_enabled_;
    bool is_css_typed_arithmetic_enabled_;
    bool is_css_url_request_modifiers_enabled_;
    bool is_css_user_select_contain_enabled_;
    bool is_css_user_valid_and_user_invalid_for_radio_enabled_;
    bool is_css_video_dynamic_range_media_queries_enabled_;
    bool is_css_view_transition_auto_name_enabled_;
    bool is_custom_elements_disable_formatting_fixups_enabled_;
    bool is_customizable_combobox_enabled_;
    bool is_customizable_select_multiple_popup_enabled_;
    bool is_custom_scrollbar_apply_minimum_thumb_length_enabled_;
    bool is_database_enabled_;
    bool is_date_time_local_arabic_comma_workaround_enabled_;
    bool is_declarative_css_modules_enabled_;
    bool is_declarative_css_modules_style_tag_enabled_;
    bool is_decouple_computed_border_width_from_style_enabled_;
    bool is_decouple_resolved_column_rule_width_from_style_enabled_;
    bool is_delegates_focus_text_control_input_fix_enabled_;
    bool is_delete_text_in_content_editable_before_removing_children_enabled_;
    bool is_deprecate_unload_opt_out_enabled_;
    bool is_desktop_capture_disable_local_echo_control_enabled_;
    bool is_desktop_pw_as_additional_windowing_controls_enabled_;
    bool is_desktop_pw_as_additional_windowing_controls_on_move_enabled_;
    bool is_device_attributes_enabled_;
    bool is_device_orientation_request_permission_enabled_;
    bool is_device_posture_enabled_;
    bool is_dialog_close_when_open_removed_enabled_;
    bool is_dialog_new_focus_behavior_enabled_;
    bool is_digital_goods_enabled_;
    bool is_digital_goods_v_2_1_enabled_;
    bool is_direct_sockets_enabled_;
    bool is_direct_sockets_in_service_workers_enabled_;
    bool is_direct_sockets_in_shared_workers_enabled_;
    bool is_disable_anchor_center_on_align_justify_items_enabled_;
    bool is_disable_different_origin_subframe_dialog_suppression_enabled_;
    bool is_disable_ellipsis_when_scrolled_enabled_;
    bool is_disable_reduce_accept_language_enabled_;
    bool is_disable_remove_format_for_plain_text_only_editable_div_enabled_;
    bool is_disallow_disconnected_area_navigation_enabled_;
    bool is_disallow_picker_for_readonly_inputs_enabled_;
    bool is_disconnect_websocket_on_bf_cache_enabled_;
    bool is_dispatch_hidden_visibility_transitions_enabled_;
    bool is_dispatch_selectionchange_event_per_element_enabled_;
    bool is_display_contents_focusable_enabled_;
    bool is_display_cutout_api_enabled_;
    bool is_document_active_view_transition_enabled_;
    bool is_document_cookie_enabled_;
    bool is_document_domain_enabled_;
    bool is_document_isolation_policy_enabled_;
    bool is_document_open_iframe_unload_events_enabled_;
    bool is_document_open_origin_alias_removal_enabled_;
    bool is_document_open_sandbox_inheritance_removal_enabled_;
    bool is_document_patching_enabled_;
    bool is_document_picture_in_picture_api_enabled_;
    bool is_document_picture_in_picture_prefer_initial_placement_enabled_;
    bool is_document_picture_in_picture_user_activation_enabled_;
    bool is_document_policy_document_domain_enabled_;
    bool is_document_policy_expect_no_linked_resources_enabled_;
    bool is_document_policy_include_js_call_stacks_in_crash_reports_enabled_;
    bool is_document_policy_in_dedicated_worker_enabled_;
    bool is_document_policy_negotiation_enabled_;
    bool is_document_policy_network_efficiency_guardrails_enabled_;
    bool is_document_policy_sync_xhr_enabled_;
    bool is_document_write_enabled_;
    bool is_dom_activate_bubbles_inheritance_enabled_;
    bool is_dont_leak_shadow_trees_in_drag_events_enabled_;
    bool is_edit_context_assignment_as_per_spec_enabled_;
    bool is_edit_context_handle_text_or_selection_update_during_composition_enabled_;
    bool is_edit_emoji_tag_sequence_enabled_;
    bool is_editing_line_movement_with_ruby_fix_enabled_;
    bool is_element_capture_enabled_;
    bool is_element_inner_text_handle_first_line_style_enabled_;
    bool is_element_internals_behaviors_enabled_;
    bool is_element_specific_read_only_constraint_validation_enabled_;
    bool is_email_verification_protocol_enabled_;
    bool is_emoji_monochrome_rendering_enabled_;
    bool is_endpoint_inclusive_commit_styles_enabled_;
    bool is_enforce_anonymity_exposure_enabled_;
    bool is_enter_in_open_shadow_roots_enabled_;
    bool is_entropy_ignored_for_first_video_frame_lcp_enabled_;
    bool is_event_pseudo_target_property_enabled_;
    bool is_event_timing_interaction_count_enabled_;
    bool is_event_timing_target_selector_enabled_;
    bool is_event_trigger_enabled_;
    bool is_experimental_content_security_policy_features_enabled_;
    bool is_experimental_js_profiler_markers_enabled_;
    bool is_experimental_machine_learning_neural_network_enabled_;
    bool is_experimental_policies_enabled_;
    bool is_expose_css_font_feature_values_rule_enabled_;
    bool is_expose_render_time_non_tao_delayed_image_enabled_;
    bool is_extended_shape_cache_enabled_;
    bool is_extended_text_metrics_enabled_;
    bool is_external_popup_menu_click_event_enabled_;
    bool is_eye_dropper_api_enabled_;
    bool is_face_detector_enabled_;
    bool is_fast_position_iterator_enabled_;
    bool is_fed_cm_enabled_;
    bool is_fed_cm_autofill_enabled_;
    bool is_fed_cm_delegation_enabled_;
    bool is_fed_cm_error_attribute_enabled_;
    bool is_fed_cm_id_p_registration_enabled_;
    bool is_fed_cm_lightweight_mode_enabled_;
    bool is_fed_cm_multiple_identity_providers_enabled_;
    bool is_fed_cm_navigation_interception_enabled_;
    bool is_fed_cm_non_string_token_enabled_;
    bool is_fenced_frames_enabled_;
    bool is_fenced_frames_api_changes_enabled_;
    bool is_fenced_frames_default_mode_enabled_;
    bool is_fenced_frames_local_unpartitioned_data_access_enabled_;
    bool is_fetch_body_bytes_enabled_;
    bool is_fetch_later_api_enabled_;
    bool is_fetch_retry_enabled_;
    bool is_fetch_upload_streaming_enabled_;
    bool is_file_handling_enabled_;
    bool is_file_handling_icons_enabled_;
    bool is_file_system_enabled_;
    bool is_file_system_access_enabled_;
    bool is_file_system_access_api_experimental_enabled_;
    bool is_file_system_access_get_cloud_identifiers_enabled_;
    bool is_file_system_access_local_enabled_;
    bool is_file_system_access_locking_scheme_enabled_;
    bool is_file_system_access_origin_private_enabled_;
    bool is_file_system_access_revoke_read_on_remove_enabled_;
    bool is_file_system_access_write_mode_enabled_;
    bool is_file_system_observer_enabled_;
    bool is_file_system_observer_unobserve_enabled_;
    bool is_filterable_select_enabled_;
    bool is_filter_container_level_styles_enabled_;
    bool is_filtering_primitives_enabled_;
    bool is_find_first_misspelling_end_when_non_editable_enabled_;
    bool is_first_line_on_list_item_enabled_;
    bool is_first_line_text_metrics_enabled_;
    bool is_fix_html_form_control_element_is_read_only_enabled_;
    bool is_fix_justify_query_command_value_enabled_;
    bool is_fix_linebreak_for_pre_tag_enabled_;
    bool is_fix_map_element_empty_name_bug_enabled_;
    bool is_fix_marker_suppression_for_appearance_auto_enabled_;
    bool is_fix_next_position_calculation_in_insert_list_enabled_;
    bool is_fix_strikethrough_toggle_in_empty_content_editable_enabled_;
    bool is_fix_visual_rect_remote_viewport_transform_enabled_;
    bool is_fledge_enabled_;
    bool is_fledge_auction_deal_support_enabled_;
    bool is_fledge_bidding_and_auction_server_api_enabled_;
    bool is_fledge_bidding_and_auction_server_api_multi_seller_enabled_;
    bool is_fledge_clickiness_enabled_;
    bool is_fledge_custom_max_auction_ad_components_enabled_;
    bool is_fledge_deprecated_render_url_replacements_enabled_;
    bool is_fledge_direct_from_seller_signals_header_ad_slot_enabled_;
    bool is_fledge_direct_from_seller_signals_web_bundles_enabled_;
    bool is_fledge_multi_bid_enabled_;
    bool is_fledge_private_model_training_enabled_;
    bool is_fledge_real_time_reporting_enabled_;
    bool is_fledge_seller_nonce_enabled_;
    bool is_fledge_seller_script_execution_mode_enabled_;
    bool is_fledge_trusted_signals_k_vv_1_creative_scanning_enabled_;
    bool is_fledge_trusted_signals_k_vv_2_contextual_data_enabled_;
    bool is_fledge_trusted_signals_k_vv_2_support_enabled_;
    bool is_flex_wrap_balance_enabled_;
    bool is_focusgroup_enabled_;
    bool is_focusgroup_grid_enabled_;
    bool is_font_access_enabled_;
    bool is_font_data_service_enabled_;
    bool is_font_fallback_for_tab_size_enabled_;
    bool is_font_family_postscript_matching_ct_migration_enabled_;
    bool is_font_family_style_matching_ct_migration_enabled_;
    bool is_font_feature_settings_descriptor_enabled_;
    bool is_font_format_avar_2_enabled_;
    bool is_font_language_override_enabled_;
    bool is_font_match_aliases_as_last_resort_enabled_;
    bool is_font_style_oblique_zero_degree_as_normal_enabled_;
    bool is_font_variation_settings_descriptor_enabled_;
    bool is_forced_colors_enabled_;
    bool is_force_eager_measure_memory_enabled_;
    bool is_force_reduce_motion_enabled_;
    bool is_fractional_scroll_offsets_enabled_;
    bool is_fragmented_oof_in_cb_enabled_;
    bool is_freeze_frames_on_visibility_enabled_;
    bool is_gamepad_multitouch_enabled_;
    bool is_gamepad_raw_input_change_event_enabled_;
    bool is_gamepad_window_event_handlers_enabled_;
    bool is_geolocation_element_enabled_;
    bool is_geometry_mapper_singular_transform_fix_enabled_;
    bool is_geometry_utils_enabled_;
    bool is_geometry_utils_for_css_pseudo_element_enabled_;
    bool is_get_all_screens_media_enabled_;
    bool is_get_computed_style_outside_flat_tree_enabled_;
    bool is_get_display_media_enabled_;
    bool is_get_display_media_requires_user_activation_enabled_;
    bool is_get_display_media_window_audio_capture_enabled_;
    bool is_get_elements_by_name_only_html_elements_enabled_;
    bool is_get_user_media_echo_cancellation_modes_enabled_;
    bool is_group_effect_enabled_;
    bool is_handle_deletion_at_start_and_end_boundary_containing_hidden_element_enabled_;
    bool is_handle_disconnected_selection_during_dom_changes_enabled_;
    bool is_handle_invalid_mask_image_with_backdrop_filter_enabled_;
    bool is_handle_shadow_dom_in_substring_util_enabled_;
    bool is_handwriting_recognition_enabled_;
    bool is_has_ua_visual_transition_enabled_;
    bool is_heading_offset_enabled_;
    bool is_hide_video_controls_when_unneeded_enabled_;
    bool is_highlights_from_point_enabled_;
    bool is_hit_test_border_radius_for_stacking_context_enabled_;
    bool is_hit_test_container_transform_state_for_preserve_3d_enabled_;
    bool is_href_translate_enabled_;
    bool is_hsts_top_level_navigations_only_enabled_;
    bool is_html_adoption_algorithm_new_steps_enabled_;
    bool is_html_command_actions_v_2_enabled_;
    bool is_html_command_element_removal_enabled_;
    bool is_html_command_for_scroll_commands_enabled_;
    bool is_html_element_scroll_parent_enabled_;
    bool is_html_image_element_actual_natural_size_enabled_;
    bool is_html_input_element_drop_webkit_clear_button_enabled_;
    bool is_html_interest_for_interest_button_pseudo_enabled_;
    bool is_html_link_element_attribute_value_changes_enabled_;
    bool is_html_parser_yield_and_delay_often_for_testing_enabled_;
    bool is_html_parser_yield_by_user_timing_enabled_;
    bool is_html_printing_artifact_annotations_enabled_;
    bool is_html_processing_instruction_enabled_;
    bool is_icu_capitalization_enabled_;
    bool is_ignore_letter_spacing_in_cursive_scripts_enabled_;
    bool is_image_data_pixel_format_enabled_;
    bool is_image_document_use_layout_width_enabled_;
    bool is_image_srcset_reselection_enabled_;
    bool is_implicit_root_scroller_enabled_;
    bool is_improved_source_retargeting_enabled_;
    bool is_incoming_call_notifications_enabled_;
    bool is_inert_element_non_editable_enabled_;
    bool is_infinite_cull_rect_enabled_;
    bool is_inherit_user_modify_without_contenteditable_enabled_;
    bool is_inline_block_line_navigation_enabled_;
    bool is_inline_script_cache_hint_enabled_;
    bool is_inner_html_parser_fastpath_log_failure_enabled_;
    bool is_input_event_data_transfer_for_insert_cmd_enabled_;
    bool is_input_events_delete_non_collapsed_selection_enabled_;
    bool is_input_in_select_enabled_;
    bool is_input_multiple_fields_ui_enabled_;
    bool is_insert_blockquote_before_outer_block_enabled_;
    bool is_installed_app_enabled_;
    bool is_install_element_enabled_;
    bool is_install_on_device_speech_recognition_enabled_;
    bool is_integrity_policy_script_enabled_;
    bool is_interest_events_non_composed_enabled_;
    bool is_interest_groups_in_shared_storage_worklet_enabled_;
    bool is_intersection_observer_composited_animations_force_main_frames_enabled_;
    bool is_inverted_colors_enabled_;
    bool is_invisible_svg_animation_throttling_enabled_;
    bool is_java_script_compile_hints_per_function_magic_runtime_enabled_;
    bool is_java_script_source_phase_imports_enabled_;
    bool is_keyboard_accessible_tooltip_enabled_;
    bool is_key_system_track_configuration_encryption_scheme_enabled_;
    bool is_label_interactive_content_check_before_handler_enabled_;
    bool is_lang_attribute_aware_form_control_ui_enabled_;
    bool is_language_detection_api_enabled_;
    bool is_language_detection_api_for_workers_enabled_;
    bool is_layout_box_rect_getters_use_fragments_enabled_;
    bool is_layout_ignore_margins_for_sticky_enabled_;
    bool is_layout_image_empty_natural_size_before_size_available_enabled_;
    bool is_layout_table_cell_alignment_safe_enabled_;
    bool is_lazy_image_conformant_load_event_timing_enabled_;
    bool is_lazy_load_video_and_audio_enabled_;
    bool is_left_click_to_handle_suggestion_enabled_;
    bool is_light_dismiss_from_click_enabled_;
    bool is_link_blur_improvement_enabled_;
    bool is_list_owner_must_have_css_box_enabled_;
    bool is_local_network_access_non_secure_context_allowed_enabled_;
    bool is_local_network_access_permission_policy_enabled_;
    bool is_local_network_access_split_permissions_enabled_;
    bool is_local_network_access_web_rtc_enabled_;
    bool is_locked_mode_enabled_;
    bool is_logical_start_of_line_block_fallback_enabled_;
    bool is_login_element_enabled_;
    bool is_long_animation_frame_source_char_position_enabled_;
    bool is_long_animation_frame_source_line_column_enabled_;
    bool is_long_animation_frame_source_line_column_interface_enabled_;
    bool is_long_animation_frame_style_duration_enabled_;
    bool is_long_press_link_select_text_enabled_;
    bool is_long_task_from_long_animation_frame_enabled_;
    bool is_mac_character_fallback_cache_enabled_;
    bool is_mac_disable_ctrl_home_end_enabled_;
    bool is_machine_learning_neural_network_enabled_;
    bool is_mac_system_clipboard_permission_check_enabled_;
    bool is_managed_configuration_enabled_;
    bool is_manual_text_enabled_;
    bool is_margin_trim_enabled_;
    bool is_mask_deserialization_time_for_cross_origin_messages_enabled_;
    bool is_mathml_operator_rtl_mirroring_enabled_;
    bool is_mathml_serialization_on_copy_enabled_;
    bool is_mathml_skip_mtr_tag_in_ancestor_wrapping_enabled_;
    bool is_measure_memory_enabled_;
    bool is_media_capabilities_encoding_info_enabled_;
    bool is_media_capabilities_spatial_audio_enabled_;
    bool is_media_capture_enabled_;
    bool is_media_capture_background_blur_enabled_;
    bool is_media_capture_camera_controls_enabled_;
    bool is_media_capture_configuration_change_enabled_;
    bool is_media_capture_voice_isolation_enabled_;
    bool is_media_controls_expand_gesture_enabled_;
    bool is_media_controls_overlay_play_button_enabled_;
    bool is_media_element_volume_greater_than_one_enabled_;
    bool is_media_engagement_bypass_autoplay_policies_enabled_;
    bool is_media_latency_hint_enabled_;
    bool is_media_playback_while_not_visible_permission_policy_enabled_;
    bool is_media_query_navigation_controls_enabled_;
    bool is_media_session_enabled_;
    bool is_media_session_chapter_information_enabled_;
    bool is_media_source_experimental_enabled_;
    bool is_media_source_extensions_for_webcodecs_enabled_;
    bool is_media_stream_track_transfer_enabled_;
    bool is_media_stream_track_web_speech_enabled_;
    bool is_memory_consumer_for_ng_shape_cache_enabled_;
    bool is_menu_elements_enabled_;
    bool is_merge_fixed_layers_enabled_;
    bool is_merge_sticky_layers_enabled_;
    bool is_message_port_close_event_enabled_;
    bool is_middle_click_autoscroll_enabled_;
    bool is_mixed_content_autoupgrades_use_is_mixed_content_restricted_in_frame_enabled_;
    bool is_mobile_layout_theme_enabled_;
    bool is_modify_paragraph_cross_editingoundary_enabled_;
    bool is_module_preload_referrer_enabled_;
    bool is_module_preload_style_json_enabled_;
    bool is_mojo_js_enabled_;
    bool is_mojo_js_test_enabled_;
    bool is_move_ending_selection_to_list_child_enabled_;
    bool is_multicol_column_wrapping_enabled_;
    bool is_navigate_event_add_handler_on_precommit_enabled_;
    bool is_navigate_event_clear_on_restore_enabled_;
    bool is_navigate_event_defer_cross_document_commit_enabled_;
    bool is_navigation_event_timing_enabled_;
    bool is_navigation_id_enabled_;
    bool is_navigator_content_utils_enabled_;
    bool is_net_info_constant_type_enabled_;
    bool is_net_info_downlink_max_enabled_;
    bool is_new_html_setting_methods_enabled_;
    bool is_no_extend_selection_to_user_select_none_out_of_flow_enabled_;
    bool is_no_font_antialiasing_enabled_;
    bool is_no_idle_encoding_for_web_tests_enabled_;
    bool is_non_empty_blockquotes_on_outdenting_enabled_;
    bool is_non_empty_visible_text_selection_for_text_fragment_enabled_;
    bool is_non_standard_appearance_value_slider_vertical_enabled_;
    bool is_normalize_line_endings_in_insert_text_enabled_;
    bool is_normalize_nbsp_for_paste_and_drop_enabled_;
    bool is_notification_constructor_enabled_;
    bool is_notification_content_image_enabled_;
    bool is_notifications_enabled_;
    bool is_notification_triggers_enabled_;
    bool is_number_input_full_width_chars_enabled_;
    bool is_off_main_thread_css_paint_enabled_;
    bool is_offscreen_canvas_get_context_attributes_enabled_;
    bool is_offset_path_transform_update_fix_enabled_;
    bool is_omit_blur_event_on_element_removal_enabled_;
    bool is_on_device_web_speech_available_enabled_;
    bool is_on_device_web_speech_quality_enabled_;
    bool is_opaque_range_enabled_;
    bool is_open_popover_invoker_restrict_to_same_tree_scope_enabled_;
    bool is_orientation_event_enabled_;
    bool is_origin_api_enabled_;
    bool is_origin_isolation_header_enabled_;
    bool is_origin_policy_enabled_;
    bool is_origin_trials_sample_api_enabled_;
    bool is_origin_trials_sample_api_browser_read_write_enabled_;
    bool is_origin_trials_sample_api_dependent_enabled_;
    bool is_origin_trials_sample_api_deprecation_enabled_;
    bool is_origin_trials_sample_api_expiry_grace_period_enabled_;
    bool is_origin_trials_sample_api_expiry_grace_period_third_party_enabled_;
    bool is_origin_trials_sample_api_implied_enabled_;
    bool is_origin_trials_sample_api_invalid_os_enabled_;
    bool is_origin_trials_sample_api_navigation_enabled_;
    bool is_origin_trials_sample_api_persistent_expiry_grace_period_enabled_;
    bool is_origin_trials_sample_api_persistent_feature_enabled_;
    bool is_origin_trials_sample_api_persistent_invalid_os_enabled_;
    bool is_origin_trials_sample_api_persistent_third_party_deprecation_feature_enabled_;
    bool is_origin_trials_sample_api_third_party_enabled_;
    bool is_outline_draw_auto_style_zero_width_enabled_;
    bool is_overlay_global_rule_removal_enabled_;
    bool is_overlay_property_enabled_;
    bool is_overscroll_gestures_enabled_;
    bool is_page_popup_enabled_;
    bool is_page_popup_copy_paste_enabled_;
    bool is_page_reveal_event_enabled_;
    bool is_page_swap_event_enabled_;
    bool is_paint_holding_for_iframes_enabled_;
    bool is_paint_offset_translation_for_composited_enabled_;
    bool is_paint_timing_mixin_enabled_;
    bool is_paint_under_invalidation_checking_enabled_;
    bool is_parakeet_enabled_;
    bool is_partial_completion_not_allowed_in_move_paragraphs_enabled_;
    bool is_partition_visited_link_database_with_self_links_enabled_;
    bool is_password_reveal_enabled_;
    bool is_payment_app_enabled_;
    bool is_payment_link_detection_enabled_;
    bool is_payment_method_change_event_enabled_;
    bool is_payment_request_enabled_;
    bool is_performance_manager_instrumentation_enabled_;
    bool is_performance_mark_custom_user_timing_from_subframe_enabled_;
    bool is_performance_mark_feature_usage_enabled_;
    bool is_performance_navigation_timing_confidence_enabled_;
    bool is_periodic_background_sync_enabled_;
    bool is_per_method_can_make_payment_quota_enabled_;
    bool is_permissions_request_revoke_enabled_;
    bool is_placeholder_visibility_enabled_;
    bool is_p_na_cl_enabled_;
    bool is_pointer_event_device_id_enabled_;
    bool is_pointer_lock_on_android_enabled_;
    bool is_pointer_raw_update_only_in_secure_context_enabled_;
    bool is_popover_hint_new_behavior_enabled_;
    bool is_position_outside_tab_span_check_sibling_node_enabled_;
    bool is_position_visibility_ignore_non_clip_ancestors_enabled_;
    bool is_potential_permissions_policy_reporting_enabled_;
    bool is_precise_memory_info_enabled_;
    bool is_prefer_default_scrollbar_styles_enabled_;
    bool is_prefer_non_composited_scrolling_enabled_;
    bool is_preferred_audio_output_devices_enabled_;
    bool is_prefers_reduced_data_enabled_;
    bool is_preload_link_rel_data_urls_enabled_;
    bool is_prerender_2_enabled_;
    bool is_prerender_2_cross_origin_iframes_enabled_;
    bool is_prerender_activation_by_form_submission_enabled_;
    bool is_prerender_until_script_enabled_;
    bool is_presentation_enabled_;
    bool is_preserve_drop_effect_enabled_;
    bool is_prevent_undo_if_not_editable_enabled_;
    bool is_private_aggregation_api_error_reporting_enabled_;
    bool is_private_aggregation_api_max_contributions_enabled_;
    bool is_private_network_access_null_ip_address_enabled_;
    bool is_private_state_tokens_enabled_;
    bool is_private_state_tokens_always_allow_issuance_enabled_;
    bool is_profiler_api_enabled_;
    bool is_profiler_api_for_dedicated_worker_enabled_;
    bool is_programmatic_scroll_promise_enabled_;
    bool is_progress_max_is_positive_enabled_;
    bool is_propagate_overscroll_behavior_from_root_enabled_;
    bool is_protected_origin_trials_sample_api_enabled_;
    bool is_protected_origin_trials_sample_api_dependent_enabled_;
    bool is_protected_origin_trials_sample_api_implied_enabled_;
    bool is_pseudo_elements_focusable_enabled_;
    bool is_pseudo_elements_hit_testable_enabled_;
    bool is_pseudo_elements_hoverable_enabled_;
    bool is_push_message_data_bytes_enabled_;
    bool is_push_messaging_enabled_;
    bool is_push_messaging_subscription_change_enabled_;
    bool is_quota_exceeded_error_update_enabled_;
    bool is_quote_first_line_style_enabled_;
    bool is_raster_inducing_scroll_enabled_;
    bool is_readable_stream_byob_reader_read_min_option_enabled_;
    bool is_read_clipboard_data_on_clipboard_item_get_type_enabled_;
    bool is_reading_flow_with_slots_enabled_;
    bool is_recheck_parent_during_node_vector_insertion_enabled_;
    bool is_record_same_document_presentation_time_once_enabled_;
    bool is_reduce_accept_language_enabled_;
    bool is_reduce_user_agent_data_linux_platform_version_enabled_;
    bool is_reduce_user_agent_minor_version_enabled_;
    bool is_region_capture_enabled_;
    bool is_related_website_partition_api_enabled_;
    bool is_rel_opener_bcg_dependency_hint_enabled_;
    bool is_remote_playback_enabled_;
    bool is_remote_playback_backend_enabled_;
    bool is_remove_charset_auto_detection_for_iso_2022_jp_enabled_;
    bool is_remove_children_in_replace_children_enabled_;
    bool is_remove_collapsed_placeholder_for_content_editable_enabled_;
    bool is_remove_dangling_markup_in_target_enabled_;
    bool is_remove_data_url_in_svg_use_enabled_;
    bool is_remove_format_filter_background_color_enabled_;
    bool is_remove_non_allowlisted_create_event_enabled_;
    bool is_remove_scroll_node_workaround_enabled_;
    bool is_remove_selection_canonicalization_in_move_paragraph_enabled_;
    bool is_remove_visible_selection_in_dom_selection_enabled_;
    bool is_render_blocking_full_frame_rate_enabled_;
    bool is_render_blocking_status_enabled_;
    bool is_render_priority_attribute_enabled_;
    bool is_report_first_frame_time_as_render_time_enabled_;
    bool is_report_layout_shift_rects_in_css_pixels_enabled_;
    bool is_request_is_reload_navigation_enabled_;
    bool is_request_main_frame_after_first_video_frame_enabled_;
    bool is_resolve_var_styles_on_copy_enabled_;
    bool is_resource_timing_content_encoding_enabled_;
    bool is_resource_timing_content_type_enabled_;
    bool is_resource_timing_initiator_enabled_;
    bool is_resource_timing_use_cors_for_body_sizes_enabled_;
    bool is_respect_overscroll_behavior_for_scroll_bubbling_enabled_;
    bool is_responsive_iframes_enabled_;
    bool is_restrict_gamepad_access_enabled_;
    bool is_restrict_own_audio_enabled_;
    bool is_root_scrollbar_follows_browser_theme_enabled_;
    bool is_route_matching_enabled_;
    bool is_rtc_always_negotiate_data_channels_enabled_;
    bool is_rtc_audio_jitter_buffer_max_packets_enabled_;
    bool is_rtc_data_channel_priority_enabled_;
    bool is_rtc_diagnostic_logging_enabled_;
    bool is_rtc_encoded_frame_audio_level_enabled_;
    bool is_rtc_encoded_frame_set_metadata_enabled_;
    bool is_rtc_encoded_frame_timestamps_enabled_;
    bool is_rtc_encoded_video_frame_additional_metadata_enabled_;
    bool is_rtc_jitter_buffer_target_enabled_;
    bool is_rtc_legacy_callback_based_get_stats_enabled_;
    bool is_rtc_rtp_encoding_parameters_codec_enabled_;
    bool is_rtc_rtp_scale_resolution_down_to_enabled_;
    bool is_rtc_rtp_script_transform_enabled_;
    bool is_rtc_rtp_transport_enabled_;
    bool is_rtc_stats_relative_packet_arrival_delay_enabled_;
    bool is_rtc_svc_scalability_mode_enabled_;
    bool is_run_microtask_before_xml_script_enabled_;
    bool is_run_snapshot_post_layout_state_steps_enabled_;
    bool is_sanitizer_api_enabled_;
    bool is_scoped_custom_element_registry_enabled_;
    bool is_scoped_view_transitions_enabled_;
    bool is_screen_detailed_hdr_headroom_enabled_;
    bool is_script_based_on_unicode_block_enabled_;
    bool is_scripted_speech_recognition_enabled_;
    bool is_scripted_speech_synthesis_enabled_;
    bool is_scroll_anchor_priority_candidate_subtree_enabled_;
    bool is_scroll_anchor_serialization_use_parent_for_text_node_enabled_;
    bool is_scrollbar_color_enabled_;
    bool is_scrollbar_gutter_bug_fix_enabled_;
    bool is_scrollbar_width_enabled_;
    bool is_scroll_into_view_nearest_enabled_;
    bool is_scroll_into_view_root_frame_viewport_bug_fix_enabled_;
    bool is_scroll_timeline_current_time_enabled_;
    bool is_scroll_timeline_named_range_scroll_enabled_;
    bool is_scroll_top_left_interop_enabled_;
    bool is_scroll_to_text_fragment_unique_fragments_enabled_;
    bool is_search_text_highlight_pseudo_enabled_;
    bool is_secure_payment_confirmation_enabled_;
    bool is_secure_payment_confirmation_availability_api_enabled_;
    bool is_secure_payment_confirmation_capabilities_enabled_;
    bool is_secure_payment_confirmation_debug_enabled_;
    bool is_secure_payment_confirmation_opt_out_enabled_;
    bool is_select_audio_output_enabled_;
    bool is_selectedcontentelement_attribute_enabled_;
    bool is_selectedcontent_multiple_enabled_;
    bool is_selectedcontent_spec_enabled_;
    bool is_selection_and_focused_visible_position_match_enabled_;
    bool is_selection_collapsed_direction_none_enabled_;
    bool is_selection_focus_affinity_enabled_;
    bool is_selection_handle_with_bottom_clipped_enabled_;
    bool is_selection_remove_range_not_found_error_enabled_;
    bool is_selection_set_base_and_extent_non_null_node_enabled_;
    bool is_selection_to_string_skips_user_select_none_enabled_;
    bool is_selection_update_only_after_autoscroll_enabled_;
    bool is_selection_update_to_initial_selection_in_listify_enabled_;
    bool is_selective_clipboard_format_read_enabled_;
    bool is_selective_permissions_intervention_enabled_;
    bool is_select_remove_overflow_hidden_enabled_;
    bool is_send_beacon_throw_for_blob_with_non_simple_type_enabled_;
    bool is_send_slot_change_signal_after_node_inserted_enabled_;
    bool is_sensor_extra_classes_enabled_;
    bool is_separate_defer_module_script_tasks_enabled_;
    bool is_serial_enabled_;
    bool is_serialize_view_transition_state_in_spa_enabled_;
    bool is_serial_port_connected_enabled_;
    bool is_service_worker_background_sync_in_dedicated_worker_enabled_;
    bool is_service_worker_client_lifecycle_state_enabled_;
    bool is_service_worker_in_dedicated_worker_enabled_;
    bool is_service_worker_static_router_timing_info_enabled_;
    bool is_set_default_drop_effect_enabled_;
    bool is_set_html_can_run_scripts_enabled_;
    bool is_set_sequential_focus_starting_point_enabled_;
    bool is_shadow_contour_follows_border_enabled_;
    bool is_shadow_root_adopted_style_sheet_enabled_;
    bool is_shadow_root_reference_target_enabled_;
    bool is_shadow_root_reference_target_aria_owns_enabled_;
    bool is_shared_array_buffer_enabled_;
    bool is_shared_array_buffer_unrestricted_access_allowed_enabled_;
    bool is_shared_storage_api_enabled_;
    bool is_shared_storage_web_locks_enabled_;
    bool is_shared_worker_enabled_;
    bool is_shared_worker_extended_lifetime_enabled_;
    bool is_side_relative_background_position_enabled_;
    bool is_signature_based_inline_integrity_enabled_;
    bool is_single_axis_scroll_containers_enabled_;
    bool is_skip_ad_enabled_;
    bool is_skip_callbacks_when_dev_tools_not_open_enabled_;
    bool is_skip_event_capture_enabled_;
    bool is_skip_non_editable_in_atomic_move_enabled_;
    bool is_skip_oof_item_for_break_candidate_enabled_;
    bool is_skip_paragraph_split_for_inline_insert_html_enabled_;
    bool is_skip_pseudo_only_lines_in_line_navigation_enabled_;
    bool is_skip_touch_event_filter_enabled_;
    bool is_skip_unselectable_content_in_serialization_enabled_;
    bool is_skip_unselectable_elements_in_paragraph_boundary_enabled_;
    bool is_smaller_viewport_units_enabled_;
    bool is_smart_card_enabled_;
    bool is_smart_zoom_enabled_;
    bool is_snapshot_scroll_timelines_post_layout_enabled_;
    bool is_soft_navigation_detection_enabled_;
    bool is_soft_navigation_detection_include_replace_state_enabled_;
    bool is_soft_navigation_heuristics_enabled_;
    bool is_sorted_layout_shift_sources_by_impact_area_enabled_;
    bool is_source_specific_multicast_in_direct_sockets_enabled_;
    bool is_spat_nav_uses_cursor_inheritance_enabled_;
    bool is_speaker_selection_enabled_;
    bool is_speculation_measurement_enabled_;
    bool is_spell_check_custom_dictionary_api_enabled_;
    bool is_split_text_not_cleanup_dummy_spans_enabled_;
    bool is_split_view_link_open_enabled_;
    bool is_srcset_selection_matches_image_set_enabled_;
    bool is_stable_blink_features_enabled_;
    bool is_stacking_context_is_not_stacked_enabled_;
    bool is_standardized_browser_zoom_enabled_;
    bool is_standardized_browser_zoom_opt_out_enabled_;
    bool is_sticky_position_has_overflow_per_axis_enabled_;
    bool is_sticky_user_activation_across_same_origin_navigation_enabled_;
    bool is_storage_buckets_enabled_;
    bool is_storage_buckets_durability_enabled_;
    bool is_storage_buckets_locks_enabled_;
    bool is_streaming_sanitizer_enabled_;
    bool is_strict_mime_types_for_workers_enabled_;
    bool is_stylus_handwriting_enabled_;
    bool is_sub_apps_enabled_;
    bool is_suppress_pointer_stream_after_drag_enabled_;
    bool is_svg_anchor_element_attributes_enabled_;
    bool is_svg_anchor_element_download_attribute_enabled_;
    bool is_svg_animate_motion_discrete_calc_mode_enabled_;
    bool is_svg_avoid_resetting_filter_quality_for_tiled_pattern_enabled_;
    bool is_svg_embedded_as_replaced_element_enabled_;
    bool is_svg_enable_text_decoration_css_styling_enabled_;
    bool is_svg_fall_back_to_container_size_enabled_;
    bool is_svg_fe_image_skip_hidden_container_viewport_dependence_enabled_;
    bool is_svg_filter_paints_for_hidden_content_enabled_;
    bool is_svg_filter_user_space_viewport_for_svg_enabled_;
    bool is_svg_ignore_negative_ellipse_radii_enabled_;
    bool is_svg_inline_root_pixel_snapping_scale_adjustment_enabled_;
    bool is_svg_length_list_clear_on_parsing_failure_enabled_;
    bool is_svg_length_resolve_unparsed_value_enabled_;
    bool is_svg_number_list_clear_on_parsing_failure_enabled_;
    bool is_svg_partition_svg_document_resources_in_memory_cache_enabled_;
    bool is_svg_path_length_css_property_enabled_;
    bool is_svg_point_list_clear_on_parsing_failure_enabled_;
    bool is_svg_script_element_async_attribute_enabled_;
    bool is_svg_sizing_with_preserve_aspect_ratio_none_enabled_;
    bool is_svg_smil_clock_value_validation_enabled_;
    bool is_svg_text_path_path_attribute_enabled_;
    bool is_svg_transform_on_nested_svg_element_enabled_;
    bool is_synthesized_keyboard_events_for_accessibility_actions_enabled_;
    bool is_synthetic_mouse_hover_over_inactive_page_enabled_;
    bool is_system_default_accent_colors_enabled_;
    bool is_system_fallback_emoji_vs_support_enabled_;
    bool is_system_wake_lock_enabled_;
    bool is_table_border_color_no_implicit_border_enabled_;
    bool is_table_default_border_color_current_color_enabled_;
    bool is_table_is_auto_fixed_layout_enabled_;
    bool is_tab_size_ancestor_enabled_;
    bool is_tab_size_with_spacing_enabled_;
    bool is_target_in_shadow_determined_before_listener_enabled_;
    bool is_test_blink_feature_default_enabled_;
    bool is_test_feature_enabled_;
    bool is_test_feature_dependent_enabled_;
    bool is_test_feature_for_browser_process_read_write_access_origin_trial_enabled_;
    bool is_test_feature_implied_enabled_;
    bool is_test_feature_protected_enabled_;
    bool is_test_feature_protected_dependent_enabled_;
    bool is_test_feature_protected_implied_enabled_;
    bool is_test_feature_stable_enabled_;
    bool is_text_area_scroll_top_preview_enabled_;
    bool is_text_detector_enabled_;
    bool is_text_emphasis_letter_spacing_enabled_;
    bool is_text_emphasis_position_auto_enabled_;
    bool is_text_emphasis_punctuation_exceptions_enabled_;
    bool is_text_emphasis_with_ruby_enabled_;
    bool is_text_fragment_api_enabled_;
    bool is_text_fragment_identifiers_enabled_;
    bool is_text_fragment_tap_opens_context_menu_enabled_;
    bool is_text_metrics_baselines_enabled_;
    bool is_text_overflow_clip_with_selection_enabled_;
    bool is_text_overflow_string_enabled_;
    bool is_text_scale_meta_tag_enabled_;
    bool is_text_spacing_trim_fallback_enabled_;
    bool is_text_spacing_trim_fallback_2_enabled_;
    bool is_text_spacing_trim_fallback_chws_enabled_;
    bool is_text_spacing_trim_yu_gothic_ui_enabled_;
    bool is_throttled_history_api_throws_security_error_enabled_;
    bool is_timeline_trigger_enabled_;
    bool is_timer_throttling_for_background_tabs_enabled_;
    bool is_timestamp_based_cls_tracking_enabled_;
    bool is_time_zone_change_event_enabled_;
    bool is_topics_api_enabled_;
    bool is_topics_document_api_enabled_;
    bool is_topics_img_api_enabled_;
    bool is_touch_drag_and_context_menu_enabled_;
    bool is_touch_drag_and_drop_enabled_;
    bool is_touch_drag_on_short_press_enabled_;
    bool is_touch_event_feature_detection_enabled_;
    bool is_touch_text_editing_redesign_enabled_;
    bool is_transferable_rtc_data_channel_enabled_;
    bool is_transition_navigation_quiet_skip_enabled_;
    bool is_translate_service_enabled_;
    bool is_translation_api_enabled_;
    bool is_translation_api_for_workers_enabled_;
    bool is_traverse_flat_tree_to_handle_slots_enabled_;
    bool is_treat_mhtml_initial_document_loads_as_cross_document_enabled_;
    bool is_trusted_types_create_parser_options_enabled_;
    bool is_trusted_types_from_literal_enabled_;
    bool is_trusted_types_html_enabled_;
    bool is_trusted_types_use_code_like_enabled_;
    bool is_two_phase_view_transition_enabled_;
    bool is_unclosed_form_control_is_invalid_enabled_;
    bool is_unexposed_task_ids_enabled_;
    bool is_unprefixed_speech_recognition_enabled_;
    bool is_unrestricted_measure_user_agent_specific_memory_enabled_;
    bool is_unrestricted_shared_array_buffer_enabled_;
    bool is_unrestricted_usb_enabled_;
    bool is_update_complex_safa_area_constraints_enabled_;
    bool is_update_selection_on_node_insertion_enabled_;
    bool is_update_trival_text_after_fragment_creation_from_text_enabled_;
    bool is_url_pattern_compare_component_enabled_;
    bool is_url_pattern_generate_enabled_;
    bool is_url_search_params_has_and_delete_multiple_args_enabled_;
    bool is_use_begin_frame_presentation_feedback_enabled_;
    bool is_use_bounded_selection_offsets_in_edit_context_delete_operations_enabled_;
    bool is_use_largest_painted_image_for_lcp_candidate_enabled_;
    bool is_use_low_quality_interpolation_enabled_;
    bool is_use_original_dom_offsets_for_offset_map_enabled_;
    bool is_use_position_for_point_in_flexible_box_with_single_child_element_enabled_;
    bool is_use_position_if_is_visually_equivalent_candidate_enabled_;
    bool is_user_action_pseudos_stop_at_top_layer_enabled_;
    bool is_user_defined_entry_point_timing_enabled_;
    bool is_user_media_element_enabled_;
    bool is_use_selection_in_dom_tree_anchor_in_extend_selection_enabled_;
    bool is_use_shadow_host_style_check_editable_enabled_;
    bool is_use_undo_step_element_dispatch_before_input_enabled_;
    bool is_v8_idle_tasks_enabled_;
    bool is_video_auto_fullscreen_enabled_;
    bool is_video_frame_metadata_background_blur_enabled_;
    bool is_video_frame_metadata_rtp_timestamp_enabled_;
    bool is_video_fullscreen_orientation_lock_enabled_;
    bool is_video_rotate_to_fullscreen_enabled_;
    bool is_video_track_generator_enabled_;
    bool is_video_track_generator_in_window_enabled_;
    bool is_video_track_generator_in_worker_enabled_;
    bool is_viewport_height_client_hint_header_enabled_;
    bool is_viewport_segments_enabled_;
    bool is_view_transition_async_finished_enabled_;
    bool is_view_transition_delay_unpause_on_teardown_enabled_;
    bool is_view_transition_hoist_backdrop_filter_effect_enabled_;
    bool is_view_transition_long_callback_timeout_for_testing_enabled_;
    bool is_view_transition_update_lifecycle_before_ready_enabled_;
    bool is_view_transition_wait_until_enabled_;
    bool is_visibility_collapse_column_enabled_;
    bool is_visual_rect_mapping_fix_for_expansion_enabled_;
    bool is_wake_lock_enabled_;
    bool is_warn_on_content_visibility_render_access_enabled_;
    bool is_web_app_installation_enabled_;
    bool is_web_app_launch_queue_enabled_;
    bool is_web_app_scope_extensions_enabled_;
    bool is_web_app_scope_system_accent_color_enabled_;
    bool is_web_app_tab_strip_enabled_;
    bool is_web_app_tab_strip_customizations_enabled_;
    bool is_web_app_translations_enabled_;
    bool is_web_assembly_custom_descriptors_v_2_enabled_;
    bool is_web_assembly_js_promise_integration_enabled_;
    bool is_web_audio_bypass_output_buffering_enabled_;
    bool is_web_audio_bypass_output_buffering_opt_out_enabled_;
    bool is_web_audio_configurable_render_quantum_enabled_;
    bool is_web_auth_enabled_;
    bool is_web_auth_authenticator_attachment_enabled_;
    bool is_web_authentication_ambient_enabled_;
    bool is_web_authentication_attestation_formats_enabled_;
    bool is_web_authentication_immediate_get_enabled_;
    bool is_web_authentication_remote_desktop_support_enabled_;
    bool is_web_authentication_supplemental_pub_keys_enabled_;
    bool is_web_bluetooth_enabled_;
    bool is_web_bluetooth_get_devices_enabled_;
    bool is_web_bluetooth_scanning_enabled_;
    bool is_web_bluetooth_watch_advertisements_enabled_;
    bool is_webcodecs_video_encoder_buffers_enabled_;
    bool is_web_crypto_pqc_enabled_;
    bool is_web_font_resize_lcp_enabled_;
    bool is_webgl_developer_extensions_enabled_;
    bool is_webgl_draft_extensions_enabled_;
    bool is_webgl_drawing_buffer_storage_enabled_;
    bool is_webgl_on_webgpu_enabled_;
    bool is_webgpu_compatibility_mode_enabled_;
    bool is_webgpu_developer_features_enabled_;
    bool is_webgpu_experimental_features_enabled_;
    bool is_webgpu_immediates_feature_enabled_;
    bool is_webgpu_map_sync_on_workers_enabled_;
    bool is_webgpu_multithread_dawn_wire_on_workers_enabled_;
    bool is_webgpu_transient_attachment_enabled_;
    bool is_web_hid_enabled_;
    bool is_web_hid_on_service_workers_enabled_;
    bool is_web_identity_digital_credentials_enabled_;
    bool is_web_identity_digital_credentials_creation_enabled_;
    bool is_web_idl_big_int_uses_to_big_int_enabled_;
    bool is_web_mcp_enabled_;
    bool is_web_mcp_declarative_file_input_enabled_;
    bool is_web_mcp_form_associated_custom_elements_enabled_;
    bool is_web_mcp_testing_enabled_;
    bool is_web_nfc_enabled_;
    bool is_web_otp_enabled_;
    bool is_web_otp_assertion_feature_policy_enabled_;
    bool is_web_preferences_enabled_;
    bool is_web_printing_enabled_;
    bool is_web_share_enabled_;
    bool is_websocket_stream_enabled_;
    bool is_websocket_stream_standard_binary_chunk_type_enabled_;
    bool is_web_speech_recognition_context_enabled_;
    bool is_web_transport_application_protocol_enabled_;
    bool is_web_transport_congestion_control_enabled_;
    bool is_web_transport_custom_certificates_enabled_;
    bool is_web_transport_send_group_enabled_;
    bool is_web_transport_stats_enabled_;
    bool is_web_ui_bundled_code_cache_async_fetch_enabled_;
    bool is_web_usb_enabled_;
    bool is_web_usb_on_dedicated_workers_enabled_;
    bool is_web_usb_on_service_workers_enabled_;
    bool is_web_vtt_regions_enabled_;
    bool is_web_xr_enabled_;
    bool is_web_xr_enabled_features_enabled_;
    bool is_web_xr_frame_rate_enabled_;
    bool is_web_xr_front_facing_enabled_;
    bool is_web_xr_gpu_binding_enabled_;
    bool is_web_xr_hit_test_entity_types_enabled_;
    bool is_web_xr_image_tracking_enabled_;
    bool is_web_xr_layers_enabled_;
    bool is_web_xr_layers_common_enabled_;
    bool is_web_xr_mesh_detection_enabled_;
    bool is_web_xr_plane_detection_enabled_;
    bool is_web_xr_pose_motion_data_enabled_;
    bool is_web_xr_spec_parity_enabled_;
    bool is_web_xr_visibility_mask_enabled_;
    bool is_window_default_status_enabled_;
    bool is_word_skip_spaces_punctuation_fix_enabled_;
    bool is_word_spacing_white_space_pre_enabled_;
    bool is_xml_no_external_entities_enabled_;
    bool is_xml_parsing_rust_enabled_;
    bool is_xml_rust_for_non_xslt_enabled_;
    bool is_xml_serializer_consistent_default_ns_decl_matching_enabled_;
    bool is_xpath_shadow_dom_support_enabled_;
    bool is_xslt_enabled_;
    bool is_xslt_special_trial_enabled_;
  };

  // Simple getter methods for protected memory values that ensure they are
  // properly initialized before first access.
  static bool get_is_mojo_js_enabled_();
  static bool get_is_mojo_js_test_enabled_();
  static bool get_is_protected_origin_trials_sample_api_enabled_();
  static bool get_is_protected_origin_trials_sample_api_dependent_enabled_();
  static bool get_is_protected_origin_trials_sample_api_implied_enabled_();
  static bool get_is_test_feature_protected_enabled_();
  static bool get_is_test_feature_protected_dependent_enabled_();
  static bool get_is_test_feature_protected_implied_enabled_();

  static bool AboutBlankPageRespectsDarkModeOnUserActionEnabled() {
    return is_about_blank_page_respects_dark_mode_on_user_action_enabled_;
  }

  static bool AboutBlankPageRespectsDarkModeOnUserActionEnabled(const FeatureContext*) { return AboutBlankPageRespectsDarkModeOnUserActionEnabled(); }

  static bool Accelerated2dCanvasEnabled() {
    return is_accelerated_2d_canvas_enabled_;
  }

  static bool Accelerated2dCanvasEnabled(const FeatureContext*) { return Accelerated2dCanvasEnabled(); }

  static bool AcceleratedSmallCanvasesEnabled() {
    return is_accelerated_small_canvases_enabled_;
  }

  static bool AcceleratedSmallCanvasesEnabled(const FeatureContext*) { return AcceleratedSmallCanvasesEnabled(); }

  static bool AccessibilityAriaVirtualContentEnabled() {
    return is_accessibility_aria_virtual_content_enabled_;
  }

  static bool AccessibilityAriaVirtualContentEnabled(const FeatureContext*) { return AccessibilityAriaVirtualContentEnabled(); }

  static bool AccessibilityCustomElementRoleNoneEnabled() {
    return is_accessibility_custom_element_role_none_enabled_;
  }

  static bool AccessibilityCustomElementRoleNoneEnabled(const FeatureContext*) { return AccessibilityCustomElementRoleNoneEnabled(); }

  static bool AccessibilityExposeDisplayNoneEnabled() {
    return is_accessibility_expose_display_none_enabled_;
  }

  static bool AccessibilityExposeDisplayNoneEnabled(const FeatureContext*) { return AccessibilityExposeDisplayNoneEnabled(); }

  static bool AccessibilityImplicitActionsEnabled() {
    return is_accessibility_implicit_actions_enabled_;
  }

  static bool AccessibilityImplicitActionsEnabled(const FeatureContext*) { return AccessibilityImplicitActionsEnabled(); }

  static bool AccessibilityMinRoleTabbableEnabled() {
    return is_accessibility_min_role_tabbable_enabled_;
  }

  static bool AccessibilityMinRoleTabbableEnabled(const FeatureContext*) { return AccessibilityMinRoleTabbableEnabled(); }

  static bool AccessibilityOSLevelBoldTextEnabled() {
    return is_accessibility_os_level_bold_text_enabled_;
  }

  static bool AccessibilityOSLevelBoldTextEnabled(const FeatureContext*) { return AccessibilityOSLevelBoldTextEnabled(); }

  static bool AccessibilityProhibitedNamesEnabled() {
    return is_accessibility_prohibited_names_enabled_;
  }

  static bool AccessibilityProhibitedNamesEnabled(const FeatureContext*) { return AccessibilityProhibitedNamesEnabled(); }

  static bool AccessibilitySerializationSizeMetricsEnabled() {
    return is_accessibility_serialization_size_metrics_enabled_;
  }

  static bool AccessibilitySerializationSizeMetricsEnabled(const FeatureContext*) { return AccessibilitySerializationSizeMetricsEnabled(); }

  static bool AccessibilityUseAXPositionForDocumentMarkersEnabled() {
    return is_accessibility_use_ax_position_for_document_markers_enabled_;
  }

  static bool AccessibilityUseAXPositionForDocumentMarkersEnabled(const FeatureContext*) { return AccessibilityUseAXPositionForDocumentMarkersEnabled(); }

  static bool AccessKeyLabelEnabled() {
    return is_access_key_label_enabled_;
  }

  static bool AccessKeyLabelEnabled(const FeatureContext*) { return AccessKeyLabelEnabled(); }

  static bool AddressSpaceEnabled() {
    if (CorsRFC1918Enabled())
      return true;
    return is_address_space_enabled_;
  }

  static bool AddressSpaceEnabled(const FeatureContext*) { return AddressSpaceEnabled(); }

  static bool AdjustDOMOffsetToLayoutOffsetForSecureTextEnabled() {
    return is_adjust_dom_offset_to_layout_offset_for_secure_text_enabled_;
  }

  static bool AdjustDOMOffsetToLayoutOffsetForSecureTextEnabled(const FeatureContext*) { return AdjustDOMOffsetToLayoutOffsetForSecureTextEnabled(); }

  static bool AdjustEndOfNextParagraphIfMovedParagraphIsUpdatedEnabled() {
    return is_adjust_end_of_next_paragraph_if_moved_paragraph_is_updated_enabled_;
  }

  static bool AdjustEndOfNextParagraphIfMovedParagraphIsUpdatedEnabled(const FeatureContext*) { return AdjustEndOfNextParagraphIfMovedParagraphIsUpdatedEnabled(); }

  static bool AdTaggingEnabled() {
    return is_ad_tagging_enabled_;
  }

  static bool AdTaggingEnabled(const FeatureContext*) { return AdTaggingEnabled(); }

  static bool AIClassifierAPIEnabled() {
    return is_ai_classifier_api_enabled_;
  }

  static bool AIClassifierAPIEnabled(const FeatureContext*) { return AIClassifierAPIEnabled(); }

  static bool AIPageContentAnchoredOffscreenNonActionabilityEnabled() {
    return is_ai_page_content_anchored_offscreen_non_actionability_enabled_;
  }

  static bool AIPageContentAnchoredOffscreenNonActionabilityEnabled(const FeatureContext*) { return AIPageContentAnchoredOffscreenNonActionabilityEnabled(); }

  static bool AIPageContentBuildOnLoadForTestingEnabled() {
    return is_ai_page_content_build_on_load_for_testing_enabled_;
  }

  static bool AIPageContentBuildOnLoadForTestingEnabled(const FeatureContext*) { return AIPageContentBuildOnLoadForTestingEnabled(); }

  static bool AIPageContentCheckGeometryEnabled() {
    return is_ai_page_content_check_geometry_enabled_;
  }

  static bool AIPageContentCheckGeometryEnabled(const FeatureContext*) { return AIPageContentCheckGeometryEnabled(); }

  static bool AIPageContentConvertNodeTextToUtf8Enabled() {
    return is_ai_page_content_convert_node_text_to_utf_8_enabled_;
  }

  static bool AIPageContentConvertNodeTextToUtf8Enabled(const FeatureContext*) { return AIPageContentConvertNodeTextToUtf8Enabled(); }

  static bool AIPageContentElementCSSRedactionEnabled() {
    return is_ai_page_content_element_css_redaction_enabled_;
  }

  static bool AIPageContentElementCSSRedactionEnabled(const FeatureContext*) { return AIPageContentElementCSSRedactionEnabled(); }

  static bool AIPageContentIncludeSVGSubtreeEnabled() {
    return is_ai_page_content_include_svg_subtree_enabled_;
  }

  static bool AIPageContentIncludeSVGSubtreeEnabled(const FeatureContext*) { return AIPageContentIncludeSVGSubtreeEnabled(); }

  static bool AIPageContentOuterBoxMapToAncestorSpaceEnabled() {
    return is_ai_page_content_outer_box_map_to_ancestor_space_enabled_;
  }

  static bool AIPageContentOuterBoxMapToAncestorSpaceEnabled(const FeatureContext*) { return AIPageContentOuterBoxMapToAncestorSpaceEnabled(); }

  static bool AIPageContentPaidContentAnnotationEnabled() {
    return is_ai_page_content_paid_content_annotation_enabled_;
  }

  static bool AIPageContentPaidContentAnnotationEnabled(const FeatureContext*) { return AIPageContentPaidContentAnnotationEnabled(); }

  static bool AIPageContentVisualViewportClampEnabled() {
    if (AIPageContentBuildOnLoadForTestingEnabled())
      return true;
    return is_ai_page_content_visual_viewport_clamp_enabled_;
  }

  static bool AIPageContentVisualViewportClampEnabled(const FeatureContext*) { return AIPageContentVisualViewportClampEnabled(); }

  static bool AIPromptAPIEnabled() {
    return is_ai_prompt_api_enabled_;
  }

  static bool AIPromptAPIEnabled(const FeatureContext*) { return AIPromptAPIEnabled(); }

  static bool AIPromptAPIForExtensionEnabled() {
    return is_ai_prompt_api_for_extension_enabled_;
  }

  static bool AIPromptAPIForExtensionEnabled(const FeatureContext*) { return AIPromptAPIForExtensionEnabled(); }

  static bool AIPromptAPIForWorkersEnabled() {
    return is_ai_prompt_api_for_workers_enabled_;
  }

  static bool AIPromptAPIForWorkersEnabled(const FeatureContext*) { return AIPromptAPIForWorkersEnabled(); }

  static bool AIPromptAPILegacyIdentifiersEnabled() {
    return is_ai_prompt_api_legacy_identifiers_enabled_;
  }

  static bool AIPromptAPILegacyIdentifiersEnabled(const FeatureContext*) { return AIPromptAPILegacyIdentifiersEnabled(); }

  static bool AIPromptAPIMultimodalInputEnabled() {
    return is_ai_prompt_api_multimodal_input_enabled_;
  }

  static bool AIPromptAPIMultimodalInputEnabled(const FeatureContext*) { return AIPromptAPIMultimodalInputEnabled(); }

  static bool AIPromptAPIStructuredOutputEnabled() {
    return is_ai_prompt_api_structured_output_enabled_;
  }

  static bool AIPromptAPIStructuredOutputEnabled(const FeatureContext*) { return AIPromptAPIStructuredOutputEnabled(); }

  static bool AIPromptAPIToolUseEnabled() {
    return is_ai_prompt_api_tool_use_enabled_;
  }

  static bool AIPromptAPIToolUseEnabled(const FeatureContext*) { return AIPromptAPIToolUseEnabled(); }

  static bool AIRewriterAPIForWorkersEnabled() {
    return is_ai_rewriter_api_for_workers_enabled_;
  }

  static bool AIRewriterAPIForWorkersEnabled(const FeatureContext*) { return AIRewriterAPIForWorkersEnabled(); }

  static bool AISummarizationAPIEnabled() {
    return is_ai_summarization_api_enabled_;
  }

  static bool AISummarizationAPIEnabled(const FeatureContext*) { return AISummarizationAPIEnabled(); }

  static bool AISummarizationAPIForWorkersEnabled() {
    return is_ai_summarization_api_for_workers_enabled_;
  }

  static bool AISummarizationAPIForWorkersEnabled(const FeatureContext*) { return AISummarizationAPIForWorkersEnabled(); }

  static bool AISummarizationPerformancePreferenceEnabled() {
    return is_ai_summarization_performance_preference_enabled_;
  }

  static bool AISummarizationPerformancePreferenceEnabled(const FeatureContext*) { return AISummarizationPerformancePreferenceEnabled(); }

  static bool AIWriterAPIForWorkersEnabled() {
    return is_ai_writer_api_for_workers_enabled_;
  }

  static bool AIWriterAPIForWorkersEnabled(const FeatureContext*) { return AIWriterAPIForWorkersEnabled(); }

  static bool AlignZoomToCenterEnabled() {
    return is_align_zoom_to_center_enabled_;
  }

  static bool AlignZoomToCenterEnabled(const FeatureContext*) { return AlignZoomToCenterEnabled(); }

  static bool AllImagesPaintedSentToElementTimingEnabled() {
    return is_all_images_painted_sent_to_element_timing_enabled_;
  }

  static bool AllImagesPaintedSentToElementTimingEnabled(const FeatureContext*) { return AllImagesPaintedSentToElementTimingEnabled(); }

  static bool AllowContentInitiatedDataUrlNavigationsEnabled() {
    return is_allow_content_initiated_data_url_navigations_enabled_;
  }

  static bool AllowContentInitiatedDataUrlNavigationsEnabled(const FeatureContext*) { return AllowContentInitiatedDataUrlNavigationsEnabled(); }

  static bool AllowPreloadingWithCSPMetaTagEnabled() {
    return is_allow_preloading_with_csp_meta_tag_enabled_;
  }

  static bool AllowPreloadingWithCSPMetaTagEnabled(const FeatureContext*) { return AllowPreloadingWithCSPMetaTagEnabled(); }

  static bool AllowSameSiteNoneCookiesInSandboxEnabled() {
    return is_allow_same_site_none_cookies_in_sandbox_enabled_;
  }

  static bool AllowSameSiteNoneCookiesInSandboxEnabled(const FeatureContext*) { return AllowSameSiteNoneCookiesInSandboxEnabled(); }

  static bool AllowSkippingEditingBoundaryToMergeEndEnabled() {
    return is_allow_skipping_editing_boundary_to_merge_end_enabled_;
  }

  static bool AllowSkippingEditingBoundaryToMergeEndEnabled(const FeatureContext*) { return AllowSkippingEditingBoundaryToMergeEndEnabled(); }

  static bool AllowSvgUseToReferenceExternalDocumentRootEnabled() {
    return is_allow_svg_use_to_reference_external_document_root_enabled_;
  }

  static bool AllowSvgUseToReferenceExternalDocumentRootEnabled(const FeatureContext*) { return AllowSvgUseToReferenceExternalDocumentRootEnabled(); }

  static bool AllowSyntheticTimingForCanvasCaptureEnabled() {
    return is_allow_synthetic_timing_for_canvas_capture_enabled_;
  }

  static bool AllowSyntheticTimingForCanvasCaptureEnabled(const FeatureContext*) { return AllowSyntheticTimingForCanvasCaptureEnabled(); }

  static bool AllowURNsInIframesEnabled() {
    return is_allow_ur_ns_in_iframes_enabled_;
  }

  static bool AllowURNsInIframesEnabled(const FeatureContext*) { return AllowURNsInIframesEnabled(); }

  static bool AncestorOriginsStoredOnDocumentEnabled() {
    return is_ancestor_origins_stored_on_document_enabled_;
  }

  static bool AncestorOriginsStoredOnDocumentEnabled(const FeatureContext*) { return AncestorOriginsStoredOnDocumentEnabled(); }

  static bool AncestorRevealingNewSpecEnabled() {
    return is_ancestor_revealing_new_spec_enabled_;
  }

  static bool AncestorRevealingNewSpecEnabled(const FeatureContext*) { return AncestorRevealingNewSpecEnabled(); }

  static bool AnchorFocusRingFixEnabled() {
    return is_anchor_focus_ring_fix_enabled_;
  }

  static bool AnchorFocusRingFixEnabled(const FeatureContext*) { return AnchorFocusRingFixEnabled(); }

  static bool AnchorPositionAdjustmentWithoutOverflowEnabled() {
    return is_anchor_position_adjustment_without_overflow_enabled_;
  }

  static bool AnchorPositionAdjustmentWithoutOverflowEnabled(const FeatureContext*) { return AnchorPositionAdjustmentWithoutOverflowEnabled(); }

  static bool AndroidDownloadableFontsMatchingEnabled() {
    return is_android_downloadable_fonts_matching_enabled_;
  }

  static bool AndroidDownloadableFontsMatchingEnabled(const FeatureContext*) { return AndroidDownloadableFontsMatchingEnabled(); }

  static bool AnimationProgressAPIEnabled() {
    return is_animation_progress_api_enabled_;
  }

  static bool AnimationProgressAPIEnabled(const FeatureContext*) { return AnimationProgressAPIEnabled(); }

  static bool AnimationTriggerEnabled() {
    if (EventTriggerEnabled())
      return true;
    if (TimelineTriggerEnabled())
      return true;
    return is_animation_trigger_enabled_;
  }

  static bool AnimationTriggerEnabled(const FeatureContext*) { return AnimationTriggerEnabled(); }

  static bool AnimationWorkletEnabled() {
    return is_animation_worklet_enabled_;
  }

  static bool AnimationWorkletEnabled(const FeatureContext*) { return AnimationWorkletEnabled(); }

  static bool AnonymousIframeEnabled() {
    return is_anonymous_iframe_enabled_;
  }

  static bool AnonymousIframeEnabled(const FeatureContext*) { return AnonymousIframeEnabled(); }

  static bool AOMAriaRelationshipPropertiesEnabled() {
    return is_aom_aria_relationship_properties_enabled_;
  }

  static bool AOMAriaRelationshipPropertiesEnabled(const FeatureContext*) { return AOMAriaRelationshipPropertiesEnabled(); }

  static bool AOMAriaRelationshipPropertiesAriaOwnsEnabled() {
    if (!AOMAriaRelationshipPropertiesEnabled())
      return false;
    return is_aom_aria_relationship_properties_aria_owns_enabled_;
  }

  static bool AOMAriaRelationshipPropertiesAriaOwnsEnabled(const FeatureContext*) { return AOMAriaRelationshipPropertiesAriaOwnsEnabled(); }

  static bool AppearanceBaseEnabled() {
    return is_appearance_base_enabled_;
  }

  static bool AppearanceBaseEnabled(const FeatureContext*) { return AppearanceBaseEnabled(); }

  static bool ApproximateGeolocationPermissionEnabled() {
    return is_approximate_geolocation_permission_enabled_;
  }

  static bool ApproximateGeolocationPermissionEnabled(const FeatureContext*) { return ApproximateGeolocationPermissionEnabled(); }

  static bool ApproximateGeolocationPermissionAPIEnabled() {
    return is_approximate_geolocation_permission_api_enabled_;
  }

  static bool ApproximateGeolocationPermissionAPIEnabled(const FeatureContext*) { return ApproximateGeolocationPermissionAPIEnabled(); }

  static bool ApproximateGeolocationWebVisibleAPIEnabled() {
    if (!ApproximateGeolocationPermissionEnabled())
      return false;
    return is_approximate_geolocation_web_visible_api_enabled_;
  }

  static bool ApproximateGeolocationWebVisibleAPIEnabled(const FeatureContext*) { return ApproximateGeolocationWebVisibleAPIEnabled(); }

  static bool AriaActionsEnabled() {
    return is_aria_actions_enabled_;
  }

  static bool AriaActionsEnabled(const FeatureContext*) { return AriaActionsEnabled(); }

  static bool AriaNotifyEnabled() {
    if (AriaNotifyV2Enabled())
      return true;
    return is_aria_notify_enabled_;
  }

  static bool AriaNotifyEnabled(const FeatureContext*) { return AriaNotifyEnabled(); }

  static bool AriaNotifyV2Enabled() {
    return is_aria_notify_v_2_enabled_;
  }

  static bool AriaNotifyV2Enabled(const FeatureContext*) { return AriaNotifyV2Enabled(); }

  static bool AriaRowColIndexTextEnabled() {
    return is_aria_row_col_index_text_enabled_;
  }

  static bool AriaRowColIndexTextEnabled(const FeatureContext*) { return AriaRowColIndexTextEnabled(); }

  static bool AsyncSetCookieEnabled() {
    return is_async_set_cookie_enabled_;
  }

  static bool AsyncSetCookieEnabled(const FeatureContext*) { return AsyncSetCookieEnabled(); }

  static bool AttributionReportingEnabled() {
    return is_attribution_reporting_enabled_;
  }

  static bool AttributionReportingEnabled(const FeatureContext*) { return AttributionReportingEnabled(); }

  static bool AudioContextAsyncStateTransitionsEnabled() {
    return is_audio_context_async_state_transitions_enabled_;
  }

  static bool AudioContextAsyncStateTransitionsEnabled(const FeatureContext*) { return AudioContextAsyncStateTransitionsEnabled(); }

  static bool AudioContextPlaybackStatsEnabled() {
    return is_audio_context_playback_stats_enabled_;
  }

  static bool AudioContextPlaybackStatsEnabled(const FeatureContext*) { return AudioContextPlaybackStatsEnabled(); }

  static bool AudioContextSetSinkIdEnabled() {
    return is_audio_context_set_sink_id_enabled_;
  }

  static bool AudioContextSetSinkIdEnabled(const FeatureContext*) { return AudioContextSetSinkIdEnabled(); }

  static bool AudioOutputDevicesEnabled() {
    return is_audio_output_devices_enabled_;
  }

  static bool AudioOutputDevicesEnabled(const FeatureContext*) { return AudioOutputDevicesEnabled(); }

  static bool AudioVideoTracksEnabled() {
    return is_audio_video_tracks_enabled_;
  }

  static bool AudioVideoTracksEnabled(const FeatureContext*) { return AudioVideoTracksEnabled(); }

  static bool AuthenticatorPasswordsOnlyImmediateRequestsEnabled() {
    return is_authenticator_passwords_only_immediate_requests_enabled_;
  }

  static bool AuthenticatorPasswordsOnlyImmediateRequestsEnabled(const FeatureContext*) { return AuthenticatorPasswordsOnlyImmediateRequestsEnabled(); }

  static bool AuthorSpecifiedLayoutScrollSnapBehaviorEnabled() {
    return is_author_specified_layout_scroll_snap_behavior_enabled_;
  }

  static bool AuthorSpecifiedLayoutScrollSnapBehaviorEnabled(const FeatureContext*) { return AuthorSpecifiedLayoutScrollSnapBehaviorEnabled(); }

  static bool AutofillEnabled() {
    return is_autofill_enabled_;
  }

  static bool AutofillEnabled(const FeatureContext*) { return AutofillEnabled(); }

  static bool AutomationControlledEnabled() {
    return is_automation_controlled_enabled_;
  }

  static bool AutomationControlledEnabled(const FeatureContext*) { return AutomationControlledEnabled(); }

  static bool AutoPictureInPictureVideoHeuristicsEnabled() {
    return is_auto_picture_in_picture_video_heuristics_enabled_;
  }

  static bool AutoPictureInPictureVideoHeuristicsEnabled(const FeatureContext*) { return AutoPictureInPictureVideoHeuristicsEnabled(); }

  static bool AvoidForcedLayoutOnInvisibleDocumentCloseEnabled() {
    return is_avoid_forced_layout_on_invisible_document_close_enabled_;
  }

  static bool AvoidForcedLayoutOnInvisibleDocumentCloseEnabled(const FeatureContext*) { return AvoidForcedLayoutOnInvisibleDocumentCloseEnabled(); }

  static bool AvoidMergingStyledSpanWithSiblingsEnabled() {
    return is_avoid_merging_styled_span_with_siblings_enabled_;
  }

  static bool AvoidMergingStyledSpanWithSiblingsEnabled(const FeatureContext*) { return AvoidMergingStyledSpanWithSiblingsEnabled(); }

  static bool AvoidNormalizingVisiblePositionsWhenStartEqualsEndEnabled() {
    return is_avoid_normalizing_visible_positions_when_start_equals_end_enabled_;
  }

  static bool AvoidNormalizingVisiblePositionsWhenStartEqualsEndEnabled(const FeatureContext*) { return AvoidNormalizingVisiblePositionsWhenStartEqualsEndEnabled(); }

  static bool BackfaceVisibilityInteropEnabled() {
    return is_backface_visibility_interop_enabled_;
  }

  static bool BackfaceVisibilityInteropEnabled(const FeatureContext*) { return BackfaceVisibilityInteropEnabled(); }

  static bool BackForwardCacheEnabled() {
    return is_back_forward_cache_enabled_;
  }

  static bool BackForwardCacheEnabled(const FeatureContext*) { return BackForwardCacheEnabled(); }

  static bool BackForwardCacheRestorationPerformanceEntryEnabled() {
    return is_back_forward_cache_restoration_performance_entry_enabled_;
  }

  static bool BackForwardCacheRestorationPerformanceEntryEnabled(const FeatureContext*) { return BackForwardCacheRestorationPerformanceEntryEnabled(); }

  static bool BackForwardCacheUpdateNotRestoredReasonsNameEnabled() {
    return is_back_forward_cache_update_not_restored_reasons_name_enabled_;
  }

  static bool BackForwardCacheUpdateNotRestoredReasonsNameEnabled(const FeatureContext*) { return BackForwardCacheUpdateNotRestoredReasonsNameEnabled(); }

  static bool BackgroundClipTextDecorationEnabled() {
    return is_background_clip_text_decoration_enabled_;
  }

  static bool BackgroundClipTextDecorationEnabled(const FeatureContext*) { return BackgroundClipTextDecorationEnabled(); }

  static bool BackgroundFetchEnabled() {
    return is_background_fetch_enabled_;
  }

  static bool BackgroundFetchEnabled(const FeatureContext*) { return BackgroundFetchEnabled(); }

  static bool BarcodeDetectorEnabled() {
    return is_barcode_detector_enabled_;
  }

  static bool BarcodeDetectorEnabled(const FeatureContext*) { return BarcodeDetectorEnabled(); }

  static bool BaseAppearanceInlineSizingEnabled() {
    return is_base_appearance_inline_sizing_enabled_;
  }

  static bool BaseAppearanceInlineSizingEnabled(const FeatureContext*) { return BaseAppearanceInlineSizingEnabled(); }

  static bool BidiCaretAffinityEnabled() {
    return is_bidi_caret_affinity_enabled_;
  }

  static bool BidiCaretAffinityEnabled(const FeatureContext*) { return BidiCaretAffinityEnabled(); }

  static bool BlinkExtensionChromeOSEnabled() {
    return is_blink_extension_chrome_os_enabled_;
  }

  static bool BlinkExtensionChromeOSEnabled(const FeatureContext*);

  static bool BlinkExtensionChromeOSIsolatedWebAppSetShapeEnabled() {
    if (!BlinkExtensionChromeOSEnabled())
      return false;
    return is_blink_extension_chrome_os_isolated_web_app_set_shape_enabled_;
  }

  static bool BlinkExtensionChromeOSIsolatedWebAppSetShapeEnabled(const FeatureContext*);

  static bool BlinkExtensionChromeOSKioskEnabled() {
    if (!BlinkExtensionChromeOSEnabled())
      return false;
    return is_blink_extension_chrome_os_kiosk_enabled_;
  }

  static bool BlinkExtensionChromeOSKioskEnabled(const FeatureContext*);

  static bool BlinkExtensionWebViewEnabled() {
    return is_blink_extension_web_view_enabled_;
  }

  static bool BlinkExtensionWebViewEnabled(const FeatureContext*) { return BlinkExtensionWebViewEnabled(); }

  static bool BlinkExtensionWebViewMediaIntegrityEnabled() {
    return is_blink_extension_web_view_media_integrity_enabled_;
  }

  static bool BlinkExtensionWebViewMediaIntegrityEnabled(const FeatureContext*) { return BlinkExtensionWebViewMediaIntegrityEnabled(); }

  static bool BlinkGeometryMapperViewportFastPathEnabled() {
    return is_blink_geometry_mapper_viewport_fast_path_enabled_;
  }

  static bool BlinkGeometryMapperViewportFastPathEnabled(const FeatureContext*) { return BlinkGeometryMapperViewportFastPathEnabled(); }

  static bool BlinkLifecycleScriptForbiddenEnabled() {
    return is_blink_lifecycle_script_forbidden_enabled_;
  }

  static bool BlinkLifecycleScriptForbiddenEnabled(const FeatureContext*) { return BlinkLifecycleScriptForbiddenEnabled(); }

  static bool BlinkRuntimeCallStatsEnabled() {
    return is_blink_runtime_call_stats_enabled_;
  }

  static bool BlinkRuntimeCallStatsEnabled(const FeatureContext*) { return BlinkRuntimeCallStatsEnabled(); }

  static bool BlobBytesEnabled() {
    return is_blob_bytes_enabled_;
  }

  static bool BlobBytesEnabled(const FeatureContext*) { return BlobBytesEnabled(); }

  static bool BlockSelectPopupUnfocusedWindowEnabled() {
    return is_block_select_popup_unfocused_window_enabled_;
  }

  static bool BlockSelectPopupUnfocusedWindowEnabled(const FeatureContext*) { return BlockSelectPopupUnfocusedWindowEnabled(); }

  static bool BoundaryEventDispatchTracksNodeRemovalEnabled() {
    return is_boundary_event_dispatch_tracks_node_removal_enabled_;
  }

  static bool BoundaryEventDispatchTracksNodeRemovalEnabled(const FeatureContext*) { return BoundaryEventDispatchTracksNodeRemovalEnabled(); }

  static bool BrowserInitiatedAutomaticPictureInPictureEnabled() {
    return is_browser_initiated_automatic_picture_in_picture_enabled_;
  }

  static bool BrowserInitiatedAutomaticPictureInPictureEnabled(const FeatureContext*) { return BrowserInitiatedAutomaticPictureInPictureEnabled(); }

  static bool BrowserVerifiedUserActivationKeyboardEnabled() {
    return is_browser_verified_user_activation_keyboard_enabled_;
  }

  static bool BrowserVerifiedUserActivationKeyboardEnabled(const FeatureContext*) { return BrowserVerifiedUserActivationKeyboardEnabled(); }

  static bool BrowserVerifiedUserActivationMouseEnabled() {
    return is_browser_verified_user_activation_mouse_enabled_;
  }

  static bool BrowserVerifiedUserActivationMouseEnabled(const FeatureContext*) { return BrowserVerifiedUserActivationMouseEnabled(); }

  static bool BufferedBytesConsumerLimitSizeEnabled() {
    return is_buffered_bytes_consumer_limit_size_enabled_;
  }

  static bool BufferedBytesConsumerLimitSizeEnabled(const FeatureContext*) { return BufferedBytesConsumerLimitSizeEnabled(); }

  static bool BypassPepcSecurityForTestingEnabled() {
    return is_bypass_pepc_security_for_testing_enabled_;
  }

  static bool BypassPepcSecurityForTestingEnabled(const FeatureContext*) { return BypassPepcSecurityForTestingEnabled(); }

  static bool CacheControlRFC7234ParsingEnabled() {
    return is_cache_control_rfc_7234_parsing_enabled_;
  }

  static bool CacheControlRFC7234ParsingEnabled(const FeatureContext*) { return CacheControlRFC7234ParsingEnabled(); }

  static bool CacheControlRFC7234ParsingMetricsEnabled() {
    return is_cache_control_rfc_7234_parsing_metrics_enabled_;
  }

  static bool CacheControlRFC7234ParsingMetricsEnabled(const FeatureContext*) { return CacheControlRFC7234ParsingMetricsEnabled(); }

  static bool CacheStyleAdjusterEnabled() {
    return is_cache_style_adjuster_enabled_;
  }

  static bool CacheStyleAdjusterEnabled(const FeatureContext*) { return CacheStyleAdjusterEnabled(); }

  static bool CallExitNodeWithoutLayoutObjectEnabled() {
    return is_call_exit_node_without_layout_object_enabled_;
  }

  static bool CallExitNodeWithoutLayoutObjectEnabled(const FeatureContext*) { return CallExitNodeWithoutLayoutObjectEnabled(); }

  static bool Canvas2dCanvasFilterEnabled() {
    return is_canvas_2d_canvas_filter_enabled_;
  }

  static bool Canvas2dCanvasFilterEnabled(const FeatureContext*) { return Canvas2dCanvasFilterEnabled(); }

  static bool Canvas2dGPUTransferEnabled() {
    return is_canvas_2d_gpu_transfer_enabled_;
  }

  static bool Canvas2dGPUTransferEnabled(const FeatureContext*) { return Canvas2dGPUTransferEnabled(); }

  static bool Canvas2dLayersEnabled() {
    return is_canvas_2d_layers_enabled_;
  }

  static bool Canvas2dLayersEnabled(const FeatureContext*) { return Canvas2dLayersEnabled(); }

  static bool Canvas2dLayersWithOptionsEnabled() {
    if (!Canvas2dLayersEnabled())
      return false;
    return is_canvas_2d_layers_with_options_enabled_;
  }

  static bool Canvas2dLayersWithOptionsEnabled(const FeatureContext*) { return Canvas2dLayersWithOptionsEnabled(); }

  static bool CanvasFloatingPointEnabled() {
    return is_canvas_floating_point_enabled_;
  }

  static bool CanvasFloatingPointEnabled(const FeatureContext*) { return CanvasFloatingPointEnabled(); }

  static bool CanvasGlobalHDRHeadroomEnabled() {
    return is_canvas_global_hdr_headroom_enabled_;
  }

  static bool CanvasGlobalHDRHeadroomEnabled(const FeatureContext*) { return CanvasGlobalHDRHeadroomEnabled(); }

  static bool CanvasGradientCSSColor4Enabled() {
    return is_canvas_gradient_css_color_4_enabled_;
  }

  static bool CanvasGradientCSSColor4Enabled(const FeatureContext*) { return CanvasGradientCSSColor4Enabled(); }

  static bool CanvasHDREnabled() {
    return is_canvas_hdr_enabled_;
  }

  static bool CanvasHDREnabled(const FeatureContext*) { return CanvasHDREnabled(); }

  static bool CanvasTextMetricsPreciseBoundsEnabled() {
    return is_canvas_text_metrics_precise_bounds_enabled_;
  }

  static bool CanvasTextMetricsPreciseBoundsEnabled(const FeatureContext*) { return CanvasTextMetricsPreciseBoundsEnabled(); }

  static bool CanvasToneMappingEnabled() {
    return is_canvas_tone_mapping_enabled_;
  }

  static bool CanvasToneMappingEnabled(const FeatureContext*) { return CanvasToneMappingEnabled(); }

  static bool CanvasUsesArcPaintOpEnabled() {
    return is_canvas_uses_arc_paint_op_enabled_;
  }

  static bool CanvasUsesArcPaintOpEnabled(const FeatureContext*) { return CanvasUsesArcPaintOpEnabled(); }

  static bool CapabilityDelegationDisplayCaptureRequestEnabled() {
    return is_capability_delegation_display_capture_request_enabled_;
  }

  static bool CapabilityDelegationDisplayCaptureRequestEnabled(const FeatureContext*) { return CapabilityDelegationDisplayCaptureRequestEnabled(); }

  static bool CaptureControllerEnabled() {
    return is_capture_controller_enabled_;
  }

  static bool CaptureControllerEnabled(const FeatureContext*) { return CaptureControllerEnabled(); }

  static bool CapturedMouseEventsEnabled() {
    if (!CaptureControllerEnabled())
      return false;
    return is_captured_mouse_events_enabled_;
  }

  static bool CapturedMouseEventsEnabled(const FeatureContext*) { return CapturedMouseEventsEnabled(); }

  static bool CapturedSurfaceControlEnabled() {
    return is_captured_surface_control_enabled_;
  }

  static bool CapturedSurfaceControlEnabled(const FeatureContext*) { return CapturedSurfaceControlEnabled(); }

  static bool CapturedSurfaceResolutionEnabled() {
    return is_captured_surface_resolution_enabled_;
  }

  static bool CapturedSurfaceResolutionEnabled(const FeatureContext*) { return CapturedSurfaceResolutionEnabled(); }

  static bool CaptureHandleEnabled() {
    if (!GetDisplayMediaEnabled())
      return false;
    return is_capture_handle_enabled_;
  }

  static bool CaptureHandleEnabled(const FeatureContext*) { return CaptureHandleEnabled(); }

  static bool CaretWithTextAffinityUpstreamEnabled() {
    return is_caret_with_text_affinity_upstream_enabled_;
  }

  static bool CaretWithTextAffinityUpstreamEnabled(const FeatureContext*) { return CaretWithTextAffinityUpstreamEnabled(); }

  static bool CCTNewRFMPushBehaviorEnabled() {
    return is_cct_new_rfm_push_behavior_enabled_;
  }

  static bool CCTNewRFMPushBehaviorEnabled(const FeatureContext*) { return CCTNewRFMPushBehaviorEnabled(); }

  static bool CheckableInputTypeLayoutInlineEnabled() {
    return is_checkable_input_type_layout_inline_enabled_;
  }

  static bool CheckableInputTypeLayoutInlineEnabled(const FeatureContext*) { return CheckableInputTypeLayoutInlineEnabled(); }

  static bool CheckForCanonicalPositionInIdleSpellCheckEnabled() {
    return is_check_for_canonical_position_in_idle_spell_check_enabled_;
  }

  static bool CheckForCanonicalPositionInIdleSpellCheckEnabled(const FeatureContext*) { return CheckForCanonicalPositionInIdleSpellCheckEnabled(); }

  static bool CheckVisibilityExtraPropertiesEnabled() {
    return is_check_visibility_extra_properties_enabled_;
  }

  static bool CheckVisibilityExtraPropertiesEnabled(const FeatureContext*) { return CheckVisibilityExtraPropertiesEnabled(); }

  static bool ClampWordBoundaryToContentEditableScopeEnabled() {
    return is_clamp_word_boundary_to_content_editable_scope_enabled_;
  }

  static bool ClampWordBoundaryToContentEditableScopeEnabled(const FeatureContext*) { return ClampWordBoundaryToContentEditableScopeEnabled(); }

  static bool ClearCurrentTargetAfterDispatchEnabled() {
    return is_clear_current_target_after_dispatch_enabled_;
  }

  static bool ClearCurrentTargetAfterDispatchEnabled(const FeatureContext*) { return ClearCurrentTargetAfterDispatchEnabled(); }

  static bool ClearFocusWithinOnSubtreeRemovalEnabled() {
    return is_clear_focus_within_on_subtree_removal_enabled_;
  }

  static bool ClearFocusWithinOnSubtreeRemovalEnabled(const FeatureContext*) { return ClearFocusWithinOnSubtreeRemovalEnabled(); }

  static bool ClearTargetOnlyIfInShadowTreeEnabled() {
    return is_clear_target_only_if_in_shadow_tree_enabled_;
  }

  static bool ClearTargetOnlyIfInShadowTreeEnabled(const FeatureContext*) { return ClearTargetOnlyIfInShadowTreeEnabled(); }

  static bool ClickFocusDoesntPersistStatusBubbleEnabled() {
    return is_click_focus_doesnt_persist_status_bubble_enabled_;
  }

  static bool ClickFocusDoesntPersistStatusBubbleEnabled(const FeatureContext*) { return ClickFocusDoesntPersistStatusBubbleEnabled(); }

  static bool ClipboardEventTargetCanBeFocusedElementEnabled() {
    return is_clipboard_event_target_can_be_focused_element_enabled_;
  }

  static bool ClipboardEventTargetCanBeFocusedElementEnabled(const FeatureContext*) { return ClipboardEventTargetCanBeFocusedElementEnabled(); }

  static bool ClipboardEventTargetUsesContainerNodeEnabled() {
    return is_clipboard_event_target_uses_container_node_enabled_;
  }

  static bool ClipboardEventTargetUsesContainerNodeEnabled(const FeatureContext*) { return ClipboardEventTargetUsesContainerNodeEnabled(); }

  static bool ClipboardItemWithDOMStringSupportEnabled() {
    return is_clipboard_item_with_dom_string_support_enabled_;
  }

  static bool ClipboardItemWithDOMStringSupportEnabled(const FeatureContext*) { return ClipboardItemWithDOMStringSupportEnabled(); }

  static bool ClipElementVisibleBoundsInLocalRootEnabled() {
    return is_clip_element_visible_bounds_in_local_root_enabled_;
  }

  static bool ClipElementVisibleBoundsInLocalRootEnabled(const FeatureContext*) { return ClipElementVisibleBoundsInLocalRootEnabled(); }

  static bool ClipPathNestedRasterOptimizationEnabled() {
    return is_clip_path_nested_raster_optimization_enabled_;
  }

  static bool ClipPathNestedRasterOptimizationEnabled(const FeatureContext*) { return ClipPathNestedRasterOptimizationEnabled(); }

  static bool CoalesceSelectionchangeEventEnabled() {
    return is_coalesce_selectionchange_event_enabled_;
  }

  static bool CoalesceSelectionchangeEventEnabled(const FeatureContext*) { return CoalesceSelectionchangeEventEnabled(); }

  static bool CoepReflectionEnabled() {
    return is_coep_reflection_enabled_;
  }

  static bool CoepReflectionEnabled(const FeatureContext*) { return CoepReflectionEnabled(); }

  static bool CollapseZeroWidthSpaceWhenReuseItemEnabled() {
    return is_collapse_zero_width_space_when_reuse_item_enabled_;
  }

  static bool CollapseZeroWidthSpaceWhenReuseItemEnabled(const FeatureContext*) { return CollapseZeroWidthSpaceWhenReuseItemEnabled(); }

  static bool ColorInputAcceptsCSSColorsEnabled() {
    return is_color_input_accepts_css_colors_enabled_;
  }

  static bool ColorInputAcceptsCSSColorsEnabled(const FeatureContext*) { return ColorInputAcceptsCSSColorsEnabled(); }

  static bool ColorSpaceDisplayP3LinearEnabled() {
    return is_color_space_display_p_3_linear_enabled_;
  }

  static bool ColorSpaceDisplayP3LinearEnabled(const FeatureContext*) { return ColorSpaceDisplayP3LinearEnabled(); }

  static bool ColorSpacePredefinedLinearSpacesEnabled() {
    return is_color_space_predefined_linear_spaces_enabled_;
  }

  static bool ColorSpacePredefinedLinearSpacesEnabled(const FeatureContext*) { return ColorSpacePredefinedLinearSpacesEnabled(); }

  static bool ColorSpaceRec2100LinearEnabled() {
    return is_color_space_rec_2100_linear_enabled_;
  }

  static bool ColorSpaceRec2100LinearEnabled(const FeatureContext*) { return ColorSpaceRec2100LinearEnabled(); }

  static bool CommandEventNotComposedEnabled() {
    return is_command_event_not_composed_enabled_;
  }

  static bool CommandEventNotComposedEnabled(const FeatureContext*) { return CommandEventNotComposedEnabled(); }

  static bool CommaSeparatedContainerQueriesEnabled() {
    return is_comma_separated_container_queries_enabled_;
  }

  static bool CommaSeparatedContainerQueriesEnabled(const FeatureContext*) { return CommaSeparatedContainerQueriesEnabled(); }

  static bool ComposedPathReturnTargetBeingDispatchedEnabled() {
    return is_composed_path_return_target_being_dispatched_enabled_;
  }

  static bool ComposedPathReturnTargetBeingDispatchedEnabled(const FeatureContext*) { return ComposedPathReturnTargetBeingDispatchedEnabled(); }

  static bool CompositeBGColorAnimationEnabled() {
    return is_composite_bg_color_animation_enabled_;
  }

  static bool CompositeBGColorAnimationEnabled(const FeatureContext*) { return CompositeBGColorAnimationEnabled(); }

  static bool CompositeBoxShadowAnimationEnabled() {
    return is_composite_box_shadow_animation_enabled_;
  }

  static bool CompositeBoxShadowAnimationEnabled(const FeatureContext*) { return CompositeBoxShadowAnimationEnabled(); }

  static bool CompositeClipPathAnimationEnabled() {
    return is_composite_clip_path_animation_enabled_;
  }

  static bool CompositeClipPathAnimationEnabled(const FeatureContext*) { return CompositeClipPathAnimationEnabled(); }

  static bool CompositedAnimationsCancelledAsynchronouslyEnabled() {
    return is_composited_animations_cancelled_asynchronously_enabled_;
  }

  static bool CompositedAnimationsCancelledAsynchronouslyEnabled(const FeatureContext*) { return CompositedAnimationsCancelledAsynchronouslyEnabled(); }

  static bool CompositedSelectionUpdateEnabled() {
    return is_composited_selection_update_enabled_;
  }

  static bool CompositedSelectionUpdateEnabled(const FeatureContext*) { return CompositedSelectionUpdateEnabled(); }

  static bool CompositingDecisionAtAnimationPhaseBoundariesEnabled() {
    return is_compositing_decision_at_animation_phase_boundaries_enabled_;
  }

  static bool CompositingDecisionAtAnimationPhaseBoundariesEnabled(const FeatureContext*) { return CompositingDecisionAtAnimationPhaseBoundariesEnabled(); }

  static bool CompositionForegroundMarkersEnabled() {
    return is_composition_foreground_markers_enabled_;
  }

  static bool CompositionForegroundMarkersEnabled(const FeatureContext*) { return CompositionForegroundMarkersEnabled(); }

  static bool CompositorEventTriggerEnabled() {
    return is_compositor_event_trigger_enabled_;
  }

  static bool CompositorEventTriggerEnabled(const FeatureContext*) { return CompositorEventTriggerEnabled(); }

  static bool CompositorTimelineTriggerEnabled() {
    return is_compositor_timeline_trigger_enabled_;
  }

  static bool CompositorTimelineTriggerEnabled(const FeatureContext*) { return CompositorTimelineTriggerEnabled(); }

  static bool CompressionDictionaryTransportEnabled() {
    return is_compression_dictionary_transport_enabled_;
  }

  static bool CompressionDictionaryTransportEnabled(const FeatureContext*) { return CompressionDictionaryTransportEnabled(); }

  static bool ComputedAccessibilityInfoEnabled() {
    return is_computed_accessibility_info_enabled_;
  }

  static bool ComputedAccessibilityInfoEnabled(const FeatureContext*) { return ComputedAccessibilityInfoEnabled(); }

  static bool ComputeInlineContentsSafeRetargetEnabled() {
    return is_compute_inline_contents_safe_retarget_enabled_;
  }

  static bool ComputeInlineContentsSafeRetargetEnabled(const FeatureContext*) { return ComputeInlineContentsSafeRetargetEnabled(); }

  static bool ComputePressureEnabled() {
    return is_compute_pressure_enabled_;
  }

  static bool ComputePressureEnabled(const FeatureContext*) { return ComputePressureEnabled(); }

  static bool ComputePressureOwnContributionEstimateEnabled() {
    return is_compute_pressure_own_contribution_estimate_enabled_;
  }

  static bool ComputePressureOwnContributionEstimateEnabled(const FeatureContext*) { return ComputePressureOwnContributionEstimateEnabled(); }

  static bool ConsiderSubOrSuperScriptAncestorAlignForCaretSelectionEnabled() {
    return is_consider_sub_or_super_script_ancestor_align_for_caret_selection_enabled_;
  }

  static bool ConsiderSubOrSuperScriptAncestorAlignForCaretSelectionEnabled(const FeatureContext*) { return ConsiderSubOrSuperScriptAncestorAlignForCaretSelectionEnabled(); }

  static bool ContactsManagerEnabled() {
    return is_contacts_manager_enabled_;
  }

  static bool ContactsManagerEnabled(const FeatureContext*) { return ContactsManagerEnabled(); }

  static bool ContactsManagerExtraPropertiesEnabled() {
    return is_contacts_manager_extra_properties_enabled_;
  }

  static bool ContactsManagerExtraPropertiesEnabled(const FeatureContext*) { return ContactsManagerExtraPropertiesEnabled(); }

  static bool ContainerNameOnlyEnabled() {
    return is_container_name_only_enabled_;
  }

  static bool ContainerNameOnlyEnabled(const FeatureContext*) { return ContainerNameOnlyEnabled(); }

  static bool ContentIndexEnabled() {
    return is_content_index_enabled_;
  }

  static bool ContentIndexEnabled(const FeatureContext*) { return ContentIndexEnabled(); }

  static bool ContextMenuEnabled() {
    return is_context_menu_enabled_;
  }

  static bool ContextMenuEnabled(const FeatureContext*) { return ContextMenuEnabled(); }

  static bool ControlledFrameEnabled() {
    return is_controlled_frame_enabled_;
  }

  static bool ControlledFrameEnabled(const FeatureContext*) { return ControlledFrameEnabled(); }

  static bool ControlledFrameWebRequestSecurityInfoEnabled() {
    if (!ControlledFrameEnabled())
      return false;
    return is_controlled_frame_web_request_security_info_enabled_;
  }

  static bool ControlledFrameWebRequestSecurityInfoEnabled(const FeatureContext*) { return ControlledFrameWebRequestSecurityInfoEnabled(); }

  static bool CookieStoreAPIMaxAgeEnabled() {
    return is_cookie_store_api_max_age_enabled_;
  }

  static bool CookieStoreAPIMaxAgeEnabled(const FeatureContext*) { return CookieStoreAPIMaxAgeEnabled(); }

  static bool CookieStoreAPIWhitespaceStrippingEnabled() {
    return is_cookie_store_api_whitespace_stripping_enabled_;
  }

  static bool CookieStoreAPIWhitespaceStrippingEnabled(const FeatureContext*) { return CookieStoreAPIWhitespaceStrippingEnabled(); }

  static bool CorrectTemplateFormParsingEnabled() {
    return is_correct_template_form_parsing_enabled_;
  }

  static bool CorrectTemplateFormParsingEnabled(const FeatureContext*) { return CorrectTemplateFormParsingEnabled(); }

  static bool CorsRFC1918Enabled() {
    return is_cors_rfc_1918_enabled_;
  }

  static bool CorsRFC1918Enabled(const FeatureContext*) { return CorsRFC1918Enabled(); }

  static bool CreateInlineContentsExcludeOutOfFlowEnabled() {
    return is_create_inline_contents_exclude_out_of_flow_enabled_;
  }

  static bool CreateInlineContentsExcludeOutOfFlowEnabled(const FeatureContext*) { return CreateInlineContentsExcludeOutOfFlowEnabled(); }

  static bool CSPReportHashEnabled() {
    return is_csp_report_hash_enabled_;
  }

  static bool CSPReportHashEnabled(const FeatureContext*) { return CSPReportHashEnabled(); }

  static bool CSSAccentColorKeywordEnabled() {
    return is_css_accent_color_keyword_enabled_;
  }

  static bool CSSAccentColorKeywordEnabled(const FeatureContext*) { return CSSAccentColorKeywordEnabled(); }

  static bool CSSActiveCaptionMapsToCanvasEnabled() {
    return is_css_active_caption_maps_to_canvas_enabled_;
  }

  static bool CSSActiveCaptionMapsToCanvasEnabled(const FeatureContext*) { return CSSActiveCaptionMapsToCanvasEnabled(); }

  static bool CSSAlphaColorFunctionEnabled() {
    return is_css_alpha_color_function_enabled_;
  }

  static bool CSSAlphaColorFunctionEnabled(const FeatureContext*) { return CSSAlphaColorFunctionEnabled(); }

  static bool CSSAltCounterEnabled() {
    return is_css_alt_counter_enabled_;
  }

  static bool CSSAltCounterEnabled(const FeatureContext*) { return CSSAltCounterEnabled(); }

  static bool CSSAnchorWithTransformsEnabled() {
    return is_css_anchor_with_transforms_enabled_;
  }

  static bool CSSAnchorWithTransformsEnabled(const FeatureContext*) { return CSSAnchorWithTransformsEnabled(); }

  static bool CSSAnimationIterationCompositeEnabled() {
    return is_css_animation_iteration_composite_enabled_;
  }

  static bool CSSAnimationIterationCompositeEnabled(const FeatureContext*) { return CSSAnimationIterationCompositeEnabled(); }

  static bool CSSArgumentGrammarEnabled() {
    return is_css_argument_grammar_enabled_;
  }

  static bool CSSArgumentGrammarEnabled(const FeatureContext*) { return CSSArgumentGrammarEnabled(); }

  static bool CSSAtRuleCounterStyleImageSymbolsEnabled() {
    return is_css_at_rule_counter_style_image_symbols_enabled_;
  }

  static bool CSSAtRuleCounterStyleImageSymbolsEnabled(const FeatureContext*) { return CSSAtRuleCounterStyleImageSymbolsEnabled(); }

  static bool CSSAtRuleCounterStyleSpeakAsDescriptorEnabled() {
    return is_css_at_rule_counter_style_speak_as_descriptor_enabled_;
  }

  static bool CSSAtRuleCounterStyleSpeakAsDescriptorEnabled(const FeatureContext*) { return CSSAtRuleCounterStyleSpeakAsDescriptorEnabled(); }

  static bool CSSBackgroundClipBorderAreaEnabled() {
    return is_css_background_clip_border_area_enabled_;
  }

  static bool CSSBackgroundClipBorderAreaEnabled(const FeatureContext*) { return CSSBackgroundClipBorderAreaEnabled(); }

  static bool CSSBorderShapeEnabled() {
    return is_css_border_shape_enabled_;
  }

  static bool CSSBorderShapeEnabled(const FeatureContext*) { return CSSBorderShapeEnabled(); }

  static bool CSSCalcSimplificationAndSerializationEnabled() {
    return is_css_calc_simplification_and_serialization_enabled_;
  }

  static bool CSSCalcSimplificationAndSerializationEnabled(const FeatureContext*) { return CSSCalcSimplificationAndSerializationEnabled(); }

  static bool CSSCaretAnimationEnabled() {
    return is_css_caret_animation_enabled_;
  }

  static bool CSSCaretAnimationEnabled(const FeatureContext*) { return CSSCaretAnimationEnabled(); }

  static bool CSSCaretShapeEnabled() {
    return is_css_caret_shape_enabled_;
  }

  static bool CSSCaretShapeEnabled(const FeatureContext*) { return CSSCaretShapeEnabled(); }

  static bool CSSCaseSensitiveSelectorEnabled() {
    return is_css_case_sensitive_selector_enabled_;
  }

  static bool CSSCaseSensitiveSelectorEnabled(const FeatureContext*) { return CSSCaseSensitiveSelectorEnabled(); }

  static bool CSSChUnitSpecCompliantFallbackEnabled() {
    return is_css_ch_unit_spec_compliant_fallback_enabled_;
  }

  static bool CSSChUnitSpecCompliantFallbackEnabled(const FeatureContext*) { return CSSChUnitSpecCompliantFallbackEnabled(); }

  static bool CSSColorTypedOMEnabled() {
    return is_css_color_typed_om_enabled_;
  }

  static bool CSSColorTypedOMEnabled(const FeatureContext*) { return CSSColorTypedOMEnabled(); }

  static bool CSSContainerProgressNotationEnabled() {
    return is_css_container_progress_notation_enabled_;
  }

  static bool CSSContainerProgressNotationEnabled(const FeatureContext*) { return CSSContainerProgressNotationEnabled(); }

  static bool CSSContainerStyleQueriesRangeEnabled() {
    return is_css_container_style_queries_range_enabled_;
  }

  static bool CSSContainerStyleQueriesRangeEnabled(const FeatureContext*) { return CSSContainerStyleQueriesRangeEnabled(); }

  static bool CSSContrastColorEnabled() {
    return is_css_contrast_color_enabled_;
  }

  static bool CSSContrastColorEnabled(const FeatureContext*) { return CSSContrastColorEnabled(); }

  static bool CSSCornersShorthandEnabled() {
    return is_css_corners_shorthand_enabled_;
  }

  static bool CSSCornersShorthandEnabled(const FeatureContext*) { return CSSCornersShorthandEnabled(); }

  static bool CSSCounterResetReversedEnabled() {
    return is_css_counter_reset_reversed_enabled_;
  }

  static bool CSSCounterResetReversedEnabled(const FeatureContext*) { return CSSCounterResetReversedEnabled(); }

  static bool CSSCrossFadeEnabled() {
    return is_css_cross_fade_enabled_;
  }

  static bool CSSCrossFadeEnabled(const FeatureContext*) { return CSSCrossFadeEnabled(); }

  static bool CSSCustomMediaEnabled() {
    return is_css_custom_media_enabled_;
  }

  static bool CSSCustomMediaEnabled(const FeatureContext*) { return CSSCustomMediaEnabled(); }

  static bool CSSDynamicRangeLimitEnabled() {
    return is_css_dynamic_range_limit_enabled_;
  }

  static bool CSSDynamicRangeLimitEnabled(const FeatureContext*) { return CSSDynamicRangeLimitEnabled(); }

  static bool CSSEnumeratedCustomPropertiesEnabled() {
    return is_css_enumerated_custom_properties_enabled_;
  }

  static bool CSSEnumeratedCustomPropertiesEnabled(const FeatureContext*) { return CSSEnumeratedCustomPropertiesEnabled(); }

  static bool CSSFontFamilySerializationEnabled() {
    return is_css_font_family_serialization_enabled_;
  }

  static bool CSSFontFamilySerializationEnabled(const FeatureContext*) { return CSSFontFamilySerializationEnabled(); }

  static bool CSSFontSizeAdjustEnabled() {
    return is_css_font_size_adjust_enabled_;
  }

  static bool CSSFontSizeAdjustEnabled(const FeatureContext*) { return CSSFontSizeAdjustEnabled(); }

  static bool CSSFunctionsEnabled() {
    return is_css_functions_enabled_;
  }

  static bool CSSFunctionsEnabled(const FeatureContext*) { return CSSFunctionsEnabled(); }

  static bool CSSGapDecorationEnabled() {
    if (!CSSGridGapSuppressionEnabled())
      return false;
    return is_css_gap_decoration_enabled_;
  }

  static bool CSSGapDecorationEnabled(const FeatureContext*) { return CSSGapDecorationEnabled(); }

  static bool CSSGridGapSuppressionEnabled() {
    return is_css_grid_gap_suppression_enabled_;
  }

  static bool CSSGridGapSuppressionEnabled(const FeatureContext*) { return CSSGridGapSuppressionEnabled(); }

  static bool CSSGridLanesLayoutEnabled() {
    return is_css_grid_lanes_layout_enabled_;
  }

  static bool CSSGridLanesLayoutEnabled(const FeatureContext*) { return CSSGridLanesLayoutEnabled(); }

  static bool CSSHangingPunctuationEnabled() {
    return is_css_hanging_punctuation_enabled_;
  }

  static bool CSSHangingPunctuationEnabled(const FeatureContext*) { return CSSHangingPunctuationEnabled(); }

  static bool CSSHexAlphaColorEnabled() {
    return is_css_hex_alpha_color_enabled_;
  }

  static bool CSSHexAlphaColorEnabled(const FeatureContext*) { return CSSHexAlphaColorEnabled(); }

  static bool CSSIdentFunctionEnabled() {
    return is_css_ident_function_enabled_;
  }

  static bool CSSIdentFunctionEnabled(const FeatureContext*) { return CSSIdentFunctionEnabled(); }

  static bool CSSImageAnimationEnabled() {
    return is_css_image_animation_enabled_;
  }

  static bool CSSImageAnimationEnabled(const FeatureContext*) { return CSSImageAnimationEnabled(); }

  static bool CSSInheritFunctionEnabled() {
    return is_css_inherit_function_enabled_;
  }

  static bool CSSInheritFunctionEnabled(const FeatureContext*) { return CSSInheritFunctionEnabled(); }

  static bool CSSKeyframesRuleLengthEnabled() {
    return is_css_keyframes_rule_length_enabled_;
  }

  static bool CSSKeyframesRuleLengthEnabled(const FeatureContext*) { return CSSKeyframesRuleLengthEnabled(); }

  static bool CSSLangExtendedRangesEnabled() {
    return is_css_lang_extended_ranges_enabled_;
  }

  static bool CSSLangExtendedRangesEnabled(const FeatureContext*) { return CSSLangExtendedRangesEnabled(); }

  static bool CSSLayoutAPIEnabled() {
    return is_css_layout_api_enabled_;
  }

  static bool CSSLayoutAPIEnabled(const FeatureContext*) { return CSSLayoutAPIEnabled(); }

  static bool CSSLetterAndWordSpacingPercentageEnabled() {
    return is_css_letter_and_word_spacing_percentage_enabled_;
  }

  static bool CSSLetterAndWordSpacingPercentageEnabled(const FeatureContext*) { return CSSLetterAndWordSpacingPercentageEnabled(); }

  static bool CSSLightDarkImageEnabled() {
    return is_css_light_dark_image_enabled_;
  }

  static bool CSSLightDarkImageEnabled(const FeatureContext*) { return CSSLightDarkImageEnabled(); }

  static bool CSSLineClampEnabled() {
    return is_css_line_clamp_enabled_;
  }

  static bool CSSLineClampEnabled(const FeatureContext*) { return CSSLineClampEnabled(); }

  static bool CSSLineClampLineBreakingEllipsisEnabled() {
    if (!CSSLineClampEnabled())
      return false;
    return is_css_line_clamp_line_breaking_ellipsis_enabled_;
  }

  static bool CSSLineClampLineBreakingEllipsisEnabled(const FeatureContext*) { return CSSLineClampLineBreakingEllipsisEnabled(); }

  static bool CSSLineClampLinesAndHeightEnabled() {
    if (!CSSLineClampEnabled())
      return false;
    return is_css_line_clamp_lines_and_height_enabled_;
  }

  static bool CSSLineClampLinesAndHeightEnabled(const FeatureContext*) { return CSSLineClampLinesAndHeightEnabled(); }

  static bool CSSListCounterAccountingEnabled() {
    return is_css_list_counter_accounting_enabled_;
  }

  static bool CSSListCounterAccountingEnabled(const FeatureContext*) { return CSSListCounterAccountingEnabled(); }

  static bool CSSLogicalCombinationPseudoEnabled() {
    return is_css_logical_combination_pseudo_enabled_;
  }

  static bool CSSLogicalCombinationPseudoEnabled(const FeatureContext*) { return CSSLogicalCombinationPseudoEnabled(); }

  static bool CSSMarkerNestedPseudoElementEnabled() {
    return is_css_marker_nested_pseudo_element_enabled_;
  }

  static bool CSSMarkerNestedPseudoElementEnabled(const FeatureContext*) { return CSSMarkerNestedPseudoElementEnabled(); }

  static bool CSSMediaProgressNotationEnabled() {
    return is_css_media_progress_notation_enabled_;
  }

  static bool CSSMediaProgressNotationEnabled(const FeatureContext*) { return CSSMediaProgressNotationEnabled(); }

  static bool CSSMixinsEnabled() {
    return is_css_mixins_enabled_;
  }

  static bool CSSMixinsEnabled(const FeatureContext*) { return CSSMixinsEnabled(); }

  static bool CSSNestedPseudoElementsEnabled() {
    return is_css_nested_pseudo_elements_enabled_;
  }

  static bool CSSNestedPseudoElementsEnabled(const FeatureContext*) { return CSSNestedPseudoElementsEnabled(); }

  static bool CSSOMGetComputedStylePseudoElementRequiresColonEnabled() {
    return is_cssom_get_computed_style_pseudo_element_requires_colon_enabled_;
  }

  static bool CSSOMGetComputedStylePseudoElementRequiresColonEnabled(const FeatureContext*) { return CSSOMGetComputedStylePseudoElementRequiresColonEnabled(); }

  static bool CSSOverscrollBehaviorChainEnabled() {
    return is_css_overscroll_behavior_chain_enabled_;
  }

  static bool CSSOverscrollBehaviorChainEnabled(const FeatureContext*) { return CSSOverscrollBehaviorChainEnabled(); }

  static bool CSSPaintAPIArgumentsEnabled() {
    return is_css_paint_api_arguments_enabled_;
  }

  static bool CSSPaintAPIArgumentsEnabled(const FeatureContext*) { return CSSPaintAPIArgumentsEnabled(); }

  static bool CSSParserIgnoreCharsetForURLsEnabled() {
    return is_css_parser_ignore_charset_for_urls_enabled_;
  }

  static bool CSSParserIgnoreCharsetForURLsEnabled(const FeatureContext*) { return CSSParserIgnoreCharsetForURLsEnabled(); }

  static bool CSSPolygonRoundingEnabled() {
    return is_css_polygon_rounding_enabled_;
  }

  static bool CSSPolygonRoundingEnabled(const FeatureContext*) { return CSSPolygonRoundingEnabled(); }

  static bool CSSPositionStickyStaticScrollPositionEnabled() {
    return is_css_position_sticky_static_scroll_position_enabled_;
  }

  static bool CSSPositionStickyStaticScrollPositionEnabled(const FeatureContext*) { return CSSPositionStickyStaticScrollPositionEnabled(); }

  static bool CSSProgressNotationEnabled() {
    return is_css_progress_notation_enabled_;
  }

  static bool CSSProgressNotationEnabled(const FeatureContext*) { return CSSProgressNotationEnabled(); }

  static bool CSSPseudoColumnEnabled() {
    return is_css_pseudo_column_enabled_;
  }

  static bool CSSPseudoColumnEnabled(const FeatureContext*) { return CSSPseudoColumnEnabled(); }

  static bool CSSPseudoElementBackdropEnabled() {
    return is_css_pseudo_element_backdrop_enabled_;
  }

  static bool CSSPseudoElementBackdropEnabled(const FeatureContext*) { return CSSPseudoElementBackdropEnabled(); }

  static bool CSSPseudoElementInterfaceEnabled() {
    return is_css_pseudo_element_interface_enabled_;
  }

  static bool CSSPseudoElementInterfaceEnabled(const FeatureContext*) { return CSSPseudoElementInterfaceEnabled(); }

  static bool CSSPseudoElementViewTransitionsEnabled() {
    if (!CSSPseudoElementInterfaceEnabled())
      return false;
    return is_css_pseudo_element_view_transitions_enabled_;
  }

  static bool CSSPseudoElementViewTransitionsEnabled(const FeatureContext*) { return CSSPseudoElementViewTransitionsEnabled(); }

  static bool CSSPseudoHasSlottedEnabled() {
    return is_css_pseudo_has_slotted_enabled_;
  }

  static bool CSSPseudoHasSlottedEnabled(const FeatureContext*) { return CSSPseudoHasSlottedEnabled(); }

  static bool CSSPseudoPlayingPausedEnabled() {
    return is_css_pseudo_playing_paused_enabled_;
  }

  static bool CSSPseudoPlayingPausedEnabled(const FeatureContext*) { return CSSPseudoPlayingPausedEnabled(); }

  static bool CSSPseudoScrollButtonsEnabled() {
    if (!PseudoElementsFocusableEnabled())
      return false;
    return is_css_pseudo_scroll_buttons_enabled_;
  }

  static bool CSSPseudoScrollButtonsEnabled(const FeatureContext*) { return CSSPseudoScrollButtonsEnabled(); }

  static bool CSSPseudoScrollMarkersEnabled() {
    if (!PseudoElementsFocusableEnabled())
      return false;
    return is_css_pseudo_scroll_markers_enabled_;
  }

  static bool CSSPseudoScrollMarkersEnabled(const FeatureContext*) { return CSSPseudoScrollMarkersEnabled(); }

  static bool CSSRandomFunctionEnabled() {
    return is_css_random_function_enabled_;
  }

  static bool CSSRandomFunctionEnabled(const FeatureContext*) { return CSSRandomFunctionEnabled(); }

  static bool CSSRandomFunctionTypedOMEnabled() {
    if (!CSSRandomFunctionEnabled())
      return false;
    return is_css_random_function_typed_om_enabled_;
  }

  static bool CSSRandomFunctionTypedOMEnabled(const FeatureContext*) { return CSSRandomFunctionTypedOMEnabled(); }

  static bool CSSResizeAutoEnabled() {
    return is_css_resize_auto_enabled_;
  }

  static bool CSSResizeAutoEnabled(const FeatureContext*) { return CSSResizeAutoEnabled(); }

  static bool CSSResourceIntegrityEnforcementEnabled() {
    return is_css_resource_integrity_enforcement_enabled_;
  }

  static bool CSSResourceIntegrityEnforcementEnabled(const FeatureContext*) { return CSSResourceIntegrityEnforcementEnabled(); }

  static bool CSSRevertRuleEnabled() {
    return is_css_revert_rule_enabled_;
  }

  static bool CSSRevertRuleEnabled(const FeatureContext*) { return CSSRevertRuleEnabled(); }

  static bool CSSRubyOverhangEnabled() {
    return is_css_ruby_overhang_enabled_;
  }

  static bool CSSRubyOverhangEnabled(const FeatureContext*) { return CSSRubyOverhangEnabled(); }

  static bool CSSSafePrintableInsetEnabled() {
    return is_css_safe_printable_inset_enabled_;
  }

  static bool CSSSafePrintableInsetEnabled(const FeatureContext*) { return CSSSafePrintableInsetEnabled(); }

  static bool CSSScopeifiedParentPseudoClassEnabled() {
    return is_css_scopeified_parent_pseudo_class_enabled_;
  }

  static bool CSSScopeifiedParentPseudoClassEnabled(const FeatureContext*) { return CSSScopeifiedParentPseudoClassEnabled(); }

  static bool CSSScopeImportEnabled() {
    return is_css_scope_import_enabled_;
  }

  static bool CSSScopeImportEnabled(const FeatureContext*) { return CSSScopeImportEnabled(); }

  static bool CSSScrolledContainerQueriesEnabled() {
    return is_css_scrolled_container_queries_enabled_;
  }

  static bool CSSScrolledContainerQueriesEnabled(const FeatureContext*) { return CSSScrolledContainerQueriesEnabled(); }

  static bool CSSScrollInitialTargetEnabled() {
    return is_css_scroll_initial_target_enabled_;
  }

  static bool CSSScrollInitialTargetEnabled(const FeatureContext*) { return CSSScrollInitialTargetEnabled(); }

  static bool CSSScrollMarkerGroupModesEnabled() {
    return is_css_scroll_marker_group_modes_enabled_;
  }

  static bool CSSScrollMarkerGroupModesEnabled(const FeatureContext*) { return CSSScrollMarkerGroupModesEnabled(); }

  static bool CSSScrollMarkerTargetBeforeAfterEnabled() {
    return is_css_scroll_marker_target_before_after_enabled_;
  }

  static bool CSSScrollMarkerTargetBeforeAfterEnabled(const FeatureContext*) { return CSSScrollMarkerTargetBeforeAfterEnabled(); }

  static bool CSSScrollSnapChangeEventEnabled() {
    return is_css_scroll_snap_change_event_enabled_;
  }

  static bool CSSScrollSnapChangeEventEnabled(const FeatureContext*) { return CSSScrollSnapChangeEventEnabled(); }

  static bool CSSScrollSnapChangingEventEnabled() {
    return is_css_scroll_snap_changing_event_enabled_;
  }

  static bool CSSScrollSnapChangingEventEnabled(const FeatureContext*) { return CSSScrollSnapChangingEventEnabled(); }

  static bool CSSScrollSnapEventConstructorExposedEnabled() {
    return is_css_scroll_snap_event_constructor_exposed_enabled_;
  }

  static bool CSSScrollSnapEventConstructorExposedEnabled(const FeatureContext*) { return CSSScrollSnapEventConstructorExposedEnabled(); }

  static bool CSSScrollSnapEventsEnabled() {
    if (CSSScrollSnapChangeEventEnabled())
      return true;
    if (CSSScrollSnapChangingEventEnabled())
      return true;
    return is_css_scroll_snap_events_enabled_;
  }

  static bool CSSScrollSnapEventsEnabled(const FeatureContext*) { return CSSScrollSnapEventsEnabled(); }

  static bool CSSScrollTargetGroupEnabled() {
    return is_css_scroll_target_group_enabled_;
  }

  static bool CSSScrollTargetGroupEnabled(const FeatureContext*) { return CSSScrollTargetGroupEnabled(); }

  static bool CSSScrollTargetGroupAriaCurrentEnabled() {
    return is_css_scroll_target_group_aria_current_enabled_;
  }

  static bool CSSScrollTargetGroupAriaCurrentEnabled(const FeatureContext*) { return CSSScrollTargetGroupAriaCurrentEnabled(); }

  static bool CSSShapeEllipseCirclePositionSerializationEnabled() {
    return is_css_shape_ellipse_circle_position_serialization_enabled_;
  }

  static bool CSSShapeEllipseCirclePositionSerializationEnabled(const FeatureContext*) { return CSSShapeEllipseCirclePositionSerializationEnabled(); }

  static bool CSSShapeOutsidePathAndShapeSupportEnabled() {
    return is_css_shape_outside_path_and_shape_support_enabled_;
  }

  static bool CSSShapeOutsidePathAndShapeSupportEnabled(const FeatureContext*) { return CSSShapeOutsidePathAndShapeSupportEnabled(); }

  static bool CSSShapeOutsideRectAndXywhSupportEnabled() {
    return is_css_shape_outside_rect_and_xywh_support_enabled_;
  }

  static bool CSSShapeOutsideRectAndXywhSupportEnabled(const FeatureContext*) { return CSSShapeOutsideRectAndXywhSupportEnabled(); }

  static bool CSSStyleSheetInitBaseURLEnabled() {
    return is_css_style_sheet_init_base_url_enabled_;
  }

  static bool CSSStyleSheetInitBaseURLEnabled(const FeatureContext*) { return CSSStyleSheetInitBaseURLEnabled(); }

  static bool CSSSupportsAtRuleFunctionEnabled() {
    return is_css_supports_at_rule_function_enabled_;
  }

  static bool CSSSupportsAtRuleFunctionEnabled(const FeatureContext*) { return CSSSupportsAtRuleFunctionEnabled(); }

  static bool CSSSupportsForImportRulesEnabled() {
    return is_css_supports_for_import_rules_enabled_;
  }

  static bool CSSSupportsForImportRulesEnabled(const FeatureContext*) { return CSSSupportsForImportRulesEnabled(); }

  static bool CSSSupportsNamedFeatureFunctionEnabled() {
    return is_css_supports_named_feature_function_enabled_;
  }

  static bool CSSSupportsNamedFeatureFunctionEnabled(const FeatureContext*) { return CSSSupportsNamedFeatureFunctionEnabled(); }

  static bool CSSSystemAccentColorEnabled() {
    return is_css_system_accent_color_enabled_;
  }

  static bool CSSSystemAccentColorEnabled(const FeatureContext*) { return CSSSystemAccentColorEnabled(); }

  static bool CSSTextAlignMatchParentEnabled() {
    return is_css_text_align_match_parent_enabled_;
  }

  static bool CSSTextAlignMatchParentEnabled(const FeatureContext*) { return CSSTextAlignMatchParentEnabled(); }

  static bool CSSTextDecorationSkipInkAllEnabled() {
    return is_css_text_decoration_skip_ink_all_enabled_;
  }

  static bool CSSTextDecorationSkipInkAllEnabled(const FeatureContext*) { return CSSTextDecorationSkipInkAllEnabled(); }

  static bool CSSTextDecorationSkipSpacesEnabled() {
    return is_css_text_decoration_skip_spaces_enabled_;
  }

  static bool CSSTextDecorationSkipSpacesEnabled(const FeatureContext*) { return CSSTextDecorationSkipSpacesEnabled(); }

  static bool CssTextFitEnabled() {
    return is_css_text_fit_enabled_;
  }

  static bool CssTextFitEnabled(const FeatureContext*) { return CssTextFitEnabled(); }

  static bool CssTextFitReshapingEnabled() {
    return is_css_text_fit_reshaping_enabled_;
  }

  static bool CssTextFitReshapingEnabled(const FeatureContext*) { return CssTextFitReshapingEnabled(); }

  static bool CssTextIndentEnabled() {
    return is_css_text_indent_enabled_;
  }

  static bool CssTextIndentEnabled(const FeatureContext*) { return CssTextIndentEnabled(); }

  static bool CssTextIndentAsPrimitiveEnabled() {
    return is_css_text_indent_as_primitive_enabled_;
  }

  static bool CssTextIndentAsPrimitiveEnabled(const FeatureContext*) { return CssTextIndentAsPrimitiveEnabled(); }

  static bool CSSTextSpacingEnabled() {
    return is_css_text_spacing_enabled_;
  }

  static bool CSSTextSpacingEnabled(const FeatureContext*) { return CSSTextSpacingEnabled(); }

  static bool CSSTextTransformFullSizeKanaEnabled() {
    return is_css_text_transform_full_size_kana_enabled_;
  }

  static bool CSSTextTransformFullSizeKanaEnabled(const FeatureContext*) { return CSSTextTransformFullSizeKanaEnabled(); }

  static bool CSSTextTransformFullWidthEnabled() {
    return is_css_text_transform_full_width_enabled_;
  }

  static bool CSSTextTransformFullWidthEnabled(const FeatureContext*) { return CSSTextTransformFullWidthEnabled(); }

  static bool CSSTextTransformMultiKeywordEnabled() {
    if (!CSSTextTransformFullWidthEnabled())
      return false;
    if (!CSSTextTransformFullSizeKanaEnabled())
      return false;
    return is_css_text_transform_multi_keyword_enabled_;
  }

  static bool CSSTextTransformMultiKeywordEnabled(const FeatureContext*) { return CSSTextTransformMultiKeywordEnabled(); }

  static bool CSSTimelineScopeAllEnabled() {
    return is_css_timeline_scope_all_enabled_;
  }

  static bool CSSTimelineScopeAllEnabled(const FeatureContext*) { return CSSTimelineScopeAllEnabled(); }

  static bool CSSTimelineScopeGlobalEnabled() {
    return is_css_timeline_scope_global_enabled_;
  }

  static bool CSSTimelineScopeGlobalEnabled(const FeatureContext*) { return CSSTimelineScopeGlobalEnabled(); }

  static bool CSSTypedArithmeticEnabled() {
    return is_css_typed_arithmetic_enabled_;
  }

  static bool CSSTypedArithmeticEnabled(const FeatureContext*) { return CSSTypedArithmeticEnabled(); }

  static bool CSSURLRequestModifiersEnabled() {
    return is_css_url_request_modifiers_enabled_;
  }

  static bool CSSURLRequestModifiersEnabled(const FeatureContext*) { return CSSURLRequestModifiersEnabled(); }

  static bool CSSUserSelectContainEnabled() {
    return is_css_user_select_contain_enabled_;
  }

  static bool CSSUserSelectContainEnabled(const FeatureContext*) { return CSSUserSelectContainEnabled(); }

  static bool CSSUserValidAndUserInvalidForRadioEnabled() {
    return is_css_user_valid_and_user_invalid_for_radio_enabled_;
  }

  static bool CSSUserValidAndUserInvalidForRadioEnabled(const FeatureContext*) { return CSSUserValidAndUserInvalidForRadioEnabled(); }

  static bool CSSVideoDynamicRangeMediaQueriesEnabled() {
    return is_css_video_dynamic_range_media_queries_enabled_;
  }

  static bool CSSVideoDynamicRangeMediaQueriesEnabled(const FeatureContext*) { return CSSVideoDynamicRangeMediaQueriesEnabled(); }

  static bool CSSViewTransitionAutoNameEnabled() {
    return is_css_view_transition_auto_name_enabled_;
  }

  static bool CSSViewTransitionAutoNameEnabled(const FeatureContext*) { return CSSViewTransitionAutoNameEnabled(); }

  static bool CustomElementsDisableFormattingFixupsEnabled() {
    return is_custom_elements_disable_formatting_fixups_enabled_;
  }

  static bool CustomElementsDisableFormattingFixupsEnabled(const FeatureContext*) { return CustomElementsDisableFormattingFixupsEnabled(); }

  static bool CustomizableComboboxEnabled() {
    if (!AppearanceBaseEnabled())
      return false;
    return is_customizable_combobox_enabled_;
  }

  static bool CustomizableComboboxEnabled(const FeatureContext*) { return CustomizableComboboxEnabled(); }

  static bool CustomizableSelectMultiplePopupEnabled() {
    return is_customizable_select_multiple_popup_enabled_;
  }

  static bool CustomizableSelectMultiplePopupEnabled(const FeatureContext*) { return CustomizableSelectMultiplePopupEnabled(); }

  static bool CustomScrollbarApplyMinimumThumbLengthEnabled() {
    return is_custom_scrollbar_apply_minimum_thumb_length_enabled_;
  }

  static bool CustomScrollbarApplyMinimumThumbLengthEnabled(const FeatureContext*) { return CustomScrollbarApplyMinimumThumbLengthEnabled(); }

  static bool DatabaseEnabled() {
    return is_database_enabled_;
  }

  static bool DatabaseEnabled(const FeatureContext*) { return DatabaseEnabled(); }

  static bool DateTimeLocalArabicCommaWorkaroundEnabled() {
    return is_date_time_local_arabic_comma_workaround_enabled_;
  }

  static bool DateTimeLocalArabicCommaWorkaroundEnabled(const FeatureContext*) { return DateTimeLocalArabicCommaWorkaroundEnabled(); }

  static bool DecoupleComputedBorderWidthFromStyleEnabled() {
    return is_decouple_computed_border_width_from_style_enabled_;
  }

  static bool DecoupleComputedBorderWidthFromStyleEnabled(const FeatureContext*) { return DecoupleComputedBorderWidthFromStyleEnabled(); }

  static bool DecoupleResolvedColumnRuleWidthFromStyleEnabled() {
    return is_decouple_resolved_column_rule_width_from_style_enabled_;
  }

  static bool DecoupleResolvedColumnRuleWidthFromStyleEnabled(const FeatureContext*) { return DecoupleResolvedColumnRuleWidthFromStyleEnabled(); }

  static bool DelegatesFocusTextControlInputFixEnabled() {
    return is_delegates_focus_text_control_input_fix_enabled_;
  }

  static bool DelegatesFocusTextControlInputFixEnabled(const FeatureContext*) { return DelegatesFocusTextControlInputFixEnabled(); }

  static bool DeleteTextInContentEditableBeforeRemovingChildrenEnabled() {
    return is_delete_text_in_content_editable_before_removing_children_enabled_;
  }

  static bool DeleteTextInContentEditableBeforeRemovingChildrenEnabled(const FeatureContext*) { return DeleteTextInContentEditableBeforeRemovingChildrenEnabled(); }

  static bool DesktopCaptureDisableLocalEchoControlEnabled() {
    return is_desktop_capture_disable_local_echo_control_enabled_;
  }

  static bool DesktopCaptureDisableLocalEchoControlEnabled(const FeatureContext*) { return DesktopCaptureDisableLocalEchoControlEnabled(); }

  static bool DesktopPWAsAdditionalWindowingControlsEnabled() {
    return is_desktop_pw_as_additional_windowing_controls_enabled_;
  }

  static bool DesktopPWAsAdditionalWindowingControlsEnabled(const FeatureContext*) { return DesktopPWAsAdditionalWindowingControlsEnabled(); }

  static bool DesktopPWAsAdditionalWindowingControlsOnMoveEnabled() {
    return is_desktop_pw_as_additional_windowing_controls_on_move_enabled_;
  }

  static bool DesktopPWAsAdditionalWindowingControlsOnMoveEnabled(const FeatureContext*) { return DesktopPWAsAdditionalWindowingControlsOnMoveEnabled(); }

  static bool DeviceAttributesEnabled() {
    return is_device_attributes_enabled_;
  }

  static bool DeviceAttributesEnabled(const FeatureContext*) { return DeviceAttributesEnabled(); }

  static bool DeviceOrientationRequestPermissionEnabled() {
    return is_device_orientation_request_permission_enabled_;
  }

  static bool DeviceOrientationRequestPermissionEnabled(const FeatureContext*) { return DeviceOrientationRequestPermissionEnabled(); }

  static bool DevicePostureEnabled() {
    return is_device_posture_enabled_;
  }

  static bool DevicePostureEnabled(const FeatureContext*) { return DevicePostureEnabled(); }

  static bool DialogCloseWhenOpenRemovedEnabled() {
    return is_dialog_close_when_open_removed_enabled_;
  }

  static bool DialogCloseWhenOpenRemovedEnabled(const FeatureContext*) { return DialogCloseWhenOpenRemovedEnabled(); }

  static bool DialogNewFocusBehaviorEnabled() {
    return is_dialog_new_focus_behavior_enabled_;
  }

  static bool DialogNewFocusBehaviorEnabled(const FeatureContext*) { return DialogNewFocusBehaviorEnabled(); }

  static bool DigitalGoodsV2_1Enabled() {
    return is_digital_goods_v_2_1_enabled_;
  }

  static bool DigitalGoodsV2_1Enabled(const FeatureContext*) { return DigitalGoodsV2_1Enabled(); }

  static bool DirectSocketsEnabled() {
    return is_direct_sockets_enabled_;
  }

  static bool DirectSocketsEnabled(const FeatureContext*);

  static bool DirectSocketsInServiceWorkersEnabled() {
    return is_direct_sockets_in_service_workers_enabled_;
  }

  static bool DirectSocketsInServiceWorkersEnabled(const FeatureContext*) { return DirectSocketsInServiceWorkersEnabled(); }

  static bool DirectSocketsInSharedWorkersEnabled() {
    return is_direct_sockets_in_shared_workers_enabled_;
  }

  static bool DirectSocketsInSharedWorkersEnabled(const FeatureContext*) { return DirectSocketsInSharedWorkersEnabled(); }

  static bool DisableAnchorCenterOnAlignJustifyItemsEnabled() {
    return is_disable_anchor_center_on_align_justify_items_enabled_;
  }

  static bool DisableAnchorCenterOnAlignJustifyItemsEnabled(const FeatureContext*) { return DisableAnchorCenterOnAlignJustifyItemsEnabled(); }

  static bool DisableEllipsisWhenScrolledEnabled() {
    return is_disable_ellipsis_when_scrolled_enabled_;
  }

  static bool DisableEllipsisWhenScrolledEnabled(const FeatureContext*) { return DisableEllipsisWhenScrolledEnabled(); }

  static bool DisableRemoveFormatForPlainTextOnlyEditableDivEnabled() {
    return is_disable_remove_format_for_plain_text_only_editable_div_enabled_;
  }

  static bool DisableRemoveFormatForPlainTextOnlyEditableDivEnabled(const FeatureContext*) { return DisableRemoveFormatForPlainTextOnlyEditableDivEnabled(); }

  static bool DisallowDisconnectedAreaNavigationEnabled() {
    return is_disallow_disconnected_area_navigation_enabled_;
  }

  static bool DisallowDisconnectedAreaNavigationEnabled(const FeatureContext*) { return DisallowDisconnectedAreaNavigationEnabled(); }

  static bool DisallowPickerForReadonlyInputsEnabled() {
    return is_disallow_picker_for_readonly_inputs_enabled_;
  }

  static bool DisallowPickerForReadonlyInputsEnabled(const FeatureContext*) { return DisallowPickerForReadonlyInputsEnabled(); }

  static bool DisconnectWebSocketOnBFCacheEnabled() {
    return is_disconnect_websocket_on_bf_cache_enabled_;
  }

  static bool DisconnectWebSocketOnBFCacheEnabled(const FeatureContext*) { return DisconnectWebSocketOnBFCacheEnabled(); }

  static bool DispatchHiddenVisibilityTransitionsEnabled() {
    return is_dispatch_hidden_visibility_transitions_enabled_;
  }

  static bool DispatchHiddenVisibilityTransitionsEnabled(const FeatureContext*) { return DispatchHiddenVisibilityTransitionsEnabled(); }

  static bool DispatchSelectionchangeEventPerElementEnabled() {
    return is_dispatch_selectionchange_event_per_element_enabled_;
  }

  static bool DispatchSelectionchangeEventPerElementEnabled(const FeatureContext*) { return DispatchSelectionchangeEventPerElementEnabled(); }

  static bool DisplayContentsFocusableEnabled() {
    return is_display_contents_focusable_enabled_;
  }

  static bool DisplayContentsFocusableEnabled(const FeatureContext*) { return DisplayContentsFocusableEnabled(); }

  static bool DisplayCutoutAPIEnabled() {
    return is_display_cutout_api_enabled_;
  }

  static bool DisplayCutoutAPIEnabled(const FeatureContext*) { return DisplayCutoutAPIEnabled(); }

  static bool DocumentActiveViewTransitionEnabled() {
    return is_document_active_view_transition_enabled_;
  }

  static bool DocumentActiveViewTransitionEnabled(const FeatureContext*) { return DocumentActiveViewTransitionEnabled(); }

  static bool DocumentCookieEnabled() {
    return is_document_cookie_enabled_;
  }

  static bool DocumentCookieEnabled(const FeatureContext*) { return DocumentCookieEnabled(); }

  static bool DocumentDomainEnabled() {
    return is_document_domain_enabled_;
  }

  static bool DocumentDomainEnabled(const FeatureContext*) { return DocumentDomainEnabled(); }

  static bool DocumentOpenIframeUnloadEventsEnabled() {
    return is_document_open_iframe_unload_events_enabled_;
  }

  static bool DocumentOpenIframeUnloadEventsEnabled(const FeatureContext*) { return DocumentOpenIframeUnloadEventsEnabled(); }

  static bool DocumentOpenOriginAliasRemovalEnabled() {
    return is_document_open_origin_alias_removal_enabled_;
  }

  static bool DocumentOpenOriginAliasRemovalEnabled(const FeatureContext*) { return DocumentOpenOriginAliasRemovalEnabled(); }

  static bool DocumentOpenSandboxInheritanceRemovalEnabled() {
    return is_document_open_sandbox_inheritance_removal_enabled_;
  }

  static bool DocumentOpenSandboxInheritanceRemovalEnabled(const FeatureContext*) { return DocumentOpenSandboxInheritanceRemovalEnabled(); }

  static bool DocumentPatchingEnabled() {
    return is_document_patching_enabled_;
  }

  static bool DocumentPatchingEnabled(const FeatureContext*) { return DocumentPatchingEnabled(); }

  static bool DocumentPictureInPictureAPIEnabled() {
    return is_document_picture_in_picture_api_enabled_;
  }

  static bool DocumentPictureInPictureAPIEnabled(const FeatureContext*) { return DocumentPictureInPictureAPIEnabled(); }

  static bool DocumentPictureInPicturePreferInitialPlacementEnabled() {
    return is_document_picture_in_picture_prefer_initial_placement_enabled_;
  }

  static bool DocumentPictureInPicturePreferInitialPlacementEnabled(const FeatureContext*) { return DocumentPictureInPicturePreferInitialPlacementEnabled(); }

  static bool DocumentPictureInPictureUserActivationEnabled() {
    return is_document_picture_in_picture_user_activation_enabled_;
  }

  static bool DocumentPictureInPictureUserActivationEnabled(const FeatureContext*) { return DocumentPictureInPictureUserActivationEnabled(); }

  static bool DocumentPolicyDocumentDomainEnabled() {
    return is_document_policy_document_domain_enabled_;
  }

  static bool DocumentPolicyDocumentDomainEnabled(const FeatureContext*) { return DocumentPolicyDocumentDomainEnabled(); }

  static bool DocumentPolicyExpectNoLinkedResourcesEnabled() {
    return is_document_policy_expect_no_linked_resources_enabled_;
  }

  static bool DocumentPolicyExpectNoLinkedResourcesEnabled(const FeatureContext*) { return DocumentPolicyExpectNoLinkedResourcesEnabled(); }

  static bool DocumentPolicyIncludeJSCallStacksInCrashReportsEnabled() {
    return is_document_policy_include_js_call_stacks_in_crash_reports_enabled_;
  }

  static bool DocumentPolicyIncludeJSCallStacksInCrashReportsEnabled(const FeatureContext*) { return DocumentPolicyIncludeJSCallStacksInCrashReportsEnabled(); }

  static bool DocumentPolicyInDedicatedWorkerEnabled() {
    return is_document_policy_in_dedicated_worker_enabled_;
  }

  static bool DocumentPolicyInDedicatedWorkerEnabled(const FeatureContext*) { return DocumentPolicyInDedicatedWorkerEnabled(); }

  static bool DocumentPolicyNetworkEfficiencyGuardrailsEnabled() {
    return is_document_policy_network_efficiency_guardrails_enabled_;
  }

  static bool DocumentPolicyNetworkEfficiencyGuardrailsEnabled(const FeatureContext*) { return DocumentPolicyNetworkEfficiencyGuardrailsEnabled(); }

  static bool DocumentPolicySyncXHREnabled() {
    return is_document_policy_sync_xhr_enabled_;
  }

  static bool DocumentPolicySyncXHREnabled(const FeatureContext*) { return DocumentPolicySyncXHREnabled(); }

  static bool DocumentWriteEnabled() {
    return is_document_write_enabled_;
  }

  static bool DocumentWriteEnabled(const FeatureContext*) { return DocumentWriteEnabled(); }

  static bool DOMActivateBubblesInheritanceEnabled() {
    return is_dom_activate_bubbles_inheritance_enabled_;
  }

  static bool DOMActivateBubblesInheritanceEnabled(const FeatureContext*) { return DOMActivateBubblesInheritanceEnabled(); }

  static bool DontLeakShadowTreesInDragEventsEnabled() {
    return is_dont_leak_shadow_trees_in_drag_events_enabled_;
  }

  static bool DontLeakShadowTreesInDragEventsEnabled(const FeatureContext*) { return DontLeakShadowTreesInDragEventsEnabled(); }

  static bool EditContextAssignmentAsPerSpecEnabled() {
    return is_edit_context_assignment_as_per_spec_enabled_;
  }

  static bool EditContextAssignmentAsPerSpecEnabled(const FeatureContext*) { return EditContextAssignmentAsPerSpecEnabled(); }

  static bool EditContextHandleTextOrSelectionUpdateDuringCompositionEnabled() {
    return is_edit_context_handle_text_or_selection_update_during_composition_enabled_;
  }

  static bool EditContextHandleTextOrSelectionUpdateDuringCompositionEnabled(const FeatureContext*) { return EditContextHandleTextOrSelectionUpdateDuringCompositionEnabled(); }

  static bool EditEmojiTagSequenceEnabled() {
    return is_edit_emoji_tag_sequence_enabled_;
  }

  static bool EditEmojiTagSequenceEnabled(const FeatureContext*) { return EditEmojiTagSequenceEnabled(); }

  static bool EditingLineMovementWithRubyFixEnabled() {
    return is_editing_line_movement_with_ruby_fix_enabled_;
  }

  static bool EditingLineMovementWithRubyFixEnabled(const FeatureContext*) { return EditingLineMovementWithRubyFixEnabled(); }

  static bool ElementCaptureEnabled() {
    return is_element_capture_enabled_;
  }

  static bool ElementCaptureEnabled(const FeatureContext*) { return ElementCaptureEnabled(); }

  static bool ElementInnerTextHandleFirstLineStyleEnabled() {
    return is_element_inner_text_handle_first_line_style_enabled_;
  }

  static bool ElementInnerTextHandleFirstLineStyleEnabled(const FeatureContext*) { return ElementInnerTextHandleFirstLineStyleEnabled(); }

  static bool ElementInternalsBehaviorsEnabled() {
    return is_element_internals_behaviors_enabled_;
  }

  static bool ElementInternalsBehaviorsEnabled(const FeatureContext*) { return ElementInternalsBehaviorsEnabled(); }

  static bool ElementSpecificReadOnlyConstraintValidationEnabled() {
    return is_element_specific_read_only_constraint_validation_enabled_;
  }

  static bool ElementSpecificReadOnlyConstraintValidationEnabled(const FeatureContext*) { return ElementSpecificReadOnlyConstraintValidationEnabled(); }

  static bool EmailVerificationProtocolEnabled() {
    return is_email_verification_protocol_enabled_;
  }

  static bool EmailVerificationProtocolEnabled(const FeatureContext*) { return EmailVerificationProtocolEnabled(); }

  static bool EmojiMonochromeRenderingEnabled() {
    return is_emoji_monochrome_rendering_enabled_;
  }

  static bool EmojiMonochromeRenderingEnabled(const FeatureContext*) { return EmojiMonochromeRenderingEnabled(); }

  static bool EndpointInclusiveCommitStylesEnabled() {
    return is_endpoint_inclusive_commit_styles_enabled_;
  }

  static bool EndpointInclusiveCommitStylesEnabled(const FeatureContext*) { return EndpointInclusiveCommitStylesEnabled(); }

  static bool EnforceAnonymityExposureEnabled() {
    return is_enforce_anonymity_exposure_enabled_;
  }

  static bool EnforceAnonymityExposureEnabled(const FeatureContext*) { return EnforceAnonymityExposureEnabled(); }

  static bool EnterInOpenShadowRootsEnabled() {
    return is_enter_in_open_shadow_roots_enabled_;
  }

  static bool EnterInOpenShadowRootsEnabled(const FeatureContext*) { return EnterInOpenShadowRootsEnabled(); }

  static bool EntropyIgnoredForFirstVideoFrameLCPEnabled() {
    return is_entropy_ignored_for_first_video_frame_lcp_enabled_;
  }

  static bool EntropyIgnoredForFirstVideoFrameLCPEnabled(const FeatureContext*) { return EntropyIgnoredForFirstVideoFrameLCPEnabled(); }

  static bool EventPseudoTargetPropertyEnabled() {
    if (!CSSPseudoElementInterfaceEnabled())
      return false;
    return is_event_pseudo_target_property_enabled_;
  }

  static bool EventPseudoTargetPropertyEnabled(const FeatureContext*) { return EventPseudoTargetPropertyEnabled(); }

  static bool EventTimingInteractionCountEnabled() {
    return is_event_timing_interaction_count_enabled_;
  }

  static bool EventTimingInteractionCountEnabled(const FeatureContext*) { return EventTimingInteractionCountEnabled(); }

  static bool EventTimingTargetSelectorEnabled() {
    return is_event_timing_target_selector_enabled_;
  }

  static bool EventTimingTargetSelectorEnabled(const FeatureContext*) { return EventTimingTargetSelectorEnabled(); }

  static bool EventTriggerEnabled() {
    return is_event_trigger_enabled_;
  }

  static bool EventTriggerEnabled(const FeatureContext*) { return EventTriggerEnabled(); }

  static bool ExperimentalContentSecurityPolicyFeaturesEnabled() {
    return is_experimental_content_security_policy_features_enabled_;
  }

  static bool ExperimentalContentSecurityPolicyFeaturesEnabled(const FeatureContext*) { return ExperimentalContentSecurityPolicyFeaturesEnabled(); }

  static bool ExperimentalJSProfilerMarkersEnabled() {
    return is_experimental_js_profiler_markers_enabled_;
  }

  static bool ExperimentalJSProfilerMarkersEnabled(const FeatureContext*) { return ExperimentalJSProfilerMarkersEnabled(); }

  static bool ExperimentalMachineLearningNeuralNetworkEnabled() {
    return is_experimental_machine_learning_neural_network_enabled_;
  }

  static bool ExperimentalMachineLearningNeuralNetworkEnabled(const FeatureContext*) { return ExperimentalMachineLearningNeuralNetworkEnabled(); }

  static bool ExperimentalPoliciesEnabled() {
    return is_experimental_policies_enabled_;
  }

  static bool ExperimentalPoliciesEnabled(const FeatureContext*) { return ExperimentalPoliciesEnabled(); }

  static bool ExposeCSSFontFeatureValuesRuleEnabled() {
    return is_expose_css_font_feature_values_rule_enabled_;
  }

  static bool ExposeCSSFontFeatureValuesRuleEnabled(const FeatureContext*) { return ExposeCSSFontFeatureValuesRuleEnabled(); }

  static bool ExposeRenderTimeNonTaoDelayedImageEnabled() {
    return is_expose_render_time_non_tao_delayed_image_enabled_;
  }

  static bool ExposeRenderTimeNonTaoDelayedImageEnabled(const FeatureContext*) { return ExposeRenderTimeNonTaoDelayedImageEnabled(); }

  static bool ExtendedShapeCacheEnabled() {
    return is_extended_shape_cache_enabled_;
  }

  static bool ExtendedShapeCacheEnabled(const FeatureContext*) { return ExtendedShapeCacheEnabled(); }

  static bool ExternalPopupMenuClickEventEnabled() {
    return is_external_popup_menu_click_event_enabled_;
  }

  static bool ExternalPopupMenuClickEventEnabled(const FeatureContext*) { return ExternalPopupMenuClickEventEnabled(); }

  static bool EyeDropperAPIEnabled() {
    return is_eye_dropper_api_enabled_;
  }

  static bool EyeDropperAPIEnabled(const FeatureContext*) { return EyeDropperAPIEnabled(); }

  static bool FaceDetectorEnabled() {
    return is_face_detector_enabled_;
  }

  static bool FaceDetectorEnabled(const FeatureContext*) { return FaceDetectorEnabled(); }

  static bool FastPositionIteratorEnabled() {
    return is_fast_position_iterator_enabled_;
  }

  static bool FastPositionIteratorEnabled(const FeatureContext*) { return FastPositionIteratorEnabled(); }

  static bool FedCmEnabled() {
    return is_fed_cm_enabled_;
  }

  static bool FedCmEnabled(const FeatureContext*) { return FedCmEnabled(); }

  static bool FedCmAutofillEnabled() {
    if (FedCmDelegationEnabled())
      return true;
    return is_fed_cm_autofill_enabled_;
  }

  static bool FedCmAutofillEnabled(const FeatureContext*) { return FedCmAutofillEnabled(); }

  static bool FedCmDelegationEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_fed_cm_delegation_enabled_;
  }

  static bool FedCmDelegationEnabled(const FeatureContext*) { return FedCmDelegationEnabled(); }

  static bool FedCmErrorAttributeEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_fed_cm_error_attribute_enabled_;
  }

  static bool FedCmErrorAttributeEnabled(const FeatureContext*) { return FedCmErrorAttributeEnabled(); }

  static bool FedCmIdPRegistrationEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_fed_cm_id_p_registration_enabled_;
  }

  static bool FedCmIdPRegistrationEnabled(const FeatureContext*) { return FedCmIdPRegistrationEnabled(); }

  static bool FedCmLightweightModeEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_fed_cm_lightweight_mode_enabled_;
  }

  static bool FedCmLightweightModeEnabled(const FeatureContext*) { return FedCmLightweightModeEnabled(); }

  static bool FedCmNavigationInterceptionEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_fed_cm_navigation_interception_enabled_;
  }

  static bool FedCmNavigationInterceptionEnabled(const FeatureContext*) { return FedCmNavigationInterceptionEnabled(); }

  static bool FedCmNonStringTokenEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_fed_cm_non_string_token_enabled_;
  }

  static bool FedCmNonStringTokenEnabled(const FeatureContext*) { return FedCmNonStringTokenEnabled(); }

  static bool FencedFramesEnabled() {
    return is_fenced_frames_enabled_;
  }

  static bool FencedFramesEnabled(const FeatureContext*) { return FencedFramesEnabled(); }

  static bool FencedFramesAPIChangesEnabled() {
    return is_fenced_frames_api_changes_enabled_;
  }

  static bool FencedFramesAPIChangesEnabled(const FeatureContext*) { return FencedFramesAPIChangesEnabled(); }

  static bool FencedFramesDefaultModeEnabled() {
    return is_fenced_frames_default_mode_enabled_;
  }

  static bool FencedFramesDefaultModeEnabled(const FeatureContext*) { return FencedFramesDefaultModeEnabled(); }

  static bool FencedFramesLocalUnpartitionedDataAccessEnabled() {
    return is_fenced_frames_local_unpartitioned_data_access_enabled_;
  }

  static bool FencedFramesLocalUnpartitionedDataAccessEnabled(const FeatureContext*) { return FencedFramesLocalUnpartitionedDataAccessEnabled(); }

  static bool FetchBodyBytesEnabled() {
    return is_fetch_body_bytes_enabled_;
  }

  static bool FetchBodyBytesEnabled(const FeatureContext*) { return FetchBodyBytesEnabled(); }

  static bool FetchLaterAPIEnabled() {
    return is_fetch_later_api_enabled_;
  }

  static bool FetchLaterAPIEnabled(const FeatureContext*) { return FetchLaterAPIEnabled(); }

  static bool FetchUploadStreamingEnabled() {
    return is_fetch_upload_streaming_enabled_;
  }

  static bool FetchUploadStreamingEnabled(const FeatureContext*) { return FetchUploadStreamingEnabled(); }

  static bool FileHandlingEnabled() {
    if (!FileSystemAccessLocalEnabled())
      return false;
    return is_file_handling_enabled_;
  }

  static bool FileHandlingEnabled(const FeatureContext*) { return FileHandlingEnabled(); }

  static bool FileHandlingIconsEnabled() {
    if (!FileHandlingEnabled())
      return false;
    return is_file_handling_icons_enabled_;
  }

  static bool FileHandlingIconsEnabled(const FeatureContext*) { return FileHandlingIconsEnabled(); }

  static bool FileSystemEnabled() {
    return is_file_system_enabled_;
  }

  static bool FileSystemEnabled(const FeatureContext*) { return FileSystemEnabled(); }

  static bool FileSystemAccessEnabled() {
    if (FileSystemAccessLocalEnabled())
      return true;
    if (FileSystemAccessOriginPrivateEnabled())
      return true;
    return is_file_system_access_enabled_;
  }

  static bool FileSystemAccessEnabled(const FeatureContext*) { return FileSystemAccessEnabled(); }

  static bool FileSystemAccessAPIExperimentalEnabled() {
    return is_file_system_access_api_experimental_enabled_;
  }

  static bool FileSystemAccessAPIExperimentalEnabled(const FeatureContext*) { return FileSystemAccessAPIExperimentalEnabled(); }

  static bool FileSystemAccessGetCloudIdentifiersEnabled() {
    return is_file_system_access_get_cloud_identifiers_enabled_;
  }

  static bool FileSystemAccessGetCloudIdentifiersEnabled(const FeatureContext*) { return FileSystemAccessGetCloudIdentifiersEnabled(); }

  static bool FileSystemAccessLocalEnabled() {
    return is_file_system_access_local_enabled_;
  }

  static bool FileSystemAccessLocalEnabled(const FeatureContext*) { return FileSystemAccessLocalEnabled(); }

  static bool FileSystemAccessLockingSchemeEnabled() {
    return is_file_system_access_locking_scheme_enabled_;
  }

  static bool FileSystemAccessLockingSchemeEnabled(const FeatureContext*) { return FileSystemAccessLockingSchemeEnabled(); }

  static bool FileSystemAccessOriginPrivateEnabled() {
    return is_file_system_access_origin_private_enabled_;
  }

  static bool FileSystemAccessOriginPrivateEnabled(const FeatureContext*) { return FileSystemAccessOriginPrivateEnabled(); }

  static bool FileSystemAccessRevokeReadOnRemoveEnabled() {
    if (!FileSystemAccessWriteModeEnabled())
      return false;
    return is_file_system_access_revoke_read_on_remove_enabled_;
  }

  static bool FileSystemAccessRevokeReadOnRemoveEnabled(const FeatureContext*) { return FileSystemAccessRevokeReadOnRemoveEnabled(); }

  static bool FileSystemAccessWriteModeEnabled() {
    return is_file_system_access_write_mode_enabled_;
  }

  static bool FileSystemAccessWriteModeEnabled(const FeatureContext*) { return FileSystemAccessWriteModeEnabled(); }

  static bool FileSystemObserverEnabled() {
    if (!FileSystemAccessEnabled())
      return false;
    return is_file_system_observer_enabled_;
  }

  static bool FileSystemObserverEnabled(const FeatureContext*) { return FileSystemObserverEnabled(); }

  static bool FileSystemObserverUnobserveEnabled() {
    return is_file_system_observer_unobserve_enabled_;
  }

  static bool FileSystemObserverUnobserveEnabled(const FeatureContext*) { return FileSystemObserverUnobserveEnabled(); }

  static bool FilterableSelectEnabled() {
    return is_filterable_select_enabled_;
  }

  static bool FilterableSelectEnabled(const FeatureContext*) { return FilterableSelectEnabled(); }

  static bool FilterContainerLevelStylesEnabled() {
    return is_filter_container_level_styles_enabled_;
  }

  static bool FilterContainerLevelStylesEnabled(const FeatureContext*) { return FilterContainerLevelStylesEnabled(); }

  static bool FilteringPrimitivesEnabled() {
    if (FilterableSelectEnabled())
      return true;
    if (CustomizableComboboxEnabled())
      return true;
    return is_filtering_primitives_enabled_;
  }

  static bool FilteringPrimitivesEnabled(const FeatureContext*) { return FilteringPrimitivesEnabled(); }

  static bool FindFirstMisspellingEndWhenNonEditableEnabled() {
    return is_find_first_misspelling_end_when_non_editable_enabled_;
  }

  static bool FindFirstMisspellingEndWhenNonEditableEnabled(const FeatureContext*) { return FindFirstMisspellingEndWhenNonEditableEnabled(); }

  static bool FirstLineOnListItemEnabled() {
    return is_first_line_on_list_item_enabled_;
  }

  static bool FirstLineOnListItemEnabled(const FeatureContext*) { return FirstLineOnListItemEnabled(); }

  static bool FirstLineTextMetricsEnabled() {
    return is_first_line_text_metrics_enabled_;
  }

  static bool FirstLineTextMetricsEnabled(const FeatureContext*) { return FirstLineTextMetricsEnabled(); }

  static bool FixHTMLFormControlElementIsReadOnlyEnabled() {
    return is_fix_html_form_control_element_is_read_only_enabled_;
  }

  static bool FixHTMLFormControlElementIsReadOnlyEnabled(const FeatureContext*) { return FixHTMLFormControlElementIsReadOnlyEnabled(); }

  static bool FixJustifyQueryCommandValueEnabled() {
    return is_fix_justify_query_command_value_enabled_;
  }

  static bool FixJustifyQueryCommandValueEnabled(const FeatureContext*) { return FixJustifyQueryCommandValueEnabled(); }

  static bool FixLinebreakForPreTagEnabled() {
    return is_fix_linebreak_for_pre_tag_enabled_;
  }

  static bool FixLinebreakForPreTagEnabled(const FeatureContext*) { return FixLinebreakForPreTagEnabled(); }

  static bool FixMapElementEmptyNameBugEnabled() {
    return is_fix_map_element_empty_name_bug_enabled_;
  }

  static bool FixMapElementEmptyNameBugEnabled(const FeatureContext*) { return FixMapElementEmptyNameBugEnabled(); }

  static bool FixMarkerSuppressionForAppearanceAutoEnabled() {
    return is_fix_marker_suppression_for_appearance_auto_enabled_;
  }

  static bool FixMarkerSuppressionForAppearanceAutoEnabled(const FeatureContext*) { return FixMarkerSuppressionForAppearanceAutoEnabled(); }

  static bool FixNextPositionCalculationInInsertListEnabled() {
    return is_fix_next_position_calculation_in_insert_list_enabled_;
  }

  static bool FixNextPositionCalculationInInsertListEnabled(const FeatureContext*) { return FixNextPositionCalculationInInsertListEnabled(); }

  static bool FixStrikethroughToggleInEmptyContentEditableEnabled() {
    return is_fix_strikethrough_toggle_in_empty_content_editable_enabled_;
  }

  static bool FixStrikethroughToggleInEmptyContentEditableEnabled(const FeatureContext*) { return FixStrikethroughToggleInEmptyContentEditableEnabled(); }

  static bool FixVisualRectRemoteViewportTransformEnabled() {
    return is_fix_visual_rect_remote_viewport_transform_enabled_;
  }

  static bool FixVisualRectRemoteViewportTransformEnabled(const FeatureContext*) { return FixVisualRectRemoteViewportTransformEnabled(); }

  static bool FledgeEnabled() {
    return is_fledge_enabled_;
  }

  static bool FledgeEnabled(const FeatureContext*) { return FledgeEnabled(); }

  static bool FledgeAuctionDealSupportEnabled() {
    return is_fledge_auction_deal_support_enabled_;
  }

  static bool FledgeAuctionDealSupportEnabled(const FeatureContext*) { return FledgeAuctionDealSupportEnabled(); }

  static bool FledgeBiddingAndAuctionServerAPIMultiSellerEnabled() {
    return is_fledge_bidding_and_auction_server_api_multi_seller_enabled_;
  }

  static bool FledgeBiddingAndAuctionServerAPIMultiSellerEnabled(const FeatureContext*) { return FledgeBiddingAndAuctionServerAPIMultiSellerEnabled(); }

  static bool FledgeClickinessEnabled() {
    return is_fledge_clickiness_enabled_;
  }

  static bool FledgeClickinessEnabled(const FeatureContext*) { return FledgeClickinessEnabled(); }

  static bool FledgeCustomMaxAuctionAdComponentsEnabled() {
    return is_fledge_custom_max_auction_ad_components_enabled_;
  }

  static bool FledgeCustomMaxAuctionAdComponentsEnabled(const FeatureContext*) { return FledgeCustomMaxAuctionAdComponentsEnabled(); }

  static bool FledgeDeprecatedRenderURLReplacementsEnabled() {
    return is_fledge_deprecated_render_url_replacements_enabled_;
  }

  static bool FledgeDeprecatedRenderURLReplacementsEnabled(const FeatureContext*) { return FledgeDeprecatedRenderURLReplacementsEnabled(); }

  static bool FledgeDirectFromSellerSignalsHeaderAdSlotEnabled() {
    return is_fledge_direct_from_seller_signals_header_ad_slot_enabled_;
  }

  static bool FledgeDirectFromSellerSignalsHeaderAdSlotEnabled(const FeatureContext*) { return FledgeDirectFromSellerSignalsHeaderAdSlotEnabled(); }

  static bool FledgeDirectFromSellerSignalsWebBundlesEnabled() {
    return is_fledge_direct_from_seller_signals_web_bundles_enabled_;
  }

  static bool FledgeDirectFromSellerSignalsWebBundlesEnabled(const FeatureContext*) { return FledgeDirectFromSellerSignalsWebBundlesEnabled(); }

  static bool FledgeMultiBidEnabled() {
    return is_fledge_multi_bid_enabled_;
  }

  static bool FledgeMultiBidEnabled(const FeatureContext*) { return FledgeMultiBidEnabled(); }

  static bool FledgePrivateModelTrainingEnabled() {
    return is_fledge_private_model_training_enabled_;
  }

  static bool FledgePrivateModelTrainingEnabled(const FeatureContext*) { return FledgePrivateModelTrainingEnabled(); }

  static bool FledgeRealTimeReportingEnabled() {
    return is_fledge_real_time_reporting_enabled_;
  }

  static bool FledgeRealTimeReportingEnabled(const FeatureContext*) { return FledgeRealTimeReportingEnabled(); }

  static bool FledgeSellerNonceEnabled() {
    return is_fledge_seller_nonce_enabled_;
  }

  static bool FledgeSellerNonceEnabled(const FeatureContext*) { return FledgeSellerNonceEnabled(); }

  static bool FledgeSellerScriptExecutionModeEnabled() {
    return is_fledge_seller_script_execution_mode_enabled_;
  }

  static bool FledgeSellerScriptExecutionModeEnabled(const FeatureContext*) { return FledgeSellerScriptExecutionModeEnabled(); }

  static bool FledgeTrustedSignalsKVv1CreativeScanningEnabled() {
    return is_fledge_trusted_signals_k_vv_1_creative_scanning_enabled_;
  }

  static bool FledgeTrustedSignalsKVv1CreativeScanningEnabled(const FeatureContext*) { return FledgeTrustedSignalsKVv1CreativeScanningEnabled(); }

  static bool FledgeTrustedSignalsKVv2ContextualDataEnabled() {
    if (!FledgeTrustedSignalsKVv2SupportEnabled())
      return false;
    return is_fledge_trusted_signals_k_vv_2_contextual_data_enabled_;
  }

  static bool FledgeTrustedSignalsKVv2ContextualDataEnabled(const FeatureContext*) { return FledgeTrustedSignalsKVv2ContextualDataEnabled(); }

  static bool FledgeTrustedSignalsKVv2SupportEnabled() {
    return is_fledge_trusted_signals_k_vv_2_support_enabled_;
  }

  static bool FledgeTrustedSignalsKVv2SupportEnabled(const FeatureContext*) { return FledgeTrustedSignalsKVv2SupportEnabled(); }

  static bool FlexWrapBalanceEnabled() {
    return is_flex_wrap_balance_enabled_;
  }

  static bool FlexWrapBalanceEnabled(const FeatureContext*) { return FlexWrapBalanceEnabled(); }

  static bool FontAccessEnabled() {
    return is_font_access_enabled_;
  }

  static bool FontAccessEnabled(const FeatureContext*) { return FontAccessEnabled(); }

  static bool FontDataServiceEnabled() {
    return is_font_data_service_enabled_;
  }

  static bool FontDataServiceEnabled(const FeatureContext*) { return FontDataServiceEnabled(); }

  static bool FontFallbackForTabSizeEnabled() {
    return is_font_fallback_for_tab_size_enabled_;
  }

  static bool FontFallbackForTabSizeEnabled(const FeatureContext*) { return FontFallbackForTabSizeEnabled(); }

  static bool FontFamilyPostscriptMatchingCTMigrationEnabled() {
    return is_font_family_postscript_matching_ct_migration_enabled_;
  }

  static bool FontFamilyPostscriptMatchingCTMigrationEnabled(const FeatureContext*) { return FontFamilyPostscriptMatchingCTMigrationEnabled(); }

  static bool FontFamilyStyleMatchingCTMigrationEnabled() {
    return is_font_family_style_matching_ct_migration_enabled_;
  }

  static bool FontFamilyStyleMatchingCTMigrationEnabled(const FeatureContext*) { return FontFamilyStyleMatchingCTMigrationEnabled(); }

  static bool FontFeatureSettingsDescriptorEnabled() {
    return is_font_feature_settings_descriptor_enabled_;
  }

  static bool FontFeatureSettingsDescriptorEnabled(const FeatureContext*) { return FontFeatureSettingsDescriptorEnabled(); }

  static bool FontFormatAvar2Enabled() {
    return is_font_format_avar_2_enabled_;
  }

  static bool FontFormatAvar2Enabled(const FeatureContext*) { return FontFormatAvar2Enabled(); }

  static bool FontLanguageOverrideEnabled() {
    return is_font_language_override_enabled_;
  }

  static bool FontLanguageOverrideEnabled(const FeatureContext*) { return FontLanguageOverrideEnabled(); }

  static bool FontMatchAliasesAsLastResortEnabled() {
    return is_font_match_aliases_as_last_resort_enabled_;
  }

  static bool FontMatchAliasesAsLastResortEnabled(const FeatureContext*) { return FontMatchAliasesAsLastResortEnabled(); }

  static bool FontStyleObliqueZeroDegreeAsNormalEnabled() {
    return is_font_style_oblique_zero_degree_as_normal_enabled_;
  }

  static bool FontStyleObliqueZeroDegreeAsNormalEnabled(const FeatureContext*) { return FontStyleObliqueZeroDegreeAsNormalEnabled(); }

  static bool FontVariationSettingsDescriptorEnabled() {
    return is_font_variation_settings_descriptor_enabled_;
  }

  static bool FontVariationSettingsDescriptorEnabled(const FeatureContext*) { return FontVariationSettingsDescriptorEnabled(); }

  static bool ForcedColorsEnabled() {
    return is_forced_colors_enabled_;
  }

  static bool ForcedColorsEnabled(const FeatureContext*) { return ForcedColorsEnabled(); }

  static bool ForceEagerMeasureMemoryEnabled() {
    return is_force_eager_measure_memory_enabled_;
  }

  static bool ForceEagerMeasureMemoryEnabled(const FeatureContext*) { return ForceEagerMeasureMemoryEnabled(); }

  static bool ForceReduceMotionEnabled() {
    return is_force_reduce_motion_enabled_;
  }

  static bool ForceReduceMotionEnabled(const FeatureContext*) { return ForceReduceMotionEnabled(); }

  static bool FractionalScrollOffsetsEnabled() {
    return is_fractional_scroll_offsets_enabled_;
  }

  static bool FractionalScrollOffsetsEnabled(const FeatureContext*) { return FractionalScrollOffsetsEnabled(); }

  static bool FragmentedOofInCbEnabled() {
    return is_fragmented_oof_in_cb_enabled_;
  }

  static bool FragmentedOofInCbEnabled(const FeatureContext*) { return FragmentedOofInCbEnabled(); }

  static bool FreezeFramesOnVisibilityEnabled() {
    return is_freeze_frames_on_visibility_enabled_;
  }

  static bool FreezeFramesOnVisibilityEnabled(const FeatureContext*) { return FreezeFramesOnVisibilityEnabled(); }

  static bool GamepadMultitouchEnabled() {
    return is_gamepad_multitouch_enabled_;
  }

  static bool GamepadMultitouchEnabled(const FeatureContext*) { return GamepadMultitouchEnabled(); }

  static bool GamepadRawInputChangeEventEnabled() {
    return is_gamepad_raw_input_change_event_enabled_;
  }

  static bool GamepadRawInputChangeEventEnabled(const FeatureContext*) { return GamepadRawInputChangeEventEnabled(); }

  static bool GamepadWindowEventHandlersEnabled() {
    return is_gamepad_window_event_handlers_enabled_;
  }

  static bool GamepadWindowEventHandlersEnabled(const FeatureContext*) { return GamepadWindowEventHandlersEnabled(); }

  static bool GeolocationElementEnabled() {
    return is_geolocation_element_enabled_;
  }

  static bool GeolocationElementEnabled(const FeatureContext*) { return GeolocationElementEnabled(); }

  static bool GeometryMapperSingularTransformFixEnabled() {
    return is_geometry_mapper_singular_transform_fix_enabled_;
  }

  static bool GeometryMapperSingularTransformFixEnabled(const FeatureContext*) { return GeometryMapperSingularTransformFixEnabled(); }

  static bool GeometryUtilsEnabled() {
    return is_geometry_utils_enabled_;
  }

  static bool GeometryUtilsEnabled(const FeatureContext*) { return GeometryUtilsEnabled(); }

  static bool GeometryUtilsForCSSPseudoElementEnabled() {
    if (!CSSPseudoElementInterfaceEnabled())
      return false;
    return is_geometry_utils_for_css_pseudo_element_enabled_;
  }

  static bool GeometryUtilsForCSSPseudoElementEnabled(const FeatureContext*) { return GeometryUtilsForCSSPseudoElementEnabled(); }

  static bool GetAllScreensMediaEnabled() {
    if (!GetDisplayMediaEnabled())
      return false;
    return is_get_all_screens_media_enabled_;
  }

  static bool GetAllScreensMediaEnabled(const FeatureContext*) { return GetAllScreensMediaEnabled(); }

  static bool GetComputedStyleOutsideFlatTreeEnabled() {
    return is_get_computed_style_outside_flat_tree_enabled_;
  }

  static bool GetComputedStyleOutsideFlatTreeEnabled(const FeatureContext*) { return GetComputedStyleOutsideFlatTreeEnabled(); }

  static bool GetDisplayMediaEnabled() {
    return is_get_display_media_enabled_;
  }

  static bool GetDisplayMediaEnabled(const FeatureContext*) { return GetDisplayMediaEnabled(); }

  static bool GetDisplayMediaRequiresUserActivationEnabled() {
    if (!GetDisplayMediaEnabled())
      return false;
    return is_get_display_media_requires_user_activation_enabled_;
  }

  static bool GetDisplayMediaRequiresUserActivationEnabled(const FeatureContext*) { return GetDisplayMediaRequiresUserActivationEnabled(); }

  static bool GetDisplayMediaWindowAudioCaptureEnabled() {
    return is_get_display_media_window_audio_capture_enabled_;
  }

  static bool GetDisplayMediaWindowAudioCaptureEnabled(const FeatureContext*);

  static bool GetElementsByNameOnlyHTMLElementsEnabled() {
    return is_get_elements_by_name_only_html_elements_enabled_;
  }

  static bool GetElementsByNameOnlyHTMLElementsEnabled(const FeatureContext*) { return GetElementsByNameOnlyHTMLElementsEnabled(); }

  static bool GetUserMediaEchoCancellationModesEnabled() {
    return is_get_user_media_echo_cancellation_modes_enabled_;
  }

  static bool GetUserMediaEchoCancellationModesEnabled(const FeatureContext*) { return GetUserMediaEchoCancellationModesEnabled(); }

  static bool GroupEffectEnabled() {
    return is_group_effect_enabled_;
  }

  static bool GroupEffectEnabled(const FeatureContext*) { return GroupEffectEnabled(); }

  static bool HandleDeletionAtStartAndEndBoundaryContainingHiddenElementEnabled() {
    return is_handle_deletion_at_start_and_end_boundary_containing_hidden_element_enabled_;
  }

  static bool HandleDeletionAtStartAndEndBoundaryContainingHiddenElementEnabled(const FeatureContext*) { return HandleDeletionAtStartAndEndBoundaryContainingHiddenElementEnabled(); }

  static bool HandleDisconnectedSelectionDuringDOMChangesEnabled() {
    return is_handle_disconnected_selection_during_dom_changes_enabled_;
  }

  static bool HandleDisconnectedSelectionDuringDOMChangesEnabled(const FeatureContext*) { return HandleDisconnectedSelectionDuringDOMChangesEnabled(); }

  static bool HandleInvalidMaskImageWithBackdropFilterEnabled() {
    return is_handle_invalid_mask_image_with_backdrop_filter_enabled_;
  }

  static bool HandleInvalidMaskImageWithBackdropFilterEnabled(const FeatureContext*) { return HandleInvalidMaskImageWithBackdropFilterEnabled(); }

  static bool HandleShadowDOMInSubstringUtilEnabled() {
    return is_handle_shadow_dom_in_substring_util_enabled_;
  }

  static bool HandleShadowDOMInSubstringUtilEnabled(const FeatureContext*) { return HandleShadowDOMInSubstringUtilEnabled(); }

  static bool HandwritingRecognitionEnabled() {
    return is_handwriting_recognition_enabled_;
  }

  static bool HandwritingRecognitionEnabled(const FeatureContext*) { return HandwritingRecognitionEnabled(); }

  static bool HasUAVisualTransitionEnabled() {
    return is_has_ua_visual_transition_enabled_;
  }

  static bool HasUAVisualTransitionEnabled(const FeatureContext*) { return HasUAVisualTransitionEnabled(); }

  static bool HeadingOffsetEnabled() {
    return is_heading_offset_enabled_;
  }

  static bool HeadingOffsetEnabled(const FeatureContext*) { return HeadingOffsetEnabled(); }

  static bool HideVideoControlsWhenUnneededEnabled() {
    return is_hide_video_controls_when_unneeded_enabled_;
  }

  static bool HideVideoControlsWhenUnneededEnabled(const FeatureContext*) { return HideVideoControlsWhenUnneededEnabled(); }

  static bool HighlightsFromPointEnabled() {
    return is_highlights_from_point_enabled_;
  }

  static bool HighlightsFromPointEnabled(const FeatureContext*) { return HighlightsFromPointEnabled(); }

  static bool HitTestBorderRadiusForStackingContextEnabled() {
    return is_hit_test_border_radius_for_stacking_context_enabled_;
  }

  static bool HitTestBorderRadiusForStackingContextEnabled(const FeatureContext*) { return HitTestBorderRadiusForStackingContextEnabled(); }

  static bool HitTestContainerTransformStateForPreserve3dEnabled() {
    return is_hit_test_container_transform_state_for_preserve_3d_enabled_;
  }

  static bool HitTestContainerTransformStateForPreserve3dEnabled(const FeatureContext*) { return HitTestContainerTransformStateForPreserve3dEnabled(); }

  static bool HstsTopLevelNavigationsOnlyEnabled() {
    return is_hsts_top_level_navigations_only_enabled_;
  }

  static bool HstsTopLevelNavigationsOnlyEnabled(const FeatureContext*) { return HstsTopLevelNavigationsOnlyEnabled(); }

  static bool HTMLAdoptionAlgorithmNewStepsEnabled() {
    return is_html_adoption_algorithm_new_steps_enabled_;
  }

  static bool HTMLAdoptionAlgorithmNewStepsEnabled(const FeatureContext*) { return HTMLAdoptionAlgorithmNewStepsEnabled(); }

  static bool HTMLCommandActionsV2Enabled() {
    return is_html_command_actions_v_2_enabled_;
  }

  static bool HTMLCommandActionsV2Enabled(const FeatureContext*) { return HTMLCommandActionsV2Enabled(); }

  static bool HTMLCommandElementRemovalEnabled() {
    return is_html_command_element_removal_enabled_;
  }

  static bool HTMLCommandElementRemovalEnabled(const FeatureContext*) { return HTMLCommandElementRemovalEnabled(); }

  static bool HTMLCommandForScrollCommandsEnabled() {
    return is_html_command_for_scroll_commands_enabled_;
  }

  static bool HTMLCommandForScrollCommandsEnabled(const FeatureContext*) { return HTMLCommandForScrollCommandsEnabled(); }

  static bool HTMLElementScrollParentEnabled() {
    return is_html_element_scroll_parent_enabled_;
  }

  static bool HTMLElementScrollParentEnabled(const FeatureContext*) { return HTMLElementScrollParentEnabled(); }

  static bool HTMLImageElementActualNaturalSizeEnabled() {
    return is_html_image_element_actual_natural_size_enabled_;
  }

  static bool HTMLImageElementActualNaturalSizeEnabled(const FeatureContext*) { return HTMLImageElementActualNaturalSizeEnabled(); }

  static bool HTMLInputElementDropWebkitClearButtonEnabled() {
    return is_html_input_element_drop_webkit_clear_button_enabled_;
  }

  static bool HTMLInputElementDropWebkitClearButtonEnabled(const FeatureContext*) { return HTMLInputElementDropWebkitClearButtonEnabled(); }

  static bool HTMLInterestForInterestButtonPseudoEnabled() {
    return is_html_interest_for_interest_button_pseudo_enabled_;
  }

  static bool HTMLInterestForInterestButtonPseudoEnabled(const FeatureContext*) { return HTMLInterestForInterestButtonPseudoEnabled(); }

  static bool HTMLLinkElementAttributeValueChangesEnabled() {
    return is_html_link_element_attribute_value_changes_enabled_;
  }

  static bool HTMLLinkElementAttributeValueChangesEnabled(const FeatureContext*) { return HTMLLinkElementAttributeValueChangesEnabled(); }

  static bool HTMLParserYieldAndDelayOftenForTestingEnabled() {
    return is_html_parser_yield_and_delay_often_for_testing_enabled_;
  }

  static bool HTMLParserYieldAndDelayOftenForTestingEnabled(const FeatureContext*) { return HTMLParserYieldAndDelayOftenForTestingEnabled(); }

  static bool HTMLParserYieldByUserTimingEnabled() {
    return is_html_parser_yield_by_user_timing_enabled_;
  }

  static bool HTMLParserYieldByUserTimingEnabled(const FeatureContext*) { return HTMLParserYieldByUserTimingEnabled(); }

  static bool HTMLPrintingArtifactAnnotationsEnabled() {
    return is_html_printing_artifact_annotations_enabled_;
  }

  static bool HTMLPrintingArtifactAnnotationsEnabled(const FeatureContext*) { return HTMLPrintingArtifactAnnotationsEnabled(); }

  static bool HTMLProcessingInstructionEnabled() {
    return is_html_processing_instruction_enabled_;
  }

  static bool HTMLProcessingInstructionEnabled(const FeatureContext*) { return HTMLProcessingInstructionEnabled(); }

  static bool ICUCapitalizationEnabled() {
    return is_icu_capitalization_enabled_;
  }

  static bool ICUCapitalizationEnabled(const FeatureContext*) { return ICUCapitalizationEnabled(); }

  static bool IgnoreLetterSpacingInCursiveScriptsEnabled() {
    return is_ignore_letter_spacing_in_cursive_scripts_enabled_;
  }

  static bool IgnoreLetterSpacingInCursiveScriptsEnabled(const FeatureContext*) { return IgnoreLetterSpacingInCursiveScriptsEnabled(); }

  static bool ImageDataPixelFormatEnabled() {
    return is_image_data_pixel_format_enabled_;
  }

  static bool ImageDataPixelFormatEnabled(const FeatureContext*) { return ImageDataPixelFormatEnabled(); }

  static bool ImageDocumentUseLayoutWidthEnabled() {
    return is_image_document_use_layout_width_enabled_;
  }

  static bool ImageDocumentUseLayoutWidthEnabled(const FeatureContext*) { return ImageDocumentUseLayoutWidthEnabled(); }

  static bool ImageSrcsetReselectionEnabled() {
    return is_image_srcset_reselection_enabled_;
  }

  static bool ImageSrcsetReselectionEnabled(const FeatureContext*) { return ImageSrcsetReselectionEnabled(); }

  static bool ImplicitRootScrollerEnabled() {
    return is_implicit_root_scroller_enabled_;
  }

  static bool ImplicitRootScrollerEnabled(const FeatureContext*) { return ImplicitRootScrollerEnabled(); }

  static bool ImprovedSourceRetargetingEnabled() {
    return is_improved_source_retargeting_enabled_;
  }

  static bool ImprovedSourceRetargetingEnabled(const FeatureContext*) { return ImprovedSourceRetargetingEnabled(); }

  static bool InertElementNonEditableEnabled() {
    return is_inert_element_non_editable_enabled_;
  }

  static bool InertElementNonEditableEnabled(const FeatureContext*) { return InertElementNonEditableEnabled(); }

  static bool InfiniteCullRectEnabled() {
    return is_infinite_cull_rect_enabled_;
  }

  static bool InfiniteCullRectEnabled(const FeatureContext*) { return InfiniteCullRectEnabled(); }

  static bool InheritUserModifyWithoutContenteditableEnabled() {
    return is_inherit_user_modify_without_contenteditable_enabled_;
  }

  static bool InheritUserModifyWithoutContenteditableEnabled(const FeatureContext*) { return InheritUserModifyWithoutContenteditableEnabled(); }

  static bool InlineBlockLineNavigationEnabled() {
    return is_inline_block_line_navigation_enabled_;
  }

  static bool InlineBlockLineNavigationEnabled(const FeatureContext*) { return InlineBlockLineNavigationEnabled(); }

  static bool InlineScriptCacheHintEnabled() {
    return is_inline_script_cache_hint_enabled_;
  }

  static bool InlineScriptCacheHintEnabled(const FeatureContext*) { return InlineScriptCacheHintEnabled(); }

  static bool InnerHTMLParserFastpathLogFailureEnabled() {
    return is_inner_html_parser_fastpath_log_failure_enabled_;
  }

  static bool InnerHTMLParserFastpathLogFailureEnabled(const FeatureContext*) { return InnerHTMLParserFastpathLogFailureEnabled(); }

  static bool InputEventDataTransferForInsertCmdEnabled() {
    return is_input_event_data_transfer_for_insert_cmd_enabled_;
  }

  static bool InputEventDataTransferForInsertCmdEnabled(const FeatureContext*) { return InputEventDataTransferForInsertCmdEnabled(); }

  static bool InputEventsDeleteNonCollapsedSelectionEnabled() {
    return is_input_events_delete_non_collapsed_selection_enabled_;
  }

  static bool InputEventsDeleteNonCollapsedSelectionEnabled(const FeatureContext*) { return InputEventsDeleteNonCollapsedSelectionEnabled(); }

  static bool InputInSelectEnabled() {
    return is_input_in_select_enabled_;
  }

  static bool InputInSelectEnabled(const FeatureContext*) { return InputInSelectEnabled(); }

  static bool InputMultipleFieldsUIEnabled() {
    return is_input_multiple_fields_ui_enabled_;
  }

  static bool InputMultipleFieldsUIEnabled(const FeatureContext*) { return InputMultipleFieldsUIEnabled(); }

  static bool InsertBlockquoteBeforeOuterBlockEnabled() {
    return is_insert_blockquote_before_outer_block_enabled_;
  }

  static bool InsertBlockquoteBeforeOuterBlockEnabled(const FeatureContext*) { return InsertBlockquoteBeforeOuterBlockEnabled(); }

  static bool InstalledAppEnabled() {
    return is_installed_app_enabled_;
  }

  static bool InstalledAppEnabled(const FeatureContext*) { return InstalledAppEnabled(); }

  static bool InstallOnDeviceSpeechRecognitionEnabled() {
    return is_install_on_device_speech_recognition_enabled_;
  }

  static bool InstallOnDeviceSpeechRecognitionEnabled(const FeatureContext*) { return InstallOnDeviceSpeechRecognitionEnabled(); }

  static bool IntegrityPolicyScriptEnabled() {
    return is_integrity_policy_script_enabled_;
  }

  static bool IntegrityPolicyScriptEnabled(const FeatureContext*) { return IntegrityPolicyScriptEnabled(); }

  static bool InterestEventsNonComposedEnabled() {
    return is_interest_events_non_composed_enabled_;
  }

  static bool InterestEventsNonComposedEnabled(const FeatureContext*) { return InterestEventsNonComposedEnabled(); }

  static bool InterestGroupsInSharedStorageWorkletEnabled() {
    return is_interest_groups_in_shared_storage_worklet_enabled_;
  }

  static bool InterestGroupsInSharedStorageWorkletEnabled(const FeatureContext*) { return InterestGroupsInSharedStorageWorkletEnabled(); }

  static bool IntersectionObserverCompositedAnimationsForceMainFramesEnabled() {
    return is_intersection_observer_composited_animations_force_main_frames_enabled_;
  }

  static bool IntersectionObserverCompositedAnimationsForceMainFramesEnabled(const FeatureContext*) { return IntersectionObserverCompositedAnimationsForceMainFramesEnabled(); }

  static bool InvertedColorsEnabled() {
    return is_inverted_colors_enabled_;
  }

  static bool InvertedColorsEnabled(const FeatureContext*) { return InvertedColorsEnabled(); }

  static bool InvisibleSVGAnimationThrottlingEnabled() {
    return is_invisible_svg_animation_throttling_enabled_;
  }

  static bool InvisibleSVGAnimationThrottlingEnabled(const FeatureContext*) { return InvisibleSVGAnimationThrottlingEnabled(); }

  static bool JavaScriptSourcePhaseImportsEnabled() {
    return is_java_script_source_phase_imports_enabled_;
  }

  static bool JavaScriptSourcePhaseImportsEnabled(const FeatureContext*) { return JavaScriptSourcePhaseImportsEnabled(); }

  static bool KeyboardAccessibleTooltipEnabled() {
    return is_keyboard_accessible_tooltip_enabled_;
  }

  static bool KeyboardAccessibleTooltipEnabled(const FeatureContext*) { return KeyboardAccessibleTooltipEnabled(); }

  static bool KeySystemTrackConfigurationEncryptionSchemeEnabled() {
    return is_key_system_track_configuration_encryption_scheme_enabled_;
  }

  static bool KeySystemTrackConfigurationEncryptionSchemeEnabled(const FeatureContext*) { return KeySystemTrackConfigurationEncryptionSchemeEnabled(); }

  static bool LabelInteractiveContentCheckBeforeHandlerEnabled() {
    return is_label_interactive_content_check_before_handler_enabled_;
  }

  static bool LabelInteractiveContentCheckBeforeHandlerEnabled(const FeatureContext*) { return LabelInteractiveContentCheckBeforeHandlerEnabled(); }

  static bool LangAttributeAwareFormControlUIEnabled() {
    return is_lang_attribute_aware_form_control_ui_enabled_;
  }

  static bool LangAttributeAwareFormControlUIEnabled(const FeatureContext*) { return LangAttributeAwareFormControlUIEnabled(); }

  static bool LanguageDetectionAPIEnabled() {
    return is_language_detection_api_enabled_;
  }

  static bool LanguageDetectionAPIEnabled(const FeatureContext*) { return LanguageDetectionAPIEnabled(); }

  static bool LanguageDetectionAPIForWorkersEnabled() {
    return is_language_detection_api_for_workers_enabled_;
  }

  static bool LanguageDetectionAPIForWorkersEnabled(const FeatureContext*) { return LanguageDetectionAPIForWorkersEnabled(); }

  static bool LayoutBoxRectGettersUseFragmentsEnabled() {
    return is_layout_box_rect_getters_use_fragments_enabled_;
  }

  static bool LayoutBoxRectGettersUseFragmentsEnabled(const FeatureContext*) { return LayoutBoxRectGettersUseFragmentsEnabled(); }

  static bool LayoutIgnoreMarginsForStickyEnabled() {
    return is_layout_ignore_margins_for_sticky_enabled_;
  }

  static bool LayoutIgnoreMarginsForStickyEnabled(const FeatureContext*) { return LayoutIgnoreMarginsForStickyEnabled(); }

  static bool LayoutImageEmptyNaturalSizeBeforeSizeAvailableEnabled() {
    return is_layout_image_empty_natural_size_before_size_available_enabled_;
  }

  static bool LayoutImageEmptyNaturalSizeBeforeSizeAvailableEnabled(const FeatureContext*) { return LayoutImageEmptyNaturalSizeBeforeSizeAvailableEnabled(); }

  static bool LayoutTableCellAlignmentSafeEnabled() {
    return is_layout_table_cell_alignment_safe_enabled_;
  }

  static bool LayoutTableCellAlignmentSafeEnabled(const FeatureContext*) { return LayoutTableCellAlignmentSafeEnabled(); }

  static bool LazyImageConformantLoadEventTimingEnabled() {
    return is_lazy_image_conformant_load_event_timing_enabled_;
  }

  static bool LazyImageConformantLoadEventTimingEnabled(const FeatureContext*) { return LazyImageConformantLoadEventTimingEnabled(); }

  static bool LazyLoadVideoAndAudioEnabled() {
    return is_lazy_load_video_and_audio_enabled_;
  }

  static bool LazyLoadVideoAndAudioEnabled(const FeatureContext*) { return LazyLoadVideoAndAudioEnabled(); }

  static bool LeftClickToHandleSuggestionEnabled() {
    return is_left_click_to_handle_suggestion_enabled_;
  }

  static bool LeftClickToHandleSuggestionEnabled(const FeatureContext*) { return LeftClickToHandleSuggestionEnabled(); }

  static bool LightDismissFromClickEnabled() {
    return is_light_dismiss_from_click_enabled_;
  }

  static bool LightDismissFromClickEnabled(const FeatureContext*) { return LightDismissFromClickEnabled(); }

  static bool LinkBlurImprovementEnabled() {
    return is_link_blur_improvement_enabled_;
  }

  static bool LinkBlurImprovementEnabled(const FeatureContext*) { return LinkBlurImprovementEnabled(); }

  static bool ListOwnerMustHaveCSSBoxEnabled() {
    return is_list_owner_must_have_css_box_enabled_;
  }

  static bool ListOwnerMustHaveCSSBoxEnabled(const FeatureContext*) { return ListOwnerMustHaveCSSBoxEnabled(); }

  static bool LocalNetworkAccessPermissionPolicyEnabled() {
    return is_local_network_access_permission_policy_enabled_;
  }

  static bool LocalNetworkAccessPermissionPolicyEnabled(const FeatureContext*) { return LocalNetworkAccessPermissionPolicyEnabled(); }

  static bool LocalNetworkAccessSplitPermissionsEnabled() {
    return is_local_network_access_split_permissions_enabled_;
  }

  static bool LocalNetworkAccessSplitPermissionsEnabled(const FeatureContext*) { return LocalNetworkAccessSplitPermissionsEnabled(); }

  static bool LocalNetworkAccessWebRTCEnabled() {
    return is_local_network_access_web_rtc_enabled_;
  }

  static bool LocalNetworkAccessWebRTCEnabled(const FeatureContext*) { return LocalNetworkAccessWebRTCEnabled(); }

  static bool LockedModeEnabled() {
    return is_locked_mode_enabled_;
  }

  static bool LockedModeEnabled(const FeatureContext*) { return LockedModeEnabled(); }

  static bool LogicalStartOfLineBlockFallbackEnabled() {
    return is_logical_start_of_line_block_fallback_enabled_;
  }

  static bool LogicalStartOfLineBlockFallbackEnabled(const FeatureContext*) { return LogicalStartOfLineBlockFallbackEnabled(); }

  static bool LoginElementEnabled() {
    if (!FedCmEnabled())
      return false;
    return is_login_element_enabled_;
  }

  static bool LoginElementEnabled(const FeatureContext*) { return LoginElementEnabled(); }

  static bool LongAnimationFrameSourceCharPositionEnabled() {
    return is_long_animation_frame_source_char_position_enabled_;
  }

  static bool LongAnimationFrameSourceCharPositionEnabled(const FeatureContext*) { return LongAnimationFrameSourceCharPositionEnabled(); }

  static bool LongAnimationFrameSourceLineColumnEnabled() {
    if (LongAnimationFrameSourceLineColumnInterfaceEnabled())
      return true;
    return is_long_animation_frame_source_line_column_enabled_;
  }

  static bool LongAnimationFrameSourceLineColumnEnabled(const FeatureContext*) { return LongAnimationFrameSourceLineColumnEnabled(); }

  static bool LongAnimationFrameSourceLineColumnInterfaceEnabled() {
    return is_long_animation_frame_source_line_column_interface_enabled_;
  }

  static bool LongAnimationFrameSourceLineColumnInterfaceEnabled(const FeatureContext*) { return LongAnimationFrameSourceLineColumnInterfaceEnabled(); }

  static bool LongPressLinkSelectTextEnabled() {
    return is_long_press_link_select_text_enabled_;
  }

  static bool LongPressLinkSelectTextEnabled(const FeatureContext*) { return LongPressLinkSelectTextEnabled(); }

  static bool LongTaskFromLongAnimationFrameEnabled() {
    return is_long_task_from_long_animation_frame_enabled_;
  }

  static bool LongTaskFromLongAnimationFrameEnabled(const FeatureContext*) { return LongTaskFromLongAnimationFrameEnabled(); }

  static bool MacCharacterFallbackCacheEnabled() {
    return is_mac_character_fallback_cache_enabled_;
  }

  static bool MacCharacterFallbackCacheEnabled(const FeatureContext*) { return MacCharacterFallbackCacheEnabled(); }

  static bool MacDisableCtrlHomeEndEnabled() {
    return is_mac_disable_ctrl_home_end_enabled_;
  }

  static bool MacDisableCtrlHomeEndEnabled(const FeatureContext*) { return MacDisableCtrlHomeEndEnabled(); }

  static bool MachineLearningNeuralNetworkEnabled() {
    return is_machine_learning_neural_network_enabled_;
  }

  static bool MachineLearningNeuralNetworkEnabled(const FeatureContext*) { return MachineLearningNeuralNetworkEnabled(); }

  static bool MacSystemClipboardPermissionCheckEnabled() {
    return is_mac_system_clipboard_permission_check_enabled_;
  }

  static bool MacSystemClipboardPermissionCheckEnabled(const FeatureContext*) { return MacSystemClipboardPermissionCheckEnabled(); }

  static bool ManagedConfigurationEnabled() {
    return is_managed_configuration_enabled_;
  }

  static bool ManagedConfigurationEnabled(const FeatureContext*) { return ManagedConfigurationEnabled(); }

  static bool ManualTextEnabled() {
    return is_manual_text_enabled_;
  }

  static bool ManualTextEnabled(const FeatureContext*) { return ManualTextEnabled(); }

  static bool MarginTrimEnabled() {
    return is_margin_trim_enabled_;
  }

  static bool MarginTrimEnabled(const FeatureContext*) { return MarginTrimEnabled(); }

  static bool MaskDeserializationTimeForCrossOriginMessagesEnabled() {
    return is_mask_deserialization_time_for_cross_origin_messages_enabled_;
  }

  static bool MaskDeserializationTimeForCrossOriginMessagesEnabled(const FeatureContext*) { return MaskDeserializationTimeForCrossOriginMessagesEnabled(); }

  static bool MathMLOperatorRTLMirroringEnabled() {
    return is_mathml_operator_rtl_mirroring_enabled_;
  }

  static bool MathMLOperatorRTLMirroringEnabled(const FeatureContext*) { return MathMLOperatorRTLMirroringEnabled(); }

  static bool MathMLSerializationOnCopyEnabled() {
    return is_mathml_serialization_on_copy_enabled_;
  }

  static bool MathMLSerializationOnCopyEnabled(const FeatureContext*) { return MathMLSerializationOnCopyEnabled(); }

  static bool MathMLSkipMtrTagInAncestorWrappingEnabled() {
    return is_mathml_skip_mtr_tag_in_ancestor_wrapping_enabled_;
  }

  static bool MathMLSkipMtrTagInAncestorWrappingEnabled(const FeatureContext*) { return MathMLSkipMtrTagInAncestorWrappingEnabled(); }

  static bool MeasureMemoryEnabled() {
    return is_measure_memory_enabled_;
  }

  static bool MeasureMemoryEnabled(const FeatureContext*) { return MeasureMemoryEnabled(); }

  static bool MediaCapabilitiesEncodingInfoEnabled() {
    return is_media_capabilities_encoding_info_enabled_;
  }

  static bool MediaCapabilitiesEncodingInfoEnabled(const FeatureContext*) { return MediaCapabilitiesEncodingInfoEnabled(); }

  static bool MediaCapabilitiesSpatialAudioEnabled() {
    return is_media_capabilities_spatial_audio_enabled_;
  }

  static bool MediaCapabilitiesSpatialAudioEnabled(const FeatureContext*) { return MediaCapabilitiesSpatialAudioEnabled(); }

  static bool MediaCaptureEnabled() {
    return is_media_capture_enabled_;
  }

  static bool MediaCaptureEnabled(const FeatureContext*) { return MediaCaptureEnabled(); }

  static bool MediaCaptureCameraControlsEnabled() {
    return is_media_capture_camera_controls_enabled_;
  }

  static bool MediaCaptureCameraControlsEnabled(const FeatureContext*) { return MediaCaptureCameraControlsEnabled(); }

  static bool MediaCaptureVoiceIsolationEnabled() {
    return is_media_capture_voice_isolation_enabled_;
  }

  static bool MediaCaptureVoiceIsolationEnabled(const FeatureContext*) { return MediaCaptureVoiceIsolationEnabled(); }

  static bool MediaControlsExpandGestureEnabled() {
    return is_media_controls_expand_gesture_enabled_;
  }

  static bool MediaControlsExpandGestureEnabled(const FeatureContext*) { return MediaControlsExpandGestureEnabled(); }

  static bool MediaControlsOverlayPlayButtonEnabled() {
    return is_media_controls_overlay_play_button_enabled_;
  }

  static bool MediaControlsOverlayPlayButtonEnabled(const FeatureContext*) { return MediaControlsOverlayPlayButtonEnabled(); }

  static bool MediaElementVolumeGreaterThanOneEnabled() {
    return is_media_element_volume_greater_than_one_enabled_;
  }

  static bool MediaElementVolumeGreaterThanOneEnabled(const FeatureContext*) { return MediaElementVolumeGreaterThanOneEnabled(); }

  static bool MediaEngagementBypassAutoplayPoliciesEnabled() {
    return is_media_engagement_bypass_autoplay_policies_enabled_;
  }

  static bool MediaEngagementBypassAutoplayPoliciesEnabled(const FeatureContext*) { return MediaEngagementBypassAutoplayPoliciesEnabled(); }

  static bool MediaLatencyHintEnabled() {
    return is_media_latency_hint_enabled_;
  }

  static bool MediaLatencyHintEnabled(const FeatureContext*) { return MediaLatencyHintEnabled(); }

  static bool MediaQueryNavigationControlsEnabled() {
    return is_media_query_navigation_controls_enabled_;
  }

  static bool MediaQueryNavigationControlsEnabled(const FeatureContext*) { return MediaQueryNavigationControlsEnabled(); }

  static bool MediaSessionEnabled() {
    return is_media_session_enabled_;
  }

  static bool MediaSessionEnabled(const FeatureContext*) { return MediaSessionEnabled(); }

  static bool MediaSessionChapterInformationEnabled() {
    return is_media_session_chapter_information_enabled_;
  }

  static bool MediaSessionChapterInformationEnabled(const FeatureContext*) { return MediaSessionChapterInformationEnabled(); }

  static bool MediaSourceExperimentalEnabled() {
    return is_media_source_experimental_enabled_;
  }

  static bool MediaSourceExperimentalEnabled(const FeatureContext*) { return MediaSourceExperimentalEnabled(); }

  static bool MediaStreamTrackTransferEnabled() {
    return is_media_stream_track_transfer_enabled_;
  }

  static bool MediaStreamTrackTransferEnabled(const FeatureContext*) { return MediaStreamTrackTransferEnabled(); }

  static bool MediaStreamTrackWebSpeechEnabled() {
    return is_media_stream_track_web_speech_enabled_;
  }

  static bool MediaStreamTrackWebSpeechEnabled(const FeatureContext*) { return MediaStreamTrackWebSpeechEnabled(); }

  static bool MemoryConsumerForNGShapeCacheEnabled() {
    return is_memory_consumer_for_ng_shape_cache_enabled_;
  }

  static bool MemoryConsumerForNGShapeCacheEnabled(const FeatureContext*) { return MemoryConsumerForNGShapeCacheEnabled(); }

  static bool MenuElementsEnabled() {
    return is_menu_elements_enabled_;
  }

  static bool MenuElementsEnabled(const FeatureContext*) { return MenuElementsEnabled(); }

  static bool MergeFixedLayersEnabled() {
    return is_merge_fixed_layers_enabled_;
  }

  static bool MergeFixedLayersEnabled(const FeatureContext*) { return MergeFixedLayersEnabled(); }

  static bool MergeStickyLayersEnabled() {
    return is_merge_sticky_layers_enabled_;
  }

  static bool MergeStickyLayersEnabled(const FeatureContext*) { return MergeStickyLayersEnabled(); }

  static bool MessagePortCloseEventEnabled() {
    return is_message_port_close_event_enabled_;
  }

  static bool MessagePortCloseEventEnabled(const FeatureContext*) { return MessagePortCloseEventEnabled(); }

  static bool MiddleClickAutoscrollEnabled() {
    return is_middle_click_autoscroll_enabled_;
  }

  static bool MiddleClickAutoscrollEnabled(const FeatureContext*) { return MiddleClickAutoscrollEnabled(); }

  static bool MixedContentAutoupgradesUseIsMixedContentRestrictedInFrameEnabled() {
    return is_mixed_content_autoupgrades_use_is_mixed_content_restricted_in_frame_enabled_;
  }

  static bool MixedContentAutoupgradesUseIsMixedContentRestrictedInFrameEnabled(const FeatureContext*) { return MixedContentAutoupgradesUseIsMixedContentRestrictedInFrameEnabled(); }

  static bool MobileLayoutThemeEnabled() {
    return is_mobile_layout_theme_enabled_;
  }

  static bool MobileLayoutThemeEnabled(const FeatureContext*) { return MobileLayoutThemeEnabled(); }

  static bool ModifyParagraphCrossEditingoundaryEnabled() {
    return is_modify_paragraph_cross_editingoundary_enabled_;
  }

  static bool ModifyParagraphCrossEditingoundaryEnabled(const FeatureContext*) { return ModifyParagraphCrossEditingoundaryEnabled(); }

  static bool ModulePreloadReferrerEnabled() {
    return is_module_preload_referrer_enabled_;
  }

  static bool ModulePreloadReferrerEnabled(const FeatureContext*) { return ModulePreloadReferrerEnabled(); }

  static bool ModulePreloadStyleJsonEnabled() {
    return is_module_preload_style_json_enabled_;
  }

  static bool ModulePreloadStyleJsonEnabled(const FeatureContext*) { return ModulePreloadStyleJsonEnabled(); }

  static bool MojoJSEnabled() {
    return get_is_mojo_js_enabled_();
  }

  static bool MojoJSEnabled(const FeatureContext*) { return MojoJSEnabled(); }

  static bool MojoJSTestEnabled() {
    return get_is_mojo_js_test_enabled_();
  }

  static bool MojoJSTestEnabled(const FeatureContext*) { return MojoJSTestEnabled(); }

  static bool MoveEndingSelectionToListChildEnabled() {
    return is_move_ending_selection_to_list_child_enabled_;
  }

  static bool MoveEndingSelectionToListChildEnabled(const FeatureContext*) { return MoveEndingSelectionToListChildEnabled(); }

  static bool MulticolColumnWrappingEnabled() {
    return is_multicol_column_wrapping_enabled_;
  }

  static bool MulticolColumnWrappingEnabled(const FeatureContext*) { return MulticolColumnWrappingEnabled(); }

  static bool NavigateEventAddHandlerOnPrecommitEnabled() {
    return is_navigate_event_add_handler_on_precommit_enabled_;
  }

  static bool NavigateEventAddHandlerOnPrecommitEnabled(const FeatureContext*) { return NavigateEventAddHandlerOnPrecommitEnabled(); }

  static bool NavigateEventClearOnRestoreEnabled() {
    return is_navigate_event_clear_on_restore_enabled_;
  }

  static bool NavigateEventClearOnRestoreEnabled(const FeatureContext*) { return NavigateEventClearOnRestoreEnabled(); }

  static bool NavigateEventDeferCrossDocumentCommitEnabled() {
    return is_navigate_event_defer_cross_document_commit_enabled_;
  }

  static bool NavigateEventDeferCrossDocumentCommitEnabled(const FeatureContext*) { return NavigateEventDeferCrossDocumentCommitEnabled(); }

  static bool NavigationEventTimingEnabled() {
    return is_navigation_event_timing_enabled_;
  }

  static bool NavigationEventTimingEnabled(const FeatureContext*) { return NavigationEventTimingEnabled(); }

  static bool NavigatorContentUtilsEnabled() {
    return is_navigator_content_utils_enabled_;
  }

  static bool NavigatorContentUtilsEnabled(const FeatureContext*) { return NavigatorContentUtilsEnabled(); }

  static bool NetInfoConstantTypeEnabled() {
    return is_net_info_constant_type_enabled_;
  }

  static bool NetInfoConstantTypeEnabled(const FeatureContext*) { return NetInfoConstantTypeEnabled(); }

  static bool NetInfoDownlinkMaxEnabled() {
    return is_net_info_downlink_max_enabled_;
  }

  static bool NetInfoDownlinkMaxEnabled(const FeatureContext*) { return NetInfoDownlinkMaxEnabled(); }

  static bool NewHTMLSettingMethodsEnabled() {
    if (!SetHTMLCanRunScriptsEnabled())
      return false;
    if (!StreamingSanitizerEnabled())
      return false;
    if (!TrustedTypesCreateParserOptionsEnabled())
      return false;
    return is_new_html_setting_methods_enabled_;
  }

  static bool NewHTMLSettingMethodsEnabled(const FeatureContext*) { return NewHTMLSettingMethodsEnabled(); }

  static bool NoExtendSelectionToUserSelectNoneOutOfFlowEnabled() {
    return is_no_extend_selection_to_user_select_none_out_of_flow_enabled_;
  }

  static bool NoExtendSelectionToUserSelectNoneOutOfFlowEnabled(const FeatureContext*) { return NoExtendSelectionToUserSelectNoneOutOfFlowEnabled(); }

  static bool NoFontAntialiasingEnabled() {
    return is_no_font_antialiasing_enabled_;
  }

  static bool NoFontAntialiasingEnabled(const FeatureContext*) { return NoFontAntialiasingEnabled(); }

  static bool NoIdleEncodingForWebTestsEnabled() {
    return is_no_idle_encoding_for_web_tests_enabled_;
  }

  static bool NoIdleEncodingForWebTestsEnabled(const FeatureContext*) { return NoIdleEncodingForWebTestsEnabled(); }

  static bool NonEmptyBlockquotesOnOutdentingEnabled() {
    return is_non_empty_blockquotes_on_outdenting_enabled_;
  }

  static bool NonEmptyBlockquotesOnOutdentingEnabled(const FeatureContext*) { return NonEmptyBlockquotesOnOutdentingEnabled(); }

  static bool NonEmptyVisibleTextSelectionForTextFragmentEnabled() {
    return is_non_empty_visible_text_selection_for_text_fragment_enabled_;
  }

  static bool NonEmptyVisibleTextSelectionForTextFragmentEnabled(const FeatureContext*) { return NonEmptyVisibleTextSelectionForTextFragmentEnabled(); }

  static bool NonStandardAppearanceValueSliderVerticalEnabled() {
    return is_non_standard_appearance_value_slider_vertical_enabled_;
  }

  static bool NonStandardAppearanceValueSliderVerticalEnabled(const FeatureContext*) { return NonStandardAppearanceValueSliderVerticalEnabled(); }

  static bool NormalizeLineEndingsInInsertTextEnabled() {
    return is_normalize_line_endings_in_insert_text_enabled_;
  }

  static bool NormalizeLineEndingsInInsertTextEnabled(const FeatureContext*) { return NormalizeLineEndingsInInsertTextEnabled(); }

  static bool NormalizeNbspForPasteAndDropEnabled() {
    return is_normalize_nbsp_for_paste_and_drop_enabled_;
  }

  static bool NormalizeNbspForPasteAndDropEnabled(const FeatureContext*) { return NormalizeNbspForPasteAndDropEnabled(); }

  static bool NotificationConstructorEnabled() {
    return is_notification_constructor_enabled_;
  }

  static bool NotificationConstructorEnabled(const FeatureContext*) { return NotificationConstructorEnabled(); }

  static bool NotificationContentImageEnabled() {
    return is_notification_content_image_enabled_;
  }

  static bool NotificationContentImageEnabled(const FeatureContext*) { return NotificationContentImageEnabled(); }

  static bool NotificationsEnabled() {
    return is_notifications_enabled_;
  }

  static bool NotificationsEnabled(const FeatureContext*) { return NotificationsEnabled(); }

  static bool NumberInputFullWidthCharsEnabled() {
    return is_number_input_full_width_chars_enabled_;
  }

  static bool NumberInputFullWidthCharsEnabled(const FeatureContext*) { return NumberInputFullWidthCharsEnabled(); }

  static bool OffMainThreadCSSPaintEnabled() {
    return is_off_main_thread_css_paint_enabled_;
  }

  static bool OffMainThreadCSSPaintEnabled(const FeatureContext*) { return OffMainThreadCSSPaintEnabled(); }

  static bool OffscreenCanvasGetContextAttributesEnabled() {
    return is_offscreen_canvas_get_context_attributes_enabled_;
  }

  static bool OffscreenCanvasGetContextAttributesEnabled(const FeatureContext*) { return OffscreenCanvasGetContextAttributesEnabled(); }

  static bool OffsetPathTransformUpdateFixEnabled() {
    return is_offset_path_transform_update_fix_enabled_;
  }

  static bool OffsetPathTransformUpdateFixEnabled(const FeatureContext*) { return OffsetPathTransformUpdateFixEnabled(); }

  static bool OmitBlurEventOnElementRemovalEnabled() {
    return is_omit_blur_event_on_element_removal_enabled_;
  }

  static bool OmitBlurEventOnElementRemovalEnabled(const FeatureContext*) { return OmitBlurEventOnElementRemovalEnabled(); }

  static bool OnDeviceWebSpeechAvailableEnabled() {
    return is_on_device_web_speech_available_enabled_;
  }

  static bool OnDeviceWebSpeechAvailableEnabled(const FeatureContext*) { return OnDeviceWebSpeechAvailableEnabled(); }

  static bool OnDeviceWebSpeechQualityEnabled() {
    return is_on_device_web_speech_quality_enabled_;
  }

  static bool OnDeviceWebSpeechQualityEnabled(const FeatureContext*) { return OnDeviceWebSpeechQualityEnabled(); }

  static bool OpenPopoverInvokerRestrictToSameTreeScopeEnabled() {
    return is_open_popover_invoker_restrict_to_same_tree_scope_enabled_;
  }

  static bool OpenPopoverInvokerRestrictToSameTreeScopeEnabled(const FeatureContext*) { return OpenPopoverInvokerRestrictToSameTreeScopeEnabled(); }

  static bool OrientationEventEnabled() {
    return is_orientation_event_enabled_;
  }

  static bool OrientationEventEnabled(const FeatureContext*) { return OrientationEventEnabled(); }

  static bool OriginAPIEnabled() {
    return is_origin_api_enabled_;
  }

  static bool OriginAPIEnabled(const FeatureContext*) { return OriginAPIEnabled(); }

  static bool OriginIsolationHeaderEnabled() {
    return is_origin_isolation_header_enabled_;
  }

  static bool OriginIsolationHeaderEnabled(const FeatureContext*) { return OriginIsolationHeaderEnabled(); }

  static bool OriginPolicyEnabled() {
    return is_origin_policy_enabled_;
  }

  static bool OriginPolicyEnabled(const FeatureContext*) { return OriginPolicyEnabled(); }

  static bool OutlineDrawAutoStyleZeroWidthEnabled() {
    return is_outline_draw_auto_style_zero_width_enabled_;
  }

  static bool OutlineDrawAutoStyleZeroWidthEnabled(const FeatureContext*) { return OutlineDrawAutoStyleZeroWidthEnabled(); }

  static bool OverlayGlobalRuleRemovalEnabled() {
    return is_overlay_global_rule_removal_enabled_;
  }

  static bool OverlayGlobalRuleRemovalEnabled(const FeatureContext*) { return OverlayGlobalRuleRemovalEnabled(); }

  static bool OverlayPropertyEnabled() {
    return is_overlay_property_enabled_;
  }

  static bool OverlayPropertyEnabled(const FeatureContext*) { return OverlayPropertyEnabled(); }

  static bool OverscrollGesturesEnabled() {
    return is_overscroll_gestures_enabled_;
  }

  static bool OverscrollGesturesEnabled(const FeatureContext*) { return OverscrollGesturesEnabled(); }

  static bool PagePopupEnabled() {
    return is_page_popup_enabled_;
  }

  static bool PagePopupEnabled(const FeatureContext*) { return PagePopupEnabled(); }

  static bool PagePopupCopyPasteEnabled() {
    if (!PagePopupEnabled())
      return false;
    return is_page_popup_copy_paste_enabled_;
  }

  static bool PagePopupCopyPasteEnabled(const FeatureContext*) { return PagePopupCopyPasteEnabled(); }

  static bool PageRevealEventEnabled() {
    return is_page_reveal_event_enabled_;
  }

  static bool PageRevealEventEnabled(const FeatureContext*) { return PageRevealEventEnabled(); }

  static bool PageSwapEventEnabled() {
    return is_page_swap_event_enabled_;
  }

  static bool PageSwapEventEnabled(const FeatureContext*) { return PageSwapEventEnabled(); }

  static bool PaintHoldingForIframesEnabled() {
    return is_paint_holding_for_iframes_enabled_;
  }

  static bool PaintHoldingForIframesEnabled(const FeatureContext*) { return PaintHoldingForIframesEnabled(); }

  static bool PaintOffsetTranslationForCompositedEnabled() {
    return is_paint_offset_translation_for_composited_enabled_;
  }

  static bool PaintOffsetTranslationForCompositedEnabled(const FeatureContext*) { return PaintOffsetTranslationForCompositedEnabled(); }

  static bool PaintTimingMixinEnabled() {
    return is_paint_timing_mixin_enabled_;
  }

  static bool PaintTimingMixinEnabled(const FeatureContext*) { return PaintTimingMixinEnabled(); }

  static bool PaintUnderInvalidationCheckingEnabled() {
    return is_paint_under_invalidation_checking_enabled_;
  }

  static bool PaintUnderInvalidationCheckingEnabled(const FeatureContext*) { return PaintUnderInvalidationCheckingEnabled(); }

  static bool PartialCompletionNotAllowedInMoveParagraphsEnabled() {
    return is_partial_completion_not_allowed_in_move_paragraphs_enabled_;
  }

  static bool PartialCompletionNotAllowedInMoveParagraphsEnabled(const FeatureContext*) { return PartialCompletionNotAllowedInMoveParagraphsEnabled(); }

  static bool PartitionVisitedLinkDatabaseWithSelfLinksEnabled() {
    return is_partition_visited_link_database_with_self_links_enabled_;
  }

  static bool PartitionVisitedLinkDatabaseWithSelfLinksEnabled(const FeatureContext*) { return PartitionVisitedLinkDatabaseWithSelfLinksEnabled(); }

  static bool PasswordRevealEnabled() {
    return is_password_reveal_enabled_;
  }

  static bool PasswordRevealEnabled(const FeatureContext*) { return PasswordRevealEnabled(); }

  static bool PaymentAppEnabled() {
    return is_payment_app_enabled_;
  }

  static bool PaymentAppEnabled(const FeatureContext*) { return PaymentAppEnabled(); }

  static bool PaymentLinkDetectionEnabled() {
    return is_payment_link_detection_enabled_;
  }

  static bool PaymentLinkDetectionEnabled(const FeatureContext*) { return PaymentLinkDetectionEnabled(); }

  static bool PaymentMethodChangeEventEnabled() {
    if (!PaymentRequestEnabled())
      return false;
    return is_payment_method_change_event_enabled_;
  }

  static bool PaymentMethodChangeEventEnabled(const FeatureContext*) { return PaymentMethodChangeEventEnabled(); }

  static bool PaymentRequestEnabled() {
    return is_payment_request_enabled_;
  }

  static bool PaymentRequestEnabled(const FeatureContext*) { return PaymentRequestEnabled(); }

  static bool PerformanceManagerInstrumentationEnabled() {
    return is_performance_manager_instrumentation_enabled_;
  }

  static bool PerformanceManagerInstrumentationEnabled(const FeatureContext*) { return PerformanceManagerInstrumentationEnabled(); }

  static bool PerformanceMarkCustomUserTimingFromSubframeEnabled() {
    return is_performance_mark_custom_user_timing_from_subframe_enabled_;
  }

  static bool PerformanceMarkCustomUserTimingFromSubframeEnabled(const FeatureContext*) { return PerformanceMarkCustomUserTimingFromSubframeEnabled(); }

  static bool PerformanceMarkFeatureUsageEnabled() {
    return is_performance_mark_feature_usage_enabled_;
  }

  static bool PerformanceMarkFeatureUsageEnabled(const FeatureContext*) { return PerformanceMarkFeatureUsageEnabled(); }

  static bool PerformanceNavigationTimingConfidenceEnabled() {
    return is_performance_navigation_timing_confidence_enabled_;
  }

  static bool PerformanceNavigationTimingConfidenceEnabled(const FeatureContext*) { return PerformanceNavigationTimingConfidenceEnabled(); }

  static bool PeriodicBackgroundSyncEnabled() {
    return is_periodic_background_sync_enabled_;
  }

  static bool PeriodicBackgroundSyncEnabled(const FeatureContext*) { return PeriodicBackgroundSyncEnabled(); }

  static bool PermissionsRequestRevokeEnabled() {
    return is_permissions_request_revoke_enabled_;
  }

  static bool PermissionsRequestRevokeEnabled(const FeatureContext*) { return PermissionsRequestRevokeEnabled(); }

  static bool PlaceholderVisibilityEnabled() {
    return is_placeholder_visibility_enabled_;
  }

  static bool PlaceholderVisibilityEnabled(const FeatureContext*) { return PlaceholderVisibilityEnabled(); }

  static bool PointerEventDeviceIdEnabled() {
    return is_pointer_event_device_id_enabled_;
  }

  static bool PointerEventDeviceIdEnabled(const FeatureContext*) { return PointerEventDeviceIdEnabled(); }

  static bool PointerLockOnAndroidEnabled() {
    return is_pointer_lock_on_android_enabled_;
  }

  static bool PointerLockOnAndroidEnabled(const FeatureContext*) { return PointerLockOnAndroidEnabled(); }

  static bool PointerRawUpdateOnlyInSecureContextEnabled() {
    return is_pointer_raw_update_only_in_secure_context_enabled_;
  }

  static bool PointerRawUpdateOnlyInSecureContextEnabled(const FeatureContext*) { return PointerRawUpdateOnlyInSecureContextEnabled(); }

  static bool PopoverHintNewBehaviorEnabled() {
    return is_popover_hint_new_behavior_enabled_;
  }

  static bool PopoverHintNewBehaviorEnabled(const FeatureContext*) { return PopoverHintNewBehaviorEnabled(); }

  static bool PositionOutsideTabSpanCheckSiblingNodeEnabled() {
    return is_position_outside_tab_span_check_sibling_node_enabled_;
  }

  static bool PositionOutsideTabSpanCheckSiblingNodeEnabled(const FeatureContext*) { return PositionOutsideTabSpanCheckSiblingNodeEnabled(); }

  static bool PositionVisibilityIgnoreNonClipAncestorsEnabled() {
    return is_position_visibility_ignore_non_clip_ancestors_enabled_;
  }

  static bool PositionVisibilityIgnoreNonClipAncestorsEnabled(const FeatureContext*) { return PositionVisibilityIgnoreNonClipAncestorsEnabled(); }

  static bool PotentialPermissionsPolicyReportingEnabled() {
    return is_potential_permissions_policy_reporting_enabled_;
  }

  static bool PotentialPermissionsPolicyReportingEnabled(const FeatureContext*) { return PotentialPermissionsPolicyReportingEnabled(); }

  static bool PreciseMemoryInfoEnabled() {
    return is_precise_memory_info_enabled_;
  }

  static bool PreciseMemoryInfoEnabled(const FeatureContext*) { return PreciseMemoryInfoEnabled(); }

  static bool PreferDefaultScrollbarStylesEnabled() {
    return is_prefer_default_scrollbar_styles_enabled_;
  }

  static bool PreferDefaultScrollbarStylesEnabled(const FeatureContext*) { return PreferDefaultScrollbarStylesEnabled(); }

  static bool PreferNonCompositedScrollingEnabled() {
    return is_prefer_non_composited_scrolling_enabled_;
  }

  static bool PreferNonCompositedScrollingEnabled(const FeatureContext*) { return PreferNonCompositedScrollingEnabled(); }

  static bool PrefersReducedDataEnabled() {
    return is_prefers_reduced_data_enabled_;
  }

  static bool PrefersReducedDataEnabled(const FeatureContext*) { return PrefersReducedDataEnabled(); }

  static bool PreloadLinkRelDataUrlsEnabled() {
    return is_preload_link_rel_data_urls_enabled_;
  }

  static bool PreloadLinkRelDataUrlsEnabled(const FeatureContext*) { return PreloadLinkRelDataUrlsEnabled(); }

  static bool Prerender2Enabled() {
    return is_prerender_2_enabled_;
  }

  static bool Prerender2Enabled(const FeatureContext*) { return Prerender2Enabled(); }

  static bool PresentationEnabled() {
    return is_presentation_enabled_;
  }

  static bool PresentationEnabled(const FeatureContext*) { return PresentationEnabled(); }

  static bool PreserveDropEffectEnabled() {
    return is_preserve_drop_effect_enabled_;
  }

  static bool PreserveDropEffectEnabled(const FeatureContext*) { return PreserveDropEffectEnabled(); }

  static bool PreventUndoIfNotEditableEnabled() {
    return is_prevent_undo_if_not_editable_enabled_;
  }

  static bool PreventUndoIfNotEditableEnabled(const FeatureContext*) { return PreventUndoIfNotEditableEnabled(); }

  static bool PrivateAggregationApiErrorReportingEnabled() {
    return is_private_aggregation_api_error_reporting_enabled_;
  }

  static bool PrivateAggregationApiErrorReportingEnabled(const FeatureContext*) { return PrivateAggregationApiErrorReportingEnabled(); }

  static bool PrivateAggregationApiMaxContributionsEnabled() {
    return is_private_aggregation_api_max_contributions_enabled_;
  }

  static bool PrivateAggregationApiMaxContributionsEnabled(const FeatureContext*) { return PrivateAggregationApiMaxContributionsEnabled(); }

  static bool PrivateNetworkAccessNullIpAddressEnabled() {
    return is_private_network_access_null_ip_address_enabled_;
  }

  static bool PrivateNetworkAccessNullIpAddressEnabled(const FeatureContext*) { return PrivateNetworkAccessNullIpAddressEnabled(); }

  static bool PrivateStateTokensEnabled() {
    return is_private_state_tokens_enabled_;
  }

  static bool PrivateStateTokensEnabled(const FeatureContext*) { return PrivateStateTokensEnabled(); }

  static bool PrivateStateTokensAlwaysAllowIssuanceEnabled() {
    return is_private_state_tokens_always_allow_issuance_enabled_;
  }

  static bool PrivateStateTokensAlwaysAllowIssuanceEnabled(const FeatureContext*) { return PrivateStateTokensAlwaysAllowIssuanceEnabled(); }

  static bool ProfilerAPIEnabled() {
    return is_profiler_api_enabled_;
  }

  static bool ProfilerAPIEnabled(const FeatureContext*) { return ProfilerAPIEnabled(); }

  static bool ProfilerAPIForDedicatedWorkerEnabled() {
    return is_profiler_api_for_dedicated_worker_enabled_;
  }

  static bool ProfilerAPIForDedicatedWorkerEnabled(const FeatureContext*) { return ProfilerAPIForDedicatedWorkerEnabled(); }

  static bool ProgrammaticScrollPromiseEnabled() {
    return is_programmatic_scroll_promise_enabled_;
  }

  static bool ProgrammaticScrollPromiseEnabled(const FeatureContext*) { return ProgrammaticScrollPromiseEnabled(); }

  static bool ProgressMaxIsPositiveEnabled() {
    return is_progress_max_is_positive_enabled_;
  }

  static bool ProgressMaxIsPositiveEnabled(const FeatureContext*) { return ProgressMaxIsPositiveEnabled(); }

  static bool PropagateOverscrollBehaviorFromRootEnabled() {
    return is_propagate_overscroll_behavior_from_root_enabled_;
  }

  static bool PropagateOverscrollBehaviorFromRootEnabled(const FeatureContext*) { return PropagateOverscrollBehaviorFromRootEnabled(); }

  static bool PseudoElementsFocusableEnabled() {
    return is_pseudo_elements_focusable_enabled_;
  }

  static bool PseudoElementsFocusableEnabled(const FeatureContext*) { return PseudoElementsFocusableEnabled(); }

  static bool PseudoElementsHitTestableEnabled() {
    return is_pseudo_elements_hit_testable_enabled_;
  }

  static bool PseudoElementsHitTestableEnabled(const FeatureContext*) { return PseudoElementsHitTestableEnabled(); }

  static bool PseudoElementsHoverableEnabled() {
    if (!PseudoElementsHitTestableEnabled())
      return false;
    return is_pseudo_elements_hoverable_enabled_;
  }

  static bool PseudoElementsHoverableEnabled(const FeatureContext*) { return PseudoElementsHoverableEnabled(); }

  static bool PushMessageDataBytesEnabled() {
    if (!PushMessagingEnabled())
      return false;
    return is_push_message_data_bytes_enabled_;
  }

  static bool PushMessageDataBytesEnabled(const FeatureContext*) { return PushMessageDataBytesEnabled(); }

  static bool PushMessagingEnabled() {
    return is_push_messaging_enabled_;
  }

  static bool PushMessagingEnabled(const FeatureContext*) { return PushMessagingEnabled(); }

  static bool PushMessagingSubscriptionChangeEnabled() {
    return is_push_messaging_subscription_change_enabled_;
  }

  static bool PushMessagingSubscriptionChangeEnabled(const FeatureContext*) { return PushMessagingSubscriptionChangeEnabled(); }

  static bool QuotaExceededErrorUpdateEnabled() {
    return is_quota_exceeded_error_update_enabled_;
  }

  static bool QuotaExceededErrorUpdateEnabled(const FeatureContext*) { return QuotaExceededErrorUpdateEnabled(); }

  static bool QuoteFirstLineStyleEnabled() {
    return is_quote_first_line_style_enabled_;
  }

  static bool QuoteFirstLineStyleEnabled(const FeatureContext*) { return QuoteFirstLineStyleEnabled(); }

  static bool RasterInducingScrollEnabled() {
    return is_raster_inducing_scroll_enabled_;
  }

  static bool RasterInducingScrollEnabled(const FeatureContext*) { return RasterInducingScrollEnabled(); }

  static bool ReadableStreamBYOBReaderReadMinOptionEnabled() {
    return is_readable_stream_byob_reader_read_min_option_enabled_;
  }

  static bool ReadableStreamBYOBReaderReadMinOptionEnabled(const FeatureContext*) { return ReadableStreamBYOBReaderReadMinOptionEnabled(); }

  static bool ReadClipboardDataOnClipboardItemGetTypeEnabled() {
    return is_read_clipboard_data_on_clipboard_item_get_type_enabled_;
  }

  static bool ReadClipboardDataOnClipboardItemGetTypeEnabled(const FeatureContext*) { return ReadClipboardDataOnClipboardItemGetTypeEnabled(); }

  static bool ReadingFlowWithSlotsEnabled() {
    return is_reading_flow_with_slots_enabled_;
  }

  static bool ReadingFlowWithSlotsEnabled(const FeatureContext*) { return ReadingFlowWithSlotsEnabled(); }

  static bool RecheckParentDuringNodeVectorInsertionEnabled() {
    return is_recheck_parent_during_node_vector_insertion_enabled_;
  }

  static bool RecheckParentDuringNodeVectorInsertionEnabled(const FeatureContext*) { return RecheckParentDuringNodeVectorInsertionEnabled(); }

  static bool RecordSameDocumentPresentationTimeOnceEnabled() {
    return is_record_same_document_presentation_time_once_enabled_;
  }

  static bool RecordSameDocumentPresentationTimeOnceEnabled(const FeatureContext*) { return RecordSameDocumentPresentationTimeOnceEnabled(); }

  static bool ReduceAcceptLanguageEnabled() {
    return is_reduce_accept_language_enabled_;
  }

  static bool ReduceAcceptLanguageEnabled(const FeatureContext*) { return ReduceAcceptLanguageEnabled(); }

  static bool ReduceUserAgentDataLinuxPlatformVersionEnabled() {
    return is_reduce_user_agent_data_linux_platform_version_enabled_;
  }

  static bool ReduceUserAgentDataLinuxPlatformVersionEnabled(const FeatureContext*) { return ReduceUserAgentDataLinuxPlatformVersionEnabled(); }

  static bool ReduceUserAgentMinorVersionEnabled() {
    return is_reduce_user_agent_minor_version_enabled_;
  }

  static bool ReduceUserAgentMinorVersionEnabled(const FeatureContext*) { return ReduceUserAgentMinorVersionEnabled(); }

  static bool RegionCaptureEnabled() {
    return is_region_capture_enabled_;
  }

  static bool RegionCaptureEnabled(const FeatureContext*) { return RegionCaptureEnabled(); }

  static bool RelatedWebsitePartitionAPIEnabled() {
    return is_related_website_partition_api_enabled_;
  }

  static bool RelatedWebsitePartitionAPIEnabled(const FeatureContext*) { return RelatedWebsitePartitionAPIEnabled(); }

  static bool RelOpenerBcgDependencyHintEnabled() {
    return is_rel_opener_bcg_dependency_hint_enabled_;
  }

  static bool RelOpenerBcgDependencyHintEnabled(const FeatureContext*) { return RelOpenerBcgDependencyHintEnabled(); }

  static bool RemotePlaybackEnabled() {
    return is_remote_playback_enabled_;
  }

  static bool RemotePlaybackEnabled(const FeatureContext*) { return RemotePlaybackEnabled(); }

  static bool RemotePlaybackBackendEnabled() {
    return is_remote_playback_backend_enabled_;
  }

  static bool RemotePlaybackBackendEnabled(const FeatureContext*) { return RemotePlaybackBackendEnabled(); }

  static bool RemoveCharsetAutoDetectionForISO2022JPEnabled() {
    return is_remove_charset_auto_detection_for_iso_2022_jp_enabled_;
  }

  static bool RemoveCharsetAutoDetectionForISO2022JPEnabled(const FeatureContext*) { return RemoveCharsetAutoDetectionForISO2022JPEnabled(); }

  static bool RemoveChildrenInReplaceChildrenEnabled() {
    return is_remove_children_in_replace_children_enabled_;
  }

  static bool RemoveChildrenInReplaceChildrenEnabled(const FeatureContext*) { return RemoveChildrenInReplaceChildrenEnabled(); }

  static bool RemoveCollapsedPlaceholderForContentEditableEnabled() {
    return is_remove_collapsed_placeholder_for_content_editable_enabled_;
  }

  static bool RemoveCollapsedPlaceholderForContentEditableEnabled(const FeatureContext*) { return RemoveCollapsedPlaceholderForContentEditableEnabled(); }

  static bool RemoveDanglingMarkupInTargetEnabled() {
    return is_remove_dangling_markup_in_target_enabled_;
  }

  static bool RemoveDanglingMarkupInTargetEnabled(const FeatureContext*) { return RemoveDanglingMarkupInTargetEnabled(); }

  static bool RemoveDataUrlInSvgUseEnabled() {
    return is_remove_data_url_in_svg_use_enabled_;
  }

  static bool RemoveDataUrlInSvgUseEnabled(const FeatureContext*) { return RemoveDataUrlInSvgUseEnabled(); }

  static bool RemoveFormatFilterBackgroundColorEnabled() {
    return is_remove_format_filter_background_color_enabled_;
  }

  static bool RemoveFormatFilterBackgroundColorEnabled(const FeatureContext*) { return RemoveFormatFilterBackgroundColorEnabled(); }

  static bool RemoveNonAllowlistedCreateEventEnabled() {
    return is_remove_non_allowlisted_create_event_enabled_;
  }

  static bool RemoveNonAllowlistedCreateEventEnabled(const FeatureContext*) { return RemoveNonAllowlistedCreateEventEnabled(); }

  static bool RemoveScrollNodeWorkaroundEnabled() {
    return is_remove_scroll_node_workaround_enabled_;
  }

  static bool RemoveScrollNodeWorkaroundEnabled(const FeatureContext*) { return RemoveScrollNodeWorkaroundEnabled(); }

  static bool RemoveSelectionCanonicalizationInMoveParagraphEnabled() {
    return is_remove_selection_canonicalization_in_move_paragraph_enabled_;
  }

  static bool RemoveSelectionCanonicalizationInMoveParagraphEnabled(const FeatureContext*) { return RemoveSelectionCanonicalizationInMoveParagraphEnabled(); }

  static bool RemoveVisibleSelectionInDOMSelectionEnabled() {
    return is_remove_visible_selection_in_dom_selection_enabled_;
  }

  static bool RemoveVisibleSelectionInDOMSelectionEnabled(const FeatureContext*) { return RemoveVisibleSelectionInDOMSelectionEnabled(); }

  static bool RenderBlockingStatusEnabled() {
    return is_render_blocking_status_enabled_;
  }

  static bool RenderBlockingStatusEnabled(const FeatureContext*) { return RenderBlockingStatusEnabled(); }

  static bool RenderPriorityAttributeEnabled() {
    return is_render_priority_attribute_enabled_;
  }

  static bool RenderPriorityAttributeEnabled(const FeatureContext*) { return RenderPriorityAttributeEnabled(); }

  static bool ReportFirstFrameTimeAsRenderTimeEnabled() {
    return is_report_first_frame_time_as_render_time_enabled_;
  }

  static bool ReportFirstFrameTimeAsRenderTimeEnabled(const FeatureContext*) { return ReportFirstFrameTimeAsRenderTimeEnabled(); }

  static bool ReportLayoutShiftRectsInCssPixelsEnabled() {
    return is_report_layout_shift_rects_in_css_pixels_enabled_;
  }

  static bool ReportLayoutShiftRectsInCssPixelsEnabled(const FeatureContext*) { return ReportLayoutShiftRectsInCssPixelsEnabled(); }

  static bool RequestIsReloadNavigationEnabled() {
    return is_request_is_reload_navigation_enabled_;
  }

  static bool RequestIsReloadNavigationEnabled(const FeatureContext*) { return RequestIsReloadNavigationEnabled(); }

  static bool RequestMainFrameAfterFirstVideoFrameEnabled() {
    return is_request_main_frame_after_first_video_frame_enabled_;
  }

  static bool RequestMainFrameAfterFirstVideoFrameEnabled(const FeatureContext*) { return RequestMainFrameAfterFirstVideoFrameEnabled(); }

  static bool ResolveVarStylesOnCopyEnabled() {
    return is_resolve_var_styles_on_copy_enabled_;
  }

  static bool ResolveVarStylesOnCopyEnabled(const FeatureContext*) { return ResolveVarStylesOnCopyEnabled(); }

  static bool ResourceTimingContentEncodingEnabled() {
    return is_resource_timing_content_encoding_enabled_;
  }

  static bool ResourceTimingContentEncodingEnabled(const FeatureContext*) { return ResourceTimingContentEncodingEnabled(); }

  static bool ResourceTimingContentTypeEnabled() {
    return is_resource_timing_content_type_enabled_;
  }

  static bool ResourceTimingContentTypeEnabled(const FeatureContext*) { return ResourceTimingContentTypeEnabled(); }

  static bool ResourceTimingInitiatorEnabled() {
    return is_resource_timing_initiator_enabled_;
  }

  static bool ResourceTimingInitiatorEnabled(const FeatureContext*) { return ResourceTimingInitiatorEnabled(); }

  static bool ResourceTimingUseCORSForBodySizesEnabled() {
    return is_resource_timing_use_cors_for_body_sizes_enabled_;
  }

  static bool ResourceTimingUseCORSForBodySizesEnabled(const FeatureContext*) { return ResourceTimingUseCORSForBodySizesEnabled(); }

  static bool RespectOverscrollBehaviorForScrollBubblingEnabled() {
    return is_respect_overscroll_behavior_for_scroll_bubbling_enabled_;
  }

  static bool RespectOverscrollBehaviorForScrollBubblingEnabled(const FeatureContext*) { return RespectOverscrollBehaviorForScrollBubblingEnabled(); }

  static bool ResponsiveIframesEnabled() {
    return is_responsive_iframes_enabled_;
  }

  static bool ResponsiveIframesEnabled(const FeatureContext*) { return ResponsiveIframesEnabled(); }

  static bool RestrictGamepadAccessEnabled() {
    return is_restrict_gamepad_access_enabled_;
  }

  static bool RestrictGamepadAccessEnabled(const FeatureContext*) { return RestrictGamepadAccessEnabled(); }

  static bool RestrictOwnAudioEnabled() {
    return is_restrict_own_audio_enabled_;
  }

  static bool RestrictOwnAudioEnabled(const FeatureContext*) { return RestrictOwnAudioEnabled(); }

  static bool RootScrollbarFollowsBrowserThemeEnabled() {
    return is_root_scrollbar_follows_browser_theme_enabled_;
  }

  static bool RootScrollbarFollowsBrowserThemeEnabled(const FeatureContext*) { return RootScrollbarFollowsBrowserThemeEnabled(); }

  static bool RouteMatchingEnabled() {
    return is_route_matching_enabled_;
  }

  static bool RouteMatchingEnabled(const FeatureContext*) { return RouteMatchingEnabled(); }

  static bool RtcAlwaysNegotiateDataChannelsEnabled() {
    return is_rtc_always_negotiate_data_channels_enabled_;
  }

  static bool RtcAlwaysNegotiateDataChannelsEnabled(const FeatureContext*) { return RtcAlwaysNegotiateDataChannelsEnabled(); }

  static bool RTCDataChannelPriorityEnabled() {
    return is_rtc_data_channel_priority_enabled_;
  }

  static bool RTCDataChannelPriorityEnabled(const FeatureContext*) { return RTCDataChannelPriorityEnabled(); }

  static bool RTCDiagnosticLoggingEnabled() {
    return is_rtc_diagnostic_logging_enabled_;
  }

  static bool RTCDiagnosticLoggingEnabled(const FeatureContext*) { return RTCDiagnosticLoggingEnabled(); }

  static bool RTCEncodedFrameAudioLevelEnabled() {
    return is_rtc_encoded_frame_audio_level_enabled_;
  }

  static bool RTCEncodedFrameAudioLevelEnabled(const FeatureContext*) { return RTCEncodedFrameAudioLevelEnabled(); }

  static bool RTCEncodedFrameTimestampsEnabled() {
    return is_rtc_encoded_frame_timestamps_enabled_;
  }

  static bool RTCEncodedFrameTimestampsEnabled(const FeatureContext*) { return RTCEncodedFrameTimestampsEnabled(); }

  static bool RTCEncodedVideoFrameAdditionalMetadataEnabled() {
    return is_rtc_encoded_video_frame_additional_metadata_enabled_;
  }

  static bool RTCEncodedVideoFrameAdditionalMetadataEnabled(const FeatureContext*) { return RTCEncodedVideoFrameAdditionalMetadataEnabled(); }

  static bool RTCJitterBufferTargetEnabled() {
    return is_rtc_jitter_buffer_target_enabled_;
  }

  static bool RTCJitterBufferTargetEnabled(const FeatureContext*) { return RTCJitterBufferTargetEnabled(); }

  static bool RTCRtpEncodingParametersCodecEnabled() {
    return is_rtc_rtp_encoding_parameters_codec_enabled_;
  }

  static bool RTCRtpEncodingParametersCodecEnabled(const FeatureContext*) { return RTCRtpEncodingParametersCodecEnabled(); }

  static bool RTCRtpScaleResolutionDownToEnabled() {
    return is_rtc_rtp_scale_resolution_down_to_enabled_;
  }

  static bool RTCRtpScaleResolutionDownToEnabled(const FeatureContext*) { return RTCRtpScaleResolutionDownToEnabled(); }

  static bool RTCRtpScriptTransformEnabled() {
    return is_rtc_rtp_script_transform_enabled_;
  }

  static bool RTCRtpScriptTransformEnabled(const FeatureContext*) { return RTCRtpScriptTransformEnabled(); }

  static bool RTCRtpTransportEnabled() {
    return is_rtc_rtp_transport_enabled_;
  }

  static bool RTCRtpTransportEnabled(const FeatureContext*) { return RTCRtpTransportEnabled(); }

  static bool RTCSvcScalabilityModeEnabled() {
    return is_rtc_svc_scalability_mode_enabled_;
  }

  static bool RTCSvcScalabilityModeEnabled(const FeatureContext*) { return RTCSvcScalabilityModeEnabled(); }

  static bool RunMicrotaskBeforeXmlScriptEnabled() {
    return is_run_microtask_before_xml_script_enabled_;
  }

  static bool RunMicrotaskBeforeXmlScriptEnabled(const FeatureContext*) { return RunMicrotaskBeforeXmlScriptEnabled(); }

  static bool RunSnapshotPostLayoutStateStepsEnabled() {
    return is_run_snapshot_post_layout_state_steps_enabled_;
  }

  static bool RunSnapshotPostLayoutStateStepsEnabled(const FeatureContext*) { return RunSnapshotPostLayoutStateStepsEnabled(); }

  static bool SanitizerAPIEnabled() {
    return is_sanitizer_api_enabled_;
  }

  static bool SanitizerAPIEnabled(const FeatureContext*) { return SanitizerAPIEnabled(); }

  static bool ScopedCustomElementRegistryEnabled() {
    return is_scoped_custom_element_registry_enabled_;
  }

  static bool ScopedCustomElementRegistryEnabled(const FeatureContext*) { return ScopedCustomElementRegistryEnabled(); }

  static bool ScopedViewTransitionsEnabled() {
    return is_scoped_view_transitions_enabled_;
  }

  static bool ScopedViewTransitionsEnabled(const FeatureContext*) { return ScopedViewTransitionsEnabled(); }

  static bool ScreenDetailedHdrHeadroomEnabled() {
    return is_screen_detailed_hdr_headroom_enabled_;
  }

  static bool ScreenDetailedHdrHeadroomEnabled(const FeatureContext*) { return ScreenDetailedHdrHeadroomEnabled(); }

  static bool ScriptBasedOnUnicodeBlockEnabled() {
    return is_script_based_on_unicode_block_enabled_;
  }

  static bool ScriptBasedOnUnicodeBlockEnabled(const FeatureContext*) { return ScriptBasedOnUnicodeBlockEnabled(); }

  static bool ScriptedSpeechRecognitionEnabled() {
    return is_scripted_speech_recognition_enabled_;
  }

  static bool ScriptedSpeechRecognitionEnabled(const FeatureContext*) { return ScriptedSpeechRecognitionEnabled(); }

  static bool ScriptedSpeechSynthesisEnabled() {
    return is_scripted_speech_synthesis_enabled_;
  }

  static bool ScriptedSpeechSynthesisEnabled(const FeatureContext*) { return ScriptedSpeechSynthesisEnabled(); }

  static bool ScrollAnchorPriorityCandidateSubtreeEnabled() {
    return is_scroll_anchor_priority_candidate_subtree_enabled_;
  }

  static bool ScrollAnchorPriorityCandidateSubtreeEnabled(const FeatureContext*) { return ScrollAnchorPriorityCandidateSubtreeEnabled(); }

  static bool ScrollAnchorSerializationUseParentForTextNodeEnabled() {
    return is_scroll_anchor_serialization_use_parent_for_text_node_enabled_;
  }

  static bool ScrollAnchorSerializationUseParentForTextNodeEnabled(const FeatureContext*) { return ScrollAnchorSerializationUseParentForTextNodeEnabled(); }

  static bool ScrollbarColorEnabled() {
    return is_scrollbar_color_enabled_;
  }

  static bool ScrollbarColorEnabled(const FeatureContext*) { return ScrollbarColorEnabled(); }

  static bool ScrollbarGutterBugFixEnabled() {
    return is_scrollbar_gutter_bug_fix_enabled_;
  }

  static bool ScrollbarGutterBugFixEnabled(const FeatureContext*) { return ScrollbarGutterBugFixEnabled(); }

  static bool ScrollbarWidthEnabled() {
    return is_scrollbar_width_enabled_;
  }

  static bool ScrollbarWidthEnabled(const FeatureContext*) { return ScrollbarWidthEnabled(); }

  static bool ScrollIntoViewNearestEnabled() {
    return is_scroll_into_view_nearest_enabled_;
  }

  static bool ScrollIntoViewNearestEnabled(const FeatureContext*) { return ScrollIntoViewNearestEnabled(); }

  static bool ScrollIntoViewRootFrameViewportBugFixEnabled() {
    return is_scroll_into_view_root_frame_viewport_bug_fix_enabled_;
  }

  static bool ScrollIntoViewRootFrameViewportBugFixEnabled(const FeatureContext*) { return ScrollIntoViewRootFrameViewportBugFixEnabled(); }

  static bool ScrollTimelineCurrentTimeEnabled() {
    return is_scroll_timeline_current_time_enabled_;
  }

  static bool ScrollTimelineCurrentTimeEnabled(const FeatureContext*) { return ScrollTimelineCurrentTimeEnabled(); }

  static bool ScrollTimelineNamedRangeScrollEnabled() {
    return is_scroll_timeline_named_range_scroll_enabled_;
  }

  static bool ScrollTimelineNamedRangeScrollEnabled(const FeatureContext*) { return ScrollTimelineNamedRangeScrollEnabled(); }

  static bool ScrollTopLeftInteropEnabled() {
    return is_scroll_top_left_interop_enabled_;
  }

  static bool ScrollTopLeftInteropEnabled(const FeatureContext*) { return ScrollTopLeftInteropEnabled(); }

  static bool ScrollToTextFragmentUniqueFragmentsEnabled() {
    return is_scroll_to_text_fragment_unique_fragments_enabled_;
  }

  static bool ScrollToTextFragmentUniqueFragmentsEnabled(const FeatureContext*) { return ScrollToTextFragmentUniqueFragmentsEnabled(); }

  static bool SearchTextHighlightPseudoEnabled() {
    return is_search_text_highlight_pseudo_enabled_;
  }

  static bool SearchTextHighlightPseudoEnabled(const FeatureContext*) { return SearchTextHighlightPseudoEnabled(); }

  static bool SecurePaymentConfirmationEnabled() {
    return is_secure_payment_confirmation_enabled_;
  }

  static bool SecurePaymentConfirmationEnabled(const FeatureContext*) { return SecurePaymentConfirmationEnabled(); }

  static bool SecurePaymentConfirmationAvailabilityAPIEnabled() {
    return is_secure_payment_confirmation_availability_api_enabled_;
  }

  static bool SecurePaymentConfirmationAvailabilityAPIEnabled(const FeatureContext*) { return SecurePaymentConfirmationAvailabilityAPIEnabled(); }

  static bool SecurePaymentConfirmationCapabilitiesEnabled() {
    return is_secure_payment_confirmation_capabilities_enabled_;
  }

  static bool SecurePaymentConfirmationCapabilitiesEnabled(const FeatureContext*) { return SecurePaymentConfirmationCapabilitiesEnabled(); }

  static bool SecurePaymentConfirmationDebugEnabled() {
    return is_secure_payment_confirmation_debug_enabled_;
  }

  static bool SecurePaymentConfirmationDebugEnabled(const FeatureContext*) { return SecurePaymentConfirmationDebugEnabled(); }

  static bool SelectAudioOutputEnabled() {
    return is_select_audio_output_enabled_;
  }

  static bool SelectAudioOutputEnabled(const FeatureContext*) { return SelectAudioOutputEnabled(); }

  static bool SelectedcontentelementAttributeEnabled() {
    if (!SelectedcontentSpecEnabled())
      return false;
    return is_selectedcontentelement_attribute_enabled_;
  }

  static bool SelectedcontentelementAttributeEnabled(const FeatureContext*) { return SelectedcontentelementAttributeEnabled(); }

  static bool SelectedcontentMultipleEnabled() {
    if (!SelectedcontentSpecEnabled())
      return false;
    if (!CustomizableSelectMultiplePopupEnabled())
      return false;
    return is_selectedcontent_multiple_enabled_;
  }

  static bool SelectedcontentMultipleEnabled(const FeatureContext*) { return SelectedcontentMultipleEnabled(); }

  static bool SelectedcontentSpecEnabled() {
    return is_selectedcontent_spec_enabled_;
  }

  static bool SelectedcontentSpecEnabled(const FeatureContext*) { return SelectedcontentSpecEnabled(); }

  static bool SelectionAndFocusedVisiblePositionMatchEnabled() {
    return is_selection_and_focused_visible_position_match_enabled_;
  }

  static bool SelectionAndFocusedVisiblePositionMatchEnabled(const FeatureContext*) { return SelectionAndFocusedVisiblePositionMatchEnabled(); }

  static bool SelectionCollapsedDirectionNoneEnabled() {
    return is_selection_collapsed_direction_none_enabled_;
  }

  static bool SelectionCollapsedDirectionNoneEnabled(const FeatureContext*) { return SelectionCollapsedDirectionNoneEnabled(); }

  static bool SelectionFocusAffinityEnabled() {
    return is_selection_focus_affinity_enabled_;
  }

  static bool SelectionFocusAffinityEnabled(const FeatureContext*) { return SelectionFocusAffinityEnabled(); }

  static bool SelectionHandleWithBottomClippedEnabled() {
    return is_selection_handle_with_bottom_clipped_enabled_;
  }

  static bool SelectionHandleWithBottomClippedEnabled(const FeatureContext*) { return SelectionHandleWithBottomClippedEnabled(); }

  static bool SelectionRemoveRangeNotFoundErrorEnabled() {
    return is_selection_remove_range_not_found_error_enabled_;
  }

  static bool SelectionRemoveRangeNotFoundErrorEnabled(const FeatureContext*) { return SelectionRemoveRangeNotFoundErrorEnabled(); }

  static bool SelectionSetBaseAndExtentNonNullNodeEnabled() {
    return is_selection_set_base_and_extent_non_null_node_enabled_;
  }

  static bool SelectionSetBaseAndExtentNonNullNodeEnabled(const FeatureContext*) { return SelectionSetBaseAndExtentNonNullNodeEnabled(); }

  static bool SelectionToStringSkipsUserSelectNoneEnabled() {
    return is_selection_to_string_skips_user_select_none_enabled_;
  }

  static bool SelectionToStringSkipsUserSelectNoneEnabled(const FeatureContext*) { return SelectionToStringSkipsUserSelectNoneEnabled(); }

  static bool SelectionUpdateOnlyAfterAutoscrollEnabled() {
    return is_selection_update_only_after_autoscroll_enabled_;
  }

  static bool SelectionUpdateOnlyAfterAutoscrollEnabled(const FeatureContext*) { return SelectionUpdateOnlyAfterAutoscrollEnabled(); }

  static bool SelectionUpdateToInitialSelectionInListifyEnabled() {
    return is_selection_update_to_initial_selection_in_listify_enabled_;
  }

  static bool SelectionUpdateToInitialSelectionInListifyEnabled(const FeatureContext*) { return SelectionUpdateToInitialSelectionInListifyEnabled(); }

  static bool SelectiveClipboardFormatReadEnabled() {
    return is_selective_clipboard_format_read_enabled_;
  }

  static bool SelectiveClipboardFormatReadEnabled(const FeatureContext*) { return SelectiveClipboardFormatReadEnabled(); }

  static bool SelectivePermissionsInterventionEnabled() {
    return is_selective_permissions_intervention_enabled_;
  }

  static bool SelectivePermissionsInterventionEnabled(const FeatureContext*) { return SelectivePermissionsInterventionEnabled(); }

  static bool SelectRemoveOverflowHiddenEnabled() {
    return is_select_remove_overflow_hidden_enabled_;
  }

  static bool SelectRemoveOverflowHiddenEnabled(const FeatureContext*) { return SelectRemoveOverflowHiddenEnabled(); }

  static bool SendBeaconThrowForBlobWithNonSimpleTypeEnabled() {
    return is_send_beacon_throw_for_blob_with_non_simple_type_enabled_;
  }

  static bool SendBeaconThrowForBlobWithNonSimpleTypeEnabled(const FeatureContext*) { return SendBeaconThrowForBlobWithNonSimpleTypeEnabled(); }

  static bool SendSlotChangeSignalAfterNodeInsertedEnabled() {
    return is_send_slot_change_signal_after_node_inserted_enabled_;
  }

  static bool SendSlotChangeSignalAfterNodeInsertedEnabled(const FeatureContext*) { return SendSlotChangeSignalAfterNodeInsertedEnabled(); }

  static bool SensorExtraClassesEnabled() {
    return is_sensor_extra_classes_enabled_;
  }

  static bool SensorExtraClassesEnabled(const FeatureContext*) { return SensorExtraClassesEnabled(); }

  static bool SeparateDeferModuleScriptTasksEnabled() {
    return is_separate_defer_module_script_tasks_enabled_;
  }

  static bool SeparateDeferModuleScriptTasksEnabled(const FeatureContext*) { return SeparateDeferModuleScriptTasksEnabled(); }

  static bool SerialEnabled() {
    return is_serial_enabled_;
  }

  static bool SerialEnabled(const FeatureContext*) { return SerialEnabled(); }

  static bool SerializeViewTransitionStateInSPAEnabled() {
    return is_serialize_view_transition_state_in_spa_enabled_;
  }

  static bool SerializeViewTransitionStateInSPAEnabled(const FeatureContext*) { return SerializeViewTransitionStateInSPAEnabled(); }

  static bool SerialPortConnectedEnabled() {
    return is_serial_port_connected_enabled_;
  }

  static bool SerialPortConnectedEnabled(const FeatureContext*) { return SerialPortConnectedEnabled(); }

  static bool ServiceWorkerBackgroundSyncInDedicatedWorkerEnabled() {
    if (!ServiceWorkerInDedicatedWorkerEnabled())
      return false;
    return is_service_worker_background_sync_in_dedicated_worker_enabled_;
  }

  static bool ServiceWorkerBackgroundSyncInDedicatedWorkerEnabled(const FeatureContext*) { return ServiceWorkerBackgroundSyncInDedicatedWorkerEnabled(); }

  static bool ServiceWorkerClientLifecycleStateEnabled() {
    return is_service_worker_client_lifecycle_state_enabled_;
  }

  static bool ServiceWorkerClientLifecycleStateEnabled(const FeatureContext*) { return ServiceWorkerClientLifecycleStateEnabled(); }

  static bool ServiceWorkerInDedicatedWorkerEnabled() {
    return is_service_worker_in_dedicated_worker_enabled_;
  }

  static bool ServiceWorkerInDedicatedWorkerEnabled(const FeatureContext*) { return ServiceWorkerInDedicatedWorkerEnabled(); }

  static bool ServiceWorkerStaticRouterTimingInfoEnabled() {
    return is_service_worker_static_router_timing_info_enabled_;
  }

  static bool ServiceWorkerStaticRouterTimingInfoEnabled(const FeatureContext*) { return ServiceWorkerStaticRouterTimingInfoEnabled(); }

  static bool SetDefaultDropEffectEnabled() {
    return is_set_default_drop_effect_enabled_;
  }

  static bool SetDefaultDropEffectEnabled(const FeatureContext*) { return SetDefaultDropEffectEnabled(); }

  static bool SetHTMLCanRunScriptsEnabled() {
    return is_set_html_can_run_scripts_enabled_;
  }

  static bool SetHTMLCanRunScriptsEnabled(const FeatureContext*) { return SetHTMLCanRunScriptsEnabled(); }

  static bool SetSequentialFocusStartingPointEnabled() {
    return is_set_sequential_focus_starting_point_enabled_;
  }

  static bool SetSequentialFocusStartingPointEnabled(const FeatureContext*) { return SetSequentialFocusStartingPointEnabled(); }

  static bool ShadowContourFollowsBorderEnabled() {
    return is_shadow_contour_follows_border_enabled_;
  }

  static bool ShadowContourFollowsBorderEnabled(const FeatureContext*) { return ShadowContourFollowsBorderEnabled(); }

  static bool ShadowRootReferenceTargetAriaOwnsEnabled() {
    return is_shadow_root_reference_target_aria_owns_enabled_;
  }

  static bool ShadowRootReferenceTargetAriaOwnsEnabled(const FeatureContext*) { return ShadowRootReferenceTargetAriaOwnsEnabled(); }

  static bool SharedArrayBufferEnabled() {
    return is_shared_array_buffer_enabled_;
  }

  static bool SharedArrayBufferEnabled(const FeatureContext*) { return SharedArrayBufferEnabled(); }

  static bool SharedArrayBufferUnrestrictedAccessAllowedEnabled() {
    return is_shared_array_buffer_unrestricted_access_allowed_enabled_;
  }

  static bool SharedArrayBufferUnrestrictedAccessAllowedEnabled(const FeatureContext*) { return SharedArrayBufferUnrestrictedAccessAllowedEnabled(); }

  static bool SharedStorageAPIEnabled() {
    return is_shared_storage_api_enabled_;
  }

  static bool SharedStorageAPIEnabled(const FeatureContext*) { return SharedStorageAPIEnabled(); }

  static bool SharedStorageWebLocksEnabled() {
    if (!SharedStorageAPIEnabled())
      return false;
    return is_shared_storage_web_locks_enabled_;
  }

  static bool SharedStorageWebLocksEnabled(const FeatureContext*) { return SharedStorageWebLocksEnabled(); }

  static bool SharedWorkerEnabled() {
    return is_shared_worker_enabled_;
  }

  static bool SharedWorkerEnabled(const FeatureContext*) { return SharedWorkerEnabled(); }

  static bool SideRelativeBackgroundPositionEnabled() {
    return is_side_relative_background_position_enabled_;
  }

  static bool SideRelativeBackgroundPositionEnabled(const FeatureContext*) { return SideRelativeBackgroundPositionEnabled(); }

  static bool SignatureBasedInlineIntegrityEnabled() {
    return is_signature_based_inline_integrity_enabled_;
  }

  static bool SignatureBasedInlineIntegrityEnabled(const FeatureContext*) { return SignatureBasedInlineIntegrityEnabled(); }

  static bool SingleAxisScrollContainersEnabled() {
    return is_single_axis_scroll_containers_enabled_;
  }

  static bool SingleAxisScrollContainersEnabled(const FeatureContext*) { return SingleAxisScrollContainersEnabled(); }

  static bool SkipAdEnabled() {
    if (!MediaSessionEnabled())
      return false;
    return is_skip_ad_enabled_;
  }

  static bool SkipAdEnabled(const FeatureContext*) { return SkipAdEnabled(); }

  static bool SkipCallbacksWhenDevToolsNotOpenEnabled() {
    return is_skip_callbacks_when_dev_tools_not_open_enabled_;
  }

  static bool SkipCallbacksWhenDevToolsNotOpenEnabled(const FeatureContext*) { return SkipCallbacksWhenDevToolsNotOpenEnabled(); }

  static bool SkipEventCaptureEnabled() {
    return is_skip_event_capture_enabled_;
  }

  static bool SkipEventCaptureEnabled(const FeatureContext*) { return SkipEventCaptureEnabled(); }

  static bool SkipNonEditableInAtomicMoveEnabled() {
    return is_skip_non_editable_in_atomic_move_enabled_;
  }

  static bool SkipNonEditableInAtomicMoveEnabled(const FeatureContext*) { return SkipNonEditableInAtomicMoveEnabled(); }

  static bool SkipOofItemForBreakCandidateEnabled() {
    return is_skip_oof_item_for_break_candidate_enabled_;
  }

  static bool SkipOofItemForBreakCandidateEnabled(const FeatureContext*) { return SkipOofItemForBreakCandidateEnabled(); }

  static bool SkipParagraphSplitForInlineInsertHTMLEnabled() {
    return is_skip_paragraph_split_for_inline_insert_html_enabled_;
  }

  static bool SkipParagraphSplitForInlineInsertHTMLEnabled(const FeatureContext*) { return SkipParagraphSplitForInlineInsertHTMLEnabled(); }

  static bool SkipPseudoOnlyLinesInLineNavigationEnabled() {
    return is_skip_pseudo_only_lines_in_line_navigation_enabled_;
  }

  static bool SkipPseudoOnlyLinesInLineNavigationEnabled(const FeatureContext*) { return SkipPseudoOnlyLinesInLineNavigationEnabled(); }

  static bool SkipTouchEventFilterEnabled() {
    return is_skip_touch_event_filter_enabled_;
  }

  static bool SkipTouchEventFilterEnabled(const FeatureContext*) { return SkipTouchEventFilterEnabled(); }

  static bool SkipUnselectableContentInSerializationEnabled() {
    return is_skip_unselectable_content_in_serialization_enabled_;
  }

  static bool SkipUnselectableContentInSerializationEnabled(const FeatureContext*) { return SkipUnselectableContentInSerializationEnabled(); }

  static bool SkipUnselectableElementsInParagraphBoundaryEnabled() {
    return is_skip_unselectable_elements_in_paragraph_boundary_enabled_;
  }

  static bool SkipUnselectableElementsInParagraphBoundaryEnabled(const FeatureContext*) { return SkipUnselectableElementsInParagraphBoundaryEnabled(); }

  static bool SmallerViewportUnitsEnabled() {
    return is_smaller_viewport_units_enabled_;
  }

  static bool SmallerViewportUnitsEnabled(const FeatureContext*) { return SmallerViewportUnitsEnabled(); }

  static bool SmartCardEnabled() {
    return is_smart_card_enabled_;
  }

  static bool SmartCardEnabled(const FeatureContext*) { return SmartCardEnabled(); }

  static bool SmartZoomEnabled() {
    return is_smart_zoom_enabled_;
  }

  static bool SmartZoomEnabled(const FeatureContext*) { return SmartZoomEnabled(); }

  static bool SnapshotScrollTimelinesPostLayoutEnabled() {
    if (!RunSnapshotPostLayoutStateStepsEnabled())
      return false;
    return is_snapshot_scroll_timelines_post_layout_enabled_;
  }

  static bool SnapshotScrollTimelinesPostLayoutEnabled(const FeatureContext*) { return SnapshotScrollTimelinesPostLayoutEnabled(); }

  static bool SoftNavigationDetectionEnabled() {
    return is_soft_navigation_detection_enabled_;
  }

  static bool SoftNavigationDetectionEnabled(const FeatureContext*) { return SoftNavigationDetectionEnabled(); }

  static bool SoftNavigationDetectionIncludeReplaceStateEnabled() {
    return is_soft_navigation_detection_include_replace_state_enabled_;
  }

  static bool SoftNavigationDetectionIncludeReplaceStateEnabled(const FeatureContext*) { return SoftNavigationDetectionIncludeReplaceStateEnabled(); }

  static bool SortedLayoutShiftSourcesByImpactAreaEnabled() {
    return is_sorted_layout_shift_sources_by_impact_area_enabled_;
  }

  static bool SortedLayoutShiftSourcesByImpactAreaEnabled(const FeatureContext*) { return SortedLayoutShiftSourcesByImpactAreaEnabled(); }

  static bool SourceSpecificMulticastInDirectSocketsEnabled() {
    if (!DirectSocketsEnabled())
      return false;
    return is_source_specific_multicast_in_direct_sockets_enabled_;
  }

  static bool SourceSpecificMulticastInDirectSocketsEnabled(const FeatureContext*) { return SourceSpecificMulticastInDirectSocketsEnabled(); }

  static bool SpatNavUsesCursorInheritanceEnabled() {
    return is_spat_nav_uses_cursor_inheritance_enabled_;
  }

  static bool SpatNavUsesCursorInheritanceEnabled(const FeatureContext*) { return SpatNavUsesCursorInheritanceEnabled(); }

  static bool SpeakerSelectionEnabled() {
    return is_speaker_selection_enabled_;
  }

  static bool SpeakerSelectionEnabled(const FeatureContext*) { return SpeakerSelectionEnabled(); }

  static bool SpeculationMeasurementEnabled() {
    return is_speculation_measurement_enabled_;
  }

  static bool SpeculationMeasurementEnabled(const FeatureContext*) { return SpeculationMeasurementEnabled(); }

  static bool SpellCheckCustomDictionaryAPIEnabled() {
    return is_spell_check_custom_dictionary_api_enabled_;
  }

  static bool SpellCheckCustomDictionaryAPIEnabled(const FeatureContext*) { return SpellCheckCustomDictionaryAPIEnabled(); }

  static bool SplitTextNotCleanupDummySpansEnabled() {
    return is_split_text_not_cleanup_dummy_spans_enabled_;
  }

  static bool SplitTextNotCleanupDummySpansEnabled(const FeatureContext*) { return SplitTextNotCleanupDummySpansEnabled(); }

  static bool SplitViewLinkOpenEnabled() {
    return is_split_view_link_open_enabled_;
  }

  static bool SplitViewLinkOpenEnabled(const FeatureContext*) { return SplitViewLinkOpenEnabled(); }

  static bool SrcsetSelectionMatchesImageSetEnabled() {
    return is_srcset_selection_matches_image_set_enabled_;
  }

  static bool SrcsetSelectionMatchesImageSetEnabled(const FeatureContext*) { return SrcsetSelectionMatchesImageSetEnabled(); }

  static bool StableBlinkFeaturesEnabled() {
    return is_stable_blink_features_enabled_;
  }

  static bool StableBlinkFeaturesEnabled(const FeatureContext*) { return StableBlinkFeaturesEnabled(); }

  static bool StackingContextIsNotStackedEnabled() {
    return is_stacking_context_is_not_stacked_enabled_;
  }

  static bool StackingContextIsNotStackedEnabled(const FeatureContext*) { return StackingContextIsNotStackedEnabled(); }

  static bool StandardizedBrowserZoomEnabled() {
    return is_standardized_browser_zoom_enabled_;
  }

  static bool StandardizedBrowserZoomEnabled(const FeatureContext*) { return StandardizedBrowserZoomEnabled(); }

  static bool StickyPositionHasOverflowPerAxisEnabled() {
    return is_sticky_position_has_overflow_per_axis_enabled_;
  }

  static bool StickyPositionHasOverflowPerAxisEnabled(const FeatureContext*) { return StickyPositionHasOverflowPerAxisEnabled(); }

  static bool StickyUserActivationAcrossSameOriginNavigationEnabled() {
    return is_sticky_user_activation_across_same_origin_navigation_enabled_;
  }

  static bool StickyUserActivationAcrossSameOriginNavigationEnabled(const FeatureContext*) { return StickyUserActivationAcrossSameOriginNavigationEnabled(); }

  static bool StorageBucketsEnabled() {
    return is_storage_buckets_enabled_;
  }

  static bool StorageBucketsEnabled(const FeatureContext*) { return StorageBucketsEnabled(); }

  static bool StorageBucketsDurabilityEnabled() {
    return is_storage_buckets_durability_enabled_;
  }

  static bool StorageBucketsDurabilityEnabled(const FeatureContext*) { return StorageBucketsDurabilityEnabled(); }

  static bool StorageBucketsLocksEnabled() {
    return is_storage_buckets_locks_enabled_;
  }

  static bool StorageBucketsLocksEnabled(const FeatureContext*) { return StorageBucketsLocksEnabled(); }

  static bool StreamingSanitizerEnabled() {
    return is_streaming_sanitizer_enabled_;
  }

  static bool StreamingSanitizerEnabled(const FeatureContext*) { return StreamingSanitizerEnabled(); }

  static bool StrictMimeTypesForWorkersEnabled() {
    return is_strict_mime_types_for_workers_enabled_;
  }

  static bool StrictMimeTypesForWorkersEnabled(const FeatureContext*) { return StrictMimeTypesForWorkersEnabled(); }

  static bool StylusHandwritingEnabled() {
    return is_stylus_handwriting_enabled_;
  }

  static bool StylusHandwritingEnabled(const FeatureContext*) { return StylusHandwritingEnabled(); }

  static bool SubAppsEnabled() {
    return is_sub_apps_enabled_;
  }

  static bool SubAppsEnabled(const FeatureContext*) { return SubAppsEnabled(); }

  static bool SuppressPointerStreamAfterDragEnabled() {
    return is_suppress_pointer_stream_after_drag_enabled_;
  }

  static bool SuppressPointerStreamAfterDragEnabled(const FeatureContext*) { return SuppressPointerStreamAfterDragEnabled(); }

  static bool SvgAnchorElementAttributesEnabled() {
    return is_svg_anchor_element_attributes_enabled_;
  }

  static bool SvgAnchorElementAttributesEnabled(const FeatureContext*) { return SvgAnchorElementAttributesEnabled(); }

  static bool SvgAnchorElementDownloadAttributeEnabled() {
    return is_svg_anchor_element_download_attribute_enabled_;
  }

  static bool SvgAnchorElementDownloadAttributeEnabled(const FeatureContext*) { return SvgAnchorElementDownloadAttributeEnabled(); }

  static bool SvgAnimateMotionDiscreteCalcModeEnabled() {
    return is_svg_animate_motion_discrete_calc_mode_enabled_;
  }

  static bool SvgAnimateMotionDiscreteCalcModeEnabled(const FeatureContext*) { return SvgAnimateMotionDiscreteCalcModeEnabled(); }

  static bool SvgAvoidResettingFilterQualityForTiledPatternEnabled() {
    return is_svg_avoid_resetting_filter_quality_for_tiled_pattern_enabled_;
  }

  static bool SvgAvoidResettingFilterQualityForTiledPatternEnabled(const FeatureContext*) { return SvgAvoidResettingFilterQualityForTiledPatternEnabled(); }

  static bool SVGEmbeddedAsReplacedElementEnabled() {
    return is_svg_embedded_as_replaced_element_enabled_;
  }

  static bool SVGEmbeddedAsReplacedElementEnabled(const FeatureContext*) { return SVGEmbeddedAsReplacedElementEnabled(); }

  static bool SvgEnableTextDecorationCssStylingEnabled() {
    return is_svg_enable_text_decoration_css_styling_enabled_;
  }

  static bool SvgEnableTextDecorationCssStylingEnabled(const FeatureContext*) { return SvgEnableTextDecorationCssStylingEnabled(); }

  static bool SvgFallBackToContainerSizeEnabled() {
    return is_svg_fall_back_to_container_size_enabled_;
  }

  static bool SvgFallBackToContainerSizeEnabled(const FeatureContext*) { return SvgFallBackToContainerSizeEnabled(); }

  static bool SvgFeImageSkipHiddenContainerViewportDependenceEnabled() {
    return is_svg_fe_image_skip_hidden_container_viewport_dependence_enabled_;
  }

  static bool SvgFeImageSkipHiddenContainerViewportDependenceEnabled(const FeatureContext*) { return SvgFeImageSkipHiddenContainerViewportDependenceEnabled(); }

  static bool SvgFilterPaintsForHiddenContentEnabled() {
    return is_svg_filter_paints_for_hidden_content_enabled_;
  }

  static bool SvgFilterPaintsForHiddenContentEnabled(const FeatureContext*) { return SvgFilterPaintsForHiddenContentEnabled(); }

  static bool SvgFilterUserSpaceViewportForSvgEnabled() {
    return is_svg_filter_user_space_viewport_for_svg_enabled_;
  }

  static bool SvgFilterUserSpaceViewportForSvgEnabled(const FeatureContext*) { return SvgFilterUserSpaceViewportForSvgEnabled(); }

  static bool SvgIgnoreNegativeEllipseRadiiEnabled() {
    return is_svg_ignore_negative_ellipse_radii_enabled_;
  }

  static bool SvgIgnoreNegativeEllipseRadiiEnabled(const FeatureContext*) { return SvgIgnoreNegativeEllipseRadiiEnabled(); }

  static bool SvgInlineRootPixelSnappingScaleAdjustmentEnabled() {
    return is_svg_inline_root_pixel_snapping_scale_adjustment_enabled_;
  }

  static bool SvgInlineRootPixelSnappingScaleAdjustmentEnabled(const FeatureContext*) { return SvgInlineRootPixelSnappingScaleAdjustmentEnabled(); }

  static bool SvgLengthListClearOnParsingFailureEnabled() {
    return is_svg_length_list_clear_on_parsing_failure_enabled_;
  }

  static bool SvgLengthListClearOnParsingFailureEnabled(const FeatureContext*) { return SvgLengthListClearOnParsingFailureEnabled(); }

  static bool SvgLengthResolveUnparsedValueEnabled() {
    return is_svg_length_resolve_unparsed_value_enabled_;
  }

  static bool SvgLengthResolveUnparsedValueEnabled(const FeatureContext*) { return SvgLengthResolveUnparsedValueEnabled(); }

  static bool SvgNumberListClearOnParsingFailureEnabled() {
    return is_svg_number_list_clear_on_parsing_failure_enabled_;
  }

  static bool SvgNumberListClearOnParsingFailureEnabled(const FeatureContext*) { return SvgNumberListClearOnParsingFailureEnabled(); }

  static bool SvgPartitionSVGDocumentResourcesInMemoryCacheEnabled() {
    return is_svg_partition_svg_document_resources_in_memory_cache_enabled_;
  }

  static bool SvgPartitionSVGDocumentResourcesInMemoryCacheEnabled(const FeatureContext*) { return SvgPartitionSVGDocumentResourcesInMemoryCacheEnabled(); }

  static bool SvgPathLengthCssPropertyEnabled() {
    return is_svg_path_length_css_property_enabled_;
  }

  static bool SvgPathLengthCssPropertyEnabled(const FeatureContext*) { return SvgPathLengthCssPropertyEnabled(); }

  static bool SvgPointListClearOnParsingFailureEnabled() {
    return is_svg_point_list_clear_on_parsing_failure_enabled_;
  }

  static bool SvgPointListClearOnParsingFailureEnabled(const FeatureContext*) { return SvgPointListClearOnParsingFailureEnabled(); }

  static bool SvgScriptElementAsyncAttributeEnabled() {
    return is_svg_script_element_async_attribute_enabled_;
  }

  static bool SvgScriptElementAsyncAttributeEnabled(const FeatureContext*) { return SvgScriptElementAsyncAttributeEnabled(); }

  static bool SvgSizingWithPreserveAspectRatioNoneEnabled() {
    return is_svg_sizing_with_preserve_aspect_ratio_none_enabled_;
  }

  static bool SvgSizingWithPreserveAspectRatioNoneEnabled(const FeatureContext*) { return SvgSizingWithPreserveAspectRatioNoneEnabled(); }

  static bool SvgSmilClockValueValidationEnabled() {
    return is_svg_smil_clock_value_validation_enabled_;
  }

  static bool SvgSmilClockValueValidationEnabled(const FeatureContext*) { return SvgSmilClockValueValidationEnabled(); }

  static bool SvgTextPathPathAttributeEnabled() {
    return is_svg_text_path_path_attribute_enabled_;
  }

  static bool SvgTextPathPathAttributeEnabled(const FeatureContext*) { return SvgTextPathPathAttributeEnabled(); }

  static bool SvgTransformOnNestedSvgElementEnabled() {
    return is_svg_transform_on_nested_svg_element_enabled_;
  }

  static bool SvgTransformOnNestedSvgElementEnabled(const FeatureContext*) { return SvgTransformOnNestedSvgElementEnabled(); }

  static bool SynthesizedKeyboardEventsForAccessibilityActionsEnabled() {
    return is_synthesized_keyboard_events_for_accessibility_actions_enabled_;
  }

  static bool SynthesizedKeyboardEventsForAccessibilityActionsEnabled(const FeatureContext*) { return SynthesizedKeyboardEventsForAccessibilityActionsEnabled(); }

  static bool SyntheticMouseHoverOverInactivePageEnabled() {
    return is_synthetic_mouse_hover_over_inactive_page_enabled_;
  }

  static bool SyntheticMouseHoverOverInactivePageEnabled(const FeatureContext*) { return SyntheticMouseHoverOverInactivePageEnabled(); }

  static bool SystemDefaultAccentColorsEnabled() {
    return is_system_default_accent_colors_enabled_;
  }

  static bool SystemDefaultAccentColorsEnabled(const FeatureContext*) { return SystemDefaultAccentColorsEnabled(); }

  static bool SystemFallbackEmojiVSSupportEnabled() {
    return is_system_fallback_emoji_vs_support_enabled_;
  }

  static bool SystemFallbackEmojiVSSupportEnabled(const FeatureContext*) { return SystemFallbackEmojiVSSupportEnabled(); }

  static bool SystemWakeLockEnabled() {
    return is_system_wake_lock_enabled_;
  }

  static bool SystemWakeLockEnabled(const FeatureContext*) { return SystemWakeLockEnabled(); }

  static bool TableBorderColorNoImplicitBorderEnabled() {
    return is_table_border_color_no_implicit_border_enabled_;
  }

  static bool TableBorderColorNoImplicitBorderEnabled(const FeatureContext*) { return TableBorderColorNoImplicitBorderEnabled(); }

  static bool TableDefaultBorderColorCurrentColorEnabled() {
    return is_table_default_border_color_current_color_enabled_;
  }

  static bool TableDefaultBorderColorCurrentColorEnabled(const FeatureContext*) { return TableDefaultBorderColorCurrentColorEnabled(); }

  static bool TableIsAutoFixedLayoutEnabled() {
    return is_table_is_auto_fixed_layout_enabled_;
  }

  static bool TableIsAutoFixedLayoutEnabled(const FeatureContext*) { return TableIsAutoFixedLayoutEnabled(); }

  static bool TabSizeAncestorEnabled() {
    return is_tab_size_ancestor_enabled_;
  }

  static bool TabSizeAncestorEnabled(const FeatureContext*) { return TabSizeAncestorEnabled(); }

  static bool TabSizeWithSpacingEnabled() {
    return is_tab_size_with_spacing_enabled_;
  }

  static bool TabSizeWithSpacingEnabled(const FeatureContext*) { return TabSizeWithSpacingEnabled(); }

  static bool TargetInShadowDeterminedBeforeListenerEnabled() {
    return is_target_in_shadow_determined_before_listener_enabled_;
  }

  static bool TargetInShadowDeterminedBeforeListenerEnabled(const FeatureContext*) { return TargetInShadowDeterminedBeforeListenerEnabled(); }

  static bool TestBlinkFeatureDefaultEnabled() {
    return is_test_blink_feature_default_enabled_;
  }

  static bool TestBlinkFeatureDefaultEnabled(const FeatureContext*) { return TestBlinkFeatureDefaultEnabled(); }

  static bool TestFeatureEnabled() {
    return is_test_feature_enabled_;
  }

  static bool TestFeatureEnabled(const FeatureContext*);

  static bool TestFeatureDependentEnabled() {
    if (!TestFeatureImpliedEnabled())
      return false;
    return is_test_feature_dependent_enabled_;
  }

  static bool TestFeatureDependentEnabled(const FeatureContext*) { return TestFeatureDependentEnabled(); }

  static bool TestFeatureImpliedEnabled() {
    if (TestFeatureEnabled())
      return true;
    return is_test_feature_implied_enabled_;
  }

  static bool TestFeatureImpliedEnabled(const FeatureContext*) { return TestFeatureImpliedEnabled(); }

  static bool TestFeatureProtectedEnabled() {
    return get_is_test_feature_protected_enabled_();
  }

  static bool TestFeatureProtectedEnabled(const FeatureContext*) { return TestFeatureProtectedEnabled(); }

  static bool TestFeatureProtectedDependentEnabled() {
    if (!TestFeatureProtectedImpliedEnabled())
      return false;
    return get_is_test_feature_protected_dependent_enabled_();
  }

  static bool TestFeatureProtectedDependentEnabled(const FeatureContext*) { return TestFeatureProtectedDependentEnabled(); }

  static bool TestFeatureProtectedImpliedEnabled() {
    if (TestFeatureProtectedEnabled())
      return true;
    return get_is_test_feature_protected_implied_enabled_();
  }

  static bool TestFeatureProtectedImpliedEnabled(const FeatureContext*) { return TestFeatureProtectedImpliedEnabled(); }

  static bool TestFeatureStableEnabled() {
    return is_test_feature_stable_enabled_;
  }

  static bool TestFeatureStableEnabled(const FeatureContext*) { return TestFeatureStableEnabled(); }

  static bool TextAreaScrollTopPreviewEnabled() {
    return is_text_area_scroll_top_preview_enabled_;
  }

  static bool TextAreaScrollTopPreviewEnabled(const FeatureContext*) { return TextAreaScrollTopPreviewEnabled(); }

  static bool TextDetectorEnabled() {
    return is_text_detector_enabled_;
  }

  static bool TextDetectorEnabled(const FeatureContext*) { return TextDetectorEnabled(); }

  static bool TextEmphasisLetterSpacingEnabled() {
    return is_text_emphasis_letter_spacing_enabled_;
  }

  static bool TextEmphasisLetterSpacingEnabled(const FeatureContext*) { return TextEmphasisLetterSpacingEnabled(); }

  static bool TextEmphasisPositionAutoEnabled() {
    return is_text_emphasis_position_auto_enabled_;
  }

  static bool TextEmphasisPositionAutoEnabled(const FeatureContext*) { return TextEmphasisPositionAutoEnabled(); }

  static bool TextEmphasisPunctuationExceptionsEnabled() {
    return is_text_emphasis_punctuation_exceptions_enabled_;
  }

  static bool TextEmphasisPunctuationExceptionsEnabled(const FeatureContext*) { return TextEmphasisPunctuationExceptionsEnabled(); }

  static bool TextEmphasisWithRubyEnabled() {
    return is_text_emphasis_with_ruby_enabled_;
  }

  static bool TextEmphasisWithRubyEnabled(const FeatureContext*) { return TextEmphasisWithRubyEnabled(); }

  static bool TextFragmentAPIEnabled() {
    return is_text_fragment_api_enabled_;
  }

  static bool TextFragmentAPIEnabled(const FeatureContext*) { return TextFragmentAPIEnabled(); }

  static bool TextFragmentTapOpensContextMenuEnabled() {
    return is_text_fragment_tap_opens_context_menu_enabled_;
  }

  static bool TextFragmentTapOpensContextMenuEnabled(const FeatureContext*) { return TextFragmentTapOpensContextMenuEnabled(); }

  static bool TextMetricsBaselinesEnabled() {
    return is_text_metrics_baselines_enabled_;
  }

  static bool TextMetricsBaselinesEnabled(const FeatureContext*) { return TextMetricsBaselinesEnabled(); }

  static bool TextOverflowClipWithSelectionEnabled() {
    return is_text_overflow_clip_with_selection_enabled_;
  }

  static bool TextOverflowClipWithSelectionEnabled(const FeatureContext*) { return TextOverflowClipWithSelectionEnabled(); }

  static bool TextOverflowStringEnabled() {
    return is_text_overflow_string_enabled_;
  }

  static bool TextOverflowStringEnabled(const FeatureContext*) { return TextOverflowStringEnabled(); }

  static bool TextScaleMetaTagEnabled() {
    return is_text_scale_meta_tag_enabled_;
  }

  static bool TextScaleMetaTagEnabled(const FeatureContext*) { return TextScaleMetaTagEnabled(); }

  static bool TextSpacingTrimFallbackEnabled() {
    return is_text_spacing_trim_fallback_enabled_;
  }

  static bool TextSpacingTrimFallbackEnabled(const FeatureContext*) { return TextSpacingTrimFallbackEnabled(); }

  static bool TextSpacingTrimFallback2Enabled() {
    if (!TextSpacingTrimFallbackEnabled())
      return false;
    return is_text_spacing_trim_fallback_2_enabled_;
  }

  static bool TextSpacingTrimFallback2Enabled(const FeatureContext*) { return TextSpacingTrimFallback2Enabled(); }

  static bool TextSpacingTrimFallbackChwsEnabled() {
    if (!TextSpacingTrimFallbackEnabled())
      return false;
    return is_text_spacing_trim_fallback_chws_enabled_;
  }

  static bool TextSpacingTrimFallbackChwsEnabled(const FeatureContext*) { return TextSpacingTrimFallbackChwsEnabled(); }

  static bool TextSpacingTrimYuGothicUIEnabled() {
    return is_text_spacing_trim_yu_gothic_ui_enabled_;
  }

  static bool TextSpacingTrimYuGothicUIEnabled(const FeatureContext*) { return TextSpacingTrimYuGothicUIEnabled(); }

  static bool ThrottledHistoryAPIThrowsSecurityErrorEnabled() {
    return is_throttled_history_api_throws_security_error_enabled_;
  }

  static bool ThrottledHistoryAPIThrowsSecurityErrorEnabled(const FeatureContext*) { return ThrottledHistoryAPIThrowsSecurityErrorEnabled(); }

  static bool TimelineTriggerEnabled() {
    return is_timeline_trigger_enabled_;
  }

  static bool TimelineTriggerEnabled(const FeatureContext*) { return TimelineTriggerEnabled(); }

  static bool TimerThrottlingForBackgroundTabsEnabled() {
    return is_timer_throttling_for_background_tabs_enabled_;
  }

  static bool TimerThrottlingForBackgroundTabsEnabled(const FeatureContext*) { return TimerThrottlingForBackgroundTabsEnabled(); }

  static bool TimestampBasedCLSTrackingEnabled() {
    return is_timestamp_based_cls_tracking_enabled_;
  }

  static bool TimestampBasedCLSTrackingEnabled(const FeatureContext*) { return TimestampBasedCLSTrackingEnabled(); }

  static bool TimeZoneChangeEventEnabled() {
    return is_time_zone_change_event_enabled_;
  }

  static bool TimeZoneChangeEventEnabled(const FeatureContext*) { return TimeZoneChangeEventEnabled(); }

  static bool TopicsAPIEnabled() {
    return is_topics_api_enabled_;
  }

  static bool TopicsAPIEnabled(const FeatureContext*) { return TopicsAPIEnabled(); }

  static bool TopicsDocumentAPIEnabled() {
    return is_topics_document_api_enabled_;
  }

  static bool TopicsDocumentAPIEnabled(const FeatureContext*) { return TopicsDocumentAPIEnabled(); }

  static bool TopicsImgAPIEnabled() {
    return is_topics_img_api_enabled_;
  }

  static bool TopicsImgAPIEnabled(const FeatureContext*) { return TopicsImgAPIEnabled(); }

  static bool TouchDragAndContextMenuEnabled() {
    return is_touch_drag_and_context_menu_enabled_;
  }

  static bool TouchDragAndContextMenuEnabled(const FeatureContext*) { return TouchDragAndContextMenuEnabled(); }

  static bool TouchDragAndDropEnabled() {
    return is_touch_drag_and_drop_enabled_;
  }

  static bool TouchDragAndDropEnabled(const FeatureContext*) { return TouchDragAndDropEnabled(); }

  static bool TouchDragOnShortPressEnabled() {
    if (!TouchDragAndDropEnabled())
      return false;
    return is_touch_drag_on_short_press_enabled_;
  }

  static bool TouchDragOnShortPressEnabled(const FeatureContext*) { return TouchDragOnShortPressEnabled(); }

  static bool TouchTextEditingRedesignEnabled() {
    return is_touch_text_editing_redesign_enabled_;
  }

  static bool TouchTextEditingRedesignEnabled(const FeatureContext*) { return TouchTextEditingRedesignEnabled(); }

  static bool TransferableRTCDataChannelEnabled() {
    return is_transferable_rtc_data_channel_enabled_;
  }

  static bool TransferableRTCDataChannelEnabled(const FeatureContext*) { return TransferableRTCDataChannelEnabled(); }

  static bool TransitionNavigationQuietSkipEnabled() {
    return is_transition_navigation_quiet_skip_enabled_;
  }

  static bool TransitionNavigationQuietSkipEnabled(const FeatureContext*) { return TransitionNavigationQuietSkipEnabled(); }

  static bool TranslateServiceEnabled() {
    return is_translate_service_enabled_;
  }

  static bool TranslateServiceEnabled(const FeatureContext*) { return TranslateServiceEnabled(); }

  static bool TranslationAPIEnabled() {
    return is_translation_api_enabled_;
  }

  static bool TranslationAPIEnabled(const FeatureContext*) { return TranslationAPIEnabled(); }

  static bool TranslationAPIForWorkersEnabled() {
    return is_translation_api_for_workers_enabled_;
  }

  static bool TranslationAPIForWorkersEnabled(const FeatureContext*) { return TranslationAPIForWorkersEnabled(); }

  static bool TraverseFlatTreeToHandleSlotsEnabled() {
    return is_traverse_flat_tree_to_handle_slots_enabled_;
  }

  static bool TraverseFlatTreeToHandleSlotsEnabled(const FeatureContext*) { return TraverseFlatTreeToHandleSlotsEnabled(); }

  static bool TreatMhtmlInitialDocumentLoadsAsCrossDocumentEnabled() {
    return is_treat_mhtml_initial_document_loads_as_cross_document_enabled_;
  }

  static bool TreatMhtmlInitialDocumentLoadsAsCrossDocumentEnabled(const FeatureContext*) { return TreatMhtmlInitialDocumentLoadsAsCrossDocumentEnabled(); }

  static bool TrustedTypesCreateParserOptionsEnabled() {
    if (!SanitizerAPIEnabled())
      return false;
    if (!SetHTMLCanRunScriptsEnabled())
      return false;
    return is_trusted_types_create_parser_options_enabled_;
  }

  static bool TrustedTypesCreateParserOptionsEnabled(const FeatureContext*) { return TrustedTypesCreateParserOptionsEnabled(); }

  static bool TrustedTypesFromLiteralEnabled() {
    return is_trusted_types_from_literal_enabled_;
  }

  static bool TrustedTypesFromLiteralEnabled(const FeatureContext*) { return TrustedTypesFromLiteralEnabled(); }

  static bool TrustedTypesHTMLEnabled() {
    return is_trusted_types_html_enabled_;
  }

  static bool TrustedTypesHTMLEnabled(const FeatureContext*) { return TrustedTypesHTMLEnabled(); }

  static bool TrustedTypesUseCodeLikeEnabled() {
    return is_trusted_types_use_code_like_enabled_;
  }

  static bool TrustedTypesUseCodeLikeEnabled(const FeatureContext*) { return TrustedTypesUseCodeLikeEnabled(); }

  static bool TwoPhaseViewTransitionEnabled() {
    return is_two_phase_view_transition_enabled_;
  }

  static bool TwoPhaseViewTransitionEnabled(const FeatureContext*) { return TwoPhaseViewTransitionEnabled(); }

  static bool UnclosedFormControlIsInvalidEnabled() {
    return is_unclosed_form_control_is_invalid_enabled_;
  }

  static bool UnclosedFormControlIsInvalidEnabled(const FeatureContext*) { return UnclosedFormControlIsInvalidEnabled(); }

  static bool UnexposedTaskIdsEnabled() {
    return is_unexposed_task_ids_enabled_;
  }

  static bool UnexposedTaskIdsEnabled(const FeatureContext*) { return UnexposedTaskIdsEnabled(); }

  static bool UnprefixedSpeechRecognitionEnabled() {
    return is_unprefixed_speech_recognition_enabled_;
  }

  static bool UnprefixedSpeechRecognitionEnabled(const FeatureContext*) { return UnprefixedSpeechRecognitionEnabled(); }

  static bool UnrestrictedMeasureUserAgentSpecificMemoryEnabled() {
    return is_unrestricted_measure_user_agent_specific_memory_enabled_;
  }

  static bool UnrestrictedMeasureUserAgentSpecificMemoryEnabled(const FeatureContext*) { return UnrestrictedMeasureUserAgentSpecificMemoryEnabled(); }

  static bool UnrestrictedUsbEnabled() {
    if (!WebUSBEnabled())
      return false;
    return is_unrestricted_usb_enabled_;
  }

  static bool UnrestrictedUsbEnabled(const FeatureContext*) { return UnrestrictedUsbEnabled(); }

  static bool UpdateComplexSafaAreaConstraintsEnabled() {
    return is_update_complex_safa_area_constraints_enabled_;
  }

  static bool UpdateComplexSafaAreaConstraintsEnabled(const FeatureContext*) { return UpdateComplexSafaAreaConstraintsEnabled(); }

  static bool UpdateSelectionOnNodeInsertionEnabled() {
    return is_update_selection_on_node_insertion_enabled_;
  }

  static bool UpdateSelectionOnNodeInsertionEnabled(const FeatureContext*) { return UpdateSelectionOnNodeInsertionEnabled(); }

  static bool UpdateTrivalTextAfterFragmentCreationFromTextEnabled() {
    return is_update_trival_text_after_fragment_creation_from_text_enabled_;
  }

  static bool UpdateTrivalTextAfterFragmentCreationFromTextEnabled(const FeatureContext*) { return UpdateTrivalTextAfterFragmentCreationFromTextEnabled(); }

  static bool URLPatternCompareComponentEnabled() {
    return is_url_pattern_compare_component_enabled_;
  }

  static bool URLPatternCompareComponentEnabled(const FeatureContext*) { return URLPatternCompareComponentEnabled(); }

  static bool URLPatternGenerateEnabled() {
    return is_url_pattern_generate_enabled_;
  }

  static bool URLPatternGenerateEnabled(const FeatureContext*) { return URLPatternGenerateEnabled(); }

  static bool URLSearchParamsHasAndDeleteMultipleArgsEnabled() {
    return is_url_search_params_has_and_delete_multiple_args_enabled_;
  }

  static bool URLSearchParamsHasAndDeleteMultipleArgsEnabled(const FeatureContext*) { return URLSearchParamsHasAndDeleteMultipleArgsEnabled(); }

  static bool UseBeginFramePresentationFeedbackEnabled() {
    return is_use_begin_frame_presentation_feedback_enabled_;
  }

  static bool UseBeginFramePresentationFeedbackEnabled(const FeatureContext*) { return UseBeginFramePresentationFeedbackEnabled(); }

  static bool UseBoundedSelectionOffsetsInEditContextDeleteOperationsEnabled() {
    return is_use_bounded_selection_offsets_in_edit_context_delete_operations_enabled_;
  }

  static bool UseBoundedSelectionOffsetsInEditContextDeleteOperationsEnabled(const FeatureContext*) { return UseBoundedSelectionOffsetsInEditContextDeleteOperationsEnabled(); }

  static bool UseLargestPaintedImageForLCPCandidateEnabled() {
    return is_use_largest_painted_image_for_lcp_candidate_enabled_;
  }

  static bool UseLargestPaintedImageForLCPCandidateEnabled(const FeatureContext*) { return UseLargestPaintedImageForLCPCandidateEnabled(); }

  static bool UseLowQualityInterpolationEnabled() {
    return is_use_low_quality_interpolation_enabled_;
  }

  static bool UseLowQualityInterpolationEnabled(const FeatureContext*) { return UseLowQualityInterpolationEnabled(); }

  static bool UseOriginalDomOffsetsForOffsetMapEnabled() {
    return is_use_original_dom_offsets_for_offset_map_enabled_;
  }

  static bool UseOriginalDomOffsetsForOffsetMapEnabled(const FeatureContext*) { return UseOriginalDomOffsetsForOffsetMapEnabled(); }

  static bool UsePositionForPointInFlexibleBoxWithSingleChildElementEnabled() {
    return is_use_position_for_point_in_flexible_box_with_single_child_element_enabled_;
  }

  static bool UsePositionForPointInFlexibleBoxWithSingleChildElementEnabled(const FeatureContext*) { return UsePositionForPointInFlexibleBoxWithSingleChildElementEnabled(); }

  static bool UsePositionIfIsVisuallyEquivalentCandidateEnabled() {
    return is_use_position_if_is_visually_equivalent_candidate_enabled_;
  }

  static bool UsePositionIfIsVisuallyEquivalentCandidateEnabled(const FeatureContext*) { return UsePositionIfIsVisuallyEquivalentCandidateEnabled(); }

  static bool UserActionPseudosStopAtTopLayerEnabled() {
    return is_user_action_pseudos_stop_at_top_layer_enabled_;
  }

  static bool UserActionPseudosStopAtTopLayerEnabled(const FeatureContext*) { return UserActionPseudosStopAtTopLayerEnabled(); }

  static bool UserDefinedEntryPointTimingEnabled() {
    return is_user_defined_entry_point_timing_enabled_;
  }

  static bool UserDefinedEntryPointTimingEnabled(const FeatureContext*) { return UserDefinedEntryPointTimingEnabled(); }

  static bool UseSelectionInDOMTreeAnchorInExtendSelectionEnabled() {
    return is_use_selection_in_dom_tree_anchor_in_extend_selection_enabled_;
  }

  static bool UseSelectionInDOMTreeAnchorInExtendSelectionEnabled(const FeatureContext*) { return UseSelectionInDOMTreeAnchorInExtendSelectionEnabled(); }

  static bool UseShadowHostStyleCheckEditableEnabled() {
    return is_use_shadow_host_style_check_editable_enabled_;
  }

  static bool UseShadowHostStyleCheckEditableEnabled(const FeatureContext*) { return UseShadowHostStyleCheckEditableEnabled(); }

  static bool UseUndoStepElementDispatchBeforeInputEnabled() {
    return is_use_undo_step_element_dispatch_before_input_enabled_;
  }

  static bool UseUndoStepElementDispatchBeforeInputEnabled(const FeatureContext*) { return UseUndoStepElementDispatchBeforeInputEnabled(); }

  static bool V8IdleTasksEnabled() {
    return is_v8_idle_tasks_enabled_;
  }

  static bool V8IdleTasksEnabled(const FeatureContext*) { return V8IdleTasksEnabled(); }

  static bool VideoAutoFullscreenEnabled() {
    return is_video_auto_fullscreen_enabled_;
  }

  static bool VideoAutoFullscreenEnabled(const FeatureContext*) { return VideoAutoFullscreenEnabled(); }

  static bool VideoFrameMetadataBackgroundBlurEnabled() {
    return is_video_frame_metadata_background_blur_enabled_;
  }

  static bool VideoFrameMetadataBackgroundBlurEnabled(const FeatureContext*) { return VideoFrameMetadataBackgroundBlurEnabled(); }

  static bool VideoFrameMetadataRtpTimestampEnabled() {
    return is_video_frame_metadata_rtp_timestamp_enabled_;
  }

  static bool VideoFrameMetadataRtpTimestampEnabled(const FeatureContext*) { return VideoFrameMetadataRtpTimestampEnabled(); }

  static bool VideoFullscreenOrientationLockEnabled() {
    return is_video_fullscreen_orientation_lock_enabled_;
  }

  static bool VideoFullscreenOrientationLockEnabled(const FeatureContext*) { return VideoFullscreenOrientationLockEnabled(); }

  static bool VideoRotateToFullscreenEnabled() {
    return is_video_rotate_to_fullscreen_enabled_;
  }

  static bool VideoRotateToFullscreenEnabled(const FeatureContext*) { return VideoRotateToFullscreenEnabled(); }

  static bool VideoTrackGeneratorEnabled() {
    return is_video_track_generator_enabled_;
  }

  static bool VideoTrackGeneratorEnabled(const FeatureContext*) { return VideoTrackGeneratorEnabled(); }

  static bool VideoTrackGeneratorInWindowEnabled() {
    return is_video_track_generator_in_window_enabled_;
  }

  static bool VideoTrackGeneratorInWindowEnabled(const FeatureContext*) { return VideoTrackGeneratorInWindowEnabled(); }

  static bool VideoTrackGeneratorInWorkerEnabled() {
    return is_video_track_generator_in_worker_enabled_;
  }

  static bool VideoTrackGeneratorInWorkerEnabled(const FeatureContext*) { return VideoTrackGeneratorInWorkerEnabled(); }

  static bool ViewportHeightClientHintHeaderEnabled() {
    return is_viewport_height_client_hint_header_enabled_;
  }

  static bool ViewportHeightClientHintHeaderEnabled(const FeatureContext*) { return ViewportHeightClientHintHeaderEnabled(); }

  static bool ViewportSegmentsEnabled() {
    return is_viewport_segments_enabled_;
  }

  static bool ViewportSegmentsEnabled(const FeatureContext*) { return ViewportSegmentsEnabled(); }

  static bool ViewTransitionAsyncFinishedEnabled() {
    return is_view_transition_async_finished_enabled_;
  }

  static bool ViewTransitionAsyncFinishedEnabled(const FeatureContext*) { return ViewTransitionAsyncFinishedEnabled(); }

  static bool ViewTransitionDelayUnpauseOnTeardownEnabled() {
    return is_view_transition_delay_unpause_on_teardown_enabled_;
  }

  static bool ViewTransitionDelayUnpauseOnTeardownEnabled(const FeatureContext*) { return ViewTransitionDelayUnpauseOnTeardownEnabled(); }

  static bool ViewTransitionHoistBackdropFilterEffectEnabled() {
    return is_view_transition_hoist_backdrop_filter_effect_enabled_;
  }

  static bool ViewTransitionHoistBackdropFilterEffectEnabled(const FeatureContext*) { return ViewTransitionHoistBackdropFilterEffectEnabled(); }

  static bool ViewTransitionLongCallbackTimeoutForTestingEnabled() {
    return is_view_transition_long_callback_timeout_for_testing_enabled_;
  }

  static bool ViewTransitionLongCallbackTimeoutForTestingEnabled(const FeatureContext*) { return ViewTransitionLongCallbackTimeoutForTestingEnabled(); }

  static bool ViewTransitionUpdateLifecycleBeforeReadyEnabled() {
    return is_view_transition_update_lifecycle_before_ready_enabled_;
  }

  static bool ViewTransitionUpdateLifecycleBeforeReadyEnabled(const FeatureContext*) { return ViewTransitionUpdateLifecycleBeforeReadyEnabled(); }

  static bool ViewTransitionWaitUntilEnabled() {
    return is_view_transition_wait_until_enabled_;
  }

  static bool ViewTransitionWaitUntilEnabled(const FeatureContext*) { return ViewTransitionWaitUntilEnabled(); }

  static bool VisibilityCollapseColumnEnabled() {
    return is_visibility_collapse_column_enabled_;
  }

  static bool VisibilityCollapseColumnEnabled(const FeatureContext*) { return VisibilityCollapseColumnEnabled(); }

  static bool VisualRectMappingFixForExpansionEnabled() {
    return is_visual_rect_mapping_fix_for_expansion_enabled_;
  }

  static bool VisualRectMappingFixForExpansionEnabled(const FeatureContext*) { return VisualRectMappingFixForExpansionEnabled(); }

  static bool WakeLockEnabled() {
    if (SystemWakeLockEnabled())
      return true;
    return is_wake_lock_enabled_;
  }

  static bool WakeLockEnabled(const FeatureContext*) { return WakeLockEnabled(); }

  static bool WarnOnContentVisibilityRenderAccessEnabled() {
    return is_warn_on_content_visibility_render_access_enabled_;
  }

  static bool WarnOnContentVisibilityRenderAccessEnabled(const FeatureContext*) { return WarnOnContentVisibilityRenderAccessEnabled(); }

  static bool WebAppLaunchQueueEnabled() {
    return is_web_app_launch_queue_enabled_;
  }

  static bool WebAppLaunchQueueEnabled(const FeatureContext*) { return WebAppLaunchQueueEnabled(); }

  static bool WebAppScopeSystemAccentColorEnabled() {
    return is_web_app_scope_system_accent_color_enabled_;
  }

  static bool WebAppScopeSystemAccentColorEnabled(const FeatureContext*) { return WebAppScopeSystemAccentColorEnabled(); }

  static bool WebAppTabStripEnabled() {
    return is_web_app_tab_strip_enabled_;
  }

  static bool WebAppTabStripEnabled(const FeatureContext*) { return WebAppTabStripEnabled(); }

  static bool WebAppTabStripCustomizationsEnabled() {
    return is_web_app_tab_strip_customizations_enabled_;
  }

  static bool WebAppTabStripCustomizationsEnabled(const FeatureContext*) { return WebAppTabStripCustomizationsEnabled(); }

  static bool WebAppTranslationsEnabled() {
    return is_web_app_translations_enabled_;
  }

  static bool WebAppTranslationsEnabled(const FeatureContext*) { return WebAppTranslationsEnabled(); }

  static bool WebAudioBypassOutputBufferingEnabled() {
    return is_web_audio_bypass_output_buffering_enabled_;
  }

  static bool WebAudioBypassOutputBufferingEnabled(const FeatureContext*) { return WebAudioBypassOutputBufferingEnabled(); }

  static bool WebAudioBypassOutputBufferingOptOutEnabled() {
    return is_web_audio_bypass_output_buffering_opt_out_enabled_;
  }

  static bool WebAudioBypassOutputBufferingOptOutEnabled(const FeatureContext*) { return WebAudioBypassOutputBufferingOptOutEnabled(); }

  static bool WebAuthEnabled() {
    return is_web_auth_enabled_;
  }

  static bool WebAuthEnabled(const FeatureContext*) { return WebAuthEnabled(); }

  static bool WebAuthAuthenticatorAttachmentEnabled() {
    return is_web_auth_authenticator_attachment_enabled_;
  }

  static bool WebAuthAuthenticatorAttachmentEnabled(const FeatureContext*) { return WebAuthAuthenticatorAttachmentEnabled(); }

  static bool WebAuthenticationAmbientEnabled() {
    return is_web_authentication_ambient_enabled_;
  }

  static bool WebAuthenticationAmbientEnabled(const FeatureContext*) { return WebAuthenticationAmbientEnabled(); }

  static bool WebAuthenticationImmediateGetEnabled() {
    return is_web_authentication_immediate_get_enabled_;
  }

  static bool WebAuthenticationImmediateGetEnabled(const FeatureContext*) { return WebAuthenticationImmediateGetEnabled(); }

  static bool WebAuthenticationRemoteDesktopSupportEnabled() {
    return is_web_authentication_remote_desktop_support_enabled_;
  }

  static bool WebAuthenticationRemoteDesktopSupportEnabled(const FeatureContext*) { return WebAuthenticationRemoteDesktopSupportEnabled(); }

  static bool WebAuthenticationSupplementalPubKeysEnabled() {
    return is_web_authentication_supplemental_pub_keys_enabled_;
  }

  static bool WebAuthenticationSupplementalPubKeysEnabled(const FeatureContext*) { return WebAuthenticationSupplementalPubKeysEnabled(); }

  static bool WebBluetoothEnabled() {
    return is_web_bluetooth_enabled_;
  }

  static bool WebBluetoothEnabled(const FeatureContext*) { return WebBluetoothEnabled(); }

  static bool WebBluetoothGetDevicesEnabled() {
    return is_web_bluetooth_get_devices_enabled_;
  }

  static bool WebBluetoothGetDevicesEnabled(const FeatureContext*) { return WebBluetoothGetDevicesEnabled(); }

  static bool WebBluetoothScanningEnabled() {
    return is_web_bluetooth_scanning_enabled_;
  }

  static bool WebBluetoothScanningEnabled(const FeatureContext*) { return WebBluetoothScanningEnabled(); }

  static bool WebBluetoothWatchAdvertisementsEnabled() {
    return is_web_bluetooth_watch_advertisements_enabled_;
  }

  static bool WebBluetoothWatchAdvertisementsEnabled(const FeatureContext*) { return WebBluetoothWatchAdvertisementsEnabled(); }

  static bool WebCodecsVideoEncoderBuffersEnabled() {
    return is_webcodecs_video_encoder_buffers_enabled_;
  }

  static bool WebCodecsVideoEncoderBuffersEnabled(const FeatureContext*) { return WebCodecsVideoEncoderBuffersEnabled(); }

  static bool WebCryptoPQCEnabled() {
    return is_web_crypto_pqc_enabled_;
  }

  static bool WebCryptoPQCEnabled(const FeatureContext*) { return WebCryptoPQCEnabled(); }

  static bool WebFontResizeLCPEnabled() {
    return is_web_font_resize_lcp_enabled_;
  }

  static bool WebFontResizeLCPEnabled(const FeatureContext*) { return WebFontResizeLCPEnabled(); }

  static bool WebGLDeveloperExtensionsEnabled() {
    return is_webgl_developer_extensions_enabled_;
  }

  static bool WebGLDeveloperExtensionsEnabled(const FeatureContext*) { return WebGLDeveloperExtensionsEnabled(); }

  static bool WebGLDraftExtensionsEnabled() {
    return is_webgl_draft_extensions_enabled_;
  }

  static bool WebGLDraftExtensionsEnabled(const FeatureContext*) { return WebGLDraftExtensionsEnabled(); }

  static bool WebGLDrawingBufferStorageEnabled() {
    return is_webgl_drawing_buffer_storage_enabled_;
  }

  static bool WebGLDrawingBufferStorageEnabled(const FeatureContext*) { return WebGLDrawingBufferStorageEnabled(); }

  static bool WebGLOnWebGPUEnabled() {
    return is_webgl_on_webgpu_enabled_;
  }

  static bool WebGLOnWebGPUEnabled(const FeatureContext*) { return WebGLOnWebGPUEnabled(); }

  static bool WebGPUDeveloperFeaturesEnabled() {
    return is_webgpu_developer_features_enabled_;
  }

  static bool WebGPUDeveloperFeaturesEnabled(const FeatureContext*) { return WebGPUDeveloperFeaturesEnabled(); }

  static bool WebGPUExperimentalFeaturesEnabled() {
    return is_webgpu_experimental_features_enabled_;
  }

  static bool WebGPUExperimentalFeaturesEnabled(const FeatureContext*) { return WebGPUExperimentalFeaturesEnabled(); }

  static bool WebGPUImmediatesFeatureEnabled() {
    if (WebGPUExperimentalFeaturesEnabled())
      return true;
    return is_webgpu_immediates_feature_enabled_;
  }

  static bool WebGPUImmediatesFeatureEnabled(const FeatureContext*) { return WebGPUImmediatesFeatureEnabled(); }

  static bool WebGPUMapSyncOnWorkersEnabled() {
    return is_webgpu_map_sync_on_workers_enabled_;
  }

  static bool WebGPUMapSyncOnWorkersEnabled(const FeatureContext*) { return WebGPUMapSyncOnWorkersEnabled(); }

  static bool WebGPUMultithreadDawnWireOnWorkersEnabled() {
    if (WebGPUMapSyncOnWorkersEnabled())
      return true;
    return is_webgpu_multithread_dawn_wire_on_workers_enabled_;
  }

  static bool WebGPUMultithreadDawnWireOnWorkersEnabled(const FeatureContext*) { return WebGPUMultithreadDawnWireOnWorkersEnabled(); }

  static bool WebGPUTransientAttachmentEnabled() {
    return is_webgpu_transient_attachment_enabled_;
  }

  static bool WebGPUTransientAttachmentEnabled(const FeatureContext*) { return WebGPUTransientAttachmentEnabled(); }

  static bool WebHIDEnabled() {
    return is_web_hid_enabled_;
  }

  static bool WebHIDEnabled(const FeatureContext*) { return WebHIDEnabled(); }

  static bool WebHIDOnServiceWorkersEnabled() {
    if (!WebHIDEnabled())
      return false;
    return is_web_hid_on_service_workers_enabled_;
  }

  static bool WebHIDOnServiceWorkersEnabled(const FeatureContext*) { return WebHIDOnServiceWorkersEnabled(); }

  static bool WebIdentityDigitalCredentialsEnabled() {
    return is_web_identity_digital_credentials_enabled_;
  }

  static bool WebIdentityDigitalCredentialsEnabled(const FeatureContext*) { return WebIdentityDigitalCredentialsEnabled(); }

  static bool WebIDLBigIntUsesToBigIntEnabled() {
    return is_web_idl_big_int_uses_to_big_int_enabled_;
  }

  static bool WebIDLBigIntUsesToBigIntEnabled(const FeatureContext*) { return WebIDLBigIntUsesToBigIntEnabled(); }

  static bool WebMCPDeclarativeFileInputEnabled() {
    return is_web_mcp_declarative_file_input_enabled_;
  }

  static bool WebMCPDeclarativeFileInputEnabled(const FeatureContext*) { return WebMCPDeclarativeFileInputEnabled(); }

  static bool WebMCPFormAssociatedCustomElementsEnabled() {
    return is_web_mcp_form_associated_custom_elements_enabled_;
  }

  static bool WebMCPFormAssociatedCustomElementsEnabled(const FeatureContext*) { return WebMCPFormAssociatedCustomElementsEnabled(); }

  static bool WebMCPTestingEnabled() {
    return is_web_mcp_testing_enabled_;
  }

  static bool WebMCPTestingEnabled(const FeatureContext*) { return WebMCPTestingEnabled(); }

  static bool WebNFCEnabled() {
    return is_web_nfc_enabled_;
  }

  static bool WebNFCEnabled(const FeatureContext*) { return WebNFCEnabled(); }

  static bool WebOTPEnabled() {
    return is_web_otp_enabled_;
  }

  static bool WebOTPEnabled(const FeatureContext*) { return WebOTPEnabled(); }

  static bool WebOTPAssertionFeaturePolicyEnabled() {
    if (!WebOTPEnabled())
      return false;
    return is_web_otp_assertion_feature_policy_enabled_;
  }

  static bool WebOTPAssertionFeaturePolicyEnabled(const FeatureContext*) { return WebOTPAssertionFeaturePolicyEnabled(); }

  static bool WebPreferencesEnabled() {
    return is_web_preferences_enabled_;
  }

  static bool WebPreferencesEnabled(const FeatureContext*) { return WebPreferencesEnabled(); }

  static bool WebPrintingEnabled() {
    return is_web_printing_enabled_;
  }

  static bool WebPrintingEnabled(const FeatureContext*) { return WebPrintingEnabled(); }

  static bool WebShareEnabled() {
    return is_web_share_enabled_;
  }

  static bool WebShareEnabled(const FeatureContext*) { return WebShareEnabled(); }

  static bool WebSocketStreamEnabled() {
    return is_websocket_stream_enabled_;
  }

  static bool WebSocketStreamEnabled(const FeatureContext*) { return WebSocketStreamEnabled(); }

  static bool WebSocketStreamStandardBinaryChunkTypeEnabled() {
    return is_websocket_stream_standard_binary_chunk_type_enabled_;
  }

  static bool WebSocketStreamStandardBinaryChunkTypeEnabled(const FeatureContext*) { return WebSocketStreamStandardBinaryChunkTypeEnabled(); }

  static bool WebSpeechRecognitionContextEnabled() {
    return is_web_speech_recognition_context_enabled_;
  }

  static bool WebSpeechRecognitionContextEnabled(const FeatureContext*) { return WebSpeechRecognitionContextEnabled(); }

  static bool WebTransportApplicationProtocolEnabled() {
    return is_web_transport_application_protocol_enabled_;
  }

  static bool WebTransportApplicationProtocolEnabled(const FeatureContext*) { return WebTransportApplicationProtocolEnabled(); }

  static bool WebTransportCongestionControlEnabled() {
    return is_web_transport_congestion_control_enabled_;
  }

  static bool WebTransportCongestionControlEnabled(const FeatureContext*) { return WebTransportCongestionControlEnabled(); }

  static bool WebTransportSendGroupEnabled() {
    return is_web_transport_send_group_enabled_;
  }

  static bool WebTransportSendGroupEnabled(const FeatureContext*) { return WebTransportSendGroupEnabled(); }

  static bool WebTransportStatsEnabled() {
    return is_web_transport_stats_enabled_;
  }

  static bool WebTransportStatsEnabled(const FeatureContext*) { return WebTransportStatsEnabled(); }

  static bool WebUIBundledCodeCacheAsyncFetchEnabled() {
    return is_web_ui_bundled_code_cache_async_fetch_enabled_;
  }

  static bool WebUIBundledCodeCacheAsyncFetchEnabled(const FeatureContext*) { return WebUIBundledCodeCacheAsyncFetchEnabled(); }

  static bool WebUSBEnabled() {
    return is_web_usb_enabled_;
  }

  static bool WebUSBEnabled(const FeatureContext*) { return WebUSBEnabled(); }

  static bool WebUSBOnDedicatedWorkersEnabled() {
    if (!WebUSBEnabled())
      return false;
    return is_web_usb_on_dedicated_workers_enabled_;
  }

  static bool WebUSBOnDedicatedWorkersEnabled(const FeatureContext*) { return WebUSBOnDedicatedWorkersEnabled(); }

  static bool WebUSBOnServiceWorkersEnabled() {
    if (!WebUSBEnabled())
      return false;
    return is_web_usb_on_service_workers_enabled_;
  }

  static bool WebUSBOnServiceWorkersEnabled(const FeatureContext*) { return WebUSBOnServiceWorkersEnabled(); }

  static bool WebVTTRegionsEnabled() {
    return is_web_vtt_regions_enabled_;
  }

  static bool WebVTTRegionsEnabled(const FeatureContext*) { return WebVTTRegionsEnabled(); }

  static bool WebXREnabled() {
    return is_web_xr_enabled_;
  }

  static bool WebXREnabled(const FeatureContext*) { return WebXREnabled(); }

  static bool WebXREnabledFeaturesEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_enabled_features_enabled_;
  }

  static bool WebXREnabledFeaturesEnabled(const FeatureContext*) { return WebXREnabledFeaturesEnabled(); }

  static bool WebXRFrameRateEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_frame_rate_enabled_;
  }

  static bool WebXRFrameRateEnabled(const FeatureContext*) { return WebXRFrameRateEnabled(); }

  static bool WebXRFrontFacingEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_front_facing_enabled_;
  }

  static bool WebXRFrontFacingEnabled(const FeatureContext*) { return WebXRFrontFacingEnabled(); }

  static bool WebXRGPUBindingEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_gpu_binding_enabled_;
  }

  static bool WebXRGPUBindingEnabled(const FeatureContext*) { return WebXRGPUBindingEnabled(); }

  static bool WebXRHitTestEntityTypesEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_hit_test_entity_types_enabled_;
  }

  static bool WebXRHitTestEntityTypesEnabled(const FeatureContext*) { return WebXRHitTestEntityTypesEnabled(); }

  static bool WebXRLayersEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_layers_enabled_;
  }

  static bool WebXRLayersEnabled(const FeatureContext*) { return WebXRLayersEnabled(); }

  static bool WebXRLayersCommonEnabled() {
    if (WebXRLayersEnabled())
      return true;
    if (WebXRGPUBindingEnabled())
      return true;
    return is_web_xr_layers_common_enabled_;
  }

  static bool WebXRLayersCommonEnabled(const FeatureContext*) { return WebXRLayersCommonEnabled(); }

  static bool WebXRMeshDetectionEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_mesh_detection_enabled_;
  }

  static bool WebXRMeshDetectionEnabled(const FeatureContext*) { return WebXRMeshDetectionEnabled(); }

  static bool WebXRPoseMotionDataEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_pose_motion_data_enabled_;
  }

  static bool WebXRPoseMotionDataEnabled(const FeatureContext*) { return WebXRPoseMotionDataEnabled(); }

  static bool WebXRSpecParityEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_spec_parity_enabled_;
  }

  static bool WebXRSpecParityEnabled(const FeatureContext*) { return WebXRSpecParityEnabled(); }

  static bool WebXRVisibilityMaskEnabled() {
    if (!WebXREnabled())
      return false;
    return is_web_xr_visibility_mask_enabled_;
  }

  static bool WebXRVisibilityMaskEnabled(const FeatureContext*) { return WebXRVisibilityMaskEnabled(); }

  static bool WindowDefaultStatusEnabled() {
    return is_window_default_status_enabled_;
  }

  static bool WindowDefaultStatusEnabled(const FeatureContext*) { return WindowDefaultStatusEnabled(); }

  static bool WordSkipSpacesPunctuationFixEnabled() {
    return is_word_skip_spaces_punctuation_fix_enabled_;
  }

  static bool WordSkipSpacesPunctuationFixEnabled(const FeatureContext*) { return WordSkipSpacesPunctuationFixEnabled(); }

  static bool WordSpacingWhiteSpacePreEnabled() {
    return is_word_spacing_white_space_pre_enabled_;
  }

  static bool WordSpacingWhiteSpacePreEnabled(const FeatureContext*) { return WordSpacingWhiteSpacePreEnabled(); }

  static bool XMLNoExternalEntitiesEnabled() {
    return is_xml_no_external_entities_enabled_;
  }

  static bool XMLNoExternalEntitiesEnabled(const FeatureContext*) { return XMLNoExternalEntitiesEnabled(); }

  static bool XMLParsingRustEnabled() {
    return is_xml_parsing_rust_enabled_;
  }

  static bool XMLParsingRustEnabled(const FeatureContext*) { return XMLParsingRustEnabled(); }

  static bool XMLRustForNonXsltEnabled() {
    return is_xml_rust_for_non_xslt_enabled_;
  }

  static bool XMLRustForNonXsltEnabled(const FeatureContext*) { return XMLRustForNonXsltEnabled(); }

  static bool XMLSerializerConsistentDefaultNsDeclMatchingEnabled() {
    return is_xml_serializer_consistent_default_ns_decl_matching_enabled_;
  }

  static bool XMLSerializerConsistentDefaultNsDeclMatchingEnabled(const FeatureContext*) { return XMLSerializerConsistentDefaultNsDeclMatchingEnabled(); }

  static bool XPathShadowDOMSupportEnabled() {
    return is_xpath_shadow_dom_support_enabled_;
  }

  static bool XPathShadowDOMSupportEnabled(const FeatureContext*) { return XPathShadowDOMSupportEnabled(); }

  static bool XSLTEnabled() {
    return is_xslt_enabled_;
  }

  static bool XSLTEnabled(const FeatureContext*) { return XSLTEnabled(); }

  static bool XSLTSpecialTrialEnabled() {
    return is_xslt_special_trial_enabled_;
  }

  static bool XSLTSpecialTrialEnabled(const FeatureContext*) { return XSLTSpecialTrialEnabled(); }


  // Origin-trial-enabled features:
  //
  // These features are currently part of an origin trial (see
  // https://www.chromium.org/blink/origin-trials). <feature>EnabledByRuntimeFlag()
  // can be used to test whether the feature is unconditionally enabled
  // (for example, by starting the browser with the appropriate command-line flag).
  // However, that is almost always the incorrect check. Most renderer code should
  // be calling <feature>Enabled(const FeatureContext*) instead, to test if the
  // feature is enabled in a given context.

  static bool AdInterestGroupAPIEnabledByRuntimeFlag() { return AdInterestGroupAPIEnabled(nullptr); }
  static bool AdInterestGroupAPIEnabled(const FeatureContext*);

  static bool AIPromptAPILegacyParamsEnabledByRuntimeFlag() { return AIPromptAPILegacyParamsEnabled(nullptr); }
  static bool AIPromptAPILegacyParamsEnabled(const FeatureContext*);

  static bool AIPromptAPIParamsEnabledByRuntimeFlag() { return AIPromptAPIParamsEnabled(nullptr); }
  static bool AIPromptAPIParamsEnabled(const FeatureContext*);

  static bool AIProofreadingAPIEnabledByRuntimeFlag() { return AIProofreadingAPIEnabled(nullptr); }
  static bool AIProofreadingAPIEnabled(const FeatureContext*);

  static bool AIRewriterAPIEnabledByRuntimeFlag() { return AIRewriterAPIEnabled(nullptr); }
  static bool AIRewriterAPIEnabled(const FeatureContext*);

  static bool AIWriterAPIEnabledByRuntimeFlag() { return AIWriterAPIEnabled(nullptr); }
  static bool AIWriterAPIEnabled(const FeatureContext*);

  static bool AppTitleEnabledByRuntimeFlag() { return AppTitleEnabled(nullptr); }
  static bool AppTitleEnabled(const FeatureContext*);

  static bool AudioContextPlayoutStatsEnabledByRuntimeFlag() { return AudioContextPlayoutStatsEnabled(nullptr); }
  static bool AudioContextPlayoutStatsEnabled(const FeatureContext*);

  static bool AutoDarkModeEnabledByRuntimeFlag() { return AutoDarkModeEnabled(nullptr); }
  static bool AutoDarkModeEnabled(const FeatureContext*);

  static bool AutofillEventEnabledByRuntimeFlag() { return AutofillEventEnabled(nullptr); }
  static bool AutofillEventEnabled(const FeatureContext*);

  static bool BackForwardCacheExperimentHTTPHeaderEnabledByRuntimeFlag() { return BackForwardCacheExperimentHTTPHeaderEnabled(nullptr); }
  static bool BackForwardCacheExperimentHTTPHeaderEnabled(const FeatureContext*);

  static bool BackForwardCacheNotRestoredReasonsEnabledByRuntimeFlag() { return BackForwardCacheNotRestoredReasonsEnabled(nullptr); }
  static bool BackForwardCacheNotRestoredReasonsEnabled(const FeatureContext*);

  static bool BackgroundPageFreezeOptOutEnabledByRuntimeFlag() { return BackgroundPageFreezeOptOutEnabled(nullptr); }
  static bool BackgroundPageFreezeOptOutEnabled(const FeatureContext*);

  static bool BlockingFocusWithoutUserActivationEnabledByRuntimeFlag() { return BlockingFocusWithoutUserActivationEnabled(nullptr); }
  static bool BlockingFocusWithoutUserActivationEnabled(const FeatureContext*);

  static bool CacheStorageCodeCacheHintEnabledByRuntimeFlag() { return CacheStorageCodeCacheHintEnabled(nullptr); }
  static bool CacheStorageCodeCacheHintEnabled(const FeatureContext*);

  static bool Canvas2dMeshEnabledByRuntimeFlag() { return Canvas2dMeshEnabled(nullptr); }
  static bool Canvas2dMeshEnabled(const FeatureContext*);

  static bool CanvasDrawElementEnabledByRuntimeFlag() { return CanvasDrawElementEnabled(nullptr); }
  static bool CanvasDrawElementEnabled(const FeatureContext*);

  static bool ConnectionAllowlistEnabledByRuntimeFlag() { return ConnectionAllowlistEnabled(nullptr); }
  static bool ConnectionAllowlistEnabled(const FeatureContext*);

  static bool ContainerTimingEnabledByRuntimeFlag() { return ContainerTimingEnabled(nullptr); }
  static bool ContainerTimingEnabled(const FeatureContext*);

  static bool CoopRestrictPropertiesEnabledByRuntimeFlag() { return CoopRestrictPropertiesEnabled(nullptr); }
  static bool CoopRestrictPropertiesEnabled(const FeatureContext*);

  static bool CpuPerformanceEnabledByRuntimeFlag() { return CpuPerformanceEnabled(nullptr); }
  static bool CpuPerformanceEnabled(const FeatureContext*);

  static bool CrashReportingStorageAPIEnabledByRuntimeFlag() { return CrashReportingStorageAPIEnabled(nullptr); }
  static bool CrashReportingStorageAPIEnabled(const FeatureContext*);

  static bool CSPHashesV1EnabledByRuntimeFlag() { return CSPHashesV1Enabled(nullptr); }
  static bool CSPHashesV1Enabled(const FeatureContext*);

  static bool DeclarativeCSSModulesEnabledByRuntimeFlag() { return DeclarativeCSSModulesEnabled(nullptr); }
  static bool DeclarativeCSSModulesEnabled(const FeatureContext*);

  static bool DeclarativeCSSModulesStyleTagEnabledByRuntimeFlag() { return DeclarativeCSSModulesStyleTagEnabled(nullptr); }
  static bool DeclarativeCSSModulesStyleTagEnabled(const FeatureContext*);

  static bool DeprecateUnloadOptOutEnabledByRuntimeFlag() { return DeprecateUnloadOptOutEnabled(nullptr); }
  static bool DeprecateUnloadOptOutEnabled(const FeatureContext*);

  static bool DigitalGoodsEnabledByRuntimeFlag() { return DigitalGoodsEnabled(nullptr); }
  static bool DigitalGoodsEnabled(const FeatureContext*);

  static bool DisableDifferentOriginSubframeDialogSuppressionEnabledByRuntimeFlag() { return DisableDifferentOriginSubframeDialogSuppressionEnabled(nullptr); }
  static bool DisableDifferentOriginSubframeDialogSuppressionEnabled(const FeatureContext*);

  static bool DisableReduceAcceptLanguageEnabledByRuntimeFlag() { return DisableReduceAcceptLanguageEnabled(nullptr); }
  static bool DisableReduceAcceptLanguageEnabled(const FeatureContext*);

  static bool DocumentIsolationPolicyEnabledByRuntimeFlag() { return DocumentIsolationPolicyEnabled(nullptr); }
  static bool DocumentIsolationPolicyEnabled(const FeatureContext*);

  static bool DocumentPolicyNegotiationEnabledByRuntimeFlag() { return DocumentPolicyNegotiationEnabled(nullptr); }
  static bool DocumentPolicyNegotiationEnabled(const FeatureContext*);

  static bool ExtendedTextMetricsEnabledByRuntimeFlag() { return ExtendedTextMetricsEnabled(nullptr); }
  static bool ExtendedTextMetricsEnabled(const FeatureContext*);

  static bool FedCmMultipleIdentityProvidersEnabledByRuntimeFlag() { return FedCmMultipleIdentityProvidersEnabled(nullptr); }
  static bool FedCmMultipleIdentityProvidersEnabled(const FeatureContext*);

  static bool FetchRetryEnabledByRuntimeFlag() { return FetchRetryEnabled(nullptr); }
  static bool FetchRetryEnabled(const FeatureContext*);

  static bool FledgeBiddingAndAuctionServerAPIEnabledByRuntimeFlag() { return FledgeBiddingAndAuctionServerAPIEnabled(nullptr); }
  static bool FledgeBiddingAndAuctionServerAPIEnabled(const FeatureContext*);

  static bool FocusgroupEnabledByRuntimeFlag() { return FocusgroupEnabled(nullptr); }
  static bool FocusgroupEnabled(const FeatureContext*);

  static bool FocusgroupGridEnabledByRuntimeFlag() { return FocusgroupGridEnabled(nullptr); }
  static bool FocusgroupGridEnabled(const FeatureContext*);

  static bool HrefTranslateEnabledByRuntimeFlag() { return HrefTranslateEnabled(nullptr); }
  static bool HrefTranslateEnabled(const FeatureContext*);

  static bool IncomingCallNotificationsEnabledByRuntimeFlag() { return IncomingCallNotificationsEnabled(nullptr); }
  static bool IncomingCallNotificationsEnabled(const FeatureContext*);

  static bool InstallElementEnabledByRuntimeFlag() { return InstallElementEnabled(nullptr); }
  static bool InstallElementEnabled(const FeatureContext*);

  static bool JavaScriptCompileHintsPerFunctionMagicRuntimeEnabledByRuntimeFlag() { return JavaScriptCompileHintsPerFunctionMagicRuntimeEnabled(nullptr); }
  static bool JavaScriptCompileHintsPerFunctionMagicRuntimeEnabled(const FeatureContext*);

  static bool LocalNetworkAccessNonSecureContextAllowedEnabledByRuntimeFlag() { return LocalNetworkAccessNonSecureContextAllowedEnabled(nullptr); }
  static bool LocalNetworkAccessNonSecureContextAllowedEnabled(const FeatureContext*);

  static bool LongAnimationFrameStyleDurationEnabledByRuntimeFlag() { return LongAnimationFrameStyleDurationEnabled(nullptr); }
  static bool LongAnimationFrameStyleDurationEnabled(const FeatureContext*);

  static bool MediaCaptureBackgroundBlurEnabledByRuntimeFlag() { return MediaCaptureBackgroundBlurEnabled(nullptr); }
  static bool MediaCaptureBackgroundBlurEnabled(const FeatureContext*);

  static bool MediaCaptureConfigurationChangeEnabledByRuntimeFlag() { return MediaCaptureConfigurationChangeEnabled(nullptr); }
  static bool MediaCaptureConfigurationChangeEnabled(const FeatureContext*);

  static bool MediaPlaybackWhileNotVisiblePermissionPolicyEnabledByRuntimeFlag() { return MediaPlaybackWhileNotVisiblePermissionPolicyEnabled(nullptr); }
  static bool MediaPlaybackWhileNotVisiblePermissionPolicyEnabled(const FeatureContext*);

  static bool MediaSourceExtensionsForWebCodecsEnabledByRuntimeFlag() { return MediaSourceExtensionsForWebCodecsEnabled(nullptr); }
  static bool MediaSourceExtensionsForWebCodecsEnabled(const FeatureContext*);

  static bool NavigationIdEnabledByRuntimeFlag() { return NavigationIdEnabled(nullptr); }
  static bool NavigationIdEnabled(const FeatureContext*);

  static bool NotificationTriggersEnabledByRuntimeFlag() { return NotificationTriggersEnabled(nullptr); }
  static bool NotificationTriggersEnabled(const FeatureContext*);

  static bool OpaqueRangeEnabledByRuntimeFlag() { return OpaqueRangeEnabled(nullptr); }
  static bool OpaqueRangeEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIEnabledByRuntimeFlag() { return OriginTrialsSampleAPIEnabled(nullptr); }
  static bool OriginTrialsSampleAPIEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIBrowserReadWriteEnabledByRuntimeFlag() { return OriginTrialsSampleAPIBrowserReadWriteEnabled(nullptr); }
  static bool OriginTrialsSampleAPIBrowserReadWriteEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIDependentEnabledByRuntimeFlag() { return OriginTrialsSampleAPIDependentEnabled(nullptr); }
  static bool OriginTrialsSampleAPIDependentEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIDeprecationEnabledByRuntimeFlag() { return OriginTrialsSampleAPIDeprecationEnabled(nullptr); }
  static bool OriginTrialsSampleAPIDeprecationEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIExpiryGracePeriodEnabledByRuntimeFlag() { return OriginTrialsSampleAPIExpiryGracePeriodEnabled(nullptr); }
  static bool OriginTrialsSampleAPIExpiryGracePeriodEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIExpiryGracePeriodThirdPartyEnabledByRuntimeFlag() { return OriginTrialsSampleAPIExpiryGracePeriodThirdPartyEnabled(nullptr); }
  static bool OriginTrialsSampleAPIExpiryGracePeriodThirdPartyEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIImpliedEnabledByRuntimeFlag() { return OriginTrialsSampleAPIImpliedEnabled(nullptr); }
  static bool OriginTrialsSampleAPIImpliedEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIInvalidOSEnabledByRuntimeFlag() { return OriginTrialsSampleAPIInvalidOSEnabled(nullptr); }
  static bool OriginTrialsSampleAPIInvalidOSEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPINavigationEnabledByRuntimeFlag() { return OriginTrialsSampleAPINavigationEnabled(nullptr); }
  static bool OriginTrialsSampleAPINavigationEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIPersistentExpiryGracePeriodEnabledByRuntimeFlag() { return OriginTrialsSampleAPIPersistentExpiryGracePeriodEnabled(nullptr); }
  static bool OriginTrialsSampleAPIPersistentExpiryGracePeriodEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIPersistentFeatureEnabledByRuntimeFlag() { return OriginTrialsSampleAPIPersistentFeatureEnabled(nullptr); }
  static bool OriginTrialsSampleAPIPersistentFeatureEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIPersistentInvalidOSEnabledByRuntimeFlag() { return OriginTrialsSampleAPIPersistentInvalidOSEnabled(nullptr); }
  static bool OriginTrialsSampleAPIPersistentInvalidOSEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIPersistentThirdPartyDeprecationFeatureEnabledByRuntimeFlag() { return OriginTrialsSampleAPIPersistentThirdPartyDeprecationFeatureEnabled(nullptr); }
  static bool OriginTrialsSampleAPIPersistentThirdPartyDeprecationFeatureEnabled(const FeatureContext*);

  static bool OriginTrialsSampleAPIThirdPartyEnabledByRuntimeFlag() { return OriginTrialsSampleAPIThirdPartyEnabled(nullptr); }
  static bool OriginTrialsSampleAPIThirdPartyEnabled(const FeatureContext*);

  static bool ParakeetEnabledByRuntimeFlag() { return ParakeetEnabled(nullptr); }
  static bool ParakeetEnabled(const FeatureContext*);

  static bool PerMethodCanMakePaymentQuotaEnabledByRuntimeFlag() { return PerMethodCanMakePaymentQuotaEnabled(nullptr); }
  static bool PerMethodCanMakePaymentQuotaEnabled(const FeatureContext*);

  static bool PNaClEnabledByRuntimeFlag() { return PNaClEnabled(nullptr); }
  static bool PNaClEnabled(const FeatureContext*);

  static bool PreferredAudioOutputDevicesEnabledByRuntimeFlag() { return PreferredAudioOutputDevicesEnabled(nullptr); }
  static bool PreferredAudioOutputDevicesEnabled(const FeatureContext*);

  static bool Prerender2CrossOriginIframesEnabledByRuntimeFlag() { return Prerender2CrossOriginIframesEnabled(nullptr); }
  static bool Prerender2CrossOriginIframesEnabled(const FeatureContext*);

  static bool PrerenderActivationByFormSubmissionEnabledByRuntimeFlag() { return PrerenderActivationByFormSubmissionEnabled(nullptr); }
  static bool PrerenderActivationByFormSubmissionEnabled(const FeatureContext*);

  static bool PrerenderUntilScriptEnabledByRuntimeFlag() { return PrerenderUntilScriptEnabled(nullptr); }
  static bool PrerenderUntilScriptEnabled(const FeatureContext*);

  static bool ProtectedOriginTrialsSampleAPIEnabledByRuntimeFlag() { return ProtectedOriginTrialsSampleAPIEnabled(nullptr); }
  static bool ProtectedOriginTrialsSampleAPIEnabled(const FeatureContext*);

  static bool ProtectedOriginTrialsSampleAPIDependentEnabledByRuntimeFlag() { return ProtectedOriginTrialsSampleAPIDependentEnabled(nullptr); }
  static bool ProtectedOriginTrialsSampleAPIDependentEnabled(const FeatureContext*);

  static bool ProtectedOriginTrialsSampleAPIImpliedEnabledByRuntimeFlag() { return ProtectedOriginTrialsSampleAPIImpliedEnabled(nullptr); }
  static bool ProtectedOriginTrialsSampleAPIImpliedEnabled(const FeatureContext*);

  static bool RenderBlockingFullFrameRateEnabledByRuntimeFlag() { return RenderBlockingFullFrameRateEnabled(nullptr); }
  static bool RenderBlockingFullFrameRateEnabled(const FeatureContext*);

  static bool RtcAudioJitterBufferMaxPacketsEnabledByRuntimeFlag() { return RtcAudioJitterBufferMaxPacketsEnabled(nullptr); }
  static bool RtcAudioJitterBufferMaxPacketsEnabled(const FeatureContext*);

  static bool RTCEncodedFrameSetMetadataEnabledByRuntimeFlag() { return RTCEncodedFrameSetMetadataEnabled(nullptr); }
  static bool RTCEncodedFrameSetMetadataEnabled(const FeatureContext*);

  static bool RTCLegacyCallbackBasedGetStatsEnabledByRuntimeFlag() { return RTCLegacyCallbackBasedGetStatsEnabled(nullptr); }
  static bool RTCLegacyCallbackBasedGetStatsEnabled(const FeatureContext*);

  static bool RTCStatsRelativePacketArrivalDelayEnabledByRuntimeFlag() { return RTCStatsRelativePacketArrivalDelayEnabled(nullptr); }
  static bool RTCStatsRelativePacketArrivalDelayEnabled(const FeatureContext*);

  static bool SecurePaymentConfirmationOptOutEnabledByRuntimeFlag() { return SecurePaymentConfirmationOptOutEnabled(nullptr); }
  static bool SecurePaymentConfirmationOptOutEnabled(const FeatureContext*);

  static bool ShadowRootAdoptedStyleSheetEnabledByRuntimeFlag() { return ShadowRootAdoptedStyleSheetEnabled(nullptr); }
  static bool ShadowRootAdoptedStyleSheetEnabled(const FeatureContext*);

  static bool ShadowRootReferenceTargetEnabledByRuntimeFlag() { return ShadowRootReferenceTargetEnabled(nullptr); }
  static bool ShadowRootReferenceTargetEnabled(const FeatureContext*);

  static bool SharedWorkerExtendedLifetimeEnabledByRuntimeFlag() { return SharedWorkerExtendedLifetimeEnabled(nullptr); }
  static bool SharedWorkerExtendedLifetimeEnabled(const FeatureContext*);

  static bool SoftNavigationHeuristicsEnabledByRuntimeFlag() { return SoftNavigationHeuristicsEnabled(nullptr); }
  static bool SoftNavigationHeuristicsEnabled(const FeatureContext*);

  static bool StandardizedBrowserZoomOptOutEnabledByRuntimeFlag() { return StandardizedBrowserZoomOptOutEnabled(nullptr); }
  static bool StandardizedBrowserZoomOptOutEnabled(const FeatureContext*);

  static bool TestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabledByRuntimeFlag() { return TestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(nullptr); }
  static bool TestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(const FeatureContext*);

  static bool TextFragmentIdentifiersEnabledByRuntimeFlag() { return TextFragmentIdentifiersEnabled(nullptr); }
  static bool TextFragmentIdentifiersEnabled(const FeatureContext*);

  static bool TouchEventFeatureDetectionEnabledByRuntimeFlag() { return TouchEventFeatureDetectionEnabled(nullptr); }
  static bool TouchEventFeatureDetectionEnabled(const FeatureContext*);

  static bool UnrestrictedSharedArrayBufferEnabledByRuntimeFlag() { return UnrestrictedSharedArrayBufferEnabled(nullptr); }
  static bool UnrestrictedSharedArrayBufferEnabled(const FeatureContext*);

  static bool UserMediaElementEnabledByRuntimeFlag() { return UserMediaElementEnabled(nullptr); }
  static bool UserMediaElementEnabled(const FeatureContext*);

  static bool WebAppInstallationEnabledByRuntimeFlag() { return WebAppInstallationEnabled(nullptr); }
  static bool WebAppInstallationEnabled(const FeatureContext*);

  static bool WebAppScopeExtensionsEnabledByRuntimeFlag() { return WebAppScopeExtensionsEnabled(nullptr); }
  static bool WebAppScopeExtensionsEnabled(const FeatureContext*);

  static bool WebAssemblyCustomDescriptorsV2EnabledByRuntimeFlag() { return WebAssemblyCustomDescriptorsV2Enabled(nullptr); }
  static bool WebAssemblyCustomDescriptorsV2Enabled(const FeatureContext*);

  static bool WebAssemblyJSPromiseIntegrationEnabledByRuntimeFlag() { return WebAssemblyJSPromiseIntegrationEnabled(nullptr); }
  static bool WebAssemblyJSPromiseIntegrationEnabled(const FeatureContext*);

  static bool WebAudioConfigurableRenderQuantumEnabledByRuntimeFlag() { return WebAudioConfigurableRenderQuantumEnabled(nullptr); }
  static bool WebAudioConfigurableRenderQuantumEnabled(const FeatureContext*);

  static bool WebAuthenticationAttestationFormatsEnabledByRuntimeFlag() { return WebAuthenticationAttestationFormatsEnabled(nullptr); }
  static bool WebAuthenticationAttestationFormatsEnabled(const FeatureContext*);

  static bool WebGPUCompatibilityModeEnabledByRuntimeFlag() { return WebGPUCompatibilityModeEnabled(nullptr); }
  static bool WebGPUCompatibilityModeEnabled(const FeatureContext*);

  static bool WebIdentityDigitalCredentialsCreationEnabledByRuntimeFlag() { return WebIdentityDigitalCredentialsCreationEnabled(nullptr); }
  static bool WebIdentityDigitalCredentialsCreationEnabled(const FeatureContext*);

  static bool WebMCPEnabledByRuntimeFlag() { return WebMCPEnabled(nullptr); }
  static bool WebMCPEnabled(const FeatureContext*);

  static bool WebTransportCustomCertificatesEnabledByRuntimeFlag() { return WebTransportCustomCertificatesEnabled(nullptr); }
  static bool WebTransportCustomCertificatesEnabled(const FeatureContext*);

  static bool WebXRImageTrackingEnabledByRuntimeFlag() { return WebXRImageTrackingEnabled(nullptr); }
  static bool WebXRImageTrackingEnabled(const FeatureContext*);

  static bool WebXRPlaneDetectionEnabledByRuntimeFlag() { return WebXRPlaneDetectionEnabled(nullptr); }
  static bool WebXRPlaneDetectionEnabled(const FeatureContext*);


  static bool IsFeatureEnabledFromString(const std::string& name);

 protected:
  // See the comment in RuntimeEnabledFeatures for why these are protected.
  static void SetStableFeaturesEnabled(bool);
  static void SetExperimentalFeaturesEnabled(bool);
  static void SetTestFeaturesEnabled(bool);
  static void SetOriginTrialControlledFeaturesEnabled(bool);

  static void SetFeatureEnabledFromString(const std::string& name, bool enabled);
  static void UpdateStatusFromBaseFeatures();

  static void SetAboutBlankPageRespectsDarkModeOnUserActionEnabled(bool enabled) { is_about_blank_page_respects_dark_mode_on_user_action_enabled_ = enabled; }
  static void SetAccelerated2dCanvasEnabled(bool enabled) { is_accelerated_2d_canvas_enabled_ = enabled; }
  static void SetAcceleratedSmallCanvasesEnabled(bool enabled) { is_accelerated_small_canvases_enabled_ = enabled; }
  static void SetAccessibilityAriaVirtualContentEnabled(bool enabled) { is_accessibility_aria_virtual_content_enabled_ = enabled; }
  static void SetAccessibilityCustomElementRoleNoneEnabled(bool enabled) { is_accessibility_custom_element_role_none_enabled_ = enabled; }
  static void SetAccessibilityExposeDisplayNoneEnabled(bool enabled) { is_accessibility_expose_display_none_enabled_ = enabled; }
  static void SetAccessibilityImplicitActionsEnabled(bool enabled) { is_accessibility_implicit_actions_enabled_ = enabled; }
  static void SetAccessibilityMinRoleTabbableEnabled(bool enabled) { is_accessibility_min_role_tabbable_enabled_ = enabled; }
  static void SetAccessibilityOSLevelBoldTextEnabled(bool enabled) { is_accessibility_os_level_bold_text_enabled_ = enabled; }
  static void SetAccessibilityProhibitedNamesEnabled(bool enabled) { is_accessibility_prohibited_names_enabled_ = enabled; }
  static void SetAccessibilitySerializationSizeMetricsEnabled(bool enabled) { is_accessibility_serialization_size_metrics_enabled_ = enabled; }
  static void SetAccessibilityUseAXPositionForDocumentMarkersEnabled(bool enabled) { is_accessibility_use_ax_position_for_document_markers_enabled_ = enabled; }
  static void SetAccessKeyLabelEnabled(bool enabled) { is_access_key_label_enabled_ = enabled; }
  static void SetAddressSpaceEnabled(bool enabled) { is_address_space_enabled_ = enabled; }
  static void SetAdInterestGroupAPIEnabled(bool enabled) { is_ad_interest_group_api_enabled_ = enabled; }
  static void SetAdjustDOMOffsetToLayoutOffsetForSecureTextEnabled(bool enabled) { is_adjust_dom_offset_to_layout_offset_for_secure_text_enabled_ = enabled; }
  static void SetAdjustEndOfNextParagraphIfMovedParagraphIsUpdatedEnabled(bool enabled) { is_adjust_end_of_next_paragraph_if_moved_paragraph_is_updated_enabled_ = enabled; }
  static void SetAdTaggingEnabled(bool enabled) { is_ad_tagging_enabled_ = enabled; }
  static void SetAIClassifierAPIEnabled(bool enabled) { is_ai_classifier_api_enabled_ = enabled; }
  static void SetAIPageContentAnchoredOffscreenNonActionabilityEnabled(bool enabled) { is_ai_page_content_anchored_offscreen_non_actionability_enabled_ = enabled; }
  static void SetAIPageContentBuildOnLoadForTestingEnabled(bool enabled) { is_ai_page_content_build_on_load_for_testing_enabled_ = enabled; }
  static void SetAIPageContentCheckGeometryEnabled(bool enabled) { is_ai_page_content_check_geometry_enabled_ = enabled; }
  static void SetAIPageContentConvertNodeTextToUtf8Enabled(bool enabled) { is_ai_page_content_convert_node_text_to_utf_8_enabled_ = enabled; }
  static void SetAIPageContentElementCSSRedactionEnabled(bool enabled) { is_ai_page_content_element_css_redaction_enabled_ = enabled; }
  static void SetAIPageContentIncludeSVGSubtreeEnabled(bool enabled) { is_ai_page_content_include_svg_subtree_enabled_ = enabled; }
  static void SetAIPageContentOuterBoxMapToAncestorSpaceEnabled(bool enabled) { is_ai_page_content_outer_box_map_to_ancestor_space_enabled_ = enabled; }
  static void SetAIPageContentPaidContentAnnotationEnabled(bool enabled) { is_ai_page_content_paid_content_annotation_enabled_ = enabled; }
  static void SetAIPageContentVisualViewportClampEnabled(bool enabled) { is_ai_page_content_visual_viewport_clamp_enabled_ = enabled; }
  static void SetAIPromptAPIEnabled(bool enabled) { is_ai_prompt_api_enabled_ = enabled; }
  static void SetAIPromptAPIForExtensionEnabled(bool enabled) { is_ai_prompt_api_for_extension_enabled_ = enabled; }
  static void SetAIPromptAPIForWorkersEnabled(bool enabled) { is_ai_prompt_api_for_workers_enabled_ = enabled; }
  static void SetAIPromptAPILegacyIdentifiersEnabled(bool enabled) { is_ai_prompt_api_legacy_identifiers_enabled_ = enabled; }
  static void SetAIPromptAPILegacyParamsEnabled(bool enabled) { is_ai_prompt_api_legacy_params_enabled_ = enabled; }
  static void SetAIPromptAPIMultimodalInputEnabled(bool enabled) { is_ai_prompt_api_multimodal_input_enabled_ = enabled; }
  static void SetAIPromptAPIParamsEnabled(bool enabled) { is_ai_prompt_api_params_enabled_ = enabled; }
  static void SetAIPromptAPIStructuredOutputEnabled(bool enabled) { is_ai_prompt_api_structured_output_enabled_ = enabled; }
  static void SetAIPromptAPIToolUseEnabled(bool enabled) { is_ai_prompt_api_tool_use_enabled_ = enabled; }
  static void SetAIProofreadingAPIEnabled(bool enabled) { is_ai_proofreading_api_enabled_ = enabled; }
  static void SetAIRewriterAPIEnabled(bool enabled) { is_ai_rewriter_api_enabled_ = enabled; }
  static void SetAIRewriterAPIForWorkersEnabled(bool enabled) { is_ai_rewriter_api_for_workers_enabled_ = enabled; }
  static void SetAISummarizationAPIEnabled(bool enabled) { is_ai_summarization_api_enabled_ = enabled; }
  static void SetAISummarizationAPIForWorkersEnabled(bool enabled) { is_ai_summarization_api_for_workers_enabled_ = enabled; }
  static void SetAISummarizationPerformancePreferenceEnabled(bool enabled) { is_ai_summarization_performance_preference_enabled_ = enabled; }
  static void SetAIWriterAPIEnabled(bool enabled) { is_ai_writer_api_enabled_ = enabled; }
  static void SetAIWriterAPIForWorkersEnabled(bool enabled) { is_ai_writer_api_for_workers_enabled_ = enabled; }
  static void SetAlignZoomToCenterEnabled(bool enabled) { is_align_zoom_to_center_enabled_ = enabled; }
  static void SetAllImagesPaintedSentToElementTimingEnabled(bool enabled) { is_all_images_painted_sent_to_element_timing_enabled_ = enabled; }
  static void SetAllowContentInitiatedDataUrlNavigationsEnabled(bool enabled) { is_allow_content_initiated_data_url_navigations_enabled_ = enabled; }
  static void SetAllowPreloadingWithCSPMetaTagEnabled(bool enabled) { is_allow_preloading_with_csp_meta_tag_enabled_ = enabled; }
  static void SetAllowSameSiteNoneCookiesInSandboxEnabled(bool enabled) { is_allow_same_site_none_cookies_in_sandbox_enabled_ = enabled; }
  static void SetAllowSkippingEditingBoundaryToMergeEndEnabled(bool enabled) { is_allow_skipping_editing_boundary_to_merge_end_enabled_ = enabled; }
  static void SetAllowSvgUseToReferenceExternalDocumentRootEnabled(bool enabled) { is_allow_svg_use_to_reference_external_document_root_enabled_ = enabled; }
  static void SetAllowSyntheticTimingForCanvasCaptureEnabled(bool enabled) { is_allow_synthetic_timing_for_canvas_capture_enabled_ = enabled; }
  static void SetAllowURNsInIframesEnabled(bool enabled) { is_allow_ur_ns_in_iframes_enabled_ = enabled; }
  static void SetAncestorOriginsStoredOnDocumentEnabled(bool enabled) { is_ancestor_origins_stored_on_document_enabled_ = enabled; }
  static void SetAncestorRevealingNewSpecEnabled(bool enabled) { is_ancestor_revealing_new_spec_enabled_ = enabled; }
  static void SetAnchorFocusRingFixEnabled(bool enabled) { is_anchor_focus_ring_fix_enabled_ = enabled; }
  static void SetAnchorPositionAdjustmentWithoutOverflowEnabled(bool enabled) { is_anchor_position_adjustment_without_overflow_enabled_ = enabled; }
  static void SetAndroidDownloadableFontsMatchingEnabled(bool enabled) { is_android_downloadable_fonts_matching_enabled_ = enabled; }
  static void SetAnimationProgressAPIEnabled(bool enabled) { is_animation_progress_api_enabled_ = enabled; }
  static void SetAnimationTriggerEnabled(bool enabled) { is_animation_trigger_enabled_ = enabled; }
  static void SetAnimationWorkletEnabled(bool enabled) { is_animation_worklet_enabled_ = enabled; }
  static void SetAnonymousIframeEnabled(bool enabled) { is_anonymous_iframe_enabled_ = enabled; }
  static void SetAOMAriaRelationshipPropertiesEnabled(bool enabled) { is_aom_aria_relationship_properties_enabled_ = enabled; }
  static void SetAOMAriaRelationshipPropertiesAriaOwnsEnabled(bool enabled) { is_aom_aria_relationship_properties_aria_owns_enabled_ = enabled; }
  static void SetAppearanceBaseEnabled(bool enabled) { is_appearance_base_enabled_ = enabled; }
  static void SetApproximateGeolocationPermissionEnabled(bool enabled) { is_approximate_geolocation_permission_enabled_ = enabled; }
  static void SetApproximateGeolocationPermissionAPIEnabled(bool enabled) { is_approximate_geolocation_permission_api_enabled_ = enabled; }
  static void SetApproximateGeolocationWebVisibleAPIEnabled(bool enabled) { is_approximate_geolocation_web_visible_api_enabled_ = enabled; }
  static void SetAppTitleEnabled(bool enabled) { is_app_title_enabled_ = enabled; }
  static void SetAriaActionsEnabled(bool enabled) { is_aria_actions_enabled_ = enabled; }
  static void SetAriaNotifyEnabled(bool enabled) { is_aria_notify_enabled_ = enabled; }
  static void SetAriaNotifyV2Enabled(bool enabled) { is_aria_notify_v_2_enabled_ = enabled; }
  static void SetAriaRowColIndexTextEnabled(bool enabled) { is_aria_row_col_index_text_enabled_ = enabled; }
  static void SetAsyncSetCookieEnabled(bool enabled) { is_async_set_cookie_enabled_ = enabled; }
  static void SetAttributionReportingEnabled(bool enabled) { is_attribution_reporting_enabled_ = enabled; }
  static void SetAudioContextAsyncStateTransitionsEnabled(bool enabled) { is_audio_context_async_state_transitions_enabled_ = enabled; }
  static void SetAudioContextPlaybackStatsEnabled(bool enabled) { is_audio_context_playback_stats_enabled_ = enabled; }
  static void SetAudioContextPlayoutStatsEnabled(bool enabled) { is_audio_context_playout_stats_enabled_ = enabled; }
  static void SetAudioContextSetSinkIdEnabled(bool enabled) { is_audio_context_set_sink_id_enabled_ = enabled; }
  static void SetAudioOutputDevicesEnabled(bool enabled) { is_audio_output_devices_enabled_ = enabled; }
  static void SetAudioVideoTracksEnabled(bool enabled) { is_audio_video_tracks_enabled_ = enabled; }
  static void SetAuthenticatorPasswordsOnlyImmediateRequestsEnabled(bool enabled) { is_authenticator_passwords_only_immediate_requests_enabled_ = enabled; }
  static void SetAuthorSpecifiedLayoutScrollSnapBehaviorEnabled(bool enabled) { is_author_specified_layout_scroll_snap_behavior_enabled_ = enabled; }
  static void SetAutoDarkModeEnabled(bool enabled) { is_auto_dark_mode_enabled_ = enabled; }
  static void SetAutofillEnabled(bool enabled) { is_autofill_enabled_ = enabled; }
  static void SetAutofillEventEnabled(bool enabled) { is_autofill_event_enabled_ = enabled; }
  static void SetAutomationControlledEnabled(bool enabled) { is_automation_controlled_enabled_ = enabled; }
  static void SetAutoPictureInPictureVideoHeuristicsEnabled(bool enabled) { is_auto_picture_in_picture_video_heuristics_enabled_ = enabled; }
  static void SetAvoidForcedLayoutOnInvisibleDocumentCloseEnabled(bool enabled) { is_avoid_forced_layout_on_invisible_document_close_enabled_ = enabled; }
  static void SetAvoidMergingStyledSpanWithSiblingsEnabled(bool enabled) { is_avoid_merging_styled_span_with_siblings_enabled_ = enabled; }
  static void SetAvoidNormalizingVisiblePositionsWhenStartEqualsEndEnabled(bool enabled) { is_avoid_normalizing_visible_positions_when_start_equals_end_enabled_ = enabled; }
  static void SetBackfaceVisibilityInteropEnabled(bool enabled) { is_backface_visibility_interop_enabled_ = enabled; }
  static void SetBackForwardCacheEnabled(bool enabled) { is_back_forward_cache_enabled_ = enabled; }
  static void SetBackForwardCacheExperimentHTTPHeaderEnabled(bool enabled) { is_back_forward_cache_experiment_http_header_enabled_ = enabled; }
  static void SetBackForwardCacheNotRestoredReasonsEnabled(bool enabled) { is_back_forward_cache_not_restored_reasons_enabled_ = enabled; }
  static void SetBackForwardCacheRestorationPerformanceEntryEnabled(bool enabled) { is_back_forward_cache_restoration_performance_entry_enabled_ = enabled; }
  static void SetBackForwardCacheUpdateNotRestoredReasonsNameEnabled(bool enabled) { is_back_forward_cache_update_not_restored_reasons_name_enabled_ = enabled; }
  static void SetBackgroundClipTextDecorationEnabled(bool enabled) { is_background_clip_text_decoration_enabled_ = enabled; }
  static void SetBackgroundFetchEnabled(bool enabled) { is_background_fetch_enabled_ = enabled; }
  static void SetBackgroundPageFreezeOptOutEnabled(bool enabled) { is_background_page_freeze_opt_out_enabled_ = enabled; }
  static void SetBarcodeDetectorEnabled(bool enabled) { is_barcode_detector_enabled_ = enabled; }
  static void SetBaseAppearanceInlineSizingEnabled(bool enabled) { is_base_appearance_inline_sizing_enabled_ = enabled; }
  static void SetBidiCaretAffinityEnabled(bool enabled) { is_bidi_caret_affinity_enabled_ = enabled; }
  static void SetBlinkExtensionChromeOSEnabled(bool enabled) { is_blink_extension_chrome_os_enabled_ = enabled; }
  static void SetBlinkExtensionChromeOSIsolatedWebAppSetShapeEnabled(bool enabled) { is_blink_extension_chrome_os_isolated_web_app_set_shape_enabled_ = enabled; }
  static void SetBlinkExtensionChromeOSKioskEnabled(bool enabled) { is_blink_extension_chrome_os_kiosk_enabled_ = enabled; }
  static void SetBlinkExtensionWebViewEnabled(bool enabled) { is_blink_extension_web_view_enabled_ = enabled; }
  static void SetBlinkExtensionWebViewMediaIntegrityEnabled(bool enabled) { is_blink_extension_web_view_media_integrity_enabled_ = enabled; }
  static void SetBlinkGeometryMapperViewportFastPathEnabled(bool enabled) { is_blink_geometry_mapper_viewport_fast_path_enabled_ = enabled; }
  static void SetBlinkLifecycleScriptForbiddenEnabled(bool enabled) { is_blink_lifecycle_script_forbidden_enabled_ = enabled; }
  static void SetBlinkRuntimeCallStatsEnabled(bool enabled) { is_blink_runtime_call_stats_enabled_ = enabled; }
  static void SetBlobBytesEnabled(bool enabled) { is_blob_bytes_enabled_ = enabled; }
  static void SetBlockingFocusWithoutUserActivationEnabled(bool enabled) { is_blocking_focus_without_user_activation_enabled_ = enabled; }
  static void SetBlockSelectPopupUnfocusedWindowEnabled(bool enabled) { is_block_select_popup_unfocused_window_enabled_ = enabled; }
  static void SetBoundaryEventDispatchTracksNodeRemovalEnabled(bool enabled) { is_boundary_event_dispatch_tracks_node_removal_enabled_ = enabled; }
  static void SetBrowserInitiatedAutomaticPictureInPictureEnabled(bool enabled) { is_browser_initiated_automatic_picture_in_picture_enabled_ = enabled; }
  static void SetBrowserVerifiedUserActivationKeyboardEnabled(bool enabled) { is_browser_verified_user_activation_keyboard_enabled_ = enabled; }
  static void SetBrowserVerifiedUserActivationMouseEnabled(bool enabled) { is_browser_verified_user_activation_mouse_enabled_ = enabled; }
  static void SetBufferedBytesConsumerLimitSizeEnabled(bool enabled) { is_buffered_bytes_consumer_limit_size_enabled_ = enabled; }
  static void SetBypassPepcSecurityForTestingEnabled(bool enabled) { is_bypass_pepc_security_for_testing_enabled_ = enabled; }
  static void SetCacheControlRFC7234ParsingEnabled(bool enabled) { is_cache_control_rfc_7234_parsing_enabled_ = enabled; }
  static void SetCacheControlRFC7234ParsingMetricsEnabled(bool enabled) { is_cache_control_rfc_7234_parsing_metrics_enabled_ = enabled; }
  static void SetCacheStorageCodeCacheHintEnabled(bool enabled) { is_cache_storage_code_cache_hint_enabled_ = enabled; }
  static void SetCacheStyleAdjusterEnabled(bool enabled) { is_cache_style_adjuster_enabled_ = enabled; }
  static void SetCallExitNodeWithoutLayoutObjectEnabled(bool enabled) { is_call_exit_node_without_layout_object_enabled_ = enabled; }
  static void SetCanvas2dCanvasFilterEnabled(bool enabled) { is_canvas_2d_canvas_filter_enabled_ = enabled; }
  static void SetCanvas2dGPUTransferEnabled(bool enabled) { is_canvas_2d_gpu_transfer_enabled_ = enabled; }
  static void SetCanvas2dLayersEnabled(bool enabled) { is_canvas_2d_layers_enabled_ = enabled; }
  static void SetCanvas2dLayersWithOptionsEnabled(bool enabled) { is_canvas_2d_layers_with_options_enabled_ = enabled; }
  static void SetCanvas2dMeshEnabled(bool enabled) { is_canvas_2d_mesh_enabled_ = enabled; }
  static void SetCanvasDrawElementEnabled(bool enabled) { is_canvas_draw_element_enabled_ = enabled; }
  static void SetCanvasFloatingPointEnabled(bool enabled) { is_canvas_floating_point_enabled_ = enabled; }
  static void SetCanvasGlobalHDRHeadroomEnabled(bool enabled) { is_canvas_global_hdr_headroom_enabled_ = enabled; }
  static void SetCanvasGradientCSSColor4Enabled(bool enabled) { is_canvas_gradient_css_color_4_enabled_ = enabled; }
  static void SetCanvasHDREnabled(bool enabled) { is_canvas_hdr_enabled_ = enabled; }
  static void SetCanvasTextMetricsPreciseBoundsEnabled(bool enabled) { is_canvas_text_metrics_precise_bounds_enabled_ = enabled; }
  static void SetCanvasToneMappingEnabled(bool enabled) { is_canvas_tone_mapping_enabled_ = enabled; }
  static void SetCanvasUsesArcPaintOpEnabled(bool enabled) { is_canvas_uses_arc_paint_op_enabled_ = enabled; }
  static void SetCapabilityDelegationDisplayCaptureRequestEnabled(bool enabled) { is_capability_delegation_display_capture_request_enabled_ = enabled; }
  static void SetCaptureControllerEnabled(bool enabled) { is_capture_controller_enabled_ = enabled; }
  static void SetCapturedMouseEventsEnabled(bool enabled) { is_captured_mouse_events_enabled_ = enabled; }
  static void SetCapturedSurfaceControlEnabled(bool enabled) { is_captured_surface_control_enabled_ = enabled; }
  static void SetCapturedSurfaceResolutionEnabled(bool enabled) { is_captured_surface_resolution_enabled_ = enabled; }
  static void SetCaptureHandleEnabled(bool enabled) { is_capture_handle_enabled_ = enabled; }
  static void SetCaretWithTextAffinityUpstreamEnabled(bool enabled) { is_caret_with_text_affinity_upstream_enabled_ = enabled; }
  static void SetCCTNewRFMPushBehaviorEnabled(bool enabled) { is_cct_new_rfm_push_behavior_enabled_ = enabled; }
  static void SetCheckableInputTypeLayoutInlineEnabled(bool enabled) { is_checkable_input_type_layout_inline_enabled_ = enabled; }
  static void SetCheckForCanonicalPositionInIdleSpellCheckEnabled(bool enabled) { is_check_for_canonical_position_in_idle_spell_check_enabled_ = enabled; }
  static void SetCheckVisibilityExtraPropertiesEnabled(bool enabled) { is_check_visibility_extra_properties_enabled_ = enabled; }
  static void SetClampWordBoundaryToContentEditableScopeEnabled(bool enabled) { is_clamp_word_boundary_to_content_editable_scope_enabled_ = enabled; }
  static void SetClearCurrentTargetAfterDispatchEnabled(bool enabled) { is_clear_current_target_after_dispatch_enabled_ = enabled; }
  static void SetClearFocusWithinOnSubtreeRemovalEnabled(bool enabled) { is_clear_focus_within_on_subtree_removal_enabled_ = enabled; }
  static void SetClearTargetOnlyIfInShadowTreeEnabled(bool enabled) { is_clear_target_only_if_in_shadow_tree_enabled_ = enabled; }
  static void SetClickFocusDoesntPersistStatusBubbleEnabled(bool enabled) { is_click_focus_doesnt_persist_status_bubble_enabled_ = enabled; }
  static void SetClipboardEventTargetCanBeFocusedElementEnabled(bool enabled) { is_clipboard_event_target_can_be_focused_element_enabled_ = enabled; }
  static void SetClipboardEventTargetUsesContainerNodeEnabled(bool enabled) { is_clipboard_event_target_uses_container_node_enabled_ = enabled; }
  static void SetClipboardItemWithDOMStringSupportEnabled(bool enabled) { is_clipboard_item_with_dom_string_support_enabled_ = enabled; }
  static void SetClipElementVisibleBoundsInLocalRootEnabled(bool enabled) { is_clip_element_visible_bounds_in_local_root_enabled_ = enabled; }
  static void SetClipPathNestedRasterOptimizationEnabled(bool enabled) { is_clip_path_nested_raster_optimization_enabled_ = enabled; }
  static void SetCoalesceSelectionchangeEventEnabled(bool enabled) { is_coalesce_selectionchange_event_enabled_ = enabled; }
  static void SetCoepReflectionEnabled(bool enabled) { is_coep_reflection_enabled_ = enabled; }
  static void SetCollapseZeroWidthSpaceWhenReuseItemEnabled(bool enabled) { is_collapse_zero_width_space_when_reuse_item_enabled_ = enabled; }
  static void SetColorInputAcceptsCSSColorsEnabled(bool enabled) { is_color_input_accepts_css_colors_enabled_ = enabled; }
  static void SetColorSpaceDisplayP3LinearEnabled(bool enabled) { is_color_space_display_p_3_linear_enabled_ = enabled; }
  static void SetColorSpacePredefinedLinearSpacesEnabled(bool enabled) { is_color_space_predefined_linear_spaces_enabled_ = enabled; }
  static void SetColorSpaceRec2100LinearEnabled(bool enabled) { is_color_space_rec_2100_linear_enabled_ = enabled; }
  static void SetCommandEventNotComposedEnabled(bool enabled) { is_command_event_not_composed_enabled_ = enabled; }
  static void SetCommaSeparatedContainerQueriesEnabled(bool enabled) { is_comma_separated_container_queries_enabled_ = enabled; }
  static void SetComposedPathReturnTargetBeingDispatchedEnabled(bool enabled) { is_composed_path_return_target_being_dispatched_enabled_ = enabled; }
  static void SetCompositeBGColorAnimationEnabled(bool enabled) { is_composite_bg_color_animation_enabled_ = enabled; }
  static void SetCompositeBoxShadowAnimationEnabled(bool enabled) { is_composite_box_shadow_animation_enabled_ = enabled; }
  static void SetCompositeClipPathAnimationEnabled(bool enabled) { is_composite_clip_path_animation_enabled_ = enabled; }
  static void SetCompositedAnimationsCancelledAsynchronouslyEnabled(bool enabled) { is_composited_animations_cancelled_asynchronously_enabled_ = enabled; }
  static void SetCompositedSelectionUpdateEnabled(bool enabled) { is_composited_selection_update_enabled_ = enabled; }
  static void SetCompositingDecisionAtAnimationPhaseBoundariesEnabled(bool enabled) { is_compositing_decision_at_animation_phase_boundaries_enabled_ = enabled; }
  static void SetCompositionForegroundMarkersEnabled(bool enabled) { is_composition_foreground_markers_enabled_ = enabled; }
  static void SetCompositorEventTriggerEnabled(bool enabled) { is_compositor_event_trigger_enabled_ = enabled; }
  static void SetCompositorTimelineTriggerEnabled(bool enabled) { is_compositor_timeline_trigger_enabled_ = enabled; }
  static void SetCompressionDictionaryTransportEnabled(bool enabled) { is_compression_dictionary_transport_enabled_ = enabled; }
  static void SetComputedAccessibilityInfoEnabled(bool enabled) { is_computed_accessibility_info_enabled_ = enabled; }
  static void SetComputeInlineContentsSafeRetargetEnabled(bool enabled) { is_compute_inline_contents_safe_retarget_enabled_ = enabled; }
  static void SetComputePressureEnabled(bool enabled) { is_compute_pressure_enabled_ = enabled; }
  static void SetComputePressureOwnContributionEstimateEnabled(bool enabled) { is_compute_pressure_own_contribution_estimate_enabled_ = enabled; }
  static void SetConnectionAllowlistEnabled(bool enabled) { is_connection_allowlist_enabled_ = enabled; }
  static void SetConsiderSubOrSuperScriptAncestorAlignForCaretSelectionEnabled(bool enabled) { is_consider_sub_or_super_script_ancestor_align_for_caret_selection_enabled_ = enabled; }
  static void SetContactsManagerEnabled(bool enabled) { is_contacts_manager_enabled_ = enabled; }
  static void SetContactsManagerExtraPropertiesEnabled(bool enabled) { is_contacts_manager_extra_properties_enabled_ = enabled; }
  static void SetContainerNameOnlyEnabled(bool enabled) { is_container_name_only_enabled_ = enabled; }
  static void SetContainerTimingEnabled(bool enabled) { is_container_timing_enabled_ = enabled; }
  static void SetContentIndexEnabled(bool enabled) { is_content_index_enabled_ = enabled; }
  static void SetContextMenuEnabled(bool enabled) { is_context_menu_enabled_ = enabled; }
  static void SetControlledFrameEnabled(bool enabled) { is_controlled_frame_enabled_ = enabled; }
  static void SetControlledFrameWebRequestSecurityInfoEnabled(bool enabled) { is_controlled_frame_web_request_security_info_enabled_ = enabled; }
  static void SetCookieStoreAPIMaxAgeEnabled(bool enabled) { is_cookie_store_api_max_age_enabled_ = enabled; }
  static void SetCookieStoreAPIWhitespaceStrippingEnabled(bool enabled) { is_cookie_store_api_whitespace_stripping_enabled_ = enabled; }
  static void SetCoopRestrictPropertiesEnabled(bool enabled) { is_coop_restrict_properties_enabled_ = enabled; }
  static void SetCorrectTemplateFormParsingEnabled(bool enabled) { is_correct_template_form_parsing_enabled_ = enabled; }
  static void SetCorsRFC1918Enabled(bool enabled) { is_cors_rfc_1918_enabled_ = enabled; }
  static void SetCpuPerformanceEnabled(bool enabled) { is_cpu_performance_enabled_ = enabled; }
  static void SetCrashReportingStorageAPIEnabled(bool enabled) { is_crash_reporting_storage_api_enabled_ = enabled; }
  static void SetCreateInlineContentsExcludeOutOfFlowEnabled(bool enabled) { is_create_inline_contents_exclude_out_of_flow_enabled_ = enabled; }
  static void SetCSPHashesV1Enabled(bool enabled) { is_csp_hashes_v_1_enabled_ = enabled; }
  static void SetCSPReportHashEnabled(bool enabled) { is_csp_report_hash_enabled_ = enabled; }
  static void SetCSSAccentColorKeywordEnabled(bool enabled) { is_css_accent_color_keyword_enabled_ = enabled; }
  static void SetCSSActiveCaptionMapsToCanvasEnabled(bool enabled) { is_css_active_caption_maps_to_canvas_enabled_ = enabled; }
  static void SetCSSAlphaColorFunctionEnabled(bool enabled) { is_css_alpha_color_function_enabled_ = enabled; }
  static void SetCSSAltCounterEnabled(bool enabled) { is_css_alt_counter_enabled_ = enabled; }
  static void SetCSSAnchorWithTransformsEnabled(bool enabled) { is_css_anchor_with_transforms_enabled_ = enabled; }
  static void SetCSSAnimationIterationCompositeEnabled(bool enabled) { is_css_animation_iteration_composite_enabled_ = enabled; }
  static void SetCSSArgumentGrammarEnabled(bool enabled) { is_css_argument_grammar_enabled_ = enabled; }
  static void SetCSSAtRuleCounterStyleImageSymbolsEnabled(bool enabled) { is_css_at_rule_counter_style_image_symbols_enabled_ = enabled; }
  static void SetCSSAtRuleCounterStyleSpeakAsDescriptorEnabled(bool enabled) { is_css_at_rule_counter_style_speak_as_descriptor_enabled_ = enabled; }
  static void SetCSSBackgroundClipBorderAreaEnabled(bool enabled) { is_css_background_clip_border_area_enabled_ = enabled; }
  static void SetCSSBorderShapeEnabled(bool enabled) { is_css_border_shape_enabled_ = enabled; }
  static void SetCSSCalcSimplificationAndSerializationEnabled(bool enabled) { is_css_calc_simplification_and_serialization_enabled_ = enabled; }
  static void SetCSSCaretAnimationEnabled(bool enabled) { is_css_caret_animation_enabled_ = enabled; }
  static void SetCSSCaretShapeEnabled(bool enabled) { is_css_caret_shape_enabled_ = enabled; }
  static void SetCSSCaseSensitiveSelectorEnabled(bool enabled) { is_css_case_sensitive_selector_enabled_ = enabled; }
  static void SetCSSChUnitSpecCompliantFallbackEnabled(bool enabled) { is_css_ch_unit_spec_compliant_fallback_enabled_ = enabled; }
  static void SetCSSColorTypedOMEnabled(bool enabled) { is_css_color_typed_om_enabled_ = enabled; }
  static void SetCSSContainerProgressNotationEnabled(bool enabled) { is_css_container_progress_notation_enabled_ = enabled; }
  static void SetCSSContainerStyleQueriesRangeEnabled(bool enabled) { is_css_container_style_queries_range_enabled_ = enabled; }
  static void SetCSSContrastColorEnabled(bool enabled) { is_css_contrast_color_enabled_ = enabled; }
  static void SetCSSCornersShorthandEnabled(bool enabled) { is_css_corners_shorthand_enabled_ = enabled; }
  static void SetCSSCounterResetReversedEnabled(bool enabled) { is_css_counter_reset_reversed_enabled_ = enabled; }
  static void SetCSSCrossFadeEnabled(bool enabled) { is_css_cross_fade_enabled_ = enabled; }
  static void SetCSSCustomMediaEnabled(bool enabled) { is_css_custom_media_enabled_ = enabled; }
  static void SetCSSDynamicRangeLimitEnabled(bool enabled) { is_css_dynamic_range_limit_enabled_ = enabled; }
  static void SetCSSEnumeratedCustomPropertiesEnabled(bool enabled) { is_css_enumerated_custom_properties_enabled_ = enabled; }
  static void SetCSSFontFamilySerializationEnabled(bool enabled) { is_css_font_family_serialization_enabled_ = enabled; }
  static void SetCSSFontSizeAdjustEnabled(bool enabled) { is_css_font_size_adjust_enabled_ = enabled; }
  static void SetCSSFunctionsEnabled(bool enabled) { is_css_functions_enabled_ = enabled; }
  static void SetCSSGapDecorationEnabled(bool enabled) { is_css_gap_decoration_enabled_ = enabled; }
  static void SetCSSGridGapSuppressionEnabled(bool enabled) { is_css_grid_gap_suppression_enabled_ = enabled; }
  static void SetCSSGridLanesLayoutEnabled(bool enabled) { is_css_grid_lanes_layout_enabled_ = enabled; }
  static void SetCSSHangingPunctuationEnabled(bool enabled) { is_css_hanging_punctuation_enabled_ = enabled; }
  static void SetCSSHexAlphaColorEnabled(bool enabled) { is_css_hex_alpha_color_enabled_ = enabled; }
  static void SetCSSIdentFunctionEnabled(bool enabled) { is_css_ident_function_enabled_ = enabled; }
  static void SetCSSImageAnimationEnabled(bool enabled) { is_css_image_animation_enabled_ = enabled; }
  static void SetCSSInheritFunctionEnabled(bool enabled) { is_css_inherit_function_enabled_ = enabled; }
  static void SetCSSKeyframesRuleLengthEnabled(bool enabled) { is_css_keyframes_rule_length_enabled_ = enabled; }
  static void SetCSSLangExtendedRangesEnabled(bool enabled) { is_css_lang_extended_ranges_enabled_ = enabled; }
  static void SetCSSLayoutAPIEnabled(bool enabled) { is_css_layout_api_enabled_ = enabled; }
  static void SetCSSLetterAndWordSpacingPercentageEnabled(bool enabled) { is_css_letter_and_word_spacing_percentage_enabled_ = enabled; }
  static void SetCSSLightDarkImageEnabled(bool enabled) { is_css_light_dark_image_enabled_ = enabled; }
  static void SetCSSLineClampEnabled(bool enabled) { is_css_line_clamp_enabled_ = enabled; }
  static void SetCSSLineClampLineBreakingEllipsisEnabled(bool enabled) { is_css_line_clamp_line_breaking_ellipsis_enabled_ = enabled; }
  static void SetCSSLineClampLinesAndHeightEnabled(bool enabled) { is_css_line_clamp_lines_and_height_enabled_ = enabled; }
  static void SetCSSListCounterAccountingEnabled(bool enabled) { is_css_list_counter_accounting_enabled_ = enabled; }
  static void SetCSSLogicalCombinationPseudoEnabled(bool enabled) { is_css_logical_combination_pseudo_enabled_ = enabled; }
  static void SetCSSMarkerNestedPseudoElementEnabled(bool enabled) { is_css_marker_nested_pseudo_element_enabled_ = enabled; }
  static void SetCSSMediaProgressNotationEnabled(bool enabled) { is_css_media_progress_notation_enabled_ = enabled; }
  static void SetCSSMixinsEnabled(bool enabled) { is_css_mixins_enabled_ = enabled; }
  static void SetCSSNestedPseudoElementsEnabled(bool enabled) { is_css_nested_pseudo_elements_enabled_ = enabled; }
  static void SetCSSOMGetComputedStylePseudoElementRequiresColonEnabled(bool enabled) { is_cssom_get_computed_style_pseudo_element_requires_colon_enabled_ = enabled; }
  static void SetCSSOverscrollBehaviorChainEnabled(bool enabled) { is_css_overscroll_behavior_chain_enabled_ = enabled; }
  static void SetCSSPaintAPIArgumentsEnabled(bool enabled) { is_css_paint_api_arguments_enabled_ = enabled; }
  static void SetCSSParserIgnoreCharsetForURLsEnabled(bool enabled) { is_css_parser_ignore_charset_for_urls_enabled_ = enabled; }
  static void SetCSSPolygonRoundingEnabled(bool enabled) { is_css_polygon_rounding_enabled_ = enabled; }
  static void SetCSSPositionStickyStaticScrollPositionEnabled(bool enabled) { is_css_position_sticky_static_scroll_position_enabled_ = enabled; }
  static void SetCSSProgressNotationEnabled(bool enabled) { is_css_progress_notation_enabled_ = enabled; }
  static void SetCSSPseudoColumnEnabled(bool enabled) { is_css_pseudo_column_enabled_ = enabled; }
  static void SetCSSPseudoElementBackdropEnabled(bool enabled) { is_css_pseudo_element_backdrop_enabled_ = enabled; }
  static void SetCSSPseudoElementInterfaceEnabled(bool enabled) { is_css_pseudo_element_interface_enabled_ = enabled; }
  static void SetCSSPseudoElementViewTransitionsEnabled(bool enabled) { is_css_pseudo_element_view_transitions_enabled_ = enabled; }
  static void SetCSSPseudoHasSlottedEnabled(bool enabled) { is_css_pseudo_has_slotted_enabled_ = enabled; }
  static void SetCSSPseudoPlayingPausedEnabled(bool enabled) { is_css_pseudo_playing_paused_enabled_ = enabled; }
  static void SetCSSPseudoScrollButtonsEnabled(bool enabled) { is_css_pseudo_scroll_buttons_enabled_ = enabled; }
  static void SetCSSPseudoScrollMarkersEnabled(bool enabled) { is_css_pseudo_scroll_markers_enabled_ = enabled; }
  static void SetCSSRandomFunctionEnabled(bool enabled) { is_css_random_function_enabled_ = enabled; }
  static void SetCSSRandomFunctionTypedOMEnabled(bool enabled) { is_css_random_function_typed_om_enabled_ = enabled; }
  static void SetCSSResizeAutoEnabled(bool enabled) { is_css_resize_auto_enabled_ = enabled; }
  static void SetCSSResourceIntegrityEnforcementEnabled(bool enabled) { is_css_resource_integrity_enforcement_enabled_ = enabled; }
  static void SetCSSRevertRuleEnabled(bool enabled) { is_css_revert_rule_enabled_ = enabled; }
  static void SetCSSRubyOverhangEnabled(bool enabled) { is_css_ruby_overhang_enabled_ = enabled; }
  static void SetCSSSafePrintableInsetEnabled(bool enabled) { is_css_safe_printable_inset_enabled_ = enabled; }
  static void SetCSSScopeifiedParentPseudoClassEnabled(bool enabled) { is_css_scopeified_parent_pseudo_class_enabled_ = enabled; }
  static void SetCSSScopeImportEnabled(bool enabled) { is_css_scope_import_enabled_ = enabled; }
  static void SetCSSScrolledContainerQueriesEnabled(bool enabled) { is_css_scrolled_container_queries_enabled_ = enabled; }
  static void SetCSSScrollInitialTargetEnabled(bool enabled) { is_css_scroll_initial_target_enabled_ = enabled; }
  static void SetCSSScrollMarkerGroupModesEnabled(bool enabled) { is_css_scroll_marker_group_modes_enabled_ = enabled; }
  static void SetCSSScrollMarkerTargetBeforeAfterEnabled(bool enabled) { is_css_scroll_marker_target_before_after_enabled_ = enabled; }
  static void SetCSSScrollSnapChangeEventEnabled(bool enabled) { is_css_scroll_snap_change_event_enabled_ = enabled; }
  static void SetCSSScrollSnapChangingEventEnabled(bool enabled) { is_css_scroll_snap_changing_event_enabled_ = enabled; }
  static void SetCSSScrollSnapEventConstructorExposedEnabled(bool enabled) { is_css_scroll_snap_event_constructor_exposed_enabled_ = enabled; }
  static void SetCSSScrollSnapEventsEnabled(bool enabled) { is_css_scroll_snap_events_enabled_ = enabled; }
  static void SetCSSScrollTargetGroupEnabled(bool enabled) { is_css_scroll_target_group_enabled_ = enabled; }
  static void SetCSSScrollTargetGroupAriaCurrentEnabled(bool enabled) { is_css_scroll_target_group_aria_current_enabled_ = enabled; }
  static void SetCSSShapeEllipseCirclePositionSerializationEnabled(bool enabled) { is_css_shape_ellipse_circle_position_serialization_enabled_ = enabled; }
  static void SetCSSShapeOutsidePathAndShapeSupportEnabled(bool enabled) { is_css_shape_outside_path_and_shape_support_enabled_ = enabled; }
  static void SetCSSShapeOutsideRectAndXywhSupportEnabled(bool enabled) { is_css_shape_outside_rect_and_xywh_support_enabled_ = enabled; }
  static void SetCSSStyleSheetInitBaseURLEnabled(bool enabled) { is_css_style_sheet_init_base_url_enabled_ = enabled; }
  static void SetCSSSupportsAtRuleFunctionEnabled(bool enabled) { is_css_supports_at_rule_function_enabled_ = enabled; }
  static void SetCSSSupportsForImportRulesEnabled(bool enabled) { is_css_supports_for_import_rules_enabled_ = enabled; }
  static void SetCSSSupportsNamedFeatureFunctionEnabled(bool enabled) { is_css_supports_named_feature_function_enabled_ = enabled; }
  static void SetCSSSystemAccentColorEnabled(bool enabled) { is_css_system_accent_color_enabled_ = enabled; }
  static void SetCSSTextAlignMatchParentEnabled(bool enabled) { is_css_text_align_match_parent_enabled_ = enabled; }
  static void SetCSSTextDecorationSkipInkAllEnabled(bool enabled) { is_css_text_decoration_skip_ink_all_enabled_ = enabled; }
  static void SetCSSTextDecorationSkipSpacesEnabled(bool enabled) { is_css_text_decoration_skip_spaces_enabled_ = enabled; }
  static void SetCssTextFitEnabled(bool enabled) { is_css_text_fit_enabled_ = enabled; }
  static void SetCssTextFitReshapingEnabled(bool enabled) { is_css_text_fit_reshaping_enabled_ = enabled; }
  static void SetCssTextIndentEnabled(bool enabled) { is_css_text_indent_enabled_ = enabled; }
  static void SetCssTextIndentAsPrimitiveEnabled(bool enabled) { is_css_text_indent_as_primitive_enabled_ = enabled; }
  static void SetCSSTextSpacingEnabled(bool enabled) { is_css_text_spacing_enabled_ = enabled; }
  static void SetCSSTextTransformFullSizeKanaEnabled(bool enabled) { is_css_text_transform_full_size_kana_enabled_ = enabled; }
  static void SetCSSTextTransformFullWidthEnabled(bool enabled) { is_css_text_transform_full_width_enabled_ = enabled; }
  static void SetCSSTextTransformMultiKeywordEnabled(bool enabled) { is_css_text_transform_multi_keyword_enabled_ = enabled; }
  static void SetCSSTimelineScopeAllEnabled(bool enabled) { is_css_timeline_scope_all_enabled_ = enabled; }
  static void SetCSSTimelineScopeGlobalEnabled(bool enabled) { is_css_timeline_scope_global_enabled_ = enabled; }
  static void SetCSSTypedArithmeticEnabled(bool enabled) { is_css_typed_arithmetic_enabled_ = enabled; }
  static void SetCSSURLRequestModifiersEnabled(bool enabled) { is_css_url_request_modifiers_enabled_ = enabled; }
  static void SetCSSUserSelectContainEnabled(bool enabled) { is_css_user_select_contain_enabled_ = enabled; }
  static void SetCSSUserValidAndUserInvalidForRadioEnabled(bool enabled) { is_css_user_valid_and_user_invalid_for_radio_enabled_ = enabled; }
  static void SetCSSVideoDynamicRangeMediaQueriesEnabled(bool enabled) { is_css_video_dynamic_range_media_queries_enabled_ = enabled; }
  static void SetCSSViewTransitionAutoNameEnabled(bool enabled) { is_css_view_transition_auto_name_enabled_ = enabled; }
  static void SetCustomElementsDisableFormattingFixupsEnabled(bool enabled) { is_custom_elements_disable_formatting_fixups_enabled_ = enabled; }
  static void SetCustomizableComboboxEnabled(bool enabled) { is_customizable_combobox_enabled_ = enabled; }
  static void SetCustomizableSelectMultiplePopupEnabled(bool enabled) { is_customizable_select_multiple_popup_enabled_ = enabled; }
  static void SetCustomScrollbarApplyMinimumThumbLengthEnabled(bool enabled) { is_custom_scrollbar_apply_minimum_thumb_length_enabled_ = enabled; }
  static void SetDatabaseEnabled(bool enabled) { is_database_enabled_ = enabled; }
  static void SetDateTimeLocalArabicCommaWorkaroundEnabled(bool enabled) { is_date_time_local_arabic_comma_workaround_enabled_ = enabled; }
  static void SetDeclarativeCSSModulesEnabled(bool enabled) { is_declarative_css_modules_enabled_ = enabled; }
  static void SetDeclarativeCSSModulesStyleTagEnabled(bool enabled) { is_declarative_css_modules_style_tag_enabled_ = enabled; }
  static void SetDecoupleComputedBorderWidthFromStyleEnabled(bool enabled) { is_decouple_computed_border_width_from_style_enabled_ = enabled; }
  static void SetDecoupleResolvedColumnRuleWidthFromStyleEnabled(bool enabled) { is_decouple_resolved_column_rule_width_from_style_enabled_ = enabled; }
  static void SetDelegatesFocusTextControlInputFixEnabled(bool enabled) { is_delegates_focus_text_control_input_fix_enabled_ = enabled; }
  static void SetDeleteTextInContentEditableBeforeRemovingChildrenEnabled(bool enabled) { is_delete_text_in_content_editable_before_removing_children_enabled_ = enabled; }
  static void SetDeprecateUnloadOptOutEnabled(bool enabled) { is_deprecate_unload_opt_out_enabled_ = enabled; }
  static void SetDesktopCaptureDisableLocalEchoControlEnabled(bool enabled) { is_desktop_capture_disable_local_echo_control_enabled_ = enabled; }
  static void SetDesktopPWAsAdditionalWindowingControlsEnabled(bool enabled) { is_desktop_pw_as_additional_windowing_controls_enabled_ = enabled; }
  static void SetDesktopPWAsAdditionalWindowingControlsOnMoveEnabled(bool enabled) { is_desktop_pw_as_additional_windowing_controls_on_move_enabled_ = enabled; }
  static void SetDeviceAttributesEnabled(bool enabled) { is_device_attributes_enabled_ = enabled; }
  static void SetDeviceOrientationRequestPermissionEnabled(bool enabled) { is_device_orientation_request_permission_enabled_ = enabled; }
  static void SetDevicePostureEnabled(bool enabled) { is_device_posture_enabled_ = enabled; }
  static void SetDialogCloseWhenOpenRemovedEnabled(bool enabled) { is_dialog_close_when_open_removed_enabled_ = enabled; }
  static void SetDialogNewFocusBehaviorEnabled(bool enabled) { is_dialog_new_focus_behavior_enabled_ = enabled; }
  static void SetDigitalGoodsEnabled(bool enabled) { is_digital_goods_enabled_ = enabled; }
  static void SetDigitalGoodsV2_1Enabled(bool enabled) { is_digital_goods_v_2_1_enabled_ = enabled; }
  static void SetDirectSocketsEnabled(bool enabled) { is_direct_sockets_enabled_ = enabled; }
  static void SetDirectSocketsInServiceWorkersEnabled(bool enabled) { is_direct_sockets_in_service_workers_enabled_ = enabled; }
  static void SetDirectSocketsInSharedWorkersEnabled(bool enabled) { is_direct_sockets_in_shared_workers_enabled_ = enabled; }
  static void SetDisableAnchorCenterOnAlignJustifyItemsEnabled(bool enabled) { is_disable_anchor_center_on_align_justify_items_enabled_ = enabled; }
  static void SetDisableDifferentOriginSubframeDialogSuppressionEnabled(bool enabled) { is_disable_different_origin_subframe_dialog_suppression_enabled_ = enabled; }
  static void SetDisableEllipsisWhenScrolledEnabled(bool enabled) { is_disable_ellipsis_when_scrolled_enabled_ = enabled; }
  static void SetDisableReduceAcceptLanguageEnabled(bool enabled) { is_disable_reduce_accept_language_enabled_ = enabled; }
  static void SetDisableRemoveFormatForPlainTextOnlyEditableDivEnabled(bool enabled) { is_disable_remove_format_for_plain_text_only_editable_div_enabled_ = enabled; }
  static void SetDisallowDisconnectedAreaNavigationEnabled(bool enabled) { is_disallow_disconnected_area_navigation_enabled_ = enabled; }
  static void SetDisallowPickerForReadonlyInputsEnabled(bool enabled) { is_disallow_picker_for_readonly_inputs_enabled_ = enabled; }
  static void SetDisconnectWebSocketOnBFCacheEnabled(bool enabled) { is_disconnect_websocket_on_bf_cache_enabled_ = enabled; }
  static void SetDispatchHiddenVisibilityTransitionsEnabled(bool enabled) { is_dispatch_hidden_visibility_transitions_enabled_ = enabled; }
  static void SetDispatchSelectionchangeEventPerElementEnabled(bool enabled) { is_dispatch_selectionchange_event_per_element_enabled_ = enabled; }
  static void SetDisplayContentsFocusableEnabled(bool enabled) { is_display_contents_focusable_enabled_ = enabled; }
  static void SetDisplayCutoutAPIEnabled(bool enabled) { is_display_cutout_api_enabled_ = enabled; }
  static void SetDocumentActiveViewTransitionEnabled(bool enabled) { is_document_active_view_transition_enabled_ = enabled; }
  static void SetDocumentCookieEnabled(bool enabled) { is_document_cookie_enabled_ = enabled; }
  static void SetDocumentDomainEnabled(bool enabled) { is_document_domain_enabled_ = enabled; }
  static void SetDocumentIsolationPolicyEnabled(bool enabled) { is_document_isolation_policy_enabled_ = enabled; }
  static void SetDocumentOpenIframeUnloadEventsEnabled(bool enabled) { is_document_open_iframe_unload_events_enabled_ = enabled; }
  static void SetDocumentOpenOriginAliasRemovalEnabled(bool enabled) { is_document_open_origin_alias_removal_enabled_ = enabled; }
  static void SetDocumentOpenSandboxInheritanceRemovalEnabled(bool enabled) { is_document_open_sandbox_inheritance_removal_enabled_ = enabled; }
  static void SetDocumentPatchingEnabled(bool enabled) { is_document_patching_enabled_ = enabled; }
  static void SetDocumentPictureInPictureAPIEnabled(bool enabled) { is_document_picture_in_picture_api_enabled_ = enabled; }
  static void SetDocumentPictureInPicturePreferInitialPlacementEnabled(bool enabled) { is_document_picture_in_picture_prefer_initial_placement_enabled_ = enabled; }
  static void SetDocumentPictureInPictureUserActivationEnabled(bool enabled) { is_document_picture_in_picture_user_activation_enabled_ = enabled; }
  static void SetDocumentPolicyDocumentDomainEnabled(bool enabled) { is_document_policy_document_domain_enabled_ = enabled; }
  static void SetDocumentPolicyExpectNoLinkedResourcesEnabled(bool enabled) { is_document_policy_expect_no_linked_resources_enabled_ = enabled; }
  static void SetDocumentPolicyIncludeJSCallStacksInCrashReportsEnabled(bool enabled) { is_document_policy_include_js_call_stacks_in_crash_reports_enabled_ = enabled; }
  static void SetDocumentPolicyInDedicatedWorkerEnabled(bool enabled) { is_document_policy_in_dedicated_worker_enabled_ = enabled; }
  static void SetDocumentPolicyNegotiationEnabled(bool enabled) { is_document_policy_negotiation_enabled_ = enabled; }
  static void SetDocumentPolicyNetworkEfficiencyGuardrailsEnabled(bool enabled) { is_document_policy_network_efficiency_guardrails_enabled_ = enabled; }
  static void SetDocumentPolicySyncXHREnabled(bool enabled) { is_document_policy_sync_xhr_enabled_ = enabled; }
  static void SetDocumentWriteEnabled(bool enabled) { is_document_write_enabled_ = enabled; }
  static void SetDOMActivateBubblesInheritanceEnabled(bool enabled) { is_dom_activate_bubbles_inheritance_enabled_ = enabled; }
  static void SetDontLeakShadowTreesInDragEventsEnabled(bool enabled) { is_dont_leak_shadow_trees_in_drag_events_enabled_ = enabled; }
  static void SetEditContextAssignmentAsPerSpecEnabled(bool enabled) { is_edit_context_assignment_as_per_spec_enabled_ = enabled; }
  static void SetEditContextHandleTextOrSelectionUpdateDuringCompositionEnabled(bool enabled) { is_edit_context_handle_text_or_selection_update_during_composition_enabled_ = enabled; }
  static void SetEditEmojiTagSequenceEnabled(bool enabled) { is_edit_emoji_tag_sequence_enabled_ = enabled; }
  static void SetEditingLineMovementWithRubyFixEnabled(bool enabled) { is_editing_line_movement_with_ruby_fix_enabled_ = enabled; }
  static void SetElementCaptureEnabled(bool enabled) { is_element_capture_enabled_ = enabled; }
  static void SetElementInnerTextHandleFirstLineStyleEnabled(bool enabled) { is_element_inner_text_handle_first_line_style_enabled_ = enabled; }
  static void SetElementInternalsBehaviorsEnabled(bool enabled) { is_element_internals_behaviors_enabled_ = enabled; }
  static void SetElementSpecificReadOnlyConstraintValidationEnabled(bool enabled) { is_element_specific_read_only_constraint_validation_enabled_ = enabled; }
  static void SetEmailVerificationProtocolEnabled(bool enabled) { is_email_verification_protocol_enabled_ = enabled; }
  static void SetEmojiMonochromeRenderingEnabled(bool enabled) { is_emoji_monochrome_rendering_enabled_ = enabled; }
  static void SetEndpointInclusiveCommitStylesEnabled(bool enabled) { is_endpoint_inclusive_commit_styles_enabled_ = enabled; }
  static void SetEnforceAnonymityExposureEnabled(bool enabled) { is_enforce_anonymity_exposure_enabled_ = enabled; }
  static void SetEnterInOpenShadowRootsEnabled(bool enabled) { is_enter_in_open_shadow_roots_enabled_ = enabled; }
  static void SetEntropyIgnoredForFirstVideoFrameLCPEnabled(bool enabled) { is_entropy_ignored_for_first_video_frame_lcp_enabled_ = enabled; }
  static void SetEventPseudoTargetPropertyEnabled(bool enabled) { is_event_pseudo_target_property_enabled_ = enabled; }
  static void SetEventTimingInteractionCountEnabled(bool enabled) { is_event_timing_interaction_count_enabled_ = enabled; }
  static void SetEventTimingTargetSelectorEnabled(bool enabled) { is_event_timing_target_selector_enabled_ = enabled; }
  static void SetEventTriggerEnabled(bool enabled) { is_event_trigger_enabled_ = enabled; }
  static void SetExperimentalContentSecurityPolicyFeaturesEnabled(bool enabled) { is_experimental_content_security_policy_features_enabled_ = enabled; }
  static void SetExperimentalJSProfilerMarkersEnabled(bool enabled) { is_experimental_js_profiler_markers_enabled_ = enabled; }
  static void SetExperimentalMachineLearningNeuralNetworkEnabled(bool enabled) { is_experimental_machine_learning_neural_network_enabled_ = enabled; }
  static void SetExperimentalPoliciesEnabled(bool enabled) { is_experimental_policies_enabled_ = enabled; }
  static void SetExposeCSSFontFeatureValuesRuleEnabled(bool enabled) { is_expose_css_font_feature_values_rule_enabled_ = enabled; }
  static void SetExposeRenderTimeNonTaoDelayedImageEnabled(bool enabled) { is_expose_render_time_non_tao_delayed_image_enabled_ = enabled; }
  static void SetExtendedShapeCacheEnabled(bool enabled) { is_extended_shape_cache_enabled_ = enabled; }
  static void SetExtendedTextMetricsEnabled(bool enabled) { is_extended_text_metrics_enabled_ = enabled; }
  static void SetExternalPopupMenuClickEventEnabled(bool enabled) { is_external_popup_menu_click_event_enabled_ = enabled; }
  static void SetEyeDropperAPIEnabled(bool enabled) { is_eye_dropper_api_enabled_ = enabled; }
  static void SetFaceDetectorEnabled(bool enabled) { is_face_detector_enabled_ = enabled; }
  static void SetFastPositionIteratorEnabled(bool enabled) { is_fast_position_iterator_enabled_ = enabled; }
  static void SetFedCmEnabled(bool enabled) { is_fed_cm_enabled_ = enabled; }
  static void SetFedCmAutofillEnabled(bool enabled) { is_fed_cm_autofill_enabled_ = enabled; }
  static void SetFedCmDelegationEnabled(bool enabled) { is_fed_cm_delegation_enabled_ = enabled; }
  static void SetFedCmErrorAttributeEnabled(bool enabled) { is_fed_cm_error_attribute_enabled_ = enabled; }
  static void SetFedCmIdPRegistrationEnabled(bool enabled) { is_fed_cm_id_p_registration_enabled_ = enabled; }
  static void SetFedCmLightweightModeEnabled(bool enabled) { is_fed_cm_lightweight_mode_enabled_ = enabled; }
  static void SetFedCmMultipleIdentityProvidersEnabled(bool enabled) { is_fed_cm_multiple_identity_providers_enabled_ = enabled; }
  static void SetFedCmNavigationInterceptionEnabled(bool enabled) { is_fed_cm_navigation_interception_enabled_ = enabled; }
  static void SetFedCmNonStringTokenEnabled(bool enabled) { is_fed_cm_non_string_token_enabled_ = enabled; }
  static void SetFencedFramesEnabled(bool enabled) { is_fenced_frames_enabled_ = enabled; }
  static void SetFencedFramesAPIChangesEnabled(bool enabled) { is_fenced_frames_api_changes_enabled_ = enabled; }
  static void SetFencedFramesDefaultModeEnabled(bool enabled) { is_fenced_frames_default_mode_enabled_ = enabled; }
  static void SetFencedFramesLocalUnpartitionedDataAccessEnabled(bool enabled) { is_fenced_frames_local_unpartitioned_data_access_enabled_ = enabled; }
  static void SetFetchBodyBytesEnabled(bool enabled) { is_fetch_body_bytes_enabled_ = enabled; }
  static void SetFetchLaterAPIEnabled(bool enabled) { is_fetch_later_api_enabled_ = enabled; }
  static void SetFetchRetryEnabled(bool enabled) { is_fetch_retry_enabled_ = enabled; }
  static void SetFetchUploadStreamingEnabled(bool enabled) { is_fetch_upload_streaming_enabled_ = enabled; }
  static void SetFileHandlingEnabled(bool enabled) { is_file_handling_enabled_ = enabled; }
  static void SetFileHandlingIconsEnabled(bool enabled) { is_file_handling_icons_enabled_ = enabled; }
  static void SetFileSystemEnabled(bool enabled) { is_file_system_enabled_ = enabled; }
  static void SetFileSystemAccessEnabled(bool enabled) { is_file_system_access_enabled_ = enabled; }
  static void SetFileSystemAccessAPIExperimentalEnabled(bool enabled) { is_file_system_access_api_experimental_enabled_ = enabled; }
  static void SetFileSystemAccessGetCloudIdentifiersEnabled(bool enabled) { is_file_system_access_get_cloud_identifiers_enabled_ = enabled; }
  static void SetFileSystemAccessLocalEnabled(bool enabled) { is_file_system_access_local_enabled_ = enabled; }
  static void SetFileSystemAccessLockingSchemeEnabled(bool enabled) { is_file_system_access_locking_scheme_enabled_ = enabled; }
  static void SetFileSystemAccessOriginPrivateEnabled(bool enabled) { is_file_system_access_origin_private_enabled_ = enabled; }
  static void SetFileSystemAccessRevokeReadOnRemoveEnabled(bool enabled) { is_file_system_access_revoke_read_on_remove_enabled_ = enabled; }
  static void SetFileSystemAccessWriteModeEnabled(bool enabled) { is_file_system_access_write_mode_enabled_ = enabled; }
  static void SetFileSystemObserverEnabled(bool enabled) { is_file_system_observer_enabled_ = enabled; }
  static void SetFileSystemObserverUnobserveEnabled(bool enabled) { is_file_system_observer_unobserve_enabled_ = enabled; }
  static void SetFilterableSelectEnabled(bool enabled) { is_filterable_select_enabled_ = enabled; }
  static void SetFilterContainerLevelStylesEnabled(bool enabled) { is_filter_container_level_styles_enabled_ = enabled; }
  static void SetFilteringPrimitivesEnabled(bool enabled) { is_filtering_primitives_enabled_ = enabled; }
  static void SetFindFirstMisspellingEndWhenNonEditableEnabled(bool enabled) { is_find_first_misspelling_end_when_non_editable_enabled_ = enabled; }
  static void SetFirstLineOnListItemEnabled(bool enabled) { is_first_line_on_list_item_enabled_ = enabled; }
  static void SetFirstLineTextMetricsEnabled(bool enabled) { is_first_line_text_metrics_enabled_ = enabled; }
  static void SetFixHTMLFormControlElementIsReadOnlyEnabled(bool enabled) { is_fix_html_form_control_element_is_read_only_enabled_ = enabled; }
  static void SetFixJustifyQueryCommandValueEnabled(bool enabled) { is_fix_justify_query_command_value_enabled_ = enabled; }
  static void SetFixLinebreakForPreTagEnabled(bool enabled) { is_fix_linebreak_for_pre_tag_enabled_ = enabled; }
  static void SetFixMapElementEmptyNameBugEnabled(bool enabled) { is_fix_map_element_empty_name_bug_enabled_ = enabled; }
  static void SetFixMarkerSuppressionForAppearanceAutoEnabled(bool enabled) { is_fix_marker_suppression_for_appearance_auto_enabled_ = enabled; }
  static void SetFixNextPositionCalculationInInsertListEnabled(bool enabled) { is_fix_next_position_calculation_in_insert_list_enabled_ = enabled; }
  static void SetFixStrikethroughToggleInEmptyContentEditableEnabled(bool enabled) { is_fix_strikethrough_toggle_in_empty_content_editable_enabled_ = enabled; }
  static void SetFixVisualRectRemoteViewportTransformEnabled(bool enabled) { is_fix_visual_rect_remote_viewport_transform_enabled_ = enabled; }
  static void SetFledgeEnabled(bool enabled) { is_fledge_enabled_ = enabled; }
  static void SetFledgeAuctionDealSupportEnabled(bool enabled) { is_fledge_auction_deal_support_enabled_ = enabled; }
  static void SetFledgeBiddingAndAuctionServerAPIEnabled(bool enabled) { is_fledge_bidding_and_auction_server_api_enabled_ = enabled; }
  static void SetFledgeBiddingAndAuctionServerAPIMultiSellerEnabled(bool enabled) { is_fledge_bidding_and_auction_server_api_multi_seller_enabled_ = enabled; }
  static void SetFledgeClickinessEnabled(bool enabled) { is_fledge_clickiness_enabled_ = enabled; }
  static void SetFledgeCustomMaxAuctionAdComponentsEnabled(bool enabled) { is_fledge_custom_max_auction_ad_components_enabled_ = enabled; }
  static void SetFledgeDeprecatedRenderURLReplacementsEnabled(bool enabled) { is_fledge_deprecated_render_url_replacements_enabled_ = enabled; }
  static void SetFledgeDirectFromSellerSignalsHeaderAdSlotEnabled(bool enabled) { is_fledge_direct_from_seller_signals_header_ad_slot_enabled_ = enabled; }
  static void SetFledgeDirectFromSellerSignalsWebBundlesEnabled(bool enabled) { is_fledge_direct_from_seller_signals_web_bundles_enabled_ = enabled; }
  static void SetFledgeMultiBidEnabled(bool enabled) { is_fledge_multi_bid_enabled_ = enabled; }
  static void SetFledgePrivateModelTrainingEnabled(bool enabled) { is_fledge_private_model_training_enabled_ = enabled; }
  static void SetFledgeRealTimeReportingEnabled(bool enabled) { is_fledge_real_time_reporting_enabled_ = enabled; }
  static void SetFledgeSellerNonceEnabled(bool enabled) { is_fledge_seller_nonce_enabled_ = enabled; }
  static void SetFledgeSellerScriptExecutionModeEnabled(bool enabled) { is_fledge_seller_script_execution_mode_enabled_ = enabled; }
  static void SetFledgeTrustedSignalsKVv1CreativeScanningEnabled(bool enabled) { is_fledge_trusted_signals_k_vv_1_creative_scanning_enabled_ = enabled; }
  static void SetFledgeTrustedSignalsKVv2ContextualDataEnabled(bool enabled) { is_fledge_trusted_signals_k_vv_2_contextual_data_enabled_ = enabled; }
  static void SetFledgeTrustedSignalsKVv2SupportEnabled(bool enabled) { is_fledge_trusted_signals_k_vv_2_support_enabled_ = enabled; }
  static void SetFlexWrapBalanceEnabled(bool enabled) { is_flex_wrap_balance_enabled_ = enabled; }
  static void SetFocusgroupEnabled(bool enabled) { is_focusgroup_enabled_ = enabled; }
  static void SetFocusgroupGridEnabled(bool enabled) { is_focusgroup_grid_enabled_ = enabled; }
  static void SetFontAccessEnabled(bool enabled) { is_font_access_enabled_ = enabled; }
  static void SetFontDataServiceEnabled(bool enabled) { is_font_data_service_enabled_ = enabled; }
  static void SetFontFallbackForTabSizeEnabled(bool enabled) { is_font_fallback_for_tab_size_enabled_ = enabled; }
  static void SetFontFamilyPostscriptMatchingCTMigrationEnabled(bool enabled) { is_font_family_postscript_matching_ct_migration_enabled_ = enabled; }
  static void SetFontFamilyStyleMatchingCTMigrationEnabled(bool enabled) { is_font_family_style_matching_ct_migration_enabled_ = enabled; }
  static void SetFontFeatureSettingsDescriptorEnabled(bool enabled) { is_font_feature_settings_descriptor_enabled_ = enabled; }
  static void SetFontFormatAvar2Enabled(bool enabled) { is_font_format_avar_2_enabled_ = enabled; }
  static void SetFontLanguageOverrideEnabled(bool enabled) { is_font_language_override_enabled_ = enabled; }
  static void SetFontMatchAliasesAsLastResortEnabled(bool enabled) { is_font_match_aliases_as_last_resort_enabled_ = enabled; }
  static void SetFontStyleObliqueZeroDegreeAsNormalEnabled(bool enabled) { is_font_style_oblique_zero_degree_as_normal_enabled_ = enabled; }
  static void SetFontVariationSettingsDescriptorEnabled(bool enabled) { is_font_variation_settings_descriptor_enabled_ = enabled; }
  static void SetForcedColorsEnabled(bool enabled) { is_forced_colors_enabled_ = enabled; }
  static void SetForceEagerMeasureMemoryEnabled(bool enabled) { is_force_eager_measure_memory_enabled_ = enabled; }
  static void SetForceReduceMotionEnabled(bool enabled) { is_force_reduce_motion_enabled_ = enabled; }
  static void SetFractionalScrollOffsetsEnabled(bool enabled) { is_fractional_scroll_offsets_enabled_ = enabled; }
  static void SetFragmentedOofInCbEnabled(bool enabled) { is_fragmented_oof_in_cb_enabled_ = enabled; }
  static void SetFreezeFramesOnVisibilityEnabled(bool enabled) { is_freeze_frames_on_visibility_enabled_ = enabled; }
  static void SetGamepadMultitouchEnabled(bool enabled) { is_gamepad_multitouch_enabled_ = enabled; }
  static void SetGamepadRawInputChangeEventEnabled(bool enabled) { is_gamepad_raw_input_change_event_enabled_ = enabled; }
  static void SetGamepadWindowEventHandlersEnabled(bool enabled) { is_gamepad_window_event_handlers_enabled_ = enabled; }
  static void SetGeolocationElementEnabled(bool enabled) { is_geolocation_element_enabled_ = enabled; }
  static void SetGeometryMapperSingularTransformFixEnabled(bool enabled) { is_geometry_mapper_singular_transform_fix_enabled_ = enabled; }
  static void SetGeometryUtilsEnabled(bool enabled) { is_geometry_utils_enabled_ = enabled; }
  static void SetGeometryUtilsForCSSPseudoElementEnabled(bool enabled) { is_geometry_utils_for_css_pseudo_element_enabled_ = enabled; }
  static void SetGetAllScreensMediaEnabled(bool enabled) { is_get_all_screens_media_enabled_ = enabled; }
  static void SetGetComputedStyleOutsideFlatTreeEnabled(bool enabled) { is_get_computed_style_outside_flat_tree_enabled_ = enabled; }
  static void SetGetDisplayMediaEnabled(bool enabled) { is_get_display_media_enabled_ = enabled; }
  static void SetGetDisplayMediaRequiresUserActivationEnabled(bool enabled) { is_get_display_media_requires_user_activation_enabled_ = enabled; }
  static void SetGetDisplayMediaWindowAudioCaptureEnabled(bool enabled) { is_get_display_media_window_audio_capture_enabled_ = enabled; }
  static void SetGetElementsByNameOnlyHTMLElementsEnabled(bool enabled) { is_get_elements_by_name_only_html_elements_enabled_ = enabled; }
  static void SetGetUserMediaEchoCancellationModesEnabled(bool enabled) { is_get_user_media_echo_cancellation_modes_enabled_ = enabled; }
  static void SetGroupEffectEnabled(bool enabled) { is_group_effect_enabled_ = enabled; }
  static void SetHandleDeletionAtStartAndEndBoundaryContainingHiddenElementEnabled(bool enabled) { is_handle_deletion_at_start_and_end_boundary_containing_hidden_element_enabled_ = enabled; }
  static void SetHandleDisconnectedSelectionDuringDOMChangesEnabled(bool enabled) { is_handle_disconnected_selection_during_dom_changes_enabled_ = enabled; }
  static void SetHandleInvalidMaskImageWithBackdropFilterEnabled(bool enabled) { is_handle_invalid_mask_image_with_backdrop_filter_enabled_ = enabled; }
  static void SetHandleShadowDOMInSubstringUtilEnabled(bool enabled) { is_handle_shadow_dom_in_substring_util_enabled_ = enabled; }
  static void SetHandwritingRecognitionEnabled(bool enabled) { is_handwriting_recognition_enabled_ = enabled; }
  static void SetHasUAVisualTransitionEnabled(bool enabled) { is_has_ua_visual_transition_enabled_ = enabled; }
  static void SetHeadingOffsetEnabled(bool enabled) { is_heading_offset_enabled_ = enabled; }
  static void SetHideVideoControlsWhenUnneededEnabled(bool enabled) { is_hide_video_controls_when_unneeded_enabled_ = enabled; }
  static void SetHighlightsFromPointEnabled(bool enabled) { is_highlights_from_point_enabled_ = enabled; }
  static void SetHitTestBorderRadiusForStackingContextEnabled(bool enabled) { is_hit_test_border_radius_for_stacking_context_enabled_ = enabled; }
  static void SetHitTestContainerTransformStateForPreserve3dEnabled(bool enabled) { is_hit_test_container_transform_state_for_preserve_3d_enabled_ = enabled; }
  static void SetHrefTranslateEnabled(bool enabled) { is_href_translate_enabled_ = enabled; }
  static void SetHstsTopLevelNavigationsOnlyEnabled(bool enabled) { is_hsts_top_level_navigations_only_enabled_ = enabled; }
  static void SetHTMLAdoptionAlgorithmNewStepsEnabled(bool enabled) { is_html_adoption_algorithm_new_steps_enabled_ = enabled; }
  static void SetHTMLCommandActionsV2Enabled(bool enabled) { is_html_command_actions_v_2_enabled_ = enabled; }
  static void SetHTMLCommandElementRemovalEnabled(bool enabled) { is_html_command_element_removal_enabled_ = enabled; }
  static void SetHTMLCommandForScrollCommandsEnabled(bool enabled) { is_html_command_for_scroll_commands_enabled_ = enabled; }
  static void SetHTMLElementScrollParentEnabled(bool enabled) { is_html_element_scroll_parent_enabled_ = enabled; }
  static void SetHTMLImageElementActualNaturalSizeEnabled(bool enabled) { is_html_image_element_actual_natural_size_enabled_ = enabled; }
  static void SetHTMLInputElementDropWebkitClearButtonEnabled(bool enabled) { is_html_input_element_drop_webkit_clear_button_enabled_ = enabled; }
  static void SetHTMLInterestForInterestButtonPseudoEnabled(bool enabled) { is_html_interest_for_interest_button_pseudo_enabled_ = enabled; }
  static void SetHTMLLinkElementAttributeValueChangesEnabled(bool enabled) { is_html_link_element_attribute_value_changes_enabled_ = enabled; }
  static void SetHTMLParserYieldAndDelayOftenForTestingEnabled(bool enabled) { is_html_parser_yield_and_delay_often_for_testing_enabled_ = enabled; }
  static void SetHTMLParserYieldByUserTimingEnabled(bool enabled) { is_html_parser_yield_by_user_timing_enabled_ = enabled; }
  static void SetHTMLPrintingArtifactAnnotationsEnabled(bool enabled) { is_html_printing_artifact_annotations_enabled_ = enabled; }
  static void SetHTMLProcessingInstructionEnabled(bool enabled) { is_html_processing_instruction_enabled_ = enabled; }
  static void SetICUCapitalizationEnabled(bool enabled) { is_icu_capitalization_enabled_ = enabled; }
  static void SetIgnoreLetterSpacingInCursiveScriptsEnabled(bool enabled) { is_ignore_letter_spacing_in_cursive_scripts_enabled_ = enabled; }
  static void SetImageDataPixelFormatEnabled(bool enabled) { is_image_data_pixel_format_enabled_ = enabled; }
  static void SetImageDocumentUseLayoutWidthEnabled(bool enabled) { is_image_document_use_layout_width_enabled_ = enabled; }
  static void SetImageSrcsetReselectionEnabled(bool enabled) { is_image_srcset_reselection_enabled_ = enabled; }
  static void SetImplicitRootScrollerEnabled(bool enabled) { is_implicit_root_scroller_enabled_ = enabled; }
  static void SetImprovedSourceRetargetingEnabled(bool enabled) { is_improved_source_retargeting_enabled_ = enabled; }
  static void SetIncomingCallNotificationsEnabled(bool enabled) { is_incoming_call_notifications_enabled_ = enabled; }
  static void SetInertElementNonEditableEnabled(bool enabled) { is_inert_element_non_editable_enabled_ = enabled; }
  static void SetInfiniteCullRectEnabled(bool enabled) { is_infinite_cull_rect_enabled_ = enabled; }
  static void SetInheritUserModifyWithoutContenteditableEnabled(bool enabled) { is_inherit_user_modify_without_contenteditable_enabled_ = enabled; }
  static void SetInlineBlockLineNavigationEnabled(bool enabled) { is_inline_block_line_navigation_enabled_ = enabled; }
  static void SetInlineScriptCacheHintEnabled(bool enabled) { is_inline_script_cache_hint_enabled_ = enabled; }
  static void SetInnerHTMLParserFastpathLogFailureEnabled(bool enabled) { is_inner_html_parser_fastpath_log_failure_enabled_ = enabled; }
  static void SetInputEventDataTransferForInsertCmdEnabled(bool enabled) { is_input_event_data_transfer_for_insert_cmd_enabled_ = enabled; }
  static void SetInputEventsDeleteNonCollapsedSelectionEnabled(bool enabled) { is_input_events_delete_non_collapsed_selection_enabled_ = enabled; }
  static void SetInputInSelectEnabled(bool enabled) { is_input_in_select_enabled_ = enabled; }
  static void SetInputMultipleFieldsUIEnabled(bool enabled) { is_input_multiple_fields_ui_enabled_ = enabled; }
  static void SetInsertBlockquoteBeforeOuterBlockEnabled(bool enabled) { is_insert_blockquote_before_outer_block_enabled_ = enabled; }
  static void SetInstalledAppEnabled(bool enabled) { is_installed_app_enabled_ = enabled; }
  static void SetInstallElementEnabled(bool enabled) { is_install_element_enabled_ = enabled; }
  static void SetInstallOnDeviceSpeechRecognitionEnabled(bool enabled) { is_install_on_device_speech_recognition_enabled_ = enabled; }
  static void SetIntegrityPolicyScriptEnabled(bool enabled) { is_integrity_policy_script_enabled_ = enabled; }
  static void SetInterestEventsNonComposedEnabled(bool enabled) { is_interest_events_non_composed_enabled_ = enabled; }
  static void SetInterestGroupsInSharedStorageWorkletEnabled(bool enabled) { is_interest_groups_in_shared_storage_worklet_enabled_ = enabled; }
  static void SetIntersectionObserverCompositedAnimationsForceMainFramesEnabled(bool enabled) { is_intersection_observer_composited_animations_force_main_frames_enabled_ = enabled; }
  static void SetInvertedColorsEnabled(bool enabled) { is_inverted_colors_enabled_ = enabled; }
  static void SetInvisibleSVGAnimationThrottlingEnabled(bool enabled) { is_invisible_svg_animation_throttling_enabled_ = enabled; }
  static void SetJavaScriptCompileHintsPerFunctionMagicRuntimeEnabled(bool enabled) { is_java_script_compile_hints_per_function_magic_runtime_enabled_ = enabled; }
  static void SetJavaScriptSourcePhaseImportsEnabled(bool enabled) { is_java_script_source_phase_imports_enabled_ = enabled; }
  static void SetKeyboardAccessibleTooltipEnabled(bool enabled) { is_keyboard_accessible_tooltip_enabled_ = enabled; }
  static void SetKeySystemTrackConfigurationEncryptionSchemeEnabled(bool enabled) { is_key_system_track_configuration_encryption_scheme_enabled_ = enabled; }
  static void SetLabelInteractiveContentCheckBeforeHandlerEnabled(bool enabled) { is_label_interactive_content_check_before_handler_enabled_ = enabled; }
  static void SetLangAttributeAwareFormControlUIEnabled(bool enabled) { is_lang_attribute_aware_form_control_ui_enabled_ = enabled; }
  static void SetLanguageDetectionAPIEnabled(bool enabled) { is_language_detection_api_enabled_ = enabled; }
  static void SetLanguageDetectionAPIForWorkersEnabled(bool enabled) { is_language_detection_api_for_workers_enabled_ = enabled; }
  static void SetLayoutBoxRectGettersUseFragmentsEnabled(bool enabled) { is_layout_box_rect_getters_use_fragments_enabled_ = enabled; }
  static void SetLayoutIgnoreMarginsForStickyEnabled(bool enabled) { is_layout_ignore_margins_for_sticky_enabled_ = enabled; }
  static void SetLayoutImageEmptyNaturalSizeBeforeSizeAvailableEnabled(bool enabled) { is_layout_image_empty_natural_size_before_size_available_enabled_ = enabled; }
  static void SetLayoutTableCellAlignmentSafeEnabled(bool enabled) { is_layout_table_cell_alignment_safe_enabled_ = enabled; }
  static void SetLazyImageConformantLoadEventTimingEnabled(bool enabled) { is_lazy_image_conformant_load_event_timing_enabled_ = enabled; }
  static void SetLazyLoadVideoAndAudioEnabled(bool enabled) { is_lazy_load_video_and_audio_enabled_ = enabled; }
  static void SetLeftClickToHandleSuggestionEnabled(bool enabled) { is_left_click_to_handle_suggestion_enabled_ = enabled; }
  static void SetLightDismissFromClickEnabled(bool enabled) { is_light_dismiss_from_click_enabled_ = enabled; }
  static void SetLinkBlurImprovementEnabled(bool enabled) { is_link_blur_improvement_enabled_ = enabled; }
  static void SetListOwnerMustHaveCSSBoxEnabled(bool enabled) { is_list_owner_must_have_css_box_enabled_ = enabled; }
  static void SetLocalNetworkAccessNonSecureContextAllowedEnabled(bool enabled) { is_local_network_access_non_secure_context_allowed_enabled_ = enabled; }
  static void SetLocalNetworkAccessPermissionPolicyEnabled(bool enabled) { is_local_network_access_permission_policy_enabled_ = enabled; }
  static void SetLocalNetworkAccessSplitPermissionsEnabled(bool enabled) { is_local_network_access_split_permissions_enabled_ = enabled; }
  static void SetLocalNetworkAccessWebRTCEnabled(bool enabled) { is_local_network_access_web_rtc_enabled_ = enabled; }
  static void SetLockedModeEnabled(bool enabled) { is_locked_mode_enabled_ = enabled; }
  static void SetLogicalStartOfLineBlockFallbackEnabled(bool enabled) { is_logical_start_of_line_block_fallback_enabled_ = enabled; }
  static void SetLoginElementEnabled(bool enabled) { is_login_element_enabled_ = enabled; }
  static void SetLongAnimationFrameSourceCharPositionEnabled(bool enabled) { is_long_animation_frame_source_char_position_enabled_ = enabled; }
  static void SetLongAnimationFrameSourceLineColumnEnabled(bool enabled) { is_long_animation_frame_source_line_column_enabled_ = enabled; }
  static void SetLongAnimationFrameSourceLineColumnInterfaceEnabled(bool enabled) { is_long_animation_frame_source_line_column_interface_enabled_ = enabled; }
  static void SetLongAnimationFrameStyleDurationEnabled(bool enabled) { is_long_animation_frame_style_duration_enabled_ = enabled; }
  static void SetLongPressLinkSelectTextEnabled(bool enabled) { is_long_press_link_select_text_enabled_ = enabled; }
  static void SetLongTaskFromLongAnimationFrameEnabled(bool enabled) { is_long_task_from_long_animation_frame_enabled_ = enabled; }
  static void SetMacCharacterFallbackCacheEnabled(bool enabled) { is_mac_character_fallback_cache_enabled_ = enabled; }
  static void SetMacDisableCtrlHomeEndEnabled(bool enabled) { is_mac_disable_ctrl_home_end_enabled_ = enabled; }
  static void SetMachineLearningNeuralNetworkEnabled(bool enabled) { is_machine_learning_neural_network_enabled_ = enabled; }
  static void SetMacSystemClipboardPermissionCheckEnabled(bool enabled) { is_mac_system_clipboard_permission_check_enabled_ = enabled; }
  static void SetManagedConfigurationEnabled(bool enabled) { is_managed_configuration_enabled_ = enabled; }
  static void SetManualTextEnabled(bool enabled) { is_manual_text_enabled_ = enabled; }
  static void SetMarginTrimEnabled(bool enabled) { is_margin_trim_enabled_ = enabled; }
  static void SetMaskDeserializationTimeForCrossOriginMessagesEnabled(bool enabled) { is_mask_deserialization_time_for_cross_origin_messages_enabled_ = enabled; }
  static void SetMathMLOperatorRTLMirroringEnabled(bool enabled) { is_mathml_operator_rtl_mirroring_enabled_ = enabled; }
  static void SetMathMLSerializationOnCopyEnabled(bool enabled) { is_mathml_serialization_on_copy_enabled_ = enabled; }
  static void SetMathMLSkipMtrTagInAncestorWrappingEnabled(bool enabled) { is_mathml_skip_mtr_tag_in_ancestor_wrapping_enabled_ = enabled; }
  static void SetMeasureMemoryEnabled(bool enabled) { is_measure_memory_enabled_ = enabled; }
  static void SetMediaCapabilitiesEncodingInfoEnabled(bool enabled) { is_media_capabilities_encoding_info_enabled_ = enabled; }
  static void SetMediaCapabilitiesSpatialAudioEnabled(bool enabled) { is_media_capabilities_spatial_audio_enabled_ = enabled; }
  static void SetMediaCaptureEnabled(bool enabled) { is_media_capture_enabled_ = enabled; }
  static void SetMediaCaptureBackgroundBlurEnabled(bool enabled) { is_media_capture_background_blur_enabled_ = enabled; }
  static void SetMediaCaptureCameraControlsEnabled(bool enabled) { is_media_capture_camera_controls_enabled_ = enabled; }
  static void SetMediaCaptureConfigurationChangeEnabled(bool enabled) { is_media_capture_configuration_change_enabled_ = enabled; }
  static void SetMediaCaptureVoiceIsolationEnabled(bool enabled) { is_media_capture_voice_isolation_enabled_ = enabled; }
  static void SetMediaControlsExpandGestureEnabled(bool enabled) { is_media_controls_expand_gesture_enabled_ = enabled; }
  static void SetMediaControlsOverlayPlayButtonEnabled(bool enabled) { is_media_controls_overlay_play_button_enabled_ = enabled; }
  static void SetMediaElementVolumeGreaterThanOneEnabled(bool enabled) { is_media_element_volume_greater_than_one_enabled_ = enabled; }
  static void SetMediaEngagementBypassAutoplayPoliciesEnabled(bool enabled) { is_media_engagement_bypass_autoplay_policies_enabled_ = enabled; }
  static void SetMediaLatencyHintEnabled(bool enabled) { is_media_latency_hint_enabled_ = enabled; }
  static void SetMediaPlaybackWhileNotVisiblePermissionPolicyEnabled(bool enabled) { is_media_playback_while_not_visible_permission_policy_enabled_ = enabled; }
  static void SetMediaQueryNavigationControlsEnabled(bool enabled) { is_media_query_navigation_controls_enabled_ = enabled; }
  static void SetMediaSessionEnabled(bool enabled) { is_media_session_enabled_ = enabled; }
  static void SetMediaSessionChapterInformationEnabled(bool enabled) { is_media_session_chapter_information_enabled_ = enabled; }
  static void SetMediaSourceExperimentalEnabled(bool enabled) { is_media_source_experimental_enabled_ = enabled; }
  static void SetMediaSourceExtensionsForWebCodecsEnabled(bool enabled) { is_media_source_extensions_for_webcodecs_enabled_ = enabled; }
  static void SetMediaStreamTrackTransferEnabled(bool enabled) { is_media_stream_track_transfer_enabled_ = enabled; }
  static void SetMediaStreamTrackWebSpeechEnabled(bool enabled) { is_media_stream_track_web_speech_enabled_ = enabled; }
  static void SetMemoryConsumerForNGShapeCacheEnabled(bool enabled) { is_memory_consumer_for_ng_shape_cache_enabled_ = enabled; }
  static void SetMenuElementsEnabled(bool enabled) { is_menu_elements_enabled_ = enabled; }
  static void SetMergeFixedLayersEnabled(bool enabled) { is_merge_fixed_layers_enabled_ = enabled; }
  static void SetMergeStickyLayersEnabled(bool enabled) { is_merge_sticky_layers_enabled_ = enabled; }
  static void SetMessagePortCloseEventEnabled(bool enabled) { is_message_port_close_event_enabled_ = enabled; }
  static void SetMiddleClickAutoscrollEnabled(bool enabled) { is_middle_click_autoscroll_enabled_ = enabled; }
  static void SetMixedContentAutoupgradesUseIsMixedContentRestrictedInFrameEnabled(bool enabled) { is_mixed_content_autoupgrades_use_is_mixed_content_restricted_in_frame_enabled_ = enabled; }
  static void SetMobileLayoutThemeEnabled(bool enabled) { is_mobile_layout_theme_enabled_ = enabled; }
  static void SetModifyParagraphCrossEditingoundaryEnabled(bool enabled) { is_modify_paragraph_cross_editingoundary_enabled_ = enabled; }
  static void SetModulePreloadReferrerEnabled(bool enabled) { is_module_preload_referrer_enabled_ = enabled; }
  static void SetModulePreloadStyleJsonEnabled(bool enabled) { is_module_preload_style_json_enabled_ = enabled; }
  static void SetMojoJSEnabled(bool enabled);
  static void SetMojoJSTestEnabled(bool enabled);
  static void SetMoveEndingSelectionToListChildEnabled(bool enabled) { is_move_ending_selection_to_list_child_enabled_ = enabled; }
  static void SetMulticolColumnWrappingEnabled(bool enabled) { is_multicol_column_wrapping_enabled_ = enabled; }
  static void SetNavigateEventAddHandlerOnPrecommitEnabled(bool enabled) { is_navigate_event_add_handler_on_precommit_enabled_ = enabled; }
  static void SetNavigateEventClearOnRestoreEnabled(bool enabled) { is_navigate_event_clear_on_restore_enabled_ = enabled; }
  static void SetNavigateEventDeferCrossDocumentCommitEnabled(bool enabled) { is_navigate_event_defer_cross_document_commit_enabled_ = enabled; }
  static void SetNavigationEventTimingEnabled(bool enabled) { is_navigation_event_timing_enabled_ = enabled; }
  static void SetNavigationIdEnabled(bool enabled) { is_navigation_id_enabled_ = enabled; }
  static void SetNavigatorContentUtilsEnabled(bool enabled) { is_navigator_content_utils_enabled_ = enabled; }
  static void SetNetInfoConstantTypeEnabled(bool enabled) { is_net_info_constant_type_enabled_ = enabled; }
  static void SetNetInfoDownlinkMaxEnabled(bool enabled) { is_net_info_downlink_max_enabled_ = enabled; }
  static void SetNewHTMLSettingMethodsEnabled(bool enabled) { is_new_html_setting_methods_enabled_ = enabled; }
  static void SetNoExtendSelectionToUserSelectNoneOutOfFlowEnabled(bool enabled) { is_no_extend_selection_to_user_select_none_out_of_flow_enabled_ = enabled; }
  static void SetNoFontAntialiasingEnabled(bool enabled) { is_no_font_antialiasing_enabled_ = enabled; }
  static void SetNoIdleEncodingForWebTestsEnabled(bool enabled) { is_no_idle_encoding_for_web_tests_enabled_ = enabled; }
  static void SetNonEmptyBlockquotesOnOutdentingEnabled(bool enabled) { is_non_empty_blockquotes_on_outdenting_enabled_ = enabled; }
  static void SetNonEmptyVisibleTextSelectionForTextFragmentEnabled(bool enabled) { is_non_empty_visible_text_selection_for_text_fragment_enabled_ = enabled; }
  static void SetNonStandardAppearanceValueSliderVerticalEnabled(bool enabled) { is_non_standard_appearance_value_slider_vertical_enabled_ = enabled; }
  static void SetNormalizeLineEndingsInInsertTextEnabled(bool enabled) { is_normalize_line_endings_in_insert_text_enabled_ = enabled; }
  static void SetNormalizeNbspForPasteAndDropEnabled(bool enabled) { is_normalize_nbsp_for_paste_and_drop_enabled_ = enabled; }
  static void SetNotificationConstructorEnabled(bool enabled) { is_notification_constructor_enabled_ = enabled; }
  static void SetNotificationContentImageEnabled(bool enabled) { is_notification_content_image_enabled_ = enabled; }
  static void SetNotificationsEnabled(bool enabled) { is_notifications_enabled_ = enabled; }
  static void SetNotificationTriggersEnabled(bool enabled) { is_notification_triggers_enabled_ = enabled; }
  static void SetNumberInputFullWidthCharsEnabled(bool enabled) { is_number_input_full_width_chars_enabled_ = enabled; }
  static void SetOffMainThreadCSSPaintEnabled(bool enabled) { is_off_main_thread_css_paint_enabled_ = enabled; }
  static void SetOffscreenCanvasGetContextAttributesEnabled(bool enabled) { is_offscreen_canvas_get_context_attributes_enabled_ = enabled; }
  static void SetOffsetPathTransformUpdateFixEnabled(bool enabled) { is_offset_path_transform_update_fix_enabled_ = enabled; }
  static void SetOmitBlurEventOnElementRemovalEnabled(bool enabled) { is_omit_blur_event_on_element_removal_enabled_ = enabled; }
  static void SetOnDeviceWebSpeechAvailableEnabled(bool enabled) { is_on_device_web_speech_available_enabled_ = enabled; }
  static void SetOnDeviceWebSpeechQualityEnabled(bool enabled) { is_on_device_web_speech_quality_enabled_ = enabled; }
  static void SetOpaqueRangeEnabled(bool enabled) { is_opaque_range_enabled_ = enabled; }
  static void SetOpenPopoverInvokerRestrictToSameTreeScopeEnabled(bool enabled) { is_open_popover_invoker_restrict_to_same_tree_scope_enabled_ = enabled; }
  static void SetOrientationEventEnabled(bool enabled) { is_orientation_event_enabled_ = enabled; }
  static void SetOriginAPIEnabled(bool enabled) { is_origin_api_enabled_ = enabled; }
  static void SetOriginIsolationHeaderEnabled(bool enabled) { is_origin_isolation_header_enabled_ = enabled; }
  static void SetOriginPolicyEnabled(bool enabled) { is_origin_policy_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIEnabled(bool enabled) { is_origin_trials_sample_api_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIBrowserReadWriteEnabled(bool enabled) { is_origin_trials_sample_api_browser_read_write_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIDependentEnabled(bool enabled) { is_origin_trials_sample_api_dependent_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIDeprecationEnabled(bool enabled) { is_origin_trials_sample_api_deprecation_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIExpiryGracePeriodEnabled(bool enabled) { is_origin_trials_sample_api_expiry_grace_period_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIExpiryGracePeriodThirdPartyEnabled(bool enabled) { is_origin_trials_sample_api_expiry_grace_period_third_party_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIImpliedEnabled(bool enabled) { is_origin_trials_sample_api_implied_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIInvalidOSEnabled(bool enabled) { is_origin_trials_sample_api_invalid_os_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPINavigationEnabled(bool enabled) { is_origin_trials_sample_api_navigation_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIPersistentExpiryGracePeriodEnabled(bool enabled) { is_origin_trials_sample_api_persistent_expiry_grace_period_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIPersistentFeatureEnabled(bool enabled) { is_origin_trials_sample_api_persistent_feature_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIPersistentInvalidOSEnabled(bool enabled) { is_origin_trials_sample_api_persistent_invalid_os_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIPersistentThirdPartyDeprecationFeatureEnabled(bool enabled) { is_origin_trials_sample_api_persistent_third_party_deprecation_feature_enabled_ = enabled; }
  static void SetOriginTrialsSampleAPIThirdPartyEnabled(bool enabled) { is_origin_trials_sample_api_third_party_enabled_ = enabled; }
  static void SetOutlineDrawAutoStyleZeroWidthEnabled(bool enabled) { is_outline_draw_auto_style_zero_width_enabled_ = enabled; }
  static void SetOverlayGlobalRuleRemovalEnabled(bool enabled) { is_overlay_global_rule_removal_enabled_ = enabled; }
  static void SetOverlayPropertyEnabled(bool enabled) { is_overlay_property_enabled_ = enabled; }
  static void SetOverscrollGesturesEnabled(bool enabled) { is_overscroll_gestures_enabled_ = enabled; }
  static void SetPagePopupEnabled(bool enabled) { is_page_popup_enabled_ = enabled; }
  static void SetPagePopupCopyPasteEnabled(bool enabled) { is_page_popup_copy_paste_enabled_ = enabled; }
  static void SetPageRevealEventEnabled(bool enabled) { is_page_reveal_event_enabled_ = enabled; }
  static void SetPageSwapEventEnabled(bool enabled) { is_page_swap_event_enabled_ = enabled; }
  static void SetPaintHoldingForIframesEnabled(bool enabled) { is_paint_holding_for_iframes_enabled_ = enabled; }
  static void SetPaintOffsetTranslationForCompositedEnabled(bool enabled) { is_paint_offset_translation_for_composited_enabled_ = enabled; }
  static void SetPaintTimingMixinEnabled(bool enabled) { is_paint_timing_mixin_enabled_ = enabled; }
  static void SetPaintUnderInvalidationCheckingEnabled(bool enabled) { is_paint_under_invalidation_checking_enabled_ = enabled; }
  static void SetParakeetEnabled(bool enabled) { is_parakeet_enabled_ = enabled; }
  static void SetPartialCompletionNotAllowedInMoveParagraphsEnabled(bool enabled) { is_partial_completion_not_allowed_in_move_paragraphs_enabled_ = enabled; }
  static void SetPartitionVisitedLinkDatabaseWithSelfLinksEnabled(bool enabled) { is_partition_visited_link_database_with_self_links_enabled_ = enabled; }
  static void SetPasswordRevealEnabled(bool enabled) { is_password_reveal_enabled_ = enabled; }
  static void SetPaymentAppEnabled(bool enabled) { is_payment_app_enabled_ = enabled; }
  static void SetPaymentLinkDetectionEnabled(bool enabled) { is_payment_link_detection_enabled_ = enabled; }
  static void SetPaymentMethodChangeEventEnabled(bool enabled) { is_payment_method_change_event_enabled_ = enabled; }
  static void SetPaymentRequestEnabled(bool enabled) { is_payment_request_enabled_ = enabled; }
  static void SetPerformanceManagerInstrumentationEnabled(bool enabled) { is_performance_manager_instrumentation_enabled_ = enabled; }
  static void SetPerformanceMarkCustomUserTimingFromSubframeEnabled(bool enabled) { is_performance_mark_custom_user_timing_from_subframe_enabled_ = enabled; }
  static void SetPerformanceMarkFeatureUsageEnabled(bool enabled) { is_performance_mark_feature_usage_enabled_ = enabled; }
  static void SetPerformanceNavigationTimingConfidenceEnabled(bool enabled) { is_performance_navigation_timing_confidence_enabled_ = enabled; }
  static void SetPeriodicBackgroundSyncEnabled(bool enabled) { is_periodic_background_sync_enabled_ = enabled; }
  static void SetPerMethodCanMakePaymentQuotaEnabled(bool enabled) { is_per_method_can_make_payment_quota_enabled_ = enabled; }
  static void SetPermissionsRequestRevokeEnabled(bool enabled) { is_permissions_request_revoke_enabled_ = enabled; }
  static void SetPlaceholderVisibilityEnabled(bool enabled) { is_placeholder_visibility_enabled_ = enabled; }
  static void SetPNaClEnabled(bool enabled) { is_p_na_cl_enabled_ = enabled; }
  static void SetPointerEventDeviceIdEnabled(bool enabled) { is_pointer_event_device_id_enabled_ = enabled; }
  static void SetPointerLockOnAndroidEnabled(bool enabled) { is_pointer_lock_on_android_enabled_ = enabled; }
  static void SetPointerRawUpdateOnlyInSecureContextEnabled(bool enabled) { is_pointer_raw_update_only_in_secure_context_enabled_ = enabled; }
  static void SetPopoverHintNewBehaviorEnabled(bool enabled) { is_popover_hint_new_behavior_enabled_ = enabled; }
  static void SetPositionOutsideTabSpanCheckSiblingNodeEnabled(bool enabled) { is_position_outside_tab_span_check_sibling_node_enabled_ = enabled; }
  static void SetPositionVisibilityIgnoreNonClipAncestorsEnabled(bool enabled) { is_position_visibility_ignore_non_clip_ancestors_enabled_ = enabled; }
  static void SetPotentialPermissionsPolicyReportingEnabled(bool enabled) { is_potential_permissions_policy_reporting_enabled_ = enabled; }
  static void SetPreciseMemoryInfoEnabled(bool enabled) { is_precise_memory_info_enabled_ = enabled; }
  static void SetPreferDefaultScrollbarStylesEnabled(bool enabled) { is_prefer_default_scrollbar_styles_enabled_ = enabled; }
  static void SetPreferNonCompositedScrollingEnabled(bool enabled) { is_prefer_non_composited_scrolling_enabled_ = enabled; }
  static void SetPreferredAudioOutputDevicesEnabled(bool enabled) { is_preferred_audio_output_devices_enabled_ = enabled; }
  static void SetPrefersReducedDataEnabled(bool enabled) { is_prefers_reduced_data_enabled_ = enabled; }
  static void SetPreloadLinkRelDataUrlsEnabled(bool enabled) { is_preload_link_rel_data_urls_enabled_ = enabled; }
  static void SetPrerender2Enabled(bool enabled) { is_prerender_2_enabled_ = enabled; }
  static void SetPrerender2CrossOriginIframesEnabled(bool enabled) { is_prerender_2_cross_origin_iframes_enabled_ = enabled; }
  static void SetPrerenderActivationByFormSubmissionEnabled(bool enabled) { is_prerender_activation_by_form_submission_enabled_ = enabled; }
  static void SetPrerenderUntilScriptEnabled(bool enabled) { is_prerender_until_script_enabled_ = enabled; }
  static void SetPresentationEnabled(bool enabled) { is_presentation_enabled_ = enabled; }
  static void SetPreserveDropEffectEnabled(bool enabled) { is_preserve_drop_effect_enabled_ = enabled; }
  static void SetPreventUndoIfNotEditableEnabled(bool enabled) { is_prevent_undo_if_not_editable_enabled_ = enabled; }
  static void SetPrivateAggregationApiErrorReportingEnabled(bool enabled) { is_private_aggregation_api_error_reporting_enabled_ = enabled; }
  static void SetPrivateAggregationApiMaxContributionsEnabled(bool enabled) { is_private_aggregation_api_max_contributions_enabled_ = enabled; }
  static void SetPrivateNetworkAccessNullIpAddressEnabled(bool enabled) { is_private_network_access_null_ip_address_enabled_ = enabled; }
  static void SetPrivateStateTokensEnabled(bool enabled) { is_private_state_tokens_enabled_ = enabled; }
  static void SetPrivateStateTokensAlwaysAllowIssuanceEnabled(bool enabled) { is_private_state_tokens_always_allow_issuance_enabled_ = enabled; }
  static void SetProfilerAPIEnabled(bool enabled) { is_profiler_api_enabled_ = enabled; }
  static void SetProfilerAPIForDedicatedWorkerEnabled(bool enabled) { is_profiler_api_for_dedicated_worker_enabled_ = enabled; }
  static void SetProgrammaticScrollPromiseEnabled(bool enabled) { is_programmatic_scroll_promise_enabled_ = enabled; }
  static void SetProgressMaxIsPositiveEnabled(bool enabled) { is_progress_max_is_positive_enabled_ = enabled; }
  static void SetPropagateOverscrollBehaviorFromRootEnabled(bool enabled) { is_propagate_overscroll_behavior_from_root_enabled_ = enabled; }
  static void SetProtectedOriginTrialsSampleAPIEnabled(bool enabled);
  static void SetProtectedOriginTrialsSampleAPIDependentEnabled(bool enabled);
  static void SetProtectedOriginTrialsSampleAPIImpliedEnabled(bool enabled);
  static void SetPseudoElementsFocusableEnabled(bool enabled) { is_pseudo_elements_focusable_enabled_ = enabled; }
  static void SetPseudoElementsHitTestableEnabled(bool enabled) { is_pseudo_elements_hit_testable_enabled_ = enabled; }
  static void SetPseudoElementsHoverableEnabled(bool enabled) { is_pseudo_elements_hoverable_enabled_ = enabled; }
  static void SetPushMessageDataBytesEnabled(bool enabled) { is_push_message_data_bytes_enabled_ = enabled; }
  static void SetPushMessagingEnabled(bool enabled) { is_push_messaging_enabled_ = enabled; }
  static void SetPushMessagingSubscriptionChangeEnabled(bool enabled) { is_push_messaging_subscription_change_enabled_ = enabled; }
  static void SetQuotaExceededErrorUpdateEnabled(bool enabled) { is_quota_exceeded_error_update_enabled_ = enabled; }
  static void SetQuoteFirstLineStyleEnabled(bool enabled) { is_quote_first_line_style_enabled_ = enabled; }
  static void SetRasterInducingScrollEnabled(bool enabled) { is_raster_inducing_scroll_enabled_ = enabled; }
  static void SetReadableStreamBYOBReaderReadMinOptionEnabled(bool enabled) { is_readable_stream_byob_reader_read_min_option_enabled_ = enabled; }
  static void SetReadClipboardDataOnClipboardItemGetTypeEnabled(bool enabled) { is_read_clipboard_data_on_clipboard_item_get_type_enabled_ = enabled; }
  static void SetReadingFlowWithSlotsEnabled(bool enabled) { is_reading_flow_with_slots_enabled_ = enabled; }
  static void SetRecheckParentDuringNodeVectorInsertionEnabled(bool enabled) { is_recheck_parent_during_node_vector_insertion_enabled_ = enabled; }
  static void SetRecordSameDocumentPresentationTimeOnceEnabled(bool enabled) { is_record_same_document_presentation_time_once_enabled_ = enabled; }
  static void SetReduceAcceptLanguageEnabled(bool enabled) { is_reduce_accept_language_enabled_ = enabled; }
  static void SetReduceUserAgentDataLinuxPlatformVersionEnabled(bool enabled) { is_reduce_user_agent_data_linux_platform_version_enabled_ = enabled; }
  static void SetReduceUserAgentMinorVersionEnabled(bool enabled) { is_reduce_user_agent_minor_version_enabled_ = enabled; }
  static void SetRegionCaptureEnabled(bool enabled) { is_region_capture_enabled_ = enabled; }
  static void SetRelatedWebsitePartitionAPIEnabled(bool enabled) { is_related_website_partition_api_enabled_ = enabled; }
  static void SetRelOpenerBcgDependencyHintEnabled(bool enabled) { is_rel_opener_bcg_dependency_hint_enabled_ = enabled; }
  static void SetRemotePlaybackEnabled(bool enabled) { is_remote_playback_enabled_ = enabled; }
  static void SetRemotePlaybackBackendEnabled(bool enabled) { is_remote_playback_backend_enabled_ = enabled; }
  static void SetRemoveCharsetAutoDetectionForISO2022JPEnabled(bool enabled) { is_remove_charset_auto_detection_for_iso_2022_jp_enabled_ = enabled; }
  static void SetRemoveChildrenInReplaceChildrenEnabled(bool enabled) { is_remove_children_in_replace_children_enabled_ = enabled; }
  static void SetRemoveCollapsedPlaceholderForContentEditableEnabled(bool enabled) { is_remove_collapsed_placeholder_for_content_editable_enabled_ = enabled; }
  static void SetRemoveDanglingMarkupInTargetEnabled(bool enabled) { is_remove_dangling_markup_in_target_enabled_ = enabled; }
  static void SetRemoveDataUrlInSvgUseEnabled(bool enabled) { is_remove_data_url_in_svg_use_enabled_ = enabled; }
  static void SetRemoveFormatFilterBackgroundColorEnabled(bool enabled) { is_remove_format_filter_background_color_enabled_ = enabled; }
  static void SetRemoveNonAllowlistedCreateEventEnabled(bool enabled) { is_remove_non_allowlisted_create_event_enabled_ = enabled; }
  static void SetRemoveScrollNodeWorkaroundEnabled(bool enabled) { is_remove_scroll_node_workaround_enabled_ = enabled; }
  static void SetRemoveSelectionCanonicalizationInMoveParagraphEnabled(bool enabled) { is_remove_selection_canonicalization_in_move_paragraph_enabled_ = enabled; }
  static void SetRemoveVisibleSelectionInDOMSelectionEnabled(bool enabled) { is_remove_visible_selection_in_dom_selection_enabled_ = enabled; }
  static void SetRenderBlockingFullFrameRateEnabled(bool enabled) { is_render_blocking_full_frame_rate_enabled_ = enabled; }
  static void SetRenderBlockingStatusEnabled(bool enabled) { is_render_blocking_status_enabled_ = enabled; }
  static void SetRenderPriorityAttributeEnabled(bool enabled) { is_render_priority_attribute_enabled_ = enabled; }
  static void SetReportFirstFrameTimeAsRenderTimeEnabled(bool enabled) { is_report_first_frame_time_as_render_time_enabled_ = enabled; }
  static void SetReportLayoutShiftRectsInCssPixelsEnabled(bool enabled) { is_report_layout_shift_rects_in_css_pixels_enabled_ = enabled; }
  static void SetRequestIsReloadNavigationEnabled(bool enabled) { is_request_is_reload_navigation_enabled_ = enabled; }
  static void SetRequestMainFrameAfterFirstVideoFrameEnabled(bool enabled) { is_request_main_frame_after_first_video_frame_enabled_ = enabled; }
  static void SetResolveVarStylesOnCopyEnabled(bool enabled) { is_resolve_var_styles_on_copy_enabled_ = enabled; }
  static void SetResourceTimingContentEncodingEnabled(bool enabled) { is_resource_timing_content_encoding_enabled_ = enabled; }
  static void SetResourceTimingContentTypeEnabled(bool enabled) { is_resource_timing_content_type_enabled_ = enabled; }
  static void SetResourceTimingInitiatorEnabled(bool enabled) { is_resource_timing_initiator_enabled_ = enabled; }
  static void SetResourceTimingUseCORSForBodySizesEnabled(bool enabled) { is_resource_timing_use_cors_for_body_sizes_enabled_ = enabled; }
  static void SetRespectOverscrollBehaviorForScrollBubblingEnabled(bool enabled) { is_respect_overscroll_behavior_for_scroll_bubbling_enabled_ = enabled; }
  static void SetResponsiveIframesEnabled(bool enabled) { is_responsive_iframes_enabled_ = enabled; }
  static void SetRestrictGamepadAccessEnabled(bool enabled) { is_restrict_gamepad_access_enabled_ = enabled; }
  static void SetRestrictOwnAudioEnabled(bool enabled) { is_restrict_own_audio_enabled_ = enabled; }
  static void SetRootScrollbarFollowsBrowserThemeEnabled(bool enabled) { is_root_scrollbar_follows_browser_theme_enabled_ = enabled; }
  static void SetRouteMatchingEnabled(bool enabled) { is_route_matching_enabled_ = enabled; }
  static void SetRtcAlwaysNegotiateDataChannelsEnabled(bool enabled) { is_rtc_always_negotiate_data_channels_enabled_ = enabled; }
  static void SetRtcAudioJitterBufferMaxPacketsEnabled(bool enabled) { is_rtc_audio_jitter_buffer_max_packets_enabled_ = enabled; }
  static void SetRTCDataChannelPriorityEnabled(bool enabled) { is_rtc_data_channel_priority_enabled_ = enabled; }
  static void SetRTCDiagnosticLoggingEnabled(bool enabled) { is_rtc_diagnostic_logging_enabled_ = enabled; }
  static void SetRTCEncodedFrameAudioLevelEnabled(bool enabled) { is_rtc_encoded_frame_audio_level_enabled_ = enabled; }
  static void SetRTCEncodedFrameSetMetadataEnabled(bool enabled) { is_rtc_encoded_frame_set_metadata_enabled_ = enabled; }
  static void SetRTCEncodedFrameTimestampsEnabled(bool enabled) { is_rtc_encoded_frame_timestamps_enabled_ = enabled; }
  static void SetRTCEncodedVideoFrameAdditionalMetadataEnabled(bool enabled) { is_rtc_encoded_video_frame_additional_metadata_enabled_ = enabled; }
  static void SetRTCJitterBufferTargetEnabled(bool enabled) { is_rtc_jitter_buffer_target_enabled_ = enabled; }
  static void SetRTCLegacyCallbackBasedGetStatsEnabled(bool enabled) { is_rtc_legacy_callback_based_get_stats_enabled_ = enabled; }
  static void SetRTCRtpEncodingParametersCodecEnabled(bool enabled) { is_rtc_rtp_encoding_parameters_codec_enabled_ = enabled; }
  static void SetRTCRtpScaleResolutionDownToEnabled(bool enabled) { is_rtc_rtp_scale_resolution_down_to_enabled_ = enabled; }
  static void SetRTCRtpScriptTransformEnabled(bool enabled) { is_rtc_rtp_script_transform_enabled_ = enabled; }
  static void SetRTCRtpTransportEnabled(bool enabled) { is_rtc_rtp_transport_enabled_ = enabled; }
  static void SetRTCStatsRelativePacketArrivalDelayEnabled(bool enabled) { is_rtc_stats_relative_packet_arrival_delay_enabled_ = enabled; }
  static void SetRTCSvcScalabilityModeEnabled(bool enabled) { is_rtc_svc_scalability_mode_enabled_ = enabled; }
  static void SetRunMicrotaskBeforeXmlScriptEnabled(bool enabled) { is_run_microtask_before_xml_script_enabled_ = enabled; }
  static void SetRunSnapshotPostLayoutStateStepsEnabled(bool enabled) { is_run_snapshot_post_layout_state_steps_enabled_ = enabled; }
  static void SetSanitizerAPIEnabled(bool enabled) { is_sanitizer_api_enabled_ = enabled; }
  static void SetScopedCustomElementRegistryEnabled(bool enabled) { is_scoped_custom_element_registry_enabled_ = enabled; }
  static void SetScopedViewTransitionsEnabled(bool enabled) { is_scoped_view_transitions_enabled_ = enabled; }
  static void SetScreenDetailedHdrHeadroomEnabled(bool enabled) { is_screen_detailed_hdr_headroom_enabled_ = enabled; }
  static void SetScriptBasedOnUnicodeBlockEnabled(bool enabled) { is_script_based_on_unicode_block_enabled_ = enabled; }
  static void SetScriptedSpeechRecognitionEnabled(bool enabled) { is_scripted_speech_recognition_enabled_ = enabled; }
  static void SetScriptedSpeechSynthesisEnabled(bool enabled) { is_scripted_speech_synthesis_enabled_ = enabled; }
  static void SetScrollAnchorPriorityCandidateSubtreeEnabled(bool enabled) { is_scroll_anchor_priority_candidate_subtree_enabled_ = enabled; }
  static void SetScrollAnchorSerializationUseParentForTextNodeEnabled(bool enabled) { is_scroll_anchor_serialization_use_parent_for_text_node_enabled_ = enabled; }
  static void SetScrollbarColorEnabled(bool enabled) { is_scrollbar_color_enabled_ = enabled; }
  static void SetScrollbarGutterBugFixEnabled(bool enabled) { is_scrollbar_gutter_bug_fix_enabled_ = enabled; }
  static void SetScrollbarWidthEnabled(bool enabled) { is_scrollbar_width_enabled_ = enabled; }
  static void SetScrollIntoViewNearestEnabled(bool enabled) { is_scroll_into_view_nearest_enabled_ = enabled; }
  static void SetScrollIntoViewRootFrameViewportBugFixEnabled(bool enabled) { is_scroll_into_view_root_frame_viewport_bug_fix_enabled_ = enabled; }
  static void SetScrollTimelineCurrentTimeEnabled(bool enabled) { is_scroll_timeline_current_time_enabled_ = enabled; }
  static void SetScrollTimelineNamedRangeScrollEnabled(bool enabled) { is_scroll_timeline_named_range_scroll_enabled_ = enabled; }
  static void SetScrollTopLeftInteropEnabled(bool enabled) { is_scroll_top_left_interop_enabled_ = enabled; }
  static void SetScrollToTextFragmentUniqueFragmentsEnabled(bool enabled) { is_scroll_to_text_fragment_unique_fragments_enabled_ = enabled; }
  static void SetSearchTextHighlightPseudoEnabled(bool enabled) { is_search_text_highlight_pseudo_enabled_ = enabled; }
  static void SetSecurePaymentConfirmationEnabled(bool enabled) { is_secure_payment_confirmation_enabled_ = enabled; }
  static void SetSecurePaymentConfirmationAvailabilityAPIEnabled(bool enabled) { is_secure_payment_confirmation_availability_api_enabled_ = enabled; }
  static void SetSecurePaymentConfirmationCapabilitiesEnabled(bool enabled) { is_secure_payment_confirmation_capabilities_enabled_ = enabled; }
  static void SetSecurePaymentConfirmationDebugEnabled(bool enabled) { is_secure_payment_confirmation_debug_enabled_ = enabled; }
  static void SetSecurePaymentConfirmationOptOutEnabled(bool enabled) { is_secure_payment_confirmation_opt_out_enabled_ = enabled; }
  static void SetSelectAudioOutputEnabled(bool enabled) { is_select_audio_output_enabled_ = enabled; }
  static void SetSelectedcontentelementAttributeEnabled(bool enabled) { is_selectedcontentelement_attribute_enabled_ = enabled; }
  static void SetSelectedcontentMultipleEnabled(bool enabled) { is_selectedcontent_multiple_enabled_ = enabled; }
  static void SetSelectedcontentSpecEnabled(bool enabled) { is_selectedcontent_spec_enabled_ = enabled; }
  static void SetSelectionAndFocusedVisiblePositionMatchEnabled(bool enabled) { is_selection_and_focused_visible_position_match_enabled_ = enabled; }
  static void SetSelectionCollapsedDirectionNoneEnabled(bool enabled) { is_selection_collapsed_direction_none_enabled_ = enabled; }
  static void SetSelectionFocusAffinityEnabled(bool enabled) { is_selection_focus_affinity_enabled_ = enabled; }
  static void SetSelectionHandleWithBottomClippedEnabled(bool enabled) { is_selection_handle_with_bottom_clipped_enabled_ = enabled; }
  static void SetSelectionRemoveRangeNotFoundErrorEnabled(bool enabled) { is_selection_remove_range_not_found_error_enabled_ = enabled; }
  static void SetSelectionSetBaseAndExtentNonNullNodeEnabled(bool enabled) { is_selection_set_base_and_extent_non_null_node_enabled_ = enabled; }
  static void SetSelectionToStringSkipsUserSelectNoneEnabled(bool enabled) { is_selection_to_string_skips_user_select_none_enabled_ = enabled; }
  static void SetSelectionUpdateOnlyAfterAutoscrollEnabled(bool enabled) { is_selection_update_only_after_autoscroll_enabled_ = enabled; }
  static void SetSelectionUpdateToInitialSelectionInListifyEnabled(bool enabled) { is_selection_update_to_initial_selection_in_listify_enabled_ = enabled; }
  static void SetSelectiveClipboardFormatReadEnabled(bool enabled) { is_selective_clipboard_format_read_enabled_ = enabled; }
  static void SetSelectivePermissionsInterventionEnabled(bool enabled) { is_selective_permissions_intervention_enabled_ = enabled; }
  static void SetSelectRemoveOverflowHiddenEnabled(bool enabled) { is_select_remove_overflow_hidden_enabled_ = enabled; }
  static void SetSendBeaconThrowForBlobWithNonSimpleTypeEnabled(bool enabled) { is_send_beacon_throw_for_blob_with_non_simple_type_enabled_ = enabled; }
  static void SetSendSlotChangeSignalAfterNodeInsertedEnabled(bool enabled) { is_send_slot_change_signal_after_node_inserted_enabled_ = enabled; }
  static void SetSensorExtraClassesEnabled(bool enabled) { is_sensor_extra_classes_enabled_ = enabled; }
  static void SetSeparateDeferModuleScriptTasksEnabled(bool enabled) { is_separate_defer_module_script_tasks_enabled_ = enabled; }
  static void SetSerialEnabled(bool enabled) { is_serial_enabled_ = enabled; }
  static void SetSerializeViewTransitionStateInSPAEnabled(bool enabled) { is_serialize_view_transition_state_in_spa_enabled_ = enabled; }
  static void SetSerialPortConnectedEnabled(bool enabled) { is_serial_port_connected_enabled_ = enabled; }
  static void SetServiceWorkerBackgroundSyncInDedicatedWorkerEnabled(bool enabled) { is_service_worker_background_sync_in_dedicated_worker_enabled_ = enabled; }
  static void SetServiceWorkerClientLifecycleStateEnabled(bool enabled) { is_service_worker_client_lifecycle_state_enabled_ = enabled; }
  static void SetServiceWorkerInDedicatedWorkerEnabled(bool enabled) { is_service_worker_in_dedicated_worker_enabled_ = enabled; }
  static void SetServiceWorkerStaticRouterTimingInfoEnabled(bool enabled) { is_service_worker_static_router_timing_info_enabled_ = enabled; }
  static void SetSetDefaultDropEffectEnabled(bool enabled) { is_set_default_drop_effect_enabled_ = enabled; }
  static void SetSetHTMLCanRunScriptsEnabled(bool enabled) { is_set_html_can_run_scripts_enabled_ = enabled; }
  static void SetSetSequentialFocusStartingPointEnabled(bool enabled) { is_set_sequential_focus_starting_point_enabled_ = enabled; }
  static void SetShadowContourFollowsBorderEnabled(bool enabled) { is_shadow_contour_follows_border_enabled_ = enabled; }
  static void SetShadowRootAdoptedStyleSheetEnabled(bool enabled) { is_shadow_root_adopted_style_sheet_enabled_ = enabled; }
  static void SetShadowRootReferenceTargetEnabled(bool enabled) { is_shadow_root_reference_target_enabled_ = enabled; }
  static void SetShadowRootReferenceTargetAriaOwnsEnabled(bool enabled) { is_shadow_root_reference_target_aria_owns_enabled_ = enabled; }
  static void SetSharedArrayBufferEnabled(bool enabled) { is_shared_array_buffer_enabled_ = enabled; }
  static void SetSharedArrayBufferUnrestrictedAccessAllowedEnabled(bool enabled) { is_shared_array_buffer_unrestricted_access_allowed_enabled_ = enabled; }
  static void SetSharedStorageAPIEnabled(bool enabled) { is_shared_storage_api_enabled_ = enabled; }
  static void SetSharedStorageWebLocksEnabled(bool enabled) { is_shared_storage_web_locks_enabled_ = enabled; }
  static void SetSharedWorkerEnabled(bool enabled) { is_shared_worker_enabled_ = enabled; }
  static void SetSharedWorkerExtendedLifetimeEnabled(bool enabled) { is_shared_worker_extended_lifetime_enabled_ = enabled; }
  static void SetSideRelativeBackgroundPositionEnabled(bool enabled) { is_side_relative_background_position_enabled_ = enabled; }
  static void SetSignatureBasedInlineIntegrityEnabled(bool enabled) { is_signature_based_inline_integrity_enabled_ = enabled; }
  static void SetSingleAxisScrollContainersEnabled(bool enabled) { is_single_axis_scroll_containers_enabled_ = enabled; }
  static void SetSkipAdEnabled(bool enabled) { is_skip_ad_enabled_ = enabled; }
  static void SetSkipCallbacksWhenDevToolsNotOpenEnabled(bool enabled) { is_skip_callbacks_when_dev_tools_not_open_enabled_ = enabled; }
  static void SetSkipEventCaptureEnabled(bool enabled) { is_skip_event_capture_enabled_ = enabled; }
  static void SetSkipNonEditableInAtomicMoveEnabled(bool enabled) { is_skip_non_editable_in_atomic_move_enabled_ = enabled; }
  static void SetSkipOofItemForBreakCandidateEnabled(bool enabled) { is_skip_oof_item_for_break_candidate_enabled_ = enabled; }
  static void SetSkipParagraphSplitForInlineInsertHTMLEnabled(bool enabled) { is_skip_paragraph_split_for_inline_insert_html_enabled_ = enabled; }
  static void SetSkipPseudoOnlyLinesInLineNavigationEnabled(bool enabled) { is_skip_pseudo_only_lines_in_line_navigation_enabled_ = enabled; }
  static void SetSkipTouchEventFilterEnabled(bool enabled) { is_skip_touch_event_filter_enabled_ = enabled; }
  static void SetSkipUnselectableContentInSerializationEnabled(bool enabled) { is_skip_unselectable_content_in_serialization_enabled_ = enabled; }
  static void SetSkipUnselectableElementsInParagraphBoundaryEnabled(bool enabled) { is_skip_unselectable_elements_in_paragraph_boundary_enabled_ = enabled; }
  static void SetSmallerViewportUnitsEnabled(bool enabled) { is_smaller_viewport_units_enabled_ = enabled; }
  static void SetSmartCardEnabled(bool enabled) { is_smart_card_enabled_ = enabled; }
  static void SetSmartZoomEnabled(bool enabled) { is_smart_zoom_enabled_ = enabled; }
  static void SetSnapshotScrollTimelinesPostLayoutEnabled(bool enabled) { is_snapshot_scroll_timelines_post_layout_enabled_ = enabled; }
  static void SetSoftNavigationDetectionEnabled(bool enabled) { is_soft_navigation_detection_enabled_ = enabled; }
  static void SetSoftNavigationDetectionIncludeReplaceStateEnabled(bool enabled) { is_soft_navigation_detection_include_replace_state_enabled_ = enabled; }
  static void SetSoftNavigationHeuristicsEnabled(bool enabled) { is_soft_navigation_heuristics_enabled_ = enabled; }
  static void SetSortedLayoutShiftSourcesByImpactAreaEnabled(bool enabled) { is_sorted_layout_shift_sources_by_impact_area_enabled_ = enabled; }
  static void SetSourceSpecificMulticastInDirectSocketsEnabled(bool enabled) { is_source_specific_multicast_in_direct_sockets_enabled_ = enabled; }
  static void SetSpatNavUsesCursorInheritanceEnabled(bool enabled) { is_spat_nav_uses_cursor_inheritance_enabled_ = enabled; }
  static void SetSpeakerSelectionEnabled(bool enabled) { is_speaker_selection_enabled_ = enabled; }
  static void SetSpeculationMeasurementEnabled(bool enabled) { is_speculation_measurement_enabled_ = enabled; }
  static void SetSpellCheckCustomDictionaryAPIEnabled(bool enabled) { is_spell_check_custom_dictionary_api_enabled_ = enabled; }
  static void SetSplitTextNotCleanupDummySpansEnabled(bool enabled) { is_split_text_not_cleanup_dummy_spans_enabled_ = enabled; }
  static void SetSplitViewLinkOpenEnabled(bool enabled) { is_split_view_link_open_enabled_ = enabled; }
  static void SetSrcsetSelectionMatchesImageSetEnabled(bool enabled) { is_srcset_selection_matches_image_set_enabled_ = enabled; }
  static void SetStableBlinkFeaturesEnabled(bool enabled) { is_stable_blink_features_enabled_ = enabled; }
  static void SetStackingContextIsNotStackedEnabled(bool enabled) { is_stacking_context_is_not_stacked_enabled_ = enabled; }
  static void SetStandardizedBrowserZoomEnabled(bool enabled) { is_standardized_browser_zoom_enabled_ = enabled; }
  static void SetStandardizedBrowserZoomOptOutEnabled(bool enabled) { is_standardized_browser_zoom_opt_out_enabled_ = enabled; }
  static void SetStickyPositionHasOverflowPerAxisEnabled(bool enabled) { is_sticky_position_has_overflow_per_axis_enabled_ = enabled; }
  static void SetStickyUserActivationAcrossSameOriginNavigationEnabled(bool enabled) { is_sticky_user_activation_across_same_origin_navigation_enabled_ = enabled; }
  static void SetStorageBucketsEnabled(bool enabled) { is_storage_buckets_enabled_ = enabled; }
  static void SetStorageBucketsDurabilityEnabled(bool enabled) { is_storage_buckets_durability_enabled_ = enabled; }
  static void SetStorageBucketsLocksEnabled(bool enabled) { is_storage_buckets_locks_enabled_ = enabled; }
  static void SetStreamingSanitizerEnabled(bool enabled) { is_streaming_sanitizer_enabled_ = enabled; }
  static void SetStrictMimeTypesForWorkersEnabled(bool enabled) { is_strict_mime_types_for_workers_enabled_ = enabled; }
  static void SetStylusHandwritingEnabled(bool enabled) { is_stylus_handwriting_enabled_ = enabled; }
  static void SetSubAppsEnabled(bool enabled) { is_sub_apps_enabled_ = enabled; }
  static void SetSuppressPointerStreamAfterDragEnabled(bool enabled) { is_suppress_pointer_stream_after_drag_enabled_ = enabled; }
  static void SetSvgAnchorElementAttributesEnabled(bool enabled) { is_svg_anchor_element_attributes_enabled_ = enabled; }
  static void SetSvgAnchorElementDownloadAttributeEnabled(bool enabled) { is_svg_anchor_element_download_attribute_enabled_ = enabled; }
  static void SetSvgAnimateMotionDiscreteCalcModeEnabled(bool enabled) { is_svg_animate_motion_discrete_calc_mode_enabled_ = enabled; }
  static void SetSvgAvoidResettingFilterQualityForTiledPatternEnabled(bool enabled) { is_svg_avoid_resetting_filter_quality_for_tiled_pattern_enabled_ = enabled; }
  static void SetSVGEmbeddedAsReplacedElementEnabled(bool enabled) { is_svg_embedded_as_replaced_element_enabled_ = enabled; }
  static void SetSvgEnableTextDecorationCssStylingEnabled(bool enabled) { is_svg_enable_text_decoration_css_styling_enabled_ = enabled; }
  static void SetSvgFallBackToContainerSizeEnabled(bool enabled) { is_svg_fall_back_to_container_size_enabled_ = enabled; }
  static void SetSvgFeImageSkipHiddenContainerViewportDependenceEnabled(bool enabled) { is_svg_fe_image_skip_hidden_container_viewport_dependence_enabled_ = enabled; }
  static void SetSvgFilterPaintsForHiddenContentEnabled(bool enabled) { is_svg_filter_paints_for_hidden_content_enabled_ = enabled; }
  static void SetSvgFilterUserSpaceViewportForSvgEnabled(bool enabled) { is_svg_filter_user_space_viewport_for_svg_enabled_ = enabled; }
  static void SetSvgIgnoreNegativeEllipseRadiiEnabled(bool enabled) { is_svg_ignore_negative_ellipse_radii_enabled_ = enabled; }
  static void SetSvgInlineRootPixelSnappingScaleAdjustmentEnabled(bool enabled) { is_svg_inline_root_pixel_snapping_scale_adjustment_enabled_ = enabled; }
  static void SetSvgLengthListClearOnParsingFailureEnabled(bool enabled) { is_svg_length_list_clear_on_parsing_failure_enabled_ = enabled; }
  static void SetSvgLengthResolveUnparsedValueEnabled(bool enabled) { is_svg_length_resolve_unparsed_value_enabled_ = enabled; }
  static void SetSvgNumberListClearOnParsingFailureEnabled(bool enabled) { is_svg_number_list_clear_on_parsing_failure_enabled_ = enabled; }
  static void SetSvgPartitionSVGDocumentResourcesInMemoryCacheEnabled(bool enabled) { is_svg_partition_svg_document_resources_in_memory_cache_enabled_ = enabled; }
  static void SetSvgPathLengthCssPropertyEnabled(bool enabled) { is_svg_path_length_css_property_enabled_ = enabled; }
  static void SetSvgPointListClearOnParsingFailureEnabled(bool enabled) { is_svg_point_list_clear_on_parsing_failure_enabled_ = enabled; }
  static void SetSvgScriptElementAsyncAttributeEnabled(bool enabled) { is_svg_script_element_async_attribute_enabled_ = enabled; }
  static void SetSvgSizingWithPreserveAspectRatioNoneEnabled(bool enabled) { is_svg_sizing_with_preserve_aspect_ratio_none_enabled_ = enabled; }
  static void SetSvgSmilClockValueValidationEnabled(bool enabled) { is_svg_smil_clock_value_validation_enabled_ = enabled; }
  static void SetSvgTextPathPathAttributeEnabled(bool enabled) { is_svg_text_path_path_attribute_enabled_ = enabled; }
  static void SetSvgTransformOnNestedSvgElementEnabled(bool enabled) { is_svg_transform_on_nested_svg_element_enabled_ = enabled; }
  static void SetSynthesizedKeyboardEventsForAccessibilityActionsEnabled(bool enabled) { is_synthesized_keyboard_events_for_accessibility_actions_enabled_ = enabled; }
  static void SetSyntheticMouseHoverOverInactivePageEnabled(bool enabled) { is_synthetic_mouse_hover_over_inactive_page_enabled_ = enabled; }
  static void SetSystemDefaultAccentColorsEnabled(bool enabled) { is_system_default_accent_colors_enabled_ = enabled; }
  static void SetSystemFallbackEmojiVSSupportEnabled(bool enabled) { is_system_fallback_emoji_vs_support_enabled_ = enabled; }
  static void SetSystemWakeLockEnabled(bool enabled) { is_system_wake_lock_enabled_ = enabled; }
  static void SetTableBorderColorNoImplicitBorderEnabled(bool enabled) { is_table_border_color_no_implicit_border_enabled_ = enabled; }
  static void SetTableDefaultBorderColorCurrentColorEnabled(bool enabled) { is_table_default_border_color_current_color_enabled_ = enabled; }
  static void SetTableIsAutoFixedLayoutEnabled(bool enabled) { is_table_is_auto_fixed_layout_enabled_ = enabled; }
  static void SetTabSizeAncestorEnabled(bool enabled) { is_tab_size_ancestor_enabled_ = enabled; }
  static void SetTabSizeWithSpacingEnabled(bool enabled) { is_tab_size_with_spacing_enabled_ = enabled; }
  static void SetTargetInShadowDeterminedBeforeListenerEnabled(bool enabled) { is_target_in_shadow_determined_before_listener_enabled_ = enabled; }
  static void SetTestBlinkFeatureDefaultEnabled(bool enabled) { is_test_blink_feature_default_enabled_ = enabled; }
  static void SetTestFeatureEnabled(bool enabled) { is_test_feature_enabled_ = enabled; }
  static void SetTestFeatureDependentEnabled(bool enabled) { is_test_feature_dependent_enabled_ = enabled; }
  static void SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(bool enabled) { is_test_feature_for_browser_process_read_write_access_origin_trial_enabled_ = enabled; }
  static void SetTestFeatureImpliedEnabled(bool enabled) { is_test_feature_implied_enabled_ = enabled; }
  static void SetTestFeatureProtectedEnabled(bool enabled);
  static void SetTestFeatureProtectedDependentEnabled(bool enabled);
  static void SetTestFeatureProtectedImpliedEnabled(bool enabled);
  static void SetTestFeatureStableEnabled(bool enabled) { is_test_feature_stable_enabled_ = enabled; }
  static void SetTextAreaScrollTopPreviewEnabled(bool enabled) { is_text_area_scroll_top_preview_enabled_ = enabled; }
  static void SetTextDetectorEnabled(bool enabled) { is_text_detector_enabled_ = enabled; }
  static void SetTextEmphasisLetterSpacingEnabled(bool enabled) { is_text_emphasis_letter_spacing_enabled_ = enabled; }
  static void SetTextEmphasisPositionAutoEnabled(bool enabled) { is_text_emphasis_position_auto_enabled_ = enabled; }
  static void SetTextEmphasisPunctuationExceptionsEnabled(bool enabled) { is_text_emphasis_punctuation_exceptions_enabled_ = enabled; }
  static void SetTextEmphasisWithRubyEnabled(bool enabled) { is_text_emphasis_with_ruby_enabled_ = enabled; }
  static void SetTextFragmentAPIEnabled(bool enabled) { is_text_fragment_api_enabled_ = enabled; }
  static void SetTextFragmentIdentifiersEnabled(bool enabled) { is_text_fragment_identifiers_enabled_ = enabled; }
  static void SetTextFragmentTapOpensContextMenuEnabled(bool enabled) { is_text_fragment_tap_opens_context_menu_enabled_ = enabled; }
  static void SetTextMetricsBaselinesEnabled(bool enabled) { is_text_metrics_baselines_enabled_ = enabled; }
  static void SetTextOverflowClipWithSelectionEnabled(bool enabled) { is_text_overflow_clip_with_selection_enabled_ = enabled; }
  static void SetTextOverflowStringEnabled(bool enabled) { is_text_overflow_string_enabled_ = enabled; }
  static void SetTextScaleMetaTagEnabled(bool enabled) { is_text_scale_meta_tag_enabled_ = enabled; }
  static void SetTextSpacingTrimFallbackEnabled(bool enabled) { is_text_spacing_trim_fallback_enabled_ = enabled; }
  static void SetTextSpacingTrimFallback2Enabled(bool enabled) { is_text_spacing_trim_fallback_2_enabled_ = enabled; }
  static void SetTextSpacingTrimFallbackChwsEnabled(bool enabled) { is_text_spacing_trim_fallback_chws_enabled_ = enabled; }
  static void SetTextSpacingTrimYuGothicUIEnabled(bool enabled) { is_text_spacing_trim_yu_gothic_ui_enabled_ = enabled; }
  static void SetThrottledHistoryAPIThrowsSecurityErrorEnabled(bool enabled) { is_throttled_history_api_throws_security_error_enabled_ = enabled; }
  static void SetTimelineTriggerEnabled(bool enabled) { is_timeline_trigger_enabled_ = enabled; }
  static void SetTimerThrottlingForBackgroundTabsEnabled(bool enabled) { is_timer_throttling_for_background_tabs_enabled_ = enabled; }
  static void SetTimestampBasedCLSTrackingEnabled(bool enabled) { is_timestamp_based_cls_tracking_enabled_ = enabled; }
  static void SetTimeZoneChangeEventEnabled(bool enabled) { is_time_zone_change_event_enabled_ = enabled; }
  static void SetTopicsAPIEnabled(bool enabled) { is_topics_api_enabled_ = enabled; }
  static void SetTopicsDocumentAPIEnabled(bool enabled) { is_topics_document_api_enabled_ = enabled; }
  static void SetTopicsImgAPIEnabled(bool enabled) { is_topics_img_api_enabled_ = enabled; }
  static void SetTouchDragAndContextMenuEnabled(bool enabled) { is_touch_drag_and_context_menu_enabled_ = enabled; }
  static void SetTouchDragAndDropEnabled(bool enabled) { is_touch_drag_and_drop_enabled_ = enabled; }
  static void SetTouchDragOnShortPressEnabled(bool enabled) { is_touch_drag_on_short_press_enabled_ = enabled; }
  static void SetTouchEventFeatureDetectionEnabled(bool enabled) { is_touch_event_feature_detection_enabled_ = enabled; }
  static void SetTouchTextEditingRedesignEnabled(bool enabled) { is_touch_text_editing_redesign_enabled_ = enabled; }
  static void SetTransferableRTCDataChannelEnabled(bool enabled) { is_transferable_rtc_data_channel_enabled_ = enabled; }
  static void SetTransitionNavigationQuietSkipEnabled(bool enabled) { is_transition_navigation_quiet_skip_enabled_ = enabled; }
  static void SetTranslateServiceEnabled(bool enabled) { is_translate_service_enabled_ = enabled; }
  static void SetTranslationAPIEnabled(bool enabled) { is_translation_api_enabled_ = enabled; }
  static void SetTranslationAPIForWorkersEnabled(bool enabled) { is_translation_api_for_workers_enabled_ = enabled; }
  static void SetTraverseFlatTreeToHandleSlotsEnabled(bool enabled) { is_traverse_flat_tree_to_handle_slots_enabled_ = enabled; }
  static void SetTreatMhtmlInitialDocumentLoadsAsCrossDocumentEnabled(bool enabled) { is_treat_mhtml_initial_document_loads_as_cross_document_enabled_ = enabled; }
  static void SetTrustedTypesCreateParserOptionsEnabled(bool enabled) { is_trusted_types_create_parser_options_enabled_ = enabled; }
  static void SetTrustedTypesFromLiteralEnabled(bool enabled) { is_trusted_types_from_literal_enabled_ = enabled; }
  static void SetTrustedTypesHTMLEnabled(bool enabled) { is_trusted_types_html_enabled_ = enabled; }
  static void SetTrustedTypesUseCodeLikeEnabled(bool enabled) { is_trusted_types_use_code_like_enabled_ = enabled; }
  static void SetTwoPhaseViewTransitionEnabled(bool enabled) { is_two_phase_view_transition_enabled_ = enabled; }
  static void SetUnclosedFormControlIsInvalidEnabled(bool enabled) { is_unclosed_form_control_is_invalid_enabled_ = enabled; }
  static void SetUnexposedTaskIdsEnabled(bool enabled) { is_unexposed_task_ids_enabled_ = enabled; }
  static void SetUnprefixedSpeechRecognitionEnabled(bool enabled) { is_unprefixed_speech_recognition_enabled_ = enabled; }
  static void SetUnrestrictedMeasureUserAgentSpecificMemoryEnabled(bool enabled) { is_unrestricted_measure_user_agent_specific_memory_enabled_ = enabled; }
  static void SetUnrestrictedSharedArrayBufferEnabled(bool enabled) { is_unrestricted_shared_array_buffer_enabled_ = enabled; }
  static void SetUnrestrictedUsbEnabled(bool enabled) { is_unrestricted_usb_enabled_ = enabled; }
  static void SetUpdateComplexSafaAreaConstraintsEnabled(bool enabled) { is_update_complex_safa_area_constraints_enabled_ = enabled; }
  static void SetUpdateSelectionOnNodeInsertionEnabled(bool enabled) { is_update_selection_on_node_insertion_enabled_ = enabled; }
  static void SetUpdateTrivalTextAfterFragmentCreationFromTextEnabled(bool enabled) { is_update_trival_text_after_fragment_creation_from_text_enabled_ = enabled; }
  static void SetURLPatternCompareComponentEnabled(bool enabled) { is_url_pattern_compare_component_enabled_ = enabled; }
  static void SetURLPatternGenerateEnabled(bool enabled) { is_url_pattern_generate_enabled_ = enabled; }
  static void SetURLSearchParamsHasAndDeleteMultipleArgsEnabled(bool enabled) { is_url_search_params_has_and_delete_multiple_args_enabled_ = enabled; }
  static void SetUseBeginFramePresentationFeedbackEnabled(bool enabled) { is_use_begin_frame_presentation_feedback_enabled_ = enabled; }
  static void SetUseBoundedSelectionOffsetsInEditContextDeleteOperationsEnabled(bool enabled) { is_use_bounded_selection_offsets_in_edit_context_delete_operations_enabled_ = enabled; }
  static void SetUseLargestPaintedImageForLCPCandidateEnabled(bool enabled) { is_use_largest_painted_image_for_lcp_candidate_enabled_ = enabled; }
  static void SetUseLowQualityInterpolationEnabled(bool enabled) { is_use_low_quality_interpolation_enabled_ = enabled; }
  static void SetUseOriginalDomOffsetsForOffsetMapEnabled(bool enabled) { is_use_original_dom_offsets_for_offset_map_enabled_ = enabled; }
  static void SetUsePositionForPointInFlexibleBoxWithSingleChildElementEnabled(bool enabled) { is_use_position_for_point_in_flexible_box_with_single_child_element_enabled_ = enabled; }
  static void SetUsePositionIfIsVisuallyEquivalentCandidateEnabled(bool enabled) { is_use_position_if_is_visually_equivalent_candidate_enabled_ = enabled; }
  static void SetUserActionPseudosStopAtTopLayerEnabled(bool enabled) { is_user_action_pseudos_stop_at_top_layer_enabled_ = enabled; }
  static void SetUserDefinedEntryPointTimingEnabled(bool enabled) { is_user_defined_entry_point_timing_enabled_ = enabled; }
  static void SetUserMediaElementEnabled(bool enabled) { is_user_media_element_enabled_ = enabled; }
  static void SetUseSelectionInDOMTreeAnchorInExtendSelectionEnabled(bool enabled) { is_use_selection_in_dom_tree_anchor_in_extend_selection_enabled_ = enabled; }
  static void SetUseShadowHostStyleCheckEditableEnabled(bool enabled) { is_use_shadow_host_style_check_editable_enabled_ = enabled; }
  static void SetUseUndoStepElementDispatchBeforeInputEnabled(bool enabled) { is_use_undo_step_element_dispatch_before_input_enabled_ = enabled; }
  static void SetV8IdleTasksEnabled(bool enabled) { is_v8_idle_tasks_enabled_ = enabled; }
  static void SetVideoAutoFullscreenEnabled(bool enabled) { is_video_auto_fullscreen_enabled_ = enabled; }
  static void SetVideoFrameMetadataBackgroundBlurEnabled(bool enabled) { is_video_frame_metadata_background_blur_enabled_ = enabled; }
  static void SetVideoFrameMetadataRtpTimestampEnabled(bool enabled) { is_video_frame_metadata_rtp_timestamp_enabled_ = enabled; }
  static void SetVideoFullscreenOrientationLockEnabled(bool enabled) { is_video_fullscreen_orientation_lock_enabled_ = enabled; }
  static void SetVideoRotateToFullscreenEnabled(bool enabled) { is_video_rotate_to_fullscreen_enabled_ = enabled; }
  static void SetVideoTrackGeneratorEnabled(bool enabled) { is_video_track_generator_enabled_ = enabled; }
  static void SetVideoTrackGeneratorInWindowEnabled(bool enabled) { is_video_track_generator_in_window_enabled_ = enabled; }
  static void SetVideoTrackGeneratorInWorkerEnabled(bool enabled) { is_video_track_generator_in_worker_enabled_ = enabled; }
  static void SetViewportHeightClientHintHeaderEnabled(bool enabled) { is_viewport_height_client_hint_header_enabled_ = enabled; }
  static void SetViewportSegmentsEnabled(bool enabled) { is_viewport_segments_enabled_ = enabled; }
  static void SetViewTransitionAsyncFinishedEnabled(bool enabled) { is_view_transition_async_finished_enabled_ = enabled; }
  static void SetViewTransitionDelayUnpauseOnTeardownEnabled(bool enabled) { is_view_transition_delay_unpause_on_teardown_enabled_ = enabled; }
  static void SetViewTransitionHoistBackdropFilterEffectEnabled(bool enabled) { is_view_transition_hoist_backdrop_filter_effect_enabled_ = enabled; }
  static void SetViewTransitionLongCallbackTimeoutForTestingEnabled(bool enabled) { is_view_transition_long_callback_timeout_for_testing_enabled_ = enabled; }
  static void SetViewTransitionUpdateLifecycleBeforeReadyEnabled(bool enabled) { is_view_transition_update_lifecycle_before_ready_enabled_ = enabled; }
  static void SetViewTransitionWaitUntilEnabled(bool enabled) { is_view_transition_wait_until_enabled_ = enabled; }
  static void SetVisibilityCollapseColumnEnabled(bool enabled) { is_visibility_collapse_column_enabled_ = enabled; }
  static void SetVisualRectMappingFixForExpansionEnabled(bool enabled) { is_visual_rect_mapping_fix_for_expansion_enabled_ = enabled; }
  static void SetWakeLockEnabled(bool enabled) { is_wake_lock_enabled_ = enabled; }
  static void SetWarnOnContentVisibilityRenderAccessEnabled(bool enabled) { is_warn_on_content_visibility_render_access_enabled_ = enabled; }
  static void SetWebAppInstallationEnabled(bool enabled) { is_web_app_installation_enabled_ = enabled; }
  static void SetWebAppLaunchQueueEnabled(bool enabled) { is_web_app_launch_queue_enabled_ = enabled; }
  static void SetWebAppScopeExtensionsEnabled(bool enabled) { is_web_app_scope_extensions_enabled_ = enabled; }
  static void SetWebAppScopeSystemAccentColorEnabled(bool enabled) { is_web_app_scope_system_accent_color_enabled_ = enabled; }
  static void SetWebAppTabStripEnabled(bool enabled) { is_web_app_tab_strip_enabled_ = enabled; }
  static void SetWebAppTabStripCustomizationsEnabled(bool enabled) { is_web_app_tab_strip_customizations_enabled_ = enabled; }
  static void SetWebAppTranslationsEnabled(bool enabled) { is_web_app_translations_enabled_ = enabled; }
  static void SetWebAssemblyCustomDescriptorsV2Enabled(bool enabled) { is_web_assembly_custom_descriptors_v_2_enabled_ = enabled; }
  static void SetWebAssemblyJSPromiseIntegrationEnabled(bool enabled) { is_web_assembly_js_promise_integration_enabled_ = enabled; }
  static void SetWebAudioBypassOutputBufferingEnabled(bool enabled) { is_web_audio_bypass_output_buffering_enabled_ = enabled; }
  static void SetWebAudioBypassOutputBufferingOptOutEnabled(bool enabled) { is_web_audio_bypass_output_buffering_opt_out_enabled_ = enabled; }
  static void SetWebAudioConfigurableRenderQuantumEnabled(bool enabled) { is_web_audio_configurable_render_quantum_enabled_ = enabled; }
  static void SetWebAuthEnabled(bool enabled) { is_web_auth_enabled_ = enabled; }
  static void SetWebAuthAuthenticatorAttachmentEnabled(bool enabled) { is_web_auth_authenticator_attachment_enabled_ = enabled; }
  static void SetWebAuthenticationAmbientEnabled(bool enabled) { is_web_authentication_ambient_enabled_ = enabled; }
  static void SetWebAuthenticationAttestationFormatsEnabled(bool enabled) { is_web_authentication_attestation_formats_enabled_ = enabled; }
  static void SetWebAuthenticationImmediateGetEnabled(bool enabled) { is_web_authentication_immediate_get_enabled_ = enabled; }
  static void SetWebAuthenticationRemoteDesktopSupportEnabled(bool enabled) { is_web_authentication_remote_desktop_support_enabled_ = enabled; }
  static void SetWebAuthenticationSupplementalPubKeysEnabled(bool enabled) { is_web_authentication_supplemental_pub_keys_enabled_ = enabled; }
  static void SetWebBluetoothEnabled(bool enabled) { is_web_bluetooth_enabled_ = enabled; }
  static void SetWebBluetoothGetDevicesEnabled(bool enabled) { is_web_bluetooth_get_devices_enabled_ = enabled; }
  static void SetWebBluetoothScanningEnabled(bool enabled) { is_web_bluetooth_scanning_enabled_ = enabled; }
  static void SetWebBluetoothWatchAdvertisementsEnabled(bool enabled) { is_web_bluetooth_watch_advertisements_enabled_ = enabled; }
  static void SetWebCodecsVideoEncoderBuffersEnabled(bool enabled) { is_webcodecs_video_encoder_buffers_enabled_ = enabled; }
  static void SetWebCryptoPQCEnabled(bool enabled) { is_web_crypto_pqc_enabled_ = enabled; }
  static void SetWebFontResizeLCPEnabled(bool enabled) { is_web_font_resize_lcp_enabled_ = enabled; }
  static void SetWebGLDeveloperExtensionsEnabled(bool enabled) { is_webgl_developer_extensions_enabled_ = enabled; }
  static void SetWebGLDraftExtensionsEnabled(bool enabled) { is_webgl_draft_extensions_enabled_ = enabled; }
  static void SetWebGLDrawingBufferStorageEnabled(bool enabled) { is_webgl_drawing_buffer_storage_enabled_ = enabled; }
  static void SetWebGLOnWebGPUEnabled(bool enabled) { is_webgl_on_webgpu_enabled_ = enabled; }
  static void SetWebGPUCompatibilityModeEnabled(bool enabled) { is_webgpu_compatibility_mode_enabled_ = enabled; }
  static void SetWebGPUDeveloperFeaturesEnabled(bool enabled) { is_webgpu_developer_features_enabled_ = enabled; }
  static void SetWebGPUExperimentalFeaturesEnabled(bool enabled) { is_webgpu_experimental_features_enabled_ = enabled; }
  static void SetWebGPUImmediatesFeatureEnabled(bool enabled) { is_webgpu_immediates_feature_enabled_ = enabled; }
  static void SetWebGPUMapSyncOnWorkersEnabled(bool enabled) { is_webgpu_map_sync_on_workers_enabled_ = enabled; }
  static void SetWebGPUMultithreadDawnWireOnWorkersEnabled(bool enabled) { is_webgpu_multithread_dawn_wire_on_workers_enabled_ = enabled; }
  static void SetWebGPUTransientAttachmentEnabled(bool enabled) { is_webgpu_transient_attachment_enabled_ = enabled; }
  static void SetWebHIDEnabled(bool enabled) { is_web_hid_enabled_ = enabled; }
  static void SetWebHIDOnServiceWorkersEnabled(bool enabled) { is_web_hid_on_service_workers_enabled_ = enabled; }
  static void SetWebIdentityDigitalCredentialsEnabled(bool enabled) { is_web_identity_digital_credentials_enabled_ = enabled; }
  static void SetWebIdentityDigitalCredentialsCreationEnabled(bool enabled) { is_web_identity_digital_credentials_creation_enabled_ = enabled; }
  static void SetWebIDLBigIntUsesToBigIntEnabled(bool enabled) { is_web_idl_big_int_uses_to_big_int_enabled_ = enabled; }
  static void SetWebMCPEnabled(bool enabled) { is_web_mcp_enabled_ = enabled; }
  static void SetWebMCPDeclarativeFileInputEnabled(bool enabled) { is_web_mcp_declarative_file_input_enabled_ = enabled; }
  static void SetWebMCPFormAssociatedCustomElementsEnabled(bool enabled) { is_web_mcp_form_associated_custom_elements_enabled_ = enabled; }
  static void SetWebMCPTestingEnabled(bool enabled) { is_web_mcp_testing_enabled_ = enabled; }
  static void SetWebNFCEnabled(bool enabled) { is_web_nfc_enabled_ = enabled; }
  static void SetWebOTPEnabled(bool enabled) { is_web_otp_enabled_ = enabled; }
  static void SetWebOTPAssertionFeaturePolicyEnabled(bool enabled) { is_web_otp_assertion_feature_policy_enabled_ = enabled; }
  static void SetWebPreferencesEnabled(bool enabled) { is_web_preferences_enabled_ = enabled; }
  static void SetWebPrintingEnabled(bool enabled) { is_web_printing_enabled_ = enabled; }
  static void SetWebShareEnabled(bool enabled) { is_web_share_enabled_ = enabled; }
  static void SetWebSocketStreamEnabled(bool enabled) { is_websocket_stream_enabled_ = enabled; }
  static void SetWebSocketStreamStandardBinaryChunkTypeEnabled(bool enabled) { is_websocket_stream_standard_binary_chunk_type_enabled_ = enabled; }
  static void SetWebSpeechRecognitionContextEnabled(bool enabled) { is_web_speech_recognition_context_enabled_ = enabled; }
  static void SetWebTransportApplicationProtocolEnabled(bool enabled) { is_web_transport_application_protocol_enabled_ = enabled; }
  static void SetWebTransportCongestionControlEnabled(bool enabled) { is_web_transport_congestion_control_enabled_ = enabled; }
  static void SetWebTransportCustomCertificatesEnabled(bool enabled) { is_web_transport_custom_certificates_enabled_ = enabled; }
  static void SetWebTransportSendGroupEnabled(bool enabled) { is_web_transport_send_group_enabled_ = enabled; }
  static void SetWebTransportStatsEnabled(bool enabled) { is_web_transport_stats_enabled_ = enabled; }
  static void SetWebUIBundledCodeCacheAsyncFetchEnabled(bool enabled) { is_web_ui_bundled_code_cache_async_fetch_enabled_ = enabled; }
  static void SetWebUSBEnabled(bool enabled) { is_web_usb_enabled_ = enabled; }
  static void SetWebUSBOnDedicatedWorkersEnabled(bool enabled) { is_web_usb_on_dedicated_workers_enabled_ = enabled; }
  static void SetWebUSBOnServiceWorkersEnabled(bool enabled) { is_web_usb_on_service_workers_enabled_ = enabled; }
  static void SetWebVTTRegionsEnabled(bool enabled) { is_web_vtt_regions_enabled_ = enabled; }
  static void SetWebXREnabled(bool enabled) { is_web_xr_enabled_ = enabled; }
  static void SetWebXREnabledFeaturesEnabled(bool enabled) { is_web_xr_enabled_features_enabled_ = enabled; }
  static void SetWebXRFrameRateEnabled(bool enabled) { is_web_xr_frame_rate_enabled_ = enabled; }
  static void SetWebXRFrontFacingEnabled(bool enabled) { is_web_xr_front_facing_enabled_ = enabled; }
  static void SetWebXRGPUBindingEnabled(bool enabled) { is_web_xr_gpu_binding_enabled_ = enabled; }
  static void SetWebXRHitTestEntityTypesEnabled(bool enabled) { is_web_xr_hit_test_entity_types_enabled_ = enabled; }
  static void SetWebXRImageTrackingEnabled(bool enabled) { is_web_xr_image_tracking_enabled_ = enabled; }
  static void SetWebXRLayersEnabled(bool enabled) { is_web_xr_layers_enabled_ = enabled; }
  static void SetWebXRLayersCommonEnabled(bool enabled) { is_web_xr_layers_common_enabled_ = enabled; }
  static void SetWebXRMeshDetectionEnabled(bool enabled) { is_web_xr_mesh_detection_enabled_ = enabled; }
  static void SetWebXRPlaneDetectionEnabled(bool enabled) { is_web_xr_plane_detection_enabled_ = enabled; }
  static void SetWebXRPoseMotionDataEnabled(bool enabled) { is_web_xr_pose_motion_data_enabled_ = enabled; }
  static void SetWebXRSpecParityEnabled(bool enabled) { is_web_xr_spec_parity_enabled_ = enabled; }
  static void SetWebXRVisibilityMaskEnabled(bool enabled) { is_web_xr_visibility_mask_enabled_ = enabled; }
  static void SetWindowDefaultStatusEnabled(bool enabled) { is_window_default_status_enabled_ = enabled; }
  static void SetWordSkipSpacesPunctuationFixEnabled(bool enabled) { is_word_skip_spaces_punctuation_fix_enabled_ = enabled; }
  static void SetWordSpacingWhiteSpacePreEnabled(bool enabled) { is_word_spacing_white_space_pre_enabled_ = enabled; }
  static void SetXMLNoExternalEntitiesEnabled(bool enabled) { is_xml_no_external_entities_enabled_ = enabled; }
  static void SetXMLParsingRustEnabled(bool enabled) { is_xml_parsing_rust_enabled_ = enabled; }
  static void SetXMLRustForNonXsltEnabled(bool enabled) { is_xml_rust_for_non_xslt_enabled_ = enabled; }
  static void SetXMLSerializerConsistentDefaultNsDeclMatchingEnabled(bool enabled) { is_xml_serializer_consistent_default_ns_decl_matching_enabled_ = enabled; }
  static void SetXPathShadowDOMSupportEnabled(bool enabled) { is_xpath_shadow_dom_support_enabled_ = enabled; }
  static void SetXSLTEnabled(bool enabled) { is_xslt_enabled_ = enabled; }
  static void SetXSLTSpecialTrialEnabled(bool enabled) { is_xslt_special_trial_enabled_ = enabled; }

 private:
  friend class RuntimeEnabledFeaturesTestHelpers;

  static bool is_about_blank_page_respects_dark_mode_on_user_action_enabled_;
  static bool is_accelerated_2d_canvas_enabled_;
  static bool is_accelerated_small_canvases_enabled_;
  static bool is_accessibility_aria_virtual_content_enabled_;
  static bool is_accessibility_custom_element_role_none_enabled_;
  static bool is_accessibility_expose_display_none_enabled_;
  static bool is_accessibility_implicit_actions_enabled_;
  static bool is_accessibility_min_role_tabbable_enabled_;
  static bool is_accessibility_os_level_bold_text_enabled_;
  static bool is_accessibility_prohibited_names_enabled_;
  static bool is_accessibility_serialization_size_metrics_enabled_;
  static bool is_accessibility_use_ax_position_for_document_markers_enabled_;
  static bool is_access_key_label_enabled_;
  static bool is_address_space_enabled_;
  static bool is_ad_interest_group_api_enabled_;
  static bool is_adjust_dom_offset_to_layout_offset_for_secure_text_enabled_;
  static bool is_adjust_end_of_next_paragraph_if_moved_paragraph_is_updated_enabled_;
  static bool is_ad_tagging_enabled_;
  static bool is_ai_classifier_api_enabled_;
  static bool is_ai_page_content_anchored_offscreen_non_actionability_enabled_;
  static bool is_ai_page_content_build_on_load_for_testing_enabled_;
  static bool is_ai_page_content_check_geometry_enabled_;
  static bool is_ai_page_content_convert_node_text_to_utf_8_enabled_;
  static bool is_ai_page_content_element_css_redaction_enabled_;
  static bool is_ai_page_content_include_svg_subtree_enabled_;
  static bool is_ai_page_content_outer_box_map_to_ancestor_space_enabled_;
  static bool is_ai_page_content_paid_content_annotation_enabled_;
  static bool is_ai_page_content_visual_viewport_clamp_enabled_;
  static bool is_ai_prompt_api_enabled_;
  static bool is_ai_prompt_api_for_extension_enabled_;
  static bool is_ai_prompt_api_for_workers_enabled_;
  static bool is_ai_prompt_api_legacy_identifiers_enabled_;
  static bool is_ai_prompt_api_legacy_params_enabled_;
  static bool is_ai_prompt_api_multimodal_input_enabled_;
  static bool is_ai_prompt_api_params_enabled_;
  static bool is_ai_prompt_api_structured_output_enabled_;
  static bool is_ai_prompt_api_tool_use_enabled_;
  static bool is_ai_proofreading_api_enabled_;
  static bool is_ai_rewriter_api_enabled_;
  static bool is_ai_rewriter_api_for_workers_enabled_;
  static bool is_ai_summarization_api_enabled_;
  static bool is_ai_summarization_api_for_workers_enabled_;
  static bool is_ai_summarization_performance_preference_enabled_;
  static bool is_ai_writer_api_enabled_;
  static bool is_ai_writer_api_for_workers_enabled_;
  static bool is_align_zoom_to_center_enabled_;
  static bool is_all_images_painted_sent_to_element_timing_enabled_;
  static bool is_allow_content_initiated_data_url_navigations_enabled_;
  static bool is_allow_preloading_with_csp_meta_tag_enabled_;
  static bool is_allow_same_site_none_cookies_in_sandbox_enabled_;
  static bool is_allow_skipping_editing_boundary_to_merge_end_enabled_;
  static bool is_allow_svg_use_to_reference_external_document_root_enabled_;
  static bool is_allow_synthetic_timing_for_canvas_capture_enabled_;
  static bool is_allow_ur_ns_in_iframes_enabled_;
  static bool is_ancestor_origins_stored_on_document_enabled_;
  static bool is_ancestor_revealing_new_spec_enabled_;
  static bool is_anchor_focus_ring_fix_enabled_;
  static bool is_anchor_position_adjustment_without_overflow_enabled_;
  static bool is_android_downloadable_fonts_matching_enabled_;
  static bool is_animation_progress_api_enabled_;
  static bool is_animation_trigger_enabled_;
  static bool is_animation_worklet_enabled_;
  static bool is_anonymous_iframe_enabled_;
  static bool is_aom_aria_relationship_properties_enabled_;
  static bool is_aom_aria_relationship_properties_aria_owns_enabled_;
  static bool is_appearance_base_enabled_;
  static bool is_approximate_geolocation_permission_enabled_;
  static bool is_approximate_geolocation_permission_api_enabled_;
  static bool is_approximate_geolocation_web_visible_api_enabled_;
  static bool is_app_title_enabled_;
  static bool is_aria_actions_enabled_;
  static bool is_aria_notify_enabled_;
  static bool is_aria_notify_v_2_enabled_;
  static bool is_aria_row_col_index_text_enabled_;
  static bool is_async_set_cookie_enabled_;
  static bool is_attribution_reporting_enabled_;
  static bool is_audio_context_async_state_transitions_enabled_;
  static bool is_audio_context_playback_stats_enabled_;
  static bool is_audio_context_playout_stats_enabled_;
  static bool is_audio_context_set_sink_id_enabled_;
  static bool is_audio_output_devices_enabled_;
  static bool is_audio_video_tracks_enabled_;
  static bool is_authenticator_passwords_only_immediate_requests_enabled_;
  static bool is_author_specified_layout_scroll_snap_behavior_enabled_;
  static bool is_auto_dark_mode_enabled_;
  static bool is_autofill_enabled_;
  static bool is_autofill_event_enabled_;
  static bool is_automation_controlled_enabled_;
  static bool is_auto_picture_in_picture_video_heuristics_enabled_;
  static bool is_avoid_forced_layout_on_invisible_document_close_enabled_;
  static bool is_avoid_merging_styled_span_with_siblings_enabled_;
  static bool is_avoid_normalizing_visible_positions_when_start_equals_end_enabled_;
  static bool is_backface_visibility_interop_enabled_;
  static bool is_back_forward_cache_enabled_;
  static bool is_back_forward_cache_experiment_http_header_enabled_;
  static bool is_back_forward_cache_not_restored_reasons_enabled_;
  static bool is_back_forward_cache_restoration_performance_entry_enabled_;
  static bool is_back_forward_cache_update_not_restored_reasons_name_enabled_;
  static bool is_background_clip_text_decoration_enabled_;
  static bool is_background_fetch_enabled_;
  static bool is_background_page_freeze_opt_out_enabled_;
  static bool is_barcode_detector_enabled_;
  static bool is_base_appearance_inline_sizing_enabled_;
  static bool is_bidi_caret_affinity_enabled_;
  static bool is_blink_extension_chrome_os_enabled_;
  static bool is_blink_extension_chrome_os_isolated_web_app_set_shape_enabled_;
  static bool is_blink_extension_chrome_os_kiosk_enabled_;
  static bool is_blink_extension_web_view_enabled_;
  static bool is_blink_extension_web_view_media_integrity_enabled_;
  static bool is_blink_geometry_mapper_viewport_fast_path_enabled_;
  static bool is_blink_lifecycle_script_forbidden_enabled_;
  static bool is_blink_runtime_call_stats_enabled_;
  static bool is_blob_bytes_enabled_;
  static bool is_blocking_focus_without_user_activation_enabled_;
  static bool is_block_select_popup_unfocused_window_enabled_;
  static bool is_boundary_event_dispatch_tracks_node_removal_enabled_;
  static bool is_browser_initiated_automatic_picture_in_picture_enabled_;
  static bool is_browser_verified_user_activation_keyboard_enabled_;
  static bool is_browser_verified_user_activation_mouse_enabled_;
  static bool is_buffered_bytes_consumer_limit_size_enabled_;
  static bool is_bypass_pepc_security_for_testing_enabled_;
  static bool is_cache_control_rfc_7234_parsing_enabled_;
  static bool is_cache_control_rfc_7234_parsing_metrics_enabled_;
  static bool is_cache_storage_code_cache_hint_enabled_;
  static bool is_cache_style_adjuster_enabled_;
  static bool is_call_exit_node_without_layout_object_enabled_;
  static bool is_canvas_2d_canvas_filter_enabled_;
  static bool is_canvas_2d_gpu_transfer_enabled_;
  static bool is_canvas_2d_layers_enabled_;
  static bool is_canvas_2d_layers_with_options_enabled_;
  static bool is_canvas_2d_mesh_enabled_;
  static bool is_canvas_draw_element_enabled_;
  static bool is_canvas_floating_point_enabled_;
  static bool is_canvas_global_hdr_headroom_enabled_;
  static bool is_canvas_gradient_css_color_4_enabled_;
  static bool is_canvas_hdr_enabled_;
  static bool is_canvas_text_metrics_precise_bounds_enabled_;
  static bool is_canvas_tone_mapping_enabled_;
  static bool is_canvas_uses_arc_paint_op_enabled_;
  static bool is_capability_delegation_display_capture_request_enabled_;
  static bool is_capture_controller_enabled_;
  static bool is_captured_mouse_events_enabled_;
  static bool is_captured_surface_control_enabled_;
  static bool is_captured_surface_resolution_enabled_;
  static bool is_capture_handle_enabled_;
  static bool is_caret_with_text_affinity_upstream_enabled_;
  static bool is_cct_new_rfm_push_behavior_enabled_;
  static bool is_checkable_input_type_layout_inline_enabled_;
  static bool is_check_for_canonical_position_in_idle_spell_check_enabled_;
  static bool is_check_visibility_extra_properties_enabled_;
  static bool is_clamp_word_boundary_to_content_editable_scope_enabled_;
  static bool is_clear_current_target_after_dispatch_enabled_;
  static bool is_clear_focus_within_on_subtree_removal_enabled_;
  static bool is_clear_target_only_if_in_shadow_tree_enabled_;
  static bool is_click_focus_doesnt_persist_status_bubble_enabled_;
  static bool is_clipboard_event_target_can_be_focused_element_enabled_;
  static bool is_clipboard_event_target_uses_container_node_enabled_;
  static bool is_clipboard_item_with_dom_string_support_enabled_;
  static bool is_clip_element_visible_bounds_in_local_root_enabled_;
  static bool is_clip_path_nested_raster_optimization_enabled_;
  static bool is_coalesce_selectionchange_event_enabled_;
  static bool is_coep_reflection_enabled_;
  static bool is_collapse_zero_width_space_when_reuse_item_enabled_;
  static bool is_color_input_accepts_css_colors_enabled_;
  static bool is_color_space_display_p_3_linear_enabled_;
  static bool is_color_space_predefined_linear_spaces_enabled_;
  static bool is_color_space_rec_2100_linear_enabled_;
  static bool is_command_event_not_composed_enabled_;
  static bool is_comma_separated_container_queries_enabled_;
  static bool is_composed_path_return_target_being_dispatched_enabled_;
  static bool is_composite_bg_color_animation_enabled_;
  static bool is_composite_box_shadow_animation_enabled_;
  static bool is_composite_clip_path_animation_enabled_;
  static bool is_composited_animations_cancelled_asynchronously_enabled_;
  static bool is_composited_selection_update_enabled_;
  static bool is_compositing_decision_at_animation_phase_boundaries_enabled_;
  static bool is_composition_foreground_markers_enabled_;
  static bool is_compositor_event_trigger_enabled_;
  static bool is_compositor_timeline_trigger_enabled_;
  static bool is_compression_dictionary_transport_enabled_;
  static bool is_computed_accessibility_info_enabled_;
  static bool is_compute_inline_contents_safe_retarget_enabled_;
  static bool is_compute_pressure_enabled_;
  static bool is_compute_pressure_own_contribution_estimate_enabled_;
  static bool is_connection_allowlist_enabled_;
  static bool is_consider_sub_or_super_script_ancestor_align_for_caret_selection_enabled_;
  static bool is_contacts_manager_enabled_;
  static bool is_contacts_manager_extra_properties_enabled_;
  static bool is_container_name_only_enabled_;
  static bool is_container_timing_enabled_;
  static bool is_content_index_enabled_;
  static bool is_context_menu_enabled_;
  static bool is_controlled_frame_enabled_;
  static bool is_controlled_frame_web_request_security_info_enabled_;
  static bool is_cookie_store_api_max_age_enabled_;
  static bool is_cookie_store_api_whitespace_stripping_enabled_;
  static bool is_coop_restrict_properties_enabled_;
  static bool is_correct_template_form_parsing_enabled_;
  static bool is_cors_rfc_1918_enabled_;
  static bool is_cpu_performance_enabled_;
  static bool is_crash_reporting_storage_api_enabled_;
  static bool is_create_inline_contents_exclude_out_of_flow_enabled_;
  static bool is_csp_hashes_v_1_enabled_;
  static bool is_csp_report_hash_enabled_;
  static bool is_css_accent_color_keyword_enabled_;
  static bool is_css_active_caption_maps_to_canvas_enabled_;
  static bool is_css_alpha_color_function_enabled_;
  static bool is_css_alt_counter_enabled_;
  static bool is_css_anchor_with_transforms_enabled_;
  static bool is_css_animation_iteration_composite_enabled_;
  static bool is_css_argument_grammar_enabled_;
  static bool is_css_at_rule_counter_style_image_symbols_enabled_;
  static bool is_css_at_rule_counter_style_speak_as_descriptor_enabled_;
  static bool is_css_background_clip_border_area_enabled_;
  static bool is_css_border_shape_enabled_;
  static bool is_css_calc_simplification_and_serialization_enabled_;
  static bool is_css_caret_animation_enabled_;
  static bool is_css_caret_shape_enabled_;
  static bool is_css_case_sensitive_selector_enabled_;
  static bool is_css_ch_unit_spec_compliant_fallback_enabled_;
  static bool is_css_color_typed_om_enabled_;
  static bool is_css_container_progress_notation_enabled_;
  static bool is_css_container_style_queries_range_enabled_;
  static bool is_css_contrast_color_enabled_;
  static bool is_css_corners_shorthand_enabled_;
  static bool is_css_counter_reset_reversed_enabled_;
  static bool is_css_cross_fade_enabled_;
  static bool is_css_custom_media_enabled_;
  static bool is_css_dynamic_range_limit_enabled_;
  static bool is_css_enumerated_custom_properties_enabled_;
  static bool is_css_font_family_serialization_enabled_;
  static bool is_css_font_size_adjust_enabled_;
  static bool is_css_functions_enabled_;
  static bool is_css_gap_decoration_enabled_;
  static bool is_css_grid_gap_suppression_enabled_;
  static bool is_css_grid_lanes_layout_enabled_;
  static bool is_css_hanging_punctuation_enabled_;
  static bool is_css_hex_alpha_color_enabled_;
  static bool is_css_ident_function_enabled_;
  static bool is_css_image_animation_enabled_;
  static bool is_css_inherit_function_enabled_;
  static bool is_css_keyframes_rule_length_enabled_;
  static bool is_css_lang_extended_ranges_enabled_;
  static bool is_css_layout_api_enabled_;
  static bool is_css_letter_and_word_spacing_percentage_enabled_;
  static bool is_css_light_dark_image_enabled_;
  static bool is_css_line_clamp_enabled_;
  static bool is_css_line_clamp_line_breaking_ellipsis_enabled_;
  static bool is_css_line_clamp_lines_and_height_enabled_;
  static bool is_css_list_counter_accounting_enabled_;
  static bool is_css_logical_combination_pseudo_enabled_;
  static bool is_css_marker_nested_pseudo_element_enabled_;
  static bool is_css_media_progress_notation_enabled_;
  static bool is_css_mixins_enabled_;
  static bool is_css_nested_pseudo_elements_enabled_;
  static bool is_cssom_get_computed_style_pseudo_element_requires_colon_enabled_;
  static bool is_css_overscroll_behavior_chain_enabled_;
  static bool is_css_paint_api_arguments_enabled_;
  static bool is_css_parser_ignore_charset_for_urls_enabled_;
  static bool is_css_polygon_rounding_enabled_;
  static bool is_css_position_sticky_static_scroll_position_enabled_;
  static bool is_css_progress_notation_enabled_;
  static bool is_css_pseudo_column_enabled_;
  static bool is_css_pseudo_element_backdrop_enabled_;
  static bool is_css_pseudo_element_interface_enabled_;
  static bool is_css_pseudo_element_view_transitions_enabled_;
  static bool is_css_pseudo_has_slotted_enabled_;
  static bool is_css_pseudo_playing_paused_enabled_;
  static bool is_css_pseudo_scroll_buttons_enabled_;
  static bool is_css_pseudo_scroll_markers_enabled_;
  static bool is_css_random_function_enabled_;
  static bool is_css_random_function_typed_om_enabled_;
  static bool is_css_resize_auto_enabled_;
  static bool is_css_resource_integrity_enforcement_enabled_;
  static bool is_css_revert_rule_enabled_;
  static bool is_css_ruby_overhang_enabled_;
  static bool is_css_safe_printable_inset_enabled_;
  static bool is_css_scopeified_parent_pseudo_class_enabled_;
  static bool is_css_scope_import_enabled_;
  static bool is_css_scrolled_container_queries_enabled_;
  static bool is_css_scroll_initial_target_enabled_;
  static bool is_css_scroll_marker_group_modes_enabled_;
  static bool is_css_scroll_marker_target_before_after_enabled_;
  static bool is_css_scroll_snap_change_event_enabled_;
  static bool is_css_scroll_snap_changing_event_enabled_;
  static bool is_css_scroll_snap_event_constructor_exposed_enabled_;
  static bool is_css_scroll_snap_events_enabled_;
  static bool is_css_scroll_target_group_enabled_;
  static bool is_css_scroll_target_group_aria_current_enabled_;
  static bool is_css_shape_ellipse_circle_position_serialization_enabled_;
  static bool is_css_shape_outside_path_and_shape_support_enabled_;
  static bool is_css_shape_outside_rect_and_xywh_support_enabled_;
  static bool is_css_style_sheet_init_base_url_enabled_;
  static bool is_css_supports_at_rule_function_enabled_;
  static bool is_css_supports_for_import_rules_enabled_;
  static bool is_css_supports_named_feature_function_enabled_;
  static bool is_css_system_accent_color_enabled_;
  static bool is_css_text_align_match_parent_enabled_;
  static bool is_css_text_decoration_skip_ink_all_enabled_;
  static bool is_css_text_decoration_skip_spaces_enabled_;
  static bool is_css_text_fit_enabled_;
  static bool is_css_text_fit_reshaping_enabled_;
  static bool is_css_text_indent_enabled_;
  static bool is_css_text_indent_as_primitive_enabled_;
  static bool is_css_text_spacing_enabled_;
  static bool is_css_text_transform_full_size_kana_enabled_;
  static bool is_css_text_transform_full_width_enabled_;
  static bool is_css_text_transform_multi_keyword_enabled_;
  static bool is_css_timeline_scope_all_enabled_;
  static bool is_css_timeline_scope_global_enabled_;
  static bool is_css_typed_arithmetic_enabled_;
  static bool is_css_url_request_modifiers_enabled_;
  static bool is_css_user_select_contain_enabled_;
  static bool is_css_user_valid_and_user_invalid_for_radio_enabled_;
  static bool is_css_video_dynamic_range_media_queries_enabled_;
  static bool is_css_view_transition_auto_name_enabled_;
  static bool is_custom_elements_disable_formatting_fixups_enabled_;
  static bool is_customizable_combobox_enabled_;
  static bool is_customizable_select_multiple_popup_enabled_;
  static bool is_custom_scrollbar_apply_minimum_thumb_length_enabled_;
  static bool is_database_enabled_;
  static bool is_date_time_local_arabic_comma_workaround_enabled_;
  static bool is_declarative_css_modules_enabled_;
  static bool is_declarative_css_modules_style_tag_enabled_;
  static bool is_decouple_computed_border_width_from_style_enabled_;
  static bool is_decouple_resolved_column_rule_width_from_style_enabled_;
  static bool is_delegates_focus_text_control_input_fix_enabled_;
  static bool is_delete_text_in_content_editable_before_removing_children_enabled_;
  static bool is_deprecate_unload_opt_out_enabled_;
  static bool is_desktop_capture_disable_local_echo_control_enabled_;
  static bool is_desktop_pw_as_additional_windowing_controls_enabled_;
  static bool is_desktop_pw_as_additional_windowing_controls_on_move_enabled_;
  static bool is_device_attributes_enabled_;
  static bool is_device_orientation_request_permission_enabled_;
  static bool is_device_posture_enabled_;
  static bool is_dialog_close_when_open_removed_enabled_;
  static bool is_dialog_new_focus_behavior_enabled_;
  static bool is_digital_goods_enabled_;
  static bool is_digital_goods_v_2_1_enabled_;
  static bool is_direct_sockets_enabled_;
  static bool is_direct_sockets_in_service_workers_enabled_;
  static bool is_direct_sockets_in_shared_workers_enabled_;
  static bool is_disable_anchor_center_on_align_justify_items_enabled_;
  static bool is_disable_different_origin_subframe_dialog_suppression_enabled_;
  static bool is_disable_ellipsis_when_scrolled_enabled_;
  static bool is_disable_reduce_accept_language_enabled_;
  static bool is_disable_remove_format_for_plain_text_only_editable_div_enabled_;
  static bool is_disallow_disconnected_area_navigation_enabled_;
  static bool is_disallow_picker_for_readonly_inputs_enabled_;
  static bool is_disconnect_websocket_on_bf_cache_enabled_;
  static bool is_dispatch_hidden_visibility_transitions_enabled_;
  static bool is_dispatch_selectionchange_event_per_element_enabled_;
  static bool is_display_contents_focusable_enabled_;
  static bool is_display_cutout_api_enabled_;
  static bool is_document_active_view_transition_enabled_;
  static bool is_document_cookie_enabled_;
  static bool is_document_domain_enabled_;
  static bool is_document_isolation_policy_enabled_;
  static bool is_document_open_iframe_unload_events_enabled_;
  static bool is_document_open_origin_alias_removal_enabled_;
  static bool is_document_open_sandbox_inheritance_removal_enabled_;
  static bool is_document_patching_enabled_;
  static bool is_document_picture_in_picture_api_enabled_;
  static bool is_document_picture_in_picture_prefer_initial_placement_enabled_;
  static bool is_document_picture_in_picture_user_activation_enabled_;
  static bool is_document_policy_document_domain_enabled_;
  static bool is_document_policy_expect_no_linked_resources_enabled_;
  static bool is_document_policy_include_js_call_stacks_in_crash_reports_enabled_;
  static bool is_document_policy_in_dedicated_worker_enabled_;
  static bool is_document_policy_negotiation_enabled_;
  static bool is_document_policy_network_efficiency_guardrails_enabled_;
  static bool is_document_policy_sync_xhr_enabled_;
  static bool is_document_write_enabled_;
  static bool is_dom_activate_bubbles_inheritance_enabled_;
  static bool is_dont_leak_shadow_trees_in_drag_events_enabled_;
  static bool is_edit_context_assignment_as_per_spec_enabled_;
  static bool is_edit_context_handle_text_or_selection_update_during_composition_enabled_;
  static bool is_edit_emoji_tag_sequence_enabled_;
  static bool is_editing_line_movement_with_ruby_fix_enabled_;
  static bool is_element_capture_enabled_;
  static bool is_element_inner_text_handle_first_line_style_enabled_;
  static bool is_element_internals_behaviors_enabled_;
  static bool is_element_specific_read_only_constraint_validation_enabled_;
  static bool is_email_verification_protocol_enabled_;
  static bool is_emoji_monochrome_rendering_enabled_;
  static bool is_endpoint_inclusive_commit_styles_enabled_;
  static bool is_enforce_anonymity_exposure_enabled_;
  static bool is_enter_in_open_shadow_roots_enabled_;
  static bool is_entropy_ignored_for_first_video_frame_lcp_enabled_;
  static bool is_event_pseudo_target_property_enabled_;
  static bool is_event_timing_interaction_count_enabled_;
  static bool is_event_timing_target_selector_enabled_;
  static bool is_event_trigger_enabled_;
  static bool is_experimental_content_security_policy_features_enabled_;
  static bool is_experimental_js_profiler_markers_enabled_;
  static bool is_experimental_machine_learning_neural_network_enabled_;
  static bool is_experimental_policies_enabled_;
  static bool is_expose_css_font_feature_values_rule_enabled_;
  static bool is_expose_render_time_non_tao_delayed_image_enabled_;
  static bool is_extended_shape_cache_enabled_;
  static bool is_extended_text_metrics_enabled_;
  static bool is_external_popup_menu_click_event_enabled_;
  static bool is_eye_dropper_api_enabled_;
  static bool is_face_detector_enabled_;
  static bool is_fast_position_iterator_enabled_;
  static bool is_fed_cm_enabled_;
  static bool is_fed_cm_autofill_enabled_;
  static bool is_fed_cm_delegation_enabled_;
  static bool is_fed_cm_error_attribute_enabled_;
  static bool is_fed_cm_id_p_registration_enabled_;
  static bool is_fed_cm_lightweight_mode_enabled_;
  static bool is_fed_cm_multiple_identity_providers_enabled_;
  static bool is_fed_cm_navigation_interception_enabled_;
  static bool is_fed_cm_non_string_token_enabled_;
  static bool is_fenced_frames_enabled_;
  static bool is_fenced_frames_api_changes_enabled_;
  static bool is_fenced_frames_default_mode_enabled_;
  static bool is_fenced_frames_local_unpartitioned_data_access_enabled_;
  static bool is_fetch_body_bytes_enabled_;
  static bool is_fetch_later_api_enabled_;
  static bool is_fetch_retry_enabled_;
  static bool is_fetch_upload_streaming_enabled_;
  static bool is_file_handling_enabled_;
  static bool is_file_handling_icons_enabled_;
  static bool is_file_system_enabled_;
  static bool is_file_system_access_enabled_;
  static bool is_file_system_access_api_experimental_enabled_;
  static bool is_file_system_access_get_cloud_identifiers_enabled_;
  static bool is_file_system_access_local_enabled_;
  static bool is_file_system_access_locking_scheme_enabled_;
  static bool is_file_system_access_origin_private_enabled_;
  static bool is_file_system_access_revoke_read_on_remove_enabled_;
  static bool is_file_system_access_write_mode_enabled_;
  static bool is_file_system_observer_enabled_;
  static bool is_file_system_observer_unobserve_enabled_;
  static bool is_filterable_select_enabled_;
  static bool is_filter_container_level_styles_enabled_;
  static bool is_filtering_primitives_enabled_;
  static bool is_find_first_misspelling_end_when_non_editable_enabled_;
  static bool is_first_line_on_list_item_enabled_;
  static bool is_first_line_text_metrics_enabled_;
  static bool is_fix_html_form_control_element_is_read_only_enabled_;
  static bool is_fix_justify_query_command_value_enabled_;
  static bool is_fix_linebreak_for_pre_tag_enabled_;
  static bool is_fix_map_element_empty_name_bug_enabled_;
  static bool is_fix_marker_suppression_for_appearance_auto_enabled_;
  static bool is_fix_next_position_calculation_in_insert_list_enabled_;
  static bool is_fix_strikethrough_toggle_in_empty_content_editable_enabled_;
  static bool is_fix_visual_rect_remote_viewport_transform_enabled_;
  static bool is_fledge_enabled_;
  static bool is_fledge_auction_deal_support_enabled_;
  static bool is_fledge_bidding_and_auction_server_api_enabled_;
  static bool is_fledge_bidding_and_auction_server_api_multi_seller_enabled_;
  static bool is_fledge_clickiness_enabled_;
  static bool is_fledge_custom_max_auction_ad_components_enabled_;
  static bool is_fledge_deprecated_render_url_replacements_enabled_;
  static bool is_fledge_direct_from_seller_signals_header_ad_slot_enabled_;
  static bool is_fledge_direct_from_seller_signals_web_bundles_enabled_;
  static bool is_fledge_multi_bid_enabled_;
  static bool is_fledge_private_model_training_enabled_;
  static bool is_fledge_real_time_reporting_enabled_;
  static bool is_fledge_seller_nonce_enabled_;
  static bool is_fledge_seller_script_execution_mode_enabled_;
  static bool is_fledge_trusted_signals_k_vv_1_creative_scanning_enabled_;
  static bool is_fledge_trusted_signals_k_vv_2_contextual_data_enabled_;
  static bool is_fledge_trusted_signals_k_vv_2_support_enabled_;
  static bool is_flex_wrap_balance_enabled_;
  static bool is_focusgroup_enabled_;
  static bool is_focusgroup_grid_enabled_;
  static bool is_font_access_enabled_;
  static bool is_font_data_service_enabled_;
  static bool is_font_fallback_for_tab_size_enabled_;
  static bool is_font_family_postscript_matching_ct_migration_enabled_;
  static bool is_font_family_style_matching_ct_migration_enabled_;
  static bool is_font_feature_settings_descriptor_enabled_;
  static bool is_font_format_avar_2_enabled_;
  static bool is_font_language_override_enabled_;
  static bool is_font_match_aliases_as_last_resort_enabled_;
  static bool is_font_style_oblique_zero_degree_as_normal_enabled_;
  static bool is_font_variation_settings_descriptor_enabled_;
  static bool is_forced_colors_enabled_;
  static bool is_force_eager_measure_memory_enabled_;
  static bool is_force_reduce_motion_enabled_;
  static bool is_fractional_scroll_offsets_enabled_;
  static bool is_fragmented_oof_in_cb_enabled_;
  static bool is_freeze_frames_on_visibility_enabled_;
  static bool is_gamepad_multitouch_enabled_;
  static bool is_gamepad_raw_input_change_event_enabled_;
  static bool is_gamepad_window_event_handlers_enabled_;
  static bool is_geolocation_element_enabled_;
  static bool is_geometry_mapper_singular_transform_fix_enabled_;
  static bool is_geometry_utils_enabled_;
  static bool is_geometry_utils_for_css_pseudo_element_enabled_;
  static bool is_get_all_screens_media_enabled_;
  static bool is_get_computed_style_outside_flat_tree_enabled_;
  static bool is_get_display_media_enabled_;
  static bool is_get_display_media_requires_user_activation_enabled_;
  static bool is_get_display_media_window_audio_capture_enabled_;
  static bool is_get_elements_by_name_only_html_elements_enabled_;
  static bool is_get_user_media_echo_cancellation_modes_enabled_;
  static bool is_group_effect_enabled_;
  static bool is_handle_deletion_at_start_and_end_boundary_containing_hidden_element_enabled_;
  static bool is_handle_disconnected_selection_during_dom_changes_enabled_;
  static bool is_handle_invalid_mask_image_with_backdrop_filter_enabled_;
  static bool is_handle_shadow_dom_in_substring_util_enabled_;
  static bool is_handwriting_recognition_enabled_;
  static bool is_has_ua_visual_transition_enabled_;
  static bool is_heading_offset_enabled_;
  static bool is_hide_video_controls_when_unneeded_enabled_;
  static bool is_highlights_from_point_enabled_;
  static bool is_hit_test_border_radius_for_stacking_context_enabled_;
  static bool is_hit_test_container_transform_state_for_preserve_3d_enabled_;
  static bool is_href_translate_enabled_;
  static bool is_hsts_top_level_navigations_only_enabled_;
  static bool is_html_adoption_algorithm_new_steps_enabled_;
  static bool is_html_command_actions_v_2_enabled_;
  static bool is_html_command_element_removal_enabled_;
  static bool is_html_command_for_scroll_commands_enabled_;
  static bool is_html_element_scroll_parent_enabled_;
  static bool is_html_image_element_actual_natural_size_enabled_;
  static bool is_html_input_element_drop_webkit_clear_button_enabled_;
  static bool is_html_interest_for_interest_button_pseudo_enabled_;
  static bool is_html_link_element_attribute_value_changes_enabled_;
  static bool is_html_parser_yield_and_delay_often_for_testing_enabled_;
  static bool is_html_parser_yield_by_user_timing_enabled_;
  static bool is_html_printing_artifact_annotations_enabled_;
  static bool is_html_processing_instruction_enabled_;
  static bool is_icu_capitalization_enabled_;
  static bool is_ignore_letter_spacing_in_cursive_scripts_enabled_;
  static bool is_image_data_pixel_format_enabled_;
  static bool is_image_document_use_layout_width_enabled_;
  static bool is_image_srcset_reselection_enabled_;
  static bool is_implicit_root_scroller_enabled_;
  static bool is_improved_source_retargeting_enabled_;
  static bool is_incoming_call_notifications_enabled_;
  static bool is_inert_element_non_editable_enabled_;
  static bool is_infinite_cull_rect_enabled_;
  static bool is_inherit_user_modify_without_contenteditable_enabled_;
  static bool is_inline_block_line_navigation_enabled_;
  static bool is_inline_script_cache_hint_enabled_;
  static bool is_inner_html_parser_fastpath_log_failure_enabled_;
  static bool is_input_event_data_transfer_for_insert_cmd_enabled_;
  static bool is_input_events_delete_non_collapsed_selection_enabled_;
  static bool is_input_in_select_enabled_;
  static bool is_input_multiple_fields_ui_enabled_;
  static bool is_insert_blockquote_before_outer_block_enabled_;
  static bool is_installed_app_enabled_;
  static bool is_install_element_enabled_;
  static bool is_install_on_device_speech_recognition_enabled_;
  static bool is_integrity_policy_script_enabled_;
  static bool is_interest_events_non_composed_enabled_;
  static bool is_interest_groups_in_shared_storage_worklet_enabled_;
  static bool is_intersection_observer_composited_animations_force_main_frames_enabled_;
  static bool is_inverted_colors_enabled_;
  static bool is_invisible_svg_animation_throttling_enabled_;
  static bool is_java_script_compile_hints_per_function_magic_runtime_enabled_;
  static bool is_java_script_source_phase_imports_enabled_;
  static bool is_keyboard_accessible_tooltip_enabled_;
  static bool is_key_system_track_configuration_encryption_scheme_enabled_;
  static bool is_label_interactive_content_check_before_handler_enabled_;
  static bool is_lang_attribute_aware_form_control_ui_enabled_;
  static bool is_language_detection_api_enabled_;
  static bool is_language_detection_api_for_workers_enabled_;
  static bool is_layout_box_rect_getters_use_fragments_enabled_;
  static bool is_layout_ignore_margins_for_sticky_enabled_;
  static bool is_layout_image_empty_natural_size_before_size_available_enabled_;
  static bool is_layout_table_cell_alignment_safe_enabled_;
  static bool is_lazy_image_conformant_load_event_timing_enabled_;
  static bool is_lazy_load_video_and_audio_enabled_;
  static bool is_left_click_to_handle_suggestion_enabled_;
  static bool is_light_dismiss_from_click_enabled_;
  static bool is_link_blur_improvement_enabled_;
  static bool is_list_owner_must_have_css_box_enabled_;
  static bool is_local_network_access_non_secure_context_allowed_enabled_;
  static bool is_local_network_access_permission_policy_enabled_;
  static bool is_local_network_access_split_permissions_enabled_;
  static bool is_local_network_access_web_rtc_enabled_;
  static bool is_locked_mode_enabled_;
  static bool is_logical_start_of_line_block_fallback_enabled_;
  static bool is_login_element_enabled_;
  static bool is_long_animation_frame_source_char_position_enabled_;
  static bool is_long_animation_frame_source_line_column_enabled_;
  static bool is_long_animation_frame_source_line_column_interface_enabled_;
  static bool is_long_animation_frame_style_duration_enabled_;
  static bool is_long_press_link_select_text_enabled_;
  static bool is_long_task_from_long_animation_frame_enabled_;
  static bool is_mac_character_fallback_cache_enabled_;
  static bool is_mac_disable_ctrl_home_end_enabled_;
  static bool is_machine_learning_neural_network_enabled_;
  static bool is_mac_system_clipboard_permission_check_enabled_;
  static bool is_managed_configuration_enabled_;
  static bool is_manual_text_enabled_;
  static bool is_margin_trim_enabled_;
  static bool is_mask_deserialization_time_for_cross_origin_messages_enabled_;
  static bool is_mathml_operator_rtl_mirroring_enabled_;
  static bool is_mathml_serialization_on_copy_enabled_;
  static bool is_mathml_skip_mtr_tag_in_ancestor_wrapping_enabled_;
  static bool is_measure_memory_enabled_;
  static bool is_media_capabilities_encoding_info_enabled_;
  static bool is_media_capabilities_spatial_audio_enabled_;
  static bool is_media_capture_enabled_;
  static bool is_media_capture_background_blur_enabled_;
  static bool is_media_capture_camera_controls_enabled_;
  static bool is_media_capture_configuration_change_enabled_;
  static bool is_media_capture_voice_isolation_enabled_;
  static bool is_media_controls_expand_gesture_enabled_;
  static bool is_media_controls_overlay_play_button_enabled_;
  static bool is_media_element_volume_greater_than_one_enabled_;
  static bool is_media_engagement_bypass_autoplay_policies_enabled_;
  static bool is_media_latency_hint_enabled_;
  static bool is_media_playback_while_not_visible_permission_policy_enabled_;
  static bool is_media_query_navigation_controls_enabled_;
  static bool is_media_session_enabled_;
  static bool is_media_session_chapter_information_enabled_;
  static bool is_media_source_experimental_enabled_;
  static bool is_media_source_extensions_for_webcodecs_enabled_;
  static bool is_media_stream_track_transfer_enabled_;
  static bool is_media_stream_track_web_speech_enabled_;
  static bool is_memory_consumer_for_ng_shape_cache_enabled_;
  static bool is_menu_elements_enabled_;
  static bool is_merge_fixed_layers_enabled_;
  static bool is_merge_sticky_layers_enabled_;
  static bool is_message_port_close_event_enabled_;
  static bool is_middle_click_autoscroll_enabled_;
  static bool is_mixed_content_autoupgrades_use_is_mixed_content_restricted_in_frame_enabled_;
  static bool is_mobile_layout_theme_enabled_;
  static bool is_modify_paragraph_cross_editingoundary_enabled_;
  static bool is_module_preload_referrer_enabled_;
  static bool is_module_preload_style_json_enabled_;
  static bool is_move_ending_selection_to_list_child_enabled_;
  static bool is_multicol_column_wrapping_enabled_;
  static bool is_navigate_event_add_handler_on_precommit_enabled_;
  static bool is_navigate_event_clear_on_restore_enabled_;
  static bool is_navigate_event_defer_cross_document_commit_enabled_;
  static bool is_navigation_event_timing_enabled_;
  static bool is_navigation_id_enabled_;
  static bool is_navigator_content_utils_enabled_;
  static bool is_net_info_constant_type_enabled_;
  static bool is_net_info_downlink_max_enabled_;
  static bool is_new_html_setting_methods_enabled_;
  static bool is_no_extend_selection_to_user_select_none_out_of_flow_enabled_;
  static bool is_no_font_antialiasing_enabled_;
  static bool is_no_idle_encoding_for_web_tests_enabled_;
  static bool is_non_empty_blockquotes_on_outdenting_enabled_;
  static bool is_non_empty_visible_text_selection_for_text_fragment_enabled_;
  static bool is_non_standard_appearance_value_slider_vertical_enabled_;
  static bool is_normalize_line_endings_in_insert_text_enabled_;
  static bool is_normalize_nbsp_for_paste_and_drop_enabled_;
  static bool is_notification_constructor_enabled_;
  static bool is_notification_content_image_enabled_;
  static bool is_notifications_enabled_;
  static bool is_notification_triggers_enabled_;
  static bool is_number_input_full_width_chars_enabled_;
  static bool is_off_main_thread_css_paint_enabled_;
  static bool is_offscreen_canvas_get_context_attributes_enabled_;
  static bool is_offset_path_transform_update_fix_enabled_;
  static bool is_omit_blur_event_on_element_removal_enabled_;
  static bool is_on_device_web_speech_available_enabled_;
  static bool is_on_device_web_speech_quality_enabled_;
  static bool is_opaque_range_enabled_;
  static bool is_open_popover_invoker_restrict_to_same_tree_scope_enabled_;
  static bool is_orientation_event_enabled_;
  static bool is_origin_api_enabled_;
  static bool is_origin_isolation_header_enabled_;
  static bool is_origin_policy_enabled_;
  static bool is_origin_trials_sample_api_enabled_;
  static bool is_origin_trials_sample_api_browser_read_write_enabled_;
  static bool is_origin_trials_sample_api_dependent_enabled_;
  static bool is_origin_trials_sample_api_deprecation_enabled_;
  static bool is_origin_trials_sample_api_expiry_grace_period_enabled_;
  static bool is_origin_trials_sample_api_expiry_grace_period_third_party_enabled_;
  static bool is_origin_trials_sample_api_implied_enabled_;
  static bool is_origin_trials_sample_api_invalid_os_enabled_;
  static bool is_origin_trials_sample_api_navigation_enabled_;
  static bool is_origin_trials_sample_api_persistent_expiry_grace_period_enabled_;
  static bool is_origin_trials_sample_api_persistent_feature_enabled_;
  static bool is_origin_trials_sample_api_persistent_invalid_os_enabled_;
  static bool is_origin_trials_sample_api_persistent_third_party_deprecation_feature_enabled_;
  static bool is_origin_trials_sample_api_third_party_enabled_;
  static bool is_outline_draw_auto_style_zero_width_enabled_;
  static bool is_overlay_global_rule_removal_enabled_;
  static bool is_overlay_property_enabled_;
  static bool is_overscroll_gestures_enabled_;
  static bool is_page_popup_enabled_;
  static bool is_page_popup_copy_paste_enabled_;
  static bool is_page_reveal_event_enabled_;
  static bool is_page_swap_event_enabled_;
  static bool is_paint_holding_for_iframes_enabled_;
  static bool is_paint_offset_translation_for_composited_enabled_;
  static bool is_paint_timing_mixin_enabled_;
  static bool is_paint_under_invalidation_checking_enabled_;
  static bool is_parakeet_enabled_;
  static bool is_partial_completion_not_allowed_in_move_paragraphs_enabled_;
  static bool is_partition_visited_link_database_with_self_links_enabled_;
  static bool is_password_reveal_enabled_;
  static bool is_payment_app_enabled_;
  static bool is_payment_link_detection_enabled_;
  static bool is_payment_method_change_event_enabled_;
  static bool is_payment_request_enabled_;
  static bool is_performance_manager_instrumentation_enabled_;
  static bool is_performance_mark_custom_user_timing_from_subframe_enabled_;
  static bool is_performance_mark_feature_usage_enabled_;
  static bool is_performance_navigation_timing_confidence_enabled_;
  static bool is_periodic_background_sync_enabled_;
  static bool is_per_method_can_make_payment_quota_enabled_;
  static bool is_permissions_request_revoke_enabled_;
  static bool is_placeholder_visibility_enabled_;
  static bool is_p_na_cl_enabled_;
  static bool is_pointer_event_device_id_enabled_;
  static bool is_pointer_lock_on_android_enabled_;
  static bool is_pointer_raw_update_only_in_secure_context_enabled_;
  static bool is_popover_hint_new_behavior_enabled_;
  static bool is_position_outside_tab_span_check_sibling_node_enabled_;
  static bool is_position_visibility_ignore_non_clip_ancestors_enabled_;
  static bool is_potential_permissions_policy_reporting_enabled_;
  static bool is_precise_memory_info_enabled_;
  static bool is_prefer_default_scrollbar_styles_enabled_;
  static bool is_prefer_non_composited_scrolling_enabled_;
  static bool is_preferred_audio_output_devices_enabled_;
  static bool is_prefers_reduced_data_enabled_;
  static bool is_preload_link_rel_data_urls_enabled_;
  static bool is_prerender_2_enabled_;
  static bool is_prerender_2_cross_origin_iframes_enabled_;
  static bool is_prerender_activation_by_form_submission_enabled_;
  static bool is_prerender_until_script_enabled_;
  static bool is_presentation_enabled_;
  static bool is_preserve_drop_effect_enabled_;
  static bool is_prevent_undo_if_not_editable_enabled_;
  static bool is_private_aggregation_api_error_reporting_enabled_;
  static bool is_private_aggregation_api_max_contributions_enabled_;
  static bool is_private_network_access_null_ip_address_enabled_;
  static bool is_private_state_tokens_enabled_;
  static bool is_private_state_tokens_always_allow_issuance_enabled_;
  static bool is_profiler_api_enabled_;
  static bool is_profiler_api_for_dedicated_worker_enabled_;
  static bool is_programmatic_scroll_promise_enabled_;
  static bool is_progress_max_is_positive_enabled_;
  static bool is_propagate_overscroll_behavior_from_root_enabled_;
  static bool is_pseudo_elements_focusable_enabled_;
  static bool is_pseudo_elements_hit_testable_enabled_;
  static bool is_pseudo_elements_hoverable_enabled_;
  static bool is_push_message_data_bytes_enabled_;
  static bool is_push_messaging_enabled_;
  static bool is_push_messaging_subscription_change_enabled_;
  static bool is_quota_exceeded_error_update_enabled_;
  static bool is_quote_first_line_style_enabled_;
  static bool is_raster_inducing_scroll_enabled_;
  static bool is_readable_stream_byob_reader_read_min_option_enabled_;
  static bool is_read_clipboard_data_on_clipboard_item_get_type_enabled_;
  static bool is_reading_flow_with_slots_enabled_;
  static bool is_recheck_parent_during_node_vector_insertion_enabled_;
  static bool is_record_same_document_presentation_time_once_enabled_;
  static bool is_reduce_accept_language_enabled_;
  static bool is_reduce_user_agent_data_linux_platform_version_enabled_;
  static bool is_reduce_user_agent_minor_version_enabled_;
  static bool is_region_capture_enabled_;
  static bool is_related_website_partition_api_enabled_;
  static bool is_rel_opener_bcg_dependency_hint_enabled_;
  static bool is_remote_playback_enabled_;
  static bool is_remote_playback_backend_enabled_;
  static bool is_remove_charset_auto_detection_for_iso_2022_jp_enabled_;
  static bool is_remove_children_in_replace_children_enabled_;
  static bool is_remove_collapsed_placeholder_for_content_editable_enabled_;
  static bool is_remove_dangling_markup_in_target_enabled_;
  static bool is_remove_data_url_in_svg_use_enabled_;
  static bool is_remove_format_filter_background_color_enabled_;
  static bool is_remove_non_allowlisted_create_event_enabled_;
  static bool is_remove_scroll_node_workaround_enabled_;
  static bool is_remove_selection_canonicalization_in_move_paragraph_enabled_;
  static bool is_remove_visible_selection_in_dom_selection_enabled_;
  static bool is_render_blocking_full_frame_rate_enabled_;
  static bool is_render_blocking_status_enabled_;
  static bool is_render_priority_attribute_enabled_;
  static bool is_report_first_frame_time_as_render_time_enabled_;
  static bool is_report_layout_shift_rects_in_css_pixels_enabled_;
  static bool is_request_is_reload_navigation_enabled_;
  static bool is_request_main_frame_after_first_video_frame_enabled_;
  static bool is_resolve_var_styles_on_copy_enabled_;
  static bool is_resource_timing_content_encoding_enabled_;
  static bool is_resource_timing_content_type_enabled_;
  static bool is_resource_timing_initiator_enabled_;
  static bool is_resource_timing_use_cors_for_body_sizes_enabled_;
  static bool is_respect_overscroll_behavior_for_scroll_bubbling_enabled_;
  static bool is_responsive_iframes_enabled_;
  static bool is_restrict_gamepad_access_enabled_;
  static bool is_restrict_own_audio_enabled_;
  static bool is_root_scrollbar_follows_browser_theme_enabled_;
  static bool is_route_matching_enabled_;
  static bool is_rtc_always_negotiate_data_channels_enabled_;
  static bool is_rtc_audio_jitter_buffer_max_packets_enabled_;
  static bool is_rtc_data_channel_priority_enabled_;
  static bool is_rtc_diagnostic_logging_enabled_;
  static bool is_rtc_encoded_frame_audio_level_enabled_;
  static bool is_rtc_encoded_frame_set_metadata_enabled_;
  static bool is_rtc_encoded_frame_timestamps_enabled_;
  static bool is_rtc_encoded_video_frame_additional_metadata_enabled_;
  static bool is_rtc_jitter_buffer_target_enabled_;
  static bool is_rtc_legacy_callback_based_get_stats_enabled_;
  static bool is_rtc_rtp_encoding_parameters_codec_enabled_;
  static bool is_rtc_rtp_scale_resolution_down_to_enabled_;
  static bool is_rtc_rtp_script_transform_enabled_;
  static bool is_rtc_rtp_transport_enabled_;
  static bool is_rtc_stats_relative_packet_arrival_delay_enabled_;
  static bool is_rtc_svc_scalability_mode_enabled_;
  static bool is_run_microtask_before_xml_script_enabled_;
  static bool is_run_snapshot_post_layout_state_steps_enabled_;
  static bool is_sanitizer_api_enabled_;
  static bool is_scoped_custom_element_registry_enabled_;
  static bool is_scoped_view_transitions_enabled_;
  static bool is_screen_detailed_hdr_headroom_enabled_;
  static bool is_script_based_on_unicode_block_enabled_;
  static bool is_scripted_speech_recognition_enabled_;
  static bool is_scripted_speech_synthesis_enabled_;
  static bool is_scroll_anchor_priority_candidate_subtree_enabled_;
  static bool is_scroll_anchor_serialization_use_parent_for_text_node_enabled_;
  static bool is_scrollbar_color_enabled_;
  static bool is_scrollbar_gutter_bug_fix_enabled_;
  static bool is_scrollbar_width_enabled_;
  static bool is_scroll_into_view_nearest_enabled_;
  static bool is_scroll_into_view_root_frame_viewport_bug_fix_enabled_;
  static bool is_scroll_timeline_current_time_enabled_;
  static bool is_scroll_timeline_named_range_scroll_enabled_;
  static bool is_scroll_top_left_interop_enabled_;
  static bool is_scroll_to_text_fragment_unique_fragments_enabled_;
  static bool is_search_text_highlight_pseudo_enabled_;
  static bool is_secure_payment_confirmation_enabled_;
  static bool is_secure_payment_confirmation_availability_api_enabled_;
  static bool is_secure_payment_confirmation_capabilities_enabled_;
  static bool is_secure_payment_confirmation_debug_enabled_;
  static bool is_secure_payment_confirmation_opt_out_enabled_;
  static bool is_select_audio_output_enabled_;
  static bool is_selectedcontentelement_attribute_enabled_;
  static bool is_selectedcontent_multiple_enabled_;
  static bool is_selectedcontent_spec_enabled_;
  static bool is_selection_and_focused_visible_position_match_enabled_;
  static bool is_selection_collapsed_direction_none_enabled_;
  static bool is_selection_focus_affinity_enabled_;
  static bool is_selection_handle_with_bottom_clipped_enabled_;
  static bool is_selection_remove_range_not_found_error_enabled_;
  static bool is_selection_set_base_and_extent_non_null_node_enabled_;
  static bool is_selection_to_string_skips_user_select_none_enabled_;
  static bool is_selection_update_only_after_autoscroll_enabled_;
  static bool is_selection_update_to_initial_selection_in_listify_enabled_;
  static bool is_selective_clipboard_format_read_enabled_;
  static bool is_selective_permissions_intervention_enabled_;
  static bool is_select_remove_overflow_hidden_enabled_;
  static bool is_send_beacon_throw_for_blob_with_non_simple_type_enabled_;
  static bool is_send_slot_change_signal_after_node_inserted_enabled_;
  static bool is_sensor_extra_classes_enabled_;
  static bool is_separate_defer_module_script_tasks_enabled_;
  static bool is_serial_enabled_;
  static bool is_serialize_view_transition_state_in_spa_enabled_;
  static bool is_serial_port_connected_enabled_;
  static bool is_service_worker_background_sync_in_dedicated_worker_enabled_;
  static bool is_service_worker_client_lifecycle_state_enabled_;
  static bool is_service_worker_in_dedicated_worker_enabled_;
  static bool is_service_worker_static_router_timing_info_enabled_;
  static bool is_set_default_drop_effect_enabled_;
  static bool is_set_html_can_run_scripts_enabled_;
  static bool is_set_sequential_focus_starting_point_enabled_;
  static bool is_shadow_contour_follows_border_enabled_;
  static bool is_shadow_root_adopted_style_sheet_enabled_;
  static bool is_shadow_root_reference_target_enabled_;
  static bool is_shadow_root_reference_target_aria_owns_enabled_;
  static bool is_shared_array_buffer_enabled_;
  static bool is_shared_array_buffer_unrestricted_access_allowed_enabled_;
  static bool is_shared_storage_api_enabled_;
  static bool is_shared_storage_web_locks_enabled_;
  static bool is_shared_worker_enabled_;
  static bool is_shared_worker_extended_lifetime_enabled_;
  static bool is_side_relative_background_position_enabled_;
  static bool is_signature_based_inline_integrity_enabled_;
  static bool is_single_axis_scroll_containers_enabled_;
  static bool is_skip_ad_enabled_;
  static bool is_skip_callbacks_when_dev_tools_not_open_enabled_;
  static bool is_skip_event_capture_enabled_;
  static bool is_skip_non_editable_in_atomic_move_enabled_;
  static bool is_skip_oof_item_for_break_candidate_enabled_;
  static bool is_skip_paragraph_split_for_inline_insert_html_enabled_;
  static bool is_skip_pseudo_only_lines_in_line_navigation_enabled_;
  static bool is_skip_touch_event_filter_enabled_;
  static bool is_skip_unselectable_content_in_serialization_enabled_;
  static bool is_skip_unselectable_elements_in_paragraph_boundary_enabled_;
  static bool is_smaller_viewport_units_enabled_;
  static bool is_smart_card_enabled_;
  static bool is_smart_zoom_enabled_;
  static bool is_snapshot_scroll_timelines_post_layout_enabled_;
  static bool is_soft_navigation_detection_enabled_;
  static bool is_soft_navigation_detection_include_replace_state_enabled_;
  static bool is_soft_navigation_heuristics_enabled_;
  static bool is_sorted_layout_shift_sources_by_impact_area_enabled_;
  static bool is_source_specific_multicast_in_direct_sockets_enabled_;
  static bool is_spat_nav_uses_cursor_inheritance_enabled_;
  static bool is_speaker_selection_enabled_;
  static bool is_speculation_measurement_enabled_;
  static bool is_spell_check_custom_dictionary_api_enabled_;
  static bool is_split_text_not_cleanup_dummy_spans_enabled_;
  static bool is_split_view_link_open_enabled_;
  static bool is_srcset_selection_matches_image_set_enabled_;
  static bool is_stable_blink_features_enabled_;
  static bool is_stacking_context_is_not_stacked_enabled_;
  static bool is_standardized_browser_zoom_enabled_;
  static bool is_standardized_browser_zoom_opt_out_enabled_;
  static bool is_sticky_position_has_overflow_per_axis_enabled_;
  static bool is_sticky_user_activation_across_same_origin_navigation_enabled_;
  static bool is_storage_buckets_enabled_;
  static bool is_storage_buckets_durability_enabled_;
  static bool is_storage_buckets_locks_enabled_;
  static bool is_streaming_sanitizer_enabled_;
  static bool is_strict_mime_types_for_workers_enabled_;
  static bool is_stylus_handwriting_enabled_;
  static bool is_sub_apps_enabled_;
  static bool is_suppress_pointer_stream_after_drag_enabled_;
  static bool is_svg_anchor_element_attributes_enabled_;
  static bool is_svg_anchor_element_download_attribute_enabled_;
  static bool is_svg_animate_motion_discrete_calc_mode_enabled_;
  static bool is_svg_avoid_resetting_filter_quality_for_tiled_pattern_enabled_;
  static bool is_svg_embedded_as_replaced_element_enabled_;
  static bool is_svg_enable_text_decoration_css_styling_enabled_;
  static bool is_svg_fall_back_to_container_size_enabled_;
  static bool is_svg_fe_image_skip_hidden_container_viewport_dependence_enabled_;
  static bool is_svg_filter_paints_for_hidden_content_enabled_;
  static bool is_svg_filter_user_space_viewport_for_svg_enabled_;
  static bool is_svg_ignore_negative_ellipse_radii_enabled_;
  static bool is_svg_inline_root_pixel_snapping_scale_adjustment_enabled_;
  static bool is_svg_length_list_clear_on_parsing_failure_enabled_;
  static bool is_svg_length_resolve_unparsed_value_enabled_;
  static bool is_svg_number_list_clear_on_parsing_failure_enabled_;
  static bool is_svg_partition_svg_document_resources_in_memory_cache_enabled_;
  static bool is_svg_path_length_css_property_enabled_;
  static bool is_svg_point_list_clear_on_parsing_failure_enabled_;
  static bool is_svg_script_element_async_attribute_enabled_;
  static bool is_svg_sizing_with_preserve_aspect_ratio_none_enabled_;
  static bool is_svg_smil_clock_value_validation_enabled_;
  static bool is_svg_text_path_path_attribute_enabled_;
  static bool is_svg_transform_on_nested_svg_element_enabled_;
  static bool is_synthesized_keyboard_events_for_accessibility_actions_enabled_;
  static bool is_synthetic_mouse_hover_over_inactive_page_enabled_;
  static bool is_system_default_accent_colors_enabled_;
  static bool is_system_fallback_emoji_vs_support_enabled_;
  static bool is_system_wake_lock_enabled_;
  static bool is_table_border_color_no_implicit_border_enabled_;
  static bool is_table_default_border_color_current_color_enabled_;
  static bool is_table_is_auto_fixed_layout_enabled_;
  static bool is_tab_size_ancestor_enabled_;
  static bool is_tab_size_with_spacing_enabled_;
  static bool is_target_in_shadow_determined_before_listener_enabled_;
  static bool is_test_blink_feature_default_enabled_;
  static bool is_test_feature_enabled_;
  static bool is_test_feature_dependent_enabled_;
  static bool is_test_feature_for_browser_process_read_write_access_origin_trial_enabled_;
  static bool is_test_feature_implied_enabled_;
  static bool is_test_feature_stable_enabled_;
  static bool is_text_area_scroll_top_preview_enabled_;
  static bool is_text_detector_enabled_;
  static bool is_text_emphasis_letter_spacing_enabled_;
  static bool is_text_emphasis_position_auto_enabled_;
  static bool is_text_emphasis_punctuation_exceptions_enabled_;
  static bool is_text_emphasis_with_ruby_enabled_;
  static bool is_text_fragment_api_enabled_;
  static bool is_text_fragment_identifiers_enabled_;
  static bool is_text_fragment_tap_opens_context_menu_enabled_;
  static bool is_text_metrics_baselines_enabled_;
  static bool is_text_overflow_clip_with_selection_enabled_;
  static bool is_text_overflow_string_enabled_;
  static bool is_text_scale_meta_tag_enabled_;
  static bool is_text_spacing_trim_fallback_enabled_;
  static bool is_text_spacing_trim_fallback_2_enabled_;
  static bool is_text_spacing_trim_fallback_chws_enabled_;
  static bool is_text_spacing_trim_yu_gothic_ui_enabled_;
  static bool is_throttled_history_api_throws_security_error_enabled_;
  static bool is_timeline_trigger_enabled_;
  static bool is_timer_throttling_for_background_tabs_enabled_;
  static bool is_timestamp_based_cls_tracking_enabled_;
  static bool is_time_zone_change_event_enabled_;
  static bool is_topics_api_enabled_;
  static bool is_topics_document_api_enabled_;
  static bool is_topics_img_api_enabled_;
  static bool is_touch_drag_and_context_menu_enabled_;
  static bool is_touch_drag_and_drop_enabled_;
  static bool is_touch_drag_on_short_press_enabled_;
  static bool is_touch_event_feature_detection_enabled_;
  static bool is_touch_text_editing_redesign_enabled_;
  static bool is_transferable_rtc_data_channel_enabled_;
  static bool is_transition_navigation_quiet_skip_enabled_;
  static bool is_translate_service_enabled_;
  static bool is_translation_api_enabled_;
  static bool is_translation_api_for_workers_enabled_;
  static bool is_traverse_flat_tree_to_handle_slots_enabled_;
  static bool is_treat_mhtml_initial_document_loads_as_cross_document_enabled_;
  static bool is_trusted_types_create_parser_options_enabled_;
  static bool is_trusted_types_from_literal_enabled_;
  static bool is_trusted_types_html_enabled_;
  static bool is_trusted_types_use_code_like_enabled_;
  static bool is_two_phase_view_transition_enabled_;
  static bool is_unclosed_form_control_is_invalid_enabled_;
  static bool is_unexposed_task_ids_enabled_;
  static bool is_unprefixed_speech_recognition_enabled_;
  static bool is_unrestricted_measure_user_agent_specific_memory_enabled_;
  static bool is_unrestricted_shared_array_buffer_enabled_;
  static bool is_unrestricted_usb_enabled_;
  static bool is_update_complex_safa_area_constraints_enabled_;
  static bool is_update_selection_on_node_insertion_enabled_;
  static bool is_update_trival_text_after_fragment_creation_from_text_enabled_;
  static bool is_url_pattern_compare_component_enabled_;
  static bool is_url_pattern_generate_enabled_;
  static bool is_url_search_params_has_and_delete_multiple_args_enabled_;
  static bool is_use_begin_frame_presentation_feedback_enabled_;
  static bool is_use_bounded_selection_offsets_in_edit_context_delete_operations_enabled_;
  static bool is_use_largest_painted_image_for_lcp_candidate_enabled_;
  static bool is_use_low_quality_interpolation_enabled_;
  static bool is_use_original_dom_offsets_for_offset_map_enabled_;
  static bool is_use_position_for_point_in_flexible_box_with_single_child_element_enabled_;
  static bool is_use_position_if_is_visually_equivalent_candidate_enabled_;
  static bool is_user_action_pseudos_stop_at_top_layer_enabled_;
  static bool is_user_defined_entry_point_timing_enabled_;
  static bool is_user_media_element_enabled_;
  static bool is_use_selection_in_dom_tree_anchor_in_extend_selection_enabled_;
  static bool is_use_shadow_host_style_check_editable_enabled_;
  static bool is_use_undo_step_element_dispatch_before_input_enabled_;
  static bool is_v8_idle_tasks_enabled_;
  static bool is_video_auto_fullscreen_enabled_;
  static bool is_video_frame_metadata_background_blur_enabled_;
  static bool is_video_frame_metadata_rtp_timestamp_enabled_;
  static bool is_video_fullscreen_orientation_lock_enabled_;
  static bool is_video_rotate_to_fullscreen_enabled_;
  static bool is_video_track_generator_enabled_;
  static bool is_video_track_generator_in_window_enabled_;
  static bool is_video_track_generator_in_worker_enabled_;
  static bool is_viewport_height_client_hint_header_enabled_;
  static bool is_viewport_segments_enabled_;
  static bool is_view_transition_async_finished_enabled_;
  static bool is_view_transition_delay_unpause_on_teardown_enabled_;
  static bool is_view_transition_hoist_backdrop_filter_effect_enabled_;
  static bool is_view_transition_long_callback_timeout_for_testing_enabled_;
  static bool is_view_transition_update_lifecycle_before_ready_enabled_;
  static bool is_view_transition_wait_until_enabled_;
  static bool is_visibility_collapse_column_enabled_;
  static bool is_visual_rect_mapping_fix_for_expansion_enabled_;
  static bool is_wake_lock_enabled_;
  static bool is_warn_on_content_visibility_render_access_enabled_;
  static bool is_web_app_installation_enabled_;
  static bool is_web_app_launch_queue_enabled_;
  static bool is_web_app_scope_extensions_enabled_;
  static bool is_web_app_scope_system_accent_color_enabled_;
  static bool is_web_app_tab_strip_enabled_;
  static bool is_web_app_tab_strip_customizations_enabled_;
  static bool is_web_app_translations_enabled_;
  static bool is_web_assembly_custom_descriptors_v_2_enabled_;
  static bool is_web_assembly_js_promise_integration_enabled_;
  static bool is_web_audio_bypass_output_buffering_enabled_;
  static bool is_web_audio_bypass_output_buffering_opt_out_enabled_;
  static bool is_web_audio_configurable_render_quantum_enabled_;
  static bool is_web_auth_enabled_;
  static bool is_web_auth_authenticator_attachment_enabled_;
  static bool is_web_authentication_ambient_enabled_;
  static bool is_web_authentication_attestation_formats_enabled_;
  static bool is_web_authentication_immediate_get_enabled_;
  static bool is_web_authentication_remote_desktop_support_enabled_;
  static bool is_web_authentication_supplemental_pub_keys_enabled_;
  static bool is_web_bluetooth_enabled_;
  static bool is_web_bluetooth_get_devices_enabled_;
  static bool is_web_bluetooth_scanning_enabled_;
  static bool is_web_bluetooth_watch_advertisements_enabled_;
  static bool is_webcodecs_video_encoder_buffers_enabled_;
  static bool is_web_crypto_pqc_enabled_;
  static bool is_web_font_resize_lcp_enabled_;
  static bool is_webgl_developer_extensions_enabled_;
  static bool is_webgl_draft_extensions_enabled_;
  static bool is_webgl_drawing_buffer_storage_enabled_;
  static bool is_webgl_on_webgpu_enabled_;
  static bool is_webgpu_compatibility_mode_enabled_;
  static bool is_webgpu_developer_features_enabled_;
  static bool is_webgpu_experimental_features_enabled_;
  static bool is_webgpu_immediates_feature_enabled_;
  static bool is_webgpu_map_sync_on_workers_enabled_;
  static bool is_webgpu_multithread_dawn_wire_on_workers_enabled_;
  static bool is_webgpu_transient_attachment_enabled_;
  static bool is_web_hid_enabled_;
  static bool is_web_hid_on_service_workers_enabled_;
  static bool is_web_identity_digital_credentials_enabled_;
  static bool is_web_identity_digital_credentials_creation_enabled_;
  static bool is_web_idl_big_int_uses_to_big_int_enabled_;
  static bool is_web_mcp_enabled_;
  static bool is_web_mcp_declarative_file_input_enabled_;
  static bool is_web_mcp_form_associated_custom_elements_enabled_;
  static bool is_web_mcp_testing_enabled_;
  static bool is_web_nfc_enabled_;
  static bool is_web_otp_enabled_;
  static bool is_web_otp_assertion_feature_policy_enabled_;
  static bool is_web_preferences_enabled_;
  static bool is_web_printing_enabled_;
  static bool is_web_share_enabled_;
  static bool is_websocket_stream_enabled_;
  static bool is_websocket_stream_standard_binary_chunk_type_enabled_;
  static bool is_web_speech_recognition_context_enabled_;
  static bool is_web_transport_application_protocol_enabled_;
  static bool is_web_transport_congestion_control_enabled_;
  static bool is_web_transport_custom_certificates_enabled_;
  static bool is_web_transport_send_group_enabled_;
  static bool is_web_transport_stats_enabled_;
  static bool is_web_ui_bundled_code_cache_async_fetch_enabled_;
  static bool is_web_usb_enabled_;
  static bool is_web_usb_on_dedicated_workers_enabled_;
  static bool is_web_usb_on_service_workers_enabled_;
  static bool is_web_vtt_regions_enabled_;
  static bool is_web_xr_enabled_;
  static bool is_web_xr_enabled_features_enabled_;
  static bool is_web_xr_frame_rate_enabled_;
  static bool is_web_xr_front_facing_enabled_;
  static bool is_web_xr_gpu_binding_enabled_;
  static bool is_web_xr_hit_test_entity_types_enabled_;
  static bool is_web_xr_image_tracking_enabled_;
  static bool is_web_xr_layers_enabled_;
  static bool is_web_xr_layers_common_enabled_;
  static bool is_web_xr_mesh_detection_enabled_;
  static bool is_web_xr_plane_detection_enabled_;
  static bool is_web_xr_pose_motion_data_enabled_;
  static bool is_web_xr_spec_parity_enabled_;
  static bool is_web_xr_visibility_mask_enabled_;
  static bool is_window_default_status_enabled_;
  static bool is_word_skip_spaces_punctuation_fix_enabled_;
  static bool is_word_spacing_white_space_pre_enabled_;
  static bool is_xml_no_external_entities_enabled_;
  static bool is_xml_parsing_rust_enabled_;
  static bool is_xml_rust_for_non_xslt_enabled_;
  static bool is_xml_serializer_consistent_default_ns_decl_matching_enabled_;
  static bool is_xpath_shadow_dom_support_enabled_;
  static bool is_xslt_enabled_;
  static bool is_xslt_special_trial_enabled_;

  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_mojo_js_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_mojo_js_test_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_protected_origin_trials_sample_api_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_protected_origin_trials_sample_api_dependent_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_protected_origin_trials_sample_api_implied_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_test_feature_protected_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_test_feature_protected_dependent_enabled_;
  static DECLARE_PROTECTED_DATA base::ProtectedMemory<bool> is_test_feature_protected_implied_enabled_;
};

class PLATFORM_EXPORT RuntimeEnabledFeatures : public RuntimeEnabledFeaturesBase {
  STATIC_ONLY(RuntimeEnabledFeatures);

  // Only the following friends are allowed to use the setters defined in the
  // protected section of RuntimeEnabledFeaturesBase. Normally, unit tests
  // should use the ScopedFeatureNameForTest classes defined in
  // platform/testing/runtime_enabled_features_test_helpers.h.
  friend class DevToolsEmulator;
  friend class InternalRuntimeFlags;
  friend class V8ContextSnapshotImpl;
  friend class WebRuntimeFeaturesBase;
  friend class WebRuntimeFeatures;
  friend class WebView;
  friend class RuntimeEnabledFeaturesTestTraits;
  friend class RuntimeProtectedEnabledFeaturesTestTraits;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_ENABLED_FEATURES_H_
