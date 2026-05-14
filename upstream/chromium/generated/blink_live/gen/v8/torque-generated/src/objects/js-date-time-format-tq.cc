#include "src/objects/js-date-time-format.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=19&c=1
class TorqueGeneratedJSDateTimeFormatAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=21&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=22&c=3
  static constexpr int kIcuLocaleOffset = kLocaleOffsetEnd + 1;
  static constexpr int kIcuLocaleOffsetEnd = kIcuLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=23&c=3
  static constexpr int kIcuSimpleDateFormatOffset = kIcuLocaleOffsetEnd + 1;
  static constexpr int kIcuSimpleDateFormatOffsetEnd = kIcuSimpleDateFormatOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=24&c=3
  static constexpr int kIcuDateIntervalFormatOffset = kIcuSimpleDateFormatOffsetEnd + 1;
  static constexpr int kIcuDateIntervalFormatOffsetEnd = kIcuDateIntervalFormatOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=25&c=3
  static constexpr int kBoundFormatOffset = kIcuDateIntervalFormatOffsetEnd + 1;
  static constexpr int kBoundFormatOffsetEnd = kBoundFormatOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-date-time-format.tq?l=26&c=3
  static constexpr int kFlagsOffset = kBoundFormatOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSDateTimeFormat, locale_),
                "Value of JSDateTimeFormat::kLocaleOffset defined in Torque and offset of field JSDateTimeFormat::locale in C++ do not match");
  static_assert(kIcuLocaleOffset == offsetof(JSDateTimeFormat, icu_locale_),
                "Value of JSDateTimeFormat::kIcuLocaleOffset defined in Torque and offset of field JSDateTimeFormat::icu_locale in C++ do not match");
  static_assert(kIcuSimpleDateFormatOffset == offsetof(JSDateTimeFormat, icu_simple_date_format_),
                "Value of JSDateTimeFormat::kIcuSimpleDateFormatOffset defined in Torque and offset of field JSDateTimeFormat::icu_simple_date_format in C++ do not match");
  static_assert(kIcuDateIntervalFormatOffset == offsetof(JSDateTimeFormat, icu_date_interval_format_),
                "Value of JSDateTimeFormat::kIcuDateIntervalFormatOffset defined in Torque and offset of field JSDateTimeFormat::icu_date_interval_format in C++ do not match");
  static_assert(kBoundFormatOffset == offsetof(JSDateTimeFormat, bound_format_),
                "Value of JSDateTimeFormat::kBoundFormatOffset defined in Torque and offset of field JSDateTimeFormat::bound_format in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSDateTimeFormat, flags_),
                "Value of JSDateTimeFormat::kFlagsOffset defined in Torque and offset of field JSDateTimeFormat::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
