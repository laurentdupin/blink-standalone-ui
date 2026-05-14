#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REMOTE_FRAME_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REMOTE_FRAME_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {

struct CreateRemoteChildParams {};
using CreateRemoteChildParamsPtr = std::unique_ptr<CreateRemoteChildParams>;
struct OpenURLParams {};
struct RemoteFrameInterfacesFromBrowser {};
using RemoteFrameInterfacesFromBrowserPtr =
    std::unique_ptr<RemoteFrameInterfacesFromBrowser>;
struct RemoteFrameInterfacesFromRenderer {};
struct RemoteMainFrameInterfaces {};
class NavigationStateKeepAliveHandle;
class RemoteFrame;
class RemoteFrameHost;
class RemoteMainFrame;
class RemoteMainFrameHost;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REMOTE_FRAME_MOJOM_BLINK_FORWARD_H_
