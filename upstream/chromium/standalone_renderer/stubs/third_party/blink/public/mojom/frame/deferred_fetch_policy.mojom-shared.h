// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_DEFERRED_FETCH_POLICY_MOJOM_SHARED_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_DEFERRED_FETCH_POLICY_MOJOM_SHARED_H_

namespace blink::mojom {

enum class DeferredFetchPolicy {
  kDisabled,
  kDeferredFetch,
  kDeferredFetchMinimal,
};

}  // namespace blink::mojom

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_DEFERRED_FETCH_POLICY_MOJOM_SHARED_H_
