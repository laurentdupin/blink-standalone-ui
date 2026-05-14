// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_PARAMS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_PARAMS_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

enum class NavigationType {
  RELOAD,
  RELOAD_BYPASSING_CACHE,
  RESTORE,
  RESTORE_WITH_POST,
  HISTORY_SAME_DOCUMENT,
  HISTORY_DIFFERENT_DOCUMENT,
  SAME_DOCUMENT,
  DIFFERENT_DOCUMENT,
};

struct BeginNavigationParams;
using BeginNavigationParamsPtr = std::unique_ptr<BeginNavigationParams>;

struct CommitNavigationParams;
using CommitNavigationParamsPtr = std::unique_ptr<CommitNavigationParams>;

struct PageSwapEventParams;
using PageSwapEventParamsPtr = std::unique_ptr<PageSwapEventParams>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_PARAMS_MOJOM_BLINK_FORWARD_H_
