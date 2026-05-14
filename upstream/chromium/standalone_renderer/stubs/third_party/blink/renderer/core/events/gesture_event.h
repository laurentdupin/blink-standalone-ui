// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_GESTURE_EVENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_GESTURE_EVENT_H_

#include "third_party/blink/renderer/core/dom/events/event.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace blink {

class GestureEvent : public Event {
 public:
  using Event::Event;
};

template <>
struct DowncastTraits<GestureEvent> {
  static bool AllowFrom(const Event&) { return false; }
};

}  // namespace blink

#endif
