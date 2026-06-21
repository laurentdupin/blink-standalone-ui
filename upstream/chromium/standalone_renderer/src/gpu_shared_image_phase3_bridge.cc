// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gpu/command_buffer/client/client_shared_image.h"

#include <optional>
#include <string>
#include <utility>

#include "base/containers/span.h"
#include "base/functional/callback.h"
#include "base/memory/scoped_refptr.h"
#include "components/viz/common/gpu/raster_context_provider.h"
#include "gpu/command_buffer/client/shared_image_interface.h"
#include "gpu/command_buffer/client/shared_image_pool.h"
#include "third_party/blink/renderer/platform/graphics/mailbox_ref.h"
#include "third_party/blink/renderer/platform/graphics/mailbox_texture_backing.h"
#include "third_party/skia/include/core/SkImage.h"
#include "third_party/skia/include/core/SkPixmap.h"
#include "ui/gfx/buffer_types.h"
#include "ui/gfx/geometry/size.h"

namespace gpu {

// Phase 3 compile boundary only. These definitions satisfy shared-image value
// ownership needed by cc/Viz transfer-resource serialization; they must not
// create usable GPU resources before the real GPU/Vulkan path is imported.

SharedImageExportResult::SharedImageExportResult() = default;
SharedImageExportResult::~SharedImageExportResult() = default;
SharedImageExportResult::SharedImageExportResult(SharedImageExportResult&&) =
    default;
SharedImageExportResult& SharedImageExportResult::operator=(
    SharedImageExportResult&&) = default;
SharedImageExportResult::SharedImageExportResult(const SyncToken& sync_token)
    : sync_tokens_({sync_token}) {}
SharedImageExportResult::SharedImageExportResult(
    std::vector<SyncToken> sync_tokens)
    : sync_tokens_(std::move(sync_tokens)) {}

bool SharedImageExportResult::HasData() const {
  return !sync_tokens_.empty();
}

std::string SharedImageExportResult::ToDebugString() const {
  std::string result;
  for (const auto& token : sync_tokens_) {
    if (!result.empty()) {
      result += ", ";
    }
    result += token.ToDebugString();
  }
  return result;
}

ExportedSharedImage::ExportedSharedImage() = default;
ExportedSharedImage::~ExportedSharedImage() = default;
ExportedSharedImage::ExportedSharedImage(ExportedSharedImage&&) = default;
ExportedSharedImage& ExportedSharedImage::operator=(ExportedSharedImage&&) =
    default;
ExportedSharedImage::ExportedSharedImage(
    const Mailbox& mailbox,
    const SharedImageMetadata& metadata,
    const SyncToken& sync_token,
    std::string debug_label,
    std::optional<gfx::GpuMemoryBufferHandle> buffer_handle,
    std::optional<gfx::BufferUsage> buffer_usage,
    uint32_t texture_target,
    bool is_software)
    : mailbox_(mailbox),
      metadata_(metadata),
      creation_sync_token_(sync_token),
      debug_label_(std::move(debug_label)),
      buffer_handle_(std::move(buffer_handle)),
      buffer_usage_(buffer_usage),
      texture_target_(texture_target),
      is_software_(is_software) {}

ExportedSharedImage ExportedSharedImage::Clone() const {
  std::optional<gfx::GpuMemoryBufferHandle> handle;
  if (buffer_handle_.has_value()) {
    handle = buffer_handle_->Clone();
  }
  return ExportedSharedImage(mailbox_, metadata_, creation_sync_token_,
                             debug_label_, std::move(handle), buffer_usage_,
                             texture_target_, is_software_);
}

ClientSharedImage::ClientSharedImage(ExportedSharedImage exported_si)
    : mailbox_(exported_si.mailbox_),
      metadata_(exported_si.metadata_),
      debug_label_(exported_si.debug_label_),
      creation_sync_token_(exported_si.creation_sync_token_),
      buffer_usage_(exported_si.buffer_usage_),
      texture_target_(exported_si.texture_target_),
      is_software_(exported_si.is_software_) {}

ClientSharedImage::ClientSharedImage(const Mailbox& mailbox,
                                     const SharedImageInfo& info)
    : mailbox_(mailbox), metadata_(info), debug_label_(info.debug_label) {}

ClientSharedImage::~ClientSharedImage() = default;

ClientSharedImage::ScopedMapping::ScopedMapping(const gfx::Size& size,
                                                viz::SharedImageFormat format)
    : size_(size), format_(format) {}

ClientSharedImage::ScopedMapping::~ScopedMapping() = default;

base::span<uint8_t> ClientSharedImage::ScopedMapping::GetMemoryForPlane(
    const uint32_t plane_index) {
  return {};
}

SkPixmap ClientSharedImage::ScopedMapping::GetSkPixmapForPlane(
    const uint32_t plane_index,
    SkImageInfo sk_image_info) {
  return {};
}

size_t ClientSharedImage::ScopedMapping::Stride(const uint32_t plane_index) {
  return 0;
}

gfx::Size ClientSharedImage::ScopedMapping::Size() {
  return size_;
}

bool ClientSharedImage::ScopedMapping::IsSharedMemory() {
  return false;
}

std::unique_ptr<ClientSharedImage::ScopedMapping> ClientSharedImage::Map() {
  return nullptr;
}

std::unique_ptr<RasterScopedAccess> ClientSharedImage::BeginRasterAccess(
    InterfaceBase*,
    const SyncToken&,
    bool) {
  return nullptr;
}

std::unique_ptr<RasterScopedAccess>
ClientSharedImage::BeginGLAccessForCopySharedImage(InterfaceBase*,
                                                   const SyncToken&,
                                                   bool) {
  return nullptr;
}

void ClientSharedImage::MapAsync(
    base::OnceCallback<void(std::unique_ptr<ScopedMapping>)> result_cb) {
  std::move(result_cb).Run(nullptr);
}

ExportedSharedImage ClientSharedImage::Export(bool with_buffer_handle) {
  // Phase 3 owns real buffer export. Keep Phase 1 fail-closed even if callers
  // request a buffer handle.
  std::optional<gfx::GpuMemoryBufferHandle> buffer_handle;
  return ExportedSharedImage(mailbox_, metadata_, creation_sync_token_,
                             debug_label_, std::move(buffer_handle),
                             buffer_usage_, texture_target_, is_software_);
}

scoped_refptr<ClientSharedImage> ClientSharedImage::ImportUnowned(
    ExportedSharedImage exported_shared_image) {
  return base::WrapRefCounted(
      new ClientSharedImage(std::move(exported_shared_image)));
}

scoped_refptr<ClientSharedImage> ClientSharedImage::CreateForTesting(
    const SharedImageMetadata& metadata,
    uint32_t texture_target) {
  // Phase 3 owns real shared-image creation. This test hook is reachable from
  // cc::ResourcePool but must not manufacture a usable GPU resource in Phase 1.
  return nullptr;
}

scoped_refptr<ClientSharedImage> ClientSharedImage::MakeUnowned() {
  return ClientSharedImage::ImportUnowned(Export());
}

uint32_t ClientSharedImage::GetTextureTarget() {
  return texture_target_;
}

gpu::SyncToken ClientSharedImage::BackingWasExternallyUpdated(
    const gpu::SyncToken& sync_token) {
  return sync_token;
}

gfx::GpuMemoryBufferType ClientSharedImage::GetGpuMemoryBufferType() const {
  return gfx::EMPTY_BUFFER;
}

bool ClientSharedImage::SupportsZeroCopyWebGPUImport() const {
  return false;
}

gfx::GpuMemoryBufferHandle ClientSharedImage::CloneGpuMemoryBufferHandle()
    const {
  return {};
}

void ClientSharedImage::OnMemoryDump(
    base::trace_event::ProcessMemoryDump* pmd,
    const base::trace_event::MemoryAllocatorDumpGuid& buffer_dump_guid,
    int importance) {}

std::unique_ptr<SharedImageTexture> ClientSharedImage::CreateGLTexture(
    gles2::GLES2Interface*) {
  return nullptr;
}

SharedImageTexture::ScopedAccess::~ScopedAccess() = default;

SyncToken SharedImageTexture::ScopedAccess::EndAccess(
    std::unique_ptr<ScopedAccess>) {
  return SyncToken();
}

SharedImageTexture::~SharedImageTexture() = default;

std::unique_ptr<SharedImageTexture::ScopedAccess>
SharedImageTexture::BeginAccess(const SyncToken&, bool) {
  return nullptr;
}

void SharedImageTexture::DidEndAccess(bool) {}

SyncToken RasterScopedAccess::EndAccess(
    std::unique_ptr<RasterScopedAccess>) {
  return SyncToken();
}

ClientImage::ClientImage(scoped_refptr<ClientSharedImage> shared_image)
    : shared_image_(std::move(shared_image)) {
  if (shared_image_) {
    sync_token_ = shared_image_->creation_sync_token();
  }
}

ClientImage::~ClientImage() = default;

const scoped_refptr<ClientSharedImage>& ClientImage::GetSharedImage() const {
  return shared_image_;
}

const SyncToken& ClientImage::GetSyncToken() const {
  return sync_token_;
}

void ClientImage::SetReleaseSyncToken(SyncToken release_sync_token) {
  sync_token_ = std::move(release_sync_token);
}

const SharedImagePoolId& ClientImage::GetPoolIdForTesting() const {
  return pool_id_;
}

void ClientImage::OnMemoryDump(base::trace_event::ProcessMemoryDump*,
                               const std::string&) const {}

SharedImagePoolBase::SharedImagePoolBase(
    const SharedImagePoolId& pool_id,
    const ImageInfo& image_info,
    std::string_view debug_label,
    const scoped_refptr<SharedImageInterface> sii,
    std::optional<uint8_t> max_pool_size,
    std::optional<base::TimeDelta> unused_resource_expiration_time)
    : pool_id_(pool_id),
      image_info_(image_info),
      debug_label_(debug_label),
      sii_(sii),
      max_pool_size_(max_pool_size),
      unused_resource_expiration_time_(unused_resource_expiration_time) {}

SharedImagePoolBase::~SharedImagePoolBase() {
  ClearInternal();
}

size_t SharedImagePoolBase::GetPoolSizeForTesting() const {
  return image_pool_.size();
}

bool SharedImagePoolBase::IsReclaimTimerRunningForTesting() const {
  return false;
}

scoped_refptr<ClientSharedImage>
SharedImagePoolBase::CreateSharedImageInternal() {
  return nullptr;
}

scoped_refptr<ClientImage> SharedImagePoolBase::GetImageFromPoolInternal() {
  return nullptr;
}

void SharedImagePoolBase::ReleaseImageInternal(scoped_refptr<ClientImage>) {}

void SharedImagePoolBase::ClearInternal() {
  image_pool_.clear();
}

void SharedImagePoolBase::ReconfigureInternal(const ImageInfo& image_info) {
  image_info_ = image_info;
  ClearInternal();
}

void SharedImagePoolBase::MaybePostUnusedResourcesReclaimTask() {}

void SharedImagePoolBase::ClearOldUnusedResources() {
  ClearInternal();
}

}  // namespace gpu

