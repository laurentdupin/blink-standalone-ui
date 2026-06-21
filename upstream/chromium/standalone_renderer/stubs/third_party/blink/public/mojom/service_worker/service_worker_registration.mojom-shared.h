#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_MOJOM_SHARED_H_

#include "third_party/blink/public/mojom/script/script_type.mojom-shared.h"

namespace blink::mojom {

enum class ServiceWorkerUpdateViaCache {
  kImports,
  kAll,
  kNone,
  kMinValue = kImports,
  kMaxValue = kNone,
};

class ServiceWorkerRegistrationObjectHostInterfaceBase {};
class ServiceWorkerRegistrationObjectInterfaceBase {};

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_MOJOM_SHARED_H_
