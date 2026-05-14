// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_INPUT_EVENT_MOJOM_SHARED_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_INPUT_EVENT_MOJOM_SHARED_H_

namespace blink::mojom {

enum class Button {
  kNoButton = -1,
  kLeft,
  kMiddle,
  kRight,
  kBarrel = kRight,
  kBack,
  kForward,
  kEraser,
};

enum class DispatchType {
  kBlocking,
  kEventNonBlocking,
  kListenersNonBlockingPassive,
  kListenersForcedNonBlockingDueToFling,
};

enum EventType {
  kUndefined = -1,
  kTypeFirst = kUndefined,
  kMouseDown,
  kMouseTypeFirst = kMouseDown,
  kMouseUp,
  kMouseMove,
  kMouseEnter,
  kMouseLeave,
  kContextMenu,
  kMouseTypeLast = kContextMenu,
  kMouseWheel,
  kRawKeyDown,
  kKeyboardTypeFirst = kRawKeyDown,
  kKeyDown,
  kKeyUp,
  kChar,
  kKeyboardTypeLast = kChar,
  kGestureScrollBegin,
  kGestureTypeFirst = kGestureScrollBegin,
  kGestureScrollEnd,
  kGestureScrollUpdate,
  kGestureFlingStart,
  kGestureFlingCancel,
  kGesturePinchBegin,
  kGesturePinchTypeFirst = kGesturePinchBegin,
  kGesturePinchEnd,
  kGesturePinchUpdate,
  kGesturePinchTypeLast = kGesturePinchUpdate,
  kGestureBegin,
  kGestureTapDown,
  kGestureShowPress,
  kGestureTap,
  kGestureTapCancel,
  kGestureShortPress,
  kGestureLongPress,
  kGestureLongTap,
  kGestureTwoFingerTap,
  kGestureTapUnconfirmed,
  kGestureDoubleTap,
  kGestureEnd,
  kGestureTypeLast = kGestureEnd,
  kTouchStart,
  kTouchTypeFirst = kTouchStart,
  kTouchMove,
  kTouchEnd,
  kTouchCancel,
  kTouchScrollStarted,
  kTouchTypeLast = kTouchScrollStarted,
  kPointerDown,
  kPointerTypeFirst = kPointerDown,
  kPointerUp,
  kPointerMove,
  kPointerRawUpdate,
  kPointerCancel,
  kPointerCausedUaAction,
  kPointerTypeLast = kPointerCausedUaAction,
  kTypeLast = kPointerTypeLast,
};

enum class RailsMode {
  kRailsModeFree = 0,
  kRailsModeHorizontal = 1,
  kRailsModeVertical = 2,
};

enum class InertialPhaseState {
  kUnknownMomentumPhase,
  kNonMomentum,
  kMomentumPhase,
  kMomentumPhaseBlocked,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

enum class PanAction {
  kNone,
  kScroll,
  kMoveCursorOrScroll,
  kStylusWritable,
};

}  // namespace blink::mojom::blink

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_INPUT_EVENT_MOJOM_SHARED_H_
