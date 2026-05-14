#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_INTEGRITY_POLICY_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_INTEGRITY_POLICY_MOJOM_SHARED_H_

namespace network::mojom {

enum class IntegrityPolicy_Destination {
  kScript,
  kStyle,
};

enum class IntegrityPolicy_Source {
  kInline,
  kExternal,
};

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_INTEGRITY_POLICY_MOJOM_SHARED_H_
