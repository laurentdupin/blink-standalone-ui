#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PERMISSIONS_POLICY_PERMISSIONS_POLICY_FEATURE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PERMISSIONS_POLICY_PERMISSIONS_POLICY_FEATURE_MOJOM_BLINK_FORWARD_H_

namespace network::mojom {

enum class PermissionsPolicyFeature {
  kAttributionReporting,
  kCamera,
  kClientHintUAHighEntropyValues,
  kCrossOriginIsolated,
  kDeferredFetch,
  kDeferredFetchMinimal,
  kFocusWithoutUserActivation,
  kFullscreen,
  kGeolocation,
  kIdentityCredentialsGet,
  kMicrophone,
  kPayment,
  kPrivateStateTokenIssuance,
  kTrustTokenRedemption,
  kUnload,
  kUsb,
  kVerticalScroll,
  kWebAppInstallation,
  kMaxValue = kWebAppInstallation,
};

}  // namespace network::mojom

namespace network::mojom::blink {
using PermissionsPolicyFeature = ::network::mojom::PermissionsPolicyFeature;
}  // namespace network::mojom::blink

namespace network {
class PermissionsPolicy;
}

namespace blink::network {
using PermissionsPolicy = ::network::PermissionsPolicy;
}

namespace blink::network::mojom {
using PermissionsPolicyFeature = ::network::mojom::PermissionsPolicyFeature;
}

namespace blink::network::mojom::blink {
using PermissionsPolicyFeature =
    ::network::mojom::blink::PermissionsPolicyFeature;
}

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PERMISSIONS_POLICY_PERMISSIONS_POLICY_FEATURE_MOJOM_BLINK_FORWARD_H_
