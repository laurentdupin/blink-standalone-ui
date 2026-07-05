set(BLINK_STANDALONE_LIVE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/base64.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/dispatcher/reentry_guard.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/check_is_test.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/check_op.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/callback_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/containers/linked_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/functional/callback_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/alias.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/crash_logging.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/dump_without_crashing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/hash/hash.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/hash/legacy_hash.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/i18n/case_conversion.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/i18n/i18n_constants.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/i18n/icu_string_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/json/string_escape.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/json/json_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/location.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/advanced_memory_safety_checks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/aligned_memory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/ref_counted.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/ref_counted_memory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/weak_ptr.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/observer_list_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/observer_list_types.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/pickle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/rand_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/rand_util_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/sampling_heap_profiler/lock_free_address_hash_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/sampling_heap_profiler/poisson_allocation_sampler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/sequence_checker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/sequence_checker_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/sequence_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/scoped_clear_last_error_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/simdutf_shim.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/escape.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/strcat.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/stringprintf.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_split.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_number_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_util_constants.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/sys_string_conversions_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_util_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/utf_offset_string_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/utf_ostream_operators.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/utf_string_conversion_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/utf_string_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/substring_set_matcher/matcher_string_pattern.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/substring_set_matcher/substring_set_matcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/delayed_task_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_checker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_checker_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_local_storage.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_local_storage_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/clock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/default_clock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/default_tick_clock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/tick_clock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/cityhash/city.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/cityhash_v103/src/city_v103.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/bignum-dtoa.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/bignum.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/cached-powers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/double-to-string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/fast-dtoa.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/fixed-dtoa.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/string-to-double.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/double_conversion/double-conversion/strtod.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/superfasthash/superfasthash.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_id_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_usage_estimator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/value_iterators.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/animation/animation_id_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/invalidation_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/list_container_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/debug/debug_colors.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/debug/layer_tree_debug_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/debug/rendering_stats.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/debug/rendering_stats_instrumentation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/input/hit_test_opaqueness.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/input/layer_selection_bound.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/input/scroll_snap_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/input/scroll_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/input/snap_selection_strategy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/layers/draw_properties.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/layers/recording_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/layers/touch_action_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/raster/raster_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/compositor_commit_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/clip_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/effect_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/occlusion.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/sticky_position_constraint.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/task_runner_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/transform_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/copy_output_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/debug_border_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/offset_tag.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/shared_quad_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/resources/shared_image_format.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/resources/shared_image_format_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/frame_sink_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/local_surface_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/region_capture_bounds.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/surface_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/surface_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/subtree_capture_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/traced_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/view_transition_element_resource_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/common/mailbox.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/common/shared_image_capabilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/common/shared_image_pool_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/common/shared_image_usage.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/common/sync_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/cookies/site_for_cookies.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/address_family.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/base64.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/data_url.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/filename_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/filename_util_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/ip_address.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/ip_address_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/mime_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/net_string_util_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/parse_number.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/registry_controlled_domains/registry_controlled_domain.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/lookup_string_in_fixed_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/url_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/log/net_log_values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/http/http_byte_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/http/http_connection_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/http/http_content_disposition.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/http/http_response_headers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/http/http_status_code.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/http/http_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/url_request/referrer_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/third_party/quiche/src/quiche/common/structured_headers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/cicp.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/platform_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/raster_handle_allocator_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/rgba_to_yuva.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/SkDiscardableMemory_chrome.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/skcolorspace_primaries.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/skcolorspace_trfn.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/skia_trace_memory_dump_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/skia_utils_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/skia_utils_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/metrics/public/cpp/metrics_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/simdutf/simdutf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/color/color_mixer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/color/color_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/color/color_provider_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/color/color_recipe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/color/color_transform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/accessibility/ax_event_intent.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/gpu_fence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/gpu_fence_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/overlay_plane_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/linear_gradient.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/hdr_static_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/swap_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/skia_span_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/skia_color_space_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/color_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/switches.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/native_theme/features/native_theme_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/native_theme/native_theme_aura.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/native_theme/native_theme_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/native_theme/overlay_scrollbar_constants.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/third_party/mozilla/url_parse.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_etc.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_filesystemurl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_fileurl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_host.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_ip.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_mailtourl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_non_special_url.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_pathurl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_query.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_relative.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_stdstring.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon_stdurl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_idna_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_parse_file.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/platform/network/http_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css/css_property_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css/parser/at_rule_descriptors.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css_value_keywords.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/event_target_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/event_type_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/html_element_attribute_name_lookup_trie.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/html_element_lookup_trie.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/html_element_type_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/html_entity_table.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/html_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/html_tokenizer_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/keywords.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/mathml_element_type_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/mathml_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/svg_element_type_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/svg_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/trustedtypes/trusted_types_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/xlink_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/xml_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/xmlns_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/boundary_event_dispatcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/context_menu_allowed_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/event_handler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/event_handling_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/input_device_capabilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/keyboard_event_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/mouse_event_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/mouse_wheel_event_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/pointer_event_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/scroll_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/touch.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/touch_action_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/input/touch_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/cors/cors_error_status.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/cors/origin_access_entry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/fetch_retry_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/integrity_report.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource_error.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource_load_timing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource_request.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource_response.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/heap/custom_spaces.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/associated_interface_provider_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/blink_embedded_ua_resources.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/compositor_runtime.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/vulkan_window_host.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/content_security_policy_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/css_file_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/devtools_instrumentation_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/file_chooser_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/fetch_initiator_type_names_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/generated_name_atoms_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/live_boundary_value_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/live_core_initializer_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/live_empty_clients_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/live_link_boundary_stubs.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/standalone_text_encoding_detector_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/viz_debug_capture_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/standalone_native_theme.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/standalone_svg_element_resource_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/typeface_resource_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/mojo_phase1_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/network_feature_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/standalone_process.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/url_network_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/web_history_item_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_input_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_gesture_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_keyboard_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_mouse_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_mouse_wheel_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_pointer_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/input/web_touch_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/scheme_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/permissions_policy/document_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/permissions_policy/policy_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/permissions_policy/policy_value_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/pointer_event_factory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/pointer_event_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/execution_context/window_agent_factory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/cached_permission_status.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/animation/element_smil_animations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/trustedtypes/trusted_script_url.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/bitmap_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/bitmap_image_metrics.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/decoding_image_generator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/deferred_image_decoder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/image_decoder_wrapper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/image_decoding_store.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/image_frame_generator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/image_orientation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/image_observer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/parkable_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/parkable_image_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/scrollbar_theme_settings.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/static_bitmap_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/unaccelerated_static_bitmap_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/fast_shared_buffer_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/image_decoder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/image_frame.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/png/png_image_decoder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/rw_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/segment_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/skia/segment_stream.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/image-decoders/skia/skia_image_decoder_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/network/header_field_tokenizer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/network/server_timing_header.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkCodec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkCodecColorProfile.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkColorPalette.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkEncodedInfo.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkExif.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkHdrAgtm.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkHdrAgtmParse.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkGainmapInfo.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkHdrMetadata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkPngCodecBase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkPngCodec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkPngCompositeChunkReader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkPixmapUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkSampler.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkSwizzler.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/codec/SkTiffUtility.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDataTable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMD5.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/encode/SkEncoder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/encode/SkICC.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/encode/SkPngEncoderBase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/encode/SkPngEncoderImpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/png.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngerror.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngget.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngmem.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngpread.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngread.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngrio.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngrtran.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngrutil.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngset.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngtrans.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwio.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwrite.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwtran.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwutil.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/intel/filter_sse2_intrinsics.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/intel/intel_init.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation_clock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation_input_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation_timeline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/color_property_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_animation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_animations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_animation_update.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_keyframe_effect_model.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_timeline_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_transition.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_color_interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_default_interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_interpolation_environment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_length_interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_number_interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css_transform_interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/deferred_timeline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/document_animations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/document_timeline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/effect_model.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/effect_stack.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/element_animations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/inert_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolable_color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolable_length.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolable_style_color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolable_transform_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolable_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolation_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/interpolation_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/invalidatable_interpolation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/keyframe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/keyframe_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/keyframe_effect_model.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/length_property_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/number_property_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/pending_animations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/property_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/sampled_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/scroll_snapshot_timeline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/scroll_timeline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/string_keyframe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/timing_calculations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/transition_interpolation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/transition_keyframe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/tree_counting_checker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/underlying_value_owner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/view_timeline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/abstract_property_set_css_style_declaration.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/active_style_sheets.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/basic_shape_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cascade_layer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cascade_layer_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/check_pseudo_has_cache_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/conditional_exp_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/container_query.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/container_query_evaluator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/container_query_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/container_selector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/counter_style.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/counter_style_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/counters_attachment_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_attr_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_crossfade_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_cyclic_variable_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_default_style_sheets.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_global_rule_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_identifier_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_image_generator_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_image_set_option_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_image_set_type_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_image_set_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_initial_color_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_invalid_variable_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_keyframe_shorthand_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_keyframes_rule.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_path_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_position_try_rule.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_property_equality.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_property_value_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_quad_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_selector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/check_pseudo_has_argument_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/check_pseudo_has_fast_reject_filter.cc  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/selector_checker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_selector_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_style_sheet.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_url_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_url_pattern_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_value_pool.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom/inline_style_property_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/document_style_environment_variables.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/element_rule_collector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/if_condition.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/inline_css_style_declaration.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/invalidation_flags.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/invalidation_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/pending_invalidations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/rule_invalidation_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/rule_invalidation_data_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/rule_invalidation_data_visitor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/invalidation/style_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/layout_tree_rebuild_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/media_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/media_query.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/media_query_evaluator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/mixin_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/navigation_query.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/out_of_flow_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/page_rule_collector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/at_rule_descriptor_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/at_rule_counter_style_descriptor_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/conditional_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/container_query_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_at_rule_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_if_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_lazy_parsing_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_lazy_property_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_idioms.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_token_stream.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_property_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_selector_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_supports_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_tokenizer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_tokenizer_input_stream.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_variable_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/media_query_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/navigation_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/part_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/post_style_update_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/css_parsing_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/css_property_ref.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/longhands/custom_property.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/longhands/longhands_custom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/longhands/variable.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/property_registration.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/random_caching_key.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/font_size_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/cascade_expansion.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/cascade_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/cascade_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/element_resolve_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/filter_operation_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/font_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/match_request.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/match_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/matched_properties_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/scoped_style_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/selector_filter_parent_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_cascade.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_resolver_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/element_style_resources.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_resolver_stats.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_rule_usage_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/viewport_style_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/pending_sheet_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/rule_feature_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/rule_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/rule_set_diff.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/scroll_target_group_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_computed_style_declaration.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/computed_style_css_value_mapping.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/selector_filter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_containment_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_engine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_environment_variables.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_image_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_invalidation_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_recalc_change.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_recalc_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_counter_style.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_font_feature_values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_font_palette_values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_import.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_keyframe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_route.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_rule_view_transition.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_scope_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_scope_frame.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_sheet_candidate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_sheet_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_sheet_contents.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_sheet_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_traversal_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/successful_position_fallback.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/try_value_flips.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/ua_counter_style_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/character_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/child_node_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/comment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/container_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/decoded_data_document_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document_encoding_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/focusgroup_flags.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/increment_load_event_delay_count.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document_fragment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document_init.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document_lifecycle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/document_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/dom_node_ids.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/dom_implementation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/element_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/element_rare_data_vector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/empty_node_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/event_dispatcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/event_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/event_target.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/event_target_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/node_event_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/scoped_event_queue.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/tree_scope_event_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/events/window_event_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/flat_tree_traversal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/id_target_observer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/id_target_observer_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/layout_tree_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/layout_tree_builder_traversal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/live_node_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/live_node_list_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/names_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/node_lists_node_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/node_traversal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/abstract_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/nth_index_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/pseudo_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/qualified_name.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/scriptable_document_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/shadow_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/slot_assignment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/slot_assignment_engine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/space_split_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/tag_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/text.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/tree_ordered_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/tree_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/tree_scope_adopter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/user_action_element_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/whitespace_attacher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/geometry/dom_rect_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/url/dom_url_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/url/dom_url_utils_read_only.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/xml_document.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/animation_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/before_text_inserted_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/keyboard_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/simulated_event_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/touch_event_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/transition_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/execution_context/agent_cluster_key.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/layout_subtree_root_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/local_dom_window.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/local_frame.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/local_frame_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/policy_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/root_frame_viewport.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/settings.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/viewport_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/document_all_name_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/document_name_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/form_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_input_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_label_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_text_area_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/input_type_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/step_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/base_checkable_input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/checkbox_input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/radio_input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/radio_button_group_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/base_text_input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/text_input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/text_field_input_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/text_control_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/text_control_inner_elements.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_span_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/type_ahead.cc

  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/labels_node_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_option_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_opt_group_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_options_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_select_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/html_selected_content_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/menu_list_inner_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/option_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/select_mutation_observer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/forms/select_type.cc

  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_base_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_area_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_body_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_br_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_font_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/rel_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_dimension.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_div_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_head_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_heading_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_hr_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_li_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_map_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_olist_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_ulist_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_html_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_name_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_paragraph_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_slot_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_style_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_tag_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_title_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_unknown_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/list_item_ordinal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/background_html_scanner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/atomic_html_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/css_preload_scanner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/fragment_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_construction_site.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_document_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_element_stack.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_entity_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_entity_search.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_formatting_element_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_parser_idioms.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_parser_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_parser_reentry_permit.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_preload_scanner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_resource_preloader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_tokenizer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_tree_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/patch.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/preload_request.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/resource_preloader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/document_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/document_load_timing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/frame_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/frame_load_request.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/old_document_info_for_commit.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/history_item_standalone.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/policy_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/progress_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/permissions_policy/document_policy_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/blob/blob_url_store.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/blob/blob_url_store.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/data_pipe_getter.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/data_pipe_getter.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/shadow/shadow_element_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/window_name_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/anchor_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/block_break_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/block_child_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/block_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/block_layout_algorithm_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/block_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/box_fragment_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/break_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/constraint_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/depth_ordered_layout_object_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/exclusions/exclusion_area.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/exclusions/exclusion_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/exclusions/layout_opportunity.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/floats_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/fragment_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/fragmentation_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/axis.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/bfc_offset.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/bfc_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/box_strut.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/logical_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/margin_strut.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/transform_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_line_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_named_line_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_placement.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_track_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_track_sizing_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/hit_test_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/hit_test_location.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/ink_overflow.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/fit_text_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/fragment_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/fragment_items.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/fragment_items_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/hyphen_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/initial_letter_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_box_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_break_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_caret_position.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_child_layout_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_cursor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_item_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_item_segment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_items_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_items_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/inline_node_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/justification_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_box_fragment_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_break_candidate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_breaker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_truncator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/line_widths.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/logical_line_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/logical_line_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/logical_line_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/offset_mapping.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/offset_mapping_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/paragraph_line_breaker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/physical_line_box_fragment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/ruby_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/score_line_breaker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/text_auto_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/transformed_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/flex_child_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/flex_gap_accumulator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/flex_item_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/flex_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/flex_line_breaker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/layout_flexible_box.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/flex/line_flexer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_layout_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/grid_sizing_tree.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid/layout_grid.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_running_positions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/grid_lanes/layout_grid_lanes.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/gap/cross_gap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/gap/gap_geometry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/gap/gap_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/gap/main_gap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/min_max_sizes.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/logical_fragment_link.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_block.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_block_flow.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_box.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_box_hot.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_br.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_inline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_input_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_object.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_object_child_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_quote.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_text.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_text_combine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_text_fragment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme_default.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme_font_provider_default.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme_font_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme_mobile.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/forms/layout_text_control.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/forms/layout_text_control_inner_editor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/forms/layout_text_control_multi_line.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/forms/layout_text_control_single_line.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/static_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/bidi_adjustment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/caret_display_item_client.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/append_node_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/apply_block_element_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/apply_style_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/break_blockquote_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/composite_edit_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/create_link_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/delete_from_text_node_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/delete_selection_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/delete_selection_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/edit_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/editing_commands_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/editing_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/editor_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/format_block_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/indent_outdent_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_commands.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_incremental_text_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_into_text_node_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_line_break_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_list_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_node_before_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_node_list_before_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_paragraph_separator_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/insert_text_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/merge_identical_elements_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/move_commands.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/remove_css_property_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/remove_format_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/remove_node_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/remove_node_preserving_children_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/replace_node_with_span_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/replace_selection_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/selection_for_undo_step.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/set_character_data_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/set_node_attribute_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/simplify_markup_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/smart_replace_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/split_element_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/split_text_node_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/split_text_node_containing_element_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/style_commands.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/typing_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/undo_stack.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/undo_step.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/unlink_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/commands/wrap_contents_in_dummy_span_command.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/compare_positions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editing_behavior.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editing_style.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editing_strategy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editing_style_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editing_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/editor_key_bindings.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/element_inner_text.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/ephemeral_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/finder/chunk_graph_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/frame_caret.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/frame_selection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/finder/find_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/finder/find_results.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/granularity_strategy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/inline_box_position.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/backwards_character_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/bit_stack.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/character_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/fully_clipped_state_stack.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/kill_ring_none.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/simplified_backwards_text_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/text_searcher_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/text_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/text_iterator_behavior.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/text_iterator_text_node_handler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/iterators/text_iterator_text_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/layout_selection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/local_caret_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/ng_flat_tree_shorthands.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/plain_text_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position_units.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position_units_paragraph.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position_units_sentence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position_units_word.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/position_with_affinity.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/relocatable_position.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/selection_adjuster.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/selection_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/selection_editor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/selection_modifier.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/selection_modifier_line.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/selection_template.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/set_selection_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/backspace_state_machine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/backward_code_point_state_machine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/backward_grapheme_boundary_state_machine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/forward_code_point_state_machine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/forward_grapheme_boundary_state_machine.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/state_machine_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/state_machines/text_segmentation_machine_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/surrounding_text.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/text_affinity.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/text_offset_mapping.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/text_segments.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/serializers/create_markup_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/serializers/markup_accumulator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/serializers/markup_formatter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/visible_position.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/visible_selection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/visible_units.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/visible_units_line.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/visible_units_paragraph.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/editing/visible_units_sentence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/current_input_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/input_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/events/web_input_event_conversion.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/inline/caret_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/length_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/line_clamp_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/measure_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/selection_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/list/layout_inside_list_marker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/list/layout_inline_list_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/list/layout_list_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/list/layout_outside_list_marker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/list/list_marker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/list/unpositioned_list_marker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/logical_box_fragment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/oof_positioned_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/outline_rect_collector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/physical_box_fragment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/physical_fragment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/physical_fragment_rare_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/positioned_float.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/relative_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/space_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/scroll_anchor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/scrollable_overflow_calculator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/shapes/shape_outside_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/simplified_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_inline_text.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_text.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_text_query.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_text_layout_attributes_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_text_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/layout_table.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/layout_table_caption.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/layout_table_cell.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/layout_table_column.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/layout_table_row.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/layout_table_section.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_borders.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_child_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_layout_algorithm_types.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_layout_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_row_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/table/table_section_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_caption_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_col_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_cell_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_part_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_row_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_rows_collection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_table_section_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/table_cell_paint_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/text_decoration_offset.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_foreign_object.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_hidden_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_block.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_filter_primitive.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_model_object.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_resource_marker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_resource_clipper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_resource_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_resource_filter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_root.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_shape.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_ellipse.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_transformable_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/layout_svg_viewport_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_content_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_layout_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_marker_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/svg_resources.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/transformed_hit_test_location.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/svg/transform_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/transform_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/chrome_client.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/page.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/border_shape_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/border_shape_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/block_paint_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_background_paint_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_border_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_decoration_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_fragment_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_paint_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_model_object_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_painter_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/clip_path_clipper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/background_image_geometry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_background_paint_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/box_reflection_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/clip_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/contoured_border_geometry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/cull_rect_updater.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/fieldset_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/fragment_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/fragment_data_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/fragment_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/frame_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/frame_set_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/focusgroup_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/focusgroup_controller_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/grid_focusgroup_structure_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/spatial_navigation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/spatial_navigation_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/gap_decorations_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/geometry_box_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/hit_testing_transform_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/inline_box_fragment_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/nine_piece_image_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/object_paint_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/object_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/outline_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_layer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_layer_clipper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_layer_paint_order_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_layer_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_layer_resource_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_layer_stacking_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/paint_property_tree_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/pre_paint_tree_walk.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/scoped_paint_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/scoped_svg_paint_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/scrollable_area_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_container_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_foreign_object_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_image_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_model_object_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_object_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_root_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/svg_shape_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/table_painters.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/text_decoration_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/decoration_line_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/text_decoration_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/text_fragment_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/text_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/theme_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/theme_painter_default.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/url_metadata_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/view_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/route_matching/route_match_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scroll_alignment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scroll_animator_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scroll_into_view_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollable_area.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_layer_delegate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_theme.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_theme_aura.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_theme_fluent.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_theme_overlay.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/scroll/scrollbar_theme_overlay_mobile.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/scrolling/sticky_position_scrolling_constraints.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/standalone_live_frame_bridge_probe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/standalone_renderer_probe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/basic_shapes.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/border_edge.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/computed_style.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/filter_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/position_area.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/shadow_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/shadow_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_base_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_ray.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_shape.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_enumeration.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_enumeration_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_angle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_angle_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_angle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_enumeration_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_href.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_length.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_number.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_circle_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/graphics/svg_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/graphics/svg_image_for_container.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/graphics/isolated_svg_document_host.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/graphics/svg_image_chrome_client.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/graphics/filters/svg_fe_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/graphics/filters/svg_filter_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_document_extensions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_element_rare_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_fe_image_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_filter_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_filter_primitive_standard_attributes.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_fit_to_view_box.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_animated_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_desc_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_geometry_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_graphics_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_image_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_image_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_length.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_length_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_length_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_length_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_length_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_line_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_marker_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_matrix_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_number.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_number_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_number_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_blender.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_byte_stream_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_byte_stream_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_query.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_string_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_string_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_path_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_parsing_error.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_point.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_point_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_preserve_aspect_ratio.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_preserve_aspect_ratio_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_rect_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_rect_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_static_string_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_string_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_string_list_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_svg_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_tests.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_text_content_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_text_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_text_positioning_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_title_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_transform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_transform_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_transform_distance.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_transform_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_transform_list_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_transformable_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_unknown_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_unit_types.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_uri_reference.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_use_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_view_spec.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_viewport_container_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_zoom_and_pan.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/properties/svg_list_property.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/properties/svg_animated_property.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/properties/svg_property_tear_off.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/exported/web_agent_cluster_key.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/exported/web_navigation_params.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/trustedtypes/trusted_script_url.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/testing/dummy_page_holder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/view_transition/view_transition_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/exported/file_path_conversion.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/exported/web_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/exported/web_http_body.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/exported/web_url.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/static_data_navigation_body_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/weborigin/scheme_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_fallback_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_height.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_metrics.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_variant_alternates.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/color_table_lookup.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/open_type_baseline_metrics.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/open_type_caps_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/open_type_vertical_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/orientation_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/script_run_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/case_mapping_harfbuzz_buffer_filler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/font_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/glyph_data_range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/han_kerning.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/harfbuzz_face.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/harfbuzz_font_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/harfbuzz_shaper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/run_segmenter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/shape_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/shape_result_bloberizer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/shape_result_cursor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/shape_result_spacing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/shape_result_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/shaping_line_breaker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/skia/skia_text_metrics.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/small_caps_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/symbols_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/unicode_range_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/utf16_text_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/contoured_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/float_rounded_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/layout_unit.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/path_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/physical_offset.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/physical_size.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/stroke_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/blend_mode.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/box_reflection.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/adjust_mask_layer_geometry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/chunk_to_layer_mapper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/content_layer_client_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/layers_as_json.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/paint_artifact_compositor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/paint_chunks_to_cc_layer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/pending_layer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing/property_tree_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositing_reasons.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositor_element_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/compositor_filter_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/graphics_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/graphics_context_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/intercepting_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/logging_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/memory_managed_paint_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/memory_managed_paint_recorder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/clip_paint_property_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/cull_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/display_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/display_item_client.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/display_item_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/display_item_raster_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/drawing_display_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/drawing_recorder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/effect_paint_property_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/foreign_layer_display_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/geometry_mapper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/geometry_mapper_clip_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/geometry_mapper_transform_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/hit_test_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/ignore_paint_timing_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_artifact.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_chunk.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_chunk_subset.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_chunker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_controller_debug_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_property_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_record_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/paint_under_invalidation_checker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/property_tree_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/raster_invalidation_tracking.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/raster_invalidator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/region_capture_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/scroll_paint_property_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/scrollbar_display_item.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/tracked_element_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint/transform_paint_property_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/paint_invalidation_reason.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/path_traversal_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/platform_focus_ring.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/predefined_color_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/styled_stroke_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/touch_action_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/instrumentation/canvas_memory_dump_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/instrumentation/resource_coordinator/document_resource_coordinator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/json/json_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/json/json_values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/fetch_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource_loader_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/text_resource_decoder_options.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/bidi_paragraph.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/character.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/character_emoji.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/character_break_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/icu_error.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/justification_opportunity.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/layout_locale.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/locale_to_script_mapping.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/segmented_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/text_break_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/text_break_iterator_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/text_break_iterator_internal_icu.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/text_boundaries.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/unicode_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/theme/web_theme_engine_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/theme/web_theme_engine_default.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/theme/web_theme_engine_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/timer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/affine_transform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/interpolated_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/matrix_3d_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/matrix_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/perspective_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/rotate_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/rotation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/scale_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/skew_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/transform_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/transforms/translate_transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/weborigin/sandboxed_opaque_security_origin_creator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/weborigin/security_origin.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/atomic_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/date_math.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/decimal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/dtoa.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/hash_table.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/shared_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/ascii_fast_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/atomic_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/atomic_string_table.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/base64.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/case_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/line_ending.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/strcat.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_builder_stream.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_concatenate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_statics.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_to_number.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_utf8_adaptor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/string_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_codec.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_codec_latin1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_codec_replacement.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_codec_user_defined.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_codec_utf16.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_codec_utf8.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_encoding.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_encoding_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_offset_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/text_position.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/utf16.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/utf8.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/text/wtf_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/stack_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/threading.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/threading_primitives.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/uuid.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/wtf/wtf.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/debug_annotation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/axis_transform2d.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/box_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/cubic_bezier.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/decomposed_transform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/insets_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/mask_filter_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/matrix44.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/point3_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/point_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/quad_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/rect_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/rect_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/size_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/transform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/transform_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/triangle_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/vector2d_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/vector2d_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/vector3d_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/lock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/element_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/checked_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRegion.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkMemory_malloc.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/draw_looper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/filter_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_record.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/filter_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_description.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/length.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/draw_looper_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/interpolation_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/filters/filter_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/filters/paint_filter_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/filters/paint_filter_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/filters/source_alpha.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/platform/character_property_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/platform/color_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/writing_direction_mode.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkData.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkString.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkTypeface.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/animation_time_delta.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_length_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_box_model_object.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFont.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkSemaphore.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/style/computed_style_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/css_to_style_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/fill_layer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/list_style_type_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/position_try_fallbacks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_highlight_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_selector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css/properties/css_property_instances.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/keyframe/timing_function.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_math_expression_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_primitive_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css/css_primitive_value_unit_trie.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_unset_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/style_builder_converter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/text_link_colors.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/animation/timing_function.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_math_function_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_numeric_literal_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_property_name.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_to_length_conversion_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_value_clamping_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/computed_style_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/css_property.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/property_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/resolver/transform_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/calculation_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/length_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_gradient_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_markup.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_ray_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_string_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_syntax_definition.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_value_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_change_reason.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_variables.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css/properties/shorthands.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_custom_ident_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_ratio_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_uri_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_variable_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/css_color_function_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_fast_paths.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/parser/css_parser_local_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/grid_track_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_initial_letter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/text_decoration_thickness.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_family.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_palette.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/style_property_shorthand.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_axis_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_border_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_border_image_slice_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_content_distribution_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_inherited_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_repeat_style_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_repeat_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_revert_layer_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_revert_rule_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_revert_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_scroll_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_view_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/style_property_shorthand_custom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_alpha_color_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_alternate_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_color_mix_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_contrast_color_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_counter_content_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_counter_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_cursor_image_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_dynamic_range_limit_mix_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_flip_revert_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_font_face_src_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_font_family_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_font_feature_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_font_style_range_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_font_variation_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_function_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_grid_auto_repeat_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_grid_integer_repeat_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_grid_template_areas_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_image_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_initial_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_layout_function_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_paint_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_palette_mix_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_pending_substitution_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_pending_system_font_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_progress_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_property_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_reflect_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_relative_color_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_scoped_keyword_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_shadow_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_shape_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_superellipse_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_timing_function_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_trigger_attachment_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_unicode_range_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_unparsed_declaration_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_unresolved_color_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_animation_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_basic_shape_values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_bracketed_value_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_gap_decoration_property_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/nine_piece_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/svg_paint.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/text/quotes_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/style/computed_style_base_constants.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_transition_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/applied_text_decoration.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/content_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_initial_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/generic_font_family_settings.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_invalidation_reason.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_object_hot.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/atomic_flag.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/css/properties/longhands.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/point_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/size.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/geometry/physical_rect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_flags.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/computed_grid_template_areas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/simple_font_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkTDArray.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathBuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpBuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_script_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/color_filter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/point.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/skia_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/anchor_specifier_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/reference_clip_path_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_generated_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_image_computed_css_value_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_crossfade_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_mask_source_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_pending_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_tree_scope_resources.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/pagination_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/generated_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/gradient.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/gradient_generated_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/crossfade_generated_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/svg/svg_parser_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkColor.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMatrix.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRegion_path.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRRect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkThreadID.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/win/SkHRESULT.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkParsePath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/rrect_f.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/rrect_f_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/url_canon.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/origin.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathMeasure.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkTextBlob.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsOp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/display_item_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_filter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_op.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_op_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_recorder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/path_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/record_paint_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/render_surface_filters.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/filter_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_shader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/skia_paint_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlendMode.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkImageInfo.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPixmap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/appendable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/bmpset.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/brkeng.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/brkiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/bytesinkutil.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/bytestream.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/bytestrie.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/bytestriebuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/bytestrieiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/caniter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/characterproperties.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/chariter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/charstr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/cmemory.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/cstr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/cstring.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/cwchar.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/dictbe.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/dictionarydata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/dtintrv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/edits.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/emojiprops.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/errorcode.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/filteredbrk.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/filterednormalizer2.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/fixedstring.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/icudataver.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/icuplug.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/loadednormalizer2impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/localebuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/localematcher.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/localeprioritylist.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locavailable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locbased.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locdispnames.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locdistance.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locdspnm.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locid.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/loclikely.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/loclikelysubtags.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locmap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locresdata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/locutil.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/lsr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/lstmbe.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/messagepattern.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/mlbe.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/normalizer2.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/normalizer2impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/normlzr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/parsepos.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/patternprops.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/pluralmap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/propname.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/propsvec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/punycode.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/putil.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbi.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbidata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbinode.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbirb.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbiscan.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbisetb.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbistbl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbitblb.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/rbbi_cache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/resbund.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/resbund_cnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/resource.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/restrace.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ruleiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/schriter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/serv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/servlk.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/servlkf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/servls.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/servnotf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/servrbf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/servslkf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/sharedobject.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/simpleformatter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/static_unicode_sets.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/stringpiece.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/stringtriebuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uarrsort.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ubidi.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ubidiln.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ubiditransform.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ubidiwrt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ubidi_props.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ubrk.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucasemap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucasemap_titlecase_brkiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucat.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uchar.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucharstrie.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucharstriebuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucharstrieiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uchriter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucln_cmn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucmndata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv2022.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvbocu.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvdisp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvhz.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvisci.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvlat1.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvmbcs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvscsu.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnvsel.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_bld.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_cb.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_cnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_ct.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_err.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_ext.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_io.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_lmb.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_set.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_u16.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_u32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_u7.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucnv_u8.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucol_swp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucptrie.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ucurr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/udata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/udatamem.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/udataswp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uenum.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uhash.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uhash_us.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uidna.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uinit.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uinvchar.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ulist.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uloc.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ulocale.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ulocbuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uloc_keytype.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uloc_tag.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/umapfile.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/umath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/umutablecptrie.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/umutex.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unames.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unifiedcache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unifilt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unifunct.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uniset.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unisetspan.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uniset_closure.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uniset_props.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unistr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unistr_case.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unistr_case_locale.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unistr_cnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unistr_props.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unistr_titlecase_brkiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unorm.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/unormcmp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uobject.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uprops.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uresbund.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uresdata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ures_cnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uscript.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uscript_props.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/usc_impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uset.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/usetiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uset_props.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ushape.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/usprep.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustack.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustrcase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustrcase_locale.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustrenum.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustrfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustring.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustrtrns.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustr_cnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustr_titlecase_brkiter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/ustr_wcs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utext.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utf_impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/util.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/util_props.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utrace.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utrie.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utrie2.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utrie2_builder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utrie_swap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uts46.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/utypes.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uvector.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uvectr32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/uvectr64.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/common/wintz.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/alphaindex.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/anytrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/astro.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/basictz.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/bocsu.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/brktrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/buddhcal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/calendar.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/casetrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/cecal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/chnsecal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/choicfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/coleitr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/coll.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collation.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationbuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationcompare.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationdata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationdatabuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationdatareader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationdatawriter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationfastlatin.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationfastlatinbuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationfcd.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationkeys.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationroot.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationrootelements.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationruleparser.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationsets.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationsettings.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationtailoring.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/collationweights.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/compactdecimalformat.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/coptccal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/cpdtrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csdetect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csmatch.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csr2022.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csrecog.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csrmbcs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csrsbcs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csrucode.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/csrutf8.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/curramt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/currfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/currpinf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/currunit.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dangical.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/datefmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dayperiodrules.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dcfmtsym.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/decContext.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/decimfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/decNumber.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/displayoptions.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-bignum-dtoa.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-bignum.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-cached-powers.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-double-to-string.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-fast-dtoa.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-string-to-double.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/double-conversion-strtod.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dtfmtsym.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dtitvfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dtitvinf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dtptngen.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/dtrule.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/erarules.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/esctrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ethpccal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/fmtable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/fmtable_cnv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/format.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/formattedvalue.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/formattedval_iterimpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/formattedval_sbimpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/formatted_string_builder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/fphdlimp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/fpositer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/funcrepl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/gender.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/gregocal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/gregoimp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/hebrwcal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/indiancal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/inputext.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/islamcal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/iso8601cal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/japancal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/listformatter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/measfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/measunit.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/measunit_extra.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/measure.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_arguments.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_checker.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_data_model.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_errors.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_evaluation.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_formattable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_formatter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_function_registry.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_parser.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/messageformat2_serializer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/msgfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/name2uni.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/nfrs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/nfrule.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/nfsubs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/nortrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/nultrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_affixutils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_asformat.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_capi.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_compact.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_currencysymbols.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_decimalquantity.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_decimfmtprops.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_fluent.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_formatimpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_grouping.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_integerwidth.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_longnames.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_mapper.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_modifiers.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_multiplier.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_notation.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_output.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_padding.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_patternmodifier.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_patternstring.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_rounding.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_scientific.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_simple.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_skeletons.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_symbolswrapper.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_usageprefs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/number_utils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_affixes.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_compositions.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_currency.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_decimal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_parsednumber.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_scientific.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_symbols.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numparse_validators.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numrange_capi.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numrange_fluent.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numrange_impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/numsys.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/olsontz.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/persncal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/pluralranges.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/plurfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/plurrule.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/quant.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/quantityformatter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbnf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbtz.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbt_data.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbt_pars.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbt_rule.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rbt_set.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/regexcmp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/regeximp.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/regexst.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/regextxt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/region.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/reldatefmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/reldtfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rematch.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/remtrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/repattrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/rulebasedcollator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/scientificnumberformatter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/scriptset.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/search.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/selfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/sharedbreakiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/simpletz.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/smpdtfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/smpdtfst.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/sortkey.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/standardplural.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/string_segment.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/strmatch.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/strrepl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/stsearch.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/taiwncal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/timezone.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/titletrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tmunit.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tmutamt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tmutfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tolowtrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/toupptrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/translit.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/transreg.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tridpars.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tzfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tzgnames.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tznames.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tznames_impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tzrule.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/tztrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucal.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucln_in.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucol.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucoleitr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucol_res.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucol_sit.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ucsdet.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/udat.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/udateintervalformat.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/udatpg.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ufieldpositer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uitercollationiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ulistformatter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ulocdata.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/umsg.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/unesctrn.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uni2name.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/units_complexconverter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/units_converter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/units_data.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/units_router.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/unum.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/unumsys.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/upluralrules.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uregex.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uregexc.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uregion.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/usearch.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uspoof.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uspoof_build.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uspoof_conf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/uspoof_impl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/utf16collationiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/utf8collationiterator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/utmscale.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/utrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/vtzone.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/vzone.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/windtfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/winnmfmt.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/wintzimpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/zonemeta.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/zrule.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/icu/source/i18n/ztrans.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkBuffer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkDebug.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkColorSpace.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPaint.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlurMaskFilterImpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkBlendModeColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread_ref.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_image_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/skia_paint_image_generator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCanvas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkM44.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage_Lazy.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage_LazyFactories.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage_Raster.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage_RasterFactories.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_optical_sizing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_selection_types.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_smoothing_mode.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_size_adjust.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_variant_emoji.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_variant_east_asian.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_variant_numeric.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_width_variant.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/font_settings.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/resolved_font_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/text_rendering_mode.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCPURecorder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPicture.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPictureData.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPictureFlat.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPicturePlayback.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPictureRecord.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPictureRecorder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPtrRecorder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/skcms.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_orientation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/skcms_ext.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkColorSpaceXformSteps.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkConvertPixels.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMallocPixelRef.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMask.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMasks.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPixelRef.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkWritePixelsRec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkImageShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkMalloc.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkUTF.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDescriptor.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFontDescriptor.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFontMgr.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkFontMgr_win_dw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkTypeface_win_dw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkScalerContext_win_dw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/win/SkDWrite.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/win/SkDWriteFontFileStream.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/win/SkDWriteGeometrySink.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkSharedMutex.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sfnt/SkOTUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBBHFactory.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRTree.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sfnt/SkOTTable_name.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkTypefaceCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScalerContext.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStream.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkSurface.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/shorthands/shorthands_custom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_aspect_ratio.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_fallback_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/calculation_expression_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/platform/font_family_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFontStream.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkGlyph.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkGlyphRunPainter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStrike.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStrikeCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStrikeSpec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkCustomTypeface.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/css_math_operator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom/css_keyword_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom/css_unsupported_color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom/cross_thread_color_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom/cross_thread_keyword_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_scrollbar_color.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/style/style_svg_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/geometry/math_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/size_conversions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/properties/css_direction_aware_resolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_worklet_input.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/animation/css/css_timing_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/cssom/css_paint_worklet_input.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathData.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkContainers.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkEdgeClipper.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkGeometry.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathIter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathPriv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathRawShapes.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPoint.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkArenaAlloc.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkAddIntersections.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpAngle.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpCoincidence.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpContour.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpEdgeBuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpSegment.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpSpan.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsAsWinding.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsCommon.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsConic.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsCubic.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsCurve.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsDebug.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsLine.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsQuad.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsRect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsSimplify.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsTightBounds.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsTSect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsTypes.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathOpsWinding.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkPathWriter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_op_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkColorTable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkColorFilterBase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_op_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkContourMeasure.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScan.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScan_AAAPath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScan_AntiPath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScan_Antihair.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScan_Hairline.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScan_Path.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStringUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkColorSpaceXformColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkComposeColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkMatrixColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkTableColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkParse.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFont_serial.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkImageFilterCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkImageFilterTypes.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkLocalMatrixImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkReadBuffer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkWriteBuffer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkBlurImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkColorFilterImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkComposeImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkCropImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkDropShadowImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkMagnifierImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkPictureImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/GlyphRun.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/decode_stashing_image_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/decoded_draw_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/draw_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/image_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_image_generator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/scoped_raster_flags.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkBlendImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkDisplacementMapImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkImageImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkMatrixConvolutionImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkMatrixTransformImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkMergeImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkMorphologyImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkShaderImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkBlendShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkColorShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkEmptyShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkPerlinNoiseShaderImpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkShaderBase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/skottie_serialization_history.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/skottie_text_property_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/tone_map_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkAnnotation.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkVertices.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/imagefilters/SkLightingImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkTiledImageUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pdf/SkDocument_PDF_None.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_op_buffer_iterator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmapDevice.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCanvas_Raster.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/SkCornerPathEffect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/SkDashPathEffect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkPictureShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/gradients/SkConicalGradient.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/gradients/SkGradientBaseShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/gradients/SkLinearGradient.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/gradients/SkRadialGradient.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/gradients/SkSweepGradient.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/legacy_display_globals.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkHalf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitter_A8.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitter_ARGB32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitter_Sprite.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkChecksum.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDraw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDraw_atlas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDraw_text.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDraw_vertices.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMaskCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRasterClip.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRasterPipeline.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRasterPipelineBlitter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkReadPixelsRec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStrokeRec.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkUnPreMultiply.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/SkBlenders.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkDeque.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkLog_win.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlendModeBlender.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlurMask.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCachedData.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCanvasPriv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDevice.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFlattenable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkImageGenerator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMaskFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMaskFilterBase.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPaintPriv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkResourceCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkSurface_Base.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSpecialImage.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkEventTracer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkNullCanvas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmapCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkIDChangeListener.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkLatticeIter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMatrixInvert.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMipmap.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMipmapAccessor.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMipmapBuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPixmapDraw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkYUVAPixmaps.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkYUVAInfo.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkYUVPlanesCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage_Base.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkSurface_Raster.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/deferred_paint_record.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/shader_transfer_cache_entry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/transfer_cache_serialize_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/solid_color_analyzer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/discardable_image_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/math_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/simple_enclosed_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkWorkingColorSpaceShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkPictureImageGenerator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmapProcState_matrixProcs.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBitmapProcState_opts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/simdutf/simdutf.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDrawShadowInfo.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkQuads.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/clear_for_opaque_raster.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMipmapHQDownSampler.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkGaussFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkPatchUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkNWayCanvas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkColorFilterShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkRescaleAndReadPixels.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSynchronizedResourceCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStrokerPriv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRSXform.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMaskBlurFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkGlobalInitialization_core.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCpu.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCapabilities.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitRow_opts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/switches.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkVertState.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkStroke.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSpriteBlitter_ARGB32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMemset_opts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitRow_D32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlitMask_opts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkTriColorShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkTransformShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkEdge.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBlurEngine.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkShadowUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkShadowTessellator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkDashPath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkBlockAllocator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_op_buffer_serializer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkWorkingFormatColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkEdgeBuilder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkAnalyticEdge.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkAlphaRuns.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkAAClip.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/paint_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkOpCubicHull.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkReduceOrder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkIntersections.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPath_serial.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathRaw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkLineClipper.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCubicClipper.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkDQuadLineIntersection.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkDLineIntersection.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkDConicLineIntersection.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/pathops/SkDCubicLineIntersection.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkCubics.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkBezierCurves.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/StrikeForGPU.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkSafeMath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkBigPicture.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCompressedDataUtils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkCPUContext.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkDrawable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRecord.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRecordCanvas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRecordDraw.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRecordedDrawable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRecordOpts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRecords.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkWriter32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/image/SkImage_Picture.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/SlugFromBuffer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/modules/skcms/src/skcms_TransformBaseline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkAutoPixmapStorage.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkGraphics.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMaskGamma.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkOpts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPathEffect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkPixelStorage.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkScalar.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSwizzler_opts.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkFloatingPoint.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkLocalMatrixShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkMatrix22.cpp
)

