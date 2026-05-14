#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_INTO_VIEW_PARAMS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_INTO_VIEW_PARAMS_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

struct ScrollAlignment;
struct FocusedEditableParams;
struct ScrollIntoViewParams;

using ScrollAlignmentPtr = std::unique_ptr<ScrollAlignment>;
using FocusedEditableParamsPtr = std::unique_ptr<FocusedEditableParams>;
using ScrollIntoViewParamsPtr = std::unique_ptr<ScrollIntoViewParams>;

}  // namespace blink::mojom::blink

#endif
