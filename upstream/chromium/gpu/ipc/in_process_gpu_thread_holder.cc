// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "gpu/ipc/in_process_gpu_thread_holder.h"

#include <stdio.h>

#include <cstdlib>

#include "base/command_line.h"
#include "base/functional/bind.h"
#include "base/functional/callback_helpers.h"
#include "base/synchronization/waitable_event.h"
#include "build/build_config.h"
#include "gpu/command_buffer/service/feature_info.h"
#include "gpu/command_buffer/service/scheduler.h"
#include "gpu/command_buffer/service/service_utils.h"
#include "gpu/command_buffer/service/shared_image/shared_image_manager.h"
#include "gpu/command_buffer/service/sync_point_manager.h"
#include "gpu/config/gpu_driver_bug_workarounds.h"
#include "gpu/config/gpu_info_collector.h"
#include "gpu/config/gpu_util.h"
#include "gpu/vulkan/buildflags.h"
#include "ui/gl/gl_surface.h"
#include "ui/gl/gl_utils.h"
#include "ui/gl/init/gl_factory.h"

#if BUILDFLAG(SKIA_USE_DAWN) && BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
#include "gpu/command_buffer/service/dawn_context_provider.h"
#endif

#if BUILDFLAG(ENABLE_VULKAN)
#include "components/viz/common/gpu/vulkan_in_process_context_provider.h"
#include "gpu/vulkan/init/vulkan_factory.h"
#include "gpu/vulkan/vulkan_device_queue.h"
#include "gpu/vulkan/vulkan_implementation.h"
#endif

