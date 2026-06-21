// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/messaging/blink_cloneable_message.h"
#include "third_party/blink/renderer/core/messaging/blink_cloneable_message_mojom_traits.h"
#include "third_party/blink/renderer/core/messaging/blink_transferable_message.h"
#include "third_party/blink/renderer/core/messaging/blink_transferable_message_mojom_traits.h"
#include "third_party/blink/public/common/messaging/cloneable_message_mojom_traits.h"
#include "third_party/blink/public/common/messaging/message_port_descriptor_mojom_traits.h"
#include "third_party/blink/public/common/messaging/transferable_message_mojom_traits.h"
#include "third_party/blink/public/mojom/array_buffer/array_buffer_contents.mojom-blink.h"
#include "third_party/blink/public/mojom/array_buffer/array_buffer_contents.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/array_buffer/array_buffer_contents.mojom.h"
#include "third_party/blink/public/mojom/blob/serialized_blob.mojom-blink.h"
#include "third_party/blink/public/mojom/blob/serialized_blob.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/blob/serialized_blob.mojom.h"
#include "third_party/blink/public/mojom/messaging/cloneable_message.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/messaging/message_port_descriptor.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/messaging/static_bitmap_image.mojom-blink.h"
#include "third_party/blink/public/mojom/messaging/static_bitmap_image.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/messaging/static_bitmap_image.mojom.h"
#include "third_party/blink/public/mojom/messaging/transferable_message.mojom-shared-internal.h"
#include "third_party/blink/renderer/platform/blob/serialized_blob_mojom_traits.h"
#include "mojo/public/cpp/platform/platform_handle.h"
#include "mojo/public/cpp/system/platform_handle.h"
#include "ui/gfx/gpu_memory_buffer_handle.h"

#include <tuple>

namespace blink {

// Structured clone, postMessage transfer, and blob/JS serialization are not
// part of the standalone rendering target. Blink-side values still appear in
// active LocalFrame signatures, so keep their special-member ownership
// centralized without linking the serialization runtime.

CloneableMessage::CloneableMessage() = default;
CloneableMessage::CloneableMessage(CloneableMessage&&) = default;
CloneableMessage& CloneableMessage::operator=(CloneableMessage&&) = default;
CloneableMessage::~CloneableMessage() = default;
CloneableMessage CloneableMessage::ShallowClone() const {
  return CloneableMessage();
}
void CloneableMessage::EnsureDataIsOwned() {}

TransferableMessage::TransferableMessage() = default;
TransferableMessage::TransferableMessage(TransferableMessage&&) = default;
TransferableMessage& TransferableMessage::operator=(TransferableMessage&&) =
    default;
TransferableMessage::~TransferableMessage() = default;

BlinkCloneableMessage::BlinkCloneableMessage() = default;
BlinkCloneableMessage::BlinkCloneableMessage(BlinkCloneableMessage&&) =
    default;
BlinkCloneableMessage& BlinkCloneableMessage::operator=(
    BlinkCloneableMessage&&) = default;
BlinkCloneableMessage::~BlinkCloneableMessage() = default;

BlinkTransferableMessage::BlinkTransferableMessage() = default;
BlinkTransferableMessage::BlinkTransferableMessage(BlinkTransferableMessage&&) =
    default;
BlinkTransferableMessage& BlinkTransferableMessage::operator=(
    BlinkTransferableMessage&&) = default;
BlinkTransferableMessage::~BlinkTransferableMessage() = default;

mojo::PendingRemote<mojom::blink::Blob> BlobDataHandle::CloneBlobRemote() {
  return mojo::PendingRemote<mojom::blink::Blob>();
}

void BlobDataHandle::CloneBlobRemote(
    mojo::PendingReceiver<mojom::blink::Blob>) {}

}  // namespace blink

namespace blink::mojom::internal {

bool MessagePortDescriptor_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
MessagePortDescriptor_Data::MessagePortDescriptor_Data()
    : header_({sizeof(*this), 0}) {}

bool CloneableMessage_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
CloneableMessage_Data::CloneableMessage_Data()
    : header_({sizeof(*this), 0}) {}

bool TransferableMessage_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
TransferableMessage_Data::TransferableMessage_Data()
    : header_({sizeof(*this), 0}) {}

bool SerializedArrayBufferContents_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
SerializedArrayBufferContents_Data::SerializedArrayBufferContents_Data()
    : header_({sizeof(*this), 0}) {}

}  // namespace blink::mojom::internal

namespace blink::mojom {

SerializedArrayBufferContents::SerializedArrayBufferContents() = default;
SerializedArrayBufferContents::SerializedArrayBufferContents(
    ::mojo_base::mojom::BigBufferPtr contents_in,
    std::optional<uint64_t> javascript_resize_limit_in)
    : contents(std::move(contents_in)),
      javascript_resize_limit(std::move(javascript_resize_limit_in)) {}
SerializedArrayBufferContents::~SerializedArrayBufferContents() = default;
void SerializedArrayBufferContents::WriteIntoTrace(perfetto::TracedValue) const {
}
bool SerializedArrayBufferContents::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

SerializedBlob::SerializedBlob() : size(0) {}
SerializedBlob::SerializedBlob(
    const std::string& uuid_in,
    const std::string& content_type_in,
    uint64_t size_in,
    mojo::PendingRemote<Blob> blob_in)
    : uuid(uuid_in),
      content_type(content_type_in),
      size(size_in),
      blob(std::move(blob_in)) {}
SerializedBlob::~SerializedBlob() = default;

}  // namespace blink::mojom

