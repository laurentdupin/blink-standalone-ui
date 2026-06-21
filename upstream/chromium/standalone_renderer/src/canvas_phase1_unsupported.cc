// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 keeps CPU Canvas 2D and layout integration active, but GPU-backed
// canvas dispatch, offscreen canvas worker plumbing, WebGL/WebGPU context
// access, surface embedding, and canvas metrics upload are out of scope.

#include <utility>

#include "third_party/blink/renderer/core/html/canvas/canvas_font_cache.h"
#include "third_party/blink/renderer/core/html/canvas/canvas_rendering_context.h"
#include "third_party/blink/renderer/core/html/canvas/predefined_color_space.h"
#include "cc/layers/solid_color_layer.h"
#include "cc/layers/surface_layer.h"
#include "third_party/blink/renderer/platform/graphics/canvas_resource_dispatcher.h"
#include "third_party/blink/renderer/platform/graphics/exported_canvas_resource.h"
#include "third_party/blink/renderer/platform/graphics/gpu/shared_context_rate_limiter.h"
#include "third_party/blink/renderer/platform/graphics/gpu/shared_gpu_context.h"
#include "third_party/blink/renderer/platform/graphics/gpu/canvas_utils.h"
#include "third_party/blink/renderer/platform/graphics/image.h"
#include "third_party/blink/renderer/platform/graphics/offscreen_canvas_placeholder.h"
#include "third_party/blink/renderer/platform/graphics/scoped_raster_timer.h"
#include "third_party/blink/renderer/platform/graphics/surface_layer_bridge.h"
#include "third_party/blink/renderer/platform/graphics/web_graphics_context_3d_provider_wrapper.h"
#include "cc/tiles/software_image_decode_cache.h"

