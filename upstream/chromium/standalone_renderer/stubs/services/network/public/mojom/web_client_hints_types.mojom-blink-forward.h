#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_CLIENT_HINTS_TYPES_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_CLIENT_HINTS_TYPES_MOJOM_BLINK_FORWARD_H_

namespace network::mojom::blink {

enum class WebClientHintsType {
  kUA,
  kUAArch,
  kUAPlatform,
  kUAModel,
  kUAMobile,
  kUAFullVersion,
  kUAPlatformVersion,
  kPrefersColorScheme,
  kUABitness,
  kViewportHeight,
  kDeviceMemory,
  kDpr,
  kResourceWidth,
  kViewportWidth,
  kUAFullVersionList,
  kUAWoW64,
  kSaveData,
  kPrefersReducedMotion,
  kUAFormFactors,
  kPrefersReducedTransparency,
};

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {
using WebClientHintsType = ::network::mojom::blink::WebClientHintsType;
}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_CLIENT_HINTS_TYPES_MOJOM_BLINK_FORWARD_H_
