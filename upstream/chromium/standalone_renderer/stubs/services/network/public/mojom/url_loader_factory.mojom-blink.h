#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_BLINK_H_

#include "services/network/public/mojom/url_loader_factory.mojom-blink-forward.h"

namespace network::mojom::blink {

class URLLoaderFactory {
 public:
  virtual ~URLLoaderFactory() = default;
};

}  // namespace network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_BLINK_H_
