// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::input_type_names {

inline const AtomicString& kButton = *new AtomicString("button");
inline const AtomicString& kCheckbox = *new AtomicString("checkbox");
inline const AtomicString& kColor = *new AtomicString("color");
inline const AtomicString& kDate = *new AtomicString("date");
inline const AtomicString& kDatetime = *new AtomicString("datetime");
inline const AtomicString& kDatetimeLocal = *new AtomicString("datetime-local");
inline const AtomicString& kEmail = *new AtomicString("email");
inline const AtomicString& kImage = *new AtomicString("image");
inline const AtomicString& kFile = *new AtomicString("file");
inline const AtomicString& kHidden = *new AtomicString("hidden");
inline const AtomicString& kMonth = *new AtomicString("month");
inline const AtomicString& kNumber = *new AtomicString("number");
inline const AtomicString& kPassword = *new AtomicString("password");
inline const AtomicString& kRadio = *new AtomicString("radio");
inline const AtomicString& kRange = *new AtomicString("range");
inline const AtomicString& kReset = *new AtomicString("reset");
inline const AtomicString& kSearch = *new AtomicString("search");
inline const AtomicString& kSubmit = *new AtomicString("submit");
inline const AtomicString& kTel = *new AtomicString("tel");
inline const AtomicString& kText = *new AtomicString("text");
inline const AtomicString& kTime = *new AtomicString("time");
inline const AtomicString& kUrl = *new AtomicString("url");
inline const AtomicString& kWeek = *new AtomicString("week");

}  // namespace blink::input_type_names

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_