namespace blink::mojom::blink {

SerializedArrayBufferContents::SerializedArrayBufferContents() = default;
SerializedArrayBufferContents::SerializedArrayBufferContents(
    ::mojo_base::mojom::blink::BigBufferPtr contents_in,
    std::optional<uint64_t> javascript_resize_limit_in)
    : contents(std::move(contents_in)),
      javascript_resize_limit(std::move(javascript_resize_limit_in)) {}
SerializedArrayBufferContents::~SerializedArrayBufferContents() = default;
void SerializedArrayBufferContents::WriteIntoTrace(perfetto::TracedValue) const {
}
bool SerializedArrayBufferContents::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

SerializedBlob::SerializedBlob() : size(0) {}
SerializedBlob::SerializedBlob(
    const String& uuid_in,
    const String& content_type_in,
    uint64_t size_in,
    mojo::PendingRemote<Blob> blob_in)
    : uuid(uuid_in),
      content_type(content_type_in),
      size(size_in),
      blob(std::move(blob_in)) {}
SerializedBlob::~SerializedBlob() = default;

}  // namespace blink::mojom::blink

namespace mojo {

mojo_base::BigBufferView
StructTraits<blink::mojom::CloneableMessageDataView,
             blink::CloneableMessage>::
    encoded_message(blink::CloneableMessage&) {
  return mojo_base::BigBufferView(base::span<const uint8_t>());
}

bool StructTraits<blink::mojom::CloneableMessageDataView,
                  blink::CloneableMessage>::
    Read(blink::mojom::CloneableMessageDataView,
         blink::CloneableMessage*) {
  return false;
}

bool StructTraits<blink::mojom::TransferableMessageDataView,
                  blink::TransferableMessage>::
    Read(blink::mojom::TransferableMessageDataView,
         blink::TransferableMessage*) {
  return false;
}

blink::Vector<scoped_refptr<blink::BlobDataHandle>>
StructTraits<blink::mojom::CloneableMessageDataView,
             blink::BlinkCloneableMessage>::
    blobs(blink::BlinkCloneableMessage&) {
  return {};
}

bool StructTraits<blink::mojom::CloneableMessageDataView,
                  blink::BlinkCloneableMessage>::
    Read(blink::mojom::CloneableMessageDataView,
         blink::BlinkCloneableMessage*) {
  return false;
}

blink::Vector<blink::mojom::blink::SerializedStaticBitmapImagePtr>
StructTraits<blink::mojom::TransferableMessageDataView,
             blink::BlinkTransferableMessage>::
    image_bitmap_contents_array(const blink::BlinkCloneableMessage&) {
  return {};
}

bool StructTraits<blink::mojom::TransferableMessageDataView,
                  blink::BlinkTransferableMessage>::
    Read(blink::mojom::TransferableMessageDataView,
         blink::BlinkTransferableMessage*) {
  return false;
}

bool StructTraits<blink::mojom::SerializedArrayBufferContentsDataView,
                  blink::ArrayBufferContents>::
    Read(blink::mojom::SerializedArrayBufferContentsDataView,
         blink::ArrayBufferContents*) {
  return false;
}

bool StructTraits<blink::mojom::SerializedArrayBufferContents::DataView,
                  blink::mojom::SerializedArrayBufferContentsPtr>::
    Read(blink::mojom::SerializedArrayBufferContents::DataView,
         blink::mojom::SerializedArrayBufferContentsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<blink::mojom::blink::SerializedArrayBufferContents::DataView,
                  blink::mojom::blink::SerializedArrayBufferContentsPtr>::
    Read(blink::mojom::blink::SerializedArrayBufferContents::DataView,
         blink::mojom::blink::SerializedArrayBufferContentsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<blink::mojom::SerializedBlobDataView,
                  scoped_refptr<blink::BlobDataHandle>>::
    Read(blink::mojom::SerializedBlobDataView,
         scoped_refptr<blink::BlobDataHandle>* out) {
  out->reset();
  return false;
}

mojo::ScopedMessagePipeHandle
StructTraits<blink::mojom::MessagePortDescriptorDataView,
             blink::MessagePortDescriptor>::
    pipe_handle(blink::MessagePortDescriptor&) {
  return mojo::ScopedMessagePipeHandle();
}

base::UnguessableToken
StructTraits<blink::mojom::MessagePortDescriptorDataView,
             blink::MessagePortDescriptor>::
    id(blink::MessagePortDescriptor&) {
  return base::UnguessableToken::Null();
}

uint64_t StructTraits<blink::mojom::MessagePortDescriptorDataView,
                      blink::MessagePortDescriptor>::
    sequence_number(blink::MessagePortDescriptor&) {
  return 0;
}

bool StructTraits<blink::mojom::MessagePortDescriptorDataView,
                  blink::MessagePortDescriptor>::
    Read(blink::mojom::MessagePortDescriptorDataView,
         blink::MessagePortDescriptor*) {
  return false;
}

}  // namespace mojo
