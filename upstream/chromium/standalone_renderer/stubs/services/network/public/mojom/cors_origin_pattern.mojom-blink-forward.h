// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SERVICES_NETWORK_PUBLIC_MOJOM_CORS_ORIGIN_PATTERN_MOJOM_BLINK_FORWARD_H_
#define SERVICES_NETWORK_PUBLIC_MOJOM_CORS_ORIGIN_PATTERN_MOJOM_BLINK_FORWARD_H_

namespace network::mojom::blink {

class CorsOriginPattern;

}  // namespace network::mojom::blink

namespace network::mojom {

#ifndef STANDALONE_RENDERER_HAS_CORS_ORIGIN_PATTERN_ENUMS
enum class CorsDomainMatchMode {
  kDisallowSubdomains,
  kAllowSubdomains,
  kAllowRegistrableDomains,
};

enum class CorsPortMatchMode {
  kAllowOnlySpecifiedPort,
  kAllowAnyPort,
};

enum class CorsOriginAccessMatchPriority {
  kDefaultPriority,
  kLowPriority,
};
#endif

}  // namespace network::mojom

namespace network::mojom::blink {

using ::network::mojom::CorsDomainMatchMode;
using ::network::mojom::CorsOriginAccessMatchPriority;
using ::network::mojom::CorsPortMatchMode;

}  // namespace network::mojom::blink

#endif  // SERVICES_NETWORK_PUBLIC_MOJOM_CORS_ORIGIN_PATTERN_MOJOM_BLINK_FORWARD_H_
