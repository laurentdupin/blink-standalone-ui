#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PERMISSIONS_POLICY_PERMISSIONS_POLICY_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PERMISSIONS_POLICY_PERMISSIONS_POLICY_MOJOM_SHARED_H_

namespace network::mojom {
class OriginWithPossibleWildcardsDataView;
class PermissionsPolicyDataView;
}

namespace network {
class PermissionsPolicy;
}

namespace blink::network {
using PermissionsPolicy = ::network::PermissionsPolicy;
}

#endif
