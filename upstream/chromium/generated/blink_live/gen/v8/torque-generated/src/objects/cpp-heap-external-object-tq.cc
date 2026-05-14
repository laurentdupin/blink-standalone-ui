#include "src/objects/cpp-heap-external-object.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/cpp-heap-external-object.tq?l=5&c=1
class TorqueGeneratedCppHeapExternalObjectAsserts {
  // https://crsrc.org/c/v8/src/objects/cpp-heap-external-object.tq?l=7&c=3
  static constexpr int kCppHeapWrappableOffset = sizeof(HeapObjectLayout);
  static constexpr int kCppHeapWrappableOffsetEnd = kCppHeapWrappableOffset + kCppHeapPointerSlotSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kHeaderSize = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kSize = kCppHeapWrappableOffsetEnd + 1;

  static_assert(kCppHeapWrappableOffset == offsetof(CppHeapExternalObject, cpp_heap_wrappable_),
                "Value of CppHeapExternalObject::kCppHeapWrappableOffset defined in Torque and offset of field CppHeapExternalObject::cpp_heap_wrappable in C++ do not match");
  static_assert(kSize == sizeof(CppHeapExternalObject));
};

} // namespace internal
} // namespace v8
