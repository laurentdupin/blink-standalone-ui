#include "src/objects/js-promise.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-promise.tq?l=12&c=1
class TorqueGeneratedJSPromiseAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObjectWithEmbedderSlots);
  // https://crsrc.org/c/v8/src/objects/js-promise.tq?l=35&c=3
  static constexpr int kReactionsOrResultOffset = sizeof(JSObjectWithEmbedderSlots);
  static constexpr int kReactionsOrResultOffsetEnd = kReactionsOrResultOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-promise.tq?l=36&c=3
  static constexpr int kFlagsOffset = kReactionsOrResultOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kReactionsOrResultOffset == offsetof(JSPromise, reactions_or_result_),
                "Value of JSPromise::kReactionsOrResultOffset defined in Torque and offset of field JSPromise::reactions_or_result in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSPromise, flags_),
                "Value of JSPromise::kFlagsOffset defined in Torque and offset of field JSPromise::flags in C++ do not match");
};

} // namespace internal
} // namespace v8
