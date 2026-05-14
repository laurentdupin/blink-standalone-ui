// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_A_ELEMENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_A_ELEMENT_H_

#include "third_party/blink/renderer/core/svg/svg_graphics_element.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace blink {

class Document;

class SVGAElement final : public SVGGraphicsElement {
 public:
  using SVGGraphicsElement::SVGGraphicsElement;
  KURL LegacyHrefURL(const Document&) const { return KURL(); }
};

template <>
struct DowncastTraits<SVGAElement> {
  static bool AllowFrom(const Element&) { return false; }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_A_ELEMENT_H_
