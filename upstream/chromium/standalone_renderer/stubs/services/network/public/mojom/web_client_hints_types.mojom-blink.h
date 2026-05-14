#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_CLIENT_HINTS_TYPES_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_CLIENT_HINTS_TYPES_MOJOM_BLINK_H_

namespace network::mojom::blink {

enum class WebClientHintsType {
  kDeviceMemory_DEPRECATED = 0,
  kDpr_DEPRECATED = 1,
  kResourceWidth_DEPRECATED = 2,
  kViewportWidth_DEPRECATED = 3,
  kRtt_DEPRECATED = 4,
  kDownlink_DEPRECATED = 5,
  kEct_DEPRECATED = 6,
  kUA = 8,
  kUAArch = 9,
  kUAPlatform = 10,
  kUAModel = 11,
  kUAMobile = 12,
  kUAFullVersion = 13,
  kUAPlatformVersion = 14,
  kPrefersColorScheme = 15,
  kUABitness = 16,
  kViewportHeight = 18,
  kDeviceMemory = 19,
  kDpr = 20,
  kResourceWidth = 21,
  kViewportWidth = 22,
  kUAFullVersionList = 23,
  kUAWoW64 = 25,
  kSaveData = 27,
  kPrefersReducedMotion = 28,
  kUAFormFactors = 29,
  kPrefersReducedTransparency = 30,
  kMinValue = kDeviceMemory_DEPRECATED,
  kMaxValue = kPrefersReducedTransparency,
};

}  // namespace network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_WEB_CLIENT_HINTS_TYPES_MOJOM_BLINK_H_
