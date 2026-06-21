// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "mojo/public/cpp/bindings/lib/native_struct_serialization.h"

#include "mojo/public/cpp/bindings/lib/message_fragment.h"
#include "mojo/public/interfaces/bindings/native_struct.mojom.h"

namespace mojo::internal {

void UnmappedNativeStructSerializerImpl::Serialize(
    const native::NativeStructPtr& input,
    MessageFragment<native::internal::NativeStruct_Data>& fragment) {
  if (!input) {
    return;
  }

  fragment.Allocate();
  fragment->data.Set(nullptr);
  fragment->handles.Set(nullptr);
}

bool UnmappedNativeStructSerializerImpl::Deserialize(
    native::internal::NativeStruct_Data* input,
    native::NativeStructPtr* output,
    Message*) {
  output->reset();
  return input == nullptr;
}

void UnmappedNativeStructSerializerImpl::SerializeMessageContents(
    IPC::Message*,
    MessageFragment<native::internal::NativeStruct_Data>& fragment) {
  fragment.Allocate();
  fragment->data.Set(nullptr);
  fragment->handles.Set(nullptr);
}

bool UnmappedNativeStructSerializerImpl::DeserializeMessageAttachments(
    native::internal::NativeStruct_Data* data,
    Message*,
    IPC::Message*) {
  return data && data->handles.is_null();
}

}  // namespace mojo::internal
