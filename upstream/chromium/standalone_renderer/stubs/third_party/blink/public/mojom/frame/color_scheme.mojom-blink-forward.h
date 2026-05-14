#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_COLOR_SCHEME_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_COLOR_SCHEME_MOJOM_BLINK_FORWARD_H_
#ifndef BLINK_STANDALONE_THEME_MOJOM_ENUMS_DEFINED
#define BLINK_STANDALONE_THEME_MOJOM_ENUMS_DEFINED
namespace blink::mojom::blink {
enum class ColorScheme { kLight, kDark };
enum class PreferredContrast { kNoPreference, kMore, kLess, kCustom };
}
namespace blink::mojom {
using ColorScheme = ::blink::mojom::blink::ColorScheme;
using PreferredContrast = ::blink::mojom::blink::PreferredContrast;
}
#endif
#endif
