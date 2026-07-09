// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "standalone_renderer/tools/frame_sink_probe/chromium_frame_sink_probe.h"

#include <algorithm>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "base/containers/flat_map.h"
#include "base/functional/bind.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/run_loop.h"
#include "base/task/sequenced_task_runner.h"
#include "base/task/single_thread_task_runner.h"
#include "base/timer/timer.h"
#ifndef BLINK_STANDALONE_FRAME_SINK_ASYNC_PROOF
#define BLINK_STANDALONE_FRAME_SINK_ASYNC_PROOF 0
#endif
#if BLINK_STANDALONE_FRAME_SINK_ASYNC_PROOF
#include "cc/mojo_embedder/async_layer_tree_frame_sink.h"
#include "cc/trees/layer_tree_frame_sink_client.h"
#endif
#include "components/viz/common/frame_sinks/begin_frame_args.h"
#include "components/viz/common/frame_sinks/copy_output_request.h"
#include "components/viz/common/frame_sinks/copy_output_result.h"
#include "components/viz/common/frame_timing_details_map.h"
#include "components/viz/common/quads/compositor_frame.h"
#include "components/viz/common/quads/compositor_render_pass.h"
#include "components/viz/common/quads/shared_quad_state.h"
#include "components/viz/common/quads/solid_color_draw_quad.h"
#include "components/viz/common/resources/returned_resource.h"
#include "components/viz/common/surfaces/frame_sink_id.h"
#include "components/viz/common/surfaces/parent_local_surface_id_allocator.h"
#include "components/viz/common/surfaces/surface_id.h"
#include "components/viz/common/viz_utils.h"
#include "components/viz/service/display/display_compositor_memory_and_task_controller.h"
#include "components/viz/service/display/output_surface.h"
#include "components/viz/service/display/output_surface_client.h"
#include "components/viz/service/display/output_surface_frame.h"
#include "components/viz/service/display/software_output_device.h"
#include "components/viz/service/display_embedder/output_surface_provider.h"
#include "components/viz/service/frame_sinks/frame_sink_manager_impl.h"
#include "components/viz/service/frame_sinks/root_compositor_frame_sink_impl.h"
#include "gpu/command_buffer/common/swap_buffers_complete_params.h"
#include "gpu/ipc/common/surface_handle.h"
#include "mojo/core/embedder/configuration.h"
#include "mojo/core/embedder/embedder.h"
#include "mojo/core/embedder/scoped_ipc_support.h"
#include "mojo/public/cpp/bindings/associated_remote.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "services/viz/public/mojom/compositing/compositor_frame_sink.mojom.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/gpu_fence_handle.h"
#include "ui/gfx/presentation_feedback.h"
#include "ui/gfx/swap_result.h"

namespace html_css_renderer {
namespace {

void InstallMojoCoreForFrameSinkProbe() {
  static bool installed = false;
  if (installed) {
    return;
  }

  mojo::core::Configuration configuration;
  configuration.disable_ipcz = true;
  configuration.is_broker_process = true;
  mojo::core::Init(configuration);
  static auto* ipc_support = new mojo::core::ScopedIPCSupport(
      base::SingleThreadTaskRunner::GetCurrentDefault(),
      mojo::core::ScopedIPCSupport::ShutdownPolicy::FAST);
  (void)ipc_support;
  installed = true;
}

std::string EscapeJson(const std::string& value) {
  std::string escaped;
  escaped.reserve(value.size());
  for (char c : value) {
    switch (c) {
      case '\\':
        escaped += "\\\\";
        break;
      case '"':
        escaped += "\\\"";
        break;
      case '\n':
        escaped += "\\n";
        break;
      case '\r':
        escaped += "\\r";
        break;
      case '\t':
        escaped += "\\t";
        break;
      default:
        escaped.push_back(c);
        break;
    }
  }
  return escaped;
}

const char* CopyOutputErrorName(viz::CopyOutputResult::Error error) {
  switch (error) {
    case viz::CopyOutputResult::Error::kNone:
      return "none";
    case viz::CopyOutputResult::Error::kUnknown:
      return "unknown";
    case viz::CopyOutputResult::Error::kTimeout:
      return "timeout";
    case viz::CopyOutputResult::Error::kEmbeddingTokenChanged:
      return "embedding_token_changed";
  }
  return "unrecognized";
}

class ProofSoftwareOutputSurface final : public viz::OutputSurface {
 public:
  ProofSoftwareOutputSurface()
      : viz::OutputSurface(std::make_unique<viz::SoftwareOutputDevice>()) {}

