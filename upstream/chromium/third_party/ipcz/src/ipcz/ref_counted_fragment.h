// Copyright 2022 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef IPCZ_SRC_IPCZ_REF_COUNTED_FRAGMENT_H_
#define IPCZ_SRC_IPCZ_REF_COUNTED_FRAGMENT_H_

#include <atomic>

#include "ipcz/ipcz.h"
#include "util/ref_counted.h"

namespace ipcz {

// A RefCountedFragment is an object allocated within a shared Fragment from
// NodeLinkMemory, and which is automatially freed when its last reference is
// released. Consumers can hold onto references to RefCountedFragment objects
// by holding a FragmentRef.
struct IPCZ_ALIGN(4) RefCountedFragment {
  enum { kUnmanagedRef };

  RefCountedFragment();

  int32_t ref_count_for_testing() const {
    return std::atomic_ref<int32_t>(const_cast<int32_t&>(ref_count_))
        .load(std::memory_order_relaxed);
  }

  // Increments the reference count for this object.
  void AddRef();

  // Releases a reference and returns the previous reference count. If this
  // returns 1, the underlying Fragment can be safely freed.
  int32_t ReleaseRef();

 private:
  // This may live in shared memory. MSVC's std::atomic is not trivially
  // copyable, so keep its storage trivial and construct an atomic_ref only for
  // the individual interprocess operations.
  int32_t ref_count_{1};
};

static_assert(std::is_trivially_copyable_v<RefCountedFragment>);
static_assert(alignof(RefCountedFragment) >= alignof(int32_t));

}  // namespace ipcz

#endif  // IPCZ_SRC_IPCZ_REF_COUNTED_FRAGMENT_H_
