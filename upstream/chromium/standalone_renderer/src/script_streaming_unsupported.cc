// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Inline script streaming is a JavaScript execution optimization. Phase 1 keeps
// parser/layout/paint active but does not enable V8 code-cache/streaming
// runtime, so background inline streamers are inert.

#include "third_party/blink/renderer/bindings/core/v8/script_streamer.h"

namespace blink {

BackgroundInlineScriptStreamer::BackgroundInlineScriptStreamer(
    v8::Isolate*,
    const String& text,
    v8::ScriptCompiler::CompileOptions,
    base::TimeDelta wait_timeout)
    : script_length_(text.length()),
      wait_timeout_(wait_timeout),
      timeout_histogram_name_() {}

void BackgroundInlineScriptStreamer::Run() {
  started_.Set();
  timed_out_ = false;
}

v8::ScriptCompiler::StreamedSource* BackgroundInlineScriptStreamer::Source(
    v8::ScriptType) {
  return nullptr;
}

InlineScriptStreamer* InlineScriptStreamer::From(
    scoped_refptr<BackgroundInlineScriptStreamer>) {
  return nullptr;
}

}  // namespace blink
