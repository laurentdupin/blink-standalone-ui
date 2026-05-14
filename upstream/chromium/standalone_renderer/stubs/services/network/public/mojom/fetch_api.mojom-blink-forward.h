#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_FETCH_API_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_FETCH_API_MOJOM_BLINK_FORWARD_H_

#include "services/network/public/mojom/fetch_api.mojom-shared.h"

namespace network::mojom {

enum class CorsPreflightPolicy : int32_t {
  kPreventPreflight,
  kConsiderPreflight,
};

}  // namespace network::mojom

namespace network::mojom::blink {

using CredentialsMode = ::network::mojom::CredentialsMode;
using FetchResponseType = ::network::mojom::FetchResponseType;
using RedirectMode = ::network::mojom::RedirectMode;
using RequestDestination = ::network::mojom::RequestDestination;
using RequestMode = ::network::mojom::RequestMode;

}  // namespace network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_FETCH_API_MOJOM_BLINK_FORWARD_H_
