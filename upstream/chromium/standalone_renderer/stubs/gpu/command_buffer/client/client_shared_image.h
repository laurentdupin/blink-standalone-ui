// Copyright 2026 The Standalone Renderer Authors
// Minimal GPU-client boundary shim for Viz resource structs.

#ifndef STANDALONE_RENDERER_STUBS_GPU_COMMAND_BUFFER_CLIENT_CLIENT_SHARED_IMAGE_H_
#define STANDALONE_RENDERER_STUBS_GPU_COMMAND_BUFFER_CLIENT_CLIENT_SHARED_IMAGE_H_

#include <string>

#include "gpu/command_buffer/common/sync_token.h"

namespace gpu {

class SharedImageExportResult {
 public:
  SharedImageExportResult() = default;
  ~SharedImageExportResult() = default;

  static SharedImageExportResult CreateEmptyResult() {
    return SharedImageExportResult();
  }

  static SharedImageExportResult CreateForTesting(const SyncToken& sync_token) {
    return SharedImageExportResult(sync_token);
  }

  bool IsEqualForTesting(const SyncToken& sync_token) const {
    return sync_token_ == sync_token;
  }

  bool IsEqualForTesting(const SharedImageExportResult& other) const {
    return sync_token_ == other.sync_token_;
  }

  bool HasData() const { return sync_token_.HasData(); }
  std::string ToDebugString() const { return sync_token_.ToDebugString(); }

 private:
  explicit SharedImageExportResult(const SyncToken& sync_token)
      : sync_token_(sync_token) {}

  SyncToken sync_token_;
};

}  // namespace gpu

#endif  // STANDALONE_RENDERER_STUBS_GPU_COMMAND_BUFFER_CLIENT_CLIENT_SHARED_IMAGE_H_
