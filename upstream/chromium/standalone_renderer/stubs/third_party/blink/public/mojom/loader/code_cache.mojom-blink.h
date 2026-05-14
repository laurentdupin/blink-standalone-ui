#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CODE_CACHE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CODE_CACHE_MOJOM_BLINK_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"

namespace blink::mojom::blink {

class CodeCacheHost {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.CodeCacheHost";
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
    void DidGenerateCacheableMetadata(Args&&...) {}
    template <typename... Args>
    void FetchCachedCode(Args&&...) {}
    template <typename... Args>
    void ClearCodeCacheEntry(Args&&...) {}
  };
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CODE_CACHE_MOJOM_BLINK_H_
