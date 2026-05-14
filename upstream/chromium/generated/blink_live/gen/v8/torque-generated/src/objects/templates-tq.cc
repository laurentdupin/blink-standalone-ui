#include "src/objects/templates.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/templates.tq?l=11&c=1
class TorqueGeneratedTemplateInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=14&c=3
  static constexpr int kTemplateInfoFlagsOffset = sizeof(HeapObjectLayout);
  static constexpr int kTemplateInfoFlagsOffsetEnd = kTemplateInfoFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kTemplateInfoFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kTemplateInfoFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kTemplateInfoFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kTemplateInfoFlagsOffsetEnd + 1;

  static_assert(kTemplateInfoFlagsOffset == offsetof(TemplateInfo, template_info_flags_),
                "Value of TemplateInfo::kTemplateInfoFlagsOffset defined in Torque and offset of field TemplateInfo::template_info_flags in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/templates.tq?l=17&c=1
class TorqueGeneratedTemplateInfoWithPropertiesAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TemplateInfo);
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=20&c=3
  static constexpr int kNumberOfPropertiesOffset = sizeof(TemplateInfo);
  static constexpr int kNumberOfPropertiesOffsetEnd = kNumberOfPropertiesOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=21&c=3
  static constexpr int kPropertyListOffset = kNumberOfPropertiesOffsetEnd + 1;
  static constexpr int kPropertyListOffsetEnd = kPropertyListOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=22&c=3
  static constexpr int kPropertyAccessorsOffset = kPropertyListOffsetEnd + 1;
  static constexpr int kPropertyAccessorsOffsetEnd = kPropertyAccessorsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPropertyAccessorsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPropertyAccessorsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPropertyAccessorsOffsetEnd + 1;
  static constexpr int kHeaderSize = kPropertyAccessorsOffsetEnd + 1;

  static_assert(kNumberOfPropertiesOffset == offsetof(TemplateInfoWithProperties, number_of_properties_),
                "Value of TemplateInfoWithProperties::kNumberOfPropertiesOffset defined in Torque and offset of field TemplateInfoWithProperties::number_of_properties in C++ do not match");
  static_assert(kPropertyListOffset == offsetof(TemplateInfoWithProperties, property_list_),
                "Value of TemplateInfoWithProperties::kPropertyListOffset defined in Torque and offset of field TemplateInfoWithProperties::property_list in C++ do not match");
  static_assert(kPropertyAccessorsOffset == offsetof(TemplateInfoWithProperties, property_accessors_),
                "Value of TemplateInfoWithProperties::kPropertyAccessorsOffset defined in Torque and offset of field TemplateInfoWithProperties::property_accessors in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/templates.tq?l=57&c=1
class TorqueGeneratedFunctionTemplateInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TemplateInfoWithProperties);
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=59&c=3
  static constexpr int kClassNameOffset = sizeof(TemplateInfoWithProperties);
  static constexpr int kClassNameOffsetEnd = kClassNameOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=63&c=3
  static constexpr int kInterfaceNameOffset = kClassNameOffsetEnd + 1;
  static constexpr int kInterfaceNameOffsetEnd = kInterfaceNameOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=68&c=3
  static constexpr int kSignatureOffset = kInterfaceNameOffsetEnd + 1;
  static constexpr int kSignatureOffsetEnd = kSignatureOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=74&c=3
  static constexpr int kRareDataOffset = kSignatureOffsetEnd + 1;
  static constexpr int kRareDataOffsetEnd = kRareDataOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=75&c=3
  static constexpr int kSharedFunctionInfoOffset = kRareDataOffsetEnd + 1;
  static constexpr int kSharedFunctionInfoOffsetEnd = kSharedFunctionInfoOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=79&c=3
  static constexpr int kCachedPropertyNameOffset = kSharedFunctionInfoOffsetEnd + 1;
  static constexpr int kCachedPropertyNameOffsetEnd = kCachedPropertyNameOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=86&c=36
  static constexpr int kCallbackDataOffset = kCachedPropertyNameOffsetEnd + 1;
  static constexpr int kCallbackDataOffsetEnd = kCallbackDataOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kCallbackDataOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=89&c=3
  static constexpr int kFlagOffset = kCallbackDataOffsetEnd + 1;
  static constexpr int kFlagOffsetEnd = kFlagOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=91&c=3
  static constexpr int kLengthOffset = kFlagOffsetEnd + 1;
  static constexpr int kLengthOffsetEnd = kLengthOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=94&c=3
  static constexpr int kInstanceTypeOffset = kLengthOffsetEnd + 1;
  static constexpr int kInstanceTypeOffsetEnd = kInstanceTypeOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=99&c=3
  static constexpr int kExceptionContextOffset = kInstanceTypeOffsetEnd + 1;
  static constexpr int kExceptionContextOffsetEnd = kExceptionContextOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=107&c=3
  static constexpr int kCallbackOffset = kExceptionContextOffsetEnd + 1;
  static constexpr int kCallbackOffsetEnd = kCallbackOffset + kExternalPointerSlotSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kCallbackOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCallbackOffsetEnd + 1;
  static constexpr int kHeaderSize = kCallbackOffsetEnd + 1;
  static constexpr int kSize = kCallbackOffsetEnd + 1;

  static_assert(kClassNameOffset == offsetof(FunctionTemplateInfo, class_name_),
                "Value of FunctionTemplateInfo::kClassNameOffset defined in Torque and offset of field FunctionTemplateInfo::class_name in C++ do not match");
  static_assert(kInterfaceNameOffset == offsetof(FunctionTemplateInfo, interface_name_),
                "Value of FunctionTemplateInfo::kInterfaceNameOffset defined in Torque and offset of field FunctionTemplateInfo::interface_name in C++ do not match");
  static_assert(kSignatureOffset == offsetof(FunctionTemplateInfo, signature_),
                "Value of FunctionTemplateInfo::kSignatureOffset defined in Torque and offset of field FunctionTemplateInfo::signature in C++ do not match");
  static_assert(kRareDataOffset == offsetof(FunctionTemplateInfo, rare_data_),
                "Value of FunctionTemplateInfo::kRareDataOffset defined in Torque and offset of field FunctionTemplateInfo::rare_data in C++ do not match");
  static_assert(kSharedFunctionInfoOffset == offsetof(FunctionTemplateInfo, shared_function_info_),
                "Value of FunctionTemplateInfo::kSharedFunctionInfoOffset defined in Torque and offset of field FunctionTemplateInfo::shared_function_info in C++ do not match");
  static_assert(kCachedPropertyNameOffset == offsetof(FunctionTemplateInfo, cached_property_name_),
                "Value of FunctionTemplateInfo::kCachedPropertyNameOffset defined in Torque and offset of field FunctionTemplateInfo::cached_property_name in C++ do not match");
  static_assert(kCallbackDataOffset == offsetof(FunctionTemplateInfo, callback_data_),
                "Value of FunctionTemplateInfo::kCallbackDataOffset defined in Torque and offset of field FunctionTemplateInfo::callback_data in C++ do not match");
  static_assert(kFlagOffset == offsetof(FunctionTemplateInfo, flag_),
                "Value of FunctionTemplateInfo::kFlagOffset defined in Torque and offset of field FunctionTemplateInfo::flag in C++ do not match");
  static_assert(kLengthOffset == offsetof(FunctionTemplateInfo, length_),
                "Value of FunctionTemplateInfo::kLengthOffset defined in Torque and offset of field FunctionTemplateInfo::length in C++ do not match");
  static_assert(kInstanceTypeOffset == offsetof(FunctionTemplateInfo, instance_type_),
                "Value of FunctionTemplateInfo::kInstanceTypeOffset defined in Torque and offset of field FunctionTemplateInfo::instance_type in C++ do not match");
  static_assert(kExceptionContextOffset == offsetof(FunctionTemplateInfo, exception_context_),
                "Value of FunctionTemplateInfo::kExceptionContextOffset defined in Torque and offset of field FunctionTemplateInfo::exception_context in C++ do not match");
  static_assert(kCallbackOffset == offsetof(FunctionTemplateInfo, callback_),
                "Value of FunctionTemplateInfo::kCallbackOffset defined in Torque and offset of field FunctionTemplateInfo::callback in C++ do not match");
  static_assert(kSize == sizeof(FunctionTemplateInfo));
};

