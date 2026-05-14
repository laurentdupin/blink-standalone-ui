#include "src/objects/js-function.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-function.tq?l=5&c=1
class TorqueGeneratedJSFunctionOrBoundFunctionOrWrappedFunctionAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kHeaderSize = sizeof(JSObject);

};

// Definition https://crsrc.org/c/v8/src/objects/js-function.tq?l=35&c=1
class TorqueGeneratedJSFunctionAsserts {
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=38&c=3
  static constexpr int kDispatchHandleOffset = sizeof(JSFunctionOrBoundFunctionOrWrappedFunction);
  static constexpr int kDispatchHandleOffsetEnd = kDispatchHandleOffset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kDispatchHandleOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=40&c=3
  static constexpr int kSharedFunctionInfoOffset = kDispatchHandleOffsetEnd + 1;
  static constexpr int kSharedFunctionInfoOffsetEnd = kSharedFunctionInfoOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=41&c=3
  static constexpr int kContextOffset = kSharedFunctionInfoOffsetEnd + 1;
  static constexpr int kContextOffsetEnd = kContextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=42&c=3
  static constexpr int kFeedbackCellOffset = kContextOffsetEnd + 1;
  static constexpr int kFeedbackCellOffsetEnd = kFeedbackCellOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFeedbackCellOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFeedbackCellOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFeedbackCellOffsetEnd + 1;
  static constexpr int kHeaderSize = kFeedbackCellOffsetEnd + 1;

  static_assert(kDispatchHandleOffset == offsetof(JSFunction, dispatch_handle_),
                "Value of JSFunction::kDispatchHandleOffset defined in Torque and offset of field JSFunction::dispatch_handle in C++ do not match");
  static_assert(kSharedFunctionInfoOffset == offsetof(JSFunction, shared_function_info_),
                "Value of JSFunction::kSharedFunctionInfoOffset defined in Torque and offset of field JSFunction::shared_function_info in C++ do not match");
  static_assert(kContextOffset == offsetof(JSFunction, context_),
                "Value of JSFunction::kContextOffset defined in Torque and offset of field JSFunction::context in C++ do not match");
  static_assert(kFeedbackCellOffset == offsetof(JSFunction, feedback_cell_),
                "Value of JSFunction::kFeedbackCellOffset defined in Torque and offset of field JSFunction::feedback_cell in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-function.tq?l=22&c=1
class TorqueGeneratedJSWrappedFunctionAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSFunctionOrBoundFunctionOrWrappedFunction);
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=26&c=3
  static constexpr int kWrappedTargetFunctionOffset = sizeof(JSFunctionOrBoundFunctionOrWrappedFunction);
  static constexpr int kWrappedTargetFunctionOffsetEnd = kWrappedTargetFunctionOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=28&c=3
  static constexpr int kContextOffset = kWrappedTargetFunctionOffsetEnd + 1;
  static constexpr int kContextOffsetEnd = kContextOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kContextOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kContextOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kContextOffsetEnd + 1;
  static constexpr int kHeaderSize = kContextOffsetEnd + 1;

  static_assert(kWrappedTargetFunctionOffset == offsetof(JSWrappedFunction, wrapped_target_function_),
                "Value of JSWrappedFunction::kWrappedTargetFunctionOffset defined in Torque and offset of field JSWrappedFunction::wrapped_target_function in C++ do not match");
  static_assert(kContextOffset == offsetof(JSWrappedFunction, context_),
                "Value of JSWrappedFunction::kContextOffset defined in Torque and offset of field JSWrappedFunction::context in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-function.tq?l=9&c=1
class TorqueGeneratedJSBoundFunctionAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSFunctionOrBoundFunctionOrWrappedFunction);
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=13&c=3
  static constexpr int kBoundTargetFunctionOffset = sizeof(JSFunctionOrBoundFunctionOrWrappedFunction);
  static constexpr int kBoundTargetFunctionOffsetEnd = kBoundTargetFunctionOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=16&c=3
  static constexpr int kBoundThisOffset = kBoundTargetFunctionOffsetEnd + 1;
  static constexpr int kBoundThisOffsetEnd = kBoundThisOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=19&c=3
  static constexpr int kBoundArgumentsOffset = kBoundThisOffsetEnd + 1;
  static constexpr int kBoundArgumentsOffsetEnd = kBoundArgumentsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kBoundArgumentsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kBoundArgumentsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kBoundArgumentsOffsetEnd + 1;
  static constexpr int kHeaderSize = kBoundArgumentsOffsetEnd + 1;

  static_assert(kBoundTargetFunctionOffset == offsetof(JSBoundFunction, bound_target_function_),
                "Value of JSBoundFunction::kBoundTargetFunctionOffset defined in Torque and offset of field JSBoundFunction::bound_target_function in C++ do not match");
  static_assert(kBoundThisOffset == offsetof(JSBoundFunction, bound_this_),
                "Value of JSBoundFunction::kBoundThisOffset defined in Torque and offset of field JSBoundFunction::bound_this in C++ do not match");
  static_assert(kBoundArgumentsOffset == offsetof(JSBoundFunction, bound_arguments_),
                "Value of JSBoundFunction::kBoundArgumentsOffset defined in Torque and offset of field JSBoundFunction::bound_arguments in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-function.tq?l=60&c=1
class TorqueGeneratedJSFunctionWithPrototypeAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSFunction);
  // https://crsrc.org/c/v8/src/objects/js-function.tq?l=63&c=3
  static constexpr int kPrototypeOrInitialMapOffset = sizeof(JSFunction);
  static constexpr int kPrototypeOrInitialMapOffsetEnd = kPrototypeOrInitialMapOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPrototypeOrInitialMapOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPrototypeOrInitialMapOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPrototypeOrInitialMapOffsetEnd + 1;
  static constexpr int kHeaderSize = kPrototypeOrInitialMapOffsetEnd + 1;

  static_assert(kPrototypeOrInitialMapOffset == offsetof(JSFunctionWithPrototype, prototype_or_initial_map_),
                "Value of JSFunctionWithPrototype::kPrototypeOrInitialMapOffset defined in Torque and offset of field JSFunctionWithPrototype::prototype_or_initial_map in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-function.tq?l=56&c=1
class TorqueGeneratedJSFunctionWithoutPrototypeAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSFunction);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSFunction);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSFunction);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSFunction);
  static constexpr int kHeaderSize = sizeof(JSFunction);

};

} // namespace internal
} // namespace v8
