#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_IP_ADDRESS_SPACE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_IP_ADDRESS_SPACE_MOJOM_SHARED_H_

namespace network::mojom {

enum class IPAddressSpace {
  kLoopback,
  kLocal,
  kPublic,
  kUnknown,
  kMaxValue = kUnknown,
};

}  // namespace network::mojom

namespace blink::network::mojom {

using IPAddressSpace = ::network::mojom::IPAddressSpace;

}  // namespace blink::network::mojom

namespace network::mojom::blink {

using IPAddressSpace = ::network::mojom::IPAddressSpace;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using IPAddressSpace = ::network::mojom::IPAddressSpace;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_IP_ADDRESS_SPACE_MOJOM_SHARED_H_
