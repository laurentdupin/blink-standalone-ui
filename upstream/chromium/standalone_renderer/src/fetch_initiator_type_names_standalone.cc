// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Standalone generated-name owner for fetch initiator names. This mirrors
// Blink's generated make_names output so AtomicString storage is installed only
// from CoreInitializer::Initialize(), after WTF static strings are ready.

#include "third_party/blink/renderer/platform/loader/fetch/fetch_initiator_type_names.h"

#include <iterator>

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/text/string_impl.h"

namespace blink::fetch_initiator_type_names {

void* names_storage[kNamesCount *
                    ((sizeof(AtomicString) + sizeof(void*) - 1) /
                     sizeof(void*))];

const AtomicString& kAttributionsrc =
    reinterpret_cast<AtomicString*>(&names_storage)[0];
const AtomicString& kAudio = reinterpret_cast<AtomicString*>(&names_storage)[1];
const AtomicString& kBeacon =
    reinterpret_cast<AtomicString*>(&names_storage)[2];
const AtomicString& kCss = reinterpret_cast<AtomicString*>(&names_storage)[3];
const AtomicString& kCSS = kCss;
const AtomicString& kDocument =
    reinterpret_cast<AtomicString*>(&names_storage)[4];
const AtomicString& kIcon = reinterpret_cast<AtomicString*>(&names_storage)[5];
const AtomicString& kInternal =
    reinterpret_cast<AtomicString*>(&names_storage)[6];
const AtomicString& kFetch = reinterpret_cast<AtomicString*>(&names_storage)[7];
const AtomicString& kLink = reinterpret_cast<AtomicString*>(&names_storage)[8];
const AtomicString& kOther = reinterpret_cast<AtomicString*>(&names_storage)[9];
const AtomicString& kPing = reinterpret_cast<AtomicString*>(&names_storage)[10];
const AtomicString& kProcessinginstruction =
    reinterpret_cast<AtomicString*>(&names_storage)[11];
const AtomicString& kScript =
    reinterpret_cast<AtomicString*>(&names_storage)[12];
const AtomicString& kTrack =
    reinterpret_cast<AtomicString*>(&names_storage)[13];
const AtomicString& kUacss =
    reinterpret_cast<AtomicString*>(&names_storage)[14];
const AtomicString& kUse = reinterpret_cast<AtomicString*>(&names_storage)[15];
const AtomicString& kViolationreport =
    reinterpret_cast<AtomicString*>(&names_storage)[16];
const AtomicString& kVideo =
    reinterpret_cast<AtomicString*>(&names_storage)[17];
const AtomicString& kXml = reinterpret_cast<AtomicString*>(&names_storage)[18];
const AtomicString& kXmlhttprequest =
    reinterpret_cast<AtomicString*>(&names_storage)[19];

void Init() {
  static bool is_loaded = false;
  if (is_loaded) {
    return;
  }
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
      {"attributionsrc", 14},
      {"audio", 5},
      {"beacon", 6},
      {"css", 3},
      {"document", 8},
      {"icon", 4},
      {"internal", 8},
      {"fetch", 5},
      {"link", 4},
      {"other", 5},
      {"ping", 4},
      {"processinginstruction", 21},
      {"script", 6},
      {"track", 5},
      {"uacss", 5},
      {"use", 3},
      {"violationreport", 15},
      {"video", 5},
      {"xml", 3},
      {"xmlhttprequest", 14},
  };

  static_assert(std::size(kNames) == kNamesCount,
                "Fetch initiator name storage must match kNamesCount.");

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl =
        StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    void* address = reinterpret_cast<AtomicString*>(&names_storage) + i;
    new (address) AtomicString(impl);
  }
}

}  // namespace blink::fetch_initiator_type_names
