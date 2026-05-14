#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEWPORT_INTERSECTION_STATE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEWPORT_INTERSECTION_STATE_MOJOM_BLINK_H_

#include <memory>

#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/geometry/transform.h"

namespace blink::mojom::blink {

enum class FrameOcclusionState {
  kUnknown = 0,
  kPossiblyOccluded = 1,
  kGuaranteedNotOccluded = 2,
};

struct ViewportIntersectionState {
  ViewportIntersectionState() = default;

  static std::unique_ptr<ViewportIntersectionState> New() {
    return std::make_unique<ViewportIntersectionState>();
  }

  bool Equals(const ViewportIntersectionState& other) const {
    return viewport_intersection == other.viewport_intersection &&
           main_frame_intersection == other.main_frame_intersection &&
           compositor_visible_rect == other.compositor_visible_rect &&
           occlusion_state == other.occlusion_state &&
           outermost_main_frame_size == other.outermost_main_frame_size &&
           outermost_main_frame_scroll_position ==
               other.outermost_main_frame_scroll_position;
  }

  gfx::Rect viewport_intersection;
  gfx::Rect main_frame_intersection;
  gfx::Rect compositor_visible_rect;
  FrameOcclusionState occlusion_state = FrameOcclusionState::kUnknown;
  gfx::Size outermost_main_frame_size;
  gfx::Point outermost_main_frame_scroll_position;
  gfx::Transform main_frame_transform;
};

using ViewportIntersectionStatePtr =
    std::unique_ptr<ViewportIntersectionState>;

}  // namespace blink::mojom::blink

#endif