set_source_files_properties(
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/resources/shared_image_format_utils.cc
  PROPERTIES INCLUDE_DIRECTORIES
             "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/include")

set(BLINK_STANDALONE_PROTOZERO_RUNTIME_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/field.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/gen_field_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/message.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/message_arena.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/packed_repeated_fields.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/proto_decoder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/scattered_heap_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/scattered_stream_null_delegate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/scattered_stream_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/static_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/virtual_destructors.cc
)

set(BLINK_STANDALONE_PROTOZERO_FILTERING_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/filtering/filter_bytecode_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/filtering/message_filter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/filtering/message_filter_config.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protozero/filtering/string_filter.cc
)

set(BLINK_STANDALONE_PERFETTO_BASE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/android_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/base64.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/clock_snapshots.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/crash_keys.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/ctrl_c_handler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/default_platform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/event_fd.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/file_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/getopt_compat.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/intrusive_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/intrusive_tree.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/lock_free_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/logging.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/metatrace.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/paged_memory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/periodic_task.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/pipe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/regex/regex.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/scoped_mmap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/scoped_sched_boost.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/status.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/string_splitter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/string_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/string_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/string_view_splitter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/temp_file.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/thread_checker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/thread_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/thread_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/time.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/unix_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/uuid.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/version.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/virtual_destructors.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/waitable_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/base/weak_runner.cc
)

