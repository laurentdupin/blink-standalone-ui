// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/page/page.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/page/page_visibility_state.mojom-blink.h"
#include "base/time/time.h"
#include "third_party/blink/public/common/frame/view_transition_state.h"

namespace blink::mojom::blink {

struct PageLifecycleState {
  bool is_frozen = false;
  PageVisibilityState visibility = PageVisibilityState::kVisible;
  bool is_in_back_forward_cache = false;
  PagehideDispatch pagehide_dispatch = PagehideDispatch::kNotDispatched;
  bool eviction_enabled = true;

  static PageLifecycleStatePtr New() {
    return std::make_unique<PageLifecycleState>();
  }
};

enum class WasActivatedOption {
  kNo,
  kYes,
};

struct PrerenderPageActivationParams {
  WasActivatedOption was_user_activated = WasActivatedOption::kNo;
  std::optional<base::TimeTicks> activation_start;
  std::optional<ViewTransitionState> view_transition_state;
};

class PageBroadcast {
 public:
  class Proxy_ {};
  virtual ~PageBroadcast() = default;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_MOJOM_BLINK_H_
