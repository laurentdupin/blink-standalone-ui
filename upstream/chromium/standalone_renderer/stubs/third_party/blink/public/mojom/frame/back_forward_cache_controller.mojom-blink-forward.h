#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_BACK_FORWARD_CACHE_CONTROLLER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_BACK_FORWARD_CACHE_CONTROLLER_MOJOM_BLINK_FORWARD_H_

#include <memory>

#include "third_party/blink/public/mojom/navigation/renderer_eviction_reason.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/scheduler/web_scheduler_tracked_feature.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/script_source_location.mojom-blink-forward.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace blink::mojom::blink {

struct BlockingDetails {
  static std::unique_ptr<BlockingDetails> New() {
    return std::make_unique<BlockingDetails>();
  }

  WebSchedulerTrackedFeature feature = WebSchedulerTrackedFeature::kDummy;
  ScriptSourceLocationPtr source;
};
using BlockingDetailsPtr = std::unique_ptr<BlockingDetails>;

class BackForwardCacheControllerHost {
 public:
  class Proxy_ {
   public:
    void EvictFromBackForwardCache(RendererEvictionReason,
                                   ScriptSourceLocationPtr) {}
    void DidChangeBackForwardCacheDisablingFeatures(
        Vector<BlockingDetailsPtr>) {}
  };
  virtual ~BackForwardCacheControllerHost() = default;
  virtual void EvictFromBackForwardCache(RendererEvictionReason,
                                         ScriptSourceLocationPtr) {}
  virtual void DidChangeBackForwardCacheDisablingFeatures(
      Vector<BlockingDetailsPtr>) {}
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_BACK_FORWARD_CACHE_CONTROLLER_MOJOM_BLINK_FORWARD_H_