namespace blink {

MailboxRef::MailboxRef(
    const gpu::SyncToken& sync_token,
    base::PlatformThreadRef context_thread_ref,
    scoped_refptr<base::SingleThreadTaskRunner> context_task_runner,
    viz::ReleaseCallback release_callback)
    : sync_token_(sync_token),
      context_thread_ref_(context_thread_ref),
      context_task_runner_(std::move(context_task_runner)),
      release_callback_(std::move(release_callback)) {}

MailboxRef::~MailboxRef() = default;

MailboxTextureBacking::MailboxTextureBacking(
    scoped_refptr<gpu::ClientSharedImage> shared_image,
    scoped_refptr<MailboxRef> mailbox_ref,
    SkAlphaType,
    scoped_refptr<viz::RasterContextProvider> context_provider)
    : shared_image_(std::move(shared_image)),
      mailbox_ref_(std::move(mailbox_ref)),
      sk_image_info_(SkImageInfo::MakeUnknown()),
      context_provider_(std::move(context_provider)) {}

MailboxTextureBacking::~MailboxTextureBacking() = default;

const SkImageInfo& MailboxTextureBacking::GetSkImageInfo() {
  return sk_image_info_;
}

gpu::Mailbox MailboxTextureBacking::GetMailbox() const {
  return shared_image_ ? shared_image_->mailbox() : gpu::Mailbox();
}

sk_sp<SkImage> MailboxTextureBacking::GetSkImageViaReadback() {
  return nullptr;
}

bool MailboxTextureBacking::readPixels(const SkImageInfo&,
                                       void*,
                                       size_t,
                                       int,
                                       int) {
  return false;
}

}  // namespace blink
