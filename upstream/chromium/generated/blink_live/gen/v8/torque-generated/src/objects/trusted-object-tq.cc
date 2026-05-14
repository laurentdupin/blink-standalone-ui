#include "src/objects/trusted-object.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/trusted-object.tq?l=5&c=1
class TorqueGeneratedTrustedObjectAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kHeaderSize = sizeof(HeapObjectLayout);

};

// Definition https://crsrc.org/c/v8/src/objects/trusted-object.tq?l=9&c=1
class TorqueGeneratedExposedTrustedObjectAsserts {
  // https://crsrc.org/c/v8/src/objects/trusted-object.tq?l=12&c=26
  static constexpr int kSelfIndirectPointerOffset = sizeof(TrustedObject);
  static constexpr int kSelfIndirectPointerOffsetEnd = kSelfIndirectPointerOffset + kTrustedPointerSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kSelfIndirectPointerOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kSelfIndirectPointerOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kSelfIndirectPointerOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kSelfIndirectPointerOffsetEnd + 1;
  static constexpr int kHeaderSize = kSelfIndirectPointerOffsetEnd + 1;

  static_assert(kSelfIndirectPointerOffset == offsetof(ExposedTrustedObject, self_indirect_pointer_),
                "Value of ExposedTrustedObject::kSelfIndirectPointerOffset defined in Torque and offset of field ExposedTrustedObject::self_indirect_pointer in C++ do not match");
};

} // namespace internal
} // namespace v8
