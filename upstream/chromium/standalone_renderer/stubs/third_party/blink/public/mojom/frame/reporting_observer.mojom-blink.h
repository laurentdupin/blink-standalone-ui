// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REPORTING_OBSERVER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REPORTING_OBSERVER_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/frame/reporting_observer.mojom-blink-forward.h"

namespace blink::mojom::blink {

class ReportBodyElement {};
class ReportBody {};
class Report {};

class ReportingObserver {
 public:
  class Proxy_ {};
  virtual ~ReportingObserver() = default;
  virtual void Notify(ReportPtr) {}
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REPORTING_OBSERVER_MOJOM_BLINK_H_
