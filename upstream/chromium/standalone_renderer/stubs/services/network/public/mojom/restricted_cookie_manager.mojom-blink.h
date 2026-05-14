#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_RESTRICTED_COOKIE_MANAGER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_RESTRICTED_COOKIE_MANAGER_MOJOM_BLINK_H_

#include <memory>

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"

namespace network::mojom::blink {

struct CookiesResponse {
  bool status = false;
};
using CookiesResponsePtr = std::unique_ptr<CookiesResponse>;

class RestrictedCookieManager {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] =
      "network.mojom.RestrictedCookieManager";
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
};

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using CookiesResponse = ::network::mojom::blink::CookiesResponse;
using CookiesResponsePtr = ::network::mojom::blink::CookiesResponsePtr;
using RestrictedCookieManager =
    ::network::mojom::blink::RestrictedCookieManager;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_RESTRICTED_COOKIE_MANAGER_MOJOM_BLINK_H_
