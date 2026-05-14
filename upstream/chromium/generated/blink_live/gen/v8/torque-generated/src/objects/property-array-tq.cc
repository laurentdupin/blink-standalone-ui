#include "src/objects/property-array.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/property-array.tq?l=5&c=1
class TorqueGeneratedPropertyArrayAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/property-array.tq?l=7&c=3
  static constexpr int kLengthAndHashOffset = sizeof(HeapObjectLayout);
  static constexpr int kLengthAndHashOffsetEnd = kLengthAndHashOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kLengthAndHashOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kLengthAndHashOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kLengthAndHashOffsetEnd + 1;
  static constexpr int kHeaderSize = kLengthAndHashOffsetEnd + 1;
  static constexpr int kSize = kLengthAndHashOffsetEnd + 1;

  static_assert(kLengthAndHashOffset == offsetof(PropertyArray, length_and_hash_),
                "Value of PropertyArray::kLengthAndHashOffset defined in Torque and offset of field PropertyArray::length_and_hash in C++ do not match");
  static_assert(kSize == sizeof(PropertyArray));
};

} // namespace internal
} // namespace v8
