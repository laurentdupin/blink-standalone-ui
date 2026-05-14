// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_TOUCH_EVENT_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_TOUCH_EVENT_MOJOM_SHARED_H_

namespace blink::mojom {

enum class TouchState {
  kStateUndefined,
  kStateReleased,
  kStatePressed,
  kStateMoved,
  kStateStationary,
  kStateCancelled,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

using TouchState = ::blink::mojom::TouchState;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_TOUCH_EVENT_MOJOM_SHARED_H_
