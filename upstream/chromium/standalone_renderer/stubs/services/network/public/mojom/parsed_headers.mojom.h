#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_H_

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "net/http/http_cookie_indices.h"
#include "services/network/public/cpp/connection_allowlist.h"
#include "services/network/public/cpp/cross_origin_embedder_policy.h"
#include "services/network/public/cpp/cross_origin_opener_policy.h"
#include "services/network/public/cpp/document_isolation_policy.h"
#include "services/network/public/cpp/integrity_policy.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"
#include "services/network/public/mojom/no_vary_search.mojom.h"
#include "services/network/public/mojom/supports_loading_mode.mojom-blink.h"
#include "services/network/public/mojom/web_client_hints_types.mojom.h"

namespace network::mojom {

enum class LinkRelAttribute {
  kUnspecified,
  kPreload,
  kModulePreload,
};

enum class LinkAsAttribute {
  kUnspecified,
};

enum class CrossOriginAttribute {
  kUnspecified,
};

enum class FetchPriorityAttribute {
  kAuto,
};

enum class XFrameOptionsValue {
  kNone,
  kDeny,
  kAllowAll,
  kSameOrigin,
  kInvalid,
  kConflict,
};

enum class OriginAgentClusterValue {
  kAbsent,
  kTrue,
  kFalse,
};

struct LinkHeader {
  template <typename... Args>
  static std::unique_ptr<LinkHeader> New(Args&&...) {
    return std::make_unique<LinkHeader>();
  }

  std::string href;
  LinkRelAttribute rel = LinkRelAttribute::kUnspecified;
  LinkAsAttribute as = LinkAsAttribute::kUnspecified;
  CrossOriginAttribute cross_origin = CrossOriginAttribute::kUnspecified;
  FetchPriorityAttribute fetch_priority = FetchPriorityAttribute::kAuto;
  std::string mime_type;
};
using LinkHeaderPtr = std::unique_ptr<LinkHeader>;

struct TimingAllowOrigin {
  enum class Tag { kSerializedOrigins, kAll };

  static std::unique_ptr<TimingAllowOrigin> NewSerializedOrigins(
      std::vector<std::string> origins) {
    auto out = std::make_unique<TimingAllowOrigin>();
    out->tag_ = Tag::kSerializedOrigins;
    out->serialized_origins_ = std::move(origins);
    return out;
  }

  static std::unique_ptr<TimingAllowOrigin> NewAll(int) {
    auto out = std::make_unique<TimingAllowOrigin>();
    out->tag_ = Tag::kAll;
    return out;
  }

  Tag which() const { return tag_; }
  const std::vector<std::string>& get_serialized_origins() const {
    return serialized_origins_;
  }

 private:
  Tag tag_ = Tag::kAll;
  std::vector<std::string> serialized_origins_;
};
using TimingAllowOriginPtr = std::unique_ptr<TimingAllowOrigin>;

struct ParsedHeaders {
  template <typename... Args>
  static std::unique_ptr<ParsedHeaders> New(Args&&...) {
    return std::make_unique<ParsedHeaders>();
  }

  std::vector<ContentSecurityPolicyPtr> content_security_policy;
  AllowCSPFromHeaderValuePtr allow_csp_from;
  network::ConnectionAllowlists connection_allowlists;
  network::CrossOriginEmbedderPolicy cross_origin_embedder_policy;
  network::CrossOriginOpenerPolicy cross_origin_opener_policy;
  network::DocumentIsolationPolicy document_isolation_policy;
  std::unique_ptr<network::IntegrityPolicy> integrity_policy;
  std::unique_ptr<network::IntegrityPolicy> integrity_policy_report_only;
  OriginAgentClusterValue origin_agent_cluster =
      OriginAgentClusterValue::kAbsent;
  std::optional<std::vector<WebClientHintsType>> accept_ch;
  std::optional<std::vector<WebClientHintsType>> critical_ch;
  bool client_hints_ignored_due_to_clear_site_data_header = false;
  XFrameOptionsValue xfo = XFrameOptionsValue::kNone;
  std::vector<LinkHeaderPtr> link_headers;
  TimingAllowOriginPtr timing_allow_origin;
  std::vector<LoadingMode> supports_loading_mode;
  std::optional<base::flat_map<std::string, std::string>> reporting_endpoints;
  std::optional<std::vector<std::string>> cookie_indices;
  std::optional<std::vector<std::string>> avail_language;
  std::optional<std::vector<std::string>> content_language;
  NoVarySearchWithParseErrorPtr no_vary_search_with_parse_error;
  bool observe_browsing_topics = false;
  bool allow_cross_origin_event_reporting = false;
};
using ParsedHeadersPtr = std::unique_ptr<ParsedHeaders>;

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_H_
