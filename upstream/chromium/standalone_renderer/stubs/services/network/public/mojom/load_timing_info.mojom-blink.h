#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_LOAD_TIMING_INFO_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_LOAD_TIMING_INFO_MOJOM_BLINK_H_

#include <memory>

#include "base/time/time.h"

namespace network::mojom::blink {

struct LoadTimingInfoConnectTiming {
  static std::unique_ptr<LoadTimingInfoConnectTiming> New(
      base::TimeTicks domain_lookup_start,
      base::TimeTicks domain_lookup_end,
      base::TimeTicks connect_start,
      base::TimeTicks connect_end,
      base::TimeTicks ssl_start,
      base::TimeTicks ssl_end) {
    auto timing = std::make_unique<LoadTimingInfoConnectTiming>();
    timing->domain_lookup_start = domain_lookup_start;
    timing->domain_lookup_end = domain_lookup_end;
    timing->connect_start = connect_start;
    timing->connect_end = connect_end;
    timing->ssl_start = ssl_start;
    timing->ssl_end = ssl_end;
    return timing;
  }

  base::TimeTicks domain_lookup_start;
  base::TimeTicks domain_lookup_end;
  base::TimeTicks connect_start;
  base::TimeTicks connect_end;
  base::TimeTicks ssl_start;
  base::TimeTicks ssl_end;
};

struct LoadTimingInfo {
  static std::unique_ptr<LoadTimingInfo> New(
      bool socket_reused,
      int32_t socket_log_id,
      base::Time request_start_time,
      base::TimeTicks request_start,
      base::TimeTicks proxy_resolve_start,
      base::TimeTicks proxy_resolve_end,
      std::unique_ptr<LoadTimingInfoConnectTiming> connect_timing,
      base::TimeTicks send_start,
      base::TimeTicks send_end,
      base::TimeTicks receive_headers_start,
      base::TimeTicks receive_headers_end,
      base::TimeTicks receive_non_informational_headers_start,
      base::TimeTicks receive_early_hints_start,
      base::TimeTicks push_start,
      base::TimeTicks push_end,
      base::TimeTicks service_worker_start_time,
      base::TimeTicks service_worker_ready_time,
      base::TimeTicks service_worker_fetch_start,
      base::TimeTicks service_worker_respond_with_settled,
      base::TimeTicks service_worker_router_evaluation_start,
      base::TimeTicks service_worker_cache_lookup_start) {
    auto timing = std::make_unique<LoadTimingInfo>();
    timing->socket_reused = socket_reused;
    timing->socket_log_id = socket_log_id;
    timing->request_start_time = request_start_time;
    timing->request_start = request_start;
    timing->proxy_resolve_start = proxy_resolve_start;
    timing->proxy_resolve_end = proxy_resolve_end;
    timing->connect_timing = std::move(connect_timing);
    timing->send_start = send_start;
    timing->send_end = send_end;
    timing->receive_headers_start = receive_headers_start;
    timing->receive_headers_end = receive_headers_end;
    timing->receive_non_informational_headers_start =
        receive_non_informational_headers_start;
    timing->receive_early_hints_start = receive_early_hints_start;
    timing->push_start = push_start;
    timing->push_end = push_end;
    timing->service_worker_start_time = service_worker_start_time;
    timing->service_worker_ready_time = service_worker_ready_time;
    timing->service_worker_fetch_start = service_worker_fetch_start;
    timing->service_worker_respond_with_settled =
        service_worker_respond_with_settled;
    timing->service_worker_router_evaluation_start =
        service_worker_router_evaluation_start;
    timing->service_worker_cache_lookup_start =
        service_worker_cache_lookup_start;
    return timing;
  }

  bool socket_reused = false;
  int32_t socket_log_id = 0;
  base::Time request_start_time;
  base::TimeTicks request_start;
  base::TimeTicks proxy_resolve_start;
  base::TimeTicks proxy_resolve_end;
  std::unique_ptr<LoadTimingInfoConnectTiming> connect_timing;
  base::TimeTicks send_start;
  base::TimeTicks send_end;
  base::TimeTicks receive_headers_start;
  base::TimeTicks receive_headers_end;
  base::TimeTicks receive_non_informational_headers_start;
  base::TimeTicks receive_early_hints_start;
  base::TimeTicks push_start;
  base::TimeTicks push_end;
  base::TimeTicks service_worker_start_time;
  base::TimeTicks service_worker_ready_time;
  base::TimeTicks service_worker_fetch_start;
  base::TimeTicks service_worker_respond_with_settled;
  base::TimeTicks service_worker_router_evaluation_start;
  base::TimeTicks service_worker_cache_lookup_start;
};

using LoadTimingInfoPtr = std::unique_ptr<LoadTimingInfo>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using LoadTimingInfo = ::network::mojom::blink::LoadTimingInfo;
using LoadTimingInfoConnectTiming =
    ::network::mojom::blink::LoadTimingInfoConnectTiming;
using LoadTimingInfoPtr = ::network::mojom::blink::LoadTimingInfoPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_LOAD_TIMING_INFO_MOJOM_BLINK_H_
