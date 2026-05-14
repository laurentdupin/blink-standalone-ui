#include "third_party/v8/builtins/array-sort.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=24&c=1
class TorqueGeneratedSortStateAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=27&c=3
  static constexpr int kReceiverOffset = sizeof(HeapObjectLayout);
  static constexpr int kReceiverOffsetEnd = kReceiverOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=32&c=3
  static constexpr int kInitialReceiverMapOffset = kReceiverOffsetEnd + 1;
  static constexpr int kInitialReceiverMapOffsetEnd = kInitialReceiverMapOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=33&c=3
  static constexpr int kInitialReceiverLengthOffset = kInitialReceiverMapOffsetEnd + 1;
  static constexpr int kInitialReceiverLengthOffsetEnd = kInitialReceiverLengthOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=36&c=3
  static constexpr int kUserCmpFnOffset = kInitialReceiverLengthOffsetEnd + 1;
  static constexpr int kUserCmpFnOffsetEnd = kUserCmpFnOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=38&c=3
  static constexpr int kIsResetToGenericOffset = kUserCmpFnOffsetEnd + 1;
  static constexpr int kIsResetToGenericOffsetEnd = kIsResetToGenericOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=43&c=3
  static constexpr int kMinGallopOffset = kIsResetToGenericOffsetEnd + 1;
  static constexpr int kMinGallopOffsetEnd = kMinGallopOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=55&c=3
  static constexpr int kPendingRunsSizeOffset = kMinGallopOffsetEnd + 1;
  static constexpr int kPendingRunsSizeOffsetEnd = kPendingRunsSizeOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=56&c=3
  static constexpr int kPendingRunsOffset = kPendingRunsSizeOffsetEnd + 1;
  static constexpr int kPendingRunsOffsetEnd = kPendingRunsOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=57&c=3
  static constexpr int kPendingPowersOffset = kPendingRunsOffsetEnd + 1;
  static constexpr int kPendingPowersOffsetEnd = kPendingPowersOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=62&c=3
  static constexpr int kWorkArrayOffset = kPendingPowersOffsetEnd + 1;
  static constexpr int kWorkArrayOffsetEnd = kWorkArrayOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=65&c=3
  static constexpr int kTempArrayOffset = kWorkArrayOffsetEnd + 1;
  static constexpr int kTempArrayOffsetEnd = kTempArrayOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=68&c=3
  static constexpr int kSortLengthOffset = kTempArrayOffsetEnd + 1;
  static constexpr int kSortLengthOffsetEnd = kSortLengthOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=72&c=3
  static constexpr int kNumberOfUndefinedOffset = kSortLengthOffsetEnd + 1;
  static constexpr int kNumberOfUndefinedOffsetEnd = kNumberOfUndefinedOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kHeaderSize = kNumberOfUndefinedOffsetEnd + 1;
  static constexpr int kSize = kNumberOfUndefinedOffsetEnd + 1;

  static_assert(kReceiverOffset == offsetof(SortState, receiver_),
                "Value of SortState::kReceiverOffset defined in Torque and offset of field SortState::receiver in C++ do not match");
  static_assert(kInitialReceiverMapOffset == offsetof(SortState, initial_receiver_map_),
                "Value of SortState::kInitialReceiverMapOffset defined in Torque and offset of field SortState::initial_receiver_map in C++ do not match");
  static_assert(kInitialReceiverLengthOffset == offsetof(SortState, initial_receiver_length_),
                "Value of SortState::kInitialReceiverLengthOffset defined in Torque and offset of field SortState::initial_receiver_length in C++ do not match");
  static_assert(kUserCmpFnOffset == offsetof(SortState, user_cmp_fn_),
                "Value of SortState::kUserCmpFnOffset defined in Torque and offset of field SortState::user_cmp_fn in C++ do not match");
  static_assert(kIsResetToGenericOffset == offsetof(SortState, is_reset_to_generic_),
                "Value of SortState::kIsResetToGenericOffset defined in Torque and offset of field SortState::is_reset_to_generic in C++ do not match");
  static_assert(kMinGallopOffset == offsetof(SortState, min_gallop_),
                "Value of SortState::kMinGallopOffset defined in Torque and offset of field SortState::min_gallop in C++ do not match");
  static_assert(kPendingRunsSizeOffset == offsetof(SortState, pending_runs_size_),
                "Value of SortState::kPendingRunsSizeOffset defined in Torque and offset of field SortState::pending_runs_size in C++ do not match");
  static_assert(kPendingRunsOffset == offsetof(SortState, pending_runs_),
                "Value of SortState::kPendingRunsOffset defined in Torque and offset of field SortState::pending_runs in C++ do not match");
  static_assert(kPendingPowersOffset == offsetof(SortState, pending_powers_),
                "Value of SortState::kPendingPowersOffset defined in Torque and offset of field SortState::pending_powers in C++ do not match");
  static_assert(kWorkArrayOffset == offsetof(SortState, work_array_),
                "Value of SortState::kWorkArrayOffset defined in Torque and offset of field SortState::work_array in C++ do not match");
  static_assert(kTempArrayOffset == offsetof(SortState, temp_array_),
                "Value of SortState::kTempArrayOffset defined in Torque and offset of field SortState::temp_array in C++ do not match");
  static_assert(kSortLengthOffset == offsetof(SortState, sort_length_),
                "Value of SortState::kSortLengthOffset defined in Torque and offset of field SortState::sort_length in C++ do not match");
  static_assert(kNumberOfUndefinedOffset == offsetof(SortState, number_of_undefined_),
                "Value of SortState::kNumberOfUndefinedOffset defined in Torque and offset of field SortState::number_of_undefined in C++ do not match");
  static_assert(kSize == sizeof(SortState));
};

} // namespace internal
} // namespace v8
