// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/profiler/thread_group_profiler.h"
#include "base/profiler/thread_group_profiler_client.h"

#include <memory>
#include <utility>

namespace base {

// Optional thread-pool stack sampling is unsupported in the standalone
// renderer Phase 1 cc build. Keep the public hooks inert so active base task
// runtime can link without reopening the stack sampler/profiler closure.
void ThreadGroupProfiler::SetClient(
    std::unique_ptr<ThreadGroupProfilerClient>) {}

bool ThreadGroupProfiler::IsProfilingEnabled() {
  return false;
}

ThreadGroupProfiler::ThreadGroupProfiler(
    scoped_refptr<SequencedTaskRunner> task_runner,
    int64_t thread_group_type,
    std::unique_ptr<PeriodicSamplingScheduler> periodic_sampling_scheduler,
    ProfilerFactory profiler_factory)
    : thread_group_type_(thread_group_type),
      periodic_sampling_scheduler_(std::move(periodic_sampling_scheduler)),
      task_runner_(std::move(task_runner)),
      stack_sampling_profiler_factory_(std::move(profiler_factory)) {}

ThreadGroupProfiler::~ThreadGroupProfiler() = default;

ThreadGroupProfiler::ActiveCollection::~ActiveCollection() = default;

void ThreadGroupProfiler::Shutdown() {}

void ThreadGroupProfiler::OnWorkerThreadStarted(
    internal::WorkerThread*) {}

void ThreadGroupProfiler::OnWorkerThreadActive(
    internal::WorkerThread*) {}

void ThreadGroupProfiler::OnWorkerThreadIdle(
    internal::WorkerThread*) {}

void ThreadGroupProfiler::OnWorkerThreadExiting(
    internal::WorkerThread*) {}

ThreadGroupProfiler::ProfilerFactory
ThreadGroupProfiler::GetDefaultProfilerFactory() {
  return ProfilerFactory();
}

}  // namespace base
