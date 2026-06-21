// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "services/viz/public/cpp/compositing/copy_output_request_mojom_traits.h"

#include <memory>

#include "base/check.h"
#include "base/synchronization/lock.h"
#include "components/viz/common/gpu/raster_context_provider.h"

namespace viz {
namespace {

base::Lock& UnsupportedRasterContextLock() {
  static base::Lock lock;
  return lock;
}

}  // namespace

RasterContextProvider::ScopedRasterContextLock::ScopedRasterContextLock(
    RasterContextProvider* context_provider,
    const char* url)
    : context_provider_(context_provider),
      context_lock_(UnsupportedRasterContextLock()) {
  CHECK(false) << "Raster context access is a Phase 3 GPU runtime boundary";
}

RasterContextProvider::ScopedRasterContextLock::~ScopedRasterContextLock() =
    default;

}  // namespace viz

namespace mojo {

// Copy-output IPC is a Viz service/runtime feature. Phase 1 only needs the
// generated cc/Viz data vocabulary to compile, so requests deserialize as
// unsupported and cannot produce result sender remotes.
mojo::PendingRemote<viz::mojom::CopyOutputResultSender>
StructTraits<viz::mojom::CopyOutputRequestDataView,
             std::unique_ptr<viz::CopyOutputRequest>>::
    result_sender(const std::unique_ptr<viz::CopyOutputRequest>& request) {
  return {};
}

bool StructTraits<viz::mojom::CopyOutputRequestDataView,
                  std::unique_ptr<viz::CopyOutputRequest>>::
    Read(viz::mojom::CopyOutputRequestDataView data,
         std::unique_ptr<viz::CopyOutputRequest>* out_p) {
  out_p->reset();
  return false;
}

}  // namespace mojo
