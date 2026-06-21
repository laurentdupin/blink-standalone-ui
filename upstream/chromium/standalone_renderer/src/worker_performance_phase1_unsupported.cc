// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Workers are outside the Phase 1 compositor/static-rendering target. Keep the
// worker performance surface inert while leaving the window performance path to
// its existing owner.

#include "third_party/blink/renderer/core/timing/global_performance.h"

namespace blink {

WorkerPerformance* GlobalPerformance::performance(WorkerGlobalScope&) {
  return nullptr;
}

}  // namespace blink
