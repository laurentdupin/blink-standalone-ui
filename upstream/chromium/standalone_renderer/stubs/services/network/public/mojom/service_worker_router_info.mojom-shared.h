// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SERVICE_WORKER_ROUTER_INFO_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SERVICE_WORKER_ROUTER_INFO_MOJOM_SHARED_H_

namespace network::mojom {

enum class ServiceWorkerRouterSourceType {
  kNetwork,
  kRaceNetworkAndFetchEvent,
  kFetchEvent,
  kCache,
  kRaceNetworkAndCache,
};

enum class ServiceWorkerStatus {
  kRunning,
  kStarting,
  kStopping,
  kStopped,
  kWarmingUp,
  kWarmedUp,
};

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SERVICE_WORKER_ROUTER_INFO_MOJOM_SHARED_H_