  ProofSoftwareOutputSurface(const ProofSoftwareOutputSurface&) = delete;
  ProofSoftwareOutputSurface& operator=(const ProofSoftwareOutputSurface&) =
      delete;

  ~ProofSoftwareOutputSurface() override = default;

  void BindToClient(viz::OutputSurfaceClient* client) override {
    client_ = client;
  }

  void EnsureBackbuffer() override {}
  void DiscardBackbuffer() override {}

  void Reshape(const ReshapeParams& params) override {
    software_device()->Resize(params.size, params.device_scale_factor);
  }

  void SwapBuffers(viz::OutputSurfaceFrame frame) override {
    base::SingleThreadTaskRunner::GetCurrentDefault()->PostTask(
        FROM_HERE,
        base::BindOnce(&ProofSoftwareOutputSurface::AckSwap,
                       weak_factory_.GetWeakPtr()));
  }

  void SetUpdateVSyncParametersCallback(
      viz::UpdateVSyncParametersCallback callback) override {}

  void SetDisplayTransformHint(gfx::OverlayTransform transform) override {}

  gfx::OverlayTransform GetDisplayTransform() override {
    return gfx::OVERLAY_TRANSFORM_NONE;
  }

 private:
  void AckSwap() {
    if (!client_) {
      return;
    }
    const base::TimeTicks now = base::TimeTicks::Now();
    gpu::SwapBuffersCompleteParams params;
    params.swap_response.timings = {now, now};
    params.swap_response.result = gfx::SwapResult::SWAP_ACK;
    client_->DidReceiveSwapBuffersAck(std::move(params),
                                      gfx::GpuFenceHandle());
    client_->DidReceivePresentationFeedback({now, base::TimeDelta(), 0});
  }

  raw_ptr<viz::OutputSurfaceClient> client_ = nullptr;
  base::WeakPtrFactory<ProofSoftwareOutputSurface> weak_factory_{this};
};

class ProofSoftwareOutputSurfaceProvider final
    : public viz::OutputSurfaceProvider {
 public:
  ProofSoftwareOutputSurfaceProvider() = default;
  ProofSoftwareOutputSurfaceProvider(const ProofSoftwareOutputSurfaceProvider&) =
      delete;
  ProofSoftwareOutputSurfaceProvider& operator=(
      const ProofSoftwareOutputSurfaceProvider&) = delete;
  ~ProofSoftwareOutputSurfaceProvider() override = default;

  std::unique_ptr<viz::DisplayCompositorMemoryAndTaskController>
  CreateGpuDependency(bool gpu_compositing,
                      gpu::SurfaceHandle surface_handle) override {
    return nullptr;
  }

  std::unique_ptr<viz::OutputSurface> CreateOutputSurface(
      gpu::SurfaceHandle surface_handle,
      bool gpu_compositing,
      viz::mojom::DisplayClient* display_client,
      viz::DisplayCompositorMemoryAndTaskController* display_controller,
      const viz::RendererSettings& renderer_settings,
      const viz::DebugRendererSettings* debug_settings) override {
    if (gpu_compositing) {
      return nullptr;
    }
    return std::make_unique<ProofSoftwareOutputSurface>();
  }

  gpu::SharedImageManager* GetSharedImageManager() override { return nullptr; }
  gpu::SyncPointManager* GetSyncPointManager() override { return nullptr; }
  gpu::Scheduler* GetGpuScheduler() override { return nullptr; }
};

viz::CompositorFrame BuildSolidColorFrame(const gfx::Size& size,
                                          SkColor4f color,
                                          uint32_t frame_token) {
  viz::CompositorFrame frame;
  frame.metadata.device_scale_factor = 1.0f;
  frame.metadata.page_scale_factor = 1.0f;
  frame.metadata.scrollable_viewport_size = gfx::SizeF(size);
  frame.metadata.visible_viewport_size = size;
  frame.metadata.root_background_color = SkColors::kTransparent;
  frame.metadata.begin_frame_ack =
      viz::BeginFrameAck::CreateManualAckWithDamage();
  frame.metadata.frame_token = frame_token;

  auto render_pass = viz::CompositorRenderPass::Create();
  render_pass->SetNew(viz::CompositorRenderPassId{1}, gfx::Rect(size),
                      gfx::Rect(size), gfx::Transform());
  viz::SharedQuadState* shared_quad_state =
      render_pass->CreateAndAppendSharedQuadState();
  shared_quad_state->SetAll(
      gfx::Transform(), gfx::Rect(size), gfx::Rect(size),
      gfx::MaskFilterInfo(), std::nullopt,
      /*contents_opaque=*/true, /*opacity_f=*/1.0f, SkBlendMode::kSrcOver,
      /*sorting_context=*/0, /*layer_id=*/1,
      /*fast_rounded_corner=*/false);
  auto* quad = render_pass->CreateAndAppendDrawQuad<viz::SolidColorDrawQuad>();
  quad->SetNew(shared_quad_state, gfx::Rect(size), gfx::Rect(size), color,
               /*anti_aliasing_off=*/true);
  frame.render_pass_list.push_back(std::move(render_pass));
  return frame;
}

class CopyWaiter {
 public:
  using RequestCopyCallback = base::RepeatingCallback<void(
      const viz::LocalSurfaceId&,
      std::unique_ptr<viz::CopyOutputRequest>)>;

