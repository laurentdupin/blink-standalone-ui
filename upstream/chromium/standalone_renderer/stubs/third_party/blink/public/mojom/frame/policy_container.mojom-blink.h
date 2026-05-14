#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_POLICY_CONTAINER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_POLICY_CONTAINER_MOJOM_BLINK_H_

#include <memory>

#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "mojo/public/cpp/bindings/message.h"
#include "services/network/public/mojom/content_security_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/cross_origin_embedder_policy.mojom-shared.h"
#include "services/network/public/mojom/integrity_policy.mojom-shared.h"
#include "services/network/public/mojom/ip_address_space.mojom-shared.h"
#include "services/network/public/mojom/referrer_policy.mojom-shared.h"
#include "services/network/public/mojom/web_sandbox_flags.mojom-shared.h"
#include "third_party/blink/public/mojom/frame/policy_container.mojom-shared.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace blink::mojom::blink {

class PolicyContainerHost {
 public:
  using Base_ = PolicyContainerHost;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };

  class Proxy_ {
   public:
    explicit Proxy_(mojo::InterfaceEndpointClient*) {}
    void SetReferrerPolicy(
        ::network::mojom::blink::ReferrerPolicy referrer_policy) {}
    void AddContentSecurityPolicies(
        Vector<::network::mojom::blink::ContentSecurityPolicyPtr>
            content_security_policies) {}
  };

  static constexpr const char Name_[] = "blink.mojom.PolicyContainerHost";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;

  virtual ~PolicyContainerHost() = default;
  virtual void SetReferrerPolicy(
      ::network::mojom::blink::ReferrerPolicy referrer_policy) {}
  virtual void AddContentSecurityPolicies(
      Vector<::network::mojom::blink::ContentSecurityPolicyPtr>
          content_security_policies) {}
};

struct PolicyContainerPolicies {
  static std::unique_ptr<PolicyContainerPolicies> New() {
    return std::make_unique<PolicyContainerPolicies>();
  }

  ::network::mojom::blink::CrossOriginEmbedderPolicyValue
      cross_origin_embedder_policy =
          ::network::mojom::blink::CrossOriginEmbedderPolicyValue::kNone;
  ::network::mojom::blink::ReferrerPolicy referrer_policy =
      ::network::mojom::blink::ReferrerPolicy::kDefault;
  ::network::mojom::blink::WebSandboxFlags sandbox_flags =
      ::network::mojom::blink::WebSandboxFlags::kNone;
  ::network::mojom::blink::IPAddressSpace ip_address_space =
      ::network::mojom::blink::IPAddressSpace::kUnknown;
  bool is_credentialless = false;
  bool can_navigate_top_without_user_gesture = true;
  bool cross_origin_isolation_enabled_by_dip = false;
  ::network::ConnectionAllowlists connection_allowlists;
  Vector<::network::mojom::blink::ContentSecurityPolicyPtr>
      content_security_policies;
};
using PolicyContainerPoliciesPtr = std::unique_ptr<PolicyContainerPolicies>;

struct PolicyContainer;
using PolicyContainerPtr = std::unique_ptr<PolicyContainer>;
struct PolicyContainerBindParams;
using PolicyContainerBindParamsPtr = std::unique_ptr<PolicyContainerBindParams>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_POLICY_CONTAINER_MOJOM_BLINK_H_
