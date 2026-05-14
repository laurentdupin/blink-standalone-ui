#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_JAVASCRIPT_FRAMEWORK_DETECTION_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_JAVASCRIPT_FRAMEWORK_DETECTION_MOJOM_SHARED_H_

#include <cstdint>

namespace blink::mojom {

enum class JavaScriptFramework : int32_t {
  kNuxt = 0,
  kVuePress = 1,
  kSapper = 2,
  kGatsby = 3,
  kNext = 4,
  kSvelte = 5,
  kAngular = 6,
  kVue = 7,
  kPreact = 8,
  kReact = 9,
  kShopify = 10,
  kSquarespace = 11,
  kWix = 12,
  kJoomla = 13,
  kWordPress = 14,
  kDrupal = 15,
  kMinValue = kNuxt,
  kMaxValue = kDrupal,
};

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_JAVASCRIPT_FRAMEWORK_DETECTION_MOJOM_SHARED_H_
