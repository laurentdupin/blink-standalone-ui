// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_TRACK_TEXT_TRACK_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_TRACK_TEXT_TRACK_H_

#include "third_party/blink/renderer/platform/heap/collection_support/heap_vector.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/heap/member.h"

namespace blink {

class CSSStyleSheet;
class Node;

class TextTrack : public GarbageCollected<TextTrack> {
 public:
  const HeapVector<Member<CSSStyleSheet>>& GetCSSStyleSheets() const {
    return style_sheets_;
  }
  Node* Owner() const { return nullptr; }
  void Trace(Visitor*) const {}

 private:
  HeapVector<Member<CSSStyleSheet>> style_sheets_;
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_TRACK_TEXT_TRACK_H_
