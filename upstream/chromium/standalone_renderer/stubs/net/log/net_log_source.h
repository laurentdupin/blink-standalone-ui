#ifndef STANDALONE_RENDERER_STUBS_NET_LOG_NET_LOG_SOURCE_H_
#define STANDALONE_RENDERER_STUBS_NET_LOG_NET_LOG_SOURCE_H_

#include "base/time/time.h"
#include "net/log/net_log_source_type.h"

namespace net {

struct NetLogSource {
  static constexpr uint32_t kInvalidId = 0;

  NetLogSource() = default;
  NetLogSource(NetLogSourceType source_type, uint32_t source_id)
      : type(source_type), id(source_id) {}
  NetLogSource(NetLogSourceType source_type,
               uint32_t source_id,
               base::TimeTicks start_time)
      : type(source_type), id(source_id), start_time(start_time) {}

  bool operator==(const NetLogSource&) const = default;

  NetLogSourceType type = NetLogSourceType::NONE;
  uint32_t id = kInvalidId;
  base::TimeTicks start_time;
};

}  // namespace net

#endif  // STANDALONE_RENDERER_STUBS_NET_LOG_NET_LOG_SOURCE_H_
