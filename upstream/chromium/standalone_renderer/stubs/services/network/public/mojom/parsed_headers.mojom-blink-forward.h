#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace network::mojom::blink {

enum class OriginAgentClusterValue {
  kAbsent,
  kTrue,
  kFalse,
};

struct ParsedHeaders {
  template <typename... Args>
  static std::unique_ptr<ParsedHeaders> New(Args&&...) {
    return std::make_unique<ParsedHeaders>();
  }
};
using ParsedHeadersPtr = std::unique_ptr<ParsedHeaders>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using OriginAgentClusterValue =
    ::network::mojom::blink::OriginAgentClusterValue;
using ParsedHeaders = ::network::mojom::blink::ParsedHeaders;
using ParsedHeadersPtr = ::network::mojom::blink::ParsedHeadersPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_PARSED_HEADERS_MOJOM_BLINK_FORWARD_H_
