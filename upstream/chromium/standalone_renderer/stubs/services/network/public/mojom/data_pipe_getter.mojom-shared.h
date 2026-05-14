#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_DATA_PIPE_GETTER_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_DATA_PIPE_GETTER_MOJOM_SHARED_H_

namespace network::mojom {

class DataPipeGetterInterfaceBase {};
class DataPipeGetter;

}  // namespace network::mojom

namespace blink::network::mojom {

using DataPipeGetterInterfaceBase =
    ::network::mojom::DataPipeGetterInterfaceBase;
using DataPipeGetter = ::network::mojom::DataPipeGetter;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_DATA_PIPE_GETTER_MOJOM_SHARED_H_
