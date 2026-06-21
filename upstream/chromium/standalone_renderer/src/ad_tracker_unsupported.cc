// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 does not enable ad-script stack inspection or DevTools ad tracking.
// Keep the Blink shape inert so rendering code can ask for ad provenance
// without pulling V8 stack/debugger runtime.

#include "third_party/blink/renderer/core/ad_tracker/ad_tracker.h"

#include <utility>

namespace blink {

AdScriptIdentifier::AdScriptIdentifier()
    : context_id(), id(kEmptyId), name() {}

AdScriptIdentifier::AdScriptIdentifier(
    const v8_inspector::V8DebuggerId& context_id,
    V8ScriptId id,
    String name)
    : context_id(context_id), id(id), name(std::move(name)) {}

bool AdScriptIdentifier::operator==(const AdScriptIdentifier& other) const {
  return context_id.pair() == other.context_id.pair() && id == other.id;
}

String AdTracker::AdScriptAncestry::ToString() const {
  return String();
}

AdTracker* AdTracker::FromExecutionContext(ExecutionContext*) {
  return nullptr;
}

bool AdTracker::IsAdScriptExecutingInDocument(Document*, StackType) {
  return false;
}

AdTracker::AdTracker(LocalFrame* local_root) : local_root_(local_root) {}

AdTracker::~AdTracker() = default;

void AdTracker::Shutdown() {
  local_root_ = nullptr;
  async_script_stack_.clear();
  context_known_ad_scripts_.clear();
  ad_script_data_.clear();
  ad_monkey_patch_calls_in_scope_.clear();
  bottom_most_ad_script_.reset();
  running_sync_tasks_ = 0;
}

void AdTracker::Will(const probe::ExecuteScript&) {}

void AdTracker::Did(const probe::ExecuteScript&) {}

void AdTracker::Will(const probe::CallFunction&) {}

void AdTracker::Did(const probe::CallFunction&) {}

std::optional<AdProvenance> AdTracker::CalculateIfAdSubresource(
    ExecutionContext*,
    const KURL&,
    ResourceType,
    const FetchInitiatorInfo&,
    std::optional<AdProvenance> known_ad_provenance,
    bool) {
  return known_ad_provenance;
}

AdTracker::AdScriptAncestry AdTracker::GetAncestry(V8ScriptId) {
  return AdScriptAncestry();
}

void AdTracker::DidCreateAsyncTask(probe::AsyncTaskContext*) {}

void AdTracker::DidStartAsyncTask(probe::AsyncTaskContext*) {}

void AdTracker::DidFinishAsyncTask(probe::AsyncTaskContext*) {}

void AdTracker::RegisterAdScript(
    v8::Local<v8::Context>,
    V8ScriptId,
    const std::optional<AdScriptIdentifier>&) {}

bool AdTracker::IsAdScriptInStack(StackType,
                                  MonkeyPatchableApi,
                                  AdScriptAncestry*) {
  return false;
}

void AdTracker::Trace(Visitor*) const {}

}  // namespace blink
