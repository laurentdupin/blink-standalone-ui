#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_FORWARD_H_

#include <memory>

namespace blink::mojom {

enum class AnnotationType {
  kSharedHighlight,
  kTextFinder,
  kGlic,
  kScrollOnly,
};

enum class AttachmentResult {
  kSuccess,
  kSelectorNotMatched,
  kRangeInvalid,
};

class AnnotationAgent;
class AnnotationAgentHost;
class AnnotationAgentContainer;
struct SelectorCreationResult;
using SelectorCreationResultPtr = std::unique_ptr<SelectorCreationResult>;
class Selector;
using SelectorPtr = std::unique_ptr<Selector>;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_FORWARD_H_