// Definition https://crsrc.org/c/v8/src/objects/templates.tq?l=25&c=1
class TorqueGeneratedFunctionTemplateRareDataAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(Struct);
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=28&c=3
  static constexpr int kPrototypeTemplateOffset = sizeof(Struct);
  static constexpr int kPrototypeTemplateOffsetEnd = kPrototypeTemplateOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=29&c=3
  static constexpr int kPrototypeProviderTemplateOffset = kPrototypeTemplateOffsetEnd + 1;
  static constexpr int kPrototypeProviderTemplateOffsetEnd = kPrototypeProviderTemplateOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=30&c=3
  static constexpr int kParentTemplateOffset = kPrototypeProviderTemplateOffsetEnd + 1;
  static constexpr int kParentTemplateOffsetEnd = kParentTemplateOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=31&c=3
  static constexpr int kNamedPropertyHandlerOffset = kParentTemplateOffsetEnd + 1;
  static constexpr int kNamedPropertyHandlerOffsetEnd = kNamedPropertyHandlerOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=32&c=3
  static constexpr int kIndexedPropertyHandlerOffset = kNamedPropertyHandlerOffsetEnd + 1;
  static constexpr int kIndexedPropertyHandlerOffsetEnd = kIndexedPropertyHandlerOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=33&c=3
  static constexpr int kInstanceTemplateOffset = kIndexedPropertyHandlerOffsetEnd + 1;
  static constexpr int kInstanceTemplateOffsetEnd = kInstanceTemplateOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=34&c=3
  static constexpr int kInstanceCallHandlerOffset = kInstanceTemplateOffsetEnd + 1;
  static constexpr int kInstanceCallHandlerOffsetEnd = kInstanceCallHandlerOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=35&c=3
  static constexpr int kAccessCheckInfoOffset = kInstanceCallHandlerOffsetEnd + 1;
  static constexpr int kAccessCheckInfoOffsetEnd = kAccessCheckInfoOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=36&c=3
  static constexpr int kCFunctionOverloadsOffset = kAccessCheckInfoOffsetEnd + 1;
  static constexpr int kCFunctionOverloadsOffsetEnd = kCFunctionOverloadsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kCFunctionOverloadsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kCFunctionOverloadsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCFunctionOverloadsOffsetEnd + 1;
  static constexpr int kHeaderSize = kCFunctionOverloadsOffsetEnd + 1;
  static constexpr int kSize = kCFunctionOverloadsOffsetEnd + 1;

  static_assert(kPrototypeTemplateOffset == offsetof(FunctionTemplateRareData, prototype_template_),
                "Value of FunctionTemplateRareData::kPrototypeTemplateOffset defined in Torque and offset of field FunctionTemplateRareData::prototype_template in C++ do not match");
  static_assert(kPrototypeProviderTemplateOffset == offsetof(FunctionTemplateRareData, prototype_provider_template_),
                "Value of FunctionTemplateRareData::kPrototypeProviderTemplateOffset defined in Torque and offset of field FunctionTemplateRareData::prototype_provider_template in C++ do not match");
  static_assert(kParentTemplateOffset == offsetof(FunctionTemplateRareData, parent_template_),
                "Value of FunctionTemplateRareData::kParentTemplateOffset defined in Torque and offset of field FunctionTemplateRareData::parent_template in C++ do not match");
  static_assert(kNamedPropertyHandlerOffset == offsetof(FunctionTemplateRareData, named_property_handler_),
                "Value of FunctionTemplateRareData::kNamedPropertyHandlerOffset defined in Torque and offset of field FunctionTemplateRareData::named_property_handler in C++ do not match");
  static_assert(kIndexedPropertyHandlerOffset == offsetof(FunctionTemplateRareData, indexed_property_handler_),
                "Value of FunctionTemplateRareData::kIndexedPropertyHandlerOffset defined in Torque and offset of field FunctionTemplateRareData::indexed_property_handler in C++ do not match");
  static_assert(kInstanceTemplateOffset == offsetof(FunctionTemplateRareData, instance_template_),
                "Value of FunctionTemplateRareData::kInstanceTemplateOffset defined in Torque and offset of field FunctionTemplateRareData::instance_template in C++ do not match");
  static_assert(kInstanceCallHandlerOffset == offsetof(FunctionTemplateRareData, instance_call_handler_),
                "Value of FunctionTemplateRareData::kInstanceCallHandlerOffset defined in Torque and offset of field FunctionTemplateRareData::instance_call_handler in C++ do not match");
  static_assert(kAccessCheckInfoOffset == offsetof(FunctionTemplateRareData, access_check_info_),
                "Value of FunctionTemplateRareData::kAccessCheckInfoOffset defined in Torque and offset of field FunctionTemplateRareData::access_check_info in C++ do not match");
  static_assert(kCFunctionOverloadsOffset == offsetof(FunctionTemplateRareData, c_function_overloads_),
                "Value of FunctionTemplateRareData::kCFunctionOverloadsOffset defined in Torque and offset of field FunctionTemplateRareData::c_function_overloads in C++ do not match");
  static_assert(kSize == sizeof(FunctionTemplateRareData));
};

