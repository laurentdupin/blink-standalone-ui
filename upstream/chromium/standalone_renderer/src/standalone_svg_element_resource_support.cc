#include "third_party/blink/renderer/core/layout/svg/layout_svg_text.h"
#include "third_party/blink/renderer/core/svg/animation/element_smil_animations.h"
#include "third_party/blink/renderer/core/svg/animation/smil_animation_sandwich.h"
#include "third_party/blink/renderer/core/svg/properties/svg_animated_property.h"
#include "third_party/blink/renderer/core/svg/svg_element.h"
#include "third_party/blink/renderer/core/svg/svg_element_rare_data.h"
#include "third_party/blink/renderer/platform/heap/disallow_new_wrapper.h"

namespace blink {

ElementSMILAnimations::ElementSMILAnimations() = default;

void ElementSMILAnimations::Trace(Visitor* visitor) const {
  visitor->Trace(sandwiches_);
}

SVGElementRareData* SVGElement::EnsureSVGRareData() {
  if (!svg_rare_data_) {
    svg_rare_data_ = MakeGarbageCollected<SVGElementRareData>();
  }
  return svg_rare_data_.Get();
}

SVGElementSet* SVGElement::SetOfIncomingReferences() const {
  if (!HasSVGRareData()) {
    return nullptr;
  }
  return &SvgRareData()->IncomingReferences();
}

void SVGElement::AddReferenceTo(SVGElement* target_element) {
  DCHECK(target_element);

  EnsureSVGRareData()->OutgoingReferences().insert(target_element);
  target_element->EnsureSVGRareData()->IncomingReferences().insert(this);
}

SVGElementSet& SVGElement::GetDependencyTraversalVisitedSet() {
  using SVGElementSetHolder = DisallowNewWrapper<SVGElementSet>;
  DEFINE_STATIC_LOCAL(Persistent<SVGElementSetHolder>,
                      invalidating_dependencies,
                      (MakeGarbageCollected<SVGElementSetHolder>()));
  return invalidating_dependencies->Value();
}

void SVGElement::RemoveAllIncomingReferences() {
  if (!HasSVGRareData()) {
    return;
  }

  SVGElementSet& incoming_references = SvgRareData()->IncomingReferences();
  for (SVGElement* source_element : incoming_references) {
    DCHECK(source_element->HasSVGRareData());
    source_element->EnsureSVGRareData()->OutgoingReferences().erase(this);
  }
  incoming_references.clear();
}

void SVGElement::RemoveAllOutgoingReferences() {
  if (!HasSVGRareData()) {
    return;
  }

  SVGElementSet& outgoing_references = SvgRareData()->OutgoingReferences();
  for (SVGElement* target_element : outgoing_references) {
    DCHECK(target_element->HasSVGRareData());
    target_element->EnsureSVGRareData()->IncomingReferences().erase(this);
  }
  outgoing_references.clear();
}

SVGElementResourceClient* SVGElement::GetSVGResourceClient() {
  if (!HasSVGRareData()) {
    return nullptr;
  }
  return SvgRareData()->GetSVGResourceClient();
}

SVGElementResourceClient& SVGElement::EnsureSVGResourceClient() {
  return EnsureSVGRareData()->EnsureSVGResourceClient(this);
}

void SVGElement::ApplyMotionTransform(AffineTransform& matrix) const {
  if (HasSVGRareData()) {
    matrix.PostConcat(*SvgRareData()->AnimateMotionTransform());
  }
}

void SVGElement::SynchronizeListOfSVGAttributes(
    const base::span<SVGAnimatedPropertyBase*> attributes) {
  for (SVGAnimatedPropertyBase* attr : attributes) {
    if (attr->NeedsSynchronizeAttribute()) {
      attr->SynchronizeAttribute();
    }
  }
}

bool LayoutSVGText::IsObjectBoundingBoxValid() const {
  NOT_DESTROYED();
  return PhysicalFragments().HasFragmentItems();
}

}  // namespace blink
