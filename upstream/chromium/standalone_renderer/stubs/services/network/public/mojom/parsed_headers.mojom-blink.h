#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_BLINK_H_

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
#include "services/network/public/mojom/content_security_policy.mojom-blink.h"
#include "services/network/public/mojom/no_vary_search.mojom-blink.h"
#include "services/network/public/mojom/parsed_headers.mojom-blink-forward.h"
#include "services/network/public/mojom/supports_loading_mode.mojom-blink.h"
#include "services/network/public/mojom/web_client_hints_types.mojom-blink.h"

namespace network::mojom::blink {

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

struct LinkHeader {
  template <typename... Args>
  static std::unique_ptr<LinkHeader> New(Args&&...) {
    return std::make_unique<LinkHeader>();
  }
};
using LinkHeaderPtr = std::unique_ptr<LinkHeader>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using LinkRelAttribute = ::network::mojom::blink::LinkRelAttribute;
using LinkAsAttribute = ::network::mojom::blink::LinkAsAttribute;
using CrossOriginAttribute = ::network::mojom::blink::CrossOriginAttribute;
using FetchPriorityAttribute = ::network::mojom::blink::FetchPriorityAttribute;
using XFrameOptionsValue = ::network::mojom::blink::XFrameOptionsValue;
using OriginAgentClusterValue =
    ::network::mojom::blink::OriginAgentClusterValue;
using LinkHeader = ::network::mojom::blink::LinkHeader;
using LinkHeaderPtr = ::network::mojom::blink::LinkHeaderPtr;
using ParsedHeaders = ::network::mojom::blink::ParsedHeaders;
using ParsedHeadersPtr = ::network::mojom::blink::ParsedHeadersPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_BLINK_H_
