// Copyright 2018 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_IPC_IN_PROCESS_GPU_THREAD_HOLDER_H_
#define GPU_IPC_IN_PROCESS_GPU_THREAD_HOLDER_H_

#include <memory>
#include <optional>

#include "base/component_export.h"
#include "base/memory/raw_ptr.h"
#include "base/memory/scoped_refptr.h"
#include "base/threading/thread.h"
#include "build/build_config.h"
#include "gpu/command_buffer/service/shared_context_state.h"
#include "gpu/config/gpu_driver_bug_workarounds.h"
#include "gpu/config/gpu_feature_info.h"
#include "gpu/config/gpu_preferences.h"
#include "gpu/ipc/gpu_in_process_thread_service.h"
#include "gpu/vulkan/buildflags.h"

#if BUILDFLAG(IS_WIN)
#include <d3d12.h>
#include <wrl/client.h>
#endif

namespace gpu {
class CommandBufferTaskExecutor;
class DawnContextProvider;
class Scheduler;
class SharedImageManager;
class SyncPointManager;
class VulkanImplementation;
class VulkanDeviceQueue;

}  // namespace gpu

namespace viz {
class VulkanInProcessContextProvider;
}  // namespace viz

namespace gpu {

// Starts a GPU thread and task executor that runs tasks on the GPU thread. This
// isn't a full GPU thread implementation and should only be used in tests. A
// default GpuPreferences and GpuFeatureInfo will be constructed from the
// command line when this class is first created.
class COMPONENT_EXPORT(GPU_THREAD_HOLDER) InProcessGpuThreadHolder
    : public base::Thread,
      public GpuInProcessThreadServiceDelegate {
 public:
  InProcessGpuThreadHolder();

  InProcessGpuThreadHolder(const InProcessGpuThreadHolder&) = delete;
  InProcessGpuThreadHolder& operator=(const InProcessGpuThreadHolder&) = delete;

  ~InProcessGpuThreadHolder() override;

  // Returns GpuPreferences that can be modified before GetTaskExecutor() is
  // called for the first time.
  GpuPreferences* GetGpuPreferences();

  // Returns GpuFeatureInfo that can be modified before GetTaskExecutor() is
  // called for the first time.
  GpuFeatureInfo* GetGpuFeatureInfo();

  // Returns a task executor that runs commands on the GPU thread. The task
  // executor will be created the first time this is called.
  CommandBufferTaskExecutor* GetTaskExecutor();

#if BUILDFLAG(ENABLE_VULKAN)
  // Testing-only hook for standalone embedders: installs an already-created
  // Vulkan implementation/device queue before GetTaskExecutor() initializes
  // GPU state. The holder borrows |vulkan_implementation| and takes wrapper
  // ownership of |vulkan_device_queue|, but not VkInstance/VkDevice/VkQueue
  // ownership when the supplied VulkanDeviceQueue is non-owning.
  void AdoptExternalVulkanForTesting(
      VulkanImplementation* vulkan_implementation,
      std::unique_ptr<VulkanDeviceQueue> vulkan_device_queue);
#endif

#if BUILDFLAG(IS_WIN)
  void SetExternalD3D12AdapterLuidForTesting(
      LUID adapter_luid,
      ID3D12Device* d3d12_device = nullptr,
      ID3D12CommandQueue* d3d12_command_queue = nullptr);
#endif

  Scheduler* scheduler();
  SyncPointManager* sync_point_manager();
  SharedImageManager* shared_image_manager();
  const GpuDriverBugWorkarounds& gpu_driver_bug_workarounds();
  const GpuPreferences& gpu_preferences() const { return gpu_preferences_; }
  const GpuFeatureInfo& gpu_feature_info() const { return gpu_feature_info_; }
  DawnContextProvider* dawn_context_provider() const {
    return dawn_context_provider_.get();
  }

  // gpu::GpuInProcessThreadServiceDelegate implementation:
  scoped_refptr<gpu::SharedContextState> GetSharedContextState() override;
  scoped_refptr<gl::GLShareGroup> GetShareGroup() override;

 private:
  void InitializeOnGpuThread(base::WaitableEvent* completion);
  void DeleteOnGpuThread();

  GpuPreferences gpu_preferences_;
  GpuFeatureInfo gpu_feature_info_;
  GpuDriverBugWorkarounds gpu_driver_bug_workarounds_;

  scoped_refptr<gl::GLShareGroup> share_group_;
  scoped_refptr<gl::GLSurface> surface_;
  scoped_refptr<gl::GLContext> context_;
  scoped_refptr<SharedContextState> context_state_;
  std::unique_ptr<DawnContextProvider> dawn_context_provider_;
#if BUILDFLAG(IS_WIN)
  std::optional<LUID> external_d3d12_adapter_luid_;
  Microsoft::WRL::ComPtr<ID3D12Device> external_d3d12_device_;
  Microsoft::WRL::ComPtr<ID3D12CommandQueue> external_d3d12_command_queue_;
#endif
#if BUILDFLAG(ENABLE_VULKAN)
  std::unique_ptr<VulkanImplementation> vulkan_implementation_;
  raw_ptr<VulkanImplementation> pending_external_vulkan_implementation_ =
      nullptr;
  std::unique_ptr<VulkanDeviceQueue> pending_external_vulkan_device_queue_;
  scoped_refptr<viz::VulkanInProcessContextProvider>
      vulkan_context_provider_;
#endif

  std::unique_ptr<SyncPointManager> sync_point_manager_;
  std::unique_ptr<Scheduler> scheduler_;
  std::unique_ptr<SharedImageManager> shared_image_manager_;
  std::unique_ptr<CommandBufferTaskExecutor> task_executor_;
};

}  // namespace gpu

#endif  // GPU_IPC_IN_PROCESS_GPU_THREAD_HOLDER_H_