set(BLINK_STANDALONE_PERFETTO_PROTOVM_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/error_handling.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/executor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/ro_cursor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/rw_proto.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/rw_proto_cursor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/protovm/vm.cc
)

set(BLINK_STANDALONE_PERFETTO_TRACING_CORE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/id_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/in_process_shared_memory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/null_trace_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/shared_memory_abi.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/shared_memory_arbiter_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/trace_packet.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/trace_writer_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/core/virtual_destructors.cc
)

set(BLINK_STANDALONE_PERFETTO_TRACING_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/console_interceptor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/data_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/event_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/interceptor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/in_process_tracing_backend.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/interceptor_trace_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/system_tracing_backend_fake.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/tracing_backend_fake.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/tracing_muxer_fake.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/tracing_muxer_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/track_event_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/internal/track_event_interned_fields.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/platform.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/platform_windows.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/traced_value.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/trace_writer_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/tracing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/tracing_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/track.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/track_event_category_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/track_event_legacy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/track_event_state_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/virtual_destructors.cc
)

set(BLINK_STANDALONE_PERFETTO_TRACING_SERVICE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/clock.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/metatrace_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/packet_stream_validator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/random.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/trace_buffer_v1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/trace_buffer_v1_with_v2_shadow.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/trace_buffer_v2.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/tracing_service_endpoints_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/tracing_service_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/service/tracing_service_session.cc
)

