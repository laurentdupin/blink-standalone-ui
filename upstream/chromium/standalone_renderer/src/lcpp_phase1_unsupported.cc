// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// LCPP drives preload/prefetch/preconnect prediction. Phase 1 does not enable
// network prediction or browser preloading, so keep the feature gate disabled.

#include "third_party/blink/public/common/loader/lcp_critical_path_predictor_util.h"

namespace blink {

bool LcppEnabled() {
  return false;
}

void ResetLcppEnabledForTesting() {}

}  // namespace blink
