// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 keeps Blink's JavaScript binding runtime disabled. These definitions
// provide the binding-world value surface needed by core DOM objects without
// installing wrappers, isolated worlds, or script execution support.

#include "third_party/blink/renderer/platform/bindings/dom_wrapper_world.h"

namespace blink {

unsigned DOMWrapperWorld::number_of_non_main_worlds_in_main_thread_ = 0;

namespace {

DOMWrapperWorld*& InertMainWorldSlot() {
  static DOMWrapperWorld* world = nullptr;
  return world;
}

}  // namespace

DOMWrapperWorld::DOMWrapperWorld(PassKey,
                                 v8::Isolate* isolate,
                                 WorldType world_type,
                                 int32_t world_id,
                                 bool)
    : world_type_(world_type),
      world_id_(world_id),
      dom_data_store_(nullptr),
      isolate_(isolate) {}

DOMWrapperWorld::~DOMWrapperWorld() = default;

DOMWrapperWorld& DOMWrapperWorld::MainWorld(v8::Isolate* isolate) {
  DOMWrapperWorld*& world = InertMainWorldSlot();
  if (!world) {
    world = MakeGarbageCollected<DOMWrapperWorld>(
        PassKey(), isolate, WorldType::kMain, kMainWorldId,
        /*is_default_world_of_isolate=*/true);
  }
  return *world;
}

DOMWrapperWorld* DOMWrapperWorld::EnsureIsolatedWorld(v8::Isolate* isolate,
                                                      int32_t) {
  return &MainWorld(isolate);
}

void DOMWrapperWorld::Trace(Visitor*) const {}

}  // namespace blink
