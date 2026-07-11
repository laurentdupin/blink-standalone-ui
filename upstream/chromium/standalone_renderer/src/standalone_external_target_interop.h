// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_SRC_STANDALONE_EXTERNAL_TARGET_INTEROP_H_
#define STANDALONE_RENDERER_SRC_STANDALONE_EXTERNAL_TARGET_INTEROP_H_

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "base/functional/callback_forward.h"
#include "base/task/single_thread_task_runner.h"
#include "base/containers/span.h"
#include "build/build_config.h"
#include "gpu/command_buffer/common/shared_image_info.h"
#include "gpu/command_buffer/client/client_shared_image.h"
#include "gpu/command_buffer/service/dawn_context_provider.h"
#include "gpu/command_buffer/service/shared_context_state.h"
#include "gpu/command_buffer/service/shared_image/skia_graphite_dawn_image_representation.h"
#include "gpu/command_buffer/service/shared_image/d3d_image_utils.h"
#include "gpu/command_buffer/service/shared_image/shared_image_backing.h"
#include "gpu/command_buffer/service/shared_image/shared_image_representation.h"
#include "html_css_renderer/compositor_runtime.h"
#include "ui/gfx/geometry/size.h"

#include "third_party/skia/include/gpu/ganesh/GrBackendSurface.h"
#include "third_party/skia/include/core/SkColor.h"

#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
#include <d3d12.h>
#include <wrl/client.h>
#endif

namespace gpu {
class Mailbox;
class SharedContextState;
class SharedImageManager;
}  // namespace gpu

class SkCanvas;

namespace html_css_renderer::standalone_interop {

#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
class BorrowedD3D12TextureBacking;
#endif

// This is intentionally Blink-free. It is the C API adapter's input to the
// borrowed-target mask renderer, not a representation of Blink paint state.
enum BackdropMaskRegionFlags : uint32_t {
  kBackdropMaskRegionRoundedRect = 1u << 0,
};

struct BackdropMaskRegion {
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
  float border_radius_top_left = 0.0f;
  float border_radius_top_right = 0.0f;
  float border_radius_bottom_right = 0.0f;
  float border_radius_bottom_left = 0.0f;
  uint32_t flags = 0;
};

// The bridge implements this privately. The borrowed-target adapter never
// reaches into Blink, Display, or an output-surface provider directly.
class ExternalTargetInteropContext {
 public:
  virtual ~ExternalTargetInteropContext() = default;

  virtual gpu::SharedImageManager* GetSharedImageManager() = 0;
  virtual scoped_refptr<gpu::SharedContextState> GetSharedContextState() = 0;
  virtual bool UsesOffscreenVulkan() const = 0;
  virtual bool UsesOffscreenD3D12() const = 0;
  virtual bool IsOffscreen() const = 0;
  virtual scoped_refptr<base::SingleThreadTaskRunner> GetGpuTaskRunner() = 0;
};

class ExternalTargetInterop {
 public:
  struct VulkanReleaseResult {
    bool backing_released = false;
    bool target_destroyed = false;
  };
#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  struct D3D12ReleaseResult {
    bool backing_released = false;
    bool target_destroyed = false;
  };
  struct D3D12VerificationResult {
    bool prepared = false;
    bool readback_verified = false;
    bool shared_texture_memory = false;
    bool nontransparent = false;
    int width = 0;
    int height = 0;
    std::string failure;
  };
  struct D3D12PreparationResult {
    bool prepared = false;
    std::string failure;
  };
#endif
  explicit ExternalTargetInterop(ExternalTargetInteropContext& context)
      : context_(context) {}

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


  std::unique_ptr<BorrowedVkImageRenderCopyBlitTarget>& borrowed_vulkan_target() {
    return borrowed_vulkan_target_;
  }

#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  struct BorrowedD3D12RenderCopyBlitTarget {
    gfx::Size size;
    std::string format = "RGBA_8888";
    gpu::Mailbox mailbox;
    Microsoft::WRL::ComPtr<ID3D12Resource> resource;
    raw_ptr<html_css_renderer::standalone_interop::BorrowedD3D12TextureBacking>
        backing = nullptr;
    raw_ptr<gpu::MemoryTypeTracker> registration_tracker = nullptr;
    std::unique_ptr<gpu::SharedImageRepresentationFactoryRef> factory_ref;
    scoped_refptr<gpu::ClientSharedImage> client_shared_image;
    bool target_created = false;
    bool external_resource = false;
    bool shared_texture_memory_created = false;
    bool registered = false;
  };


  std::unique_ptr<BorrowedD3D12RenderCopyBlitTarget>& borrowed_d3d12_target() {
    return borrowed_d3d12_target_;
  }
  void*& cached_d3d12_shared_handle() { return cached_external_d3d12_shared_handle_; }
  raw_ptr<ID3D12Resource>& cached_d3d12_resource_hint() {
    return cached_external_d3d12_resource_hint_;
  }
  Microsoft::WRL::ComPtr<IUnknown>& cached_d3d12_resource_identity() {
    return cached_external_d3d12_resource_identity_;
  }
  Microsoft::WRL::ComPtr<ID3D12Resource>& cached_d3d12_opened_resource() {
    return cached_external_d3d12_opened_resource_;
  }
