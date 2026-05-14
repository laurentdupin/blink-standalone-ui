#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_BLINK_FORWARD_H_

#include <functional>
#include <memory>

namespace blink::mojom::blink {

enum class AnnotationType {
  kSharedHighlight,
};

struct Selector;
using SelectorPtr = std::unique_ptr<Selector>;
class AnnotationAgent;
class AnnotationAgentHost;
class AnnotationAgentContainer;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_BLINK_FORWARD_H_
