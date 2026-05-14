#include "src/objects/ordered-hash-table.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=14&c=1
class TorqueGeneratedSmallOrderedHashTableAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(HeapObjectLayout);
  static constexpr int kHeaderSize = sizeof(HeapObjectLayout);

};

// Definition https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=22&c=1
class TorqueGeneratedSmallOrderedHashSetAsserts {
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=24&c=3
  static constexpr int kNumberOfElementsOffset = sizeof(SmallOrderedHashTable);
  static constexpr int kNumberOfElementsOffsetEnd = kNumberOfElementsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=25&c=3
  static constexpr int kNumberOfDeletedElementsOffset = kNumberOfElementsOffsetEnd + 1;
  static constexpr int kNumberOfDeletedElementsOffsetEnd = kNumberOfDeletedElementsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=26&c=9
  static constexpr int kNumberOfBucketsOffset = kNumberOfDeletedElementsOffsetEnd + 1;
  static constexpr int kNumberOfBucketsOffsetEnd = kNumberOfBucketsOffset + kUInt8Size - 1;
  static constexpr int kHeaderSize = kNumberOfBucketsOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=28&c=31
  static constexpr int kPaddingOffset = kNumberOfBucketsOffsetEnd + 1;
  static constexpr int kPaddingOffsetEnd = kPaddingOffset + (1 * kUInt8Size) - 1;
  static constexpr int kStartOfStrongFieldsOffset = kPaddingOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=29&c=3
  static constexpr int kDataTableOffset = kPaddingOffsetEnd + 1;
  static constexpr int kDataTableOffsetEnd = kDataTableOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataTableOffsetEnd + 1;

