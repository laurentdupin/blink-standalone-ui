#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_LOCAL_RESOURCE_LOADER_CONFIG_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_LOCAL_RESOURCE_LOADER_CONFIG_MOJOM_H_

#include <memory>

namespace blink::mojom {

struct LocalResourceValue {};
struct LocalResourceSource {};
struct LocalResourceLoaderConfig {};

using LocalResourceLoaderConfigPtr =
    std::unique_ptr<LocalResourceLoaderConfig>;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_LOCAL_RESOURCE_LOADER_CONFIG_MOJOM_H_
