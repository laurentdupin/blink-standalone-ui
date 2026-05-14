#include "src/objects/js-plural-rules.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-plural-rules.tq?l=12&c=1
class TorqueGeneratedJSPluralRulesAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-plural-rules.tq?l=14&c=3
  static constexpr int kLocaleOffset = sizeof(JSObject);
  static constexpr int kLocaleOffsetEnd = kLocaleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-plural-rules.tq?l=15&c=3
  static constexpr int kFlagsOffset = kLocaleOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-plural-rules.tq?l=16&c=3
  static constexpr int kIcuPluralRulesOffset = kFlagsOffsetEnd + 1;
  static constexpr int kIcuPluralRulesOffsetEnd = kIcuPluralRulesOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-plural-rules.tq?l=17&c=3
  static constexpr int kIcuNumberFormatterOffset = kIcuPluralRulesOffsetEnd + 1;
  static constexpr int kIcuNumberFormatterOffsetEnd = kIcuNumberFormatterOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIcuNumberFormatterOffsetEnd + 1;
  static constexpr int kHeaderSize = kIcuNumberFormatterOffsetEnd + 1;

  static_assert(kLocaleOffset == offsetof(JSPluralRules, locale_),
                "Value of JSPluralRules::kLocaleOffset defined in Torque and offset of field JSPluralRules::locale in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSPluralRules, flags_),
                "Value of JSPluralRules::kFlagsOffset defined in Torque and offset of field JSPluralRules::flags in C++ do not match");
  static_assert(kIcuPluralRulesOffset == offsetof(JSPluralRules, icu_plural_rules_),
                "Value of JSPluralRules::kIcuPluralRulesOffset defined in Torque and offset of field JSPluralRules::icu_plural_rules in C++ do not match");
  static_assert(kIcuNumberFormatterOffset == offsetof(JSPluralRules, icu_number_formatter_),
                "Value of JSPluralRules::kIcuNumberFormatterOffset defined in Torque and offset of field JSPluralRules::icu_number_formatter in C++ do not match");
};

} // namespace internal
} // namespace v8
