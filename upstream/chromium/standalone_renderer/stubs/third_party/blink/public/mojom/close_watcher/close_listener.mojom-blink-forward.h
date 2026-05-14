#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CLOSE_WATCHER_CLOSE_LISTENER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CLOSE_WATCHER_CLOSE_LISTENER_MOJOM_BLINK_FORWARD_H_

#include <memory>
#include <utility>

#include "mojo/public/cpp/bindings/message.h"

namespace blink::mojom::blink {

class CloseListener {
 public:
  static constexpr const char Name_[] = "blink.mojom.CloseListener";
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  using IPCStableHashFunction = uint32_t (*)(::mojo::Message&);

  virtual ~CloseListener() = default;
  virtual void Signal() {}

  class RequestValidator_ : public ::mojo::MessageReceiver {
   public:
    bool Accept(::mojo::Message*) override { return true; }
  };

  static IPCStableHashFunction MessageToMethodInfo_(::mojo::Message&) {
    return nullptr;
  }
  static const char* MessageToMethodName_(::mojo::Message&) { return ""; }

  template <typename ImplRefTraits>
  class Stub_ : public ::mojo::MessageReceiverWithResponderStatus {
   public:
    using ImplPointerType = typename ImplRefTraits::PointerType;

    void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
    ImplPointerType& sink() { return sink_; }

    bool Accept(::mojo::Message*) override { return true; }
    bool AcceptWithResponder(
        ::mojo::Message*,
        std::unique_ptr<::mojo::MessageReceiverWithStatus>) override {
      return true;
    }
    bool PrefersSerializedMessages() override { return false; }

   private:
    ImplPointerType sink_{};
  };
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CLOSE_WATCHER_CLOSE_LISTENER_MOJOM_BLINK_FORWARD_H_
