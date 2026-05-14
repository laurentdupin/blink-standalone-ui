// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SERVICES_NETWORK_PUBLIC_MOJOM_WEB_SANDBOX_FLAGS_MOJOM_SHARED_H_
#define SERVICES_NETWORK_PUBLIC_MOJOM_WEB_SANDBOX_FLAGS_MOJOM_SHARED_H_

#include <cstdint>

namespace network::mojom {

enum class WebSandboxFlags : int32_t {
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
  kAll = -1,
};

}  // namespace network::mojom

#endif  // SERVICES_NETWORK_PUBLIC_MOJOM_WEB_SANDBOX_FLAGS_MOJOM_SHARED_H_
