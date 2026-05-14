// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_BASE_TRACE_EVENT_TRACE_EVENT_H_
#define STANDALONE_RENDERER_STUBS_BASE_TRACE_EVENT_TRACE_EVENT_H_

#include <cstdint>

#include "base/trace_event/common/trace_event_common.h"

namespace base {
namespace trace_event {

template <typename IdType, const char* Category>
class TraceScopedTrackableObject {
 public:
  TraceScopedTrackableObject(const char*, IdType) {}
  TraceScopedTrackableObject(const TraceScopedTrackableObject&) = delete;
  TraceScopedTrackableObject& operator=(const TraceScopedTrackableObject&) =
      delete;
  ~TraceScopedTrackableObject() = default;
};

uint64_t GetNextGlobalTraceId();

inline bool IsCategoryEnabledOnStop(const char*) {
  return false;
}

inline void EmitNamedTrigger(const char*) {}

}  // namespace trace_event
}  // namespace base

#endif  // STANDALONE_RENDERER_STUBS_BASE_TRACE_EVENT_TRACE_EVENT_H_
