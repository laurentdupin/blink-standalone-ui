// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_COLLECTION_SUPPORT_HEAP_HASH_MAP_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_COLLECTION_SUPPORT_HEAP_HASH_MAP_H_

#include "third_party/blink/renderer/platform/bindings/trace_wrapper_v8_reference.h"
#include "third_party/blink/renderer/platform/heap/collection_support/utils.h"
#include "third_party/blink/renderer/platform/heap/forward.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/heap/heap_allocator_impl.h"
#include "third_party/blink/renderer/platform/wtf/hash_map.h"
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"

namespace blink {

template <internal::HeapCollectionType CollectionType,
          typename KeyArg,
          typename MappedArg,
          typename KeyTraitsArg = HashTraits<KeyArg>,
          typename MappedTraitsArg = HashTraits<MappedArg>>
class BasicHeapHashMap;

namespace internal {

template <typename T>
static constexpr bool IsValidNonTraceableHeapHashMapType() {
  return !IsTraceableV<T> && !IsPointerToGarbageCollectedType<T>;
}

template <HeapCollectionType CollectionType,
          typename KeyArg,
          typename MappedArg,
          typename KeyTraitsArg,
          typename MappedTraitsArg>
struct BasicHeapHashMapTypeConstraints {
  constexpr BasicHeapHashMapTypeConstraints() {
    static_assert(std::is_trivially_destructible_v<
                      blink::BasicHeapHashMap<CollectionType,
                                              KeyArg,
                                              MappedArg,
                                              KeyTraitsArg,
                                              MappedTraitsArg>>,
                  "BasicHeapHashMap must be trivially destructible.");
    static_assert(IsTraceableV<KeyArg> || IsTraceableV<MappedArg>,
                  "For hash maps without traceable elements, use HashMap<> "
                  "instead of BasicHeapHashMap<>.");
    static_assert(IsMemberOrWeakMemberType<KeyArg>::value ||
                      IsValidNonTraceableHeapHashMapType<KeyArg>(),
                  "BasicHeapHashMap supports only Member, WeakMember and "
                  "non-traceable types as keys.");
    static_assert(
        IsMemberOrWeakMemberType<MappedArg>::value ||
            IsTraceableV<MappedArg> ||
            IsValidNonTraceableHeapHashMapType<MappedArg>() ||
            IsSubclassOfTemplate<MappedArg, v8::TracedReference>::value,
        "BasicHeapHashMap supports only Member, WeakMember, "
        "TraceWrapperV8Reference, objects with Trace(), and "
        "non-traceable types as values.");
  }
};

}  // namespace internal

template <internal::HeapCollectionType CollectionType,
          typename KeyArg,
          typename MappedArg,
          typename KeyTraitsArg,
          typename MappedTraitsArg>
class EMPTY_BASES BasicHeapHashMap final
    : private internal::BasicHeapHashMapTypeConstraints<CollectionType,
                                                        KeyArg,
                                                        MappedArg,
                                                        KeyTraitsArg,
                                                        MappedTraitsArg>,
      public std::conditional_t<
          CollectionType == internal::HeapCollectionType::kGCed,
          GarbageCollected<BasicHeapHashMap<CollectionType,
                                            KeyArg,
                                            MappedArg,
                                            KeyTraitsArg,
                                            MappedTraitsArg>>,
          internal::DisallowNewBaseForHeapCollections>,
      public HashMap<KeyArg,
                     MappedArg,
                     KeyTraitsArg,
                     MappedTraitsArg,
                     HeapAllocator> {
 public:
  BasicHeapHashMap() = default;

  void Trace(Visitor* visitor) const {
    HashMap<KeyArg, MappedArg, KeyTraitsArg, MappedTraitsArg,
            HeapAllocator>::Trace(visitor);
  }

};

template <typename KeyArg,
          typename MappedArg,
          typename KeyTraitsArg,
          typename MappedTraitsArg>
struct IsDisallowNewTrait<BasicHeapHashMap<
    internal::HeapCollectionType::kDisallowNew,
    KeyArg,
    MappedArg,
    KeyTraitsArg,
    MappedTraitsArg>> : std::true_type {};

// On-stack for in-field version of HashSet for referring to
// GarbageCollected objects.
template <typename KeyArg,
          typename MappedArg,
          typename KeyTraitsArg = HashTraits<KeyArg>,
          typename MappedTraitsArg = HashTraits<MappedArg>>
using HeapHashMap = BasicHeapHashMap<internal::HeapCollectionType::kDisallowNew,
                                     KeyArg,
                                     MappedArg,
                                     KeyTraitsArg,
                                     MappedTraitsArg>;

static_assert(IsDisallowNew<HeapHashMap<int, int>>);
#define COMMA ,
ASSERT_SIZE(HashMap<int COMMA int>, HeapHashMap<int COMMA int>);
#undef COMMA

// GCed version of HashSet for referring to GarbageCollected objects.
template <typename KeyArg,
          typename MappedArg,
          typename KeyTraitsArg = HashTraits<KeyArg>,
          typename MappedTraitsArg = HashTraits<MappedArg>>
using GCedHeapHashMap = BasicHeapHashMap<internal::HeapCollectionType::kGCed,
                                         KeyArg,
                                         MappedArg,
                                         KeyTraitsArg,
                                         MappedTraitsArg>;

static_assert(!IsDisallowNew<GCedHeapHashMap<int, int>>);
#define COMMA ,
ASSERT_SIZE(HashMap<int COMMA int>, GCedHeapHashMap<int COMMA int>);
#undef COMMA

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_COLLECTION_SUPPORT_HEAP_HASH_MAP_H_
