#ifndef STANDALONE_RENDERER_STUBS_UI_ACCESSIBILITY_AX_ENUMS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_UI_ACCESSIBILITY_AX_ENUMS_MOJOM_BLINK_FORWARD_H_

namespace ax::mojom::blink {

enum class Role {
  kUnknown = 181,
  kNone,
  kGrid = 92,
  kListBox = 112,
  kListBoxOption = 113,
  kMenu = 122,
  kMenuBar = 123,
  kMenuItem = 124,
  kRadioButton = 141,
  kRadioGroup = 142,
  kTab = 164,
  kTabList = 165,
  kToolbar = 176,
};

enum class Command {
  kNone = 0,
  kSpinButtonDecrement,
  kSpinButtonIncrement,
};

enum class NameFrom {
  kNone = 0,
};

}  // namespace ax::mojom::blink

#endif
