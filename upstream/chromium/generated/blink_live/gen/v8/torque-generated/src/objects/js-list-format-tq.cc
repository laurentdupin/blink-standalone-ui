#include "src/objects/js-list-format.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-list-format.tq?l=14&c=1
class TorqueGeneratedJSListFormatAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-list-format.tq?l=16&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-list-format.tq?l=17&c=3
  static constexpr int kIcuFormatterOffset = kLocaleOffsetEnd + 1;
  static constexpr int kIcuFormatterOffsetEnd = kIcuFormatterOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-list-format.tq?l=18&c=3
  static constexpr int kFlagsOffset = kIcuFormatterOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSListFormat, locale_),
                "Value of JSListFormat::kLocaleOffset defined in Torque and offset of field JSListFormat::locale in C++ do not match");
  static_assert(kIcuFormatterOffset == offsetof(JSListFormat, icu_formatter_),
                "Value of JSListFormat::kIcuFormatterOffset defined in Torque and offset of field JSListFormat::icu_formatter in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSListFormat, flags_),
                "Value of JSListFormat::kFlagsOffset defined in Torque and offset of field JSListFormat::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
