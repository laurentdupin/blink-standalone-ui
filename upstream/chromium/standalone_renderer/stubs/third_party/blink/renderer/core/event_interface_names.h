// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_EVENT_INTERFACE_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_EVENT_INTERFACE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::event_interface_names {

extern const AtomicString kAnimationEvent;
extern const AtomicString kAnimationPlaybackEvent;
extern const AtomicString kAutofillEvent;
extern const AtomicString kBeforeUnloadEvent;
extern const AtomicString kCanvasPaintEvent;
extern const AtomicString kClipboardEvent;
extern const AtomicString kCommandEvent;
extern const AtomicString kCompositionEvent;
extern const AtomicString kContentVisibilityAutoStateChangeEvent;
extern const AtomicString kCustomEvent;
extern const AtomicString kEmailVerifiedEvent;
extern const AtomicString kErrorEvent;
extern const AtomicString kEvent;
extern const AtomicString kFocusEvent;
extern const AtomicString kFontFaceSetLoadEvent;
extern const AtomicString kFormDataEvent;
extern const AtomicString kHashChangeEvent;
extern const AtomicString kInterestEvent;
extern const AtomicString kKeyboardEvent;
extern const AtomicString kMediaQueryListEvent;
extern const AtomicString kMessageEvent;
extern const AtomicString kMojoInterfaceRequestEvent;
extern const AtomicString kMouseEvent;
extern const AtomicString kNavigateEvent;
extern const AtomicString kNavigationCurrentEntryChangeEvent;
extern const AtomicString kOverscrollEvent;
extern const AtomicString kPageRevealEvent;
extern const AtomicString kPageSwapEvent;
extern const AtomicString kPageTransitionEvent;
extern const AtomicString kPopStateEvent;
extern const AtomicString kProgressEvent;
extern const AtomicString kPromiseRejectionEvent;
extern const AtomicString kResourceProgressEvent;
extern const AtomicString kRouteEvent;
extern const AtomicString kSecurityPolicyViolationEvent;
extern const AtomicString kSubmitEvent;
extern const AtomicString kTaskPriorityChangeEvent;
extern const AtomicString kTextEvent;
extern const AtomicString kTextFormatUpdateEvent;
extern const AtomicString kTextUpdateEvent;
extern const AtomicString kToggleEvent;
extern const AtomicString kTouchEvent;
extern const AtomicString kTrackEvent;
extern const AtomicString kTransitionEvent;
extern const AtomicString kUIEvent;
extern const AtomicString kWebMCPEvent;
extern const AtomicString kWheelEvent;
extern const AtomicString kNamesCount;

}  // namespace blink::event_interface_names

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_EVENT_INTERFACE_NAMES_H_
