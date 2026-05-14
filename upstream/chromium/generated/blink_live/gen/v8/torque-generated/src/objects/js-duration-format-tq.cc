#include "src/objects/js-duration-format.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-duration-format.tq?l=43&c=1
class TorqueGeneratedJSDurationFormatAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-duration-format.tq?l=45&c=3
  static constexpr int kStyleFlagsOffset = sizeof(JSObject);
  static constexpr int kStyleFlagsOffsetEnd = kStyleFlagsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-duration-format.tq?l=46&c=3
  static constexpr int kDisplayFlagsOffset = kStyleFlagsOffsetEnd + 1;
  static constexpr int kDisplayFlagsOffsetEnd = kDisplayFlagsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-duration-format.tq?l=47&c=3
  static constexpr int kIcuLocaleOffset = kDisplayFlagsOffsetEnd + 1;
  static constexpr int kIcuLocaleOffsetEnd = kIcuLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-duration-format.tq?l=48&c=3
  static constexpr int kIcuNumberFormatterOffset = kIcuLocaleOffsetEnd + 1;
  static constexpr int kIcuNumberFormatterOffsetEnd = kIcuNumberFormatterOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kHeaderSize = kIcuNumberFormatterOffsetEnd + 1;

  static_assert(kStyleFlagsOffset == offsetof(JSDurationFormat, style_flags_),
                "Value of JSDurationFormat::kStyleFlagsOffset defined in Torque and offset of field JSDurationFormat::style_flags in C++ do not match");
  static_assert(kDisplayFlagsOffset == offsetof(JSDurationFormat, display_flags_),
                "Value of JSDurationFormat::kDisplayFlagsOffset defined in Torque and offset of field JSDurationFormat::display_flags in C++ do not match");
  static_assert(kIcuLocaleOffset == offsetof(JSDurationFormat, icu_locale_),
                "Value of JSDurationFormat::kIcuLocaleOffset defined in Torque and offset of field JSDurationFormat::icu_locale in C++ do not match");
  static_assert(kIcuNumberFormatterOffset == offsetof(JSDurationFormat, icu_number_formatter_),
                "Value of JSDurationFormat::kIcuNumberFormatterOffset defined in Torque and offset of field JSDurationFormat::icu_number_formatter in C++ do not match");
};

} // namespace internal
} // namespace v8
