// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_IPC_SERVICE_EXTERNAL_GPU_BACKEND_DESCRIPTOR_H_
#define GPU_IPC_SERVICE_EXTERNAL_GPU_BACKEND_DESCRIPTOR_H_

#include <cstdint>

#include "build/build_config.h"
#include "gpu/ipc/service/gpu_ipc_service_export.h"

namespace gpu {

// Optional, in-process embedder backend state supplied before Viz creates GPU
// resources. Every handle is borrowed: GpuInit and GpuServiceImpl must never
// destroy the embedder's device, queue, implementation, or Dawn context.
//
// The fields are opaque at the GpuInit boundary so this header stays portable
// and does not pull Vulkan, D3D12, or Dawn headers into normal GPU startup.
// A later backend-specific adoption step validates and types the fields on the
// GPU sequence. An empty descriptor preserves Chromium's normal ownership.
struct GPU_IPC_SERVICE_EXPORT ExternalGpuBackendDescriptor {
  void* vulkan_implementation = nullptr;
  void* vulkan_device_queue = nullptr;
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
