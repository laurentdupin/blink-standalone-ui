// Standalone no-network net-log capture-mode shim.
//
// The image experiment needs net::HttpRequestHeaders declarations through
// Blink's fetch/resource headers, but standalone rendering does not enable
// network logging.

#ifndef NET_LOG_NET_LOG_CAPTURE_MODE_H_
#define NET_LOG_NET_LOG_CAPTURE_MODE_H_

namespace net {

enum class NetLogCaptureMode {
  kDefault,
  kIncludeSensitive,
  kEverything,
};

}  // namespace net

#endif  // NET_LOG_NET_LOG_CAPTURE_MODE_H_
