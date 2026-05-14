#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_USER_ACTIVATION_UPDATE_TYPES_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_USER_ACTIVATION_UPDATE_TYPES_MOJOM_SHARED_H_

namespace blink::mojom {

enum class UserActivationUpdateType {
  kNotifyActivation,
  kNotifyActivationStickyOnly,
  kConsumeTransientActivation,
  kClearActivation,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

using UserActivationUpdateType = ::blink::mojom::UserActivationUpdateType;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_USER_ACTIVATION_UPDATE_TYPES_MOJOM_SHARED_H_
