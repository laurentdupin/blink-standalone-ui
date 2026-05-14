#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_LOAD_TIMING_INFO_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_LOAD_TIMING_INFO_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace network::mojom::blink {

struct LoadTimingInfo;
using LoadTimingInfoPtr = std::unique_ptr<LoadTimingInfo>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using LoadTimingInfo = ::network::mojom::blink::LoadTimingInfo;
using LoadTimingInfoPtr = ::network::mojom::blink::LoadTimingInfoPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_LOAD_TIMING_INFO_MOJOM_BLINK_FORWARD_H_
