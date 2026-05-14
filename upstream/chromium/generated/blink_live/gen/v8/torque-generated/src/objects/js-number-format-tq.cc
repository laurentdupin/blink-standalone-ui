#include "src/objects/js-number-format.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-number-format.tq?l=7&c=1
class TorqueGeneratedJSNumberFormatAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-number-format.tq?l=9&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-number-format.tq?l=10&c=3
  static constexpr int kIcuNumberFormatterOffset = kLocaleOffsetEnd + 1;
  static constexpr int kIcuNumberFormatterOffsetEnd = kIcuNumberFormatterOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-number-format.tq?l=12&c=3
  static constexpr int kBoundFormatOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kBoundFormatOffsetEnd = kBoundFormatOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kBoundFormatOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kBoundFormatOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBoundFormatOffsetEnd + 1;
  static constexpr int kHeaderSize = kBoundFormatOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSNumberFormat, locale_),
                "Value of JSNumberFormat::kLocaleOffset defined in Torque and offset of field JSNumberFormat::locale in C++ do not match");
  static_assert(kIcuNumberFormatterOffset == offsetof(JSNumberFormat, icu_number_formatter_),
                "Value of JSNumberFormat::kIcuNumberFormatterOffset defined in Torque and offset of field JSNumberFormat::icu_number_formatter in C++ do not match");
  static_assert(kBoundFormatOffset == offsetof(JSNumberFormat, bound_format_),
                "Value of JSNumberFormat::kBoundFormatOffset defined in Torque and offset of field JSNumberFormat::bound_format in C++ do not match");
};

} // namespace internal
} // namespace v8
