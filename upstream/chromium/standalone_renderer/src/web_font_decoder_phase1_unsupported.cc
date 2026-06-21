// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Downloadable web-font decoding depends on OTS/WOFF sanitization, which is
// outside Phase 1. System-font rendering remains active; remote/web font data
// fails closed here.

#include "third_party/blink/renderer/platform/fonts/web_font_decoder.h"

namespace blink {

sk_sp<SkTypeface> WebFontDecoder::Decode(SegmentedBuffer*) {
  SetErrorString("Web font decoding is unsupported in this standalone build.");
  return nullptr;
}

}  // namespace blink
