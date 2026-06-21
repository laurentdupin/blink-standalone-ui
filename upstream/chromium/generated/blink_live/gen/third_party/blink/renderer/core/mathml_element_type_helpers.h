// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/element_type_helpers.h.tmpl
// and input files:
//   upstream\chromium\third_party\blink\renderer\core\mathml\mathml_tag_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_ELEMENT_TYPE_HELPERS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_ELEMENT_TYPE_HELPERS_H_

#include "third_party/blink/renderer/core/mathml/mathml_element.h"
#include "third_party/blink/renderer/core/mathml_names.h"
#include "third_party/blink/renderer/core/element_type_enum.h"

namespace blink {

class Document;

// Type checking.
class MathMLFractionElement;
template <>
struct DowncastTraits<MathMLFractionElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kMathMLFractionElement;
  }
};

class MathMLOperatorElement;
template <>
struct DowncastTraits<MathMLOperatorElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kMathMLOperatorElement;
  }
};

class MathMLPaddedElement;
template <>
struct DowncastTraits<MathMLPaddedElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kMathMLPaddedElement;
  }
};

class MathMLSpaceElement;
template <>
struct DowncastTraits<MathMLSpaceElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kMathMLSpaceElement;
  }
};

class MathMLTableCellElement;
template <>
struct DowncastTraits<MathMLTableCellElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kMathMLTableCellElement;
  }
};


}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_ELEMENT_TYPE_HELPERS_H_
