#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PRERENDER_PRERENDER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PRERENDER_PRERENDER_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

enum class PrerenderTriggerType {
  kLinkRelPrerender,
  kLinkRelNext,
};

struct PrerenderAttributes {};
using PrerenderAttributesPtr = std::unique_ptr<PrerenderAttributes>;

class NoStatePrefetchProcessor {
 public:
  class Proxy_ {
   public:
    void Start(PrerenderAttributesPtr) {}
    void Cancel() {}
  };
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PRERENDER_PRERENDER_MOJOM_BLINK_FORWARD_H_
