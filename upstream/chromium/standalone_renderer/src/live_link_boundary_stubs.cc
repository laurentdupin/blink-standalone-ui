// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/loader/resource/css_style_sheet_resource.h"
#include "third_party/blink/renderer/core/css/style_sheet.h"
#include "third_party/blink/renderer/core/html/custom/ce_reactions_scope.h"
#include "third_party/blink/renderer/core/layout/mathml/math_fraction_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_layout_utils.h"
#include "third_party/blink/renderer/core/layout/mathml/math_padded_layout_algorithm.h"
#include "third_party/blink/renderer/core/layout/mathml/math_space_layout_algorithm.h"
#include "third_party/blink/renderer/core/mathml/mathml_table_cell_element.h"

#include "base/trace_event/trace_arguments.h"
#include "base/cpu.h"
#include "base/feature_list.h"
#include "base/features.h"
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
#include "base/memory/scoped_refptr.h"
#include "base/memory/discardable_memory_allocator.h"
#include "base/synchronization/lock.h"
#include "base/task/task_traits.h"
#include "base/trace_event/memory_allocator_dump.h"
#include "base/trace_event/process_memory_dump.h"
#include "base/trace_event/traced_value.h"
#include "base/time/default_tick_clock.h"
#include "base/sequence_checker.h"
#include "base/threading/thread_checker_impl.h"
#include "base/timer/elapsed_timer.h"
#include "base/timer/lap_timer.h"
#include "base/win/scoped_handle.h"
#include "base/allocator/partition_allocator/src/partition_alloc/allocation_guard.h"
#include "base/allocator/partition_allocator/src/partition_alloc/oom.h"
#include "cc/animation/animation_id_provider.h"
#include "skia/ext/font_utils.h"
#include "include/codec/SkCodec.h"
#include "include/codec/SkPngRustDecoder.h"
#include "src/codec/SkPngCodec.h"
#ifdef DrawText
#undef DrawText
#endif
#include "html_css_renderer/standalone_resource_provider.h"
#include "services/network/public/cpp/single_request_url_loader_factory.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/frame/delegated_capability_request_token.h"
#include "third_party/blink/public/common/permissions_policy/document_policy.h"
#include "third_party/blink/public/common/permissions_policy/policy_value.h"
#include "third_party/blink/public/resources/grit/blink_image_resources.h"
#include "third_party/blink/public/resources/grit/blink_resources.h"
#include "third_party/blink/public/common/thread_safe_browser_interface_broker_proxy.h"
#include "third_party/blink/public/platform/platform.h"
#include "third_party/blink/public/platform/scheduler/web_agent_group_scheduler.h"
#include "third_party/blink/public/platform/scheduler/web_thread_scheduler.h"
#include "third_party/blink/renderer/core/html_element_factory.h"
#include "third_party/blink/renderer/core/html/forms/form_data.h"
#include "third_party/blink/renderer/core/html/forms/html_data_list_element.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"
#include "third_party/blink/renderer/core/html/forms/html_options_collection.h"
#include "third_party/blink/renderer/core/html/forms/html_opt_group_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/html_selected_content_element.h"
#include "third_party/blink/renderer/core/html/forms/html_text_area_element.h"
#include "third_party/blink/renderer/core/html/forms/text_control_element.h"
#include "third_party/blink/renderer/core/dom/opaque_range.h"
#include "third_party/blink/renderer/core/html/html_base_element.h"
#include "third_party/blink/renderer/core/html/html_script_element.h"
#include "third_party/blink/renderer/core/html/html_span_element.h"
#include "third_party/blink/renderer/core/html/html_style_element.h"
#include "third_party/blink/renderer/core/html/html_table_caption_element.h"
#include "third_party/blink/renderer/core/html/html_table_cell_element.h"
#include "third_party/blink/renderer/core/html/html_table_col_element.h"
#include "third_party/blink/renderer/core/html/html_table_element.h"
#include "third_party/blink/renderer/core/html/html_table_row_element.h"
#include "third_party/blink/renderer/core/html/html_table_section_element.h"
#include "third_party/blink/renderer/core/events/animation_playback_event.h"
#include "third_party/blink/renderer/core/editing/selection_controller.h"
#include "third_party/blink/renderer/core/html/canvas/image_element_base.h"
#include "third_party/blink/renderer/platform/heap/custom_spaces.h"
#include "v8/include/cppgc/platform.h"
#include "v8/include/v8-platform.h"

#include "third_party/blink/renderer/core/html/cross_origin_attribute.h"
#include "third_party/blink/renderer/core/html/html_image_element.h"
#include "third_party/blink/renderer/core/html/html_picture_element.h"
#include "third_party/blink/renderer/core/html/html_source_element.h"
#include "third_party/blink/renderer/core/svg/svg_animated_angle.h"
#include "third_party/blink/renderer/core/svg/svg_animated_enumeration_base.h"
#include "third_party/blink/renderer/core/svg/svg_filter_element.h"
#include "third_party/blink/renderer/core/svg/svg_fe_image_element.h"
#include "third_party/blink/renderer/core/svg/svg_image_element.h"
#include "third_party/blink/renderer/core/svg/svg_line_element.h"
#include "third_party/blink/renderer/core/svg/svg_marker_element.h"
#include "third_party/blink/renderer/core/svg/svg_mpath_element.h"
#include "third_party/blink/renderer/core/svg/svg_path_element.h"
#include "third_party/blink/renderer/core/svg/svg_resource_document_content.h"
#include "third_party/blink/renderer/core/svg/svg_string_list_tear_off.h"
#include "third_party/blink/renderer/core/html/loading_attribute.h"
#include "third_party/blink/renderer/core/css/media_values_dynamic.h"
#include "third_party/blink/renderer/core/css/cssom/css_unit_value.h"
#include "third_party/blink/renderer/core/css/media_query_list_listener.h"
#include "third_party/blink/renderer/core/css/parser/sizes_attribute_parser.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver_state.h"
#include "third_party/blink/renderer/core/html/parser/html_srcset_parser.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_initiator_type_names.h"
#include "third_party/blink/renderer/core/html/html_image_fallback_helper.h"
#include "third_party/blink/renderer/core/html/html_object_element.h"
#include "third_party/blink/renderer/core/highlight/highlight_style_utils.h"
#include "third_party/blink/renderer/core/image_replacement/document_image_replacements.h"
#include "third_party/blink/renderer/core/image_replacement/image_replacement.h"
#include "third_party/blink/renderer/core/inspector/identifiers_factory.h"
#include "third_party/blink/renderer/core/layout/layout_block.h"
#include "third_party/blink/renderer/core/layout/layout_box_model_object.h"
#include "third_party/blink/renderer/core/layout/layout_inline.h"
#include "third_party/blink/renderer/core/layout/layout_image_replacement.h"
#include "third_party/blink/renderer/core/layout/length_utils.h"
#include "third_party/blink/renderer/core/layout/layout_media.h"
#include "third_party/blink/renderer/core/loader/resource/image_resource.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_response.h"
#include "third_party/blink/renderer/core/svg/graphics/svg_image_for_container.h"
#include "third_party/blink/renderer/core/svg/svg_animated_length.h"
#include "third_party/blink/renderer/core/svg/svg_animated_length_list.h"
#include "third_party/blink/renderer/core/svg/svg_animated_number.h"
#include "third_party/blink/renderer/core/svg/svg_animated_number_list.h"
#include "third_party/blink/renderer/core/svg/svg_animated_preserve_aspect_ratio.h"
#include "third_party/blink/renderer/core/svg/svg_animated_rect.h"
#include "third_party/blink/renderer/core/svg/svg_animated_transform_list.h"
#include "third_party/blink/renderer/core/svg/svg_angle_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_desc_element.h"
#include "third_party/blink/renderer/core/svg/svg_length_list_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_length_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_matrix_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_number_list_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_number_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_point_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_preserve_aspect_ratio_tear_off.h"
#include "third_party/blink/renderer/platform/graphics/compositor_element_id.h"
#include "third_party/blink/renderer/core/svg/svg_svg_element.h"
#include "third_party/blink/renderer/core/svg/svg_text_element.h"
#include "third_party/blink/renderer/core/svg/svg_title_element.h"
#include "third_party/blink/renderer/core/svg/svg_transform_list_tear_off.h"
#include "third_party/blink/renderer/core/svg/svg_transform_tear_off.h"
#include "third_party/blink/renderer/core/animation/timeline_trigger.h"
#include "third_party/blink/renderer/core/animation/css_color_interpolation_type.h"
#include "third_party/blink/renderer/core/animation/css_default_interpolation_type.h"
#include "third_party/blink/renderer/core/animation/css_length_interpolation_type.h"
#include "third_party/blink/renderer/core/animation/css_number_interpolation_type.h"
#include "third_party/blink/renderer/core/animation/css_transform_interpolation_type.h"
#include "third_party/blink/renderer/core/animation/css/css_transition.h"
#include "third_party/blink/renderer/core/animation/effect_input.h"
#include "third_party/blink/renderer/core/animation/interpolation_types_map.h"
#include "third_party/blink/renderer/core/animation/timing_calculations.h"
#include "third_party/blink/renderer/core/animation/timing_input.h"
#include "third_party/blink/renderer/core/css/css_property_names.h"
#include "third_party/blink/renderer/core/css/properties/css_property.h"
#include "third_party/blink/renderer/platform/heap/collection_support/heap_hash_map.h"
#include "third_party/blink/renderer/platform/heap/persistent.h"
#include "third_party/blink/renderer/core/paint/timing/image_element_timing.h"
#include "third_party/blink/renderer/core/paint/timing/paint_timing_detector.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_error.h"
#include "third_party/blink/renderer/platform/network/mime/content_type.h"
#include "third_party/blink/renderer/platform/network/mime/mime_type_registry.h"
#include "third_party/blink/renderer/core/html/html_li_element.h"
#include "third_party/blink/renderer/core/html/html_olist_element.h"
#include "third_party/blink/renderer/core/html/html_ulist_element.h"
#include "third_party/blink/renderer/core/input/input_device_capabilities.h"
#include "third_party/blink/renderer/core/input/gesture_manager.h"
#include "third_party/blink/renderer/core/html/blocking_attribute.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_types_util.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_htmlscriptelement_svgscriptelement.h"
#include "third_party/blink/renderer/bindings/core/v8/active_script_wrappable_creation_key.h"
#include "third_party/blink/renderer/bindings/core/v8/script_value.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_mutation_observer_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_htmlelement_long.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_htmloptgroupelement_htmloptionelement.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_string_trustedscript.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_stringlegacynulltoemptystring_trustedscript.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_union_trustedscripturl_usvstring.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_event_modifier_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_mouse_event_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_pointer_event_init.h"
#include "third_party/blink/renderer/bindings/core/v8/v8_drag_event_init.h"
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
#include "net/base/platform_mime_util.h"
#include "net/http/http_log_util.h"
#include "third_party/abseil-cpp/absl/container/internal/hashtablez_sampler.h"
#include <cstdarg>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <future>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <malloc.h>
#include <new>
#include <ostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "unicode/ubidi.h"
#include "unicode/uchar.h"
#include "third_party/skia/include/core/SkFlattenable.h"
#include "third_party/skia/src/effects/SkDashImpl.h"
#include "third_party/skia/src/shaders/SkLocalMatrixShader.h"
#include "third_party/skia/src/shaders/SkPictureShader.h"
#include "third_party/skia/src/shaders/SkShaderBase.h"
#include "third_party/skia/src/shaders/gradients/SkGradientBaseShader.h"
#include "unicode/uscript.h"
#include "hb-ot.h"

extern "C" const char icudt78_dat[] = {0};

#if BUILDFLAG(IS_WIN)
extern "C" {
__declspec(dllimport) void* __stdcall GetModuleHandleW(const wchar_t*);
__declspec(dllimport) void* __stdcall LoadLibraryW(const wchar_t*);
__declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId();
__declspec(dllimport) void __stdcall AcquireSRWLockExclusive(void*);
__declspec(dllimport) void* __stdcall VirtualAlloc(void*,
                                                   size_t,
                                                   unsigned long,
                                                   unsigned long);
__declspec(dllimport) int __stdcall VirtualFree(void*, size_t, unsigned long);
__declspec(dllimport) int __stdcall VirtualProtect(void*,
                                                   size_t,
                                                   unsigned long,
                                                   unsigned long*);
}

extern "C" int RAND_bytes(uint8_t* buffer, size_t length) {
  using ProcessPrngFn = int(__stdcall*)(unsigned char*, size_t);
  static ProcessPrngFn process_prng = []() -> ProcessPrngFn {
    void* module = ::GetModuleHandleW(L"bcryptprimitives.dll");
    if (!module) {
      module = ::LoadLibraryW(L"bcryptprimitives.dll");
    }
    if (!module) {
      return nullptr;
    }
    return reinterpret_cast<ProcessPrngFn>(
        ::GetProcAddress(module, "ProcessPrng"));
  }();
  return process_prng && process_prng(buffer, length) ? 1 : 0;
}
#endif

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
#include "ui/gfx/geometry/skia_conversions.h"
#include "url/gurl.h"
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
#include "third_party/skia/modules/skcms/skcms.h"
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
#include "third_party/blink/renderer/core/css/parser/css_parser_context.h"
#include "third_party/blink/renderer/core/css/parser/css_parser_token_stream.h"
#include "third_party/blink/renderer/core/css/properties/css_parsing_utils.h"
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
#include "third_party/blink/renderer/core/page/touch_adjustment.h"
#include "third_party/blink/renderer/core/page/context_menu_controller.h"
#include "third_party/blink/renderer/core/page/drag_controller.h"
#include "third_party/blink/renderer/core/page/focus_controller.h"
#include "third_party/blink/renderer/core/page/link_highlight.h"
#include "third_party/blink/renderer/core/page/page.h"
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
#include "ui/gfx/geometry/point_conversions.h"
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
#include "third_party/blink/renderer/core/clipboard/data_transfer.h"
#include "third_party/blink/renderer/core/clipboard/data_transfer_access_policy.h"
#include "third_party/blink/renderer/core/clipboard/data_object.h"
#include "third_party/blink/renderer/core/clipboard/data_object_item.h"
#include "third_party/blink/renderer/core/dom/processing_instruction.h"
#include "third_party/blink/renderer/core/dom/document_fragment.h"
#include "third_party/blink/renderer/core/dom/mutation_observer_interest_group.h"
#include "third_party/blink/renderer/core/dom/scroll_marker_group_data.h"
#include "third_party/blink/renderer/core/dom/shadow_root.h"
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
#include "third_party/blink/renderer/core/editing/local_caret_rect.h"
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
#include "third_party/blink/renderer/core/events/pointer_event.h"
#include "third_party/blink/renderer/core/events/drag_event.h"
#include "third_party/blink/renderer/core/events/wheel_event.h"
#include "third_party/blink/renderer/core/events/text_event.h"
#include "third_party/blink/renderer/core/events/toggle_event.h"
#include "third_party/blink/renderer/core/events/transition_event.h"
#include "third_party/blink/renderer/core/events/ui_event.h"
#include "third_party/blink/renderer/core/events/pointer_event_factory.h"
#include "third_party/blink/renderer/core/events/web_input_event_conversion.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/input/touch.h"
#include "third_party/blink/renderer/core/input/touch_list.h"
#include "third_party/blink/renderer/core/execution_context/execution_context_lifecycle_observer.h"
#include "third_party/blink/renderer/core/execution_context/execution_context_lifecycle_state_observer.h"
#include "third_party/blink/renderer/core/fileapi/public_url_manager.h"
#include "third_party/blink/renderer/core/fileapi/file_list.h"
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
#include "third_party/blink/renderer/core/input/keyboard_event_manager.h"
#include "third_party/blink/renderer/core/input/touch_event_manager.h"
#include "third_party/blink/renderer/core/input/widget_event_handler.h"
#include "third_party/blink/renderer/core/page/drag_state.h"
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
#include "third_party/blink/renderer/core/svg_names.h"
#include "third_party/blink/renderer/core/svg/svg_circle_element.h"
#include "third_party/blink/renderer/core/svg/svg_rect_element.h"
#include "third_party/blink/renderer/core/svg/svg_svg_element.h"
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
#include "third_party/blink/renderer/core/html/forms/file_input_type.h"
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
#include "third_party/blink/renderer/core/html/forms/step_range.h"
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
#include "third_party/blink/renderer/core/layout/svg/layout_svg_text_path.h"
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
#include "third_party/blink/renderer/core/script/xml_parser_script_runner.h"
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
#include "third_party/blink/renderer/core/layout/hit_test_location.h"
#include "third_party/blink/renderer/platform/fonts/font.h"
#include "third_party/blink/renderer/platform/fonts/font_fallback_list.h"
#include "third_party/blink/renderer/platform/fonts/plain_text_painter.h"
#include "third_party/blink/renderer/platform/fonts/simple_font_data.h"
#include "third_party/blink/renderer/platform/graphics/dark_mode_image_cache.h"
#include "third_party/blink/renderer/platform/graphics/bitmap_image.h"
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
#include "third_party/blink/renderer/core/trustedtypes/trusted_script_url.h"
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
#include "third_party/blink/renderer/platform/network/http_parsers.h"
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
#include "third_party/blink/renderer/platform/bindings/exception_messages.h"
#include "third_party/blink/renderer/platform/instrumentation/instance_counters.h"
#include "third_party/blink/renderer/platform/instrumentation/histogram.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/web_memory_allocator_dump.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/web_process_memory_dump.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/traced_value.h"
#include "third_party/blink/renderer/platform/disk_data_allocator.h"
#include "third_party/blink/renderer/platform/disk_data_metadata.h"
#include "third_party/blink/renderer/platform/instrumentation/resource_coordinator/document_resource_coordinator.h"
#include "third_party/blink/renderer/platform/loader/fetch/memory_cache.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_parameters.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_loader.h"
#include "third_party/blink/public/common/loader/referrer_utils.h"
#include "third_party/blink/renderer/platform/bindings/runtime_call_stats.h"
#include "third_party/blink/renderer/platform/bindings/script_regexp.h"
#include "third_party/blink/renderer/platform/bindings/parkable_string.h"
#include "third_party/blink/renderer/platform/fonts/font_performance.h"
#include "third_party/blink/renderer/platform/graphics/compositing/paint_artifact_compositor.h"
#include "third_party/blink/renderer/platform/geometry/length_functions.h"
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
#include "third_party/blink/renderer/platform/wtf/allocator/partitions.h"
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

namespace SkPngRustDecoder {
bool IsPng(const void* data, size_t len) {
  return SkPngCodec::IsPng(data, len);
}

std::unique_ptr<SkCodec> Decode(std::unique_ptr<SkStream> stream,
                                SkCodec::Result* result,
                                SkCodecs::DecodeContext) {
  SkCodec::Result result_storage;
  if (!result) {
    result = &result_storage;
  }
  return SkPngCodec::MakeFromStream(std::move(stream), result);
}
}  // namespace SkPngRustDecoder

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
scoped_refptr<SharedURLLoaderFactory> SharedURLLoaderFactory::Create(
    std::unique_ptr<PendingSharedURLLoaderFactory> pending_factory) {
  return pending_factory ? pending_factory->CreateFactory() : nullptr;
}

bool SharedURLLoaderFactory::BypassRedirectChecks() const {
  return false;
}

SharedURLLoaderFactory::~SharedURLLoaderFactory() = default;

PendingSharedURLLoaderFactory::PendingSharedURLLoaderFactory() = default;
PendingSharedURLLoaderFactory::~PendingSharedURLLoaderFactory() = default;

class SingleRequestURLLoaderFactory::HandlerState
    : public base::RefCounted<SingleRequestURLLoaderFactory::HandlerState> {
 public:
  explicit HandlerState(FullRequestHandler handler)
      : handler_(std::move(handler)) {}

  HandlerState(const HandlerState&) = delete;
  HandlerState& operator=(const HandlerState&) = delete;

  void CreateLoaderAndStart(
      mojo::PendingReceiver<mojom::URLLoader> loader,
      int32_t request_id,
      uint32_t options,
      const ResourceRequest& request,
      mojo::PendingRemote<mojom::URLLoaderClient> client,
      const net::MutableNetworkTrafficAnnotationTag& traffic_annotation) {
    if (handler_) {
      std::move(handler_).Run(std::move(loader), request_id, options, request,
                              std::move(client), traffic_annotation);
    }
  }

 private:
  friend class base::RefCounted<HandlerState>;
  ~HandlerState() = default;

  FullRequestHandler handler_;
};

class SingleRequestURLLoaderFactory::PendingFactory
    : public PendingSharedURLLoaderFactory {
 public:
  explicit PendingFactory(scoped_refptr<HandlerState> state)
      : state_(std::move(state)) {}
  ~PendingFactory() override = default;

 private:
  scoped_refptr<SharedURLLoaderFactory> CreateFactory() override {
    return base::WrapRefCounted(
        new SingleRequestURLLoaderFactory(std::move(state_)));
  }

  scoped_refptr<HandlerState> state_;
};

SingleRequestURLLoaderFactory::SingleRequestURLLoaderFactory(
    RequestHandler handler)
    : state_(base::MakeRefCounted<HandlerState>(base::BindOnce(
          [](RequestHandler handler,
             mojo::PendingReceiver<mojom::URLLoader> loader,
             int32_t,
             uint32_t,
             const ResourceRequest& request,
             mojo::PendingRemote<mojom::URLLoaderClient> client,
             const net::MutableNetworkTrafficAnnotationTag&) {
            std::move(handler).Run(request, std::move(loader),
                                   std::move(client));
          },
          std::move(handler)))) {}

SingleRequestURLLoaderFactory::SingleRequestURLLoaderFactory(
    FullRequestHandler full_handler)
    : state_(base::MakeRefCounted<HandlerState>(std::move(full_handler))) {}

SingleRequestURLLoaderFactory::SingleRequestURLLoaderFactory(
    scoped_refptr<HandlerState> state)
    : state_(std::move(state)) {}

SingleRequestURLLoaderFactory::~SingleRequestURLLoaderFactory() = default;

void SingleRequestURLLoaderFactory::CreateLoaderAndStart(
    mojo::PendingReceiver<mojom::URLLoader> loader,
    int32_t request_id,
    uint32_t options,
    const ResourceRequest& request,
    mojo::PendingRemote<mojom::URLLoaderClient> client,
    const net::MutableNetworkTrafficAnnotationTag& traffic_annotation) {
  state_->CreateLoaderAndStart(std::move(loader), request_id, options, request,
                               std::move(client), traffic_annotation);
}

void SingleRequestURLLoaderFactory::Clone(
    mojo::PendingReceiver<mojom::URLLoaderFactory>) {}

std::unique_ptr<PendingSharedURLLoaderFactory>
SingleRequestURLLoaderFactory::Clone() {
  return std::make_unique<PendingFactory>(state_);
}

PermissionsPolicyFeaturesBitset::~PermissionsPolicyFeaturesBitset() = default;
}  // namespace network

namespace base {
namespace internal {
}  // namespace internal
}  // namespace base

namespace blink::scheduler {
WebThreadScheduler::~WebThreadScheduler() = default;

scoped_refptr<base::SingleThreadTaskRunner>
WebThreadScheduler::DeprecatedDefaultTaskRunner() {
  return base::SingleThreadTaskRunner::GetCurrentDefault();
}

std::unique_ptr<blink::MainThread> WebThreadScheduler::CreateMainThread() {
  return nullptr;
}

void WebThreadScheduler::SetRendererBackgrounded(bool) {}

void WebThreadScheduler::OnUrgentMessageReceived() {}

void WebThreadScheduler::OnUrgentMessageProcessed() {}
}  // namespace blink::scheduler

