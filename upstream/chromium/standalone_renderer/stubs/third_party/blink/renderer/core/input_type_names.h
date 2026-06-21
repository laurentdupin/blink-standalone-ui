// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::input_type_names {
extern const AtomicString& kButton;
extern const AtomicString& kCheckbox;
extern const AtomicString& kColor;
extern const AtomicString& kDate;
extern const AtomicString& kDatetime;
extern const AtomicString& kDatetimeLocal;
extern const AtomicString& kEmail;
extern const AtomicString& kImage;
extern const AtomicString& kFile;
extern const AtomicString& kHidden;
extern const AtomicString& kMonth;
extern const AtomicString& kNumber;
extern const AtomicString& kPassword;
extern const AtomicString& kRadio;
extern const AtomicString& kRange;
extern const AtomicString& kReset;
extern const AtomicString& kSearch;
extern const AtomicString& kSubmit;
extern const AtomicString& kTel;
extern const AtomicString& kText;
extern const AtomicString& kTime;
extern const AtomicString& kUrl;
extern const AtomicString& kWeek;

constexpr unsigned kNamesCount = 23;

void Init();


}  // namespace blink::input_type_names

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_
