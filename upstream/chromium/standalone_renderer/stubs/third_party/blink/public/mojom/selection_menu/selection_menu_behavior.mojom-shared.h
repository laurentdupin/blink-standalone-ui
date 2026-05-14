#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SELECTION_MENU_SELECTION_MENU_BEHAVIOR_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SELECTION_MENU_SELECTION_MENU_BEHAVIOR_MOJOM_SHARED_H_

namespace blink::mojom {

enum class SelectionMenuBehavior {
  kHide,
  kShow,
  kMaxValue = kShow,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

using SelectionMenuBehavior = ::blink::mojom::SelectionMenuBehavior;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SELECTION_MENU_SELECTION_MENU_BEHAVIOR_MOJOM_SHARED_H_
