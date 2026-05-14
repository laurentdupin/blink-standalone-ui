// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_TIMING_WORKER_GLOBAL_SCOPE_PERFORMANCE_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_TIMING_WORKER_GLOBAL_SCOPE_PERFORMANCE_H_

namespace blink {

class Performance;
class WorkerGlobalScope;

class WorkerGlobalScopePerformance {
 public:
  static Performance* performance(WorkerGlobalScope&) { return nullptr; }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_TIMING_WORKER_GLOBAL_SCOPE_PERFORMANCE_H_
