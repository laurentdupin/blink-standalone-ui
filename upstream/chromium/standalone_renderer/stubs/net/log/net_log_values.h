// Standalone no-network net-log value shim.
//
// Real HTTP header helpers construct diagnostic values for net logging. The
// standalone renderer does not enable network logging, but keeping the value
// conversion shape lets the real parser/helper code compile unchanged.

#ifndef NET_LOG_NET_LOG_VALUES_H_
#define NET_LOG_NET_LOG_VALUES_H_

#include <string_view>

#include "base/values.h"

namespace net {

inline base::Value NetLogStringValue(std::string_view value) {
  return base::Value(value);
}

}  // namespace net

#endif  // NET_LOG_NET_LOG_VALUES_H_
