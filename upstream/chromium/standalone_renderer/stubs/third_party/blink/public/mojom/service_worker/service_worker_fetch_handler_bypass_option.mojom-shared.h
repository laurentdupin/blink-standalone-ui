#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_FETCH_HANDLER_BYPASS_OPTION_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_FETCH_HANDLER_BYPASS_OPTION_MOJOM_SHARED_H_

namespace blink::mojom {

enum class ServiceWorkerFetchHandlerBypassOption {
  kDefault,
  kRaceNetworkRequest,
  kRaceNetworkRequestHoldback,
  kSyntheticResponse,
  kSyntheticResponseDryRunMode,
  kMaxValue = kSyntheticResponseDryRunMode,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

using ServiceWorkerFetchHandlerBypassOption =
    ::blink::mojom::ServiceWorkerFetchHandlerBypassOption;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_FETCH_HANDLER_BYPASS_OPTION_MOJOM_SHARED_H_
