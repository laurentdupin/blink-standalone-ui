#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ASSOCIATED_INTERFACES_ASSOCIATED_INTERFACES_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ASSOCIATED_INTERFACES_ASSOCIATED_INTERFACES_MOJOM_H_

namespace blink::mojom {

class AssociatedInterface;
class AssociatedInterfaceProvider {
 public:
  using Base_ = AssociatedInterfaceProvider;
  class Proxy_ {
   public:
    template <typename... Args>
    void GetAssociatedInterface(Args&&...) {}
  };
  virtual ~AssociatedInterfaceProvider() = default;
};

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ASSOCIATED_INTERFACES_ASSOCIATED_INTERFACES_MOJOM_H_
