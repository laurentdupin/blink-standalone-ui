#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVICE_POSTURE_DEVICE_POSTURE_PROVIDER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVICE_POSTURE_DEVICE_POSTURE_PROVIDER_MOJOM_BLINK_FORWARD_H_
namespace blink::mojom::blink {
enum class DevicePostureType {
  kContinuous,
  kFolded,
};
class DevicePostureClient {
 public:
  virtual ~DevicePostureClient() = default;
  virtual void OnPostureChanged(DevicePostureType) {}
};
class DevicePostureProvider {
 public:
  class Proxy_ {
   public:
    void AddListener(DevicePostureClient*) {}
  };
};
}
#endif
