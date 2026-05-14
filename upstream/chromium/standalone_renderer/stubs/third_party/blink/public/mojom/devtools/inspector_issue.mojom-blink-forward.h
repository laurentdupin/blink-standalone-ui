// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_INSPECTOR_ISSUE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_INSPECTOR_ISSUE_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"

namespace blink::mojom::blink {

enum class InspectorIssueCode;
enum class AttributionReportingIssueType;
enum class GenericIssueErrorType;
enum class PartitioningBlobURLInfo;
class InspectorIssueDetails;
class InspectorIssueInfo;

using InspectorIssueDetailsPtr = mojo::StructPtr<InspectorIssueDetails>;
using InspectorIssueInfoPtr = mojo::StructPtr<InspectorIssueInfo>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_INSPECTOR_ISSUE_MOJOM_BLINK_FORWARD_H_
