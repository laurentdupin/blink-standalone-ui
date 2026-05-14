#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_BLOCKED_NAVIGATION_TYPES_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_BLOCKED_NAVIGATION_TYPES_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class NavigationBlockedReason {
  kRedirectWithNoUserGesture,
  kRedirectWithNoUserGestureSandbox,
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using NavigationBlockedReason =
    ::blink::mojom::blink::NavigationBlockedReason;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_BLOCKED_NAVIGATION_TYPES_MOJOM_BLINK_FORWARD_H_
