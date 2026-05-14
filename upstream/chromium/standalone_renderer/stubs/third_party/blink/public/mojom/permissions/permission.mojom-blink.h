#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_PERMISSION_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_PERMISSION_MOJOM_BLINK_H_

#include <memory>
#include <optional>
#include <utility>

#include "mojo/public/cpp/bindings/pending_remote.h"
#include "third_party/blink/public/mojom/permissions/permission_status.mojom-blink-forward.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "ui/gfx/geometry/rect.h"

namespace blink::mojom::blink {

enum class PermissionName {
  GEOLOCATION,
  NOTIFICATIONS,
  MIDI,
  PROTECTED_MEDIA_IDENTIFIER,
  PERSISTENT_STORAGE,
  AUDIO_CAPTURE,
  VIDEO_CAPTURE,
  BACKGROUND_SYNC,
  SENSORS,
  CLIPBOARD_READ,
  CLIPBOARD_WRITE,
  PAYMENT_HANDLER,
  BACKGROUND_FETCH,
  IDLE_DETECTION,
  PERIODIC_BACKGROUND_SYNC,
  SCREEN_WAKE_LOCK,
  SYSTEM_WAKE_LOCK,
  NFC,
  STORAGE_ACCESS,
  WINDOW_MANAGEMENT,
  LOCAL_FONTS,
  DISPLAY_CAPTURE,
  TOP_LEVEL_STORAGE_ACCESS,
  CAPTURED_SURFACE_CONTROL,
  SPEAKER_SELECTION,
  KEYBOARD_LOCK,
  POINTER_LOCK,
  FULLSCREEN,
  WEB_APP_INSTALLATION,
  LOCAL_NETWORK_ACCESS,
  LOCAL_NETWORK,
  LOOPBACK_NETWORK,
  VR,
  AR,
  HAND_TRACKING,
  WEB_PRINTING,
  SMART_CARD,
  GEOLOCATION_APPROXIMATE,
};

struct PermissionDescriptor {
  static std::unique_ptr<PermissionDescriptor> New() {
    return std::make_unique<PermissionDescriptor>();
  }

  PermissionName name = PermissionName::GEOLOCATION;
};
using PermissionDescriptorPtr = std::unique_ptr<PermissionDescriptor>;

struct PermissionStatusWithDetails {
  static std::unique_ptr<PermissionStatusWithDetails> New() {
    return std::make_unique<PermissionStatusWithDetails>();
  }

  PermissionStatus status = PermissionStatus::DENIED;
};
using PermissionStatusWithDetailsPtr =
    std::unique_ptr<PermissionStatusWithDetails>;

class PermissionObserver {
 public:
  virtual ~PermissionObserver() = default;
  virtual void OnPermissionStatusChange(PermissionStatusWithDetailsPtr) {}
};

enum class EmbeddedPermissionControlResult {
  kDismissed = 0,
  kGranted = 1,
  kDenied = 2,
  kNotSupported = 3,
  kResolvedNoUserGesture = 4,
};

struct GeolocationEmbeddedPermissionRequestDescriptor {
  static std::unique_ptr<GeolocationEmbeddedPermissionRequestDescriptor> New() {
    return std::make_unique<GeolocationEmbeddedPermissionRequestDescriptor>();
  }

  bool autolocate = false;
};
using GeolocationEmbeddedPermissionRequestDescriptorPtr =
    std::unique_ptr<GeolocationEmbeddedPermissionRequestDescriptor>;

struct InstallEmbeddedPermissionRequestDescriptor {
  static std::unique_ptr<InstallEmbeddedPermissionRequestDescriptor> New() {
    return std::make_unique<InstallEmbeddedPermissionRequestDescriptor>();
  }
};
using InstallEmbeddedPermissionRequestDescriptorPtr =
    std::unique_ptr<InstallEmbeddedPermissionRequestDescriptor>;

struct UserMediaEmbeddedPermissionRequestDescriptor {
  static std::unique_ptr<UserMediaEmbeddedPermissionRequestDescriptor> New() {
    return std::make_unique<UserMediaEmbeddedPermissionRequestDescriptor>();
  }
};
using UserMediaEmbeddedPermissionRequestDescriptorPtr =
    std::unique_ptr<UserMediaEmbeddedPermissionRequestDescriptor>;

struct EmbeddedPermissionControlDescriptorExtension {
  static std::unique_ptr<EmbeddedPermissionControlDescriptorExtension>
  NewGeolocation(GeolocationEmbeddedPermissionRequestDescriptorPtr) {
    return std::make_unique<EmbeddedPermissionControlDescriptorExtension>();
  }
  static std::unique_ptr<EmbeddedPermissionControlDescriptorExtension>
  NewInstall(InstallEmbeddedPermissionRequestDescriptorPtr) {
    return std::make_unique<EmbeddedPermissionControlDescriptorExtension>();
  }
  static std::unique_ptr<EmbeddedPermissionControlDescriptorExtension>
  NewUserMedia(UserMediaEmbeddedPermissionRequestDescriptorPtr) {
    return std::make_unique<EmbeddedPermissionControlDescriptorExtension>();
  }
};
using EmbeddedPermissionControlDescriptorExtensionPtr =
    std::unique_ptr<EmbeddedPermissionControlDescriptorExtension>;

struct EmbeddedPermissionRequestDescriptor {
  static std::unique_ptr<EmbeddedPermissionRequestDescriptor> New() {
    return std::make_unique<EmbeddedPermissionRequestDescriptor>();
  }

  gfx::Rect element_position;
  EmbeddedPermissionControlDescriptorExtensionPtr detail;
};
using EmbeddedPermissionRequestDescriptorPtr =
    std::unique_ptr<EmbeddedPermissionRequestDescriptor>;

class EmbeddedPermissionControlClient {
 public:
  virtual ~EmbeddedPermissionControlClient() = default;
  virtual void OnEmbeddedPermissionControlRegistered(
      bool,
      const std::optional<::blink::Vector<PermissionStatus>>&) {}
};

class PermissionService;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_PERMISSION_MOJOM_BLINK_H_
