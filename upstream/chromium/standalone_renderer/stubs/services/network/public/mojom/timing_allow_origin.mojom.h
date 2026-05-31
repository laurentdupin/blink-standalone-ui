#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace network::mojom {

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

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_TIMING_ALLOW_ORIGIN_MOJOM_H_
