#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_ATTRIBUTION_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_ATTRIBUTION_MOJOM_BLINK_H_

namespace network {
struct FetchRetryOptions;
}  // namespace network

namespace network::mojom {

enum class AttributionSupport {
  kWeb = 0,
  kWebAndOs = 1,
  kOs = 2,
  kNone = 3,
  kUnset = 4,
};

enum class AttributionReportingEligibility {
  kUnset,
  kEmpty,
  kEventSource,
  kNavigationSource,
  kTrigger,
  kEventSourceOrTrigger,
};

}  // namespace network::mojom

namespace network::mojom::blink {

using AttributionSupport = ::network::mojom::AttributionSupport;
using AttributionReportingEligibility =
    ::network::mojom::AttributionReportingEligibility;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using AttributionSupport = ::network::mojom::AttributionSupport;
using AttributionReportingEligibility =
    ::network::mojom::AttributionReportingEligibility;

}  // namespace blink::network::mojom::blink

namespace blink::network::mojom {

using AttributionSupport = ::network::mojom::AttributionSupport;
using AttributionReportingEligibility =
    ::network::mojom::AttributionReportingEligibility;

}  // namespace blink::network::mojom

namespace blink::network {

using FetchRetryOptions = ::network::FetchRetryOptions;

}  // namespace blink::network

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_ATTRIBUTION_MOJOM_BLINK_H_
