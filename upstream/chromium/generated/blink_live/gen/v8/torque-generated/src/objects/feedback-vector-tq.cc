#include "src/objects/feedback-vector.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=27&c=1
class TorqueGeneratedClosureFeedbackCellArrayAsserts {
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=29&c=9
  static constexpr int kLengthOffset = sizeof(HeapObjectLayout);
  static constexpr int kLengthOffsetEnd = kLengthOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=31&c=31
  static constexpr int kOptionalPaddingOffset = kLengthOffsetEnd + 1;
  static constexpr int kOptionalPaddingOffsetEnd = kOptionalPaddingOffset + 0 - 1;
  static constexpr int kStartOfStrongFieldsOffset = kOptionalPaddingOffsetEnd + 1;
  static constexpr int kHeaderSize = kOptionalPaddingOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=32&c=3
  static constexpr int kObjectsOffset = kOptionalPaddingOffsetEnd + 1;
  static constexpr int kObjectsOffsetEnd = kObjectsOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kObjectsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kObjectsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kObjectsOffsetEnd + 1;

  static_assert(kLengthOffset == offsetof(ClosureFeedbackCellArray, length_),
                "Value of ClosureFeedbackCellArray::kLengthOffset defined in Torque and offset of field ClosureFeedbackCellArray::length in C++ do not match");
  static_assert(kOptionalPaddingOffset == offsetof(ClosureFeedbackCellArray, optional_padding_),
                "Value of ClosureFeedbackCellArray::kOptionalPaddingOffset defined in Torque and offset of field ClosureFeedbackCellArray::optional_padding in C++ do not match");
  static_assert(kObjectsOffset == OFFSET_OF_DATA_START(ClosureFeedbackCellArray),
                "Value of ClosureFeedbackCellArray::kObjectsOffset defined in Torque and offset of field ClosureFeedbackCellArray::objects in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=35&c=1
class TorqueGeneratedFeedbackVectorAsserts {
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=37&c=9
  static constexpr int kLengthOffset = sizeof(HeapObjectLayout);
  static constexpr int kLengthOffsetEnd = kLengthOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=38&c=3
  static constexpr int kInvocationCountOffset = kLengthOffsetEnd + 1;
  static constexpr int kInvocationCountOffsetEnd = kInvocationCountOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=40&c=3
  static constexpr int kInvocationCountBeforeStableOffset = kInvocationCountOffsetEnd + 1;
  static constexpr int kInvocationCountBeforeStableOffsetEnd = kInvocationCountBeforeStableOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=41&c=3
  static constexpr int kOsrStateOffset = kInvocationCountBeforeStableOffsetEnd + 1;
  static constexpr int kOsrStateOffsetEnd = kOsrStateOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=42&c=3
  static constexpr int kFlagsOffset = kOsrStateOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kUInt16Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=43&c=3
  static constexpr int kSharedFunctionInfoOffset = kFlagsOffsetEnd + 1;
  static constexpr int kSharedFunctionInfoOffsetEnd = kSharedFunctionInfoOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=44&c=3
  static constexpr int kClosureFeedbackCellArrayOffset = kSharedFunctionInfoOffsetEnd + 1;
  static constexpr int kClosureFeedbackCellArrayOffsetEnd = kClosureFeedbackCellArrayOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=45&c=3
  static constexpr int kParentFeedbackCellOffset = kClosureFeedbackCellArrayOffsetEnd + 1;
  static constexpr int kParentFeedbackCellOffsetEnd = kParentFeedbackCellOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kParentFeedbackCellOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kParentFeedbackCellOffsetEnd + 1;
  static constexpr int kHeaderSize = kParentFeedbackCellOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=46&c=36
  static constexpr int kRawFeedbackSlotsOffset = kParentFeedbackCellOffsetEnd + 1;
  static constexpr int kRawFeedbackSlotsOffsetEnd = kRawFeedbackSlotsOffset + 0 - 1;
  static constexpr int kEndOfWeakFieldsOffset = kRawFeedbackSlotsOffsetEnd + 1;

  static_assert(kLengthOffset == offsetof(FeedbackVector, length_),
                "Value of FeedbackVector::kLengthOffset defined in Torque and offset of field FeedbackVector::length in C++ do not match");
  static_assert(kInvocationCountOffset == offsetof(FeedbackVector, invocation_count_),
                "Value of FeedbackVector::kInvocationCountOffset defined in Torque and offset of field FeedbackVector::invocation_count in C++ do not match");
  static_assert(kInvocationCountBeforeStableOffset == offsetof(FeedbackVector, invocation_count_before_stable_),
                "Value of FeedbackVector::kInvocationCountBeforeStableOffset defined in Torque and offset of field FeedbackVector::invocation_count_before_stable in C++ do not match");
  static_assert(kOsrStateOffset == offsetof(FeedbackVector, osr_state_),
                "Value of FeedbackVector::kOsrStateOffset defined in Torque and offset of field FeedbackVector::osr_state in C++ do not match");
  static_assert(kFlagsOffset == offsetof(FeedbackVector, flags_),
                "Value of FeedbackVector::kFlagsOffset defined in Torque and offset of field FeedbackVector::flags in C++ do not match");
  static_assert(kSharedFunctionInfoOffset == offsetof(FeedbackVector, shared_function_info_),
                "Value of FeedbackVector::kSharedFunctionInfoOffset defined in Torque and offset of field FeedbackVector::shared_function_info in C++ do not match");
  static_assert(kClosureFeedbackCellArrayOffset == offsetof(FeedbackVector, closure_feedback_cell_array_),
                "Value of FeedbackVector::kClosureFeedbackCellArrayOffset defined in Torque and offset of field FeedbackVector::closure_feedback_cell_array in C++ do not match");
  static_assert(kParentFeedbackCellOffset == offsetof(FeedbackVector, parent_feedback_cell_),
                "Value of FeedbackVector::kParentFeedbackCellOffset defined in Torque and offset of field FeedbackVector::parent_feedback_cell in C++ do not match");
  static_assert(kRawFeedbackSlotsOffset == OFFSET_OF_DATA_START(FeedbackVector),
                "Value of FeedbackVector::kRawFeedbackSlotsOffset defined in Torque and offset of field FeedbackVector::raw_feedback_slots in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=49&c=1
class TorqueGeneratedFeedbackMetadataAsserts {
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=51&c=3
  static constexpr int kSlotCountOffset = sizeof(HeapObjectLayout);
  static constexpr int kSlotCountOffsetEnd = kSlotCountOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/feedback-vector.tq?l=52&c=3
  static constexpr int kCreateClosureSlotCountOffset = kSlotCountOffsetEnd + 1;
  static constexpr int kCreateClosureSlotCountOffsetEnd = kCreateClosureSlotCountOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kCreateClosureSlotCountOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kCreateClosureSlotCountOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kCreateClosureSlotCountOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kCreateClosureSlotCountOffsetEnd + 1;
  static constexpr int kHeaderSize = kCreateClosureSlotCountOffsetEnd + 1;
  static constexpr int kSize = kCreateClosureSlotCountOffsetEnd + 1;

  static_assert(kSlotCountOffset == offsetof(FeedbackMetadata, slot_count_),
                "Value of FeedbackMetadata::kSlotCountOffset defined in Torque and offset of field FeedbackMetadata::slot_count in C++ do not match");
  static_assert(kCreateClosureSlotCountOffset == offsetof(FeedbackMetadata, create_closure_slot_count_),
                "Value of FeedbackMetadata::kCreateClosureSlotCountOffset defined in Torque and offset of field FeedbackMetadata::create_closure_slot_count in C++ do not match");
  static_assert(kSize == sizeof(FeedbackMetadata));
};

} // namespace internal
} // namespace v8
