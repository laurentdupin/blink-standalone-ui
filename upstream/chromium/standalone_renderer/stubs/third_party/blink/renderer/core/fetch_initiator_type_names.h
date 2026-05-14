// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_INITIATOR_TYPE_NAMES_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_INITIATOR_TYPE_NAMES_H_

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"

namespace blink::fetch_initiator_type_names {

inline const AtomicString& kAttributionsrc = *new AtomicString("attributionsrc");
inline const AtomicString& kAudio = *new AtomicString("audio");
inline const AtomicString& kBeacon = *new AtomicString("beacon");
inline const AtomicString& kCss = *new AtomicString("css");
inline const AtomicString& kDocument = *new AtomicString("document");
inline const AtomicString& kIcon = *new AtomicString("icon");
inline const AtomicString& kInternal = *new AtomicString("internal");
inline const AtomicString& kFetch = *new AtomicString("fetch");
inline const AtomicString& kLink = *new AtomicString("link");
inline const AtomicString& kOther = *new AtomicString("other");
inline const AtomicString& kPing = *new AtomicString("ping");
inline const AtomicString& kProcessinginstruction = *new AtomicString("processinginstruction");
inline const AtomicString& kScript = *new AtomicString("script");
inline const AtomicString& kTrack = *new AtomicString("track");
inline const AtomicString& kUacss = *new AtomicString("uacss");
inline const AtomicString& kUse = *new AtomicString("use");
inline const AtomicString& kViolationreport = *new AtomicString("violationreport");
inline const AtomicString& kVideo = *new AtomicString("video");
inline const AtomicString& kXml = *new AtomicString("xml");
inline const AtomicString& kXmlhttprequest = *new AtomicString("xmlhttprequest");
inline constexpr unsigned kNamesCount = 20;

}  // namespace blink::fetch_initiator_type_names

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_FETCH_INITIATOR_TYPE_NAMES_H_
