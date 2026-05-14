#include "src/objects/js-array-buffer.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=72&c=1
class TorqueGeneratedJSArrayBufferViewAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSAPIObjectWithEmbedderSlots);
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=75&c=3
  static constexpr int kBufferOffset = sizeof(JSAPIObjectWithEmbedderSlots);
  static constexpr int kBufferOffsetEnd = kBufferOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kBufferOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=76&c=3
  static constexpr int kBitFieldOffset = kBufferOffsetEnd + 1;
  static constexpr int kBitFieldOffsetEnd = kBitFieldOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=79&c=3
  static constexpr int kRawByteOffsetOffset = kBitFieldOffsetEnd + 1;
  static constexpr int kRawByteOffsetOffsetEnd = kRawByteOffsetOffset + kIntptrSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=81&c=3
  static constexpr int kRawByteLengthOffset = kRawByteOffsetOffsetEnd + 1;
  static constexpr int kRawByteLengthOffsetEnd = kRawByteLengthOffset + kIntptrSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kRawByteLengthOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kRawByteLengthOffsetEnd + 1;
  static constexpr int kHeaderSize = kRawByteLengthOffsetEnd + 1;

  static_assert(kBufferOffset == offsetof(JSArrayBufferView, buffer_),
                "Value of JSArrayBufferView::kBufferOffset defined in Torque and offset of field JSArrayBufferView::buffer in C++ do not match");
  static_assert(kBitFieldOffset == offsetof(JSArrayBufferView, bit_field_),
                "Value of JSArrayBufferView::kBitFieldOffset defined in Torque and offset of field JSArrayBufferView::bit_field in C++ do not match");
  static_assert(kRawByteOffsetOffset == offsetof(JSArrayBufferView, raw_byte_offset_),
                "Value of JSArrayBufferView::kRawByteOffsetOffset defined in Torque and offset of field JSArrayBufferView::raw_byte_offset in C++ do not match");
  static_assert(kRawByteLengthOffset == offsetof(JSArrayBufferView, raw_byte_length_),
                "Value of JSArrayBufferView::kRawByteLengthOffset defined in Torque and offset of field JSArrayBufferView::raw_byte_length in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=119&c=1
class TorqueGeneratedJSTypedArrayAsserts {
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=122&c=3
  static constexpr int kRawLengthOffset = sizeof(JSArrayBufferView);
  static constexpr int kRawLengthOffsetEnd = kRawLengthOffset + kIntptrSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=124&c=3
  static constexpr int kExternalPointerOffset = kRawLengthOffsetEnd + 1;
  static constexpr int kExternalPointerOffsetEnd = kExternalPointerOffset + kSystemPointerSize - 1;
  static constexpr int kStartOfStrongFieldsOffset = kExternalPointerOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=125&c=3
  static constexpr int kBasePointerOffset = kExternalPointerOffsetEnd + 1;
  static constexpr int kBasePointerOffsetEnd = kBasePointerOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kBasePointerOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kBasePointerOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBasePointerOffsetEnd + 1;
  static constexpr int kHeaderSize = kBasePointerOffsetEnd + 1;

  static_assert(kRawLengthOffset == offsetof(JSTypedArray, raw_length_),
                "Value of JSTypedArray::kRawLengthOffset defined in Torque and offset of field JSTypedArray::raw_length in C++ do not match");
  static_assert(kExternalPointerOffset == offsetof(JSTypedArray, external_pointer_),
                "Value of JSTypedArray::kExternalPointerOffset defined in Torque and offset of field JSTypedArray::external_pointer in C++ do not match");
  static_assert(kBasePointerOffset == offsetof(JSTypedArray, base_pointer_),
                "Value of JSTypedArray::kBasePointerOffset defined in Torque and offset of field JSTypedArray::base_pointer in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=18&c=1
class TorqueGeneratedJSArrayBufferAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSAPIObjectWithEmbedderSlots);
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=20&c=3
  static constexpr int kViewsOrDetachKeyOffset = sizeof(JSAPIObjectWithEmbedderSlots);
  static constexpr int kViewsOrDetachKeyOffsetEnd = kViewsOrDetachKeyOffset + kTaggedSize - 1;
  static constexpr int kEndOfWeakFieldsOffset = kViewsOrDetachKeyOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=22&c=3
  static constexpr int kRawByteLengthOffset = kViewsOrDetachKeyOffsetEnd + 1;
  static constexpr int kRawByteLengthOffsetEnd = kRawByteLengthOffset + kIntptrSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=24&c=3
  static constexpr int kRawMaxByteLengthOffset = kRawByteLengthOffsetEnd + 1;
  static constexpr int kRawMaxByteLengthOffsetEnd = kRawMaxByteLengthOffset + kIntptrSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=26&c=3
  static constexpr int kBackingStoreOffset = kRawMaxByteLengthOffsetEnd + 1;
  static constexpr int kBackingStoreOffsetEnd = kBackingStoreOffset + kSystemPointerSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=27&c=3
  static constexpr int kExtensionOffset = kBackingStoreOffsetEnd + 1;
  static constexpr int kExtensionOffsetEnd = kExtensionOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=28&c=3
  static constexpr int kBitFieldOffset = kExtensionOffsetEnd + 1;
  static constexpr int kBitFieldOffsetEnd = kBitFieldOffset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kBitFieldOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kBitFieldOffsetEnd + 1;
  static constexpr int kHeaderSize = kBitFieldOffsetEnd + 1;

  static_assert(kViewsOrDetachKeyOffset == offsetof(JSArrayBuffer, views_or_detach_key_),
                "Value of JSArrayBuffer::kViewsOrDetachKeyOffset defined in Torque and offset of field JSArrayBuffer::views_or_detach_key in C++ do not match");
  static_assert(kRawByteLengthOffset == offsetof(JSArrayBuffer, raw_byte_length_),
                "Value of JSArrayBuffer::kRawByteLengthOffset defined in Torque and offset of field JSArrayBuffer::raw_byte_length in C++ do not match");
  static_assert(kRawMaxByteLengthOffset == offsetof(JSArrayBuffer, raw_max_byte_length_),
                "Value of JSArrayBuffer::kRawMaxByteLengthOffset defined in Torque and offset of field JSArrayBuffer::raw_max_byte_length in C++ do not match");
  static_assert(kBackingStoreOffset == offsetof(JSArrayBuffer, backing_store_),
                "Value of JSArrayBuffer::kBackingStoreOffset defined in Torque and offset of field JSArrayBuffer::backing_store in C++ do not match");
  static_assert(kExtensionOffset == offsetof(JSArrayBuffer, extension_),
                "Value of JSArrayBuffer::kExtensionOffset defined in Torque and offset of field JSArrayBuffer::extension in C++ do not match");
  static_assert(kBitFieldOffset == offsetof(JSArrayBuffer, bit_field_),
                "Value of JSArrayBuffer::kBitFieldOffset defined in Torque and offset of field JSArrayBuffer::bit_field in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=131&c=1
class TorqueGeneratedJSDetachedTypedArrayAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSTypedArray);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSTypedArray);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSTypedArray);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSTypedArray);
  static constexpr int kHeaderSize = sizeof(JSTypedArray);

};

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=142&c=1
class TorqueGeneratedJSDataViewOrRabGsabDataViewAsserts {
  // https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=146&c=3
  static constexpr int kDataPointerOffset = sizeof(JSArrayBufferView);
  static constexpr int kDataPointerOffsetEnd = kDataPointerOffset + kSystemPointerSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataPointerOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataPointerOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kDataPointerOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataPointerOffsetEnd + 1;
  static constexpr int kHeaderSize = kDataPointerOffsetEnd + 1;

  static_assert(kDataPointerOffset == offsetof(JSDataViewOrRabGsabDataView, data_pointer_),
                "Value of JSDataViewOrRabGsabDataView::kDataPointerOffset defined in Torque and offset of field JSDataViewOrRabGsabDataView::data_pointer in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=149&c=1
class TorqueGeneratedJSDataViewAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kHeaderSize = sizeof(JSDataViewOrRabGsabDataView);

};

// Definition https://crsrc.org/c/v8/src/objects/js-array-buffer.tq?l=152&c=1
class TorqueGeneratedJSRabGsabDataViewAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSDataViewOrRabGsabDataView);
  static constexpr int kHeaderSize = sizeof(JSDataViewOrRabGsabDataView);

};

} // namespace internal
} // namespace v8
