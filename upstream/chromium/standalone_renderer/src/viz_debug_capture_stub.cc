// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "components/viz/service/display_embedder/skia_output_surface_impl_on_gpu_debug_capture.h"

namespace gpu {
class SharedContextState;
class SharedImageRepresentationFactory;
}  // namespace gpu

namespace viz {

void AttemptDebuggerBufferCapture(
    ImageContextImpl*,
    gpu::SharedContextState*,
    gpu::SharedImageRepresentationFactory*) {}

}  // namespace viz
