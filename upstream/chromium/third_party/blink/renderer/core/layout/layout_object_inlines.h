// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_LAYOUT_LAYOUT_OBJECT_INLINES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_LAYOUT_LAYOUT_OBJECT_INLINES_H_

#include "third_party/blink/renderer/core/css/style_engine.h"
#include "third_party/blink/renderer/core/inspector/inspector_trace_events.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"

#if defined(HTML_CSS_RENDERER_STANDALONE)
#include <cstdio>
#endif

namespace blink {

// The following methods are inlined for performance but not put in
// layout_object.h because that would unnecessarily tie layout_object.h
// to style_engine.h and inspector_trace_events.h for all users of
// layout_object.h that don't use these methods.

inline const ComputedStyle* LayoutObject::FirstLineStyle() const {
  NOT_DESTROYED();
#if defined(HTML_CSS_RENDERER_STANDALONE)
  return Style();
#else
  if (GetDocument().GetStyleEngine().UsesFirstLineRules()) {
    if (const ComputedStyle* first_line_style = FirstLineStyleWithoutFallback())
      return first_line_style;
  }
  return Style();
#endif
}

inline const ComputedStyle& LayoutObject::FirstLineStyleRef() const {
  NOT_DESTROYED();
  const ComputedStyle* style = FirstLineStyle();
  CHECK(style);
  return *style;
}

inline const ComputedStyle* LayoutObject::Style(bool first_line) const {
  NOT_DESTROYED();
  return first_line ? FirstLineStyle() : Style();
}

inline const ComputedStyle& LayoutObject::StyleRef(bool first_line) const {
  NOT_DESTROYED();
  const ComputedStyle* style = Style(first_line);
  CHECK(style);
  return *style;
}

// SetNeedsLayout() won't cause full paint invalidations as
// SetNeedsLayoutAndFullPaintInvalidation() does. Otherwise the two methods are
// identical.
inline void LayoutObject::SetNeedsLayout(
    LayoutInvalidationReasonForTracing reason,
    MarkingBehavior mark_parents) {
  NOT_DESTROYED();
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
#if DCHECK_IS_ON()
  DCHECK(!IsSetNeedsLayoutForbidden());
#endif
  bool already_needed_layout = bitfields_.SelfNeedsFullLayout();
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
  SetSelfNeedsFullLayout(true);
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
  SetNeedsOverflowRecalc();
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
  SetSubgridMinMaxSizesCacheDirty(true);
  SetTableColumnConstraintDirty(true);
  if (!already_needed_layout) {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
    DEVTOOLS_TIMELINE_TRACE_EVENT_INSTANT_WITH_CATEGORIES(
        TRACE_DISABLED_BY_DEFAULT("devtools.timeline.invalidationTracking"),
        "LayoutInvalidationTracking",
        inspector_layout_invalidation_tracking_event::Data, this, reason);
#endif
    if (mark_parents == kMarkContainerChain) {
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
      MarkContainerChainForLayout();
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
    }
  }
#if defined(HTML_CSS_RENDERER_STANDALONE)
#endif
}

inline void LayoutObject::SetNeedsLayoutAndFullPaintInvalidation(
    LayoutInvalidationReasonForTracing reason,
    MarkingBehavior mark_parents) {
  NOT_DESTROYED();
  SetNeedsLayout(reason, mark_parents);
  SetShouldDoFullPaintInvalidation();
}

inline void LayoutObject::SetNeedsLayoutAndIntrinsicWidthsRecalc(
    LayoutInvalidationReasonForTracing reason) {
  NOT_DESTROYED();
  SetNeedsLayout(reason);
  SetIntrinsicLogicalWidthsDirty();
}

inline void
LayoutObject::SetNeedsLayoutAndIntrinsicWidthsRecalcAndFullPaintInvalidation(
    LayoutInvalidationReasonForTracing reason) {
  NOT_DESTROYED();
  SetNeedsLayoutAndFullPaintInvalidation(reason);
  SetIntrinsicLogicalWidthsDirty();
}

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_LAYOUT_LAYOUT_OBJECT_INLINES_H_
