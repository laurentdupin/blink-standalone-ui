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
#include <string>
#include <thread>
#include <utility>
#include <unordered_map>
#include <vector>

#include "base/auto_reset.h"
#include "base/check.h"
#include "base/base_paths.h"
#include "base/command_line.h"
#include "base/containers/flat_map.h"
#include "base/files/file_util.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/sequence_checker.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "base/task/single_thread_task_runner.h"
#include "base/timer/timer.h"
#include "build/build_config.h"
#include "cc/layers/layer.h"
#include "cc/layers/solid_color_layer.h"
#include "cc/paint/paint_op.h"
#include "cc/paint/paint_op_buffer_iterator.h"
#include "cc/paint/paint_record.h"
#include "cc/animation/animation_host.h"
#include "cc/metrics/begin_main_frame_metrics.h"
#include "cc/raster/single_thread_task_graph_runner.h"
#include "cc/raster/synchronous_task_graph_runner.h"
#include "cc/trees/compositor_commit_data.h"
#include "cc/trees/layer_tree_frame_sink.h"
#include "cc/trees/layer_tree_frame_sink_client.h"
#include "cc/trees/layer_tree_host.h"
#include "cc/trees/layer_tree_host_delegate.h"
#include "cc/trees/layer_tree_host_single_thread_delegate.h"
#include "cc/trees/layer_tree_settings.h"
#include "components/viz/common/frame_sinks/begin_frame_source.h"
#include "components/viz/common/frame_sinks/copy_output_request.h"
#include "components/viz/common/frame_sinks/copy_output_result.h"
#include "components/viz/common/gpu/context_cache_controller.h"
#include "components/viz/common/gpu/context_lost_observer.h"
#include "components/viz/common/gpu/raster_context_provider.h"
#include "components/viz/common/gpu/vulkan_in_process_context_provider.h"
#include "components/viz/common/resources/shared_image_format_utils.h"
#include "components/viz/common/display/renderer_settings.h"
#include "components/viz/common/surfaces/frame_sink_id.h"
#include "components/viz/common/surfaces/parent_local_surface_id_allocator.h"
#include "components/viz/service/display/display.h"
#include "components/viz/service/display/display_client.h"
#include "components/viz/service/display/display_compositor_memory_and_task_controller.h"
#include "components/viz/service/display/display_scheduler_base.h"
#include "components/viz/service/display/output_surface.h"
#include "components/viz/service/display/overlay_processor_interface.h"
#include "components/viz/service/display/overlay_processor_stub.h"
#include "components/viz/service/display_embedder/skia_output_surface_dependency.h"
#include "components/viz/service/display_embedder/skia_output_surface_impl.h"
#include "components/viz/service/frame_sinks/compositor_frame_sink_support.h"
#include "components/viz/service/frame_sinks/frame_sink_manager_impl.h"
#include "components/viz/service/surfaces/pending_copy_output_request.h"
#include "gpu/command_buffer/client/context_support.h"
#include "gpu/command_buffer/client/client_shared_image.h"
#include "gpu/command_buffer/client/raster_interface.h"
#include "gpu/command_buffer/client/shared_image_interface.h"
#include "gpu/command_buffer/common/shared_image_usage.h"
#include "gpu/command_buffer/service/copy_shared_image_helper.h"
#include "gpu/command_buffer/service/memory_tracking.h"
#include "gpu/command_buffer/service/scheduler.h"
#include "gpu/command_buffer/service/scheduler_sequence.h"
#include "gpu/command_buffer/service/shared_image/shared_image_backing.h"
#include "gpu/command_buffer/service/shared_image/shared_image_factory.h"
#include "gpu/command_buffer/service/shared_image/shared_image_manager.h"
#include "gpu/command_buffer/service/shared_image/shared_image_representation.h"
#include "gpu/command_buffer/service/skia_utils.h"
#include "gpu/command_buffer/service/sync_point_manager.h"
#include "gpu/ipc/in_process_gpu_thread_holder.h"
#include "gpu/command_buffer/service/service_utils.h"
#include "gpu/command_buffer/service/shared_context_state.h"
#include "third_party/blink/public/web/web_navigation_params.h"
#include "third_party/blink/renderer/platform/testing/unit_test_helpers.h"
#include "gpu/ipc/common/surface_handle.h"
#include "gpu/ipc/raster_in_process_context.h"
#include "gpu/ipc/service/image_transport_surface.h"
#include "gpu/vulkan/init/vulkan_factory.h"
#include "gpu/vulkan/vulkan_device_queue.h"
#include "gpu/vulkan/vulkan_function_pointers.h"
#include "gpu/vulkan/vulkan_image.h"
#include "gpu/vulkan/vulkan_implementation.h"
#include "html_css_renderer/compositor_runtime.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "base/time/time.h"
#include "services/viz/public/mojom/compositing/compositor_frame_sink.mojom.h"
#include "third_party/blink/public/common/input/web_keyboard_event.h"
#include "third_party/blink/public/common/input/web_mouse_event.h"
#include "third_party/blink/public/common/input/web_mouse_wheel_event.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkPath.h"
#include "third_party/skia/include/core/SkPathBuilder.h"
#include "third_party/skia/include/core/SkPathEffect.h"
#include "third_party/skia/include/core/SkPixmap.h"
#include "third_party/skia/include/core/SkRRect.h"
#include "third_party/skia/include/core/SkSerialProcs.h"
#include "third_party/skia/include/core/SkShader.h"
#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/core/SkStream.h"
#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/skia/include/core/SkTextBlob.h"
#include "third_party/skia/include/core/SkTypeface.h"
#include "third_party/skia/include/encode/SkPngEncoder.h"
#include "third_party/skia/include/gpu/ganesh/GrBackendSurface.h"
#include "third_party/skia/include/gpu/ganesh/GrBackendSemaphore.h"
#include "third_party/skia/include/gpu/ganesh/GrDirectContext.h"
#include "third_party/skia/include/gpu/ganesh/SkSurfaceGanesh.h"
#include "third_party/skia/include/gpu/ganesh/vk/GrVkBackendSurface.h"
#include "third_party/skia/include/private/chromium/GrPromiseImageTexture.h"
#include "ui/gl/buildflags.h"
#include "ui/gl/gl_context.h"
#include "ui/gl/gl_implementation.h"
#include "ui/gl/gl_share_group.h"
#include "ui/gl/gl_surface.h"
#include "ui/gl/gl_utils.h"
#include "ui/gl/init/gl_factory.h"
#include "ui/gl/presenter.h"

#if BUILDFLAG(IS_WIN)
#include <d3d12.h>
#include <wrl/client.h>

#if defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
#include "gpu/command_buffer/service/dawn_context_provider.h"
#include "gpu/command_buffer/service/shared_image/skia_graphite_dawn_image_representation.h"
#include "gpu/command_buffer/service/shared_image/d3d_image_utils.h"
#endif
#endif
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/document_lifecycle.h"
#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/element_traversal.h"
#include "third_party/blink/renderer/core/dom/focus_params.h"
#include "third_party/blink/renderer/core/dom/node.h"
#include "third_party/blink/renderer/core/dom/shadow_root.h"
#include "third_party/blink/renderer/core/dom/text.h"
#include "third_party/blink/renderer/core/animation/animation.h"
#include "third_party/blink/renderer/core/animation/animation_clock.h"
#include "third_party/blink/renderer/core/animation/document_animations.h"
#include "third_party/blink/renderer/core/animation/document_timeline.h"
#include "third_party/blink/renderer/core/animation/element_animations.h"
#include "third_party/blink/renderer/core/animation/keyframe_effect.h"
#include "third_party/blink/renderer/core/animation/pending_animations.h"
#include "third_party/blink/renderer/core/core_initializer.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/root_frame_viewport.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/frame/visual_viewport.h"
#include "third_party/blink/renderer/core/css/post_style_update_scope.h"
#include "third_party/blink/renderer/core/css/css_property_value_set.h"
#include "third_party/blink/renderer/core/css/css_style_sheet.h"
#include "third_party/blink/renderer/core/css/properties/longhands.h"
#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/execution_context/agent.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html/html_base_element.h"
#include "third_party/blink/renderer/core/html/html_body_element.h"
#include "third_party/blink/renderer/core/html/html_element.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/html/html_html_element.h"
#include "third_party/blink/renderer/core/html/html_image_element.h"
#include "third_party/blink/renderer/core/html/html_style_element.h"
#include "third_party/blink/renderer/core/html/forms/html_button_element.h"
#include "third_party/blink/renderer/core/html/forms/html_input_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/forms/radio_button_group_scope.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/html_text_area_element.h"
#include "third_party/blink/renderer/core/html/forms/text_control_element.h"
#include "third_party/blink/renderer/core/events/text_event.h"
#include "third_party/blink/renderer/core/input/event_handler.h"
#include "third_party/blink/renderer/core/loader/resource/image_resource_content.h"
#include "third_party/blink/renderer/platform/heap/thread_state.h"
#include "third_party/blink/renderer/core/layout/hit_test_location.h"
#include "third_party/blink/renderer/core/layout/hit_test_result.h"
#include "third_party/blink/renderer/core/layout/hit_test_request.h"
#include "third_party/blink/renderer/core/layout/layout_box.h"
#include "third_party/blink/renderer/core/layout/layout_box_model_object.h"
#include "third_party/blink/renderer/core/layout/layout_image.h"
#include "third_party/blink/renderer/core/layout/layout_invalidation_reason.h"
#include "third_party/blink/renderer/core/layout/list/layout_list_item.h"
#include "third_party/blink/renderer/core/layout/block_node.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/layout/layout_object_inlines.h"
#include "third_party/blink/renderer/core/layout/table/layout_table.h"
#include "third_party/blink/renderer/core/layout/table/layout_table_column.h"
#include "third_party/blink/renderer/core/layout/table/table_layout_algorithm_types.h"
#include "third_party/blink/renderer/core/loader/empty_clients.h"
#include "third_party/blink/renderer/core/page/focus_controller.h"
#include "third_party/blink/renderer/core/page/page.h"
#include "third_party/blink/renderer/core/layout/layout_view.h"
#include "third_party/blink/renderer/core/layout/physical_box_fragment.h"
#include "third_party/blink/renderer/core/layout/physical_fragment.h"
#include "third_party/blink/renderer/core/layout/physical_fragment_link.h"
#include "third_party/blink/renderer/core/paint/object_paint_properties.h"
#include "third_party/blink/renderer/core/paint/paint_layer.h"
#include "third_party/blink/renderer/core/paint/paint_layer_paint_order_iterator.h"
#include "third_party/blink/renderer/core/paint/paint_layer_scrollable_area.h"
#include "third_party/blink/renderer/core/paint/paint_property_tree_builder.h"
#include "third_party/blink/renderer/core/scroll/scrollable_area.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/style_image.h"
#include "third_party/blink/renderer/platform/graphics/compositor_filter_operations.h"
#include "third_party/blink/renderer/platform/graphics/paint/drawing_display_item.h"
#include "third_party/blink/renderer/platform/graphics/paint/geometry_mapper.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_artifact.h"
#include "third_party/blink/renderer/platform/graphics/paint/paint_chunk.h"
#include "third_party/blink/renderer/platform/graphics/paint/scrollbar_display_item.h"
#include "third_party/blink/renderer/platform/geometry/length.h"
#include "third_party/blink/renderer/platform/graphics/dom_node_id.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/wtf.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/point_f.h"
#include "ui/gfx/geometry/rect_conversions.h"
#include "ui/gfx/geometry/skia_conversions.h"
#include "ui/events/keycodes/dom/dom_key.h"
#include "ui/gfx/ca_layer_params.h"

namespace gpu {
class DawnContextProvider;
}  // namespace gpu

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
extern "C" void StandaloneRendererResetFontResolutionDiagnostics();
extern "C" void StandaloneRendererResetImageReachabilityDiagnostics();
extern "C" int StandaloneRendererImageResourceContentFetchCalled();
extern "C" int StandaloneRendererLayoutImageSetResourceCalled();
extern "C" int StandaloneRendererLayoutImageResourceInitializeCalled();
extern "C" int StandaloneRendererLayoutImageResourceSetResourceCalled();
extern "C" int StandaloneRendererLayoutImageResourceNaturalDimensionsCalled();

namespace {
void* g_standalone_native_window_handle = nullptr;
gfx::Size g_standalone_native_window_size;
bool g_standalone_defer_image_attribute_loads = false;
raw_ptr<gpu::VulkanImplementation>
    g_pending_external_vulkan_implementation_for_testing = nullptr;
std::unique_ptr<gpu::VulkanDeviceQueue>
    g_pending_external_vulkan_device_queue_for_testing;
#if BUILDFLAG(IS_WIN)
std::optional<LUID> g_pending_external_d3d12_adapter_luid_for_testing;
Microsoft::WRL::ComPtr<ID3D12Device>
    g_pending_external_d3d12_device_for_testing;
Microsoft::WRL::ComPtr<ID3D12CommandQueue>
    g_pending_external_d3d12_command_queue_for_testing;
#endif
}  // namespace

void StandaloneBlinkLiveFrameBridgeInstallExternalVulkanForTesting(
    void* vulkan_implementation,
    void* vulkan_device_queue) {
#if BUILDFLAG(ENABLE_VULKAN)
  g_pending_external_vulkan_implementation_for_testing =
      static_cast<gpu::VulkanImplementation*>(vulkan_implementation);
  g_pending_external_vulkan_device_queue_for_testing.reset(
      static_cast<gpu::VulkanDeviceQueue*>(vulkan_device_queue));
#endif
}

void InstallPendingExternalVulkanForTesting(
    gpu::InProcessGpuThreadHolder* holder) {
#if BUILDFLAG(ENABLE_VULKAN)
  if (!holder || !g_pending_external_vulkan_implementation_for_testing ||
      !g_pending_external_vulkan_device_queue_for_testing) {
    return;
  }
  holder->AdoptExternalVulkanForTesting(
      g_pending_external_vulkan_implementation_for_testing,
      std::move(g_pending_external_vulkan_device_queue_for_testing));
  g_pending_external_vulkan_implementation_for_testing = nullptr;
#endif
}

void StandaloneBlinkLiveFrameBridgeInstallExternalD3D12AdapterLuidForTesting(
    uint32_t adapter_luid_low,
    int32_t adapter_luid_high,
    void* d3d12_device,
    void* d3d12_command_queue) {
#if BUILDFLAG(IS_WIN)
  LUID luid = {};
  luid.LowPart = adapter_luid_low;
  luid.HighPart = adapter_luid_high;
  g_pending_external_d3d12_adapter_luid_for_testing = luid;
  g_pending_external_d3d12_device_for_testing =
      static_cast<ID3D12Device*>(d3d12_device);
  g_pending_external_d3d12_command_queue_for_testing =
      static_cast<ID3D12CommandQueue*>(d3d12_command_queue);
#endif
}

void InstallPendingExternalD3D12AdapterLuidForTesting(
    gpu::InProcessGpuThreadHolder* holder) {
#if BUILDFLAG(IS_WIN)
  if (!holder || !g_pending_external_d3d12_adapter_luid_for_testing) {
    return;
  }
  holder->SetExternalD3D12AdapterLuidForTesting(
      *g_pending_external_d3d12_adapter_luid_for_testing,
      g_pending_external_d3d12_device_for_testing.Get(),
      g_pending_external_d3d12_command_queue_for_testing.Get());
  g_pending_external_d3d12_adapter_luid_for_testing.reset();
  g_pending_external_d3d12_device_for_testing.Reset();
  g_pending_external_d3d12_command_queue_for_testing.Reset();
#endif
}

extern "C" bool StandaloneRendererDeferImageAttributeLoads() {
  return g_standalone_defer_image_attribute_loads;
}
extern "C" void StandaloneRendererSetDeferImageAttributeLoads(bool enabled) {
  g_standalone_defer_image_attribute_loads = enabled;
}
extern "C" void*
StandaloneRendererNativeWindowHandleForStandaloneRenderer() {
  return g_standalone_native_window_handle;
}
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
void InstallStandaloneMojoThunksForStandaloneRenderer();

namespace {

extern "C" void HtmlCssRendererStandaloneSetCrashBreadcrumb(const char*);

void TraceLiveFrameProbeStage(const char* stage);
void TraceLiveFrameProbeStagef(const char* format,
                               wtf_size_t first,
                               wtf_size_t second);
std::string JsonStringForStandaloneRenderer(const std::string& value);

gfx::Size StandalonePhysicalViewportForDeviceScale(
    const gfx::Size& logical_viewport,
    float device_scale_factor) {
  const float clamped_scale =
      device_scale_factor > 0.0f ? device_scale_factor : 1.0f;
  return gfx::Size(
      std::max(1, static_cast<int>(
                      std::ceil(logical_viewport.width() * clamped_scale))),
      std::max(1, static_cast<int>(
                      std::ceil(logical_viewport.height() * clamped_scale))));
}

std::string DescribeGLInitializationFailure(const char* prefix) {
  std::ostringstream out;
  out << prefix;
  const base::CommandLine* command_line =
      base::CommandLine::ForCurrentProcess();
  const std::optional<gl::GLImplementationParts> requested =
      gl::GetRequestedGLImplementationFromCommandLine(command_line);
  out << " (requested_gl="
      << (requested.has_value() ? requested->ToString() : "none")
      << ", active_gl=" << gl::GetGLImplementationParts().ToString()
      << ", USE_STATIC_ANGLE=" << (BUILDFLAG(USE_STATIC_ANGLE) ? 1 : 0)
      << ", ENABLE_VULKAN=" << (BUILDFLAG(ENABLE_VULKAN) ? 1 : 0);
#if BUILDFLAG(IS_WIN)
  base::FilePath module_dir;
  if (base::PathService::Get(base::DIR_MODULE, &module_dir)) {
    const base::FilePath gles = module_dir.Append(L"libGLESv2.dll");
    const base::FilePath egl = module_dir.Append(L"libEGL.dll");
    out << ", libGLESv2.dll=" << (base::PathExists(gles) ? 1 : 0)
        << ", libEGL.dll=" << (base::PathExists(egl) ? 1 : 0)
        << ", module_dir=" << module_dir.AsUTF8Unsafe();
  } else {
    out << ", module_dir=<unavailable>";
  }
#endif
  out << ")";
  return out.str();
}

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
  bool loader_content_loaded = false;
  bool loader_content_loading = false;
  int loader_content_status = -1;
  bool image_element_complete = false;
  bool image_element_primary_content = false;
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

struct ImagePaintIntoRectDiagnostics {
  bool called = false;
  int count = 0;
  float dest_x = 0.0f;
  float dest_y = 0.0f;
  float dest_width = 0.0f;
  float dest_height = 0.0f;
  float content_x = 0.0f;
  float content_y = 0.0f;
  float content_width = 0.0f;
  float content_height = 0.0f;
  float snapped_dest_x = 0.0f;
  float snapped_dest_y = 0.0f;
  float snapped_dest_width = 0.0f;
  float snapped_dest_height = 0.0f;
  float src_x = 0.0f;
  float src_y = 0.0f;
  float src_width = 0.0f;
  float src_height = 0.0f;
  int image_width = 0;
  int image_height = 0;
  int interpolation_quality = -1;
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
  int source_chunk_index = -1;
  int source_display_item_index = -1;
  uint64_t source_display_item_client_id = 0;
  bool source_display_item_client_id_valid = false;
};

struct LiveFinerCacheUnitDescriptor {
  int unit_index = -1;
  int begin_display_item_index = -1;
  int end_display_item_index = -1;
  uint64_t display_item_client_id = 0;
  bool display_item_client_id_valid = false;
  float visual_x = 0.0f;
  float visual_y = 0.0f;
  float visual_width = 0.0f;
  float visual_height = 0.0f;
  uint64_t content_hash = 0;
  uint64_t resource_signal_hash = 0;
  int display_item_count = 0;
  int drawing_item_count = 0;
  int paint_op_count = 0;
  int recursive_paint_op_count = 0;
  int visual_op_count = 0;
  bool conservative_candidate = false;
  bool has_save_layer_ops = false;
  bool has_non_rect_clip_ops = false;
  bool has_non_translation_transform = false;
  bool has_effect_opacity = false;
  bool has_shader_ops = false;
  bool has_image_ops = false;
  bool has_path_ops = false;
  bool has_filter_ops = false;
  bool has_path_effect_ops = false;
  std::string stable_key;
};

struct LiveHitTestEntry {
  std::string element_id;
  std::string tag_name;
  std::string data_godot_action;
  DisplayItemClientId paint_client_id = kInvalidDisplayItemClientId;
  int paint_order = -1;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  bool disabled = false;
  bool editable = false;
  bool checked = false;
  bool focused = false;
};

struct LiveFormControlEntry {
  std::string element_id;
  std::string tag_name;
  std::string value;
  std::string type;
  std::string min;
  std::string max;
  std::string step;
  std::vector<std::string> selected_values;
  bool checked = false;
  bool focused = false;
  bool selection_offsets_present = false;
  unsigned selection_start = 0;
  unsigned selection_end = 0;
};

enum StandaloneBackdropFilterFlags : uint32_t {
  kStandaloneBackdropFilterRoundedRect = 1u << 0,
  kStandaloneBackdropFilterUnsupportedComplexClip = 1u << 1,
  kStandaloneBackdropFilterUnsupportedTransform = 1u << 2,
  kStandaloneBackdropFilterUnsupportedFilterOp = 1u << 3,
  kStandaloneBackdropFilterUnsupportedMaskOrBlend = 1u << 4,
};

enum StandaloneBackdropFilterOperationType : uint32_t {
  kStandaloneBackdropFilterOperationBlur = 0,
  kStandaloneBackdropFilterOperationBrightness = 1,
  kStandaloneBackdropFilterOperationContrast = 2,
  kStandaloneBackdropFilterOperationSaturate = 3,
  kStandaloneBackdropFilterOperationGrayscale = 4,
  kStandaloneBackdropFilterOperationSepia = 5,
  kStandaloneBackdropFilterOperationInvert = 6,
  kStandaloneBackdropFilterOperationHueRotate = 7,
  kStandaloneBackdropFilterOperationOpacity = 8,
};

struct LiveBackdropFilterRegion {
  std::string element_id;
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float blur_radius_css_px = 0.0f;
  float border_radius_top_left = 0.0f;
  float border_radius_top_right = 0.0f;
  float border_radius_bottom_right = 0.0f;
  float border_radius_bottom_left = 0.0f;
  float opacity = 1.0f;
  uint32_t flags = 0;
  std::vector<LiveExportedFilterOperation> filter_operations;
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

struct LiveRawFrameOutput {
  int width = 0;
  int height = 0;
  int stride = 0;
  int pixel_format = 0;
  bool premultiplied_alpha = true;
  std::vector<uint8_t> pixels;
};

struct LiveGpuFrameOutput {
  bool shared_image_available = false;
  bool is_software = false;
  bool vk_context_provider_available = false;
  bool shared_context_state_is_vulkan = false;
  int width = 0;
  int height = 0;
  std::string format;
  std::string mailbox;
  std::string creation_sync_token;
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

class StandaloneVizFrameSinkClient final
    : public viz::mojom::CompositorFrameSinkClient {
 public:
  StandaloneVizFrameSinkClient() = default;
  StandaloneVizFrameSinkClient(const StandaloneVizFrameSinkClient&) = delete;
  StandaloneVizFrameSinkClient& operator=(const StandaloneVizFrameSinkClient&) =
      delete;
  ~StandaloneVizFrameSinkClient() override = default;

  void SetCcClient(cc::LayerTreeFrameSinkClient* client) {
    cc_client_ = client;
  }

  void SetAsyncCompositorFrameAck(bool enabled) {
    async_compositor_frame_ack_ = enabled;
  }

  void SetDeferCompositorFrameAck(bool enabled) {
    defer_compositor_frame_ack_ = enabled;
  }

  void FlushDeferredCompositorFrameAck() {
    if (!deferred_compositor_frame_ack_pending_) {
      return;
    }
    deferred_compositor_frame_ack_pending_ = false;
    std::vector<viz::ReturnedResource> resources =
        std::move(deferred_compositor_frame_ack_resources_);
    deferred_compositor_frame_ack_resources_.clear();
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
        FROM_HERE,
        base::BindOnce(&StandaloneVizFrameSinkClient::ForwardCompositorFrameAck,
                       weak_factory_.GetWeakPtr(), std::move(resources)));
  }

  void DidReceiveCompositorFrameAck(
      std::vector<viz::ReturnedResource> resources) override {
    if (async_compositor_frame_ack_) {
      base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
          FROM_HERE,
          base::BindOnce(
              &StandaloneVizFrameSinkClient::ForwardCompositorFrameAck,
              weak_factory_.GetWeakPtr(), std::move(resources)));
      return;
    }
    ForwardCompositorFrameAck(std::move(resources));
  }

  void ForwardCompositorFrameAck(
      std::vector<viz::ReturnedResource> resources) {
    if (defer_compositor_frame_ack_) {
      for (auto& resource : resources) {
        deferred_compositor_frame_ack_resources_.push_back(std::move(resource));
      }
      deferred_compositor_frame_ack_pending_ = true;
      return;
    }
    if (!cc_client_) {
      return;
    }
    cc_client_->ReclaimResources(std::move(resources));
    cc_client_->DidReceiveCompositorFrameAck();
  }

  void OnBeginFrame(
      const viz::BeginFrameArgs& args,
      const base::flat_map<uint32_t, viz::FrameTimingDetails>& details,
      std::vector<viz::ReturnedResource> resources) override {
    if (cc_client_ && !resources.empty()) {
      cc_client_->ReclaimResources(std::move(resources));
    }
  }

  void OnBeginFramePausedChanged(bool paused) override {}

  void ReclaimResources(
      std::vector<viz::ReturnedResource> resources) override {
    if (cc_client_ && !resources.empty()) {
      cc_client_->ReclaimResources(std::move(resources));
    }
  }

  void OnCompositorFrameTransitionDirectiveProcessed(
      uint32_t sequence_id) override {
    if (cc_client_) {
      cc_client_->OnCompositorFrameTransitionDirectiveProcessed(sequence_id);
    }
  }

  void OnSurfaceEvicted(
      const viz::LocalSurfaceId& local_surface_id) override {
    if (cc_client_) {
      cc_client_->OnSurfaceEvicted(local_surface_id);
    }
  }

 private:
  raw_ptr<cc::LayerTreeFrameSinkClient> cc_client_ = nullptr;
  bool async_compositor_frame_ack_ = false;
  bool defer_compositor_frame_ack_ = false;
  bool deferred_compositor_frame_ack_pending_ = false;
  std::vector<viz::ReturnedResource> deferred_compositor_frame_ack_resources_;
  base::WeakPtrFactory<StandaloneVizFrameSinkClient> weak_factory_{this};
};

class StandaloneDisplayClient final : public viz::DisplayClient {
 public:
  StandaloneDisplayClient(bool* skia_gpu_reached, std::string* failure_reason)
      : skia_gpu_reached_(skia_gpu_reached),
        failure_reason_(failure_reason) {}

  StandaloneDisplayClient(const StandaloneDisplayClient&) = delete;
  StandaloneDisplayClient& operator=(const StandaloneDisplayClient&) = delete;
  ~StandaloneDisplayClient() override = default;

  void DisplayOutputSurfaceLost() override {
    if (failure_reason_) {
      *failure_reason_ = "Viz Display output surface was lost";
    }
  }

  void DisplayWillDrawAndSwap(
      bool will_draw_and_swap,
      viz::AggregatedRenderPassList* render_passes) override {
    if (will_draw_and_swap && skia_gpu_reached_) {
      *skia_gpu_reached_ = true;
    }
  }

  void DisplayDidDrawAndSwap() override {
    if (skia_gpu_reached_) {
      *skia_gpu_reached_ = true;
    }
  }

  void DisplayDidReceiveCALayerParams(gfx::CALayerParams ca_layer_params)
      override {}

  void DisplayDidCompleteSwapWithSize(const gfx::Size& pixel_size) override {}

  void DisplayAddChildWindowToBrowser(gpu::SurfaceHandle child_window) override {
  }

  void SetWideColorEnabled(bool enabled) override {}

 private:
  raw_ptr<bool> skia_gpu_reached_ = nullptr;
  raw_ptr<std::string> failure_reason_ = nullptr;
};

const char* StandaloneCopyOutputErrorName(viz::CopyOutputResult::Error error) {
  switch (error) {
    case viz::CopyOutputResult::Error::kNone:
      return "none";
    case viz::CopyOutputResult::Error::kUnknown:
      return "unknown";
    case viz::CopyOutputResult::Error::kTimeout:
      return "timeout";
    case viz::CopyOutputResult::Error::kEmbeddingTokenChanged:
      return "embedding_token_changed";
  }
  return "unknown";
}

struct StandaloneBorrowedVkImageBackingSmokeResult {
  bool context_available = false;
  bool target_created = false;
  bool backend_texture_valid = false;
  bool registered = false;
  bool produced_skia = false;
  bool write_access = false;
  bool readback_verified = false;
  bool backing_released = false;
  bool target_destroyed = false;
  int width = 64;
  int height = 32;
  std::string format = "RGBA_8888";
  std::string failure;
};

std::string StandaloneBorrowedVkImageBackingSmokeLine(
    const StandaloneBorrowedVkImageBackingSmokeResult& result) {
  std::ostringstream out;
  out << "gpu_borrowed_vkimage_backing_smoke: ";
  if (result.failure.empty()) {
    out << "ok";
  } else {
    out << "failed failure=" << result.failure;
  }
  out << " path=skia_direct_write"
      << " viz_blit_request=0"
      << " target=" << result.width << "x" << result.height
      << " format=" << result.format
      << " context=" << (result.context_available ? 1 : 0)
      << " target_created=" << (result.target_created ? 1 : 0)
      << " backend_texture=" << (result.backend_texture_valid ? 1 : 0)
      << " registered=" << (result.registered ? 1 : 0)
      << " produced_skia=" << (result.produced_skia ? 1 : 0)
      << " write_access=" << (result.write_access ? 1 : 0)
      << " readback=" << (result.readback_verified ? 1 : 0)
      << " backing_released=" << (result.backing_released ? 1 : 0)
      << " target_destroyed=" << (result.target_destroyed ? 1 : 0)
      << " ownership=borrowed";
  return out.str();
}

struct StandaloneBorrowedVkImageRenderCopySmokeResult {
  bool source_available = false;
  bool context_available = false;
  bool target_created = false;
  bool backend_texture_valid = false;
  bool registered = false;
  bool service_copy = false;
  bool viz_blit_request = false;
  bool readback_verified = false;
  bool backing_released = false;
  bool target_destroyed = false;
  bool blocked = false;
  int width = 0;
  int height = 0;
  std::string path = "service_copy";
  std::string format = "RGBA_8888";
  std::string source_mailbox;
  std::string source_background;
  std::string source_box;
  std::string observed_background;
  std::string observed_box;
  size_t nontransparent_pixels = 0;
  std::string failure;
};

struct StandaloneVulkanGpuOutputPixelSmokeResult {
  bool source_available = false;
  bool context_available = false;
  bool readback_verified = false;
  bool blocked = false;
  int width = 0;
  int height = 0;
  std::string format = "RGBA_8888";
  std::string source_mailbox;
  std::string observed_background;
  std::string observed_box;
  size_t nontransparent_pixels = 0;
  std::string failure;
};

struct StandaloneBorrowedD3D12RenderCopySmokeResult {
  bool source_available = false;
  bool context_available = false;
  bool target_created = false;
  bool shared_texture_memory = false;
  bool registered = false;
  bool viz_blit_request = false;
  bool readback_verified = false;
  bool backing_released = false;
  bool target_destroyed = false;
  bool blocked = false;
  int width = 0;
  int height = 0;
  std::string path = "viz_blit_request";
  std::string format = "RGBA_8888";
  std::string source_mailbox;
  std::string observed_background;
  std::string observed_box;
  size_t nontransparent_pixels = 0;
  std::string failure;
};

std::string StandaloneBorrowedVkImageRenderCopySmokeLine(
    const StandaloneBorrowedVkImageRenderCopySmokeResult& result) {
  std::ostringstream out;
  out << "gpu_borrowed_vkimage_render_copy_smoke: ";
  if (result.failure.empty()) {
    out << "ok";
  } else if (result.blocked) {
    out << "blocked reason=" << result.failure;
  } else {
    out << "failed failure=" << result.failure;
  }
  out << " path=" << result.path
      << " viz_blit_request=" << (result.viz_blit_request ? 1 : 0)
      << " target=" << result.width << "x" << result.height
      << " format=" << result.format
      << " source=" << (result.source_available ? 1 : 0)
      << " source_mailbox=" << result.source_mailbox
      << " source_background=" << result.source_background
      << " source_box=" << result.source_box
      << " observed_background=" << result.observed_background
      << " observed_box=" << result.observed_box
      << " nontransparent_pixels=" << result.nontransparent_pixels
      << " context=" << (result.context_available ? 1 : 0)
      << " target_created=" << (result.target_created ? 1 : 0)
      << " backend_texture=" << (result.backend_texture_valid ? 1 : 0)
      << " registered=" << (result.registered ? 1 : 0)
      << " service_copy=" << (result.service_copy ? 1 : 0)
      << " readback=" << (result.readback_verified ? 1 : 0)
      << " backing_released=" << (result.backing_released ? 1 : 0)
      << " target_destroyed=" << (result.target_destroyed ? 1 : 0)
      << " ownership=borrowed";
  return out.str();
}

std::string StandaloneVulkanGpuOutputPixelSmokeLine(
    const StandaloneVulkanGpuOutputPixelSmokeResult& result) {
  std::ostringstream out;
  out << "gpu_output_vulkan_pixel_smoke: ";
  if (result.failure.empty()) {
    out << "ok";
  } else if (result.blocked) {
    out << "blocked reason=" << result.failure;
  } else {
    out << "failed failure=" << result.failure;
  }
  out << " source=" << (result.source_available ? 1 : 0)
      << " source_mailbox=" << result.source_mailbox
      << " size=" << result.width << "x" << result.height
      << " format=" << result.format
      << " observed_background=" << result.observed_background
      << " observed_box=" << result.observed_box
      << " nontransparent_pixels=" << result.nontransparent_pixels
      << " context=" << (result.context_available ? 1 : 0)
      << " readback=" << (result.readback_verified ? 1 : 0);
  return out.str();
}

std::string StandaloneBorrowedD3D12RenderCopySmokeLine(
    const StandaloneBorrowedD3D12RenderCopySmokeResult& result) {
  std::ostringstream out;
  out << "gpu_borrowed_d3d12_render_copy_smoke: ";
  if (result.failure.empty()) {
    out << "ok";
  } else if (result.blocked) {
    out << "blocked reason=" << result.failure;
  } else {
    out << "failed failure=" << result.failure;
  }
  out << " path=" << result.path
      << " viz_blit_request=" << (result.viz_blit_request ? 1 : 0)
      << " target=" << result.width << "x" << result.height
      << " format=" << result.format
      << " source=" << (result.source_available ? 1 : 0)
      << " source_mailbox=" << result.source_mailbox
      << " observed_background=" << result.observed_background
      << " observed_box=" << result.observed_box
      << " nontransparent_pixels=" << result.nontransparent_pixels
      << " context=" << (result.context_available ? 1 : 0)
      << " target_created=" << (result.target_created ? 1 : 0)
      << " shared_texture_memory=" << (result.shared_texture_memory ? 1 : 0)
      << " registered=" << (result.registered ? 1 : 0)
      << " readback=" << (result.readback_verified ? 1 : 0)
      << " backing_released=" << (result.backing_released ? 1 : 0)
      << " target_destroyed=" << (result.target_destroyed ? 1 : 0)
      << " ownership=borrowed";
  return out.str();
}

std::string StandaloneFormatColor(SkColor color) {
  std::ostringstream out;
  out << std::hex << std::setfill('0')
      << std::setw(2) << static_cast<int>(SkColorGetA(color))
      << std::setw(2) << static_cast<int>(SkColorGetR(color))
      << std::setw(2) << static_cast<int>(SkColorGetG(color))
      << std::setw(2) << static_cast<int>(SkColorGetB(color));
  return out.str();
}

bool StandaloneColorClose(SkColor observed, SkColor expected) {
  auto close_channel = [](uint8_t observed_channel, uint8_t expected_channel) {
    return std::abs(static_cast<int>(observed_channel) -
                    static_cast<int>(expected_channel)) <= 6;
  };
  return close_channel(SkColorGetA(observed), SkColorGetA(expected)) &&
         close_channel(SkColorGetR(observed), SkColorGetR(expected)) &&
         close_channel(SkColorGetG(observed), SkColorGetG(expected)) &&
         close_channel(SkColorGetB(observed), SkColorGetB(expected));
}

class StandaloneBorrowedVkImageBacking final
    : public gpu::ClearTrackingSharedImageBacking {
 public:
  StandaloneBorrowedVkImageBacking(
      const gpu::Mailbox& mailbox,
      const gpu::SharedImageInfo& si_info,
      scoped_refptr<gpu::SharedContextState> context_state,
      const GrBackendTexture& backend_texture)
      : gpu::ClearTrackingSharedImageBacking(
            mailbox,
            si_info,
            /*estimated_size=*/
            static_cast<size_t>(std::max(0, si_info.size.width())) *
                static_cast<size_t>(std::max(0, si_info.size.height())) * 4u,
            /*is_thread_safe=*/false),
        context_state_(std::move(context_state)),
        backend_texture_(backend_texture),
        promise_texture_(GrPromiseImageTexture::Make(backend_texture_)) {}

  StandaloneBorrowedVkImageBacking(
      const StandaloneBorrowedVkImageBacking&) = delete;
  StandaloneBorrowedVkImageBacking& operator=(
      const StandaloneBorrowedVkImageBacking&) = delete;

  ~StandaloneBorrowedVkImageBacking() override {
    DCHECK(!is_write_);
    DCHECK_EQ(read_count_, 0);
    // The VkImage is embedder-owned in the product design. This proof backing
    // intentionally drops only its Skia wrappers and never destroys the image.
    promise_texture_.reset();
  }

  gpu::SharedImageBackingType GetType() const override {
    return gpu::SharedImageBackingType::kStandaloneBorrowedVkImage;
  }

  void Update(std::unique_ptr<gfx::GpuFence> in_fence) override {}

 protected:
  std::unique_ptr<gpu::SkiaGaneshImageRepresentation> ProduceSkiaGanesh(
      gpu::SharedImageManager* manager,
      gpu::MemoryTypeTracker* tracker,
      scoped_refptr<gpu::SharedContextState> context_state) override;

 private:
  class SkiaRepresentation final : public gpu::SkiaGaneshImageRepresentation {
   public:
    SkiaRepresentation(GrDirectContext* gr_context,
                       gpu::SharedImageManager* manager,
                       StandaloneBorrowedVkImageBacking* backing,
                       gpu::MemoryTypeTracker* tracker)
        : gpu::SkiaGaneshImageRepresentation(gr_context,
                                             manager,
                                             backing,
                                             tracker) {}

    bool SupportsMultipleConcurrentReadAccess() override { return true; }

    std::vector<sk_sp<SkSurface>> BeginWriteAccess(
        int final_msaa_count,
        const SkSurfaceProps& surface_props,
        const gfx::Rect& update_rect,
        std::vector<GrBackendSemaphore>* begin_semaphores,
        std::vector<GrBackendSemaphore>* end_semaphores,
        std::unique_ptr<skgpu::MutableTextureState>* end_state) override {
      return borrowed_backing()->BeginSkiaWriteAccess(final_msaa_count,
                                                      surface_props);
    }

    std::vector<sk_sp<GrPromiseImageTexture>> BeginWriteAccess(
        std::vector<GrBackendSemaphore>* begin_semaphores,
        std::vector<GrBackendSemaphore>* end_semaphores,
        std::unique_ptr<skgpu::MutableTextureState>* end_state) override {
      return borrowed_backing()->BeginSkiaWriteAccessAsPromiseTexture();
    }

    void EndWriteAccess() override { borrowed_backing()->EndSkiaWriteAccess(); }

    std::vector<sk_sp<GrPromiseImageTexture>> BeginReadAccess(
        std::vector<GrBackendSemaphore>* begin_semaphores,
        std::vector<GrBackendSemaphore>* end_semaphores,
        std::unique_ptr<skgpu::MutableTextureState>* end_state) override {
      return borrowed_backing()->BeginSkiaReadAccess();
    }

    void EndReadAccess() override { borrowed_backing()->EndSkiaReadAccess(); }

   private:
    StandaloneBorrowedVkImageBacking* borrowed_backing() {
      return static_cast<StandaloneBorrowedVkImageBacking*>(backing());
    }
  };

  std::vector<sk_sp<SkSurface>> BeginSkiaWriteAccess(
      int final_msaa_count,
      const SkSurfaceProps& surface_props) {
    if (is_write_ || read_count_ > 0 || !context_state_ ||
        !context_state_->gr_context() || !backend_texture_.isValid()) {
      return {};
    }
    is_write_ = true;
    const SkColorType sk_color_type = viz::ToClosestSkColorType(format());
    sk_sp<SkSurface> surface = SkSurfaces::WrapBackendTexture(
        context_state_->gr_context(), backend_texture_, surface_origin(),
        final_msaa_count, sk_color_type, color_space().ToSkColorSpace(),
        &surface_props);
    if (!surface) {
      is_write_ = false;
      return {};
    }
    return {std::move(surface)};
  }

  std::vector<sk_sp<GrPromiseImageTexture>>
  BeginSkiaWriteAccessAsPromiseTexture() {
    if (is_write_ || read_count_ > 0 || !promise_texture_) {
      return {};
    }
    is_write_ = true;
    return {promise_texture_};
  }

  void EndSkiaWriteAccess() {
    DCHECK(is_write_);
    is_write_ = false;
    SetCleared();
  }

  std::vector<sk_sp<GrPromiseImageTexture>> BeginSkiaReadAccess() {
    if (is_write_ || !promise_texture_) {
      return {};
    }
    ++read_count_;
    return {promise_texture_};
  }

  void EndSkiaReadAccess() {
    DCHECK_GT(read_count_, 0);
    --read_count_;
  }

  scoped_refptr<gpu::SharedContextState> context_state_;
  GrBackendTexture backend_texture_;
  sk_sp<GrPromiseImageTexture> promise_texture_;
  bool is_write_ = false;
  int read_count_ = 0;
};

std::unique_ptr<gpu::SkiaGaneshImageRepresentation>
StandaloneBorrowedVkImageBacking::ProduceSkiaGanesh(
    gpu::SharedImageManager* manager,
    gpu::MemoryTypeTracker* tracker,
    scoped_refptr<gpu::SharedContextState> context_state) {
  if (context_state != context_state_) {
    return nullptr;
  }
  return std::make_unique<SkiaRepresentation>(
      context_state_->gr_context(), manager, this, tracker);
}

#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
std::string HResultHex(HRESULT hr) {
  std::ostringstream out;
  out << "0x" << std::hex << std::setw(8) << std::setfill('0')
      << static_cast<unsigned long>(hr);
  return out.str();
}

bool SameD3D12Device(ID3D12Device* a, ID3D12Device* b) {
  if (!a || !b) {
    return false;
  }
  Microsoft::WRL::ComPtr<IUnknown> a_identity;
  Microsoft::WRL::ComPtr<IUnknown> b_identity;
  if (FAILED(a->QueryInterface(IID_PPV_ARGS(&a_identity))) ||
      FAILED(b->QueryInterface(IID_PPV_ARGS(&b_identity)))) {
    return false;
  }
  return a_identity.Get() == b_identity.Get();
}

Microsoft::WRL::ComPtr<IUnknown> D3D12ResourceIdentity(
    ID3D12Resource* resource) {
  Microsoft::WRL::ComPtr<IUnknown> identity;
  if (!resource ||
      FAILED(resource->QueryInterface(IID_PPV_ARGS(&identity)))) {
    return identity;
  }
  return identity;
}

std::string PointerHex(const void* ptr) {
  std::ostringstream out;
  out << "0x" << std::hex << reinterpret_cast<uintptr_t>(ptr);
  return out.str();
}

std::string LuidString(const LUID& luid) {
  std::ostringstream out;
  out << "0x" << std::hex << static_cast<uint32_t>(luid.HighPart) << ":"
      << luid.LowPart;
  return out.str();
}

std::string D3D12DeviceLuidString(ID3D12Device* device) {
  if (!device) {
    return "none";
  }
  return LuidString(device->GetAdapterLuid());
}

class StandaloneBorrowedD3D12TextureBacking final
    : public gpu::ClearTrackingSharedImageBacking {
 public:
  StandaloneBorrowedD3D12TextureBacking(
      const gpu::Mailbox& mailbox,
      const gpu::SharedImageInfo& si_info,
      scoped_refptr<gpu::SharedContextState> context_state,
      Microsoft::WRL::ComPtr<ID3D12Resource> resource)
      : gpu::ClearTrackingSharedImageBacking(
            mailbox,
            si_info,
            /*estimated_size=*/
            static_cast<size_t>(std::max(0, si_info.size.width())) *
                static_cast<size_t>(std::max(0, si_info.size.height())) * 4u,
            /*is_thread_safe=*/false),
        context_state_(std::move(context_state)),
        resource_(std::move(resource)) {}

  StandaloneBorrowedD3D12TextureBacking(
      const StandaloneBorrowedD3D12TextureBacking&) = delete;
  StandaloneBorrowedD3D12TextureBacking& operator=(
      const StandaloneBorrowedD3D12TextureBacking&) = delete;

  ~StandaloneBorrowedD3D12TextureBacking() override {
    DCHECK(!access_open_);
    texture_ = nullptr;
    shared_texture_memory_ = nullptr;
  }

  gpu::SharedImageBackingType GetType() const override {
    return gpu::SharedImageBackingType::kStandaloneBorrowedD3D12Texture;
  }

  void Update(std::unique_ptr<gfx::GpuFence> in_fence) override {}

  bool shared_texture_memory_created() const {
    return shared_texture_memory_ != nullptr;
  }

  bool ReadbackToPixels(std::vector<uint32_t>* pixels) {
    if (!pixels || !context_state_ || !context_state_->dawn_context_provider() ||
        !resource_) {
      return false;
    }
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue =
        context_state_->dawn_context_provider()->GetD3D12CommandQueue();
    if (!queue) {
      return false;
    }
    Microsoft::WRL::ComPtr<ID3D12Device> device;
    if (FAILED(queue->GetDevice(IID_PPV_ARGS(&device))) || !device) {
      return false;
    }
    D3D12_RESOURCE_DESC texture_desc = resource_->GetDesc();
    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
    UINT row_count = 0;
    UINT64 row_size_bytes = 0;
    UINT64 total_bytes = 0;
    device->GetCopyableFootprints(&texture_desc, 0, 1, 0, &footprint,
                                  &row_count, &row_size_bytes, &total_bytes);
    if (row_count == 0 || row_size_bytes == 0 || total_bytes == 0) {
      return false;
    }
    D3D12_HEAP_PROPERTIES readback_heap = {};
    readback_heap.Type = D3D12_HEAP_TYPE_READBACK;
    readback_heap.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    readback_heap.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    readback_heap.CreationNodeMask = 1;
    readback_heap.VisibleNodeMask = 1;
    D3D12_RESOURCE_DESC buffer_desc = {};
    buffer_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    buffer_desc.Alignment = 0;
    buffer_desc.Width = total_bytes;
    buffer_desc.Height = 1;
    buffer_desc.DepthOrArraySize = 1;
    buffer_desc.MipLevels = 1;
    buffer_desc.Format = DXGI_FORMAT_UNKNOWN;
    buffer_desc.SampleDesc.Count = 1;
    buffer_desc.SampleDesc.Quality = 0;
    buffer_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    buffer_desc.Flags = D3D12_RESOURCE_FLAG_NONE;
    Microsoft::WRL::ComPtr<ID3D12Resource> readback;
    if (FAILED(device->CreateCommittedResource(
            &readback_heap, D3D12_HEAP_FLAG_NONE, &buffer_desc,
            D3D12_RESOURCE_STATE_COPY_DEST, nullptr,
            IID_PPV_ARGS(&readback))) ||
        !readback) {
      return false;
    }
    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
    if (FAILED(device->CreateCommandAllocator(
            D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&allocator))) ||
        !allocator) {
      return false;
    }
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
    if (FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                         allocator.Get(), nullptr,
                                         IID_PPV_ARGS(&command_list))) ||
        !command_list) {
      return false;
    }

    D3D12_TEXTURE_COPY_LOCATION src = {};
    src.pResource = resource_.Get();
    src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src.SubresourceIndex = 0;
    D3D12_TEXTURE_COPY_LOCATION dst = {};
    dst.pResource = readback.Get();
    dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    dst.PlacedFootprint = footprint;
    command_list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
    if (FAILED(command_list->Close())) {
      return false;
    }
    ID3D12CommandList* command_lists[] = {command_list.Get()};
    queue->ExecuteCommandLists(1, command_lists);

    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    if (FAILED(device->CreateFence(0, D3D12_FENCE_FLAG_NONE,
                                   IID_PPV_ARGS(&fence))) ||
        !fence) {
      return false;
    }
    HANDLE event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!event_handle) {
      return false;
    }
    constexpr UINT64 kFenceValue = 1;
    if (FAILED(queue->Signal(fence.Get(), kFenceValue))) {
      ::CloseHandle(event_handle);
      return false;
    }
    if (fence->GetCompletedValue() < kFenceValue) {
      if (FAILED(fence->SetEventOnCompletion(kFenceValue, event_handle))) {
        ::CloseHandle(event_handle);
        return false;
      }
      ::WaitForSingleObject(event_handle, 5000);
    }
    ::CloseHandle(event_handle);
    if (fence->GetCompletedValue() < kFenceValue) {
      return false;
    }

    void* mapped = nullptr;
    D3D12_RANGE read_range = {0, static_cast<SIZE_T>(total_bytes)};
    if (FAILED(readback->Map(0, &read_range, &mapped)) || !mapped) {
      return false;
    }
    const uint8_t* mapped_bytes = static_cast<const uint8_t*>(mapped);
    const uint32_t width = static_cast<uint32_t>(size().width());
    const uint32_t height = static_cast<uint32_t>(size().height());
    constexpr uint32_t kBytesPerPixel = 4;
    pixels->assign(static_cast<size_t>(width) * static_cast<size_t>(height), 0);
    for (uint32_t y = 0; y < height; ++y) {
      const uint8_t* row =
          mapped_bytes + footprint.Offset +
          static_cast<size_t>(y) * footprint.Footprint.RowPitch;
      for (uint32_t x = 0; x < width; ++x) {
        const uint8_t* p = row + static_cast<size_t>(x) * kBytesPerPixel;
        (*pixels)[static_cast<size_t>(y) * width + x] =
            SkColorSetARGB(p[3], p[0], p[1], p[2]);
      }
    }
    D3D12_RANGE written_range = {0, 0};
    readback->Unmap(0, &written_range);
    return true;
  }

 protected:
  std::unique_ptr<gpu::DawnImageRepresentation> ProduceDawn(
      gpu::SharedImageManager* manager,
      gpu::MemoryTypeTracker* tracker,
      const wgpu::Device& device,
      wgpu::BackendType backend_type,
      std::vector<wgpu::TextureFormat> view_formats,
      scoped_refptr<gpu::SharedContextState> context_state) override;

  std::unique_ptr<gpu::SkiaGraphiteImageRepresentation> ProduceSkiaGraphite(
      gpu::SharedImageManager* manager,
      gpu::MemoryTypeTracker* tracker,
      scoped_refptr<gpu::SharedContextState> context_state) override;

 private:
  class DawnRepresentation final : public gpu::DawnImageRepresentation {
   public:
    DawnRepresentation(gpu::SharedImageManager* manager,
                       StandaloneBorrowedD3D12TextureBacking* backing,
                       gpu::MemoryTypeTracker* tracker,
                       wgpu::Device device,
                       wgpu::BackendType backend_type)
        : gpu::DawnImageRepresentation(manager, backing, tracker),
          device_(std::move(device)),
          backend_type_(backend_type) {}

    ~DawnRepresentation() override { EndAccess(); }

   private:
    wgpu::Texture BeginAccess(wgpu::TextureUsage usage,
                              wgpu::TextureUsage internal_usage) override {
      return borrowed_backing()->BeginDawnAccess(device_, backend_type_, usage,
                                                 internal_usage);
    }

    void EndAccess() override {
      if (device_) {
        borrowed_backing()->EndDawnAccess();
      }
    }

    StandaloneBorrowedD3D12TextureBacking* borrowed_backing() {
      return static_cast<StandaloneBorrowedD3D12TextureBacking*>(backing());
    }

    wgpu::Device device_;
    wgpu::BackendType backend_type_;
  };

  wgpu::SharedTextureMemory EnsureSharedTextureMemory(
      const wgpu::Device& device) {
    if (!shared_texture_memory_) {
      shared_texture_memory_ =
          gpu::CreateDawnSharedTextureMemory(device, resource_);
    }
    return shared_texture_memory_;
  }

  wgpu::Texture BeginDawnAccess(wgpu::Device device,
                                wgpu::BackendType backend_type,
                                wgpu::TextureUsage usage,
                                wgpu::TextureUsage internal_usage) {
    if (backend_type != wgpu::BackendType::D3D12 || access_open_ ||
        !resource_) {
      return nullptr;
    }
    wgpu::SharedTextureMemory shared_texture_memory =
        EnsureSharedTextureMemory(device);
    if (!shared_texture_memory) {
      return nullptr;
    }
    texture_ = gpu::CreateDawnSharedTexture(
        shared_texture_memory, usage, internal_usage,
        base::span<const wgpu::TextureFormat>());
    if (!texture_) {
      return nullptr;
    }

    write_access_ = (usage & gpu::DawnImageRepresentation::kWriteUsage) !=
                    wgpu::TextureUsage::None;
    wgpu::SharedTextureMemoryBeginAccessDescriptor begin_desc = {};
    begin_desc.initialized = IsCleared();
    begin_desc.concurrentRead = !write_access_ && IsCleared();
    if (shared_texture_memory.BeginAccess(texture_, &begin_desc) !=
        wgpu::Status::Success) {
      texture_ = nullptr;
      return nullptr;
    }
    access_open_ = true;
    return texture_;
  }

  void EndDawnAccess() {
    if (!access_open_ || !shared_texture_memory_ || !texture_) {
      return;
    }
    wgpu::SharedTextureMemoryEndAccessState end_state = {};
    shared_texture_memory_.EndAccess(texture_.Get(), &end_state);
    if (write_access_) {
      SetCleared();
    }
    texture_ = nullptr;
    access_open_ = false;
    write_access_ = false;
  }

  scoped_refptr<gpu::SharedContextState> context_state_;
  Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
  wgpu::SharedTextureMemory shared_texture_memory_;
  wgpu::Texture texture_;
  bool access_open_ = false;
  bool write_access_ = false;
};

std::unique_ptr<gpu::DawnImageRepresentation>
StandaloneBorrowedD3D12TextureBacking::ProduceDawn(
    gpu::SharedImageManager* manager,
    gpu::MemoryTypeTracker* tracker,
    const wgpu::Device& device,
    wgpu::BackendType backend_type,
    std::vector<wgpu::TextureFormat> view_formats,
    scoped_refptr<gpu::SharedContextState> context_state) {
  if (context_state != context_state_ || backend_type != wgpu::BackendType::D3D12) {
    return nullptr;
  }
  return std::make_unique<DawnRepresentation>(manager, this, tracker, device,
                                              backend_type);
}

std::unique_ptr<gpu::SkiaGraphiteImageRepresentation>
StandaloneBorrowedD3D12TextureBacking::ProduceSkiaGraphite(
    gpu::SharedImageManager* manager,
    gpu::MemoryTypeTracker* tracker,
    scoped_refptr<gpu::SharedContextState> context_state) {
  if (context_state != context_state_ ||
      !context_state_->dawn_context_provider()) {
    return nullptr;
  }
  wgpu::Device device = context_state_->dawn_context_provider()->GetDevice();
  wgpu::BackendType backend_type =
      context_state_->dawn_context_provider()->backend_type();
  auto dawn_representation = ProduceDawn(
      manager, tracker, device, backend_type, {}, context_state);
  if (!dawn_representation) {
    return nullptr;
  }
  return std::make_unique<gpu::SkiaGraphiteDawnImageRepresentation>(
      std::move(dawn_representation), context_state,
      context_state->gpu_main_graphite_recorder(), manager, this, tracker);
}
#endif  // BUILDFLAG(IS_WIN) &&
        // BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER

class StandaloneSkiaOutputSurfaceDependency final
    : public viz::SkiaOutputSurfaceDependency {
 public:
  StandaloneSkiaOutputSurfaceDependency(
      std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder,
      gpu::SurfaceHandle surface_handle,
      std::string* failure_reason,
      bool use_vulkan_offscreen,
      bool use_d3d12_offscreen,
      bool* vulkan_context_provider_available,
      bool* shared_context_state_is_vulkan)
      : gpu_thread_holder_(std::move(gpu_thread_holder)),
        surface_handle_(surface_handle),
        failure_reason_(failure_reason),
        use_vulkan_offscreen_(use_vulkan_offscreen),
        use_d3d12_offscreen_(use_d3d12_offscreen),
        vulkan_context_provider_available_(vulkan_context_provider_available),
        shared_context_state_is_vulkan_(shared_context_state_is_vulkan),
        client_task_runner_(base::SingleThreadTaskRunner::GetCurrentDefault()) {
    vulkan_gpu_preferences_ = gpu_thread_holder_
                                  ? gpu_thread_holder_->gpu_preferences()
                                  : gpu::GpuPreferences();
    vulkan_gpu_preferences_.gr_context_type = gpu::GrContextType::kVulkan;
    d3d12_gpu_preferences_ = gpu_thread_holder_
                                  ? gpu_thread_holder_->gpu_preferences()
                                  : gpu::GpuPreferences();
    d3d12_gpu_preferences_.gr_context_type =
        gpu::GrContextType::kGraphiteDawn;
  }

  StandaloneSkiaOutputSurfaceDependency(
      const StandaloneSkiaOutputSurfaceDependency&) = delete;
  StandaloneSkiaOutputSurfaceDependency& operator=(
      const StandaloneSkiaOutputSurfaceDependency&) = delete;

  ~StandaloneSkiaOutputSurfaceDependency() override = default;

  std::unique_ptr<gpu::SingleTaskSequence> CreateSequence() override {
    if (!gpu_thread_holder_ || !gpu_thread_holder_->GetTaskExecutor()) {
      SetFailure("Viz Display cannot create a GPU task sequence");
      return nullptr;
    }
    return std::make_unique<gpu::SchedulerSequence>(
        gpu_thread_holder_->scheduler(), gpu_thread_holder_->task_runner());
  }

  gpu::SharedImageManager* GetSharedImageManager() override {
    return gpu_thread_holder_ ? gpu_thread_holder_->shared_image_manager()
                              : nullptr;
  }

  gpu::SyncPointManager* GetSyncPointManager() override {
    return gpu_thread_holder_ ? gpu_thread_holder_->sync_point_manager()
                              : nullptr;
  }

  const gpu::GpuDriverBugWorkarounds& GetGpuDriverBugWorkarounds() override {
    return gpu_thread_holder_->gpu_driver_bug_workarounds();
  }

  scoped_refptr<gpu::SharedContextState> GetSharedContextState() override {
    if (use_vulkan_offscreen_ && IsOffscreen()) {
      scoped_refptr<gpu::SharedContextState> context_state =
          gpu_thread_holder_ ? gpu_thread_holder_->GetSharedContextState()
                             : nullptr;
      if (!context_state || !context_state->GrContextIsVulkan() ||
          !context_state->vk_context_provider()) {
        SetFailure(
            "offscreen Vulkan Display requires a Vulkan in-process GPU "
            "SharedContextState");
        return nullptr;
      }
      if (shared_context_state_is_vulkan_) {
        *shared_context_state_is_vulkan_ = context_state->GrContextIsVulkan();
      }
      return context_state;
    }
    return gpu_thread_holder_ ? gpu_thread_holder_->GetSharedContextState()
                              : nullptr;
  }

  gpu::raster::GrShaderCache* GetGrShaderCache() override { return nullptr; }

  viz::VulkanContextProvider* GetVulkanContextProvider() override {
    if (use_vulkan_offscreen_ && IsOffscreen()) {
      scoped_refptr<gpu::SharedContextState> context_state =
          gpu_thread_holder_ ? gpu_thread_holder_->GetSharedContextState()
                             : nullptr;
      if (!context_state || !context_state->vk_context_provider()) {
        SetFailure(
            "offscreen Vulkan Display requires a Vulkan context provider from "
            "the in-process GPU holder");
        return nullptr;
      }
      if (vulkan_context_provider_available_) {
        *vulkan_context_provider_available_ =
            context_state->vk_context_provider() != nullptr;
      }
      return context_state->vk_context_provider();
    }
    return nullptr;
  }

  gpu::DawnContextProvider* GetDawnContextProvider() override {
#if BUILDFLAG(SKIA_USE_DAWN) && BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
    if (use_d3d12_offscreen_ && IsOffscreen()) {
      return gpu_thread_holder_ ? gpu_thread_holder_->dawn_context_provider()
                                : nullptr;
    }
#endif
    return nullptr;
  }

  const gpu::GpuPreferences& GetGpuPreferences() const override {
    if (use_vulkan_offscreen_ && surface_handle_ == gpu::kNullSurfaceHandle) {
      return vulkan_gpu_preferences_;
    }
    if (use_d3d12_offscreen_ && surface_handle_ == gpu::kNullSurfaceHandle) {
      return d3d12_gpu_preferences_;
    }
    return gpu_thread_holder_->gpu_preferences();
  }

  const gpu::GpuFeatureInfo& GetGpuFeatureInfo() override {
    return gpu_thread_holder_->gpu_feature_info();
  }

  bool IsOffscreen() override {
    return surface_handle_ == gpu::kNullSurfaceHandle;
  }

  gpu::SurfaceHandle GetSurfaceHandle() override { return surface_handle_; }

  scoped_refptr<gl::Presenter> CreatePresenter() override {
    if (IsOffscreen()) {
      SetFailure("Viz Display has no native HWND surface handle for presenter");
      return nullptr;
    }
    return gpu::ImageTransportSurface::CreatePresenter(
        GetSharedContextState(), GetGpuDriverBugWorkarounds(),
        GetGpuFeatureInfo(), surface_handle_);
  }

  scoped_refptr<gl::GLSurface> CreateGLSurface(
      gl::GLSurfaceFormat format) override {
    if (IsOffscreen()) {
      SetFailure("Viz Display has no native HWND surface handle for GL surface");
      return nullptr;
    }
    auto context_state = GetSharedContextState();
    if (!context_state || !context_state->display()) {
      SetFailure("Viz Display shared context has no GL display");
      return nullptr;
    }
    return gpu::ImageTransportSurface::CreateNativeGLSurface(
        context_state->display(), surface_handle_, format);
  }

  scoped_refptr<base::SingleThreadTaskRunner> GetClientTaskRunner() override {
    return client_task_runner_;
  }

  void ScheduleGrContextCleanup() override {
    if (auto context_state = GetSharedContextState()) {
      context_state->ScheduleSkiaCleanup();
    }
  }

  void ScheduleDelayedGPUTaskFromGPUThread(base::OnceClosure task) override {
    if (!gpu_thread_holder_) {
      return;
    }
    gpu_thread_holder_->task_runner()->PostDelayedTask(
        FROM_HERE, std::move(task), base::Milliseconds(2));
  }

  void DidLoseContext(gpu::error::ContextLostReason reason,
                      const GURL& active_url) override {
    SetFailure("Viz Display Skia output surface lost its GPU context");
  }

  bool NeedsSupportForExternalStencil() override { return false; }

  bool IsUsingCompositorGpuThread() override { return false; }

  scoped_refptr<base::SingleThreadTaskRunner>
  GpuTaskRunnerIfOffSequenceForTesting() const {
    if (!gpu_thread_holder_) {
      return nullptr;
    }
    scoped_refptr<base::SingleThreadTaskRunner> task_runner =
        gpu_thread_holder_->task_runner();
    if (!task_runner || task_runner->RunsTasksInCurrentSequence()) {
      return nullptr;
    }
    return task_runner;
  }

  std::string RunBorrowedVkImageBackingSmokeForTesting() {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 std::string* result, base::WaitableEvent* completed) {
                *result =
                    self->RunBorrowedVkImageBackingSmokeOnCurrentSequence();
                completed->Signal();
              },
              base::Unretained(this), &result, &completed));
      if (!posted) {
        return "gpu_borrowed_vkimage_backing_smoke: failed failure=failed "
               "to post borrowed VkImage smoke to Vulkan context sequence";
      }
      completed.Wait();
      return result;
    }
    return RunBorrowedVkImageBackingSmokeOnCurrentSequence();
  }

  std::string RunVulkanBackdropMaskPrototypeForTesting(
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& output_size,
      const gfx::Size& css_viewport) {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 std::vector<LiveBackdropFilterRegion> regions,
                 gfx::Size output_size, gfx::Size css_viewport,
                 std::string* result, base::WaitableEvent* completed) {
                *result = self->RunVulkanBackdropMaskPrototypeOnCurrentSequence(
                    regions, output_size, css_viewport);
                completed->Signal();
              },
              base::Unretained(this), regions, output_size, css_viewport,
              &result, &completed));
      if (!posted) {
        return "gpu_vulkan_backdrop_mask_prototype_smoke: failed "
               "failure=failed to post mask prototype to Vulkan context "
               "sequence";
      }
      completed.Wait();
      return result;
    }
    return RunVulkanBackdropMaskPrototypeOnCurrentSequence(regions, output_size,
                                                          css_viewport);
  }

  std::string RunD3D12BackdropMaskPrototypeForTesting(
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& output_size,
      const gfx::Size& css_viewport) {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 std::vector<LiveBackdropFilterRegion> regions,
                 gfx::Size output_size, gfx::Size css_viewport,
                 std::string* result, base::WaitableEvent* completed) {
                *result = self->RunD3D12BackdropMaskPrototypeOnCurrentSequence(
                    regions, output_size, css_viewport);
                completed->Signal();
              },
              base::Unretained(this), regions, output_size, css_viewport,
              &result, &completed));
      if (!posted) {
        return "gpu_d3d12_backdrop_mask_prototype_smoke: failed "
               "failure=failed to post mask prototype to D3D12 context "
               "sequence";
      }
      completed.Wait();
      return result;
    }
    return RunD3D12BackdropMaskPrototypeOnCurrentSequence(regions, output_size,
                                                          css_viewport);
  }

  std::string RunBorrowedVkImageBackingSmokeOnCurrentSequence() {
    StandaloneBorrowedVkImageBackingSmokeResult result;
    std::unique_ptr<gpu::VulkanImage> target_image;
    scoped_refptr<gpu::MemoryTracker> memory_tracker;
    std::unique_ptr<gpu::MemoryTypeTracker> memory_type_tracker;
    std::unique_ptr<gpu::SharedImageRepresentationFactoryRef> factory_ref;
    std::unique_ptr<gpu::SkiaImageRepresentation> skia_representation;
    std::unique_ptr<gpu::SkiaImageRepresentation::ScopedWriteAccess>
        write_access;

    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      write_access.reset();
      skia_representation.reset();
      if (factory_ref) {
        factory_ref.reset();
        result.backing_released = true;
      }
      memory_type_tracker.reset();
      memory_tracker.reset();
      if (target_image) {
        target_image->Destroy();
        result.target_destroyed = true;
      }
      return StandaloneBorrowedVkImageBackingSmokeLine(result);
    };

    if (!use_vulkan_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "borrowed VkImage smoke requires offscreen Vulkan output");
    }
    gpu::SharedImageManager* manager = GetSharedImageManager();
    if (!manager) {
      return finish_with_failure("SharedImageManager is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    viz::VulkanContextProvider* vulkan_provider =
        context_state->vk_context_provider();
    gpu::VulkanDeviceQueue* device_queue = vulkan_provider->GetDeviceQueue();
    if (!device_queue) {
      return finish_with_failure("Vulkan context provider has no device queue");
    }
    result.context_available = true;

    const gfx::Size target_size(result.width, result.height);
    target_image = gpu::VulkanImage::Create(
        device_queue, target_size, VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
            VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    if (!target_image || target_image->image() == VK_NULL_HANDLE) {
      return finish_with_failure("stand-in target VkImage creation failed");
    }
    result.target_created = true;

    const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
    const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
    const GrVkImageInfo vk_image_info =
        gpu::CreateGrVkImageInfo(target_image.get(), format, color_space);
    const GrBackendTexture backend_texture =
        GrBackendTextures::MakeVk(result.width, result.height, vk_image_info);
    if (!backend_texture.isValid()) {
      return finish_with_failure("Skia backend texture wrapping failed");
    }
    result.backend_texture_valid = true;

    const gpu::Mailbox mailbox = gpu::Mailbox::Generate();
    const gpu::SharedImageUsageSet usage =
        gpu::SHARED_IMAGE_USAGE_DISPLAY_READ |
        gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE;
    gpu::SharedImageInfo si_info(format, target_size, color_space,
                                 kTopLeft_GrSurfaceOrigin,
                                 kPremul_SkAlphaType, usage,
                                 "StandaloneBorrowedVkImageBackingSmoke");
    memory_tracker = base::MakeRefCounted<gpu::MemoryTracker>();
    memory_type_tracker =
        std::make_unique<gpu::MemoryTypeTracker>(memory_tracker);
    factory_ref = manager->Register(
        std::make_unique<StandaloneBorrowedVkImageBacking>(
            mailbox, si_info, context_state, backend_texture),
        memory_type_tracker.get());
    if (!factory_ref) {
      return finish_with_failure("borrowed VkImage backing registration failed");
    }
    result.registered = true;

    skia_representation = manager->ProduceSkia(
        mailbox, memory_type_tracker.get(), context_state,
        gpu::SharedImageUsageSet(gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE));
    if (!skia_representation) {
      return finish_with_failure("borrowed VkImage Skia representation failed");
    }
    result.produced_skia = true;

    std::vector<GrBackendSemaphore> begin_semaphores;
    std::vector<GrBackendSemaphore> end_semaphores;
    write_access = skia_representation->BeginScopedWriteAccess(
        /*final_msaa_count=*/1, SkSurfaceProps(), &begin_semaphores,
        &end_semaphores,
        gpu::SharedImageRepresentation::AllowUnclearedAccess::kYes);
    if (!write_access || !write_access->has_surfaces() ||
        !write_access->surface()) {
      return finish_with_failure("borrowed VkImage Skia write access failed");
    }
    result.write_access = true;
    SkSurface* surface = write_access->surface();
    if (!begin_semaphores.empty() &&
        !surface->wait(begin_semaphores.size(), begin_semaphores.data(),
                       /*deleteSemaphoresAfterWait=*/false)) {
      return finish_with_failure("borrowed VkImage begin semaphore wait failed");
    }

    constexpr SkColor kExpectedColor = SkColorSetARGB(255, 210, 99, 41);
    surface->getCanvas()->clear(kExpectedColor);
    context_state->gr_context()->flush(surface);
    if (!context_state->gr_context()->submit()) {
      return finish_with_failure("borrowed VkImage Skia submit failed");
    }

    const SkImageInfo readback_info =
        SkImageInfo::MakeN32Premul(result.width, result.height);
    std::vector<uint32_t> readback_pixels(
        static_cast<size_t>(result.width) * static_cast<size_t>(result.height));
    const size_t row_bytes =
        static_cast<size_t>(result.width) * sizeof(uint32_t);
    if (!surface->readPixels(readback_info, readback_pixels.data(), row_bytes,
                             0, 0)) {
      return finish_with_failure("borrowed VkImage readback verification failed");
    }
    SkPixmap pixmap(readback_info, readback_pixels.data(), row_bytes);
    const SkColor observed =
        pixmap.getColor(result.width / 2, result.height / 2);
    auto close_channel = [](uint8_t observed_channel,
                            uint8_t expected_channel) {
      return std::abs(static_cast<int>(observed_channel) -
                      static_cast<int>(expected_channel)) <= 4;
    };
    if (!close_channel(SkColorGetA(observed), SkColorGetA(kExpectedColor)) ||
        !close_channel(SkColorGetR(observed), SkColorGetR(kExpectedColor)) ||
        !close_channel(SkColorGetG(observed), SkColorGetG(kExpectedColor)) ||
        !close_channel(SkColorGetB(observed), SkColorGetB(kExpectedColor))) {
      return finish_with_failure("borrowed VkImage readback color mismatch");
    }
    result.readback_verified = true;

    write_access.reset();
    skia_representation.reset();
    factory_ref.reset();
    result.backing_released = true;
    memory_type_tracker.reset();
    memory_tracker.reset();
    target_image->Destroy();
    result.target_destroyed = true;
    target_image.reset();
    return StandaloneBorrowedVkImageBackingSmokeLine(result);
  }

  std::string RunVulkanBackdropMaskPrototypeOnCurrentSequence(
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& output_size,
      const gfx::Size& css_viewport) {
    constexpr const char* kLabel =
        "gpu_vulkan_backdrop_mask_prototype_smoke";
    std::unique_ptr<gpu::VulkanImage> target_image;

    auto finish_with_failure = [&](std::string failure) {
      if (target_image) {
        target_image->Destroy();
      }
      return std::string(kLabel) + ": failed failure=" + std::move(failure);
    };

    if (regions.empty()) {
      return finish_with_failure("no backdrop filter regions collected");
    }
    if (output_size.IsEmpty() || css_viewport.IsEmpty()) {
      return finish_with_failure("target or CSS viewport size is empty");
    }
    if (!use_vulkan_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "backdrop mask prototype requires offscreen Vulkan output");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    viz::VulkanContextProvider* vulkan_provider =
        context_state->vk_context_provider();
    gpu::VulkanDeviceQueue* device_queue = vulkan_provider->GetDeviceQueue();
    if (!device_queue) {
      return finish_with_failure("Vulkan context provider has no device queue");
    }

    target_image = gpu::VulkanImage::Create(
        device_queue, output_size, VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
            VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    if (!target_image || target_image->image() == VK_NULL_HANDLE) {
      return finish_with_failure(
          "stand-in backdrop mask VkImage creation failed");
    }

    const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
    const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
    const GrVkImageInfo vk_image_info =
        gpu::CreateGrVkImageInfo(target_image.get(), format, color_space);
    const GrBackendTexture backend_texture =
        GrBackendTextures::MakeVk(output_size.width(), output_size.height(),
                                  vk_image_info);
    if (!backend_texture.isValid()) {
      return finish_with_failure("Skia backend texture wrapping failed");
    }
    sk_sp<SkSurface> surface = SkSurfaces::WrapBackendTexture(
        context_state->gr_context(), backend_texture, kTopLeft_GrSurfaceOrigin,
        /*sampleCnt=*/1, kRGBA_8888_SkColorType, color_space.ToSkColorSpace(),
        nullptr);
    if (!surface) {
      return finish_with_failure("backdrop mask SkSurface wrapping failed");
    }

    SkCanvas* canvas = surface->getCanvas();
    canvas->clear(SkColors::kTransparent);
    SkPaint paint;
    paint.setStyle(SkPaint::kFill_Style);
    paint.setAntiAlias(true);

    const float scale_x = static_cast<float>(output_size.width()) /
                          static_cast<float>(css_viewport.width());
    const float scale_y = static_cast<float>(output_size.height()) /
                          static_cast<float>(css_viewport.height());
    const size_t encoded_region_count = std::min<size_t>(regions.size(), 255u);
    for (size_t i = 0; i < encoded_region_count; ++i) {
      const LiveBackdropFilterRegion& region = regions[i];
      const uint8_t region_id = static_cast<uint8_t>(i + 1u);
      paint.setColor(SkColorSetARGB(255, region_id, 255, 0));
      const SkRect rect = SkRect::MakeXYWH(
          region.x * scale_x, region.y * scale_y, region.width * scale_x,
          region.height * scale_y);
      if ((region.flags & kStandaloneBackdropFilterRoundedRect) != 0) {
        SkVector radii[4] = {
            {region.border_radius_top_left * scale_x,
             region.border_radius_top_left * scale_y},
            {region.border_radius_top_right * scale_x,
             region.border_radius_top_right * scale_y},
            {region.border_radius_bottom_right * scale_x,
             region.border_radius_bottom_right * scale_y},
            {region.border_radius_bottom_left * scale_x,
             region.border_radius_bottom_left * scale_y},
        };
        SkRRect rrect;
        rrect.setRectRadii(rect, radii);
        canvas->drawRRect(rrect, paint);
      } else {
        canvas->drawRect(rect, paint);
      }
    }

    context_state->gr_context()->flush(surface.get());
    if (!context_state->gr_context()->submit()) {
      return finish_with_failure("backdrop mask Skia submit failed");
    }

    const SkImageInfo readback_info =
        SkImageInfo::MakeN32Premul(output_size.width(), output_size.height());
    std::vector<uint32_t> readback_pixels(static_cast<size_t>(
        output_size.width()) * static_cast<size_t>(output_size.height()));
    const size_t row_bytes =
        static_cast<size_t>(output_size.width()) * sizeof(uint32_t);
    if (!surface->readPixels(readback_info, readback_pixels.data(), row_bytes,
                             0, 0)) {
      return finish_with_failure("backdrop mask readback failed");
    }
    std::array<bool, 256> seen_ids = {};
    size_t mask_pixels = 0;
    SkPixmap pixmap(readback_info, readback_pixels.data(), row_bytes);
    for (int y = 0; y < output_size.height(); ++y) {
      for (int x = 0; x < output_size.width(); ++x) {
        const SkColor color = pixmap.getColor(x, y);
        const uint8_t id = SkColorGetR(color);
        const uint8_t coverage = SkColorGetG(color);
        if (id != 0 && coverage != 0) {
          ++mask_pixels;
          seen_ids[id] = true;
        }
      }
    }
    size_t distinct_ids = 0;
    for (bool seen : seen_ids) {
      if (seen) {
        ++distinct_ids;
      }
    }
    if (mask_pixels == 0 || distinct_ids == 0) {
      return finish_with_failure("backdrop mask target remained empty");
    }

    context_state->gr_context()->flushAndSubmit(GrSyncCpu::kYes);
    if (device_queue) {
      vkDeviceWaitIdle(device_queue->GetVulkanDevice());
    }
    target_image->Destroy();
    target_image.reset();

    std::ostringstream out;
    out << kLabel << ": ok"
        << " encoding=rgba8_id_coverage"
        << " target=" << output_size.width() << "x" << output_size.height()
        << " regions=" << regions.size()
        << " encoded_regions=" << encoded_region_count
        << " distinct_ids=" << distinct_ids
        << " mask_pixels=" << mask_pixels;
    return out.str();
  }

  std::string RenderVulkanBackdropMaskToExternalTargetForTesting(
      const html_css_renderer::ExternalVulkanImageTarget* external_target,
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& output_size,
      const gfx::Size& css_viewport) {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 const html_css_renderer::ExternalVulkanImageTarget*
                     external_target,
                 const std::vector<LiveBackdropFilterRegion>* regions,
                 gfx::Size output_size, gfx::Size css_viewport,
                 std::string* result, base::WaitableEvent* completed) {
                *result =
                    self->RenderVulkanBackdropMaskToExternalTargetOnCurrentSequence(
                        external_target, *regions, output_size, css_viewport);
                completed->Signal();
              },
              base::Unretained(this), external_target, &regions, output_size,
              css_viewport, &result, &completed));
      if (!posted) {
        return "gpu_external_vkimage_backdrop_mask: failed failure=failed to "
               "post mask render to Vulkan context sequence";
      }
      completed.Wait();
      return result;
    }
    return RenderVulkanBackdropMaskToExternalTargetOnCurrentSequence(
        external_target, regions, output_size, css_viewport);
  }

  std::string RenderVulkanBackdropMaskToExternalTargetOnCurrentSequence(
      const html_css_renderer::ExternalVulkanImageTarget* external_target,
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& output_size,
      const gfx::Size& css_viewport) {
    constexpr const char* kLabel = "gpu_external_vkimage_backdrop_mask";
    auto finish_with_failure = [&](std::string failure) {
      DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return std::string(kLabel) + ": failed failure=" + std::move(failure);
    };

    if (!external_target) {
      return finish_with_failure("external Vulkan mask target is null");
    }
    if (regions.empty()) {
      return finish_with_failure("no backdrop filter regions collected");
    }
    if (output_size.IsEmpty() || css_viewport.IsEmpty()) {
      return finish_with_failure("target or CSS viewport size is empty");
    }
    scoped_refptr<gpu::ClientSharedImage> unused_shared_image;
    std::string prepare_result =
        PrepareBorrowedVkImageRenderCopyBlitTargetForTesting(
            output_size, nullptr, external_target, &unused_shared_image);
    if (!prepare_result.empty()) {
      return finish_with_failure(prepare_result);
    }
    if (!borrowed_blit_target_ || !borrowed_blit_target_->image) {
      return finish_with_failure(
          "external Vulkan mask target wrapper is unavailable");
    }

    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
    const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
    const GrVkImageInfo vk_image_info =
        gpu::CreateGrVkImageInfo(borrowed_blit_target_->image.get(), format,
                                 color_space);
    const GrBackendTexture backend_texture =
        GrBackendTextures::MakeVk(output_size.width(), output_size.height(),
                                  vk_image_info);
    if (!backend_texture.isValid()) {
      return finish_with_failure("Skia backend texture wrapping failed");
    }
    sk_sp<SkSurface> surface = SkSurfaces::WrapBackendTexture(
        context_state->gr_context(), backend_texture, kTopLeft_GrSurfaceOrigin,
        /*sampleCnt=*/1, kRGBA_8888_SkColorType, color_space.ToSkColorSpace(),
        nullptr);
    if (!surface) {
      return finish_with_failure("backdrop mask SkSurface wrapping failed");
    }

    SkCanvas* canvas = surface->getCanvas();
    canvas->clear(SkColors::kTransparent);
    SkPaint paint;
    paint.setStyle(SkPaint::kFill_Style);
    paint.setAntiAlias(true);

    const float scale_x = static_cast<float>(output_size.width()) /
                          static_cast<float>(css_viewport.width());
    const float scale_y = static_cast<float>(output_size.height()) /
                          static_cast<float>(css_viewport.height());
    const size_t encoded_region_count = std::min<size_t>(regions.size(), 255u);
    for (size_t i = 0; i < encoded_region_count; ++i) {
      const LiveBackdropFilterRegion& region = regions[i];
      const uint8_t region_id = static_cast<uint8_t>(i + 1u);
      paint.setColor(SkColorSetARGB(255, region_id, 255, 0));
      const SkRect rect = SkRect::MakeXYWH(
          region.x * scale_x, region.y * scale_y, region.width * scale_x,
          region.height * scale_y);
      if ((region.flags & kStandaloneBackdropFilterRoundedRect) != 0) {
        SkVector radii[4] = {
            {region.border_radius_top_left * scale_x,
             region.border_radius_top_left * scale_y},
            {region.border_radius_top_right * scale_x,
             region.border_radius_top_right * scale_y},
            {region.border_radius_bottom_right * scale_x,
             region.border_radius_bottom_right * scale_y},
            {region.border_radius_bottom_left * scale_x,
             region.border_radius_bottom_left * scale_y},
        };
        SkRRect rrect;
        rrect.setRectRadii(rect, radii);
        canvas->drawRRect(rrect, paint);
      } else {
        canvas->drawRect(rect, paint);
      }
    }

    context_state->gr_context()->flush(surface.get());
    if (!context_state->gr_context()->submit()) {
      return finish_with_failure("backdrop mask Skia submit failed");
    }

    const SkImageInfo readback_info =
        SkImageInfo::MakeN32Premul(output_size.width(), output_size.height());
    std::vector<uint32_t> readback_pixels(static_cast<size_t>(
        output_size.width()) * static_cast<size_t>(output_size.height()));
    const size_t row_bytes =
        static_cast<size_t>(output_size.width()) * sizeof(uint32_t);
    if (!surface->readPixels(readback_info, readback_pixels.data(), row_bytes,
                             0, 0)) {
      return finish_with_failure("backdrop mask readback failed");
    }
    std::array<bool, 256> seen_ids = {};
    size_t mask_pixels = 0;
    SkPixmap pixmap(readback_info, readback_pixels.data(), row_bytes);
    for (int y = 0; y < output_size.height(); ++y) {
      for (int x = 0; x < output_size.width(); ++x) {
        const SkColor color = pixmap.getColor(x, y);
        const uint8_t id = SkColorGetR(color);
        const uint8_t coverage = SkColorGetG(color);
        if (id != 0 && coverage != 0) {
          ++mask_pixels;
          seen_ids[id] = true;
        }
      }
    }
    size_t distinct_ids = 0;
    for (bool seen : seen_ids) {
      if (seen) {
        ++distinct_ids;
      }
    }
    if (mask_pixels == 0 || distinct_ids == 0) {
      return finish_with_failure("backdrop mask target remained empty");
    }
    context_state->gr_context()->flushAndSubmit(GrSyncCpu::kYes);
    WaitForBorrowedVkImageRenderCopyBlitTargetForTesting();
    DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();

    std::ostringstream out;
    out << kLabel << ": ok"
        << " encoding=rgba8_id_coverage"
        << " target=" << output_size.width() << "x" << output_size.height()
        << " regions=" << regions.size()
        << " encoded_regions=" << encoded_region_count
        << " distinct_ids=" << distinct_ids
        << " mask_pixels=" << mask_pixels
        << " ownership=borrowed";
    return out.str();
  }

  std::string RunD3D12BackdropMaskPrototypeOnCurrentSequence(
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& output_size,
      const gfx::Size& css_viewport) {
    constexpr const char* kLabel = "gpu_d3d12_backdrop_mask_prototype_smoke";
#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
    Microsoft::WRL::ComPtr<ID3D12Resource> target;
    Microsoft::WRL::ComPtr<ID3D12Resource> readback;
    HANDLE event_handle = nullptr;

    auto finish_with_failure = [&](std::string failure) {
      if (event_handle) {
        ::CloseHandle(event_handle);
      }
      return std::string(kLabel) + ": failed failure=" + std::move(failure);
    };

    if (regions.empty()) {
      return finish_with_failure("no backdrop filter regions collected");
    }
    if (output_size.IsEmpty() || css_viewport.IsEmpty()) {
      return finish_with_failure("target or CSS viewport size is empty");
    }
    if (!use_d3d12_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "backdrop mask prototype requires offscreen D3D12 output");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->IsGraphiteDawnD3D() ||
        !context_state->dawn_context_provider()) {
      return finish_with_failure(
          "offscreen runtime has no D3D12 Graphite/Dawn SharedContextState");
    }
    if (context_state->dawn_context_provider()->backend_type() !=
        wgpu::BackendType::D3D12) {
      return finish_with_failure("Dawn context provider is not D3D12");
    }
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue =
        context_state->dawn_context_provider()->GetD3D12CommandQueue();
    if (!queue) {
      return finish_with_failure("Dawn D3D12 command queue is unavailable");
    }
    Microsoft::WRL::ComPtr<ID3D12Device> device;
    if (FAILED(queue->GetDevice(IID_PPV_ARGS(&device))) || !device) {
      return finish_with_failure("Dawn D3D12 device is unavailable");
    }

    D3D12_HEAP_PROPERTIES heap_properties = {};
    heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heap_properties.CreationNodeMask = 1;
    heap_properties.VisibleNodeMask = 1;

    D3D12_RESOURCE_DESC texture_desc = {};
    texture_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    texture_desc.Width = static_cast<UINT64>(output_size.width());
    texture_desc.Height = static_cast<UINT>(output_size.height());
    texture_desc.DepthOrArraySize = 1;
    texture_desc.MipLevels = 1;
    texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture_desc.SampleDesc.Count = 1;
    texture_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    texture_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET |
                         D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;

    D3D12_CLEAR_VALUE clear_value = {};
    clear_value.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    HRESULT hr = device->CreateCommittedResource(
        &heap_properties, D3D12_HEAP_FLAG_NONE, &texture_desc,
        D3D12_RESOURCE_STATE_COMMON, &clear_value, IID_PPV_ARGS(&target));
    if (FAILED(hr) || !target) {
      return finish_with_failure("stand-in D3D12 mask target creation failed");
    }

    D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
    rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtv_heap_desc.NumDescriptors = 1;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap;
    hr = device->CreateDescriptorHeap(&rtv_heap_desc,
                                      IID_PPV_ARGS(&rtv_heap));
    if (FAILED(hr) || !rtv_heap) {
      return finish_with_failure("D3D12 mask RTV heap creation failed");
    }
    D3D12_RENDER_TARGET_VIEW_DESC rtv_desc = {};
    rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
    const D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle =
        rtv_heap->GetCPUDescriptorHandleForHeapStart();
    device->CreateRenderTargetView(target.Get(), &rtv_desc, rtv_handle);

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
    UINT row_count = 0;
    UINT64 row_size_bytes = 0;
    UINT64 total_bytes = 0;
    device->GetCopyableFootprints(&texture_desc, 0, 1, 0, &footprint,
                                  &row_count, &row_size_bytes, &total_bytes);
    if (row_count == 0 || row_size_bytes == 0 || total_bytes == 0) {
      return finish_with_failure("D3D12 mask readback footprint invalid");
    }

    D3D12_HEAP_PROPERTIES readback_heap = {};
    readback_heap.Type = D3D12_HEAP_TYPE_READBACK;
    readback_heap.CreationNodeMask = 1;
    readback_heap.VisibleNodeMask = 1;
    D3D12_RESOURCE_DESC buffer_desc = {};
    buffer_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    buffer_desc.Width = total_bytes;
    buffer_desc.Height = 1;
    buffer_desc.DepthOrArraySize = 1;
    buffer_desc.MipLevels = 1;
    buffer_desc.Format = DXGI_FORMAT_UNKNOWN;
    buffer_desc.SampleDesc.Count = 1;
    buffer_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    hr = device->CreateCommittedResource(
        &readback_heap, D3D12_HEAP_FLAG_NONE, &buffer_desc,
        D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback));
    if (FAILED(hr) || !readback) {
      return finish_with_failure("D3D12 mask readback resource creation failed");
    }

    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
    hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                        IID_PPV_ARGS(&allocator));
    if (FAILED(hr) || !allocator) {
      return finish_with_failure("D3D12 mask command allocator creation failed");
    }
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
    hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                   allocator.Get(), nullptr,
                                   IID_PPV_ARGS(&command_list));
    if (FAILED(hr) || !command_list) {
      return finish_with_failure("D3D12 mask command list creation failed");
    }

    D3D12_RESOURCE_BARRIER to_render_target = {};
    to_render_target.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    to_render_target.Transition.pResource = target.Get();
    to_render_target.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    to_render_target.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    to_render_target.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
    command_list->ResourceBarrier(1, &to_render_target);

    const FLOAT transparent[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    command_list->ClearRenderTargetView(rtv_handle, transparent, 0, nullptr);

    const float scale_x = static_cast<float>(output_size.width()) /
                          static_cast<float>(css_viewport.width());
    const float scale_y = static_cast<float>(output_size.height()) /
                          static_cast<float>(css_viewport.height());
    const size_t encoded_region_count = std::min<size_t>(regions.size(), 255u);
    size_t encoded_rects = 0;
    for (size_t i = 0; i < encoded_region_count; ++i) {
      const LiveBackdropFilterRegion& region = regions[i];
      LONG left = static_cast<LONG>(std::floor(region.x * scale_x));
      LONG top = static_cast<LONG>(std::floor(region.y * scale_y));
      LONG right =
          static_cast<LONG>(std::ceil((region.x + region.width) * scale_x));
      LONG bottom =
          static_cast<LONG>(std::ceil((region.y + region.height) * scale_y));
      left = std::clamp<LONG>(left, 0, output_size.width());
      top = std::clamp<LONG>(top, 0, output_size.height());
      right = std::clamp<LONG>(right, 0, output_size.width());
      bottom = std::clamp<LONG>(bottom, 0, output_size.height());
      if (right <= left || bottom <= top) {
        continue;
      }
      const D3D12_RECT rect = {left, top, right, bottom};
      const uint8_t region_id = static_cast<uint8_t>(i + 1u);
      const FLOAT color[4] = {static_cast<FLOAT>(region_id) / 255.0f,
                              1.0f, 0.0f, 1.0f};
      command_list->ClearRenderTargetView(rtv_handle, color, 1, &rect);
      ++encoded_rects;
    }

    D3D12_RESOURCE_BARRIER to_copy_source = {};
    to_copy_source.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    to_copy_source.Transition.pResource = target.Get();
    to_copy_source.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    to_copy_source.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    to_copy_source.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE;
    command_list->ResourceBarrier(1, &to_copy_source);

    D3D12_TEXTURE_COPY_LOCATION src = {};
    src.pResource = target.Get();
    src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src.SubresourceIndex = 0;
    D3D12_TEXTURE_COPY_LOCATION dst = {};
    dst.pResource = readback.Get();
    dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    dst.PlacedFootprint = footprint;
    command_list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

    hr = command_list->Close();
    if (FAILED(hr)) {
      return finish_with_failure("D3D12 mask command list close failed");
    }
    ID3D12CommandList* command_lists[] = {command_list.Get()};
    queue->ExecuteCommandLists(1, command_lists);

    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    if (FAILED(hr) || !fence) {
      return finish_with_failure("D3D12 mask fence creation failed");
    }
    event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!event_handle) {
      return finish_with_failure("D3D12 mask fence event creation failed");
    }
    constexpr UINT64 kFenceValue = 1;
    hr = queue->Signal(fence.Get(), kFenceValue);
    if (FAILED(hr)) {
      return finish_with_failure("D3D12 mask queue signal failed");
    }
    if (fence->GetCompletedValue() < kFenceValue) {
      hr = fence->SetEventOnCompletion(kFenceValue, event_handle);
      if (FAILED(hr)) {
        return finish_with_failure("D3D12 mask fence wait setup failed");
      }
      ::WaitForSingleObject(event_handle, 5000);
    }
    ::CloseHandle(event_handle);
    event_handle = nullptr;
    if (fence->GetCompletedValue() < kFenceValue) {
      return finish_with_failure("D3D12 mask fence wait timed out");
    }

    void* mapped = nullptr;
    D3D12_RANGE read_range = {0, static_cast<SIZE_T>(total_bytes)};
    hr = readback->Map(0, &read_range, &mapped);
    if (FAILED(hr) || !mapped) {
      return finish_with_failure("D3D12 mask readback map failed");
    }
    std::array<bool, 256> seen_ids = {};
    size_t mask_pixels = 0;
    const uint8_t* mapped_bytes = static_cast<const uint8_t*>(mapped);
    for (int y = 0; y < output_size.height(); ++y) {
      const uint8_t* row =
          mapped_bytes + footprint.Offset +
          static_cast<size_t>(y) * footprint.Footprint.RowPitch;
      for (int x = 0; x < output_size.width(); ++x) {
        const uint8_t* pixel = row + static_cast<size_t>(x) * 4u;
        const uint8_t id = pixel[0];
        const uint8_t coverage = pixel[1];
        if (id != 0 && coverage != 0) {
          ++mask_pixels;
          seen_ids[id] = true;
        }
      }
    }
    D3D12_RANGE written_range = {0, 0};
    readback->Unmap(0, &written_range);

    size_t distinct_ids = 0;
    for (bool seen : seen_ids) {
      if (seen) {
        ++distinct_ids;
      }
    }
    if (encoded_rects == 0 || mask_pixels == 0 || distinct_ids == 0) {
      return finish_with_failure("D3D12 backdrop mask target remained empty");
    }

    std::ostringstream out;
    out << kLabel << ": ok"
        << " encoding=rgba8_id_coverage"
        << " shape=rectangular_coverage_mvp"
        << " target=" << output_size.width() << "x" << output_size.height()
        << " regions=" << regions.size()
        << " encoded_regions=" << encoded_region_count
        << " encoded_rects=" << encoded_rects
        << " distinct_ids=" << distinct_ids
        << " mask_pixels=" << mask_pixels;
    return out.str();
#else
    return std::string(kLabel) +
           ": blocked failure=D3D12/Dawn external targets are not enabled in "
           "this build";
#endif
  }

  std::string RenderD3D12BackdropMaskToExternalTargetForTesting(
      void* d3d12_resource,
      void* shared_handle,
      int width,
      int height,
      const std::vector<LiveBackdropFilterRegion>& regions,
      const gfx::Size& css_viewport) {
#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
    constexpr const char* kLabel = "gpu_external_d3d12_backdrop_mask";
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 uintptr_t d3d12_resource,
                 uintptr_t shared_handle,
                 int width,
                 int height,
                 std::vector<LiveBackdropFilterRegion> regions,
                 gfx::Size css_viewport,
                 std::string* result,
                 base::WaitableEvent* completed) {
                *result =
                    self->RenderD3D12BackdropMaskToExternalTargetForTesting(
                        reinterpret_cast<void*>(d3d12_resource),
                        reinterpret_cast<void*>(shared_handle), width, height,
                        regions, css_viewport);
                completed->Signal();
              },
              base::Unretained(this),
              reinterpret_cast<uintptr_t>(d3d12_resource),
              reinterpret_cast<uintptr_t>(shared_handle), width, height,
              regions, css_viewport, &result, &completed));
      if (!posted) {
        return std::string(kLabel) +
               ": failed failure=failed to post D3D12 backdrop mask task";
      }
      completed.Wait();
      return result;
    }
    Microsoft::WRL::ComPtr<ID3D12Resource> readback;
    HANDLE event_handle = nullptr;

    auto finish_with_failure = [&](std::string failure) {
      if (event_handle) {
        ::CloseHandle(event_handle);
      }
      DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return std::string(kLabel) + ": failed failure=" + std::move(failure);
    };

    if (regions.empty()) {
      return finish_with_failure("no backdrop filter regions collected");
    }
    if (css_viewport.IsEmpty()) {
      return finish_with_failure("CSS viewport size is empty");
    }
    gfx::Size output_size(width, height);
    if (output_size.IsEmpty() && d3d12_resource) {
      ID3D12Resource* resource = static_cast<ID3D12Resource*>(d3d12_resource);
      const D3D12_RESOURCE_DESC desc = resource->GetDesc();
      output_size =
          gfx::Size(static_cast<int>(desc.Width), static_cast<int>(desc.Height));
    }
    if (output_size.IsEmpty()) {
      return finish_with_failure("target size is empty");
    }
    scoped_refptr<gpu::ClientSharedImage> unused_shared_image;
    std::string prepare_result =
        PrepareBorrowedD3D12RenderCopyBlitTargetForTesting(
            output_size, static_cast<ID3D12Resource*>(d3d12_resource),
            shared_handle, &unused_shared_image);
    if (!prepare_result.empty()) {
      return finish_with_failure(prepare_result);
    }
    if (!borrowed_d3d12_blit_target_ ||
        !borrowed_d3d12_blit_target_->resource) {
      return finish_with_failure(
          "external D3D12 mask target wrapper is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->IsGraphiteDawnD3D() ||
        !context_state->dawn_context_provider()) {
      return finish_with_failure(
          "offscreen runtime has no D3D12 Graphite/Dawn SharedContextState");
    }
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue =
        context_state->dawn_context_provider()->GetD3D12CommandQueue();
    if (!queue) {
      return finish_with_failure("Dawn D3D12 command queue is unavailable");
    }
    Microsoft::WRL::ComPtr<ID3D12Device> device;
    if (FAILED(queue->GetDevice(IID_PPV_ARGS(&device))) || !device) {
      return finish_with_failure("Dawn D3D12 device is unavailable");
    }

    ID3D12Resource* target = borrowed_d3d12_blit_target_->resource.Get();
    D3D12_RESOURCE_DESC texture_desc = target->GetDesc();
    D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
    rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    rtv_heap_desc.NumDescriptors = 1;
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap;
    HRESULT hr = device->CreateDescriptorHeap(&rtv_heap_desc,
                                              IID_PPV_ARGS(&rtv_heap));
    if (FAILED(hr) || !rtv_heap) {
      return finish_with_failure("D3D12 mask RTV heap creation failed");
    }
    D3D12_RENDER_TARGET_VIEW_DESC rtv_desc = {};
    rtv_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
    const D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle =
        rtv_heap->GetCPUDescriptorHandleForHeapStart();
    device->CreateRenderTargetView(target, &rtv_desc, rtv_handle);

    D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
    UINT row_count = 0;
    UINT64 row_size_bytes = 0;
    UINT64 total_bytes = 0;
    device->GetCopyableFootprints(&texture_desc, 0, 1, 0, &footprint,
                                  &row_count, &row_size_bytes, &total_bytes);
    if (row_count == 0 || row_size_bytes == 0 || total_bytes == 0) {
      return finish_with_failure("D3D12 mask readback footprint invalid");
    }

    D3D12_HEAP_PROPERTIES readback_heap = {};
    readback_heap.Type = D3D12_HEAP_TYPE_READBACK;
    readback_heap.CreationNodeMask = 1;
    readback_heap.VisibleNodeMask = 1;
    D3D12_RESOURCE_DESC buffer_desc = {};
    buffer_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    buffer_desc.Width = total_bytes;
    buffer_desc.Height = 1;
    buffer_desc.DepthOrArraySize = 1;
    buffer_desc.MipLevels = 1;
    buffer_desc.Format = DXGI_FORMAT_UNKNOWN;
    buffer_desc.SampleDesc.Count = 1;
    buffer_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    hr = device->CreateCommittedResource(
        &readback_heap, D3D12_HEAP_FLAG_NONE, &buffer_desc,
        D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback));
    if (FAILED(hr) || !readback) {
      return finish_with_failure("D3D12 mask readback resource creation failed");
    }

    Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
    hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                        IID_PPV_ARGS(&allocator));
    if (FAILED(hr) || !allocator) {
      return finish_with_failure("D3D12 mask command allocator creation failed");
    }
    Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
    hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                   allocator.Get(), nullptr,
                                   IID_PPV_ARGS(&command_list));
    if (FAILED(hr) || !command_list) {
      return finish_with_failure("D3D12 mask command list creation failed");
    }

    D3D12_RESOURCE_BARRIER to_render_target = {};
    to_render_target.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    to_render_target.Transition.pResource = target;
    to_render_target.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    to_render_target.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
    to_render_target.Transition.StateAfter =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    command_list->ResourceBarrier(1, &to_render_target);

    const FLOAT transparent[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    command_list->ClearRenderTargetView(rtv_handle, transparent, 0, nullptr);

    const float scale_x = static_cast<float>(output_size.width()) /
                          static_cast<float>(css_viewport.width());
    const float scale_y = static_cast<float>(output_size.height()) /
                          static_cast<float>(css_viewport.height());
    const size_t encoded_region_count = std::min<size_t>(regions.size(), 255u);
    size_t encoded_rects = 0;
    for (size_t i = 0; i < encoded_region_count; ++i) {
      const LiveBackdropFilterRegion& region = regions[i];
      LONG left = static_cast<LONG>(std::floor(region.x * scale_x));
      LONG top = static_cast<LONG>(std::floor(region.y * scale_y));
      LONG right =
          static_cast<LONG>(std::ceil((region.x + region.width) * scale_x));
      LONG bottom =
          static_cast<LONG>(std::ceil((region.y + region.height) * scale_y));
      left = std::clamp<LONG>(left, 0, output_size.width());
      top = std::clamp<LONG>(top, 0, output_size.height());
      right = std::clamp<LONG>(right, 0, output_size.width());
      bottom = std::clamp<LONG>(bottom, 0, output_size.height());
      if (right <= left || bottom <= top) {
        continue;
      }
      const D3D12_RECT rect = {left, top, right, bottom};
      const uint8_t region_id = static_cast<uint8_t>(i + 1u);
      const FLOAT color[4] = {static_cast<FLOAT>(region_id) / 255.0f,
                              1.0f, 0.0f, 1.0f};
      command_list->ClearRenderTargetView(rtv_handle, color, 1, &rect);
      ++encoded_rects;
    }

    D3D12_RESOURCE_BARRIER to_copy_source = {};
    to_copy_source.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    to_copy_source.Transition.pResource = target;
    to_copy_source.Transition.Subresource =
        D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    to_copy_source.Transition.StateBefore =
        D3D12_RESOURCE_STATE_RENDER_TARGET;
    to_copy_source.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE;
    command_list->ResourceBarrier(1, &to_copy_source);

    D3D12_TEXTURE_COPY_LOCATION src = {};
    src.pResource = target;
    src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
    src.SubresourceIndex = 0;
    D3D12_TEXTURE_COPY_LOCATION dst = {};
    dst.pResource = readback.Get();
    dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
    dst.PlacedFootprint = footprint;
    command_list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

    hr = command_list->Close();
    if (FAILED(hr)) {
      return finish_with_failure("D3D12 mask command list close failed");
    }
    ID3D12CommandList* command_lists[] = {command_list.Get()};
    queue->ExecuteCommandLists(1, command_lists);

    Microsoft::WRL::ComPtr<ID3D12Fence> fence;
    hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    if (FAILED(hr) || !fence) {
      return finish_with_failure("D3D12 mask fence creation failed");
    }
    event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!event_handle) {
      return finish_with_failure("D3D12 mask fence event creation failed");
    }
    constexpr UINT64 kFenceValue = 1;
    hr = queue->Signal(fence.Get(), kFenceValue);
    if (FAILED(hr)) {
      return finish_with_failure("D3D12 mask queue signal failed");
    }
    if (fence->GetCompletedValue() < kFenceValue) {
      hr = fence->SetEventOnCompletion(kFenceValue, event_handle);
      if (FAILED(hr)) {
        return finish_with_failure("D3D12 mask fence wait setup failed");
      }
      ::WaitForSingleObject(event_handle, 5000);
    }
    ::CloseHandle(event_handle);
    event_handle = nullptr;
    if (fence->GetCompletedValue() < kFenceValue) {
      return finish_with_failure("D3D12 mask fence wait timed out");
    }

    void* mapped = nullptr;
    D3D12_RANGE read_range = {0, static_cast<SIZE_T>(total_bytes)};
    hr = readback->Map(0, &read_range, &mapped);
    if (FAILED(hr) || !mapped) {
      return finish_with_failure("D3D12 mask readback map failed");
    }
    std::array<bool, 256> seen_ids = {};
    size_t mask_pixels = 0;
    const uint8_t* mapped_bytes = static_cast<const uint8_t*>(mapped);
    for (int y = 0; y < output_size.height(); ++y) {
      const uint8_t* row =
          mapped_bytes + footprint.Offset +
          static_cast<size_t>(y) * footprint.Footprint.RowPitch;
      for (int x = 0; x < output_size.width(); ++x) {
        const uint8_t* pixel = row + static_cast<size_t>(x) * 4u;
        const uint8_t id = pixel[0];
        const uint8_t coverage = pixel[1];
        if (id != 0 && coverage != 0) {
          ++mask_pixels;
          seen_ids[id] = true;
        }
      }
    }
    D3D12_RANGE written_range = {0, 0};
    readback->Unmap(0, &written_range);

    size_t distinct_ids = 0;
    for (bool seen : seen_ids) {
      if (seen) {
        ++distinct_ids;
      }
    }
    if (encoded_rects == 0 || mask_pixels == 0 || distinct_ids == 0) {
      return finish_with_failure("D3D12 backdrop mask target remained empty");
    }
    DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();

    std::ostringstream out;
    out << kLabel << ": ok"
        << " encoding=rgba8_id_coverage"
        << " shape=rectangular_coverage_mvp"
        << " target=" << output_size.width() << "x" << output_size.height()
        << " regions=" << regions.size()
        << " encoded_regions=" << encoded_region_count
        << " encoded_rects=" << encoded_rects
        << " distinct_ids=" << distinct_ids
        << " mask_pixels=" << mask_pixels
        << " ownership=borrowed";
    return out.str();
#else
    return "gpu_external_d3d12_backdrop_mask: blocked failure=D3D12/Dawn "
           "external targets are not enabled in this build";
#endif
  }

  std::string RunBorrowedVkImageRenderCopySmokeForTesting(
      scoped_refptr<gpu::ClientSharedImage> source_shared_image) {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 scoped_refptr<gpu::ClientSharedImage> source_shared_image,
                 std::string* result, base::WaitableEvent* completed) {
                *result =
                    self->RunBorrowedVkImageRenderCopySmokeOnCurrentSequence(
                        std::move(source_shared_image));
                completed->Signal();
              },
              base::Unretained(this), std::move(source_shared_image), &result,
              &completed));
      if (!posted) {
        return "gpu_borrowed_vkimage_render_copy_smoke: failed "
               "failure=failed to post render-copy smoke to Vulkan context "
               "sequence";
      }
      completed.Wait();
      return result;
    }
    return RunBorrowedVkImageRenderCopySmokeOnCurrentSequence(
        std::move(source_shared_image));
  }

  std::string RunGpuOutputVulkanPixelSmokeForTesting(
      scoped_refptr<gpu::ClientSharedImage> source_shared_image) {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 scoped_refptr<gpu::ClientSharedImage> source_shared_image,
                 std::string* result, base::WaitableEvent* completed) {
                *result = self->RunGpuOutputVulkanPixelSmokeOnCurrentSequence(
                    std::move(source_shared_image));
                completed->Signal();
              },
              base::Unretained(this), std::move(source_shared_image), &result,
              &completed));
      if (!posted) {
        return "gpu_output_vulkan_pixel_smoke: failed failure=failed to post "
               "pixel smoke to Vulkan context sequence";
      }
      completed.Wait();
      return result;
    }
    return RunGpuOutputVulkanPixelSmokeOnCurrentSequence(
        std::move(source_shared_image));
  }

  std::string RunGpuOutputVulkanPixelSmokeOnCurrentSequence(
      scoped_refptr<gpu::ClientSharedImage> source_shared_image) {
    StandaloneVulkanGpuOutputPixelSmokeResult result;
    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      return StandaloneVulkanGpuOutputPixelSmokeLine(result);
    };
    auto finish_with_blocker = [&](std::string reason) {
      result.blocked = true;
      result.failure = std::move(reason);
      return StandaloneVulkanGpuOutputPixelSmokeLine(result);
    };

    if (!source_shared_image || source_shared_image->mailbox().IsZero()) {
      return finish_with_failure(
          "pixel smoke requires a held CopyOutput SharedImage source");
    }
    result.source_available = true;
    result.source_mailbox = source_shared_image->mailbox().ToDebugString();
    result.width = source_shared_image->size().width();
    result.height = source_shared_image->size().height();
    result.format = source_shared_image->format().ToString();
    if (result.width <= 0 || result.height <= 0) {
      return finish_with_failure("CopyOutput source has invalid size");
    }
    if (!use_vulkan_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "pixel smoke requires offscreen Vulkan output");
    }
    gpu::SharedImageManager* manager = GetSharedImageManager();
    if (!manager) {
      return finish_with_failure("SharedImageManager is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    result.context_available = true;

    scoped_refptr<gpu::MemoryTracker> memory_tracker =
        base::MakeRefCounted<gpu::MemoryTracker>();
    gpu::SharedImageRepresentationFactory representation_factory(
        manager, std::move(memory_tracker));
    auto read_representation = representation_factory.ProduceSkia(
        source_shared_image->mailbox(), context_state,
        gpu::SharedImageUsageSet(gpu::SHARED_IMAGE_USAGE_DISPLAY_READ));
    if (!read_representation) {
      return finish_with_failure(
          "CopyOutput source Skia representation failed");
    }
    std::vector<GrBackendSemaphore> begin_semaphores;
    std::vector<GrBackendSemaphore> end_semaphores;
    auto read_access = read_representation->BeginScopedReadAccess(
        &begin_semaphores, &end_semaphores);
    if (!begin_semaphores.empty() &&
        !context_state->gr_context()->wait(begin_semaphores.size(),
                                           begin_semaphores.data(),
                                           /*deleteSemaphoresAfterWait=*/false)) {
      return finish_with_failure(
          "CopyOutput source read semaphore wait failed");
    }
    if (!read_access) {
      return finish_with_failure("CopyOutput source read access failed");
    }
    sk_sp<SkImage> image = read_access->CreateSkImage(context_state.get());
    if (!image) {
      return finish_with_failure("CopyOutput source image creation failed");
    }

    const SkImageInfo readback_info =
        SkImageInfo::MakeN32Premul(result.width, result.height);
    std::vector<uint32_t> readback_pixels(
        static_cast<size_t>(result.width) * static_cast<size_t>(result.height));
    const size_t row_bytes =
        static_cast<size_t>(result.width) * sizeof(uint32_t);
    if (!image->readPixels(context_state->gr_context(), readback_info,
                           readback_pixels.data(), row_bytes, 0, 0)) {
      return finish_with_failure("CopyOutput source readback failed");
    }
    SkPixmap pixmap(readback_info, readback_pixels.data(), row_bytes);
    for (uint32_t pixel : readback_pixels) {
      if (SkColorGetA(pixel) != 0) {
        ++result.nontransparent_pixels;
      }
    }
    const SkColor expected_background = SkColorSetARGB(255, 0x12, 0x34, 0x56);
    const SkColor expected_box = SkColorSetARGB(255, 0xd0, 0x63, 0x29);
    const SkColor observed_background = pixmap.getColor(4, 4);
    const SkColor observed_box =
        pixmap.getColor(std::min(result.width - 1, 24),
                        std::min(result.height - 1, 24));
    result.observed_background = StandaloneFormatColor(observed_background);
    result.observed_box = StandaloneFormatColor(observed_box);
    if (result.nontransparent_pixels == 0) {
      return finish_with_blocker(
          "offscreen Vulkan CopyOutput source SharedImage is transparent");
    }
    if (!StandaloneColorClose(observed_background, expected_background) ||
        !StandaloneColorClose(observed_box, expected_box)) {
      return finish_with_failure(
          "offscreen Vulkan CopyOutput pixel verification failed");
    }
    result.readback_verified = true;
    return StandaloneVulkanGpuOutputPixelSmokeLine(result);
  }

  std::string RunBorrowedVkImageRenderCopySmokeOnCurrentSequence(
      scoped_refptr<gpu::ClientSharedImage> source_shared_image) {
    StandaloneBorrowedVkImageRenderCopySmokeResult result;
    std::unique_ptr<gpu::VulkanImage> target_image;
    scoped_refptr<gpu::MemoryTracker> registration_memory_tracker;
    std::unique_ptr<gpu::MemoryTypeTracker> registration_memory_type_tracker;
    std::unique_ptr<gpu::SharedImageRepresentationFactoryRef> factory_ref;

    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      if (factory_ref) {
        factory_ref.reset();
        result.backing_released = true;
      }
      registration_memory_type_tracker.reset();
      registration_memory_tracker.reset();
      if (target_image) {
        target_image->Destroy();
        result.target_destroyed = true;
      }
      return StandaloneBorrowedVkImageRenderCopySmokeLine(result);
    };

    if (!source_shared_image || source_shared_image->mailbox().IsZero()) {
      return finish_with_failure(
          "render-copy smoke requires a held CopyOutput SharedImage source");
    }
    result.source_available = true;
    result.source_mailbox = source_shared_image->mailbox().ToDebugString();
    result.width = source_shared_image->size().width();
    result.height = source_shared_image->size().height();
    result.format = source_shared_image->format().ToString();
    if (result.width <= 0 || result.height <= 0) {
      return finish_with_failure("CopyOutput source has invalid size");
    }
    if (!use_vulkan_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "render-copy smoke requires offscreen Vulkan output");
    }
    gpu::SharedImageManager* manager = GetSharedImageManager();
    if (!manager) {
      return finish_with_failure("SharedImageManager is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    viz::VulkanContextProvider* vulkan_provider =
        context_state->vk_context_provider();
    gpu::VulkanDeviceQueue* device_queue = vulkan_provider->GetDeviceQueue();
    if (!device_queue) {
      return finish_with_failure("Vulkan context provider has no device queue");
    }
    result.context_available = true;

    const gfx::Size target_size(result.width, result.height);
    target_image = gpu::VulkanImage::Create(
        device_queue, target_size, VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
            VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    if (!target_image || target_image->image() == VK_NULL_HANDLE) {
      return finish_with_failure("stand-in target VkImage creation failed");
    }
    result.target_created = true;

    const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
    const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
    const GrVkImageInfo vk_image_info =
        gpu::CreateGrVkImageInfo(target_image.get(), format, color_space);
    const GrBackendTexture backend_texture =
        GrBackendTextures::MakeVk(result.width, result.height, vk_image_info);
    if (!backend_texture.isValid()) {
      return finish_with_failure("Skia backend texture wrapping failed");
    }
    result.backend_texture_valid = true;

    const gpu::Mailbox target_mailbox = gpu::Mailbox::Generate();
    const gpu::SharedImageUsageSet usage =
        gpu::SHARED_IMAGE_USAGE_DISPLAY_READ |
        gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE;
    gpu::SharedImageInfo si_info(format, target_size, color_space,
                                 kTopLeft_GrSurfaceOrigin,
                                 kPremul_SkAlphaType, usage,
                                 "StandaloneBorrowedVkImageRenderCopySmoke");
    registration_memory_tracker = base::MakeRefCounted<gpu::MemoryTracker>();
    registration_memory_type_tracker =
        std::make_unique<gpu::MemoryTypeTracker>(registration_memory_tracker);
    factory_ref = manager->Register(
        std::make_unique<StandaloneBorrowedVkImageBacking>(
            target_mailbox, si_info, context_state, backend_texture),
        registration_memory_type_tracker.get());
    if (!factory_ref) {
      return finish_with_failure("borrowed VkImage backing registration failed");
    }
    result.registered = true;

    scoped_refptr<gpu::MemoryTracker> copy_memory_tracker =
        base::MakeRefCounted<gpu::MemoryTracker>();
    gpu::SharedImageRepresentationFactory representation_factory(
        manager, std::move(copy_memory_tracker));
    gpu::CopySharedImageHelper copy_helper(&representation_factory,
                                           context_state.get());
    {
      auto source_read_representation = representation_factory.ProduceSkia(
          source_shared_image->mailbox(), context_state);
      if (!source_read_representation) {
        return finish_with_failure(
            "render-copy source Skia representation failed");
      }
      std::vector<GrBackendSemaphore> source_begin_semaphores;
      std::vector<GrBackendSemaphore> source_end_semaphores;
      auto source_read_access =
          source_read_representation->BeginScopedReadAccess(
              &source_begin_semaphores, &source_end_semaphores);
      if (!source_begin_semaphores.empty() &&
          !context_state->gr_context()->wait(
              source_begin_semaphores.size(), source_begin_semaphores.data(),
              /*deleteSemaphoresAfterWait=*/false)) {
        return finish_with_failure(
            "render-copy source read semaphore wait failed");
      }
      if (!source_read_access) {
        return finish_with_failure("render-copy source read access failed");
      }
      sk_sp<SkImage> source_image =
          source_read_access->CreateSkImage(context_state.get());
      if (!source_image) {
        return finish_with_failure("render-copy source image creation failed");
      }
      const SkImageInfo source_readback_info =
          SkImageInfo::MakeN32Premul(result.width, result.height);
      std::vector<uint32_t> source_readback_pixels(
          static_cast<size_t>(result.width) *
          static_cast<size_t>(result.height));
      const size_t source_row_bytes =
          static_cast<size_t>(result.width) * sizeof(uint32_t);
      if (!source_image->readPixels(context_state->gr_context(),
                                    source_readback_info,
                                    source_readback_pixels.data(),
                                    source_row_bytes, 0, 0)) {
        return finish_with_failure("render-copy source readback failed");
      }
      SkPixmap source_pixmap(source_readback_info,
                             source_readback_pixels.data(), source_row_bytes);
      result.source_background =
          StandaloneFormatColor(source_pixmap.getColor(4, 4));
      result.source_box = StandaloneFormatColor(source_pixmap.getColor(
          std::min(result.width - 1, 24), std::min(result.height - 1, 24)));
    }
    std::array<gpu::Mailbox, 2> mailboxes = {
        source_shared_image->mailbox(), target_mailbox};
    auto copy_result = copy_helper.CopySharedImage(
        /*xoffset=*/0, /*yoffset=*/0, /*x=*/0, /*y=*/0,
        static_cast<GLsizei>(result.width),
        static_cast<GLsizei>(result.height),
        static_cast<GLsizei>(result.width),
        static_cast<GLsizei>(result.height),
        reinterpret_cast<const volatile GLbyte*>(mailboxes.data()));
    if (!copy_result.has_value()) {
      const gpu::CopySharedImageHelper::GLError& error = copy_result.error();
      return finish_with_failure(error.function_name + ": " + error.msg);
    }
    result.service_copy = true;

    auto read_representation = representation_factory.ProduceSkia(
        target_mailbox, context_state,
        gpu::SharedImageUsageSet(gpu::SHARED_IMAGE_USAGE_DISPLAY_READ));
    if (!read_representation) {
      return finish_with_failure(
          "borrowed VkImage Skia read representation failed");
    }
    std::vector<GrBackendSemaphore> read_begin_semaphores;
    std::vector<GrBackendSemaphore> read_end_semaphores;
    auto read_access = read_representation->BeginScopedReadAccess(
        &read_begin_semaphores, &read_end_semaphores);
    if (!read_access) {
      return finish_with_failure("borrowed VkImage Skia read access failed");
    }
    if (!read_begin_semaphores.empty() &&
        !context_state->gr_context()->wait(read_begin_semaphores.size(),
                                           read_begin_semaphores.data(),
                                           /*deleteSemaphoresAfterWait=*/false)) {
      return finish_with_failure("borrowed VkImage read semaphore wait failed");
    }
    sk_sp<SkImage> image = read_access->CreateSkImage(context_state.get());
    if (!image) {
      return finish_with_failure("borrowed VkImage readback image creation failed");
    }

    const SkImageInfo readback_info =
        SkImageInfo::MakeN32Premul(result.width, result.height);
    std::vector<uint32_t> readback_pixels(
        static_cast<size_t>(result.width) * static_cast<size_t>(result.height));
    const size_t row_bytes =
        static_cast<size_t>(result.width) * sizeof(uint32_t);
    if (!image->readPixels(context_state->gr_context(), readback_info,
                           readback_pixels.data(), row_bytes, 0, 0)) {
      return finish_with_failure("borrowed VkImage render-copy readback failed");
    }
    SkPixmap pixmap(readback_info, readback_pixels.data(), row_bytes);
    for (uint32_t pixel : readback_pixels) {
      if (SkColorGetA(pixel) != 0) {
        ++result.nontransparent_pixels;
      }
    }
    const SkColor expected_background = SkColorSetARGB(255, 0x12, 0x34, 0x56);
    const SkColor expected_box = SkColorSetARGB(255, 0xd0, 0x63, 0x29);
    const SkColor observed_background = pixmap.getColor(4, 4);
    const SkColor observed_box =
        pixmap.getColor(std::min(result.width - 1, 24),
                        std::min(result.height - 1, 24));
    result.observed_background = StandaloneFormatColor(observed_background);
    result.observed_box = StandaloneFormatColor(observed_box);
    if (!StandaloneColorClose(observed_background, expected_background) ||
        !StandaloneColorClose(observed_box, expected_box)) {
      return finish_with_failure("rendered HTML pixel verification failed");
    }
    result.readback_verified = true;

    read_access.reset();
    read_representation.reset();
    factory_ref.reset();
    result.backing_released = true;
    registration_memory_type_tracker.reset();
    registration_memory_tracker.reset();
    target_image->Destroy();
    result.target_destroyed = true;
    target_image.reset();
    return StandaloneBorrowedVkImageRenderCopySmokeLine(result);
  }

  std::string PrepareBorrowedVkImageRenderCopyBlitTargetForTesting(
      const gfx::Size& target_size,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
    return PrepareBorrowedVkImageRenderCopyBlitTargetForTesting(
        target_size, nullptr, nullptr, target_shared_image);
  }

  std::string PrepareBorrowedVkImageRenderCopyBlitTargetForTesting(
      const gfx::Size& target_size,
      gpu::VulkanImage* external_image,
      const html_css_renderer::ExternalVulkanImageTarget* external_target,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      scoped_refptr<gpu::ClientSharedImage> shared_image;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 const gfx::Size& target_size,
                 uintptr_t external_image,
                 uintptr_t external_target,
                 scoped_refptr<gpu::ClientSharedImage>* shared_image,
                 std::string* result, base::WaitableEvent* completed) {
                *result =
                    self
                        ->PrepareBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(
                            target_size,
                            reinterpret_cast<gpu::VulkanImage*>(
                                external_image),
                            reinterpret_cast<const html_css_renderer::
                                                 ExternalVulkanImageTarget*>(
                                external_target),
                            shared_image);
                completed->Signal();
              },
              base::Unretained(this), target_size,
              reinterpret_cast<uintptr_t>(external_image),
              reinterpret_cast<uintptr_t>(external_target), &shared_image,
              &result, &completed));
      if (!posted) {
        return "gpu_borrowed_vkimage_render_copy_smoke: failed "
               "failure=failed to post borrowed blit target setup to "
               "Vulkan context sequence path=viz_blit_request "
               "viz_blit_request=1";
      }
      completed.Wait();
      if (result.empty() && target_shared_image) {
        *target_shared_image = std::move(shared_image);
      }
      return result;
    }
    return PrepareBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(
        target_size, external_image, external_target, target_shared_image);
  }

  std::string VerifyBorrowedVkImageRenderCopyBlitTargetForTesting() {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 std::string* result, base::WaitableEvent* completed) {
                *result = self
                              ->VerifyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
                completed->Signal();
              },
              base::Unretained(this), &result, &completed));
      if (!posted) {
        return "gpu_borrowed_vkimage_render_copy_smoke: failed "
               "failure=failed to post borrowed blit target verification to "
               "Vulkan context sequence path=viz_blit_request "
               "viz_blit_request=1";
      }
      completed.Wait();
      return result;
    }
    return VerifyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
  }

  void DiscardBorrowedVkImageRenderCopyBlitTargetForTesting() {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      if (task_runner->PostTask(
              FROM_HERE,
              base::BindOnce(
                  [](StandaloneSkiaOutputSurfaceDependency* self,
                     base::WaitableEvent* completed) {
                    self->DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
                    completed->Signal();
                  },
                  base::Unretained(this), &completed))) {
        completed.Wait();
      }
      return;
    }
    DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
  }

  void WaitForBorrowedVkImageRenderCopyBlitTargetForTesting() {
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      if (task_runner->PostTask(
              FROM_HERE,
              base::BindOnce(
                  [](StandaloneSkiaOutputSurfaceDependency* self,
                     base::WaitableEvent* completed) {
                    self->WaitForBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
                    completed->Signal();
                  },
                  base::Unretained(this), &completed))) {
        completed.Wait();
      }
      return;
    }
    WaitForBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
  }

  std::string PrepareBorrowedD3D12RenderCopyBlitTargetForTesting(
      const gfx::Size& target_size,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
    return PrepareBorrowedD3D12RenderCopyBlitTargetForTesting(
        target_size, nullptr, nullptr, target_shared_image);
  }

  std::string PrepareBorrowedD3D12RenderCopyBlitTargetForTesting(
      const gfx::Size& target_size,
      ID3D12Resource* external_resource,
      void* shared_handle,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      scoped_refptr<gpu::ClientSharedImage> shared_image;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
              base::BindOnce(
                  [](StandaloneSkiaOutputSurfaceDependency* self,
                     const gfx::Size& target_size,
                     uintptr_t external_resource,
                     uintptr_t shared_handle,
                     scoped_refptr<gpu::ClientSharedImage>* shared_image,
                     std::string* result, base::WaitableEvent* completed) {
                *result =
                    self
                        ->PrepareBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence(
                            target_size,
                            reinterpret_cast<ID3D12Resource*>(
                                external_resource),
                            reinterpret_cast<void*>(shared_handle),
                            shared_image);
                completed->Signal();
              },
              base::Unretained(this), target_size,
              reinterpret_cast<uintptr_t>(external_resource),
              reinterpret_cast<uintptr_t>(shared_handle), &shared_image, &result,
              &completed));
      if (!posted) {
        return "gpu_borrowed_d3d12_render_copy_smoke: failed "
               "failure=failed to post borrowed D3D12 blit target setup "
               "path=viz_blit_request viz_blit_request=1";
      }
      completed.Wait();
      if (result.empty() && target_shared_image) {
        *target_shared_image = std::move(shared_image);
      }
      return result;
    }
    return PrepareBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence(
        target_size, external_resource, shared_handle, target_shared_image);
#else
    StandaloneBorrowedD3D12RenderCopySmokeResult result;
    result.blocked = true;
    result.failure = "native D3D12 borrowed target requires Windows and "
                     "experimental Dawn D3D12 render support";
    return StandaloneBorrowedD3D12RenderCopySmokeLine(result);
#endif
  }

  std::string VerifyBorrowedD3D12RenderCopyBlitTargetForTesting() {
#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      std::string result;
      const bool posted = task_runner->PostTask(
          FROM_HERE,
          base::BindOnce(
              [](StandaloneSkiaOutputSurfaceDependency* self,
                 std::string* result, base::WaitableEvent* completed) {
                *result = self
                              ->VerifyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence();
                completed->Signal();
              },
              base::Unretained(this), &result, &completed));
      if (!posted) {
        return "gpu_borrowed_d3d12_render_copy_smoke: failed "
               "failure=failed to post borrowed D3D12 target verification "
               "path=viz_blit_request viz_blit_request=1";
      }
      completed.Wait();
      return result;
    }
    return VerifyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence();
#else
    StandaloneBorrowedD3D12RenderCopySmokeResult result;
    result.blocked = true;
    result.failure = "native D3D12 borrowed target requires Windows and "
                     "experimental Dawn D3D12 render support";
    return StandaloneBorrowedD3D12RenderCopySmokeLine(result);
#endif
  }

  void DiscardBorrowedD3D12RenderCopyBlitTargetForTesting() {
#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
    if (scoped_refptr<base::SingleThreadTaskRunner> task_runner =
            GpuTaskRunnerIfOffSequenceForTesting()) {
      base::WaitableEvent completed(
          base::WaitableEvent::ResetPolicy::MANUAL,
          base::WaitableEvent::InitialState::NOT_SIGNALED);
      if (task_runner->PostTask(
              FROM_HERE,
              base::BindOnce(
                  [](StandaloneSkiaOutputSurfaceDependency* self,
                     base::WaitableEvent* completed) {
                    self
                        ->DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence();
                    completed->Signal();
                  },
                  base::Unretained(this), &completed))) {
        completed.Wait();
      }
      return;
    }
    DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence();
#endif
  }

 private:
  struct BorrowedVkImageRenderCopyBlitTarget {
    gfx::Size size;
    std::string format = "RGBA_8888";
    gpu::Mailbox mailbox;
    std::unique_ptr<gpu::VulkanImage> image;
    raw_ptr<gpu::VulkanImage> external_image = nullptr;
    raw_ptr<gpu::MemoryTypeTracker> registration_tracker = nullptr;
    std::unique_ptr<gpu::SharedImageRepresentationFactoryRef> factory_ref;
    scoped_refptr<gpu::ClientSharedImage> client_shared_image;
    bool target_created = false;
    bool external_resource = false;
    bool backend_texture_valid = false;
    bool registered = false;
  };

  std::string PrepareBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(
      const gfx::Size& target_size,
      gpu::VulkanImage* external_image,
      const html_css_renderer::ExternalVulkanImageTarget* external_target,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
    DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
    StandaloneBorrowedVkImageRenderCopySmokeResult result;
    result.path = "viz_blit_request";
    result.viz_blit_request = true;
    result.width = target_size.width();
    result.height = target_size.height();

    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence();
      return StandaloneBorrowedVkImageRenderCopySmokeLine(result);
    };

    if (!target_shared_image) {
      return finish_with_failure("borrowed blit target output pointer is null");
    }
    if (target_size.IsEmpty()) {
      return finish_with_failure("borrowed blit target size is empty");
    }
    if (!use_vulkan_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "borrowed blit target requires offscreen Vulkan output");
    }
    gpu::SharedImageManager* manager = GetSharedImageManager();
    if (!manager) {
      return finish_with_failure("SharedImageManager is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    viz::VulkanContextProvider* vulkan_provider =
        context_state->vk_context_provider();
    gpu::VulkanDeviceQueue* device_queue = vulkan_provider->GetDeviceQueue();
    if (!device_queue) {
      return finish_with_failure("Vulkan context provider has no device queue");
    }
    result.context_available = true;

    auto target = std::make_unique<BorrowedVkImageRenderCopyBlitTarget>();
    target->size = target_size;
    gpu::VulkanImage* target_image = external_image;
    if (external_target) {
      if (!external_target->vk_image || !external_target->vk_device_memory ||
          external_target->width != target_size.width() ||
          external_target->height != target_size.height() ||
          external_target->vk_format != VK_FORMAT_R8G8B8A8_UNORM ||
          external_target->allocation_size == 0) {
        return finish_with_failure(
            "raw external Vulkan target metadata is incomplete or does not "
            "match the active renderer size/format");
      }
      target->image = gpu::VulkanImage::CreateBorrowed(
          device_queue, static_cast<VkImage>(external_target->vk_image),
          static_cast<VkDeviceMemory>(external_target->vk_device_memory),
          target_size, static_cast<VkFormat>(external_target->vk_format),
          static_cast<VkImageTiling>(external_target->image_tiling),
          static_cast<VkDeviceSize>(external_target->allocation_size),
          external_target->memory_type_index,
          static_cast<VkImageUsageFlags>(external_target->image_usage_flags),
          static_cast<VkImageCreateFlags>(external_target->image_create_flags),
          external_target->queue_family_index);
      target_image = target->image.get();
      if (!target_image || target_image->image() == VK_NULL_HANDLE) {
        return finish_with_failure(
            "raw external Vulkan target wrapper creation failed");
      }
      target->external_resource = true;
    } else if (external_image) {
      if (external_image->image() == VK_NULL_HANDLE ||
          !external_image->device_queue() ||
          external_image->device_queue()->GetVulkanDevice() !=
              device_queue->GetVulkanDevice() ||
          external_image->size() != target_size ||
          external_image->format() != VK_FORMAT_R8G8B8A8_UNORM) {
        return finish_with_failure(
            "borrowed external Vulkan target metadata does not match the "
            "active renderer Vulkan device/size/format");
      }
      target->external_image = external_image;
      target->external_resource = true;
    } else {
      target->image = gpu::VulkanImage::Create(
          device_queue, target_size, VK_FORMAT_R8G8B8A8_UNORM,
          VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
              VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
              VK_IMAGE_USAGE_TRANSFER_DST_BIT);
      target_image = target->image.get();
      if (!target_image || target_image->image() == VK_NULL_HANDLE) {
        return finish_with_failure(
            "stand-in blit target VkImage creation failed");
      }
    }
    target->target_created = true;
    result.target_created = true;

    const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
    const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
    const GrVkImageInfo vk_image_info =
        gpu::CreateGrVkImageInfo(target_image, format, color_space);
    const GrBackendTexture backend_texture =
        GrBackendTextures::MakeVk(target_size.width(), target_size.height(),
                                  vk_image_info);
    if (!backend_texture.isValid()) {
      if (target->image) {
        target->image->Destroy();
      }
      return finish_with_failure("Skia backend texture wrapping failed");
    }
    target->backend_texture_valid = true;
    result.backend_texture_valid = true;

    target->mailbox = gpu::Mailbox::Generate();
    const gpu::SharedImageUsageSet usage =
        gpu::SHARED_IMAGE_USAGE_DISPLAY_READ |
        gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE;
    gpu::SharedImageInfo si_info(format, target_size, color_space,
                                 kTopLeft_GrSurfaceOrigin,
                                 kPremul_SkAlphaType, usage,
                                 "StandaloneBorrowedVkImageBlitTargetSmoke");
    target->registration_tracker = context_state->memory_type_tracker();
    target->factory_ref = manager->Register(
        std::make_unique<StandaloneBorrowedVkImageBacking>(
            target->mailbox, si_info, context_state, backend_texture),
        target->registration_tracker);
    if (!target->factory_ref) {
      if (target->image) {
        target->image->Destroy();
      }
      return finish_with_failure("borrowed blit target registration failed");
    }
    target->registered = true;
    result.registered = true;

    gpu::SharedImageMetadata metadata;
    metadata.format = format;
    metadata.size = target_size;
    metadata.color_space = color_space;
    metadata.surface_origin = kTopLeft_GrSurfaceOrigin;
    metadata.alpha_type = kPremul_SkAlphaType;
    metadata.usage = usage;
    target->client_shared_image = gpu::ClientSharedImage::CreateForTesting(
        target->mailbox, metadata, gpu::SyncToken(), /*texture_target=*/3553u,
        /*is_software=*/false);
    if (!target->client_shared_image) {
      target->factory_ref.reset();
      if (target->image) {
        target->image->Destroy();
      }
      return finish_with_failure("borrowed blit target ClientSharedImage failed");
    }

    *target_shared_image = target->client_shared_image;
    borrowed_blit_target_ = std::move(target);
    return "";
  }

  std::string VerifyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence() {
    StandaloneBorrowedVkImageRenderCopySmokeResult result;
    result.path = "viz_blit_request";
    result.viz_blit_request = true;
    if (borrowed_blit_target_) {
      result.width = borrowed_blit_target_->size.width();
      result.height = borrowed_blit_target_->size.height();
      result.format = borrowed_blit_target_->format;
      result.target_created = borrowed_blit_target_->target_created;
      result.backend_texture_valid =
          borrowed_blit_target_->backend_texture_valid;
      result.registered = borrowed_blit_target_->registered;
    }

    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(&result);
      return StandaloneBorrowedVkImageRenderCopySmokeLine(result);
    };
    auto finish_with_blocker = [&](std::string reason) {
      result.blocked = true;
      result.failure = std::move(reason);
      DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(&result);
      return StandaloneBorrowedVkImageRenderCopySmokeLine(result);
    };

    if (!borrowed_blit_target_) {
      return finish_with_failure("borrowed blit target is not prepared");
    }
    gpu::SharedImageManager* manager = GetSharedImageManager();
    if (!manager) {
      return finish_with_failure("SharedImageManager is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider() ||
        !context_state->gr_context()) {
      return finish_with_failure(
          "offscreen runtime has no Vulkan Ganesh SharedContextState");
    }
    result.context_available = true;

    auto read_representation = manager->ProduceSkia(
        borrowed_blit_target_->mailbox,
        borrowed_blit_target_->registration_tracker, context_state,
        gpu::SharedImageUsageSet(gpu::SHARED_IMAGE_USAGE_DISPLAY_READ));
    if (!read_representation) {
      return finish_with_failure(
          "borrowed blit target Skia read representation failed");
    }
    std::vector<GrBackendSemaphore> read_begin_semaphores;
    std::vector<GrBackendSemaphore> read_end_semaphores;
    auto read_access = read_representation->BeginScopedReadAccess(
        &read_begin_semaphores, &read_end_semaphores);
    if (!read_begin_semaphores.empty() &&
        !context_state->gr_context()->wait(read_begin_semaphores.size(),
                                           read_begin_semaphores.data(),
                                           /*deleteSemaphoresAfterWait=*/false)) {
      return finish_with_failure("borrowed blit target read semaphore wait failed");
    }
    if (!read_access) {
      return finish_with_failure("borrowed blit target Skia read access failed");
    }
    sk_sp<SkImage> image = read_access->CreateSkImage(context_state.get());
    if (!image) {
      return finish_with_failure("borrowed blit target image creation failed");
    }

    const SkImageInfo readback_info =
        SkImageInfo::MakeN32Premul(result.width, result.height);
    std::vector<uint32_t> readback_pixels(
        static_cast<size_t>(result.width) * static_cast<size_t>(result.height));
    const size_t row_bytes =
        static_cast<size_t>(result.width) * sizeof(uint32_t);
    if (!image->readPixels(context_state->gr_context(), readback_info,
                           readback_pixels.data(), row_bytes, 0, 0)) {
      return finish_with_failure("borrowed blit target readback failed");
    }
    SkPixmap pixmap(readback_info, readback_pixels.data(), row_bytes);
    for (uint32_t pixel : readback_pixels) {
      if (SkColorGetA(pixel) != 0) {
        ++result.nontransparent_pixels;
      }
    }
    const SkColor expected_background = SkColorSetARGB(255, 0x12, 0x34, 0x56);
    const SkColor expected_box = SkColorSetARGB(255, 0xd0, 0x63, 0x29);
    const SkColor observed_background = pixmap.getColor(4, 4);
    const SkColor observed_box =
        pixmap.getColor(std::min(result.width - 1, 24),
                        std::min(result.height - 1, 24));
    result.observed_background = StandaloneFormatColor(observed_background);
    result.observed_box = StandaloneFormatColor(observed_box);
    if (result.nontransparent_pixels == 0) {
      return finish_with_blocker(
          "offscreen Vulkan BlitRequest populated a transparent borrowed target");
    }
    if (!StandaloneColorClose(observed_background, expected_background) ||
        !StandaloneColorClose(observed_box, expected_box)) {
      return finish_with_failure("borrowed blit target pixel verification failed");
    }
    result.readback_verified = true;

    read_access.reset();
    read_representation.reset();
    context_state->gr_context()->flushAndSubmit(GrSyncCpu::kYes);
    context_state->gr_context()->performDeferredCleanup(
        std::chrono::milliseconds(0));
    if (context_state && context_state->vk_context_provider() &&
        context_state->vk_context_provider()->GetDeviceQueue()) {
      vkDeviceWaitIdle(
          context_state->vk_context_provider()->GetDeviceQueue()
              ->GetVulkanDevice());
    }
    DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(&result);
    if (context_state && context_state->vk_context_provider() &&
        context_state->vk_context_provider()->GetDeviceQueue()) {
      vkDeviceWaitIdle(
          context_state->vk_context_provider()->GetDeviceQueue()
              ->GetVulkanDevice());
    }
    return StandaloneBorrowedVkImageRenderCopySmokeLine(result);
  }

  void DestroyBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence(
      StandaloneBorrowedVkImageRenderCopySmokeResult* result = nullptr) {
    if (!borrowed_blit_target_) {
      return;
    }
    borrowed_blit_target_->client_shared_image.reset();
    if (borrowed_blit_target_->factory_ref) {
      borrowed_blit_target_->factory_ref.reset();
      if (result) {
        result->backing_released = true;
      }
    }
    if (borrowed_blit_target_->image) {
      borrowed_blit_target_->image->Destroy();
      if (result) {
        result->target_destroyed = true;
      }
    }
    borrowed_blit_target_.reset();
  }

  void WaitForBorrowedVkImageRenderCopyBlitTargetOnCurrentSequence() {
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->GrContextIsVulkan() ||
        !context_state->vk_context_provider()) {
      return;
    }
    if (context_state->gr_context()) {
      context_state->gr_context()->flushAndSubmit(GrSyncCpu::kYes);
      context_state->gr_context()->performDeferredCleanup(
          std::chrono::milliseconds(0));
    }
    gpu::VulkanDeviceQueue* device_queue =
        context_state->vk_context_provider()->GetDeviceQueue();
    if (device_queue) {
      vkDeviceWaitIdle(device_queue->GetVulkanDevice());
    }
  }

  void SetFailure(const char* reason) {
    if (failure_reason_ && reason && failure_reason_->empty()) {
      *failure_reason_ = reason;
    }
  }

  std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder_;
  gpu::SurfaceHandle surface_handle_ = gpu::kNullSurfaceHandle;
  raw_ptr<std::string> failure_reason_ = nullptr;
  bool use_vulkan_offscreen_ = false;
  bool use_d3d12_offscreen_ = false;
  gpu::GpuPreferences vulkan_gpu_preferences_;
  gpu::GpuPreferences d3d12_gpu_preferences_;
  raw_ptr<bool> vulkan_context_provider_available_ = nullptr;
  raw_ptr<bool> shared_context_state_is_vulkan_ = nullptr;
  scoped_refptr<base::SingleThreadTaskRunner> client_task_runner_;
  std::unique_ptr<BorrowedVkImageRenderCopyBlitTarget>
      borrowed_blit_target_;

#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  struct BorrowedD3D12RenderCopyBlitTarget {
    gfx::Size size;
    std::string format = "RGBA_8888";
    gpu::Mailbox mailbox;
    Microsoft::WRL::ComPtr<ID3D12Resource> resource;
    raw_ptr<StandaloneBorrowedD3D12TextureBacking> backing = nullptr;
    raw_ptr<gpu::MemoryTypeTracker> registration_tracker = nullptr;
    std::unique_ptr<gpu::SharedImageRepresentationFactoryRef> factory_ref;
    scoped_refptr<gpu::ClientSharedImage> client_shared_image;
    bool target_created = false;
    bool external_resource = false;
    bool shared_texture_memory_created = false;
    bool registered = false;
  };

  std::string PrepareBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence(
      const gfx::Size& target_size,
      ID3D12Resource* external_resource,
      void* shared_handle,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
    DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence();
    StandaloneBorrowedD3D12RenderCopySmokeResult result;
    result.viz_blit_request = true;
    result.width = target_size.width();
    result.height = target_size.height();

    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence();
      return StandaloneBorrowedD3D12RenderCopySmokeLine(result);
    };

    if (!target_shared_image) {
      return finish_with_failure("borrowed D3D12 target output pointer is null");
    }
    if (target_size.IsEmpty()) {
      return finish_with_failure("borrowed D3D12 target size is empty");
    }
    if (!use_d3d12_offscreen_ || !IsOffscreen()) {
      return finish_with_failure(
          "borrowed D3D12 target requires offscreen D3D12 output");
    }
    gpu::SharedImageManager* manager = GetSharedImageManager();
    if (!manager) {
      return finish_with_failure("SharedImageManager is unavailable");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->IsGraphiteDawnD3D() ||
        !context_state->dawn_context_provider()) {
      return finish_with_failure(
          "offscreen runtime has no D3D12 Graphite/Dawn SharedContextState");
    }
    if (context_state->dawn_context_provider()->backend_type() !=
        wgpu::BackendType::D3D12) {
      return finish_with_failure("Dawn context provider is not D3D12");
    }
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue =
        context_state->dawn_context_provider()->GetD3D12CommandQueue();
    if (!queue) {
      return finish_with_failure("Dawn D3D12 command queue is unavailable");
    }
    Microsoft::WRL::ComPtr<ID3D12Device> device;
    if (FAILED(queue->GetDevice(IID_PPV_ARGS(&device))) || !device) {
      return finish_with_failure("Dawn D3D12 device is unavailable");
    }
    result.context_available = true;

    D3D12_RESOURCE_DESC resource_desc = {};
    auto target = std::make_unique<BorrowedD3D12RenderCopyBlitTarget>();
    target->size = target_size;
    Microsoft::WRL::ComPtr<ID3D12Resource> opened_shared_resource;
    Microsoft::WRL::ComPtr<IUnknown> external_resource_identity =
        D3D12ResourceIdentity(external_resource);
    bool can_use_external_resource_directly = false;
    Microsoft::WRL::ComPtr<ID3D12Device> external_resource_device;
    if (external_resource) {
      can_use_external_resource_directly =
          SUCCEEDED(external_resource->GetDevice(
              IID_PPV_ARGS(&external_resource_device))) &&
          external_resource_device &&
          SameD3D12Device(external_resource_device.Get(), device.Get());
    }
    if (shared_handle && !can_use_external_resource_directly) {
      const bool cache_handle_hit =
          shared_handle == cached_external_d3d12_shared_handle_;
      const bool cache_resource_hit =
          external_resource &&
          external_resource == cached_external_d3d12_resource_hint_;
      const bool cache_resource_identity_hit =
          external_resource_identity &&
          cached_external_d3d12_resource_identity_ &&
          external_resource_identity.Get() ==
              cached_external_d3d12_resource_identity_.Get();
      if ((cache_handle_hit || cache_resource_hit ||
           cache_resource_identity_hit) &&
          cached_external_d3d12_opened_resource_) {
        opened_shared_resource = cached_external_d3d12_opened_resource_;
      } else {
        HRESULT hr = device->OpenSharedHandle(
            static_cast<HANDLE>(shared_handle),
            IID_PPV_ARGS(&opened_shared_resource));
        if (FAILED(hr) || !opened_shared_resource) {
          std::ostringstream failure;
          failure << "borrowed external D3D12 shared handle open failed hr="
                  << HResultHex(hr)
                  << " cache_handle_hit=" << (cache_handle_hit ? 1 : 0)
                  << " cache_resource_hit=" << (cache_resource_hit ? 1 : 0)
                  << " cache_resource_identity_hit="
                  << (cache_resource_identity_hit ? 1 : 0)
                  << " has_resource=" << (external_resource ? 1 : 0)
                  << " resource_ptr=" << PointerHex(external_resource)
                  << " cached_resource_ptr="
                  << PointerHex(cached_external_d3d12_resource_hint_.get())
                  << " resource_identity="
                  << PointerHex(external_resource_identity.Get())
                  << " cached_resource_identity="
                  << PointerHex(cached_external_d3d12_resource_identity_.Get())
                  << " direct_resource_compatible="
                  << (can_use_external_resource_directly ? 1 : 0)
                  << " active_device_luid="
                  << D3D12DeviceLuidString(device.Get())
                  << " resource_device_luid="
                  << D3D12DeviceLuidString(external_resource_device.Get());
          return finish_with_failure(failure.str());
        }
        cached_external_d3d12_shared_handle_ = shared_handle;
        cached_external_d3d12_resource_hint_ = external_resource;
        cached_external_d3d12_resource_identity_ = external_resource_identity;
        cached_external_d3d12_opened_resource_ = opened_shared_resource;
      }
      external_resource = opened_shared_resource.Get();
    }
    if (external_resource) {
      resource_desc = external_resource->GetDesc();
      if (resource_desc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D ||
          resource_desc.Width != static_cast<UINT64>(target_size.width()) ||
          resource_desc.Height != static_cast<UINT>(target_size.height()) ||
          resource_desc.Format != DXGI_FORMAT_R8G8B8A8_UNORM) {
        return finish_with_failure(
            "borrowed external D3D12 target resource metadata mismatch");
      }
      Microsoft::WRL::ComPtr<ID3D12Device> resource_device;
      if (!shared_handle) {
        if (FAILED(external_resource->GetDevice(
                IID_PPV_ARGS(&resource_device))) ||
            !resource_device ||
            !SameD3D12Device(resource_device.Get(), device.Get())) {
          return finish_with_failure(
              "borrowed external D3D12 target is not owned by the active "
              "renderer D3D12 device");
        }
      }
      target->resource =
          opened_shared_resource ? opened_shared_resource : external_resource;
      target->external_resource = true;
      if (!opened_shared_resource && can_use_external_resource_directly) {
        cached_external_d3d12_shared_handle_ = shared_handle;
        cached_external_d3d12_resource_hint_ = external_resource;
        cached_external_d3d12_resource_identity_ = external_resource_identity;
        cached_external_d3d12_opened_resource_ = external_resource;
      }
    } else {
      D3D12_HEAP_PROPERTIES heap_properties = {};
      heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
      heap_properties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
      heap_properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
      heap_properties.CreationNodeMask = 1;
      heap_properties.VisibleNodeMask = 1;

      resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
      resource_desc.Alignment = 0;
      resource_desc.Width = static_cast<UINT64>(target_size.width());
      resource_desc.Height = static_cast<UINT>(target_size.height());
      resource_desc.DepthOrArraySize = 1;
      resource_desc.MipLevels = 1;
      resource_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      resource_desc.SampleDesc.Count = 1;
      resource_desc.SampleDesc.Quality = 0;
      resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
      resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET |
                            D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;

      HRESULT hr = device->CreateCommittedResource(
          &heap_properties, D3D12_HEAP_FLAG_NONE, &resource_desc,
          D3D12_RESOURCE_STATE_COMMON, nullptr,
          IID_PPV_ARGS(&target->resource));
      if (FAILED(hr) || !target->resource) {
        return finish_with_failure(
            "stand-in D3D12 target resource creation failed");
      }
    }
    target->target_created = true;
    result.target_created = true;

    const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
    const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
    const gpu::SharedImageUsageSet usage =
        gpu::SHARED_IMAGE_USAGE_DISPLAY_READ |
        gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE;
    gpu::SharedImageInfo si_info(format, target_size, color_space,
                                 kTopLeft_GrSurfaceOrigin,
                                 kPremul_SkAlphaType, usage,
                                 "StandaloneBorrowedD3D12BlitTargetSmoke");
    target->mailbox = gpu::Mailbox::Generate();
    target->registration_tracker = context_state->memory_type_tracker();
    auto backing = std::make_unique<StandaloneBorrowedD3D12TextureBacking>(
        target->mailbox, si_info, context_state, target->resource);
    target->backing = backing.get();
    target->factory_ref =
        manager->Register(std::move(backing), target->registration_tracker);
    if (!target->factory_ref) {
      return finish_with_failure("borrowed D3D12 target registration failed");
    }
    target->registered = true;
    result.registered = true;

    gpu::SharedImageMetadata metadata;
    metadata.format = format;
    metadata.size = target_size;
    metadata.color_space = color_space;
    metadata.surface_origin = kTopLeft_GrSurfaceOrigin;
    metadata.alpha_type = kPremul_SkAlphaType;
    metadata.usage = usage;
    target->client_shared_image = gpu::ClientSharedImage::CreateForTesting(
        target->mailbox, metadata, gpu::SyncToken(), /*texture_target=*/3553u,
        /*is_software=*/false);
    if (!target->client_shared_image) {
      return finish_with_failure(
          "borrowed D3D12 target ClientSharedImage failed");
    }

    *target_shared_image = target->client_shared_image;
    borrowed_d3d12_blit_target_ = std::move(target);
    return "";
  }

  std::string VerifyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence() {
    StandaloneBorrowedD3D12RenderCopySmokeResult result;
    result.viz_blit_request = true;
    if (borrowed_d3d12_blit_target_) {
      result.width = borrowed_d3d12_blit_target_->size.width();
      result.height = borrowed_d3d12_blit_target_->size.height();
      result.format = borrowed_d3d12_blit_target_->format;
      result.target_created = borrowed_d3d12_blit_target_->target_created;
      result.registered = borrowed_d3d12_blit_target_->registered;
      result.shared_texture_memory =
          borrowed_d3d12_blit_target_->backing &&
          borrowed_d3d12_blit_target_->backing
              ->shared_texture_memory_created();
    }

    auto finish_with_failure = [&](std::string failure) {
      result.failure = std::move(failure);
      DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence(&result);
      return StandaloneBorrowedD3D12RenderCopySmokeLine(result);
    };

    if (!borrowed_d3d12_blit_target_ || !borrowed_d3d12_blit_target_->backing) {
      return finish_with_failure("borrowed D3D12 target is not prepared");
    }
    scoped_refptr<gpu::SharedContextState> context_state =
        GetSharedContextState();
    if (!context_state || !context_state->IsGraphiteDawnD3D() ||
        !context_state->dawn_context_provider()) {
      return finish_with_failure(
          "offscreen runtime has no D3D12 Graphite/Dawn SharedContextState");
    }
    result.context_available = true;

    std::vector<uint32_t> readback_pixels;
    if (!borrowed_d3d12_blit_target_->backing->ReadbackToPixels(
            &readback_pixels)) {
      return finish_with_failure("borrowed D3D12 target readback failed");
    }
    const int width = result.width;
    const int height = result.height;
    if (width <= 0 || height <= 0 ||
        readback_pixels.size() !=
            static_cast<size_t>(width) * static_cast<size_t>(height)) {
      return finish_with_failure("borrowed D3D12 readback dimensions invalid");
    }
    for (uint32_t pixel : readback_pixels) {
      if (SkColorGetA(pixel) != 0) {
        ++result.nontransparent_pixels;
      }
    }
    auto pixel_at = [&](int x, int y) {
      return readback_pixels[static_cast<size_t>(y) *
                                 static_cast<size_t>(width) +
                             static_cast<size_t>(x)];
    };
    const SkColor expected_background = SkColorSetARGB(255, 0x12, 0x34, 0x56);
    const SkColor expected_box = SkColorSetARGB(255, 0xd0, 0x63, 0x29);
    const SkColor observed_background = pixel_at(4, 4);
    const SkColor observed_box =
        pixel_at(std::min(width - 1, 24), std::min(height - 1, 24));
    result.observed_background = StandaloneFormatColor(observed_background);
    result.observed_box = StandaloneFormatColor(observed_box);
    if (result.nontransparent_pixels == 0) {
      return finish_with_failure(
          "offscreen D3D12 BlitRequest populated a transparent target");
    }
    if (!StandaloneColorClose(observed_background, expected_background) ||
        !StandaloneColorClose(observed_box, expected_box)) {
      return finish_with_failure(
          "borrowed D3D12 target pixel verification failed");
    }
    result.readback_verified = true;
    result.shared_texture_memory =
        borrowed_d3d12_blit_target_->backing->shared_texture_memory_created();
    DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence(&result);
    return StandaloneBorrowedD3D12RenderCopySmokeLine(result);
  }

  void DestroyBorrowedD3D12RenderCopyBlitTargetOnCurrentSequence(
      StandaloneBorrowedD3D12RenderCopySmokeResult* result = nullptr) {
    if (!borrowed_d3d12_blit_target_) {
      return;
    }
    borrowed_d3d12_blit_target_->client_shared_image.reset();
    borrowed_d3d12_blit_target_->backing = nullptr;
    if (borrowed_d3d12_blit_target_->factory_ref) {
      borrowed_d3d12_blit_target_->factory_ref.reset();
      if (result) {
        result->backing_released = true;
      }
    }
    if (borrowed_d3d12_blit_target_->resource) {
      const bool external_resource =
          borrowed_d3d12_blit_target_->external_resource;
      borrowed_d3d12_blit_target_->resource.Reset();
      if (result && !external_resource) {
        result->target_destroyed = true;
      }
    }
    borrowed_d3d12_blit_target_.reset();
  }

  std::unique_ptr<BorrowedD3D12RenderCopyBlitTarget>
      borrowed_d3d12_blit_target_;
  void* cached_external_d3d12_shared_handle_ = nullptr;
  raw_ptr<ID3D12Resource> cached_external_d3d12_resource_hint_ = nullptr;
  Microsoft::WRL::ComPtr<IUnknown> cached_external_d3d12_resource_identity_;
  Microsoft::WRL::ComPtr<ID3D12Resource>
      cached_external_d3d12_opened_resource_;
#endif
};

class StandaloneInProcessRasterContextProvider final
    : public viz::RasterContextProvider,
      public base::RefCountedThreadSafe<
          StandaloneInProcessRasterContextProvider> {
 public:
  StandaloneInProcessRasterContextProvider(
      std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder,
      bool enforce_cache_controller_lock,
      bool* gpu_context_created,
      bool* raster_context_created,
      bool* shared_image_interface_available,
      std::string* failure_reason)
      : gpu_thread_holder_(std::move(gpu_thread_holder)),
        enforce_cache_controller_lock_(enforce_cache_controller_lock),
        gpu_context_created_(gpu_context_created),
        raster_context_created_(raster_context_created),
        shared_image_interface_available_(shared_image_interface_available),
        failure_reason_(failure_reason) {
    DETACH_FROM_SEQUENCE(sequence_checker_);
  }

  StandaloneInProcessRasterContextProvider(
      const StandaloneInProcessRasterContextProvider&) = delete;
  StandaloneInProcessRasterContextProvider& operator=(
      const StandaloneInProcessRasterContextProvider&) = delete;

  void AddRef() const override {
    base::RefCountedThreadSafe<
        StandaloneInProcessRasterContextProvider>::AddRef();
  }

  void Release() const override {
    base::RefCountedThreadSafe<
        StandaloneInProcessRasterContextProvider>::Release();
  }

  gpu::ContextResult BindToCurrentSequence() override {
    DCHECK_CALLED_ON_VALID_SEQUENCE(sequence_checker_);
    TraceLiveFrameProbeStage("cc raster context BindToCurrentSequence begin");
    if (bind_tried_) {
      TraceLiveFrameProbeStage("cc raster context BindToCurrentSequence cached");
      return bind_result_;
    }
    bind_tried_ = true;

    if (!gpu_thread_holder_) {
      TraceLiveFrameProbeStage("cc raster context missing gpu thread holder");
      SetFailure("missing in-process GPU thread holder");
      bind_result_ = gpu::ContextResult::kFatalFailure;
      return bind_result_;
    }

    if (gl::GetGLImplementation() == gl::kGLImplementationNone) {
      TraceLiveFrameProbeStage("cc raster context before static GL bindings");
      if (!gl::init::InitializeStaticGLBindingsOneOff()) {
        TraceLiveFrameProbeStage("cc raster context static GL bindings failed");
        SetFailure(DescribeGLInitializationFailure(
            "Chromium GL static binding initialization failed before raster "
            "context creation"));
        bind_result_ = gpu::ContextResult::kFatalFailure;
        return bind_result_;
      }
      TraceLiveFrameProbeStage("cc raster context after static GL bindings");
      if (gl::GetGLImplementation() != gl::kGLImplementationDisabled &&
          !gl::init::InitializeGLOneOffPlatformImplementation(
              /*disable_gl_drawing=*/false, /*init_extensions=*/true,
              gl::GpuPreference::kDefault)) {
        TraceLiveFrameProbeStage("cc raster context platform GL init failed");
        SetFailure(DescribeGLInitializationFailure(
            "Chromium GL display/platform initialization failed before raster "
            "context creation"));
        bind_result_ = gpu::ContextResult::kFatalFailure;
        return bind_result_;
      }
      TraceLiveFrameProbeStage("cc raster context after platform GL init");
    }

    TraceLiveFrameProbeStage("cc raster context before RasterInProcessContext");
    raster_context_ = std::make_unique<gpu::RasterInProcessContext>();
    TraceLiveFrameProbeStage("cc raster context before GetTaskExecutor");
    gpu::CommandBufferTaskExecutor* task_executor =
        gpu_thread_holder_->GetTaskExecutor();
    TraceLiveFrameProbeStage("cc raster context after GetTaskExecutor");
    if (!task_executor) {
      SetFailure("in-process GPU thread failed to create a command-buffer task "
                 "executor");
      bind_result_ = gpu::ContextResult::kFatalFailure;
      return bind_result_;
    }
    TraceLiveFrameProbeStage("cc raster context before Initialize");
    bind_result_ = raster_context_->Initialize(
        task_executor, /*gr_shader_cache=*/nullptr,
        /*use_shader_cache_shm_count=*/nullptr);
    TraceLiveFrameProbeStage("cc raster context after Initialize");
    if (bind_result_ != gpu::ContextResult::kSuccess) {
      TraceLiveFrameProbeStage("cc raster context Initialize failed");
      SetFailure("gpu::RasterInProcessContext initialization failed");
      raster_context_.reset();
      return bind_result_;
    }

    TraceLiveFrameProbeStage("cc raster context before cache controller");
    cache_controller_ = std::make_unique<viz::ContextCacheController>(
        raster_context_->GetContextSupport(),
        base::SingleThreadTaskRunner::GetCurrentDefault());
    if (enforce_cache_controller_lock_) {
      cache_controller_->SetLock(&context_lock_);
    }
    TraceLiveFrameProbeStage("cc raster context after cache controller");

    if (gpu_context_created_) {
      *gpu_context_created_ = true;
    }
    if (raster_context_created_) {
      *raster_context_created_ = true;
    }
    if (shared_image_interface_available_) {
      *shared_image_interface_available_ =
          raster_context_->GetSharedImageInterface() != nullptr;
    }
    SetFailure("");
    return bind_result_;
  }

  void AddObserver(viz::ContextLostObserver* obs) override {
    observers_.AddObserver(obs);
  }

  void RemoveObserver(viz::ContextLostObserver* obs) override {
    observers_.RemoveObserver(obs);
  }

  base::Lock* GetLock() override { return &context_lock_; }

  viz::ContextCacheController* CacheController() override {
    CHECK(cache_controller_);
    return cache_controller_.get();
  }

  gpu::ContextSupport* ContextSupport() override {
    CHECK(raster_context_);
    return raster_context_->GetContextSupport();
  }

  gpu::SharedImageInterface* SharedImageInterface() override {
    CHECK(raster_context_);
    return raster_context_->GetSharedImageInterface();
  }

  const gpu::Capabilities& ContextCapabilities() const override {
    CHECK(raster_context_);
    return raster_context_->GetCapabilities();
  }

  const gpu::GpuFeatureInfo& GetGpuFeatureInfo() const override {
    CHECK(raster_context_);
    return raster_context_->GetGpuFeatureInfo();
  }

  gpu::raster::RasterInterface* RasterInterface() override {
    CHECK(raster_context_);
    return raster_context_->GetImplementation();
  }

 private:
  friend class base::RefCountedThreadSafe<
      StandaloneInProcessRasterContextProvider>;

  ~StandaloneInProcessRasterContextProvider() override = default;

  void SetFailure(const char* reason) {
    if (failure_reason_) {
      *failure_reason_ = reason ? reason : "";
    }
  }

  void SetFailure(const std::string& reason) {
    if (failure_reason_) {
      *failure_reason_ = reason;
    }
  }

  std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder_;
  std::unique_ptr<gpu::RasterInProcessContext> raster_context_;
  std::unique_ptr<viz::ContextCacheController> cache_controller_;
  base::Lock context_lock_;
  base::ObserverList<viz::ContextLostObserver>::Unchecked observers_;
  bool enforce_cache_controller_lock_ = false;
  bool bind_tried_ = false;
  gpu::ContextResult bind_result_ = gpu::ContextResult::kSuccess;
  raw_ptr<bool> gpu_context_created_ = nullptr;
  raw_ptr<bool> raster_context_created_ = nullptr;
  raw_ptr<bool> shared_image_interface_available_ = nullptr;
  raw_ptr<std::string> failure_reason_ = nullptr;
  SEQUENCE_CHECKER(sequence_checker_);
};

class StandaloneDirectLayerTreeFrameSink final : public cc::LayerTreeFrameSink {
 public:
  StandaloneDirectLayerTreeFrameSink(
      viz::FrameSinkManagerImpl* frame_sink_manager,
      const viz::FrameSinkId& frame_sink_id,
      std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder,
      scoped_refptr<viz::RasterContextProvider> compositor_context_provider,
      scoped_refptr<viz::RasterContextProvider> worker_context_provider,
      scoped_refptr<base::SingleThreadTaskRunner> compositor_task_runner,
      const gfx::Size& viewport,
      bool* compositor_frame_submitted,
      bool* viz_display_created,
      bool* skia_gpu_reached,
      gfx::Size* submitted_output_size,
      gfx::Size* viz_display_output_size,
      bool* copy_output_requested,
      bool* copy_output_png_requested,
      bool* copy_output_raw_requested,
      bool* copy_output_gpu_requested,
      bool* copy_output_completed,
      bool* copy_output_succeeded,
      std::vector<uint8_t>* copy_output_png,
      LiveRawFrameOutput* copy_output_raw_frame,
      LiveGpuFrameOutput* copy_output_gpu_frame,
      std::string* copy_output_failure,
      std::string* failure_reason,
      bool* begin_frame_source_set = nullptr,
      int* did_not_produce_count = nullptr,
      int* last_frame_skipped_reason = nullptr,
      int* last_did_not_produce_has_damage = nullptr,
      bool async_compositor_frame_ack = false,
      bool use_vulkan_offscreen_output = false,
      bool use_d3d12_offscreen_output = false)
      : cc::LayerTreeFrameSink(std::move(compositor_context_provider),
                               std::move(worker_context_provider),
                               std::move(compositor_task_runner),
                               /*shared_image_interface=*/nullptr),
        frame_sink_manager_(frame_sink_manager),
        frame_sink_id_(frame_sink_id),
        gpu_thread_holder_(std::move(gpu_thread_holder)),
        viewport_(viewport),
        display_client_(skia_gpu_reached, failure_reason),
        compositor_frame_submitted_(compositor_frame_submitted),
        viz_display_created_(viz_display_created),
        skia_gpu_reached_(skia_gpu_reached),
        submitted_output_size_(submitted_output_size),
        viz_display_output_size_(viz_display_output_size),
        copy_output_requested_(copy_output_requested),
        copy_output_png_requested_(copy_output_png_requested),
        copy_output_raw_requested_(copy_output_raw_requested),
        copy_output_gpu_requested_(copy_output_gpu_requested),
        copy_output_completed_(copy_output_completed),
        copy_output_succeeded_(copy_output_succeeded),
        copy_output_png_(copy_output_png),
        copy_output_raw_frame_(copy_output_raw_frame),
        copy_output_gpu_frame_(copy_output_gpu_frame),
        copy_output_failure_(copy_output_failure),
        failure_reason_(failure_reason),
        begin_frame_source_set_(begin_frame_source_set),
        did_not_produce_count_(did_not_produce_count),
        last_frame_skipped_reason_(last_frame_skipped_reason),
        last_did_not_produce_has_damage_(
            last_did_not_produce_has_damage),
        use_vulkan_offscreen_output_(use_vulkan_offscreen_output),
        use_d3d12_offscreen_output_(use_d3d12_offscreen_output) {
    // Standalone screenshot/readback consumers compare CSS top-left pixel
    // coordinates. Disable Viz backing/output-surface padding that is useful
    // for production buffer reuse but changes observable CopyOutput bounds.
    renderer_settings_.dont_round_texture_sizes_for_pixel_tests = true;
    renderer_settings_.requires_alpha_channel = true;
    viz_client_.SetAsyncCompositorFrameAck(async_compositor_frame_ack);
  }

  StandaloneDirectLayerTreeFrameSink(
      const StandaloneDirectLayerTreeFrameSink&) = delete;
  StandaloneDirectLayerTreeFrameSink& operator=(
      const StandaloneDirectLayerTreeFrameSink&) = delete;

  ~StandaloneDirectLayerTreeFrameSink() override {
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
  }

  bool BindToClient(cc::LayerTreeFrameSinkClient* client) override {
    TraceLiveFrameProbeStage("direct frame sink BindToClient begin");
    if (!cc::LayerTreeFrameSink::BindToClient(client)) {
      TraceLiveFrameProbeStage("direct frame sink base BindToClient failed");
      if (!failure_reason_ || failure_reason_->empty()) {
        SetFailure("cc::LayerTreeFrameSink rejected the cc client");
      }
      return false;
    }
    TraceLiveFrameProbeStage("direct frame sink after base BindToClient");
    begin_frame_source_ = std::make_unique<viz::BackToBackBeginFrameSource>(
        std::make_unique<viz::DelayBasedTimeSource>(
            compositor_task_runner_.get()));
    client->SetBeginFrameSource(begin_frame_source_.get());
    if (begin_frame_source_set_) {
      *begin_frame_source_set_ = true;
    }
    viz_client_.SetCcClient(client);
    TraceLiveFrameProbeStage("direct frame sink before support create");
    support_ = std::make_unique<viz::CompositorFrameSinkSupport>(
        &viz_client_, frame_sink_manager_, frame_sink_id_, /*is_root=*/true);
    TraceLiveFrameProbeStage("direct frame sink after support create");
    return true;
  }

  void DetachFromClient() override {
    if (client_) {
      client_->SetBeginFrameSource(nullptr);
    }
    begin_frame_source_.reset();
    if (begin_frame_source_set_) {
      *begin_frame_source_set_ = false;
    }
    viz_client_.SetCcClient(nullptr);
    support_.reset();
    cc::LayerTreeFrameSink::DetachFromClient();
  }

  void SetLocalSurfaceId(
      const viz::LocalSurfaceId& local_surface_id) override {
    TraceLiveFrameProbeStage("direct frame sink SetLocalSurfaceId");
    local_surface_id_ = local_surface_id;
  }

  void SubmitCompositorFrame(viz::CompositorFrame frame,
                             bool hit_test_data_changed) override {
    TraceLiveFrameProbeStage("direct frame sink SubmitCompositorFrame begin");
    if (std::getenv("HTML_CSS_RENDERER_DUMP_CC_FRAME")) {
      const std::string frame_json = frame.ToString();
      std::fprintf(stderr, "standalone_cc_frame=%s\n", frame_json.c_str());
      std::fflush(stderr);
    }
    if (!support_) {
      SetFailure("Viz CompositorFrameSinkSupport is not initialized");
      return;
    }
    if (!local_surface_id_.is_valid()) {
      SetFailure("cc submitted a frame before setting a valid LocalSurfaceId");
      return;
    }
    std::optional<viz::HitTestRegionList> hit_test_region_list;
    if (client_) {
      hit_test_region_list = client_->BuildHitTestData();
    }
    const float device_scale_factor = frame.device_scale_factor();
    last_submitted_device_scale_factor_ = device_scale_factor;
    gfx::Size output_size = viewport_;
    if (!frame.render_pass_list.empty()) {
      output_size = frame.render_pass_list.back()->output_rect.size();
    }
    if (submitted_output_size_) {
      *submitted_output_size_ = output_size;
    }
    const bool should_copy_output =
        copy_output_requested_ && *copy_output_requested_;
    const bool needs_display =
        g_standalone_native_window_handle || should_copy_output;
    if (needs_display && EnsureVizDisplay(output_size)) {
      display_->SetLocalSurfaceId(local_surface_id_, device_scale_factor);
      display_->Resize(output_size);
      if (viz_display_output_size_) {
        *viz_display_output_size_ = output_size;
      }
    }
    const viz::SubmitResult result = support_->MaybeSubmitCompositorFrame(
        local_surface_id_, std::move(frame), std::move(hit_test_region_list),
        /*submit_time=*/0);
    TraceLiveFrameProbeStage("direct frame sink after MaybeSubmitCompositorFrame");
    if (result == viz::SubmitResult::ACCEPTED) {
      if (compositor_frame_submitted_) {
        *compositor_frame_submitted_ = true;
      }
      SetFailure("");
      if (display_) {
        DrawVizDisplayNow();
      }
      if (should_copy_output && display_) {
        RequestCopyOutput(output_size,
                          copy_output_png_requested_ &&
                              *copy_output_png_requested_,
                          copy_output_raw_requested_ &&
                              *copy_output_raw_requested_,
                          copy_output_gpu_requested_ &&
                              *copy_output_gpu_requested_);
        DrawVizDisplayNow();
      }
      if (should_copy_output) {
        if (copy_output_completed_ && !*copy_output_completed_) {
          base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
          base::OneShotTimer timeout;
          copy_output_run_loop_ = &run_loop;
          timeout.Start(FROM_HERE, base::Seconds(5), run_loop.QuitClosure());
          viz_client_.SetDeferCompositorFrameAck(true);
          run_loop.Run();
          viz_client_.SetDeferCompositorFrameAck(false);
          viz_client_.FlushDeferredCompositorFrameAck();
          timeout.Stop();
          copy_output_run_loop_ = nullptr;
        }
        if (copy_output_requested_) {
          *copy_output_requested_ = false;
        }
        if (copy_output_completed_ && !*copy_output_completed_) {
          SetCopyOutputFailure(
              "Viz CopyOutput did not complete during Display DrawAndSwap");
        }
      }
      return;
    }
    SetFailure(viz::CompositorFrameSinkSupport::GetSubmitResultAsString(result));
  }

  void DidNotProduceFrame(const viz::BeginFrameAck& ack,
                          cc::FrameSkippedReason reason) override {
    if (did_not_produce_count_) {
      ++*did_not_produce_count_;
    }
    if (last_frame_skipped_reason_) {
      *last_frame_skipped_reason_ = static_cast<int>(reason);
    }
    if (last_did_not_produce_has_damage_) {
      *last_did_not_produce_has_damage_ = ack.has_damage ? 1 : 0;
    }
    TraceLiveFrameProbeStagef(
        "direct frame sink DidNotProduceFrame reason=%lu has_damage=%lu",
        static_cast<wtf_size_t>(reason),
        ack.has_damage ? static_cast<wtf_size_t>(1)
                       : static_cast<wtf_size_t>(0));
    if (support_) {
      support_->DidNotProduceFrame(ack);
    }
  }

  void NotifyNewLocalSurfaceIdExpectedWhilePaused() override {
    if (support_) {
      support_->NotifyNewLocalSurfaceIdExpectedWhilePaused();
    }
  }

  void ExportFrameTiming() override {}

  std::string RunBorrowedVkImageBackingSmokeForTesting() {
    if (!display_) {
      return "gpu_borrowed_vkimage_backing_smoke: failed failure=Viz Display "
             "is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_borrowed_vkimage_backing_smoke: failed failure=offscreen "
             "Vulkan Skia dependency is not available";
    }
    return offscreen_skia_dependency_->RunBorrowedVkImageBackingSmokeForTesting();
  }

  std::string RunBorrowedVkImageRenderCopySmokeForTesting() {
    return RunVkImageRenderCopyForTesting(nullptr);
  }

  std::string RunExternalVkImageRenderCopyForTesting(
      const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
    return RunVkImageRenderCopyForTesting(vulkan_image);
  }

  std::string RenderExternalVkImageToTarget(
      const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
    if (!vulkan_image) {
      return "gpu_external_vkimage_render_copy: failed failure=external "
             "Vulkan image is null";
    }

    gfx::Size output_size(vulkan_image->width, vulkan_image->height);
    if (output_size.IsEmpty()) {
      output_size = viewport_;
      if (viz_display_output_size_ && !viz_display_output_size_->IsEmpty()) {
        output_size = *viz_display_output_size_;
      }
    }
    ResetOffscreenVizDisplayForExternalTargetResize(output_size);
    if (!display_) {
      if (!local_surface_id_.is_valid()) {
        return "gpu_external_vkimage_render_copy: failed failure=Viz Display "
               "cannot initialize without LocalSurfaceId";
      }
      if (!EnsureVizDisplay(output_size)) {
        return "gpu_external_vkimage_render_copy: failed failure=Viz Display "
               "could not initialize";
      }
      display_->SetLocalSurfaceId(local_surface_id_,
                                  last_submitted_device_scale_factor_);
      display_->Resize(output_size);
      if (viz_display_output_size_) {
        *viz_display_output_size_ = output_size;
      }
    } else if (local_surface_id_.is_valid()) {
      display_->SetLocalSurfaceId(local_surface_id_,
                                  last_submitted_device_scale_factor_);
      display_->Resize(output_size);
      if (viz_display_output_size_) {
        *viz_display_output_size_ = output_size;
      }
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_external_vkimage_render_copy: failed "
             "failure=offscreen Vulkan Skia dependency is not available";
    }
    scoped_refptr<gpu::ClientSharedImage> blit_target;
    std::string prepare_result =
        offscreen_skia_dependency_
            ->PrepareBorrowedVkImageRenderCopyBlitTargetForTesting(
                output_size, nullptr, vulkan_image, &blit_target);
    if (!prepare_result.empty()) {
      return "gpu_external_vkimage_render_copy: failed failure=" +
             prepare_result;
    }
    if (!blit_target || blit_target->mailbox().IsZero()) {
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return "gpu_external_vkimage_render_copy: failed failure=external "
             "Vulkan blit target SharedImage is unavailable";
    }

    RequestCopyOutput(output_size,
                      /*wants_png=*/false,
                      /*wants_raw=*/false,
                      /*wants_gpu=*/true, std::move(blit_target));
    DrawVizDisplayNow();
    if (copy_output_completed_ && !*copy_output_completed_) {
      base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
      base::OneShotTimer timeout;
      copy_output_run_loop_ = &run_loop;
      timeout.Start(FROM_HERE, base::Seconds(5), run_loop.QuitClosure());
      run_loop.Run();
      timeout.Stop();
      copy_output_run_loop_ = nullptr;
    }
    if (copy_output_completed_ && !*copy_output_completed_) {
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return "gpu_external_vkimage_render_copy: failed failure=Viz "
             "BlitRequest CopyOutput did not complete";
    }
    if (copy_output_succeeded_ && !*copy_output_succeeded_) {
      std::string failure =
          copy_output_failure_ && !copy_output_failure_->empty()
              ? *copy_output_failure_
              : "Viz BlitRequest CopyOutput failed";
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return "gpu_external_vkimage_render_copy: failed failure=" + failure;
    }
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    offscreen_skia_dependency_
        ->WaitForBorrowedVkImageRenderCopyBlitTargetForTesting();
    offscreen_skia_dependency_
        ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
    std::ostringstream out;
    out << "gpu_external_vkimage_render_copy: ok"
        << " path=viz_blit_request"
        << " target=" << output_size.width() << "x" << output_size.height();
    return out.str();
  }

  std::string RenderBackdropMaskToExternalVkImage(
      const html_css_renderer::ExternalVulkanImageTarget* vulkan_image,
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!display_) {
      return "gpu_external_vkimage_backdrop_mask: failed failure=Viz Display "
             "is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_external_vkimage_backdrop_mask: failed "
             "failure=offscreen Vulkan Skia dependency is not available";
    }
    gfx::Size output_size = viewport_;
    if (vulkan_image && vulkan_image->width > 0 && vulkan_image->height > 0) {
      output_size = gfx::Size(vulkan_image->width, vulkan_image->height);
    } else if (viz_display_output_size_ && !viz_display_output_size_->IsEmpty()) {
      output_size = *viz_display_output_size_;
    }
    return offscreen_skia_dependency_
        ->RenderVulkanBackdropMaskToExternalTargetForTesting(
            vulkan_image, regions, output_size, viewport_);
  }

  std::string RunVkImageRenderCopyForTesting(
      const html_css_renderer::ExternalVulkanImageTarget* external_target) {
    if (!display_) {
      return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=Viz "
             "Display is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_borrowed_vkimage_render_copy_smoke: failed "
             "failure=offscreen Vulkan Skia dependency is not available";
    }

    gfx::Size output_size = viewport_;
    if (viz_display_output_size_ && !viz_display_output_size_->IsEmpty()) {
      output_size = *viz_display_output_size_;
    }
    scoped_refptr<gpu::ClientSharedImage> blit_target;
    std::string prepare_result =
        offscreen_skia_dependency_
            ->PrepareBorrowedVkImageRenderCopyBlitTargetForTesting(
                output_size, nullptr, external_target, &blit_target);
    if (!prepare_result.empty()) {
      return prepare_result;
    }
    if (!blit_target || blit_target->mailbox().IsZero()) {
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return "gpu_borrowed_vkimage_render_copy_smoke: failed "
             "failure=borrowed blit target SharedImage is unavailable "
             "path=viz_blit_request viz_blit_request=1";
    }

    RequestCopyOutput(output_size,
                      /*wants_png=*/false,
                      /*wants_raw=*/false,
                      /*wants_gpu=*/true, std::move(blit_target));
    DrawVizDisplayNow();
    if (copy_output_completed_ && !*copy_output_completed_) {
      base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
      base::OneShotTimer timeout;
      copy_output_run_loop_ = &run_loop;
      timeout.Start(FROM_HERE, base::Seconds(5), run_loop.QuitClosure());
      run_loop.Run();
      timeout.Stop();
      copy_output_run_loop_ = nullptr;
    }
    if (copy_output_completed_ && !*copy_output_completed_) {
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return "gpu_borrowed_vkimage_render_copy_smoke: failed "
             "failure=Viz BlitRequest CopyOutput did not complete "
             "path=viz_blit_request viz_blit_request=1";
    }
    if (copy_output_succeeded_ && !*copy_output_succeeded_) {
      std::string failure =
          copy_output_failure_ && !copy_output_failure_->empty()
              ? *copy_output_failure_
              : "Viz BlitRequest CopyOutput failed";
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
      return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=" +
             failure + " path=viz_blit_request viz_blit_request=1";
    }
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    return offscreen_skia_dependency_
        ->VerifyBorrowedVkImageRenderCopyBlitTargetForTesting();
  }

  std::string RunBorrowedD3D12RenderCopySmokeForTesting() {
    return RunD3D12RenderCopyForTesting(nullptr);
  }

  std::string RunExternalD3D12RenderCopyForTesting(void* d3d12_resource,
                                                   void* shared_handle) {
    ID3D12Resource* external_resource =
        static_cast<ID3D12Resource*>(d3d12_resource);
    return RunD3D12RenderCopyForTesting(external_resource, shared_handle);
  }

  std::string RenderExternalD3D12ToTarget(void* d3d12_resource,
                                          void* shared_handle,
                                          int width,
                                          int height) {
    ID3D12Resource* external_resource =
        static_cast<ID3D12Resource*>(d3d12_resource);
    if (!external_resource && !shared_handle) {
      return "gpu_external_d3d12_render_copy: failed failure=external D3D12 "
             "resource/shared handle is null";
    }

    gfx::Size output_size(width, height);
    if (output_size.IsEmpty() && external_resource) {
      const D3D12_RESOURCE_DESC desc = external_resource->GetDesc();
      output_size =
          gfx::Size(static_cast<int>(desc.Width), static_cast<int>(desc.Height));
    } else if (output_size.IsEmpty() && viz_display_output_size_ &&
               !viz_display_output_size_->IsEmpty()) {
      output_size = *viz_display_output_size_;
    } else if (output_size.IsEmpty()) {
      output_size = viewport_;
    }
    ResetOffscreenVizDisplayForExternalTargetResize(output_size);
    if (!display_) {
      if (!local_surface_id_.is_valid()) {
        return "gpu_external_d3d12_render_copy: failed failure=Viz Display "
               "cannot initialize without LocalSurfaceId";
      }
      if (!EnsureVizDisplay(output_size)) {
        return "gpu_external_d3d12_render_copy: failed failure=Viz Display "
               "could not initialize";
      }
      display_->SetLocalSurfaceId(local_surface_id_,
                                  last_submitted_device_scale_factor_);
      display_->Resize(output_size);
      if (viz_display_output_size_) {
        *viz_display_output_size_ = output_size;
      }
      DrawVizDisplayNow();
    } else if (local_surface_id_.is_valid()) {
      display_->SetLocalSurfaceId(local_surface_id_,
                                  last_submitted_device_scale_factor_);
      display_->Resize(output_size);
      if (viz_display_output_size_) {
        *viz_display_output_size_ = output_size;
      }
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_external_d3d12_render_copy: failed "
             "failure=offscreen D3D12 Skia dependency is not available";
    }
    scoped_refptr<gpu::ClientSharedImage> blit_target;
    std::string prepare_result =
        offscreen_skia_dependency_
            ->PrepareBorrowedD3D12RenderCopyBlitTargetForTesting(
                output_size, external_resource, shared_handle, &blit_target);
    if (!prepare_result.empty()) {
      return "gpu_external_d3d12_render_copy: failed failure=" +
             prepare_result;
    }
    if (!blit_target || blit_target->mailbox().IsZero()) {
      offscreen_skia_dependency_
          ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return "gpu_external_d3d12_render_copy: failed failure=external D3D12 "
             "target SharedImage is unavailable";
    }

    RequestCopyOutput(output_size,
                      /*wants_png=*/false,
                      /*wants_raw=*/false,
                      /*wants_gpu=*/true, std::move(blit_target));
    DrawVizDisplayNow();
    if (copy_output_completed_ && !*copy_output_completed_) {
      base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
      base::OneShotTimer timeout;
      copy_output_run_loop_ = &run_loop;
      timeout.Start(FROM_HERE, base::Seconds(5), run_loop.QuitClosure());
      run_loop.Run();
      timeout.Stop();
      copy_output_run_loop_ = nullptr;
    }
    if (copy_output_completed_ && !*copy_output_completed_) {
      offscreen_skia_dependency_
          ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return "gpu_external_d3d12_render_copy: failed failure=Viz BlitRequest "
             "CopyOutput did not complete";
    }
    if (copy_output_succeeded_ && !*copy_output_succeeded_) {
      std::string failure =
          copy_output_failure_ && !copy_output_failure_->empty()
              ? *copy_output_failure_
              : "Viz BlitRequest CopyOutput failed";
      offscreen_skia_dependency_
          ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return "gpu_external_d3d12_render_copy: failed failure=" + failure;
    }
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    offscreen_skia_dependency_
        ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
    std::ostringstream out;
    out << "gpu_external_d3d12_render_copy: ok"
        << " path=viz_blit_request"
        << " target=" << output_size.width() << "x" << output_size.height();
    return out.str();
  }

  std::string RenderBackdropMaskToExternalD3D12Target(
      void* d3d12_resource,
      void* shared_handle,
      int width,
      int height,
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!display_) {
      return "gpu_external_d3d12_backdrop_mask: failed failure=Viz Display "
             "is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_external_d3d12_backdrop_mask: failed "
             "failure=offscreen D3D12 Skia dependency is not available";
    }
    gfx::Size css_viewport = viewport_;
    return offscreen_skia_dependency_
        ->RenderD3D12BackdropMaskToExternalTargetForTesting(
            d3d12_resource, shared_handle, width, height, regions,
            css_viewport);
  }

  std::string RunD3D12RenderCopyForTesting(ID3D12Resource* external_resource,
                                           void* shared_handle = nullptr) {
    if (!display_) {
      return "gpu_borrowed_d3d12_render_copy_smoke: failed failure=Viz "
             "Display is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_borrowed_d3d12_render_copy_smoke: failed "
             "failure=offscreen D3D12 Skia dependency is not available";
    }

    gfx::Size output_size = viewport_;
    if (viz_display_output_size_ && !viz_display_output_size_->IsEmpty()) {
      output_size = *viz_display_output_size_;
    }
    scoped_refptr<gpu::ClientSharedImage> blit_target;
    std::string prepare_result =
        offscreen_skia_dependency_
            ->PrepareBorrowedD3D12RenderCopyBlitTargetForTesting(
                output_size, external_resource, shared_handle, &blit_target);
    if (!prepare_result.empty()) {
      return prepare_result;
    }
    if (!blit_target || blit_target->mailbox().IsZero()) {
      offscreen_skia_dependency_
          ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return "gpu_borrowed_d3d12_render_copy_smoke: failed "
             "failure=borrowed D3D12 target SharedImage is unavailable "
             "path=viz_blit_request viz_blit_request=1";
    }

    RequestCopyOutput(output_size,
                      /*wants_png=*/false,
                      /*wants_raw=*/false,
                      /*wants_gpu=*/true, std::move(blit_target));
    DrawVizDisplayNow();
    if (copy_output_completed_ && !*copy_output_completed_) {
      base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
      base::OneShotTimer timeout;
      copy_output_run_loop_ = &run_loop;
      timeout.Start(FROM_HERE, base::Seconds(5), run_loop.QuitClosure());
      run_loop.Run();
      timeout.Stop();
      copy_output_run_loop_ = nullptr;
    }
    if (copy_output_completed_ && !*copy_output_completed_) {
      offscreen_skia_dependency_
          ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return "gpu_borrowed_d3d12_render_copy_smoke: failed "
             "failure=Viz BlitRequest CopyOutput did not complete "
             "path=viz_blit_request viz_blit_request=1";
    }
    if (copy_output_succeeded_ && !*copy_output_succeeded_) {
      std::string failure =
          copy_output_failure_ && !copy_output_failure_->empty()
              ? *copy_output_failure_
              : "Viz BlitRequest CopyOutput failed";
      offscreen_skia_dependency_
          ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
      return "gpu_borrowed_d3d12_render_copy_smoke: failed failure=" +
             failure + " path=viz_blit_request viz_blit_request=1";
    }
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    return offscreen_skia_dependency_
        ->VerifyBorrowedD3D12RenderCopyBlitTargetForTesting();
  }

  std::string RunGpuOutputVulkanPixelSmokeForTesting() {
    if (!display_) {
      return "gpu_output_vulkan_pixel_smoke: failed failure=Viz Display is "
             "not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_output_vulkan_pixel_smoke: failed failure=offscreen Vulkan "
             "Skia dependency is not available";
    }
    if (!held_gpu_copy_output_shared_image_) {
      return "gpu_output_vulkan_pixel_smoke: failed failure=held Vulkan "
             "CopyOutput SharedImage is not available";
    }
    return offscreen_skia_dependency_->RunGpuOutputVulkanPixelSmokeForTesting(
        held_gpu_copy_output_shared_image_);
  }

  std::string RunVulkanBackdropMaskPrototypeForTesting(
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!display_) {
      return "gpu_vulkan_backdrop_mask_prototype_smoke: failed failure=Viz "
             "Display is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_vulkan_backdrop_mask_prototype_smoke: failed "
             "failure=offscreen Vulkan Skia dependency is not available";
    }
    gfx::Size output_size = viewport_;
    if (viz_display_output_size_ && !viz_display_output_size_->IsEmpty()) {
      output_size = *viz_display_output_size_;
    }
    return offscreen_skia_dependency_->RunVulkanBackdropMaskPrototypeForTesting(
        regions, output_size, viewport_);
  }

  std::string RunD3D12BackdropMaskPrototypeForTesting(
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!display_) {
      return "gpu_d3d12_backdrop_mask_prototype_smoke: failed failure=Viz "
             "Display is not initialized";
    }
    if (!offscreen_skia_dependency_) {
      return "gpu_d3d12_backdrop_mask_prototype_smoke: failed "
             "failure=offscreen D3D12 Skia dependency is not available";
    }
    gfx::Size output_size = viewport_;
    if (viz_display_output_size_ && !viz_display_output_size_->IsEmpty()) {
      output_size = *viz_display_output_size_;
    }
    return offscreen_skia_dependency_->RunD3D12BackdropMaskPrototypeForTesting(
        regions, output_size, viewport_);
  }

  void ReleaseExternalGpuTargetState() {
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    if (!offscreen_skia_dependency_) {
      return;
    }
    offscreen_skia_dependency_
        ->WaitForBorrowedVkImageRenderCopyBlitTargetForTesting();
    offscreen_skia_dependency_
        ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
    offscreen_skia_dependency_
        ->DiscardBorrowedD3D12RenderCopyBlitTargetForTesting();
    if (!g_standalone_native_window_handle) {
      display_.reset();
      offscreen_skia_dependency_ = nullptr;
      if (viz_display_output_size_) {
        *viz_display_output_size_ = gfx::Size();
      }
    }
  }

 private:
  void ReleaseHeldGpuCopyOutputSharedImage(const gpu::SyncToken& sync_token) {
    held_gpu_copy_output_shared_image_.reset();
    if (held_gpu_copy_output_release_callback_) {
      std::move(held_gpu_copy_output_release_callback_)
          .Run(sync_token, /*lost_resource=*/false);
    }
  }

  void SetFailure(const char* reason) {
    if (failure_reason_) {
      *failure_reason_ = reason ? reason : "";
    }
  }

  bool EnsureVizDisplay(const gfx::Size& output_size) {
    if (display_) {
      return true;
    }
    if (!g_standalone_native_window_handle) {
      if (!gpu_thread_holder_) {
        SetFailure("Offscreen Viz Display cannot initialize without GPU thread holder");
        return false;
      }
      if (!gpu_thread_holder_->GetTaskExecutor()) {
        SetFailure("Offscreen Viz Display GPU thread holder failed to initialize");
        return false;
      }
      auto dependency = std::make_unique<StandaloneSkiaOutputSurfaceDependency>(
          gpu_thread_holder_, gpu::kNullSurfaceHandle, failure_reason_,
          use_vulkan_offscreen_output_, use_d3d12_offscreen_output_,
          &vulkan_context_provider_available_,
          &vulkan_shared_context_state_is_vulkan_);
      offscreen_skia_dependency_ = dependency.get();
      auto display_controller =
          std::make_unique<viz::DisplayCompositorMemoryAndTaskController>(
              std::move(dependency));
      std::unique_ptr<viz::OutputSurface> output_surface =
          viz::SkiaOutputSurfaceImpl::Create(display_controller.get(),
                                             renderer_settings_,
                                             &debug_settings_);
      if (!output_surface) {
        SetFailure("Offscreen Viz Display SkiaOutputSurfaceImpl creation failed");
        return false;
      }
      auto overlay_processor = std::make_unique<viz::OverlayProcessorStub>();
      display_ = std::make_unique<viz::Display>(
          gpu_thread_holder_->shared_image_manager(),
          gpu_thread_holder_->scheduler(),
          renderer_settings_, &debug_settings_, frame_sink_id_,
          std::move(display_controller), std::move(output_surface),
          std::move(overlay_processor),
          /*scheduler=*/nullptr,
          base::SingleThreadTaskRunner::GetCurrentDefault());
      display_->Initialize(&display_client_,
                           frame_sink_manager_->surface_manager());
      display_->SetVisible(true);
      display_->Resize(output_size);
      display_uses_software_output_ = false;
      if (viz_display_created_) {
        *viz_display_created_ = true;
      }
      TraceLiveFrameProbeStage(
          "direct frame sink after offscreen Display initialize");
      return true;
    }
    if (!gpu_thread_holder_) {
      SetFailure("Viz Display cannot initialize without GPU thread holder");
      return false;
    }
    gpu::SurfaceHandle surface_handle = reinterpret_cast<gpu::SurfaceHandle>(
        g_standalone_native_window_handle);
    if (surface_handle == gpu::kNullSurfaceHandle) {
      SetFailure("Viz Display received a null native surface handle");
      return false;
    }
    TraceLiveFrameProbeStage("direct frame sink before Viz Display GPU init");
    offscreen_skia_dependency_ = nullptr;
    if (!gpu_thread_holder_->GetTaskExecutor()) {
      SetFailure("Viz Display GPU thread holder failed to initialize");
      return false;
    }
    TraceLiveFrameProbeStage("direct frame sink before Viz Display dependency");
    auto display_controller =
        std::make_unique<viz::DisplayCompositorMemoryAndTaskController>(
            std::make_unique<StandaloneSkiaOutputSurfaceDependency>(
                gpu_thread_holder_, surface_handle, failure_reason_,
                /*use_vulkan_offscreen=*/false,
                /*use_d3d12_offscreen=*/false,
                /*vulkan_context_provider_available=*/nullptr,
                /*shared_context_state_is_vulkan=*/nullptr));
    TraceLiveFrameProbeStage("direct frame sink before SkiaOutputSurface");
    std::unique_ptr<viz::OutputSurface> output_surface =
        viz::SkiaOutputSurfaceImpl::Create(display_controller.get(),
                                           renderer_settings_,
                                           &debug_settings_);
    if (!output_surface) {
      SetFailure("Viz Display SkiaOutputSurfaceImpl creation failed");
      return false;
    }
    TraceLiveFrameProbeStage("direct frame sink after SkiaOutputSurface");
    auto overlay_processor = viz::OverlayProcessorInterface::CreateOverlayProcessor(
        output_surface.get(), surface_handle, output_surface->capabilities(),
        display_controller.get(), gpu_thread_holder_->shared_image_manager(),
        renderer_settings_, &debug_settings_);
    if (!overlay_processor) {
      SetFailure("Viz Display overlay processor creation failed");
      return false;
    }
    TraceLiveFrameProbeStage("direct frame sink before Display create");
    display_ = std::make_unique<viz::Display>(
        gpu_thread_holder_->shared_image_manager(), gpu_thread_holder_->scheduler(),
        renderer_settings_, &debug_settings_, frame_sink_id_,
        std::move(display_controller), std::move(output_surface),
        std::move(overlay_processor),
        /*scheduler=*/nullptr, base::SingleThreadTaskRunner::GetCurrentDefault());
    display_->Initialize(&display_client_, frame_sink_manager_->surface_manager());
    display_->SetVisible(true);
    display_->Resize(output_size);
    display_uses_software_output_ = false;
    if (viz_display_created_) {
      *viz_display_created_ = true;
    }
    TraceLiveFrameProbeStage("direct frame sink after Display initialize");
    return true;
  }

  void ResetOffscreenVizDisplayForExternalTargetResize(
      const gfx::Size& output_size) {
    if (g_standalone_native_window_handle || !display_ ||
        !viz_display_output_size_ || viz_display_output_size_->IsEmpty() ||
        *viz_display_output_size_ == output_size) {
      return;
    }
    TraceLiveFrameProbeStage(
        "direct frame sink drain offscreen Display for external target resize");
    ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    if (offscreen_skia_dependency_) {
      offscreen_skia_dependency_
          ->WaitForBorrowedVkImageRenderCopyBlitTargetForTesting();
      offscreen_skia_dependency_
          ->DiscardBorrowedVkImageRenderCopyBlitTargetForTesting();
    }
  }

  void DrawVizDisplayNow() {
    if (!display_) {
      return;
    }
    TraceLiveFrameProbeStage("direct frame sink before Display DrawAndSwap");
    const base::TimeTicks now = base::TimeTicks::Now();
    const base::TimeDelta interval = viz::BeginFrameArgs::DefaultInterval();
    viz::DrawAndSwapParams params;
    params.begin_frame_args = viz::BeginFrameArgs::Create(
        BEGINFRAME_FROM_HERE, viz::BeginFrameArgs::kManualSourceId,
        ++display_begin_frame_sequence_, now, now + interval, interval,
        viz::BeginFrameArgs::NORMAL);
    params.expected_display_time = now + interval;
    const bool drew = display_->DrawAndSwap(params);
    TraceLiveFrameProbeStage("direct frame sink after Display DrawAndSwap");
    TraceLiveFrameProbeStage("direct frame sink before DrawAndSwap result");
    if (!drew) {
      SetFailure("Viz Display DrawAndSwap returned false");
      return;
    }
    TraceLiveFrameProbeStage("direct frame sink before gpu reached flag");
    if (!display_uses_software_output_ && skia_gpu_reached_) {
      *skia_gpu_reached_ = true;
    }
    TraceLiveFrameProbeStage("direct frame sink after gpu reached flag");
  }

  void RequestCopyOutput(const gfx::Size& output_size,
                         bool wants_png,
                         bool wants_raw,
                         bool wants_gpu,
                         scoped_refptr<gpu::ClientSharedImage> blit_target =
                             nullptr) {
    if (wants_gpu) {
      ReleaseHeldGpuCopyOutputSharedImage(gpu::SyncToken());
    }
    if (!support_) {
      SetCopyOutputFailure("Viz CopyOutput cannot run without frame sink support");
      return;
    }
    if (!local_surface_id_.is_valid()) {
      SetCopyOutputFailure("Viz CopyOutput cannot run without LocalSurfaceId");
      return;
    }
    if (copy_output_completed_) {
      *copy_output_completed_ = false;
    }
    if (copy_output_succeeded_) {
      *copy_output_succeeded_ = false;
    }
    if (copy_output_png_) {
      copy_output_png_->clear();
    }
    if (copy_output_raw_frame_) {
      *copy_output_raw_frame_ = LiveRawFrameOutput();
    }
    if (copy_output_gpu_frame_) {
      *copy_output_gpu_frame_ = LiveGpuFrameOutput();
    }
    if (copy_output_failure_) {
      copy_output_failure_->clear();
    }

    auto request = std::make_unique<viz::CopyOutputRequest>(
        viz::CopyOutputRequest::ResultFormat::RGBA,
        wants_gpu ? viz::CopyOutputRequest::ResultDestination::kSharedImage
                  : viz::CopyOutputRequest::ResultDestination::kSystemMemory,
        base::BindOnce(&StandaloneDirectLayerTreeFrameSink::OnCopyOutput,
                       base::Unretained(this), wants_png, wants_raw,
                       wants_gpu));
    request->set_area(gfx::Rect(output_size));
    if (blit_target) {
      request->set_result_selection(gfx::Rect(output_size));
      const gpu::SyncToken sync_token = blit_target->creation_sync_token();
      request->set_blit_request(viz::BlitRequest(
          gfx::Point(), viz::LetterboxingBehavior::kDoNotLetterbox,
          std::move(blit_target), sync_token,
          /*populates_mappable_shared_image=*/false));
    }
    support_->RequestCopyOfOutput(
        std::make_unique<viz::PendingCopyOutputRequest>(
            local_surface_id_, viz::SubtreeCaptureId(), std::move(request)));
  }

  void OnCopyOutput(bool wants_png,
                    bool wants_raw,
                    bool wants_gpu,
                    std::unique_ptr<viz::CopyOutputResult> output) {
    if (!output) {
      SetCopyOutputFailure("Viz CopyOutput returned no result");
      return;
    }
    if (output->IsEmpty()) {
      SetCopyOutputFailure(
          std::string("Viz CopyOutput returned empty result: ") +
          StandaloneCopyOutputErrorName(output->error()));
      return;
    }
    if (wants_gpu) {
      if (output->destination() !=
          viz::CopyOutputResult::Destination::kSharedImage) {
        SetCopyOutputFailure("Viz CopyOutput did not return a shared image");
        return;
      }
      scoped_refptr<gpu::ClientSharedImage> shared_image =
          output->GetSharedImage();
      if (!shared_image || shared_image->mailbox().IsZero()) {
        SetCopyOutputFailure("Viz CopyOutput shared image is missing");
        return;
      }
      held_gpu_copy_output_shared_image_ = shared_image;
      held_gpu_copy_output_release_callback_ =
          output->TakeSharedImageOwnership();
      if (copy_output_gpu_frame_) {
        LiveGpuFrameOutput gpu_frame;
        gpu_frame.shared_image_available = true;
        gpu_frame.is_software = shared_image->is_software();
        gpu_frame.vk_context_provider_available =
            vulkan_context_provider_available_;
        gpu_frame.shared_context_state_is_vulkan =
            vulkan_shared_context_state_is_vulkan_;
        gpu_frame.width = shared_image->size().width();
        gpu_frame.height = shared_image->size().height();
        gpu_frame.format = shared_image->format().ToString();
        gpu_frame.mailbox = shared_image->mailbox().ToDebugString();
        gpu_frame.creation_sync_token =
            shared_image->creation_sync_token().ToDebugString();
        *copy_output_gpu_frame_ = std::move(gpu_frame);
      }
      if (copy_output_failure_) {
        copy_output_failure_->clear();
      }
      if (copy_output_succeeded_) {
        *copy_output_succeeded_ = true;
      }
      if (copy_output_completed_) {
        *copy_output_completed_ = true;
      }
      if (copy_output_run_loop_) {
        copy_output_run_loop_->Quit();
      }
      return;
    }
    viz::CopyOutputResult::ScopedSkBitmap scoped_bitmap =
        output->ScopedAccessSkBitmap();
    SkBitmap bitmap = scoped_bitmap.GetOutScopedBitmap();
    if (!bitmap.readyToDraw()) {
      SetCopyOutputFailure("Viz CopyOutput bitmap is not drawable");
      return;
    }
    SkPixmap pixmap;
    if (!bitmap.peekPixels(&pixmap)) {
      SetCopyOutputFailure("Viz CopyOutput bitmap has no readable pixels");
      return;
    }
    SkBitmap top_left_bitmap;
    if (!top_left_bitmap.tryAllocPixels(pixmap.info())) {
      SetCopyOutputFailure("Viz CopyOutput PNG normalization allocation failed");
      return;
    }
    SkPixmap top_left_pixmap;
    if (!top_left_bitmap.peekPixels(&top_left_pixmap)) {
      SetCopyOutputFailure("Viz CopyOutput normalized bitmap has no pixels");
      return;
    }
    const size_t row_bytes =
        pixmap.info().minRowBytes64() > 0
            ? static_cast<size_t>(pixmap.info().minRowBytes64())
            : static_cast<size_t>(pixmap.width()) *
                  pixmap.info().bytesPerPixel();
    for (int y = 0; y < pixmap.height(); ++y) {
      std::memcpy(top_left_pixmap.writable_addr(0, y),
                  pixmap.addr(0, pixmap.height() - 1 - y), row_bytes);
    }
    if (wants_raw && copy_output_raw_frame_) {
      LiveRawFrameOutput raw_frame;
      raw_frame.width = top_left_pixmap.width();
      raw_frame.height = top_left_pixmap.height();
      raw_frame.stride = static_cast<int>(top_left_pixmap.rowBytes());
      raw_frame.premultiplied_alpha =
          top_left_pixmap.info().alphaType() == kPremul_SkAlphaType;
      if (top_left_pixmap.info().colorType() == kRGBA_8888_SkColorType) {
        raw_frame.pixel_format = 1;
      } else if (top_left_pixmap.info().colorType() ==
                 kBGRA_8888_SkColorType) {
        raw_frame.pixel_format = 2;
      }
      if (raw_frame.pixel_format != 0 && raw_frame.width > 0 &&
          raw_frame.height > 0 && raw_frame.stride > 0) {
        const size_t byte_count =
            static_cast<size_t>(raw_frame.stride) *
            static_cast<size_t>(raw_frame.height);
        const auto* pixels =
            static_cast<const uint8_t*>(top_left_pixmap.addr(0, 0));
        raw_frame.pixels.assign(pixels, pixels + byte_count);
      }
      *copy_output_raw_frame_ = std::move(raw_frame);
    }
    if (wants_raw && copy_output_raw_frame_ &&
        copy_output_raw_frame_->pixels.empty()) {
      SetCopyOutputFailure(
          "Viz CopyOutput raw frame has unsupported pixel format");
      return;
    }
    if (wants_png) {
      SkPngEncoder::Options options;
      sk_sp<SkData> png = SkPngEncoder::Encode(top_left_pixmap, options);
      if (!png || png->empty()) {
        SetCopyOutputFailure("Viz CopyOutput PNG encoding failed");
        return;
      }
      if (copy_output_png_) {
        const auto* bytes = static_cast<const uint8_t*>(png->data());
        copy_output_png_->assign(bytes, bytes + png->size());
      }
    }
    if (copy_output_failure_) {
      copy_output_failure_->clear();
    }
    if (copy_output_succeeded_) {
      *copy_output_succeeded_ = true;
    }
    if (copy_output_completed_) {
      *copy_output_completed_ = true;
    }
    if (copy_output_run_loop_) {
      copy_output_run_loop_->Quit();
    }
  }

  void SetCopyOutputFailure(std::string reason) {
    if (copy_output_png_) {
      copy_output_png_->clear();
    }
    if (copy_output_raw_frame_) {
      *copy_output_raw_frame_ = LiveRawFrameOutput();
    }
    if (copy_output_gpu_frame_) {
      *copy_output_gpu_frame_ = LiveGpuFrameOutput();
    }
    if (copy_output_failure_) {
      *copy_output_failure_ = std::move(reason);
    }
    if (copy_output_succeeded_) {
      *copy_output_succeeded_ = false;
    }
    if (copy_output_completed_) {
      *copy_output_completed_ = true;
    }
    if (copy_output_run_loop_) {
      copy_output_run_loop_->Quit();
    }
  }

  raw_ptr<viz::FrameSinkManagerImpl> frame_sink_manager_ = nullptr;
  viz::FrameSinkId frame_sink_id_;
  viz::LocalSurfaceId local_surface_id_;
  std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder_;
  gfx::Size viewport_;
  viz::RendererSettings renderer_settings_;
  viz::DebugRendererSettings debug_settings_;
  StandaloneVizFrameSinkClient viz_client_;
  StandaloneDisplayClient display_client_;
  std::unique_ptr<viz::BackToBackBeginFrameSource> begin_frame_source_;
  std::unique_ptr<viz::CompositorFrameSinkSupport> support_;
  std::unique_ptr<viz::Display> display_;
  raw_ptr<StandaloneSkiaOutputSurfaceDependency> offscreen_skia_dependency_ =
      nullptr;
  bool display_uses_software_output_ = false;
  bool vulkan_context_provider_available_ = false;
  bool vulkan_shared_context_state_is_vulkan_ = false;
  bool use_d3d12_offscreen_output_ = false;
  float last_submitted_device_scale_factor_ = 1.0f;
  uint64_t display_begin_frame_sequence_ = viz::BeginFrameArgs::kStartingFrameNumber;
  raw_ptr<bool> compositor_frame_submitted_ = nullptr;
  raw_ptr<bool> viz_display_created_ = nullptr;
  raw_ptr<bool> skia_gpu_reached_ = nullptr;
  raw_ptr<gfx::Size> submitted_output_size_ = nullptr;
  raw_ptr<gfx::Size> viz_display_output_size_ = nullptr;
  raw_ptr<bool> copy_output_requested_ = nullptr;
  raw_ptr<bool> copy_output_png_requested_ = nullptr;
  raw_ptr<bool> copy_output_raw_requested_ = nullptr;
  raw_ptr<bool> copy_output_gpu_requested_ = nullptr;
  raw_ptr<bool> copy_output_completed_ = nullptr;
  raw_ptr<bool> copy_output_succeeded_ = nullptr;
  raw_ptr<std::vector<uint8_t>> copy_output_png_ = nullptr;
  raw_ptr<LiveRawFrameOutput> copy_output_raw_frame_ = nullptr;
  raw_ptr<LiveGpuFrameOutput> copy_output_gpu_frame_ = nullptr;
  raw_ptr<std::string> copy_output_failure_ = nullptr;
  raw_ptr<base::RunLoop> copy_output_run_loop_ = nullptr;
  scoped_refptr<gpu::ClientSharedImage> held_gpu_copy_output_shared_image_;
  viz::ReleaseCallback held_gpu_copy_output_release_callback_;
  raw_ptr<std::string> failure_reason_ = nullptr;
  raw_ptr<bool> begin_frame_source_set_ = nullptr;
  raw_ptr<int> did_not_produce_count_ = nullptr;
  raw_ptr<int> last_frame_skipped_reason_ = nullptr;
  raw_ptr<int> last_did_not_produce_has_damage_ = nullptr;
  bool use_vulkan_offscreen_output_ = false;
};

struct OriginalElementAttributeValue {
  bool present = false;
  std::string value;
};

using StandaloneProbeClock = std::chrono::steady_clock;

double StandaloneProbeElapsedMs(StandaloneProbeClock::time_point start,
                                StandaloneProbeClock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}

class StandaloneCcLayerHost final
    : public cc::LayerTreeHostDelegate,
      public cc::LayerTreeHostSingleThreadDelegate,
      public cc::LayerTreeHostSchedulingDelegate {
 public:
  StandaloneCcLayerHost() {
    settings_.single_thread_proxy_scheduler = true;
    settings_.use_layer_lists = true;
    settings_.can_use_lcd_text = true;
    settings_.layers_always_allowed_lcd_text = true;
  }

  StandaloneCcLayerHost(const StandaloneCcLayerHost&) = delete;
  StandaloneCcLayerHost& operator=(const StandaloneCcLayerHost&) = delete;

  ~StandaloneCcLayerHost() override {
    active_frame_sink_ = nullptr;
    layer_tree_host_.reset();
    animation_host_.reset();
    if (scheduler_task_graph_runner_started_) {
      scheduler_task_graph_runner_.Shutdown();
      scheduler_task_graph_runner_started_ = false;
    }
  }

  bool AttachRootLayer(scoped_refptr<cc::Layer> root_layer,
                       const gfx::Size& viewport,
                       float device_scale_factor,
                       std::string* failure_reason) {
    attach_attempted_ = true;
    if (!root_layer) {
      root_layer_attached_ = false;
      SetFailure(failure_reason, "PaintArtifactCompositor supplied no root cc::Layer");
      return false;
    }
    cc::Layer* root_layer_ptr = root_layer.get();
    if (!EnsureHost(failure_reason)) {
      root_layer_attached_ = false;
      return false;
    }
    const gfx::Size physical_viewport =
        StandalonePhysicalViewportForDeviceScale(viewport, device_scale_factor);
    const bool viewport_changed = logical_viewport_ != viewport ||
                                  physical_viewport_ != physical_viewport ||
                                  device_scale_factor_ != device_scale_factor;
    const bool root_layer_changed = root_layer_ptr != attached_root_layer_;
    if (!surface_id_allocator_.HasValidLocalSurfaceId() || viewport_changed) {
      surface_id_allocator_.GenerateId();
    }
    logical_viewport_ = viewport;
    physical_viewport_ = physical_viewport;
    device_scale_factor_ = device_scale_factor;
    TraceLiveFrameProbeStage("cc host AttachRootLayer before viewport surface");
    layer_tree_host_->SetViewportRectAndScale(
        gfx::Rect(physical_viewport_), device_scale_factor_,
        surface_id_allocator_.GetCurrentLocalSurfaceId());
    layer_tree_host_->SetVisualDeviceViewportIntersectionRect(
        gfx::Rect(physical_viewport_));
    layer_tree_host_->SetVisualDeviceViewportSize(physical_viewport_);
    TraceLiveFrameProbeStage("cc host AttachRootLayer after viewport surface");
    root_layer->SetBounds(viewport);
    layer_tree_host_->SetRootLayer(std::move(root_layer));
    root_layer_attached_ = layer_tree_host_->has_root_layer();
    if (root_layer_attached_) {
      attached_root_layer_ = root_layer_ptr;
      next_composite_requires_forced_redraw_ |=
          viewport_changed || root_layer_changed || commit_count_ == 0 ||
          !frame_sink_bound_;
      if (!inside_scheduler_layer_tree_update_) {
        layer_tree_host_->SetNeedsCommit();
      }
      commit_requested_ = true;
    } else {
      attached_root_layer_ = nullptr;
      SetFailure(failure_reason, "cc::LayerTreeHost rejected the PAC root layer");
    }
    return root_layer_attached_;
  }

  bool CompositeForTest(std::string* failure_reason) {
    if (!layer_tree_host_ || !root_layer_attached_) {
      SetFailure(failure_reason,
                 "cc::LayerTreeHost has no attached PAC root layer to submit");
      return false;
    }
    TraceLiveFrameProbeStage("cc host CompositeForTest before SetNeedsCommit");
    if (next_composite_requires_forced_redraw_) {
      layer_tree_host_->SetNeedsCommitWithForcedRedraw();
    } else {
      layer_tree_host_->SetNeedsCommit();
    }
    next_composite_requires_forced_redraw_ = false;
    commit_requested_ = true;
    TraceLiveFrameProbeStage("cc host CompositeForTest before cc composite");
    layer_tree_host_->CompositeForTest(base::TimeTicks::Now(),
                                       /*raster=*/true, base::DoNothing());
    TraceLiveFrameProbeStage("cc host CompositeForTest after cc composite");
    return true;
  }

  bool host_created() const { return layer_tree_host_ != nullptr; }
  void SetTransparentBackground(bool enabled) {
    if (transparent_background_ == enabled) {
      return;
    }
    transparent_background_ = enabled;
    if (layer_tree_host_) {
      layer_tree_host_->set_background_color(
          transparent_background_ ? SkColors::kTransparent : SkColors::kWhite);
      layer_tree_host_->SetNeedsRedrawRect(gfx::Rect(physical_viewport_));
      if (!inside_scheduler_layer_tree_update_) {
        layer_tree_host_->SetNeedsCommit();
      }
      commit_requested_ = true;
    }
  }
  bool attach_attempted() const { return attach_attempted_; }
  bool root_layer_attached() const { return root_layer_attached_; }
  bool commit_requested() const { return commit_requested_; }
  bool frame_sink_requested() const { return frame_sink_requested_; }
  bool frame_sink_bound() const { return frame_sink_bound_; }
  bool compositor_frame_submitted() const {
    return compositor_frame_submitted_;
  }
  bool gpu_context_created() const { return gpu_context_created_; }
  bool raster_context_created() const { return raster_context_created_; }
  bool shared_image_interface_available() const {
    return shared_image_interface_available_;
  }
  bool viz_display_created() const { return viz_display_created_; }
  bool skia_gpu_reached() const { return skia_gpu_reached_; }
  bool use_vulkan_offscreen_output() const {
    return use_vulkan_offscreen_output_;
  }
  bool use_d3d12_offscreen_output() const {
    return use_d3d12_offscreen_output_;
  }
  void SetUseVulkanOffscreenOutput(bool enabled) {
    SetGpuOffscreenOutputMode(enabled, /*use_d3d12=*/false);
  }
  void SetUseD3D12OffscreenOutput(bool enabled) {
    SetGpuOffscreenOutputMode(/*use_vulkan=*/false, enabled);
  }
  void SetGpuOffscreenOutputMode(bool use_vulkan, bool use_d3d12) {
    if (use_vulkan_offscreen_output_ == use_vulkan &&
        use_d3d12_offscreen_output_ == use_d3d12) {
      return;
    }
    use_vulkan_offscreen_output_ = use_vulkan;
    use_d3d12_offscreen_output_ = use_d3d12;
    active_frame_sink_ = nullptr;
    layer_tree_host_.reset();
    animation_host_.reset();
    frame_sink_manager_.reset();
    frame_sink_id_registered_ = false;
    attached_root_layer_ = nullptr;
    root_layer_attached_ = false;
    frame_sink_bound_ = false;
    frame_sink_requested_ = false;
    frame_sink_failure_reason_.clear();
  }
  gfx::Size submitted_output_size() const { return submitted_output_size_; }
  gfx::Size viz_display_output_size() const { return viz_display_output_size_; }
  int commit_count() const { return commit_count_; }
  const std::string& frame_sink_failure_reason() const {
    return frame_sink_failure_reason_;
  }
  void RequestNextCopyOutput(bool wants_png, bool wants_raw) {
    RequestNextCopyOutput(wants_png, wants_raw, /*wants_gpu=*/false);
  }

  void RequestNextGpuFrameOutput() {
    RequestNextGpuFrameOutput(/*use_vulkan_offscreen_output=*/false,
                              /*use_d3d12_offscreen_output=*/false);
  }

  void RequestNextGpuFrameOutput(bool use_vulkan_offscreen_output,
                                 bool use_d3d12_offscreen_output = false) {
    DCHECK_EQ(use_vulkan_offscreen_output_, use_vulkan_offscreen_output);
    DCHECK_EQ(use_d3d12_offscreen_output_, use_d3d12_offscreen_output);
    RequestNextCopyOutput(/*wants_png=*/false, /*wants_raw=*/false,
                          /*wants_gpu=*/true);
  }

  void RequestNextCopyOutput(bool wants_png, bool wants_raw, bool wants_gpu) {
    copy_output_requested_ = true;
    copy_output_png_requested_ = wants_png;
    copy_output_raw_requested_ = wants_raw;
    copy_output_gpu_requested_ = wants_gpu;
    copy_output_completed_ = false;
    copy_output_succeeded_ = false;
    copy_output_png_.clear();
    copy_output_raw_frame_ = LiveRawFrameOutput();
    copy_output_gpu_frame_ = LiveGpuFrameOutput();
    copy_output_failure_.clear();
    next_composite_requires_forced_redraw_ = true;
  }
  void RequestNextCopyOutputPng() {
    RequestNextCopyOutput(/*wants_png=*/true, /*wants_raw=*/false);
  }
  std::string RunBorrowedVkImageBackingSmokeForTesting() {
    if (!active_frame_sink_) {
      return "gpu_borrowed_vkimage_backing_smoke: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunBorrowedVkImageBackingSmokeForTesting();
  }
  std::string RunBorrowedVkImageRenderCopySmokeForTesting() {
    if (!active_frame_sink_) {
      return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunBorrowedVkImageRenderCopySmokeForTesting();
  }
  std::string RunExternalVkImageRenderCopyForTesting(
      const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
    if (!active_frame_sink_) {
      return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunExternalVkImageRenderCopyForTesting(
        vulkan_image);
  }
  std::string RenderExternalVkImageToTarget(
      const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
    if (!active_frame_sink_) {
      return "gpu_external_vkimage_render_copy: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RenderExternalVkImageToTarget(vulkan_image);
  }

  std::string RenderBackdropMaskToExternalVkImage(
      const html_css_renderer::ExternalVulkanImageTarget* vulkan_image,
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!active_frame_sink_) {
      return "gpu_external_vkimage_backdrop_mask: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RenderBackdropMaskToExternalVkImage(vulkan_image,
                                                                  regions);
  }
  std::string RunBorrowedD3D12RenderCopySmokeForTesting() {
    if (!active_frame_sink_) {
      return "gpu_borrowed_d3d12_render_copy_smoke: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunBorrowedD3D12RenderCopySmokeForTesting();
  }
  std::string RunExternalD3D12RenderCopyForTesting(void* d3d12_resource,
                                                   void* shared_handle) {
    if (!active_frame_sink_) {
      return "gpu_borrowed_d3d12_render_copy_smoke: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunExternalD3D12RenderCopyForTesting(
        d3d12_resource, shared_handle);
  }
  std::string RenderExternalD3D12ToTarget(void* d3d12_resource,
                                          void* shared_handle,
                                          int width,
                                          int height) {
    if (!active_frame_sink_) {
      return "gpu_external_d3d12_render_copy: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RenderExternalD3D12ToTarget(
        d3d12_resource, shared_handle, width, height);
  }

  std::string RenderBackdropMaskToExternalD3D12Target(
      void* d3d12_resource,
      void* shared_handle,
      int width,
      int height,
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!active_frame_sink_) {
      return "gpu_external_d3d12_backdrop_mask: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RenderBackdropMaskToExternalD3D12Target(
        d3d12_resource, shared_handle, width, height, regions);
  }
  std::string RunGpuOutputVulkanPixelSmokeForTesting() {
    if (!active_frame_sink_) {
      return "gpu_output_vulkan_pixel_smoke: failed failure=active "
             "LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunGpuOutputVulkanPixelSmokeForTesting();
  }
  std::string RunVulkanBackdropMaskPrototypeForTesting(
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!active_frame_sink_) {
      return "gpu_vulkan_backdrop_mask_prototype_smoke: failed "
             "failure=active LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunVulkanBackdropMaskPrototypeForTesting(regions);
  }
  std::string RunD3D12BackdropMaskPrototypeForTesting(
      const std::vector<LiveBackdropFilterRegion>& regions) {
    if (!active_frame_sink_) {
      return "gpu_d3d12_backdrop_mask_prototype_smoke: failed "
             "failure=active LayerTreeFrameSink is not available";
    }
    return active_frame_sink_->RunD3D12BackdropMaskPrototypeForTesting(regions);
  }
  void ReleaseExternalGpuTargetState() {
    if (active_frame_sink_) {
      active_frame_sink_->ReleaseExternalGpuTargetState();
    }
  }
  bool copy_output_completed() const { return copy_output_completed_; }
  bool copy_output_succeeded() const { return copy_output_succeeded_; }
  const std::vector<uint8_t>& copy_output_png() const {
    return copy_output_png_;
  }
  const LiveRawFrameOutput& copy_output_raw_frame() const {
    return copy_output_raw_frame_;
  }
  const LiveGpuFrameOutput& copy_output_gpu_frame() const {
    return copy_output_gpu_frame_;
  }
  const std::string& copy_output_failure() const {
    return copy_output_failure_;
  }
  double timing_frame_sink_warmup_ms() const {
    return timing_frame_sink_warmup_ms_;
  }
  double timing_root_preattach_ms() const {
    return timing_root_preattach_ms_;
  }
  double timing_pending_update_ms() const {
    return timing_pending_update_ms_;
  }
  double timing_scheduler_run_loop_ms() const {
    return timing_scheduler_run_loop_ms_;
  }
  double timing_submit_wait_ms() const { return timing_submit_wait_ms_; }

  cc::AnimationHost* animation_host() const { return animation_host_.get(); }

  bool EnsureHostForScheduler(const gfx::Size& viewport,
                              float device_scale_factor,
                              std::string* failure_reason) {
    if (!EnsureHost(failure_reason)) {
      return false;
    }
    UpdateViewportForScheduler(viewport, device_scale_factor);
    return true;
  }

  bool EnsureFrameSinkReadyForScheduler(std::string* failure_reason) {
    if (!layer_tree_host_) {
      SetFailure(failure_reason,
                 "cc scheduler frame requested before LayerTreeHost exists");
      return false;
    }
    if (frame_sink_bound_) {
      timing_frame_sink_warmup_ms_ = 0.0;
      return true;
    }
    const auto warmup_start = StandaloneProbeClock::now();
    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    frame_sink_init_run_loop_ = &run_loop;
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE, run_loop.QuitClosure(), base::Seconds(2));
    TraceLiveFrameProbeStage("cc host scheduler before frame sink warm-up");
    layer_tree_host_->SetShouldWarmUp();
    run_loop.Run();
    timing_frame_sink_warmup_ms_ =
        StandaloneProbeElapsedMs(warmup_start, StandaloneProbeClock::now());
    TraceLiveFrameProbeStage("cc host scheduler after frame sink warm-up");
    frame_sink_init_run_loop_ = nullptr;
    if (!frame_sink_bound_) {
      SetFailure(failure_reason,
                 frame_sink_failure_reason_.empty()
                     ? "cc scheduler did not initialize LayerTreeFrameSink"
                     : frame_sink_failure_reason_.c_str());
      return false;
    }
    return true;
  }

  void SetPendingLayerTreeUpdateForScheduler(std::function<void()> update) {
    pending_scheduler_layer_tree_update_ = std::move(update);
  }

  void ClearPendingLayerTreeUpdateForScheduler() {
    pending_scheduler_layer_tree_update_ = nullptr;
  }

  bool ScheduleFrameWithPendingLayerTreeUpdateForScheduler(
      std::function<void()> pre_attach_root_update,
      std::function<void()> update,
      base::TimeDelta scheduler_timeout,
      bool* timed_out,
      std::string* failure_reason) {
    if (!layer_tree_host_) {
      SetFailure(failure_reason,
                 "cc scheduler frame requested before LayerTreeHost exists");
      return false;
    }
    compositor_frame_submitted_ = false;
    scheduler_begin_main_frame_seen_ = false;
    scheduler_pending_update_ran_ = false;
    if (timed_out) {
      *timed_out = false;
    }
    timing_root_preattach_ms_ = 0.0;
    timing_pending_update_ms_ = 0.0;
    timing_scheduler_run_loop_ms_ = 0.0;
    timing_submit_wait_ms_ = 0.0;
    if (!root_layer_attached_) {
      TraceLiveFrameProbeStage(
          "cc host scheduler bootstrap before PAC root preattach");
      const auto preattach_start = StandaloneProbeClock::now();
      base::AutoReset<bool> inside_update(&inside_scheduler_layer_tree_update_,
                                          true);
      pre_attach_root_update();
      timing_root_preattach_ms_ =
          StandaloneProbeElapsedMs(preattach_start, StandaloneProbeClock::now());
      TraceLiveFrameProbeStage(
          "cc host scheduler bootstrap after PAC root preattach");
      if (!root_layer_attached_) {
        SetFailure(failure_reason,
                   "cc scheduler could not preattach the PAC root layer");
        return false;
      }
    }
    UpdateViewportForScheduler(logical_viewport_, device_scale_factor_);
    SetPendingLayerTreeUpdateForScheduler(std::move(update));
    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    base::OneShotTimer timeout_timer;
    scheduler_frame_run_loop_ = &run_loop;
    // Keep synchronous embedder ticks responsive if cc posts the frame but the
    // standalone scheduler callback that normally quits this loop is missed.
    timeout_timer.Start(
        FROM_HERE, scheduler_timeout,
        base::BindOnce(
            [](base::RunLoop* loop, bool* timed_out) {
              if (timed_out) {
                *timed_out = true;
              }
              loop->Quit();
            },
            &run_loop, timed_out));

    TraceLiveFrameProbeStage("cc host scheduler before posted SetNeedsCommit");
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
        FROM_HERE,
        base::BindOnce(
            &StandaloneCcLayerHost::
                RequestPendingSchedulerCommitAfterFrameSinkInit,
            weak_factory_.GetWeakPtr()));
    commit_requested_ = true;
    TraceLiveFrameProbeStage("cc host scheduler before run loop");
    scheduler_frame_start_time_ = StandaloneProbeClock::now();
    const auto run_loop_start = StandaloneProbeClock::now();
    run_loop.Run();
    timeout_timer.Stop();
    timing_scheduler_run_loop_ms_ =
        StandaloneProbeElapsedMs(run_loop_start, StandaloneProbeClock::now());
    TraceLiveFrameProbeStage("cc host scheduler after run loop");
    scheduler_frame_run_loop_ = nullptr;
    scheduler_frame_start_time_.reset();
    ClearPendingLayerTreeUpdateForScheduler();
    if (timed_out && *timed_out && !compositor_frame_submitted_) {
      SetFailure(failure_reason, "cc scheduler frame is pending");
      return false;
    }
    if (!scheduler_pending_update_ran_) {
      SetFailure(failure_reason,
                 "cc scheduler did not run the pending standalone frame update");
      return false;
    }
    if (!compositor_frame_submitted_) {
      SetFailure(failure_reason,
                 scheduler_begin_main_frame_seen_
                     ? "cc scheduler did not submit a compositor frame"
                     : "cc scheduler did not invoke BeginMainFrame");
      return false;
    }
    return true;
  }

 private:
  bool EnsureHost(std::string* failure_reason) {
    if (layer_tree_host_) {
      return true;
    }
    scoped_refptr<base::SingleThreadTaskRunner> main_task_runner =
        base::SingleThreadTaskRunner::GetCurrentDefault();
    if (!main_task_runner) {
      SetFailure(failure_reason,
                 "cc::LayerTreeHost requires a current main-thread task runner");
      return false;
    }

    animation_host_ = cc::AnimationHost::CreateMainInstance();
    cc::LayerTreeHost::InitParams params;
    params.client = this;
    params.scheduling_delegate = this;
    params.task_graph_runner = TaskGraphRunnerForCurrentMode();
    params.settings = &settings_;
    params.main_task_runner = std::move(main_task_runner);
    params.mutator_host = animation_host_.get();

    layer_tree_host_ =
        cc::LayerTreeHost::CreateSingleThreaded(this, std::move(params));
    if (!layer_tree_host_) {
      SetFailure(failure_reason, "cc::LayerTreeHost creation failed");
      animation_host_.reset();
      return false;
    }
    layer_tree_host_->SetVisible(true);
    layer_tree_host_->set_background_color(
        transparent_background_ ? SkColors::kTransparent : SkColors::kWhite);
    return true;
  }

  static void SetFailure(std::string* out, const char* reason) {
    if (out) {
      *out = reason ? reason : "";
    }
  }

  cc::TaskGraphRunner* TaskGraphRunnerForCurrentMode() {
    if (!settings_.single_thread_proxy_scheduler) {
      return &task_graph_runner_;
    }
    if (!scheduler_task_graph_runner_started_) {
      scheduler_task_graph_runner_.Start(
          "StandaloneCcSchedulerTileRunner", base::SimpleThread::Options());
      scheduler_task_graph_runner_started_ = true;
      TraceLiveFrameProbeStage(
          "cc host scheduler using SingleThreadTaskGraphRunner");
    }
    return &scheduler_task_graph_runner_;
  }

  void RememberFrameSinkFailure(const char* reason) {
    frame_sink_failure_reason_ = reason ? reason : "";
  }

  void RequestPendingSchedulerCommitAfterFrameSinkInit() {
    if (!layer_tree_host_ ||
        (!pending_scheduler_layer_tree_update_ && !root_layer_attached_)) {
      return;
    }
    TraceLiveFrameProbeStage(
        "cc host posted frame-sink init pending update commit");
    const bool force_redraw = next_composite_requires_forced_redraw_;
    if (force_redraw) {
      if (attached_root_layer_) {
        attached_root_layer_->SetNeedsDisplay();
      }
      layer_tree_host_->SetNeedsRecalculateRasterScales();
    }
    layer_tree_host_->SetNeedsUpdateLayers();
    layer_tree_host_->SetNeedsRedrawRect(gfx::Rect(physical_viewport_));
    if (force_redraw) {
      layer_tree_host_->SetNeedsCommitWithForcedRedraw();
    } else {
      layer_tree_host_->SetNeedsCommit();
    }
    next_composite_requires_forced_redraw_ = false;
    commit_requested_ = true;
  }

  void UpdateViewportForScheduler(const gfx::Size& viewport,
                                  float device_scale_factor) {
    if (!layer_tree_host_) {
      logical_viewport_ = viewport;
      device_scale_factor_ =
          device_scale_factor > 0.0f ? device_scale_factor : 1.0f;
      physical_viewport_ = StandalonePhysicalViewportForDeviceScale(
          logical_viewport_, device_scale_factor_);
      return;
    }
    const float clamped_device_scale_factor =
        device_scale_factor > 0.0f ? device_scale_factor : 1.0f;
    const gfx::Size physical_viewport =
        StandalonePhysicalViewportForDeviceScale(
            viewport, clamped_device_scale_factor);
    const bool viewport_changed = logical_viewport_ != viewport ||
                                  physical_viewport_ != physical_viewport ||
                                  device_scale_factor_ !=
                                      clamped_device_scale_factor;
    if (!surface_id_allocator_.HasValidLocalSurfaceId() || viewport_changed) {
      surface_id_allocator_.GenerateId();
    }
    logical_viewport_ = viewport;
    physical_viewport_ = physical_viewport;
    device_scale_factor_ = clamped_device_scale_factor;
    TraceLiveFrameProbeStage("cc host scheduler before viewport surface");
    layer_tree_host_->SetViewportRectAndScale(
        gfx::Rect(physical_viewport_), device_scale_factor_,
        surface_id_allocator_.GetCurrentLocalSurfaceId());
    layer_tree_host_->SetVisualDeviceViewportIntersectionRect(
        gfx::Rect(physical_viewport_));
    layer_tree_host_->SetVisualDeviceViewportSize(physical_viewport_);
    if (attached_root_layer_) {
      attached_root_layer_->SetBounds(logical_viewport_);
    }
    if (viewport_changed) {
      next_composite_requires_forced_redraw_ = true;
      layer_tree_host_->SetNeedsUpdateLayers();
      layer_tree_host_->SetNeedsRedrawRect(gfx::Rect(physical_viewport_));
      if (!inside_scheduler_layer_tree_update_) {
        layer_tree_host_->SetNeedsCommit();
      }
      commit_requested_ = true;
    }
    TraceLiveFrameProbeStage("cc host scheduler after viewport surface");
  }

  bool CreateFrameSink() {
    TraceLiveFrameProbeStage("cc host CreateFrameSink begin");
    scoped_refptr<base::SingleThreadTaskRunner> main_task_runner =
        base::SingleThreadTaskRunner::GetCurrentDefault();
    if (!main_task_runner) {
      TraceLiveFrameProbeStage("cc host CreateFrameSink missing task runner");
      RememberFrameSinkFailure(
          "cc::LayerTreeFrameSink requires a current task runner");
      return false;
    }

    viz::FrameSinkManagerImpl::InitParams manager_params;
    if (!frame_sink_manager_) {
      TraceLiveFrameProbeStage("cc host CreateFrameSink before manager");
      frame_sink_manager_ =
          std::make_unique<viz::FrameSinkManagerImpl>(manager_params);
      TraceLiveFrameProbeStage("cc host CreateFrameSink after manager");
    }

    const viz::FrameSinkId frame_sink_id(777, 1);
    if (!frame_sink_id_registered_) {
      TraceLiveFrameProbeStage("cc host CreateFrameSink before register id");
      frame_sink_manager_->RegisterFrameSinkId(frame_sink_id,
                                               /*report_activation=*/true);
      frame_sink_manager_->SetFrameSinkDebugLabel(
          frame_sink_id, "standalone-renderer-cc-root");
      frame_sink_id_registered_ = true;
      TraceLiveFrameProbeStage("cc host CreateFrameSink after register id");
    }

    TraceLiveFrameProbeStage("cc host CreateFrameSink before gpu holder");
    if (!gpu_thread_holder_) {
      gpu_thread_holder_ = std::make_shared<gpu::InProcessGpuThreadHolder>();
      gpu_thread_holder_->GetGpuPreferences()->gr_context_type =
          use_d3d12_offscreen_output_
              ? gpu::GrContextType::kGraphiteDawn
              : (use_vulkan_offscreen_output_ ? gpu::GrContextType::kVulkan
                                              : gpu::GrContextType::kGL);
      if (use_vulkan_offscreen_output_) {
        InstallPendingExternalVulkanForTesting(gpu_thread_holder_.get());
      }
      if (use_d3d12_offscreen_output_) {
        InstallPendingExternalD3D12AdapterLuidForTesting(
            gpu_thread_holder_.get());
      }
    }
    TraceLiveFrameProbeStage("cc host CreateFrameSink after gpu holder");
    TraceLiveFrameProbeStage("cc host CreateFrameSink before context providers");
    auto compositor_context_provider =
        base::MakeRefCounted<StandaloneInProcessRasterContextProvider>(
            gpu_thread_holder_, /*enforce_cache_controller_lock=*/false,
            &gpu_context_created_, &raster_context_created_,
            &shared_image_interface_available_, &frame_sink_failure_reason_);
    auto worker_context_provider =
        base::MakeRefCounted<StandaloneInProcessRasterContextProvider>(
            gpu_thread_holder_,
            /*enforce_cache_controller_lock=*/true, &gpu_context_created_,
            &raster_context_created_, &shared_image_interface_available_,
            &frame_sink_failure_reason_);
    TraceLiveFrameProbeStage("cc host CreateFrameSink after context providers");

    TraceLiveFrameProbeStage("cc host CreateFrameSink before worker bind");
    const gpu::ContextResult worker_bind_result =
        worker_context_provider->BindToCurrentSequence();
    TraceLiveFrameProbeStage("cc host CreateFrameSink after worker bind");
    if (worker_bind_result != gpu::ContextResult::kSuccess) {
      RememberFrameSinkFailure(
          frame_sink_failure_reason_.empty()
              ? "worker raster context provider failed to bind"
              : frame_sink_failure_reason_.c_str());
      return false;
    }

    TraceLiveFrameProbeStage("cc host CreateFrameSink before frame sink");
    auto layer_tree_frame_sink =
        std::make_unique<StandaloneDirectLayerTreeFrameSink>(
            frame_sink_manager_.get(), frame_sink_id, gpu_thread_holder_,
            std::move(compositor_context_provider),
            std::move(worker_context_provider), std::move(main_task_runner),
            g_standalone_native_window_size.IsEmpty()
                ? physical_viewport_
                : g_standalone_native_window_size,
            &compositor_frame_submitted_, &viz_display_created_,
            &skia_gpu_reached_, &submitted_output_size_,
            &viz_display_output_size_, &copy_output_requested_,
            &copy_output_png_requested_, &copy_output_raw_requested_,
            &copy_output_gpu_requested_,
            &copy_output_completed_, &copy_output_succeeded_,
            &copy_output_png_, &copy_output_raw_frame_,
            &copy_output_gpu_frame_, &copy_output_failure_,
            &frame_sink_failure_reason_,
            /*begin_frame_source_set=*/nullptr,
            /*did_not_produce_count=*/nullptr,
            /*last_frame_skipped_reason=*/nullptr,
            /*last_did_not_produce_has_damage=*/nullptr,
            settings_.single_thread_proxy_scheduler,
            use_vulkan_offscreen_output_, use_d3d12_offscreen_output_);
    active_frame_sink_ = layer_tree_frame_sink.get();
    TraceLiveFrameProbeStage("cc host CreateFrameSink before SetLayerTreeFrameSink");
    layer_tree_host_->SetLayerTreeFrameSink(std::move(layer_tree_frame_sink));
    TraceLiveFrameProbeStage("cc host CreateFrameSink after SetLayerTreeFrameSink");
    return true;
  }

  void WillBeginMainFrame() override {}
  void BeginMainFrame(const viz::BeginFrameArgs& args) override {
    TraceLiveFrameProbeStage("cc host BeginMainFrame");
    last_begin_main_frame_args_ = args;
    scheduler_begin_main_frame_seen_ = true;
  }
  void BeginMainFrameNotExpectedSoon() override {}
  void BeginMainFrameNotExpectedUntil(base::TimeTicks time) override {}
  void DidBeginMainFrame() override {}
  void WillUpdateLayers() override {}
  void DidUpdateLayers() override {}
  void DidObserveFirstScrollDelay(int source_frame_number,
                                  base::TimeDelta first_scroll_delay,
                                  base::TimeTicks first_scroll_timestamp)
      override {}
  void OnDeferMainFrameUpdatesChanged(bool defer_status) override {}
  void OnDeferCommitsChanged(bool defer_status,
                             cc::PaintHoldingReason reason) override {}
  void OnCommitRequested() override { commit_requested_ = true; }
  void UpdateLayerTreeHost() override {
    TraceLiveFrameProbeStage("cc host UpdateLayerTreeHost");
    if (!pending_scheduler_layer_tree_update_) {
      return;
    }
    std::function<void()> update = std::move(pending_scheduler_layer_tree_update_);
    pending_scheduler_layer_tree_update_ = nullptr;
    base::AutoReset<bool> inside_update(&inside_scheduler_layer_tree_update_,
                                        true);
    const auto update_start = StandaloneProbeClock::now();
    update();
    if (copy_output_requested_) {
      TraceLiveFrameProbeStage(
          "cc host UpdateLayerTreeHost forcing CopyOutput damage");
      if (attached_root_layer_) {
        attached_root_layer_->SetNeedsDisplay();
      }
      layer_tree_host_->SetNeedsUpdateLayers();
      layer_tree_host_->SetNeedsRedrawRect(gfx::Rect(physical_viewport_));
    }
    timing_pending_update_ms_ =
        StandaloneProbeElapsedMs(update_start, StandaloneProbeClock::now());
    scheduler_pending_update_ran_ = true;
  }
  void ApplyViewportChanges(const cc::ApplyViewportChangesArgs& args) override {
  }
  void UpdateCompositorScrollState(
      const cc::CompositorCommitData& commit_data) override {}
  void UpdateAnimatedImageState(
      const cc::CompositorCommitData& commit_data) override {}
  void RequestNewLayerTreeFrameSink() override {
    frame_sink_requested_ = true;
    frame_sink_bound_ = false;
    compositor_frame_submitted_ = false;
    gpu_context_created_ = false;
    raster_context_created_ = false;
    shared_image_interface_available_ = false;
    viz_display_created_ = false;
    skia_gpu_reached_ = false;
    frame_sink_failure_reason_.clear();
    if (!CreateFrameSink()) {
      frame_sink_bound_ = false;
    }
  }
  void DidInitializeLayerTreeFrameSink() override {
    frame_sink_bound_ = true;
    frame_sink_failure_reason_.clear();
    if (frame_sink_init_run_loop_) {
      frame_sink_init_run_loop_->Quit();
    }
    if (layer_tree_host_ &&
        (pending_scheduler_layer_tree_update_ || root_layer_attached_)) {
      TraceLiveFrameProbeStage(
          "cc host DidInitializeLayerTreeFrameSink post pending update");
      base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
          FROM_HERE,
          base::BindOnce(
              &StandaloneCcLayerHost::
                  RequestPendingSchedulerCommitAfterFrameSinkInit,
              weak_factory_.GetWeakPtr()));
    }
  }
  void DidFailToInitializeLayerTreeFrameSink() override {
    frame_sink_bound_ = false;
    active_frame_sink_ = nullptr;
    if (frame_sink_failure_reason_.empty()) {
      RememberFrameSinkFailure("cc::LayerTreeHost rejected LayerTreeFrameSink");
    }
  }
  void WillCommit(const cc::CommitState& commit_state) override {}
  void DidCommit(int source_frame_number,
                 base::TimeTicks commit_start_time,
                 base::TimeTicks commit_finish_time) override {
    ++commit_count_;
  }
  void DidCommitAndDrawFrame(int source_frame_number) override {}
  void DidCompletePageScaleAnimation(int source_frame_number) override {}
  void DidPresentCompositorFrame(
      uint32_t frame_token,
      const viz::FrameTimingDetails& frame_timing_details) override {}
  void RecordStartOfFrameMetrics() override {}
  void RecordEndOfFrameMetrics(base::TimeTicks frame_begin_time,
                               cc::ActiveFrameSequenceTrackers trackers)
      override {}
  std::unique_ptr<cc::BeginMainFrameMetrics> GetBeginMainFrameMetrics()
      override {
    return nullptr;
  }
  void NotifyCompositorMetricsTrackerResults(
      cc::CustomTrackerResults results) override {}
  void DidRunBeginMainFrame() override {}
  void DidSubmitCompositorFrame() override {
    TraceLiveFrameProbeStage("cc host DidSubmitCompositorFrame");
    if (scheduler_frame_run_loop_ && !scheduler_pending_update_ran_) {
      TraceLiveFrameProbeStage(
          "cc host ignoring stale submit before pending scheduler update");
      return;
    }
    compositor_frame_submitted_ = true;
    if (scheduler_frame_start_time_) {
      timing_submit_wait_ms_ = StandaloneProbeElapsedMs(
          *scheduler_frame_start_time_, StandaloneProbeClock::now());
    }
    if (scheduler_frame_run_loop_) {
      scheduler_frame_run_loop_->Quit();
    }
  }
  void DidLoseLayerTreeFrameSink() override {
    frame_sink_requested_ = true;
    frame_sink_bound_ = false;
    active_frame_sink_ = nullptr;
    RememberFrameSinkFailure("cc::LayerTreeFrameSink was lost");
  }

  cc::LayerTreeSettings settings_;
  cc::SynchronousTaskGraphRunner task_graph_runner_;
  cc::SingleThreadTaskGraphRunner scheduler_task_graph_runner_;
  bool scheduler_task_graph_runner_started_ = false;
  std::unique_ptr<cc::AnimationHost> animation_host_;
  viz::ParentLocalSurfaceIdAllocator surface_id_allocator_;
  std::unique_ptr<viz::FrameSinkManagerImpl> frame_sink_manager_;
  std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder_;
  std::unique_ptr<cc::LayerTreeHost> layer_tree_host_;
  raw_ptr<StandaloneDirectLayerTreeFrameSink> active_frame_sink_ = nullptr;
  raw_ptr<cc::Layer> attached_root_layer_ = nullptr;
  gfx::Size logical_viewport_;
  gfx::Size physical_viewport_;
  float device_scale_factor_ = 1.0f;
  bool attach_attempted_ = false;
  bool root_layer_attached_ = false;
  bool next_composite_requires_forced_redraw_ = true;
  bool commit_requested_ = false;
  bool frame_sink_requested_ = false;
  bool frame_sink_bound_ = false;
  bool frame_sink_id_registered_ = false;
  bool compositor_frame_submitted_ = false;
  bool gpu_context_created_ = false;
  bool raster_context_created_ = false;
  bool shared_image_interface_available_ = false;
  bool viz_display_created_ = false;
  bool skia_gpu_reached_ = false;
  gfx::Size submitted_output_size_;
  gfx::Size viz_display_output_size_;
  bool copy_output_requested_ = false;
  bool copy_output_png_requested_ = false;
  bool copy_output_raw_requested_ = false;
  bool copy_output_gpu_requested_ = false;
  bool copy_output_completed_ = false;
  bool copy_output_succeeded_ = false;
  bool use_vulkan_offscreen_output_ = false;
  bool use_d3d12_offscreen_output_ = false;
  std::vector<uint8_t> copy_output_png_;
  LiveRawFrameOutput copy_output_raw_frame_;
  LiveGpuFrameOutput copy_output_gpu_frame_;
  std::string copy_output_failure_;
  int commit_count_ = 0;
  std::string frame_sink_failure_reason_;
  std::function<void()> pending_scheduler_layer_tree_update_;
  viz::BeginFrameArgs last_begin_main_frame_args_;
  bool scheduler_begin_main_frame_seen_ = false;
  bool scheduler_pending_update_ran_ = false;
  bool transparent_background_ = false;
  bool inside_scheduler_layer_tree_update_ = false;
  raw_ptr<base::RunLoop> scheduler_frame_run_loop_ = nullptr;
  raw_ptr<base::RunLoop> frame_sink_init_run_loop_ = nullptr;
  std::optional<StandaloneProbeClock::time_point> scheduler_frame_start_time_;
  double timing_frame_sink_warmup_ms_ = 0.0;
  double timing_root_preattach_ms_ = 0.0;
  double timing_pending_update_ms_ = 0.0;
  double timing_scheduler_run_loop_ms_ = 0.0;
  double timing_submit_wait_ms_ = 0.0;
  base::WeakPtrFactory<StandaloneCcLayerHost> weak_factory_{this};
};

class StandaloneCcSchedulerParityProbe final
    : public cc::LayerTreeHostDelegate,
      public cc::LayerTreeHostSingleThreadDelegate,
      public cc::LayerTreeHostSchedulingDelegate {
 public:
  explicit StandaloneCcSchedulerParityProbe(const gfx::Size& viewport)
      : viewport_(viewport) {
    settings_.single_thread_proxy_scheduler = true;
    settings_.use_layer_lists = false;
  }

  ~StandaloneCcSchedulerParityProbe() override {
    layer_tree_host_.reset();
    animation_host_.reset();
    if (task_graph_runner_started_) {
      task_graph_runner_.Shutdown();
      task_graph_runner_started_ = false;
    }
  }

  StandaloneCcSchedulerParityProbe(const StandaloneCcSchedulerParityProbe&) =
      delete;
  StandaloneCcSchedulerParityProbe& operator=(
      const StandaloneCcSchedulerParityProbe&) = delete;

  std::string Run() {
    if (!CreateHost()) {
      return BuildJson(false);
    }

    frame_sink_warm_run_loop_ = std::make_unique<base::RunLoop>(
        base::RunLoop::Type::kNestableTasksAllowed);
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE, frame_sink_warm_run_loop_->QuitClosure(), base::Seconds(2));
    TraceLiveFrameProbeStage("cc scheduler probe before SetShouldWarmUp");
    layer_tree_host_->SetShouldWarmUp();
    frame_sink_warm_run_loop_->Run();
    TraceLiveFrameProbeStage("cc scheduler probe after SetShouldWarmUp");
    frame_sink_warm_run_loop_.reset();

    scheduler_run_loop_ = std::make_unique<base::RunLoop>(
        base::RunLoop::Type::kNestableTasksAllowed);
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostDelayedTask(
        FROM_HERE, scheduler_run_loop_->QuitClosure(), base::Seconds(2));
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
        FROM_HERE,
        base::BindOnce(&StandaloneCcSchedulerParityProbe::PostInitCommit,
                       base::Unretained(this)));
    scheduler_run_loop_->Run();
    scheduler_run_loop_.reset();

    return BuildJson(compositor_frame_submitted_);
  }

 private:
  bool CreateHost() {
    scoped_refptr<base::SingleThreadTaskRunner> main_task_runner =
        base::SingleThreadTaskRunner::GetCurrentDefault();
    if (!main_task_runner) {
      failure_reason_ =
          "cc scheduler probe requires a current main-thread task runner";
      return false;
    }

    animation_host_ = cc::AnimationHost::CreateMainInstance();
    cc::LayerTreeHost::InitParams params;
    params.client = this;
    params.scheduling_delegate = this;
    params.task_graph_runner = TaskGraphRunnerForProbe();
    params.settings = &settings_;
    params.main_task_runner = std::move(main_task_runner);
    params.mutator_host = animation_host_.get();
    layer_tree_host_ =
        cc::LayerTreeHost::CreateSingleThreaded(this, std::move(params));
    if (!layer_tree_host_) {
      failure_reason_ = "cc scheduler probe failed to create LayerTreeHost";
      return false;
    }
    host_created_ = true;
    layer_tree_host_->SetVisible(true);
    visible_ = true;
    return true;
  }

  cc::TaskGraphRunner* TaskGraphRunnerForProbe() {
    if (!task_graph_runner_started_) {
      task_graph_runner_.Start("StandaloneCcSchedulerProbeTileRunner",
                               base::SimpleThread::Options());
      task_graph_runner_started_ = true;
    }
    return &task_graph_runner_;
  }

  bool CreateFrameSink() {
    scoped_refptr<base::SingleThreadTaskRunner> main_task_runner =
        base::SingleThreadTaskRunner::GetCurrentDefault();
    if (!main_task_runner) {
      failure_reason_ =
          "cc scheduler probe frame sink requires a current task runner";
      return false;
    }

    if (!frame_sink_manager_) {
      viz::FrameSinkManagerImpl::InitParams manager_params;
      frame_sink_manager_ =
          std::make_unique<viz::FrameSinkManagerImpl>(manager_params);
    }
    const viz::FrameSinkId frame_sink_id(778, 1);
    if (!frame_sink_id_registered_) {
      frame_sink_manager_->RegisterFrameSinkId(frame_sink_id,
                                               /*report_activation=*/true);
      frame_sink_manager_->SetFrameSinkDebugLabel(
          frame_sink_id, "standalone-renderer-cc-scheduler-probe");
      frame_sink_id_registered_ = true;
    }

    if (!gpu_thread_holder_) {
      gpu_thread_holder_ = std::make_shared<gpu::InProcessGpuThreadHolder>();
      gpu_thread_holder_->GetGpuPreferences()->gr_context_type =
          gpu::GrContextType::kGL;
    }
    auto compositor_context_provider =
        base::MakeRefCounted<StandaloneInProcessRasterContextProvider>(
            gpu_thread_holder_, /*enforce_cache_controller_lock=*/false,
            &gpu_context_created_, &raster_context_created_,
            &shared_image_interface_available_, &failure_reason_);
    auto worker_context_provider =
        base::MakeRefCounted<StandaloneInProcessRasterContextProvider>(
            gpu_thread_holder_, /*enforce_cache_controller_lock=*/true,
            &gpu_context_created_, &raster_context_created_,
            &shared_image_interface_available_, &failure_reason_);
    const gpu::ContextResult worker_bind_result =
        worker_context_provider->BindToCurrentSequence();
    if (worker_bind_result != gpu::ContextResult::kSuccess) {
      if (failure_reason_.empty()) {
        failure_reason_ =
            "cc scheduler probe worker raster context provider failed to bind";
      }
      return false;
    }

    auto layer_tree_frame_sink =
        std::make_unique<StandaloneDirectLayerTreeFrameSink>(
            frame_sink_manager_.get(), frame_sink_id, gpu_thread_holder_,
            std::move(compositor_context_provider),
            std::move(worker_context_provider), std::move(main_task_runner),
            viewport_, &compositor_frame_submitted_, &viz_display_created_,
            &skia_gpu_reached_, /*submitted_output_size=*/nullptr,
            /*viz_display_output_size=*/nullptr, &copy_output_requested_,
            /*copy_output_png_requested=*/nullptr,
            /*copy_output_raw_requested=*/nullptr,
            /*copy_output_gpu_requested=*/nullptr,
            &copy_output_completed_, &copy_output_succeeded_,
            &copy_output_png_, &copy_output_raw_frame_,
            /*copy_output_gpu_frame=*/nullptr, &copy_output_failure_,
            &failure_reason_,
            &begin_frame_source_set_, &did_not_produce_count_,
            &last_frame_skipped_reason_, &last_did_not_produce_has_damage_,
            /*async_compositor_frame_ack=*/true);
    layer_tree_host_->SetLayerTreeFrameSink(std::move(layer_tree_frame_sink));
    return true;
  }

  void PostInitCommit() {
    post_init_commit_ran_ = true;
    if (!layer_tree_host_) {
      failure_reason_ = "cc scheduler probe post-init commit has no host";
      QuitSchedulerRunLoop();
      return;
    }
    if (!frame_sink_bound_) {
      failure_reason_ =
          "cc scheduler probe post-init commit ran before frame sink bound";
      QuitSchedulerRunLoop();
      return;
    }
    if (!surface_id_allocator_.HasValidLocalSurfaceId()) {
      surface_id_allocator_.GenerateId();
    }
    layer_tree_host_->SetViewportRectAndScale(
        gfx::Rect(viewport_), /*device_scale_factor=*/1.0f,
        surface_id_allocator_.GetCurrentLocalSurfaceId());
    layer_tree_host_->SetVisualDeviceViewportIntersectionRect(
        gfx::Rect(viewport_));
    layer_tree_host_->SetVisualDeviceViewportSize(viewport_);

    scoped_refptr<cc::SolidColorLayer> root_layer =
        cc::SolidColorLayer::Create();
    root_layer->SetBounds(viewport_);
    root_layer->SetIsDrawable(true);
    root_layer->SetBackgroundColor(SkColor4f{0.1f, 0.45f, 0.9f, 1.0f});
    layer_tree_host_->SetRootLayer(root_layer);
    root_layer_attached_ = layer_tree_host_->has_root_layer();
    layer_tree_host_->SetNeedsCommit();
    layer_tree_host_->SetNeedsRedrawRect(gfx::Rect(viewport_));
    set_needs_commit_posted_ = true;
  }

  void QuitSchedulerRunLoop() {
    if (scheduler_run_loop_) {
      scheduler_run_loop_->Quit();
    }
  }

  std::string BuildJson(bool success) const {
    std::ostringstream json;
    json << "{\n";
    json << "  \"probe\": \"cc_scheduler_parity\",\n";
    json << "  \"success\": " << (success ? "true" : "false") << ",\n";
    json << "  \"host_created\": " << (host_created_ ? 1 : 0) << ",\n";
    json << "  \"visible\": " << (visible_ ? 1 : 0) << ",\n";
    json << "  \"request_new_layer_tree_frame_sink\": "
         << (request_new_layer_tree_frame_sink_seen_ ? 1 : 0) << ",\n";
    json << "  \"frame_sink_bound\": " << (frame_sink_bound_ ? 1 : 0)
         << ",\n";
    json << "  \"begin_frame_source_set\": "
         << (begin_frame_source_set_ ? 1 : 0) << ",\n";
    json << "  \"post_init_commit_ran\": " << (post_init_commit_ran_ ? 1 : 0)
         << ",\n";
    json << "  \"set_needs_commit_posted\": "
         << (set_needs_commit_posted_ ? 1 : 0) << ",\n";
    json << "  \"root_layer_attached\": " << (root_layer_attached_ ? 1 : 0)
         << ",\n";
    json << "  \"will_begin_main_frame_count\": "
         << will_begin_main_frame_count_ << ",\n";
    json << "  \"begin_main_frame_count\": " << begin_main_frame_count_
         << ",\n";
    json << "  \"did_begin_main_frame_count\": "
         << did_begin_main_frame_count_ << ",\n";
    json << "  \"update_layer_tree_host_count\": "
         << update_layer_tree_host_count_ << ",\n";
    json << "  \"did_run_begin_main_frame_count\": "
         << did_run_begin_main_frame_count_ << ",\n";
    json << "  \"did_commit_count\": " << did_commit_count_ << ",\n";
    json << "  \"did_submit_compositor_frame_count\": "
         << did_submit_compositor_frame_count_ << ",\n";
    json << "  \"did_not_produce_count\": " << did_not_produce_count_
         << ",\n";
    json << "  \"last_frame_skipped_reason\": "
         << last_frame_skipped_reason_ << ",\n";
    json << "  \"last_did_not_produce_has_damage\": "
         << last_did_not_produce_has_damage_ << ",\n";
    json << "  \"gpu_context_created\": " << (gpu_context_created_ ? 1 : 0)
         << ",\n";
    json << "  \"raster_context_created\": "
         << (raster_context_created_ ? 1 : 0) << ",\n";
    json << "  \"shared_image_interface_available\": "
         << (shared_image_interface_available_ ? 1 : 0) << ",\n";
    json << "  \"compositor_frame_submitted\": "
         << (compositor_frame_submitted_ ? 1 : 0) << ",\n";
    json << "  \"failure_reason\": "
         << JsonStringForStandaloneRenderer(failure_reason_) << "\n";
    json << "}\n";
    return json.str();
  }

  void WillBeginMainFrame() override { ++will_begin_main_frame_count_; }
  void BeginMainFrame(const viz::BeginFrameArgs& args) override {
    ++begin_main_frame_count_;
  }
  void BeginMainFrameNotExpectedSoon() override {}
  void BeginMainFrameNotExpectedUntil(base::TimeTicks time) override {}
  void DidBeginMainFrame() override { ++did_begin_main_frame_count_; }
  void WillUpdateLayers() override {}
  void DidUpdateLayers() override {}
  void DidObserveFirstScrollDelay(int source_frame_number,
                                  base::TimeDelta first_scroll_delay,
                                  base::TimeTicks first_scroll_timestamp)
      override {}
  void OnDeferMainFrameUpdatesChanged(bool defer_status) override {}
  void OnDeferCommitsChanged(bool defer_status,
                             cc::PaintHoldingReason reason) override {}
  void OnCommitRequested() override {}
  void UpdateLayerTreeHost() override { ++update_layer_tree_host_count_; }
  void ApplyViewportChanges(const cc::ApplyViewportChangesArgs& args) override {
  }
  void UpdateCompositorScrollState(
      const cc::CompositorCommitData& commit_data) override {}
  void UpdateAnimatedImageState(
      const cc::CompositorCommitData& commit_data) override {}
  void RequestNewLayerTreeFrameSink() override {
    request_new_layer_tree_frame_sink_seen_ = true;
    frame_sink_bound_ = false;
    if (!CreateFrameSink()) {
      frame_sink_bound_ = false;
    }
  }
  void DidInitializeLayerTreeFrameSink() override {
    frame_sink_bound_ = true;
    if (frame_sink_warm_run_loop_) {
      frame_sink_warm_run_loop_->Quit();
    }
  }
  void DidFailToInitializeLayerTreeFrameSink() override {
    frame_sink_bound_ = false;
    if (failure_reason_.empty()) {
      failure_reason_ =
          "cc scheduler probe LayerTreeFrameSink initialization failed";
    }
    if (frame_sink_warm_run_loop_) {
      frame_sink_warm_run_loop_->Quit();
    }
  }
  void WillCommit(const cc::CommitState& commit_state) override {}
  void DidCommit(int source_frame_number,
                 base::TimeTicks commit_start_time,
                 base::TimeTicks commit_finish_time) override {
    ++did_commit_count_;
  }
  void DidCommitAndDrawFrame(int source_frame_number) override {}
  void DidCompletePageScaleAnimation(int source_frame_number) override {}
  void DidPresentCompositorFrame(
      uint32_t frame_token,
      const viz::FrameTimingDetails& frame_timing_details) override {}
  void RecordStartOfFrameMetrics() override {}
  void RecordEndOfFrameMetrics(base::TimeTicks frame_begin_time,
                               cc::ActiveFrameSequenceTrackers trackers)
      override {}
  std::unique_ptr<cc::BeginMainFrameMetrics> GetBeginMainFrameMetrics()
      override {
    return nullptr;
  }
  void NotifyCompositorMetricsTrackerResults(
      cc::CustomTrackerResults results) override {}
  void DidRunBeginMainFrame() override {
    ++did_run_begin_main_frame_count_;
  }
  void DidSubmitCompositorFrame() override {
    ++did_submit_compositor_frame_count_;
    compositor_frame_submitted_ = true;
    QuitSchedulerRunLoop();
  }
  void DidLoseLayerTreeFrameSink() override {
    frame_sink_bound_ = false;
    failure_reason_ = "cc scheduler probe LayerTreeFrameSink was lost";
  }

  gfx::Size viewport_;
  cc::LayerTreeSettings settings_;
  cc::SingleThreadTaskGraphRunner task_graph_runner_;
  bool task_graph_runner_started_ = false;
  std::unique_ptr<cc::AnimationHost> animation_host_;
  viz::ParentLocalSurfaceIdAllocator surface_id_allocator_;
  std::unique_ptr<viz::FrameSinkManagerImpl> frame_sink_manager_;
  std::shared_ptr<gpu::InProcessGpuThreadHolder> gpu_thread_holder_;
  std::unique_ptr<cc::LayerTreeHost> layer_tree_host_;
  std::unique_ptr<base::RunLoop> frame_sink_warm_run_loop_;
  std::unique_ptr<base::RunLoop> scheduler_run_loop_;
  bool host_created_ = false;
  bool visible_ = false;
  bool request_new_layer_tree_frame_sink_seen_ = false;
  bool frame_sink_bound_ = false;
  bool frame_sink_id_registered_ = false;
  bool begin_frame_source_set_ = false;
  bool post_init_commit_ran_ = false;
  bool set_needs_commit_posted_ = false;
  bool root_layer_attached_ = false;
  int will_begin_main_frame_count_ = 0;
  int begin_main_frame_count_ = 0;
  int did_begin_main_frame_count_ = 0;
  int update_layer_tree_host_count_ = 0;
  int did_run_begin_main_frame_count_ = 0;
  int did_commit_count_ = 0;
  int did_submit_compositor_frame_count_ = 0;
  int did_not_produce_count_ = 0;
  int last_frame_skipped_reason_ = -1;
  int last_did_not_produce_has_damage_ = -1;
  bool gpu_context_created_ = false;
  bool raster_context_created_ = false;
  bool shared_image_interface_available_ = false;
  bool compositor_frame_submitted_ = false;
  bool viz_display_created_ = false;
  bool skia_gpu_reached_ = false;
  bool copy_output_requested_ = false;
  bool copy_output_png_requested_ = false;
  bool copy_output_raw_requested_ = false;
  bool copy_output_gpu_requested_ = false;
  bool copy_output_completed_ = false;
  bool copy_output_succeeded_ = false;
  std::vector<uint8_t> copy_output_png_;
  LiveRawFrameOutput copy_output_raw_frame_;
  LiveGpuFrameOutput copy_output_gpu_frame_;
  std::string copy_output_failure_;
  std::string failure_reason_;
};

struct StandaloneMouseInputEventForRenderer {
  int type = 0;
  float x = 0.0f;
  float y = 0.0f;
  int button = 0;
  int modifiers = 0;
  int click_count = 0;
};

struct StandaloneKeyboardInputEventForRenderer {
  int type = 0;
  int key = 0;
  std::string text;
  int modifiers = 0;
};

struct StandaloneDomMutationForRenderer {
  int type = 0;
  std::string element_id;
  std::string name;
  std::string value;
};

struct LiveFramePaintProbeCache {
  DummyPageHolder* holder = nullptr;
  Persistent<ChromeClient> chrome_client;
  std::unique_ptr<StandaloneCcLayerHost> cc_layer_host;
  bool cc_host_created = false;
  bool cc_attach_attempted = false;
  bool cc_root_layer_attached = false;
  bool cc_commit_requested = false;
  bool cc_frame_sink_requested = false;
  bool cc_frame_sink_bound = false;
  bool cc_compositor_frame_submitted = false;
  bool cc_gpu_context_created = false;
  bool cc_raster_context_created = false;
  bool cc_shared_image_interface_available = false;
  bool cc_viz_display_created = false;
  bool cc_skia_gpu_reached = false;
  gfx::Size cc_submitted_output_size;
  gfx::Size cc_viz_display_output_size;
  bool copy_output_raw_requested = false;
  bool copy_output_png_requested = false;
  bool copy_output_gpu_requested = false;
  bool copy_output_gpu_prepare_requested = false;
  bool copy_output_gpu_prepare_pending = false;
  bool copy_output_gpu_use_vulkan_offscreen = false;
  bool copy_output_gpu_use_d3d12_offscreen = false;
  bool copy_output_png_completed = false;
  bool copy_output_png_succeeded = false;
  std::vector<uint8_t> copy_output_png;
  LiveRawFrameOutput copy_output_raw_frame;
  LiveGpuFrameOutput copy_output_gpu_frame;
  std::string copy_output_failure;
  int cc_commit_count = 0;
  std::string cc_attach_failure_reason;
  std::string cc_frame_sink_failure_reason;
  LiveFramePaintProbeResult result;
  std::string body_html;
  std::string requested_element_attributes_serialized;
  std::unordered_map<std::string, std::string>
      requested_element_attributes_by_id_and_name;
  bool element_attributes_changed_since_probe = false;
  std::unordered_map<std::string, OriginalElementAttributeValue>
      original_element_attribute_values;
  std::unordered_map<std::string, std::string>
      applied_element_attributes_by_id_and_name;
  std::string requested_hovered_element_id;
  std::string requested_active_element_id;
  bool requested_interaction_state = false;
  bool requested_pointer_state = false;
  float requested_pointer_x = 0.0f;
  float requested_pointer_y = 0.0f;
  bool requested_pointer_pressed = false;
  int requested_pointer_event_type = 0;
  std::vector<StandaloneMouseInputEventForRenderer>
      requested_mouse_input_events;
  bool mouse_input_events_consumed = false;
  bool mouse_input_events_dispatched = false;
  int mouse_input_event_dispatch_count = 0;
  std::string mouse_input_status = "not_requested";
  std::vector<StandaloneKeyboardInputEventForRenderer>
      requested_keyboard_input_events;
  bool keyboard_input_events_consumed = false;
  bool keyboard_input_events_dispatched = false;
  int keyboard_input_event_dispatch_count = 0;
  std::string keyboard_input_status = "not_requested";
  std::vector<StandaloneDomMutationForRenderer> requested_dom_mutations;
  bool dom_mutations_applied = false;
  int dom_mutation_apply_count = 0;
  bool pointer_state_applied = false;
  std::string pointer_state_status = "not_requested";
  std::string pointer_hit_element_id;
  std::string pointer_hit_element_tag;
  std::string pointer_hit_element_class;
  std::string pointer_hover_element_id;
  std::string pointer_hover_element_tag;
  std::string pointer_hover_element_class;
  bool pointer_focus_requested = false;
  bool pointer_focus_applied = false;
  std::string pointer_focus_status = "not_requested";
  std::string pointer_focused_element_id;
  std::string pointer_down_activation_element_id;
  DOMNodeId pointer_down_activation_node_id = kInvalidDOMNodeId;
  bool pointer_activation_requested = false;
  bool pointer_activation_applied = false;
  std::string pointer_activation_element_id;
  std::string pointer_activation_down_element_id;
  DOMNodeId pointer_activation_node_id = kInvalidDOMNodeId;
  DOMNodeId pointer_activation_down_node_id = kInvalidDOMNodeId;
  std::string pointer_activation_status = "not_requested";
  bool requested_wheel_scroll = false;
  float requested_wheel_x = 0.0f;
  float requested_wheel_y = 0.0f;
  float requested_wheel_delta_x = 0.0f;
  float requested_wheel_delta_y = 0.0f;
  bool wheel_scroll_base_captured = false;
  float wheel_scroll_base_x = 0.0f;
  float wheel_scroll_base_y = 0.0f;
  bool wheel_scroll_applied = false;
  bool wheel_scroll_changed = false;
  bool wheel_scroll_target_is_element = false;
  std::string wheel_scroll_target_element_id;
  float wheel_scroll_applied_x = 0.0f;
  float wheel_scroll_applied_y = 0.0f;
  float wheel_scroll_max_x = 0.0f;
  float wheel_scroll_max_y = 0.0f;
  std::string wheel_scroll_status = "not_requested";
  std::vector<LiveExportedDrawOp> exported_draw_ops;
  std::vector<LiveExportedChunkPropertyState> chunk_property_states;
  std::vector<std::string> chunk_stable_keys;
  std::vector<std::string> chunk_id_strings;
  std::vector<std::vector<LiveFinerCacheUnitDescriptor>>
      finer_cache_units_by_chunk;
  std::vector<LiveHitTestEntry> hit_test_entries;
  std::vector<LiveFormControlEntry> form_control_entries;
  std::vector<LiveBackdropFilterRegion> backdrop_filter_regions;
  std::vector<LiveScrollableElementEntry> scrollable_element_entries;
  std::vector<std::string> artifact_audit_lines;
  std::string raw_paint_artifact_audit_json;
  std::string sticky_position_diagnostics_json;
  bool compositor_root_layer_available = false;
  int compositor_layer_count = 0;
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
  float device_scale_factor = 1.0f;
  bool transparent_background = false;
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
  int active_animation_count = 0;
  bool needs_animation_timing_update = false;
  bool needs_lifecycle_update = false;
  bool needs_begin_frame = false;
  bool needs_output = false;
  double timing_total_ms = 0.0;
  double timing_input_setup_ms = 0.0;
  double timing_html_document_setup_ms = 0.0;
  double timing_style_update_ms = 0.0;
  double timing_layout_lifecycle_ms = 0.0;
  double timing_prepaint_and_paint_lifecycle_ms = 0.0;
  double timing_paint_artifact_generation_ms = 0.0;
  double timing_paint_artifact_audit_ms = 0.0;
  double timing_paint_artifact_extraction_ms = 0.0;
  double timing_cc_composite_ms = 0.0;
  double timing_cc_frame_sink_warmup_ms = 0.0;
  double timing_cc_root_preattach_ms = 0.0;
  double timing_cc_pending_update_ms = 0.0;
  double timing_cc_scheduler_run_loop_ms = 0.0;
  double timing_cc_submit_wait_ms = 0.0;
  double timing_cc_startup_prewarm_ms = 0.0;
  bool timing_cache_hit = false;
  bool timing_reused_live_document = false;
  bool timing_rebuilt_for_attributes = false;
  bool full_paint_artifact_audit = false;
  bool collect_frame_diagnostics = true;
  bool collect_backdrop_filter_metadata = true;
  bool trace_stages = false;
  std::string lifecycle_stop;
  ImageReachabilityDiagnostics image_reachability;
  ImagePaintIntoRectDiagnostics image_paint_into_rect;
  bool initialized = false;
};

bool RectsMatchForStandaloneRenderer(const gfx::Rect& a, const gfx::Rect& b) {
  return a.x() == b.x() && a.y() == b.y() && a.width() == b.width() &&
         a.height() == b.height();
}

std::unordered_map<uint64_t, std::unique_ptr<LiveFramePaintProbeCache>>&
ProbeCachesByInstance() {
  static auto* caches =
      new std::unordered_map<uint64_t, std::unique_ptr<LiveFramePaintProbeCache>>();
  return *caches;
}

uint64_t& CurrentProbeInstanceId() {
  static thread_local uint64_t instance_id = 0;
  return instance_id;
}

uint64_t& NextProbeInstanceId() {
  static uint64_t* next_id = new uint64_t(1);
  return *next_id;
}

LiveFramePaintProbeCache& DefaultProbeCache() {
  static LiveFramePaintProbeCache* cache = new LiveFramePaintProbeCache();
  return *cache;
}

LiveFramePaintProbeCache& ProbeCache() {
  const uint64_t instance_id = CurrentProbeInstanceId();
  if (!instance_id) {
    return DefaultProbeCache();
  }
  auto& caches = ProbeCachesByInstance();
  auto it = caches.find(instance_id);
  if (it == caches.end()) {
    it = caches
             .emplace(instance_id,
                      std::make_unique<LiveFramePaintProbeCache>())
             .first;
  }
  return *it->second;
}

void RunStandaloneMainThreadTasksForNavigationReset() {
  base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
  run_loop.RunUntilIdle();
}

void CollectStandaloneBlinkGarbageForNavigationReset() {
  ThreadState::Current()->CollectAllGarbageForTesting(
      ThreadState::StackState::kMayContainHeapPointers);
}

void ClearStandaloneFrameDiagnosticState(LiveFramePaintProbeCache& cache) {
  cache.result = LiveFramePaintProbeResult();
  cache.body_html.clear();
  cache.element_attributes_changed_since_probe = false;
  cache.original_element_attribute_values.clear();
  cache.applied_element_attributes_by_id_and_name.clear();
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.hit_test_entries.clear();
  cache.form_control_entries.clear();
  cache.backdrop_filter_regions.clear();
  cache.scrollable_element_entries.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
  cache.sticky_position_diagnostics_json.clear();
  cache.compositor_root_layer_available = false;
  cache.compositor_layer_count = 0;
  cache.cc_attach_attempted = false;
  cache.cc_root_layer_attached = false;
  cache.cc_commit_requested = false;
  cache.cc_frame_sink_requested = false;
  cache.cc_frame_sink_bound = false;
  cache.cc_compositor_frame_submitted = false;
  cache.cc_gpu_context_created = false;
  cache.cc_raster_context_created = false;
  cache.cc_shared_image_interface_available = false;
  cache.cc_viz_display_created = false;
  cache.cc_skia_gpu_reached = false;
  cache.cc_submitted_output_size = gfx::Size();
  cache.cc_viz_display_output_size = gfx::Size();
  cache.cc_commit_count = 0;
  cache.cc_attach_failure_reason.clear();
  cache.cc_frame_sink_failure_reason.clear();
  cache.initialized = false;
}

void ResetStandaloneLiveDocumentForFullHtmlReplacement(
    LiveFramePaintProbeCache& cache) {
  RunStandaloneMainThreadTasksForNavigationReset();
  cache.cc_layer_host.reset();
  RunStandaloneMainThreadTasksForNavigationReset();
  if (cache.holder) {
    cache.holder->RestoreMockOverlayScrollbarSettingsForTesting();
  }
  delete cache.holder;
  cache.holder = nullptr;
  RunStandaloneMainThreadTasksForNavigationReset();
  CollectStandaloneBlinkGarbageForNavigationReset();
  RunStandaloneMainThreadTasksForNavigationReset();
  ClearStandaloneFrameDiagnosticState(cache);
}

void DestroyProbeCacheInstance(uint64_t instance_id) {
  if (!instance_id) {
    return;
  }
  auto& caches = ProbeCachesByInstance();
  auto it = caches.find(instance_id);
  if (it == caches.end()) {
    return;
  }
  const uint64_t previous_instance_id = CurrentProbeInstanceId();
  CurrentProbeInstanceId() = instance_id;
  ResetStandaloneLiveDocumentForFullHtmlReplacement(*it->second);
  CurrentProbeInstanceId() = previous_instance_id == instance_id
                                 ? 0
                                 : previous_instance_id;
  caches.erase(it);
}

extern "C" void StandaloneRendererNoteImagePaintIntoRect(
    float dest_x,
    float dest_y,
    float dest_width,
    float dest_height,
    float content_x,
    float content_y,
    float content_width,
    float content_height,
    float snapped_dest_x,
    float snapped_dest_y,
    float snapped_dest_width,
    float snapped_dest_height,
    float src_x,
    float src_y,
    float src_width,
    float src_height,
    int image_width,
    int image_height,
    int interpolation_quality) {
  ImagePaintIntoRectDiagnostics& diagnostics =
      ProbeCache().image_paint_into_rect;
  diagnostics.called = true;
  ++diagnostics.count;
  diagnostics.dest_x = dest_x;
  diagnostics.dest_y = dest_y;
  diagnostics.dest_width = dest_width;
  diagnostics.dest_height = dest_height;
  diagnostics.content_x = content_x;
  diagnostics.content_y = content_y;
  diagnostics.content_width = content_width;
  diagnostics.content_height = content_height;
  diagnostics.snapped_dest_x = snapped_dest_x;
  diagnostics.snapped_dest_y = snapped_dest_y;
  diagnostics.snapped_dest_width = snapped_dest_width;
  diagnostics.snapped_dest_height = snapped_dest_height;
  diagnostics.src_x = src_x;
  diagnostics.src_y = src_y;
  diagnostics.src_width = src_width;
  diagnostics.src_height = src_height;
  diagnostics.image_width = image_width;
  diagnostics.image_height = image_height;
  diagnostics.interpolation_quality = interpolation_quality;
}

void ImportCopyOutputPngFromCcHostForStandaloneRenderer(
    LiveFramePaintProbeCache& cache) {
  if (!cache.cc_layer_host) {
    return;
  }
  cache.copy_output_png_completed =
      cache.cc_layer_host->copy_output_completed();
  cache.copy_output_png_succeeded =
      cache.cc_layer_host->copy_output_succeeded();
  cache.copy_output_png = cache.cc_layer_host->copy_output_png();
  cache.copy_output_raw_frame = cache.cc_layer_host->copy_output_raw_frame();
  cache.copy_output_gpu_frame = cache.cc_layer_host->copy_output_gpu_frame();
  cache.copy_output_failure = cache.cc_layer_host->copy_output_failure();
  if (cache.copy_output_png_completed) {
    cache.copy_output_png_requested = false;
    cache.copy_output_raw_requested = false;
    cache.copy_output_gpu_requested = false;
  }
}

void SyncStandaloneCcHostStateForStandaloneRenderer(
    LiveFramePaintProbeCache& cache) {
  if (!cache.cc_layer_host) {
    cache.cc_host_created = false;
    cache.cc_attach_attempted = false;
    cache.cc_root_layer_attached = false;
    cache.cc_commit_requested = false;
    cache.cc_frame_sink_requested = false;
    cache.cc_frame_sink_bound = false;
    cache.cc_compositor_frame_submitted = false;
    cache.cc_gpu_context_created = false;
    cache.cc_raster_context_created = false;
    cache.cc_shared_image_interface_available = false;
    cache.cc_viz_display_created = false;
    cache.cc_skia_gpu_reached = false;
    cache.cc_submitted_output_size = gfx::Size();
    cache.cc_viz_display_output_size = gfx::Size();
    cache.cc_commit_count = 0;
    cache.cc_frame_sink_failure_reason.clear();
    return;
  }

  cache.cc_host_created = cache.cc_layer_host->host_created();
  cache.cc_attach_attempted = cache.cc_layer_host->attach_attempted();
  cache.cc_root_layer_attached = cache.cc_layer_host->root_layer_attached();
  cache.cc_commit_requested = cache.cc_layer_host->commit_requested();
  cache.cc_frame_sink_requested = cache.cc_layer_host->frame_sink_requested();
  cache.cc_frame_sink_bound = cache.cc_layer_host->frame_sink_bound();
  cache.cc_compositor_frame_submitted =
      cache.cc_layer_host->compositor_frame_submitted();
  cache.cc_gpu_context_created = cache.cc_layer_host->gpu_context_created();
  cache.cc_raster_context_created =
      cache.cc_layer_host->raster_context_created();
  cache.cc_shared_image_interface_available =
      cache.cc_layer_host->shared_image_interface_available();
  cache.cc_viz_display_created = cache.cc_layer_host->viz_display_created();
  cache.cc_skia_gpu_reached = cache.cc_layer_host->skia_gpu_reached();
  cache.cc_submitted_output_size =
      cache.cc_layer_host->submitted_output_size();
  cache.cc_viz_display_output_size =
      cache.cc_layer_host->viz_display_output_size();
  cache.cc_commit_count = cache.cc_layer_host->commit_count();
  cache.cc_frame_sink_failure_reason =
      cache.cc_layer_host->frame_sink_failure_reason();
}

void SyncStandaloneCcTimingForStandaloneRenderer(
    LiveFramePaintProbeCache& cache) {
  if (!cache.cc_layer_host) {
    return;
  }
  cache.timing_cc_frame_sink_warmup_ms =
      cache.cc_layer_host->timing_frame_sink_warmup_ms();
  cache.timing_cc_root_preattach_ms =
      cache.cc_layer_host->timing_root_preattach_ms();
  cache.timing_cc_pending_update_ms =
      cache.cc_layer_host->timing_pending_update_ms();
  cache.timing_cc_scheduler_run_loop_ms =
      cache.cc_layer_host->timing_scheduler_run_loop_ms();
  cache.timing_cc_submit_wait_ms =
      cache.cc_layer_host->timing_submit_wait_ms();
}

bool PrewarmStandaloneCcFrameSinkForStandaloneRenderer(
    LiveFramePaintProbeCache& cache,
    const gfx::Size& viewport) {
  if (!cache.cc_layer_host) {
    cache.cc_layer_host = std::make_unique<StandaloneCcLayerHost>();
  }
  cache.cc_layer_host->SetTransparentBackground(cache.transparent_background);
  cache.cc_frame_sink_failure_reason.clear();
  const auto prewarm_start = StandaloneProbeClock::now();
  const bool host_ok = cache.cc_layer_host->EnsureHostForScheduler(
      viewport, cache.device_scale_factor, &cache.cc_frame_sink_failure_reason);
  const bool sink_ok =
      host_ok && cache.cc_layer_host->EnsureFrameSinkReadyForScheduler(
                     &cache.cc_frame_sink_failure_reason);
  cache.timing_cc_startup_prewarm_ms =
      StandaloneProbeElapsedMs(prewarm_start, StandaloneProbeClock::now());
  SyncStandaloneCcTimingForStandaloneRenderer(cache);
  SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  return sink_ok;
}

bool SubmitStandaloneBlinkCompositorStateToCcForStandaloneRenderer(
    LiveFramePaintProbeCache& cache,
    const char* before_stage,
    const char* after_stage) {
  SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  if (!cache.cc_layer_host || !cache.cc_layer_host->root_layer_attached()) {
    return false;
  }

  TraceLiveFrameProbeStage(before_stage);
  cache.cc_frame_sink_failure_reason.clear();
  if (cache.copy_output_gpu_use_vulkan_offscreen ||
      cache.copy_output_gpu_use_d3d12_offscreen) {
    cache.cc_layer_host->SetGpuOffscreenOutputMode(
        cache.copy_output_gpu_use_vulkan_offscreen,
        cache.copy_output_gpu_use_d3d12_offscreen);
  }
  if (cache.copy_output_png_requested || cache.copy_output_raw_requested ||
      cache.copy_output_gpu_requested) {
    if (cache.copy_output_gpu_requested) {
      cache.cc_layer_host->RequestNextGpuFrameOutput(
          cache.copy_output_gpu_use_vulkan_offscreen,
          cache.copy_output_gpu_use_d3d12_offscreen);
    } else {
      cache.cc_layer_host->RequestNextCopyOutput(
          cache.copy_output_png_requested, cache.copy_output_raw_requested,
          /*wants_gpu=*/false);
    }
  }
  const auto composite_start = StandaloneProbeClock::now();
  const bool submitted =
      cache.cc_layer_host->CompositeForTest(&cache.cc_frame_sink_failure_reason);
  cache.timing_cc_composite_ms +=
      StandaloneProbeElapsedMs(composite_start, StandaloneProbeClock::now());
  ImportCopyOutputPngFromCcHostForStandaloneRenderer(cache);
  SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  TraceLiveFrameProbeStage(after_stage);
  return submitted;
}

class StandaloneCompositorChromeClient final : public EmptyChromeClient {
 public:
  explicit StandaloneCompositorChromeClient(LiveFramePaintProbeCache* cache)
      : cache_(cache) {}

  void AttachRootLayer(scoped_refptr<cc::Layer> layer,
                       LocalFrame* local_root) override {
    if (!cache_) {
      return;
    }
    if (!cache_->cc_layer_host) {
      cache_->cc_layer_host = std::make_unique<StandaloneCcLayerHost>();
    }
    cache_->cc_layer_host->SetTransparentBackground(
        cache_->transparent_background);
    cache_->cc_attach_failure_reason.clear();
    const bool attached = cache_->cc_layer_host->AttachRootLayer(
        std::move(layer), gfx::Size(cache_->viewport_width,
                                    cache_->viewport_height),
        cache_->device_scale_factor,
        &cache_->cc_attach_failure_reason);
    SyncStandaloneCcHostStateForStandaloneRenderer(*cache_);
    cache_->cc_root_layer_attached = attached;
  }

  cc::AnimationHost* GetCompositorAnimationHost(LocalFrame& frame) const override {
    return cache_ && cache_->cc_layer_host ? cache_->cc_layer_host->animation_host()
                                           : nullptr;
  }

 private:
  LiveFramePaintProbeCache* cache_;
};

void TraceLiveFrameProbeStage(const char* stage) {
  HtmlCssRendererStandaloneSetCrashBreadcrumb(stage);
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

int LifecycleStateForStandaloneRenderer(const Document* document) {
  return document ? static_cast<int>(document->Lifecycle().GetState()) : -1;
}

bool IsPrePaintCleanForStandaloneRenderer(const Document* document) {
  return document &&
         document->Lifecycle().GetState() >= DocumentLifecycle::kPrePaintClean;
}

void TraceLiveFrameProbeLifecycleState(const char* label,
                                       Document* document,
                                       LocalFrame* frame,
                                       LocalFrameView* frame_view) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.trace_stages) {
    return;
  }

  Document* frame_document = frame ? frame->GetDocument() : nullptr;
  LocalFrame* view_frame = frame_view ? &frame_view->GetFrame() : nullptr;
  char buffer[512];
  std::snprintf(
      buffer, sizeof(buffer),
      "%s doc=%p doc_state=%d doc_needs_style=%d frame=%p frame_doc=%p "
      "frame_doc_state=%d view=%p view_frame=%p view_needs_layout=%d",
      label ? label : "lifecycle", static_cast<void*>(document),
      LifecycleStateForStandaloneRenderer(document),
      document && document->NeedsLayoutTreeUpdate() ? 1 : 0,
      static_cast<void*>(frame), static_cast<void*>(frame_document),
      LifecycleStateForStandaloneRenderer(frame_document),
      static_cast<void*>(frame_view), static_cast<void*>(view_frame),
      frame_view && frame_view->NeedsLayout() ? 1 : 0);
  TraceLiveFrameProbeStage(buffer);
}

std::string BlinkStringToStdStringForStandaloneRenderer(const String& value);

Element* HitTestElementAtViewportPointForStandaloneRenderer(
    LocalFrameView& frame_view,
    float x,
    float y,
    HitTestRequest::HitTestRequestType hit_type) {
  LocalFrame& frame = frame_view.GetFrame();
  if (!frame.GetDocument() || !frame.View()) {
    return nullptr;
  }

  const gfx::PointF root_point(x, y);
  const HitTestLocation location(frame_view.ConvertFromRootFrame(root_point));
  const HitTestResult result = frame.GetEventHandler().HitTestResultAtLocation(
      location, hit_type, nullptr, /*no_lifecycle_update=*/true);
  Element* hit_element = result.InnerPossiblyPseudoElement();
  if (!hit_element && result.InnerNode()) {
    hit_element = DynamicTo<Element>(result.InnerNode());
    if (!hit_element) {
      hit_element = result.InnerNode()->parentElement();
    }
  }
  return hit_element;
}

PaintLayerScrollableArea* ScrollableAreaForElementForStandaloneRenderer(
    Element& element) {
  auto* box = DynamicTo<LayoutBox>(element.GetLayoutObject());
  if (!box || !box->IsScrollContainer()) {
    return nullptr;
  }
  PaintLayer* layer = box->EnclosingLayer();
  return box->GetScrollableArea()
             ? box->GetScrollableArea()
             : (layer ? layer->GetScrollableArea() : nullptr);
}

std::string ElementIdForStandaloneRenderer(Element& element) {
  return BlinkStringToStdStringForStandaloneRenderer(
      String(element.GetIdAttribute()));
}

bool ApplyRelativeWheelDeltaToScrollableAreaForStandaloneRenderer(
    PaintLayerScrollableArea& scrollable_area,
    float delta_x,
    float delta_y) {
  scrollable_area.UpdateAfterOverflowRecalc();
  const ScrollOffset current_offset = scrollable_area.GetScrollOffset();
  const ScrollOffset requested_offset(current_offset.x() + delta_x,
                                      current_offset.y() + delta_y);
  const ScrollOffset clamped_offset =
      scrollable_area.ClampScrollOffset(requested_offset);
  if (std::abs(clamped_offset.x() - current_offset.x()) <= 0.001f &&
      std::abs(clamped_offset.y() - current_offset.y()) <= 0.001f) {
    return false;
  }
  return scrollable_area.SetScrollOffset(
      clamped_offset, mojom::blink::ScrollType::kProgrammatic,
      cc::ScrollSourceType::kRelativeScroll,
      mojom::blink::ScrollBehavior::kInstant);
}

bool TryApplyWheelScrollToOverflowElementForStandaloneRenderer(
    LocalFrameView& frame_view) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.wheel_scroll_target_is_element = false;
  cache.wheel_scroll_target_element_id.clear();
  cache.wheel_scroll_applied_x = 0.0f;
  cache.wheel_scroll_applied_y = 0.0f;
  cache.wheel_scroll_max_x = 0.0f;
  cache.wheel_scroll_max_y = 0.0f;
  if (!cache.requested_wheel_scroll) {
    return false;
  }

  Document* document = frame_view.GetFrame().GetDocument();
  if (!document) {
    cache.wheel_scroll_status = "document_missing_for_wheel_hit_test";
    return false;
  }

  Element* hit_element = HitTestElementAtViewportPointForStandaloneRenderer(
      frame_view, cache.requested_wheel_x, cache.requested_wheel_y,
      HitTestRequest::kMove);
  if (!hit_element) {
    cache.wheel_scroll_status = "no_wheel_hit_test_target";
    return false;
  }

  for (Element* element = hit_element; element;
       element = element->parentElement()) {
    if (element == document->body() || element == document->documentElement()) {
      continue;
    }
    PaintLayerScrollableArea* scrollable_area =
        ScrollableAreaForElementForStandaloneRenderer(*element);
    if (!scrollable_area) {
      continue;
    }
    const bool changed = ApplyRelativeWheelDeltaToScrollableAreaForStandaloneRenderer(
        *scrollable_area, cache.requested_wheel_delta_x,
        cache.requested_wheel_delta_y);
    const ScrollOffset maximum = scrollable_area->MaximumScrollOffset();
    const gfx::PointF applied_position = scrollable_area->ScrollPosition();
    cache.wheel_scroll_target_is_element = true;
    cache.wheel_scroll_target_element_id =
        ElementIdForStandaloneRenderer(*element);
    cache.wheel_scroll_applied_x = applied_position.x();
    cache.wheel_scroll_applied_y = applied_position.y();
    cache.wheel_scroll_max_x = maximum.x();
    cache.wheel_scroll_max_y = maximum.y();
    if (changed) {
      cache.wheel_scroll_applied = true;
      cache.wheel_scroll_changed = true;
      cache.wheel_scroll_status =
          "applied_to_element_scrollable_area_relative_instant";
      return true;
    }
    cache.wheel_scroll_status =
        "element_scrollable_area_cannot_consume_delta";
  }

  return false;
}

void ApplyDocumentScrollOffsetForStandaloneRenderer(LocalFrameView& frame_view,
                                                    bool apply_wheel_scroll) {
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
  ScrollableArea* viewport = frame_view.LayoutViewport();
  if (!viewport) {
    viewport = frame_view.GetScrollableArea();
  }
  if (!viewport) {
    cache.scroll_offset_status = "frame_scrollable_area_missing";
    if (apply_wheel_scroll && cache.requested_wheel_scroll &&
        !cache.wheel_scroll_applied) {
      cache.wheel_scroll_status = "frame_scrollable_area_missing";
    }
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
  const bool should_apply_requested_document_scroll =
      cache.scroll_offset_requested &&
      !(apply_wheel_scroll && cache.requested_wheel_scroll &&
        cache.wheel_scroll_applied);
  if (should_apply_requested_document_scroll) {
    const ScrollOffset requested_offset = viewport->ScrollPositionToOffset(
        gfx::PointF(cache.requested_scroll_x, cache.requested_scroll_y));
    const ScrollOffset clamped_offset =
        viewport->ClampScrollOffset(requested_offset);
    cache.scroll_offset_changed = viewport->SetScrollOffset(
        clamped_offset, mojom::blink::ScrollType::kProgrammatic,
        cc::ScrollSourceType::kAbsoluteScroll,
        mojom::blink::ScrollBehavior::kInstant);
    // The standalone bridge may apply an explicit document scroll state after
    // a previous frame's paint properties were built. Rebuild Blink's scroll
    // paint properties even if the ScrollableArea reports no offset delta
    // because the requested state matches the underlying scroller.
    frame_view.SetNeedsPaintPropertyUpdate();
    cache.scroll_offset_status = "applied_to_frame_scrollable_area";
  } else if (cache.scroll_offset_requested && cache.requested_wheel_scroll &&
             cache.wheel_scroll_applied) {
    cache.scroll_offset_status =
        "skipped_absolute_document_scroll_after_wheel_applied";
  }
  if (apply_wheel_scroll && cache.requested_wheel_scroll &&
      !cache.wheel_scroll_applied) {
    TryApplyWheelScrollToOverflowElementForStandaloneRenderer(frame_view);
  }
  if (apply_wheel_scroll && cache.requested_wheel_scroll &&
      !cache.wheel_scroll_applied) {
    if (!cache.wheel_scroll_base_captured) {
      const ScrollOffset base_offset = viewport->GetScrollOffset();
      cache.wheel_scroll_base_x = base_offset.x();
      cache.wheel_scroll_base_y = base_offset.y();
      cache.wheel_scroll_base_captured = true;
    }
    const ScrollOffset requested_offset =
        ScrollOffset(cache.wheel_scroll_base_x + cache.requested_wheel_delta_x,
                     cache.wheel_scroll_base_y + cache.requested_wheel_delta_y);
    const ScrollOffset clamped_offset =
        viewport->ClampScrollOffset(requested_offset);
    const ScrollOffset before_wheel_offset = viewport->GetScrollOffset();
    viewport->SetScrollOffset(
        clamped_offset, mojom::blink::ScrollType::kProgrammatic,
        cc::ScrollSourceType::kRelativeScroll,
        mojom::blink::ScrollBehavior::kInstant);
    cache.wheel_scroll_changed =
        cache.wheel_scroll_changed ||
        viewport->GetScrollOffset() != before_wheel_offset;
    cache.scroll_offset_changed =
        cache.scroll_offset_changed || cache.wheel_scroll_changed;
    cache.wheel_scroll_applied = true;
    cache.wheel_scroll_target_is_element = false;
    cache.wheel_scroll_target_element_id.clear();
    cache.wheel_scroll_applied_x = viewport->ScrollPosition().x();
    cache.wheel_scroll_applied_y = viewport->ScrollPosition().y();
    cache.wheel_scroll_max_x = maximum.x();
    cache.wheel_scroll_max_y = maximum.y();
    cache.wheel_scroll_status =
        "applied_to_frame_scrollable_area_relative_instant";
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
  // Real cc::DrawLooper no longer exposes layer iteration. Keep this temporary
  // retained bridge from adding a non-upstream cc accessor; the final cc path
  // should own draw looper playback directly.
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

void CopyRRectRadiiForStandaloneRenderer(const SkRRect& rrect,
                                         LiveExportedDrawOp& exported) {
  for (size_t i = 0; i < exported.corner_radii.size(); ++i) {
    exported.corner_radii[i] =
        rrect.radii(static_cast<SkRRect::Corner>(i));
  }
  exported.radius_x = exported.corner_radii[0].x();
  exported.radius_y = exported.corner_radii[0].y();
}

void AppendRRectOp(const SkRRect& rrect,
                   float translate_x,
                   float translate_y,
                   SkScalar stroke_width,
                   const SkColor4f& color,
                   bool stroke,
                   std::vector<LiveExportedDrawOp>& exported_draw_ops,
                   const cc::PaintFlags* flags = nullptr) {
  const SkRect& rect = rrect.getBounds();
  const float width = rect.width();
  const float height = rect.height();
  if (width <= 0.0f || height <= 0.0f) {
    return;
  }
  LiveExportedDrawOp exported;
  exported.type = stroke ? 6 : 5;
  exported.x = translate_x + rect.x();
  exported.y = translate_y + rect.y();
  exported.width = width;
  exported.height = height;
  CopyRRectRadiiForStandaloneRenderer(rrect, exported);
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
  CopyRRectRadiiForStandaloneRenderer(rrect, exported);
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

bool AppendSkRectOpWithFlags(
    const SkRect& rect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!rect.isFinite()) {
    return false;
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
      return true;
    }
    return false;
  }
  if (flags.getStyle() == cc::PaintFlags::kStroke_Style) {
    AppendStrokeRectOp(translate_x + rect.x(), translate_y + rect.y(),
                       rect.width(), rect.height(), flags.getStrokeWidth(),
                       flags.getColor4f(), exported_draw_ops, &flags);
    return true;
  }
  AppendSkRectFillOp(rect, translate_x, translate_y, flags.getColor4f(),
                     exported_draw_ops);
  return true;
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

bool AppendSkRRectOpWithFlags(
    const SkRRect& rrect,
    float translate_x,
    float translate_y,
    const cc::PaintFlags& flags,
    std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  const SkRect rect = rrect.rect();
  if (!rect.isFinite()) {
    return false;
  }
  if (flags.HasShader() && flags.getStyle() != cc::PaintFlags::kStroke_Style) {
    std::vector<uint8_t> shader_bytes = SerializeShaderBytes(flags);
    if (!shader_bytes.empty()) {
      LiveExportedDrawOp exported;
      exported.type = 20;
      exported.x = translate_x + rect.x();
      exported.y = translate_y + rect.y();
      exported.width = rect.width();
      exported.height = rect.height();
      CopyRRectRadiiForStandaloneRenderer(rrect, exported);
      AppendSkColor(exported, flags.getColor4f());
      exported.shader_bytes = std::move(shader_bytes);
      exported_draw_ops.push_back(std::move(exported));
      return true;
    }
    return false;
  }
  AppendRRectOp(rrect, translate_x, translate_y, flags.getStrokeWidth(),
                flags.getColor4f(),
                flags.getStyle() == cc::PaintFlags::kStroke_Style,
                exported_draw_ops, &flags);
  return true;
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

  SkPath local_path = path.makeOffset(-bounds.x(), -bounds.y());
  const size_t path_byte_count = local_path.writeToMemory(nullptr);
  if (path_byte_count == 0) {
    return;
  }

  LiveExportedDrawOp exported;
  exported.type = 21;
  exported.x = translate_x + bounds.x();
  exported.y = translate_y + bounds.y();
  exported.width = bounds.width();
  exported.height = bounds.height();
  exported.font_size = flags.getStyle() == cc::PaintFlags::kStroke_Style
                           ? std::max<SkScalar>(1.0f, flags.getStrokeWidth())
                           : 0.0f;
  AppendSkColor(exported, flags.getColor4f());
  AppendStrokeStyle(flags, exported);
  AppendDrawLooperLayers(flags, exported);
  exported.path_bytes.resize(path_byte_count);
  local_path.writeToMemory(exported.path_bytes.data());

  if (flags.HasShader()) {
    exported.shader_bytes = SerializeShaderBytes(flags);
  }
  exported.path_effect_bytes = SerializePathEffectBytes(flags);

  exported_draw_ops.push_back(std::move(exported));
}
bool AppendTextBlobOp(const cc::DrawTextBlobOp& text_op,
                      int fallback_x,
                      int fallback_y,
                      int fallback_width,
                      int fallback_height,
                      std::vector<LiveExportedDrawOp>& exported_draw_ops) {
  if (!text_op.blob) {
    return false;
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
    return true;
  }
  return false;
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

std::string SamplingOptionsStringForStandaloneRenderer(
    const SkSamplingOptions& sampling) {
  if (sampling.isAniso()) {
    return "aniso=" + std::to_string(sampling.maxAniso);
  }
  if (sampling.useCubic) {
    return "cubic=B" + std::to_string(sampling.cubic.B) + ",C" +
           std::to_string(sampling.cubic.C);
  }
  return std::string("filter=") +
         (sampling.filter == SkFilterMode::kLinear ? "linear" : "nearest") +
         ",mipmap=" +
         (sampling.mipmap == SkMipmapMode::kLinear
              ? "linear"
              : sampling.mipmap == SkMipmapMode::kNearest ? "nearest"
                                                          : "none");
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
        if (!AppendSkRectOpWithFlags(
                static_cast<const cc::DrawRectOp&>(op).rect, translate_x,
                translate_y, static_cast<const cc::DrawRectOp&>(op).flags,
                exported_draw_ops)) {
          mark_unsupported(op);
        }
        break;
      case cc::PaintOpType::kDrawArc: {
        mark_unsupported(op);
        break;
      }
      case cc::PaintOpType::kDrawArcLite: {
        mark_unsupported(op);
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
        if (!AppendSkRRectOpWithFlags(
                static_cast<const cc::DrawRRectOp&>(op).rrect, translate_x,
                translate_y, static_cast<const cc::DrawRRectOp&>(op).flags,
                exported_draw_ops)) {
          mark_unsupported(op);
        }
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
        if (!AppendTextBlobOp(static_cast<const cc::DrawTextBlobOp&>(op),
                              static_cast<int>(translate_x),
                              static_cast<int>(translate_y), fallback_width,
                              fallback_height, exported_draw_ops)) {
          mark_unsupported(op);
        }
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
      const DisplayItem& item = display_items[item_index];
      const auto* drawing =
          DynamicTo<DrawingDisplayItem>(item);
      const auto* scrollbar =
          DynamicTo<ScrollbarDisplayItem>(item);
      if (!drawing && !scrollbar) {
        continue;
      }
      const size_t exported_op_begin = exported_draw_ops.size();
      if (drawing) {
        if (!AppendPaintRecordExtractedOps(
                drawing->GetPaintRecord(), 0.0f, 0.0f, viewport_width,
                viewport_height, exported_draw_ops, diagnostics,
                projection_has_non_translation)) {
          complete = false;
        }
      } else {
        cc::PaintRecord scrollbar_record = scrollbar->Paint();
        if (!AppendPaintRecordExtractedOps(
                scrollbar_record, 0.0f, 0.0f, viewport_width,
                viewport_height, exported_draw_ops, diagnostics,
                projection_has_non_translation)) {
          complete = false;
        }
      }
      const DisplayItemClientId item_client_id =
          item.ClientId();
      for (size_t op_index = exported_op_begin;
           op_index < exported_draw_ops.size(); ++op_index) {
        LiveExportedDrawOp& op = exported_draw_ops[op_index];
        op.source_chunk_index = static_cast<int>(chunk_index);
        op.source_display_item_index = static_cast<int>(item_index);
        op.source_display_item_client_id =
            static_cast<uint64_t>(item_client_id);
        op.source_display_item_client_id_valid =
            item_client_id != kInvalidDisplayItemClientId;
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

bool ExportBackdropFilterOperationsForStandaloneRenderer(
    const CompositorFilterOperations* filters,
    std::vector<LiveExportedFilterOperation>& operations,
    float* blur_radius_css_px,
    bool* unsupported_filter_op) {
  operations.clear();
  if (blur_radius_css_px) {
    *blur_radius_css_px = 0.0f;
  }
  if (unsupported_filter_op) {
    *unsupported_filter_op = false;
  }
  if (!filters) {
    return false;
  }

  bool has_supported_operation = false;
  for (const cc::FilterOperation& operation :
       filters->AsCcFilterOperations().operations()) {
    LiveExportedFilterOperation out;
    switch (operation.type()) {
      case cc::FilterOperation::BLUR:
        out.type = kStandaloneBackdropFilterOperationBlur;
        out.amount = operation.amount();
        if (blur_radius_css_px) {
          *blur_radius_css_px =
              std::max(*blur_radius_css_px, operation.amount());
        }
        break;
      case cc::FilterOperation::BRIGHTNESS:
        out.type = kStandaloneBackdropFilterOperationBrightness;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::CONTRAST:
        out.type = kStandaloneBackdropFilterOperationContrast;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::SATURATE:
        out.type = kStandaloneBackdropFilterOperationSaturate;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::GRAYSCALE:
        out.type = kStandaloneBackdropFilterOperationGrayscale;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::SEPIA:
        out.type = kStandaloneBackdropFilterOperationSepia;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::INVERT:
        out.type = kStandaloneBackdropFilterOperationInvert;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::HUE_ROTATE:
        out.type = kStandaloneBackdropFilterOperationHueRotate;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::OPACITY:
        out.type = kStandaloneBackdropFilterOperationOpacity;
        out.amount = operation.amount();
        break;
      case cc::FilterOperation::DROP_SHADOW:
      case cc::FilterOperation::COLOR_MATRIX:
      case cc::FilterOperation::ZOOM:
      case cc::FilterOperation::REFERENCE:
      case cc::FilterOperation::SATURATING_BRIGHTNESS:
      case cc::FilterOperation::ALPHA_THRESHOLD:
      case cc::FilterOperation::OFFSET:
        if (unsupported_filter_op) {
          *unsupported_filter_op = true;
        }
        continue;
    }

    has_supported_operation = true;
    if (operations.size() >= 8u) {
      if (unsupported_filter_op) {
        *unsupported_filter_op = true;
      }
      continue;
    }
    operations.push_back(out);
  }
  return has_supported_operation;
}

void CollectBackdropFilterRegionsForStandaloneRenderer(
    const PaintArtifact& artifact,
    std::vector<LiveBackdropFilterRegion>& regions) {
  regions.clear();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  std::vector<uint64_t> seen_effect_nodes;
  for (wtf_size_t chunk_index = 0; chunk_index < chunks.size();
       ++chunk_index) {
    const PaintChunk& chunk = chunks[chunk_index];
    const PropertyTreeState chunk_state = chunk.properties.Unalias();
    const EffectPaintPropertyNode& effect = chunk_state.Effect();
    const CompositorFilterOperations* backdrop_filter =
        effect.BackdropFilter();
    if (!backdrop_filter) {
      continue;
    }
    const uint64_t effect_node_id = reinterpret_cast<uintptr_t>(&effect);
    if (std::find(seen_effect_nodes.begin(), seen_effect_nodes.end(),
                  effect_node_id) != seen_effect_nodes.end()) {
      continue;
    }
    seen_effect_nodes.push_back(effect_node_id);

    LiveBackdropFilterRegion region;
    region.opacity = effect.Opacity();
    float blur_radius = 0.0f;
    bool unsupported_filter_op = false;
    const bool has_supported_filter =
        ExportBackdropFilterOperationsForStandaloneRenderer(
            backdrop_filter, region.filter_operations, &blur_radius,
            &unsupported_filter_op);
    region.blur_radius_css_px = blur_radius;
    if (!has_supported_filter || unsupported_filter_op) {
      region.flags |= kStandaloneBackdropFilterUnsupportedFilterOp;
    }
    if (effect.BlendMode() != SkBlendMode::kSrcOver) {
      region.flags |= kStandaloneBackdropFilterUnsupportedMaskOrBlend;
    }
    if (effect.BackdropMaskElementId()) {
      region.flags |= kStandaloneBackdropFilterUnsupportedMaskOrBlend;
    }

    bool projection_has_non_translation = false;
    const gfx::Transform projection = DirectTransformToRootForStandaloneRenderer(
        chunk_state, nullptr, &projection_has_non_translation);
    if (!projection.Is2dTransform() || projection_has_non_translation) {
      region.flags |= kStandaloneBackdropFilterUnsupportedTransform;
    }

    const SkPath& backdrop_bounds_path = effect.BackdropFilterBounds();
    SkRect backdrop_rect;
    SkRRect backdrop_rrect;
    const bool is_rect = backdrop_bounds_path.isRect(&backdrop_rect);
    const bool is_rrect = !is_rect && backdrop_bounds_path.isRRect(&backdrop_rrect);
    if (!is_rect && !is_rrect) {
      region.flags |= kStandaloneBackdropFilterUnsupportedComplexClip;
    }
    const gfx::RectF mapped_bounds =
        projection.MapRect(gfx::SkRectToRectF(backdrop_bounds_path.getBounds()));
    region.x = mapped_bounds.x();
    region.y = mapped_bounds.y();
    region.width = mapped_bounds.width();
    region.height = mapped_bounds.height();
    if (is_rrect) {
      region.flags |= kStandaloneBackdropFilterRoundedRect;
      region.border_radius_top_left = backdrop_rrect.radii(SkRRect::kUpperLeft_Corner).x();
      region.border_radius_top_right =
          backdrop_rrect.radii(SkRRect::kUpperRight_Corner).x();
      region.border_radius_bottom_right =
          backdrop_rrect.radii(SkRRect::kLowerRight_Corner).x();
      region.border_radius_bottom_left =
          backdrop_rrect.radii(SkRRect::kLowerLeft_Corner).x();
    }
    if (region.width > 0.0f && region.height > 0.0f) {
      regions.push_back(std::move(region));
    }
  }
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
        entry.tag_name = BlinkStringToStdStringForStandaloneRenderer(
            String(element->localName()));
        std::transform(entry.tag_name.begin(), entry.tag_name.end(),
                       entry.tag_name.begin(), [](char c) {
                         return static_cast<char>(std::tolower(
                             static_cast<unsigned char>(c)));
                       });
        entry.data_godot_action = BlinkStringToStdStringForStandaloneRenderer(
            element->getAttribute(AtomicString("data-godot-action")));
        entry.paint_client_id = element->GetLayoutObject()->Id();
        entry.x = rect.x();
        entry.y = rect.y();
        entry.width = rect.width();
        entry.height = rect.height();
        entry.disabled = element->IsDisabledFormControl();
        entry.editable =
            element->IsTextControl() ||
            element->FastHasAttribute(html_names::kContenteditableAttr);
        if (auto* input = DynamicTo<HTMLInputElement>(element)) {
          entry.checked = input->Checked();
        }
        entry.focused = element->GetDocument().FocusedElement() == element;
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
  const CSSPropertyValueSet* inline_style = element->InlineStyle();
  json << ",\"inline_style_present\":"
       << (inline_style ? "true" : "false")
       << ",\"inline_style_property_count\":"
       << (inline_style ? inline_style->PropertyCount() : 0);
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
  if (!card && body) {
    card = FindElementByAttributeValueForStandaloneRenderer(
        *body, AtomicString("id"), AtomicString("card"));
  }
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
  size_t style_element_count = 0;
  size_t style_element_text_length = 0;
  size_t style_element_sheet_count = 0;
  size_t generic_style_tag_count = 0;
  for (HTMLStyleElement& style_element :
       Traversal<HTMLStyleElement>::DescendantsOf(document)) {
    ++style_element_count;
    style_element_text_length +=
        static_cast<size_t>(style_element.TextFromChildren().length());
    if (style_element.sheet()) {
      ++style_element_sheet_count;
    }
  }
  for (Element& element : Traversal<Element>::DescendantsOf(document)) {
    if (element.HasTagName(html_names::kStyleTag)) {
      ++generic_style_tag_count;
    }
  }
  const ActiveStyleSheetVector active_style_sheets =
      document.GetStyleEngine().ActiveStyleSheetsForInspector();
  std::ostringstream json;
  json << "{\"document\":" << DocumentEvidenceJsonForStandaloneRenderer(document)
       << ",\"style_sheets\":{\"style_element_count\":"
       << style_element_count
       << ",\"generic_style_tag_count\":" << generic_style_tag_count
       << ",\"style_element_text_length\":" << style_element_text_length
       << ",\"style_element_sheet_count\":" << style_element_sheet_count
       << ",\"active_style_sheet_count\":" << active_style_sheets.size()
       << "}"
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
    bool has_transform_related_ancestor = false;
    for (const LayoutObject* current = layout_object;
         current && current != layout_object->View();
         current = current->Parent()) {
      if (current->HasTransformRelatedProperty()) {
        has_transform_related_ancestor = true;
        break;
      }
    }
    const gfx::Rect absolute_bounding_box_rect =
        layout_object->AbsoluteBoundingBoxRect();
    json << ",\"box_geometry\":{\"stitched_size\":"
         << PhysicalSizeJsonForStandaloneRenderer(box->StitchedSize())
         << ",\"border_box_rect\":"
         << PhysicalRectJsonForStandaloneRenderer(box->PhysicalBorderBoxRect());
    if (has_transform_related_ancestor) {
      json << ",\"local_to_root_offset\":null"
           << ",\"local_to_root_offset_reason\":\"transform_related_ancestor\"";
    } else {
      const PhysicalOffset local_to_root_offset =
          layout_object->OffsetFromAncestor(layout_object->View());
      json << ",\"local_to_root_offset\":"
           << PhysicalOffsetJsonForStandaloneRenderer(local_to_root_offset);
    }
    json << ",\"absolute_bounding_box_rect\":"
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
       << ",\"device_scale_factor\":" << cache.device_scale_factor
       << ",\"media_values\":{\"viewport_width\":" << cache.viewport_width
       << ",\"viewport_height\":" << cache.viewport_height
       << ",\"device_width\":" << cache.viewport_width
       << ",\"device_height\":" << cache.viewport_height
       << ",\"orientation\":" << JsonStringForStandaloneRenderer(orientation)
       << ",\"hover\":\"hover\""
       << ",\"pointer\":\"fine\""
       << ",\"any_hover\":\"hover\""
       << ",\"any_pointer\":\"fine\""
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
  std::string element_id;
  std::string debug_id;
  std::string type_attr;
  std::string name_attr;
  std::string min_attr;
  std::string max_attr;
  std::string step_attr;
  std::string input_name;
  std::string value_attr;
  std::string live_value;
  std::vector<std::string> selected_values;
  std::string element_interface;
  std::string computed_display;
  std::string layout_object_type;
  std::string parent_layout_object_type;
  std::string first_missing_stage;
  std::string standalone_support_status;
  std::string unsupported_closure_boundary;
  float absolute_x = 0.0f;
  float absolute_y = 0.0f;
  float absolute_width = 0.0f;
  float absolute_height = 0.0f;
  bool layout_object_present = false;
  bool absolute_bounds_present = false;
  bool is_connected = false;
  bool checked = false;
  bool focused = false;
  bool radio_group_scope_present = false;
  bool radio_group_checked = false;
  bool user_agent_shadow_root_present = false;
  bool text_control_inner_editor_present = false;
  bool placeholder_attr_present = false;
  bool placeholder_visible = false;
  unsigned selection_start = 0;
  unsigned selection_end = 0;
  bool selection_offsets_present = false;
  int user_agent_shadow_child_count = 0;
  int shadow_layout_object_count = 0;
  int shadow_layout_text_count = 0;
  int option_count = 0;
  int selected_option_count = 0;
  unsigned radio_group_size = 0;
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
      item.element_id = BlinkStringToStdStringForStandaloneRenderer(
          String(element->GetIdAttribute()));
      item.debug_id = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(AtomicString("data-debug-id")));
      item.type_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kTypeAttr));
      item.name_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kNameAttr));
      item.min_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kMinAttr));
      item.max_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kMaxAttr));
      item.step_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kStepAttr));
      item.value_attr = BlinkStringToStdStringForStandaloneRenderer(
          element->getAttribute(html_names::kValueAttr));
      item.is_connected = element->isConnected();
      item.focused = element->IsFocused();
      item.placeholder_attr_present =
          element->FastHasAttribute(html_names::kPlaceholderAttr);
      if (auto* input = DynamicTo<HTMLInputElement>(element)) {
        item.element_interface = "HTMLInputElement";
        item.checked = input->Checked();
        item.input_name =
            BlinkStringToStdStringForStandaloneRenderer(input->GetName());
        item.live_value =
            BlinkStringToStdStringForStandaloneRenderer(input->Value());
        if (input->FormControlType() ==
            mojom::blink::FormControlType::kInputRadio) {
          item.radio_group_size = input->SizeOfRadioGroup();
          if (RadioButtonGroupScope* scope = input->GetRadioButtonGroupScope()) {
            item.radio_group_scope_present = true;
            item.radio_group_checked =
                scope->CheckedButtonForGroup(input->GetName()) == input;
          }
        }
      } else if (auto* select = DynamicTo<HTMLSelectElement>(element)) {
        item.element_interface = "HTMLSelectElement";
        item.live_value =
            BlinkStringToStdStringForStandaloneRenderer(select->Value());
        for (auto& option : select->GetOptionList()) {
          if (option.Selected()) {
            item.selected_values.push_back(
                BlinkStringToStdStringForStandaloneRenderer(option.value()));
          }
        }
      } else if (auto* textarea = DynamicTo<HTMLTextAreaElement>(element)) {
        item.element_interface = "HTMLTextAreaElement";
        item.value_attr = BlinkStringToStdStringForStandaloneRenderer(
            textarea->Value());
        item.live_value = item.value_attr;
        item.placeholder_visible =
            item.placeholder_attr_present && item.value_attr.empty();
      } else if (auto* text_control =
                     DynamicTo<TextControlElement>(element)) {
        item.element_interface = "TextControlElement";
        item.value_attr = BlinkStringToStdStringForStandaloneRenderer(
            text_control->Value());
        item.live_value = item.value_attr;
      } else {
        item.element_interface = "HTMLElement";
      }
      if (auto* text_control = DynamicTo<TextControlElement>(element)) {
        item.text_control_inner_editor_present =
            text_control->InnerEditorElement();
        item.selection_start = text_control->selectionStart();
        item.selection_end = text_control->selectionEnd();
        item.selection_offsets_present = true;
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
        const gfx::RectF absolute_bounds =
            layout_object->AbsoluteBoundingBoxRectF();
        item.absolute_bounds_present = true;
        item.absolute_x = absolute_bounds.x();
        item.absolute_y = absolute_bounds.y();
        item.absolute_width = absolute_bounds.width();
        item.absolute_height = absolute_bounds.height();
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

void CollectFormControlEntriesForStandaloneRenderer(
    Document& document,
    std::vector<LiveFormControlEntry>& entries) {
  FormControlDiagnosticsForStandaloneRenderer diagnostics;
  CollectFormControlDomDiagnosticsForStandaloneRenderer(&document,
                                                       diagnostics);
  entries.clear();
  for (const auto& item : diagnostics.controls) {
    if (item.element_id.empty()) {
      continue;
    }
    LiveFormControlEntry entry;
    entry.element_id = item.element_id;
    entry.tag_name = item.tag_name;
    entry.value = item.live_value;
    entry.type = item.type_attr;
    entry.min = item.min_attr;
    entry.max = item.max_attr;
    entry.step = item.step_attr;
    entry.selected_values = item.selected_values;
    entry.checked = item.checked;
    entry.focused = item.focused;
    entry.selection_offsets_present = item.selection_offsets_present;
    entry.selection_start = item.selection_start;
    entry.selection_end = item.selection_end;
    entries.push_back(std::move(entry));
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
         << ",\"element_id\":"
         << JsonStringForStandaloneRenderer(item.element_id)
         << ",\"data_debug_id\":"
         << JsonStringForStandaloneRenderer(item.debug_id)
         << ",\"type_attr\":" << JsonStringForStandaloneRenderer(item.type_attr)
         << ",\"name_attr\":" << JsonStringForStandaloneRenderer(item.name_attr)
         << ",\"min_attr\":" << JsonStringForStandaloneRenderer(item.min_attr)
         << ",\"max_attr\":" << JsonStringForStandaloneRenderer(item.max_attr)
         << ",\"step_attr\":" << JsonStringForStandaloneRenderer(item.step_attr)
         << ",\"input_name\":" << JsonStringForStandaloneRenderer(item.input_name)
         << ",\"value_length\":" << item.value_attr.size()
         << ",\"live_value\":"
         << JsonStringForStandaloneRenderer(item.live_value)
         << ",\"live_value_length\":" << item.live_value.size()
         << ",\"element_interface\":"
         << JsonStringForStandaloneRenderer(item.element_interface)
         << ",\"checked\":" << (item.checked ? "true" : "false")
         << ",\"is_connected\":" << (item.is_connected ? "true" : "false")
         << ",\"radio_group_scope_present\":"
         << (item.radio_group_scope_present ? "true" : "false")
         << ",\"radio_group_size\":" << item.radio_group_size
         << ",\"radio_group_checked\":"
         << (item.radio_group_checked ? "true" : "false")
         << ",\"computed_display\":"
         << JsonStringForStandaloneRenderer(item.computed_display)
         << ",\"layout_object_present\":"
         << (item.layout_object_present ? "true" : "false")
         << ",\"layout_object_type\":"
         << JsonStringForStandaloneRenderer(item.layout_object_type)
         << ",\"parent_layout_object_type\":"
         << JsonStringForStandaloneRenderer(item.parent_layout_object_type)
         << ",\"absolute_bounds_present\":"
         << (item.absolute_bounds_present ? "true" : "false")
         << ",\"absolute_bounds\":{\"x\":" << item.absolute_x
         << ",\"y\":" << item.absolute_y
         << ",\"width\":" << item.absolute_width
         << ",\"height\":" << item.absolute_height << "}"
         << ",\"standalone_support_status\":"
         << JsonStringForStandaloneRenderer(item.standalone_support_status)
         << ",\"unsupported_closure_boundary\":"
         << JsonStringForStandaloneRenderer(item.unsupported_closure_boundary)
         << ",\"user_agent_shadow_root_present\":"
         << (item.user_agent_shadow_root_present ? "true" : "false")
         << ",\"text_control_inner_editor_present\":"
         << (item.text_control_inner_editor_present ? "true" : "false")
         << ",\"selection_offsets_present\":"
         << (item.selection_offsets_present ? "true" : "false")
         << ",\"selection_start\":" << item.selection_start
         << ",\"selection_end\":" << item.selection_end
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
  Element* fixture_target =
      body ? FindElementByClassForStandaloneRenderer(
                 *body, AtomicString("fixture-target"))
           : nullptr;
  Element* debug_id =
      body ? FindElementByAttributeForStandaloneRenderer(
                 *body, AtomicString("data-debug-id"))
           : nullptr;
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
       << ","
       << BackgroundLayerDiagnosticsJsonForStandaloneRenderer(
              "fixture-target", document,
              fixture_target ? fixture_target->GetComputedStyle() : nullptr,
              fixture_target ? fixture_target->GetLayoutObject() : nullptr,
              layout_view,
              fixture_target ? static_cast<const Node*>(fixture_target) : node)
       << ","
       << BackgroundLayerDiagnosticsJsonForStandaloneRenderer(
              "data-debug-id", document,
              debug_id ? debug_id->GetComputedStyle() : nullptr,
              debug_id ? debug_id->GetLayoutObject() : nullptr, layout_view,
              debug_id ? static_cast<const Node*>(debug_id) : node)
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
  int paint_op_count = 0;
  int recursive_paint_op_count = 0;
  int visual_op_count = 0;
  int retained_supported_visual_op_count = 0;
  int retained_unsupported_visual_op_count = 0;
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

struct FinerCacheUnitAudit {
  int unit_index = 0;
  wtf_size_t begin_item_index = 0;
  wtf_size_t end_item_index = 0;
  DisplayItemClientId client_id = kInvalidDisplayItemClientId;
  bool client_id_valid = false;
  std::string first_item_id;
  std::string last_item_id;
  gfx::Rect visual_bounds;
  int display_item_count = 0;
  int drawing_item_count = 0;
  int scrollbar_display_item_count = 0;
  RawPaintRecordAudit audit;
  std::string content_fingerprint;
};

bool IsPaintOpCurrentlyExtracted(cc::PaintOpType type);

int DrawLooperLayerCountForStandaloneRenderer(const cc::PaintFlags& flags) {
  const sk_sp<cc::DrawLooper>& looper = flags.getLooper();
  if (!looper) {
    return 0;
  }
  // See AppendDrawLooperLayers: this local bridge must not depend on cc
  // internals that are intentionally hidden by real Chromium.
  return 0;
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
                      << PaintOpGeometryJsonForStandaloneRenderer(op);
      if (op.GetType() == cc::PaintOpType::kDrawImage) {
        const auto& image_op = static_cast<const cc::DrawImageOp&>(op);
        const int image_width = image_op.image.width();
        const int image_height = image_op.image.height();
        *paint_ops_json
            << ",\"src_rect\":"
            << SkRectJsonForStandaloneRenderer(SkRect::MakeXYWH(
                   0.0f, 0.0f, static_cast<SkScalar>(image_width),
                   static_cast<SkScalar>(image_height)))
            << ",\"dst_rect\":"
            << SkRectJsonForStandaloneRenderer(SkRect::MakeXYWH(
                   image_op.left, image_op.top,
                   static_cast<SkScalar>(image_width),
                   static_cast<SkScalar>(image_height)))
            << ",\"image_size\":[" << image_width << "," << image_height
            << "]"
            << ",\"sampling_options\":"
            << JsonStringForStandaloneRenderer(
                   SamplingOptionsStringForStandaloneRenderer(
                       image_op.sampling));
      } else if (op.GetType() == cc::PaintOpType::kDrawImageRect) {
        const auto& image_op = static_cast<const cc::DrawImageRectOp&>(op);
        *paint_ops_json
            << ",\"src_rect\":"
            << SkRectJsonForStandaloneRenderer(image_op.src)
            << ",\"dst_rect\":"
            << SkRectJsonForStandaloneRenderer(image_op.dst)
            << ",\"image_size\":[" << image_op.image.width() << ","
            << image_op.image.height() << "]"
            << ",\"sampling_options\":"
            << JsonStringForStandaloneRenderer(
                   SamplingOptionsStringForStandaloneRenderer(
                       image_op.sampling));
      }
      *paint_ops_json << "}";
    }

    if (op.GetType() == cc::PaintOpType::kDrawRecord) {
      AppendPaintRecordAuditJson(
          static_cast<const cc::DrawRecordOp&>(op).record, audit,
          paint_ops_json, false, depth + 1, first_paint_op);
    }
  }
}

int AuditHistogramCount(const std::map<std::string, int>& histogram,
                        const std::string& key) {
  const auto it = histogram.find(key);
  return it == histogram.end() ? 0 : it->second;
}

void MergeRawPaintRecordAudit(RawPaintRecordAudit& target,
                              const RawPaintRecordAudit& source) {
  for (const auto& [name, count] : source.top_level_histogram) {
    target.top_level_histogram[name] += count;
  }
  for (const auto& [name, count] : source.recursive_histogram) {
    target.recursive_histogram[name] += count;
  }
  for (const auto& [name, count] : source.unsupported_histogram) {
    target.unsupported_histogram[name] += count;
  }
  target.paint_op_count += source.paint_op_count;
  target.recursive_paint_op_count += source.recursive_paint_op_count;
  target.visual_op_count += source.visual_op_count;
  target.retained_supported_visual_op_count +=
      source.retained_supported_visual_op_count;
  target.retained_unsupported_visual_op_count +=
      source.retained_unsupported_visual_op_count;
  target.text_blob_count += source.text_blob_count;
  target.image_count += source.image_count;
  target.shader_count += source.shader_count;
  target.path_count += source.path_count;
  target.filter_count += source.filter_count;
  target.draw_looper_count += source.draw_looper_count;
  target.draw_looper_layer_count += source.draw_looper_layer_count;
  target.path_effect_count += source.path_effect_count;
  target.has_non_text_visual_paint |= source.has_non_text_visual_paint;
  target.has_non_translation_transform |=
      source.has_non_translation_transform;
  target.has_effect_opacity |= source.has_effect_opacity;
}

void AppendDisplayItemToFinerCacheUnits(
    std::vector<FinerCacheUnitAudit>& units,
    wtf_size_t item_index,
    DisplayItemClientId client_id,
    const std::string& item_id,
    const std::string& item_type,
    const gfx::Rect& visual_rect,
    bool is_drawing,
    bool is_scrollbar,
    const RawPaintRecordAudit& item_audit) {
  const bool client_id_valid = client_id != kInvalidDisplayItemClientId;
  const bool can_extend_previous =
      client_id_valid && !units.empty() && units.back().client_id == client_id;
  if (!can_extend_previous) {
    FinerCacheUnitAudit unit;
    unit.unit_index = static_cast<int>(units.size());
    unit.begin_item_index = item_index;
    unit.end_item_index = item_index;
    unit.client_id = client_id;
    unit.client_id_valid = client_id_valid;
    unit.first_item_id = item_id;
    unit.visual_bounds = visual_rect;
    units.push_back(std::move(unit));
  }
  FinerCacheUnitAudit& unit = units.back();
  unit.end_item_index = item_index + 1;
  unit.last_item_id = item_id;
  ++unit.display_item_count;
  if (is_drawing) {
    ++unit.drawing_item_count;
  }
  if (is_scrollbar) {
    ++unit.scrollbar_display_item_count;
  }
  if (!visual_rect.IsEmpty()) {
    if (unit.visual_bounds.IsEmpty()) {
      unit.visual_bounds = visual_rect;
    } else {
      unit.visual_bounds.Union(visual_rect);
    }
  }
  MergeRawPaintRecordAudit(unit.audit, item_audit);
  unit.content_fingerprint += "|" + item_id + ":" + item_type + ":" +
                              std::to_string(visual_rect.x()) + "," +
                              std::to_string(visual_rect.y()) + "," +
                              std::to_string(visual_rect.width()) + "," +
                              std::to_string(visual_rect.height()) + ":" +
                              std::to_string(item_audit.recursive_paint_op_count);
}

std::vector<std::string> FinerCacheUnitDesignNotes(
    const FinerCacheUnitAudit& unit) {
  std::vector<std::string> notes;
  if (!unit.client_id_valid) {
    notes.push_back("invalid_display_item_client_id");
  }
  if (unit.drawing_item_count == 0 &&
      unit.scrollbar_display_item_count == 0) {
    notes.push_back("no_drawing_display_items");
  }
  if (unit.scrollbar_display_item_count > 0) {
    notes.push_back("contains_scrollbar_display_items");
  }
  if (unit.visual_bounds.IsEmpty()) {
    notes.push_back("empty_visual_bounds");
  }
  if (AuditHistogramCount(unit.audit.recursive_histogram,
                          "SaveLayerAlphaOp") > 0 ||
      AuditHistogramCount(unit.audit.recursive_histogram,
                          "SaveLayerFiltersOp") > 0) {
    notes.push_back("contains_save_layer_ops");
  }
  if (AuditHistogramCount(unit.audit.recursive_histogram, "ClipRRectOp") > 0 ||
      AuditHistogramCount(unit.audit.recursive_histogram, "ClipPathOp") > 0) {
    notes.push_back("contains_non_rect_clip_ops");
  }
  if (unit.audit.has_non_translation_transform) {
    notes.push_back("contains_non_translation_transform");
  }
  if (unit.audit.has_effect_opacity) {
    notes.push_back("contains_effect_opacity");
  }
  if (unit.audit.shader_count > 0) {
    notes.push_back("contains_shader_ops");
  }
  if (unit.audit.image_count > 0) {
    notes.push_back("contains_image_ops");
  }
  if (unit.audit.path_count > 0) {
    notes.push_back("contains_path_ops");
  }
  if (unit.audit.filter_count > 0) {
    notes.push_back("contains_filter_ops");
  }
  if (unit.audit.path_effect_count > 0) {
    notes.push_back("contains_path_effect_ops");
  }
  return notes;
}

std::string StringArrayJsonForStandaloneRenderer(
    const std::vector<std::string>& values) {
  std::ostringstream json;
  json << "[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    json << JsonStringForStandaloneRenderer(values[i]);
  }
  json << "]";
  return json.str();
}

uint64_t FinerCacheUnitContentHash(const FinerCacheUnitAudit& unit) {
  return HashStringForStandaloneRenderer(unit.content_fingerprint);
}

uint64_t FinerCacheUnitResourceSignalHash(const FinerCacheUnitAudit& unit) {
  return HashStringForStandaloneRenderer(
      std::to_string(unit.audit.image_count) + ":" +
      std::to_string(unit.audit.shader_count) + ":" +
      std::to_string(unit.audit.path_count) + ":" +
      std::to_string(unit.audit.filter_count) + ":" +
      std::to_string(unit.audit.path_effect_count) + ":" +
      std::to_string(unit.audit.text_blob_count));
}

std::string FinerCacheUnitStableKey(const std::string& chunk_stable_key,
                                    const FinerCacheUnitAudit& unit) {
  return chunk_stable_key + ":display-client=" +
         std::to_string(static_cast<uint64_t>(unit.client_id)) +
         ":content=" + std::to_string(FinerCacheUnitContentHash(unit));
}

LiveFinerCacheUnitDescriptor ExportFinerCacheUnitDescriptor(
    const std::string& chunk_stable_key,
    const FinerCacheUnitAudit& unit) {
  const std::vector<std::string> notes = FinerCacheUnitDesignNotes(unit);
  LiveFinerCacheUnitDescriptor descriptor;
  descriptor.unit_index = unit.unit_index;
  descriptor.begin_display_item_index =
      static_cast<int>(unit.begin_item_index);
  descriptor.end_display_item_index = static_cast<int>(unit.end_item_index);
  descriptor.display_item_client_id =
      static_cast<uint64_t>(unit.client_id);
  descriptor.display_item_client_id_valid = unit.client_id_valid;
  descriptor.visual_x = static_cast<float>(unit.visual_bounds.x());
  descriptor.visual_y = static_cast<float>(unit.visual_bounds.y());
  descriptor.visual_width = static_cast<float>(unit.visual_bounds.width());
  descriptor.visual_height = static_cast<float>(unit.visual_bounds.height());
  descriptor.content_hash = FinerCacheUnitContentHash(unit);
  descriptor.resource_signal_hash = FinerCacheUnitResourceSignalHash(unit);
  descriptor.display_item_count = unit.display_item_count;
  descriptor.drawing_item_count = unit.drawing_item_count;
  descriptor.paint_op_count = unit.audit.paint_op_count;
  descriptor.recursive_paint_op_count =
      unit.audit.recursive_paint_op_count;
  descriptor.visual_op_count = unit.audit.visual_op_count;
  descriptor.conservative_candidate = notes.empty();
  descriptor.has_save_layer_ops =
      AuditHistogramCount(unit.audit.recursive_histogram,
                          "SaveLayerAlphaOp") > 0 ||
      AuditHistogramCount(unit.audit.recursive_histogram,
                          "SaveLayerFiltersOp") > 0;
  descriptor.has_non_rect_clip_ops =
      AuditHistogramCount(unit.audit.recursive_histogram, "ClipRRectOp") >
          0 ||
      AuditHistogramCount(unit.audit.recursive_histogram, "ClipPathOp") > 0;
  descriptor.has_non_translation_transform =
      unit.audit.has_non_translation_transform;
  descriptor.has_effect_opacity = unit.audit.has_effect_opacity;
  descriptor.has_shader_ops = unit.audit.shader_count > 0;
  descriptor.has_image_ops = unit.audit.image_count > 0;
  descriptor.has_path_ops = unit.audit.path_count > 0;
  descriptor.has_filter_ops = unit.audit.filter_count > 0;
  descriptor.has_path_effect_ops = unit.audit.path_effect_count > 0;
  descriptor.stable_key = FinerCacheUnitStableKey(chunk_stable_key, unit);
  return descriptor;
}

std::string FinerCacheUnitMetadataJsonForStandaloneRenderer(
    wtf_size_t chunk_index,
    const std::string& chunk_stable_key,
    const std::vector<FinerCacheUnitAudit>& units) {
  int candidate_count = 0;
  int invalid_client_count = 0;
  int save_layer_unit_count = 0;
  int non_rect_clip_unit_count = 0;
  int resource_dependent_unit_count = 0;
  for (const FinerCacheUnitAudit& unit : units) {
    const std::vector<std::string> notes = FinerCacheUnitDesignNotes(unit);
    if (notes.empty()) {
      ++candidate_count;
    }
    if (!unit.client_id_valid) {
      ++invalid_client_count;
    }
    if (AuditHistogramCount(unit.audit.recursive_histogram,
                            "SaveLayerAlphaOp") > 0 ||
        AuditHistogramCount(unit.audit.recursive_histogram,
                            "SaveLayerFiltersOp") > 0) {
      ++save_layer_unit_count;
    }
    if (AuditHistogramCount(unit.audit.recursive_histogram, "ClipRRectOp") >
            0 ||
        AuditHistogramCount(unit.audit.recursive_histogram, "ClipPathOp") >
            0) {
      ++non_rect_clip_unit_count;
    }
    if (unit.audit.shader_count > 0 || unit.audit.image_count > 0 ||
        unit.audit.path_count > 0 || unit.audit.filter_count > 0 ||
        unit.audit.path_effect_count > 0) {
      ++resource_dependent_unit_count;
    }
  }

  std::ostringstream json;
  json << "{\"schema_version\":1"
       << ",\"behavior_neutral\":true"
       << ",\"cache_behavior_enabled\":false"
       << ",\"boundary_source\":\"consecutive_blink_display_item_client_runs\""
       << ",\"chunk_index\":" << chunk_index
       << ",\"chunk_stable_key\":"
       << JsonStringForStandaloneRenderer(chunk_stable_key)
       << ",\"unit_count\":" << units.size()
       << ",\"conservative_candidate_count\":" << candidate_count
       << ",\"unproven_or_blocked_count\":"
       << (static_cast<int>(units.size()) - candidate_count)
       << ",\"invalid_client_unit_count\":" << invalid_client_count
       << ",\"save_layer_unit_count\":" << save_layer_unit_count
       << ",\"non_rect_clip_unit_count\":" << non_rect_clip_unit_count
       << ",\"resource_dependent_unit_count\":"
       << resource_dependent_unit_count << ",\"units\":[";
  for (size_t i = 0; i < units.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    const FinerCacheUnitAudit& unit = units[i];
    const std::vector<std::string> notes = FinerCacheUnitDesignNotes(unit);
    const uint64_t content_hash = FinerCacheUnitContentHash(unit);
    const uint64_t resource_signal_hash =
        FinerCacheUnitResourceSignalHash(unit);
    const std::string unit_stable_key =
        FinerCacheUnitStableKey(chunk_stable_key, unit);
    json << "{\"unit_index\":" << unit.unit_index
         << ",\"stable_key\":"
         << JsonStringForStandaloneRenderer(unit_stable_key)
         << ",\"client_id\":"
         << static_cast<uint64_t>(unit.client_id)
         << ",\"client_id_valid\":"
         << (unit.client_id_valid ? "true" : "false")
         << ",\"begin_item_index\":" << unit.begin_item_index
         << ",\"end_item_index\":" << unit.end_item_index
         << ",\"display_item_count\":" << unit.display_item_count
         << ",\"drawing_item_count\":" << unit.drawing_item_count
         << ",\"scrollbar_display_item_count\":"
         << unit.scrollbar_display_item_count
         << ",\"first_item_id\":"
         << JsonStringForStandaloneRenderer(unit.first_item_id)
         << ",\"last_item_id\":"
         << JsonStringForStandaloneRenderer(unit.last_item_id)
         << ",\"visual_bounds\":"
         << RectJsonForStandaloneRenderer(unit.visual_bounds)
         << ",\"content_hash\":" << content_hash
         << ",\"resource_signal_hash\":" << resource_signal_hash
         << ",\"paint_op_count\":" << unit.audit.paint_op_count
         << ",\"recursive_paint_op_count\":"
         << unit.audit.recursive_paint_op_count
         << ",\"visual_op_count\":" << unit.audit.visual_op_count
         << ",\"text_blob_count\":" << unit.audit.text_blob_count
         << ",\"image_count\":" << unit.audit.image_count
         << ",\"shader_count\":" << unit.audit.shader_count
         << ",\"path_count\":" << unit.audit.path_count
         << ",\"filter_count\":" << unit.audit.filter_count
         << ",\"path_effect_count\":" << unit.audit.path_effect_count
         << ",\"recursive_op_histogram\":"
         << MapToJsonObject(unit.audit.recursive_histogram)
         << ",\"conservative_candidate\":"
         << (notes.empty() ? "true" : "false")
         << ",\"design_notes\":"
         << StringArrayJsonForStandaloneRenderer(notes) << "}";
  }
  json << "]}";
  return json.str();
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
          diagnostics.loader_content_loaded = content->IsLoaded();
          diagnostics.loader_content_loading = content->IsLoading();
          diagnostics.loader_content_status =
              static_cast<int>(content->GetContentStatus());
          diagnostics.image_element_complete = image_element->complete();
          diagnostics.image_element_primary_content =
              image_element->IsPrimaryContent();
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

void StartStandaloneImageLoadsForStaticRenderFromNode(Node& node) {
  if (auto* image = DynamicTo<HTMLImageElement>(node)) {
    const AtomicString src = image->FastGetAttribute(html_names::kSrcAttr);
    const AtomicString srcset =
        image->FastGetAttribute(html_names::kSrcsetAttr);
    if (src.empty() && srcset.empty()) {
      for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
        StartStandaloneImageLoadsForStaticRenderFromNode(*child);
      }
      return;
    }
    if (!src.empty() && srcset.empty()) {
      std::string source = src.GetString().Utf8();
      std::string lowered_source = LowerAsciiForStandaloneRenderer(source);
      if (lowered_source.rfind("data:", 0) != 0 &&
          lowered_source.rfind("file:", 0) != 0 &&
          lowered_source.find(':') == std::string::npos) {
        html_css_renderer::StandaloneResourceRequest request;
        request.url = source;
        request.type_hint =
            html_css_renderer::StandaloneResourceTypeHint::kImage;
        request.initiator =
            html_css_renderer::StandaloneResourceInitiator::kImgElement;
        request.accepted_mime_types.push_back("image/png");
        request.accepted_mime_types.push_back("image/jpeg");
        request.accepted_mime_types.push_back("image/bmp");
        request.accepted_mime_types.push_back("image/svg+xml");
        html_css_renderer::StandaloneResourceResult result =
            html_css_renderer::DefaultStandaloneResourceProvider().LoadResource(
                request);
        if (result.status !=
                html_css_renderer::StandaloneResourceStatus::kSuccess ||
            result.resolved_path.empty()) {
          TraceLiveFrameProbeStage("static image load skipped local resource");
          for (Node* child = node.firstChild(); child;
               child = child->nextSibling()) {
            StartStandaloneImageLoadsForStaticRenderFromNode(*child);
          }
          return;
        }
        std::string file_url = result.resolved_path;
        std::replace(file_url.begin(), file_url.end(), '\\', '/');
        if (file_url.size() < 3 || file_url[1] != ':') {
          file_url = "/" + file_url;
        }
        file_url = "file:///" + file_url;
        StandaloneRendererSetDeferImageAttributeLoads(true);
        image->setAttribute(html_names::kSrcAttr,
                            AtomicString(file_url.c_str()));
        StandaloneRendererSetDeferImageAttributeLoads(false);
      }
    }
    image->SelectSourceURL(ImageLoader::kUpdateIgnorePreviousError);
    TraceLiveFrameProbeStage("static image load source normalized");
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    StartStandaloneImageLoadsForStaticRenderFromNode(*child);
  }
}

void StartStandaloneImageLoadsForStaticRender(Document& document) {
  if (Element* root = document.documentElement()) {
    StartStandaloneImageLoadsForStaticRenderFromNode(*root);
  }
}

void RunStandaloneImageLoadingTasksForStaticRender() {
  TraceLiveFrameProbeStage("static image load before RunUntilIdle");
  base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
  run_loop.RunUntilIdle();
  TraceLiveFrameProbeStage("static image load after RunUntilIdle");
}

void CompleteStandaloneImageLoadsForStaticRenderFromNode(Node& node) {
  if (auto* image = DynamicTo<HTMLImageElement>(node)) {
    ImageResourceContent* content = image->CachedImage();
    if (content) {
      content->MaybeFinalizeStandaloneSvgImageForStaticRender();
      content = image->CachedImage();
    }
    if (content && content->IsLoaded() && content->HasImage() &&
        !content->ErrorOccurred()) {
      TraceLiveFrameProbeStage("static image load before loaded disposition reset");
      image->OnImageLoadComplete();
      TraceLiveFrameProbeStage("static image load after loaded disposition reset");
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    CompleteStandaloneImageLoadsForStaticRenderFromNode(*child);
  }
}

void CompleteStandaloneImageLoadsForStaticRender(Document& document) {
  if (Element* root = document.documentElement()) {
    CompleteStandaloneImageLoadsForStaticRenderFromNode(*root);
  }
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

bool AttributeMutationRequiresDocumentRebuildForStandaloneRenderer(
    const std::string& html,
    const std::unordered_map<std::string, std::string>& attributes) {
  // Blink's live attribute mutation path now drives style invalidation,
  // property-tree updates, and cc commits for these cases. Rebuilding the
  // standalone document here defeats resource/layer retention on every
  // effective attribute update.
  return false;
}

bool AttributeMutationMayAffectImageLoadsForStandaloneRenderer(
    const std::unordered_map<std::string, std::string>& attributes) {
  for (const auto& [key, value] : attributes) {
    const size_t separator = key.find(':');
    if (separator == std::string::npos || separator + 1 >= key.size()) {
      continue;
    }
    const std::string attribute =
        LowerAsciiForStandaloneRenderer(key.substr(separator + 1));
    if (attribute == "src" || attribute == "srcset" || attribute == "sizes") {
      return true;
    }
  }
  return false;
}

void ApplyElementAttributesForStandaloneRenderer(
    Document& document,
    const std::unordered_map<std::string, std::string>& attributes,
    std::unordered_map<std::string, OriginalElementAttributeValue>*
        original_values,
    std::unordered_map<std::string, std::string>* applied_attributes) {
  if (applied_attributes && original_values) {
    std::vector<std::string> restore_keys;
    for (const auto& [key, value] : *applied_attributes) {
      if (attributes.find(key) == attributes.end()) {
        restore_keys.push_back(key);
      }
    }
    for (const std::string& key : restore_keys) {
      const size_t separator = key.find(':');
      if (separator != std::string::npos && separator != 0 &&
          separator + 1 < key.size()) {
        Element* element =
            document.getElementById(AtomicString(String::FromUtf8(
                key.substr(0, separator))));
        if (element) {
          const AtomicString attribute_name(
              String::FromUtf8(key.substr(separator + 1)));
          const auto original = original_values->find(key);
          if (original != original_values->end() && original->second.present) {
            element->setAttribute(
                attribute_name,
                AtomicString(String::FromUtf8(original->second.value)));
          } else {
            element->removeAttribute(attribute_name);
          }
        }
      }
      applied_attributes->erase(key);
      original_values->erase(key);
    }
  }

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
    if (original_values && original_values->find(key) == original_values->end()) {
      OriginalElementAttributeValue original;
      original.present = element->hasAttribute(attribute_name);
      if (original.present) {
        original.value = BlinkStringToStdStringForStandaloneRenderer(
            String(element->getAttribute(attribute_name)));
      }
      (*original_values)[key] = std::move(original);
    }
    if (value.empty()) {
      element->removeAttribute(attribute_name);
    } else {
      element->setAttribute(attribute_name, AtomicString(String::FromUtf8(value)));
    }
    if (applied_attributes) {
      (*applied_attributes)[key] = value;
    }
  }
}

bool ParseStandaloneUnsignedPair(const std::string& value,
                                 unsigned* first,
                                 unsigned* second) {
  const size_t separator = value.find(':');
  if (separator == std::string::npos) {
    return false;
  }
  char* end = nullptr;
  const unsigned long parsed_first =
      std::strtoul(value.substr(0, separator).c_str(), &end, 10);
  if (!end || *end != '\0') {
    return false;
  }
  end = nullptr;
  const unsigned long parsed_second =
      std::strtoul(value.substr(separator + 1).c_str(), &end, 10);
  if (!end || *end != '\0') {
    return false;
  }
  *first = static_cast<unsigned>(parsed_first);
  *second = static_cast<unsigned>(parsed_second);
  return true;
}

void MarkStandaloneFormControlMutationLayout(Element& element) {
  LayoutObject* layout_object = element.GetLayoutObject();
  if (!layout_object) {
    return;
  }
  layout_object->SetNeedsLayoutAndFullPaintInvalidation(
      layout_invalidation_reason::kTextControlChanged);
}

std::vector<std::string> ParseStandaloneLengthPrefixedStringList(
    const std::string& serialized) {
  std::vector<std::string> values;
  size_t offset = 0;
  while (offset < serialized.size()) {
    const size_t separator = serialized.find(':', offset);
    if (separator == std::string::npos || separator == offset) {
      break;
    }
    size_t length = 0;
    for (size_t i = offset; i < separator; ++i) {
      if (!std::isdigit(static_cast<unsigned char>(serialized[i]))) {
        return values;
      }
      length = length * 10 + static_cast<size_t>(serialized[i] - '0');
    }
    const size_t value_begin = separator + 1;
    if (value_begin + length > serialized.size()) {
      break;
    }
    values.push_back(serialized.substr(value_begin, length));
    offset = value_begin + length;
  }
  return values;
}

void ApplyStandaloneSelectSelectedValuesForRenderer(
    HTMLSelectElement& select,
    const std::vector<std::string>& selected_values) {
  for (auto& option : select.GetOptionList()) {
    const std::string option_value =
        BlinkStringToStdStringForStandaloneRenderer(option.value());
    const bool should_select =
        std::find(selected_values.begin(), selected_values.end(),
                  option_value) != selected_values.end();
    option.SetSelected(should_select);
    option.SetDirty(true);
  }
  MarkStandaloneFormControlMutationLayout(select);
  select.GetDocument().UpdateStyleAndLayoutTree();
}

void MarkStandaloneInputEventLayout(Document& document,
                                    LocalFrameView& frame_view) {
  frame_view.SetNeedsLayout();
  if (Element* focused_element = document.FocusedElement()) {
    MarkStandaloneFormControlMutationLayout(*focused_element);
  }
}

void UpdateStandaloneFocusedInputLayout(Document& document) {
  Element* focused_element = document.FocusedElement();
  if (!focused_element) {
    return;
  }
  MarkStandaloneFormControlMutationLayout(*focused_element);
  document.UpdateStyleAndLayoutForNode(focused_element,
                                       DocumentUpdateReason::kTest);
}

TextControlElement* FocusedTextControlForStandaloneRenderer(
    Document& document) {
  return DynamicTo<TextControlElement>(document.FocusedElement());
}

bool ReplaceFocusedTextControlSelectionForStandaloneRenderer(
    Document& document,
    const String& replacement) {
  TextControlElement* control =
      FocusedTextControlForStandaloneRenderer(document);
  if (!control) {
    return false;
  }

  String original = control->InnerEditorValue();
  unsigned start = control->selectionStart();
  unsigned end = control->selectionEnd();
  if (start > end) {
    std::swap(start, end);
  }
  start = std::min(start, original.length());
  end = std::min(end, original.length());

  StringBuilder text;
  text.Append(StringView(original, 0, start));
  text.Append(replacement);
  text.Append(StringView(original, end));
  control->SetValue(text.ToString(), TextFieldEventBehavior::kDispatchNoEvent,
                    TextControlSetValueSelection::kDoNotSet);

  const unsigned caret = start + replacement.length();
  control->SetSelectionRange(caret, caret);
  MarkStandaloneFormControlMutationLayout(*control);
  return true;
}

bool ApplyFocusedTextControlEditingKeyForStandaloneRenderer(Document& document,
                                                            int key) {
  TextControlElement* control =
      FocusedTextControlForStandaloneRenderer(document);
  if (!control) {
    return false;
  }

  String original = control->InnerEditorValue();
  unsigned start = control->selectionStart();
  unsigned end = control->selectionEnd();
  if (start > end) {
    std::swap(start, end);
  }
  start = std::min(start, original.length());
  end = std::min(end, original.length());

  if (start == end) {
    if (key == 8) {
      if (start == 0) {
        return true;
      }
      --start;
    } else if (key == 46) {
      if (end >= original.length()) {
        return true;
      }
      ++end;
    } else {
      return false;
    }
  }

  StringBuilder text;
  text.Append(StringView(original, 0, start));
  text.Append(StringView(original, end));
  control->SetValue(text.ToString(), TextFieldEventBehavior::kDispatchNoEvent,
                    TextControlSetValueSelection::kDoNotSet);
  control->SetSelectionRange(start, start);
  MarkStandaloneFormControlMutationLayout(*control);
  return true;
}

void ApplyDomMutationsForStandaloneRenderer(
    Document& document,
    const std::vector<StandaloneDomMutationForRenderer>& mutations) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.dom_mutations_applied = false;
  cache.dom_mutation_apply_count = 0;
  for (const StandaloneDomMutationForRenderer& mutation : mutations) {
    if (mutation.type == 9) {
      document.ClearFocusedElement();
      cache.dom_mutations_applied = true;
      ++cache.dom_mutation_apply_count;
      continue;
    }
    Element* element =
        mutation.type == 12
            ? document.body()
            : document.getElementById(
                  AtomicString(String::FromUtf8(mutation.element_id)));
    if (!element && mutation.type == 5) {
      const AtomicString style_element_id(
          String::FromUtf8(mutation.element_id));
      for (HTMLStyleElement& candidate :
           Traversal<HTMLStyleElement>::DescendantsOf(document)) {
        if (candidate.GetIdAttribute() == style_element_id) {
          element = &candidate;
          break;
        }
      }
    }
    if (!element) {
      continue;
    }
    switch (mutation.type) {
      case 1:
        element->setTextContent(String::FromUtf8(mutation.value));
        break;
      case 11:
        element->SetInnerHTMLWithoutTrustedTypes(
            String::FromUtf8(mutation.value));
        break;
      case 12:
        element->SetInnerHTMLWithoutTrustedTypes(
            String::FromUtf8(mutation.value));
        break;
      case 13:
        if (auto* select = DynamicTo<HTMLSelectElement>(element)) {
          ApplyStandaloneSelectSelectedValuesForRenderer(
              *select,
              ParseStandaloneLengthPrefixedStringList(mutation.value));
        } else {
          continue;
        }
        break;
      case 14:
        element->InsertAdjacentHTMLWithoutTrustedTypesForTesting(
            String::FromUtf8(mutation.name),
            String::FromUtf8(mutation.value), ASSERT_NO_EXCEPTION);
        break;
      case 15:
        element->remove(ASSERT_NO_EXCEPTION);
        break;
      case 2:
        if (mutation.name.empty()) {
          continue;
        }
        element->setAttribute(AtomicString(String::FromUtf8(mutation.name)),
                              AtomicString(String::FromUtf8(mutation.value)));
        break;
      case 3:
        if (mutation.name.empty()) {
          continue;
        }
        element->removeAttribute(AtomicString(String::FromUtf8(mutation.name)));
        break;
      case 4:
        element->setAttribute(html_names::kStyleAttr,
                              AtomicString(String::FromUtf8(mutation.value)));
        break;
      case 5:
        if (auto* style_element = DynamicTo<HTMLStyleElement>(element)) {
          style_element->ReplaceStyleTextForStandaloneRenderer(
              String::FromUtf8(mutation.value));
        } else {
          continue;
        }
        break;
      case 6:
        if (auto* textarea = DynamicTo<HTMLTextAreaElement>(element)) {
          textarea->setValueForBinding(String::FromUtf8(mutation.value));
          MarkStandaloneFormControlMutationLayout(*element);
        } else if (auto* select = DynamicTo<HTMLSelectElement>(element)) {
          select->setValueForBinding(String::FromUtf8(mutation.value));
          MarkStandaloneFormControlMutationLayout(*element);
        } else if (auto* text_control = DynamicTo<TextControlElement>(element)) {
          text_control->SetValue(String::FromUtf8(mutation.value));
          MarkStandaloneFormControlMutationLayout(*element);
        } else {
          continue;
        }
        break;
      case 7:
        if (auto* input = DynamicTo<HTMLInputElement>(element)) {
          if (!input->IsCheckable()) {
            continue;
          }
          input->SetChecked(mutation.value == "1");
          MarkStandaloneFormControlMutationLayout(*element);
        } else {
          continue;
        }
        break;
      case 8:
        document.UpdateStyleAndLayoutTree();
        if (Page* page = document.GetPage()) {
          page->GetFocusController().SetFocusedElement(element,
                                                      document.GetFrame());
        } else {
          element->Focus();
        }
        break;
      case 10: {
        auto* text_control = DynamicTo<TextControlElement>(element);
        if (!text_control) {
          continue;
        }
        unsigned start = 0;
        unsigned end = 0;
        if (!ParseStandaloneUnsignedPair(mutation.value, &start, &end)) {
          continue;
        }
        document.UpdateStyleAndLayoutTree();
        text_control->SetSelectionRange(start, end);
        break;
      }
      default:
        continue;
    }
    cache.dom_mutations_applied = true;
    ++cache.dom_mutation_apply_count;
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

void UpdateStandaloneInteractionStyleInvalidationForStandaloneRenderer(
    Document& document) {
  StyleEngine& style_engine = document.GetStyleEngine();
  style_engine.UpdateActiveStyle();
  if (style_engine.NeedsStyleInvalidation()) {
    style_engine.InvalidateStyle();
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
  } else if (hovered_element) {
    document.UpdateHoverActiveState(/*is_active=*/false,
                                    /*update_active_chain=*/false,
                                    hovered_element);
  }

  UpdateStandaloneInteractionStyleInvalidationForStandaloneRenderer(document);
}

bool UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
    LocalFrameView& frame_view,
    DocumentUpdateReason reason);

WebInputEvent::Type WebMouseEventTypeForStandaloneRenderer(int type) {
  switch (type) {
    case 2:
      return WebInputEvent::Type::kMouseDown;
    case 3:
      return WebInputEvent::Type::kMouseUp;
    case 1:
    default:
      return WebInputEvent::Type::kMouseMove;
  }
}

WebPointerProperties::Button WebMouseButtonForStandaloneRenderer(int button) {
  switch (button) {
    case 1:
      return WebPointerProperties::Button::kLeft;
    case 2:
      return WebPointerProperties::Button::kMiddle;
    case 3:
      return WebPointerProperties::Button::kRight;
    case 0:
    default:
      return WebPointerProperties::Button::kNoButton;
  }
}

std::string WebInputEventResultForStandaloneRenderer(
    WebInputEventResult result) {
  switch (result) {
    case WebInputEventResult::kNotHandled:
      return "not_handled";
    case WebInputEventResult::kHandledSystem:
      return "handled_system";
    case WebInputEventResult::kHandledApplication:
      return "handled_application";
    case WebInputEventResult::kHandledSuppressed:
      return "handled_suppressed";
  }
  return "unknown";
}

void PopulatePointerDiagnosticsFromDocumentForStandaloneRenderer(
    Document& document) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.pointer_hit_element_id.clear();
  cache.pointer_hit_element_tag.clear();
  cache.pointer_hit_element_class.clear();
  cache.pointer_hover_element_id.clear();
  cache.pointer_hover_element_tag.clear();
  cache.pointer_hover_element_class.clear();
  cache.pointer_focused_element_id.clear();

  if (Element* hover_element = document.HoverElement()) {
    cache.pointer_hover_element_id =
        BlinkStringToStdStringForStandaloneRenderer(
            String(hover_element->GetIdAttribute()));
    cache.pointer_hover_element_tag =
        BlinkStringToStdStringForStandaloneRenderer(hover_element->tagName());
    cache.pointer_hover_element_class =
        BlinkStringToStdStringForStandaloneRenderer(
            hover_element->getAttribute(html_names::kClassAttr));
  }
  if (Element* active_element = document.GetActiveElement()) {
    cache.pointer_hit_element_id =
        BlinkStringToStdStringForStandaloneRenderer(
            String(active_element->GetIdAttribute()));
    cache.pointer_hit_element_tag =
        BlinkStringToStdStringForStandaloneRenderer(active_element->tagName());
    cache.pointer_hit_element_class =
        BlinkStringToStdStringForStandaloneRenderer(
            active_element->getAttribute(html_names::kClassAttr));
  }
  if (Element* focused_element = document.FocusedElement()) {
    cache.pointer_focused_element_id =
        BlinkStringToStdStringForStandaloneRenderer(
            String(focused_element->GetIdAttribute()));
  }
}

void DispatchMouseInputEventsForStandaloneRenderer(Document& document,
                                                   LocalFrameView& frame_view) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.requested_mouse_input_events.empty() &&
      cache.mouse_input_events_consumed) {
    return;
  }
  cache.mouse_input_events_dispatched = false;
  cache.mouse_input_event_dispatch_count = 0;
  cache.mouse_input_status = cache.requested_mouse_input_events.empty()
                                 ? "not_requested"
                                 : "requested";
  cache.pointer_state_applied = false;
  cache.pointer_state_status =
      cache.requested_mouse_input_events.empty() ? "not_requested"
                                                 : "requested";
  cache.pointer_focus_requested = false;
  cache.pointer_focus_applied = false;
  cache.pointer_focus_status = "not_requested";
  cache.pointer_activation_requested = false;
  cache.pointer_activation_applied = false;
  cache.pointer_activation_status = "owned_by_blink_event_dispatch";
  cache.pointer_activation_element_id.clear();
  cache.pointer_activation_down_element_id.clear();
  cache.pointer_activation_node_id = kInvalidDOMNodeId;
  cache.pointer_activation_down_node_id = kInvalidDOMNodeId;
  PopulatePointerDiagnosticsFromDocumentForStandaloneRenderer(document);
  const std::string initial_hover_element_id = cache.pointer_hover_element_id;
  const std::string initial_active_element_id = cache.pointer_hit_element_id;

  if (cache.requested_mouse_input_events.empty()) {
    return;
  }
  std::vector<StandaloneMouseInputEventForRenderer> pending_events =
      std::move(cache.requested_mouse_input_events);
  cache.requested_mouse_input_events.clear();
  cache.mouse_input_events_consumed = true;

  LocalFrame* frame = document.GetFrame();
  if (!frame || !frame->View()) {
    cache.mouse_input_status = "frame_missing";
    cache.pointer_state_status = "frame_missing";
    return;
  }

  TraceLiveFrameProbeLifecycleState("mouse input before lifecycle update",
                                    &document, frame, &frame_view);
  TraceLiveFrameProbeStage("before mouse input lifecycle update");
  UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
      *frame->View(), DocumentUpdateReason::kTest);
  TraceLiveFrameProbeStage("after mouse input lifecycle update");

  std::string last_result = "not_dispatched";
  for (const StandaloneMouseInputEventForRenderer& pending : pending_events) {
    const WebInputEvent::Type event_type =
        WebMouseEventTypeForStandaloneRenderer(pending.type);
    const WebPointerProperties::Button button =
        WebMouseButtonForStandaloneRenderer(pending.button);
    WebMouseEvent event(event_type, gfx::PointF(pending.x, pending.y),
                        gfx::PointF(pending.x, pending.y), button,
                        pending.click_count, pending.modifiers,
                        base::TimeTicks::Now());
    event.UpdateEventModifiersToMatchButton();

    if (cache.trace_stages) {
      char buffer[256];
      std::snprintf(buffer, sizeof(buffer),
                    "before blink mouse event dispatch type=%d x=%.1f y=%.1f",
                    static_cast<int>(event_type), pending.x, pending.y);
      TraceLiveFrameProbeStage(buffer);
    }
    WebInputEventResult dispatch_result = WebInputEventResult::kNotHandled;
    if (event_type == WebInputEvent::Type::kMouseMove) {
      TraceLiveFrameProbeStage("before HandleMouseMoveEvent");
      dispatch_result = frame->GetEventHandler().HandleMouseMoveEvent(
          event, Vector<WebMouseEvent>(), Vector<WebMouseEvent>());
      TraceLiveFrameProbeStage("after HandleMouseMoveEvent");
    } else if (event_type == WebInputEvent::Type::kMouseDown) {
      cache.pointer_focus_requested = true;
      TraceLiveFrameProbeStage("before HandleMousePressEvent");
      dispatch_result = frame->GetEventHandler().HandleMousePressEvent(event);
      TraceLiveFrameProbeStage("after HandleMousePressEvent");
    } else if (event_type == WebInputEvent::Type::kMouseUp) {
      cache.pointer_activation_requested = true;
      TraceLiveFrameProbeStage("before HandleMouseReleaseEvent");
      dispatch_result = frame->GetEventHandler().HandleMouseReleaseEvent(event);
      TraceLiveFrameProbeStage("after HandleMouseReleaseEvent");
    }
    last_result = WebInputEventResultForStandaloneRenderer(dispatch_result);
    if (event_type == WebInputEvent::Type::kMouseDown ||
        event_type == WebInputEvent::Type::kMouseUp) {
      cache.needs_output = true;
    }
    if (cache.trace_stages) {
      char buffer[256];
      std::snprintf(buffer, sizeof(buffer),
                    "after blink mouse event dispatch result=%s",
                    last_result.c_str());
      TraceLiveFrameProbeStage(buffer);
    }
    ++cache.mouse_input_event_dispatch_count;
  }

  cache.mouse_input_events_dispatched =
      cache.mouse_input_event_dispatch_count > 0;
  cache.mouse_input_status =
      std::string("dispatched_via_blink_event_handler:") + last_result;
  cache.pointer_state_applied = cache.mouse_input_events_dispatched;
  cache.pointer_state_status = cache.mouse_input_status;
  PopulatePointerDiagnosticsFromDocumentForStandaloneRenderer(document);
  if (cache.pointer_hover_element_id != initial_hover_element_id ||
      cache.pointer_hit_element_id != initial_active_element_id) {
    cache.needs_output = true;
  }
  cache.pointer_focus_applied =
      cache.pointer_focus_requested && !cache.pointer_focused_element_id.empty();
  cache.pointer_focus_status =
      cache.pointer_focus_requested
          ? (cache.pointer_focus_applied ? "focused_by_blink_event_handler"
                                         : "not_focused_by_blink_event_handler")
          : "not_requested";
  cache.pointer_activation_status =
      cache.pointer_activation_requested
          ? "activation_owned_by_blink_event_handler"
          : "not_requested";
}

int StandaloneWindowsKeyCodeForKeyboardInputKey(int key) {
  switch (key) {
    case 8:
      return 8;   // Backspace.
    case 9:
      return 9;   // Tab.
    case 13:
      return 13;  // Enter.
    case 46:
      return 46;  // Delete.
    default:
      return 0;
  }
}

uint32_t StandaloneDomKeyForKeyboardInputKey(int key) {
  switch (key) {
    case 8:
      return static_cast<uint32_t>(ui::DomKey::BACKSPACE);
    case 9:
      return static_cast<uint32_t>(ui::DomKey::TAB);
    case 13:
      return static_cast<uint32_t>(ui::DomKey::ENTER);
    case 46:
      return static_cast<uint32_t>(ui::DomKey::DEL);
    default:
      return static_cast<uint32_t>(ui::DomKey::UNIDENTIFIED);
  }
}

std::string DispatchKeyboardInputEventViaBlinkForStandaloneRenderer(
    LocalFrame& frame,
    const StandaloneKeyboardInputEventForRenderer& pending) {
  const int key_code = StandaloneWindowsKeyCodeForKeyboardInputKey(pending.key);
  if (!key_code) {
    return "key_unknown";
  }
  WebInputEvent::Type event_type = WebInputEvent::Type::kUndefined;
  if (pending.type == 2) {
    event_type = WebInputEvent::Type::kKeyDown;
  } else if (pending.type == 3) {
    event_type = WebInputEvent::Type::kKeyUp;
  } else {
    return "key_type_ignored";
  }

  WebKeyboardEvent event(event_type, pending.modifiers, base::TimeTicks::Now());
  event.windows_key_code = key_code;
  event.native_key_code = key_code;
  event.dom_key = StandaloneDomKeyForKeyboardInputKey(pending.key);
  if (pending.key == 13) {
    // Chromium editing treats Enter as a text-insertion command generated from
    // the keypress/char phase. Standalone receives only the platform keydown,
    // so provide the text payload and let KeyboardEventManager synthesize the
    // normal Blink keypress path.
    event.text[0] = '\r';
    event.unmodified_text[0] = '\r';
  }
  const WebInputEventResult result = frame.GetEventHandler().KeyEvent(event);
  return std::string("key_") + WebInputEventResultForStandaloneRenderer(result);
}

void DispatchKeyboardInputEventsForStandaloneRenderer(Document& document,
                                                      LocalFrameView& frame_view) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.requested_keyboard_input_events.empty() &&
      cache.keyboard_input_events_consumed) {
    return;
  }
  cache.keyboard_input_events_dispatched = false;
  cache.keyboard_input_event_dispatch_count = 0;
  cache.keyboard_input_status = cache.requested_keyboard_input_events.empty()
                                    ? "not_requested"
                                    : "requested";
  if (cache.requested_keyboard_input_events.empty()) {
    return;
  }

  std::vector<StandaloneKeyboardInputEventForRenderer> pending_events =
      std::move(cache.requested_keyboard_input_events);
  cache.requested_keyboard_input_events.clear();
  cache.keyboard_input_events_consumed = true;

  LocalFrame* frame = document.GetFrame();
  if (!frame || !frame->View()) {
    cache.keyboard_input_status = "frame_missing";
    return;
  }

  TraceLiveFrameProbeLifecycleState("keyboard input before lifecycle update",
                                    &document, frame, &frame_view);
  MarkStandaloneInputEventLayout(document, frame_view);
  TraceLiveFrameProbeStage("before keyboard input lifecycle update");
  UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
      *frame->View(), DocumentUpdateReason::kTest);
  TraceLiveFrameProbeStage("after keyboard input lifecycle update");

  std::string last_result = "not_dispatched";
  for (const StandaloneKeyboardInputEventForRenderer& pending :
       pending_events) {
    bool handled = false;
    MarkStandaloneInputEventLayout(document, frame_view);
    TraceLiveFrameProbeStage("before keyboard input predispatch lifecycle update");
    UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
        *frame->View(), DocumentUpdateReason::kTest);
    TraceLiveFrameProbeStage("after keyboard input predispatch lifecycle update");
    TraceLiveFrameProbeStage("before focused input layout update");
    UpdateStandaloneFocusedInputLayout(document);
    TraceLiveFrameProbeStage("after focused input layout update");
    if (pending.type == 1 && !pending.text.empty()) {
      const String text = String::FromUtf8(pending.text);
      TraceLiveFrameProbeStage("before standalone text control text insert");
      handled =
          ReplaceFocusedTextControlSelectionForStandaloneRenderer(document,
                                                                  text);
      TraceLiveFrameProbeStage("after standalone text control text insert");
      last_result = handled ? "text_handled" : "text_not_handled";
    } else if (pending.type == 2 && (pending.key == 8 || pending.key == 46)) {
      TraceLiveFrameProbeStage("before standalone text control edit key");
      handled =
          ApplyFocusedTextControlEditingKeyForStandaloneRenderer(document,
                                                                 pending.key);
      TraceLiveFrameProbeStage("after standalone text control edit key");
      last_result = handled ? "key_text_control_handled"
                            : "key_text_control_not_handled";
    } else if (pending.type == 2 || pending.type == 3) {
      TraceLiveFrameProbeStage("before blink keyboard dispatch");
      last_result =
          DispatchKeyboardInputEventViaBlinkForStandaloneRenderer(*frame,
                                                                  pending);
      TraceLiveFrameProbeStage("after blink keyboard dispatch");
      handled = true;
    } else {
      last_result = "event_ignored";
    }
    if (handled) {
      cache.keyboard_input_events_dispatched = true;
      cache.needs_output = true;
      MarkStandaloneInputEventLayout(document, frame_view);
    }
    ++cache.keyboard_input_event_dispatch_count;
  }

  if (cache.keyboard_input_events_dispatched) {
    PopulatePointerDiagnosticsFromDocumentForStandaloneRenderer(document);
  }
  cache.keyboard_input_status =
      std::string("dispatched_via_blink_event_handler:") + last_result;
}

void ApplyAnimationTimeForStandaloneRenderer(Document& document) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.animation_time_requested) {
    return;
  }
  cache.animation_time_status.clear();

  const base::TimeTicks animation_time =
      document.Timeline().CalculateZeroTime() +
      base::Milliseconds(cache.requested_animation_time_ms);
  document.GetAnimationClock().SetAllowedToDynamicallyUpdateTime(false);
  document.GetAnimationClock().UpdateTime(animation_time);
  if (document.GetAgent().event_loop()) {
    document.GetDocumentAnimations().UpdateAnimationTimingForAnimationFrame();
  } else {
    document.GetDocumentAnimations().UpdateAnimationTimingIfNeeded();
    cache.animation_time_status =
        "applied_to_document_animation_clock_without_event_loop_checkpoint";
  }
  for (Animation* animation : document.Timeline().GetAnimations()) {
    if (animation) {
      animation->Update(kTimingUpdateForAnimationFrame);
      animation->UpdateIfNecessary();
    }
  }
  cache.applied_animation_time_ms = cache.requested_animation_time_ms;
  cache.animation_time_applied = true;
  if (cache.animation_time_status.empty()) {
    cache.animation_time_status = "applied_to_document_animation_clock";
  }
}

void SeedAnimationStartTimeForStandaloneRenderer(Document& document) {
  const base::TimeTicks zero_time = document.Timeline().CalculateZeroTime();
  document.GetAnimationClock().ResetTimeForTesting();
  document.GetAnimationClock().SetAllowedToDynamicallyUpdateTime(false);
  document.GetAnimationClock().UpdateTime(zero_time);
}

bool HtmlContainsStandaloneAnimationForRenderer(
    const std::string& input_html) {
  const std::string lower_html = LowerAsciiForStandaloneRenderer(input_html);
  return lower_html.find("@keyframes") != std::string::npos ||
         lower_html.find("animation:") != std::string::npos ||
         lower_html.find("transition:") != std::string::npos;
}

bool StandaloneAnimationTraceEnabled() {
  const char* value = std::getenv("HTML_CSS_RENDERER_ANIMATION_TRACE");
  return value && value[0] && std::strcmp(value, "0") != 0;
}

void TraceAnimationStateForStandaloneRenderer(const char* label,
                                              Document& document) {
  if (!StandaloneAnimationTraceEnabled()) {
    return;
  }
  const std::optional<AnimationTimeDelta> timeline_time =
      document.Timeline().CurrentTime();
  wtf_size_t animation_count = 0;
  for (Animation* animation : document.Timeline().GetAnimations()) {
    if (animation) {
      ++animation_count;
    }
  }
  std::fprintf(stderr,
               "animation_trace label=%s timeline_ms=%.3f needs_timing=%d "
               "animation_count=%u\n",
               label,
               timeline_time ? timeline_time->InMillisecondsF() : -1.0,
               document.GetDocumentAnimations().NeedsAnimationTimingUpdate()
                   ? 1
                   : 0,
               static_cast<unsigned>(animation_count));
  int index = 0;
  for (Animation* animation : document.Timeline().GetAnimations()) {
    if (!animation) {
      continue;
    }
    const std::optional<AnimationTimeDelta> start_time =
        animation->StartTimeInternal();
    const std::optional<AnimationTimeDelta> current_time =
        animation->CurrentTimeInternal();
    auto* effect = DynamicTo<KeyframeEffect>(animation->effect());
    Element* target = effect ? effect->EffectTarget() : nullptr;
    const std::string target_tag =
        target ? std::string(target->tagName().Utf8().c_str()) : "";
    const std::string target_class =
        target
            ? std::string(target->getAttribute(html_names::kClassAttr)
                              .Utf8()
                              .c_str())
            : "";
    int background_red = -1;
    int background_green = -1;
    int background_blue = -1;
    float background_alpha = -1.0f;
    int needs_style_recalc = -1;
    int style_change_type = -1;
    int animation_style_change = -1;
    if (target) {
      needs_style_recalc = target->NeedsStyleRecalc() ? 1 : 0;
      style_change_type = static_cast<int>(target->GetStyleChangeType());
      if (ElementAnimations* element_animations =
              target->GetElementAnimations()) {
        animation_style_change =
            element_animations->IsAnimationStyleChange() ? 1 : 0;
      }
      if (const ComputedStyle* style = target->GetComputedStyle()) {
        const Color background_color =
            style->VisitedDependentColor(GetCSSPropertyBackgroundColor());
        background_red = background_color.Red();
        background_green = background_color.Green();
        background_blue = background_color.Blue();
        background_alpha = background_color.Alpha();
      }
    }
    const bool affects_background =
        effect && effect->Affects(PropertyHandle(GetCSSPropertyBackgroundColor()));
    const bool affects_opacity =
        effect && effect->Affects(PropertyHandle(GetCSSPropertyOpacity()));
    const bool affects_transform =
        effect &&
        (effect->Affects(PropertyHandle(GetCSSPropertyTransform())) ||
         effect->Affects(PropertyHandle(GetCSSPropertyTranslate())) ||
         effect->Affects(PropertyHandle(GetCSSPropertyScale())) ||
         effect->Affects(PropertyHandle(GetCSSPropertyRotate())));
    std::fprintf(stderr,
                 "animation_trace item=%d playing=%d effectively_playing=%d "
                 "pending=%d outdated=%d start_ms=%.3f current_ms=%.3f "
                 "target_tag=%s target_class=%s affects_bg=%d "
                 "affects_opacity=%d affects_transform=%d needs_style=%d "
                 "style_change=%d animation_style_change=%d "
                 "background_rgba=%d,%d,%d,%.3f\n",
                 index++, animation->Playing() ? 1 : 0,
                 animation->EffectivelyPlaying() ? 1 : 0,
                 animation->PendingInternal() ? 1 : 0,
                 animation->Outdated() ? 1 : 0,
                 start_time ? start_time->InMillisecondsF() : -1.0,
                 current_time ? current_time->InMillisecondsF() : -1.0,
                 target_tag.c_str(), target_class.c_str(),
                 affects_background ? 1 : 0, affects_opacity ? 1 : 0,
                 affects_transform ? 1 : 0, needs_style_recalc,
                 style_change_type, animation_style_change, background_red,
                 background_green, background_blue, background_alpha);
  }
}

void MarkPaintPropertyTargetForStandaloneRenderer(LayoutObject& layout_object,
                                                  bool affects_opacity,
                                                  bool affects_transform) {
  if (affects_transform || affects_opacity) {
    if (auto* box_model_object =
            DynamicTo<LayoutBoxModelObject>(layout_object)) {
      box_model_object->EnsureLayerAfterAttachForStandalone();
    }
  }
  bool scheduled_deferred_update = false;
  if (affects_opacity) {
    scheduled_deferred_update |=
        PaintPropertyTreeBuilder::ScheduleDeferredOpacityNodeUpdate(
            layout_object);
  }
  if (affects_transform) {
    scheduled_deferred_update |=
        PaintPropertyTreeBuilder::ScheduleDeferredTransformNodeUpdate(
            layout_object);
  }
  if (!scheduled_deferred_update) {
    layout_object.SetNeedsPaintPropertyUpdate();
  }
}

void MarkComputedPaintPropertyTargetsForStandaloneRenderer(Node& node) {
  if (auto* element = DynamicTo<Element>(node)) {
    if (const ComputedStyle* style = element->GetComputedStyle()) {
      const bool has_opacity_property = style->HasNonInitialOpacity();
      const bool has_transform_property = style->HasTransform();
      if ((has_opacity_property || has_transform_property) &&
          element->GetLayoutObject()) {
        MarkPaintPropertyTargetForStandaloneRenderer(
            *element->GetLayoutObject(), has_opacity_property,
            has_transform_property);
      }
    }
  }
  for (Node* child = node.firstChild(); child; child = child->nextSibling()) {
    MarkComputedPaintPropertyTargetsForStandaloneRenderer(*child);
  }
}

void MarkAnimatedPaintPropertyTargetsForStandaloneRenderer(Document& document) {
  // Standalone does not run the browser compositor commit path that can directly
  // refresh animated property nodes, so keep Blink's prepaint builder honest
  // after sampled opacity/transform style changes. Non-composited animations
  // such as background-color still need Blink's normal animation style recalc
  // and paint invalidation before this synthetic frame is captured.
  for (Animation* animation : document.Timeline().GetAnimations()) {
    if (!animation) {
      continue;
    }
    auto* effect = DynamicTo<KeyframeEffect>(animation->effect());
    if (!effect) {
      continue;
    }
    const bool affects_opacity =
        effect->Affects(PropertyHandle(GetCSSPropertyOpacity()));
    const bool affects_transform =
        effect->Affects(PropertyHandle(GetCSSPropertyTransform())) ||
        effect->Affects(PropertyHandle(GetCSSPropertyTranslate())) ||
        effect->Affects(PropertyHandle(GetCSSPropertyScale())) ||
        effect->Affects(PropertyHandle(GetCSSPropertyRotate()));
    const bool affects_background =
        effect->Affects(PropertyHandle(GetCSSPropertyBackgroundColor()));
    Element* target = effect->EffectTarget();
    if (!target) {
      continue;
    }
    target->SetNeedsAnimationStyleRecalc();
    target->SetAnimationStyleChange(true);
    if (LayoutObject* layout_object = target->GetLayoutObject()) {
      if (affects_opacity || affects_transform) {
        MarkPaintPropertyTargetForStandaloneRenderer(
            *layout_object, affects_opacity, affects_transform);
      } else {
        if (affects_background) {
          layout_object->SetBackgroundNeedsFullPaintInvalidation();
        }
        layout_object->SetShouldDoFullPaintInvalidationWithoutLayoutChange(
            PaintInvalidationReason::kStyle);
      }
      if (LocalFrameView* frame_view = layout_object->GetFrameView()) {
        frame_view->SetPaintArtifactCompositorNeedsUpdate();
      }
    }
  }
  if (Element* document_element = document.documentElement()) {
    MarkComputedPaintPropertyTargetsForStandaloneRenderer(*document_element);
  }
}

void UpdateFrameSchedulingStateForStandaloneRenderer(
    Document& document,
    LocalFrameView& frame_view,
    bool has_standalone_animation_source) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.active_animation_count = 0;
  for (Animation* animation : document.Timeline().GetAnimations()) {
    if (!animation || animation->AnimationHasNoEffect()) {
      continue;
    }
    if (animation->Playing() || animation->EffectivelyPlaying() ||
        animation->CompositorPending()) {
      ++cache.active_animation_count;
    }
  }
  cache.needs_animation_timing_update =
      document.GetDocumentAnimations().NeedsAnimationTimingUpdate();
  cache.needs_lifecycle_update =
      document.NeedsLayoutTreeUpdate() || frame_view.NeedsLayout();
  cache.needs_begin_frame = cache.active_animation_count > 0 ||
                            cache.needs_animation_timing_update ||
                            cache.needs_lifecycle_update;
  cache.needs_output = cache.needs_output ||
                       (has_standalone_animation_source &&
                        cache.active_animation_count > 0);
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
  cache.finer_cache_units_by_chunk.clear();
  cache.finer_cache_units_by_chunk.resize(chunk_count);
  TraceLiveFrameProbeStage("paint audit after chunks/items");
  cache.artifact_audit_lines.push_back(
      "paint_artifact_audit summary chunks=" + std::to_string(chunk_count) +
      " display_items=" + std::to_string(display_item_count));

  std::map<std::string, int> total_op_histogram;
  std::map<std::string, int> total_recursive_op_histogram;
  std::map<std::string, int> total_unsupported_histogram;
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
                  << ",\"unsupported_ops\":{},\"unsupported_retained_ops\":{}"
                  << ",\"finer_cache_unit_metadata\":"
                  << FinerCacheUnitMetadataJsonForStandaloneRenderer(
                         chunk_index, empty_stable_key, {})
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
    int chunk_op_count = 0;
    int chunk_recursive_op_count = 0;
    int drawing_item_count = 0;
    int non_drawing_item_count = 0;
    RawPaintRecordAudit chunk_raw_audit;
    std::vector<FinerCacheUnitAudit> finer_cache_units;
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
      const bool item_is_scrollbar = item.IsScrollbar();
      const DisplayItemClientId item_client_id = item.ClientId();
      display_items_json << "{\"index\":" << item_index << ",\"id\":"
                         << JsonStringForStandaloneRenderer(item_id)
                         << ",\"type\":"
                         << JsonStringForStandaloneRenderer(item_type)
                         << ",\"client_id\":"
                         << static_cast<uint64_t>(item_client_id)
                         << ",\"client_id_valid\":"
                         << (item_client_id != kInvalidDisplayItemClientId
                                 ? "true"
                                 : "false")
                         << ",\"client_debug_name\":null"
                         << ",\"client_owner_node_id\":null"
                         << ",\"visual_rect\":"
                         << RectJsonForStandaloneRenderer(item_visual_rect)
                         << ",\"is_drawing\":"
                         << (item_is_drawing ? "true" : "false")
                         << ",\"is_scrollbar\":"
                         << (item_is_scrollbar ? "true" : "false");
      RawPaintRecordAudit item_audit;
      if (!item_is_drawing) {
        ++non_drawing_item_count;
        const auto* scrollbar = DynamicTo<ScrollbarDisplayItem>(item);
        if (scrollbar) {
          std::ostringstream paint_ops_json;
          paint_ops_json << "[";
          cc::PaintRecord scrollbar_record = scrollbar->Paint();
          AppendPaintRecordAuditJson(scrollbar_record, item_audit,
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
          chunk_op_count += item_audit.paint_op_count;
          chunk_recursive_op_count += item_audit.recursive_paint_op_count;
          MergeRawPaintRecordAudit(chunk_raw_audit, item_audit);
          AppendDisplayItemToFinerCacheUnits(
              finer_cache_units, item_index, item_client_id, item_id,
              item_type, item_visual_rect, item_is_drawing,
              item_is_scrollbar, item_audit);
          display_items_json
              << ",\"scrollbar_paint_record_extracted\":true"
              << ",\"paint_record_op_histogram\":"
              << MapToJsonObject(item_audit.top_level_histogram)
              << ",\"recursive_paint_record_op_histogram\":"
              << MapToJsonObject(item_audit.recursive_histogram)
              << ",\"paint_ops\":" << paint_ops_json.str() << "}";
          continue;
        }
        AppendDisplayItemToFinerCacheUnits(
            finer_cache_units, item_index, item_client_id, item_id, item_type,
            item_visual_rect, item_is_drawing, item_is_scrollbar, item_audit);
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
        AppendDisplayItemToFinerCacheUnits(
            finer_cache_units, item_index, item_client_id, item_id, item_type,
            item_visual_rect, item_is_drawing, item_is_scrollbar, item_audit);
        display_items_json
            << ",\"paint_record_op_histogram\":{},\"recursive_paint_record_op_histogram\":{},\"paint_ops\":[]}";
        continue;
      }
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
      chunk_op_count += item_audit.paint_op_count;
      chunk_recursive_op_count += item_audit.recursive_paint_op_count;
      MergeRawPaintRecordAudit(chunk_raw_audit, item_audit);
      AppendDisplayItemToFinerCacheUnits(
          finer_cache_units, item_index, item_client_id, item_id, item_type,
          item_visual_rect, item_is_drawing, item_is_scrollbar, item_audit);
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
    total_op_count += chunk_op_count;
    total_recursive_op_count += chunk_recursive_op_count;
    total_drawing_item_count += drawing_item_count;
    total_non_drawing_item_count += non_drawing_item_count;
    total_raw_audit.visual_op_count += chunk_raw_audit.visual_op_count;
    total_raw_audit.retained_supported_visual_op_count +=
        chunk_raw_audit.retained_supported_visual_op_count;
    total_raw_audit.retained_unsupported_visual_op_count +=
        chunk_raw_audit.retained_unsupported_visual_op_count;
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
    const std::string chunk_unsupported_retained_histogram_json =
        MapToJsonObject(chunk_unsupported_histogram);
    const std::string display_items_json_string = display_items_json.str();
    const std::string finer_cache_unit_metadata_json =
        FinerCacheUnitMetadataJsonForStandaloneRenderer(
            chunk_index, stable_key, finer_cache_units);
    std::vector<LiveFinerCacheUnitDescriptor> exported_finer_units;
    exported_finer_units.reserve(finer_cache_units.size());
    for (const FinerCacheUnitAudit& unit : finer_cache_units) {
      exported_finer_units.push_back(
          ExportFinerCacheUnitDescriptor(stable_key, unit));
    }
    if (cache.finer_cache_units_by_chunk.size() <= chunk_index) {
      cache.finer_cache_units_by_chunk.resize(chunk_index + 1);
    }
    cache.finer_cache_units_by_chunk[chunk_index] =
        std::move(exported_finer_units);
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
                << ",\"unsupported_retained_ops\":"
                << chunk_unsupported_retained_histogram_json
                << ",\"finer_cache_unit_metadata\":"
                << finer_cache_unit_metadata_json
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
      std::getenv("HTML_CSS_RENDERER_PAGE_EVIDENCE") && cache.holder
          ? PageEvidenceJsonForStandaloneRenderer(cache.holder->GetDocument())
          : "{\"status\":\"inaccessible\",\"field\":\"page_evidence\","
            "\"reason\":\"optional PageEvidenceJsonForStandaloneRenderer walk "
            "is disabled by default; set "
            "HTML_CSS_RENDERER_PAGE_EVIDENCE=1 for coordinate-correct element "
            "evidence\"}";
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
  const bool img_layout_record_paint =
      lowered_input.find("<img") != std::string::npos &&
      cache.image_reachability.layout_is_layout_image &&
      cache.image_reachability.loader_content_loaded &&
      StandaloneRendererLayoutImagePaintReplacedCalled() > 0 &&
      StandaloneRendererImagePainterPaintReplacedCalled() > 0;
  const bool has_standalone_image_paint =
      total_raw_audit.image_count > 0 || img_layout_record_paint;
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
  if (!has_standalone_image_paint &&
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
       << ",\"wheel_scroll_diagnostics\":{\"requested\":"
       << (cache.requested_wheel_scroll ? "true" : "false")
       << ",\"x\":" << cache.requested_wheel_x
       << ",\"y\":" << cache.requested_wheel_y
       << ",\"delta\":{\"x\":" << cache.requested_wheel_delta_x
       << ",\"y\":" << cache.requested_wheel_delta_y
       << "},\"applied_to_blink\":"
       << (cache.wheel_scroll_applied ? "true" : "false")
       << ",\"changed\":"
       << (cache.wheel_scroll_changed ? "true" : "false")
       << ",\"target_is_element\":"
       << (cache.wheel_scroll_target_is_element ? "true" : "false")
       << ",\"target_element_id\":"
       << JsonStringForStandaloneRenderer(cache.wheel_scroll_target_element_id)
       << ",\"applied\":{\"x\":" << cache.wheel_scroll_applied_x
       << ",\"y\":" << cache.wheel_scroll_applied_y << "}"
       << ",\"maximum\":{\"x\":" << cache.wheel_scroll_max_x
       << ",\"y\":" << cache.wheel_scroll_max_y << "}"
       << ",\"status\":"
       << JsonStringForStandaloneRenderer(cache.wheel_scroll_status) << "}"
       << ",\"mouse_input_events\":{\"requested_count\":"
       << cache.requested_mouse_input_events.size()
       << ",\"dispatched_count\":" << cache.mouse_input_event_dispatch_count
       << ",\"dispatched_via_blink_event_handler\":"
       << (cache.mouse_input_events_dispatched ? "true" : "false")
       << ",\"status\":"
       << JsonStringForStandaloneRenderer(cache.mouse_input_status) << "}"
       << ",\"keyboard_input_events\":{\"requested_count\":"
       << cache.requested_keyboard_input_events.size()
       << ",\"dispatched_count\":" << cache.keyboard_input_event_dispatch_count
       << ",\"dispatched_via_blink_event_handler\":"
       << (cache.keyboard_input_events_dispatched ? "true" : "false")
       << ",\"status\":"
       << JsonStringForStandaloneRenderer(cache.keyboard_input_status) << "}"
       << ",\"pointer_interaction\":{\"requested\":"
       << (cache.requested_pointer_state ? "true" : "false")
       << ",\"pressed\":"
       << (cache.requested_pointer_pressed ? "true" : "false")
       << ",\"event_type\":" << cache.requested_pointer_event_type
       << ",\"x\":" << cache.requested_pointer_x
       << ",\"y\":" << cache.requested_pointer_y
       << ",\"applied_to_blink\":"
       << (cache.pointer_state_applied ? "true" : "false")
       << ",\"status\":"
       << JsonStringForStandaloneRenderer(cache.pointer_state_status)
       << ",\"hit_element_id\":"
       << JsonStringForStandaloneRenderer(cache.pointer_hit_element_id)
       << ",\"hit_element_tag\":"
       << JsonStringForStandaloneRenderer(cache.pointer_hit_element_tag)
       << ",\"hit_element_class\":"
       << JsonStringForStandaloneRenderer(cache.pointer_hit_element_class)
       << ",\"hover_element_id\":"
       << JsonStringForStandaloneRenderer(cache.pointer_hover_element_id)
       << ",\"hover_element_tag\":"
       << JsonStringForStandaloneRenderer(cache.pointer_hover_element_tag)
       << ",\"hover_element_class\":"
       << JsonStringForStandaloneRenderer(cache.pointer_hover_element_class)
       << ",\"focus_requested\":"
       << (cache.pointer_focus_requested ? "true" : "false")
       << ",\"focus_applied_to_blink\":"
       << (cache.pointer_focus_applied ? "true" : "false")
       << ",\"focused_element_id\":"
       << JsonStringForStandaloneRenderer(cache.pointer_focused_element_id)
       << ",\"focus_status\":"
       << JsonStringForStandaloneRenderer(cache.pointer_focus_status)
       << ",\"activation_requested\":"
       << (cache.pointer_activation_requested ? "true" : "false")
       << ",\"activation_applied_to_blink\":"
       << (cache.pointer_activation_applied ? "true" : "false")
       << ",\"activation_element_id\":"
       << JsonStringForStandaloneRenderer(cache.pointer_activation_element_id)
       << ",\"activation_down_element_id\":"
       << JsonStringForStandaloneRenderer(
              cache.pointer_activation_down_element_id)
       << ",\"activation_node_id\":" << cache.pointer_activation_node_id
       << ",\"activation_down_node_id\":"
       << cache.pointer_activation_down_node_id
       << ",\"activation_status\":"
       << JsonStringForStandaloneRenderer(cache.pointer_activation_status)
       << "}"
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
          "\"color\",\"transform\",\"length\"]"
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
       << ",\"device_scale_factor\":" << cache.device_scale_factor
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
       << "\"standalone_paints_scrollbars\":true,"
       << "\"standard_scrollbars_painted\":true,"
       << "\"custom_scrollbars_painted\":false,"
       << "\"overlay_or_visual_viewport_scrollbars_painted\":false,"
       << "\"paint_source\":\"ScrollbarDisplayItem::Paint\","
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
       << ",\"unsupported_retained_raw_op_histogram\":"
       << MapToJsonObject(total_unsupported_histogram)
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
  const LiveExportedDrawOp* first_draw_image_op = nullptr;
  for (const LiveExportedDrawOp& op : cache.exported_draw_ops) {
    if (op.type == 22) {
      first_draw_image_op = &op;
      break;
    }
  }
  json << image_element_count << ",\"src_scheme_histogram\":"
       << MapToJsonObject(image_scheme_histogram)
       << ",\"resource_load_status\":\""
       << (image_element_count > 0 && !has_standalone_image_paint
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
       << ",\"loader_content_loaded\":"
       << (cache.image_reachability.loader_content_loaded ? "true" : "false")
       << ",\"loader_content_loading\":"
       << (cache.image_reachability.loader_content_loading ? "true" : "false")
       << ",\"loader_content_status\":"
       << cache.image_reachability.loader_content_status
       << ",\"image_element_complete\":"
       << (cache.image_reachability.image_element_complete ? "true" : "false")
       << ",\"image_element_primary_content\":"
       << (cache.image_reachability.image_element_primary_content ? "true"
                                                                  : "false")
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
       << JsonStringForStandaloneRenderer(provider_image_status)
       << ",\"paint_into_rect_called\":"
       << (cache.image_paint_into_rect.called ? "true" : "false")
       << ",\"paint_into_rect_count\":"
       << cache.image_paint_into_rect.count
       << ",\"paint_into_rect_dest\":["
       << cache.image_paint_into_rect.dest_x << ","
       << cache.image_paint_into_rect.dest_y << ","
       << cache.image_paint_into_rect.dest_width << ","
       << cache.image_paint_into_rect.dest_height << "]"
       << ",\"paint_into_rect_content\":["
       << cache.image_paint_into_rect.content_x << ","
       << cache.image_paint_into_rect.content_y << ","
       << cache.image_paint_into_rect.content_width << ","
       << cache.image_paint_into_rect.content_height << "]"
       << ",\"paint_into_rect_pixel_snapped_dest\":["
       << cache.image_paint_into_rect.snapped_dest_x << ","
       << cache.image_paint_into_rect.snapped_dest_y << ","
       << cache.image_paint_into_rect.snapped_dest_width << ","
       << cache.image_paint_into_rect.snapped_dest_height << "]"
       << ",\"paint_into_rect_src\":["
       << cache.image_paint_into_rect.src_x << ","
       << cache.image_paint_into_rect.src_y << ","
       << cache.image_paint_into_rect.src_width << ","
       << cache.image_paint_into_rect.src_height << "]"
       << ",\"paint_into_rect_image_size\":["
       << cache.image_paint_into_rect.image_width << ","
       << cache.image_paint_into_rect.image_height << "]"
       << ",\"paint_into_rect_interpolation_quality\":"
       << cache.image_paint_into_rect.interpolation_quality
       << ",\"first_draw_image_op\":";
  if (first_draw_image_op) {
    json << "{\"label\":"
         << JsonStringForStandaloneRenderer(first_draw_image_op->debug_label)
         << ",\"dst_rect\":[" << first_draw_image_op->x << ","
         << first_draw_image_op->y << "," << first_draw_image_op->width
         << "," << first_draw_image_op->height << "]"
         << ",\"src_rect\":[" << first_draw_image_op->src_x << ","
         << first_draw_image_op->src_y << ","
         << first_draw_image_op->src_width << ","
         << first_draw_image_op->src_height << "]"
         << ",\"image_size\":[" << first_draw_image_op->mask_width << ","
         << first_draw_image_op->mask_height << "]"
         << ",\"sampling_options\":"
         << JsonStringForStandaloneRenderer(
                first_draw_image_op->sampling_options)
         << ",\"source_chunk_index\":"
         << first_draw_image_op->source_chunk_index
         << ",\"source_display_item_index\":"
         << first_draw_image_op->source_display_item_index << "}";
  } else {
    json << "null";
  }
  json << "}"
       << ",\"image_pipeline\":{\"image_element_count\":"
       << image_element_count << ",\"images\":[";
  const std::vector<std::string> image_sources =
      ImageSrcListForStandaloneRenderer(cache.body_html);
  for (size_t i = 0; i < image_sources.size(); ++i) {
    if (i > 0) {
      json << ",";
    }
    const std::string& src = image_sources[i];
    const bool has_image_paint = has_standalone_image_paint;
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
         << ",\"loader_content_loaded\":"
         << (cache.image_reachability.loader_content_loaded ? "true" : "false")
         << ",\"loader_content_loading\":"
         << (cache.image_reachability.loader_content_loading ? "true" : "false")
         << ",\"loader_content_status\":"
         << cache.image_reachability.loader_content_status
         << ",\"image_element_complete\":"
         << (cache.image_reachability.image_element_complete ? "true" : "false")
         << ",\"image_element_primary_content\":"
         << (cache.image_reachability.image_element_primary_content ? "true"
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
       << ",\"raw_ops_lost_during_retained_extraction\":";
  int visual_unsupported_ops = 0;
  for (const auto& [name, count] : total_unsupported_histogram) {
    visual_unsupported_ops += count;
  }
  const int raw_ops_lost =
      std::max(0, total_raw_audit.visual_op_count -
                      total_raw_audit.retained_supported_visual_op_count -
                      total_raw_audit.retained_unsupported_visual_op_count);
  json << raw_ops_lost
       << ",\"visual_unsupported_ops\":" << visual_unsupported_ops
       << ",\"unsupported_retained_ops\":" << visual_unsupported_ops << "}"
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

void BuildPaintArtifactRetainedMetadata(const PaintArtifact& artifact,
                                        LiveFramePaintProbeCache& cache) {
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  const PaintChunks& chunks = artifact.GetPaintChunks();
  const DisplayItemList& items = artifact.GetDisplayItemList();
  const wtf_size_t chunk_count = chunks.size();
  cache.finer_cache_units_by_chunk.clear();
  cache.finer_cache_units_by_chunk.resize(chunk_count);
  cache.artifact_audit_lines.push_back(
      "paint_artifact_audit summary chunks=" + std::to_string(chunk_count) +
      " display_items=" + std::to_string(items.size()) +
      " mode=retained_metadata_only");

  cache.chunk_stable_keys.resize(chunk_count);
  cache.chunk_id_strings.resize(chunk_count);
  for (wtf_size_t chunk_index = 0; chunk_index < chunk_count; ++chunk_index) {
    const PaintChunk& chunk = chunks[chunk_index];
    const std::string chunk_id =
        BlinkStringToStdStringForStandaloneRenderer(chunk.id.ToString());
    std::string stable_key;
    if (chunk.begin_index == chunk.end_index) {
      stable_key =
          !chunk_id.empty()
              ? "blink-chunk:id=" + chunk_id + ":empty"
              : "blink-chunk:empty:debug-index=" +
                    std::to_string(chunk_index);
    } else {
      const PropertyTreeState chunk_state = chunk.properties.Unalias();
      const gfx::Transform projection = DirectTransformToRootForStandaloneRenderer(
          chunk_state, nullptr, nullptr);
      const std::string property_fingerprint =
          chunk_id + ":" + std::to_string(chunk.begin_index) + ":" +
          std::to_string(chunk.end_index) + ":" +
          MatrixJsonForStandaloneRenderer(projection);
      const uint64_t property_hash =
          HashStringForStandaloneRenderer(property_fingerprint);
      stable_key =
          !chunk_id.empty()
              ? "blink-chunk:id=" + chunk_id + ":state=" +
                    std::to_string(property_hash)
              : "blink-chunk:fingerprint=" +
                    std::to_string(HashStringForStandaloneRenderer(
                        std::to_string(chunk.begin_index) + ":" +
                        std::to_string(chunk.end_index))) +
                    ":state=" + std::to_string(property_hash) +
                    ":debug-index=" + std::to_string(chunk_index);
    }
    cache.chunk_stable_keys[chunk_index] = stable_key;
    cache.chunk_id_strings[chunk_index] = chunk_id;
  }
}

std::string BuildRetainedMetadataTimingJsonForStandaloneRenderer(
    const LiveFramePaintProbeCache& cache) {
  std::ostringstream json;
  json << "{\"source\":\"real Blink PaintArtifact\","
       << "\"audit_mode\":\"retained_metadata_only\","
       << "\"render_timing_diagnostics\":{"
       << "\"mode\":\"in_process_probe_chrono\","
       << "\"warm_or_cold\":\"cold_or_rebuilt_probe_state\","
       << "\"cache_hit\":" << (cache.timing_cache_hit ? "true" : "false")
       << ",\"input_setup_ms\":" << cache.timing_input_setup_ms
       << ",\"html_parse_document_setup_ms\":"
       << cache.timing_html_document_setup_ms
       << ",\"style_update_ms\":" << cache.timing_style_update_ms
       << ",\"layout_lifecycle_ms\":" << cache.timing_layout_lifecycle_ms
       << ",\"prepaint_paint_lifecycle_ms\":"
       << cache.timing_prepaint_and_paint_lifecycle_ms
       << ",\"paint_artifact_generation_ms\":"
       << cache.timing_paint_artifact_generation_ms
       << ",\"paint_artifact_audit_json_ms\":"
       << cache.timing_paint_artifact_audit_ms
       << ",\"paint_artifact_extraction_ms\":"
       << cache.timing_paint_artifact_extraction_ms
       << ",\"total_probe_ms\":" << cache.timing_total_ms
       << ",\"caveat\":\"probe timings exclude process startup and CPU replay\""
       << "}}";
  return json.str();
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
      "paint_op_extraction unsupported_retained_ops reason=incomplete "
      "requires=PaintArtifactCompositor/cc");
  TraceLiveFrameProbeStage("export retained extraction incomplete");
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
}

void EnsureWtfInitializedForStandaloneRenderer() {
  static bool initialized = false;
  if (!initialized) {
    InstallStandaloneMojoThunksForStandaloneRenderer();
    blink::InitializeWtf();
    blink::Length::Initialize();
    blink::CoreInitializer::GetInstance().Initialize();
    initialized = true;
  }
}

int CountCcLayersForStandaloneRenderer(const cc::Layer* layer) {
  if (!layer) {
    return 0;
  }
  int count = 1;
  for (const scoped_refptr<cc::Layer>& child : layer->children()) {
    count += CountCcLayersForStandaloneRenderer(child.get());
  }
  return count;
}

enum class StandaloneCcFrameAdvanceMode {
  kCompositeForTest,
  kSchedulerCallback,
};

std::optional<LiveFramePaintProbeResult>
UpdateStandaloneBlinkLifecyclePacAndCcForStandaloneRenderer(
    LiveFramePaintProbeCache& cache,
    const std::string& input_html,
    bool html_content_already_loaded,
    Document& document,
    LocalFrameView& frame_view,
    LiveFramePaintProbeResult& result,
    StandaloneCcFrameAdvanceMode cc_advance_mode) {
  frame_view.SetCanHaveScrollbars(false);
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
  const bool seeded_animation_start_time =
      !html_content_already_loaded &&
      (cache.animation_time_requested ||
       HtmlContainsStandaloneAnimationForRenderer(input_html));
  if (seeded_animation_start_time) {
    SeedAnimationStartTimeForStandaloneRenderer(document);
    TraceAnimationStateForStandaloneRenderer("after_seed_zero", document);
  }
  if (cache.animation_time_requested) {
    UpdateLifecycleToLayoutCleanForStandaloneRenderer(
        frame_view, DocumentUpdateReason::kTest);
  }
  UpdateLifecycleToLayoutCleanForStandaloneRenderer(
      frame_view, DocumentUpdateReason::kTest);
  TraceAnimationStateForStandaloneRenderer("after_initial_layout_clean",
                                           document);
  if (seeded_animation_start_time) {
    document.GetPendingAnimations().Update(nullptr, false);
    document.GetDocumentAnimations().UpdateAnimationTimingIfNeeded();
    TraceAnimationStateForStandaloneRenderer("after_initial_pending_update",
                                             document);
  }
  if (cache.animation_time_requested) {
    TraceLiveFrameProbeStage("before standalone animation time apply");
    TraceAnimationStateForStandaloneRenderer("before_requested_time_apply",
                                             document);
    document.GetPendingAnimations().Update(nullptr, false);
    ApplyAnimationTimeForStandaloneRenderer(document);
    TraceAnimationStateForStandaloneRenderer("after_requested_time_apply",
                                             document);
    if (cache.animation_time_applied) {
      MarkAnimatedPaintPropertyTargetsForStandaloneRenderer(document);
      UpdateLifecycleToLayoutCleanForStandaloneRenderer(
          frame_view, DocumentUpdateReason::kTest);
      MarkAnimatedPaintPropertyTargetsForStandaloneRenderer(document);
      UpdateLifecycleToLayoutCleanForStandaloneRenderer(
          frame_view, DocumentUpdateReason::kTest);
      TraceAnimationStateForStandaloneRenderer("after_requested_time_layout",
                                               document);
    }
    TraceLiveFrameProbeStage("after standalone animation time apply");
  }
  UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
  TraceLiveFrameProbeStage("after required layout lifecycle update");
  if (!cache.requested_pointer_state && cache.requested_interaction_state) {
    ApplyInteractionStateForStandaloneRenderer(
        document, cache.requested_hovered_element_id,
        cache.requested_active_element_id);
  }
  frame_view.SetNeedsUpdateGeometries();
  frame_view.UpdateGeometry();
  const bool preapply_element_scroll_for_wheel =
      cache.requested_wheel_scroll && !cache.wheel_scroll_applied;
  if (preapply_element_scroll_for_wheel) {
    TraceLiveFrameProbeStage("before pre-wheel element scroll offset apply");
    ApplyElementScrollOffsetsForStandaloneRenderer(document);
    TraceLiveFrameProbeStage("after pre-wheel element scroll offset apply");
  }
  TraceLiveFrameProbeStage("before document scroll offset apply");
  ApplyDocumentScrollOffsetForStandaloneRenderer(
      frame_view, /*apply_wheel_scroll=*/false);
  TraceLiveFrameProbeStage("after document scroll offset apply");
  if (!cache.requested_wheel_scroll || !cache.wheel_scroll_applied) {
    TraceLiveFrameProbeStage("before element scroll offset apply");
    ApplyElementScrollOffsetsForStandaloneRenderer(document);
    TraceLiveFrameProbeStage("after element scroll offset apply");
  }
  UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
  TraceLiveFrameProbeLifecycleState("pre-input before prepaint lifecycle update",
                                    &document, document.GetFrame(),
                                    &frame_view);
  TraceLiveFrameProbeStage("before pre-input prepaint lifecycle update");
  UpdateAllLifecyclePhasesExceptPaintForStandaloneRenderer(
      frame_view, DocumentUpdateReason::kTest);
  TraceLiveFrameProbeStage("after pre-input prepaint lifecycle update");
  TraceLiveFrameProbeLifecycleState("pre-input after prepaint lifecycle update",
                                    &document, document.GetFrame(),
                                    &frame_view);
  DispatchMouseInputEventsForStandaloneRenderer(document, frame_view);
  if (cache.pointer_state_applied || cache.pointer_focus_requested) {
    TraceLiveFrameProbeStage("before post-pointer lifecycle update");
    document.UpdateStyleAndLayoutTree();
    UpdateLifecycleToLayoutCleanForStandaloneRenderer(
        frame_view, DocumentUpdateReason::kTest);
    TraceLiveFrameProbeStage("after post-pointer lifecycle update");
  }
  DispatchKeyboardInputEventsForStandaloneRenderer(document, frame_view);
  if (cache.keyboard_input_events_dispatched) {
    TraceLiveFrameProbeStage("before post-keyboard lifecycle update");
    document.UpdateStyleAndLayoutTree();
    UpdateLifecycleToLayoutCleanForStandaloneRenderer(
        frame_view, DocumentUpdateReason::kTest);
    TraceLiveFrameProbeStage("after post-keyboard lifecycle update");
  }
  CollectFormControlEntriesForStandaloneRenderer(document,
                                                cache.form_control_entries);
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
  const bool preapply_post_lifecycle_element_scroll_for_wheel =
      cache.requested_wheel_scroll && !cache.wheel_scroll_applied;
  if (preapply_post_lifecycle_element_scroll_for_wheel) {
    TraceLiveFrameProbeStage(
        "before post-lifecycle pre-wheel element scroll offset apply");
    ApplyElementScrollOffsetsForStandaloneRenderer(document);
    TraceLiveFrameProbeStage(
        "after post-lifecycle pre-wheel element scroll offset apply");
  }
  TraceLiveFrameProbeStage("before post-lifecycle document scroll offset apply");
  ApplyDocumentScrollOffsetForStandaloneRenderer(
      frame_view, /*apply_wheel_scroll=*/true);
  TraceLiveFrameProbeStage("after post-lifecycle document scroll offset apply");
  if (!cache.requested_wheel_scroll || !cache.wheel_scroll_applied) {
    TraceLiveFrameProbeStage(
        "before post-lifecycle element scroll offset apply");
    ApplyElementScrollOffsetsForStandaloneRenderer(document);
    TraceLiveFrameProbeStage("after post-lifecycle element scroll offset apply");
  }
  UpdateStickyConstraintsForStandaloneRenderer(frame_view, document);
  if (cc_advance_mode == StandaloneCcFrameAdvanceMode::kCompositeForTest) {
    SubmitStandaloneBlinkCompositorStateToCcForStandaloneRenderer(
        cache, "before standalone cc composite",
        "after standalone cc composite");
  } else {
    SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  }
  if (cache.scroll_offset_changed || cache.element_scroll_offset_changed ||
      cache.wheel_scroll_changed) {
    if (cache.scroll_offset_requested || cache.element_scroll_offset_requested ||
        cache.requested_wheel_scroll) {
      cache.needs_output = true;
    }
    TraceLiveFrameProbeStage("before post-scroll lifecycle update");
    result.lifecycle_reached_paint_clean =
        UpdateAllLifecyclePhasesForTestForStandaloneRenderer(frame_view) ? 1
                                                                         : 0;
    TraceLiveFrameProbeStage("after post-scroll lifecycle update");
    if (cc_advance_mode == StandaloneCcFrameAdvanceMode::kCompositeForTest) {
      SubmitStandaloneBlinkCompositorStateToCcForStandaloneRenderer(
          cache, "before post-scroll standalone cc composite",
          "after post-scroll standalone cc composite");
    } else {
      SyncStandaloneCcHostStateForStandaloneRenderer(cache);
    }
  }
  UpdateFrameSchedulingStateForStandaloneRenderer(
      document, frame_view,
      HtmlContainsStandaloneAnimationForRenderer(input_html));
  cache.timing_prepaint_and_paint_lifecycle_ms =
      StandaloneProbeElapsedMs(paint_lifecycle_start,
                               StandaloneProbeClock::now());
  return std::nullopt;
}

bool CanProcessMouseMoveOnlyFrameWithoutCcScheduler(
    const LiveFramePaintProbeCache& cache) {
  if (cache.requested_mouse_input_events.empty()) {
    return false;
  }
  if (cache.copy_output_png_requested || cache.copy_output_raw_requested ||
      cache.copy_output_gpu_requested || cache.requested_wheel_scroll ||
      !cache.requested_keyboard_input_events.empty() ||
      !cache.requested_dom_mutations.empty()) {
    return false;
  }
  for (const StandaloneMouseInputEventForRenderer& event :
       cache.requested_mouse_input_events) {
    if (WebMouseEventTypeForStandaloneRenderer(event.type) !=
            WebInputEvent::Type::kMouseMove ||
        event.button != 0 || event.modifiers != 0 || event.click_count != 0) {
      return false;
    }
  }
  return true;
}

bool ScheduleStandaloneBlinkCompositorStateThroughCcSchedulerForStandaloneRenderer(
    LiveFramePaintProbeCache& cache,
    const std::string& input_html,
    bool html_content_already_loaded,
    Document& document,
    LocalFrameView& frame_view,
    LiveFramePaintProbeResult& result) {
  if (!cache.cc_layer_host) {
    cache.cc_layer_host = std::make_unique<StandaloneCcLayerHost>();
  }
  const bool lightweight_update_without_output_request =
      !cache.collect_frame_diagnostics && !cache.copy_output_png_requested &&
      !cache.copy_output_raw_requested && !cache.copy_output_gpu_requested &&
      !cache.copy_output_gpu_prepare_requested;
  if (cache.copy_output_gpu_requested ||
      cache.copy_output_gpu_prepare_requested ||
      (!lightweight_update_without_output_request &&
       (cache.copy_output_gpu_use_vulkan_offscreen ||
        cache.copy_output_gpu_use_d3d12_offscreen))) {
    cache.cc_layer_host->SetGpuOffscreenOutputMode(
        cache.copy_output_gpu_use_vulkan_offscreen,
        cache.copy_output_gpu_use_d3d12_offscreen);
  }
  cache.cc_frame_sink_failure_reason.clear();
  if (!cache.cc_layer_host->EnsureHostForScheduler(
          gfx::Size(cache.viewport_width, cache.viewport_height),
          cache.device_scale_factor,
          &cache.cc_frame_sink_failure_reason)) {
    SyncStandaloneCcHostStateForStandaloneRenderer(cache);
    return false;
  }
  if (lightweight_update_without_output_request) {
    std::optional<LiveFramePaintProbeResult> lifecycle_stop_result =
        UpdateStandaloneBlinkLifecyclePacAndCcForStandaloneRenderer(
            cache, input_html, html_content_already_loaded, document,
            frame_view, result,
            StandaloneCcFrameAdvanceMode::kSchedulerCallback);
    SyncStandaloneCcTimingForStandaloneRenderer(cache);
    SyncStandaloneCcHostStateForStandaloneRenderer(cache);
    cache.timing_cc_scheduler_run_loop_ms = 0.0;
    if (lifecycle_stop_result) {
      cache.result = *lifecycle_stop_result;
    }
    return true;
  }
  const bool mouse_move_only_fast_path =
      CanProcessMouseMoveOnlyFrameWithoutCcScheduler(cache) &&
      cache.cc_layer_host->root_layer_attached() &&
      cache.cc_layer_host->frame_sink_bound();
  if (mouse_move_only_fast_path) {
    std::optional<LiveFramePaintProbeResult> lifecycle_stop_result =
        UpdateStandaloneBlinkLifecyclePacAndCcForStandaloneRenderer(
            cache, input_html, html_content_already_loaded, document,
            frame_view, result,
            StandaloneCcFrameAdvanceMode::kSchedulerCallback);
    SyncStandaloneCcTimingForStandaloneRenderer(cache);
    SyncStandaloneCcHostStateForStandaloneRenderer(cache);
    cache.timing_cc_scheduler_run_loop_ms = 0.0;
    if (lifecycle_stop_result) {
      cache.result = *lifecycle_stop_result;
    }
    if (!cache.needs_output && !cache.copy_output_png_requested &&
        !cache.copy_output_raw_requested && !cache.copy_output_gpu_requested) {
      return true;
    }
  }
  if (!cache.cc_layer_host->EnsureFrameSinkReadyForScheduler(
          &cache.cc_frame_sink_failure_reason)) {
    SyncStandaloneCcHostStateForStandaloneRenderer(cache);
    return false;
  }
  if (cache.copy_output_png_requested || cache.copy_output_raw_requested ||
      cache.copy_output_gpu_requested) {
    if (cache.copy_output_gpu_requested) {
      cache.cc_layer_host->RequestNextGpuFrameOutput(
          cache.copy_output_gpu_use_vulkan_offscreen,
          cache.copy_output_gpu_use_d3d12_offscreen);
    } else {
      cache.cc_layer_host->RequestNextCopyOutput(
          cache.copy_output_png_requested, cache.copy_output_raw_requested,
          /*wants_gpu=*/false);
    }
  }

  std::optional<LiveFramePaintProbeResult> lifecycle_stop_result;
  auto pre_attach_root = [&cache, &frame_view]() {
    TraceLiveFrameProbeStage("before standalone cc scheduler PAC root preattach");
    frame_view.EnsurePaintArtifactCompositorRootLayerAttachedForStandaloneRenderer();
    SyncStandaloneCcHostStateForStandaloneRenderer(cache);
    TraceLiveFrameProbeStage("after standalone cc scheduler PAC root preattach");
  };
  auto update = [&cache, &input_html, html_content_already_loaded, &document,
                 &frame_view, &result, &lifecycle_stop_result]() {
    lifecycle_stop_result =
        UpdateStandaloneBlinkLifecyclePacAndCcForStandaloneRenderer(
            cache, input_html, html_content_already_loaded, document,
            frame_view, result,
            StandaloneCcFrameAdvanceMode::kSchedulerCallback);
  };

  TraceLiveFrameProbeStage("before standalone cc scheduler frame");
  const auto scheduler_start = StandaloneProbeClock::now();
  const bool bounded_vulkan_prepare =
      cache.copy_output_gpu_prepare_requested &&
      cache.copy_output_gpu_use_vulkan_offscreen &&
      cache.cc_layer_host->frame_sink_bound() &&
      cache.cc_layer_host->root_layer_attached();
  bool scheduler_timed_out = false;
  const bool submitted =
      cache.cc_layer_host->ScheduleFrameWithPendingLayerTreeUpdateForScheduler(
          std::move(pre_attach_root), std::move(update),
          bounded_vulkan_prepare ? base::Milliseconds(16)
                                 : base::Milliseconds(250),
          bounded_vulkan_prepare ? &scheduler_timed_out : nullptr,
          &cache.cc_frame_sink_failure_reason);
  cache.copy_output_gpu_prepare_pending =
      bounded_vulkan_prepare && scheduler_timed_out && !submitted;
  SyncStandaloneCcTimingForStandaloneRenderer(cache);
  cache.timing_cc_composite_ms +=
      StandaloneProbeElapsedMs(scheduler_start, StandaloneProbeClock::now());
  ImportCopyOutputPngFromCcHostForStandaloneRenderer(cache);
  SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  TraceLiveFrameProbeStage("after standalone cc scheduler frame");
  if (lifecycle_stop_result) {
    cache.result = *lifecycle_stop_result;
  }
  return submitted;
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
  const bool rebuild_for_attribute_mutation =
      cache.element_attributes_changed_since_probe &&
      (AttributeMutationRequiresDocumentRebuildForStandaloneRenderer(
           input_html, cache.requested_element_attributes_by_id_and_name) ||
       AttributeMutationRequiresDocumentRebuildForStandaloneRenderer(
           input_html, cache.applied_element_attributes_by_id_and_name));
  const bool html_content_already_loaded =
      cache.holder && cache.body_html == input_html &&
      !rebuild_for_attribute_mutation;
  const auto setup_start = StandaloneProbeClock::now();
  html_css_renderer::ResetStandaloneResourceProviderDiagnostics();
  StandaloneRendererResetImageReachabilityDiagnostics();
  StandaloneRendererResetFontResolutionDiagnostics();
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
  cache.image_paint_into_rect = ImagePaintIntoRectDiagnostics();
  cache.timing_total_ms = 0.0;
  cache.timing_input_setup_ms = 0.0;
  cache.timing_html_document_setup_ms = 0.0;
  cache.timing_style_update_ms = 0.0;
  cache.timing_layout_lifecycle_ms = 0.0;
  cache.timing_prepaint_and_paint_lifecycle_ms = 0.0;
  cache.timing_paint_artifact_generation_ms = 0.0;
  cache.timing_paint_artifact_audit_ms = 0.0;
  cache.timing_paint_artifact_extraction_ms = 0.0;
  cache.timing_cc_composite_ms = 0.0;
  cache.timing_cc_frame_sink_warmup_ms = 0.0;
  cache.timing_cc_root_preattach_ms = 0.0;
  cache.timing_cc_pending_update_ms = 0.0;
  cache.timing_cc_scheduler_run_loop_ms = 0.0;
  cache.timing_cc_submit_wait_ms = 0.0;
  cache.timing_cache_hit = false;
  cache.timing_reused_live_document = false;
  cache.timing_rebuilt_for_attributes = false;
  cache.timing_reused_live_document = html_content_already_loaded;
  cache.timing_rebuilt_for_attributes = rebuild_for_attribute_mutation;
  cache.hit_test_entries.clear();
  cache.scrollable_element_entries.clear();
  cache.sticky_update_scroll_area_count = 0;
  cache.sticky_update_consumed_descendant_count = 0;
  cache.sticky_update_constrained_after_count = 0;
  cache.sticky_update_consumed_horizontal_count = 0;
  cache.sticky_update_consumed_vertical_count = 0;
  cache.active_animation_count = 0;
  cache.needs_animation_timing_update = false;
  cache.needs_lifecycle_update = false;
  cache.needs_begin_frame = false;
  cache.needs_output = false;
  cache.compositor_root_layer_available = false;
  cache.compositor_layer_count = 0;
  SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  LiveFramePaintProbeResult result;
  TraceLiveFrameProbeStage("before DummyPageHolder");
  if (!cache.holder) {
    cache.chrome_client =
        MakeGarbageCollected<StandaloneCompositorChromeClient>(&cache);
    cache.holder =
        std::make_unique<DummyPageHolder>(
            gfx::Size(cache.viewport_width, cache.viewport_height),
            cache.chrome_client.Get())
            .release();
    cache.holder->GetFrameView().SetBaseBackgroundColor(
        cache.transparent_background ? Color::kTransparent : Color::kWhite);
    Document::SetForceSynchronousParsingForTesting(true);
    StandaloneRendererSetDeferImageAttributeLoads(true);
    cache.holder->GetFrame().Loader().CommitNavigation(
        WebNavigationParams::CreateWithHTMLStringForTesting(
            base::span<const char>(input_html.data(), input_html.size()),
            KURL("file:///standalone-renderer-document.html")),
        /*extra_data=*/nullptr);
    blink::test::RunPendingTasks();
    StandaloneRendererSetDeferImageAttributeLoads(false);
    Document::SetForceSynchronousParsingForTesting(false);
  }
  TraceLiveFrameProbeStage("after DummyPageHolder");
  Document* document_ptr = &cache.holder->GetDocument();
  document_ptr->GetStyleEngine().UpdateViewportSize();
  TraceLiveFrameProbeStage("after GetDocument");
  cache.timing_input_setup_ms =
      StandaloneProbeElapsedMs(setup_start, StandaloneProbeClock::now());

  if (!document_ptr->documentElement() || !document_ptr->body()) {
    TraceLiveFrameProbeStage("missing body");
    return result;
  }

  TraceLiveFrameProbeStage("before document setup");
  const auto html_setup_start = StandaloneProbeClock::now();
  g_standalone_blink_saw_font_draw_text = false;
  if (!html_content_already_loaded) {
    cache.original_element_attribute_values.clear();
    cache.applied_element_attributes_by_id_and_name.clear();
  }
  Document& document = *document_ptr;
  TraceLiveFrameProbeStage("before ApplyElementAttributes");
  ApplyElementAttributesForStandaloneRenderer(
      document, cache.requested_element_attributes_by_id_and_name,
      &cache.original_element_attribute_values,
      &cache.applied_element_attributes_by_id_and_name);
  TraceLiveFrameProbeStage("after ApplyElementAttributes");
  TraceLiveFrameProbeStage("before ApplyDomMutations");
  ApplyDomMutationsForStandaloneRenderer(document,
                                         cache.requested_dom_mutations);
  TraceLiveFrameProbeStage("after ApplyDomMutations");
  if (cache.dom_mutations_applied) {
    cache.needs_output = true;
    TraceLiveFrameProbeStage("before post-dom-mutation pending tasks");
    blink::test::RunPendingTasks();
    TraceLiveFrameProbeStage("after post-dom-mutation pending tasks");
  }
  cache.element_attributes_changed_since_probe = false;
  TraceLiveFrameProbeStage("after document setup");
  cache.timing_html_document_setup_ms =
      StandaloneProbeElapsedMs(html_setup_start, StandaloneProbeClock::now());
  const bool static_image_loads_needed =
      !html_content_already_loaded ||
      AttributeMutationMayAffectImageLoadsForStandaloneRenderer(
          cache.requested_element_attributes_by_id_and_name);
  if (static_image_loads_needed) {
    TraceLiveFrameProbeStage("before static image loads");
    StartStandaloneImageLoadsForStaticRender(document);
    RunStandaloneImageLoadingTasksForStaticRender();
    CompleteStandaloneImageLoadsForStaticRender(document);
    TraceLiveFrameProbeStage("after static image loads");
  } else {
    TraceLiveFrameProbeStage("static image loads skipped for live document");
  }
  TraceLiveFrameProbeStage("before image reachability");
  cache.image_reachability =
      CollectImageReachabilityForStandaloneRenderer(document, input_html);
  TraceLiveFrameProbeStage("after image reachability");
  TraceLiveFrameProbeStage("before render blocking unblock");
  document.RenderBlockingResourceUnblocked();
  TraceLiveFrameProbeStage("after render blocking unblock");
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
  if (cache.lifecycle_stop.empty()) {
    const bool scheduler_submitted =
        ScheduleStandaloneBlinkCompositorStateThroughCcSchedulerForStandaloneRenderer(
            cache, input_html, html_content_already_loaded, document,
            frame_view, result);
    if (!scheduler_submitted) {
      cache.body_html = input_html;
      cache.raw_paint_artifact_audit_json =
          std::string("{\"source\":\"real Blink PaintArtifact\",") +
          "\"status\":\"stopped_before_artifact_due_to_scheduler_failure\"}";
      cache.result = result;
      cache.initialized = true;
      return result;
    }
  } else {
    std::optional<LiveFramePaintProbeResult> lifecycle_stop_result =
        UpdateStandaloneBlinkLifecyclePacAndCcForStandaloneRenderer(
            cache, input_html, html_content_already_loaded, document,
            frame_view, result,
            StandaloneCcFrameAdvanceMode::kSchedulerCallback);
    if (lifecycle_stop_result) {
      return *lifecycle_stop_result;
    }
  }
  cache.hit_test_entries.clear();
  cache.scrollable_element_entries.clear();
  CollectLiveHitTestEntriesForStandaloneRenderer(&document,
                                                 cache.hit_test_entries);
  if (cache.collect_frame_diagnostics) {
    cache.image_reachability =
        CollectImageReachabilityForStandaloneRenderer(document, input_html);
    CollectLiveScrollableElementEntriesForStandaloneRenderer(
        &document, cache.scrollable_element_entries);
    cache.sticky_position_diagnostics_json =
        StickyPositionDiagnosticsJsonForStandaloneRenderer(&document);
  } else {
    cache.image_reachability = ImageReachabilityDiagnostics();
    cache.sticky_position_diagnostics_json.clear();
  }
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
  if (document.Lifecycle().GetState() < DocumentLifecycle::kPaintClean) {
    TraceLiveFrameProbeStage(
        "before final lifecycle update before GetPaintArtifact");
    result.lifecycle_reached_paint_clean =
        UpdateAllLifecyclePhasesForTestForStandaloneRenderer(frame_view) ? 1
                                                                         : 0;
    TraceLiveFrameProbeStage(
        "after final lifecycle update before GetPaintArtifact");
  }
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
  if (cache.collect_frame_diagnostics ||
      cache.collect_backdrop_filter_metadata) {
    CollectBackdropFilterRegionsForStandaloneRenderer(
        artifact, cache.backdrop_filter_regions);
  } else {
    cache.backdrop_filter_regions.clear();
  }
  if (cc::Layer* root_layer = frame_view.RootCcLayer()) {
    cache.compositor_root_layer_available = true;
    cache.compositor_layer_count =
        CountCcLayersForStandaloneRenderer(root_layer);
    cache.artifact_audit_lines.push_back(
        "paint_artifact_compositor root_layer=1 cc_layer_count=" +
        std::to_string(cache.compositor_layer_count));
  } else {
    cache.compositor_root_layer_available = false;
    cache.compositor_layer_count = 0;
    cache.artifact_audit_lines.push_back(
        "paint_artifact_compositor root_layer=0 cc_layer_count=0");
  }
  SyncStandaloneCcHostStateForStandaloneRenderer(cache);
  if (cache.cc_host_created || cache.cc_attach_attempted) {
    cache.artifact_audit_lines.push_back(
        "cc_layer_tree_host host=" +
        std::to_string(cache.cc_host_created ? 1 : 0) + " attached=" +
        std::to_string(cache.cc_root_layer_attached ? 1 : 0) +
        " commit_requested=" +
        std::to_string(cache.cc_commit_requested ? 1 : 0) +
        " frame_sink_requested=" +
        std::to_string(cache.cc_frame_sink_requested ? 1 : 0) +
        " frame_sink_bound=" +
        std::to_string(cache.cc_frame_sink_bound ? 1 : 0) +
        " gpu_context=" +
        std::to_string(cache.cc_gpu_context_created ? 1 : 0) +
        " raster_context=" +
        std::to_string(cache.cc_raster_context_created ? 1 : 0) +
        " shared_image=" +
        std::to_string(cache.cc_shared_image_interface_available ? 1 : 0) +
        " compositor_frame_submitted=" +
        std::to_string(cache.cc_compositor_frame_submitted ? 1 : 0) +
        " viz_display=" +
        std::to_string(cache.cc_viz_display_created ? 1 : 0) +
        " skia_gpu=" +
        std::to_string(cache.cc_skia_gpu_reached ? 1 : 0));
  }
  SortLiveHitTestEntriesByPaintOrderForStandaloneRenderer(
      artifact, cache.hit_test_entries);
  if (cache.collect_frame_diagnostics) {
    SortLiveScrollableElementEntriesByPaintOrderForStandaloneRenderer(
        artifact, cache.scrollable_element_entries);
  }
  cache.timing_paint_artifact_generation_ms =
      StandaloneProbeElapsedMs(paint_artifact_start,
                               StandaloneProbeClock::now());
  cache.body_html = input_html;
  cache.timing_total_ms =
      StandaloneProbeElapsedMs(total_start, StandaloneProbeClock::now());
  const auto audit_start = StandaloneProbeClock::now();
  if (cache.collect_frame_diagnostics) {
    if (cache.full_paint_artifact_audit) {
      BuildPaintArtifactAudit(artifact, cache);
    } else {
      BuildPaintArtifactRetainedMetadata(artifact, cache);
    }
  } else {
    cache.raw_paint_artifact_audit_json.clear();
    cache.artifact_audit_lines.clear();
  }
  cache.timing_paint_artifact_audit_ms =
      StandaloneProbeElapsedMs(audit_start, StandaloneProbeClock::now());
  if (LifecycleStopEqualsForStandaloneRenderer("artifact")) {
    cache.body_html = input_html;
    cache.result = result;
    cache.initialized = true;
    return result;
  }
  const auto extraction_start = StandaloneProbeClock::now();
  if (cache.collect_frame_diagnostics) {
    ExportDrawOpsForStandaloneRenderer(artifact, cache);
  } else {
    cache.exported_draw_ops.clear();
  }
  cache.timing_paint_artifact_extraction_ms =
      StandaloneProbeElapsedMs(extraction_start, StandaloneProbeClock::now());
  cache.timing_total_ms =
      StandaloneProbeElapsedMs(total_start, StandaloneProbeClock::now());
  if (!cache.full_paint_artifact_audit && cache.collect_frame_diagnostics) {
    cache.raw_paint_artifact_audit_json =
        BuildRetainedMetadataTimingJsonForStandaloneRenderer(cache);
  }
  cache.result = result;
  cache.initialized = true;
  return result;
}

std::string RunStandaloneCcSchedulerParityProbeForStandaloneRenderer(
    int width,
    int height) {
  const int safe_width = std::max(1, width);
  const int safe_height = std::max(1, height);
  StandaloneCcSchedulerParityProbe probe(gfx::Size(safe_width, safe_height));
  return probe.Run();
}

}  // namespace

extern "C" const char*
StandaloneBlinkLiveFrameBridgeRunCcSchedulerProbeForStandaloneRenderer(
    int width,
    int height) {
  static std::string probe_json;
  probe_json =
      RunStandaloneCcSchedulerParityProbeForStandaloneRenderer(width, height);
  return probe_json.c_str();
}

uint64_t StandaloneBlinkLiveFrameBridgeCreateInstanceForStandaloneRenderer() {
  const uint64_t instance_id = NextProbeInstanceId()++;
  ProbeCachesByInstance().emplace(
      instance_id, std::make_unique<LiveFramePaintProbeCache>());
  return instance_id;
}

void StandaloneBlinkLiveFrameBridgeSetCurrentInstanceForStandaloneRenderer(
    uint64_t instance_id) {
  CurrentProbeInstanceId() = instance_id;
}

void StandaloneBlinkLiveFrameBridgeDestroyInstanceForStandaloneRenderer(
    uint64_t instance_id) {
  DestroyProbeCacheInstance(instance_id);
}

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
  if (cache.holder) {
    const gfx::Size viewport_size(clamped_width, clamped_height);
    LocalFrameView& frame_view = cache.holder->GetFrameView();
    frame_view.Resize(viewport_size);
    frame_view.SetNeedsUpdateGeometries();
    cache.holder->GetPage().GetVisualViewport().SetSize(viewport_size);
    cache.holder->GetDocument().GetStyleEngine().UpdateViewportSize();
  }
  cache.initialized = false;
  cache.cc_attach_failure_reason.clear();
  cache.cc_frame_sink_failure_reason.clear();
  cache.element_attributes_changed_since_probe = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetDeviceScaleFactorForStandaloneRenderer(
    float device_scale_factor) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const float clamped_device_scale_factor =
      device_scale_factor > 0.0f ? device_scale_factor : 1.0f;
  if (cache.device_scale_factor == clamped_device_scale_factor) {
    return;
  }
  cache.device_scale_factor = clamped_device_scale_factor;
  if (cache.holder) {
    cache.holder->GetDocument().GetStyleEngine().UpdateViewportSize();
  }
  cache.initialized = false;
  cache.cc_attach_failure_reason.clear();
  cache.cc_frame_sink_failure_reason.clear();
  cache.element_attributes_changed_since_probe = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetTransparentBackgroundForStandaloneRenderer(
    int enabled) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool transparent = enabled != 0;
  if (cache.transparent_background == transparent) {
    return;
  }
  cache.transparent_background = transparent;
  if (cache.holder) {
    cache.holder->GetFrameView().SetBaseBackgroundColor(
        transparent ? Color::kTransparent : Color::kWhite);
  }
  if (cache.cc_layer_host) {
    cache.cc_layer_host->SetTransparentBackground(transparent);
  }
  cache.initialized = false;
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeInvalidateCacheForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  ResetStandaloneLiveDocumentForFullHtmlReplacement(cache);
}

void StandaloneBlinkLiveFrameBridgeSetNativeWindowForStandaloneRenderer(
    void* native_window_handle,
    int width,
    int height) {
  gfx::Size requested_size(std::max(1, width), std::max(1, height));
  if (g_standalone_native_window_handle == native_window_handle &&
      g_standalone_native_window_size == requested_size) {
    return;
  }
  g_standalone_native_window_handle = native_window_handle;
  g_standalone_native_window_size = requested_size;
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.initialized = false;
  cache.cc_frame_sink_failure_reason.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeRequestPngSnapshotForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.copy_output_png_requested = true;
  cache.copy_output_gpu_requested = false;
  cache.copy_output_gpu_use_vulkan_offscreen = false;
  cache.copy_output_gpu_use_d3d12_offscreen = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_png.clear();
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgeRequestRawFrameForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.copy_output_raw_requested = true;
  cache.copy_output_gpu_requested = false;
  cache.copy_output_gpu_use_vulkan_offscreen = false;
  cache.copy_output_gpu_use_d3d12_offscreen = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgeRequestGpuFrameForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.copy_output_gpu_requested = true;
  cache.copy_output_gpu_use_vulkan_offscreen = false;
  cache.copy_output_gpu_use_d3d12_offscreen = false;
  cache.copy_output_png_requested = false;
  cache.copy_output_raw_requested = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_png.clear();
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgeRequestVulkanGpuFrameForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool backend_changed =
      cache.copy_output_gpu_use_d3d12_offscreen ||
      !cache.copy_output_gpu_use_vulkan_offscreen;
  cache.copy_output_gpu_requested = true;
  cache.copy_output_gpu_prepare_requested = false;
  cache.copy_output_gpu_use_vulkan_offscreen = true;
  cache.copy_output_gpu_use_d3d12_offscreen = false;
  cache.copy_output_png_requested = false;
  cache.copy_output_raw_requested = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_png.clear();
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.copy_output_gpu_prepare_pending = false;
  if (backend_changed) {
    cache.cc_layer_host.reset();
  }
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgePrepareVulkanGpuFrameForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool backend_changed =
      cache.copy_output_gpu_use_d3d12_offscreen ||
      !cache.copy_output_gpu_use_vulkan_offscreen;
  cache.copy_output_gpu_requested = false;
  cache.copy_output_gpu_prepare_requested = true;
  cache.copy_output_gpu_use_vulkan_offscreen = true;
  cache.copy_output_gpu_use_d3d12_offscreen = false;
  cache.copy_output_png_requested = false;
  cache.copy_output_raw_requested = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_png.clear();
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.copy_output_gpu_prepare_pending = false;
  if (backend_changed) {
    cache.cc_layer_host.reset();
  }
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgeRequestD3D12GpuFrameForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool backend_changed =
      cache.copy_output_gpu_use_vulkan_offscreen ||
      !cache.copy_output_gpu_use_d3d12_offscreen;
  cache.copy_output_gpu_requested = true;
  cache.copy_output_gpu_prepare_requested = false;
  cache.copy_output_gpu_use_vulkan_offscreen = false;
  cache.copy_output_gpu_use_d3d12_offscreen = true;
  cache.copy_output_png_requested = false;
  cache.copy_output_raw_requested = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_png.clear();
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.copy_output_gpu_prepare_pending = false;
  if (backend_changed) {
    cache.cc_layer_host.reset();
  }
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgePrepareD3D12GpuFrameForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool backend_changed =
      cache.copy_output_gpu_use_vulkan_offscreen ||
      !cache.copy_output_gpu_use_d3d12_offscreen;
  cache.copy_output_gpu_requested = false;
  cache.copy_output_gpu_prepare_requested = true;
  cache.copy_output_gpu_use_vulkan_offscreen = false;
  cache.copy_output_gpu_use_d3d12_offscreen = true;
  cache.copy_output_png_requested = false;
  cache.copy_output_raw_requested = false;
  cache.copy_output_png_completed = false;
  cache.copy_output_png_succeeded = false;
  cache.copy_output_png.clear();
  cache.copy_output_raw_frame = LiveRawFrameOutput();
  cache.copy_output_gpu_frame = LiveGpuFrameOutput();
  cache.copy_output_failure.clear();
  cache.copy_output_gpu_prepare_pending = false;
  if (backend_changed) {
    cache.cc_layer_host.reset();
  }
  cache.initialized = false;
}

const char*
StandaloneBlinkLiveFrameBridgeRunBorrowedVkImageBackingSmokeForStandaloneRenderer() {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.copy_output_gpu_frame.shared_image_available ||
      !cache.copy_output_gpu_frame.vk_context_provider_available ||
      !cache.copy_output_gpu_frame.shared_context_state_is_vulkan) {
    smoke_result =
        "gpu_borrowed_vkimage_backing_smoke: failed failure=Vulkan SharedImage "
        "CopyOutput did not initialize before borrowed target smoke";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_borrowed_vkimage_backing_smoke: failed failure=cc layer host is "
        "not available";
    return smoke_result.c_str();
  }
  smoke_result = cache.cc_layer_host->RunBorrowedVkImageBackingSmokeForTesting();
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRunBorrowedVkImageRenderCopySmokeForStandaloneRenderer() {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.copy_output_gpu_frame.shared_image_available ||
      !cache.copy_output_gpu_frame.vk_context_provider_available ||
      !cache.copy_output_gpu_frame.shared_context_state_is_vulkan) {
    smoke_result =
        "gpu_borrowed_vkimage_render_copy_smoke: failed failure=Vulkan "
        "SharedImage CopyOutput did not initialize before render-copy smoke";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_borrowed_vkimage_render_copy_smoke: failed failure=cc layer host "
        "is not available";
    return smoke_result.c_str();
  }
  smoke_result =
      cache.cc_layer_host->RunBorrowedVkImageRenderCopySmokeForTesting();
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRunExternalVkImageRenderCopyForStandaloneRenderer(
    const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!vulkan_image) {
    smoke_result =
        "gpu_borrowed_vkimage_render_copy_smoke: failed failure=external "
        "Vulkan image is null";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_borrowed_vkimage_render_copy_smoke: failed failure=cc layer host "
        "is not available";
    return smoke_result.c_str();
  }
  smoke_result =
      cache.cc_layer_host->RunExternalVkImageRenderCopyForTesting(vulkan_image);
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRenderExternalVkImageToTargetForStandaloneRenderer(
    const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
  static std::string result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!vulkan_image) {
    result =
        "gpu_external_vkimage_render_copy: failed failure=external Vulkan "
        "image is null";
    return result.c_str();
  }
  if (!cache.cc_layer_host) {
    result =
        "gpu_external_vkimage_render_copy: failed failure=cc layer host is not "
        "available";
    return result.c_str();
  }
  result = cache.cc_layer_host->RenderExternalVkImageToTarget(vulkan_image);
  cache.copy_output_gpu_prepare_requested = false;
  return result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRenderBackdropMaskToExternalVkImageForStandaloneRenderer(
    const html_css_renderer::ExternalVulkanImageTarget* vulkan_image) {
  static std::string result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!vulkan_image) {
    result =
        "gpu_external_vkimage_backdrop_mask: failed failure=external Vulkan "
        "mask image is null";
    return result.c_str();
  }
  if (cache.backdrop_filter_regions.empty()) {
    result =
        "gpu_external_vkimage_backdrop_mask: failed failure=no backdrop "
        "filter regions collected";
    return result.c_str();
  }
  if (!cache.cc_layer_host) {
    result =
        "gpu_external_vkimage_backdrop_mask: failed failure=cc layer host is "
        "not available";
    return result.c_str();
  }
  result = cache.cc_layer_host->RenderBackdropMaskToExternalVkImage(
      vulkan_image, cache.backdrop_filter_regions);
  return result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRunBorrowedD3D12RenderCopySmokeForStandaloneRenderer() {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.copy_output_gpu_frame.shared_image_available) {
    smoke_result =
        "gpu_borrowed_d3d12_render_copy_smoke: failed failure=D3D12 "
        "SharedImage CopyOutput did not initialize before render-copy smoke";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_borrowed_d3d12_render_copy_smoke: failed failure=cc layer host "
        "is not available";
    return smoke_result.c_str();
  }
  smoke_result =
      cache.cc_layer_host->RunBorrowedD3D12RenderCopySmokeForTesting();
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRunExternalD3D12RenderCopyForStandaloneRenderer(
    void* d3d12_resource,
    void* shared_handle) {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!d3d12_resource && !shared_handle) {
    smoke_result =
        "gpu_borrowed_d3d12_render_copy_smoke: failed failure=external "
        "D3D12 resource/shared handle is null";
    return smoke_result.c_str();
  }
  if (!cache.copy_output_gpu_frame.shared_image_available) {
    smoke_result =
        "gpu_borrowed_d3d12_render_copy_smoke: failed failure=D3D12 "
        "SharedImage CopyOutput did not initialize before external render-copy";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_borrowed_d3d12_render_copy_smoke: failed failure=cc layer host "
        "is not available";
    return smoke_result.c_str();
  }
  smoke_result =
      cache.cc_layer_host->RunExternalD3D12RenderCopyForTesting(d3d12_resource,
                                                                shared_handle);
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRenderExternalD3D12ToTargetForStandaloneRenderer(
    void* d3d12_resource,
    void* shared_handle,
    int width,
    int height) {
  static std::string result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!d3d12_resource && !shared_handle) {
    result =
        "gpu_external_d3d12_render_copy: failed failure=external D3D12 "
        "resource/shared handle is null";
    return result.c_str();
  }
  if (!cache.cc_layer_host) {
    result =
        "gpu_external_d3d12_render_copy: failed failure=cc layer host is not "
        "available";
    return result.c_str();
  }
  result =
      cache.cc_layer_host->RenderExternalD3D12ToTarget(d3d12_resource,
                                                       shared_handle, width,
                                                       height);
  cache.copy_output_gpu_prepare_requested = false;
  return result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRenderBackdropMaskToExternalD3D12TargetForStandaloneRenderer(
    void* d3d12_resource,
    void* shared_handle,
    int width,
    int height) {
  static std::string result;
  LiveFramePaintProbeCache& cache = ProbeCache();
#if BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  if (!d3d12_resource && !shared_handle) {
    result =
        "gpu_external_d3d12_backdrop_mask: failed failure=external D3D12 mask "
        "resource/shared handle is null";
    return result.c_str();
  }
  if (cache.backdrop_filter_regions.empty()) {
    result =
        "gpu_external_d3d12_backdrop_mask: failed failure=no backdrop filter "
        "regions collected";
    return result.c_str();
  }
  if (!cache.cc_layer_host) {
    result =
        "gpu_external_d3d12_backdrop_mask: failed failure=cc layer host is not "
        "available";
    return result.c_str();
  }
  result = cache.cc_layer_host->RenderBackdropMaskToExternalD3D12Target(
      d3d12_resource, shared_handle, width, height,
      cache.backdrop_filter_regions);
  return result.c_str();
#else
  result =
      "gpu_external_d3d12_backdrop_mask: blocked failure=D3D12/Dawn external "
      "targets are not enabled in this build";
  return result.c_str();
#endif
}

void StandaloneBlinkLiveFrameBridgeReleaseExternalGpuTargetStateForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.cc_layer_host) {
    cache.cc_layer_host->ReleaseExternalGpuTargetState();
  }
  cache.copy_output_gpu_prepare_pending = false;
}

const char*
StandaloneBlinkLiveFrameBridgeRunGpuOutputVulkanPixelSmokeForStandaloneRenderer() {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.copy_output_gpu_frame.shared_image_available ||
      !cache.copy_output_gpu_frame.vk_context_provider_available ||
      !cache.copy_output_gpu_frame.shared_context_state_is_vulkan) {
    smoke_result =
        "gpu_output_vulkan_pixel_smoke: failed failure=Vulkan SharedImage "
        "CopyOutput did not initialize before pixel smoke";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_output_vulkan_pixel_smoke: failed failure=cc layer host is not "
        "available";
    return smoke_result.c_str();
  }
  smoke_result =
      cache.cc_layer_host->RunGpuOutputVulkanPixelSmokeForTesting();
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRunVulkanBackdropMaskPrototypeForStandaloneRenderer() {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.copy_output_gpu_frame.vk_context_provider_available ||
      !cache.copy_output_gpu_frame.shared_context_state_is_vulkan) {
    smoke_result =
        "gpu_vulkan_backdrop_mask_prototype_smoke: failed failure=Vulkan "
        "SharedContextState is not available";
    return smoke_result.c_str();
  }
  if (cache.backdrop_filter_regions.empty()) {
    smoke_result =
        "gpu_vulkan_backdrop_mask_prototype_smoke: failed failure=no "
        "backdrop filter regions collected";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_vulkan_backdrop_mask_prototype_smoke: failed failure=cc layer "
        "host is not available";
    return smoke_result.c_str();
  }
  smoke_result = cache.cc_layer_host->RunVulkanBackdropMaskPrototypeForTesting(
      cache.backdrop_filter_regions);
  return smoke_result.c_str();
}

const char*
StandaloneBlinkLiveFrameBridgeRunD3D12BackdropMaskPrototypeForStandaloneRenderer() {
  static std::string smoke_result;
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.backdrop_filter_regions.empty()) {
    smoke_result =
        "gpu_d3d12_backdrop_mask_prototype_smoke: failed failure=no "
        "backdrop filter regions collected";
    return smoke_result.c_str();
  }
  if (!cache.cc_layer_host) {
    smoke_result =
        "gpu_d3d12_backdrop_mask_prototype_smoke: failed failure=cc layer "
        "host is not available";
    return smoke_result.c_str();
  }
  smoke_result = cache.cc_layer_host->RunD3D12BackdropMaskPrototypeForTesting(
      cache.backdrop_filter_regions);
  return smoke_result.c_str();
}

void StandaloneBlinkLiveFrameBridgeSetDocumentScrollOffsetForStandaloneRenderer(
    float x,
    float y) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool requested = true;
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
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetWheelScrollForStandaloneRenderer(
    float x,
    float y,
    float delta_x,
    float delta_y,
    int requested) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool next_requested = requested != 0;
  if (!next_requested && !cache.requested_wheel_scroll &&
      std::abs(cache.requested_wheel_x - x) <= 0.001f &&
      std::abs(cache.requested_wheel_y - y) <= 0.001f &&
      std::abs(cache.requested_wheel_delta_x - delta_x) <= 0.001f &&
      std::abs(cache.requested_wheel_delta_y - delta_y) <= 0.001f) {
    return;
  }
  cache.requested_wheel_scroll = next_requested;
  cache.requested_wheel_x = x;
  cache.requested_wheel_y = y;
  cache.requested_wheel_delta_x = delta_x;
  cache.requested_wheel_delta_y = delta_y;
  cache.wheel_scroll_base_captured = false;
  cache.wheel_scroll_base_x = 0.0f;
  cache.wheel_scroll_base_y = 0.0f;
  cache.wheel_scroll_applied = false;
  cache.wheel_scroll_changed = false;
  cache.wheel_scroll_target_is_element = false;
  cache.wheel_scroll_target_element_id.clear();
  cache.wheel_scroll_applied_x = 0.0f;
  cache.wheel_scroll_applied_y = 0.0f;
  cache.wheel_scroll_max_x = 0.0f;
  cache.wheel_scroll_max_y = 0.0f;
  cache.wheel_scroll_status = next_requested ? "requested" : "not_requested";
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
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
  cache.element_attributes_changed_since_probe = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

int StandaloneBlinkLiveFrameBridgeDocumentScrollOffsetForStandaloneRenderer(
    const char* body_html,
    float* x,
    float* y,
    float* max_x,
    float* max_y) {
  RunLiveFramePaintProbe(body_html);
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.scroll_offset_applied) {
    return 0;
  }
  if (x) {
    *x = cache.applied_scroll_x;
  }
  if (y) {
    *y = cache.applied_scroll_y;
  }
  if (max_x) {
    *max_x = cache.max_scroll_x;
  }
  if (max_y) {
    *max_y = cache.max_scroll_y;
  }
  return 1;
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
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
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
  cache.element_attributes_changed_since_probe = true;
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeClearDomMutationsForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.requested_dom_mutations.empty()) {
    return;
  }
  cache.requested_dom_mutations.clear();
  cache.initialized = false;
}

void StandaloneBlinkLiveFrameBridgeAppendDomMutationForStandaloneRenderer(
    int type,
    const char* element_id,
    const char* name,
    const char* value) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  StandaloneDomMutationForRenderer mutation;
  mutation.type = type;
  mutation.element_id = element_id ? element_id : "";
  mutation.name = name ? name : "";
  mutation.value = value ? value : "";
  cache.requested_dom_mutations.push_back(std::move(mutation));
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

int StandaloneBlinkLiveFrameBridgeHasLiveElementForStandaloneRenderer(
    const char* element_id) {
  if (!element_id || !*element_id) {
    return 0;
  }
  DummyPageHolder* holder = ProbeCache().holder;
  if (!holder || !holder->GetDocument().documentElement()) {
    return 0;
  }
  return holder->GetDocument()
             .getElementById(AtomicString(String::FromUtf8(element_id)))
             ? 1
             : 0;
}

int StandaloneBlinkLiveFrameBridgeHasLiveBodyForStandaloneRenderer() {
  DummyPageHolder* holder = ProbeCache().holder;
  if (!holder) {
    return 0;
  }
  return holder->GetDocument().body() ? 1 : 0;
}

void StandaloneBlinkLiveFrameBridgeSetInteractionStateForStandaloneRenderer(
    const char* hovered_element_id,
    const char* active_element_id) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool next_requested = hovered_element_id || active_element_id;
  const std::string hovered = hovered_element_id ? hovered_element_id : "";
  const std::string active = active_element_id ? active_element_id : "";
  if (cache.requested_interaction_state == next_requested &&
      cache.requested_hovered_element_id == hovered &&
      cache.requested_active_element_id == active) {
    return;
  }
  cache.requested_interaction_state = next_requested;
  cache.requested_hovered_element_id = hovered;
  cache.requested_active_element_id = active;
  cache.initialized = false;
  cache.element_attributes_changed_since_probe = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeClearMouseInputEventsForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.requested_mouse_input_events.empty() &&
      !cache.mouse_input_events_consumed) {
    return;
  }
  cache.requested_mouse_input_events.clear();
  cache.mouse_input_events_consumed = false;
  cache.mouse_input_events_dispatched = false;
  cache.mouse_input_event_dispatch_count = 0;
  cache.mouse_input_status = "not_requested";
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeAppendMouseInputEventForStandaloneRenderer(
    int type,
    float x,
    float y,
    int button,
    int modifiers,
    int click_count) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.requested_mouse_input_events.push_back(
      StandaloneMouseInputEventForRenderer{type, x, y, button, modifiers,
                                           click_count});
  cache.mouse_input_events_consumed = false;
  cache.mouse_input_status = "requested";
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeClearKeyboardInputEventsForStandaloneRenderer() {
  LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.requested_keyboard_input_events.empty() &&
      !cache.keyboard_input_events_consumed) {
    return;
  }
  cache.requested_keyboard_input_events.clear();
  cache.keyboard_input_events_consumed = false;
  cache.keyboard_input_events_dispatched = false;
  cache.keyboard_input_event_dispatch_count = 0;
  cache.keyboard_input_status = "not_requested";
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeAppendKeyboardInputEventForStandaloneRenderer(
    int type,
    int key,
    const char* text,
    int modifiers) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  cache.requested_keyboard_input_events.push_back(
      StandaloneKeyboardInputEventForRenderer{
          type, key, text ? std::string(text) : std::string(), modifiers});
  cache.keyboard_input_events_consumed = false;
  cache.keyboard_input_status = "requested";
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetFullPaintArtifactAuditForStandaloneRenderer(
    int enabled) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool value = enabled != 0;
  if (cache.full_paint_artifact_audit == value) {
    return;
  }
  cache.full_paint_artifact_audit = value;
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetFrameDiagnosticsForStandaloneRenderer(
    int enabled) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool value = enabled != 0;
  if (cache.collect_frame_diagnostics == value) {
    return;
  }
  cache.collect_frame_diagnostics = value;
  cache.initialized = false;
  cache.exported_draw_ops.clear();
  cache.chunk_property_states.clear();
  cache.chunk_stable_keys.clear();
  cache.chunk_id_strings.clear();
  cache.finer_cache_units_by_chunk.clear();
  cache.artifact_audit_lines.clear();
  cache.raw_paint_artifact_audit_json.clear();
}

void StandaloneBlinkLiveFrameBridgeSetBackdropFilterMetadataForStandaloneRenderer(
    int enabled) {
  LiveFramePaintProbeCache& cache = ProbeCache();
  const bool value = enabled != 0;
  if (cache.collect_backdrop_filter_metadata == value) {
    return;
  }
  cache.collect_backdrop_filter_metadata = value;
  cache.initialized = false;
  cache.backdrop_filter_regions.clear();
}

void StandaloneBlinkLiveFrameBridgeSetTraceStagesForStandaloneRenderer(
    int enabled) {
  ProbeCache().trace_stages = enabled != 0;
}

int StandaloneBlinkLiveFrameBridgeTraceStagesEnabledForStandaloneRenderer() {
  return ProbeCache().trace_stages ? 1 : 0;
}

extern "C" int
StandaloneBlinkLiveFrameBridgeTraceStagesEnabledForCcForStandaloneRenderer() {
  return StandaloneBlinkLiveFrameBridgeTraceStagesEnabledForStandaloneRenderer();
}

extern "C" void StandaloneBlinkLiveFrameBridgeTraceStageForCcForStandaloneRenderer(
    const char* stage) {
  TraceLiveFrameProbeStage(stage);
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

int StandaloneBlinkLiveFrameBridgePrewarmCcFrameSinkForStandaloneRenderer(
    int width,
    int height) {
  EnsureWtfInitializedForStandaloneRenderer();
  LiveFramePaintProbeCache& cache = ProbeCache();
  const int safe_width = std::max(1, width);
  const int safe_height = std::max(1, height);
  return PrewarmStandaloneCcFrameSinkForStandaloneRenderer(
             cache, gfx::Size(safe_width, safe_height))
             ? 1
             : 0;
}

int StandaloneBlinkLiveFrameBridgePaintChunkCountForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).paint_chunk_count;
}

int StandaloneBlinkLiveFrameBridgeDisplayItemCountForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).display_item_count;
}

double StandaloneBlinkLiveFrameBridgeTimingTotalMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_total_ms;
}

double StandaloneBlinkLiveFrameBridgeTimingInputSetupMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_input_setup_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingHtmlDocumentSetupMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_html_document_setup_ms;
}

double StandaloneBlinkLiveFrameBridgeTimingStyleUpdateMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_style_update_ms;
}

double StandaloneBlinkLiveFrameBridgeTimingLayoutLifecycleMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_layout_lifecycle_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingPrepaintAndPaintLifecycleMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_prepaint_and_paint_lifecycle_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingPaintArtifactGenerationMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_paint_artifact_generation_ms;
}

double StandaloneBlinkLiveFrameBridgeTimingPaintArtifactAuditMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_paint_artifact_audit_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingPaintArtifactExtractionMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_paint_artifact_extraction_ms;
}

double StandaloneBlinkLiveFrameBridgeTimingCcCompositeMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_composite_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingCcFrameSinkWarmupMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_frame_sink_warmup_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingCcRootPreattachMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_root_preattach_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingCcPendingUpdateMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_pending_update_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingCcSchedulerRunLoopMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_scheduler_run_loop_ms;
}

double StandaloneBlinkLiveFrameBridgeTimingCcSubmitWaitMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_submit_wait_ms;
}

double
StandaloneBlinkLiveFrameBridgeTimingCcStartupPrewarmMsForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cc_startup_prewarm_ms;
}

int StandaloneBlinkLiveFrameBridgeTimingCacheHitForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_cache_hit ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeTimingReusedLiveDocumentForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_reused_live_document ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeTimingRebuiltForAttributesForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().timing_rebuilt_for_attributes ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCompositorRootLayerForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().compositor_root_layer_available ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcHostForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_host_created ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcRootLayerAttachedForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_root_layer_attached ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcCommitRequestedForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_commit_requested ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcFrameSinkRequestedForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_frame_sink_requested ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcFrameSinkBoundForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_frame_sink_bound ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcCompositorFrameSubmittedForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_compositor_frame_submitted ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcGpuContextForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_gpu_context_created ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcRasterContextForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_raster_context_created ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcSharedImageInterfaceForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_shared_image_interface_available ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcVizDisplayForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_viz_display_created ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcSkiaGpuForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().cc_skia_gpu_reached ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcSubmittedOutputSizeForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height) {
  RunLiveFramePaintProbe(body_html);
  const gfx::Size size = ProbeCache().cc_submitted_output_size;
  if (width) {
    *width = size.width();
  }
  if (height) {
    *height = size.height();
  }
  return size.IsEmpty() ? 0 : 1;
}

int StandaloneBlinkLiveFrameBridgeCcVizDisplayOutputSizeForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height) {
  RunLiveFramePaintProbe(body_html);
  const gfx::Size size = ProbeCache().cc_viz_display_output_size;
  if (width) {
    *width = size.width();
  }
  if (height) {
    *height = size.height();
  }
  return size.IsEmpty() ? 0 : 1;
}

int StandaloneBlinkLiveFrameBridgeCcFrameSinkFailureForStandaloneRenderer(
    const char* body_html,
    char* out,
    int capacity) {
  RunLiveFramePaintProbe(body_html);
  if (!out || capacity <= 0) {
    return 0;
  }
  const std::string& failure = ProbeCache().cc_frame_sink_failure_reason;
  const int copied =
      std::min<int>(capacity - 1, static_cast<int>(failure.size()));
  if (copied > 0) {
    std::memcpy(out, failure.data(), copied);
  }
  out[copied] = '\0';
  return copied;
}

int StandaloneBlinkLiveFrameBridgeGpuPreparePendingForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().copy_output_gpu_prepare_pending ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeCcAttachFailureForStandaloneRenderer(
    const char* body_html,
    char* out,
    int capacity) {
  RunLiveFramePaintProbe(body_html);
  if (!out || capacity <= 0) {
    return 0;
  }
  const std::string& failure = ProbeCache().cc_attach_failure_reason;
  const int copied =
      std::min<int>(capacity - 1, static_cast<int>(failure.size()));
  if (copied > 0) {
    std::memcpy(out, failure.data(), copied);
  }
  out[copied] = '\0';
  return copied;
}

int StandaloneBlinkLiveFrameBridgeCompositorLayerCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().compositor_layer_count;
}

int StandaloneBlinkLiveFrameBridgeReachesPaintCleanForStandaloneRenderer(
    const char* body_html) {
  return RunLiveFramePaintProbe(body_html).lifecycle_reached_paint_clean;
}

int StandaloneBlinkLiveFrameBridgeNeedsBeginFrameForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().needs_begin_frame ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgeNeedsOutputForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return ProbeCache().needs_output ? 1 : 0;
}

int StandaloneBlinkLiveFrameBridgePointerObservedStateForStandaloneRenderer(
    const char* body_html,
    char* hovered_element_id,
    int hovered_element_id_capacity,
    char* active_element_id,
    int active_element_id_capacity) {
  RunLiveFramePaintProbe(body_html);
  const LiveFramePaintProbeCache& cache = ProbeCache();
  if (!cache.pointer_state_applied) {
    return 0;
  }
  if (hovered_element_id && hovered_element_id_capacity > 0) {
    const size_t copied =
        std::min(cache.pointer_hover_element_id.size(),
                 static_cast<size_t>(hovered_element_id_capacity - 1));
    std::memcpy(hovered_element_id, cache.pointer_hover_element_id.data(),
                copied);
    hovered_element_id[copied] = '\0';
  }
  if (active_element_id && active_element_id_capacity > 0) {
    const std::string& active_id = cache.pointer_hit_element_id;
    const size_t copied =
        std::min(active_id.size(),
                 static_cast<size_t>(active_element_id_capacity - 1));
    std::memcpy(active_element_id, active_id.data(), copied);
    active_element_id[copied] = '\0';
  }
  return 1;
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
    char* tag_name,
    int tag_name_capacity,
    char* data_godot_action,
    int data_godot_action_capacity,
    float* x,
    float* y,
    float* width,
    float* height,
    int* disabled,
    int* editable,
    int* checked,
    int* focused) {
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
  if (tag_name && tag_name_capacity > 0) {
    const size_t copied =
        std::min(entry.tag_name.size(),
                 static_cast<size_t>(tag_name_capacity - 1));
    std::memcpy(tag_name, entry.tag_name.data(), copied);
    tag_name[copied] = '\0';
  }
  if (data_godot_action && data_godot_action_capacity > 0) {
    const size_t copied =
        std::min(entry.data_godot_action.size(),
                 static_cast<size_t>(data_godot_action_capacity - 1));
    std::memcpy(data_godot_action, entry.data_godot_action.data(), copied);
    data_godot_action[copied] = '\0';
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
  if (disabled) {
    *disabled = entry.disabled ? 1 : 0;
  }
  if (editable) {
    *editable = entry.editable ? 1 : 0;
  }
  if (checked) {
    *checked = entry.checked ? 1 : 0;
  }
  if (focused) {
    *focused = entry.focused ? 1 : 0;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeFormControlEntryCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().form_control_entries.size());
}

std::string SerializeStandaloneSelectedValues(
    const std::vector<std::string>& values) {
  std::string serialized;
  for (const std::string& value : values) {
    serialized += std::to_string(value.size());
    serialized += ':';
    serialized += value;
  }
  return serialized;
}

int StandaloneBlinkLiveFrameBridgeFormControlEntryAtForStandaloneRenderer(
    const char* body_html,
    int index,
    char* element_id,
    int element_id_capacity,
    char* tag_name,
    int tag_name_capacity,
    char* value,
    int value_capacity,
    int* checked,
    int* focused,
    int* selection_offsets_present,
    unsigned* selection_start,
    unsigned* selection_end,
    char* type,
    int type_capacity,
    char* min,
    int min_capacity,
    char* max,
    int max_capacity,
    char* step,
    int step_capacity,
    char* selected_values,
    int selected_values_capacity) {
  RunLiveFramePaintProbe(body_html);
  const auto& entries = ProbeCache().form_control_entries;
  if (index < 0 || index >= static_cast<int>(entries.size())) {
    return 0;
  }
  const LiveFormControlEntry& entry = entries[static_cast<size_t>(index)];
  auto copy_string = [](const std::string& source, char* destination,
                        int destination_capacity) {
    if (!destination || destination_capacity <= 0) {
      return;
    }
    const size_t copied =
        std::min(source.size(), static_cast<size_t>(destination_capacity - 1));
    std::memcpy(destination, source.data(), copied);
    destination[copied] = '\0';
  };
  copy_string(entry.element_id, element_id, element_id_capacity);
  copy_string(entry.tag_name, tag_name, tag_name_capacity);
  copy_string(entry.value, value, value_capacity);
  copy_string(entry.type, type, type_capacity);
  copy_string(entry.min, min, min_capacity);
  copy_string(entry.max, max, max_capacity);
  copy_string(entry.step, step, step_capacity);
  copy_string(SerializeStandaloneSelectedValues(entry.selected_values),
              selected_values, selected_values_capacity);
  if (checked) {
    *checked = entry.checked ? 1 : 0;
  }
  if (focused) {
    *focused = entry.focused ? 1 : 0;
  }
  if (selection_offsets_present) {
    *selection_offsets_present = entry.selection_offsets_present ? 1 : 0;
  }
  if (selection_start) {
    *selection_start = entry.selection_start;
  }
  if (selection_end) {
    *selection_end = entry.selection_end;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeBackdropFilterRegionCountForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().backdrop_filter_regions.size());
}

int StandaloneBlinkLiveFrameBridgeBackdropFilterRegionAtForStandaloneRenderer(
    const char* body_html,
    int index,
    float* x,
    float* y,
    float* width,
    float* height,
    float* blur_radius_css_px,
    float* border_radius_top_left,
    float* border_radius_top_right,
    float* border_radius_bottom_right,
    float* border_radius_bottom_left,
    float* opacity,
    uint32_t* flags,
    uint32_t* filter_op_count,
    uint32_t* filter_op_types,
    float* filter_op_amounts,
    int filter_op_capacity,
    char* element_id,
    int element_id_capacity) {
  RunLiveFramePaintProbe(body_html);
  const auto& entries = ProbeCache().backdrop_filter_regions;
  if (index < 0 || index >= static_cast<int>(entries.size())) {
    return 0;
  }
  const LiveBackdropFilterRegion& entry = entries[static_cast<size_t>(index)];
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
  if (blur_radius_css_px) {
    *blur_radius_css_px = entry.blur_radius_css_px;
  }
  if (border_radius_top_left) {
    *border_radius_top_left = entry.border_radius_top_left;
  }
  if (border_radius_top_right) {
    *border_radius_top_right = entry.border_radius_top_right;
  }
  if (border_radius_bottom_right) {
    *border_radius_bottom_right = entry.border_radius_bottom_right;
  }
  if (border_radius_bottom_left) {
    *border_radius_bottom_left = entry.border_radius_bottom_left;
  }
  if (opacity) {
    *opacity = entry.opacity;
  }
  if (flags) {
    *flags = entry.flags;
  }
  const uint32_t copied_filter_op_count =
      filter_op_capacity > 0
          ? std::min<uint32_t>(
                static_cast<uint32_t>(entry.filter_operations.size()),
                static_cast<uint32_t>(filter_op_capacity))
          : 0u;
  if (filter_op_count) {
    *filter_op_count = copied_filter_op_count;
  }
  for (uint32_t i = 0; i < copied_filter_op_count; ++i) {
    if (filter_op_types) {
      filter_op_types[i] = static_cast<uint32_t>(
          entry.filter_operations[static_cast<size_t>(i)].type);
    }
    if (filter_op_amounts) {
      filter_op_amounts[i] =
          entry.filter_operations[static_cast<size_t>(i)].amount;
    }
  }
  if (element_id && element_id_capacity > 0) {
    const size_t copied =
        std::min(entry.element_id.size(),
                 static_cast<size_t>(element_id_capacity - 1));
    std::memcpy(element_id, entry.element_id.data(), copied);
    element_id[copied] = '\0';
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

int StandaloneBlinkLiveFrameBridgePngSnapshotStatusForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  const LiveFramePaintProbeCache& cache = ProbeCache();
  if (cache.copy_output_png_succeeded) {
    return 1;
  }
  if (cache.copy_output_png_completed) {
    return -1;
  }
  return 0;
}

int StandaloneBlinkLiveFrameBridgePngSnapshotByteSizeForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().copy_output_png.size());
}

int StandaloneBlinkLiveFrameBridgePngSnapshotBytesForStandaloneRenderer(
    const char* body_html,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const std::vector<uint8_t>& png = ProbeCache().copy_output_png;
  if (!destination || destination_size <= 0 ||
      destination_size < static_cast<int>(png.size())) {
    return 0;
  }
  std::memcpy(destination, png.data(), png.size());
  return static_cast<int>(png.size());
}

int StandaloneBlinkLiveFrameBridgePngSnapshotFailureForStandaloneRenderer(
    const char* body_html,
    char* buffer,
    int buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const LiveFramePaintProbeCache& cache = ProbeCache();
  std::string failure = cache.copy_output_failure;
  if (failure.empty()) {
    std::ostringstream out;
    out << "Viz CopyOutput did not produce output"
        << " completed=" << (cache.copy_output_png_completed ? 1 : 0)
        << " succeeded=" << (cache.copy_output_png_succeeded ? 1 : 0)
        << " png_requested=" << (cache.copy_output_png_requested ? 1 : 0)
        << " raw_requested=" << (cache.copy_output_raw_requested ? 1 : 0)
        << " gpu_requested=" << (cache.copy_output_gpu_requested ? 1 : 0)
        << " host=" << (cache.cc_host_created ? 1 : 0)
        << " root=" << (cache.cc_root_layer_attached ? 1 : 0)
        << " sink=" << (cache.cc_frame_sink_bound ? 1 : 0)
        << " submitted=" << (cache.cc_compositor_frame_submitted ? 1 : 0)
        << " display=" << (cache.cc_viz_display_created ? 1 : 0)
        << " commits=" << cache.cc_commit_count
        << " frame_sink_failure=" << cache.cc_frame_sink_failure_reason;
    failure = out.str();
  }
  if (!buffer || buffer_size <= 0) {
    return 0;
  }
  const int copy_count =
      std::min(static_cast<int>(failure.size()), buffer_size - 1);
  std::memcpy(buffer, failure.data(), static_cast<size_t>(copy_count));
  buffer[copy_count] = '\0';
  return copy_count;
}

int StandaloneBlinkLiveFrameBridgeRawFrameInfoForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height,
    int* stride,
    int* pixel_format,
    int* premultiplied_alpha) {
  RunLiveFramePaintProbe(body_html);
  const LiveRawFrameOutput& raw = ProbeCache().copy_output_raw_frame;
  if (raw.pixels.empty() || raw.width <= 0 || raw.height <= 0 ||
      raw.stride <= 0 || raw.pixel_format == 0) {
    return 0;
  }
  if (width) {
    *width = raw.width;
  }
  if (height) {
    *height = raw.height;
  }
  if (stride) {
    *stride = raw.stride;
  }
  if (pixel_format) {
    *pixel_format = raw.pixel_format;
  }
  if (premultiplied_alpha) {
    *premultiplied_alpha = raw.premultiplied_alpha ? 1 : 0;
  }
  return 1;
}

int StandaloneBlinkLiveFrameBridgeRawFrameByteSizeForStandaloneRenderer(
    const char* body_html) {
  RunLiveFramePaintProbe(body_html);
  return static_cast<int>(ProbeCache().copy_output_raw_frame.pixels.size());
}

int StandaloneBlinkLiveFrameBridgeRawFrameBytesForStandaloneRenderer(
    const char* body_html,
    uint8_t* destination,
    int destination_size) {
  RunLiveFramePaintProbe(body_html);
  const std::vector<uint8_t>& pixels = ProbeCache().copy_output_raw_frame.pixels;
  if (!destination || destination_size <= 0 ||
      destination_size < static_cast<int>(pixels.size())) {
    return 0;
  }
  std::memcpy(destination, pixels.data(), pixels.size());
  return static_cast<int>(pixels.size());
}

int StandaloneBlinkLiveFrameBridgeGpuFrameInfoForStandaloneRenderer(
    const char* body_html,
    int* width,
    int* height,
    int* is_software,
    int* vk_context_provider,
    int* is_vulkan_context,
    char* format,
    int format_capacity,
    char* mailbox,
    int mailbox_capacity,
    char* creation_sync_token,
    int creation_sync_token_capacity) {
  RunLiveFramePaintProbe(body_html);
  const LiveGpuFrameOutput& gpu_frame = ProbeCache().copy_output_gpu_frame;
  if (!gpu_frame.shared_image_available || gpu_frame.width <= 0 ||
      gpu_frame.height <= 0 || gpu_frame.mailbox.empty()) {
    return 0;
  }
  if (width) {
    *width = gpu_frame.width;
  }
  if (height) {
    *height = gpu_frame.height;
  }
  if (is_software) {
    *is_software = gpu_frame.is_software ? 1 : 0;
  }
  if (vk_context_provider) {
    *vk_context_provider =
        gpu_frame.vk_context_provider_available ? 1 : 0;
  }
  if (is_vulkan_context) {
    *is_vulkan_context =
        gpu_frame.shared_context_state_is_vulkan ? 1 : 0;
  }
  if (format && format_capacity > 0) {
    const int copy_count =
        std::min(static_cast<int>(gpu_frame.format.size()),
                 format_capacity - 1);
    std::memcpy(format, gpu_frame.format.data(),
                static_cast<size_t>(copy_count));
    format[copy_count] = '\0';
  }
  if (mailbox && mailbox_capacity > 0) {
    const int copy_count =
        std::min(static_cast<int>(gpu_frame.mailbox.size()),
                 mailbox_capacity - 1);
    std::memcpy(mailbox, gpu_frame.mailbox.data(),
                static_cast<size_t>(copy_count));
    mailbox[copy_count] = '\0';
  }
  if (creation_sync_token && creation_sync_token_capacity > 0) {
    const int copy_count =
        std::min(static_cast<int>(gpu_frame.creation_sync_token.size()),
                 creation_sync_token_capacity - 1);
    std::memcpy(creation_sync_token, gpu_frame.creation_sync_token.data(),
                static_cast<size_t>(copy_count));
    creation_sync_token[copy_count] = '\0';
  }
  return 1;
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

int StandaloneBlinkLiveFrameBridgeFinerCacheUnitCountForStandaloneRenderer(
    const char* body_html,
    int chunk_index) {
  RunLiveFramePaintProbe(body_html);
  const auto& units_by_chunk = ProbeCache().finer_cache_units_by_chunk;
  if (chunk_index < 0 ||
      static_cast<size_t>(chunk_index) >= units_by_chunk.size()) {
    return 0;
  }
  return static_cast<int>(
      units_by_chunk[static_cast<size_t>(chunk_index)].size());
}

int StandaloneBlinkLiveFrameBridgeFinerCacheUnitAtForStandaloneRenderer(
    const char* body_html,
    int chunk_index,
    int unit_index,
    int* exported_unit_index,
    int* begin_display_item_index,
    int* end_display_item_index,
    uint64_t* display_item_client_id,
    int* display_item_client_id_valid,
    float* visual_x,
    float* visual_y,
    float* visual_width,
    float* visual_height,
    uint64_t* content_hash,
    uint64_t* resource_signal_hash,
    int* display_item_count,
    int* drawing_item_count,
    int* paint_op_count,
    int* recursive_paint_op_count,
    int* visual_op_count,
    int* conservative_candidate,
    int* has_save_layer_ops,
    int* has_non_rect_clip_ops,
    int* has_non_translation_transform,
    int* has_effect_opacity,
    int* has_shader_ops,
    int* has_image_ops,
    int* has_path_ops,
    int* has_filter_ops,
    int* has_path_effect_ops,
    char* stable_key_buffer,
    int stable_key_buffer_size) {
  RunLiveFramePaintProbe(body_html);
  const auto& units_by_chunk = ProbeCache().finer_cache_units_by_chunk;
  if (chunk_index < 0 ||
      static_cast<size_t>(chunk_index) >= units_by_chunk.size()) {
    return 0;
  }
  const auto& units = units_by_chunk[static_cast<size_t>(chunk_index)];
  if (unit_index < 0 || static_cast<size_t>(unit_index) >= units.size()) {
    return 0;
  }
  const LiveFinerCacheUnitDescriptor& unit =
      units[static_cast<size_t>(unit_index)];
  if (exported_unit_index) {
    *exported_unit_index = unit.unit_index;
  }
  if (begin_display_item_index) {
    *begin_display_item_index = unit.begin_display_item_index;
  }
  if (end_display_item_index) {
    *end_display_item_index = unit.end_display_item_index;
  }
  if (display_item_client_id) {
    *display_item_client_id = unit.display_item_client_id;
  }
  if (display_item_client_id_valid) {
    *display_item_client_id_valid =
        unit.display_item_client_id_valid ? 1 : 0;
  }
  if (visual_x) {
    *visual_x = unit.visual_x;
  }
  if (visual_y) {
    *visual_y = unit.visual_y;
  }
  if (visual_width) {
    *visual_width = unit.visual_width;
  }
  if (visual_height) {
    *visual_height = unit.visual_height;
  }
  if (content_hash) {
    *content_hash = unit.content_hash;
  }
  if (resource_signal_hash) {
    *resource_signal_hash = unit.resource_signal_hash;
  }
  if (display_item_count) {
    *display_item_count = unit.display_item_count;
  }
  if (drawing_item_count) {
    *drawing_item_count = unit.drawing_item_count;
  }
  if (paint_op_count) {
    *paint_op_count = unit.paint_op_count;
  }
  if (recursive_paint_op_count) {
    *recursive_paint_op_count = unit.recursive_paint_op_count;
  }
  if (visual_op_count) {
    *visual_op_count = unit.visual_op_count;
  }
  if (conservative_candidate) {
    *conservative_candidate = unit.conservative_candidate ? 1 : 0;
  }
  if (has_save_layer_ops) {
    *has_save_layer_ops = unit.has_save_layer_ops ? 1 : 0;
  }
  if (has_non_rect_clip_ops) {
    *has_non_rect_clip_ops = unit.has_non_rect_clip_ops ? 1 : 0;
  }
  if (has_non_translation_transform) {
    *has_non_translation_transform =
        unit.has_non_translation_transform ? 1 : 0;
  }
  if (has_effect_opacity) {
    *has_effect_opacity = unit.has_effect_opacity ? 1 : 0;
  }
  if (has_shader_ops) {
    *has_shader_ops = unit.has_shader_ops ? 1 : 0;
  }
  if (has_image_ops) {
    *has_image_ops = unit.has_image_ops ? 1 : 0;
  }
  if (has_path_ops) {
    *has_path_ops = unit.has_path_ops ? 1 : 0;
  }
  if (has_filter_ops) {
    *has_filter_ops = unit.has_filter_ops ? 1 : 0;
  }
  if (has_path_effect_ops) {
    *has_path_effect_ops = unit.has_path_effect_ops ? 1 : 0;
  }
  if (stable_key_buffer && stable_key_buffer_size > 0) {
    const int copy_count = std::min(
        static_cast<int>(unit.stable_key.size()), stable_key_buffer_size - 1);
    std::memcpy(stable_key_buffer, unit.stable_key.data(),
                static_cast<size_t>(copy_count));
    stable_key_buffer[copy_count] = '\0';
  }
  return 1;
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

int StandaloneBlinkLiveFrameBridgeExportedDrawOpSourceAtForStandaloneRenderer(
    const char* body_html,
    int op_index,
    int* source_chunk_index,
    int* source_display_item_index,
    uint64_t* source_display_item_client_id,
    int* source_display_item_client_id_valid) {
  RunLiveFramePaintProbe(body_html);
  const auto& ops = ProbeCache().exported_draw_ops;
  if (op_index < 0 || static_cast<size_t>(op_index) >= ops.size()) {
    return 0;
  }
  const LiveExportedDrawOp& op = ops[static_cast<size_t>(op_index)];
  if (source_chunk_index) {
    *source_chunk_index = op.source_chunk_index;
  }
  if (source_display_item_index) {
    *source_display_item_index = op.source_display_item_index;
  }
  if (source_display_item_client_id) {
    *source_display_item_client_id = op.source_display_item_client_id;
  }
  if (source_display_item_client_id_valid) {
    *source_display_item_client_id_valid =
        op.source_display_item_client_id_valid ? 1 : 0;
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
  if (op.type != 5 && op.type != 6 && op.type != 15 && op.type != 20) {
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
