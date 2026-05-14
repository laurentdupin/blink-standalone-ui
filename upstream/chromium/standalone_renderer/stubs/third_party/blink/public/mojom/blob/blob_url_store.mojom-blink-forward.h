#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_URL_STORE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_URL_STORE_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"

namespace mojo {
class InterfaceEndpointClient;
}

namespace blink::mojom::blink {

class BlobURLToken {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr const char Name_[] = "blink.mojom.BlobURLToken";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_ {
   public:
    explicit Proxy_(mojo::InterfaceEndpointClient*) {}
    template <typename Receiver>
    void Clone(Receiver) {}
  };
  template <typename ImplRefTraits>
  class Stub_ {};
};
class BlobURLStore {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.BlobURLStore";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class RequestValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_ {};
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_URL_STORE_MOJOM_BLINK_FORWARD_H_
