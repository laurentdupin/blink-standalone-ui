// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <cstdio>
#include <optional>

#include "base/at_exit.h"
#include "base/memory/raw_ptr.h"
#include "base/run_loop.h"
#include "base/task/single_thread_task_executor.h"
#include "components/viz/common/frame_sinks/begin_frame_args.h"
#include "components/viz/common/quads/compositor_frame.h"
#include "components/viz/common/surfaces/local_surface_id.h"
#include "mojo/core/embedder/embedder.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"
#include "services/viz/public/mojom/compositing/compositor_frame_sink.mojom.h"
#include "services/viz/public/mojom/compositing/layer_context.mojom.h"

namespace {
class FrameSinkReceiver final : public viz::mojom::CompositorFrameSink {
 public:
  explicit FrameSinkReceiver(base::RunLoop* run_loop) : run_loop_(run_loop) {}
  void SetParams(viz::mojom::CompositorFrameSinkParamsPtr) override {}
  void SetNeedsBeginFrame(bool needs_begin_frame) override {
    received_needs_begin_frame_ = needs_begin_frame;
    run_loop_->Quit();
  }
  void SubmitCompositorFrame(const viz::LocalSurfaceId&, viz::CompositorFrame,
                             std::optional<viz::HitTestRegionList>, uint64_t) override {}
  void DidNotProduceFrame(const viz::BeginFrameAck&) override {}
  void NotifyNewLocalSurfaceIdExpectedWhilePaused() override {}
  void BindLayerContext(viz::mojom::PendingLayerContextPtr,
                        viz::mojom::LayerContextSettingsPtr) override {}
  bool received_needs_begin_frame() const { return received_needs_begin_frame_; }
 private:
  raw_ptr<base::RunLoop> run_loop_;
  bool received_needs_begin_frame_ = false;
};
int Fail(const char* message) {
  std::fprintf(stderr, "static_mojo_core_smoke: failed %s\n", message);
  return 1;
}
}  // namespace

int main() {
  base::AtExitManager at_exit;
  base::SingleThreadTaskExecutor executor(base::MessagePumpType::DEFAULT);
  mojo::core::Init();
  base::RunLoop run_loop;
  FrameSinkReceiver implementation(&run_loop);
  mojo::PendingRemote<viz::mojom::CompositorFrameSink> pending_remote;
  mojo::Receiver<viz::mojom::CompositorFrameSink> receiver(
      &implementation, pending_remote.InitWithNewPipeAndPassReceiver());
  mojo::Remote<viz::mojom::CompositorFrameSink> remote(std::move(pending_remote));
  if (!remote.is_bound() || !receiver.is_bound()) return Fail("normal_mojo_endpoint_not_bound");
  remote->SetNeedsBeginFrame(true);
  run_loop.Run();
  if (!implementation.received_needs_begin_frame()) return Fail("remote_receiver_round_trip");
  remote.reset();
  receiver.reset();
  std::puts("static_mojo_core_smoke: passed");
  return 0;
}
