#include "src/objects/js-relative-time-format.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-relative-time-format.tq?l=13&c=1
class TorqueGeneratedJSRelativeTimeFormatAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-relative-time-format.tq?l=15&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-relative-time-format.tq?l=16&c=3
  static constexpr int kNumberingSystemOffset = kLocaleOffsetEnd + 1;
  static constexpr int kNumberingSystemOffsetEnd = kNumberingSystemOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-relative-time-format.tq?l=17&c=3
  static constexpr int kIcuFormatterOffset = kNumberingSystemOffsetEnd + 1;
  static constexpr int kIcuFormatterOffsetEnd = kIcuFormatterOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-relative-time-format.tq?l=18&c=3
  static constexpr int kFlagsOffset = kIcuFormatterOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSRelativeTimeFormat, locale_),
                "Value of JSRelativeTimeFormat::kLocaleOffset defined in Torque and offset of field JSRelativeTimeFormat::locale in C++ do not match");
  static_assert(kNumberingSystemOffset == offsetof(JSRelativeTimeFormat, numberingSystem_),
                "Value of JSRelativeTimeFormat::kNumberingSystemOffset defined in Torque and offset of field JSRelativeTimeFormat::numberingSystem in C++ do not match");
  static_assert(kIcuFormatterOffset == offsetof(JSRelativeTimeFormat, icu_formatter_),
                "Value of JSRelativeTimeFormat::kIcuFormatterOffset defined in Torque and offset of field JSRelativeTimeFormat::icu_formatter in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSRelativeTimeFormat, flags_),
                "Value of JSRelativeTimeFormat::kFlagsOffset defined in Torque and offset of field JSRelativeTimeFormat::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
