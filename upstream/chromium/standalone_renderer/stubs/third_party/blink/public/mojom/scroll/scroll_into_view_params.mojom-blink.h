// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_INTO_VIEW_PARAMS_MOJOM_BLINK_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_INTO_VIEW_PARAMS_MOJOM_BLINK_H_

#include <memory>

#include "third_party/blink/public/mojom/scroll/scroll_enums.mojom-blink.h"
#include "ui/gfx/geometry/size_f.h"
#include "ui/gfx/geometry/vector2d_f.h"

namespace blink::mojom::blink {

struct ScrollAlignment {
  enum class Behavior {
    kNoScroll = 0,
    kCenter,
    kTop,
    kBottom,
    kLeft,
    kRight,
    kClosestEdge,
  };
  Behavior rect_visible = Behavior::kNoScroll;
  Behavior rect_hidden = Behavior::kCenter;
  Behavior rect_partial = Behavior::kClosestEdge;

  ScrollAlignment() = default;
  ScrollAlignment(Behavior visible, Behavior hidden, Behavior partial)
      : rect_visible(visible), rect_hidden(hidden), rect_partial(partial) {}

  static std::unique_ptr<ScrollAlignment> New() {
    return std::make_unique<ScrollAlignment>();
  }
  static std::unique_ptr<ScrollAlignment> New(const ScrollAlignment& value) {
    return std::make_unique<ScrollAlignment>(value);
  }
};
using ScrollAlignmentPtr = std::unique_ptr<ScrollAlignment>;

struct FocusedEditableParams {
  gfx::Vector2dF relative_location;
  gfx::SizeF size;
  bool can_zoom = true;
};
using FocusedEditableParamsPtr = std::unique_ptr<FocusedEditableParams>;

struct ScrollIntoViewParams {
  ScrollAlignmentPtr align_x = std::make_unique<ScrollAlignment>();
  ScrollAlignmentPtr align_y = std::make_unique<ScrollAlignment>();
  ScrollType type = ScrollType::kProgrammatic;
  bool make_visible_in_visual_viewport = true;
  ScrollBehavior behavior = ScrollBehavior::kAuto;
  bool is_for_scroll_sequence = false;
  FocusedEditableParamsPtr for_focused_editable;
  bool cross_origin_boundaries = true;

  static std::unique_ptr<ScrollIntoViewParams> New() {
    return std::make_unique<ScrollIntoViewParams>();
  }
};
using ScrollIntoViewParamsPtr = std::unique_ptr<ScrollIntoViewParams>;

}  // namespace blink::mojom::blink

namespace blink::mojom {

using ScrollAlignment_Behavior = ::blink::mojom::blink::ScrollAlignment::Behavior;

}  // namespace blink::mojom

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCROLL_SCROLL_INTO_VIEW_PARAMS_MOJOM_BLINK_H_
