#include "src/objects/js-locale.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-locale.tq?l=7&c=1
class TorqueGeneratedJSLocaleAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-locale.tq?l=9&c=3
  static constexpr int kIcuLocaleOffset = sizeof(JSObject);
  static constexpr int kIcuLocaleOffsetEnd = kIcuLocaleOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIcuLocaleOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIcuLocaleOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIcuLocaleOffsetEnd + 1;
  static constexpr int kHeaderSize = kIcuLocaleOffsetEnd + 1;

  static_assert(kIcuLocaleOffset == offsetof(JSLocale, icu_locale_),
                "Value of JSLocale::kIcuLocaleOffset defined in Torque and offset of field JSLocale::icu_locale in C++ do not match");
};

} // namespace internal
} // namespace v8
