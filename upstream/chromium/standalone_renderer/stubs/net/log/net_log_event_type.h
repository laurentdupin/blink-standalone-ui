// Standalone no-network net-log event-type shim.
//
// The image/resource integration probe needs HTTP helper declarations that
// mention NetLogEventType. Standalone local/data rendering does not enable
// network logging, so keep this as an inert type surface.

#ifndef NET_LOG_NET_LOG_EVENT_TYPE_H_
#define NET_LOG_NET_LOG_EVENT_TYPE_H_

namespace net {

enum class NetLogEventType {};

}  // namespace net

#endif  // NET_LOG_NET_LOG_EVENT_TYPE_H_
