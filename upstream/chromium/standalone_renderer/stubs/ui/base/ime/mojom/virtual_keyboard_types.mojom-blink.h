#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_VIRTUAL_KEYBOARD_TYPES_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_VIRTUAL_KEYBOARD_TYPES_MOJOM_BLINK_H_

namespace ui::mojom::blink {

enum class VirtualKeyboardPolicy {
  AUTO,
  MANUAL,
};

enum class VirtualKeyboardVisibilityRequest {
  NONE,
  SHOW,
  HIDE,
};

enum class VirtualKeyboardMode {
  kUnset,
  kResizesVisual,
  kResizesContent,
  kOverlaysContent,
};

}  // namespace ui::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_VIRTUAL_KEYBOARD_TYPES_MOJOM_BLINK_H_
