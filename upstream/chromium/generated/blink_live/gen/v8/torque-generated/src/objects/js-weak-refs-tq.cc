#include "src/objects/js-weak-refs.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=22&c=1
class TorqueGeneratedWeakCellAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=24&c=3
  static constexpr int kFinalizationRegistryOffset = sizeof(HeapObjectLayout);
  static constexpr int kFinalizationRegistryOffsetEnd = kFinalizationRegistryOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=25&c=3
  static constexpr int kHoldingsOffset = kFinalizationRegistryOffsetEnd + 1;
  static constexpr int kHoldingsOffsetEnd = kHoldingsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=26&c=3
  static constexpr int kTargetOffset = kHoldingsOffsetEnd + 1;
  static constexpr int kTargetOffsetEnd = kTargetOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=27&c=3
  static constexpr int kUnregisterTokenOffset = kTargetOffsetEnd + 1;
  static constexpr int kUnregisterTokenOffsetEnd = kUnregisterTokenOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=31&c=3
  static constexpr int kPrevOffset = kUnregisterTokenOffsetEnd + 1;
  static constexpr int kPrevOffsetEnd = kPrevOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=32&c=3
  static constexpr int kNextOffset = kPrevOffsetEnd + 1;
  static constexpr int kNextOffsetEnd = kNextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=40&c=3
  static constexpr int kKeyListPrevOffset = kNextOffsetEnd + 1;
  static constexpr int kKeyListPrevOffsetEnd = kKeyListPrevOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=41&c=3
  static constexpr int kKeyListNextOffset = kKeyListPrevOffsetEnd + 1;
  static constexpr int kKeyListNextOffsetEnd = kKeyListNextOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kKeyListNextOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kKeyListNextOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kKeyListNextOffsetEnd + 1;
  static constexpr int kHeaderSize = kKeyListNextOffsetEnd + 1;
  static constexpr int kSize = kKeyListNextOffsetEnd + 1;

  static_assert(kFinalizationRegistryOffset == offsetof(WeakCell, finalization_registry_),
                "Value of WeakCell::kFinalizationRegistryOffset defined in Torque and offset of field WeakCell::finalization_registry in C++ do not match");
  static_assert(kHoldingsOffset == offsetof(WeakCell, holdings_),
                "Value of WeakCell::kHoldingsOffset defined in Torque and offset of field WeakCell::holdings in C++ do not match");
  static_assert(kTargetOffset == offsetof(WeakCell, target_),
                "Value of WeakCell::kTargetOffset defined in Torque and offset of field WeakCell::target in C++ do not match");
  static_assert(kUnregisterTokenOffset == offsetof(WeakCell, unregister_token_),
                "Value of WeakCell::kUnregisterTokenOffset defined in Torque and offset of field WeakCell::unregister_token in C++ do not match");
  static_assert(kPrevOffset == offsetof(WeakCell, prev_),
                "Value of WeakCell::kPrevOffset defined in Torque and offset of field WeakCell::prev in C++ do not match");
  static_assert(kNextOffset == offsetof(WeakCell, next_),
                "Value of WeakCell::kNextOffset defined in Torque and offset of field WeakCell::next in C++ do not match");
  static_assert(kKeyListPrevOffset == offsetof(WeakCell, key_list_prev_),
                "Value of WeakCell::kKeyListPrevOffset defined in Torque and offset of field WeakCell::key_list_prev in C++ do not match");
  static_assert(kKeyListNextOffset == offsetof(WeakCell, key_list_next_),
                "Value of WeakCell::kKeyListNextOffset defined in Torque and offset of field WeakCell::key_list_next in C++ do not match");
  static_assert(kSize == sizeof(WeakCell));
};

// Definition https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=9&c=1
class TorqueGeneratedJSFinalizationRegistryAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=11&c=3
  static constexpr int kNativeContextOffset = sizeof(JSObject);
  static constexpr int kNativeContextOffsetEnd = kNativeContextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=12&c=3
  static constexpr int kCleanupOffset = kNativeContextOffsetEnd + 1;
  static constexpr int kCleanupOffsetEnd = kCleanupOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=13&c=3
  static constexpr int kActiveCellsOffset = kCleanupOffsetEnd + 1;
  static constexpr int kActiveCellsOffsetEnd = kActiveCellsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=14&c=3
  static constexpr int kClearedCellsOffset = kActiveCellsOffsetEnd + 1;
  static constexpr int kClearedCellsOffsetEnd = kClearedCellsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=15&c=3
  static constexpr int kKeyMapOffset = kClearedCellsOffsetEnd + 1;
  static constexpr int kKeyMapOffsetEnd = kKeyMapOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=18&c=3
  static constexpr int kNextDirtyOffset = kKeyMapOffsetEnd + 1;
  static constexpr int kNextDirtyOffsetEnd = kNextDirtyOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=19&c=3
  static constexpr int kFlagsOffset = kNextDirtyOffsetEnd + 1;
  static constexpr int kFlagsOffsetEnd = kFlagsOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kFlagsOffsetEnd + 1;
  static constexpr int kHeaderSize = kFlagsOffsetEnd + 1;

  static_assert(kNativeContextOffset == offsetof(JSFinalizationRegistry, native_context_),
                "Value of JSFinalizationRegistry::kNativeContextOffset defined in Torque and offset of field JSFinalizationRegistry::native_context in C++ do not match");
  static_assert(kCleanupOffset == offsetof(JSFinalizationRegistry, cleanup_),
                "Value of JSFinalizationRegistry::kCleanupOffset defined in Torque and offset of field JSFinalizationRegistry::cleanup in C++ do not match");
  static_assert(kActiveCellsOffset == offsetof(JSFinalizationRegistry, active_cells_),
                "Value of JSFinalizationRegistry::kActiveCellsOffset defined in Torque and offset of field JSFinalizationRegistry::active_cells in C++ do not match");
  static_assert(kClearedCellsOffset == offsetof(JSFinalizationRegistry, cleared_cells_),
                "Value of JSFinalizationRegistry::kClearedCellsOffset defined in Torque and offset of field JSFinalizationRegistry::cleared_cells in C++ do not match");
  static_assert(kKeyMapOffset == offsetof(JSFinalizationRegistry, key_map_),
                "Value of JSFinalizationRegistry::kKeyMapOffset defined in Torque and offset of field JSFinalizationRegistry::key_map in C++ do not match");
  static_assert(kNextDirtyOffset == offsetof(JSFinalizationRegistry, next_dirty_),
                "Value of JSFinalizationRegistry::kNextDirtyOffset defined in Torque and offset of field JSFinalizationRegistry::next_dirty in C++ do not match");
  static_assert(kFlagsOffset == offsetof(JSFinalizationRegistry, flags_),
                "Value of JSFinalizationRegistry::kFlagsOffset defined in Torque and offset of field JSFinalizationRegistry::flags in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=44&c=1
class TorqueGeneratedJSWeakRefAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-weak-refs.tq?l=46&c=3
  static constexpr int kTargetOffset = sizeof(JSObject);
  static constexpr int kTargetOffsetEnd = kTargetOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kTargetOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kTargetOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kTargetOffsetEnd + 1;
  static constexpr int kHeaderSize = kTargetOffsetEnd + 1;

  static_assert(kTargetOffset == offsetof(JSWeakRef, target_),
                "Value of JSWeakRef::kTargetOffset defined in Torque and offset of field JSWeakRef::target in C++ do not match");
};

} // namespace internal
} // namespace v8
