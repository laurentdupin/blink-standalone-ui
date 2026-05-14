#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_RESTRICTED_COOKIE_MANAGER_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_RESTRICTED_COOKIE_MANAGER_MOJOM_SHARED_H_

namespace network::mojom {

namespace blink {
class RestrictedCookieManager;
}  // namespace blink

using RestrictedCookieManagerInterfaceBase =
    ::network::mojom::blink::RestrictedCookieManager;

}  // namespace network::mojom

namespace blink::network::mojom {

using RestrictedCookieManagerInterfaceBase =
    ::network::mojom::RestrictedCookieManagerInterfaceBase;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_RESTRICTED_COOKIE_MANAGER_MOJOM_SHARED_H_
