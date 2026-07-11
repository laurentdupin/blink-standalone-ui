// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "standalone_renderer/src/standalone_external_target_interop.h"

#include <algorithm>
#include <cmath>

#include "third_party/skia/include/core/SkCanvas.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/skia/include/core/SkColorSpace.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPaint.h"
#include "third_party/skia/include/core/SkRRect.h"
#include "third_party/skia/include/core/SkRect.h"
#include "components/viz/common/resources/shared_image_format_utils.h"
#include "gpu/command_buffer/service/memory_tracking.h"
#include "gpu/command_buffer/service/shared_context_state.h"
#include "gpu/command_buffer/service/shared_image/shared_image_manager.h"
#include "gpu/command_buffer/service/shared_image/shared_image_representation.h"
#include "gpu/command_buffer/service/skia_utils.h"
#include "gpu/vulkan/vulkan_device_queue.h"
#include "gpu/vulkan/vulkan_image.h"
#include "gpu/command_buffer/client/client_shared_image.h"
#include "components/viz/common/gpu/vulkan_in_process_context_provider.h"
#include "third_party/skia/include/gpu/ganesh/SkSurfaceGanesh.h"
#include "third_party/skia/include/gpu/ganesh/GrBackendSemaphore.h"
#include "third_party/skia/include/gpu/ganesh/vk/GrVkBackendSurface.h"
#include "third_party/skia/include/private/chromium/GrPromiseImageTexture.h"

