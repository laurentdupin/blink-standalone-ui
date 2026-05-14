#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_KEEP_ALIVE_HANDLE_FACTORY_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_KEEP_ALIVE_HANDLE_FACTORY_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/loader/keep_alive_handle.mojom-blink.h"

namespace blink::mojom::blink {

class KeepAliveHandleFactory {
 public:
  using Base_ = KeepAliveHandleFactory;
  class Proxy_ {
   public:
    template <typename... Args>
    void IssueKeepAliveHandle(Args&&...) {}
  };
  virtual ~KeepAliveHandleFactory() = default;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_KEEP_ALIVE_HANDLE_FACTORY_MOJOM_BLINK_H_
