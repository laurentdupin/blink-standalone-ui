#include "html_css_renderer/vulkan_window_host.h"

#include <algorithm>
#include <memory>
#include <optional>
#include <string>
#include <utility>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>

#include "base/functional/callback_helpers.h"
#include "components/viz/common/surfaces/frame_sink_id.h"
#include "components/viz/service/frame_sinks/compositor_frame_sink_support.h"
#include "components/viz/service/frame_sinks/frame_sink_manager_impl.h"
#include "gpu/vulkan/init/vulkan_factory.h"
#include "gpu/vulkan/vulkan_command_buffer.h"
#include "gpu/vulkan/vulkan_command_pool.h"
#include "gpu/vulkan/vulkan_device_queue.h"
#include "gpu/vulkan/vulkan_function_pointers.h"
#include "gpu/vulkan/vulkan_implementation.h"
#include "gpu/vulkan/vulkan_surface.h"
#include "gpu/vulkan/vulkan_swap_chain.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/overlay_transform.h"
#include "ui/gfx/presentation_feedback.h"
#include "ui/gfx/swap_result.h"

namespace html_css_renderer {
namespace {

gfx::Size ToGfxSize(Size size) {
  return gfx::Size(std::max(1, static_cast<int>(size.width)),
                   std::max(1, static_cast<int>(size.height)));
}

Size ToRendererSize(const gfx::Size& size) {
  return Size{static_cast<float>(size.width()),
              static_cast<float>(size.height())};
}

void AddDiagnostic(NativePresentationResult& result, std::string diagnostic) {
  result.diagnostics.push_back(std::move(diagnostic));
}

void SetFailure(NativePresentationResult& result, std::string failure) {
  result.failure_reason = std::move(failure);
  AddDiagnostic(result, "presentation failure: " + result.failure_reason);
}

std::string SwapResultName(gfx::SwapResult result) {
  switch (result) {
    case gfx::SwapResult::SWAP_ACK:
      return "SWAP_ACK";
    case gfx::SwapResult::SWAP_NAK_RECREATE_BUFFERS:
      return "SWAP_NAK_RECREATE_BUFFERS";
    case gfx::SwapResult::SWAP_FAILED:
      return "SWAP_FAILED";
  }
  return "unknown swap result";
}

}  // namespace

class VulkanWindowHost::Impl {
 public:
  ~Impl() { Shutdown(); }

