#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_TIMING_RESOURCE_TIMING_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_TIMING_RESOURCE_TIMING_MOJOM_BLINK_FORWARD_H_

#include <memory>

#include "base/time/time.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink::mojom::blink {

enum class CacheState {
  kNone,
  kLocal,
  kValidated,
};

struct ResourceTimingInfo {
  static std::unique_ptr<ResourceTimingInfo> New() {
    return std::make_unique<ResourceTimingInfo>();
  }

  base::TimeTicks start_time;
  KURL name;
  base::TimeTicks response_end;
  base::TimeTicks last_redirect_end_time;
  uint64_t encoded_body_size = 0;
  uint64_t decoded_body_size = 0;
  bool allow_timing_details = false;
  bool is_secure_transport = false;
  bool did_reuse_connection = false;
  String alpn_negotiated_protocol;
  String connection_info;
  String content_type;
  String content_encoding;
  int32_t response_status = 0;
  CacheState cache_state = CacheState::kNone;
};
using ResourceTimingInfoPtr = std::unique_ptr<ResourceTimingInfo>;
struct ServerTimingInfo;
using ServerTimingInfoPtr = std::unique_ptr<ServerTimingInfo>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_TIMING_RESOURCE_TIMING_MOJOM_BLINK_FORWARD_H_
