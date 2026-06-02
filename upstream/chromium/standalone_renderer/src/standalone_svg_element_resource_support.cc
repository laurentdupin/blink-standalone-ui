#include "third_party/blink/renderer/core/svg/animation/element_smil_animations.h"
#include "third_party/blink/renderer/core/svg/animation/smil_animation_sandwich.h"
#include "third_party/blink/renderer/core/svg/svg_animation_element.h"

namespace blink {

ElementSMILAnimations::ElementSMILAnimations() = default;

void ElementSMILAnimations::Trace(Visitor* visitor) const {
  visitor->Trace(sandwiches_);
}

void SMILAnimationSandwich::Trace(Visitor* visitor) const {
  visitor->Trace(sandwich_);
  visitor->Trace(active_);
}

}  // namespace blink
