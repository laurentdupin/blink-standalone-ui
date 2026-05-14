// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_FILE_BACKED_BLOB_FACTORY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_FILE_BACKED_BLOB_FACTORY_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/bindings/remote.h"

namespace blink::mojom::blink {

class FileBackedBlobFactory;
using FileBackedBlobFactoryPtr = mojo::Remote<FileBackedBlobFactory>;
using FileBackedBlobFactoryPendingReceiver =
    mojo::PendingReceiver<FileBackedBlobFactory>;
using FileBackedBlobFactoryPendingRemote =
    mojo::PendingRemote<FileBackedBlobFactory>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_FILE_BACKED_BLOB_FACTORY_MOJOM_BLINK_FORWARD_H_
