#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_UNENCODED_DIGEST_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_UNENCODED_DIGEST_MOJOM_H_

#include <memory>
#include <vector>

#include "services/network/public/cpp/integrity_metadata.h"
#include "services/network/public/mojom/unencoded_digest.mojom-blink-forward.h"

namespace network::mojom {

using UnencodedDigestIssue =
    ::network::mojom::blink::UnencodedDigestIssue;

struct UnencodedDigests {
  static std::unique_ptr<UnencodedDigests> New() {
    return std::make_unique<UnencodedDigests>();
  }

  std::vector<network::IntegrityMetadata> digests;
  std::vector<UnencodedDigestIssue> issues;
};
using UnencodedDigestsPtr = std::unique_ptr<UnencodedDigests>;

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_UNENCODED_DIGEST_MOJOM_H_
