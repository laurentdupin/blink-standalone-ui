#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_WEBPREFERENCES_WEB_PREFERENCES_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_WEBPREFERENCES_WEB_PREFERENCES_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom {

#if !defined(BLINK_STANDALONE_IMAGE_ANIMATION_POLICY_DEFINED)
#define BLINK_STANDALONE_IMAGE_ANIMATION_POLICY_DEFINED
enum class ImageAnimationPolicy {
  kImageAnimationPolicyAllowed,
  kImageAnimationPolicyAnimateOnce,
  kImageAnimationPolicyNoAnimation,
};
#endif

}  // namespace blink::mojom

namespace blink::mojom::blink {

enum class PointerType {
  kPointerNone = 1,
  kPointerFirstType = kPointerNone,
  kPointerCoarseType = 2,
  kPointerFineType = 4,
};

enum class HoverType {
  kHoverNone = 1,
  kHoverFirstType = kHoverNone,
  kHoverHoverType = 2,
};

enum class OutputDeviceUpdateAbilityType {
  kSlowType,
  kFastType,
};

enum class ViewportStyle {
  kDefault,
  kMobile,
  kTelevision,
  kLast = kTelevision,
};

enum class EditingBehavior {
  kEditingMacBehavior,
  kEditingWindowsBehavior,
  kEditingUnixBehavior,
  kEditingAndroidBehavior,
  kEditingChromeOSBehavior,
};

using ImageAnimationPolicy = ::blink::mojom::ImageAnimationPolicy;

}  // namespace blink::mojom::blink

namespace blink::mojom {

using EditingBehavior = ::blink::mojom::blink::EditingBehavior;
using HoverType = ::blink::mojom::blink::HoverType;
using OutputDeviceUpdateAbilityType =
    ::blink::mojom::blink::OutputDeviceUpdateAbilityType;
using PointerType = ::blink::mojom::blink::PointerType;
using ViewportStyle = ::blink::mojom::blink::ViewportStyle;

}  // namespace blink::mojom

#endif
