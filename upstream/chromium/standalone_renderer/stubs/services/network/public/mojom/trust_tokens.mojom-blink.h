#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_BLINK_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "services/network/public/mojom/trust_tokens.mojom-shared.h"

namespace network::mojom::blink {

struct TrustTokenParams {};
using TrustTokenOperationStatus = ::network::mojom::TrustTokenOperationStatus;
struct HasTrustTokensResult {
  TrustTokenOperationStatus status = TrustTokenOperationStatus::kFailedPrecondition;
  bool has_trust_tokens = false;
};
using HasTrustTokensResultPtr = std::unique_ptr<HasTrustTokensResult>;
struct HasRedemptionRecordResult {
  TrustTokenOperationStatus status = TrustTokenOperationStatus::kFailedPrecondition;
  bool has_redemption_record = false;
};
using HasRedemptionRecordResultPtr =
    std::unique_ptr<HasRedemptionRecordResult>;
class TrustTokenQueryAnswerer {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "network.mojom.TrustTokenQueryAnswerer";
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
    void HasTrustTokens(Args&&...) {}
    template <typename... Args>
    void HasRedemptionRecord(Args&&...) {}
  };
};

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using TrustTokenParams = ::network::mojom::blink::TrustTokenParams;
using TrustTokenOperationStatus = ::network::mojom::TrustTokenOperationStatus;
using HasTrustTokensResult = ::network::mojom::blink::HasTrustTokensResult;
using HasTrustTokensResultPtr =
    ::network::mojom::blink::HasTrustTokensResultPtr;
using HasRedemptionRecordResult =
    ::network::mojom::blink::HasRedemptionRecordResult;
using HasRedemptionRecordResultPtr =
    ::network::mojom::blink::HasRedemptionRecordResultPtr;
using TrustTokenQueryAnswerer =
    ::network::mojom::blink::TrustTokenQueryAnswerer;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TRUST_TOKENS_MOJOM_BLINK_H_
