#include "src/objects/js-struct.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-struct.tq?l=8&c=1
class TorqueGeneratedAlwaysSharedSpaceJSObjectAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kHeaderSize = sizeof(JSObject);

};

// Definition https://crsrc.org/c/v8/src/objects/js-struct.tq?l=12&c=1
class TorqueGeneratedJSSharedStructAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kHeaderSize = sizeof(AlwaysSharedSpaceJSObject);

};

} // namespace internal
} // namespace v8