namespace blink {

CanvasRenderingContext::CanvasRenderingAPI
CanvasRenderingContext::RenderingAPIFromId(const String& id) {
  if (id == "2d") {
    return CanvasRenderingAPI::k2D;
  }
  return CanvasRenderingAPI::kUnknown;
}

void CanvasRenderingContext::MaybeRecordUKMCanvasAccessibility() {}
void CanvasRenderingContext::RecordUKMCanvasRenderingAPI() {}
void CanvasRenderingContext::RecordUMACanvasRenderingAPI() {}
void CanvasRenderingContext::RecordUKMCanvasDrawnToRenderingAPI() {}

void ParseCanvasHighDynamicRangeOptions(
    const CanvasHighDynamicRangeOptions*,
    gfx::HDRMetadata& hdr_metadata) {
  hdr_metadata = gfx::HDRMetadata();
}

unsigned CanvasFontCache::MaxFonts() {
  return 50;
}

bool SharedGpuContext::IsGpuCompositingEnabled() {
  return false;
}

base::WeakPtr<WebGraphicsContext3DProviderWrapper>
SharedGpuContext::ContextProviderWrapper() {
  return {};
}

base::WeakPtr<WebGraphicsContext3DProviderWrapper>
SharedGpuContext::GetExistingContextProviderWrapper() {
  return {};
}

bool SharedGpuContext::IsValidWithoutRestoringForTesting() {
  return false;
}

WebGraphicsSharedImageInterfaceProvider*
SharedGpuContext::SharedImageInterfaceProvider() {
  return nullptr;
}

void SharedGpuContext::SetContextProviderFactoryForTesting(
    ContextProviderFactory) {}

void SharedGpuContext::Reset() {}

cc::ImageDecodeCache& Image::SharedCCDecodeCache(SkColorType color_type) {
  static const size_t kLockedMemoryLimitBytes = 64 * 1024 * 1024;
  if (color_type == kRGBA_F16_SkColorType) {
    static cc::SoftwareImageDecodeCache image_decode_cache(
        kRGBA_F16_SkColorType, kLockedMemoryLimitBytes);
    return image_decode_cache;
  }
  static cc::SoftwareImageDecodeCache image_decode_cache(
      kN32_SkColorType, kLockedMemoryLimitBytes);
  return image_decode_cache;
}

bool IsScanoutSupportedForCanvasWithFormat(
    viz::SharedImageFormat,
    const gpu::Capabilities&) {
  return false;
}

WebGraphicsContext3DProviderWrapper::~WebGraphicsContext3DProviderWrapper() =
    default;

void WebGraphicsContext3DProviderWrapper::AddObserver(DestructionObserver*) {}

void WebGraphicsContext3DProviderWrapper::RemoveObserver(DestructionObserver*) {
}

ScopedRasterTimer::ScopedRasterTimer(gpu::raster::RasterInterface*,
                                     Host& host,
                                     bool)
    : raster_interface_(nullptr), host_(host) {}

ScopedRasterTimer::~ScopedRasterTimer() = default;

void ScopedRasterTimer::Host::CheckGpuTimers(gpu::raster::RasterInterface*) {}

void ScopedRasterTimer::Host::AddGpuTimer(
    std::unique_ptr<ScopedRasterTimer::AsyncGpuRasterTimer>) {}

SharedContextRateLimiter::SharedContextRateLimiter(unsigned max_pending_ticks)
    : max_pending_ticks_(max_pending_ticks), can_use_sync_queries_(false) {}

void SharedContextRateLimiter::Tick() {}
void SharedContextRateLimiter::Reset() {}

OffscreenCanvasPlaceholder::Client::~Client() = default;
OffscreenCanvasPlaceholder::~OffscreenCanvasPlaceholder() = default;

void OffscreenCanvasPlaceholder::SetOffscreenCanvasResource(
    scoped_refptr<ExportedCanvasResource>&&) {}

void OffscreenCanvasPlaceholder::SetClient(
    base::WeakPtr<Client>,
    scoped_refptr<base::SingleThreadTaskRunner>) {}

void OffscreenCanvasPlaceholder::SetSuspendOffscreenCanvasAnimation(
    AnimationState requested_state) {
  current_animation_state_ = requested_state;
}

OffscreenCanvasPlaceholder*
OffscreenCanvasPlaceholder::GetPlaceholderCanvasById(DOMNodeId) {
  return nullptr;
}

void OffscreenCanvasPlaceholder::RegisterPlaceholderCanvas(DOMNodeId) {}
void OffscreenCanvasPlaceholder::UnregisterPlaceholderCanvas() {
  placeholder_id_ = kNoPlaceholderId;
}

bool OffscreenCanvasPlaceholder::PostSetAnimationStateToOffscreenCanvasThread(
    AnimationState) {
  return false;
}

ExportedCanvasResource::ExportedCanvasResource(
    scoped_refptr<CanvasResource> resource)
    : resource_(std::move(resource)) {}

ExportedCanvasResource::~ExportedCanvasResource() = default;

void ExportedCanvasResource::OnPlaceholderReleasedResource(
    scoped_refptr<ExportedCanvasResource>&&) {}

gfx::Size ExportedCanvasResource::Size() const {
  return gfx::Size();
}

bool ExportedCanvasResource::OriginClean() const {
  return false;
}

scoped_refptr<StaticBitmapImage> ExportedCanvasResource::Bitmap() {
  return nullptr;
}

void ExportedCanvasResource::Transfer() {}

void ExportedCanvasResource::EndDisplayCompositorAccess(
    gpu::SharedImageExportResult,
    bool) {}

bool ExportedCanvasResource::PrepareTransferableResource(
    viz::TransferableResource*,
    bool) {
  return false;
}

CanvasResourceDispatcher::~CanvasResourceDispatcher() = default;

void CanvasResourceDispatcher::SetNeedsBeginFrame(bool) {}

void CanvasResourceDispatcher::SetAnimationState(
    OffscreenCanvasPlaceholder::AnimationState animation_state) {
  animation_state_ = animation_state;
}

void CanvasResourceDispatcher::DispatchFrame(scoped_refptr<CanvasResource>&&,
                                             const gfx::Rect&,
                                             bool) {}

void CanvasResourceDispatcher::OnMainThreadReceivedImage() {}

bool CanvasResourceDispatcher::HasTooManyPendingFrames() const {
  return false;
}

void CanvasResourceDispatcher::Reshape(const gfx::Size& size) {
  size_ = size;
}

void CanvasResourceDispatcher::DidReceiveCompositorFrameAck(
    Vector<viz::ReturnedResource>) {}

void CanvasResourceDispatcher::OnBeginFrame(
    const viz::BeginFrameArgs&,
    const HashMap<uint32_t, viz::FrameTimingDetails>&,
    Vector<viz::ReturnedResource>) {}

void CanvasResourceDispatcher::ReclaimResources(
    Vector<viz::ReturnedResource>) {}

void CanvasResourceDispatcher::PostImageToPlaceholder(
    scoped_refptr<ExportedCanvasResource>&&) {}

void CanvasResourceDispatcher::SetFilterQuality(
    cc::PaintFlags::FilterQuality) {}

WebSurfaceLayerBridge::~WebSurfaceLayerBridge() = default;

SurfaceLayerBridge::SurfaceLayerBridge(
    viz::FrameSinkId parent_frame_sink_id,
    WebSurfaceLayerBridgeObserver* observer,
    cc::UpdateSubmissionStateCB update_submission_state_callback)
    : observer_(observer),
      update_submission_state_callback_(
          std::move(update_submission_state_callback)),
      frame_sink_id_(viz::FrameSinkId()),
      parent_frame_sink_id_(parent_frame_sink_id) {}

SurfaceLayerBridge::~SurfaceLayerBridge() = default;

void SurfaceLayerBridge::CreateSolidColorLayer() {}

void SurfaceLayerBridge::BindSurfaceEmbedder(
    mojo::PendingReceiver<mojom::blink::SurfaceEmbedder>) {}

void SurfaceLayerBridge::EmbedSurface(const viz::SurfaceId& surface_id) {
  current_surface_id_ = surface_id;
}

void SurfaceLayerBridge::SetLocalSurfaceId(
    const viz::LocalSurfaceId& local_surface_id) {
  current_surface_id_ = viz::SurfaceId(frame_sink_id_, local_surface_id);
}

void SurfaceLayerBridge::OnOpacityChanged(bool is_opaque) {
  frames_are_opaque_ = is_opaque;
}

cc::Layer* SurfaceLayerBridge::GetCcLayer() const {
  return nullptr;
}

const viz::FrameSinkId& SurfaceLayerBridge::GetFrameSinkId() const {
  return frame_sink_id_;
}

void SurfaceLayerBridge::SetContentsOpaque(bool opaque) {
  embedder_expects_opaque_ = opaque;
}

void SurfaceLayerBridge::CreateSurfaceLayer() {}
void SurfaceLayerBridge::ClearObserver() {
  observer_ = nullptr;
}
void SurfaceLayerBridge::RegisterFrameSinkHierarchy() {}
void SurfaceLayerBridge::UnregisterFrameSinkHierarchy() {}
void SurfaceLayerBridge::ReparentFrameSinkHierarchy(
    const viz::FrameSinkId& new_parent_frame_sink_id) {
  parent_frame_sink_id_ = new_parent_frame_sink_id;
}
void SurfaceLayerBridge::UpdateSurfaceLayerOpacity() {}

}  // namespace blink
