// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gfx/win/d3d_shared_fence.h"

namespace gfx {

// Phase 3 compile boundary only. Real D3D/Vulkan shared-fence creation,
// signaling, and waiting belong to the GPU/Vulkan integration phase.
D3DSharedFence::~D3DSharedFence() = default;

}  // namespace gfx
