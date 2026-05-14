// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Standalone renderer compile-time stub for an unavailable generated mojom
// forward header in this checkout.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace blink::mojom::blink {

class Blob;
using BlobPtr = mojo::Remote<Blob>;
using BlobPendingReceiver = mojo::PendingReceiver<Blob>;
using BlobPendingRemote = mojo::PendingRemote<Blob>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_MOJOM_BLINK_FORWARD_H_
