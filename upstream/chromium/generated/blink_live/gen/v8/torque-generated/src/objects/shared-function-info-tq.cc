#include "src/objects/shared-function-info.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=7&c=1
class TorqueGeneratedPreparseDataAsserts {
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=10&c=3
  static constexpr int kDataLengthOffset = sizeof(HeapObjectLayout);
  static constexpr int kDataLengthOffsetEnd = kDataLengthOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=11&c=3
  static constexpr int kChildrenLengthOffset = kDataLengthOffsetEnd + 1;
  static constexpr int kChildrenLengthOffsetEnd = kChildrenLengthOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kChildrenLengthOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kChildrenLengthOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kChildrenLengthOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kChildrenLengthOffsetEnd + 1;
  static constexpr int kHeaderSize = kChildrenLengthOffsetEnd + 1;
  static constexpr int kSize = kChildrenLengthOffsetEnd + 1;

  static_assert(kDataLengthOffset == offsetof(PreparseData, data_length_),
                "Value of PreparseData::kDataLengthOffset defined in Torque and offset of field PreparseData::data_length in C++ do not match");
  static_assert(kChildrenLengthOffset == offsetof(PreparseData, children_length_),
                "Value of PreparseData::kChildrenLengthOffset defined in Torque and offset of field PreparseData::children_length in C++ do not match");
  static_assert(kSize == sizeof(PreparseData));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=14&c=1
class TorqueGeneratedInterpreterDataAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(ExposedTrustedObject);
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=16&c=3
  static constexpr int kBytecodeArrayOffset = sizeof(ExposedTrustedObject);
  static constexpr int kBytecodeArrayOffsetEnd = kBytecodeArrayOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=17&c=3
  static constexpr int kInterpreterTrampolineOffset = kBytecodeArrayOffsetEnd + 1;
  static constexpr int kInterpreterTrampolineOffsetEnd = kInterpreterTrampolineOffset + kTaggedSize - 1;
  static constexpr int kEndOfWeakFieldsOffset = kInterpreterTrampolineOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kInterpreterTrampolineOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kInterpreterTrampolineOffsetEnd + 1;
  static constexpr int kHeaderSize = kInterpreterTrampolineOffsetEnd + 1;
  static constexpr int kSize = kInterpreterTrampolineOffsetEnd + 1;

  static_assert(kBytecodeArrayOffset == offsetof(InterpreterData, bytecode_array_),
                "Value of InterpreterData::kBytecodeArrayOffset defined in Torque and offset of field InterpreterData::bytecode_array in C++ do not match");
  static_assert(kInterpreterTrampolineOffset == offsetof(InterpreterData, interpreter_trampoline_),
                "Value of InterpreterData::kInterpreterTrampolineOffset defined in Torque and offset of field InterpreterData::interpreter_trampoline in C++ do not match");
  static_assert(kSize == sizeof(InterpreterData));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=63&c=1
class TorqueGeneratedSharedFunctionInfoAsserts {
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=76&c=3
  static constexpr int kTrustedFunctionDataOffset = sizeof(HeapObjectLayout);
  static constexpr int kTrustedFunctionDataOffsetEnd = kTrustedFunctionDataOffset + kTrustedPointerSize - 1;
  static constexpr int kStartOfStrongFieldsOffset = kTrustedFunctionDataOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=80&c=3
  static constexpr int kUntrustedFunctionDataOffset = kTrustedFunctionDataOffsetEnd + 1;
  static constexpr int kUntrustedFunctionDataOffsetEnd = kUntrustedFunctionDataOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=81&c=3
  static constexpr int kNameOrScopeInfoOffset = kUntrustedFunctionDataOffsetEnd + 1;
  static constexpr int kNameOrScopeInfoOffsetEnd = kNameOrScopeInfoOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=82&c=3
  static constexpr int kOuterScopeInfoOrFeedbackMetadataOffset = kNameOrScopeInfoOffsetEnd + 1;
  static constexpr int kOuterScopeInfoOrFeedbackMetadataOffsetEnd = kOuterScopeInfoOrFeedbackMetadataOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=83&c=3
  static constexpr int kScriptOffset = kOuterScopeInfoOrFeedbackMetadataOffsetEnd + 1;
  static constexpr int kScriptOffsetEnd = kScriptOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kScriptOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=87&c=3
  static constexpr int kLengthOffset = kScriptOffsetEnd + 1;
  static constexpr int kLengthOffsetEnd = kLengthOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=103&c=3
  static constexpr int kFormalParameterCountOffset = kLengthOffsetEnd + 1;
  static constexpr int kFormalParameterCountOffsetEnd = kFormalParameterCountOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=104&c=3
  static constexpr int kFunctionTokenOffsetOffset = kFormalParameterCountOffsetEnd + 1;
  static constexpr int kFunctionTokenOffsetOffsetEnd = kFunctionTokenOffsetOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=107&c=3
  static constexpr int kExpectedNofPropertiesOffset = kFunctionTokenOffsetOffsetEnd + 1;
  static constexpr int kExpectedNofPropertiesOffsetEnd = kExpectedNofPropertiesOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=108&c=3
  static constexpr int kFlags2Offset = kExpectedNofPropertiesOffsetEnd + 1;
  static constexpr int kFlags2OffsetEnd = kFlags2Offset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=109&c=3
  static constexpr int kFlagsOffset = kFlags2OffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=113&c=3
  static constexpr int kFunctionLiteralIdOffset = kFlagsOffsetEnd + 1;
  static constexpr int kFunctionLiteralIdOffsetEnd = kFunctionLiteralIdOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=117&c=3
  static constexpr int kUniqueIdOffset = kFunctionLiteralIdOffsetEnd + 1;
  static constexpr int kUniqueIdOffsetEnd = kUniqueIdOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=120&c=3
  static constexpr int kAgeOffset = kUniqueIdOffsetEnd + 1;
  static constexpr int kAgeOffsetEnd = kAgeOffset + kUInt16Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=124&c=3
  static constexpr int kFeedbackSlotOffset = kAgeOffsetEnd + 1;
  static constexpr int kFeedbackSlotOffsetEnd = kFeedbackSlotOffset + kUInt16Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kFeedbackSlotOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFeedbackSlotOffsetEnd + 1;
  static constexpr int kHeaderSize = kFeedbackSlotOffsetEnd + 1;
  static constexpr int kSize = kFeedbackSlotOffsetEnd + 1;

