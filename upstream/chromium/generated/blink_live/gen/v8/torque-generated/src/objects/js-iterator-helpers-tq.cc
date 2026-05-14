#include "src/objects/js-iterator-helpers.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=14&c=1
class TorqueGeneratedJSIteratorHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=17&c=3
  static constexpr int kStateOffset = sizeof(JSObject);
  static constexpr int kStateOffsetEnd = kStateOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kHeaderSize = kStateOffsetEnd + 1;

  static_assert(kStateOffset == offsetof(JSIteratorHelper, state_),
                "Value of JSIteratorHelper::kStateOffset defined in Torque and offset of field JSIteratorHelper::state in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=20&c=1
class TorqueGeneratedJSIteratorHelperSimpleAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelper);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=23&c=3
  static constexpr int kUnderlyingIteratorOffset = sizeof(JSIteratorHelper);
  static constexpr int kUnderlyingIteratorOffsetEnd = kUnderlyingIteratorOffset + 8 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kUnderlyingIteratorOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kUnderlyingIteratorOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kUnderlyingIteratorOffsetEnd + 1;
  static constexpr int kHeaderSize = kUnderlyingIteratorOffsetEnd + 1;

};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=26&c=1
class TorqueGeneratedJSIteratorMapHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelperSimple);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=28&c=3
  static constexpr int kMapperOffset = sizeof(JSIteratorHelperSimple);
  static constexpr int kMapperOffsetEnd = kMapperOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=29&c=3
  static constexpr int kCounterOffset = kMapperOffsetEnd + 1;
  static constexpr int kCounterOffsetEnd = kCounterOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kCounterOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kCounterOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCounterOffsetEnd + 1;
  static constexpr int kHeaderSize = kCounterOffsetEnd + 1;

  static_assert(kMapperOffset == offsetof(JSIteratorMapHelper, mapper_),
                "Value of JSIteratorMapHelper::kMapperOffset defined in Torque and offset of field JSIteratorMapHelper::mapper in C++ do not match");
  static_assert(kCounterOffset == offsetof(JSIteratorMapHelper, counter_),
                "Value of JSIteratorMapHelper::kCounterOffset defined in Torque and offset of field JSIteratorMapHelper::counter in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=32&c=1
class TorqueGeneratedJSIteratorFilterHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelperSimple);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=34&c=3
  static constexpr int kPredicateOffset = sizeof(JSIteratorHelperSimple);
  static constexpr int kPredicateOffsetEnd = kPredicateOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=35&c=3
  static constexpr int kCounterOffset = kPredicateOffsetEnd + 1;
  static constexpr int kCounterOffsetEnd = kCounterOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kCounterOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kCounterOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCounterOffsetEnd + 1;
  static constexpr int kHeaderSize = kCounterOffsetEnd + 1;

  static_assert(kPredicateOffset == offsetof(JSIteratorFilterHelper, predicate_),
                "Value of JSIteratorFilterHelper::kPredicateOffset defined in Torque and offset of field JSIteratorFilterHelper::predicate in C++ do not match");
  static_assert(kCounterOffset == offsetof(JSIteratorFilterHelper, counter_),
                "Value of JSIteratorFilterHelper::kCounterOffset defined in Torque and offset of field JSIteratorFilterHelper::counter in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=38&c=1
class TorqueGeneratedJSIteratorTakeHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelperSimple);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=40&c=3
  static constexpr int kRemainingOffset = sizeof(JSIteratorHelperSimple);
  static constexpr int kRemainingOffsetEnd = kRemainingOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kRemainingOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kRemainingOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kRemainingOffsetEnd + 1;
  static constexpr int kHeaderSize = kRemainingOffsetEnd + 1;

  static_assert(kRemainingOffset == offsetof(JSIteratorTakeHelper, remaining_),
                "Value of JSIteratorTakeHelper::kRemainingOffset defined in Torque and offset of field JSIteratorTakeHelper::remaining in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=43&c=1
class TorqueGeneratedJSIteratorDropHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelperSimple);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=45&c=3
  static constexpr int kRemainingOffset = sizeof(JSIteratorHelperSimple);
  static constexpr int kRemainingOffsetEnd = kRemainingOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kRemainingOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kRemainingOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kRemainingOffsetEnd + 1;
  static constexpr int kHeaderSize = kRemainingOffsetEnd + 1;

  static_assert(kRemainingOffset == offsetof(JSIteratorDropHelper, remaining_),
                "Value of JSIteratorDropHelper::kRemainingOffset defined in Torque and offset of field JSIteratorDropHelper::remaining in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=48&c=1
class TorqueGeneratedJSIteratorFlatMapHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelperSimple);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=50&c=3
  static constexpr int kMapperOffset = sizeof(JSIteratorHelperSimple);
  static constexpr int kMapperOffsetEnd = kMapperOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=51&c=3
  static constexpr int kCounterOffset = kMapperOffsetEnd + 1;
  static constexpr int kCounterOffsetEnd = kCounterOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=52&c=3
  static constexpr int kInnerIteratorOffset = kCounterOffsetEnd + 1;
  static constexpr int kInnerIteratorOffsetEnd = kInnerIteratorOffset + 8 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kInnerIteratorOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kInnerIteratorOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kInnerIteratorOffsetEnd + 1;
  static constexpr int kHeaderSize = kInnerIteratorOffsetEnd + 1;

  static_assert(kMapperOffset == offsetof(JSIteratorFlatMapHelper, mapper_),
                "Value of JSIteratorFlatMapHelper::kMapperOffset defined in Torque and offset of field JSIteratorFlatMapHelper::mapper in C++ do not match");
  static_assert(kCounterOffset == offsetof(JSIteratorFlatMapHelper, counter_),
                "Value of JSIteratorFlatMapHelper::kCounterOffset defined in Torque and offset of field JSIteratorFlatMapHelper::counter in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=55&c=1
class TorqueGeneratedJSIteratorConcatHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelperSimple);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=57&c=3
  static constexpr int kIterablesOffset = sizeof(JSIteratorHelperSimple);
  static constexpr int kIterablesOffsetEnd = kIterablesOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=58&c=3
  static constexpr int kCurrentOffset = kIterablesOffsetEnd + 1;
  static constexpr int kCurrentOffsetEnd = kCurrentOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kCurrentOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kCurrentOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCurrentOffsetEnd + 1;
  static constexpr int kHeaderSize = kCurrentOffsetEnd + 1;

  static_assert(kIterablesOffset == offsetof(JSIteratorConcatHelper, iterables_),
                "Value of JSIteratorConcatHelper::kIterablesOffset defined in Torque and offset of field JSIteratorConcatHelper::iterables in C++ do not match");
  static_assert(kCurrentOffset == offsetof(JSIteratorConcatHelper, current_),
                "Value of JSIteratorConcatHelper::kCurrentOffset defined in Torque and offset of field JSIteratorConcatHelper::current in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=67&c=1
class TorqueGeneratedJSIteratorZipHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorHelper);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=69&c=3
  static constexpr int kUnderlyingIteratorsOffset = sizeof(JSIteratorHelper);
  static constexpr int kUnderlyingIteratorsOffsetEnd = kUnderlyingIteratorsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=70&c=3
  static constexpr int kModeOffset = kUnderlyingIteratorsOffsetEnd + 1;
  static constexpr int kModeOffsetEnd = kModeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=71&c=3
  static constexpr int kActiveCountOffset = kModeOffsetEnd + 1;
  static constexpr int kActiveCountOffsetEnd = kActiveCountOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=72&c=3
  static constexpr int kPaddingOffset = kActiveCountOffsetEnd + 1;
  static constexpr int kPaddingOffsetEnd = kPaddingOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPaddingOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPaddingOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPaddingOffsetEnd + 1;
  static constexpr int kHeaderSize = kPaddingOffsetEnd + 1;

  static_assert(kUnderlyingIteratorsOffset == offsetof(JSIteratorZipHelper, underlying_iterators_),
                "Value of JSIteratorZipHelper::kUnderlyingIteratorsOffset defined in Torque and offset of field JSIteratorZipHelper::underlying_iterators in C++ do not match");
  static_assert(kModeOffset == offsetof(JSIteratorZipHelper, mode_),
                "Value of JSIteratorZipHelper::kModeOffset defined in Torque and offset of field JSIteratorZipHelper::mode in C++ do not match");
  static_assert(kActiveCountOffset == offsetof(JSIteratorZipHelper, active_count_),
                "Value of JSIteratorZipHelper::kActiveCountOffset defined in Torque and offset of field JSIteratorZipHelper::active_count in C++ do not match");
  static_assert(kPaddingOffset == offsetof(JSIteratorZipHelper, padding_),
                "Value of JSIteratorZipHelper::kPaddingOffset defined in Torque and offset of field JSIteratorZipHelper::padding in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=75&c=1
class TorqueGeneratedJSIteratorZipKeyedHelperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSIteratorZipHelper);
  // https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=77&c=3
  static constexpr int kKeysOffset = sizeof(JSIteratorZipHelper);
  static constexpr int kKeysOffsetEnd = kKeysOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kKeysOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kKeysOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kKeysOffsetEnd + 1;
  static constexpr int kHeaderSize = kKeysOffsetEnd + 1;

  static_assert(kKeysOffset == offsetof(JSIteratorZipKeyedHelper, keys_),
                "Value of JSIteratorZipKeyedHelper::kKeysOffset defined in Torque and offset of field JSIteratorZipKeyedHelper::keys in C++ do not match");
};

} // namespace internal
} // namespace v8
