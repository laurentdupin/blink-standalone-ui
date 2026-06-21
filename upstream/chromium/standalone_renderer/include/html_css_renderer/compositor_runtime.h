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
  std::string lifecycle_stop;
};

struct CompositorFrameResult {
  RendererSnapshot successor_snapshot;
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
  int compositor_layer_count = 0;
  int paint_chunk_count = 0;
  int display_item_count = 0;
  bool needs_begin_frame = false;
  bool png_snapshot_requested = false;
  bool png_snapshot_available = false;
  std::string png_snapshot_failure;
  std::vector<uint8_t> png_snapshot_bytes;
  std::string raw_paint_artifact_audit_json;
  std::vector<HitTestEntry> hit_test_entries;
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
};

std::unique_ptr<StandaloneCompositorRuntime> CreateStandaloneCompositorRuntime(
    CompositorRuntimeCreateInfo create_info);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_RUNTIME_H_
