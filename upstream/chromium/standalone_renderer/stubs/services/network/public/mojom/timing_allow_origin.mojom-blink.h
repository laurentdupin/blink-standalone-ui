#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_BLINK_H_

#include <memory>
#include <string>
#include <vector>

namespace network::mojom::blink {

struct TimingAllowOrigin {
  enum class Tag { kSerializedOrigins, kAll };

  static std::unique_ptr<TimingAllowOrigin> NewSerializedOrigins(
      std::vector<std::string>) {
    auto value = std::make_unique<TimingAllowOrigin>();
    value->tag = Tag::kSerializedOrigins;
    return value;
  }

  template <typename Origins>
  static std::unique_ptr<TimingAllowOrigin> NewSerializedOrigins(Origins&&) {
    auto value = std::make_unique<TimingAllowOrigin>();
    value->tag = Tag::kSerializedOrigins;
    return value;
  }

  static std::unique_ptr<TimingAllowOrigin> NewAll(int) {
    auto value = std::make_unique<TimingAllowOrigin>();
    value->tag = Tag::kAll;
    return value;
  }

  template <typename... Args>
  static std::unique_ptr<TimingAllowOrigin> New(Args&&...) {
    return std::make_unique<TimingAllowOrigin>();
  }

  Tag tag = Tag::kAll;
};
using TimingAllowOriginPtr = std::unique_ptr<TimingAllowOrigin>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using TimingAllowOrigin = ::network::mojom::blink::TimingAllowOrigin;
using TimingAllowOriginPtr = ::network::mojom::blink::TimingAllowOriginPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_BLINK_H_