  bool RequestAndWait(const viz::LocalSurfaceId& local_surface_id,
                      const gfx::Size& size,
                      const char* label,
                      RequestCopyCallback request_copy,
                      base::RepeatingClosure draw_now,
                      std::string* failure_reason) {
    completed_ = false;
    succeeded_ = false;
    pixels_ = 0;
    failure_.clear();

    auto request = std::make_unique<viz::CopyOutputRequest>(
        viz::CopyOutputRequest::ResultFormat::RGBA,
        viz::CopyOutputRequest::ResultDestination::kSystemMemory,
        base::BindOnce(&CopyWaiter::OnCopyOutput, weak_factory_.GetWeakPtr(),
                       std::string(label)));
    viz::SetCopyOutputRequestResultSize(request.get(), gfx::Rect(size), size,
                                        size);
    request->set_result_task_runner(
        base::SequencedTaskRunner::GetCurrentDefault());
    request_copy.Run(local_surface_id, std::move(request));
    draw_now.Run();

    base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
    run_loop_ = &run_loop;
    base::OneShotTimer timeout;
    timeout.Start(FROM_HERE, base::Seconds(5), run_loop.QuitClosure());
    run_loop.Run();
    timeout.Stop();
    run_loop_ = nullptr;

    if (!completed_) {
      *failure_reason = std::string(label) + " CopyOutput did not complete";
      return false;
    }
    if (!succeeded_) {
      *failure_reason = std::string(label) + " " +
                        (failure_.empty() ? "CopyOutput failed" : failure_);
      return false;
    }
    return true;
  }

  int pixels() const { return pixels_; }

 private:
  void OnCopyOutput(std::string label,
                    std::unique_ptr<viz::CopyOutputResult> output) {
    if (!output) {
      failure_ = label + " CopyOutput returned no result";
      Finish(false);
      return;
    }
    if (output->IsEmpty()) {
      failure_ = label + " CopyOutput returned empty result: " +
                 CopyOutputErrorName(output->error());
      Finish(false);
      return;
    }
    if (output->size().IsEmpty()) {
      failure_ = label + " CopyOutput returned an empty size";
      Finish(false);
      return;
    }
    pixels_ += output->size().width() * output->size().height();
    Finish(pixels_ > 0);
  }

  void Finish(bool succeeded) {
    succeeded_ = succeeded;
    completed_ = true;
    if (run_loop_) {
      run_loop_->Quit();
    }
  }

  bool completed_ = false;
  bool succeeded_ = false;
  int pixels_ = 0;
  std::string failure_;
  raw_ptr<base::RunLoop> run_loop_ = nullptr;
  base::WeakPtrFactory<CopyWaiter> weak_factory_{this};
};

class RootFrameSinkProof final : public viz::mojom::CompositorFrameSinkClient {
 public:
  explicit RootFrameSinkProof(const gfx::Size& viewport) : viewport_(viewport) {}
  RootFrameSinkProof(const RootFrameSinkProof&) = delete;
  RootFrameSinkProof& operator=(const RootFrameSinkProof&) = delete;
  ~RootFrameSinkProof() override {
    root_frame_sink_.reset();
    frame_sink_manager_.reset();
  }

