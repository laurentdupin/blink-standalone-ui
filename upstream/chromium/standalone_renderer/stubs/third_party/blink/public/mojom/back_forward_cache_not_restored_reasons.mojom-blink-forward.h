#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BACK_FORWARD_CACHE_NOT_RESTORED_REASONS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BACK_FORWARD_CACHE_NOT_RESTORED_REASONS_MOJOM_BLINK_FORWARD_H_

#include <memory>

#include "mojo/public/cpp/bindings/clone_traits.h"

namespace blink::mojom::blink {

struct SameOriginBfcacheNotRestoredDetails {};
struct BFCacheBlockingDetailedReason {};
struct BackForwardCacheNotRestoredReasons {};

using SameOriginBfcacheNotRestoredDetailsPtr =
    std::unique_ptr<SameOriginBfcacheNotRestoredDetails>;
using BFCacheBlockingDetailedReasonPtr =
    std::unique_ptr<BFCacheBlockingDetailedReason>;
using BackForwardCacheNotRestoredReasonsPtr =
    std::unique_ptr<BackForwardCacheNotRestoredReasons>;

}  // namespace blink::mojom::blink

namespace mojo {

template <>
struct CloneTraits<
    ::blink::mojom::blink::BackForwardCacheNotRestoredReasonsPtr> {
  static ::blink::mojom::blink::BackForwardCacheNotRestoredReasonsPtr Clone(
      const ::blink::mojom::blink::BackForwardCacheNotRestoredReasonsPtr&
          input) {
    if (!input)
      return nullptr;
    return std::make_unique<
        ::blink::mojom::blink::BackForwardCacheNotRestoredReasons>();
  }
};

}  // namespace mojo

#endif
