// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_IPC_SERVICE_EXTERNAL_GPU_BACKEND_DESCRIPTOR_H_
#define GPU_IPC_SERVICE_EXTERNAL_GPU_BACKEND_DESCRIPTOR_H_

#include <cstdint>
#include <memory>

#include "build/build_config.h"
#include "gpu/ipc/service/gpu_ipc_service_export.h"
#include "gpu/vulkan/buildflags.h"

#if BUILDFLAG(ENABLE_VULKAN)
#include "gpu/vulkan/vulkan_device_queue.h"
#endif

namespace gpu {

// Optional, in-process embedder backend state supplied before Viz creates GPU
// resources. Device, implementation, and Dawn pointers are borrowed. The
// VulkanDeviceQueue wrapper is transferred to GpuServiceImpl, but it remains
// non-owning with respect to the embedder's VkInstance, VkDevice, and VkQueue.
//
// The fields are opaque at the GpuInit boundary so this header stays portable
// and does not pull Vulkan, D3D12, or Dawn headers into normal GPU startup.
// A later backend-specific adoption step validates and types the fields on the
// GPU sequence. An empty descriptor preserves Chromium's normal ownership.
struct GPU_IPC_SERVICE_EXPORT ExternalGpuBackendDescriptor {
  void* vulkan_implementation = nullptr;
#if BUILDFLAG(ENABLE_VULKAN)
  std::unique_ptr<VulkanDeviceQueue> vulkan_device_queue;
#endif
  void* dawn_context_provider = nullptr;

#if BUILDFLAG(IS_WIN)
  void* d3d12_device = nullptr;
  void* d3d12_command_queue = nullptr;
  uint32_t d3d12_adapter_luid_low = 0;
  int32_t d3d12_adapter_luid_high = 0;
#endif

  bool has_borrowed_backend() const {
#if BUILDFLAG(IS_WIN)
    return vulkan_implementation || vulkan_device_queue ||
           dawn_context_provider || d3d12_device || d3d12_command_queue ||
           d3d12_adapter_luid_low || d3d12_adapter_luid_high;
#else
    return vulkan_implementation || vulkan_device_queue ||
           dawn_context_provider;
#endif
  }
};

}  // namespace gpu

#endif  // GPU_IPC_SERVICE_EXTERNAL_GPU_BACKEND_DESCRIPTOR_H_