  std::string Run() {
    if (!CreateRootFrameSink()) {
      return BuildJson(false);
    }
    if (!SubmitAndCopy(viewport_, SkColors::kBlue, "initial")) {
      return BuildJson(false);
    }
    const gfx::Size resized(std::max(1, viewport_.width() / 2),
                            std::max(1, viewport_.height() / 2));
    if (!SubmitAndCopy(resized, SkColors::kGreen, "resized")) {
      return BuildJson(false);
    }
    return BuildJson(true);
  }

 private:
  bool CreateRootFrameSink() {
    if (!base::SingleThreadTaskRunner::GetCurrentDefault()) {
      failure_reason_ = "root proof requires a current task runner";
      return false;
    }
    frame_sink_manager_ =
        std::make_unique<viz::FrameSinkManagerImpl>(
            viz::FrameSinkManagerImpl::InitParams(&output_surface_provider_));
    frame_sink_manager_->RegisterFrameSinkId(frame_sink_id_,
                                             /*report_activation=*/true);
    frame_sink_manager_->SetFrameSinkDebugLabel(
        frame_sink_id_, "standalone-renderer-root-proof");

    renderer_settings_.dont_round_texture_sizes_for_pixel_tests = true;
    renderer_settings_.requires_alpha_channel = true;

    auto params = viz::mojom::RootCompositorFrameSinkParams::New();
    params->frame_sink_id = frame_sink_id_;
    params->widget = gpu::kNullSurfaceHandle;
    params->gpu_compositing = false;
    params->renderer_settings = renderer_settings_;
    params->compositor_frame_sink =
        compositor_frame_sink_remote_.BindNewEndpointAndPassReceiver();
    params->compositor_frame_sink_client =
        compositor_frame_sink_client_receiver_.BindNewPipeAndPassRemote();
    params->display_private =
        display_private_remote_.BindNewEndpointAndPassReceiver();

    root_frame_sink_ = viz::RootCompositorFrameSinkImpl::Create(
        std::move(params), frame_sink_manager_.get(), &output_surface_provider_,
        viz::BeginFrameSource::kNotRestartableId,
        /*run_all_compositor_stages_before_draw=*/true, &debug_settings_,
        /*hint_session_factory=*/nullptr);
    if (!root_frame_sink_) {
      failure_reason_ = "RootCompositorFrameSinkImpl::Create returned null";
      return false;
    }
    root_frame_sink_->SetDisplayVisible(true);
    root_frame_sink_->Resize(viewport_);
    return true;
  }

  bool SubmitAndCopy(const gfx::Size& size,
                     SkColor4f color,
                     const char* label) {
    surface_id_allocator_.GenerateId();
    const viz::LocalSurfaceId local_surface_id =
        surface_id_allocator_.GetCurrentLocalSurfaceId();
    root_frame_sink_->Resize(size);
    root_frame_sink_->SubmitCompositorFrame(
        local_surface_id, BuildSolidColorFrame(size, color, ++frame_token_),
        std::nullopt, /*submit_time=*/0);
    DrawNow();
    const viz::SurfaceId current_surface_id =
        root_frame_sink_->CurrentSurfaceId();
    if (!current_surface_id.is_valid() ||
        current_surface_id.local_surface_id() != local_surface_id) {
      failure_reason_ = std::string(label) +
                        " did not activate submitted LocalSurfaceId";
      return false;
    }
    return copy_waiter_.RequestAndWait(
        local_surface_id, size, label,
        base::BindRepeating(&RootFrameSinkProof::RequestCopy,
                            weak_factory_.GetWeakPtr()),
        base::BindRepeating(&RootFrameSinkProof::DrawNow,
                            weak_factory_.GetWeakPtr()),
        &failure_reason_);
  }

  void RequestCopy(const viz::LocalSurfaceId& local_surface_id,
                   std::unique_ptr<viz::CopyOutputRequest> request) {
    frame_sink_manager_->RequestCopyOfOutput(
        viz::SurfaceId(frame_sink_id_, local_surface_id), std::move(request),
        /*capture_exact_surface_id=*/true, base::Seconds(5));
  }

  void DrawNow() {
    root_frame_sink_->ForceImmediateDrawAndSwapIfPossible();
    base::RunLoop().RunUntilIdle();
  }

