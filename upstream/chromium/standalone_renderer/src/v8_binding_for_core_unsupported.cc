// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 does not enable Blink's JavaScript binding runtime. These helpers
// satisfy core DOM references to binding context conversion APIs while keeping
// script execution entry points inert.

#include "third_party/blink/renderer/bindings/core/v8/v8_binding_for_core.h"

namespace blink {

v8::Isolate* ToIsolate(const LocalFrame*) {
  return v8::Isolate::TryGetCurrent();
}

LocalDOMWindow* ToLocalDOMWindow(const ScriptState*) {
  return nullptr;
}

ExecutionContext* ToExecutionContext(const ScriptState*) {
  return nullptr;
}

LocalDOMWindow* ToLocalDOMWindow(v8::Local<v8::Context>) {
  return nullptr;
}

LocalDOMWindow* EnteredDOMWindow(v8::Isolate*) {
  return nullptr;
}

LocalDOMWindow* IncumbentDOMWindow(v8::Isolate*) {
  return nullptr;
}

LocalDOMWindow* CurrentDOMWindow(v8::Isolate*) {
  return nullptr;
}

ExecutionContext* ToExecutionContext(v8::Local<v8::Context>) {
  return nullptr;
}

ExecutionContext* CurrentExecutionContext(v8::Isolate*) {
  return nullptr;
}

v8::Local<v8::Context> ToV8Context(ExecutionContext*, DOMWrapperWorld&) {
  return v8::Local<v8::Context>();
}

v8::Local<v8::Context> ToV8Context(LocalFrame*, DOMWrapperWorld&) {
  return v8::Local<v8::Context>();
}

v8::Local<v8::Context> ToV8ContextEvenIfDetached(LocalFrame*,
                                                 DOMWrapperWorld&) {
  return v8::Local<v8::Context>();
}

v8::Local<v8::Context> ToV8ContextMaybeEmpty(LocalFrame*,
                                             DOMWrapperWorld&) {
  return v8::Local<v8::Context>();
}

ScriptState* ToScriptState(ExecutionContext*, DOMWrapperWorld&) {
  return nullptr;
}

ScriptState* ToScriptState(LocalFrame*, DOMWrapperWorld&) {
  return nullptr;
}

ScriptState* ToScriptStateForMainWorld(ExecutionContext*) {
  return nullptr;
}

ScriptState* ToScriptStateForMainWorld(LocalFrame*) {
  return nullptr;
}

LocalFrame* ToLocalFrameIfNotDetached(v8::Local<v8::Context>) {
  return nullptr;
}

v8::MicrotaskQueue* ToMicrotaskQueue(ExecutionContext*) {
  return nullptr;
}

v8::MicrotaskQueue* ToMicrotaskQueue(ScriptState*) {
  return nullptr;
}

bool IsInParallelAlgorithmRunnable(ExecutionContext*, ScriptState*) {
  return false;
}

}  // namespace blink
