// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SERVICE_WORKER_ROUTER_INFO_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SERVICE_WORKER_ROUTER_INFO_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"
#include "services/network/public/mojom/service_worker_router_info.mojom-shared.h"

namespace network::mojom::blink {

class ServiceWorkerRouterInfo;
using ServiceWorkerRouterInfoPtr = mojo::StructPtr<ServiceWorkerRouterInfo>;

}  // namespace network::mojom::blink

namespace blink::network::mojom {

using ServiceWorkerRouterSourceType =
    ::network::mojom::ServiceWorkerRouterSourceType;
using ServiceWorkerStatus = ::network::mojom::ServiceWorkerStatus;

}  // namespace blink::network::mojom

namespace blink::network::mojom::blink {

using ServiceWorkerRouterInfoPtr =
    ::network::mojom::blink::ServiceWorkerRouterInfoPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SERVICE_WORKER_ROUTER_INFO_MOJOM_BLINK_FORWARD_H_
