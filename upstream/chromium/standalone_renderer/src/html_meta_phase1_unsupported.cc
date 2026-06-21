// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 keeps HTML parsing and rendering metadata such as viewport/theme
// handling, but browser policy/network metadata processing is unsupported.
// These no-op owners prevent <meta http-equiv>, Client Hints delegation, and
// permissions-policy updates from importing network/browser runtimes.

#include "third_party/blink/renderer/core/html/client_hints_util.h"
#include "third_party/blink/renderer/core/loader/http_equiv.h"

namespace blink {

void HttpEquiv::Process(Document&,
                        const AtomicString&,
                        const AtomicString&,
                        bool,
                        bool,
                        Element*) {}

void UpdateWindowPermissionsPolicyWithDelegationSupportForClientHints(
    ClientHintsPreferences&,
    LocalDOMWindow*,
    const String&,
    const KURL&,
    ClientHintsPreferences::Context*,
    network::MetaCHType,
    bool,
    bool) {}

void UpdateIFrameContainerPolicyWithDelegationSupportForClientHints(
    network::ParsedPermissionsPolicy&,
    LocalDOMWindow*) {}

}  // namespace blink
