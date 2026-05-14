#include "src/objects/js-segments.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-segments.tq?l=11&c=1
class TorqueGeneratedJSSegmentsAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-segments.tq?l=13&c=3
  static constexpr int kIcuIteratorWithTextOffset = sizeof(JSObject);
  static constexpr int kIcuIteratorWithTextOffsetEnd = kIcuIteratorWithTextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-segments.tq?l=14&c=3
  static constexpr int kRawStringOffset = kIcuIteratorWithTextOffsetEnd + 1;
  static constexpr int kRawStringOffsetEnd = kRawStringOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-segments.tq?l=15&c=3
  static constexpr int kFlagsOffset = kRawStringOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kIcuIteratorWithTextOffset == offsetof(JSSegments, icu_iterator_with_text_),
                "Value of JSSegments::kIcuIteratorWithTextOffset defined in Torque and offset of field JSSegments::icu_iterator_with_text in C++ do not match");
  static_assert(kRawStringOffset == offsetof(JSSegments, raw_string_),
                "Value of JSSegments::kRawStringOffset defined in Torque and offset of field JSSegments::raw_string in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSSegments, flags_),
                "Value of JSSegments::kFlagsOffset defined in Torque and offset of field JSSegments::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
