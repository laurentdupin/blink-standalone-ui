// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_REGISTRY_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_REGISTRY_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/blob/blob_registry.mojom-blink-forward.h"

namespace blink::mojom::blink {

class BlobRegistry {
 public:
  class Proxy_ {};
  virtual ~BlobRegistry() = default;
};

class ProgressClient {
 public:
  class Proxy_ {};
  virtual ~ProgressClient() = default;
  virtual void OnProgress(uint64_t delta) = 0;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_REGISTRY_MOJOM_BLINK_H_
