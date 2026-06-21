// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 does not import Blink's web-test runtime. These toggles are queried
// by font rendering code, so keep only deterministic defaults here.

#include "third_party/blink/renderer/platform/web_test_support.h"

namespace blink {

bool WebTestSupport::IsFontAntialiasingEnabledForTest() {
  return false;
}

bool WebTestSupport::IsTextSubpixelPositioningAllowedForTest() {
  return true;
}

}  // namespace blink