set(BLINK_STANDALONE_PERFETTO_ANDROID_STATS_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/android_stats/statsd_logging_helper.cc
)

file(GLOB_RECURSE BLINK_STANDALONE_PERFETTO_GENERATED_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/common/*.gen.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/common/*.pbzero.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/config/*.gen.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/config/*.pbzero.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/protovm/*.gen.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/protovm/*.pbzero.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/trace/*.gen.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/perfetto/protos/perfetto/trace/*.pbzero.cc
)

list(APPEND BLINK_STANDALONE_PERFETTO_GENERATED_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/tracing/protos/chrome_enums.pbzero.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/base/tracing/protos/chrome_track_event.pbzero.cc
)
list(REMOVE_DUPLICATES BLINK_STANDALONE_PERFETTO_GENERATED_SOURCES)

set(BLINK_STANDALONE_BASE_TRACING_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/interned_args_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_dump_request_args.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/named_trigger.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/perfetto_proto_appender.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_arguments.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_config.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_config_category_filter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_event_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_log.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/trace_session_observer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/traced_value.cc
)

set(BLINK_STANDALONE_BLINK_TRACING_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/instrumentation/tracing/trace_event.cc
)

# DevTools/Inspector implementation is outside the Phase 1 compositor target.
# Keep generated headers available for declarations, but do not link the
# inspector agents/protocol runtime or probe implementation into production.
set(BLINK_STANDALONE_BLINK_INSPECTOR_OWNER_SOURCES
)

set(BLINK_STANDALONE_BLINK_PROBE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/probe/async_task_context.cc
)

set(BLINK_STANDALONE_RE2_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/bitmap256.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/bitstate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/compile.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/dfa.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/filtered_re2.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/mimics_pcre.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/nfa.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/onepass.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/parse.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/perl_groups.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/prefilter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/prefilter_tree.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/prog.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/re2.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/regexp.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/simplify.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/tostring.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/unicode_casefold.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/re2/unicode_groups.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/util/rune.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/re2/src/util/strutil.cc
)

set(BLINK_STANDALONE_URL_PATTERN_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/url_pattern/simple_url_pattern_matcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/url_pattern/url_pattern_util.cc
)

set(BLINK_STANDALONE_LIBURLPATTERN_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/liburlpattern/constructor_string_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/liburlpattern/parse.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/liburlpattern/part.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/liburlpattern/pattern.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/liburlpattern/tokenize.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/liburlpattern/utils.cc
)

set(BLINK_STANDALONE_URL_PATTERN_INDEX_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/url_pattern_index/url_rule_util.cc
)

set(BLINK_STANDALONE_SUBRESOURCE_FILTER_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/subresource_filter/core/common/scoped_rule.cc
)

set(BLINK_STANDALONE_INSPECTOR_PROTOCOL_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/cbor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/chromium/json_platform_chromium.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/chromium/protocol_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/dispatch.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/error_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/json.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/protocol_core.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/serializable.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/span.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/inspector_protocol/crdtp/status.cc
)

set_source_files_properties(${BLINK_STANDALONE_INSPECTOR_PROTOCOL_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "CRDTP_IMPLEMENTATION")

set(BLINK_STANDALONE_BLINK_INSPECTOR_PROTOCOL_GENERATED_SOURCES)

# Network service runtime and network IPC implementation files are not active in
# the standalone renderer. Generated services/network headers remain available
# as Blink data vocabulary, but external network access is intentionally closed
# at the standalone resource-loading boundary.

set(BLINK_STANDALONE_NETWORK_PUBLIC_MOJOM_VOCABULARY_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/content_security_policy.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/content_security_policy.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/content_security_policy.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/connection_allowlist.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/connection_allowlist.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/connection_allowlist.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cors.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cors.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cors.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cors_origin_pattern.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cors_origin_pattern.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cors_origin_pattern.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cross_origin_embedder_policy.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cross_origin_embedder_policy.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cross_origin_embedder_policy.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_address.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_address.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_address.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_address_space.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_address_space.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_address_space.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_algorithm.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_algorithm.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_algorithm.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_metadata.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_metadata.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_metadata.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_policy.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_policy.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/integrity_policy.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_endpoint.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_endpoint.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/ip_endpoint.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/link_header.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/link_header.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/link_header.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/load_timing_info.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/load_timing_info.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/load_timing_info.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/network_param.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/network_param.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/network_param.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cross_origin_opener_policy.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cross_origin_opener_policy.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/cross_origin_opener_policy.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/schemeful_site.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/schemeful_site.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/schemeful_site.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/fetch_api.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/permissions_policy/permissions_policy.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/permissions_policy/permissions_policy.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/permissions_policy/permissions_policy.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/permissions_policy/permissions_policy_feature.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/referrer_policy.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/service_worker_router_info.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/source_location.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/source_location.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/source_location.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/trust_tokens.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/trust_tokens.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/trust_tokens.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/url_response_head.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/url_response_head.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/url_response_head.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/web_sandbox_flags.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/web_sandbox_flags.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/web_sandbox_flags.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/web_bundle_handle.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/web_bundle_handle.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/network/public/mojom/web_bundle_handle.mojom.cc
)

# Structured-clone/postMessage/blob-transfer implementations are outside the
# Phase 1 rendering target. Headers remain available as generated vocabulary,
# but these runtime transfer paths are not linked.
set(BLINK_STANDALONE_BLINK_MESSAGING_SOURCES)

set(BLINK_STANDALONE_UNSUPPORTED_MESSAGING_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/messaging_transfer_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/task_attribution_id.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/task_attribution_id.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/task_attribution_id.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/user_activation_snapshot.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/user_activation_snapshot.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/user_activation_snapshot.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/messaging/message_port_channel.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/messaging/message_port_descriptor.cc
)

set(BLINK_STANDALONE_FRAME_MOJOM_SUPPORT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/frame_mojom_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/frame/frame_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/frame/frame_policy_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/base/ime/ime_text_span.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/base/ime/mojom/ime_types_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/events/ipc/ui_events_param_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/events/keycodes/dom/keycode_converter.cc
)

set(BLINK_STANDALONE_UNSUPPORTED_POLICY_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/html_meta_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/mixed_content_checker_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/network_mojom_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/permissions_policy_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/permissions_policy_protocol_constants_unsupported.cc
)

set(BLINK_STANDALONE_PHASE1_UNSUPPORTED_RUNTIME_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/image_map_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/lcpp_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/preload_helper_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/text_track_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/worker_performance_phase1_unsupported.cc
)

set(BLINK_STANDALONE_POLICY_CONTAINER_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/connection_allowlist.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/cross_origin_embedder_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/integrity_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/integrity_metadata_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/integrity_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/policy_container_utils.cc
)

file(GLOB_RECURSE BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/*.mojom-shared.cc
)
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "test-utils\\.cc$")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/annotation/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/array_buffer/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/blob/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/context_menu/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/devtools/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/disk_allocator\\.mojom")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/drag/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/fenced_frame/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/fetch/")
list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/third_party/blink/public/mojom/messaging/")

set(BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_VOCABULARY_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/fenced_frame/fenced_frame_config.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/fenced_frame/fenced_frame_config.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/fenced_frame/fenced_frame_config.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/fetch/fetch_api_request.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/blob/data_element.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/blob/data_element.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/static_bitmap_image.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/static_bitmap_image.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/public/mojom/messaging/static_bitmap_image.mojom.cc
)

file(GLOB_RECURSE BLINK_STANDALONE_MOJOM_GENERATED_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/cc/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/cc/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/cc/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/mojo/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/mojo/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/mojo/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/components/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/components/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/components/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ipc/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ipc/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/viz/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/viz/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/viz/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/skia/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/skia/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/skia/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ui/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ui/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ui/*.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/url/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/url/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/url/*.mojom-shared.cc
)
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "test-utils\\.cc$")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "mojo/public/mojom/base/proto_wrapper\\.mojom")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "mojo/public/mojom/base/ref_counted_memory\\.mojom")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "mojo/public/mojom/base/safe_base_name\\.mojom")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "motion_event_android")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "(^|/)android(/|_|$)")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "_android\\.mojom")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "frame_sink_video_capture")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "video_capture")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "WebGPU")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "webgpu")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "WebNN")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "webnn")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "dawn")
if(NOT WIN32)
  list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/mojo/public/mojom/base/.*_win\\.mojom")
  list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/services/viz/privileged/mojom/gl/")
  list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/services/viz/privileged/mojom/viz_main\\.mojom")
endif()
# Viz, input, and GL service interfaces are non-Blink service vocabulary in
# this phase. Keep normal/shared C++ outputs, but do not compile accidental
# Blink variants from broad local generation passes.
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/services/viz/.*\\.mojom-blink\\.cc$")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/components/input/.*\\.mojom-blink\\.cc$")
list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "/ui/gl/.*\\.mojom-blink\\.cc$")
list(REMOVE_DUPLICATES BLINK_STANDALONE_MOJOM_GENERATED_SOURCES)

set(BLINK_STANDALONE_VIZ_BLINK_VALUE_MOJOM_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/viz/public/mojom/compositing/local_surface_id.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/viz/public/mojom/compositing/shared_image_format.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/services/viz/public/mojom/compositing/view_transition_element_resource_id.mojom-blink.cc
)

set(BLINK_STANDALONE_UI_GL_MOJOM_GENERATED_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ui/gl/mojom/gl_implementation.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ui/gl/mojom/gl_implementation.mojom-shared.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/ui/gl/mojom/gl_implementation.mojom.cc
)

file(GLOB_RECURSE BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/gpu/*.mojom.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/gpu/*.mojom-blink.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/gpu/*.mojom-shared.cc
)
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "test-utils\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "WebGPU")
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "webgpu")
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "WebNN")
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "webnn")
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX "dawn")
list(REMOVE_DUPLICATES BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES)

file(GLOB_RECURSE BLINK_STANDALONE_CC_COMPOSITOR_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/animation/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/base/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/debug/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/input/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/layers/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/metrics/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/mojo_embedder/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/mojom/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/paint/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/raster/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/resources/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/scheduler/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/tiles/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/trees/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/view_transition/*.cc
)
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/benchmarks/")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/test/")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/test_support/")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/android/")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "_unittest")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "_perftest")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "_pixeltest")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "_test\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "_test_base\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "_fuzzer")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/layers/video_layer.*\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/layers/video_frame_provider_client_impl\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/layers/heads_up_display_layer.*\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/paint/skottie_mru_resource_provider\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/paint/skottie_wrapper_impl\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/metrics/scroll_jank_v4_frame_stage_calculator\\.cc$")
list(FILTER BLINK_STANDALONE_CC_COMPOSITOR_SOURCES EXCLUDE REGEX "/cc/metrics/scroll_jank_v4_tracing_recorder\\.cc$")
list(REMOVE_DUPLICATES BLINK_STANDALONE_CC_COMPOSITOR_SOURCES)

set(BLINK_STANDALONE_CC_PHASE1_EXPLICIT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/cc_scroll_jank_metrics_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/cc_micro_benchmark_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/benchmarks/benchmark_instrumentation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/benchmarks/micro_benchmark.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/benchmarks/micro_benchmark_controller_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/benchmarks/micro_benchmark_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/layers/heads_up_display_layer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/cc/layers/heads_up_display_layer_impl.cc
)

set(BLINK_STANDALONE_NATIVE_MOJOM_TRAIT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/big_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/big_buffer_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/byte_size_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/byte_string_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/file_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/generic_pending_associated_receiver_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/generic_pending_receiver_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/process_id_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/read_only_file_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/read_only_buffer_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/shared_memory_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/shared_memory_version.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/string16_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/time_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/token_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/unguessable_token_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/values_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/base/wstring_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/string_traits_wtf.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/validation_errors.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/validation_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/message_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/message_view.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/sqlite_vfs/mojom/sqlite_vfs_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/persistent_cache/mojom/persistent_cache_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/connection_allowlist_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/cross_origin_embedder_policy_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/integrity_policy_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/network/public/cpp/url_loader_completion_status.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/blit_request_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/bitmap_in_shared_memory_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/frame_deadline_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/public/mojom/bitmap_skbitmap_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/public/mojom/image_info_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/mailbox_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/constants_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/gpu_disk_cache_type_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/luid_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/messaging/accelerated_static_bitmap_image_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/frame/view_transition_state_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/navigation/impression_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/tokens/tokens_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/mojo/string16_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/mojom/url_gurl_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/url/mojom/origin_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/buffer_types_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/color_space_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/display_color_spaces_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/gpu_extra_info_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/gpu_fence_handle_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/hdr_metadata_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/delegated_ink_metadata_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/linear_gradient_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/mask_filter_info_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/mojom/native_handle_types_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/mojom/gl_implementation_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/latency/mojom/latency_info_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/events/mojom/event_latency_metadata_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/display/mojom/display_constants_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/display/mojom/screen_info_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/display/mojom/screen_infos_mojom_traits.cc
)

set(BLINK_STANDALONE_MOJO_BINDINGS_RUNTIME_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/generic_pending_associated_receiver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/generic_pending_receiver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/async_flusher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/pending_flush.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/urgent_message_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/connection_group.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/connection_group_ref.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/associated_interface_ptr_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/associated_group_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/associated_group.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/associated_receiver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/array_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/binding_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/connector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/control_message_handler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/control_message_proxy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/generated_code_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/handle_serialization.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/interface_endpoint_client.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/message.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/message_dispatcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/message_header_validator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/message_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/message_size_estimator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/multiplex_router.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/pending_receiver_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/pending_remote_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/pipe_control_message_handler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/pipe_control_message_proxy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/proxy_to_responder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/scoped_interface_endpoint_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/send_message_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/sequence_local_sync_event_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/sync_call_restrictions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/sync_event_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/sync_handle_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/sync_handle_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/task_runner_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/thread_safe_forwarder_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/validation_errors.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/validation_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/bindings/lib/validation_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/platform/platform_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/handle_signal_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/message.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/platform_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/simple_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/trap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/wait.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/cpp/system/wait_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/mojo/public/c/system/thunks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/mojo_native_struct_unsupported.cc
)

set(BLINK_STANDALONE_VIZ_COMMON_VALUE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/client/shared_image_interface.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/client/client_resource_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/viz_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/gl_switches.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/gpu/context_cache_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/blit_request.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/begin_frame_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/copy_output_request.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/copy_output_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/begin_frame_args.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_sinks/delay_based_time_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/frame_timing_details.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/hit_test/hit_test_region_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/aggregated_render_pass.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/aggregated_render_pass_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/compositor_frame.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/compositor_frame_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/compositor_frame_transition_directive.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/compositor_render_pass.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/compositor_render_pass_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/content_draw_quad_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/frame_deadline.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/frame_interval_inputs.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/largest_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/picture_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/quad_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/render_pass_io.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/render_pass_draw_quad_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/render_pass_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/shared_element_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/solid_color_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/surface_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/texture_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/tile_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/quads/video_hole_draw_quad.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/resources/returned_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/resources/transferable_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/child_local_surface_id_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/parent_local_surface_id_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/surfaces/tracked_element_rects.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/transition_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/copy_output_result_mojom_traits.cc
)

set(BLINK_STANDALONE_VIZ_PUBLIC_CPP_MOJOM_TRAIT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/crash_keys.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/begin_frame_args_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/compositor_frame_metadata_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/compositor_frame_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/compositor_frame_transition_directive_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/compositor_render_pass_id_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/compositor_render_pass_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/filter_operation_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/filter_operations_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/frame_interval_inputs_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/frame_timing_details_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/paint_filter_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/quads_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/resource_id_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/shared_image_format_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/thread_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/transferable_resource_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/compositing/trees_in_viz_timing_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/hit_test/aggregated_hit_test_region_mojom_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/cpp/hit_test/hit_test_region_list_mojom_traits.cc
)

file(GLOB_RECURSE BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/client/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/common/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/host/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/public/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/services/viz/privileged/*.cc
)
# Phase Viz/GPU keeps the broad Viz service/display import, but filters browser
# host glue, tests, optional debugger/input trails, and platform output devices
# that are not part of the first in-process software/Vulkan checkpoint.
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/components/viz/host/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/test/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/tests/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/test_support/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_test_")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/demo/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/java/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/debugger/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/input/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/performance_hint/")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_unittest")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_perftest")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_pixeltest")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_test\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_test_base\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_test_helper\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_mock\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "mock_")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "fake")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_fuzzer")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)android(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)fuchsia(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)ios(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)linux(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)mac(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)ozone(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)wayland(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "(^|/)x11(/|_|$)")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_android\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_fuchsia\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_ios\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_linux\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_mac\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_ozone\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_wayland\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_x11\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "delegated_ink")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "ca_layer_overlay")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "dc_layer_overlay\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_processor_android")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_processor_delegated")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_processor_mac")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_processor_ozone")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_processor_surface_control")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_processor_win")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "overlay_strategy_underlay_cast")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "test_resource_factory")
# Browser-side GPU remote/channel wrappers are not part of the first
# in-process Viz display checkpoint. The GPU service implementation remains in
# the broad import; services/viz/public/cpp/gpu/gpu.cc is client/browser glue.
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/services/viz/public/cpp/gpu/gpu\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "/services/viz/public/cpp/gpu/context_provider_command_buffer\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "throw_uncaught_exception")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "skia_output_device_dawn")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "skia_output_device_dcomp")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "skia_output_device_webview")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "skia_output_device_vulkan")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "software_output_device_win")
# Keep optional runtime/platform feature paths out of this Windows Vulkan
# checkpoint. The generated/value vocabulary remains available separately.
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "frame_sink_throttler")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "WebGPU")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "webgpu")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "WebNN")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "webnn")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "dawn")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "gmock")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "_posix\\.cc$")
# Video cadence matching is media-timing policy, not required for the first
# in-process static/canvas compositor checkpoint.
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "frame_interval_matchers")
# ImageContextImpl currently includes Skia Graphite/Dawn headers unconditionally;
# keep Dawn/WebGPU runtime out of this Windows Vulkan checkpoint.
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "image_context_impl\\.cc$")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "video")
list(FILTER BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES EXCLUDE REGEX "media")

file(GLOB_RECURSE BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/client/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/common/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/config/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/*.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/vulkan/*.cc
)
list(APPEND BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/vulkan/init/vulkan_factory.cc
)
if(WIN32)
  list(APPEND BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/vulkan/win32/vulkan_implementation_win32.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/vulkan/win32/vulkan_surface_win32.cc
  )
endif()
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/test/")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/tests/")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/test_support/")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_test_")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_unittest")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_perftest")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_pixeltest")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_test\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_test_base\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_test_helper\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_mock\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "fake")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "test_helper")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "test_utils")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "test_image")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_fuzzer")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "mock_")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "mock_transfer_buffer")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "test_shared_image_interface")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "unittest_main")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/mocks")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)android(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)fuchsia(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)ios(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)linux(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)mac(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)ozone(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)wayland(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "(^|/)x11(/|_|$)")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_android\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_fuchsia\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_ios\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_linux\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_mac\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_ozone\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_wayland\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_x11\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "ahardwarebuffer")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "d3d")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "dcomp")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "compound_image_backing")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "egl_image_backing")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "external_vk_image")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "disk_cache")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "drm_modifiers_filter_vulkan")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gles2_c_lib")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/dawn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "dawn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "dxgi")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gles2_cmd_decoder")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gl_context_mock")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gl_surface_mock")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "iosurface")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "image_reader_gl_owner")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "mappable_buffer_ahb")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "mappable_buffer_io_surface")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "mappable_buffer_native_pixmap")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "native_pixmap")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "passthrough")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "memory_program_cache")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "mock_texture_owner")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "texture_owner")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "webgpu")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "webgpu_implementation")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "webgpu_interface")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "WebGPU")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "WebNN")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "webnn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gmock")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_posix\\.cc$")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gl_ozone")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "ozone_image")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "android_image")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "android.*image")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "external_vk_image_dawn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "shared_image.*dawn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gpu_surface")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "wrapped_graphite_texture_backing")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "video")
list(FILTER BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "media")

file(GLOB_RECURSE BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/*.cc
)
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/test/")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/tests/")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_unittest")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_perftest")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_test\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_mock\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "fake")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/android/")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "/ozone/")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "android")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "ozone")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "dawn")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "WebGPU")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "webgpu")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gmock")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_posix\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_android\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_fuchsia\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_ios\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_linux\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_mac\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_ozone\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_wayland\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "_x11\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "child_window_win\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "ca_renderer")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "dcomp")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "dc_layer")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "delegated_ink")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "direct_composition")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "egl_surface_io_surface\\.cc$")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gl_mock")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gl_surface_egl_surface_control")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "gl_surface_egl_x11")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "swap_chain")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "vsync_provider_win_dcomp")
list(FILTER BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES EXCLUDE REGEX "vsync_thread_win_dcomp")
list(REMOVE_DUPLICATES BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES)
list(REMOVE_DUPLICATES BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES)
list(REMOVE_DUPLICATES BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES)

set(BLINK_STANDALONE_GFX_RANGE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/range/range.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/range/range_f.cc
)

set(BLINK_STANDALONE_UI_VALUE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/base/ui_base_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/trace_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/tween.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/keyframe/animation_curve.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/keyframe/keyframe_effect.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/keyframe/keyframe_model.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/keyframe/keyframed_animation_curve.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/animation/keyframe/transition.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/ca_layer_params.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/color_space.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/color_space_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/delegated_ink_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/display_color_spaces.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/extension_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/font_render_params.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/win/d3d_shared_fence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/ipc/gfx_param_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/ipc/geometry/gfx_param_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/gpu_extra_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/insets_outsets_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/three_point_cubic_bezier.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/transform_operation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/geometry/transform_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/codec/png_codec.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/codec/vector_wstream.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/gpu_memory_buffer_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/hdr_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/overlay_layer_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/overlay_transform_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/win/crash_id_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/win/hwnd_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/win/window_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/selection_bound.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/swap_result.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gfx/vsync_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/latency/latency_info.cc
)

set(BLINK_STANDALONE_VIZ_GPU_SUPPORT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/sqlite_vfs/pending_file_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/persistent_cache/pending_backend.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/discardable_memory/client/client_discardable_shared_memory_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/discardable_memory/common/discardable_shared_memory_heap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/startup_metric_utils/common/startup_metric_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/startup_metric_utils/gpu/startup_metric_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/version_info/version_info_with_user_agent.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/debugger/viz_debugger.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display/frame_interval_matchers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/image_context_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/skia_output_device_dcomp.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/skia_output_device_webview.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/skia_output_device_vulkan.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/software_output_device_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/software_output_device_win_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/display_embedder/software_output_device_win_swapchain.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/frame_sinks/frame_sink_throttler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/frame_sinks/video_detector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/hit_test/hit_test_aggregator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/hit_test/hit_test_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/components/viz/service/performance_hint/hint_session.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/client/gles2_c_lib.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/gles2_cmd_decoder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/gles2_cmd_decoder_passthrough.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/gles2_cmd_decoder_passthrough_doers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/gles2_cmd_decoder_passthrough_handlers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/gles2_cmd_decoder_passthrough_handlers_autogen.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/passthrough_program_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/dxgi_shared_handle_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/compound_image_backing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/external_vk_image_backing_factory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/external_vk_image_backing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/external_vk_image_gl_representation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/external_vk_image_overlay_representation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/command_buffer/service/shared_image/external_vk_image_skia_representation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/command_buffer_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/context_url.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/gles2_command_buffer_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/gpu_channel.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/gpu_channel_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/gpu_channel_shared_image_interface.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/gpu_init.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/gpu_watchdog_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/image_transport_surface_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/raster_command_buffer_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/shared_image_stub.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/gpu_in_process_thread_service.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/in_process_command_buffer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/in_process_gpu_thread_holder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/raster_in_process_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/common/gpu_disk_cache_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/color_plane_layout.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/format_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/video_frame.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/video_frame_layout.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/video_frame_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/video_frame_pool.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/video_types.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/video_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/base/wait_and_replace_sync_token_client.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/media/filters/video_cadence_estimator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/convolver.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/convolver_SSE2.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/image_operations.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/opacity_filter_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkPaintFilterCanvas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/display/win/display_config_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/dc_layer_overlay_params.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/dcomp_surface_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/direct_composition_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/dc_layer_overlay_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/child_window_win.cc
)

set(BLINK_STANDALONE_ANGLE_IMAGE_UTIL_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/angle_version_info.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/angleutils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/CompiledShaderState.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/debug.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/entry_points_enum_autogen.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/Float16ToFloat32.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/gl_enum_utils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/gl_enum_utils_autogen.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/mathutil.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/PackedEnums.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/PackedGLEnums_autogen.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/PoolAlloc.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/SimpleMutex.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/string_utils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/system_utils.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/tls.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/utilities.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/third_party/xxhash/xxhash.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/image_util/imageformats.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/image_util/loadimage.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/image_util/loadimage_etc.cpp
)
if(WIN32)
  list(APPEND BLINK_STANDALONE_ANGLE_IMAGE_UTIL_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/system_utils_win.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/system_utils_win32.cpp
  )
elseif(UNIX AND NOT APPLE)
  list(APPEND BLINK_STANDALONE_ANGLE_IMAGE_UTIL_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/system_utils_linux.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/common/system_utils_posix.cpp
  )
endif()

file(GLOB_RECURSE BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/compiler/preprocessor/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/compiler/translator/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/compiler/translator/glsl/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/compiler/translator/tree_ops/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/compiler/translator/tree_ops/glsl/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/angle/src/compiler/translator/tree_util/*.cpp
)
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/ir/src/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/tree_ops/glsl/apple/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/hlsl/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/msl/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/spirv/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/wgsl/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "/tests?/")
list(FILTER BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES EXCLUDE REGEX "_unittest")
list(REMOVE_DUPLICATES BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES)
set_source_files_properties(${BLINK_STANDALONE_ANGLE_TRANSLATOR_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "ANGLE_ENABLE_ESSL=1;ANGLE_ENABLE_GLSL=1")

# Video/audio decoding, media session, WebRTC, and media stream parser runtime
# sources are intentionally not active in this standalone phase. Canvas and
# static image rendering remain active through Blink, Skia, GPU, and Viz owners.

set(BLINK_STANDALONE_BASE_JSON_RUNTIME_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/atomicops.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/check.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/byte_size.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/json/json_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/json/json_string_value_serializer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/json/values_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/discardable_memory_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/discardable_shared_memory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/memory_pressure_listener.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/memory_pressure_listener_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/unsafe_shared_memory_pool.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/pattern.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/cancelable_task_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_collision_warner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/hang_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_pressure_level_proto.cc
)

file(GLOB_RECURSE BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/tessellate/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/vk/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/vk/vulkanmemoryallocator/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/analysis/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/codegen/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/ir/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/lex/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/tracing/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/transform/*.cpp
)
list(APPEND BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkBase64.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkLog.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkSpinlock.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkExecutor.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkFontMetricsPriv.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkKnownRuntimeEffects.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRuntimeBlender.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkRuntimeEffect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkYUVMath.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkMesh.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkSLTypeShared.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkTaskGroup.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkTypeface_remote.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/SkColorMatrix.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/SkShaderMaskFilterImpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/effects/colorfilters/SkRuntimeColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/shaders/SkRuntimeShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/DistanceFieldAdjustTable.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/GlyphVector.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/Slug.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/SlugImpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/StrikeCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/SubRunAllocator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/SubRunContainer.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/SubRunControl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/TextBlob.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/TextBlobRedrawCoordinator.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/VertexFiller.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/text/gpu/SkChromeRemoteGlyphCache.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkShaderUtils.cpp
)
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/android/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/dawn/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/d3d/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/gl/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/ganesh/gl/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/ganesh/d3d/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/ganesh/mtl/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/mtl/")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/gpu/tessellate/.*Test")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "AHardwareBuffer")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "Android")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "Graphite")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "Metal")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "Mock")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "Test")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/lex/Main\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/SkSLModuleDataFile\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/codegen/SkSLHLSLCodeGenerator\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/codegen/SkSLMetalCodeGenerator\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/codegen/SkSLSPIRVtoHLSL\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/codegen/SkSLSPIRVValidator\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/codegen/SkSLWGSLCodeGenerator\\.cpp$")
list(FILTER BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES EXCLUDE REGEX "/sksl/codegen/SkSLWGSLValidator\\.cpp$")
list(APPEND BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES
  # GrDirectContext::MakeMock is compiled into Skia's runtime object even
  # though standalone never selects it for presentation.
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/mock/GrMockBackendSurface.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/mock/GrMockCaps.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/mock/GrMockGpu.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/mock/GrMockTypes.cpp
)
list(REMOVE_DUPLICATES BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES)

set_source_files_properties(${BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "SKIA_IMPLEMENTATION=1;SK_GANESH=1;SK_VULKAN=1;SK_USE_INTERNAL_VULKAN_HEADERS=1")

file(GLOB_RECURSE BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/*.cpp
)
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/dawn/")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/d3d/")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/mtl/")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/surface/Surface_Android")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/precompile/")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/gpu/graphite/vk/precompile/")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "AHardwareBuffer")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "Android")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "Dawn")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "Metal")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "Mock")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "Test")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "Vello")
list(FILTER BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES EXCLUDE REGEX "/third_party/vello/")
list(APPEND BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/capture/SkCapture.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/capture/SkCaptureCanvas.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/capture/SkCaptureManager.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PaintOption.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PaintOptions.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PrecompileBlender.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PrecompileColorFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PrecompileImageFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PrecompileMaskFilter.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PrecompileRuntimeEffect.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/graphite/precompile/PrecompileShader.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/sksl/SkSLGraphiteModules.cpp
)
list(REMOVE_DUPLICATES BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES)

set_source_files_properties(${BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "SKIA_IMPLEMENTATION=1;SK_GRAPHITE=1;SK_VULKAN=1;SK_USE_INTERNAL_VULKAN_HEADERS=1")

file(GLOB BLINK_STANDALONE_SKIA_GL_BACKEND_COMPAT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/gl/*.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/gpu/ganesh/gl/builders/*.cpp
)
list(FILTER BLINK_STANDALONE_SKIA_GL_BACKEND_COMPAT_SOURCES EXCLUDE REGEX "AHardwareBuffer")
list(APPEND BLINK_STANDALONE_SKIA_GL_BACKEND_COMPAT_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/core/SkOverdrawCanvas.cpp
)
list(REMOVE_DUPLICATES BLINK_STANDALONE_SKIA_GL_BACKEND_COMPAT_SOURCES)

set_source_files_properties(${BLINK_STANDALONE_SKIA_GL_BACKEND_COMPAT_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "SKIA_IMPLEMENTATION=1;SK_GANESH=1;SK_GL=1")

set(BLINK_STANDALONE_CRYPTO_RUNTIME_SOURCES
)

set(BLINK_STANDALONE_BORINGSSL_HASH_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/md5/md5.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/sha/sha1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/sha/sha256.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/fipsmodule/sha/sha1.cc.inc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/fipsmodule/sha/sha256.cc.inc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/boringssl_hash_support.cc
)

set(BLINK_STANDALONE_BASE_RUNTIME_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/at_exit.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/barrier_closure.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/command_line.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/debugger.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/debugger_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/gdi_debug_util_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/stack_trace.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/stack_trace_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/task_trace.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/feature_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/base_paths.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/base_paths_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/environment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/scoped_environment_variable_override.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/discardable_memory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_enumerator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_enumerator_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_tracing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_util_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_path.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/file_version_info_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/important_file_writer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/important_file_writer_cleaner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/memory_mapped_file.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/memory_mapped_file_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/safe_base_name.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/functional/callback_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/hash/sha1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/lazy_instance_helpers.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/logging.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/io_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/message_pump.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/message_pump_default.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/message_pump_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/platform_shared_memory_mapper_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/read_only_shared_memory_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/platform_shared_memory_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/platform_shared_memory_region_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/page_size_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/post_delayed_memory_reduction_task.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/protected_memory_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/shared_memory_mapper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/shared_memory_mapping.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/shared_memory_security_policy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/shared_memory_switch.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/shared_memory_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/unsafe_shared_memory_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/writable_shared_memory_region.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory_coordinator/memory_coordinator_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/native_library_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/scoped_native_library.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/version.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/bucket_ranges.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/crc32.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/dummy_histogram.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/field_trial.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/field_trial_entry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/field_trial_param_associator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/field_trial_params.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/histogram.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/histogram_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/histogram_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/histogram_samples.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/histogram_snapshot_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/metrics_hashes.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/persistent_histogram_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/persistent_memory_allocator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/persistent_sample_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/ranges_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/sample_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/sample_vector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/sparse_histogram.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/metrics/statistics_recorder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/observer_list_threadsafe.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/pending_task.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_info_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_handle_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_metrics.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_metrics_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/profiler/metadata_recorder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/profiler/module_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/profiler/module_cache_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/profiler/sample_metadata.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/base_stack_sampling_profiler_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/run_loop.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/strcat_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_split_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/string_number_conversions_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/condition_variable_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/waitable_event.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/waitable_event_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/waitable_event_watcher_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/system/sys_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/system/sys_info_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/path_service.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/containers/intrusive_heap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/power_monitor/power_monitor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/power_monitor/power_monitor_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/work_id_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/lock_metrics_recorder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/common/checked_lock_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/common/lazy_now.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/common/operations_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/common/scoped_defer_task_posting.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/common/task_annotator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/current_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/execution_fence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/scoped_set_task_priority_for_current_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/post_job.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/default_delayed_task_handle_delegate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequenced_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/single_thread_task_executor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/single_thread_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/associated_thread_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/atomic_flag_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/delayed_task_handle_delegate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/enqueue_order_generator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/fence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/sequence_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/sequence_manager_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/sequenced_task_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/task_order.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/task_queue.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/task_queue_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/task_queue_selector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/task_time_observer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/tasks.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/thread_controller.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/thread_controller_power_monitor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/thread_controller_with_message_pump_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/time_domain.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/wake_up_queue.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/work_deduplicator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/work_queue.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/work_queue_sets.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/sequence_manager/work_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/delayed_task_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/environment_config.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/job_task_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/pooled_parallel_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/pooled_sequenced_task_runner.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/pooled_single_thread_task_runner_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/pooled_task_runner_delegate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/priority_queue.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/sequence.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/service_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/task.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/task_source.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/task_source_sort_key.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/task_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/thread_group.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/thread_group_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/thread_pool_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/thread_pool_instance.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/worker_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_pool/worker_thread_set.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/task_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/task_traits.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/task/thread_type.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/timer/elapsed_timer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/timer/timer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/scoped_blocking_call.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/scoped_blocking_call_internal.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/scoped_thread_priority.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/sequence_local_storage_map.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/sequence_local_storage_slot.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/simple_thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_id_name_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_restrictions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/post_task_and_reply_impl.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/third_party/nspr/prtime.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time_delta_from_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time_override.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/unguessable_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/heap_profiler_allocation_context_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/histogram_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/malloc_dump_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_allocator_dump.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_allocator_dump_guid.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_dump_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_dump_provider_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_dump_scheduler.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/memory_infra_background_allowlist.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/measured_memory_dump_provider_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/trace_event/process_memory_dump.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/message_window.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/pe_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/pe_image_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/security_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/access_token.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/access_control_list.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/com_init_balancer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/com_init_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/hstring_reference.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/object_watcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/resource_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/resource_exhaustion.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_bstr.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_gdi_object.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_handle.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_handle_verifier.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_hstring.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_com_initializer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_winrt_initializer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/scoped_variant.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/security_descriptor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/sid.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/static_constants.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/win_util.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/wrapped_window_proc.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/windows_version.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/win/wmi.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/vlog.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/version_info/version_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/handle_attachment_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/handle_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_channel.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_channel_factory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_channel_proxy.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_listener.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_message_attachment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_message_pipe_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_mojo_handle_attachment.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_mojo_bootstrap.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/param_traits_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/ipc/ipc_sync_channel.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/codec_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/font_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/geometry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/base_threading_instrumentation_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/canvas_phase1_unsupported.cc
)

set(BLINK_STANDALONE_BLINK_RUNTIME_OWNER_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/common/features_generated.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/permissions_policy/policy_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/core/settings_base.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/generated/blink_live/gen/third_party/blink/renderer/platform/runtime_enabled_features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/cert/ct_sct_to_string.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/net/base/ip_endpoint.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/features.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/storage_key/storage_key.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/common/web_preferences/web_preferences.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/bindings/core/v8/capture_source_location.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/mailbox_ref.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/mailbox_texture_backing.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/skia/skia_utils.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/ad_tracker_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/cssom_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/binding_world_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/blob_registry_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/execution_context_browser_policy_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/fetch_phase1_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/font_face_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/font_phase1_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/document_write_intervention_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/memory_cache_tracing_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/memory_pressure_phase1_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/network_utils_data_url_phase1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/net_data_url_phase1_support.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/script_streaming_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/static_render_mime_phase1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/to_blink_string_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/v8_binding_for_core_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/v8_wrapper_type_info_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/web_font_decoder_phase1_unsupported.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/web_test_support_phase1.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/execution_context/execution_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/dom_exception.cc
  # CSSOM/IDL wrapper owners are intentionally outside the Phase 1 cc path.
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/media_values_cached.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/css/media_values.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/display_lock/display_lock_context.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/display_lock/display_lock_document_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/display_lock/display_lock_utilities.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/idleness_detector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/page_visibility_observer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/canvas/canvas_context_creation_attributes_core.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/canvas/canvas_rendering_context_host.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/canvas/canvas_resource_tracker.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/canvas/html_canvas_accessibility_manager.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/canvas/html_canvas_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/canvas/unique_font_selector.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_html_canvas.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/blocking_attribute.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_meta_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/link_rel_attribute.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/inspector/identifiers_factory.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/inspector/inspected_frames.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_embedded_content.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/lcp_critical_path_predictor/element_locator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/lcp_critical_path_predictor/lcp_critical_path_predictor.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/bindings/source_location.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/bindings/thread_debugger.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_custom_platform_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/font_platform_data.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/font_format_check.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/open_type_cpal_lookup.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/opentype/variable_axes_names.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/palette_interpolation.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/plain_text_node.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/plain_text_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/shaping/frame_shape_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/web_font_render_style.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/win/font_platform_data_win.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/canvas_child_paint_state.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/color_space_gamut.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/instrumentation/instance_counters.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/memory_cache.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/buffering_bytes_consumer.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/fetch_parameters.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/raw_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/loader/fetch/resource_fetcher.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/scheduler/common/worker_pool.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/web_bundle/script_web_bundle_rule.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/viewport_description.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/page/scrolling/scrolling_coordinator.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/html_canvas_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/test_report_body.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/visual_viewport.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/timing/worker_global_scope_performance.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/accelerated_static_bitmap_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/canvas_2d_color_params.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/canvas_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/graphics/canvas_resource_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/network/mime/mime_type_registry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/network/network_state_notifier.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/weborigin/origin_access_entry.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/weborigin/known_ports.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/weborigin/kurl.cc
)

set_source_files_properties(
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/fipsmodule/sha/sha1.cc.inc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/boringssl/src/crypto/fipsmodule/sha/sha256.cc.inc
  PROPERTIES
    LANGUAGE CXX)

set_source_files_properties(${BLINK_STANDALONE_BORINGSSL_HASH_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "OPENSSL_NO_ASM=1;STANDALONE_RENDERER_NO_BLINK_PREINCLUDE=1")

set(BLINK_STANDALONE_SKIA_PNG_WRITE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/encode/SkPngEncoder.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/encode/SkPngEncoderImpl.cpp
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwio.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwrite.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwtran.c
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/third_party/externals/libpng/pngwutil.c
)

set_source_files_properties(${BLINK_STANDALONE_SKIA_PNG_WRITE_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "PNG_WRITE_SUPPORTED=1;PNG_WRITE_CUSTOMIZE_COMPRESSION_SUPPORTED=1")

set_source_files_properties(${BLINK_STANDALONE_BASE_RUNTIME_SOURCES}
  PROPERTIES
    COMPILE_DEFINITIONS "STANDALONE_RENDERER_NEEDS_WIN_CALLBACK=1;STANDALONE_RENDERER_NO_BLINK_PREINCLUDE=1")

list(APPEND BLINK_STANDALONE_LIVE_SOURCES
  ${BLINK_STANDALONE_PROTOZERO_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_PROTOZERO_FILTERING_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_BASE_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_PROTOVM_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_TRACING_CORE_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_TRACING_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_TRACING_SERVICE_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_ANDROID_STATS_SOURCES}
  ${BLINK_STANDALONE_PERFETTO_GENERATED_SOURCES}
  ${BLINK_STANDALONE_BASE_TRACING_SOURCES}
  ${BLINK_STANDALONE_BLINK_TRACING_SOURCES}
  ${BLINK_STANDALONE_BLINK_INSPECTOR_OWNER_SOURCES}
  ${BLINK_STANDALONE_BLINK_PROBE_SOURCES}
  ${BLINK_STANDALONE_RE2_SOURCES}
  ${BLINK_STANDALONE_URL_PATTERN_SOURCES}
  ${BLINK_STANDALONE_LIBURLPATTERN_SOURCES}
  ${BLINK_STANDALONE_URL_PATTERN_INDEX_SOURCES}
  ${BLINK_STANDALONE_SUBRESOURCE_FILTER_SOURCES}
  ${BLINK_STANDALONE_INSPECTOR_PROTOCOL_SOURCES}
  ${BLINK_STANDALONE_BLINK_INSPECTOR_PROTOCOL_GENERATED_SOURCES}
  ${BLINK_STANDALONE_NETWORK_PUBLIC_MOJOM_VOCABULARY_SOURCES}
  ${BLINK_STANDALONE_UNSUPPORTED_POLICY_SOURCES}
  ${BLINK_STANDALONE_PHASE1_UNSUPPORTED_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_BLINK_MESSAGING_SOURCES}
  ${BLINK_STANDALONE_UNSUPPORTED_MESSAGING_SOURCES}
  ${BLINK_STANDALONE_FRAME_MOJOM_SUPPORT_SOURCES}
  ${BLINK_STANDALONE_POLICY_CONTAINER_SOURCES}
  ${BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_VOCABULARY_SOURCES}
  ${BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES}
  ${BLINK_STANDALONE_MOJOM_GENERATED_SOURCES}
  ${BLINK_STANDALONE_VIZ_BLINK_VALUE_MOJOM_SOURCES}
  ${BLINK_STANDALONE_UI_GL_MOJOM_GENERATED_SOURCES}
  ${BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES}
  ${BLINK_STANDALONE_CC_COMPOSITOR_SOURCES}
  ${BLINK_STANDALONE_CC_PHASE1_EXPLICIT_SOURCES}
  ${BLINK_STANDALONE_MOJO_BINDINGS_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_NATIVE_MOJOM_TRAIT_SOURCES}
  ${BLINK_STANDALONE_VIZ_COMMON_VALUE_SOURCES}
  ${BLINK_STANDALONE_VIZ_PUBLIC_CPP_MOJOM_TRAIT_SOURCES}
  ${BLINK_STANDALONE_VIZ_GPU_IMPORT_SOURCES}
  ${BLINK_STANDALONE_GPU_RUNTIME_IMPORT_SOURCES}
  ${BLINK_STANDALONE_UI_GL_RUNTIME_IMPORT_SOURCES}
  ${BLINK_STANDALONE_GFX_RANGE_SOURCES}
  ${BLINK_STANDALONE_UI_VALUE_SOURCES}
  ${BLINK_STANDALONE_VIZ_GPU_SUPPORT_SOURCES}
  ${BLINK_STANDALONE_BASE_JSON_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_SKIA_GPU_GANESH_VULKAN_SOURCES}
  ${BLINK_STANDALONE_SKIA_GRAPHITE_VULKAN_SOURCES}
  ${BLINK_STANDALONE_SKIA_GL_BACKEND_COMPAT_SOURCES}
  ${BLINK_STANDALONE_CRYPTO_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_BORINGSSL_HASH_SOURCES}
  ${BLINK_STANDALONE_BASE_RUNTIME_SOURCES}
  ${BLINK_STANDALONE_BLINK_RUNTIME_OWNER_SOURCES}
)

set(BLINK_STANDALONE_LIBYUV_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/compare.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/compare_common.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/convert.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/convert_argb.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/convert_from.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/convert_from_argb.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/convert_to_argb.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/convert_to_i420.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/cpu_id.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/planar_functions.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/rotate.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/rotate_any.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/rotate_argb.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/rotate_common.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/row_any.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/row_common.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/scale.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/scale_any.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/scale_argb.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/scale_common.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/scale_rgb.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/scale_uv.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/source/video_common.cc
)

set_source_files_properties(${BLINK_STANDALONE_LIBYUV_SOURCES}
  PROPERTIES
    INCLUDE_DIRECTORIES "${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/libyuv/include"
    COMPILE_DEFINITIONS "CHROMIUM;LIBYUV_DISABLE_X86;LIBYUV_DISABLE_NEON;LIBYUV_DISABLE_SVE;LIBYUV_DISABLE_SME;LIBYUV_DISABLE_RVV;LIBYUV_DISABLE_LSX;LIBYUV_DISABLE_LASX")

list(APPEND BLINK_STANDALONE_LIVE_SOURCES
  ${BLINK_STANDALONE_LIBYUV_SOURCES}
)

list(APPEND BLINK_STANDALONE_LIVE_SOURCES
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/standalone_resource_provider.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_image_fallback_helper.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_image_element.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/html_image_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/image_loader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/resource/image_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/resource/image_resource_content.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/loader/resource/multipart_image_resource_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/dom/presentation_attribute_style.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_image.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_image_resource.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_replaced.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/natural_sizing_info.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/replaced_layout_algorithm.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/image_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/paint/replaced_painter.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/html_meta_charset_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/text_resource_decoder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/html/parser/text_resource_decoder_builder.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/xml/parser/shared_buffer_reader.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/xml/parser/xhtml_subset.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/xml/parser/xml_document_parser.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/xml/parser/xml_document_parser_scope.cc
  ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/xml/parser/xml_errors.cc
)

if(NOT WIN32)
  list(APPEND BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/dispatcher/dispatcher.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/dispatcher/internal/dispatch_data.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/dispatcher/memory_tagging.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/allocator/dispatcher/tls.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/base_paths_standalone_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_enumerator_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_descriptor_watcher_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/file_util_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/memory_mapped_file_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/scoped_file.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/files/scoped_file_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/file_descriptor_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/elf_reader.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/debugger_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/debug/stack_trace_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/page_size_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/platform_shared_memory_handle.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/platform_shared_memory_mapper_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/platform_shared_memory_region_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/memory/protected_memory_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/message_pump_epoll.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/native_library_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/message_loop/watchable_io_message_pump_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/posix/global_descriptors.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/posix/can_lower_nice_to.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/internal_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/kill_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_iterator_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_iterator.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_handle_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_handle_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_metrics_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_metrics_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/process/process_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/profiler/module_cache_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/rand_util_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/safe_sprintf.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/strings/sys_string_conversions_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/posix/safe_strerror.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/condition_variable_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/synchronization/waitable_event_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/system/sys_info_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/system/sys_info_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread_internal_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread_linux_base.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/platform_thread_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/threading/thread_local_storage_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time_conversion_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time_exploded_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/time/time_now_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/base/timer/hi_res_timer_manager_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/config/gpu_info_collector_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/ipc/service/image_transport_surface_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/vulkan/vulkan_image_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/gpu/vulkan/vulkan_util_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/skia/ext/font_utils.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/font_support_standalone_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/gl_factory_standalone_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/native_pixmap_handle_standalone_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/skresources_standalone.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/standalone_renderer/src/native_presentation_standalone_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/platform/fonts/vdmx_parser.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/layout/layout_theme_linux.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/perfetto/src/tracing/platform_posix.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/base/SkTSearch.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkFontMgr_custom.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkFontMgr_custom_empty.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkFontHost_FreeType.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkFontHost_FreeType_common.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/ports/SkLog_stdio.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/skia/src/utils/SkCharToGlyphCache.cpp
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/gl_context_stub.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/gl_display.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/gl_surface_stub.cc
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/ui/gl/gl_fence_android_native_fence_sync.cc
  )
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "(/win/.*|_win|_win32)\\.(cc|cpp|c)$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "_win[^/]*\\.(cc|cpp|c)$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/components/viz/common/display/use_layered_window\\.cc$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/components/viz/service/display/overlay_processor_(delegated|ozone)\\.cc$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/components/viz/service/display/overlay_processor_delegated_support\\.cc$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/components/viz/service/display_embedder/output_device_backing\\.cc$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/components/viz/service/display_embedder/skia_output_device_dcomp\\.cc$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/gpu/ipc/common/device_perf_info\\.mojom")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/gpu/command_buffer/service/dxgi_")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/ui/gl/debug_utils\\.cc$")
  list(FILTER BLINK_STANDALONE_LIVE_SOURCES EXCLUDE REGEX
    "/ui/gl/(dc_layer|dcomp|direct_composition)")
  list(FILTER BLINK_STANDALONE_BLINK_PUBLIC_MOJOM_GENERATED_SOURCES EXCLUDE REGEX
    "(_win|_win32)\\.mojom")
  list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX
    "(_win|_win32)\\.mojom")
  list(FILTER BLINK_STANDALONE_MOJOM_GENERATED_SOURCES EXCLUDE REGEX
    "/gpu/ipc/common/device_perf_info\\.mojom")
  list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX
    "(_win|_win32)\\.mojom")
  list(FILTER BLINK_STANDALONE_GPU_MOJOM_GENERATED_SOURCES EXCLUDE REGEX
    "/gpu/ipc/common/device_perf_info\\.mojom")
  list(APPEND BLINK_STANDALONE_LIVE_SOURCES
    ${BLINK_STANDALONE_CHROMIUM_ROOT}/third_party/blink/renderer/core/frame/local_dom_window.cc
  )
endif()

list(REMOVE_DUPLICATES BLINK_STANDALONE_LIVE_SOURCES)
