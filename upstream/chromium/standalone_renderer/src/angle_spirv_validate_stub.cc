// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "common/spirv/spirv_types.h"

namespace angle::spirv {

bool Validate(const Blob&) {
  // Standalone release builds only reference this from ANGLE ASSERT paths.
  // Avoid depending on SPIRV-Tools in the embeddable runtime package.
  return false;
}

void Print(const Blob&) {}

}  // namespace angle::spirv
