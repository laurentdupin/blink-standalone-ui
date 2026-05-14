#ifndef STANDALONE_RENDERER_STUBS_MOJO_PUBLIC_MOJOM_BASE_TEXT_DIRECTION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_MOJO_PUBLIC_MOJOM_BASE_TEXT_DIRECTION_MOJOM_BLINK_FORWARD_H_

namespace mojo_base::mojom {

enum class TextDirection {
  UNKNOWN_DIRECTION,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
};

}  // namespace mojo_base::mojom

namespace mojo_base::mojom::blink {

using TextDirection = ::mojo_base::mojom::TextDirection;

}  // namespace mojo_base::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_MOJO_PUBLIC_MOJOM_BASE_TEXT_DIRECTION_MOJOM_BLINK_FORWARD_H_
