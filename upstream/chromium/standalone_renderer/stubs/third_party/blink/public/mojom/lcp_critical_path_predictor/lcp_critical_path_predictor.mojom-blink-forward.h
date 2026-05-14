#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LCP_CRITICAL_PATH_PREDICTOR_LCP_CRITICAL_PATH_PREDICTOR_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LCP_CRITICAL_PATH_PREDICTOR_LCP_CRITICAL_PATH_PREDICTOR_MOJOM_BLINK_FORWARD_H_

#include <memory>
#include <vector>

#include "services/network/public/mojom/fetch_api.mojom-blink-forward.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace url {
class Origin;
}

namespace base {
class TimeDelta;
}

namespace blink::mojom::blink {

struct LcpElement {
  static std::unique_ptr<LcpElement> New() {
    return std::make_unique<LcpElement>();
  }
  bool is_image = false;
};
using LcpElementPtr = std::unique_ptr<LcpElement>;

struct LCPCriticalPathPredictorNavigationTimeHint {
  bool for_testing = false;
};
using LCPCriticalPathPredictorNavigationTimeHintPtr =
    std::unique_ptr<LCPCriticalPathPredictorNavigationTimeHint>;

class LCPCriticalPathPredictorHost {
 public:
  class Proxy_ {
   public:
    void OnLcpUpdated(LcpElementPtr) {}
    void OnLcpTimingPredictedForTesting(std::vector<uint8_t>) {}
    void SetLcpInfluencerScriptUrls(std::vector<KURL>) {}
    void AddPreconnectOrigin(const url::Origin&) {}
    void NotifyFetchedFont(const KURL&, bool) {}
    void NotifyFetchedSubresource(
        const KURL&,
        base::TimeDelta,
        ::network::mojom::blink::RequestDestination) {}
    void SetUnusedPreloads(std::vector<KURL>) {}
  };
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LCP_CRITICAL_PATH_PREDICTOR_LCP_CRITICAL_PATH_PREDICTOR_MOJOM_BLINK_FORWARD_H_
