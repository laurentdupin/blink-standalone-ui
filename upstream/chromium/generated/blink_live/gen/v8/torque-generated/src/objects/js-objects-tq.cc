#include "src/objects/js-objects.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=6&c=1
class TorqueGeneratedJSReceiverAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=10&c=3
  static constexpr int kPropertiesOrHashOffset = sizeof(HeapObjectLayout);
  static constexpr int kPropertiesOrHashOffsetEnd = kPropertiesOrHashOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPropertiesOrHashOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPropertiesOrHashOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPropertiesOrHashOffsetEnd + 1;
  static constexpr int kHeaderSize = kPropertiesOrHashOffsetEnd + 1;

  static_assert(kPropertiesOrHashOffset == offsetof(JSReceiver, properties_or_hash_),
                "Value of JSReceiver::kPropertiesOrHashOffset defined in Torque and offset of field JSReceiver::properties_or_hash in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=15&c=1
class TorqueGeneratedJSObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSReceiver);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=35&c=3
  static constexpr int kElementsOffset = sizeof(JSReceiver);
  static constexpr int kElementsOffsetEnd = kElementsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kElementsOffsetEnd + 1;
  static constexpr int kHeaderSize = kElementsOffsetEnd + 1;

  static_assert(kElementsOffset == offsetof(JSObject, elements_),
                "Value of JSObject::kElementsOffset defined in Torque and offset of field JSObject::elements in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=53&c=1
class TorqueGeneratedJSObjectWithEmbedderSlotsAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kHeaderSize = sizeof(JSObject);

};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=58&c=1
class TorqueGeneratedJSAPIObjectWithEmbedderSlotsAsserts {
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=61&c=3
  static constexpr int kCppHeapWrappableOffset = sizeof(JSObject);
  static constexpr int kCppHeapWrappableOffsetEnd = kCppHeapWrappableOffset + kCppHeapPointerSlotSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kHeaderSize = kCppHeapWrappableOffsetEnd + 1;

  static_assert(kCppHeapWrappableOffset == offsetof(JSAPIObjectWithEmbedderSlots, cpp_heap_wrappable_),
                "Value of JSAPIObjectWithEmbedderSlots::kCppHeapWrappableOffset defined in Torque and offset of field JSAPIObjectWithEmbedderSlots::cpp_heap_wrappable in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=64&c=1
class TorqueGeneratedJSCustomElementsObjectAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kHeaderSize = sizeof(JSObject);

};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=72&c=1
class TorqueGeneratedJSSpecialObjectAsserts {
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=77&c=3
  static constexpr int kCppHeapWrappableOffset = sizeof(JSCustomElementsObject);
  static constexpr int kCppHeapWrappableOffsetEnd = kCppHeapWrappableOffset + kCppHeapPointerSlotSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kCppHeapWrappableOffsetEnd + 1;
  static constexpr int kHeaderSize = kCppHeapWrappableOffsetEnd + 1;

  static_assert(kCppHeapWrappableOffset == offsetof(JSSpecialObject, cpp_heap_wrappable_),
                "Value of JSSpecialObject::kCppHeapWrappableOffset defined in Torque and offset of field JSSpecialObject::cpp_heap_wrappable in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=45&c=1
class TorqueGeneratedJSExternalObjectAsserts {
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=47&c=3
  static constexpr int kValueOffset = sizeof(JSObject);
  static constexpr int kValueOffsetEnd = kValueOffset + kExternalPointerSlotSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kHeaderSize = kValueOffsetEnd + 1;

  static_assert(kValueOffset == offsetof(JSExternalObject, value_),
                "Value of JSExternalObject::kValueOffset defined in Torque and offset of field JSExternalObject::value in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=124&c=1
class TorqueGeneratedJSGlobalProxyAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSSpecialObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSSpecialObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSSpecialObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSSpecialObject);
  static constexpr int kHeaderSize = sizeof(JSSpecialObject);

};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=127&c=1
class TorqueGeneratedJSGlobalObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSSpecialObject);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=137&c=3
  static constexpr int kGlobalProxyOffset = sizeof(JSSpecialObject);
  static constexpr int kGlobalProxyOffsetEnd = kGlobalProxyOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=151&c=3
  static constexpr int kGlobalProxyForApiOffset = kGlobalProxyOffsetEnd + 1;
  static constexpr int kGlobalProxyForApiOffsetEnd = kGlobalProxyForApiOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kGlobalProxyForApiOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kGlobalProxyForApiOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kGlobalProxyForApiOffsetEnd + 1;
  static constexpr int kHeaderSize = kGlobalProxyForApiOffsetEnd + 1;

  static_assert(kGlobalProxyOffset == offsetof(JSGlobalObject, global_proxy_),
                "Value of JSGlobalObject::kGlobalProxyOffset defined in Torque and offset of field JSGlobalObject::global_proxy in C++ do not match");
  static_assert(kGlobalProxyForApiOffset == offsetof(JSGlobalObject, global_proxy_for_api_),
                "Value of JSGlobalObject::kGlobalProxyForApiOffset defined in Torque and offset of field JSGlobalObject::global_proxy_for_api in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=154&c=1
class TorqueGeneratedJSPrimitiveWrapperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSCustomElementsObject);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=156&c=3
  static constexpr int kValueOffset = sizeof(JSCustomElementsObject);
  static constexpr int kValueOffsetEnd = kValueOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kValueOffsetEnd + 1;
  static constexpr int kHeaderSize = kValueOffsetEnd + 1;

