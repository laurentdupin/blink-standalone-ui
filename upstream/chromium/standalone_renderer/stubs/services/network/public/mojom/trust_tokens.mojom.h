#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_H_

#include <memory>

#include "services/network/public/mojom/trust_tokens.mojom-shared.h"

namespace network::mojom {

struct TrustTokenParams {};
using TrustTokenParamsPtr = std::unique_ptr<TrustTokenParams>;

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_H_
