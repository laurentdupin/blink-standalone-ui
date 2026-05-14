#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_STORAGE_ACCESS_API_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_STORAGE_ACCESS_API_MOJOM_BLINK_FORWARD_H_

namespace network::mojom {

enum class StorageAccessApiStatus {
  kNone,
  kAccessViaAPI,
};

}  // namespace network::mojom

namespace network::mojom::blink {

enum class StorageAccessApiStatus {
  kNone,
  kAccessViaAPI,
};

}  // namespace network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_STORAGE_ACCESS_API_MOJOM_BLINK_FORWARD_H_
