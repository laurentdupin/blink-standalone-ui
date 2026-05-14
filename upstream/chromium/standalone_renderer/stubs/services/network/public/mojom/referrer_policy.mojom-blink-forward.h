// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Standalone renderer compile-time stub. This intentionally provides only the
// enum surface needed by Blink core headers; the runtime must never link
// network service implementations.

#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_REFERRER_POLICY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_REFERRER_POLICY_MOJOM_BLINK_FORWARD_H_

#define BLINK_STANDALONE_REFERRER_POLICY_ENUM_DEFINED

namespace network::mojom {

enum class ReferrerPolicy {
  kAlways,
  kDefault,
  kNever,
  kNoReferrerWhenDowngrade,
  kOrigin,
  kOriginWhenCrossOrigin,
  kSameOrigin,
  kStrictOrigin,
  kStrictOriginWhenCrossOrigin,
};

}  // namespace network::mojom

namespace network::mojom::blink {

using ReferrerPolicy = ::network::mojom::ReferrerPolicy;

}  // namespace network::mojom::blink

namespace blink::network::mojom {

using ReferrerPolicy = ::network::mojom::ReferrerPolicy;

}  // namespace blink::network::mojom

namespace blink::network::mojom::blink {

using ReferrerPolicy = ::network::mojom::blink::ReferrerPolicy;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_REFERRER_POLICY_MOJOM_BLINK_FORWARD_H_
