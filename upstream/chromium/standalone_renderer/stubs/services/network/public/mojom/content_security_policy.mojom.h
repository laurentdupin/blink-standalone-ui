#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_H_

#include <memory>
#include <string>

#include "services/network/public/mojom/web_sandbox_flags.mojom-blink-forward.h"

namespace network::mojom::blink {

enum class ContentSecurityPolicyType {
  kReport,
  kEnforce,
};

enum class ContentSecurityPolicySource {
  kHTTP,
  kMeta,
};

}  // namespace network::mojom::blink

namespace network::mojom {

using ContentSecurityPolicyType = ::network::mojom::blink::ContentSecurityPolicyType;
using ContentSecurityPolicySource = ::network::mojom::blink::ContentSecurityPolicySource;

enum class CSPDisposition {
  CHECK,
  DO_NOT_CHECK,
};

enum class CSPDirectiveName {
  Unknown,
};

enum class CSPRequireTrustedTypesFor {
  None,
};


struct CSPSource {
  std::string scheme;
  std::string host;
  int32_t port = -1;
  std::string path;
  bool is_host_wildcard = false;
  bool is_port_wildcard = false;
};

struct ContentSecurityPolicyHeader {
  std::string header_value;
  network::mojom::blink::ContentSecurityPolicyType type =
      network::mojom::blink::ContentSecurityPolicyType::kEnforce;
  network::mojom::blink::ContentSecurityPolicySource source =
      network::mojom::blink::ContentSecurityPolicySource::kHTTP;
};

struct AllowCSPFromHeaderValue {};
using AllowCSPFromHeaderValuePtr =
    std::unique_ptr<AllowCSPFromHeaderValue>;

struct SourceLocation {};
using SourceLocationPtr = std::unique_ptr<SourceLocation>;

struct ContentSecurityPolicy {
  CSPSource self_origin;
  network::mojom::blink::WebSandboxFlags sandbox =
      network::mojom::blink::WebSandboxFlags::kNone;
  ContentSecurityPolicyHeader header;

  ContentSecurityPolicy* Clone() const { return const_cast<ContentSecurityPolicy*>(this); }
};

using CSPSourcePtr = std::unique_ptr<CSPSource>;
using ContentSecurityPolicyPtr = ContentSecurityPolicy*;

class OriginWithPossibleWildcardsDataView;

}  // namespace network::mojom

#endif
