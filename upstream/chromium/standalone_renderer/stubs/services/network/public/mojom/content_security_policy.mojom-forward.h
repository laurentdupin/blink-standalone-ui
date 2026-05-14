#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_FORWARD_H_

#include <memory>

namespace network::mojom {
struct CSPSource;
struct ContentSecurityPolicy;
using CSPSourcePtr = std::unique_ptr<CSPSource>;
using ContentSecurityPolicyPtr = ContentSecurityPolicy*;
}

#endif
