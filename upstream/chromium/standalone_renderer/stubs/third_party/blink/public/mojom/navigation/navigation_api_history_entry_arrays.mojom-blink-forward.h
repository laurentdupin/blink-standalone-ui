// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_API_HISTORY_ENTRY_ARRAYS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_API_HISTORY_ENTRY_ARRAYS_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

struct NavigationApiHistoryEntry;
using NavigationApiHistoryEntryPtr =
    std::unique_ptr<NavigationApiHistoryEntry>;

struct NavigationApiHistoryEntryArrays;
using NavigationApiHistoryEntryArraysPtr =
    std::unique_ptr<NavigationApiHistoryEntryArrays>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_API_HISTORY_ENTRY_ARRAYS_MOJOM_BLINK_FORWARD_H_
