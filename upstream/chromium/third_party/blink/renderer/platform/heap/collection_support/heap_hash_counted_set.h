// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_COLLECTION_SUPPORT_HEAP_HASH_COUNTED_SET_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_COLLECTION_SUPPORT_HEAP_HASH_COUNTED_SET_H_

#include "third_party/blink/renderer/platform/heap/collection_support/utils.h"
#include "third_party/blink/renderer/platform/heap/forward.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/heap/heap_allocator_impl.h"
#include "third_party/blink/renderer/platform/wtf/hash_counted_set.h"
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"

namespace blink {

template <internal::HeapCollectionType CollectionType,
          typename Value,
          typename Traits = HashTraits<Value>>
class BasicHeapHashCountedSet;

namespace internal {

template <HeapCollectionType CollectionType, typename Value, typename Traits>
struct BasicHeapHashCountedSetTypeConstraints {
  constexpr BasicHeapHashCountedSetTypeConstraints() {
    static_assert(IsMemberOrWeakMemberType<Value>::value,
                  "HeapHashCountedSet supports only Member and WeakMember.");
    static_assert(std::is_trivially_destructible<
                      blink::BasicHeapHashCountedSet<CollectionType,
                                                     Value,
                                                     Traits>>::value,
                  "HeapHashCountedSet must be trivially destructible.");
    static_assert(IsTraceableV<Value>,
                  "For counted sets without traceable elements, use "
                  "HashCountedSet<> instead of HeapHashCountedSet<>.");
  }
};

}  // namespace internal

template <internal::HeapCollectionType CollectionType,
          typename Value,
          typename Traits>
class EMPTY_BASES BasicHeapHashCountedSet final
    : private internal::BasicHeapHashCountedSetTypeConstraints<CollectionType,
                                                               Value,
                                                               Traits>,
      public std::conditional_t<
          CollectionType == internal::HeapCollectionType::kGCed,
          GarbageCollected<
              BasicHeapHashCountedSet<CollectionType, Value, Traits>>,
          internal::DisallowNewBaseForHeapCollections>,
      public HashCountedSet<Value, Traits, HeapAllocator> {
 public:
  BasicHeapHashCountedSet() = default;

  void Trace(Visitor* visitor) const {
    HashCountedSet<Value, Traits, HeapAllocator>::Trace(visitor);
  }

};

template <typename T, typename Traits>
struct IsDisallowNewTrait<BasicHeapHashCountedSet<
    internal::HeapCollectionType::kDisallowNew,
    T,
    Traits>> : std::true_type {};

// On-stack for in-field version of HashCountedSet for referring to
// GarbageCollected or DISALLOW_NEW() objects with Trace() methods.
template <typename T, typename Traits = HashTraits<T>>
using HeapHashCountedSet =
    BasicHeapHashCountedSet<internal::HeapCollectionType::kDisallowNew,
                            T,
                            Traits>;

static_assert(IsDisallowNew<HeapHashCountedSet<int>>);
ASSERT_SIZE(HashCountedSet<int>, HeapHashCountedSet<int>);

// GCed version of HashCountedSet for referring to GarbageCollected or
// DISALLOW_NEW() objects with Trace() methods.
template <typename T, typename Traits = HashTraits<T>>
using GCedHeapHashCountedSet =
    BasicHeapHashCountedSet<internal::HeapCollectionType::kGCed, T, Traits>;

static_assert(!IsDisallowNew<GCedHeapHashCountedSet<int>>);
ASSERT_SIZE(HashCountedSet<int>, GCedHeapHashCountedSet<int>);

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_HEAP_COLLECTION_SUPPORT_HEAP_HASH_COUNTED_SET_H_