// Definition https://crsrc.org/c/v8/src/objects/templates.tq?l=116&c=1
class TorqueGeneratedObjectTemplateInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TemplateInfoWithProperties);
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=118&c=3
  static constexpr int kConstructorOffset = sizeof(TemplateInfoWithProperties);
  static constexpr int kConstructorOffsetEnd = kConstructorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=119&c=3
  static constexpr int kDataOffset = kConstructorOffsetEnd + 1;
  static constexpr int kDataOffsetEnd = kDataOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataOffsetEnd + 1;
  static constexpr int kHeaderSize = kDataOffsetEnd + 1;
  static constexpr int kSize = kDataOffsetEnd + 1;

  static_assert(kConstructorOffset == offsetof(ObjectTemplateInfo, constructor_),
                "Value of ObjectTemplateInfo::kConstructorOffset defined in Torque and offset of field ObjectTemplateInfo::constructor in C++ do not match");
  static_assert(kDataOffset == offsetof(ObjectTemplateInfo, data_),
                "Value of ObjectTemplateInfo::kDataOffset defined in Torque and offset of field ObjectTemplateInfo::data in C++ do not match");
  static_assert(kSize == sizeof(ObjectTemplateInfo));
};

// Definition https://crsrc.org/c/v8/src/objects/templates.tq?l=122&c=1
class TorqueGeneratedDictionaryTemplateInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TemplateInfo);
  // https://crsrc.org/c/v8/src/objects/templates.tq?l=124&c=3
  static constexpr int kPropertyNamesOffset = sizeof(TemplateInfo);
  static constexpr int kPropertyNamesOffsetEnd = kPropertyNamesOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPropertyNamesOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPropertyNamesOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPropertyNamesOffsetEnd + 1;
  static constexpr int kHeaderSize = kPropertyNamesOffsetEnd + 1;
  static constexpr int kSize = kPropertyNamesOffsetEnd + 1;

  static_assert(kPropertyNamesOffset == offsetof(DictionaryTemplateInfo, property_names_),
                "Value of DictionaryTemplateInfo::kPropertyNamesOffset defined in Torque and offset of field DictionaryTemplateInfo::property_names in C++ do not match");
  static_assert(kSize == sizeof(DictionaryTemplateInfo));
};

} // namespace internal
} // namespace v8