  void DidReceiveCompositorFrameAck(
      std::vector<viz::ReturnedResource> resources) override {
    ++ack_count_;
  }
  void OnBeginFrame(
      const viz::BeginFrameArgs& args,
      const base::flat_map<uint32_t, viz::FrameTimingDetails>& details,
      std::vector<viz::ReturnedResource> resources) override {}
  void OnBeginFramePausedChanged(bool paused) override {}
  void ReclaimResources(std::vector<viz::ReturnedResource> resources) override {}
  void OnCompositorFrameTransitionDirectiveProcessed(
      uint32_t sequence_id) override {}
  void OnSurfaceEvicted(
      const viz::LocalSurfaceId& local_surface_id) override {}

  std::string BuildJson(bool success) const {
    std::ostringstream out;
    out << "{\n"
        << "  \"success\": " << (success ? "true" : "false") << ",\n"
        << "  \"path\": \"RootCompositorFrameSinkImpl/software-proof\",\n"
        << "  \"viewport\": \"" << viewport_.width() << "x"
        << viewport_.height() << "\",\n"
        << "  \"acks\": " << ack_count_ << ",\n"
        << "  \"copy_pixels\": " << copy_waiter_.pixels() << ",\n"
        << "  \"failure\": \"" << EscapeJson(failure_reason_) << "\"\n"
        << "}\n";
    return out.str();
  }

  gfx::Size viewport_;
  const viz::FrameSinkId frame_sink_id_{880, 1};
  ProofSoftwareOutputSurfaceProvider output_surface_provider_;
  std::unique_ptr<viz::FrameSinkManagerImpl> frame_sink_manager_;
  std::unique_ptr<viz::RootCompositorFrameSinkImpl> root_frame_sink_;
  viz::RendererSettings renderer_settings_;
  viz::DebugRendererSettings debug_settings_;
  viz::ParentLocalSurfaceIdAllocator surface_id_allocator_;
  mojo::AssociatedRemote<viz::mojom::CompositorFrameSink>
      compositor_frame_sink_remote_;
  mojo::AssociatedRemote<viz::mojom::DisplayPrivate> display_private_remote_;
  mojo::Receiver<viz::mojom::CompositorFrameSinkClient>
      compositor_frame_sink_client_receiver_{this};
  uint32_t frame_token_ = 0;
  int ack_count_ = 0;
  CopyWaiter copy_waiter_;
  std::string failure_reason_;
  base::WeakPtrFactory<RootFrameSinkProof> weak_factory_{this};
};

#if BLINK_STANDALONE_FRAME_SINK_ASYNC_PROOF
class AsyncFrameSinkClient final : public cc::LayerTreeFrameSinkClient {
 public:
  void SetBeginFrameSource(viz::BeginFrameSource* source) override {
    begin_frame_source_set = source != nullptr;
  }
  std::optional<viz::HitTestRegionList> BuildHitTestData() override {
    return std::nullopt;
  }
  void ReclaimResources(std::vector<viz::ReturnedResource> resources) override {
    reclaimed_resources += static_cast<int>(resources.size());
  }
  void SetTreeActivationCallback(base::RepeatingClosure callback) override {}
  void DidReceiveCompositorFrameAck() override { ++ack_count; }
  void DidPresentCompositorFrame(
      uint32_t frame_token,
      const viz::FrameTimingDetails& details) override {}
  void DidLoseLayerTreeFrameSink() override { lost = true; }
  void OnDraw(const gfx::Transform& transform,
              const gfx::Rect& viewport,
              bool resourceless_software_draw,
              bool skip_draw) override {}
  void SetMemoryPolicy(const cc::ManagedMemoryPolicy& policy) override {}
  void SetExternalTilePriorityConstraints(
      const gfx::Rect& viewport_rect,
      const gfx::Transform& transform) override {}

  bool begin_frame_source_set = false;
  bool lost = false;
  int ack_count = 0;
  int reclaimed_resources = 0;
};

class AsyncFrameSinkProof final {
 public:
  explicit AsyncFrameSinkProof(const gfx::Size& viewport) : viewport_(viewport) {}
  AsyncFrameSinkProof(const AsyncFrameSinkProof&) = delete;
  AsyncFrameSinkProof& operator=(const AsyncFrameSinkProof&) = delete;
  ~AsyncFrameSinkProof() {
    async_frame_sink_.reset();
    root_frame_sink_.reset();
    frame_sink_manager_.reset();
  }

