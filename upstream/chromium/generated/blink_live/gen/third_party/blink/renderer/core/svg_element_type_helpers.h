// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/element_type_helpers.h.tmpl
// and input files:
//   upstream\chromium\third_party\blink\renderer\core\svg\svg_tag_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_ELEMENT_TYPE_HELPERS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_ELEMENT_TYPE_HELPERS_H_

#include "third_party/blink/renderer/core/svg/svg_element.h"
#include "third_party/blink/renderer/core/svg_names.h"
#include "third_party/blink/renderer/core/element_type_enum.h"

namespace blink {

class Document;

// Type checking.
class SVGAElement;
template <>
struct DowncastTraits<SVGAElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGAElement;
  }
};

class SVGAnimateMotionElement;
template <>
struct DowncastTraits<SVGAnimateMotionElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGAnimateMotionElement;
  }
};

class SVGAnimateTransformElement;
template <>
struct DowncastTraits<SVGAnimateTransformElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGAnimateTransformElement;
  }
};

class SVGCircleElement;
template <>
struct DowncastTraits<SVGCircleElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGCircleElement;
  }
};

class SVGClipPathElement;
template <>
struct DowncastTraits<SVGClipPathElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGClipPathElement;
  }
};

class SVGDefsElement;
template <>
struct DowncastTraits<SVGDefsElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGDefsElement;
  }
};

class SVGDescElement;
template <>
struct DowncastTraits<SVGDescElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGDescElement;
  }
};

class SVGEllipseElement;
template <>
struct DowncastTraits<SVGEllipseElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGEllipseElement;
  }
};

class SVGFEBlendElement;
template <>
struct DowncastTraits<SVGFEBlendElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEBlendElement;
  }
};

class SVGFEColorMatrixElement;
template <>
struct DowncastTraits<SVGFEColorMatrixElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEColorMatrixElement;
  }
};

class SVGFEComponentTransferElement;
template <>
struct DowncastTraits<SVGFEComponentTransferElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEComponentTransferElement;
  }
};

class SVGFECompositeElement;
template <>
struct DowncastTraits<SVGFECompositeElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFECompositeElement;
  }
};

class SVGFEConvolveMatrixElement;
template <>
struct DowncastTraits<SVGFEConvolveMatrixElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEConvolveMatrixElement;
  }
};

class SVGFEDiffuseLightingElement;
template <>
struct DowncastTraits<SVGFEDiffuseLightingElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEDiffuseLightingElement;
  }
};

class SVGFEDisplacementMapElement;
template <>
struct DowncastTraits<SVGFEDisplacementMapElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEDisplacementMapElement;
  }
};

class SVGFEDistantLightElement;
template <>
struct DowncastTraits<SVGFEDistantLightElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEDistantLightElement;
  }
};

class SVGFEDropShadowElement;
template <>
struct DowncastTraits<SVGFEDropShadowElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEDropShadowElement;
  }
};

class SVGFEFloodElement;
template <>
struct DowncastTraits<SVGFEFloodElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEFloodElement;
  }
};

class SVGFEFuncAElement;
template <>
struct DowncastTraits<SVGFEFuncAElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEFuncAElement;
  }
};

class SVGFEFuncBElement;
template <>
struct DowncastTraits<SVGFEFuncBElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEFuncBElement;
  }
};

class SVGFEFuncGElement;
template <>
struct DowncastTraits<SVGFEFuncGElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEFuncGElement;
  }
};

class SVGFEFuncRElement;
template <>
struct DowncastTraits<SVGFEFuncRElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEFuncRElement;
  }
};

class SVGFEGaussianBlurElement;
template <>
struct DowncastTraits<SVGFEGaussianBlurElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEGaussianBlurElement;
  }
};

class SVGFEImageElement;
template <>
struct DowncastTraits<SVGFEImageElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEImageElement;
  }
};

class SVGFEMergeElement;
template <>
struct DowncastTraits<SVGFEMergeElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEMergeElement;
  }
};

class SVGFEMergeNodeElement;
template <>
struct DowncastTraits<SVGFEMergeNodeElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEMergeNodeElement;
  }
};

class SVGFEMorphologyElement;
template <>
struct DowncastTraits<SVGFEMorphologyElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEMorphologyElement;
  }
};

