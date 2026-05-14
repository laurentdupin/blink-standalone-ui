// Copyright 2026 The Standalone Renderer Authors
// Minimal GPU IPC boundary shim for CC frame sink headers.

#ifndef STANDALONE_RENDERER_STUBS_GPU_IPC_CLIENT_GPU_CHANNEL_OBSERVER_H_
#define STANDALONE_RENDERER_STUBS_GPU_IPC_CLIENT_GPU_CHANNEL_OBSERVER_H_

namespace gpu {

class GpuChannelLostObserver {
 public:
  GpuChannelLostObserver() = default;
  virtual ~GpuChannelLostObserver() = default;

  virtual void OnGpuChannelLost() = 0;
};

}  // namespace gpu

#endif  // STANDALONE_RENDERER_STUBS_GPU_IPC_CLIENT_GPU_CHANNEL_OBSERVER_H_
