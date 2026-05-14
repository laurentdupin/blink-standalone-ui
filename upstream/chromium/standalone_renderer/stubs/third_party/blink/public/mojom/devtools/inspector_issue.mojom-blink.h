// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_INSPECTOR_ISSUE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_INSPECTOR_ISSUE_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/devtools/inspector_issue.mojom-blink-forward.h"

namespace blink::mojom::blink {

enum class InspectorIssueCode {
  kGenericIssue,
  kPartitioningBlobURLIssue,
};

enum class ContentSecurityPolicyViolationType {
  kInlineViolation,
  kEvalViolation,
  kURLViolation,
  kSRIViolation,
  kTrustedTypesSinkViolation,
  kTrustedTypesPolicyViolation,
  kWasmEvalViolation,
};

enum class AttributionReportingIssueType {
  kPermissionPolicyDisabled,
};

enum class GenericIssueErrorType {
  kUnknown,
};

enum class PartitioningBlobURLInfo {
  kBlockedCrossPartitionFetching,
  kEnforceNoopenerForNavigation,
};

class InspectorIssueDetails {};

class InspectorIssueInfo {
 public:
  InspectorIssueCode code = InspectorIssueCode::kGenericIssue;
  InspectorIssueDetailsPtr details;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_INSPECTOR_ISSUE_MOJOM_BLINK_H_
