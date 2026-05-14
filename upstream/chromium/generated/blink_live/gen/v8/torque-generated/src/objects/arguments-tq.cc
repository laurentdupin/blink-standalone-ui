#include "src/objects/arguments.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/arguments.tq?l=5&c=1
class TorqueGeneratedJSArgumentsObjectAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSObject);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSObject);
  static constexpr int kHeaderSize = sizeof(JSObject);

};

// Definition https://crsrc.org/c/v8/src/objects/arguments.tq?l=28&c=1
class TorqueGeneratedSloppyArgumentsElementsAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(FixedArrayBase);
  // https://crsrc.org/c/v8/src/objects/arguments.tq?l=30&c=3
  static constexpr int kContextOffset = sizeof(FixedArrayBase);
  static constexpr int kContextOffsetEnd = kContextOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/arguments.tq?l=31&c=3
  static constexpr int kArgumentsOffset = kContextOffsetEnd + 1;
  static constexpr int kArgumentsOffsetEnd = kArgumentsOffset + kTaggedSize - 1;
  static constexpr int kHeaderSize = kArgumentsOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/arguments.tq?l=32&c=3
  static constexpr int kMappedEntriesOffset = kArgumentsOffsetEnd + 1;
  static constexpr int kMappedEntriesOffsetEnd = kMappedEntriesOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kMappedEntriesOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kMappedEntriesOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kMappedEntriesOffsetEnd + 1;

  static_assert(kContextOffset == offsetof(SloppyArgumentsElements, context_),
                "Value of SloppyArgumentsElements::kContextOffset defined in Torque and offset of field SloppyArgumentsElements::context in C++ do not match");
  static_assert(kArgumentsOffset == offsetof(SloppyArgumentsElements, arguments_),
                "Value of SloppyArgumentsElements::kArgumentsOffset defined in Torque and offset of field SloppyArgumentsElements::arguments in C++ do not match");
  static_assert(kMappedEntriesOffset == OFFSET_OF_DATA_START(SloppyArgumentsElements),
                "Value of SloppyArgumentsElements::kMappedEntriesOffset defined in Torque and offset of field SloppyArgumentsElements::mapped_entries in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/arguments.tq?l=48&c=1
class TorqueGeneratedAliasedArgumentsEntryAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(Struct);
  // https://crsrc.org/c/v8/src/objects/arguments.tq?l=50&c=3
  static constexpr int kAliasedContextSlotOffset = sizeof(Struct);
  static constexpr int kAliasedContextSlotOffsetEnd = kAliasedContextSlotOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kAliasedContextSlotOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kAliasedContextSlotOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kAliasedContextSlotOffsetEnd + 1;
  static constexpr int kHeaderSize = kAliasedContextSlotOffsetEnd + 1;
  static constexpr int kSize = kAliasedContextSlotOffsetEnd + 1;

  static_assert(kAliasedContextSlotOffset == offsetof(AliasedArgumentsEntry, aliased_context_slot_),
                "Value of AliasedArgumentsEntry::kAliasedContextSlotOffset defined in Torque and offset of field AliasedArgumentsEntry::aliased_context_slot in C++ do not match");
  static_assert(kSize == sizeof(AliasedArgumentsEntry));
};

} // namespace internal
} // namespace v8
