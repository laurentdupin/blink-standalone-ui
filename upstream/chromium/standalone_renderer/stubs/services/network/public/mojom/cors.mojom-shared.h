#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CORS_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CORS_MOJOM_SHARED_H_

#include <ostream>

namespace network {
struct CorsErrorStatus;
}  // namespace network

namespace network::mojom {

enum class CorsError {
  kDisallowedByMode,
  kInvalidResponse,
  kWildcardOriginNotAllowed,
  kMissingAllowOriginHeader,
  kMultipleAllowOriginValues,
  kInvalidAllowOriginValue,
  kAllowOriginMismatch,
  kInvalidAllowCredentials,
  kMaxValue = kInvalidAllowCredentials,
};

inline std::ostream& operator<<(std::ostream& os, CorsError value) {
  return os << static_cast<int>(value);
}

}  // namespace network::mojom

namespace blink::network {

using CorsErrorStatus = ::network::CorsErrorStatus;

}  // namespace blink::network

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CORS_MOJOM_SHARED_H_
