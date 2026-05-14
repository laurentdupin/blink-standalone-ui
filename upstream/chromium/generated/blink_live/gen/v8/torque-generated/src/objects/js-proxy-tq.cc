#include "src/objects/js-proxy.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-proxy.tq?l=5&c=1
class TorqueGeneratedJSProxyAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSReceiver);
  // https://crsrc.org/c/v8/src/objects/js-proxy.tq?l=7&c=3
  static constexpr int kTargetOffset = sizeof(JSReceiver);
  static constexpr int kTargetOffsetEnd = kTargetOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-proxy.tq?l=8&c=3
  static constexpr int kHandlerOffset = kTargetOffsetEnd + 1;
  static constexpr int kHandlerOffsetEnd = kHandlerOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kHandlerOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/js-proxy.tq?l=9&c=3
  static constexpr int kFlagsOffset = kHandlerOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;
  static constexpr int kSize = kFlagsOffsetEnd + 1;

  static_assert(kTargetOffset == offsetof(JSProxy, target_),
                "Value of JSProxy::kTargetOffset defined in Torque and offset of field JSProxy::target in C++ do not match");
  static_assert(kHandlerOffset == offsetof(JSProxy, handler_),
                "Value of JSProxy::kHandlerOffset defined in Torque and offset of field JSProxy::handler in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSProxy, flags_),
                "Value of JSProxy::kFlagsOffset defined in Torque and offset of field JSProxy::flags in C++ do not match");
  static_assert(kSize == sizeof(JSProxy));
};

} // namespace internal
} // namespace v8