  std::string Run() {
    if (!CreateRootAndAsyncFrameSink()) {
      return BuildJson(false);
    }
    if (!SubmitAndCopy(viewport_, SkColors::kBlue, "initial")) {
      return BuildJson(false);
    }
    const gfx::Size resized(std::max(1, viewport_.width() / 2),
                            std::max(1, viewport_.height() / 2));
    if (!SubmitAndCopy(resized, SkColors::kGreen, "resized")) {
      return BuildJson(false);
    }
    return BuildJson(true);
  }

 private:
  bool CreateRootAndAsyncFrameSink() {
    scoped_refptr<base::SingleThreadTaskRunner> task_runner =
        base::SingleThreadTaskRunner::GetCurrentDefault();
    if (!task_runner) {
      failure_reason_ = "async proof requires a current task runner";
      return false;
    }
    frame_sink_manager_ =
        std::make_unique<viz::FrameSinkManagerImpl>(
            viz::FrameSinkManagerImpl::InitParams(&output_surface_provider_));
    frame_sink_manager_->RegisterFrameSinkId(frame_sink_id_,
                                             /*report_activation=*/true);
    frame_sink_manager_->SetFrameSinkDebugLabel(
        frame_sink_id_, "standalone-renderer-async-proof");

    renderer_settings_.dont_round_texture_sizes_for_pixel_tests = true;
    renderer_settings_.requires_alpha_channel = true;

    mojo::PendingReceiver<viz::mojom::CompositorFrameSinkClient>
        async_client_receiver;
    mojo::AssociatedRemote<viz::mojom::CompositorFrameSink>
        root_associated_frame_sink_remote;

    auto params = viz::mojom::RootCompositorFrameSinkParams::New();
    params->frame_sink_id = frame_sink_id_;
    params->widget = gpu::kNullSurfaceHandle;
    params->gpu_compositing = false;
    params->renderer_settings = renderer_settings_;
    params->compositor_frame_sink = root_associated_frame_sink_remote
                                        .BindNewEndpointAndPassDedicatedReceiver();
    params->compositor_frame_sink_client =
        async_client_receiver.InitWithNewPipeAndPassRemote();
    params->display_private =
        display_private_remote_.BindNewEndpointAndPassReceiver();

    root_frame_sink_ = viz::RootCompositorFrameSinkImpl::Create(
        std::move(params), frame_sink_manager_.get(), &output_surface_provider_,
        viz::BeginFrameSource::kNotRestartableId,
        /*run_all_compositor_stages_before_draw=*/true, &debug_settings_,
        /*hint_session_factory=*/nullptr);
    if (!root_frame_sink_) {
      failure_reason_ = "RootCompositorFrameSinkImpl::Create returned null";
      return false;
    }
    root_frame_sink_->SetDisplayVisible(true);
    root_frame_sink_->Resize(viewport_);

    async_root_receiver_ =
        std::make_unique<mojo::Receiver<viz::mojom::CompositorFrameSink>>(
            root_frame_sink_.get());

    cc::mojo_embedder::AsyncLayerTreeFrameSink::InitParams async_params;
    async_params.compositor_task_runner = task_runner;
    async_params.pipes.compositor_frame_sink_remote =
        async_root_receiver_->BindNewPipeAndPassRemote(task_runner);
    async_params.pipes.client_receiver = std::move(async_client_receiver);
    async_params.auto_needs_begin_frame = true;
    async_params.no_compositor_frame_acks = false;
    async_frame_sink_ =
        std::make_unique<cc::mojo_embedder::AsyncLayerTreeFrameSink>(
            /*context_provider=*/nullptr,
            /*worker_context_provider=*/nullptr,
            /*shared_image_interface=*/nullptr, &async_params);
    if (!async_frame_sink_->BindToClient(&client_)) {
      failure_reason_ = "AsyncLayerTreeFrameSink::BindToClient failed";
      return false;
    }
    base::RunLoop().RunUntilIdle();
    return true;
  }

