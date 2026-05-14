// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.cc.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\svg\svg_attribute_names.json5
//   ..\..\third_party\blink\renderer\core\svg\svg_tag_names.json5


#include "third_party/blink/renderer/core/svg_names.h"

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/static_constructors.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_hasher.h"

namespace blink {
namespace svg_names {

DEFINE_GLOBAL(, AtomicString, kNamespaceURI);

// Tags

void* tag_storage[kTagsCount * ((sizeof(SVGQualifiedName) + sizeof(void *) - 1) / sizeof(void *))];
const SVGQualifiedName& kATag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[0];
const SVGQualifiedName& kAnimateTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[1];
const SVGQualifiedName& kAnimateColorTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[2];
const SVGQualifiedName& kAnimateMotionTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[3];
const SVGQualifiedName& kAnimateTransformTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[4];
const SVGQualifiedName& kCircleTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[5];
const SVGQualifiedName& kClipPathTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[6];
const SVGQualifiedName& kDefsTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[7];
const SVGQualifiedName& kDescTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[8];
const SVGQualifiedName& kEllipseTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[9];
const SVGQualifiedName& kFEBlendTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[10];
const SVGQualifiedName& kFEColorMatrixTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[11];
const SVGQualifiedName& kFEComponentTransferTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[12];
const SVGQualifiedName& kFECompositeTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[13];
const SVGQualifiedName& kFEConvolveMatrixTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[14];
const SVGQualifiedName& kFEDiffuseLightingTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[15];
const SVGQualifiedName& kFEDisplacementMapTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[16];
const SVGQualifiedName& kFEDistantLightTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[17];
const SVGQualifiedName& kFEDropShadowTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[18];
const SVGQualifiedName& kFEFloodTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[19];
const SVGQualifiedName& kFEFuncATag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[20];
const SVGQualifiedName& kFEFuncBTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[21];
const SVGQualifiedName& kFEFuncGTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[22];
const SVGQualifiedName& kFEFuncRTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[23];
const SVGQualifiedName& kFEGaussianBlurTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[24];
const SVGQualifiedName& kFEImageTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[25];
const SVGQualifiedName& kFEMergeTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[26];
const SVGQualifiedName& kFEMergeNodeTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[27];
const SVGQualifiedName& kFEMorphologyTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[28];
const SVGQualifiedName& kFEOffsetTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[29];
const SVGQualifiedName& kFEPointLightTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[30];
const SVGQualifiedName& kFESpecularLightingTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[31];
const SVGQualifiedName& kFESpotLightTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[32];
const SVGQualifiedName& kFETileTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[33];
const SVGQualifiedName& kFETurbulenceTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[34];
const SVGQualifiedName& kFilterTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[35];
const SVGQualifiedName& kForeignObjectTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[36];
const SVGQualifiedName& kGTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[37];
const SVGQualifiedName& kImageTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[38];
const SVGQualifiedName& kLineTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[39];
const SVGQualifiedName& kLinearGradientTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[40];
const SVGQualifiedName& kMarkerTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[41];
const SVGQualifiedName& kMaskTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[42];
const SVGQualifiedName& kMetadataTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[43];
const SVGQualifiedName& kMPathTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[44];
const SVGQualifiedName& kPathTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[45];
const SVGQualifiedName& kPatternTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[46];
const SVGQualifiedName& kPolygonTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[47];
const SVGQualifiedName& kPolylineTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[48];
const SVGQualifiedName& kRadialGradientTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[49];
const SVGQualifiedName& kRectTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[50];
const SVGQualifiedName& kScriptTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[51];
const SVGQualifiedName& kSetTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[52];
const SVGQualifiedName& kStopTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[53];
const SVGQualifiedName& kStyleTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[54];
const SVGQualifiedName& kSVGTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[55];
const SVGQualifiedName& kSwitchTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[56];
const SVGQualifiedName& kSymbolTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[57];
const SVGQualifiedName& kTextTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[58];
const SVGQualifiedName& kTextPathTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[59];
const SVGQualifiedName& kTitleTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[60];
const SVGQualifiedName& kTSpanTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[61];
const SVGQualifiedName& kUseTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[62];
const SVGQualifiedName& kViewTag = reinterpret_cast<SVGQualifiedName*>(&tag_storage)[63];


base::HeapArray<const QualifiedName*> GetTags() {
  auto tags = base::HeapArray<const QualifiedName*>::Uninit(kTagsCount);
  for (size_t i = 0; i < kTagsCount; ++i) {
    tags[i] = reinterpret_cast<QualifiedNameWithHash*>(&tag_storage) + i;
  }
  return tags;
}

// Attributes

void* attr_storage[kAttrsCount * ((sizeof(QualifiedNameWithHash) + sizeof(void *) - 1) / sizeof(void *))];

const QualifiedNameWithHash& kAccumulateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[0];
const QualifiedNameWithHash& kAdditiveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[1];
const QualifiedNameWithHash& kAlignmentBaselineAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[2];
const QualifiedNameWithHash& kAmplitudeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[3];
const QualifiedNameWithHash& kAnimateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[4];
const QualifiedNameWithHash& kAsyncAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[5];
const QualifiedNameWithHash& kAttributeNameAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[6];
const QualifiedNameWithHash& kAttributeTypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[7];
const QualifiedNameWithHash& kAutofocusAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[8];
const QualifiedNameWithHash& kAzimuthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[9];
const QualifiedNameWithHash& kBaseFrequencyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[10];
const QualifiedNameWithHash& kBaseProfileAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[11];
const QualifiedNameWithHash& kBaselineShiftAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[12];
const QualifiedNameWithHash& kBeginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[13];
const QualifiedNameWithHash& kBiasAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[14];
const QualifiedNameWithHash& kBufferedRenderingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[15];
const QualifiedNameWithHash& kByAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[16];
const QualifiedNameWithHash& kCalcModeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[17];
const QualifiedNameWithHash& kClipAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[18];
const QualifiedNameWithHash& kClipPathAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[19];
const QualifiedNameWithHash& kClipRuleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[20];
const QualifiedNameWithHash& kClipPathUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[21];
const QualifiedNameWithHash& kColorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[22];
const QualifiedNameWithHash& kColorInterpolationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[23];
const QualifiedNameWithHash& kColorInterpolationFiltersAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[24];
const QualifiedNameWithHash& kColorRenderingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[25];
const QualifiedNameWithHash& kCrossoriginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[26];
const QualifiedNameWithHash& kCursorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[27];
const QualifiedNameWithHash& kCxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[28];
const QualifiedNameWithHash& kCyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[29];
const QualifiedNameWithHash& kDAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[30];
const QualifiedNameWithHash& kDecodingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[31];
const QualifiedNameWithHash& kDiffuseConstantAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[32];
const QualifiedNameWithHash& kDirectionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[33];
const QualifiedNameWithHash& kDisplayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[34];
const QualifiedNameWithHash& kDivisorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[35];
const QualifiedNameWithHash& kDominantBaselineAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[36];
const QualifiedNameWithHash& kDownloadAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[37];
const QualifiedNameWithHash& kDurAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[38];
const QualifiedNameWithHash& kDxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[39];
const QualifiedNameWithHash& kDyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[40];
const QualifiedNameWithHash& kEdgeModeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[41];
const QualifiedNameWithHash& kElevationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[42];
const QualifiedNameWithHash& kEndAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[43];
const QualifiedNameWithHash& kExponentAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[44];
const QualifiedNameWithHash& kFillAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[45];
const QualifiedNameWithHash& kFillOpacityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[46];
const QualifiedNameWithHash& kFillRuleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[47];
const QualifiedNameWithHash& kFilterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[48];
const QualifiedNameWithHash& kFilterUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[49];
const QualifiedNameWithHash& kFloodColorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[50];
const QualifiedNameWithHash& kFloodOpacityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[51];
const QualifiedNameWithHash& kFocusgroupAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[52];
const QualifiedNameWithHash& kFontFamilyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[53];
const QualifiedNameWithHash& kFontSizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[54];
const QualifiedNameWithHash& kFontSizeAdjustAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[55];
const QualifiedNameWithHash& kFontStretchAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[56];
const QualifiedNameWithHash& kFontStyleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[57];
const QualifiedNameWithHash& kFontVariantAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[58];
const QualifiedNameWithHash& kFontWeightAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[59];
const QualifiedNameWithHash& kFormatAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[60];
const QualifiedNameWithHash& kFrAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[61];
const QualifiedNameWithHash& kFromAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[62];
const QualifiedNameWithHash& kFxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[63];
const QualifiedNameWithHash& kFyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[64];
const QualifiedNameWithHash& kG1Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[65];
const QualifiedNameWithHash& kG2Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[66];
const QualifiedNameWithHash& kGlyphRefAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[67];
const QualifiedNameWithHash& kGradientTransformAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[68];
const QualifiedNameWithHash& kGradientUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[69];
const QualifiedNameWithHash& kHeightAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[70];
const QualifiedNameWithHash& kHrefAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[71];
const QualifiedNameWithHash& kHreflangAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[72];
const QualifiedNameWithHash& kImageRenderingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[73];
const QualifiedNameWithHash& kInAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[74];
const QualifiedNameWithHash& kIn2Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[75];
const QualifiedNameWithHash& kInterceptAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[76];
const QualifiedNameWithHash& kInterestforAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[77];
const QualifiedNameWithHash& kKAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[78];
const QualifiedNameWithHash& kK1Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[79];
const QualifiedNameWithHash& kK2Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[80];
const QualifiedNameWithHash& kK3Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[81];
const QualifiedNameWithHash& kK4Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[82];
const QualifiedNameWithHash& kKernelMatrixAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[83];
const QualifiedNameWithHash& kKernelUnitLengthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[84];
const QualifiedNameWithHash& kKeyPointsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[85];
const QualifiedNameWithHash& kKeySplinesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[86];
const QualifiedNameWithHash& kKeyTimesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[87];
const QualifiedNameWithHash& kLangAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[88];
const QualifiedNameWithHash& kLengthAdjustAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[89];
const QualifiedNameWithHash& kLetterSpacingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[90];
const QualifiedNameWithHash& kLightingColorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[91];
const QualifiedNameWithHash& kLimitingConeAngleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[92];
const QualifiedNameWithHash& kLocalAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[93];
const QualifiedNameWithHash& kMarkerEndAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[94];
const QualifiedNameWithHash& kMarkerMidAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[95];
const QualifiedNameWithHash& kMarkerStartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[96];
const QualifiedNameWithHash& kMarkerHeightAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[97];
const QualifiedNameWithHash& kMarkerUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[98];
const QualifiedNameWithHash& kMarkerWidthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[99];
const QualifiedNameWithHash& kMaskAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[100];
const QualifiedNameWithHash& kMaskTypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[101];
const QualifiedNameWithHash& kMaskContentUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[102];
const QualifiedNameWithHash& kMaskUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[103];
const QualifiedNameWithHash& kMaxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[104];
const QualifiedNameWithHash& kMediaAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[105];
const QualifiedNameWithHash& kMethodAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[106];
const QualifiedNameWithHash& kMinAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[107];
const QualifiedNameWithHash& kModeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[108];
const QualifiedNameWithHash& kNameAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[109];
const QualifiedNameWithHash& kNumOctavesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[110];
const QualifiedNameWithHash& kOffsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[111];
const QualifiedNameWithHash& kOnactivateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[112];
const QualifiedNameWithHash& kOnbeginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[113];
const QualifiedNameWithHash& kOnendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[114];
const QualifiedNameWithHash& kOnfocusinAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[115];
const QualifiedNameWithHash& kOnfocusoutAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[116];
const QualifiedNameWithHash& kOnrepeatAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[117];
const QualifiedNameWithHash& kOpacityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[118];
const QualifiedNameWithHash& kOperatorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[119];
const QualifiedNameWithHash& kOrderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[120];
const QualifiedNameWithHash& kOrientAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[121];
const QualifiedNameWithHash& kOriginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[122];
const QualifiedNameWithHash& kOverflowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[123];
const QualifiedNameWithHash& kPaintOrderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[124];
const QualifiedNameWithHash& kPathAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[125];
const QualifiedNameWithHash& kPathLengthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[126];
const QualifiedNameWithHash& kPatternContentUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[127];
const QualifiedNameWithHash& kPatternTransformAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[128];
const QualifiedNameWithHash& kPatternUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[129];
const QualifiedNameWithHash& kPingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[130];
const QualifiedNameWithHash& kPointerEventsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[131];
const QualifiedNameWithHash& kPointsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[132];
const QualifiedNameWithHash& kPointsAtXAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[133];
const QualifiedNameWithHash& kPointsAtYAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[134];
const QualifiedNameWithHash& kPointsAtZAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[135];
const QualifiedNameWithHash& kPreserveAlphaAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[136];
const QualifiedNameWithHash& kPreserveAspectRatioAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[137];
const QualifiedNameWithHash& kPrimitiveUnitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[138];
const QualifiedNameWithHash& kRAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[139];
const QualifiedNameWithHash& kRadiusAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[140];
const QualifiedNameWithHash& kRefXAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[141];
const QualifiedNameWithHash& kRefYAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[142];
const QualifiedNameWithHash& kReferrerpolicyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[143];
const QualifiedNameWithHash& kRelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[144];
const QualifiedNameWithHash& kRepeatCountAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[145];
const QualifiedNameWithHash& kRepeatDurAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[146];
const QualifiedNameWithHash& kRequiredExtensionsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[147];
const QualifiedNameWithHash& kRequiredFeaturesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[148];
const QualifiedNameWithHash& kRestartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[149];
const QualifiedNameWithHash& kResultAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[150];
const QualifiedNameWithHash& kRotateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[151];
const QualifiedNameWithHash& kRxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[152];
const QualifiedNameWithHash& kRyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[153];
const QualifiedNameWithHash& kScaleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[154];
const QualifiedNameWithHash& kSeedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[155];
const QualifiedNameWithHash& kShapeRenderingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[156];
const QualifiedNameWithHash& kSideAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[157];
const QualifiedNameWithHash& kSlopeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[158];
const QualifiedNameWithHash& kSpacingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[159];
const QualifiedNameWithHash& kSpecularConstantAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[160];
const QualifiedNameWithHash& kSpecularExponentAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[161];
const QualifiedNameWithHash& kSpreadMethodAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[162];
const QualifiedNameWithHash& kStartOffsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[163];
const QualifiedNameWithHash& kStdDeviationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[164];
const QualifiedNameWithHash& kStitchTilesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[165];
const QualifiedNameWithHash& kStopColorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[166];
const QualifiedNameWithHash& kStopOpacityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[167];
const QualifiedNameWithHash& kStrokeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[168];
const QualifiedNameWithHash& kStrokeDasharrayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[169];
const QualifiedNameWithHash& kStrokeDashoffsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[170];
const QualifiedNameWithHash& kStrokeLinecapAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[171];
const QualifiedNameWithHash& kStrokeLinejoinAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[172];
const QualifiedNameWithHash& kStrokeMiterlimitAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[173];
const QualifiedNameWithHash& kStrokeOpacityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[174];
const QualifiedNameWithHash& kStrokeWidthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[175];
const QualifiedNameWithHash& kStyleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[176];
const QualifiedNameWithHash& kSurfaceScaleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[177];
const QualifiedNameWithHash& kSystemLanguageAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[178];
const QualifiedNameWithHash& kTableValuesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[179];
const QualifiedNameWithHash& kTargetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[180];
const QualifiedNameWithHash& kTargetXAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[181];
const QualifiedNameWithHash& kTargetYAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[182];
const QualifiedNameWithHash& kTextAnchorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[183];
const QualifiedNameWithHash& kTextDecorationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[184];
const QualifiedNameWithHash& kTextOverflowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[185];
const QualifiedNameWithHash& kTextRenderingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[186];
const QualifiedNameWithHash& kTextLengthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[187];
const QualifiedNameWithHash& kTitleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[188];
const QualifiedNameWithHash& kToAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[189];
const QualifiedNameWithHash& kTransformAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[190];
const QualifiedNameWithHash& kTransformOriginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[191];
const QualifiedNameWithHash& kTypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[192];
const QualifiedNameWithHash& kU1Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[193];
const QualifiedNameWithHash& kU2Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[194];
const QualifiedNameWithHash& kUnicodeBidiAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[195];
const QualifiedNameWithHash& kValuesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[196];
const QualifiedNameWithHash& kVectorEffectAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[197];
const QualifiedNameWithHash& kVersionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[198];
const QualifiedNameWithHash& kViewBoxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[199];
const QualifiedNameWithHash& kVisibilityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[200];
const QualifiedNameWithHash& kWhiteSpaceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[201];
const QualifiedNameWithHash& kWidthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[202];
const QualifiedNameWithHash& kWordSpacingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[203];
const QualifiedNameWithHash& kWritingModeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[204];
const QualifiedNameWithHash& kXAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[205];
const QualifiedNameWithHash& kX1Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[206];
const QualifiedNameWithHash& kX2Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[207];
const QualifiedNameWithHash& kXChannelSelectorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[208];
const QualifiedNameWithHash& kYAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[209];
const QualifiedNameWithHash& kY1Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[210];
const QualifiedNameWithHash& kY2Attr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[211];
const QualifiedNameWithHash& kYChannelSelectorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[212];
const QualifiedNameWithHash& kZAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[213];
const QualifiedNameWithHash& kZoomAndPanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[214];

base::HeapArray<const QualifiedName*> GetAttrs() {
  auto attrs = base::HeapArray<const QualifiedName*>::Uninit(kAttrsCount);
  for (size_t i = 0; i < kAttrsCount; ++i) {
    attrs[i] = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage) + i;
  }
  return attrs;
}


void Init() {
  struct NameEntry {
    const char* name;
    unsigned char length;
    unsigned char is_tag;
    unsigned char is_attr;
  };

  // Namespace
  // Use placement new to initialize the globals.
  new ((void*)&kNamespaceURI) AtomicString("http://www.w3.org/2000/svg");

  static constexpr NameEntry kNames[] = {
    { "a", 1, 1, 0 },
    { "accumulate", 10, 0, 1 },
    { "additive", 8, 0, 1 },
    { "alignment-baseline", 18, 0, 1 },
    { "amplitude", 9, 0, 1 },
    { "animate", 7, 1, 1 },
    { "animateColor", 12, 1, 0 },
    { "animateMotion", 13, 1, 0 },
    { "animateTransform", 16, 1, 0 },
    { "async", 5, 0, 1 },
    { "attributeName", 13, 0, 1 },
    { "attributeType", 13, 0, 1 },
    { "autofocus", 9, 0, 1 },
    { "azimuth", 7, 0, 1 },
    { "baseFrequency", 13, 0, 1 },
    { "baseProfile", 11, 0, 1 },
    { "baseline-shift", 14, 0, 1 },
    { "begin", 5, 0, 1 },
    { "bias", 4, 0, 1 },
    { "buffered-rendering", 18, 0, 1 },
    { "by", 2, 0, 1 },
    { "calcMode", 8, 0, 1 },
    { "circle", 6, 1, 0 },
    { "clip", 4, 0, 1 },
    { "clip-path", 9, 0, 1 },
    { "clip-rule", 9, 0, 1 },
    { "clipPath", 8, 1, 0 },
    { "clipPathUnits", 13, 0, 1 },
    { "color", 5, 0, 1 },
    { "color-interpolation", 19, 0, 1 },
    { "color-interpolation-filters", 27, 0, 1 },
    { "color-rendering", 15, 0, 1 },
    { "crossorigin", 11, 0, 1 },
    { "cursor", 6, 0, 1 },
    { "cx", 2, 0, 1 },
    { "cy", 2, 0, 1 },
    { "d", 1, 0, 1 },
    { "decoding", 8, 0, 1 },
    { "defs", 4, 1, 0 },
    { "desc", 4, 1, 0 },
    { "diffuseConstant", 15, 0, 1 },
    { "direction", 9, 0, 1 },
    { "display", 7, 0, 1 },
    { "divisor", 7, 0, 1 },
    { "dominant-baseline", 17, 0, 1 },
    { "download", 8, 0, 1 },
    { "dur", 3, 0, 1 },
    { "dx", 2, 0, 1 },
    { "dy", 2, 0, 1 },
    { "edgeMode", 8, 0, 1 },
    { "elevation", 9, 0, 1 },
    { "ellipse", 7, 1, 0 },
    { "end", 3, 0, 1 },
    { "exponent", 8, 0, 1 },
    { "feBlend", 7, 1, 0 },
    { "feColorMatrix", 13, 1, 0 },
    { "feComponentTransfer", 19, 1, 0 },
    { "feComposite", 11, 1, 0 },
    { "feConvolveMatrix", 16, 1, 0 },
    { "feDiffuseLighting", 17, 1, 0 },
    { "feDisplacementMap", 17, 1, 0 },
    { "feDistantLight", 14, 1, 0 },
    { "feDropShadow", 12, 1, 0 },
    { "feFlood", 7, 1, 0 },
    { "feFuncA", 7, 1, 0 },
    { "feFuncB", 7, 1, 0 },
    { "feFuncG", 7, 1, 0 },
    { "feFuncR", 7, 1, 0 },
    { "feGaussianBlur", 14, 1, 0 },
    { "feImage", 7, 1, 0 },
    { "feMerge", 7, 1, 0 },
    { "feMergeNode", 11, 1, 0 },
    { "feMorphology", 12, 1, 0 },
    { "feOffset", 8, 1, 0 },
    { "fePointLight", 12, 1, 0 },
    { "feSpecularLighting", 18, 1, 0 },
    { "feSpotLight", 11, 1, 0 },
    { "feTile", 6, 1, 0 },
    { "feTurbulence", 12, 1, 0 },
    { "fill", 4, 0, 1 },
    { "fill-opacity", 12, 0, 1 },
    { "fill-rule", 9, 0, 1 },
    { "filter", 6, 1, 1 },
    { "filterUnits", 11, 0, 1 },
    { "flood-color", 11, 0, 1 },
    { "flood-opacity", 13, 0, 1 },
    { "focusgroup", 10, 0, 1 },
    { "font-family", 11, 0, 1 },
    { "font-size", 9, 0, 1 },
    { "font-size-adjust", 16, 0, 1 },
    { "font-stretch", 12, 0, 1 },
    { "font-style", 10, 0, 1 },
    { "font-variant", 12, 0, 1 },
    { "font-weight", 11, 0, 1 },
    { "foreignObject", 13, 1, 0 },
    { "format", 6, 0, 1 },
    { "fr", 2, 0, 1 },
    { "from", 4, 0, 1 },
    { "fx", 2, 0, 1 },
    { "fy", 2, 0, 1 },
    { "g", 1, 1, 0 },
    { "g1", 2, 0, 1 },
    { "g2", 2, 0, 1 },
    { "glyphRef", 8, 0, 1 },
    { "gradientTransform", 17, 0, 1 },
    { "gradientUnits", 13, 0, 1 },
    { "height", 6, 0, 1 },
    { "href", 4, 0, 1 },
    { "hreflang", 8, 0, 1 },
    { "image", 5, 1, 0 },
    { "image-rendering", 15, 0, 1 },
    { "in", 2, 0, 1 },
    { "in2", 3, 0, 1 },
    { "intercept", 9, 0, 1 },
    { "interestfor", 11, 0, 1 },
    { "k", 1, 0, 1 },
    { "k1", 2, 0, 1 },
    { "k2", 2, 0, 1 },
    { "k3", 2, 0, 1 },
    { "k4", 2, 0, 1 },
    { "kernelMatrix", 12, 0, 1 },
    { "kernelUnitLength", 16, 0, 1 },
    { "keyPoints", 9, 0, 1 },
    { "keySplines", 10, 0, 1 },
    { "keyTimes", 8, 0, 1 },
    { "lang", 4, 0, 1 },
    { "lengthAdjust", 12, 0, 1 },
    { "letter-spacing", 14, 0, 1 },
    { "lighting-color", 14, 0, 1 },
    { "limitingConeAngle", 17, 0, 1 },
    { "line", 4, 1, 0 },
    { "linearGradient", 14, 1, 0 },
    { "local", 5, 0, 1 },
    { "marker", 6, 1, 0 },
    { "marker-end", 10, 0, 1 },
    { "marker-mid", 10, 0, 1 },
    { "marker-start", 12, 0, 1 },
    { "markerHeight", 12, 0, 1 },
    { "markerUnits", 11, 0, 1 },
    { "markerWidth", 11, 0, 1 },
    { "mask", 4, 1, 1 },
    { "mask-type", 9, 0, 1 },
    { "maskContentUnits", 16, 0, 1 },
    { "maskUnits", 9, 0, 1 },
    { "max", 3, 0, 1 },
    { "media", 5, 0, 1 },
    { "metadata", 8, 1, 0 },
    { "method", 6, 0, 1 },
    { "min", 3, 0, 1 },
    { "mode", 4, 0, 1 },
    { "mpath", 5, 1, 0 },
    { "name", 4, 0, 1 },
    { "numOctaves", 10, 0, 1 },
    { "offset", 6, 0, 1 },
    { "onactivate", 10, 0, 1 },
    { "onbegin", 7, 0, 1 },
    { "onend", 5, 0, 1 },
    { "onfocusin", 9, 0, 1 },
    { "onfocusout", 10, 0, 1 },
    { "onrepeat", 8, 0, 1 },
    { "opacity", 7, 0, 1 },
    { "operator", 8, 0, 1 },
    { "order", 5, 0, 1 },
    { "orient", 6, 0, 1 },
    { "origin", 6, 0, 1 },
    { "overflow", 8, 0, 1 },
    { "paint-order", 11, 0, 1 },
    { "path", 4, 1, 1 },
    { "pathLength", 10, 0, 1 },
    { "pattern", 7, 1, 0 },
    { "patternContentUnits", 19, 0, 1 },
    { "patternTransform", 16, 0, 1 },
    { "patternUnits", 12, 0, 1 },
    { "ping", 4, 0, 1 },
    { "pointer-events", 14, 0, 1 },
    { "points", 6, 0, 1 },
    { "pointsAtX", 9, 0, 1 },
    { "pointsAtY", 9, 0, 1 },
    { "pointsAtZ", 9, 0, 1 },
    { "polygon", 7, 1, 0 },
    { "polyline", 8, 1, 0 },
    { "preserveAlpha", 13, 0, 1 },
    { "preserveAspectRatio", 19, 0, 1 },
    { "primitiveUnits", 14, 0, 1 },
    { "r", 1, 0, 1 },
    { "radialGradient", 14, 1, 0 },
    { "radius", 6, 0, 1 },
    { "rect", 4, 1, 0 },
    { "refX", 4, 0, 1 },
    { "refY", 4, 0, 1 },
    { "referrerpolicy", 14, 0, 1 },
    { "rel", 3, 0, 1 },
    { "repeatCount", 11, 0, 1 },
    { "repeatDur", 9, 0, 1 },
    { "requiredExtensions", 18, 0, 1 },
    { "requiredFeatures", 16, 0, 1 },
    { "restart", 7, 0, 1 },
    { "result", 6, 0, 1 },
    { "rotate", 6, 0, 1 },
    { "rx", 2, 0, 1 },
    { "ry", 2, 0, 1 },
    { "scale", 5, 0, 1 },
    { "script", 6, 1, 0 },
    { "seed", 4, 0, 1 },
    { "set", 3, 1, 0 },
    { "shape-rendering", 15, 0, 1 },
    { "side", 4, 0, 1 },
    { "slope", 5, 0, 1 },
    { "spacing", 7, 0, 1 },
    { "specularConstant", 16, 0, 1 },
    { "specularExponent", 16, 0, 1 },
    { "spreadMethod", 12, 0, 1 },
    { "startOffset", 11, 0, 1 },
    { "stdDeviation", 12, 0, 1 },
    { "stitchTiles", 11, 0, 1 },
    { "stop", 4, 1, 0 },
    { "stop-color", 10, 0, 1 },
    { "stop-opacity", 12, 0, 1 },
    { "stroke", 6, 0, 1 },
    { "stroke-dasharray", 16, 0, 1 },
    { "stroke-dashoffset", 17, 0, 1 },
    { "stroke-linecap", 14, 0, 1 },
    { "stroke-linejoin", 15, 0, 1 },
    { "stroke-miterlimit", 17, 0, 1 },
    { "stroke-opacity", 14, 0, 1 },
    { "stroke-width", 12, 0, 1 },
    { "style", 5, 1, 1 },
    { "surfaceScale", 12, 0, 1 },
    { "svg", 3, 1, 0 },
    { "switch", 6, 1, 0 },
    { "symbol", 6, 1, 0 },
    { "systemLanguage", 14, 0, 1 },
    { "tableValues", 11, 0, 1 },
    { "target", 6, 0, 1 },
    { "targetX", 7, 0, 1 },
    { "targetY", 7, 0, 1 },
    { "text", 4, 1, 0 },
    { "text-anchor", 11, 0, 1 },
    { "text-decoration", 15, 0, 1 },
    { "text-overflow", 13, 0, 1 },
    { "text-rendering", 14, 0, 1 },
    { "textLength", 10, 0, 1 },
    { "textPath", 8, 1, 0 },
    { "title", 5, 1, 1 },
    { "to", 2, 0, 1 },
    { "transform", 9, 0, 1 },
    { "transform-origin", 16, 0, 1 },
    { "tspan", 5, 1, 0 },
    { "type", 4, 0, 1 },
    { "u1", 2, 0, 1 },
    { "u2", 2, 0, 1 },
    { "unicode-bidi", 12, 0, 1 },
    { "use", 3, 1, 0 },
    { "values", 6, 0, 1 },
    { "vector-effect", 13, 0, 1 },
    { "version", 7, 0, 1 },
    { "view", 4, 1, 0 },
    { "viewBox", 7, 0, 1 },
    { "visibility", 10, 0, 1 },
    { "white-space", 11, 0, 1 },
    { "width", 5, 0, 1 },
    { "word-spacing", 12, 0, 1 },
    { "writing-mode", 12, 0, 1 },
    { "x", 1, 0, 1 },
    { "x1", 2, 0, 1 },
    { "x2", 2, 0, 1 },
    { "xChannelSelector", 16, 0, 1 },
    { "y", 1, 0, 1 },
    { "y1", 2, 0, 1 },
    { "y2", 2, 0, 1 },
    { "yChannelSelector", 16, 0, 1 },
    { "z", 1, 0, 1 },
    { "zoomAndPan", 10, 0, 1 },
  };

  size_t tag_i = 0;
  size_t attr_i = 0;
  for (const NameEntry& name : kNames) {
    StringImpl* impl = StringImpl::CreateStatic(base::span(name.name, name.length));

    // We need a static version of the uppercase string, since the QualifiedNameWithHash
    // constructor will call LocalNameUpper(), and we cannot insert non-static strings
    // before we are done inserting static strings.
    char upper_buf[256];
    for (unsigned i = 0; i < name.length; ++i) {
      CHECK_LT(i, sizeof(upper_buf));
      upper_buf[i] = ToAsciiUpper(name.name[i]);
    }
    AtomicString upper(StringImpl::CreateStatic(base::span(upper_buf, name.length)));

    if (name.is_tag) {
      void* address = reinterpret_cast<SVGQualifiedName*>(&tag_storage) + tag_i;
      QualifiedNameWithHash::CreateStatic(address, impl, kNamespaceURI);
      ++tag_i;
    }

    if (!name.is_attr)
      continue;
    void* address = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage) + attr_i;
    QualifiedNameWithHash::CreateStatic(address, impl);
    ++attr_i;
  }
  DCHECK_EQ(tag_i, kTagsCount);
  DCHECK_EQ(attr_i, kAttrsCount);
}


}  // namespace svg_names
}  // namespace blink