  static_assert(kTrustedFunctionDataOffset == offsetof(SharedFunctionInfo, trusted_function_data_),
                "Value of SharedFunctionInfo::kTrustedFunctionDataOffset defined in Torque and offset of field SharedFunctionInfo::trusted_function_data in C++ do not match");
  static_assert(kUntrustedFunctionDataOffset == offsetof(SharedFunctionInfo, untrusted_function_data_),
                "Value of SharedFunctionInfo::kUntrustedFunctionDataOffset defined in Torque and offset of field SharedFunctionInfo::untrusted_function_data in C++ do not match");
  static_assert(kNameOrScopeInfoOffset == offsetof(SharedFunctionInfo, name_or_scope_info_),
                "Value of SharedFunctionInfo::kNameOrScopeInfoOffset defined in Torque and offset of field SharedFunctionInfo::name_or_scope_info in C++ do not match");
  static_assert(kOuterScopeInfoOrFeedbackMetadataOffset == offsetof(SharedFunctionInfo, outer_scope_info_or_feedback_metadata_),
                "Value of SharedFunctionInfo::kOuterScopeInfoOrFeedbackMetadataOffset defined in Torque and offset of field SharedFunctionInfo::outer_scope_info_or_feedback_metadata in C++ do not match");
  static_assert(kScriptOffset == offsetof(SharedFunctionInfo, script_),
                "Value of SharedFunctionInfo::kScriptOffset defined in Torque and offset of field SharedFunctionInfo::script in C++ do not match");
  static_assert(kLengthOffset == offsetof(SharedFunctionInfo, length_),
                "Value of SharedFunctionInfo::kLengthOffset defined in Torque and offset of field SharedFunctionInfo::length in C++ do not match");
  static_assert(kFormalParameterCountOffset == offsetof(SharedFunctionInfo, formal_parameter_count_),
                "Value of SharedFunctionInfo::kFormalParameterCountOffset defined in Torque and offset of field SharedFunctionInfo::formal_parameter_count in C++ do not match");
  static_assert(kFunctionTokenOffsetOffset == offsetof(SharedFunctionInfo, function_token_offset_),
                "Value of SharedFunctionInfo::kFunctionTokenOffsetOffset defined in Torque and offset of field SharedFunctionInfo::function_token_offset in C++ do not match");
  static_assert(kExpectedNofPropertiesOffset == offsetof(SharedFunctionInfo, expected_nof_properties_),
                "Value of SharedFunctionInfo::kExpectedNofPropertiesOffset defined in Torque and offset of field SharedFunctionInfo::expected_nof_properties in C++ do not match");
  static_assert(kFlags2Offset == offsetof(SharedFunctionInfo, flags2_),
                "Value of SharedFunctionInfo::kFlags2Offset defined in Torque and offset of field SharedFunctionInfo::flags2 in C++ do not match");
  static_assert(kFlagsOffset == offsetof(SharedFunctionInfo, flags_),
                "Value of SharedFunctionInfo::kFlagsOffset defined in Torque and offset of field SharedFunctionInfo::flags in C++ do not match");
  static_assert(kFunctionLiteralIdOffset == offsetof(SharedFunctionInfo, function_literal_id_),
                "Value of SharedFunctionInfo::kFunctionLiteralIdOffset defined in Torque and offset of field SharedFunctionInfo::function_literal_id in C++ do not match");
  static_assert(kUniqueIdOffset == offsetof(SharedFunctionInfo, unique_id_),
                "Value of SharedFunctionInfo::kUniqueIdOffset defined in Torque and offset of field SharedFunctionInfo::unique_id in C++ do not match");
  static_assert(kAgeOffset == offsetof(SharedFunctionInfo, age_),
                "Value of SharedFunctionInfo::kAgeOffset defined in Torque and offset of field SharedFunctionInfo::age in C++ do not match");
  static_assert(kFeedbackSlotOffset == offsetof(SharedFunctionInfo, feedback_slot_),
                "Value of SharedFunctionInfo::kFeedbackSlotOffset defined in Torque and offset of field SharedFunctionInfo::feedback_slot in C++ do not match");
  static_assert(kSize == sizeof(SharedFunctionInfo));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=131&c=1
class TorqueGeneratedSharedFunctionInfoWrapperAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(TrustedObject);
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=133&c=3
  static constexpr int kSharedInfoOffset = sizeof(TrustedObject);
  static constexpr int kSharedInfoOffsetEnd = kSharedInfoOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kSharedInfoOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kSharedInfoOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kSharedInfoOffsetEnd + 1;
  static constexpr int kHeaderSize = kSharedInfoOffsetEnd + 1;
  static constexpr int kSize = kSharedInfoOffsetEnd + 1;

