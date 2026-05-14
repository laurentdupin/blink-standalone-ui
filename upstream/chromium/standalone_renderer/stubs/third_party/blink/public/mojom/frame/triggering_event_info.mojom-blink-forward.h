#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_TRIGGERING_EVENT_INFO_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_TRIGGERING_EVENT_INFO_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class TriggeringEventInfo {
  kUnknown,
  kNotFromEvent,
  kFromTrustedEvent,
  kFromUntrustedEvent,
  kMinValue = kUnknown,
  kMaxValue = kFromUntrustedEvent,
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_TRIGGERING_EVENT_INFO_MOJOM_BLINK_FORWARD_H_
