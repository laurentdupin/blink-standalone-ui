#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_BLINK_H_

#include <optional>

#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "third_party/blink/public/mojom/annotation/annotation.mojom-blink-forward.h"

namespace blink::mojom::blink {

struct Selector {};

class AnnotationAgent {};
class AnnotationAgentHost {};

class AnnotationAgentContainer {
 public:
  using CreateAgentFromSelectionCallback = std::function<void()>;
  virtual ~AnnotationAgentContainer() = default;
  virtual void CreateAgent(mojo::PendingRemote<AnnotationAgentHost>,
                           mojo::PendingReceiver<AnnotationAgent>,
                           AnnotationType,
                           SelectorPtr,
                           std::optional<int> = std::nullopt) {}
  virtual void CreateAgentFromSelection(AnnotationType,
                                        CreateAgentFromSelectionCallback) {}
  virtual void RemoveAgentsOfType(AnnotationType) {}
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_ANNOTATION_ANNOTATION_MOJOM_BLINK_H_