namespace blink {
extern "C" bool g_standalone_blink_saw_font_draw_text = false;
extern "C" int g_standalone_blink_viewport_width = 800;
extern "C" int g_standalone_blink_viewport_height = 600;
extern "C" int g_standalone_css_animation_timeline_update_called = 0;
extern "C" int g_standalone_css_animation_update_called = 0;
extern "C" int g_standalone_css_transition_update_called = 0;
extern "C" int g_standalone_document_animations_update_called = 0;
extern "C" int g_standalone_page_animator_service_called = 0;
extern "C" int g_standalone_oof_layout_part_run_called = 0;
extern "C" int g_standalone_oof_candidate_count = 0;
extern "C" int g_standalone_oof_descendant_collected = 0;
extern "C" int g_standalone_oof_layout_attempted = 0;
extern "C" int g_standalone_oof_fragment_created = 0;
extern "C" int g_standalone_oof_candidate_repropagated = 0;
extern "C" int g_standalone_oof_candidate_dropped_at_root = 0;
extern "C" int g_standalone_oof_unsupported_inline_containing_block = 0;
extern "C" int g_standalone_oof_layout_null_results = 0;
extern "C" int g_standalone_oof_zero_size_fragments = 0;
extern "C" int g_standalone_oof_safety_limit_hit = 0;

extern "C" void StandaloneRendererResetOutOfFlowDiagnostics() {
  g_standalone_oof_layout_part_run_called = 0;
  g_standalone_oof_candidate_count = 0;
  g_standalone_oof_descendant_collected = 0;
  g_standalone_oof_layout_attempted = 0;
  g_standalone_oof_fragment_created = 0;
  g_standalone_oof_candidate_repropagated = 0;
  g_standalone_oof_candidate_dropped_at_root = 0;
  g_standalone_oof_unsupported_inline_containing_block = 0;
  g_standalone_oof_layout_null_results = 0;
  g_standalone_oof_zero_size_fragments = 0;
  g_standalone_oof_safety_limit_hit = 0;
}

namespace {
struct StandaloneMediaQueryEvaluationTrace {
  std::string feature;
  std::string expected_value;
  std::string actual_value;
  std::string result;
  std::string unsupported_reason;
};

std::vector<StandaloneMediaQueryEvaluationTrace>&
StandaloneMediaQueryEvaluationTraces() {
  static std::vector<StandaloneMediaQueryEvaluationTrace>* traces =
      new std::vector<StandaloneMediaQueryEvaluationTrace>();
  return *traces;
}

std::map<std::string, std::string>& StandaloneMediaQueryParsedExpectedValues() {
  static std::map<std::string, std::string>* values =
      new std::map<std::string, std::string>();
  return *values;
}

std::string StandaloneJsonEscape(const std::string& value) {
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

std::string StandaloneJsonString(const std::string& value) {
  return "\"" + StandaloneJsonEscape(value) + "\"";
}

std::string StandaloneKleeneValueString(KleeneValue value) {
  switch (value) {
    case KleeneValue::kTrue:
      return "true";
    case KleeneValue::kFalse:
      return "false";
    case KleeneValue::kUnknown:
      return "unknown";
  }
  return "unknown";
}

std::string StandaloneMediaQueryActualValue(const String& feature) {
  if (feature == media_feature_names::kWidthMediaFeature ||
      feature == media_feature_names::kMinWidthMediaFeature ||
      feature == media_feature_names::kMaxWidthMediaFeature ||
      feature == media_feature_names::kInlineSizeMediaFeature ||
      feature == media_feature_names::kMinInlineSizeMediaFeature ||
      feature == media_feature_names::kMaxInlineSizeMediaFeature ||
      feature == media_feature_names::kDeviceWidthMediaFeature ||
      feature == media_feature_names::kMinDeviceWidthMediaFeature ||
      feature == media_feature_names::kMaxDeviceWidthMediaFeature) {
    return std::to_string(g_standalone_blink_viewport_width) + "px";
  }
  if (feature == media_feature_names::kHeightMediaFeature ||
      feature == media_feature_names::kMinHeightMediaFeature ||
      feature == media_feature_names::kMaxHeightMediaFeature ||
      feature == media_feature_names::kBlockSizeMediaFeature ||
      feature == media_feature_names::kMinBlockSizeMediaFeature ||
      feature == media_feature_names::kMaxBlockSizeMediaFeature ||
      feature == media_feature_names::kDeviceHeightMediaFeature ||
      feature == media_feature_names::kMinDeviceHeightMediaFeature ||
      feature == media_feature_names::kMaxDeviceHeightMediaFeature) {
    return std::to_string(g_standalone_blink_viewport_height) + "px";
  }
  if (feature == media_feature_names::kOrientationMediaFeature) {
    return g_standalone_blink_viewport_width >= g_standalone_blink_viewport_height
               ? "landscape"
               : "portrait";
  }
  if (feature == media_feature_names::kHoverMediaFeature ||
      feature == media_feature_names::kAnyHoverMediaFeature) {
    return "hover";
  }
  if (feature == media_feature_names::kPointerMediaFeature ||
      feature == media_feature_names::kAnyPointerMediaFeature) {
    return "fine";
  }
  if (feature == media_feature_names::kPrefersColorSchemeMediaFeature) {
    return "light";
  }
  if (feature == media_feature_names::kPrefersReducedMotionMediaFeature) {
    return "no-preference";
  }
  return "unsupported_or_unknown";
}

bool StandaloneMediaQueryFeatureSupportedForDiagnostics(const String& feature) {
  return feature == media_feature_names::kWidthMediaFeature ||
         feature == media_feature_names::kMinWidthMediaFeature ||
         feature == media_feature_names::kMaxWidthMediaFeature ||
         feature == media_feature_names::kHeightMediaFeature ||
         feature == media_feature_names::kMinHeightMediaFeature ||
         feature == media_feature_names::kMaxHeightMediaFeature ||
         feature == media_feature_names::kInlineSizeMediaFeature ||
         feature == media_feature_names::kMinInlineSizeMediaFeature ||
         feature == media_feature_names::kMaxInlineSizeMediaFeature ||
         feature == media_feature_names::kBlockSizeMediaFeature ||
         feature == media_feature_names::kMinBlockSizeMediaFeature ||
         feature == media_feature_names::kMaxBlockSizeMediaFeature ||
         feature == media_feature_names::kDeviceWidthMediaFeature ||
         feature == media_feature_names::kMinDeviceWidthMediaFeature ||
         feature == media_feature_names::kMaxDeviceWidthMediaFeature ||
         feature == media_feature_names::kDeviceHeightMediaFeature ||
         feature == media_feature_names::kMinDeviceHeightMediaFeature ||
         feature == media_feature_names::kMaxDeviceHeightMediaFeature ||
         feature == media_feature_names::kOrientationMediaFeature ||
         feature == media_feature_names::kHoverMediaFeature ||
         feature == media_feature_names::kAnyHoverMediaFeature ||
         feature == media_feature_names::kPointerMediaFeature ||
         feature == media_feature_names::kAnyPointerMediaFeature ||
         feature == media_feature_names::kPrefersColorSchemeMediaFeature ||
         feature == media_feature_names::kPrefersReducedMotionMediaFeature;
}

std::string StandaloneMediaQueryDiagnosticsJson() {
  std::ostringstream json;
  json << "{\"queries\":[";
  const auto& traces = StandaloneMediaQueryEvaluationTraces();
  for (size_t i = 0; i < traces.size(); ++i) {
    if (i) {
      json << ",";
    }
    const auto& trace = traces[i];
    json << "{\"text\":\"(" << StandaloneJsonEscape(trace.feature);
    if (!trace.expected_value.empty()) {
      json << ": " << StandaloneJsonEscape(trace.expected_value);
    }
    json << ")\",\"parsed\":true"
         << ",\"evaluation_result\":"
         << (trace.result == "true"    ? "true"
             : trace.result == "false" ? "false"
                                        : "null")
         << ",\"features\":[{\"name\":"
         << StandaloneJsonString(trace.feature)
         << ",\"expected_value\":" << StandaloneJsonString(trace.expected_value)
         << ",\"actual_value\":" << StandaloneJsonString(trace.actual_value)
         << ",\"match\":"
         << (trace.result == "true"    ? "true"
             : trace.result == "false" ? "false"
                                        : "null")
         << "}],\"unsupported_features\":";
    if (trace.unsupported_reason.empty()) {
      json << "[]";
    } else {
      json << "[{\"name\":" << StandaloneJsonString(trace.feature)
           << ",\"reason\":" << StandaloneJsonString(trace.unsupported_reason)
           << "}]";
    }
    json << ",\"error\":\"\"}";
  }
  json << "]}";
  return json.str();
}

void StandaloneRecordMediaQueryEvaluation(const MediaQueryFeatureExpNode& node,
                                          KleeneValue result) {
  auto& traces = StandaloneMediaQueryEvaluationTraces();
  if (traces.size() >= 256) {
    return;
  }
  StandaloneMediaQueryEvaluationTrace trace;
  trace.feature = node.HasMediaFeature()
                      ? node.Name().Utf8()
                      : (node.IsCustomMedia() ? node.Name().Utf8()
                                              : "style-range");
  const MediaQueryExpBounds& bounds = node.Bounds();
  if (bounds.left.IsValid() && bounds.right.IsValid()) {
    trace.expected_value = bounds.left.value.CssText().Utf8() + " .. " +
                           bounds.right.value.CssText().Utf8();
  } else if (bounds.left.IsValid()) {
    trace.expected_value = bounds.left.value.CssText().Utf8();
  } else if (bounds.right.IsValid()) {
    trace.expected_value = bounds.right.value.CssText().Utf8();
  }
  if (trace.expected_value.empty()) {
    const auto& parsed_values = StandaloneMediaQueryParsedExpectedValues();
    const auto parsed = parsed_values.find(trace.feature);
    if (parsed != parsed_values.end()) {
      trace.expected_value = parsed->second;
    }
  }
  trace.actual_value =
      node.HasMediaFeature() ? StandaloneMediaQueryActualValue(node.Name())
                             : "unsupported_or_unknown";
  trace.result = StandaloneKleeneValueString(result);
  if (!node.HasMediaFeature() ||
      !StandaloneMediaQueryFeatureSupportedForDiagnostics(node.Name())) {
    trace.unsupported_reason =
        node.IsCustomMedia()
            ? "custom media is not supported by the standalone subset"
            : "feature is not in the current standalone static media subset";
  }
  traces.push_back(std::move(trace));
}
}  // namespace

extern "C" void StandaloneRendererResetMediaQueryDiagnostics() {
  StandaloneMediaQueryEvaluationTraces().clear();
  StandaloneMediaQueryParsedExpectedValues().clear();
}

extern "C" int StandaloneRendererMediaQueryDiagnosticsJsonSize() {
  static std::string* serialized = new std::string();
  *serialized = StandaloneMediaQueryDiagnosticsJson();
  return static_cast<int>(serialized->size());
}

extern "C" int StandaloneRendererMediaQueryDiagnosticsJson(char* buffer,
                                                           int buffer_size) {
  if (!buffer || buffer_size <= 0) {
    return 0;
  }
  const std::string serialized = StandaloneMediaQueryDiagnosticsJson();
  const int bytes_to_copy =
      std::min(static_cast<int>(serialized.size()), buffer_size - 1);
  if (bytes_to_copy <= 0) {
    buffer[0] = '\0';
    return 0;
  }
  std::memcpy(buffer, serialized.data(), static_cast<size_t>(bytes_to_copy));
  buffer[bytes_to_copy] = '\0';
  return bytes_to_copy;
}

extern "C" int StandaloneRendererMediaQueryDiagnosticCount() {
  return static_cast<int>(StandaloneMediaQueryEvaluationTraces().size());
}

extern "C" int StandaloneRendererMediaQueryDiagnosticFieldAt(int index,
                                                             int field,
                                                             char* buffer,
                                                             int buffer_size) {
  if (!buffer || buffer_size <= 0) {
    return 0;
  }
  const auto& traces = StandaloneMediaQueryEvaluationTraces();
  if (index < 0 || static_cast<size_t>(index) >= traces.size()) {
    buffer[0] = '\0';
    return 0;
  }
  const auto& trace = traces[static_cast<size_t>(index)];
  const std::string* value = &trace.feature;
  switch (field) {
    case 0:
      value = &trace.feature;
      break;
    case 1:
      value = &trace.expected_value;
      break;
    case 2:
      value = &trace.actual_value;
      break;
    case 3:
      value = &trace.result;
      break;
    case 4:
      value = &trace.unsupported_reason;
      break;
    default:
      buffer[0] = '\0';
      return 0;
  }
  const int bytes_to_copy =
      std::min(static_cast<int>(value->size()), buffer_size - 1);
  if (bytes_to_copy <= 0) {
    buffer[0] = '\0';
    return 0;
  }
  std::memcpy(buffer, value->data(), static_cast<size_t>(bytes_to_copy));
  buffer[bytes_to_copy] = '\0';
  return bytes_to_copy;
}

namespace {
int g_image_resource_content_fetch_called = 0;
int g_layout_image_set_resource_called = 0;
int g_layout_image_resource_initialize_called = 0;
int g_layout_image_resource_set_resource_called = 0;
int g_layout_image_resource_natural_dimensions_called = 0;
int g_layout_image_resource_get_image_called = 0;
int g_layout_image_resource_maybe_animated_called = 0;
int g_layout_image_resource_maybe_animated_null_image = 0;
int g_layout_image_paint_called = 0;
int g_layout_image_paint_replaced_called = 0;
int g_image_painter_paint_replaced_called = 0;
std::string g_image_resource_content_fetch_last_url;
}  // namespace

extern "C" void StandaloneRendererResetImageReachabilityDiagnostics() {
  g_image_resource_content_fetch_called = 0;
  g_layout_image_set_resource_called = 0;
  g_layout_image_resource_initialize_called = 0;
  g_layout_image_resource_set_resource_called = 0;
  g_layout_image_resource_natural_dimensions_called = 0;
  g_layout_image_resource_get_image_called = 0;
  g_layout_image_resource_maybe_animated_called = 0;
  g_layout_image_resource_maybe_animated_null_image = 0;
  g_layout_image_paint_called = 0;
  g_layout_image_paint_replaced_called = 0;
  g_image_painter_paint_replaced_called = 0;
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

extern "C" void StandaloneRendererNoteLayoutImageResourceMaybeAnimated(
    bool null_image) {
  ++g_layout_image_resource_maybe_animated_called;
  if (null_image)
    ++g_layout_image_resource_maybe_animated_null_image;
}

extern "C" void StandaloneRendererNoteLayoutImagePaint() {
  ++g_layout_image_paint_called;
}

extern "C" void StandaloneRendererNoteLayoutImagePaintReplaced() {
  ++g_layout_image_paint_replaced_called;
}

extern "C" void StandaloneRendererNoteImagePainterPaintReplaced() {
  ++g_image_painter_paint_replaced_called;
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

extern "C" int StandaloneRendererLayoutImageResourceMaybeAnimatedCalled() {
  return g_layout_image_resource_maybe_animated_called;
}

extern "C" int StandaloneRendererLayoutImageResourceMaybeAnimatedNullImage() {
  return g_layout_image_resource_maybe_animated_null_image;
}

extern "C" int StandaloneRendererLayoutImagePaintCalled() {
  return g_layout_image_paint_called;
}

extern "C" int StandaloneRendererLayoutImagePaintReplacedCalled() {
  return g_layout_image_paint_replaced_called;
}

extern "C" int StandaloneRendererImagePainterPaintReplacedCalled() {
  return g_image_painter_paint_replaced_called;
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
      event_loop_(base::AdoptRef(new scheduler::EventLoop(this, isolate, nullptr))),
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
  explicit StandaloneNoopAgentGroupScheduler(
      scheduler::WebThreadScheduler& main_thread_scheduler)
      : main_thread_scheduler_(&main_thread_scheduler) {}
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
    return *main_thread_scheduler_;
  }
  v8::Isolate* Isolate() override { return nullptr; }
  void OnUrgentMessageReceived() override {}
  void OnUrgentMessageProcessed() override {}

 private:
  raw_ptr<scheduler::WebThreadScheduler> main_thread_scheduler_;
};

class StandaloneNoopMainThreadScheduler final
    : public MainThreadScheduler,
      public scheduler::WebThreadScheduler {
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
  scoped_refptr<base::SingleThreadTaskRunner> DeprecatedDefaultTaskRunner()
      override {
    return StandaloneNoopTaskRunner();
  }
  base::TimeTicks MonotonicallyIncreasingVirtualTime() override {
    return base::TimeTicks::Now();
  }
  void AddTaskObserver(base::TaskObserver*) override {}
  void RemoveTaskObserver(base::TaskObserver*) override {}
  void SetV8Isolate(v8::Isolate*) override {}
  blink::MainThreadScheduler* ToMainThreadScheduler() override {
    return static_cast<blink::MainThreadScheduler*>(this);
  }
  std::unique_ptr<RendererPauseHandle> PauseScheduler() override {
    return std::make_unique<PauseHandle>();
  }
  scoped_refptr<base::SingleThreadTaskRunner> NonWakingTaskRunner() override {
    return StandaloneNoopTaskRunner();
  }
  AgentGroupScheduler* CreateAgentGroupScheduler() override {
    static Persistent<StandaloneNoopAgentGroupScheduler> scheduler;
    if (!scheduler) {
      scheduler = MakeGarbageCollected<StandaloneNoopAgentGroupScheduler>(
          static_cast<scheduler::WebThreadScheduler&>(*this));
    }
    return scheduler.Get();
  }
  std::unique_ptr<scheduler::WebAgentGroupScheduler>
  CreateWebAgentGroupScheduler() override {
    return nullptr;
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
    return this;
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
  bool CanRegister(const KURL&, HTMLElement*, bool = true);
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
const AtomicString kKeyboardEvent("KeyboardEvent");
const AtomicString kPageRevealEvent("PageRevealEvent");
const AtomicString kTextEvent("TextEvent");
const AtomicString kTransitionEvent("TransitionEvent");
const AtomicString kBeforeUnloadEvent("BeforeUnloadEvent");
}

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

void EventListenerMap::CopyEventListenersNotCreatedFromMarkupToTarget(
    EventTarget*) {}

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


namespace switches {
extern const char kDisableBlobUrlPartitioning[] =
    "disable-blob-url-partitioning";
}  // namespace switches


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

const WrapperTypeInfo& SVGAngleTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAngle");
const WrapperTypeInfo& SVGAnimatedLength::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedLength");
const WrapperTypeInfo& SVGAnimatedAngle::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedAngle");
const WrapperTypeInfo& SVGAnimatedEnumerationBase::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedEnumerationBase");
const WrapperTypeInfo& SVGAnimatedLengthList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedLengthList");
const WrapperTypeInfo& SVGAnimatedNumber::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedNumber");
const WrapperTypeInfo& SVGAnimatedNumberList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedNumberList");
const WrapperTypeInfo& SVGAnimatedPreserveAspectRatio::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedPreserveAspectRatio");
const WrapperTypeInfo& SVGAnimatedRect::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedRect");
const WrapperTypeInfo& SVGAnimatedString::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedString");
const WrapperTypeInfo& SVGAnimatedTransformList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGAnimatedTransformList");
const WrapperTypeInfo& SVGElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGElement");
const WrapperTypeInfo& SVGGeometryElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGGeometryElement");
const WrapperTypeInfo& SVGGraphicsElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGGraphicsElement");
const WrapperTypeInfo& SVGCircleElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGCircleElement");
const WrapperTypeInfo& SVGFilterElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGFilterElement");
const WrapperTypeInfo& SVGFEImageElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGFEImageElement");
const WrapperTypeInfo& SVGImageElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGImageElement");
const WrapperTypeInfo& SVGDescElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGDescElement");
const WrapperTypeInfo& SVGLineElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGLineElement");
const WrapperTypeInfo& SVGMarkerElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGMarkerElement");
const WrapperTypeInfo& SVGPathElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGPathElement");
const WrapperTypeInfo& SVGLengthListTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGLengthList");
const WrapperTypeInfo& SVGLengthTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGLength");
const WrapperTypeInfo& SVGMatrixTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGMatrix");
const WrapperTypeInfo& SVGNumberListTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGNumberList");
const WrapperTypeInfo& SVGNumberTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGNumber");
const WrapperTypeInfo& SVGPointTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGPoint");
const WrapperTypeInfo& SVGPreserveAspectRatioTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGPreserveAspectRatio");
const WrapperTypeInfo& SVGRectTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGRect");
const WrapperTypeInfo& SVGRectElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGRectElement");
const WrapperTypeInfo& SVGSVGElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGSVGElement");
const WrapperTypeInfo& SVGTextContentElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGTextContentElement");
const WrapperTypeInfo& SVGTextPositioningElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGTextPositioningElement");
const WrapperTypeInfo& SVGTextElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGTextElement");
const WrapperTypeInfo& SVGTitleElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGTitleElement");
const WrapperTypeInfo& SVGStringListTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGStringList");
const WrapperTypeInfo& SVGTransformListTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGTransformList");
const WrapperTypeInfo& SVGTransformTearOff::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGTransform");
const WrapperTypeInfo& SVGUseElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("SVGUseElement");
const WrapperTypeInfo& TrustedScriptURL::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TrustedScriptURL");

const WrapperTypeInfo& HTMLBRElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLBRElement");
const WrapperTypeInfo& HTMLBaseElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLBaseElement");
const WrapperTypeInfo& HTMLBodyElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLBodyElement");
const WrapperTypeInfo& HTMLDivElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLDivElement");
const WrapperTypeInfo& HTMLFormElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLFormElement");
const WrapperTypeInfo& HTMLImageElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLImageElement");
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
const WrapperTypeInfo& HTMLInputElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLInputElement");
const WrapperTypeInfo& HTMLLabelElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLLabelElement");
const WrapperTypeInfo& HTMLTextAreaElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTextAreaElement");
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
const WrapperTypeInfo& HTMLTableCaptionElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTableCaptionElement");
const WrapperTypeInfo& HTMLTableCellElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTableCellElement");
const WrapperTypeInfo& HTMLTableColElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTableColElement");
const WrapperTypeInfo& HTMLTableElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTableElement");
const WrapperTypeInfo& HTMLTableRowElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTableRowElement");
const WrapperTypeInfo& HTMLTableSectionElement::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("HTMLTableSectionElement");
const WrapperTypeInfo& MediaList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("MediaList");
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
const WrapperTypeInfo& MouseEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("MouseEvent");
const WrapperTypeInfo& KeyboardEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("KeyboardEvent");
const WrapperTypeInfo& TextEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TextEvent");
const WrapperTypeInfo& PointerEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("PointerEvent");
const WrapperTypeInfo& DragEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DragEvent");
const WrapperTypeInfo& WheelEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("WheelEvent");
const WrapperTypeInfo& Touch::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("Touch");
const WrapperTypeInfo& TouchList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TouchList");
const WrapperTypeInfo& InputDeviceCapabilities::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("InputDeviceCapabilities");
const WrapperTypeInfo& DataTransfer::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("DataTransfer");
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

bool StandaloneDomTraceEnabled() {
  const char* value = std::getenv("HTML_CSS_RENDERER_TRACE_DOM");
  return value && value[0] && value[0] != '0';
}

void TraceStandaloneHtmlFactory(const AtomicString& local_name,
                                const char* stage) {
  if (!StandaloneDomTraceEnabled()) {
    return;
  }
  std::fprintf(stderr, "standalone_dom.factory.%s=%s\n", stage,
               local_name.GetString().Utf8().c_str());
  std::fflush(stderr);
}

extern "C" int g_standalone_html_factory_create_html_count;
extern "C" int g_standalone_html_factory_create_body_count;

HTMLElement* HTMLElementFactory::Create(const AtomicString& local_name,
                                        Document& document,
                                        const CreateElementFlags flags) {
  TraceStandaloneHtmlFactory(local_name, "before");
  if (local_name == html_names::kHTMLTag.LocalName()) {
    ++g_standalone_html_factory_create_html_count;
    HTMLElement* element = MakeGarbageCollected<HTMLHtmlElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kHeadTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLHeadElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kBodyTag.LocalName()) {
    ++g_standalone_html_factory_create_body_count;
    HTMLElement* element = MakeGarbageCollected<HTMLBodyElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kImgTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLImageElement>(document, flags);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kFormTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLFormElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kLabelTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLLabelElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
  if (local_name == html_names::kInputTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLInputElement>(document, flags);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTextareaTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTextAreaElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
#endif
#if HTML_CSS_RENDERER_STANDALONE_SELECT_CONTROL
  if (local_name == html_names::kSelectTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLSelectElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kOptionTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLOptionElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kOptgroupTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLOptGroupElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
#endif
  if (local_name == html_names::kTitleTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTitleElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kBrTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLBRElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kDivTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLDivElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kH1Tag.LocalName() ||
      local_name == html_names::kH2Tag.LocalName() ||
      local_name == html_names::kH3Tag.LocalName() ||
      local_name == html_names::kH4Tag.LocalName() ||
      local_name == html_names::kH5Tag.LocalName() ||
      local_name == html_names::kH6Tag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLHeadingElement>(
        QualifiedName(g_null_atom, local_name, html_names::xhtmlNamespaceURI),
        document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kLiTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLLIElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kOlTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLOListElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kPTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLParagraphElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kUlTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLUListElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTableTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTableElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kCaptionTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLTableCaptionElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kColTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLTableColElement>(html_names::kColTag,
                                                  document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kColgroupTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLTableColElement>(html_names::kColgroupTag,
                                                  document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTbodyTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTableSectionElement>(
        html_names::kTbodyTag, document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTheadTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTableSectionElement>(
        html_names::kTheadTag, document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTfootTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTableSectionElement>(
        html_names::kTfootTag, document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTrTag.LocalName()) {
    HTMLElement* element = MakeGarbageCollected<HTMLTableRowElement>(document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kTdTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLTableCellElement>(html_names::kTdTag,
                                                   document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  if (local_name == html_names::kThTag.LocalName()) {
    HTMLElement* element =
        MakeGarbageCollected<HTMLTableCellElement>(html_names::kThTag,
                                                   document);
    TraceStandaloneHtmlFactory(local_name, "after");
    return element;
  }
  QualifiedName tag_name(g_null_atom, local_name,
                         html_names::xhtmlNamespaceURI);
  HTMLElement* element = MakeGarbageCollected<HTMLElement>(tag_name, document);
  TraceStandaloneHtmlFactory(local_name, "after");
  return element;
}

SVGElement* SVGElementFactory::Create(const AtomicString& local_name,
                                      Document& document,
                                      const CreateElementFlags) {
  if (local_name == svg_names::kSVGTag.LocalName())
    return MakeGarbageCollected<SVGSVGElement>(document);
  if (local_name == svg_names::kRectTag.LocalName())
    return MakeGarbageCollected<SVGRectElement>(document);
  if (local_name == svg_names::kCircleTag.LocalName())
    return MakeGarbageCollected<SVGCircleElement>(document);
  if (local_name == svg_names::kLineTag.LocalName())
    return MakeGarbageCollected<SVGLineElement>(document);
  if (local_name == svg_names::kPathTag.LocalName())
    return MakeGarbageCollected<SVGPathElement>(document);
  if (local_name == svg_names::kTextTag.LocalName())
    return MakeGarbageCollected<SVGTextElement>(document);
  if (local_name == svg_names::kTitleTag.LocalName())
    return MakeGarbageCollected<SVGTitleElement>(document);
  if (local_name == svg_names::kDescTag.LocalName())
    return MakeGarbageCollected<SVGDescElement>(document);
  return nullptr;
}

void SVGMPathElement::TargetPathChanged() {}

bool LcppScriptObserverEnabled() {
  return false;
}

HashSet<String> LCPScriptObserver::GetExecutingScriptUrls() {
  return HashSet<String>();
}

ImageCandidate BestFitSourceForImageAttributes(float,
                                               float,
                                               const String& src_attribute,
                                               const String&,
                                               Document*) {
  if (src_attribute.empty()) {
    return ImageCandidate();
  }
  DescriptorParsingResult result;
  result.SetDensity(1.0f);
  return ImageCandidate(src_attribute, 0, src_attribute.length(), result,
                        ImageCandidate::kSrcOrigin);
}

ImageCandidate BestFitSourceForSrcsetAttribute(float,
                                               float,
                                               const String&,
                                               Document*) {
  return ImageCandidate();
}

String BestFitSourceForImageAttributes(float,
                                       float,
                                       const String& src_attribute,
                                       ImageCandidate& srcset_image_candidate) {
  srcset_image_candidate = ImageCandidate();
  return src_attribute;
}

void HTMLFormElement::Associate(HTMLImageElement&) {}
void HTMLFormElement::Disassociate(HTMLImageElement&) {}
void MediaQueryMatcher::AddViewportListener(MediaQueryListListener*) {}
void MediaQueryMatcher::RemoveViewportListener(MediaQueryListListener*) {}
LoadingAttributeValue GetLoadingAttributeValue(const String&) {
  return LoadingAttributeValue::kAuto;
}
Image::ImageDecodingMode ImageElementBase::ParseImageDecodingMode(
    const AtomicString&) {
  return Image::kSyncDecode;
}
Image::ImageDecodingMode ImageElementBase::GetDecodingModeForPainting(
    PaintImage::Id) {
  return decoding_mode_;
}
CrossOriginAttributeValue GetCrossOriginAttributeValue(const String&) {
  return kCrossOriginAttributeNotSet;
}
ContentType::ContentType(const String& type) : type_(type) {}
String ContentType::GetType() const {
  return type_;
}
bool HTMLSourceElement::MediaQueryMatches() const {
  return false;
}
void HTMLPictureElement::AddListenerToSourceChildren() {}
void HTMLPictureElement::RemoveListenerFromSourceChildren() {}

void HTMLFormElement::DidAssociateByParser() {}

MediaValues* MediaValuesDynamic::Create(Document& document) {
  return MediaValuesDynamic::Create(document.GetFrame());
}

MediaValues* MediaValuesDynamic::Create(LocalFrame* frame) {
  if (!frame || !frame->View() || !frame->GetDocument()) {
    if (frame && frame->GetDocument()) {
      return MakeGarbageCollected<MediaValuesCached>(*frame->GetDocument());
    }
    return MakeGarbageCollected<MediaValuesCached>();
  }
  return MakeGarbageCollected<MediaValuesDynamic>(frame);
}

SizesAttributeParser::SizesAttributeParser(MediaValues*,
                                           const String&,
                                           ExecutionContext*,
                                           const HTMLImageElement*) {}

bool SizesAttributeParser::IsAuto() {
  return false;
}

float SizesAttributeParser::Size() {
  return 100.0f;
}

mojom::blink::FetchPriorityHint GetFetchPriorityAttributeValue(
    const String&) {
  return mojom::blink::FetchPriorityHint::kAuto;
}

DocumentImageReplacements* DocumentImageReplacements::FromIfExists(
    Document&) {
  return nullptr;
}

ImageReplacement* DocumentImageReplacements::GetImageReplacement(
    HTMLImageElement*) const {
  return nullptr;
}

void ImageReplacement::ResetImageReplacement(base::PassKey<HTMLImageElement>,
                                             HTMLImageElement&,
                                             Document&) {}

void ImageReplacement::CreateImageReplacementShadowTree(
    base::PassKey<HTMLImageElement>,
    HTMLImageElement&) {}

bool ImageReplacement::ResumeReplacementAfterImageLoad() {
  return false;
}

MediaQueryListListener::MediaQueryListListener() = default;

void HTMLSourceElement::Trace(Visitor* visitor) const {
  HTMLElement::Trace(visitor);
}

LayoutImageReplacement::LayoutImageReplacement(HTMLImageElement* element)
    : LayoutImage(element) {}
LayoutImageReplacement::~LayoutImageReplacement() = default;
void LayoutImageReplacement::Trace(Visitor* visitor) const {
  LayoutImage::Trace(visitor);
}
bool LayoutImageReplacement::IsChildAllowed(LayoutObject*,
                                            const ComputedStyle&) const {
  return false;
}
void LayoutImageReplacement::PaintReplaced(
    const PaintInfo&,
    const PhysicalOffset&) const {}

scoped_refptr<Image> ImageElementBase::GetSourceImageForCanvas(
    SourceImageStatus* status,
    const gfx::SizeF&) {
  if (status) {
    *status = kIncompleteSourceImageStatus;
  }
  return nullptr;
}

bool ImageElementBase::WouldTaintOrigin() const {
  return false;
}

bool ImageElementBase::IsImageElement() const {
  return true;
}

gfx::SizeF ImageElementBase::ElementSize(
    const gfx::SizeF& default_object_size,
    const RespectImageOrientationEnum) const {
  return default_object_size;
}

gfx::SizeF ImageElementBase::DefaultDestinationSize(
    const gfx::SizeF& default_object_size,
    const RespectImageOrientationEnum) const {
  return default_object_size;
}

const KURL& ImageElementBase::SourceURL() const {
  static KURL* url = new KURL();
  return *url;
}

bool ImageElementBase::IsOpaque() const {
  return false;
}

bool ImageElementBase::IsAccelerated() const {
  return false;
}

ImageBitmapSourceStatus ImageElementBase::CheckUsability() const {
  return base::ok();
}

ScriptPromise<ImageBitmap> ImageElementBase::CreateImageBitmap(
    ScriptState*,
    std::optional<gfx::Rect>,
    const ImageBitmapOptions*,
    ExceptionState&) {
  return ScriptPromise<ImageBitmap>();
}

ScriptPromise<ImageBitmap> ImageBitmapSource::CreateImageBitmap(
    ScriptState*,
    std::optional<gfx::Rect>,
    const ImageBitmapOptions*,
    ExceptionState&) {
  return ScriptPromise<ImageBitmap>();
}

void HTMLObjectElement::RenderFallbackContent(
    HTMLObjectElement::ErrorEventPolicy) {}

void ScriptPromiseResolverBase::Reject(DOMException*) {}

void ImageElementTiming::NotifyImagePainted(
    const LayoutObject&,
    const ImageResourceContent&,
    const PropertyTreeStateOrAlias&,
    const gfx::Rect&) {}

bool PaintTimingDetector::NotifyImagePaint(
    const LayoutObject&,
    const gfx::Size&,
    const MediaTiming&,
    const PropertyTreeStateOrAlias&,
    const gfx::Rect&) {
  return false;
}

Color HighlightStyleUtils::HighlightBackgroundColor(
    const Document&,
    const ComputedStyle&,
    Node*,
    std::optional<Color>,
    PseudoId,
    bool,
    SearchTextIsActiveMatch) {
  return Color::kTransparent;
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

FrameLoadRequest::FrameLoadRequest(LocalDOMWindow* origin_window,
                                   const ResourceRequest&)
    : origin_window_(origin_window),
      should_send_referrer_(kMaybeSendReferrer),
      creation_time_(base::TimeTicks::Now()) {}

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

bool UIEventWithKeyState::new_tab_modifier_set_from_isolated_world_ = false;

UIEventWithKeyState::UIEventWithKeyState(
    const AtomicString& type,
    Bubbles bubbles,
    Cancelable cancelable,
    AbstractView* view,
    int detail,
    WebInputEvent::Modifiers modifiers,
    base::TimeTicks platform_time_stamp,
    InputDeviceCapabilities* source_capabilities)
    : UIEvent(type,
              bubbles,
              cancelable,
              ComposedMode::kComposed,
              platform_time_stamp,
              view,
              detail,
              source_capabilities),
      modifiers_(modifiers) {}

UIEventWithKeyState::UIEventWithKeyState(
    const AtomicString& type,
    const EventModifierInit* initializer,
    base::TimeTicks platform_time_stamp)
    : UIEvent(type,
              initializer && initializer->bubbles() ? Bubbles::kYes
                                                    : Bubbles::kNo,
              initializer && initializer->cancelable() ? Cancelable::kYes
                                                       : Cancelable::kNo,
              initializer && initializer->composed()
                  ? ComposedMode::kComposed
                  : ComposedMode::kScoped,
              platform_time_stamp,
              initializer ? initializer->view() : nullptr,
              initializer ? initializer->detail() : 0,
              initializer ? initializer->sourceCapabilities() : nullptr),
      modifiers_(0) {
  if (initializer) {
    InitModifiers(initializer->ctrlKey(), initializer->altKey(),
                  initializer->shiftKey(), initializer->metaKey());
  }
}

void UIEventWithKeyState::DidCreateEventInIsolatedWorld(bool,
                                                        bool,
                                                        bool,
                                                        bool) {}

void UIEventWithKeyState::SetFromWebInputEventModifiers(
    EventModifierInit* initializer,
    WebInputEvent::Modifiers modifiers) {
  if (!initializer) {
    return;
  }
  initializer->setCtrlKey(modifiers & WebInputEvent::kControlKey);
  initializer->setShiftKey(modifiers & WebInputEvent::kShiftKey);
  initializer->setAltKey(modifiers & WebInputEvent::kAltKey);
  initializer->setMetaKey(modifiers & WebInputEvent::kMetaKey);
}

bool UIEventWithKeyState::getModifierState(const String&) const {
  return false;
}

const UIEventWithKeyState* FindEventWithKeyState(const Event*) {
  return nullptr;
}

UIEventTiming::UIEventTiming(LocalFrame*, const Event&) {}

TextEvent* TextEvent::Create() {
  return MakeGarbageCollected<TextEvent>();
}

TextEvent* TextEvent::Create(AbstractView* view,
                             const String& data,
                             TextEventInputType input_type) {
  return MakeGarbageCollected<TextEvent>(view, data, input_type);
}

TextEvent* TextEvent::CreateForPlainTextPaste(AbstractView* view,
                                              const String& data,
                                              bool should_smart_replace) {
  return MakeGarbageCollected<TextEvent>(view, data, nullptr,
                                         should_smart_replace, false);
}

TextEvent* TextEvent::CreateForFragmentPaste(
    AbstractView* view,
    DocumentFragment* data,
    bool should_smart_replace,
    bool should_match_style,
    DataTransfer* data_transfer) {
  return MakeGarbageCollected<TextEvent>(
      view, String(), data, should_smart_replace, should_match_style,
      data_transfer);
}

TextEvent* TextEvent::CreateForDrop(AbstractView* view, const String& data) {
  return MakeGarbageCollected<TextEvent>(view, data, kTextEventInputDrop);
}

TextEvent::TextEvent()
    : input_type_(kTextEventInputKeyboard),
      pasting_fragment_(nullptr),
      data_transfer_(nullptr),
      should_smart_replace_(false),
      should_match_style_(false) {}

TextEvent::TextEvent(AbstractView* view,
                     const String& data,
                     TextEventInputType input_type)
    : UIEvent(event_type_names::kTextInput,
              Bubbles::kYes,
              Cancelable::kYes,
              ComposedMode::kComposed,
              base::TimeTicks::Now(),
              view,
              0,
              nullptr),
      input_type_(input_type),
      data_(data),
      pasting_fragment_(nullptr),
      data_transfer_(nullptr),
      should_smart_replace_(false),
      should_match_style_(false) {}

TextEvent::TextEvent(AbstractView* view,
                     const String& data,
                     DocumentFragment* pasting_fragment,
                     bool should_smart_replace,
                     bool should_match_style,
                     DataTransfer* data_transfer)
    : UIEvent(event_type_names::kTextInput,
              Bubbles::kYes,
              Cancelable::kYes,
              ComposedMode::kComposed,
              base::TimeTicks::Now(),
              view,
              0,
              nullptr),
      input_type_(kTextEventInputPaste),
      data_(data),
      pasting_fragment_(pasting_fragment),
      data_transfer_(data_transfer),
      should_smart_replace_(should_smart_replace),
      should_match_style_(should_match_style) {}

TextEvent::~TextEvent() = default;

void TextEvent::initTextEvent(const AtomicString& type,
                              bool bubbles,
                              bool cancelable,
                              AbstractView* view,
                              const String& data) {
  initUIEvent(type, bubbles, cancelable, view, 0);
  data_ = data;
}

const AtomicString& TextEvent::InterfaceName() const {
  return event_interface_names::kTextEvent;
}

void TextEvent::Trace(Visitor* visitor) const {
  UIEvent::Trace(visitor);
  visitor->Trace(pasting_fragment_);
  visitor->Trace(data_transfer_);
}

void UIEventWithKeyState::InitModifiers(bool ctrl_key,
                                        bool alt_key,
                                        bool shift_key,
                                        bool meta_key) {
  modifiers_ = 0;
  if (ctrl_key) {
    modifiers_ |= WebInputEvent::kControlKey;
  }
  if (alt_key) {
    modifiers_ |= WebInputEvent::kAltKey;
  }
  if (shift_key) {
    modifiers_ |= WebInputEvent::kShiftKey;
  }
  if (meta_key) {
    modifiers_ |= WebInputEvent::kMetaKey;
  }
}

MouseEvent::MouseEvent()
    : UIEventWithKeyState(),
      position_type_(PositionType::kPosition),
      button_(-1),
      buttons_(0),
      synthetic_event_type_(kRealOrIndistinguishable),
      menu_source_type_(ui::mojom::blink::MenuSourceType::kNone) {}

MouseEvent* MouseEvent::Create(
    const AtomicString& event_type,
    const MouseEventInit* initializer,
    base::TimeTicks platform_time_stamp,
    SyntheticEventType synthetic_event_type,
    ui::mojom::blink::MenuSourceType menu_source_type) {
  return MakeGarbageCollected<MouseEvent>(
      event_type, initializer, platform_time_stamp, synthetic_event_type,
      menu_source_type);
}

MouseEvent* MouseEvent::Create(ScriptState*,
                               const AtomicString& event_type,
                               const MouseEventInit* initializer) {
  return Create(event_type, initializer, base::TimeTicks::Now(),
                kRealOrIndistinguishable,
                ui::mojom::blink::MenuSourceType::kNone);
}

MouseEvent::MouseEvent(const AtomicString& event_type,
                       const MouseEventInit* initializer,
                       base::TimeTicks platform_time_stamp,
                       SyntheticEventType synthetic_event_type,
                       ui::mojom::blink::MenuSourceType menu_source_type,
                       LocalDOMWindow* fallback_dom_window)
    : UIEventWithKeyState(event_type, initializer, platform_time_stamp),
      screen_x_(initializer ? initializer->screenX() : 0),
      screen_y_(initializer ? initializer->screenY() : 0),
      movement_delta_(initializer ? initializer->movementX() : 0,
                      initializer ? initializer->movementY() : 0),
      position_type_(synthetic_event_type == kPositionless
                         ? PositionType::kPositionless
                         : PositionType::kPosition),
      button_(initializer ? initializer->button() : -1),
      buttons_(initializer ? initializer->buttons() : 0),
      related_target_(initializer ? initializer->relatedTarget() : nullptr),
      synthetic_event_type_(synthetic_event_type),
      menu_source_type_(menu_source_type) {
  if (initializer) {
    InitCoordinates(initializer->clientX(), initializer->clientY(),
                    fallback_dom_window);
  }
}

void MouseEvent::InitCoordinates(const double client_x,
                                 const double client_y,
                                 const LocalDOMWindow*) {
  client_x_ = client_x;
  client_y_ = client_y;
  page_x_ = client_x;
  page_y_ = client_y;
  absolute_location_ = gfx::PointF(client_x, client_y);
  layer_location_ = gfx::PointF(client_x, client_y);
  offset_x_ = client_x;
  offset_y_ = client_y;
  has_cached_relative_position_ = true;
}

void MouseEvent::InitCoordinatesForTesting(double screen_x,
                                           double screen_y,
                                           double client_x,
                                           double client_y) {
  screen_x_ = screen_x;
  screen_y_ = screen_y;
  InitCoordinates(client_x, client_y);
}

uint16_t MouseEvent::WebInputEventModifiersToButtons(unsigned modifiers) {
  uint16_t buttons = 0;
  if (modifiers & WebInputEvent::kLeftButtonDown) {
    buttons |= 1;
  }
  if (modifiers & WebInputEvent::kRightButtonDown) {
    buttons |= 2;
  }
  if (modifiers & WebInputEvent::kMiddleButtonDown) {
    buttons |= 4;
  }
  return buttons;
}

void MouseEvent::initMouseEvent(ScriptState*,
                                const AtomicString& type,
                                bool bubbles,
                                bool cancelable,
                                AbstractView* view,
                                int detail,
                                int screen_x,
                                int screen_y,
                                int client_x,
                                int client_y,
                                bool ctrl_key,
                                bool alt_key,
                                bool shift_key,
                                bool meta_key,
                                int16_t button,
                                EventTarget* related_target,
                                uint16_t buttons) {
  initEvent(type, bubbles, cancelable);
  initUIEvent(type, bubbles, cancelable, view, detail);
  InitModifiers(ctrl_key, alt_key, shift_key, meta_key);
  screen_x_ = screen_x;
  screen_y_ = screen_y;
  InitCoordinates(client_x, client_y);
  button_ = button;
  buttons_ = buttons;
  related_target_ = related_target;
  position_type_ = PositionType::kPosition;
  synthetic_event_type_ = kRealOrIndistinguishable;
  menu_source_type_ = ui::mojom::blink::MenuSourceType::kNone;
}

void MouseEvent::SetCoordinatesFromWebPointerProperties(
    const WebPointerProperties& web_pointer_properties,
    const LocalDOMWindow*,
    MouseEventInit* initializer) {
  if (!initializer) {
    return;
  }
  initializer->setScreenX(web_pointer_properties.PositionInScreen().x());
  initializer->setScreenY(web_pointer_properties.PositionInScreen().y());
  initializer->setClientX(web_pointer_properties.PositionInWidget().x());
  initializer->setClientY(web_pointer_properties.PositionInWidget().y());
  if (web_pointer_properties.is_raw_movement_event) {
    initializer->setMovementX(web_pointer_properties.movement_x);
    initializer->setMovementY(web_pointer_properties.movement_y);
  }
}

const AtomicString& MouseEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}

bool MouseEvent::IsMouseEvent() const {
  return true;
}

int16_t MouseEvent::button() const {
  return button_;
}

bool MouseEvent::IsLeftButton() const {
  return button_ == 0;
}

bool MouseEvent::IsLinkClickButton() const {
  return IsLeftButton();
}

unsigned MouseEvent::which() const {
  if (button_ < 0) {
    return 0;
  }
  return static_cast<unsigned>(button_) + 1;
}

Node* MouseEvent::toElement() const {
  return RawTarget() ? RawTarget()->ToNode() : nullptr;
}

Node* MouseEvent::fromElement() const {
  return related_target_ ? related_target_->ToNode() : nullptr;
}

void MouseEvent::Trace(Visitor* visitor) const {
  UIEvent::Trace(visitor);
  visitor->Trace(related_target_);
}

DispatchEventResult MouseEvent::DispatchEvent(EventDispatcher& dispatcher) {
  return dispatcher.Dispatch();
}

PointerEvent::PointerEvent(
    const AtomicString& type,
    const PointerEventInit* initializer,
    base::TimeTicks platform_time_stamp,
    MouseEvent::SyntheticEventType synthetic_event_type,
    ui::mojom::blink::MenuSourceType menu_source_type,
    bool prevent_counting_as_interaction)
    : MouseEvent(type,
                 initializer,
                 platform_time_stamp,
                 synthetic_event_type,
                 menu_source_type),
      pointer_id_(initializer ? initializer->pointerId() : 0),
      width_(initializer ? initializer->width() : 1),
      height_(initializer ? initializer->height() : 1),
      pressure_(initializer ? initializer->pressure() : 0),
      tilt_x_(initializer ? initializer->getTiltXOr(0) : 0),
      tilt_y_(initializer ? initializer->getTiltYOr(0) : 0),
      azimuth_angle_(initializer ? initializer->getAzimuthAngleOr(0) : 0),
      altitude_angle_(initializer ? initializer->getAltitudeAngleOr(0) : 0),
      tangential_pressure_(initializer ? initializer->tangentialPressure() : 0),
      twist_(initializer ? initializer->twist() : 0),
      pointer_type_(initializer ? initializer->pointerType() : String()),
      is_primary_(initializer ? initializer->isPrimary() : false),
      persistent_device_id_(initializer ? initializer->persistentDeviceId() : 0),
      prevent_counting_as_interaction_(prevent_counting_as_interaction) {}

PointerId PointerEvent::pointerIdForBindings() const {
  return pointer_id_;
}

bool PointerEvent::IsMouseEvent() const {
  return type() == event_type_names::kClick ||
         type() == event_type_names::kAuxclick ||
         type() == event_type_names::kContextmenu;
}

bool PointerEvent::IsPointerEvent() const {
  return true;
}

double PointerEvent::offsetX() const {
  return MouseEvent::offsetX();
}

double PointerEvent::offsetY() const {
  return MouseEvent::offsetY();
}

void PointerEvent::ReceivedTarget() {
  MouseEvent::ReceivedTarget();
}

Node* PointerEvent::fromElement() const {
  return nullptr;
}

Node* PointerEvent::toElement() const {
  return nullptr;
}

HeapVector<Member<PointerEvent>> PointerEvent::getCoalescedEvents() {
  return coalesced_events_;
}

HeapVector<Member<PointerEvent>> PointerEvent::getPredictedEvents() {
  return predicted_events_;
}

base::TimeTicks PointerEvent::OldestPlatformTimeStamp() const {
  return PlatformTimeStamp();
}

DispatchEventResult PointerEvent::DispatchEvent(EventDispatcher& dispatcher) {
  if (type().empty()) {
    return DispatchEventResult::kNotCanceled;
  }
  if (isTrusted()) {
    for (const auto& coalesced_event : coalesced_events_) {
      coalesced_event->SetTarget(&dispatcher.GetNode());
    }
    for (const auto& predicted_event : predicted_events_) {
      predicted_event->SetTarget(&dispatcher.GetNode());
    }
  }
  if (type() == event_type_names::kClick) {
    return MouseEvent::DispatchEvent(dispatcher);
  }
  return dispatcher.Dispatch();
}

Document* PointerEvent::GetDocument() const {
  if (auto* local_dom_window = DynamicTo<LocalDOMWindow>(view())) {
    return local_dom_window->document();
  }
  return nullptr;
}

bool PointerEvent::ShouldHaveIntegerCoordinates() const {
  return type() == event_type_names::kClick ||
         type() == event_type_names::kAuxclick ||
         type() == event_type_names::kContextmenu;
}

void PointerEvent::Trace(Visitor* visitor) const {
  MouseEvent::Trace(visitor);
  visitor->Trace(coalesced_events_);
  visitor->Trace(predicted_events_);
}

DragEvent::DragEvent()
    : MouseEvent(), data_transfer_(nullptr) {}

DragEvent::DragEvent(const AtomicString& type,
                     const DragEventInit* initializer,
                     base::TimeTicks platform_time_stamp,
                     SyntheticEventType synthetic_event_type)
    : MouseEvent(type, initializer, platform_time_stamp, synthetic_event_type,
                 ui::mojom::blink::MenuSourceType::kNone),
      data_transfer_(initializer ? initializer->dataTransfer() : nullptr) {}

bool DragEvent::IsDragEvent() const {
  return true;
}

bool DragEvent::IsMouseEvent() const {
  return false;
}

DispatchEventResult DragEvent::DispatchEvent(EventDispatcher& dispatcher) {
  return dispatcher.Dispatch();
}

void DragEvent::Trace(Visitor* visitor) const {
  MouseEvent::Trace(visitor);
  visitor->Trace(data_transfer_);
}

WheelEvent* WheelEvent::Create(const WebMouseWheelEvent& native_event,
                               LocalDOMWindow& window) {
  return MakeGarbageCollected<WheelEvent>(native_event, window);
}

WheelEvent* WheelEvent::Create(const WebMouseWheelEvent& native_event,
                               const gfx::Vector2dF& delta_in_pixels,
                               LocalDOMWindow& window) {
  return MakeGarbageCollected<WheelEvent>(native_event, delta_in_pixels,
                                          window);
}

WheelEvent::WheelEvent()
    : MouseEvent(),
      delta_x_(0),
      delta_y_(0),
      delta_z_(0),
      delta_mode_(kDomDeltaPixel) {}

WheelEvent::WheelEvent(const AtomicString&, const WheelEventInit*)
    : WheelEvent() {}

WheelEvent::WheelEvent(const WebMouseWheelEvent& native_event,
                       LocalDOMWindow& window)
    : WheelEvent(native_event,
                 gfx::Vector2dF(-native_event.delta_x, -native_event.delta_y),
                 window) {}

WheelEvent::WheelEvent(const WebMouseWheelEvent& native_event,
                       const gfx::Vector2dF& delta_in_pixels,
                       LocalDOMWindow&)
    : MouseEvent(),
      wheel_delta_(static_cast<int>(native_event.wheel_ticks_x *
                                    kTickMultiplier),
                   static_cast<int>(native_event.wheel_ticks_y *
                                    kTickMultiplier)),
      delta_x_(delta_in_pixels.x()),
      delta_y_(delta_in_pixels.y()),
      delta_z_(0),
      delta_mode_(kDomDeltaPixel),
      native_event_(native_event) {}

const AtomicString& WheelEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}

bool WheelEvent::IsMouseEvent() const {
  return false;
}

bool WheelEvent::IsWheelEvent() const {
  return true;
}

void WheelEvent::preventDefault() {
  Event::preventDefault();
}

DispatchEventResult WheelEvent::DispatchEvent(EventDispatcher& dispatcher) {
  return dispatcher.Dispatch();
}

void WheelEvent::Trace(Visitor* visitor) const {
  MouseEvent::Trace(visitor);
}

namespace {

float StandaloneLayoutZoomFactor(const LocalDOMWindow* local_dom_window) {
  if (!local_dom_window)
    return 1.f;
  LocalFrame* frame = local_dom_window->GetFrame();
  if (!frame)
    return 1.f;
  return frame->LayoutZoomFactor();
}

const LayoutObject* StandaloneFindTargetLayoutObject(Node*& target_node) {
  LayoutObject* layout_object = target_node->GetLayoutObject();
  if (!layout_object || !layout_object->IsSVG())
    return layout_object;
  while (!layout_object->IsSVGRoot())
    layout_object = layout_object->Parent();
  target_node = layout_object->GetNode();
  auto* svg_element = DynamicTo<SVGElement>(target_node);
  DCHECK(!target_node ||
         (svg_element && svg_element->IsOutermostSVGSVGElement()));
  return layout_object;
}

float StandaloneFrameScale(const LocalFrameView* frame_view) {
  float scale = 1;
  if (frame_view) {
    LocalFrameView* root_view = frame_view->GetFrame().LocalFrameRoot().View();
    if (root_view)
      scale = root_view->InputEventsScaleFactor();
  }
  return scale;
}

gfx::Vector2dF StandaloneFrameTranslation(const LocalFrameView* frame_view) {
  gfx::Point visual_viewport;
  if (frame_view) {
    LocalFrameView* root_view = frame_view->GetFrame().LocalFrameRoot().View();
    if (root_view && root_view->GetPage()) {
      visual_viewport = gfx::ToFlooredPoint(
          root_view->GetPage()->GetVisualViewport().VisibleRect().origin());
    }
  }
  return visual_viewport.OffsetFromOrigin();
}

}  // namespace

void MouseEvent::ReceivedTarget() {
  has_cached_relative_position_ = false;
}

void MouseEvent::ComputeRelativePosition() {
  Node* target_node = RawTarget() ? RawTarget()->ToNode() : nullptr;
  if (!target_node)
    return;

  offset_x_ = page_x_;
  offset_y_ = page_y_;
  layer_location_ = gfx::PointF(page_x_, page_y_);

  LocalDOMWindow* dom_window_for_zoom_factor =
      DynamicTo<LocalDOMWindow>(view());
  if (!dom_window_for_zoom_factor)
    dom_window_for_zoom_factor = target_node->GetDocument().domWindow();

  float zoom_factor = StandaloneLayoutZoomFactor(dom_window_for_zoom_factor);
  float inverse_zoom_factor = 1 / zoom_factor;

  target_node->GetDocument().UpdateStyleAndLayout(DocumentUpdateReason::kInput);

  if (const LayoutObject* layout_object =
          StandaloneFindTargetLayoutObject(target_node)) {
    gfx::PointF local_pos =
        layout_object->AbsoluteToLocalPoint(AbsoluteLocation());

    if (layout_object->IsBoxModelObject()) {
      const auto* layout_box = To<LayoutBoxModelObject>(layout_object);
      const PhysicalOffset offset = layout_box->BorderOutsets().Offset();
      local_pos.Offset(-offset.left, -offset.top);
    }

    offset_x_ = local_pos.x() * inverse_zoom_factor;
    offset_y_ = local_pos.y() * inverse_zoom_factor;
  }

  Node* n = target_node;
  while (n && !n->GetLayoutObject())
    n = n->parentNode();

  if (n) {
    layer_location_.Scale(zoom_factor);
    if (LocalFrameView* view = n->GetLayoutObject()->View()->GetFrameView())
      layer_location_ = view->DocumentToFrame(layer_location_);

    PaintLayer* layer = n->GetLayoutObject()->EnclosingLayer();
    if (layer) {
      layer = layer->EnclosingSelfPaintingLayer();
      PhysicalOffset physical_offset =
          layer->GetLayoutObject().LocalToAbsolutePoint(PhysicalOffset(), 0);
      layer_location_ -= gfx::Vector2dF(physical_offset);
    }

    layer_location_.Scale(inverse_zoom_factor);
  }

  has_cached_relative_position_ = true;
}

WebMouseEvent TransformWebMouseEvent(LocalFrameView* frame_view,
                                     const WebMouseEvent& event) {
  WebMouseEvent result = event;
  if (event.GetType() == WebInputEvent::Type::kMouseUp ||
      event.GetType() == WebInputEvent::Type::kMouseDown) {
    result.UpdateEventModifiersToMatchButton();
  }
  result.SetFrameScale(StandaloneFrameScale(frame_view));
  result.SetFrameTranslate(StandaloneFrameTranslation(frame_view));
  return result;
}

int MouseEvent::layerX() {
  if (!has_cached_relative_position_)
    ComputeRelativePosition();
  return static_cast<int>(std::floor(layer_location_.x()));
}

int MouseEvent::layerY() {
  if (!has_cached_relative_position_)
    ComputeRelativePosition();
  return static_cast<int>(std::floor(layer_location_.y()));
}

double MouseEvent::offsetX() const {
  if (!HasPosition())
    return 0;
  if (!has_cached_relative_position_)
    const_cast<MouseEvent*>(this)->ComputeRelativePosition();
  return std::round(offset_x_);
}

double MouseEvent::offsetY() const {
  if (!HasPosition())
    return 0;
  if (!has_cached_relative_position_)
    const_cast<MouseEvent*>(this)->ComputeRelativePosition();
  return std::round(offset_y_);
}

void ContextMenuController::HandleContextMenuEvent(MouseEvent*) {}

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
ThreadStateStorage ThreadStateStorage::main_thread_state_storage_;
constinit thread_local ThreadStateStorage* g_thread_specific_
    __attribute__((tls_model(BLINK_HEAP_THREAD_LOCAL_MODEL))) = nullptr;

namespace {
constexpr unsigned long kStandaloneMemCommit = 0x1000;
constexpr unsigned long kStandaloneMemReserve = 0x2000;
constexpr unsigned long kStandaloneMemDecommit = 0x4000;
constexpr unsigned long kStandaloneMemRelease = 0x8000;
constexpr unsigned long kStandaloneMemReset = 0x80000;
constexpr unsigned long kStandalonePageNoAccess = 0x01;
constexpr unsigned long kStandalonePageReadonly = 0x02;
constexpr unsigned long kStandalonePageReadwrite = 0x04;
constexpr unsigned long kStandalonePageExecuteRead = 0x20;
constexpr unsigned long kStandalonePageExecuteReadwrite = 0x40;

unsigned long StandalonePageProtection(
    v8::PageAllocator::Permission permission) {
  switch (permission) {
    case v8::PageAllocator::kNoAccess:
    case v8::PageAllocator::kNoAccessWillJitLater:
      return kStandalonePageNoAccess;
    case v8::PageAllocator::kRead:
      return kStandalonePageReadonly;
    case v8::PageAllocator::kReadWrite:
      return kStandalonePageReadwrite;
    case v8::PageAllocator::kReadWriteExecute:
      return kStandalonePageExecuteReadwrite;
    case v8::PageAllocator::kReadExecute:
      return kStandalonePageExecuteRead;
  }
}

bool StandaloneNoAccessPermission(v8::PageAllocator::Permission permission) {
  return permission == v8::PageAllocator::kNoAccess ||
         permission == v8::PageAllocator::kNoAccessWillJitLater;
}

void* StandaloneTryAlignedReserve(size_t length, size_t alignment) {
  if (alignment <= 65536) {
    return nullptr;
  }
  if (length > std::numeric_limits<size_t>::max() - alignment) {
    return nullptr;
  }

  const size_t reserve_length = length + alignment;
  for (int attempt = 0; attempt < 8; ++attempt) {
    void* raw = VirtualAlloc(nullptr, reserve_length, kStandaloneMemReserve,
                             kStandalonePageNoAccess);
    if (!raw) {
      continue;
    }
    const uintptr_t raw_address = reinterpret_cast<uintptr_t>(raw);
    const uintptr_t aligned_address =
        (raw_address + alignment - 1) & ~(alignment - 1);
    VirtualFree(raw, 0, kStandaloneMemRelease);

    void* aligned = reinterpret_cast<void*>(aligned_address);
    if (VirtualAlloc(aligned, length, kStandaloneMemReserve,
                     kStandalonePageNoAccess) == aligned) {
      return aligned;
    }
  }
  return nullptr;
}

class StandaloneV8PageAllocator final : public v8::PageAllocator {
 public:
  StandaloneV8PageAllocator() = default;

  size_t AllocatePageSize() override { return allocation_granularity_; }
  size_t CommitPageSize() override { return page_size_; }
  void SetRandomMmapSeed(int64_t) override {}
  void* GetRandomMmapAddr() override { return nullptr; }

  void* AllocatePages(void* address,
                      size_t length,
                      size_t alignment,
                      Permission permissions) override {
    const unsigned long allocation_type =
        kStandaloneMemReserve |
        (StandaloneNoAccessPermission(permissions) ? 0 : kStandaloneMemCommit);
    if (!address && alignment > allocation_granularity_) {
      void* reserved = StandaloneTryAlignedReserve(length, alignment);
      if (!reserved) {
        return nullptr;
      }
      if (StandaloneNoAccessPermission(permissions)) {
        return reserved;
      }
      if (VirtualAlloc(reserved, length, kStandaloneMemCommit,
                       StandalonePageProtection(permissions)) == reserved) {
        return reserved;
      }
      VirtualFree(reserved, 0, kStandaloneMemRelease);
      return nullptr;
    }
    return VirtualAlloc(address, length, allocation_type,
                        StandalonePageProtection(permissions));
  }

  bool FreePages(void* address, size_t) override {
    return !!VirtualFree(address, 0, kStandaloneMemRelease);
  }

  bool ReleasePages(void* address, size_t length, size_t new_length) override {
    if (new_length >= length) {
      return true;
    }
    if (new_length == 0) {
      return FreePages(address, length);
    }
    auto* release_start = static_cast<uint8_t*>(address) + new_length;
    return !!VirtualFree(release_start, length - new_length,
                         kStandaloneMemDecommit);
  }

  bool SetPermissions(void* address,
                      size_t length,
                      Permission permissions) override {
    if (!StandaloneNoAccessPermission(permissions) &&
        VirtualAlloc(address, length, kStandaloneMemCommit,
                     StandalonePageProtection(permissions)) != address) {
      return false;
    }
    unsigned long old_protect = 0;
    return !!VirtualProtect(address, length, StandalonePageProtection(permissions),
                            &old_protect);
  }

  bool RecommitPages(void* address,
                     size_t length,
                     Permission permissions) override {
    return VirtualAlloc(address, length, kStandaloneMemCommit,
                        StandalonePageProtection(permissions)) == address;
  }

  bool DiscardSystemPages(void* address, size_t size) override {
    return !!VirtualAlloc(address, size, kStandaloneMemReset,
                          kStandalonePageReadwrite);
  }

  bool DecommitPages(void* address, size_t size) override {
    return !!VirtualFree(address, size, kStandaloneMemDecommit);
  }

 private:
  size_t page_size_ = 4096;
  size_t allocation_granularity_ = 65536;
};

class StandaloneV8TaskRunner final : public v8::TaskRunner {
 public:
  bool IdleTasksEnabled() override { return false; }
  bool NonNestableTasksEnabled() const override { return true; }
};

class StandaloneV8JobHandle final : public v8::JobHandle {
 public:
  void NotifyConcurrencyIncrease() override {}
  void Join() override {}
  void Cancel() override {}
  void CancelAndDetach() override {}
  bool IsActive() override { return false; }
  bool IsValid() override { return false; }
};

class StandaloneV8Platform final : public v8::Platform {
 public:
  v8::PageAllocator* GetPageAllocator() override { return &page_allocator_; }

  int NumberOfWorkerThreads() override { return 0; }

  std::shared_ptr<v8::TaskRunner> GetForegroundTaskRunner(
      v8::Isolate*,
      v8::TaskPriority) override {
    static auto runner = std::make_shared<StandaloneV8TaskRunner>();
    return runner;
  }

  double MonotonicallyIncreasingTime() override {
    return base::TimeTicks::Now().since_origin().InSecondsF();
  }

  double CurrentClockTimeMillis() override {
    return base::Time::Now().InMillisecondsFSinceUnixEpoch();
  }

  v8::TracingController* GetTracingController() override {
    return &tracing_controller_;
  }

 protected:
  std::unique_ptr<v8::JobHandle> CreateJobImpl(
      v8::TaskPriority,
      std::unique_ptr<v8::JobTask>,
      const v8::SourceLocation&) override {
    return std::make_unique<StandaloneV8JobHandle>();
  }

  void PostTaskOnWorkerThreadImpl(v8::TaskPriority,
                                  std::unique_ptr<v8::Task>,
                                  const v8::SourceLocation&) override {}

  void PostDelayedTaskOnWorkerThreadImpl(v8::TaskPriority,
                                         std::unique_ptr<v8::Task>,
                                         double,
                                         const v8::SourceLocation&) override {}

 private:
  StandaloneV8PageAllocator page_allocator_;
  v8::TracingController tracing_controller_;
};

StandaloneV8Platform& StandaloneCppgcPlatform() {
  static StandaloneV8Platform platform;
  return platform;
}

v8::Platform* StandaloneInitializedCppgcPlatform(v8::Platform* platform) {
  v8::Platform* effective_platform =
      platform ? platform : &StandaloneCppgcPlatform();
  if (!cppgc::IsInitialized()) {
    cppgc::InitializeProcess(effective_platform->GetPageAllocator());
  }
  return effective_platform;
}

cppgc::AllocationHandle& StandaloneAllocationHandle() {
  alignas(std::max_align_t) static unsigned char allocation_handle[64] = {};
  return *reinterpret_cast<cppgc::AllocationHandle*>(allocation_handle);
}

cppgc::HeapHandle& StandaloneHeapHandle() {
  alignas(std::max_align_t) static unsigned char heap_handle[64] = {};
  return *reinterpret_cast<cppgc::HeapHandle*>(heap_handle);
}
}  // namespace

ThreadStateStorage::ThreadStateStorage(
    ThreadState& thread_state,
    cppgc::AllocationHandle& allocation_handle,
    cppgc::HeapHandle& heap_handle)
    : allocation_handle_(&allocation_handle),
      heap_handle_(&heap_handle),
      thread_state_(&thread_state) {}

void ThreadStateStorage::AttachMainThread(
    ThreadState& thread_state,
    cppgc::AllocationHandle& allocation_handle,
    cppgc::HeapHandle& heap_handle) {
  g_thread_specific_ = new (&main_thread_state_storage_)
      ThreadStateStorage(thread_state, allocation_handle, heap_handle);
}

void ThreadStateStorage::AttachNonMainThread(
    ThreadState& thread_state,
    cppgc::AllocationHandle& allocation_handle,
    cppgc::HeapHandle& heap_handle) {
  g_thread_specific_ =
      new ThreadStateStorage(thread_state, allocation_handle, heap_handle);
}

void ThreadStateStorage::DetachNonMainThread(
    ThreadStateStorage& thread_state_storage) {
  if (g_thread_specific_ == &thread_state_storage) {
    g_thread_specific_ = nullptr;
  }
  if (&thread_state_storage != &main_thread_state_storage_) {
    delete &thread_state_storage;
  }
}

ThreadStateStorage* ThreadStateStorage::Current() {
  if (!g_thread_specific_) {
    ThreadState::AttachMainThread();
  }
  return g_thread_specific_;
}

ThreadState* ThreadState::AttachMainThread(
    std::optional<cppgc::StackStartMarker>) {
  auto* thread_state = new ThreadState(&StandaloneCppgcPlatform());
  ThreadStateStorage::AttachMainThread(
      *thread_state, thread_state->cpp_heap().GetAllocationHandle(),
      thread_state->cpp_heap().GetHeapHandle());
  return thread_state;
}

ThreadState* ThreadState::AttachCurrentThread() {
  auto* thread_state = new ThreadState(&StandaloneCppgcPlatform());
  ThreadStateStorage::AttachNonMainThread(
      *thread_state, thread_state->cpp_heap().GetAllocationHandle(),
      thread_state->cpp_heap().GetHeapHandle());
  return thread_state;
}

void ThreadState::DetachCurrentThread() {}

ThreadState::ThreadState(
    v8::Platform* platform,
    std::optional<cppgc::StackStartMarker>)
    : owning_cpp_heap_(v8::CppHeap::Create(
          StandaloneInitializedCppgcPlatform(platform),
          v8::CppHeapCreateParams(CustomSpaces::CreateCustomSpaces()))),
      cpp_heap_(owning_cpp_heap_.get()),
      heap_handle_(cpp_heap_->GetHeapHandle()),
      thread_id_(CurrentThread()) {}

ThreadState::~ThreadState() = default;

void ThreadState::AttachToIsolate(v8::Isolate*,
                                  DevToolsCountersCallback) {}

void ThreadState::DetachFromIsolate() {}

std::unique_ptr<v8::CppHeap> ThreadState::ReleaseCppHeap() {
  return std::move(owning_cpp_heap_);
}

void ThreadState::RecoverCppHeap(std::unique_ptr<v8::CppHeap> cpp_heap) {
  owning_cpp_heap_ = std::move(cpp_heap);
  cpp_heap_ = owning_cpp_heap_.get();
}

void ThreadState::RecoverCppHeapAfterIsolateTearDownForTesting() {}

ThreadState* ThreadState::AttachMainThreadForTesting(v8::Platform*) {
  return AttachMainThread();
}

ThreadState* ThreadState::AttachCurrentThreadForTesting(v8::Platform*) {
  return AttachCurrentThread();
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

const char* const Partitions::kAllocatedObjectPoolName =
    "blink_gc/allocated_objects";

namespace {
class StandaloneDecodedImage final : public Image {
 public:
  static scoped_refptr<StandaloneDecodedImage> Create(sk_sp<SkImage> image) {
    if (!image) {
      return nullptr;
    }
    return base::AdoptRef(new StandaloneDecodedImage(std::move(image)));
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
  explicit StandaloneDecodedImage(sk_sp<SkImage> image)
      : Image(nullptr, false),
        size_(image->width(), image->height()),
        paint_image_(CreatePaintImageBuilder()
                         .set_image(std::move(image),
                                    cc::PaintImage::GetNextContentId())
                         .TakePaintImage()) {}

  gfx::Size size_;
  PaintImage paint_image_;
};

scoped_refptr<Image> LoadStandaloneDecodedImage(
    const KURL& url,
    html_css_renderer::StandaloneResourceInitiator initiator) {
  html_css_renderer::StandaloneResourceRequest request;
  request.url = url.GetString().Utf8();
  request.type_hint = html_css_renderer::StandaloneResourceTypeHint::kImage;
  request.initiator = initiator;
  request.accepted_mime_types.push_back("image/png");
  request.accepted_mime_types.push_back("image/jpeg");
  request.accepted_mime_types.push_back("image/bmp");
  request.accepted_mime_types.push_back("image/webp");
  request.accepted_mime_types.push_back("image/svg+xml");
  html_css_renderer::StandaloneResourceResult result =
      html_css_renderer::DefaultStandaloneResourceProvider().LoadResource(
          request);
  if (result.status != html_css_renderer::StandaloneResourceStatus::kSuccess) {
    return nullptr;
  }
  if (result.mime_type == "image/svg+xml" && !result.encoded_bytes.empty()) {
    return nullptr;
  }
  if (!result.decoded_image) {
    return nullptr;
  }
  return StandaloneDecodedImage::Create(std::move(result.decoded_image));
}

html_css_renderer::StandaloneResourceInitiator StandaloneInitiatorForFetch(
    const FetchParameters& params) {
  if (params.Options().initiator_info.name == fetch_initiator_type_names::kCSS ||
      params.Options().initiator_info.name ==
          fetch_initiator_type_names::kUacss) {
    return html_css_renderer::StandaloneResourceInitiator::kCssBackgroundImage;
  }
  return html_css_renderer::StandaloneResourceInitiator::kImgElement;
}

html_css_renderer::StandaloneResourceResult LoadStandaloneEncodedImageResource(
    const KURL& url,
    html_css_renderer::StandaloneResourceInitiator initiator) {
  html_css_renderer::StandaloneResourceRequest request;
  request.url = url.GetString().Utf8();
  request.type_hint = html_css_renderer::StandaloneResourceTypeHint::kImage;
  request.initiator = initiator;
  request.accepted_mime_types.push_back("image/png");
  request.accepted_mime_types.push_back("image/jpeg");
  request.accepted_mime_types.push_back("image/bmp");
  request.accepted_mime_types.push_back("image/webp");
  request.accepted_mime_types.push_back("image/svg+xml");
  return html_css_renderer::DefaultStandaloneResourceProvider().LoadResource(
      request);
}

bool ShouldUseStandaloneDecodedImageResource(
    const html_css_renderer::StandaloneResourceResult& result) {
  return (result.mime_type == "image/jpeg" ||
          result.mime_type == "image/bmp" ||
          result.mime_type == "image/webp") &&
         result.decoded_image;
}

Resource* CreateStandaloneDecodedImageResource(
    const FetchParameters& params,
    html_css_renderer::StandaloneResourceResult result) {
  scoped_refptr<Image> image =
      StandaloneDecodedImage::Create(std::move(result.decoded_image));
  if (!image) {
    return nullptr;
  }

  auto* image_resource = MakeGarbageCollected<ImageResource>(
      params.GetResourceRequest(), params.Options(),
      ImageResourceContent::CreateLoaded(std::move(image)));

  ResourceResponse response;
  response.SetHttpStatusCode(200);
  response.SetHttpStatusText(AtomicString("OK"));
  response.SetCurrentRequestUrl(params.Url());
  response.SetExpectedContentLength(
      static_cast<int64_t>(result.encoded_bytes.size()));
  response.SetTextEncodingName(g_empty_atom);
  response.SetMimeType(AtomicString(result.mime_type.c_str()));
  response.AddHttpHeaderField(http_names::kContentType, response.MimeType());

  scoped_refptr<SharedBuffer> data = SharedBuffer::Create(
      base::span<const uint8_t>(result.encoded_bytes.data(),
                                result.encoded_bytes.size()));

  image_resource->ResponseReceived(response);
  image_resource->SetDataBufferingPolicy(kBufferData);
  image_resource->SetResourceBuffer(data);
  image_resource->SetCacheIdentifier(result.cache_key.empty()
                                         ? params.Url().GetString()
                                         : String(result.cache_key.c_str()));
  image_resource->SetStatus(ResourceStatus::kCached);
  return image_resource;
}

Resource* CreateStandaloneProviderBackedResource(
    const FetchParameters& params,
    const ResourceFactory& factory,
    base::SingleThreadTaskRunner* task_runner) {
  if (factory.GetType() != ResourceType::kImage) {
    return nullptr;
  }

  html_css_renderer::StandaloneResourceResult result =
      LoadStandaloneEncodedImageResource(params.Url(),
                                         StandaloneInitiatorForFetch(params));
  if (result.status == html_css_renderer::StandaloneResourceStatus::kSuccess &&
      ShouldUseStandaloneDecodedImageResource(result)) {
    if (Resource* resource =
            CreateStandaloneDecodedImageResource(params, std::move(result))) {
      return resource;
    }
  }

  Resource* resource = factory.Create(params.GetResourceRequest(),
                                      params.Options(),
                                      params.DecoderOptions());

  if (result.status != html_css_renderer::StandaloneResourceStatus::kSuccess ||
      result.encoded_bytes.empty()) {
    resource->FinishAsError(ResourceError::CancelledError(params.Url()),
                            task_runner);
    return resource;
  }

  ResourceResponse response;
  response.SetHttpStatusCode(200);
  response.SetHttpStatusText(AtomicString("OK"));
  response.SetCurrentRequestUrl(params.Url());
  response.SetExpectedContentLength(
      static_cast<int64_t>(result.encoded_bytes.size()));
  response.SetTextEncodingName(g_empty_atom);
  response.SetMimeType(AtomicString(result.mime_type.c_str()));
  response.AddHttpHeaderField(http_names::kContentType, response.MimeType());

  scoped_refptr<SharedBuffer> data = SharedBuffer::Create(
      base::span<const uint8_t>(result.encoded_bytes.data(),
                                result.encoded_bytes.size()));

  resource->NotifyStartLoad();
  resource->ResponseReceived(response);
  resource->SetDataBufferingPolicy(kBufferData);
  resource->SetResourceBuffer(data);
  resource->SetCacheIdentifier(result.cache_key.empty()
                                   ? params.Url().GetString()
                                   : String(result.cache_key.c_str()));
  resource->Finish(base::TimeTicks(), task_runner);
  return resource;
}
}  // namespace

MemoryPressureListenerRegistration::MemoryPressureListenerRegistration(
    base::Location,
    base::MemoryPressureListenerTag,
    base::MemoryPressureListener*) {}
MemoryPressureListenerRegistration::~MemoryPressureListenerRegistration() =
    default;
void MemoryPressureListenerRegistration::Dispose() {}

WebMemoryAllocatorDump::WebMemoryAllocatorDump(
    base::trace_event::MemoryAllocatorDump*)
    : guid_(0) {}
void WebMemoryAllocatorDump::AddScalar(const char*, const char*, uint64_t) {}
void WebMemoryAllocatorDump::AddString(const char*, const char*, const String&) {
}
WebMemoryAllocatorDumpGuid WebMemoryAllocatorDump::Guid() const {
  return guid_;
}
WebMemoryAllocatorDump* WebProcessMemoryDump::CreateMemoryAllocatorDump(
    const String&) {
  return nullptr;
}
void WebProcessMemoryDump::AddSuballocation(WebMemoryAllocatorDumpGuid,
                                            const String&) {}

void SubresourceIntegrity::ParseIntegrityAttribute(const String&,
                                                   IntegrityMetadataSet&,
                                                   const FeatureContext*) {}
bool SubresourceIntegrity::CheckUnencodedDigests(
    const Vector<network::IntegrityMetadata>&,
    const SegmentedBuffer*) {
  return true;
}
bool SubresourceIntegrity::CheckSubresourceIntegrity(
    const IntegrityMetadataSet&,
    const SegmentedBuffer*,
    const KURL&,
    const Resource&,
    const FeatureContext*,
    IntegrityReport&,
    HashMap<HashAlgorithm, String>*) {
  return true;
}
String SubresourceIntegrity::GetSubresourceIntegrityHash(
    const SegmentedBuffer*,
    HashAlgorithm) {
  return String();
}

FetchContext& ResourceLoader::Context() const {
  return FetchContext::NullInstance();
}
void ResourceLoader::ScheduleCancel() {}
void ResourceLoader::DidChangePriority(ResourceLoadPriority, int) {}
void ResourceLoader::AbortResponseBodyLoading() {}
void ResourceLoader::DidFinishLoading(base::TimeTicks,
                                      int64_t,
                                      uint64_t,
                                      int64_t) {}
void ResourceLoader::DidFinishLoadingFirstPartInMultipart() {}
scoped_refptr<base::SingleThreadTaskRunner>
ResourceLoader::GetLoadingTaskRunner() {
  return nullptr;
}
void ResourceLoader::Trace(Visitor* visitor) const {
  visitor->Trace(resource_);
  visitor->Trace(fetcher_);
}

bool ParseMultipartHeadersFromBody(base::span<const uint8_t>,
                                   ResourceResponse*,
                                   wtf_size_t*) {
  return false;
}

void ParseCommaDelimitedHeader(const StringView&, CommaDelimitedHeaderSet&) {}

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
  return mojom::blink::PointerType::kPointerFineType;
}
int MediaValuesDynamic::AvailablePointerTypes() const {
  return static_cast<int>(mojom::blink::PointerType::kPointerFineType);
}
mojom::blink::HoverType MediaValuesDynamic::PrimaryHoverType() const {
  return mojom::blink::HoverType::kHoverHoverType;
}
mojom::blink::OutputDeviceUpdateAbilityType
MediaValuesDynamic::OutputDeviceUpdateAbilityType() const {
  return mojom::blink::OutputDeviceUpdateAbilityType::kFastType;
}
int MediaValuesDynamic::AvailableHoverTypes() const {
  return static_cast<int>(mojom::blink::HoverType::kHoverHoverType);
}
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
  return frame_ && frame_->View()
             ? frame_->View()->ViewportSizeForMediaQueries().width()
             : 800;
}
double MediaValuesDynamic::ViewportHeight() const {
  if (viewport_dimensions_overridden_) {
    return viewport_height_override_;
  }
  return frame_ && frame_->View()
             ? frame_->View()->ViewportSizeForMediaQueries().height()
             : 600;
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

void HTMLDialogElement::HandleDialogLightDismissForClick(
    const PointerEventFactory::PointerTarget&,
    const PointerEventFactory::PointerTarget&) {}
void HTMLDialogElement::HandleDialogLightDismiss(const PointerEvent&,
                                                 const Node&) {}

#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
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
#endif

bool HTMLSubmitButtonBehavior::HandleActivation(Event&) {
  return false;
}

int KeyboardEvent::charCode() const {
  return 0;
}

KeyboardEvent::KeyboardEvent(const WebKeyboardEvent&,
                             LocalDOMWindow*,
                             bool cancellable)
    : UIEventWithKeyState(event_type_names::kKeydown,
                          Bubbles::kYes,
                          cancellable ? Cancelable::kYes : Cancelable::kNo,
                          nullptr,
                          0,
                          WebInputEvent::kNoModifiers,
                          base::TimeTicks::Now(),
                          nullptr),
      location_(kDomKeyLocationStandard) {}

KeyboardEvent::~KeyboardEvent() = default;

void KeyboardEvent::Trace(Visitor* visitor) const {
  UIEventWithKeyState::Trace(visitor);
}

const AtomicString& KeyboardEvent::InterfaceName() const {
  return event_interface_names::kKeyboardEvent;
}

bool KeyboardEvent::IsKeyboardEvent() const {
  return true;
}

unsigned KeyboardEvent::which() const {
  return static_cast<unsigned>(keyCode());
}

void ElementInternals::SetBehaviors(HeapVector<Member<ElementBehavior>>,
                                    ExceptionState&) {}

Element* HTMLFormElement::FindDefaultButton() const {
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
  LayoutBox* box = GetLayoutBox();
  if (!box)
    return PhysicalRect();
  return PhysicalRect(PhysicalOffset::FromPointFRound(ScrollPosition()),
                      box->PhysicalPaddingBoxRect().size);
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

#if 0
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
#endif
InterpolationTypesMap::InterpolationTypesMap(const PropertyRegistry* registry,
                                             const Document& document)
    : document_(document), registry_(registry) {}
size_t InterpolationTypesMap::Version() const {
  return 0;
}
const InterpolationTypes* InterpolationTypesMap::Get(
    const PropertyHandle& property) const {
  using ApplicableTypesMap =
      GCedHeapHashMap<PropertyHandle, Member<InterpolationTypes>>;
  DEFINE_STATIC_LOCAL(Persistent<ApplicableTypesMap>, applicable_types_map,
                      (MakeGarbageCollected<ApplicableTypesMap>()));

  auto entry = applicable_types_map->find(property);
  if (entry != applicable_types_map->end()) {
    return entry->value;
  }

  auto* applicable_types = MakeGarbageCollected<InterpolationTypes>();
  const CSSProperty& css_property = property.GetCSSProperty();
  bool supported_by_standalone = false;
  switch (css_property.PropertyID()) {
    case CSSPropertyID::kOpacity:
    case CSSPropertyID::kFillOpacity:
    case CSSPropertyID::kFloodOpacity:
    case CSSPropertyID::kStopOpacity:
    case CSSPropertyID::kStrokeOpacity:
      applicable_types->push_back(
          MakeGarbageCollected<CSSNumberInterpolationType>(property));
      supported_by_standalone = true;
      break;
    case CSSPropertyID::kAccentColor:
    case CSSPropertyID::kBackgroundColor:
    case CSSPropertyID::kBorderBottomColor:
    case CSSPropertyID::kBorderLeftColor:
    case CSSPropertyID::kBorderRightColor:
    case CSSPropertyID::kBorderTopColor:
    case CSSPropertyID::kCaretColor:
    case CSSPropertyID::kColor:
    case CSSPropertyID::kFloodColor:
    case CSSPropertyID::kLightingColor:
    case CSSPropertyID::kOutlineColor:
    case CSSPropertyID::kStopColor:
    case CSSPropertyID::kTextDecorationColor:
    case CSSPropertyID::kTextEmphasisColor:
    case CSSPropertyID::kWebkitTextFillColor:
    case CSSPropertyID::kWebkitTextStrokeColor:
      applicable_types->push_back(
          MakeGarbageCollected<CSSColorInterpolationType>(property));
      supported_by_standalone = true;
      break;
    case CSSPropertyID::kTransform:
      applicable_types->push_back(
          MakeGarbageCollected<CSSTransformInterpolationType>(property));
      supported_by_standalone = true;
      break;
    case CSSPropertyID::kHeight:
    case CSSPropertyID::kLeft:
    case CSSPropertyID::kTop:
    case CSSPropertyID::kWidth:
      applicable_types->push_back(
          MakeGarbageCollected<CSSLengthInterpolationType>(property));
      supported_by_standalone = true;
      break;
    default:
      break;
  }
  if (supported_by_standalone) {
    applicable_types->push_back(
        MakeGarbageCollected<CSSDefaultInterpolationType>(property));
  }

  auto add_result = applicable_types_map->insert(property, applicable_types);
  return add_result.stored_value->value;
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

static EDisplay StandaloneEquivalentBlockDisplay(EDisplay display) {
  switch (display) {
    case EDisplay::kFlowRootListItem:
    case EDisplay::kBlock:
    case EDisplay::kTable:
    case EDisplay::kWebkitBox:
    case EDisplay::kFlex:
    case EDisplay::kGrid:
    case EDisplay::kBlockMath:
    case EDisplay::kBlockRuby:
    case EDisplay::kListItem:
    case EDisplay::kFlowRoot:
    case EDisplay::kLayoutCustom:
    case EDisplay::kGridLanes:
      return display;
    case EDisplay::kInlineTable:
      return EDisplay::kTable;
    case EDisplay::kWebkitInlineBox:
      return EDisplay::kWebkitBox;
    case EDisplay::kInlineFlex:
      return EDisplay::kFlex;
    case EDisplay::kInlineGrid:
      return EDisplay::kGrid;
    case EDisplay::kMath:
      return EDisplay::kBlockMath;
    case EDisplay::kRuby:
      return EDisplay::kBlockRuby;
    case EDisplay::kInlineLayoutCustom:
      return EDisplay::kLayoutCustom;
    case EDisplay::kInlineListItem:
      return EDisplay::kListItem;
    case EDisplay::kInlineFlowRootListItem:
      return EDisplay::kFlowRootListItem;
    case EDisplay::kInlineGridLanes:
      return EDisplay::kGridLanes;
    case EDisplay::kContents:
    case EDisplay::kInline:
    case EDisplay::kInlineBlock:
    case EDisplay::kTableRowGroup:
    case EDisplay::kTableHeaderGroup:
    case EDisplay::kTableFooterGroup:
    case EDisplay::kTableRow:
    case EDisplay::kTableColumnGroup:
    case EDisplay::kTableColumn:
    case EDisplay::kTableCell:
    case EDisplay::kTableCaption:
    case EDisplay::kRubyText:
      return EDisplay::kBlock;
    case EDisplay::kNone:
      return display;
  }
  return EDisplay::kBlock;
}

void StyleAdjuster::AdjustComputedStyle(StyleResolverState& state, Element* element) {
  ComputedStyleBuilder& builder = state.StyleBuilder();
  if (builder.Display() != EDisplay::kContents &&
      (builder.HasOutOfFlowPosition() || builder.IsFloating())) {
    builder.SetDisplay(StandaloneEquivalentBlockDisplay(builder.Display()));
  }
  if (builder.Display() != EDisplay::kNone &&
      builder.StyleType() != kPseudoIdScrollMarker) {
    if (const ComputedStyle* layout_parent_style =
            state.LayoutParentStyle()) {
      AdjustStyleForDisplay(builder, *layout_parent_style, element,
                            element ? &element->GetDocument() : nullptr);
    }
  }
  if (builder.Appearance() == AppearanceValue::kNone || !element) {
    builder.SetEffectiveAppearance(AppearanceValue::kNone);
  } else {
    LayoutTheme::GetTheme().AdjustStyle(*element, builder);
  }
  builder.SetForcesStackingContext(false);
  if (builder.GetPosition() != EPosition::kStatic) {
    builder.SetAllowsZIndex(true);
    if (!builder.HasAutoZIndex()) {
      builder.SetForcesStackingContext(true);
    }
  }
}

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

MediaQueryExp::MediaQueryExp(const MediaQueryExp& other)
    : type_(other.type_),
      media_feature_(other.media_feature_),
      reference_value_(other.reference_value_),
      bounds_(other.bounds_) {}
MediaQueryExp::~MediaQueryExp() = default;

namespace {
bool StandaloneMediaFeatureWithValidIdent(const String& media_feature,
                                          CSSValueID ident) {
  if (media_feature == media_feature_names::kOrientationMediaFeature) {
    return ident == CSSValueID::kPortrait || ident == CSSValueID::kLandscape;
  }
  if (media_feature == media_feature_names::kPointerMediaFeature ||
      media_feature == media_feature_names::kAnyPointerMediaFeature) {
    return ident == CSSValueID::kNone || ident == CSSValueID::kCoarse ||
           ident == CSSValueID::kFine;
  }
  if (media_feature == media_feature_names::kHoverMediaFeature ||
      media_feature == media_feature_names::kAnyHoverMediaFeature) {
    return ident == CSSValueID::kNone || ident == CSSValueID::kHover;
  }
  if (media_feature == media_feature_names::kPrefersColorSchemeMediaFeature) {
    return ident == CSSValueID::kDark || ident == CSSValueID::kLight;
  }
  if (media_feature ==
      media_feature_names::kPrefersReducedMotionMediaFeature) {
    return ident == CSSValueID::kNoPreference || ident == CSSValueID::kReduce;
  }
  return false;
}

bool StandaloneMediaFeatureWithValidLength(const String& media_feature,
                                           const CSSPrimitiveValue* value) {
  if (!value ||
      !(value->IsLength() ||
        (value->IsNumber() && value->GetValueIfKnown() == 0.0))) {
    return false;
  }
  return media_feature == media_feature_names::kHeightMediaFeature ||
         media_feature == media_feature_names::kMaxHeightMediaFeature ||
         media_feature == media_feature_names::kMinHeightMediaFeature ||
         media_feature == media_feature_names::kWidthMediaFeature ||
         media_feature == media_feature_names::kMaxWidthMediaFeature ||
         media_feature == media_feature_names::kMinWidthMediaFeature ||
         media_feature == media_feature_names::kDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kMaxDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kMinDeviceHeightMediaFeature ||
         media_feature == media_feature_names::kDeviceWidthMediaFeature ||
         media_feature == media_feature_names::kMinDeviceWidthMediaFeature ||
         media_feature == media_feature_names::kMaxDeviceWidthMediaFeature ||
         media_feature == media_feature_names::kInlineSizeMediaFeature ||
         media_feature == media_feature_names::kMinInlineSizeMediaFeature ||
         media_feature == media_feature_names::kMaxInlineSizeMediaFeature ||
         media_feature == media_feature_names::kBlockSizeMediaFeature ||
         media_feature == media_feature_names::kMinBlockSizeMediaFeature ||
         media_feature == media_feature_names::kMaxBlockSizeMediaFeature;
}
}  // namespace

MediaQueryExp::MediaQueryExp(const String& media_feature,
                             const MediaQueryExpValue& value)
    : MediaQueryExp(media_feature,
                    MediaQueryExpBounds(MediaQueryExpComparison(value)),
                    Type::kMediaFeature) {}

MediaQueryExp::MediaQueryExp(const String& media_feature,
                             const MediaQueryExpBounds& bounds,
                             Type type)
    : type_(type), media_feature_(media_feature), bounds_(bounds) {}

MediaQueryExp::MediaQueryExp(
    const CSSUnparsedDeclarationValue& reference_value,
    const MediaQueryExpBounds& bounds)
    : type_(Type::kStyleRange),
      reference_value_(reference_value),
      bounds_(bounds) {}

MediaQueryExp MediaQueryExp::Create(const AtomicString& media_feature,
                                    CSSParserTokenStream& stream,
                                    const CSSParserContext& context,
                                    bool) {
  std::optional<MediaQueryExpValue> value =
      MediaQueryExpValue::Consume(media_feature, stream, context, false);
  if (value.has_value()) {
    StandaloneMediaQueryParsedExpectedValues()[media_feature.Utf8()] =
        value->CssText().Utf8();
    return MediaQueryExp(media_feature, value.value());
  }
  return Invalid();
}

MediaQueryExp MediaQueryExp::Create(const AtomicString& media_feature,
                                    const MediaQueryExpBounds& bounds) {
  return MediaQueryExp(media_feature, bounds, Type::kMediaFeature);
}

MediaQueryExp MediaQueryExp::Create(const AtomicString& custom_media) {
  return MediaQueryExp(custom_media, MediaQueryExpBounds(), Type::kCustomMedia);
}

MediaQueryExp MediaQueryExp::Create(const MediaQueryExpValue& reference_value,
                                    const MediaQueryExpBounds& bounds) {
  if (!reference_value.IsValue()) {
    return Invalid();
  }
  const CSSUnparsedDeclarationValue* value =
      DynamicTo<CSSUnparsedDeclarationValue>(reference_value.GetCSSValue());
  if (!value) {
    return Invalid();
  }
  return MediaQueryExp(*value, bounds);
}

void MediaQueryExp::Trace(Visitor* visitor) const {
  visitor->Trace(reference_value_);
  visitor->Trace(bounds_);
}

bool MediaQueryExp::operator==(const MediaQueryExp& other) const {
  return type_ == other.type_ && media_feature_ == other.media_feature_ &&
         reference_value_ == other.reference_value_ && bounds_ == other.bounds_;
}

bool MediaQueryExp::IsViewportDependent() const {
  if (!HasMediaFeature()) {
    return false;
  }
  return IsWidthDependent() || IsHeightDependent() ||
         IsInlineSizeDependent() || IsBlockSizeDependent() ||
         media_feature_ == media_feature_names::kOrientationMediaFeature;
}

bool MediaQueryExp::IsDeviceDependent() const {
  if (!HasMediaFeature()) {
    return false;
  }
  return media_feature_ == media_feature_names::kDeviceWidthMediaFeature ||
         media_feature_ == media_feature_names::kMinDeviceWidthMediaFeature ||
         media_feature_ == media_feature_names::kMaxDeviceWidthMediaFeature ||
         media_feature_ == media_feature_names::kDeviceHeightMediaFeature ||
         media_feature_ == media_feature_names::kMinDeviceHeightMediaFeature ||
         media_feature_ == media_feature_names::kMaxDeviceHeightMediaFeature ||
         media_feature_ ==
             media_feature_names::kDevicePixelRatioMediaFeature ||
         media_feature_ ==
             media_feature_names::kMinDevicePixelRatioMediaFeature ||
         media_feature_ ==
             media_feature_names::kMaxDevicePixelRatioMediaFeature;
}

bool MediaQueryExp::IsWidthDependent() const {
  if (!HasMediaFeature()) {
    return false;
  }
  return media_feature_ == media_feature_names::kWidthMediaFeature ||
         media_feature_ == media_feature_names::kMinWidthMediaFeature ||
         media_feature_ == media_feature_names::kMaxWidthMediaFeature;
}

bool MediaQueryExp::IsHeightDependent() const {
  if (!HasMediaFeature()) {
    return false;
  }
  return media_feature_ == media_feature_names::kHeightMediaFeature ||
         media_feature_ == media_feature_names::kMinHeightMediaFeature ||
         media_feature_ == media_feature_names::kMaxHeightMediaFeature;
}

bool MediaQueryExp::IsInlineSizeDependent() const {
  if (!HasMediaFeature()) {
    return false;
  }
  return media_feature_ == media_feature_names::kInlineSizeMediaFeature ||
         media_feature_ == media_feature_names::kMinInlineSizeMediaFeature ||
         media_feature_ == media_feature_names::kMaxInlineSizeMediaFeature;
}

bool MediaQueryExp::IsBlockSizeDependent() const {
  if (!HasMediaFeature()) {
    return false;
  }
  return media_feature_ == media_feature_names::kBlockSizeMediaFeature ||
         media_feature_ == media_feature_names::kMinBlockSizeMediaFeature ||
         media_feature_ == media_feature_names::kMaxBlockSizeMediaFeature;
}

String MediaQueryExp::Serialize() const {
  if (HasMediaFeature() || IsCustomMedia()) {
    return media_feature_;
  }
  return String();
}

unsigned MediaQueryExp::GetUnitFlags() const {
  unsigned unit_flags = 0;
  if (Bounds().left.IsValid()) {
    unit_flags |= Bounds().left.value.GetUnitFlags();
  }
  if (Bounds().right.IsValid()) {
    unit_flags |= Bounds().right.value.GetUnitFlags();
  }
  return unit_flags;
}

std::optional<MediaQueryExpValue> MediaQueryExpValue::Consume(
    const String& media_feature,
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    bool) {
  CSSParserLocalContext local_context =
      CSSParserLocalContext::CreateWithoutPropertyForAtRules();
  CSSPrimitiveValue* value = css_parsing_utils::ConsumeLength(
      stream, context, local_context, CSSPrimitiveValue::ValueRange::kAll);
  if (!value) {
    value = css_parsing_utils::ConsumeNumber(
        stream, context, local_context, CSSPrimitiveValue::ValueRange::kAll);
  }
  if (value) {
    if (StandaloneMediaFeatureWithValidLength(media_feature, value) ||
        value->IsNumber()) {
      return MediaQueryExpValue(*value);
    }
    return std::nullopt;
  }
  if (CSSIdentifierValue* ident = css_parsing_utils::ConsumeIdent(stream)) {
    CSSValueID ident_id = ident->GetValueID();
    if (StandaloneMediaFeatureWithValidIdent(media_feature, ident_id)) {
      return MediaQueryExpValue(ident_id);
    }
  }
  return std::nullopt;
}

unsigned MediaQueryExpValue::GetUnitFlags() const {
  return 0;
}

String MediaQueryExpValue::CssText() const {
  switch (type_) {
    case Type::kInvalid:
      return String();
    case Type::kValue:
      return GetCSSValue().CssText();
    case Type::kRatio:
      return String();
    case Type::kId:
      return GetCSSValueNameAs<StringView>(Id()).ToString();
  }
  return String();
}

void MediaQueryFeatureExpNode::Trace(Visitor* visitor) const {
  visitor->Trace(exp_);
}

unsigned MediaQueryFeatureExpNode::GetUnitFlags() const {
  return 0;
}

bool MediaQueryFeatureExpNode::IsViewportDependent() const {
  return exp_.IsViewportDependent();
}

bool MediaQueryFeatureExpNode::IsDeviceDependent() const {
  return exp_.IsDeviceDependent();
}

bool MediaQueryFeatureExpNode::IsWidthDependent() const {
  return exp_.IsWidthDependent();
}

bool MediaQueryFeatureExpNode::IsHeightDependent() const {
  return exp_.IsHeightDependent();
}

bool MediaQueryFeatureExpNode::IsInlineSizeDependent() const {
  return exp_.IsInlineSizeDependent();
}

bool MediaQueryFeatureExpNode::IsBlockSizeDependent() const {
  return exp_.IsBlockSizeDependent();
}

KleeneValue MediaQueryFeatureExpNode::Evaluate(
    ConditionalExpNodeVisitor& visitor) const {
  static bool media_query_evaluator_initialized = false;
  if (!media_query_evaluator_initialized) {
    MediaQueryEvaluator::Init();
    media_query_evaluator_initialized = true;
  }
  const KleeneValue result = visitor.EvaluateMediaQueryFeatureExpNode(*this);
  StandaloneRecordMediaQueryEvaluation(*this, result);
  return result;
}

void MediaQueryFeatureExpNode::SerializeTo(StringBuilder& builder) const {
  builder.Append(exp_.Serialize());
}

const unsigned char* SelectorStatisticsFlag::GetCategoryGroupEnabled() {
  static const unsigned char disabled = 0;
  return &disabled;
}

void SelectorStatisticsCollector::ReserveCapacity(wtf_size_t) {}
void SelectorStatisticsCollector::BeginCollectionForRule(const RuleData*) {}
void SelectorStatisticsCollector::EndCollectionForCurrentRule() {}

RuleInvalidationDataTracer::RuleInvalidationDataTracer(
    const RuleInvalidationData& data)
    : RuleInvalidationDataVisitor<RuleInvalidationDataVisitorType::kTracer>(
          data) {}
void RuleInvalidationDataTracer::TraceInvalidationSetsForSelector(
    const CSSSelector&) {}

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

LinkStyle* HTMLLinkElement::GetLinkStyle() const {
  return nullptr;
}

Referrer::Referrer()
    : referrer_policy(network::mojom::ReferrerPolicy::kDefault) {}

const AtomicString& Referrer::ClientReferrerString() {
  static const AtomicString* client = new AtomicString("about:client");
  return *client;
}


unsigned FirstLetterPseudoElement::FirstLetterLength(
    const String& string,
    bool,
    Punctuation& punctuation) {
  punctuation = Punctuation::kNotSeen;
  return string.empty() ? 0u : 1u;
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

Vector<String> FileInputType::FilesFromFormControlState(
    const FormControlState&) {
  return Vector<String>();
}

void SpellChecker::DidEndEditingOnTextField(Element*) {}

void ListedElement::UpdateWillValidateCache(WillValidateReason) {}

void FontCache::PrewarmFamily(const AtomicString&) {}


void HTMLFormElement::InvalidateDefaultButtonStyle() const {}

void DOMTokenList::Add(const AtomicString&) {}
void DOMTokenList::Remove(const AtomicString&) {}

String ExceptionMessages::NotAFiniteNumber(double, const char*) {
  return String("Value is not a finite number.");
}

String ExceptionMessages::IndexExceedsMinimumBound(const char*,
                                                   bool,
                                                   const String&,
                                                   const String&) {
  return String("Index is below the minimum bound.");
}

String ExceptionMessages::IndexExceedsMaximumBound(const char*,
                                                   bool,
                                                   const String&,
                                                   const String&) {
  return String("Index is above the maximum bound.");
}

String ExceptionMessages::ReadOnly(const char*) {
  return String("The object is read-only.");
}

bool IsWordBreak(char16_t) {
  return false;
}

InputDeviceCapabilitiesConstants* DOMWindow::GetInputDeviceCapabilities() {
  if (!input_capabilities_)
    input_capabilities_ = MakeGarbageCollected<InputDeviceCapabilitiesConstants>();
  return input_capabilities_.Get();
}

void HitTestResult::OverrideNodeAndPosition(Node* node,
                                            PhysicalOffset position) {
  local_point_ = position;
  SetInnerNode(node);
}

void OpaqueRange::Trace(Visitor*) const {}

v8::Local<v8::Value> ScriptValue::V8Value() const {
  return v8::Local<v8::Value>();
}

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
String TrustedTypesCheckForScriptURL(const String& script_url,
                                     const ExecutionContext*,
                                     const AtomicString&,
                                     const AtomicString&,
                                     ExceptionState&) {
  return script_url;
}

LayoutShiftTracker::ReattachHookScope::ReattachHookScope(const Node&) {}
LayoutShiftTracker::ReattachHookScope::~ReattachHookScope() = default;
void LayoutShiftTracker::ReattachHookScope::NotifyAttach(const Node&) {}
void LayoutShiftTracker::ReattachHookScope::NotifyDetach(const Node&) {}
void LayoutShiftTracker::Trace(Visitor*) const {}

EventHandlerRegistry::EventHandlerRegistry(LocalFrame& frame)
    : frame_(&frame) {}
EventHandlerRegistry::~EventHandlerRegistry() = default;
void EventHandlerRegistry::Trace(Visitor*) const {}
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
bool EventHandlerRegistry::HasEventHandlers(EventHandlerClass) const {
  return false;
}

#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
namespace {

int& StandaloneCurrentKeyboardEventKeyCodeForEditor() {
  static thread_local int key_code = 0;
  return key_code;
}

class StandaloneScopedKeyboardEventKeyCodeForEditor {
 public:
  explicit StandaloneScopedKeyboardEventKeyCodeForEditor(int key_code)
      : previous_(StandaloneCurrentKeyboardEventKeyCodeForEditor()) {
    StandaloneCurrentKeyboardEventKeyCodeForEditor() = key_code;
  }
  ~StandaloneScopedKeyboardEventKeyCodeForEditor() {
    StandaloneCurrentKeyboardEventKeyCodeForEditor() = previous_;
  }

 private:
  int previous_;
};

}  // namespace
#endif

KeyboardEventManager::KeyboardEventManager(LocalFrame& frame,
                                           ScrollManager& scroll_manager)
    : frame_(&frame), scroll_manager_(&scroll_manager) {}
void KeyboardEventManager::Trace(Visitor* visitor) const {
  visitor->Trace(frame_);
  visitor->Trace(scroll_manager_);
  visitor->Trace(scrollend_event_target_);
}
bool KeyboardEventManager::HandleAccessKey(const WebKeyboardEvent&) {
  return false;
}
WebInputEventResult KeyboardEventManager::KeyEvent(
    const WebKeyboardEvent& key_event) {
#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
  StandaloneScopedKeyboardEventKeyCodeForEditor standalone_key_code_scope(
      key_event.windows_key_code);
#endif
  if (!frame_ || !frame_->GetDocument() || !frame_->GetDocument()->domWindow()) {
    return WebInputEventResult::kNotHandled;
  }

  Node* node = nullptr;
  if (Element* focused = frame_->GetDocument()->FocusedElement()) {
    node = focused;
  } else if (frame_->GetDocument()->body()) {
    node = frame_->GetDocument()->body();
  } else {
    node = frame_->GetDocument()->documentElement();
  }
  if (!node) {
    return WebInputEventResult::kNotHandled;
  }

  KeyboardEvent* event =
      KeyboardEvent::Create(key_event, frame_->GetDocument()->domWindow());
  event->SetTarget(node);
  const DispatchEventResult dispatch_result = node->DispatchEvent(*event);
  if (dispatch_result == DispatchEventResult::kNotCanceled &&
      !event->DefaultHandled()) {
    DefaultKeyboardEventHandler(event, node);
  }
  return event->DefaultHandled() ||
                 dispatch_result != DispatchEventResult::kNotCanceled
             ? WebInputEventResult::kHandledSystem
             : WebInputEventResult::kNotHandled;
}
void KeyboardEventManager::DefaultKeyboardEventHandler(KeyboardEvent* event,
                                                      Node*) {
  if (!event || !frame_) {
    return;
  }
  frame_->GetEditor().HandleKeyboardEvent(event);
}
void KeyboardEventManager::CapsLockStateMayHaveChanged() {}
WebInputEvent::Modifiers KeyboardEventManager::GetCurrentModifierState() {
  return WebInputEvent::kNoModifiers;
}
bool KeyboardEventManager::CurrentCapsLockState() {
  return false;
}
void KeyboardEventManager::SetCurrentCapsLockState(OverrideCapsLockState) {}

TouchEventManager::TouchEventManager(LocalFrame& frame)
    : frame_(&frame),
      suppressing_touchmoves_within_slop_(false),
      current_touch_action_(TouchAction::kAuto) {}
void TouchEventManager::Trace(Visitor* visitor) const {
  visitor->Trace(frame_);
  visitor->Trace(touch_attribute_map_);
  visitor->Trace(touch_sequence_document_);
}
void TouchEventManager::HandleTouchPoint(
    const WebPointerEvent&,
    const Vector<WebPointerEvent>&,
    const event_handling_util::PointerEventTarget&) {}
WebInputEventResult TouchEventManager::FlushEvents() {
  return WebInputEventResult::kNotHandled;
}
void TouchEventManager::Clear() {
  touch_attribute_map_.clear();
  touch_sequence_document_ = nullptr;
}
void TouchEventManager::HandlePseudoElementRemoval(PseudoElement&) {}
bool TouchEventManager::IsAnyTouchActive() const {
  return false;
}
Node* TouchEventManager::GetTouchPointerNode(
    const WebPointerEvent&,
    const event_handling_util::PointerEventTarget&) {
  return nullptr;
}
void TouchEventManager::UpdateTouchAttributeMapsForPointerDown(
    const WebPointerEvent&,
    Node*,
    TouchAction) {}
Element* TouchEventManager::CurrentTouchDownElement() {
  return nullptr;
}

void WidgetEventHandler::HandleMouseMove(
    LocalFrame&,
    const WebMouseEvent&,
    const std::vector<std::unique_ptr<WebInputEvent>>&,
    const std::vector<std::unique_ptr<WebInputEvent>>&) {}
void WidgetEventHandler::HandleMouseLeave(LocalFrame&, const WebMouseEvent&) {}
void WidgetEventHandler::HandleMouseDown(LocalFrame&, const WebMouseEvent&) {}
WebInputEventResult WidgetEventHandler::HandleMouseUp(LocalFrame&,
                                                      const WebMouseEvent&) {
  return WebInputEventResult::kNotHandled;
}
WebInputEventResult WidgetEventHandler::HandleMouseWheel(
    LocalFrame&,
    const WebMouseWheelEvent&) {
  return WebInputEventResult::kNotHandled;
}
WebInputEventResult WidgetEventHandler::HandlePointerEvent(
    LocalFrame&,
    const WebPointerEvent&,
    const std::vector<std::unique_ptr<WebInputEvent>>&,
    const std::vector<std::unique_ptr<WebInputEvent>>&) {
  return WebInputEventResult::kNotHandled;
}
WebInputEventResult WidgetEventHandler::HandleInputEvent(
    const WebCoalescedInputEvent&,
    LocalFrame*) {
  return WebInputEventResult::kNotHandled;
}

SelectionController::SelectionController(LocalFrame& frame)
    : ExecutionContextLifecycleObserver(nullptr),
      frame_(&frame),
      mouse_down_may_start_select_(false),
      mouse_down_was_single_click_in_selection_(false),
      mouse_down_allows_multi_click_(false),
      selection_state_(SelectionState::kHaveNotStartedSelection) {}
SelectionController::~SelectionController() = default;
void SelectionController::Trace(Visitor* visitor) const {
  visitor->Trace(frame_);
}
bool SelectionController::HandleMousePressEvent(
    const MouseEventWithHitTestResults& event) {
  Node* inner_node = event.InnerNode();
  mouse_down_may_start_select_ =
      ((!inner_node || !inner_node->GetLayoutObject() ||
        inner_node->CanStartSelection()) ||
       IsSelectionOverLink(event)) &&
      !event.GetScrollbar();
  mouse_down_was_single_click_in_selection_ = false;
  mouse_down_allows_multi_click_ = event.Event().click_count == 1;
  selection_state_ = SelectionState::kHaveNotStartedSelection;

#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
  if (event.Event().button == WebPointerProperties::Button::kLeft &&
      event.Event().click_count == 1 && frame_ && frame_->GetDocument()) {
    const PositionWithAffinity position =
        event.GetHitTestResult().GetPosition();
    TextControlElement* control = nullptr;
    if (!position.IsNull())
      control = EnclosingTextControl(position.GetPosition());
    if (!control) {
      if (Node* node = event.InnerNode()) {
        if (auto* element = DynamicTo<Element>(node))
          control = DynamicTo<TextControlElement>(element);
        if (!control && node->IsInShadowTree())
          control = DynamicTo<TextControlElement>(node->OwnerShadowHost());
      }
    }
    if (control && !control->IsDisabledOrReadOnly() && !position.IsNull()) {
      const unsigned index = control->IndexForPosition(position.GetPosition());
      control->SetSelectionRange(index, index);
    }
  }
#endif
  return false;
}
WebInputEventResult SelectionController::HandleMouseDraggedEvent(
    const MouseEventWithHitTestResults&,
    const gfx::Point&,
    const PhysicalOffset&) {
  return WebInputEventResult::kNotHandled;
}
bool SelectionController::HandleMouseReleaseEvent(
    const MouseEventWithHitTestResults&,
    const PhysicalOffset&) {
  return false;
}
bool SelectionController::HandlePasteGlobalSelection(const WebMouseEvent&) {
  return false;
}
bool SelectionController::HandleGestureLongPress(const HitTestResult&) {
  return false;
}
void SelectionController::HandleGestureTwoFingerTap(
    const GestureEventWithHitTestResults&) {}
void SelectionController::UpdateSelectionForMouseDrag(const PhysicalOffset&,
                                                      const PhysicalOffset&) {}
template <typename MouseEventObject>
void SelectionController::UpdateSelectionForContextMenuEvent(
    const MouseEventObject*,
    const HitTestResult&,
    const PhysicalOffset&) {}
template void SelectionController::UpdateSelectionForContextMenuEvent<MouseEvent>(
    const MouseEvent*,
    const HitTestResult&,
    const PhysicalOffset&);
template void
SelectionController::UpdateSelectionForContextMenuEvent<PointerEvent>(
    const PointerEvent*,
    const HitTestResult&,
    const PhysicalOffset&);
void SelectionController::PassMousePressEventToSubframe(
    const MouseEventWithHitTestResults&) {}
void SelectionController::InitializeSelectionState() {
  selection_state_ = SelectionState::kHaveNotStartedSelection;
}
void SelectionController::SetMouseDownMayStartSelect(bool value) {
  mouse_down_may_start_select_ = value;
}
bool SelectionController::MouseDownMayStartSelect() const {
  return mouse_down_may_start_select_;
}
bool SelectionController::MouseDownWasSingleClickInSelection() const {
  return mouse_down_was_single_click_in_selection_;
}
void SelectionController::NotifySelectionChanged() {}
void SelectionController::ContextDestroyed() {}

bool IsSelectionOverLink(const MouseEventWithHitTestResults&) {
  return false;
}

bool IsExtendingSelection(const MouseEventWithHitTestResults&) {
  return false;
}

SelectionInFlatTree AdjustSelectionWithTrailingWhitespace(
    const SelectionInFlatTree& selection) {
  return selection;
}

SelectionInFlatTree AdjustSelectionByUserSelect(
    Node*,
    const SelectionInFlatTree& selection) {
  return selection;
}

FocusChangedObserver::FocusChangedObserver(Page*) {}
bool FocusChangedObserver::IsFrameFocused(LocalFrame*) {
  return false;
}

GestureManager::GestureManager(LocalFrame& frame,
                               ScrollManager& scroll_manager,
                               MouseEventManager& mouse_event_manager,
                               PointerEventManager& pointer_event_manager,
                               SelectionController& selection_controller)
    : FocusChangedObserver(nullptr),
      frame_(&frame),
      scroll_manager_(&scroll_manager),
      mouse_event_manager_(&mouse_event_manager),
      pointer_event_manager_(&pointer_event_manager),
      suppress_mouse_events_from_gestures_(false),
      gesture_context_menu_deferred_(false),
      selection_controller_(&selection_controller) {}

void GestureManager::Trace(Visitor* visitor) const {
  visitor->Trace(frame_);
  visitor->Trace(scroll_manager_);
  visitor->Trace(mouse_event_manager_);
  visitor->Trace(pointer_event_manager_);
}
void GestureManager::Clear() {}
void GestureManager::ResetLongTapContextMenuStates() {}
HitTestRequest::HitTestRequestType GestureManager::GetHitTypeForGestureType(
    WebInputEvent::Type) {
  return HitTestRequest::kReadOnly | HitTestRequest::kActive;
}
WebInputEventResult GestureManager::HandleGestureEventInFrame(
    const GestureEventWithHitTestResults&) {
  return WebInputEventResult::kNotHandled;
}
bool GestureManager::GestureContextMenuDeferred() const {
  return false;
}
void GestureManager::HandleTouchDragEnd(const WebMouseEvent&,
                                        ui::mojom::blink::DragOperation) {}

void DocumentMarkerController::RemoveMarkersForNode(
    const Text&,
    DocumentMarker::MarkerTypes) {}

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

#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
bool HTMLInputElement::IsCheckable() const {
  return false;
}

bool HTMLInputElement::HasBeenPasswordField() const {
  return false;
}
#endif

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




void ScrollMarkerGroupData::ClearFocusGroup() {
  focus_group_.clear();
}

void ScrollMarkerGroupData::ClearScrollableAreaSubscriptions() {}

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

bool Frame::AllowFocusWithoutUserActivation() {
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

void AnchorPositionScrollData::Trace(Visitor* visitor) const {
  PostLayoutSnapshotClient::Trace(visitor);
  visitor->Trace(anchored_element_);
}

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

void DocumentSpeculationRules::LinkGainedOrLostComputedStyle(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::LinkMatchedSelectorsUpdated(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::ChildStyleRecalcBlocked(Element*) {}
void DocumentSpeculationRules::DidStyleChildren(Element*) {}

bool HTMLMenuItemElement::ShouldHaveExpandIcon() const {
  return false;
}

ViewTransition* ViewTransitionUtils::GetTransition(const Element&) {
  return nullptr;
}
#endif

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

VisibleSelection FrameSelection::ComputeVisibleSelectionInDOMTree() const {
  return VisibleSelection();
}

void FrameSelection::SetCaretBlinkingSuspended(bool) {}

Document& FrameSelection::GetDocument() const {
  return *frame_->GetDocument();
}

bool FrameSelection::SelectionHasFocus() const {
  return FrameIsFocusedAndActive();
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

template <typename Strategy>
bool VisibleSelectionTemplate<Strategy>::IsNone() const {
  return true;
}

template <typename Strategy>
bool VisibleSelectionTemplate<Strategy>::IsRange() const {
  return false;
}

template <typename Strategy>
PositionTemplate<Strategy> VisibleSelectionTemplate<Strategy>::Start() const {
  return anchor_;
}

template <typename Strategy>
EphemeralRangeTemplate<Strategy>
VisibleSelectionTemplate<Strategy>::ToNormalizedEphemeralRange() const {
  return EphemeralRangeTemplate<Strategy>();
}

bool IsNodeFullyContained(const EphemeralRange&, const Node&) {
  return false;
}

bool IsInPasswordField(const Position&) {
  return false;
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

LocalCaretRect LocalCaretRectOfPosition(const PositionWithAffinity&,
                                        CaretShape,
                                        EditingBoundaryCrossingRule) {
  return LocalCaretRect();
}

gfx::Rect AbsoluteCaretBoundsOf(const PositionWithAffinity&,
                                CaretShape,
                                EditingBoundaryCrossingRule) {
  return gfx::Rect();
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
  return document.CreateRawElement(tag_name, flags);
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

void FontFaceCache::Add(const StyleRuleFontFace*, FontFace*) {}

EInsideLink VisitedLinkState::DetermineLinkStateSlowCase(const Element&) {
  return EInsideLink::kNotInsideLink;
}

#if 0
void DocumentTimeline::InvalidateKeyframeEffects(
    const TreeScope&,
    const StyleChangeReasonForTracing&) {}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
scoped_refptr<QuotesData> LayoutLocale::GetQuotesData() const {
  return nullptr;
}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
CSSValue* AtRuleDescriptorParser::ParseAtCounterStyleDescriptor(
    AtRuleDescriptorID,
    CSSParserTokenStream&,
    const CSSParserContext&) {
  return nullptr;
}
#endif

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

#if 0
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
                                            const ComputedStyleBuilder&) {
  ++g_standalone_css_animation_timeline_update_called;
}
void CSSAnimations::CalculateAnimationUpdate(CSSAnimationUpdate&,
                                             Element&,
                                             Element&,
                                             const ComputedStyleBuilder&,
                                             const ComputedStyle*,
                                             StyleResolver*,
                                             bool) {
  ++g_standalone_css_animation_update_called;
}
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
                                              bool) {
  ++g_standalone_css_transition_update_called;
}
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
#endif
bool TimelineTrigger::Update() {
  return false;
}

void AnimationTrigger::removeAnimation(Animation*) {}

CSSUnitValue* CSSNumericValue::to(CSSPrimitiveValue::UnitType) const {
  return nullptr;
}

CSSNumericValue* CSSNumericValue::FromCSSValue(const CSSPrimitiveValue&) {
  return nullptr;
}

const char* const V8AnimationPlayState::string_table_[] = {
    "idle", "pending", "running", "paused", "finished"};

const char* const V8ReplaceState::string_table_[] = {
    "active", "removed", "persisted"};
const char* const V8IterationCompositeOperation::string_table_[] = {
    "replace", "accumulate"};

std::unique_ptr<CompositorAnimation> CompositorAnimation::Create(
    std::optional<int>) {
  return nullptr;
}

cc::Animation* CompositorAnimation::CcAnimation() const {
  return nullptr;
}

int CompositorAnimation::CcAnimationId() const {
  return 0;
}

void CompositorAnimation::SetAnimationDelegate(CompositorAnimationDelegate*) {}

void CompositorAnimation::DetachElement() {}

bool CompositorAnimation::IsElementAttached() const {
  return false;
}

void CompositorAnimation::AttachPaintWorkletElement() {}

CompositorAnimations::FailureReasons
CompositorAnimations::CheckCanStartAnimationOnCompositor(
    const Timing&,
    const Timing::NormalizedTiming&,
    const Element&,
    const Animation*,
    const EffectModel&,
    const PaintArtifactCompositor*,
    double,
    PropertyHandleSet*) {
  return CompositorAnimations::kInvalidAnimationOrEffect;
}

bool CompositorAnimations::CompositorPropertyAnimationsHaveNoEffect(
    const Element&,
    const Animation*,
    const EffectModel&,
    const PaintArtifactCompositor*) {
  return false;
}

bool CompositorAnimations::CanStartScrollTimelineOnCompositor(Node*) {
  return false;
}

void CompositorAnimations::StartAnimationOnCompositor(
    const Element&,
    int,
    std::optional<double>,
    std::optional<base::TimeDelta>,
    const Timing&,
    const Timing::NormalizedTiming&,
    const Animation*,
    CompositorAnimation&,
    const EffectModel&,
    Vector<int>&,
    double,
    bool,
    bool) {}

void CompositorAnimations::CancelAnimationOnCompositor(
    const Element&,
    CompositorAnimation*,
    int,
    const EffectModel&) {}

void CompositorAnimations::CancelIncompatibleAnimationsOnCompositor(
    const Element&,
    const Animation&,
    const EffectModel&) {}

void CompositorAnimations::PauseAnimationForTestingOnCompositor(
    const Element&,
    const Animation&,
    int,
    base::TimeDelta,
    const EffectModel&) {}

void CompositorAnimations::AttachCompositedLayers(Element&,
                                                  CompositorAnimation*) {}

const WrapperTypeInfo& CSSAnimation::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSAnimation");
const WrapperTypeInfo& CSSTransition::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("CSSTransition");
const WrapperTypeInfo& AnimationPlaybackEvent::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("AnimationPlaybackEvent");
const WrapperTypeInfo& TimelineTriggerRange::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TimelineTriggerRange");
const WrapperTypeInfo& TimelineTriggerRangeList::wrapper_type_info_ =
    StandaloneWrapperTypeInfo("TimelineTriggerRangeList");

V8UnionStringOrTimelineRangeOffset::V8UnionStringOrTimelineRangeOffset(
    const String& value)
    : content_type_(ContentType::kString), member_string_(value) {}

V8UnionStringOrTimelineRangeOffset::V8UnionStringOrTimelineRangeOffset(
    String&& value)
    : content_type_(ContentType::kString), member_string_(std::move(value)) {}

void V8UnionStringOrTimelineRangeOffset::Trace(Visitor* visitor) const {
  visitor->Trace(member_timeline_range_offset_);
}

void V8UnionStringOrTimelineRangeOffset::Clear() {
  member_string_ = String();
  member_timeline_range_offset_ = nullptr;
}

AnimationPlaybackEvent::AnimationPlaybackEvent(
    const AtomicString& type,
    V8CSSNumberish* current_time,
    V8CSSNumberish* timeline_time)
    : Event(type, Bubbles::kNo, Cancelable::kNo),
      current_time_(current_time),
      timeline_time_(timeline_time) {}

AnimationPlaybackEvent::AnimationPlaybackEvent(
    const AtomicString& type,
    const AnimationPlaybackEventInit*)
    : Event(type, Bubbles::kNo, Cancelable::kNo) {}

AnimationPlaybackEvent::~AnimationPlaybackEvent() = default;

const AtomicString& AnimationPlaybackEvent::InterfaceName() const {
  return event_interface_names::kEvent;
}

void AnimationPlaybackEvent::Trace(Visitor* visitor) const {
  TraceIfNeeded<Member<V8CSSNumberish>>::Trace(visitor, current_time_);
  TraceIfNeeded<Member<V8CSSNumberish>>::Trace(visitor, timeline_time_);
  Event::Trace(visitor);
}

TimelineTriggerRange::TimelineTriggerRange(
    AnimationTimeline* timeline,
    Boundary* activation_range_start,
    Boundary* activation_range_end,
    Boundary* active_range_start,
    Boundary* active_range_end)
    : timeline_(timeline),
      activation_range_start_(activation_range_start),
      activation_range_end_(activation_range_end),
      active_range_start_(active_range_start),
      active_range_end_(active_range_end),
      state_(State::kIdle) {}

AnimationTimeline* TimelineTriggerRange::timeline() {
  return timeline_.Get();
}

const TimelineTriggerRange::Boundary*
TimelineTriggerRange::activationRangeStart(ExecutionContext*) {
  return activation_range_start_.Get();
}

const TimelineTriggerRange::Boundary*
TimelineTriggerRange::activationRangeEnd(ExecutionContext*) {
  return activation_range_end_.Get();
}

const TimelineTriggerRange::Boundary*
TimelineTriggerRange::activeRangeStart(ExecutionContext*) {
  return active_range_start_.Get();
}

const TimelineTriggerRange::Boundary*
TimelineTriggerRange::activeRangeEnd(ExecutionContext*) {
  return active_range_end_.Get();
}

void TimelineTriggerRange::Trace(Visitor* visitor) const {
  visitor->Trace(timeline_);
  visitor->Trace(activation_range_start_);
  visitor->Trace(activation_range_end_);
  visitor->Trace(active_range_start_);
  visitor->Trace(active_range_end_);
  ScriptWrappable::Trace(visitor);
}

TimelineTriggerRangeList::TimelineTriggerRangeList(
    const HeapVector<Member<TimelineTriggerRange>>& ranges)
    : ranges_(ranges) {}

void TimelineTriggerRangeList::Trace(Visitor* visitor) const {
  visitor->Trace(ranges_);
  ScriptWrappable::Trace(visitor);
}

TimelineTriggerRangeList* TimelineTriggerRangeList::Create(
    ExecutionContext*,
    const HeapVector<Member<TimelineTriggerOptions>>&,
    ExceptionState&) {
  return nullptr;
}

TimelineTriggerRange* TimelineTriggerRangeList::item(unsigned index) {
  if (index < ranges_.size())
    return ranges_[index].Get();
  return nullptr;
}

TimelineTrigger::TimelineTrigger(TimelineTriggerRangeList* ranges,
                                 Element* owning_element)
    : ranges_(ranges), state_(State::kIdle) {
  owning_element_ = owning_element;
}

bool TimelineTrigger::CanTrigger() const {
  return false;
}

bool TimelineTrigger::IsTimelineTrigger() const {
  return true;
}

bool AnimationTrigger::IsTimelineTrigger() const {
  return false;
}

bool AnimationTrigger::IsEventTrigger() const {
  return false;
}

void TimelineTrigger::Trace(Visitor* visitor) const {
  visitor->Trace(ranges_);
  AnimationTrigger::Trace(visitor);
}

void TimelineTrigger::CreateCompositorTrigger() {}

void TimelineTrigger::WillAddAnimation(Animation*,
                                       Behavior,
                                       Behavior,
                                       ExceptionState&) {}

void TimelineTrigger::DidAddAnimation() {}

void TimelineTrigger::DidRemoveAnimation(Animation*) {}

void TimelineTrigger::NotifyActivated(base::TimeTicks) {}

void TimelineTrigger::NotifyDeactivated(base::TimeTicks) {}

void AnimationTrigger::Dispose() {}

void AnimationTrigger::DestroyCompositorTrigger() {
  compositor_trigger_ = nullptr;
}

void AnimationTrigger::Trace(Visitor* visitor) const {
  visitor->Trace(owning_element_);
  visitor->Trace(animation_behavior_map_);
  ScriptWrappable::Trace(visitor);
}

void AnimationTrigger::WillAddAnimation(Animation*,
                                        Behavior,
                                        Behavior,
                                        ExceptionState&) {}

void AnimationTrigger::DidAddAnimation() {}

void AnimationTrigger::DidRemoveAnimation(Animation*) {}

void StyleTriggerAttachment::Attach(AnimationTrigger&,
                                    const NamingScope&,
                                    CSSAnimation&) const {}

void WorkletAnimationController::UpdateAnimationTimings(TimingUpdateReason) {}
void WorkletAnimationController::UpdateAnimationStates() {}
void AnimationTrigger::UpdateCompositorTrigger(const PaintArtifactCompositor*) {}

Timing TimingInput::Convert(
    const V8UnionKeyframeEffectOptionsOrUnrestrictedDouble*,
    Document*,
    ExceptionState&) {
  return Timing();
}

Timing TimingInput::Convert(
    const V8UnionKeyframeAnimationOptionsOrUnrestrictedDouble*,
    Document*,
    ExceptionState&) {
  return Timing();
}

KeyframeEffectModelBase* EffectInput::Convert(Element*,
                                              const ScriptValue&,
                                              EffectModel::CompositeOperation,
                                              ScriptState*,
                                              ExceptionState&) {
  return nullptr;
}

StringKeyframeVector EffectInput::ParseKeyframesArgument(Element*,
                                                         const ScriptValue&,
                                                         ScriptState*,
                                                         ExceptionState&) {
  return StringKeyframeVector();
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

EffectTiming* Timing::ConvertToEffectTiming() const {
  return nullptr;
}

Timing::FillMode Timing::ResolvedFillMode(bool is_keyframe_effect) const {
  if (fill_mode != Timing::FillMode::AUTO)
    return fill_mode;

  if (is_keyframe_effect)
    return Timing::FillMode::NONE;
  return Timing::FillMode::BOTH;
}

Timing::CalculatedTiming Timing::CalculateTimings(
    std::optional<AnimationTimeDelta> local_time,
    bool is_idle,
    const NormalizedTiming& normalized_timing,
    AnimationDirection animation_direction,
    bool is_keyframe_effect,
    std::optional<double> playback_rate,
    bool paused_for_trigger,
    bool is_endpoint_inclusive) const {
  const AnimationTimeDelta active_duration = normalized_timing.active_duration;
  const AnimationTimeDelta duration = normalized_timing.iteration_duration;

  Timing::Phase current_phase = TimingCalculations::CalculatePhase(
      normalized_timing, local_time, animation_direction, paused_for_trigger,
      is_endpoint_inclusive);

  const std::optional<AnimationTimeDelta> active_time =
      TimingCalculations::CalculateActiveTime(
          normalized_timing, ResolvedFillMode(is_keyframe_effect), local_time,
          current_phase);

  std::optional<double> progress;

  const std::optional<double> overall_progress =
      TimingCalculations::CalculateOverallProgress(
          current_phase, active_time, duration, iteration_count,
          iteration_start);
  const std::optional<double> simple_iteration_progress =
      TimingCalculations::CalculateSimpleIterationProgress(
          current_phase, overall_progress, iteration_start, active_time,
          active_duration, iteration_count);
  const std::optional<double> current_iteration =
      TimingCalculations::CalculateCurrentIteration(
          current_phase, active_time, iteration_count, overall_progress,
          simple_iteration_progress);
  const bool current_direction_is_forwards =
      TimingCalculations::IsCurrentDirectionForwards(current_iteration,
                                                     direction);
  const std::optional<double> directed_progress =
      TimingCalculations::CalculateDirectedProgress(
          simple_iteration_progress, current_iteration, direction);

  progress = TimingCalculations::CalculateTransformedProgress(
      current_phase, directed_progress, current_direction_is_forwards,
      timing_function);

  AnimationTimeDelta time_to_next_iteration = AnimationTimeDelta::Max();
  if (!duration.is_zero()) {
    const AnimationTimeDelta start_offset =
        TimingCalculations::MultiplyZeroAlwaysGivesZero(duration,
                                                        iteration_start);
    const std::optional<AnimationTimeDelta> offset_active_time =
        TimingCalculations::CalculateOffsetActiveTime(
            active_duration, active_time, start_offset);
    const std::optional<AnimationTimeDelta> iteration_time =
        TimingCalculations::CalculateIterationTime(
            duration, active_duration, offset_active_time, start_offset,
            current_phase, *this);
    if (iteration_time) {
      time_to_next_iteration = duration - iteration_time.value();
      if (active_duration - active_time.value() < time_to_next_iteration)
        time_to_next_iteration = AnimationTimeDelta::Max();
    }
  }

  CalculatedTiming calculated = CalculatedTiming();
  calculated.phase = current_phase;
  calculated.current_iteration = current_iteration;
  calculated.progress = progress;
  calculated.is_in_effect = active_time.has_value();
  calculated.is_in_play = calculated.phase == Timing::kPhaseActive;
  calculated.is_current =
      calculated.is_in_play ||
      (playback_rate.has_value() && playback_rate > 0 &&
       calculated.phase == Timing::kPhaseBefore) ||
      (playback_rate.has_value() && playback_rate < 0 &&
       calculated.phase == Timing::kPhaseAfter) ||
      (!is_idle && normalized_timing.timeline_duration);
  calculated.local_time = local_time;
  calculated.time_to_next_iteration = time_to_next_iteration;

  return calculated;
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

#if 0
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
#endif

void ExceptionState::ThrowTypeError(const String&) {
  had_exception_ = true;
}
void ExceptionState::ThrowDOMException(DOMExceptionCode, const String&) {
  had_exception_ = true;
}
void ExceptionState::ThrowDOMException(DOMExceptionCode, const char*) {
  had_exception_ = true;
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

#if 0
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
                                          bool) {
  ++g_standalone_document_animations_update_called;
}
void DocumentAnimations::UpdateAnimationTimingForAnimationFrame() {}
size_t DocumentAnimations::GetAnimationsCount() {
  return 0;
}
void DocumentAnimations::Trace(Visitor*) const {}
void PendingAnimations::TimerFired(TimerBase*) {}
void PendingAnimations::Trace(Visitor*) const {}
#endif
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

gfx::Size PaintLayerScrollableArea::ContentsSize() const {
  LayoutBox* box = GetLayoutBox();
  return PixelSnappedContentsSize(
      PhysicalOffset(box ? box->ClientLeft() : LayoutUnit(),
                     box ? box->ClientTop() : LayoutUnit()));
}
void PaintLayerScrollableArea::EnqueueScrollEventIfNeeded() {}
PaintLayer* PaintLayerScrollableArea::Layer() const {
  return layer_.Get();
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
void PaintLayerScrollableArea::Trace(Visitor* visitor) const {
  visitor->Trace(scrollbar_manager_);
  visitor->Trace(layer_);
  visitor->Trace(scroll_anchor_);
  visitor->Trace(rare_data_);
  visitor->Trace(scroll_corner_display_item_client_);
  ScrollableArea::Trace(visitor);
}
CompositorElementId PaintLayerScrollableArea::GetScrollElementId() const {
  return CompositorElementIdFromUniqueObjectId(
      GetLayoutBox()->UniqueId(), CompositorElementIdNamespace::kScroll);
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PaintPropertyTreeBuilder::DirectlyUpdateOpacityValue(
    const LayoutObject&) {}
void PaintPropertyTreeBuilder::DirectlyUpdateTransformMatrix(
    const LayoutObject&) {}
#endif
void PaintTimingDetector::NotifyPaintFinished() {}
void PaintTiming::MarkPaintTiming() {}
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
bool FrameView::RectInParentIsStable(const base::TimeTicks&) const {
  return true;
}
bool FrameView::RectInParentIsStableForIOv2(const base::TimeTicks&) const {
  return true;
}
void RemoteFrameView::UpdateCompositingScaleFactor() {}
void RemoteFrameView::UpdateCompositingRect() {}
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PhysicalRect LayoutReplaced::ReplacedContentRect() const {
  return PhysicalRect();
}
#endif
FragmentAnchor* FragmentAnchor::TryCreate(const KURL&, LocalFrame&, bool) {
  return nullptr;
}
void HTMLPlugInElement::UpdatePlugin() {}
WebPluginContainerImpl* PluginDocument::GetPluginView() {
  return nullptr;
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
  frame_->DomWindow()->SetContentSecurityPolicy(
      MakeGarbageCollected<ContentSecurityPolicy>());
  DocumentInit init = DocumentInit::Create()
                          .WithWindow(frame_->DomWindow(), nullptr)
                          .WithToken(document_token)
                          .ForInitialEmptyDocument(true)
                          .WithTypeFrom("text/html")
                          .WithUkmSourceId(document_ukm_source_id);
  Document* document = frame_->DomWindow()->InstallNewDocument(init);
#if defined(HTML_CSS_RENDERER_STANDALONE)
  Element* html = MakeGarbageCollected<HTMLHtmlElement>(*document);
  Element* body = MakeGarbageCollected<HTMLBodyElement>(*document);
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
void FrameSelection::InvalidatePaint(const LayoutBlock&,
                                     const PaintInvalidatorContext&) {}
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
void FrameSelection::Clear() {
  granularity_ = TextGranularity::kCharacter;
  is_handle_visible_ = false;
  is_directional_ = false;
}
String FrameSelection::SelectedText() const {
  return String();
}
String FrameSelection::SelectedText(const TextIteratorBehavior&) const {
  return String();
}
String FrameSelection::SelectedTextForClipboard() const {
  return String();
}
String FrameSelection::SelectedHTMLForClipboard() const {
  return String();
}
void FrameSelection::SelectSubString(const Element&, int, int) {}
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
#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
  if (!frame_ || !frame_->GetDocument()) {
    return false;
  }
  auto* control =
      DynamicTo<TextControlElement>(frame_->GetDocument()->FocusedElement());
  return control && !control->IsDisabledOrReadOnly();
#else
  return false;
#endif
}

#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
namespace {

TextControlElement* StandaloneTextControlFromEditingEvent(LocalFrame* frame,
                                                          Event* event) {
  if (!frame || !frame->GetDocument()) {
    return nullptr;
  }
  if (event && event->RawTarget()) {
    if (Node* node = event->RawTarget()->ToNode()) {
      if (auto* control = DynamicTo<TextControlElement>(node)) {
        return control;
      }
      if (node->IsInShadowTree()) {
        if (auto* control =
                DynamicTo<TextControlElement>(node->OwnerShadowHost())) {
          return control;
        }
      }
    }
  }
  return DynamicTo<TextControlElement>(frame->GetDocument()->FocusedElement());
}

bool StandaloneApplyTextControlEditFromEditor(TextControlElement& control,
                                              const String& replacement,
                                              bool delete_backward,
                                              bool delete_forward) {
  if (control.IsDisabledOrReadOnly()) {
    return false;
  }
  unsigned start = control.selectionStart();
  unsigned end = control.selectionEnd();
  if (start > end) {
    std::swap(start, end);
  }
  const String original = control.InnerEditorValue();
  start = std::min<unsigned>(start, original.length());
  end = std::min<unsigned>(end, original.length());
  if (delete_backward && start == end && start > 0) {
    --start;
  } else if (delete_forward && start == end && end < original.length()) {
    ++end;
  }
  if (replacement.empty() && start == end) {
    return false;
  }

  StringBuilder edited;
  edited.Append(StringView(original, 0, start));
  edited.Append(replacement);
  edited.Append(StringView(original, end));
  const unsigned caret = start + replacement.length();

  control.SetValueBeforeFirstUserEditIfNotSet();
  control.SetValue(edited.ToString(),
                   TextFieldEventBehavior::kDispatchInputEvent,
                   TextControlSetValueSelection::kDoNotSet);
  control.SetSelectionRange(caret, caret);
  return true;
}

}  // namespace
#endif

bool Editor::HandleTextEvent(TextEvent* event) {
#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
  if (!frame_ || !frame_->GetDocument() || !event) {
    return false;
  }
  TextControlElement* control =
      StandaloneTextControlFromEditingEvent(frame_.Get(), event);
  if (!control || control->IsDisabledOrReadOnly() || event->IsDrop() ||
      event->IsPaste() || event->IsIncrementalInsertion()) {
    return false;
  }

  const String data = event->data();
  if (data.empty()) {
    return false;
  }
  return StandaloneApplyTextControlEditFromEditor(
      *control, data, /*delete_backward=*/false, /*delete_forward=*/false);
#else
  return false;
#endif
}
void Editor::HandleKeyboardEvent(KeyboardEvent* event) {
#if HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
  if (!event) {
    return;
  }
  const WebKeyboardEvent* key_event = event->KeyEvent();
  const bool is_editing_key_event =
      event->type() == event_type_names::kKeydown ||
      event->type() == event_type_names::kKeypress ||
      (key_event &&
       (key_event->GetType() == WebInputEvent::Type::kRawKeyDown ||
        key_event->GetType() == WebInputEvent::Type::kKeyDown ||
        key_event->GetType() == WebInputEvent::Type::kChar));
  if (!is_editing_key_event) {
    return;
  }
  TextControlElement* control =
      StandaloneTextControlFromEditingEvent(frame_.Get(), event);
  if (!control || control->IsDisabledOrReadOnly()) {
    return;
  }

  bool handled = false;
  int key_code = event->keyCode();
  if (!key_code && key_event) {
    key_code = key_event->windows_key_code;
  }
  if (!key_code) {
    key_code = StandaloneCurrentKeyboardEventKeyCodeForEditor();
  }
  switch (key_code) {
    case 8:
      handled = StandaloneApplyTextControlEditFromEditor(
          *control, g_empty_string, /*delete_backward=*/true,
          /*delete_forward=*/false);
      break;
    case 46:
      handled = StandaloneApplyTextControlEditFromEditor(
          *control, g_empty_string, /*delete_backward=*/false,
          /*delete_forward=*/true);
      break;
    case 13:
      if (IsA<HTMLTextAreaElement>(*control)) {
        handled = StandaloneApplyTextControlEditFromEditor(
            *control, String("\n"), /*delete_backward=*/false,
            /*delete_forward=*/false);
      }
      break;
    default:
      break;
  }
  if (handled) {
    event->SetDefaultHandled();
  }
#endif
}
void Editor::SetBaseWritingDirection(mojo_base::mojom::TextDirection) {}
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
DataObject* DataObject::Create() {
  return MakeGarbageCollected<DataObject>();
}
DataObject::DataObject() : modifiers_(0) {}
DataObject::~DataObject() = default;
void DataObject::Trace(Visitor* visitor) const {
  visitor->Trace(item_list_);
  visitor->Trace(observers_);
  Supplementable<DataObject>::Trace(visitor);
}

void DataObjectItem::Trace(Visitor* visitor) const {
  visitor->Trace(file_);
  visitor->Trace(system_clipboard_);
}

void FileList::Trace(Visitor* visitor) const {
  visitor->Trace(files_);
  ScriptWrappable::Trace(visitor);
}

DataTransfer* DataTransfer::Create() {
  return MakeGarbageCollected<DataTransfer>(
      kCopyAndPaste, DataTransferAccessPolicy::kWritable, DataObject::Create());
}
DataTransfer* DataTransfer::Create(DataTransferType type,
                                   DataTransferAccessPolicy policy,
                                   DataObject* data_object) {
  return MakeGarbageCollected<DataTransfer>(type, policy, data_object);
}
DataTransfer::DataTransfer(DataTransferType type,
                           DataTransferAccessPolicy policy,
                           DataObject* data_object)
    : policy_(policy),
      transfer_type_(type),
      data_object_(data_object),
      data_store_item_list_changed_(false) {}
DataTransfer::~DataTransfer() = default;
void DataTransfer::ClearDragImage() {
  drag_image_ = nullptr;
  drag_image_element_ = nullptr;
  drag_loc_ = gfx::Point();
}
void DataTransfer::resetDropEffect() {
  drop_effect_ = AtomicString();
}
void DataTransfer::SetDestinationOperationFromEffectAllowed() {}
void DataTransfer::SetDestinationOperation(ui::mojom::blink::DragOperation) {}
void DataTransfer::SetAccessPolicy(DataTransferAccessPolicy policy) {
  policy_ = policy;
}
DataObject* DataTransfer::GetDataObject() const {
  return data_object_.Get();
}
void DataTransfer::OnItemListChanged() {
  data_store_item_list_changed_ = true;
}
void DataTransfer::Trace(Visitor* visitor) const {
  visitor->Trace(data_object_);
  visitor->Trace(drag_image_);
  visitor->Trace(drag_image_element_);
  visitor->Trace(files_);
  ScriptWrappable::Trace(visitor);
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
void ContextLifecycleNotifier::NotifyContextDestroyed() {}
void WindowPerformance::ClearForWindowReuse(LocalDOMWindow&) {}
v8::Local<v8::Value> ScriptWrappable::ToV8(ScriptState*) {
  return v8::Local<v8::Value>();
}
TrustedTypePolicyFactory::TrustedTypePolicyFactory(ExecutionContext* context)
    : ExecutionContextClient(context) {}
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
bool AttributionSrcLoader::CanRegister(const KURL&, HTMLElement*, bool) {
  return false;
}
std::optional<Impression> AttributionSrcLoader::RegisterNavigation(
    const KURL&,
    const std::vector<WebString>&,
    bool,
    network::mojom::ReferrerPolicy) {
  return std::nullopt;
}
void FontFaceSetDocument::DidLayout(Document&) {}
void PaintLayerScrollableArea::UpdateAllStickyConstraints() {
  LayoutBox* layout_box = GetLayoutBox();
  if (!layout_box)
    return;
  PaintLayer* layer = Layer();
  if (!layer)
    return;
  for (const auto& fragment : layout_box->PhysicalFragments()) {
    for (const auto& item : fragment.StickyDescendants()) {
      if (auto* sticky_descendant = item.GetIfConsumed()) {
        StickyConstraintsData data =
            sticky_descendant->ComputeStickyPositionConstraints(
                *layer, item.ConsumedAxes());
        sticky_descendant->SetStickyConstraints(data);
        sticky_descendant->StickyConstraints().ComputeStickyOffset(
            ScrollPosition(), item.ConsumedAxes());
      }
    }
  }
}
void PaintLayerScrollableArea::EnqueueForStickyUpdateIfNeeded() {
  LayoutBox* layout_box = GetLayoutBox();
  if (!layout_box)
    return;
  LocalFrameView* frame_view = layout_box->GetFrameView();
  if (!frame_view)
    return;
  for (const auto& fragment : layout_box->PhysicalFragments()) {
    if (fragment.HasConsumedStickyDescendants()) {
      frame_view->AddPendingStickyUpdate(this);
      break;
    }
  }
}
LayoutBox* PaintLayerScrollableArea::GetLayoutBox() const {
  return layer_ ? layer_->GetLayoutBox() : nullptr;
}
gfx::Rect PaintLayerScrollableArea::VisibleContentRect(
    IncludeScrollbarsInRect) const {
  const PhysicalRect layout_content_rect(LayoutContentRect(kExcludeScrollbars));
  return gfx::Rect(ToFlooredPoint(layout_content_rect.offset),
                   ToRoundedSize(layout_content_rect.size));
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
void LayoutShiftTracker::NotifyChangeEvent() {}
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
void DragCaret::InvalidatePaint(const LayoutBlock&,
                                const PaintInvalidatorContext&) {}
bool SnapCoordinator::UpdateSnapContainerData(LayoutBox&) {
  return false;
}
bool PaintLayerScrollableArea::HasRunningAnimation() {
  return false;
}
void ScrollMarkerGroupPseudoElement::ScrollSelectedIntoView(bool) {}

DOMRectList::DOMRectList() = default;
DOMRect::DOMRect(double x, double y, double width, double height)
    : DOMRectReadOnly(x, y, width, height) {}
DOMRect* DOMRect::FromRectF(const gfx::RectF& rect) {
  return MakeGarbageCollected<DOMRect>(rect.x(), rect.y(), rect.width(),
                                       rect.height());
}

bool IsTrustedTypesEventHandlerAttribute(const QualifiedName&) { return false; }
String GetTrustedTypesLiteral(const ScriptValue&, ScriptState*) {
  return String();
}
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
void Performance::NotifyNavigationTimingToObservers() {}
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
void PageAnimator::ServiceScriptedAnimations(base::TimeTicks) {
  ++g_standalone_page_animator_service_called;
}
void PageAnimator::UpdateLifecycleToLayoutClean(LocalFrame&,
                                                DocumentUpdateReason) {}
void PageAnimator::UpdateAllLifecyclePhasesExceptPaint(
    LocalFrame&,
    DocumentUpdateReason) {}
void PageAnimator::UpdateAllLifecyclePhases(LocalFrame&,
                                            DocumentUpdateReason) {}
void PageAnimator::PostAnimate() {}
HeapVector<Member<Animation>> PageAnimator::GetAnimations(const TreeScope&) {
  return HeapVector<Member<Animation>>();
}
void PageAnimator::SetHasCanvasInvalidation() {}
void PageAnimator::SetCurrentFrameHadRaf() {}
void PageAnimator::SetNextFrameHasPendingRaf() {}
void PageAnimator::SetHasViewTransition(bool) {}
void AutoscrollController::Trace(Visitor*) const {}
AutoscrollController::AutoscrollController(Page& page)
    : page_(&page),
      autoscroll_type_(kNoAutoscroll),
      middle_click_mode_(kMiddleClickInitial) {}
void AutoscrollController::StopMiddleClickAutoscroll(LocalFrame*) {}
void AutoscrollController::StopAutoscrollIfNeeded(LayoutObject*) {}
void AutoscrollController::Animate() {}
bool AutoscrollController::SelectionAutoscrollInProgress() const {
  return false;
}
bool AutoscrollController::MiddleClickAutoscrollInProgress() const {
  return false;
}
void DragCaret::Trace(Visitor*) const {}
DragCaret::DragCaret() : display_item_client_(nullptr) {}
void DragController::Trace(Visitor*) const {}
DragController::DragController(Page* page)
    : ExecutionContextLifecycleObserver(nullptr),
      page_(page),
      drag_state_(MakeGarbageCollected<DragState>()),
      document_is_handling_drag_(false) {}
Node* DragController::DraggableNode(const LocalFrame*,
                                    Node*,
                                    const gfx::Point&,
                                    SelectionDragPolicy,
                                    DragSourceAction&) const {
  return nullptr;
}
bool DragController::PopulateDragDataTransfer(LocalFrame*,
                                              const DragState&,
                                              const gfx::Point&) {
  return false;
}
bool DragController::StartDrag(LocalFrame*,
                               const DragState&,
                               const WebMouseEvent&,
                               const gfx::Point&) {
  return false;
}
DragState& DragController::GetDragState() {
  return *drag_state_;
}
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
bool Editor::FindString(LocalFrame&, const String&, FindOptions) {
  return false;
}
void SyncScrollAttemptHeuristic::DidAccessScrollOffset() {}
void SyncScrollAttemptHeuristic::DidSetScrollOffset() {}
void SyncScrollAttemptHeuristic::DidRequestAnimationFrame() {}
ScrollToOptions::ScrollToOptions() = default;
void ScrollToOptions::Trace(Visitor*) const {}
V8FrameCallback::V8FrameCallback(V8FrameRequestCallback*) {}
void V8FrameCallback::Trace(Visitor*) const {}
void V8FrameCallback::Invoke(double) {}
CustomElementRegistry::CustomElementRegistry(const LocalDOMWindow*) {}
void CustomElementRegistry::AssociatedWith(Document&) {}
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
Element* PointerLockController::GetPointerLockedElement(LocalFrame*) {
  return nullptr;
}
void Fullscreen::ElementRemoved(Element&) {}
Element* Fullscreen::FullscreenElementFrom(Document&) {
  return nullptr;
}
bool Fullscreen::HasFullscreenElements() {
  return false;
}
#if 0
void CSSAnimations::Cancel() {}
void CSSAnimations::MaybeApplyPendingUpdate(Element*) {}
#endif
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
void OverscrollAreaTracker::RemoveOverscroll(Element*) {}

void StyleAdjuster::AdjustStyleForDisplay(ComputedStyleBuilder& builder,
                                          const ComputedStyle& layout_parent_style,
                                          const Element*,
                                          Document*) {
  if (layout_parent_style.BlockifiesChildren()) {
    builder.SetIsInBlockifyingDisplay();
    if (builder.Display() != EDisplay::kContents) {
      builder.SetDisplay(StandaloneEquivalentBlockDisplay(builder.Display()));
      if (!builder.HasOutOfFlowPosition()) {
        builder.SetIsFlexOrGridOrCustomItem();
      }
    }

    if (layout_parent_style.IsDisplayFlexibleOrGridBox() ||
        layout_parent_style.IsDisplayGridLanesBox() ||
        layout_parent_style.IsDisplayMathType()) {
      builder.SetIsInsideDisplayIgnoringFloatingChildren();
    }
  }
}

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
Vector<char> ParseMultipartBoundary(const AtomicString&) {
  return Vector<char>();
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
void FontPerformance::MarkDomContentLoaded() {}
void FrameLoader::FinishedParsing() {}
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
IntersectionObserverController::IntersectionObserverController(
    ExecutionContext* context)
    : ExecutionContextClient(context) {}
ElementIntersectionObserverData::ElementIntersectionObserverData() = default;
ScriptRegexp* EmailInputType::CreateEmailRegexp(v8::Isolate*) {
  return nullptr;
}
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
VisitedLinkState::VisitedLinkState(const Document& document)
    : document_(document) {}
void VisitedLinkState::Trace(Visitor* visitor) const {
  visitor->Trace(document_);
}
void FrameViewAutoSizeInfo::Trace(Visitor*) const {}
bool FrameViewAutoSizeInfo::AutoSizeIfNeeded() {
  return false;
}
void FrameViewAutoSizeInfo::Clear() {}
void WebPluginContainerImpl::Trace(Visitor*) const {}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void TransformPaintPropertyNode::State::Trace(Visitor*) const {}
#endif
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
void RenderBlockingResourceManager::Trace(Visitor*) const {}
void CookieJar::Trace(Visitor*) const {}
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
void ViewTransition::SkipTransition(PromiseResponse) {}
CanvasFontCache::~CanvasFontCache() = default;
void CanvasFontCache::Trace(Visitor*) const {}
void ElementDataCache::Trace(Visitor*) const {}
void V8UnionStringOrTrustedHTML::Trace(Visitor* visitor) const {
  visitor->Trace(member_trusted_html_);
}
void ViewTransitionSupplement::Trace(Visitor*) const {}
void NodeIterator::Trace(Visitor*) const {}
void Range::Trace(Visitor*) const {}
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
void MediaQueryMatcher::MediaFeaturesChanged() {}
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
const Vector<network::mojom::blink::ContentSecurityPolicyPtr>&
ContentSecurityPolicy::GetParsedPolicies() const {
  static const Vector<network::mojom::blink::ContentSecurityPolicyPtr> policies;
  return policies;
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
void MediaQueryMatcher::DocumentDetached() {}
AXObjectCache* AXObjectCache::Create(Document&, const ui::AXMode&) {
  return nullptr;
}
CanvasFontCache::CanvasFontCache(Document&) {}
bool LazyImageHelper::LoadAllImagesAndBlockLoadEvent(Document&) {
  return false;
}
void LazyImageHelper::StartMonitoring(Element*) {}
void LazyImageHelper::StopMonitoring(Element*) {}
bool LazyImageHelper::ShouldDeferImageLoad(LocalFrame&, HTMLImageElement*) {
  return false;
}
void CookieJar::InvalidateCache() {}
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
String ExceptionMessages::ArgumentNullOrIncorrectType(int,
                                                      const String&) {
  return String();
}
void ResourceLoadScheduler::LoosenThrottlingPolicy() {}
void ViewTransitionSupplement::WillInsertBody() {}
void RenderBlockingResourceManager::WillInsertDocumentBody() {}
void FrameLoader::DidFinishNavigation(FrameLoader::NavigationFinishState) {}
void HttpRefreshScheduler::MaybeStartTimer() {}
void DetectJavascriptFrameworksOnLoad(Document&) {}
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
NodeChildRemovalTracker* NodeChildRemovalTracker::last_ = nullptr;
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

Element* EnclosingAnchorElement(const Position&) {
  return nullptr;
}

void FrameSelection::DidChangeFocus() {}
void FrameSelection::SetFrameIsFocused(bool flag) {
  focused_ = flag;
}
bool FrameSelection::FrameIsFocusedAndActive() const {
  return focused_ && frame_->GetPage() &&
         frame_->GetPage()->GetFocusController().IsActive();
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
void ExceptionState::ThrowSecurityError(const String&, const String&) {
  had_exception_ = true;
}
void ScriptController::UpdateSecurityOrigin(const SecurityOrigin*) {}
EventInit::EventInit() = default;
EventInit::EventInit(v8::Isolate*) : EventInit() {}
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

UIEventInit::UIEventInit() = default;
UIEventInit::UIEventInit(v8::Isolate*) : UIEventInit() {}
void UIEventInit::Trace(Visitor* visitor) const {
  EventInit::Trace(visitor);
  visitor->Trace(member_source_capabilities_);
  visitor->Trace(member_view_);
}

EventModifierInit::EventModifierInit() = default;
EventModifierInit::EventModifierInit(v8::Isolate*) : EventModifierInit() {}
void EventModifierInit::Trace(Visitor* visitor) const {
  UIEventInit::Trace(visitor);
}

MouseEventInit::MouseEventInit() = default;
MouseEventInit::MouseEventInit(v8::Isolate*) : MouseEventInit() {}
void MouseEventInit::setRegion(const String& value) {
  member_region_ = value;
}
void MouseEventInit::setRegion(String&& value) {
  member_region_ = std::move(value);
}
void MouseEventInit::Trace(Visitor* visitor) const {
  EventModifierInit::Trace(visitor);
  visitor->Trace(member_related_target_);
}

PointerEventInit::PointerEventInit() = default;
PointerEventInit::PointerEventInit(v8::Isolate*) : PointerEventInit() {}
void PointerEventInit::setCoalescedEvents(
    const HeapVector<Member<PointerEvent>>& value) {
  member_coalesced_events_ = value;
}
void PointerEventInit::setCoalescedEvents(
    HeapVector<Member<PointerEvent>>&& value) {
  member_coalesced_events_ = std::move(value);
}
void PointerEventInit::setPointerType(const String& value) {
  member_pointer_type_ = value;
}
void PointerEventInit::setPointerType(String&& value) {
  member_pointer_type_ = std::move(value);
}
void PointerEventInit::setPredictedEvents(
    const HeapVector<Member<PointerEvent>>& value) {
  member_predicted_events_ = value;
}
void PointerEventInit::setPredictedEvents(
    HeapVector<Member<PointerEvent>>&& value) {
  member_predicted_events_ = std::move(value);
}
void PointerEventInit::Trace(Visitor* visitor) const {
  MouseEventInit::Trace(visitor);
  visitor->Trace(member_coalesced_events_);
  visitor->Trace(member_predicted_events_);
}

DragEventInit::DragEventInit() = default;
DragEventInit::DragEventInit(v8::Isolate*) : DragEventInit() {}
void DragEventInit::Trace(Visitor* visitor) const {
  MouseEventInit::Trace(visitor);
  visitor->Trace(member_data_transfer_);
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
const PositionTemplate<Strategy>&
SelectionTemplate<Strategy>::ComputeStartPosition() const {
  return anchor_;
}
template <typename Strategy>
const PositionTemplate<Strategy>&
SelectionTemplate<Strategy>::ComputeEndPosition() const {
  return focus_;
}
template <typename Strategy>
bool SelectionTemplate<Strategy>::IsCaret() const {
  return anchor_.IsNotNull() && anchor_ == focus_;
}
template <typename Strategy>
VisibleSelectionTemplate<Strategy>::VisibleSelectionTemplate()
    : affinity_(TextAffinity::kDownstream), anchor_is_first_(true) {}
template Element* VisibleSelectionTemplate<EditingStrategy>::RootEditableElement()
    const;
template SelectionTemplate<EditingStrategy>
VisibleSelectionTemplate<EditingStrategy>::AsSelection() const;
template bool VisibleSelectionTemplate<EditingStrategy>::IsNone() const;
template bool VisibleSelectionTemplate<EditingStrategy>::IsRange() const;
template PositionTemplate<EditingStrategy>
VisibleSelectionTemplate<EditingStrategy>::Start() const;
template EphemeralRangeTemplate<EditingStrategy>
VisibleSelectionTemplate<EditingStrategy>::ToNormalizedEphemeralRange() const;
template const PositionTemplate<EditingStrategy>&
SelectionTemplate<EditingStrategy>::ComputeStartPosition() const;
template const PositionTemplate<EditingStrategy>&
SelectionTemplate<EditingStrategy>::ComputeEndPosition() const;
template bool SelectionTemplate<EditingStrategy>::IsCaret() const;
template class SelectionTemplate<EditingStrategy>;
template class SelectionTemplate<EditingInFlatTreeStrategy>;
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

#if 0
bool DocumentAnimations::NeedsAnimationTimingUpdate() {
  return false;
}
void DocumentAnimations::UpdateAnimationTimingIfNeeded() {}
void DocumentAnimations::DetachCompositorTimelines() {}
void DocumentAnimations::DetachCompositorTriggers() {}
#endif
#if 0
CompositorAnimations::FailureReasons Animation::CheckCanStartAnimationOnCompositor(
    const PaintArtifactCompositor*,
    StartOnCompositorReason,
    PropertyHandleSet*) const {
  return CompositorAnimations::kInvalidAnimationOrEffect;
}
void Animation::OnPaintWorkletImageCreated() {}
#endif

void FrameSelection::MarkCacheDirty() {}
unsigned FontPerformance::in_style_ = 0;
void DocumentSpeculationRules::DocumentStyleUpdated() {}
void DocumentSpeculationRules::DocumentBaseTargetChanged() {}
void DocumentSpeculationRules::DocumentBaseURLChanged() {}
void DocumentSpeculationRules::DocumentReferrerPolicyChanged() {}
void DocumentSpeculationRules::LinkGainedOrLostComputedStyle(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::LinkMatchedSelectorsUpdated(
    HTMLAnchorElementBase*) {}
void DocumentSpeculationRules::ChildStyleRecalcBlocked(Element*) {}
void DocumentSpeculationRules::DidStyleChildren(Element*) {}
void ScriptLoader::DocumentBaseURLChanged() {}
#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
ShadowRoot* HTMLInputElement::EnsureShadowSubtree() {
  return nullptr;
}
void HTMLInputElement::EndEditing() {}
#endif
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
DocumentTiming::DocumentTiming(Document&)
    : document_timing_values_(MakeGarbageCollected<DocumentTimingValues>()) {}
void DocumentTiming::MarkDomLoading() {}
void DocumentTiming::MarkDomComplete() {}
void DocumentTiming::MarkDomInteractive() {}
ScriptedAnimationController::ScriptedAnimationController(
    LocalDOMWindow* window)
    : ExecutionContextLifecycleStateObserver(window),
      callback_collection_(window) {}
#if 0
DocumentAnimations::DocumentAnimations(Document* document)
    : current_transition_generation_(0), document_(document) {}
#endif
WorkletAnimationController::WorkletAnimationController(Document* document)
    : document_(document) {}
FragmentDirective::FragmentDirective(Document& document)
    : owner_document_(&document) {}
FragmentDirective::~FragmentDirective() = default;
KURL FragmentDirective::ConsumeFragmentDirective(const KURL& url) {
  return url;
}
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
    : hit_test_request_(request),
      cacheable_(true),
      point_in_inner_node_frame_(location.Point()),
      is_over_embedded_content_view_(false),
      is_over_resizer_(false),
      is_over_scroll_corner_(false) {}
HitTestResult::HitTestResult(const HitTestResult&) = default;
HitTestResult& HitTestResult::operator=(const HitTestResult&) = default;
void HitTestResult::Trace(Visitor* visitor) const {
  visitor->Trace(hit_test_request_);
  visitor->Trace(inner_node_);
  visitor->Trace(inner_element_);
  visitor->Trace(inner_possibly_pseudo_node_);
  visitor->Trace(inner_url_element_);
  visitor->Trace(scrollbar_);
  visitor->Trace(list_based_test_result_);
}
void HitTestRequest::Trace(Visitor* visitor) const {
  visitor->Trace(stop_node_);
}
void HitTestResult::CacheValues(const HitTestResult& other) {
  hit_test_request_ =
      other.hit_test_request_.GetType() & ~HitTestRequest::kAvoidCache;
}
PositionWithAffinity HitTestResult::GetPosition() const {
  const Node* node = inner_possibly_pseudo_node_;
  if (!node)
    return PositionWithAffinity();
  DCHECK_GE(node->GetDocument().Lifecycle().GetState(),
            DocumentLifecycle::kPrePaintClean);
  LayoutObject* layout_object = node->GetLayoutObject();
  if (!layout_object)
    return PositionWithAffinity();

  CHECK(!DisplayLockUtilities::LockedAncestorPreventingPaint(*layout_object));

  if (layout_object->ChildPaintBlockedByDisplayLock())
    return PositionWithAffinity(Position(*node, 0), TextAffinity::kDefault);

  if (node->IsPseudoElement()) {
    switch (node->GetPseudoId()) {
      case kPseudoIdBefore:
      case kPseudoIdMarker: {
        const Node* originating =
            &To<PseudoElement>(node)->UltimateOriginatingElement();
        return PositionWithAffinity(Position::FirstPositionInNode(*originating));
      }
      case kPseudoIdAfter: {
        const Node* originating =
            &To<PseudoElement>(node)->UltimateOriginatingElement();
        return PositionWithAffinity(Position::LastPositionInNode(*originating));
      }
      case kPseudoIdCheckMark:
        return PositionWithAffinity(Position::FirstPositionInNode(*inner_node_));
      default:
        break;
    }
  }

  return layout_object->PositionForPoint(LocalPoint());
}
void HitTestResult::SetURLElement(Element* element) {
  inner_url_element_ = element;
}
bool HitTestResult::IsOverLink() const {
  return false;
}
void HitTestResult::SetScrollbar(Scrollbar* scrollbar) {
  scrollbar_ = scrollbar;
}
void HitTestResult::SetToShadowHostIfInUAShadowRoot() {
  Node* node = InnerNode();
  if (!node)
    return;

  ShadowRoot* containing_shadow_root = node->ContainingShadowRoot();
  Element* shadow_host = nullptr;

  while (containing_shadow_root && containing_shadow_root->IsUserAgent()) {
    shadow_host = &containing_shadow_root->host();
    containing_shadow_root = shadow_host->ContainingShadowRoot();
  }

  if (node->IsInShadowTree() && node->OwnerShadowHost())
    OverrideNodeAndPosition(node->OwnerShadowHost(), local_point_);

  if (shadow_host)
    OverrideNodeAndPosition(shadow_host, local_point_);
}
HitTestResult::~HitTestResult() = default;
PositionWithAffinity HitTestResult::GetPositionForInnerNodeOrImageMapImage()
    const {
  Node* node = InnerPossiblyPseudoNode();
  if (node && !node->IsPseudoElement())
    node = InnerNodeOrImageMapImage();
  if (!node)
    return PositionWithAffinity();
  DCHECK_GE(node->GetDocument().Lifecycle().GetState(),
            DocumentLifecycle::kPrePaintClean);
  LayoutObject* layout_object = node->GetLayoutObject();
  if (!layout_object)
    return PositionWithAffinity();
  CHECK(!DisplayLockUtilities::LockedAncestorPreventingPaint(*layout_object));

  if (layout_object->ChildPaintBlockedByDisplayLock())
    return PositionWithAffinity(Position(*node, 0), TextAffinity::kDefault);

  PositionWithAffinity position = layout_object->PositionForPoint(LocalPoint());
  if (position.IsNull())
    return PositionWithAffinity(FirstPositionInOrBeforeNode(*node));
  return position;
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
  if (auto* element = DynamicTo<Element>(inner_possibly_pseudo_node_.Get())) {
    return element;
  }
  return inner_element_.Get();
}
Node* HitTestResult::InnerNodeOrImageMapImage() const {
  return inner_node_.Get();
}
LocalFrame* HitTestResult::InnerNodeFrame() const {
  return inner_node_ ? inner_node_->GetDocument().GetFrame() : nullptr;
}
HitTestLocation HitTestResult::ResolveRectBasedTest(
    Node* resolved_inner_node,
    const PhysicalOffset& resolved_point_in_main_frame) {
  SetInnerNode(resolved_inner_node);
  point_in_inner_node_frame_ = resolved_point_in_main_frame;
  return HitTestLocation(resolved_point_in_main_frame);
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
PositionTemplate<Strategy>::PositionTemplate(const Node& anchor_node,
                                             int offset)
    : PositionTemplate(&anchor_node, offset) {}
template <typename Strategy>
PositionTemplate<Strategy>::PositionTemplate(const PositionTemplate&) =
    default;
template <typename Strategy>
PositionTemplate<Strategy>& PositionTemplate<Strategy>::operator=(
    const PositionTemplate&) = default;
template <typename Strategy>
Node* PositionTemplate<Strategy>::ComputeContainerNode() const {
  if (!anchor_node_)
    return nullptr;

  switch (AnchorType()) {
    case PositionAnchorType::kAfterChildren:
    case PositionAnchorType::kOffsetInAnchor:
      return anchor_node_.Get();
    case PositionAnchorType::kBeforeAnchor:
    case PositionAnchorType::kAfterAnchor:
      return Strategy::Parent(*anchor_node_);
  }
  NOTREACHED();
}
template <typename Strategy>
static int StandaloneMinOffsetForNode(Node* anchor_node, int offset) {
  if (auto* data = DynamicTo<CharacterData>(anchor_node))
    return std::min(offset, static_cast<int>(data->length()));

  int new_offset = 0;
  for (Node* node = Strategy::FirstChild(*anchor_node);
       node && new_offset < offset; node = Strategy::NextSibling(*node))
    ++new_offset;

  return new_offset;
}
template <typename Strategy>
int PositionTemplate<Strategy>::ComputeOffsetInContainerNode() const {
  if (!anchor_node_)
    return 0;

  switch (AnchorType()) {
    case PositionAnchorType::kAfterChildren:
      return LastOffsetInNode(*anchor_node_);
    case PositionAnchorType::kOffsetInAnchor:
      return StandaloneMinOffsetForNode<Strategy>(anchor_node_.Get(), offset_);
    case PositionAnchorType::kBeforeAnchor:
      return Strategy::Index(*anchor_node_);
    case PositionAnchorType::kAfterAnchor:
      return Strategy::Index(*anchor_node_) + 1;
  }
  NOTREACHED();
}
template <typename Strategy>
Node* PositionTemplate<Strategy>::ComputeNodeBeforePosition() const {
  if (!anchor_node_)
    return nullptr;
  switch (AnchorType()) {
    case PositionAnchorType::kAfterChildren:
      return Strategy::LastChild(*anchor_node_);
    case PositionAnchorType::kOffsetInAnchor:
      return offset_ ? Strategy::ChildAt(*anchor_node_, offset_ - 1) : nullptr;
    case PositionAnchorType::kBeforeAnchor:
      return Strategy::PreviousSibling(*anchor_node_);
    case PositionAnchorType::kAfterAnchor:
      return anchor_node_.Get();
  }
  NOTREACHED();
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
int PositionTemplate<Strategy>::LastOffsetInNode(const Node& node) {
  if (auto* data = DynamicTo<CharacterData>(node))
    return static_cast<int>(data->length());
  return static_cast<int>(Strategy::CountChildren(node));
}
template <typename Strategy>
PositionTemplate<Strategy> PositionTemplate<Strategy>::FirstPositionInNode(
    const Node& anchor_node) {
  return PositionTemplate<Strategy>(anchor_node, 0);
}
template <typename Strategy>
PositionTemplate<Strategy> PositionTemplate<Strategy>::LastPositionInNode(
    const Node& anchor_node) {
  if (anchor_node.IsTextNode())
    return PositionTemplate<Strategy>(anchor_node, LastOffsetInNode(anchor_node));
  return PositionTemplate<Strategy>(&anchor_node,
                                    PositionAnchorType::kAfterChildren);
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
#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
TextControlElement* EnclosingTextControl(const Node*) {
  return nullptr;
}
#endif
template int
PositionTemplate<EditingStrategy>::ComputeOffsetInContainerNode() const;
template PositionTemplate<EditingStrategy>
PositionTemplate<EditingStrategy>::ParentAnchoredEquivalent() const;
template PositionTemplate<EditingStrategy>
PositionTemplate<EditingStrategy>::InParentBeforeNode(const Node&);
template int16_t PositionTemplate<EditingStrategy>::CompareTo(
    const PositionTemplate<EditingStrategy>&) const;
template bool PositionTemplate<EditingStrategy>::IsConnected() const;
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
bool ContentSecurityPolicy::AllowInline(InlineType inline_type,
                                        Element*,
                                        const String&,
                                        const String&,
                                        const String&,
                                        const OrdinalNumber&,
                                        ReportingDisposition) {
  // Standalone documents do not install page CSP policies. Match Chromium's
  // empty-policy behavior for CSS so parsed inline style attributes affect
  // layout, while leaving script/event inline paths disabled.
  return inline_type == InlineType::kStyle ||
         inline_type == InlineType::kStyleAttribute;
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
const AtomicString& QualifiedName::LocalNameUpperSlow() const {
  return LocalName();
}
#endif
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
void Frame::Initialize() {
  DCHECK_NE(IsLocalFrame(), IsRemoteFrame());

  if (owner_)
    owner_->SetContentFrame(*this);
  else
    page_->SetMainFrame(this);
}
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
DOMWindow::~DOMWindow() = default;
void DOMWindow::Trace(Visitor*) const {}
bool DOMWindow::IsCurrentlyDisplayedInFrame() const {
  return false;
}
DOMWindow* DOMWindow::top() const {
  return const_cast<DOMWindow*>(this);
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
  return window_ ? window_->GetExecutionContext() : nullptr;
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
v8::Local<v8::Value> bindings::DictionaryBase::ToV8(ScriptState*) const {
  return v8::Local<v8::Value>();
}
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
void Deprecation::CountDeprecation(ExecutionContext*, mojom::WebFeature) {}
void ScriptController::DiscardFrame() {}
void ScriptController::Trace(Visitor*) const {}
void ScriptController::ExecuteJavaScriptURL(const KURL&,
                                            network::mojom::CSPDisposition,
                                            const DOMWrapperWorld*) {}
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
#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
Vector<String> HTMLInputElement::FilesFromFileInputFormControlState(
    const FormControlState&) {
  return Vector<String>();
}
#endif
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
void PaintLayerScrollableArea::SetHasHorizontalScrollbar(bool has_scrollbar) {
  if (has_scrollbar == HasHorizontalScrollbar())
    return;
  SetScrollbarNeedsPaintInvalidation(kHorizontalScrollbar);
  scrollbar_manager_.SetHasHorizontalScrollbar(has_scrollbar);
  SetScrollCornerNeedsPaintInvalidation();
}
void PaintLayerScrollableArea::SetHasVerticalScrollbar(bool has_scrollbar) {
  if (has_scrollbar == HasVerticalScrollbar())
    return;
  SetScrollbarNeedsPaintInvalidation(kVerticalScrollbar);
  scrollbar_manager_.SetHasVerticalScrollbar(has_scrollbar);
  SetScrollCornerNeedsPaintInvalidation();
}
gfx::Point EmbeddedContentView::Location() const {
  return gfx::Point();
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void LayoutListItem::UpdateCounterStyle() {}
void LayoutInlineListItem::UpdateCounterStyle() {}
#endif
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
    const ScrollOffset& offset,
    mojom::blink::ScrollType scroll_type,
    cc::ScrollSourceType source_type) {
  ScrollableArea* area = GetScrollableArea();
  if (!area)
    return;
  area->ScrollOffsetChanged(area->ClampScrollOffset(offset), scroll_type,
                            source_type);
}
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
  ScrollOffsetChanged(offset, mojom::blink::ScrollType::kProgrammatic,
                      source_type);
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
ExceptionState::ExceptionState(DummyExceptionStateForTesting&)
    : context_(kEmptyContext), isolate_(nullptr) {}
void ExceptionState::RethrowV8Exception(v8::TryCatch&) {
  had_exception_ = true;
}
String LogicalOffset::ToString() const {
  return String();
}
DarkModeImageClassifier::~DarkModeImageClassifier() = default;
#if !defined(HTML_CSS_RENDERER_STANDALONE)
PaintUnderInvalidationChecker::~PaintUnderInvalidationChecker() = default;
#endif
ElementDataCache::ElementDataCache() = default;
#if 0
void DocumentAnimations::MarkAnimationsCompositorPending() {}
#endif
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
                         DocumentPolicyFeatureInfo>({
          {mojom::blink::DocumentPolicyFeature::kExpectNoLinkedResources,
           {"expect-no-linked-resources", PolicyValue::CreateBool(false)}},
      });
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
#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
bool HTMLInputElement::IsButton() const {
  return false;
}
#endif
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
    : hit_test_request_(HitTestRequest::kReadOnly | HitTestRequest::kActive),
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
ImageElementTiming::ImageElementTiming(LocalDOMWindow& window)
    : Supplement<LocalDOMWindow>(window) {}
ImageElementTiming& ImageElementTiming::From(LocalDOMWindow& window) {
  static Persistent<ImageElementTiming> timing;
  if (!timing) {
    timing = MakeGarbageCollected<ImageElementTiming>(window);
  }
  return *timing;
}
void ImageElementTiming::NotifyImageFinished(const LayoutObject&,
                                             const ImageResourceContent*) {}
void ImageElementTiming::NotifyImageRemoved(const LayoutObject*,
                                            const ImageResourceContent*) {}
void ImageElementTiming::Trace(Visitor*) const {}
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
void WebHTTPBody::Reset() {}
void FrameLoader::CommitNavigation(
    std::unique_ptr<WebNavigationParams>,
    std::unique_ptr<WebDocumentLoader::ExtraData>,
    CommitReason) {}
void test::RunPendingTasks() {}
MainThread* Thread::MainThread() {
  return &StandaloneMainThread();
}
URLLoaderMockFactory* URLLoaderMockFactory::GetSingletonInstance() {
  return nullptr;
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
void ActiveScriptWrappableBase::RegisterActiveScriptWrappable() {}
WorkletAnimationController::~WorkletAnimationController() = default;
void WorkletAnimationController::SynchronizeAnimatorName(const String&) {}
void WorkletAnimationController::SetMutationUpdate(
    std::unique_ptr<AnimationWorkletOutput>) {}
CookieJar::~CookieJar() = default;
void ScriptRunner::PendingScriptFinished(PendingScript*) {}
XMLParserScriptRunner::XMLParserScriptRunner(XMLParserScriptRunnerHost* host)
    : host_(host) {}
XMLParserScriptRunner::~XMLParserScriptRunner() = default;
void XMLParserScriptRunner::Detach() {
  parser_blocking_script_ = nullptr;
}
void XMLParserScriptRunner::ProcessScriptElement(Document&,
                                                 Element*,
                                                 TextPosition) {}
void XMLParserScriptRunner::PendingScriptFinished(PendingScript*) {}
void XMLParserScriptRunner::Trace(Visitor* visitor) const {
  visitor->Trace(parser_blocking_script_);
  visitor->Trace(host_);
  PendingScriptClient::Trace(visitor);
}
void ScriptedAnimationController::Trace(Visitor*) const {}
void ScriptedAnimationController::ContextLifecycleStateChanged(
    mojom::blink::FrameLifecycleState) {}
void FragmentDirective::Trace(Visitor* visitor) const {
  visitor->Trace(directives_);
  visitor->Trace(owner_document_);
}
const AtomicString event_interface_names::kErrorEvent("ErrorEvent");
const AtomicString event_interface_names::kHashChangeEvent("HashChangeEvent");
const AtomicString event_interface_names::kWheelEvent("WheelEvent");

}  // namespace blink

namespace blink::scheduler {
EventLoop::EventLoop(Delegate* delegate,
                     v8::Isolate* isolate,
                     std::unique_ptr<v8::MicrotaskQueue> microtask_queue)
    : delegate_(delegate),
      isolate_(isolate),
      microtask_queue_(std::move(microtask_queue)) {}
EventLoop::~EventLoop() = default;
void EventLoop::EnqueueMicrotask(base::OnceCallback<void()>) {}
std::unique_ptr<FrameScheduler> CreateDummyFrameScheduler(v8::Isolate*) {
  return nullptr;
}
}  // namespace blink::scheduler

namespace cc {
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
Quaternion Quaternion::FromAxisAngle(double x, double y, double z, double w) {
  return Quaternion(x, y, z, w);
}
Quaternion Quaternion::Slerp(const Quaternion&, double) const {
  return *this;
}
}  // namespace gfx

namespace ui {
Cursor::Cursor() = default;
Cursor::Cursor(mojom::CursorType type) : type_(type) {}
Cursor::Cursor(const Cursor& cursor)
    : type_(cursor.type_),
      platform_cursor_(cursor.platform_cursor_),
      custom_hotspot_(cursor.custom_hotspot_),
      image_scale_factor_(cursor.image_scale_factor_) {}
Cursor::~Cursor() = default;
Cursor Cursor::NewCustom(SkBitmap bitmap,
                         gfx::Point hotspot,
                         float image_scale_factor) {
  Cursor cursor;
  cursor.type_ = mojom::CursorType::kCustom;
  cursor.custom_bitmap_ = std::move(bitmap);
  cursor.custom_hotspot_ = hotspot;
  cursor.image_scale_factor_ = image_scale_factor == 0.0f ? 1.0f : image_scale_factor;
  return cursor;
}
const SkBitmap& Cursor::custom_bitmap() const {
  static SkBitmap* bitmap = new SkBitmap();
  return *bitmap;
}
const gfx::Point& Cursor::custom_hotspot() const {
  return custom_hotspot_;
}
float Cursor::image_scale_factor() const {
  return 1.0f;
}
bool Cursor::operator==(const Cursor& cursor) const {
  return type_ == cursor.type_;
}
bool Cursor::AreDimensionsValidForWeb(const gfx::Size&, float scale_factor) {
  return scale_factor != 0.0f;
}
}  // namespace ui

namespace blink {
#define STANDALONE_CURSOR(name, type)                                      \
  const ui::Cursor& name() {                                               \
    DEFINE_STATIC_LOCAL(ui::Cursor, cursor, (ui::mojom::CursorType::type)); \
    return cursor;                                                         \
  }
STANDALONE_CURSOR(PointerCursor, kPointer)
STANDALONE_CURSOR(CrossCursor, kCross)
STANDALONE_CURSOR(HandCursor, kHand)
STANDALONE_CURSOR(MoveCursor, kMove)
STANDALONE_CURSOR(IBeamCursor, kIBeam)
STANDALONE_CURSOR(WaitCursor, kWait)
STANDALONE_CURSOR(HelpCursor, kHelp)
STANDALONE_CURSOR(EastResizeCursor, kEastResize)
STANDALONE_CURSOR(NorthResizeCursor, kNorthResize)
STANDALONE_CURSOR(NorthEastResizeCursor, kNorthEastResize)
STANDALONE_CURSOR(NorthWestResizeCursor, kNorthWestResize)
STANDALONE_CURSOR(SouthResizeCursor, kSouthResize)
STANDALONE_CURSOR(SouthEastResizeCursor, kSouthEastResize)
STANDALONE_CURSOR(SouthWestResizeCursor, kSouthWestResize)
STANDALONE_CURSOR(WestResizeCursor, kWestResize)
STANDALONE_CURSOR(NorthSouthResizeCursor, kNorthSouthResize)
STANDALONE_CURSOR(EastWestResizeCursor, kEastWestResize)
STANDALONE_CURSOR(NorthEastSouthWestResizeCursor, kNorthEastSouthWestResize)
STANDALONE_CURSOR(NorthWestSouthEastResizeCursor, kNorthWestSouthEastResize)
STANDALONE_CURSOR(ColumnResizeCursor, kColumnResize)
STANDALONE_CURSOR(RowResizeCursor, kRowResize)
STANDALONE_CURSOR(MiddlePanningCursor, kMiddlePanning)
STANDALONE_CURSOR(MiddlePanningVerticalCursor, kMiddlePanningVertical)
STANDALONE_CURSOR(MiddlePanningHorizontalCursor, kMiddlePanningHorizontal)
STANDALONE_CURSOR(EastPanningCursor, kEastPanning)
STANDALONE_CURSOR(NorthPanningCursor, kNorthPanning)
STANDALONE_CURSOR(NorthEastPanningCursor, kNorthEastPanning)
STANDALONE_CURSOR(NorthWestPanningCursor, kNorthWestPanning)
STANDALONE_CURSOR(SouthPanningCursor, kSouthPanning)
STANDALONE_CURSOR(SouthEastPanningCursor, kSouthEastPanning)
STANDALONE_CURSOR(SouthWestPanningCursor, kSouthWestPanning)
STANDALONE_CURSOR(WestPanningCursor, kWestPanning)
STANDALONE_CURSOR(VerticalTextCursor, kVerticalText)
STANDALONE_CURSOR(CellCursor, kCell)
STANDALONE_CURSOR(ContextMenuCursor, kContextMenu)
STANDALONE_CURSOR(NoDropCursor, kNoDrop)
STANDALONE_CURSOR(NotAllowedCursor, kNotAllowed)
STANDALONE_CURSOR(ProgressCursor, kProgress)
STANDALONE_CURSOR(AliasCursor, kAlias)
STANDALONE_CURSOR(ZoomInCursor, kZoomIn)
STANDALONE_CURSOR(ZoomOutCursor, kZoomOut)
STANDALONE_CURSOR(CopyCursor, kCopy)
STANDALONE_CURSOR(NoneCursor, kNone)
STANDALONE_CURSOR(GrabCursor, kGrab)
STANDALONE_CURSOR(GrabbingCursor, kGrabbing)
#undef STANDALONE_CURSOR
}  // namespace blink

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

namespace base {
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
namespace debug {
}  // namespace debug
namespace sequence_manager {
}  // namespace sequence_manager
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
std::string UnlocalizedTimeFormatWithPattern(const Time&,
                                             std::string_view,
                                             const icu::TimeZone*) {
  return std::string();
}
namespace internal {
LockImpl::LockImpl() : native_handle_({0}) {}
LockImpl::~LockImpl() = default;
void LockImpl::LockInternal() {
  ::AcquireSRWLockExclusive(&native_handle_);
}
}  // namespace internal
CPU::CPU() = default;
CPU::CPU(CPU&&) = default;
const CPU& CPU::GetInstanceNoAllocation() {
  static CPU* cpu = new CPU();
  return *cpu;
}
namespace win {
}  // namespace win
}  // namespace base

namespace net {

std::string ElideHeaderValueForNetLog(NetLogCaptureMode,
                                      std::string_view,
                                      std::string_view value) {
  return std::string(value);
}

bool PlatformMimeUtil::GetPlatformMimeTypeFromExtension(
    const base::FilePath::StringType&,
    std::string*) const {
  return false;
}

bool PlatformMimeUtil::GetPlatformPreferredExtensionForMimeType(
    std::string_view,
    base::FilePath::StringType*) const {
  return false;
}

void PlatformMimeUtil::GetPlatformExtensionsForMimeType(
    std::string_view,
    std::unordered_set<base::FilePath::StringType>*) const {}

}  // namespace net

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

namespace mojo {
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
namespace internal {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
size_t Buffer::Allocate(size_t) {
  return 0;
}
#endif
InterfacePtrStateBase::InterfacePtrStateBase() = default;
InterfacePtrStateBase::~InterfacePtrStateBase() = default;
void InterfacePtrStateBase::Bind(
    PendingRemoteState*,
    scoped_refptr<base::SequencedTaskRunner>) {}
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
PendingRemoteState InterfacePtrStateBase::Unbind() {
  return PendingRemoteState();
}
void InterfacePtrStateBase::Swap(InterfacePtrStateBase*) {}
}  // namespace internal
}  // namespace mojo

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

namespace absl::container_internal {
HashtablezInfoHandle ForcedTrySample(size_t, size_t, size_t, uint16_t) {
  return HashtablezInfoHandle(nullptr);
}
}  // namespace absl::container_internal

extern "C" bool AbslContainerInternalSampleEverything() {
  return false;
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
void ExplicitManagementImpl::FreeUnreferencedObject(HeapHandle&, void*) {}
bool ExplicitManagementImpl::Resize(void*, size_t) {
  return false;
}
size_t BaseObjectSizeTrait::GetObjectSizeForGarbageCollected(const void*) {
  return 0;
}
CrossThreadPersistentRegion&
WeakCrossThreadPersistentPolicy::GetPersistentRegion(const void*) {
  static FatalOutOfMemoryHandler* oom =
      reinterpret_cast<FatalOutOfMemoryHandler*>(1);
  alignas(CrossThreadPersistentRegion) static unsigned char storage
      [sizeof(CrossThreadPersistentRegion)];
  static CrossThreadPersistentRegion* region =
      ::new (storage) CrossThreadPersistentRegion(*oom);
  return *region;
}
CrossThreadPersistentRegion&
StrongCrossThreadPersistentPolicy::GetPersistentRegion(const void*) {
  return WeakCrossThreadPersistentPolicy::GetPersistentRegion(nullptr);
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
Region::Region() = default;
Region::Region(const Region&) = default;
Region::~Region() = default;
void Region::Union(const gfx::Rect&) {}
#endif
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
}  // namespace cc

#if !defined(HTML_CSS_RENDERER_STANDALONE)
SkRegion::SkRegion() = default;
SkRegion::SkRegion(const SkRegion&) = default;
SkRegion::~SkRegion() = default;
#endif

namespace perfetto {
namespace base {
}  // namespace base
}  // namespace perfetto

namespace subresource_filter {
MemoryMappedRuleset::~MemoryMappedRuleset() = default;
}  // namespace subresource_filter

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

namespace blink {
size_t Platform::GetMaxDecodedImageBytes() {
  return kNoDecodedImageByteLimit;
}

DiskDataAllocator::DiskDataAllocator() = default;
DiskDataAllocator::~DiskDataAllocator() = default;
DiskDataAllocator& DiskDataAllocator::Instance() {
  static auto* allocator = new DiskDataAllocator();
  return *allocator;
}
void DiskDataAllocator::Bind(
    mojo::PendingReceiver<mojom::blink::DiskAllocator>) {}
void DiskDataAllocator::ProvideTemporaryFile(base::File) {}
bool DiskDataAllocator::may_write() {
  return false;
}
void DiskDataAllocator::set_may_write_for_testing(bool) {}
std::unique_ptr<ReservedChunk> DiskDataAllocator::TryReserveChunk(size_t) {
  return nullptr;
}
std::unique_ptr<DiskDataMetadata> DiskDataAllocator::Write(
    std::unique_ptr<ReservedChunk>,
    base::span<const uint8_t>) {
  return nullptr;
}
void DiskDataAllocator::Read(const DiskDataMetadata&,
                             base::span<uint8_t>) {}
void DiskDataAllocator::Discard(std::unique_ptr<DiskDataMetadata>) {}
std::optional<size_t> DiskDataAllocator::DoWrite(
    int64_t,
    base::span<const uint8_t>) {
  return std::nullopt;
}
void DiskDataAllocator::DoRead(int64_t, base::span<uint8_t>) {}
ReservedChunk::ReservedChunk(DiskDataAllocator* allocator,
                             std::unique_ptr<DiskDataMetadata> metadata)
    : allocator_(allocator), metadata_(std::move(metadata)) {}
ReservedChunk::~ReservedChunk() = default;
std::unique_ptr<DiskDataMetadata> ReservedChunk::Take() {
  return std::move(metadata_);
}

PaintImage Image::ResizeAndOrientImage(
    const PaintImage& image,
    ImageOrientation orientation,
    gfx::Vector2dF image_scale,
    float opacity,
    InterpolationQuality interpolation_quality) {
  return ResizeAndOrientImage(image, orientation, image_scale, opacity,
                              interpolation_quality, nullptr);
}

PaintImage Image::ResizeAndOrientImage(const PaintImage& image,
                                       ImageOrientation orientation,
                                       gfx::Vector2dF image_scale,
                                       float opacity,
                                       InterpolationQuality,
                                       sk_sp<SkColorSpace>) {
  if (orientation == ImageOrientationEnum::kDefault &&
      image_scale == gfx::Vector2dF(1, 1) && opacity == 1.0f) {
    return image;
  }
  return PaintImage();
}

ThreadScheduler* ThreadScheduler::Current() {
  return nullptr;
}

}  // namespace blink

namespace base {
std::unique_ptr<debug::StackTrace> ThreadCheckerImpl::GetBoundAt() const {
  return nullptr;
}
}  // namespace base

namespace {

struct StandaloneFontResolutionDiagnostic {
  std::string requested_family;
  std::string effective_family;
  std::string resolved_family;
  std::string fallback_reason;
  std::string skfont_edging;
  std::string skfont_hinting;
  float computed_size = 0.0f;
  float test_string_width = 0.0f;
  float test_string_rounded_glyph_width = 0.0f;
  float metrics_ascent = 0.0f;
  float metrics_descent = 0.0f;
  float metrics_leading = 0.0f;
  int weight = 0;
  int width = 0;
  int slant = 0;
  bool requested_family_was_empty = false;
  bool requested_family_was_generic = false;
  bool synthetic_bold = false;
  bool synthetic_italic = false;
  bool skfont_antialias = false;
  bool skfont_subpixel_positioning = false;
  bool skfont_embedded_bitmaps = false;
  bool skfont_linear_metrics = false;
};

std::vector<StandaloneFontResolutionDiagnostic>&
StandaloneFontResolutionDiagnostics() {
  static std::vector<StandaloneFontResolutionDiagnostic>* diagnostics =
      new std::vector<StandaloneFontResolutionDiagnostic>();
  return *diagnostics;
}

std::string StandaloneEscapeJsonString(const std::string& value) {
  std::string escaped;
  escaped.reserve(value.size() + 8);
  for (char c : value) {
    switch (c) {
      case '\\':
        escaped += "\\\\";
        break;
      case '"':
        escaped += "\\\"";
        break;
      case '\n':
        escaped += "\\n";
        break;
      case '\r':
        escaped += "\\r";
        break;
      case '\t':
        escaped += "\\t";
        break;
      default:
        escaped += c;
        break;
    }
  }
  return escaped;
}

std::string StandaloneJsonString(const std::string& value) {
  return "\"" + StandaloneEscapeJsonString(value) + "\"";
}

std::string StandaloneSkFontEdgingName(SkFont::Edging edging) {
  switch (edging) {
    case SkFont::Edging::kAlias:
      return "alias";
    case SkFont::Edging::kAntiAlias:
      return "antialias";
    case SkFont::Edging::kSubpixelAntiAlias:
      return "subpixel_antialias";
  }
  return "unknown";
}

std::string StandaloneSkFontHintingName(SkFontHinting hinting) {
  switch (hinting) {
    case SkFontHinting::kNone:
      return "none";
    case SkFontHinting::kSlight:
      return "slight";
    case SkFontHinting::kNormal:
      return "normal";
    case SkFontHinting::kFull:
      return "full";
  }
  return "unknown";
}

void StandaloneRecordFontResolutionDiagnostic(
    StandaloneFontResolutionDiagnostic diagnostic) {
  auto& diagnostics = StandaloneFontResolutionDiagnostics();
  if (diagnostics.size() >= 256) {
    return;
  }
  diagnostics.push_back(std::move(diagnostic));
}

std::string StandaloneLowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });
  return value;
}

bool StandaloneTypefaceMatchesRequestedFamily(const SkTypeface& typeface,
                                              const std::string& family) {
  SkString resolved_family;
  typeface.getFamilyName(&resolved_family);
  return StandaloneLowerAscii(resolved_family.c_str()) ==
         StandaloneLowerAscii(family);
}

}  // namespace

extern "C" int StandaloneRendererFontResolutionDiagnosticCount() {
  return static_cast<int>(StandaloneFontResolutionDiagnostics().size());
}

extern "C" int StandaloneRendererFontResolutionDiagnosticJsonAt(
    int index,
    char* buffer,
    int buffer_size) {
  if (!buffer || buffer_size <= 0) {
    return 0;
  }
  buffer[0] = '\0';
  const auto& diagnostics = StandaloneFontResolutionDiagnostics();
  if (index < 0 || static_cast<size_t>(index) >= diagnostics.size()) {
    return 0;
  }
  const auto& diagnostic = diagnostics[static_cast<size_t>(index)];
  std::ostringstream json;
  json << "{\"requested_family\":"
       << StandaloneJsonString(diagnostic.requested_family)
       << ",\"effective_family\":"
       << StandaloneJsonString(diagnostic.effective_family)
       << ",\"resolved_family\":"
       << StandaloneJsonString(diagnostic.resolved_family)
       << ",\"fallback_reason\":"
       << StandaloneJsonString(diagnostic.fallback_reason)
       << ",\"skfont_edging\":"
       << StandaloneJsonString(diagnostic.skfont_edging)
       << ",\"skfont_antialias\":"
       << (diagnostic.skfont_antialias ? "true" : "false")
       << ",\"skfont_subpixel_positioning\":"
       << (diagnostic.skfont_subpixel_positioning ? "true" : "false")
       << ",\"skfont_embedded_bitmaps\":"
       << (diagnostic.skfont_embedded_bitmaps ? "true" : "false")
       << ",\"skfont_linear_metrics\":"
       << (diagnostic.skfont_linear_metrics ? "true" : "false")
       << ",\"skfont_hinting\":"
       << StandaloneJsonString(diagnostic.skfont_hinting)
       << ",\"computed_size\":" << diagnostic.computed_size
       << ",\"test_string\":\"Custom Property Math\""
       << ",\"test_string_width\":" << diagnostic.test_string_width
       << ",\"test_string_rounded_glyph_width\":"
       << diagnostic.test_string_rounded_glyph_width
       << ",\"metrics_ascent\":" << diagnostic.metrics_ascent
       << ",\"metrics_descent\":" << diagnostic.metrics_descent
       << ",\"metrics_leading\":" << diagnostic.metrics_leading
       << ",\"weight\":" << diagnostic.weight
       << ",\"width\":" << diagnostic.width
       << ",\"slant\":" << diagnostic.slant
       << ",\"requested_family_was_empty\":"
       << (diagnostic.requested_family_was_empty ? "true" : "false")
       << ",\"requested_family_was_generic\":"
       << (diagnostic.requested_family_was_generic ? "true" : "false")
       << ",\"synthetic_bold\":"
       << (diagnostic.synthetic_bold ? "true" : "false")
       << ",\"synthetic_italic\":"
       << (diagnostic.synthetic_italic ? "true" : "false") << "}";
  const std::string payload = json.str();
  std::snprintf(buffer, static_cast<size_t>(buffer_size), "%s",
                payload.c_str());
  return static_cast<int>(payload.size());
}

namespace blink {
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

namespace {
class StandalonePlatform final : public Platform {
 public:
  bool IsThreadedAnimationEnabled() override { return false; }

  scoped_refptr<viz::RasterContextProvider> SharedMainThreadContextProvider()
      override {
    return nullptr;
  }

  scoped_refptr<viz::RasterContextProvider> SharedCompositorWorkerContextProvider(
      cc::RasterDarkModeFilter*) override {
    return nullptr;
  }

  void SharedMediaContextProvider(
      base::OnceCallback<void(scoped_refptr<viz::RasterContextProvider>)>)
      override {}

  scoped_refptr<gpu::GpuChannelHost> EstablishGpuChannelSync() override {
    return nullptr;
  }

  bool IsGpuRemoteDisconnected() override { return true; }

  void EstablishGpuChannel(EstablishGpuChannelCallback) override {}

  std::unique_ptr<WebDedicatedWorkerHostFactoryClient>
  CreateDedicatedWorkerHostFactoryClient(
      WebDedicatedWorker*,
      const BrowserInterfaceBrokerProxy&) override {
    return nullptr;
  }

  void CreateServiceWorkerSubresourceLoaderFactory(
      CrossVariantMojoRemote<mojom::ServiceWorkerContainerHostInterfaceBase>,
      const WebString&,
      std::unique_ptr<network::PendingSharedURLLoaderFactory>,
      mojo::PendingReceiver<network::mojom::URLLoaderFactory>,
      scoped_refptr<base::SequencedTaskRunner>) override {}

  ThreadSafeBrowserInterfaceBrokerProxy* GetBrowserInterfaceBroker()
      override {
    return nullptr;
  }

  std::unique_ptr<media::MediaLog> GetMediaLog(
      MediaInspectorContext*,
      scoped_refptr<base::SingleThreadTaskRunner>,
      bool) override {
    return nullptr;
  }

  gfx::ColorSpace GetRenderingColorSpace() const override {
    return gfx::ColorSpace();
  }
};
}  // namespace

Platform::Platform() = default;
Platform::~Platform() = default;

scoped_refptr<base::SingleThreadTaskRunner>
Platform::CompositorThreadTaskRunner() {
  return nullptr;
}

std::unique_ptr<WebGraphicsContext3DProvider>
Platform::CreateWebGLGraphicsContextProvider(bool,
                                             bool,
                                             WebGLContextType,
                                             const WebURL&,
                                             WebGLContextInfo*) {
  return nullptr;
}

std::unique_ptr<WebGraphicsContext3DProvider>
Platform::CreateRasterGraphicsContextProvider(const WebURL&,
                                              RasterContextType) {
  return nullptr;
}

std::unique_ptr<WebGraphicsContext3DProvider>
Platform::CreateSharedOffscreenGraphicsContext3DProvider() {
  return nullptr;
}

std::unique_ptr<WebGraphicsContext3DProvider>
Platform::CreateWebGPUGraphicsContext3DProvider(const WebURL&,
                                                WebGPUReplyThread) {
  return nullptr;
}

void Platform::CreateWebGPUGraphicsContext3DProviderAsync(
    const WebURL&,
    WebGPUReplyThread,
    base::OnceCallback<void(std::unique_ptr<WebGraphicsContext3DProvider>)>) {}

scoped_refptr<viz::RasterContextProvider>
Platform::SharedMainThreadContextProvider() {
  return nullptr;
}

scoped_refptr<viz::RasterContextProvider>
Platform::SharedCompositorWorkerContextProvider(cc::RasterDarkModeFilter*) {
  return nullptr;
}

void Platform::SharedMediaContextProvider(
    base::OnceCallback<void(scoped_refptr<viz::RasterContextProvider>)>) {}

scoped_refptr<gpu::GpuChannelHost> Platform::EstablishGpuChannelSync() {
  return nullptr;
}

bool Platform::IsGpuRemoteDisconnected() {
  return true;
}

void Platform::EstablishGpuChannel(EstablishGpuChannelCallback) {}

std::unique_ptr<WebDedicatedWorkerHostFactoryClient>
Platform::CreateDedicatedWorkerHostFactoryClient(
    WebDedicatedWorker*,
    const BrowserInterfaceBrokerProxy&) {
  return nullptr;
}

void Platform::CreateServiceWorkerSubresourceLoaderFactory(
    CrossVariantMojoRemote<mojom::ServiceWorkerContainerHostInterfaceBase>,
    const WebString&,
    std::unique_ptr<network::PendingSharedURLLoaderFactory>,
    mojo::PendingReceiver<network::mojom::URLLoaderFactory>,
    scoped_refptr<base::SequencedTaskRunner>) {}

ThreadSafeBrowserInterfaceBrokerProxy* Platform::GetBrowserInterfaceBroker() {
  return nullptr;
}

std::unique_ptr<media::MediaLog> Platform::GetMediaLog(
    MediaInspectorContext*,
    scoped_refptr<base::SingleThreadTaskRunner>,
    bool) {
  return nullptr;
}

gfx::ColorSpace Platform::GetRenderingColorSpace() const {
  return gfx::ColorSpace();
}

Platform* Platform::Current() {
  static StandalonePlatform* platform = new StandalonePlatform();
  return platform;
}
void ThreadSafeBrowserInterfaceBrokerProxy::GetInterface(
    mojo::GenericPendingReceiver) {}

namespace inspector_parse_author_style_sheet_event {
void Data(perfetto::TracedValue,
          CSSStyleSheetResource*,
          const String&,
          const CSSParserContext*) {}
}  // namespace inspector_parse_author_style_sheet_event


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
CSSValue* CSSValue::Create(const Length& value, float zoom) {
  switch (value.GetType()) {
    case Length::kAuto:
    case Length::kMinContent:
    case Length::kMaxContent:
    case Length::kStretch:
    case Length::kFitContent:
    case Length::kContent:
      return CSSIdentifierValue::Create(value);
    case Length::kPercent:
    case Length::kFixed:
    case Length::kCalculated:
    case Length::kFlex:
      return CSSPrimitiveValue::CreateFromLength(value, zoom);
    case Length::kMinIntrinsic:
    case Length::kNone:
    case Length::kOverlapJoin:
      break;
  }
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

void FrameSelection::LayoutBlockWillBeDestroyed(const LayoutBlock&) {}
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
  if (IsInline() || IsFloatingOrOutOfFlowPositioned() || IsScrollContainer() ||
      IsFlexItem() || IsCustomItem() || IsDocumentElement() || IsGridItem() ||
      IsGridLanesItem() || IsWritingModeRoot() || IsMathItem() ||
      StyleRef().Display() == EDisplay::kFlowRoot ||
      StyleRef().Display() == EDisplay::kFlowRootListItem ||
      ShouldApplyPaintContainment() || ShouldApplyLayoutContainment() ||
      StyleRef().IsContainerForSizeContainerQueries() ||
      StyleRef().HasLineClamp() || StyleRef().SpecifiesColumns() ||
      StyleRef().GetColumnSpan() == EColumnSpan::kAll) {
    return true;
  }

  if (RuntimeEnabledFeatures::CanvasDrawElementEnabled(
          GetDocument().GetExecutionContext()) &&
      Parent()->IsCanvas()) {
    return true;
  }

  if (StyleRef().AlignContent().GetPosition() != ContentPosition::kNormal ||
      StyleRef().AlignContent().Distribution() !=
          ContentDistributionType::kDefault) {
    return true;
  }

  if (IsRenderedLegend() || IsSemiReplaced())
    return true;

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
LayoutImageResourceStyleImage::LayoutImageResourceStyleImage(
    StyleImage* style_image)
    : style_image_(style_image) {
  DCHECK(style_image_);
}
StyleImageSet::StyleImageSet(StyleImage* image, CSSImageSetValue* value)
    : best_fit_image_(image), image_set_value_(value) {}

#if !defined(HTML_CSS_RENDERER_STANDALONE)
void ReferenceFilterOperation::AddClient(SVGResourceClient&) {}
void ReferenceFilterOperation::RemoveClient(SVGResourceClient&) {}
#endif

#if !defined(HTML_CSS_RENDERER_STANDALONE)
bool IsSupportedImageMimeType(std::string_view) {
  return false;
}
#endif

ColorChannelKeyword CSSValueIDToColorChannelKeyword(CSSValueID) {
  return static_cast<ColorChannelKeyword>(0);
}
CSSValueID ColorChannelKeywordToCSSValueID(ColorChannelKeyword) {
  return CSSValueID::kInvalid;
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
  for (const FontFamily* family = &font_description.Family(); family;
       family = family->Next()) {
    AtomicString family_name = family->FamilyName();
    if (family_name.empty()) {
      continue;
    }
    if (family->FamilyIsGeneric()) {
      const std::string generic_name = family_name.GetString().Utf8();
      const std::string lower_generic = StandaloneLowerAscii(generic_name);
      if (lower_generic == "monospace" ||
          lower_generic == "ui-monospace") {
        family_name = AtomicString("Consolas");
      } else if (lower_generic == "system-ui" ||
                 lower_generic == "ui-sans-serif") {
        family_name = AtomicString("Segoe UI");
      } else if (lower_generic == "sans-serif" ||
                 lower_generic == "cursive" ||
                 lower_generic == "fantasy") {
        family_name = AtomicString("Arial");
      } else {
        family_name = AtomicString("Times New Roman");
      }
    }
    if (const SimpleFontData* data =
            FontCache::Get().GetFontData(font_description, family_name)) {
      return data;
    }
  }

  switch (font_description.GenericFamily()) {
    case FontDescription::kMonospaceFamily:
      return FontCache::Get().GetFontData(font_description,
                                          AtomicString("Consolas"),
                                          AlternateFontName::kLastResort);
    case FontDescription::kSansSerifFamily:
    case FontDescription::kCursiveFamily:
    case FontDescription::kFantasyFamily:
      return FontCache::Get().GetFontData(font_description,
                                          AtomicString("Arial"),
                                          AlternateFontName::kLastResort);
    case FontDescription::kStandardFamily:
    case FontDescription::kWebkitBodyFamily:
    case FontDescription::kNoFamily:
    case FontDescription::kSerifFamily:
      return FontCache::Get().GetFontData(font_description,
                                          AtomicString("Times New Roman"),
                                          AlternateFontName::kLastResort);
  }
  return nullptr;
}

const SimpleFontData* FontCache::GetFontData(
    const FontDescription& font_description,
    const AtomicString& family_name,
    AlternateFontName alternate_font_name) {
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
  std::string fallback_reason = "empty_font_manager";
  if (sk_sp<SkFontMgr> font_manager = skia::DefaultFontMgr()) {
    typeface =
        font_manager->matchFamilyStyle(requested_family.c_str(),
                                       requested_style);
    if (typeface &&
        (alternate_font_name == AlternateFontName::kLastResort ||
         StandaloneTypefaceMatchesRequestedFamily(*typeface,
                                                  requested_family))) {
      fallback_reason = "match_family_style";
    } else {
      typeface = nullptr;
    }
    if (!typeface) {
      typeface = font_manager->legacyMakeTypeface(requested_family.c_str(),
                                                  requested_style);
      if (typeface &&
          (alternate_font_name == AlternateFontName::kLastResort ||
           StandaloneTypefaceMatchesRequestedFamily(*typeface,
                                                    requested_family))) {
        fallback_reason = "legacy_make_typeface";
      } else {
        typeface = nullptr;
      }
    }
    if (!typeface && alternate_font_name == AlternateFontName::kLastResort &&
        font_manager->countFamilies() > 0) {
      SkString family_name;
      font_manager->getFamilyName(0, &family_name);
      typeface =
          font_manager->matchFamilyStyle(family_name.c_str(),
                                         requested_style);
      if (typeface) {
        fallback_reason = "first_family_fallback";
      }
    }
  }
  if (!typeface) {
    if (alternate_font_name != AlternateFontName::kLastResort) {
      return nullptr;
    }
    typeface = SkTypeface::MakeEmpty();
    fallback_reason = "empty_typeface";
  }

  auto* platform_data = new Persistent<FontPlatformData>();
  const bool synthetic_bold =
      font_description.Weight() >= kBoldThreshold && typeface &&
      !typeface->isBold();
  const bool synthetic_italic =
      font_description.Style() == kItalicSlopeValue && typeface &&
      !typeface->isItalic();
  SkString resolved_family;
  if (typeface) {
    typeface->getFamilyName(&resolved_family);
  }
  StandaloneFontResolutionDiagnostic diagnostic;
  diagnostic.requested_family =
      family_name.empty() ? std::string() : family_name.GetString().Utf8();
  diagnostic.effective_family = requested_family;
  diagnostic.resolved_family = resolved_family.c_str();
  diagnostic.fallback_reason = fallback_reason;
  diagnostic.computed_size = computed_size;
  SkFont diagnostic_font(typeface, computed_size);
  diagnostic_font.setEmbolden(synthetic_bold);
  diagnostic_font.setSkewX(synthetic_italic ? -0.25f : 0.0f);
  diagnostic_font.setEdging(SkFont::Edging::kSubpixelAntiAlias);
  diagnostic_font.setSubpixel(true);
  diagnostic_font.setEmbeddedBitmaps(true);
  diagnostic.skfont_edging =
      StandaloneSkFontEdgingName(diagnostic_font.getEdging());
  diagnostic.skfont_antialias =
      diagnostic_font.getEdging() != SkFont::Edging::kAlias;
  diagnostic.skfont_subpixel_positioning = diagnostic_font.isSubpixel();
  diagnostic.skfont_embedded_bitmaps = diagnostic_font.isEmbeddedBitmaps();
  diagnostic.skfont_linear_metrics = diagnostic_font.isLinearMetrics();
  diagnostic.skfont_hinting =
      StandaloneSkFontHintingName(diagnostic_font.getHinting());
  diagnostic.test_string_width = diagnostic_font.measureText(
      "Custom Property Math", 20, SkTextEncoding::kUTF8);
  const char kDiagnosticText[] = "Custom Property Math";
  const int glyph_count = diagnostic_font.textToGlyphs(
      kDiagnosticText, 20, SkTextEncoding::kUTF8, {});
  if (glyph_count > 0) {
    std::vector<SkGlyphID> glyphs(static_cast<size_t>(glyph_count));
    diagnostic_font.textToGlyphs(kDiagnosticText, 20, SkTextEncoding::kUTF8,
                                 SkSpan<SkGlyphID>(glyphs.data(),
                                                   glyphs.size()));
    std::vector<SkScalar> widths(static_cast<size_t>(glyph_count));
    diagnostic_font.getWidths(glyphs, widths);
    for (SkScalar width : widths) {
      diagnostic.test_string_rounded_glyph_width +=
          static_cast<float>(SkScalarRoundToInt(width));
    }
  }
  SkFontMetrics font_metrics;
  diagnostic_font.getMetrics(&font_metrics);
  diagnostic.metrics_ascent = font_metrics.fAscent;
  diagnostic.metrics_descent = font_metrics.fDescent;
  diagnostic.metrics_leading = font_metrics.fLeading;
  diagnostic.weight = requested_style.weight();
  diagnostic.width = requested_style.width();
  diagnostic.slant = requested_style.slant();
  diagnostic.requested_family_was_empty = family_name.empty();
  diagnostic.requested_family_was_generic =
      font_description.Family().FamilyIsGeneric();
  diagnostic.synthetic_bold = synthetic_bold;
  diagnostic.synthetic_italic = synthetic_italic;
  StandaloneRecordFontResolutionDiagnostic(std::move(diagnostic));
  *platform_data = MakeGarbageCollected<FontPlatformData>(
      std::move(typeface), std::string(), computed_size, synthetic_bold,
      synthetic_italic, font_description.TextRendering(),
      font_description.ResolveFontFeatures(), font_description.Orientation());
  auto* simple_font_data = new Persistent<SimpleFontData>();
  *simple_font_data =
      MakeGarbageCollected<SimpleFontData>(platform_data->Get(), nullptr);
  platform_data_by_key[cache_key] = platform_data;
  simple_font_data_by_key[cache_key] = simple_font_data;
  return simple_font_data->Get();
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

const KURL& SVGResourceDocumentContent::Url() const {
  static const KURL* empty_url = new KURL();
  return *empty_url;
}
SVGResourceDocumentContent* SVGResourceDocumentContent::Fetch(
    FetchParameters&,
    Document&) {
  return nullptr;
}
SVGResourceDocumentContent::SVGResourceDocumentContent(
    AgentGroupScheduler&,
    scoped_refptr<base::SingleThreadTaskRunner>) {}
SVGResourceDocumentContent::~SVGResourceDocumentContent() = default;
bool SVGResourceDocumentContent::IsLoaded() const {
  return false;
}
bool SVGResourceDocumentContent::IsLoading() const {
  return false;
}
bool SVGResourceDocumentContent::ErrorOccurred() const {
  return true;
}
Document* SVGResourceDocumentContent::GetDocument() const {
  return nullptr;
}
void SVGResourceDocumentContent::NotifyStartLoad() {}
SVGResourceDocumentContent::UpdateResult SVGResourceDocumentContent::UpdateDocument(
    scoped_refptr<SharedBuffer>,
    const KURL&) {
  return UpdateResult::kError;
}
void SVGResourceDocumentContent::ClearDocument() {}
void SVGResourceDocumentContent::Dispose() {}
void SVGResourceDocumentContent::UpdateStatus(ResourceStatus) {}
void SVGResourceDocumentContent::AddObserver(SVGResourceDocumentObserver*) {}
void SVGResourceDocumentContent::RemoveObserver(SVGResourceDocumentObserver*) {}
void SVGResourceDocumentContent::NotifyObservers() {}
SVGResourceTarget* SVGResourceDocumentContent::GetResourceTarget(
    const AtomicString&) {
  return nullptr;
}
void SVGResourceDocumentContent::Trace(Visitor*) const {}

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
      override_image_resolution_(override_image_resolution) {
  is_image_resource_ = true;
  if (image_) {
    image_->AddObserver(this);
  }
}
StyleFetchedImage::~StyleFetchedImage() = default;
WrappedImagePtr StyleFetchedImage::Data() const { return image_.Get(); }
float StyleFetchedImage::ApplyImageResolution(float multiplier) const {
  const Image& image = *image_->GetImage();
  if (image.IsBitmapImage() && override_image_resolution_ > 0.0f) {
    multiplier /= override_image_resolution_;
  } else if (image_->HasDevicePixelRatioHeaderValue()) {
    multiplier /= image_->DevicePixelRatioHeaderValue();
  }
  return multiplier;
}
float StyleFetchedImage::ImageScaleFactor() const {
  if (override_image_resolution_ > 0.0f) {
    return override_image_resolution_;
  }
  if (image_ && image_->HasDevicePixelRatioHeaderValue()) {
    return image_->DevicePixelRatioHeaderValue();
  }
  return 1.0f;
}
CSSValue* StyleFetchedImage::CssValue() const { return nullptr; }
CSSValue* StyleFetchedImage::ComputedCSSValue(const ComputedStyle&,
                                              bool,
                                              CSSValuePhase) const {
  return nullptr;
}
bool StyleFetchedImage::CanRender() const {
  return image_ && image_->HasImage() && !image_->ErrorOccurred();
}
bool StyleFetchedImage::IsLoaded() const {
  return image_ && image_->IsLoaded();
}
bool StyleFetchedImage::IsLoading() const {
  return image_ && image_->IsLoading();
}
bool StyleFetchedImage::ErrorOccurred() const {
  return !image_ || image_->ErrorOccurred();
}
bool StyleFetchedImage::IsCorsSameOrigin(String&) const { return false; }
NaturalSizingInfo StyleFetchedImage::GetNaturalSizingInfo(
    float multiplier,
    RespectImageOrientationEnum respect_orientation) const {
  if (!image_ || !image_->HasImage() || image_->ErrorOccurred()) {
    return NaturalSizingInfo::None();
  }
  Image& image = *image_->GetImage();
  NaturalSizingInfo sizing_info;
  if (auto* svg_image = DynamicTo<SVGImage>(image)) {
    const SVGImageViewInfo* view_info =
        SVGImageForContainer::CreateViewInfo(*svg_image, url_);
    sizing_info =
        SVGImageForContainer::GetNaturalDimensions(*svg_image, view_info)
            .value_or(NaturalSizingInfo::None());
  } else {
    gfx::SizeF size(image.Size(ForceOrientationIfNecessary(respect_orientation)));
    sizing_info = NaturalSizingInfo::MakeFixed(size);
  }

  multiplier = ApplyImageResolution(multiplier);
  sizing_info.size = ApplyZoom(sizing_info.size, multiplier);
  return sizing_info;
}
gfx::SizeF StyleFetchedImage::ImageSize(float multiplier,
                                        const gfx::SizeF& default_object_size,
                                        RespectImageOrientationEnum respect_orientation) const {
  if (!image_ || !image_->HasImage() || image_->ErrorOccurred()) {
    return default_object_size;
  }
  multiplier = ApplyImageResolution(multiplier);
  Image& image = *image_->GetImage();
  gfx::SizeF size;
  if (auto* svg_image = DynamicTo<SVGImage>(image)) {
    const SVGImageViewInfo* view_info =
        SVGImageForContainer::CreateViewInfo(*svg_image, url_);
    const gfx::SizeF unzoomed_default_object_size =
        gfx::ScaleSize(default_object_size, 1 / multiplier);
    size = SVGImageForContainer::ConcreteObjectSize(
        *svg_image, view_info, unzoomed_default_object_size);
  } else {
    size = gfx::SizeF(image.Size(ForceOrientationIfNecessary(respect_orientation)));
  }
  return ApplyZoom(size, multiplier);
}
bool StyleFetchedImage::HasIntrinsicSize() const {
  if (!image_ || !image_->HasImage() || image_->ErrorOccurred()) {
    return false;
  }
  Image& image = *image_->GetImage();
  if (auto* svg_image = DynamicTo<SVGImage>(image)) {
    const SVGImageViewInfo* view_info =
        SVGImageForContainer::CreateViewInfo(*svg_image, url_);
    std::optional<NaturalSizingInfo> natural_sizing_info =
        SVGImageForContainer::GetNaturalDimensions(*svg_image, view_info);
    return natural_sizing_info && !natural_sizing_info->IsNone();
  }
  return image.HasIntrinsicSize();
}
void StyleFetchedImage::AddClient(ImageResourceObserver* observer) {
  if (image_ && observer) {
    image_->AddObserver(observer);
  }
}
void StyleFetchedImage::RemoveClient(ImageResourceObserver* observer) {
  if (image_ && observer) {
    image_->RemoveObserver(observer);
  }
}
scoped_refptr<Image> StyleFetchedImage::GetImage(
    const ImageResourceObserver&,
    const Node& node,
    const ComputedStyle& style,
    const gfx::SizeF& target_size) const {
  if (!image_ || image_->ErrorOccurred()) {
    return Image::NullImage();
  }
  Image* image = image_->GetImage();
  auto* svg_image = DynamicTo<SVGImage>(image);
  if (!svg_image) {
    return image;
  }
  const SVGImageViewInfo* view_info =
      SVGImageForContainer::CreateViewInfo(*svg_image, url_);
  return SVGImageForContainer::Create(*svg_image, target_size,
                                      style.EffectiveZoom(), view_info,
                                      node.GetDocument()
                                          .GetStyleEngine()
                                          .ResolveColorSchemeForEmbedding(
                                              &style));
}
bool StyleFetchedImage::KnownToBeOpaque(const Document&,
                                        const ComputedStyle&) const {
  return image_ && image_->HasImage() && !image_->ErrorOccurred() &&
         image_->GetImage()->IsOpaque();
}
ImageResourceContent* StyleFetchedImage::CachedImage() const {
  return image_.Get();
}
void StyleFetchedImage::Trace(Visitor* visitor) const {
  visitor->Trace(image_);
  visitor->Trace(url_data_);
  visitor->Trace(document_);
  StyleImage::Trace(visitor);
  ImageResourceObserver::Trace(visitor);
}
bool StyleFetchedImage::IsEqual(const StyleImage& other) const {
  return this == &other;
}
void StyleFetchedImage::Prefinalize() {
  if (image_) {
    image_->DidRemoveObserver();
    image_ = nullptr;
  }
}
void StyleFetchedImage::ImageNotifyFinished(ImageResourceContent*) {
  document_.Clear();
}
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


LayoutImageResourceStyleImage::~LayoutImageResourceStyleImage() = default;
void LayoutImageResourceStyleImage::Trace(Visitor* visitor) const {
  visitor->Trace(style_image_);
  LayoutImageResource::Trace(visitor);
}
void LayoutImageResourceStyleImage::Initialize(LayoutObject* layout_object) {
  LayoutImageResource::Initialize(layout_object);

  if (style_image_->IsImageResource()) {
    cached_image_ = To<StyleFetchedImage>(style_image_.Get())->CachedImage();
  }

  style_image_->AddClient(layout_object_);
}
void LayoutImageResourceStyleImage::Shutdown() {
  DCHECK(layout_object_);
  style_image_->RemoveClient(layout_object_);
  cached_image_ = nullptr;
}
scoped_refptr<Image> LayoutImageResourceStyleImage::GetImage(
    const gfx::SizeF& size) const {
  if (style_image_->IsPendingImage()) {
    return nullptr;
  }
  const Node* node = layout_object_->GetNode();
  if (!node) {
    node = &layout_object_->GetDocument();
  }
  return style_image_->GetImage(*layout_object_, *node,
                                layout_object_->StyleRef(), size);
}
NaturalSizingInfo LayoutImageResourceStyleImage::GetNaturalDimensions(
    float multiplier) const {
  return style_image_->GetNaturalSizingInfo(multiplier, ImageOrientation());
}
RespectImageOrientationEnum LayoutImageResourceStyleImage::ImageOrientation()
    const {
  RespectImageOrientationEnum respect_orientation =
      layout_object_->StyleRef().ImageOrientation();
  return style_image_->ForceOrientationIfNecessary(respect_orientation);
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

#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
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
#endif
float ComputeTextWidth(const StringView&, const ComputedStyle&) {
  return 0.0f;
}
#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
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
#endif

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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void LayoutTableCell::InvalidateLayoutResultCacheAfterMeasure() const {}
#endif
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
void PaintLayerScrollableArea::UpdateAfterOverflowRecalc() {
  LayoutBox* box = GetLayoutBox();
  if (!box)
    return;
  PhysicalRect new_overflow_rect = box->ScrollableOverflowRect();
  new_overflow_rect.Unite(
      PhysicalRect(new_overflow_rect.offset,
                   LayoutContentRect(kExcludeScrollbars).size));
  overflow_rect_ = new_overflow_rect;
}
ScrollOffset PaintLayerScrollableArea::GetScrollOffset() const {
  // Some standalone diagnostic layout paths query a missing layer scrollable area.
  // Real scrollable areas still return their Blink-owned stored offset.
  if (reinterpret_cast<uintptr_t>(this) == 0)
    return ScrollOffset();
  return scroll_offset_;
}
PhysicalAxes PaintLayerScrollableArea::ScrollableAxes() const {
  const auto* box = GetLayoutBox();
  if (!box || !box->IsScrollContainer())
    return kPhysicalAxesNone;
  if (box->IsLayoutView())
    return kPhysicalAxesBoth;

  PhysicalAxes axes = kPhysicalAxesNone;
  const auto& style = box->StyleRef();
  if (style.IsOverflowValueScrollableX())
    axes |= kPhysicalAxesHorizontal;
  if (style.IsOverflowValueScrollableY())
    axes |= kPhysicalAxesVertical;
  return axes;
}
int PaintLayerScrollableArea::VerticalScrollbarWidth(
    OverlayScrollbarClipBehavior overlay_scrollbar_clip_behavior) const {
  if (!HasVerticalScrollbar())
    return 0;
  if (overlay_scrollbar_clip_behavior == kIgnoreOverlayScrollbarSize &&
      GetLayoutBox()->StyleRef().OverflowY() == EOverflow::kOverlay) {
    return 0;
  }
  if ((overlay_scrollbar_clip_behavior == kIgnoreOverlayScrollbarSize ||
       !VerticalScrollbar()->ShouldParticipateInHitTesting()) &&
      VerticalScrollbar()->IsOverlayScrollbar()) {
    return 0;
  }
  return VerticalScrollbar()->ScrollbarThickness();
}
int PaintLayerScrollableArea::HorizontalScrollbarHeight(
    OverlayScrollbarClipBehavior overlay_scrollbar_clip_behavior) const {
  if (!HasHorizontalScrollbar())
    return 0;
  if (overlay_scrollbar_clip_behavior == kIgnoreOverlayScrollbarSize &&
      GetLayoutBox()->StyleRef().OverflowX() == EOverflow::kOverlay) {
    return 0;
  }
  if ((overlay_scrollbar_clip_behavior == kIgnoreOverlayScrollbarSize ||
       !HorizontalScrollbar()->ShouldParticipateInHitTesting()) &&
      HorizontalScrollbar()->IsOverlayScrollbar()) {
    return 0;
  }
  return HorizontalScrollbar()->ScrollbarThickness();
}
LayoutUnit PaintLayerScrollableArea::ScrollWidth() const {
  return overflow_rect_.Width();
}
LayoutUnit PaintLayerScrollableArea::ScrollHeight() const {
  return overflow_rect_.Height();
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
  inner_possibly_pseudo_node_ = node;
  if (auto* element = DynamicTo<Element>(node)) {
    inner_element_ = element;
  } else {
    inner_element_ = node ? node->parentElement() : nullptr;
  }
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
                                       bool all_data_received) {
  encoded_image_data_ = std::move(data);
  if (!encoded_image_data_.get())
    return kSizeAvailable;

  size_t length = encoded_image_data_->size();
  if (!length)
    return kSizeAvailable;

  return DataChanged(all_data_received);
}
SkBitmap Image::AsSkBitmapForCurrentFrame(RespectImageOrientationEnum) {
  return SkBitmap();
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
void Image::DrawPattern(GraphicsContext& context,
                        const cc::PaintFlags& flags,
                        const gfx::RectF& dest_rect,
                        const ImageTilingInfo& tiling_info,
                        const ImageDrawOptions& draw_options) {
  cc::PaintCanvas* canvas = context.Canvas();
  if (!canvas || dest_rect.IsEmpty() || tiling_info.image_rect.IsEmpty() ||
      tiling_info.scale.x() <= 0.0f || tiling_info.scale.y() <= 0.0f) {
    return;
  }

  Image::SizeConfig size_config;
  size_config.apply_orientation = draw_options.respect_orientation;
  const gfx::SizeF image_size = SizeWithConfigAsFloat(size_config);
  gfx::RectF source_rect = tiling_info.image_rect;
  source_rect.Intersect(gfx::RectF(0.0f, 0.0f, image_size.width(),
                                   image_size.height()));
  if (source_rect.IsEmpty()) {
    return;
  }

  const float draw_width = source_rect.width() * tiling_info.scale.x();
  const float draw_height = source_rect.height() * tiling_info.scale.y();
  const float advance_x = draw_width + tiling_info.spacing.width();
  const float advance_y = draw_height + tiling_info.spacing.height();
  if (draw_width <= 0.0f || draw_height <= 0.0f || advance_x <= 0.0f ||
      advance_y <= 0.0f) {
    return;
  }

  float start_x = tiling_info.phase.x() + source_rect.x() * tiling_info.scale.x();
  float start_y = tiling_info.phase.y() + source_rect.y() * tiling_info.scale.y();
  while (start_x > dest_rect.x()) {
    start_x -= advance_x;
  }
  while (start_y > dest_rect.y()) {
    start_y -= advance_y;
  }
  while (start_x + draw_width <= dest_rect.x()) {
    start_x += advance_x;
  }
  while (start_y + draw_height <= dest_rect.y()) {
    start_y += advance_y;
  }

  canvas->save();
  canvas->clipRect(gfx::RectFToSkRect(dest_rect));
  for (float y = start_y; y < dest_rect.bottom(); y += advance_y) {
    for (float x = start_x; x < dest_rect.right(); x += advance_x) {
      const gfx::RectF tile_dest(x, y, draw_width, draw_height);
      if (!tile_dest.Intersects(dest_rect)) {
        continue;
      }
      Draw(canvas, flags, tile_dest, source_rect, draw_options);
    }
  }
  canvas->restore();
}
PaintImageBuilder Image::CreatePaintImageBuilder(
    std::optional<PaintImage::Id> paint_id) {
  auto builder = PaintImageBuilder::WithDefault();
  builder.set_id(paint_id.value_or(stable_image_id_));
  builder.set_animation_type(PaintImage::AnimationType::kStatic)
      .set_is_multipart(is_multipart_);
  return builder;
}
void CustomScrollbar::ClearPaintFlags() {}
const ComputedStyle* CustomScrollbar::GetScrollbarPartStyleForCursor(
    ScrollbarPart) const {
  return nullptr;
}
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
extern "C" int g_standalone_text_decoration_painter_constructed = 0;
extern "C" int g_standalone_text_decoration_begin_called = 0;
extern "C" int g_standalone_text_decoration_except_line_through_called = 0;
extern "C" int g_standalone_text_decoration_only_line_through_called = 0;
extern "C" int g_standalone_decoration_line_painter_paint_called = 0;
extern "C" int g_standalone_html_factory_create_html_count = 0;
extern "C" int g_standalone_html_factory_create_body_count = 0;
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
const LineRelativeRect&
HighlightPainter::SelectionPaintState::LineRelativeSelectionRect() {
  static LineRelativeRect* rect = new LineRelativeRect{LineRelativeOffset(LayoutUnit(), LayoutUnit()), LogicalSize()};
  return *rect;
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
void ScopedTextShadowPainter::ApplyShadowList(GraphicsContext&,
                                              const TextPaintStyle&) {}
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif
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
FieldsetLayoutAlgorithm::FieldsetLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params),
      writing_direction_(GetConstraintSpace().GetWritingDirection()),
      consumed_block_size_(LayoutUnit()) {}
LayoutUnit LayoutMedia::ComputePanelWidth(const PhysicalRect& rect) const {
  return rect.Width();
}
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
OutOfFlowLayoutPart::OutOfFlowLayoutPart(BoxFragmentBuilder* container_builder)
    : container_builder_(container_builder),
      multicol_children_(nullptr),
      fragmentainer_consumed_block_size_() {}
void OutOfFlowLayoutPart::Run() {
  ++g_standalone_oof_layout_part_run_called;
  if (!container_builder_) {
    return;
  }

  const BlockNode& container_node = container_builder_->Node();
  if (container_node.ChildLayoutBlockedByDisplayLock()) {
    return;
  }

  HeapVector<LogicalOofPositionedNode> candidates;
  container_builder_->SwapOutOfFlowPositionedCandidates(&candidates);
  g_standalone_oof_candidate_count += static_cast<int>(candidates.size());
  constexpr wtf_size_t kStandaloneMaxOofCandidatesPerContainer = 256;
  if (candidates.size() > kStandaloneMaxOofCandidatesPerContainer) {
    g_standalone_oof_safety_limit_hit = 1;
    candidates.Shrink(kStandaloneMaxOofCandidatesPerContainer);
  }

  for (const auto& candidate : candidates) {
    BlockNode child = candidate.Node();
    if (!child) {
      continue;
    }
    ++g_standalone_oof_descendant_collected;

    LayoutBox* child_box = child.GetLayoutBox();
    LayoutBox* container_box = container_builder_->Node().GetLayoutBox();
    LayoutBox* standalone_containing_block_box = container_box;
    if (child_box && container_box &&
        child_box->ContainingBlock() != container_box) {
      if (auto* containing_block_box = child_box->ContainingBlock();
          containing_block_box && !containing_block_box->IsLayoutView() &&
          child.Style().GetPosition() != EPosition::kFixed) {
        if (containing_block_box->StyleRef().Display() == EDisplay::kInlineBlock &&
            containing_block_box->LocationContainer() == container_box) {
          standalone_containing_block_box = containing_block_box;
        } else {
          ++g_standalone_oof_candidate_dropped_at_root;
          ++g_standalone_oof_unsupported_inline_containing_block;
          continue;
        }
      } else {
        if (container_box->IsLayoutView()) {
          ++g_standalone_oof_candidate_dropped_at_root;
          ++g_standalone_oof_unsupported_inline_containing_block;
          continue;
        } else {
          ++g_standalone_oof_candidate_repropagated;
          container_builder_->AddOutOfFlowDescendant(candidate);
          continue;
        }
      }
    }

    const ComputedStyle& style = child.Style();
    const PhysicalToLogical<const Length&> logical_insets(
        style.GetWritingDirection(), style.Top(), style.Right(),
        style.Bottom(), style.Left());
    const Length& inline_start = logical_insets.InlineStart();
    const Length& inline_end = logical_insets.InlineEnd();
    const Length& block_start = logical_insets.BlockStart();
    const Length& block_end = logical_insets.BlockEnd();
    const ConstraintSpace& parent_space = container_builder_->GetConstraintSpace();
    BoxStrut container_borders = container_builder_->Borders();
    LogicalOffset containing_block_offset;
    LogicalSize containing_border_box_size =
        container_builder_->InitialBorderBoxSize();
    if (standalone_containing_block_box &&
        standalone_containing_block_box != container_box) {
      BlockNode containing_block_node(standalone_containing_block_box);
      container_borders = ComputeBorders(parent_space, containing_block_node);
      containing_border_box_size = ToLogicalSize(
          standalone_containing_block_box->StitchedSize(),
          parent_space.GetWritingMode());
      PhysicalSize container_physical_size =
          ToPhysicalSize(container_builder_->InitialBorderBoxSize(),
                         parent_space.GetWritingMode());
      WritingModeConverter converter(parent_space.GetWritingDirection(),
                                     container_physical_size);
      containing_block_offset = converter.ToLogical(
          standalone_containing_block_box->PhysicalLocation(),
          standalone_containing_block_box->StitchedSize());
    }
    const LogicalSize containing_size(
        (containing_border_box_size.inline_size - container_borders.InlineSum())
            .ClampNegativeToZero(),
        (containing_border_box_size.block_size - container_borders.BlockSum())
            .ClampNegativeToZero());
    auto ResolveStandaloneInset =
        [](const Length& length,
           LayoutUnit percentage_basis) -> std::optional<LayoutUnit> {
      if (length.IsFixed() || length.IsPercent() || length.IsCalculated()) {
        return ValueForLength(length, percentage_basis);
      }
      return std::nullopt;
    };
    const std::optional<LayoutUnit> inline_start_offset =
        ResolveStandaloneInset(inline_start, containing_size.inline_size);
    const std::optional<LayoutUnit> inline_end_offset =
        ResolveStandaloneInset(inline_end, containing_size.inline_size);
    const std::optional<LayoutUnit> block_start_offset =
        ResolveStandaloneInset(block_start, containing_size.block_size);
    const std::optional<LayoutUnit> block_end_offset =
        ResolveStandaloneInset(block_end, containing_size.block_size);

    LogicalSize available_size = containing_size;
    if (!style.LogicalWidth().IsFixed()) {
      if (inline_start_offset && !inline_end_offset) {
        available_size.inline_size =
            (containing_size.inline_size - *inline_start_offset)
                .ClampNegativeToZero();
      } else if (!inline_start_offset && inline_end_offset) {
        available_size.inline_size =
            (containing_size.inline_size - *inline_end_offset)
                .ClampNegativeToZero();
      }
    }
    if (!style.LogicalHeight().IsFixed()) {
      if (block_start_offset && !block_end_offset) {
        available_size.block_size =
            (containing_size.block_size - *block_start_offset)
                .ClampNegativeToZero();
      } else if (!block_start_offset && block_end_offset) {
        available_size.block_size =
            (containing_size.block_size - *block_end_offset)
                .ClampNegativeToZero();
      }
    }
    bool is_fixed_inline_size = false;
    bool is_fixed_block_size = false;
    const bool inline_auto_should_fit_content = style.LogicalWidth().HasAuto();
    const bool block_auto_should_fit_content = style.LogicalHeight().HasAuto();
    const BoxStrut child_border_padding =
        ComputeBorders(parent_space, child) +
        ComputePadding(parent_space, style);
    if (style.LogicalWidth().IsFixed()) {
      available_size.inline_size = LayoutUnit(style.LogicalWidth().Pixels());
      if (style.BoxSizing() == EBoxSizing::kContentBox) {
        available_size.inline_size += child_border_padding.InlineSum();
      } else {
        available_size.inline_size = std::max(
            child_border_padding.InlineSum(), available_size.inline_size);
      }
      is_fixed_inline_size = true;
    }
    if (style.LogicalHeight().IsFixed()) {
      available_size.block_size = LayoutUnit(style.LogicalHeight().Pixels());
      if (style.BoxSizing() == EBoxSizing::kContentBox) {
        available_size.block_size += child_border_padding.BlockSum();
      } else {
        available_size.block_size =
            std::max(child_border_padding.BlockSum(), available_size.block_size);
      }
      is_fixed_block_size = true;
    }
    if (!style.LogicalWidth().IsFixed() && inline_start_offset &&
        inline_end_offset) {
      available_size.inline_size =
          (containing_size.inline_size - *inline_start_offset -
           *inline_end_offset)
              .ClampNegativeToZero();
      is_fixed_inline_size = true;
    }
    if (!style.LogicalHeight().IsFixed() && block_start_offset &&
        block_end_offset) {
      available_size.block_size =
          (containing_size.block_size - *block_start_offset -
           *block_end_offset)
              .ClampNegativeToZero();
      is_fixed_block_size = true;
    }
    ConstraintSpaceBuilder intrinsic_space_builder(
        parent_space, style.GetWritingDirection(), /*is_new_fc=*/true);
    intrinsic_space_builder.SetAvailableSize(available_size);
    if (is_fixed_inline_size) {
      intrinsic_space_builder.SetIsFixedInlineSize(true);
    }
    if (is_fixed_block_size) {
      intrinsic_space_builder.SetIsFixedBlockSize(true);
    }
    const ConstraintSpace child_intrinsic_space =
        intrinsic_space_builder.ToConstraintSpace();
    auto MinMaxSizesFunc = [&](SizeType type) -> MinMaxSizesResult {
      return child.ComputeMinMaxSizes(style.GetWritingMode(), type,
                                      child_intrinsic_space);
    };
    if (style.LogicalWidth().HasContentOrIntrinsic()) {
      const LayoutUnit inline_size = ResolveMainInlineLength(
          child_intrinsic_space, style, child_border_padding, MinMaxSizesFunc,
          style.LogicalWidth(), &Length::FitContent(),
          available_size.inline_size);
      if (inline_size != kIndefiniteSize) {
        available_size.inline_size = inline_size;
        is_fixed_inline_size = true;
      }
    }
    if (style.LogicalMinWidth().HasContentOrIntrinsic() ||
        style.LogicalMaxWidth().HasContentOrIntrinsic()) {
      const MinMaxSizes min_max_inline_sizes = ComputeMinMaxInlineSizes(
          child_intrinsic_space, child, child_border_padding,
          /* auto_min_length */ nullptr, MinMaxSizesFunc,
          TransferredSizesMode::kNormal, FitContentMode::kNormal,
          available_size.inline_size);
      available_size.inline_size =
          min_max_inline_sizes.ClampSizeToMinAndMax(available_size.inline_size);
      is_fixed_inline_size = true;
    }
    ConstraintSpaceBuilder child_space_builder(
        parent_space, style.GetWritingDirection(), /*is_new_fc=*/true);
    child_space_builder.SetAvailableSize(available_size);
    if (inline_auto_should_fit_content && !is_fixed_inline_size) {
      child_space_builder.SetInlineAutoBehavior(AutoSizeBehavior::kFitContent);
    }
    if (block_auto_should_fit_content && !is_fixed_block_size) {
      child_space_builder.SetBlockAutoBehavior(AutoSizeBehavior::kFitContent);
    }
    if (is_fixed_inline_size) {
      child_space_builder.SetIsFixedInlineSize(true);
    }
    if (is_fixed_block_size) {
      child_space_builder.SetIsFixedBlockSize(true);
    }
    child_space_builder.SetPercentageResolutionSize(
        parent_space.PercentageResolutionSize());
    if (parent_space.IsHiddenForPaint()) {
      child_space_builder.SetIsHiddenForPaint(true);
    }

    ++g_standalone_oof_layout_attempted;
    const LayoutResult* result = child.Layout(
        child_space_builder.ToConstraintSpace(), candidate.GetBreakToken());
    if (!result) {
      ++g_standalone_oof_layout_null_results;
      continue;
    }
    const auto& physical_fragment =
        To<PhysicalBoxFragment>(result->GetPhysicalFragment());
    LogicalOffset offset =
        containing_block_offset + candidate.StaticPosition().offset;
    if (inline_start_offset) {
      offset.inline_offset =
          containing_block_offset.inline_offset + container_borders.inline_start +
          *inline_start_offset;
    } else if (inline_end_offset) {
      const LogicalSize child_size =
          ToLogicalSize(physical_fragment.Size(), style.GetWritingMode());
      offset.inline_offset =
          containing_block_offset.inline_offset + container_borders.inline_start +
          containing_size.inline_size - *inline_end_offset -
          child_size.inline_size;
    }
    if (block_start_offset) {
      offset.block_offset =
          containing_block_offset.block_offset + container_borders.block_start +
          *block_start_offset;
    } else if (block_end_offset) {
      const LogicalSize child_size =
          ToLogicalSize(physical_fragment.Size(), style.GetWritingMode());
      offset.block_offset =
          containing_block_offset.block_offset + container_borders.block_start +
          containing_size.block_size - *block_end_offset -
          child_size.block_size;
    }
    if ((physical_fragment.Size().width == LayoutUnit() ||
         physical_fragment.Size().height == LayoutUnit()) &&
        ((style.LogicalWidth().IsFixed() && style.LogicalWidth().Pixels() > 0) ||
         (style.LogicalHeight().IsFixed() &&
          style.LogicalHeight().Pixels() > 0))) {
      ++g_standalone_oof_zero_size_fragments;
    }
    container_builder_->AddResult(*result, offset);
    container_builder_->SetHasOutOfFlowFragmentChild(true);
    ++g_standalone_oof_fragment_created;
  }
}
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
#if defined(HTML_CSS_RENDERER_STANDALONE)
namespace {
void SetStandaloneChildLayoutBoxLocation(
    const PhysicalBoxFragment& child_fragment,
    PhysicalOffset child_fragment_offset) {
  if (child_fragment.IsLayoutObjectDestroyedOrMoved() ||
      !child_fragment.IsFirstForNode()) {
    return;
  }

  auto* child_layout_box =
      DynamicTo<LayoutBox>(child_fragment.GetMutableLayoutObject());
  if (!child_layout_box) {
    return;
  }

  child_layout_box->SetLocation(child_fragment_offset);
}
}  // namespace

void UpdateChildLayoutBoxLocations(const PhysicalBoxFragment& fragment) {
  if (fragment.GetLayoutObject()->ChildLayoutBlockedByDisplayLock()) {
    return;
  }

  if (const FragmentItems* items = fragment.Items()) {
    for (InlineCursor cursor(fragment, *items); cursor;
         cursor.MoveToNext()) {
      const PhysicalBoxFragment* child_box_fragment =
          cursor.Current().BoxFragment();
      if (!child_box_fragment) {
        continue;
      }
      SetStandaloneChildLayoutBoxLocation(
          *child_box_fragment, cursor.Current().OffsetInContainerFragment());
    }
  }

  for (const auto& child : fragment.Children()) {
    const auto* child_box_fragment =
        DynamicTo<PhysicalBoxFragment>(child.get());
    if (!child_box_fragment || child_box_fragment->IsColumnBox()) {
      continue;
    }
    SetStandaloneChildLayoutBoxLocation(*child_box_fragment, child.offset);
  }
}
#else
void UpdateChildLayoutBoxLocations(const PhysicalBoxFragment&) {}
#endif
NamingScope* ToTriggerScopedName(const ScopedCSSName&, const Element&) {
  return nullptr;
}
void NamingScope::Trace(Visitor*) const {}

PaintLayerScrollableArea::~PaintLayerScrollableArea() = default;
PaintLayerScrollableArea::PaintLayerScrollableArea(PaintLayer& layer)
    : ScrollableArea(StandaloneNoopTaskRunner()),
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
namespace {
const LayoutObject& StandaloneScrollbarStyleSource(const LayoutBox& box) {
  if (IsA<LayoutView>(box)) {
    Document& document = box.GetDocument();
    if (Element* body = document.body()) {
      if (LayoutObject* body_layout = body->GetLayoutObject()) {
        if (body_layout->StyleRef().HasCustomScrollbarStyle(body))
          return *body_layout;
      }
    }
    if (Element* document_element = document.documentElement()) {
      if (LayoutObject* document_layout = document_element->GetLayoutObject()) {
        if (document_layout->StyleRef().HasCustomScrollbarStyle(
                document_element)) {
          return *document_layout;
        }
      }
    }
  } else if (!box.GetNode() && box.Parent()) {
    return *box.Parent();
  }
  return box;
}

void StandaloneComputeScrollbarNeed(PaintLayerScrollableArea& area,
                                    bool& needs_horizontal,
                                    bool& needs_vertical) {
  needs_horizontal = false;
  needs_vertical = false;
  LayoutBox* box = area.GetLayoutBox();
  if (!box || !box->GetFrame() || !box->GetFrame()->GetSettings() ||
      box->GetFrame()->GetSettings()->GetHideScrollbars() ||
      box->StyleRef().UsedScrollbarWidth() == EScrollbarWidth::kNone) {
    return;
  }

  mojom::blink::ScrollbarMode horizontal_mode =
      mojom::blink::ScrollbarMode::kAuto;
  mojom::blink::ScrollbarMode vertical_mode =
      mojom::blink::ScrollbarMode::kAuto;
  if (auto* layout_view = DynamicTo<LayoutView>(box)) {
    layout_view->CalculateScrollbarModes(horizontal_mode, vertical_mode);
  } else {
    const EOverflow overflow_x = box->StyleRef().OverflowX();
    if (overflow_x == EOverflow::kScroll) {
      horizontal_mode = mojom::blink::ScrollbarMode::kAlwaysOn;
    } else if (overflow_x == EOverflow::kHidden ||
               overflow_x == EOverflow::kClip ||
               overflow_x == EOverflow::kVisible) {
      horizontal_mode = mojom::blink::ScrollbarMode::kAlwaysOff;
    }

    const EOverflow overflow_y = box->StyleRef().OverflowY();
    if (overflow_y == EOverflow::kScroll) {
      vertical_mode = mojom::blink::ScrollbarMode::kAlwaysOn;
    } else if (overflow_y == EOverflow::kHidden ||
               overflow_y == EOverflow::kClip ||
               overflow_y == EOverflow::kVisible) {
      vertical_mode = mojom::blink::ScrollbarMode::kAlwaysOff;
    }
  }

  if (horizontal_mode == mojom::blink::ScrollbarMode::kAlwaysOn)
    needs_horizontal = true;
  else if (horizontal_mode == mojom::blink::ScrollbarMode::kAuto)
    needs_horizontal = area.HasHorizontalOverflow();

  if (vertical_mode == mojom::blink::ScrollbarMode::kAlwaysOn)
    needs_vertical = true;
  else if (vertical_mode == mojom::blink::ScrollbarMode::kAuto)
    needs_vertical = area.HasVerticalOverflow();
}
}  // namespace

void PaintLayerScrollableArea::UpdateAfterLayout() {
  EnqueueForStickyUpdateIfNeeded();
  UpdateAfterOverflowRecalc();
  if (!ScrollbarsCanBeActive())
    return;

  bool needs_horizontal_scrollbar = false;
  bool needs_vertical_scrollbar = false;
  StandaloneComputeScrollbarNeed(*this, needs_horizontal_scrollbar,
                                 needs_vertical_scrollbar);
  if (needs_horizontal_scrollbar || needs_vertical_scrollbar) {
    GetLayoutBox()->GetMutableForPainting().EnsureId();
  }
  SetHasHorizontalScrollbar(needs_horizontal_scrollbar);
  SetHasVerticalScrollbar(needs_vertical_scrollbar);

  const gfx::Size visible = VisibleContentRect(kExcludeScrollbars).size();
  const gfx::Size contents = ContentsSize();
  if (Scrollbar* scrollbar = HorizontalScrollbar())
    scrollbar->SetProportion(visible.width(), contents.width());
  if (Scrollbar* scrollbar = VerticalScrollbar())
    scrollbar->SetProportion(visible.height(), contents.height());
  PositionOverflowControls();
}
void PaintLayerScrollableArea::ScrollbarManager::SetHasHorizontalScrollbar(
    bool has_scrollbar) {
  if (has_scrollbar) {
    if (!h_bar_) {
      h_bar_ = CreateScrollbar(kHorizontalScrollbar);
      h_bar_is_attached_ = 1;
      if (h_bar_)
        ScrollableArea()->DidAddScrollbar(*h_bar_, kHorizontalScrollbar);
    } else {
      h_bar_is_attached_ = 1;
    }
  } else {
    h_bar_is_attached_ = 0;
    if (h_bar_)
      DestroyScrollbar(kHorizontalScrollbar);
  }
}
void PaintLayerScrollableArea::ScrollbarManager::SetHasVerticalScrollbar(
    bool has_scrollbar) {
  if (has_scrollbar) {
    if (!v_bar_) {
      v_bar_ = CreateScrollbar(kVerticalScrollbar);
      v_bar_is_attached_ = 1;
      if (v_bar_)
        ScrollableArea()->DidAddScrollbar(*v_bar_, kVerticalScrollbar);
    } else {
      v_bar_is_attached_ = 1;
    }
  } else {
    v_bar_is_attached_ = 0;
    if (v_bar_)
      DestroyScrollbar(kVerticalScrollbar);
  }
}
Scrollbar* PaintLayerScrollableArea::ScrollbarManager::CreateScrollbar(
    ScrollbarOrientation orientation) {
  LayoutBox* box = ScrollableArea()->GetLayoutBox();
  if (!box || !box->GetDocument().View())
    return nullptr;

  const LayoutObject& style_source = StandaloneScrollbarStyleSource(*box);
  Scrollbar* scrollbar =
      MakeGarbageCollected<Scrollbar>(ScrollableArea(), orientation,
                                      &style_source);
  box->GetDocument().View()->AddScrollbar(scrollbar);
  return scrollbar;
}
void PaintLayerScrollableArea::ScrollbarManager::DestroyScrollbar(
    ScrollbarOrientation orientation) {
  Member<Scrollbar>& scrollbar =
      orientation == kHorizontalScrollbar ? h_bar_ : v_bar_;
  if (!scrollbar)
    return;

  ScrollableArea()->SetScrollbarNeedsPaintInvalidation(orientation);
  ScrollableArea()->WillRemoveScrollbar(*scrollbar, orientation);
  if (LayoutBox* box = ScrollableArea()->GetLayoutBox()) {
    if (LocalFrameView* view = box->GetDocument().View())
      view->RemoveScrollbar(scrollbar);
  }
  scrollbar->DisconnectFromScrollableArea();
  scrollbar = nullptr;
}
void PaintLayerScrollableArea::ScrollbarManager::DestroyDetachedScrollbars() {
  if (h_bar_ && !h_bar_is_attached_)
    DestroyScrollbar(kHorizontalScrollbar);
  if (v_bar_ && !v_bar_is_attached_)
    DestroyScrollbar(kVerticalScrollbar);
}
void PaintLayerScrollableArea::ScrollbarManager::Dispose() {
  h_bar_is_attached_ = 0;
  v_bar_is_attached_ = 0;
  DestroyScrollbar(kHorizontalScrollbar);
  DestroyScrollbar(kVerticalScrollbar);
}
void PaintLayerScrollableArea::ScrollbarManager::Trace(Visitor* visitor) const {
  visitor->Trace(scrollable_area_);
  visitor->Trace(h_bar_);
  visitor->Trace(v_bar_);
}
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
bool PaintLayerScrollableArea::HasOverlayOverflowControls() const {
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
  gfx::Size visible_size = VisibleContentRect(kExcludeScrollbars).size();
  return gfx::Vector2d(std::max(0, ContentsSize().width() -
                                       visible_size.width()),
                       std::max(0, ContentsSize().height() -
                                       visible_size.height()));
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
bool PaintLayerScrollableArea::ScrollbarsCanBeActive() const {
  LayoutBox* box = GetLayoutBox();
  if (!box || !box->GetFrame())
    return false;
  LocalFrameView* frame_view = box->GetFrameView();
  return frame_view && box->GetFrame()->GetDocument();
}
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
void PaintLayerScrollableArea::DisposeImpl() {
  scrollbar_manager_.Dispose();
  ClearScrollableArea();
  layer_ = nullptr;
}
void PaintLayerScrollableArea::ScrollControlWasSetNeedsPaintInvalidation() {}
void PaintLayerScrollableArea::InvalidatePaintOfScrollControlsIfNeeded(
    const PaintInvalidatorContext&) {}
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
  LayoutBox* box = GetLayoutBox();
  if (box && box->GetFrame() && box->GetFrame()->GetPage())
    return box->GetFrame()->GetPage()->GetScrollbarTheme();
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
void PaintLayerScrollableArea::UpdateScrollOffset(const ScrollOffset& offset,
                                                  mojom::blink::ScrollType,
                                                  cc::ScrollSourceType) {
  scroll_offset_ = offset;
}
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
    const FilterOperations& operations) const {
  CompositorFilterOperations filters;
  for (FilterOperation* op : operations.Operations()) {
    switch (op->GetType()) {
      case FilterOperation::OperationType::kReference:
        // Reference SVG filters still require the broader SVG filter graph
        // stack. Keep them fail-soft while restoring basic CSS filter metadata.
        break;
      case FilterOperation::OperationType::kGrayscale:
      case FilterOperation::OperationType::kSepia:
      case FilterOperation::OperationType::kSaturate:
      case FilterOperation::OperationType::kHueRotate: {
        float amount = To<BasicColorMatrixFilterOperation>(*op).Amount();
        switch (op->GetType()) {
          case FilterOperation::OperationType::kGrayscale:
            filters.AppendGrayscaleFilter(amount);
            break;
          case FilterOperation::OperationType::kSepia:
            filters.AppendSepiaFilter(amount);
            break;
          case FilterOperation::OperationType::kSaturate:
            filters.AppendSaturateFilter(amount);
            break;
          case FilterOperation::OperationType::kHueRotate:
            filters.AppendHueRotateFilter(amount);
            break;
          default:
            break;
        }
        break;
      }
      case FilterOperation::OperationType::kLuminanceToAlpha:
      case FilterOperation::OperationType::kConvolveMatrix:
      case FilterOperation::OperationType::kComponentTransfer:
      case FilterOperation::OperationType::kTurbulence:
        break;
      case FilterOperation::OperationType::kColorMatrix: {
        Vector<float> matrix_values =
            To<ColorMatrixFilterOperation>(*op).Values();
        filters.AppendColorMatrixFilter(std::move(matrix_values));
        break;
      }
      case FilterOperation::OperationType::kInvert:
      case FilterOperation::OperationType::kOpacity:
      case FilterOperation::OperationType::kBrightness:
      case FilterOperation::OperationType::kContrast: {
        float amount = To<BasicComponentTransferFilterOperation>(*op).Amount();
        switch (op->GetType()) {
          case FilterOperation::OperationType::kInvert:
            filters.AppendInvertFilter(amount);
            break;
          case FilterOperation::OperationType::kOpacity:
            filters.AppendOpacityFilter(amount);
            break;
          case FilterOperation::OperationType::kBrightness:
            filters.AppendBrightnessFilter(amount);
            break;
          case FilterOperation::OperationType::kContrast:
            filters.AppendContrastFilter(amount);
            break;
          default:
            break;
        }
        break;
      }
      case FilterOperation::OperationType::kBlur: {
        float pixel_radius =
            To<BlurFilterOperation>(*op).StdDeviation().Pixels();
        pixel_radius *= shorthand_scale_;
        filters.AppendBlurFilter(pixel_radius);
        break;
      }
      case FilterOperation::OperationType::kDropShadow: {
        const ShadowData& shadow = To<DropShadowFilterOperation>(*op).Shadow();
        const gfx::Vector2d floored_offset = gfx::ToFlooredVector2d(
            gfx::ScaleVector2d(shadow.Offset(), shorthand_scale_));
        float radius = shadow.BlurValue() * shorthand_scale_;
        filters.AppendDropShadowFilter(
            floored_offset, radius,
            shadow.GetColor().Resolve(current_color_, color_scheme_));
        break;
      }
      case FilterOperation::OperationType::kBoxReflect:
        break;
    }
  }
  if (!filters.IsEmpty()) {
    filters.SetReferenceBox(reference_box_);
  }
  return filters;
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
bool StyleImage::IsCorsSameOrigin() const {
  return true;
}
RespectImageOrientationEnum StyleImage::ForceOrientationIfNecessary(
    RespectImageOrientationEnum orientation) const {
  return orientation;
}
gfx::SizeF StyleImage::ApplyZoom(const gfx::SizeF& size, float multiplier) {
  if (multiplier == 1.0f) {
    return size;
  }

  gfx::SizeF scaled_size = gfx::ScaleSize(size, multiplier);
  if (size.width() > 0) {
    scaled_size.set_width(std::max(1.0f, scaled_size.width()));
  }
  if (size.height() > 0) {
    scaled_size.set_height(std::max(1.0f, scaled_size.height()));
  }
  return scaled_size;
}
scoped_refptr<Image> Image::LoadPlatformResource(
    int resource_id,
    ui::ResourceScaleFactor) {
  if (resource_id != IDR_BROKENIMAGE) {
    return Image::NullImage();
  }

  // Chromium serves this PNG from blink_image_resources.pak. The standalone
  // cut embeds the same Blink broken-image icon so the native fallback shadow
  // tree can paint through LayoutImageResource/ImagePainter.
  static constexpr unsigned char kBrokenImagePng[] = {
      137, 80,  78,  71,  13,  10,  26,  10,  0,   0,   0,   13,  73,
      72,  68,  82,  0,   0,   0,   14,  0,   0,   0,   16,  8,   6,
      0,   0,   0,   38,  148, 78,  58,  0,   0,   1,   135, 73,  68,
      65,  84,  40,  83,  141, 144, 73,  47,  67,  81,  24,  134, 191,
      181, 95,  132, 165, 132, 159, 32,  54,  88,  88,  179, 176, 183,
      34,  36,  106, 232, 192, 53,  84,  231, 149, 72,  140, 77,  236,
      196, 88,  65,  213, 144, 226, 86,  85,  26,  165, 134, 32,  184,
      180, 104, 175, 215, 249, 14,  183, 81,  185, 162, 111, 242, 44,
      206, 57,  207, 179, 57,  20,  8,   4,   80,  10,  68,  84,  70,
      63,  231, 247, 7,   160, 101, 63,  240, 152, 49,  231, 41,  163,
      67,  81,  20,  176, 87,  20,  251, 124, 126, 156, 223, 233, 56,
      78,  231, 76,  73,  222, 188, 203, 144, 199, 110, 33,  246, 122,
      189, 56,  185, 214, 17,  57,  125, 147, 24,  51,  206, 106, 234,
      181, 16,  242, 216, 151, 177, 219, 237, 65,  252, 74,  199, 118,
      226, 21,  191, 199, 119, 71,  34,  180, 217, 108, 69,  112, 67,
      46,  151, 91,  134, 102, 219, 138, 103, 17,  137, 107, 184, 184,
      203, 225, 94,  203, 75,  248, 63,  184, 33,  167, 115, 12,  241,
      75,  29,  27,  199, 47,  166, 132, 79,  50,  216, 79,  102, 113,
      112, 246, 69,  234, 86,  7,   55,  52,  58,  234, 68,  44,  157,
      71,  72,  125, 46,  9,   118, 185, 161, 225, 225, 17,  168, 226,
      176, 118, 168, 149, 4,   187, 162, 33,  82,  148, 33,  168, 23,
      121, 172, 68,  181, 2,   203, 209, 71,  204, 68,  162, 8,   238,
      196, 138, 238, 25,  225, 114, 67,  52,  56,  168, 224, 72,  132,
      139, 123, 15,  18,  79,  104, 30,  181, 227, 229, 168, 155, 172,
      144, 52,  207, 53,  98,  54,  172, 26,  239, 36,  92,  110, 136,
      28,  142, 1,   28,  158, 231, 177, 176, 251, 0,   219, 146, 87,
      200, 149, 133, 200, 160, 126, 178, 10,  19,  155, 17,  18,  14,
      9,   87,  54,  100, 183, 59,  100, 232, 90,  13,  154, 70,  223,
      80,  195, 84,  53,  205, 133, 19,  28,  130, 27,  178, 90,  237,
      88,  79,  164, 209, 56,  93,  243, 103, 100, 208, 18,  108, 66,
      52,  245, 14,  110, 168, 191, 223, 138, 182, 133, 214, 127, 35,
      227, 174, 119, 173, 7,   189, 214, 62,  80,  103, 103, 23,  218,
      219, 59,  204, 160, 31,  20,  189, 117, 91,  44,  248, 4,   42,
      101, 142, 59,  53,  32,  182, 139, 0,   0,   0,   0,   73,  69,
      78,  68,  174, 66,  96,  130};

  scoped_refptr<Image> image = BitmapImage::Create();
  image->SetData(
      SharedBuffer::Create(base::span<const unsigned char>(kBrokenImagePng)),
      true);
  return image;
}
void CustomScrollbarTheme::PaintIntoRect(const LayoutCustomScrollbarPart&,
                                         const PaintInfo&,
                                         const PhysicalRect&) {}
void CustomScrollbar::Paint(const PaintInfo&, const PhysicalOffset&) const {}
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
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
#endif
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
#if defined(HTML_CSS_RENDERER_STANDALONE)
unsigned MathMLTableCellElement::colSpan() const {
  return 1;
}
unsigned MathMLTableCellElement::rowSpan() const {
  return 1;
}
LayoutUnit MathTableBaseline(const ComputedStyle&, LayoutUnit block_offset) {
  return LayoutUnit(block_offset / 2);
}
#endif
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
std::unique_ptr<PathPositionMapper> LayoutSVGTextPath::LayoutPath() const {
  return nullptr;
}

PathPositionMapper::PositionType PathPositionMapper::PointAndNormalAtLength(
    float,
    PointAndTangent&) {
  return kBeforePath;
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
#if !HTML_CSS_RENDERER_STANDALONE_TEXT_INPUT
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
#endif
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
    const AttributeModificationParams& params) {
  HTMLElement::AttributeChanged(params);
}
void HTMLFormControlElement::ParseAttribute(
    const AttributeModificationParams& params) {
  HTMLElement::ParseAttribute(params);
}
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
void HTMLFormControlElement::DefaultEventHandler(Event& event) {
  HTMLElement::DefaultEventHandler(event);
}
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
  return SelectorChecker::MatchesFocusVisiblePseudoClass(*this);
}
bool HTMLFormControlElement::IsKeyboardFocusableSlow(
    UpdateBehavior update_behavior) const {
  return IsFocusable(update_behavior) && tabIndex() >= 0;
}
FocusableState HTMLFormControlElement::SupportsFocus(
    UpdateBehavior) const {
  return IsDisabledFormControl() ? FocusableState::kNotFocusable
                                 : FocusableState::kFocusable;
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
const Node* HTMLFormElement::GetListedElementsScope() const {
  return this;
}
void FormData::AppendFromElement(const String&, const String&) {}
String Locale::ConvertToLocalizedNumber(const String& value) {
  return value;
}
String Locale::ValidationMessageTooLongText(unsigned, int) {
  return String();
}
String Locale::ValidationMessageTooShortText(unsigned, int) {
  return String();
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
void HTMLFormElement::SubmitImplicitly(const Event&, bool) {}
void AutoscrollController::StartAutoscrollForSelection(LayoutObject*) {}
void AutoscrollController::StartMiddleClickAutoscroll(LocalFrame*,
                                                      LayoutBox*,
                                                      const gfx::PointF&,
                                                      const gfx::PointF&) {}
void AutoscrollController::HandleMouseMoveForMiddleClickAutoscroll(
    LocalFrame*,
    const gfx::PointF&,
    bool) {}
void AutoscrollController::HandleMouseReleaseForMiddleClickAutoscroll(
    LocalFrame*,
    bool) {}
void AutoscrollController::UpdateDragAndDrop(Node*,
                                             const gfx::PointF&,
                                             base::TimeTicks) {}
bool AutoscrollController::AutoscrollInProgressFor(const LayoutBox*) const {
  return false;
}
void AutoscrollController::StopAutoscroll() {}

bool FindBestTouchAdjustmentCandidate(TouchAdjustmentCandidateType,
                                      Node*&,
                                      gfx::Point&,
                                      const gfx::Point&,
                                      const gfx::Rect&,
                                      const HeapVector<Member<Node>>&) {
  return false;
}

PhysicalSize GetHitTestRectForAdjustment(LocalFrame&,
                                         const PhysicalSize& touch_area) {
  return touch_area;
}

void HitTestResult::Append(const HitTestResult& other) {
  if (!inner_node_ && other.InnerNode()) {
    inner_node_ = other.InnerNode();
    inner_element_ = other.InnerElement();
    inner_possibly_pseudo_node_ = other.InnerPossiblyPseudoNode();
    local_point_ = other.LocalPoint();
    point_in_inner_node_frame_ = other.PointInInnerNodeFrame();
    inner_url_element_ = other.URLElement();
    scrollbar_ = other.GetScrollbar();
    is_over_embedded_content_view_ = other.IsOverEmbeddedContentView();
    is_over_resizer_ = other.IsOverResizer();
    is_over_scroll_corner_ = other.IsOverScrollCorner();
  }
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
#if !defined(HTML_CSS_RENDERER_STANDALONE)
void PhysicalFragment::Trace(Visitor*) const {}
#endif
DarkModeImageClassifier::DarkModeImageClassifier() = default;
DarkModeResult DarkModeImageClassifier::Classify(const SkPixmap&,
                                                 const SkIRect&) const {
  return DarkModeResult::kDoNotApplyFilter;
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
gfx::Rect PaintLayerScrollableArea::RectForHorizontalScrollbar() const {
  if (!HasHorizontalScrollbar())
    return gfx::Rect();

  const gfx::Rect scroll_corner = ScrollCornerRect();
  const gfx::Size border_box_size = PixelSnappedBorderBoxSize();
  const PhysicalBoxStrut border = GetLayoutBox()->BorderOutsets();
  int left = border.left.ToInt();
  if (GetLayoutBox()->ShouldPlaceBlockDirectionScrollbarOnLogicalLeft()) {
    left += HasVerticalScrollbar() ? VerticalScrollbar()->ScrollbarThickness()
                                   : ResizerCornerRect(kResizerForPointer)
                                         .width();
  }

  return gfx::Rect(left,
                   border_box_size.height() - border.bottom.ToInt() -
                       HorizontalScrollbar()->ScrollbarThickness(),
                   border_box_size.width() - border.HorizontalSum().ToInt() -
                       scroll_corner.width(),
                   HorizontalScrollbar()->ScrollbarThickness());
}
gfx::Rect PaintLayerScrollableArea::RectForVerticalScrollbar() const {
  if (!HasVerticalScrollbar())
    return gfx::Rect();

  const gfx::Rect scroll_corner = ScrollCornerRect();
  const gfx::Size border_box_size = PixelSnappedBorderBoxSize();
  const PhysicalBoxStrut border = GetLayoutBox()->BorderOutsets();
  const int left =
      GetLayoutBox()->ShouldPlaceBlockDirectionScrollbarOnLogicalLeft()
          ? border.left.ToInt()
          : border_box_size.width() - border.right.ToInt() -
                VerticalScrollbar()->ScrollbarThickness();

  return gfx::Rect(left, border.top.ToInt(),
                   VerticalScrollbar()->ScrollbarThickness(),
                   border_box_size.height() - border.VerticalSum().ToInt() -
                       scroll_corner.height());
}
void PaintLayerScrollableArea::PositionOverflowControls() {
  if (Scrollbar* vertical_scrollbar = VerticalScrollbar())
    vertical_scrollbar->SetFrameRect(RectForVerticalScrollbar());
  if (Scrollbar* horizontal_scrollbar = HorizontalScrollbar())
    horizontal_scrollbar->SetFrameRect(RectForHorizontalScrollbar());
}
gfx::Rect PaintLayerScrollableArea::ScrollCornerAndResizerRect() const {
  return gfx::Rect();
}
bool PaintLayerScrollableArea::IsAbsolutePointInResizeControl(
    const gfx::Point&,
    ResizerHitTestType) const {
  return false;
}
gfx::Transform PaintLayerScrollableArea::InitializeResizeTransform(
    const gfx::Point&) {
  return gfx::Transform();
}
void PaintLayerScrollableArea::Resize(const gfx::Point&,
                                      const gfx::Transform&) {}
gfx::Size PaintLayerScrollableArea::PixelSnappedBorderBoxSize() const {
  const LayoutBox* box = GetLayoutBox();
  if (!box)
    return gfx::Size();
  return ToPixelSnappedRect(box->PhysicalBorderBoxRect()).size();
}
bool PaintLayerScrollableArea::HasHorizontalOverflow() const {
  const LayoutUnit client_width =
      LayoutContentRect(kIncludeScrollbars).Width() -
      VerticalScrollbarWidth(kIgnoreOverlayScrollbarSize);
  return ScrollWidth().Round() > client_width.Round();
}
bool PaintLayerScrollableArea::HasVerticalOverflow() const {
  const LayoutUnit client_height =
      LayoutContentRect(kIncludeScrollbars).Height() -
      HorizontalScrollbarHeight(kIgnoreOverlayScrollbarSize);
  return ScrollHeight().Round() > client_height.Round();
}
gfx::Size PaintLayerScrollableArea::PixelSnappedContentsSize(
    const PhysicalOffset&) const {
  return ToPixelSnappedRect(PhysicalRect(PhysicalOffset(), overflow_rect_.size))
      .size();
}
bool PaintLayerScrollableArea::BackgroundNeedsRepaintOnScroll() const {
  return false;
}
cc::ElementId PaintLayerScrollableArea::GetScrollCornerElementId() const {
  return cc::ElementId();
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
std::optional<gfx::RectF> CSSMaskPainter::MaskBoundingBox(
    const LayoutObject& object,
    const PhysicalOffset& paint_offset) {
  if (!object.IsBoxModelObject() || object.IsSVGChild())
    return std::nullopt;

  const ComputedStyle& style = object.StyleRef();
  if (!style.HasMask())
    return std::nullopt;

  PhysicalRect maximum_mask_region;
  EFillBox maximum_mask_clip = style.MaskLayers().LayersClipMax();
  if (object.IsBox()) {
    if (maximum_mask_clip == EFillBox::kNoClip) {
      maximum_mask_region =
          To<LayoutBox>(object)
              .Layer()
              ->LocalBoundingBoxIncludingSelfPaintingDescendants();
    } else {
      maximum_mask_region = To<LayoutBox>(object).PhysicalBorderBoxRect();
    }
  } else {
    if (maximum_mask_clip == EFillBox::kNoClip) {
      maximum_mask_region =
          To<LayoutInline>(object)
              .Layer()
              ->LocalBoundingBoxIncludingSelfPaintingDescendants();
    } else {
      maximum_mask_region = To<LayoutInline>(object).PhysicalLinesBoundingBox();
    }
  }
  if (style.HasMaskBoxImageOutsets())
    maximum_mask_region.Expand(style.MaskBoxImageOutsets());
  maximum_mask_region.offset += paint_offset;
  return gfx::RectF(maximum_mask_region);
}
bool LinkHighlight::IsHighlightingInternal(const LayoutObject&) const {
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
}  // namespace blink

void ShowAllPropertyTrees(const blink::LocalFrameView&) {}

namespace base {
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
}  // namespace base

namespace viz {
}  // namespace viz

namespace cc {
}  // namespace cc

namespace SkOpts {
void Init_ml3() {}
void Init_ml4() {}
}  // namespace SkOpts

namespace crashpad {
void Annotation::SetSize(ValueSizeType size) {
  size_ = size;
}
void Annotation::Clear() {
  size_ = 0;
}
}  // namespace crashpad

namespace cppgc::internal {
void DCheckImpl(const char*, SourceLocation) {}
}  // namespace cppgc::internal

namespace base {
}  // namespace base

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
template <bool AllowDangling>
bool RawPtrBackupRefImpl<AllowDangling>::CheckPointerWithinSameAlloc(uintptr_t,
                                                                     uintptr_t,
                                                                     size_t) {
  return false;
}
template bool RawPtrBackupRefImpl<false>::IsPointeeAlive(uintptr_t);
template bool RawPtrBackupRefImpl<true>::IsPointeeAlive(uintptr_t);
template void RawPtrBackupRefImpl<false>::AcquireInternal(uintptr_t);
template void RawPtrBackupRefImpl<true>::AcquireInternal(uintptr_t);
template void RawPtrBackupRefImpl<false>::ReleaseInternal(uintptr_t);
template void RawPtrBackupRefImpl<true>::ReleaseInternal(uintptr_t);
template void RawPtrBackupRefImpl<false>::ReportIfDanglingInternal(uintptr_t);
template void RawPtrBackupRefImpl<true>::ReportIfDanglingInternal(uintptr_t);
template bool RawPtrBackupRefImpl<false>::CheckPointerWithinSameAlloc(uintptr_t,
                                                                      uintptr_t,
                                                                      size_t);
template bool RawPtrBackupRefImpl<true>::CheckPointerWithinSameAlloc(uintptr_t,
                                                                     uintptr_t,
                                                                     size_t);
void CheckThatAddressIsntWithinFirstPartitionPage(uintptr_t) {}
}  // namespace base::internal

#if !defined(HTML_CSS_RENDERER_STANDALONE)
template <>
SkColor SkRGBA4f<kUnpremul_SkAlphaType>::toSkColor() const {
  return 0;
}
#endif

namespace skia {
}  // namespace skia

void SkFlattenable::PrivateInitializer::InitEffects() {
  // The standalone build owns a narrow Skia initialization boundary instead of
  // linking Skia's full ports/SkGlobalInitialization_default.cc. Register the
  // shader/path-effect flattenables required to deserialize Blink PaintFlags
  // resources (CSS gradients, local-matrix wrapped gradients, simple shader
  // composition, and dashed/dotted border strokes) without pulling
  // browser/network services into the cut.
  SK_REGISTER_FLATTENABLE(SkDashImpl);
  SkRegisterBlendShaderFlattenable();
  SkRegisterColorShaderFlattenable();
  SkRegisterEmptyShaderFlattenable();
  SK_REGISTER_FLATTENABLE(SkLocalMatrixShader);
  SK_REGISTER_FLATTENABLE(SkPictureShader);
  SkRegisterConicalGradientShaderFlattenable();
  SkRegisterLinearGradientShaderFlattenable();
  SkRegisterRadialGradientShaderFlattenable();
  SkRegisterSweepGradientShaderFlattenable();
  SkRegisterWorkingColorSpaceShaderFlattenable();
  SkShaderBase::RegisterFlattenables();
}
void SkFlattenable::PrivateInitializer::InitImageFilters() {}

sk_sp<SkColorFilter> SkHighContrastFilter::Make(const SkHighContrastConfig&) {
  return nullptr;
}

namespace cc {
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
