#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_REGISTRATION_MOJOM_SHARED_H_

namespace blink::mojom {

#if !defined(STANDALONE_RENDERER_SCRIPT_TYPE_DEFINED)
#define STANDALONE_RENDERER_SCRIPT_TYPE_DEFINED
enum class ScriptType {
  kClassic,
  kModule,
  kImportMap,
  kSpeculationRules,
  kMinValue = kClassic,
  kMaxValue = kSpeculationRules,
};
#endif

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
