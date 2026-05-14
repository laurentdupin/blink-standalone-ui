#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_PERMISSION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_PERMISSION_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"

namespace blink::mojom::blink {
class PermissionService {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.PermissionService";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_;
};
class PermissionService::Proxy_ : public PermissionService {
 public:
  template <typename... Args>
  explicit Proxy_(Args&&...) {}
};
enum class PermissionName;
}
#endif
