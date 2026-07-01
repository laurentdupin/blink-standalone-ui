// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Context menu, drag, and disk allocator IPC surfaces are browser-feature
// vocabulary that can appear in generated frame signatures. The standalone
// renderer does not support those runtime channels in Phase 1.

#include "third_party/blink/public/mojom/context_menu/context_menu.mojom-blink.h"
#include "third_party/blink/public/mojom/context_menu/context_menu.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/context_menu/context_menu.mojom.h"
#include "third_party/blink/public/mojom/disk_allocator.mojom-blink.h"
#include "third_party/blink/public/mojom/disk_allocator.mojom.h"
#include "third_party/blink/public/mojom/drag/drag.mojom-blink.h"
#include "third_party/blink/public/mojom/drag/drag.mojom-shared-internal.h"
#include "third_party/blink/public/mojom/drag/drag.mojom.h"
#include "third_party/blink/public/mojom/blob/serialized_blob.mojom-shared-internal.h"

#include "mojo/public/cpp/bindings/message.h"

#include <memory>
#include <optional>
#include <utility>

#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

namespace blink::mojom::internal {

bool Accelerator_Data::Validate(const void*,
                                mojo::internal::ValidationContext*) {
  return true;
}
Accelerator_Data::Accelerator_Data() : header_({sizeof(*this), 0}) {}

bool FormRendererId_Data::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}
FormRendererId_Data::FormRendererId_Data() : header_({sizeof(*this), 0}) {}

bool FieldRendererId_Data::Validate(const void*,
                                    mojo::internal::ValidationContext*) {
  return true;
}
FieldRendererId_Data::FieldRendererId_Data() : header_({sizeof(*this), 0}) {}

bool CustomContextMenuItem_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
CustomContextMenuItem_Data::CustomContextMenuItem_Data()
    : header_({sizeof(*this), 0}) {}

bool UntrustworthyContextMenuParams_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
UntrustworthyContextMenuParams_Data::UntrustworthyContextMenuParams_Data()
    : header_({sizeof(*this), 0}) {}

bool AllowedDragOperations_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
AllowedDragOperations_Data::AllowedDragOperations_Data()
    : header_({sizeof(*this), 0}) {}

bool DragItemString_Data::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}
DragItemString_Data::DragItemString_Data() : header_({sizeof(*this), 0}) {}

bool DragItemBinary_Data::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}
DragItemBinary_Data::DragItemBinary_Data() : header_({sizeof(*this), 0}) {}

bool DragItemFileSystemFile_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
DragItemFileSystemFile_Data::DragItemFileSystemFile_Data()
    : header_({sizeof(*this), 0}) {}

bool DragData_Data::Validate(const void*,
                             mojo::internal::ValidationContext*) {
  return true;
}
DragData_Data::DragData_Data() : header_({sizeof(*this), 0}) {}

bool DragEventSourceInfo_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
DragEventSourceInfo_Data::DragEventSourceInfo_Data()
    : header_({sizeof(*this), 0}) {}

bool SerializedBlob_Data::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}
SerializedBlob_Data::SerializedBlob_Data() : header_({sizeof(*this), 0}) {}

}  // namespace blink::mojom::internal

