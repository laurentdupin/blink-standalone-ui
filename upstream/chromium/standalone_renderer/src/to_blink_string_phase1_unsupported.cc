// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 does not enable V8 string conversion. Keep the required template
// instantiation inert instead of source-listing Blink's binding runtime.

#include "third_party/blink/renderer/platform/bindings/to_blink_string.h"

namespace blink {

template <typename StringType>
StringType ToBlinkString(v8::Isolate*, v8::Local<v8::String>, ExternalMode) {
  return StringType();
}

template String ToBlinkString<String>(v8::Isolate*,
                                      v8::Local<v8::String>,
                                      ExternalMode);

}  // namespace blink
