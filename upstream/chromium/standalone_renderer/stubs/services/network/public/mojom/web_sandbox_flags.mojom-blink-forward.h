// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_SANDBOX_FLAGS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_SANDBOX_FLAGS_MOJOM_BLINK_FORWARD_H_

#include <cstdint>

namespace network::mojom::blink {

enum class WebSandboxFlags : uint32_t {
  kNone = 0,
  kNavigation = 1 << 0,
  kPlugins = 1 << 1,
  kOrigin = 1 << 2,
  kForms = 1 << 3,
  kScripts = 1 << 4,
  kTopNavigation = 1 << 5,
  kPopups = 1 << 6,
  kPointerLock = 1 << 7,
  kAutomaticFeatures = 1 << 8,
  kDocumentDomain = 1 << 9,
  kModals = 1 << 10,
  kDownloads = 1 << 11,
  kPropagatesToAuxiliaryBrowsingContexts = 1 << 12,
  kTopNavigationByUserActivation = 1 << 13,
  kAll = 0xffffffffu,
};

constexpr WebSandboxFlags operator|(WebSandboxFlags lhs,
                                    WebSandboxFlags rhs) {
  return static_cast<WebSandboxFlags>(static_cast<uint32_t>(lhs) |
                                      static_cast<uint32_t>(rhs));
}

constexpr WebSandboxFlags operator&(WebSandboxFlags lhs,
                                    WebSandboxFlags rhs) {
  return static_cast<WebSandboxFlags>(static_cast<uint32_t>(lhs) &
                                      static_cast<uint32_t>(rhs));
}

constexpr WebSandboxFlags operator~(WebSandboxFlags value) {
  return static_cast<WebSandboxFlags>(~static_cast<uint32_t>(value));
}

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {
using WebSandboxFlags = ::network::mojom::blink::WebSandboxFlags;
}

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_SANDBOX_FLAGS_MOJOM_BLINK_FORWARD_H_
