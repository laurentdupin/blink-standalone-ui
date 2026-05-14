#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_USER_ACTIVATION_NOTIFICATION_TYPE_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_USER_ACTIVATION_NOTIFICATION_TYPE_MOJOM_FORWARD_H_

namespace blink::mojom {
enum class UserActivationNotificationType {
  kNone,
  kInteraction,
  kDevTools,
  kExtensionEvent,
  kExtensionGuestView,
  kExtensionMessaging,
  kMedia,
  kFileSystemAccess,
  kPlugin,
  kTest,
  kWebScriptExec,
  kVoiceSearch,
  kExtensionMessagingBothPrivileged,
  kExtensionMessagingSenderPrivileged,
  kExtensionMessagingReceiverPrivileged,
  kExtensionMessagingNeitherPrivileged,
};
}

#endif
