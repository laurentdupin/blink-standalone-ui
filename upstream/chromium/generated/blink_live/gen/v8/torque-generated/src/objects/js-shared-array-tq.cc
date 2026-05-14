#include "src/objects/js-shared-array.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-shared-array.tq?l=5&c=1
class TorqueGeneratedJSSharedArrayAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kHeaderSize = sizeof(AlwaysSharedSpaceJSObject);

};

} // namespace internal
} // namespace v8
