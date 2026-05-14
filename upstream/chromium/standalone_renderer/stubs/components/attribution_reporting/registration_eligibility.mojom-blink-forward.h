// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_COMPONENTS_ATTRIBUTION_REPORTING_REGISTRATION_ELIGIBILITY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_COMPONENTS_ATTRIBUTION_REPORTING_REGISTRATION_ELIGIBILITY_MOJOM_BLINK_FORWARD_H_

namespace attribution_reporting::mojom {

enum class RegistrationEligibility {
  kSource,
  kTrigger,
  kSourceOrTrigger,
};

}  // namespace attribution_reporting::mojom

namespace attribution_reporting::mojom::blink {

using RegistrationEligibility = ::attribution_reporting::mojom::RegistrationEligibility;

}  // namespace attribution_reporting::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_COMPONENTS_ATTRIBUTION_REPORTING_REGISTRATION_ELIGIBILITY_MOJOM_BLINK_FORWARD_H_
