#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_LIFECYCLE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_LIFECYCLE_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class FrameVisibility;
enum class FrameLifecycleState;

}  // namespace blink::mojom::blink

namespace blink::mojom {

using FrameVisibility = ::blink::mojom::blink::FrameVisibility;
using FrameLifecycleState = ::blink::mojom::blink::FrameLifecycleState;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_LIFECYCLE_MOJOM_BLINK_FORWARD_H_