  static_assert(kValueOffset == offsetof(JSPrimitiveWrapper, value_),
                "Value of JSPrimitiveWrapper::kValueOffset defined in Torque and offset of field JSPrimitiveWrapper::value in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=159&c=1
class TorqueGeneratedJSMessageObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=162&c=3
  static constexpr int kMessageTypeOffset = sizeof(JSObject);
  static constexpr int kMessageTypeOffsetEnd = kMessageTypeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=164&c=3
  static constexpr int kArgumentOffset = kMessageTypeOffsetEnd + 1;
  static constexpr int kArgumentOffsetEnd = kArgumentOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=166&c=3
  static constexpr int kScriptOffset = kArgumentOffsetEnd + 1;
  static constexpr int kScriptOffsetEnd = kScriptOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=168&c=3
  static constexpr int kStackTraceOffset = kScriptOffsetEnd + 1;
  static constexpr int kStackTraceOffsetEnd = kStackTraceOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=169&c=3
  static constexpr int kSharedInfoOffset = kStackTraceOffsetEnd + 1;
  static constexpr int kSharedInfoOffsetEnd = kSharedInfoOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=173&c=3
  static constexpr int kBytecodeOffsetOffset = kSharedInfoOffsetEnd + 1;
  static constexpr int kBytecodeOffsetOffsetEnd = kBytecodeOffsetOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=174&c=3
  static constexpr int kStartPositionOffset = kBytecodeOffsetOffsetEnd + 1;
  static constexpr int kStartPositionOffsetEnd = kStartPositionOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=175&c=3
  static constexpr int kEndPositionOffset = kStartPositionOffsetEnd + 1;
  static constexpr int kEndPositionOffsetEnd = kEndPositionOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=176&c=3
  static constexpr int kErrorLevelOffset = kEndPositionOffsetEnd + 1;
  static constexpr int kErrorLevelOffsetEnd = kErrorLevelOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kErrorLevelOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kErrorLevelOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kErrorLevelOffsetEnd + 1;
  static constexpr int kHeaderSize = kErrorLevelOffsetEnd + 1;

  static_assert(kMessageTypeOffset == offsetof(JSMessageObject, message_type_),
                "Value of JSMessageObject::kMessageTypeOffset defined in Torque and offset of field JSMessageObject::message_type in C++ do not match");
  static_assert(kArgumentOffset == offsetof(JSMessageObject, argument_),
                "Value of JSMessageObject::kArgumentOffset defined in Torque and offset of field JSMessageObject::argument in C++ do not match");
  static_assert(kScriptOffset == offsetof(JSMessageObject, script_),
                "Value of JSMessageObject::kScriptOffset defined in Torque and offset of field JSMessageObject::script in C++ do not match");
  static_assert(kStackTraceOffset == offsetof(JSMessageObject, stack_trace_),
                "Value of JSMessageObject::kStackTraceOffset defined in Torque and offset of field JSMessageObject::stack_trace in C++ do not match");
  static_assert(kSharedInfoOffset == offsetof(JSMessageObject, shared_info_),
                "Value of JSMessageObject::kSharedInfoOffset defined in Torque and offset of field JSMessageObject::shared_info in C++ do not match");
  static_assert(kBytecodeOffsetOffset == offsetof(JSMessageObject, bytecode_offset_),
                "Value of JSMessageObject::kBytecodeOffsetOffset defined in Torque and offset of field JSMessageObject::bytecode_offset in C++ do not match");
  static_assert(kStartPositionOffset == offsetof(JSMessageObject, start_position_),
                "Value of JSMessageObject::kStartPositionOffset defined in Torque and offset of field JSMessageObject::start_position in C++ do not match");
  static_assert(kEndPositionOffset == offsetof(JSMessageObject, end_position_),
                "Value of JSMessageObject::kEndPositionOffset defined in Torque and offset of field JSMessageObject::end_position in C++ do not match");
  static_assert(kErrorLevelOffset == offsetof(JSMessageObject, error_level_),
                "Value of JSMessageObject::kErrorLevelOffset defined in Torque and offset of field JSMessageObject::error_level in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=179&c=1
class TorqueGeneratedJSDateAsserts {
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=184&c=3
  static constexpr int kValueOffset = sizeof(JSObject);
  static constexpr int kValueOffsetEnd = kValueOffset + kDoubleSize - 1;
  static constexpr int kStartOfStrongFieldsOffset = kValueOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=187&c=3
  static constexpr int kYearOffset = kValueOffsetEnd + 1;
  static constexpr int kYearOffsetEnd = kYearOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=188&c=3
  static constexpr int kMonthOffset = kYearOffsetEnd + 1;
  static constexpr int kMonthOffsetEnd = kMonthOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=189&c=3
  static constexpr int kDayOffset = kMonthOffsetEnd + 1;
  static constexpr int kDayOffsetEnd = kDayOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=190&c=3
  static constexpr int kWeekdayOffset = kDayOffsetEnd + 1;
  static constexpr int kWeekdayOffsetEnd = kWeekdayOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=191&c=3
  static constexpr int kHourOffset = kWeekdayOffsetEnd + 1;
  static constexpr int kHourOffsetEnd = kHourOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=192&c=3
  static constexpr int kMinOffset = kHourOffsetEnd + 1;
  static constexpr int kMinOffsetEnd = kMinOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=193&c=3
  static constexpr int kSecOffset = kMinOffsetEnd + 1;
  static constexpr int kSecOffsetEnd = kSecOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=197&c=3
  static constexpr int kCacheStampOffset = kSecOffsetEnd + 1;
  static constexpr int kCacheStampOffsetEnd = kCacheStampOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kCacheStampOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kCacheStampOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCacheStampOffsetEnd + 1;
  static constexpr int kHeaderSize = kCacheStampOffsetEnd + 1;

  static_assert(kValueOffset == offsetof(JSDate, value_),
                "Value of JSDate::kValueOffset defined in Torque and offset of field JSDate::value in C++ do not match");
  static_assert(kYearOffset == offsetof(JSDate, year_),
                "Value of JSDate::kYearOffset defined in Torque and offset of field JSDate::year in C++ do not match");
  static_assert(kMonthOffset == offsetof(JSDate, month_),
                "Value of JSDate::kMonthOffset defined in Torque and offset of field JSDate::month in C++ do not match");
  static_assert(kDayOffset == offsetof(JSDate, day_),
                "Value of JSDate::kDayOffset defined in Torque and offset of field JSDate::day in C++ do not match");
  static_assert(kWeekdayOffset == offsetof(JSDate, weekday_),
                "Value of JSDate::kWeekdayOffset defined in Torque and offset of field JSDate::weekday in C++ do not match");
  static_assert(kHourOffset == offsetof(JSDate, hour_),
                "Value of JSDate::kHourOffset defined in Torque and offset of field JSDate::hour in C++ do not match");
  static_assert(kMinOffset == offsetof(JSDate, min_),
                "Value of JSDate::kMinOffset defined in Torque and offset of field JSDate::min in C++ do not match");
  static_assert(kSecOffset == offsetof(JSDate, sec_),
                "Value of JSDate::kSecOffset defined in Torque and offset of field JSDate::sec in C++ do not match");
  static_assert(kCacheStampOffset == offsetof(JSDate, cache_stamp_),
                "Value of JSDate::kCacheStampOffset defined in Torque and offset of field JSDate::cache_stamp in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=200&c=1
class TorqueGeneratedJSAsyncFromSyncIteratorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=202&c=3
  static constexpr int kSyncIteratorOffset = sizeof(JSObject);
  static constexpr int kSyncIteratorOffsetEnd = kSyncIteratorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=205&c=3
  static constexpr int kNextOffset = kSyncIteratorOffsetEnd + 1;
  static constexpr int kNextOffsetEnd = kNextOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kNextOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kNextOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kNextOffsetEnd + 1;
  static constexpr int kHeaderSize = kNextOffsetEnd + 1;

  static_assert(kSyncIteratorOffset == offsetof(JSAsyncFromSyncIterator, sync_iterator_),
                "Value of JSAsyncFromSyncIterator::kSyncIteratorOffset defined in Torque and offset of field JSAsyncFromSyncIterator::sync_iterator in C++ do not match");
  static_assert(kNextOffset == offsetof(JSAsyncFromSyncIterator, next_),
                "Value of JSAsyncFromSyncIterator::kNextOffset defined in Torque and offset of field JSAsyncFromSyncIterator::next in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=208&c=1
class TorqueGeneratedJSStringIteratorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=211&c=3
  static constexpr int kStringOffset = sizeof(JSObject);
  static constexpr int kStringOffsetEnd = kStringOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=213&c=3
  static constexpr int kIndexOffset = kStringOffsetEnd + 1;
  static constexpr int kIndexOffsetEnd = kIndexOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIndexOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIndexOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIndexOffsetEnd + 1;
  static constexpr int kHeaderSize = kIndexOffsetEnd + 1;

  static_assert(kStringOffset == offsetof(JSStringIterator, string_),
                "Value of JSStringIterator::kStringOffset defined in Torque and offset of field JSStringIterator::string in C++ do not match");
  static_assert(kIndexOffset == offsetof(JSStringIterator, index_),
                "Value of JSStringIterator::kIndexOffset defined in Torque and offset of field JSStringIterator::index in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-objects.tq?l=218&c=1
class TorqueGeneratedJSValidIteratorWrapperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-objects.tq?l=221&c=3
  static constexpr int kUnderlyingOffset = sizeof(JSObject);
  static constexpr int kUnderlyingOffsetEnd = kUnderlyingOffset + 8 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kUnderlyingOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kUnderlyingOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kUnderlyingOffsetEnd + 1;
  static constexpr int kHeaderSize = kUnderlyingOffsetEnd + 1;

};

} // namespace internal
} // namespace v8
