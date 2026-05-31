#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONNECTION_ALLOWLIST_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONNECTION_ALLOWLIST_MOJOM_BLINK_H_

#include "services/network/public/cpp/connection_allowlist.h"
#include "services/network/public/mojom/connection_allowlist.mojom-shared.h"

namespace network::mojom::blink {

using ConnectionAllowlist = ::network::mojom::ConnectionAllowlist;
using ConnectionAllowlistIssue = ::network::mojom::ConnectionAllowlistIssue;
using ConnectionAllowlists = ::network::ConnectionAllowlists;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using ConnectionAllowlist = ::network::mojom::ConnectionAllowlist;
using ConnectionAllowlistIssue = ::network::mojom::ConnectionAllowlistIssue;
using ConnectionAllowlists = ::network::ConnectionAllowlists;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CONNECTION_ALLOWLIST_MOJOM_BLINK_H_
