// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#if defined(BLINK_STANDALONE_USE_REAL_SVG_SVG_ELEMENT)
#include_next "third_party/blink/renderer/core/svg/svg_svg_element.h"
#else

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_SVG_ELEMENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_SVG_ELEMENT_H_

#include "third_party/blink/renderer/core/svg/svg_element.h"

namespace blink {

class SVGSVGElement final : public SVGElement {
 public:
  using SVGElement::SVGElement;
  bool IsOutermostSVGSVGElement() const { return false; }
};

template <>
struct DowncastTraits<SVGSVGElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_SVG_ELEMENT_H_

#endif  // defined(BLINK_STANDALONE_USE_REAL_SVG_SVG_ELEMENT)
