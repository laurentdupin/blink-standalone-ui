#include "src/objects/api-callbacks.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=13&c=1
class TorqueGeneratedInterceptorInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=15&c=3
  static constexpr int kDataOffset = sizeof(HeapObjectLayout);
  static constexpr int kDataOffsetEnd = kDataOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=16&c=3
  static constexpr int kFlagsOffset = kDataOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=18&c=3
  static constexpr int kGetterOffset = kFlagsOffsetEnd + 1;
  static constexpr int kGetterOffsetEnd = kGetterOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=19&c=3
  static constexpr int kSetterOffset = kGetterOffsetEnd + 1;
  static constexpr int kSetterOffsetEnd = kSetterOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=20&c=3
  static constexpr int kQueryOffset = kSetterOffsetEnd + 1;
  static constexpr int kQueryOffsetEnd = kQueryOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=21&c=3
  static constexpr int kDescriptorOffset = kQueryOffsetEnd + 1;
  static constexpr int kDescriptorOffsetEnd = kDescriptorOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=22&c=3
  static constexpr int kDeleterOffset = kDescriptorOffsetEnd + 1;
  static constexpr int kDeleterOffsetEnd = kDeleterOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=23&c=3
  static constexpr int kEnumeratorOffset = kDeleterOffsetEnd + 1;
  static constexpr int kEnumeratorOffsetEnd = kEnumeratorOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=24&c=3
  static constexpr int kDefinerOffset = kEnumeratorOffsetEnd + 1;
  static constexpr int kDefinerOffsetEnd = kDefinerOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=26&c=3
  static constexpr int kIndexOfOffset = kDefinerOffsetEnd + 1;
  static constexpr int kIndexOfOffsetEnd = kIndexOfOffset + kExternalPointerSlotSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kIndexOfOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIndexOfOffsetEnd + 1;
  static constexpr int kHeaderSize = kIndexOfOffsetEnd + 1;
  static constexpr int kSize = kIndexOfOffsetEnd + 1;

  static_assert(kDataOffset == offsetof(InterceptorInfo, data_),
                "Value of InterceptorInfo::kDataOffset defined in Torque and offset of field InterceptorInfo::data in C++ do not match");
  static_assert(kFlagsOffset == offsetof(InterceptorInfo, flags_),
                "Value of InterceptorInfo::kFlagsOffset defined in Torque and offset of field InterceptorInfo::flags in C++ do not match");
  static_assert(kGetterOffset == offsetof(InterceptorInfo, getter_),
                "Value of InterceptorInfo::kGetterOffset defined in Torque and offset of field InterceptorInfo::getter in C++ do not match");
  static_assert(kSetterOffset == offsetof(InterceptorInfo, setter_),
                "Value of InterceptorInfo::kSetterOffset defined in Torque and offset of field InterceptorInfo::setter in C++ do not match");
  static_assert(kQueryOffset == offsetof(InterceptorInfo, query_),
                "Value of InterceptorInfo::kQueryOffset defined in Torque and offset of field InterceptorInfo::query in C++ do not match");
  static_assert(kDescriptorOffset == offsetof(InterceptorInfo, descriptor_),
                "Value of InterceptorInfo::kDescriptorOffset defined in Torque and offset of field InterceptorInfo::descriptor in C++ do not match");
  static_assert(kDeleterOffset == offsetof(InterceptorInfo, deleter_),
                "Value of InterceptorInfo::kDeleterOffset defined in Torque and offset of field InterceptorInfo::deleter in C++ do not match");
  static_assert(kEnumeratorOffset == offsetof(InterceptorInfo, enumerator_),
                "Value of InterceptorInfo::kEnumeratorOffset defined in Torque and offset of field InterceptorInfo::enumerator in C++ do not match");
  static_assert(kDefinerOffset == offsetof(InterceptorInfo, definer_),
                "Value of InterceptorInfo::kDefinerOffset defined in Torque and offset of field InterceptorInfo::definer in C++ do not match");
  static_assert(kIndexOfOffset == offsetof(InterceptorInfo, index_of_),
                "Value of InterceptorInfo::kIndexOfOffset defined in Torque and offset of field InterceptorInfo::index_of in C++ do not match");
  static_assert(kSize == sizeof(InterceptorInfo));
};

