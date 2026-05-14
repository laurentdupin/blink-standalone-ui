#include "src/objects/embedder-data-array.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/embedder-data-array.tq?l=5&c=1
class TorqueGeneratedEmbedderDataArrayAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/embedder-data-array.tq?l=8&c=3
  static constexpr int kLengthOffset = sizeof(HeapObjectLayout);
  static constexpr int kLengthOffsetEnd = kLengthOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kLengthOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kLengthOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kLengthOffsetEnd + 1;
  static constexpr int kHeaderSize = kLengthOffsetEnd + 1;
  static constexpr int kSize = kLengthOffsetEnd + 1;

  static_assert(kLengthOffset == offsetof(EmbedderDataArray, length_),
                "Value of EmbedderDataArray::kLengthOffset defined in Torque and offset of field EmbedderDataArray::length in C++ do not match");
  static_assert(kSize == sizeof(EmbedderDataArray));
};

} // namespace internal
} // namespace v8
