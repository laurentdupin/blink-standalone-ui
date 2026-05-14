#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BROWSER_INTERFACE_BROKER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BROWSER_INTERFACE_BROKER_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/browser_interface_broker.mojom-blink-forward.h"

namespace blink::mojom::blink {

class BrowserInterfaceBroker {
 public:
  using Base_ = BrowserInterfaceBroker;
  class Proxy_ {};
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using BrowserInterfaceBroker = ::blink::mojom::blink::BrowserInterfaceBroker;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BROWSER_INTERFACE_BROKER_MOJOM_BLINK_H_