namespace blink::mojom {

bool ContextMenuClientStubDispatch::Accept(ContextMenuClient*,
                                           mojo::Message*) {
  return false;
}

bool ContextMenuClientStubDispatch::AcceptWithResponder(
    ContextMenuClient*,
    mojo::Message*,
    std::unique_ptr<mojo::MessageReceiverWithStatus>) {
  return false;
}

bool DiskAllocatorStubDispatch::Accept(DiskAllocator*, mojo::Message*) {
  return false;
}

bool DiskAllocatorStubDispatch::AcceptWithResponder(
    DiskAllocator*,
    mojo::Message*,
    std::unique_ptr<mojo::MessageReceiverWithStatus>) {
  return false;
}

Accelerator::Accelerator() : key_code(0), modifiers(0) {}
Accelerator::Accelerator(uint16_t key_code_in, int32_t modifiers_in)
    : key_code(key_code_in), modifiers(modifiers_in) {}
Accelerator::~Accelerator() = default;
size_t Accelerator::Hash(size_t seed) const {
  return seed;
}
void Accelerator::WriteIntoTrace(perfetto::TracedValue) const {}
bool Accelerator::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

FormRendererId::FormRendererId() : id(0) {}
FormRendererId::FormRendererId(uint64_t id_in) : id(id_in) {}
FormRendererId::~FormRendererId() = default;
size_t FormRendererId::Hash(size_t seed) const {
  return seed;
}
void FormRendererId::WriteIntoTrace(perfetto::TracedValue) const {}
bool FormRendererId::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

FieldRendererId::FieldRendererId() : id(0) {}
FieldRendererId::FieldRendererId(uint64_t id_in) : id(id_in) {}
FieldRendererId::~FieldRendererId() = default;
size_t FieldRendererId::Hash(size_t seed) const {
  return seed;
}
void FieldRendererId::WriteIntoTrace(perfetto::TracedValue) const {}
bool FieldRendererId::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

CustomContextMenuItem::CustomContextMenuItem() = default;
CustomContextMenuItem::~CustomContextMenuItem() = default;
void CustomContextMenuItem::WriteIntoTrace(perfetto::TracedValue) const {}
bool CustomContextMenuItem::Validate(const void*,
                                     mojo::internal::ValidationContext*) {
  return true;
}

UntrustworthyContextMenuParams::UntrustworthyContextMenuParams() = default;
UntrustworthyContextMenuParams::~UntrustworthyContextMenuParams() = default;
void UntrustworthyContextMenuParams::WriteIntoTrace(
    perfetto::TracedValue) const {}
bool UntrustworthyContextMenuParams::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

AllowedDragOperations::AllowedDragOperations()
    : allow_copy(false), allow_link(false), allow_move(false) {}
AllowedDragOperations::AllowedDragOperations(bool allow_copy,
                                             bool allow_link,
                                             bool allow_move)
    : allow_copy(allow_copy),
      allow_link(allow_link),
      allow_move(allow_move) {}
AllowedDragOperations::~AllowedDragOperations() = default;
size_t AllowedDragOperations::Hash(size_t seed) const {
  return seed;
}
void AllowedDragOperations::WriteIntoTrace(perfetto::TracedValue) const {}
bool AllowedDragOperations::Validate(const void*,
                                     mojo::internal::ValidationContext*) {
  return true;
}

DragItem::~DragItem() {}

DragData::DragData()
    : force_default_action(false),
      source_effect_allowed(std::nullopt),
      referrer_policy(::network::mojom::ReferrerPolicy::kDefault) {}
DragData::~DragData() = default;
void DragData::WriteIntoTrace(perfetto::TracedValue) const {}
bool DragData::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

DragEventSourceInfo::DragEventSourceInfo() = default;
DragEventSourceInfo::~DragEventSourceInfo() = default;
void DragEventSourceInfo::WriteIntoTrace(perfetto::TracedValue) const {}
bool DragEventSourceInfo::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}

}  // namespace blink::mojom

