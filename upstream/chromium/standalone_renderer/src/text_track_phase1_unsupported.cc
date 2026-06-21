// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Text tracks are part of media/subtitle runtime. Media decoding is unsupported
// in Phase 1, but style invalidation code can still inspect the declared track
// shape. Keep ownership inert and do not import cue/media runtime.

#include "third_party/blink/renderer/core/html/track/text_track.h"

namespace blink {

Node* TextTrack::Owner() const {
  return nullptr;
}

}  // namespace blink
