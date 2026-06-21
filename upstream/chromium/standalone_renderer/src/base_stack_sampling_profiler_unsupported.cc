// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/profiler/stack_sampling_profiler.h"

namespace base {

void StackSamplingProfiler::ApplyMetadataToPastSamples(
    TimeTicks,
    TimeTicks,
    uint64_t,
    std::optional<int64_t>,
    int64_t,
    std::optional<PlatformThreadId>) {}

void StackSamplingProfiler::AddProfileMetadata(
    uint64_t,
    std::optional<int64_t>,
    int64_t,
    std::optional<PlatformThreadId>) {}

}  // namespace base
