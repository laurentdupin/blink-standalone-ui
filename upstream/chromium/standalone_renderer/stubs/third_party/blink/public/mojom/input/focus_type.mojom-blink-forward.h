#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_FOCUS_TYPE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_FOCUS_TYPE_MOJOM_BLINK_FORWARD_H_
namespace blink::mojom::blink {
enum class FocusType {
  kNone,
  kForward,
  kBackward,
  kScript,
  kMouse,
  kPage,
  kAccessKey,
};
}
#endif
