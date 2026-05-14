// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.h.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\mathml\mathml_attribute_names.json5
//   ..\..\third_party\blink\renderer\core\mathml\mathml_tag_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_NAMES_H_

#include "base/containers/heap_array.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/qualified_name.h"

namespace blink {

class MathMLQualifiedName : public QualifiedNameWithHash { };

namespace mathml_names {

// Namespace
CORE_EXPORT extern const AtomicString& kNamespaceURI;

// Tags


CORE_EXPORT extern const blink::MathMLQualifiedName& kAnnotationTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kAnnotationXmlTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMactionTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMalignmarkTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMathTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMerrorTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMfracTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMglyphTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMiTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMmultiscriptsTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMnTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMoTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMoverTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMpaddedTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMphantomTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMprescriptsTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMrootTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMrowTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMsTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMspaceTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMsqrtTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMstyleTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMsubTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMsubsupTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMsupTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMtableTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMtdTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMtextTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMtrTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMunderTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kMunderoverTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kNoneTag;
CORE_EXPORT extern const blink::MathMLQualifiedName& kSemanticsTag;

// Attributes
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAccentAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kAccentunderAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kColumnspanAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDefinitionURLAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDepthAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDisplayAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kDisplaystyleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kEncodingAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFenceAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kFormAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kHeightAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLargeopAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLinethicknessAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLspaceAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMathbackgroundAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMathcolorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMathsizeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMathvariantAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMaxsizeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMinsizeAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kMovablelimitsAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRowspanAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRspaceAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kScriptlevelAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSeparatorAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kStretchyAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSymmetricAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kVoffsetAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kWidthAttr;

constexpr unsigned kTagsCount = 33;
CORE_EXPORT base::HeapArray<const QualifiedName*> GetTags();

constexpr unsigned kAttrsCount = 29;
CORE_EXPORT base::HeapArray<const QualifiedName*> GetAttrs();


void Init();

}  // namespace mathml_names
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_NAMES_H_
