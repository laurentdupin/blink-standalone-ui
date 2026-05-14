#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_BLINK_FORWARD_H_

#include "services/network/public/mojom/content_security_policy.mojom.h"
#include "third_party/blink/public/mojom/devtools/inspector_issue.mojom-blink.h"

namespace network::mojom::blink {

enum class CSPDisposition {
  CHECK,
  DO_NOT_CHECK,
};

enum class CSPDirectiveName {
  Unknown,
};

enum class CSPRequireTrustedTypesFor {
  None = 0,
  Script = 1,
};

using ContentSecurityPolicy = ::network::mojom::ContentSecurityPolicy;
using ContentSecurityPolicyPtr = ::network::mojom::ContentSecurityPolicyPtr;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using ContentSecurityPolicy = ::network::mojom::ContentSecurityPolicy;
using ContentSecurityPolicyPtr = ::network::mojom::ContentSecurityPolicyPtr;
using CSPDisposition = ::network::mojom::blink::CSPDisposition;
using ContentSecurityPolicyType =
    ::network::mojom::blink::ContentSecurityPolicyType;
using ContentSecurityPolicySource =
    ::network::mojom::blink::ContentSecurityPolicySource;
using CSPDirectiveName = ::network::mojom::blink::CSPDirectiveName;
using CSPRequireTrustedTypesFor =
    ::network::mojom::blink::CSPRequireTrustedTypesFor;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_BLINK_FORWARD_H_
