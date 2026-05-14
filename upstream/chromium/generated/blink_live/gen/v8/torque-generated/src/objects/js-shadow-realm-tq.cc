#include "src/objects/js-shadow-realm.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-shadow-realm.tq?l=5&c=1
class TorqueGeneratedJSShadowRealmAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-shadow-realm.tq?l=7&c=3
  static constexpr int kNativeContextOffset = sizeof(JSObject);
  static constexpr int kNativeContextOffsetEnd = kNativeContextOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kNativeContextOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kNativeContextOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kNativeContextOffsetEnd + 1;
  static constexpr int kHeaderSize = kNativeContextOffsetEnd + 1;

  static_assert(kNativeContextOffset == offsetof(JSShadowRealm, native_context_),
                "Value of JSShadowRealm::kNativeContextOffset defined in Torque and offset of field JSShadowRealm::native_context in C++ do not match");
};

} // namespace internal
} // namespace v8