namespace html_css_renderer::standalone_interop {
namespace {

bool PointInsideRegion(const BackdropMaskRegion& region,
                       float pixel_x,
                       float pixel_y,
                       float scale_x,
                       float scale_y) {
  const float left = region.x * scale_x;
  const float top = region.y * scale_y;
  const float right = (region.x + region.width) * scale_x;
  const float bottom = (region.y + region.height) * scale_y;
  if (pixel_x < left || pixel_x >= right || pixel_y < top ||
      pixel_y >= bottom) {
    return false;
  }
  if ((region.flags & kBackdropMaskRegionRoundedRect) == 0) {
    return true;
  }

  auto inside_corner = [](float x, float y, float center_x, float center_y,
                          float radius_x, float radius_y) {
    if (radius_x <= 0.0f || radius_y <= 0.0f) {
      return true;
    }
    const float dx = (x - center_x) / radius_x;
    const float dy = (y - center_y) / radius_y;
    return dx * dx + dy * dy <= 1.0f;
  };

  const float tl_rx = region.border_radius_top_left * scale_x;
  const float tl_ry = region.border_radius_top_left * scale_y;
  if (tl_rx > 0.0f && tl_ry > 0.0f && pixel_x < left + tl_rx &&
      pixel_y < top + tl_ry) {
    return inside_corner(pixel_x, pixel_y, left + tl_rx, top + tl_ry, tl_rx,
                         tl_ry);
  }

  const float tr_rx = region.border_radius_top_right * scale_x;
  const float tr_ry = region.border_radius_top_right * scale_y;
  if (tr_rx > 0.0f && tr_ry > 0.0f && pixel_x >= right - tr_rx &&
      pixel_y < top + tr_ry) {
    return inside_corner(pixel_x, pixel_y, right - tr_rx, top + tr_ry, tr_rx,
                         tr_ry);
  }

  const float br_rx = region.border_radius_bottom_right * scale_x;
  const float br_ry = region.border_radius_bottom_right * scale_y;
  if (br_rx > 0.0f && br_ry > 0.0f && pixel_x >= right - br_rx &&
      pixel_y >= bottom - br_ry) {
    return inside_corner(pixel_x, pixel_y, right - br_rx, bottom - br_ry,
                         br_rx, br_ry);
  }

  const float bl_rx = region.border_radius_bottom_left * scale_x;
  const float bl_ry = region.border_radius_bottom_left * scale_y;
  if (bl_rx > 0.0f && bl_ry > 0.0f && pixel_x < left + bl_rx &&
      pixel_y >= bottom - bl_ry) {
    return inside_corner(pixel_x, pixel_y, left + bl_rx, bottom - bl_ry,
                         bl_rx, bl_ry);
  }
  return true;
}

class BorrowedVulkanImageBacking final
    : public gpu::ClearTrackingSharedImageBacking {
 public:
  BorrowedVulkanImageBacking(const gpu::Mailbox& mailbox,
                             const gpu::SharedImageInfo& si_info,
                             scoped_refptr<gpu::SharedContextState> context_state,
                             const GrBackendTexture& backend_texture)
      : gpu::ClearTrackingSharedImageBacking(
            mailbox,
            si_info,
            static_cast<size_t>(std::max(0, si_info.size.width())) *
                static_cast<size_t>(std::max(0, si_info.size.height())) * 4u,
            /*is_thread_safe=*/false),
        context_state_(std::move(context_state)),
        backend_texture_(backend_texture),
        promise_texture_(GrPromiseImageTexture::Make(backend_texture_)) {}

  ~BorrowedVulkanImageBacking() override {
    DCHECK(!is_write_);
    DCHECK_EQ(read_count_, 0);
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
      scoped_refptr<gpu::SharedContextState> context_state) override {
    if (context_state != context_state_) {
      return nullptr;
    }
    return std::make_unique<SkiaRepresentation>(context_state_->gr_context(),
                                                manager, this, tracker);
  }

 private:
  class SkiaRepresentation final : public gpu::SkiaGaneshImageRepresentation {
   public:
    SkiaRepresentation(GrDirectContext* gr_context,
                       gpu::SharedImageManager* manager,
                       BorrowedVulkanImageBacking* backing,
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
    BorrowedVulkanImageBacking* borrowed_backing() {
      return static_cast<BorrowedVulkanImageBacking*>(backing());
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

}  // namespace

std::string ValidateVulkanPreparationContext(
    ExternalTargetInteropContext& context) {
  if (!context.UsesOffscreenVulkan() || !context.IsOffscreen()) {
    return "borrowed blit target requires offscreen Vulkan output";
  }
  if (!context.GetSharedImageManager()) {
    return "SharedImageManager is unavailable";
  }
  scoped_refptr<gpu::SharedContextState> context_state =
      context.GetSharedContextState();
  if (!context_state || !context_state->GrContextIsVulkan() ||
      !context_state->vk_context_provider() || !context_state->gr_context()) {
    return "offscreen runtime has no Vulkan Ganesh SharedContextState";
  }
  return {};
}

size_t PopulateBackdropMaskRows(uint8_t* dst,
                                size_t row_pitch,
                                const gfx::Size& output_size,
                                const gfx::Size& css_viewport,
                                const std::vector<BackdropMaskRegion>& regions) {
  if (!dst || output_size.IsEmpty() || css_viewport.IsEmpty()) {
    return 0;
  }
  const float scale_x = static_cast<float>(output_size.width()) /
                        static_cast<float>(css_viewport.width());
  const float scale_y = static_cast<float>(output_size.height()) /
                        static_cast<float>(css_viewport.height());
  size_t mask_pixels = 0;
  const size_t encoded_region_count = std::min<size_t>(regions.size(), 255u);
  for (size_t i = 0; i < encoded_region_count; ++i) {
    const BackdropMaskRegion& region = regions[i];
    int left = static_cast<int>(std::floor(region.x * scale_x));
    int top = static_cast<int>(std::floor(region.y * scale_y));
    int right =
        static_cast<int>(std::ceil((region.x + region.width) * scale_x));
    int bottom =
        static_cast<int>(std::ceil((region.y + region.height) * scale_y));
    left = std::clamp(left, 0, output_size.width());
    top = std::clamp(top, 0, output_size.height());
    right = std::clamp(right, 0, output_size.width());
    bottom = std::clamp(bottom, 0, output_size.height());
    if (right <= left || bottom <= top) {
      continue;
    }
    const uint8_t region_id = static_cast<uint8_t>(i + 1u);
    for (int y = top; y < bottom; ++y) {
      uint8_t* row = dst + static_cast<size_t>(y) * row_pitch;
      for (int x = left; x < right; ++x) {
        const float center_x = static_cast<float>(x) + 0.5f;
        const float center_y = static_cast<float>(y) + 0.5f;
        if (!PointInsideRegion(region, center_x, center_y, scale_x, scale_y)) {
          continue;
        }
        uint8_t* pixel = row + static_cast<size_t>(x) * 4u;
        if (pixel[0] == 0 || pixel[1] == 0) {
          ++mask_pixels;
        }
        pixel[0] = region_id;
        pixel[1] = 255;
        pixel[2] = 0;
        pixel[3] = 255;
      }
    }
  }
  return mask_pixels;
}

void DrawBackdropMask(SkCanvas* canvas,
                      const gfx::Size& output_size,
                      const gfx::Size& css_viewport,
                      const std::vector<BackdropMaskRegion>& regions) {
  if (!canvas || output_size.IsEmpty() || css_viewport.IsEmpty()) {
    return;
  }
  const float scale_x = static_cast<float>(output_size.width()) /
                        static_cast<float>(css_viewport.width());
  const float scale_y = static_cast<float>(output_size.height()) /
                        static_cast<float>(css_viewport.height());
  SkPaint paint;
  paint.setStyle(SkPaint::kFill_Style);
  paint.setAntiAlias(true);
  const size_t encoded_region_count = std::min<size_t>(regions.size(), 255u);
  for (size_t i = 0; i < encoded_region_count; ++i) {
    const BackdropMaskRegion& region = regions[i];
    const uint8_t region_id = static_cast<uint8_t>(i + 1u);
    paint.setColor(SkColorSetARGB(255, region_id, 255, 0));
    const SkRect rect = SkRect::MakeXYWH(region.x * scale_x,
                                         region.y * scale_y,
                                         region.width * scale_x,
                                         region.height * scale_y);
    if ((region.flags & kBackdropMaskRegionRoundedRect) != 0) {
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
}

std::unique_ptr<gpu::SharedImageBacking> CreateBorrowedVulkanImageBacking(
    const gpu::Mailbox& mailbox,
    const gpu::SharedImageInfo& si_info,
    scoped_refptr<gpu::SharedContextState> context_state,
    const GrBackendTexture& backend_texture) {
  return std::make_unique<BorrowedVulkanImageBacking>(
      mailbox, si_info, std::move(context_state), backend_texture);
}

std::string ExternalTargetInterop::VerifyBorrowedVulkanTarget() {
  if (!borrowed_vulkan_target_) {
    return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=borrowed "
           "blit target is not prepared path=viz_blit_request "
           "viz_blit_request=1";
  }
  std::string context_failure = ValidateVulkanPreparationContext(context_);
  if (!context_failure.empty()) {
    return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=" +
           context_failure + " path=viz_blit_request viz_blit_request=1";
  }
  gpu::SharedImageManager* manager = context_.GetSharedImageManager();
  scoped_refptr<gpu::SharedContextState> context_state =
      context_.GetSharedContextState();
  auto representation = manager->ProduceSkia(
      borrowed_vulkan_target_->mailbox,
      borrowed_vulkan_target_->registration_tracker, context_state,
      gpu::SharedImageUsageSet(gpu::SHARED_IMAGE_USAGE_DISPLAY_READ));
  if (!representation) {
    return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=borrowed "
           "blit target Skia read representation failed path=viz_blit_request "
           "viz_blit_request=1";
  }
  std::vector<GrBackendSemaphore> begin_semaphores;
  std::vector<GrBackendSemaphore> end_semaphores;
  auto access = representation->BeginScopedReadAccess(&begin_semaphores,
                                                       &end_semaphores);
  if (!access) {
    return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=borrowed "
           "blit target Skia read access failed path=viz_blit_request "
           "viz_blit_request=1";
  }
  sk_sp<SkImage> image = access->CreateSkImage(context_state.get());
  if (!image) {
    return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=borrowed "
           "blit target image creation failed path=viz_blit_request "
           "viz_blit_request=1";
  }
  std::vector<uint32_t> pixels(static_cast<size_t>(borrowed_vulkan_target_->size.width()) *
                               static_cast<size_t>(borrowed_vulkan_target_->size.height()));
  const SkImageInfo info = SkImageInfo::MakeN32Premul(
      borrowed_vulkan_target_->size.width(), borrowed_vulkan_target_->size.height());
  if (!image->readPixels(context_state->gr_context(), info, pixels.data(),
                         static_cast<size_t>(borrowed_vulkan_target_->size.width()) * sizeof(uint32_t), 0, 0)) {
    return "gpu_borrowed_vkimage_render_copy_smoke: failed failure=borrowed "
           "blit target readback failed path=viz_blit_request viz_blit_request=1";
  }
  size_t nontransparent = 0;
  for (uint32_t pixel : pixels) {
    nontransparent += SkColorGetA(pixel) != 0;
  }
  if (nontransparent == 0) {
    return "gpu_borrowed_vkimage_render_copy_smoke: blocked reason=offscreen "
           "Vulkan BlitRequest populated a transparent borrowed target "
           "path=viz_blit_request viz_blit_request=1";
  }
  return "gpu_borrowed_vkimage_render_copy_smoke: ok path=viz_blit_request "
         "viz_blit_request=1 target=" +
         std::to_string(borrowed_vulkan_target_->size.width()) + "x" +
         std::to_string(borrowed_vulkan_target_->size.height()) +
         " format=RGBA_8888 readback=1 ownership=borrowed";
}

std::string ExternalTargetInterop::PrepareBorrowedVulkanTarget(
    const gfx::Size& target_size,
    gpu::VulkanImage* external_image,
    const html_css_renderer::ExternalVulkanImageTarget* external_target,
    scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
  DiscardBorrowedVulkanTarget();
  if (!target_shared_image || target_size.IsEmpty()) {
    return "borrowed blit target output pointer or size is invalid";
  }
  if (std::string error = ValidateVulkanPreparationContext(context_);
      !error.empty()) {
    return error;
  }
  auto context_state = context_.GetSharedContextState();
  auto* device_queue = context_state->vk_context_provider()->GetDeviceQueue();
  if (!device_queue) {
    return "Vulkan context provider has no device queue";
  }
  auto target = std::make_unique<BorrowedVkImageRenderCopyBlitTarget>();
  target->size = target_size;
  gpu::VulkanImage* image = external_image;
  if (external_target) {
    if (!external_target->vk_image || !external_target->vk_device_memory ||
        external_target->width != target_size.width() ||
        external_target->height != target_size.height() ||
        external_target->vk_format != VK_FORMAT_R8G8B8A8_UNORM ||
        external_target->allocation_size == 0) {
      return "raw external Vulkan target metadata is incomplete or does not match the active renderer size/format";
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
    image = target->image.get();
    target->external_resource = true;
  } else if (external_image) {
    image = external_image;
    target->external_image = external_image;
    target->external_resource = true;
  } else {
    target->image = gpu::VulkanImage::Create(
        device_queue, target_size, VK_FORMAT_R8G8B8A8_UNORM,
        VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
            VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT);
    image = target->image.get();
  }
  if (!image || image->image() == VK_NULL_HANDLE) {
    return "raw external Vulkan target wrapper creation failed";
  }
  const auto format = viz::SinglePlaneFormat::kRGBA_8888;
  const auto color_space = gfx::ColorSpace::CreateSRGB();
  const GrBackendTexture backend_texture = GrBackendTextures::MakeVk(
      target_size.width(), target_size.height(),
      gpu::CreateGrVkImageInfo(image, format, color_space));
  if (!backend_texture.isValid()) {
    return "Skia backend texture wrapping failed";
  }
  target->mailbox = gpu::Mailbox::Generate();
  const gpu::SharedImageUsageSet usage = gpu::SHARED_IMAGE_USAGE_DISPLAY_READ |
                                         gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE;
  gpu::SharedImageInfo info(format, target_size, color_space,
                            kTopLeft_GrSurfaceOrigin, kPremul_SkAlphaType,
                            usage, "StandaloneBorrowedVkImageBlitTargetSmoke");
  target->registration_tracker = context_state->memory_type_tracker();
  target->factory_ref = context_.GetSharedImageManager()->Register(
      CreateBorrowedVulkanImageBacking(target->mailbox, info, context_state,
                                       backend_texture),
      target->registration_tracker);
  if (!target->factory_ref) return "borrowed blit target registration failed";
  gpu::SharedImageMetadata metadata{format, target_size, color_space,
                                    kTopLeft_GrSurfaceOrigin,
                                    kPremul_SkAlphaType, usage};
  target->client_shared_image = gpu::ClientSharedImage::CreateForTesting(
      target->mailbox, metadata, gpu::SyncToken(), 3553u, false);
  if (!target->client_shared_image) return "borrowed blit target ClientSharedImage failed";
  target->target_created = target->backend_texture_valid = target->registered = true;
  *target_shared_image = target->client_shared_image;
  borrowed_vulkan_target_ = std::move(target);
  return {};
}

std::string ExternalTargetInterop::RenderBorrowedVulkanBackdropMask(
    const gfx::Size& output_size,
    const gfx::Size& css_viewport,
    const std::vector<BackdropMaskRegion>& regions) {
  if (!borrowed_vulkan_target_ || !borrowed_vulkan_target_->image ||
      output_size.IsEmpty() || css_viewport.IsEmpty() || regions.empty()) {
    return "gpu_external_vkimage_backdrop_mask: failed failure=prepared Vulkan mask target or regions unavailable";
  }
  auto context_state = context_.GetSharedContextState();
  if (!context_state || !context_state->gr_context()) {
    return "gpu_external_vkimage_backdrop_mask: failed failure=offscreen runtime has no Vulkan Ganesh SharedContextState";
  }
  const auto format = viz::SinglePlaneFormat::kRGBA_8888;
  const auto color_space = gfx::ColorSpace::CreateSRGB();
  const GrBackendTexture texture = GrBackendTextures::MakeVk(
      output_size.width(), output_size.height(),
      gpu::CreateGrVkImageInfo(borrowed_vulkan_target_->image.get(), format,
                               color_space));
  sk_sp<SkSurface> surface = SkSurfaces::WrapBackendTexture(
      context_state->gr_context(), texture, kTopLeft_GrSurfaceOrigin, 1,
      kRGBA_8888_SkColorType, color_space.ToSkColorSpace(), nullptr);
  if (!surface) {
    return "gpu_external_vkimage_backdrop_mask: failed failure=backdrop mask SkSurface wrapping failed";
  }
  surface->getCanvas()->clear(SkColors::kTransparent);
  DrawBackdropMask(surface->getCanvas(), output_size, css_viewport, regions);
  context_state->gr_context()->flush(surface.get());
  if (!context_state->gr_context()->submit()) {
    return "gpu_external_vkimage_backdrop_mask: failed failure=backdrop mask Skia submit failed";
  }
  return "gpu_external_vkimage_backdrop_mask: ok encoding=rgba8_id_coverage ownership=borrowed";
}

ExternalTargetInterop::VulkanReleaseResult
ExternalTargetInterop::DiscardBorrowedVulkanTarget() {
  VulkanReleaseResult result;
  if (!borrowed_vulkan_target_) {
    return result;
  }
  borrowed_vulkan_target_->client_shared_image.reset();
  if (borrowed_vulkan_target_->factory_ref) {
    borrowed_vulkan_target_->factory_ref.reset();
    result.backing_released = true;
  }
  if (borrowed_vulkan_target_->image) {
    borrowed_vulkan_target_->image->Destroy();
    if (!borrowed_vulkan_target_->external_resource) {
      result.target_destroyed = true;
    }
  }
  borrowed_vulkan_target_.reset();
  return result;
}

#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
namespace {
bool SameD3D12DeviceForInterop(ID3D12Device* a, ID3D12Device* b) {
  if (!a || !b) return false;
  Microsoft::WRL::ComPtr<IUnknown> a_identity;
  Microsoft::WRL::ComPtr<IUnknown> b_identity;
  return SUCCEEDED(a->QueryInterface(IID_PPV_ARGS(&a_identity))) &&
         SUCCEEDED(b->QueryInterface(IID_PPV_ARGS(&b_identity))) &&
         a_identity.Get() == b_identity.Get();
}
}  // namespace

ExternalTargetInterop::D3D12ReleaseResult
ExternalTargetInterop::DiscardBorrowedD3D12Target() {
  D3D12ReleaseResult result;
  if (!borrowed_d3d12_target_) {
    return result;
  }
  borrowed_d3d12_target_->client_shared_image.reset();
  borrowed_d3d12_target_->backing = nullptr;
  if (borrowed_d3d12_target_->factory_ref) {
    borrowed_d3d12_target_->factory_ref.reset();
    result.backing_released = true;
  }
  if (borrowed_d3d12_target_->resource) {
    const bool external_resource = borrowed_d3d12_target_->external_resource;
    borrowed_d3d12_target_->resource.Reset();
    result.target_destroyed = !external_resource;
  }
  borrowed_d3d12_target_.reset();
  return result;
}

ExternalTargetInterop::D3D12VerificationResult
ExternalTargetInterop::VerifyBorrowedD3D12Target() {
  D3D12VerificationResult result;
  if (!borrowed_d3d12_target_ || !borrowed_d3d12_target_->backing) {
    result.failure = "borrowed D3D12 target is not prepared";
    return result;
  }
  result.prepared = true;
  result.width = borrowed_d3d12_target_->size.width();
  result.height = borrowed_d3d12_target_->size.height();
  result.shared_texture_memory =
      borrowed_d3d12_target_->backing->shared_texture_memory_created();
  std::vector<uint32_t> pixels;
  if (!borrowed_d3d12_target_->backing->ReadbackToPixels(&pixels)) {
    result.failure = "borrowed D3D12 target readback failed";
    return result;
  }
  if (result.width <= 0 || result.height <= 0 ||
      pixels.size() != static_cast<size_t>(result.width) * result.height) {
    result.failure = "borrowed D3D12 readback dimensions invalid";
    return result;
  }
  for (uint32_t pixel : pixels) {
    if (SkColorGetA(pixel) != 0) {
      result.nontransparent = true;
      break;
    }
  }
  if (!result.nontransparent) {
    result.failure = "offscreen D3D12 BlitRequest populated a transparent target";
    return result;
  }
  result.readback_verified = true;
  return result;
}

ExternalTargetInterop::D3D12PreparationResult
ExternalTargetInterop::PrepareBorrowedD3D12Target(
    const gfx::Size& target_size,
    ID3D12Resource* external_resource,
    void* shared_handle,
    scoped_refptr<gpu::ClientSharedImage>* target_shared_image) {
  D3D12PreparationResult result;
  DiscardBorrowedD3D12Target();
  if (!target_shared_image || !context_.UsesOffscreenD3D12() || !context_.IsOffscreen() ||
      target_size.IsEmpty()) {
    result.failure = "borrowed D3D12 target requires offscreen D3D12 output";
    return result;
  }
  auto context_state = context_.GetSharedContextState();
  if (!context_state || !context_state->dawn_context_provider() ||
      context_state->dawn_context_provider()->backend_type() !=
          wgpu::BackendType::D3D12) {
    result.failure = "offscreen runtime has no D3D12 Graphite/Dawn SharedContextState";
    return result;
  }
  auto queue = context_state->dawn_context_provider()->GetD3D12CommandQueue();
  Microsoft::WRL::ComPtr<ID3D12Device> device;
  if (!queue || FAILED(queue->GetDevice(IID_PPV_ARGS(&device))) || !device) {
    result.failure = "Dawn D3D12 device is unavailable";
    return result;
  }
  auto target = std::make_unique<BorrowedD3D12RenderCopyBlitTarget>();
  target->size = target_size;
  Microsoft::WRL::ComPtr<ID3D12Resource> opened;
  Microsoft::WRL::ComPtr<ID3D12Device> resource_device;
  const bool direct = external_resource &&
      SUCCEEDED(external_resource->GetDevice(IID_PPV_ARGS(&resource_device))) &&
      SameD3D12DeviceForInterop(resource_device.Get(), device.Get());
  if (shared_handle && !direct) {
    if (shared_handle == cached_external_d3d12_shared_handle_ &&
        cached_external_d3d12_opened_resource_) {
      opened = cached_external_d3d12_opened_resource_;
    } else if (FAILED(device->OpenSharedHandle(static_cast<HANDLE>(shared_handle),
                                                 IID_PPV_ARGS(&opened))) || !opened) {
      result.failure = "borrowed external D3D12 shared handle open failed";
      return result;
    }
    cached_external_d3d12_shared_handle_ = shared_handle;
    cached_external_d3d12_resource_hint_ = external_resource;
    cached_external_d3d12_opened_resource_ = opened;
    external_resource = opened.Get();
  }
  if (external_resource) {
    const D3D12_RESOURCE_DESC desc = external_resource->GetDesc();
    if (desc.Dimension != D3D12_RESOURCE_DIMENSION_TEXTURE2D ||
        desc.Width != static_cast<UINT64>(target_size.width()) ||
        desc.Height != static_cast<UINT>(target_size.height()) ||
        desc.Format != DXGI_FORMAT_R8G8B8A8_UNORM) {
      result.failure = "borrowed external D3D12 target resource metadata mismatch";
      return result;
    }
    target->resource = opened ? opened : external_resource;
    target->external_resource = true;
  } else {
    D3D12_HEAP_PROPERTIES heap = {};
    heap.Type = D3D12_HEAP_TYPE_DEFAULT;
    D3D12_RESOURCE_DESC desc = {};
    desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    desc.Width = target_size.width(); desc.Height = target_size.height();
    desc.DepthOrArraySize = 1; desc.MipLevels = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; desc.SampleDesc.Count = 1;
    desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET |
                 D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
    if (FAILED(device->CreateCommittedResource(&heap, D3D12_HEAP_FLAG_NONE,
        &desc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&target->resource))) ||
        !target->resource) {
      result.failure = "stand-in D3D12 target resource creation failed";
      return result;
    }
  }
  const viz::SharedImageFormat format = viz::SinglePlaneFormat::kRGBA_8888;
  const gfx::ColorSpace color_space = gfx::ColorSpace::CreateSRGB();
  const gpu::SharedImageUsageSet usage = gpu::SHARED_IMAGE_USAGE_DISPLAY_READ |
                                         gpu::SHARED_IMAGE_USAGE_DISPLAY_WRITE;
  gpu::SharedImageInfo info(format, target_size, color_space,
                            kTopLeft_GrSurfaceOrigin, kPremul_SkAlphaType,
                            usage, "StandaloneBorrowedD3D12BlitTargetSmoke");
  target->mailbox = gpu::Mailbox::Generate();
  target->registration_tracker = context_state->memory_type_tracker();
  auto backing = std::make_unique<BorrowedD3D12TextureBacking>(
      target->mailbox, info, context_state, target->resource);
  target->backing = backing.get();
  target->factory_ref = context_.GetSharedImageManager()->Register(
      std::move(backing), target->registration_tracker);
  if (!target->factory_ref) {
    result.failure = "borrowed D3D12 target registration failed";
    return result;
  }
  gpu::SharedImageMetadata metadata;
  metadata.format = format;
  metadata.size = target_size;
  metadata.color_space = color_space;
  metadata.surface_origin = kTopLeft_GrSurfaceOrigin;
  metadata.alpha_type = kPremul_SkAlphaType;
  metadata.usage = usage;
  target->client_shared_image = gpu::ClientSharedImage::CreateForTesting(
      target->mailbox, metadata, gpu::SyncToken(), 3553u, false);
  if (!target->client_shared_image) {
    target->factory_ref.reset();
    result.failure = "borrowed D3D12 target ClientSharedImage failed";
    return result;
  }
  target->registered = true;
  target->target_created = true;
  *target_shared_image = target->client_shared_image;
  borrowed_d3d12_target_ = std::move(target);
  result.prepared = true;
  return result;
}

std::string ExternalTargetInterop::RenderBorrowedD3D12BackdropMask(
    const gfx::Size& output_size,
    const gfx::Size& css_viewport,
    const std::vector<BackdropMaskRegion>& regions) {
  if (!borrowed_d3d12_target_ || !borrowed_d3d12_target_->resource ||
      output_size.IsEmpty() || css_viewport.IsEmpty() || regions.empty()) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=prepared D3D12 mask target or regions unavailable";
  }
  const size_t row_pitch = static_cast<size_t>(output_size.width()) * 4u;
  std::vector<uint8_t> mask_bytes(
      row_pitch * static_cast<size_t>(output_size.height()), 0);
  const size_t mask_pixels = PopulateBackdropMaskRows(
      mask_bytes.data(), row_pitch, output_size, css_viewport, regions);
  auto context_state = context_.GetSharedContextState();
  if (!context_state || !context_state->dawn_context_provider()) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=offscreen runtime has no D3D12 Graphite/Dawn SharedContextState";
  }
  Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue =
      context_state->dawn_context_provider()->GetD3D12CommandQueue();
  Microsoft::WRL::ComPtr<ID3D12Device> device;
  if (!queue || FAILED(queue->GetDevice(IID_PPV_ARGS(&device))) || !device) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=Dawn D3D12 device is unavailable";
  }
  const D3D12_RESOURCE_DESC texture_desc =
      borrowed_d3d12_target_->resource->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
  UINT row_count = 0;
  UINT64 row_size_bytes = 0;
  UINT64 total_bytes = 0;
  device->GetCopyableFootprints(&texture_desc, 0, 1, 0, &footprint,
                                &row_count, &row_size_bytes, &total_bytes);
  if (!row_count || !row_size_bytes || !total_bytes) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask upload footprint invalid";
  }
  D3D12_HEAP_PROPERTIES upload_heap = {};
  upload_heap.Type = D3D12_HEAP_TYPE_UPLOAD;
  D3D12_RESOURCE_DESC upload_desc = {};
  upload_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
  upload_desc.Width = total_bytes;
  upload_desc.Height = 1;
  upload_desc.DepthOrArraySize = 1;
  upload_desc.MipLevels = 1;
  upload_desc.SampleDesc.Count = 1;
  upload_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  Microsoft::WRL::ComPtr<ID3D12Resource> upload;
  if (FAILED(device->CreateCommittedResource(
          &upload_heap, D3D12_HEAP_FLAG_NONE, &upload_desc,
          D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&upload))) ||
      !upload) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask upload resource creation failed";
  }
  D3D12_HEAP_PROPERTIES readback_heap = {};
  readback_heap.Type = D3D12_HEAP_TYPE_READBACK;
  Microsoft::WRL::ComPtr<ID3D12Resource> readback;
  if (FAILED(device->CreateCommittedResource(
          &readback_heap, D3D12_HEAP_FLAG_NONE, &upload_desc,
          D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback))) ||
      !readback) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask readback resource creation failed";
  }
  void* mapped = nullptr;
  D3D12_RANGE empty_read_range = {0, 0};
  if (FAILED(upload->Map(0, &empty_read_range, &mapped)) || !mapped) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask upload map failed";
  }
  std::memset(mapped, 0, static_cast<size_t>(total_bytes));
  for (int y = 0; y < output_size.height(); ++y) {
    std::memcpy(static_cast<uint8_t*>(mapped) + footprint.Offset +
                    static_cast<size_t>(y) * footprint.Footprint.RowPitch,
                mask_bytes.data() + static_cast<size_t>(y) * row_pitch,
                row_pitch);
  }
  D3D12_RANGE written_range = {0, static_cast<SIZE_T>(total_bytes)};
  upload->Unmap(0, &written_range);
  Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
  Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
  if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                             IID_PPV_ARGS(&allocator))) ||
      FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                       allocator.Get(), nullptr,
                                       IID_PPV_ARGS(&command_list))) ||
      !command_list) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask command list creation failed";
  }
  D3D12_RESOURCE_BARRIER to_copy_dest = {};
  to_copy_dest.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  to_copy_dest.Transition.pResource = borrowed_d3d12_target_->resource.Get();
  to_copy_dest.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  to_copy_dest.Transition.StateBefore = D3D12_RESOURCE_STATE_COMMON;
  to_copy_dest.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_DEST;
  command_list->ResourceBarrier(1, &to_copy_dest);
  D3D12_TEXTURE_COPY_LOCATION upload_source = {};
  upload_source.pResource = upload.Get();
  upload_source.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
  upload_source.PlacedFootprint = footprint;
  D3D12_TEXTURE_COPY_LOCATION target_destination = {};
  target_destination.pResource = borrowed_d3d12_target_->resource.Get();
  target_destination.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
  command_list->CopyTextureRegion(&target_destination, 0, 0, 0,
                                  &upload_source, nullptr);
  D3D12_RESOURCE_BARRIER to_copy_source = to_copy_dest;
  to_copy_source.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
  to_copy_source.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE;
  command_list->ResourceBarrier(1, &to_copy_source);
  D3D12_TEXTURE_COPY_LOCATION readback_destination = {};
  readback_destination.pResource = readback.Get();
  readback_destination.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
  readback_destination.PlacedFootprint = footprint;
  D3D12_TEXTURE_COPY_LOCATION target_source = {};
  target_source.pResource = borrowed_d3d12_target_->resource.Get();
  target_source.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
  command_list->CopyTextureRegion(&readback_destination, 0, 0, 0,
                                  &target_source, nullptr);
  if (FAILED(command_list->Close())) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask command list close failed";
  }
  ID3D12CommandList* command_lists[] = {command_list.Get()};
  queue->ExecuteCommandLists(1, command_lists);
  Microsoft::WRL::ComPtr<ID3D12Fence> fence;
  if (FAILED(device->CreateFence(0, D3D12_FENCE_FLAG_NONE,
                                 IID_PPV_ARGS(&fence))) || !fence) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask fence creation failed";
  }
  HANDLE event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
  if (!event_handle || FAILED(queue->Signal(fence.Get(), 1))) {
    if (event_handle) ::CloseHandle(event_handle);
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask queue signal failed";
  }
  if (fence->GetCompletedValue() < 1 &&
      (FAILED(fence->SetEventOnCompletion(1, event_handle)) ||
       ::WaitForSingleObject(event_handle, 5000) != WAIT_OBJECT_0)) {
    ::CloseHandle(event_handle);
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask fence wait failed";
  }
  ::CloseHandle(event_handle);
  if (fence->GetCompletedValue() < 1) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask fence wait timed out";
  }
  void* readback_mapped = nullptr;
  D3D12_RANGE read_range = {0, static_cast<SIZE_T>(total_bytes)};
  if (FAILED(readback->Map(0, &read_range, &readback_mapped)) || !readback_mapped) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 mask readback map failed";
  }
  std::array<bool, 256> readback_ids = {};
  size_t readback_mask_pixels = 0;
  const uint8_t* readback_bytes = static_cast<const uint8_t*>(readback_mapped);
  for (int y = 0; y < output_size.height(); ++y) {
    const uint8_t* row = readback_bytes + footprint.Offset +
        static_cast<size_t>(y) * footprint.Footprint.RowPitch;
    for (int x = 0; x < output_size.width(); ++x) {
      const uint8_t* pixel = row + static_cast<size_t>(x) * 4u;
      if (pixel[0] && pixel[1]) {
        ++readback_mask_pixels;
        readback_ids[pixel[0]] = true;
      }
    }
  }
  D3D12_RANGE no_written_range = {0, 0};
  readback->Unmap(0, &no_written_range);
  size_t readback_distinct_ids = 0;
  for (bool seen : readback_ids) readback_distinct_ids += seen;
  if (!readback_mask_pixels || !readback_distinct_ids) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 backdrop mask target remained empty";
  }
  return "gpu_external_d3d12_backdrop_mask: ok encoding=rgba8_id_coverage "
         "mask_pixels=" + std::to_string(readback_mask_pixels) +
         " distinct_ids=" + std::to_string(readback_distinct_ids) +
         " ownership=borrowed";
  std::array<bool, 256> ids = {};
  for (size_t offset = 0; offset + 3 < mask_bytes.size(); offset += 4) {
    if (mask_bytes[offset] && mask_bytes[offset + 1]) {
      ids[mask_bytes[offset]] = true;
    }
  }
  size_t distinct_ids = 0;
  for (bool seen : ids) distinct_ids += seen;
  if (!mask_pixels || !distinct_ids) {
    return "gpu_external_d3d12_backdrop_mask: failed failure=D3D12 rounded backdrop mask encoded no pixels";
  }
  return "gpu_external_d3d12_backdrop_mask: ok encoding=rgba8_id_coverage "
         "mask_pixels=" + std::to_string(mask_pixels) +
         " distinct_ids=" + std::to_string(distinct_ids) +
         " ownership=borrowed";
}
#endif

}  // namespace html_css_renderer::standalone_interop