#endif

  std::string VerifyBorrowedVulkanTarget();
  std::string PrepareBorrowedVulkanTarget(
      const gfx::Size& target_size,
      gpu::VulkanImage* external_image,
      const html_css_renderer::ExternalVulkanImageTarget* external_target,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image);
  std::string RenderBorrowedVulkanBackdropMask(
      const gfx::Size& output_size,
      const gfx::Size& css_viewport,
      const std::vector<BackdropMaskRegion>& regions);
  VulkanReleaseResult DiscardBorrowedVulkanTarget();
#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  D3D12ReleaseResult DiscardBorrowedD3D12Target();
  D3D12VerificationResult VerifyBorrowedD3D12Target();
  D3D12PreparationResult PrepareBorrowedD3D12Target(
      const gfx::Size& target_size,
      ID3D12Resource* external_resource,
      void* shared_handle,
      scoped_refptr<gpu::ClientSharedImage>* target_shared_image);
  std::string RenderBorrowedD3D12BackdropMask(
      const gfx::Size& output_size,
      const gfx::Size& css_viewport,
      const std::vector<BackdropMaskRegion>& regions);
#endif

 private:
  ExternalTargetInteropContext& context_;
  std::unique_ptr<BorrowedVkImageRenderCopyBlitTarget> borrowed_vulkan_target_;
#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  std::unique_ptr<BorrowedD3D12RenderCopyBlitTarget> borrowed_d3d12_target_;
  void* cached_external_d3d12_shared_handle_ = nullptr;
  raw_ptr<ID3D12Resource> cached_external_d3d12_resource_hint_ = nullptr;
  Microsoft::WRL::ComPtr<IUnknown> cached_external_d3d12_resource_identity_;
  Microsoft::WRL::ComPtr<ID3D12Resource> cached_external_d3d12_opened_resource_;
#endif
};

// An exercised context-only preparation guard used before borrowed Vulkan
// registration. Later lifecycle methods move behind this same interface.
std::string ValidateVulkanPreparationContext(ExternalTargetInteropContext& context);

size_t PopulateBackdropMaskRows(uint8_t* dst,
                                size_t row_pitch,
                                const gfx::Size& output_size,
                                const gfx::Size& css_viewport,
                                const std::vector<BackdropMaskRegion>& regions);

// Draws the same id/coverage encoding used by the CPU-backed D3D12 mask path.
// The caller owns the Skia surface and submission ordering.
void DrawBackdropMask(SkCanvas* canvas,
                      const gfx::Size& output_size,
                      const gfx::Size& css_viewport,
                      const std::vector<BackdropMaskRegion>& regions);

// Registers only an embedder-borrowed VkImage with Chromium SharedImage. The
// caller retains the VkImage lifetime and unregisters the backing before it
// releases the target.
std::unique_ptr<gpu::SharedImageBacking> CreateBorrowedVulkanImageBacking(
    const gpu::Mailbox& mailbox,
    const gpu::SharedImageInfo& si_info,
    scoped_refptr<gpu::SharedContextState> context_state,
    const GrBackendTexture& backend_texture);

#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
class BorrowedD3D12TextureBacking final
    : public gpu::ClearTrackingSharedImageBacking {
 public:
  BorrowedD3D12TextureBacking(
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

  BorrowedD3D12TextureBacking(
      const BorrowedD3D12TextureBacking&) = delete;
  BorrowedD3D12TextureBacking& operator=(
      const BorrowedD3D12TextureBacking&) = delete;

  ~BorrowedD3D12TextureBacking() override {
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
                       BorrowedD3D12TextureBacking* backing,
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

    BorrowedD3D12TextureBacking* borrowed_backing() {
      return static_cast<BorrowedD3D12TextureBacking*>(backing());
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

inline std::unique_ptr<gpu::DawnImageRepresentation>
BorrowedD3D12TextureBacking::ProduceDawn(
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

inline std::unique_ptr<gpu::SkiaGraphiteImageRepresentation>
BorrowedD3D12TextureBacking::ProduceSkiaGraphite(
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


}  // namespace html_css_renderer::standalone_interop

#endif  // STANDALONE_RENDERER_SRC_STANDALONE_EXTERNAL_TARGET_INTEROP_H_
