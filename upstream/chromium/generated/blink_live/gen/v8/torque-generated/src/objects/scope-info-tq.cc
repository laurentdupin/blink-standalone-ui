#include "src/objects/scope-info.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/scope-info.tq?l=122&c=1
class TorqueGeneratedScopeInfoAsserts {
  // https://crsrc.org/c/v8/src/objects/scope-info.tq?l=124&c=42
  static constexpr int kFlagsOffset = sizeof(HeapObjectLayout);
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/scope-info.tq?l=129&c=3
  static constexpr int kParameterCountOffset = kFlagsOffsetEnd + 1;
  static constexpr int kParameterCountOffsetEnd = kParameterCountOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/scope-info.tq?l=133&c=9
  static constexpr int kContextLocalCountOffset = kParameterCountOffsetEnd + 1;
  static constexpr int kContextLocalCountOffsetEnd = kContextLocalCountOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/scope-info.tq?l=136&c=3
  static constexpr int kPositionInfoOffset = kContextLocalCountOffsetEnd + 1;
  static constexpr int kPositionInfoOffsetEnd = kPositionInfoOffset + 8 - 1;
  static constexpr int kHeaderSize = kPositionInfoOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/scope-info.tq?l=141&c=9
  static constexpr int kModuleVariableCountOffset = kPositionInfoOffsetEnd + 1;
  static constexpr int kModuleVariableCountOffsetEnd = kModuleVariableCountOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kModuleVariableCountOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kModuleVariableCountOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kModuleVariableCountOffsetEnd + 1;

  static_assert(kFlagsOffset == offsetof(ScopeInfo, flags_),
                "Value of ScopeInfo::kFlagsOffset defined in Torque and offset of field ScopeInfo::flags in C++ do not match");
  static_assert(kParameterCountOffset == offsetof(ScopeInfo, parameter_count_),
                "Value of ScopeInfo::kParameterCountOffset defined in Torque and offset of field ScopeInfo::parameter_count in C++ do not match");
  static_assert(kContextLocalCountOffset == offsetof(ScopeInfo, context_local_count_),
                "Value of ScopeInfo::kContextLocalCountOffset defined in Torque and offset of field ScopeInfo::context_local_count in C++ do not match");
  static_assert(kModuleVariableCountOffset == OFFSET_OF_DATA_START(ScopeInfo),
                "Value of ScopeInfo::kModuleVariableCountOffset defined in Torque and offset of field ScopeInfo::module_variable_count in C++ do not match");
};

} // namespace internal
} // namespace v8
