#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FAVICON_FAVICON_URL_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FAVICON_FAVICON_URL_MOJOM_BLINK_H_

namespace blink::mojom::blink {

enum class FaviconIconType {
  kInvalid,
  kFavicon,
  kTouchIcon,
  kTouchPrecomposedIcon,
  kMinValue = kInvalid,
  kMaxValue = kTouchPrecomposedIcon,
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FAVICON_FAVICON_URL_MOJOM_BLINK_H_
