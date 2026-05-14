// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_names.h.tmpl
// and input files:
//   ../../third_party/blink/renderer/core/html/parser/html_tokenizer_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_TOKENIZER_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_TOKENIZER_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/platform_export.h"

namespace blink {
namespace html_tokenizer_names {

extern const AtomicString& kCdata;
extern const AtomicString& kDashDash;
extern const AtomicString& kDoctype;
extern const AtomicString& kPublic;
extern const AtomicString& kSystem;

constexpr unsigned kNamesCount = 5;

void Init();

}  // namespace html_tokenizer_names
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_TOKENIZER_NAMES_H_
