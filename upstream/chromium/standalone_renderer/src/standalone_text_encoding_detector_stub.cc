// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/text/text_encoding_detector.h"

#include "third_party/blink/renderer/platform/wtf/text/text_encoding.h"

namespace blink {

bool DetectTextEncoding(base::span<const uint8_t>,
                        const char*,
                        const KURL&,
                        const char*,
                        TextEncoding* detected_encoding) {
  *detected_encoding = TextEncoding();
  return false;
}

}  // namespace blink
