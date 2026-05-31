#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SHARED_DICTIONARY_ACCESS_OBSERVER_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SHARED_DICTIONARY_ACCESS_OBSERVER_MOJOM_H_

#include <cstdint>

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"

namespace network::mojom {

class SharedDictionaryAccessObserver {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] =
      "network.mojom.SharedDictionaryAccessObserver";
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
    template <typename... Args>
    explicit Proxy_(Args&&...) {}

    template <typename... Args>
    void Clone(Args&&...) {}
  };
};

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SHARED_DICTIONARY_ACCESS_OBSERVER_MOJOM_H_