namespace blink::mojom::blink {

bool ContextMenuClientStubDispatch::Accept(ContextMenuClient*,
                                           mojo::Message*) {
  return false;
}

bool ContextMenuClientStubDispatch::AcceptWithResponder(
    ContextMenuClient*,
    mojo::Message*,
    std::unique_ptr<mojo::MessageReceiverWithStatus>) {
  return false;
}

bool DiskAllocatorStubDispatch::Accept(DiskAllocator*, mojo::Message*) {
  return false;
}

bool DiskAllocatorStubDispatch::AcceptWithResponder(
    DiskAllocator*,
    mojo::Message*,
    std::unique_ptr<mojo::MessageReceiverWithStatus>) {
  return false;
}

Accelerator::Accelerator() : key_code(0), modifiers(0) {}
Accelerator::Accelerator(uint16_t key_code_in, int32_t modifiers_in)
    : key_code(key_code_in), modifiers(modifiers_in) {}
Accelerator::~Accelerator() = default;
size_t Accelerator::Hash(size_t seed) const {
  return seed;
}
void Accelerator::WriteIntoTrace(perfetto::TracedValue) const {}
bool Accelerator::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

FormRendererId::FormRendererId() : id(0) {}
FormRendererId::FormRendererId(uint64_t id_in) : id(id_in) {}
FormRendererId::~FormRendererId() = default;
size_t FormRendererId::Hash(size_t seed) const {
  return seed;
}
void FormRendererId::WriteIntoTrace(perfetto::TracedValue) const {}
bool FormRendererId::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

FieldRendererId::FieldRendererId() : id(0) {}
FieldRendererId::FieldRendererId(uint64_t id_in) : id(id_in) {}
FieldRendererId::~FieldRendererId() = default;
size_t FieldRendererId::Hash(size_t seed) const {
  return seed;
}
void FieldRendererId::WriteIntoTrace(perfetto::TracedValue) const {}
bool FieldRendererId::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

CustomContextMenuItem::CustomContextMenuItem() = default;
CustomContextMenuItem::~CustomContextMenuItem() = default;
void CustomContextMenuItem::WriteIntoTrace(perfetto::TracedValue) const {}
bool CustomContextMenuItem::Validate(const void*,
                                     mojo::internal::ValidationContext*) {
  return true;
}

UntrustworthyContextMenuParams::UntrustworthyContextMenuParams() = default;
UntrustworthyContextMenuParams::~UntrustworthyContextMenuParams() = default;
void UntrustworthyContextMenuParams::WriteIntoTrace(
    perfetto::TracedValue) const {}
bool UntrustworthyContextMenuParams::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

AllowedDragOperations::AllowedDragOperations()
    : allow_copy(false), allow_link(false), allow_move(false) {}
AllowedDragOperations::AllowedDragOperations(bool allow_copy,
                                             bool allow_link,
                                             bool allow_move)
    : allow_copy(allow_copy),
      allow_link(allow_link),
      allow_move(allow_move) {}
AllowedDragOperations::~AllowedDragOperations() = default;
size_t AllowedDragOperations::Hash(size_t seed) const {
  return seed;
}
void AllowedDragOperations::WriteIntoTrace(perfetto::TracedValue) const {}
bool AllowedDragOperations::Validate(const void*,
                                     mojo::internal::ValidationContext*) {
  return true;
}

DragItem::~DragItem() {}

DragData::DragData()
    : force_default_action(false),
      source_effect_allowed(std::nullopt),
      referrer_policy(::network::mojom::blink::ReferrerPolicy::kDefault) {}
DragData::~DragData() = default;
void DragData::WriteIntoTrace(perfetto::TracedValue) const {}
bool DragData::Validate(const void*, mojo::internal::ValidationContext*) {
  return true;
}

DragEventSourceInfo::DragEventSourceInfo() = default;
DragEventSourceInfo::~DragEventSourceInfo() = default;
void DragEventSourceInfo::WriteIntoTrace(perfetto::TracedValue) const {}
bool DragEventSourceInfo::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}

}  // namespace blink::mojom::blink

namespace mojo {

bool StructTraits<::blink::mojom::UntrustworthyContextMenuParams::DataView,
                  ::blink::mojom::UntrustworthyContextMenuParamsPtr>::
    Read(::blink::mojom::UntrustworthyContextMenuParams::DataView,
         ::blink::mojom::UntrustworthyContextMenuParamsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::blink::UntrustworthyContextMenuParams::
                      DataView,
                  ::blink::mojom::blink::UntrustworthyContextMenuParamsPtr>::
    Read(::blink::mojom::blink::UntrustworthyContextMenuParams::DataView,
         ::blink::mojom::blink::UntrustworthyContextMenuParamsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::AllowedDragOperations::DataView,
                  ::blink::mojom::AllowedDragOperationsPtr>::
    Read(::blink::mojom::AllowedDragOperations::DataView,
         ::blink::mojom::AllowedDragOperationsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::blink::AllowedDragOperations::DataView,
                  ::blink::mojom::blink::AllowedDragOperationsPtr>::
    Read(::blink::mojom::blink::AllowedDragOperations::DataView,
         ::blink::mojom::blink::AllowedDragOperationsPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::DragData::DataView,
                  ::blink::mojom::DragDataPtr>::
    Read(::blink::mojom::DragData::DataView,
         ::blink::mojom::DragDataPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::blink::DragData::DataView,
                  ::blink::mojom::blink::DragDataPtr>::
    Read(::blink::mojom::blink::DragData::DataView,
         ::blink::mojom::blink::DragDataPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::DragEventSourceInfo::DataView,
                  ::blink::mojom::DragEventSourceInfoPtr>::
    Read(::blink::mojom::DragEventSourceInfo::DataView,
         ::blink::mojom::DragEventSourceInfoPtr* output) {
  output->reset();
  return false;
}

bool StructTraits<::blink::mojom::blink::DragEventSourceInfo::DataView,
                  ::blink::mojom::blink::DragEventSourceInfoPtr>::
    Read(::blink::mojom::blink::DragEventSourceInfo::DataView,
         ::blink::mojom::blink::DragEventSourceInfoPtr* output) {
  output->reset();
  return false;
}

}  // namespace mojo
