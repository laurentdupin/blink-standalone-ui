#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_WINDOW_SHOW_STATE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_WINDOW_SHOW_STATE_MOJOM_BLINK_FORWARD_H_

namespace ui::mojom::blink {
enum class WindowShowState {
  kDefault = 0,
  kNormal = 1,
  kMinimized = 2,
  kMaximized = 3,
  kInactive = 4,
  kFullscreen = 5,
  kEnd = 6,
};
}

#endif
