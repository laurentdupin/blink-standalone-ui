#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_PAGE_MOJOM_BLINK_FORWARD_H_
#include <memory>

namespace blink::mojom::blink {
class PageBroadcast;
enum class PagehideDispatch {
  kNotDispatched,
  kDispatchedNotPersisted,
  kDispatchedPersisted,
};
struct PageLifecycleState;
using PageLifecycleStatePtr = std::unique_ptr<PageLifecycleState>;
struct PrerenderPageActivationParams;
using PrerenderPageActivationParamsPtr =
    std::unique_ptr<PrerenderPageActivationParams>;
}
#endif
