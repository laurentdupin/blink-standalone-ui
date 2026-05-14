#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_USE_COUNTER_USE_COUNTER_FEATURE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_USE_COUNTER_USE_COUNTER_FEATURE_MOJOM_SHARED_H_

namespace blink::mojom {

enum class UseCounterFeatureType {
  kWebFeature,
  kCssProperty,
  kAnimatedCssProperty,
  kPermissionsPolicyViolationEnforce,
  kPermissionsPolicyIframeAttribute,
  kPermissionsPolicyHeader,
  kWebDXFeature,
  kPermissionsPolicyEnabledPrivacySensitive,
};

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_USE_COUNTER_USE_COUNTER_FEATURE_MOJOM_SHARED_H_
