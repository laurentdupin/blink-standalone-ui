// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FETCH_FETCH_API_REQUEST_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FETCH_FETCH_API_REQUEST_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"
#include "third_party/blink/public/mojom/fetch/fetch_api_request.mojom-shared.h"

namespace blink::mojom::blink {

using RequestContextType = ::blink::mojom::RequestContextType;
using FetchCacheMode = ::blink::mojom::FetchCacheMode;
using FetchPriorityHint = ::blink::mojom::FetchPriorityHint;
class FetchAPIRequestHeaders;
class FetchAPIRequestBody;
class FetchAPIRequest;

using FetchAPIRequestHeadersPtr = mojo::StructPtr<FetchAPIRequestHeaders>;
using FetchAPIRequestBodyPtr = mojo::StructPtr<FetchAPIRequestBody>;
using FetchAPIRequestPtr = mojo::StructPtr<FetchAPIRequest>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FETCH_FETCH_API_REQUEST_MOJOM_BLINK_FORWARD_H_
