// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 keeps static image rendering but does not import anchor/navigation
// or image-map interactivity. Layout/paint only need these methods for image
// map focus-ring handling, so return inert values instead of pulling the full
// HTMLAreaElement/HTMLAnchorElementBase runtime.

#include "third_party/blink/renderer/core/html/html_area_element.h"

#include "third_party/blink/renderer/platform/geometry/path.h"

namespace blink {

HTMLImageElement* HTMLAreaElement::ImageElement() const {
  return nullptr;
}

Path HTMLAreaElement::GetPath(const LayoutObject*,
                              const gfx::Vector2dF&) const {
  return Path();
}

}  // namespace blink
