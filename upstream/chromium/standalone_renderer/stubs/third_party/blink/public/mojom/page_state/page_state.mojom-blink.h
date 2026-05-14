#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_STATE_PAGE_STATE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_STATE_PAGE_STATE_MOJOM_BLINK_H_

namespace blink::mojom::blink {

enum class ScrollRestorationType {
  kAuto,
  kManual,
  kMaxValue = kManual,
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using ScrollRestorationType = ::blink::mojom::blink::ScrollRestorationType;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_STATE_PAGE_STATE_MOJOM_BLINK_H_
