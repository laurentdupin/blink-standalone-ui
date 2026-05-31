#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONTENT_SECURITY_POLICY_MOJOM_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "services/network/public/cpp/integrity_metadata.h"
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

  static std::unique_ptr<CSPSource> New() {
    return std::make_unique<CSPSource>();
  }

  static std::unique_ptr<CSPSource> New(std::string scheme,
                                        std::string host,
                                        int32_t port,
                                        std::string path,
                                        bool is_host_wildcard,
                                        bool is_port_wildcard) {
    auto source = std::make_unique<CSPSource>();
    source->scheme = std::move(scheme);
    source->host = std::move(host);
    source->port = port;
    source->path = std::move(path);
    source->is_host_wildcard = is_host_wildcard;
    source->is_port_wildcard = is_port_wildcard;
    return source;
  }
};
using CSPSourcePtr = std::unique_ptr<CSPSource>;

struct CSPSourceList {
  std::vector<CSPSourcePtr> sources;
  std::vector<std::string> nonces;
  std::vector<network::IntegrityMetadata> hashes;
  std::vector<network::IntegrityMetadata> url_hashes;
  std::vector<network::IntegrityMetadata> eval_hashes;
  bool allow_self = false;
  bool allow_star = false;
  bool allow_inline = false;
  bool allow_inline_speculation_rules = false;
  bool allow_eval = false;
  bool allow_wasm_eval = false;
  bool allow_wasm_unsafe_eval = false;
  bool allow_dynamic = false;
  bool allow_dynamic_url = false;
  bool allow_unsafe_hashes = false;
  bool report_sample = false;
  bool allow_trusted_types_eval = false;
  std::string report_hash_algorithm;

  template <typename... Args>
  static std::unique_ptr<CSPSourceList> New(Args&&...) {
    return std::make_unique<CSPSourceList>();
  }
};
using CSPSourceListPtr = std::unique_ptr<CSPSourceList>;

struct ContentSecurityPolicyHeader {
  std::string header_value;
  network::mojom::blink::ContentSecurityPolicyType type =
      network::mojom::blink::ContentSecurityPolicyType::kEnforce;
  network::mojom::blink::ContentSecurityPolicySource source =
      network::mojom::blink::ContentSecurityPolicySource::kHTTP;

  template <typename... Args>
  static std::unique_ptr<ContentSecurityPolicyHeader> New(Args&&...) {
    return std::make_unique<ContentSecurityPolicyHeader>();
  }
};
using ContentSecurityPolicyHeaderPtr =
    std::unique_ptr<ContentSecurityPolicyHeader>;

struct AllowCSPFromHeaderValue {};
using AllowCSPFromHeaderValuePtr =
    std::unique_ptr<AllowCSPFromHeaderValue>;

struct SourceLocation {};
using SourceLocationPtr = std::unique_ptr<SourceLocation>;

struct ContentSecurityPolicy {
  CSPSource self_origin;
  std::vector<std::pair<CSPDirectiveName, std::string>> raw_directives;
  std::vector<CSPSourceListPtr> directives;
  bool upgrade_insecure_requests = false;
  bool treat_as_public_address = false;
  bool block_all_mixed_content = false;
  network::mojom::blink::WebSandboxFlags sandbox =
      network::mojom::blink::WebSandboxFlags::kNone;
  ContentSecurityPolicyHeader header;
  bool use_reporting_api = false;
  std::vector<std::string> report_endpoints;
  CSPRequireTrustedTypesFor require_trusted_types_for =
      CSPRequireTrustedTypesFor::None;
  std::vector<std::string> parsing_errors;

  ContentSecurityPolicy* Clone() const { return const_cast<ContentSecurityPolicy*>(this); }

  template <typename... Args>
  static std::unique_ptr<ContentSecurityPolicy> New(Args&&...) {
    return std::make_unique<ContentSecurityPolicy>();
  }
};

using ContentSecurityPolicyPtr = ContentSecurityPolicy*;

struct CSPTrustedTypes {
  std::vector<std::string> list;
  bool allow_any = false;
  bool allow_duplicates = false;

  template <typename... Args>
  static std::unique_ptr<CSPTrustedTypes> New(Args&&...) {
    return std::make_unique<CSPTrustedTypes>();
  }
};
using CSPTrustedTypesPtr = std::unique_ptr<CSPTrustedTypes>;

class OriginWithPossibleWildcardsDataView;

}  // namespace network::mojom

#endif
