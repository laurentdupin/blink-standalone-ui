#include "src/objects/js-disposable-stack.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=24&c=1
class TorqueGeneratedJSDisposableStackBaseAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=31&c=3
  static constexpr int kStackOffset = sizeof(JSObject);
  static constexpr int kStackOffsetEnd = kStackOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=32&c=3
  static constexpr int kStatusOffset = kStackOffsetEnd + 1;
  static constexpr int kStatusOffsetEnd = kStatusOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=33&c=3
  static constexpr int kErrorOffset = kStatusOffsetEnd + 1;
  static constexpr int kErrorOffsetEnd = kErrorOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=34&c=3
  static constexpr int kErrorMessageOffset = kErrorOffsetEnd + 1;
  static constexpr int kErrorMessageOffsetEnd = kErrorMessageOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kErrorMessageOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kErrorMessageOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kErrorMessageOffsetEnd + 1;
  static constexpr int kHeaderSize = kErrorMessageOffsetEnd + 1;

  static_assert(kStackOffset == offsetof(JSDisposableStackBase, stack_),
                "Value of JSDisposableStackBase::kStackOffset defined in Torque and offset of field JSDisposableStackBase::stack in C++ do not match");
  static_assert(kStatusOffset == offsetof(JSDisposableStackBase, status_),
                "Value of JSDisposableStackBase::kStatusOffset defined in Torque and offset of field JSDisposableStackBase::status in C++ do not match");
  static_assert(kErrorOffset == offsetof(JSDisposableStackBase, error_),
                "Value of JSDisposableStackBase::kErrorOffset defined in Torque and offset of field JSDisposableStackBase::error in C++ do not match");
  static_assert(kErrorMessageOffset == offsetof(JSDisposableStackBase, error_message_),
                "Value of JSDisposableStackBase::kErrorMessageOffset defined in Torque and offset of field JSDisposableStackBase::error_message in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=37&c=1
class TorqueGeneratedJSSyncDisposableStackAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kHeaderSize = sizeof(JSDisposableStackBase);

};

// Definition https://crsrc.org/c/v8/src/objects/js-disposable-stack.tq?l=40&c=1
class TorqueGeneratedJSAsyncDisposableStackAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSDisposableStackBase);
  static constexpr int kHeaderSize = sizeof(JSDisposableStackBase);

};

} // namespace internal
} // namespace v8
