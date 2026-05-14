#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CORS_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CORS_MOJOM_SHARED_H_

namespace network {
struct CorsErrorStatus;
}  // namespace network

namespace network::mojom {

enum class CorsError {
  kDisallowedByMode,
  kInvalidResponse,
  kMaxValue = kInvalidResponse,
};

}  // namespace network::mojom

namespace blink::network {

using CorsErrorStatus = ::network::CorsErrorStatus;

}  // namespace blink::network

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CORS_MOJOM_SHARED_H_
