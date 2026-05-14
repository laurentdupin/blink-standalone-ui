#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_TRANSFERRABLE_URL_LOADER_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_TRANSFERRABLE_URL_LOADER_MOJOM_H_

#include <memory>

#include "url/gurl.h"

namespace blink::mojom {

struct TransferrableURLLoader {
  GURL url;
};
using TransferrableURLLoaderPtr = std::unique_ptr<TransferrableURLLoader>;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_TRANSFERRABLE_URL_LOADER_MOJOM_H_
