#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_DEVICE_BOUND_SESSIONS_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_DEVICE_BOUND_SESSIONS_MOJOM_SHARED_H_

namespace network::mojom {

enum class DeviceBoundSessionUsage {
  kUnknown = 0,
  kNoSiteMatchNotInScope = 1,
  kSiteMatchNotInScope = 2,
  kInScopeRefreshNotYetNeeded = 3,
  kInScopeRefreshNotAllowed = 4,
  kInScopeProactiveRefreshNotPossible = 5,
  kInScopeProactiveRefreshAttempted = 6,
  kDeferred = 7,
};

}  // namespace network::mojom

namespace blink::network::mojom {

using DeviceBoundSessionUsage = ::network::mojom::DeviceBoundSessionUsage;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_DEVICE_BOUND_SESSIONS_MOJOM_SHARED_H_
