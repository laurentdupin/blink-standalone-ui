#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_FETCH_LATER_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_FETCH_LATER_MOJOM_H_

namespace blink::mojom {

class FetchLaterLoader {
 public:
  static constexpr bool PassesAssociatedKinds_ = true;
  static constexpr bool HasUninterruptableMethods_ = false;
  class Proxy_ {
   public:
    template <typename... Args>
    void SendNow(Args&&...) {}
    template <typename... Args>
    void Cancel(Args&&...) {}
  };
};
class FetchLaterLoaderFactory {
 public:
  static constexpr bool PassesAssociatedKinds_ = true;
  static constexpr bool HasUninterruptableMethods_ = false;
  class Proxy_ {
   public:
    template <typename... Args>
    void CreateLoader(Args&&...) {}
    template <typename... Args>
    void Clone(Args&&...) {}
  };
};
using FetchLaterLoaderInterfaceBase = FetchLaterLoader;
using FetchLaterLoaderFactoryInterfaceBase = FetchLaterLoaderFactory;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_FETCH_LATER_MOJOM_H_
