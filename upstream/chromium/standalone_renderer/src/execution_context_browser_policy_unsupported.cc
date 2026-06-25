// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Browser policy, CSP reporting, blob URL IPC, and sanitized JS exception
// helpers are outside the Phase 1 renderer path. These definitions keep active
// core ExecutionContext code linkable without enabling browser/network/DevTools
// runtime.

#include "third_party/blink/renderer/core/frame/csp/execution_context_csp_delegate.h"

#include <optional>
#include <utility>

#include "base/check.h"
#include "third_party/blink/public/common/permissions_policy/policy_value.h"
#include "third_party/blink/renderer/core/events/error_event.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/execution_context/security_context.h"
#include "third_party/blink/renderer/core/fileapi/public_url_manager.h"
#include "third_party/blink/renderer/core/fileapi/url_registry.h"
#include "third_party/blink/renderer/core/frame/integrity_policy.h"
#include "third_party/blink/renderer/core/inspector/inspector_audits_issue.h"
#include "third_party/blink/renderer/platform/bindings/exception_messages.h"
#include "third_party/blink/renderer/platform/bindings/source_location.h"
#include "third_party/blink/renderer/platform/heap/visitor.h"
#include "third_party/blink/renderer/platform/weborigin/scheme_registry.h"

namespace blink {

void AuditsIssue::ReportSharedArrayBufferIssue(
    ExecutionContext*,
    bool,
    SharedArrayBufferIssueType) {}

ErrorEvent* ErrorEvent::CreateSanitizedError(ScriptState*) {
  return nullptr;
}

void IntegrityPolicy::LogParsingErrorsIfAny(ExecutionContext*,
                                            const network::IntegrityPolicy&) {}

SecurityContext::FeatureStatus SecurityContext::IsFeatureEnabled(
    network::mojom::PermissionsPolicyFeature) const {
  return {false, false, String()};
}

bool SecurityContext::IsFeatureEnabled(
    mojom::blink::DocumentPolicyFeature) const {
  return false;
}

SecurityContext::FeatureStatus SecurityContext::IsFeatureEnabled(
    mojom::blink::DocumentPolicyFeature,
    PolicyValue) const {
  return {false, false, String()};
}

void SecurityContext::Trace(Visitor*) const {}

ExecutionContextCSPDelegate::ExecutionContextCSPDelegate(
    ExecutionContext& execution_context)
    : execution_context_(&execution_context) {}

void ExecutionContextCSPDelegate::Trace(Visitor* visitor) const {
  visitor->Trace(execution_context_);
}

const SecurityOrigin* ExecutionContextCSPDelegate::GetSecurityOrigin() {
  return execution_context_ ? execution_context_->GetSecurityOrigin() : nullptr;
}

const KURL& ExecutionContextCSPDelegate::Url() const {
  return execution_context_->Url();
}

void ExecutionContextCSPDelegate::SetSandboxFlags(
    network::mojom::blink::WebSandboxFlags) {}

void ExecutionContextCSPDelegate::SetRequireTrustedTypes() {}

void ExecutionContextCSPDelegate::AddInsecureRequestPolicy(
    mojom::blink::InsecureRequestPolicy) {}

SourceLocation* ExecutionContextCSPDelegate::GetSourceLocation() {
  return nullptr;
}

std::optional<uint16_t> ExecutionContextCSPDelegate::GetStatusCode() {
  return std::nullopt;
}

String ExecutionContextCSPDelegate::GetDocumentReferrer() {
  return String();
}

void ExecutionContextCSPDelegate::DispatchViolationEvent(
    const SecurityPolicyViolationEventInit&,
    Element*) {}

void ExecutionContextCSPDelegate::PostViolationReport(
    const SecurityPolicyViolationEventInit&,
    const String&,
    bool,
    const Vector<String>&,
    bool) {}

void ExecutionContextCSPDelegate::Count(WebFeature) {}

void ExecutionContextCSPDelegate::AddConsoleMessage(ConsoleMessage*) {}

void ExecutionContextCSPDelegate::AddInspectorIssue(AuditsIssue) {}

void ExecutionContextCSPDelegate::DisableEval(const String&) {}

void ExecutionContextCSPDelegate::SetWasmEvalErrorMessage(const String&) {}

void ExecutionContextCSPDelegate::ReportBlockedScriptExecutionToInspector(
    const String&) {}

void ExecutionContextCSPDelegate::DidAddContentSecurityPolicies(
    Vector<network::mojom::blink::ContentSecurityPolicyPtr>) {}

bool ExecutionContextCSPDelegate::ScriptSrcExtendedHashesEnabled() {
  return false;
}

PublicURLManager::PublicURLManager(ExecutionContext* execution_context)
    : ExecutionContextLifecycleObserver(execution_context),
      is_stopped_(true),
      frame_url_store_(execution_context),
      worker_url_store_(execution_context) {}

PublicURLManager::PublicURLManager(
    base::PassKey<GlobalStorageAccessHandle>,
    ExecutionContext* execution_context,
    mojo::PendingAssociatedRemote<mojom::blink::BlobURLStore>)
    : ExecutionContextLifecycleObserver(execution_context),
      is_stopped_(true),
      frame_url_store_(execution_context),
      worker_url_store_(execution_context) {}

String PublicURLManager::RegisterURL(URLRegistrable*) {
  return String();
}

void PublicURLManager::Revoke(const KURL&) {}

void PublicURLManager::Resolve(
    const KURL&,
    mojo::PendingReceiver<network::mojom::blink::URLLoaderFactory>) {}

void PublicURLManager::ContextDestroyed() {
  is_stopped_ = true;
  mojo_urls_.clear();
}

void PublicURLManager::Trace(Visitor* visitor) const {
  ExecutionContextLifecycleObserver::Trace(visitor);
  visitor->Trace(frame_url_store_);
  visitor->Trace(worker_url_store_);
}

mojom::blink::BlobURLStore& PublicURLManager::GetBlobURLStore() {
  CHECK(false);
  static mojom::blink::BlobURLStore* unsupported_store = nullptr;
  return *unsupported_store;
}

String ExceptionMessages::AddContextToMessage(v8::ExceptionContext,
                                              const char*,
                                              const String&,
                                              const String& message) {
  return message;
}

}  // namespace blink
