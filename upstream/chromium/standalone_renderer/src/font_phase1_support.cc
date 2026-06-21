// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 keeps system/static text rendering active without importing the full
// FontCache owner yet. These are the narrow value/static owners needed by the
// active font path.

#include "third_party/blink/renderer/platform/fonts/font.h"

#include "third_party/blink/renderer/platform/fonts/font_cache.h"

namespace blink {

bool FontCache::antialiased_text_enabled_ = true;
bool FontCache::lcd_text_enabled_ = true;

void FontCache::SetSystemFontFamily(const AtomicString&) {}

bool Font::CanShapeWordByWord() const {
  return false;
}

}  // namespace blink
