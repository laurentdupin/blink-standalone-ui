#include "src/objects/swiss-name-dictionary.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/swiss-name-dictionary.tq?l=7&c=1
class TorqueGeneratedSwissNameDictionaryAsserts {
  // https://crsrc.org/c/v8/src/objects/swiss-name-dictionary.tq?l=9&c=3
  static constexpr int kHashOffset = sizeof(HeapObjectLayout);
  static constexpr int kHashOffsetEnd = kHashOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/swiss-name-dictionary.tq?l=10&c=9
  static constexpr int kCapacityOffset = kHashOffsetEnd + 1;
  static constexpr int kCapacityOffsetEnd = kCapacityOffset + kInt32Size - 1;
  static constexpr int kStartOfStrongFieldsOffset = kCapacityOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/swiss-name-dictionary.tq?l=11&c=3
  static constexpr int kMetaTableOffset = kCapacityOffsetEnd + 1;
  static constexpr int kMetaTableOffsetEnd = kMetaTableOffset + kTaggedSize - 1;
  static constexpr int kHeaderSize = kMetaTableOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/swiss-name-dictionary.tq?l=12&c=3
  static constexpr int kDataTableOffset = kMetaTableOffsetEnd + 1;
  static constexpr int kDataTableOffsetEnd = kDataTableOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataTableOffsetEnd + 1;

  static_assert(kHashOffset == offsetof(SwissNameDictionary, hash_),
                "Value of SwissNameDictionary::kHashOffset defined in Torque and offset of field SwissNameDictionary::hash in C++ do not match");
  static_assert(kCapacityOffset == offsetof(SwissNameDictionary, capacity_),
                "Value of SwissNameDictionary::kCapacityOffset defined in Torque and offset of field SwissNameDictionary::capacity in C++ do not match");
  static_assert(kMetaTableOffset == offsetof(SwissNameDictionary, meta_table_),
                "Value of SwissNameDictionary::kMetaTableOffset defined in Torque and offset of field SwissNameDictionary::meta_table in C++ do not match");
  static_assert(kDataTableOffset == OFFSET_OF_DATA_START(SwissNameDictionary),
                "Value of SwissNameDictionary::kDataTableOffset defined in Torque and offset of field SwissNameDictionary::data_table in C++ do not match");
};

} // namespace internal
} // namespace v8
