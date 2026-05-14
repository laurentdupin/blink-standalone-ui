#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_SCROLL_DIRECTION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_SCROLL_DIRECTION_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class ScrollDirection {
  kScrollUpIgnoringWritingMode,
  kScrollDownIgnoringWritingMode,
  kScrollLeftIgnoringWritingMode,
  kScrollRightIgnoringWritingMode,
  kScrollBlockDirectionBackward,
  kScrollBlockDirectionForward,
  kScrollInlineDirectionBackward,
  kScrollInlineDirectionForward,
};

}  // namespace blink::mojom::blink

#endif
