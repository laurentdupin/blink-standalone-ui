#include "src/objects/map.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/map.tq?l=37&c=1
class TorqueGeneratedMapAsserts {
  // https://crsrc.org/c/v8/src/objects/map.tq?l=72&c=3
  static constexpr int kInstanceSizeInWordsOffset = sizeof(HeapObjectLayout);
  static constexpr int kInstanceSizeInWordsOffsetEnd = kInstanceSizeInWordsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=73&c=3
  static constexpr int kInobjectPropertiesStartOrConstructorFunctionIndexOffset = kInstanceSizeInWordsOffsetEnd + 1;
  static constexpr int kInobjectPropertiesStartOrConstructorFunctionIndexOffsetEnd = kInobjectPropertiesStartOrConstructorFunctionIndexOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=74&c=3
  static constexpr int kUsedOrUnusedInstanceSizeInWordsOffset = kInobjectPropertiesStartOrConstructorFunctionIndexOffsetEnd + 1;
  static constexpr int kUsedOrUnusedInstanceSizeInWordsOffsetEnd = kUsedOrUnusedInstanceSizeInWordsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=75&c=3
  static constexpr int kVisitorIdOffset = kUsedOrUnusedInstanceSizeInWordsOffsetEnd + 1;
  static constexpr int kVisitorIdOffsetEnd = kVisitorIdOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=76&c=3
  static constexpr int kInstanceTypeOffset = kVisitorIdOffsetEnd + 1;
  static constexpr int kInstanceTypeOffsetEnd = kInstanceTypeOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=77&c=3
  static constexpr int kBitFieldOffset = kInstanceTypeOffsetEnd + 1;
  static constexpr int kBitFieldOffsetEnd = kBitFieldOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=78&c=3
  static constexpr int kBitField2Offset = kBitFieldOffsetEnd + 1;
  static constexpr int kBitField2OffsetEnd = kBitField2Offset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=79&c=3
  static constexpr int kBitField3Offset = kBitField2OffsetEnd + 1;
  static constexpr int kBitField3OffsetEnd = kBitField3Offset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kBitField3OffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=83&c=3
  static constexpr int kPrototypeOffset = kBitField3OffsetEnd + 1;
  static constexpr int kPrototypeOffsetEnd = kPrototypeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=84&c=3
  static constexpr int kConstructorOrBackPointerOrNativeContextOffset = kPrototypeOffsetEnd + 1;
  static constexpr int kConstructorOrBackPointerOrNativeContextOffsetEnd = kConstructorOrBackPointerOrNativeContextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=86&c=30
  static constexpr int kInstanceDescriptorsOffset = kConstructorOrBackPointerOrNativeContextOffsetEnd + 1;
  static constexpr int kInstanceDescriptorsOffsetEnd = kInstanceDescriptorsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=92&c=30
  static constexpr int kDependentCodeOffset = kInstanceDescriptorsOffsetEnd + 1;
  static constexpr int kDependentCodeOffsetEnd = kDependentCodeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=95&c=3
  static constexpr int kPrototypeValidityCellOffset = kDependentCodeOffsetEnd + 1;
  static constexpr int kPrototypeValidityCellOffsetEnd = kPrototypeValidityCellOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPrototypeValidityCellOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPrototypeValidityCellOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=96&c=3
  static constexpr int kTransitionsOrPrototypeInfoOffset = kPrototypeValidityCellOffsetEnd + 1;
  static constexpr int kTransitionsOrPrototypeInfoOffsetEnd = kTransitionsOrPrototypeInfoOffset + kTaggedSize - 1;
  static constexpr int kEndOfWeakFieldsOffset = kTransitionsOrPrototypeInfoOffsetEnd + 1;
  static constexpr int kHeaderSize = kTransitionsOrPrototypeInfoOffsetEnd + 1;
  static constexpr int kSize = kTransitionsOrPrototypeInfoOffsetEnd + 1;

