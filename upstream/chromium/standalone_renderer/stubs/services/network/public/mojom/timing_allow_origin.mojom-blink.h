#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_BLINK_H_

#include <memory>

namespace network::mojom::blink {

struct TimingAllowOrigin {
  template <typename... Args>
  static std::unique_ptr<TimingAllowOrigin> New(Args&&...) {
    return std::make_unique<TimingAllowOrigin>();
  }
};
using TimingAllowOriginPtr = std::unique_ptr<TimingAllowOrigin>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using TimingAllowOrigin = ::network::mojom::blink::TimingAllowOrigin;
using TimingAllowOriginPtr = ::network::mojom::blink::TimingAllowOriginPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_BLINK_H_
