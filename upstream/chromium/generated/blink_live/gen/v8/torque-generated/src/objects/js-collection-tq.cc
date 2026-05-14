#include "src/objects/js-collection.h"

namespace v8 {
namespace internal {

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=5&c=1
class TorqueGeneratedJSCollectionAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-collection.tq?l=11&c=3
  static constexpr int kTableOffset = sizeof(JSObject);
  static constexpr int kTableOffsetEnd = kTableOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kTableOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kTableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kTableOffsetEnd + 1;
  static constexpr int kHeaderSize = kTableOffsetEnd + 1;

  static_assert(kTableOffset == offsetof(JSCollection, table_),
                "Value of JSCollection::kTableOffset defined in Torque and offset of field JSCollection::table in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=13&c=1
class TorqueGeneratedJSSetAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSCollection);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSCollection);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSCollection);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSCollection);
  static constexpr int kHeaderSize = sizeof(JSCollection);

};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=15&c=1
class TorqueGeneratedJSMapAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSCollection);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSCollection);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSCollection);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSCollection);
  static constexpr int kHeaderSize = sizeof(JSCollection);

};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=18&c=1
class TorqueGeneratedJSWeakCollectionAsserts {
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSObject);
  // https://crsrc.org/c/v8/src/objects/js-collection.tq?l=22&c=3
  static constexpr int kTableOffset = sizeof(JSObject);
  static constexpr int kTableOffsetEnd = kTableOffset + kTaggedSize - 1;
  static constexpr int kEndOfStrongFieldsOffset = kTableOffsetEnd + 1;
  static constexpr int kStartOfWeakFieldsOffset = kTableOffsetEnd + 1;
  static constexpr int kEndOfWeakFieldsOffset = kTableOffsetEnd + 1;
  static constexpr int kHeaderSize = kTableOffsetEnd + 1;

  static_assert(kTableOffset == offsetof(JSWeakCollection, table_),
                "Value of JSWeakCollection::kTableOffset defined in Torque and offset of field JSWeakCollection::table in C++ do not match");
};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=24&c=1
class TorqueGeneratedJSWeakSetAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kHeaderSize = sizeof(JSWeakCollection);

};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=26&c=1
class TorqueGeneratedJSWeakMapAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSWeakCollection);
  static constexpr int kHeaderSize = sizeof(JSWeakCollection);

};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=29&c=1
class TorqueGeneratedJSMapIteratorAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kHeaderSize = sizeof(JSCollectionIterator);

};

// Definition https://crsrc.org/c/v8/src/objects/js-collection.tq?l=39&c=1
class TorqueGeneratedJSSetIteratorAsserts {
  static constexpr int kStartOfWeakFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kEndOfWeakFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kStartOfStrongFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kEndOfStrongFieldsOffset = sizeof(JSCollectionIterator);
  static constexpr int kHeaderSize = sizeof(JSCollectionIterator);

};

} // namespace internal
} // namespace v8