namespace gpu {

namespace {

void TraceStandaloneGpuThreadHolderStage(const char* stage) {
#if defined(HTML_CSS_RENDERER_STANDALONE)
  if (!std::getenv("HTML_CSS_RENDERER_TRACE_GPU_INIT"))
    return;
  fprintf(stderr, "gpu_thread_holder.stage=%s\n", stage ? stage : "");
  fflush(stderr);
#endif
}

void TraceStandaloneGpuThreadHolderPointer(const char* label, const void* ptr) {
#if defined(HTML_CSS_RENDERER_STANDALONE)
  if (!std::getenv("HTML_CSS_RENDERER_TRACE_GPU_INIT"))
    return;
  fprintf(stderr, "gpu_thread_holder.ptr=%s %p\n", label ? label : "", ptr);
  fflush(stderr);
#endif
}

}  // namespace

InProcessGpuThreadHolder::InProcessGpuThreadHolder()
    : base::Thread("GpuThread") {
  DCHECK(base::CommandLine::InitializedForCurrentProcess());
  auto* command_line = base::CommandLine::ForCurrentProcess();
  gpu_preferences_ = gles2::ParseGpuPreferences(command_line);

  gpu::GPUInfo gpu_info;
  gpu::CollectGraphicsInfoForTesting(&gpu_info);
  gpu_feature_info_ = gpu::ComputeGpuFeatureInfo(gpu_info, gpu_preferences_,
                                                 command_line, nullptr);

  Start();
}

InProcessGpuThreadHolder::~InProcessGpuThreadHolder() {
  // Ensure members created on GPU thread are destroyed there too.
  task_runner()->PostTask(
      FROM_HERE, base::BindOnce(&InProcessGpuThreadHolder::DeleteOnGpuThread,
                                base::Unretained(this)));
  Stop();
}

GpuPreferences* InProcessGpuThreadHolder::GetGpuPreferences() {
  DCHECK(!task_executor_);
  return &gpu_preferences_;
}

GpuFeatureInfo* InProcessGpuThreadHolder::GetGpuFeatureInfo() {
  DCHECK(!task_executor_);
  return &gpu_feature_info_;
}

CommandBufferTaskExecutor* InProcessGpuThreadHolder::GetTaskExecutor() {
  if (!task_executor_) {
    TraceStandaloneGpuThreadHolderStage("GetTaskExecutor before post init");
    base::WaitableEvent completion;
    task_runner()->PostTask(
        FROM_HERE,
        base::BindOnce(&InProcessGpuThreadHolder::InitializeOnGpuThread,
                       base::Unretained(this), &completion));
    TraceStandaloneGpuThreadHolderStage("GetTaskExecutor before wait");
    completion.Wait();
    TraceStandaloneGpuThreadHolderStage("GetTaskExecutor after wait");
  }
  return task_executor_.get();
}

#if BUILDFLAG(ENABLE_VULKAN)
void InProcessGpuThreadHolder::AdoptExternalVulkanForTesting(
    VulkanImplementation* vulkan_implementation,
    std::unique_ptr<VulkanDeviceQueue> vulkan_device_queue) {
  DCHECK(!task_executor_);
  DCHECK(vulkan_implementation);
  DCHECK(vulkan_device_queue);
  pending_external_vulkan_implementation_ = vulkan_implementation;
  pending_external_vulkan_device_queue_ = std::move(vulkan_device_queue);
}
#endif

#if BUILDFLAG(IS_WIN)
void InProcessGpuThreadHolder::SetExternalD3D12AdapterLuidForTesting(
    LUID adapter_luid,
    ID3D12Device* d3d12_device,
    ID3D12CommandQueue* d3d12_command_queue) {
  DCHECK(!task_executor_);
  external_d3d12_adapter_luid_ = adapter_luid;
  external_d3d12_device_ = d3d12_device;
  external_d3d12_command_queue_ = d3d12_command_queue;
}
#endif

Scheduler* InProcessGpuThreadHolder::scheduler() {
  GetTaskExecutor();
  return scheduler_.get();
}

SyncPointManager* InProcessGpuThreadHolder::sync_point_manager() {
  GetTaskExecutor();
  return sync_point_manager_.get();
}

SharedImageManager* InProcessGpuThreadHolder::shared_image_manager() {
  GetTaskExecutor();
  return shared_image_manager_.get();
}

const GpuDriverBugWorkarounds&
InProcessGpuThreadHolder::gpu_driver_bug_workarounds() {
  GetTaskExecutor();
  return gpu_driver_bug_workarounds_;
}

void InProcessGpuThreadHolder::InitializeOnGpuThread(
    base::WaitableEvent* completion) {
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread begin");
  sync_point_manager_ = std::make_unique<SyncPointManager>();
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread after sync point");
  scheduler_ = std::make_unique<Scheduler>(sync_point_manager_.get());
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread after scheduler");
  shared_image_manager_ = std::make_unique<SharedImageManager>();
  TraceStandaloneGpuThreadHolderStage(
      "InitializeOnGpuThread after shared image manager");

  bool use_passthrough_cmd_decoder =
      gpu_preferences_.use_passthrough_cmd_decoder;

  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread before share group");
  share_group_ = new gl::GLShareGroup();
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread before surface");
  surface_ =
      gl::init::CreateOffscreenGLSurface(gl::GetDefaultDisplay(), gfx::Size());
  if (!surface_) {
    TraceStandaloneGpuThreadHolderStage(
        "InitializeOnGpuThread failed creating offscreen surface");
    completion->Signal();
    return;
  }
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread after surface");
  gl::GLContextAttribs attribs =
      gles2::GenerateGLContextAttribsForCompositor(use_passthrough_cmd_decoder);
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread before context");
  context_ =
      gl::init::CreateGLContext(share_group_.get(), surface_.get(), attribs);
  if (!context_) {
    TraceStandaloneGpuThreadHolderStage(
        "InitializeOnGpuThread failed creating GL context");
    completion->Signal();
    return;
  }
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread before MakeCurrent");
  if (!context_->MakeCurrent(surface_.get())) {
    TraceStandaloneGpuThreadHolderStage(
        "InitializeOnGpuThread failed MakeCurrent");
    completion->Signal();
    return;
  }
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread after MakeCurrent");
  gpu_driver_bug_workarounds_ = GpuDriverBugWorkarounds(
      gpu_feature_info_.enabled_gpu_driver_bug_workarounds);
  TraceStandaloneGpuThreadHolderPointer("workarounds after construct",
                                        &gpu_driver_bug_workarounds_);

  bool use_virtualized_gl_context = false;
#if BUILDFLAG(IS_MAC)
  // Virtualize GpuPreference:::kLowPower contexts by default on OS X to prevent
  // performance regressions when enabling FCM. https://crbug.com/180463
  use_virtualized_gl_context = true;
#endif
  use_virtualized_gl_context |=
      gpu_driver_bug_workarounds_.use_virtualized_gl_contexts;
  if (use_passthrough_cmd_decoder) {
    // Virtualized contexts don't work with passthrough command decoder.
    // See https://crbug.com/914976
    use_virtualized_gl_context = false;
  }
  if (use_virtualized_gl_context)
    share_group_->SetSharedContext(context_.get());

  TraceStandaloneGpuThreadHolderStage(
      "InitializeOnGpuThread before shared context state");
#if BUILDFLAG(SKIA_USE_DAWN) && BUILDFLAG(IS_WIN) && \
    defined(BLINK_STANDALONE_EXPERIMENTAL_DAWN_D3D12_RENDER)
  if (gpu_preferences_.gr_context_type == GrContextType::kGraphiteDawn) {
    TraceStandaloneGpuThreadHolderStage(
        "InitializeOnGpuThread before Dawn D3D12 context provider");
    if (external_d3d12_device_ && external_d3d12_command_queue_) {
      dawn_context_provider_ =
          DawnContextProvider::CreateWithExternalD3D12Device(
              external_d3d12_device_, external_d3d12_command_queue_,
              gpu_preferences_, gpu_feature_info_,
              /*progress_reporter=*/nullptr,
              DawnContextProvider::DefaultValidateAdapterFn,
              external_d3d12_adapter_luid_);
    } else {
      dawn_context_provider_ = DawnContextProvider::CreateWithBackend(
          wgpu::BackendType::D3D12, /*force_fallback_adapter=*/false,
          gpu_preferences_, gpu_feature_info_, /*progress_reporter=*/nullptr,
          DawnContextProvider::DefaultValidateAdapterFn,
          external_d3d12_adapter_luid_);
    }
    if (!dawn_context_provider_) {
      TraceStandaloneGpuThreadHolderStage(
          "InitializeOnGpuThread failed Dawn D3D12 context provider");
      completion->Signal();
      return;
    }
  }
#endif
#if BUILDFLAG(ENABLE_VULKAN)
  if (gpu_preferences_.gr_context_type == GrContextType::kVulkan) {
    if (pending_external_vulkan_implementation_ &&
        pending_external_vulkan_device_queue_) {
      TraceStandaloneGpuThreadHolderStage(
          "InitializeOnGpuThread before external Vulkan context provider");
      vulkan_context_provider_ =
          viz::VulkanInProcessContextProvider::CreateForCompositorGpuThread(
              pending_external_vulkan_implementation_.get(),
              std::move(pending_external_vulkan_device_queue_));
      pending_external_vulkan_implementation_ = nullptr;
    } else {
      TraceStandaloneGpuThreadHolderStage(
          "InitializeOnGpuThread before Vulkan implementation");
      vulkan_implementation_ = CreateVulkanImplementation(false);
      if (!vulkan_implementation_ ||
          !vulkan_implementation_->InitializeVulkanInstance(true)) {
        TraceStandaloneGpuThreadHolderStage(
            "InitializeOnGpuThread failed Vulkan implementation");
        vulkan_implementation_.reset();
        completion->Signal();
        return;
      }
      TraceStandaloneGpuThreadHolderStage(
          "InitializeOnGpuThread before Vulkan context provider");
      vulkan_context_provider_ =
          viz::VulkanInProcessContextProvider::Create(
              vulkan_implementation_.get());
    }
    if (!vulkan_context_provider_) {
      TraceStandaloneGpuThreadHolderStage(
          "InitializeOnGpuThread failed Vulkan context provider");
      vulkan_implementation_.reset();
      completion->Signal();
      return;
    }
  }
#endif
  context_state_ = base::MakeRefCounted<SharedContextState>(
      share_group_, surface_, context_, use_virtualized_gl_context,
      base::DoNothing(), gpu_preferences_.gr_context_type,
#if BUILDFLAG(ENABLE_VULKAN)
      vulkan_context_provider_.get()
#else
      nullptr
#endif
      ,
#if GPU_IN_PROCESS_THREAD_HOLDER_HAS_DAWN_CONTEXT_PROVIDER
      dawn_context_provider_.get()
#else
      nullptr
#endif
  );
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread before InitializeGL");
  TraceStandaloneGpuThreadHolderPointer("workarounds before InitializeGL",
                                        &gpu_driver_bug_workarounds_);
  context_state_->InitializeGL(gpu_preferences_, gpu_driver_bug_workarounds_,
                               gpu_feature_info_);
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread after InitializeGL");
  TraceStandaloneGpuThreadHolderStage(
      "InitializeOnGpuThread before InitializeSkia");
  TraceStandaloneGpuThreadHolderPointer("workarounds before InitializeSkia",
                                        &gpu_driver_bug_workarounds_);
  context_state_->InitializeSkia(gpu_preferences_, gpu_driver_bug_workarounds_,
                                 /*gr_cache=*/nullptr,
                                 /*persistent_cache=*/nullptr,
                                 /*use_shader_cache_shm_count=*/nullptr,
                                 /*progress_reporter=*/nullptr);
  if (!context_state_->gr_context() &&
      !context_state_->graphite_shared_context()) {
    TraceStandaloneGpuThreadHolderStage(
        "InitializeOnGpuThread failed InitializeSkia");
    completion->Signal();
    return;
  }
  TraceStandaloneGpuThreadHolderStage(
      "InitializeOnGpuThread after InitializeSkia");

  TraceStandaloneGpuThreadHolderStage(
      "InitializeOnGpuThread before task executor");
  task_executor_ = std::make_unique<GpuInProcessThreadService>(
      this, task_runner(), scheduler_.get(), sync_point_manager_.get(),
      gl::GLSurfaceFormat(), gpu_feature_info_, gpu_preferences_,
      shared_image_manager_.get(), nullptr);
  TraceStandaloneGpuThreadHolderStage(
      "InitializeOnGpuThread after task executor");

  completion->Signal();
  TraceStandaloneGpuThreadHolderStage("InitializeOnGpuThread signaled");
}

void InProcessGpuThreadHolder::DeleteOnGpuThread() {
  task_executor_.reset();
  scheduler_.reset();
  sync_point_manager_.reset();
  shared_image_manager_.reset();

  context_state_.reset();
#if GPU_IN_PROCESS_THREAD_HOLDER_HAS_DAWN_CONTEXT_PROVIDER
  dawn_context_provider_.reset();
#endif
#if BUILDFLAG(ENABLE_VULKAN)
  if (vulkan_context_provider_) {
    vulkan_context_provider_->Destroy();
    vulkan_context_provider_.reset();
  }
  vulkan_implementation_.reset();
#endif
  context_.reset();
  surface_.reset();
  share_group_.reset();
}

scoped_refptr<SharedContextState>
InProcessGpuThreadHolder::GetSharedContextState() {
  DCHECK(context_state_);
  return context_state_;
}

scoped_refptr<gl::GLShareGroup> InProcessGpuThreadHolder::GetShareGroup() {
  if (!share_group_)
    share_group_ = base::MakeRefCounted<gl::GLShareGroup>();
  return share_group_;
}

}  // namespace gpu
