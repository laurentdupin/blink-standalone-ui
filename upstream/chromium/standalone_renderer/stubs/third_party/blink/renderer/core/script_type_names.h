// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_SCRIPT_TYPE_NAMES_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_SCRIPT_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::script_type_names {

inline const AtomicString& kClassic = *new AtomicString("classic");
inline const AtomicString& kImportmap = *new AtomicString("importmap");
inline const AtomicString& kModule = *new AtomicString("module");
inline const AtomicString& kRoutemap = *new AtomicString("routemap");
inline const AtomicString& kSpeculationrules =
    *new AtomicString("speculationrules");
inline const AtomicString& kWebbundle = *new AtomicString("webbundle");

}  // namespace blink::script_type_names

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_SCRIPT_TYPE_NAMES_H_
