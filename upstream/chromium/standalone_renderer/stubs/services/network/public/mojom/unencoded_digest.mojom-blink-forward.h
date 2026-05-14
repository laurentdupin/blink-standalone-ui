#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_UNENCODED_DIGEST_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_UNENCODED_DIGEST_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace network::mojom::blink {

enum class UnencodedDigestIssue {
  kMalformedDictionary,
  kUnknownAlgorithm,
  kIncorrectDigestType,
  kIncorrectDigestLength,
};

struct UnencodedDigests {
  template <typename... Args>
  static std::unique_ptr<UnencodedDigests> New(Args&&...) {
    return std::make_unique<UnencodedDigests>();
  }
};
using UnencodedDigestsPtr = std::unique_ptr<UnencodedDigests>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using UnencodedDigestIssue = ::network::mojom::blink::UnencodedDigestIssue;
using UnencodedDigests = ::network::mojom::blink::UnencodedDigests;
using UnencodedDigestsPtr = ::network::mojom::blink::UnencodedDigestsPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_UNENCODED_DIGEST_MOJOM_BLINK_FORWARD_H_
