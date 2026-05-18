// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_AREA_ELEMENT_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_AREA_ELEMENT_H_

#include "third_party/blink/renderer/core/html/html_anchor_element.h"
#include "third_party/blink/renderer/platform/geometry/path.h"

namespace blink {

class HTMLImageElement;
class LayoutObject;

class HTMLAreaElement final : public HTMLAnchorElementBase {
 public:
  using HTMLAnchorElementBase::HTMLAnchorElementBase;
  Path GetPath(const LayoutObject*,
               float zoom_factor = 1,
               const gfx::SizeF& default_length = gfx::SizeF()) const {
    return Path();
  }
  Path GetPath(const LayoutObject*, const gfx::Vector2dF&) const {
    return Path();
  }
  HTMLImageElement* ImageElement() const { return nullptr; }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_HTML_HTML_AREA_ELEMENT_H_
