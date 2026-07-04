// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// External network loading and browser-side mixed-content enforcement are
// unsupported in Phase 1. The standalone resource boundary rejects network
// fetches; these owners keep Blink rendering code linked without importing
// Network Service, CSP, worker-fetch, or DevTools issue runtime.

#include "third_party/blink/renderer/core/loader/mixed_content_checker.h"

#include "base/notreached.h"
#include "net/base/url_util.h"
#include "third_party/blink/public/mojom/fetch/fetch_api_request.mojom-blink.h"
#include "third_party/blink/public/mojom/loader/mixed_content.mojom-blink.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_client_settings_object.h"
#include "third_party/blink/renderer/platform/loader/fetch/https_state.h"
#include "third_party/blink/renderer/platform/weborigin/scheme_registry.h"
#include "third_party/blink/renderer/platform/weborigin/security_origin.h"
#include "url/gurl.h"
#include "url/url_constants.h"

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

namespace {

bool StandaloneIsPotentiallyTrustworthyUrl(const KURL& url) {
  if (url.ProtocolIsData()) {
    return true;
  }

  const GURL gurl(url);
  if (gurl.IsAboutBlank() || gurl.IsAboutSrcdoc()) {
    return true;
  }
  if (gurl.SchemeIs(url::kHttpsScheme) || gurl.SchemeIs(url::kWssScheme) ||
      gurl.SchemeIs(url::kFileScheme)) {
    return true;
  }
  if (net::IsLocalhost(gurl)) {
    return true;
  }
  return SchemeRegistry::SchemeShouldBypassSecureContextCheck(url.Protocol());
}

bool StandaloneIsInsecureUrl(const KURL& url) {
  return !StandaloneIsPotentiallyTrustworthyUrl(url);
}

}  // namespace

bool MixedContentChecker::IsMixedContent(const SecurityOrigin* security_origin,
                                         const KURL& url) {
  if (!security_origin)
    return false;
  return IsMixedContent(
      security_origin->GetOriginOrPrecursorOriginIfOpaque()->Protocol(), url);
}

bool MixedContentChecker::IsMixedContent(const String& origin_protocol,
                                         const KURL& url) {
  if (!SchemeRegistry::ShouldTreatURLSchemeAsRestrictingMixedContent(
          origin_protocol)) {
    return false;
  }
  return StandaloneIsInsecureUrl(url);
}

bool MixedContentChecker::IsMixedContent(
    const FetchClientSettingsObject& settings,
    const KURL& url) {
  switch (settings.GetHttpsState()) {
    case HttpsState::kNone:
      return false;
    case HttpsState::kModern:
      return StandaloneIsInsecureUrl(url);
  }
  NOTREACHED();
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
    mojom::RequestContextType context,
    CheckModeForPlugin check_mode_for_plugin) {
  switch (context) {
    case mojom::RequestContextType::AUDIO:
    case mojom::RequestContextType::IMAGE:
    case mojom::RequestContextType::VIDEO:
      return mojom::blink::MixedContentContextType::kOptionallyBlockable;

    case mojom::RequestContextType::PLUGIN:
      return check_mode_for_plugin == MixedContent::CheckModeForPlugin::kStrict
                 ? mojom::blink::MixedContentContextType::kBlockable
                 : mojom::blink::MixedContentContextType::kOptionallyBlockable;

    case mojom::RequestContextType::ATTRIBUTION_SRC:
    case mojom::RequestContextType::BEACON:
    case mojom::RequestContextType::CSP_REPORT:
    case mojom::RequestContextType::EMBED:
    case mojom::RequestContextType::EVENT_SOURCE:
    case mojom::RequestContextType::FAVICON:
    case mojom::RequestContextType::FETCH:
    case mojom::RequestContextType::FONT:
    case mojom::RequestContextType::FORM:
    case mojom::RequestContextType::FRAME:
    case mojom::RequestContextType::HYPERLINK:
    case mojom::RequestContextType::IFRAME:
    case mojom::RequestContextType::IMAGE_SET:
    case mojom::RequestContextType::INTERNAL:
    case mojom::RequestContextType::JSON:
    case mojom::RequestContextType::LOCATION:
    case mojom::RequestContextType::MANIFEST:
    case mojom::RequestContextType::OBJECT:
    case mojom::RequestContextType::PING:
    case mojom::RequestContextType::PREFETCH:
    case mojom::RequestContextType::SCRIPT:
    case mojom::RequestContextType::SERVICE_WORKER:
    case mojom::RequestContextType::SHARED_WORKER:
    case mojom::RequestContextType::SPECULATION_RULES:
    case mojom::RequestContextType::STYLE:
    case mojom::RequestContextType::SUBRESOURCE:
    case mojom::RequestContextType::SUBRESOURCE_WEBBUNDLE:
    case mojom::RequestContextType::TRACK:
    case mojom::RequestContextType::WORKER:
    case mojom::RequestContextType::XML_HTTP_REQUEST:
    case mojom::RequestContextType::XSLT:
      return mojom::blink::MixedContentContextType::kBlockable;

    case mojom::RequestContextType::DOWNLOAD:
      return mojom::blink::MixedContentContextType::kShouldBeBlockable;

    case mojom::RequestContextType::UNSPECIFIED:
      NOTREACHED();
  }
  NOTREACHED();
  return mojom::blink::MixedContentContextType::kBlockable;
}

}  // namespace blink