  NativePresentationResult Initialize(const NativeWindowConfig& config) {
    Shutdown();

    NativePresentationResult result;
    result.native_window_available = config.win32_hwnd != nullptr;
    if (!result.native_window_available) {
      SetFailure(result, "SDL did not expose a Win32 HWND");
      return result;
    }

    hwnd_ = reinterpret_cast<HWND>(config.win32_hwnd);
    surface_size_ = ToGfxSize(config.viewport);
    result.surface_size = ToRendererSize(surface_size_);
    AddDiagnostic(result, "SDL native window handle acquired");

    vulkan_implementation_ = gpu::CreateVulkanImplementation(false);
    if (!vulkan_implementation_) {
      SetFailure(result, "gpu::CreateVulkanImplementation returned null");
      return result;
    }

    result.vulkan_instance_initialized =
        vulkan_implementation_->InitializeVulkanInstance(true);
    if (!result.vulkan_instance_initialized) {
      SetFailure(result, "Chromium Vulkan instance initialization failed");
      return result;
    }
    AddDiagnostic(result, "Chromium Vulkan instance initialized");

    device_queue_ = gpu::CreateVulkanDeviceQueue(
        vulkan_implementation_.get(),
        gpu::VulkanDeviceQueue::GRAPHICS_QUEUE_FLAG |
            gpu::VulkanDeviceQueue::PRESENTATION_SUPPORT_QUEUE_FLAG);
    result.vulkan_device_queue_initialized = device_queue_ != nullptr;
    if (!result.vulkan_device_queue_initialized) {
      SetFailure(result, "Chromium Vulkan device/queue initialization failed");
      return result;
    }
    AddDiagnostic(result, "Chromium Vulkan graphics/presentation queue initialized");

    surface_ = vulkan_implementation_->CreateViewSurface(hwnd_);
    result.vulkan_surface_created = surface_ != nullptr;
    if (!result.vulkan_surface_created) {
      SetFailure(result, "Chromium Win32 Vulkan surface creation failed");
      return result;
    }
    AddDiagnostic(result, "Chromium Win32 Vulkan surface created");

    result.vulkan_surface_initialized = surface_->Initialize(
        device_queue_.get(), gpu::VulkanSurface::DEFAULT_SURFACE_FORMAT);
    if (!result.vulkan_surface_initialized) {
      SetFailure(result, "Chromium Vulkan surface initialization failed");
      return result;
    }

    if (!surface_->Reshape(surface_size_, gfx::OVERLAY_TRANSFORM_NONE)) {
      SetFailure(result, "Chromium Vulkan surface reshape/swapchain creation failed");
      return result;
    }
    result.vulkan_swapchain_created = surface_->swap_chain() != nullptr;
    if (!result.vulkan_swapchain_created) {
      SetFailure(result, "Chromium Vulkan swapchain is not available after reshape");
      return result;
    }
    AddDiagnostic(result, "Chromium Vulkan surface initialized and swapchain created");

    command_pool_ = std::make_unique<gpu::VulkanCommandPool>(device_queue_.get());
    if (!command_pool_->Initialize()) {
      SetFailure(result, "Chromium Vulkan command pool initialization failed");
      return result;
    }

    viz_frame_sink_manager_ = std::make_unique<viz::FrameSinkManagerImpl>(
        viz::FrameSinkManagerImpl::InitParams());
    result.viz_frame_sink_manager_created =
        viz_frame_sink_manager_ != nullptr;
    if (!result.viz_frame_sink_manager_created) {
      SetFailure(result, "Viz FrameSinkManagerImpl creation failed");
      return result;
    }

    viz_frame_sink_support_ = std::make_unique<viz::CompositorFrameSinkSupport>(
        nullptr, viz_frame_sink_manager_.get(), viz::FrameSinkId(1, 1), true);
    result.viz_frame_sink_support_created =
        viz_frame_sink_support_ != nullptr;
    if (!result.viz_frame_sink_support_created) {
      SetFailure(result, "Viz CompositorFrameSinkSupport creation failed");
      return result;
    }

    initialized_ = true;
    AddDiagnostic(result, "Chromium Vulkan presentation host is ready");
    AddDiagnostic(result, "Viz FrameSinkManagerImpl created");
    AddDiagnostic(result, "Viz CompositorFrameSinkSupport created");
    AddDiagnostic(result,
                  "Viz FrameSinkManager/CompositorFrameSinkSupport are ready; "
                  "the submitted cc frame creates the Viz Display/Skia GPU "
                  "path when an HWND-backed frame is advanced");
    return result;
  }

