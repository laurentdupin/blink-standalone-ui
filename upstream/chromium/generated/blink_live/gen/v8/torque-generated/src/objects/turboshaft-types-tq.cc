#include "src/objects/turboshaft-types.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=17&c=1
class TorqueGeneratedTurboshaftTypeAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kHeaderSize = sizeof(HeapObjectLayout);

};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=21&c=1
class TorqueGeneratedTurboshaftWord32TypeAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kHeaderSize = sizeof(TurboshaftType);

};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=25&c=1
class TorqueGeneratedTurboshaftWord32RangeTypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=27&c=3
  static constexpr int kFromOffset = sizeof(TurboshaftWord32Type);
  static constexpr int kFromOffsetEnd = kFromOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=28&c=3
  static constexpr int kToOffset = kFromOffsetEnd + 1;
  static constexpr int kToOffsetEnd = kToOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kToOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kToOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kToOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kToOffsetEnd + 1;
  static constexpr int kHeaderSize = kToOffsetEnd + 1;
  static constexpr int kSize = kToOffsetEnd + 1;

  static_assert(kFromOffset == offsetof(TurboshaftWord32RangeType, from_),
                "Value of TurboshaftWord32RangeType::kFromOffset defined in Torque and offset of field TurboshaftWord32RangeType::from in C++ do not match");
  static_assert(kToOffset == offsetof(TurboshaftWord32RangeType, to_),
                "Value of TurboshaftWord32RangeType::kToOffset defined in Torque and offset of field TurboshaftWord32RangeType::to in C++ do not match");
  static_assert(kSize == sizeof(TurboshaftWord32RangeType));
};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=31&c=1
class TorqueGeneratedTurboshaftWord32SetTypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=33&c=9
  static constexpr int kSetSizeOffset = sizeof(TurboshaftWord32Type);
  static constexpr int kSetSizeOffsetEnd = kSetSizeOffset + kInt32Size - 1;
  static constexpr int kHeaderSize = kSetSizeOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=34&c=3
  static constexpr int kElementsOffset = kSetSizeOffsetEnd + 1;
  static constexpr int kElementsOffsetEnd = kElementsOffset + 0 - 1;
  static constexpr int kStartOfWeakFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kElementsOffsetEnd + 1;

  static_assert(kSetSizeOffset == offsetof(TurboshaftWord32SetType, set_size_),
                "Value of TurboshaftWord32SetType::kSetSizeOffset defined in Torque and offset of field TurboshaftWord32SetType::set_size in C++ do not match");
  static_assert(kElementsOffset == OFFSET_OF_DATA_START(TurboshaftWord32SetType),
                "Value of TurboshaftWord32SetType::kElementsOffset defined in Torque and offset of field TurboshaftWord32SetType::elements in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=37&c=1
class TorqueGeneratedTurboshaftWord64TypeAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(TurboshaftType);
  static constexpr int kHeaderSize = sizeof(TurboshaftType);

};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=41&c=1
class TorqueGeneratedTurboshaftWord64RangeTypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=43&c=3
  static constexpr int kFromHighOffset = sizeof(TurboshaftWord64Type);
  static constexpr int kFromHighOffsetEnd = kFromHighOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=44&c=3
  static constexpr int kFromLowOffset = kFromHighOffsetEnd + 1;
  static constexpr int kFromLowOffsetEnd = kFromLowOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=45&c=3
  static constexpr int kToHighOffset = kFromLowOffsetEnd + 1;
  static constexpr int kToHighOffsetEnd = kToHighOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=46&c=3
  static constexpr int kToLowOffset = kToHighOffsetEnd + 1;
  static constexpr int kToLowOffsetEnd = kToLowOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kToLowOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kToLowOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kToLowOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kToLowOffsetEnd + 1;
  static constexpr int kHeaderSize = kToLowOffsetEnd + 1;
  static constexpr int kSize = kToLowOffsetEnd + 1;

  static_assert(kFromHighOffset == offsetof(TurboshaftWord64RangeType, from_high_),
                "Value of TurboshaftWord64RangeType::kFromHighOffset defined in Torque and offset of field TurboshaftWord64RangeType::from_high in C++ do not match");
  static_assert(kFromLowOffset == offsetof(TurboshaftWord64RangeType, from_low_),
                "Value of TurboshaftWord64RangeType::kFromLowOffset defined in Torque and offset of field TurboshaftWord64RangeType::from_low in C++ do not match");
  static_assert(kToHighOffset == offsetof(TurboshaftWord64RangeType, to_high_),
                "Value of TurboshaftWord64RangeType::kToHighOffset defined in Torque and offset of field TurboshaftWord64RangeType::to_high in C++ do not match");
  static_assert(kToLowOffset == offsetof(TurboshaftWord64RangeType, to_low_),
                "Value of TurboshaftWord64RangeType::kToLowOffset defined in Torque and offset of field TurboshaftWord64RangeType::to_low in C++ do not match");
  static_assert(kSize == sizeof(TurboshaftWord64RangeType));
};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=49&c=1
class TorqueGeneratedTurboshaftWord64SetTypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=51&c=9
  static constexpr int kSetSizeOffset = sizeof(TurboshaftWord64Type);
  static constexpr int kSetSizeOffsetEnd = kSetSizeOffset + kInt32Size - 1;
  static constexpr int kHeaderSize = kSetSizeOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=52&c=3
  static constexpr int kElementsHighOffset = kSetSizeOffsetEnd + 1;
  static constexpr int kElementsHighOffsetEnd = kElementsHighOffset + 0 - 1;
  static constexpr int kStartOfWeakFieldsOffset = kElementsHighOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kElementsHighOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kElementsHighOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kElementsHighOffsetEnd + 1;

  static_assert(kSetSizeOffset == offsetof(TurboshaftWord64SetType, set_size_),
                "Value of TurboshaftWord64SetType::kSetSizeOffset defined in Torque and offset of field TurboshaftWord64SetType::set_size in C++ do not match");
  static_assert(kElementsHighOffset == OFFSET_OF_DATA_START(TurboshaftWord64SetType),
                "Value of TurboshaftWord64SetType::kElementsHighOffset defined in Torque and offset of field TurboshaftWord64SetType::elements_high in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=56&c=1
class TorqueGeneratedTurboshaftFloat64TypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=59&c=3
  static constexpr int kSpecialValuesOffset = sizeof(TurboshaftType);
  static constexpr int kSpecialValuesOffsetEnd = kSpecialValuesOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kSpecialValuesOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kSpecialValuesOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kSpecialValuesOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kSpecialValuesOffsetEnd + 1;
  static constexpr int kHeaderSize = kSpecialValuesOffsetEnd + 1;

  static_assert(kSpecialValuesOffset == offsetof(TurboshaftFloat64Type, special_values_),
                "Value of TurboshaftFloat64Type::kSpecialValuesOffset defined in Torque and offset of field TurboshaftFloat64Type::special_values in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=62&c=1
class TorqueGeneratedTurboshaftFloat64RangeTypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=64&c=3
  static constexpr int kPaddingOffset = sizeof(TurboshaftFloat64Type);
  static constexpr int kPaddingOffsetEnd = kPaddingOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=65&c=3
  static constexpr int kMinOffset = kPaddingOffsetEnd + 1;
  static constexpr int kMinOffsetEnd = kMinOffset + kDoubleSize - 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=66&c=3
  static constexpr int kMaxOffset = kMinOffsetEnd + 1;
  static constexpr int kMaxOffsetEnd = kMaxOffset + kDoubleSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kMaxOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kMaxOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kMaxOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kMaxOffsetEnd + 1;
  static constexpr int kHeaderSize = kMaxOffsetEnd + 1;
  static constexpr int kSize = kMaxOffsetEnd + 1;

  static_assert(kPaddingOffset == offsetof(TurboshaftFloat64RangeType, _padding_),
                "Value of TurboshaftFloat64RangeType::kPaddingOffset defined in Torque and offset of field TurboshaftFloat64RangeType::_padding in C++ do not match");
  static_assert(kMinOffset == offsetof(TurboshaftFloat64RangeType, min_),
                "Value of TurboshaftFloat64RangeType::kMinOffset defined in Torque and offset of field TurboshaftFloat64RangeType::min in C++ do not match");
  static_assert(kMaxOffset == offsetof(TurboshaftFloat64RangeType, max_),
                "Value of TurboshaftFloat64RangeType::kMaxOffset defined in Torque and offset of field TurboshaftFloat64RangeType::max in C++ do not match");
  static_assert(kSize == sizeof(TurboshaftFloat64RangeType));
};

// Definition https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=69&c=1
class TorqueGeneratedTurboshaftFloat64SetTypeAsserts {
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=71&c=9
  static constexpr int kSetSizeOffset = sizeof(TurboshaftFloat64Type);
  static constexpr int kSetSizeOffsetEnd = kSetSizeOffset + kInt32Size - 1;
  static constexpr int kHeaderSize = kSetSizeOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/turboshaft-types.tq?l=72&c=3
  static constexpr int kElementsOffset = kSetSizeOffsetEnd + 1;
  static constexpr int kElementsOffsetEnd = kElementsOffset + 0 - 1;
  static constexpr int kStartOfWeakFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kElementsOffsetEnd + 1;

  static_assert(kSetSizeOffset == offsetof(TurboshaftFloat64SetType, set_size_),
                "Value of TurboshaftFloat64SetType::kSetSizeOffset defined in Torque and offset of field TurboshaftFloat64SetType::set_size in C++ do not match");
  static_assert(kElementsOffset == OFFSET_OF_DATA_START(TurboshaftFloat64SetType),
                "Value of TurboshaftFloat64SetType::kElementsOffset defined in Torque and offset of field TurboshaftFloat64SetType::elements in C++ do not match");
};

} // namespace internal
} // namespace v8
