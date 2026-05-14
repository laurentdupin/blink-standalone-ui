#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_VISIBILITY_STATE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_VISIBILITY_STATE_MOJOM_BLINK_H_

namespace blink::mojom::blink {

enum class PageVisibilityState {
  kVisible,
  kHidden,
  kHiddenButPainting,
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using PageVisibilityState = ::blink::mojom::blink::PageVisibilityState;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_VISIBILITY_STATE_MOJOM_BLINK_H_
