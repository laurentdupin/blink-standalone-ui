// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_SCRIPT_TYPE_NAMES_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_SCRIPT_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::script_type_names {
extern const AtomicString& kClassic;
extern const AtomicString& kImportmap;
extern const AtomicString& kModule;
extern const AtomicString& kRoutemap;
extern const AtomicString& kSpeculationrules;
extern const AtomicString& kWebbundle;

constexpr unsigned kNamesCount = 6;

void Init();


}  // namespace blink::script_type_names

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_SCRIPT_TYPE_NAMES_H_
