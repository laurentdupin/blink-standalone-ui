#include "src/objects/js-array.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-array.tq?l=7&c=1
class TorqueGeneratedJSArrayIteratorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=9&c=3
  static constexpr int kIteratedObjectOffset = sizeof(JSObject);
  static constexpr int kIteratedObjectOffsetEnd = kIteratedObjectOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=34&c=3
  static constexpr int kNextIndexOffset = kIteratedObjectOffsetEnd + 1;
  static constexpr int kNextIndexOffsetEnd = kNextIndexOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=36&c=3
  static constexpr int kKindOffset = kNextIndexOffsetEnd + 1;
  static constexpr int kKindOffsetEnd = kKindOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kKindOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kKindOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kKindOffsetEnd + 1;
  static constexpr int kHeaderSize = kKindOffsetEnd + 1;

  static_assert(kIteratedObjectOffset == offsetof(JSArrayIterator, iterated_object_),
                "Value of JSArrayIterator::kIteratedObjectOffset defined in Torque and offset of field JSArrayIterator::iterated_object in C++ do not match");
  static_assert(kNextIndexOffset == offsetof(JSArrayIterator, next_index_),
                "Value of JSArrayIterator::kNextIndexOffset defined in Torque and offset of field JSArrayIterator::next_index in C++ do not match");
  static_assert(kKindOffset == offsetof(JSArrayIterator, kind_),
                "Value of JSArrayIterator::kKindOffset defined in Torque and offset of field JSArrayIterator::kind in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-array.tq?l=62&c=1
class TorqueGeneratedJSArrayAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=67&c=3
  static constexpr int kLengthOffset = sizeof(JSObject);
  static constexpr int kLengthOffsetEnd = kLengthOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kLengthOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kLengthOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kLengthOffsetEnd + 1;
  static constexpr int kHeaderSize = kLengthOffsetEnd + 1;

  static_assert(kLengthOffset == offsetof(JSArray, length_),
                "Value of JSArray::kLengthOffset defined in Torque and offset of field JSArray::length in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-array.tq?l=70&c=1
class TorqueGeneratedTemplateLiteralObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSArray);
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=74&c=3
  static constexpr int kRawOffset = sizeof(JSArray);
  static constexpr int kRawOffsetEnd = kRawOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=75&c=3
  static constexpr int kFunctionLiteralIdOffset = kRawOffsetEnd + 1;
  static constexpr int kFunctionLiteralIdOffsetEnd = kFunctionLiteralIdOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array.tq?l=76&c=3
  static constexpr int kSlotIdOffset = kFunctionLiteralIdOffsetEnd + 1;
  static constexpr int kSlotIdOffsetEnd = kSlotIdOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kSlotIdOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kSlotIdOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kSlotIdOffsetEnd + 1;
  static constexpr int kHeaderSize = kSlotIdOffsetEnd + 1;

  static_assert(kRawOffset == offsetof(TemplateLiteralObject, raw_),
                "Value of TemplateLiteralObject::kRawOffset defined in Torque and offset of field TemplateLiteralObject::raw in C++ do not match");
  static_assert(kFunctionLiteralIdOffset == offsetof(TemplateLiteralObject, function_literal_id_),
                "Value of TemplateLiteralObject::kFunctionLiteralIdOffset defined in Torque and offset of field TemplateLiteralObject::function_literal_id in C++ do not match");
  static_assert(kSlotIdOffset == offsetof(TemplateLiteralObject, slot_id_),
                "Value of TemplateLiteralObject::kSlotIdOffset defined in Torque and offset of field TemplateLiteralObject::slot_id in C++ do not match");
};

} // namespace internal
} // namespace v8
