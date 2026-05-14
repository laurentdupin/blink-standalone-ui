#include "src/objects/js-collator.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-collator.tq?l=7&c=1
class TorqueGeneratedJSCollatorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-collator.tq?l=9&c=3
  static constexpr int kIcuCollatorOffset = sizeof(JSObject);
  static constexpr int kIcuCollatorOffsetEnd = kIcuCollatorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-collator.tq?l=10&c=3
  static constexpr int kBoundCompareOffset = kIcuCollatorOffsetEnd + 1;
  static constexpr int kBoundCompareOffsetEnd = kBoundCompareOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-collator.tq?l=11&c=3
  static constexpr int kLocaleOffset = kBoundCompareOffsetEnd + 1;
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kLocaleOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kLocaleOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kLocaleOffsetEnd + 1;
  static constexpr int kHeaderSize = kLocaleOffsetEnd + 1;

  static_assert(kIcuCollatorOffset == offsetof(JSCollator, icu_collator_),
                "Value of JSCollator::kIcuCollatorOffset defined in Torque and offset of field JSCollator::icu_collator in C++ do not match");
  static_assert(kBoundCompareOffset == offsetof(JSCollator, bound_compare_),
                "Value of JSCollator::kBoundCompareOffset defined in Torque and offset of field JSCollator::bound_compare in C++ do not match");
  static_assert(kLocaleOffset == offsetof(JSCollator, locale_),
                "Value of JSCollator::kLocaleOffset defined in Torque and offset of field JSCollator::locale in C++ do not match");
};

} // namespace internal
} // namespace v8
