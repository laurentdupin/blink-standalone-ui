#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FULLSCREEN_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FULLSCREEN_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

struct FullscreenOptions {
  bool prefers_navigation_bar = false;
  bool prefers_status_bar = false;
  int64_t display_id = -1;
  bool is_prefixed = false;
  bool is_xr_overlay = false;
};
using FullscreenOptionsPtr = std::unique_ptr<FullscreenOptions>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FULLSCREEN_MOJOM_BLINK_FORWARD_H_
