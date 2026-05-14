#ifndef STANDALONE_RENDERER_STUBS_PRINTING_MOJOM_PRINT_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_PRINTING_MOJOM_PRINT_MOJOM_SHARED_H_

namespace printing::mojom {

enum class PrintScalingOption {
  kNone,
  kFitToPrintableArea,
  kSourceSize,
  kFitToPaper,
  kCenterShrinkToFitPaper,
};

}  // namespace printing::mojom

#endif
