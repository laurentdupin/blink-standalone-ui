#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_SHARED_H_

#include "services/network/public/mojom/trust_tokens.mojom-blink-forward.h"

namespace network::mojom {

enum class TrustTokenOperationStatus {
  kOk,
  kInvalidArgument,
  kResourceExhausted,
  kFailedPrecondition,
};

}  // namespace network::mojom

namespace blink::network::mojom {

using TrustTokenOperationStatus = ::network::mojom::TrustTokenOperationStatus;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_SHARED_H_
