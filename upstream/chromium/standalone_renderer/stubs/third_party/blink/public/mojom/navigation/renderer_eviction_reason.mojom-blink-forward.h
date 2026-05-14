#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_RENDERER_EVICTION_REASON_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_RENDERER_EVICTION_REASON_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class RendererEvictionReason {
  kJavaScriptExecution,
  kNetworkRequestDatapipeDrainedAsBytesConsumer,
  kNetworkRequestRedirected,
  kNetworkRequestTimeout,
  kNetworkExceedsBufferLimit,
  kBroadcastChannelOnMessage,
  kSharedWorkerMessage,
  kMaxValue = kSharedWorkerMessage,
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using RendererEvictionReason = ::blink::mojom::blink::RendererEvictionReason;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_RENDERER_EVICTION_REASON_MOJOM_BLINK_FORWARD_H_
