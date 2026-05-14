#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_FETCH_HANDLER_TYPE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_FETCH_HANDLER_TYPE_MOJOM_SHARED_H_

namespace blink::mojom {

enum class ServiceWorkerFetchHandlerType {
  kNoHandler = 0,
  kNotSkippable = 1,
  kEmptyFetchHandler = 2,
  kMaxValue = kEmptyFetchHandler,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

using ServiceWorkerFetchHandlerType =
    ::blink::mojom::ServiceWorkerFetchHandlerType;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SERVICE_WORKER_SERVICE_WORKER_FETCH_HANDLER_TYPE_MOJOM_SHARED_H_
