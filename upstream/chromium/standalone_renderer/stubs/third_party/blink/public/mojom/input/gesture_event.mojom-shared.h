// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_GESTURE_EVENT_MOJOM_SHARED_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_GESTURE_EVENT_MOJOM_SHARED_H_

namespace blink::mojom {

enum class GestureDevice {
  kUninitialized,
  kTouchscreen,
  kTouchpad,
  kSyntheticAutoscroll,
  kScrollbar,
};

}  // namespace blink::mojom

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_GESTURE_EVENT_MOJOM_SHARED_H_
