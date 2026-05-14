#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_PAUSE_SUBRESOURCE_LOADING_HANDLE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_PAUSE_SUBRESOURCE_LOADING_HANDLE_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"

namespace blink::mojom::blink {
class PauseSubresourceLoadingHandle {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] =
      "blink.mojom.PauseSubresourceLoadingHandle";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class RequestValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  template <typename ImplRefTraits>
  class Stub_ : public mojo::MessageReceiverWithResponderStatus {
   public:
    using ImplPointerType = typename ImplRefTraits::PointerType;
    void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
    ImplPointerType& sink() { return sink_; }
    bool Accept(mojo::Message*) override { return true; }
    bool AcceptWithResponder(mojo::Message*,
                             std::unique_ptr<mojo::MessageReceiverWithStatus>)
        override {
      return true;
    }

   private:
    ImplPointerType sink_;
  };
};
}
#endif
