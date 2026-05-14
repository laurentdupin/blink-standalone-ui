#include "src/objects/js-segmenter.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-segmenter.tq?l=13&c=1
class TorqueGeneratedJSSegmenterAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-segmenter.tq?l=15&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-segmenter.tq?l=16&c=3
  static constexpr int kIcuBreakIteratorOffset = kLocaleOffsetEnd + 1;
  static constexpr int kIcuBreakIteratorOffsetEnd = kIcuBreakIteratorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-segmenter.tq?l=17&c=3
  static constexpr int kFlagsOffset = kIcuBreakIteratorOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSSegmenter, locale_),
                "Value of JSSegmenter::kLocaleOffset defined in Torque and offset of field JSSegmenter::locale in C++ do not match");
  static_assert(kIcuBreakIteratorOffset == offsetof(JSSegmenter, icu_break_iterator_),
                "Value of JSSegmenter::kIcuBreakIteratorOffset defined in Torque and offset of field JSSegmenter::icu_break_iterator in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSSegmenter, flags_),
                "Value of JSSegmenter::kFlagsOffset defined in Torque and offset of field JSSegmenter::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
