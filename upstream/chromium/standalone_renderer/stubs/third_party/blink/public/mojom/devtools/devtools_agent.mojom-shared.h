#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_DEVTOOLS_AGENT_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_DEVTOOLS_AGENT_MOJOM_SHARED_H_

namespace blink::mojom {

namespace blink {
class DevToolsAgent;
class DevToolsAgentHost;
}  // namespace blink

using DevToolsAgentInterfaceBase = ::blink::mojom::blink::DevToolsAgent;
using DevToolsAgentHostInterfaceBase =
    ::blink::mojom::blink::DevToolsAgentHost;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_DEVTOOLS_AGENT_MOJOM_SHARED_H_
