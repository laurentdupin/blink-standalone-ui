// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_FOREIGN_OBJECT_ELEMENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_FOREIGN_OBJECT_ELEMENT_H_

#include "third_party/blink/renderer/core/svg/svg_element.h"

namespace blink {

class SVGForeignObjectElement final : public SVGElement {
 public:
  using SVGElement::SVGElement;
};

template <>
struct DowncastTraits<SVGForeignObjectElement> {
  static bool AllowFrom(const Node&) { return false; }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_FOREIGN_OBJECT_ELEMENT_H_
