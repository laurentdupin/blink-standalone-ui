#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FRAME_OWNER_PROPERTIES_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FRAME_OWNER_PROPERTIES_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/css/preferred_color_scheme.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/color_scheme.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/frame_owner_properties.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/scroll/scrollbar_mode.mojom-blink-forward.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink::mojom::blink {

struct FrameOwnerProperties {
  String name;
  ScrollbarMode scrollbar_mode = ScrollbarMode::kAuto;
  int32_t margin_width = 0;
  int32_t margin_height = 0;
  bool allow_fullscreen = false;
  bool allow_payment_request = false;
  bool is_display_none = false;
  ColorScheme color_scheme = ColorScheme::kLight;
  PreferredColorScheme preferred_color_scheme = PreferredColorScheme::kLight;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FRAME_OWNER_PROPERTIES_MOJOM_BLINK_H_
