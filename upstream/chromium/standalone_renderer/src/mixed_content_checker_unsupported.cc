// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// External network loading and browser-side mixed-content enforcement are
// unsupported in Phase 1. The standalone resource boundary rejects network
// fetches; these owners keep Blink rendering code linked without importing
// Network Service, CSP, worker-fetch, or DevTools issue runtime.

#include "third_party/blink/renderer/core/loader/mixed_content_checker.h"

#include "third_party/blink/public/mojom/loader/mixed_content.mojom-blink.h"

namespace blink {

bool MixedContentChecker::ShouldBlockFetch(
    LocalFrame*,
    mojom::blink::RequestContextType,
    network::mojom::blink::IPAddressSpace,
    const KURL&,
    ResourceRequest::RedirectStatus,
    const KURL&,
    const String&,
    ReportingDisposition,
    mojom::blink::ContentSecurityNotifier&) {
  return false;
}

bool MixedContentChecker::ShouldBlockFetchOnWorker(
    WorkerFetchContext&,
    mojom::blink::RequestContextType,
    const KURL&,
    ResourceRequest::RedirectStatus,
    const KURL&,
    ReportingDisposition,
    bool) {
  return false;
}

bool MixedContentChecker::IsWebSocketAllowed(const FrameFetchContext&,
                                             LocalFrame*,
                                             const KURL&) {
  return false;
}

bool MixedContentChecker::IsWebSocketAllowed(WorkerFetchContext&,
                                             const KURL&) {
  return false;
}

bool MixedContentChecker::IsMixedContent(const SecurityOrigin*, const KURL&) {
  return false;
}

bool MixedContentChecker::IsMixedContent(const String&, const KURL&) {
  return false;
}

bool MixedContentChecker::IsMixedContent(const FetchClientSettingsObject&,
                                         const KURL&) {
  return false;
}

bool MixedContentChecker::IsMixedFormAction(LocalFrame*,
                                            const KURL&,
                                            ReportingDisposition) {
  return false;
}

bool MixedContentChecker::ShouldAutoupgrade(
    const FetchClientSettingsObject*,
    mojom::blink::RequestContextType,
    WebContentSettingsClient*,
    const ResourceRequest&,
    ExecutionContext*,
    LocalFrame*) {
  return false;
}

mojom::blink::MixedContentContextType
MixedContentChecker::ContextTypeForInspector(LocalFrame*,
                                             const ResourceRequest&) {
  return mojom::blink::MixedContentContextType::kNotMixedContent;
}

void MixedContentChecker::HandleCertificateError(
    const ResourceResponse&,
    mojom::blink::RequestContextType,
    MixedContent::CheckModeForPlugin,
    mojom::blink::ContentSecurityNotifier&) {}

void MixedContentChecker::MixedContentFound(LocalFrame*,
                                            const KURL&,
                                            const KURL&,
                                            mojom::blink::RequestContextType,
                                            bool,
                                            const KURL&,
                                            bool,
                                            SourceLocation*) {}

ConsoleMessage* MixedContentChecker::CreateConsoleMessageAboutFetchAutoupgrade(
    const KURL&,
    const KURL&) {
  return nullptr;
}

ConsoleMessage*
MixedContentChecker::CreateConsoleMessageAboutFetchIPAddressNoAutoupgrade(
    const KURL&,
    const KURL&) {
  return nullptr;
}

ConsoleMessage*
MixedContentChecker::CreateConsoleMessageAboutFetchLocalNetworkNoAutoupgrade(
    const KURL&,
    const KURL&) {
  return nullptr;
}

void MixedContentChecker::UpgradeInsecureRequest(
    ResourceRequest&,
    const FetchClientSettingsObject*,
    ExecutionContext*,
    mojom::RequestContextFrameType,
    WebContentSettingsClient*,
    LocalFrame*) {}

MixedContent::CheckModeForPlugin MixedContentChecker::DecideCheckModeForPlugin(
    Settings*) {
  return MixedContent::CheckModeForPlugin::kStrict;
}

mojom::blink::MixedContentContextType MixedContent::ContextTypeFromRequestContext(
    mojom::RequestContextType,
    CheckModeForPlugin) {
  return mojom::blink::MixedContentContextType::kNotMixedContent;
}

}  // namespace blink
