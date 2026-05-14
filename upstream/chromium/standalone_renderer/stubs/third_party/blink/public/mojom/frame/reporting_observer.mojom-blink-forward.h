// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REPORTING_OBSERVER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REPORTING_OBSERVER_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"

namespace blink::mojom::blink {

class ReportBodyElement;
class ReportBody;
class Report;
class ReportingObserver;

using ReportBodyElementPtr = mojo::StructPtr<ReportBodyElement>;
using ReportBodyPtr = mojo::StructPtr<ReportBody>;
using ReportPtr = mojo::StructPtr<Report>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REPORTING_OBSERVER_MOJOM_BLINK_FORWARD_H_
