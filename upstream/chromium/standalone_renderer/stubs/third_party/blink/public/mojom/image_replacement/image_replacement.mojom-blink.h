// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_IMAGE_REPLACEMENT_IMAGE_REPLACEMENT_MOJOM_BLINK_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_IMAGE_REPLACEMENT_IMAGE_REPLACEMENT_MOJOM_BLINK_H_

#include "mojo/public/cpp/bindings/pending_remote.h"

namespace blink::mojom::blink {

class ImageReplacementHost;

class ImageReplacement {
 public:
  using Proxy_ = ImageReplacement;
  virtual ~ImageReplacement() = default;
  virtual void StartReplacement(
      mojo::PendingRemote<ImageReplacementHost> host_remote) = 0;
  virtual void RenderReplacement() = 0;
};

class ImageReplacementHost {
 public:
  using Proxy_ = ImageReplacementHost;
  virtual ~ImageReplacementHost() = default;
};

class ImageReplacementProxy {
 public:
  void StartReplacement(mojo::PendingRemote<ImageReplacementHost>) {}
  void RenderReplacement() {}
};

using ImageReplacementProxy_ = ImageReplacementProxy;

}  // namespace blink::mojom::blink

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_IMAGE_REPLACEMENT_IMAGE_REPLACEMENT_MOJOM_BLINK_H_
