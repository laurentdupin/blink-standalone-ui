// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::input_type_names {

inline const AtomicString& kImage = *new AtomicString("image");
inline const AtomicString& kFile = *new AtomicString("file");

}  // namespace blink::input_type_names

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_INPUT_TYPE_NAMES_H_
