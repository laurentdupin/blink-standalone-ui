// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 keeps memory-pressure state inert. The full Blink owner initializes
// device-memory and feature state that is outside this rendering-only build.

#include "third_party/blink/renderer/platform/instrumentation/memory_pressure_listener.h"

namespace blink {

bool MemoryPressureListenerRegistry::is_low_end_device_ = false;

bool MemoryPressureListenerRegistry::IsLowEndDevice() {
  return is_low_end_device_;
}

bool MemoryPressureListenerRegistry::IsLowEndDeviceOrPartialLowEndModeEnabled() {
  return is_low_end_device_;
}

bool MemoryPressureListenerRegistry::
    IsLowEndDeviceOrPartialLowEndModeEnabledIncludingCanvasFontCache() {
  return is_low_end_device_;
}

void MemoryPressureListenerRegistry::Initialize() {
  is_low_end_device_ = false;
}

void MemoryPressureListenerRegistry::SetIsLowEndDeviceForTesting(
    bool is_low_end_device) {
  is_low_end_device_ = is_low_end_device;
}

}  // namespace blink