  NativePresentationResult Present(const CompositorFrameResult& frame) {
    NativePresentationResult result;
    result.native_window_available = hwnd_ != nullptr;
    result.vulkan_instance_initialized = vulkan_implementation_ != nullptr;
    result.vulkan_device_queue_initialized = device_queue_ != nullptr;
    result.vulkan_surface_created = surface_ != nullptr;
    result.vulkan_surface_initialized = initialized_;
    result.vulkan_swapchain_created = surface_ && surface_->swap_chain();
    result.surface_size = ToRendererSize(surface_size_);
    result.viz_frame_sink_manager_created =
        viz_frame_sink_manager_ != nullptr;
    result.viz_frame_sink_support_created =
        viz_frame_sink_support_ != nullptr;
    result.cc_host_created = frame.cc_host_created;
    result.cc_root_layer_attached = frame.cc_root_layer_attached;
    result.cc_commit_requested = frame.cc_commit_requested;
    result.cc_frame_sink_requested = frame.cc_frame_sink_requested;
    result.cc_frame_sink_bound = frame.cc_frame_sink_bound;
    result.gpu_context_created = frame.gpu_context_created;
    result.raster_context_created = frame.raster_context_created;
    result.shared_image_interface_available =
        frame.shared_image_interface_available;
    result.compositor_frame_submitted = frame.compositor_frame_submitted;
    result.viz_display_created = frame.viz_display_created;
    result.skia_renderer_gpu_path_reached =
        frame.skia_renderer_gpu_path_reached;
    result.compositor_output_size = frame.compositor_output_size;
    result.viz_display_output_size = frame.viz_display_output_size;

    if (!initialized_) {
      SetFailure(result, "Chromium Vulkan presentation host is not initialized");
      return result;
    }
    if (!frame.paint_clean || !frame.root_layer_available) {
      SetFailure(result,
                 "Blink/cc frame is not presentable: PaintClean/root layer is missing");
      return result;
    }

    const gfx::Size requested_size = ToGfxSize(frame.successor_snapshot.viewport);
    if (requested_size != surface_size_) {
      if (!surface_->Reshape(requested_size, gfx::OVERLAY_TRANSFORM_NONE)) {
        SetFailure(result, "Chromium Vulkan surface resize failed");
        return result;
      }
      surface_size_ = requested_size;
      result.surface_size = ToRendererSize(surface_size_);
      result.vulkan_swapchain_created = surface_->swap_chain() != nullptr;
      AddDiagnostic(result, "Chromium Vulkan swapchain resized");
    }

    std::optional<gpu::VulkanSwapChain::ScopedWrite> scoped_write;
    scoped_write.emplace(surface_->swap_chain());
    if (!scoped_write->success()) {
      SetFailure(result, "Chromium Vulkan swapchain image acquisition failed");
      return result;
    }

    VkSemaphore begin_semaphore = scoped_write->begin_semaphore();
    VkSemaphore end_semaphore = scoped_write->end_semaphore();
    auto command_buffer = command_pool_->CreatePrimaryCommandBuffer();
    if (!command_buffer) {
      SetFailure(result, "Chromium Vulkan command buffer allocation failed");
      scoped_write.reset();
      return result;
    }

    {
      gpu::ScopedSingleUseCommandBufferRecorder recorder(*command_buffer);
      command_buffer->TransitionImageLayout(scoped_write->image(),
                                            scoped_write->image_layout(),
                                            VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);
    }
    if (!command_buffer->Submit(1, &begin_semaphore, 1, &end_semaphore)) {
      SetFailure(result, "Chromium Vulkan command buffer submission failed");
      command_buffer->Destroy();
      scoped_write.reset();
      return result;
    }
    scoped_write.reset();

    const gfx::SwapResult swap_result = surface_->SwapBuffers(
        base::DoNothingAs<void(const gfx::PresentationFeedback&)>());
    vkQueueWaitIdle(device_queue_->GetVulkanQueue());
    command_buffer->Destroy();

    result.vulkan_presented = swap_result == gfx::SwapResult::SWAP_ACK;
    AddDiagnostic(result, "Chromium Vulkan swap result: " +
                              SwapResultName(swap_result));
    if (!result.vulkan_presented) {
      SetFailure(result, "Chromium Vulkan swap did not acknowledge presentation");
      return result;
    }

    AddDiagnostic(result,
                  result.viz_display_created
                      ? "Viz Display is available for the submitted cc root surface"
                      : "Vulkan presented through Chromium's Win32 surface/swapchain; "
                        "the submitted cc root surface has not reached a Viz Display");
    AddDiagnostic(result,
                  result.skia_renderer_gpu_path_reached
                      ? "Viz SkiaRenderer GPU draw/swap path was reached"
                      : "Viz SkiaRenderer GPU draw/swap path was not reached");
    return result;
  }

 private:
  void Shutdown() {
    if (surface_) {
      if (device_queue_)
        surface_->Finish();
      surface_->Destroy();
      surface_.reset();
    }
    if (command_pool_) {
      command_pool_->Destroy();
      command_pool_.reset();
    }
    viz_frame_sink_support_.reset();
    viz_frame_sink_manager_.reset();
    if (device_queue_) {
      device_queue_->Destroy();
      device_queue_.reset();
    }
    vulkan_implementation_.reset();
    hwnd_ = nullptr;
    initialized_ = false;
    surface_size_ = gfx::Size();
  }

  HWND hwnd_ = nullptr;
  gfx::Size surface_size_;
  bool initialized_ = false;
  std::unique_ptr<gpu::VulkanImplementation> vulkan_implementation_;
  std::unique_ptr<gpu::VulkanDeviceQueue> device_queue_;
  std::unique_ptr<gpu::VulkanSurface> surface_;
  std::unique_ptr<gpu::VulkanCommandPool> command_pool_;
  std::unique_ptr<viz::FrameSinkManagerImpl> viz_frame_sink_manager_;
  std::unique_ptr<viz::CompositorFrameSinkSupport> viz_frame_sink_support_;
};

VulkanWindowHost::VulkanWindowHost() : impl_(std::make_unique<Impl>()) {}

VulkanWindowHost::~VulkanWindowHost() = default;

NativePresentationResult VulkanWindowHost::Initialize(
    const NativeWindowConfig& config) {
  return impl_->Initialize(config);
}

NativePresentationResult VulkanWindowHost::Present(
    const CompositorFrameResult& frame) {
  return impl_->Present(frame);
}

}  // namespace html_css_renderer
