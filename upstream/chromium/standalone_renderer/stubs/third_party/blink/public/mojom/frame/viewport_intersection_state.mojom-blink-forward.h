#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEWPORT_INTERSECTION_STATE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEWPORT_INTERSECTION_STATE_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {
enum class FrameOcclusionState;
struct ViewportIntersectionState;
using ViewportIntersectionStatePtr =
    std::unique_ptr<ViewportIntersectionState>;
}

#endif
