#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_ENUMS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_ENUMS_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class ScrollType {
  kUser = 0,
  kProgrammatic,
  kClamping,
  kCompositor,
  kAnchoring,
  kScrollStart,
};

enum class ScrollBehavior {
  kAuto = 0,
  kInstant,
  kSmooth,
};

}  // namespace blink::mojom::blink

#endif