// Definition https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=29&c=1
class TorqueGeneratedAccessCheckInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(Struct);
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=31&c=3
  static constexpr int kCallbackOffset = sizeof(Struct);
  static constexpr int kCallbackOffsetEnd = kCallbackOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=32&c=3
  static constexpr int kNamedInterceptorOffset = kCallbackOffsetEnd + 1;
  static constexpr int kNamedInterceptorOffsetEnd = kNamedInterceptorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=33&c=3
  static constexpr int kIndexedInterceptorOffset = kNamedInterceptorOffsetEnd + 1;
  static constexpr int kIndexedInterceptorOffsetEnd = kIndexedInterceptorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=34&c=3
  static constexpr int kDataOffset = kIndexedInterceptorOffsetEnd + 1;
  static constexpr int kDataOffsetEnd = kDataOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataOffsetEnd + 1;
  static constexpr int kHeaderSize = kDataOffsetEnd + 1;
  static constexpr int kSize = kDataOffsetEnd + 1;

  static_assert(kCallbackOffset == offsetof(AccessCheckInfo, callback_),
                "Value of AccessCheckInfo::kCallbackOffset defined in Torque and offset of field AccessCheckInfo::callback in C++ do not match");
  static_assert(kNamedInterceptorOffset == offsetof(AccessCheckInfo, named_interceptor_),
                "Value of AccessCheckInfo::kNamedInterceptorOffset defined in Torque and offset of field AccessCheckInfo::named_interceptor in C++ do not match");
  static_assert(kIndexedInterceptorOffset == offsetof(AccessCheckInfo, indexed_interceptor_),
                "Value of AccessCheckInfo::kIndexedInterceptorOffset defined in Torque and offset of field AccessCheckInfo::indexed_interceptor in C++ do not match");
  static_assert(kDataOffset == offsetof(AccessCheckInfo, data_),
                "Value of AccessCheckInfo::kDataOffset defined in Torque and offset of field AccessCheckInfo::data in C++ do not match");
  static_assert(kSize == sizeof(AccessCheckInfo));
};

// Definition https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=47&c=1
class TorqueGeneratedAccessorInfoAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=49&c=3
  static constexpr int kDataOffset = sizeof(HeapObjectLayout);
  static constexpr int kDataOffsetEnd = kDataOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=58&c=3
  static constexpr int kNameOffset = kDataOffsetEnd + 1;
  static constexpr int kNameOffsetEnd = kNameOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kNameOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=62&c=3
  static constexpr int kGetterOffset = kNameOffsetEnd + 1;
  static constexpr int kGetterOffsetEnd = kGetterOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=63&c=3
  static constexpr int kSetterOffset = kGetterOffsetEnd + 1;
  static constexpr int kSetterOffsetEnd = kSetterOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/api-callbacks.tq?l=64&c=3
  static constexpr int kFlagsOffset = kSetterOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;
  static constexpr int kSize = kFlagsOffsetEnd + 1;

  static_assert(kDataOffset == offsetof(AccessorInfo, data_),
                "Value of AccessorInfo::kDataOffset defined in Torque and offset of field AccessorInfo::data in C++ do not match");
  static_assert(kNameOffset == offsetof(AccessorInfo, name_),
                "Value of AccessorInfo::kNameOffset defined in Torque and offset of field AccessorInfo::name in C++ do not match");
  static_assert(kGetterOffset == offsetof(AccessorInfo, getter_),
                "Value of AccessorInfo::kGetterOffset defined in Torque and offset of field AccessorInfo::getter in C++ do not match");
  static_assert(kSetterOffset == offsetof(AccessorInfo, setter_),
                "Value of AccessorInfo::kSetterOffset defined in Torque and offset of field AccessorInfo::setter in C++ do not match");
  static_assert(kFlagsOffset == offsetof(AccessorInfo, flags_),
                "Value of AccessorInfo::kFlagsOffset defined in Torque and offset of field AccessorInfo::flags in C++ do not match");
  static_assert(kSize == sizeof(AccessorInfo));
};

} // namespace internal
} // namespace v8
