#include "src/objects/js-atomics-synchronization.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-atomics-synchronization.tq?l=5&c=1
class TorqueGeneratedJSSynchronizationPrimitiveAsserts {
  // https://crsrc.org/c/v8/src/objects/js-atomics-synchronization.tq?l=8&c=3
  static constexpr int kWaiterQueueHeadOffset = sizeof(AlwaysSharedSpaceJSObject);
  static constexpr int kWaiterQueueHeadOffsetEnd = kWaiterQueueHeadOffset + kExternalPointerSlotSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-atomics-synchronization.tq?l=9&c=3
  static constexpr int kStateOffset = kWaiterQueueHeadOffsetEnd + 1;
  static constexpr int kStateOffsetEnd = kStateOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kStateOffsetEnd + 1;
  static constexpr int kHeaderSize = kStateOffsetEnd + 1;

  static_assert(kWaiterQueueHeadOffset == offsetof(JSSynchronizationPrimitive, waiter_queue_head_),
                "Value of JSSynchronizationPrimitive::kWaiterQueueHeadOffset defined in Torque and offset of field JSSynchronizationPrimitive::waiter_queue_head in C++ do not match");
  static_assert(kStateOffset == offsetof(JSSynchronizationPrimitive, state_),
                "Value of JSSynchronizationPrimitive::kStateOffset defined in Torque and offset of field JSSynchronizationPrimitive::state in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-atomics-synchronization.tq?l=12&c=1
class TorqueGeneratedJSAtomicsMutexAsserts {
  // https://crsrc.org/c/v8/src/objects/js-atomics-synchronization.tq?l=14&c=3
  static constexpr int kOwnerThreadIdOffset = sizeof(JSSynchronizationPrimitive);
  static constexpr int kOwnerThreadIdOffsetEnd = kOwnerThreadIdOffset + kInt32Size - 1;
  static constexpr int kStartOfWeakFieldsOffset = kOwnerThreadIdOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kOwnerThreadIdOffsetEnd + 1;
  static constexpr int kStartOfStrongFieldsOffset = kOwnerThreadIdOffsetEnd + 1;
  static constexpr int kEndOfStrongFieldsOffset = kOwnerThreadIdOffsetEnd + 1;
  static constexpr int kHeaderSize = kOwnerThreadIdOffsetEnd + 1;

  static_assert(kOwnerThreadIdOffset == offsetof(JSAtomicsMutex, owner_thread_id_),
                "Value of JSAtomicsMutex::kOwnerThreadIdOffset defined in Torque and offset of field JSAtomicsMutex::owner_thread_id in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-atomics-synchronization.tq?l=17&c=1
class TorqueGeneratedJSAtomicsConditionAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSSynchronizationPrimitive);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSSynchronizationPrimitive);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSSynchronizationPrimitive);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSSynchronizationPrimitive);
  static constexpr int kHeaderSize = sizeof(JSSynchronizationPrimitive);

};

} // namespace internal
} // namespace v8