  static_assert(kInstanceSizeInWordsOffset == offsetof(Map, instance_size_in_words_),
                "Value of Map::kInstanceSizeInWordsOffset defined in Torque and offset of field Map::instance_size_in_words in C++ do not match");
  static_assert(kInobjectPropertiesStartOrConstructorFunctionIndexOffset == offsetof(Map, inobject_properties_start_or_constructor_function_index_),
                "Value of Map::kInobjectPropertiesStartOrConstructorFunctionIndexOffset defined in Torque and offset of field Map::inobject_properties_start_or_constructor_function_index in C++ do not match");
  static_assert(kUsedOrUnusedInstanceSizeInWordsOffset == offsetof(Map, used_or_unused_instance_size_in_words_),
                "Value of Map::kUsedOrUnusedInstanceSizeInWordsOffset defined in Torque and offset of field Map::used_or_unused_instance_size_in_words in C++ do not match");
  static_assert(kVisitorIdOffset == offsetof(Map, visitor_id_),
                "Value of Map::kVisitorIdOffset defined in Torque and offset of field Map::visitor_id in C++ do not match");
  static_assert(kInstanceTypeOffset == offsetof(Map, instance_type_),
                "Value of Map::kInstanceTypeOffset defined in Torque and offset of field Map::instance_type in C++ do not match");
  static_assert(kBitFieldOffset == offsetof(Map, bit_field_),
                "Value of Map::kBitFieldOffset defined in Torque and offset of field Map::bit_field in C++ do not match");
  static_assert(kBitField2Offset == offsetof(Map, bit_field2_),
                "Value of Map::kBitField2Offset defined in Torque and offset of field Map::bit_field2 in C++ do not match");
  static_assert(kBitField3Offset == offsetof(Map, bit_field3_),
                "Value of Map::kBitField3Offset defined in Torque and offset of field Map::bit_field3 in C++ do not match");
  static_assert(kPrototypeOffset == offsetof(Map, prototype_),
                "Value of Map::kPrototypeOffset defined in Torque and offset of field Map::prototype in C++ do not match");
  static_assert(kConstructorOrBackPointerOrNativeContextOffset == offsetof(Map, constructor_or_back_pointer_or_native_context_),
                "Value of Map::kConstructorOrBackPointerOrNativeContextOffset defined in Torque and offset of field Map::constructor_or_back_pointer_or_native_context in C++ do not match");
  static_assert(kInstanceDescriptorsOffset == offsetof(Map, instance_descriptors_),
                "Value of Map::kInstanceDescriptorsOffset defined in Torque and offset of field Map::instance_descriptors in C++ do not match");
  static_assert(kDependentCodeOffset == offsetof(Map, dependent_code_),
                "Value of Map::kDependentCodeOffset defined in Torque and offset of field Map::dependent_code in C++ do not match");
  static_assert(kPrototypeValidityCellOffset == offsetof(Map, prototype_validity_cell_),
                "Value of Map::kPrototypeValidityCellOffset defined in Torque and offset of field Map::prototype_validity_cell in C++ do not match");
  static_assert(kTransitionsOrPrototypeInfoOffset == offsetof(Map, transitions_or_prototype_info_),
                "Value of Map::kTransitionsOrPrototypeInfoOffset defined in Torque and offset of field Map::transitions_or_prototype_info in C++ do not match");
  static_assert(kSize == sizeof(Map));
};

// Definition https://crsrc.org/c/v8/src/objects/map.tq?l=111&c=1
class TorqueGeneratedExtendedMapAsserts {
  // https://crsrc.org/c/v8/src/objects/map.tq?l=115&c=3
  static constexpr int kBitFieldExOffset = sizeof(Map);
  static constexpr int kBitFieldExOffsetEnd = kBitFieldExOffset + kUInt8Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kBitFieldExOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBitFieldExOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kBitFieldExOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kBitFieldExOffsetEnd + 1;
  static constexpr int kHeaderSize = kBitFieldExOffsetEnd + 1;
  static constexpr int kSize = kBitFieldExOffsetEnd + 1;

  static_assert(kBitFieldExOffset == offsetof(ExtendedMap, bit_field_ex_),
                "Value of ExtendedMap::kBitFieldExOffset defined in Torque and offset of field ExtendedMap::bit_field_ex in C++ do not match");
  static_assert(kSize == sizeof(ExtendedMap));
};

// Definition https://crsrc.org/c/v8/src/objects/map.tq?l=121&c=1
class TorqueGeneratedJSInterceptorMapAsserts {
  static constexpr int kHeaderSize = sizeof(ExtendedMap);
  // https://crsrc.org/c/v8/src/objects/map.tq?l=125&c=31
  static constexpr int kExtendedPaddingOffset = sizeof(ExtendedMap);
  static constexpr int kExtendedPaddingOffsetEnd = kExtendedPaddingOffset + (3 * kUInt8Size) - 1;
  static constexpr int kStartOfStrongFieldsOffset = kExtendedPaddingOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=127&c=3
  static constexpr int kNamedInterceptorOffset = kExtendedPaddingOffsetEnd + 1;
  static constexpr int kNamedInterceptorOffsetEnd = kNamedInterceptorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/map.tq?l=128&c=3
  static constexpr int kIndexedInterceptorOffset = kNamedInterceptorOffsetEnd + 1;
  static constexpr int kIndexedInterceptorOffsetEnd = kIndexedInterceptorOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIndexedInterceptorOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIndexedInterceptorOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIndexedInterceptorOffsetEnd + 1;
  static constexpr int kSize = kIndexedInterceptorOffsetEnd + 1;

  static_assert(kExtendedPaddingOffset == offsetof(JSInterceptorMap, extended_padding_),
                "Value of JSInterceptorMap::kExtendedPaddingOffset defined in Torque and offset of field JSInterceptorMap::extended_padding in C++ do not match");
  static_assert(kNamedInterceptorOffset == offsetof(JSInterceptorMap, named_interceptor_),
                "Value of JSInterceptorMap::kNamedInterceptorOffset defined in Torque and offset of field JSInterceptorMap::named_interceptor in C++ do not match");
  static_assert(kIndexedInterceptorOffset == offsetof(JSInterceptorMap, indexed_interceptor_),
                "Value of JSInterceptorMap::kIndexedInterceptorOffset defined in Torque and offset of field JSInterceptorMap::indexed_interceptor in C++ do not match");
  static_assert(kSize == sizeof(JSInterceptorMap));
};

} // namespace internal
} // namespace v8
