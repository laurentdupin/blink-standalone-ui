// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// document.write() intervention is browser/network/script-fetch policy. The
// standalone renderer has no network fetch path and does not enable script
// execution optimizations in Phase 1, so this boundary leaves document-written
// scripts to the existing local loader policy and does not issue intervention
// fetches.

#include "third_party/blink/renderer/core/script/document_write_intervention.h"

namespace blink {

bool MaybeDisallowFetchForDocWrittenScript(FetchParameters&, Document&) {
  return false;
}

void PossiblyFetchBlockedDocWriteScript(const Resource*,
                                        Document&,
                                        const ScriptFetchOptions&,
                                        CrossOriginAttributeValue) {}

}  // namespace blink
