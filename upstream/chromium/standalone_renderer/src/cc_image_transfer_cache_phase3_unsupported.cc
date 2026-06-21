// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cc/paint/image_transfer_cache_entry.h"

#include "base/containers/span.h"
#include "third_party/skia/include/core/SkImage.h"

namespace cc {

// Phase 3 owns GPU/Ganesh image transfer-cache deserialization. Phase 1 keeps
// the cc paint transfer-cache vocabulary linkable but cannot produce service
// GPU images from serialized transfer-cache data.

ServiceImageTransferCacheEntry::ServiceImageTransferCacheEntry() = default;
ServiceImageTransferCacheEntry::~ServiceImageTransferCacheEntry() = default;
ServiceImageTransferCacheEntry::ServiceImageTransferCacheEntry(
    ServiceImageTransferCacheEntry&& other) = default;
ServiceImageTransferCacheEntry& ServiceImageTransferCacheEntry::operator=(
    ServiceImageTransferCacheEntry&& other) = default;

size_t ServiceImageTransferCacheEntry::CachedSize() const {
  return 0;
}

bool ServiceImageTransferCacheEntry::Deserialize(
    GrDirectContext* gr_context,
    skgpu::graphite::Recorder* graphite_recorder,
    base::span<const uint8_t> data) {
  return false;
}

void ServiceImageTransferCacheEntry::EnsureMips() {}

bool ServiceImageTransferCacheEntry::has_mips() const {
  return false;
}

const sk_sp<SkImage>& ServiceImageTransferCacheEntry::GetPlaneImage(
    size_t index) const {
  static const sk_sp<SkImage> empty_image;
  return empty_image;
}

bool ServiceImageTransferCacheEntry::fits_on_gpu() const {
  return false;
}

}  // namespace cc
