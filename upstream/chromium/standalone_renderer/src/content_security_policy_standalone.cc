// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/loader/fetch/integrity_metadata.h"

namespace blink {
using IntegrityAlgorithm = ::network::mojom::blink::IntegrityAlgorithm;
}  // namespace blink

#include "third_party/blink/renderer/core/frame/csp/content_security_policy.h"

namespace blink {

ContentSecurityPolicy::ContentSecurityPolicy() = default;
ContentSecurityPolicy::~ContentSecurityPolicy() = default;

void ContentSecurityPolicy::Trace(Visitor*) const {}

bool ContentSecurityPolicy::IsBound() {
  return false;
}

void ContentSecurityPolicy::BindToDelegate(ContentSecurityPolicyDelegate&) {}

void ContentSecurityPolicy::AddPolicies(
    Vector<network::mojom::blink::ContentSecurityPolicyPtr>) {}

bool ContentSecurityPolicy::ShouldCheckEval() const {
  return false;
}

bool ContentSecurityPolicy::AllowEval(ReportingDisposition,
                                      ContentSecurityPolicy::ExceptionStatus,
                                      const String&) {
  return true;
}

bool ContentSecurityPolicy::IsActive() const {
  return false;
}

bool ContentSecurityPolicy::IsActiveForConnections() const {
  return false;
}

bool ContentSecurityPolicy::AllowImageFromSource(
    const KURL&,
    const KURL&,
    RedirectStatus,
    ReportingDisposition,
    ContentSecurityPolicy::CheckHeaderType) {
  return true;
}

bool ContentSecurityPolicy::AllowScriptFromSource(
    const KURL&,
    const String&,
    const IntegrityMetadataSet&,
    ParserDisposition,
    const KURL&,
    RedirectStatus,
    ReportingDisposition,
    ContentSecurityPolicy::CheckHeaderType) {
  return true;
}

}  // namespace blink
