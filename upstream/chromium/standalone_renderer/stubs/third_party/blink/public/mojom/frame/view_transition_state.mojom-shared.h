#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEW_TRANSITION_STATE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEW_TRANSITION_STATE_MOJOM_SHARED_H_

#include "mojo/public/cpp/bindings/struct_traits.h"
#include "third_party/blink/public/common/tokens/tokens.h"

namespace blink::mojom {

enum class ViewTransitionPropertyId {
  kBackdropFilter,
  kBorderRadius,
  kBorderWidth,
  kColorScheme,
  kCornerShape,
  kMixBlendMode,
  kTextOrientation,
  kWritingMode,
};

enum class ViewTransitionElementBoxSizing {
  kBorderBox,
  kContentBox,
};

class ViewTransitionElementDataView;
class ViewTransitionStateDataView;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_VIEW_TRANSITION_STATE_MOJOM_SHARED_H_