  static_assert(kNumberOfElementsOffset == offsetof(SmallOrderedHashSet, number_of_elements_),
                "Value of SmallOrderedHashSet::kNumberOfElementsOffset defined in Torque and offset of field SmallOrderedHashSet::number_of_elements in C++ do not match");
  static_assert(kNumberOfDeletedElementsOffset == offsetof(SmallOrderedHashSet, number_of_deleted_elements_),
                "Value of SmallOrderedHashSet::kNumberOfDeletedElementsOffset defined in Torque and offset of field SmallOrderedHashSet::number_of_deleted_elements in C++ do not match");
  static_assert(kNumberOfBucketsOffset == offsetof(SmallOrderedHashSet, number_of_buckets_),
                "Value of SmallOrderedHashSet::kNumberOfBucketsOffset defined in Torque and offset of field SmallOrderedHashSet::number_of_buckets in C++ do not match");
  static_assert(kPaddingOffset == offsetof(SmallOrderedHashSet, padding_),
                "Value of SmallOrderedHashSet::kPaddingOffset defined in Torque and offset of field SmallOrderedHashSet::padding in C++ do not match");
  static_assert(kDataTableOffset == OFFSET_OF_DATA_START(SmallOrderedHashSet),
                "Value of SmallOrderedHashSet::kDataTableOffset defined in Torque and offset of field SmallOrderedHashSet::data_table in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=61&c=1
class TorqueGeneratedSmallOrderedHashMapAsserts {
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=63&c=3
  static constexpr int kNumberOfElementsOffset = sizeof(SmallOrderedHashTable);
  static constexpr int kNumberOfElementsOffsetEnd = kNumberOfElementsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=64&c=3
  static constexpr int kNumberOfDeletedElementsOffset = kNumberOfElementsOffsetEnd + 1;
  static constexpr int kNumberOfDeletedElementsOffsetEnd = kNumberOfDeletedElementsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=65&c=9
  static constexpr int kNumberOfBucketsOffset = kNumberOfDeletedElementsOffsetEnd + 1;
  static constexpr int kNumberOfBucketsOffsetEnd = kNumberOfBucketsOffset + kUInt8Size - 1;
  static constexpr int kHeaderSize = kNumberOfBucketsOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=67&c=31
  static constexpr int kPaddingOffset = kNumberOfBucketsOffsetEnd + 1;
  static constexpr int kPaddingOffsetEnd = kPaddingOffset + (1 * kUInt8Size) - 1;
  static constexpr int kStartOfStrongFieldsOffset = kPaddingOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=68&c=3
  static constexpr int kDataTableOffset = kPaddingOffsetEnd + 1;
  static constexpr int kDataTableOffsetEnd = kDataTableOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataTableOffsetEnd + 1;

  static_assert(kNumberOfElementsOffset == offsetof(SmallOrderedHashMap, number_of_elements_),
                "Value of SmallOrderedHashMap::kNumberOfElementsOffset defined in Torque and offset of field SmallOrderedHashMap::number_of_elements in C++ do not match");
  static_assert(kNumberOfDeletedElementsOffset == offsetof(SmallOrderedHashMap, number_of_deleted_elements_),
                "Value of SmallOrderedHashMap::kNumberOfDeletedElementsOffset defined in Torque and offset of field SmallOrderedHashMap::number_of_deleted_elements in C++ do not match");
  static_assert(kNumberOfBucketsOffset == offsetof(SmallOrderedHashMap, number_of_buckets_),
                "Value of SmallOrderedHashMap::kNumberOfBucketsOffset defined in Torque and offset of field SmallOrderedHashMap::number_of_buckets in C++ do not match");
  static_assert(kPaddingOffset == offsetof(SmallOrderedHashMap, padding_),
                "Value of SmallOrderedHashMap::kPaddingOffset defined in Torque and offset of field SmallOrderedHashMap::padding in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=98&c=1
class TorqueGeneratedSmallOrderedNameDictionaryAsserts {
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=100&c=3
  static constexpr int kHashOffset = sizeof(SmallOrderedHashTable);
  static constexpr int kHashOffsetEnd = kHashOffset + kInt32Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=102&c=31
  static constexpr int kPadding0Offset = kHashOffsetEnd + 1;
  static constexpr int kPadding0OffsetEnd = kPadding0Offset + 0 - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=103&c=3
  static constexpr int kNumberOfElementsOffset = kPadding0OffsetEnd + 1;
  static constexpr int kNumberOfElementsOffsetEnd = kNumberOfElementsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=104&c=3
  static constexpr int kNumberOfDeletedElementsOffset = kNumberOfElementsOffsetEnd + 1;
  static constexpr int kNumberOfDeletedElementsOffsetEnd = kNumberOfDeletedElementsOffset + kUInt8Size - 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=105&c=9
  static constexpr int kNumberOfBucketsOffset = kNumberOfDeletedElementsOffsetEnd + 1;
  static constexpr int kNumberOfBucketsOffsetEnd = kNumberOfBucketsOffset + kUInt8Size - 1;
  static constexpr int kHeaderSize = kNumberOfBucketsOffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=107&c=31
  static constexpr int kPadding1Offset = kNumberOfBucketsOffsetEnd + 1;
  static constexpr int kPadding1OffsetEnd = kPadding1Offset + (1 * kUInt8Size) - 1;
  static constexpr int kStartOfStrongFieldsOffset = kPadding1OffsetEnd + 1;
  // https://crsrc.org/c/v8/src/objects/ordered-hash-table.tq?l=108&c=3
  static constexpr int kDataTableOffset = kPadding1OffsetEnd + 1;
  static constexpr int kDataTableOffsetEnd = kDataTableOffset + 0 - 1;
  static constexpr int kEndOfStrongFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kDataTableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kDataTableOffsetEnd + 1;

  static_assert(kHashOffset == offsetof(SmallOrderedNameDictionary, hash_),
                "Value of SmallOrderedNameDictionary::kHashOffset defined in Torque and offset of field SmallOrderedNameDictionary::hash in C++ do not match");
  static_assert(kPadding0Offset == offsetof(SmallOrderedNameDictionary, padding_0_),
                "Value of SmallOrderedNameDictionary::kPadding0Offset defined in Torque and offset of field SmallOrderedNameDictionary::padding_0 in C++ do not match");
  static_assert(kNumberOfElementsOffset == offsetof(SmallOrderedNameDictionary, number_of_elements_),
                "Value of SmallOrderedNameDictionary::kNumberOfElementsOffset defined in Torque and offset of field SmallOrderedNameDictionary::number_of_elements in C++ do not match");
  static_assert(kNumberOfDeletedElementsOffset == offsetof(SmallOrderedNameDictionary, number_of_deleted_elements_),
                "Value of SmallOrderedNameDictionary::kNumberOfDeletedElementsOffset defined in Torque and offset of field SmallOrderedNameDictionary::number_of_deleted_elements in C++ do not match");
  static_assert(kNumberOfBucketsOffset == offsetof(SmallOrderedNameDictionary, number_of_buckets_),
                "Value of SmallOrderedNameDictionary::kNumberOfBucketsOffset defined in Torque and offset of field SmallOrderedNameDictionary::number_of_buckets in C++ do not match");
  static_assert(kPadding1Offset == offsetof(SmallOrderedNameDictionary, padding_1_),
                "Value of SmallOrderedNameDictionary::kPadding1Offset defined in Torque and offset of field SmallOrderedNameDictionary::padding_1 in C++ do not match");
};

} // namespace internal
} // namespace v8
