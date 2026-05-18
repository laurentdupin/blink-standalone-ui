// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/loader/resource/css_style_sheet_resource.h"
#include "third_party/blink/renderer/core/css/style_sheet.h"
#include "third_party/blink/renderer/core/html/custom/ce_reactions_scope.h"
#include "third_party/blink/renderer/core/layout/mathml/math_fraction_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_padded_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_space_layout_algorithm.h"

#include "base/trace_event/trace_arguments.h"
#include "base/cpu.h"
#include "base/feature_list.h"
#include "base/metrics/field_trial_params.h"
#include "base/observer_list_types.h"
#include "base/metrics/histogram_functions.h"
#include "base/rand_util.h"
#include "base/run_loop.h"
#include "base/command_line.h"
#include "base/files/file_path.h"
#include "base/json/json_reader.h"
#include "base/allocator/partition_allocator/src/partition_alloc/shim/allocator_shim.h"
#include "base/memory/ref_counted_memory.h"
#include "base/memory/discardable_memory_allocator.h"
#include "base/synchronization/lock.h"
#include "base/trace_event/traced_value.h"
#include "base/time/default_tick_clock.h"
#include "base/sequence_checker.h"
#include "base/timer/elapsed_timer.h"
#include "base/timer/lap_timer.h"
#include "base/win/scoped_handle.h"
#include "base/allocator/partition_allocator/src/partition_alloc/allocation_guard.h"
#include "base/allocator/partition_allocator/src/partition_alloc/oom.h"
#if defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
#ifdef DrawText
#undef DrawText
#endif
#include "html_css_renderer/standalone_resource_provider.h"
#endif
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/frame/delegated_capability_request_token.h"
#include "third_party/blink/public/common/permissions_policy/document_policy.h"
#include "third_party/blink/public/common/permissions_policy/policy_value.h"
#include "third_party/blink/public/resources/grit/blink_resources.h"
#include "third_party/blink/public/common/thread_safe_browser_interface_broker_proxy.h"
#include "third_party/blink/public/platform/platform.h"
#include "third_party/blink/renderer/core/html_element_factory.h"
#include "third_party/blink/renderer/core/html/forms/form_data.h"
#include "third_party/blink/renderer/core/html/forms/html_data_list_element.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"
#include "third_party/blink/renderer/core/html/forms/html_options_collection.h"
#include "third_party/blink/renderer/core/html/forms/html_opt_group_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/html_selected_content_element.h"
#include "third_party/blink/renderer/core/html/html_script_element.h"
#include "third_party/blink/renderer/core/html/html_span_element.h"
#include "third_party/blink/renderer/core/html/html_style_element.h"
#include "third_party/blink/renderer/core/html/html_li_element.h"
#include "third_party/blink/renderer/core/html/html_olist_element.h"
#include "third_party/blink/renderer/core/html/html_ulist_element.h"
#include "third_party/blink/renderer/core/input/input_device_capabilities.h"
#include "third_party/blink/renderer/core/html/blocking_attribute.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_types_util.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_htmlscriptelement_svgscriptelement.h"
#include "third_party/blink/renderer/bindings/core/v8/active_script_wrappable_creation_key.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_mutation_observer_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_htmlelement_long.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_htmloptgroupelement_htmloptionelement.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_string_trustedscript.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_stringlegacynulltoemptystring_trustedscript.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_trustedscripturl_usvstring.h"
#include "third_party/blink/renderer/core/paint/css_mask_painter.h"
#include "third_party/blink/renderer/core/paint/svg_root_painter.h"
#include "third_party/blink/renderer/core/frame/window_properties.h"
#include "third_party/blink/renderer/core/timing/soft_navigation_paint_attribution_tracker.h"
#include "third_party/blink/renderer/core/dom/child_list_mutation_scope.h"
#include "services/metrics/public/cpp/mojo_ukm_recorder.h"
#include "services/metrics/public/cpp/ukm_recorder.h"
#include "services/metrics/public/cpp/delegating_ukm_recorder.h"
#include "services/network/public/cpp/connection_allowlist.h"
#include "services/network/public/cpp/integrity_policy.h"
#include "services/network/public/cpp/permissions_policy/permissions_policy.h"
#include "components/subresource_filter/core/common/scoped_rule.h"
#include "components/subresource_filter/core/common/memory_mapped_ruleset.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "third_party/abseil-cpp/absl/container/internal/hashtablez_sampler.h"
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <future>
#include <iostream>
#include <limits>
#include <map>
#include <malloc.h>
#include <new>
#include <ostream>
#include <string>
#include <tuple>
#include <utility>

#include "unicode/ubidi.h"
#include "unicode/uchar.h"
#include "third_party/skia/include/core/SkFlattenable.h"
#include "third_party/skia/src/shaders/SkLocalMatrixShader.h"
#include "third_party/skia/src/shaders/SkShaderBase.h"
#include "third_party/skia/src/shaders/gradients/SkGradientBaseShader.h"
#include "unicode/uscript.h"
#include "hb-ot.h"

extern "C" const char icudt78_dat[] = {0};

#include "cc/paint/paint_flags.h"
#include "cc/base/region.h"
#include "third_party/blink/renderer/platform/fonts/shaping/shape_result_bloberizer.h"
#include "third_party/blink/renderer/platform/fonts/font_unique_name_lookup.h"
#include "cc/debug/picture_debug_util.h"
#include "cc/paint/image_transfer_cache_entry.h"
#include "cc/paint/skottie_transfer_cache_entry.h"
#include "cc/paint/transfer_cache_serialize_helper.h"
#include "cc/paint/record_paint_canvas.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "mojo/public/cpp/bindings/lib/buffer.h"
#include "mojo/public/cpp/bindings/lib/validation_context.h"
#include "mojo/public/cpp/bindings/lib/validation_errors.h"
#include "mojo/public/cpp/bindings/message.h"
#include "skia/ext/draw_gainmap_image.h"
#include "skia/ext/legacy_display_globals.h"
#include "skia/ext/skia_utils_base.h"
#include "cc/animation/animation_host.h"
#include "cc/layers/layer.h"
#include "cc/layers/solid_color_scrollbar_layer.h"
#include "cc/trees/layer_tree_host.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkColorSpace.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkImage.h"
#if defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
#include "ui/gfx/geometry/skia_conversions.h"
#endif
#include "third_party/skia/include/core/SkStream.h"
#include "third_party/skia/include/ports/SkTypeface_win.h"
#include "third_party/skia/include/core/SkMesh.h"
#include "third_party/skia/include/core/SkPicture.h"
#include "third_party/skia/include/core/SkColorFilter.h"
#include "third_party/skia/include/effects/SkHighContrastFilter.h"
#include "third_party/skia/include/effects/SkLumaColorFilter.h"
#include "third_party/skia/include/effects/SkOverdrawColorFilter.h"
#include "third_party/skia/include/effects/SkRuntimeEffect.h"
#include "third_party/skia/include/gpu/ganesh/GrBackendSurface.h"
#include "third_party/skia/include/gpu/ganesh/GrDirectContext.h"
#include "third_party/skia/include/gpu/ganesh/GrRecordingContext.h"
#include "third_party/skia/include/gpu/ganesh/GrYUVABackendTextures.h"
#include "third_party/skia/include/gpu/ganesh/SkImageGanesh.h"
#include "third_party/skia/include/gpu/graphite/Image.h"
#include "third_party/skia/include/gpu/graphite/Recorder.h"
#include "third_party/skia/include/private/SkHdrMetadata.h"
#include "third_party/skia/include/private/chromium/SkChromeRemoteGlyphCache.h"
#include "third_party/skia/include/private/chromium/Slug.h"
#include "third_party/skia/include/utils/SkNullCanvas.h"
#include "third_party/skia/src/gpu/ganesh/GrBackendSurfacePriv.h"
#include "skia/public/mojom/hdr_metadata.mojom-shared-internal.h"
#include "skia/public/mojom/skcolorspace_primaries.mojom-shared-internal.h"
#include "ui/gfx/mojom/hdr_metadata_mojom_traits.h"
#include "ui/gfx/mojom/hdr_metadata.mojom-shared-internal.h"
#include "third_party/crashpad/crashpad/client/annotation.h"
#include "third_party/skia/modules/skottie/include/Skottie.h"
#include "third_party/skia/modules/skottie/include/SkottieProperty.h"
#include "third_party/skia/modules/skottie/src/SkottiePriv.h"
#include "third_party/skia/modules/skottie/src/Transform.h"
#include "third_party/skia/modules/skottie/src/text/TextAdapter.h"
#include "third_party/skia/modules/skresources/include/SkResources.h"
#include "third_party/skia/modules/skshaper/include/SkShaper_factory.h"
#include "ui/gfx/animation/tween.h"
#include "ui/gfx/color_utils.h"
#include "ui/gfx/color_space.h"
#include "ui/gfx/hdr_metadata.h"
#include "third_party/skia/modules/skcms/skcms.h"
#include "skia/ext/skcms_ext.h"
#include "third_party/skia/src/base/SkBuffer.h"
#include "third_party/skia/src/core/SkOSFile.h"
#include "third_party/skia/src/core/SkKnownRuntimeEffects.h"
#include "third_party/skia/src/core/SkMemset.h"
#include "third_party/skia/src/sksl/SkSLMemoryPool.h"
#include "third_party/skia/src/sksl/SkSLPool.h"
#include "third_party/skia/src/sksl/SkSLProgramSettings.h"
#include "third_party/skia/src/sksl/analysis/SkSLProgramUsage.h"
#include "third_party/skia/src/sksl/ir/SkSLProgram.h"
#include "third_party/skia/src/sksl/ir/SkSLProgramElement.h"
#include "third_party/skia/src/sksl/ir/SkSLSymbolTable.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_composite_operation.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_node_filter.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_timeline_range_offset.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_cssnumericvalue_double.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_cssnumericvalue_string.h"
#include "third_party/blink/renderer/core/animation/animation_timeline.h"
#include "third_party/blink/renderer/core/animation/animation.h"
#include "third_party/blink/renderer/core/animation/animation_input_helpers.h"
#include "third_party/blink/renderer/core/animation/animation_utils.h"
#include "third_party/blink/renderer/core/animation/compositor_animations.h"
#include "third_party/blink/renderer/core/animation/keyframe_effect.h"
#include "third_party/blink/renderer/core/animation/interpolation_types_map.h"
#include "third_party/blink/renderer/core/animation/length_property_functions.h"
#include "third_party/blink/renderer/core/animation/property_handle.h"
#include "third_party/blink/renderer/core/animation/css/css_animation.h"
#include "third_party/blink/renderer/core/animation/css/css_animations.h"
#include "third_party/blink/renderer/core/animation/css/compositor_keyframe_value_factory.h"
#include "third_party/blink/renderer/core/animation/document_timeline.h"
#include "third_party/blink/renderer/core/animation/document_animations.h"
#include "third_party/blink/renderer/core/animation/pending_animations.h"
#include "third_party/blink/renderer/core/animation/scroll_timeline_util.h"
#include "third_party/blink/renderer/core/animation/timeline_trigger.h"
#include "third_party/blink/renderer/core/animation/scroll_timeline.h"
#include "third_party/blink/renderer/core/animation/timing_input.h"
#include "third_party/blink/renderer/core/animation/timeline_range.h"
#include "third_party/blink/renderer/core/animation/timeline_offset.h"
#include "third_party/blink/renderer/core/animation/view_timeline.h"
#include "third_party/blink/renderer/core/animation/worklet_animation_controller.h"
#include "third_party/blink/renderer/core/ad_tracker/ad_tracker.h"
#include "third_party/blink/renderer/core/ad_tracker/overlay_interstitial_ad_detector.h"
#include "third_party/blink/renderer/core/ad_tracker/sticky_ad_detector.h"
#include "third_party/blink/public/web/extension_script_streamer.h"
#include "third_party/blink/renderer/bindings/core/v8/js_event_handler_for_content_attribute.h"
#include "third_party/blink/renderer/bindings/core/v8/js_based_event_listener.h"
#include "third_party/blink/renderer/bindings/core/v8/js_event_listener.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_throw_dom_exception.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_css_style_sheet.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_css_style_sheet_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_object_builder.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_event_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_focus_options.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_overscroll_event_init.h"
#include "third_party/blink/renderer/bindings/core/v8/script_promise_resolver.h"
#include "third_party/blink/renderer/bindings/core/v8/script_controller.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_observable_array_css_style_sheet.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_document_ready_state.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_shadow_root_mode.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_slot_assignment_mode.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_visibility_state.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_boolean_string_unrestricteddouble.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_boolean_scrollintoviewoptions.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_scroll_to_options.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_cssstylevalue_undefined.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_keyframeeffectoptions_unrestricteddouble.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_string_trustedhtml.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_urlpatterninit_usvstring.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_url_pattern_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_local_compile_hints_producer.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_compile_hints_producer.h"
#include "third_party/blink/renderer/bindings/core/v8/window_proxy_manager.h"
#include "third_party/blink/renderer/bindings/core/v8/binding_security.h"
#include "third_party/blink/renderer/bindings/core/v8/isolated_world_csp.h"
#include "third_party/blink/renderer/bindings/core/v8/world_safe_v8_reference.h"
#include "third_party/blink/public/platform/interface_registry.h"
#include "third_party/blink/public/web/web_frame.h"
#include "third_party/blink/renderer/core/css/css_default_style_sheets.h"
#include "third_party/blink/renderer/core/css/background_color_paint_image_generator.h"
#include "third_party/blink/renderer/core/css/box_shadow_paint_image_generator.h"
#include "third_party/blink/renderer/core/css/clip_path_paint_image_generator.h"
#include "third_party/blink/renderer/core/clipboard/system_clipboard.h"
#include "third_party/blink/renderer/core/content_capture/content_capture_manager.h"
#include "third_party/blink/renderer/core/css/style_media.h"
#include "third_party/blink/renderer/core/css/css_computed_style_declaration.h"
#include "third_party/blink/renderer/core/css/css_font_face_src_value.h"
#include "third_party/blink/renderer/core/css/css_font_selector.h"
#include "third_party/blink/renderer/core/css/css_crossfade_value.h"
#include "third_party/blink/renderer/core/css/css_image_set_value.h"
#include "third_party/blink/renderer/core/css/css_image_value.h"
#include "third_party/blink/renderer/core/css/css_paint_image_generator.h"
#include "third_party/blink/renderer/core/css/css_paint_value.h"
#include "third_party/blink/renderer/core/css/cssom/paint_worklet_deferred_image.h"
#include "third_party/blink/renderer/core/css/cssom/paint_worklet_input.h"
#include "third_party/blink/renderer/core/css/cssom/paint_worklet_style_property_map.h"
#include "third_party/blink/renderer/core/css/media_list.h"
#include "third_party/blink/renderer/core/css/media_values_cached.h"
#include "third_party/blink/renderer/core/css/media_query_exp.h"
#include "third_party/blink/renderer/core/css/media_query_evaluator.h"
#include "third_party/blink/renderer/core/css/media_values.h"
#include "third_party/blink/renderer/core/css/property_bitsets.h"
#include "third_party/blink/renderer/core/css/style_property_serializer.h"
#include "third_party/blink/renderer/core/css/css_property_value.h"
#include "third_party/blink/renderer/core/css/css_syntax_string_parser.h"
#include "third_party/blink/renderer/core/css/layout_upgrade.h"
#include "third_party/blink/renderer/core/css/media_feature_overrides.h"
#include "third_party/blink/renderer/core/css/media_query_matcher.h"
#include "third_party/blink/renderer/core/css/parser/at_rule_descriptor_parser.h"
#include "third_party/blink/renderer/core/css/parser/font_variant_alternates_parser.h"
#include "third_party/blink/renderer/core/css/parser/link_condition_parser.h"
#include "third_party/blink/renderer/core/css/properties/longhands/custom_property.h"
#include "third_party/blink/renderer/core/css/post_style_update_scope.h"
#include "third_party/blink/renderer/core/css/selector_checker.h"
#include "third_party/blink/renderer/core/css/selector_statistics.h"
#include "third_party/blink/renderer/core/css/selector_statistics_flag.h"
#include "third_party/blink/renderer/core/css/style_attribute_mutation_scope.h"
#include "third_party/blink/renderer/core/css/style_recalc_context.h"
#include "third_party/blink/renderer/core/css/resolver/element_style_resources.h"
#include "third_party/blink/renderer/platform/scheduler/public/agent_group_scheduler.h"
#include "third_party/blink/renderer/platform/scheduler/public/frame_scheduler.h"
#include "third_party/blink/renderer/platform/scheduler/public/main_thread.h"
#include "third_party/blink/renderer/platform/scheduler/public/main_thread_scheduler.h"
#include "third_party/blink/renderer/core/css/resolver/filter_operation_resolver.h"
#include "third_party/blink/renderer/core/css/invalidation/invalidation_flags.h"
#include "third_party/blink/renderer/core/css/invalidation/invalidation_tracing_flag.h"
#include "third_party/blink/renderer/core/css/invalidation/rule_invalidation_data_builder.h"
#include "third_party/blink/renderer/core/css/invalidation/rule_invalidation_data_tracer.h"
#include "third_party/blink/renderer/core/css/invalidation/style_invalidator.h"
#include "third_party/blink/renderer/core/css/css_import_rule.h"
#include "third_party/blink/renderer/core/css/css_keyframe_rule.h"
#include "third_party/blink/renderer/core/css/css_keyframes_rule.h"
#include "third_party/blink/renderer/core/css/css_container_values.h"
#include "third_party/blink/renderer/core/css/container_query_data.h"
#include "third_party/blink/renderer/core/css/counter_style_map.h"
#include "third_party/blink/renderer/core/css/css_position_try_descriptors.h"
#include "third_party/blink/renderer/core/css/css_position_try_rule.h"
#include "third_party/blink/renderer/core/css/css_rule.h"
#include "third_party/blink/renderer/core/css/css_rule_list.h"
#include "third_party/blink/renderer/core/css/css_style_sheet.h"
#include "third_party/blink/renderer/core/css/css_style_rule.h"
#include "third_party/blink/renderer/core/css/css_nested_declarations_rule.h"
#include "third_party/blink/renderer/core/css/link_condition.h"
#include "third_party/blink/renderer/core/css/scroll_state_query_snapshot.h"
#include "third_party/blink/renderer/core/css/snapped_query_scroll_snapshot.h"
#include "third_party/blink/renderer/core/css/vision_deficiency.h"
#include "third_party/blink/renderer/core/css/cssom/css_style_value.h"
#include "third_party/blink/renderer/core/css/cssom/cross_thread_unit_value.h"
#include "third_party/blink/renderer/core/css/cssom/cross_thread_unparsed_value.h"
#include "third_party/blink/renderer/core/css/cssom/cross_thread_unsupported_value.h"
#include "third_party/blink/renderer/core/css/cssom/css_keyword_value.h"
#include "third_party/blink/renderer/core/css/cssom/prepopulated_computed_style_property_map.h"
#include "third_party/blink/renderer/core/css/css_color_channel_keywords.h"
#include "third_party/blink/renderer/core/css/cssom/style_value_factory.h"
#include "third_party/blink/renderer/core/css/cssom/computed_style_property_map.h"
#include "third_party/blink/renderer/core/css/cssom/style_property_map_read_only.h"
#include "third_party/blink/renderer/core/css/cssom/style_property_map_read_only_main_thread.h"
#include "third_party/blink/renderer/core/css/cssom/style_property_map.h"
#include "third_party/blink/renderer/core/css/selector_query.h"
#include "third_party/blink/renderer/core/css/font_face_cache.h"
#include "third_party/blink/renderer/core/css/font_face.h"
#include "third_party/blink/renderer/core/css/font_face_set_document.h"
#include "third_party/blink/renderer/core/css/media_query_list.h"
#include "third_party/blink/renderer/core/css/media_query_list_listener.h"
#include "third_party/blink/renderer/core/css/css_selector_watch.h"
#include "third_party/blink/renderer/core/css/font_size_functions.h"
#include "third_party/blink/renderer/core/dom/pseudo_element.h"
#include "third_party/blink/renderer/core/dom/visited_link_state.h"
#include "third_party/blink/renderer/core/dom/abort_signal.h"
#include "third_party/blink/renderer/core/dom/frame_request_callback_collection.h"
#include "third_party/blink/renderer/core/dom/events/event_dispatch_forbidden_scope.h"
#include "third_party/blink/renderer/core/dom/events/scoped_event_queue.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_document_state.h"
#include "third_party/blink/renderer/core/editing/editing_behavior.h"
#include "third_party/blink/renderer/core/editing/ime/input_method_controller.h"
#include "third_party/blink/renderer/core/events/hash_change_event.h"
#include "third_party/blink/renderer/core/events/message_event.h"
#include "third_party/blink/renderer/core/events/page_transition_event.h"
#include "third_party/blink/renderer/core/events/pop_state_event.h"
#include "third_party/blink/renderer/core/execution_context/agent.h"
#include "third_party/blink/renderer/bindings/core/v8/rejected_promises.h"
#include "third_party/blink/renderer/core/execution_context/window_agent.h"
#include "third_party/blink/renderer/core/execution_context/window_agent_factory.h"
#include "third_party/blink/renderer/core/dom/document_init.h"
#include "third_party/blink/renderer/core/dom/document_parser.h"
#include "third_party/blink/renderer/core/frame/bar_prop.h"
#include "third_party/blink/renderer/core/frame/browser_controls.h"
#include "third_party/blink/renderer/core/frame/crash_report_context.h"
#include "third_party/blink/renderer/core/frame/document_policy_violation_report_body.h"
#include "third_party/blink/renderer/core/frame/dom_viewport.h"
#include "third_party/blink/renderer/core/frame/dom_visual_viewport.h"
#include "third_party/blink/renderer/core/frame/external.h"
#include "third_party/blink/renderer/core/frame/frame_lifecycle.h"
#include "third_party/blink/renderer/core/frame/history.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/navigator.h"
#include "third_party/blink/renderer/core/frame/navigation_rate_limiter.h"
#include "third_party/blink/renderer/core/frame/opened_frame_tracker.h"
#include "third_party/blink/renderer/core/frame/page_scale_constraints_set.h"
#include "third_party/blink/renderer/core/frame/policy_container.h"
#include "third_party/blink/renderer/core/frame/permissions_policy_violation_report_body.h"
#include "third_party/blink/renderer/core/frame/report.h"
#include "third_party/blink/renderer/core/frame/report_body.h"
#include "third_party/blink/renderer/core/frame/reporting_context.h"
#include "third_party/blink/renderer/core/frame/screen.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/settings_base.h"
#include "third_party/blink/renderer/core/html/fenced_frame/fence.h"
#include "third_party/blink/renderer/core/html/fenced_frame/document_fenced_frames.h"
#include "third_party/blink/renderer/core/html/custom/custom_element_registry.h"
#include "third_party/blink/renderer/core/navigation_api/navigation_api.h"
#include "third_party/blink/renderer/core/paint/timing/first_meaningful_paint_detector.h"
#include "third_party/blink/renderer/core/preferences/navigator_preferences.h"
#include "third_party/blink/renderer/core/preferences/preference_manager.h"
#include "third_party/blink/renderer/core/preferences/preference_overrides.h"
#include "third_party/blink/renderer/core/scroll/scrollbar_theme.h"
#include "third_party/blink/renderer/core/scroll/scrollbar_theme_overlay_mobile.h"
#include "third_party/blink/renderer/core/page/scrolling/sync_scroll_attempt_heuristic.h"
#include "third_party/blink/renderer/core/editing/drag_caret.h"
#include "third_party/blink/renderer/core/inspector/console_message_storage.h"
#include "third_party/blink/renderer/core/page/autoscroll_controller.h"
#include "third_party/blink/renderer/core/page/context_menu_controller.h"
#include "third_party/blink/renderer/core/page/drag_controller.h"
#include "third_party/blink/renderer/core/page/link_highlight.h"
#include "third_party/blink/renderer/core/page/page_animator.h"
#include "third_party/blink/renderer/core/page/page_visibility_observer.h"
#include "third_party/blink/renderer/core/page/plugin_data.h"
#include "third_party/blink/renderer/core/page/pointer_lock_controller.h"
#include "third_party/blink/renderer/core/page/scoped_browsing_context_group_pauser.h"
#include "third_party/blink/renderer/core/page/scoped_page_pauser.h"
#include "third_party/blink/renderer/core/page/scrolling/scrolling_coordinator.h"
#include "third_party/blink/renderer/core/page/spatial_navigation_controller.h"
#include "third_party/blink/renderer/core/page/validation_message_client_impl.h"
#include "third_party/blink/renderer/core/paint/link_highlight_impl.h"
#include "third_party/blink/renderer/core/svg/svg_document_resource_tracker.h"
#include "third_party/blink/renderer/core/svg/svg_resource_scheduler_registry.h"
#include "third_party/blink/renderer/core/sanitizer/sanitizer.h"
#include "third_party/blink/public/platform/resource_load_info_notifier_wrapper.h"
#include "third_party/blink/public/platform/modules/service_worker/web_service_worker_network_provider.h"
#include "third_party/blink/public/web/web_navigation_params.h"
#include "third_party/blink/renderer/core/timing/dom_window_performance.h"
#include "third_party/blink/renderer/platform/scheduler/public/thread.h"
#include "third_party/blink/renderer/platform/testing/unit_test_helpers.h"
#include "third_party/blink/renderer/platform/testing/url_loader_mock_factory.h"
#include "ui/base/cursor/cursor.h"
#include "ui/color/color_mixer.h"
#include "ui/color/color_provider_utils.h"
#include "ui/color/color_provider.h"
#include "ui/color/color_recipe.h"
#include "ui/display/screen_info.h"
#include "ui/display/screen_infos.h"
#include "third_party/blink/renderer/core/timing/event_timing.h"
#include "third_party/blink/renderer/core/timing/window_performance.h"
#include "third_party/blink/renderer/core/timing/soft_navigation_heuristics.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_type_policy_factory.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_supplement.h"
#include "third_party/blink/renderer/platform/back_forward_cache_buffer_limit_tracker.h"
#include "third_party/blink/renderer/platform/web_test_support.h"
#include "third_party/blink/renderer/platform/scheduler/public/feature_and_js_location_blocking_bfcache.h"
#include "third_party/blink/renderer/platform/weborigin/security_policy.h"
#include "third_party/blink/renderer/core/typed_arrays/array_buffer/array_buffer_contents.h"
#include "third_party/blink/renderer/core/dom/abort_signal_registry.h"
#include "third_party/blink/renderer/core/dom/comment.h"
#include "third_party/blink/renderer/core/dom/document_fragment.h"
#include "third_party/blink/renderer/core/dom/document_type.h"
#include "third_party/blink/renderer/core/dom/document_encoding_data.h"
#include "third_party/blink/renderer/core/dom/document_parser_timing.h"
#include "third_party/blink/renderer/core/dom/document_timing.h"
#include "third_party/blink/renderer/core/dom/cdata_section.h"
#include "third_party/blink/renderer/core/dom/name_node_list.h"
#include "third_party/blink/renderer/core/dom/class_collection.h"
#include "third_party/blink/renderer/core/dom/transform_source.h"
#include "third_party/blink/renderer/core/dom/xml_document.h"
#include "third_party/blink/renderer/core/dom/dom_implementation.h"
#include "third_party/blink/renderer/core/html/custom/custom_element.h"
#include "third_party/blink/renderer/core/html/custom/custom_element_registry.h"
#include "third_party/blink/renderer/core/dom/mutation_observer.h"
#include "third_party/blink/renderer/core/dom/mutation_record.h"
#include "third_party/blink/renderer/core/dom/mutation_observer_registration.h"
#include "third_party/blink/renderer/core/dom/observable.h"
#include "third_party/blink/renderer/core/dom/qualified_name.h"
#include "third_party/blink/renderer/core/dom/first_letter_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/subscriber.h"
#include "third_party/blink/renderer/core/dom/visited_link_state.h"
#include "third_party/blink/renderer/core/dom/dataset_dom_string_map.h"
#include "third_party/blink/renderer/core/dom/attr.h"
#include "third_party/blink/renderer/core/dom/dom_node_ids.h"
#include "third_party/blink/renderer/core/dom/dom_token_list.h"
#include "third_party/blink/renderer/core/dom/child_list_mutation_scope.h"
#include "third_party/blink/renderer/core/dom/beforeunload_event_listener.h"
#include "third_party/blink/renderer/core/dom/element_animation_trigger_data.h"
#include "third_party/blink/renderer/core/dom/element_data_cache.h"
#include "third_party/blink/renderer/core/dom/icon_url.h"
#include "third_party/blink/renderer/core/dom/live_node_list_registry.h"
#include "third_party/blink/renderer/core/dom/scripted_animation_controller.h"
#include "third_party/blink/renderer/core/dom/flat_tree_node_data.h"
#include "third_party/blink/renderer/core/dom/named_node_map.h"
#include "third_party/blink/renderer/core/dom/column_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/scroll_marker_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/scroll_marker_group_pseudo_element.h"
#include "third_party/blink/renderer/core/dom/node_lists_node_data.h"
#include "third_party/blink/renderer/core/dom/node_iterator.h"
#include "third_party/blink/renderer/core/dom/tree_walker.h"
#include "third_party/blink/renderer/core/dom/node_child_removal_tracker.h"
#include "third_party/blink/renderer/core/dom/range.h"
#include "third_party/blink/renderer/core/dom/invalidate_node_list_caches_scope.h"
#include "third_party/blink/renderer/core/dom/events/event_path.h"
#include "third_party/blink/renderer/core/dom/events/event_dispatcher.h"
#include "third_party/blink/renderer/core/dom/events/add_event_listener_options_resolved.h"
#include "third_party/blink/renderer/core/dom/events/event_listener_map.h"
#include "third_party/blink/renderer/core/dom/events/scoped_event_queue.h"
#include "third_party/blink/renderer/core/dom/events/tree_scope_event_context.h"
#include "third_party/blink/renderer/core/css/resolver/style_adjuster.h"
#include "third_party/blink/renderer/core/dom/processing_instruction.h"
#include "third_party/blink/renderer/core/dom/mutation_observer_interest_group.h"
#include "third_party/blink/renderer/core/dom/scroll_marker_group_data.h"
#include "third_party/blink/renderer/core/dom/text_diff_range.h"
#include "third_party/blink/renderer/core/editing/serializers/markup_accumulator.h"
#include "third_party/blink/renderer/core/editing/dom_selection.h"
#include "third_party/blink/renderer/core/editing/frame_selection.h"
#include "third_party/blink/renderer/core/editing/ime/edit_context.h"
#include "third_party/blink/renderer/core/editing/set_selection_options.h"
#include "third_party/blink/renderer/core/editing/selection_template.h"
#include "third_party/blink/renderer/core/editing/visible_selection.h"
#include "third_party/blink/renderer/core/editing/position_with_affinity.h"
#include "third_party/blink/renderer/core/editing/editing_utilities.h"
#include "third_party/blink/renderer/core/editing/editor.h"
#include "third_party/blink/renderer/core/editing/drag_caret.h"
#include "third_party/blink/renderer/core/editing/granularity_strategy.h"
#include "third_party/blink/renderer/core/editing/kill_ring.h"
#include "third_party/blink/renderer/core/editing/markers/document_marker_controller.h"
#include "third_party/blink/renderer/core/editing/commands/undo_stack.h"
#include "third_party/blink/renderer/core/editing/spellcheck/spell_checker.h"
#include "third_party/blink/renderer/core/events/animation_event.h"
#include "third_party/blink/renderer/core/events/command_event.h"
#include "third_party/blink/renderer/core/events/error_event.h"
#include "third_party/blink/renderer/core/events/focus_event.h"
#include "third_party/blink/renderer/core/events/interest_event.h"
#include "third_party/blink/renderer/core/events/before_unload_event.h"
#include "third_party/blink/renderer/core/events/visual_viewport_resize_event.h"
#include "third_party/blink/renderer/core/events/visual_viewport_scroll_event.h"
#include "third_party/blink/renderer/core/events/visual_viewport_scrollend_event.h"
#include "third_party/blink/renderer/core/events/event_util.h"
#include "third_party/blink/renderer/core/events/keyboard_event.h"
#include "third_party/blink/renderer/core/events/mouse_event.h"
#include "third_party/blink/renderer/core/events/text_event.h"
#include "third_party/blink/renderer/core/events/toggle_event.h"
#include "third_party/blink/renderer/core/events/transition_event.h"
#include "third_party/blink/renderer/core/events/ui_event.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/execution_context/execution_context_lifecycle_observer.h"
#include "third_party/blink/renderer/core/execution_context/execution_context_lifecycle_state_observer.h"
#include "third_party/blink/renderer/core/fileapi/public_url_manager.h"
#include "third_party/blink/renderer/core/fullscreen/fullscreen.h"
#include "third_party/blink/renderer/core/fragment_directive/fragment_directive.h"
#include "third_party/blink/renderer/core/fragment_directive/text_fragment_handler.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_context.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_utilities.h"
#include "third_party/blink/renderer/core/frame/embedded_content_view.h"
#include "third_party/blink/renderer/core/frame/frame_console.h"
#include "third_party/blink/renderer/core/frame/frame.h"
#include "third_party/blink/renderer/core/frame/frame_view.h"
#include "third_party/blink/renderer/core/frame/frame_view_auto_size_info.h"
#include "third_party/blink/renderer/core/frame/frame_overlay.h"
#include "third_party/blink/renderer/core/frame/pagination_state.h"
#include "third_party/blink/renderer/core/frame/remote_frame_view.h"
#include "third_party/blink/renderer/core/frame/root_frame_viewport.h"
#include "third_party/blink/renderer/core/frame/smart_clip.h"
#include "third_party/blink/renderer/core/frame/visual_viewport.h"
#include "third_party/blink/renderer/core/frame/local_frame_ukm_aggregator.h"
#include "third_party/blink/renderer/core/frame/local_frame_mojo_handler.h"
#include "third_party/blink/renderer/core/frame/pausable_script_executor.h"
#include "third_party/blink/renderer/core/loader/frame_load_request.h"
#include "third_party/blink/renderer/core/frame/csp/content_security_policy.h"
#include "third_party/blink/renderer/core/frame/intervention.h"
#include "third_party/blink/renderer/core/frame/page_dismissal_scope.h"
#include "third_party/blink/renderer/core/frame/event_handler_registry.h"
#include "third_party/blink/renderer/core/frame/picture_in_picture_controller.h"
#include "third_party/blink/renderer/core/html/closewatcher/close_watcher.h"
#include "third_party/blink/renderer/core/dom/child_frame_disconnector.h"
#include "third_party/blink/renderer/core/page/plugin_script_forbidden_scope.h"
#include "third_party/blink/renderer/core/html/html_anchor_element.h"
#include "third_party/blink/renderer/core/html/anchor_element_viewport_position_tracker.h"
#include "third_party/blink/renderer/core/html/html_stream.h"
#include "third_party/blink/renderer/core/html/html_all_collection.h"
#include "third_party/blink/renderer/core/html/html_document.h"
#include "third_party/blink/renderer/core/html_element_factory.h"
#include "third_party/blink/renderer/core/svg_element_factory.h"
#include "third_party/blink/renderer/core/mathml_element_factory.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html/html_dialog_element.h"
#include "third_party/blink/renderer/core/html/canvas/canvas_font_cache.h"
#include "third_party/blink/renderer/core/html/media/lazy_load_media_observer.h"
#include "third_party/blink/renderer/core/html/html_menu_item_element.h"
#include "third_party/blink/renderer/core/html/html_quote_element.h"
#include "third_party/blink/renderer/core/html/html_link_element.h"
#include "third_party/blink/renderer/core/html/html_image_element.h"
#include "third_party/blink/renderer/core/html/html_meta_element.h"
#include "third_party/blink/renderer/core/html/html_body_element.h"
#include "third_party/blink/renderer/core/html/html_frame_owner_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/html/html_html_element.h"
#include "third_party/blink/renderer/core/html/html_br_element.h"
#include "third_party/blink/renderer/core/html/html_div_element.h"
#include "third_party/blink/renderer/core/html/html_heading_element.h"
#include "third_party/blink/renderer/core/html/html_paragraph_element.h"
#include "third_party/blink/renderer/core/html/html_title_element.h"
#include "third_party/blink/renderer/core/html/html_unknown_element.h"
#include "third_party/blink/renderer/core/html/custom/element_internals.h"
#include "third_party/blink/renderer/core/html/display_ad_element_monitor.h"
#include "third_party/blink/renderer/core/html/menu_safe_triangle.h"
#include "third_party/blink/renderer/core/html/forms/html_form_control_element.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"
#include "third_party/blink/renderer/core/html/html_summary_element.h"
#include "third_party/blink/renderer/core/html/forms/html_input_element.h"
#include "third_party/blink/renderer/core/html/forms/html_data_list_element.h"
#include "third_party/blink/renderer/core/html/forms/html_label_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/forms/html_opt_group_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/slider_thumb_element.h"
#include "third_party/blink/renderer/core/html/forms/option_list.h"
#include "third_party/blink/renderer/core/html/forms/html_submit_button_behavior.h"
#include "third_party/blink/renderer/core/html/forms/autofill_event.h"
#include "third_party/blink/renderer/core/html/forms/email_input_type.h"
#include "third_party/blink/renderer/core/html/forms/form_controller.h"
#include "third_party/blink/renderer/core/html/forms/labels_node_list.h"
#include "third_party/blink/renderer/core/html/forms/radio_button_group_scope.h"
#include "third_party/blink/renderer/core/html/forms/radio_node_list.h"
#include "third_party/blink/renderer/core/html/forms/listed_element.h"
#include "third_party/blink/renderer/core/html/html_br_element.h"
#include "third_party/blink/renderer/core/html/html_collection.h"
#include "third_party/blink/renderer/core/html/html_embed_element.h"
#include "third_party/blink/renderer/core/html/html_html_element.h"
#include "third_party/blink/renderer/core/html/html_object_element.h"
#include "third_party/blink/renderer/core/html/html_plugin_element.h"
#include "third_party/blink/renderer/core/html/html_slot_element.h"
#include "third_party/blink/renderer/core/html/html_template_element.h"
#include "third_party/blink/renderer/core/html/parser/fragment_parser.h"
#include "third_party/blink/renderer/core/html/parser/html_document_parser_fastpath.h"
#include "third_party/blink/renderer/core/html/parser/background_html_scanner.h"
#include "third_party/blink/renderer/core/html/parser/html_document_parser.h"
#include "third_party/blink/renderer/core/html/parser/html_parser_metrics.h"
#include "third_party/blink/renderer/core/html/parser/html_preload_scanner.h"
#include "third_party/blink/renderer/core/html/parser/html_resource_preloader.h"
#include "third_party/blink/renderer/core/html/parser/resource_preloader.h"
#include "third_party/blink/renderer/core/highlight/highlight_registry.h"
#include "third_party/blink/renderer/core/input/event_handler.h"
#include "third_party/blink/renderer/core/input/mouse_event_manager.h"
#include "third_party/blink/renderer/core/input/pointer_event_manager.h"
#include "third_party/blink/renderer/core/inspector/inspector_audits_issue.h"
#include "third_party/blink/renderer/core/inspector/inspector_issue_reporter.h"
#include "third_party/blink/renderer/core/inspector/inspector_trace_events.h"
#include "third_party/blink/renderer/core/inspector/identifiers_factory.h"
#include "third_party/blink/renderer/core/inspector/invalidation_set_to_selector_map.h"
#include "third_party/blink/renderer/core/probe/core_probes.h"
#include "third_party/blink/renderer/core/inspector/style_rule_to_style_sheet_contents_map.h"
#include "third_party/blink/renderer/core/exported/web_plugin_container_impl.h"
#include "third_party/blink/renderer/core/layout/custom/layout_worklet.h"
#include "third_party/blink/renderer/core/layout/traced_layout_object.h"
#include "third_party/blink/renderer/core/layout/anchor_position_scroll_data.h"
#include "third_party/blink/renderer/core/layout/anchor_position_visibility_observer.h"
#include "third_party/blink/renderer/core/layout/layout_counter.h"
#include "third_party/blink/renderer/core/layout/layout_image.h"
#include "third_party/blink/renderer/core/layout/layout_image_resource.h"
#include "third_party/blink/renderer/core/layout/layout_image_resource_style_image.h"
#include "third_party/blink/renderer/core/layout/layout_br.h"
#include "third_party/blink/renderer/core/layout/layout_embedded_content.h"
#include "third_party/blink/renderer/core/layout/grid/grid_line_resolver.h"
#include "third_party/blink/renderer/core/layout/grid/layout_grid.h"
#include "third_party/blink/renderer/core/layout/grid_lanes/layout_grid_lanes.h"
#include "third_party/blink/renderer/core/layout/layout_shift_tracker.h"
#include "third_party/blink/renderer/core/layout/layout_replaced.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_inline_text.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_root.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_text.h"
#include "third_party/blink/renderer/core/layout/svg/transform_helper.h"
#include "third_party/blink/renderer/core/layout/svg/svg_layout_support.h"
#include "third_party/blink/renderer/core/layout/svg/svg_resources.h"
#include "third_party/blink/renderer/core/layout/layout_text_fragment.h"
#include "third_party/blink/renderer/core/layout/anchor_map.h"
#include "third_party/blink/renderer/core/layout/anchor_scope.h"
#include "third_party/blink/renderer/core/layout/fragmentation_utils.h"
#include "third_party/blink/renderer/core/layout/forms/layout_fieldset.h"
#include "third_party/blink/renderer/core/layout/forms/layout_text_control.h"
#include "third_party/blink/renderer/core/layout/disable_layout_side_effects_scope.h"
#include "third_party/blink/renderer/core/layout/gap/gap_geometry.h"
#include "third_party/blink/renderer/core/layout/ink_overflow.h"
#include "third_party/blink/renderer/core/layout/measure_cache.h"
#include "third_party/blink/renderer/core/layout/relative_utils.h"
#include "third_party/blink/renderer/core/layout/scrollable_overflow_calculator.h"
#include "third_party/blink/renderer/core/layout/layout_result.h"
#include "third_party/blink/renderer/core/layout/list/list_marker.h"
#include "third_party/blink/renderer/core/layout/layout_counter.h"
#include "third_party/blink/renderer/core/layout/table/layout_table_cell.h"
#include "third_party/blink/renderer/core/layout/table/table_borders.h"
#include "third_party/blink/renderer/core/layout/physical_box_fragment.h"
#include "third_party/blink/renderer/core/layout/physical_fragment.h"
#include "third_party/blink/renderer/core/layout/pointer_events_hit_rules.h"
#include "third_party/blink/renderer/core/layout/shapes/shape_outside_info.h"
#include "third_party/blink/renderer/core/paint/fragment_data.h"
#include "third_party/blink/renderer/core/paint/block_paint_invalidator.h"
#include "third_party/blink/renderer/core/paint/box_paint_invalidator.h"
#include "third_party/blink/renderer/core/paint/background_image_geometry.h"
#include "third_party/blink/renderer/core/paint/box_fragment_painter.h"
#include "third_party/blink/renderer/core/paint/custom_scrollbar_theme.h"
#include "third_party/blink/renderer/core/paint/decoration_line_painter.h"
#include "third_party/blink/renderer/core/paint/fieldset_paint_info.h"
#include "third_party/blink/renderer/core/paint/highlight_painter.h"
#include "third_party/blink/renderer/core/paint/line_relative_rect.h"
#include "third_party/blink/renderer/core/paint/mathml_painter.h"
#include "third_party/blink/renderer/core/paint/nine_piece_image_grid.h"
#include "third_party/blink/renderer/core/paint/paint_auto_dark_mode.h"
#include "third_party/blink/renderer/core/paint/rounded_inner_rect_clipper.h"
#include "third_party/blink/renderer/core/paint/clip_path_clipper.h"
#include "third_party/blink/renderer/core/paint/svg_mask_painter.h"
#include "third_party/blink/renderer/core/paint/svg_object_painter.h"
#include "third_party/blink/renderer/core/paint/outline_painter.h"
#include "third_party/blink/renderer/core/paint/selection_bounds_recorder.h"
#include "third_party/blink/renderer/core/paint/text_combine_painter.h"
#include "third_party/blink/renderer/core/paint/text_decoration_painter.h"
#include "third_party/blink/renderer/core/paint/text_overflow_post_layout_snapshot.h"
#include "third_party/blink/renderer/core/paint/theme_painter_default.h"
#include "third_party/blink/renderer/core/paint/inline_paint_context.h"
#include "third_party/blink/renderer/platform/fonts/text_fragment_paint_info.h"
#include "third_party/blink/renderer/platform/fonts/shaping/shape_result_view.h"
#include "third_party/blink/renderer/platform/fonts/font_global_context.h"
#include "third_party/blink/renderer/platform/fonts/opentype/open_type_caps_support.h"
#include "third_party/blink/renderer/platform/fonts/opentype/open_type_features.h"
#include "third_party/blink/renderer/platform/fonts/shaping/harfbuzz_face.h"
#include "third_party/blink/renderer/core/layout/column_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/frame_set_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/forms/fieldset_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/custom/custom_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/custom/custom_layout_child.h"
#include "third_party/blink/renderer/core/layout/custom/layout_worklet.h"
#include "third_party/blink/renderer/core/layout/custom/layout_worklet_global_scope_proxy.h"
#include "third_party/blink/renderer/core/layout/flex/flex_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/grid/grid_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/grid_lanes/grid_lanes_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_operator_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_radical_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_row_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_scripts_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_token_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_under_over_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/replaced_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/paginated_root_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/out_of_flow_layout_part.h"
#include "third_party/blink/renderer/core/layout/fragment_repeater.h"
#include "third_party/blink/renderer/core/layout/transform_utils.h"
#include "third_party/blink/renderer/core/layout/table/table_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/table/layout_table_section.h"
#include "third_party/blink/renderer/core/layout/table/table_row_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/table/table_section_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/list/layout_list_marker_image.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_viewport_container.h"
#include "third_party/blink/renderer/core/layout/svg/svg_text_layout_algorithm.h"
#include "third_party/blink/renderer/core/style/fit_text.h"
#include "third_party/blink/renderer/core/editing/bidi_adjustment.h"
#include "third_party/blink/renderer/core/editing/drag_caret.h"
#include "third_party/blink/renderer/core/editing/ime/input_method_controller.h"
#include "third_party/blink/renderer/core/dom/first_letter_pseudo_element.h"
#include "third_party/blink/renderer/core/html/html_marquee_element.h"
#include "third_party/blink/renderer/core/highlight/highlight_style_utils.h"
#include "third_party/blink/renderer/core/layout/inline/caret_rect.h"
#include "third_party/blink/renderer/core/layout/inline/inline_caret_position.h"
#include "third_party/blink/renderer/core/paint/marker_range_mapping_context.h"
#include "third_party/blink/renderer/core/paint/text_decoration_info.h"
#include "third_party/blink/renderer/core/mathml/mathml_radical_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_fraction_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_operator_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_padded_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_space_element.h"
#include "third_party/blink/renderer/platform/fonts/shaping/shape_result_spacing.h"
#include "third_party/blink/renderer/platform/fonts/shaping/ng_shape_cache.h"
#include "third_party/blink/renderer/platform/text/character_break_iterator.h"
#include "third_party/blink/renderer/platform/text/text_break_iterator.h"
#include "third_party/blink/renderer/core/paint/pre_paint_disable_side_effects_scope.h"
#include "third_party/blink/renderer/platform/graphics/paint/geometry_mapper.h"
#include "third_party/blink/renderer/core/paint/object_paint_invalidator.h"
#include "third_party/blink/renderer/core/style/style_mask_source_image.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/layout/layout_view_transition_root.h"
#include "third_party/blink/renderer/core/layout/depth_ordered_layout_object_list.h"
#include "third_party/blink/renderer/core/layout/list/layout_inline_list_item.h"
#include "third_party/blink/renderer/core/layout/list/layout_list_item.h"
#include "third_party/blink/renderer/core/html/list_item_ordinal.h"
#include "third_party/blink/renderer/core/html/html_olist_element.h"
#include "third_party/blink/renderer/core/loader/frame_loader.h"
#include "third_party/blink/renderer/core/loader/http_refresh_scheduler.h"
#include "third_party/blink/renderer/core/loader/cookie_jar.h"
#include "third_party/blink/renderer/core/loader/document_loader.h"
#include "third_party/blink/renderer/core/loader/idleness_detector.h"
#include "third_party/blink/renderer/core/loader/pending_link_preload.h"
#include "third_party/blink/renderer/core/loader/progress_tracker.h"
#include "third_party/blink/renderer/core/loader/render_blocking_element_link_map.h"
#include "third_party/blink/renderer/core/loader/resource/image_resource_content.h"
#include "third_party/blink/renderer/core/loader/resource/font_resource.h"
#include "third_party/blink/renderer/core/loader/resource/text_resource.h"
#include "third_party/blink/renderer/core/loader/render_blocking_resource_manager.h"
#include "third_party/blink/renderer/core/accessibility/ax_object_cache.h"
#include "third_party/blink/renderer/core/lcp_critical_path_predictor/lcp_critical_path_predictor.h"
#include "third_party/blink/renderer/core/timing/soft_navigation_heuristics.h"
#include "third_party/blink/renderer/core/loader/lazy_image_helper.h"
#include "third_party/blink/renderer/core/loader/prefetched_signed_exchange_manager.h"
#include "third_party/blink/renderer/core/loader/preload_helper.h"
#include "third_party/blink/renderer/core/loader/frame_fetch_context.h"
#include "third_party/blink/renderer/core/loader/no_state_prefetch_client.h"
#include "third_party/blink/renderer/core/loader/interactive_detector.h"
#include "third_party/blink/renderer/core/layout/inline/fragment_item.h"
#include "third_party/blink/renderer/core/layout/inline/inline_cursor.h"
#include "third_party/blink/renderer/core/layout/inline/abstract_inline_text_box.h"
#include "third_party/blink/renderer/core/layout/inline/offset_mapping.h"
#include "third_party/blink/renderer/core/layout/layout_text_combine.h"
#include "third_party/blink/renderer/core/layout/layout_progress.h"
#include "third_party/blink/renderer/core/html/html_progress_element.h"
#include "third_party/blink/renderer/core/page/page_popup_controller.h"
#include "third_party/blink/renderer/core/scroll/snap_event.h"
#include "third_party/blink/renderer/core/layout/hit_test_result.h"
#include "third_party/blink/renderer/core/script/html_parser_script_runner.h"
#include "third_party/blink/renderer/core/script/html_parser_script_runner_host.h"
#include "third_party/blink/renderer/platform/scheduler/public/non_main_thread.h"
#include "mojo/public/cpp/bindings/lib/interface_ptr_state.h"
#include "mojo/public/cpp/base/big_buffer.h"
#include "services/metrics/public/mojom/ukm_interface.mojom.h"
#include "third_party/blink/renderer/core/page/context_menu_controller.h"
#include "third_party/blink/renderer/core/page/page_animator.h"
#include "third_party/blink/renderer/core/page/pointer_lock_controller.h"
#include "third_party/blink/renderer/core/page/focusgroup_controller_utils.h"
#include "third_party/blink/renderer/core/page/scrolling/root_scroller_controller.h"
#include "third_party/blink/renderer/core/page/scrolling/sticky_position_scrolling_constraints.h"
#include "third_party/blink/renderer/core/scroll/scrollbar_layer_delegate.h"
#include "third_party/blink/renderer/core/frame/deprecation/deprecation.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_context.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_document_state.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_utilities.h"
#include "third_party/blink/renderer/core/paint/compositing/compositing_reason_finder.h"
#include "third_party/blink/renderer/core/paint/paint_layer_scrollable_area.h"
#include "third_party/blink/renderer/core/paint/cull_rect_updater.h"
#include "third_party/blink/renderer/core/paint/paint_layer.h"
#include "third_party/blink/renderer/core/paint/paint_layer_painter.h"
#include "third_party/blink/renderer/core/paint/frame_painter.h"
#include "third_party/blink/renderer/core/paint/filter_effect_builder.h"
#include "third_party/blink/renderer/core/paint/pre_paint_tree_walk.h"
#include "third_party/blink/renderer/core/paint/paint_property_tree_builder.h"
#include "third_party/blink/renderer/core/paint/timing/paint_timing_detector.h"
#include "third_party/blink/renderer/core/paint/timing/image_element_timing.h"
#include "third_party/blink/renderer/core/paint/timing/first_meaningful_paint_detector.h"
#include "third_party/blink/renderer/core/page/link_highlight.h"
#include "third_party/blink/renderer/core/page/scrolling/scrolling_coordinator.h"
#include "third_party/blink/renderer/core/page/scrolling/top_document_root_scroller_controller.h"
#include "third_party/blink/renderer/core/page/scrolling/fragment_anchor.h"
#include "third_party/blink/renderer/core/page/scrolling/snap_coordinator.h"
#include "third_party/blink/renderer/core/paint/timing/paint_timing.h"
#include "third_party/blink/renderer/core/mobile_metrics/mobile_friendliness_checker.h"
#include "third_party/blink/renderer/core/mobile_metrics/tap_friendliness_checker.h"
#include "third_party/blink/renderer/core/resize_observer/resize_observer_controller.h"
#include "third_party/blink/renderer/core/editing/serializers/serialization.h"
#include "third_party/blink/renderer/core/editing/serializers/create_markup_options.h"
#include "third_party/blink/renderer/core/editing/layout_selection.h"
#include "third_party/blink/renderer/core/editing/frame_selection.h"
#include "third_party/blink/renderer/core/editing/visible_position.h"
#include "third_party/blink/renderer/core/editing/visible_units.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_types_util.h"
#include "ui/base/cursor/cursor.h"
#include "third_party/blink/renderer/core/paint/timing/container_timing.h"
#include "third_party/blink/renderer/core/layout/layout_theme.h"
#include "third_party/blink/renderer/core/layout/layout_theme_default.h"
#include "third_party/blink/renderer/core/layout/table/layout_table_cell.h"
#include "third_party/blink/renderer/core/layout/layout_theme_font_provider.h"
#include "third_party/blink/renderer/platform/theme/web_theme_engine_helper.h"
#include "third_party/blink/renderer/core/layout/custom_scrollbar.h"
#include "third_party/blink/renderer/platform/fonts/font.h"
#include "third_party/blink/renderer/platform/fonts/font_fallback_list.h"
#include "third_party/blink/renderer/platform/fonts/plain_text_painter.h"
#include "third_party/blink/renderer/platform/fonts/simple_font_data.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_image_cache.h"
#include "third_party/blink/renderer/platform/graphics/generated_image.h"
#include "third_party/blink/renderer/platform/graphics/gradient.h"
#include "third_party/blink/renderer/platform/graphics/gradient_generated_image.h"
#include "third_party/blink/renderer/platform/graphics/image.h"
#include "third_party/blink/renderer/platform/text/layout_locale.h"
#include "third_party/blink/renderer/platform/wtf/text/text_codec_cjk.h"
#include "third_party/blink/renderer/platform/wtf/text/text_codec_icu.h"
#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"
#include "third_party/blink/renderer/platform/timer.h"
#include "ui/gfx/geometry/quaternion.h"
#include "third_party/blink/renderer/core/permissions_policy/dom_feature_policy.h"
#include "third_party/blink/renderer/core/accessibility/ax_context.h"
#include "third_party/blink/renderer/core/overscroll/overscroll_area_tracker.h"
#include "third_party/blink/renderer/core/overscroll/overscroll_event.h"
#include "third_party/blink/renderer/core/resize_observer/resize_observation.h"
#include "third_party/blink/renderer/core/resize_observer/resize_observer.h"
#include "third_party/blink/renderer/core/speculation_rules/document_speculation_rules.h"
#include "third_party/blink/renderer/core/route_matching/route.h"
#include "third_party/blink/renderer/core/route_matching/route_map.h"
#include "third_party/blink/renderer/core/script/modulator.h"
#include "third_party/blink/renderer/core/script/script_runner.h"
#include "third_party/blink/renderer/core/script/script_loader.h"
#include "third_party/blink/renderer/core/sanitizer/sanitizer_api.h"
#include "third_party/blink/renderer/core/script_tools/model_context.h"
#include "third_party/blink/renderer/core/script_tools/model_context_supplement.h"
#include "third_party/blink/renderer/core/scroll/scroll_alignment.h"
#include "third_party/blink/renderer/core/scroll/programmatic_scroll_animator.h"
#include "third_party/blink/renderer/core/scroll/scroll_animator_compositor_coordinator.h"
#include "third_party/blink/renderer/core/scroll/scroll_animator_base.h"
#include "third_party/blink/renderer/core/scroll/scroll_into_view_util.h"
#include "third_party/blink/renderer/core/scroll/snap_event.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/content_data.h"
#include "third_party/blink/renderer/core/style/filter_operation.h"
#include "third_party/blink/renderer/core/style/style_path.h"
#include "third_party/blink/renderer/core/style/filter_operation.h"
#include "third_party/blink/renderer/core/style/style_fetched_image.h"
#include "third_party/blink/renderer/core/style/style_image_set.h"
#include "third_party/blink/renderer/core/style/style_trigger_attachment.h"
#include "third_party/blink/renderer/core/css/cssom/css_unit_value.h"
#include "third_party/blink/renderer/core/dom/css_pseudo_element.h"
#include "third_party/blink/renderer/core/timing/performance.h"
#include "third_party/blink/renderer/core/timing/render_blocking_metrics_reporter.h"
#include "third_party/blink/renderer/core/timing/soft_navigation_heuristics.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_script.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_types_util.h"
#include "third_party/blink/renderer/core/frame/performance_monitor.h"
#include "third_party/blink/renderer/core/frame/location_report_body.h"
#include "third_party/blink/renderer/core/frame/permissions_policy_violation_report_body.h"
#include "third_party/blink/renderer/core/html/plugin_document.h"
#include "third_party/blink/renderer/core/inspector/inspector_task_runner.h"
#include "third_party/blink/renderer/core/inspector/inspector_audits_issue.h"
#include "third_party/blink/renderer/core/inspector/inspector_issue_storage.h"
#include "third_party/blink/renderer/core/inspector/main_thread_debugger.h"
#include "third_party/blink/renderer/core/loader/document_load_timing.h"
#include "third_party/blink/renderer/core/geometry/dom_rect_list.h"
#include "third_party/blink/renderer/core/view_transition/view_transition.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_style_tracker.h"
#include "third_party/blink/renderer/platform/bindings/exception_state.h"
#include "third_party/blink/renderer/platform/graphics/compositing/paint_artifact_compositor.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_image_classifier.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_under_invalidation_checker.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_recorder.h"
#include "third_party/blink/renderer/platform/json/json_values.h"
#include "third_party/blink/renderer/platform/network/network_utils.h"
#include "third_party/blink/renderer/platform/bindings/v8_histogram_accumulator.h"
#include "third_party/blink/renderer/platform/blob/blob_data.h"
#include "third_party/blink/renderer/platform/mojo/browser_interface_broker_proxy_impl.h"
#include "third_party/blink/renderer/core/geometry/dom_rect.h"
#include "third_party/blink/renderer/core/css/cssom/caret_position.h"
#include "third_party/blink/renderer/core/intersection_observer/element_intersection_observer_data.h"
#include "third_party/blink/renderer/core/intersection_observer/intersection_observer_controller.h"
#include "third_party/blink/renderer/platform/bindings/callback_interface_base.h"
#include "third_party/blink/renderer/core/svg/svg_length_functions.h"
#include "third_party/blink/renderer/core/svg/graphics/svg_image.h"
#include "third_party/blink/renderer/core/svg/svg_path_builder.h"
#include "third_party/blink/renderer/core/svg/svg_resource.h"
#include "third_party/blink/renderer/core/svg/svg_animated_href.h"
#include "third_party/blink/renderer/core/svg/svg_element.h"
#include "third_party/blink/renderer/core/svg/svg_graphics_element.h"
#include "third_party/blink/renderer/core/svg/svg_resource.h"
#include "third_party/blink/renderer/core/svg/svg_use_element.h"
#include "third_party/blink/renderer/core/svg/svg_title_element.h"
#include "third_party/blink/renderer/core/svg/svg_unknown_element.h"
#include "third_party/blink/renderer/core/svg/svg_document_extensions.h"
#include "third_party/blink/renderer/core/svg/svg_tree_scope_resources.h"
#include "third_party/blink/renderer/core/url_pattern/url_pattern.h"
#include "third_party/blink/renderer/core/view_transition/view_transition.h"
#include "third_party/blink/renderer/core/view_transition/page_reveal_event.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_transition_element.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_utils.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_pseudo_element_base.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_supplement.h"
#include "third_party/blink/renderer/core/xml/parser/xml_document_parser.h"
#include "third_party/blink/renderer/platform/fonts/font_metrics.h"
#include "third_party/blink/renderer/platform/fonts/font_cache.h"
#include "third_party/blink/renderer/platform/fonts/font_performance.h"
#include "third_party/blink/renderer/platform/fonts/font_platform_data.h"
#include "third_party/blink/renderer/platform/fonts/opentype/open_type_math_support.h"
#include "third_party/blink/renderer/platform/fonts/simple_font_data.h"
#include "third_party/blink/renderer/platform/graphics/filters/filter.h"
#include "third_party/blink/renderer/platform/graphics/filters/filter_effect.h"
#include "third_party/blink/renderer/platform/graphics/filters/fe_gaussian_blur.h"
#include "third_party/blink/renderer/platform/graphics/filters/fe_drop_shadow.h"
#include "third_party/blink/renderer/platform/graphics/graphics_context.h"
#include "third_party/blink/renderer/platform/graphics/graphics_context_types.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_filter.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_color_filter.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_color_classifier.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_image_classifier.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_settings.h"
#include "third_party/blink/renderer/platform/graphics/draw_looper_builder.h"
#include "third_party/blink/renderer/platform/graphics/main_thread_mutator_client.h"
#include "third_party/blink/renderer/platform/geometry/stroke_data.h"
#include "third_party/blink/renderer/platform/heap/thread_state.h"
#include "third_party/blink/renderer/platform/bindings/frozen_array_base.h"
#include "third_party/blink/renderer/platform/instrumentation/instance_counters.h"
#include "third_party/blink/renderer/platform/instrumentation/histogram.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/traced_value.h"
#include "third_party/blink/renderer/platform/instrumentation/resource_coordinator/document_resource_coordinator.h"
#include "third_party/blink/renderer/platform/loader/fetch/memory_cache.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_parameters.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"
#include "third_party/blink/public/common/loader/referrer_utils.h"
#include "third_party/blink/renderer/platform/bindings/runtime_call_stats.h"
#include "third_party/blink/renderer/platform/bindings/script_regexp.h"
#include "third_party/blink/renderer/platform/bindings/parkable_string.h"
#include "third_party/blink/renderer/platform/fonts/font_performance.h"
#include "third_party/blink/renderer/platform/graphics/compositing/paint_artifact_compositor.h"
#include "base/memory_coordinator/memory_consumer.h"
#include "base/memory_coordinator/memory_consumer_registry.h"
#include "base/task/single_thread_task_runner.h"
#include "third_party/blink/renderer/platform/instrumentation/memory_coordinator/memory_consumer_registration.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_controller.h"
#include "third_party/blink/renderer/platform/graphics/paint/display_item_list.h"
#include "third_party/blink/renderer/platform/graphics/logging_canvas.h"
#include "cc/input/layer_selection_bound.h"
#include "cc/input/main_thread_scrolling_reason.h"
#include "cc/layers/scrollbar_layer_base.h"
#include "cc/trees/property_tree.h"
#include "components/viz/common/surfaces/region_capture_bounds.h"
#include "cc/view_transition/view_transition_request.h"
#include "perfetto/tracing/internal/track_event_internal.h"
#include "perfetto/tracing/track_event_legacy.h"
#include "perfetto/tracing/traced_value.h"
#include "v8/include/v8-traced-handle.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher_properties.h"
#include "third_party/blink/renderer/platform/loader/fetch/null_resource_fetcher_properties.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_request.h"
#include "third_party/blink/renderer/platform/loader/fetch/script_fetch_options.h"
#include "third_party/blink/renderer/platform/loader/integrity_report.h"
#include "third_party/blink/renderer/platform/loader/subresource_integrity.h"
#include "third_party/blink/renderer/platform/network/http_names.h"
#include "third_party/blink/renderer/platform/network/encoded_form_data.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/bindings/wrapper_type_info.h"
#include "third_party/blink/renderer/platform/bindings/v8_per_isolate_data.h"
#include "third_party/blink/renderer/platform/bindings/dom_wrapper_world.h"
#include "third_party/blink/renderer/platform/bindings/v8_dom_activity_logger.h"
#include "third_party/blink/renderer/platform/text/character.h"
#include "third_party/blink/renderer/platform/text/layout_locale.h"
#include "third_party/blink/renderer/platform/text/quotes_data.h"
#include "third_party/blink/renderer/platform/text/platform_locale.h"
#include "third_party/blink/renderer/platform/text/hyphenation.h"
#include "third_party/blink/renderer/platform/wtf/text/case_map.h"
#include "third_party/blink/renderer/platform/wtf/text/text_encoding.h"
#include "third_party/blink/renderer/platform/weborigin/referrer.h"
#include "third_party/blink/renderer/platform/weborigin/origin_access_entry.h"
#include "third_party/blink/renderer/platform/scheduler/public/event_loop.h"
#include "third_party/blink/renderer/platform/scheduler/public/post_cancellable_task.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"
#include "cc/input/scroll_snap_data.h"
#include "ui/native_theme/native_theme.h"
#include "unicode/timezone.h"

#if !defined(HTML_CSS_RENDERER_STANDALONE) && \
    !defined(STANDALONE_RENDERER_GN_PROBE)
void sk_free(void* p) { std::free(p); }

void* sk_malloc_flags(size_t size, unsigned flags) {
  void* p = (flags & 1u) ? std::calloc(1, size) : std::malloc(size);
  if (!p && size != 0 && (flags & 2u)) {
    std::abort();
  }
  return p;
}

void* sk_realloc_throw(void* p, size_t size) {
  void* result = std::realloc(p, size);
  if (!result && size != 0) {
    std::abort();
  }
  return result;
}

size_t sk_malloc_size(void*, size_t size) { return size; }

void SkDebugf_FileLine(const char*, int, const char* format, ...) {
  va_list args;
  va_start(args, format);
  std::vfprintf(stderr, format, args);
  va_end(args);
}

void SkAbort_FileLine(const char*, int, const char* format, ...) {
  va_list args;
  va_start(args, format);
  std::vfprintf(stderr, format, args);
  va_end(args);
  std::abort();
}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
void* sk_realloc_throw(void* p, size_t count, size_t elem_size) {
  if (elem_size != 0 && count > std::numeric_limits<size_t>::max() / elem_size) {
    std::abort();
  }
  return sk_realloc_throw(p, count * elem_size);
}

bool sk_double_nearly_zero(double value) {
  return value > -1e-12 && value < 1e-12;
}

bool sk_doubles_nearly_equal_ulps(double a, double b, unsigned char) {
  return sk_double_nearly_zero(a - b);
}

void* sk_fmmap(FILE*, size_t*) {
  return nullptr;
}

void sk_fmunmap(const void*, size_t) {}

void* sk_fdmmap(int, size_t*) {
  return nullptr;
}

size_t sk_qread(FILE* file, void* buffer, size_t count, size_t offset) {
  if (!file) {
    return 0;
  }
  std::fseek(file, static_cast<long>(offset), SEEK_SET);
  return std::fread(buffer, 1, count, file);
}

void sk_fsync(FILE*) {}

bool sk_exists(const char*, SkFILE_Flags) {
  return false;
}

void SkPath::dump(SkWStream*, bool) const {}

bool SkRBuffer::read(void* buffer, size_t size) {
  if (size > available()) {
    fValid = false;
    return false;
  }
  if (buffer && size) {
    std::memcpy(buffer, fPos, size);
  }
  fPos += size;
  return true;
}

void SkWBuffer::writeNoSizeCheck(const void* buffer, size_t size) {
  if (fStop && fPos + size > fStop) {
    fPos = fStop;
    return;
  }
  if (buffer && fData) {
    std::memcpy(fPos, buffer, size);
  }
  fPos += size;
}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
FILE* sk_fopen(const char* path, SkFILE_Flags flags) {
  const char* mode = (flags & kWrite_SkFILE_Flag) ? "wb" : "rb";
  return std::fopen(path, mode);
}

void sk_fclose(FILE* file) {
  if (file) {
    std::fclose(file);
  }
}

size_t sk_ftell(FILE* file) {
  if (!file) {
    return 0;
  }
  long current = std::ftell(file);
  return current < 0 ? 0 : static_cast<size_t>(current);
}

size_t sk_fgetsize(FILE* file) {
  if (!file) {
    return 0;
  }
  long current = std::ftell(file);
  std::fseek(file, 0, SEEK_END);
  long end = std::ftell(file);
  std::fseek(file, current, SEEK_SET);
  return end < 0 ? 0 : static_cast<size_t>(end);
}

size_t sk_fwrite(const void* buffer, size_t size, FILE* file) {
  return file ? std::fwrite(buffer, 1, size, file) : 0;
}

void sk_fflush(FILE* file) {
  if (file) {
    std::fflush(file);
  }
}
#endif

#if defined(HTML_CSS_RENDERER_STANDALONE)
void* sk_fmmap(FILE*, size_t*) {
  return nullptr;
}

void sk_fmunmap(const void*, size_t) {}

void* sk_fdmmap(int, size_t*) {
  return nullptr;
}

FILE* sk_fopen(const char*, SkFILE_Flags) {
  return nullptr;
}

void sk_fclose(FILE*) {}
size_t sk_qread(FILE*, void*, size_t, size_t) {
  return 0;
}
void sk_fsync(FILE*) {}
size_t sk_ftell(FILE*) {
  return 0;
}
size_t sk_fgetsize(FILE*) {
  return 0;
}
size_t sk_fwrite(const void*, size_t, FILE*) {
  return 0;
}
void sk_fflush(FILE*) {}
void SkPath::dump(SkWStream*, bool) const {}
#endif

namespace v8 {
namespace internal {
class SharedObjectConveyorHandles {};
}  // namespace internal

bool Value::IsPromise() const {
  return false;
}

Maybe<bool> Promise::Resolver::Resolve(Local<Context>, Local<Value>) {
  return Just(false);
}

MaybeLocal<Promise::Resolver> Promise::Resolver::New(Local<Context>) {
  return MaybeLocal<Promise::Resolver>();
}

Maybe<bool> Promise::Resolver::Reject(Local<Context>, Local<Value>) {
  return Just(false);
}

MaybeLocal<Array> Array::New(Local<Context>,
                             size_t,
                             std::function<MaybeLocal<Value>()>) {
  return MaybeLocal<Array>();
}

SharedValueConveyor::~SharedValueConveyor() = default;

namespace api_internal {
void ToLocalEmpty() {}
}  // namespace api_internal
}  // namespace v8

namespace perfetto {
TracedValue::~TracedValue() = default;
TracedValue::TracedValue(TracedValue&&) = default;
TracedValue TracedValue::CreateFromProto(
    protos::pbzero::DebugAnnotation* annotation,
    EventContext* event_context) {
  return TracedValue(annotation, event_context, nullptr);
}
EventContext::~EventContext() = default;
protos::pbzero::DebugAnnotation* EventContext::AddDebugAnnotation(
    const char*) {
  return nullptr;
}
namespace internal {
void DataSourceType::PopulateTlsInst(DataSourceInstanceThreadLocalState*,
                                     DataSourceState*,
                                     uint32_t) {}
void DataSourceType::ClearIncrementalState(
    DataSourceInstanceThreadLocalState*,
    uint32_t,
    uint32_t) {}
TraceTimestamp TrackEventInternal::GetTraceTime() {
  return TraceTimestamp{0, 0};
}
void TrackEventInternal::ResetIncrementalState(
    TraceWriterBase*,
    TrackEventIncrementalState*,
    const TrackEventTlsState&,
    const TraceTimestamp&) {}
EventContext TrackEventInternal::WriteEvent(
    TraceWriterBase*,
    TrackEventIncrementalState*,
    TrackEventTlsState&,
    const Category*,
    protos::pbzero::TrackEvent::Type,
    const TraceTimestamp&,
    bool) {
  return EventContext(static_cast<protos::pbzero::TrackEvent*>(nullptr));
}
void TrackEventInternal::WriteEventName(StaticString,
                                        EventContext&,
                                        const TrackEventTlsState&) {}
protozero::MessageHandle<protos::pbzero::TracePacket>
TrackEventInternal::NewTracePacket(TraceWriterBase*,
                                   TrackEventIncrementalState*,
                                   const TrackEventTlsState&,
                                   TraceTimestamp,
                                   uint32_t) {
  return protozero::MessageHandle<protos::pbzero::TracePacket>();
}
TrackRegistry* TrackRegistry::instance_ = nullptr;
void TrackRegistry::WriteTrackDescriptor(
    const std::string&,
    protozero::MessageHandle<protos::pbzero::TracePacket>) {}
TracedValue CreateTracedValueFromProto(protos::pbzero::DebugAnnotation*,
                                       EventContext*) {
  return TracedValue::CreateFromProto(nullptr);
}
}  // namespace internal
void Track::Serialize(protos::pbzero::TrackDescriptor*) const {}
}  // namespace perfetto

namespace protozero {
void Message::EndNestedMessage() {}
Message* Message::BeginNestedMessageInternal(uint32_t) {
  return nullptr;
}
uint32_t Message::Finalize() {
  return 0;
}
void ScatteredStreamWriter::WriteBytesSlowPath(const uint8_t*, size_t) {}
}  // namespace protozero

namespace v8 {
TryCatch::TryCatch(Isolate*) {}
TryCatch::~TryCatch() {}
bool TryCatch::HasCaught() const {
  return false;
}
Local<Value> TryCatch::ReThrow() {
  return Local<Value>();
}
}  // namespace v8

namespace SkCodecs {
bool HasDecoder(std::string_view) {
  return true;
}
}  // namespace SkCodecs

namespace blink {
CEReactionsScope* CEReactionsScope::top_of_stack_ = nullptr;
CEReactionsScope* CEReactionsScope::Current() {
  return top_of_stack_;
}
CEReactionsScope::CEReactionsScope(v8::Isolate* isolate)
    : prev_(top_of_stack_), try_catch_(isolate) {
  top_of_stack_ = this;
}
CEReactionsScope::~CEReactionsScope() {
  top_of_stack_ = prev_;
}
void CEReactionsScope::EnqueueToCurrentQueue(CustomElementReactionStack&,
                                             Element&,
                                             CustomElementReaction&) {}
void MutationObserver::CancelInspectorAsyncTasks() {}
}  // namespace blink

namespace cppgc::internal {
PrefinalizerRegistration::PrefinalizerRegistration(void*, Callback) {}
PersistentRegion& StandalonePersistentRegion() {
  static HeapBase* heap = reinterpret_cast<HeapBase*>(1);
  static FatalOutOfMemoryHandler* oom =
      reinterpret_cast<FatalOutOfMemoryHandler*>(1);
  alignas(PersistentRegion) static unsigned char storage[sizeof(PersistentRegion)];
  static PersistentRegion* region = ::new (storage) PersistentRegion(*heap, *oom);
  return *region;
}
PersistentRegion& WeakPersistentPolicy::GetPersistentRegion(const void*) {
  return StandalonePersistentRegion();
}
}  // namespace cppgc::internal

namespace network::cors {
#if !defined(STANDALONE_RENDERER_GN_PROBE)
OriginAccessEntry::OriginAccessEntry(
    const std::string& protocol,
    const std::string& domain,
    const uint16_t port,
    const mojom::CorsDomainMatchMode domain_match_mode,
    const mojom::CorsPortMatchMode port_match_mode,
    const mojom::CorsOriginAccessMatchPriority priority)
    : protocol_(protocol),
      host_(domain),
      port_(port),
      domain_match_mode_(domain_match_mode),
      port_match_mode_(port_match_mode),
      priority_(priority),
      host_is_ip_address_(false),
      host_is_public_suffix_(false) {}
#endif
}  // namespace network::cors

namespace network {
ConnectionAllowlist::~ConnectionAllowlist() = default;
ConnectionAllowlists::ConnectionAllowlists() = default;
ConnectionAllowlists::~ConnectionAllowlists() = default;
IntegrityPolicy::~IntegrityPolicy() = default;
PermissionsPolicy::Allowlist::~Allowlist() = default;
PermissionsPolicy::~PermissionsPolicy() = default;
PermissionsPolicyFeaturesBitset::~PermissionsPolicyFeaturesBitset() = default;
}  // namespace network

namespace net::registry_controlled_domains {
bool SameDomainOrHost(const url::Origin&,
                      const url::Origin&,
                      PrivateRegistryFilter) {
  return false;
}
}  // namespace net::registry_controlled_domains

namespace base {
namespace debug {
StackTrace::StackTrace() = default;
StackTrace::StackTrace(size_t) {}
StackTrace::StackTrace(span<const void* const>) {}
#if BUILDFLAG(IS_WIN)
StackTrace::StackTrace(_EXCEPTION_POINTERS*) {}
StackTrace::StackTrace(const _CONTEXT*) {}
#endif
bool StackTrace::WillSymbolizeToStreamForTesting() {
  return false;
}
void StackTrace::InitializeFeatures() {}
void StackTrace::Print() const {}
void StackTrace::PrintWithPrefix(cstring_view) const {}
void StackTrace::OutputToStream(std::ostream*) const {}
void StackTrace::OutputToStreamWithPrefix(std::ostream*, cstring_view) const {}
std::string StackTrace::ToString() const {
  return std::string();
}
std::string StackTrace::ToStringWithPrefix(cstring_view) const {
  return std::string();
}
void StackTrace::SuppressStackTracesWithMessageForTesting(std::string) {}
}  // namespace debug

namespace internal {
LinkNodeBase::LinkNodeBase() = default;
LinkNodeBase::LinkNodeBase(LinkNodeBase* previous, LinkNodeBase* next)
    : previous_(previous), next_(next) {}
LinkNodeBase::LinkNodeBase(LinkNodeBase&& rhs)
    : previous_(rhs.previous_), next_(rhs.next_) {
  if (previous_) {
    previous_->next_ = this;
  }
  if (next_) {
    next_->previous_ = this;
  }
  rhs.previous_ = &rhs;
  rhs.next_ = &rhs;
}
void LinkNodeBase::RemoveFromList() {
  if (previous_) {
    previous_->next_ = next_;
  }
  if (next_) {
    next_->previous_ = previous_;
  }
  previous_ = nullptr;
  next_ = nullptr;
}
void LinkNodeBase::InsertBeforeBase(LinkNodeBase* e) {
  previous_ = e->previous_;
  next_ = e;
  e->previous_->next_ = this;
  e->previous_ = this;
}
void LinkNodeBase::InsertAfterBase(LinkNodeBase* e) {
  next_ = e->next_;
  previous_ = e;
  e->next_->previous_ = this;
  e->next_ = this;
}
void LinkNodeBase::MakeSelfReferencingBase() {
  previous_ = this;
  next_ = this;
}
CheckedObserverAdapter::CheckedObserverAdapter(const CheckedObserver* observer)
    : weak_ptr_(const_cast<CheckedObserver*>(observer)->factory_.GetWeakPtr()) {}
CheckedObserverAdapter::CheckedObserverAdapter(CheckedObserverAdapter&& other) =
    default;
CheckedObserverAdapter& CheckedObserverAdapter::operator=(
    CheckedObserverAdapter&& other) = default;
CheckedObserverAdapter::~CheckedObserverAdapter() = default;
}  // namespace internal

TaskRunner::TaskRunner() = default;
TaskRunner::~TaskRunner() = default;
void TaskRunner::OnDestruct() const {
  delete this;
}
DelayedTaskHandle SequencedTaskRunner::PostCancelableDelayedTask(
    subtle::PostDelayedTaskPassKey,
    const Location&,
    OnceClosure,
    TimeDelta) {
  return DelayedTaskHandle();
}
DelayedTaskHandle SequencedTaskRunner::PostCancelableDelayedTaskAt(
    subtle::PostDelayedTaskPassKey,
    const Location&,
    OnceClosure,
    TimeTicks,
    subtle::DelayPolicy) {
  return DelayedTaskHandle();
}
bool SequencedTaskRunner::PostDelayedTaskAt(subtle::PostDelayedTaskPassKey,
                                           const Location&,
                                           OnceClosure,
                                           TimeTicks,
                                           subtle::DelayPolicy) {
  return true;
}
bool SequencedTaskRunner::RunOrPostTask(subtle::RunOrPostTaskPassKey,
                                        const Location&,
                                        OnceClosure task) {
  if (task) {
    std::move(task).Run();
  }
  return true;
}
bool SequencedTaskRunner::DeleteOrReleaseSoonInternal(
    const Location&,
    void (*deleter)(const void*),
    const void* object) {
  if (deleter && object) {
    deleter(object);
  }
  return true;
}
bool SingleThreadTaskRunner::BelongsToCurrentThread() const {
  return RunsTasksInCurrentSequence();
}
}  // namespace base

namespace blink {
extern "C" bool g_standalone_blink_saw_font_draw_text = false;
extern "C" int g_standalone_blink_viewport_width = 800;
extern "C" int g_standalone_blink_viewport_height = 600;

namespace {
int g_image_resource_content_fetch_called = 0;
int g_layout_image_set_resource_called = 0;
int g_layout_image_resource_initialize_called = 0;
int g_layout_image_resource_set_resource_called = 0;
int g_layout_image_resource_natural_dimensions_called = 0;
int g_layout_image_resource_get_image_called = 0;
std::string g_image_resource_content_fetch_last_url;
}  // namespace

extern "C" void StandaloneRendererResetImageReachabilityDiagnostics() {
  g_image_resource_content_fetch_called = 0;
  g_layout_image_set_resource_called = 0;
  g_layout_image_resource_initialize_called = 0;
  g_layout_image_resource_set_resource_called = 0;
  g_layout_image_resource_natural_dimensions_called = 0;
  g_layout_image_resource_get_image_called = 0;
  g_image_resource_content_fetch_last_url.clear();
}

extern "C" void StandaloneRendererNoteImageResourceContentFetch(
    const char* url) {
  ++g_image_resource_content_fetch_called;
  g_image_resource_content_fetch_last_url = url ? url : "";
}

extern "C" void StandaloneRendererNoteLayoutImageSetResource() {
  ++g_layout_image_set_resource_called;
}

extern "C" void StandaloneRendererNoteLayoutImageResourceInitialize() {
  ++g_layout_image_resource_initialize_called;
}

extern "C" void StandaloneRendererNoteLayoutImageResourceSetResource() {
  ++g_layout_image_resource_set_resource_called;
}

extern "C" void StandaloneRendererNoteLayoutImageResourceNaturalDimensions() {
  ++g_layout_image_resource_natural_dimensions_called;
}

extern "C" void StandaloneRendererNoteLayoutImageResourceGetImage() {
  ++g_layout_image_resource_get_image_called;
}

extern "C" int StandaloneRendererImageResourceContentFetchCalled() {
  return g_image_resource_content_fetch_called;
}

extern "C" int StandaloneRendererLayoutImageSetResourceCalled() {
  return g_layout_image_set_resource_called;
}

extern "C" int StandaloneRendererLayoutImageResourceInitializeCalled() {
  return g_layout_image_resource_initialize_called;
}

extern "C" int StandaloneRendererLayoutImageResourceSetResourceCalled() {
  return g_layout_image_resource_set_resource_called;
}

extern "C" int StandaloneRendererLayoutImageResourceNaturalDimensionsCalled() {
  return g_layout_image_resource_natural_dimensions_called;
}

extern "C" int StandaloneRendererLayoutImageResourceGetImageCalled() {
  return g_layout_image_resource_get_image_called;
}

extern "C" int StandaloneRendererImageResourceContentFetchLastUrl(char* out,
                                                                  int size) {
  if (!out || size <= 0) {
    return 0;
  }
  const int copied = std::min<int>(
      static_cast<int>(g_image_resource_content_fetch_last_url.size()),
      size - 1);
  std::memcpy(out, g_image_resource_content_fetch_last_url.data(), copied);
  out[copied] = '\0';
  return copied;
}

bool RuntimeEnabledFeaturesBase::is_selectedcontentelement_attribute_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_selectedcontent_multiple_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_selectedcontent_spec_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_customizable_select_multiple_popup_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_select_remove_overflow_hidden_enabled_ =
    false;

void SetStandaloneDocumentBodyForStandaloneRenderer(Document*, HTMLElement*);

namespace {
v8::Isolate* StandaloneBlinkIsolate() {
  static uintptr_t dummy_isolate_storage = 0;
  return reinterpret_cast<v8::Isolate*>(&dummy_isolate_storage);
}
}  // namespace

Thread::Thread() = default;
Thread::~Thread() = default;
bool Thread::IsCurrentThread() const {
  return true;
}
void Thread::AddTaskObserver(TaskObserver*) {}
void Thread::RemoveTaskObserver(TaskObserver*) {}
void Thread::UpdateThreadTLS(Thread*) {}
FrameOrWorkerScheduler::FrameOrWorkerScheduler() = default;
FrameOrWorkerScheduler::~FrameOrWorkerScheduler() = default;
Agent::Agent(v8::Isolate* isolate,
             const base::UnguessableToken& cluster_id,
             AgentType agent_type,
             std::unique_ptr<v8::MicrotaskQueue> microtask_queue)
    : Agent(isolate,
            cluster_id,
            std::move(microtask_queue),
            AgentClusterKey::CreateUniversalFileAgent(),
            agent_type) {}
Agent::Agent(v8::Isolate* isolate,
             const base::UnguessableToken& cluster_id,
             std::unique_ptr<v8::MicrotaskQueue>,
             const AgentClusterKey& agent_cluster_key,
             AgentType agent_type)
    : isolate_(isolate),
      event_loop_(nullptr),
      cluster_id_(cluster_id),
      agent_cluster_key_(agent_cluster_key),
      agent_type_(agent_type) {}
Agent::~Agent() = default;
void Agent::Trace(Visitor*) const {}
void Agent::AttachContext(ExecutionContext*) {}
void Agent::DetachContext(ExecutionContext*) {}
bool Agent::IsCrossOriginIsolated() const {
  return false;
}
bool Agent::IsWebSecurityDisabled() {
  return false;
}
void Agent::SetIsWebSecurityDisabled(bool) {}
bool Agent::IsIsolatedContext() {
  return false;
}
void Agent::ResetIsIsolatedContextForTest() {}
void Agent::SetIsIsolatedContext(bool) {}
bool Agent::IsWindowAgent() const {
  return false;
}
void Agent::Dispose() {}
void Agent::PerformMicrotaskCheckpoint() {}
RejectedPromises& Agent::GetRejectedPromises() {
  return *static_cast<RejectedPromises*>(nullptr);
}
void Agent::NotifyRejectedPromises() {}
class RejectedPromises::Message final {};
RejectedPromises::RejectedPromises() = default;
RejectedPromises::~RejectedPromises() = default;
void RejectedPromises::Dispose() {}
void RejectedPromises::RejectedWithNoHandler(ScriptState*,
                                             v8::PromiseRejectMessage,
                                             const String&,
                                             SourceLocation*,
                                             SanitizeScriptErrors) {}
void RejectedPromises::HandlerAdded(v8::PromiseRejectMessage) {}
void RejectedPromises::ProcessQueue() {}
void RejectedPromises::ProcessQueueNow(MessageQueue) {}
void RejectedPromises::RevokeNow(std::unique_ptr<Message>) {}
WindowAgent::WindowAgent(AgentGroupScheduler& agent_group_scheduler)
    : blink::Agent(StandaloneBlinkIsolate(),
                   base::UnguessableToken::Create(),
                   AgentType::kDocument),
      agent_group_scheduler_(agent_group_scheduler) {}
WindowAgent::WindowAgent(AgentGroupScheduler& agent_group_scheduler,
                         const AgentClusterKey& agent_cluster_key)
    : blink::Agent(StandaloneBlinkIsolate(),
                   base::UnguessableToken::Create(),
                   nullptr,
                   agent_cluster_key,
                   AgentType::kDocument),
      agent_group_scheduler_(agent_group_scheduler) {}
WindowAgent::~WindowAgent() = default;
void WindowAgent::Trace(Visitor* visitor) const {
  blink::Agent::Trace(visitor);
  visitor->Trace(agent_group_scheduler_);
}
bool WindowAgent::IsWindowAgent() const {
  return true;
}
void WindowAgent::PerformMicrotaskCheckpoint() {}
AgentGroupScheduler& WindowAgent::GetAgentGroupScheduler() {
  return *agent_group_scheduler_;
}

namespace {

class StandaloneNoopSingleThreadTaskRunner final
    : public base::SingleThreadTaskRunner {
 public:
  bool PostDelayedTask(const base::Location&,
                       base::OnceClosure,
                       base::TimeDelta) override {
    return true;
  }

  bool PostNonNestableDelayedTask(const base::Location&,
                                  base::OnceClosure,
                                  base::TimeDelta) override {
    return true;
  }

  bool RunsTasksInCurrentSequence() const override { return true; }
};

scoped_refptr<base::SingleThreadTaskRunner> StandaloneNoopTaskRunner() {
  static scoped_refptr<base::SingleThreadTaskRunner>* runner =
      new scoped_refptr<base::SingleThreadTaskRunner>(
          base::MakeRefCounted<StandaloneNoopSingleThreadTaskRunner>());
  return *runner;
}

class StandaloneNoopAgentGroupScheduler;

class StandaloneNoopFrameScheduler final : public FrameScheduler {
 public:
  explicit StandaloneNoopFrameScheduler(PageScheduler* page_scheduler,
                                        AgentGroupScheduler* agent_scheduler,
                                        FrameType frame_type)
      : page_scheduler_(page_scheduler),
        agent_scheduler_(agent_scheduler),
        frame_type_(frame_type),
        frame_weak_factory_(this),
        scheduler_weak_factory_(this) {}

  void SetFrameVisible(bool visible) override { visible_ = visible; }
  bool IsFrameVisible() const override { return visible_; }
  void SetVisibleAreaLarge(bool) override {}
  void SetHadUserActivation(bool) override {}
  bool IsPageVisible() const override { return true; }
  void SetPaused(bool) override {}
  void SetShouldReportPostedTasksWhenDisabled(bool) override {}
  void SetCrossOriginToNearestMainFrame(bool value) override {
    cross_origin_ = value;
  }
  bool IsCrossOriginToNearestMainFrame() const override {
    return cross_origin_;
  }
  void SetAgentClusterId(const base::UnguessableToken&) override {}
  void SetIsAdFrame(bool is_ad_frame) override { is_ad_frame_ = is_ad_frame; }
  bool IsAdFrame() const override { return is_ad_frame_; }
  bool IsInEmbeddedFrameTree() const override { return false; }
  void TraceUrlChange(const String&) override {}
  void AddTaskTime(base::TimeDelta) override {}
  FrameType GetFrameType() const override { return frame_type_; }
  scoped_refptr<base::SingleThreadTaskRunner> GetTaskRunner(TaskType) override {
    return StandaloneNoopTaskRunner();
  }
  PageScheduler* GetPageScheduler() const override { return page_scheduler_; }
  AgentGroupScheduler* GetAgentGroupScheduler() override {
    return agent_scheduler_;
  }
  void DidStartProvisionalLoad() override {}
  void DidCommitProvisionalLoad(bool,
                                NavigationType,
                                DidCommitProvisionalLoadParams) override {}
  void OnFirstContentfulPaintInMainFrame() override {}
  void OnMainFrameInteractive() override {}
  void OnFirstMeaningfulPaint() override {}
  void OnDidInstallNewDocument() override {}
  bool IsExemptFromBudgetBasedThrottling() const override { return true; }
  std::unique_ptr<mojom::blink::PauseSubresourceLoadingHandle>
  GetPauseSubresourceLoadingHandle() override {
    return nullptr;
  }
  HashSet<SchedulingPolicy::Feature>
  GetActiveFeaturesTrackedForBackForwardCacheMetrics() override {
    return {};
  }
  base::WeakPtr<FrameScheduler> GetWeakPtr() override {
    return frame_weak_factory_.GetWeakPtr();
  }
  void ReportActiveSchedulerTrackedFeatures() override {}
  base::TimeDelta UnreportedTaskTime() const override {
    return base::TimeDelta();
  }
  std::unique_ptr<WebSchedulingTaskQueue> CreateWebSchedulingTaskQueue(
      WebSchedulingQueueType,
      WebSchedulingPriority) override {
    return nullptr;
  }
  scoped_refptr<base::SingleThreadTaskRunner> CompositorTaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  WebScopedVirtualTimePauser CreateWebScopedVirtualTimePauser(
      const String&,
      WebScopedVirtualTimePauser::VirtualTaskDuration) override {
    return WebScopedVirtualTimePauser();
  }

 protected:
  void OnStartedUsingNonStickyFeature(
      SchedulingPolicy::Feature,
      const SchedulingPolicy&,
      SourceLocation*,
      SchedulingAffectingFeatureHandle*) override {}
  void OnStartedUsingStickyFeature(SchedulingPolicy::Feature,
                                   const SchedulingPolicy&,
                                   SourceLocation*) override {}
  void OnStoppedUsingNonStickyFeature(
      SchedulingAffectingFeatureHandle*) override {}
  base::WeakPtr<FrameOrWorkerScheduler> GetFrameOrWorkerSchedulerWeakPtr()
      override {
    return scheduler_weak_factory_.GetWeakPtr();
  }

 private:
  raw_ptr<PageScheduler> page_scheduler_;
  raw_ptr<AgentGroupScheduler> agent_scheduler_;
  FrameType frame_type_;
  bool visible_ = true;
  bool cross_origin_ = false;
  bool is_ad_frame_ = false;
  base::WeakPtrFactory<FrameScheduler> frame_weak_factory_;
  base::WeakPtrFactory<FrameOrWorkerScheduler> scheduler_weak_factory_;
};

class StandaloneNoopPageScheduler final : public PageScheduler {
 public:
  explicit StandaloneNoopPageScheduler(AgentGroupScheduler* agent_scheduler)
      : agent_scheduler_(agent_scheduler) {}

  void OnTitleOrFaviconUpdated() override {}
  void SetPageVisible(bool visible) override { visible_ = visible; }
  bool IsPageVisible() const override { return visible_; }
  void SetPageFrozen(bool frozen) override { frozen_ = frozen; }
  void SetPageBackForwardCached(bool cached) override { bfcached_ = cached; }
  bool IsMainFrameLocal() const override { return main_frame_local_; }
  void SetIsMainFrameLocal(bool local) override { main_frame_local_ = local; }
  bool IsInBackForwardCache() const override { return bfcached_; }
  std::unique_ptr<FrameScheduler> CreateFrameScheduler(
      FrameScheduler::Delegate*,
      const LocalFrameToken&,
      bool,
      FrameScheduler::FrameType frame_type) override {
    return std::make_unique<StandaloneNoopFrameScheduler>(
        this, agent_scheduler_, frame_type);
  }
  void AudioStateChanged(bool playing) override { audio_playing_ = playing; }
  bool IsAudioPlaying() const override { return audio_playing_; }
  bool IsExemptFromBudgetBasedThrottling() const override { return true; }
  bool OptedOutFromAggressiveThrottlingForTest() const override {
    return true;
  }
  AgentGroupScheduler& GetAgentGroupScheduler() override {
    return *agent_scheduler_;
  }
  VirtualTimeController* GetVirtualTimeController() override { return nullptr; }
  scoped_refptr<scheduler::WidgetScheduler> CreateWidgetScheduler(
      scheduler::WidgetScheduler::Delegate*) override {
    return nullptr;
  }

 private:
  raw_ptr<AgentGroupScheduler> agent_scheduler_;
  bool visible_ = true;
  bool frozen_ = false;
  bool bfcached_ = false;
  bool main_frame_local_ = true;
  bool audio_playing_ = false;
};

class StandaloneNoopAgentGroupScheduler final : public AgentGroupScheduler {
 public:
  StandaloneNoopAgentGroupScheduler() {
  }
  std::unique_ptr<PageScheduler> CreatePageScheduler(
      PageScheduler::Delegate*) override {
    return std::make_unique<StandaloneNoopPageScheduler>(this);
  }
  void AddAgent(Agent*) override {}
  scoped_refptr<base::SingleThreadTaskRunner> DefaultTaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  scoped_refptr<base::SingleThreadTaskRunner> CompositorTaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  scheduler::WebThreadScheduler& GetMainThreadScheduler() override {
    return *reinterpret_cast<scheduler::WebThreadScheduler*>(1);
  }
  v8::Isolate* Isolate() override { return nullptr; }
  void OnUrgentMessageReceived() override {}
  void OnUrgentMessageProcessed() override {}
};

class StandaloneNoopMainThreadScheduler final : public MainThreadScheduler {
 public:
  class PauseHandle final : public RendererPauseHandle {};

  StandaloneNoopMainThreadScheduler() {
  }
  void Shutdown() override {}
  bool ShouldYieldForHighPriorityWork() override { return false; }
  void PostIdleTask(const base::Location&, Thread::IdleTask) override {}
  void PostDelayedIdleTask(const base::Location&,
                           base::TimeDelta,
                           Thread::IdleTask) override {}
  void RemoveCancelledIdleTasks() override {}
  scoped_refptr<base::SingleThreadTaskRunner> V8TaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  scoped_refptr<base::SingleThreadTaskRunner> CleanupTaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  base::TimeTicks MonotonicallyIncreasingVirtualTime() override {
    return base::TimeTicks::Now();
  }
  void AddTaskObserver(base::TaskObserver*) override {}
  void RemoveTaskObserver(base::TaskObserver*) override {}
  void SetV8Isolate(v8::Isolate*) override {}
  MainThreadScheduler* ToMainThreadScheduler() override {
    return this;
  }
  std::unique_ptr<RendererPauseHandle> PauseScheduler() override {
    return std::make_unique<PauseHandle>();
  }
  scoped_refptr<base::SingleThreadTaskRunner> NonWakingTaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  AgentGroupScheduler* CreateAgentGroupScheduler() override {
    alignas(StandaloneNoopAgentGroupScheduler) static unsigned char storage
        [sizeof(StandaloneNoopAgentGroupScheduler)];
    static StandaloneNoopAgentGroupScheduler* scheduler =
        ::new (storage) StandaloneNoopAgentGroupScheduler();
    return scheduler;
  }
  AgentGroupScheduler* GetCurrentAgentGroupScheduler() override {
    return nullptr;
  }
  void AddRAILModeObserver(RAILModeObserver*) override {}
  void RemoveRAILModeObserver(RAILModeObserver const*) override {}
  void ForEachMainThreadIsolate(
      base::FunctionRef<void(v8::Isolate*)>) override {}
  void ExecuteAfterCurrentTaskForTesting(base::OnceClosure task,
                                         ExecuteAfterCurrentTaskRestricted)
      override {
    if (task) {
      std::move(task).Run();
    }
  }
  void StartIdlePeriodForTesting() override {}
  void SetRendererBackgroundedForTesting(bool) override {}

 private:
  v8::Isolate* Isolate() override { return nullptr; }
  scheduler::WebThreadScheduler* ToWebMainThreadScheduler() override {
    return nullptr;
  }
};

class StandaloneNoopMainThread final : public MainThread {
 public:
  StandaloneNoopMainThread() {
  }
  ThreadScheduler* Scheduler() override {
    return &scheduler_;
  }
  scoped_refptr<base::SingleThreadTaskRunner> GetTaskRunner(
      MainThreadTaskRunnerRestricted) const override {
    return StandaloneNoopTaskRunner();
  }

 private:
  StandaloneNoopMainThreadScheduler scheduler_;
};

StandaloneNoopMainThread& StandaloneMainThread() {
  static StandaloneNoopMainThread* thread = new StandaloneNoopMainThread();
  return *thread;
}

}  // namespace

class AttributionSrcLoader {
 public:
  explicit AttributionSrcLoader(LocalFrame*);
  ~AttributionSrcLoader();
  void Trace(Visitor*) const;
  void Register(const AtomicString&, HTMLElement*, network::mojom::ReferrerPolicy);
  std::optional<Impression> RegisterNavigation(
      const KURL&,
      const std::vector<WebString>&,
      bool,
      network::mojom::ReferrerPolicy);
};
class SavedFormState {};
class StaticBitmapImage {
 public:
  void AddRef() const {}
  void Release() const {}
};

const CSSBitset kLogicalGroupProperties;
const CSSBitset kKnownExposedProperties;
const CSSBitset kAnimationAffectingProperties;
const CSSBitset kSurrogateProperties;

namespace event_interface_names {
const AtomicString kAnimationEvent("AnimationEvent");
const AtomicString kCommandEvent("CommandEvent");
const AtomicString kEvent("Event");
const AtomicString kInterestEvent("InterestEvent");
const AtomicString kPageRevealEvent("PageRevealEvent");
const AtomicString kTextEvent("TextEvent");
const AtomicString kTransitionEvent("TransitionEvent");
const AtomicString kBeforeUnloadEvent("BeforeUnloadEvent");
}

namespace features {
BASE_FEATURE(kCSSFontComparisonFix,
             "CSSFontComparisonFix",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kCapStringBuilderLengthTo1GiB,
             "CapStringBuilderLengthTo1GiB",
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(bool,
                   kThrottleFrameRateOnInitialization,
                   &kCSSFontComparisonFix,
                   "throttle-frame-rate-on-initialization",
                   false);
const base::FeatureParam<DelayAsyncScriptDelayType>::Option
    kStandaloneDelayAsyncScriptDelayTypeOptions[] = {
        {DelayAsyncScriptDelayType::kFinishedParsing, "finished_parsing"},
        {DelayAsyncScriptDelayType::kFirstPaintOrFinishedParsing,
         "first_paint_or_finished_parsing"},
        {DelayAsyncScriptDelayType::kTillFirstLcpCandidate,
         "till_first_lcp_candidate"}};
BASE_FEATURE_ENUM_PARAM(DelayAsyncScriptDelayType,
                        kDelayAsyncScriptExecutionDelayParam,
                        &kCSSFontComparisonFix,
                        "delay_async_script_execution_delay",
                        DelayAsyncScriptDelayType::kFinishedParsing,
                        &kStandaloneDelayAsyncScriptDelayTypeOptions);
BASE_FEATURE(kPrerender2EarlyDocumentLifecycleUpdate,
             "Prerender2EarlyDocumentLifecycleUpdate",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kDelayAsyncScriptExecution,
             "DelayAsyncScriptExecution",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(bool,
                   kDelayAsyncScriptExecutionDelayByDefaultParam,
                   &kDelayAsyncScriptExecution,
                   "delay-by-default",
                   false);
BASE_FEATURE(kThreadedPreloadScanner,
             "ThreadedPreloadScanner",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kPrecompileInlineScripts,
             "PrecompileInlineScripts",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kProcessHtmlDataImmediately,
             "ProcessHtmlDataImmediately",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(bool,
                   kProcessHtmlDataImmediatelyChildFrame,
                   &kProcessHtmlDataImmediately,
                   "child-frame",
                   false);
BASE_FEATURE_PARAM(bool,
                   kProcessHtmlDataImmediatelyFirstChunk,
                   &kProcessHtmlDataImmediately,
                   "first-chunk",
                   false);
BASE_FEATURE_PARAM(bool,
                   kProcessHtmlDataImmediatelyMainFrame,
                   &kProcessHtmlDataImmediately,
                   "main-frame",
                   false);
BASE_FEATURE_PARAM(bool,
                   kProcessHtmlDataImmediatelySubsequentChunks,
                   &kProcessHtmlDataImmediately,
                   "subsequent-chunks",
                   false);
BASE_FEATURE(kDeferTreeBuilderFlush,
             "DeferTreeBuilderFlush",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(base::TimeDelta,
                   kDeferTreeBuilderFlushInitialInterval,
                   &kDeferTreeBuilderFlush,
                   "initial-interval",
                   base::Milliseconds(0));
BASE_FEATURE_PARAM(base::TimeDelta,
                   kDeferTreeBuilderFlushMaxInterval,
                   &kDeferTreeBuilderFlush,
                   "max-interval",
                   base::Milliseconds(0));
BASE_FEATURE_PARAM(double,
                   kDeferTreeBuilderFlushMultiplier,
                   &kDeferTreeBuilderFlush,
                   "multiplier",
                   1.0);
BASE_FEATURE_PARAM(bool,
                   kDelayAsyncScriptExecutionWhenLcpFoundInHtml,
                   &kCSSFontComparisonFix,
                   "delay-when-lcp-found-in-html",
                   false);
BASE_FEATURE(kLCPPFontURLPredictor,
             "LCPPFontURLPredictor",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kLowPriorityAsyncScriptExecution,
             "LowPriorityAsyncScriptExecution",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(bool,
                   kLowPriorityAsyncScriptExecutionDisableWhenLcpNotInHtmlParam,
                   &kLowPriorityAsyncScriptExecution,
                   "disable-when-lcp-not-in-html",
                   false);
BASE_FEATURE(kHTMLParserYieldByUserTiming,
             "HTMLParserYieldByUserTiming",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kOptimizeHTMLElementUrls,
             "OptimizeHTMLElementUrls",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kDevToolsAllowPopoverForcing,
             "DevToolsAllowPopoverForcing",
             base::FEATURE_ENABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(size_t,
                   kDocumentURLCacheSize,
                   &kOptimizeHTMLElementUrls,
                   "document-url-cache-size",
                   0u);
}  // namespace features

#if !defined(HTML_CSS_RENDERER_STANDALONE)
const QualifiedName& g_any_name =
    *new QualifiedName(g_null_atom, AtomicString("*"), g_null_atom);
const QualifiedName& g_null_name =
    *new QualifiedName(g_null_atom, g_null_atom, g_null_atom);
void QualifiedNameWithHash::CreateStatic(void*, StringImpl*) {}
void QualifiedNameWithHash::CreateStatic(void*,
                                         StringImpl*,
                                         const AtomicString&) {}
#endif

namespace probe {
AsyncTaskContext::~AsyncTaskContext() = default;
void AsyncTaskContext::Cancel() {}
}  // namespace probe

#if !defined(STANDALONE_RENDERER_GN_PROBE)
void String::WriteIntoTrace(perfetto::TracedValue) const {}
void AtomicString::WriteIntoTrace(perfetto::TracedValue) const {}
#endif

extern "C" void WTFAnnotateBenignRaceSized(const char*,
                                           int,
                                           const volatile void*,
                                           size_t,
                                           const char*) {}

EventListenerMap::EventListenerMap() = default;

bool EventListenerMap::Add(
    const AtomicString&,
    EventListener*,
    const AddEventListenerOptionsResolved*,
    RegisteredEventListener** registered_listener) {
  if (registered_listener) {
    *registered_listener = nullptr;
  }
  return false;
}

bool EventListenerMap::Remove(
    const AtomicString&,
    const EventListener*,
    const RegisteredEventListener::OptionsForMatching&,
    RegisteredEventListener** registered_listener) {
  if (registered_listener) {
    *registered_listener = nullptr;
  }
  return false;
}

EventListenerVector* EventListenerMap::Find(const AtomicString&) {
  return nullptr;
}

Vector<AtomicString> EventListenerMap::EventTypes() const {
  return {};
}

void EventListenerMap::Clear() {}

void EventListenerMap::Trace(Visitor* visitor) const {
  visitor->Trace(entries_);
}

AddEventListenerOptions::AddEventListenerOptions() = default;
void AddEventListenerOptions::Trace(Visitor* visitor) const {
  EventListenerOptions::Trace(visitor);
}

EventListenerOptions::EventListenerOptions() = default;
void EventListenerOptions::Trace(Visitor*) const {}

AddEventListenerOptionsResolved::AddEventListenerOptionsResolved() = default;
AddEventListenerOptionsResolved::AddEventListenerOptionsResolved(
    const AddEventListenerOptions*) {}
AddEventListenerOptionsResolved::~AddEventListenerOptionsResolved() = default;
void AddEventListenerOptionsResolved::Trace(Visitor* visitor) const {
  AddEventListenerOptions::Trace(visitor);
}

void RegisteredEventListener::SetCallback(EventListener* listener) {
  callback_ = listener;
}

bool RegisteredEventListener::ShouldFire(const Event&) const {
  return !removed_;
}

void RegisteredEventListener::Trace(Visitor* visitor) const {
  visitor->Trace(callback_);
}
AddEventListenerOptionsResolved* RegisteredEventListener::Options() const {
  return nullptr;
}

void Editor::CountEvent(ExecutionContext*, const Event&) {}

base::TimeDelta PerformanceMonitor::Threshold(ExecutionContext*,
                                              Violation) {
  return base::TimeDelta();
}

ScriptState* CallbackInterfaceBase::CallbackRelevantScriptStateOrReportError(
    const char*,
    const char*) {
  return nullptr;
}

ExecutionContextClient::ExecutionContextClient(ExecutionContext* context)
    : execution_context_(context) {}
ExecutionContext* ExecutionContextClient::GetExecutionContext() const {
  return execution_context_.Get();
}
LocalDOMWindow* ExecutionContextClient::DomWindow() const {
  return nullptr;
}
void ExecutionContextClient::Trace(Visitor* visitor) const {
  visitor->Trace(execution_context_);
}

ExecutionContextLifecycleObserver::ExecutionContextLifecycleObserver(
    ExecutionContext* context,
    Type type)
    : observer_type_(type) {}
ExecutionContext* ExecutionContextLifecycleObserver::GetExecutionContext()
    const {
  return nullptr;
}
void ExecutionContextLifecycleObserver::SetExecutionContext(
    ExecutionContext*) {}
LocalDOMWindow* ExecutionContextLifecycleObserver::DomWindow() const {
  return nullptr;
}
void ExecutionContextLifecycleObserver::Trace(Visitor* visitor) const {
  ContextLifecycleObserver::Trace(visitor);
}

ExecutionContextLifecycleStateObserver::ExecutionContextLifecycleStateObserver(
    ExecutionContext* context)
    : ExecutionContextLifecycleObserver(context) {}
ExecutionContextLifecycleStateObserver::~ExecutionContextLifecycleStateObserver() =
    default;
void ExecutionContextLifecycleStateObserver::SetExecutionContext(
    ExecutionContext* context) {
  ExecutionContextLifecycleObserver::SetExecutionContext(context);
}

JSBasedEventListener::~JSBasedEventListener() = default;
JSBasedEventListener::JSBasedEventListener() = default;
void JSBasedEventListener::Trace(Visitor* visitor) const {
  EventListener::Trace(visitor);
}
void JSBasedEventListener::Invoke(ExecutionContext*, Event*) {}
bool JSBasedEventListener::BelongsToTheCurrentWorld(ExecutionContext*) const {
  return false;
}
SourceLocation* JSBasedEventListener::GetSourceLocation(EventTarget&) {
  return nullptr;
}

void JSEventListener::Trace(Visitor* visitor) const {
  JSBasedEventListener::Trace(visitor);
}
v8::Local<v8::Value> JSEventListener::GetEffectiveFunction(EventTarget&) {
  return v8::Local<v8::Value>();
}
void JSEventListener::InvokeInternal(EventTarget&,
                                     Event&,
                                     v8::Local<v8::Value>) {}

ScriptState* ToScriptStateForMainWorld(LocalFrame*) {
  return nullptr;
}

Modulator* Modulator::From(ScriptState*) {
  return nullptr;
}

bool V8PerIsolateData::HasInstance(const WrapperTypeInfo*,
                                   v8::Local<v8::Value>) {
  return false;
}

Observable::Observable(ExecutionContext* context, SubscribeDelegate*)
    : ExecutionContextClient(context) {}

void Observable::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  ExecutionContextClient::Trace(visitor);
}

AbortSignal::AlgorithmHandle* AbortSignal::AddAlgorithm(
    base::OnceClosure) {
  return nullptr;
}

AbortSignalRegistry* AbortSignalRegistry::From(ExecutionContext&) {
  return nullptr;
}

void AbortSignalRegistry::RegisterAbortAlgorithm(
    EventListener*,
    AbortSignal::AlgorithmHandle*) {}

bool RuntimeEnabledFeaturesBase::DeprecateUnloadOptOutEnabled(
    const FeatureContext*) {
  return false;
}

AbortSignal* Subscriber::signal() const {
  return nullptr;
}
void Subscriber::next(ScriptValue) {}
void Subscriber::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
}

bool DOMTokenList::ValidateTokenValue(const AtomicString&,
                                      ExceptionState&) const {
  return true;
}

void DatasetDOMStringMap::GetNames(Vector<String>& names) {
  names.clear();
}

String DatasetDOMStringMap::item(const String&) {
  return String();
}

bool DatasetDOMStringMap::Contains(const String&) {
  return false;
}

void DatasetDOMStringMap::SetItem(const String&,
                                  const String&,
                                  ExceptionState&) {}

bool DatasetDOMStringMap::DeleteItem(const String&) {
  return false;
}

void DatasetDOMStringMap::Trace(Visitor* visitor) const {
  DOMStringMap::Trace(visitor);
  visitor->Trace(element_);
}

bool RuntimeEnabledFeaturesBase::is_css_resource_integrity_enforcement_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_mobile_layout_theme_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_base_appearance_inline_sizing_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_html_input_element_drop_webkit_clear_button_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_fix_marker_suppression_for_appearance_auto_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_active_caption_maps_to_canvas_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_input_multiple_fields_ui_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_html_command_actions_v_2_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_popover_hint_new_behavior_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_access_key_label_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_list_counter_accounting_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_about_blank_page_respects_dark_mode_on_user_action_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scopeified_parent_pseudo_class_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_improved_source_retargeting_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_composed_path_return_target_being_dispatched_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_animation_iteration_composite_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_compositing_decision_at_animation_phase_boundaries_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_timeline_scope_all_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_timeline_scope_global_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_off_main_thread_css_paint_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_propagate_overscroll_behavior_from_root_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_smaller_viewport_units_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_argument_grammar_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_icu_capitalization_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_text_emphasis_punctuation_exceptions_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_script_based_on_unicode_block_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_media_query_navigation_controls_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_device_posture_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_inverted_colors_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_desktop_pw_as_additional_windowing_controls_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_inherit_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_shadow_contour_follows_border_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_parser_ignore_charset_for_urls_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_cssom_get_computed_style_pseudo_element_requires_colon_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_logical_combination_pseudo_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_lang_extended_ranges_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_marker_nested_pseudo_element_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_nested_pseudo_elements_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_element_backdrop_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_element_view_transitions_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_pseudo_elements_hit_testable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_pseudo_elements_hoverable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_two_phase_view_transition_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_prefer_default_scrollbar_styles_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_inherit_user_modify_without_contenteditable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_font_variation_settings_descriptor_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_video_dynamic_range_media_queries_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_prefers_reduced_data_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_container_name_only_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_comma_separated_container_queries_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_supports_for_import_rules_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scope_import_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_supports_at_rule_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_supports_named_feature_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_custom_media_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_container_style_queries_range_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_mixins_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_clear_current_target_after_dispatch_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_orientation_event_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_capability_delegation_display_capture_request_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_window_default_status_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_fractional_scroll_offsets_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_skip_event_capture_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scrolled_container_queries_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_at_rule_counter_style_speak_as_descriptor_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_playing_paused_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_marker_target_before_after_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_scroll_buttons_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_column_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_filterable_select_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_has_slotted_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_case_sensitive_selector_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_style_sheet_init_base_url_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_dom_activate_bubbles_inheritance_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_middle_click_autoscroll_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_selection_collapsed_direction_none_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_selection_set_base_and_extent_non_null_node_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_use_selection_in_dom_tree_anchor_in_extend_selection_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_selection_remove_range_not_found_error_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_html_parser_yield_and_delay_often_for_testing_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_html_processing_instruction_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_input_in_select_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_html_adoption_algorithm_new_steps_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_allow_preloading_with_csp_meta_tag_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_document_open_sandbox_inheritance_removal_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_document_open_origin_alias_removal_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_avoid_forced_layout_on_invisible_document_close_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_document_open_iframe_unload_events_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scroll_top_left_interop_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_standardized_browser_zoom_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_experimental_policies_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_time_zone_change_event_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_scroll_into_view_root_frame_viewport_bug_fix_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_raster_inducing_scroll_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_author_specified_layout_scroll_snap_behavior_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_snap_change_event_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_snap_changing_event_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_svg_partition_svg_document_resources_in_memory_cache_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_dispatch_hidden_visibility_transitions_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_web_preferences_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_scroll_anchor_priority_candidate_subtree_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_scroll_anchor_serialization_use_parent_for_text_node_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_ch_unit_spec_compliant_fallback_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_mathml_operator_rtl_mirroring_enabled_ =
    false;

namespace features {
BASE_FEATURE(kPausePagesPerBrowsingContextGroup,
             "PausePagesPerBrowsingContextGroup",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kCompositedAnimationsForceMainFrames,
             "CompositedAnimationsForceMainFrames",
             base::FEATURE_DISABLED_BY_DEFAULT);
const base::FeatureParam<bool> kForceMainFramesForIntersectionObserver{
    &kCompositedAnimationsForceMainFrames, "intersection-observer", false};
const base::FeatureParam<bool> kForceMainFramesForAnchorTransform{
    &kCompositedAnimationsForceMainFrames, "anchor-transform", false};
BASE_FEATURE(kVisualRectMappingApplyLocalVisualViewportTransform,
             "VisualRectMappingApplyLocalVisualViewportTransform",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kCaptureJSExecutionLocation,
             "CaptureJSExecutionLocation",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kBackForwardCacheDWCOnJavaScriptExecution,
             "BackForwardCacheDWCOnJavaScriptExecution",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kBackForwardCachePauseMicrotasks,
             "BackForwardCachePauseMicrotasks",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kEnableLazyLoadImageForInvisiblePage,
             "EnableLazyLoadImageForInvisiblePage",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kThrottleUnimportantFrameTimers,
             "ThrottleUnimportantFrameTimers",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kWebFontsCacheAwareTimeoutAdaption,
             "WebFontsCacheAwareTimeoutAdaption",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kEnforceNoopenerOnBlobURLNavigation,
             "EnforceNoopenerOnBlobURLNavigation",
             base::FEATURE_DISABLED_BY_DEFAULT);
const base::FeatureParam<EnableLazyLoadImageForInvisiblePageType>::Option
    kStandaloneEnableLazyLoadImageForInvisiblePageTypeOptions[] = {
        {EnableLazyLoadImageForInvisiblePageType::kAllInvisiblePage,
         "all_invisible_page"},
        {EnableLazyLoadImageForInvisiblePageType::kPrerenderPage,
         "prerender_page"}};
BASE_FEATURE_ENUM_PARAM(
    EnableLazyLoadImageForInvisiblePageType,
    kEnableLazyLoadImageForInvisiblePageTypeParam,
    &kEnableLazyLoadImageForInvisiblePage,
    "enabled_page_type",
    EnableLazyLoadImageForInvisiblePageType::kAllInvisiblePage,
    &kStandaloneEnableLazyLoadImageForInvisiblePageTypeOptions);
BASE_FEATURE_PARAM(int,
                   kLargeFrameSizePercentThreshold,
                   &kThrottleUnimportantFrameTimers,
                   "large_frame_size_percent_threshold",
                   75);
bool IsUnloadBlocklisted() {
  return true;
}
bool IsAllowURNsInIframeEnabled() {
  return false;
}
}  // namespace features

namespace switches {
extern const char kDisableBlobUrlPartitioning[] =
    "disable-blob-url-partitioning";
}  // namespace switches

bool RuntimeEnabledFeaturesBase::IsFeatureEnabledFromString(
    const std::string&) {
  return false;
}
bool RuntimeEnabledFeaturesBase::StandardizedBrowserZoomOptOutEnabled(
    const FeatureContext*) {
  return false;
}

namespace {
const WrapperTypeInfo& StandaloneWrapperTypeInfo(const char* name) {
  static const WrapperTypeInfo info{
      {0},
      nullptr,
      nullptr,
      name,
      nullptr,
      v8::CppHeapPointerTag{},
      v8::CppHeapPointerTag{},
      WrapperTypeInfo::kWrapperTypeObjectPrototype,
      WrapperTypeInfo::kNodeClassId,
      WrapperTypeInfo::kIdlInterface,
      false};
  return info;
}
}  // namespace

const WrapperTypeInfo& HTMLBRElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLBRElement");
const WrapperTypeInfo& HTMLBodyElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLBodyElement");
const WrapperTypeInfo& HTMLDivElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLDivElement");
const WrapperTypeInfo& HTMLFormElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLFormElement");
const WrapperTypeInfo& HTMLHeadingElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLHeadingElement");
const WrapperTypeInfo& HTMLHtmlElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLHtmlElement");
const WrapperTypeInfo& HTMLLIElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLLIElement");
const WrapperTypeInfo& HTMLDataListElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLDataListElement");
const WrapperTypeInfo& HTMLOptGroupElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLOptGroupElement");
const WrapperTypeInfo& HTMLOptionElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLOptionElement");
const WrapperTypeInfo& HTMLOptionsCollection::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLOptionsCollection");
const WrapperTypeInfo& HTMLSelectElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLSelectElement");
const WrapperTypeInfo& HTMLSelectedContentElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLSelectedContentElement");
const WrapperTypeInfo& HTMLSpanElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLSpanElement");
const WrapperTypeInfo& HTMLOListElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLOListElement");
const WrapperTypeInfo& HTMLParagraphElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLParagraphElement");
const WrapperTypeInfo& HTMLScriptElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLScriptElement");
const WrapperTypeInfo& HTMLSlotElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLSlotElement");
const WrapperTypeInfo& HTMLStyleElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLStyleElement");
const WrapperTypeInfo& HTMLTitleElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTitleElement");
const WrapperTypeInfo& HTMLUListElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLUListElement");
const WrapperTypeInfo& HTMLUnknownElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLUnknownElement");
const WrapperTypeInfo& MediaList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("MediaList");
const WrapperTypeInfo& EventTarget::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("EventTarget");
const WrapperTypeInfo& Element::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Element");
const WrapperTypeInfo& HTMLElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLElement");
const WrapperTypeInfo& CSSKeyframesRule::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSKeyframesRule");
const WrapperTypeInfo& CSSRuleList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSRuleList");
const WrapperTypeInfo& CSSPositionTryRule::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSPositionTryRule");
const WrapperTypeInfo& CSSStyleSheet::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSStyleSheet");
const WrapperTypeInfo& StyleSheet::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("StyleSheet");
const WrapperTypeInfo& CSSRule::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSRule");
const WrapperTypeInfo& CSSKeyframeRule::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSKeyframeRule");
const WrapperTypeInfo& CSSPositionTryDescriptors::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSPositionTryDescriptors");
const WrapperTypeInfo& StyleSheetList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("StyleSheetList");
const WrapperTypeInfo& Node::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Node");
const WrapperTypeInfo& Text::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Text");
const WrapperTypeInfo& CharacterData::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CharacterData");
const WrapperTypeInfo& Comment::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Comment");
const WrapperTypeInfo& DocumentType::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DocumentType");
const WrapperTypeInfo& ProcessingInstruction::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ProcessingInstruction");
const WrapperTypeInfo& CustomLayoutChild::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CustomLayoutChild");
const WrapperTypeInfo& ShadowRoot::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ShadowRoot");
const WrapperTypeInfo& HTMLCollection::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLCollection");
const WrapperTypeInfo& MutationObserver::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("MutationObserver");
const WrapperTypeInfo& UIEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("UIEvent");
const WrapperTypeInfo& DOMSelection::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMSelection");
const WrapperTypeInfo& CSSStyleDeclaration::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSStyleDeclaration");
const WrapperTypeInfo& StylePropertyMap::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("StylePropertyMap");
const WrapperTypeInfo& Observable::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Observable");
const WrapperTypeInfo& bindings::FrozenArrayBase::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("FrozenArrayBase");
const WrapperTypeInfo& NamedNodeMap::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("NamedNodeMap");
const WrapperTypeInfo& DOMRectList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMRectList");
const WrapperTypeInfo& DOMTokenList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMTokenList");
const WrapperTypeInfo& DOMStringMap::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMStringMap");
const WrapperTypeInfo& ElementInternals::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ElementInternals");
const WrapperTypeInfo& V8ObservableArrayCSSStyleSheet::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("V8ObservableArrayCSSStyleSheet");
const WrapperTypeInfo& ObservableArrayExoticObject::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ObservableArrayExoticObject");
const WrapperTypeInfo& DOMException::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMException");
const WrapperTypeInfo& Attr::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Attr");
const WrapperTypeInfo& HTMLSubmitButtonBehavior::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLSubmitButtonBehavior");
const WrapperTypeInfo& FocusEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("FocusEvent");
const WrapperTypeInfo& ErrorEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ErrorEvent");
const WrapperTypeInfo& CSSPseudoElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSPseudoElement");
const WrapperTypeInfo& Document::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Document");
const WrapperTypeInfo& DocumentFragment::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DocumentFragment");
const WrapperTypeInfo& DOMImplementation::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMImplementation");
const WrapperTypeInfo& StylePropertyMapReadOnly::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("StylePropertyMapReadOnly");
const WrapperTypeInfo& InterestEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("InterestEvent");
const WrapperTypeInfo& PageRevealEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("PageRevealEvent");
const WrapperTypeInfo& DOMRect::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMRect");
const WrapperTypeInfo& HTMLAllCollection::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLAllCollection");
const WrapperTypeInfo& XMLDocument::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("XMLDocument");
const WrapperTypeInfo& HTMLDocument::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLDocument");
const WrapperTypeInfo& DOMFeaturePolicy::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMFeaturePolicy");
const WrapperTypeInfo& DOMRectReadOnly::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DOMRectReadOnly");
const WrapperTypeInfo& OverscrollEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("OverscrollEvent");
const WrapperTypeInfo& SnapEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SnapEvent");
const WrapperTypeInfo& Range::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Range");
const WrapperTypeInfo& AbstractRange::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AbstractRange");
const WrapperTypeInfo& NodeIterator::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("NodeIterator");
const WrapperTypeInfo& TreeWalker::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TreeWalker");
const WrapperTypeInfo& BeforeUnloadEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("BeforeUnloadEvent");
const WrapperTypeInfo& RouteMap::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("RouteMap");
const WrapperTypeInfo& NodeList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("NodeList");
const WrapperTypeInfo& FragmentDirective::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("FragmentDirective");
const WrapperTypeInfo& DocumentTimeline::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DocumentTimeline");
const WrapperTypeInfo& RadioNodeList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("RadioNodeList");
const WrapperTypeInfo& CaretPosition::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CaretPosition");

const char* const V8ShadowRootMode::string_table_[] = {"open", "closed"};
const char* const V8SlotAssignmentMode::string_table_[] = {"manual", "named"};
const char* const V8DocumentReadyState::string_table_[] = {"loading",
                                                           "interactive",
                                                           "complete"};
const char* const V8VisibilityState::string_table_[] = {"visible", "hidden"};

HTMLElement* HTMLElementFactory::Create(const AtomicString& local_name,
                                        Document& document,
                                        const CreateElementFlags) {
  if (local_name == html_names::kHTMLTag.LocalName())
    return MakeGarbageCollected<HTMLHtmlElement>(document);
  if (local_name == html_names::kHeadTag.LocalName())
    return MakeGarbageCollected<HTMLHeadElement>(document);
  if (local_name == html_names::kBodyTag.LocalName())
    return MakeGarbageCollected<HTMLBodyElement>(document);
  if (local_name == html_names::kFormTag.LocalName()) {
    return MakeGarbageCollected<HTMLFormElement>(document);
  }
  if (local_name == html_names::kTitleTag.LocalName())
    return MakeGarbageCollected<HTMLTitleElement>(document);
  if (local_name == html_names::kBrTag.LocalName())
    return MakeGarbageCollected<HTMLBRElement>(document);
  if (local_name == html_names::kDivTag.LocalName())
    return MakeGarbageCollected<HTMLDivElement>(document);
  if (local_name == html_names::kH1Tag.LocalName() ||
      local_name == html_names::kH2Tag.LocalName() ||
      local_name == html_names::kH3Tag.LocalName() ||
      local_name == html_names::kH4Tag.LocalName() ||
      local_name == html_names::kH5Tag.LocalName() ||
      local_name == html_names::kH6Tag.LocalName())
    return MakeGarbageCollected<HTMLHeadingElement>(
        QualifiedName(g_null_atom, local_name, html_names::xhtmlNamespaceURI),
        document);
  if (local_name == html_names::kLiTag.LocalName())
    return MakeGarbageCollected<HTMLLIElement>(document);
  if (local_name == html_names::kOlTag.LocalName())
    return MakeGarbageCollected<HTMLOListElement>(document);
  if (local_name == html_names::kPTag.LocalName())
    return MakeGarbageCollected<HTMLParagraphElement>(document);
  if (local_name == html_names::kUlTag.LocalName())
    return MakeGarbageCollected<HTMLUListElement>(document);
  QualifiedName tag_name(g_null_atom, local_name,
                         html_names::xhtmlNamespaceURI);
  return MakeGarbageCollected<HTMLElement>(tag_name, document);
}

SVGElement* SVGElementFactory::Create(const AtomicString&,
                                      Document&,
                                      const CreateElementFlags) {
  return nullptr;
}

MathMLElement* MathMLElementFactory::Create(const AtomicString&,
                                            Document&,
                                            const CreateElementFlags) {
  return nullptr;
}
const WrapperTypeInfo V8CSSStyleSheet::wrapper_type_info_{
    {0},
    nullptr,
    nullptr,
    "CSSStyleSheet",
    nullptr,
    V8CSSStyleSheet::kThisTag,
    V8CSSStyleSheet::kMaxSubclassTag,
    WrapperTypeInfo::kWrapperTypeObjectPrototype,
    WrapperTypeInfo::kObjectClassId,
    WrapperTypeInfo::kIdlInterface,
    false};

const WrapperTypeInfo& StandaloneDummyWrapperTypeInfo() {
  static const WrapperTypeInfo info{
      {0},
      nullptr,
      nullptr,
      "StandaloneDummy",
      nullptr,
      static_cast<v8::CppHeapPointerTag>(0),
      static_cast<v8::CppHeapPointerTag>(0),
      WrapperTypeInfo::kWrapperTypeObjectPrototype,
      WrapperTypeInfo::kObjectClassId,
      WrapperTypeInfo::kIdlInterface,
      false};
  return info;
}
const WrapperTypeInfo& DOMWindow::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& WindowProperties::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& HashChangeEvent::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& PermissionsPolicyViolationReportBody::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& ReportBody::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& Report::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& External::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& MessageEvent::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& Fence::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& CrashReportContext::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& History::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& Screen::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& BarProp::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& Navigator::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& NavigationApi::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& StyleMedia::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& CustomElementRegistry::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& PageTransitionEvent::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& TrustedTypePolicyFactory::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();

ResourceRequestHead::ResourceRequestHead() = default;
ResourceRequestHead::ResourceRequestHead(ResourceRequestHead&&) = default;
ResourceRequestHead::~ResourceRequestHead() = default;

ResourceRequestHead::WebBundleTokenParams::WebBundleTokenParams(
    const WebBundleTokenParams& other)
    : bundle_url(other.bundle_url), token(other.token) {}

ResourceRequestHead::WebBundleTokenParams&
ResourceRequestHead::WebBundleTokenParams::operator=(
    const WebBundleTokenParams& other) {
  bundle_url = other.bundle_url;
  token = other.token;
  handle.reset();
  return *this;
}

ResourceRequestBody::ResourceRequestBody() = default;
ResourceRequestBody::ResourceRequestBody(ResourceRequestBody&&) = default;
ResourceRequestBody::~ResourceRequestBody() = default;

ResourceRequest::ResourceRequest() = default;
ResourceRequest::ResourceRequest(const String&) : ResourceRequest() {}
ResourceRequest::ResourceRequest(const KURL&) : ResourceRequest() {}
ResourceRequest::ResourceRequest(const ResourceRequestHead&) : ResourceRequest() {}
ResourceRequest::ResourceRequest(ResourceRequest&&) = default;
ResourceRequest::~ResourceRequest() = default;
FrameLoadRequest::FrameLoadRequest(LocalDOMWindow* origin_window,
                                   const ResourceRequest&)
    : origin_window_(origin_window),
      should_send_referrer_(kMaybeSendReferrer),
      creation_time_(base::TimeTicks::Now()) {}

FetchParameters::FetchParameters(ResourceRequest resource_request,
                                 ResourceLoaderOptions options)
    : resource_request_(std::move(resource_request)),
      decoder_options_(TextResourceDecoderOptions::kPlainTextContent),
      options_(std::move(options)) {}

FetchParameters::FetchParameters(FetchParameters&&) = default;
FetchParameters::~FetchParameters() = default;

ScriptFetchOptions::ScriptFetchOptions()
    : nonce_(),
      integrity_metadata_(),
      integrity_attribute_(),
      parser_state_(kNotParserInserted),
      credentials_mode_(network::mojom::CredentialsMode::kSameOrigin),
      referrer_policy_(network::mojom::ReferrerPolicy::kDefault),
      fetch_priority_hint_(mojom::blink::FetchPriorityHint::kAuto) {}

ScriptFetchOptions::ScriptFetchOptions(
    const String& nonce,
    const IntegrityMetadataSet& integrity_metadata,
    const String& integrity_attribute,
    ParserDisposition parser_state,
    network::mojom::CredentialsMode credentials_mode,
    network::mojom::ReferrerPolicy referrer_policy,
    mojom::blink::FetchPriorityHint fetch_priority_hint,
    RenderBlockingBehavior render_blocking_behavior)
    : nonce_(nonce),
      integrity_metadata_(integrity_metadata),
      integrity_attribute_(integrity_attribute),
      parser_state_(parser_state),
      credentials_mode_(credentials_mode),
      referrer_policy_(referrer_policy),
      fetch_priority_hint_(fetch_priority_hint),
      render_blocking_behavior_(render_blocking_behavior) {}

ScriptFetchOptions::~ScriptFetchOptions() = default;

void FetchParameters::SetCrossOriginAccessControl(const SecurityOrigin*,
                                                  CrossOriginAttributeValue value) {
  cross_origin_attribute_value_ = value;
}

void FetchParameters::SetCrossOriginAccessControl(
    const SecurityOrigin*,
    network::mojom::CredentialsMode) {}

void ResourceClient::Trace(Visitor* visitor) const {
  visitor->Trace(resource_);
}

void ResourceClient::SetResource(Resource* new_resource,
                                 base::SingleThreadTaskRunner*) {
  resource_ = new_resource;
}

void ResourceClient::Prefinalize() {
  ClearResource();
}

void ResourceRequestHead::SetFetchIntegrity(const String&, const FeatureContext*) {}
void ResourceRequestHead::RemoveUserAndPassFromURL() {}
void ResourceRequestHead::SetHTTPOrigin(const SecurityOrigin*) {}
void ResourceRequestHead::SetPriority(WebURLRequest::Priority, int) {}
void ResourceRequestHead::SetHasUserGesture(bool value) {
  has_user_gesture_ = value;
}
Referrer SecurityPolicy::GenerateReferrer(network::mojom::ReferrerPolicy policy,
                                          const KURL&,
                                          const String& referrer) {
  return Referrer(referrer, policy);
}

const String& Frame::GetFrameIdForTracing() {
  return g_empty_string;
}
bool Frame::IsCrossOriginToOutermostMainFrame() const {
  return false;
}
bool Frame::IsOutermostMainFrame() const {
  return true;
}
bool Frame::IsCrossOriginToNearestMainFrame() const {
  return false;
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
void LayoutListItem::OrdinalValueChanged() {}

void LayoutInlineListItem::OrdinalValueChanged() {}
#endif

EventPath::EventPath(Node&, Event*) {}
EventTarget& EventPath::EventTargetRespectingTargetRules(Node& reference_node) {
  return reference_node;
}
void EventPath::InitializeWith(Node&, Event*) {}
NodeEventContext& EventPath::TopNodeEventContext() {
  static NodeEventContext* context = nullptr;
  return *context;
}
void EventPath::Trace(Visitor*) const {}

GCedHeapVector<Member<EventTarget>>& TreeScopeEventContext::EnsureEventPath(
    EventPath&) {
  static Persistent<GCedHeapVector<Member<EventTarget>>> path =
      MakeGarbageCollected<GCedHeapVector<Member<EventTarget>>>();
  return *path;
}
DispatchEventResult EventDispatcher::Dispatch() {
  return DispatchEventResult::kNotCanceled;
}
DispatchEventResult EventDispatcher::DispatchEvent(Node&, Event&) {
  return DispatchEventResult::kNotCanceled;
}
void EventDispatcher::DispatchScopedEvent(Node&, Event&) {}
void EventDispatcher::DispatchSimulatedClick(Node&,
                                             const Event*,
                                             SimulatedClickCreationScope) {}

UIEvent::UIEvent() : Event(), detail_(0) {}
UIEvent::UIEvent(const AtomicString& type,
                 Bubbles bubbles,
                 Cancelable cancelable,
                 ComposedMode composed_mode,
                 base::TimeTicks platform_time_stamp,
                 AbstractView* view,
                 int detail,
                 InputDeviceCapabilities* source_capabilities)
    : Event(type, bubbles, cancelable, composed_mode, platform_time_stamp),
      view_(view),
      detail_(detail),
      source_capabilities_(source_capabilities) {}
UIEvent::~UIEvent() = default;
void UIEvent::initUIEvent(const AtomicString&,
                          bool,
                          bool,
                          AbstractView* view,
                          int detail) {
  view_ = view;
  detail_ = detail;
}
const AtomicString& UIEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}
bool UIEvent::IsUIEvent() const {
  return true;
}
unsigned UIEvent::which() const {
  return 0;
}
void UIEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
  visitor->Trace(view_);
}

void ContextMenuController::HandleContextMenuEvent(MouseEvent*) {}
void EventHandler::DefaultKeyboardEventHandler(KeyboardEvent*) {}
void EventHandler::DefaultTextInputEventHandler(TextEvent*) {}
void EventHandler::StartMiddleClickAutoscroll(LayoutObject*) {}

namespace event_util {
const Vector<AtomicString>& MouseButtonEventTypes() {
  static const Vector<AtomicString>* events = new Vector<AtomicString>();
  return *events;
}
bool IsPointerEventType(const AtomicString&) {
  return false;
}
bool IsSnapEventType(const AtomicString&) {
  return false;
}
}  // namespace event_util

double Performance::MonotonicTimeToDOMHighResTimeStamp(base::TimeTicks) const {
  return 0.0;
}
CSSPseudoElement* CSSPseudoElement::From(PseudoElement*) {
  return nullptr;
}
void CSSPseudoElement::Trace(Visitor*) const {}

void LayoutCounter::UpdateCounter(Vector<int>) {}
void ScopedCSSNameList::Trace(Visitor*) const {}

const HitTestResult::NodeSet& HitTestResult::ListBasedTestResult() const {
  static Persistent<NodeSet> nodes = MakeGarbageCollected<NodeSet>();
  return *nodes;
}

const AtomicString& LayoutCounter::Separator() const {
  return g_empty_atom;
}

void FontFaceCache::ClearAll() {}

FontFaceCache::FontFaceCache() = default;

void FontFaceCache::Trace(Visitor* visitor) const {
}

bool FontFaceCache::ClearCSSConnected() {
  return false;
}

void FontFaceCache::Remove(const StyleRuleFontFace*) {}

namespace {

void ApplyStandaloneDefaultGenericFonts(
    GenericFontFamilySettings& settings) {
  if (settings.Standard().empty()) {
    settings.UpdateStandard(AtomicString("Times New Roman"));
  }
  if (settings.Serif().empty()) {
    settings.UpdateSerif(AtomicString("Times New Roman"));
  }
  if (settings.SansSerif().empty()) {
    settings.UpdateSansSerif(AtomicString("Arial"));
  }
  if (settings.Fixed().empty()) {
    settings.UpdateFixed(AtomicString("Consolas"));
  }
}

}  // namespace

void CSSFontSelector::UpdateGenericFontFamilySettings(Document& document) {
  if (document.GetSettings()) {
    generic_font_family_settings_ =
        document.GetSettings()->GetGenericFontFamilySettings();
  }
  ApplyStandaloneDefaultGenericFonts(generic_font_family_settings_);
  FontCacheInvalidated();
}

CSSFontSelector::CSSFontSelector(const TreeScope& tree_scope)
    : tree_scope_(&tree_scope) {
  font_face_cache_ = MakeGarbageCollected<FontFaceCache>();
  ApplyStandaloneDefaultGenericFonts(generic_font_family_settings_);
}

CSSFontSelector::~CSSFontSelector() = default;

const FontData* CSSFontSelector::GetFontData(
    const FontDescription& font_description,
    const FontFamily& font_family) {
  AtomicString family_name =
      FontSelector::FamilyNameFromSettings(generic_font_family_settings_,
                                           font_description, font_family,
                                           GetUseCounter());
  if (family_name.empty() && !font_family.FamilyIsGeneric()) {
    family_name = font_family.FamilyName();
  }
  if (family_name.empty()) {
    return nullptr;
  }
  return FontCache::Get().GetFontData(font_description, family_name);
}

void CSSFontSelector::FontFaceInvalidated(FontInvalidationReason) {}

void CSSFontSelector::FontCacheInvalidated() {}

void CSSFontSelector::RegisterForInvalidationCallbacks(FontSelectorClient*) {}

void CSSFontSelector::UnregisterForInvalidationCallbacks(FontSelectorClient*) {}

bool CSSFontSelector::IsAlive() const {
  return tree_scope_;
}

UseCounter* CSSFontSelector::GetUseCounter() const {
  return nullptr;
}

void CSSFontSelector::Trace(Visitor* visitor) const {
  visitor->Trace(tree_scope_);
  CSSFontSelectorBase::Trace(visitor);
}

bool CSSFontSelectorBase::IsPlatformFamilyMatchAvailable(
    const FontDescription&,
    const FontFamily&) {
  return false;
}

void CSSFontSelectorBase::WillUseFontData(const FontDescription&,
                                          const FontFamily&,
                                          const String&) {}

void CSSFontSelectorBase::WillUseRange(const FontDescription&,
                                       const AtomicString&,
                                       const FontDataForRangeSet&) {}

void CSSFontSelectorBase::ReportNotDefGlyph() const {}

void CSSFontSelectorBase::Trace(Visitor* visitor) const {
}

CSSFontSelector* PagePopupController::CreateCSSFontSelector(Document& document) {
  return MakeGarbageCollected<CSSFontSelector>(document);
}

bool RenderBlockingResourceManager::AddPendingStylesheet(const Node&) {
  return false;
}

bool RenderBlockingResourceManager::RemovePendingStylesheet(const Node&) {
  return false;
}

bool ProcessingInstruction::IsXSL() const {
  return false;
}
ProcessingInstruction::ProcessingInstruction(Document& document,
                                             const String& target,
                                             const String& data)
    : CharacterData(document, data, kCreateProcessingInstruction),
      target_(target),
      loading_(false),
      alternate_(false),
      is_css_(false),
      is_xsl_(false) {}
ProcessingInstruction::~ProcessingInstruction() = default;
void ProcessingInstruction::Trace(Visitor* visitor) const {
  CharacterData::Trace(visitor);
}
String ProcessingInstruction::nodeName() const {
  return target_;
}
bool ProcessingInstruction::SheetLoaded() {
  return true;
}
Node::InsertionNotificationRequest ProcessingInstruction::InsertedInto(
    ContainerNode&) {
  return kInsertionDone;
}
void ProcessingInstruction::DidNotifySubtreeInsertionsToDocument() {}
void ProcessingInstruction::RemovedFrom(ContainerNode&) {}
CharacterData* ProcessingInstruction::CloneWithData(Document&,
                                                    const String&) const {
  return nullptr;
}
void ProcessingInstruction::NotifyFinished(Resource*) {}
const AtomicString& ProcessingInstruction::GetAttributeValue(
    const AtomicString&,
    const AtomicString&) {
  return g_null_atom;
}

void ScrollMarkerGroupData::AddToFocusGroup(Element&) {}

void ScrollMarkerGroupData::RemoveFromFocusGroup(Element&) {}

void ScrollMarkerGroupData::UpdateSelectedScrollMarker() {}

Element* ScrollMarkerGroupData::Selected() const {
  return selected_marker_.Get();
}

bool ScrollMarkerGroupData::UpdateSnapshot() {
  return false;
}

bool ScrollMarkerGroupData::ShouldScheduleNextService() {
  return false;
}

void ScrollMarkerGroupData::Trace(Visitor* visitor) const {
  PostLayoutSnapshotClient::Trace(visitor);
  visitor->Trace(focus_group_);
  visitor->Trace(selected_marker_);
  visitor->Trace(pending_selected_marker_);
}

Element* HTMLAnchorElement::ScrollTargetElement() const {
  return nullptr;
}

void StyleAdjuster::RunUncacheableStyleAdjustment(
    ComputedStyleBuilder&,
    Element&,
    const Element*,
    const Element*) {}

StyleAdjuster::ElementTypeForCache StyleAdjuster::GetElementTypeCacheKey(
    const ComputedStyle&,
    const Element&) {
  return ElementTypeForCache();
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
Hyphenation* LayoutLocale::GetHyphenation() const {
  return nullptr;
}

void LayoutLocale::ComputeCaseMapLocale() const {}

bool LayoutLocale::IsMacrolanguageChineseSlow() const {
  return false;
}
const LayoutLocale* LayoutLocale::Get(const AtomicString&) {
  return nullptr;
}
#endif
bool IsOnStack(void*) {
  return false;
}
namespace internal {
uintptr_t g_main_thread_stack_start = 0;
uintptr_t g_main_thread_underestimated_stack_size = 0;
size_t ThreadStackSize() {
  return 0;
}
void InitializeMainThreadStackEstimate() {}
}  // namespace internal
ThreadStateStorage ThreadStateStorage::main_thread_state_storage_;
ThreadStateStorage* ThreadStateStorage::Current() {
  return &main_thread_state_storage_;
}
std::ostream& operator<<(std::ostream& stream, WritingMode) {
  return stream;
}

void Hyphenation::SetLimits(wtf_size_t min_prefix_length,
                            wtf_size_t min_suffix_length,
                            wtf_size_t min_word_length) {
  min_prefix_length_ = min_prefix_length;
  min_suffix_length_ = min_suffix_length;
  min_word_length_ = min_word_length;
}

scoped_refptr<Hyphenation> Hyphenation::PlatformGetHyphenation(
    const AtomicString&) {
  return nullptr;
}

String Capitalize(const String& string, UChar) {
  return string;
}

#if defined(HTML_CSS_RENDERER_STANDALONE)
String CaseMap::ToLower(const String& source, TextOffsetMap*) const {
  return source.DeprecatedLower();
}

String CaseMap::ToUpper(const String& source, TextOffsetMap*) const {
  return source;
}

String CaseMap::ToTitle(const String& source, TextOffsetMap*, UChar) const {
  return source;
}
CaseMap::Locale::Locale(const AtomicString&) : case_map_locale_(nullptr) {}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
int FontMetrics::IntAscentInternal(FontBaseline, ApplyBaselineTable) const {
  return int_ascent_;
}
#endif

namespace unicode {
int ItalicMathVariant(int character) {
  return character;
}
}  // namespace unicode

KURL MemoryCache::RemoveFragmentIdentifierIfNeeded(const KURL& url) {
  return url;
}

#if defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
namespace {
class StandaloneDataUrlPngImage final : public Image {
 public:
  static scoped_refptr<StandaloneDataUrlPngImage> Create(sk_sp<SkImage> image) {
    if (!image) {
      return nullptr;
    }
    return base::AdoptRef(new StandaloneDataUrlPngImage(std::move(image)));
  }

  bool IsOpaque() override { return paint_image_.IsOpaque(); }
  gfx::Size SizeWithConfig(SizeConfig) const override { return size_; }
  void DestroyDecodedData() override {}
  PaintImage PaintImageForCurrentFrame() override { return paint_image_; }
  void Draw(cc::PaintCanvas* canvas,
            const cc::PaintFlags& flags,
            const gfx::RectF& dst_rect,
            const gfx::RectF& src_rect,
            const ImageDrawOptions& draw_options) override {
    if (!canvas || !paint_image_ || dst_rect.IsEmpty() || src_rect.IsEmpty()) {
      return;
    }
    canvas->drawImageRect(paint_image_, gfx::RectFToSkRect(src_rect),
                          gfx::RectFToSkRect(dst_rect),
                          draw_options.sampling_options, &flags,
                          ToSkiaRectConstraint(draw_options.clamping_mode));
  }

 private:
  explicit StandaloneDataUrlPngImage(sk_sp<SkImage> image)
      : Image(nullptr, false),
        size_(image->width(), image->height()),
        paint_image_(CreatePaintImageBuilder()
                         .set_image(std::move(image),
                                    cc::PaintImage::GetNextContentId())
                         .TakePaintImage()) {}

  gfx::Size size_;
  PaintImage paint_image_;
};

scoped_refptr<Image> DecodeStandaloneDataUrlPngImage(const KURL& url) {
  html_css_renderer::StandaloneResourceRequest request;
  request.url = url.GetString().Utf8();
  request.type_hint = html_css_renderer::StandaloneResourceTypeHint::kImage;
  request.initiator =
      html_css_renderer::StandaloneResourceInitiator::kImgElement;
  request.accepted_mime_types.push_back("image/png");
  html_css_renderer::StandaloneResourceResult result =
      html_css_renderer::DefaultStandaloneResourceProvider().LoadResource(
          request);
  if (result.status != html_css_renderer::StandaloneResourceStatus::kSuccess ||
      !result.decoded_image) {
    return nullptr;
  }
  return StandaloneDataUrlPngImage::Create(std::move(result.decoded_image));
}
}  // namespace
#endif

ImageResourceContent::ImageResourceContent(scoped_refptr<blink::Image> image)
    : image_(std::move(image)) {
  content_status_ = image_ ? ResourceStatus::kCached : ResourceStatus::kNotStarted;
  size_available_ = image_ ? Image::kSizeAvailable : Image::kSizeUnavailable;
}

ImageResourceContent* ImageResourceContent::CreateLoaded(
    scoped_refptr<blink::Image> image) {
  return MakeGarbageCollected<ImageResourceContent>(std::move(image));
}

ImageResourceContent* ImageResourceContent::Fetch(FetchParameters& params,
                                                  ResourceFetcher*) {
#if defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
  StandaloneRendererNoteImageResourceContentFetch(
      params.Url().GetString().Utf8().c_str());
  if (scoped_refptr<Image> image =
          DecodeStandaloneDataUrlPngImage(params.Url())) {
    return ImageResourceContent::CreateLoaded(std::move(image));
  }
#endif
  return nullptr;
}

bool ImageResourceContent::IsAnimatedImage() const {
  return false;
}

void ImageResourceContent::Trace(Visitor* visitor) const {
  ImageObserver::Trace(visitor);
}
void ImageResourceContent::AddObserver(ImageResourceObserver*) {}
void ImageResourceContent::RemoveObserver(ImageResourceObserver*) {}
RespectImageOrientationEnum ImageResourceContent::ForceOrientationIfNecessary(
    RespectImageOrientationEnum default_orientation) const {
  return default_orientation;
}
const KURL& ImageResourceContent::Url() const {
  static KURL* url = new KURL();
  return *url;
}
void ImageResourceContent::SetIsSufficientContentLoadedForPaint() {}
bool ImageResourceContent::IsSufficientContentLoadedForPaint() const {
  return true;
}
uint64_t ImageResourceContent::ContentSizeForEntropy() const {
  return 0;
}
bool ImageResourceContent::IsPaintedFirstFrame() const {
  return image_.get();
}
std::optional<WebURLRequest::Priority> ImageResourceContent::RequestPriority()
    const {
  return std::nullopt;
}
bool ImageResourceContent::IsDataUrl() const {
  return true;
}
AtomicString ImageResourceContent::MediaType() const {
  return AtomicString("image");
}
bool ImageResourceContent::IsBroken() const {
  return !image_;
}
void ImageResourceContent::SetIsBroken() {
  is_broken_ = true;
}
bool ImageResourceContent::IsCorsSameOrigin() const {
  return true;
}
base::TimeTicks ImageResourceContent::DiscoveryTime() const {
  return base::TimeTicks();
}
base::TimeTicks ImageResourceContent::LoadStart() const {
  return base::TimeTicks();
}
base::TimeTicks ImageResourceContent::LoadEnd() const {
  return base::TimeTicks();
}
void ImageResourceContent::DecodedSizeChangedTo(const blink::Image*, size_t) {}
bool ImageResourceContent::ShouldPauseAnimation(const blink::Image*) {
  return false;
}
void ImageResourceContent::Changed(const blink::Image*) {}
void ImageResourceContent::AsyncLoadCompleted(const blink::Image*) {}

void Resource::Trace(Visitor* visitor) const {
  visitor->Trace(clients_);
}

void IntegrityReport::SendReports(UseCounterAndConsoleLogger*) const {}

void SubresourceIntegrity::ParseIntegrityAttribute(const String&,
                                                   IntegrityMetadataSet&,
                                                   const FeatureContext*) {}

String TimelineOffset::TimelineRangeNameToString(V8TimelineRange::Enum) {
  return String();
}

bool TimelineOffset::UpdateOffset(Element*, CSSValue*) {
  return false;
}

std::optional<TimelineOffset> TimelineOffset::Create(
    Element*,
    String,
    double,
    ExceptionState&) {
  return std::nullopt;
}

std::optional<TimelineOffset> TimelineOffset::Create(
    Element*,
    const V8UnionStringOrTimelineRangeOffset*,
    double,
    ExceptionState&) {
  return std::nullopt;
}

bool TimelineOffset::IsStyleDependent(const CSSValue*) {
  return false;
}

CSSValue* TimelineOffset::ParseOffset(Document*, String) {
  return nullptr;
}

Length TimelineOffset::ResolveLength(Element*, const CSSValue*) {
  return Length::Fixed();
}

String TimelineOffset::ToString() const {
  return String();
}

TimelineOffsetOrAuto TimelineOffsetOrAuto::Create(
    Element*,
    const V8UnionStringOrTimelineRangeOffset*,
    double,
    ExceptionState&) {
  return TimelineOffsetOrAuto();
}

bool TimelineRange::IsEmpty() const {
  return true;
}

double TimelineRange::ToFractionalOffset(const TimelineOffset&) const {
  return 0.0;
}

AtomicString CreateVisionDeficiencyFilterUrl(VisionDeficiency) {
  return AtomicString();
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
ReferenceFilterOperation::ReferenceFilterOperation(const AtomicString& url,
                                                   SVGResource* resource)
    : FilterOperation(OperationType::kReference), url_(url), resource_(resource) {}

gfx::RectF ReferenceFilterOperation::MapRect(const gfx::RectF& rect) const {
  return rect;
}

void ReferenceFilterOperation::Trace(Visitor* visitor) const {
  visitor->Trace(filter_);
  FilterOperation::Trace(visitor);
}

bool ReferenceFilterOperation::IsEqualAssumingSameType(
    const FilterOperation& other) const {
  return url_ == To<ReferenceFilterOperation>(other).url_;
}
#endif

CSSRule::CSSRule(CSSStyleSheet* parent)
    : has_cached_selector_text_(false),
      parent_is_rule_(false),
      parent_(parent) {}

void CSSRule::SetParentStyleSheet(CSSStyleSheet* parent) {
  parent_is_rule_ = false;
  parent_ = parent;
}

void CSSRule::SetParentRule(CSSRule* parent) {
  parent_is_rule_ = true;
  parent_ = parent;
}

void CSSRule::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  visitor->Trace(parent_);
}

const CSSParserContext* CSSRule::ParserContext(SecureContextMode) const {
  return nullptr;
}

bool CSSRule::VerifyParentIsCSSRule() const {
  return true;
}

bool CSSRule::VerifyParentIsCSSStyleSheet() const {
  return true;
}

CSSStyleSheetInit::CSSStyleSheetInit() = default;
CSSStyleSheetInit::CSSStyleSheetInit(v8::Isolate*) {}
void CSSStyleSheetInit::setBaseURL(const String& value) {
  member_base_url_ = value;
}
void CSSStyleSheetInit::setBaseURL(String&& value) {
  member_base_url_ = std::move(value);
}
void CSSStyleSheetInit::Trace(Visitor* visitor) const {
  bindings::InputDictionaryBase::Trace(visitor);
}

StyleSheet::~StyleSheet() = default;

CSSKeyframeRule::CSSKeyframeRule(StyleRuleKeyframe* rule,
                                 CSSKeyframesRule* parent)
    : CSSRule(parent ? parent->parentStyleSheet() : nullptr),
      keyframe_(rule) {
  SetParentRule(parent);
}

CSSKeyframeRule::~CSSKeyframeRule() = default;

void CSSKeyframeRule::Reattach(StyleRuleBase* rule) {
  keyframe_ = DynamicTo<StyleRuleKeyframe>(rule);
}

void CSSKeyframeRule::Trace(Visitor* visitor) const {
  CSSRule::Trace(visitor);
  visitor->Trace(keyframe_);
}

CSSStyleDeclaration* CSSKeyframeRule::style() const {
  return nullptr;
}

CSSStyleSheet* CSSImportRule::styleSheet() const {
  return nullptr;
}

CSSRuleList* CSSStyleRule::cssRules() const {
  return nullptr;
}

CSSRule* CSSNestedDeclarationsRule::InnerCSSStyleRule() const {
  return nullptr;
}

CSSPositionTryDescriptors::CSSPositionTryDescriptors(
    MutableCSSPropertyValueSet& property_set,
    CSSRule* parent)
    : StyleRuleCSSStyleDeclaration(property_set, parent) {}

bool CSSPositionTryDescriptors::IsPropertyValid(CSSPropertyID) const {
  return true;
}

String CSSPositionTryDescriptors::Get(CSSPropertyID) {
  return String();
}

void CSSPositionTryDescriptors::Set(const ExecutionContext*,
                                    CSSPropertyID,
                                    const String&,
                                    ExceptionState&) {}

void CSSPositionTryDescriptors::Trace(Visitor* visitor) const {
  StyleRuleCSSStyleDeclaration::Trace(visitor);
}

CSSStyleDeclaration::CSSStyleDeclaration(ExecutionContext* context)
    : ExecutionContextClient(context) {}
CSSStyleDeclaration::~CSSStyleDeclaration() = default;
void CSSStyleDeclaration::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  ExecutionContextClient::Trace(visitor);
}

StyleRuleCSSStyleDeclaration::StyleRuleCSSStyleDeclaration(
    MutableCSSPropertyValueSet& property_set,
    CSSRule* parent)
    : PropertySetCSSStyleDeclaration(nullptr, property_set),
      parent_rule_(parent) {}

StyleRuleCSSStyleDeclaration::~StyleRuleCSSStyleDeclaration() = default;

void StyleRuleCSSStyleDeclaration::Trace(Visitor* visitor) const {
  PropertySetCSSStyleDeclaration::Trace(visitor);
  visitor->Trace(parent_rule_);
}

CSSStyleSheet* StyleRuleCSSStyleDeclaration::ParentStyleSheet() const {
  return parent_rule_ ? parent_rule_->parentStyleSheet() : nullptr;
}

void StyleRuleCSSStyleDeclaration::WillMutate() {}

void StyleRuleCSSStyleDeclaration::DidMutate(MutationType) {}

void PropertySetCSSStyleDeclaration::Trace(Visitor* visitor) const {
  AbstractPropertySetCSSStyleDeclaration::Trace(visitor);
  visitor->Trace(property_set_);
}

unsigned StyleAttributeMutationScope::scope_count_ = 0;
AbstractPropertySetCSSStyleDeclaration*
    StyleAttributeMutationScope::current_decl_ = nullptr;
bool StyleAttributeMutationScope::should_notify_inspector_ = false;
bool StyleAttributeMutationScope::should_deliver_ = false;

StyleAttributeMutationScope::StyleAttributeMutationScope(
    AbstractPropertySetCSSStyleDeclaration* decl) {
  ++scope_count_;
  current_decl_ = decl;
}

StyleAttributeMutationScope::~StyleAttributeMutationScope() {
  if (scope_count_) {
    --scope_count_;
  }
  if (!scope_count_) {
    current_decl_ = nullptr;
    should_notify_inspector_ = false;
    should_deliver_ = false;
  }
}

StylePropertySerializer::CSSPropertyValueSetForSerializer::
    CSSPropertyValueSetForSerializer(const CSSPropertyValueSet& properties)
    : property_set_(&properties),
      all_index_(-1),
      need_to_expand_all_(false) {}

StylePropertySerializer::StylePropertySerializer(
    const CSSPropertyValueSet& properties)
    : property_set_(properties) {}

String StylePropertySerializer::SerializeShorthand(CSSPropertyID) const {
  return String();
}

String StylePropertySerializer::AsText() const {
  return String();
}

LinkCondition::LinkCondition(
    NavigationLocation* location,
    const ConditionalExpNode* navigation_param_root_exp)
    : navigation_location_(location),
      navigation_param_root_exp_(navigation_param_root_exp) {}

void LinkCondition::Trace(Visitor* visitor) const {
  visitor->Trace(navigation_param_root_exp_);
}

void LinkCondition::SerializeTo(StringBuilder&) const {}

bool LinkCondition::Evaluate(const Element&) const {
  return false;
}

CSSContainerValues::CSSContainerValues(
    Document& document,
    Element& container,
    std::optional<double> width,
    std::optional<double> height,
    ContainerStuckPhysical stuck_horizontal,
    ContainerStuckPhysical stuck_vertical,
    ContainerSnappedFlags snapped,
    ContainerScrollableFlags scrollable_horizontal,
    ContainerScrollableFlags scrollable_vertical,
    ContainerScrolled scrolled_horizontal,
    ContainerScrolled scrolled_vertical,
    WritingDirectionMode abs_container_writing_direction,
    const PositionTryFallback& fallback)
    : MediaValuesDynamic(static_cast<LocalFrame*>(nullptr)),
      element_(&container),
      width_(width),
      height_(height),
      writing_direction_(WritingMode::kHorizontalTb, TextDirection::kLtr),
      abs_container_writing_direction_(abs_container_writing_direction),
      stuck_horizontal_(stuck_horizontal),
      stuck_vertical_(stuck_vertical),
      snapped_(snapped),
      scrollable_horizontal_(scrollable_horizontal),
      scrollable_vertical_(scrollable_vertical),
      scrolled_horizontal_(scrolled_horizontal),
      scrolled_vertical_(scrolled_vertical),
      anchored_fallback_(fallback) {}

void CSSContainerValues::Trace(Visitor* visitor) const {
  visitor->Trace(element_);
}

float CSSContainerValues::EmFontSize(float) const { return 16.0f; }
float CSSContainerValues::RemFontSize(float) const { return 16.0f; }
float CSSContainerValues::ExFontSize(float) const { return 8.0f; }
float CSSContainerValues::RexFontSize(float) const { return 8.0f; }
float CSSContainerValues::ChFontSize(float) const { return 8.0f; }
float CSSContainerValues::RchFontSize(float) const { return 8.0f; }
float CSSContainerValues::IcFontSize(float) const { return 16.0f; }
float CSSContainerValues::RicFontSize(float) const { return 16.0f; }
float CSSContainerValues::LineHeight(float) const { return 16.0f; }
float CSSContainerValues::RootLineHeight(float) const { return 16.0f; }
float CSSContainerValues::CapFontSize(float) const { return 16.0f; }
float CSSContainerValues::RcapFontSize(float) const { return 16.0f; }
double CSSContainerValues::ContainerWidth() const { return width_.value_or(0); }
double CSSContainerValues::ContainerHeight() const { return height_.value_or(0); }
ContainerStuckLogical CSSContainerValues::StuckInline() const {
  return ContainerStuckLogical::kNo;
}
ContainerStuckLogical CSSContainerValues::StuckBlock() const {
  return ContainerStuckLogical::kNo;
}
ContainerScrollableFlags CSSContainerValues::ScrollableInline() const {
  return scrollable_horizontal_;
}
ContainerScrollableFlags CSSContainerValues::ScrollableBlock() const {
  return scrollable_vertical_;
}
ContainerScrolled CSSContainerValues::ScrolledInline() const {
  return scrolled_horizontal_;
}
ContainerScrolled CSSContainerValues::ScrolledBlock() const {
  return scrolled_vertical_;
}

MediaValuesDynamic::MediaValuesDynamic(LocalFrame* frame)
    : frame_(frame),
      viewport_dimensions_overridden_(false),
      viewport_width_override_(0),
      viewport_height_override_(0) {}

MediaValuesDynamic::MediaValuesDynamic(LocalFrame* frame,
                                       bool overridden_viewport_dimensions,
                                       double viewport_width,
                                       double viewport_height)
    : frame_(frame),
      viewport_dimensions_overridden_(overridden_viewport_dimensions),
      viewport_width_override_(viewport_width),
      viewport_height_override_(viewport_height) {}

void MediaValuesDynamic::Trace(Visitor* visitor) const {
  visitor->Trace(frame_);
}

int MediaValuesDynamic::DeviceWidth() const { return 0; }
int MediaValuesDynamic::DeviceHeight() const { return 0; }
float MediaValuesDynamic::DevicePixelRatio() const { return 1.0f; }
bool MediaValuesDynamic::DeviceSupportsHDR() const { return false; }
int MediaValuesDynamic::ColorBitsPerComponent() const { return 24; }
int MediaValuesDynamic::MonochromeBitsPerComponent() const { return 0; }
bool MediaValuesDynamic::InvertedColors() const { return false; }
mojom::blink::PointerType MediaValuesDynamic::PrimaryPointerType() const {
  return mojom::blink::PointerType::kPointerNone;
}
int MediaValuesDynamic::AvailablePointerTypes() const { return 0; }
mojom::blink::HoverType MediaValuesDynamic::PrimaryHoverType() const {
  return mojom::blink::HoverType::kHoverNone;
}
mojom::blink::OutputDeviceUpdateAbilityType
MediaValuesDynamic::OutputDeviceUpdateAbilityType() const {
  return mojom::blink::OutputDeviceUpdateAbilityType::kFastType;
}
int MediaValuesDynamic::AvailableHoverTypes() const { return 0; }
bool MediaValuesDynamic::ThreeDEnabled() const { return false; }
bool MediaValuesDynamic::StrictMode() const { return true; }
const String MediaValuesDynamic::MediaType() const { return AtomicString("screen"); }
blink::mojom::DisplayMode MediaValuesDynamic::DisplayMode() const {
  return blink::mojom::DisplayMode::kBrowser;
}
ui::mojom::blink::WindowShowState MediaValuesDynamic::WindowShowState() const {
  return ui::mojom::blink::WindowShowState::kDefault;
}
bool MediaValuesDynamic::Resizable() const { return true; }
ColorSpaceGamut MediaValuesDynamic::ColorGamut() const {
  return ColorSpaceGamut::kUnknown;
}
mojom::blink::PreferredColorScheme
MediaValuesDynamic::GetPreferredColorScheme() const {
  return mojom::blink::PreferredColorScheme::kLight;
}
mojom::blink::PreferredContrast
MediaValuesDynamic::GetPreferredContrast() const {
  return mojom::blink::PreferredContrast::kNoPreference;
}
bool MediaValuesDynamic::PrefersReducedMotion() const { return false; }
bool MediaValuesDynamic::PrefersReducedData() const { return false; }
bool MediaValuesDynamic::PrefersReducedTransparency() const { return false; }
ForcedColors MediaValuesDynamic::GetForcedColors() const {
  return ForcedColors::kNone;
}
NavigationControls MediaValuesDynamic::GetNavigationControls() const {
  return NavigationControls::kNone;
}
int MediaValuesDynamic::GetHorizontalViewportSegments() const { return 1; }
int MediaValuesDynamic::GetVerticalViewportSegments() const { return 1; }
mojom::blink::DevicePostureType MediaValuesDynamic::GetDevicePosture() const {
  return mojom::blink::DevicePostureType::kContinuous;
}
Scripting MediaValuesDynamic::GetScripting() const { return Scripting::kNone; }
Document* MediaValuesDynamic::GetDocument() const { return nullptr; }
bool MediaValuesDynamic::HasValues() const { return true; }
float MediaValuesDynamic::EmFontSize(float) const { return 16.0f; }
float MediaValuesDynamic::RemFontSize(float) const { return 16.0f; }
float MediaValuesDynamic::ExFontSize(float) const { return 8.0f; }
float MediaValuesDynamic::RexFontSize(float) const { return 8.0f; }
float MediaValuesDynamic::ChFontSize(float) const { return 8.0f; }
float MediaValuesDynamic::RchFontSize(float) const { return 8.0f; }
float MediaValuesDynamic::IcFontSize(float) const { return 16.0f; }
float MediaValuesDynamic::RicFontSize(float) const { return 16.0f; }
float MediaValuesDynamic::LineHeight(float) const { return 16.0f; }
float MediaValuesDynamic::RootLineHeight(float) const { return 16.0f; }
float MediaValuesDynamic::CapFontSize(float) const { return 16.0f; }
float MediaValuesDynamic::RcapFontSize(float) const { return 16.0f; }
double MediaValuesDynamic::ViewportWidth() const {
  if (viewport_dimensions_overridden_) {
    return viewport_width_override_;
  }
  return frame_ && frame_->View() ? frame_->View()->GetLayoutSize().width() : 800;
}
double MediaValuesDynamic::ViewportHeight() const {
  if (viewport_dimensions_overridden_) {
    return viewport_height_override_;
  }
  return frame_ && frame_->View() ? frame_->View()->GetLayoutSize().height() : 600;
}
double MediaValuesDynamic::SmallViewportWidth() const { return ViewportWidth(); }
double MediaValuesDynamic::SmallViewportHeight() const { return ViewportHeight(); }
double MediaValuesDynamic::LargeViewportWidth() const { return ViewportWidth(); }
double MediaValuesDynamic::LargeViewportHeight() const { return ViewportHeight(); }
double MediaValuesDynamic::DynamicViewportWidth() const { return ViewportWidth(); }
double MediaValuesDynamic::DynamicViewportHeight() const { return ViewportHeight(); }
double MediaValuesDynamic::ContainerWidth() const { return 0; }
double MediaValuesDynamic::ContainerHeight() const { return 0; }
double MediaValuesDynamic::ContainerWidth(const ScopedCSSName&) const { return 0; }
double MediaValuesDynamic::ContainerHeight(const ScopedCSSName&) const { return 0; }

ScrollStateQuerySnapshot::ScrollStateQuerySnapshot(Element& container)
    : PostLayoutSnapshotClient(static_cast<LocalFrame*>(nullptr)),
      container_(&container) {}

bool ScrollStateQuerySnapshot::UpdateSnapshot() {
  return false;
}

bool ScrollStateQuerySnapshot::ShouldScheduleNextService() {
  return false;
}

void ScrollStateQuerySnapshot::Trace(Visitor* visitor) const {
  visitor->Trace(container_);
}

PostLayoutSnapshotClient::PostLayoutSnapshotClient(LocalFrame*) {}

void PostLayoutSnapshotClient::UpdateSnapshotForServiceAnimations() {
  UpdateSnapshot();
}

MediaValuesCached::MediaValuesCached() = default;
MediaValuesCached::MediaValuesCached(Document& document) {
  LocalFrame* frame = document.GetFrame();
  const double width =
      frame && frame->View() ? frame->View()->GetLayoutSize().width() : 800;
  const double height =
      frame && frame->View() ? frame->View()->GetLayoutSize().height() : 600;
  data_.viewport_width = width;
  data_.viewport_height = height;
  data_.small_viewport_width = width;
  data_.small_viewport_height = height;
  data_.large_viewport_width = width;
  data_.large_viewport_height = height;
  data_.dynamic_viewport_width = width;
  data_.dynamic_viewport_height = height;
  data_.device_width = static_cast<int>(width);
  data_.device_height = static_cast<int>(height);
  data_.device_pixel_ratio = 1.0f;
  data_.media_type = AtomicString("screen");
  data_.strict_mode = true;
  data_.resizable = true;
}
MediaValuesCached::MediaValuesCached(const MediaValuesCachedData& data)
    : data_(data) {}
MediaValuesCached::MediaValuesCachedData::MediaValuesCachedData() = default;
MediaValues* MediaValuesCached::Copy() const { return nullptr; }
void MediaValuesCached::OverrideViewportDimensions(double width, double height) {
  data_.viewport_width = width;
  data_.viewport_height = height;
}
int MediaValuesCached::DeviceWidth() const { return data_.device_width; }
int MediaValuesCached::DeviceHeight() const { return data_.device_height; }
float MediaValuesCached::DevicePixelRatio() const { return data_.device_pixel_ratio; }
bool MediaValuesCached::DeviceSupportsHDR() const { return data_.device_supports_hdr; }
int MediaValuesCached::ColorBitsPerComponent() const { return data_.color_bits_per_component; }
int MediaValuesCached::MonochromeBitsPerComponent() const { return data_.monochrome_bits_per_component; }
bool MediaValuesCached::InvertedColors() const { return data_.inverted_colors; }
mojom::blink::PointerType MediaValuesCached::PrimaryPointerType() const { return data_.primary_pointer_type; }
int MediaValuesCached::AvailablePointerTypes() const { return data_.available_pointer_types; }
mojom::blink::HoverType MediaValuesCached::PrimaryHoverType() const { return data_.primary_hover_type; }
mojom::blink::OutputDeviceUpdateAbilityType MediaValuesCached::OutputDeviceUpdateAbilityType() const { return data_.output_device_update_ability_type; }
int MediaValuesCached::AvailableHoverTypes() const { return data_.available_hover_types; }
bool MediaValuesCached::ThreeDEnabled() const { return data_.three_d_enabled; }
bool MediaValuesCached::StrictMode() const { return data_.strict_mode; }
Document* MediaValuesCached::GetDocument() const { return nullptr; }
bool MediaValuesCached::HasValues() const { return true; }
const String MediaValuesCached::MediaType() const { return data_.media_type; }
blink::mojom::DisplayMode MediaValuesCached::DisplayMode() const { return data_.display_mode; }
ui::mojom::blink::WindowShowState MediaValuesCached::WindowShowState() const { return data_.window_show_state; }
bool MediaValuesCached::Resizable() const { return data_.resizable; }
ColorSpaceGamut MediaValuesCached::ColorGamut() const { return data_.color_gamut; }
mojom::blink::PreferredColorScheme MediaValuesCached::GetPreferredColorScheme() const { return data_.preferred_color_scheme; }
mojom::blink::PreferredContrast MediaValuesCached::GetPreferredContrast() const { return data_.preferred_contrast; }
bool MediaValuesCached::PrefersReducedMotion() const { return data_.prefers_reduced_motion; }
bool MediaValuesCached::PrefersReducedData() const { return data_.prefers_reduced_data; }
bool MediaValuesCached::PrefersReducedTransparency() const { return data_.prefers_reduced_transparency; }
ForcedColors MediaValuesCached::GetForcedColors() const { return data_.forced_colors; }
NavigationControls MediaValuesCached::GetNavigationControls() const { return data_.navigation_controls; }
int MediaValuesCached::GetHorizontalViewportSegments() const { return data_.horizontal_viewport_segments; }
int MediaValuesCached::GetVerticalViewportSegments() const { return data_.vertical_viewport_segments; }
mojom::blink::DevicePostureType MediaValuesCached::GetDevicePosture() const { return data_.device_posture; }
Scripting MediaValuesCached::GetScripting() const { return data_.scripting; }
float MediaValuesCached::EmFontSize(float) const { return data_.em_size; }
float MediaValuesCached::RemFontSize(float) const { return data_.em_size; }
float MediaValuesCached::ExFontSize(float) const { return data_.ex_size; }
float MediaValuesCached::RexFontSize(float) const { return data_.ex_size; }
float MediaValuesCached::ChFontSize(float) const { return data_.ch_size; }
float MediaValuesCached::RchFontSize(float) const { return data_.ch_size; }
float MediaValuesCached::IcFontSize(float) const { return data_.ic_size; }
float MediaValuesCached::RicFontSize(float) const { return data_.ic_size; }
float MediaValuesCached::LineHeight(float) const { return data_.line_height; }
float MediaValuesCached::RootLineHeight(float) const { return data_.line_height; }
float MediaValuesCached::CapFontSize(float) const { return data_.cap_size; }
float MediaValuesCached::RcapFontSize(float) const { return data_.cap_size; }
double MediaValuesCached::ViewportWidth() const { return data_.viewport_width; }
double MediaValuesCached::ViewportHeight() const { return data_.viewport_height; }
double MediaValuesCached::SmallViewportWidth() const { return data_.small_viewport_width; }
double MediaValuesCached::SmallViewportHeight() const { return data_.small_viewport_height; }
double MediaValuesCached::LargeViewportWidth() const { return data_.large_viewport_width; }
double MediaValuesCached::LargeViewportHeight() const { return data_.large_viewport_height; }
double MediaValuesCached::DynamicViewportWidth() const { return data_.dynamic_viewport_width; }
double MediaValuesCached::DynamicViewportHeight() const { return data_.dynamic_viewport_height; }
double MediaValuesCached::ContainerWidth() const { return 0; }
double MediaValuesCached::ContainerHeight() const { return 0; }
double MediaValuesCached::ContainerWidth(const ScopedCSSName&) const { return 0; }
double MediaValuesCached::ContainerHeight(const ScopedCSSName&) const { return 0; }

const AtomicString& HTMLAnchorElementBase::GetName() const {
  return g_null_atom;
}


CSSStyleSheet* ViewTransition::UAStyleSheet() const {
  return nullptr;
}

void ViewTransitionSupplement::OnViewTransitionsStyleUpdated(
    bool,
    const Vector<String>&,
    const std::optional<Vector<String>>&) {}

bool ThreadState::IsTakingHeapSnapshot() const {
  return false;
}

bool ThreadState::IsSweepingOnOwningThread() const {
  return false;
}

const char* ThreadState::CopyNameForHeapSnapshot(const char* name) const {
  return name;
}

CSSStyleSheetResource* CSSStyleSheetResource::Fetch(FetchParameters&,
                                                    ResourceFetcher*,
                                                    ResourceClient*) {
  return nullptr;
}

const String CSSStyleSheetResource::SheetText(const CSSParserContext*,
                                              MIMETypeCheck) const {
  return String();
}

network::mojom::ReferrerPolicy CSSStyleSheetResource::GetReferrerPolicy()
    const {
  return network::mojom::ReferrerPolicy::kDefault;
}

void CSSStyleSheetResource::Trace(Visitor* visitor) const {
  TextResource::Trace(visitor);
}

const ResourceRequestHead& Resource::LastResourceRequest() const {
  static ResourceRequestHead empty_request;
  return empty_request;
}

TextEncoding TextResource::Encoding() const {
  return Utf8Encoding();
}

bool HTMLEmbedElement::IsExposed() const {
  return false;
}

bool HTMLObjectElement::IsExposed() const {
  return false;
}

bool HTMLObjectElement::ContainsJavaApplet() const {
  return false;
}

bool HTMLLinkElement::StyleSheetIsLoading() const {
  return false;
}

void SpellChecker::RemoveSpellingAndGrammarMarkers(const HTMLElement&,
                                                   ElementsType) {}

void SpellChecker::RespondToChangedEnablement(const HTMLElement&, bool) {}

JSEventHandlerForContentAttribute* JSEventHandlerForContentAttribute::Create(
    ExecutionContext*,
    const QualifiedName&,
    const AtomicString&,
    JSEventHandler::HandlerType) {
  return nullptr;
}

void ReplaceChildrenWithText(ContainerNode*, const String&, ExceptionState&) {}

v8::Local<v8::Value>
V8UnionBooleanOrStringOrUnrestrictedDouble::DirectToV8(ScriptState*,
                                                       const String&) {
  return v8::Local<v8::Value>();
}

v8::Local<v8::Value>
V8UnionBooleanOrStringOrUnrestrictedDouble::DirectToV8(ScriptState*, bool) {
  return v8::Local<v8::Value>();
}

ToggleEvent::ToggleEvent(const AtomicString& type,
                         Event::Cancelable cancelable,
                         const String& old_state,
                         const String& new_state,
                         Element* source)
    : Event(type, Event::Bubbles::kNo, cancelable),
      old_state_(old_state),
      new_state_(new_state),
      source_(source) {}

const String& ToggleEvent::oldState() const {
  return old_state_;
}

const String& ToggleEvent::newState() const {
  return new_state_;
}

void ToggleEvent::Trace(Visitor* visitor) const {
  visitor->Trace(source_);
  Event::Trace(visitor);
}

CommandEvent::CommandEvent(const AtomicString& type,
                           const String& command,
                           Element* source)
    : Event(type, Event::Bubbles::kNo, Event::Cancelable::kNo),
      source_(source),
      command_(command) {}

void CommandEvent::Trace(Visitor* visitor) const {
  visitor->Trace(source_);
  Event::Trace(visitor);
}

void MenuSafeTriangle::MaybeCreate(HTMLMenuItemElement*, HTMLMenuListElement*) {}

void MenuSafeTriangle::Recheck() {}

CloseWatcher* CloseWatcher::Create(LocalDOMWindow&) {
  return nullptr;
}

void CloseWatcher::destroy() {}

void HTMLDialogElement::SetFocusForDialog() {}

bool HTMLInputElement::IsBaseAppearanceCombobox() const {
  return false;
}

AppearanceValue HTMLInputElement::AutoAppearance() const {
  return AppearanceValue::kAuto;
}

HTMLDataListElement* HTMLInputElement::DataList() const {
  return nullptr;
}

bool HTMLInputElement::IsTelephone() const {
  return false;
}

bool HTMLSubmitButtonBehavior::HandleActivation(Event&) {
  return false;
}

int KeyboardEvent::charCode() const {
  return 0;
}

void ElementInternals::SetBehaviors(HeapVector<Member<ElementBehavior>>,
                                    ExceptionState&) {}

Element* HTMLFormElement::FindDefaultButton() const {
  return nullptr;
}

HTMLElement* HTMLLabelElement::Control() const {
  return nullptr;
}

void FrameLoader::DispatchDocumentElementAvailable() {}

void FrameLoader::RunScriptsAtDocumentElementAvailable() {}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
void LayoutTextFragment::SetContentString(const String& content) {
  content_string_ = content;
}
#endif

const cc::SnapContainerData* PaintLayerScrollableArea::GetSnapContainerData()
    const {
  return nullptr;
}

SnappedQueryScrollSnapshot*
PaintLayerScrollableArea::GetSnappedQueryScrollSnapshot() {
  return nullptr;
}

SnappedQueryScrollSnapshot&
PaintLayerScrollableArea::EnsureSnappedQueryScrollSnapshot() {
  static SnappedQueryScrollSnapshot* snapshot =
      reinterpret_cast<SnappedQueryScrollSnapshot*>(
          sk_malloc_flags(sizeof(SnappedQueryScrollSnapshot), 1));
  return *snapshot;
}

PhysicalRect PaintLayerScrollableArea::LayoutContentRect(
    IncludeScrollbarsInRect) const {
  return PhysicalRect();
}

gfx::Size PaintLayerScrollableArea::ComputeScrollbarWidthsForViewportUnits(
    StyleBasedScrollbarData) const {
  return gfx::Size();
}

ScriptPromise<IDLUndefined> Fullscreen::ExitFullscreen(Document&,
                                                       ScriptState*,
                                                       ExceptionState*,
                                                       bool) {
  return ScriptPromise<IDLUndefined>();
}

void Fullscreen::RequestFullscreen(Element&) {}

URLPatternInit::URLPatternInit() = default;

void URLPatternInit::setProtocol(const String& value) {
  has_protocol_ = true;
  member_protocol_ = value;
}

void URLPatternInit::setHostname(const String& value) {
  has_hostname_ = true;
  member_hostname_ = value;
}

void URLPatternInit::setPort(const String& value) {
  has_port_ = true;
  member_port_ = value;
}

void URLPatternInit::setPathname(const String& value) {
  has_pathname_ = true;
  member_pathname_ = value;
}

void URLPatternInit::setSearch(const String& value) {
  has_search_ = true;
  member_search_ = value;
}

void URLPatternInit::setHash(const String& value) {
  has_hash_ = true;
  member_hash_ = value;
}

void URLPatternInit::setBaseURL(const String& value) {
  has_base_url_ = true;
  member_base_url_ = value;
}

URLPattern* URLPattern::Create(v8::Isolate*,
                               const V8UnionURLPatternInitOrUSVString*,
                               ExceptionState&) {
  return nullptr;
}

void V8UnionURLPatternInitOrUSVString::Trace(Visitor*) const {}

void Route::Trace(Visitor*) const {}

void Filter::Trace(Visitor* visitor) const {
}

ContainerTiming::ContainerTiming(LocalDOMWindow& window)
    : Supplement<LocalDOMWindow>(window) {}

ContainerTiming& ContainerTiming::From(LocalDOMWindow& window) {
  static Persistent<ContainerTiming> timing =
      MakeGarbageCollected<ContainerTiming>(window);
  return *timing;
}

void ContainerTiming::MaybeUpdateContainerRootIdentifier(
    Element*,
    const AtomicString&) {}

bool ContainerTiming::CanReportToContainerTiming() const {
  return false;
}

void ContainerTiming::EmitPerformanceEntries() {}

void ContainerTiming::OnElementPainted(const DOMPaintTimingInfo&,
                                       Element*,
                                       const gfx::RectF&) {}

void ContainerTiming::Trace(Visitor* visitor) const {
  Supplement<LocalDOMWindow>::Trace(visitor);
}

void StyleRuleToStyleSheetContentsMap::Add(
    const StyleRule*,
    const StyleSheetContents*) {}

const StyleSheetContents* StyleRuleToStyleSheetContentsMap::Lookup(
    const StyleRule*) const {
  return nullptr;
}

void StyleRuleToStyleSheetContentsMap::Trace(Visitor*) const {}

TracedValue::TracedValue() = default;
TracedValue::~TracedValue() = default;
void TracedValue::EndDictionary() {}
void TracedValue::EndArray() {}
void TracedValue::SetInteger(const char*, int) {}
void TracedValue::SetDouble(const char*, double) {}
void TracedValue::SetBoolean(const char*, bool) {}
void TracedValue::SetString(const char*, const String&) {}
void TracedValue::SetValue(const char*, TracedValue*) {}
void TracedValue::BeginArray(const char*) {}
void TracedValue::BeginDictionary(const char*) {}
void TracedValue::SetIntegerWithCopiedName(const char*, int) {}
void TracedValue::SetDoubleWithCopiedName(const char*, double) {}
void TracedValue::SetBooleanWithCopiedName(const char*, bool) {}
void TracedValue::SetStringWithCopiedName(const char*, const String&) {}
void TracedValue::BeginArrayWithCopiedName(const char*) {}
void TracedValue::BeginDictionaryWithCopiedName(const char*) {}
void TracedValue::PushInteger(int) {}
void TracedValue::PushDouble(double) {}
void TracedValue::PushBoolean(bool) {}
void TracedValue::PushString(const String&) {}
void TracedValue::BeginArray() {}
void TracedValue::BeginDictionary() {}
void TracedValue::AppendAsTraceFormat(std::string*) const {}
bool TracedValue::AppendToProto(ProtoAppender*) const {
  return false;
}

MarkupFormatter::MarkupFormatter(AbsoluteURLs resolve_urls,
                                 SerializationType serialization_type)
    : resolve_urls_method_(resolve_urls),
      serialization_type_(serialization_type) {}

bool MarkupFormatter::SerializeAsHTML() const {
  return serialization_type_ == SerializationType::kHTML;
}

void MarkupFormatter::AppendStartMarkup(StringBuilder&, const Node&) {}
void MarkupFormatter::AppendEndMarkup(StringBuilder&, const Element&) {}
void MarkupFormatter::AppendEndMarkup(StringBuilder&,
                                      const Element&,
                                      const AtomicString&,
                                      const AtomicString&) {}
void MarkupFormatter::AppendText(StringBuilder&, const Text&) {}
void MarkupFormatter::AppendStartTagOpen(StringBuilder&, const Element&) {}
void MarkupFormatter::AppendStartTagOpen(StringBuilder&,
                                         const AtomicString&,
                                         const AtomicString&) {}
void MarkupFormatter::AppendStartTagClose(StringBuilder&, const Element&) {}
String MarkupFormatter::ResolveURLIfNeeded(const Element&,
                                           const Attribute&) const {
  return String();
}
EntityMask MarkupFormatter::EntityMaskForText(const Text&) const {
  return kEntityMaskInPCDATA;
}
void MarkupFormatter::AppendAttributeValue(StringBuilder&,
                                           const String&,
                                           bool) {}
void MarkupFormatter::AppendAttributeAsHTML(StringBuilder&,
                                           const Attribute&,
                                           const String&) {}
void MarkupFormatter::AppendAttribute(StringBuilder&,
                                      const AtomicString&,
                                      const AtomicString&,
                                      const String&,
                                      bool) {}

bool ElementCannotHaveEndTag(const Node&) {
  return false;
}

class MarkupAccumulator::NamespaceContext {};

MarkupAccumulator::MarkupAccumulator(AbsoluteURLs absolute_urls,
                                     SerializationType serialization_type,
                                     const ShadowRootInclusion& inclusion,
                                     AttributesMode attributes_mode)
    : formatter_(absolute_urls, serialization_type),
      shadow_root_inclusion_(inclusion),
      prefix_index_(0),
      attributes_mode_(attributes_mode) {}

MarkupAccumulator::~MarkupAccumulator() = default;

AtomicString MarkupAccumulator::AppendElement(const Element&) {
  return g_empty_atom;
}

void MarkupAccumulator::AppendEndTag(const Element&, const AtomicString&) {}
void MarkupAccumulator::AppendAttribute(const Element&, const Attribute&) {}
MarkupAccumulator::EmitElementChoice MarkupAccumulator::WillProcessElement(
    const Element&) {
  return EmitElementChoice::kEmit;
}
void MarkupAccumulator::AppendCustomAttributes(const Element&) {}
MarkupAccumulator::EmitAttributeChoice MarkupAccumulator::WillProcessAttribute(
    const Element&,
    const Attribute&) const {
  return EmitAttributeChoice::kEmit;
}
std::pair<ShadowRoot*, HTMLTemplateElement*> MarkupAccumulator::GetShadowTree(
    const Element&) const {
  return {nullptr, nullptr};
}

const WrapperTypeInfo& HTMLTemplateElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTemplateElement");
const WrapperTypeInfo& Event::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Event");
const WrapperTypeInfo& Animation::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Animation");
const WrapperTypeInfo& AnimationEffect::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AnimationEffect");
const WrapperTypeInfo& AnimationTimeline::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AnimationTimeline");
const WrapperTypeInfo& ScrollTimeline::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ScrollTimeline");
const WrapperTypeInfo& ViewTimeline::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ViewTimeline");
const WrapperTypeInfo& KeyframeEffect::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("KeyframeEffect");
const WrapperTypeInfo& TimelineTrigger::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TimelineTrigger");
const WrapperTypeInfo& AnimationTrigger::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AnimationTrigger");
const WrapperTypeInfo& CSSUnitValue::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSUnitValue");
const WrapperTypeInfo& CSSNumericValue::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSNumericValue");
const WrapperTypeInfo& AnimationEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AnimationEvent");
const WrapperTypeInfo& TransitionEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TransitionEvent");
HTMLTemplateElement::HTMLTemplateElement(Document& document)
    : HTMLElement(html_names::kTemplateTag, document) {}
HTMLTemplateElement::~HTMLTemplateElement() = default;
DocumentFragment* HTMLTemplateElement::content() const {
  return nullptr;
}
ContainerNode* HTMLTemplateElement::InsertionTarget() const {
  return nullptr;
}
void HTMLTemplateElement::CloneNonAttributePropertiesFrom(
    const Element&,
    NodeCloningData&) {}
void HTMLTemplateElement::DidMoveToNewDocument(Document& old_document) {
  HTMLElement::DidMoveToNewDocument(old_document);
}
void HTMLTemplateElement::Trace(Visitor* visitor) const {
  HTMLElement::Trace(visitor);
}
void HTMLTemplateElement::FinishParsingChildren() {}

HTMLFormElement::HTMLFormElement(Document& document)
    : HTMLElement(html_names::kFormTag, document),
      listed_elements_are_dirty_(false),
      listed_elements_for_autofill_are_dirty_(false),
      image_elements_are_dirty_(false),
      has_elements_associated_by_parser_(false),
      has_elements_associated_by_form_attribute_(false),
      did_finish_parsing_children_(false),
      is_in_reset_function_(false) {}
HTMLFormElement::~HTMLFormElement() = default;
void HTMLFormElement::AttachLayoutTree(AttachContext& context) {
  HTMLElement::AttachLayoutTree(context);
}
void HTMLFormElement::DetachLayoutTree(bool performing_reattach) {
  HTMLElement::DetachLayoutTree(performing_reattach);
}
Node::InsertionNotificationRequest HTMLFormElement::InsertedInto(
    ContainerNode& insertion_point) {
  return HTMLElement::InsertedInto(insertion_point);
}
void HTMLFormElement::RemovedFrom(ContainerNode& insertion_point) {
  HTMLElement::RemovedFrom(insertion_point);
}
void HTMLFormElement::HandleLocalEvents(Event&) {}
void HTMLFormElement::AttributeChanged(
    const AttributeModificationParams& params) {
  HTMLElement::AttributeChanged(params);
}
void HTMLFormElement::ParseAttribute(const AttributeModificationParams& params) {
  HTMLElement::ParseAttribute(params);
}
bool HTMLFormElement::HasLegalLinkAttribute(const QualifiedName&) const {
  return false;
}
bool HTMLFormElement::IsURLAttribute(const Attribute&) const {
  return false;
}
void HTMLFormElement::FinishParsingChildren() {
  HTMLElement::FinishParsingChildren();
}
bool HTMLFormElement::MatchesValidityPseudoClasses() const {
  return true;
}
bool HTMLFormElement::IsValidElement() {
  return true;
}

const Vector<AtomicString>
ViewTransitionPseudoElementBase::ViewTransitionClassList() const {
  return Vector<AtomicString>();
}

CompositorKeyframeValue* CompositorKeyframeValueFactory::Create(
    const PropertyHandle&,
    const ComputedStyle&,
    double) {
  return nullptr;
}

bool KeyframeEffect::HasPlayingAnimation() const {
  return false;
}
bool KeyframeEffect::HasAnimation() const {
  return false;
}
bool KeyframeEffect::HasRevert() const {
  return false;
}
void KeyframeEffect::NotifySampledEffectRemovedFromEffectStack() {}
void KeyframeEffect::Trace(Visitor* visitor) const {
  AnimationEffect::Trace(visitor);
}
KeyframeEffect::KeyframeEffect(Element* target,
                               KeyframeEffectModelBase* model,
                               const Timing& timing,
                               Priority priority,
                               EventDelegate* event_delegate)
    : AnimationEffect(timing, event_delegate),
      effect_target_(target),
      target_element_(target),
      model_(model),
      priority_(priority),
      ignore_css_keyframes_(false) {}
KeyframeEffect::~KeyframeEffect() = default;
bool KeyframeEffect::Affects(const PropertyHandle&) const {
  return false;
}
bool KeyframeEffect::HasActiveAnimationsOnCompositor() const {
  return false;
}
bool KeyframeEffect::HasActiveAnimationsOnCompositor(
    const PropertyHandle&) const {
  return false;
}
bool KeyframeEffect::UpdateBoxSizeAndCheckTransformAxisAlignment(
    const gfx::SizeF&) {
  return false;
}
bool KeyframeEffect::IsIdentityOrTranslation() const {
  return true;
}
void KeyframeEffect::SetLogicalPropertyResolutionContext(
    WritingDirectionMode) {}
void KeyframeEffect::UpdateChildrenAndEffects() const {}
void KeyframeEffect::Attach(AnimationEffectOwner* owner) {
  AnimationEffect::Attach(owner);
}
void KeyframeEffect::Detach() {
  AnimationEffect::Detach();
}
AnimationTimeDelta KeyframeEffect::CalculateTimeToEffectChange(
    bool,
    std::optional<AnimationTimeDelta>,
    AnimationTimeDelta) const {
  return AnimationTimeDelta::Max();
}
std::optional<AnimationTimeDelta> KeyframeEffect::TimelineDuration() const {
  return std::nullopt;
}
InterpolationTypesMap::InterpolationTypesMap(const PropertyRegistry* registry,
                                             const Document& document)
    : document_(document), registry_(registry) {}
uint64_t InterpolationTypesMap::Version() const {
  return 0;
}
const InterpolationTypes* InterpolationTypesMap::Get(
    const PropertyHandle&) const {
  return nullptr;
}
InterpolationTypes* InterpolationTypesMap::CreateInterpolationTypesForCSSSyntax(
    const AtomicString&,
    const CSSSyntaxDefinition&,
    const PropertyRegistration&) {
  return nullptr;
}


bool StyleAdjuster::IsCacheCompatible(const ComputedStyle&,
                                      const ComputedStyle&,
                                      const ComputedStyle&,
                                      const ComputedStyle&) {
  return true;
}

void StyleAdjuster::AdjustComputedStyle(StyleResolverState&, Element*) {}

CompositingReasons
CompositingReasonFinder::PotentialCompositingReasonsFor3DTransform(
    const ComputedStyle&) {
  return CompositingReason::kNone;
}

LayoutWorklet* LayoutWorklet::From(LocalDOMWindow&) {
  return nullptr;
}

DocumentLayoutDefinition* const kInvalidDocumentLayoutDefinition = nullptr;


InterpolationQuality GetDefaultInterpolationQuality() {
  return kInterpolationLow;
}

MediaQueryExp::MediaQueryExp(const MediaQueryExp& other) = default;
MediaQueryExp::~MediaQueryExp() = default;

MediaQueryExp MediaQueryExp::Create(const AtomicString&,
                                    CSSParserTokenStream&,
                                    const CSSParserContext&,
                                    bool) {
  return MediaQueryExp();
}

MediaQueryExp MediaQueryExp::Create(const AtomicString&,
                                    const MediaQueryExpBounds&) {
  return MediaQueryExp();
}

MediaQueryExp MediaQueryExp::Create(const AtomicString&) {
  return MediaQueryExp();
}

MediaQueryExp MediaQueryExp::Create(const MediaQueryExpValue&,
                                    const MediaQueryExpBounds&) {
  return MediaQueryExp();
}

void MediaQueryExp::Trace(Visitor* visitor) const {
  visitor->Trace(reference_value_);
  visitor->Trace(bounds_);
}

bool MediaQueryExp::operator==(const MediaQueryExp& other) const {
  return type_ == other.type_ && media_feature_ == other.media_feature_;
}

bool MediaQueryExp::IsViewportDependent() const {
  return false;
}

bool MediaQueryExp::IsDeviceDependent() const {
  return false;
}

bool MediaQueryExp::IsWidthDependent() const {
  return false;
}

bool MediaQueryExp::IsHeightDependent() const {
  return false;
}

bool MediaQueryExp::IsInlineSizeDependent() const {
  return false;
}

bool MediaQueryExp::IsBlockSizeDependent() const {
  return false;
}

String MediaQueryExp::Serialize() const {
  return String();
}

unsigned MediaQueryExp::GetUnitFlags() const {
  return 0;
}

std::optional<MediaQueryExpValue> MediaQueryExpValue::Consume(
    const String&,
    CSSParserTokenStream&,
    const CSSParserContext&,
    bool) {
  return std::nullopt;
}

unsigned MediaQueryExpValue::GetUnitFlags() const {
  return 0;
}

String MediaQueryExpValue::CssText() const {
  return String();
}

void MediaQueryFeatureExpNode::Trace(Visitor* visitor) const {
  visitor->Trace(exp_);
}

unsigned MediaQueryFeatureExpNode::GetUnitFlags() const {
  return 0;
}

bool MediaQueryFeatureExpNode::IsViewportDependent() const {
  return false;
}

bool MediaQueryFeatureExpNode::IsDeviceDependent() const {
  return false;
}

bool MediaQueryFeatureExpNode::IsWidthDependent() const {
  return false;
}

bool MediaQueryFeatureExpNode::IsHeightDependent() const {
  return false;
}

bool MediaQueryFeatureExpNode::IsInlineSizeDependent() const {
  return false;
}

bool MediaQueryFeatureExpNode::IsBlockSizeDependent() const {
  return false;
}

KleeneValue MediaQueryFeatureExpNode::Evaluate(
    ConditionalExpNodeVisitor&) const {
  return KleeneValue::kUnknown;
}

void MediaQueryFeatureExpNode::SerializeTo(StringBuilder&) const {}

std::optional<double> MediaValues::InlineSize() const {
  return Width();
}

std::optional<double> MediaValues::BlockSize() const {
  return Height();
}

bool MediaValues::SnappedBlock() const {
  return false;
}

bool MediaValues::SnappedInline() const {
  return false;
}

MediaValues* MediaValues::CreateDynamicIfFrameExists(LocalFrame* frame) {
  return MakeGarbageCollected<MediaValuesDynamic>(frame);
}

const unsigned char* SelectorStatisticsFlag::GetCategoryGroupEnabled() {
  static const unsigned char disabled = 0;
  return &disabled;
}

void SelectorStatisticsCollector::ReserveCapacity(wtf_size_t) {}
void SelectorStatisticsCollector::BeginCollectionForRule(const RuleData*) {}
void SelectorStatisticsCollector::EndCollectionForCurrentRule() {}

String IdentifiersFactory::IdForCSSStyleSheet(const CSSStyleSheet*) {
  return String();
}

const StyleSheetContents*
InvalidationSetToSelectorMap::LookupStyleSheetContentsForRule(
    const StyleRule*) {
  return nullptr;
}

void InvalidationSetToSelectorMap::RemoveEntriesForInvalidationSet(
    const InvalidationSet*) {}

InvalidationSetToSelectorMap::CombineScope::CombineScope(
    const InvalidationSet*,
    const InvalidationSet*) {}
InvalidationSetToSelectorMap::CombineScope::~CombineScope() = default;

InvalidationSetToSelectorMap::SelectorScope::SelectorScope(StyleRule*,
                                                           unsigned) {}
InvalidationSetToSelectorMap::SelectorScope::~SelectorScope() = default;

InvalidationSetToSelectorMap::StyleSheetContentsScope::StyleSheetContentsScope(
    const StyleSheetContents*) {}
InvalidationSetToSelectorMap::StyleSheetContentsScope::~StyleSheetContentsScope() =
    default;

void InvalidationSetToSelectorMap::RecordInvalidationSetEntry(
    const InvalidationSet*,
    SelectorFeatureType,
    const AtomicString&) {}

void InvalidationSetToSelectorMap::StartOrStopTrackingIfNeeded(
    const TreeScope&,
    const StyleEngine&) {}

String DescendantInvalidationSetToIdString(const InvalidationSet&) {
  return String();
}

template <RuleInvalidationDataVisitorType VisitorType>
RuleInvalidationDataVisitor<
    VisitorType>::RuleInvalidationDataVisitor(RuleInvalidationDataType& data)
    : rule_invalidation_data_(data) {}

template <RuleInvalidationDataVisitorType VisitorType>
SelectorPreMatch
RuleInvalidationDataVisitor<VisitorType>::
    CollectFeaturesFromSelector(const CSSSelector&, const StyleScope*) {
  return SelectorPreMatch::kMayMatch;
}

template SelectorPreMatch
RuleInvalidationDataVisitor<RuleInvalidationDataVisitorType::kBuilder>::
    CollectFeaturesFromSelector(const CSSSelector&, const StyleScope*);

RuleInvalidationDataBuilder::RuleInvalidationDataBuilder(
    RuleInvalidationData& data)
    : RuleInvalidationDataVisitor<RuleInvalidationDataVisitorType::kBuilder>(
          data) {}
void RuleInvalidationDataBuilder::Merge(const RuleInvalidationData&) {}

RuleInvalidationDataTracer::RuleInvalidationDataTracer(
    const RuleInvalidationData& data)
    : RuleInvalidationDataVisitor<RuleInvalidationDataVisitorType::kTracer>(
          data) {}
void RuleInvalidationDataTracer::TraceInvalidationSetsForSelector(
    const CSSSelector&) {}

StyleInvalidator::StyleInvalidator(PendingInvalidationMap& map)
    : pending_invalidation_map_(map) {}
StyleInvalidator::~StyleInvalidator() = default;
void StyleInvalidator::Invalidate(Document&, Element*) {}

const Path& StylePath::GetPath() const {
  static const Path* empty_path = new Path();
  return *empty_path;
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
gfx::SizeF SVGViewportResolver::ResolveViewport() const {
  return gfx::SizeF();
}
SVGViewportResolver::SVGViewportResolver(const SVGElement&)
    : context_object_(nullptr) {}
float SVGViewportResolver::ViewportDimension(SVGLengthMode) const {
  return 0.0f;
}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
Glyph SimpleFontData::GlyphForCharacter(UChar32) const {
  return 0;
}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
UChar32 Character::FullwidthVariant(UChar32 code_point) {
  return code_point;
}

UChar32 Character::FullSizeKanaVariant(UChar32 code_point) {
  return code_point;
}

wtf_size_t NumGraphemeClusters(const StringView& string) {
  return string.length();
}
#endif

bool Deprecation::IsDeprecated(mojom::WebFeature) {
  return false;
}

CSSSelectorWatch* CSSSelectorWatch::FromIfExists(Document&) {
  return nullptr;
}

DocumentSpeculationRules& DocumentSpeculationRules::From(Document&) {
  static DocumentSpeculationRules* rules =
      reinterpret_cast<DocumentSpeculationRules*>(
          sk_malloc_flags(sizeof(DocumentSpeculationRules), 1));
  return *rules;
}

bool AdTracker::IsAdScriptExecutingInDocument(Document*, StackType) {
  return false;
}
AdTracker::AdTracker(LocalFrame* frame) : local_root_(frame) {}
AdTracker::~AdTracker() = default;
void AdTracker::Trace(Visitor*) const {}
std::optional<AdProvenance> AdTracker::CalculateIfAdSubresource(
    ExecutionContext*,
    const KURL&,
    ResourceType,
    const FetchInitiatorInfo&,
    std::optional<AdProvenance> known_ad_provenance,
    bool) {
  return known_ad_provenance;
}
bool AdTracker::IsAdScriptInStack(StackType,
                                  MonkeyPatchableApi,
                                  AdScriptAncestry*) {
  return false;
}
void AdTracker::Shutdown() {}

LinkStyle* HTMLLinkElement::GetLinkStyle() const {
  return nullptr;
}

Referrer::Referrer()
    : referrer(ClientReferrerString()),
      referrer_policy(network::mojom::ReferrerPolicy::kDefault) {}

const AtomicString& Referrer::ClientReferrerString() {
  static const AtomicString* client = new AtomicString("client");
  return *client;
}


Element* DisplayLockUtilities::LockedInclusiveAncestorPreventingStyleWithinTreeScope(
    const Node&) {
  return nullptr;
}
Node* DOMNodeIds::NodeForId(DOMNodeId) {
  return nullptr;
}

unsigned FirstLetterPseudoElement::FirstLetterLength(
    const String& string,
    bool,
    Punctuation& punctuation) {
  punctuation = Punctuation::kNotSeen;
  return string.empty() ? 0u : 1u;
}

LocalSVGResource::LocalSVGResource(TreeScope& tree_scope, const AtomicString&)
    : tree_scope_(&tree_scope) {}
void LocalSVGResource::Unregister() {}
void LocalSVGResource::Trace(Visitor* visitor) const {
  SVGResource::Trace(visitor);
  visitor->Trace(tree_scope_);
}

DOMSelection::DOMSelection(const TreeScope*) : ExecutionContextClient(nullptr) {}
void DOMSelection::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  ExecutionContextClient::Trace(visitor);
}

Element* Fullscreen::FullscreenElementForBindingFrom(TreeScope&) {
  return nullptr;
}

bool Fullscreen::IsFullscreenFlagSetFor(const Element&) {
  return false;
}

PictureInPictureController& PictureInPictureController::From(Document&) {
  static PictureInPictureController* controller =
      reinterpret_cast<PictureInPictureController*>(
          sk_malloc_flags(sizeof(PictureInPictureController), 1));
  return *controller;
}

bool PictureInPictureController::IsElementInPictureInPicture(const Element*) {
  return false;
}

void RadioButtonGroupScope::Trace(Visitor*) const {}

ElementInternals::ElementInternals(HTMLElement& target) : target_(target) {}

void ElementInternals::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  ListedElement::Trace(visitor);
  visitor->Trace(target_);
}

bool ElementInternals::IsElementInternals() const { return true; }
bool ElementInternals::IsEnumeratable() const { return false; }
void ElementInternals::AppendToFormData(FormData&) {}
void ElementInternals::DidChangeForm() {}
bool ElementInternals::HasBadInput() const { return false; }
bool ElementInternals::PatternMismatch() const { return false; }
bool ElementInternals::RangeOverflow() const { return false; }
bool ElementInternals::RangeUnderflow() const { return false; }
bool ElementInternals::StepMismatch() const { return false; }
bool ElementInternals::TooLong() const { return false; }
bool ElementInternals::TooShort() const { return false; }
bool ElementInternals::TypeMismatch() const { return false; }
bool ElementInternals::ValueMissing() const { return false; }
bool ElementInternals::CustomError() const { return false; }
bool ElementInternals::HasState(const AtomicString&) const { return false; }
String ElementInternals::validationMessage() const { return String(); }
String ElementInternals::ValidationSubMessage() const { return String(); }
Element& ElementInternals::ValidationAnchor() const { return *target_; }
void ElementInternals::DisabledStateMightBeChanged() {}
bool ElementInternals::ClassSupportsStateRestore() const { return false; }
bool ElementInternals::ShouldSaveAndRestoreFormControlState() const {
  return false;
}
FormControlState ElementInternals::SaveFormControlState() const {
  return FormControlState();
}
void ElementInternals::RestoreFormControlState(const FormControlState&) {}

DisplayLockContext::DisplayLockContext(Element* element) : element_(element) {}

void CSSPseudoElementsCacheData::CacheCSSPseudoElement(
    PseudoId pseudo_id,
    const AtomicString& pseudo_argument,
    CSSPseudoElement& pseudo_element) {
  pseudo_elements_map_.Set(PseudoElementCacheKey(pseudo_id, pseudo_argument),
                           &pseudo_element);
}

CSSPseudoElement* CSSPseudoElementsCacheData::GetCSSPseudoElement(
    PseudoId pseudo_id,
    const AtomicString& pseudo_argument) {
  auto it = pseudo_elements_map_.find(
      PseudoElementCacheKey(pseudo_id, pseudo_argument));
  return it == pseudo_elements_map_.end() ? nullptr : it->value.Get();
}

void CSSPseudoElementsCacheData::Trace(Visitor* visitor) const {
  visitor->Trace(pseudo_elements_map_);
}

AnchorPositionVisibilityObserver::AnchorPositionVisibilityObserver(
    Element& anchored_element)
    : anchored_element_(&anchored_element) {}

void AnchorPositionVisibilityObserver::MonitorAnchor(const Element* anchor) {
  anchor_element_ = anchor;
}
void AnchorPositionVisibilityObserver::UpdateForCssAnchorVisibility() {}
void AnchorPositionVisibilityObserver::UpdateForChainedAnchorVisibility(
    const HeapHashSet<WeakMember<PostLayoutSnapshotClient>>&) {}

AnchorPositionScrollData::AnchorPositionScrollData(Element* anchored_element)
    : PostLayoutSnapshotClient(nullptr), anchored_element_(anchored_element) {}

AnchorPositionScrollData::~AnchorPositionScrollData() = default;

OverscrollAreaTracker::OverscrollAreaTracker(Element*) {}

void ContainerQueryData::Trace(Visitor*) const {}

void ResizeObservation::Trace(Visitor* visitor) const {
  visitor->Trace(target_);
}

void CloseWatcher::Trace(Visitor* visitor) const {
  EventTarget::Trace(visitor);
  ExecutionContextClient::Trace(visitor);
}

DisplayAdElementMonitor::DisplayAdElementMonitor(
    Element* element,
    AdProvenance ad_provenance)
    : element_(element), ad_provenance_(std::move(ad_provenance)) {}

void DisplayAdElementMonitor::Trace(Visitor* visitor) const {
  visitor->Trace(element_);
}

void FlatTreeNodeData::Trace(Visitor* visitor) const {
  visitor->Trace(assigned_slot_);
  visitor->Trace(previous_in_assigned_nodes_);
  visitor->Trace(next_in_assigned_nodes_);
  visitor->Trace(manually_assigned_slot_);
}

DOMNodeId DOMNodeIds::IdForNode(Node*) {
  return 0;
}

Vector<AtomicString> const
ViewTransitionPseudoElementBase::GetContainedViewTransitionNames() const {
  return {};
}

const String& TrustedScript::toString() const {
  return script_;
}

String TrustedTypesCheckForScript(const String& script,
                                  const ExecutionContext*,
                                  const AtomicString&,
                                  const AtomicString&,
                                  ExceptionState&) {
  return script;
}
String TrustedTypesCheckForScript(
    const V8UnionStringOrTrustedScript*,
    const ExecutionContext*,
    const AtomicString&,
    const AtomicString&,
    ExceptionState&) {
  return String();
}
String TrustedTypesCheckForScript(
    const V8UnionStringLegacyNullToEmptyStringOrTrustedScript*,
    const ExecutionContext*,
    const AtomicString&,
    const AtomicString&,
    ExceptionState&) {
  return String();
}
String TrustedTypesCheckForScriptURL(
    const V8UnionTrustedScriptURLOrUSVString*,
    const ExecutionContext*,
    const AtomicString&,
    const AtomicString&,
    ExceptionState&) {
  return String();
}

bool SVGImage::IsInSVGImage(const Node*) {
  return false;
}

void SVGElement::SetNeedsStyleRecalcForInstances(
    StyleChangeType,
    const StyleChangeReasonForTracing&) {}

SVGElement* SVGElement::CorrespondingElement() const {
  return nullptr;
}

bool EventHandler::UsesHandCursor(const Node*) {
  return false;
}

LayoutShiftTracker::ReattachHookScope::ReattachHookScope(const Node&) {}
LayoutShiftTracker::ReattachHookScope::~ReattachHookScope() = default;
void LayoutShiftTracker::ReattachHookScope::NotifyAttach(const Node&) {}
void LayoutShiftTracker::ReattachHookScope::NotifyDetach(const Node&) {}
void LayoutShiftTracker::Trace(Visitor*) const {}

void EventHandlerRegistry::DidAddEventHandler(EventTarget&,
                                              EventHandlerClass) {}
void EventHandlerRegistry::DidRemoveEventHandler(EventTarget&,
                                                 EventHandlerClass) {}
void EventHandlerRegistry::DidAddEventHandler(EventTarget&,
                                              const AtomicString&,
                                              const AddEventListenerOptions*) {}
void EventHandlerRegistry::DidRemoveEventHandler(
    EventTarget&,
    const AtomicString&,
    const AddEventListenerOptions*) {}
void EventHandlerRegistry::DidRemoveAllEventHandlers(EventTarget&) {}
void EventHandlerRegistry::DidMoveOutOfLocalRoot(EventTarget&) {}
void EventHandlerRegistry::DidMoveIntoLocalRoot(EventTarget&) {}
const EventTargetSet* EventHandlerRegistry::EventHandlerTargets(
    EventHandlerClass) const {
  return nullptr;
}

void DocumentMarkerController::RemoveMarkersForNode(
    const Text&,
    DocumentMarker::MarkerTypes) {}

WebPluginContainerImpl* LayoutEmbeddedContent::Plugin() const {
  return nullptr;
}

void HTMLQuoteElement::AdjustPseudoStyleLocale(ComputedStyleBuilder&) {}

bool HTMLMenuItemElement::IsCheckable() const {
  return false;
}
bool HTMLMenuItemElement::ShouldAppearChecked() const {
  return false;
}
HTMLMenuOwnerElement* HTMLMenuItemElement::OwningMenuElement() const {
  return nullptr;
}
bool HTMLMenuItemElement::IsSubmenuOpen() const {
  return false;
}

bool HTMLInputElement::IsCheckable() const {
  return false;
}

bool HTMLInputElement::HasBeenPasswordField() const {
  return false;
}

bool SelectorQuery::Matches(Element&) const {
  return false;
}

Element* SelectorQuery::Closest(Element&) const {
  return nullptr;
}

void PointerLockController::RequestPointerLock(
    ScriptPromiseResolver<IDLUndefined>*,
    Element*,
    const PointerLockOptions*) {}

DOMException::DOMException(DOMExceptionCode code,
                           const char* name,
                           const char* message)
    : legacy_code_(static_cast<uint16_t>(code)),
      name_(name ? name : ""),
      sanitized_message_(message ? message : ""),
      unsanitized_message_(message ? message : "") {}

void DisplayLockContext::DidMoveToNewDocument(Document& document) {
  document_ = &document;
}


Attr::Attr(Element& element, const QualifiedName& name)
    : Node(&element.GetTreeScope(), kCreateAttribute),
      element_(&element),
      name_(name) {}

Attr::Attr(Document& document, const QualifiedName& name, const AtomicString& value)
    : Node(&document, kCreateAttribute),
      name_(name),
      standalone_value_or_attached_local_name_(value) {}

Attr::~Attr() = default;

const AtomicString& Attr::value() const {
  return standalone_value_or_attached_local_name_;
}

void Attr::setValue(const AtomicString&, ExceptionState&) {}

void Attr::Trace(Visitor* visitor) const {
  Node::Trace(visitor);
  visitor->Trace(element_);
}

void PageAnimator::SetHasInlineStyleMutation() {}

CSSPropertyValueSet* ComputePresentationAttributeStyle(Element&) {
  return nullptr;
}

AtomicString DefaultLanguage() {
  return g_empty_atom;
}

bool V8DOMActivityLogger::HasActivityLoggerInIsolatedWorlds() {
  return false;
}

V8DOMActivityLogger* V8DOMActivityLogger::CurrentActivityLoggerIfIsolatedWorld(
    v8::Isolate*) {
  return nullptr;
}

namespace focusgroup {
bool IsActualFocusgroup(const FocusgroupData&) {
  return false;
}
}  // namespace focusgroup

bool RuntimeEnabledFeaturesBase::is_check_visibility_extra_properties_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_customizable_combobox_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_edit_context_assignment_as_per_spec_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_element_capture_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_element_internals_behaviors_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_remove_visible_selection_in_dom_selection_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_spat_nav_uses_cursor_inheritance_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_get_computed_style_outside_flat_tree_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_element_interface_enabled_ = false;

bool RuntimeEnabledFeaturesBase::ShadowRootAdoptedStyleSheetEnabled(
    const FeatureContext*) {
  return false;
}

bool RuntimeEnabledFeaturesBase::ContainerTimingEnabled(
    const FeatureContext*) {
  return false;
}

bool SVGElement::IsOutermostSVGSVGElement() const {
  return false;
}
bool SVGElement::IsResourceTarget() const {
  return false;
}

void ScrollMarkerGroupData::ClearFocusGroup() {
  focus_group_.clear();
}

void ScrollMarkerGroupData::ClearScrollableAreaSubscriptions() {}

Element* DisplayLockUtilities::LockedAncestorPreventingPaint(const Node&) {
  return nullptr;
}

Element* DisplayLockUtilities::LockedAncestorPreventingPaint(
    const LayoutObject&) {
  return nullptr;
}

bool DisplayLockUtilities::IsDisplayLockedPreventingPaint(const Node*, bool) {
  return false;
}

bool SVGElement::HasSVGParent() const {
  return false;
}

void EditContext::AttachElement(HTMLElement*) {}

void EditContext::DetachElement(HTMLElement*) {}

const HeapVector<Member<HTMLElement>>& EditContext::attachedElements() {
  static const HeapVector<Member<HTMLElement>> elements;
  return elements;
}

const FrozenArray<Element>* ElementInternals::GetElementArrayAttribute(
    const QualifiedName&) const {
  return nullptr;
}

ElementBehavior* ElementInternals::FindBehaviorByType(
    const WrapperTypeInfo*) const {
  return nullptr;
}

CustomElementDefinition* CustomElementRegistry::DefinitionForName(
    const AtomicString&) const {
  return nullptr;
}

void Attr::AttachToElement(Element* element, const AtomicString& local_name) {
  element_ = element;
  standalone_value_or_attached_local_name_ = local_name;
}

MutationRecord* MutationRecord::CreateAttributes(Node*,
                                                 const QualifiedName&,
                                                 const AtomicString&) {
  return nullptr;
}

LocalDOMWindow* IncumbentDOMWindow(v8::Isolate*) {
  return nullptr;
}

bool Frame::AllowFocusWithoutUserActivation() {
  return false;
}

bool EventHandler::IsHandlingKeyEvent() const {
  return false;
}

bool EventListenerMap::ContainsJSBasedEventListeners(
    const AtomicString&) const {
  return false;
}

bool IsSpatialNavigationEnabled(const LocalFrame*) {
  return false;
}

bool IsScrollableNode(const Node*) {
  return false;
}

void PaintLayerScrollableArea::UpdateFocusDataForSnapAreas() {}

void ScrollMarkerPseudoElement::Dispose() {}

ColumnPseudoElement::ColumnPseudoElement(Element* element, wtf_size_t index)
    : IndexedPseudoElement(element, kPseudoIdColumn, index) {}

ScrollMarkerPseudoElement::ScrollMarkerPseudoElement(Element* element)
    : PseudoElement(element, kPseudoIdScrollMarker) {}

FocusEvent::FocusEvent(const AtomicString& type,
                       Bubbles bubbles,
                       AbstractView* view,
                       int detail,
                       EventTarget* related_target,
    InputDeviceCapabilities* source_capabilities)
    : UIEvent(type,
              bubbles,
              Cancelable::kNo,
              ComposedMode::kScoped,
              base::TimeTicks::Now(),
              view,
              detail,
              source_capabilities),
      related_target_(related_target) {}

#if defined(HTML_CSS_RENDERER_STANDALONE)
void ReplaceChildrenWithFragment(ContainerNode* container,
                                 DocumentFragment* fragment,
                                 ExceptionState& exception_state) {
  DCHECK(container);
  ContainerNode* container_node(container);

  ChildListMutationScope mutation(*container_node);

  if (!fragment->firstChild()) {
    container_node->RemoveChildren();
    return;
  }

  if (container_node->HasOneChild()) {
    container_node->ReplaceChild(fragment, container_node->firstChild(),
                                 exception_state);
    return;
  }

  container_node->RemoveChildren();
  container_node->AppendChild(fragment, exception_state);
}
#else
void ReplaceChildrenWithFragment(ContainerNode*,
                                 DocumentFragment*,
                                 ExceptionState&) {}
#endif

String TrustedTypesCheckForHTML(
    const V8UnionStringLegacyNullToEmptyStringOrTrustedHTML*,
    const ExecutionContext*,
    const AtomicString&,
    const AtomicString&,
    ExceptionState&) {
  return String();
}

void MergeWithNextTextNode(Text*, ExceptionState&) {}

bool EventHandler::IsPointerEventActive(int) {
  return false;
}

void EventHandler::SetPointerCapture(int, Element*) {}

void EventHandler::ReleasePointerCapture(int, Element*) {}

bool EventHandler::HasPointerCapture(int, const Element*) const {
  return false;
}

String Element::innerText(TextVisitor*) {
  return textContent(true);
}

StyleRecalcContext StyleRecalcContext::FromAncestors(Element&) {
  return StyleRecalcContext();
}

PseudoElement* ViewTransitionTransitionElement::
    FindViewTransitionGroupPseudoElement(const AtomicString&) {
  return nullptr;
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
PseudoId ViewTransitionUtils::ParentViewTransitionPseudoId(PseudoId) {
  return kPseudoIdNone;
}
#endif

std::pair<PseudoId, AtomicString>
CSSPseudoElement::ConvertTypeToSupportedPseudoId(const AtomicString&) {
  return {kPseudoIdNone, g_null_atom};
}

bool CSSPseudoElement::IsSupportedTypeForCSSPseudoElement(PseudoId) {
  return false;
}

std::pair<PseudoId, AtomicString> CSSPseudoElement::GetViewTransitionParent(
    PseudoId,
    const AtomicString&) {
  return {kPseudoIdNone, g_null_atom};
}

CSSPseudoElement* CSSPseudoElement::pseudo(PseudoId,
                                           const AtomicString&) {
  return nullptr;
}

CSSPseudoElement::CSSPseudoElement(Element& element,
                                   PseudoId pseudo_id,
                                   const AtomicString& pseudo_argument)
    : pseudo_id_(pseudo_id),
      pseudo_argument_(pseudo_argument),
      element_(&element) {}

void NamedNodeMap::Trace(Visitor*) const {}

void DOMTokenList::Trace(Visitor*) const {}

void DOMRectList::Trace(Visitor*) const {}

void LayoutSVGText::NotifySubtreeStructureChanged(LayoutObject*, const char*) {}

LayoutSVGText* LayoutSVGText::LocateLayoutSVGTextAncestor(LayoutObject*) {
  return nullptr;
}

float SVGLayoutSupport::CalculateScreenFontSizeScalingFactor(
    const LayoutObject*) {
  return 1.0f;
}

void AnchorPositionScrollData::Trace(Visitor* visitor) const {
  PostLayoutSnapshotClient::Trace(visitor);
  visitor->Trace(anchored_element_);
}

void DisplayLockContext::WillStartLifecycleUpdate(const LocalFrameView&) {}

void DisplayLockContext::DidFinishLayout() {}

bool AnchorPositionScrollData::UpdateSnapshot() {
  return false;
}

bool AnchorPositionScrollData::ShouldScheduleNextService() {
  return false;
}
bool AnchorPositionScrollData::IsActive() const {
  return false;
}

void OverscrollAreaTracker::Trace(Visitor*) const {}

void DisplayAdElementMonitor::DidFinishLifecycleUpdate(
    const LocalFrameView&) {}

void OverscrollAreaTracker::RemoveAllOverscroll() {}
void OverscrollAreaTracker::AddOverscroll(Element*) {}

void UndoStack::ElementRemoved(Element*) {}

void ColumnPseudoElement::AttachLayoutTree(AttachContext&) {}
void ColumnPseudoElement::DetachLayoutTree(bool) {}
bool ColumnPseudoElement::LayoutObjectIsNeeded(const DisplayStyle&) const {
  return false;
}

StyleRecalcContext StyleRecalcContext::FromPseudoElementAncestors(Element&,
                                                                  PseudoId) {
  return StyleRecalcContext();
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
void ViewTransitionUtils::ForEachTransitionPseudo(
    const Element&,
    base::FunctionRef<void(PseudoElement*)>,
    Filter) {}

CSSSelectorWatch& CSSSelectorWatch::From(Document& document) {
  static CSSSelectorWatch* watch =
      reinterpret_cast<CSSSelectorWatch*>(new char[sizeof(CSSSelectorWatch)]);
  return *watch;
}

void CSSSelectorWatch::UpdateSelectorMatches(const Vector<String>&,
                                             const Vector<String>&) {}

void DisplayLockContext::DetachLayoutTree() {}

void DocumentSpeculationRules::LinkGainedOrLostComputedStyle(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::LinkMatchedSelectorsUpdated(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::ChildStyleRecalcBlocked(Element*) {}
void DocumentSpeculationRules::DidStyleChildren(Element*) {}

void DisplayLockContext::SetRequestedState(EContentVisibility state) {
  state_ = state;
}

const ComputedStyle* DisplayLockContext::AdjustElementStyle(
    const ComputedStyle* style) const {
  return style;
}

bool HTMLMenuItemElement::ShouldHaveExpandIcon() const {
  return false;
}

bool RuntimeEnabledFeaturesBase::
    is_html_interest_for_interest_button_pseudo_enabled_ = false;

void DisplayLockContext::DidStyleSelf() {}
void DisplayLockContext::DidStyleChildren() {}

ViewTransition* ViewTransitionUtils::GetTransition(const Element&) {
  return nullptr;
}
#endif

int DisplayLockDocumentState::LockedDisplayLockCount() const {
  return 0;
}

#if defined(HTML_CSS_RENDERER_STANDALONE)
CSSSelectorWatch& CSSSelectorWatch::From(Document&) {
  alignas(CSSSelectorWatch) static unsigned char storage[sizeof(CSSSelectorWatch)];
  return *reinterpret_cast<CSSSelectorWatch*>(storage);
}
void CSSSelectorWatch::UpdateSelectorMatches(const Vector<String>&,
                                             const Vector<String>&) {}
#endif

LayoutText* FirstLetterPseudoElement::FirstLetterTextLayoutObject(
    const Element&) {
  return nullptr;
}

bool ViewTransition::HasIncompatibleStyle() const {
  return true;
}

bool ViewTransition::IsTerminalState(State) {
  return true;
}

void ViewTransition::SkipTransitionSoon() {}

bool ViewTransition::IsGeneratingPseudo(
    const ViewTransitionPseudoElementBase&) const {
  return false;
}

const Vector<AtomicString>&
ViewTransitionPseudoElementBase::GetViewTransitionNames() const {
  static const Vector<AtomicString> names;
  return names;
}

const AtomicString& ViewTransitionPseudoElementBase::GetContainingGroupName(
    const AtomicString&) const {
  return g_null_atom;
}

VisibleSelection FrameSelection::ComputeVisibleSelectionInDOMTreeDeprecated()
    const {
  return VisibleSelection();
}

template <typename Strategy>
Element* VisibleSelectionTemplate<Strategy>::RootEditableElement() const {
  return nullptr;
}

SetSelectionOptions::Builder::Builder() = default;
SetSelectionOptions SetSelectionOptions::Builder::Build() const {
  return data_;
}
SetSelectionOptions::Builder& SetSelectionOptions::Builder::SetShouldCloseTyping(
    bool value) {
  data_.should_close_typing_ = value;
  return *this;
}
SetSelectionOptions::Builder&
SetSelectionOptions::Builder::SetShouldClearTypingStyle(bool value) {
  data_.should_clear_typing_style_ = value;
  return *this;
}
SetSelectionOptions::Builder& SetSelectionOptions::Builder::SetDoNotSetFocus(
    bool value) {
  data_.do_not_set_focus_ = value;
  return *this;
}

template <>
SelectionInDOMTree::Builder::Builder() = default;

template <>
SelectionInDOMTree::Builder& SelectionInDOMTree::Builder::Collapse(
    const Position& position) {
  selection_.anchor_ = position;
  selection_.focus_ = position;
  return *this;
}

template <>
SelectionInDOMTree SelectionInDOMTree::Builder::Build() const {
  return selection_;
}

VisibleSelection CreateVisibleSelection(const SelectionInDOMTree&) {
  return VisibleSelection();
}

template <typename Strategy>
SelectionTemplate<Strategy> VisibleSelectionTemplate<Strategy>::AsSelection()
    const {
  return SelectionTemplate<Strategy>();
}

void FrameSelection::SetSelection(const SelectionInDOMTree&,
                                  const SetSelectionOptions&) {}

void FrameSelection::RevealSelection(
    const mojom::blink::ScrollAlignment&,
    RevealExtentOption) {}

PositionWithAffinity AdjustForEditingBoundary(
    const PositionWithAffinity& position) {
  return position;
}

PositionWithAffinity AdjustForEditingBoundary(const Position& position) {
  return PositionWithAffinity(position);
}

IndexedPseudoElement::IndexedPseudoElement(Element* parent,
                                           PseudoId pseudo_id,
                                           wtf_size_t index,
                                           const AtomicString& argument)
    : PseudoElement(parent, pseudo_id, argument), index_(index) {}

void ScrollMarkerPseudoElement::Trace(Visitor* visitor) const {
  Element::Trace(visitor);
}
void ScrollMarkerPseudoElement::AttachLayoutTree(AttachContext&) {}
void ScrollMarkerPseudoElement::DefaultEventHandler(Event&) {}
void ScrollMarkerPseudoElement::SetHasFocusWithinUpToAncestor(bool,
                                                              Element*,
                                                              bool) {}
void ScrollMarkerPseudoElement::SetActive(bool) {}
void ScrollMarkerPseudoElement::SetHovered(bool) {}

void FocusEvent::Trace(Visitor* visitor) const {
  UIEvent::Trace(visitor);
  visitor->Trace(related_target_);
}
const AtomicString& FocusEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}
bool FocusEvent::IsFocusEvent() const {
  return true;
}
DispatchEventResult FocusEvent::DispatchEvent(EventDispatcher& dispatcher) {
  return DispatchEventResult::kNotCanceled;
}

void Attr::setNodeValue(const String& value, ExceptionState&) {
  standalone_value_or_attached_local_name_ = AtomicString(value);
}

Node* Attr::Clone(Document&,
                  NodeCloningData&,
                  ContainerNode*,
                  CustomElementRegistry*,
                  ExceptionState&) const {
  return nullptr;
}

void Attr::setTextContentForBinding(
    const V8UnionStringOrTrustedScript*,
    ExceptionState&) {}

v8::Local<v8::FunctionTemplate>
V8ObservableArrayCSSStyleSheet::GetProxyHandlerFunctionTemplate(
    ScriptState*) {
  return v8::Local<v8::FunctionTemplate>();
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
FragmentParserOptions::FragmentParserOptions(TrustedParserOptions*) {}
#endif

void ElementAnimationTriggerData::SetNamedTriggers(
    NamedAnimationTriggerMap& named_triggers) {
  named_triggers_ = named_triggers;
}

NamedAnimationTriggerMap& ElementAnimationTriggerData::NamedTriggers() {
  return named_triggers_;
}

void ElementAnimationTriggerData::Trace(Visitor* visitor) const {
  visitor->Trace(named_triggers_);
}

PaintLayerScrollableAreaRareData::PaintLayerScrollableAreaRareData() = default;

void PaintLayerScrollableAreaRareData::Trace(Visitor*) const {}

int InstanceCounters::node_counter_ = 0;

unsigned DOMWrapperWorld::number_of_non_main_worlds_in_main_thread_ = 0;

V8ObservableArrayCSSStyleSheet::V8ObservableArrayCSSStyleSheet(
    GarbageCollectedMixin* platform_object,
    SetAlgorithmCallback set_algorithm_callback,
    DeleteAlgorithmCallback delete_algorithm_callback)
    : BaseClass(platform_object),
      set_algorithm_callback_(set_algorithm_callback),
      delete_algorithm_callback_(delete_algorithm_callback) {}

void V8ObservableArrayCSSStyleSheet::Trace(Visitor* visitor) const {
  BaseClass::Trace(visitor);
}

void V8UnionBooleanOrScrollIntoViewOptions::Trace(Visitor*) const {}

void V8UnionKeyframeEffectOptionsOrUnrestrictedDouble::Trace(Visitor*) const {}

void V8ThrowDOMException::Throw(v8::Isolate*,
                                DOMExceptionCode,
                                const String&,
                                const String&) {}

void CustomElement::EnqueueAdoptedCallback(Element&, Document&, Document&) {}
bool CustomElement::ShouldCreateCustomElement(const AtomicString&) {
  return false;
}
bool CustomElement::ShouldCreateCustomElement(const QualifiedName&) {
  return false;
}
HTMLElement* CustomElement::CreateCustomElement(Document&,
                                                const QualifiedName&,
                                                const CreateElementFlags) {
  return nullptr;
}
Element* CustomElement::CreateUncustomizedOrUndefinedElement(
    Document& document,
    const QualifiedName& tag_name,
    const CreateElementFlags flags,
    const AtomicString&,
    CustomElementRegistry*,
    const bool) {
  if (tag_name.NamespaceURI() == html_names::xhtmlNamespaceURI)
    return HTMLElementFactory::Create(tag_name.LocalName(), document, flags);
  return MakeGarbageCollected<HTMLUnknownElement>(tag_name, document);
}
CustomElementDefinition* CustomElementRegistry::DefinitionFor(
    const CustomElementDescriptor&) const {
  return nullptr;
}
HTMLElement* CustomElementDefinition::CreateElement(Document&,
                                                    const QualifiedName&,
                                                    const CreateElementFlags) {
  return nullptr;
}

SVGResource::SVGResource() = default;
SVGResource::~SVGResource() = default;
void SVGResource::Trace(Visitor*) const {}

namespace bindings {
ObservableArrayBase::ObservableArrayBase(
    GarbageCollectedMixin* platform_object,
    ObservableArrayExoticObject* observable_array_exotic_object)
    : platform_object_(platform_object),
      observable_array_exotic_object_(observable_array_exotic_object) {}

void ObservableArrayBase::Trace(Visitor* visitor) const {
  visitor->Trace(platform_object_);
  visitor->Trace(observable_array_exotic_object_);
}

v8::Local<v8::Value> FrozenArrayBase::Wrap(ScriptState*) {
  return v8::Local<v8::Value>();
}

v8::Local<v8::Object> FrozenArrayBase::AssociateWithWrapper(
    v8::Isolate*,
    const WrapperTypeInfo*,
    v8::Local<v8::Object> wrapper) {
  return wrapper;
}
}  // namespace bindings

ObservableArrayExoticObject::ObservableArrayExoticObject(
    bindings::ObservableArrayBase* observable_array_backing_list_object)
    : observable_array_backing_list_object_(
          observable_array_backing_list_object) {}

v8::Local<v8::Value> ObservableArrayExoticObject::Wrap(ScriptState*) {
  return v8::Local<v8::Value>();
}

v8::Local<v8::Object> ObservableArrayExoticObject::AssociateWithWrapper(
    v8::Isolate*,
    const WrapperTypeInfo*,
    v8::Local<v8::Object> wrapper) {
  return wrapper;
}

void ObservableArrayExoticObject::Trace(Visitor* visitor) const {
  visitor->Trace(observable_array_backing_list_object_);
}

LinkCondition* LinkConditionParser::Parse(CSSParserTokenStream&,
                                          const Document&) {
  return nullptr;
}

CSSSyntaxStringParser::CSSSyntaxStringParser(const String& string)
    : input_(StringView(string)) {}

std::optional<CSSSyntaxDefinition> CSSSyntaxStringParser::Parse() {
  return std::nullopt;
}

FontFace* FontFace::Create(Document*,
                           const CascadeLayered<const StyleRuleFontFace>&,
                           bool) {
  return nullptr;
}

void FontFaceCache::Add(const StyleRuleFontFace*, FontFace*) {}

EInsideLink VisitedLinkState::DetermineLinkStateSlowCase(const Element&) {
  return EInsideLink::kNotInsideLink;
}

void DocumentTimeline::InvalidateKeyframeEffects(
    const TreeScope&,
    const StyleChangeReasonForTracing&) {}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
scoped_refptr<QuotesData> LayoutLocale::GetQuotesData() const {
  return nullptr;
}
#endif

CSSValue* AtRuleDescriptorParser::ParseAtCounterStyleDescriptor(
    AtRuleDescriptorID,
    CSSParserTokenStream&,
    const CSSParserContext&) {
  return nullptr;
}

CSSValue* AtRuleDescriptorParser::ParseAtFontPaletteValuesDescriptor(
    AtRuleDescriptorID,
    CSSParserTokenStream&,
    const CSSParserContext&) {
  return nullptr;
}

V8UnionURLPatternInitOrUSVString::V8UnionURLPatternInitOrUSVString(
    const String& value)
    : content_type_(ContentType::kUSVString), member_usv_string_(value) {}

URLPattern* URLPattern::Create(v8::Isolate*,
                               const V8UnionURLPatternInitOrUSVString*,
                               const String&,
                               ExceptionState&) {
  return nullptr;
}

MutableCSSPropertyValueSet* SVGElement::AnimatedSMILStyleProperties() const {
  return nullptr;
}

namespace inspector_style_resolver_resolve_style_event {
void Data(perfetto::TracedValue, Element*, PseudoId) {}
}  // namespace inspector_style_resolver_resolve_style_event

namespace inspector_style_invalidator_invalidate_event {
const char kInvalidationSetInvalidatesSubtree[] = "subtree";
const char kInvalidationSetMatchedTagName[] = "tag";
const char kInvalidationSetMatchedId[] = "id";
const char kInvalidationSetMatchedClass[] = "class";
const char kInvalidationSetMatchedCustomPseudoName[] = "pseudo";
const char kInvalidationSetMatchedAttribute[] = "attr";
const char kInvalidationSetMatchedPart[] = "part";
const char kInvalidationSetInvalidatesTreeCounting[] = "tree-counting";
const char kInvalidationSetInvalidatesSelf[] = "self";
void SelectorPart(perfetto::TracedValue,
                  Element&,
                  const char*,
                  const InvalidationSet&,
                  const AtomicString&) {}
void InvalidationList(perfetto::TracedValue,
                      ContainerNode&,
                      const Vector<scoped_refptr<InvalidationSet>>&) {}
}  // namespace inspector_style_invalidator_invalidate_event

namespace inspector_schedule_style_invalidation_tracking_event {
void ClassChange(perfetto::TracedValue,
                 Element&,
                 const InvalidationSet&,
                 const AtomicString&) {}
void IdChange(perfetto::TracedValue,
              Element&,
              const InvalidationSet&,
              const AtomicString&) {}
void AttributeChange(perfetto::TracedValue,
                     Element&,
                     const InvalidationSet&,
                     const QualifiedName&) {}
void PseudoChange(perfetto::TracedValue,
                  Element&,
                  const InvalidationSet&,
                  CSSSelector::PseudoType) {}
}  // namespace inspector_schedule_style_invalidation_tracking_event

V8UnionCSSNumericValueOrDouble* Animation::currentTime() const {
  return nullptr;
}
Animation* Animation::Create(AnimationEffect*, AnimationTimeline*, ExceptionState&) {
  return nullptr;
}
bool Animation::Update(TimingUpdateReason) {
  return false;
}
void Animation::cancel() {}
std::optional<AnimationTimeDelta> Animation::CurrentTimeInternal() const {
  return std::nullopt;
}
std::optional<AnimationTimeDelta> Animation::UnlimitedCurrentTime() const {
  return std::nullopt;
}
V8AnimationPlayState::Enum Animation::CalculateAnimationPlayState() const {
  return V8AnimationPlayState::Enum::kIdle;
}
void Animation::OnActivePhaseStateChange(bool) {}
double Animation::playbackRate() const {
  return 1.0;
}
std::optional<double> Animation::TimeAsAnimationProgress(
    AnimationTimeDelta) const {
  return std::nullopt;
}
void Animation::UpdateBoundaryAlignment(Timing::NormalizedTiming&) const {}
bool Animation::OnValidateSnapshot(bool) {
  return false;
}
bool Animation::ResolveTimelineOffsets(const TimelineRange&) {
  return false;
}
Document* Animation::GetDocument() const {
  return nullptr;
}
void Animation::Unpause() {}
void Animation::SetCompositorPending(CompositorPendingReason) {}
void Animation::RestartAnimationOnCompositor(CompositorPendingReason) {}
bool Animation::HasActiveAnimationsOnCompositor() const {
  return false;
}
void Animation::InvalidateEffectTargetStyle() {}
bool Animation::IsReplaceable() {
  return false;
}
void Animation::MarkPendingIfCompositorPropertyAnimationChanges(
    const PaintArtifactCompositor*) {}
Animation::NativePaintWorkletReasons Animation::GetNativePaintWorkletReasons()
    const {
  return kNoPaintWorklet;
}
bool Animation::Limited(std::optional<AnimationTimeDelta>) const {
  return false;
}
bool Animation::HasLowerCompositeOrdering(
    const Animation*,
    const Animation*,
    CompareAnimationsOrdering) {
  return false;
}

CSSAnimations::CSSAnimations() = default;
void CSSAnimations::Trace(Visitor* visitor) const {
  visitor->Trace(running_animations_);
  visitor->Trace(transitions_);
  visitor->Trace(previous_active_interpolations_for_animations_);
  visitor->Trace(timeline_data_);
}
bool CSSAnimations::IsAnimationAffectingProperty(const CSSProperty&) {
  return false;
}
bool CSSAnimations::IsAffectedByKeyframesFromScope(const Element&,
                                                   const TreeScope&) {
  return false;
}
bool CSSAnimations::IsAnimatingCustomProperties(const ElementAnimations*) {
  return false;
}
bool CSSAnimations::IsAnimatingStandardProperties(const ElementAnimations*,
                                                 const CSSBitset*,
                                                 KeyframeEffect::Priority) {
  return false;
}
bool CSSAnimations::IsAnimatingFontAffectingProperties(const ElementAnimations*) {
  return false;
}
bool CSSAnimations::IsAnimatingLineHeightProperty(const ElementAnimations*) {
  return false;
}
bool CSSAnimations::IsAnimatingRevert(const ElementAnimations*) {
  return false;
}
bool CSSAnimations::IsAnimatingDisplayProperty(const ElementAnimations*) {
  return false;
}
void CSSAnimations::CalculateTimelineUpdate(CSSAnimationUpdate&,
                                            Element&,
                                            const ComputedStyleBuilder&) {}
void CSSAnimations::CalculateAnimationUpdate(CSSAnimationUpdate&,
                                             Element&,
                                             Element&,
                                             const ComputedStyleBuilder&,
                                             const ComputedStyle*,
                                             StyleResolver*,
                                             bool) {}
void CSSAnimations::CalculateCompositorAnimationUpdate(CSSAnimationUpdate&,
                                                       Element&,
                                                       Element&,
                                                       const ComputedStyle&,
                                                       const ComputedStyle*,
                                                       bool,
                                                       bool) {}
void CSSAnimations::CalculateTransitionUpdate(CSSAnimationUpdate&,
                                              Element&,
                                              const ComputedStyleBuilder&,
                                              const ComputedStyle*,
                                              const StyleRecalcContext&,
                                              bool) {}
void CSSAnimations::SnapshotCompositorKeyframes(Element&,
                                                CSSAnimationUpdate&,
                                                const ComputedStyle&,
                                                const ComputedStyle*) {}
void CSSAnimations::UpdateAnimationFlags(Element&,
                                         CSSAnimationUpdate&,
                                         ComputedStyleBuilder&) {}
void CSSAnimations::TimelineData::Trace(Visitor* visitor) const {
  visitor->Trace(scroll_timelines_);
  visitor->Trace(view_timelines_);
  visitor->Trace(deferred_timeline_map_);
  visitor->Trace(timeline_attachments_);
}
void CSSAnimations::RunningAnimation::Trace(Visitor* visitor) const {
  visitor->Trace(animation);
  visitor->Trace(style_rule);
}

void CSSAnimation::SetNamedTriggerAttachment(
    Member<const TriggerScopedName>,
    AnimationTrigger*) {}
void StyleTriggerAttachment::Attach(AnimationTrigger&,
                                    const NamingScope&,
                                    CSSAnimation&) const {}
void DocumentAnimations::AddTimeline(AnimationTimeline&) {}
DocumentTimeline::DocumentTimeline(Document* document,
                                   base::TimeDelta origin_time,
                                   PlatformTiming* timing)
    : AnimationTimeline(document),
      origin_time_(origin_time),
      playback_rate_(1),
      timing_(timing),
      zero_time_initialized_(false) {}
base::TimeTicks DocumentTimeline::CalculateZeroTime() {
  return base::TimeTicks();
}
void DocumentTimeline::Trace(Visitor* visitor) const {
  AnimationTimeline::Trace(visitor);
  visitor->Trace(timing_);
}
bool DocumentTimeline::IsActive() const {
  return false;
}
std::optional<base::TimeDelta>
DocumentTimeline::InitialStartTimeForAnimations() {
  return std::nullopt;
}
void DocumentTimeline::ScheduleNextService() {}
cc::AnimationTimeline* DocumentTimeline::EnsureCompositorTimeline() {
  return nullptr;
}
AnimationTimeline::PhaseAndTime DocumentTimeline::CurrentPhaseAndTime() {
  return {TimelinePhase::kInactive, std::nullopt};
}
bool TimelineTrigger::Update() {
  return false;
}
namespace scroll_timeline_util {
scoped_refptr<CompositorScrollTimeline> ToCompositorScrollTimeline(
    AnimationTimeline*) {
  return nullptr;
}
std::optional<CompositorElementId> GetCompositorScrollElementId(const Node*) {
  return std::nullopt;
}
CompositorScrollTimeline::ScrollDirection ConvertOrientation(
    ScrollAxis,
    const ComputedStyle*) {
  return CompositorScrollTimeline::ScrollDown;
}
}  // namespace scroll_timeline_util
CSSUnitValue* CSSUnitValue::Create(double,
                                   CSSPrimitiveValue::UnitType) {
  return nullptr;
}

const WrapperTypeInfo& ToggleEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ToggleEvent");
const WrapperTypeInfo& CommandEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CommandEvent");
ToggleEvent::~ToggleEvent() = default;
const AtomicString& ToggleEvent::InterfaceName() const {
  static const AtomicString name("ToggleEvent");
  return name;
}

void URLPatternInit::Trace(Visitor*) const {}
const void* URLPatternInit::TemplateKey() const {
  return nullptr;
}
void URLPatternInit::FillTemplateProperties(
    Vector<std::string_view>&) const {}
v8::Local<v8::Object> URLPatternInit::FillValues(
    ScriptState*,
    v8::Local<v8::DictionaryTemplate>) const {
  return v8::Local<v8::Object>();
}

V8ObjectBuilder& V8ObjectBuilder::AddString(const StringView&,
                                            const StringView&) {
  return *this;
}
V8ObjectBuilder::V8ObjectBuilder(ScriptState*) : script_state_(nullptr) {}
V8ObjectBuilder& V8ObjectBuilder::AddNull(const StringView&) {
  return *this;
}
V8ObjectBuilder& V8ObjectBuilder::AddNumber(const StringView&, double) {
  return *this;
}
void V8ObjectBuilder::AddInternal(const StringView&, v8::Local<v8::Value>) {}
ScriptObject V8ObjectBuilder::ToScriptObject() const {
  return ScriptObject();
}

unsigned PropertyHandle::GetHash() const {
  return static_cast<unsigned>(handle_type_) ^
         static_cast<unsigned>(css_property_->PropertyID()) ^
         property_name_.Hash();
}

bool PropertyHandle::operator==(const PropertyHandle& other) const {
  return handle_type_ == other.handle_type_ &&
         css_property_ == other.css_property_ &&
         property_name_ == other.property_name_;
}

EffectTiming* Timing::ConvertToEffectTiming() const {
  return nullptr;
}

Timing::CalculatedTiming Timing::CalculateTimings(
    std::optional<AnimationTimeDelta>,
    bool,
    const NormalizedTiming&,
    AnimationDirection,
    bool,
    std::optional<double>,
    bool,
    bool) const {
  return CalculatedTiming();
}

ComputedEffectTiming* Timing::getComputedTiming(const CalculatedTiming&,
                                                const NormalizedTiming&,
                                                bool) const {
  return nullptr;
}

template <>
bool TimingInput::Update<OptionalEffectTiming>(Timing&,
                                               const OptionalEffectTiming*,
                                               Document*,
                                               ExceptionState&) {
  return false;
}

const CSSValue* AnimationUtils::KeyframeValueFromComputedStyle(
    const PropertyHandle&,
    const ComputedStyle&,
    const Document&,
    const LayoutObject*) {
  return nullptr;
}

void AnimationUtils::ForEachInterpolatedPropertyValue(
    Element*,
    const PropertyHandleSet&,
    ActiveInterpolationsMap&,
    base::FunctionRef<void(PropertyHandle, const CSSValue*)>) {}

void ExceptionState::ThrowTypeError(const String&) {
  had_exception_ = true;
}
void ExceptionState::ThrowDOMException(DOMExceptionCode, const String&) {
  had_exception_ = true;
}
void ExceptionState::ThrowDOMException(DOMExceptionCode, const char*) {
  had_exception_ = true;
}

bool LengthPropertyFunctions::CanAnimateKeyword(const CSSProperty&,
                                                CSSValueID) {
  return false;
}

bool CompositorAnimations::CompositedPropertyRequiresSnapshot(
    const PropertyHandle&) {
  return false;
}

TimelineRangeOffset::TimelineRangeOffset() = default;
TimelineRangeOffset::TimelineRangeOffset(v8::Isolate*) {}

void TimelineRangeOffset::Trace(Visitor* visitor) const {
  visitor->Trace(member_offset_);
}

const void* TimelineRangeOffset::TemplateKey() const {
  return nullptr;
}

void TimelineRangeOffset::FillTemplateProperties(
    Vector<std::string_view>&) const {}

v8::Local<v8::Object> TimelineRangeOffset::FillValues(
    ScriptState*,
    v8::Local<v8::DictionaryTemplate>) const {
  return v8::Local<v8::Object>();
}

const char* const V8TimelineRange::string_table_[] = {
    "normal", "cover", "contain", "entry",
    "entry-crossing", "exit", "exit-crossing", "scroll"};

const char* const V8CompositeOperation::string_table_[] = {
    "replace", "add", "accumulate"};

void V8UnionCSSNumericValueOrDouble::Trace(Visitor* visitor) const {
  visitor->Trace(member_css_numeric_value_);
}

void V8UnionCSSNumericValueOrString::Trace(Visitor* visitor) const {
  visitor->Trace(member_css_numeric_value_);
}

Animation* Animation::Create(ExecutionContext*,
                             AnimationEffect*,
                             AnimationTimeline*,
                             ExceptionState&) {
  return nullptr;
}
void Animation::SetRangeStartInternal(std::optional<TimelineOffset>) {}
void Animation::SetRangeEndInternal(std::optional<TimelineOffset>) {}
KeyframeEffect* KeyframeEffect::Create(ScriptState*,
                                       Element*,
                                       const ScriptValue&,
                                       ExceptionState&) {
  return nullptr;
}
KeyframeEffect* KeyframeEffect::Create(
    ScriptState*,
    Element*,
    const ScriptValue&,
    const V8UnionKeyframeEffectOptionsOrUnrestrictedDouble*,
    ExceptionState&) {
  return nullptr;
}
HeapVector<Member<Animation>> DocumentAnimations::getAnimations(
    const TreeScope&) {
  return {};
}
void DocumentAnimations::UpdateAnimationTriggerAttachments() {}
void DocumentAnimations::UpdateAnimations(DocumentLifecycle::LifecycleState,
                                          const PaintArtifactCompositor*,
                                          bool) {}
void DocumentAnimations::UpdateAnimationTimingForAnimationFrame() {}
size_t DocumentAnimations::GetAnimationsCount() {
  return 0;
}
void DocumentAnimations::Trace(Visitor*) const {}
void PendingAnimations::TimerFired(TimerBase*) {}
void PendingAnimations::Trace(Visitor*) const {}
void WorkletAnimationController::Trace(Visitor*) const {}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
QualifiedName::QualifiedName(const AtomicString& prefix,
                             const AtomicString& local_name,
                             const AtomicString& namespace_uri) {
  impl_ = QualifiedNameImpl::Create(prefix.Impl(), local_name.Impl(),
                                    namespace_uri.Impl(), false);
}
QualifiedName::QualifiedName(const AtomicString& local_name)
    : QualifiedName(g_null_atom, local_name, g_null_atom) {}
QualifiedName::QualifiedName(const AtomicString& prefix,
                             const AtomicString& local_name,
                             const AtomicString& namespace_uri,
                             bool is_static) {
  impl_ = QualifiedNameImpl::Create(prefix.Impl(), local_name.Impl(),
                                    namespace_uri.Impl(), is_static);
}
QualifiedName::~QualifiedName() = default;
QualifiedName::QualifiedNameImpl::~QualifiedNameImpl() = default;
unsigned QualifiedName::QualifiedNameImpl::ComputeHash() const {
  QualifiedNameComponents components = {prefix_.Impl(), local_name_.Impl(),
                                        namespace_.Impl()};
  return HashComponents(components);
}
#endif

int HTMLFrameOwnerElement::PluginDisposeSuspendScope::suspend_count_ = 0;
void HTMLFrameOwnerElement::PluginDisposeSuspendScope::
    PerformDeferredPluginDispose() {
  suspend_count_ = 0;
}
bool RuntimeCallStats::IsEnabled() {
  return false;
}
RuntimeCallStats* RuntimeCallStats::From(v8::Isolate*) {
  return nullptr;
}
void RuntimeCallTimer::Start(RuntimeCallCounter*, RuntimeCallTimer*) {}
RuntimeCallTimer* RuntimeCallTimer::Stop() {
  return nullptr;
}
const unsigned char* InvalidationTracingFlag::GetCategoryGroupEnabled() {
  static const unsigned char disabled = 0;
  return &disabled;
}

bool RuntimeEnabledFeaturesBase::is_reading_flow_with_slots_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_blink_runtime_call_stats_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_heading_offset_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_shadow_root_reference_target_aria_owns_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_html_command_for_scroll_commands_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_clip_element_visible_bounds_in_local_root_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_trusted_types_html_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_inner_html_parser_fastpath_log_failure_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_page_reveal_event_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_page_popup_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_page_popup_copy_paste_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_ad_tagging_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_programmatic_scroll_promise_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_coalesce_selectionchange_event_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_aria_notify_v_2_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_aria_notify_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_back_forward_cache_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_viewport_segments_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_text_scale_meta_tag_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_force_reduce_motion_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_light_dismiss_from_click_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_lang_attribute_aware_form_control_ui_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_clear_focus_within_on_subtree_removal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_omit_blur_event_on_element_removal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_user_action_pseudos_stop_at_top_layer_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_marker_group_modes_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_desktop_pw_as_additional_windowing_controls_on_move_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_origin_isolation_header_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_recheck_parent_during_node_vector_insertion_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_send_slot_change_signal_after_node_inserted_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_remove_children_in_replace_children_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_snapshot_scroll_timelines_post_layout_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_record_same_document_presentation_time_once_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_run_snapshot_post_layout_state_steps_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_implicit_root_scroller_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_quote_first_line_style_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_display_contents_focusable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_correct_template_form_parsing_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_streaming_sanitizer_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_set_html_can_run_scripts_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_sanitizer_api_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_trusted_types_create_parser_options_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_new_html_setting_methods_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_document_patching_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scoped_custom_element_registry_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_custom_elements_disable_formatting_fixups_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_html_command_element_removal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_position_sticky_static_scroll_position_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_html_printing_artifact_annotations_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_blink_geometry_mapper_viewport_fast_path_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_fix_visual_rect_remote_viewport_transform_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_line_clamp_line_breaking_ellipsis_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_search_text_highlight_pseudo_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_corners_shorthand_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_spacing_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_ruby_overhang_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_initial_target_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_scroll_target_group_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scrollbar_width_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_decoration_skip_spaces_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_fit_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scoped_view_transitions_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_letter_and_word_spacing_percentage_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_decouple_resolved_column_rule_width_from_style_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_outline_draw_auto_style_zero_width_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_disable_anchor_center_on_align_justify_items_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_side_relative_background_position_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_decouple_computed_border_width_from_style_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_alt_counter_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_counter_reset_reversed_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_layout_api_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_view_transition_auto_name_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::
    is_css_shape_outside_path_and_shape_support_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_shape_outside_rect_and_xywh_support_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_indent_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_indent_as_primitive_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_font_style_oblique_zero_degree_as_normal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_ident_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_revert_rule_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_url_request_modifiers_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_alpha_color_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_contrast_color_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_accent_color_keyword_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_light_dark_image_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_cross_fade_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_non_standard_appearance_value_slider_vertical_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_font_family_serialization_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_background_clip_border_area_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_font_format_avar_2_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_polygon_rounding_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_text_transform_full_size_kana_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_transform_full_width_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_transform_multi_keyword_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_overflow_string_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_paint_api_arguments_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_overscroll_behavior_chain_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_align_match_parent_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_appearance_base_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_user_select_contain_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_resize_auto_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_typed_arithmetic_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_progress_notation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_random_function_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_media_progress_notation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_container_progress_notation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::WebMCPEnabled(const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::BlockingFocusWithoutUserActivationEnabled(
    const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::FocusgroupEnabled(const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::ShadowRootReferenceTargetEnabled(
    const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::CanvasDrawElementEnabled(
    const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::TouchEventFeatureDetectionEnabled(
    const FeatureContext*) {
  return false;
}

bool DisplayLockUtilities::IsInUnlockedOrActivatableSubtree(
    const Node&,
    DisplayLockActivationReason) {
  return true;
}
Element* DisplayLockUtilities::LockedAncestorPreventingPrePaint(
    const LayoutObject&) {
  return nullptr;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
ViewTransition* ViewTransitionUtils::GetTransition(const Document&) {
  return nullptr;
}
ViewTransition* ViewTransitionUtils::GetTransition(const Node&) {
  return nullptr;
}
VectorOf<std::unique_ptr<cc::ViewTransitionRequest>>
ViewTransitionUtils::GetPendingRequests(const Document&) {
  return {};
}
#endif
PageRevealEvent::PageRevealEvent()
    : Event(event_type_names::kPagereveal, Bubbles::kNo, Cancelable::kNo) {}
PageRevealEvent::PageRevealEvent(const AtomicString& type,
                                 const PageRevealEventInit*)
    : Event(type, Bubbles::kNo, Cancelable::kNo) {}
PageRevealEvent::~PageRevealEvent() = default;
const AtomicString& PageRevealEvent::InterfaceName() const {
  return event_interface_names::kPageRevealEvent;
}
void PageRevealEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
}
DOMViewTransition* PageRevealEvent::viewTransition() const {
  return dom_view_transition_.Get();
}
void PageRevealEvent::SetViewTransition(DOMViewTransition* transition) {
  dom_view_transition_ = transition;
}
Resource* PendingLinkPreload::GetResourceForTesting() const {
  return nullptr;
}
void PendingLinkPreload::Trace(Visitor*) const {}
void StreamingSanitizer::DidParseDocument(Document*) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
FragmentParserOptions::FragmentParserOptions(SetHTMLUnsafeOptions*) {}
#endif
std::optional<FragmentParserOptions> TrustedTypesCheckForParserOptions(
    FragmentParserOptions options,
    MarkupInsertionMode,
    const ExecutionContext*,
    const AtomicString&,
    const AtomicString&,
    ExceptionState&) {
  return options;
}
StreamingSanitizer* SanitizerAPI::CreateStreamingSanitizer(
    Sanitizer::Mode,
    FragmentParserOptions,
    ExceptionState&) {
  return nullptr;
}
bool SanitizerAPI::AllowMutatingRootElement(Sanitizer::Mode,
                                            const ContainerNode*) {
  return true;
}
void SanitizerAPI::SanitizeInternal(Sanitizer::Mode,
                                    const ContainerNode*,
                                    ContainerNode*,
                                    FragmentParserOptions,
                                    ExceptionState&) {}
bool XMLDocumentParser::ParseDocumentFragment(const String&,
                                              DocumentFragment*,
                                              Element*,
                                              ParserContentPolicy,
                                              ExceptionState&) {
  return false;
}

InvalidateNodeListCachesScope::InvalidateNodeListCachesScope(Document& document)
    : document_(document), invalidate_for_null_attr_name_(false) {}
InvalidateNodeListCachesScope::~InvalidateNodeListCachesScope() = default;
void InvalidateNodeListCachesScope::Invalidate(Document&,
                                               const QualifiedName*) {}
void ChildListMutationAccumulator::ChildAdded(Node&) {}
ChildListMutationAccumulator* ChildListMutationAccumulator::GetOrCreate(
    Node&) {
  return nullptr;
}
void ChildListMutationAccumulator::WillRemoveChild(Node&) {}
void ChildListMutationAccumulator::LeaveMutationScope() {}
void ScopedEventQueue::IncrementScopingLevel() {}
void ScopedEventQueue::DecrementScopingLevel() {}
MutationRecord* MutationRecord::CreateCharacterData(Node*, const String&) {
  return nullptr;
}

SelectorQuery* SelectorQueryCache::Add(const AtomicString&,
                                       const Document&,
                                       ExceptionState&) {
  return nullptr;
}
Element* SelectorQuery::QueryFirst(ContainerNode&) const {
  return nullptr;
}
StaticElementList* SelectorQuery::QueryAll(ContainerNode&) const {
  return nullptr;
}
ScriptRegexp::ScriptRegexp(v8::Isolate*,
                           const String&,
                           TextCaseSensitivity,
                           MultilineMode,
                           UnicodeMode) {}
int ScriptRegexp::Match(StringView,
                        int,
                        int* match_length,
                        Vector<String>* group_list) const {
  if (match_length) {
    *match_length = 0;
  }
  if (group_list) {
    group_list->clear();
  }
  return -1;
}

NameNodeList::~NameNodeList() = default;
bool NameNodeList::ElementMatches(const Element&) const {
  return false;
}
ClassCollection::~ClassCollection() = default;
RadioNodeList::~RadioNodeList() = default;
bool RadioNodeList::ElementMatches(const Element&) const {
  return false;
}
String CreateMarkup(const Node*,
                    ChildrenOnly,
                    AbsoluteURLs,
                    const ShadowRootInclusion&) {
  return String();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
FragmentParserOptions FragmentParserOptions::From(
    const V8UnionSetHTMLUnsafeOptionsOrTrustedParserOptions*) {
  return FragmentParserOptions();
}
FragmentParserOptions::FragmentParserOptions(SetHTMLOptions*) {}
FragmentParserConfig FragmentParserConfig::ForContainer(
    ContainerNode* context,
    Sanitizer::Mode mode,
    const AtomicString& interface_name,
    const AtomicString& property_name) {
  FragmentParserConfig config;
  config.context_element = DynamicTo<Element>(context);
  config.sanitizer_mode = mode;
  config.interface_name = interface_name;
  config.property_name = property_name;
  return config;
}
DocumentFragment* ParseHTMLFragment(const String&,
                                    const FragmentParserConfig&,
                                    FragmentParserOptions,
                                    ExceptionState&) {
  return nullptr;
}
#endif
bool TryParsingHTMLFragment(const String&,
                            Document&,
                            ContainerNode&,
                            Element&,
                            ParserContentPolicy,
                            HTMLFragmentParsingBehaviorSet,
                            bool*) {
  return false;
}
void LogTagsForUnsupportedTagTypeFailure(DocumentFragment&) {}
WritableStream* HTMLStream::Create(ScriptState*,
                                   ContainerNode*,
                                   Node*,
                                   Sanitizer::Mode,
                                   const FragmentParserOptions&,
                                   const AtomicString&,
                                   const AtomicString&,
                                   ExceptionState&) {
  return nullptr;
}
String TrustedTypesCheckForHTML(const V8UnionStringOrTrustedHTML*,
                                const ExecutionContext*,
                                const AtomicString&,
                                const AtomicString&,
                                ExceptionState&) {
  return String();
}
void TextDiffRange::CheckValid(const String&, const String&) const {}
void ProcessingInstruction::DidChangeData() {}

const QualifiedName Attr::GetQualifiedName() const { return name_; }
void CustomElement::EnqueueAttributeChangedCallback(
    Element&,
    const QualifiedName&,
    const AtomicString&,
    const AtomicString&) {}
void Attr::DetachFromElementWithValue(const AtomicString& value) {
  element_ = nullptr;
  standalone_value_or_attached_local_name_ = value;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
std::ostream& operator<<(std::ostream& stream, const QualifiedName& name) {
  return stream << name.ToString().Utf8();
}
#endif
void SVGElement::SynchronizeSVGAttribute(const QualifiedName&) const {}

bool MenuSafeTriangle::ShouldDeferInterestGained(Element*,
                                                 Element*,
                                                 Element::InterestState) {
  return false;
}
bool MenuSafeTriangle::ShouldDeferInterestLost(
    Element*,
    Element*,
    Element::InterestLostCancelable,
    Element::InterestLostPopoverBehavior) {
  return false;
}
InterestEvent::InterestEvent(const AtomicString& type,
                             Element*,
                             Cancelable cancelable)
    : Event(type, Bubbles::kNo, cancelable) {}
HTMLMenuListElement* HTMLMenuItemElement::GetInvokedSubmenu() const {
  return nullptr;
}

bool DisplayLockDocumentState::HasActivatableLocks() const { return false; }
bool DisplayLockContext::ShouldCommitForActivation(
    DisplayLockActivationReason) const {
  return false;
}
void DisplayLockContext::CommitForActivation(DisplayLockActivationReason) {}

gfx::Size PaintLayerScrollableArea::ContentsSize() const {
  return gfx::Size();
}
void PaintLayerScrollableArea::EnqueueScrollEventIfNeeded() {}
PaintLayer* PaintLayerScrollableArea::Layer() const {
  return nullptr;
}
bool PaintLayerScrollableArea::ScrollByPageWithSnap(
    ScrollDirectionPhysical,
    mojom::blink::ScrollBehavior) {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PaintLayer::SetDescendantNeedsRepaint() {}
void PaintLayer::ClearNeedsRepaintRecursively() {}
void PaintLayer::SetDescendantNeedsCullRectUpdate() {}
void PaintLayer::SetNeedsCullRectUpdate() {}
void PaintLayer::UpdateDescendantDependentFlags() {}
void PaintLayer::DirtyVisibleContentStatus() {}
#endif
void PaintLayerScrollableArea::Trace(Visitor*) const {}
CompositorElementId PaintLayerScrollableArea::GetScrollElementId() const {
  return CompositorElementId();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PaintPropertyTreeBuilder::DirectlyUpdateOpacityValue(
    const LayoutObject&) {}
void PaintPropertyTreeBuilder::DirectlyUpdateTransformMatrix(
    const LayoutObject&) {}
#endif
void PaintTimingDetector::NotifyPaintFinished() {}
void PaintTiming::MarkPaintTiming() {}
PaintArtifactCompositor::~PaintArtifactCompositor() = default;
void PaintArtifactCompositor::SetLayerDebugInfoEnabled(bool) {}
void PaintArtifactCompositor::SetTracksRasterInvalidations(bool) {}
void PaintArtifactCompositor::WillBeRemovedFromFrame() {}
void PaintArtifactCompositor::SetNeedsUpdateAfterRepaint(
    const PaintArtifact&,
    const PaintArtifact&) {}
void PaintArtifactCompositor::SetNeedsUpdateInternal(UpdateType) {}
PaintArtifactCompositor::PaintArtifactCompositor(
    base::WeakPtr<cc::ScrollCallbacks>) {}
void PaintArtifactCompositor::SetLCDTextPreference(LCDTextPreference) {}
bool PaintArtifactCompositor::SetScrollbarSolidColor(cc::ElementId, SkColor4f) {
  return false;
}
bool PaintArtifactCompositor::SetScrollbarNeedsDisplay(cc::ElementId) {
  return false;
}
void PaintArtifactCompositor::SetDevicePixelRatio(float) {}
bool PaintArtifactCompositor::TryFastPathUpdate(const PaintArtifact&) {
  return false;
}
void PaintArtifactCompositor::Update(
    const PaintArtifact&,
    const PaintArtifactCompositor::ViewportProperties&,
    const HeapVector<Member<const TransformPaintPropertyNode>, 32>&,
    VectorOf<std::unique_ptr<cc::ViewTransitionRequest>>) {}
std::unique_ptr<JSONObject> PaintArtifactCompositor::GetLayersAsJSON(
    LayerTreeFlags) const {
  return nullptr;
}
size_t PaintArtifactCompositor::ApproximateUnsharedMemoryUsage() const {
  return 0;
}
MainThreadScrollingReasons
PaintArtifactCompositor::GetMainThreadRepaintReasons(
    const ScrollPaintPropertyNode&) const {
  return 0;
}
void LinkHighlight::UpdateAfterPaint(const PaintArtifactCompositor*) {}
ViewTransition* ViewTransitionSupplement::GetTransition() {
  return nullptr;
}
ViewTransition* ViewTransitionSupplement::GetTransition(const Element&) {
  return nullptr;
}
void ViewTransitionSupplement::ForEachTransition(
    base::FunctionRef<void(ViewTransition&)>) {}
VectorOf<std::unique_ptr<cc::ViewTransitionRequest>>
ViewTransitionSupplement::TakePendingRequests() {
  return {};
}
void ViewTransitionSupplement::WillEnterGetComputedStyleScope() {}
void ViewTransitionSupplement::WillExitGetComputedStyleScope() {}
void ViewTransitionSupplement::WillUpdateStyleAndLayoutTree() {}
bool ViewTransition::NeedsViewTransitionEffectNode(const LayoutObject&) const {
  return false;
}
bool ViewTransition::IsTransitionElementExcludingRoot(const Element&) const {
  return false;
}
bool PaintLayerScrollableArea::CanPropagateScroll() const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void DisplayItemList::clear() {
  items_.clear();
}
#endif
void EmbeddedContentView::SetFrameRect(const gfx::Rect& frame_rect) {
  frame_rect_ = frame_rect;
  FrameRectsChanged(frame_rect_);
}
void EmbeddedContentView::SetSelfVisible(bool visible) {
  self_visible_ = visible;
  SelfVisibleChanged();
}
void EmbeddedContentView::SetParentVisible(bool visible) {
  parent_visible_ = visible;
  ParentVisibleChanged();
}
FrameView::FrameView(const gfx::Rect& frame_rect)
    : EmbeddedContentView(frame_rect) {}
void RemoteFrameView::UpdateCompositingScaleFactor() {}
void RemoteFrameView::UpdateCompositingRect() {}
VisualViewport::VisualViewport(Page& page)
    : ScrollableArea(nullptr),
      page_(&page),
      scale_(1),
      is_pinch_gesture_active_(false),
      browser_controls_adjustment_(0),
      needs_paint_property_update_(false),
      overscroll_type_(OverscrollType::kNone) {}
const TransformPaintPropertyNode*
VisualViewport::GetOverscrollElasticityTransformNode() const {
  return nullptr;
}
const TransformPaintPropertyNode* VisualViewport::GetPageScaleNode() const {
  return nullptr;
}
const TransformPaintPropertyNode* VisualViewport::GetScrollTranslationNode()
    const {
  return nullptr;
}
VisualViewport::~VisualViewport() = default;
void VisualViewport::Trace(Visitor* visitor) const {
  visitor->Trace(page_);
  ScrollableArea::Trace(visitor);
}
ChromeClient* VisualViewport::GetChromeClient() const {
  return nullptr;
}
PhysicalRect VisualViewport::ScrollIntoView(
    const PhysicalRect& rect,
    const PhysicalBoxStrut&,
    const mojom::blink::ScrollIntoViewParamsPtr&,
    std::unique_ptr<ScrollPromiseResolver::ActiveScrollTracker>) {
  return rect;
}
PhysicalOffset VisualViewport::LocalToScrollOriginOffset() const {
  return PhysicalOffset();
}
cc::AnimationHost* VisualViewport::GetCompositorAnimationHost() const {
  return nullptr;
}
cc::AnimationTimeline* VisualViewport::GetCompositorAnimationTimeline() const {
  return nullptr;
}
int VisualViewport::ScrollSize(ScrollbarOrientation) const {
  return 0;
}
gfx::Vector2d VisualViewport::MinimumScrollOffsetInt() const {
  return gfx::Vector2d();
}
gfx::Vector2d VisualViewport::MaximumScrollOffsetInt() const {
  return gfx::Vector2d();
}
ScrollOffset VisualViewport::MaximumScrollOffset() const {
  return ScrollOffset();
}
gfx::Rect VisualViewport::VisibleContentRect(IncludeScrollbarsInRect) const {
  return gfx::Rect(size_);
}
gfx::Size VisualViewport::ContentsSize() const {
  return size_;
}
CompositorElementId VisualViewport::GetScrollElementId() const {
  return scroll_element_id_;
}
bool VisualViewport::ScrollAnimatorEnabled() const {
  return false;
}
bool VisualViewport::ScheduleAnimation() {
  return false;
}
bool VisualViewport::UserInputScrollable(ScrollbarOrientation) const {
  return false;
}
cc::Layer* VisualViewport::LayerForHorizontalScrollbar() const {
  return nullptr;
}
cc::Layer* VisualViewport::LayerForVerticalScrollbar() const {
  return nullptr;
}
void VisualViewport::DisposeImpl() {}
mojom::blink::ColorScheme VisualViewport::UsedColorSchemeScrollbars() const {
  return mojom::blink::ColorScheme::kLight;
}
bool VisualViewport::VisualViewportSuppliesScrollbars() const {
  return false;
}
scoped_refptr<base::SingleThreadTaskRunner> VisualViewport::GetTimerTaskRunner()
    const {
  return nullptr;
}
ScrollbarTheme& VisualViewport::GetPageScrollbarTheme() const {
  class StandaloneScrollbarTheme final : public ScrollbarTheme {
   public:
    bool NativeThemeHasButtons() const override { return false; }
    bool HasThumb(const Scrollbar&) const override { return false; }
    gfx::Rect BackButtonRect(const Scrollbar&) const override { return gfx::Rect(); }
    gfx::Rect ForwardButtonRect(const Scrollbar&) const override { return gfx::Rect(); }
    gfx::Rect TrackRect(const Scrollbar&) const override { return gfx::Rect(); }
    int MinimumThumbLength(const Scrollbar&) const override { return 0; }
  };
  static StandaloneScrollbarTheme theme;
  return theme;
}
void VisualViewport::DropCompositorScrollDeltaNextCommit() {}
bool VisualViewport::SetScrollOffsetInternal(
    const ScrollOffset& offset,
    mojom::blink::ScrollType,
    cc::ScrollSourceType,
    mojom::blink::ScrollBehavior,
    bool,
    std::unique_ptr<ScrollPromiseResolver::ActiveScrollTracker>) {
  offset_ = offset;
  return true;
}
const Document* VisualViewport::GetDocument() const {
  return nullptr;
}
void VisualViewport::UpdateScrollOffset(const ScrollOffset& offset,
                                        mojom::blink::ScrollType,
                                        cc::ScrollSourceType) {
  offset_ = offset;
}
gfx::PointF VisualViewport::ViewportCSSPixelsToRootFrame(
    const gfx::PointF& point) const {
  return point;
}
gfx::PointF VisualViewport::ViewportToRootFrame(const gfx::PointF& point) const {
  return point;
}
void VisualViewport::SetLocation(const gfx::PointF&) {}
void VisualViewport::SetScale(float) {}
void VisualViewport::SetScaleAndLocation(float, bool, const gfx::PointF&) {}
gfx::RectF VisualViewport::RootFrameToViewport(const gfx::RectF& rect) const {
  return rect;
}
gfx::Rect VisualViewport::ViewportToRootFrame(const gfx::Rect& rect) const {
  return rect;
}
gfx::Rect VisualViewport::RootFrameToViewport(const gfx::Rect& rect) const {
  return rect;
}
gfx::Point VisualViewport::RootFrameToViewport(const gfx::Point& point) const {
  return point;
}
gfx::Point VisualViewport::ViewportToRootFrame(const gfx::Point& point) const {
  return point;
}
gfx::PointF VisualViewport::RootFrameToViewport(const gfx::PointF& point) const {
  return point;
}
void VisualViewport::UsedColorSchemeChanged() {}
void VisualViewport::ScrollbarColorChanged() {}
std::optional<blink::Color> VisualViewport::CSSScrollbarThumbColor() const {
  return std::nullopt;
}
bool VisualViewport::IsActiveViewport() const {
  return false;
}
void VisualViewport::InitializeScrollbars() {}
PhysicalSize CalculateInitialContainingBlockSizeForPagination(Document&) {
  return PhysicalSize();
}
float CalculateOverflowShrinkForPrinting(const LayoutView&, float shrink) {
  return shrink;
}
float PageScaleConstraints::ClampToConstraints(float page_scale_factor) const {
  return page_scale_factor;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
OverriddenCullRectScope::OverriddenCullRectScope(PaintLayer&,
                                                 const CullRect&,
                                                 bool) {}
OverriddenCullRectScope::~OverriddenCullRectScope() = default;
void CullRectUpdater::UpdateForTesting(const CullRect&) {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const EffectPaintPropertyNode& EffectPaintPropertyNode::Root() {
  return *static_cast<const EffectPaintPropertyNode*>(nullptr);
}
const ClipPaintPropertyNode& ClipPaintPropertyNode::Root() {
  return *static_cast<const ClipPaintPropertyNode*>(nullptr);
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const TransformPaintPropertyNode& TransformPaintPropertyNode::Root() {
  return *static_cast<const TransformPaintPropertyNode*>(nullptr);
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
cc::PaintRecord PaintArtifact::GetPaintRecord(const PropertyTreeState&,
                                              const gfx::Rect*) const {
  return cc::PaintRecord();
}
#endif
base::TimeDelta TimerBase::NextFireInterval() const {
  return base::TimeDelta();
}
void TapFriendlinessChecker::RegisterTapEvent(Element*) {}
void FontPerformance::MarkFirstContentfulPaint() {}
void LocalFrameUkmAggregator::DidReachFirstContentfulPaint() {}
void LocalFrameUkmAggregator::OnCommitRequested() {}
AnchorElementViewportPositionTracker*
AnchorElementViewportPositionTracker::MaybeGetOrCreateFor(Document&) {
  return nullptr;
}
void AnchorElementViewportPositionTracker::OnFirstContentfulPaint() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
size_t PaintControllerPersistentData::ApproximateUnsharedMemoryUsage() const {
  return 0;
}
#endif
void ScrollingCoordinator::DidCompositorScroll(
    CompositorElementId,
    const gfx::PointF&,
    cc::ScrollSourceType,
    const std::optional<cc::TargetSnapAreaElementIds>&) {}
void ScrollingCoordinator::DidChangeScrollbarsHidden(CompositorElementId,
                                                     bool) {}
Node* TopDocumentRootScrollerController::GlobalRootScroller() const {
  return nullptr;
}
Document* HTMLFrameOwnerElement::contentDocument() const {
  return nullptr;
}
FrameViewAutoSizeInfo::FrameViewAutoSizeInfo(LocalFrameView*) {}
void FrameViewAutoSizeInfo::ConfigureAutoSizeMode(const gfx::Size&,
                                                  const gfx::Size&) {}
ContentCaptureManager::ContentCaptureManager(LocalFrame& frame)
    : local_frame_root_(&frame) {}
ContentCaptureManager::~ContentCaptureManager() = default;
void ContentCaptureManager::OnFrameWasHidden() {}
void ContentCaptureManager::OnFrameWasShown() {}
void ContentCaptureManager::Shutdown() {}
void ContentCaptureManager::Trace(Visitor*) const {}
ContentCaptureTask* ContentCaptureManager::CreateContentCaptureTask() {
  return nullptr;
}
BackgroundColorPaintImageGenerator*
BackgroundColorPaintImageGenerator::Create(LocalFrame&) {
  return nullptr;
}
BoxShadowPaintImageGenerator* BoxShadowPaintImageGenerator::Create(
    LocalFrame&) {
  return nullptr;
}
ClipPathPaintImageGenerator* ClipPathPaintImageGenerator::Create(LocalFrame&) {
  return nullptr;
}
gfx::Rect LayoutEmbeddedContent::BorderBoxFromEmbeddedContent(
    const gfx::Rect& rect) const {
  return rect;
}
PhysicalOffset LayoutEmbeddedContent::BorderBoxFromEmbeddedContent(
    const PhysicalOffset& offset) const {
  return offset;
}
gfx::PointF LayoutEmbeddedContent::EmbeddedContentFromBorderBox(
    const gfx::PointF& point) const {
  return point;
}
bool SVGDocumentExtensions::ServiceSmilOnAnimationFrame(Document&) {
  return false;
}
bool SVGDocumentExtensions::ZoomAndPanEnabled() const {
  return false;
}
void PageAnimator::SetHasSmilAnimation() {}
void PageAnimator::ScheduleVisualUpdate(LocalFrame*) {}
void FrameView::UpdateRenderThrottlingStatus(bool, bool, bool, bool) {}
void FrameView::UpdateViewportIntersection(unsigned, bool) {}
FrameOverlay::FrameOverlay(LocalFrame* frame, std::unique_ptr<Delegate> delegate)
    : frame_(frame), delegate_(std::move(delegate)) {}
FrameOverlay::~FrameOverlay() = default;
void FrameOverlay::Destroy() {}
void FrameOverlay::UpdatePrePaint() {}
void FrameOverlay::Paint(GraphicsContext&) const {}
void FrameOverlay::Trace(Visitor*) const {}
NaturalSizingInfo LayoutSVGRoot::UnscaledNaturalSizingInfo(
    const SVGRect*) const {
  return NaturalSizingInfo();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect LayoutReplaced::ReplacedContentRect() const {
  return PhysicalRect();
}
#endif
#if defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect LayoutReplaced::ReplacedContentRect() const {
  return PhysicalRect();
}
PhysicalNaturalSizingInfo LayoutReplaced::ComputeNaturalSizingInfo() const {
  return PhysicalNaturalSizingInfo();
}
#endif
void LayoutEmbeddedContent::UpdateGeometry(EmbeddedContentView&) {}
bool MouseEventManager::IsMousePositionUnknown() {
  return true;
}
FragmentAnchor* FragmentAnchor::TryCreate(const KURL&, LocalFrame&, bool) {
  return nullptr;
}
void HTMLPlugInElement::UpdatePlugin() {}
WebPluginContainerImpl* PluginDocument::GetPluginView() {
  return nullptr;
}
void ResourceFetcher::UpdateImagePrioritiesAndSpeculativeDecodes() {}
void ResourceFetcher::SetDefersLoading(LoaderFreezeMode) {}
const KURL& ResourceRequestHead::Url() const {
  static KURL* url = new KURL();
  return *url;
}
HTMLFormElement* FrameLoadRequest::Form() const {
  return nullptr;
}
FrameLoader::FrameLoader(LocalFrame* frame)
    : frame_(frame),
      progress_tracker_(nullptr),
      dispatching_did_clear_window_object_in_main_world_(false) {}
bool FrameLoader::AllowPlugins() {
  return false;
}
String FrameLoader::UserAgent() const {
  return String();
}
std::optional<UserAgentMetadata> FrameLoader::UserAgentMetadata() const {
  return std::nullopt;
}
void FrameLoader::SetDefersLoading(LoaderFreezeMode) {}
void FrameLoader::Trace(Visitor* visitor) const {
  visitor->Trace(frame_);
  visitor->Trace(progress_tracker_);
  visitor->Trace(document_loader_);
}
void FrameLoader::StartNavigation(FrameLoadRequest&, WebFrameLoadType) {}
void FrameLoader::Init(const DocumentToken& document_token,
                       std::unique_ptr<PolicyContainer>,
                       const StorageKey&,
                       ukm::SourceId document_ukm_source_id,
                       const KURL&,
                       std::unique_ptr<base::UnguessableToken>) {
  AgentClusterKey agent_cluster_key = AgentClusterKey::CreateUniversalFileAgent();
  WindowAgent* agent =
      frame_->window_agent_factory().GetAgentForAgentClusterKey(
          false, agent_cluster_key);
  if (!agent) {
    Page* page = frame_->GetPage();
    AgentGroupScheduler& agent_group_scheduler = page->GetAgentGroupScheduler();
    agent = MakeGarbageCollected<WindowAgent>(
        agent_group_scheduler, agent_cluster_key);
  }
  frame_->SetDOMWindow(MakeGarbageCollected<LocalDOMWindow>(*frame_, agent));
  DocumentInit init = DocumentInit::Create()
                          .WithWindow(frame_->DomWindow(), nullptr)
                          .WithToken(document_token)
                          .ForInitialEmptyDocument(true)
                          .WithTypeFrom("text/html")
                          .WithUkmSourceId(document_ukm_source_id);
  Document* document = frame_->DomWindow()->InstallNewDocument(init);
#if defined(HTML_CSS_RENDERER_STANDALONE)
  static const AtomicString* html_local = new AtomicString("html");
  static const AtomicString* body_local = new AtomicString("body");
  static const AtomicString* xhtml_namespace =
      new AtomicString("http://www.w3.org/1999/xhtml");
  QualifiedName html_name(g_null_atom, *html_local, *xhtml_namespace);
  QualifiedName body_name(g_null_atom, *body_local, *xhtml_namespace);
  Element* html = MakeGarbageCollected<HTMLElement>(html_name, *document);
  Element* body = MakeGarbageCollected<HTMLElement>(body_name, *document);
  document->ParserAppendChild(html);
  html->ParserAppendChild(body);
  SetStandaloneDocumentBodyForStandaloneRenderer(document, To<HTMLElement>(body));
#else
#endif
  state_ = State::kInitialized;
}
void FrameLoader::DispatchUnloadEventAndFillOldDocumentInfoIfNeeded(bool) {}
void FrameLoader::Detach() {}
bool FrameLoader::DetachDocument() {
  return true;
}
bool FrameLoader::ShouldClose(bool, bool, base::TimeTicks&, base::TimeTicks&) {
  return true;
}
ResourceRequest FrameLoader::ResourceRequestForReload(WebFrameLoadType,
                                                      ClientRedirectPolicy) {
  return ResourceRequest();
}
FrameLoader::~FrameLoader() = default;
bool IsReloadLoadType(WebFrameLoadType) {
  return false;
}
void FrameSelection::DidLayout() {}
void FrameSelection::DidAttachDocument(Document*) {}
FrameSelection::FrameSelection(LocalFrame& frame)
    : frame_(frame),
      layout_selection_(nullptr),
      selection_editor_(nullptr),
      granularity_(TextGranularity::kCharacter),
      x_pos_for_vertical_arrow_navigation_(LayoutUnit()),
      focused_(false),
      is_directional_(false),
      frame_caret_(nullptr) {}
FrameSelection::~FrameSelection() = default;
void FrameSelection::Trace(Visitor*) const {}
String FrameSelection::SelectedText() const {
  return String();
}
String FrameSelection::SelectedText(const TextIteratorBehavior&) const {
  return String();
}
String FrameSelection::SelectedTextForClipboard() const {
  return String();
}
Editor::Editor(LocalFrame& frame)
    : frame_(&frame),
      undo_stack_(nullptr),
      prevent_reveal_selection_(0),
      should_start_new_kill_ring_sequence_(false),
      should_style_with_css_(false),
      kill_ring_(nullptr),
      default_paragraph_separator_(EditorParagraphSeparator::kIsDiv) {}
Editor::~Editor() = default;
void Editor::Trace(Visitor*) const {}
void Editor::CopyImage(const HitTestResult&) {}
void Editor::Clear() {}
bool Editor::CanEdit() const {
  return false;
}
void Editor::SetBaseWritingDirection(mojo_base::mojom::TextDirection) {}
EventHandler::EventHandler(LocalFrame& frame)
    : frame_(&frame),
      selection_controller_(nullptr),
      hover_timer_(frame.GetTaskRunner(TaskType::kUserInteraction),
                   this,
                   &EventHandler::HoverTimerFired),
      cursor_update_timer_(frame.GetTaskRunner(TaskType::kUserInteraction),
                           this,
                           &EventHandler::CursorUpdateTimerFired),
      should_only_fire_drag_over_event_(false),
      max_mouse_moved_duration_(0.0),
      active_interval_timer_(frame.GetTaskRunner(TaskType::kUserInteraction),
                             this,
                             &EventHandler::ActiveIntervalTimerFired),
      should_use_touch_event_adjusted_point_(false) {}
void EventHandler::Trace(Visitor*) const {}
void EventHandler::Clear() {}
bool EventHandler::BubblingScroll(mojom::blink::ScrollDirection,
                                  ui::ScrollGranularity,
                                  Node*) {
  return false;
}
HitTestResult EventHandler::HitTestResultAtLocation(
    const HitTestLocation&,
    HitTestRequest::HitTestRequestType,
    const LayoutObject*,
    bool,
    std::optional<HitTestRequest::HitNodeCb>) {
  return HitTestResult();
}
void EventHandler::HoverTimerFired(TimerBase*) {}
void EventHandler::CursorUpdateTimerFired(TimerBase*) {}
void EventHandler::ActiveIntervalTimerFired(TimerBase*) {}
FrameConsole::FrameConsole(LocalFrame& frame) : frame_(&frame) {}
BrowserInterfaceBrokerProxyImpl::BrowserInterfaceBrokerProxyImpl(
    ContextLifecycleNotifier* notifier)
    : broker_(notifier) {
}
BrowserInterfaceBrokerProxy::BrowserInterfaceBrokerProxy() = default;
BrowserInterfaceBrokerProxy::~BrowserInterfaceBrokerProxy() = default;
InterfaceRegistry* InterfaceRegistry::GetEmptyInterfaceRegistry() {
  class EmptyInterfaceRegistry final : public InterfaceRegistry {
   public:
    void AddInterface(const char*,
                      const InterfaceFactory&,
                      scoped_refptr<base::SingleThreadTaskRunner>) override {}
    void AddAssociatedInterface(
        const char*,
        const AssociatedInterfaceFactory&) override {}
  };
  static InterfaceRegistry* registry = new EmptyInterfaceRegistry();
  return registry;
}
void BrowserInterfaceBrokerProxyImpl::Bind(
    CrossVariantMojoRemote<mojom::BrowserInterfaceBrokerInterfaceBase>,
    scoped_refptr<base::SingleThreadTaskRunner>) {}
CrossVariantMojoReceiver<mojom::BrowserInterfaceBrokerInterfaceBase>
BrowserInterfaceBrokerProxyImpl::Reset(
    scoped_refptr<base::SingleThreadTaskRunner>) {
  return {};
}
void BrowserInterfaceBrokerProxyImpl::GetInterface(
    mojo::GenericPendingReceiver) const {}
bool BrowserInterfaceBrokerProxyImpl::is_bound() const {
  return false;
}
void BrowserInterfaceBrokerProxyImpl::Trace(Visitor*) const {}
InspectorIssueReporter::InspectorIssueReporter(InspectorIssueStorage* storage)
    : storage_(storage) {}
void InspectorIssueReporter::Trace(Visitor*) const {}
InspectorIssueReporter::~InspectorIssueReporter() = default;
void FrameConsole::Trace(Visitor*) const {}
void FrameConsole::AddMessage(ConsoleMessage*, bool) {}
void LocalFrameMojoHandler::Trace(Visitor*) const {}
void LocalFrameMojoHandler::WasAttachedAsLocalMainFrame() {}
void LocalFrameMojoHandler::ClosePageForTesting() {}
void LocalFrameMojoHandler::DidDetachFrame() {}
mojom::blink::ReportingServiceProxy*
LocalFrameMojoHandler::ReportingService() {
  return nullptr;
}
mojom::blink::DevicePostureProvider*
LocalFrameMojoHandler::DevicePostureProvider() {
  return nullptr;
}
mojom::blink::BackForwardCacheControllerHost&
LocalFrameMojoHandler::BackForwardCacheControllerHostRemote() {
  return *static_cast<mojom::blink::BackForwardCacheControllerHost*>(nullptr);
}
void SystemClipboard::Trace(Visitor*) const {}
SystemClipboard::Snapshot::~Snapshot() = default;
SecurityContext::~SecurityContext() = default;
ContextLifecycleNotifier::~ContextLifecycleNotifier() = default;
void ContextLifecycleObserver::Trace(Visitor*) const {}
void ContextLifecycleObserver::SetContextLifecycleNotifier(
    ContextLifecycleNotifier* notifier) {
  notifier_ = notifier;
}
bool ContextLifecycleNotifier::IsContextDestroyed() const {
  return false;
}
void WindowPerformance::ClearForWindowReuse(LocalDOMWindow&) {}
const base::UnguessableToken& ExecutionContext::GetAgentClusterID() const {
  return base::UnguessableToken::Null();
}
v8::Local<v8::Context> ToV8ContextMaybeEmpty(LocalFrame*,
                                             DOMWrapperWorld&) {
  return v8::Local<v8::Context>();
}
v8::Local<v8::Value> ScriptWrappable::ToV8(ScriptState*) {
  return v8::Local<v8::Value>();
}
TrustedTypePolicyFactory::TrustedTypePolicyFactory(ExecutionContext* context)
    : ExecutionContextClient(context) {}
const SecurityOrigin* ExecutionContext::GetSecurityOrigin() const {
  return nullptr;
}
SecurityOrigin* ExecutionContext::GetMutableSecurityOrigin() {
  return nullptr;
}
void TextFragmentHandler::Trace(Visitor*) const {}
void TextFragmentHandler::DidDetachDocumentOrFrame() {}
void TextFragmentHandler::BindTextFragmentReceiver(
    mojo::PendingReceiver<mojom::blink::TextFragmentReceiver>) {}
void v8_compile_hints::V8LocalCompileHintsProducer::Trace(Visitor*) const {}
v8_compile_hints::V8LocalCompileHintsProducer::V8LocalCompileHintsProducer(
    LocalFrame* frame)
    : should_generate_data_(false), frame_(frame) {}
void v8_compile_hints::V8LocalCompileHintsProducer::GenerateData(bool) {}
void v8_compile_hints::V8CrowdsourcedCompileHintsProducer::GenerateData() {}
V8HistogramAccumulator* V8HistogramAccumulator::GetInstance() {
  static V8HistogramAccumulator* accumulator = new V8HistogramAccumulator();
  return accumulator;
}
V8HistogramAccumulator::V8HistogramAccumulator() = default;
void V8HistogramAccumulator::GenerateDataInteractive() {}
InspectorTaskRunner::InspectorTaskRunner(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : isolate_task_runner_(std::move(task_runner)), task_queue_cv_(&lock_) {}
InspectorTaskRunner::~InspectorTaskRunner() = default;
void InspectorTaskRunner::InitIsolate(v8::Isolate*) {}
void InspectorTaskRunner::Dispose() {}
void MainThreadDebugger::DidClearContextsForFrame(LocalFrame*) {}
MainThreadDebugger* MainThreadDebugger::Instance(v8::Isolate*) {
  return nullptr;
}
void MainThreadDebugger::ExceptionThrown(ExecutionContext*, ErrorEvent*) {}
void ScriptController::DisableEval(const String&) {}
void ScriptController::SetWasmEvalErrorMessage(const String&) {}
LocalWindowProxy* ScriptController::WindowProxy(DOMWrapperWorld&) {
  return nullptr;
}
void WorldSafeV8ReferenceInternal::MaybeCheckCreationContext(
    v8::Isolate*,
    v8::Local<v8::Context>,
    const DOMWrapperWorld&,
    v8::Local<v8::Value>) {}
void WindowProxyManager::Trace(Visitor*) const {}
void WindowProxyManager::ClearForV8MemoryPurge() {}
void WindowProxyManager::ClearForNavigation() {}
void LocalWindowProxyManager::SetAbortScriptExecution(
    v8::Context::AbortScriptExecutionCallback) {}
WindowProxyManager::WindowProxyManager(v8::Isolate* isolate,
                                       Frame& frame,
                                       FrameType frame_type)
    : isolate_(isolate),
      frame_(&frame),
      frame_type_(frame_type),
      window_proxy_(nullptr) {}
PerformanceMonitor::PerformanceMonitor(LocalFrame* frame, v8::Isolate* isolate)
    : local_root_(frame), isolate_(isolate) {}
PerformanceMonitor::~PerformanceMonitor() = default;
void PerformanceMonitor::Trace(Visitor*) const {}
void PerformanceMonitor::Dispose() {}
void PerformanceMonitor::Shutdown() {}
void PerformanceMonitor::WillProcessTask(base::TimeTicks) {}
void PerformanceMonitor::DidProcessTask(base::TimeTicks, base::TimeTicks) {}
AttributionSrcLoader::AttributionSrcLoader(LocalFrame*) {}
AttributionSrcLoader::~AttributionSrcLoader() = default;
void AttributionSrcLoader::Trace(Visitor*) const {}
std::optional<Impression> AttributionSrcLoader::RegisterNavigation(
    const KURL&,
    const std::vector<WebString>&,
    bool,
    network::mojom::ReferrerPolicy) {
  return std::nullopt;
}
IdlenessDetector::IdlenessDetector(LocalFrame* frame, const base::TickClock* clock)
    : local_frame_(frame),
      task_observer_added_(false),
      clock_(clock),
      network_quiet_timer_(frame ? frame->GetTaskRunner(TaskType::kInternalLoading)
                                 : nullptr,
                           this,
                           &IdlenessDetector::NetworkQuietTimerFired) {}
void IdlenessDetector::Trace(Visitor*) const {}
void IdlenessDetector::Shutdown() {}
void IdlenessDetector::StartIfNeeded() {}
void IdlenessDetector::NetworkQuietTimerFired(TimerBase*) {}
void IdlenessDetector::WillProcessTask(base::TimeTicks) {}
void IdlenessDetector::DidProcessTask(base::TimeTicks, base::TimeTicks) {}
void FontFaceSetDocument::DidLayout(Document&) {}
void EventHandler::MarkHoverStateDirty() {}
void PaintLayerScrollableArea::UpdateAllStickyConstraints() {}
LayoutBox* PaintLayerScrollableArea::GetLayoutBox() const {
  return nullptr;
}
gfx::Rect PaintLayerScrollableArea::VisibleContentRect(
    IncludeScrollbarsInRect) const {
  return gfx::Rect();
}
std::optional<gfx::PointF> PaintLayerScrollableArea::GetSnapPositionAndSetTarget(
    const cc::SnapSelectionStrategy&) {
  return std::nullopt;
}
PaintLayerScrollableArea* PaintLayerScrollableArea::FromNode(const Node&) {
  return nullptr;
}
void TopDocumentRootScrollerController::Initialize(RootFrameViewport&,
                                                   Document&) {}
const DarkModeSettings& GetCurrentDarkModeSettings() {
  static DarkModeSettings* settings = new DarkModeSettings();
  return *settings;
}
class DarkModeInvertedColorCache {};
DarkModeFilter::ImmutableData::ImmutableData(const DarkModeSettings&)
    : foreground_classifier(nullptr),
      background_classifier(nullptr),
      image_classifier(nullptr),
      color_filter(nullptr),
      image_filter(nullptr) {}
DarkModeFilter::DarkModeFilter(const DarkModeSettings& settings)
    : immutable_(settings),
      inverted_color_cache_(new DarkModeInvertedColorCache()) {}
DarkModeFilter::~DarkModeFilter() {}
SkColor4f DarkModeFilter::InvertColorIfNeeded(const SkColor4f& color,
                                              ElementRole) {
  return color;
}
SkColor4f DarkModeFilter::InvertColorIfNeeded(
    const SkColor4f& color,
    ElementRole,
    const SkColor4f&) {
  return color;
}
std::optional<cc::PaintFlags> DarkModeFilter::ApplyToFlagsIfNeeded(
    const cc::PaintFlags&,
    ElementRole,
    SkColor4f) {
  return std::nullopt;
}
size_t DarkModeFilter::GetInvertedColorCacheSizeForTesting() {
  return 0;
}
bool DarkModeFilter::ShouldApplyFilterToImage(ImageType) const {
  return false;
}
sk_sp<cc::ColorFilter> DarkModeFilter::GenerateImageFilter(
    const SkPixmap&,
    const SkIRect&) const {
  return nullptr;
}
void DarkModeFilter::ApplyFilterToImage(Image*, cc::PaintFlags*, const SkRect&) {}
void LocalFrameUkmAggregator::RecordTimerSample(size_t,
                                                base::TimeTicks,
                                                base::TimeTicks) {}
LocalFrameUkmAggregator::LocalFrameUkmAggregator()
    : clock_(base::DefaultTickClock::GetInstance()) {}
LocalFrameUkmAggregator::ScopedUkmHierarchicalTimer
LocalFrameUkmAggregator::GetScopedTimer(size_t metric_index) {
  return ScopedUkmHierarchicalTimer(scoped_refptr<LocalFrameUkmAggregator>(),
                                    metric_index, clock_);
}
LocalFrameUkmAggregator::ScopedUkmHierarchicalTimer::ScopedUkmHierarchicalTimer(
    scoped_refptr<LocalFrameUkmAggregator> aggregator,
    size_t metric_index,
    const base::TickClock* clock)
    : aggregator_(std::move(aggregator)),
      metric_index_(metric_index),
      clock_(clock),
      start_time_(base::TimeTicks()) {}
LocalFrameUkmAggregator::ScopedUkmHierarchicalTimer::ScopedUkmHierarchicalTimer(
    ScopedUkmHierarchicalTimer&& other)
    : aggregator_(std::move(other.aggregator_)),
      metric_index_(other.metric_index_),
      clock_(other.clock_),
      start_time_(other.start_time_) {}
LocalFrameUkmAggregator::ScopedUkmHierarchicalTimer::
    ~ScopedUkmHierarchicalTimer() = default;
LocalFrameUkmAggregator::~LocalFrameUkmAggregator() = default;
LocalFrameUkmAggregator::ScopedForcedLayoutTimer
LocalFrameUkmAggregator::GetScopedForcedLayoutTimer(
    DocumentUpdateReason update_reason) {
  return ScopedForcedLayoutTimer(*this, update_reason, true, false, false,
                                 false);
}
LocalFrameUkmAggregator::ScopedForcedLayoutTimer::ScopedForcedLayoutTimer(
    LocalFrameUkmAggregator& aggregator,
    DocumentUpdateReason update_reason,
    bool avoid_unnecessary_forced_layout_measurements,
    bool should_report_uma_this_frame,
    bool is_pre_fcp,
    bool)
    : aggregator_(&aggregator),
      update_reason_(update_reason),
      start_time_(base::TimeTicks()),
      avoid_unnecessary_forced_layout_measurements_(
          avoid_unnecessary_forced_layout_measurements),
      should_report_uma_this_frame_(should_report_uma_this_frame),
      is_pre_fcp_(is_pre_fcp) {}
LocalFrameUkmAggregator::ScopedForcedLayoutTimer::~ScopedForcedLayoutTimer() =
    default;
LocalFrameUkmAggregator::ScopedForcedLayoutTimer::ScopedForcedLayoutTimer(
    ScopedForcedLayoutTimer&& other)
    : aggregator_(std::move(other.aggregator_)),
      update_reason_(other.update_reason_),
      start_time_(other.start_time_),
      avoid_unnecessary_forced_layout_measurements_(
          other.avoid_unnecessary_forced_layout_measurements_),
      should_report_uma_this_frame_(other.should_report_uma_this_frame_),
      is_pre_fcp_(other.is_pre_fcp_) {}
LocalFrameUkmAggregator::ScopedForcedLayoutTimer&
LocalFrameUkmAggregator::ScopedForcedLayoutTimer::operator=(
    ScopedForcedLayoutTimer&& other) {
  aggregator_ = std::move(other.aggregator_);
  update_reason_ = other.update_reason_;
  start_time_ = other.start_time_;
  avoid_unnecessary_forced_layout_measurements_ =
      other.avoid_unnecessary_forced_layout_measurements_;
  should_report_uma_this_frame_ = other.should_report_uma_this_frame_;
  is_pre_fcp_ = other.is_pre_fcp_;
  return *this;
}
void LocalFrameUkmAggregator::TransmitFinalSample(int64_t,
                                                  ukm::UkmRecorder*,
                                                  bool) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintController::~PaintController() = default;
#endif
void MobileFriendlinessChecker::NotifyPaintBegin() {}
void MobileFriendlinessChecker::NotifyPaintEnd() {}
MobileFriendlinessChecker* MobileFriendlinessChecker::Create(
    LocalFrameView&) {
  return nullptr;
}
void MobileFriendlinessChecker::MaybeRecompute() {}
TapFriendlinessChecker* TapFriendlinessChecker::CreateIfMobile(
    LocalFrameView&) {
  return nullptr;
}
LayoutShiftTracker::LayoutShiftTracker(LocalFrameView* frame_view)
    : frame_view_(frame_view),
      is_active_(false),
      score_(0.0),
      weighted_score_(0.0),
      timer_(nullptr, this, &LayoutShiftTracker::TimerFired),
      frame_max_distance_(0.0),
      overall_max_distance_(0.0),
      observed_input_or_scroll_(false),
      most_recent_input_timestamp_initialized_(false) {}
void LayoutShiftTracker::Dispose() {}
void LayoutShiftTracker::NotifyViewportSizeChanged() {}
void LayoutShiftTracker::NotifyScroll(mojom::blink::ScrollType,
                                      ScrollOffset) {}
PaintTimingDetector::PaintTimingDetector(LocalFrameView*) {}
void PaintTimingDetector::NotifyScroll(mojom::blink::ScrollType) {}
void PaintTimingDetector::Trace(Visitor*) const {}
void PaintTimingDetector::EmitLcpPerformanceEntry(
    const DOMPaintTimingInfo&,
    uint64_t,
    base::TimeTicks,
    const AtomicString&,
    const String&,
    Element*) {}
void PaintTimingDetector::OnLcpMetricsForReportingChanged() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
CullRectUpdater::CullRectUpdater(PaintLayer& starting_layer, bool)
    : starting_layer_(starting_layer),
      view_transition_supplement_(nullptr),
      expansion_ratio_(0.0f) {}
void CullRectUpdater::Update() {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintController::PaintController(bool,
                                 PaintControllerPersistentData* data,
                                 PaintBenchmarkMode mode)
    : persistent_data_(data),
      paint_chunker_(new_paint_artifact_->GetPaintChunks()),
      benchmark_mode_(mode) {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
GraphicsContext::GraphicsContext(PaintController& paint_controller)
    : paint_controller_(paint_controller) {}
GraphicsContext::~GraphicsContext() = default;
void GraphicsContext::FillRect(const gfx::Rect&,
                               const Color&,
                               const AutoDarkMode&,
                               SkBlendMode) {}
void PaintController::UpdateCurrentPaintChunkProperties(
    const PaintChunk::Id&,
    const DisplayItemClient&,
    const PropertyTreeStateOrAlias&) {}
void PaintController::UpdateCurrentPaintChunkProperties(
    const PropertyTreeStateOrAlias&) {}
bool PaintController::UseCachedItemIfPossible(const DisplayItemClient&,
                                              DisplayItem::Type) {
  return false;
}
DrawingRecorder::DrawingRecorder(GraphicsContext& context,
                                 const DisplayItemClient& client,
                                 DisplayItem::Type type,
                                 const gfx::Rect& visual_rect)
    : context_(context),
      client_(client),
    type_(type),
      visual_rect_(visual_rect) {}
DrawingRecorder::~DrawingRecorder() = default;
PaintResult PaintLayerPainter::Paint(GraphicsContext&, PaintFlags) {
  return kFullyPainted;
}
void FramePainter::Paint(GraphicsContext&, PaintFlags) {}
#endif
void VisualViewport::Paint(GraphicsContext&) const {}
void LinkHighlight::Paint(GraphicsContext&) const {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const PaintArtifact& PaintController::CommitNewDisplayItems() {
  static Persistent<PaintArtifact> artifact =
      MakeGarbageCollected<PaintArtifact>();
  return *artifact;
}
#endif
ResizeObserverController* ResizeObserverController::FromIfExists(
    LocalDOMWindow&) {
  return nullptr;
}
size_t ResizeObserverController::GatherObservations() {
  return 0;
}
bool ResizeObserverController::SkippedObservations() {
  return false;
}
void ResizeObserverController::ClearObservations() {}
void ResizeObserverController::DeliverObservations() {}
void ExecutionContext::DispatchErrorEvent(ErrorEvent*, SanitizeScriptErrors) {}
PublicURLManager& ExecutionContext::GetPublicURLManager() {
  return *static_cast<PublicURLManager*>(nullptr);
}
void PublicURLManager::ResolveAsBlobURLToken(
    const KURL&,
    mojo::PendingReceiver<mojom::blink::BlobURLToken>,
    bool) {}
bool RootScrollerController::PerformRootScrollerSelection() {
  return false;
}
void LinkHighlight::UpdateBeforePrePaint() {}
void LinkHighlight::UpdateAfterPrePaint() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PrePaintTreeWalk::WalkTree(LocalFrameView&) {}
#endif
void PageAnimator::ReportFrameAnimations(cc::AnimationHost*) {}
void WebPluginContainerImpl::UpdateAllLifecyclePhases() {}
void FrameSelection::UpdateStyleAndLayoutIfNeeded() {}
void DragCaret::UpdateStyleAndLayoutIfNeeded() {}
bool SnapCoordinator::UpdateSnapContainerData(LayoutBox&) {
  return false;
}
bool PaintLayerScrollableArea::HasRunningAnimation() {
  return false;
}
void ScrollMarkerGroupPseudoElement::ScrollSelectedIntoView(bool) {}
bool SVGGraphicsElement::IsNonRendered(const LayoutObject*) const {
  return false;
}

DOMRectList::DOMRectList() = default;
DOMRect::DOMRect(double x, double y, double width, double height)
    : DOMRectReadOnly(x, y, width, height) {}
DOMRect* DOMRect::FromRectF(const gfx::RectF& rect) {
  return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), rect.width(),
                                       rect.height());
}

bool IsTrustedTypesEventHandlerAttribute(const QualifiedName&) { return false; }
bool SVGAnimatedHref::IsKnownAttribute(const QualifiedName&) { return false; }
AtomicString TrustedTypesCheckFor(
    SpecificTrustedType,
    const V8UnionTrustedHTMLOrTrustedScriptOrTrustedScriptURL*,
    const ExecutionContext*,
    const AtomicString&,
    const AtomicString&,
    ExceptionState&) {
  return g_empty_atom;
}
AtomicString TrustedTypesCheckFor(SpecificTrustedType,
                                  AtomicString value,
                                  const ExecutionContext*,
                                  const AtomicString&,
                                  const AtomicString&,
                                  ExceptionState&) {
  return value;
}

void RenderBlockingResourceManager::RemovePendingParsingElement(
    const AtomicString&,
    Element*) {}
void DOMTokenList::DidUpdateAttributeValue(const AtomicString&,
                                           const AtomicString&) {}
#if DCHECK_IS_ON()
unsigned EventDispatchForbiddenScope::count_ = 0;
#endif
ScopedEventQueue* ScopedEventQueue::Instance() {
  return nullptr;
}
void Performance::NotifyNavigationTimingToObservers() {}
namespace probe {
void LoadEventFired(LocalFrame*) {}
}
void SoftNavigationHeuristics::ModifiedAttribute(Element*,
                                                 const QualifiedName&) {}
SoftNavigationHeuristics* SoftNavigationHeuristics::CreateIfNeeded(
    LocalDOMWindow*) {
  return nullptr;
}
void SoftNavigationHeuristics::InsertedNode(Node*, Node*) {}
bool SoftNavigationHeuristics::ModifiedNode(Node*) {
  return false;
}
void SoftNavigationHeuristics::Shutdown() {}
void HTMLAnchorElement::UpdateScrollTargetGroupMembership() {}
namespace focusgroup {
FocusgroupData ParseFocusgroup(const Element*, const AtomicString&) {
  return FocusgroupData();
}
}  // namespace focusgroup
bool ProtocolIsJavaScript(const StringView&) { return false; }
unsigned ScriptForbiddenScope::g_main_thread_counter_ = 0;
unsigned ScriptForbiddenScope::g_blink_lifecycle_counter_ = 0;
unsigned& ScriptForbiddenScope::GetMutableCounter() {
  return g_main_thread_counter_;
}
ScrollResult::ScrollResult() = default;
void ScrollResult::Trace(Visitor*) const {}
const void* ScrollResult::TemplateKey() const {
  return nullptr;
}
void ScrollResult::FillTemplateProperties(Vector<std::string_view>&) const {}
v8::Local<v8::Object> ScrollResult::FillValues(
    ScriptState*,
    v8::Local<v8::DictionaryTemplate>) const {
  return v8::Local<v8::Object>();
}
ContextLifecycleObserver::~ContextLifecycleObserver() = default;
void ContextLifecycleNotifier::Trace(Visitor*) const {}
FrameLifecycle::FrameLifecycle() : state_(kAttached) {}
NavigationRateLimiter::NavigationRateLimiter(Frame& frame)
    : frame_(&frame), enabled(false) {}
bool NavigationRateLimiter::CanProceed() {
  return true;
}
OpenedFrameTracker::OpenedFrameTracker() = default;
OpenedFrameTracker::~OpenedFrameTracker() = default;
FirstMeaningfulPaintDetector::FirstMeaningfulPaintDetector(PaintTiming* timing)
    : paint_timing_(timing) {}
void FirstMeaningfulPaintDetector::Trace(Visitor*) const {}
void PageAnimator::Trace(Visitor*) const {}
void PageVisibilityObserver::ObserverSetWillBeCleared() {}
bool ScopedBrowsingContextGroupPauser::IsActive(Page&) {
  return false;
}
bool ScopedPagePauser::IsActive() {
  return false;
}
ScopedPagePauser::ScopedPagePauser() = default;
ScopedPagePauser::~ScopedPagePauser() = default;
PageAnimator::PageAnimator(Page& page)
    : page_(&page),
      servicing_animations_(false),
      updating_layout_and_style_for_painting_(false) {}
void PageAnimator::SetSuppressFrameRequestsWorkaroundFor704763Only(bool) {}
void PageAnimator::ServiceScriptedAnimations(base::TimeTicks) {}
void PageAnimator::UpdateLifecycleToLayoutClean(LocalFrame&,
                                                DocumentUpdateReason) {}
void PageAnimator::UpdateAllLifecyclePhasesExceptPaint(
    LocalFrame&,
    DocumentUpdateReason) {}
void PageAnimator::UpdateAllLifecyclePhases(LocalFrame&,
                                            DocumentUpdateReason) {}
void AutoscrollController::Trace(Visitor*) const {}
AutoscrollController::AutoscrollController(Page& page)
    : page_(&page),
      autoscroll_type_(kNoAutoscroll),
      middle_click_mode_(kMiddleClickInitial) {}
void AutoscrollController::StopMiddleClickAutoscroll(LocalFrame*) {}
void AutoscrollController::StopAutoscrollIfNeeded(LayoutObject*) {}
void AutoscrollController::Animate() {}
void DragCaret::Trace(Visitor*) const {}
DragCaret::DragCaret() : display_item_client_(nullptr) {}
void DragController::Trace(Visitor*) const {}
DragController::DragController(Page* page)
    : ExecutionContextLifecycleObserver(nullptr),
      page_(page),
      document_is_handling_drag_(false) {}
void DragController::ContextDestroyed() {}
void ContextMenuController::Trace(Visitor*) const {}
ContextMenuController::ContextMenuController(Page* page) : page_(page) {}
ContextMenuController::~ContextMenuController() = default;
void ContextMenuController::CustomContextMenuAction(uint32_t) {}
void ContextMenuController::ContextMenuClosed(
    const KURL&,
    const std::optional<Impression>&) {}
bool ContextMenuController::ShowContextMenu(LocalFrame*,
                                            const PhysicalOffset&,
                                            ui::mojom::blink::MenuSourceType,
                                            const MouseEvent*) {
  return false;
}
void ContextMenuController::DocumentDetached(Document*) {}
void PageScaleConstraintsSet::Trace(Visitor*) const {}
PageScaleConstraintsSet::PageScaleConstraintsSet(Page* page)
    : page_(page),
      last_contents_width_(0),
      last_vertical_scrollbar_width_(0),
      needs_reset_(false),
      constraints_dirty_(false) {}
const PageScaleConstraints& PageScaleConstraintsSet::DefaultConstraints()
    const {
  return default_constraints_;
}
void PageScaleConstraintsSet::SetDefaultConstraints(
    const PageScaleConstraints& constraints) {
  default_constraints_ = constraints;
}
void PageScaleConstraintsSet::ComputeFinalConstraints() {
  final_constraints_ = default_constraints_;
}
void PageScaleConstraintsSet::SetNeedsReset(bool value) {
  needs_reset_ = value;
}
void PageScaleConstraintsSet::SetUserAgentConstraints(
    const PageScaleConstraints& constraints) {
  user_agent_constraints_ = constraints;
}
bool PageScaleConstraints::operator==(const PageScaleConstraints&) const {
  return true;
}
PageScaleConstraints::PageScaleConstraints()
    : initial_scale(1), minimum_scale(1), maximum_scale(1) {}
void PointerLockController::Trace(Visitor*) const {}
PointerLockController::PointerLockController(Page* page) : page_(page) {}
void BrowserControls::Trace(Visitor*) const {}
BrowserControls::BrowserControls(Page& page)
    : page_(&page),
      top_shown_ratio_(1),
      bottom_shown_ratio_(1),
      baseline_top_content_offset_(0),
      baseline_bottom_content_offset_(0),
      accumulated_scroll_delta_(0),
      permitted_state_(cc::BrowserControlsState::kBoth) {}
void ConsoleMessageStorage::Trace(Visitor*) const {}
ConsoleMessageStorage::ConsoleMessageStorage() : expired_count_(0) {}
void ConsoleMessageStorage::Clear() {}
void TopDocumentRootScrollerController::Trace(Visitor*) const {}
TopDocumentRootScrollerController::TopDocumentRootScrollerController(Page& page)
    : page_(&page) {}
LinkHighlight::~LinkHighlight() = default;
void LinkHighlight::Trace(Visitor*) const {}
LinkHighlight::LinkHighlight(Page& page) : page_(&page) {}
void LinkHighlight::ResetForPageNavigation() {}
void LinkHighlight::AnimationHostInitialized(cc::AnimationHost&) {}
void LinkHighlight::WillCloseAnimationHost() {}
LinkHighlightImpl::~LinkHighlightImpl() = default;
ValidationMessageClientImpl::~ValidationMessageClientImpl() = default;
ValidationMessageClientImpl::ValidationMessageClientImpl(Page& page)
    : page_(&page) {}
void ValidationMessageClientImpl::Trace(Visitor*) const {}
void ValidationMessageClientImpl::ShowValidationMessage(Element&,
                                                        const String&,
                                                        TextDirection,
                                                        const String&,
                                                        TextDirection) {}
void ValidationMessageClientImpl::HideValidationMessage(const Element&) {}
bool ValidationMessageClientImpl::IsValidationMessageVisible(
    const Element&) {
  return false;
}
void ValidationMessageClientImpl::DocumentDetached(const Document&) {}
void ValidationMessageClientImpl::DidChangeFocusTo(const Element*) {}
void ValidationMessageClientImpl::WillBeDestroyed() {}
void ValidationMessageClientImpl::ServiceScriptedAnimations(base::TimeTicks) {}
void ValidationMessageClientImpl::LayoutOverlay() {}
void ValidationMessageClientImpl::UpdatePrePaint() {}
void ValidationMessageClientImpl::PaintOverlay(GraphicsContext&) {}
void ValidationMessageClientImpl::WillOpenPopup() {}
void v8_compile_hints::V8CrowdsourcedCompileHintsProducer::Trace(
    Visitor*) const {}
v8_compile_hints::V8CrowdsourcedCompileHintsProducer::
    V8CrowdsourcedCompileHintsProducer(Page* page)
    : page_(page) {}
void v8_compile_hints::V8CrowdsourcedCompileHintsProducer::ClearData() {}
ScrollingCoordinator::~ScrollingCoordinator() = default;
ScrollingCoordinator::ScrollingCoordinator(Page* page) : page_(page) {}
void ScrollingCoordinator::Trace(Visitor*) const {}
void ScrollingCoordinator::WillBeDestroyed() {}
void PointerLockController::DocumentDetached(Document*) {}
SpatialNavigationController::SpatialNavigationController(Page& page)
    : page_(&page) {}
void SpatialNavigationController::Trace(Visitor*) const {}
SVGDocumentResourceTracker::SVGDocumentResourceTracker(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    const String& cache_identifier)
    : dispose_task_runner_(std::move(task_runner)),
      cache_identifier_(cache_identifier) {}
void SVGDocumentResourceTracker::Trace(Visitor*) const {}
void SVGDocumentResourceTracker::WillBeDestroyed() {}
String SVGDocumentResourceTracker::MakeCacheIdentifier(StringView) {
  return String();
}
SVGDocumentResourceTracker* SVGResourceSchedulerRegistry::GetTracker(
    AgentGroupScheduler&) {
  return nullptr;
}
void PluginData::Trace(Visitor*) const {}
void PluginData::UpdatePluginList() {}
void PluginData::ResetPluginData() {}
FeatureAndJSLocationBlockingBFCache::~FeatureAndJSLocationBlockingBFCache() =
    default;
DisplayLockDocumentState::ScopedForceActivatableDisplayLocks
DisplayLockDocumentState::GetScopedForceActivatableLocks() {
  return ScopedForceActivatableDisplayLocks(nullptr);
}
DisplayLockDocumentState::ScopedForceActivatableDisplayLocks::
    ScopedForceActivatableDisplayLocks(DisplayLockDocumentState* state)
    : state_(state) {}
DisplayLockDocumentState::ScopedForceActivatableDisplayLocks::
    ~ScopedForceActivatableDisplayLocks() = default;
bool Editor::FindString(LocalFrame&, const String&, FindOptions) {
  return false;
}
void SyncScrollAttemptHeuristic::DidAccessScrollOffset() {}
void SyncScrollAttemptHeuristic::DidSetScrollOffset() {}
void SyncScrollAttemptHeuristic::DidRequestAnimationFrame() {}
CSSComputedStyleDeclaration::CSSComputedStyleDeclaration(Element* element,
                                                         bool,
                                                         const String&)
    : CSSStyleDeclaration(nullptr),
      element_(element),
      pseudo_element_specifier_(kPseudoIdNone),
      allow_visited_style_(false),
      guaranteed_style_clean_(false) {}
CSSComputedStyleDeclaration::~CSSComputedStyleDeclaration() = default;
void CSSComputedStyleDeclaration::Trace(Visitor* visitor) const {
  visitor->Trace(element_);
  CSSStyleDeclaration::Trace(visitor);
}
CSSRule* CSSComputedStyleDeclaration::parentRule() const {
  return nullptr;
}
String CSSComputedStyleDeclaration::cssText() const {
  return String();
}
void CSSComputedStyleDeclaration::setCSSText(const ExecutionContext*,
                                             const String&,
                                             ExceptionState&) {}
unsigned CSSComputedStyleDeclaration::length() const {
  return 0;
}
String CSSComputedStyleDeclaration::item(unsigned) const {
  return String();
}
String CSSComputedStyleDeclaration::getPropertyValue(const String&) {
  return String();
}
String CSSComputedStyleDeclaration::getPropertyPriority(const String&) {
  return String();
}
String CSSComputedStyleDeclaration::GetPropertyShorthand(const String&) {
  return String();
}
bool CSSComputedStyleDeclaration::IsPropertyImplicit(const String&) {
  return false;
}
void CSSComputedStyleDeclaration::setProperty(const ExecutionContext*,
                                              const String&,
                                              const String&,
                                              const String&,
                                              ExceptionState&) {}
String CSSComputedStyleDeclaration::removeProperty(const String&,
                                                   ExceptionState&) {
  return String();
}
void CSSComputedStyleDeclaration::QuietlyRemoveProperty(const String&) {}
const CSSValue* CSSComputedStyleDeclaration::GetPropertyCSSValueInternal(
    const AtomicString&) {
  return nullptr;
}
const CSSValue* CSSComputedStyleDeclaration::GetPropertyCSSValueInternal(
    CSSPropertyID) {
  return nullptr;
}
String CSSComputedStyleDeclaration::GetPropertyValueInternal(CSSPropertyID) {
  return String();
}
String CSSComputedStyleDeclaration::GetPropertyValueWithHint(const String&,
                                                             unsigned) {
  return String();
}
String CSSComputedStyleDeclaration::GetPropertyPriorityWithHint(const String&,
                                                                unsigned) {
  return String();
}
void CSSComputedStyleDeclaration::SetPropertyInternal(CSSPropertyID,
                                                      const String&,
                                                      StringView,
                                                      bool,
                                                      SecureContextMode,
                                                      ExceptionState&) {}
bool CSSComputedStyleDeclaration::CssPropertyMatches(CSSPropertyID,
                                                     const CSSValue&) const {
  return false;
}
ScrollToOptions::ScrollToOptions() = default;
void ScrollToOptions::Trace(Visitor*) const {}
V8FrameCallback::V8FrameCallback(V8FrameRequestCallback*) {}
void V8FrameCallback::Trace(Visitor*) const {}
void V8FrameCallback::Invoke(double) {}
CustomElementRegistry::CustomElementRegistry(const LocalDOMWindow*) {}
void CustomElementRegistry::AssociatedWith(Document&) {}
LocalDOMWindow* EnteredDOMWindow(v8::Isolate*) {
  return nullptr;
}
LocalDOMWindow* ToLocalDOMWindow(const ScriptState*) {
  return nullptr;
}
bool BindingSecurity::ShouldAllowAccessTo(const LocalDOMWindow*,
                                          const DOMWindow*) {
  return true;
}
WebWindowFeatures GetWindowFeaturesFromString(const String&,
                                              LocalDOMWindow*) {
  return WebWindowFeatures();
}
FrameAdEvidence::FrameAdEvidence(bool parent_is_ad)
    : parent_is_ad_(parent_is_ad) {}
FrameAdEvidence::FrameAdEvidence(const FrameAdEvidence& other) = default;
FrameAdEvidence::~FrameAdEvidence() = default;
bool FrameAdEvidence::IndicatesAdFrame() const {
  return parent_is_ad_;
}
void FrameAdEvidence::UpdateFilterListResult(mojom::FilterListResult value) {
  latest_filter_list_result_ = value;
  most_restrictive_filter_list_result_ = value;
}
UserActivationState::UserActivationState()
    : first_notification_type_(mojom::UserActivationNotificationType::kNone),
      last_notification_type_(mojom::UserActivationNotificationType::kNone) {}
bool UserActivationState::HasBeenActive() const {
  return has_been_active_;
}
bool UserActivationState::IsActive() const {
  return false;
}
bool UserActivationState::LastActivationWasRestricted() const {
  return false;
}
bool UserActivationState::ConsumeIfActive() {
  return false;
}

ParkableString::ParkableString(scoped_refptr<StringImpl>&& impl)
    : impl_(nullptr) {}
ParkableString::ParkableString(scoped_refptr<StringImpl>&& impl,
                               std::unique_ptr<SecureStringDigest>)
    : impl_(nullptr) {}
ParkableString::~ParkableString() = default;
ParkableStringImpl::~ParkableStringImpl() = default;
void ParkableStringImpl::ReleaseAndRemoveIfNeeded() const {}

void ElementIntersectionObserverData::TrackWithController(
    IntersectionObserverController&) {}
void DisplayLockContext::ElementConnected() {}
void DisplayLockContext::ElementDisconnected() {}
void DisplayAdElementMonitor::EnsureStarted() {}
void DisplayAdElementMonitor::OnElementRemoved() {}
void CustomElement::EnqueueConnectedMoveCallback(Element&) {}
void CustomElement::TryToUpgrade(Element&) {}
void CustomElement::EnqueueConnectedCallback(Element&) {}
void CustomElement::EnqueueDisconnectedCallback(Element&) {}
ExecutionContext* EditContext::GetExecutionContext() const { return nullptr; }
void EditContext::SetExecutionContext(ExecutionContext*) {}
void PointerLockController::ElementRemoved(Element*) {}
Element* PointerLockController::GetElement() const {
  return nullptr;
}
void Fullscreen::ElementRemoved(Element&) {}
Element* Fullscreen::FullscreenElementFrom(Document&) {
  return nullptr;
}
bool Fullscreen::HasFullscreenElements() {
  return false;
}
void CSSAnimations::Cancel() {}
void CSSAnimations::MaybeApplyPendingUpdate(Element*) {}
void Editor::ElementRemoved(Element*) {}
void SpellChecker::ElementRemoved(Element*) {}
void SpellChecker::RemoveSpellingMarkersUnderWords(const Vector<String>&) {}
SpellChecker::SpellChecker(LocalDOMWindow& window)
    : window_(&window),
      spell_check_requester_(nullptr),
      idle_spell_check_controller_(nullptr) {}
void SpellChecker::Trace(Visitor*) const {}
InputMethodController::InputMethodController(LocalDOMWindow& window,
                                             LocalFrame& frame)
    : ExecutionContextLifecycleObserver(&window),
      frame_(&frame),
      has_composition_(false),
      last_vk_visibility_request_(
          ui::mojom::VirtualKeyboardVisibilityRequest::NONE) {}
InputMethodController::~InputMethodController() = default;
void InputMethodController::Trace(Visitor*) const {}
void InputMethodController::ContextDestroyed() {}
void InputMethodController::DidChangeVisibility(const LayoutObject&) {}
TextSuggestionController::TextSuggestionController(LocalDOMWindow& window)
    : is_suggestion_menu_open_(false),
      window_(&window),
      text_suggestion_host_(&window) {}
void TextSuggestionController::Trace(Visitor*) const {}
void EventHandler::ElementRemoved(Element*) {}
void EventHandler::ScheduleCursorUpdate() {}
void MouseEventManager::HandlePseudoElementRemoval(PseudoElement&) {}
void PointerEventManager::HandlePseudoElementRemoval(PseudoElement&) {}
void OverscrollAreaTracker::RemoveOverscroll(Element*) {}

void StyleAdjuster::AdjustStyleForDisplay(ComputedStyleBuilder&,
                                          const ComputedStyle&,
                                          const Element*,
                                          Document*) {}

StyleRecalcContext StyleRecalcContext::FromParentContext(
    const StyleRecalcContext&,
    Element&) {
  return StyleRecalcContext();
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
ListItemOrdinal* ListItemOrdinal::Get(const Node&) { return nullptr; }
std::optional<int> ListItemOrdinal::ExplicitValue() const {
  return std::nullopt;
}
bool ListItemOrdinal::IsInReversedOrderedList(const Node&) { return false; }
#endif

HTMLDocument::HTMLDocument(const DocumentInit& initializer,
                           DocumentClassFlags extended_document_classes)
    : Document(initializer,
               base::Union(DocumentClassFlags({DocumentClass::kHTML}),
                           extended_document_classes)) {
}
HTMLDocument::~HTMLDocument() = default;
bool HTMLDocument::IsCaseSensitiveAttribute(const QualifiedName&) {
  return false;
}
void HTMLDocument::RemoveNamedItem(const AtomicString&) {}
void HTMLDocument::AddNamedItem(const AtomicString&) {}

void ScriptPromiseResolverBase::Reject(v8::Local<v8::Value>) {}
ScriptPromiseResolverBase::ScriptPromiseResolverBase(
    ScriptState* script_state,
    const ExceptionContext& exception_context)
    : resolver_(),
      state_(kPending),
      script_state_(script_state),
      value_(),
      exception_context_(exception_context) {}
ScriptPromiseResolverBase::~ScriptPromiseResolverBase() = default;
#if DCHECK_IS_ON()
void ScriptPromiseResolverBase::Dispose() {}
#endif
void ScriptPromiseResolverBase::Trace(Visitor*) const {}
ExecutionContext* ScriptPromiseResolverBase::GetExecutionContext() {
  return nullptr;
}
void ScriptPromiseResolverBase::NotifyResolveOrReject() {}
KURL::KURL()
    : is_valid_(false),
      protocol_is_in_http_family_(false),
      parsed_(),
      string_(g_empty_atom) {}
KURL::KURL(const StringView& string)
    : is_valid_(!string.IsNull()),
      protocol_is_in_http_family_(false),
      parsed_(),
      string_(AtomicString(string.ToString())) {}
KURL::KURL(const KURL& other)
    : is_valid_(other.is_valid_),
      protocol_is_in_http_family_(other.protocol_is_in_http_family_),
      protocol_(other.protocol_),
      parsed_(other.parsed_),
      string_(other.string_) {
  if (other.inner_url_) {
    inner_url_ = std::make_unique<KURL>(*other.inner_url_);
  }
}
KURL::~KURL() = default;
KURL& KURL::operator=(const KURL& other) {
  if (this == &other) {
    return *this;
  }
  is_valid_ = other.is_valid_;
  protocol_is_in_http_family_ = other.protocol_is_in_http_family_;
  protocol_ = other.protocol_;
  parsed_ = other.parsed_;
  string_ = other.string_;
  inner_url_.reset();
  if (other.inner_url_) {
    inner_url_ = std::make_unique<KURL>(*other.inner_url_);
  }
  return *this;
}
KURL::KURL(const KURL&, const StringView& relative, const TextEncoding&)
    : KURL(relative) {}
void KURL::WriteIntoTrace(perfetto::TracedValue) const {}
const AtomicString& HTMLLinkElement::GetType() const {
  return g_empty_atom;
}
const AtomicString& HTMLLinkElement::Rel() const {
  return g_empty_atom;
}
KURL HTMLLinkElement::Href() const {
  return KURL();
}
void RenderBlockingResourceManager::ClearPendingParsingElements() {}
void DocumentParserTiming::MarkParserStop() {}
void DocumentTiming::MarkDomContentLoadedEventStart() {}
void DocumentTiming::MarkDomContentLoadedEventEnd() {}
void DocumentTiming::Trace(Visitor*) const {}
namespace scheduler {
void EventLoop::PerformMicrotaskCheckpoint() {}
std::unique_ptr<EventLoop::PauseMicrotasksHandle> EventLoop::PauseMicrotasks() {
  return nullptr;
}
EventLoop::PauseMicrotasksHandle::~PauseMicrotasksHandle() = default;
}  // namespace scheduler
NonMainThread* Thread::CompositorThread() {
  return nullptr;
}
namespace network_utils {
String GetDomainAndRegistry(const StringView&, PrivateRegistryFilter) {
  return String();
}
}  // namespace network_utils
bool IsInflightNetworkRequestBackForwardCacheSupportEnabled() {
  return false;
}
ModelContext* ModelContextSupplement::modelContext(Navigator&) {
  return nullptr;
}
WebFrame* WebFrame::FromCoreFrame(Frame*) {
  return nullptr;
}
void ModelContext::DidFinishParsing() {}
void IdlenessDetector::DomContentLoadedEventFired() {}
void FontPerformance::MarkDomContentLoaded() {}
void FrameLoader::FinishedParsing() {}
void ResourceFetcher::ClearPreloads(ClearPreloadsPolicy) {}
void DocumentLoader::ReportTotalTakenTimeToUpdateSubresourceLoadMetrics() {}
IconURL IconURL::DefaultFavicon(const KURL&) {
  return IconURL(KURL(), Vector<gfx::Size>(), String(),
                 mojom::blink::FaviconIconType::kFavicon);
}
mojom::blink::FaviconIconType HTMLLinkElement::GetIconType() const {
  return mojom::blink::FaviconIconType::kFavicon;
}
bool MediaQueryList::matches() {
  return false;
}
const Vector<gfx::Size>& HTMLLinkElement::IconSizes() const {
  static const Vector<gfx::Size> sizes;
  return sizes;
}
const AtomicString& HTMLMetaElement::Media() const {
  return g_empty_atom;
}
const AtomicString& HTMLMetaElement::Content() const {
  return g_empty_atom;
}
ContentSecurityPolicy*
ExecutionContext::GetContentSecurityPolicyForCurrentWorld() {
  return GetContentSecurityPolicy();
}
IntersectionObserverController::IntersectionObserverController(
    ExecutionContext* context)
    : ExecutionContextClient(context) {}
ElementIntersectionObserverData::ElementIntersectionObserverData() = default;
ScriptRegexp* EmailInputType::CreateEmailRegexp(v8::Isolate*) {
  return nullptr;
}
void DisplayLockDocumentState::ElementAddedToTopLayer(Element*) {}
void DisplayLockDocumentState::ElementRemovedFromTopLayer(Element*) {}
void PointerLockController::ExitPointerLock() {}
bool PointerLockController::LockPending() const {
  return false;
}
int ScriptedAnimationController::RegisterFrameCallback(FrameCallback*) {
  return 0;
}
void ScriptedAnimationController::CancelFrameCallback(int) {}
std::unique_ptr<Locale> Locale::Create(const String&) {
  return nullptr;
}
Locale& Locale::DefaultLocale() {
  return *reinterpret_cast<Locale*>(new char[sizeof(void*)]);
}
bool HTMLObjectElement::DidFinishLoading() const {
  return false;
}
FontFaceSetDocument* FontFaceSetDocument::From(Document&) {
  return nullptr;
}
std::unique_ptr<DocumentResourceCoordinator>
DocumentResourceCoordinator::MaybeCreate(const BrowserInterfaceBrokerProxy&) {
  return nullptr;
}
DOMFeaturePolicy::DOMFeaturePolicy(ExecutionContext*) {}
void LiveNodeListRegistry::Trace(Visitor*) const {}
bool Frame::IsDescendantOf(const Frame*) const {
  return false;
}
void ProgressTracker::ProgressStarted() {}
BeforeUnloadEventListener::BeforeUnloadEventListener(Document* document)
    : doc_(document), show_dialog_(false) {}
void BeforeUnloadEventListener::Trace(Visitor* visitor) const {
  NativeEventListener::Trace(visitor);
  visitor->Trace(doc_);
}
void BeforeUnloadEventListener::Invoke(ExecutionContext*, Event*) {}
void DocumentLoader::NotifyPrerenderingDocumentActivated(
    const mojom::blink::PrerenderPageActivationParams&) {}
void HTMLDialogElement::Trace(Visitor* visitor) const {
  HTMLElement::Trace(visitor);
}
Vector<AtomicString>& CustomElement::EmbedderCustomElementNames() {
  static Vector<AtomicString> names;
  return names;
}
bool CustomElement::IsHyphenatedSpecElementName(const AtomicString&) {
  return false;
}
namespace inspector_recalculate_styles_event {
void Data(perfetto::TracedValue, LocalFrame*) {}
}  // namespace inspector_recalculate_styles_event
namespace inspector_invalidate_layout_event {
void Data(perfetto::TracedValue, LocalFrame*, int) {}
}  // namespace inspector_invalidate_layout_event
namespace inspector_layout_event {
void BeginData(perfetto::TracedValue, LocalFrameView*) {}
void EndData(perfetto::TracedValue,
             const HeapVector<LayoutObjectWithDepth>&) {}
}  // namespace inspector_layout_event
namespace inspector_pre_paint_event {
void Data(perfetto::TracedValue, LocalFrame*) {}
}  // namespace inspector_pre_paint_event
namespace inspector_layerize_event {
void Data(perfetto::TracedValue, LocalFrame*) {}
}  // namespace inspector_layerize_event
namespace inspector_set_layer_tree_id {
void Data(perfetto::TracedValue, LocalFrame*) {}
}  // namespace inspector_set_layer_tree_id
namespace inspector_dom_stats {
void Data(perfetto::TracedValue, LocalFrame*) {}
}  // namespace inspector_dom_stats

VisitedLinkState::VisitedLinkState(const Document& document)
    : document_(document) {}
void VisitedLinkState::Trace(Visitor* visitor) const {
  visitor->Trace(document_);
}
void DisplayLockContext::Trace(Visitor*) const {}
void DisplayLockContext::NotifyWillDisconnect() {}
void FrameViewAutoSizeInfo::Trace(Visitor*) const {}
bool FrameViewAutoSizeInfo::AutoSizeIfNeeded() {
  return false;
}
void FrameViewAutoSizeInfo::Clear() {}
void WebPluginContainerImpl::Trace(Visitor*) const {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void TransformPaintPropertyNode::State::Trace(Visitor*) const {}
#endif
void PaintArtifactCompositor::Trace(Visitor*) const {}
void MobileFriendlinessChecker::Trace(Visitor*) const {}
void TapFriendlinessChecker::Trace(Visitor*) const {}
void ScrollMarkerGroupPseudoElement::Trace(Visitor*) const {}
bool RenderBlockingElementLinkMap::HasElement(RenderBlockingLevel) const {
  return false;
}
void HttpRefreshScheduler::Trace(Visitor*) const {}
void DocumentMarkerController::Trace(Visitor*) const {}
void ScriptRunner::Trace(Visitor*) const {}
void ScriptRunnerDelayer::Trace(Visitor*) const {}
void DisplayLockDocumentState::Trace(Visitor*) const {}
void RenderBlockingResourceManager::Trace(Visitor*) const {}
void CookieJar::Trace(Visitor*) const {}
ResourceFetcher::~ResourceFetcher() = default;
void ResourceFetcher::Trace(Visitor*) const {}
void RootScrollerController::Trace(Visitor*) const {}
void RootScrollerController::ElementRemoved(const Element&) {}
MediaQueryMatcher::~MediaQueryMatcher() = default;
void MediaQueryMatcher::Trace(Visitor*) const {}
void MediaQueryMatcher::ViewportChanged() {}
void MediaQueryMatcher::DynamicViewportChanged() {}
MediaQueryList* MediaQueryMatcher::MatchMedia(const String&) {
  return nullptr;
}
AXContext::AXContext(Document& document, const ui::AXMode& mode)
    : document_(document), ax_mode_(mode) {}
AXContext::~AXContext() = default;
AXObjectCache& AXContext::GetAXObjectCache() {
  return *static_cast<AXObjectCache*>(nullptr);
}
ShareableElementData* ElementDataCache::CachedShareableElementDataWithAttributes(
    const StringImpl*,
    const Vector<Attribute, kAttributePrealloc>&) {
  return nullptr;
}
void SVGUseElement::Trace(Visitor* visitor) const {
  SVGGraphicsElement::Trace(visitor);
}
void ViewTransition::SkipTransition(PromiseResponse) {}
CanvasFontCache::~CanvasFontCache() = default;
void CanvasFontCache::Trace(Visitor*) const {}
void ElementDataCache::Trace(Visitor*) const {}
void V8UnionStringOrTrustedHTML::Trace(Visitor* visitor) const {
  visitor->Trace(member_trusted_html_);
}
void ViewTransitionSupplement::Trace(Visitor*) const {}
void HTMLImageElement::OnResize() {}
void NodeIterator::Trace(Visitor*) const {}
void Range::Trace(Visitor*) const {}
SVGDocumentExtensions::~SVGDocumentExtensions() = default;
void SVGDocumentExtensions::Trace(Visitor*) const {}
HTMLAllCollection::HTMLAllCollection(ContainerNode& node, CollectionType type)
    : HTMLCollection(node, type) {}
HTMLAllCollection::~HTMLAllCollection() = default;
void ElementIntersectionObserverData::Trace(Visitor*) const {}
void LazyLoadMediaObserver::Trace(Visitor*) const {}
void ResizeObserver::Trace(Visitor*) const {}
void PendingLinkPreload::UnblockRendering() {}
void PendingLinkPreload::Dispose() {}
void PendingLinkPreload::AddResource(Resource*) {}
PendingLinkPreload::~PendingLinkPreload() = default;
void MenuSafeTriangle::Trace(Visitor*) const {}
bool DocumentLayoutUpgrade::ShouldUpgrade() {
  return false;
}
bool ParentLayoutUpgrade::ShouldUpgrade() {
  return false;
}
bool ElementLayoutUpgrade::ShouldUpgrade() {
  return false;
}
void DetachableResourceFetcherProperties::Trace(Visitor*) const {}
DOMRectReadOnly::DOMRectReadOnly(double x,
                                 double y,
                                 double width,
                                 double height)
    : x_(x), y_(y), width_(width), height_(height) {}
void SVGGraphicsElement::Trace(Visitor* visitor) const {
  SVGElement::Trace(visitor);
}
std::unique_ptr<TracedValue> TracedLayoutObject::Create(const LayoutView&,
                                                        bool) {
  return nullptr;
}
ScrollOptions::ScrollOptions() = default;
const char* const V8ScrollContainer::string_table_[] = {"all", "nearest"};
const char* const V8ScrollBehavior::string_table_[] = {"auto", "instant",
                                                       "smooth"};
void ScrollIntoViewOptions::Trace(Visitor*) const {}
void ScrollOptions::Trace(Visitor*) const {}
IntersectionObserverController::~IntersectionObserverController() = default;
void IntersectionObserverController::Trace(Visitor* visitor) const {
  ExecutionContextClient::Trace(visitor);
}
void IntersectionObserverController::ComputeIntersections(
    unsigned,
    LocalFrameView&,
    gfx::Vector2dF,
    ComputeIntersectionsContext&) {}
void IntersectionObserverController::DeliverNotifications(
    IntersectionObserver::DeliveryBehavior) {}
void IntersectionObserverController::UpdateIntersectionObserverStatus() {}
void DOMFeaturePolicy::Trace(Visitor* visitor) const {
}
void SVGElement::Trace(Visitor*) const {}
void MediaQueryMatcher::MediaFeaturesChanged() {}
HTMLResourcePreloader::HTMLResourcePreloader(Document& document)
    : document_(document) {}
void HTMLResourcePreloader::Trace(Visitor* visitor) const {
  visitor->Trace(document_);
}
bool HTMLResourcePreloader::ShouldPreload(
    const Document*,
    ResourceType,
    bool,
    FetchParameters::DeferOption,
    mojom::blink::FetchPriorityHint) {
  return false;
}
void HTMLResourcePreloader::Preload(std::unique_ptr<PreloadRequest>) {}
void ResourcePreloader::TakeAndPreload(PreloadRequestStream& requests) {
  requests.clear();
}
std::unique_ptr<HTMLPreloadScanner> HTMLPreloadScanner::Create(
    Document&,
    HTMLParserOptions,
    TokenPreloadScanner::ScannerType) {
  return std::unique_ptr<HTMLPreloadScanner>(new HTMLPreloadScanner());
}
HTMLPreloadScanner::BackgroundPtr HTMLPreloadScanner::CreateBackground(
    HTMLDocumentParser*,
    HTMLParserOptions,
    scoped_refptr<base::SequencedTaskRunner> task_runner,
    TakePreloadFn) {
  return BackgroundPtr(nullptr, Deleter{std::move(task_runner)});
}
std::unique_ptr<BackgroundHTMLScanner::ScriptTokenScanner>
BackgroundHTMLScanner::ScriptTokenScanner::Create(ScriptableDocumentParser*) {
  return nullptr;
}
SequenceBound<BackgroundHTMLScanner> BackgroundHTMLScanner::Create(
    const HTMLParserOptions&,
    ScriptableDocumentParser*) {
  return SequenceBound<BackgroundHTMLScanner>();
}
BackgroundHTMLScanner::~BackgroundHTMLScanner() = default;
void BackgroundHTMLScanner::Scan(const String&) {}
HTMLPreloadScanner::~HTMLPreloadScanner() = default;
void HTMLPreloadScanner::AppendToEnd(const SegmentedString&) {}
std::unique_ptr<PendingPreloadData> HTMLPreloadScanner::Scan(const KURL&) {
  return std::make_unique<PendingPreloadData>();
}
void HTMLPreloadScanner::ScanInBackground(const String&, const KURL&) {}
base::WeakPtr<HTMLPreloadScanner> HTMLPreloadScanner::AsWeakPtr() {
  return weak_ptr_factory_.GetWeakPtr();
}
HTMLParserScriptRunner::HTMLParserScriptRunner(
    HTMLParserReentryPermit* reentry_permit,
    Document* document,
    HTMLParserScriptRunnerHost* host)
    : reentry_permit_(reentry_permit), document_(document), host_(host) {}
HTMLParserScriptRunner::~HTMLParserScriptRunner() = default;
void HTMLParserScriptRunner::Detach() {
  parser_blocking_script_ = nullptr;
  scripts_to_execute_after_parsing_.clear();
  host_ = nullptr;
  document_ = nullptr;
}
void HTMLParserScriptRunner::ProcessScriptElement(Element*, const TextPosition&) {}
void HTMLParserScriptRunner::ExecuteScriptsWaitingForLoad() {}
void HTMLParserScriptRunner::ExecuteScriptsWaitingForResources() {}
bool HTMLParserScriptRunner::ExecuteScriptsWaitingForParsing() {
  return false;
}
bool HTMLParserScriptRunner::HasParserBlockingScript() const {
  return false;
}
void HTMLParserScriptRunner::Trace(Visitor* visitor) const {
  visitor->Trace(reentry_permit_);
  visitor->Trace(document_);
  visitor->Trace(host_);
  visitor->Trace(parser_blocking_script_);
  visitor->Trace(scripts_to_execute_after_parsing_);
}
void HTMLParserScriptRunner::UnblockForPrerenderActivation() {}
void HTMLParserScriptRunner::PendingScriptFinished(PendingScript*) {}
void HTMLParserScriptRunner::ExecutePendingParserBlockingScriptAndDispatchEvent() {}
void HTMLParserScriptRunner::ExecutePendingDeferredScriptAndDispatchEvent(
    PendingScript*) {}
void HTMLParserScriptRunner::ExecuteParsingBlockingScripts() {}
void HTMLParserScriptRunner::ProcessScriptElementInternal(
    Element*,
    const TextPosition&) {}
bool HTMLParserScriptRunner::IsParserBlockingScriptReady() {
  return false;
}
PendingScript* HTMLParserScriptRunner::TryTakeReadyScriptWaitingForParsing(
    HeapDeque<Member<PendingScript>>*) {
  return nullptr;
}
Document* HTMLDocument::CloneDocumentWithoutChildren() const {
  return MakeGarbageCollected<HTMLDocument>(
      DocumentInit::Create()
          .WithExecutionContext(GetExecutionContext())
          .WithAgent(GetAgent())
          .WithURL(Url()));
}
DisplayLockUtilities::ScopedForcedUpdate::Impl::Impl(
    const Node* node,
    DisplayLockContext::ForcedPhase phase,
    bool,
    bool only_cv_auto,
    bool emit_warnings)
    : node_(node),
      phase_(phase),
      only_cv_auto_(only_cv_auto),
      emit_warnings_(emit_warnings) {}
DisplayLockUtilities::ScopedForcedUpdate::Impl::Impl(
    const Range* range,
    DisplayLockContext::ForcedPhase phase,
    bool only_cv_auto,
    bool emit_warnings)
    : node_(range ? &range->OwnerDocument() : nullptr),
      phase_(phase),
      only_cv_auto_(only_cv_auto),
      emit_warnings_(emit_warnings) {}
void DisplayLockUtilities::ScopedForcedUpdate::Impl::
    AddForcedUpdateScopeForContext(DisplayLockContext*) {}
void DisplayLockUtilities::ScopedForcedUpdate::Impl::EnsureMinimumForcedPhase(
    DisplayLockContext::ForcedPhase phase) {
  phase_ = phase;
}
void DisplayLockUtilities::ScopedForcedUpdate::Impl::Destroy() {}
DocumentEncodingData::DocumentEncodingData(const TextResourceDecoder&)
    : DocumentEncodingData() {}
HTMLParserMetrics::HTMLParserMetrics(int64_t source_id, ukm::UkmRecorder* recorder)
    : source_id_(source_id), recorder_(recorder) {}
void HTMLParserMetrics::AddChunk(base::TimeDelta, unsigned tokens_parsed) {
  ++chunk_count_;
  total_tokens_parsed_ += tokens_parsed;
}
void HTMLParserMetrics::AddYieldInterval(base::TimeDelta) {}
void HTMLParserMetrics::AddInput(unsigned length) {
  input_character_count_ += length;
}
void HTMLParserMetrics::AddFetchQueuedPreloadsTime(int64_t elapsed_time) {
  fetch_queued_preloads_time_ += elapsed_time;
}
void HTMLParserMetrics::AddPreloadTime(int64_t elapsed_time) {
  preload_time_ += elapsed_time;
}
void HTMLParserMetrics::AddPrepareToStopParsingTime(int64_t elapsed_time) {
  prepare_to_stop_parsing_time_ += elapsed_time;
}
void HTMLParserMetrics::AddPumpTokenizerTime(int64_t elapsed_time) {
  pump_tokenizer_time_ += elapsed_time;
}
void HTMLParserMetrics::AddScanAndPreloadTime(int64_t elapsed_time) {
  scan_and_preload_time_ += elapsed_time;
}
void HTMLParserMetrics::AddScanTime(int64_t elapsed_time) {
  scan_time_ += elapsed_time;
}
void HTMLParserMetrics::ReportMetricsAtParseEnd() {}
void HTMLParserMetrics::ReportUMAs() {}
bool ExecutionContext::IsFeatureEnabled(
    mojom::blink::DocumentPolicyFeature) const {
  return false;
}
void DocumentLoader::DidObserveLoadingBehavior(LoadingBehaviorFlag) {}
void DocumentLoader::DispatchLcppFontPreloads(
    const ViewportDescription*,
    PreloadHelper::LoadLinksFromHeaderMode) {}
PrefetchedSignedExchangeManager*
DocumentLoader::GetPrefetchedSignedExchangeManager() const {
  return nullptr;
}
void HTMLMetaElement::ProcessMetaCH(Document&,
                                    const AtomicString&,
                                    network::MetaCHType,
                                    bool,
                                    bool) {}
const Vector<network::mojom::blink::ContentSecurityPolicyPtr>&
ContentSecurityPolicy::GetParsedPolicies() const {
  static const Vector<network::mojom::blink::ContentSecurityPolicyPtr> policies;
  return policies;
}
InlineScriptStreamer* InlineScriptStreamer::From(
    scoped_refptr<BackgroundInlineScriptStreamer>) {
  return nullptr;
}
ThreadCreationParams::ThreadCreationParams(ThreadType type)
    : thread_type(type), name(nullptr), frame_or_worker_scheduler(nullptr) {}
ThreadCreationParams& ThreadCreationParams::SetSupportsGC(bool supports_gc_value) {
  supports_gc = supports_gc_value;
  return *this;
}
std::unique_ptr<NonMainThread> NonMainThread::CreateThread(
    const ThreadCreationParams&) {
  return nullptr;
}
Thread* Thread::Current() {
  return &StandaloneMainThread();
}
bool KURL::IsLocalFile() const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
gfx::RectF InlineCursorPosition::ObjectBoundingBox(
    const InlineCursor&) const {
  return gfx::RectF();
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalOffset FragmentItem::MapPointInContainer(
    const PhysicalOffset& point) const {
  return point;
}
#endif
void EventHandlerRegistry::DocumentDetached(Document&) {}
void FrameSelection::ContextDestroyed() {}
void ResourceFetcher::ClearContext() {}
int ResourceFetcher::BlockingRequestCount() const {
  return 0;
}
void ResourceFetcher::ScheduleWarnUnusedPreloads(
    base::OnceCallback<void(Vector<KURL>)>) {}
void ResourceFetcher::MaybeRecordLCPPSubresourceMetrics(const KURL&) {}
void MediaQueryMatcher::DocumentDetached() {}
SVGDocumentExtensions::SVGDocumentExtensions(Document*) {}
bool RuntimeEnabledFeaturesBase::AutofillEventEnabled(
    const FeatureContext*) {
  return false;
}
AXObjectCache* AXObjectCache::Create(Document&, const ui::AXMode&) {
  return nullptr;
}
CanvasFontCache::CanvasFontCache(Document&) {}
bool LazyImageHelper::LoadAllImagesAndBlockLoadEvent(Document&) {
  return false;
}
void DisplayLockDocumentState::NotifyPrintingOrPreviewChanged() {}
void CookieJar::InvalidateCache() {}
void KURL::SetFragmentIdentifier(const String&) {}
void DocumentLoader::DidOpenDocumentInputStream(const KURL&) {}
network::mojom::blink::WebSandboxFlags ExecutionContext::GetSandboxFlags()
    const {
  return network::mojom::blink::WebSandboxFlags::kNone;
}
void SecurityContext::SetSandboxFlags(
    network::mojom::blink::WebSandboxFlags) {}
void SecurityContext::SetSecurityOrigin(scoped_refptr<SecurityOrigin>) {}
void ExceptionState::ThrowSecurityError(const char*, const char*) {
  had_exception_ = true;
}
DocumentParserTiming& DocumentParserTiming::From(Document& document) {
  static Persistent<DocumentParserTiming> timing;
  if (!timing) {
    timing = MakeGarbageCollected<DocumentParserTiming>(document);
  }
  return *timing;
}
DocumentParserTiming::DocumentParserTiming(Document& document)
    : Supplement<Document>(document) {}
void DocumentParserTiming::MarkParserDetached() {}
void DocumentParserTiming::MarkParserStart() {}
std::unique_ptr<TextResourceDecoder> BuildTextResourceDecoder(
    LocalFrame*,
    const KURL&,
    const AtomicString&,
    const AtomicString&) {
  return nullptr;
}
String ExceptionMessages::ArgumentNullOrIncorrectType(int,
                                                      const String&) {
  return String();
}
void ResourceLoadScheduler::LoosenThrottlingPolicy() {}
void ViewTransitionSupplement::WillInsertBody() {}
void RenderBlockingResourceManager::WillInsertDocumentBody() {}
void FrameLoader::DidFinishNavigation(FrameLoader::NavigationFinishState) {}
void SVGDocumentExtensions::DispatchSVGLoadEventToOutermostSVGElements() {}
void SVGDocumentExtensions::StartAnimations() {}
void HttpRefreshScheduler::MaybeStartTimer() {}
void ViewportDescription::ReportMobilePageStats(const LocalFrame*) const {}
const KURL& DocumentLoader::Url() const {
  return BlankUrl();
}
void DetectJavascriptFrameworksOnLoad(Document&) {}
void LCPCriticalPathPredictor::OnOutermostMainFrameDocumentLoad() {}
void DocumentLoader::DispatchLinkHeaderPreloads(
    const ViewportDescription*,
    PreloadHelper::LoadLinksFromHeaderMode) {}
void LCPCriticalPathPredictor::OnWarnedUnusedPreloads(const Vector<KURL>&) {}
bool EventListenerMap::Contains(const AtomicString&) const {
  return false;
}
void ScriptedAnimationController::EnqueuePerFrameEvent(Event*) {}
void ScriptedAnimationController::EnqueueTask(base::OnceClosure) {}
void ScriptedAnimationController::EnqueueEvent(Event*) {}
void ScriptedAnimationController::EnqueueMediaQueryChangeListeners(
    HeapVector<Member<MediaQueryListListener>>&) {}
void ScriptedAnimationController::DispatchMediaQueryListEventsAndCallbacks() {}
VisualViewportResizeEvent::VisualViewportResizeEvent()
    : Event(AtomicString("resize"), Bubbles::kNo, Cancelable::kNo) {}
VisualViewportResizeEvent::~VisualViewportResizeEvent() = default;
void VisualViewportResizeEvent::DoneDispatchingEventAtCurrentTarget() {}
VisualViewportScrollEvent::VisualViewportScrollEvent()
    : Event(AtomicString("scroll"), Bubbles::kNo, Cancelable::kNo) {}
VisualViewportScrollEvent::~VisualViewportScrollEvent() = default;
void VisualViewportScrollEvent::DoneDispatchingEventAtCurrentTarget() {}
VisualViewportScrollEndEvent::VisualViewportScrollEndEvent()
    : Event(AtomicString("scrollend"), Bubbles::kNo, Cancelable::kNo) {}
VisualViewportScrollEndEvent::~VisualViewportScrollEndEvent() = default;
void VisualViewportScrollEndEvent::DoneDispatchingEventAtCurrentTarget() {}
void EventHandler::ScheduleHoverStateUpdate() {}
NodeChildRemovalTracker* NodeChildRemovalTracker::last_ = nullptr;
void DisplayLockUtilities::ElementLostFocus(Element*) {}
void DisplayLockUtilities::ElementGainedFocus(Element*) {}
void EditContext::Blur() {}
void EditContext::Focus() {}
bool IsRootEditableElement(const Node&) {
  return false;
}
bool IsEditable(const Node&) {
  return false;
}
bool IsRichlyEditable(const Node&) {
  return false;
}
Element* RootEditableElement(const Node&) {
  return nullptr;
}
void FrameSelection::DidChangeFocus() {}
bool FrameSelection::FrameIsFocusedAndActive() const {
  return false;
}
Element* FocusgroupControllerUtils::GetFocusgroupOwnerOfItem(
    const Element*) {
  return nullptr;
}
void Range::selectNodeContents(Node*, ExceptionState&) {}
bool Range::IsConnected() const {
  return false;
}
Node* Range::FirstNode() const {
  return nullptr;
}
void Range::UpdateOwnerDocumentIfNeeded() {}
void Range::NodeChildrenWillBeRemoved(ContainerNode&) {}
void Range::FixupRemovedChildrenAcrossShadowBoundary(ContainerNode&) {}
void Range::NodeWillBeRemoved(Node&) {}
void Range::FixupRemovedNodeAcrossShadowBoundary(Node&) {}
void Range::DidInsertText(const CharacterData&, unsigned, unsigned) {}
void Range::DidRemoveText(const CharacterData&, unsigned, unsigned) {}
void Range::DidMergeTextNodes(const NodeWithIndex&, unsigned) {}
void Range::DidSplitTextNode(const Text&) {}
void LiveNodeListRegistry::Add(const LiveNodeListBase*,
                               NodeListInvalidationType) {}
void LiveNodeListRegistry::Remove(const LiveNodeListBase*,
                                  NodeListInvalidationType) {}
void NodeIterator::NodeWillBeRemoved(Node&) {}
void FrameSelection::NodeChildrenWillBeRemoved(ContainerNode&) {}
void FrameSelection::NodeWillBeRemoved(Node&) {}
void FrameSelection::DidUpdateCharacterData(CharacterData*,
                                            unsigned,
                                            unsigned,
                                            unsigned) {}
void FrameSelection::DidChangeChildren(
    const ContainerNode::ChildrenChange&) {}
void FrameSelection::DidMergeTextNodes(const Text&,
                                       const NodeWithIndex&,
                                       unsigned) {}
void FrameSelection::DidSplitTextNode(const Text&) {}
void MouseEventManager::NodeChildrenWillBeRemoved(ContainerNode&) {}
void MouseEventManager::NodeWillBeRemoved(Node&) {}
void PointerEventManager::NodeChildrenWillBeRemoved(ContainerNode&) {}
void PointerEventManager::NodeWillBeRemoved(Node&) {}
void DragCaret::NodeChildrenWillBeRemoved(ContainerNode&) {}
void DragCaret::NodeWillBeRemoved(Node&) {}
void DocumentMarkerController::DidUpdateCharacterData(CharacterData*,
                                                      unsigned,
                                                      unsigned,
                                                      unsigned) {}
SnapEvent* SnapEvent::Create(const AtomicString& type,
                             Bubbles bubbles,
                             Member<Node> block_target,
                             Member<Node> inline_target) {
  return MakeGarbageCollected<SnapEvent>(type, bubbles, block_target,
                                         inline_target);
}
SnapEvent::SnapEvent(const AtomicString& type,
                     Bubbles bubbles,
                     Member<Node> block_target,
                     Member<Node> inline_target)
    : Event(type, bubbles, Cancelable::kNo),
      snap_target_block_(block_target),
      snap_target_inline_(inline_target) {}
OverscrollEventInit::OverscrollEventInit() = default;
void OverscrollEventInit::Trace(Visitor* visitor) const {
  EventInit::Trace(visitor);
}
OverscrollEvent::OverscrollEvent(const AtomicString& type,
                                 const OverscrollEventInit*)
    : Event(type, Bubbles::kNo, Cancelable::kNo),
      overscroll_target_(nullptr),
      overscrolling_(false) {}
OverscrollEvent::~OverscrollEvent() = default;
const AtomicString& OverscrollEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}
void OverscrollEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
  visitor->Trace(overscroll_target_);
}
Element* OverscrollEvent::overscrollTarget() const {
  return overscroll_target_.Get();
}
bool OverscrollEvent::overscrolling() const {
  return overscrolling_;
}
bool EventListenerMap::ContainsCapturing(const AtomicString&) const {
  return false;
}
void AuditsIssue::ReportDocumentCookiePerformanceIssue(ExecutionContext*) {}
String CookieJar::Cookies() {
  return String();
}
void CookieJar::SetCookie(const String&) {}
bool CookieJar::CookiesEnabled() {
  return false;
}
void CookieJar::SetCookieManager(
    mojo::PendingRemote<network::mojom::blink::RestrictedCookieManager>) {}
const AtomicString& DocumentLoader::GetReferrer() const {
  return g_empty_atom;
}
void ExceptionState::ThrowSecurityError(const String&, const String&) {
  had_exception_ = true;
}
void ScriptController::UpdateSecurityOrigin(const SecurityOrigin*) {}
EventInit::EventInit() = default;
void EventInit::Trace(Visitor*) const {}
const void* EventInit::TemplateKey() const {
  return nullptr;
}
void EventInit::FillTemplateProperties(Vector<std::string_view>&) const {}
v8::Local<v8::Object> EventInit::FillValues(
    ScriptState*,
    v8::Local<v8::DictionaryTemplate>) const {
  return v8::Local<v8::Object>();
}

V8UnionCSSStyleValueOrUndefined* StylePropertyMapReadOnlyMainThread::get(
    const ExecutionContext*,
    const String&,
    ExceptionState&) const {
  return nullptr;
}
CSSStyleValueVector StylePropertyMapReadOnlyMainThread::getAll(
    const ExecutionContext*,
    const String&,
    ExceptionState&) const {
  return {};
}
bool StylePropertyMapReadOnlyMainThread::has(const ExecutionContext*,
                                             const String&,
                                             ExceptionState&) const {
  return false;
}
StylePropertyMapReadOnlyMainThread::IterationSource*
StylePropertyMapReadOnlyMainThread::CreateIterationSource(ScriptState*) {
  return nullptr;
}
unsigned int ComputedStylePropertyMap::size() const {
  return 0;
}
const CSSValue* ComputedStylePropertyMap::GetProperty(CSSPropertyID) const {
  return nullptr;
}
const CSSValue* ComputedStylePropertyMap::GetCustomProperty(
    const AtomicString&) const {
  return nullptr;
}
void ComputedStylePropertyMap::ForEachProperty(IterationFunction) {}
String ComputedStylePropertyMap::SerializationForShorthand(
    const CSSProperty&) const {
  return String();
}
ScrollIntoViewOptions::ScrollIntoViewOptions() = default;
const char* const V8ScrollLogicalPosition::string_table_[] = {
    "start", "center", "end", "nearest"};
void ScrollMarkerGroupPseudoElement::PinSelectedMarker(
    ScrollMarkerPseudoElement*) {}
void ScrollMarkerGroupPseudoElement::UnPinSelectedMarker() {}
bool ScrollMarkerGroupPseudoElement::SelectedMarkerIsPinned() const {
  return false;
}
ScrollMarkerPseudoElement* ScrollMarkerGroupPseudoElement::Selected() const {
  return nullptr;
}
void InterestEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
  visitor->Trace(source_);
}
ErrorEvent::ErrorEvent(const String& message,
                       SourceLocation* location,
                       ScriptValue,
                       DOMWrapperWorld* world)
    : Event(event_type_names::kError, Bubbles::kNo, Cancelable::kNo),
      unsanitized_message_(message),
      sanitized_message_(message),
      location_(location),
      world_(world) {}
ErrorEvent::~ErrorEvent() = default;
const AtomicString& ErrorEvent::InterfaceName() const {
  return event_interface_names::kErrorEvent;
}
bool ErrorEvent::CanBeDispatchedInWorld(const DOMWrapperWorld&) const {
  return true;
}
bool ErrorEvent::IsErrorEvent() const {
  return true;
}
ScriptValue ErrorEvent::error(ScriptState*) const {
  return ScriptValue();
}
void ErrorEvent::SetUnsanitizedMessage(const String& message) {
  unsanitized_message_ = message;
}
void ErrorEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
  visitor->Trace(location_);
  visitor->Trace(world_);
}
void V8UnionCSSStyleValueOrUndefined::Trace(Visitor* visitor) const {
  visitor->Trace(member_css_style_value_);
}
void ScriptRegexp::Trace(Visitor*) const {}
NameNodeList::NameNodeList(ContainerNode& root,
                           CollectionType type,
                           const AtomicString& name)
    : LiveNodeList(root, type, kInvalidateOnNameAttrChange), name_(name) {}
ClassCollection::ClassCollection(ContainerNode& root,
                                 CollectionType type,
                                 const AtomicString& class_name)
    : HTMLCollection(root, type),
      class_names_(MakeGarbageCollected<SpaceSplitStringWrapper>(class_name)) {}
RadioNodeList::RadioNodeList(ContainerNode& root,
                             CollectionType type,
                             const AtomicString& name)
    : LiveNodeList(root, type, kInvalidateOnNameAttrChange), name_(name) {}

SetSelectionOptions::SetSelectionOptions() = default;
SetSelectionOptions::SetSelectionOptions(const SetSelectionOptions&) = default;
template <typename Strategy>
SelectionTemplate<Strategy>::SelectionTemplate() = default;
template <typename Strategy>
SelectionTemplate<Strategy>::SelectionTemplate(
    const SelectionTemplate& other) = default;
template <typename Strategy>
VisibleSelectionTemplate<Strategy>::VisibleSelectionTemplate()
    : affinity_(TextAffinity::kDownstream), anchor_is_first_(true) {}
template Element* VisibleSelectionTemplate<EditingStrategy>::RootEditableElement()
    const;
template SelectionTemplate<EditingStrategy>
VisibleSelectionTemplate<EditingStrategy>::AsSelection() const;
template class SelectionTemplate<EditingStrategy>;
template class VisibleSelectionTemplate<EditingStrategy>;

Range* Range::Create(Document& document) {
  return MakeGarbageCollected<Range>(document);
}
Range::Range(Document& document)
    : owner_document_(&document), start_(*owner_document_), end_(*owner_document_) {}
Range::Range(Document& document, const Position&, const Position&)
    : Range(document) {}

AbstractRange::AbstractRange() = default;
AbstractRange::~AbstractRange() = default;

NodeIteratorBase::NodeIteratorBase(Node* root_node,
                                   unsigned what_to_show,
                                   V8NodeFilter* filter)
    : root_(root_node), what_to_show_(what_to_show), filter_(filter) {}
void NodeIteratorBase::Trace(Visitor* visitor) const {
  visitor->Trace(root_);
  visitor->Trace(filter_);
}

NodeIterator::NodePointer::NodePointer() : is_pointer_before_node(false) {}
NodeIterator::NodePointer::NodePointer(Node* node_in, bool before)
    : node(node_in), is_pointer_before_node(before) {}
void NodeIterator::NodePointer::Clear() {
  node.Clear();
}
bool NodeIterator::NodePointer::MoveToNext(Node*) {
  return false;
}
bool NodeIterator::NodePointer::MoveToPrevious(Node*) {
  return false;
}
NodeIterator::NodeIterator(Node* root_node,
                           unsigned what_to_show,
                           V8NodeFilter* filter)
    : NodeIteratorBase(root_node, what_to_show, filter),
      reference_node_(root_node, true) {}

TreeWalker::TreeWalker(Node* root_node,
                       unsigned what_to_show,
                       V8NodeFilter* filter)
    : NodeIteratorBase(root_node, what_to_show, filter), current_(root_node) {}
void TreeWalker::Trace(Visitor*) const {}

bool DocumentAnimations::NeedsAnimationTimingUpdate() {
  return false;
}
void DocumentAnimations::UpdateAnimationTimingIfNeeded() {}
void DocumentAnimations::DetachCompositorTimelines() {}
void DocumentAnimations::DetachCompositorTriggers() {}
CompositorAnimations::FailureReasons Animation::CheckCanStartAnimationOnCompositor(
    const PaintArtifactCompositor*,
    StartOnCompositorReason,
    PropertyHandleSet*) const {
  return CompositorAnimations::kInvalidAnimationOrEffect;
}
void Animation::OnPaintWorkletImageCreated() {}

void FrameSelection::MarkCacheDirty() {}
void DisplayLockDocumentState::EnsureMinimumForcedPhase(
    DisplayLockContext::ForcedPhase) {}
bool RuntimeEnabledFeaturesBase::is_update_complex_safa_area_constraints_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_html_interest_for_interest_button_pseudo_enabled_ =
    false;
unsigned FontPerformance::in_style_ = 0;
void DocumentSpeculationRules::DocumentStyleUpdated() {}
void DocumentSpeculationRules::DocumentBaseTargetChanged() {}
void DocumentSpeculationRules::DocumentBaseURLChanged() {}
void DocumentSpeculationRules::LinkGainedOrLostComputedStyle(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::LinkMatchedSelectorsUpdated(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::ChildStyleRecalcBlocked(Element*) {}
void DocumentSpeculationRules::DidStyleChildren(Element*) {}
void ScriptLoader::DocumentBaseURLChanged() {}
const AtomicString& HTMLMetaElement::GetName() const {
  return g_null_atom;
}
ShadowRoot* HTMLInputElement::EnsureShadowSubtree() {
  return nullptr;
}
void HTMLInputElement::EndEditing() {}
void SVGUseElement::BuildPendingResource() {}
void SVGResource::NotifyContentChanged() {}
Element* DisplayLockUtilities::LockedAncestorPreventingStyle(const Node&) {
  return nullptr;
}
bool DisplayLockUtilities::IsUnlockedQuickCheck(const Node&) {
  return true;
}
void DisplayLockContext::DetachLayoutTree() {}
void DisplayLockContext::SetRequestedState(EContentVisibility) {}
const ComputedStyle* DisplayLockContext::AdjustElementStyle(
    const ComputedStyle* style) const {
  return style;
}
void DisplayLockContext::DidStyleSelf() {}
void DisplayLockContext::DidStyleChildren() {}
bool HTMLMenuItemElement::ShouldHaveExpandIcon() const {
  return false;
}
bool FrameLoader::NeedsHistoryItemRestore(WebFrameLoadType) {
  return false;
}
void FrameLoader::SaveScrollAnchor() {}
void PaintLayerScrollableArea::ApplyPendingHistoryRestoreScrollOffset() {}
PhysicalSize PaintLayerScrollableArea::Size() const {
  return PhysicalSize();
}
LayoutBox* Scrollbar::GetLayoutBox() const {
  return nullptr;
}
bool Scrollbar::IsScrollCornerVisible() const {
  return false;
}
gfx::Rect PaintLayerScrollableArea::ResizerCornerRect(
    ResizerHitTestType) const {
  return gfx::Rect();
}
bool PaintLayerScrollableArea::NeedsScrollCorner() const {
  return false;
}
bool PaintLayerScrollableArea::MayCompositeScrollbar(const Scrollbar&) const {
  return false;
}
gfx::Rect PaintLayerScrollableArea::ScrollingBackgroundVisualRect(
    const PhysicalOffset&) const {
  return gfx::Rect();
}
void DocumentMarkerController::InvalidateRectsForAllTextMatchMarkers() {}
void DocumentMarkerController::PrepareForDestruction() {}
void SVGDocumentExtensions::PauseAnimations() {}
void HttpRefreshScheduler::Cancel() {}
HttpRefreshScheduler::HttpRefreshScheduler(Document* document)
    : document_(document) {}
DocumentMarkerController::DocumentMarkerController(Document& document)
    : document_(document) {}
bool DocumentMarkerController::PossiblyHasTextMatchMarkers() const {
  return false;
}
Vector<gfx::Rect> DocumentMarkerController::LayoutRectsForTextMatchMarkers() {
  return Vector<gfx::Rect>();
}
void DocumentMarkerController::StartGlicMarkerAnimationIfNeeded() {}
WebPrintPageDescription GetPageDescriptionFromLayout(const Document&, unsigned) {
  return WebPrintPageDescription();
}
PageDismissalScope::PageDismissalScope() = default;
PageDismissalScope::~PageDismissalScope() {}
BeforeUnloadEvent::BeforeUnloadEvent() = default;
BeforeUnloadEvent::~BeforeUnloadEvent() = default;
bool BeforeUnloadEvent::IsBeforeUnloadEvent() const {
  return true;
}
void BeforeUnloadEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
}
void Intervention::GenerateReport(LocalFrame*, const String&, const String&) {}
AutofillEvent* AutofillEvent::Create(
    const AtomicString& type,
    HeapVector<std::pair<Member<Element>, String>> field_data,
    const base::UnguessableToken& fill_id,
    bool supports_refill) {
  return MakeGarbageCollected<AutofillEvent>(
      type, std::move(field_data), fill_id, supports_refill);
}
void PerformanceMonitor::ReportGenericViolation(ExecutionContext*,
                                                PerformanceMonitor::Violation,
                                                const String&,
                                                base::TimeDelta,
                                                SourceLocation*) {}
String TrustedTypesCheckForHTML(const String& string,
                                const ExecutionContext*,
                                const AtomicString&,
                                const AtomicString&,
                                ExceptionState&) {
  return string;
}
const String& TrustedHTML::toString() const {
  return html_;
}
bool ContentSecurityPolicy::AllowBaseURI(const KURL&) {
  return true;
}
void ScriptRunnerDelayer::Deactivate() {}
ScriptRunner::ScriptRunner(Document* document) : document_(document) {}
ScriptRunnerDelayer::ScriptRunnerDelayer(ScriptRunner* script_runner,
                                         ScriptRunner::DelayReason reason)
    : script_runner_(script_runner), delay_reason_(reason) {}
void ScriptRunnerDelayer::Activate() {}
DocumentEncodingData::DocumentEncodingData() = default;
DocumentTiming::DocumentTiming(Document&)
    : document_timing_values_(MakeGarbageCollected<DocumentTimingValues>()) {}
void DocumentTiming::MarkDomLoading() {}
void DocumentTiming::MarkDomComplete() {}
void DocumentTiming::MarkDomInteractive() {}
ScriptedAnimationController::ScriptedAnimationController(
    LocalDOMWindow* window)
    : ExecutionContextLifecycleStateObserver(window),
      callback_collection_(window) {}
DocumentAnimations::DocumentAnimations(Document* document)
    : current_transition_generation_(0), document_(document) {}
WorkletAnimationController::WorkletAnimationController(Document* document)
    : document_(document) {}
FragmentDirective::FragmentDirective(Document& document)
    : owner_document_(&document) {}
FragmentDirective::~FragmentDirective() = default;
KURL FragmentDirective::ConsumeFragmentDirective(const KURL& url) {
  return url;
}
DisplayLockDocumentState::DisplayLockDocumentState(Document* document)
    : document_(document) {}
RenderBlockingResourceManager::RenderBlockingResourceManager(Document& document)
    : element_render_blocking_links_(MakeGarbageCollected<
          RenderBlockingElementLinkMap>(
          RenderBlockingElementLinkMap::RenderBlockingElementSetEmtpyCallback())),
      document_(document),
      font_preload_max_blocking_timer_(
          document.GetTaskRunner(TaskType::kInternalFrameLifecycleControl),
          this,
          &RenderBlockingResourceManager::FontPreloadingTimerFired),
      font_preload_max_fcp_delay_timer_(
          document.GetTaskRunner(TaskType::kInternalFrameLifecycleControl),
          this,
          &RenderBlockingResourceManager::FontPreloadingTimerFired) {}
CookieJar::CookieJar(Document* document)
    : backend_(document ? document->GetExecutionContext() : nullptr),
      document_(document) {}
RootScrollerController::RootScrollerController(Document& document)
    : document_(document) {}
ViewTransitionSupplement::ViewTransitionSupplement(Document& document)
    : document_(&document) {}
ViewTransitionSupplement::~ViewTransitionSupplement() = default;
void ViewTransitionSupplement::AddPendingRequest(
    std::unique_ptr<ViewTransitionRequest>) {}
void ViewTransitionSupplement::OnTransitionFinished(ViewTransition*) {}
void ViewTransitionSupplement::OnSkipTransitionWithPendingCallback(
    ViewTransition*) {}
void ViewTransitionSupplement::OnSkippedTransitionDOMCallback(ViewTransition*) {}
void ViewTransitionSupplement::OnTransitionCaptured(ViewTransition*) {}
void ViewTransitionSupplement::DidChangeVisibilityState() {}
bool ParseHTTPRefresh(const String&,
                      bool (*)(char16_t),
                      base::TimeDelta&,
                      String&) {
  return false;
}
void HttpRefreshScheduler::Schedule(base::TimeDelta,
                                    const KURL&,
                                    Document::HttpRefreshType) {}
LocalDOMWindow* PictureInPictureController::GetDocumentPictureInPictureWindow(
    const Document&) {
  return nullptr;
}
HitTestResult::HitTestResult(const HitTestRequest& request,
                             const HitTestLocation& location)
    : hit_test_request_(request), cacheable_(true) {}
HitTestResult::HitTestResult(const HitTestResult&) = default;
HitTestResult& HitTestResult::operator=(const HitTestResult&) = default;
void HitTestResult::Trace(Visitor*) const {}
void HitTestResult::CacheValues(const HitTestResult&) {}
PositionWithAffinity HitTestResult::GetPosition() const {
  return PositionWithAffinity();
}
void HitTestResult::SetURLElement(Element*) {}
void HitTestResult::SetToShadowHostIfInUAShadowRoot() {}
HitTestResult::~HitTestResult() = default;
PositionWithAffinity HitTestResult::GetPositionForInnerNodeOrImageMapImage()
    const {
  return PositionWithAffinity();
}
KURL HitTestResult::AbsoluteImageURL() const {
  return KURL();
}
KURL HitTestResult::AbsoluteLinkURL() const {
  return KURL();
}
String HitTestResult::Title(TextDirection& direction) const {
  direction = TextDirection::kLtr;
  return String();
}
Element* HitTestResult::InnerPossiblyPseudoElement() const {
  return nullptr;
}
Node* HitTestResult::InnerNodeOrImageMapImage() const {
  return nullptr;
}
CDATASection* CDATASection::Create(Document&, const String&) {
  return nullptr;
}
template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate()
    : anchor_node_(nullptr),
      offset_(0),
      anchor_type_(PositionAnchorType::kOffsetInAnchor) {}
template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const Node* anchor_node, int offset)
    : anchor_node_(const_cast<Node*>(anchor_node)),
      offset_(offset),
      anchor_type_(PositionAnchorType::kOffsetInAnchor) {}
template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const Node* anchor_node,
                                             PositionAnchorType anchor_type)
    : anchor_node_(const_cast<Node*>(anchor_node)),
      offset_(0),
      anchor_type_(anchor_type) {}
template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const PositionTemplate&) =
    default;
template <typename Strategy>
PositionTemplate<Strategy>& PositionTemplate<Strategy>::operator=(
    const PositionTemplate&) = default;
template <typename Strategy>
int PositionTemplate<Strategy>::ComputeOffsetInContainerNode() const {
  return 0;
}
template <typename Strategy>
PositionTemplate<Strategy>
PositionTemplate<Strategy>::ParentAnchoredEquivalent() const {
  return PositionTemplate<Strategy>();
}
template <typename Strategy>
PositionTemplate<Strategy>
PositionTemplate<Strategy>::InParentBeforeNode(const Node&) {
  return PositionTemplate<Strategy>();
}
template <typename Strategy>
int16_t PositionTemplate<Strategy>::CompareTo(
    const PositionTemplate<Strategy>&) const {
  return 0;
}
template <typename Strategy>
bool PositionTemplate<Strategy>::IsConnected() const {
  return false;
}
template <typename Strategy>
bool PositionTemplate<Strategy>::IsValidFor(const Document&) const {
  return true;
}
template <typename Strategy>
bool PositionTemplate<Strategy>::operator<=(
    const PositionTemplate<Strategy>& other) const {
  return CompareTo(other) <= 0;
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
PositionTemplate<Strategy>
PositionTemplate<Strategy>::FirstPositionInOrBeforeNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(&anchor_node, 0);
}
template <typename Strategy>
PositionTemplate<Strategy>
PositionTemplate<Strategy>::LastPositionInOrAfterNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(&anchor_node,
                                    PositionAnchorType::kAfterChildren);
}
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
template class PositionTemplate<EditingStrategy>;
template class PositionTemplate<EditingInFlatTreeStrategy>;
template bool PositionTemplate<EditingStrategy>::operator<=(
    const PositionTemplate<EditingStrategy>&) const;
template bool PositionTemplate<EditingInFlatTreeStrategy>::operator<=(
    const PositionTemplate<EditingInFlatTreeStrategy>&) const;
template class PositionWithAffinityTemplate<EditingStrategy>;
template class PositionWithAffinityTemplate<EditingInFlatTreeStrategy>;
bool EditingIgnoresContent(const Node&) {
  return false;
}
bool IsDisplayInsideTable(const Node*) {
  return false;
}
template <typename Traversal>
int EditingAlgorithm<Traversal>::LastOffsetForEditing(const Node*) {
  return 0;
}
short ComparePositions(const Position& a, const Position& b) {
  return a.CompareTo(b);
}
short ComparePositions(const PositionInFlatTree& a,
                       const PositionInFlatTree& b) {
  return a.CompareTo(b);
}
PositionWithAffinity PositionForContentsPointRespectingEditingBoundary(
    const gfx::Point&,
    LocalFrame*) {
  return PositionWithAffinity();
}
template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate() = default;
template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate(
    const PositionTemplate<Strategy>& start,
    const PositionTemplate<Strategy>& end)
    : start_position_(start), end_position_(end) {}
template <typename Strategy>
EphemeralRangeTemplate<Strategy>::EphemeralRangeTemplate(
    const EphemeralRangeTemplate&) = default;
template <typename Strategy>
EphemeralRangeTemplate<Strategy>::~EphemeralRangeTemplate() = default;
template <typename Strategy>
EphemeralRangeTemplate<Strategy> EphemeralRangeTemplate<Strategy>::RangeOfContents(
    const Node&) {
  return EphemeralRangeTemplate<Strategy>();
}
template <typename Strategy>
bool EphemeralRangeTemplate<Strategy>::IsValid() const {
  return !start_position_.IsNull() && !end_position_.IsNull();
}
template <typename Strategy>
PositionTemplate<Strategy> EphemeralRangeTemplate<Strategy>::StartPosition()
    const {
  return start_position_;
}
template <typename Strategy>
PositionTemplate<Strategy> EphemeralRangeTemplate<Strategy>::EndPosition()
    const {
  return end_position_;
}
template class EphemeralRangeTemplate<EditingStrategy>;
template class EphemeralRangeTemplate<EditingInFlatTreeStrategy>;
String PlainText(const EphemeralRange&, const TextIteratorBehavior&) {
  return String();
}
std::ostream& operator<<(std::ostream& ostream, const Position&) {
  return ostream;
}
template <typename Strategy>
VisiblePositionTemplate<Strategy>::VisiblePositionTemplate()
    : position_with_affinity_() {}
template class VisiblePositionTemplate<EditingStrategy>;
EditingBehavior Editor::Behavior() const {
  return EditingBehavior(mojom::blink::EditingBehavior::kEditingWindowsBehavior);
}
VisiblePosition CreateVisiblePosition(const PositionWithAffinity&) {
  return VisiblePosition();
}
CreateMarkupOptions::Builder&
CreateMarkupOptions::Builder::SetShouldAnnotateForInterchange(bool) {
  return *this;
}
CreateMarkupOptions::Builder& CreateMarkupOptions::Builder::SetShouldResolveURLs(
    AbsoluteURLs) {
  return *this;
}
String CreateMarkup(const Position&,
                    const Position&,
                    const CreateMarkupOptions&) {
  return String();
}
TextControlElement* EnclosingTextControl(const Node*) {
  return nullptr;
}
template int
PositionTemplate<EditingStrategy>::ComputeOffsetInContainerNode() const;
template PositionTemplate<EditingStrategy>
PositionTemplate<EditingStrategy>::ParentAnchoredEquivalent() const;
template PositionTemplate<EditingStrategy>
PositionTemplate<EditingStrategy>::InParentBeforeNode(const Node&);
template int16_t PositionTemplate<EditingStrategy>::CompareTo(
    const PositionTemplate<EditingStrategy>&) const;
template bool PositionTemplate<EditingStrategy>::IsConnected() const;
void EventHandler::NotifyElementActivated() {}
ResizeObserver* ResizeObserver::Create(LocalDOMWindow* window,
                                       ResizeObserver::Delegate* delegate) {
  return MakeGarbageCollected<ResizeObserver>(delegate, window);
}
void ResizeObserver::observe(Element*) {}
void ResizeObserver::unobserve(Element*) {}
ResourceFetcher* FrameFetchContext::CreateFetcherForCommittedDocument(
    DocumentLoader&,
    Document&) {
  return nullptr;
}
NullResourceFetcherProperties::NullResourceFetcherProperties()
    : fetch_client_settings_object_(nullptr) {}
void NullResourceFetcherProperties::Trace(Visitor* visitor) const {
  visitor->Trace(fetch_client_settings_object_);
  ResourceFetcherProperties::Trace(visitor);
}
ResourceFetcherInit::ResourceFetcherInit(
    DetachableResourceFetcherProperties& properties_in,
    FetchContext* context_in,
    scoped_refptr<base::SingleThreadTaskRunner> freezable_task_runner_in,
    scoped_refptr<base::SingleThreadTaskRunner> unfreezable_task_runner_in,
    ResourceFetcher::LoaderFactory* loader_factory_in,
    ContextLifecycleNotifier* context_lifecycle_notifier_in,
    BackForwardCacheLoaderHelper* back_forward_cache_loader_helper_in)
    : properties(&properties_in),
      context(context_in),
      freezable_task_runner(std::move(freezable_task_runner_in)),
      unfreezable_task_runner(std::move(unfreezable_task_runner_in)),
      loader_factory(loader_factory_in),
      context_lifecycle_notifier(context_lifecycle_notifier_in),
      back_forward_cache_loader_helper(back_forward_cache_loader_helper_in) {}
ResourceFetcher::ResourceFetcher(const ResourceFetcherInit& init)
    : properties_(init.properties),
      context_(init.context),
      freezable_task_runner_(init.freezable_task_runner),
      unfreezable_task_runner_(init.unfreezable_task_runner),
      loader_factory_(init.loader_factory),
      back_forward_cache_loader_helper_(init.back_forward_cache_loader_helper),
      resource_timing_report_timer_(init.freezable_task_runner, this,
                                    &ResourceFetcher::ResourceTimingReportTimerFired),
      blob_registry_remote_(init.context_lifecycle_notifier),
      context_lifecycle_notifier_(init.context_lifecycle_notifier),
      auto_load_images_(true),
      allow_stale_resources_(false),
      image_fetched_(false),
      stale_while_revalidate_enabled_(false) {}
void ResourceFetcher::ResourceTimingReportTimerFired(TimerBase*) {}
void ResourceFetcher::ReloadImagesIfNotDeferred() {}
void ResourceFetcher::SetAutoLoadImages(bool value) {
  auto_load_images_ = value;
}
bool ExecutionContext::IsFeatureEnabled(
    network::mojom::PermissionsPolicyFeature,
    ReportOptions,
    const String&) {
  return false;
}
void ExecutionContext::SetLifecycleState(mojom::blink::FrameLifecycleState) {}
bool SecurityContext::IsSandboxed(
    network::mojom::blink::WebSandboxFlags) const {
  return false;
}
bool SchemeRegistry::IsDomainRelaxationForbiddenForURLScheme(const String&) {
  return true;
}
bool SchemeRegistry::ShouldTreatURLSchemeAsNotAllowingJavascriptURLs(
    const String&) {
  return true;
}
SecurityContext::SecurityContext(ExecutionContext* context)
    : sandbox_flags_(network::mojom::blink::WebSandboxFlags::kNone),
      execution_context_(context),
      insecure_request_policy_(
          mojom::blink::InsecureRequestPolicy::kLeaveInsecureRequestsAlone) {
}
HttpsState CalculateHttpsState(const SecurityOrigin*,
                               std::optional<HttpsState> parent_https_state) {
  return parent_https_state.value_or(HttpsState::kNone);
}
bool ContentSecurityPolicy::ShouldBypassMainWorldDeprecated(
    const ExecutionContext*) {
  return false;
}
bool ContentSecurityPolicy::ShouldBypassMainWorldDeprecated(
    const DOMWrapperWorld*) {
  return false;
}
bool ContentSecurityPolicy::IsNonceableElement(const Element*) {
  return false;
}
bool ContentSecurityPolicy::AllowInline(InlineType,
                                        Element*,
                                        const String&,
                                        const String&,
                                        const String&,
                                        const OrdinalNumber&,
                                        ReportingDisposition) {
  return false;
}
String TrustedTypesCheckForJavascriptURLinNavigation(const String& value,
                                                     ExecutionContext*) {
  return value;
}
IsolatedWorldCSP::IsolatedWorldCSP() = default;
IsolatedWorldCSP& IsolatedWorldCSP::Get() {
  static IsolatedWorldCSP* csp = new IsolatedWorldCSP();
  return *csp;
}
ContentSecurityPolicy* IsolatedWorldCSP::CreateIsolatedWorldCSP(
    LocalDOMWindow&,
    int32_t) {
  return nullptr;
}
bool SchemeRegistry::IsWebUIScheme(const String&) {
  return false;
}
bool SchemeRegistry::ShouldTreatURLSchemeAsFirstPartyWhenTopLevel(
    const String&) {
  return false;
}
bool SchemeRegistry::ShouldTreatURLAsFirstPartyWhenTopLevelEmbeddingSecure(
    const SecurityOrigin*,
    const String&) {
  return false;
}
bool KURL::ProtocolIsInHttpFamily() const {
  return false;
}
bool KURL::ProtocolIsJavaScript() const {
  return false;
}
String KURL::ElidedString() const {
  return GetString();
}
String KURL::StrippedForUseAsReferrer() const {
  return GetString();
}
StringView KURL::Host() const {
  return StringView();
}
String KURL::Protocol() const {
  return protocol_;
}
bool operator==(const KURL& a, const KURL& b) {
  return a.GetString() == b.GetString();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const AtomicString& QualifiedName::LocalNameUpperSlow() const {
  return LocalName();
}
#endif
KURL::KURL(const KURL& base, const StringView&) : KURL(base) {}
bool KURL::IsAboutBlankUrl() const {
  return false;
}
bool KURL::IsNull() const {
  return false;
}
bool KURL::IsValid() const {
  return is_valid_;
}
StringView KURL::FragmentIdentifier() const {
  return StringView();
}
bool KURL::IsAboutSrcdocUrl() const {
  return false;
}
const KURL& BlankUrl() {
  static KURL* url = new KURL(StringView("about:blank"));
  return *url;
}
const KURL& NullUrl() {
  static KURL* url = new KURL();
  return *url;
}
bool ProtocolIs(const StringView&, const char*) {
  return false;
}
String DecodeUrlEscapeSequences(const StringView&, url::DecodeUrlMode) {
  return String();
}
bool EqualIgnoringFragmentIdentifier(const KURL&, const KURL&) {
  return false;
}
std::optional<base::Time> ParseDate(const String&) {
  return std::nullopt;
}
v8::Local<v8::Value> V8ThrowDOMException::CreateOrEmpty(v8::Isolate*,
                                                        DOMExceptionCode,
                                                        const String&,
                                                        const String&) {
  return v8::Local<v8::Value>();
}
void CanvasFontCache::Dispose() {}
void CanvasFontCache::DidProcessTask(const base::PendingTask&) {}
void CanvasFontCache::PruneAll() {}
void DocumentParserTiming::Trace(Visitor*) const {}
CustomCountHistogram::CustomCountHistogram(const char*, int, int, int)
    : histogram_(nullptr) {}
void CustomCountHistogram::CountMicroseconds(base::TimeDelta) {}
void ProgressTracker::Trace(Visitor*) const {}
bool XMLDocumentParser::SupportsXMLVersion(const String&) {
  return true;
}
XMLDocumentParser::XMLDocumentParser(Document& document, LocalFrameView*)
    : ScriptableDocumentParser(document),
      xml_errors_(&document),
      script_start_position_(TextPosition::MinimumPosition()) {}
XMLDocumentParser::~XMLDocumentParser() = default;
void XMLDocumentParser::Trace(Visitor* visitor) const {
  ScriptableDocumentParser::Trace(visitor);
  visitor->Trace(current_node_);
  visitor->Trace(ancestor_resetting_namespace_);
  visitor->Trace(current_node_stack_);
  visitor->Trace(leaf_text_node_);
  xml_errors_.Trace(visitor);
  visitor->Trace(document_);
  visitor->Trace(script_runner_);
}
void XMLDocumentParser::Append(const String&) {}
void XMLDocumentParser::Finish() {}
void XMLDocumentParser::StopParsing() {}
void XMLDocumentParser::Detach() {}
void XMLDocumentParser::ExecuteScriptsWaitingForResources() {}
bool XMLDocumentParser::IsWaitingForScripts() const {
  return false;
}
void XMLDocumentParser::DidAddPendingParserBlockingStylesheet() {}
void XMLDocumentParser::DidLoadAllPendingParserBlockingStylesheets() {}
OrdinalNumber XMLDocumentParser::LineNumber() const {
  return OrdinalNumber::First();
}
TextPosition XMLDocumentParser::GetTextPosition() const {
  return TextPosition::MinimumPosition();
}
void XMLDocumentParser::NotifyScriptExecuted() {}
bool HttpRefreshScheduler::IsScheduledWithin(base::TimeDelta) const {
  return false;
}
void Frame::CancelFormSubmission() {}
Frame::Frame(FrameClient* client,
             Page& page,
             FrameOwner* owner,
             Frame* parent,
             Frame* previous_sibling,
             FrameInsertType,
             const FrameToken& frame_token,
             const base::UnguessableToken& devtools_frame_token,
             WindowProxyManager* window_proxy_manager,
             WindowAgentFactory* inheriting_agent_factory)
    : tree_node_(this),
      page_(&page),
      owner_(owner),
      client_(client),
      window_proxy_manager_(window_proxy_manager),
      parent_(parent),
      navigation_rate_limiter_(*this),
      window_agent_factory_(inheriting_agent_factory
                                ? inheriting_agent_factory
                                : MakeGarbageCollected<WindowAgentFactory>(
                                      page.GetAgentGroupScheduler())),
      is_loading_(false),
      devtools_frame_token_(devtools_frame_token),
      frame_token_(frame_token) {
  CHECK(!previous_sibling);
}
Frame::~Frame() = default;
void Frame::SetOpenerDoNotNotify(Frame* opener) {
  opener_ = opener;
}
bool Frame::Detach(FrameDetachType) {
  return true;
}
HTMLFrameOwnerElement* Frame::DeprecatedLocalOwner() const {
  return DynamicTo<HTMLFrameOwnerElement>(owner_.Get());
}
bool Frame::IsFencedFrameRoot() const {
  return false;
}
bool Frame::IsInFencedFrameTree() const {
  return false;
}
void Frame::Initialize() {}
void Frame::UpdateVisibleToHitTesting() {}
void Frame::UpdateInheritedEffectiveTouchActionIfPossible() {}
void Frame::UpdateInertIfPossible() {}
void Frame::Trace(Visitor*) const {}
Frame* Frame::Parent() const {
  return parent_.Get();
}
WindowProxy* Frame::GetWindowProxy(DOMWrapperWorld&) {
  return nullptr;
}
WindowProxy* Frame::GetWindowProxyMaybeUninitialized(DOMWrapperWorld&) {
  return nullptr;
}
Settings* Frame::GetSettings() const {
  if (GetPage()) {
    return &GetPage()->GetSettings();
  }
  return nullptr;
}
void Frame::DidChangeVisibilityState() {}
void Frame::NotifyUserActivationInFrameTree(
    mojom::UserActivationNotificationType,
    bool) {}
bool Frame::ConsumeTransientUserActivationInFrameTree() {
  return false;
}
bool Frame::IsCrossOriginToParentOrOuterDocument() const {
  return false;
}
bool RemoteFrame::IsRemoteFrameHostRemoteBound() {
  return false;
}
void RemoteFrame::ZoomFactorChanged(double) {}
FocusOptions::FocusOptions() = default;
void FocusOptions::Trace(Visitor*) const {}
SmartClip::SmartClip(LocalFrame* frame) : frame_(frame) {}
SmartClipData SmartClip::DataForRect(const gfx::Rect&) {
  return SmartClipData();
}
void FrameLoader::DidExplicitOpen() {}
void FrameLoader::RestoreScrollPositionAndViewState() {}
void FrameLoader::StopAllLoaders(bool) {}
void DocumentLoadTiming::SetRandomizedConfidence(
    const std::optional<std::pair<double, mojom::blink::ConfidenceLevel>>&) {}
void DocumentLoadTiming::MarkLoadEventStart() {}
void DocumentLoadTiming::MarkLoadEventEnd() {}
bool IsFetchLaterUseDeferredFetchPolicyEnabled() {
  return false;
}
void HTMLFrameOwnerElement::MaybeClearDeferredFetchPolicy() {}
bool HTMLFrameOwnerElement::LoadImmediatelyIfLazy() {
  return false;
}
void HTMLFrameOwnerElement::CancelPendingLazyLoad() {}
void HTMLFrameOwnerElement::SetEmbeddedContentView(EmbeddedContentView*) {}
SubframeLoadingDisabler::SubtreeRootSet&
SubframeLoadingDisabler::DisabledSubtreeRoots() {
  static SubtreeRootSet* roots = new SubtreeRootSet();
  return *roots;
}
void CloseWatcher::WatcherStack::SetHadUserInteraction(bool) {}
CloseWatcher::WatcherStack::WatcherStack(LocalDOMWindow* window)
    : receiver_(this, window), window_(window) {}
void CloseWatcher::WatcherStack::Trace(Visitor*) const {}
void CloseWatcher::WatcherStack::Signal() {}
PluginScriptForbiddenScope::PluginScriptForbiddenScope() = default;
PluginScriptForbiddenScope::~PluginScriptForbiddenScope() = default;
void ChildFrameDisconnector::Disconnect(DisconnectPolicy) {}
void SelectorQueryCache::Invalidate() {}
DocumentSpeculationRules* DocumentSpeculationRules::FromIfExists(Document&) {
  return nullptr;
}
DocumentResourceCoordinator::~DocumentResourceCoordinator() = default;
void DocumentResourceCoordinator::SetIsAdFrame(bool) {}
void DocumentResourceCoordinator::SetLifecycleState(
    performance_manager::mojom::LifecycleState) {}
void DocumentResourceCoordinator::SetNetworkAlmostIdle() {}
TransformSource::~TransformSource() = default;
MediaQueryMatcher::MediaQueryMatcher(Document& document) : document_(document) {}
void VisitedLinkState::InvalidateStyleForAllLinks(bool) {}
void VisitedLinkState::InvalidateStyleForLink(uint64_t) {}
SettingsBase::SettingsBase()
    : delegate_(nullptr),
      lcd_text_preference_(LCDTextPreference::kStronglyPreferred),
      network_quiet_timeout_(0.5),
      accelerated_2d_canvas_msaa_sample_count_(0),
      accessibility_font_scale_factor_(1.0),
      accessibility_font_weight_adjustment_(0),
      accessibility_text_size_contrast_factor_(0),
      autoplay_policy_(AutoplayPolicy::Type::kNoUserGestureRequired),
      available_hover_types_(ui::HOVER_TYPE_NONE),
      available_pointer_types_(ui::POINTER_TYPE_NONE),
      default_fixed_font_size_(0),
      default_font_size_(0),
      display_mode_override_(blink::mojom::DisplayMode::kUndefined),
#if BUILDFLAG(IS_ANDROID)
      editing_behavior_type_(mojom::blink::EditingBehavior::kEditingAndroidBehavior),
#elif BUILDFLAG(IS_CHROMEOS)
      editing_behavior_type_(mojom::blink::EditingBehavior::kEditingChromeOSBehavior),
#elif BUILDFLAG(IS_MAC)
      editing_behavior_type_(mojom::blink::EditingBehavior::kEditingMacBehavior),
#elif BUILDFLAG(IS_WIN)
      editing_behavior_type_(mojom::blink::EditingBehavior::kEditingWindowsBehavior),
#else
      editing_behavior_type_(mojom::blink::EditingBehavior::kEditingUnixBehavior),
#endif
      image_animation_policy_(mojom::blink::ImageAnimationPolicy::kImageAnimationPolicyAllowed),
      lazy_loading_frame_margin_px_2_g_(6000),
      lazy_loading_frame_margin_px_3_g_(3500),
      lazy_loading_frame_margin_px_4_g_(2500),
      lazy_loading_frame_margin_px_offline_(8000),
      lazy_loading_frame_margin_px_slow_2_g_(8000),
      lazy_loading_frame_margin_px_unknown_(4000),
      lazy_loading_image_margin_px_2_g_(6000),
      lazy_loading_image_margin_px_3_g_(2500),
      lazy_loading_image_margin_px_4_g_(1250),
      lazy_loading_image_margin_px_offline_(8000),
      lazy_loading_image_margin_px_slow_2_g_(8000),
      lazy_loading_image_margin_px_unknown_(3000),
      low_priority_iframes_threshold_(WebEffectiveConnectionType::kTypeUnknown),
      max_touch_points_(0),
      media_type_override_(""),
      minimum_font_size_(0),
      minimum_logical_font_size_(0),
      navigation_controls_(NavigationControls::kNone),
      output_device_update_ability_type_(mojom::blink::OutputDeviceUpdateAbilityType::kFastType),
      parser_scripting_flag_policy_(ParserScriptingFlagPolicy::kOnlyIfScriptIsEnabled),
      password_echo_duration_in_seconds_(1),
      preferred_color_scheme_(mojom::blink::PreferredColorScheme::kLight),
      preferred_contrast_(mojom::blink::PreferredContrast::kNoPreference),
      preferred_root_scrollbar_color_scheme_(mojom::blink::PreferredColorScheme::kLight),
      primary_hover_type_(mojom::blink::HoverType::kHoverNone),
      primary_pointer_type_(mojom::blink::PointerType::kPointerNone),
      printing_maximum_shrink_factor_(1.5),
      root_scrollbar_theme_color_(std::nullopt),
      selection_strategy_(SelectionStrategy::kCharacter),
      text_track_kind_user_preference_(TextTrackKindUserPreference::kDefault),
      text_track_margin_percentage_(0),
      v8_cache_options_(mojom::blink::V8CacheOptions::kDefault),
      validation_message_timer_magnification_(50),
      viewport_style_(mojom::blink::ViewportStyle::kDefault),
      window_show_state_(ui::mojom::blink::WindowShowState::kDefault),
      dom_paste_allowed_(false),
      dont_send_key_events_to_javascript_(false),
      highlight_ads_(false),
      inspector_highlight_ads_(false),
      web_xr_immersive_ar_allowed_(true),
      accelerated_compositing_enabled_(false),
      accessibility_always_show_focus_(false),
      accessibility_include_svg_g_element_(false),
      accessibility_password_values_enabled_(false),
      allow_custom_scrollbar_in_main_frame_(true),
      allow_file_access_from_file_urls_(true),
      allow_geolocation_on_insecure_origins_(false),
      allow_running_of_insecure_content_(true),
      allow_scripts_to_close_windows_(false),
      allow_universal_access_from_file_urls_(true),
      allow_unrestricted_window_focus_(false),
      always_show_context_menu_on_touch_(true),
      antialiased_2d_canvas_enabled_(true),
      antialiased_clips_2d_canvas_enabled_(true),
      aria_modal_prunes_ax_tree_(false),
      barrel_button_for_drag_enabled_(false),
      bypass_csp_(false),
      caret_browsing_enabled_(false),
      cookie_enabled_(true),
      disable_reading_from_canvas_(false),
      disallow_fetch_for_doc_written_scripts_in_main_frame_(false),
      disallow_fetch_for_doc_written_scripts_in_main_frame_if_effectively_2_g_(false),
      disallow_fetch_for_doc_written_scripts_in_main_frame_on_slow_connections_(true),
      dns_prefetching_enabled_(false),
      do_html_preload_scanning_(true),
      do_not_update_selection_on_mutating_selection_range_(false),
      downloadable_binary_fonts_enabled_(true),
      dynamic_safe_area_insets_enabled_(false),
      embedded_media_experience_enabled_(false),
      force_android_overlay_scrollbar_(false),
      force_dark_mode_enabled_(false),
      force_main_world_initialization_(false),
      force_touch_event_feature_detection_for_inspector_(false),
      force_zero_layout_height_(false),
      fullscreen_supported_(true),
      hide_download_ui_(false),
      hide_scrollbars_(false),
      hyperlink_auditing_enabled_(false),
      ignore_main_frame_overflow_hidden_quirk_(false),
      ignore_permission_for_device_changed_event_(false),
      images_enabled_(true),
      immersive_mode_enabled_(false),
      immersive_video_playback_enabled_(false),
      in_forced_colors_(false),
      inverted_colors_(false),
      is_forced_colors_disabled_(false),
      is_initial_profile_(false),
      java_script_can_access_clipboard_(false),
      lazy_load_enabled_(true),
      load_with_overview_mode_(true),
      loads_images_automatically_(false),
      local_storage_enabled_(false),
      log_dns_prefetch_and_preconnect_(false),
      log_preload_(false),
      main_frame_clips_content_(true),
      main_frame_resizes_are_orientation_changes_(false),
      media_controls_enabled_(true),
      middle_click_paste_allowed_(true),
      mock_gesture_tap_highlights_enabled_(false),
      modal_context_menu_(true),
      multi_target_tap_notification_enabled_(true),
      navigate_on_drag_drop_(true),
      password_echo_enabled_physical_(false),
      password_echo_enabled_touch_(false),
      picture_in_picture_enabled_(true),
      place_rtl_scrollbars_on_left_side_in_main_frame_(false),
      plugins_enabled_(false),
      prefer_hidden_volume_controls_(false),
      prefers_default_scrollbar_styles_(false),
      prefers_reduced_motion_(false),
      prefers_reduced_transparency_(false),
      presentation_receiver_(false),
      presentation_requires_user_gesture_(true),
      report_screen_size_in_physical_pixels_quirk_(false),
      require_transient_activation_and_authorization_for_sub_apps_api_(true),
      require_transient_activation_for_get_display_media_(true),
      require_transient_activation_for_show_file_or_directory_picker_(true),
      resizable_(true),
      rubber_banding_on_compositor_thread_(false),
      scale_all_fonts_if_no_meta_text_scale_tag_(false),
      script_enabled_(false),
      scroll_animator_enabled_(true),
#if BUILDFLAG(IS_WIN)
      select_trailing_whitespace_enabled_(true),
#else
      select_trailing_whitespace_enabled_(false),
#endif
      selection_clipboard_buffer_available_(false),
      selection_includes_alt_image_text_(false),
      should_clear_document_background_(true),
      should_print_backgrounds_(false),
      should_protect_against_ipc_flooding_(true),
      should_reuse_global_for_unowned_main_frame_(false),
      show_context_menu_on_mouse_up_(false),
      shrinks_viewport_content_to_fit_(false),
      smart_insert_delete_enabled_(false),
      smooth_scroll_for_find_enabled_(false),
      spatial_navigation_enabled_(false),
      spell_check_enabled_by_default_(true),
      strict_mixed_content_checking_(false),
      strict_mixed_content_checking_for_plugin_(false),
      strict_powerful_feature_restrictions_(false),
      strictly_block_blockable_mixed_content_(false),
      supports_multiple_windows_(true),
      sync_xhr_in_documents_enabled_(true),
      target_blank_implies_no_opener_enabled_will_be_removed_(true),
      text_areas_are_resizable_(false),
      text_size_adjust_enabled_(false),
      touch_drag_drop_enabled_(false),
      touch_drag_end_context_menu_(false),
      touch_editing_enabled_(false),
      use_ax_menu_list_(true),
      use_wide_viewport_(true),
      viewport_enabled_(false),
      viewport_meta_enabled_(false),
      viewport_meta_merge_content_quirk_(false),
      viewport_meta_zero_values_quirk_(false),
      web_gl_1_enabled_(true),
      webgl2_enabled_(true),
      web_gl_errors_to_console_enabled_(true),
      web_security_enabled_(true),
      wide_viewport_quirk_enabled_(false) {}
void SettingsBase::SetLCDTextPreference(LCDTextPreference preference) {
  lcd_text_preference_ = preference;
}
void SettingsBase::Invalidate(SettingsDelegate::ChangeType) {
  if (delegate_) {
    delegate_->SettingsChanged(SettingsDelegate::ChangeType::kStyle);
  }
}
void SettingsBase::SetDefaultFontSize(int default_font_size) {
  if (default_font_size_ == default_font_size) {
    return;
  }
  default_font_size_ = default_font_size;
  Invalidate(SettingsDelegate::ChangeType::kStyle);
  Invalidate(SettingsDelegate::ChangeType::kFontScaleFactor);
}
void SettingsBase::SetDefaultFixedFontSize(int default_fixed_font_size) {
  if (default_fixed_font_size_ == default_fixed_font_size) {
    return;
  }
  default_fixed_font_size_ = default_fixed_font_size;
  Invalidate(SettingsDelegate::ChangeType::kStyle);
}
SettingsDelegate::SettingsDelegate(std::unique_ptr<Settings> settings)
    : settings_(std::move(settings)) {}
SettingsDelegate::~SettingsDelegate() = default;
DOMWindow::DOMWindow(Frame& frame)
    : frame_(frame),
      window_proxy_manager_(frame.GetWindowProxyManager()),
      window_is_closing_(false) {
}
Location* DOMWindow::location() const {
  return nullptr;
}
v8::Local<v8::Object> DOMWindow::AssociateWithWrapper(
    v8::Isolate*,
    const WrapperTypeInfo*,
    v8::Local<v8::Object> wrapper) {
  return wrapper;
}
const AtomicString& DOMWindow::InterfaceName() const {
  static const AtomicString* name = new AtomicString("DOMWindow");
  return *name;
}
const DOMWindow* DOMWindow::ToDOMWindow() const {
  return this;
}
bool DOMWindow::IsWindowOrWorkerGlobalScope() const {
  return true;
}
DOMOrigin* DOMWindow::GetDOMOrigin(LocalDOMWindow*) const {
  return nullptr;
}
v8::Local<v8::Value> DOMWindow::Wrap(ScriptState*) {
  return v8::Local<v8::Value>();
}
void UniversalGlobalScope::Trace(Visitor*) const {}
ExecutionContext::~ExecutionContext() = default;
void ExecutionContext::NotifyContextDestroyed() {}
bool ExecutionContext::IsContextPaused() const {
  return false;
}
bool ExecutionContext::IsSameAgentCluster(const base::UnguessableToken&) const {
  return false;
}
void ExecutionContext::CountDeprecation(mojom::WebFeature) {}
ExecutionContext* ExecutionContext::From(const ScriptState*) {
  return nullptr;
}
ContentSecurityPolicy* ExecutionContext::GetContentSecurityPolicyForWorld(
    const DOMWrapperWorld*) {
  return nullptr;
}
mojom::blink::V8CacheOptions ExecutionContext::GetV8CacheOptions() const {
  return mojom::blink::V8CacheOptions::kDefault;
}
String ExecutionContext::OutgoingReferrer() const {
  return String();
}
DOMWindow::~DOMWindow() = default;
void DOMWindow::Trace(Visitor*) const {}
bool DOMWindow::IsCurrentlyDisplayedInFrame() const {
  return false;
}
DOMWindow* DOMWindow::top() const {
  return const_cast<DOMWindow*>(this);
}
ExecutionContext::ExecutionContext(v8::Isolate* isolate,
                                   Agent* agent,
                                   bool)
    : isolate_(isolate),
      security_context_(this),
      agent_(agent),
      circular_sequential_id_(0),
      in_dispatch_error_event_(false),
      lifecycle_state_(mojom::FrameLifecycleState::kRunning),
      csp_delegate_(nullptr),
      window_interaction_tokens_(0) {
}
History::History(LocalDOMWindow* window) : ExecutionContextClient(window) {}
Screen::Screen(LocalDOMWindow* window, int64_t display_id)
    : ExecutionContextClient(window), display_id_(display_id) {}
void Screen::Trace(Visitor*) const {}
const AtomicString& Screen::InterfaceName() const {
  static const AtomicString* name = new AtomicString("Screen");
  return *name;
}
ExecutionContext* Screen::GetExecutionContext() const {
  return ExecutionContextClient::GetExecutionContext();
}
BarProp::BarProp(ExecutionContext* context) : ExecutionContextClient(context) {}
NavigatorBase::NavigatorBase(ExecutionContext* context)
    : NavigatorLanguage(context), ExecutionContextClient(context) {}
Navigator::Navigator(ExecutionContext* context) : NavigatorBase(context) {}
unsigned int NavigatorBase::hardwareConcurrency() const {
  return 1;
}
void NavigatorBase::Trace(Visitor*) const {}
String NavigatorBase::platform() const {
  return String();
}
unsigned int NavigatorConcurrentHardware::hardwareConcurrency() const {
  return 1;
}
String NavigatorID::platform() const {
  return String();
}
String NavigatorBase::userAgent() const {
  return String();
}
ExecutionContext* NavigatorBase::GetUAExecutionContext() const {
  return GetExecutionContext();
}
UserAgentMetadata NavigatorBase::GetUserAgentMetadata() const {
  return UserAgentMetadata();
}
String Navigator::platform() const {
  return String();
}
String Navigator::GetAcceptLanguages() {
  return String();
}
NavigationApi::NavigationApi(LocalDOMWindow*) {}
const AtomicString& NavigationApi::InterfaceName() const {
  static const AtomicString* name = new AtomicString("Navigation");
  return *name;
}
void NavigationApi::AddedEventListener(const AtomicString&,
                                       RegisteredEventListener&) {}
void NavigationApi::RemovedEventListener(const AtomicString&,
                                         const RegisteredEventListener&) {}
StyleMedia::StyleMedia(LocalDOMWindow* window)
    : ExecutionContextClient(window) {}
void History::Trace(Visitor*) const {}
void BarProp::Trace(Visitor*) const {}
void Navigator::Trace(Visitor*) const {}
void StyleMedia::Trace(Visitor*) const {}
void NavigationApi::Trace(Visitor*) const {}
void DOMViewport::Trace(Visitor*) const {}
void DOMVisualViewport::Trace(Visitor*) const {}
const WrapperTypeInfo& DOMViewport::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
const WrapperTypeInfo& DOMVisualViewport::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
DOMViewport::DOMViewport(LocalDOMWindow* window) : window_(window) {}
DOMViewport::~DOMViewport() = default;
std::optional<HeapVector<Member<DOMRect>>> DOMViewport::segments() const {
  return std::nullopt;
}
DOMVisualViewport::DOMVisualViewport(LocalDOMWindow* window)
    : window_(window) {}
DOMVisualViewport::~DOMVisualViewport() = default;
const AtomicString& DOMVisualViewport::InterfaceName() const {
  static const AtomicString* name = new AtomicString("VisualViewport");
  return *name;
}
ExecutionContext* DOMVisualViewport::GetExecutionContext() const {
  return reinterpret_cast<ExecutionContext*>(window_.Get());
}
float DOMVisualViewport::offsetLeft() const { return 0; }
float DOMVisualViewport::offsetTop() const { return 0; }
float DOMVisualViewport::pageLeft() const { return 0; }
float DOMVisualViewport::pageTop() const { return 0; }
double DOMVisualViewport::width() const { return 0; }
double DOMVisualViewport::height() const { return 0; }
double DOMVisualViewport::scale() const { return 1; }
void Fence::Trace(Visitor*) const {}
void CrashReportContext::Trace(Visitor*) const {}
void SoftNavigationHeuristics::Trace(Visitor*) const {}
void TrustedTypePolicyFactory::Trace(Visitor*) const {}
const AtomicString& TrustedTypePolicyFactory::InterfaceName() const {
  static const AtomicString* name = new AtomicString("TrustedTypePolicyFactory");
  return *name;
}
ExecutionContext* TrustedTypePolicyFactory::GetExecutionContext() const {
  return ExecutionContextClient::GetExecutionContext();
}
void MessageEvent::Trace(Visitor*) const {}
MessageEvent::MessageEvent(scoped_refptr<SerializedScriptValue>,
                           scoped_refptr<const SecurityOrigin>,
                           MessageOriginKind,
                           const String&,
                           EventTarget*,
                           Vector<MessagePortChannel>,
                           UserActivation*,
                           mojom::blink::DelegatedCapability)
    : Event() {}
MessageEvent::MessageEvent(scoped_refptr<const SecurityOrigin>, EventTarget*)
    : Event() {}
MessageEvent::~MessageEvent() = default;
const AtomicString& MessageEvent::InterfaceName() const {
  static const AtomicString* name = new AtomicString("MessageEvent");
  return *name;
}
DOMOrigin* MessageEvent::GetDOMOrigin(LocalDOMWindow*) const {
  return nullptr;
}
void MessageEvent::EntangleMessagePorts(ExecutionContext*) {}
bool MessageEvent::IsOriginCheckRequiredToAccessData() const {
  return false;
}
bool MessageEvent::IsLockedToAgentCluster() const {
  return false;
}
bool MessageEvent::CanDeserializeIn(ExecutionContext*) const {
  return true;
}
class MessagePortChannel::State
    : public base::RefCountedThreadSafe<MessagePortChannel::State> {
 private:
  friend class base::RefCountedThreadSafe<MessagePortChannel::State>;
  ~State() = default;
};
MessagePortChannel::~MessagePortChannel() = default;
PageTransitionEvent::PageTransitionEvent(const AtomicString& type,
                                         bool persisted)
    : Event(type, Bubbles::kNo, Cancelable::kNo),
      persisted_(persisted) {}
PageTransitionEvent::PageTransitionEvent(base::TimeTicks)
    : Event(), persisted_(true) {}
PageTransitionEvent::~PageTransitionEvent() = default;
void PageTransitionEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
}
const AtomicString& PageTransitionEvent::InterfaceName() const {
  static const AtomicString* name = new AtomicString("PageTransitionEvent");
  return *name;
}
PopStateEvent* PopStateEvent::Create(scoped_refptr<SerializedScriptValue>,
                                     History*,
                                     bool,
                                     UserNavigationInvolvement) {
  return nullptr;
}
NavigationEventTiming::NavigationEventTiming(LocalFrame*, const Event&) {}
EventTiming::~EventTiming() = default;
SerializedScriptValue::~SerializedScriptValue() = default;
ArrayBufferContents::~ArrayBufferContents() = default;
BlobDataHandle::~BlobDataHandle() = default;
void inspector_handle_post_message_event::Data(perfetto::TracedValue,
                                               ExecutionContext*,
                                               const MessageEvent&) {}
void inspector_schedule_post_message_event::Data(perfetto::TracedValue,
                                                 ExecutionContext*,
                                                 uint64_t) {}
void inspector_event_dispatch_event::Data(perfetto::TracedValue,
                                          const Event&,
                                          v8::Isolate*) {}
void inspector_mark_load_event::Data(perfetto::TracedValue, LocalFrame*) {}
v8::MicrotaskQueue* ToMicrotaskQueue(ExecutionContext*) {
  return nullptr;
}
v8::MicrotaskQueue* ToMicrotaskQueue(ScriptState*) {
  return nullptr;
}
v8::Local<v8::Value> bindings::DictionaryBase::ToV8(ScriptState*) const {
  return v8::Local<v8::Value>();
}
void ExecutionContext::RemoveURLFromMemoryCache(const KURL&) {}
void ExecutionContext::Trace(Visitor*) const {}
ContentSecurityPolicy* ExecutionContext::GetContentSecurityPolicy() const {
  return content_security_policy_.Get();
}
ContentSecurityPolicyDelegate&
ExecutionContext::GetContentSecurityPolicyDelegate() {
  return *csp_delegate_;
}
network::mojom::ReferrerPolicy ExecutionContext::GetReferrerPolicy() const {
  return network::mojom::ReferrerPolicy::kDefault;
}
bool ExecutionContext::IsFeatureEnabled(
    network::mojom::PermissionsPolicyFeature) const {
  return false;
}
bool ExecutionContext::IsSandboxed(
    network::mojom::blink::WebSandboxFlags) const {
  return false;
}
void ExecutionContext::SetIsInBackForwardCache(bool) {}
const DOMWrapperWorld* ExecutionContext::GetCurrentWorld() const {
  return nullptr;
}
DOMWrapperWorld& DOMWrapperWorld::MainWorld(v8::Isolate*) {
  return *static_cast<DOMWrapperWorld*>(nullptr);
}
NetworkStateNotifier& GetNetworkStateNotifier() {
  static NetworkStateNotifier* notifier = new NetworkStateNotifier();
  return *notifier;
}
std::unique_ptr<NetworkStateNotifier::NetworkStateObserverHandle>
NetworkStateNotifier::AddOnLineObserver(
    NetworkStateObserver*,
    scoped_refptr<base::SingleThreadTaskRunner>) {
  return nullptr;
}
NetworkStateNotifier::NetworkStateObserverHandle::~NetworkStateObserverHandle() =
    default;
DelegatedCapabilityRequestToken::DelegatedCapabilityRequestToken() = default;
void DelegatedCapabilityRequestToken::Activate() {}
bool DelegatedCapabilityRequestToken::IsActive() const {
  return false;
}
bool DelegatedCapabilityRequestToken::ConsumeIfActive() {
  return false;
}
void BackForwardCacheBufferLimitTracker::DidBufferBytes(size_t) {}
BackForwardCacheBufferLimitTracker::BackForwardCacheBufferLimitTracker()
    : max_buffered_bytes_per_process_(0), total_bytes_buffered_(0) {}
BackForwardCacheBufferLimitTracker& BackForwardCacheBufferLimitTracker::Get() {
  static BackForwardCacheBufferLimitTracker* tracker =
      new BackForwardCacheBufferLimitTracker();
  return *tracker;
}
void BackForwardCacheBufferLimitTracker::
    DidRemoveFrameOrWorkerFromBackForwardCache(uint64_t) {}
Fence::Fence(LocalDOMWindow& window) : ExecutionContextClient(&window) {}
CrashReportContext::CrashReportContext(LocalDOMWindow& window)
    : ExecutionContextClient(&window) {}
PolicyValue DocumentPolicy::GetFeatureValue(
    mojom::blink::DocumentPolicyFeature) const {
  return PolicyValue();
}
const std::optional<std::string> DocumentPolicy::GetFeatureEndpoint(
    mojom::blink::DocumentPolicyFeature) const {
  return std::nullopt;
}
void ViewTransitionSupplement::SendOptInStatusToHost() {}
bool ExecutionContext::RequireTrustedTypes() const {
  return false;
}
std::unique_ptr<mojom::blink::PolicyContainerPolicies>
FromWebPolicyContainerPolicies(const WebPolicyContainerPolicies&) {
  return nullptr;
}
LocationReportBody::ReportLocation LocationReportBody::CreateReportLocation(
    const String& file,
    std::optional<uint32_t> line_number,
    std::optional<uint32_t> column_number) {
  return ReportLocation{file, line_number, column_number};
}
LocationReportBody::ReportLocation LocationReportBody::CreateReportLocation(
    SourceLocation*) {
  return ReportLocation{String(), std::nullopt, std::nullopt};
}
void PermissionsPolicyViolationReportBody::BuildJSONValue(
    V8ObjectBuilder&) const {}
const WrapperTypeInfo& DocumentPolicyViolationReportBody::wrapper_type_info_ =
    StandaloneDummyWrapperTypeInfo();
DocumentPolicyViolationReportBody::DocumentPolicyViolationReportBody(
    const String& feature_id,
    const String& message,
    const String& disposition,
    const String&)
    : LocationReportBody(nullptr),
      feature_id_(feature_id),
      message_(message),
      disposition_(disposition) {}
void DocumentPolicyViolationReportBody::BuildJSONValue(
    V8ObjectBuilder&) const {}
unsigned DocumentPolicyViolationReportBody::MatchId() const {
  return 0;
}
unsigned LocationReportBody::MatchId() const {
  return 0;
}
bool LocationReportBody::IsExtensionSource() const {
  return false;
}
void LocationReportBody::BuildJSONValue(V8ObjectBuilder&) const {}
unsigned Report::MatchId() const {
  return body_ ? body_->MatchId() : 0;
}
AuditsIssue::AuditsIssue(AuditsIssue&&) = default;
AuditsIssue::~AuditsIssue() = default;
void InspectorIssueStorage::AddInspectorIssue(ExecutionContext*, AuditsIssue) {}
InspectorIssueStorage::InspectorIssueStorage() = default;
InspectorIssueStorage::~InspectorIssueStorage() = default;
void InspectorIssueStorage::Clear() {}
ReportingContext* ReportingContext::From(ExecutionContext*) {
  return nullptr;
}
namespace probe {
void AsyncTaskContext::Schedule(ExecutionContext*,
                                const StringView&,
                                ScanForAds) {}
AsyncTask::AsyncTask(ExecutionContext*, AsyncTaskContext*, const char*, bool) {}
AsyncTask::~AsyncTask() = default;
}  // namespace probe
String ExceptionMessages::FailedToExecute(const String&,
                                          const char*,
                                          const String&) {
  return String();
}
void Deprecation::CountDeprecationCrossOriginIframe(LocalDOMWindow*,
                                                    mojom::WebFeature) {}
Deprecation::Deprecation() = default;
void Deprecation::ClearSuppression() {}
void AuditsIssue::ReportPartitioningBlobURLIssue(
    LocalDOMWindow*,
    String,
    mojom::blink::PartitioningBlobURLInfo) {}
SourceLocation::~SourceLocation() = default;
SourceLocation::SourceLocation(
    const String& url,
    const String& function,
    unsigned line_number,
    unsigned column_number,
    std::unique_ptr<v8_inspector::V8StackTrace> stack_trace,
    int script_id)
    : url_(url),
      function_(function),
      line_number_(line_number),
      column_number_(column_number),
      char_position_(0),
      stack_trace_(std::move(stack_trace)),
      script_id_(script_id) {}
SourceLocation* CaptureSourceLocation(ExecutionContext*) {
  return MakeGarbageCollected<SourceLocation>(String(), String(), 0, 0,
                                              nullptr, 0);
}
SourceLocation* CaptureSourceLocation() {
  return MakeGarbageCollected<SourceLocation>(String(), String(), 0, 0,
                                              nullptr, 0);
}
void Deprecation::CountDeprecation(ExecutionContext*, mojom::WebFeature) {}
namespace mojom {
std::ostream& operator<<(std::ostream& os, WebFeature feature) {
  return os << static_cast<int>(feature);
}
}  // namespace mojom
void ExecutionContext::AddConsoleMessageImpl(
    mojom::blink::ConsoleMessageSource,
    mojom::blink::ConsoleMessageLevel,
    const String&,
    bool,
    std::optional<mojom::blink::ConsoleMessageCategory>) {}
bool ExecutionContext::FeatureEnabled(mojom::OriginTrialFeature) const {
  return false;
}
void ScriptController::DiscardFrame() {}
void ScriptController::Trace(Visitor*) const {}
void ScriptController::ExecuteJavaScriptURL(const KURL&,
                                            network::mojom::CSPDisposition,
                                            const DOMWrapperWorld*) {}
v8::Isolate* ToIsolate(const LocalFrame*) {
  return nullptr;
}
DOMWrapperWorld* DOMWrapperWorld::EnsureIsolatedWorld(v8::Isolate*, int) {
  return nullptr;
}
void DOMWrapperWorld::Trace(Visitor*) const {}
ScriptState* ToScriptState(LocalFrame*, DOMWrapperWorld&) {
  return nullptr;
}
void PausableScriptExecutor::CreateAndRun(
    ScriptState*,
    Vector<WebScriptSource>,
    ExecuteScriptPolicy,
    mojom::blink::UserActivationOption,
    mojom::blink::EvaluationTiming,
    mojom::blink::LoadEventBlockingOption,
    mojom::blink::WantResultOption,
    mojom::blink::PromiseResultOption,
    WebScriptExecutionCallback callback) {
  if (callback) {
    std::move(callback).Run(std::nullopt, base::TimeTicks());
  }
}
void FrameOrWorkerScheduler::RegisterStickyFeature(SchedulingPolicy::Feature,
                                                   SchedulingPolicy) {}
FrameOrWorkerScheduler::SchedulingAffectingFeatureHandle
FrameOrWorkerScheduler::RegisterFeature(SchedulingPolicy::Feature,
                                        SchedulingPolicy) {
  return SchedulingAffectingFeatureHandle();
}
FrameOrWorkerScheduler::SchedulingAffectingFeatureHandle&
FrameOrWorkerScheduler::SchedulingAffectingFeatureHandle::operator=(
    SchedulingAffectingFeatureHandle&& other) {
  feature_ = other.feature_;
  policy_ = other.policy_;
  scheduler_ = std::move(other.scheduler_);
  return *this;
}
const AtomicString& DocumentLoader::MimeType() const {
  return g_empty_atom;
}
const mojom::RendererContentSettingsPtr&
DocumentLoader::GetContentSettings() {
  static const mojom::RendererContentSettingsPtr* settings =
      new mojom::RendererContentSettingsPtr();
  return *settings;
}
Vector<String> HTMLInputElement::FilesFromFileInputFormControlState(
    const FormControlState&) {
  return Vector<String>();
}
AutofillEvent::AutofillEvent(
    const AtomicString& type,
    HeapVector<std::pair<Member<Element>, String>>,
    const base::UnguessableToken& fill_id,
    bool supports_refill)
    : Event(type, Bubbles::kNo, Cancelable::kNo),
      fill_id_(fill_id),
      supports_refill_(supports_refill) {}
const WrapperTypeInfo& AutofillEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AutofillEvent");
void AutofillEvent::Trace(Visitor* visitor) const {
  Event::Trace(visitor);
}
const AtomicString& AutofillEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}
void KURL::SetQuery(const String&) {}
bool KURL::IsEmpty() const {
  return string_.empty();
}
bool KURL::ProtocolIs(StringView protocol) const {
  return protocol_ == protocol;
}
const HeapVector<Member<ListedElement>>&
HTMLFormElement::CollectAndCacheListedElements(bool) const {
  static ListedElement::List elements;
  return elements;
}
void TopDocumentRootScrollerController::Reset() {}
void RootScrollerController::DidResizeFrameView() {}
Node& RootScrollerController::EffectiveRootScroller() const {
  return *static_cast<Node*>(nullptr);
}
void PaintLayerScrollableArea::RemoveScrollbarsForReconstruction() {}
bool PaintLayerScrollableArea::ShouldPerformScrollAnchoring() const {
  return false;
}
void PaintLayerScrollableArea::SetHasVerticalScrollbar(bool) {}
gfx::Point EmbeddedContentView::Location() const {
  return gfx::Point();
}
void VisualViewport::MainFrameDidChangeSize() {}
Element* DisplayLockUtilities::LockedAncestorPreventingLayout(
    const LayoutObject&) {
  return nullptr;
}
bool DisplayLockUtilities::IsAutoWithoutLayout(const LayoutObject&) {
  return false;
}
void FirstMeaningfulPaintDetector::MarkNextPaintAsMeaningfulIfNeeded(
    const LayoutObjectCounter&,
    double,
    double,
    int) {}
FirstMeaningfulPaintDetector& FirstMeaningfulPaintDetector::From(Document&) {
  static FirstMeaningfulPaintDetector* detector =
      MakeGarbageCollected<FirstMeaningfulPaintDetector>(
          static_cast<PaintTiming*>(nullptr));
  return *detector;
}
void FirstMeaningfulPaintDetector::OnNetwork2Quiet() {}
PaintTiming& PaintTiming::From(Document&) {
  return *static_cast<PaintTiming*>(nullptr);
}
void PaintTiming::MarkFirstEligibleToPaint() {}
void PaintTiming::MarkIneligibleToPaint() {}
void PaintTiming::MarkFirstContentfulPaint() {}
void OverlayInterstitialAdDetector::MaybeFireDetection(LocalFrame*) {}
void StickyAdDetector::MaybeFireDetection(LocalFrame*) {}
ExtensionScriptStreamer::~ExtensionScriptStreamer() = default;
ExtensionScriptStreamer::ExtensionScriptStreamer(
    const ExtensionScriptStreamer&) {}
void ViewTransition::UpdateSnapshotContainingBlockStyle() {}
gfx::Size ViewTransition::GetSnapshotRootSize() const {
  return gfx::Size();
}
gfx::Vector2d ViewTransition::GetFrameToSnapshotRootOffset() const {
  return gfx::Vector2d();
}
LayoutViewTransitionRoot::LayoutViewTransitionRoot(Document&)
    : LayoutBlockFlow(nullptr) {}
LayoutViewTransitionRoot::~LayoutViewTransitionRoot() = default;
bool ViewTransitionStyleTracker::IsTransitionElement(const Element&) const {
  return false;
}
void FrameSelection::CommitAppearanceIfNeeded() {}
bool LayoutSVGText::NeedsTextMetricsUpdate() const {
  return false;
}
bool LayoutSVGRoot::IsEmbeddedThroughSVGImage() const {
  return false;
}
bool LayoutSVGRoot::IsEmbeddedThroughFrameContainingSVGDocument() const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void LayoutListItem::UpdateCounterStyle() {}
void LayoutInlineListItem::UpdateCounterStyle() {}
#endif
void inspector_hit_test_event::EndData(perfetto::TracedValue,
                                       const HitTestRequest&,
                                       const HitTestLocation&,
                                       const HitTestResult&) {}
void AnchorElementViewportPositionTracker::OnScrollEnd() {}
ScrollAnimatorCompositorCoordinator::ScrollAnimatorCompositorCoordinator()
    : element_id_(CompositorElementId()),
      run_state_(RunState::kIdle),
      impl_only_animation_takeover_(false),
      compositor_animation_id_(0),
      compositor_animation_group_id_(0) {}
CompositorAnimationClient::~CompositorAnimationClient() = default;
ScrollAnimatorCompositorCoordinator::~ScrollAnimatorCompositorCoordinator() =
    default;
bool ScrollAnimatorCompositorCoordinator::HasAnimationThatRequiresService()
    const {
  return false;
}
void ScrollAnimatorCompositorCoordinator::Dispose() {}
String ScrollAnimatorCompositorCoordinator::RunStateAsText() const {
  return String();
}
void ScrollAnimatorCompositorCoordinator::DetachElement() {}
void ScrollAnimatorCompositorCoordinator::ResetAnimationState() {}
void ScrollAnimatorCompositorCoordinator::CancelAnimation() {}
void ScrollAnimatorCompositorCoordinator::TakeOverCompositorAnimation() {}
void ScrollAnimatorCompositorCoordinator::UpdateCompositorAnimations() {}
void ScrollAnimatorCompositorCoordinator::ScrollOffsetChanged(
    const ScrollOffset&,
    mojom::blink::ScrollType,
    cc::ScrollSourceType) {}
void ScrollAnimatorCompositorCoordinator::AdjustImplOnlyScrollOffsetAnimation(
    const gfx::Vector2d&) {}
bool ScrollAnimatorCompositorCoordinator::AddAnimation(
    std::unique_ptr<cc::KeyframeModel>) {
  return false;
}
void ScrollAnimatorCompositorCoordinator::RemoveAnimation() {}
void ScrollAnimatorCompositorCoordinator::AbortAnimation() {}
gfx::PointF ScrollAnimatorCompositorCoordinator::CompositorOffsetFromBlinkOffset(
    ScrollOffset offset) {
  return gfx::PointF(offset.x(), offset.y());
}
ScrollOffset ScrollAnimatorCompositorCoordinator::BlinkOffsetFromCompositorOffset(
    gfx::PointF offset) {
  return ScrollOffset(offset.x(), offset.y());
}
void ScrollAnimatorCompositorCoordinator::CompositorAnimationFinished(int) {}
bool ScrollAnimatorCompositorCoordinator::ReattachCompositorAnimationIfNeeded(
    cc::AnimationTimeline*) {
  return false;
}
void ScrollAnimatorCompositorCoordinator::NotifyAnimationStarted(
    base::TimeDelta,
    int) {}
void ScrollAnimatorCompositorCoordinator::NotifyAnimationFinished(
    base::TimeDelta,
    int) {}
void ScrollAnimatorCompositorCoordinator::NotifyAnimationAborted(
    base::TimeDelta,
    int) {}
CompositorAnimation*
ScrollAnimatorCompositorCoordinator::GetCompositorAnimation() const {
  return nullptr;
}
ProgrammaticScrollAnimator::ProgrammaticScrollAnimator(
    ScrollableArea* scrollable_area)
    : scrollable_area_(scrollable_area),
      source_type_(cc::ScrollSourceType::kNone) {}
ProgrammaticScrollAnimator::~ProgrammaticScrollAnimator() = default;
void ProgrammaticScrollAnimator::ScrollToOffsetWithoutAnimation(
    const ScrollOffset& offset,
    cc::ScrollSourceType source_type) {
  target_offset_ = offset;
  source_type_ = source_type;
}
void ProgrammaticScrollAnimator::AnimateToOffset(
    const ScrollOffset& offset,
    cc::ScrollSourceType source_type,
    ScrollableArea::ScrollCallback) {
  ScrollToOffsetWithoutAnimation(offset, source_type);
}
void ProgrammaticScrollAnimator::ResetAnimationState() {}
void ProgrammaticScrollAnimator::CancelAnimation() {}
void ProgrammaticScrollAnimator::TickAnimation(base::TimeTicks) {}
void ProgrammaticScrollAnimator::UpdateCompositorAnimations() {}
void ProgrammaticScrollAnimator::NotifyCompositorAnimationFinished(int) {}
void ProgrammaticScrollAnimator::Trace(Visitor* visitor) const {
  visitor->Trace(scrollable_area_);
}
ScrollAnimatorBase* ScrollAnimatorBase::Create(ScrollableArea* scrollable_area) {
  return MakeGarbageCollected<ScrollAnimatorBase>(scrollable_area);
}
SynthesizedClip& PaintArtifactCompositor::CreateOrReuseSynthesizedClipLayer(
    const ClipPaintPropertyNode&,
    const TransformPaintPropertyNode&,
    bool,
    CompositorElementId&,
    CompositorElementId&) {
  return *static_cast<SynthesizedClip*>(nullptr);
}
bool PaintArtifactCompositor::NeedsCompositedScrolling(
    const TransformPaintPropertyNode&) const {
  return false;
}
bool PaintArtifactCompositor::ShouldForceMainThreadRepaint(
    const TransformPaintPropertyNode&) const {
  return false;
}
ExceptionState::ExceptionState(DummyExceptionStateForTesting&)
    : context_(kEmptyContext), isolate_(nullptr) {}
String LogicalOffset::ToString() const {
  return String();
}
DarkModeImageClassifier::~DarkModeImageClassifier() = default;
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintUnderInvalidationChecker::~PaintUnderInvalidationChecker() = default;
#endif
ElementDataCache::ElementDataCache() = default;
void DocumentAnimations::MarkAnimationsCompositorPending() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void ViewTransitionUtils::ForEachTransition(
    const Document&,
    base::FunctionRef<void(ViewTransition&)>) {}
#endif
void ViewTransition::RunViewTransitionStepsDuringMainFrame() {}
void ViewTransition::RunViewTransitionStepsOutsideMainFrame() {}
ResizeObserverController* ResizeObserverController::From(LocalDOMWindow&) {
  return nullptr;
}
ResizeObserver::ResizeObserver(Delegate* delegate, LocalDOMWindow*)
    : ActiveScriptWrappable<ResizeObserver>({}),
      ExecutionContextClient(nullptr),
      callback_(nullptr),
      delegate_(delegate),
      skipped_observations_(false) {}
const WrapperTypeInfo& ResizeObserver::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("ResizeObserver");
bool ResizeObserver::HasPendingActivity() const {
  return false;
}
bool IsContextDestroyedForActiveScriptWrappable(const ExecutionContext*) {
  return true;
}
bool TestableBrowserInterfaceBrokerProxy::SetBinderForTesting(
    const std::string&,
    TestBinder) const {
  return false;
}
bool WebTestSupport::IsRunningWebTest() {
  return false;
}
BrowserInterfaceBrokerProxy& GetEmptyBrowserInterfaceBroker() {
  static BrowserInterfaceBrokerProxy* broker =
      static_cast<BrowserInterfaceBrokerProxy*>(nullptr);
  return *broker;
}
const String GetNameForFeature(network::mojom::PermissionsPolicyFeature,
                               bool) {
  return String();
}
const base::flat_map<mojom::blink::DocumentPolicyFeature,
                     DocumentPolicyFeatureInfo>&
GetDocumentPolicyFeatureInfoMap() {
  static base::flat_map<mojom::blink::DocumentPolicyFeature,
                        DocumentPolicyFeatureInfo>* map =
      new base::flat_map<mojom::blink::DocumentPolicyFeature,
                         DocumentPolicyFeatureInfo>();
  return *map;
}
void HighlightRegistry::ValidateHighlightMarkers() {}
const char HighlightRegistry::kSupplementName[] = "HighlightRegistry";
NoStatePrefetchClient* NoStatePrefetchClient::From(Page*) {
  return nullptr;
}
DocumentFencedFrames* DocumentFencedFrames::Get(Document&) {
  return nullptr;
}
InteractiveDetector* InteractiveDetector::From(Document&) {
  return nullptr;
}
void InteractiveDetector::OnPageHiddenChanged(bool) {}
RenderBlockingMetricsReporter& RenderBlockingMetricsReporter::From(
    Document& document) {
  static RenderBlockingMetricsReporter* reporter = nullptr;
  if (!reporter) {
    reporter = MakeGarbageCollected<RenderBlockingMetricsReporter>(document);
  }
  return *reporter;
}
RenderBlockingMetricsReporter::RenderBlockingMetricsReporter(Document& document)
    : Supplement<Document>(document) {}
void RenderBlockingMetricsReporter::RenderBlockingResourcesLoaded() {}
void RenderBlockingMetricsReporter::Trace(Visitor*) const {}
TaskHandle PostCancellableTask(base::SequencedTaskRunner&,
                               const base::Location&,
                               base::OnceClosure) {
  return TaskHandle();
}
CaretPosition::CaretPosition(Node* node, unsigned offset)
    : node_(node), offset_(offset) {}
void CaretPosition::Trace(Visitor* visitor) const {
  visitor->Trace(node_);
}
void CallbackInterfaceBase::Trace(Visitor*) const {}
FrameRequestCallbackCollection::FrameRequestCallbackCollection(
    ExecutionContext*) {}
RenderBlockingElementLinkMap::RenderBlockingElementLinkMap(
    RenderBlockingElementSetEmtpyCallback callback)
    : on_blocking_elements_empty_(std::move(callback)) {}
RenderBlockingElementLinkMap::~RenderBlockingElementLinkMap() = default;
void RenderBlockingElementLinkMap::Trace(Visitor*) const {}
void RenderBlockingResourceManager::FontPreloadingTimerFired(TimerBase*) {}
PreferenceManager* NavigatorPreferences::preferences(Navigator&) {
  return nullptr;
}
void PreferenceManager::PreferenceMaybeChanged() {}
void MediaFeatureOverrides::SetOverride(const AtomicString&,
                                        const String&,
                                        const Document*) {}
void PreferenceOverrides::SetOverride(const AtomicString&,
                                      const String&,
                                      const Document*) {}
void PaintLayerScrollableArea::SetTickmarksOverride(Vector<gfx::Rect>) {}
void Scrollbar::SetNeedsPaintInvalidation(ScrollbarPart) {}
AnchorScopedName* ToAnchorScopedName(const ScopedCSSName&,
                                     const LayoutObject&) {
  return nullptr;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const LayoutObject* AnchorMap::AnchorLayoutObject(
    const LayoutBox&,
    const std::variant<const NamingScope*, const Element*>&) const {
  return nullptr;
}
#endif
void DisplayLockContext::SetAnchorPositioningRenderStateMayHaveChanged() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void ShapeOutsideInfo::Trace(Visitor*) const {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const PhysicalFragment* PhysicalFragment::PostLayout() const {
  return this;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
#if !defined(HTML_CSS_RENDERER_STANDALONE)
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const BlockBreakToken* FindPreviousBreakToken(const PhysicalBoxFragment&) {
  return nullptr;
}
#endif
#endif
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void LayoutResult::Trace(Visitor*) const {}
#endif
bool CSSValue::HasFailedOrCanceledSubresources() const {
  return false;
}
bool CSSValue::MayContainUrl() const {
  return false;
}
void CSSValue::ReResolveUrl(const Document&) const {}
bool HTMLInputElement::IsButton() const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
Text* LayoutTextFragment::AssociatedTextNode() const {
  return nullptr;
}
#endif
 #if !defined(HTML_CSS_RENDERER_STANDALONE)
const LayoutBox* PhysicalBoxFragment::OwnerLayoutBox() const {
  return nullptr;
}
#endif
LayoutBox* LayoutFieldset::FindInFlowLegend(const LayoutBlock&) {
  return nullptr;
}
bool HTMLSummaryElement::IsMainSummary() const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
ListMarker::ListStyleCategory ListMarker::GetListStyleCategory(
    Document&,
    const ComputedStyle&) {
  return ListStyleCategory::kNone;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PaintLayer::AddChild(PaintLayer*, PaintLayer*) {}
void PaintLayer::RemoveChild(PaintLayer*) {}
void PaintLayer::SetNeedsVisualOverflowRecalc() {}
void PaintLayer::SetNeedsRepaint() {}
#endif
bool Font::IsFallbackValid() const {
  return true;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
HarfBuzzFace* FontPlatformData::GetHarfBuzzFace() const {
  return nullptr;
}
#endif
#if defined(HTML_CSS_RENDERER_STANDALONE)
HarfBuzzFace* FontPlatformData::GetHarfBuzzFace() const {
  if (!harfbuzz_face_) {
    harfbuzz_face_ = MakeGarbageCollected<HarfBuzzFace>(this, UniqueID());
  }
  return harfbuzz_face_.Get();
}
#endif
bool OpenTypeMathSupport::HasMathData(const HarfBuzzFace*) {
  return false;
}
std::optional<float> OpenTypeMathSupport::MathConstant(
    const HarfBuzzFace*,
    MathConstants) {
  return std::nullopt;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool CompositorFilterOperations::IsEmpty() const {
  return true;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
gfx::Transform GeometryMapper::SourceToDestinationProjection(
    const TransformPaintPropertyNode&,
    const TransformPaintPropertyNode&) {
  return gfx::Transform();
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PropertyTreeStateOrAlias FragmentData::LocalBorderBoxPropertiesFallback()
    const {
  return PropertyTreeStateOrAlias(
      TransformPaintPropertyNode::Root(), ClipPaintPropertyNode::Root(),
      EffectPaintPropertyNode::Root());
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
String QualifiedName::ToString() const {
  return LocalName().GetString();
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintInvalidationReason
ObjectPaintInvalidatorWithContext::ComputePaintInvalidationReason() {
  return PaintInvalidationReason::kNone;
}
void ObjectPaintInvalidator::SlowSetPaintingLayerNeedsRepaint() {}
void ObjectPaintInvalidator::InvalidateDisplayItemClient(
    const DisplayItemClient&,
    PaintInvalidationReason) {}
void ObjectPaintInvalidatorWithContext::InvalidatePaintWithComputedReason(
    PaintInvalidationReason) {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool GeometryMapper::LocalToAncestorVisualRect(
    const PropertyTreeState&,
    const PropertyTreeState&,
    FloatClipRect&,
    OverlayScrollbarClipBehavior,
    VisualRectFlags) {
  return false;
}
bool GeometryMapper::LocalToLocalRootViewportRect(
    const PropertyTreeState&,
    FloatClipRect&,
    OverlayScrollbarClipBehavior,
    VisualRectFlags) {
  return false;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
std::ostream& operator<<(std::ostream& os, PaintInvalidationReason reason) {
  return os << static_cast<int>(reason);
}
#endif
std::ostream& operator<<(std::ostream& os, TextAffinity affinity) {
  return os << static_cast<int>(affinity);
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const EffectPaintPropertyNodeOrAlias& FragmentData::ContentsEffect() const {
  return *static_cast<const EffectPaintPropertyNodeOrAlias*>(nullptr);
}
const ClipPaintPropertyNodeOrAlias& FragmentData::ContentsClip() const {
  return *static_cast<const ClipPaintPropertyNodeOrAlias*>(nullptr);
}
const TransformPaintPropertyNodeOrAlias& FragmentData::ContentsTransform()
    const {
  return *static_cast<const TransformPaintPropertyNodeOrAlias*>(nullptr);
}
#endif
HitTestResult::HitTestResult()
    : hit_test_request_(0),
      cacheable_(true),
      is_over_embedded_content_view_(false),
      is_over_resizer_(false),
      is_over_scroll_corner_(false) {}
bool LayoutSelection::IsSelected(const LayoutObject&) {
  return false;
}
void StyleAdjuster::AdjustStyleForCombinedText(ComputedStyleBuilder&) {}
void StyleAdjuster::AdjustStyleForTextCombine(ComputedStyleBuilder&) {}
const HeapVector<Member<Element>>& OverscrollAreaTracker::DOMSortedElements() {
  return *static_cast<const HeapVector<Member<Element>>*>(nullptr);
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void FragmentData::RareData::Trace(Visitor*) const {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
String FontCache::FirstAvailableOrFirst(const String& families) {
  return families;
}
#endif
#if defined(HTML_CSS_RENDERER_STANDALONE)
String FontCache::FirstAvailableOrFirst(const String& families) {
  return families;
}
#endif
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
CSSStyleValue* StyleValueFactory::CssValueToStyleValue(
    const CSSPropertyName&,
    const CSSValue&) {
  return nullptr;
}
CSSStyleValueVector StyleValueFactory::CssValueToStyleValueVector(
    const CSSPropertyName&,
    const CSSValue&) {
  return CSSStyleValueVector();
}
CSSStyleValueVector StyleValueFactory::CssValueToStyleValueVector(
    const CSSValue&) {
  return CSSStyleValueVector();
}
void PaintTimingDetector::ReportIgnoredContent() {}
void PaintTimingDetector::NotifyImageFinished(const LayoutObject&,
                                              const MediaTiming*) {}
void PaintTimingDetector::NotifyImageRemoved(const LayoutObject&,
                                             const ImageResourceContent*) {}
ImageElementTiming& ImageElementTiming::From(LocalDOMWindow&) {
  return *static_cast<ImageElementTiming*>(nullptr);
}
void ImageElementTiming::NotifyImageFinished(const LayoutObject&,
                                             const ImageResourceContent*) {}
void ImageElementTiming::NotifyImageRemoved(const LayoutObject*,
                                            const ImageResourceContent*) {}
bool ImageResourceContent::ErrorOccurred() const {
  return false;
}
bool ImageResourceContent::LoadFailedOrCanceled() const {
  return false;
}
const std::optional<AdProvenance>& ImageResourceContent::GetAdProvenance()
    const {
  static std::optional<AdProvenance>* provenance =
      new std::optional<AdProvenance>();
  return *provenance;
}
bool Sanitizer::ShouldReplaceNodeWithChildren(Node*) const {
  return false;
}
Sanitizer::Action Sanitizer::SanitizeSingleNode(Node*, Mode) const {
  return Action::kKeep;
}
CustomElementRegistry* CustomElementRegistry::DefaultRegistry(Document&) {
  return nullptr;
}
void CustomElementRegistry::Trace(Visitor*) const {}
void HTMLFormElement::Trace(Visitor* visitor) const {
  HTMLElement::Trace(visitor);
}
WebNavigationParams::~WebNavigationParams() = default;
std::unique_ptr<WebNavigationParams>
WebNavigationParams::CreateWithEmptyHTMLForTesting(const WebURL&) {
  return nullptr;
}
FramePolicy::~FramePolicy() = default;
void WebHTTPBody::Reset() {}
void FrameLoader::CommitNavigation(
    std::unique_ptr<WebNavigationParams>,
    std::unique_ptr<WebDocumentLoader::ExtraData>,
    CommitReason) {}
void DocumentLoader::DisableCodeCacheForTesting() {}
void test::RunPendingTasks() {}
bool ScrollbarThemeSettings::MockScrollbarsEnabled() {
  return false;
}
bool ScrollbarThemeSettings::OverlayScrollbarsEnabled() {
  return false;
}
void ScrollbarThemeSettings::SetOverlayScrollbarsEnabled(bool) {
}
void ScrollbarThemeSettings::SetMockScrollbarsEnabled(bool) {
}
MainThread* Thread::MainThread() {
  return &StandaloneMainThread();
}
void VisualViewport::SetSize(const gfx::Size&) {}
URLLoaderMockFactory* URLLoaderMockFactory::GetSingletonInstance() {
  return nullptr;
}
const ui::Cursor& PointerCursor() {
  static ui::Cursor* cursor = new ui::Cursor();
  return *cursor;
}
ResourceLoadInfoNotifierWrapper::ResourceLoadInfoNotifierWrapper(
    base::WeakPtr<WeakWrapperResourceLoadInfoNotifier>)
    : weak_wrapper_resource_load_info_notifier_(nullptr), task_runner_(nullptr) {}
ResourceLoadInfoNotifierWrapper::ResourceLoadInfoNotifierWrapper(
    base::WeakPtr<WeakWrapperResourceLoadInfoNotifier>,
    scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : weak_wrapper_resource_load_info_notifier_(nullptr),
      task_runner_(std::move(task_runner)) {}
ResourceLoadInfoNotifierWrapper::~ResourceLoadInfoNotifierWrapper() = default;
WindowPerformance* DOMWindowPerformance::performance(LocalDOMWindow&) {
  return nullptr;
}
void WindowPerformance::WillShowModalDialog() {}
namespace probe {
void WillRunJavaScriptDialog(LocalFrame*) {}
void DidRunJavaScriptDialog(LocalFrame*) {}
}  // namespace probe
ScrollbarTheme& ScrollbarTheme::GetTheme() {
  return *static_cast<ScrollbarTheme*>(nullptr);
}
void ScrollbarTheme::PaintScrollCorner(const PaintInfo&,
                                       const ScrollableArea&,
                                       const DisplayItemClient&,
                                       const gfx::Rect&) {}
void ScrollbarTheme::PaintTickmarks(const PaintInfo&,
                                    const Scrollbar&,
                                    const gfx::Rect&) {}
int ScrollbarTheme::ThumbPosition(const Scrollbar&, float) const {
  return 0;
}
base::TimeDelta ScrollbarTheme::OverlayScrollbarFadeOutDelay() const {
  return base::TimeDelta();
}
base::TimeDelta ScrollbarTheme::OverlayScrollbarFadeOutDuration() const {
  return base::TimeDelta();
}
int ScrollbarTheme::TrackPosition(const Scrollbar&) const {
  return 0;
}
int ScrollbarTheme::TrackLength(const Scrollbar&) const {
  return 0;
}
gfx::Rect ScrollbarTheme::ThumbRect(const Scrollbar&) const {
  return gfx::Rect();
}
void ScrollbarTheme::SplitTrack(const Scrollbar&,
                                const gfx::Rect& track,
                                gfx::Rect& start_track,
                                gfx::Rect& thumb_track,
                                gfx::Rect& end_track) const {
  start_track = gfx::Rect();
  thumb_track = track;
  end_track = gfx::Rect();
}
base::TimeDelta ScrollbarTheme::InitialAutoscrollTimerDelay() const {
  return base::TimeDelta();
}
base::TimeDelta ScrollbarTheme::AutoscrollTimerDelay() const {
  return base::TimeDelta();
}
ScrollbarPart ScrollbarTheme::HitTest(const Scrollbar&,
                                      const gfx::Point&) const {
  return kNoPart;
}
void ScrollbarTheme::PaintTrackBackgroundAndButtons(const PaintInfo&,
                                                    const Scrollbar&,
                                                    const gfx::Rect&) {}
ScrollbarThemeOverlayMobile& ScrollbarThemeOverlayMobile::GetInstance() {
  return *static_cast<ScrollbarThemeOverlayMobile*>(nullptr);
}
void ActiveScriptWrappableBase::RegisterActiveScriptWrappable() {}
XMLErrors::XMLErrors(Document* document)
    : document_(document),
      error_count_(0),
      last_error_position_(TextPosition::MinimumPosition()) {}
void XMLErrors::Trace(Visitor* visitor) const {
  visitor->Trace(document_);
}
XMLParserContext::~XMLParserContext() = default;
void XMLParserScriptRunner::Trace(Visitor*) const {}
WorkletAnimationController::~WorkletAnimationController() = default;
void WorkletAnimationController::SynchronizeAnimatorName(const String&) {}
void WorkletAnimationController::SetMutationUpdate(
    std::unique_ptr<AnimationWorkletOutput>) {}
CookieJar::~CookieJar() = default;
void ScriptRunner::PendingScriptFinished(PendingScript*) {}
void ScriptedAnimationController::Trace(Visitor*) const {}
void ScriptedAnimationController::ContextLifecycleStateChanged(
    mojom::blink::FrameLifecycleState) {}
void FragmentDirective::Trace(Visitor* visitor) const {
  visitor->Trace(directives_);
  visitor->Trace(owner_document_);
}
const AtomicString& http_names::kLastModified =
    *new AtomicString("Last-Modified");
const AtomicString event_interface_names::kErrorEvent("ErrorEvent");
const AtomicString event_interface_names::kHashChangeEvent("HashChangeEvent");

}  // namespace blink

namespace blink::scheduler {
EventLoop::~EventLoop() = default;
void EventLoop::EnqueueMicrotask(base::OnceCallback<void()>) {}
std::unique_ptr<FrameScheduler> CreateDummyFrameScheduler(v8::Isolate*) {
  return nullptr;
}
}  // namespace blink::scheduler

namespace cc {
ViewTransitionRequest::~ViewTransitionRequest() = default;
ScopedRequestHighFramerate::~ScopedRequestHighFramerate() = default;
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintOpBuffer::PaintOpBuffer() = default;
PaintOpBuffer::~PaintOpBuffer() = default;
const PaintImage::Id PaintImage::kInvalidId = 0;
const PaintImage::ContentId PaintImage::kInvalidContentId = 0;
PaintImage::PaintImage() = default;
PaintRecord::~PaintRecord() = default;
PaintImage::~PaintImage() = default;
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
SkottieTextPropertyValue::~SkottieTextPropertyValue() = default;
#endif
std::string MainThreadScrollingReason::AsText(uint32_t) {
  return std::string();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintRecord::PaintRecord() = default;
RecordPaintCanvas::RecordPaintCanvas() = default;
RecordPaintCanvas::~RecordPaintCanvas() = default;
PaintRecord RecordPaintCanvas::ReleaseAsRecord() {
  return PaintRecord();
}
PaintRecord RecordPaintCanvas::CopyAsRecord() {
  return PaintRecord();
}
void* RecordPaintCanvas::accessTopLayerPixels(SkImageInfo*,
                                              size_t*,
                                              SkIPoint*) {
  return nullptr;
}
void RecordPaintCanvas::flush() {}
bool RecordPaintCanvas::NeedsFlush() const {
  return false;
}
int RecordPaintCanvas::save() {
  return 1;
}
int RecordPaintCanvas::saveLayer(const PaintFlags&) {
  return 1;
}
int RecordPaintCanvas::saveLayer(const SkRect&, const PaintFlags&) {
  return 1;
}
int RecordPaintCanvas::saveLayerAlphaf(float) {
  return 1;
}
int RecordPaintCanvas::saveLayerAlphaf(const SkRect&, float) {
  return 1;
}
int RecordPaintCanvas::saveLayerFilters(base::span<const sk_sp<PaintFilter>>,
                                        const PaintFlags&) {
  return 1;
}
void RecordPaintCanvas::restore() {}
int RecordPaintCanvas::getSaveCount() const {
  return 1;
}
void RecordPaintCanvas::restoreToCount(int) {}
void RecordPaintCanvas::translate(SkScalar, SkScalar) {}
void RecordPaintCanvas::scale(SkScalar, SkScalar) {}
void RecordPaintCanvas::rotate(SkScalar) {}
void RecordPaintCanvas::concat(const SkM44&) {}
void RecordPaintCanvas::setMatrix(const SkM44&) {}
void RecordPaintCanvas::clipRect(const SkRect&, SkClipOp, bool) {}
void RecordPaintCanvas::clipRRect(const SkRRect& rrect,
                                  SkClipOp op,
                                  bool antialias) {
  clipRRectInternal(rrect, op, antialias);
}
void RecordPaintCanvas::clipPath(const SkPath& path,
                                 SkClipOp op,
                                 bool antialias,
                                 UsePaintCache use_paint_cache) {
  clipPathInternal(path, op, antialias, use_paint_cache);
}
void RecordPaintCanvas::clipRRectInternal(const SkRRect&, SkClipOp, bool) {}
void RecordPaintCanvas::clipPathInternal(const SkPath&,
                                         SkClipOp,
                                         bool,
                                         UsePaintCache) {}
SkImageInfo RecordPaintCanvas::imageInfo() const {
  return SkImageInfo::MakeUnknown();
}
bool RecordPaintCanvas::getLocalClipBounds(SkRect*) const {
  return false;
}
bool RecordPaintCanvas::getDeviceClipBounds(SkIRect*) const {
  return false;
}
SkM44 RecordPaintCanvas::getLocalToDevice() const {
  return SkM44();
}
void RecordPaintCanvas::drawColor(SkColor4f, SkBlendMode) {}
void RecordPaintCanvas::clear(SkColor4f) {}
void RecordPaintCanvas::drawLine(SkScalar,
                                 SkScalar,
                                 SkScalar,
                                 SkScalar,
                                 const PaintFlags&) {}
void RecordPaintCanvas::drawArc(const SkRect&,
                                SkScalar,
                                SkScalar,
                                const PaintFlags&) {}
void RecordPaintCanvas::drawRect(const SkRect&, const PaintFlags&) {}
void RecordPaintCanvas::drawIRect(const SkIRect&, const PaintFlags&) {}
void RecordPaintCanvas::drawOval(const SkRect&, const PaintFlags&) {}
void RecordPaintCanvas::drawRRect(const SkRRect&, const PaintFlags&) {}
void RecordPaintCanvas::drawDRRect(const SkRRect&,
                                   const SkRRect&,
                                   const PaintFlags&) {}
void RecordPaintCanvas::drawRoundRect(const SkRect&,
                                      SkScalar,
                                      SkScalar,
                                      const PaintFlags&) {}
void RecordPaintCanvas::drawPath(const SkPath&,
                                 const PaintFlags&,
                                 UsePaintCache) {}
void RecordPaintCanvas::drawImage(const PaintImage&,
                                  SkScalar,
                                  SkScalar,
                                  const SkSamplingOptions&,
                                  const PaintFlags*) {}
void RecordPaintCanvas::drawImageRect(const PaintImage&,
                                      const SkRect&,
                                      const SkRect&,
                                      const SkSamplingOptions&,
                                      const PaintFlags*,
                                      SkCanvas::SrcRectConstraint) {}
void RecordPaintCanvas::drawVertices(scoped_refptr<RefCountedBuffer<SkPoint>>,
                                     scoped_refptr<RefCountedBuffer<SkPoint>>,
                                     scoped_refptr<RefCountedBuffer<uint16_t>>,
                                     const PaintFlags&) {}
void RecordPaintCanvas::drawSkottie(scoped_refptr<SkottieWrapper>,
                                    const SkRect&,
                                    float,
                                    SkottieFrameDataMap,
                                    const SkottieColorMap&,
                                    SkottieTextPropertyValueMap) {}
void RecordPaintCanvas::drawTextBlob(sk_sp<SkTextBlob>,
                                     SkScalar,
                                     SkScalar,
                                     const PaintFlags&) {}
void RecordPaintCanvas::drawTextBlob(sk_sp<SkTextBlob>,
                                     SkScalar,
                                     SkScalar,
                                     NodeId,
                                     const PaintFlags&) {}
void RecordPaintCanvas::drawPicture(PaintRecord) {}
void RecordPaintCanvas::drawPicture(PaintRecord, bool) {}
void RecordPaintCanvas::Annotate(AnnotationType,
                                 const SkRect&,
                                 sk_sp<SkData>) {}
void RecordPaintCanvas::recordCustomData(uint32_t) {}
void RecordPaintCanvas::setNodeId(int) {}
#endif
void AnimationHost::SetAnimationCounts(size_t) {}
bool Layer::IsMainThread() const {
  return true;
}
bool LayerTreeHost::IsMainThread() const {
  return true;
}
}  // namespace cc

namespace gfx {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool Rect::Intersects(const Rect&) const {
  return false;
}
bool Rect::Contains(const Rect& other) const {
  return other.x() >= x() && other.y() >= y() && other.right() <= right() &&
         other.bottom() <= bottom();
}
void Rect::Offset(const Vector2d& offset) {
  set_x(x() + offset.x());
  set_y(y() + offset.y());
}
void Rect::Union(const Rect& other) {
  if (IsEmpty()) {
    *this = other;
    return;
  }
  if (other.IsEmpty()) {
    return;
  }
  int new_x = std::min(x(), other.x());
  int new_y = std::min(y(), other.y());
  int new_right = std::max(right(), other.right());
  int new_bottom = std::max(bottom(), other.bottom());
  SetRect(new_x, new_y, new_right - new_x, new_bottom - new_y);
}
void Rect::AdjustForSaturatedBottom(int bottom) {
  set_height(bottom - y());
}
void Rect::AdjustForSaturatedRight(int right) {
  set_width(right - x());
}
#endif
void Vector2d::Add(const Vector2d& other) {
  set_x(x() + other.x());
  set_y(y() + other.y());
}
void Vector2d::Subtract(const Vector2d& other) {
  set_x(x() - other.x());
  set_y(y() - other.y());
}
bool Vector2d::IsZero() const {
  return x() == 0 && y() == 0;
}
std::string Vector2d::ToString() const {
  return std::to_string(x()) + "," + std::to_string(y());
}
Vector2d operator-(const Vector2d& vector) {
  return Vector2d(-vector.x(), -vector.y());
}
Vector2d ToRoundedVector2d(const Vector2dF& vector) {
  return Vector2d(static_cast<int>(std::round(vector.x())),
                  static_cast<int>(std::round(vector.y())));
}
Vector2d ToFlooredVector2d(const Vector2dF& vector) {
  return Vector2d(static_cast<int>(std::floor(vector.x())),
                  static_cast<int>(std::floor(vector.y())));
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
Size ScaleToFlooredSize(const Size& size, float scale) {
  return Size(static_cast<int>(std::floor(size.width() * scale)),
              static_cast<int>(std::floor(size.height() * scale)));
}
Size ToRoundedSize(const SizeF& size) {
  return Size(static_cast<int>(std::round(size.width())),
              static_cast<int>(std::round(size.height())));
}
base::CheckedNumeric<int> Size::GetCheckedArea() const {
  return base::CheckMul(width(), height());
}
Point ToFlooredPoint(const PointF& point) {
  return Point(static_cast<int>(std::floor(point.x())),
               static_cast<int>(std::floor(point.y())));
}
#endif
DisplayColorSpaces::DisplayColorSpaces() = default;
DisplayColorSpaces::DisplayColorSpaces(const DisplayColorSpaces&) = default;
Quaternion Quaternion::FromAxisAngle(double x, double y, double z, double w) {
  return Quaternion(x, y, z, w);
}
Quaternion Quaternion::Slerp(const Quaternion&, double) const {
  return *this;
}
}  // namespace gfx

namespace ui {
Cursor::Cursor() = default;
Cursor::Cursor(const Cursor& cursor)
    : type_(cursor.type_),
      platform_cursor_(cursor.platform_cursor_),
      custom_hotspot_(cursor.custom_hotspot_),
      image_scale_factor_(cursor.image_scale_factor_) {}
Cursor::~Cursor() = default;
const SkBitmap& Cursor::custom_bitmap() const {
  static SkBitmap* bitmap = new SkBitmap();
  return *bitmap;
}
float Cursor::image_scale_factor() const {
  return 1.0f;
}
std::unique_ptr<ColorProvider> CreateEmulatedForcedColorsColorProvider(bool) {
  return std::make_unique<ColorProvider>();
}
std::unique_ptr<ColorProvider> CreateDefaultColorProviderForBlink(bool) {
  return std::make_unique<ColorProvider>();
}
base::flat_map<color::mojom::RendererColorId, SkColor>
GetDefaultBlinkColorProviderColorMaps(bool, bool) {
  return {{static_cast<color::mojom::RendererColorId>(0), SK_ColorBLACK}};
}
bool IsRendererColorMappingEquivalent(
    const ColorProvider* color_provider,
    const base::flat_map<color::mojom::RendererColorId, SkColor>&) {
  return color_provider != nullptr;
}
std::unique_ptr<ColorProvider> CreateColorProviderFromRendererColorMap(
    const base::flat_map<color::mojom::RendererColorId, SkColor>&) {
  return std::make_unique<ColorProvider>();
}
std::unique_ptr<ColorProvider> CreateEmulatedForcedColorsColorProviderForTest() {
  return std::make_unique<ColorProvider>();
}
ColorProvider::ColorProvider() = default;
ColorProvider::~ColorProvider() = default;
SkColor ColorProvider::GetColor(ColorId) const {
  return SK_ColorBLACK;
}
ColorMixer::~ColorMixer() = default;
ColorRecipe::~ColorRecipe() = default;
ColorTransform::~ColorTransform() = default;
NativeTheme* NativeTheme::GetInstanceForWeb() {
  return nullptr;
}
float NativeTheme::AdjustBorderRadiusByZoom(Part, float border_radius, float) {
  return border_radius;
}
float NativeTheme::AdjustBorderWidthByZoom(float border_width, float) {
  return border_width;
}
}  // namespace ui

namespace display {
ScreenInfo::ScreenInfo() = default;
ScreenInfo::ScreenInfo(const ScreenInfo& other) = default;
ScreenInfo::~ScreenInfo() = default;
ScreenInfos::ScreenInfos() = default;
ScreenInfos::ScreenInfos(const ScreenInfo& screen_info)
    : screen_infos({screen_info}), current_display_id(screen_info.display_id) {}
ScreenInfos::~ScreenInfos() = default;
const ScreenInfo& ScreenInfos::current() const {
  static ScreenInfo* fallback = new ScreenInfo();
  for (const ScreenInfo& screen : screen_infos) {
    if (screen.display_id == current_display_id) {
      return screen;
    }
  }
  return screen_infos.empty() ? *fallback : screen_infos.front();
}
}  // namespace display

namespace v8::internal {
class EmbedderState {};
void CopyTracedReference(const Address* const*, Address**) {}
void DisposeTracedReference(Address*) {}
Address* GlobalizeTracedReference(Isolate*,
                                  Address,
                                  Address* slot,
                                  TracedReferenceStoreMode,
                                  TracedReferenceHandling) {
  return slot;
}
}  // namespace v8::internal

#if !defined(HTML_CSS_RENDERER_STANDALONE)
SkBitmap::SkBitmap() = default;
SkBitmap::~SkBitmap() = default;
SkColorInfo::~SkColorInfo() = default;
SkColorInfo::SkColorInfo(SkColorType color_type,
                         SkAlphaType alpha_type,
                         sk_sp<SkColorSpace> color_space)
    : fColorSpace(std::move(color_space)),
      fColorType(color_type),
      fAlphaType(alpha_type) {}
SkColorInfo::SkColorInfo(SkColorInfo&& other)
    : fColorSpace(std::move(other.fColorSpace)),
      fColorType(other.fColorType),
      fAlphaType(other.fAlphaType) {}
SkImageInfo SkImageInfo::MakeUnknown(int width, int height) {
  return SkImageInfo::Make({width, height},
                           SkColorInfo(kUnknown_SkColorType,
                                       kUnknown_SkAlphaType,
                                       nullptr));
}
SkTextBlob::~SkTextBlob() = default;
void SkTextBlob::operator delete(void* ptr) {
  ::operator delete(ptr);
}
#endif

namespace v8 {
EmbedderStateScope::EmbedderStateScope(Isolate*,
                                       Local<v8::Context>,
                                       EmbedderStateTag) {}
EmbedderStateScope::~EmbedderStateScope() = default;
void Context::Enter() {}
void Context::Exit() {}
void Context::SetMicrotaskQueue(MicrotaskQueue*) {}
Local<Context> Isolate::GetCurrentContext() {
  return Local<Context>();
}
bool Value::IsObject() const {
  return false;
}
void* Object::GetAlignedPointerFromEmbedderDataInCreationContext(
    Isolate*,
    int,
    EmbedderDataTypeTag) {
  return nullptr;
}
internal::ExternalPointerTag ToExternalPointerTag(EmbedderDataTypeTag) {
  return internal::kExternalPointerNullTag;
}
MicrotasksScope::MicrotasksScope(Isolate*, MicrotaskQueue*, Type)
    : i_isolate_(nullptr), microtask_queue_(nullptr), run_(false) {}
MicrotasksScope::~MicrotasksScope() = default;
bool MicrotasksScope::IsRunningMicrotasks(Isolate*) {
  return false;
}
Local<Promise> Promise::Resolver::GetPromise() {
  return Local<Promise>();
}
internal::Address* HandleScope::Extend(Isolate*) {
  return nullptr;
}
void HandleScope::DeleteExtensions(Isolate*) {}
}  // namespace v8

namespace perfetto::internal {
protos::pbzero::DebugAnnotation* TrackEventInternal::AddDebugAnnotation(
    perfetto::EventContext*,
    const char*) {
  return nullptr;
}
const Track TrackEventInternal::kDefaultTrack{};
TracingMuxer* TracingMuxer::instance_ = nullptr;
}  // namespace perfetto::internal

namespace perfetto {
template <>
internal::DataSourceType&
DataSourceHelper<internal::TrackEventDataSource,
                 internal::TrackEventDataSourceTraits>::type() {
  static internal::DataSourceType* type = new internal::DataSourceType();
  return *type;
}
}  // namespace perfetto

namespace perfetto::legacy {
template <>
ThreadTrack ConvertThreadId(const PerfettoLegacyCurrentThreadId&) {
  return ThreadTrack::Current();
}
}  // namespace perfetto::legacy

namespace perfetto::internal {
}  // namespace perfetto::internal

namespace perfetto {
uint64_t Platform::process_id_ = 0;
ThreadTrack ThreadTrack::Current() {
  return ThreadTrack(0, false);
}
TracedDictionary::TracedDictionary(TracedValue value)
    : message_(nullptr),
      field_id_(0),
      event_context_(nullptr),
      checked_scope_(nullptr) {}
void TracedValue::WriteDouble(double) && {}
void TracedValue::WritePointer(const void*) && {}
}  // namespace perfetto

namespace base::trace_event {
TracedValue::TracedValue(uint64_t) {}
TracedValue::TracedValue(uint64_t, bool) {}
void TracedValue::BeginDictionary() {}
void TracedValue::BeginDictionary(const char*) {}
void TracedValue::EndDictionary() {}
void TracedValue::BeginArray(const char*) {}
void TracedValue::EndArray() {}
void TracedValue::SetInteger(const char*, int) {}
void TracedValue::SetDouble(const char*, double) {}
void TracedValue::SetBoolean(const char*, bool) {}
void TracedValue::SetString(const char*, std::string_view) {}
void TracedValue::AppendInteger(int) {}
void TracedValue::AppendDouble(double) {}
std::string TracedValueJSON::ToJSON() const {
  return std::string();
}
std::string TracedValueJSON::ToFormattedJSON() const {
  return std::string();
}
void ConvertableToTraceFormat::Add(
    perfetto::protos::pbzero::DebugAnnotation*) const {}
uint64_t GetNextGlobalTraceId() {
  static uint64_t next = 1;
  return next++;
}
}  // namespace base::trace_event

namespace base::perfetto_track_event::internal {
const ::perfetto::internal::TrackEventCategoryRegistry kCategoryRegistry(
    0,
    nullptr,
    nullptr);
}  // namespace base::perfetto_track_event::internal

namespace base {
PlatformThreadId PlatformThreadBase::CurrentId() {
  return PlatformThreadId();
}
PlatformThreadRef PlatformThreadBase::CurrentRef() {
  return PlatformThreadRef();
}
SequenceCheckerImpl::SequenceCheckerImpl() = default;
SequenceCheckerImpl::~SequenceCheckerImpl() = default;
void SequenceCheckerImpl::DetachFromSequence() {}
void DCheckAsserter::warn() {}
bool FeatureList::IsEnabled(const Feature& feature) {
  return feature.default_state == FEATURE_ENABLED_BY_DEFAULT;
}
namespace internal {
bool IsFeatureParamWithCacheEnabled() {
  return false;
}
}  // namespace internal
template <>
bool FeatureParam<bool>::GetWithoutCache() const {
  return default_value;
}
template <>
int FeatureParam<int>::GetWithoutCache() const {
  return default_value;
}
template <>
size_t FeatureParam<size_t>::GetWithoutCache() const {
  return default_value;
}
template <>
double FeatureParam<double>::GetWithoutCache() const {
  return default_value;
}
template <>
std::string FeatureParam<std::string>::GetWithoutCache() const {
  return default_value;
}
template <>
TimeDelta FeatureParam<TimeDelta>::GetWithoutCache() const {
  return default_value;
}
namespace i18n {
bool StringSearchIgnoringCaseAndAccents(std::u16string,
                                        std::u16string_view,
                                        size_t* match_index,
                                        size_t* match_length) {
  if (match_index) {
    *match_index = std::u16string::npos;
  }
  if (match_length) {
    *match_length = 0;
  }
  return false;
}
}  // namespace i18n
ThreadLocalStorage::Slot::Slot(TLSDestructorFunc) {}
ThreadLocalStorage::Slot::~Slot() = default;
void* ThreadLocalStorage::Slot::Get() const {
  return nullptr;
}
void ThreadLocalStorage::Slot::Set(void*) {}
size_t TokenHash::operator()(const Token&) {
  return 0;
}
const UnguessableToken& UnguessableToken::Null() {
  static const UnguessableToken* token = new UnguessableToken();
  return *token;
}
std::string StrCat(span<const std::string_view> pieces) {
  std::string out;
  for (std::string_view piece : pieces) {
    out.append(piece);
  }
  return out;
}
uint64_t FastHash(span<const uint8_t>) {
  return 0;
}
uint32_t PersistentHash(std::string_view value) {
  uint32_t hash = 2166136261u;
  for (char ch : value) {
    hash ^= static_cast<unsigned char>(ch);
    hash *= 16777619u;
  }
  return hash;
}
uint64_t HashInts64(uint64_t a, uint64_t b) {
  return a ^ (b + 0x9e3779b97f4a7c15ull + (a << 6) + (a >> 2));
}
void* AlignedAlloc(size_t size, size_t alignment) {
  return allocator_shim::UncheckedAlignedAlloc(size, alignment);
}
namespace debug {
void Alias(const void*) {}
ScopedCrashKeyString::ScopedCrashKeyString(CrashKeyString* crash_key,
                                           std::string_view)
    : crash_key_(crash_key) {}
ScopedCrashKeyString::~ScopedCrashKeyString() = default;
CrashKeyString* AllocateCrashKeyString(const char[], CrashKeySize) {
  return nullptr;
}
bool DumpWithoutCrashing(const Location&, TimeDelta) {
  return false;
}
}  // namespace debug
namespace sequence_manager {
TaskTimeObserver::~TaskTimeObserver() = default;
}  // namespace sequence_manager
CheckedObserver::CheckedObserver() = default;
CheckedObserver::~CheckedObserver() = default;
Value::~Value() = default;
const char* Value::GetTypeName(Type) {
  return "none";
}
int Value::GetInt() const {
  return 0;
}
const DictValue& Value::GetDict() const {
  static const DictValue* empty = new DictValue();
  return *empty;
}
const ListValue& Value::GetList() const {
  static const ListValue* empty = new ListValue();
  return *empty;
}
DictValue::DictValue() = default;
DictValue::~DictValue() = default;
ListValue::ListValue() = default;
ListValue::~ListValue() = default;
size_t ListValue::size() const {
  return storage_.size();
}
RefCountedString::RefCountedString(std::string value)
    : string_(std::move(value)) {}
RefCountedString::~RefCountedString() = default;
span<const uint8_t> RefCountedString::AsSpan() const {
  return as_byte_span(string_);
}
const Value* DictValue::Find(std::string_view) const {
  return nullptr;
}
Value* DictValue::Find(std::string_view) {
  return nullptr;
}
std::optional<int> DictValue::FindInt(std::string_view) const {
  return std::nullopt;
}
const std::string* DictValue::FindString(std::string_view) const {
  return nullptr;
}
std::string* DictValue::FindString(std::string_view) {
  return nullptr;
}
const ListValue* DictValue::FindList(std::string_view) const {
  return nullptr;
}
ListValue* DictValue::FindList(std::string_view) {
  return nullptr;
}
ListValue::const_iterator ListValue::begin() const {
  const Value* data = storage_.data();
  return const_iterator(data, data);
}
ListValue::const_iterator ListValue::end() const {
  const Value* data = storage_.data();
  return const_iterator(data, data + storage_.size());
}
const Value& ListValue::operator[](size_t index) const {
  return storage_[index];
}
std::optional<DictValue> JSONReader::ReadDict(std::string_view,
                                              int,
                                              size_t) {
  return std::nullopt;
}
std::ostream& operator<<(std::ostream& os, TimeDelta time_delta) {
  return os << time_delta.InMicroseconds() << " us";
}
ConditionVariable::ConditionVariable(Lock*) {}
ConditionVariable::~ConditionVariable() = default;
void Location::WriteIntoTrace(perfetto::TracedValue) const {}
void UmaHistogramSparse(const char*, int) {}
void UmaHistogramBoolean(const char*, bool) {}
void UmaHistogramCounts100(const char*, int) {}
void UmaHistogramExactLinear(const char*, int, int) {}
void UmaHistogramCustomTimes(const char*,
                             TimeDelta,
                             TimeDelta,
                             TimeDelta,
                             uint64_t) {}
void UmaHistogramCustomMicrosecondsTimes(const char*,
                                         TimeDelta,
                                         TimeDelta,
                                         TimeDelta,
                                         uint64_t) {}
void UmaHistogramTimes(const char*, TimeDelta) {}
void UmaHistogramTimes(const std::string&, TimeDelta) {}
void UmaHistogramMicrosecondsTimes(const char*, TimeDelta) {}
void UmaHistogramMicrosecondsTimes(const std::string&, TimeDelta) {}
std::string GetFieldTrialParamValueByFeature(const Feature&,
                                             const std::string&) {
  return std::string();
}
void LogInvalidEnumValue(const Feature&,
                         const std::string&,
                         const std::string&,
                         int) {}
HistogramBase* Histogram::FactoryGet(const char*, int, int, uint64_t, int) {
  return nullptr;
}
HistogramBase* LinearHistogram::FactoryGet(const char*,
                                           int,
                                           int,
                                           uint64_t,
                                           int) {
  return nullptr;
}
HistogramBase* Histogram::FactoryTimeGet(const char*,
                                         TimeDelta,
                                         TimeDelta,
                                         uint64_t,
                                         int) {
  return nullptr;
}
void HistogramBase::AddTimeMillisecondsGranularity(const TimeDelta&) {}
void HistogramBase::AddTimeMicrosecondsGranularity(const TimeDelta&) {}
MetricsSubSampler::MetricsSubSampler() = default;
bool MetricsSubSampler::ShouldSample(double) const {
  return false;
}
InsecureRandomGenerator::InsecureRandomGenerator() = default;
TimeDelta ElapsedTimer::Elapsed() const {
  return TimeDelta();
}
ElapsedTimer::ElapsedTimer() = default;
LapTimer::LapTimer(int warmup_laps,
                   TimeDelta time_limit,
                   int check_interval,
                   TimerMethod method)
    : warmup_laps_(warmup_laps),
      time_limit_(time_limit),
      check_interval_(check_interval),
      method_(method),
      num_laps_(0) {}
bool LapTimer::HasTimeLimitExpired() const {
  return true;
}
void LapTimer::NextLap() {}
TimeDelta LapTimer::TimePerLap() const {
  return TimeDelta();
}
Location::Location() = default;
Location::Location(const Location&) = default;
Time Time::Now() {
  return Time();
}
std::string UnlocalizedTimeFormatWithPattern(const Time&,
                                             std::string_view,
                                             const icu::TimeZone*) {
  return std::string();
}
WaitableEvent::~WaitableEvent() = default;
RunLoop::RunLoop(Type type)
    : delegate_(nullptr), type_(type), origin_task_runner_(nullptr) {}
RunLoop::~RunLoop() = default;
void RunLoop::Run(const Location&) {}
RepeatingClosure RunLoop::QuitClosure() & {
  return RepeatingClosure();
}
namespace internal {
LockImpl::LockImpl() = default;
LockImpl::~LockImpl() = default;
void LockImpl::LockInternal() {}
WeakReferenceOwner::WeakReferenceOwner() = default;
WeakReferenceOwner::~WeakReferenceOwner() = default;
WeakReference WeakReferenceOwner::GetRef() const {
  return WeakReference();
}
WeakReference::WeakReference() = default;
WeakReference::WeakReference(const WeakReference& other)
    : flag_(other.flag_) {}
WeakReference::WeakReference(WeakReference&& other) noexcept
    : flag_(std::move(other.flag_)) {}
WeakReference::~WeakReference() = default;
WeakReference& WeakReference::operator=(WeakReference&& other) noexcept {
  flag_ = std::move(other.flag_);
  return *this;
}
bool WeakReference::IsValid() const {
  return MaybeValid();
}
bool WeakReference::MaybeValid() const {
  return !flag_ || flag_->MaybeValid();
}
bool WeakReference::Flag::MaybeValid() const {
  return true;
}
WeakReference::Flag::~Flag() = default;
BindStateHolder& BindStateHolder::operator=(const BindStateHolder& other) =
    default;
BindStateHolder::BindStateHolder(const BindStateHolder& other) = default;
BindStateHolder::~BindStateHolder() = default;
void BindStateHolder::Reset() {
  bind_state_ = nullptr;
}
WeakPtrFactoryBase::WeakPtrFactoryBase(uintptr_t ptr) : ptr_(ptr) {}
WeakPtrFactoryBase::~WeakPtrFactoryBase() = default;
}  // namespace internal
bool TimeTicks::IsHighResolution() {
  return false;
}
TimeTicks TimeTicks::Now() {
  return TimeTicks();
}
double RandDouble() {
  return 0.5;
}
CPU::CPU() = default;
CPU::CPU(CPU&&) = default;
const CPU& CPU::GetInstanceNoAllocation() {
  static CPU* cpu = new CPU();
  return *cpu;
}
int RandIntInclusive(int from, int) {
  return from;
}
std::string Token::ToString() const {
  return std::string();
}
bool operator==(const UnguessableToken&, const UnguessableToken&) {
  return true;
}
const void* GetProgramCounter() {
  return nullptr;
}
ScopedUmaHistogramTimer::ScopedUmaHistogramTimer(
    std::string_view name,
    ScopedHistogramTiming timing)
    : constructed_(TimeTicks::Now()), timing_(timing), name_(name) {}
ScopedUmaHistogramTimer::~ScopedUmaHistogramTimer() = default;
SharedMemoryMapping::SharedMemoryMapping() = default;
SharedMemoryMapping::~SharedMemoryMapping() = default;
WritableSharedMemoryMapping::WritableSharedMemoryMapping() = default;
MemoryMappedFile::~MemoryMappedFile() = default;
File::~File() = default;
FilePath::FilePath() = default;
FilePath::FilePath(const FilePath& that) = default;
FilePath::FilePath(StringViewType path) : path_(path) {}
FilePath::FilePath(FilePath&& that) noexcept = default;
FilePath::~FilePath() = default;
FilePath& FilePath::operator=(const FilePath& that) = default;
FilePath& FilePath::operator=(FilePath&& that) noexcept = default;
FilePath FilePath::FromASCII(std::string_view ascii) {
  StringType path;
  path.reserve(ascii.size());
  for (char ch : ascii) {
    path.push_back(static_cast<CharType>(ch));
  }
  return FilePath(path);
}
bool FilePath::IsAbsolute() const {
  return false;
}
FilePath FilePath::Append(const FilePath& component) const {
  FilePath result(*this);
  if (!result.path_.empty()) {
    result.path_.push_back(kSeparators[0]);
  }
  result.path_.append(component.path_);
  return result;
}
FileTracing::ScopedEnabler::~ScopedEnabler() = default;
CommandLine::CommandLine(NoProgram) : argv_(1) {}
CommandLine* CommandLine::ForCurrentProcess() {
  static CommandLine* command_line = new CommandLine(NO_PROGRAM);
  return command_line;
}
bool CommandLine::HasSwitch(const char* const) const {
  return false;
}
namespace win {
void VerifierTraits::StopTracking(void*, const void*, const void*, const void*) {}
bool HandleTraits::CloseHandle(HANDLE handle) {
  return CloseHandle(handle) != 0;
}
}  // namespace win
bool SequenceCheckerImpl::CalledOnValidSequence(
    std::unique_ptr<debug::StackTrace>*) const {
  return true;
}
// The standalone renderer runs Blink synchronously; no ambient task runner is
// exposed through Chromium's task APIs.
const scoped_refptr<SequencedTaskRunner>&
SequencedTaskRunner::GetCurrentDefault() {
  static scoped_refptr<SequencedTaskRunner>* runner =
      new scoped_refptr<SequencedTaskRunner>();
  return *runner;
}
bool TaskRunner::PostTask(const Location&, OnceClosure) {
  return false;
}
const DefaultTickClock* DefaultTickClock::GetInstance() {
  static DefaultTickClock* clock = new DefaultTickClock();
  return clock;
}
DefaultTickClock::~DefaultTickClock() = default;
TimeTicks DefaultTickClock::NowTicks() const {
  return TimeTicks::Now();
}
TickClock::~TickClock() = default;
void TaskRunnerTraits::Destruct(const TaskRunner* task_runner) {
  task_runner->OnDestruct();
}
UnguessableToken UnguessableToken::Create() {
  return UnguessableToken();
}
MemoryPressureListener::MemoryPressureListener() = default;
class AsyncMemoryPressureListenerRegistration::MainThread {};
AsyncMemoryPressureListenerRegistration::
    AsyncMemoryPressureListenerRegistration(const Location&,
                                            MemoryPressureListenerTag,
                                            MemoryPressureListener*,
                                            bool) {}
AsyncMemoryPressureListenerRegistration::
    ~AsyncMemoryPressureListenerRegistration() = default;
}  // namespace base

namespace skresources {
sk_sp<SkImage> ImageAsset::getFrame(float) {
  return nullptr;
}
ResourceProviderProxyBase::ResourceProviderProxyBase(sk_sp<ResourceProvider> rp)
    : fProxy(std::move(rp)) {}
sk_sp<SkData> ResourceProviderProxyBase::load(const char[], const char[]) const {
  return nullptr;
}
sk_sp<ImageAsset> ResourceProviderProxyBase::loadImageAsset(
    const char[],
    const char[],
    const char[]) const {
  return nullptr;
}
sk_sp<SkTypeface> ResourceProviderProxyBase::loadTypeface(const char[],
                                                          const char[]) const {
  return nullptr;
}
sk_sp<SkData> ResourceProviderProxyBase::loadFont(const char[],
                                                  const char[]) const {
  return nullptr;
}
sk_sp<ExternalTrackAsset> ResourceProviderProxyBase::loadAudioAsset(
    const char[],
    const char[],
    const char[]) {
  return nullptr;
}
CachingResourceProvider::CachingResourceProvider(sk_sp<ResourceProvider> rp)
    : ResourceProviderProxyBase(std::move(rp)) {}
sk_sp<ImageAsset> CachingResourceProvider::loadImageAsset(const char[],
                                                          const char[],
                                                          const char[]) const {
  return nullptr;
}
sk_sp<DataURIResourceProviderProxy> DataURIResourceProviderProxy::Make(
    sk_sp<ResourceProvider>,
    ImageDecodeStrategy,
    sk_sp<const SkFontMgr>) {
  return nullptr;
}
}  // namespace skresources

namespace skia {
sk_sp<SkFontMgr> DefaultFontMgr() {
  static SkFontMgr* font_manager = []() -> SkFontMgr* {
    sk_sp<SkFontMgr> windows_fonts = SkFontMgr_New_DirectWrite();
    if (windows_fonts && windows_fonts->countFamilies() > 0) {
      return windows_fonts.release();
    }
    return SkFontMgr::RefEmpty().release();
  }();
  return sk_ref_sp(font_manager);
}
base::span<const uint8_t> as_byte_span(const SkData& data) {
  return base::span(static_cast<const uint8_t*>(data.data()), data.size());
}
void DrawGainmapImage(SkCanvas*,
                      sk_sp<SkImage>,
                      sk_sp<SkImage>,
                      const SkGainmapInfo&,
                      float,
                      float,
                      float,
                      const SkSamplingOptions&,
                      const SkPaint&) {}
void DrawGainmapImageRect(SkCanvas*,
                          sk_sp<SkImage>,
                          sk_sp<SkImage>,
                          const SkGainmapInfo&,
                          float,
                          const SkRect&,
                          const SkRect&,
                          const SkSamplingOptions&,
                          const SkPaint&) {}
}  // namespace skia

namespace SkImages {
sk_sp<SkImage> DeferredFromEncodedData(sk_sp<const SkData>,
                                       std::optional<SkAlphaType>) {
  return nullptr;
}
}  // namespace SkImages

namespace sktext::gpu {
void Slug::draw(SkCanvas*, const SkPaint&) const {}
sk_sp<SkData> Slug::serialize() const {
  return nullptr;
}
size_t Slug::serialize(void*, size_t) const {
  return 0;
}
sk_sp<Slug> Slug::ConvertBlob(SkCanvas*,
                              const SkTextBlob&,
                              SkPoint,
                              const SkPaint&) {
  return nullptr;
}
sk_sp<Slug> Slug::Deserialize(const void*, size_t, const SkStrikeClient*) {
  return nullptr;
}
}  // namespace sktext::gpu

namespace skottie {
Animation::~Animation() = default;
Animation::Builder::Builder(uint32_t flags) : fFlags(flags) {}
Animation::Builder::~Builder() = default;
Animation::Builder& Animation::Builder::setLogger(sk_sp<Logger> logger) {
  fLogger = std::move(logger);
  return *this;
}
Animation::Builder& Animation::Builder::setPropertyObserver(
    sk_sp<PropertyObserver> observer) {
  fPropertyObserver = std::move(observer);
  return *this;
}
Animation::Builder& Animation::Builder::setFontManager(
    sk_sp<SkFontMgr> font_manager) {
  fFontMgr = std::move(font_manager);
  return *this;
}
Animation::Builder& Animation::Builder::setResourceProvider(
    sk_sp<ResourceProvider> provider) {
  fResourceProvider = std::move(provider);
  return *this;
}
Animation::Builder& Animation::Builder::setMarkerObserver(
    sk_sp<MarkerObserver> observer) {
  fMarkerObserver = std::move(observer);
  return *this;
}
sk_sp<Animation> Animation::Builder::make(const char*, size_t) {
  return nullptr;
}
void Animation::seekFrameTime(double, sksg::InvalidationController*) {}
void Animation::render(SkCanvas*, const SkRect*) const {}
void Animation::render(SkCanvas*, const SkRect*, RenderFlags) const {}

void PropertyObserver::onOpacityProperty(
    const char* const,
    const LazyHandle<OpacityPropertyHandle>&) {}
void PropertyObserver::onEnterNode(const char* const, NodeType) {}
void PropertyObserver::onLeavingNode(const char* const, NodeType) {}

template <>
ColorPropertyValue PropertyHandle<ColorPropertyValue, sksg::Color>::get()
    const {
  return 0;
}
template <>
void PropertyHandle<ColorPropertyValue, sksg::Color>::set(
    const ColorPropertyValue&) {}
template <>
PropertyHandle<ColorPropertyValue, sksg::Color>::~PropertyHandle() = default;

template <>
TextPropertyValue
PropertyHandle<TextPropertyValue, internal::TextAdapter>::get() const {
  return TextPropertyValue();
}
template <>
void PropertyHandle<TextPropertyValue, internal::TextAdapter>::set(
    const TextPropertyValue&) {}
template <>
PropertyHandle<TextPropertyValue, internal::TextAdapter>::
    ~PropertyHandle() = default;

template <>
TransformPropertyValue
PropertyHandle<TransformPropertyValue, internal::TransformAdapter2D>::get()
    const {
  return TransformPropertyValue();
}
template <>
PropertyHandle<TransformPropertyValue, internal::TransformAdapter2D>::
    ~PropertyHandle() = default;
}  // namespace skottie

namespace gpu {
Mailbox::Mailbox() {
  SetZero();
}
bool Mailbox::IsZero() const {
  for (int8_t byte : name) {
    if (byte != 0) {
      return false;
    }
  }
  return true;
}
void Mailbox::SetZero() {
  std::memset(name, 0, sizeof(name));
}
}  // namespace gpu

namespace mojo {
Message::Message() = default;
Message::Message(uint32_t,
                 uint32_t,
                 size_t,
                 size_t,
                 MojoCreateMessageFlags,
                 std::vector<ScopedHandle>*,
                 size_t) {}
Message::~Message() = default;
void Message::SerializeHandles(AssociatedGroupController*) {}
uint32_t Message::payload_num_bytes() const {
  return 0;
}
const uint8_t* Message::payload() const {
  return nullptr;
}
class ScopedInterfaceEndpointHandle::State
    : public base::RefCountedThreadSafe<State> {
 private:
  friend class base::RefCountedThreadSafe<State>;
  ~State() = default;
};
ScopedInterfaceEndpointHandle::ScopedInterfaceEndpointHandle() = default;
ScopedInterfaceEndpointHandle::ScopedInterfaceEndpointHandle(
    ScopedInterfaceEndpointHandle&& other) {
  state_.swap(other.state_);
}
ScopedInterfaceEndpointHandle::~ScopedInterfaceEndpointHandle() = default;
ScopedInterfaceEndpointHandle& ScopedInterfaceEndpointHandle::operator=(
    ScopedInterfaceEndpointHandle&& other) {
  state_.swap(other.state_);
  return *this;
}
void ScopedInterfaceEndpointHandle::CreatePairPendingAssociation(
    ScopedInterfaceEndpointHandle* handle0,
    ScopedInterfaceEndpointHandle* handle1) {
  if (handle0)
    handle0->reset();
  if (handle1)
    handle1->reset();
}
void ScopedInterfaceEndpointHandle::reset() {}
bool ScopedInterfaceEndpointHandle::is_valid() const {
  return false;
}
bool MessageReceiver::PrefersSerializedMessages() {
  return false;
}
SharedMemoryVersionClient::~SharedMemoryVersionClient() = default;
GenericPendingReceiver::~GenericPendingReceiver() = default;
GenericPendingReceiver::GenericPendingReceiver(std::string_view,
                                               ScopedMessagePipeHandle) {}
ReceiverSetState::ReceiverSetState() = default;
ReceiverSetState::~ReceiverSetState() = default;
ReceiverSetState::Entry::Entry(ReceiverSetState& state,
                               ReceiverId id,
                               std::unique_ptr<ReceiverState> receiver,
                               std::unique_ptr<MessageFilter>)
    : state_(state), id_(id), receiver_(std::move(receiver)) {}
ReceiverSetState::Entry::~Entry() = default;
ReceiverId ReceiverSetState::Add(std::unique_ptr<ReceiverState>,
                                 std::unique_ptr<MessageFilter>) {
  return 0;
}
PassThroughFilter::PassThroughFilter() = default;
PassThroughFilter::~PassThroughFilter() = default;
bool PassThroughFilter::Accept(Message*) {
  return true;
}
namespace internal {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
size_t Buffer::Allocate(size_t) {
  return 0;
}
#endif
ArrayIndexError MakeMessageWithArrayIndex(const char* message,
                                          size_t index,
                                          size_t size) {
  return {message, size, index};
}
ArrayExpectedSizeError MakeMessageWithExpectedArraySize(
    const char* message,
    size_t size,
    size_t expected_size) {
  return {message, size, expected_size};
}
void HandleSerializationWarning(ValidationError, const char*) {}
void HandleSerializationWarning(ValidationError, const ArrayIndexError&) {}
void HandleSerializationWarning(ValidationError,
                                const ArrayExpectedSizeError&) {}
ValidationContext::ValidationContext(const void*,
                                     size_t,
                                     size_t,
                                     size_t,
                                     Message*,
                                     const char*,
                                     int,
                                     ValidatorType)
    : message_(nullptr),
      description_(""),
      validator_type_(kUnspecifiedValidator),
      data_begin_(0),
      data_end_(0),
      handle_begin_(0),
      handle_end_(0),
      associated_endpoint_handle_begin_(0),
      associated_endpoint_handle_end_(0),
      stack_depth_(0) {}
ValidationContext::ValidationContext(Message*,
                                     const char*,
                                     ValidatorType)
    : message_(nullptr),
      description_(""),
      validator_type_(kUnspecifiedValidator),
      data_begin_(0),
      data_end_(0),
      handle_begin_(0),
      handle_end_(0),
      associated_endpoint_handle_begin_(0),
      associated_endpoint_handle_end_(0),
      stack_depth_(0) {}
ValidationContext::~ValidationContext() = default;
AssociatedInterfacePtrStateBase::AssociatedInterfacePtrStateBase() = default;
AssociatedInterfacePtrStateBase::~AssociatedInterfacePtrStateBase() = default;
BindingStateBase::BindingStateBase() = default;
BindingStateBase::~BindingStateBase() = default;
AssociatedReceiverBase::AssociatedReceiverBase() = default;
AssociatedReceiverBase::~AssociatedReceiverBase() = default;
void AssociatedReceiverBase::reset() {}
void BindingStateBase::SetFilter(std::unique_ptr<MessageFilter>) {}
void BindingStateBase::FlushForTesting() {}
void BindingStateBase::CloseWithReason(uint32_t, std::string_view) {}
void BindingStateBase::Close() {}
void BindingStateBase::BindInternal(
    PendingReceiverState*,
    scoped_refptr<base::SequencedTaskRunner>,
    const char*,
    std::unique_ptr<MessageReceiver>,
    bool,
    base::span<const uint32_t>,
    MessageReceiverWithResponderStatus*,
    uint32_t,
    MessageToMethodInfoCallback,
    MessageToMethodNameCallback) {}
InterfacePtrStateBase::InterfacePtrStateBase() = default;
InterfacePtrStateBase::~InterfacePtrStateBase() = default;
void InterfacePtrStateBase::Bind(
    PendingRemoteState*,
    scoped_refptr<base::SequencedTaskRunner>) {}
void AssociatedInterfacePtrStateBase::Bind(
    ScopedInterfaceEndpointHandle,
    uint32_t,
    std::unique_ptr<MessageReceiver>,
    scoped_refptr<base::SequencedTaskRunner>,
    const char*,
    MessageToMethodInfoCallback,
    MessageToMethodNameCallback) {}
bool InterfacePtrStateBase::InitializeEndpointClient(
    bool,
    bool,
    bool,
    std::unique_ptr<MessageReceiver>,
    const char*,
    MessageToMethodInfoCallback,
    MessageToMethodNameCallback) {
  return false;
}
void InterfacePtrStateBase::Swap(InterfacePtrStateBase*) {}
void AssociatedInterfacePtrStateBase::Swap(AssociatedInterfacePtrStateBase*) {}
ScopedInterfaceEndpointHandle AssociatedInterfacePtrStateBase::PassHandle() {
  return ScopedInterfaceEndpointHandle();
}
scoped_refptr<MultiplexRouter> MultiplexRouter::CreateAndStartReceiving(
    ScopedMessagePipeHandle,
    Config,
    bool,
    scoped_refptr<base::SequencedTaskRunner>,
    const char*) {
  return nullptr;
}
}  // namespace internal
}  // namespace mojo

namespace gfx::mojom::internal {
HdrMetadataExtendedRange_Data::HdrMetadataExtendedRange_Data()
    : header_({sizeof(*this), 0}), current_headroom(1.0f), desired_headroom(1.0f) {}
HDRMetadata_Data::HDRMetadata_Data()
    : header_({sizeof(*this), 0}),
      ndwl_$flag(false),
      pad2_{0, 0, 0},
      ndwl_$value(0.0f) {}
}  // namespace gfx::mojom::internal

namespace skia::mojom::internal {
SkHdrContentLightLevelInformation_Data::
    SkHdrContentLightLevelInformation_Data()
    : header_({sizeof(*this), 0}), max_cll(0.0f), max_fall(0.0f) {}
SkHdrMasteringDisplayColorVolume_Data::
    SkHdrMasteringDisplayColorVolume_Data()
    : header_({sizeof(*this), 0}), max_luminance(0.0f), min_luminance(0.0f) {}
SkHdrAgtmGainCurveControlPoint_Data::
    SkHdrAgtmGainCurveControlPoint_Data()
    : header_({sizeof(*this), 0}), x(0.0f), y(0.0f), m(0.0f), padfinal_{0, 0, 0, 0} {}
SkHdrAgtmGainCurve_Data::SkHdrAgtmGainCurve_Data()
    : header_({sizeof(*this), 0}) {}
SkHdrAgtmComponentMixingFunction_Data::
    SkHdrAgtmComponentMixingFunction_Data()
    : header_({sizeof(*this), 0}) {}
SkHdrAgtmColorGainFunction_Data::SkHdrAgtmColorGainFunction_Data()
    : header_({sizeof(*this), 0}) {}
SkHdrAgtmAlternateImage_Data::SkHdrAgtmAlternateImage_Data()
    : header_({sizeof(*this), 0}) {}
SkHdrAgtmHeadroomAdaptiveToneMap_Data::
    SkHdrAgtmHeadroomAdaptiveToneMap_Data()
    : header_({sizeof(*this), 0}) {}
SkHdrAdaptiveGlobalToneMap_Data::SkHdrAdaptiveGlobalToneMap_Data()
    : header_({sizeof(*this), 0}) {}
}  // namespace skia::mojom::internal

extern "C" MojoResult MojoCreateMessagePipe(
    const MojoCreateMessagePipeOptions*,
    MojoHandle* message_pipe_handle0,
    MojoHandle* message_pipe_handle1) {
  if (message_pipe_handle0)
    *message_pipe_handle0 = MOJO_HANDLE_INVALID;
  if (message_pipe_handle1)
    *message_pipe_handle1 = MOJO_HANDLE_INVALID;
  return MOJO_RESULT_OK;
}
extern "C" MojoResult MojoClose(MojoHandle) {
  return MOJO_RESULT_OK;
}

namespace mojo_base {
namespace internal {
BigBufferSharedMemoryRegion::~BigBufferSharedMemoryRegion() = default;
}  // namespace internal
BigBuffer::~BigBuffer() = default;
}  // namespace mojo_base

namespace ukm::mojom {
UkmRecorderFactory::IPCStableHashFunction
UkmRecorderFactory::MessageToMethodInfo_(mojo::Message&) {
  return nullptr;
}
const char* UkmRecorderFactory::MessageToMethodName_(mojo::Message&) {
  return "";
}
UkmRecorderFactoryProxy::UkmRecorderFactoryProxy(
    mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {}
void UkmRecorderFactoryProxy::CreateUkmRecorder(
    mojo::PendingReceiver<UkmRecorderInterface>,
    mojo::PendingRemote<UkmRecorderClientInterface>) {}
}  // namespace ukm::mojom

namespace subresource_filter {
ScopedRule::ScopedRule() : ruleset_(nullptr), rule_(nullptr) {}
ScopedRule::ScopedRule(ScopedRule&& other)
    : ruleset_(std::move(other.ruleset_)),
      rule_(other.rule_) {}
ScopedRule& ScopedRule::operator=(ScopedRule&& other) = default;
ScopedRule::~ScopedRule() = default;
}  // namespace subresource_filter

namespace absl::container_internal {
HashtablezInfoHandle ForcedTrySample(size_t, size_t, size_t, uint16_t) {
  return HashtablezInfoHandle(nullptr);
}
}  // namespace absl::container_internal

extern "C" bool AbslContainerInternalSampleEverything() {
  return false;
}

namespace allocator_shim {
void* UncheckedAlloc(size_t size) {
  return std::malloc(size ? size : 1);
}
void UncheckedFree(void* ptr) {
  std::free(ptr);
}
void* UncheckedRealloc(void* ptr, size_t size) {
  return std::realloc(ptr, size ? size : 1);
}
void* UncheckedAlignedAlloc(size_t size, size_t alignment) {
  size_t adjusted_alignment = std::max(alignment, sizeof(void*));
  return _aligned_malloc(size ? size : 1, adjusted_alignment);
}
void UncheckedAlignedFree(void* ptr) {
  _aligned_free(ptr);
}
void* UncheckedAlignedRealloc(void* ptr, size_t size, size_t alignment) {
  return _aligned_realloc(ptr, size ? size : 1, std::max(alignment, sizeof(void*)));
}
}  // namespace allocator_shim

namespace rust_allocator_internal {
unsigned char* alloc(size_t size, size_t align) {
  return static_cast<unsigned char*>(
      allocator_shim::UncheckedAlignedAlloc(size, align));
}
void dealloc(unsigned char* ptr, size_t, size_t) {
  allocator_shim::UncheckedAlignedFree(ptr);
}
unsigned char* realloc(unsigned char* ptr,
                       size_t,
                       size_t align,
                       size_t new_size) {
  return static_cast<unsigned char*>(
      allocator_shim::UncheckedAlignedRealloc(ptr, new_size, align));
}
unsigned char* alloc_zeroed(size_t size, size_t align) {
  unsigned char* ptr = alloc(size, align);
  if (ptr) {
    std::memset(ptr, 0, size);
  }
  return ptr;
}
void alloc_error_handler_impl() {
  std::abort();
}
}  // namespace rust_allocator_internal

extern "C" MojoResult MojoUnmapBuffer(void*) {
  return MOJO_RESULT_OK;
}

namespace cppgc::internal {
PersistentRegionLock::PersistentRegionLock() = default;
PersistentRegionLock::~PersistentRegionLock() = default;
void PersistentRegionLock::AssertLocked() {}
PersistentRegionBase::PersistentRegionBase(
    const FatalOutOfMemoryHandler& oom_handler)
    : oom_handler_(oom_handler) {}
PersistentRegionBase::~PersistentRegionBase() = default;
void PersistentRegionBase::Iterate(RootVisitor&) {}
size_t PersistentRegionBase::NodesInUse() const {
  return nodes_in_use_;
}
void PersistentRegionBase::ClearAllUsedNodes() {
  nodes_in_use_ = 0;
  free_list_head_ = nullptr;
  nodes_.clear();
}
TraceDescriptor TraceTraitFromInnerAddressImpl::GetTraceDescriptor(
    const void*) {
  return {nullptr, nullptr};
}

void* StandaloneCppgcAllocatePayload(size_t size) {
  // cppgc::MakeGarbageCollected writes construction metadata immediately before
  // the returned payload. The standalone shim does not provide a real cppgc heap
  // header yet, but it must still reserve prefix space to keep those writes from
  // corrupting the C allocator's bookkeeping.
  constexpr size_t kHeaderPadding = 64;
  void* base = std::calloc(1, (size ? size : 1) + kHeaderPadding);
  return static_cast<char*>(base) + kHeaderPadding;
}

PersistentRegion& StrongPersistentPolicy::GetPersistentRegion(const void*) {
  return StandalonePersistentRegion();
}
bool PersistentRegion::IsCreationThread() {
  return true;
}
PersistentNode* PersistentRegionBase::RefillFreeListAndAllocateNode(
    void* owner,
    TraceRootCallback trace) {
  auto node = std::make_unique<std::array<PersistentNode, 256u>>();
  for (PersistentNode& slot : *node) {
    slot.InitializeAsFreeNode(free_list_head_);
    free_list_head_ = &slot;
  }
  nodes_.push_back(std::move(node));
  PersistentNode* allocated = free_list_head_;
  free_list_head_ = allocated->FreeListNext();
  allocated->InitializeAsUsedNode(owner, trace);
  ++nodes_in_use_;
  return allocated;
}
void FatalImpl(const char*, SourceLocation) {}
void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  GCInfoIndex,
                                                  CustomSpaceIndex) {
  return StandaloneCppgcAllocatePayload(size);
}
void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  GCInfoIndex) {
  return StandaloneCppgcAllocatePayload(size);
}
void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  AlignVal,
                                                  GCInfoIndex) {
  return StandaloneCppgcAllocatePayload(size);
}
void* MakeGarbageCollectedTraitInternal::Allocate(AllocationHandle&,
                                                  size_t size,
                                                  AlignVal,
                                                  GCInfoIndex,
                                                  CustomSpaceIndex) {
  return StandaloneCppgcAllocatePayload(size);
}
void ExplicitManagementImpl::FreeUnreferencedObject(HeapHandle&, void*) {}
bool ExplicitManagementImpl::Resize(void*, size_t) {
  return false;
}
void WriteBarrier::DijkstraMarkingBarrierRangeSlow(HeapHandle&,
                                                   const void*,
                                                   size_t,
                                                   size_t,
                                                   TraceCallback) {}
void WriteBarrier::SteeleMarkingBarrierSlowWithSentinelCheck(const void*) {}
void WriteBarrier::DijkstraMarkingBarrierSlowWithSentinelCheck(const void*) {}
AtomicEntryFlag WriteBarrier::write_barrier_enabled_;
size_t BaseObjectSizeTrait::GetObjectSizeForGarbageCollected(const void*) {
  return 0;
}
CrossThreadPersistentRegion&
WeakCrossThreadPersistentPolicy::GetPersistentRegion(const void*) {
  return *static_cast<CrossThreadPersistentRegion*>(nullptr);
}
CrossThreadPersistentRegion::CrossThreadPersistentRegion(
    const FatalOutOfMemoryHandler& oom_handler)
    : PersistentRegionBase(oom_handler) {}
CrossThreadPersistentRegion::~CrossThreadPersistentRegion() = default;
void CrossThreadPersistentRegion::Iterate(RootVisitor&) {}
size_t CrossThreadPersistentRegion::NodesInUse() const {
  return PersistentRegionBase::NodesInUse();
}
void CrossThreadPersistentRegion::ClearAllUsedNodes() {
  PersistentRegionBase::ClearAllUsedNodes();
}
}  // namespace cppgc::internal

namespace cc {
void PictureDebugUtil::SerializeAsBase64(const SkPicture*, std::string*) {}
void AnimationHost::AddAnimationTimeline(scoped_refptr<AnimationTimeline>) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
Region::Region() = default;
Region::Region(const Region&) = default;
Region::~Region() = default;
void Region::Union(const gfx::Rect&) {}
#endif
AnimationWorkletOutput::AnimationWorkletOutput() = default;
AnimationWorkletOutput::~AnimationWorkletOutput() = default;
AnimationWorkletOutput::AnimationState::~AnimationState() = default;
#if !defined(HTML_CSS_RENDERER_STANDALONE)
SnapContainerData::~SnapContainerData() = default;
SnapContainerData::SnapContainerData(const SnapContainerData&) = default;

const TargetSnapAreaElementIds& SnapContainerData::GetTargetSnapAreaElementIds()
    const {
  static const TargetSnapAreaElementIds empty;
  return empty;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
CorePaintFlags::CorePaintFlags() {
  bitfields_uint_ = 0u;
  bitfields_.cap_type_ = SkPaint::kDefault_Cap;
  bitfields_.join_type_ = SkPaint::kDefault_Join;
  bitfields_.style_ = SkPaint::kFill_Style;
  bitfields_.blend_mode_ = static_cast<int>(SkBlendMode::kSrcOver);
  bitfields_.filter_quality_ =
      static_cast<int>(PaintFlags::FilterQuality::kNone);
  bitfields_.dynamic_range_limit_standard_mix_ = 0;
  bitfields_.dynamic_range_limit_constrained_high_mix_ = 0;
}
PaintFlags::PaintFlags() = default;
PaintFlags::PaintFlags(const PaintFlags&) = default;
PaintFlags::PaintFlags(PaintFlags&&) = default;
PaintFlags::~PaintFlags() = default;
bool PaintFlags::getFillPath(const SkPath& src,
                             SkPath* dst,
                             const SkRect*,
                             SkScalar) const {
  if (dst) {
    *dst = src;
  }
  return true;
}
#endif
void ScrollTimeline::UpdateScrollerIdAndScrollOffsets(
    std::optional<ElementId>,
    std::optional<ScrollOffsets>) {}
}  // namespace cc

#if !defined(HTML_CSS_RENDERER_STANDALONE)
SkRegion::SkRegion() = default;
SkRegion::SkRegion(const SkRegion&) = default;
SkRegion::~SkRegion() = default;
#endif

namespace perfetto {
namespace base {
void LogMessage(LogLev, const char*, int, const char*, ...) {}
}  // namespace base
uint64_t Track::process_uuid = 0;
TracedArray::TracedArray(TracedValue value)
    : TracedArray(std::move(value).WriteArray()) {}

TracedArray TracedDictionary::AddArray(StaticString) {
  return TracedArray(TracedValue(
      static_cast<perfetto::protos::pbzero::DebugAnnotation*>(nullptr),
      event_context_,
      &checked_scope_));
}

TracedValue TracedArray::AppendItem() {
  return TracedValue(annotation_, event_context_, &checked_scope_);
}

TracedArray TracedValue::WriteArray() && {
  return TracedArray(annotation_, event_context_, &checked_scope_);
}
TracedDictionary TracedValue::WriteDictionary() && {
  return TracedDictionary(
      TracedValue(annotation_, event_context_, &checked_scope_));
}
TracedValue TracedDictionary::AddItem(StaticString) {
  return TracedValue(
      static_cast<perfetto::protos::pbzero::DebugAnnotation*>(nullptr),
      event_context_, &checked_scope_);
}

void TracedValue::WriteUInt64(uint64_t) && {}
void TracedValue::WriteInt64(int64_t) && {}
void TracedValue::WriteString(const char*) && {}
void TracedValue::WriteString(const std::string&) && {}
void TracedValue::WriteBoolean(bool) && {}
}  // namespace perfetto

namespace subresource_filter {
MemoryMappedRuleset::~MemoryMappedRuleset() = default;
ScopedRule::ScopedRule(const ScopedRule&) = default;
ScopedRule& ScopedRule::operator=(const ScopedRule&) = default;
}  // namespace subresource_filter

namespace partition_alloc {
ScopedAllowAllocations::ScopedAllowAllocations() = default;
ScopedAllowAllocations::~ScopedAllowAllocations() = default;
namespace internal {
[[noreturn]] void OnNoMemory(size_t) {
  std::abort();
}
}  // namespace internal
}  // namespace partition_alloc

namespace ukm {
SourceId UkmRecorder::GetNewSourceID() {
  return 1;
}
std::unique_ptr<MojoUkmRecorder> MojoUkmRecorder::Create(
    mojom::UkmRecorderFactory&) {
  return nullptr;
}
base::WeakPtr<MojoUkmRecorder> MojoUkmRecorder::GetWeakPtr() {
  return base::WeakPtr<MojoUkmRecorder>();
}
void DelegatingUkmRecorder::AddDelegate(base::WeakPtr<UkmRecorder>) {}
DelegatingUkmRecorder* DelegatingUkmRecorder::Get() {
  return nullptr;
}
void DelegatingUkmRecorder::RemoveDelegate(UkmRecorder*) {}
}  // namespace ukm

namespace gfx {
HDRMetadata::HDRMetadata(const HDRMetadata& rhs) = default;
HDRMetadata& HDRMetadata::operator=(const HDRMetadata& rhs) = default;
bool HdrMetadataAgtm::IsEnabled() {
  return false;
}
bool ColorSpace::operator==(const ColorSpace&) const {
  return false;
}
sk_sp<SkData> MakeSkDataFromSpanWithCopy(base::span<const uint8_t> data) {
  return SkData::MakeWithCopy(data.data(), data.size());
}
float Tween::FloatValueBetween(double value, float start, float target) {
  return start + static_cast<float>(value) * (target - start);
}
int Tween::LinearIntValueBetween(double value, int start, int target) {
  return start + static_cast<int>(value * (target - start));
}
SkColor4f Tween::ColorValueBetween(double value,
                                   SkColor4f start,
                                   SkColor4f target) {
  return {FloatValueBetween(value, start.fR, target.fR),
          FloatValueBetween(value, start.fG, target.fG),
          FloatValueBetween(value, start.fB, target.fB),
          FloatValueBetween(value, start.fA, target.fA)};
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
Point ToRoundedPoint(const PointF& point) {
  return Point(static_cast<int>(std::round(point.x())),
               static_cast<int>(std::round(point.y())));
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool Rect::Contains(int point_x, int point_y) const {
  return point_x >= x() && point_x < right() && point_y >= y() &&
         point_y < bottom();
}
#endif
}  // namespace gfx

namespace gfx {
HDRMetadata::HDRMetadata() = default;
HDRMetadata::~HDRMetadata() = default;

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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif
}  // namespace skcms

#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif

namespace v8::internal {
struct ScriptStreamingData {};
}  // namespace v8::internal

namespace v8 {
cppgc::HeapHandle& CppHeap::GetHeapHandle() {
  return *static_cast<cppgc::HeapHandle*>(nullptr);
}
ScriptCompiler::StreamedSource::~StreamedSource() = default;
ExternalMemoryAccounter::~ExternalMemoryAccounter() = default;
void ExternalMemoryAccounter::Increase(Isolate*, size_t) {}
void ExternalMemoryAccounter::Decrease(Isolate*, size_t) {}
Isolate* Isolate::TryGetCurrent() {
  return nullptr;
}
bool Isolate::HasPendingException() {
  return false;
}
}  // namespace v8

namespace blink {
std::array<std::atomic_int, InstanceCounters::kCounterTypeLength>
    InstanceCounters::counters_;

ScopedPaintTimingDetectorBlockPaintHook*
    ScopedPaintTimingDetectorBlockPaintHook::top_ = nullptr;
void ScopedPaintTimingDetectorBlockPaintHook::EmplaceIfNeeded(
    const LayoutBoxModelObject&,
    const PropertyTreeStateOrAlias&) {}
ScopedPaintTimingDetectorBlockPaintHook::~ScopedPaintTimingDetectorBlockPaintHook() =
    default;

void AuditsIssue::ReportStylesheetLoadingRequestFailedIssue(
    Document*,
    const KURL&,
    const String&,
    const KURL&,
    OrdinalNumber,
    OrdinalNumber,
    const String&) {}

Platform* Platform::Current() {
  return nullptr;
}
void ThreadSafeBrowserInterfaceBrokerProxy::GetInterface(
    mojo::GenericPendingReceiver) {}

namespace inspector_parse_author_style_sheet_event {
void Data(perfetto::TracedValue,
          CSSStyleSheetResource*,
          const String&,
          const CSSParserContext*) {}

void Data(perfetto::TracedValue, const CSSStyleSheetResource*) {}
}  // namespace inspector_parse_author_style_sheet_event

namespace inspector_style_recalc_invalidation_tracking_event {
void Data(perfetto::TracedValue,
          Node*,
          StyleChangeType,
          const StyleChangeReasonForTracing&) {}
}  // namespace inspector_style_recalc_invalidation_tracking_event

namespace inspector_layout_invalidation_tracking_event {
void Data(perfetto::TracedValue,
          const LayoutObject*,
          LayoutInvalidationReasonForTracing) {}
}  // namespace inspector_layout_invalidation_tracking_event

namespace http_names {
const AtomicString& kSourceMap = *new AtomicString("SourceMap");
const AtomicString& kXSourceMap = *new AtomicString("X-SourceMap");
}  // namespace http_names

bool RuntimeEnabledFeaturesBase::is_css_caret_animation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_caret_shape_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_dynamic_range_limit_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_responsive_iframes_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_hanging_punctuation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_image_animation_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_overscroll_gestures_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_margin_trim_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_hex_alpha_color_enabled_ = true;
bool RuntimeEnabledFeaturesBase::is_overlay_property_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_safe_printable_inset_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_svg_path_length_css_property_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_functions_enabled_ = true;
bool RuntimeEnabledFeaturesBase::is_first_line_on_list_item_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_grid_gap_suppression_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_gap_decoration_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_multicol_column_wrapping_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_font_size_adjust_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_font_language_override_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_line_clamp_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_flex_wrap_balance_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_grid_lanes_layout_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_pseudo_scroll_markers_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_pseudo_elements_focusable_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_scrollbar_color_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_text_overflow_clip_with_selection_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_disable_ellipsis_when_scrolled_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_fed_cm_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_login_element_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_fenced_frames_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_geolocation_element_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_menu_elements_enabled_ = false;
bool RuntimeEnabledFeaturesBase::InstallElementEnabled(const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::UserMediaElementEnabled(
    const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::OriginTrialsSampleAPIEnabled(
    const FeatureContext*) {
  return false;
}
bool RuntimeEnabledFeaturesBase::
    is_scroll_timeline_named_range_scroll_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_layout_box_rect_getters_use_fragments_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_visual_rect_mapping_fix_for_expansion_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_offset_path_transform_update_fix_enabled_ = false;
bool RuntimeEnabledFeaturesBase::
    is_css_shape_ellipse_circle_position_serialization_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_color_space_rec_2100_linear_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_stacking_context_is_not_stacked_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_single_axis_scroll_containers_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_layout_ignore_margins_for_sticky_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_anchor_with_transforms_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_composite_bg_color_animation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_text_decoration_skip_ink_all_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_forced_colors_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_event_trigger_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_animation_trigger_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_route_matching_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_border_shape_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_use_original_dom_offsets_for_offset_map_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_color_space_display_p_3_linear_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_timeline_trigger_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_composite_clip_path_animation_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_emphasis_position_auto_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_overlay_global_rule_removal_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_emphasis_with_ruby_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_css_system_accent_color_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_web_app_scope_system_accent_color_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_tab_size_with_spacing_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_font_fallback_for_tab_size_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_text_spacing_trim_fallback_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_system_fallback_emoji_vs_support_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_spacing_trim_fallback_2_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_spacing_trim_fallback_chws_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_spacing_trim_yu_gothic_ui_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_text_emphasis_letter_spacing_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_ignore_letter_spacing_in_cursive_scripts_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_extended_shape_cache_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_word_spacing_white_space_pre_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_memory_consumer_for_ng_shape_cache_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_tab_size_ancestor_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_collapse_zero_width_space_when_reuse_item_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_skip_oof_item_for_break_candidate_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_first_line_text_metrics_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_bidi_caret_affinity_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_svg_length_resolve_unparsed_value_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_css_line_clamp_lines_and_height_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_layout_table_cell_alignment_safe_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_layout_image_empty_natural_size_before_size_available_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_list_owner_must_have_css_box_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_fragmented_oof_in_cb_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_use_position_for_point_in_flexible_box_with_single_child_element_enabled_ =
    false;

namespace features {
extern constinit const base::Feature kBakedGamutMapping(
    "BakedGamutMapping",
    base::FEATURE_DISABLED_BY_DEFAULT,
    base::internal::FeatureMacroHandshake::kSecret);
}  // namespace features

String ToString(unsigned value) {
  return String::Number(value);
}

void ExceptionState::ThrowTypeError(const char*) {}

const WrapperTypeInfo& CSSKeywordValue::wrapper_type_info_ =
    *static_cast<const WrapperTypeInfo*>(nullptr);
const WrapperTypeInfo& CSSStyleValue::wrapper_type_info_ =
    *static_cast<const WrapperTypeInfo*>(nullptr);

CSSStyleValue* CrossThreadUnparsedValue::ToCSSStyleValue() {
  return nullptr;
}
std::unique_ptr<CrossThreadStyleValue> CrossThreadUnparsedValue::IsolatedCopy()
    const {
  return std::make_unique<CrossThreadUnparsedValue>(value_);
}
bool CrossThreadUnparsedValue::operator==(
    const CrossThreadStyleValue& other) const {
  if (auto* value = DynamicTo<CrossThreadUnparsedValue>(other)) {
    return value_ == value->value_;
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
bool CrossThreadUnitValue::operator==(const CrossThreadStyleValue& other)
    const {
  if (auto* value = DynamicTo<CrossThreadUnitValue>(other)) {
    return value_ == value->value_ && unit_ == value->unit_;
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
  if (auto* value = DynamicTo<CrossThreadUnsupportedValue>(other)) {
    return value_ == value->value_;
  }
  return false;
}

String CSSStyleValue::toString() const {
  return String();
}
String CSSValue::CssText() const {
  return String();
}
bool CSSValue::operator==(const CSSValue& other) const {
  return this == &other;
}
CSSValue* CSSValue::Create(const Length&, float) {
  return nullptr;
}
void CSSValue::Trace(Visitor*) const {}
bool CSSValue::HasRandomFunctions() const {
  return false;
}
const CSSValue& CSSValue::PopulateWithTreeScope(const TreeScope*) const {
  return *this;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
CSSValuePool& CssValuePool() {
  return *static_cast<CSSValuePool*>(nullptr);
}
#endif
void ScopedCSSName::Trace(Visitor*) const {}
bool Longhand::ApplyParentValueIfZoomChanged(StyleResolverState&) const {
  return false;
}
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
const char* ScriptWrappable::GetHumanReadableName() const {
  return "ScriptWrappable";
}
void ScriptWrappable::Trace(Visitor*) const {}
v8::Local<v8::Value> ScriptWrappable::Wrap(ScriptState*) {
  return v8::Local<v8::Value>();
}
v8::Local<v8::Object> ScriptWrappable::AssociateWithWrapper(
    v8::Isolate*,
    const WrapperTypeInfo*,
    v8::Local<v8::Object> wrapper) {
  return wrapper;
}

ExternalSVGResourceDocumentContent::ExternalSVGResourceDocumentContent(
    const KURL& url,
    const CSSUrlRequestModifiers& modifiers)
    : SVGResource(), url_(url), modifiers_(modifiers) {}

void FrameSelection::LayoutBlockWillBeDestroyed(const LayoutBlock&) {}
void LayoutSVGText::SetNeedsTextMetricsUpdate() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void FragmentItems::DirtyLinesFromChangedChild(
    const LayoutObject&,
    const LayoutBlockFlow&) {}
void FragmentItems::LayoutObjectWillBeDestroyed(const LayoutObject&) {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
InlineCursor::InlineCursor(const PhysicalBoxFragment&) {}
InlineCursor::InlineCursor(const LayoutBlockFlow&) {}
InlineCursor InlineCursor::CursorForDescendants() const {
  return InlineCursor();
}
void InlineCursor::MoveToFirstLine() {
  MakeNull();
}
void InlineCursor::MoveToNext() {
  MakeNull();
}
void InlineCursor::MoveToNextSkippingChildren() {
  MakeNull();
}
void InlineCursor::MoveToNextLine() {
  MakeNull();
}
void InlineCursor::MoveTo(const LayoutObject&) {
  MakeNull();
}
void InlineCursor::MoveToNextForSameLayoutObject() {
  MakeNull();
}
#endif
void TextOverflowPostLayoutSnapshot::Trace(Visitor* visitor) const {
  visitor->Trace(scroller_);
}
TextOverflowPostLayoutSnapshot::TextOverflowPostLayoutSnapshot(
    PaintLayerScrollableArea& scroller)
    : PostLayoutSnapshotClient(nullptr), scroller_(&scroller) {}
bool TextOverflowPostLayoutSnapshot::UpdateSnapshot() {
  return false;
}
bool TextOverflowPostLayoutSnapshot::ShouldScheduleNextService() {
  return false;
}
void LayoutBlockFlow::StyleDidChange(
    StyleDifference diff,
    const ComputedStyle* old_style,
    const LayoutObject::StyleChangeContext& style_change_context) {
  LayoutObject::StyleDidChange(diff, old_style, style_change_context);
  UpdateFromStyle();
}
bool LayoutBlockFlow::CreatesNewFormattingContext() const {
  return false;
}
void LayoutBlockFlow::Trace(Visitor*) const {}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
BoxPainterBase::FillLayerInfo BoxFragmentPainter::GetFillLayerInfo(
    const Color&,
    const FillLayer& fill_layer,
    BackgroundBleedAvoidance bleed,
    bool,
    PaintFlags paint_flags) const {
  return BoxPainterBase::FillLayerInfo(
      *static_cast<const Document*>(nullptr),
      *static_cast<const ComputedStyle*>(nullptr), false, Color(), fill_layer,
      bleed, PhysicalBoxSides(), false, false, paint_flags);
}
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
int OutlinePainter::OutlineOutsetExtent(const ComputedStyle&,
                                        const LayoutObject::OutlineInfo&) {
  return 0;
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
#endif
void BlockPaintInvalidator::InvalidatePaint(const PaintInvalidatorContext&) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PhysicalBoxFragment::RecalcInkOverflow() {}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
wtf_size_t GridLineResolver::SubgridSpanSize(GridTrackSizingDirection) const {
  return 0;
}
#endif

LayoutImage* LayoutImage::CreateAnonymous(Document&) {
  return nullptr;
}
void LayoutImage::SetImageResource(LayoutImageResource* image_resource) {
  StandaloneRendererNoteLayoutImageSetResource();
  image_resource_ = image_resource;
  if (image_resource_) {
    image_resource_->Initialize(this);
  }
}
LayoutListMarkerImage* LayoutListMarkerImage::CreateAnonymous(Document*) {
  return nullptr;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
LayoutTextFragment* LayoutTextFragment::CreateAnonymous(Document&,
                                                        const String&) {
  return nullptr;
}
#endif
String LayoutCounter::GenerateCounterText(Vector<int>,
                                          const CounterStyle*,
                                          const AtomicString&) {
  return String();
}
LayoutCounter::LayoutCounter(Document& document, const CounterContentData& data)
    : LayoutText(&document, String()), counter_(&data) {}
#if !defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
LayoutImageResource::LayoutImageResource() = default;
#endif
LayoutImageResourceStyleImage::LayoutImageResourceStyleImage(StyleImage*) {}
StyleImageSet::StyleImageSet(StyleImage* image, CSSImageSetValue* value)
    : best_fit_image_(image), image_set_value_(value) {}

gfx::RectF TransformHelper::ComputeReferenceBox(const LayoutObject&) {
  return gfx::RectF();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void ReferenceFilterOperation::AddClient(SVGResourceClient&) {}
void ReferenceFilterOperation::RemoveClient(SVGResourceClient&) {}
#endif

Path StylePath::GetPath(const gfx::RectF&, float, float) const {
  return Path();
}
CSSValue* StylePath::ComputedCSSValue() const {
  return nullptr;
}
bool StylePath::IsEqualAssumingSameType(const BasicShape&) const {
  return false;
}

bool IsSupportedImageMimeType(std::string_view) {
  return false;
}

ColorChannelKeyword CSSValueIDToColorChannelKeyword(CSSValueID) {
  return static_cast<ColorChannelKeyword>(0);
}
CSSValueID ColorChannelKeywordToCSSValueID(ColorChannelKeyword) {
  return CSSValueID::kInvalid;
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
double FontSizeFunctions::SnapToClosestFontScaleBucket(double value) {
  return value;
}

namespace {

FontDescription StandaloneDefaultFontDescription() {
  FontDescription description;
  description.SetSpecifiedSize(16.0f);
  description.SetComputedSize(16.0f);
  description.SetAdjustedSize(16.0f);
  description.SetKeywordSize(FontSizeFunctions::InitialKeywordSize());
  description.SetGenericFamily(FontDescription::kStandardFamily);
  return description;
}

}  // namespace

Font::Font() : font_description_(StandaloneDefaultFontDescription()) {}
Font::Font(const FontDescription& description)
    : font_description_(description) {}
Font::Font(const FontDescription& description, FontSelector*)
    : font_description_(description) {}
bool Font::operator==(const Font& other) const {
  return GetFontSelector() == other.GetFontSelector() &&
         font_description_ == other.GetFontDescription();
}
void Font::WillUseFontData(const String&) const {}
FontFallbackList* Font::EnsureFontFallbackList() const {
  if (!font_fallback_list_) {
    font_fallback_list_ = MakeGarbageCollected<FontFallbackList>(GetFontSelector());
  }
  return font_fallback_list_.Get();
}
base::span<const FontFeatureRange> Font::GetFontFeatures() const {
  return {};
}
bool Font::HasNonInitialFontFeatures() const {
  return false;
}
bool Font::HasSimpleFontFeatures() const {
  return true;
}
std::pair<float, bool> Font::TabWidthInternal(const SimpleFontData*,
                                              const TabSize&) const {
  return {32.0f, true};
}
float Font::TabWidth(const SimpleFontData* font_data,
                     const TabSize& tab_size,
                     float position) const {
  const auto [base_tab_width, is_successed] =
      TabWidthInternal(font_data, tab_size);
  if (!is_successed || base_tab_width <= 0.0f) {
    return 0.0f;
  }
  return base_tab_width - fmodf(position, base_tab_width);
}
void Font::DrawText(cc::PaintCanvas* canvas,
                    const TextFragmentPaintInfo& text_info,
                    const gfx::PointF& point,
                    cc::NodeId node_id,
                    const cc::PaintFlags& flags,
                    DrawType draw_type) const {
  if (ShouldSkipDrawing() || !canvas) {
    return;
  }
  ShapeResultBloberizer::FillGlyphsNG bloberizer(
      GetFontDescription(), text_info.text, text_info.from, text_info.to,
      text_info.shape_result,
      draw_type == Font::DrawType::kGlyphsOnly
          ? ShapeResultBloberizer::Type::kNormal
          : ShapeResultBloberizer::Type::kEmitText);
  DrawTextBlobs(bloberizer.Blobs(), *canvas, point, flags, node_id);
}
void Font::DrawEmphasisMarks(cc::PaintCanvas*,
                             const TextFragmentPaintInfo&,
                             const AtomicString&,
                             const gfx::PointF&,
                             const cc::PaintFlags&) const {}
int Font::EmphasisMarkHeight(const AtomicString&) const {
  return 0;
}
PlainTextPainter& PlainTextPainter::Shared() {
  alignas(PlainTextPainter) static unsigned char storage[sizeof(PlainTextPainter)];
  return *reinterpret_cast<PlainTextPainter*>(storage);
}
bool PlainTextPainter::DrawWithBidiReorder(const TextRun&,
                                           unsigned,
                                           unsigned,
                                           const Font&,
                                           Font::CustomFontNotReadyAction,
                                           cc::PaintCanvas&,
                                           const gfx::PointF&,
                                           const cc::PaintFlags&,
                                           Font::DrawType) {
  return false;
}
FontFallbackList::FontFallbackList(FontSelector* font_selector)
    : font_selector_(font_selector) {}
void FontFallbackList::Trace(Visitor*) const {}
bool FontFallbackList::ShouldSkipDrawing() const {
  return false;
}
const SimpleFontData* FontFallbackList::DeterminePrimarySimpleFontData(
    const FontDescription& font_description,
    int,
    bool) {
  AtomicString family_name = font_description.Family().FamilyName();
  if (family_name.empty() || font_description.Family().FamilyIsGeneric()) {
    switch (font_description.GenericFamily()) {
      case FontDescription::kStandardFamily:
      case FontDescription::kWebkitBodyFamily:
      case FontDescription::kNoFamily:
      case FontDescription::kSerifFamily:
        family_name = AtomicString("Times New Roman");
        break;
      case FontDescription::kMonospaceFamily:
        family_name = AtomicString("Consolas");
        break;
      case FontDescription::kSansSerifFamily:
      case FontDescription::kCursiveFamily:
      case FontDescription::kFantasyFamily:
        family_name = AtomicString("Arial");
        break;
    }
  }
  return FontCache::Get().GetFontData(font_description, family_name);
}

const SimpleFontData* FontCache::GetFontData(
    const FontDescription& font_description,
    const AtomicString& family_name,
    AlternateFontName) {
  static std::map<std::string, Persistent<FontPlatformData>*>
      platform_data_by_key;
  static std::map<std::string, Persistent<SimpleFontData>*>
      simple_font_data_by_key;
  const float computed_size =
      font_description.ComputedSize() > 0 ? font_description.ComputedSize()
                                          : 16.0f;
  const int size_key = static_cast<int>(std::round(computed_size * 64.0f));
  std::string requested_family =
      family_name.empty() ? "Arial" : family_name.GetString().Utf8();
  const SkFontStyle requested_style = font_description.SkiaFontStyle();
  const std::string cache_key =
      requested_family + "#" + std::to_string(size_key) + "#" +
      std::to_string(requested_style.weight()) + "#" +
      std::to_string(requested_style.width()) + "#" +
      std::to_string(requested_style.slant());
  auto simple_it = simple_font_data_by_key.find(cache_key);
  if (simple_it != simple_font_data_by_key.end() && *simple_it->second) {
    return simple_it->second->Get();
  }

  sk_sp<SkTypeface> typeface;
  if (sk_sp<SkFontMgr> font_manager = skia::DefaultFontMgr()) {
    typeface =
        font_manager->matchFamilyStyle(requested_family.c_str(),
                                       requested_style);
    if (!typeface) {
      typeface = font_manager->legacyMakeTypeface(requested_family.c_str(),
                                                  requested_style);
    }
    if (!typeface && font_manager->countFamilies() > 0) {
      SkString family_name;
      font_manager->getFamilyName(0, &family_name);
      typeface =
          font_manager->matchFamilyStyle(family_name.c_str(),
                                         requested_style);
    }
  }
  if (!typeface) {
    typeface = SkTypeface::MakeEmpty();
  }

  auto* platform_data = new Persistent<FontPlatformData>();
  const bool synthetic_bold =
      font_description.Weight() >= kBoldThreshold && typeface &&
      !typeface->isBold();
  const bool synthetic_italic =
      font_description.Style() == kItalicSlopeValue && typeface &&
      !typeface->isItalic();
  *platform_data = MakeGarbageCollected<FontPlatformData>(
      std::move(typeface), std::string(), computed_size, synthetic_bold,
      synthetic_italic, TextRenderingMode::kAutoTextRendering,
      ResolvedFontFeatures{});
  auto* simple_font_data = new Persistent<SimpleFontData>();
  *simple_font_data =
      MakeGarbageCollected<SimpleFontData>(platform_data->Get(), nullptr);
  platform_data_by_key[cache_key] = platform_data;
  simple_font_data_by_key[cache_key] = simple_font_data;
  return simple_font_data->Get();
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
void TimerBase::RunInternal() {}
base::TimeTicks TimerBase::TimerCurrentTimeTicks() const {
  return base::TimeTicks();
}
void TimerBase::SetNextFireTime(base::TimeTicks next_fire_time) {
  next_fire_time_ = next_fire_time;
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

AbstractInlineTextBox* AbstractInlineTextBox::GetOrCreate(
    const InlineCursor&) {
  return nullptr;
}
void AbstractInlineTextBox::WillDestroy(const InlineCursor&) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool LayoutTextCombine::NeedsAffineTransformInPaint() const {
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
#endif
void ContentCaptureManager::ScheduleTaskIfNeeded(const Node&) {}
void ContentCaptureManager::OnLayoutTextWillBeDestroyed(const Node&) {}
void ContentCaptureManager::OnNodeTextChanged(Node&) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
std::ostream& operator<<(std::ostream& ostream, const FragmentItem*) {
  return ostream;
}
#endif
std::ostream& operator<<(std::ostream& ostream, TextDirection direction) {
  return ostream << static_cast<int>(direction);
}
template <unsigned fractional_bits, typename Storage>
std::ostream& operator<<(std::ostream& ostream,
                         const FixedPoint<fractional_bits, Storage>&) {
  return ostream;
}
template std::ostream& operator<<<16, int>(std::ostream&,
                                           const FixedPoint<16, int>&);
template std::ostream& operator<<<16, int64_t>(
    std::ostream&,
    const FixedPoint<16, int64_t>&);
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool OffsetMapping::IsBeforeNonCollapsedContent(const Position&) const {
  return false;
}
bool OffsetMapping::IsAfterNonCollapsedContent(const Position&) const {
  return false;
}
std::optional<UChar> OffsetMapping::GetCharacterBefore(
    const Position&) const {
  return std::nullopt;
}
const OffsetMapping* OffsetMapping::GetFor(const LayoutObject*) {
  return nullptr;
}
base::span<const OffsetMappingUnit>
OffsetMapping::GetMappingUnitsForTextContentOffsetRange(unsigned,
                                                        unsigned) const {
  return {};
}
base::span<const OffsetMappingUnit> OffsetMapping::GetMappingUnitsForNode(
    const Node&) const {
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
const Node* OffsetMappingUnit::AssociatedNode() const {
  return nullptr;
}
unsigned OffsetMappingUnit::ConvertTextContentToLastDOMOffset(
    unsigned offset) const {
  return offset;
}
#endif
TextIteratorBehavior::TextIteratorBehavior() {
  values_.all = 0;
}

void SVGResource::AddClient(SVGResourceClient&) {}
void SVGResource::RemoveClient(SVGResourceClient&) {}
void SVGResource::AddObserver(ImageResourceObserver&) {}
void SVGResource::RemoveObserver(ImageResourceObserver&) {}
SVGResourceClient* SVGResource::GetObserverResourceClient(
    ImageResourceObserver&) {
  return nullptr;
}
LayoutSVGResourceContainer* SVGResource::ResourceContainerNoCycleCheck()
    const {
  return nullptr;
}

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

ExternalSVGResourceImageContent::ExternalSVGResourceImageContent(
    ImageResourceContent* image_content,
    const AtomicString& fragment)
    : image_content_(image_content), fragment_(fragment) {}
void ExternalSVGResourceImageContent::Trace(Visitor* visitor) const {
  SVGResource::Trace(visitor);
  visitor->Trace(image_content_);
}
void ExternalSVGResourceImageContent::Prefinalize() {}
bool ExternalSVGResourceImageContent::IsLoading() const {
  return false;
}
Element* ExternalSVGResourceImageContent::ResolveTarget() {
  return nullptr;
}
void ExternalSVGResourceImageContent::ImageNotifyFinished(ImageResourceContent*) {}
String ExternalSVGResourceImageContent::DebugName() const {
  return "ExternalSVGResourceImageContent";
}

void MathMLSpaceElement::AddMathBaselineIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLPaddedElement::AddMathBaselineIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLPaddedElement::AddMathPaddedDepthIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLPaddedElement::AddMathPaddedLSpaceIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLPaddedElement::AddMathPaddedVOffsetIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLFractionElement::AddMathFractionBarThicknessIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLOperatorElement::AddMathLSpaceIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLOperatorElement::AddMathRSpaceIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLOperatorElement::AddMathMinSizeIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}
void MathMLOperatorElement::AddMathMaxSizeIfNeeded(
    ComputedStyleBuilder&,
    const CSSToLengthConversionData&) {}

const RouteMap* RouteMap::Get(const Document*) {
  return nullptr;
}
RouteMap* RouteMap::Get(Document*) {
  return nullptr;
}
RouteMap& RouteMap::Ensure(Document&) {
  return *static_cast<RouteMap*>(nullptr);
}
void RouteMap::AddRouteFromRule(const String&, URLPattern*) {}
void RouteMap::AddAnonymousRoute(URLPattern*) {}
const Route* RouteMap::FindRoute(const String&) const {
  return nullptr;
}
const Route* RouteMap::FindRoute(const URLPattern*) const {
  return nullptr;
}
void RouteMap::GetActiveRoutes(NavigationPreposition, MatchCollection*) const {}

network::mojom::ReferrerPolicy ReferrerUtils::MojoReferrerPolicyResolveDefault(
    network::mojom::ReferrerPolicy policy) {
  return policy == network::mojom::ReferrerPolicy::kDefault
             ? network::mojom::ReferrerPolicy::kStrictOriginWhenCrossOrigin
             : policy;
}

FontResource* FontResource::Fetch(FetchParameters&,
                                  ResourceFetcher*,
                                  FontResourceClient*) {
  return nullptr;
}
void FontResource::Trace(Visitor* visitor) const {
  Resource::Trace(visitor);
}
void ResourceFetcher::EmulateLoadStartedForInspector(
    Resource*,
    mojom::blink::RequestContextType,
    network::mojom::RequestDestination,
    const AtomicString&) {}
void ImageResourceContent::EmulateLoadStartedForInspector(ResourceFetcher*,
                                                          const AtomicString&) {
}
CSSPaintImageGenerator* CSSPaintImageGenerator::Create(const String&,
                                                       const Document&,
                                                       Observer*) {
  return nullptr;
}
std::optional<PaintWorkletStylePropertyMap::CrossThreadData>
PaintWorkletStylePropertyMap::BuildCrossThreadData(
    const Document&,
    UniqueObjectId,
    const ComputedStyle&,
    const Vector<CSSPropertyID>&,
    const Vector<AtomicString>&,
    CompositorPaintWorkletInput::PropertyKeys&) {
  return std::nullopt;
}
scoped_refptr<PaintWorkletDeferredImage> PaintWorkletDeferredImage::Create(
    scoped_refptr<PaintWorkletInput>,
    const gfx::SizeF&) {
  return nullptr;
}

StyleFetchedImage::StyleFetchedImage(ImageResourceContent* image,
                                     const CSSUrlData& url_data,
                                     const Document& document,
                                     const KURL& url,
                                     const float override_image_resolution)
    : image_(image),
      url_data_(&url_data),
      document_(&document),
      url_(url),
      override_image_resolution_(override_image_resolution) {}
StyleFetchedImage::~StyleFetchedImage() = default;
WrappedImagePtr StyleFetchedImage::Data() const { return image_.Get(); }
float StyleFetchedImage::ImageScaleFactor() const { return 1.0f; }
CSSValue* StyleFetchedImage::CssValue() const { return nullptr; }
CSSValue* StyleFetchedImage::ComputedCSSValue(const ComputedStyle&,
                                              bool,
                                              CSSValuePhase) const {
  return nullptr;
}
bool StyleFetchedImage::CanRender() const { return false; }
bool StyleFetchedImage::IsLoaded() const { return false; }
bool StyleFetchedImage::IsLoading() const { return false; }
bool StyleFetchedImage::ErrorOccurred() const { return true; }
bool StyleFetchedImage::IsCorsSameOrigin(String&) const { return false; }
NaturalSizingInfo StyleFetchedImage::GetNaturalSizingInfo(
    float,
    RespectImageOrientationEnum) const {
  return NaturalSizingInfo::None();
}
gfx::SizeF StyleFetchedImage::ImageSize(float,
                                        const gfx::SizeF& default_object_size,
                                        RespectImageOrientationEnum) const {
  return default_object_size;
}
bool StyleFetchedImage::HasIntrinsicSize() const { return false; }
void StyleFetchedImage::AddClient(ImageResourceObserver*) {}
void StyleFetchedImage::RemoveClient(ImageResourceObserver*) {}
scoped_refptr<Image> StyleFetchedImage::GetImage(const ImageResourceObserver&,
                                                 const Node&,
                                                 const ComputedStyle&,
                                                 const gfx::SizeF&) const {
  return nullptr;
}
bool StyleFetchedImage::KnownToBeOpaque(const Document&,
                                        const ComputedStyle&) const {
  return false;
}
ImageResourceContent* StyleFetchedImage::CachedImage() const {
  return image_.Get();
}
void StyleFetchedImage::Trace(Visitor* visitor) const {
  visitor->Trace(image_);
  visitor->Trace(url_data_);
  visitor->Trace(document_);
  StyleImage::Trace(visitor);
}
bool StyleFetchedImage::IsEqual(const StyleImage& other) const {
  return this == &other;
}
void StyleFetchedImage::Prefinalize() {}
void StyleFetchedImage::ImageNotifyFinished(ImageResourceContent*) {}
bool StyleFetchedImage::GetImageAnimationPolicy(
    mojom::blink::ImageAnimationPolicy&) {
  return false;
}
bool StyleFetchedImage::CanBeSpeculativelyDecoded() const {
  return false;
}

LayoutCounter::~LayoutCounter() = default;
void LayoutCounter::Trace(Visitor* visitor) const {
  visitor->Trace(counter_);
  LayoutText::Trace(visitor);
}
void LayoutCounter::WillBeDestroyed() {
  LayoutText::WillBeDestroyed();
}

#if !defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
LayoutImageResource::~LayoutImageResource() = default;
void LayoutImageResource::Trace(Visitor* visitor) const {
  visitor->Trace(cached_image_);
  visitor->Trace(layout_object_);
}
void LayoutImageResource::Initialize(LayoutObject* layout_object) {
  StandaloneRendererNoteLayoutImageResourceInitialize();
  layout_object_ = layout_object;
}
void LayoutImageResource::Shutdown() {
  layout_object_ = nullptr;
  cached_image_ = nullptr;
}
scoped_refptr<Image> LayoutImageResource::GetImage(const gfx::SizeF&) const {
  StandaloneRendererNoteLayoutImageResourceGetImage();
  return nullptr;
}
NaturalSizingInfo LayoutImageResource::GetNaturalDimensions(float) const {
  StandaloneRendererNoteLayoutImageResourceNaturalDimensions();
  return NaturalSizingInfo::None();
}
RespectImageOrientationEnum LayoutImageResource::ImageOrientation() const {
  return kDoNotRespectImageOrientation;
}
#endif

LayoutImageResourceStyleImage::~LayoutImageResourceStyleImage() = default;
void LayoutImageResourceStyleImage::Trace(Visitor* visitor) const {
  visitor->Trace(style_image_);
  LayoutImageResource::Trace(visitor);
}
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

StyleImageSet::~StyleImageSet() = default;
CSSValue* StyleImageSet::CssValue() const {
  return image_set_value_.Get();
}
CSSValue* StyleImageSet::ComputedCSSValue(const ComputedStyle&,
                                          bool,
                                          CSSValuePhase) const {
  return image_set_value_.Get();
}
WrappedImagePtr StyleImageSet::Data() const {
  return best_fit_image_ ? best_fit_image_->Data() : nullptr;
}
bool StyleImageSet::CanRender() const {
  return best_fit_image_ && best_fit_image_->CanRender();
}
bool StyleImageSet::IsLoaded() const {
  return !best_fit_image_ || best_fit_image_->IsLoaded();
}
bool StyleImageSet::IsLoading() const {
  return best_fit_image_ && best_fit_image_->IsLoading();
}
bool StyleImageSet::ErrorOccurred() const {
  return best_fit_image_ && best_fit_image_->ErrorOccurred();
}
bool StyleImageSet::IsCorsSameOrigin(String& failing_url) const {
  return !best_fit_image_ || best_fit_image_->IsCorsSameOrigin(failing_url);
}
NaturalSizingInfo StyleImageSet::GetNaturalSizingInfo(
    float multiplier,
    RespectImageOrientationEnum orientation) const {
  return best_fit_image_
             ? best_fit_image_->GetNaturalSizingInfo(multiplier, orientation)
             : NaturalSizingInfo::None();
}
gfx::SizeF StyleImageSet::ImageSize(
    float multiplier,
    const gfx::SizeF& default_object_size,
    RespectImageOrientationEnum orientation) const {
  return best_fit_image_ ? best_fit_image_->ImageSize(
                               multiplier, default_object_size, orientation)
                         : default_object_size;
}
bool StyleImageSet::HasIntrinsicSize() const {
  return best_fit_image_ && best_fit_image_->HasIntrinsicSize();
}
void StyleImageSet::AddClient(ImageResourceObserver* observer) {
  if (best_fit_image_) {
    best_fit_image_->AddClient(observer);
  }
}
void StyleImageSet::RemoveClient(ImageResourceObserver* observer) {
  if (best_fit_image_) {
    best_fit_image_->RemoveClient(observer);
  }
}
scoped_refptr<Image> StyleImageSet::GetImage(const ImageResourceObserver&,
                                             const Node&,
                                             const ComputedStyle&,
                                             const gfx::SizeF&) const {
  return nullptr;
}
float StyleImageSet::ImageScaleFactor() const {
  return best_fit_image_ ? best_fit_image_->ImageScaleFactor() : 1.0f;
}
bool StyleImageSet::KnownToBeOpaque(const Document& document,
                                    const ComputedStyle& style) const {
  return best_fit_image_ && best_fit_image_->KnownToBeOpaque(document, style);
}
ImageResourceContent* StyleImageSet::CachedImage() const {
  return best_fit_image_ ? best_fit_image_->CachedImage() : nullptr;
}
void StyleImageSet::Trace(Visitor* visitor) const {
  visitor->Trace(best_fit_image_);
  visitor->Trace(image_set_value_);
  StyleImage::Trace(visitor);
}
bool StyleImageSet::IsEqual(const StyleImage& other) const {
  return this == &other;
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif

unsigned CSSValue::Hash() const {
  return static_cast<unsigned>(GetClassType());
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

WebThemeEngine* WebThemeEngineHelper::GetNativeThemeEngine() {
  return nullptr;
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool PhysicalFragment::IsImplicitAnchor() const {
  return false;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
ShapeOutsideInfo::InfoMap& ShapeOutsideInfo::GetInfoMap() {
  return *static_cast<ShapeOutsideInfo::InfoMap*>(nullptr);
}
#endif
const TableBorders* TableNode::GetTableBorders() const {
  return nullptr;
}
LayoutUnit TableNode::ComputeTableInlineSize(
    const ConstraintSpace&,
    const BoxStrut&) const {
  return LayoutUnit();
}
LayoutUnit TableNode::ComputeCaptionBlockSize(const ConstraintSpace&) const {
  return LayoutUnit();
}
void FinalizeTableCellLayout(LayoutUnit, BoxFragmentBuilder*) {}
void MeasureCache::LayoutObjectWillBeDestroyed() {}
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void FragmentItems::ClearAssociatedFragments(LayoutObject*) {}
void FragmentItems::FinalizeAfterLayout(
    const HeapVector<Member<const LayoutResult>, 1>&,
    LayoutBlockFlow&) {}
const LayoutResult* LayoutResult::CloneWithPostLayoutFragments(
    const LayoutResult& result) {
  return &result;
}
void LayoutResult::CopyMutableOutOfFlowData(const LayoutResult&) const {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const LayoutResult* BlockNode::Layout(const ConstraintSpace&,
                                      const BlockBreakToken*,
                                      const EarlyBreak*,
                                      const ColumnSpannerPath*) const {
  return nullptr;
}
MinMaxSizesResult BlockNode::ComputeMinMaxSizes(
    WritingMode,
    SizeType,
    const ConstraintSpace&,
    MinMaxSizesFloatInput) const {
  return MinMaxSizesResult();
}
#endif

unsigned DisableLayoutSideEffectsScope::count_ = 0;
void PaintLayerScrollableArea::SetScrollOffsetUnconditionally(
    const ScrollOffset&,
    mojom::blink::ScrollType) {}
void PaintLayerScrollableArea::EnqueueForSnapUpdateIfNeeded() {}
void PaintLayerScrollableArea::ClampScrollOffsetAfterOverflowChange() {}
void PaintLayerScrollableArea::UpdateAfterOverflowRecalc() {}
ScrollOffset PaintLayerScrollableArea::GetScrollOffset() const {
  return ScrollOffset();
}
PhysicalAxes PaintLayerScrollableArea::ScrollableAxes() const {
  return PhysicalAxes();
}
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
int PaintLayerScrollableArea::HypotheticalScrollbarThickness(
    ScrollbarOrientation,
    bool) const {
  return 0;
}
bool PaintLayerScrollableArea::HitTestOverflowControls(HitTestResult&,
                                                       const gfx::Point&) {
  return false;
}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PaintLayer::ScrollContainerStatusChanged() {}
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
void PaintLayer::Trace(Visitor*) const {}
String PaintLayer::DebugName() const {
  return String("PaintLayer");
}
DOMNodeId PaintLayer::OwnerNodeId(bool) const {
  return kInvalidDOMNodeId;
}
void PaintLayer::RemoveOnlyThisLayerAfterStyleChange(const ComputedStyle*) {}
void PaintLayer::StyleDidChange(StyleDifference, const ComputedStyle*) {}
void PaintLayer::InsertOnlyThisLayerAfterStyleChange() {}
void PaintLayer::SetNeedsCompositingInputsUpdate() {}
void PaintLayer::UpdateFilters(StyleDifference,
                               const ComputedStyle*,
                               const ComputedStyle&) {}
void PaintLayer::UpdateBackdropFilters(const ComputedStyle*,
                                       const ComputedStyle&) {}
void PaintLayer::UpdateClipPath(const ComputedStyle*, const ComputedStyle&) {}
void PaintLayer::UpdateOffsetPath(const ComputedStyle*, const ComputedStyle&) {}
void PaintLayer::UpdateTransform() {}
void PaintLayer::UpdateScrollingAfterLayout() {}
bool PaintLayer::PaintsWithFilters() const {
  return false;
}
PhysicalRect PaintLayer::MapRectForFilter(const PhysicalRect& rect) const {
  return rect;
}
gfx::RectF PaintLayer::MapRectForFilter(const gfx::RectF& rect) const {
  return rect;
}
gfx::RectF PaintLayer::FilterReferenceBox() const {
  return gfx::RectF();
}
const PaintLayer* PaintLayer::ContainingScrollContainerLayer(bool*) const {
  return nullptr;
}
gfx::Transform PaintLayer::CurrentTransform() const {
  return gfx::Transform();
}
#endif

void PrepopulatedComputedStylePropertyMap::UpdateStyle(
    const Document&,
    const ComputedStyle&) {}
void DisplayLockContext::DidLayoutChildren() {}
bool DisplayLockContext::ActivatableDisplayLocksForced() const {
  return false;
}
bool DisplayLockContext::IsScreenReaderActive() const {
  return false;
}
bool DisplayLockContext::ShouldActivateForScreenReader() const {
  return false;
}
bool Frame::IsMainFrame() const {
  return true;
}
ChromeClient& Frame::GetChromeClient() const {
  return *static_cast<ChromeClient*>(nullptr);
}
Page* Frame::GetPage() const {
  return page_.Get();
}
LayoutEmbeddedContent* Frame::OwnerLayoutObject() const {
  return nullptr;
}
String Locale::QueryString(int) {
  return String();
}
template <>
char* PartitionAllocator::AllocateVectorBacking<char>(size_t size) {
  return static_cast<char*>(std::calloc(1, size ? size : 1));
}
void* Partitions::BufferMalloc(size_t n, const char*) {
  return std::malloc(n ? n : 1);
}
void Partitions::BufferFree(void* p) {
  std::free(p);
}
void Partitions::BufferFreeWithSize(void* p, size_t) {
  std::free(p);
}
void* Partitions::FastZeroedMalloc(size_t n, const char*) {
  return std::calloc(1, n ? n : 1);
}
void* Partitions::FastMalloc(size_t n, const char*) {
  return std::malloc(n ? n : 1);
}
void Partitions::FastFree(void* p) {
  std::free(p);
}
size_t Partitions::BufferPotentialCapacity(size_t n) {
  return n;
}
void* PartitionAllocator::AllocateBacking(size_t size, const char*) {
  return std::malloc(size ? size : 1);
}
void PartitionAllocator::FreeBacking(void* address) {
  std::free(address);
}
const String& ParkableString::ToString() const {
  static const String* empty = new String();
  return impl_ ? impl_->ToString() : *empty;
}
const String& ParkableStringImpl::ToString() {
  static const String* empty = new String();
  return *empty;
}
#if defined(HTML_CSS_RENDERER_STANDALONE)
scoped_refptr<StringImpl> CaseMap::FastToLowerInvariant(StringImpl* impl) {
  return scoped_refptr<StringImpl>(impl);
}
#endif
void TextCodecCjk::RegisterEncodingNames(EncodingNameRegistrar) {}
void TextCodecCjk::RegisterCodecs(TextCodecRegistrar) {}
void TextCodecIcu::RegisterEncodingNames(EncodingNameRegistrar) {}
void TextCodecIcu::RegisterCodecs(TextCodecRegistrar) {}
IcuConverterWrapper::~IcuConverterWrapper() = default;
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool LayoutBox::IsUserScrollable() const {
  return false;
}
const PhysicalBoxFragment* LayoutBox::GetPhysicalFragment(unsigned) const {
  return nullptr;
}
const LayoutResult* LayoutBox::CachedLayoutResult(
    const ConstraintSpace&,
    const BlockBreakToken*,
    const EarlyBreak*,
    const ColumnSpannerPath*,
    std::optional<FragmentGeometry>*,
    LayoutCacheStatus*) {
  return nullptr;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool LayoutBox::MayIntersect(const HitTestResult&,
                             const HitTestLocation&,
                             const PhysicalOffset&) const {
  return false;
}
#endif
ListBasedHitTestBehavior HitTestResult::AddNodeToListBasedTestResult(
    Node*,
    const HitTestLocation&,
    const PhysicalRect&) {
  return ListBasedHitTestBehavior::kStopHitTesting;
}
ListBasedHitTestBehavior HitTestResult::AddNodeToListBasedTestResult(
    Node*,
    const HitTestLocation&,
    const cc::Region&) {
  return ListBasedHitTestBehavior::kStopHitTesting;
}
void HitTestResult::SetInnerNode(Node* node) {
  inner_node_ = node;
}
Image* ImageResourceContent::GetImage() const {
  return image_ ? image_.get() : nullptr;
}
Image::Image(ImageObserver* observer, bool is_multipart)
    : image_observer_disabled_(false),
      image_observer_(observer),
      stable_image_id_(0),
      is_multipart_(is_multipart) {}
Image::~Image() = default;
Image* Image::NullImage() {
  return nullptr;
}
Image::SizeAvailability Image::SetData(scoped_refptr<SharedBuffer> data,
                                       bool) {
  encoded_image_data_ = std::move(data);
  return encoded_image_data_ ? kSizeAvailable : kSizeUnavailable;
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
gfx::RectF Image::CorrectSrcRectForImageOrientation(gfx::SizeF,
                                                    gfx::RectF src_rect) const {
  return src_rect;
}
scoped_refptr<Image> Image::ImageForDefaultFrame() {
  return scoped_refptr<Image>(this);
}
bool Image::ApplyShader(cc::PaintFlags&,
                        const SkMatrix&,
                        const gfx::RectF&,
                        const ImageDrawOptions&) {
  return false;
}
void Image::DrawPattern(GraphicsContext&,
                        const cc::PaintFlags&,
                        const gfx::RectF&,
                        const ImageTilingInfo&,
                        const ImageDrawOptions&) {}
PaintImageBuilder Image::CreatePaintImageBuilder(
    std::optional<PaintImage::Id> paint_id) {
  auto builder = PaintImageBuilder::WithDefault();
  builder.set_id(paint_id.value_or(stable_image_id_));
  builder.set_animation_type(PaintImage::AnimationType::kStatic)
      .set_is_multipart(is_multipart_);
  return builder;
}
void BoxPaintInvalidator::InvalidatePaint() {}
void CustomScrollbar::ClearPaintFlags() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect LayoutReplaced::PreSnappedRectForPersistentSizing(
    const PhysicalRect& rect) {
  return rect;
}
#endif
#if defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect LayoutReplaced::PreSnappedRectForPersistentSizing(
    const PhysicalRect& rect) {
  return rect;
}
#endif
PhysicalOffset AnchorPositionScrollData::
    SpeculativeDefaultAnchorRememberedOffsetIncludingChained() const {
  return PhysicalOffset();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
unsigned BoxFragmentIndex(const PhysicalBoxFragment&) {
  return 0;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PositionWithAffinity PhysicalBoxFragment::PositionForPoint(
    PhysicalOffset) const {
  return PositionWithAffinity();
}
PhysicalBoxFragment::MutableForStyleRecalc
PhysicalBoxFragment::GetMutableForStyleRecalc() const {
  return MutableForStyleRecalc(base::PassKey<PhysicalBoxFragment>(),
                               const_cast<PhysicalBoxFragment&>(*this));
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
const PhysicalBoxFragment* PhysicalBoxFragment::PostLayout() const {
  return this;
}
PhysicalOffset PhysicalBoxFragment::OffsetFromOwnerLayoutBox() const {
  return PhysicalOffset();
}
void PhysicalBoxFragment::AddSelfOutlineRects(
    const PhysicalOffset&,
    OutlineType,
    OutlineRectCollector&,
    LayoutObject::OutlineInfo*) const {}
PhysicalRect PhysicalBoxFragment::ContentsInkOverflowRect() const {
  return PhysicalRect();
}
PhysicalRect PhysicalBoxFragment::SelfInkOverflowRect() const {
  return PhysicalRect();
}
PhysicalRect PhysicalBoxFragment::InkOverflowRect() const {
  return PhysicalRect();
}
#endif
PhysicalRect PhysicalBoxFragment::ContentRect() const {
  return PhysicalRect({}, Size());
}
PhysicalRect PhysicalBoxFragment::OverflowClipRect(
    const PhysicalOffset&,
    OverlayScrollbarClipBehavior) const {
  return PhysicalRect({}, Size());
}
PhysicalSize PhysicalBoxFragment::ScrollSize() const {
  return Size();
}
gfx::Vector2d PhysicalBoxFragment::PixelSnappedOverscrollContentOffset() const {
  return gfx::Vector2d();
}
gfx::Vector2d PhysicalBoxFragment::PixelSnappedScrolledContentOffset() const {
  return gfx::Vector2d();
}
bool PhysicalBoxFragment::MayIntersect(const HitTestResult&,
                                       const HitTestLocation&,
                                       const PhysicalOffset&) const {
  return true;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalOffset OffsetInStitchedFragments(const PhysicalBoxFragment&,
                                         PhysicalSize*) {
  return PhysicalOffset();
}
bool CanPaintMultipleFragments(const LayoutObject&) {
  return false;
}
bool CanPaintMultipleFragments(const PhysicalBoxFragment&) {
  return false;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const FragmentData* PhysicalFragment::GetFragmentData() const {
  return nullptr;
}
bool PhysicalFragment::IsBlockFlow() const {
  return false;
}
bool PhysicalFragment::IsTextControlContainer() const {
  return false;
}
bool PhysicalFragment::IsMonolithic() const {
  return false;
}
#endif
const PhysicalFragmentLink& GetPageBorderBoxLink(const PhysicalBoxFragment&) {
  alignas(PhysicalFragmentLink) static unsigned char storage[sizeof(PhysicalFragmentLink)] = {};
  return *reinterpret_cast<PhysicalFragmentLink*>(storage);
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect FragmentItem::SelfInkOverflowRect() const {
  return PhysicalRect();
}
#endif
InlinePaintContext::ScopedInlineItem::ScopedInlineItem(
    const FragmentItem&,
    InlinePaintContext* inline_context)
    : inline_context_(inline_context), push_count_(0) {}
InlinePaintContext::ScopedLineBox::ScopedLineBox(
    const InlineCursor&,
    InlinePaintContext* inline_context)
    : inline_context_(inline_context) {}
HighlightPainter::SelectionPaintState::SelectionPaintState(
    const InlineCursor& containing_block,
    const PhysicalOffset& box_offset,
    const std::optional<AffineTransform> writing_mode_rotation)
    : selection_status_(0, 0, SelectSoftLineBreak::kNotSelected),
      state_(SelectionState::kNone),
      containing_block_(containing_block),
      box_offset_(box_offset),
      writing_mode_rotation_(writing_mode_rotation),
      paint_selected_text_only_(false) {}
void HighlightPainter::SelectionPaintState::ComputeSelectionStyle(
    const Document&,
    const ComputedStyle&,
    Node*,
    const PaintInfo&,
    const TextPaintStyle&) {}
const PhysicalRect&
HighlightPainter::SelectionPaintState::PhysicalSelectionRect() {
  static PhysicalRect* rect = new PhysicalRect();
  return *rect;
}
void HighlightPainter::SelectionPaintState::PaintSelectionBackground(
    GraphicsContext&,
    Node*,
    const Document&,
    const ComputedStyle&,
    const PaintInfo&,
    const std::optional<AffineTransform>&) {}
void HighlightPainter::SelectionPaintState::PaintSelectedText(
    TextPainter&,
    const TextFragmentPaintInfo&,
    const TextPaintStyle&,
    DOMNodeId,
    const AutoDarkMode&) {}
void HighlightPainter::SelectionPaintState::
    PaintSuppressingTextProperWhereSelected(TextPainter&,
                                            const TextFragmentPaintInfo&,
                                            const TextPaintStyle&,
                                            DOMNodeId,
                                            const AutoDarkMode&) {}
HighlightPainter::HighlightPainter(
    const TextFragmentPaintInfo& fragment_paint_info,
    TextPainter& text_painter,
    TextDecorationPainter& decoration_painter,
    const PaintInfo& paint_info,
    const InlineCursor& cursor,
    const FragmentItem& fragment_item,
    const PhysicalOffset& box_origin,
    const ComputedStyle& style,
    const TextPaintStyle& text_style,
    SelectionPaintState* selection)
    : fragment_paint_info_(fragment_paint_info),
      text_painter_(text_painter),
      decoration_painter_(decoration_painter),
      paint_info_(paint_info),
      cursor_(cursor),
      fragment_item_(fragment_item),
      box_origin_(box_origin),
      originating_style_(style),
      originating_text_style_(text_style),
      selection_(selection),
      layout_object_(nullptr),
      node_(nullptr),
      foreground_auto_dark_mode_(AutoDarkMode::Disabled()),
      background_auto_dark_mode_(AutoDarkMode::Disabled()) {}
void HighlightPainter::PaintNonCssMarkers(Phase) {}
HighlightPainter::Case HighlightPainter::PaintCase() const {
  return kNoHighlights;
}
void HighlightPainter::PaintOriginatingShadow(const TextPaintStyle&, DOMNodeId) {}
void HighlightPainter::PaintHighlightOverlays(const TextPaintStyle&,
                                              DOMNodeId,
                                              bool,
                                              std::optional<AffineTransform>) {}
void HighlightPainter::FastPaintSpellingGrammarDecorations() {}
TextDecorationPainter::TextDecorationPainter(
    TextPainter& text_painter,
    const InlinePaintContext* inline_context,
    const PaintInfo& paint_info,
    const ComputedStyle& style,
    const TextPaintStyle& text_style,
    const LineRelativeRect& decoration_rect,
    HighlightPainter::SelectionPaintState* selection)
    : text_painter_(text_painter),
      inline_context_(inline_context),
      paint_info_(paint_info),
      style_(style),
      text_style_(text_style),
      decoration_rect_(decoration_rect),
      selection_(selection),
      step_(kBegin),
      phase_(kOriginating) {}
TextDecorationPainter::~TextDecorationPainter() = default;
void TextDecorationPainter::Begin(const FragmentItem&, Phase phase) {
  phase_ = phase;
}
void TextDecorationPainter::PaintExceptLineThrough(
    const TextFragmentPaintInfo&) {}
void TextDecorationPainter::PaintOnlyLineThrough() {}
SelectionBoundsRecorder::SelectionBoundsRecorder(SelectionState state,
                                                 PhysicalRect selection_rect,
                                                 PaintController& controller,
                                                 TextDirection direction,
                                                 WritingMode writing_mode)
    : state_(state),
      selection_rect_(selection_rect),
      paint_controller_(controller),
      text_direction_(direction),
      writing_mode_(writing_mode) {}
SelectionBoundsRecorder::~SelectionBoundsRecorder() = default;
bool SelectionBoundsRecorder::ShouldRecordSelection(const FrameSelection&,
                                                    SelectionState) {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
TextDirection FragmentItem::ResolvedDirection() const {
  return TextDirection::kLtr;
}
TextOffsetRange FragmentItem::TextOffset() const {
  return TextOffsetRange();
}
#endif
TextFragmentPaintInfo TextFragmentPaintInfo::Slice(unsigned slice_from,
                                                   unsigned slice_to) const {
  return TextFragmentPaintInfo{text, slice_from, slice_to, shape_result,
                               text_fit_scaling_factor};
}
TextFragmentPaintInfo TextFragmentPaintInfo::WithStartOffset(
    unsigned start_from) const {
  return TextFragmentPaintInfo{text, start_from, to, shape_result,
                               text_fit_scaling_factor};
}
TextFragmentPaintInfo TextFragmentPaintInfo::WithEndOffset(
    unsigned end_to) const {
  return TextFragmentPaintInfo{text, from, end_to, shape_result,
                               text_fit_scaling_factor};
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void ShapeResultView::ExpandRangeToIncludePartialGlyphs(unsigned*, unsigned*) const {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool FragmentItem::IsGeneratedText() const {
  return false;
}
AffineTransform FragmentItem::BuildSvgTransformForBoundingBox() const {
  return AffineTransform();
}
float FragmentItem::SvgScalingFactor() const {
  return 1.0f;
}
#endif
PhysicalOffset WritingModeConverter::SlowToPhysical(
    const LogicalOffset& offset,
    const PhysicalSize&) const {
  return PhysicalOffset(offset.inline_offset, offset.block_offset);
}
AffineTransform LineRelativeRect::ComputeRelativeToPhysicalTransform(
    WritingMode) const {
  return AffineTransform();
}
gfx::RectF DecorationLinePainter::Bounds(const DecorationGeometry& geometry) {
  return geometry.line;
}
DecorationGeometry DecorationGeometry::Make(StrokeStyle style,
                                            const gfx::RectF& line,
                                            float double_offset,
                                            float wavy_offset,
                                            const WaveDefinition* wave) {
  DecorationGeometry geometry;
  geometry.style = style;
  geometry.line = line;
  geometry.double_offset = double_offset;
  geometry.wavy_offset = wavy_offset;
  if (wave) {
    geometry.wavy_wave = *wave;
  }
  return geometry;
}
void DecorationLinePainter::Paint(const DecorationGeometry&,
                                  const Color&,
                                  const AutoDarkMode&,
                                  const cc::PaintFlags*) {}
int Font::EmphasisMarkDescent(const AtomicString&) const {
  return 0;
}
int Font::EmphasisMarkAscent(const AtomicString&) const {
  return 0;
}
void Font::GetTextIntercepts(const TextFragmentPaintInfo&,
                             InkSkipCJKHandling,
                             const cc::PaintFlags&,
                             const std::tuple<float, float>&,
                             Vector<TextIntercept>&) const {}
float Font::TextAutoSpaceInlineSize() const {
  return 0.0f;
}
gfx::RectF Font::TextInkBounds(const TextFragmentPaintInfo&) const {
  return gfx::RectF();
}
void Font::ReportNotDefGlyph() const {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect FragmentItem::LocalVisualRectFor(const LayoutObject&) {
  return PhysicalRect();
}
bool FragmentItem::HasSvgTransformForBoundingBox() const {
  return false;
}
void FragmentItem::InvalidateInkOverflow() {}
PhysicalRect FragmentItem::InkOverflowRect() const {
  return PhysicalRect();
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void FragmentItems::LayoutObjectWillBeMoved(const LayoutObject&) {}
#endif

LayoutSelectionStatus FrameSelection::ComputeLayoutSelectionStatus(
    const InlineCursor&) const {
  return LayoutSelectionStatus(0, 0, SelectSoftLineBreak::kNotSelected);
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect InlineCursor::CurrentLocalSelectionRectForText(
    const LayoutSelectionStatus&) const {
  return PhysicalRect();
}
#endif
bool HasPaintedOutline(const ComputedStyle&, const Node*) {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
TextOffsetMap::TextOffsetMap(wtf_size_t,
                             const TextOffsetMap&,
                             wtf_size_t,
                             const TextOffsetMap&,
                             wtf_size_t) {}
void TextOffsetMap::Append(wtf_size_t source, wtf_size_t target) {
  entries_.push_back(Entry(source, target));
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
unsigned LengthOfGraphemeCluster(const StringView& string, unsigned offset) {
  return offset < string.length() ? 1u : 0u;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool InlineNode::SetTextWithOffset(LayoutText*, String, const TextDiffRange&) {
  return false;
}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
FragmentData::RareData::RareData() = default;
FragmentData::RareData::~RareData() = default;
void FragmentData::SetLayer(PaintLayer* layer) {
  AssertIsFirst();
  if (rare_data_ || layer)
    EnsureRareData().SetLayer(layer);
}
FragmentData::RareData& FragmentData::EnsureRareData() {
  if (!rare_data_)
    rare_data_ = MakeGarbageCollected<RareData>();
  return *rare_data_;
}
void FragmentData::RareData::SetLayer(PaintLayer* new_layer) {
  if (layer && layer != new_layer) {
    layer->Destroy();
    x_sticky_constraints = nullptr;
    y_sticky_constraints = nullptr;
  }
  layer = new_layer;
}
void FragmentData::RareData::EnsureId() {
  if (!unique_id)
    unique_id = NewUniqueObjectId();
}
const FragmentData& FragmentDataList::at(unsigned) const {
  return *static_cast<const FragmentData*>(nullptr);
}
const FragmentData& FragmentDataList::back() const {
  return at(0);
}
wtf_size_t FragmentDataList::size() const {
  return 0;
}
#endif
PhysicalRect WritingModeConverter::SlowToPhysical(
    const LogicalRect&) const {
  return PhysicalRect();
}
LogicalRect WritingModeConverter::SlowToLogical(
    const PhysicalRect&) const {
  return LogicalRect();
}
LogicalOffset WritingModeConverter::SlowToLogical(
    const PhysicalOffset&,
    const PhysicalSize&) const {
  return LogicalOffset();
}
unsigned PrePaintDisableSideEffectsScope::count_ = 0;
InlinePaintContext::ScopedInlineBoxAncestors::ScopedInlineBoxAncestors(
    const InlineCursor&,
    InlinePaintContext*) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void InlineCursorPosition::RecalcInkOverflow(
    const InlineCursor&,
    InlinePaintContext*) const {}
#endif
void InlinePaintContext::ClearLineBox() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect InlineCursor::CurrentLocalRect(unsigned, unsigned) const {
  return PhysicalRect();
}
PhysicalRect InlineCursor::CurrentRectInFirstContainerFragment() const {
  return PhysicalRect();
}
const LayoutBlockFlow* InlineCursor::GetLayoutBlockFlow() const {
  return nullptr;
}
PositionWithAffinity InlineCursor::PositionForPointInChild(
    const PhysicalOffset&) const {
  return PositionWithAffinity();
}
void InlineCursor::MoveToLastForSameLayoutObject() {}
void InlineCursor::MoveToIncludingCulledInline(const LayoutObject&) {}
StringView InlineCursorPosition::Text(const InlineCursor&) const {
  return StringView();
}
#endif
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const GCedHeapVector<SplitAxisItem<LayoutBoxModelObject>>&
PhysicalFragment::StickyDescendants() const {
  return *static_cast<const GCedHeapVector<
      SplitAxisItem<LayoutBoxModelObject>>*>(nullptr);
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool ShapeOutsideInfo::IsEnabledFor(const LayoutBox&) {
  return false;
}
#endif
std::unique_ptr<Shape> Shape::CreateRasterShape(Image*,
                                                float,
                                                int,
                                                const gfx::Rect&,
                                                const gfx::Rect&,
                                                WritingMode,
                                                float,
                                                RespectImageOrientationEnum) {
  return nullptr;
}
std::unique_ptr<Shape> Shape::CreateShape(const BasicShape*,
                                          const LogicalSize&,
                                          WritingMode,
                                          float,
                                          float) {
  return nullptr;
}
std::unique_ptr<Shape> Shape::CreateLayoutBoxShape(const ContouredRect&,
                                                   WritingMode,
                                                   float) {
  return nullptr;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
MinMaxSizesResult GridLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult GridLanesLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
#endif
MinMaxSizesResult ReplacedLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult FieldsetLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult FrameSetLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult ColumnLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult MathRadicalLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult MathOperatorLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult MathTokenLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult MathUnderOverLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult MathScriptsLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MinMaxSizesResult MathRowLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
MinMaxSizesResult FlexLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
FlexLayoutAlgorithm::FlexLayoutAlgorithm(
    const LayoutAlgorithmParams& params,
    const HashMap<wtf_size_t, LayoutUnit>*)
    : LayoutAlgorithm(params),
      is_webkit_box_(false),
      is_column_(false),
      is_wrap_reverse_(false),
      is_reverse_direction_(false),
      is_multi_line_(false),
      is_horizontal_flow_(true),
      is_cross_size_definite_(false),
      balance_min_line_count_(std::nullopt),
      child_percentage_size_(LogicalSize()),
      gap_between_items_(LayoutUnit()),
      gap_between_lines_(LayoutUnit()) {}
const LayoutResult* FlexLayoutAlgorithm::Layout() {
  return nullptr;
}
#endif
MinMaxSizesResult TableLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
const LayoutResult* TableLayoutAlgorithm::Layout() {
  return nullptr;
}
TableRowLayoutAlgorithm::TableRowLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* TableRowLayoutAlgorithm::Layout() {
  return nullptr;
}
TableSectionLayoutAlgorithm::TableSectionLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* TableSectionLayoutAlgorithm::Layout() {
  return nullptr;
}
MinMaxSizesResult CustomLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
CustomLayoutAlgorithm::CustomLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params), params_(params) {}
const LayoutResult* CustomLayoutAlgorithm::Layout() {
  return nullptr;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
GridLayoutAlgorithm::GridLayoutAlgorithm(const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* GridLayoutAlgorithm::Layout() {
  return nullptr;
}
GridLanesLayoutAlgorithm::GridLanesLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* GridLanesLayoutAlgorithm::Layout() {
  return nullptr;
}
#endif
ReplacedLayoutAlgorithm::ReplacedLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* ReplacedLayoutAlgorithm::Layout() {
  return nullptr;
}
FieldsetLayoutAlgorithm::FieldsetLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params),
      writing_direction_(GetConstraintSpace().GetWritingDirection()),
      consumed_block_size_(LayoutUnit()) {}
const LayoutResult* FieldsetLayoutAlgorithm::Layout() {
  return nullptr;
}
FrameSetLayoutAlgorithm::FrameSetLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* FrameSetLayoutAlgorithm::Layout() {
  return nullptr;
}
ColumnLayoutAlgorithm::ColumnLayoutAlgorithm(const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* ColumnLayoutAlgorithm::Layout() {
  return nullptr;
}
PaginatedRootLayoutAlgorithm::PaginatedRootLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* PaginatedRootLayoutAlgorithm::Layout() {
  return nullptr;
}
MathRadicalLayoutAlgorithm::MathRadicalLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathRadicalLayoutAlgorithm::Layout() {
  return nullptr;
}
MathOperatorLayoutAlgorithm::MathOperatorLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
MathTokenLayoutAlgorithm::MathTokenLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathTokenLayoutAlgorithm::Layout() {
  return nullptr;
}
MathUnderOverLayoutAlgorithm::MathUnderOverLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathUnderOverLayoutAlgorithm::Layout() {
  return nullptr;
}
MathScriptsLayoutAlgorithm::MathScriptsLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathScriptsLayoutAlgorithm::Layout() {
  return nullptr;
}
MathRowLayoutAlgorithm::MathRowLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathRowLayoutAlgorithm::Layout() {
  return nullptr;
}
const LayoutResult* MathOperatorLayoutAlgorithm::Layout() {
  return nullptr;
}
MathSpaceLayoutAlgorithm::MathSpaceLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathSpaceLayoutAlgorithm::Layout() {
  return nullptr;
}
MinMaxSizesResult MathSpaceLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MathFractionLayoutAlgorithm::MathFractionLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathFractionLayoutAlgorithm::Layout() {
  return nullptr;
}
MinMaxSizesResult MathFractionLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
MathPaddedLayoutAlgorithm::MathPaddedLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {}
const LayoutResult* MathPaddedLayoutAlgorithm::Layout() {
  return nullptr;
}
MinMaxSizesResult MathPaddedLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  return MinMaxSizesResult();
}
bool IsValidMathMLFraction(const BlockNode&) {
  return false;
}
bool IsValidMathMLRadical(const BlockNode&) {
  return false;
}
bool IsOperatorWithSpecialShaping(const BlockNode&) {
  return false;
}
bool IsTextOnlyToken(const BlockNode&) {
  return false;
}
bool IsValidMathMLScript(const BlockNode&) {
  return false;
}
bool IsUnderOverLaidOutAsSubSup(const BlockNode&) {
  return false;
}
OutOfFlowLayoutPart::OutOfFlowLayoutPart(BoxFragmentBuilder*) {}
void OutOfFlowLayoutPart::Run() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void UpdateTransformState(const PhysicalFragment&,
                          PhysicalOffset,
                          const LayoutObject&,
                          PhysicalSize,
                          TransformState*) {}
std::optional<gfx::Transform> GetTransformForChildFragment(
    const PhysicalBoxFragment&,
    const LayoutObject&,
    PhysicalSize) {
  return std::nullopt;
}
#endif
const PhysicalBoxFragment& GetPageArea(const PhysicalBoxFragment& box) {
  return box;
}
void FragmentRepeater::DeepCloneRepeatableRoot(LayoutBox&) {}
void UpdateChildLayoutBoxLocations(const PhysicalBoxFragment&) {}
NamingScope* ToTriggerScopedName(const ScopedCSSName&, const Element&) {
  return nullptr;
}
void NamingScope::Trace(Visitor*) const {}

bool PaintLayerStackingNode::StyleDidChange(PaintLayer&,
                                            const ComputedStyle*) {
  return false;
}
PaintLayerStackingNode::PaintLayerStackingNode(PaintLayer* layer)
    : layer_(layer), z_order_lists_dirty_(true) {}
void PaintLayerStackingNode::DirtyZOrderLists() {
  pos_z_order_list_.clear();
  neg_z_order_list_.clear();
  z_order_lists_dirty_ = true;
}
void PaintLayerStackingNode::UpdateZOrderLists() {
  z_order_lists_dirty_ = false;
}
void PaintLayerStackingNode::Trace(Visitor* visitor) const {
  visitor->Trace(layer_);
  visitor->Trace(pos_z_order_list_);
  visitor->Trace(neg_z_order_list_);
  visitor->Trace(layer_to_overlay_overflow_controls_painting_after_);
}
PaintLayerScrollableArea::~PaintLayerScrollableArea() = default;
PaintLayerScrollableArea::PaintLayerScrollableArea(PaintLayer& layer)
    : ScrollableArea(nullptr),
      layer_(&layer),
      in_resize_mode_(false),
      scrolls_overflow_(false),
      needs_scroll_offset_clamp_(false),
      needs_relayout_(false),
      had_horizontal_scrollbar_before_relayout_(false),
      had_vertical_scrollbar_before_relayout_(false),
      had_resizer_before_relayout_(false),
      scroll_origin_changed_(false),
      is_scrollbar_freeze_root_(false),
      is_horizontal_scrollbar_frozen_(false),
      is_vertical_scrollbar_frozen_(false),
      scrollbar_manager_(*this),
      has_last_committed_scroll_offset_(false),
      scroll_corner_(nullptr),
      resizer_(nullptr),
      scroll_anchor_(this) {}
void PaintLayerScrollableArea::UpdateAfterStyleChange(const ComputedStyle*) {}
void PaintLayerScrollableArea::UpdateAfterLayout() {}
PaintLayerScrollableArea::DelayScrollOffsetClampScope::
    DelayScrollOffsetClampScope() {}
PaintLayerScrollableArea::DelayScrollOffsetClampScope::
    ~DelayScrollOffsetClampScope() {}
PaintLayerScrollableArea::FreezeScrollbarsRootScope::FreezeScrollbarsRootScope(
    const LayoutBox&,
    bool,
    bool) {}
PaintLayerScrollableArea::FreezeScrollbarsRootScope::
    ~FreezeScrollbarsRootScope() {}
int PaintLayerScrollableArea::FreezeScrollbarsScope::count_ = 0;
void PaintLayerScrollableArea::VisibleSizeChanged() {}
gfx::Point PaintLayerScrollableArea::ConvertFromRootFrameToVisualViewport(
    const gfx::Point& point) const {
  return point;
}
bool PaintLayerScrollableArea::ShouldOverflowControlsPaintAsOverlay() const {
  return false;
}
ChromeClient* PaintLayerScrollableArea::GetChromeClient() const {
  return nullptr;
}
PhysicalRect PaintLayerScrollableArea::ScrollIntoView(
    const PhysicalRect& rect,
    const PhysicalBoxStrut&,
    const mojom::blink::ScrollIntoViewParamsPtr&,
    std::unique_ptr<ScrollPromiseResolver::ActiveScrollTracker>) {
  return rect;
}
PhysicalOffset PaintLayerScrollableArea::LocalToScrollOriginOffset() const {
  return PhysicalOffset();
}
void PaintLayerScrollableArea::SetSnapContainerData(
    std::optional<cc::SnapContainerData>) {}
bool PaintLayerScrollableArea::SetTargetSnapAreaElementIds(
    cc::TargetSnapAreaElementIds) {
  return false;
}
std::optional<cc::SnapPositionData> PaintLayerScrollableArea::GetSnapPosition(
    const cc::SnapSelectionStrategy&) const {
  return std::nullopt;
}
void PaintLayerScrollableArea::DidAddScrollbar(Scrollbar&,
                                               ScrollbarOrientation) {}
void PaintLayerScrollableArea::WillRemoveScrollbar(Scrollbar&,
                                                   ScrollbarOrientation) {}
void PaintLayerScrollableArea::DidChangeGlobalRootScroller() {}
void PaintLayerScrollableArea::ContentsResized() {}
cc::AnimationHost* PaintLayerScrollableArea::GetCompositorAnimationHost()
    const {
  return nullptr;
}
cc::AnimationTimeline*
PaintLayerScrollableArea::GetCompositorAnimationTimeline() const {
  return nullptr;
}
bool PaintLayerScrollableArea::IsActive() const { return true; }
bool PaintLayerScrollableArea::IsThrottled() const { return false; }
int PaintLayerScrollableArea::ScrollSize(ScrollbarOrientation) const {
  return 0;
}
bool PaintLayerScrollableArea::IsScrollCornerVisible() const { return false; }
gfx::Rect PaintLayerScrollableArea::ScrollCornerRect() const {
  return gfx::Rect();
}
bool PaintLayerScrollableArea::HasTickmarks() const { return false; }
Vector<gfx::Rect> PaintLayerScrollableArea::GetTickmarks() const {
  return Vector<gfx::Rect>();
}
void PaintLayerScrollableArea::SetScrollCornerNeedsPaintInvalidation() {}
gfx::Point PaintLayerScrollableArea::ConvertFromScrollbarToContainingEmbeddedContentView(
    const Scrollbar&,
    const gfx::Point& point) const {
  return point;
}
gfx::Rect PaintLayerScrollableArea::ConvertFromScrollbarToContainingEmbeddedContentView(
    const Scrollbar&,
    const gfx::Rect& rect) const {
  return rect;
}
gfx::Point PaintLayerScrollableArea::ConvertFromContainingEmbeddedContentViewToScrollbar(
    const Scrollbar&,
    const gfx::Point& point) const {
  return point;
}
gfx::Point PaintLayerScrollableArea::ConvertFromRootFrame(
    const gfx::Point& point) const {
  return point;
}
gfx::Vector2d PaintLayerScrollableArea::MinimumScrollOffsetInt() const {
  return gfx::Vector2d();
}
gfx::Vector2d PaintLayerScrollableArea::MaximumScrollOffsetInt() const {
  return gfx::Vector2d();
}
PhysicalRect PaintLayerScrollableArea::VisibleScrollSnapportRect(
    IncludeScrollbarsInRect) const {
  return PhysicalRect();
}
gfx::Point PaintLayerScrollableArea::LastKnownMousePosition() const {
  return gfx::Point();
}
bool PaintLayerScrollableArea::ShouldSuspendScrollAnimations() const {
  return true;
}
bool PaintLayerScrollableArea::ScrollbarsCanBeActive() const { return false; }
bool PaintLayerScrollableArea::ScrollAnimatorEnabled() const { return false; }
bool PaintLayerScrollableArea::ScheduleAnimation() { return false; }
void PaintLayerScrollableArea::RegisterForAnimation() {}
void PaintLayerScrollableArea::DeregisterForAnimation() {}
bool PaintLayerScrollableArea::UsesCompositedScrolling() const { return false; }
bool PaintLayerScrollableArea::ShouldScrollOnMainThread() const { return true; }
bool PaintLayerScrollableArea::UserInputScrollable(ScrollbarOrientation) const {
  return false;
}
bool PaintLayerScrollableArea::ShouldPlaceVerticalScrollbarOnLeft() const {
  return false;
}
void PaintLayerScrollableArea::DisposeImpl() {}
void PaintLayerScrollableArea::ScrollControlWasSetNeedsPaintInvalidation() {}
mojom::blink::ScrollBehavior PaintLayerScrollableArea::ScrollBehaviorStyle()
    const {
  return mojom::blink::ScrollBehavior::kAuto;
}
mojom::blink::ColorScheme PaintLayerScrollableArea::UsedColorSchemeScrollbars()
    const {
  return mojom::blink::ColorScheme::kLight;
}
gfx::QuadF PaintLayerScrollableArea::LocalToVisibleContentQuad(
    const gfx::QuadF& quad,
    const LayoutObject*,
    unsigned) const {
  return quad;
}
bool PaintLayerScrollableArea::IsRootFrameLayoutViewport() const {
  return false;
}
bool PaintLayerScrollableArea::VisualViewportSuppliesScrollbars() const {
  return false;
}
bool PaintLayerScrollableArea::RestoreScrollAnchor(const SerializedAnchor&) {
  return false;
}
void PaintLayerScrollableArea::DidScrollWithScrollbar(
    ScrollbarPart,
    ScrollbarOrientation,
    WebInputEvent::Type) {}
scoped_refptr<base::SingleThreadTaskRunner>
PaintLayerScrollableArea::GetTimerTaskRunner() const {
  return nullptr;
}
void PaintLayerScrollableArea::DidCompositorScroll(const gfx::PointF&,
                                                   cc::ScrollSourceType) {}
void PaintLayerScrollableArea::ScrollbarFrameRectChanged() {}
ScrollbarTheme& PaintLayerScrollableArea::GetPageScrollbarTheme() const {
  return *static_cast<ScrollbarTheme*>(nullptr);
}
bool PaintLayerScrollableArea::IsApplyingScrollStart() const { return false; }
void PaintLayerScrollableArea::SetScrollsnapchangeTargetIds(
    std::optional<cc::TargetSnapAreaElementIds>) {}
void PaintLayerScrollableArea::UpdateSnappedTargetsAndEnqueueScrollSnapChange() {}
std::optional<cc::TargetSnapAreaElementIds>
PaintLayerScrollableArea::GetScrollsnapchangingTargetIds() const {
  return std::nullopt;
}
void PaintLayerScrollableArea::SetScrollsnapchangingTargetIds(
    std::optional<cc::TargetSnapAreaElementIds>) {}
void PaintLayerScrollableArea::UpdateScrollSnapChangingTargetsAndEnqueueScrollSnapChanging(
    const cc::TargetSnapAreaElementIds&) {}
const cc::SnapSelectionStrategy* PaintLayerScrollableArea::GetImplSnapStrategy()
    const {
  return nullptr;
}
void PaintLayerScrollableArea::SetImplSnapStrategy(
    std::unique_ptr<cc::SnapSelectionStrategy>) {}
void PaintLayerScrollableArea::EnqueueScrollSnapChangingEventFromImplIfNeeded() {}
void PaintLayerScrollableArea::DropCompositorScrollDeltaNextCommit() {}
void PaintLayerScrollableArea::SetSnappedQueryTargetIds(
    std::optional<cc::TargetSnapAreaElementIds>) {}
bool PaintLayerScrollableArea::IsGlobalRootNonOverlayScroller() const {
  return false;
}
ScrollMarkerGroupPseudoElement* PaintLayerScrollableArea::GetScrollMarkerGroup()
    const {
  return nullptr;
}
void PaintLayerScrollableArea::UpdateScrollMarkers() {}
void PaintLayerScrollableArea::DidUpdateVisualViewport() {}
void PaintLayerScrollableArea::ScrollbarVisibilityChanged() {}
void PaintLayerScrollableArea::StopApplyingScrollStart() {}
Node* PaintLayerScrollableArea::GetSnapEventTargetAlongAxis(
    const AtomicString&,
    cc::SnapAxis) const {
  return nullptr;
}
bool PaintLayerScrollableArea::ShouldAvoidHidingOverlayScrollbars() const {
  return true;
}
void PaintLayerScrollableArea::UpdateScrollOffset(const ScrollOffset&,
                                                  mojom::blink::ScrollType,
                                                  cc::ScrollSourceType) {}
String PaintLayerScrollableArea::ScrollingBackgroundDisplayItemClient::DebugName()
    const {
  return String();
}
DOMNodeId PaintLayerScrollableArea::ScrollingBackgroundDisplayItemClient::OwnerNodeId(
    bool) const {
  return 0;
}
String PaintLayerScrollableArea::ScrollCornerDisplayItemClient::DebugName()
    const {
  return String();
}
DOMNodeId PaintLayerScrollableArea::ScrollCornerDisplayItemClient::OwnerNodeId(
    bool) const {
  return 0;
}
void PaintLayerFragment::Trace(Visitor* visitor) const {
  visitor->Trace(fragment_data);
  visitor->Trace(physical_fragment);
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool PaintPropertyTreeBuilder::ScheduleDeferredTransformNodeUpdate(
    LayoutObject&) {
  return false;
}
bool PaintPropertyTreeBuilder::ScheduleDeferredOpacityNodeUpdate(
    LayoutObject&) {
  return false;
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool CullRectUpdater::IsOverridingCullRects() {
  return false;
}
#endif
String ExternalRepresentation(LocalFrame*, unsigned, const PaintLayer*) {
  return String();
}
const scoped_refptr<cc::ViewTransitionContentLayer>&
ViewTransition::GetScopeSnapshotLayer() const {
  static const scoped_refptr<cc::ViewTransitionContentLayer>* layer =
      new scoped_refptr<cc::ViewTransitionContentLayer>();
  return *layer;
}
MobileFriendlinessChecker* MobileFriendlinessChecker::From(const Document&) {
  return nullptr;
}
void MobileFriendlinessChecker::NotifyPaintReplaced(
    const PhysicalRect&,
    const TransformPaintPropertyNodeOrAlias&) {}
void RasterInvalidationTracking::CheckUnderInvalidations(
    const String&,
    PaintRecord,
    const gfx::Rect&) {}
void PaintTiming::NotifyPaint(bool, bool, bool) {}
bool PaintTimingDetector::NotifyBackgroundImagePaint(
    const Node&,
    const Image&,
    const StyleImage&,
    const PropertyTreeStateOrAlias&,
    const gfx::Rect&) {
  return false;
}
void ImageElementTiming::NotifyBackgroundImagePainted(
    Node&,
    const StyleImage&,
    const PropertyTreeStateOrAlias&,
    const gfx::Rect&) {}
namespace inspector_paint_image_event {
void Data(perfetto::TracedValue,
          Node*,
          const StyleImage&,
          const gfx::RectF&,
          const gfx::RectF&) {}
}  // namespace inspector_paint_image_event
std::unique_ptr<JSONArray> RecordAsJSON(const PaintRecord&) {
  return std::make_unique<JSONArray>();
}
String RecordAsDebugString(const PaintRecord&) {
  return String();
}
String CompositingReason::ToString(CompositingReasons) {
  return String();
}
FilterEffectBuilder::FilterEffectBuilder(const gfx::RectF& reference_box,
                                         std::optional<gfx::SizeF> viewport,
                                         float zoom,
                                         Color current_color,
                                         mojom::blink::ColorScheme color_scheme,
                                         const cc::PaintFlags* fill_flags,
                                         const cc::PaintFlags* stroke_flags)
    : reference_box_(reference_box),
      viewport_(viewport),
      zoom_(zoom),
      shorthand_scale_(1),
      current_color_(current_color),
      color_scheme_(color_scheme),
      fill_flags_(fill_flags),
      stroke_flags_(stroke_flags) {}
Filter* FilterEffectBuilder::BuildReferenceFilter(
    const ReferenceFilterOperation&,
    FilterEffect*,
    SVGFilterGraphNodeMap*) const {
  return nullptr;
}
FilterEffect* FilterEffectBuilder::BuildFilterEffect(
    const FilterOperations&,
    bool) const {
  return nullptr;
}
CompositorFilterOperations FilterEffectBuilder::BuildFilterOperations(
    const FilterOperations&) const {
  return CompositorFilterOperations();
}
gfx::RectF FEGaussianBlur::MapEffect(const gfx::SizeF&,
                                     const gfx::RectF& rect) {
  return rect;
}
gfx::RectF FEDropShadow::MapEffect(const gfx::SizeF&,
                                   const gfx::Vector2dF&,
                                   const gfx::RectF& rect) {
  return rect;
}
Filter::Filter(float scale)
    : reference_box_(), filter_region_(), scale_(scale),
      unit_scaling_(kUserSpace), source_graphic_(nullptr),
      last_effect_(nullptr) {}
gfx::RectF Filter::MapLocalRectToAbsoluteRect(const gfx::RectF& rect) const {
  return rect;
}
float Filter::ApplyHorizontalScale(float value) const {
  return value * scale_;
}
float Filter::ApplyVerticalScale(float value) const {
  return value * scale_;
}
gfx::RectF FilterEffect::MapRect(const gfx::RectF& rect) const {
  return rect;
}
DrawLooperBuilder::DrawLooperBuilder() = default;
DrawLooperBuilder::~DrawLooperBuilder() = default;
void DrawLooperBuilder::AddShadow(const gfx::Vector2dF&,
                                  float,
                                  const Color&,
                                  ShadowTransformMode,
                                  ShadowAlphaMode) {}
void DrawLooperBuilder::AddUnmodifiedContent() {}
sk_sp<cc::DrawLooper> DrawLooperBuilder::DetachDrawLooper() {
  return nullptr;
}
bool StyleImage::IsCorsSameOrigin() const {
  return true;
}
RespectImageOrientationEnum StyleImage::ForceOrientationIfNecessary(
    RespectImageOrientationEnum orientation) const {
  return orientation;
}
scoped_refptr<Image> Image::LoadPlatformResource(int,
                                                 ui::ResourceScaleFactor) {
  return nullptr;
}
const TransformPaintPropertyNode*
VisualViewport::TransformNodeForViewportScrollbars() const {
  return nullptr;
}
void CustomScrollbarTheme::PaintIntoRect(const LayoutCustomScrollbarPart&,
                                         const PaintInfo&,
                                         const PhysicalRect&) {}
void CustomScrollbar::Paint(const PaintInfo&, const PhysicalOffset&) const {}
ScrollbarLayerDelegate::ScrollbarLayerDelegate(blink::Scrollbar& scrollbar)
    : scrollbar_(&scrollbar) {}
ScrollbarLayerDelegate::~ScrollbarLayerDelegate() = default;
bool ScrollbarLayerDelegate::IsSame(const cc::Scrollbar&) const {
  return false;
}
cc::ScrollbarOrientation ScrollbarLayerDelegate::Orientation() const {
  return cc::ScrollbarOrientation::kVertical;
}
bool ScrollbarLayerDelegate::IsLeftSideVerticalScrollbar() const {
  return false;
}
bool ScrollbarLayerDelegate::HasThumb() const {
  return false;
}
bool ScrollbarLayerDelegate::IsSolidColor() const {
  return false;
}
bool ScrollbarLayerDelegate::IsOverlay() const {
  return false;
}
bool ScrollbarLayerDelegate::IsRunningWebTest() const {
  return false;
}
bool ScrollbarLayerDelegate::IsFluentOverlayScrollbarMinimalMode() const {
  return false;
}
bool ScrollbarLayerDelegate::SupportsDragSnapBack() const {
  return false;
}
bool ScrollbarLayerDelegate::JumpOnTrackClick() const {
  return false;
}
bool ScrollbarLayerDelegate::IsOpaque() const {
  return false;
}
int ScrollbarLayerDelegate::MinimumThumbLength() const {
  return 0;
}
gfx::Rect ScrollbarLayerDelegate::ThumbRect() const {
  return gfx::Rect();
}
gfx::Rect ScrollbarLayerDelegate::TrackRect() const {
  return gfx::Rect();
}
gfx::Rect ScrollbarLayerDelegate::BackButtonRect() const {
  return gfx::Rect();
}
gfx::Rect ScrollbarLayerDelegate::ForwardButtonRect() const {
  return gfx::Rect();
}
float ScrollbarLayerDelegate::Opacity() const {
  return 0.0f;
}
bool ScrollbarLayerDelegate::ThumbNeedsRepaint() const {
  return false;
}
void ScrollbarLayerDelegate::ClearThumbNeedsRepaint() {}
bool ScrollbarLayerDelegate::TrackAndButtonsNeedRepaint() const {
  return false;
}
bool ScrollbarLayerDelegate::NeedsUpdateDisplay() const {
  return false;
}
void ScrollbarLayerDelegate::ClearNeedsUpdateDisplay() {}
bool ScrollbarLayerDelegate::HasTickmarks() const {
  return false;
}
void ScrollbarLayerDelegate::PaintThumb(cc::PaintCanvas&,
                                        const gfx::Rect&) {}
void ScrollbarLayerDelegate::PaintTrackAndButtons(cc::PaintCanvas&,
                                                  const gfx::Rect&) {}
SkColor4f ScrollbarLayerDelegate::ThumbColor() const {
  return SkColor4f{0.0f, 0.0f, 0.0f, 0.0f};
}
bool ScrollbarLayerDelegate::UsesNinePatchThumbResource() const {
  return false;
}
gfx::Size ScrollbarLayerDelegate::NinePatchThumbCanvasSize() const {
  return gfx::Size();
}
gfx::Rect ScrollbarLayerDelegate::NinePatchThumbAperture() const {
  return gfx::Rect();
}
bool ScrollbarLayerDelegate::UsesSolidColorThumb() const {
  return false;
}
gfx::Insets ScrollbarLayerDelegate::SolidColorThumbInsets() const {
  return gfx::Insets();
}
bool ScrollbarLayerDelegate::UsesNinePatchTrackAndButtonsResource() const {
  return false;
}
gfx::Size ScrollbarLayerDelegate::NinePatchTrackAndButtonsCanvasSize(
    float) const {
  return gfx::Size();
}
gfx::Rect ScrollbarLayerDelegate::NinePatchTrackAndButtonsAperture(
    float) const {
  return gfx::Rect();
}
gfx::Rect ScrollbarLayerDelegate::ShrinkMainThreadedMinimalModeThumbRect(
    gfx::Rect& rect) const {
  return rect;
}
bool ScrollbarLayerDelegate::ShouldPaint() const {
  return false;
}
CompositorElementId Scrollbar::GetElementId() const {
  return CompositorElementId();
}
RoundedInnerRectClipper::RoundedInnerRectClipper(GraphicsContext& context,
                                                 const PhysicalRect&,
                                                 const ContouredRect&)
    : context_(context) {}
RoundedInnerRectClipper::~RoundedInnerRectClipper() = default;
ImageAutoDarkMode ImageClassifierHelper::GetImageAutoDarkMode(
    LocalFrame&,
    const ComputedStyle&,
    const gfx::RectF&,
    const gfx::RectF&,
    DarkModeFilter::ElementRole) {
  return ImageAutoDarkMode::Disabled();
}
NinePieceImageGrid::NinePieceImageGrid(const NinePieceImage&,
                                       const gfx::SizeF& image_size,
                                       const gfx::Vector2dF&,
                                       float zoom,
                                       const gfx::Rect& border_image_area,
                                       const gfx::Outsets&,
                                       PhysicalBoxSides)
    : border_image_area_(border_image_area),
      image_size_(image_size),
      horizontal_tile_rule_(kStretchImageRule),
      vertical_tile_rule_(kStretchImageRule),
      zoom_(zoom),
      fill_(false),
      top_{0, 0},
      right_{0, 0},
      bottom_{0, 0},
      left_{0, 0} {}
NinePieceImageGrid::NinePieceDrawInfo NinePieceImageGrid::GetNinePieceDrawInfo(
    NinePiece) const {
  NinePieceDrawInfo info;
  info.is_drawable = false;
  info.is_corner_piece = false;
  return info;
}
SkBlendMode ToSkBlendMode(CompositeOperator, BlendMode) {
  return SkBlendMode::kSrcOver;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
gfx::Rect LayoutTextCombine::VisualRectForPaint(
    const PhysicalOffset&) const {
  return gfx::Rect();
}
AffineTransform LayoutTextCombine::ComputeAffineTransformForPaint(
    const PhysicalOffset&) const {
  return AffineTransform();
}
PhysicalRect LayoutTextCombine::ComputeTextBoundsRectForHitTest(
    const FragmentItem&,
    const PhysicalOffset&) const {
  return PhysicalRect();
}
LayoutUnit LayoutTextCombine::AdjustTextLeftForPaint(LayoutUnit text_left) const {
  return text_left;
}
LayoutUnit LayoutTextCombine::AdjustTextTopForPaint(LayoutUnit text_top) const {
  return text_top;
}
void LayoutTextCombine::AssertStyleIsValid(const ComputedStyle&) {}
#endif
bool TextCombinePainter::ShouldPaint(const LayoutTextCombine&) {
  return false;
}
void TextCombinePainter::Paint(const PaintInfo&,
                               const PhysicalOffset&,
                               const LayoutTextCombine&) {}
CaretShape FrameSelection::GetCaretShape() const {
  return CaretShape::kBar;
}
void FrameSelection::PaintCaret(GraphicsContext&,
                                const PhysicalOffset&) {}
bool FrameSelection::ShouldPaintCaret(const PhysicalBoxFragment&) const {
  return false;
}
void DragCaret::PaintDragCaret(const LocalFrame*,
                               GraphicsContext&,
                               const PhysicalOffset&) const {}
bool DragCaret::ShouldPaintCaret(const PhysicalBoxFragment&) const {
  return false;
}
void MathMLPainter::Paint(const PaintInfo&, PhysicalOffset) {}
void HitTestResult::SetNodeAndPosition(Node* node,
                                       const PhysicalBoxFragment*,
                                       const PhysicalOffset& point) {
  SetNodeAndPosition(node, point);
}
PointerEventsHitRules::PointerEventsHitRules(EHitTesting,
                                             const HitTestRequest&,
                                             EPointerEvents)
    : require_visible(false),
      require_fill(false),
      require_stroke(false),
      can_hit_stroke(false),
      can_hit_bounding_box(false) {}
ListBasedHitTestBehavior HitTestResult::AddNodeToListBasedTestResult(
    Node*,
    const HitTestLocation&,
    const gfx::QuadF&) {
  return kStopHitTesting;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
LogicalOffset ComputeRelativeOffset(const ComputedStyle&,
                                    WritingDirectionMode,
                                    const LogicalSize&) {
  return LogicalOffset();
}
#endif
PhysicalOffset LogicalOffset::ConvertToPhysical(WritingDirectionMode,
                                                PhysicalSize,
                                                PhysicalSize) const {
  return PhysicalOffset(inline_offset, block_offset);
}
FieldsetPaintInfo::FieldsetPaintInfo(const ComputedStyle&,
                                     const PhysicalSize&,
                                     const PhysicalBoxStrut&,
                                     const PhysicalRect&)
    : border_outsets(), legend_cutout_rect() {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool GapGeometry::IsMultiColSpanner(wtf_size_t,
                                    GridTrackSizingDirection) const {
  return false;
}
LayoutUnit GapGeometry::GetGapCenterOffset(GridTrackSizingDirection,
                                           wtf_size_t) const {
  return LayoutUnit();
}
void GapGeometry::GenerateIntersectionListForGap(
    GridTrackSizingDirection,
    wtf_size_t,
    Vector<GapIntersection>& intersections) const {
  intersections.Shrink(0);
}
bool GapGeometry::IsCapIntersection(GridTrackSizingDirection,
                                    wtf_size_t,
                                    wtf_size_t,
                                    bool,
                                    RuleVisibilityItems,
                                    RuleVisibilityItems,
                                    const Vector<GapIntersection>&) const {
  return true;
}
LayoutUnit GapGeometry::GetMaxInsetWidth(
    GridTrackSizingDirection,
    wtf_size_t,
    wtf_size_t,
    bool,
    const Vector<GapIntersection>&) const {
  return LayoutUnit();
}
LayoutUnit GapGeometry::GetCrossDecorationWidthForIntersection(
    wtf_size_t,
    wtf_size_t,
    bool,
    const Vector<GapIntersection>&,
    bool,
    const Vector<int>&) const {
  return LayoutUnit();
}
LayoutUnit GapGeometry::ComputeInsetStart(const ComputedStyle&,
                                          wtf_size_t,
                                          wtf_size_t,
                                          const Vector<GapIntersection>&,
                                          bool,
                                          bool,
                                          bool,
                                          bool,
                                          LayoutUnit,
                                          LayoutUnit) const {
  return LayoutUnit();
}
LayoutUnit GapGeometry::ComputeInsetEnd(const ComputedStyle&,
                                        wtf_size_t,
                                        wtf_size_t,
                                        const Vector<GapIntersection>&,
                                        bool,
                                        bool,
                                        bool,
                                        bool,
                                        LayoutUnit,
                                        LayoutUnit) const {
  return LayoutUnit();
}
LayoutUnit GapGeometry::GetCrossWidthForIntersection(
    GridTrackSizingDirection,
    wtf_size_t,
    wtf_size_t,
    bool,
    const Vector<GapIntersection>&) const {
  return LayoutUnit();
}
LayoutUnit GapGeometry::GetCrossingGapSize(GridTrackSizingDirection) const {
  return LayoutUnit();
}
PhysicalRect GapGeometry::ComputeInkOverflowForGaps(
    WritingDirectionMode,
    const PhysicalSize&,
    LayoutUnit,
    LayoutUnit,
    const GapDecorationInkOutsets&) const {
  return PhysicalRect();
}
#endif
void MobileFriendlinessChecker::NotifyPaintTextFragment(
    const PhysicalRect&,
    int,
    const TransformPaintPropertyNodeOrAlias&) {}
const PhysicalBoxFragment& GetPageBorderBox(const PhysicalBoxFragment& box) {
  return box;
}
PhysicalRect StitchedPageContentRect(const LayoutView&, unsigned) {
  return PhysicalRect();
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void InlineCursor::MoveToNextFragmentainer() {}
InlineCursor::InlineCursor(const InlineBackwardCursor&) {}
InlineCursor::InlineCursor(const PhysicalBoxFragment&, const FragmentItems&) {}
void InlineCursor::ExpandRootToContainingBlock() {}
bool InlineCursorPosition::HasChildren() const {
  return false;
}
const DisplayItemClient*
InlineCursorPosition::GetSelectionDisplayItemClient() const {
  return nullptr;
}
InlineBackwardCursor::InlineBackwardCursor(const InlineCursor& cursor)
    : cursor_(cursor), current_index_(0) {}
void InlineBackwardCursor::MoveToPreviousSibling() {}
InlineCursor InlineBackwardCursor::CursorForDescendants() const {
  return InlineCursor();
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool FragmentItem::HasSelfPaintingLayer() const {
  return false;
}
bool FragmentItem::IsBlockInInline() const {
  return false;
}
#endif
LayoutTable* LayoutTableCell::Table() const {
  return nullptr;
}
unsigned LayoutTableCell::ColSpan() const {
  return 1;
}
unsigned LayoutTableCell::ParseRowSpanFromDOM() const {
  return 1;
}
bool LayoutTableSection::IsEmpty() const {
  return true;
}
Color TableBorders::BorderColor(const ComputedStyle*, EdgeSide) {
  return Color();
}
const AtomicString& LayoutCounter::ListStyle(const LayoutObject*,
                                             const ComputedStyle&) {
  return g_null_atom;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect ListMarker::RelativeSymbolMarkerRect(const ComputedStyle&,
                                                  const AtomicString&,
                                                  LayoutUnit) {
  return PhysicalRect();
}
#endif
bool LayoutCounter::IsDirectionalSymbolMarker() const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool FragmentItem::IsFloating() const {
  return false;
}
bool FragmentItem::IsInlineBox() const {
  return false;
}
const ShapeResultView* FragmentItem::TextShapeResult() const {
  return nullptr;
}
TextFragmentPaintInfo FragmentItem::TextPaintInfo(
    const FragmentItems&) const {
  return TextFragmentPaintInfo{StringView(), 0, 0, nullptr, 1.0f};
}
float FragmentItem::GetFitTextScale() const {
  return 1.0f;
}
FontHeight FragmentItem::AnnotationMetrics() const {
  return FontHeight();
}
const Font& FragmentItem::ScaledFont() const {
  return *Style().GetFont();
}
bool FragmentItem::HasSvgTransformForPaint() const {
  return false;
}
AffineTransform FragmentItem::BuildSvgTransformForPaint() const {
  return AffineTransform();
}
gfx::QuadF FragmentItem::SvgUnscaledQuad() const {
  return gfx::QuadF();
}
PhysicalRect FragmentItem::ComputeTextBoundsRectForHitTest(
    const PhysicalOffset&,
    bool) const {
  return PhysicalRect();
}
std::ostream& operator<<(std::ostream& ostream, const FragmentItem&) {
  return ostream << "FragmentItem";
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const TransformPaintPropertyNodeOrAlias& FragmentData::PreTransform() const {
  return TransformPaintPropertyNode::Root();
}
const ClipPaintPropertyNodeOrAlias& FragmentData::PreClip() const {
  return ClipPaintPropertyNode::Root();
}
const EffectPaintPropertyNodeOrAlias& FragmentData::PreEffect() const {
  return EffectPaintPropertyNode::Root();
}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect ComputeReferenceBox(const LayoutBox&) {
  return PhysicalRect();
}
#endif
bool LayoutSVGRoot::HasNonIsolatedBlendingDescendants() const {
  return false;
}
double LayoutSVGRoot::LogicalSizeScaleFactorForPercentageLengths() const {
  return 1.0;
}
gfx::SizeF LayoutSVGRoot::ViewportSize() const {
  return gfx::SizeF();
}
gfx::RectF LayoutSVGRoot::ViewBoxRect() const {
  return gfx::RectF();
}
gfx::RectF LayoutSVGViewportContainer::ViewBoxRect() const {
  return gfx::RectF();
}
void LayoutSVGRoot::LayoutRoot(const PhysicalRect&) {}
void ScrollMarkerGroupPseudoElement::ClearFocusGroup() {}
bool HTMLMarqueeElement::IsHorizontal() const {
  return true;
}
LayoutBlock* LayoutFieldset::FindAnonymousFieldsetContentBox() const {
  return nullptr;
}
bool MathMLRadicalElement::HasIndex() const {
  return false;
}
FitTextMethod FitText::Method() const {
  return FitTextMethod::kScale;
}
LayoutWorkletGlobalScopeProxy* LayoutWorklet::Proxy() {
  return nullptr;
}
CSSLayoutDefinition* LayoutWorkletGlobalScopeProxy::FindDefinition(
    const AtomicString&) {
  return nullptr;
}
CustomLayoutChild::CustomLayoutChild(const CSSLayoutDefinition&,
                                     LayoutInputNode node)
    : node_(node), style_map_(nullptr), token_(nullptr) {}
void CustomLayoutChild::Trace(Visitor* visitor) const {
  visitor->Trace(style_map_);
  ScriptWrappable::Trace(visitor);
}
void InputMethodController::DidLayoutSubtree(const LayoutObject&) {}
void InputMethodController::DidUpdateLayout(const LayoutObject&) {}
void InputMethodController::LayoutObjectWillBeDestroyed(const LayoutObject&) {}
void DragCaret::LayoutBlockWillBeDestroyed(const LayoutBlock&) {}
void FirstLetterPseudoElement::ClearRemainingTextLayoutObject() {}
void FirstLetterPseudoElement::UpdateTextFragments() {}
void FirstLetterPseudoElement::Trace(Visitor* visitor) const {
  PseudoElement::Trace(visitor);
}
bool DocumentMarkerController::HasAnyMarkersForText(const Text&) const {
  return false;
}
DocumentMarkerVector DocumentMarkerController::MarkersFor(
    const Text&,
    DocumentMarker::MarkerType,
    unsigned,
    unsigned) const {
  return DocumentMarkerVector();
}
TextOffsetRange HighlightPainter::GetFragmentDOMOffsets(const Text&,
                                                        unsigned from,
                                                        unsigned to) {
  return TextOffsetRange(from, to);
}
PseudoId HighlightPainter::PseudoFor(DocumentMarker::MarkerType) {
  return kPseudoIdNone;
}
TextDecorationLine HighlightPainter::LineFor(DocumentMarker::MarkerType) {
  return TextDecorationLine::kNone;
}
Color HighlightPainter::ColorFor(DocumentMarker::MarkerType) {
  return Color::kTransparent;
}
const ComputedStyle* HighlightStyleUtils::HighlightPseudoStyle(
    const ComputedStyle&,
    PseudoId,
    const AtomicString&) {
  return nullptr;
}
std::optional<TextOffsetRange> MarkerRangeMappingContext::GetTextContentOffsets(
    const DocumentMarker&) const {
  return std::nullopt;
}
MarkerRangeMappingContext::DOMToTextContentOffsetMapper::
    DOMToTextContentOffsetMapper(const LayoutObject&) {}
CaretShape GetCaretShapeFromComputedStyle(const ComputedStyle&) {
  return CaretShape::kBar;
}
LogicalRect GetCaretRectAtTextOffset(const InlineCursor&,
                                     unsigned,
                                     CaretShape) {
  return LogicalRect();
}
InlineCaretPosition BidiAdjustment::AdjustForHitTest(
    const InlineCaretPosition& position) {
  return position;
}
InlineCaretPosition BidiAdjustment::AdjustForInlineCaretPositionResolution(
    const InlineCaretPosition& position) {
  return position;
}
SvgTextLayoutAlgorithm::SvgTextLayoutAlgorithm(InlineNode node,
                                               WritingMode writing_mode)
    : inline_node_(node),
      addressable_count_(0),
      horizontal_(IsHorizontalWritingMode(writing_mode)),
      inline_direction_(
          WritingDirectionMode(writing_mode, TextDirection::kLtr).InlineEnd()) {}
PhysicalSize SvgTextLayoutAlgorithm::Layout(
    const String&,
    FragmentItemsBuilder::ItemWithOffsetList&) {
  return PhysicalSize();
}
bool LayoutProgress::IsDeterminate() const {
  return false;
}
double LayoutProgress::AnimationProgress() const {
  return 0.0;
}
const double HTMLProgressElement::kInvalidPosition = -1;
const double HTMLProgressElement::kIndeterminatePosition = -1;
double HTMLProgressElement::position() const {
  return kIndeterminatePosition;
}
bool HTMLInputElement::IsTextButton() const {
  return false;
}
double HTMLInputElement::Minimum() const {
  return 0.0;
}
double HTMLInputElement::Maximum() const {
  return 1.0;
}
bool HTMLInputElement::IsValidValue(const String&) const {
  return true;
}
String HTMLInputElement::SanitizeValue(const String& value) const {
  return value;
}
bool HTMLInputElement::ShouldAppearChecked() const {
  return false;
}
bool HTMLInputElement::IsPickerVisible() const {
  return false;
}
bool HTMLInputElement::ShouldApplyMiddleEllipsis() const {
  return false;
}
Decimal HTMLInputElement::RatioValue() const {
  return Decimal(0);
}
HTMLInputElement* SliderThumbElement::HostInput() const {
  return nullptr;
}
bool ViewTransition::IsRepresentedViaPseudoElements(
    const LayoutObject&) const {
  return false;
}
bool ViewTransition::MatchForOnlyChild(PseudoId, const AtomicString&) const {
  return false;
}
bool ViewTransition::MatchForActiveViewTransition() {
  return false;
}
bool ViewTransition::MatchForActiveViewTransitionType(
    const Vector<AtomicString>&) {
  return false;
}

MutationObserver::MutationObserver(ExecutionContext* context,
                                   Delegate* delegate)
    : ActiveScriptWrappable<MutationObserver>(
          ActiveScriptWrappableCreationKey()),
      ExecutionContextLifecycleStateObserver(context),
      delegate_(delegate) {}
MutationObserver::~MutationObserver() = default;
MutationObserver* MutationObserver::Create(Delegate* delegate) {
  return MakeGarbageCollected<MutationObserver>(nullptr, delegate);
}
MutationObserver* MutationObserver::Create(ScriptState*, V8MutationCallback*) {
  return MakeGarbageCollected<MutationObserver>(nullptr, nullptr);
}
void MutationObserver::observe(Node*, const MutationObserverInit*,
                               ExceptionState&) {}
MutationRecordVector MutationObserver::takeRecords() {
  return MutationRecordVector();
}
void MutationObserver::disconnect() {}
void MutationObserver::ObservationStarted(MutationObserverRegistration*) {}
void MutationObserver::ObservationEnded(MutationObserverRegistration*) {}
void MutationObserver::EnqueueMutationRecord(MutationRecord*) {}
void MutationObserver::SetHasTransientRegistration() {}
HeapHashSet<Member<Node>> MutationObserver::GetObservedNodes() const {
  return HeapHashSet<Member<Node>>();
}
void MutationObserver::ContextLifecycleStateChanged(
    mojom::FrameLifecycleState) {}
void MutationObserver::ContextDestroyed() {}
void MutationObserver::Trace(Visitor* visitor) const {
  ScriptWrappable::Trace(visitor);
  ExecutionContextLifecycleStateObserver::Trace(visitor);
  visitor->Trace(delegate_);
}
void MutationObserver::DeliverMutations() {}
void MutationObserver::EnqueueSlotChange(HTMLSlotElement&) {}
void MutationObserver::CleanSlotChangeList(Document&) {}

MutationObserverRegistration::MutationObserverRegistration(
    MutationObserver& observer,
    Node* node,
    MutationObserverOptions options,
    const HashSet<AtomicString>& attribute_filter)
    : observer_(&observer),
      registration_node_(node),
      registration_node_keep_alive_(node),
      options_(options),
      attribute_filter_(attribute_filter) {}
MutationObserverRegistration::~MutationObserverRegistration() = default;
void MutationObserverRegistration::Dispose() {}
void MutationObserverRegistration::ObservedSubtreeNodeWillDetach(Node&) {}
void MutationObserverRegistration::Unregister() {}
bool MutationObserverRegistration::ShouldReceiveMutationFrom(
    Node&,
    MutationType,
    const QualifiedName*) const {
  return false;
}
void MutationObserverRegistration::ResetObservation(
    MutationObserverOptions options,
    const HashSet<AtomicString>& attribute_filter) {
  options_ = options;
  attribute_filter_ = attribute_filter;
}
void MutationObserverRegistration::Trace(Visitor* visitor) const {
  visitor->Trace(observer_);
  visitor->Trace(registration_node_);
  visitor->Trace(registration_node_keep_alive_);
  visitor->Trace(transient_registration_nodes_);
}
MutationObserverInterestGroup* MutationObserverInterestGroup::CreateIfNeeded(
    Node&,
    MutationType,
    MutationRecordDeliveryOptions,
    const QualifiedName*) {
  return nullptr;
}
void MutationObserverInterestGroup::EnqueueMutationRecord(MutationRecord*) {}

MutationObserverInit::MutationObserverInit() = default;
void MutationObserverInit::Trace(Visitor*) const {}
void MutationObserverInit::setAttributeFilter(Vector<String>&&) {}

HTMLFormControlElement::HTMLFormControlElement(const QualifiedName& tag_name,
                                               Document& document)
    : HTMLElement(tag_name, document), ListedElement(), autofill_state_(),
      blocks_form_submission_(false) {}
HTMLFormControlElement::~HTMLFormControlElement() = default;
void HTMLFormControlElement::Trace(Visitor* visitor) const {
  HTMLElement::Trace(visitor);
  ListedElement::Trace(visitor);
}
void HTMLFormControlElement::AttachLayoutTree(AttachContext& context) {
  HTMLElement::AttachLayoutTree(context);
}
void HTMLFormControlElement::DetachLayoutTree(bool performing_reattach) {
  HTMLElement::DetachLayoutTree(performing_reattach);
}
Node::InsertionNotificationRequest HTMLFormControlElement::InsertedInto(
    ContainerNode& insertion_point) {
  HTMLElement::InsertedInto(insertion_point);
  ListedElement::InsertedInto(insertion_point);
  return kInsertionDone;
}
void HTMLFormControlElement::RemovedFrom(ContainerNode& insertion_point) {
  HTMLElement::RemovedFrom(insertion_point);
  ListedElement::RemovedFrom(insertion_point);
}
void HTMLFormControlElement::DidMoveToNewDocument(Document& old_document) {
  ListedElement::DidMoveToNewDocument(old_document);
  HTMLElement::DidMoveToNewDocument(old_document);
}
void HTMLFormControlElement::AttributeChanged(
    const AttributeModificationParams&) {}
void HTMLFormControlElement::ParseAttribute(
    const AttributeModificationParams&) {}
void HTMLFormControlElement::CloneNonAttributePropertiesFrom(
    const Element&,
    NodeCloningData&) {}
HTMLElement* HTMLFormControlElement::formForBinding() const {
  return nullptr;
}
HTMLFormElement* HTMLFormControlElement::formOwner() const {
  return nullptr;
}
void HTMLFormControlElement::AssociateWith(HTMLFormElement*) {}
bool HTMLFormControlElement::IsDisabledFormControl() const {
  return false;
}
bool HTMLFormControlElement::MatchesEnabledPseudoClass() const {
  return true;
}
bool HTMLFormControlElement::IsRequired() const {
  return false;
}
bool HTMLFormControlElement::IsSuccessfulSubmitButton() const {
  return false;
}
String HTMLFormControlElement::ResultForDialogSubmit() {
  return String();
}
HTMLFormControlElement::PopoverTargetElement
HTMLFormControlElement::popoverTargetElement() {
  return PopoverTargetElement();
}
void HTMLFormControlElement::DefaultEventHandler(Event&) {}
bool HTMLFormControlElement::willValidate() const {
  return false;
}
bool HTMLFormControlElement::IsReadOnly() const {
  return false;
}
bool HTMLFormControlElement::IsDisabledOrReadOnly() const {
  return false;
}
bool HTMLFormControlElement::MayTriggerVirtualKeyboard() const {
  return false;
}
bool HTMLFormControlElement::ShouldHaveFocusAppearance() const {
  return false;
}
bool HTMLFormControlElement::IsKeyboardFocusableSlow(
    UpdateBehavior) const {
  return false;
}
FocusableState HTMLFormControlElement::SupportsFocus(
    UpdateBehavior) const {
  return FocusableState::kNotFocusable;
}
bool HTMLFormControlElement::MatchesValidityPseudoClasses() const {
  return false;
}
bool HTMLFormControlElement::MatchesToolSubmitActivePseudoClass() const {
  return false;
}
const AtomicString& HTMLFormControlElement::autocapitalize() const {
  return g_empty_atom;
}
void HTMLFormControlElement::RequiredAttributeChanged() {}
void HTMLFormControlElement::DisabledAttributeChanged() {}
void HTMLFormControlElement::WillChangeForm() {}
void HTMLFormControlElement::DidChangeForm() {}
void HTMLFormControlElement::SetAutofillState(WebAutofillState) {}
bool HTMLFormControlElement::IsValidElement() {
  return true;
}

HTMLFormControlElementWithState::HTMLFormControlElementWithState(
    const QualifiedName& tag_name,
    Document& document)
    : HTMLFormControlElement(tag_name, document),
      interacted_state_(InteractedState::kNotInteracted),
      force_user_valid_(false) {}
HTMLFormControlElementWithState::~HTMLFormControlElementWithState() = default;
bool HTMLFormControlElementWithState::ShouldAutocomplete() const {
  return false;
}
String HTMLFormControlElementWithState::IDLExposedAutofillValue() const {
  return String();
}
void HTMLFormControlElementWithState::setIDLExposedAutofillValue(
    const String&) {}
bool HTMLFormControlElementWithState::ClassSupportsStateRestore() const {
  return false;
}
bool HTMLFormControlElementWithState::ShouldSaveAndRestoreFormControlState()
    const {
  return false;
}
void HTMLFormControlElementWithState::SetUserHasEditedTheField() {}
void HTMLFormControlElementWithState::SetUserHasEditedTheFieldAndBlurred() {}
void HTMLFormControlElementWithState::ForceUserValid() {}
bool HTMLFormControlElementWithState::MatchesUserInvalidPseudo() {
  return false;
}
bool HTMLFormControlElementWithState::MatchesUserValidPseudo() {
  return false;
}
void HTMLFormControlElementWithState::DispatchInputEvent() {}
void HTMLFormControlElementWithState::DispatchChangeEvent() {}
void HTMLFormControlElementWithState::DispatchCancelEvent() {}
bool HTMLFormControlElementWithState::IsFormControlElementWithState() const {
  return true;
}
void HTMLFormControlElementWithState::FinishParsingChildren() {
  HTMLFormControlElement::FinishParsingChildren();
}
void HTMLFormControlElementWithState::ResetImpl() {}
int HTMLFormControlElementWithState::DefaultTabIndex() const {
  return 0;
}

ListedElement::ListedElement()
    : has_validation_message_(false),
      form_was_set_by_parser_(false),
      will_validate_initialized_(false),
      will_validate_(true),
      is_valid_(true),
      validity_is_dirty_(false),
      is_element_disabled_(false),
      is_readonly_(false) {}
ListedElement::~ListedElement() = default;
void ListedElement::Trace(Visitor* visitor) const {
  visitor->Trace(form_);
}
ListedElement* ListedElement::From(Element&) {
  return nullptr;
}
const HTMLElement& ListedElement::ToHTMLElement() const {
  return *static_cast<const HTMLElement*>(nullptr);
}
HTMLElement& ListedElement::ToHTMLElement() {
  return *static_cast<HTMLElement*>(nullptr);
}
HTMLElement* ListedElement::RetargetedForm() const {
  return nullptr;
}
bool ListedElement::IsFormControlElement() const { return false; }
bool ListedElement::IsFormControlElementWithState() const { return false; }
bool ListedElement::IsElementInternals() const { return false; }
bool ListedElement::IsObjectElement() const { return false; }
const AtomicString& ListedElement::GetName() const { return g_empty_atom; }
void ListedElement::ResetFormOwner() {}
void ListedElement::FormRemovedFromTree(const Node&) {}
bool ListedElement::WillValidate() const { return false; }
bool ListedElement::CustomError() const { return false; }
ValidityState* ListedElement::validity() { return nullptr; }
bool ListedElement::HasBadInput() const { return false; }
bool ListedElement::PatternMismatch() const { return false; }
bool ListedElement::RangeOverflow() const { return false; }
bool ListedElement::RangeUnderflow() const { return false; }
bool ListedElement::StepMismatch() const { return false; }
bool ListedElement::TooLong() const { return false; }
bool ListedElement::TooShort() const { return false; }
bool ListedElement::TypeMismatch() const { return false; }
bool ListedElement::ValueMissing() const { return false; }
bool ListedElement::Valid() const { return true; }
String ListedElement::validationMessage() const { return String(); }
String ListedElement::ValidationSubMessage() const { return String(); }
String ListedElement::CustomValidationMessage() const { return String(); }
void ListedElement::setCustomValidity(const String&) {}
void ListedElement::UpdateVisibleValidationMessage() {}
void ListedElement::HideVisibleValidationMessage() {}
bool ListedElement::checkValidity(List*) { return true; }
bool ListedElement::reportValidity() { return true; }
void ListedElement::ShowValidationMessage() {}
bool ListedElement::IsValidationMessageVisible() const { return false; }
void ListedElement::FindCustomValidationMessageTextDirection(
    const String&, TextDirection&, String&, TextDirection&) {}
Element& ListedElement::ValidationAnchor() const {
  return *static_cast<Element*>(nullptr);
}
Element& ListedElement::GetHostOrFocusDelegate() const {
  return *static_cast<Element*>(nullptr);
}
bool ListedElement::ValidationAnchorOrHostIsFocusable() const { return false; }
bool ListedElement::IsValidElement() { return true; }
bool ListedElement::IsNotCandidateOrValid() { return true; }
void ListedElement::SetNeedsValidityCheck() {}
void ListedElement::DisabledAttributeChanged() {}
void ListedElement::ReadonlyAttributeChanged() {}
void ListedElement::FormAttributeChanged() {}
void ListedElement::FormAttributeTargetChanged() {}
void ListedElement::InsertedInto(ContainerNode&) {}
void ListedElement::RemovedFrom(ContainerNode&) {}
void ListedElement::DidMoveToNewDocument(Document&) {}
void ListedElement::AncestorDisabledStateWasChanged() {}
bool ListedElement::IsActuallyDisabled() const { return false; }
bool ListedElement::ClassSupportsStateRestore() const { return false; }
bool ListedElement::ShouldSaveAndRestoreFormControlState() const {
  return false;
}
FormControlState ListedElement::SaveFormControlState() const {
  return FormControlState();
}
void ListedElement::RestoreFormControlState(const FormControlState&) {}
void ListedElement::NotifyFormStateChanged() {}
void ListedElement::TakeStateAndRestore() {}
HTMLFormElement* ListedElement::GetOwningFormForAutofill() const {
  return nullptr;
}
void ListedElement::SetForm(HTMLFormElement*) {}
void ListedElement::AssociateByParser(HTMLFormElement*) {}
void ListedElement::WillChangeForm() {}
void ListedElement::DidChangeForm() {}
bool ListedElement::RecalcWillValidate() const { return false; }

HTMLDataListElement::HTMLDataListElement(Document& document)
    : HTMLElement(html_names::kDatalistTag, document) {}
HTMLDataListOptionsCollection* HTMLDataListElement::options() {
  return nullptr;
}
void HTMLDataListElement::OptionElementChildrenChanged() {}
PopoverHideResult HTMLDataListElement::HidePopoverInternal(
    Element*,
    HidePopoverFocusBehavior,
    HidePopoverTransitionBehavior,
    ExceptionState*) {
  return PopoverHideResult::kHidden;
}
void HTMLDataListElement::MoveActiveOption(Direction) {}
HTMLInputElement* HTMLDataListElement::ComboboxInput() {
  return nullptr;
}
void HTMLDataListElement::Trace(Visitor* visitor) const {
  HTMLElement::Trace(visitor);
  visitor->Trace(active_option_);
}
bool HTMLDataListElement::SupportsBaseAppearanceInternal(
    BaseAppearanceValue) const {
  return false;
}
void HTMLDataListElement::ChildrenChanged(const ChildrenChange&) {}
void HTMLDataListElement::FinishParsingChildren() {}
void HTMLDataListElement::DidMoveToNewDocument(Document&) {}
void HTMLDataListElement::Prefinalize() {}

bool HTMLFormElement::NoValidate() const {
  return false;
}
bool HTMLFormElement::MatchesToolFormActivePseudoClass() const {
  return false;
}
void FormData::AppendFromElement(const String&, const String&) {}
String Locale::ConvertToLocalizedNumber(const String& value) {
  return value;
}
String Locale::QueryString(int, const String&) {
  return String();
}
void V8UnionHTMLOptGroupElementOrHTMLOptionElement::Trace(
    Visitor*) const {}
void V8UnionHTMLElementOrLong::Trace(Visitor*) const {}
void AuditsIssue::ReportElementAccessibilityIssue(
    Document*,
    int,
    ElementAccessibilityIssueReason,
    bool) {}
int KeyboardEvent::keyCode() const {
  return 0;
}
InputDeviceCapabilitiesConstants* DOMWindow::GetInputDeviceCapabilities() {
  return nullptr;
}
InputDeviceCapabilities* InputDeviceCapabilitiesConstants::FiresTouchEvents(
    bool) {
  return nullptr;
}
void HTMLFormElement::SubmitImplicitly(const Event&, bool) {}
void AutoscrollController::StartAutoscrollForSelection(LayoutObject*) {}
void EventHandler::SetMouseDownMayStartAutoscroll() {}
bool AutoscrollController::AutoscrollInProgressFor(const LayoutBox*) const {
  return false;
}
void AutoscrollController::StopAutoscroll() {}

void HitTestResult::Append(const HitTestResult&) {}
bool ClipPathClipper::HitTest(const LayoutObject&, const HitTestLocation&) {
  return false;
}
void SVGMaskPainter::Paint(GraphicsContext&,
                           const LayoutObject&,
                           const DisplayItemClient&) {}
void SVGMaskPainter::PaintSVGMaskLayer(GraphicsContext&,
                                       const StyleMaskSourceImage&,
                                       const ImageResourceObserver&,
                                       const gfx::RectF&,
                                       float,
                                       SkBlendMode,
                                       bool) {}
void SVGResources::UpdatePaints(const LayoutObject&,
                                const ComputedStyle*,
                                const ComputedStyle&) {}
void SVGResources::ClearPaints(const LayoutObject&, const ComputedStyle*) {}
bool SVGObjectPainter::HasFill(const ComputedStyle&,
                               const SvgContextPaints*) {
  return false;
}
bool SVGObjectPainter::HasVisibleStroke(const ComputedStyle&,
                                        const SvgContextPaints*) {
  return false;
}
bool SVGObjectPainter::PreparePaint(PaintFlags,
                                    const ComputedStyle&,
                                    LayoutSVGResourceMode,
                                    cc::PaintFlags&,
                                    const AffineTransform*) {
  return false;
}
void SVGLayoutSupport::ApplyStrokeStyleToStrokeData(StrokeData&,
                                                    const ComputedStyle&,
                                                    const LayoutObject&,
                                                    float) {}
extern const int32_t kSerializedCharacterDataSize = 0;
alignas(4) extern const uint8_t kSerializedCharacterData[] = {};
#if !defined(HTML_CSS_RENDERER_STANDALONE)
CharacterBreakIterator::CharacterBreakIterator(const StringView&)
    : is_8bit_(true), charaters8_(nullptr), offset_(0), length_(0) {}
CharacterBreakIterator::CharacterBreakIterator(base::span<const UChar>)
    : is_8bit_(true), charaters8_(nullptr), offset_(0), length_(0) {}
int CharacterBreakIterator::Next() {
  return kTextBreakDone;
}
int CharacterBreakIterator::Current() {
  return offset_;
}
bool CharacterBreakIterator::IsBreak(int offset) const {
  return offset == 0 || offset == static_cast<int>(length_);
}
int CharacterBreakIterator::Preceding(int) const {
  return kTextBreakDone;
}
int CharacterBreakIterator::Following(int) const {
  return kTextBreakDone;
}
void CharacterBreakIterator::ReturnToPool::operator()(void*) const {}
void ReturnBreakIteratorToPool::operator()(void*) const {}
std::unique_ptr<icu::BreakIterator, ReturnBreakIteratorToPool>
AcquireLineBreakIterator(StringView, const AtomicString&) {
  return nullptr;
}
#endif
SkTypeface* FontPlatformData::Typeface() const {
  return typeface_.get();
}
FontPlatformData::FontPlatformData(sk_sp<SkTypeface> typeface,
                                   const std::string&,
                                   float text_size,
                                   bool synthetic_bold,
                                   bool synthetic_italic,
                                   TextRenderingMode text_rendering,
                                   ResolvedFontFeatures resolved_font_features,
                                   FontOrientation orientation)
    : typeface_(std::move(typeface)),
      text_size_(text_size),
      synthetic_bold_(synthetic_bold),
      synthetic_italic_(synthetic_italic),
      text_rendering_(text_rendering),
      orientation_(orientation),
      resolved_font_features_(std::move(resolved_font_features)) {}

FontPlatformData::FontPlatformData(const FontPlatformData& src,
                                   float text_size)
    : FontPlatformData(src.typeface_,
                       std::string(),
                       text_size,
                       src.synthetic_bold_,
                       src.synthetic_italic_,
                       src.text_rendering_,
                       src.resolved_font_features_,
                       src.orientation_) {}

FontPlatformData::~FontPlatformData() = default;

SkFont FontPlatformData::CreateSkFont(const FontDescription*) const {
  SkFont font(typeface_, text_size_ > 0 ? text_size_ : 12.0f);
  font.setEmbolden(synthetic_bold_);
  font.setSkewX(synthetic_italic_ ? -0.25f : 0.0f);
  return font;
}
void FontPlatformData::Trace(Visitor*) const {}
String FontPlatformData::GetPostScriptName() const {
  return String();
}
SkTypefaceID FontPlatformData::UniqueID() const {
  return typeface_ ? typeface_->uniqueID() : 0;
}
unsigned FontPlatformData::GetHash() const {
  return UniqueID();
}
bool FontPlatformData::operator==(const FontPlatformData& other) const {
  return UniqueID() == other.UniqueID() && text_size_ == other.text_size_ &&
         synthetic_bold_ == other.synthetic_bold_ &&
         synthetic_italic_ == other.synthetic_italic_ &&
         orientation_ == other.orientation_;
}
bool FontPlatformData::FontContainsCharacter(UChar32 character) const {
  return typeface_ && typeface_->unicharToGlyph(character) != 0;
}
FontCache& FontCache::Get() {
  alignas(FontCache) static unsigned char storage[sizeof(FontCache)] = {};
  return *reinterpret_cast<FontCache*>(storage);
}
const SimpleFontData* FontCache::FallbackFontForCharacter(
    const FontDescription& font_description,
    UChar32,
    const SimpleFontData* primary_font,
    FontFallbackPriority) {
  return primary_font ? primary_font
                      : FontCache::Get().GetLastResortFallbackFont(
                            font_description);
}
const SimpleFontData* FontCache::GetLastResortFallbackFont(
    const FontDescription& font_description) {
  return nullptr;
}
void FontCache::CrashWithFontInfo(const FontDescription*) {}
const FontData* FontFallbackList::FontDataAt(
    const FontDescription& font_description,
    unsigned index) {
  if (index != 0) {
    return nullptr;
  }
  return DeterminePrimarySimpleFontData(font_description, uchar::kSpace);
}
VariationSelectorMode GetVariationSelectorModeFromFontVariantEmoji(
    FontVariantEmoji) {
  return kUseSpecifiedVariationSelector;
}
bool ShouldIgnoreVariationSelector(VariationSelectorMode) {
  return false;
}
bool UseFontVariantEmojiVariationSelector(VariationSelectorMode) {
  return false;
}
bool Character::IsVariationSequence(UChar32, UChar32) {
  return false;
}
bool Character::IsEmoji(UChar32) {
  return false;
}
bool Character::IsEmojiTextDefault(UChar32) {
  return false;
}
bool Character::IsEmojiEmojiDefault(UChar32) {
  return false;
}
FontGlobalContext& FontGlobalContext::Get() {
  DEFINE_STATIC_LOCAL(Persistent<FontGlobalContext>, context, ());
  if (!context) {
    context = MakeGarbageCollected<FontGlobalContext>(
        FontGlobalContext::PassKey());
  }
  return *context;
}
FontGlobalContext::FontGlobalContext(PassKey)
    : memory_pressure_listener_registration_(
          FROM_HERE,
          base::MemoryPressureListenerTag::kFontGlobalContext,
          this) {}
FontGlobalContext::~FontGlobalContext() = default;
FontGlobalContext* FontGlobalContext::TryGet() {
  return &Get();
}
FontUniqueNameLookup* FontGlobalContext::GetFontUniqueNameLookup() {
  return nullptr;
}
void FontGlobalContext::Init() {
  HarfBuzzFace::Init();
}
void FontGlobalContext::OnMemoryPressure(base::MemoryPressureLevel) {}
FontCache::FontCache() = default;
FontCache::~FontCache() = default;
void FontCache::Trace(Visitor*) const {}
FontPlatformDataCache::FontPlatformDataCache() : font_size_limit_(10000.0f) {}

void DeleteStandaloneTypefaceStream(void* stream_asset_ptr) {
  delete reinterpret_cast<SkStreamAsset*>(stream_asset_ptr);
}

void DeleteStandaloneTypefaceBuffer(void* buffer) {
  delete[] reinterpret_cast<char*>(buffer);
}

hb_blob_t* StandaloneHarfBuzzSkiaGetTable(hb_face_t*,
                                          hb_tag_t tag,
                                          void* user_data) {
  SkTypeface* typeface = reinterpret_cast<SkTypeface*>(user_data);
  if (!typeface) {
    return nullptr;
  }
  const size_t table_size = typeface->getTableSize(tag);
  if (table_size == 0 ||
      table_size > static_cast<size_t>(std::numeric_limits<unsigned int>::max())) {
    return nullptr;
  }
  char* buffer = new char[table_size];
  const size_t actual_size = typeface->getTableData(tag, 0, table_size, buffer);
  if (actual_size != table_size) {
    delete[] buffer;
    return nullptr;
  }
  return hb_blob_create(buffer, static_cast<unsigned int>(table_size),
                        HB_MEMORY_MODE_READONLY, buffer,
                        DeleteStandaloneTypefaceBuffer);
}

hb::unique_ptr<hb_face_t> HbFaceFromSkTypeface(sk_sp<SkTypeface> typeface) {
  if (!typeface) {
    return hb::unique_ptr<hb_face_t>();
  }
  hb::unique_ptr<hb_face_t> face(hb_face_create_for_tables(
      StandaloneHarfBuzzSkiaGetTable, typeface.get(), nullptr));
  hb_face_set_index(face.get(), 0);
  return face;
}
OpenTypeFeatures::OpenTypeFeatures(const SimpleFontData&) {}
bool OpenTypeCapsSupport::SupportsOpenTypeFeature(hb_script_t, uint32_t) const {
  return false;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void FontFeatureRangesSaver::CheckIsAdditionsOnly() const {}
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
unsigned JustificationContext::CountOpportunities(TextJustify,
                                                  base::span<const LChar>,
                                                  TextDirection) {
  return 0;
}
unsigned JustificationContext::CountOpportunities(TextJustify,
                                                  base::span<const UChar>,
                                                  TextDirection) {
  return 0;
}
std::pair<bool, bool> JustificationContext::CheckOpportunity16(TextJustify,
                                                               UChar32) {
  return {false, false};
}
std::pair<bool, bool> JustificationContext::CheckOpportunity8(TextJustify,
                                                              LChar) {
  return {false, false};
}
#endif
void ClipPathClipper::PaintClipPathAsMaskImage(GraphicsContext&,
                                               const LayoutObject&,
                                               const DisplayItemClient&) {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PhysicalFragment::Trace(Visitor*) const {}
#endif
DarkModeImageClassifier::DarkModeImageClassifier() = default;
DarkModeResult DarkModeImageClassifier::Classify(const SkPixmap&,
                                                 const SkIRect&) const {
  return DarkModeResult::kDoNotApplyFilter;
}
#if !defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
DarkModeImageCache* Image::GetDarkModeImageCache() {
  return nullptr;
}
SkBitmap Image::AsSkBitmapForCurrentFrame(RespectImageOrientationEnum) {
  return SkBitmap();
}
#endif
bool RuntimeEnabledFeaturesBase::is_scrollbar_gutter_bug_fix_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_remove_scroll_node_workaround_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_geometry_mapper_singular_transform_fix_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_merge_fixed_layers_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_merge_sticky_layers_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_paint_under_invalidation_checking_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_svg_filter_paints_for_hidden_content_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_hit_test_container_transform_state_for_preserve_3d_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_hit_test_border_radius_for_stacking_context_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_svg_filter_user_space_viewport_for_svg_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_backface_visibility_interop_enabled_ = false;
bool RuntimeEnabledFeaturesBase::is_view_transition_hoist_backdrop_filter_effect_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_handle_invalid_mask_image_with_backdrop_filter_enabled_ =
    false;
bool RuntimeEnabledFeaturesBase::is_paint_offset_translation_for_composited_enabled_ =
    false;

PaintPropertyChangeType VisualViewport::UpdatePaintPropertyNodesIfNeeded(
    PaintPropertyTreeBuilderFragmentContext&) {
  return PaintPropertyChangeType::kUnchanged;
}
const ScrollPaintPropertyNode* VisualViewport::GetScrollNode() const {
  return nullptr;
}
namespace paint_property_tree_printer {
void UpdateDebugNames(const VisualViewport&) {}
void UpdateDebugNames(const LayoutObject&, ObjectPaintProperties&) {}
}  // namespace paint_property_tree_printer
CompositingReasons CompositingReasonFinder::DirectReasonsForPaintProperties(
    const LayoutObject&,
    const LayoutObject*) {
  return CompositingReason::kNone;
}
bool CompositingReasonFinder::ShouldForcePreferCompositingToLCDText(
    const LayoutObject&,
    CompositingReasons) {
  return false;
}
bool PaintLayerScrollableArea::PrefersNonCompositedScrolling() const {
  return true;
}
void PaintLayerScrollableArea::PositionOverflowControls() {}
gfx::Rect PaintLayerScrollableArea::ScrollCornerAndResizerRect() const {
  return gfx::Rect();
}
gfx::Size PaintLayerScrollableArea::PixelSnappedBorderBoxSize() const {
  return gfx::Size();
}
bool PaintLayerScrollableArea::HasHorizontalOverflow() const {
  return false;
}
bool PaintLayerScrollableArea::HasVerticalOverflow() const {
  return false;
}
gfx::Size PaintLayerScrollableArea::PixelSnappedContentsSize(
    const PhysicalOffset&) const {
  return gfx::Size();
}
bool PaintLayerScrollableArea::BackgroundNeedsRepaintOnScroll() const {
  return false;
}
cc::ElementId PaintLayerScrollableArea::GetScrollCornerElementId() const {
  return cc::ElementId();
}
void ClipPathClipper::FallbackClipPathAnimationIfNecessary(const LayoutObject&,
                                                           bool) {}
bool ClipPathClipper::ClipPathStatusResolved(const LayoutObject&) {
  return true;
}
std::optional<gfx::RectF> ClipPathClipper::LocalClipPathBoundingBox(
    const LayoutObject&) {
  return std::nullopt;
}
bool ClipPathClipper::HasCompositeClipPathAnimation(
    const LayoutObject&,
    CompositedStateResolutionType) {
  return false;
}
void ClipPathClipper::FallbackClipPathAnimationDueToAbsentBounds(
    const LayoutObject&) {}
std::optional<Path> ClipPathClipper::PathBasedClip(const LayoutObject&,
                                                   const gfx::Vector2dF&) {
  return std::nullopt;
}
LayoutView* LayoutEmbeddedContent::ChildLayoutView() const {
  return nullptr;
}
EmbeddedContentView* LayoutEmbeddedContent::GetEmbeddedContentView() const {
  return nullptr;
}
AffineTransform LayoutEmbeddedContent::EmbeddedContentTransform() const {
  return AffineTransform();
}
const LayoutBoxModelObject*
StickyPositionScrollingConstraints::NearestStickyLayerShiftingStickyBox()
    const {
  return nullptr;
}
const LayoutBoxModelObject* StickyPositionScrollingConstraints::
    NearestStickyLayerShiftingContainingBlock() const {
  return nullptr;
}
PhysicalOffset AnchorPositionScrollData::SpeculativeDefaultAnchorRememberedOffset()
    const {
  return PhysicalOffset();
}
viz::ViewTransitionElementResourceId ViewTransition::GetSnapshotId(
    const LayoutObject&) const {
  return viz::ViewTransitionElementResourceId();
}
bool ViewTransition::NeedsViewTransitionClipNode(const LayoutObject&) const {
  return false;
}
PaintPropertyChangeType ViewTransition::UpdateCaptureClip(
    const LayoutObject&,
    const ClipPaintPropertyNodeOrAlias*,
    const TransformPaintPropertyNodeOrAlias*) {
  return PaintPropertyChangeType::kUnchanged;
}
const ClipPaintPropertyNode* ViewTransition::GetCaptureClip(
    const LayoutObject&) const {
  return nullptr;
}
bool CompositorAnimations::CanStartTransformAnimationOnCompositorForSVG(
    const SVGElement&) {
  return false;
}
AffineTransform TransformHelper::ComputeTransform(
    UseCounter&,
    const ComputedStyle&,
    const gfx::RectF&,
    ComputedStyle::ApplyTransformOrigin) {
  return AffineTransform();
}
gfx::PointF TransformHelper::ComputeTransformOrigin(const ComputedStyle&,
                                                    const gfx::RectF&) {
  return gfx::PointF();
}
std::optional<gfx::RectF> CSSMaskPainter::MaskBoundingBox(
    const LayoutObject&,
    const PhysicalOffset&) {
  return std::nullopt;
}
SkBlendMode ToSkBlendMode(BlendMode) {
  return SkBlendMode::kSrcOver;
}
SVGElementResourceClient* SVGResources::GetClient(const LayoutObject&) {
  return nullptr;
}
void SVGElementResourceClient::UpdateFilterData(CompositorFilterOperations&) {}
bool LinkHighlight::IsHighlightingInternal(const LayoutObject&) const {
  return false;
}
AffineTransform LayoutSVGViewportContainer::ComputeViewboxTransform() const {
  return AffineTransform();
}
AffineTransform SVGRootPainter::TransformToPixelSnappedBorderBox(
    const PhysicalOffset&) const {
  return AffineTransform();
}
bool PaintArtifactCompositor::DirectlyUpdateScrollOffsetTransform(
    const TransformPaintPropertyNode&) {
  return false;
}
bool PaintArtifactCompositor::UsesRasterInducingScroll(
    const ScrollPaintPropertyNode&) const {
  return false;
}
bool PaintArtifactCompositor::DirectlyUpdateTransform(
    const TransformPaintPropertyNode&) {
  return false;
}
bool PaintArtifactCompositor::DirectlyUpdateCompositedOpacityValue(
    const EffectPaintPropertyNode&) {
  return false;
}
float TargetScaleForPage(const PhysicalBoxFragment&) {
  return 1.0f;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void CullRectUpdater::PaintPropertiesChanged(
    const LayoutObject&,
    const PaintPropertiesChangeInfo&) {}
#endif
bool SVGLayoutSupport::IsIsolationRequired(const LayoutObject*) {
  return false;
}
bool SVGLayoutSupport::IsOverflowHidden(const LayoutObject&) {
  return false;
}
bool LayoutReplaced::ClipsToContentBox() const {
  return false;
}
bool LayoutShiftTracker::NeedsToTrack(const LayoutObject&) const {
  return false;
}
void LayoutShiftTracker::NotifyTextPrePaint(
    const LayoutText&,
    const PropertyTreeStateOrAlias&,
    const LogicalOffset&,
    const LogicalOffset&,
    const PhysicalOffset&,
    const gfx::Vector2dF&,
    const gfx::Vector2dF&,
    const gfx::Vector2dF&,
    const PhysicalOffset&,
    LayoutUnit) {}
void LayoutShiftTracker::NotifyBoxPrePaint(
    const LayoutBox&,
    const PropertyTreeStateOrAlias&,
    const PhysicalRect&,
    const PhysicalRect&,
    const PhysicalOffset&,
    const gfx::Vector2dF&,
    const gfx::Vector2dF&,
    const gfx::Vector2dF&,
    const PhysicalOffset&) {}
LayoutShiftTracker::ContainingBlockScope*
    LayoutShiftTracker::ContainingBlockScope::top_ = nullptr;
void LayoutShiftTracker::NotifyPrePaintFinished() {}
void ShowAllPropertyTrees(const LocalFrameView&) {}
void FrameSelection::EnsureInvalidationOfPreviousLayoutBlock() {}
SoftNavigationPaintAttributionTracker::PrePaintUpdateResult
SoftNavigationPaintAttributionTracker::UpdateOnPrePaint(const LayoutObject&,
                                                        Node*,
                                                        Node*) {
  return PrePaintUpdateResult::kPropagateCurrentNode;
}
PhysicalRect StitchedPageContentRect(const PhysicalBoxFragment&) {
  return PhysicalRect();
}
const PhysicalBoxFragment* GetPageContainer(const LayoutView&, wtf_size_t) {
  return nullptr;
}
namespace features {
BASE_FEATURE(kExpandCompositedCullRect, base::FEATURE_DISABLED_BY_DEFAULT);
const base::FeatureParam<int> kCullRectPixelDistanceToExpand{
    &kExpandCompositedCullRect, "pixels", 4000};
const base::FeatureParam<bool> kSmallScrollersUseMinCullRect{
    &kExpandCompositedCullRect, "small_scroller_opt", false};
const base::FeatureParam<int> kCullRectChangedEnoughDistance{
    &kExpandCompositedCullRect, "changed_enough", 512};
}  // namespace features

}  // namespace blink

void ShowAllPropertyTrees(const blink::LocalFrameView&) {}

namespace color_utils {
float GetContrastRatio(SkColor, SkColor) {
  return 1.0f;
}
float GetContrastRatio(SkColor4f, SkColor4f) {
  return 1.0f;
}
float GetRelativeLuminance4f(SkColor4f) {
  return 0.0f;
}
SkColor GetResultingPaintColor(SkColor foreground, SkColor) {
  return foreground;
}
BlendResult BlendForMinContrast(SkColor foreground,
                                SkColor,
                                std::optional<SkColor>,
                                float) {
  return {SK_AlphaOPAQUE, foreground};
}
}  // namespace color_utils

namespace base {
RefCountedMemory::RefCountedMemory() = default;
RefCountedMemory::~RefCountedMemory() = default;
HistogramBase* BooleanHistogram::FactoryGet(const char*, int32_t) {
  return nullptr;
}
HistogramBase* Histogram::FactoryMicrosecondsTimeGet(const char*,
                                                     TimeDelta,
                                                     TimeDelta,
                                                     uint64_t,
                                                     int32_t) {
  return nullptr;
}
void HistogramBase::AddBoolean(bool) {}
bool UncheckedMalloc(size_t size, void** result) {
  *result = std::malloc(size ? size : 1);
  return *result != nullptr;
}
bool UncheckedCalloc(size_t num_items, size_t size, void** result) {
  *result = std::calloc(num_items ? num_items : 1, size ? size : 1);
  return *result != nullptr;
}
void UncheckedFree(void* ptr) {
  std::free(ptr);
}
DiscardableMemoryAllocator* DiscardableMemoryAllocator::GetInstance() {
  return nullptr;
}
std::unique_ptr<DiscardableMemory>
DiscardableMemoryAllocator::AllocateLockedDiscardableMemoryWithRetryOrDie(
    size_t,
    OnceClosure) {
  return nullptr;
}
std::string CommandLine::GetSwitchValueASCII(std::string_view) const {
  return std::string();
}
std::string Base64Encode(span<const uint8_t>) {
  return std::string();
}
std::string Base64Encode(std::string_view) {
  return std::string();
}
void StringAppendV(std::string* dst, const char* format, va_list ap) {
  if (!dst || !format)
    return;
  char buffer[2048];
  int written = vsnprintf(buffer, sizeof(buffer), format, ap);
  if (written > 0)
    dst->append(buffer, static_cast<size_t>(
                            std::min<int>(written, sizeof(buffer) - 1)));
}
}  // namespace base

namespace base::trace_event {
TracedValue::~TracedValue() = default;
void TracedValue::AppendAsTraceFormat(std::string*) const {}
bool TracedValue::AppendToProto(ProtoAppender*) const {
  return false;
}
}  // namespace base::trace_event

namespace logging {
int GetMinLogLevel() {
  return 0;
}
}  // namespace logging

extern "C" MojoResult MojoDestroyMessage(MojoMessageHandle) {
  return MOJO_RESULT_OK;
}
extern "C" MojoResult MojoAppendMessageData(
    MojoMessageHandle,
    uint32_t payload_size,
    const MojoHandle*,
    uint32_t,
    const MojoAppendMessageDataOptions*,
    void** buffer,
    uint32_t* buffer_size) {
  static std::vector<uint8_t>* storage = new std::vector<uint8_t>();
  storage->assign(payload_size, 0);
  if (buffer)
    *buffer = storage->data();
  if (buffer_size)
    *buffer_size = payload_size;
  return MOJO_RESULT_OK;
}

namespace viz {
RegionCaptureBounds::RegionCaptureBounds() = default;
RegionCaptureBounds::RegionCaptureBounds(RegionCaptureBounds&&) = default;
RegionCaptureBounds::~RegionCaptureBounds() = default;
void RegionCaptureBounds::Set(const RegionCaptureCropId& crop_id,
                              const gfx::Rect& bounds) {
  bounds_[crop_id] = bounds;
}
}  // namespace viz

namespace cc {
void Layer::SetBounds(const gfx::Size&) {}
void Layer::SetIsDrawable(bool) {}
void Layer::SetTouchActionRegion(TouchActionRegion) {}
void Layer::SetWheelEventRegion(Region) {}
void Layer::SetCaptureBounds(viz::RegionCaptureBounds) {}
void Layer::SetTrackedElementRects(viz::TrackedElementRects) {}
void Layer::SetMainThreadScrollHitTestRegion(const Region&) {}
void Layer::SetNonCompositedScrollHitTestRects(
    std::vector<ScrollHitTestRect>) {}
void Layer::SetContentsOpaque(bool) {}
void Layer::SetHitTestOpaqueness(HitTestOpaqueness) {}
void Layer::SetElementId(ElementId) {}
void Layer::SetOffsetToTransformParent(gfx::Vector2dF) {}
void ScrollTree::ClearScrollingContentsCullRect(ElementId) {}
void ScrollTree::SetScrollingContentsCullRect(ElementId, const gfx::Rect&) {}
LayerSelectionBound::LayerSelectionBound()
    : type(gfx::SelectionBound::Type::EMPTY),
      edge_start(),
      edge_end(),
      layer_id(0),
      hidden(false) {}
LayerSelectionBound::~LayerSelectionBound() = default;
scoped_refptr<ScrollbarLayerBase> ScrollbarLayerBase::CreateOrReuse(
    scoped_refptr<Scrollbar>,
    ScrollbarLayerBase*) {
  return nullptr;
}
void ScrollbarLayerBase::SetScrollElementId(ElementId) {}
AnchorPositionScrollData::AnchorPositionScrollData() = default;
AnchorPositionScrollData::~AnchorPositionScrollData() = default;
AnchorPositionScrollData::AnchorPositionScrollData(
    const AnchorPositionScrollData&) = default;
bool AnchorPositionScrollData::operator==(
    const AnchorPositionScrollData&) const {
  return true;
}
}  // namespace cc

namespace SkOpts {
void Init_ml3() {}
void Init_ml4() {}
}  // namespace SkOpts

namespace skgpu::graphite {
int Recorder::maxTextureSize() const {
  return 0;
}
}  // namespace skgpu::graphite

namespace SkImages {
sk_sp<SkImage> TextureFromImage(skgpu::graphite::Recorder*,
                                const SkImage*,
                                SkImage::RequiredProperties) {
  return nullptr;
}
sk_sp<SkImage> TextureFromYUVAImages(skgpu::graphite::Recorder*,
                                     const SkYUVAInfo&,
                                     SkSpan<const sk_sp<SkImage>>,
                                     sk_sp<SkColorSpace>) {
  return nullptr;
}
}  // namespace SkImages

namespace crashpad {
void Annotation::SetSize(ValueSizeType size) {
  size_ = size;
}
void Annotation::Clear() {
  size_ = 0;
}
}  // namespace crashpad

namespace gfx::mojom {
bool HDRMetadata::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}
}  // namespace gfx::mojom

namespace mojo {
bool StructTraits<gfx::mojom::HDRMetadataDataView, gfx::HDRMetadata>::Read(
    gfx::mojom::HDRMetadataDataView,
    gfx::HDRMetadata*) {
  return false;
}
}  // namespace mojo

namespace skia::mojom::internal {
SkColorSpacePrimaries_Data::SkColorSpacePrimaries_Data() = default;
}  // namespace skia::mojom::internal

namespace cppgc::internal {
GCInfoIndex EnsureGCInfoIndexTrait::EnsureGCInfoIndex(
    std::atomic<GCInfoIndex>& registered_index,
    TraceCallback,
    FinalizationCallback,
    NameCallback) {
  registered_index = 1;
  return 1;
}
GCInfoIndex EnsureGCInfoIndexTrait::EnsureGCInfoIndex(
    std::atomic<GCInfoIndex>& registered_index,
    TraceCallback) {
  registered_index = 1;
  return 1;
}
GCInfoIndex EnsureGCInfoIndexTrait::EnsureGCInfoIndex(
    std::atomic<GCInfoIndex>& registered_index,
    TraceCallback,
    FinalizationCallback) {
  registered_index = 1;
  return 1;
}
void DCheckImpl(const char*, SourceLocation) {}
}  // namespace cppgc::internal

namespace cppgc {
bool LivenessBroker::IsHeapObjectAliveImpl(const void*) const {
  return true;
}
}  // namespace cppgc

namespace cppgc::subtle {
void NoGarbageCollectionScope::Enter(HeapHandle&) {}
void NoGarbageCollectionScope::Leave(HeapHandle&) {}
bool HeapState::IsInAtomicPause(const HeapHandle&) {
  return false;
}
bool HeapState::IsMarking(const HeapHandle&) {
  return false;
}
bool DisallowGarbageCollectionScope::IsGarbageCollectionAllowed(
    HeapHandle&) {
  return true;
}
}  // namespace cppgc::subtle

namespace base {
DelayedTaskHandle::DelayedTaskHandle() = default;
DelayedTaskHandle::~DelayedTaskHandle() = default;
bool DelayedTaskHandle::IsValid() const {
  return false;
}
Location::Location(const char* file_name, const void* program_counter)
    : file_name_(file_name), program_counter_(program_counter) {}
Location::Location(const char* function_name,
                   const char* file_name,
                   int line_number,
                   const void* program_counter)
    : function_name_(function_name),
      file_name_(file_name),
      line_number_(line_number),
      program_counter_(program_counter) {}
Location& Location::operator=(const Location&) = default;
Location Location::Current(const char* function_name,
                           const char* file_name,
                           int line_number) {
  return Location(function_name, file_name, line_number, nullptr);
}
Location Location::CurrentWithoutFunctionName(const char* file_name,
                                              int line_number) {
  return Location(nullptr, file_name, line_number, nullptr);
}
#if DCHECK_IS_ON()
ScopedValidateSequenceChecker::ScopedValidateSequenceChecker(
    const SequenceChecker&) {}
ScopedValidateSequenceChecker::~ScopedValidateSequenceChecker() = default;
#endif
}  // namespace base

namespace base::internal {
namespace {
bool StandaloneQueryCancellationTraits(
    const BindStateBase*,
    BindStateBase::CancellationQueryMode mode) {
  return std::to_underlying(mode);
}
}  // namespace
BindStateBase::BindStateBase(InvokeFuncStorage invoke, DestructorPtr destructor)
    : BindStateBase(invoke, destructor, &StandaloneQueryCancellationTraits) {}
BindStateBase::BindStateBase(InvokeFuncStorage invoke,
                             DestructorPtr destructor,
                             QueryCancellationTraitsPtr query)
    : polymorphic_invoke_(invoke),
      destructor_(destructor),
      query_cancellation_traits_(query) {}
BindStateHolder& BindStateHolder::operator=(BindStateHolder&&) noexcept =
    default;
bool BindStateHolder::IsCancelled() const {
  return bind_state_ && bind_state_->IsCancelled();
}
bool BindStateHolder::MaybeValid() const {
  return bind_state_ && bind_state_->MaybeValid();
}
void BindStateBaseRefCountTraits::Destruct(const BindStateBase* state) {
  delete state;
}
}  // namespace base::internal

namespace base::subtle {
void RefCountedBase::AddRefImpl() const {}
void RefCountedBase::ReleaseImpl() const {}
bool RefCountedBase::CalledOnValidSequence() const {
  return true;
}
bool RefCountedThreadSafeBase::HasOneRef() const {
  return false;
}
RefCountedThreadSafeBase::~RefCountedThreadSafeBase() = default;
}  // namespace base::subtle

namespace base::trace_event {
bool ConvertableToTraceFormat::AppendToProto(ProtoAppender*) const {
  return false;
}
}  // namespace base::trace_event

namespace base::internal {
template <bool AllowDangling>
bool RawPtrBackupRefImpl<AllowDangling>::IsPointeeAlive(uintptr_t) {
  return true;
}
template <bool AllowDangling>
void RawPtrBackupRefImpl<AllowDangling>::AcquireInternal(uintptr_t) {}
template <bool AllowDangling>
void RawPtrBackupRefImpl<AllowDangling>::ReleaseInternal(uintptr_t) {}
template <bool AllowDangling>
void RawPtrBackupRefImpl<AllowDangling>::ReportIfDanglingInternal(uintptr_t) {}
template void RawPtrBackupRefImpl<false>::AcquireInternal(uintptr_t);
template void RawPtrBackupRefImpl<true>::AcquireInternal(uintptr_t);
template void RawPtrBackupRefImpl<false>::ReleaseInternal(uintptr_t);
template void RawPtrBackupRefImpl<true>::ReleaseInternal(uintptr_t);
template void RawPtrBackupRefImpl<false>::ReportIfDanglingInternal(uintptr_t);
template void RawPtrBackupRefImpl<true>::ReportIfDanglingInternal(uintptr_t);
void CheckThatAddressIsntWithinFirstPartitionPage(uintptr_t) {}
}  // namespace base::internal

#if !defined(HTML_CSS_RENDERER_STANDALONE)
template <>
SkColor SkRGBA4f<kUnpremul_SkAlphaType>::toSkColor() const {
  return 0;
}
#endif

namespace std {
int uncaught_exceptions() noexcept {
  return 0;
}
ostream& operator<<(ostream& out, const u16string&) {
  return out;
}
}  // namespace std

namespace logging {
LogMessage::LogMessage(const char* file, int line, int severity)
    : severity_(severity), message_start_(0), file_(file), line_(line) {}
CheckError::CheckError(LogMessage* log_message) : log_message_(log_message) {}
CheckError::~CheckError() = default;
int GetVlogLevelHelper(const char*, size_t) {
  return 0;
}
bool ShouldCreateLogMessage(int) {
  return false;
}
LogMessage::~LogMessage() = default;
CheckError CheckError::NotImplemented(const char*, const base::Location&) {
  return CheckError(nullptr);
}
CheckError CheckError::DCheck(const char*, const base::Location&) {
  return CheckError(nullptr);
}
LogMessage* CheckError::DCheckOp(char*, const base::Location&) {
  return nullptr;
}
CheckNoreturnError CheckNoreturnError::Check(const char*,
                                             const base::Location&) {
  return CheckNoreturnError(nullptr);
}
LogMessage* CheckNoreturnError::CheckOp(char*, const base::Location&) {
  return nullptr;
}
CheckNoreturnError::~CheckNoreturnError() {
  std::abort();
}
std::ostream& CheckError::stream() {
  static std::ostream* stream = &std::cerr;
  return *stream;
}
NotReachedError NotReachedError::DumpWillBeNotReached(
    const base::Location&) {
  return NotReachedError(nullptr);
}
NotReachedError::~NotReachedError() = default;
LogMessageFatal::~LogMessageFatal() = default;
NotReachedNoreturnError::NotReachedNoreturnError(const base::Location&)
    : CheckError(nullptr) {}
NotReachedNoreturnError::~NotReachedNoreturnError() {
  std::abort();
}
void SetLogItems(bool, bool, bool, bool) {}
}  // namespace logging

namespace partition_alloc::internal {
PartitionAddressSpace::PoolSetup PartitionAddressSpace::setup_;
namespace base {
ScopedClearLastError::ScopedClearLastError() : last_system_error_(0) {}
ScopedClearLastError::~ScopedClearLastError() = default;
namespace strings {
CStringBuilder& CStringBuilder::operator<<(const char* text) {
  return *this;
}
const char* CStringBuilder::c_str() {
  return "";
}
}  // namespace strings
}  // namespace base
namespace logging {
LogMessage::LogMessage(const char* file, int line, LogSeverity severity)
    : severity_(severity),
      message_start_(0),
      file_(file),
      line_(line),
      last_error_() {}
LogMessage::LogMessage(const char* file, int line, const char* condition)
    : severity_(LOGGING_FATAL),
      message_start_(0),
      file_(file),
      line_(line),
      last_error_() {
  if (condition) {
    stream() << condition;
  }
}
LogMessage::~LogMessage() = default;
namespace check_error {
Check::Check(const char* file, int line, const char* condition)
    : CheckError(file, line, LOGGING_FATAL, condition) {}
}  // namespace check_error
CheckError::CheckError(const char* file,
                       int line,
                       LogSeverity severity,
                       const char*) {
  new (&log_message_) LogMessage(file, line, severity);
}
CheckError::CheckError(const char* file, int line, LogSeverity severity) {
  new (&log_message_) LogMessage(file, line, severity);
}
CheckError::CheckError(const char* file,
                       int line,
                       LogSeverity severity,
                       const char* condition,
                       SystemErrorCode) {
  new (&log_message_) LogMessage(file, line, condition);
}
CheckError::~CheckError() {
  log_message_.~LogMessage();
}
partition_alloc::internal::base::strings::CStringBuilder& CheckError::stream() {
  static partition_alloc::internal::base::strings::CStringBuilder* builder =
      new partition_alloc::internal::base::strings::CStringBuilder();
  return *builder;
}
}  // namespace logging
}  // namespace partition_alloc::internal

namespace skia {
SkFont DefaultFont() {
  return SkFont(SkTypeface::MakeEmpty(), 12.0f);
}
}  // namespace skia

int GrRecordingContext::maxTextureSize() const {
  return 0;
}
GrSemaphoresSubmitted GrDirectContext::flush(const GrFlushInfo&) {
  return GrSemaphoresSubmitted::kNo;
}
bool GrDirectContext::submit(const GrSubmitInfo&) {
  return false;
}
SkRuntimeEffect::Result SkRuntimeEffect::MakeForShader(
    SkString,
    const Options&) {
  return {};
}
sk_sp<SkColorFilter> SkRuntimeEffect::makeColorFilter(
    sk_sp<const SkData>) const {
  return nullptr;
}
const SkRuntimeEffect::Uniform* SkRuntimeEffect::findUniform(
    std::string_view) const {
  return nullptr;
}
const SkRuntimeEffect::Child* SkRuntimeEffect::findChild(
    std::string_view) const {
  return nullptr;
}
size_t SkRuntimeEffect::Uniform::sizeInBytes() const {
  return 0;
}
size_t SkRuntimeEffect::uniformSize() const {
  return 0;
}
sk_sp<SkShader> SkRuntimeEffectBuilder::makeShader(const SkMatrix*) const {
  return nullptr;
}
sk_sp<SkColorFilter> SkRuntimeEffectBuilder::makeColorFilter() const {
  return nullptr;
}
SkRuntimeEffect::Result SkRuntimeEffect::MakeForColorFilter(
    SkString,
    const Options&) {
  return {};
}
sk_sp<SkShader> SkRuntimeEffect::makeShader(sk_sp<const SkData>,
                                            sk_sp<SkShader>[],
                                            size_t,
                                            const SkMatrix*) const {
  return nullptr;
}
sk_sp<SkShader> SkRuntimeEffect::makeShader(sk_sp<const SkData>,
                                            SkSpan<const ChildPtr>,
                                            const SkMatrix*) const {
  return nullptr;
}
sk_sp<SkBlender> SkRuntimeEffect::makeBlender(sk_sp<const SkData>,
                                              SkSpan<const ChildPtr>) const {
  return nullptr;
}

namespace SkKnownRuntimeEffects {
bool IsSkiaKnownRuntimeEffect(int) {
  return false;
}
sk_sp<SkRuntimeEffect> MaybeGetKnownRuntimeEffect(uint32_t) {
  return nullptr;
}
const SkRuntimeEffect* GetKnownRuntimeEffect(StableKey) {
  return nullptr;
}
}  // namespace SkKnownRuntimeEffects

namespace SkSL {
Pool::~Pool() {
  fMemPool.release();
}
Program::~Program() {
  fSource.release();
  fConfig.release();
  fUsage.release();
  fSymbols.release();
  fPool.release();
  for (auto& element : fOwnedElements) {
    element.release();
  }
}
}  // namespace SkSL

void SkFlattenable::PrivateInitializer::InitEffects() {
  // The standalone build owns a narrow Skia initialization boundary instead of
  // linking Skia's full ports/SkGlobalInitialization_default.cc. Register the
  // shader flattenables required to deserialize Blink PaintFlags shader
  // resources (CSS gradients, local-matrix wrapped gradients, and simple
  // shader composition) without pulling browser/network services into the cut.
  SkRegisterBlendShaderFlattenable();
  SkRegisterColorShaderFlattenable();
  SkRegisterEmptyShaderFlattenable();
  SK_REGISTER_FLATTENABLE(SkLocalMatrixShader);
  SkRegisterConicalGradientShaderFlattenable();
  SkRegisterLinearGradientShaderFlattenable();
  SkRegisterRadialGradientShaderFlattenable();
  SkRegisterSweepGradientShaderFlattenable();
  SkRegisterWorkingColorSpaceShaderFlattenable();
  SkShaderBase::RegisterFlattenables();
}
void SkFlattenable::PrivateInitializer::InitImageFilters() {}

SkMeshSpecification::~SkMeshSpecification() {}
SkMesh::SkMesh() = default;
SkMesh::~SkMesh() {}
SkMesh::SkMesh(const SkMesh&) = default;

namespace skhdr {
void Metadata::setMasteringDisplayColorVolume(
    const MasteringDisplayColorVolume&) {}
void Metadata::setContentLightLevelInformation(
    const ContentLightLevelInformation&) {}
void Metadata::setAdaptiveGlobalToneMap(const AdaptiveGlobalToneMap&) {}
sk_sp<SkColorFilter> Metadata::makeToneMapColorFilter(
    float,
    const SkColorSpace*) const {
  return nullptr;
}
}  // namespace skhdr

std::unique_ptr<SkCanvas> SkStrikeServer::makeAnalysisCanvas(
    int width,
    int height,
    const SkSurfaceProps&,
    sk_sp<SkColorSpace>,
    bool,
    bool) {
  return SkMakeNullCanvas();
}

sk_sp<SkColorFilter> SkHighContrastFilter::Make(const SkHighContrastConfig&) {
  return nullptr;
}
sk_sp<SkColorFilter> SkLumaColorFilter::Make() {
  return nullptr;
}
sk_sp<SkColorFilter> SkOverdrawColorFilter::MakeWithSkColors(
    const SkColor[SkOverdrawColorFilter::kNumColors]) {
  return nullptr;
}
sk_sp<SkColorFilter> SkColorFilters::Lerp(float,
                                          sk_sp<SkColorFilter>,
                                          sk_sp<SkColorFilter>) {
  return nullptr;
}

namespace cc {
size_t NumberOfPlanesForYUVDecodeFormat(YUVDecodeFormat) {
  return 0;
}
ClientImageTransferCacheEntry::Image::Image() = default;
ClientImageTransferCacheEntry::Image::Image(const Image&) = default;
ClientImageTransferCacheEntry::Image&
ClientImageTransferCacheEntry::Image::operator=(const Image&) = default;
ClientImageTransferCacheEntry::Image::Image(const SkPixmap*) {}
ClientImageTransferCacheEntry::Image::Image(base::span<const SkPixmap>,
                                            const SkYUVAInfo&,
                                            const SkColorSpace*) {}
ClientImageTransferCacheEntry::ClientImageTransferCacheEntry(
    const Image& image,
    bool needs_mips,
    const gfx::HDRMetadata& hdr_metadata,
    sk_sp<SkColorSpace> target_color_space)
    : needs_mips_(needs_mips),
      target_color_space_(std::move(target_color_space)),
      id_(kInvalidImageTransferCacheEntryId),
      image_(image),
      hdr_metadata_(hdr_metadata) {}
ClientImageTransferCacheEntry::ClientImageTransferCacheEntry(
    const Image& image,
    const Image& gainmap_image,
    const SkGainmapInfo& gainmap_info,
    bool needs_mips)
    : needs_mips_(needs_mips),
      id_(kInvalidImageTransferCacheEntryId),
      image_(image),
      gainmap_image_(gainmap_image),
      gainmap_info_(gainmap_info) {}
ClientImageTransferCacheEntry::~ClientImageTransferCacheEntry() = default;
uint32_t ClientImageTransferCacheEntry::Id() const {
  return id_;
}
uint32_t ClientImageTransferCacheEntry::SerializedSize() const {
  return 0;
}
bool ClientImageTransferCacheEntry::Serialize(base::span<uint8_t>) const {
  return false;
}
base::AtomicSequenceNumber ClientImageTransferCacheEntry::s_next_id_;
ServiceImageTransferCacheEntry::ServiceImageTransferCacheEntry() = default;
ServiceImageTransferCacheEntry::~ServiceImageTransferCacheEntry() = default;
ServiceImageTransferCacheEntry::ServiceImageTransferCacheEntry(
    ServiceImageTransferCacheEntry&&) = default;
ServiceImageTransferCacheEntry& ServiceImageTransferCacheEntry::operator=(
    ServiceImageTransferCacheEntry&&) = default;
size_t ServiceImageTransferCacheEntry::CachedSize() const {
  return 0;
}
bool ServiceImageTransferCacheEntry::Deserialize(
    GrDirectContext*,
    skgpu::graphite::Recorder*,
    base::span<const uint8_t>) {
  return false;
}
void ServiceImageTransferCacheEntry::EnsureMips() {}
bool ServiceImageTransferCacheEntry::has_mips() const {
  return false;
}
const sk_sp<SkImage>& ServiceImageTransferCacheEntry::GetPlaneImage(
    size_t index) const {
  return plane_images_[index];
}
bool ServiceImageTransferCacheEntry::fits_on_gpu() const {
  return false;
}

ClientSkottieTransferCacheEntry::ClientSkottieTransferCacheEntry(
    scoped_refptr<SkottieWrapper> skottie)
    : skottie_(std::move(skottie)) {}
ClientSkottieTransferCacheEntry::~ClientSkottieTransferCacheEntry() = default;
uint32_t ClientSkottieTransferCacheEntry::Id() const {
  return 0;
}
uint32_t ClientSkottieTransferCacheEntry::SerializedSize() const {
  return 0;
}
bool ClientSkottieTransferCacheEntry::Serialize(base::span<uint8_t>) const {
  return false;
}
}  // namespace cc

namespace base {
class AsyncMemoryConsumerRegistration::MainThread {};
AsyncMemoryConsumerRegistration::AsyncMemoryConsumerRegistration(
    std::string_view,
    std::optional<MemoryConsumerTraits>,
    MemoryConsumer*,
    CheckUnregister,
    CheckRegistryExists) {}
AsyncMemoryConsumerRegistration::~AsyncMemoryConsumerRegistration() = default;
MemoryConsumer::MemoryConsumer() = default;
MemoryConsumerTraits::MemoryConsumerTraits(const MemoryConsumerTraits&) =
    default;
bool MemoryConsumerRegistry::Exists() {
  return false;
}
bool SingleThreadTaskRunner::HasMainThreadDefault() {
  return false;
}
const scoped_refptr<SingleThreadTaskRunner>&
SingleThreadTaskRunner::GetMainThreadDefault() {
  static const scoped_refptr<SingleThreadTaskRunner>* runner =
      new scoped_refptr<SingleThreadTaskRunner>();
  return *runner;
}
}  // namespace base

namespace blink {
ScriptLoader* ScriptElementBase::InitializeScriptLoader(CreateElementFlags flags) {
  return MakeGarbageCollected<ScriptLoader>(this, flags);
}
ScriptLoader::ScriptLoader(ScriptElementBase* element,
                           const CreateElementFlags)
    : element_(element) {}
ScriptLoader::~ScriptLoader() = default;
void ScriptLoader::Trace(Visitor* visitor) const {
  visitor->Trace(element_);
  ResourceFinishObserver::Trace(visitor);
}
ScriptLoader::ScriptTypeAtPrepare ScriptLoader::GetScriptTypeAtPrepare(
    const String&,
    const String&) {
  return ScriptTypeAtPrepare::kInvalid;
}
bool ScriptLoader::BlockForNoModule(ScriptTypeAtPrepare, bool) {
  return true;
}
network::mojom::CredentialsMode ScriptLoader::ModuleScriptCredentialsMode(
    CrossOriginAttributeValue) {
  return static_cast<network::mojom::CredentialsMode>(0);
}
PendingScript* ScriptLoader::PrepareScript(ParserBlockingInlineOption,
                                           const TextPosition&) {
  already_started_ = true;
  script_type_ = ScriptTypeAtPrepare::kInvalid;
  return nullptr;
}
void ScriptLoader::DidNotifySubtreeInsertionsToDocument() {}
void ScriptLoader::ChildrenChanged(const ContainerNode::ChildrenChange&) {}
void ScriptLoader::HandleSourceAttribute(const String&) {}
void ScriptLoader::HandleAsyncAttribute() {
  force_async_ = true;
}
void ScriptLoader::Removed() {}
void ScriptLoader::NotifyFinished() {}

void BlockingAttribute::OnAttributeValueChanged(const AtomicString&,
                                                const AtomicString&) {}
bool BlockingAttribute::ValidateTokenValue(const AtomicString&,
                                           ExceptionState&) const {
  return false;
}
bool DOMTokenList::contains(const AtomicString& token) const {
  return token_set_.Contains(token);
}
void RenderBlockingResourceManager::RemovePendingScript(
    const ScriptElementBase&) {}
void AttributionSrcLoader::Register(const AtomicString&,
                                    HTMLElement*,
                                    network::mojom::ReferrerPolicy) {}
v8::Local<v8::Value> V8UnionStringOrTrustedScript::DirectToV8(
    ScriptState*,
    const String&) {
  return v8::Local<v8::Value>();
}
void V8UnionHTMLScriptElementOrSVGScriptElement::Trace(Visitor*) const {}

MemoryConsumerRegistration::MemoryConsumerRegistration(
    std::string_view,
    std::optional<base::MemoryConsumerTraits>,
    base::MemoryConsumer*,
    CheckUnregister,
    CheckRegistryExists) {}
MemoryConsumerRegistration::~MemoryConsumerRegistration() = default;
void MemoryConsumerRegistration::Dispose() {}
}  // namespace blink

namespace blink::standalone_renderer_probe {
namespace {
void CopyProbeString(const char* value, char* out, int out_len) {
  if (!out || out_len <= 0) {
    return;
  }
  std::strncpy(out, value ? value : "", static_cast<size_t>(out_len - 1));
  out[out_len - 1] = '\0';
}
}  // namespace

int StandaloneBlinkRealPaintBridgeSurfaceReachableForStandaloneRenderer() {
  return 0;
}
int StandaloneBlinkRealPaintBridgeRequiresPaintCleanForStandaloneRenderer() {
  return 0;
}
void ResetStandaloneHTMLTreeBuilderRecordingForStandaloneRenderer() {}
void StandaloneHTMLTreeBuilderParseHTMLForStandaloneRenderer(const char*) {}
int StandaloneHTMLTreeBuilderRecordedNodeCountForStandaloneRenderer() {
  return 0;
}
int StandaloneHTMLTreeBuilderDOMSnapshotNodeCountForStandaloneRenderer() {
  return 0;
}
void StandaloneHTMLTreeBuilderDOMSnapshotNodeKindAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderDOMSnapshotNodeNameAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderDOMSnapshotNodeValueAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderRecordedNodeKindAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderRecordedNodeNameAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderRecordedNodeValueAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
int StandaloneHTMLTreeBuilderDOMSnapshotParentAtForStandaloneRenderer(int) {
  return -1;
}
int StandaloneHTMLTreeBuilderDOMSnapshotDepthAtForStandaloneRenderer(int) {
  return 0;
}
int StandaloneHTMLTreeBuilderDOMSnapshotFirstChildAtForStandaloneRenderer(int) {
  return -1;
}
int StandaloneHTMLTreeBuilderDOMSnapshotNextSiblingAtForStandaloneRenderer(int) {
  return -1;
}
int StandaloneHTMLTreeBuilderDOMSnapshotChildCountAtForStandaloneRenderer(int) {
  return 0;
}
int StandaloneHTMLTreeBuilderRecordedParentAtForStandaloneRenderer(int) {
  return -1;
}
int StandaloneHTMLTreeBuilderRecordedDepthAtForStandaloneRenderer(int) {
  return 0;
}
int StandaloneHTMLTreeBuilderRecordedFirstChildAtForStandaloneRenderer(int) {
  return -1;
}
int StandaloneHTMLTreeBuilderRecordedNextSiblingAtForStandaloneRenderer(int) {
  return -1;
}
int StandaloneHTMLTreeBuilderRecordedChildCountAtForStandaloneRenderer(int) {
  return 0;
}
int StandaloneHTMLTreeBuilderDOMLinkedNodeCountForStandaloneRenderer() {
  return 0;
}
int StandaloneHTMLTreeBuilderDOMLinkedMaxDepthForStandaloneRenderer() {
  return 0;
}
int StandaloneHTMLTreeBuilderLayoutSnapshotBoxCountForStandaloneRenderer() {
  return 0;
}
void StandaloneHTMLTreeBuilderLayoutSnapshotRoleAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
int StandaloneHTMLTreeBuilderLayoutSnapshotNodeAtForStandaloneRenderer(int) {
  return -1;
}
float StandaloneHTMLTreeBuilderLayoutSnapshotXAtForStandaloneRenderer(int) {
  return 0.0f;
}
float StandaloneHTMLTreeBuilderLayoutSnapshotYAtForStandaloneRenderer(int) {
  return 0.0f;
}
float StandaloneHTMLTreeBuilderLayoutSnapshotWidthAtForStandaloneRenderer(int) {
  return 0.0f;
}
float StandaloneHTMLTreeBuilderLayoutSnapshotHeightAtForStandaloneRenderer(int) {
  return 0.0f;
}
int StandaloneHTMLTreeBuilderPaintArtifactChunkCountForStandaloneRenderer() {
  return 0;
}
void StandaloneHTMLTreeBuilderPaintArtifactChunkIdAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderPaintArtifactChunkRoleAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
void StandaloneHTMLTreeBuilderPaintArtifactChunkOpAtForStandaloneRenderer(
    int,
    char* out,
    int out_len) {
  CopyProbeString("", out, out_len);
}
int StandaloneHTMLTreeBuilderPaintArtifactChunkNodeAtForStandaloneRenderer(int) {
  return -1;
}
float StandaloneHTMLTreeBuilderPaintArtifactChunkXAtForStandaloneRenderer(int) {
  return 0.0f;
}
float StandaloneHTMLTreeBuilderPaintArtifactChunkYAtForStandaloneRenderer(int) {
  return 0.0f;
}
float StandaloneHTMLTreeBuilderPaintArtifactChunkWidthAtForStandaloneRenderer(
    int) {
  return 0.0f;
}
float StandaloneHTMLTreeBuilderPaintArtifactChunkHeightAtForStandaloneRenderer(
    int) {
  return 0.0f;
}
}  // namespace blink::standalone_renderer_probe
