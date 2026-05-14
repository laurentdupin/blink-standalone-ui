// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_TEXT_EVENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_EVENTS_TEXT_EVENT_H_

#include "third_party/blink/renderer/core/event_interface_names.h"
#include "third_party/blink/renderer/core/events/ui_event.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace blink {

class TextEvent final : public UIEvent {};

template <>
struct DowncastTraits<TextEvent> {
  static bool AllowFrom(const Event& event) {
    return event.HasInterface(event_interface_names::kTextEvent);
  }
};

}  // namespace blink

#endif
