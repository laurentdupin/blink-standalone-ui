// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_FETCH_INITIATOR_TYPE_NAMES_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_FETCH_INITIATOR_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::fetch_initiator_type_names {

extern const AtomicString& kAttributionsrc;
extern const AtomicString& kAudio;
extern const AtomicString& kBeacon;
extern const AtomicString& kCss;
extern const AtomicString& kCSS;
extern const AtomicString& kDocument;
extern const AtomicString& kIcon;
extern const AtomicString& kInternal;
extern const AtomicString& kFetch;
extern const AtomicString& kLink;
extern const AtomicString& kOther;
extern const AtomicString& kPing;
extern const AtomicString& kProcessinginstruction;
extern const AtomicString& kScript;
extern const AtomicString& kTrack;
extern const AtomicString& kUacss;
extern const AtomicString& kUse;
extern const AtomicString& kViolationreport;
extern const AtomicString& kVideo;
extern const AtomicString& kXml;
extern const AtomicString& kXmlhttprequest;

constexpr unsigned kNamesCount = 20;

void Init();

}  // namespace blink::fetch_initiator_type_names

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_FETCH_INITIATOR_TYPE_NAMES_H_
