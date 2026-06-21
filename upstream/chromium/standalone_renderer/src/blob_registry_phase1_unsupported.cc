// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 has no browser blob registry or external blob IPC. These definitions
// satisfy generated Blink IPC vocabulary referenced by ResourceFetcher without
// enabling blob registration, streaming, or browser-side blob runtime.

#include "third_party/blink/public/mojom/blob/blob_registry.mojom-blink.h"
#include "third_party/blink/public/mojom/blob/data_element.mojom-blink.h"
#include "third_party/blink/public/mojom/blob/serialized_blob.mojom-blink.h"

#include <memory>
#include <utility>

namespace blink::mojom::blink {

BlobRegistry::IPCStableHashFunction BlobRegistry::MessageToMethodInfo_(
    mojo::Message&) {
  return nullptr;
}

const char* BlobRegistry::MessageToMethodName_(mojo::Message&) {
  return nullptr;
}

bool BlobRegistry::Register(
    ::mojo::PendingReceiver<::blink::mojom::blink::Blob>,
    const ::blink::String&,
    const ::blink::String&,
    const ::blink::String&,
    ::blink::Vector<::blink::mojom::blink::DataElementPtr>) {
  return false;
}

BlobRegistryProxy::BlobRegistryProxy(
    mojo::MessageReceiverWithResponder* receiver)
    : receiver_(receiver) {}

bool BlobRegistryProxy::Register(
    ::mojo::PendingReceiver<::blink::mojom::blink::Blob>,
    const ::blink::String&,
    const ::blink::String&,
    const ::blink::String&,
    ::blink::Vector<::blink::mojom::blink::DataElementPtr>) {
  return false;
}

void BlobRegistryProxy::Register(
    ::mojo::PendingReceiver<::blink::mojom::blink::Blob>,
    const ::blink::String&,
    const ::blink::String&,
    const ::blink::String&,
    ::blink::Vector<::blink::mojom::blink::DataElementPtr>,
    RegisterCallback) {}

void BlobRegistryProxy::RegisterFromStream(
    const ::blink::String&,
    const ::blink::String&,
    uint64_t,
    ::mojo::ScopedDataPipeConsumerHandle,
    ::mojo::PendingAssociatedRemote<ProgressClient>,
    RegisterFromStreamCallback callback) {
  if (callback) {
    std::move(callback).Run(nullptr);
  }
}

bool BlobRegistryRequestValidator::Accept(mojo::Message*) {
  return false;
}

bool BlobRegistryResponseValidator::Accept(mojo::Message*) {
  return false;
}

bool ProgressClientStubDispatch::Accept(ProgressClient*, mojo::Message*) {
  return false;
}

bool ProgressClientStubDispatch::AcceptWithResponder(
    ProgressClient*,
    mojo::Message*,
    std::unique_ptr<mojo::MessageReceiverWithStatus>) {
  return false;
}

}  // namespace blink::mojom::blink
