#include "src/objects/js-collection-iterator.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-collection-iterator.tq?l=5&c=1
class TorqueGeneratedJSCollectionIteratorAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-collection-iterator.tq?l=9&c=3
  static constexpr int kTableOffset = sizeof(JSObject);
  static constexpr int kTableOffsetEnd = kTableOffset + kTaggedSize - 1;
  // https://crsrc.org/c/v8/src/objects/js-collection-iterator.tq?l=11&c=3
  static constexpr int kIndexOffset = kTableOffsetEnd + 1;
  static constexpr int kIndexOffsetEnd = kIndexOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kIndexOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kIndexOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kIndexOffsetEnd + 1;
  static constexpr int kHeaderSize = kIndexOffsetEnd + 1;

  static_assert(kTableOffset == offsetof(JSCollectionIterator, table_),
                "Value of JSCollectionIterator::kTableOffset defined in Torque and offset of field JSCollectionIterator::table in C++ do not match");
  static_assert(kIndexOffset == offsetof(JSCollectionIterator, index_),
                "Value of JSCollectionIterator::kIndexOffset defined in Torque and offset of field JSCollectionIterator::index in C++ do not match");
};

} // namespace internal
} // namespace v8
