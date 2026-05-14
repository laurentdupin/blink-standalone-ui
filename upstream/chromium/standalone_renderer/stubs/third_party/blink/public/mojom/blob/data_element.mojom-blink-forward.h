// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_DATA_ELEMENT_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_DATA_ELEMENT_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"

namespace blink::mojom::blink {

class DataElement;
class DataElementFile;
class BytesProvider;
using DataElementPtr = mojo::StructPtr<DataElement>;
using DataElementFilePtr = mojo::StructPtr<DataElementFile>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_DATA_ELEMENT_MOJOM_BLINK_FORWARD_H_
