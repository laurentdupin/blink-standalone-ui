#include "src/objects/js-break-iterator.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=7&c=1
class TorqueGeneratedJSV8BreakIteratorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=9&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=10&c=3
  static constexpr int kIcuIteratorWithTextOffset = kLocaleOffsetEnd + 1;
  static constexpr int kIcuIteratorWithTextOffsetEnd = kIcuIteratorWithTextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=11&c=3
  static constexpr int kBoundAdoptTextOffset = kIcuIteratorWithTextOffsetEnd + 1;
  static constexpr int kBoundAdoptTextOffsetEnd = kBoundAdoptTextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=12&c=3
  static constexpr int kBoundFirstOffset = kBoundAdoptTextOffsetEnd + 1;
  static constexpr int kBoundFirstOffsetEnd = kBoundFirstOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=13&c=3
  static constexpr int kBoundNextOffset = kBoundFirstOffsetEnd + 1;
  static constexpr int kBoundNextOffsetEnd = kBoundNextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=14&c=3
  static constexpr int kBoundCurrentOffset = kBoundNextOffsetEnd + 1;
  static constexpr int kBoundCurrentOffsetEnd = kBoundCurrentOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-break-iterator.tq?l=15&c=3
  static constexpr int kBoundBreakTypeOffset = kBoundCurrentOffsetEnd + 1;
  static constexpr int kBoundBreakTypeOffsetEnd = kBoundBreakTypeOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kBoundBreakTypeOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kBoundBreakTypeOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBoundBreakTypeOffsetEnd + 1;
  static constexpr int kHeaderSize = kBoundBreakTypeOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSV8BreakIterator, locale_),
                "Value of JSV8BreakIterator::kLocaleOffset defined in Torque and offset of field JSV8BreakIterator::locale in C++ do not match");
  static_assert(kIcuIteratorWithTextOffset == offsetof(JSV8BreakIterator, icu_iterator_with_text_),
                "Value of JSV8BreakIterator::kIcuIteratorWithTextOffset defined in Torque and offset of field JSV8BreakIterator::icu_iterator_with_text in C++ do not match");
  static_assert(kBoundAdoptTextOffset == offsetof(JSV8BreakIterator, bound_adopt_text_),
                "Value of JSV8BreakIterator::kBoundAdoptTextOffset defined in Torque and offset of field JSV8BreakIterator::bound_adopt_text in C++ do not match");
  static_assert(kBoundFirstOffset == offsetof(JSV8BreakIterator, bound_first_),
                "Value of JSV8BreakIterator::kBoundFirstOffset defined in Torque and offset of field JSV8BreakIterator::bound_first in C++ do not match");
  static_assert(kBoundNextOffset == offsetof(JSV8BreakIterator, bound_next_),
                "Value of JSV8BreakIterator::kBoundNextOffset defined in Torque and offset of field JSV8BreakIterator::bound_next in C++ do not match");
  static_assert(kBoundCurrentOffset == offsetof(JSV8BreakIterator, bound_current_),
                "Value of JSV8BreakIterator::kBoundCurrentOffset defined in Torque and offset of field JSV8BreakIterator::bound_current in C++ do not match");
  static_assert(kBoundBreakTypeOffset == offsetof(JSV8BreakIterator, bound_break_type_),
                "Value of JSV8BreakIterator::kBoundBreakTypeOffset defined in Torque and offset of field JSV8BreakIterator::bound_break_type in C++ do not match");
};

} // namespace internal
} // namespace v8
