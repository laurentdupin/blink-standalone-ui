#ifndef STANDALONE_RENDERER_STUBS_GPU_IPC_COMMON_EXPORTED_SHARED_IMAGE_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_GPU_IPC_COMMON_EXPORTED_SHARED_IMAGE_MOJOM_FORWARD_H_

#include <memory>

namespace gpu::mojom {

struct SharedImageExportResult;
using SharedImageExportResultPtr = std::unique_ptr<SharedImageExportResult>;
class SharedImageExportResultDataView;
struct ExportedSharedImage;
using ExportedSharedImagePtr = std::unique_ptr<ExportedSharedImage>;
class ExportedSharedImageDataView;

}  // namespace gpu::mojom

#endif  // STANDALONE_RENDERER_STUBS_GPU_IPC_COMMON_EXPORTED_SHARED_IMAGE_MOJOM_FORWARD_H_
