// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.h.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\svg\svg_attribute_names.json5
//   ..\..\third_party\blink\renderer\core\svg\svg_tag_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_NAMES_H_

#include "base/containers/heap_array.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/qualified_name.h"

namespace blink {

class SVGQualifiedName : public QualifiedNameWithHash { };

namespace svg_names {

// Namespace
CORE_EXPORT extern const AtomicString& kNamespaceURI;

// Tags


CORE_EXPORT extern const blink::SVGQualifiedName& kATag;
CORE_EXPORT extern const blink::SVGQualifiedName& kAnimateTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kAnimateColorTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kAnimateMotionTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kAnimateTransformTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kCircleTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kClipPathTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kDefsTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kDescTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kEllipseTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEBlendTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEColorMatrixTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEComponentTransferTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFECompositeTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEConvolveMatrixTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEDiffuseLightingTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEDisplacementMapTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEDistantLightTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEDropShadowTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEFloodTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEFuncATag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEFuncBTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEFuncGTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEFuncRTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEGaussianBlurTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEImageTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEMergeTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEMergeNodeTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEMorphologyTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEOffsetTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFEPointLightTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFESpecularLightingTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFESpotLightTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFETileTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFETurbulenceTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kFilterTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kForeignObjectTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kGTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kImageTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kLineTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kLinearGradientTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kMarkerTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kMaskTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kMetadataTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kMPathTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kPathTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kPatternTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kPolygonTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kPolylineTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kRadialGradientTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kRectTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kScriptTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kSetTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kStopTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kStyleTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kSVGTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kSwitchTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kSymbolTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kTextTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kTextPathTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kTitleTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kTSpanTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kUseTag;
CORE_EXPORT extern const blink::SVGQualifiedName& kViewTag;

// Attributes
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAccumulateAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAdditiveAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAlignmentBaselineAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAmplitudeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAnimateAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAsyncAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAttributeNameAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAttributeTypeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAutofocusAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAzimuthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kBaseFrequencyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kBaseProfileAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kBaselineShiftAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kBeginAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kBiasAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kBufferedRenderingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kByAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kCalcModeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kClipAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kClipPathAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kClipRuleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kClipPathUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kColorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kColorInterpolationAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kColorInterpolationFiltersAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kColorRenderingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kCrossoriginAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kCursorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kCxAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kCyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDecodingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDiffuseConstantAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDirectionAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDisplayAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDivisorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDominantBaselineAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDownloadAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDurAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDxAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kEdgeModeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kElevationAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kEndAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kExponentAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFillAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFillOpacityAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFillRuleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFilterAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFilterUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFloodColorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFloodOpacityAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFocusgroupAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontFamilyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontSizeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontSizeAdjustAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontStretchAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontStyleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontVariantAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFontWeightAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFormatAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFrAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFromAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFxAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kG1Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kG2Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kGlyphRefAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kGradientTransformAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kGradientUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kHeightAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kHrefAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kHreflangAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kImageRenderingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kInAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kIn2Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kInterceptAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kInterestforAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kKAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kK1Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kK2Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kK3Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kK4Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kKernelMatrixAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kKernelUnitLengthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kKeyPointsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kKeySplinesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kKeyTimesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLangAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLengthAdjustAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLetterSpacingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLightingColorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLimitingConeAngleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLocalAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMarkerEndAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMarkerMidAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMarkerStartAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMarkerHeightAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMarkerUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMarkerWidthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMaskAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMaskTypeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMaskContentUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMaskUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMaxAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMediaAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMethodAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMinAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kModeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kNameAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kNumOctavesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOffsetAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOnactivateAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOnbeginAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOnendAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOnfocusinAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOnfocusoutAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOnrepeatAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOpacityAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOperatorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOrderAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOrientAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOriginAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kOverflowAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPaintOrderAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPathAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPathLengthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPatternContentUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPatternTransformAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPatternUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPointerEventsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPointsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPointsAtXAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPointsAtYAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPointsAtZAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPreserveAlphaAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPreserveAspectRatioAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kPrimitiveUnitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRadiusAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRefXAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRefYAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kReferrerpolicyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRelAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRepeatCountAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRepeatDurAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRequiredExtensionsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRequiredFeaturesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRestartAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kResultAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRotateAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRxAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kScaleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSeedAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kShapeRenderingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSideAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSlopeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSpacingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSpecularConstantAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSpecularExponentAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSpreadMethodAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStartOffsetAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStdDeviationAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStitchTilesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStopColorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStopOpacityAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeDasharrayAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeDashoffsetAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeLinecapAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeLinejoinAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeMiterlimitAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeOpacityAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStrokeWidthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStyleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSurfaceScaleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSystemLanguageAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTableValuesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTargetAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTargetXAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTargetYAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTextAnchorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTextDecorationAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTextOverflowAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTextRenderingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTextLengthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTitleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kToAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTransformAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTransformOriginAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTypeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kU1Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kU2Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kUnicodeBidiAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kValuesAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kVectorEffectAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kVersionAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kViewBoxAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kVisibilityAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kWhiteSpaceAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kWidthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kWordSpacingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kWritingModeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kXAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kX1Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kX2Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kXChannelSelectorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kYAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kY1Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kY2Attr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kYChannelSelectorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kZAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kZoomAndPanAttr;

constexpr unsigned kTagsCount = 64;
CORE_EXPORT base::HeapArray<const QualifiedName*> GetTags();

constexpr unsigned kAttrsCount = 215;
CORE_EXPORT base::HeapArray<const QualifiedName*> GetAttrs();


void Init();

}  // namespace svg_names
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_NAMES_H_
