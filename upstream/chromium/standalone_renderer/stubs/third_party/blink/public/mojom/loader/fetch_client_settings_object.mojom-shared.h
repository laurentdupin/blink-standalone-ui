// third_party/blink/public/mojom/loader/fetch_client_settings_object.mojom-shared.h
// standalone shim.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_FETCH_CLIENT_SETTINGS_OBJECT_MOJOM_SHARED_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_FETCH_CLIENT_SETTINGS_OBJECT_MOJOM_SHARED_H_

#include <stdint.h>

namespace blink::mojom {

// https://w3c.github.io/webappsec-upgrade-insecure-requests/#insecure-requests-policy
enum class InsecureRequestsPolicy : int32_t {
  kDoNotUpgrade,
  kUpgrade,
};

}  // namespace blink::mojom

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_FETCH_CLIENT_SETTINGS_OBJECT_MOJOM_SHARED_H_
