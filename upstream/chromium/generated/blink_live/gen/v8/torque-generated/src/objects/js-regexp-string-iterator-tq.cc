#include "src/objects/js-regexp-string-iterator.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-regexp-string-iterator.tq?l=11&c=1
class TorqueGeneratedJSRegExpStringIteratorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-regexp-string-iterator.tq?l=14&c=3
  static constexpr int kIteratingRegExpOffset = sizeof(JSObject);
  static constexpr int kIteratingRegExpOffsetEnd = kIteratingRegExpOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-regexp-string-iterator.tq?l=16&c=3
  static constexpr int kIteratedStringOffset = kIteratingRegExpOffsetEnd + 1;
  static constexpr int kIteratedStringOffsetEnd = kIteratedStringOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-regexp-string-iterator.tq?l=17&c=3
  static constexpr int kFlagsOffset = kIteratedStringOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kIteratingRegExpOffset == offsetof(JSRegExpStringIterator, iterating_reg_exp_),
                "Value of JSRegExpStringIterator::kIteratingRegExpOffset defined in Torque and offset of field JSRegExpStringIterator::iterating_reg_exp in C++ do not match");
  static_assert(kIteratedStringOffset == offsetof(JSRegExpStringIterator, iterated_string_),
                "Value of JSRegExpStringIterator::kIteratedStringOffset defined in Torque and offset of field JSRegExpStringIterator::iterated_string in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSRegExpStringIterator, flags_),
                "Value of JSRegExpStringIterator::kFlagsOffset defined in Torque and offset of field JSRegExpStringIterator::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