  static_assert(kSharedInfoOffset == offsetof(SharedFunctionInfoWrapper, shared_info_),
                "Value of SharedFunctionInfoWrapper::kSharedInfoOffset defined in Torque and offset of field SharedFunctionInfoWrapper::shared_info in C++ do not match");
  static_assert(kSize == sizeof(SharedFunctionInfoWrapper));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=162&c=1
class TorqueGeneratedUncompiledDataAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(ExposedTrustedObject);
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=165&c=3
  static constexpr int kInferredNameOffset = sizeof(ExposedTrustedObject);
  static constexpr int kInferredNameOffsetEnd = kInferredNameOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kInferredNameOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=166&c=3
  static constexpr int kStartPositionOffset = kInferredNameOffsetEnd + 1;
  static constexpr int kStartPositionOffsetEnd = kStartPositionOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=167&c=3
  static constexpr int kEndPositionOffset = kStartPositionOffsetEnd + 1;
  static constexpr int kEndPositionOffsetEnd = kEndPositionOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kEndPositionOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kEndPositionOffsetEnd + 1;
  static constexpr int kHeaderSize = kEndPositionOffsetEnd + 1;

  static_assert(kInferredNameOffset == offsetof(UncompiledData, inferred_name_),
                "Value of UncompiledData::kInferredNameOffset defined in Torque and offset of field UncompiledData::inferred_name in C++ do not match");
  static_assert(kStartPositionOffset == offsetof(UncompiledData, start_position_),
                "Value of UncompiledData::kStartPositionOffset defined in Torque and offset of field UncompiledData::start_position in C++ do not match");
  static_assert(kEndPositionOffset == offsetof(UncompiledData, end_position_),
                "Value of UncompiledData::kEndPositionOffset defined in Torque and offset of field UncompiledData::end_position in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=170&c=1
class TorqueGeneratedUncompiledDataWithoutPreparseDataAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(UncompiledData);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(UncompiledData);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(UncompiledData);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(UncompiledData);
  static constexpr int kHeaderSize = sizeof(UncompiledData);
  static constexpr int kSize = sizeof(UncompiledData);

  static_assert(kSize == sizeof(UncompiledDataWithoutPreparseData));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=173&c=1
class TorqueGeneratedUncompiledDataWithPreparseDataAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(UncompiledData);
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=175&c=3
  static constexpr int kPreparseDataOffset = sizeof(UncompiledData);
  static constexpr int kPreparseDataOffsetEnd = kPreparseDataOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPreparseDataOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPreparseDataOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPreparseDataOffsetEnd + 1;
  static constexpr int kHeaderSize = kPreparseDataOffsetEnd + 1;
  static constexpr int kSize = kPreparseDataOffsetEnd + 1;

  static_assert(kPreparseDataOffset == offsetof(UncompiledDataWithPreparseData, preparse_data_),
                "Value of UncompiledDataWithPreparseData::kPreparseDataOffset defined in Torque and offset of field UncompiledDataWithPreparseData::preparse_data in C++ do not match");
  static_assert(kSize == sizeof(UncompiledDataWithPreparseData));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=178&c=1
class TorqueGeneratedUncompiledDataWithoutPreparseDataWithJobAsserts {
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=181&c=3
  static constexpr int kJobOffset = sizeof(UncompiledDataWithoutPreparseData);
  static constexpr int kJobOffsetEnd = kJobOffset + kSystemPointerSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kHeaderSize = kJobOffsetEnd + 1;
  static constexpr int kSize = kJobOffsetEnd + 1;

  static_assert(kJobOffset == offsetof(UncompiledDataWithoutPreparseDataWithJob, job_),
                "Value of UncompiledDataWithoutPreparseDataWithJob::kJobOffset defined in Torque and offset of field UncompiledDataWithoutPreparseDataWithJob::job in C++ do not match");
  static_assert(kSize == sizeof(UncompiledDataWithoutPreparseDataWithJob));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=184&c=1
class TorqueGeneratedUncompiledDataWithPreparseDataAndJobAsserts {
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=187&c=3
  static constexpr int kJobOffset = sizeof(UncompiledDataWithPreparseData);
  static constexpr int kJobOffsetEnd = kJobOffset + kSystemPointerSize - 1;
  static constexpr int kStartOfWeakFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kJobOffsetEnd + 1;
  static constexpr int kHeaderSize = kJobOffsetEnd + 1;
  static constexpr int kSize = kJobOffsetEnd + 1;

  static_assert(kJobOffset == offsetof(UncompiledDataWithPreparseDataAndJob, job_),
                "Value of UncompiledDataWithPreparseDataAndJob::kJobOffset defined in Torque and offset of field UncompiledDataWithPreparseDataAndJob::job in C++ do not match");
  static_assert(kSize == sizeof(UncompiledDataWithPreparseDataAndJob));
};

// Definition https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=200&c=1
class TorqueGeneratedOnHeapBasicBlockProfilerDataAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=202&c=3
  static constexpr int kBlockIdsOffset = sizeof(HeapObjectLayout);
  static constexpr int kBlockIdsOffsetEnd = kBlockIdsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=203&c=3
  static constexpr int kCountsOffset = kBlockIdsOffsetEnd + 1;
  static constexpr int kCountsOffsetEnd = kCountsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=204&c=3
  static constexpr int kBranchesOffset = kCountsOffsetEnd + 1;
  static constexpr int kBranchesOffsetEnd = kBranchesOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=205&c=3
  static constexpr int kNameOffset = kBranchesOffsetEnd + 1;
  static constexpr int kNameOffsetEnd = kNameOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=206&c=3
  static constexpr int kScheduleOffset = kNameOffsetEnd + 1;
  static constexpr int kScheduleOffsetEnd = kScheduleOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=207&c=3
  static constexpr int kCodeOffset = kScheduleOffsetEnd + 1;
  static constexpr int kCodeOffsetEnd = kCodeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=208&c=3
  static constexpr int kHashOffset = kCodeOffsetEnd + 1;
  static constexpr int kHashOffsetEnd = kHashOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kHashOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kHashOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kHashOffsetEnd + 1;
  static constexpr int kHeaderSize = kHashOffsetEnd + 1;
  static constexpr int kSize = kHashOffsetEnd + 1;

  static_assert(kBlockIdsOffset == offsetof(OnHeapBasicBlockProfilerData, block_ids_),
                "Value of OnHeapBasicBlockProfilerData::kBlockIdsOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::block_ids in C++ do not match");
  static_assert(kCountsOffset == offsetof(OnHeapBasicBlockProfilerData, counts_),
                "Value of OnHeapBasicBlockProfilerData::kCountsOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::counts in C++ do not match");
  static_assert(kBranchesOffset == offsetof(OnHeapBasicBlockProfilerData, branches_),
                "Value of OnHeapBasicBlockProfilerData::kBranchesOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::branches in C++ do not match");
  static_assert(kNameOffset == offsetof(OnHeapBasicBlockProfilerData, name_),
                "Value of OnHeapBasicBlockProfilerData::kNameOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::name in C++ do not match");
  static_assert(kScheduleOffset == offsetof(OnHeapBasicBlockProfilerData, schedule_),
                "Value of OnHeapBasicBlockProfilerData::kScheduleOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::schedule in C++ do not match");
  static_assert(kCodeOffset == offsetof(OnHeapBasicBlockProfilerData, code_),
                "Value of OnHeapBasicBlockProfilerData::kCodeOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::code in C++ do not match");
  static_assert(kHashOffset == offsetof(OnHeapBasicBlockProfilerData, hash_),
                "Value of OnHeapBasicBlockProfilerData::kHashOffset defined in Torque and offset of field OnHeapBasicBlockProfilerData::hash in C++ do not match");
  static_assert(kSize == sizeof(OnHeapBasicBlockProfilerData));
};

} // namespace internal
} // namespace v8
