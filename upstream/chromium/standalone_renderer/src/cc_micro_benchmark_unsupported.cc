// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "cc/benchmarks/micro_benchmark_controller.h"

#include <memory>
#include <string>
#include <vector>

#include "base/values.h"
#include "cc/benchmarks/micro_benchmark_impl.h"

namespace cc {

// Phase 1 standalone rendering does not expose cc dev microbenchmarks. Keep the
// LayerTreeHost plumbing linkable without importing optional benchmark bodies.
int MicroBenchmarkController::next_id_ = 1;

MicroBenchmarkController::MicroBenchmarkController(LayerTreeHost* host)
    : host_(host) {}

MicroBenchmarkController::~MicroBenchmarkController() = default;

void MicroBenchmarkController::DidUpdateLayers() {}

int MicroBenchmarkController::ScheduleRun(
    const std::string& micro_benchmark_name,
    base::DictValue settings,
    MicroBenchmark::DoneCallback callback) {
  return 0;
}

bool MicroBenchmarkController::SendMessage(int id, base::DictValue message) {
  return false;
}

std::vector<std::unique_ptr<MicroBenchmarkImpl>>
MicroBenchmarkController::CreateImplBenchmarks() const {
  return {};
}

void MicroBenchmarkController::CleanUpFinishedBenchmarks() {}

int MicroBenchmarkController::GetNextIdAndIncrement() {
  return next_id_++;
}

}  // namespace cc
