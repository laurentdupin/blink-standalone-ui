#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_MANIFEST_DISPLAY_MODE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_MANIFEST_DISPLAY_MODE_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {
enum class DisplayMode {
  kUndefined,
  kBrowser,
  kMinimalUi,
  kStandalone,
  kFullscreen,
  kWindowControlsOverlay,
  kTabbed,
  kUnframed,
  kPictureInPicture,
};
}

namespace blink::mojom {
using DisplayMode = ::blink::mojom::blink::DisplayMode;
}

#endif
