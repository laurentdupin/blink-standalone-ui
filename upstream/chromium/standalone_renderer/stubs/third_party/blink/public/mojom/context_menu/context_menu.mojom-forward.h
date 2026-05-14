#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTEXT_MENU_CONTEXT_MENU_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTEXT_MENU_CONTEXT_MENU_MOJOM_FORWARD_H_

#include <memory>

namespace blink::mojom {

enum class ContextMenuDataMediaType {
  kNone,
  kImage,
  kVideo,
  kAudio,
  kCanvas,
  kFile,
  kPlugin,
};

enum class CustomContextMenuItemType {
  kOption,
  kCheckableOption,
  kGroup,
  kSeparator,
  kSubMenu,
};

class ContextMenuClient;
struct Accelerator;
using AcceleratorPtr = std::unique_ptr<Accelerator>;
struct FormRendererId;
struct FieldRendererId;
struct CustomContextMenuItem;
using CustomContextMenuItemPtr = std::unique_ptr<CustomContextMenuItem>;
struct UntrustworthyContextMenuParams;
using UntrustworthyContextMenuParamsPtr =
    std::unique_ptr<UntrustworthyContextMenuParams>;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTEXT_MENU_CONTEXT_MENU_MOJOM_FORWARD_H_
