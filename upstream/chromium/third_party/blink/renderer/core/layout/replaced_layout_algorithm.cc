// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/layout/replaced_layout_algorithm.h"

#include <cstdio>

#include "third_party/blink/renderer/core/layout/constraint_space.h"
#include "third_party/blink/renderer/core/layout/constraint_space_builder.h"
#include "third_party/blink/renderer/core/layout/geometry/writing_mode_converter.h"
#include "third_party/blink/renderer/core/layout/layout_box.h"
#include "third_party/blink/renderer/core/layout/layout_image_replacement.h"
#include "third_party/blink/renderer/core/layout/layout_replaced.h"
#include "third_party/blink/renderer/core/layout/layout_video.h"
#include "third_party/blink/renderer/platform/geometry/layout_unit.h"

namespace blink {

ReplacedLayoutAlgorithm::ReplacedLayoutAlgorithm(
    const LayoutAlgorithmParams& params)
    : LayoutAlgorithm(params) {
  DCHECK(params.space.IsNewFormattingContext());
}

const LayoutResult* ReplacedLayoutAlgorithm::Layout() {
  DCHECK(!GetBreakToken() || GetBreakToken()->IsBreakBefore());
#if defined(HTML_CSS_RENDERER_STANDALONE) && \
    defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
  std::fprintf(stderr,
               "image_reachability.stage=replaced_layout_algorithm_enter "
               "box=%p is_image=%d is_media=%d is_image_replacement=%d\n",
               static_cast<const void*>(Node().GetLayoutBox()),
               Node().GetLayoutBox() && Node().GetLayoutBox()->IsLayoutImage(),
               Node().IsMedia(), Node().IsImageReplacement());
  std::fflush(stderr);
#endif

  if (Node().IsMedia()) {
    LayoutMediaChildren();
  } else if (Node().IsCanvas() &&
             RuntimeEnabledFeatures::CanvasDrawElementEnabled(
                 Node().GetDocument().GetExecutionContext())) {
    LayoutCanvasChildren();
  } else if (Node().IsImageReplacement()) {
    LayoutImageReplacementChildren();
  }

  const LayoutResult* result = container_builder_.ToBoxFragment();
#if defined(HTML_CSS_RENDERER_STANDALONE) && \
    defined(HTML_CSS_RENDERER_ENABLE_REAL_BLINK_IMAGE_PNG)
  std::fprintf(stderr,
               "image_reachability.stage=replaced_layout_algorithm_exit "
               "box=%p result=%p\n",
               static_cast<const void*>(Node().GetLayoutBox()),
               static_cast<const void*>(result));
  std::fflush(stderr);
#endif
  return result;
}

MinMaxSizesResult ReplacedLayoutAlgorithm::ComputeMinMaxSizes(
    const MinMaxSizesFloatInput&) {
  NOTREACHED();
}

// This is necessary for CanvasRenderingContext2D.drawElementImage().
void ReplacedLayoutAlgorithm::LayoutCanvasChildren() {
  for (LayoutInputNode child = Node().FirstChild(); child;
       child = child.NextSibling()) {
    DCHECK(!child.IsFloating());
    DCHECK(!child.IsOutOfFlowPositioned());

    ConstraintSpaceBuilder space_builder(GetConstraintSpace().GetWritingMode(),
                                         child.Style().GetWritingDirection(),
                                         /* is_new_fc= */ true);

    space_builder.SetAvailableSize(ChildAvailableSize());
    space_builder.SetPercentageResolutionSize(ChildAvailableSize());
    space_builder.SetIsPaintedAtomically(true);

    const LayoutResult* result =
        To<BlockNode>(child).Layout(space_builder.ToConstraintSpace());
    // Since this only works with drawElementImage(), we ignore relative
    // placement and put the element at (0,0) because it will be drawn
    // explicitly by the user.
    container_builder_.AddResult(*result,
                                 LogicalOffset(LayoutUnit(), LayoutUnit()));
  }
}

void ReplacedLayoutAlgorithm::LayoutMediaChildren() {
  WritingModeConverter converter(GetConstraintSpace().GetWritingDirection(),
                                 container_builder_.Size());
  LogicalRect logical_new_rect(
      BorderPadding().StartOffset(),
      ShrinkLogicalSize(container_builder_.Size(), BorderPadding()));
  PhysicalRect new_rect = converter.ToPhysical(logical_new_rect);

  for (LayoutInputNode child = Node().FirstChild(); child;
       child = child.NextSibling()) {
    LayoutUnit width = new_rect.Width();
    if (child.GetDOMNode()->IsMediaControls()) {
      width =
          To<LayoutMedia>(Node().GetLayoutBox())->ComputePanelWidth(new_rect);
    }

    ConstraintSpaceBuilder space_builder(GetConstraintSpace().GetWritingMode(),
                                         child.Style().GetWritingDirection(),
                                         /* is_new_fc */ true);
    LogicalSize child_size =
        converter.ToLogical(PhysicalSize(width, new_rect.Height()));
    space_builder.SetAvailableSize(child_size);
    space_builder.SetIsFixedInlineSize(true);
    space_builder.SetIsFixedBlockSize(true);

    const LayoutResult* result =
        To<BlockNode>(child).Layout(space_builder.ToConstraintSpace());
    LogicalOffset offset = converter.ToLogical(
        new_rect.offset, result->GetPhysicalFragment().Size());
    container_builder_.AddResult(*result, offset);
  }
}

void ReplacedLayoutAlgorithm::LayoutImageReplacementChildren() {
  // LayoutImageReplacement should only have one child (the replacement iframe's
  // layout node).
  CHECK(Node().FirstChild());
  CHECK(!Node().FirstChild().NextSibling());
  const BlockNode child = To<BlockNode>(Node().FirstChild());

  ConstraintSpaceBuilder space_builder(GetConstraintSpace().GetWritingMode(),
                                       child.Style().GetWritingDirection(),
                                       /* is_new_fc */ true);
  space_builder.SetAvailableSize(ChildAvailableSize());
  space_builder.SetIsFixedInlineSize(true);
  space_builder.SetIsFixedBlockSize(true);

  const LayoutResult* result = child.Layout(space_builder.ToConstraintSpace());
  container_builder_.AddResult(*result, BorderPadding().StartOffset());
}

}  // namespace blink
