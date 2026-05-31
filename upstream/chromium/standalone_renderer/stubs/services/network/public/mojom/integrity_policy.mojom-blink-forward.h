// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_INTEGRITY_POLICY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_INTEGRITY_POLICY_MOJOM_BLINK_FORWARD_H_

#include <memory>
#include <string>
#include <vector>

#include "services/network/public/mojom/integrity_policy.mojom-shared.h"

namespace network::mojom::blink {

struct IntegrityPolicy {
  using Destination = ::network::mojom::IntegrityPolicy_Destination;
  using Source = ::network::mojom::IntegrityPolicy_Source;

  std::vector<Destination> blocked_destinations;
  std::vector<Source> sources;
  std::vector<std::string> endpoints;
  std::vector<std::string> parsing_errors;

  template <typename... Args>
  static std::unique_ptr<IntegrityPolicy> New(Args&&...) {
    return std::make_unique<IntegrityPolicy>();
  }
};
using IntegrityPolicyPtr = std::unique_ptr<IntegrityPolicy>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using IntegrityPolicy = ::network::mojom::blink::IntegrityPolicy;
using IntegrityPolicyPtr = ::network::mojom::blink::IntegrityPolicyPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_INTEGRITY_POLICY_MOJOM_BLINK_FORWARD_H_