  bool SubmitAndCopy(const gfx::Size& size,
                     SkColor4f color,
                     const char* label) {
    surface_id_allocator_.GenerateId();
    const viz::LocalSurfaceId local_surface_id =
        surface_id_allocator_.GetCurrentLocalSurfaceId();
    root_frame_sink_->Resize(size);
    async_frame_sink_->SetLocalSurfaceId(local_surface_id);
    async_frame_sink_->SubmitCompositorFrame(
        BuildSolidColorFrame(size, color, ++frame_token_),
        /*hit_test_data_changed=*/true);
    DrawNow();
    const viz::SurfaceId current_surface_id =
        root_frame_sink_->CurrentSurfaceId();
    if (!current_surface_id.is_valid() ||
        current_surface_id.local_surface_id() != local_surface_id) {
      failure_reason_ = std::string(label) +
                        " did not activate submitted LocalSurfaceId";
      return false;
    }
    return copy_waiter_.RequestAndWait(
        local_surface_id, size, label,
        base::BindRepeating(&AsyncFrameSinkProof::RequestCopy,
                            weak_factory_.GetWeakPtr()),
        base::BindRepeating(&AsyncFrameSinkProof::DrawNow,
                            weak_factory_.GetWeakPtr()),
        &failure_reason_);
  }

  void RequestCopy(const viz::LocalSurfaceId& local_surface_id,
                   std::unique_ptr<viz::CopyOutputRequest> request) {
    frame_sink_manager_->RequestCopyOfOutput(
        viz::SurfaceId(frame_sink_id_, local_surface_id), std::move(request),
        /*capture_exact_surface_id=*/true, base::Seconds(5));
  }

  void DrawNow() {
    base::RunLoop().RunUntilIdle();
    root_frame_sink_->ForceImmediateDrawAndSwapIfPossible();
    base::RunLoop().RunUntilIdle();
  }

  std::string BuildJson(bool success) const {
    std::ostringstream out;
    out << "{\n"
        << "  \"success\": " << (success ? "true" : "false") << ",\n"
        << "  \"path\": \"RootCompositorFrameSinkImpl+AsyncLayerTreeFrameSink/"
           "software-proof\",\n"
        << "  \"viewport\": \"" << viewport_.width() << "x"
        << viewport_.height() << "\",\n"
        << "  \"begin_frame_source_set\": "
        << (client_.begin_frame_source_set ? 1 : 0) << ",\n"
        << "  \"acks\": " << client_.ack_count << ",\n"
        << "  \"reclaimed_resources\": " << client_.reclaimed_resources
        << ",\n"
        << "  \"copy_pixels\": " << copy_waiter_.pixels() << ",\n"
        << "  \"failure\": \"" << EscapeJson(failure_reason_) << "\"\n"
        << "}\n";
    return out.str();
  }

  gfx::Size viewport_;
  const viz::FrameSinkId frame_sink_id_{881, 1};
  ProofSoftwareOutputSurfaceProvider output_surface_provider_;
  std::unique_ptr<viz::FrameSinkManagerImpl> frame_sink_manager_;
  std::unique_ptr<viz::RootCompositorFrameSinkImpl> root_frame_sink_;
  std::unique_ptr<cc::mojo_embedder::AsyncLayerTreeFrameSink>
      async_frame_sink_;
  std::unique_ptr<mojo::Receiver<viz::mojom::CompositorFrameSink>>
      async_root_receiver_;
  AsyncFrameSinkClient client_;
  viz::RendererSettings renderer_settings_;
  viz::DebugRendererSettings debug_settings_;
  viz::ParentLocalSurfaceIdAllocator surface_id_allocator_;
  mojo::AssociatedRemote<viz::mojom::DisplayPrivate> display_private_remote_;
  uint32_t frame_token_ = 0;
  CopyWaiter copy_waiter_;
  std::string failure_reason_;
  base::WeakPtrFactory<AsyncFrameSinkProof> weak_factory_{this};
};
#endif

}  // namespace

std::string RunChromiumRootFrameSinkProof(int width, int height) {
  InstallMojoCoreForFrameSinkProbe();
  const int safe_width = std::max(1, width);
  const int safe_height = std::max(1, height);
  RootFrameSinkProof proof(gfx::Size(safe_width, safe_height));
  return proof.Run();
}

std::string RunChromiumAsyncFrameSinkProof(int width, int height) {
#if BLINK_STANDALONE_FRAME_SINK_ASYNC_PROOF
  InstallMojoCoreForFrameSinkProbe();
  const int safe_width = std::max(1, width);
  const int safe_height = std::max(1, height);
  AsyncFrameSinkProof proof(gfx::Size(safe_width, safe_height));
  return proof.Run();
#else
  return "{\n"
         "  \"success\": false,\n"
         "  \"path\": \"AsyncLayerTreeFrameSink/disabled\",\n"
         "  \"failure\": \"async frame-sink transport is not part of the root lifecycle proof\"\n"
         "}\n";
#endif
}

}  // namespace html_css_renderer
