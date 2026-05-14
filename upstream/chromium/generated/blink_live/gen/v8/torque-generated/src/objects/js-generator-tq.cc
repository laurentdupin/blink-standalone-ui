#include "src/objects/js-generator.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-generator.tq?l=11&c=1
class TorqueGeneratedJSGeneratorObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=13&c=3
  static constexpr int kFunctionOffset = sizeof(JSObject);
  static constexpr int kFunctionOffsetEnd = kFunctionOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=14&c=3
  static constexpr int kContextOffset = kFunctionOffsetEnd + 1;
  static constexpr int kContextOffsetEnd = kContextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=15&c=3
  static constexpr int kReceiverOffset = kContextOffsetEnd + 1;
  static constexpr int kReceiverOffsetEnd = kReceiverOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=21&c=3
  static constexpr int kInputOrDebugPosOffset = kReceiverOffsetEnd + 1;
  static constexpr int kInputOrDebugPosOffsetEnd = kInputOrDebugPosOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=24&c=3
  static constexpr int kResumeModeOffset = kInputOrDebugPosOffsetEnd + 1;
  static constexpr int kResumeModeOffsetEnd = kResumeModeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=29&c=3
  static constexpr int kContinuationOffset = kResumeModeOffsetEnd + 1;
  static constexpr int kContinuationOffsetEnd = kContinuationOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=32&c=3
  static constexpr int kParametersAndRegistersOffset = kContinuationOffsetEnd + 1;
  static constexpr int kParametersAndRegistersOffsetEnd = kParametersAndRegistersOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kParametersAndRegistersOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kParametersAndRegistersOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kParametersAndRegistersOffsetEnd + 1;
  static constexpr int kHeaderSize = kParametersAndRegistersOffsetEnd + 1;

  static_assert(kFunctionOffset == offsetof(JSGeneratorObject, function_),
                "Value of JSGeneratorObject::kFunctionOffset defined in Torque and offset of field JSGeneratorObject::function in C++ do not match");
  static_assert(kContextOffset == offsetof(JSGeneratorObject, context_),
                "Value of JSGeneratorObject::kContextOffset defined in Torque and offset of field JSGeneratorObject::context in C++ do not match");
  static_assert(kReceiverOffset == offsetof(JSGeneratorObject, receiver_),
                "Value of JSGeneratorObject::kReceiverOffset defined in Torque and offset of field JSGeneratorObject::receiver in C++ do not match");
  static_assert(kInputOrDebugPosOffset == offsetof(JSGeneratorObject, input_or_debug_pos_),
                "Value of JSGeneratorObject::kInputOrDebugPosOffset defined in Torque and offset of field JSGeneratorObject::input_or_debug_pos in C++ do not match");
  static_assert(kResumeModeOffset == offsetof(JSGeneratorObject, resume_mode_),
                "Value of JSGeneratorObject::kResumeModeOffset defined in Torque and offset of field JSGeneratorObject::resume_mode in C++ do not match");
  static_assert(kContinuationOffset == offsetof(JSGeneratorObject, continuation_),
                "Value of JSGeneratorObject::kContinuationOffset defined in Torque and offset of field JSGeneratorObject::continuation in C++ do not match");
  static_assert(kParametersAndRegistersOffset == offsetof(JSGeneratorObject, parameters_and_registers_),
                "Value of JSGeneratorObject::kParametersAndRegistersOffset defined in Torque and offset of field JSGeneratorObject::parameters_and_registers in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-generator.tq?l=35&c=1
class TorqueGeneratedJSAsyncFunctionObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSGeneratorObject);
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=37&c=3
  static constexpr int kPromiseOffset = sizeof(JSGeneratorObject);
  static constexpr int kPromiseOffsetEnd = kPromiseOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=40&c=3
  static constexpr int kAwaitResolveClosureOffset = kPromiseOffsetEnd + 1;
  static constexpr int kAwaitResolveClosureOffsetEnd = kAwaitResolveClosureOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=41&c=3
  static constexpr int kAwaitRejectClosureOffset = kAwaitResolveClosureOffsetEnd + 1;
  static constexpr int kAwaitRejectClosureOffsetEnd = kAwaitRejectClosureOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kAwaitRejectClosureOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kAwaitRejectClosureOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kAwaitRejectClosureOffsetEnd + 1;
  static constexpr int kHeaderSize = kAwaitRejectClosureOffsetEnd + 1;

  static_assert(kPromiseOffset == offsetof(JSAsyncFunctionObject, promise_),
                "Value of JSAsyncFunctionObject::kPromiseOffset defined in Torque and offset of field JSAsyncFunctionObject::promise in C++ do not match");
  static_assert(kAwaitResolveClosureOffset == offsetof(JSAsyncFunctionObject, await_resolve_closure_),
                "Value of JSAsyncFunctionObject::kAwaitResolveClosureOffset defined in Torque and offset of field JSAsyncFunctionObject::await_resolve_closure in C++ do not match");
  static_assert(kAwaitRejectClosureOffset == offsetof(JSAsyncFunctionObject, await_reject_closure_),
                "Value of JSAsyncFunctionObject::kAwaitRejectClosureOffset defined in Torque and offset of field JSAsyncFunctionObject::await_reject_closure in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-generator.tq?l=44&c=1
class TorqueGeneratedJSAsyncGeneratorObjectAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSGeneratorObject);
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=48&c=3
  static constexpr int kQueueOffset = sizeof(JSGeneratorObject);
  static constexpr int kQueueOffsetEnd = kQueueOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=50&c=3
  static constexpr int kIsAwaitingOffset = kQueueOffsetEnd + 1;
  static constexpr int kIsAwaitingOffsetEnd = kIsAwaitingOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIsAwaitingOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIsAwaitingOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIsAwaitingOffsetEnd + 1;
  static constexpr int kHeaderSize = kIsAwaitingOffsetEnd + 1;

  static_assert(kQueueOffset == offsetof(JSAsyncGeneratorObject, queue_),
                "Value of JSAsyncGeneratorObject::kQueueOffset defined in Torque and offset of field JSAsyncGeneratorObject::queue in C++ do not match");
  static_assert(kIsAwaitingOffset == offsetof(JSAsyncGeneratorObject, is_awaiting_),
                "Value of JSAsyncGeneratorObject::kIsAwaitingOffset defined in Torque and offset of field JSAsyncGeneratorObject::is_awaiting in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-generator.tq?l=53&c=1
class TorqueGeneratedAsyncGeneratorRequestAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(Struct);
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=55&c=3
  static constexpr int kNextOffset = sizeof(Struct);
  static constexpr int kNextOffsetEnd = kNextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=56&c=3
  static constexpr int kResumeModeOffset = kNextOffsetEnd + 1;
  static constexpr int kResumeModeOffsetEnd = kResumeModeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=57&c=3
  static constexpr int kValueOffset = kResumeModeOffsetEnd + 1;
  static constexpr int kValueOffsetEnd = kValueOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-generator.tq?l=58&c=3
  static constexpr int kPromiseOffset = kValueOffsetEnd + 1;
  static constexpr int kPromiseOffsetEnd = kPromiseOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kPromiseOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kPromiseOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kPromiseOffsetEnd + 1;
  static constexpr int kHeaderSize = kPromiseOffsetEnd + 1;
  static constexpr int kSize = kPromiseOffsetEnd + 1;

  static_assert(kNextOffset == offsetof(AsyncGeneratorRequest, next_),
                "Value of AsyncGeneratorRequest::kNextOffset defined in Torque and offset of field AsyncGeneratorRequest::next in C++ do not match");
  static_assert(kResumeModeOffset == offsetof(AsyncGeneratorRequest, resume_mode_),
                "Value of AsyncGeneratorRequest::kResumeModeOffset defined in Torque and offset of field AsyncGeneratorRequest::resume_mode in C++ do not match");
  static_assert(kValueOffset == offsetof(AsyncGeneratorRequest, value_),
                "Value of AsyncGeneratorRequest::kValueOffset defined in Torque and offset of field AsyncGeneratorRequest::value in C++ do not match");
  static_assert(kPromiseOffset == offsetof(AsyncGeneratorRequest, promise_),
                "Value of AsyncGeneratorRequest::kPromiseOffset defined in Torque and offset of field AsyncGeneratorRequest::promise in C++ do not match");
  static_assert(kSize == sizeof(AsyncGeneratorRequest));
};

} // namespace internal
} // namespace v8
