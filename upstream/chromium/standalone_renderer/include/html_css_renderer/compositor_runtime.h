#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_RUNTIME_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_RUNTIME_H_

#include <memory>
#include <string>
#include <vector>

#include "html_css_renderer/compositor_types.h"

namespace html_css_renderer {

struct CompositorRuntimeCreateInfo {
  RendererCreateInfo renderer;
  bool enable_paint_artifact_audit = false;
  bool trace_stages = false;
  bool no_script_profile = false;
  bool transparent_background = false;
  std::string lifecycle_stop;
};

struct CompositorFrameTiming {
  double runtime_apply_state_ms = 0.0;
  double runtime_bridge_query_ms = 0.0;
  double runtime_total_ms = 0.0;
  double bridge_total_ms = 0.0;
  double bridge_input_setup_ms = 0.0;
  double bridge_html_document_setup_ms = 0.0;
  double bridge_style_update_ms = 0.0;
  double bridge_layout_lifecycle_ms = 0.0;
  double bridge_prepaint_and_paint_lifecycle_ms = 0.0;
  double bridge_paint_artifact_generation_ms = 0.0;
  double bridge_paint_artifact_audit_ms = 0.0;
  double bridge_paint_artifact_extraction_ms = 0.0;
  double bridge_cc_composite_ms = 0.0;
  double bridge_cc_frame_sink_warmup_ms = 0.0;
  double bridge_cc_root_preattach_ms = 0.0;
  double bridge_cc_pending_update_ms = 0.0;
  double bridge_cc_scheduler_run_loop_ms = 0.0;
  double bridge_cc_submit_wait_ms = 0.0;
  double bridge_cc_startup_prewarm_ms = 0.0;
  bool bridge_cache_hit = false;
  bool bridge_reused_live_document = false;
  bool bridge_rebuilt_for_attributes = false;
};

struct GpuFrameOutput {
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

struct CompositorFrameResult {
  RendererSnapshot successor_snapshot;
  CompositorFrameTiming timing;
  bool frame_advanced = true;
  bool frame_skipped_due_to_no_demand = false;
  bool paint_clean = false;
  bool root_layer_available = false;
  bool cc_host_created = false;
  bool cc_root_layer_attached = false;
  bool cc_commit_requested = false;
  bool cc_frame_sink_requested = false;
  bool cc_frame_sink_bound = false;
  bool gpu_context_created = false;
  bool raster_context_created = false;
  bool shared_image_interface_available = false;
  bool compositor_frame_submitted = false;
  bool viz_display_created = false;
  bool skia_renderer_gpu_path_reached = false;
  Size compositor_output_size;
  Size viz_display_output_size;
  int compositor_layer_count = 0;
  int paint_chunk_count = 0;
  int display_item_count = 0;
  bool needs_begin_frame = false;
  bool png_snapshot_requested = false;
  bool png_snapshot_available = false;
  std::string png_snapshot_failure;
  std::vector<uint8_t> png_snapshot_bytes;
  bool raw_frame_requested = false;
  std::string raw_frame_failure;
  RawFrameOutput raw_frame;
  bool gpu_frame_requested = false;
  std::string gpu_frame_failure;
  GpuFrameOutput gpu_frame;
  std::string raw_paint_artifact_audit_json;
  std::vector<HitTestEntry> hit_test_entries;
  std::vector<FormControlEntry> form_control_entries;
  std::vector<BackdropFilterRegion> backdrop_filter_regions;
  std::vector<ScrollableElementEntry> scrollable_element_entries;
  Point document_max_scroll_offset;
  std::vector<std::string> diagnostics;
};

struct NativeWindowConfig {
  void* win32_hwnd = nullptr;
  Size viewport;
};

struct NativePresentationResult {
  bool native_window_available = false;
  bool vulkan_instance_initialized = false;
  bool vulkan_device_queue_initialized = false;
  bool vulkan_surface_created = false;
  bool vulkan_surface_initialized = false;
  bool vulkan_swapchain_created = false;
  bool vulkan_presented = false;
  bool viz_frame_sink_manager_created = false;
  bool viz_frame_sink_support_created = false;
  bool viz_display_created = false;
  bool cc_host_created = false;
  bool cc_root_layer_attached = false;
  bool cc_commit_requested = false;
  bool cc_frame_sink_requested = false;
  bool cc_frame_sink_bound = false;
  bool gpu_context_created = false;
  bool raster_context_created = false;
  bool shared_image_interface_available = false;
  bool compositor_frame_submitted = false;
  bool skia_renderer_gpu_path_reached = false;
  Size surface_size;
  Size compositor_output_size;
  Size viz_display_output_size;
  std::string failure_reason;
  std::vector<std::string> diagnostics;
};

class StandaloneCompositorRuntime {
 public:
  virtual ~StandaloneCompositorRuntime() = default;

  virtual bool Initialize(std::vector<std::string>* diagnostics) = 0;
  virtual NativePresentationResult InitializeNativeWindow(
      const NativeWindowConfig& config) = 0;
  virtual CompositorFrameResult AdvanceFrame(const FrameInput& input) = 0;
  virtual NativePresentationResult PresentToNativeWindow(
      const CompositorFrameResult& frame) = 0;
  virtual RendererSnapshot Snapshot() const = 0;
  virtual bool HasLiveElement(const std::string& element_id) const = 0;
  virtual bool HasLiveBody() const = 0;
  virtual std::string RunBorrowedVkImageBackingSmokeForTesting() = 0;
};

std::unique_ptr<StandaloneCompositorRuntime> CreateStandaloneCompositorRuntime(
    CompositorRuntimeCreateInfo create_info);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_RUNTIME_H_
