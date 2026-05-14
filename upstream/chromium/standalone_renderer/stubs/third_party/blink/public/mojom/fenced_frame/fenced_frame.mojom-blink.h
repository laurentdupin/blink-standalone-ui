#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FENCED_FRAME_FENCED_FRAME_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FENCED_FRAME_FENCED_FRAME_MOJOM_BLINK_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "third_party/blink/public/mojom/fenced_frame/fenced_frame.mojom-blink-forward.h"

namespace blink::mojom::blink {

class FencedFrameOwnerHost {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.FencedFrameOwnerHost";
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
  };
  template <typename ImplRefTraits>
  class Stub_;

  virtual ~FencedFrameOwnerHost() = default;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FENCED_FRAME_FENCED_FRAME_MOJOM_BLINK_H_
