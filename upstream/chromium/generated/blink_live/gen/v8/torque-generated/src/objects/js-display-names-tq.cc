#include "src/objects/js-display-names.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-display-names.tq?l=18&c=1
class TorqueGeneratedJSDisplayNamesAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-display-names.tq?l=20&c=3
  static constexpr int kInternalOffset = sizeof(JSObject);
  static constexpr int kInternalOffsetEnd = kInternalOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-display-names.tq?l=21&c=3
  static constexpr int kFlagsOffset = kInternalOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kInternalOffset == offsetof(JSDisplayNames, internal_),
                "Value of JSDisplayNames::kInternalOffset defined in Torque and offset of field JSDisplayNames::internal in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSDisplayNames, flags_),
                "Value of JSDisplayNames::kFlagsOffset defined in Torque and offset of field JSDisplayNames::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
