// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_INSPECTOR_PROTOCOL_AUDITS_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_INSPECTOR_PROTOCOL_AUDITS_H_

namespace blink::protocol::Audits {

class InspectorIssue {};

enum class GenericIssueErrorType {
  kUnknown,
};

enum class PropertyRuleIssueReason {
  kInvalidSyntax,
};

enum class PermissionElementIssueType {
  kUnknown,
};

}  // namespace blink::protocol::Audits

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_CORE_INSPECTOR_PROTOCOL_AUDITS_H_
