// Copyright 2023 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_MATHML_TABLE_CELL_ELEMENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_MATHML_TABLE_CELL_ELEMENT_H_

#include "third_party/blink/renderer/core/mathml/mathml_element.h"
#include "third_party/blink/renderer/core/mathml_names.h"

namespace blink {

class CORE_EXPORT MathMLTableCellElement final : public MathMLElement {
 public:
  explicit MathMLTableCellElement(Document&);
  ElementType GetElementType() const final {
    return ElementType::kMathMLTableCellElement;
  }

  unsigned colSpan() const;
  unsigned rowSpan() const;

 private:
  void ParseAttribute(const AttributeModificationParams&) final;
  LayoutObject* CreateLayoutObject(const ComputedStyle&) final;
};

template <>
struct DowncastTraits<MathMLTableCellElement> {
  static bool AllowFrom(const Node& node) {
    auto* mathml_element = DynamicTo<MathMLElement>(node);
    return mathml_element && AllowFrom(*mathml_element);
  }
  static bool AllowFrom(const MathMLElement& mathml_element) {
    return mathml_element.HasTagName(mathml_names::kMtdTag);
  }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_MATHML_MATHML_TABLE_CELL_ELEMENT_H_