class SVGFEOffsetElement;
template <>
struct DowncastTraits<SVGFEOffsetElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEOffsetElement;
  }
};

class SVGFEPointLightElement;
template <>
struct DowncastTraits<SVGFEPointLightElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEPointLightElement;
  }
};

class SVGFESpecularLightingElement;
template <>
struct DowncastTraits<SVGFESpecularLightingElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFESpecularLightingElement;
  }
};

class SVGFESpotLightElement;
template <>
struct DowncastTraits<SVGFESpotLightElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFESpotLightElement;
  }
};

class SVGFETileElement;
template <>
struct DowncastTraits<SVGFETileElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFETileElement;
  }
};

class SVGFETurbulenceElement;
template <>
struct DowncastTraits<SVGFETurbulenceElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFETurbulenceElement;
  }
};

class SVGFilterElement;
template <>
struct DowncastTraits<SVGFilterElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFilterElement;
  }
};

class SVGForeignObjectElement;
template <>
struct DowncastTraits<SVGForeignObjectElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGForeignObjectElement;
  }
};

class SVGGElement;
template <>
struct DowncastTraits<SVGGElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGGElement;
  }
};

class SVGImageElement;
template <>
struct DowncastTraits<SVGImageElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGImageElement;
  }
};

class SVGLineElement;
template <>
struct DowncastTraits<SVGLineElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGLineElement;
  }
};

class SVGLinearGradientElement;
template <>
struct DowncastTraits<SVGLinearGradientElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGLinearGradientElement;
  }
};

class SVGMarkerElement;
template <>
struct DowncastTraits<SVGMarkerElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGMarkerElement;
  }
};

class SVGMaskElement;
template <>
struct DowncastTraits<SVGMaskElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGMaskElement;
  }
};

class SVGMetadataElement;
template <>
struct DowncastTraits<SVGMetadataElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGMetadataElement;
  }
};

class SVGMPathElement;
template <>
struct DowncastTraits<SVGMPathElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGMPathElement;
  }
};

class SVGPathElement;
template <>
struct DowncastTraits<SVGPathElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGPathElement;
  }
};

class SVGPatternElement;
template <>
struct DowncastTraits<SVGPatternElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGPatternElement;
  }
};

class SVGPolygonElement;
template <>
struct DowncastTraits<SVGPolygonElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGPolygonElement;
  }
};

class SVGPolylineElement;
template <>
struct DowncastTraits<SVGPolylineElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGPolylineElement;
  }
};

class SVGRadialGradientElement;
template <>
struct DowncastTraits<SVGRadialGradientElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGRadialGradientElement;
  }
};

class SVGRectElement;
template <>
struct DowncastTraits<SVGRectElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGRectElement;
  }
};

class SVGScriptElement;
template <>
struct DowncastTraits<SVGScriptElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGScriptElement;
  }
};

class SVGSetElement;
template <>
struct DowncastTraits<SVGSetElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGSetElement;
  }
};

class SVGStopElement;
template <>
struct DowncastTraits<SVGStopElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGStopElement;
  }
};

class SVGStyleElement;
template <>
struct DowncastTraits<SVGStyleElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGStyleElement;
  }
};

class SVGSVGElement;
template <>
struct DowncastTraits<SVGSVGElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGSVGElement;
  }
};

class SVGSwitchElement;
template <>
struct DowncastTraits<SVGSwitchElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGSwitchElement;
  }
};

class SVGSymbolElement;
template <>
struct DowncastTraits<SVGSymbolElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGSymbolElement;
  }
};

class SVGTextElement;
template <>
struct DowncastTraits<SVGTextElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGTextElement;
  }
};

class SVGTextPathElement;
template <>
struct DowncastTraits<SVGTextPathElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGTextPathElement;
  }
};

class SVGTitleElement;
template <>
struct DowncastTraits<SVGTitleElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGTitleElement;
  }
};

class SVGTSpanElement;
template <>
struct DowncastTraits<SVGTSpanElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGTSpanElement;
  }
};

class SVGUseElement;
template <>
struct DowncastTraits<SVGUseElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGUseElement;
  }
};

class SVGViewElement;
template <>
struct DowncastTraits<SVGViewElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGViewElement;
  }
};


}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_ELEMENT_TYPE_HELPERS_H_
