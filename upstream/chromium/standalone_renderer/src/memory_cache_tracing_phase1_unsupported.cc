// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Memory-cache dumping and forced GC are tracing/testing facilities. Keep them
// inert in Phase 1 instead of importing Blink GC tracing runtime.

#include "third_party/blink/renderer/platform/heap/thread_state.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/memory_cache_dump_provider.h"

namespace blink {

void ThreadState::CollectAllGarbageForTesting(StackState) {}

void MemoryCacheDumpClient::Trace(Visitor*) const {}

MemoryCacheDumpProvider* MemoryCacheDumpProvider::Instance() {
  static MemoryCacheDumpProvider instance;
  return &instance;
}

bool MemoryCacheDumpProvider::OnMemoryDump(
    const base::trace_event::MemoryDumpArgs&,
    base::trace_event::ProcessMemoryDump*) {
  return false;
}

MemoryCacheDumpProvider::MemoryCacheDumpProvider() = default;

MemoryCacheDumpProvider::~MemoryCacheDumpProvider() = default;

}  // namespace blink
