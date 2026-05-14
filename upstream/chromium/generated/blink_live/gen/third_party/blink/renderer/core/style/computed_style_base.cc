// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   core/style/templates/computed_style_base.cc.tmpl
// and input files:
//   ../../third_party/blink/renderer/core/css/computed_style_field_aliases.json5
//   ../../third_party/blink/renderer/core/css/css_group_config.json5
//   ../../third_party/blink/renderer/core/css/css_properties.json5
//   ../../third_party/blink/renderer/core/css/css_value_keywords.json5
//   ../../third_party/blink/renderer/core/style/computed_style_extra_fields.json5
//   ../../third_party/blink/renderer/platform/runtime_enabled_features.json5


#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/computed_style_base.h"
#include "third_party/blink/renderer/core/style/content_data.h"  // For the logging operator to be visible.
#include "third_party/blink/renderer/platform/wtf/size_assertions.h"

#include <utility>

namespace blink {

// Constructor and destructor are protected so that only the parent class ComputedStyle
// can instantiate this class.
ComputedStyleBase::ComputedStyleBase() :
    misc_inherited_data_(StyleMiscInheritedData::Create())
    , misc_data_(StyleMiscData::Create())
    , inherited_data_(StyleInheritedData::Create())
    , visual_data_(StyleVisualData::Create())
    , svginherited_data_(StyleSvginheritedData::Create())
    , box_data_(StyleBoxData::Create())
    , svg_data_(StyleSVGData::Create())
    , surround_data_(StyleSurroundData::Create())
    , background_data_(StyleBackgroundData::Create())
    , base_data_(nullptr)
  , data_{
    static_cast<unsigned>(kPseudoIdNone) // pseudo_element_styles_
    , static_cast<unsigned>(EDisplay::kInline) // display_
    , static_cast<unsigned>(false) // affected_by_active_
    , static_cast<unsigned>(PseudoId::kPseudoIdNone) // style_type_
    , static_cast<unsigned>(static_cast<unsigned>(EVerticalAlign::kBaseline)) // vertical_align_
    , static_cast<unsigned>(EClear::kNone) // clear_
    , static_cast<unsigned>(EFloat::kNone) // floating_
    , static_cast<unsigned>(EOverflow::kVisible) // overflow_x_
    , static_cast<unsigned>(EOverflow::kVisible) // overflow_y_
    , static_cast<unsigned>(EPosition::kStatic) // position_
    , static_cast<unsigned>(ETransformBox::kViewBox) // transform_box_
    , static_cast<unsigned>(UnicodeBidi::kNormal) // unicode_bidi_
    , static_cast<unsigned>(false) // affected_by_drag_
    , static_cast<unsigned>(EContentVisibility::kVisible) // content_visibility_
    , static_cast<unsigned>(EInlineBlockBaselineEdge::kMarginBox) // inline_block_baseline_edge_
    , static_cast<unsigned>(0) // is_stacking_context_without_containment_
    , static_cast<unsigned>(EOverflowAnchor::kAuto) // overflow_anchor_
    , static_cast<unsigned>(0) // viewport_unit_flags_
    , static_cast<unsigned>(false) // affected_by_focus_within_
    , static_cast<unsigned>(false) // affected_by_hover_
    , static_cast<unsigned>(false) // allows_z_index_
    , static_cast<unsigned>(true) // border_collapse_is_inherited_
    , static_cast<unsigned>(EBoxDirection::kNormal) // box_direction_
    , static_cast<unsigned>(EBoxSizing::kContentBox) // box_sizing_
    , static_cast<unsigned>(true) // caption_side_is_inherited_
    , static_cast<unsigned>(false) // child_has_explicit_inheritance_
    , static_cast<unsigned>(true) // color_is_inherited_
    , static_cast<unsigned>(true) // cursor_is_inherited_
    , static_cast<unsigned>(false) // custom_style_callback_depends_on_font_
    , static_cast<unsigned>(true) // empty_cells_is_inherited_
    , static_cast<unsigned>(false) // forces_stacking_context_
    , static_cast<unsigned>(false) // has_attr_function_
    , static_cast<unsigned>(false) // has_author_background_
    , static_cast<unsigned>(false) // has_author_border_
    , static_cast<unsigned>(false) // has_author_border_radius_
    , static_cast<unsigned>(false) // has_author_highlight_colors_
    , static_cast<unsigned>(false) // has_container_relative_value_
    , static_cast<unsigned>(false) // has_em_units_
    , static_cast<unsigned>(false) // has_env_
    , static_cast<unsigned>(false) // has_explicit_inheritance_
    , static_cast<unsigned>(false) // has_glyph_relative_units_
    , static_cast<unsigned>(false) // has_logical_direction_relative_units_
    , static_cast<unsigned>(false) // has_root_font_relative_units_
    , static_cast<unsigned>(false) // has_variable_declaration_
    , static_cast<unsigned>(false) // has_variable_reference_
    , static_cast<unsigned>(true) // interactivity_is_inherited_
    , static_cast<unsigned>(true) // is_css_inert_is_inherited_
    , static_cast<unsigned>(false) // is_ensured_in_display_none_
    , static_cast<unsigned>(false) // is_flex_or_grid_or_custom_item_
    , static_cast<unsigned>(true) // is_html_inert_is_inherited_
    , static_cast<unsigned>(false) // is_in_blockifying_display_
    , static_cast<unsigned>(false) // is_in_inlinifying_display_
    , static_cast<unsigned>(false) // is_inside_display_ignoring_floating_children_
    , static_cast<unsigned>(false) // is_link_
    , static_cast<unsigned>(true) // is_original_display_inline_type_
    , static_cast<unsigned>(false) // is_page_margin_box_
    , static_cast<unsigned>(true) // list_style_position_is_inherited_
    , static_cast<unsigned>(EOriginTrialTestProperty::kNormal) // origin_trial_test_property_
    , static_cast<unsigned>(true) // pointer_events_is_inherited_
    , static_cast<unsigned>(true) // rtl_ordering_is_inherited_
    , static_cast<unsigned>(EScrollSnapStop::kNormal) // scroll_snap_stop_
    , static_cast<unsigned>(false) // should_ignore_overflow_property_for_inline_block_baseline_
    , static_cast<unsigned>(false) // skips_contents_
    , static_cast<unsigned>(ETableLayout::kAuto) // table_layout_
    , static_cast<unsigned>(true) // text_transform_is_inherited_
    , static_cast<unsigned>(true) // visibility_is_inherited_
    , static_cast<unsigned>(EPointerEvents::kAuto) // pointer_events_
    , static_cast<unsigned>(ECaretShape::kAuto) // caret_shape_
    , static_cast<unsigned>(ETextAlign::kStart) // text_align_
    , static_cast<unsigned>(WritingMode::kHorizontalTb) // writing_mode_
    , static_cast<unsigned>(EInsideLink::kNotInsideLink) // inside_link_
    , static_cast<unsigned>(TextWrapStyle::kAuto) // text_wrap_style_
    , static_cast<unsigned>(EVisibility::kVisible) // visibility_
    , static_cast<unsigned>(WhiteSpaceCollapse::kCollapse) // white_space_collapse_
    , static_cast<unsigned>(EBorderCollapse::kSeparate) // border_collapse_
    , static_cast<unsigned>(ECaptionSide::kTop) // caption_side_
    , static_cast<unsigned>(ECaretAnimation::kAuto) // caret_animation_
    , static_cast<unsigned>(false) // color_scheme_flags_is_normal_
    , static_cast<unsigned>(false) // color_scheme_forced_
    , static_cast<unsigned>(false) // dark_color_scheme_
    , static_cast<unsigned>(TextDirection::kLtr) // direction_
    , static_cast<unsigned>(false) // is_css_inert_
    , static_cast<unsigned>(false) // is_ensured_outside_flat_tree_
    , static_cast<unsigned>(false) // is_html_inert_
    , static_cast<unsigned>(EListStylePosition::kOutside) // list_style_position_
    , static_cast<unsigned>(false) // prefers_default_scrollbar_styles_
    , static_cast<unsigned>(EPrintColorAdjust::kEconomy) // print_color_adjust_
    , static_cast<unsigned>(EOrder::kLogical) // rtl_ordering_
    , static_cast<unsigned>(TextWrapMode::kWrap) // text_wrap_mode_
  }
{
}

// These const_casts are quite safe, since ComputedStyle[Base] is immutable.
ComputedStyleBase::ComputedStyleBase(const ComputedStyleBuilderBase& builder) :
    misc_inherited_data_(const_cast<StyleMiscInheritedData*>(builder.misc_inherited_data_))
    , misc_data_(const_cast<StyleMiscData*>(builder.misc_data_))
    , inherited_data_(const_cast<StyleInheritedData*>(builder.inherited_data_))
    , visual_data_(const_cast<StyleVisualData*>(builder.visual_data_))
    , svginherited_data_(const_cast<StyleSvginheritedData*>(builder.svginherited_data_))
    , box_data_(const_cast<StyleBoxData*>(builder.box_data_))
    , svg_data_(const_cast<StyleSVGData*>(builder.svg_data_))
    , surround_data_(const_cast<StyleSurroundData*>(builder.surround_data_))
    , background_data_(const_cast<StyleBackgroundData*>(builder.background_data_))
    , base_data_(builder.base_data_)
    , data_(builder.data_)
  {
    // Reset derived flags:
    data_.is_stacking_context_without_containment_ = 0;
  }


Vector<std::pair<String, size_t>>
ComputedStyleBase::FindChangedGroups(const ComputedStyleBase &other_style) const {
  Vector<std::pair<String, size_t>> output;
    if (!base::ValuesEquivalent(misc_inherited_data_,
      other_style.misc_inherited_data_)) {
    output.emplace_back("misc_inherited_data_",
        sizeof(*misc_inherited_data_));
  }
  if (!base::ValuesEquivalent(misc_inherited_data_->misc_inherited_1_data_,
      other_style.misc_inherited_data_->misc_inherited_1_data_)) {
    output.emplace_back("misc_inherited_data_->misc_inherited_1_data_",
        sizeof(*misc_inherited_data_->misc_inherited_1_data_));
  }
  if (!base::ValuesEquivalent(misc_inherited_data_->misc_inherited_2_data_,
      other_style.misc_inherited_data_->misc_inherited_2_data_)) {
    output.emplace_back("misc_inherited_data_->misc_inherited_2_data_",
        sizeof(*misc_inherited_data_->misc_inherited_2_data_));
  }
  if (!base::ValuesEquivalent(misc_data_,
      other_style.misc_data_)) {
    output.emplace_back("misc_data_",
        sizeof(*misc_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_1_data_,
      other_style.misc_data_->misc_1_data_)) {
    output.emplace_back("misc_data_->misc_1_data_",
        sizeof(*misc_data_->misc_1_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->visited_data_,
      other_style.misc_data_->visited_data_)) {
    output.emplace_back("misc_data_->visited_data_",
        sizeof(*misc_data_->visited_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_2_data_,
      other_style.misc_data_->misc_2_data_)) {
    output.emplace_back("misc_data_->misc_2_data_",
        sizeof(*misc_data_->misc_2_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_3_data_,
      other_style.misc_data_->misc_3_data_)) {
    output.emplace_back("misc_data_->misc_3_data_",
        sizeof(*misc_data_->misc_3_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->forced_colors_data_,
      other_style.misc_data_->forced_colors_data_)) {
    output.emplace_back("misc_data_->forced_colors_data_",
        sizeof(*misc_data_->forced_colors_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_4_data_,
      other_style.misc_data_->misc_4_data_)) {
    output.emplace_back("misc_data_->misc_4_data_",
        sizeof(*misc_data_->misc_4_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_5_data_,
      other_style.misc_data_->misc_5_data_)) {
    output.emplace_back("misc_data_->misc_5_data_",
        sizeof(*misc_data_->misc_5_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_6_data_,
      other_style.misc_data_->misc_6_data_)) {
    output.emplace_back("misc_data_->misc_6_data_",
        sizeof(*misc_data_->misc_6_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->timeline_data_,
      other_style.misc_data_->timeline_data_)) {
    output.emplace_back("misc_data_->timeline_data_",
        sizeof(*misc_data_->timeline_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_7_data_,
      other_style.misc_data_->misc_7_data_)) {
    output.emplace_back("misc_data_->misc_7_data_",
        sizeof(*misc_data_->misc_7_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->misc_8_data_,
      other_style.misc_data_->misc_8_data_)) {
    output.emplace_back("misc_data_->misc_8_data_",
        sizeof(*misc_data_->misc_8_data_));
  }
  if (!base::ValuesEquivalent(misc_data_->math_data_,
      other_style.misc_data_->math_data_)) {
    output.emplace_back("misc_data_->math_data_",
        sizeof(*misc_data_->math_data_));
  }
  if (!base::ValuesEquivalent(inherited_data_,
      other_style.inherited_data_)) {
    output.emplace_back("inherited_data_",
        sizeof(*inherited_data_));
  }
  if (!base::ValuesEquivalent(inherited_data_->inherited_forced_colors_data_,
      other_style.inherited_data_->inherited_forced_colors_data_)) {
    output.emplace_back("inherited_data_->inherited_forced_colors_data_",
        sizeof(*inherited_data_->inherited_forced_colors_data_));
  }
  if (!base::ValuesEquivalent(inherited_data_->inherited_visited_data_,
      other_style.inherited_data_->inherited_visited_data_)) {
    output.emplace_back("inherited_data_->inherited_visited_data_",
        sizeof(*inherited_data_->inherited_visited_data_));
  }
  if (!base::ValuesEquivalent(inherited_data_->highlight_data_data_,
      other_style.inherited_data_->highlight_data_data_)) {
    output.emplace_back("inherited_data_->highlight_data_data_",
        sizeof(*inherited_data_->highlight_data_data_));
  }
  if (!base::ValuesEquivalent(visual_data_,
      other_style.visual_data_)) {
    output.emplace_back("visual_data_",
        sizeof(*visual_data_));
  }
  if (!base::ValuesEquivalent(svginherited_data_,
      other_style.svginherited_data_)) {
    output.emplace_back("svginherited_data_",
        sizeof(*svginherited_data_));
  }
  if (!base::ValuesEquivalent(svginherited_data_->fill_data_,
      other_style.svginherited_data_->fill_data_)) {
    output.emplace_back("svginherited_data_->fill_data_",
        sizeof(*svginherited_data_->fill_data_));
  }
  if (!base::ValuesEquivalent(svginherited_data_->stroke_data_,
      other_style.svginherited_data_->stroke_data_)) {
    output.emplace_back("svginherited_data_->stroke_data_",
        sizeof(*svginherited_data_->stroke_data_));
  }
  if (!base::ValuesEquivalent(svginherited_data_->resources_data_,
      other_style.svginherited_data_->resources_data_)) {
    output.emplace_back("svginherited_data_->resources_data_",
        sizeof(*svginherited_data_->resources_data_));
  }
  if (!base::ValuesEquivalent(box_data_,
      other_style.box_data_)) {
    output.emplace_back("box_data_",
        sizeof(*box_data_));
  }
  if (!base::ValuesEquivalent(svg_data_,
      other_style.svg_data_)) {
    output.emplace_back("svg_data_",
        sizeof(*svg_data_));
  }
  if (!base::ValuesEquivalent(svg_data_->svgmisc_data_,
      other_style.svg_data_->svgmisc_data_)) {
    output.emplace_back("svg_data_->svgmisc_data_",
        sizeof(*svg_data_->svgmisc_data_));
  }
  if (!base::ValuesEquivalent(svg_data_->geometry_data_,
      other_style.svg_data_->geometry_data_)) {
    output.emplace_back("svg_data_->geometry_data_",
        sizeof(*svg_data_->geometry_data_));
  }
  if (!base::ValuesEquivalent(svg_data_->stop_data_,
      other_style.svg_data_->stop_data_)) {
    output.emplace_back("svg_data_->stop_data_",
        sizeof(*svg_data_->stop_data_));
  }
  if (!base::ValuesEquivalent(surround_data_,
      other_style.surround_data_)) {
    output.emplace_back("surround_data_",
        sizeof(*surround_data_));
  }
  if (!base::ValuesEquivalent(background_data_,
      other_style.background_data_)) {
    output.emplace_back("background_data_",
        sizeof(*background_data_));
  }

  return output;
}

void ComputedStyleBase::Trace(Visitor* visitor) const {
  static_cast<const ComputedStyle*>(this)->TraceAfterDispatch(visitor);
}


uint64_t ComputedStyleBase::FieldInvalidationDiff(const ComputedStyle& a, const ComputedStyle& b) {
  uint64_t diff = 0u;
  if (a.misc_inherited_data_.Get() != b.misc_inherited_data_.Get()) {
    if (a.misc_inherited_data_->misc_inherited_1_data_.Get() != b.misc_inherited_data_->misc_inherited_1_data_.Get()) {
      if (a.misc_inherited_data_->misc_inherited_1_data_->dynamic_range_limit_ != b.misc_inherited_data_->misc_inherited_1_data_->dynamic_range_limit_) {
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->hyphenation_string_ != b.misc_inherited_data_->misc_inherited_1_data_->hyphenation_string_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_inherited_data_->misc_inherited_1_data_->quotes_, b.misc_inherited_data_->misc_inherited_1_data_->quotes_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_inherited_data_->misc_inherited_1_data_->list_style_image_, b.misc_inherited_data_->misc_inherited_1_data_->list_style_image_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_inherited_data_->misc_inherited_1_data_->list_style_type_, b.misc_inherited_data_->misc_inherited_1_data_->list_style_type_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_inherited_data_->misc_inherited_1_data_->scrollbar_color_, b.misc_inherited_data_->misc_inherited_1_data_->scrollbar_color_)) {
        diff |= kScrollbarStyle;
        diff |= kScrollbarColor;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->text_indent_ != b.misc_inherited_data_->misc_inherited_1_data_->text_indent_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->text_size_adjust_ != b.misc_inherited_data_->misc_inherited_1_data_->text_size_adjust_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->tab_size_ != b.misc_inherited_data_->misc_inherited_1_data_->tab_size_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->text_emphasis_color_ != b.misc_inherited_data_->misc_inherited_1_data_->text_emphasis_color_) {
        diff |= kColor;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->accent_color_ != b.misc_inherited_data_->misc_inherited_1_data_->accent_color_) {
        diff |= kAccentColor;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->caret_color_ != b.misc_inherited_data_->misc_inherited_1_data_->caret_color_) {
        diff |= kColor;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->hyphenate_limit_chars_ != b.misc_inherited_data_->misc_inherited_1_data_->hyphenate_limit_chars_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_1_data_->orphans_ != b.misc_inherited_data_->misc_inherited_1_data_->orphans_) {
        diff |= kLayout;
      }

    }
    if (a.misc_inherited_data_->misc_inherited_2_data_.Get() != b.misc_inherited_data_->misc_inherited_2_data_.Get()) {
      if (a.misc_inherited_data_->misc_inherited_2_data_->text_emphasis_custom_mark_ != b.misc_inherited_data_->misc_inherited_2_data_->text_emphasis_custom_mark_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_inherited_data_->misc_inherited_2_data_->text_shadow_, b.misc_inherited_data_->misc_inherited_2_data_->text_shadow_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_2_data_->text_underline_offset_ != b.misc_inherited_data_->misc_inherited_2_data_->text_underline_offset_) {
        diff |= kTextDecoration;
      }
      if (a.misc_inherited_data_->misc_inherited_2_data_->text_stroke_width_ != b.misc_inherited_data_->misc_inherited_2_data_->text_stroke_width_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_2_data_->effective_zoom_ != b.misc_inherited_data_->misc_inherited_2_data_->effective_zoom_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_inherited_data_->misc_inherited_2_data_->text_fill_color_ != b.misc_inherited_data_->misc_inherited_2_data_->text_fill_color_) {
        diff |= kColor;
      }
      if (a.misc_inherited_data_->misc_inherited_2_data_->text_stroke_color_ != b.misc_inherited_data_->misc_inherited_2_data_->text_stroke_color_) {
        diff |= kColor;
      }
      if (a.misc_inherited_data_->misc_inherited_2_data_->widows_ != b.misc_inherited_data_->misc_inherited_2_data_->widows_) {
        diff |= kLayout;
      }

    }
    if (a.misc_inherited_data_->text_box_edge_ != b.misc_inherited_data_->text_box_edge_) {
      diff |= kLayout;
    }
    if (a.misc_inherited_data_->text_underline_position_ != b.misc_inherited_data_->text_underline_position_) {
      diff |= kTextDecoration;
    }
    if (a.misc_inherited_data_->hanging_punctuation_ != b.misc_inherited_data_->hanging_punctuation_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->image_rendering_ != b.misc_inherited_data_->image_rendering_) {
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->line_break_ != b.misc_inherited_data_->line_break_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_align_last_ != b.misc_inherited_data_->text_align_last_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_decoration_skip_spaces_ != b.misc_inherited_data_->text_decoration_skip_spaces_) {
      diff |= kTextDecoration;
    }
    if (a.misc_inherited_data_->text_emphasis_mark_ != b.misc_inherited_data_->text_emphasis_mark_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->block_ellipsis_ != b.misc_inherited_data_->block_ellipsis_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_emphasis_position_ != b.misc_inherited_data_->text_emphasis_position_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->user_select_ != b.misc_inherited_data_->user_select_) {
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->word_break_ != b.misc_inherited_data_->word_break_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->hyphens_ != b.misc_inherited_data_->hyphens_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->image_animation_ != b.misc_inherited_data_->image_animation_) {
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->overflow_wrap_ != b.misc_inherited_data_->overflow_wrap_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->ruby_align_ != b.misc_inherited_data_->ruby_align_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_decoration_skip_ink_ != b.misc_inherited_data_->text_decoration_skip_ink_) {
      diff |= kTextDecoration;
    }
    if (a.misc_inherited_data_->text_indent_flags_ != b.misc_inherited_data_->text_indent_flags_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_justify_ != b.misc_inherited_data_->text_justify_) {
      diff |= kLayout;
    }
    if (a.misc_inherited_data_->text_orientation_ != b.misc_inherited_data_->text_orientation_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_security_ != b.misc_inherited_data_->text_security_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->user_modify_ != b.misc_inherited_data_->user_modify_) {
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->empty_cells_ != b.misc_inherited_data_->empty_cells_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->image_orientation_ != b.misc_inherited_data_->image_orientation_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->ruby_overhang_ != b.misc_inherited_data_->ruby_overhang_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->ruby_position_ != b.misc_inherited_data_->ruby_position_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->subtree_will_change_contents_ != b.misc_inherited_data_->subtree_will_change_contents_) {
      diff |= kCompositing;
    }
    if (a.misc_inherited_data_->text_autospace_ != b.misc_inherited_data_->text_autospace_) {
      diff |= kReshape;
    }
    if (a.misc_inherited_data_->text_combine_ != b.misc_inherited_data_->text_combine_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_inherited_data_->text_emphasis_fill_ != b.misc_inherited_data_->text_emphasis_fill_) {
      diff |= kLayout;
      diff |= kPaint;
    }

  }
  if (a.misc_data_.Get() != b.misc_data_.Get()) {
    if (a.misc_data_->misc_1_data_.Get() != b.misc_data_->misc_1_data_.Get()) {
      if (a.misc_data_->misc_1_data_->backdrop_filter_ != b.misc_data_->misc_1_data_->backdrop_filter_) {
        diff |= kCompositing;
      }
      if (a.misc_data_->misc_1_data_->anchor_scope_ != b.misc_data_->misc_1_data_->anchor_scope_) {
        diff |= kLayout;
      }
      if (a.misc_data_->misc_1_data_->position_anchor_ != b.misc_data_->misc_1_data_->position_anchor_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_1_data_->column_rule_color_ != b.misc_data_->misc_1_data_->column_rule_color_) {
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_1_data_->anchor_name_, b.misc_data_->misc_1_data_->anchor_name_)) {
        diff |= kLayout;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_1_data_->border_shape_, b.misc_data_->misc_1_data_->border_shape_)) {
        diff |= kBorderVisual;
        diff |= kPaint;
        diff |= kVisualOverflow;
        diff |= kBorderShape;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_1_data_->box_shadow_, b.misc_data_->misc_1_data_->box_shadow_)) {
        diff |= kPaint;
        diff |= kVisualOverflow;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_1_data_->clip_path_, b.misc_data_->misc_1_data_->clip_path_)) {
        diff |= kClipPath;
      }
      if (a.misc_data_->misc_1_data_->column_gap_ != b.misc_data_->misc_1_data_->column_gap_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_1_data_->column_rule_inset_cap_end_ != b.misc_data_->misc_1_data_->column_rule_inset_cap_end_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_1_data_->column_height_ != b.misc_data_->misc_1_data_->column_height_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_1_data_->position_area_ != b.misc_data_->misc_1_data_->position_area_) {
        diff |= kBoxPaintProperty;
        diff |= kLayout;
        diff |= kOutOfFlow;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_1_data_->column_count_ != b.misc_data_->misc_1_data_->column_count_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_1_data_->align_self_ != b.misc_data_->misc_1_data_->align_self_) {
        diff |= kLayout;
      }
      if (a.misc_data_->misc_1_data_->align_content_ != b.misc_data_->misc_1_data_->align_content_) {
        diff |= kLayout;
      }

    }
    if (a.misc_data_->visited_data_.Get() != b.misc_data_->visited_data_.Get()) {
      if (a.misc_data_->visited_data_->internal_visited_column_rule_color_ != b.misc_data_->visited_data_->internal_visited_column_rule_color_) {
        diff |= kPaint;
      }
      if (a.misc_data_->visited_data_->internal_visited_background_color_ != b.misc_data_->visited_data_->internal_visited_background_color_) {
        diff |= kBackgroundColor;
      }
      if (a.misc_data_->visited_data_->internal_visited_border_bottom_color_ != b.misc_data_->visited_data_->internal_visited_border_bottom_color_) {
        diff |= kBorderOutlineVisitedColor;
      }
      if (a.misc_data_->visited_data_->internal_visited_border_left_color_ != b.misc_data_->visited_data_->internal_visited_border_left_color_) {
        diff |= kBorderOutlineVisitedColor;
      }
      if (a.misc_data_->visited_data_->internal_visited_border_right_color_ != b.misc_data_->visited_data_->internal_visited_border_right_color_) {
        diff |= kBorderOutlineVisitedColor;
      }
      if (a.misc_data_->visited_data_->internal_visited_border_top_color_ != b.misc_data_->visited_data_->internal_visited_border_top_color_) {
        diff |= kBorderOutlineVisitedColor;
      }
      if (a.misc_data_->visited_data_->internal_visited_outline_color_ != b.misc_data_->visited_data_->internal_visited_outline_color_) {
        diff |= kBorderOutlineVisitedColor;
      }
      if (a.misc_data_->visited_data_->internal_visited_text_decoration_color_ != b.misc_data_->visited_data_->internal_visited_text_decoration_color_) {
        diff |= kColor;
      }

    }
    if (a.misc_data_->misc_2_data_.Get() != b.misc_data_->misc_2_data_.Get()) {
      if (a.misc_data_->misc_2_data_->grid_auto_columns_ != b.misc_data_->misc_2_data_->grid_auto_columns_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->filter_ != b.misc_data_->misc_2_data_->filter_) {
        diff |= kFilterData;
      }
      if (a.misc_data_->misc_2_data_->flow_tolerance_ != b.misc_data_->misc_2_data_->flow_tolerance_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->column_rule_width_ != b.misc_data_->misc_2_data_->column_rule_width_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->column_rule_style_ != b.misc_data_->misc_2_data_->column_rule_style_) {
        diff |= kPaint;
        diff |= kGapDecorations;
      }
      if (a.misc_data_->misc_2_data_->column_rule_inset_cap_start_ != b.misc_data_->misc_2_data_->column_rule_inset_cap_start_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->column_rule_inset_junction_end_ != b.misc_data_->misc_2_data_->column_rule_inset_junction_end_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->column_rule_inset_junction_start_ != b.misc_data_->misc_2_data_->column_rule_inset_junction_start_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->flex_basis_ != b.misc_data_->misc_2_data_->flex_basis_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->column_width_ != b.misc_data_->misc_2_data_->column_width_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->flex_grow_ != b.misc_data_->misc_2_data_->flex_grow_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->flex_shrink_ != b.misc_data_->misc_2_data_->flex_shrink_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->flex_line_count_ != b.misc_data_->misc_2_data_->flex_line_count_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_2_data_->flex_wrap_ != b.misc_data_->misc_2_data_->flex_wrap_) {
        diff |= kLayout;
        diff |= kPaint;
      }

    }
    if (a.misc_data_->misc_3_data_.Get() != b.misc_data_->misc_3_data_.Get()) {
      if (a.misc_data_->misc_3_data_->grid_auto_rows_ != b.misc_data_->misc_3_data_->grid_auto_rows_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->grid_column_end_ != b.misc_data_->misc_3_data_->grid_column_end_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->grid_column_start_ != b.misc_data_->misc_3_data_->grid_column_start_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->grid_row_end_ != b.misc_data_->misc_3_data_->grid_row_end_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->grid_row_start_ != b.misc_data_->misc_3_data_->grid_row_start_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_3_data_->grid_template_areas_, b.misc_data_->misc_3_data_->grid_template_areas_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_3_data_->grid_template_columns_, b.misc_data_->misc_3_data_->grid_template_columns_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_3_data_->grid_template_rows_, b.misc_data_->misc_3_data_->grid_template_rows_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->initial_letter_ != b.misc_data_->misc_3_data_->initial_letter_) {
        diff |= kReshape;
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->object_position_ != b.misc_data_->misc_3_data_->object_position_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->max_lines_ != b.misc_data_->misc_3_data_->max_lines_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->grid_lanes_direction_ != b.misc_data_->misc_3_data_->grid_lanes_direction_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_3_data_->justify_items_ != b.misc_data_->misc_3_data_->justify_items_) {
        diff |= kLayout;
      }
      if (a.misc_data_->misc_3_data_->justify_self_ != b.misc_data_->misc_3_data_->justify_self_) {
        diff |= kLayout;
      }

    }
    if (a.misc_data_->misc_4_data_.Get() != b.misc_data_->misc_4_data_.Get()) {
      if (!base::ValuesEquivalent(a.misc_data_->misc_4_data_->object_view_box_, b.misc_data_->misc_4_data_->object_view_box_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_4_data_->offset_path_, b.misc_data_->misc_4_data_->offset_path_)) {
        diff |= kHasTransform;
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_4_data_->position_try_fallbacks_, b.misc_data_->misc_4_data_->position_try_fallbacks_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_4_data_->rotate_, b.misc_data_->misc_4_data_->rotate_)) {
        diff |= kHasTransform;
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->offset_rotate_ != b.misc_data_->misc_4_data_->offset_rotate_) {
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->offset_anchor_ != b.misc_data_->misc_4_data_->offset_anchor_) {
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->offset_position_ != b.misc_data_->misc_4_data_->offset_position_) {
        diff |= kHasTransform;
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->perspective_origin_ != b.misc_data_->misc_4_data_->perspective_origin_) {
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->offset_distance_ != b.misc_data_->misc_4_data_->offset_distance_) {
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->perspective_ != b.misc_data_->misc_4_data_->perspective_) {
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_4_data_->outline_color_ != b.misc_data_->misc_4_data_->outline_color_) {
        diff |= kOutline;
      }
      if (a.misc_data_->misc_4_data_->order_ != b.misc_data_->misc_4_data_->order_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_4_data_->outline_offset_ != b.misc_data_->misc_4_data_->outline_offset_) {
        diff |= kOutline;
      }
      if (a.misc_data_->misc_4_data_->outline_width_ != b.misc_data_->misc_4_data_->outline_width_) {
        diff |= kOutline;
      }
      if (a.misc_data_->misc_4_data_->reading_order_ != b.misc_data_->misc_4_data_->reading_order_) {
        diff |= kLayout;
      }

    }
    if (a.misc_data_->misc_5_data_.Get() != b.misc_data_->misc_5_data_.Get()) {
      if (a.misc_data_->misc_5_data_->row_rule_color_ != b.misc_data_->misc_5_data_->row_rule_color_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_5_data_->row_rule_width_ != b.misc_data_->misc_5_data_->row_rule_width_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_5_data_->row_rule_style_ != b.misc_data_->misc_5_data_->row_rule_style_) {
        diff |= kPaint;
        diff |= kGapDecorations;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_5_data_->scale_, b.misc_data_->misc_5_data_->scale_)) {
        diff |= kHasTransform;
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_5_data_->row_gap_ != b.misc_data_->misc_5_data_->row_gap_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_5_data_->row_rule_inset_cap_end_ != b.misc_data_->misc_5_data_->row_rule_inset_cap_end_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_5_data_->row_rule_inset_cap_start_ != b.misc_data_->misc_5_data_->row_rule_inset_cap_start_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_5_data_->row_rule_inset_junction_end_ != b.misc_data_->misc_5_data_->row_rule_inset_junction_end_) {
        diff |= kPaint;
      }
      if (a.misc_data_->misc_5_data_->row_rule_inset_junction_start_ != b.misc_data_->misc_5_data_->row_rule_inset_junction_start_) {
        diff |= kPaint;
      }

    }
    if (a.misc_data_->misc_6_data_.Get() != b.misc_data_->misc_6_data_.Get()) {
      if (a.misc_data_->misc_6_data_->text_decoration_thickness_ != b.misc_data_->misc_6_data_->text_decoration_thickness_) {
        diff |= kTextDecoration;
      }
      if (a.misc_data_->misc_6_data_->text_overflow_ != b.misc_data_->misc_6_data_->text_overflow_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_6_data_->trigger_scope_ != b.misc_data_->misc_6_data_->trigger_scope_) {
        diff |= kLayout;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_6_data_->shape_outside_, b.misc_data_->misc_6_data_->shape_outside_)) {
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_6_data_->translate_, b.misc_data_->misc_6_data_->translate_)) {
        diff |= kHasTransform;
        diff |= kTransformData;
        diff |= kTransformOther;
      }
      if (a.misc_data_->misc_6_data_->shape_margin_ != b.misc_data_->misc_6_data_->shape_margin_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_6_data_->text_fit_ != b.misc_data_->misc_6_data_->text_fit_) {
        diff |= kLayout;
      }
      if (a.misc_data_->misc_6_data_->text_decoration_color_ != b.misc_data_->misc_6_data_->text_decoration_color_) {
        diff |= kColor;
      }

    }
    if (a.misc_data_->misc_7_data_.Get() != b.misc_data_->misc_7_data_.Get()) {
      if (a.misc_data_->misc_7_data_->display_layout_custom_name_ != b.misc_data_->misc_7_data_->display_layout_custom_name_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_7_data_->mask_ != b.misc_data_->misc_7_data_->mask_) {
        diff |= kMask;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_7_data_->mask_box_image_ != b.misc_data_->misc_7_data_->mask_box_image_) {
        diff |= kMask;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.misc_data_->misc_7_data_->box_reflect_, b.misc_data_->misc_7_data_->box_reflect_)) {
        diff |= kFilterData;
      }
      if (a.misc_data_->misc_7_data_->box_flex_ != b.misc_data_->misc_7_data_->box_flex_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_7_data_->box_ordinal_group_ != b.misc_data_->misc_7_data_->box_ordinal_group_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->misc_7_data_->webkit_line_clamp_ != b.misc_data_->misc_7_data_->webkit_line_clamp_) {
        diff |= kLayout;
        diff |= kPaint;
      }

    }
    if (a.misc_data_->math_data_.Get() != b.misc_data_->math_data_.Get()) {
      if (a.misc_data_->math_data_->math_fraction_bar_thickness_ != b.misc_data_->math_data_->math_fraction_bar_thickness_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->math_data_->math_l_space_ != b.misc_data_->math_data_->math_l_space_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->math_data_->math_r_space_ != b.misc_data_->math_data_->math_r_space_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->math_data_->math_padded_v_offset_ != b.misc_data_->math_data_->math_padded_v_offset_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->math_data_->math_min_size_ != b.misc_data_->math_data_->math_min_size_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.misc_data_->math_data_->math_max_size_ != b.misc_data_->math_data_->math_max_size_) {
        diff |= kLayout;
        diff |= kPaint;
      }

    }
    if (!base::ValuesEquivalent(a.misc_data_->will_change_, b.misc_data_->will_change_)) {
      diff |= kCompositing;
    }
    if (a.misc_data_->appearance_ != b.misc_data_->appearance_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->blend_mode_ != b.misc_data_->blend_mode_) {
      diff |= kBlendMode;
      diff |= kPaint;
    }
    if (a.misc_data_->contain_ != b.misc_data_->contain_) {
      diff |= kLayout;
    }
    if (a.misc_data_->break_after_ != b.misc_data_->break_after_) {
      diff |= kLayout;
    }
    if (a.misc_data_->break_before_ != b.misc_data_->break_before_) {
      diff |= kLayout;
    }
    if (a.misc_data_->container_type_ != b.misc_data_->container_type_) {
      diff |= kLayout;
    }
    if (a.misc_data_->grid_auto_flow_ != b.misc_data_->grid_auto_flow_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->margin_trim_ != b.misc_data_->margin_trim_) {
      diff |= kLayout;
    }
    if (a.misc_data_->outline_style_ != b.misc_data_->outline_style_) {
      diff |= kOutline;
    }
    if (a.misc_data_->scrollbar_gutter_ != b.misc_data_->scrollbar_gutter_) {
      diff |= kLayout;
    }
    if (a.misc_data_->box_align_ != b.misc_data_->box_align_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->object_fit_ != b.misc_data_->object_fit_) {
      diff |= kPaint;
    }
    if (a.misc_data_->position_try_order_ != b.misc_data_->position_try_order_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->position_visibility_ != b.misc_data_->position_visibility_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->reading_flow_ != b.misc_data_->reading_flow_) {
      diff |= kLayout;
    }
    if (a.misc_data_->resize_ != b.misc_data_->resize_) {
      diff |= kPaint;
    }
    if (a.misc_data_->text_decoration_style_ != b.misc_data_->text_decoration_style_) {
      diff |= kTextDecoration;
    }
    if (a.misc_data_->box_pack_ != b.misc_data_->box_pack_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->break_inside_ != b.misc_data_->break_inside_) {
      diff |= kLayout;
    }
    if (a.misc_data_->column_rule_break_ != b.misc_data_->column_rule_break_) {
      diff |= kPaint;
    }
    if (a.misc_data_->column_rule_visibility_items_ != b.misc_data_->column_rule_visibility_items_) {
      diff |= kPaint;
    }
    if (a.misc_data_->column_wrap_ != b.misc_data_->column_wrap_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->continue_ != b.misc_data_->continue_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->draggable_region_mode_ != b.misc_data_->draggable_region_mode_) {
      diff |= kLayout;
    }
    if (a.misc_data_->flex_direction_ != b.misc_data_->flex_direction_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->overscroll_behavior_x_ != b.misc_data_->overscroll_behavior_x_) {
      diff |= kBoxPaintProperty;
    }
    if (a.misc_data_->overscroll_behavior_y_ != b.misc_data_->overscroll_behavior_y_) {
      diff |= kBoxPaintProperty;
    }
    if (a.misc_data_->page_margin_safety_ != b.misc_data_->page_margin_safety_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->row_rule_break_ != b.misc_data_->row_rule_break_) {
      diff |= kPaint;
    }
    if (a.misc_data_->row_rule_visibility_items_ != b.misc_data_->row_rule_visibility_items_) {
      diff |= kPaint;
    }
    if (a.misc_data_->scrollbar_width_ != b.misc_data_->scrollbar_width_) {
      diff |= kLayout;
      diff |= kPaint;
      diff |= kScrollbarStyle;
    }
    if (a.misc_data_->user_drag_ != b.misc_data_->user_drag_) {
      diff |= kPaint;
    }
    if (a.misc_data_->align_content_block_center_ != b.misc_data_->align_content_block_center_) {
      diff |= kLayout;
    }
    if (a.misc_data_->backface_visibility_ != b.misc_data_->backface_visibility_) {
      diff |= kCompositing;
    }
    if (a.misc_data_->box_orient_ != b.misc_data_->box_orient_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->column_fill_ != b.misc_data_->column_fill_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->column_span_ != b.misc_data_->column_span_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->grid_lanes_pack_ != b.misc_data_->grid_lanes_pack_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->has_auto_column_count_ != b.misc_data_->has_auto_column_count_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->has_auto_column_height_ != b.misc_data_->has_auto_column_height_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->has_auto_column_width_ != b.misc_data_->has_auto_column_width_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->has_current_backdrop_filter_animation_ != b.misc_data_->has_current_backdrop_filter_animation_) {
      diff |= kCompositing;
    }
    if (a.misc_data_->has_current_clip_path_animation_ != b.misc_data_->has_current_clip_path_animation_) {
      diff |= kCompositing;
    }
    if (a.misc_data_->has_current_filter_animation_ != b.misc_data_->has_current_filter_animation_) {
      diff |= kCompositing;
    }
    if (a.misc_data_->has_current_opacity_animation_ != b.misc_data_->has_current_opacity_animation_) {
      diff |= kCompositing;
    }
    if (a.misc_data_->has_current_rotate_animation_ != b.misc_data_->has_current_rotate_animation_) {
      diff |= kCompositing;
      diff |= kHasTransform;
    }
    if (a.misc_data_->has_current_scale_animation_ != b.misc_data_->has_current_scale_animation_) {
      diff |= kCompositing;
      diff |= kHasTransform;
    }
    if (a.misc_data_->has_current_transform_animation_ != b.misc_data_->has_current_transform_animation_) {
      diff |= kCompositing;
      diff |= kHasTransform;
    }
    if (a.misc_data_->has_current_translate_animation_ != b.misc_data_->has_current_translate_animation_) {
      diff |= kCompositing;
      diff |= kHasTransform;
    }
    if (a.misc_data_->is_bottom_relative_to_safe_area_inset_ != b.misc_data_->is_bottom_relative_to_safe_area_inset_) {
      diff |= kLayout;
    }
    if (a.misc_data_->is_specified_display_webkit_box_ != b.misc_data_->is_specified_display_webkit_box_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.misc_data_->isolation_ != b.misc_data_->isolation_) {
      diff |= kPaint;
    }
    if (a.misc_data_->outline_style_is_auto_ != b.misc_data_->outline_style_is_auto_) {
      diff |= kOutline;
    }
    if (a.misc_data_->rule_overlap_ != b.misc_data_->rule_overlap_) {
      diff |= kPaint;
    }
    if (a.misc_data_->scroll_initial_target_ != b.misc_data_->scroll_initial_target_) {
      diff |= kLayout;
    }

  }
  if (a.inherited_data_.Get() != b.inherited_data_.Get()) {
    if (a.inherited_data_->inherited_visited_data_.Get() != b.inherited_data_->inherited_visited_data_.Get()) {
      if (a.inherited_data_->inherited_visited_data_->internal_visited_text_emphasis_color_ != b.inherited_data_->inherited_visited_data_->internal_visited_text_emphasis_color_) {
        diff |= kColor;
      }
      if (a.inherited_data_->inherited_visited_data_->internal_visited_text_fill_color_ != b.inherited_data_->inherited_visited_data_->internal_visited_text_fill_color_) {
        diff |= kColor;
      }
      if (a.inherited_data_->inherited_visited_data_->internal_visited_text_stroke_color_ != b.inherited_data_->inherited_visited_data_->internal_visited_text_stroke_color_) {
        diff |= kColor;
      }
      if (a.inherited_data_->inherited_visited_data_->internal_visited_caret_color_ != b.inherited_data_->inherited_visited_data_->internal_visited_caret_color_) {
        diff |= kColor;
      }

    }
    if (!base::ValuesEquivalent(a.inherited_data_->font_, b.inherited_data_->font_)) {
      diff |= kReshape;
    }
    if (!base::ValuesEquivalent(a.inherited_data_->container_font_, b.inherited_data_->container_font_)) {
      diff |= kReshape;
    }
    if (a.inherited_data_->line_height_ != b.inherited_data_->line_height_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.inherited_data_->internal_visited_color_ != b.inherited_data_->internal_visited_color_) {
      diff |= kBorderVisual;
      diff |= kColor;
      diff |= kCurrentcolor;
    }
    if (a.inherited_data_->color_ != b.inherited_data_->color_) {
      diff |= kAccentColor;
      diff |= kBorderVisual;
      diff |= kColor;
      diff |= kCurrentcolor;
      diff |= kOutline;
    }
    if (a.inherited_data_->horizontal_border_spacing_ != b.inherited_data_->horizontal_border_spacing_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.inherited_data_->vertical_border_spacing_ != b.inherited_data_->vertical_border_spacing_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.inherited_data_->text_transform_ != b.inherited_data_->text_transform_) {
      diff |= kReshape;
    }

  }
  if (a.visual_data_.Get() != b.visual_data_.Get()) {
    if (!base::ValuesEquivalent(a.visual_data_->base_text_decoration_data_, b.visual_data_->base_text_decoration_data_)) {
      diff |= kTextDecoration;
    }
    if (a.visual_data_->clip_ != b.visual_data_->clip_) {
      diff |= kClip;
    }
    if (a.visual_data_->text_decoration_line_ != b.visual_data_->text_decoration_line_) {
      diff |= kTextDecoration;
    }
    if (a.visual_data_->field_sizing_ != b.visual_data_->field_sizing_) {
      diff |= kLayout;
    }
    if (a.visual_data_->has_auto_clip_ != b.visual_data_->has_auto_clip_) {
      diff |= kClip;
    }

  }
  if (a.svginherited_data_.Get() != b.svginherited_data_.Get()) {
    if (a.svginherited_data_->fill_data_.Get() != b.svginherited_data_->fill_data_.Get()) {
      if (a.svginherited_data_->fill_data_->fill_paint_ != b.svginherited_data_->fill_data_->fill_paint_) {
        diff |= kPaint;
      }
      if (a.svginherited_data_->fill_data_->fill_opacity_ != b.svginherited_data_->fill_data_->fill_opacity_) {
        diff |= kPaint;
      }

    }
    if (a.svginherited_data_->stroke_data_.Get() != b.svginherited_data_->stroke_data_.Get()) {
      if (a.svginherited_data_->stroke_data_->internal_visited_stroke_paint_ != b.svginherited_data_->stroke_data_->internal_visited_stroke_paint_) {
        diff |= kPaint;
      }
      if (a.svginherited_data_->stroke_data_->stroke_paint_ != b.svginherited_data_->stroke_data_->stroke_paint_) {
        diff |= kPaint;
        diff |= kStroke;
      }
      if (!base::ValuesEquivalent(a.svginherited_data_->stroke_data_->stroke_dash_array_, b.svginherited_data_->stroke_data_->stroke_dash_array_)) {
        diff |= kPaint;
        diff |= kStroke;
        diff |= kBorderShape;
      }
      if (a.svginherited_data_->stroke_data_->stroke_dash_offset_ != b.svginherited_data_->stroke_data_->stroke_dash_offset_) {
        diff |= kPaint;
      }
      if (a.svginherited_data_->stroke_data_->stroke_width_ != b.svginherited_data_->stroke_data_->stroke_width_) {
        diff |= kLayout;
        diff |= kPaint;
        diff |= kBorderShape;
      }
      if (a.svginherited_data_->stroke_data_->stroke_miter_limit_ != b.svginherited_data_->stroke_data_->stroke_miter_limit_) {
        diff |= kLayout;
        diff |= kPaint;
        diff |= kBorderShape;
      }
      if (a.svginherited_data_->stroke_data_->stroke_opacity_ != b.svginherited_data_->stroke_data_->stroke_opacity_) {
        diff |= kPaint;
      }
      if (a.svginherited_data_->stroke_data_->cap_style_ != b.svginherited_data_->stroke_data_->cap_style_) {
        diff |= kLayout;
        diff |= kPaint;
        diff |= kBorderShape;
      }
      if (a.svginherited_data_->stroke_data_->join_style_ != b.svginherited_data_->stroke_data_->join_style_) {
        diff |= kLayout;
        diff |= kPaint;
        diff |= kBorderShape;
      }

    }
    if (a.svginherited_data_->resources_data_.Get() != b.svginherited_data_->resources_data_.Get()) {
      if (!base::ValuesEquivalent(a.svginherited_data_->resources_data_->marker_end_resource_, b.svginherited_data_->resources_data_->marker_end_resource_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.svginherited_data_->resources_data_->marker_mid_resource_, b.svginherited_data_->resources_data_->marker_mid_resource_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (!base::ValuesEquivalent(a.svginherited_data_->resources_data_->marker_start_resource_, b.svginherited_data_->resources_data_->marker_start_resource_)) {
        diff |= kLayout;
        diff |= kPaint;
      }

    }
    if (a.svginherited_data_->css_dominant_baseline_ != b.svginherited_data_->css_dominant_baseline_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.svginherited_data_->dominant_baseline_ != b.svginherited_data_->dominant_baseline_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.svginherited_data_->paint_order_ != b.svginherited_data_->paint_order_) {
      diff |= kPaint;
    }
    if (a.svginherited_data_->color_interpolation_ != b.svginherited_data_->color_interpolation_) {
      diff |= kPaint;
    }
    if (a.svginherited_data_->color_interpolation_filters_ != b.svginherited_data_->color_interpolation_filters_) {
      diff |= kPaint;
    }
    if (a.svginherited_data_->shape_rendering_ != b.svginherited_data_->shape_rendering_) {
      diff |= kPaint;
    }
    if (a.svginherited_data_->text_anchor_ != b.svginherited_data_->text_anchor_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.svginherited_data_->clip_rule_ != b.svginherited_data_->clip_rule_) {
      diff |= kPaint;
    }
    if (a.svginherited_data_->fill_rule_ != b.svginherited_data_->fill_rule_) {
      diff |= kPaint;
    }

  }
  if (a.box_data_.Get() != b.box_data_.Get()) {
    if (a.box_data_->overflow_clip_margin_ != b.box_data_->overflow_clip_margin_) {
      diff |= kBoxPaintProperty;
      diff |= kLayout;
    }
    if (a.box_data_->height_ != b.box_data_->height_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->margin_bottom_ != b.box_data_->margin_bottom_) {
      diff |= kMargin;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->margin_left_ != b.box_data_->margin_left_) {
      diff |= kMargin;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->margin_right_ != b.box_data_->margin_right_) {
      diff |= kMargin;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->margin_top_ != b.box_data_->margin_top_) {
      diff |= kMargin;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->max_height_ != b.box_data_->max_height_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->max_width_ != b.box_data_->max_width_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->min_height_ != b.box_data_->min_height_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->min_width_ != b.box_data_->min_width_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->padding_bottom_ != b.box_data_->padding_bottom_) {
      diff |= kLayout;
      diff |= kPaint;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->padding_left_ != b.box_data_->padding_left_) {
      diff |= kLayout;
      diff |= kPaint;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->padding_right_ != b.box_data_->padding_right_) {
      diff |= kLayout;
      diff |= kPaint;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->padding_top_ != b.box_data_->padding_top_) {
      diff |= kLayout;
      diff |= kPaint;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->width_ != b.box_data_->width_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.box_data_->vertical_align_length_ != b.box_data_->vertical_align_length_) {
      diff |= kLayout;
    }
    if (a.box_data_->border_bottom_width_ != b.box_data_->border_bottom_width_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->border_left_width_ != b.box_data_->border_left_width_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->border_right_width_ != b.box_data_->border_right_width_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->border_top_width_ != b.box_data_->border_top_width_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->z_index_ != b.box_data_->z_index_) {
      diff |= kZIndex;
    }
    if (a.box_data_->align_items_ != b.box_data_->align_items_) {
      diff |= kLayout;
    }
    if (a.box_data_->justify_content_ != b.box_data_->justify_content_) {
      diff |= kLayout;
    }
    if (a.box_data_->border_bottom_style_ != b.box_data_->border_bottom_style_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->border_left_style_ != b.box_data_->border_left_style_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->border_right_style_ != b.box_data_->border_right_style_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->border_top_style_ != b.box_data_->border_top_style_) {
      diff |= kBorderWidth;
      diff |= kBorderVisual;
    }
    if (a.box_data_->baseline_source_ != b.box_data_->baseline_source_) {
      diff |= kLayout;
    }
    if (a.box_data_->text_box_trim_ != b.box_data_->text_box_trim_) {
      diff |= kLayout;
    }
    if (a.box_data_->box_decoration_break_ != b.box_data_->box_decoration_break_) {
      diff |= kLayout;
      diff |= kPaint;
    }

  }
  if (a.svg_data_.Get() != b.svg_data_.Get()) {
    if (a.svg_data_->svgmisc_data_.Get() != b.svg_data_->svgmisc_data_.Get()) {
      if (a.svg_data_->svgmisc_data_->baseline_shift_ != b.svg_data_->svgmisc_data_->baseline_shift_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->svgmisc_data_->flood_opacity_ != b.svg_data_->svgmisc_data_->flood_opacity_) {
        diff |= kPaint;
      }
      if (a.svg_data_->svgmisc_data_->flood_color_ != b.svg_data_->svgmisc_data_->flood_color_) {
        diff |= kPaint;
      }
      if (a.svg_data_->svgmisc_data_->lighting_color_ != b.svg_data_->svgmisc_data_->lighting_color_) {
        diff |= kPaint;
      }
      if (a.svg_data_->svgmisc_data_->baseline_shift_type_ != b.svg_data_->svgmisc_data_->baseline_shift_type_) {
        diff |= kLayout;
        diff |= kPaint;
      }

    }
    if (a.svg_data_->geometry_data_.Get() != b.svg_data_->geometry_data_.Get()) {
      if (!base::ValuesEquivalent(a.svg_data_->geometry_data_->d_, b.svg_data_->geometry_data_->d_)) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->cx_ != b.svg_data_->geometry_data_->cx_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->cy_ != b.svg_data_->geometry_data_->cy_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->r_ != b.svg_data_->geometry_data_->r_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->rx_ != b.svg_data_->geometry_data_->rx_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->ry_ != b.svg_data_->geometry_data_->ry_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->x_ != b.svg_data_->geometry_data_->x_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->y_ != b.svg_data_->geometry_data_->y_) {
        diff |= kLayout;
        diff |= kPaint;
      }
      if (a.svg_data_->geometry_data_->path_length_ != b.svg_data_->geometry_data_->path_length_) {
        diff |= kPaint;
      }

    }
    if (a.svg_data_->stop_data_.Get() != b.svg_data_->stop_data_.Get()) {
      if (a.svg_data_->stop_data_->stop_opacity_ != b.svg_data_->stop_data_->stop_opacity_) {
        diff |= kPaint;
      }
      if (a.svg_data_->stop_data_->stop_color_ != b.svg_data_->stop_data_->stop_color_) {
        diff |= kPaint;
      }

    }
    if (a.svg_data_->transform_ != b.svg_data_->transform_) {
      diff |= kHasTransform;
      diff |= kTransformData;
      diff |= kTransformProperty;
    }
    if (a.svg_data_->transform_origin_ != b.svg_data_->transform_origin_) {
      diff |= kTransformData;
      diff |= kTransformOther;
    }
    if (a.svg_data_->opacity_ != b.svg_data_->opacity_) {
      diff |= kOpacity;
    }
    if (a.svg_data_->alignment_baseline_ != b.svg_data_->alignment_baseline_) {
      diff |= kLayout;
      diff |= kPaint;
    }
    if (a.svg_data_->mask_type_ != b.svg_data_->mask_type_) {
      diff |= kPaint;
    }
    if (a.svg_data_->vector_effect_ != b.svg_data_->vector_effect_) {
      diff |= kLayout;
      diff |= kPaint;
    }

  }
  if (a.surround_data_.Get() != b.surround_data_.Get()) {
    if (a.surround_data_->corner_bottom_left_shape_ != b.surround_data_->corner_bottom_left_shape_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->corner_bottom_right_shape_ != b.surround_data_->corner_bottom_right_shape_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->corner_top_left_shape_ != b.surround_data_->corner_top_left_shape_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->corner_top_right_shape_ != b.surround_data_->corner_top_right_shape_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->border_image_ != b.surround_data_->border_image_) {
      diff |= kBorderImage;
      diff |= kBorderVisual;
    }
    if (a.surround_data_->aspect_ratio_ != b.surround_data_->aspect_ratio_) {
      diff |= kLayout;
    }
    if (a.surround_data_->contain_intrinsic_height_ != b.surround_data_->contain_intrinsic_height_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.surround_data_->contain_intrinsic_width_ != b.surround_data_->contain_intrinsic_width_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }
    if (a.surround_data_->border_bottom_left_radius_ != b.surround_data_->border_bottom_left_radius_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->border_bottom_right_radius_ != b.surround_data_->border_bottom_right_radius_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->border_top_left_radius_ != b.surround_data_->border_top_left_radius_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->border_top_right_radius_ != b.surround_data_->border_top_right_radius_) {
      diff |= kBorderRadius;
      diff |= kPaint;
    }
    if (a.surround_data_->bottom_ != b.surround_data_->bottom_) {
      diff |= kInset;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.surround_data_->left_ != b.surround_data_->left_) {
      diff |= kInset;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.surround_data_->right_ != b.surround_data_->right_) {
      diff |= kInset;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.surround_data_->top_ != b.surround_data_->top_) {
      diff |= kInset;
      diff |= kOutOfFlow;
      diff |= kScrollAnchor;
    }
    if (a.surround_data_->border_bottom_color_ != b.surround_data_->border_bottom_color_) {
      diff |= kBorderVisual;
    }
    if (a.surround_data_->border_left_color_ != b.surround_data_->border_left_color_) {
      diff |= kBorderVisual;
    }
    if (a.surround_data_->border_right_color_ != b.surround_data_->border_right_color_) {
      diff |= kBorderVisual;
    }
    if (a.surround_data_->border_top_color_ != b.surround_data_->border_top_color_) {
      diff |= kBorderVisual;
    }
    if (a.surround_data_->frame_sizing_ != b.surround_data_->frame_sizing_) {
      diff |= kLayout;
      diff |= kScrollAnchor;
    }

  }
  if (a.background_data_.Get() != b.background_data_.Get()) {
    if (a.background_data_->background_ != b.background_data_->background_) {
      diff |= kBackground;
      diff |= kCurrentcolor;
    }
    if (a.background_data_->background_color_ != b.background_data_->background_color_) {
      diff |= kBackgroundColor;
    }

  }
  if (a.data_.pseudo_element_styles_ != b.data_.pseudo_element_styles_) {
    diff |= kScrollbarStyle;
  }
  if (a.data_.vertical_align_ != b.data_.vertical_align_) {
    diff |= kLayout;
  }
  if (a.data_.clear_ != b.data_.clear_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.floating_ != b.data_.floating_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.overflow_x_ != b.data_.overflow_x_) {
    diff |= kBoxPaintProperty;
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.overflow_y_ != b.data_.overflow_y_) {
    diff |= kBoxPaintProperty;
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.position_ != b.data_.position_) {
    diff |= kClip;
    diff |= kLayout;
    diff |= kScrollAnchor;
  }
  if (a.data_.transform_box_ != b.data_.transform_box_) {
    diff |= kTransformData;
    diff |= kTransformOther;
  }
  if (a.data_.unicode_bidi_ != b.data_.unicode_bidi_) {
    diff |= kReshape;
  }
  if (a.data_.content_visibility_ != b.data_.content_visibility_) {
    diff |= kLayout;
  }
  if (a.data_.box_direction_ != b.data_.box_direction_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.box_sizing_ != b.data_.box_sizing_) {
    diff |= kLayout;
  }
  if (a.data_.is_original_display_inline_type_ != b.data_.is_original_display_inline_type_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.skips_contents_ != b.data_.skips_contents_) {
    diff |= kLayout;
  }
  if (a.data_.table_layout_ != b.data_.table_layout_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.caret_shape_ != b.data_.caret_shape_) {
    diff |= kPaint;
  }
  if (a.data_.text_align_ != b.data_.text_align_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.writing_mode_ != b.data_.writing_mode_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.inside_link_ != b.data_.inside_link_) {
    diff |= kBorderVisual;
    diff |= kPaint;
  }
  if (a.data_.text_wrap_style_ != b.data_.text_wrap_style_) {
    diff |= kLayout;
  }
  if (a.data_.visibility_ != b.data_.visibility_) {
    diff |= kPaint;
    diff |= kVisibility;
  }
  if (a.data_.white_space_collapse_ != b.data_.white_space_collapse_) {
    diff |= kReshape;
  }
  if (a.data_.border_collapse_ != b.data_.border_collapse_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.caption_side_ != b.data_.caption_side_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.caret_animation_ != b.data_.caret_animation_) {
    diff |= kPaint;
  }
  if (a.data_.color_scheme_forced_ != b.data_.color_scheme_forced_) {
    diff |= kPaint;
  }
  if (a.data_.dark_color_scheme_ != b.data_.dark_color_scheme_) {
    diff |= kAccentColor;
    diff |= kBorderVisual;
    diff |= kCurrentcolor;
    diff |= kPaint;
  }
  if (a.data_.direction_ != b.data_.direction_) {
    diff |= kReshape;
  }
  if (a.data_.is_css_inert_ != b.data_.is_css_inert_) {
    diff |= kInert;
  }
  if (a.data_.is_html_inert_ != b.data_.is_html_inert_) {
    diff |= kInert;
  }
  if (a.data_.list_style_position_ != b.data_.list_style_position_) {
    diff |= kLayout;
    diff |= kPaint;
  }
  if (a.data_.prefers_default_scrollbar_styles_ != b.data_.prefers_default_scrollbar_styles_) {
    diff |= kLayout;
    diff |= kPaint;
    diff |= kScrollbarColor;
  }
  if (a.data_.print_color_adjust_ != b.data_.print_color_adjust_) {
    diff |= kPaint;
  }
  if (a.data_.rtl_ordering_ != b.data_.rtl_ordering_) {
    diff |= kReshape;
  }
  if (a.data_.text_wrap_mode_ != b.data_.text_wrap_mode_) {
    diff |= kReshape;
  }

  return diff;
}

CSSBitset ComputedStyleBase::TransitionAllDiff(const ComputedStyle& a, const ComputedStyle& b) {
  CSSBitset diff;
        auto* a_misc_inherited_data_ = a.misc_inherited_data_.Get();
      auto* b_misc_inherited_data_ = b.misc_inherited_data_.Get();
      if (a_misc_inherited_data_ != b_misc_inherited_data_) {
              auto* a_misc_inherited_data__misc_inherited_1_data_ = a_misc_inherited_data_->misc_inherited_1_data_.Get();
        auto* b_misc_inherited_data__misc_inherited_1_data_ = b_misc_inherited_data_->misc_inherited_1_data_.Get();
        if (a_misc_inherited_data__misc_inherited_1_data_ != b_misc_inherited_data__misc_inherited_1_data_) {
            
          if (a_misc_inherited_data__misc_inherited_1_data_->dynamic_range_limit_ != b_misc_inherited_data__misc_inherited_1_data_->dynamic_range_limit_) {
            diff.Set(CSSPropertyID::kDynamicRangeLimit);
          }
          if (!base::ValuesEquivalent(a_misc_inherited_data__misc_inherited_1_data_->list_style_image_, b_misc_inherited_data__misc_inherited_1_data_->list_style_image_)) {
            diff.Set(CSSPropertyID::kListStyleImage);
          }
          if (!base::ValuesEquivalent(a_misc_inherited_data__misc_inherited_1_data_->scrollbar_color_, b_misc_inherited_data__misc_inherited_1_data_->scrollbar_color_)) {
            diff.Set(CSSPropertyID::kScrollbarColor);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->text_indent_ != b_misc_inherited_data__misc_inherited_1_data_->text_indent_) {
            diff.Set(CSSPropertyID::kTextIndent);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->text_size_adjust_ != b_misc_inherited_data__misc_inherited_1_data_->text_size_adjust_) {
            diff.Set(CSSPropertyID::kTextSizeAdjust);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->tab_size_ != b_misc_inherited_data__misc_inherited_1_data_->tab_size_) {
            diff.Set(CSSPropertyID::kTabSize);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->text_emphasis_color_ != b_misc_inherited_data__misc_inherited_1_data_->text_emphasis_color_) {
            diff.Set(CSSPropertyID::kTextEmphasisColor);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->accent_color_ != b_misc_inherited_data__misc_inherited_1_data_->accent_color_) {
            diff.Set(CSSPropertyID::kAccentColor);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->caret_color_ != b_misc_inherited_data__misc_inherited_1_data_->caret_color_) {
            diff.Set(CSSPropertyID::kCaretColor);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->math_depth_ != b_misc_inherited_data__misc_inherited_1_data_->math_depth_) {
            diff.Set(CSSPropertyID::kMathDepth);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->orphans_ != b_misc_inherited_data__misc_inherited_1_data_->orphans_) {
            diff.Set(CSSPropertyID::kOrphans);
          }



        }
        auto* a_misc_inherited_data__misc_inherited_2_data_ = a_misc_inherited_data_->misc_inherited_2_data_.Get();
        auto* b_misc_inherited_data__misc_inherited_2_data_ = b_misc_inherited_data_->misc_inherited_2_data_.Get();
        if (a_misc_inherited_data__misc_inherited_2_data_ != b_misc_inherited_data__misc_inherited_2_data_) {
            
          if (!base::ValuesEquivalent(a_misc_inherited_data__misc_inherited_2_data_->text_shadow_, b_misc_inherited_data__misc_inherited_2_data_->text_shadow_)) {
            diff.Set(CSSPropertyID::kTextShadow);
          }
          if (a_misc_inherited_data__misc_inherited_2_data_->text_underline_offset_ != b_misc_inherited_data__misc_inherited_2_data_->text_underline_offset_) {
            diff.Set(CSSPropertyID::kTextUnderlineOffset);
          }
          if (a_misc_inherited_data__misc_inherited_2_data_->text_fill_color_ != b_misc_inherited_data__misc_inherited_2_data_->text_fill_color_) {
            diff.Set(CSSPropertyID::kWebkitTextFillColor);
          }
          if (a_misc_inherited_data__misc_inherited_2_data_->text_stroke_color_ != b_misc_inherited_data__misc_inherited_2_data_->text_stroke_color_) {
            diff.Set(CSSPropertyID::kWebkitTextStrokeColor);
          }
          if (a_misc_inherited_data__misc_inherited_2_data_->widows_ != b_misc_inherited_data__misc_inherited_2_data_->widows_) {
            diff.Set(CSSPropertyID::kWidows);
          }



        }




      }
      auto* a_misc_data_ = a.misc_data_.Get();
      auto* b_misc_data_ = b.misc_data_.Get();
      if (a_misc_data_ != b_misc_data_) {
              auto* a_misc_data__misc_1_data_ = a_misc_data_->misc_1_data_.Get();
        auto* b_misc_data__misc_1_data_ = b_misc_data_->misc_1_data_.Get();
        if (a_misc_data__misc_1_data_ != b_misc_data__misc_1_data_) {
            
          if (a_misc_data__misc_1_data_->backdrop_filter_ != b_misc_data__misc_1_data_->backdrop_filter_) {
            diff.Set(CSSPropertyID::kBackdropFilter);
          }
          if (a_misc_data__misc_1_data_->column_rule_color_ != b_misc_data__misc_1_data_->column_rule_color_) {
            diff.Set(CSSPropertyID::kColumnRuleColor);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_1_data_->border_shape_, b_misc_data__misc_1_data_->border_shape_)) {
            diff.Set(CSSPropertyID::kBorderShape);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_1_data_->box_shadow_, b_misc_data__misc_1_data_->box_shadow_)) {
            diff.Set(CSSPropertyID::kBoxShadow);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_1_data_->clip_path_, b_misc_data__misc_1_data_->clip_path_)) {
            diff.Set(CSSPropertyID::kClipPath);
          }
          if (a_misc_data__misc_1_data_->column_gap_ != b_misc_data__misc_1_data_->column_gap_) {
            diff.Set(CSSPropertyID::kColumnGap);
          }
          if (a_misc_data__misc_1_data_->column_rule_inset_cap_end_ != b_misc_data__misc_1_data_->column_rule_inset_cap_end_) {
            diff.Set(CSSPropertyID::kColumnRuleInsetCapEnd);
          }
          if (a_misc_data__misc_1_data_->column_height_ != b_misc_data__misc_1_data_->column_height_) {
            diff.Set(CSSPropertyID::kColumnHeight);
          }
          if (a_misc_data__misc_1_data_->column_count_ != b_misc_data__misc_1_data_->column_count_) {
            diff.Set(CSSPropertyID::kColumnCount);
          }



        }
        auto* a_misc_data__visited_data_ = a_misc_data_->visited_data_.Get();
        auto* b_misc_data__visited_data_ = b_misc_data_->visited_data_.Get();
        if (a_misc_data__visited_data_ != b_misc_data__visited_data_) {
            

            // column-rule-color is partially stored on internal_visited_column_rule_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_column_rule_color_ != b_misc_data__visited_data_->internal_visited_column_rule_color_) {
              diff.Set(CSSPropertyID::kColumnRuleColor);
            }
            // background-color is partially stored on internal_visited_background_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_background_color_ != b_misc_data__visited_data_->internal_visited_background_color_) {
              diff.Set(CSSPropertyID::kBackgroundColor);
            }
            // border-bottom-color is partially stored on internal_visited_border_bottom_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_border_bottom_color_ != b_misc_data__visited_data_->internal_visited_border_bottom_color_) {
              diff.Set(CSSPropertyID::kBorderBottomColor);
            }
            // border-left-color is partially stored on internal_visited_border_left_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_border_left_color_ != b_misc_data__visited_data_->internal_visited_border_left_color_) {
              diff.Set(CSSPropertyID::kBorderLeftColor);
            }
            // border-right-color is partially stored on internal_visited_border_right_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_border_right_color_ != b_misc_data__visited_data_->internal_visited_border_right_color_) {
              diff.Set(CSSPropertyID::kBorderRightColor);
            }
            // border-top-color is partially stored on internal_visited_border_top_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_border_top_color_ != b_misc_data__visited_data_->internal_visited_border_top_color_) {
              diff.Set(CSSPropertyID::kBorderTopColor);
            }
            // outline-color is partially stored on internal_visited_outline_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_outline_color_ != b_misc_data__visited_data_->internal_visited_outline_color_) {
              diff.Set(CSSPropertyID::kOutlineColor);
            }
            // text-decoration-color is partially stored on internal_visited_text_decoration_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_misc_data__visited_data_->internal_visited_text_decoration_color_ != b_misc_data__visited_data_->internal_visited_text_decoration_color_) {
              diff.Set(CSSPropertyID::kTextDecorationColor);
            }


        }
        auto* a_misc_data__misc_2_data_ = a_misc_data_->misc_2_data_.Get();
        auto* b_misc_data__misc_2_data_ = b_misc_data_->misc_2_data_.Get();
        if (a_misc_data__misc_2_data_ != b_misc_data__misc_2_data_) {
            
          if (a_misc_data__misc_2_data_->filter_ != b_misc_data__misc_2_data_->filter_) {
            diff.Set(CSSPropertyID::kFilter);
          }
          if (a_misc_data__misc_2_data_->column_rule_width_ != b_misc_data__misc_2_data_->column_rule_width_) {
            diff.Set(CSSPropertyID::kColumnRuleWidth);
          }
          if (a_misc_data__misc_2_data_->column_rule_inset_cap_start_ != b_misc_data__misc_2_data_->column_rule_inset_cap_start_) {
            diff.Set(CSSPropertyID::kColumnRuleInsetCapStart);
          }
          if (a_misc_data__misc_2_data_->column_rule_inset_junction_end_ != b_misc_data__misc_2_data_->column_rule_inset_junction_end_) {
            diff.Set(CSSPropertyID::kColumnRuleInsetJunctionEnd);
          }
          if (a_misc_data__misc_2_data_->column_rule_inset_junction_start_ != b_misc_data__misc_2_data_->column_rule_inset_junction_start_) {
            diff.Set(CSSPropertyID::kColumnRuleInsetJunctionStart);
          }
          if (a_misc_data__misc_2_data_->flex_basis_ != b_misc_data__misc_2_data_->flex_basis_) {
            diff.Set(CSSPropertyID::kFlexBasis);
          }
          if (a_misc_data__misc_2_data_->column_width_ != b_misc_data__misc_2_data_->column_width_) {
            diff.Set(CSSPropertyID::kColumnWidth);
          }
          if (a_misc_data__misc_2_data_->flex_grow_ != b_misc_data__misc_2_data_->flex_grow_) {
            diff.Set(CSSPropertyID::kFlexGrow);
          }
          if (a_misc_data__misc_2_data_->flex_shrink_ != b_misc_data__misc_2_data_->flex_shrink_) {
            diff.Set(CSSPropertyID::kFlexShrink);
          }
          if (a_misc_data__misc_2_data_->flex_line_count_ != b_misc_data__misc_2_data_->flex_line_count_) {
            diff.Set(CSSPropertyID::kFlexLineCount);
          }



        }
        auto* a_misc_data__misc_3_data_ = a_misc_data_->misc_3_data_.Get();
        auto* b_misc_data__misc_3_data_ = b_misc_data_->misc_3_data_.Get();
        if (a_misc_data__misc_3_data_ != b_misc_data__misc_3_data_) {
            
          if (!base::ValuesEquivalent(a_misc_data__misc_3_data_->grid_template_columns_, b_misc_data__misc_3_data_->grid_template_columns_)) {
            diff.Set(CSSPropertyID::kGridTemplateColumns);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_3_data_->grid_template_rows_, b_misc_data__misc_3_data_->grid_template_rows_)) {
            diff.Set(CSSPropertyID::kGridTemplateRows);
          }
          if (a_misc_data__misc_3_data_->object_position_ != b_misc_data__misc_3_data_->object_position_) {
            diff.Set(CSSPropertyID::kObjectPosition);
          }
          if (a_misc_data__misc_3_data_->interest_delay_end_ != b_misc_data__misc_3_data_->interest_delay_end_) {
            diff.Set(CSSPropertyID::kInterestDelayEnd);
          }
          if (a_misc_data__misc_3_data_->interest_delay_start_ != b_misc_data__misc_3_data_->interest_delay_start_) {
            diff.Set(CSSPropertyID::kInterestDelayStart);
          }



        }
        auto* a_misc_data__forced_colors_data_ = a_misc_data_->forced_colors_data_.Get();
        auto* b_misc_data__forced_colors_data_ = b_misc_data_->forced_colors_data_.Get();
        if (a_misc_data__forced_colors_data_ != b_misc_data__forced_colors_data_) {
            



        }
        auto* a_misc_data__misc_4_data_ = a_misc_data_->misc_4_data_.Get();
        auto* b_misc_data__misc_4_data_ = b_misc_data_->misc_4_data_.Get();
        if (a_misc_data__misc_4_data_ != b_misc_data__misc_4_data_) {
            
          if (!base::ValuesEquivalent(a_misc_data__misc_4_data_->object_view_box_, b_misc_data__misc_4_data_->object_view_box_)) {
            diff.Set(CSSPropertyID::kObjectViewBox);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_4_data_->offset_path_, b_misc_data__misc_4_data_->offset_path_)) {
            diff.Set(CSSPropertyID::kOffsetPath);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_4_data_->rotate_, b_misc_data__misc_4_data_->rotate_)) {
            diff.Set(CSSPropertyID::kRotate);
          }
          if (a_misc_data__misc_4_data_->offset_rotate_ != b_misc_data__misc_4_data_->offset_rotate_) {
            diff.Set(CSSPropertyID::kOffsetRotate);
          }
          if (a_misc_data__misc_4_data_->offset_anchor_ != b_misc_data__misc_4_data_->offset_anchor_) {
            diff.Set(CSSPropertyID::kOffsetAnchor);
          }
          if (a_misc_data__misc_4_data_->offset_position_ != b_misc_data__misc_4_data_->offset_position_) {
            diff.Set(CSSPropertyID::kOffsetPosition);
          }
          if (a_misc_data__misc_4_data_->perspective_origin_ != b_misc_data__misc_4_data_->perspective_origin_) {
            diff.Set(CSSPropertyID::kPerspectiveOrigin);
          }
          if (a_misc_data__misc_4_data_->offset_distance_ != b_misc_data__misc_4_data_->offset_distance_) {
            diff.Set(CSSPropertyID::kOffsetDistance);
          }
          if (a_misc_data__misc_4_data_->perspective_ != b_misc_data__misc_4_data_->perspective_) {
            diff.Set(CSSPropertyID::kPerspective);
          }
          if (a_misc_data__misc_4_data_->outline_color_ != b_misc_data__misc_4_data_->outline_color_) {
            diff.Set(CSSPropertyID::kOutlineColor);
          }
          if (a_misc_data__misc_4_data_->order_ != b_misc_data__misc_4_data_->order_) {
            diff.Set(CSSPropertyID::kOrder);
          }
          if (a_misc_data__misc_4_data_->outline_offset_ != b_misc_data__misc_4_data_->outline_offset_) {
            diff.Set(CSSPropertyID::kOutlineOffset);
          }
          if (a_misc_data__misc_4_data_->outline_width_ != b_misc_data__misc_4_data_->outline_width_) {
            diff.Set(CSSPropertyID::kOutlineWidth);
          }
          if (a_misc_data__misc_4_data_->reading_order_ != b_misc_data__misc_4_data_->reading_order_) {
            diff.Set(CSSPropertyID::kReadingOrder);
          }



        }
        auto* a_misc_data__misc_5_data_ = a_misc_data_->misc_5_data_.Get();
        auto* b_misc_data__misc_5_data_ = b_misc_data_->misc_5_data_.Get();
        if (a_misc_data__misc_5_data_ != b_misc_data__misc_5_data_) {
            
          if (a_misc_data__misc_5_data_->row_rule_color_ != b_misc_data__misc_5_data_->row_rule_color_) {
            diff.Set(CSSPropertyID::kRowRuleColor);
          }
          if (a_misc_data__misc_5_data_->row_rule_width_ != b_misc_data__misc_5_data_->row_rule_width_) {
            diff.Set(CSSPropertyID::kRowRuleWidth);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_5_data_->scale_, b_misc_data__misc_5_data_->scale_)) {
            diff.Set(CSSPropertyID::kScale);
          }
          if (a_misc_data__misc_5_data_->row_gap_ != b_misc_data__misc_5_data_->row_gap_) {
            diff.Set(CSSPropertyID::kRowGap);
          }
          if (a_misc_data__misc_5_data_->row_rule_inset_cap_end_ != b_misc_data__misc_5_data_->row_rule_inset_cap_end_) {
            diff.Set(CSSPropertyID::kRowRuleInsetCapEnd);
          }
          if (a_misc_data__misc_5_data_->row_rule_inset_cap_start_ != b_misc_data__misc_5_data_->row_rule_inset_cap_start_) {
            diff.Set(CSSPropertyID::kRowRuleInsetCapStart);
          }
          if (a_misc_data__misc_5_data_->row_rule_inset_junction_end_ != b_misc_data__misc_5_data_->row_rule_inset_junction_end_) {
            diff.Set(CSSPropertyID::kRowRuleInsetJunctionEnd);
          }
          if (a_misc_data__misc_5_data_->row_rule_inset_junction_start_ != b_misc_data__misc_5_data_->row_rule_inset_junction_start_) {
            diff.Set(CSSPropertyID::kRowRuleInsetJunctionStart);
          }



        }
        auto* a_misc_data__misc_6_data_ = a_misc_data_->misc_6_data_.Get();
        auto* b_misc_data__misc_6_data_ = b_misc_data_->misc_6_data_.Get();
        if (a_misc_data__misc_6_data_ != b_misc_data__misc_6_data_) {
            
          if (!base::ValuesEquivalent(a_misc_data__misc_6_data_->shape_outside_, b_misc_data__misc_6_data_->shape_outside_)) {
            diff.Set(CSSPropertyID::kShapeOutside);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_6_data_->translate_, b_misc_data__misc_6_data_->translate_)) {
            diff.Set(CSSPropertyID::kTranslate);
          }
          if (a_misc_data__misc_6_data_->shape_margin_ != b_misc_data__misc_6_data_->shape_margin_) {
            diff.Set(CSSPropertyID::kShapeMargin);
          }
          if (a_misc_data__misc_6_data_->shape_image_threshold_ != b_misc_data__misc_6_data_->shape_image_threshold_) {
            diff.Set(CSSPropertyID::kShapeImageThreshold);
          }
          if (a_misc_data__misc_6_data_->text_decoration_color_ != b_misc_data__misc_6_data_->text_decoration_color_) {
            diff.Set(CSSPropertyID::kTextDecorationColor);
          }



        }
        auto* a_misc_data__timeline_data_ = a_misc_data_->timeline_data_.Get();
        auto* b_misc_data__timeline_data_ = b_misc_data_->timeline_data_.Get();
        if (a_misc_data__timeline_data_ != b_misc_data__timeline_data_) {
            



        }
        auto* a_misc_data__misc_7_data_ = a_misc_data_->misc_7_data_.Get();
        auto* b_misc_data__misc_7_data_ = b_misc_data_->misc_7_data_.Get();
        if (a_misc_data__misc_7_data_ != b_misc_data__misc_7_data_) {
            


            if (a_misc_data__misc_7_data_->mask_ != b_misc_data__misc_7_data_->mask_) {
                  // mask-size is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskSize);
                  // -webkit-mask-position-x is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskPositionX);
                  // -webkit-mask-position-y is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskPositionY);
            }
            if (a_misc_data__misc_7_data_->mask_box_image_ != b_misc_data__misc_7_data_->mask_box_image_) {
                  // -webkit-mask-box-image-outset is stored on mask_box_image_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskBoxImageOutset);
                  // -webkit-mask-box-image-slice is stored on mask_box_image_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskBoxImageSlice);
                  // -webkit-mask-box-image-source is stored on mask_box_image_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskBoxImageSource);
                  // -webkit-mask-box-image-width is stored on mask_box_image_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskBoxImageWidth);
            }

        }
        auto* a_misc_data__misc_8_data_ = a_misc_data_->misc_8_data_.Get();
        auto* b_misc_data__misc_8_data_ = b_misc_data_->misc_8_data_.Get();
        if (a_misc_data__misc_8_data_ != b_misc_data__misc_8_data_) {
            



        }
        auto* a_misc_data__math_data_ = a_misc_data_->math_data_.Get();
        auto* b_misc_data__math_data_ = b_misc_data_->math_data_.Get();
        if (a_misc_data__math_data_ != b_misc_data__math_data_) {
            



        }




      }
      auto* a_inherited_data_ = a.inherited_data_.Get();
      auto* b_inherited_data_ = b.inherited_data_.Get();
      if (a_inherited_data_ != b_inherited_data_) {
              auto* a_inherited_data__inherited_forced_colors_data_ = a_inherited_data_->inherited_forced_colors_data_.Get();
        auto* b_inherited_data__inherited_forced_colors_data_ = b_inherited_data_->inherited_forced_colors_data_.Get();
        if (a_inherited_data__inherited_forced_colors_data_ != b_inherited_data__inherited_forced_colors_data_) {
            



        }
        auto* a_inherited_data__inherited_visited_data_ = a_inherited_data_->inherited_visited_data_.Get();
        auto* b_inherited_data__inherited_visited_data_ = b_inherited_data_->inherited_visited_data_.Get();
        if (a_inherited_data__inherited_visited_data_ != b_inherited_data__inherited_visited_data_) {
            

            // text-emphasis-color is partially stored on internal_visited_text_emphasis_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_inherited_data__inherited_visited_data_->internal_visited_text_emphasis_color_ != b_inherited_data__inherited_visited_data_->internal_visited_text_emphasis_color_) {
              diff.Set(CSSPropertyID::kTextEmphasisColor);
            }
            // -webkit-text-fill-color is partially stored on internal_visited_text_fill_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_inherited_data__inherited_visited_data_->internal_visited_text_fill_color_ != b_inherited_data__inherited_visited_data_->internal_visited_text_fill_color_) {
              diff.Set(CSSPropertyID::kWebkitTextFillColor);
            }
            // -webkit-text-stroke-color is partially stored on internal_visited_text_stroke_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_inherited_data__inherited_visited_data_->internal_visited_text_stroke_color_ != b_inherited_data__inherited_visited_data_->internal_visited_text_stroke_color_) {
              diff.Set(CSSPropertyID::kWebkitTextStrokeColor);
            }
            // caret-color is partially stored on internal_visited_caret_color_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_inherited_data__inherited_visited_data_->internal_visited_caret_color_ != b_inherited_data__inherited_visited_data_->internal_visited_caret_color_) {
              diff.Set(CSSPropertyID::kCaretColor);
            }


        }
        auto* a_inherited_data__highlight_data_data_ = a_inherited_data_->highlight_data_data_.Get();
        auto* b_inherited_data__highlight_data_data_ = b_inherited_data_->highlight_data_data_.Get();
        if (a_inherited_data__highlight_data_data_ != b_inherited_data__highlight_data_data_) {
            



        }

        if (a_inherited_data_->letter_spacing_ != b_inherited_data_->letter_spacing_) {
          diff.Set(CSSPropertyID::kLetterSpacing);
        }
        if (a_inherited_data_->line_height_ != b_inherited_data_->line_height_) {
          diff.Set(CSSPropertyID::kLineHeight);
        }
        if (a_inherited_data_->word_spacing_ != b_inherited_data_->word_spacing_) {
          diff.Set(CSSPropertyID::kWordSpacing);
        }
        if (a_inherited_data_->color_ != b_inherited_data_->color_) {
          diff.Set(CSSPropertyID::kColor);
        }
        if (a_inherited_data_->horizontal_border_spacing_ != b_inherited_data_->horizontal_border_spacing_) {
          diff.Set(CSSPropertyID::kWebkitBorderHorizontalSpacing);
        }
        if (a_inherited_data_->vertical_border_spacing_ != b_inherited_data_->vertical_border_spacing_) {
          diff.Set(CSSPropertyID::kWebkitBorderVerticalSpacing);
        }

          // color is partially stored on internal_visited_color_ in this group
          // (which may not be the same as its home group), so test it here too.
          if (a_inherited_data_->internal_visited_color_ != b_inherited_data_->internal_visited_color_) {
            diff.Set(CSSPropertyID::kColor);
          }

          if (!base::ValuesEquivalent(a_inherited_data_->font_, b_inherited_data_->font_)) {
                // font-palette is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontPalette);
                // font-size is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontSize);
                // font-size-adjust is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontSizeAdjust);
                // font-stretch is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontStretch);
                // font-style is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontStyle);
                // font-variation-settings is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariationSettings);
                // font-weight is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontWeight);
                // letter-spacing is partially stored on font_ in this group
                // (which may not be the same as its home group), so test it here too.
                diff.Set(CSSPropertyID::kLetterSpacing);
                // word-spacing is partially stored on font_ in this group
                // (which may not be the same as its home group), so test it here too.
                diff.Set(CSSPropertyID::kWordSpacing);
          }

      }
      auto* a_visual_data_ = a.visual_data_.Get();
      auto* b_visual_data_ = b.visual_data_.Get();
      if (a_visual_data_ != b_visual_data_) {
          
        if (a_visual_data_->clip_ != b_visual_data_->clip_) {
          diff.Set(CSSPropertyID::kClip);
        }



      }
      auto* a_svginherited_data_ = a.svginherited_data_.Get();
      auto* b_svginherited_data_ = b.svginherited_data_.Get();
      if (a_svginherited_data_ != b_svginherited_data_) {
              auto* a_svginherited_data__fill_data_ = a_svginherited_data_->fill_data_.Get();
        auto* b_svginherited_data__fill_data_ = b_svginherited_data_->fill_data_.Get();
        if (a_svginherited_data__fill_data_ != b_svginherited_data__fill_data_) {
            
          if (a_svginherited_data__fill_data_->fill_paint_ != b_svginherited_data__fill_data_->fill_paint_) {
            diff.Set(CSSPropertyID::kFill);
          }
          if (a_svginherited_data__fill_data_->fill_opacity_ != b_svginherited_data__fill_data_->fill_opacity_) {
            diff.Set(CSSPropertyID::kFillOpacity);
          }

            // fill is partially stored on internal_visited_fill_paint_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_svginherited_data__fill_data_->internal_visited_fill_paint_ != b_svginherited_data__fill_data_->internal_visited_fill_paint_) {
              diff.Set(CSSPropertyID::kFill);
            }


        }
        auto* a_svginherited_data__stroke_data_ = a_svginherited_data_->stroke_data_.Get();
        auto* b_svginherited_data__stroke_data_ = b_svginherited_data_->stroke_data_.Get();
        if (a_svginherited_data__stroke_data_ != b_svginherited_data__stroke_data_) {
            
          if (a_svginherited_data__stroke_data_->stroke_paint_ != b_svginherited_data__stroke_data_->stroke_paint_) {
            diff.Set(CSSPropertyID::kStroke);
          }
          if (!base::ValuesEquivalent(a_svginherited_data__stroke_data_->stroke_dash_array_, b_svginherited_data__stroke_data_->stroke_dash_array_)) {
            diff.Set(CSSPropertyID::kStrokeDasharray);
          }
          if (a_svginherited_data__stroke_data_->stroke_dash_offset_ != b_svginherited_data__stroke_data_->stroke_dash_offset_) {
            diff.Set(CSSPropertyID::kStrokeDashoffset);
          }
          if (a_svginherited_data__stroke_data_->stroke_width_ != b_svginherited_data__stroke_data_->stroke_width_) {
            diff.Set(CSSPropertyID::kStrokeWidth);
          }
          if (a_svginherited_data__stroke_data_->stroke_miter_limit_ != b_svginherited_data__stroke_data_->stroke_miter_limit_) {
            diff.Set(CSSPropertyID::kStrokeMiterlimit);
          }
          if (a_svginherited_data__stroke_data_->stroke_opacity_ != b_svginherited_data__stroke_data_->stroke_opacity_) {
            diff.Set(CSSPropertyID::kStrokeOpacity);
          }

            // stroke is partially stored on internal_visited_stroke_paint_ in this group
            // (which may not be the same as its home group), so test it here too.
            if (a_svginherited_data__stroke_data_->internal_visited_stroke_paint_ != b_svginherited_data__stroke_data_->internal_visited_stroke_paint_) {
              diff.Set(CSSPropertyID::kStroke);
            }


        }
        auto* a_svginherited_data__resources_data_ = a_svginherited_data_->resources_data_.Get();
        auto* b_svginherited_data__resources_data_ = b_svginherited_data_->resources_data_.Get();
        if (a_svginherited_data__resources_data_ != b_svginherited_data__resources_data_) {
            



        }




      }
      auto* a_box_data_ = a.box_data_.Get();
      auto* b_box_data_ = b.box_data_.Get();
      if (a_box_data_ != b_box_data_) {
          
        if (a_box_data_->height_ != b_box_data_->height_) {
          diff.Set(CSSPropertyID::kHeight);
        }
        if (a_box_data_->margin_bottom_ != b_box_data_->margin_bottom_) {
          diff.Set(CSSPropertyID::kMarginBottom);
        }
        if (a_box_data_->margin_left_ != b_box_data_->margin_left_) {
          diff.Set(CSSPropertyID::kMarginLeft);
        }
        if (a_box_data_->margin_right_ != b_box_data_->margin_right_) {
          diff.Set(CSSPropertyID::kMarginRight);
        }
        if (a_box_data_->margin_top_ != b_box_data_->margin_top_) {
          diff.Set(CSSPropertyID::kMarginTop);
        }
        if (a_box_data_->max_height_ != b_box_data_->max_height_) {
          diff.Set(CSSPropertyID::kMaxHeight);
        }
        if (a_box_data_->max_width_ != b_box_data_->max_width_) {
          diff.Set(CSSPropertyID::kMaxWidth);
        }
        if (a_box_data_->min_height_ != b_box_data_->min_height_) {
          diff.Set(CSSPropertyID::kMinHeight);
        }
        if (a_box_data_->min_width_ != b_box_data_->min_width_) {
          diff.Set(CSSPropertyID::kMinWidth);
        }
        if (a_box_data_->padding_bottom_ != b_box_data_->padding_bottom_) {
          diff.Set(CSSPropertyID::kPaddingBottom);
        }
        if (a_box_data_->padding_left_ != b_box_data_->padding_left_) {
          diff.Set(CSSPropertyID::kPaddingLeft);
        }
        if (a_box_data_->padding_right_ != b_box_data_->padding_right_) {
          diff.Set(CSSPropertyID::kPaddingRight);
        }
        if (a_box_data_->padding_top_ != b_box_data_->padding_top_) {
          diff.Set(CSSPropertyID::kPaddingTop);
        }
        if (a_box_data_->width_ != b_box_data_->width_) {
          diff.Set(CSSPropertyID::kWidth);
        }
        if (a_box_data_->border_bottom_width_ != b_box_data_->border_bottom_width_) {
          diff.Set(CSSPropertyID::kBorderBottomWidth);
        }
        if (a_box_data_->border_left_width_ != b_box_data_->border_left_width_) {
          diff.Set(CSSPropertyID::kBorderLeftWidth);
        }
        if (a_box_data_->border_right_width_ != b_box_data_->border_right_width_) {
          diff.Set(CSSPropertyID::kBorderRightWidth);
        }
        if (a_box_data_->border_top_width_ != b_box_data_->border_top_width_) {
          diff.Set(CSSPropertyID::kBorderTopWidth);
        }
        if (a_box_data_->z_index_ != b_box_data_->z_index_) {
          diff.Set(CSSPropertyID::kZIndex);
        }


          if (a_box_data_->vertical_align_length_ != b_box_data_->vertical_align_length_) {
                // vertical-align is stored on vertical_align_length_ in this group, so test it here.
                diff.Set(CSSPropertyID::kVerticalAlign);
          }
          if (a_box_data_->has_auto_z_index_ != b_box_data_->has_auto_z_index_) {
                // z-index is partially stored on has_auto_z_index_ in this group
                // (which may not be the same as its home group), so test it here too.
                diff.Set(CSSPropertyID::kZIndex);
          }

      }
      auto* a_svg_data_ = a.svg_data_.Get();
      auto* b_svg_data_ = b.svg_data_.Get();
      if (a_svg_data_ != b_svg_data_) {
              auto* a_svg_data__svgmisc_data_ = a_svg_data_->svgmisc_data_.Get();
        auto* b_svg_data__svgmisc_data_ = b_svg_data_->svgmisc_data_.Get();
        if (a_svg_data__svgmisc_data_ != b_svg_data__svgmisc_data_) {
            
          if (a_svg_data__svgmisc_data_->baseline_shift_ != b_svg_data__svgmisc_data_->baseline_shift_) {
            diff.Set(CSSPropertyID::kBaselineShift);
          }
          if (a_svg_data__svgmisc_data_->flood_opacity_ != b_svg_data__svgmisc_data_->flood_opacity_) {
            diff.Set(CSSPropertyID::kFloodOpacity);
          }
          if (a_svg_data__svgmisc_data_->flood_color_ != b_svg_data__svgmisc_data_->flood_color_) {
            diff.Set(CSSPropertyID::kFloodColor);
          }
          if (a_svg_data__svgmisc_data_->lighting_color_ != b_svg_data__svgmisc_data_->lighting_color_) {
            diff.Set(CSSPropertyID::kLightingColor);
          }



        }
        auto* a_svg_data__geometry_data_ = a_svg_data_->geometry_data_.Get();
        auto* b_svg_data__geometry_data_ = b_svg_data_->geometry_data_.Get();
        if (a_svg_data__geometry_data_ != b_svg_data__geometry_data_) {
            
          if (!base::ValuesEquivalent(a_svg_data__geometry_data_->d_, b_svg_data__geometry_data_->d_)) {
            diff.Set(CSSPropertyID::kD);
          }
          if (a_svg_data__geometry_data_->cx_ != b_svg_data__geometry_data_->cx_) {
            diff.Set(CSSPropertyID::kCx);
          }
          if (a_svg_data__geometry_data_->cy_ != b_svg_data__geometry_data_->cy_) {
            diff.Set(CSSPropertyID::kCy);
          }
          if (a_svg_data__geometry_data_->r_ != b_svg_data__geometry_data_->r_) {
            diff.Set(CSSPropertyID::kR);
          }
          if (a_svg_data__geometry_data_->rx_ != b_svg_data__geometry_data_->rx_) {
            diff.Set(CSSPropertyID::kRx);
          }
          if (a_svg_data__geometry_data_->ry_ != b_svg_data__geometry_data_->ry_) {
            diff.Set(CSSPropertyID::kRy);
          }
          if (a_svg_data__geometry_data_->x_ != b_svg_data__geometry_data_->x_) {
            diff.Set(CSSPropertyID::kX);
          }
          if (a_svg_data__geometry_data_->y_ != b_svg_data__geometry_data_->y_) {
            diff.Set(CSSPropertyID::kY);
          }
          if (a_svg_data__geometry_data_->path_length_ != b_svg_data__geometry_data_->path_length_) {
            diff.Set(CSSPropertyID::kPathLength);
          }



        }
        auto* a_svg_data__stop_data_ = a_svg_data_->stop_data_.Get();
        auto* b_svg_data__stop_data_ = b_svg_data_->stop_data_.Get();
        if (a_svg_data__stop_data_ != b_svg_data__stop_data_) {
            
          if (a_svg_data__stop_data_->stop_opacity_ != b_svg_data__stop_data_->stop_opacity_) {
            diff.Set(CSSPropertyID::kStopOpacity);
          }
          if (a_svg_data__stop_data_->stop_color_ != b_svg_data__stop_data_->stop_color_) {
            diff.Set(CSSPropertyID::kStopColor);
          }



        }

        if (a_svg_data_->transform_ != b_svg_data_->transform_) {
          diff.Set(CSSPropertyID::kTransform);
        }
        if (a_svg_data_->transform_origin_ != b_svg_data_->transform_origin_) {
          diff.Set(CSSPropertyID::kTransformOrigin);
        }
        if (a_svg_data_->opacity_ != b_svg_data_->opacity_) {
          diff.Set(CSSPropertyID::kOpacity);
        }



      }
      auto* a_surround_data_ = a.surround_data_.Get();
      auto* b_surround_data_ = b.surround_data_.Get();
      if (a_surround_data_ != b_surround_data_) {
          
        if (a_surround_data_->corner_bottom_left_shape_ != b_surround_data_->corner_bottom_left_shape_) {
          diff.Set(CSSPropertyID::kCornerBottomLeftShape);
        }
        if (a_surround_data_->corner_bottom_right_shape_ != b_surround_data_->corner_bottom_right_shape_) {
          diff.Set(CSSPropertyID::kCornerBottomRightShape);
        }
        if (a_surround_data_->corner_top_left_shape_ != b_surround_data_->corner_top_left_shape_) {
          diff.Set(CSSPropertyID::kCornerTopLeftShape);
        }
        if (a_surround_data_->corner_top_right_shape_ != b_surround_data_->corner_top_right_shape_) {
          diff.Set(CSSPropertyID::kCornerTopRightShape);
        }
        if (a_surround_data_->aspect_ratio_ != b_surround_data_->aspect_ratio_) {
          diff.Set(CSSPropertyID::kAspectRatio);
        }
        if (a_surround_data_->contain_intrinsic_height_ != b_surround_data_->contain_intrinsic_height_) {
          diff.Set(CSSPropertyID::kContainIntrinsicHeight);
        }
        if (a_surround_data_->contain_intrinsic_width_ != b_surround_data_->contain_intrinsic_width_) {
          diff.Set(CSSPropertyID::kContainIntrinsicWidth);
        }
        if (a_surround_data_->border_bottom_left_radius_ != b_surround_data_->border_bottom_left_radius_) {
          diff.Set(CSSPropertyID::kBorderBottomLeftRadius);
        }
        if (a_surround_data_->border_bottom_right_radius_ != b_surround_data_->border_bottom_right_radius_) {
          diff.Set(CSSPropertyID::kBorderBottomRightRadius);
        }
        if (a_surround_data_->border_top_left_radius_ != b_surround_data_->border_top_left_radius_) {
          diff.Set(CSSPropertyID::kBorderTopLeftRadius);
        }
        if (a_surround_data_->border_top_right_radius_ != b_surround_data_->border_top_right_radius_) {
          diff.Set(CSSPropertyID::kBorderTopRightRadius);
        }
        if (a_surround_data_->bottom_ != b_surround_data_->bottom_) {
          diff.Set(CSSPropertyID::kBottom);
        }
        if (a_surround_data_->left_ != b_surround_data_->left_) {
          diff.Set(CSSPropertyID::kLeft);
        }
        if (a_surround_data_->right_ != b_surround_data_->right_) {
          diff.Set(CSSPropertyID::kRight);
        }
        if (a_surround_data_->top_ != b_surround_data_->top_) {
          diff.Set(CSSPropertyID::kTop);
        }
        if (a_surround_data_->border_bottom_color_ != b_surround_data_->border_bottom_color_) {
          diff.Set(CSSPropertyID::kBorderBottomColor);
        }
        if (a_surround_data_->border_left_color_ != b_surround_data_->border_left_color_) {
          diff.Set(CSSPropertyID::kBorderLeftColor);
        }
        if (a_surround_data_->border_right_color_ != b_surround_data_->border_right_color_) {
          diff.Set(CSSPropertyID::kBorderRightColor);
        }
        if (a_surround_data_->border_top_color_ != b_surround_data_->border_top_color_) {
          diff.Set(CSSPropertyID::kBorderTopColor);
        }


          if (a_surround_data_->border_image_ != b_surround_data_->border_image_) {
                // border-image-outset is stored on border_image_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBorderImageOutset);
                // border-image-slice is stored on border_image_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBorderImageSlice);
                // border-image-source is stored on border_image_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBorderImageSource);
                // border-image-width is stored on border_image_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBorderImageWidth);
          }

      }
      auto* a_background_data_ = a.background_data_.Get();
      auto* b_background_data_ = b.background_data_.Get();
      if (a_background_data_ != b_background_data_) {
          
        if (a_background_data_->background_color_ != b_background_data_->background_color_) {
          diff.Set(CSSPropertyID::kBackgroundColor);
        }


          if (a_background_data_->background_ != b_background_data_->background_) {
                // background-image is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundImage);
                // background-position-x is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundPositionX);
                // background-position-y is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundPositionY);
                // background-size is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundSize);
          }

      }

      if (a.data_.visibility_ != b.data_.visibility_) {
        diff.Set(CSSPropertyID::kVisibility);
      }


        if (a.data_.vertical_align_ != b.data_.vertical_align_) {
              // vertical-align is stored on vertical_align_ in this group, so test it here.
              diff.Set(CSSPropertyID::kVerticalAlign);
        }



  return diff;
}

CSSBitset ComputedStyleBase::TransitionAllWithDiscreteDiff(const ComputedStyle& a, const ComputedStyle& b) {
  // In order to avoid too much code bloat, we make TransitionAllWithDiscreteDiff()
  // call TransitionAllDiff() to reuse its code for what it can do, even though
  // it will be somewhat less efficient (we need to check group pointers twice).
  CSSBitset diff = TransitionAllDiff(a, b);

  // Everything below is related to discrete properties.
        auto* a_misc_inherited_data_ = a.misc_inherited_data_.Get();
      auto* b_misc_inherited_data_ = b.misc_inherited_data_.Get();
      if (a_misc_inherited_data_ != b_misc_inherited_data_) {
              auto* a_misc_inherited_data__misc_inherited_1_data_ = a_misc_inherited_data_->misc_inherited_1_data_.Get();
        auto* b_misc_inherited_data__misc_inherited_1_data_ = b_misc_inherited_data_->misc_inherited_1_data_.Get();
        if (a_misc_inherited_data__misc_inherited_1_data_ != b_misc_inherited_data__misc_inherited_1_data_) {
            
          if (a_misc_inherited_data__misc_inherited_1_data_->color_scheme_ != b_misc_inherited_data__misc_inherited_1_data_->color_scheme_) {
            diff.Set(CSSPropertyID::kColorScheme);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->hyphenation_string_ != b_misc_inherited_data__misc_inherited_1_data_->hyphenation_string_) {
            diff.Set(CSSPropertyID::kHyphenateCharacter);
          }
          if (!base::ValuesEquivalent(a_misc_inherited_data__misc_inherited_1_data_->quotes_, b_misc_inherited_data__misc_inherited_1_data_->quotes_)) {
            diff.Set(CSSPropertyID::kQuotes);
          }
          if (!base::ValuesEquivalent(a_misc_inherited_data__misc_inherited_1_data_->list_style_type_, b_misc_inherited_data__misc_inherited_1_data_->list_style_type_)) {
            diff.Set(CSSPropertyID::kListStyleType);
          }
          if (a_misc_inherited_data__misc_inherited_1_data_->hyphenate_limit_chars_ != b_misc_inherited_data__misc_inherited_1_data_->hyphenate_limit_chars_) {
            diff.Set(CSSPropertyID::kHyphenateLimitChars);
          }



        }
        auto* a_misc_inherited_data__misc_inherited_2_data_ = a_misc_inherited_data_->misc_inherited_2_data_.Get();
        auto* b_misc_inherited_data__misc_inherited_2_data_ = b_misc_inherited_data_->misc_inherited_2_data_.Get();
        if (a_misc_inherited_data__misc_inherited_2_data_ != b_misc_inherited_data__misc_inherited_2_data_) {
            
          if (a_misc_inherited_data__misc_inherited_2_data_->text_stroke_width_ != b_misc_inherited_data__misc_inherited_2_data_->text_stroke_width_) {
            diff.Set(CSSPropertyID::kWebkitTextStrokeWidth);
          }
          if (a_misc_inherited_data__misc_inherited_2_data_->tap_highlight_color_ != b_misc_inherited_data__misc_inherited_2_data_->tap_highlight_color_) {
            diff.Set(CSSPropertyID::kWebkitTapHighlightColor);
          }


            if (a_misc_inherited_data__misc_inherited_2_data_->text_emphasis_custom_mark_ != b_misc_inherited_data__misc_inherited_2_data_->text_emphasis_custom_mark_) {
                  // text-emphasis-style is stored on text_emphasis_custom_mark_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kTextEmphasisStyle);
            }

        }

        if (a_misc_inherited_data_->text_box_edge_ != b_misc_inherited_data_->text_box_edge_) {
          diff.Set(CSSPropertyID::kTextBoxEdge);
        }
        if (a_misc_inherited_data_->text_underline_position_ != b_misc_inherited_data_->text_underline_position_) {
          diff.Set(CSSPropertyID::kTextUnderlinePosition);
        }
        if (a_misc_inherited_data_->hanging_punctuation_ != b_misc_inherited_data_->hanging_punctuation_) {
          diff.Set(CSSPropertyID::kHangingPunctuation);
        }
        if (a_misc_inherited_data_->image_rendering_ != b_misc_inherited_data_->image_rendering_) {
          diff.Set(CSSPropertyID::kImageRendering);
        }
        if (a_misc_inherited_data_->line_break_ != b_misc_inherited_data_->line_break_) {
          diff.Set(CSSPropertyID::kLineBreak);
             diff.Set(CSSPropertyID::kWebkitLineBreak);  // Surrogate.
        }
        if (a_misc_inherited_data_->speak_ != b_misc_inherited_data_->speak_) {
          diff.Set(CSSPropertyID::kSpeak);
        }
        if (a_misc_inherited_data_->text_align_last_ != b_misc_inherited_data_->text_align_last_) {
          diff.Set(CSSPropertyID::kTextAlignLast);
        }
        if (a_misc_inherited_data_->text_decoration_skip_spaces_ != b_misc_inherited_data_->text_decoration_skip_spaces_) {
          diff.Set(CSSPropertyID::kTextDecorationSkipSpaces);
        }
        if (a_misc_inherited_data_->block_ellipsis_ != b_misc_inherited_data_->block_ellipsis_) {
          diff.Set(CSSPropertyID::kBlockEllipsis);
        }
        if (a_misc_inherited_data_->text_emphasis_position_ != b_misc_inherited_data_->text_emphasis_position_) {
          diff.Set(CSSPropertyID::kTextEmphasisPosition);
        }
        if (a_misc_inherited_data_->user_select_ != b_misc_inherited_data_->user_select_) {
          diff.Set(CSSPropertyID::kUserSelect);
        }
        if (a_misc_inherited_data_->word_break_ != b_misc_inherited_data_->word_break_) {
          diff.Set(CSSPropertyID::kWordBreak);
        }
        if (a_misc_inherited_data_->forced_color_adjust_ != b_misc_inherited_data_->forced_color_adjust_) {
          diff.Set(CSSPropertyID::kForcedColorAdjust);
        }
        if (a_misc_inherited_data_->hyphens_ != b_misc_inherited_data_->hyphens_) {
          diff.Set(CSSPropertyID::kHyphens);
        }
        if (a_misc_inherited_data_->image_animation_ != b_misc_inherited_data_->image_animation_) {
          diff.Set(CSSPropertyID::kImageAnimation);
        }
        if (a_misc_inherited_data_->overflow_wrap_ != b_misc_inherited_data_->overflow_wrap_) {
          diff.Set(CSSPropertyID::kOverflowWrap);
        }
        if (a_misc_inherited_data_->ruby_align_ != b_misc_inherited_data_->ruby_align_) {
          diff.Set(CSSPropertyID::kRubyAlign);
        }
        if (a_misc_inherited_data_->text_decoration_skip_ink_ != b_misc_inherited_data_->text_decoration_skip_ink_) {
          diff.Set(CSSPropertyID::kTextDecorationSkipInk);
        }
        if (a_misc_inherited_data_->text_justify_ != b_misc_inherited_data_->text_justify_) {
          diff.Set(CSSPropertyID::kTextJustify);
        }
        if (a_misc_inherited_data_->text_security_ != b_misc_inherited_data_->text_security_) {
          diff.Set(CSSPropertyID::kWebkitTextSecurity);
        }
        if (a_misc_inherited_data_->user_modify_ != b_misc_inherited_data_->user_modify_) {
          diff.Set(CSSPropertyID::kWebkitUserModify);
        }
        if (a_misc_inherited_data_->empty_cells_ != b_misc_inherited_data_->empty_cells_) {
          diff.Set(CSSPropertyID::kEmptyCells);
        }
        if (a_misc_inherited_data_->image_orientation_ != b_misc_inherited_data_->image_orientation_) {
          diff.Set(CSSPropertyID::kImageOrientation);
        }
        if (a_misc_inherited_data_->interactivity_ != b_misc_inherited_data_->interactivity_) {
          diff.Set(CSSPropertyID::kInteractivity);
        }
        if (a_misc_inherited_data_->math_shift_ != b_misc_inherited_data_->math_shift_) {
          diff.Set(CSSPropertyID::kMathShift);
        }
        if (a_misc_inherited_data_->math_style_ != b_misc_inherited_data_->math_style_) {
          diff.Set(CSSPropertyID::kMathStyle);
        }
        if (a_misc_inherited_data_->ruby_overhang_ != b_misc_inherited_data_->ruby_overhang_) {
          diff.Set(CSSPropertyID::kRubyOverhang);
        }
        if (a_misc_inherited_data_->ruby_position_ != b_misc_inherited_data_->ruby_position_) {
          diff.Set(CSSPropertyID::kRubyPosition);
             diff.Set(CSSPropertyID::kWebkitRubyPosition);  // Surrogate.
        }
        if (a_misc_inherited_data_->text_autospace_ != b_misc_inherited_data_->text_autospace_) {
          diff.Set(CSSPropertyID::kTextAutospace);
        }


          if (a_misc_inherited_data_->text_emphasis_mark_ != b_misc_inherited_data_->text_emphasis_mark_) {
                // text-emphasis-style is stored on text_emphasis_mark_ in this group, so test it here.
                diff.Set(CSSPropertyID::kTextEmphasisStyle);
          }
          if (a_misc_inherited_data_->text_emphasis_fill_ != b_misc_inherited_data_->text_emphasis_fill_) {
                // text-emphasis-style is stored on text_emphasis_fill_ in this group, so test it here.
                diff.Set(CSSPropertyID::kTextEmphasisStyle);
          }

      }
      auto* a_misc_data_ = a.misc_data_.Get();
      auto* b_misc_data_ = b.misc_data_.Get();
      if (a_misc_data_ != b_misc_data_) {
              auto* a_misc_data__misc_1_data_ = a_misc_data_->misc_1_data_.Get();
        auto* b_misc_data__misc_1_data_ = b_misc_data_->misc_1_data_.Get();
        if (a_misc_data__misc_1_data_ != b_misc_data__misc_1_data_) {
            
          if (a_misc_data__misc_1_data_->anchor_scope_ != b_misc_data__misc_1_data_->anchor_scope_) {
            diff.Set(CSSPropertyID::kAnchorScope);
          }
          if (a_misc_data__misc_1_data_->position_anchor_ != b_misc_data__misc_1_data_->position_anchor_) {
            diff.Set(CSSPropertyID::kPositionAnchor);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_1_data_->anchor_name_, b_misc_data__misc_1_data_->anchor_name_)) {
            diff.Set(CSSPropertyID::kAnchorName);
          }
          if (a_misc_data__misc_1_data_->position_area_ != b_misc_data__misc_1_data_->position_area_) {
            diff.Set(CSSPropertyID::kPositionArea);
          }
          if (a_misc_data__misc_1_data_->align_self_ != b_misc_data__misc_1_data_->align_self_) {
            diff.Set(CSSPropertyID::kAlignSelf);
          }
          if (a_misc_data__misc_1_data_->align_content_ != b_misc_data__misc_1_data_->align_content_) {
            diff.Set(CSSPropertyID::kAlignContent);
          }



        }
        auto* a_misc_data__visited_data_ = a_misc_data_->visited_data_.Get();
        auto* b_misc_data__visited_data_ = b_misc_data_->visited_data_.Get();
        if (a_misc_data__visited_data_ != b_misc_data__visited_data_) {
            



        }
        auto* a_misc_data__misc_2_data_ = a_misc_data_->misc_2_data_.Get();
        auto* b_misc_data__misc_2_data_ = b_misc_data_->misc_2_data_.Get();
        if (a_misc_data__misc_2_data_ != b_misc_data__misc_2_data_) {
            
          if (a_misc_data__misc_2_data_->grid_auto_columns_ != b_misc_data__misc_2_data_->grid_auto_columns_) {
            diff.Set(CSSPropertyID::kGridAutoColumns);
          }
          if (a_misc_data__misc_2_data_->flow_tolerance_ != b_misc_data__misc_2_data_->flow_tolerance_) {
            diff.Set(CSSPropertyID::kFlowTolerance);
          }
          if (a_misc_data__misc_2_data_->column_rule_style_ != b_misc_data__misc_2_data_->column_rule_style_) {
            diff.Set(CSSPropertyID::kColumnRuleStyle);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_2_data_->content_, b_misc_data__misc_2_data_->content_)) {
            diff.Set(CSSPropertyID::kContent);
          }
          if (a_misc_data__misc_2_data_->flex_wrap_ != b_misc_data__misc_2_data_->flex_wrap_) {
            diff.Set(CSSPropertyID::kFlexWrap);
          }



        }
        auto* a_misc_data__misc_3_data_ = a_misc_data_->misc_3_data_.Get();
        auto* b_misc_data__misc_3_data_ = b_misc_data_->misc_3_data_.Get();
        if (a_misc_data__misc_3_data_ != b_misc_data__misc_3_data_) {
            
          if (a_misc_data__misc_3_data_->grid_auto_rows_ != b_misc_data__misc_3_data_->grid_auto_rows_) {
            diff.Set(CSSPropertyID::kGridAutoRows);
          }
          if (a_misc_data__misc_3_data_->grid_column_end_ != b_misc_data__misc_3_data_->grid_column_end_) {
            diff.Set(CSSPropertyID::kGridColumnEnd);
          }
          if (a_misc_data__misc_3_data_->grid_column_start_ != b_misc_data__misc_3_data_->grid_column_start_) {
            diff.Set(CSSPropertyID::kGridColumnStart);
          }
          if (a_misc_data__misc_3_data_->grid_row_end_ != b_misc_data__misc_3_data_->grid_row_end_) {
            diff.Set(CSSPropertyID::kGridRowEnd);
          }
          if (a_misc_data__misc_3_data_->grid_row_start_ != b_misc_data__misc_3_data_->grid_row_start_) {
            diff.Set(CSSPropertyID::kGridRowStart);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_3_data_->grid_template_areas_, b_misc_data__misc_3_data_->grid_template_areas_)) {
            diff.Set(CSSPropertyID::kGridTemplateAreas);
          }
          if (a_misc_data__misc_3_data_->initial_letter_ != b_misc_data__misc_3_data_->initial_letter_) {
            diff.Set(CSSPropertyID::kInitialLetter);
          }
          if (a_misc_data__misc_3_data_->max_lines_ != b_misc_data__misc_3_data_->max_lines_) {
            diff.Set(CSSPropertyID::kMaxLines);
          }
          if (a_misc_data__misc_3_data_->grid_lanes_direction_ != b_misc_data__misc_3_data_->grid_lanes_direction_) {
            diff.Set(CSSPropertyID::kGridLanesDirection);
          }
          if (a_misc_data__misc_3_data_->justify_items_ != b_misc_data__misc_3_data_->justify_items_) {
            diff.Set(CSSPropertyID::kJustifyItems);
          }
          if (a_misc_data__misc_3_data_->justify_self_ != b_misc_data__misc_3_data_->justify_self_) {
            diff.Set(CSSPropertyID::kJustifySelf);
          }



        }
        auto* a_misc_data__forced_colors_data_ = a_misc_data_->forced_colors_data_.Get();
        auto* b_misc_data__forced_colors_data_ = b_misc_data_->forced_colors_data_.Get();
        if (a_misc_data__forced_colors_data_ != b_misc_data__forced_colors_data_) {
            



        }
        auto* a_misc_data__misc_4_data_ = a_misc_data_->misc_4_data_.Get();
        auto* b_misc_data__misc_4_data_ = b_misc_data_->misc_4_data_.Get();
        if (a_misc_data__misc_4_data_ != b_misc_data__misc_4_data_) {
            
          if (a_misc_data__misc_4_data_->page_ != b_misc_data__misc_4_data_->page_) {
            diff.Set(CSSPropertyID::kPage);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_4_data_->position_try_fallbacks_, b_misc_data__misc_4_data_->position_try_fallbacks_)) {
            diff.Set(CSSPropertyID::kPositionTryFallbacks);
          }



        }
        auto* a_misc_data__misc_5_data_ = a_misc_data_->misc_5_data_.Get();
        auto* b_misc_data__misc_5_data_ = b_misc_data_->misc_5_data_.Get();
        if (a_misc_data__misc_5_data_ != b_misc_data__misc_5_data_) {
            
          if (a_misc_data__misc_5_data_->row_rule_style_ != b_misc_data__misc_5_data_->row_rule_style_) {
            diff.Set(CSSPropertyID::kRowRuleStyle);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_5_data_->scroll_marker_group_, b_misc_data__misc_5_data_->scroll_marker_group_)) {
            diff.Set(CSSPropertyID::kScrollMarkerGroup);
          }
          if (a_misc_data__misc_5_data_->scroll_padding_bottom_ != b_misc_data__misc_5_data_->scroll_padding_bottom_) {
            diff.Set(CSSPropertyID::kScrollPaddingBottom);
          }
          if (a_misc_data__misc_5_data_->scroll_padding_left_ != b_misc_data__misc_5_data_->scroll_padding_left_) {
            diff.Set(CSSPropertyID::kScrollPaddingLeft);
          }
          if (a_misc_data__misc_5_data_->scroll_margin_bottom_ != b_misc_data__misc_5_data_->scroll_margin_bottom_) {
            diff.Set(CSSPropertyID::kScrollMarginBottom);
          }
          if (a_misc_data__misc_5_data_->scroll_margin_left_ != b_misc_data__misc_5_data_->scroll_margin_left_) {
            diff.Set(CSSPropertyID::kScrollMarginLeft);
          }
          if (a_misc_data__misc_5_data_->scroll_margin_right_ != b_misc_data__misc_5_data_->scroll_margin_right_) {
            diff.Set(CSSPropertyID::kScrollMarginRight);
          }
          if (a_misc_data__misc_5_data_->scroll_margin_top_ != b_misc_data__misc_5_data_->scroll_margin_top_) {
            diff.Set(CSSPropertyID::kScrollMarginTop);
          }



        }
        auto* a_misc_data__misc_6_data_ = a_misc_data_->misc_6_data_.Get();
        auto* b_misc_data__misc_6_data_ = b_misc_data_->misc_6_data_.Get();
        if (a_misc_data__misc_6_data_ != b_misc_data__misc_6_data_) {
            
          if (a_misc_data__misc_6_data_->text_decoration_thickness_ != b_misc_data__misc_6_data_->text_decoration_thickness_) {
            diff.Set(CSSPropertyID::kTextDecorationThickness);
          }
          if (a_misc_data__misc_6_data_->text_overflow_ != b_misc_data__misc_6_data_->text_overflow_) {
            diff.Set(CSSPropertyID::kTextOverflow);
          }
          if (a_misc_data__misc_6_data_->trigger_scope_ != b_misc_data__misc_6_data_->trigger_scope_) {
            diff.Set(CSSPropertyID::kTriggerScope);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_6_data_->view_transition_class_, b_misc_data__misc_6_data_->view_transition_class_)) {
            diff.Set(CSSPropertyID::kViewTransitionClass);
          }
          if (a_misc_data__misc_6_data_->scroll_padding_right_ != b_misc_data__misc_6_data_->scroll_padding_right_) {
            diff.Set(CSSPropertyID::kScrollPaddingRight);
          }
          if (a_misc_data__misc_6_data_->scroll_padding_top_ != b_misc_data__misc_6_data_->scroll_padding_top_) {
            diff.Set(CSSPropertyID::kScrollPaddingTop);
          }
          if (a_misc_data__misc_6_data_->text_fit_ != b_misc_data__misc_6_data_->text_fit_) {
            diff.Set(CSSPropertyID::kTextFit);
          }
          if (a_misc_data__misc_6_data_->scroll_snap_type_ != b_misc_data__misc_6_data_->scroll_snap_type_) {
            diff.Set(CSSPropertyID::kScrollSnapType);
          }
          if (a_misc_data__misc_6_data_->scroll_snap_align_ != b_misc_data__misc_6_data_->scroll_snap_align_) {
            diff.Set(CSSPropertyID::kScrollSnapAlign);
          }
          if (a_misc_data__misc_6_data_->touch_action_ != b_misc_data__misc_6_data_->touch_action_) {
            diff.Set(CSSPropertyID::kTouchAction);
          }



        }
        auto* a_misc_data__timeline_data_ = a_misc_data_->timeline_data_.Get();
        auto* b_misc_data__timeline_data_ = b_misc_data_->timeline_data_.Get();
        if (a_misc_data__timeline_data_ != b_misc_data__timeline_data_) {
            



        }
        auto* a_misc_data__misc_7_data_ = a_misc_data_->misc_7_data_.Get();
        auto* b_misc_data__misc_7_data_ = b_misc_data_->misc_7_data_.Get();
        if (a_misc_data__misc_7_data_ != b_misc_data__misc_7_data_) {
            
          if (a_misc_data__misc_7_data_->view_transition_group_ != b_misc_data__misc_7_data_->view_transition_group_) {
            diff.Set(CSSPropertyID::kViewTransitionGroup);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_7_data_->view_transition_name_, b_misc_data__misc_7_data_->view_transition_name_)) {
            diff.Set(CSSPropertyID::kViewTransitionName);
          }
          if (!base::ValuesEquivalent(a_misc_data__misc_7_data_->box_reflect_, b_misc_data__misc_7_data_->box_reflect_)) {
            diff.Set(CSSPropertyID::kWebkitBoxReflect);
          }
          if (a_misc_data__misc_7_data_->box_flex_ != b_misc_data__misc_7_data_->box_flex_) {
            diff.Set(CSSPropertyID::kWebkitBoxFlex);
          }
          if (a_misc_data__misc_7_data_->box_ordinal_group_ != b_misc_data__misc_7_data_->box_ordinal_group_) {
            diff.Set(CSSPropertyID::kWebkitBoxOrdinalGroup);
          }
          if (a_misc_data__misc_7_data_->webkit_line_clamp_ != b_misc_data__misc_7_data_->webkit_line_clamp_) {
            diff.Set(CSSPropertyID::kWebkitLineClamp);
          }


            if (!base::ValuesEquivalent(a_misc_data__misc_7_data_->counter_directives_, b_misc_data__misc_7_data_->counter_directives_)) {
                  // counter-increment is stored on counter_directives_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kCounterIncrement);
                  // counter-reset is stored on counter_directives_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kCounterReset);
                  // counter-set is stored on counter_directives_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kCounterSet);
            }
            if (a_misc_data__misc_7_data_->mask_ != b_misc_data__misc_7_data_->mask_) {
                  // mask-clip is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskClip);
                  // mask-image is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskImage);
                  // mask-mode is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskMode);
                  // mask-origin is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskOrigin);
                  // mask-repeat is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskRepeat);
                  // mask-composite is stored on mask_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kMaskComposite);
            }
            if (a_misc_data__misc_7_data_->mask_box_image_ != b_misc_data__misc_7_data_->mask_box_image_) {
                  // -webkit-mask-box-image-repeat is stored on mask_box_image_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kWebkitMaskBoxImageRepeat);
            }
            if (a_misc_data__misc_7_data_->page_size_ != b_misc_data__misc_7_data_->page_size_) {
                  // size is stored on page_size_ in this group, so test it here.
                  diff.Set(CSSPropertyID::kSize);
            }

        }
        auto* a_misc_data__misc_8_data_ = a_misc_data_->misc_8_data_.Get();
        auto* b_misc_data__misc_8_data_ = b_misc_data_->misc_8_data_.Get();
        if (a_misc_data__misc_8_data_ != b_misc_data__misc_8_data_) {
            



        }
        auto* a_misc_data__math_data_ = a_misc_data_->math_data_.Get();
        auto* b_misc_data__math_data_ = b_misc_data_->math_data_.Get();
        if (a_misc_data__math_data_ != b_misc_data__math_data_) {
            



        }

        if (a_misc_data_->appearance_ != b_misc_data_->appearance_) {
          diff.Set(CSSPropertyID::kAppearance);
        }
        if (a_misc_data_->blend_mode_ != b_misc_data_->blend_mode_) {
          diff.Set(CSSPropertyID::kMixBlendMode);
        }
        if (a_misc_data_->break_after_ != b_misc_data_->break_after_) {
          diff.Set(CSSPropertyID::kBreakAfter);
        }
        if (a_misc_data_->break_before_ != b_misc_data_->break_before_) {
          diff.Set(CSSPropertyID::kBreakBefore);
        }
        if (a_misc_data_->grid_auto_flow_ != b_misc_data_->grid_auto_flow_) {
          diff.Set(CSSPropertyID::kGridAutoFlow);
        }
        if (a_misc_data_->margin_trim_ != b_misc_data_->margin_trim_) {
          diff.Set(CSSPropertyID::kMarginTrim);
        }
        if (a_misc_data_->outline_style_ != b_misc_data_->outline_style_) {
          diff.Set(CSSPropertyID::kOutlineStyle);
        }
        if (a_misc_data_->scrollbar_gutter_ != b_misc_data_->scrollbar_gutter_) {
          diff.Set(CSSPropertyID::kScrollbarGutter);
        }
        if (a_misc_data_->box_align_ != b_misc_data_->box_align_) {
          diff.Set(CSSPropertyID::kWebkitBoxAlign);
        }
        if (a_misc_data_->object_fit_ != b_misc_data_->object_fit_) {
          diff.Set(CSSPropertyID::kObjectFit);
        }
        if (a_misc_data_->position_try_order_ != b_misc_data_->position_try_order_) {
          diff.Set(CSSPropertyID::kPositionTryOrder);
        }
        if (a_misc_data_->position_visibility_ != b_misc_data_->position_visibility_) {
          diff.Set(CSSPropertyID::kPositionVisibility);
        }
        if (a_misc_data_->reading_flow_ != b_misc_data_->reading_flow_) {
          diff.Set(CSSPropertyID::kReadingFlow);
        }
        if (a_misc_data_->resize_ != b_misc_data_->resize_) {
          diff.Set(CSSPropertyID::kResize);
        }
        if (a_misc_data_->text_decoration_style_ != b_misc_data_->text_decoration_style_) {
          diff.Set(CSSPropertyID::kTextDecorationStyle);
        }
        if (a_misc_data_->box_pack_ != b_misc_data_->box_pack_) {
          diff.Set(CSSPropertyID::kWebkitBoxPack);
        }
        if (a_misc_data_->break_inside_ != b_misc_data_->break_inside_) {
          diff.Set(CSSPropertyID::kBreakInside);
        }
        if (a_misc_data_->column_rule_break_ != b_misc_data_->column_rule_break_) {
          diff.Set(CSSPropertyID::kColumnRuleBreak);
        }
        if (a_misc_data_->column_rule_visibility_items_ != b_misc_data_->column_rule_visibility_items_) {
          diff.Set(CSSPropertyID::kColumnRuleVisibilityItems);
        }
        if (a_misc_data_->column_wrap_ != b_misc_data_->column_wrap_) {
          diff.Set(CSSPropertyID::kColumnWrap);
        }
        if (a_misc_data_->continue_ != b_misc_data_->continue_) {
          diff.Set(CSSPropertyID::kContinue);
        }
        if (a_misc_data_->draggable_region_mode_ != b_misc_data_->draggable_region_mode_) {
          diff.Set(CSSPropertyID::kAppRegion);
        }
        if (a_misc_data_->flex_direction_ != b_misc_data_->flex_direction_) {
          diff.Set(CSSPropertyID::kFlexDirection);
        }
        if (a_misc_data_->overscroll_behavior_x_ != b_misc_data_->overscroll_behavior_x_) {
          diff.Set(CSSPropertyID::kOverscrollBehaviorX);
        }
        if (a_misc_data_->overscroll_behavior_y_ != b_misc_data_->overscroll_behavior_y_) {
          diff.Set(CSSPropertyID::kOverscrollBehaviorY);
        }
        if (a_misc_data_->page_margin_safety_ != b_misc_data_->page_margin_safety_) {
          diff.Set(CSSPropertyID::kPageMarginSafety);
        }
        if (a_misc_data_->page_orientation_ != b_misc_data_->page_orientation_) {
          diff.Set(CSSPropertyID::kPageOrientation);
        }
        if (a_misc_data_->row_rule_break_ != b_misc_data_->row_rule_break_) {
          diff.Set(CSSPropertyID::kRowRuleBreak);
        }
        if (a_misc_data_->row_rule_visibility_items_ != b_misc_data_->row_rule_visibility_items_) {
          diff.Set(CSSPropertyID::kRowRuleVisibilityItems);
        }
        if (a_misc_data_->scroll_behavior_ != b_misc_data_->scroll_behavior_) {
          diff.Set(CSSPropertyID::kScrollBehavior);
        }
        if (a_misc_data_->scrollbar_width_ != b_misc_data_->scrollbar_width_) {
          diff.Set(CSSPropertyID::kScrollbarWidth);
        }
        if (a_misc_data_->user_drag_ != b_misc_data_->user_drag_) {
          diff.Set(CSSPropertyID::kWebkitUserDrag);
        }
        if (a_misc_data_->backface_visibility_ != b_misc_data_->backface_visibility_) {
          diff.Set(CSSPropertyID::kBackfaceVisibility);
        }
        if (a_misc_data_->box_orient_ != b_misc_data_->box_orient_) {
          diff.Set(CSSPropertyID::kWebkitBoxOrient);
        }
        if (a_misc_data_->column_fill_ != b_misc_data_->column_fill_) {
          diff.Set(CSSPropertyID::kColumnFill);
        }
        if (a_misc_data_->column_span_ != b_misc_data_->column_span_) {
          diff.Set(CSSPropertyID::kColumnSpan);
        }
        if (a_misc_data_->grid_lanes_pack_ != b_misc_data_->grid_lanes_pack_) {
          diff.Set(CSSPropertyID::kGridLanesPack);
        }
        if (a_misc_data_->isolation_ != b_misc_data_->isolation_) {
          diff.Set(CSSPropertyID::kIsolation);
        }
        if (a_misc_data_->overlay_ != b_misc_data_->overlay_) {
          diff.Set(CSSPropertyID::kOverlay);
        }
        if (a_misc_data_->rule_overlap_ != b_misc_data_->rule_overlap_) {
          diff.Set(CSSPropertyID::kRuleOverlap);
        }
        if (a_misc_data_->scroll_initial_target_ != b_misc_data_->scroll_initial_target_) {
          diff.Set(CSSPropertyID::kScrollInitialTarget);
        }
        if (a_misc_data_->scroll_target_group_ != b_misc_data_->scroll_target_group_) {
          diff.Set(CSSPropertyID::kScrollTargetGroup);
        }
        if (a_misc_data_->transform_style_3d_ != b_misc_data_->transform_style_3d_) {
          diff.Set(CSSPropertyID::kTransformStyle);
        }
        if (a_misc_data_->view_transition_scope_ != b_misc_data_->view_transition_scope_) {
          diff.Set(CSSPropertyID::kViewTransitionScope);
        }


          if (a_misc_data_->page_size_type_ != b_misc_data_->page_size_type_) {
                // size is stored on page_size_type_ in this group, so test it here.
                diff.Set(CSSPropertyID::kSize);
          }

      }
      auto* a_inherited_data_ = a.inherited_data_.Get();
      auto* b_inherited_data_ = b.inherited_data_.Get();
      if (a_inherited_data_ != b_inherited_data_) {
              auto* a_inherited_data__inherited_forced_colors_data_ = a_inherited_data_->inherited_forced_colors_data_.Get();
        auto* b_inherited_data__inherited_forced_colors_data_ = b_inherited_data_->inherited_forced_colors_data_.Get();
        if (a_inherited_data__inherited_forced_colors_data_ != b_inherited_data__inherited_forced_colors_data_) {
            



        }
        auto* a_inherited_data__inherited_visited_data_ = a_inherited_data_->inherited_visited_data_.Get();
        auto* b_inherited_data__inherited_visited_data_ = b_inherited_data_->inherited_visited_data_.Get();
        if (a_inherited_data__inherited_visited_data_ != b_inherited_data__inherited_visited_data_) {
            



        }
        auto* a_inherited_data__highlight_data_data_ = a_inherited_data_->highlight_data_data_.Get();
        auto* b_inherited_data__highlight_data_data_ = b_inherited_data_->highlight_data_data_.Get();
        if (a_inherited_data__highlight_data_data_ != b_inherited_data__highlight_data_data_) {
            



        }

        if (a_inherited_data_->cursor_ != b_inherited_data_->cursor_) {
          diff.Set(CSSPropertyID::kCursor);
        }
        if (a_inherited_data_->text_transform_ != b_inherited_data_->text_transform_) {
          diff.Set(CSSPropertyID::kTextTransform);
        }


          if (!base::ValuesEquivalent(a_inherited_data_->font_, b_inherited_data_->font_)) {
                // font-family is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontFamily);
                // font-feature-settings is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontFeatureSettings);
                // font-kerning is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontKerning);
                // font-language-override is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontLanguageOverride);
                // font-optical-sizing is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontOpticalSizing);
                // font-synthesis-small-caps is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontSynthesisSmallCaps);
                // font-synthesis-style is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontSynthesisStyle);
                // font-synthesis-weight is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontSynthesisWeight);
                // font-variant-alternates is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantAlternates);
                // font-variant-caps is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantCaps);
                // font-variant-east-asian is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantEastAsian);
                // font-variant-emoji is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantEmoji);
                // font-variant-ligatures is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantLigatures);
                // font-variant-numeric is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantNumeric);
                // font-variant-position is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kFontVariantPosition);
                // text-rendering is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kTextRendering);
                // text-spacing-trim is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kTextSpacingTrim);
                // -webkit-font-smoothing is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kWebkitFontSmoothing);
                // -webkit-locale is stored on font_ in this group, so test it here.
                diff.Set(CSSPropertyID::kWebkitLocale);
          }

      }
      auto* a_visual_data_ = a.visual_data_.Get();
      auto* b_visual_data_ = b.visual_data_.Get();
      if (a_visual_data_ != b_visual_data_) {
          
        if (a_visual_data_->zoom_ != b_visual_data_->zoom_) {
          diff.Set(CSSPropertyID::kZoom);
        }
        if (a_visual_data_->text_decoration_line_ != b_visual_data_->text_decoration_line_) {
          diff.Set(CSSPropertyID::kTextDecorationLine);
        }
        if (a_visual_data_->field_sizing_ != b_visual_data_->field_sizing_) {
          diff.Set(CSSPropertyID::kFieldSizing);
        }



      }
      auto* a_svginherited_data_ = a.svginherited_data_.Get();
      auto* b_svginherited_data_ = b.svginherited_data_.Get();
      if (a_svginherited_data_ != b_svginherited_data_) {
              auto* a_svginherited_data__fill_data_ = a_svginherited_data_->fill_data_.Get();
        auto* b_svginherited_data__fill_data_ = b_svginherited_data_->fill_data_.Get();
        if (a_svginherited_data__fill_data_ != b_svginherited_data__fill_data_) {
            



        }
        auto* a_svginherited_data__stroke_data_ = a_svginherited_data_->stroke_data_.Get();
        auto* b_svginherited_data__stroke_data_ = b_svginherited_data_->stroke_data_.Get();
        if (a_svginherited_data__stroke_data_ != b_svginherited_data__stroke_data_) {
            
          if (a_svginherited_data__stroke_data_->cap_style_ != b_svginherited_data__stroke_data_->cap_style_) {
            diff.Set(CSSPropertyID::kStrokeLinecap);
          }
          if (a_svginherited_data__stroke_data_->join_style_ != b_svginherited_data__stroke_data_->join_style_) {
            diff.Set(CSSPropertyID::kStrokeLinejoin);
          }



        }
        auto* a_svginherited_data__resources_data_ = a_svginherited_data_->resources_data_.Get();
        auto* b_svginherited_data__resources_data_ = b_svginherited_data_->resources_data_.Get();
        if (a_svginherited_data__resources_data_ != b_svginherited_data__resources_data_) {
            
          if (!base::ValuesEquivalent(a_svginherited_data__resources_data_->marker_end_resource_, b_svginherited_data__resources_data_->marker_end_resource_)) {
            diff.Set(CSSPropertyID::kMarkerEnd);
          }
          if (!base::ValuesEquivalent(a_svginherited_data__resources_data_->marker_mid_resource_, b_svginherited_data__resources_data_->marker_mid_resource_)) {
            diff.Set(CSSPropertyID::kMarkerMid);
          }
          if (!base::ValuesEquivalent(a_svginherited_data__resources_data_->marker_start_resource_, b_svginherited_data__resources_data_->marker_start_resource_)) {
            diff.Set(CSSPropertyID::kMarkerStart);
          }



        }

        if (a_svginherited_data_->dominant_baseline_ != b_svginherited_data_->dominant_baseline_) {
          diff.Set(CSSPropertyID::kDominantBaseline);
        }
        if (a_svginherited_data_->paint_order_ != b_svginherited_data_->paint_order_) {
          diff.Set(CSSPropertyID::kPaintOrder);
        }
        if (a_svginherited_data_->color_interpolation_ != b_svginherited_data_->color_interpolation_) {
          diff.Set(CSSPropertyID::kColorInterpolation);
        }
        if (a_svginherited_data_->color_interpolation_filters_ != b_svginherited_data_->color_interpolation_filters_) {
          diff.Set(CSSPropertyID::kColorInterpolationFilters);
        }
        if (a_svginherited_data_->color_rendering_ != b_svginherited_data_->color_rendering_) {
          diff.Set(CSSPropertyID::kColorRendering);
        }
        if (a_svginherited_data_->shape_rendering_ != b_svginherited_data_->shape_rendering_) {
          diff.Set(CSSPropertyID::kShapeRendering);
        }
        if (a_svginherited_data_->text_anchor_ != b_svginherited_data_->text_anchor_) {
          diff.Set(CSSPropertyID::kTextAnchor);
        }
        if (a_svginherited_data_->clip_rule_ != b_svginherited_data_->clip_rule_) {
          diff.Set(CSSPropertyID::kClipRule);
        }
        if (a_svginherited_data_->fill_rule_ != b_svginherited_data_->fill_rule_) {
          diff.Set(CSSPropertyID::kFillRule);
        }



      }
      auto* a_box_data_ = a.box_data_.Get();
      auto* b_box_data_ = b.box_data_.Get();
      if (a_box_data_ != b_box_data_) {
          
        if (a_box_data_->overflow_clip_margin_ != b_box_data_->overflow_clip_margin_) {
          diff.Set(CSSPropertyID::kOverflowClipMargin);
        }
        if (a_box_data_->align_items_ != b_box_data_->align_items_) {
          diff.Set(CSSPropertyID::kAlignItems);
        }
        if (a_box_data_->justify_content_ != b_box_data_->justify_content_) {
          diff.Set(CSSPropertyID::kJustifyContent);
        }
        if (a_box_data_->border_bottom_style_ != b_box_data_->border_bottom_style_) {
          diff.Set(CSSPropertyID::kBorderBottomStyle);
        }
        if (a_box_data_->border_left_style_ != b_box_data_->border_left_style_) {
          diff.Set(CSSPropertyID::kBorderLeftStyle);
        }
        if (a_box_data_->border_right_style_ != b_box_data_->border_right_style_) {
          diff.Set(CSSPropertyID::kBorderRightStyle);
        }
        if (a_box_data_->border_top_style_ != b_box_data_->border_top_style_) {
          diff.Set(CSSPropertyID::kBorderTopStyle);
        }
        if (a_box_data_->baseline_source_ != b_box_data_->baseline_source_) {
          diff.Set(CSSPropertyID::kBaselineSource);
        }
        if (a_box_data_->text_box_trim_ != b_box_data_->text_box_trim_) {
          diff.Set(CSSPropertyID::kTextBoxTrim);
        }
        if (a_box_data_->box_decoration_break_ != b_box_data_->box_decoration_break_) {
          diff.Set(CSSPropertyID::kBoxDecorationBreak);
             diff.Set(CSSPropertyID::kWebkitBoxDecorationBreak);  // Surrogate.
        }



      }
      auto* a_svg_data_ = a.svg_data_.Get();
      auto* b_svg_data_ = b.svg_data_.Get();
      if (a_svg_data_ != b_svg_data_) {
              auto* a_svg_data__svgmisc_data_ = a_svg_data_->svgmisc_data_.Get();
        auto* b_svg_data__svgmisc_data_ = b_svg_data_->svgmisc_data_.Get();
        if (a_svg_data__svgmisc_data_ != b_svg_data__svgmisc_data_) {
            



        }
        auto* a_svg_data__geometry_data_ = a_svg_data_->geometry_data_.Get();
        auto* b_svg_data__geometry_data_ = b_svg_data_->geometry_data_.Get();
        if (a_svg_data__geometry_data_ != b_svg_data__geometry_data_) {
            



        }
        auto* a_svg_data__stop_data_ = a_svg_data_->stop_data_.Get();
        auto* b_svg_data__stop_data_ = b_svg_data_->stop_data_.Get();
        if (a_svg_data__stop_data_ != b_svg_data__stop_data_) {
            



        }

        if (a_svg_data_->alignment_baseline_ != b_svg_data_->alignment_baseline_) {
          diff.Set(CSSPropertyID::kAlignmentBaseline);
        }
        if (a_svg_data_->buffered_rendering_ != b_svg_data_->buffered_rendering_) {
          diff.Set(CSSPropertyID::kBufferedRendering);
        }
        if (a_svg_data_->mask_type_ != b_svg_data_->mask_type_) {
          diff.Set(CSSPropertyID::kMaskType);
        }
        if (a_svg_data_->vector_effect_ != b_svg_data_->vector_effect_) {
          diff.Set(CSSPropertyID::kVectorEffect);
        }



      }
      auto* a_surround_data_ = a.surround_data_.Get();
      auto* b_surround_data_ = b.surround_data_.Get();
      if (a_surround_data_ != b_surround_data_) {
          
        if (a_surround_data_->frame_sizing_ != b_surround_data_->frame_sizing_) {
          diff.Set(CSSPropertyID::kFrameSizing);
        }


          if (a_surround_data_->border_image_ != b_surround_data_->border_image_) {
                // border-image-repeat is stored on border_image_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBorderImageRepeat);
          }

      }
      auto* a_background_data_ = a.background_data_.Get();
      auto* b_background_data_ = b.background_data_.Get();
      if (a_background_data_ != b_background_data_) {
          


          if (a_background_data_->background_ != b_background_data_->background_) {
                // background-attachment is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundAttachment);
                // background-blend-mode is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundBlendMode);
                // background-clip is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundClip);
                // background-origin is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundOrigin);
                // background-repeat is stored on background_ in this group, so test it here.
                diff.Set(CSSPropertyID::kBackgroundRepeat);
          }

      }

      if (a.data_.clear_ != b.data_.clear_) {
        diff.Set(CSSPropertyID::kClear);
      }
      if (a.data_.floating_ != b.data_.floating_) {
        diff.Set(CSSPropertyID::kFloat);
      }
      if (a.data_.overflow_x_ != b.data_.overflow_x_) {
        diff.Set(CSSPropertyID::kOverflowX);
      }
      if (a.data_.overflow_y_ != b.data_.overflow_y_) {
        diff.Set(CSSPropertyID::kOverflowY);
      }
      if (a.data_.position_ != b.data_.position_) {
        diff.Set(CSSPropertyID::kPosition);
      }
      if (a.data_.transform_box_ != b.data_.transform_box_) {
        diff.Set(CSSPropertyID::kTransformBox);
      }
      if (a.data_.content_visibility_ != b.data_.content_visibility_) {
        diff.Set(CSSPropertyID::kContentVisibility);
      }
      if (a.data_.overflow_anchor_ != b.data_.overflow_anchor_) {
        diff.Set(CSSPropertyID::kOverflowAnchor);
      }
      if (a.data_.box_direction_ != b.data_.box_direction_) {
        diff.Set(CSSPropertyID::kWebkitBoxDirection);
      }
      if (a.data_.box_sizing_ != b.data_.box_sizing_) {
        diff.Set(CSSPropertyID::kBoxSizing);
      }
      if (a.data_.origin_trial_test_property_ != b.data_.origin_trial_test_property_) {
        diff.Set(CSSPropertyID::kOriginTrialTestProperty);
      }
      if (a.data_.scroll_snap_stop_ != b.data_.scroll_snap_stop_) {
        diff.Set(CSSPropertyID::kScrollSnapStop);
      }
      if (a.data_.table_layout_ != b.data_.table_layout_) {
        diff.Set(CSSPropertyID::kTableLayout);
      }
      if (a.data_.pointer_events_ != b.data_.pointer_events_) {
        diff.Set(CSSPropertyID::kPointerEvents);
      }
      if (a.data_.caret_shape_ != b.data_.caret_shape_) {
        diff.Set(CSSPropertyID::kCaretShape);
      }
      if (a.data_.text_align_ != b.data_.text_align_) {
        diff.Set(CSSPropertyID::kTextAlign);
      }
      if (a.data_.text_wrap_style_ != b.data_.text_wrap_style_) {
        diff.Set(CSSPropertyID::kTextWrapStyle);
      }
      if (a.data_.white_space_collapse_ != b.data_.white_space_collapse_) {
        diff.Set(CSSPropertyID::kWhiteSpaceCollapse);
      }
      if (a.data_.border_collapse_ != b.data_.border_collapse_) {
        diff.Set(CSSPropertyID::kBorderCollapse);
      }
      if (a.data_.caption_side_ != b.data_.caption_side_) {
        diff.Set(CSSPropertyID::kCaptionSide);
      }
      if (a.data_.caret_animation_ != b.data_.caret_animation_) {
        diff.Set(CSSPropertyID::kCaretAnimation);
      }
      if (a.data_.list_style_position_ != b.data_.list_style_position_) {
        diff.Set(CSSPropertyID::kListStylePosition);
      }
      if (a.data_.print_color_adjust_ != b.data_.print_color_adjust_) {
        diff.Set(CSSPropertyID::kPrintColorAdjust);
      }
      if (a.data_.rtl_ordering_ != b.data_.rtl_ordering_) {
        diff.Set(CSSPropertyID::kWebkitRtlOrdering);
      }
      if (a.data_.text_wrap_mode_ != b.data_.text_wrap_mode_) {
        diff.Set(CSSPropertyID::kTextWrapMode);
      }


        if (a.data_.display_ != b.data_.display_) {
              // display is stored on display_ in this group, so test it here.
              diff.Set(CSSPropertyID::kDisplay);
        }


        // TODO(crbug.com/40919412): Add support for -webkit-text-combine in PropertyEquality.
        // TODO(crbug.com/40919412): Add support for -webkit-text-decorations-in-effect in PropertyEquality.

  return diff;
}

// Derived fields:

// is_stacking_context_without_containment_
bool ComputedStyleBase::IsStackingContextWithoutContainment() const {
  if (!data_.is_stacking_context_without_containment_) {
    data_.is_stacking_context_without_containment_ = 0b10 | (static_cast<unsigned>(static_cast<const ComputedStyle*>(this)->CalculateIsStackingContextWithoutContainment()) & 1);
  }
  return data_.is_stacking_context_without_containment_ & 1;
}

#if DCHECK_IS_ON()

String ComputedStyleBase::DebugFieldToString(DebugField field) {
  switch (field) {
   case DebugField::accent_color_:
     return "accent_color_";
   case DebugField::affected_by_active_:
     return "affected_by_active_";
   case DebugField::affected_by_css_function_:
     return "affected_by_css_function_";
   case DebugField::affected_by_drag_:
     return "affected_by_drag_";
   case DebugField::affected_by_focus_within_:
     return "affected_by_focus_within_";
   case DebugField::affected_by_functional_media_:
     return "affected_by_functional_media_";
   case DebugField::affected_by_hover_:
     return "affected_by_hover_";
   case DebugField::align_content_:
     return "align_content_";
   case DebugField::align_content_block_center_:
     return "align_content_block_center_";
   case DebugField::align_items_:
     return "align_items_";
   case DebugField::align_self_:
     return "align_self_";
   case DebugField::alignment_baseline_:
     return "alignment_baseline_";
   case DebugField::allows_z_index_:
     return "allows_z_index_";
   case DebugField::anchor_center_offset_:
     return "anchor_center_offset_";
   case DebugField::anchor_name_:
     return "anchor_name_";
   case DebugField::anchor_scope_:
     return "anchor_scope_";
   case DebugField::animation_trigger_:
     return "animation_trigger_";
   case DebugField::animations_:
     return "animations_";
   case DebugField::appearance_:
     return "appearance_";
   case DebugField::aspect_ratio_:
     return "aspect_ratio_";
   case DebugField::backdrop_filter_:
     return "backdrop_filter_";
   case DebugField::backface_visibility_:
     return "backface_visibility_";
   case DebugField::background_:
     return "background_";
   case DebugField::background_color_:
     return "background_color_";
   case DebugField::base_data_:
     return "base_data_";
   case DebugField::base_text_decoration_data_:
     return "base_text_decoration_data_";
   case DebugField::baseline_shift_:
     return "baseline_shift_";
   case DebugField::baseline_shift_type_:
     return "baseline_shift_type_";
   case DebugField::baseline_source_:
     return "baseline_source_";
   case DebugField::blend_mode_:
     return "blend_mode_";
   case DebugField::block_ellipsis_:
     return "block_ellipsis_";
   case DebugField::border_bottom_color_:
     return "border_bottom_color_";
   case DebugField::border_bottom_left_radius_:
     return "border_bottom_left_radius_";
   case DebugField::border_bottom_right_radius_:
     return "border_bottom_right_radius_";
   case DebugField::border_bottom_style_:
     return "border_bottom_style_";
   case DebugField::border_bottom_width_:
     return "border_bottom_width_";
   case DebugField::border_collapse_:
     return "border_collapse_";
   case DebugField::border_collapse_is_inherited_:
     return "border_collapse_is_inherited_";
   case DebugField::border_image_:
     return "border_image_";
   case DebugField::border_left_color_:
     return "border_left_color_";
   case DebugField::border_left_style_:
     return "border_left_style_";
   case DebugField::border_left_width_:
     return "border_left_width_";
   case DebugField::border_right_color_:
     return "border_right_color_";
   case DebugField::border_right_style_:
     return "border_right_style_";
   case DebugField::border_right_width_:
     return "border_right_width_";
   case DebugField::border_shape_:
     return "border_shape_";
   case DebugField::border_top_color_:
     return "border_top_color_";
   case DebugField::border_top_left_radius_:
     return "border_top_left_radius_";
   case DebugField::border_top_right_radius_:
     return "border_top_right_radius_";
   case DebugField::border_top_style_:
     return "border_top_style_";
   case DebugField::border_top_width_:
     return "border_top_width_";
   case DebugField::bottom_:
     return "bottom_";
   case DebugField::box_align_:
     return "box_align_";
   case DebugField::box_decoration_break_:
     return "box_decoration_break_";
   case DebugField::box_direction_:
     return "box_direction_";
   case DebugField::box_flex_:
     return "box_flex_";
   case DebugField::box_ordinal_group_:
     return "box_ordinal_group_";
   case DebugField::box_orient_:
     return "box_orient_";
   case DebugField::box_pack_:
     return "box_pack_";
   case DebugField::box_reflect_:
     return "box_reflect_";
   case DebugField::box_shadow_:
     return "box_shadow_";
   case DebugField::box_sizing_:
     return "box_sizing_";
   case DebugField::break_after_:
     return "break_after_";
   case DebugField::break_before_:
     return "break_before_";
   case DebugField::break_inside_:
     return "break_inside_";
   case DebugField::buffered_rendering_:
     return "buffered_rendering_";
   case DebugField::callback_selectors_:
     return "callback_selectors_";
   case DebugField::can_affect_animations_:
     return "can_affect_animations_";
   case DebugField::cap_style_:
     return "cap_style_";
   case DebugField::caption_side_:
     return "caption_side_";
   case DebugField::caption_side_is_inherited_:
     return "caption_side_is_inherited_";
   case DebugField::caret_animation_:
     return "caret_animation_";
   case DebugField::caret_color_:
     return "caret_color_";
   case DebugField::caret_shape_:
     return "caret_shape_";
   case DebugField::child_has_explicit_inheritance_:
     return "child_has_explicit_inheritance_";
   case DebugField::clear_:
     return "clear_";
   case DebugField::clip_:
     return "clip_";
   case DebugField::clip_path_:
     return "clip_path_";
   case DebugField::clip_rule_:
     return "clip_rule_";
   case DebugField::color_:
     return "color_";
   case DebugField::color_interpolation_:
     return "color_interpolation_";
   case DebugField::color_interpolation_filters_:
     return "color_interpolation_filters_";
   case DebugField::color_is_current_color_:
     return "color_is_current_color_";
   case DebugField::color_is_inherited_:
     return "color_is_inherited_";
   case DebugField::color_rendering_:
     return "color_rendering_";
   case DebugField::color_scheme_:
     return "color_scheme_";
   case DebugField::color_scheme_flags_is_normal_:
     return "color_scheme_flags_is_normal_";
   case DebugField::color_scheme_forced_:
     return "color_scheme_forced_";
   case DebugField::column_count_:
     return "column_count_";
   case DebugField::column_fill_:
     return "column_fill_";
   case DebugField::column_gap_:
     return "column_gap_";
   case DebugField::column_height_:
     return "column_height_";
   case DebugField::column_rule_break_:
     return "column_rule_break_";
   case DebugField::column_rule_color_:
     return "column_rule_color_";
   case DebugField::column_rule_inset_cap_end_:
     return "column_rule_inset_cap_end_";
   case DebugField::column_rule_inset_cap_start_:
     return "column_rule_inset_cap_start_";
   case DebugField::column_rule_inset_junction_end_:
     return "column_rule_inset_junction_end_";
   case DebugField::column_rule_inset_junction_start_:
     return "column_rule_inset_junction_start_";
   case DebugField::column_rule_style_:
     return "column_rule_style_";
   case DebugField::column_rule_visibility_items_:
     return "column_rule_visibility_items_";
   case DebugField::column_rule_width_:
     return "column_rule_width_";
   case DebugField::column_span_:
     return "column_span_";
   case DebugField::column_width_:
     return "column_width_";
   case DebugField::column_wrap_:
     return "column_wrap_";
   case DebugField::contain_:
     return "contain_";
   case DebugField::contain_intrinsic_height_:
     return "contain_intrinsic_height_";
   case DebugField::contain_intrinsic_width_:
     return "contain_intrinsic_width_";
   case DebugField::container_font_:
     return "container_font_";
   case DebugField::container_name_:
     return "container_name_";
   case DebugField::container_type_:
     return "container_type_";
   case DebugField::content_:
     return "content_";
   case DebugField::content_visibility_:
     return "content_visibility_";
   case DebugField::continue_:
     return "continue_";
   case DebugField::corner_bottom_left_shape_:
     return "corner_bottom_left_shape_";
   case DebugField::corner_bottom_right_shape_:
     return "corner_bottom_right_shape_";
   case DebugField::corner_top_left_shape_:
     return "corner_top_left_shape_";
   case DebugField::corner_top_right_shape_:
     return "corner_top_right_shape_";
   case DebugField::counter_directives_:
     return "counter_directives_";
   case DebugField::css_dominant_baseline_:
     return "css_dominant_baseline_";
   case DebugField::cursor_:
     return "cursor_";
   case DebugField::cursor_data_:
     return "cursor_data_";
   case DebugField::cursor_is_inherited_:
     return "cursor_is_inherited_";
   case DebugField::custom_highlight_names_:
     return "custom_highlight_names_";
   case DebugField::custom_style_callback_depends_on_font_:
     return "custom_style_callback_depends_on_font_";
   case DebugField::cx_:
     return "cx_";
   case DebugField::cy_:
     return "cy_";
   case DebugField::d_:
     return "d_";
   case DebugField::dark_color_scheme_:
     return "dark_color_scheme_";
   case DebugField::depends_on_anchored_container_queries_:
     return "depends_on_anchored_container_queries_";
   case DebugField::depends_on_scroll_state_container_queries_:
     return "depends_on_scroll_state_container_queries_";
   case DebugField::depends_on_size_container_queries_:
     return "depends_on_size_container_queries_";
   case DebugField::depends_on_style_container_queries_:
     return "depends_on_style_container_queries_";
   case DebugField::direction_:
     return "direction_";
   case DebugField::display_:
     return "display_";
   case DebugField::display_layout_custom_name_:
     return "display_layout_custom_name_";
   case DebugField::display_layout_custom_parent_name_:
     return "display_layout_custom_parent_name_";
   case DebugField::document_rules_selectors_:
     return "document_rules_selectors_";
   case DebugField::dominant_baseline_:
     return "dominant_baseline_";
   case DebugField::draggable_region_mode_:
     return "draggable_region_mode_";
   case DebugField::dynamic_range_limit_:
     return "dynamic_range_limit_";
   case DebugField::effective_appearance_:
     return "effective_appearance_";
   case DebugField::effective_touch_action_:
     return "effective_touch_action_";
   case DebugField::effective_zoom_:
     return "effective_zoom_";
   case DebugField::element_is_view_transition_participant_:
     return "element_is_view_transition_participant_";
   case DebugField::empty_cells_:
     return "empty_cells_";
   case DebugField::empty_cells_is_inherited_:
     return "empty_cells_is_inherited_";
   case DebugField::field_sizing_:
     return "field_sizing_";
   case DebugField::fill_opacity_:
     return "fill_opacity_";
   case DebugField::fill_paint_:
     return "fill_paint_";
   case DebugField::fill_rule_:
     return "fill_rule_";
   case DebugField::filter_:
     return "filter_";
   case DebugField::first_line_depends_on_size_container_queries_:
     return "first_line_depends_on_size_container_queries_";
   case DebugField::flex_basis_:
     return "flex_basis_";
   case DebugField::flex_direction_:
     return "flex_direction_";
   case DebugField::flex_grow_:
     return "flex_grow_";
   case DebugField::flex_line_count_:
     return "flex_line_count_";
   case DebugField::flex_shrink_:
     return "flex_shrink_";
   case DebugField::flex_wrap_:
     return "flex_wrap_";
   case DebugField::floating_:
     return "floating_";
   case DebugField::flood_color_:
     return "flood_color_";
   case DebugField::flood_opacity_:
     return "flood_opacity_";
   case DebugField::flow_tolerance_:
     return "flow_tolerance_";
   case DebugField::font_:
     return "font_";
   case DebugField::forced_color_adjust_:
     return "forced_color_adjust_";
   case DebugField::forces_stacking_context_:
     return "forces_stacking_context_";
   case DebugField::frame_sizing_:
     return "frame_sizing_";
   case DebugField::grid_auto_columns_:
     return "grid_auto_columns_";
   case DebugField::grid_auto_flow_:
     return "grid_auto_flow_";
   case DebugField::grid_auto_rows_:
     return "grid_auto_rows_";
   case DebugField::grid_column_end_:
     return "grid_column_end_";
   case DebugField::grid_column_start_:
     return "grid_column_start_";
   case DebugField::grid_lanes_direction_:
     return "grid_lanes_direction_";
   case DebugField::grid_lanes_pack_:
     return "grid_lanes_pack_";
   case DebugField::grid_row_end_:
     return "grid_row_end_";
   case DebugField::grid_row_start_:
     return "grid_row_start_";
   case DebugField::grid_template_areas_:
     return "grid_template_areas_";
   case DebugField::grid_template_columns_:
     return "grid_template_columns_";
   case DebugField::grid_template_rows_:
     return "grid_template_rows_";
   case DebugField::hanging_punctuation_:
     return "hanging_punctuation_";
   case DebugField::has_anchor_evaluator_:
     return "has_anchor_evaluator_";
   case DebugField::has_anchor_functions_:
     return "has_anchor_functions_";
   case DebugField::has_attr_function_:
     return "has_attr_function_";
   case DebugField::has_author_background_:
     return "has_author_background_";
   case DebugField::has_author_border_:
     return "has_author_border_";
   case DebugField::has_author_border_radius_:
     return "has_author_border_radius_";
   case DebugField::has_author_highlight_colors_:
     return "has_author_highlight_colors_";
   case DebugField::has_auto_clip_:
     return "has_auto_clip_";
   case DebugField::has_auto_column_count_:
     return "has_auto_column_count_";
   case DebugField::has_auto_column_height_:
     return "has_auto_column_height_";
   case DebugField::has_auto_column_width_:
     return "has_auto_column_width_";
   case DebugField::has_auto_z_index_:
     return "has_auto_z_index_";
   case DebugField::has_clip_path_:
     return "has_clip_path_";
   case DebugField::has_container_relative_value_:
     return "has_container_relative_value_";
   case DebugField::has_current_backdrop_filter_animation_:
     return "has_current_backdrop_filter_animation_";
   case DebugField::has_current_background_color_animation_:
     return "has_current_background_color_animation_";
   case DebugField::has_current_clip_path_animation_:
     return "has_current_clip_path_animation_";
   case DebugField::has_current_filter_animation_:
     return "has_current_filter_animation_";
   case DebugField::has_current_opacity_animation_:
     return "has_current_opacity_animation_";
   case DebugField::has_current_rotate_animation_:
     return "has_current_rotate_animation_";
   case DebugField::has_current_scale_animation_:
     return "has_current_scale_animation_";
   case DebugField::has_current_transform_animation_:
     return "has_current_transform_animation_";
   case DebugField::has_current_translate_animation_:
     return "has_current_translate_animation_";
   case DebugField::has_element_dependent_random_functions_:
     return "has_element_dependent_random_functions_";
   case DebugField::has_em_units_:
     return "has_em_units_";
   case DebugField::has_env_:
     return "has_env_";
   case DebugField::has_env_safe_area_inset_bottom_:
     return "has_env_safe_area_inset_bottom_";
   case DebugField::has_explicit_inheritance_:
     return "has_explicit_inheritance_";
   case DebugField::has_explicit_overflow_x_visible_:
     return "has_explicit_overflow_x_visible_";
   case DebugField::has_explicit_overflow_y_visible_:
     return "has_explicit_overflow_y_visible_";
   case DebugField::has_glyph_relative_units_:
     return "has_glyph_relative_units_";
   case DebugField::has_line_height_relative_units_:
     return "has_line_height_relative_units_";
   case DebugField::has_line_if_empty_:
     return "has_line_if_empty_";
   case DebugField::has_logical_direction_relative_units_:
     return "has_logical_direction_relative_units_";
   case DebugField::has_non_ua_highlight_pseudo_styles_:
     return "has_non_ua_highlight_pseudo_styles_";
   case DebugField::has_non_universal_highlight_pseudo_styles_:
     return "has_non_universal_highlight_pseudo_styles_";
   case DebugField::has_root_font_relative_units_:
     return "has_root_font_relative_units_";
   case DebugField::has_sibling_functions_:
     return "has_sibling_functions_";
   case DebugField::has_variable_declaration_:
     return "has_variable_declaration_";
   case DebugField::has_variable_reference_:
     return "has_variable_reference_";
   case DebugField::height_:
     return "height_";
   case DebugField::highlight_data_:
     return "highlight_data_";
   case DebugField::highlights_depend_on_size_container_queries_:
     return "highlights_depend_on_size_container_queries_";
   case DebugField::horizontal_border_spacing_:
     return "horizontal_border_spacing_";
   case DebugField::hyphenate_limit_chars_:
     return "hyphenate_limit_chars_";
   case DebugField::hyphenation_string_:
     return "hyphenation_string_";
   case DebugField::hyphens_:
     return "hyphens_";
   case DebugField::image_animation_:
     return "image_animation_";
   case DebugField::image_orientation_:
     return "image_orientation_";
   case DebugField::image_rendering_:
     return "image_rendering_";
   case DebugField::in_base_appearance_:
     return "in_base_appearance_";
   case DebugField::in_forced_colors_mode_:
     return "in_forced_colors_mode_";
   case DebugField::inherited_variables_:
     return "inherited_variables_";
   case DebugField::initial_data_:
     return "initial_data_";
   case DebugField::initial_letter_:
     return "initial_letter_";
   case DebugField::inline_block_baseline_edge_:
     return "inline_block_baseline_edge_";
   case DebugField::inline_style_lost_cascade_:
     return "inline_style_lost_cascade_";
   case DebugField::inside_link_:
     return "inside_link_";
   case DebugField::interactivity_:
     return "interactivity_";
   case DebugField::interactivity_is_inherited_:
     return "interactivity_is_inherited_";
   case DebugField::interest_delay_end_:
     return "interest_delay_end_";
   case DebugField::interest_delay_start_:
     return "interest_delay_start_";
   case DebugField::internal_forced_background_color_:
     return "internal_forced_background_color_";
   case DebugField::internal_forced_border_color_:
     return "internal_forced_border_color_";
   case DebugField::internal_forced_color_:
     return "internal_forced_color_";
   case DebugField::internal_forced_outline_color_:
     return "internal_forced_outline_color_";
   case DebugField::internal_forced_visited_color_:
     return "internal_forced_visited_color_";
   case DebugField::internal_overscroll_area_:
     return "internal_overscroll_area_";
   case DebugField::internal_overscroll_position_:
     return "internal_overscroll_position_";
   case DebugField::internal_visited_background_color_:
     return "internal_visited_background_color_";
   case DebugField::internal_visited_border_bottom_color_:
     return "internal_visited_border_bottom_color_";
   case DebugField::internal_visited_border_left_color_:
     return "internal_visited_border_left_color_";
   case DebugField::internal_visited_border_right_color_:
     return "internal_visited_border_right_color_";
   case DebugField::internal_visited_border_top_color_:
     return "internal_visited_border_top_color_";
   case DebugField::internal_visited_caret_color_:
     return "internal_visited_caret_color_";
   case DebugField::internal_visited_color_:
     return "internal_visited_color_";
   case DebugField::internal_visited_color_is_current_color_:
     return "internal_visited_color_is_current_color_";
   case DebugField::internal_visited_column_rule_color_:
     return "internal_visited_column_rule_color_";
   case DebugField::internal_visited_fill_paint_:
     return "internal_visited_fill_paint_";
   case DebugField::internal_visited_outline_color_:
     return "internal_visited_outline_color_";
   case DebugField::internal_visited_stroke_paint_:
     return "internal_visited_stroke_paint_";
   case DebugField::internal_visited_text_decoration_color_:
     return "internal_visited_text_decoration_color_";
   case DebugField::internal_visited_text_emphasis_color_:
     return "internal_visited_text_emphasis_color_";
   case DebugField::internal_visited_text_fill_color_:
     return "internal_visited_text_fill_color_";
   case DebugField::internal_visited_text_stroke_color_:
     return "internal_visited_text_stroke_color_";
   case DebugField::interpolate_size_:
     return "interpolate_size_";
   case DebugField::is_bottom_relative_to_safe_area_inset_:
     return "is_bottom_relative_to_safe_area_inset_";
   case DebugField::is_css_inert_:
     return "is_css_inert_";
   case DebugField::is_css_inert_is_inherited_:
     return "is_css_inert_is_inherited_";
   case DebugField::is_ensured_in_display_none_:
     return "is_ensured_in_display_none_";
   case DebugField::is_ensured_outside_flat_tree_:
     return "is_ensured_outside_flat_tree_";
   case DebugField::is_flex_or_grid_or_custom_item_:
     return "is_flex_or_grid_or_custom_item_";
   case DebugField::is_html_inert_:
     return "is_html_inert_";
   case DebugField::is_html_inert_is_inherited_:
     return "is_html_inert_is_inherited_";
   case DebugField::is_in_blockifying_display_:
     return "is_in_blockifying_display_";
   case DebugField::is_in_inlinifying_display_:
     return "is_in_inlinifying_display_";
   case DebugField::is_inside_display_ignoring_floating_children_:
     return "is_inside_display_ignoring_floating_children_";
   case DebugField::is_link_:
     return "is_link_";
   case DebugField::is_original_display_inline_type_:
     return "is_original_display_inline_type_";
   case DebugField::is_page_margin_box_:
     return "is_page_margin_box_";
   case DebugField::is_running_backdrop_filter_animation_on_compositor_:
     return "is_running_backdrop_filter_animation_on_compositor_";
   case DebugField::is_running_filter_animation_on_compositor_:
     return "is_running_filter_animation_on_compositor_";
   case DebugField::is_running_opacity_animation_on_compositor_:
     return "is_running_opacity_animation_on_compositor_";
   case DebugField::is_running_rotate_animation_on_compositor_:
     return "is_running_rotate_animation_on_compositor_";
   case DebugField::is_running_scale_animation_on_compositor_:
     return "is_running_scale_animation_on_compositor_";
   case DebugField::is_running_transform_animation_on_compositor_:
     return "is_running_transform_animation_on_compositor_";
   case DebugField::is_running_translate_animation_on_compositor_:
     return "is_running_translate_animation_on_compositor_";
   case DebugField::is_secondary_body_element_:
     return "is_secondary_body_element_";
   case DebugField::is_specified_display_webkit_box_:
     return "is_specified_display_webkit_box_";
   case DebugField::is_stacking_context_without_containment_:
     return "is_stacking_context_without_containment_";
   case DebugField::is_starting_style_:
     return "is_starting_style_";
   case DebugField::isolation_:
     return "isolation_";
   case DebugField::join_style_:
     return "join_style_";
   case DebugField::justify_content_:
     return "justify_content_";
   case DebugField::justify_items_:
     return "justify_items_";
   case DebugField::justify_self_:
     return "justify_self_";
   case DebugField::left_:
     return "left_";
   case DebugField::letter_spacing_:
     return "letter_spacing_";
   case DebugField::lighting_color_:
     return "lighting_color_";
   case DebugField::line_break_:
     return "line_break_";
   case DebugField::line_height_:
     return "line_height_";
   case DebugField::list_style_image_:
     return "list_style_image_";
   case DebugField::list_style_position_:
     return "list_style_position_";
   case DebugField::list_style_position_is_inherited_:
     return "list_style_position_is_inherited_";
   case DebugField::list_style_type_:
     return "list_style_type_";
   case DebugField::margin_bottom_:
     return "margin_bottom_";
   case DebugField::margin_left_:
     return "margin_left_";
   case DebugField::margin_right_:
     return "margin_right_";
   case DebugField::margin_top_:
     return "margin_top_";
   case DebugField::margin_trim_:
     return "margin_trim_";
   case DebugField::marker_end_resource_:
     return "marker_end_resource_";
   case DebugField::marker_mid_resource_:
     return "marker_mid_resource_";
   case DebugField::marker_start_resource_:
     return "marker_start_resource_";
   case DebugField::mask_:
     return "mask_";
   case DebugField::mask_box_image_:
     return "mask_box_image_";
   case DebugField::mask_type_:
     return "mask_type_";
   case DebugField::math_baseline_:
     return "math_baseline_";
   case DebugField::math_depth_:
     return "math_depth_";
   case DebugField::math_fraction_bar_thickness_:
     return "math_fraction_bar_thickness_";
   case DebugField::math_l_space_:
     return "math_l_space_";
   case DebugField::math_max_size_:
     return "math_max_size_";
   case DebugField::math_min_size_:
     return "math_min_size_";
   case DebugField::math_padded_depth_:
     return "math_padded_depth_";
   case DebugField::math_padded_v_offset_:
     return "math_padded_v_offset_";
   case DebugField::math_r_space_:
     return "math_r_space_";
   case DebugField::math_shift_:
     return "math_shift_";
   case DebugField::math_style_:
     return "math_style_";
   case DebugField::max_height_:
     return "max_height_";
   case DebugField::max_lines_:
     return "max_lines_";
   case DebugField::max_width_:
     return "max_width_";
   case DebugField::may_have_margin_:
     return "may_have_margin_";
   case DebugField::may_have_padding_:
     return "may_have_padding_";
   case DebugField::maybe_has_gap_decorations_:
     return "maybe_has_gap_decorations_";
   case DebugField::min_height_:
     return "min_height_";
   case DebugField::min_width_:
     return "min_width_";
   case DebugField::non_inherited_variables_:
     return "non_inherited_variables_";
   case DebugField::object_fit_:
     return "object_fit_";
   case DebugField::object_position_:
     return "object_position_";
   case DebugField::object_view_box_:
     return "object_view_box_";
   case DebugField::offset_anchor_:
     return "offset_anchor_";
   case DebugField::offset_distance_:
     return "offset_distance_";
   case DebugField::offset_path_:
     return "offset_path_";
   case DebugField::offset_position_:
     return "offset_position_";
   case DebugField::offset_rotate_:
     return "offset_rotate_";
   case DebugField::opacity_:
     return "opacity_";
   case DebugField::order_:
     return "order_";
   case DebugField::origin_trial_test_property_:
     return "origin_trial_test_property_";
   case DebugField::orphans_:
     return "orphans_";
   case DebugField::outline_color_:
     return "outline_color_";
   case DebugField::outline_offset_:
     return "outline_offset_";
   case DebugField::outline_style_:
     return "outline_style_";
   case DebugField::outline_style_is_auto_:
     return "outline_style_is_auto_";
   case DebugField::outline_width_:
     return "outline_width_";
   case DebugField::overflow_anchor_:
     return "overflow_anchor_";
   case DebugField::overflow_clip_margin_:
     return "overflow_clip_margin_";
   case DebugField::overflow_wrap_:
     return "overflow_wrap_";
   case DebugField::overflow_x_:
     return "overflow_x_";
   case DebugField::overflow_y_:
     return "overflow_y_";
   case DebugField::overlay_:
     return "overlay_";
   case DebugField::overscroll_behavior_x_:
     return "overscroll_behavior_x_";
   case DebugField::overscroll_behavior_y_:
     return "overscroll_behavior_y_";
   case DebugField::padding_bottom_:
     return "padding_bottom_";
   case DebugField::padding_left_:
     return "padding_left_";
   case DebugField::padding_right_:
     return "padding_right_";
   case DebugField::padding_top_:
     return "padding_top_";
   case DebugField::page_:
     return "page_";
   case DebugField::page_margin_safety_:
     return "page_margin_safety_";
   case DebugField::page_orientation_:
     return "page_orientation_";
   case DebugField::page_size_:
     return "page_size_";
   case DebugField::page_size_type_:
     return "page_size_type_";
   case DebugField::paint_images_:
     return "paint_images_";
   case DebugField::paint_order_:
     return "paint_order_";
   case DebugField::path_length_:
     return "path_length_";
   case DebugField::perspective_:
     return "perspective_";
   case DebugField::perspective_origin_:
     return "perspective_origin_";
   case DebugField::pointer_events_:
     return "pointer_events_";
   case DebugField::pointer_events_is_inherited_:
     return "pointer_events_is_inherited_";
   case DebugField::position_:
     return "position_";
   case DebugField::position_anchor_:
     return "position_anchor_";
   case DebugField::position_area_:
     return "position_area_";
   case DebugField::position_area_offsets_:
     return "position_area_offsets_";
   case DebugField::position_try_fallbacks_:
     return "position_try_fallbacks_";
   case DebugField::position_try_order_:
     return "position_try_order_";
   case DebugField::position_visibility_:
     return "position_visibility_";
   case DebugField::prefers_default_scrollbar_styles_:
     return "prefers_default_scrollbar_styles_";
   case DebugField::print_color_adjust_:
     return "print_color_adjust_";
   case DebugField::pseudo_element_styles_:
     return "pseudo_element_styles_";
   case DebugField::quotes_:
     return "quotes_";
   case DebugField::r_:
     return "r_";
   case DebugField::reading_flow_:
     return "reading_flow_";
   case DebugField::reading_order_:
     return "reading_order_";
   case DebugField::requires_accelerated_compositing_for_external_reasons_:
     return "requires_accelerated_compositing_for_external_reasons_";
   case DebugField::resize_:
     return "resize_";
   case DebugField::right_:
     return "right_";
   case DebugField::rotate_:
     return "rotate_";
   case DebugField::row_gap_:
     return "row_gap_";
   case DebugField::row_rule_break_:
     return "row_rule_break_";
   case DebugField::row_rule_color_:
     return "row_rule_color_";
   case DebugField::row_rule_inset_cap_end_:
     return "row_rule_inset_cap_end_";
   case DebugField::row_rule_inset_cap_start_:
     return "row_rule_inset_cap_start_";
   case DebugField::row_rule_inset_junction_end_:
     return "row_rule_inset_junction_end_";
   case DebugField::row_rule_inset_junction_start_:
     return "row_rule_inset_junction_start_";
   case DebugField::row_rule_style_:
     return "row_rule_style_";
   case DebugField::row_rule_visibility_items_:
     return "row_rule_visibility_items_";
   case DebugField::row_rule_width_:
     return "row_rule_width_";
   case DebugField::rtl_ordering_:
     return "rtl_ordering_";
   case DebugField::rtl_ordering_is_inherited_:
     return "rtl_ordering_is_inherited_";
   case DebugField::ruby_align_:
     return "ruby_align_";
   case DebugField::ruby_overhang_:
     return "ruby_overhang_";
   case DebugField::ruby_position_:
     return "ruby_position_";
   case DebugField::rule_overlap_:
     return "rule_overlap_";
   case DebugField::rx_:
     return "rx_";
   case DebugField::ry_:
     return "ry_";
   case DebugField::scale_:
     return "scale_";
   case DebugField::scroll_behavior_:
     return "scroll_behavior_";
   case DebugField::scroll_initial_target_:
     return "scroll_initial_target_";
   case DebugField::scroll_margin_bottom_:
     return "scroll_margin_bottom_";
   case DebugField::scroll_margin_left_:
     return "scroll_margin_left_";
   case DebugField::scroll_margin_right_:
     return "scroll_margin_right_";
   case DebugField::scroll_margin_top_:
     return "scroll_margin_top_";
   case DebugField::scroll_marker_group_:
     return "scroll_marker_group_";
   case DebugField::scroll_padding_bottom_:
     return "scroll_padding_bottom_";
   case DebugField::scroll_padding_left_:
     return "scroll_padding_left_";
   case DebugField::scroll_padding_right_:
     return "scroll_padding_right_";
   case DebugField::scroll_padding_top_:
     return "scroll_padding_top_";
   case DebugField::scroll_snap_align_:
     return "scroll_snap_align_";
   case DebugField::scroll_snap_stop_:
     return "scroll_snap_stop_";
   case DebugField::scroll_snap_type_:
     return "scroll_snap_type_";
   case DebugField::scroll_target_group_:
     return "scroll_target_group_";
   case DebugField::scroll_timeline_axis_:
     return "scroll_timeline_axis_";
   case DebugField::scroll_timeline_name_:
     return "scroll_timeline_name_";
   case DebugField::scrollbar_color_:
     return "scrollbar_color_";
   case DebugField::scrollbar_gutter_:
     return "scrollbar_gutter_";
   case DebugField::scrollbar_width_:
     return "scrollbar_width_";
   case DebugField::shape_image_threshold_:
     return "shape_image_threshold_";
   case DebugField::shape_margin_:
     return "shape_margin_";
   case DebugField::shape_outside_:
     return "shape_outside_";
   case DebugField::shape_rendering_:
     return "shape_rendering_";
   case DebugField::should_ignore_overflow_property_for_inline_block_baseline_:
     return "should_ignore_overflow_property_for_inline_block_baseline_";
   case DebugField::skips_contents_:
     return "skips_contents_";
   case DebugField::speak_:
     return "speak_";
   case DebugField::stop_color_:
     return "stop_color_";
   case DebugField::stop_opacity_:
     return "stop_opacity_";
   case DebugField::stroke_dash_array_:
     return "stroke_dash_array_";
   case DebugField::stroke_dash_offset_:
     return "stroke_dash_offset_";
   case DebugField::stroke_miter_limit_:
     return "stroke_miter_limit_";
   case DebugField::stroke_opacity_:
     return "stroke_opacity_";
   case DebugField::stroke_paint_:
     return "stroke_paint_";
   case DebugField::stroke_width_:
     return "stroke_width_";
   case DebugField::style_type_:
     return "style_type_";
   case DebugField::subtree_is_sticky_:
     return "subtree_is_sticky_";
   case DebugField::subtree_will_change_contents_:
     return "subtree_will_change_contents_";
   case DebugField::tab_size_:
     return "tab_size_";
   case DebugField::table_layout_:
     return "table_layout_";
   case DebugField::tap_highlight_color_:
     return "tap_highlight_color_";
   case DebugField::text_align_:
     return "text_align_";
   case DebugField::text_align_last_:
     return "text_align_last_";
   case DebugField::text_anchor_:
     return "text_anchor_";
   case DebugField::text_autospace_:
     return "text_autospace_";
   case DebugField::text_box_edge_:
     return "text_box_edge_";
   case DebugField::text_box_trim_:
     return "text_box_trim_";
   case DebugField::text_combine_:
     return "text_combine_";
   case DebugField::text_decoration_color_:
     return "text_decoration_color_";
   case DebugField::text_decoration_line_:
     return "text_decoration_line_";
   case DebugField::text_decoration_skip_ink_:
     return "text_decoration_skip_ink_";
   case DebugField::text_decoration_skip_spaces_:
     return "text_decoration_skip_spaces_";
   case DebugField::text_decoration_style_:
     return "text_decoration_style_";
   case DebugField::text_decoration_thickness_:
     return "text_decoration_thickness_";
   case DebugField::text_emphasis_color_:
     return "text_emphasis_color_";
   case DebugField::text_emphasis_custom_mark_:
     return "text_emphasis_custom_mark_";
   case DebugField::text_emphasis_fill_:
     return "text_emphasis_fill_";
   case DebugField::text_emphasis_mark_:
     return "text_emphasis_mark_";
   case DebugField::text_emphasis_position_:
     return "text_emphasis_position_";
   case DebugField::text_fill_color_:
     return "text_fill_color_";
   case DebugField::text_fit_:
     return "text_fit_";
   case DebugField::text_indent_:
     return "text_indent_";
   case DebugField::text_indent_flags_:
     return "text_indent_flags_";
   case DebugField::text_justify_:
     return "text_justify_";
   case DebugField::text_orientation_:
     return "text_orientation_";
   case DebugField::text_overflow_:
     return "text_overflow_";
   case DebugField::text_security_:
     return "text_security_";
   case DebugField::text_shadow_:
     return "text_shadow_";
   case DebugField::text_size_adjust_:
     return "text_size_adjust_";
   case DebugField::text_stroke_color_:
     return "text_stroke_color_";
   case DebugField::text_stroke_width_:
     return "text_stroke_width_";
   case DebugField::text_transform_:
     return "text_transform_";
   case DebugField::text_transform_is_inherited_:
     return "text_transform_is_inherited_";
   case DebugField::text_underline_offset_:
     return "text_underline_offset_";
   case DebugField::text_underline_position_:
     return "text_underline_position_";
   case DebugField::text_wrap_mode_:
     return "text_wrap_mode_";
   case DebugField::text_wrap_style_:
     return "text_wrap_style_";
   case DebugField::timeline_scope_:
     return "timeline_scope_";
   case DebugField::timeline_trigger_name_:
     return "timeline_trigger_name_";
   case DebugField::top_:
     return "top_";
   case DebugField::touch_action_:
     return "touch_action_";
   case DebugField::transform_:
     return "transform_";
   case DebugField::transform_box_:
     return "transform_box_";
   case DebugField::transform_origin_:
     return "transform_origin_";
   case DebugField::transform_style_3d_:
     return "transform_style_3d_";
   case DebugField::transitions_:
     return "transitions_";
   case DebugField::translate_:
     return "translate_";
   case DebugField::trigger_scope_:
     return "trigger_scope_";
   case DebugField::ua_shadow_host_data_:
     return "ua_shadow_host_data_";
   case DebugField::unconditional_scrollbar_size_:
     return "unconditional_scrollbar_size_";
   case DebugField::unicode_bidi_:
     return "unicode_bidi_";
   case DebugField::user_drag_:
     return "user_drag_";
   case DebugField::user_modify_:
     return "user_modify_";
   case DebugField::user_select_:
     return "user_select_";
   case DebugField::vector_effect_:
     return "vector_effect_";
   case DebugField::vertical_align_:
     return "vertical_align_";
   case DebugField::vertical_align_length_:
     return "vertical_align_length_";
   case DebugField::vertical_border_spacing_:
     return "vertical_border_spacing_";
   case DebugField::view_timeline_axis_:
     return "view_timeline_axis_";
   case DebugField::view_timeline_inset_:
     return "view_timeline_inset_";
   case DebugField::view_timeline_name_:
     return "view_timeline_name_";
   case DebugField::view_transition_class_:
     return "view_transition_class_";
   case DebugField::view_transition_group_:
     return "view_transition_group_";
   case DebugField::view_transition_name_:
     return "view_transition_name_";
   case DebugField::view_transition_scope_:
     return "view_transition_scope_";
   case DebugField::viewport_unit_flags_:
     return "viewport_unit_flags_";
   case DebugField::visibility_:
     return "visibility_";
   case DebugField::visibility_is_inherited_:
     return "visibility_is_inherited_";
   case DebugField::webkit_line_clamp_:
     return "webkit_line_clamp_";
   case DebugField::white_space_collapse_:
     return "white_space_collapse_";
   case DebugField::widows_:
     return "widows_";
   case DebugField::width_:
     return "width_";
   case DebugField::will_change_:
     return "will_change_";
   case DebugField::word_break_:
     return "word_break_";
   case DebugField::word_spacing_:
     return "word_spacing_";
   case DebugField::writing_mode_:
     return "writing_mode_";
   case DebugField::x_:
     return "x_";
   case DebugField::y_:
     return "y_";
   case DebugField::z_index_:
     return "z_index_";
   case DebugField::zoom_:
     return "zoom_";
  }
}

template<typename, typename = void>
constexpr bool HasLogging {};

template<typename T>
constexpr bool HasLogging<
  T,
  std::void_t<decltype(std::stringstream() << std::declval<T>())>
> = true;

template<typename> constexpr bool IsPersistent = false;
template<typename T> constexpr bool IsPersistent<Persistent<T>> = true;

template <typename> constexpr bool IsScopedRefPtr = false;
template <typename T> constexpr bool IsScopedRefPtr<scoped_refptr<T>> = true;

template<class T>
static std::string DebugStringForField(const T& t) {
  if constexpr (std::is_same_v<T, bool>) {
    return t ? "true" : "false";
  }
  if constexpr (IsPersistent<T>) {
    if constexpr (HasLogging<typename T::PointeeType>) {
      std::stringstream ss;
      ss << *t;
      return ss.str();
    }
  }
  if constexpr (IsScopedRefPtr<T>) {
    if constexpr (HasLogging<typename T::element_type>) {
      std::stringstream ss;
      ss << *t;
      return ss.str();
    }
  }
  if constexpr (HasLogging<T>) {
    std::stringstream ss;
    ss << t;
    return ss.str();
  }
  return "<unable to print>";
}

Vector<ComputedStyleBase::DebugDiff>
ComputedStyleBase::DebugDiffFields(const ComputedStyleBase& o) const {
  Vector<DebugDiff> diff;
      // Group: misc-inherited1
  const auto& dynamic_range_limit__expr = misc_inherited_data_->misc_inherited_1_data_->dynamic_range_limit_;
  const auto& o_dynamic_range_limit__expr = o.misc_inherited_data_->misc_inherited_1_data_->dynamic_range_limit_;
  if (!(dynamic_range_limit__expr == o_dynamic_range_limit__expr)) {
    DebugDiff d;
    d.field = DebugField::dynamic_range_limit_;
    d.actual = DebugStringForField(dynamic_range_limit__expr);
    d.correct = DebugStringForField(o_dynamic_range_limit__expr);
    diff.push_back(std::move(d));
  }
  const auto& color_scheme__expr = misc_inherited_data_->misc_inherited_1_data_->color_scheme_;
  const auto& o_color_scheme__expr = o.misc_inherited_data_->misc_inherited_1_data_->color_scheme_;
  if (!(color_scheme__expr == o_color_scheme__expr)) {
    DebugDiff d;
    d.field = DebugField::color_scheme_;
    d.actual = DebugStringForField(color_scheme__expr);
    d.correct = DebugStringForField(o_color_scheme__expr);
    diff.push_back(std::move(d));
  }
  const auto& hyphenation_string__expr = misc_inherited_data_->misc_inherited_1_data_->hyphenation_string_;
  const auto& o_hyphenation_string__expr = o.misc_inherited_data_->misc_inherited_1_data_->hyphenation_string_;
  if (!(hyphenation_string__expr == o_hyphenation_string__expr)) {
    DebugDiff d;
    d.field = DebugField::hyphenation_string_;
    d.actual = DebugStringForField(hyphenation_string__expr);
    d.correct = DebugStringForField(o_hyphenation_string__expr);
    diff.push_back(std::move(d));
  }
  const auto& quotes__expr = misc_inherited_data_->misc_inherited_1_data_->quotes_;
  const auto& o_quotes__expr = o.misc_inherited_data_->misc_inherited_1_data_->quotes_;
  if (!(base::ValuesEquivalent(quotes__expr, o_quotes__expr))) {
    DebugDiff d;
    d.field = DebugField::quotes_;
    d.actual = DebugStringForField(quotes__expr);
    d.correct = DebugStringForField(o_quotes__expr);
    diff.push_back(std::move(d));
  }
  const auto& list_style_image__expr = misc_inherited_data_->misc_inherited_1_data_->list_style_image_;
  const auto& o_list_style_image__expr = o.misc_inherited_data_->misc_inherited_1_data_->list_style_image_;
  if (!(base::ValuesEquivalent(list_style_image__expr, o_list_style_image__expr))) {
    DebugDiff d;
    d.field = DebugField::list_style_image_;
    d.actual = DebugStringForField(list_style_image__expr);
    d.correct = DebugStringForField(o_list_style_image__expr);
    diff.push_back(std::move(d));
  }
  const auto& list_style_type__expr = misc_inherited_data_->misc_inherited_1_data_->list_style_type_;
  const auto& o_list_style_type__expr = o.misc_inherited_data_->misc_inherited_1_data_->list_style_type_;
  if (!(base::ValuesEquivalent(list_style_type__expr, o_list_style_type__expr))) {
    DebugDiff d;
    d.field = DebugField::list_style_type_;
    d.actual = DebugStringForField(list_style_type__expr);
    d.correct = DebugStringForField(o_list_style_type__expr);
    diff.push_back(std::move(d));
  }
  const auto& scrollbar_color__expr = misc_inherited_data_->misc_inherited_1_data_->scrollbar_color_;
  const auto& o_scrollbar_color__expr = o.misc_inherited_data_->misc_inherited_1_data_->scrollbar_color_;
  if (!(base::ValuesEquivalent(scrollbar_color__expr, o_scrollbar_color__expr))) {
    DebugDiff d;
    d.field = DebugField::scrollbar_color_;
    d.actual = DebugStringForField(scrollbar_color__expr);
    d.correct = DebugStringForField(o_scrollbar_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_indent__expr = misc_inherited_data_->misc_inherited_1_data_->text_indent_;
  const auto& o_text_indent__expr = o.misc_inherited_data_->misc_inherited_1_data_->text_indent_;
  if (!(text_indent__expr == o_text_indent__expr)) {
    DebugDiff d;
    d.field = DebugField::text_indent_;
    d.actual = DebugStringForField(text_indent__expr);
    d.correct = DebugStringForField(o_text_indent__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_size_adjust__expr = misc_inherited_data_->misc_inherited_1_data_->text_size_adjust_;
  const auto& o_text_size_adjust__expr = o.misc_inherited_data_->misc_inherited_1_data_->text_size_adjust_;
  if (!(text_size_adjust__expr == o_text_size_adjust__expr)) {
    DebugDiff d;
    d.field = DebugField::text_size_adjust_;
    d.actual = DebugStringForField(text_size_adjust__expr);
    d.correct = DebugStringForField(o_text_size_adjust__expr);
    diff.push_back(std::move(d));
  }
  const auto& tab_size__expr = misc_inherited_data_->misc_inherited_1_data_->tab_size_;
  const auto& o_tab_size__expr = o.misc_inherited_data_->misc_inherited_1_data_->tab_size_;
  if (!(tab_size__expr == o_tab_size__expr)) {
    DebugDiff d;
    d.field = DebugField::tab_size_;
    d.actual = DebugStringForField(tab_size__expr);
    d.correct = DebugStringForField(o_tab_size__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_emphasis_color__expr = misc_inherited_data_->misc_inherited_1_data_->text_emphasis_color_;
  const auto& o_text_emphasis_color__expr = o.misc_inherited_data_->misc_inherited_1_data_->text_emphasis_color_;
  if (!(text_emphasis_color__expr == o_text_emphasis_color__expr)) {
    DebugDiff d;
    d.field = DebugField::text_emphasis_color_;
    d.actual = DebugStringForField(text_emphasis_color__expr);
    d.correct = DebugStringForField(o_text_emphasis_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& accent_color__expr = misc_inherited_data_->misc_inherited_1_data_->accent_color_;
  const auto& o_accent_color__expr = o.misc_inherited_data_->misc_inherited_1_data_->accent_color_;
  if (!(accent_color__expr == o_accent_color__expr)) {
    DebugDiff d;
    d.field = DebugField::accent_color_;
    d.actual = DebugStringForField(accent_color__expr);
    d.correct = DebugStringForField(o_accent_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& caret_color__expr = misc_inherited_data_->misc_inherited_1_data_->caret_color_;
  const auto& o_caret_color__expr = o.misc_inherited_data_->misc_inherited_1_data_->caret_color_;
  if (!(caret_color__expr == o_caret_color__expr)) {
    DebugDiff d;
    d.field = DebugField::caret_color_;
    d.actual = DebugStringForField(caret_color__expr);
    d.correct = DebugStringForField(o_caret_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& hyphenate_limit_chars__expr = misc_inherited_data_->misc_inherited_1_data_->hyphenate_limit_chars_;
  const auto& o_hyphenate_limit_chars__expr = o.misc_inherited_data_->misc_inherited_1_data_->hyphenate_limit_chars_;
  if (!(hyphenate_limit_chars__expr == o_hyphenate_limit_chars__expr)) {
    DebugDiff d;
    d.field = DebugField::hyphenate_limit_chars_;
    d.actual = DebugStringForField(hyphenate_limit_chars__expr);
    d.correct = DebugStringForField(o_hyphenate_limit_chars__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_depth__expr = misc_inherited_data_->misc_inherited_1_data_->math_depth_;
  const auto& o_math_depth__expr = o.misc_inherited_data_->misc_inherited_1_data_->math_depth_;
  if (!(math_depth__expr == o_math_depth__expr)) {
    DebugDiff d;
    d.field = DebugField::math_depth_;
    d.actual = DebugStringForField(math_depth__expr);
    d.correct = DebugStringForField(o_math_depth__expr);
    diff.push_back(std::move(d));
  }
  const auto& orphans__expr = misc_inherited_data_->misc_inherited_1_data_->orphans_;
  const auto& o_orphans__expr = o.misc_inherited_data_->misc_inherited_1_data_->orphans_;
  if (!(orphans__expr == o_orphans__expr)) {
    DebugDiff d;
    d.field = DebugField::orphans_;
    d.actual = DebugStringForField(orphans__expr);
    d.correct = DebugStringForField(o_orphans__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc-inherited2
  const auto& text_emphasis_custom_mark__expr = misc_inherited_data_->misc_inherited_2_data_->text_emphasis_custom_mark_;
  const auto& o_text_emphasis_custom_mark__expr = o.misc_inherited_data_->misc_inherited_2_data_->text_emphasis_custom_mark_;
  if (!(text_emphasis_custom_mark__expr == o_text_emphasis_custom_mark__expr)) {
    DebugDiff d;
    d.field = DebugField::text_emphasis_custom_mark_;
    d.actual = DebugStringForField(text_emphasis_custom_mark__expr);
    d.correct = DebugStringForField(o_text_emphasis_custom_mark__expr);
    diff.push_back(std::move(d));
  }
  const auto& ua_shadow_host_data__expr = misc_inherited_data_->misc_inherited_2_data_->ua_shadow_host_data_;
  const auto& o_ua_shadow_host_data__expr = o.misc_inherited_data_->misc_inherited_2_data_->ua_shadow_host_data_;
  if (!(base::ValuesEquivalent(ua_shadow_host_data__expr, o_ua_shadow_host_data__expr))) {
    DebugDiff d;
    d.field = DebugField::ua_shadow_host_data_;
    d.actual = DebugStringForField(ua_shadow_host_data__expr);
    d.correct = DebugStringForField(o_ua_shadow_host_data__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_shadow__expr = misc_inherited_data_->misc_inherited_2_data_->text_shadow_;
  const auto& o_text_shadow__expr = o.misc_inherited_data_->misc_inherited_2_data_->text_shadow_;
  if (!(base::ValuesEquivalent(text_shadow__expr, o_text_shadow__expr))) {
    DebugDiff d;
    d.field = DebugField::text_shadow_;
    d.actual = DebugStringForField(text_shadow__expr);
    d.correct = DebugStringForField(o_text_shadow__expr);
    diff.push_back(std::move(d));
  }
  const auto& cursor_data__expr = misc_inherited_data_->misc_inherited_2_data_->cursor_data_;
  const auto& o_cursor_data__expr = o.misc_inherited_data_->misc_inherited_2_data_->cursor_data_;
  if (!(base::ValuesEquivalent(cursor_data__expr, o_cursor_data__expr))) {
    DebugDiff d;
    d.field = DebugField::cursor_data_;
    d.actual = DebugStringForField(cursor_data__expr);
    d.correct = DebugStringForField(o_cursor_data__expr);
    diff.push_back(std::move(d));
  }
  const auto& initial_data__expr = misc_inherited_data_->misc_inherited_2_data_->initial_data_;
  const auto& o_initial_data__expr = o.misc_inherited_data_->misc_inherited_2_data_->initial_data_;
  if (!(base::ValuesEquivalent(initial_data__expr, o_initial_data__expr))) {
    DebugDiff d;
    d.field = DebugField::initial_data_;
    d.actual = DebugStringForField(initial_data__expr);
    d.correct = DebugStringForField(o_initial_data__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_underline_offset__expr = misc_inherited_data_->misc_inherited_2_data_->text_underline_offset_;
  const auto& o_text_underline_offset__expr = o.misc_inherited_data_->misc_inherited_2_data_->text_underline_offset_;
  if (!(text_underline_offset__expr == o_text_underline_offset__expr)) {
    DebugDiff d;
    d.field = DebugField::text_underline_offset_;
    d.actual = DebugStringForField(text_underline_offset__expr);
    d.correct = DebugStringForField(o_text_underline_offset__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_stroke_width__expr = misc_inherited_data_->misc_inherited_2_data_->text_stroke_width_;
  const auto& o_text_stroke_width__expr = o.misc_inherited_data_->misc_inherited_2_data_->text_stroke_width_;
  if (!(text_stroke_width__expr == o_text_stroke_width__expr)) {
    DebugDiff d;
    d.field = DebugField::text_stroke_width_;
    d.actual = DebugStringForField(text_stroke_width__expr);
    d.correct = DebugStringForField(o_text_stroke_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& effective_zoom__expr = misc_inherited_data_->misc_inherited_2_data_->effective_zoom_;
  const auto& o_effective_zoom__expr = o.misc_inherited_data_->misc_inherited_2_data_->effective_zoom_;
  if (!(effective_zoom__expr == o_effective_zoom__expr)) {
    DebugDiff d;
    d.field = DebugField::effective_zoom_;
    d.actual = DebugStringForField(effective_zoom__expr);
    d.correct = DebugStringForField(o_effective_zoom__expr);
    diff.push_back(std::move(d));
  }
  const auto& tap_highlight_color__expr = misc_inherited_data_->misc_inherited_2_data_->tap_highlight_color_;
  const auto& o_tap_highlight_color__expr = o.misc_inherited_data_->misc_inherited_2_data_->tap_highlight_color_;
  if (!(tap_highlight_color__expr == o_tap_highlight_color__expr)) {
    DebugDiff d;
    d.field = DebugField::tap_highlight_color_;
    d.actual = DebugStringForField(tap_highlight_color__expr);
    d.correct = DebugStringForField(o_tap_highlight_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_fill_color__expr = misc_inherited_data_->misc_inherited_2_data_->text_fill_color_;
  const auto& o_text_fill_color__expr = o.misc_inherited_data_->misc_inherited_2_data_->text_fill_color_;
  if (!(text_fill_color__expr == o_text_fill_color__expr)) {
    DebugDiff d;
    d.field = DebugField::text_fill_color_;
    d.actual = DebugStringForField(text_fill_color__expr);
    d.correct = DebugStringForField(o_text_fill_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_stroke_color__expr = misc_inherited_data_->misc_inherited_2_data_->text_stroke_color_;
  const auto& o_text_stroke_color__expr = o.misc_inherited_data_->misc_inherited_2_data_->text_stroke_color_;
  if (!(text_stroke_color__expr == o_text_stroke_color__expr)) {
    DebugDiff d;
    d.field = DebugField::text_stroke_color_;
    d.actual = DebugStringForField(text_stroke_color__expr);
    d.correct = DebugStringForField(o_text_stroke_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& widows__expr = misc_inherited_data_->misc_inherited_2_data_->widows_;
  const auto& o_widows__expr = o.misc_inherited_data_->misc_inherited_2_data_->widows_;
  if (!(widows__expr == o_widows__expr)) {
    DebugDiff d;
    d.field = DebugField::widows_;
    d.actual = DebugStringForField(widows__expr);
    d.correct = DebugStringForField(o_widows__expr);
    diff.push_back(std::move(d));
  }
  const auto& effective_touch_action__expr = misc_inherited_data_->misc_inherited_2_data_->effective_touch_action_;
  const auto& o_effective_touch_action__expr = o.misc_inherited_data_->misc_inherited_2_data_->effective_touch_action_;
  if (!(effective_touch_action__expr == o_effective_touch_action__expr)) {
    DebugDiff d;
    d.field = DebugField::effective_touch_action_;
    d.actual = DebugStringForField(effective_touch_action__expr);
    d.correct = DebugStringForField(o_effective_touch_action__expr);
    diff.push_back(std::move(d));
  }

  // Group: misc-inherited
  const auto& text_box_edge__expr = misc_inherited_data_->text_box_edge_;
  const auto& o_text_box_edge__expr = o.misc_inherited_data_->text_box_edge_;
  if (!(text_box_edge__expr == o_text_box_edge__expr)) {
    DebugDiff d;
    d.field = DebugField::text_box_edge_;
    d.actual = DebugStringForField(text_box_edge__expr);
    d.correct = DebugStringForField(o_text_box_edge__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_underline_position__expr = misc_inherited_data_->text_underline_position_;
  const auto& o_text_underline_position__expr = o.misc_inherited_data_->text_underline_position_;
  if (!(text_underline_position__expr == o_text_underline_position__expr)) {
    DebugDiff d;
    d.field = DebugField::text_underline_position_;
    d.actual = DebugStringForField(text_underline_position__expr);
    d.correct = DebugStringForField(o_text_underline_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& hanging_punctuation__expr = misc_inherited_data_->hanging_punctuation_;
  const auto& o_hanging_punctuation__expr = o.misc_inherited_data_->hanging_punctuation_;
  if (!(hanging_punctuation__expr == o_hanging_punctuation__expr)) {
    DebugDiff d;
    d.field = DebugField::hanging_punctuation_;
    d.actual = DebugStringForField(hanging_punctuation__expr);
    d.correct = DebugStringForField(o_hanging_punctuation__expr);
    diff.push_back(std::move(d));
  }
  const auto& image_rendering__expr = misc_inherited_data_->image_rendering_;
  const auto& o_image_rendering__expr = o.misc_inherited_data_->image_rendering_;
  if (!(image_rendering__expr == o_image_rendering__expr)) {
    DebugDiff d;
    d.field = DebugField::image_rendering_;
    d.actual = DebugStringForField(image_rendering__expr);
    d.correct = DebugStringForField(o_image_rendering__expr);
    diff.push_back(std::move(d));
  }
  const auto& line_break__expr = misc_inherited_data_->line_break_;
  const auto& o_line_break__expr = o.misc_inherited_data_->line_break_;
  if (!(line_break__expr == o_line_break__expr)) {
    DebugDiff d;
    d.field = DebugField::line_break_;
    d.actual = DebugStringForField(line_break__expr);
    d.correct = DebugStringForField(o_line_break__expr);
    diff.push_back(std::move(d));
  }
  const auto& speak__expr = misc_inherited_data_->speak_;
  const auto& o_speak__expr = o.misc_inherited_data_->speak_;
  if (!(speak__expr == o_speak__expr)) {
    DebugDiff d;
    d.field = DebugField::speak_;
    d.actual = DebugStringForField(speak__expr);
    d.correct = DebugStringForField(o_speak__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_align_last__expr = misc_inherited_data_->text_align_last_;
  const auto& o_text_align_last__expr = o.misc_inherited_data_->text_align_last_;
  if (!(text_align_last__expr == o_text_align_last__expr)) {
    DebugDiff d;
    d.field = DebugField::text_align_last_;
    d.actual = DebugStringForField(text_align_last__expr);
    d.correct = DebugStringForField(o_text_align_last__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_decoration_skip_spaces__expr = misc_inherited_data_->text_decoration_skip_spaces_;
  const auto& o_text_decoration_skip_spaces__expr = o.misc_inherited_data_->text_decoration_skip_spaces_;
  if (!(text_decoration_skip_spaces__expr == o_text_decoration_skip_spaces__expr)) {
    DebugDiff d;
    d.field = DebugField::text_decoration_skip_spaces_;
    d.actual = DebugStringForField(text_decoration_skip_spaces__expr);
    d.correct = DebugStringForField(o_text_decoration_skip_spaces__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_emphasis_mark__expr = misc_inherited_data_->text_emphasis_mark_;
  const auto& o_text_emphasis_mark__expr = o.misc_inherited_data_->text_emphasis_mark_;
  if (!(text_emphasis_mark__expr == o_text_emphasis_mark__expr)) {
    DebugDiff d;
    d.field = DebugField::text_emphasis_mark_;
    d.actual = DebugStringForField(text_emphasis_mark__expr);
    d.correct = DebugStringForField(o_text_emphasis_mark__expr);
    diff.push_back(std::move(d));
  }
  const auto& block_ellipsis__expr = misc_inherited_data_->block_ellipsis_;
  const auto& o_block_ellipsis__expr = o.misc_inherited_data_->block_ellipsis_;
  if (!(block_ellipsis__expr == o_block_ellipsis__expr)) {
    DebugDiff d;
    d.field = DebugField::block_ellipsis_;
    d.actual = DebugStringForField(block_ellipsis__expr);
    d.correct = DebugStringForField(o_block_ellipsis__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_emphasis_position__expr = misc_inherited_data_->text_emphasis_position_;
  const auto& o_text_emphasis_position__expr = o.misc_inherited_data_->text_emphasis_position_;
  if (!(text_emphasis_position__expr == o_text_emphasis_position__expr)) {
    DebugDiff d;
    d.field = DebugField::text_emphasis_position_;
    d.actual = DebugStringForField(text_emphasis_position__expr);
    d.correct = DebugStringForField(o_text_emphasis_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& user_select__expr = misc_inherited_data_->user_select_;
  const auto& o_user_select__expr = o.misc_inherited_data_->user_select_;
  if (!(user_select__expr == o_user_select__expr)) {
    DebugDiff d;
    d.field = DebugField::user_select_;
    d.actual = DebugStringForField(user_select__expr);
    d.correct = DebugStringForField(o_user_select__expr);
    diff.push_back(std::move(d));
  }
  const auto& word_break__expr = misc_inherited_data_->word_break_;
  const auto& o_word_break__expr = o.misc_inherited_data_->word_break_;
  if (!(word_break__expr == o_word_break__expr)) {
    DebugDiff d;
    d.field = DebugField::word_break_;
    d.actual = DebugStringForField(word_break__expr);
    d.correct = DebugStringForField(o_word_break__expr);
    diff.push_back(std::move(d));
  }
  const auto& forced_color_adjust__expr = misc_inherited_data_->forced_color_adjust_;
  const auto& o_forced_color_adjust__expr = o.misc_inherited_data_->forced_color_adjust_;
  if (!(forced_color_adjust__expr == o_forced_color_adjust__expr)) {
    DebugDiff d;
    d.field = DebugField::forced_color_adjust_;
    d.actual = DebugStringForField(forced_color_adjust__expr);
    d.correct = DebugStringForField(o_forced_color_adjust__expr);
    diff.push_back(std::move(d));
  }
  const auto& hyphens__expr = misc_inherited_data_->hyphens_;
  const auto& o_hyphens__expr = o.misc_inherited_data_->hyphens_;
  if (!(hyphens__expr == o_hyphens__expr)) {
    DebugDiff d;
    d.field = DebugField::hyphens_;
    d.actual = DebugStringForField(hyphens__expr);
    d.correct = DebugStringForField(o_hyphens__expr);
    diff.push_back(std::move(d));
  }
  const auto& image_animation__expr = misc_inherited_data_->image_animation_;
  const auto& o_image_animation__expr = o.misc_inherited_data_->image_animation_;
  if (!(image_animation__expr == o_image_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::image_animation_;
    d.actual = DebugStringForField(image_animation__expr);
    d.correct = DebugStringForField(o_image_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& overflow_wrap__expr = misc_inherited_data_->overflow_wrap_;
  const auto& o_overflow_wrap__expr = o.misc_inherited_data_->overflow_wrap_;
  if (!(overflow_wrap__expr == o_overflow_wrap__expr)) {
    DebugDiff d;
    d.field = DebugField::overflow_wrap_;
    d.actual = DebugStringForField(overflow_wrap__expr);
    d.correct = DebugStringForField(o_overflow_wrap__expr);
    diff.push_back(std::move(d));
  }
  const auto& ruby_align__expr = misc_inherited_data_->ruby_align_;
  const auto& o_ruby_align__expr = o.misc_inherited_data_->ruby_align_;
  if (!(ruby_align__expr == o_ruby_align__expr)) {
    DebugDiff d;
    d.field = DebugField::ruby_align_;
    d.actual = DebugStringForField(ruby_align__expr);
    d.correct = DebugStringForField(o_ruby_align__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_decoration_skip_ink__expr = misc_inherited_data_->text_decoration_skip_ink_;
  const auto& o_text_decoration_skip_ink__expr = o.misc_inherited_data_->text_decoration_skip_ink_;
  if (!(text_decoration_skip_ink__expr == o_text_decoration_skip_ink__expr)) {
    DebugDiff d;
    d.field = DebugField::text_decoration_skip_ink_;
    d.actual = DebugStringForField(text_decoration_skip_ink__expr);
    d.correct = DebugStringForField(o_text_decoration_skip_ink__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_indent_flags__expr = misc_inherited_data_->text_indent_flags_;
  const auto& o_text_indent_flags__expr = o.misc_inherited_data_->text_indent_flags_;
  if (!(text_indent_flags__expr == o_text_indent_flags__expr)) {
    DebugDiff d;
    d.field = DebugField::text_indent_flags_;
    d.actual = DebugStringForField(text_indent_flags__expr);
    d.correct = DebugStringForField(o_text_indent_flags__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_justify__expr = misc_inherited_data_->text_justify_;
  const auto& o_text_justify__expr = o.misc_inherited_data_->text_justify_;
  if (!(text_justify__expr == o_text_justify__expr)) {
    DebugDiff d;
    d.field = DebugField::text_justify_;
    d.actual = DebugStringForField(text_justify__expr);
    d.correct = DebugStringForField(o_text_justify__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_orientation__expr = misc_inherited_data_->text_orientation_;
  const auto& o_text_orientation__expr = o.misc_inherited_data_->text_orientation_;
  if (!(text_orientation__expr == o_text_orientation__expr)) {
    DebugDiff d;
    d.field = DebugField::text_orientation_;
    d.actual = DebugStringForField(text_orientation__expr);
    d.correct = DebugStringForField(o_text_orientation__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_security__expr = misc_inherited_data_->text_security_;
  const auto& o_text_security__expr = o.misc_inherited_data_->text_security_;
  if (!(text_security__expr == o_text_security__expr)) {
    DebugDiff d;
    d.field = DebugField::text_security_;
    d.actual = DebugStringForField(text_security__expr);
    d.correct = DebugStringForField(o_text_security__expr);
    diff.push_back(std::move(d));
  }
  const auto& user_modify__expr = misc_inherited_data_->user_modify_;
  const auto& o_user_modify__expr = o.misc_inherited_data_->user_modify_;
  if (!(user_modify__expr == o_user_modify__expr)) {
    DebugDiff d;
    d.field = DebugField::user_modify_;
    d.actual = DebugStringForField(user_modify__expr);
    d.correct = DebugStringForField(o_user_modify__expr);
    diff.push_back(std::move(d));
  }
  const auto& empty_cells__expr = misc_inherited_data_->empty_cells_;
  const auto& o_empty_cells__expr = o.misc_inherited_data_->empty_cells_;
  if (!(empty_cells__expr == o_empty_cells__expr)) {
    DebugDiff d;
    d.field = DebugField::empty_cells_;
    d.actual = DebugStringForField(empty_cells__expr);
    d.correct = DebugStringForField(o_empty_cells__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_line_if_empty__expr = misc_inherited_data_->has_line_if_empty_;
  const auto& o_has_line_if_empty__expr = o.misc_inherited_data_->has_line_if_empty_;
  if (!(has_line_if_empty__expr == o_has_line_if_empty__expr)) {
    DebugDiff d;
    d.field = DebugField::has_line_if_empty_;
    d.actual = DebugStringForField(has_line_if_empty__expr);
    d.correct = DebugStringForField(o_has_line_if_empty__expr);
    diff.push_back(std::move(d));
  }
  const auto& image_orientation__expr = misc_inherited_data_->image_orientation_;
  const auto& o_image_orientation__expr = o.misc_inherited_data_->image_orientation_;
  if (!(image_orientation__expr == o_image_orientation__expr)) {
    DebugDiff d;
    d.field = DebugField::image_orientation_;
    d.actual = DebugStringForField(image_orientation__expr);
    d.correct = DebugStringForField(o_image_orientation__expr);
    diff.push_back(std::move(d));
  }
  const auto& in_base_appearance__expr = misc_inherited_data_->in_base_appearance_;
  const auto& o_in_base_appearance__expr = o.misc_inherited_data_->in_base_appearance_;
  if (!(in_base_appearance__expr == o_in_base_appearance__expr)) {
    DebugDiff d;
    d.field = DebugField::in_base_appearance_;
    d.actual = DebugStringForField(in_base_appearance__expr);
    d.correct = DebugStringForField(o_in_base_appearance__expr);
    diff.push_back(std::move(d));
  }
  const auto& interactivity__expr = misc_inherited_data_->interactivity_;
  const auto& o_interactivity__expr = o.misc_inherited_data_->interactivity_;
  if (!(interactivity__expr == o_interactivity__expr)) {
    DebugDiff d;
    d.field = DebugField::interactivity_;
    d.actual = DebugStringForField(interactivity__expr);
    d.correct = DebugStringForField(o_interactivity__expr);
    diff.push_back(std::move(d));
  }
  const auto& interpolate_size__expr = misc_inherited_data_->interpolate_size_;
  const auto& o_interpolate_size__expr = o.misc_inherited_data_->interpolate_size_;
  if (!(interpolate_size__expr == o_interpolate_size__expr)) {
    DebugDiff d;
    d.field = DebugField::interpolate_size_;
    d.actual = DebugStringForField(interpolate_size__expr);
    d.correct = DebugStringForField(o_interpolate_size__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_shift__expr = misc_inherited_data_->math_shift_;
  const auto& o_math_shift__expr = o.misc_inherited_data_->math_shift_;
  if (!(math_shift__expr == o_math_shift__expr)) {
    DebugDiff d;
    d.field = DebugField::math_shift_;
    d.actual = DebugStringForField(math_shift__expr);
    d.correct = DebugStringForField(o_math_shift__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_style__expr = misc_inherited_data_->math_style_;
  const auto& o_math_style__expr = o.misc_inherited_data_->math_style_;
  if (!(math_style__expr == o_math_style__expr)) {
    DebugDiff d;
    d.field = DebugField::math_style_;
    d.actual = DebugStringForField(math_style__expr);
    d.correct = DebugStringForField(o_math_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& ruby_overhang__expr = misc_inherited_data_->ruby_overhang_;
  const auto& o_ruby_overhang__expr = o.misc_inherited_data_->ruby_overhang_;
  if (!(ruby_overhang__expr == o_ruby_overhang__expr)) {
    DebugDiff d;
    d.field = DebugField::ruby_overhang_;
    d.actual = DebugStringForField(ruby_overhang__expr);
    d.correct = DebugStringForField(o_ruby_overhang__expr);
    diff.push_back(std::move(d));
  }
  const auto& ruby_position__expr = misc_inherited_data_->ruby_position_;
  const auto& o_ruby_position__expr = o.misc_inherited_data_->ruby_position_;
  if (!(ruby_position__expr == o_ruby_position__expr)) {
    DebugDiff d;
    d.field = DebugField::ruby_position_;
    d.actual = DebugStringForField(ruby_position__expr);
    d.correct = DebugStringForField(o_ruby_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& subtree_is_sticky__expr = misc_inherited_data_->subtree_is_sticky_;
  const auto& o_subtree_is_sticky__expr = o.misc_inherited_data_->subtree_is_sticky_;
  if (!(subtree_is_sticky__expr == o_subtree_is_sticky__expr)) {
    DebugDiff d;
    d.field = DebugField::subtree_is_sticky_;
    d.actual = DebugStringForField(subtree_is_sticky__expr);
    d.correct = DebugStringForField(o_subtree_is_sticky__expr);
    diff.push_back(std::move(d));
  }
  const auto& subtree_will_change_contents__expr = misc_inherited_data_->subtree_will_change_contents_;
  const auto& o_subtree_will_change_contents__expr = o.misc_inherited_data_->subtree_will_change_contents_;
  if (!(subtree_will_change_contents__expr == o_subtree_will_change_contents__expr)) {
    DebugDiff d;
    d.field = DebugField::subtree_will_change_contents_;
    d.actual = DebugStringForField(subtree_will_change_contents__expr);
    d.correct = DebugStringForField(o_subtree_will_change_contents__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_autospace__expr = misc_inherited_data_->text_autospace_;
  const auto& o_text_autospace__expr = o.misc_inherited_data_->text_autospace_;
  if (!(text_autospace__expr == o_text_autospace__expr)) {
    DebugDiff d;
    d.field = DebugField::text_autospace_;
    d.actual = DebugStringForField(text_autospace__expr);
    d.correct = DebugStringForField(o_text_autospace__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_combine__expr = misc_inherited_data_->text_combine_;
  const auto& o_text_combine__expr = o.misc_inherited_data_->text_combine_;
  if (!(text_combine__expr == o_text_combine__expr)) {
    DebugDiff d;
    d.field = DebugField::text_combine_;
    d.actual = DebugStringForField(text_combine__expr);
    d.correct = DebugStringForField(o_text_combine__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_emphasis_fill__expr = misc_inherited_data_->text_emphasis_fill_;
  const auto& o_text_emphasis_fill__expr = o.misc_inherited_data_->text_emphasis_fill_;
  if (!(text_emphasis_fill__expr == o_text_emphasis_fill__expr)) {
    DebugDiff d;
    d.field = DebugField::text_emphasis_fill_;
    d.actual = DebugStringForField(text_emphasis_fill__expr);
    d.correct = DebugStringForField(o_text_emphasis_fill__expr);
    diff.push_back(std::move(d));
  }

      // Group: misc1
  const auto& backdrop_filter__expr = misc_data_->misc_1_data_->backdrop_filter_;
  const auto& o_backdrop_filter__expr = o.misc_data_->misc_1_data_->backdrop_filter_;
  if (!(backdrop_filter__expr == o_backdrop_filter__expr)) {
    DebugDiff d;
    d.field = DebugField::backdrop_filter_;
    d.actual = DebugStringForField(backdrop_filter__expr);
    d.correct = DebugStringForField(o_backdrop_filter__expr);
    diff.push_back(std::move(d));
  }
  const auto& animation_trigger__expr = misc_data_->misc_1_data_->animation_trigger_;
  const auto& o_animation_trigger__expr = o.misc_data_->misc_1_data_->animation_trigger_;
  if (!(animation_trigger__expr == o_animation_trigger__expr)) {
    DebugDiff d;
    d.field = DebugField::animation_trigger_;
    d.actual = DebugStringForField(animation_trigger__expr);
    d.correct = DebugStringForField(o_animation_trigger__expr);
    diff.push_back(std::move(d));
  }
  const auto& anchor_scope__expr = misc_data_->misc_1_data_->anchor_scope_;
  const auto& o_anchor_scope__expr = o.misc_data_->misc_1_data_->anchor_scope_;
  if (!(anchor_scope__expr == o_anchor_scope__expr)) {
    DebugDiff d;
    d.field = DebugField::anchor_scope_;
    d.actual = DebugStringForField(anchor_scope__expr);
    d.correct = DebugStringForField(o_anchor_scope__expr);
    diff.push_back(std::move(d));
  }
  const auto& position_anchor__expr = misc_data_->misc_1_data_->position_anchor_;
  const auto& o_position_anchor__expr = o.misc_data_->misc_1_data_->position_anchor_;
  if (!(position_anchor__expr == o_position_anchor__expr)) {
    DebugDiff d;
    d.field = DebugField::position_anchor_;
    d.actual = DebugStringForField(position_anchor__expr);
    d.correct = DebugStringForField(o_position_anchor__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_color__expr = misc_data_->misc_1_data_->column_rule_color_;
  const auto& o_column_rule_color__expr = o.misc_data_->misc_1_data_->column_rule_color_;
  if (!(column_rule_color__expr == o_column_rule_color__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_color_;
    d.actual = DebugStringForField(column_rule_color__expr);
    d.correct = DebugStringForField(o_column_rule_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& anchor_name__expr = misc_data_->misc_1_data_->anchor_name_;
  const auto& o_anchor_name__expr = o.misc_data_->misc_1_data_->anchor_name_;
  if (!(base::ValuesEquivalent(anchor_name__expr, o_anchor_name__expr))) {
    DebugDiff d;
    d.field = DebugField::anchor_name_;
    d.actual = DebugStringForField(anchor_name__expr);
    d.correct = DebugStringForField(o_anchor_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_shape__expr = misc_data_->misc_1_data_->border_shape_;
  const auto& o_border_shape__expr = o.misc_data_->misc_1_data_->border_shape_;
  if (!(base::ValuesEquivalent(border_shape__expr, o_border_shape__expr))) {
    DebugDiff d;
    d.field = DebugField::border_shape_;
    d.actual = DebugStringForField(border_shape__expr);
    d.correct = DebugStringForField(o_border_shape__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_shadow__expr = misc_data_->misc_1_data_->box_shadow_;
  const auto& o_box_shadow__expr = o.misc_data_->misc_1_data_->box_shadow_;
  if (!(base::ValuesEquivalent(box_shadow__expr, o_box_shadow__expr))) {
    DebugDiff d;
    d.field = DebugField::box_shadow_;
    d.actual = DebugStringForField(box_shadow__expr);
    d.correct = DebugStringForField(o_box_shadow__expr);
    diff.push_back(std::move(d));
  }
  const auto& clip_path__expr = misc_data_->misc_1_data_->clip_path_;
  const auto& o_clip_path__expr = o.misc_data_->misc_1_data_->clip_path_;
  if (!(base::ValuesEquivalent(clip_path__expr, o_clip_path__expr))) {
    DebugDiff d;
    d.field = DebugField::clip_path_;
    d.actual = DebugStringForField(clip_path__expr);
    d.correct = DebugStringForField(o_clip_path__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_gap__expr = misc_data_->misc_1_data_->column_gap_;
  const auto& o_column_gap__expr = o.misc_data_->misc_1_data_->column_gap_;
  if (!(column_gap__expr == o_column_gap__expr)) {
    DebugDiff d;
    d.field = DebugField::column_gap_;
    d.actual = DebugStringForField(column_gap__expr);
    d.correct = DebugStringForField(o_column_gap__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_inset_cap_end__expr = misc_data_->misc_1_data_->column_rule_inset_cap_end_;
  const auto& o_column_rule_inset_cap_end__expr = o.misc_data_->misc_1_data_->column_rule_inset_cap_end_;
  if (!(column_rule_inset_cap_end__expr == o_column_rule_inset_cap_end__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_inset_cap_end_;
    d.actual = DebugStringForField(column_rule_inset_cap_end__expr);
    d.correct = DebugStringForField(o_column_rule_inset_cap_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_height__expr = misc_data_->misc_1_data_->column_height_;
  const auto& o_column_height__expr = o.misc_data_->misc_1_data_->column_height_;
  if (!(column_height__expr == o_column_height__expr)) {
    DebugDiff d;
    d.field = DebugField::column_height_;
    d.actual = DebugStringForField(column_height__expr);
    d.correct = DebugStringForField(o_column_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& position_area__expr = misc_data_->misc_1_data_->position_area_;
  const auto& o_position_area__expr = o.misc_data_->misc_1_data_->position_area_;
  if (!(position_area__expr == o_position_area__expr)) {
    DebugDiff d;
    d.field = DebugField::position_area_;
    d.actual = DebugStringForField(position_area__expr);
    d.correct = DebugStringForField(o_position_area__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_count__expr = misc_data_->misc_1_data_->column_count_;
  const auto& o_column_count__expr = o.misc_data_->misc_1_data_->column_count_;
  if (!(column_count__expr == o_column_count__expr)) {
    DebugDiff d;
    d.field = DebugField::column_count_;
    d.actual = DebugStringForField(column_count__expr);
    d.correct = DebugStringForField(o_column_count__expr);
    diff.push_back(std::move(d));
  }
  const auto& align_self__expr = misc_data_->misc_1_data_->align_self_;
  const auto& o_align_self__expr = o.misc_data_->misc_1_data_->align_self_;
  if (!(align_self__expr == o_align_self__expr)) {
    DebugDiff d;
    d.field = DebugField::align_self_;
    d.actual = DebugStringForField(align_self__expr);
    d.correct = DebugStringForField(o_align_self__expr);
    diff.push_back(std::move(d));
  }
  const auto& align_content__expr = misc_data_->misc_1_data_->align_content_;
  const auto& o_align_content__expr = o.misc_data_->misc_1_data_->align_content_;
  if (!(align_content__expr == o_align_content__expr)) {
    DebugDiff d;
    d.field = DebugField::align_content_;
    d.actual = DebugStringForField(align_content__expr);
    d.correct = DebugStringForField(o_align_content__expr);
    diff.push_back(std::move(d));
  }

    // Group: visited
  const auto& internal_visited_column_rule_color__expr = misc_data_->visited_data_->internal_visited_column_rule_color_;
  const auto& o_internal_visited_column_rule_color__expr = o.misc_data_->visited_data_->internal_visited_column_rule_color_;
  if (!(internal_visited_column_rule_color__expr == o_internal_visited_column_rule_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_column_rule_color_;
    d.actual = DebugStringForField(internal_visited_column_rule_color__expr);
    d.correct = DebugStringForField(o_internal_visited_column_rule_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_background_color__expr = misc_data_->visited_data_->internal_visited_background_color_;
  const auto& o_internal_visited_background_color__expr = o.misc_data_->visited_data_->internal_visited_background_color_;
  if (!(internal_visited_background_color__expr == o_internal_visited_background_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_background_color_;
    d.actual = DebugStringForField(internal_visited_background_color__expr);
    d.correct = DebugStringForField(o_internal_visited_background_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_border_bottom_color__expr = misc_data_->visited_data_->internal_visited_border_bottom_color_;
  const auto& o_internal_visited_border_bottom_color__expr = o.misc_data_->visited_data_->internal_visited_border_bottom_color_;
  if (!(internal_visited_border_bottom_color__expr == o_internal_visited_border_bottom_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_border_bottom_color_;
    d.actual = DebugStringForField(internal_visited_border_bottom_color__expr);
    d.correct = DebugStringForField(o_internal_visited_border_bottom_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_border_left_color__expr = misc_data_->visited_data_->internal_visited_border_left_color_;
  const auto& o_internal_visited_border_left_color__expr = o.misc_data_->visited_data_->internal_visited_border_left_color_;
  if (!(internal_visited_border_left_color__expr == o_internal_visited_border_left_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_border_left_color_;
    d.actual = DebugStringForField(internal_visited_border_left_color__expr);
    d.correct = DebugStringForField(o_internal_visited_border_left_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_border_right_color__expr = misc_data_->visited_data_->internal_visited_border_right_color_;
  const auto& o_internal_visited_border_right_color__expr = o.misc_data_->visited_data_->internal_visited_border_right_color_;
  if (!(internal_visited_border_right_color__expr == o_internal_visited_border_right_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_border_right_color_;
    d.actual = DebugStringForField(internal_visited_border_right_color__expr);
    d.correct = DebugStringForField(o_internal_visited_border_right_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_border_top_color__expr = misc_data_->visited_data_->internal_visited_border_top_color_;
  const auto& o_internal_visited_border_top_color__expr = o.misc_data_->visited_data_->internal_visited_border_top_color_;
  if (!(internal_visited_border_top_color__expr == o_internal_visited_border_top_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_border_top_color_;
    d.actual = DebugStringForField(internal_visited_border_top_color__expr);
    d.correct = DebugStringForField(o_internal_visited_border_top_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_outline_color__expr = misc_data_->visited_data_->internal_visited_outline_color_;
  const auto& o_internal_visited_outline_color__expr = o.misc_data_->visited_data_->internal_visited_outline_color_;
  if (!(internal_visited_outline_color__expr == o_internal_visited_outline_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_outline_color_;
    d.actual = DebugStringForField(internal_visited_outline_color__expr);
    d.correct = DebugStringForField(o_internal_visited_outline_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_text_decoration_color__expr = misc_data_->visited_data_->internal_visited_text_decoration_color_;
  const auto& o_internal_visited_text_decoration_color__expr = o.misc_data_->visited_data_->internal_visited_text_decoration_color_;
  if (!(internal_visited_text_decoration_color__expr == o_internal_visited_text_decoration_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_text_decoration_color_;
    d.actual = DebugStringForField(internal_visited_text_decoration_color__expr);
    d.correct = DebugStringForField(o_internal_visited_text_decoration_color__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc2
  const auto& grid_auto_columns__expr = misc_data_->misc_2_data_->grid_auto_columns_;
  const auto& o_grid_auto_columns__expr = o.misc_data_->misc_2_data_->grid_auto_columns_;
  if (!(grid_auto_columns__expr == o_grid_auto_columns__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_auto_columns_;
    d.actual = DebugStringForField(grid_auto_columns__expr);
    d.correct = DebugStringForField(o_grid_auto_columns__expr);
    diff.push_back(std::move(d));
  }
  const auto& filter__expr = misc_data_->misc_2_data_->filter_;
  const auto& o_filter__expr = o.misc_data_->misc_2_data_->filter_;
  if (!(filter__expr == o_filter__expr)) {
    DebugDiff d;
    d.field = DebugField::filter_;
    d.actual = DebugStringForField(filter__expr);
    d.correct = DebugStringForField(o_filter__expr);
    diff.push_back(std::move(d));
  }
  const auto& flow_tolerance__expr = misc_data_->misc_2_data_->flow_tolerance_;
  const auto& o_flow_tolerance__expr = o.misc_data_->misc_2_data_->flow_tolerance_;
  if (!(flow_tolerance__expr == o_flow_tolerance__expr)) {
    DebugDiff d;
    d.field = DebugField::flow_tolerance_;
    d.actual = DebugStringForField(flow_tolerance__expr);
    d.correct = DebugStringForField(o_flow_tolerance__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_width__expr = misc_data_->misc_2_data_->column_rule_width_;
  const auto& o_column_rule_width__expr = o.misc_data_->misc_2_data_->column_rule_width_;
  if (!(column_rule_width__expr == o_column_rule_width__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_width_;
    d.actual = DebugStringForField(column_rule_width__expr);
    d.correct = DebugStringForField(o_column_rule_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_style__expr = misc_data_->misc_2_data_->column_rule_style_;
  const auto& o_column_rule_style__expr = o.misc_data_->misc_2_data_->column_rule_style_;
  if (!(column_rule_style__expr == o_column_rule_style__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_style_;
    d.actual = DebugStringForField(column_rule_style__expr);
    d.correct = DebugStringForField(o_column_rule_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& container_name__expr = misc_data_->misc_2_data_->container_name_;
  const auto& o_container_name__expr = o.misc_data_->misc_2_data_->container_name_;
  if (!(base::ValuesEquivalent(container_name__expr, o_container_name__expr))) {
    DebugDiff d;
    d.field = DebugField::container_name_;
    d.actual = DebugStringForField(container_name__expr);
    d.correct = DebugStringForField(o_container_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& content__expr = misc_data_->misc_2_data_->content_;
  const auto& o_content__expr = o.misc_data_->misc_2_data_->content_;
  if (!(base::ValuesEquivalent(content__expr, o_content__expr))) {
    DebugDiff d;
    d.field = DebugField::content_;
    d.actual = DebugStringForField(content__expr);
    d.correct = DebugStringForField(o_content__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_inset_cap_start__expr = misc_data_->misc_2_data_->column_rule_inset_cap_start_;
  const auto& o_column_rule_inset_cap_start__expr = o.misc_data_->misc_2_data_->column_rule_inset_cap_start_;
  if (!(column_rule_inset_cap_start__expr == o_column_rule_inset_cap_start__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_inset_cap_start_;
    d.actual = DebugStringForField(column_rule_inset_cap_start__expr);
    d.correct = DebugStringForField(o_column_rule_inset_cap_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_inset_junction_end__expr = misc_data_->misc_2_data_->column_rule_inset_junction_end_;
  const auto& o_column_rule_inset_junction_end__expr = o.misc_data_->misc_2_data_->column_rule_inset_junction_end_;
  if (!(column_rule_inset_junction_end__expr == o_column_rule_inset_junction_end__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_inset_junction_end_;
    d.actual = DebugStringForField(column_rule_inset_junction_end__expr);
    d.correct = DebugStringForField(o_column_rule_inset_junction_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_inset_junction_start__expr = misc_data_->misc_2_data_->column_rule_inset_junction_start_;
  const auto& o_column_rule_inset_junction_start__expr = o.misc_data_->misc_2_data_->column_rule_inset_junction_start_;
  if (!(column_rule_inset_junction_start__expr == o_column_rule_inset_junction_start__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_inset_junction_start_;
    d.actual = DebugStringForField(column_rule_inset_junction_start__expr);
    d.correct = DebugStringForField(o_column_rule_inset_junction_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& flex_basis__expr = misc_data_->misc_2_data_->flex_basis_;
  const auto& o_flex_basis__expr = o.misc_data_->misc_2_data_->flex_basis_;
  if (!(flex_basis__expr == o_flex_basis__expr)) {
    DebugDiff d;
    d.field = DebugField::flex_basis_;
    d.actual = DebugStringForField(flex_basis__expr);
    d.correct = DebugStringForField(o_flex_basis__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_width__expr = misc_data_->misc_2_data_->column_width_;
  const auto& o_column_width__expr = o.misc_data_->misc_2_data_->column_width_;
  if (!(column_width__expr == o_column_width__expr)) {
    DebugDiff d;
    d.field = DebugField::column_width_;
    d.actual = DebugStringForField(column_width__expr);
    d.correct = DebugStringForField(o_column_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& flex_grow__expr = misc_data_->misc_2_data_->flex_grow_;
  const auto& o_flex_grow__expr = o.misc_data_->misc_2_data_->flex_grow_;
  if (!(flex_grow__expr == o_flex_grow__expr)) {
    DebugDiff d;
    d.field = DebugField::flex_grow_;
    d.actual = DebugStringForField(flex_grow__expr);
    d.correct = DebugStringForField(o_flex_grow__expr);
    diff.push_back(std::move(d));
  }
  const auto& flex_shrink__expr = misc_data_->misc_2_data_->flex_shrink_;
  const auto& o_flex_shrink__expr = o.misc_data_->misc_2_data_->flex_shrink_;
  if (!(flex_shrink__expr == o_flex_shrink__expr)) {
    DebugDiff d;
    d.field = DebugField::flex_shrink_;
    d.actual = DebugStringForField(flex_shrink__expr);
    d.correct = DebugStringForField(o_flex_shrink__expr);
    diff.push_back(std::move(d));
  }
  const auto& flex_line_count__expr = misc_data_->misc_2_data_->flex_line_count_;
  const auto& o_flex_line_count__expr = o.misc_data_->misc_2_data_->flex_line_count_;
  if (!(flex_line_count__expr == o_flex_line_count__expr)) {
    DebugDiff d;
    d.field = DebugField::flex_line_count_;
    d.actual = DebugStringForField(flex_line_count__expr);
    d.correct = DebugStringForField(o_flex_line_count__expr);
    diff.push_back(std::move(d));
  }
  const auto& flex_wrap__expr = misc_data_->misc_2_data_->flex_wrap_;
  const auto& o_flex_wrap__expr = o.misc_data_->misc_2_data_->flex_wrap_;
  if (!(flex_wrap__expr == o_flex_wrap__expr)) {
    DebugDiff d;
    d.field = DebugField::flex_wrap_;
    d.actual = DebugStringForField(flex_wrap__expr);
    d.correct = DebugStringForField(o_flex_wrap__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc3
  const auto& grid_auto_rows__expr = misc_data_->misc_3_data_->grid_auto_rows_;
  const auto& o_grid_auto_rows__expr = o.misc_data_->misc_3_data_->grid_auto_rows_;
  if (!(grid_auto_rows__expr == o_grid_auto_rows__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_auto_rows_;
    d.actual = DebugStringForField(grid_auto_rows__expr);
    d.correct = DebugStringForField(o_grid_auto_rows__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_column_end__expr = misc_data_->misc_3_data_->grid_column_end_;
  const auto& o_grid_column_end__expr = o.misc_data_->misc_3_data_->grid_column_end_;
  if (!(grid_column_end__expr == o_grid_column_end__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_column_end_;
    d.actual = DebugStringForField(grid_column_end__expr);
    d.correct = DebugStringForField(o_grid_column_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_column_start__expr = misc_data_->misc_3_data_->grid_column_start_;
  const auto& o_grid_column_start__expr = o.misc_data_->misc_3_data_->grid_column_start_;
  if (!(grid_column_start__expr == o_grid_column_start__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_column_start_;
    d.actual = DebugStringForField(grid_column_start__expr);
    d.correct = DebugStringForField(o_grid_column_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_row_end__expr = misc_data_->misc_3_data_->grid_row_end_;
  const auto& o_grid_row_end__expr = o.misc_data_->misc_3_data_->grid_row_end_;
  if (!(grid_row_end__expr == o_grid_row_end__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_row_end_;
    d.actual = DebugStringForField(grid_row_end__expr);
    d.correct = DebugStringForField(o_grid_row_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_row_start__expr = misc_data_->misc_3_data_->grid_row_start_;
  const auto& o_grid_row_start__expr = o.misc_data_->misc_3_data_->grid_row_start_;
  if (!(grid_row_start__expr == o_grid_row_start__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_row_start_;
    d.actual = DebugStringForField(grid_row_start__expr);
    d.correct = DebugStringForField(o_grid_row_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_template_areas__expr = misc_data_->misc_3_data_->grid_template_areas_;
  const auto& o_grid_template_areas__expr = o.misc_data_->misc_3_data_->grid_template_areas_;
  if (!(base::ValuesEquivalent(grid_template_areas__expr, o_grid_template_areas__expr))) {
    DebugDiff d;
    d.field = DebugField::grid_template_areas_;
    d.actual = DebugStringForField(grid_template_areas__expr);
    d.correct = DebugStringForField(o_grid_template_areas__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_template_columns__expr = misc_data_->misc_3_data_->grid_template_columns_;
  const auto& o_grid_template_columns__expr = o.misc_data_->misc_3_data_->grid_template_columns_;
  if (!(base::ValuesEquivalent(grid_template_columns__expr, o_grid_template_columns__expr))) {
    DebugDiff d;
    d.field = DebugField::grid_template_columns_;
    d.actual = DebugStringForField(grid_template_columns__expr);
    d.correct = DebugStringForField(o_grid_template_columns__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_template_rows__expr = misc_data_->misc_3_data_->grid_template_rows_;
  const auto& o_grid_template_rows__expr = o.misc_data_->misc_3_data_->grid_template_rows_;
  if (!(base::ValuesEquivalent(grid_template_rows__expr, o_grid_template_rows__expr))) {
    DebugDiff d;
    d.field = DebugField::grid_template_rows_;
    d.actual = DebugStringForField(grid_template_rows__expr);
    d.correct = DebugStringForField(o_grid_template_rows__expr);
    diff.push_back(std::move(d));
  }
  const auto& initial_letter__expr = misc_data_->misc_3_data_->initial_letter_;
  const auto& o_initial_letter__expr = o.misc_data_->misc_3_data_->initial_letter_;
  if (!(initial_letter__expr == o_initial_letter__expr)) {
    DebugDiff d;
    d.field = DebugField::initial_letter_;
    d.actual = DebugStringForField(initial_letter__expr);
    d.correct = DebugStringForField(o_initial_letter__expr);
    diff.push_back(std::move(d));
  }
  const auto& object_position__expr = misc_data_->misc_3_data_->object_position_;
  const auto& o_object_position__expr = o.misc_data_->misc_3_data_->object_position_;
  if (!(object_position__expr == o_object_position__expr)) {
    DebugDiff d;
    d.field = DebugField::object_position_;
    d.actual = DebugStringForField(object_position__expr);
    d.correct = DebugStringForField(o_object_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& interest_delay_end__expr = misc_data_->misc_3_data_->interest_delay_end_;
  const auto& o_interest_delay_end__expr = o.misc_data_->misc_3_data_->interest_delay_end_;
  if (!(interest_delay_end__expr == o_interest_delay_end__expr)) {
    DebugDiff d;
    d.field = DebugField::interest_delay_end_;
    d.actual = DebugStringForField(interest_delay_end__expr);
    d.correct = DebugStringForField(o_interest_delay_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& interest_delay_start__expr = misc_data_->misc_3_data_->interest_delay_start_;
  const auto& o_interest_delay_start__expr = o.misc_data_->misc_3_data_->interest_delay_start_;
  if (!(interest_delay_start__expr == o_interest_delay_start__expr)) {
    DebugDiff d;
    d.field = DebugField::interest_delay_start_;
    d.actual = DebugStringForField(interest_delay_start__expr);
    d.correct = DebugStringForField(o_interest_delay_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& max_lines__expr = misc_data_->misc_3_data_->max_lines_;
  const auto& o_max_lines__expr = o.misc_data_->misc_3_data_->max_lines_;
  if (!(max_lines__expr == o_max_lines__expr)) {
    DebugDiff d;
    d.field = DebugField::max_lines_;
    d.actual = DebugStringForField(max_lines__expr);
    d.correct = DebugStringForField(o_max_lines__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_lanes_direction__expr = misc_data_->misc_3_data_->grid_lanes_direction_;
  const auto& o_grid_lanes_direction__expr = o.misc_data_->misc_3_data_->grid_lanes_direction_;
  if (!(grid_lanes_direction__expr == o_grid_lanes_direction__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_lanes_direction_;
    d.actual = DebugStringForField(grid_lanes_direction__expr);
    d.correct = DebugStringForField(o_grid_lanes_direction__expr);
    diff.push_back(std::move(d));
  }
  const auto& justify_items__expr = misc_data_->misc_3_data_->justify_items_;
  const auto& o_justify_items__expr = o.misc_data_->misc_3_data_->justify_items_;
  if (!(justify_items__expr == o_justify_items__expr)) {
    DebugDiff d;
    d.field = DebugField::justify_items_;
    d.actual = DebugStringForField(justify_items__expr);
    d.correct = DebugStringForField(o_justify_items__expr);
    diff.push_back(std::move(d));
  }
  const auto& justify_self__expr = misc_data_->misc_3_data_->justify_self_;
  const auto& o_justify_self__expr = o.misc_data_->misc_3_data_->justify_self_;
  if (!(justify_self__expr == o_justify_self__expr)) {
    DebugDiff d;
    d.field = DebugField::justify_self_;
    d.actual = DebugStringForField(justify_self__expr);
    d.correct = DebugStringForField(o_justify_self__expr);
    diff.push_back(std::move(d));
  }

    // Group: forced_colors
  const auto& internal_forced_background_color__expr = misc_data_->forced_colors_data_->internal_forced_background_color_;
  const auto& o_internal_forced_background_color__expr = o.misc_data_->forced_colors_data_->internal_forced_background_color_;
  if (!(internal_forced_background_color__expr == o_internal_forced_background_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_forced_background_color_;
    d.actual = DebugStringForField(internal_forced_background_color__expr);
    d.correct = DebugStringForField(o_internal_forced_background_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_forced_border_color__expr = misc_data_->forced_colors_data_->internal_forced_border_color_;
  const auto& o_internal_forced_border_color__expr = o.misc_data_->forced_colors_data_->internal_forced_border_color_;
  if (!(internal_forced_border_color__expr == o_internal_forced_border_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_forced_border_color_;
    d.actual = DebugStringForField(internal_forced_border_color__expr);
    d.correct = DebugStringForField(o_internal_forced_border_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_forced_outline_color__expr = misc_data_->forced_colors_data_->internal_forced_outline_color_;
  const auto& o_internal_forced_outline_color__expr = o.misc_data_->forced_colors_data_->internal_forced_outline_color_;
  if (!(internal_forced_outline_color__expr == o_internal_forced_outline_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_forced_outline_color_;
    d.actual = DebugStringForField(internal_forced_outline_color__expr);
    d.correct = DebugStringForField(o_internal_forced_outline_color__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc4
  const auto& page__expr = misc_data_->misc_4_data_->page_;
  const auto& o_page__expr = o.misc_data_->misc_4_data_->page_;
  if (!(page__expr == o_page__expr)) {
    DebugDiff d;
    d.field = DebugField::page_;
    d.actual = DebugStringForField(page__expr);
    d.correct = DebugStringForField(o_page__expr);
    diff.push_back(std::move(d));
  }
  const auto& object_view_box__expr = misc_data_->misc_4_data_->object_view_box_;
  const auto& o_object_view_box__expr = o.misc_data_->misc_4_data_->object_view_box_;
  if (!(base::ValuesEquivalent(object_view_box__expr, o_object_view_box__expr))) {
    DebugDiff d;
    d.field = DebugField::object_view_box_;
    d.actual = DebugStringForField(object_view_box__expr);
    d.correct = DebugStringForField(o_object_view_box__expr);
    diff.push_back(std::move(d));
  }
  const auto& offset_path__expr = misc_data_->misc_4_data_->offset_path_;
  const auto& o_offset_path__expr = o.misc_data_->misc_4_data_->offset_path_;
  if (!(base::ValuesEquivalent(offset_path__expr, o_offset_path__expr))) {
    DebugDiff d;
    d.field = DebugField::offset_path_;
    d.actual = DebugStringForField(offset_path__expr);
    d.correct = DebugStringForField(o_offset_path__expr);
    diff.push_back(std::move(d));
  }
  const auto& position_try_fallbacks__expr = misc_data_->misc_4_data_->position_try_fallbacks_;
  const auto& o_position_try_fallbacks__expr = o.misc_data_->misc_4_data_->position_try_fallbacks_;
  if (!(base::ValuesEquivalent(position_try_fallbacks__expr, o_position_try_fallbacks__expr))) {
    DebugDiff d;
    d.field = DebugField::position_try_fallbacks_;
    d.actual = DebugStringForField(position_try_fallbacks__expr);
    d.correct = DebugStringForField(o_position_try_fallbacks__expr);
    diff.push_back(std::move(d));
  }
  const auto& rotate__expr = misc_data_->misc_4_data_->rotate_;
  const auto& o_rotate__expr = o.misc_data_->misc_4_data_->rotate_;
  if (!(base::ValuesEquivalent(rotate__expr, o_rotate__expr))) {
    DebugDiff d;
    d.field = DebugField::rotate_;
    d.actual = DebugStringForField(rotate__expr);
    d.correct = DebugStringForField(o_rotate__expr);
    diff.push_back(std::move(d));
  }
  const auto& offset_rotate__expr = misc_data_->misc_4_data_->offset_rotate_;
  const auto& o_offset_rotate__expr = o.misc_data_->misc_4_data_->offset_rotate_;
  if (!(offset_rotate__expr == o_offset_rotate__expr)) {
    DebugDiff d;
    d.field = DebugField::offset_rotate_;
    d.actual = DebugStringForField(offset_rotate__expr);
    d.correct = DebugStringForField(o_offset_rotate__expr);
    diff.push_back(std::move(d));
  }
  const auto& offset_anchor__expr = misc_data_->misc_4_data_->offset_anchor_;
  const auto& o_offset_anchor__expr = o.misc_data_->misc_4_data_->offset_anchor_;
  if (!(offset_anchor__expr == o_offset_anchor__expr)) {
    DebugDiff d;
    d.field = DebugField::offset_anchor_;
    d.actual = DebugStringForField(offset_anchor__expr);
    d.correct = DebugStringForField(o_offset_anchor__expr);
    diff.push_back(std::move(d));
  }
  const auto& offset_position__expr = misc_data_->misc_4_data_->offset_position_;
  const auto& o_offset_position__expr = o.misc_data_->misc_4_data_->offset_position_;
  if (!(offset_position__expr == o_offset_position__expr)) {
    DebugDiff d;
    d.field = DebugField::offset_position_;
    d.actual = DebugStringForField(offset_position__expr);
    d.correct = DebugStringForField(o_offset_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& perspective_origin__expr = misc_data_->misc_4_data_->perspective_origin_;
  const auto& o_perspective_origin__expr = o.misc_data_->misc_4_data_->perspective_origin_;
  if (!(perspective_origin__expr == o_perspective_origin__expr)) {
    DebugDiff d;
    d.field = DebugField::perspective_origin_;
    d.actual = DebugStringForField(perspective_origin__expr);
    d.correct = DebugStringForField(o_perspective_origin__expr);
    diff.push_back(std::move(d));
  }
  const auto& offset_distance__expr = misc_data_->misc_4_data_->offset_distance_;
  const auto& o_offset_distance__expr = o.misc_data_->misc_4_data_->offset_distance_;
  if (!(offset_distance__expr == o_offset_distance__expr)) {
    DebugDiff d;
    d.field = DebugField::offset_distance_;
    d.actual = DebugStringForField(offset_distance__expr);
    d.correct = DebugStringForField(o_offset_distance__expr);
    diff.push_back(std::move(d));
  }
  const auto& perspective__expr = misc_data_->misc_4_data_->perspective_;
  const auto& o_perspective__expr = o.misc_data_->misc_4_data_->perspective_;
  if (!(perspective__expr == o_perspective__expr)) {
    DebugDiff d;
    d.field = DebugField::perspective_;
    d.actual = DebugStringForField(perspective__expr);
    d.correct = DebugStringForField(o_perspective__expr);
    diff.push_back(std::move(d));
  }
  const auto& outline_color__expr = misc_data_->misc_4_data_->outline_color_;
  const auto& o_outline_color__expr = o.misc_data_->misc_4_data_->outline_color_;
  if (!(outline_color__expr == o_outline_color__expr)) {
    DebugDiff d;
    d.field = DebugField::outline_color_;
    d.actual = DebugStringForField(outline_color__expr);
    d.correct = DebugStringForField(o_outline_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& order__expr = misc_data_->misc_4_data_->order_;
  const auto& o_order__expr = o.misc_data_->misc_4_data_->order_;
  if (!(order__expr == o_order__expr)) {
    DebugDiff d;
    d.field = DebugField::order_;
    d.actual = DebugStringForField(order__expr);
    d.correct = DebugStringForField(o_order__expr);
    diff.push_back(std::move(d));
  }
  const auto& outline_offset__expr = misc_data_->misc_4_data_->outline_offset_;
  const auto& o_outline_offset__expr = o.misc_data_->misc_4_data_->outline_offset_;
  if (!(outline_offset__expr == o_outline_offset__expr)) {
    DebugDiff d;
    d.field = DebugField::outline_offset_;
    d.actual = DebugStringForField(outline_offset__expr);
    d.correct = DebugStringForField(o_outline_offset__expr);
    diff.push_back(std::move(d));
  }
  const auto& outline_width__expr = misc_data_->misc_4_data_->outline_width_;
  const auto& o_outline_width__expr = o.misc_data_->misc_4_data_->outline_width_;
  if (!(outline_width__expr == o_outline_width__expr)) {
    DebugDiff d;
    d.field = DebugField::outline_width_;
    d.actual = DebugStringForField(outline_width__expr);
    d.correct = DebugStringForField(o_outline_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& reading_order__expr = misc_data_->misc_4_data_->reading_order_;
  const auto& o_reading_order__expr = o.misc_data_->misc_4_data_->reading_order_;
  if (!(reading_order__expr == o_reading_order__expr)) {
    DebugDiff d;
    d.field = DebugField::reading_order_;
    d.actual = DebugStringForField(reading_order__expr);
    d.correct = DebugStringForField(o_reading_order__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc5
  const auto& row_rule_color__expr = misc_data_->misc_5_data_->row_rule_color_;
  const auto& o_row_rule_color__expr = o.misc_data_->misc_5_data_->row_rule_color_;
  if (!(row_rule_color__expr == o_row_rule_color__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_color_;
    d.actual = DebugStringForField(row_rule_color__expr);
    d.correct = DebugStringForField(o_row_rule_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_width__expr = misc_data_->misc_5_data_->row_rule_width_;
  const auto& o_row_rule_width__expr = o.misc_data_->misc_5_data_->row_rule_width_;
  if (!(row_rule_width__expr == o_row_rule_width__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_width_;
    d.actual = DebugStringForField(row_rule_width__expr);
    d.correct = DebugStringForField(o_row_rule_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_style__expr = misc_data_->misc_5_data_->row_rule_style_;
  const auto& o_row_rule_style__expr = o.misc_data_->misc_5_data_->row_rule_style_;
  if (!(row_rule_style__expr == o_row_rule_style__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_style_;
    d.actual = DebugStringForField(row_rule_style__expr);
    d.correct = DebugStringForField(o_row_rule_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& scale__expr = misc_data_->misc_5_data_->scale_;
  const auto& o_scale__expr = o.misc_data_->misc_5_data_->scale_;
  if (!(base::ValuesEquivalent(scale__expr, o_scale__expr))) {
    DebugDiff d;
    d.field = DebugField::scale_;
    d.actual = DebugStringForField(scale__expr);
    d.correct = DebugStringForField(o_scale__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_marker_group__expr = misc_data_->misc_5_data_->scroll_marker_group_;
  const auto& o_scroll_marker_group__expr = o.misc_data_->misc_5_data_->scroll_marker_group_;
  if (!(base::ValuesEquivalent(scroll_marker_group__expr, o_scroll_marker_group__expr))) {
    DebugDiff d;
    d.field = DebugField::scroll_marker_group_;
    d.actual = DebugStringForField(scroll_marker_group__expr);
    d.correct = DebugStringForField(o_scroll_marker_group__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_gap__expr = misc_data_->misc_5_data_->row_gap_;
  const auto& o_row_gap__expr = o.misc_data_->misc_5_data_->row_gap_;
  if (!(row_gap__expr == o_row_gap__expr)) {
    DebugDiff d;
    d.field = DebugField::row_gap_;
    d.actual = DebugStringForField(row_gap__expr);
    d.correct = DebugStringForField(o_row_gap__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_inset_cap_end__expr = misc_data_->misc_5_data_->row_rule_inset_cap_end_;
  const auto& o_row_rule_inset_cap_end__expr = o.misc_data_->misc_5_data_->row_rule_inset_cap_end_;
  if (!(row_rule_inset_cap_end__expr == o_row_rule_inset_cap_end__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_inset_cap_end_;
    d.actual = DebugStringForField(row_rule_inset_cap_end__expr);
    d.correct = DebugStringForField(o_row_rule_inset_cap_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_inset_cap_start__expr = misc_data_->misc_5_data_->row_rule_inset_cap_start_;
  const auto& o_row_rule_inset_cap_start__expr = o.misc_data_->misc_5_data_->row_rule_inset_cap_start_;
  if (!(row_rule_inset_cap_start__expr == o_row_rule_inset_cap_start__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_inset_cap_start_;
    d.actual = DebugStringForField(row_rule_inset_cap_start__expr);
    d.correct = DebugStringForField(o_row_rule_inset_cap_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_inset_junction_end__expr = misc_data_->misc_5_data_->row_rule_inset_junction_end_;
  const auto& o_row_rule_inset_junction_end__expr = o.misc_data_->misc_5_data_->row_rule_inset_junction_end_;
  if (!(row_rule_inset_junction_end__expr == o_row_rule_inset_junction_end__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_inset_junction_end_;
    d.actual = DebugStringForField(row_rule_inset_junction_end__expr);
    d.correct = DebugStringForField(o_row_rule_inset_junction_end__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_inset_junction_start__expr = misc_data_->misc_5_data_->row_rule_inset_junction_start_;
  const auto& o_row_rule_inset_junction_start__expr = o.misc_data_->misc_5_data_->row_rule_inset_junction_start_;
  if (!(row_rule_inset_junction_start__expr == o_row_rule_inset_junction_start__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_inset_junction_start_;
    d.actual = DebugStringForField(row_rule_inset_junction_start__expr);
    d.correct = DebugStringForField(o_row_rule_inset_junction_start__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_padding_bottom__expr = misc_data_->misc_5_data_->scroll_padding_bottom_;
  const auto& o_scroll_padding_bottom__expr = o.misc_data_->misc_5_data_->scroll_padding_bottom_;
  if (!(scroll_padding_bottom__expr == o_scroll_padding_bottom__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_padding_bottom_;
    d.actual = DebugStringForField(scroll_padding_bottom__expr);
    d.correct = DebugStringForField(o_scroll_padding_bottom__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_padding_left__expr = misc_data_->misc_5_data_->scroll_padding_left_;
  const auto& o_scroll_padding_left__expr = o.misc_data_->misc_5_data_->scroll_padding_left_;
  if (!(scroll_padding_left__expr == o_scroll_padding_left__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_padding_left_;
    d.actual = DebugStringForField(scroll_padding_left__expr);
    d.correct = DebugStringForField(o_scroll_padding_left__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_margin_bottom__expr = misc_data_->misc_5_data_->scroll_margin_bottom_;
  const auto& o_scroll_margin_bottom__expr = o.misc_data_->misc_5_data_->scroll_margin_bottom_;
  if (!(scroll_margin_bottom__expr == o_scroll_margin_bottom__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_margin_bottom_;
    d.actual = DebugStringForField(scroll_margin_bottom__expr);
    d.correct = DebugStringForField(o_scroll_margin_bottom__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_margin_left__expr = misc_data_->misc_5_data_->scroll_margin_left_;
  const auto& o_scroll_margin_left__expr = o.misc_data_->misc_5_data_->scroll_margin_left_;
  if (!(scroll_margin_left__expr == o_scroll_margin_left__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_margin_left_;
    d.actual = DebugStringForField(scroll_margin_left__expr);
    d.correct = DebugStringForField(o_scroll_margin_left__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_margin_right__expr = misc_data_->misc_5_data_->scroll_margin_right_;
  const auto& o_scroll_margin_right__expr = o.misc_data_->misc_5_data_->scroll_margin_right_;
  if (!(scroll_margin_right__expr == o_scroll_margin_right__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_margin_right_;
    d.actual = DebugStringForField(scroll_margin_right__expr);
    d.correct = DebugStringForField(o_scroll_margin_right__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_margin_top__expr = misc_data_->misc_5_data_->scroll_margin_top_;
  const auto& o_scroll_margin_top__expr = o.misc_data_->misc_5_data_->scroll_margin_top_;
  if (!(scroll_margin_top__expr == o_scroll_margin_top__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_margin_top_;
    d.actual = DebugStringForField(scroll_margin_top__expr);
    d.correct = DebugStringForField(o_scroll_margin_top__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc6
  const auto& text_decoration_thickness__expr = misc_data_->misc_6_data_->text_decoration_thickness_;
  const auto& o_text_decoration_thickness__expr = o.misc_data_->misc_6_data_->text_decoration_thickness_;
  if (!(text_decoration_thickness__expr == o_text_decoration_thickness__expr)) {
    DebugDiff d;
    d.field = DebugField::text_decoration_thickness_;
    d.actual = DebugStringForField(text_decoration_thickness__expr);
    d.correct = DebugStringForField(o_text_decoration_thickness__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_overflow__expr = misc_data_->misc_6_data_->text_overflow_;
  const auto& o_text_overflow__expr = o.misc_data_->misc_6_data_->text_overflow_;
  if (!(text_overflow__expr == o_text_overflow__expr)) {
    DebugDiff d;
    d.field = DebugField::text_overflow_;
    d.actual = DebugStringForField(text_overflow__expr);
    d.correct = DebugStringForField(o_text_overflow__expr);
    diff.push_back(std::move(d));
  }
  const auto& trigger_scope__expr = misc_data_->misc_6_data_->trigger_scope_;
  const auto& o_trigger_scope__expr = o.misc_data_->misc_6_data_->trigger_scope_;
  if (!(trigger_scope__expr == o_trigger_scope__expr)) {
    DebugDiff d;
    d.field = DebugField::trigger_scope_;
    d.actual = DebugStringForField(trigger_scope__expr);
    d.correct = DebugStringForField(o_trigger_scope__expr);
    diff.push_back(std::move(d));
  }
  const auto& shape_outside__expr = misc_data_->misc_6_data_->shape_outside_;
  const auto& o_shape_outside__expr = o.misc_data_->misc_6_data_->shape_outside_;
  if (!(base::ValuesEquivalent(shape_outside__expr, o_shape_outside__expr))) {
    DebugDiff d;
    d.field = DebugField::shape_outside_;
    d.actual = DebugStringForField(shape_outside__expr);
    d.correct = DebugStringForField(o_shape_outside__expr);
    diff.push_back(std::move(d));
  }
  const auto& timeline_trigger_name__expr = misc_data_->misc_6_data_->timeline_trigger_name_;
  const auto& o_timeline_trigger_name__expr = o.misc_data_->misc_6_data_->timeline_trigger_name_;
  if (!(base::ValuesEquivalent(timeline_trigger_name__expr, o_timeline_trigger_name__expr))) {
    DebugDiff d;
    d.field = DebugField::timeline_trigger_name_;
    d.actual = DebugStringForField(timeline_trigger_name__expr);
    d.correct = DebugStringForField(o_timeline_trigger_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& translate__expr = misc_data_->misc_6_data_->translate_;
  const auto& o_translate__expr = o.misc_data_->misc_6_data_->translate_;
  if (!(base::ValuesEquivalent(translate__expr, o_translate__expr))) {
    DebugDiff d;
    d.field = DebugField::translate_;
    d.actual = DebugStringForField(translate__expr);
    d.correct = DebugStringForField(o_translate__expr);
    diff.push_back(std::move(d));
  }
  const auto& view_transition_class__expr = misc_data_->misc_6_data_->view_transition_class_;
  const auto& o_view_transition_class__expr = o.misc_data_->misc_6_data_->view_transition_class_;
  if (!(base::ValuesEquivalent(view_transition_class__expr, o_view_transition_class__expr))) {
    DebugDiff d;
    d.field = DebugField::view_transition_class_;
    d.actual = DebugStringForField(view_transition_class__expr);
    d.correct = DebugStringForField(o_view_transition_class__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_padding_right__expr = misc_data_->misc_6_data_->scroll_padding_right_;
  const auto& o_scroll_padding_right__expr = o.misc_data_->misc_6_data_->scroll_padding_right_;
  if (!(scroll_padding_right__expr == o_scroll_padding_right__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_padding_right_;
    d.actual = DebugStringForField(scroll_padding_right__expr);
    d.correct = DebugStringForField(o_scroll_padding_right__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_padding_top__expr = misc_data_->misc_6_data_->scroll_padding_top_;
  const auto& o_scroll_padding_top__expr = o.misc_data_->misc_6_data_->scroll_padding_top_;
  if (!(scroll_padding_top__expr == o_scroll_padding_top__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_padding_top_;
    d.actual = DebugStringForField(scroll_padding_top__expr);
    d.correct = DebugStringForField(o_scroll_padding_top__expr);
    diff.push_back(std::move(d));
  }
  const auto& shape_margin__expr = misc_data_->misc_6_data_->shape_margin_;
  const auto& o_shape_margin__expr = o.misc_data_->misc_6_data_->shape_margin_;
  if (!(shape_margin__expr == o_shape_margin__expr)) {
    DebugDiff d;
    d.field = DebugField::shape_margin_;
    d.actual = DebugStringForField(shape_margin__expr);
    d.correct = DebugStringForField(o_shape_margin__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_fit__expr = misc_data_->misc_6_data_->text_fit_;
  const auto& o_text_fit__expr = o.misc_data_->misc_6_data_->text_fit_;
  if (!(text_fit__expr == o_text_fit__expr)) {
    DebugDiff d;
    d.field = DebugField::text_fit_;
    d.actual = DebugStringForField(text_fit__expr);
    d.correct = DebugStringForField(o_text_fit__expr);
    diff.push_back(std::move(d));
  }
  const auto& shape_image_threshold__expr = misc_data_->misc_6_data_->shape_image_threshold_;
  const auto& o_shape_image_threshold__expr = o.misc_data_->misc_6_data_->shape_image_threshold_;
  if (!(shape_image_threshold__expr == o_shape_image_threshold__expr)) {
    DebugDiff d;
    d.field = DebugField::shape_image_threshold_;
    d.actual = DebugStringForField(shape_image_threshold__expr);
    d.correct = DebugStringForField(o_shape_image_threshold__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_snap_type__expr = misc_data_->misc_6_data_->scroll_snap_type_;
  const auto& o_scroll_snap_type__expr = o.misc_data_->misc_6_data_->scroll_snap_type_;
  if (!(scroll_snap_type__expr == o_scroll_snap_type__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_snap_type_;
    d.actual = DebugStringForField(scroll_snap_type__expr);
    d.correct = DebugStringForField(o_scroll_snap_type__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_snap_align__expr = misc_data_->misc_6_data_->scroll_snap_align_;
  const auto& o_scroll_snap_align__expr = o.misc_data_->misc_6_data_->scroll_snap_align_;
  if (!(scroll_snap_align__expr == o_scroll_snap_align__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_snap_align_;
    d.actual = DebugStringForField(scroll_snap_align__expr);
    d.correct = DebugStringForField(o_scroll_snap_align__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_decoration_color__expr = misc_data_->misc_6_data_->text_decoration_color_;
  const auto& o_text_decoration_color__expr = o.misc_data_->misc_6_data_->text_decoration_color_;
  if (!(text_decoration_color__expr == o_text_decoration_color__expr)) {
    DebugDiff d;
    d.field = DebugField::text_decoration_color_;
    d.actual = DebugStringForField(text_decoration_color__expr);
    d.correct = DebugStringForField(o_text_decoration_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& touch_action__expr = misc_data_->misc_6_data_->touch_action_;
  const auto& o_touch_action__expr = o.misc_data_->misc_6_data_->touch_action_;
  if (!(touch_action__expr == o_touch_action__expr)) {
    DebugDiff d;
    d.field = DebugField::touch_action_;
    d.actual = DebugStringForField(touch_action__expr);
    d.correct = DebugStringForField(o_touch_action__expr);
    diff.push_back(std::move(d));
  }

    // Group: timeline
  const auto& scroll_timeline_name__expr = misc_data_->timeline_data_->scroll_timeline_name_;
  const auto& o_scroll_timeline_name__expr = o.misc_data_->timeline_data_->scroll_timeline_name_;
  if (!(scroll_timeline_name__expr == o_scroll_timeline_name__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_timeline_name_;
    d.actual = DebugStringForField(scroll_timeline_name__expr);
    d.correct = DebugStringForField(o_scroll_timeline_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& view_timeline_name__expr = misc_data_->timeline_data_->view_timeline_name_;
  const auto& o_view_timeline_name__expr = o.misc_data_->timeline_data_->view_timeline_name_;
  if (!(view_timeline_name__expr == o_view_timeline_name__expr)) {
    DebugDiff d;
    d.field = DebugField::view_timeline_name_;
    d.actual = DebugStringForField(view_timeline_name__expr);
    d.correct = DebugStringForField(o_view_timeline_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_timeline_axis__expr = misc_data_->timeline_data_->scroll_timeline_axis_;
  const auto& o_scroll_timeline_axis__expr = o.misc_data_->timeline_data_->scroll_timeline_axis_;
  if (!(scroll_timeline_axis__expr == o_scroll_timeline_axis__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_timeline_axis_;
    d.actual = DebugStringForField(scroll_timeline_axis__expr);
    d.correct = DebugStringForField(o_scroll_timeline_axis__expr);
    diff.push_back(std::move(d));
  }
  const auto& view_timeline_axis__expr = misc_data_->timeline_data_->view_timeline_axis_;
  const auto& o_view_timeline_axis__expr = o.misc_data_->timeline_data_->view_timeline_axis_;
  if (!(view_timeline_axis__expr == o_view_timeline_axis__expr)) {
    DebugDiff d;
    d.field = DebugField::view_timeline_axis_;
    d.actual = DebugStringForField(view_timeline_axis__expr);
    d.correct = DebugStringForField(o_view_timeline_axis__expr);
    diff.push_back(std::move(d));
  }
  const auto& view_timeline_inset__expr = misc_data_->timeline_data_->view_timeline_inset_;
  const auto& o_view_timeline_inset__expr = o.misc_data_->timeline_data_->view_timeline_inset_;
  if (!(view_timeline_inset__expr == o_view_timeline_inset__expr)) {
    DebugDiff d;
    d.field = DebugField::view_timeline_inset_;
    d.actual = DebugStringForField(view_timeline_inset__expr);
    d.correct = DebugStringForField(o_view_timeline_inset__expr);
    diff.push_back(std::move(d));
  }
  const auto& timeline_scope__expr = misc_data_->timeline_data_->timeline_scope_;
  const auto& o_timeline_scope__expr = o.misc_data_->timeline_data_->timeline_scope_;
  if (!(timeline_scope__expr == o_timeline_scope__expr)) {
    DebugDiff d;
    d.field = DebugField::timeline_scope_;
    d.actual = DebugStringForField(timeline_scope__expr);
    d.correct = DebugStringForField(o_timeline_scope__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc7
  const auto& view_transition_group__expr = misc_data_->misc_7_data_->view_transition_group_;
  const auto& o_view_transition_group__expr = o.misc_data_->misc_7_data_->view_transition_group_;
  if (!(view_transition_group__expr == o_view_transition_group__expr)) {
    DebugDiff d;
    d.field = DebugField::view_transition_group_;
    d.actual = DebugStringForField(view_transition_group__expr);
    d.correct = DebugStringForField(o_view_transition_group__expr);
    diff.push_back(std::move(d));
  }
  const auto& display_layout_custom_name__expr = misc_data_->misc_7_data_->display_layout_custom_name_;
  const auto& o_display_layout_custom_name__expr = o.misc_data_->misc_7_data_->display_layout_custom_name_;
  if (!(display_layout_custom_name__expr == o_display_layout_custom_name__expr)) {
    DebugDiff d;
    d.field = DebugField::display_layout_custom_name_;
    d.actual = DebugStringForField(display_layout_custom_name__expr);
    d.correct = DebugStringForField(o_display_layout_custom_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& display_layout_custom_parent_name__expr = misc_data_->misc_7_data_->display_layout_custom_parent_name_;
  const auto& o_display_layout_custom_parent_name__expr = o.misc_data_->misc_7_data_->display_layout_custom_parent_name_;
  if (!(display_layout_custom_parent_name__expr == o_display_layout_custom_parent_name__expr)) {
    DebugDiff d;
    d.field = DebugField::display_layout_custom_parent_name_;
    d.actual = DebugStringForField(display_layout_custom_parent_name__expr);
    d.correct = DebugStringForField(o_display_layout_custom_parent_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& custom_highlight_names__expr = misc_data_->misc_7_data_->custom_highlight_names_;
  const auto& o_custom_highlight_names__expr = o.misc_data_->misc_7_data_->custom_highlight_names_;
  if (!(base::ValuesEquivalent(custom_highlight_names__expr, o_custom_highlight_names__expr))) {
    DebugDiff d;
    d.field = DebugField::custom_highlight_names_;
    d.actual = DebugStringForField(custom_highlight_names__expr);
    d.correct = DebugStringForField(o_custom_highlight_names__expr);
    diff.push_back(std::move(d));
  }
  const auto& counter_directives__expr = misc_data_->misc_7_data_->counter_directives_;
  const auto& o_counter_directives__expr = o.misc_data_->misc_7_data_->counter_directives_;
  if (!(base::ValuesEquivalent(counter_directives__expr, o_counter_directives__expr))) {
    DebugDiff d;
    d.field = DebugField::counter_directives_;
    d.actual = DebugStringForField(counter_directives__expr);
    d.correct = DebugStringForField(o_counter_directives__expr);
    diff.push_back(std::move(d));
  }
  const auto& mask__expr = misc_data_->misc_7_data_->mask_;
  const auto& o_mask__expr = o.misc_data_->misc_7_data_->mask_;
  if (!(mask__expr == o_mask__expr)) {
    DebugDiff d;
    d.field = DebugField::mask_;
    d.actual = DebugStringForField(mask__expr);
    d.correct = DebugStringForField(o_mask__expr);
    diff.push_back(std::move(d));
  }
  const auto& mask_box_image__expr = misc_data_->misc_7_data_->mask_box_image_;
  const auto& o_mask_box_image__expr = o.misc_data_->misc_7_data_->mask_box_image_;
  if (!(mask_box_image__expr == o_mask_box_image__expr)) {
    DebugDiff d;
    d.field = DebugField::mask_box_image_;
    d.actual = DebugStringForField(mask_box_image__expr);
    d.correct = DebugStringForField(o_mask_box_image__expr);
    diff.push_back(std::move(d));
  }
  const auto& unconditional_scrollbar_size__expr = misc_data_->misc_7_data_->unconditional_scrollbar_size_;
  const auto& o_unconditional_scrollbar_size__expr = o.misc_data_->misc_7_data_->unconditional_scrollbar_size_;
  if (!(unconditional_scrollbar_size__expr == o_unconditional_scrollbar_size__expr)) {
    DebugDiff d;
    d.field = DebugField::unconditional_scrollbar_size_;
    d.actual = DebugStringForField(unconditional_scrollbar_size__expr);
    d.correct = DebugStringForField(o_unconditional_scrollbar_size__expr);
    diff.push_back(std::move(d));
  }
  const auto& view_transition_name__expr = misc_data_->misc_7_data_->view_transition_name_;
  const auto& o_view_transition_name__expr = o.misc_data_->misc_7_data_->view_transition_name_;
  if (!(base::ValuesEquivalent(view_transition_name__expr, o_view_transition_name__expr))) {
    DebugDiff d;
    d.field = DebugField::view_transition_name_;
    d.actual = DebugStringForField(view_transition_name__expr);
    d.correct = DebugStringForField(o_view_transition_name__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_reflect__expr = misc_data_->misc_7_data_->box_reflect_;
  const auto& o_box_reflect__expr = o.misc_data_->misc_7_data_->box_reflect_;
  if (!(base::ValuesEquivalent(box_reflect__expr, o_box_reflect__expr))) {
    DebugDiff d;
    d.field = DebugField::box_reflect_;
    d.actual = DebugStringForField(box_reflect__expr);
    d.correct = DebugStringForField(o_box_reflect__expr);
    diff.push_back(std::move(d));
  }
  const auto& animations__expr = misc_data_->misc_7_data_->animations_;
  const auto& o_animations__expr = o.misc_data_->misc_7_data_->animations_;
  if (!(base::ValuesEquivalent(animations__expr, o_animations__expr))) {
    DebugDiff d;
    d.field = DebugField::animations_;
    d.actual = DebugStringForField(animations__expr);
    d.correct = DebugStringForField(o_animations__expr);
    diff.push_back(std::move(d));
  }
  const auto& transitions__expr = misc_data_->misc_7_data_->transitions_;
  const auto& o_transitions__expr = o.misc_data_->misc_7_data_->transitions_;
  if (!(base::ValuesEquivalent(transitions__expr, o_transitions__expr))) {
    DebugDiff d;
    d.field = DebugField::transitions_;
    d.actual = DebugStringForField(transitions__expr);
    d.correct = DebugStringForField(o_transitions__expr);
    diff.push_back(std::move(d));
  }
  const auto& page_size__expr = misc_data_->misc_7_data_->page_size_;
  const auto& o_page_size__expr = o.misc_data_->misc_7_data_->page_size_;
  if (!(page_size__expr == o_page_size__expr)) {
    DebugDiff d;
    d.field = DebugField::page_size_;
    d.actual = DebugStringForField(page_size__expr);
    d.correct = DebugStringForField(o_page_size__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_flex__expr = misc_data_->misc_7_data_->box_flex_;
  const auto& o_box_flex__expr = o.misc_data_->misc_7_data_->box_flex_;
  if (!(box_flex__expr == o_box_flex__expr)) {
    DebugDiff d;
    d.field = DebugField::box_flex_;
    d.actual = DebugStringForField(box_flex__expr);
    d.correct = DebugStringForField(o_box_flex__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_ordinal_group__expr = misc_data_->misc_7_data_->box_ordinal_group_;
  const auto& o_box_ordinal_group__expr = o.misc_data_->misc_7_data_->box_ordinal_group_;
  if (!(box_ordinal_group__expr == o_box_ordinal_group__expr)) {
    DebugDiff d;
    d.field = DebugField::box_ordinal_group_;
    d.actual = DebugStringForField(box_ordinal_group__expr);
    d.correct = DebugStringForField(o_box_ordinal_group__expr);
    diff.push_back(std::move(d));
  }
  const auto& webkit_line_clamp__expr = misc_data_->misc_7_data_->webkit_line_clamp_;
  const auto& o_webkit_line_clamp__expr = o.misc_data_->misc_7_data_->webkit_line_clamp_;
  if (!(webkit_line_clamp__expr == o_webkit_line_clamp__expr)) {
    DebugDiff d;
    d.field = DebugField::webkit_line_clamp_;
    d.actual = DebugStringForField(webkit_line_clamp__expr);
    d.correct = DebugStringForField(o_webkit_line_clamp__expr);
    diff.push_back(std::move(d));
  }

    // Group: misc8
  const auto& callback_selectors__expr = misc_data_->misc_8_data_->callback_selectors_;
  const auto& o_callback_selectors__expr = o.misc_data_->misc_8_data_->callback_selectors_;
  if (!(callback_selectors__expr == o_callback_selectors__expr)) {
    DebugDiff d;
    d.field = DebugField::callback_selectors_;
    d.actual = DebugStringForField(callback_selectors__expr);
    d.correct = DebugStringForField(o_callback_selectors__expr);
    diff.push_back(std::move(d));
  }
  const auto& non_inherited_variables__expr = misc_data_->misc_8_data_->non_inherited_variables_;
  const auto& o_non_inherited_variables__expr = o.misc_data_->misc_8_data_->non_inherited_variables_;
  if (!(non_inherited_variables__expr == o_non_inherited_variables__expr)) {
    DebugDiff d;
    d.field = DebugField::non_inherited_variables_;
    d.actual = DebugStringForField(non_inherited_variables__expr);
    d.correct = DebugStringForField(o_non_inherited_variables__expr);
    diff.push_back(std::move(d));
  }
  const auto& document_rules_selectors__expr = misc_data_->misc_8_data_->document_rules_selectors_;
  const auto& o_document_rules_selectors__expr = o.misc_data_->misc_8_data_->document_rules_selectors_;
  if (!(base::ValuesEquivalent(document_rules_selectors__expr, o_document_rules_selectors__expr))) {
    DebugDiff d;
    d.field = DebugField::document_rules_selectors_;
    d.actual = DebugStringForField(document_rules_selectors__expr);
    d.correct = DebugStringForField(o_document_rules_selectors__expr);
    diff.push_back(std::move(d));
  }

    // Group: math
  const auto& math_baseline__expr = misc_data_->math_data_->math_baseline_;
  const auto& o_math_baseline__expr = o.misc_data_->math_data_->math_baseline_;
  if (!(math_baseline__expr == o_math_baseline__expr)) {
    DebugDiff d;
    d.field = DebugField::math_baseline_;
    d.actual = DebugStringForField(math_baseline__expr);
    d.correct = DebugStringForField(o_math_baseline__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_fraction_bar_thickness__expr = misc_data_->math_data_->math_fraction_bar_thickness_;
  const auto& o_math_fraction_bar_thickness__expr = o.misc_data_->math_data_->math_fraction_bar_thickness_;
  if (!(math_fraction_bar_thickness__expr == o_math_fraction_bar_thickness__expr)) {
    DebugDiff d;
    d.field = DebugField::math_fraction_bar_thickness_;
    d.actual = DebugStringForField(math_fraction_bar_thickness__expr);
    d.correct = DebugStringForField(o_math_fraction_bar_thickness__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_l_space__expr = misc_data_->math_data_->math_l_space_;
  const auto& o_math_l_space__expr = o.misc_data_->math_data_->math_l_space_;
  if (!(math_l_space__expr == o_math_l_space__expr)) {
    DebugDiff d;
    d.field = DebugField::math_l_space_;
    d.actual = DebugStringForField(math_l_space__expr);
    d.correct = DebugStringForField(o_math_l_space__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_r_space__expr = misc_data_->math_data_->math_r_space_;
  const auto& o_math_r_space__expr = o.misc_data_->math_data_->math_r_space_;
  if (!(math_r_space__expr == o_math_r_space__expr)) {
    DebugDiff d;
    d.field = DebugField::math_r_space_;
    d.actual = DebugStringForField(math_r_space__expr);
    d.correct = DebugStringForField(o_math_r_space__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_padded_v_offset__expr = misc_data_->math_data_->math_padded_v_offset_;
  const auto& o_math_padded_v_offset__expr = o.misc_data_->math_data_->math_padded_v_offset_;
  if (!(math_padded_v_offset__expr == o_math_padded_v_offset__expr)) {
    DebugDiff d;
    d.field = DebugField::math_padded_v_offset_;
    d.actual = DebugStringForField(math_padded_v_offset__expr);
    d.correct = DebugStringForField(o_math_padded_v_offset__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_padded_depth__expr = misc_data_->math_data_->math_padded_depth_;
  const auto& o_math_padded_depth__expr = o.misc_data_->math_data_->math_padded_depth_;
  if (!(math_padded_depth__expr == o_math_padded_depth__expr)) {
    DebugDiff d;
    d.field = DebugField::math_padded_depth_;
    d.actual = DebugStringForField(math_padded_depth__expr);
    d.correct = DebugStringForField(o_math_padded_depth__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_min_size__expr = misc_data_->math_data_->math_min_size_;
  const auto& o_math_min_size__expr = o.misc_data_->math_data_->math_min_size_;
  if (!(math_min_size__expr == o_math_min_size__expr)) {
    DebugDiff d;
    d.field = DebugField::math_min_size_;
    d.actual = DebugStringForField(math_min_size__expr);
    d.correct = DebugStringForField(o_math_min_size__expr);
    diff.push_back(std::move(d));
  }
  const auto& math_max_size__expr = misc_data_->math_data_->math_max_size_;
  const auto& o_math_max_size__expr = o.misc_data_->math_data_->math_max_size_;
  if (!(math_max_size__expr == o_math_max_size__expr)) {
    DebugDiff d;
    d.field = DebugField::math_max_size_;
    d.actual = DebugStringForField(math_max_size__expr);
    d.correct = DebugStringForField(o_math_max_size__expr);
    diff.push_back(std::move(d));
  }

  // Group: misc
  const auto& will_change__expr = misc_data_->will_change_;
  const auto& o_will_change__expr = o.misc_data_->will_change_;
  if (!(base::ValuesEquivalent(will_change__expr, o_will_change__expr))) {
    DebugDiff d;
    d.field = DebugField::will_change_;
    d.actual = DebugStringForField(will_change__expr);
    d.correct = DebugStringForField(o_will_change__expr);
    diff.push_back(std::move(d));
  }
  const auto& appearance__expr = misc_data_->appearance_;
  const auto& o_appearance__expr = o.misc_data_->appearance_;
  if (!(appearance__expr == o_appearance__expr)) {
    DebugDiff d;
    d.field = DebugField::appearance_;
    d.actual = DebugStringForField(appearance__expr);
    d.correct = DebugStringForField(o_appearance__expr);
    diff.push_back(std::move(d));
  }
  const auto& blend_mode__expr = misc_data_->blend_mode_;
  const auto& o_blend_mode__expr = o.misc_data_->blend_mode_;
  if (!(blend_mode__expr == o_blend_mode__expr)) {
    DebugDiff d;
    d.field = DebugField::blend_mode_;
    d.actual = DebugStringForField(blend_mode__expr);
    d.correct = DebugStringForField(o_blend_mode__expr);
    diff.push_back(std::move(d));
  }
  const auto& contain__expr = misc_data_->contain_;
  const auto& o_contain__expr = o.misc_data_->contain_;
  if (!(contain__expr == o_contain__expr)) {
    DebugDiff d;
    d.field = DebugField::contain_;
    d.actual = DebugStringForField(contain__expr);
    d.correct = DebugStringForField(o_contain__expr);
    diff.push_back(std::move(d));
  }
  const auto& effective_appearance__expr = misc_data_->effective_appearance_;
  const auto& o_effective_appearance__expr = o.misc_data_->effective_appearance_;
  if (!(effective_appearance__expr == o_effective_appearance__expr)) {
    DebugDiff d;
    d.field = DebugField::effective_appearance_;
    d.actual = DebugStringForField(effective_appearance__expr);
    d.correct = DebugStringForField(o_effective_appearance__expr);
    diff.push_back(std::move(d));
  }
  const auto& break_after__expr = misc_data_->break_after_;
  const auto& o_break_after__expr = o.misc_data_->break_after_;
  if (!(break_after__expr == o_break_after__expr)) {
    DebugDiff d;
    d.field = DebugField::break_after_;
    d.actual = DebugStringForField(break_after__expr);
    d.correct = DebugStringForField(o_break_after__expr);
    diff.push_back(std::move(d));
  }
  const auto& break_before__expr = misc_data_->break_before_;
  const auto& o_break_before__expr = o.misc_data_->break_before_;
  if (!(break_before__expr == o_break_before__expr)) {
    DebugDiff d;
    d.field = DebugField::break_before_;
    d.actual = DebugStringForField(break_before__expr);
    d.correct = DebugStringForField(o_break_before__expr);
    diff.push_back(std::move(d));
  }
  const auto& container_type__expr = misc_data_->container_type_;
  const auto& o_container_type__expr = o.misc_data_->container_type_;
  if (!(container_type__expr == o_container_type__expr)) {
    DebugDiff d;
    d.field = DebugField::container_type_;
    d.actual = DebugStringForField(container_type__expr);
    d.correct = DebugStringForField(o_container_type__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_auto_flow__expr = misc_data_->grid_auto_flow_;
  const auto& o_grid_auto_flow__expr = o.misc_data_->grid_auto_flow_;
  if (!(grid_auto_flow__expr == o_grid_auto_flow__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_auto_flow_;
    d.actual = DebugStringForField(grid_auto_flow__expr);
    d.correct = DebugStringForField(o_grid_auto_flow__expr);
    diff.push_back(std::move(d));
  }
  const auto& margin_trim__expr = misc_data_->margin_trim_;
  const auto& o_margin_trim__expr = o.misc_data_->margin_trim_;
  if (!(margin_trim__expr == o_margin_trim__expr)) {
    DebugDiff d;
    d.field = DebugField::margin_trim_;
    d.actual = DebugStringForField(margin_trim__expr);
    d.correct = DebugStringForField(o_margin_trim__expr);
    diff.push_back(std::move(d));
  }
  const auto& outline_style__expr = misc_data_->outline_style_;
  const auto& o_outline_style__expr = o.misc_data_->outline_style_;
  if (!(outline_style__expr == o_outline_style__expr)) {
    DebugDiff d;
    d.field = DebugField::outline_style_;
    d.actual = DebugStringForField(outline_style__expr);
    d.correct = DebugStringForField(o_outline_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& scrollbar_gutter__expr = misc_data_->scrollbar_gutter_;
  const auto& o_scrollbar_gutter__expr = o.misc_data_->scrollbar_gutter_;
  if (!(scrollbar_gutter__expr == o_scrollbar_gutter__expr)) {
    DebugDiff d;
    d.field = DebugField::scrollbar_gutter_;
    d.actual = DebugStringForField(scrollbar_gutter__expr);
    d.correct = DebugStringForField(o_scrollbar_gutter__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_align__expr = misc_data_->box_align_;
  const auto& o_box_align__expr = o.misc_data_->box_align_;
  if (!(box_align__expr == o_box_align__expr)) {
    DebugDiff d;
    d.field = DebugField::box_align_;
    d.actual = DebugStringForField(box_align__expr);
    d.correct = DebugStringForField(o_box_align__expr);
    diff.push_back(std::move(d));
  }
  const auto& object_fit__expr = misc_data_->object_fit_;
  const auto& o_object_fit__expr = o.misc_data_->object_fit_;
  if (!(object_fit__expr == o_object_fit__expr)) {
    DebugDiff d;
    d.field = DebugField::object_fit_;
    d.actual = DebugStringForField(object_fit__expr);
    d.correct = DebugStringForField(o_object_fit__expr);
    diff.push_back(std::move(d));
  }
  const auto& position_try_order__expr = misc_data_->position_try_order_;
  const auto& o_position_try_order__expr = o.misc_data_->position_try_order_;
  if (!(position_try_order__expr == o_position_try_order__expr)) {
    DebugDiff d;
    d.field = DebugField::position_try_order_;
    d.actual = DebugStringForField(position_try_order__expr);
    d.correct = DebugStringForField(o_position_try_order__expr);
    diff.push_back(std::move(d));
  }
  const auto& position_visibility__expr = misc_data_->position_visibility_;
  const auto& o_position_visibility__expr = o.misc_data_->position_visibility_;
  if (!(position_visibility__expr == o_position_visibility__expr)) {
    DebugDiff d;
    d.field = DebugField::position_visibility_;
    d.actual = DebugStringForField(position_visibility__expr);
    d.correct = DebugStringForField(o_position_visibility__expr);
    diff.push_back(std::move(d));
  }
  const auto& reading_flow__expr = misc_data_->reading_flow_;
  const auto& o_reading_flow__expr = o.misc_data_->reading_flow_;
  if (!(reading_flow__expr == o_reading_flow__expr)) {
    DebugDiff d;
    d.field = DebugField::reading_flow_;
    d.actual = DebugStringForField(reading_flow__expr);
    d.correct = DebugStringForField(o_reading_flow__expr);
    diff.push_back(std::move(d));
  }
  const auto& affected_by_css_function__expr = misc_data_->affected_by_css_function_;
  const auto& o_affected_by_css_function__expr = o.misc_data_->affected_by_css_function_;
  if (!(affected_by_css_function__expr == o_affected_by_css_function__expr)) {
    DebugDiff d;
    d.field = DebugField::affected_by_css_function_;
    d.actual = DebugStringForField(affected_by_css_function__expr);
    d.correct = DebugStringForField(o_affected_by_css_function__expr);
    diff.push_back(std::move(d));
  }
  const auto& resize__expr = misc_data_->resize_;
  const auto& o_resize__expr = o.misc_data_->resize_;
  if (!(resize__expr == o_resize__expr)) {
    DebugDiff d;
    d.field = DebugField::resize_;
    d.actual = DebugStringForField(resize__expr);
    d.correct = DebugStringForField(o_resize__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_decoration_style__expr = misc_data_->text_decoration_style_;
  const auto& o_text_decoration_style__expr = o.misc_data_->text_decoration_style_;
  if (!(text_decoration_style__expr == o_text_decoration_style__expr)) {
    DebugDiff d;
    d.field = DebugField::text_decoration_style_;
    d.actual = DebugStringForField(text_decoration_style__expr);
    d.correct = DebugStringForField(o_text_decoration_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_pack__expr = misc_data_->box_pack_;
  const auto& o_box_pack__expr = o.misc_data_->box_pack_;
  if (!(box_pack__expr == o_box_pack__expr)) {
    DebugDiff d;
    d.field = DebugField::box_pack_;
    d.actual = DebugStringForField(box_pack__expr);
    d.correct = DebugStringForField(o_box_pack__expr);
    diff.push_back(std::move(d));
  }
  const auto& break_inside__expr = misc_data_->break_inside_;
  const auto& o_break_inside__expr = o.misc_data_->break_inside_;
  if (!(break_inside__expr == o_break_inside__expr)) {
    DebugDiff d;
    d.field = DebugField::break_inside_;
    d.actual = DebugStringForField(break_inside__expr);
    d.correct = DebugStringForField(o_break_inside__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_break__expr = misc_data_->column_rule_break_;
  const auto& o_column_rule_break__expr = o.misc_data_->column_rule_break_;
  if (!(column_rule_break__expr == o_column_rule_break__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_break_;
    d.actual = DebugStringForField(column_rule_break__expr);
    d.correct = DebugStringForField(o_column_rule_break__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_rule_visibility_items__expr = misc_data_->column_rule_visibility_items_;
  const auto& o_column_rule_visibility_items__expr = o.misc_data_->column_rule_visibility_items_;
  if (!(column_rule_visibility_items__expr == o_column_rule_visibility_items__expr)) {
    DebugDiff d;
    d.field = DebugField::column_rule_visibility_items_;
    d.actual = DebugStringForField(column_rule_visibility_items__expr);
    d.correct = DebugStringForField(o_column_rule_visibility_items__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_wrap__expr = misc_data_->column_wrap_;
  const auto& o_column_wrap__expr = o.misc_data_->column_wrap_;
  if (!(column_wrap__expr == o_column_wrap__expr)) {
    DebugDiff d;
    d.field = DebugField::column_wrap_;
    d.actual = DebugStringForField(column_wrap__expr);
    d.correct = DebugStringForField(o_column_wrap__expr);
    diff.push_back(std::move(d));
  }
  const auto& continue__expr = misc_data_->continue_;
  const auto& o_continue__expr = o.misc_data_->continue_;
  if (!(continue__expr == o_continue__expr)) {
    DebugDiff d;
    d.field = DebugField::continue_;
    d.actual = DebugStringForField(continue__expr);
    d.correct = DebugStringForField(o_continue__expr);
    diff.push_back(std::move(d));
  }
  const auto& draggable_region_mode__expr = misc_data_->draggable_region_mode_;
  const auto& o_draggable_region_mode__expr = o.misc_data_->draggable_region_mode_;
  if (!(draggable_region_mode__expr == o_draggable_region_mode__expr)) {
    DebugDiff d;
    d.field = DebugField::draggable_region_mode_;
    d.actual = DebugStringForField(draggable_region_mode__expr);
    d.correct = DebugStringForField(o_draggable_region_mode__expr);
    diff.push_back(std::move(d));
  }
  const auto& flex_direction__expr = misc_data_->flex_direction_;
  const auto& o_flex_direction__expr = o.misc_data_->flex_direction_;
  if (!(flex_direction__expr == o_flex_direction__expr)) {
    DebugDiff d;
    d.field = DebugField::flex_direction_;
    d.actual = DebugStringForField(flex_direction__expr);
    d.correct = DebugStringForField(o_flex_direction__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_overscroll_area__expr = misc_data_->internal_overscroll_area_;
  const auto& o_internal_overscroll_area__expr = o.misc_data_->internal_overscroll_area_;
  if (!(internal_overscroll_area__expr == o_internal_overscroll_area__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_overscroll_area_;
    d.actual = DebugStringForField(internal_overscroll_area__expr);
    d.correct = DebugStringForField(o_internal_overscroll_area__expr);
    diff.push_back(std::move(d));
  }
  const auto& overscroll_behavior_x__expr = misc_data_->overscroll_behavior_x_;
  const auto& o_overscroll_behavior_x__expr = o.misc_data_->overscroll_behavior_x_;
  if (!(overscroll_behavior_x__expr == o_overscroll_behavior_x__expr)) {
    DebugDiff d;
    d.field = DebugField::overscroll_behavior_x_;
    d.actual = DebugStringForField(overscroll_behavior_x__expr);
    d.correct = DebugStringForField(o_overscroll_behavior_x__expr);
    diff.push_back(std::move(d));
  }
  const auto& overscroll_behavior_y__expr = misc_data_->overscroll_behavior_y_;
  const auto& o_overscroll_behavior_y__expr = o.misc_data_->overscroll_behavior_y_;
  if (!(overscroll_behavior_y__expr == o_overscroll_behavior_y__expr)) {
    DebugDiff d;
    d.field = DebugField::overscroll_behavior_y_;
    d.actual = DebugStringForField(overscroll_behavior_y__expr);
    d.correct = DebugStringForField(o_overscroll_behavior_y__expr);
    diff.push_back(std::move(d));
  }
  const auto& page_margin_safety__expr = misc_data_->page_margin_safety_;
  const auto& o_page_margin_safety__expr = o.misc_data_->page_margin_safety_;
  if (!(page_margin_safety__expr == o_page_margin_safety__expr)) {
    DebugDiff d;
    d.field = DebugField::page_margin_safety_;
    d.actual = DebugStringForField(page_margin_safety__expr);
    d.correct = DebugStringForField(o_page_margin_safety__expr);
    diff.push_back(std::move(d));
  }
  const auto& page_orientation__expr = misc_data_->page_orientation_;
  const auto& o_page_orientation__expr = o.misc_data_->page_orientation_;
  if (!(page_orientation__expr == o_page_orientation__expr)) {
    DebugDiff d;
    d.field = DebugField::page_orientation_;
    d.actual = DebugStringForField(page_orientation__expr);
    d.correct = DebugStringForField(o_page_orientation__expr);
    diff.push_back(std::move(d));
  }
  const auto& page_size_type__expr = misc_data_->page_size_type_;
  const auto& o_page_size_type__expr = o.misc_data_->page_size_type_;
  if (!(page_size_type__expr == o_page_size_type__expr)) {
    DebugDiff d;
    d.field = DebugField::page_size_type_;
    d.actual = DebugStringForField(page_size_type__expr);
    d.correct = DebugStringForField(o_page_size_type__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_break__expr = misc_data_->row_rule_break_;
  const auto& o_row_rule_break__expr = o.misc_data_->row_rule_break_;
  if (!(row_rule_break__expr == o_row_rule_break__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_break_;
    d.actual = DebugStringForField(row_rule_break__expr);
    d.correct = DebugStringForField(o_row_rule_break__expr);
    diff.push_back(std::move(d));
  }
  const auto& row_rule_visibility_items__expr = misc_data_->row_rule_visibility_items_;
  const auto& o_row_rule_visibility_items__expr = o.misc_data_->row_rule_visibility_items_;
  if (!(row_rule_visibility_items__expr == o_row_rule_visibility_items__expr)) {
    DebugDiff d;
    d.field = DebugField::row_rule_visibility_items_;
    d.actual = DebugStringForField(row_rule_visibility_items__expr);
    d.correct = DebugStringForField(o_row_rule_visibility_items__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_behavior__expr = misc_data_->scroll_behavior_;
  const auto& o_scroll_behavior__expr = o.misc_data_->scroll_behavior_;
  if (!(scroll_behavior__expr == o_scroll_behavior__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_behavior_;
    d.actual = DebugStringForField(scroll_behavior__expr);
    d.correct = DebugStringForField(o_scroll_behavior__expr);
    diff.push_back(std::move(d));
  }
  const auto& scrollbar_width__expr = misc_data_->scrollbar_width_;
  const auto& o_scrollbar_width__expr = o.misc_data_->scrollbar_width_;
  if (!(scrollbar_width__expr == o_scrollbar_width__expr)) {
    DebugDiff d;
    d.field = DebugField::scrollbar_width_;
    d.actual = DebugStringForField(scrollbar_width__expr);
    d.correct = DebugStringForField(o_scrollbar_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& user_drag__expr = misc_data_->user_drag_;
  const auto& o_user_drag__expr = o.misc_data_->user_drag_;
  if (!(user_drag__expr == o_user_drag__expr)) {
    DebugDiff d;
    d.field = DebugField::user_drag_;
    d.actual = DebugStringForField(user_drag__expr);
    d.correct = DebugStringForField(o_user_drag__expr);
    diff.push_back(std::move(d));
  }
  const auto& affected_by_functional_media__expr = misc_data_->affected_by_functional_media_;
  const auto& o_affected_by_functional_media__expr = o.misc_data_->affected_by_functional_media_;
  if (!(affected_by_functional_media__expr == o_affected_by_functional_media__expr)) {
    DebugDiff d;
    d.field = DebugField::affected_by_functional_media_;
    d.actual = DebugStringForField(affected_by_functional_media__expr);
    d.correct = DebugStringForField(o_affected_by_functional_media__expr);
    diff.push_back(std::move(d));
  }
  const auto& align_content_block_center__expr = misc_data_->align_content_block_center_;
  const auto& o_align_content_block_center__expr = o.misc_data_->align_content_block_center_;
  if (!(align_content_block_center__expr == o_align_content_block_center__expr)) {
    DebugDiff d;
    d.field = DebugField::align_content_block_center_;
    d.actual = DebugStringForField(align_content_block_center__expr);
    d.correct = DebugStringForField(o_align_content_block_center__expr);
    diff.push_back(std::move(d));
  }
  const auto& backface_visibility__expr = misc_data_->backface_visibility_;
  const auto& o_backface_visibility__expr = o.misc_data_->backface_visibility_;
  if (!(backface_visibility__expr == o_backface_visibility__expr)) {
    DebugDiff d;
    d.field = DebugField::backface_visibility_;
    d.actual = DebugStringForField(backface_visibility__expr);
    d.correct = DebugStringForField(o_backface_visibility__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_orient__expr = misc_data_->box_orient_;
  const auto& o_box_orient__expr = o.misc_data_->box_orient_;
  if (!(box_orient__expr == o_box_orient__expr)) {
    DebugDiff d;
    d.field = DebugField::box_orient_;
    d.actual = DebugStringForField(box_orient__expr);
    d.correct = DebugStringForField(o_box_orient__expr);
    diff.push_back(std::move(d));
  }
  const auto& can_affect_animations__expr = misc_data_->can_affect_animations_;
  const auto& o_can_affect_animations__expr = o.misc_data_->can_affect_animations_;
  if (!(can_affect_animations__expr == o_can_affect_animations__expr)) {
    DebugDiff d;
    d.field = DebugField::can_affect_animations_;
    d.actual = DebugStringForField(can_affect_animations__expr);
    d.correct = DebugStringForField(o_can_affect_animations__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_fill__expr = misc_data_->column_fill_;
  const auto& o_column_fill__expr = o.misc_data_->column_fill_;
  if (!(column_fill__expr == o_column_fill__expr)) {
    DebugDiff d;
    d.field = DebugField::column_fill_;
    d.actual = DebugStringForField(column_fill__expr);
    d.correct = DebugStringForField(o_column_fill__expr);
    diff.push_back(std::move(d));
  }
  const auto& column_span__expr = misc_data_->column_span_;
  const auto& o_column_span__expr = o.misc_data_->column_span_;
  if (!(column_span__expr == o_column_span__expr)) {
    DebugDiff d;
    d.field = DebugField::column_span_;
    d.actual = DebugStringForField(column_span__expr);
    d.correct = DebugStringForField(o_column_span__expr);
    diff.push_back(std::move(d));
  }
  const auto& depends_on_anchored_container_queries__expr = misc_data_->depends_on_anchored_container_queries_;
  const auto& o_depends_on_anchored_container_queries__expr = o.misc_data_->depends_on_anchored_container_queries_;
  if (!(depends_on_anchored_container_queries__expr == o_depends_on_anchored_container_queries__expr)) {
    DebugDiff d;
    d.field = DebugField::depends_on_anchored_container_queries_;
    d.actual = DebugStringForField(depends_on_anchored_container_queries__expr);
    d.correct = DebugStringForField(o_depends_on_anchored_container_queries__expr);
    diff.push_back(std::move(d));
  }
  const auto& depends_on_scroll_state_container_queries__expr = misc_data_->depends_on_scroll_state_container_queries_;
  const auto& o_depends_on_scroll_state_container_queries__expr = o.misc_data_->depends_on_scroll_state_container_queries_;
  if (!(depends_on_scroll_state_container_queries__expr == o_depends_on_scroll_state_container_queries__expr)) {
    DebugDiff d;
    d.field = DebugField::depends_on_scroll_state_container_queries_;
    d.actual = DebugStringForField(depends_on_scroll_state_container_queries__expr);
    d.correct = DebugStringForField(o_depends_on_scroll_state_container_queries__expr);
    diff.push_back(std::move(d));
  }
  const auto& depends_on_size_container_queries__expr = misc_data_->depends_on_size_container_queries_;
  const auto& o_depends_on_size_container_queries__expr = o.misc_data_->depends_on_size_container_queries_;
  if (!(depends_on_size_container_queries__expr == o_depends_on_size_container_queries__expr)) {
    DebugDiff d;
    d.field = DebugField::depends_on_size_container_queries_;
    d.actual = DebugStringForField(depends_on_size_container_queries__expr);
    d.correct = DebugStringForField(o_depends_on_size_container_queries__expr);
    diff.push_back(std::move(d));
  }
  const auto& depends_on_style_container_queries__expr = misc_data_->depends_on_style_container_queries_;
  const auto& o_depends_on_style_container_queries__expr = o.misc_data_->depends_on_style_container_queries_;
  if (!(depends_on_style_container_queries__expr == o_depends_on_style_container_queries__expr)) {
    DebugDiff d;
    d.field = DebugField::depends_on_style_container_queries_;
    d.actual = DebugStringForField(depends_on_style_container_queries__expr);
    d.correct = DebugStringForField(o_depends_on_style_container_queries__expr);
    diff.push_back(std::move(d));
  }
  const auto& element_is_view_transition_participant__expr = misc_data_->element_is_view_transition_participant_;
  const auto& o_element_is_view_transition_participant__expr = o.misc_data_->element_is_view_transition_participant_;
  if (!(element_is_view_transition_participant__expr == o_element_is_view_transition_participant__expr)) {
    DebugDiff d;
    d.field = DebugField::element_is_view_transition_participant_;
    d.actual = DebugStringForField(element_is_view_transition_participant__expr);
    d.correct = DebugStringForField(o_element_is_view_transition_participant__expr);
    diff.push_back(std::move(d));
  }
  const auto& first_line_depends_on_size_container_queries__expr = misc_data_->first_line_depends_on_size_container_queries_;
  const auto& o_first_line_depends_on_size_container_queries__expr = o.misc_data_->first_line_depends_on_size_container_queries_;
  if (!(first_line_depends_on_size_container_queries__expr == o_first_line_depends_on_size_container_queries__expr)) {
    DebugDiff d;
    d.field = DebugField::first_line_depends_on_size_container_queries_;
    d.actual = DebugStringForField(first_line_depends_on_size_container_queries__expr);
    d.correct = DebugStringForField(o_first_line_depends_on_size_container_queries__expr);
    diff.push_back(std::move(d));
  }
  const auto& grid_lanes_pack__expr = misc_data_->grid_lanes_pack_;
  const auto& o_grid_lanes_pack__expr = o.misc_data_->grid_lanes_pack_;
  if (!(grid_lanes_pack__expr == o_grid_lanes_pack__expr)) {
    DebugDiff d;
    d.field = DebugField::grid_lanes_pack_;
    d.actual = DebugStringForField(grid_lanes_pack__expr);
    d.correct = DebugStringForField(o_grid_lanes_pack__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_auto_column_count__expr = misc_data_->has_auto_column_count_;
  const auto& o_has_auto_column_count__expr = o.misc_data_->has_auto_column_count_;
  if (!(has_auto_column_count__expr == o_has_auto_column_count__expr)) {
    DebugDiff d;
    d.field = DebugField::has_auto_column_count_;
    d.actual = DebugStringForField(has_auto_column_count__expr);
    d.correct = DebugStringForField(o_has_auto_column_count__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_auto_column_height__expr = misc_data_->has_auto_column_height_;
  const auto& o_has_auto_column_height__expr = o.misc_data_->has_auto_column_height_;
  if (!(has_auto_column_height__expr == o_has_auto_column_height__expr)) {
    DebugDiff d;
    d.field = DebugField::has_auto_column_height_;
    d.actual = DebugStringForField(has_auto_column_height__expr);
    d.correct = DebugStringForField(o_has_auto_column_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_auto_column_width__expr = misc_data_->has_auto_column_width_;
  const auto& o_has_auto_column_width__expr = o.misc_data_->has_auto_column_width_;
  if (!(has_auto_column_width__expr == o_has_auto_column_width__expr)) {
    DebugDiff d;
    d.field = DebugField::has_auto_column_width_;
    d.actual = DebugStringForField(has_auto_column_width__expr);
    d.correct = DebugStringForField(o_has_auto_column_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_backdrop_filter_animation__expr = misc_data_->has_current_backdrop_filter_animation_;
  const auto& o_has_current_backdrop_filter_animation__expr = o.misc_data_->has_current_backdrop_filter_animation_;
  if (!(has_current_backdrop_filter_animation__expr == o_has_current_backdrop_filter_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_backdrop_filter_animation_;
    d.actual = DebugStringForField(has_current_backdrop_filter_animation__expr);
    d.correct = DebugStringForField(o_has_current_backdrop_filter_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_background_color_animation__expr = misc_data_->has_current_background_color_animation_;
  const auto& o_has_current_background_color_animation__expr = o.misc_data_->has_current_background_color_animation_;
  if (!(has_current_background_color_animation__expr == o_has_current_background_color_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_background_color_animation_;
    d.actual = DebugStringForField(has_current_background_color_animation__expr);
    d.correct = DebugStringForField(o_has_current_background_color_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_clip_path_animation__expr = misc_data_->has_current_clip_path_animation_;
  const auto& o_has_current_clip_path_animation__expr = o.misc_data_->has_current_clip_path_animation_;
  if (!(has_current_clip_path_animation__expr == o_has_current_clip_path_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_clip_path_animation_;
    d.actual = DebugStringForField(has_current_clip_path_animation__expr);
    d.correct = DebugStringForField(o_has_current_clip_path_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_filter_animation__expr = misc_data_->has_current_filter_animation_;
  const auto& o_has_current_filter_animation__expr = o.misc_data_->has_current_filter_animation_;
  if (!(has_current_filter_animation__expr == o_has_current_filter_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_filter_animation_;
    d.actual = DebugStringForField(has_current_filter_animation__expr);
    d.correct = DebugStringForField(o_has_current_filter_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_opacity_animation__expr = misc_data_->has_current_opacity_animation_;
  const auto& o_has_current_opacity_animation__expr = o.misc_data_->has_current_opacity_animation_;
  if (!(has_current_opacity_animation__expr == o_has_current_opacity_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_opacity_animation_;
    d.actual = DebugStringForField(has_current_opacity_animation__expr);
    d.correct = DebugStringForField(o_has_current_opacity_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_rotate_animation__expr = misc_data_->has_current_rotate_animation_;
  const auto& o_has_current_rotate_animation__expr = o.misc_data_->has_current_rotate_animation_;
  if (!(has_current_rotate_animation__expr == o_has_current_rotate_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_rotate_animation_;
    d.actual = DebugStringForField(has_current_rotate_animation__expr);
    d.correct = DebugStringForField(o_has_current_rotate_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_scale_animation__expr = misc_data_->has_current_scale_animation_;
  const auto& o_has_current_scale_animation__expr = o.misc_data_->has_current_scale_animation_;
  if (!(has_current_scale_animation__expr == o_has_current_scale_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_scale_animation_;
    d.actual = DebugStringForField(has_current_scale_animation__expr);
    d.correct = DebugStringForField(o_has_current_scale_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_transform_animation__expr = misc_data_->has_current_transform_animation_;
  const auto& o_has_current_transform_animation__expr = o.misc_data_->has_current_transform_animation_;
  if (!(has_current_transform_animation__expr == o_has_current_transform_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_transform_animation_;
    d.actual = DebugStringForField(has_current_transform_animation__expr);
    d.correct = DebugStringForField(o_has_current_transform_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_current_translate_animation__expr = misc_data_->has_current_translate_animation_;
  const auto& o_has_current_translate_animation__expr = o.misc_data_->has_current_translate_animation_;
  if (!(has_current_translate_animation__expr == o_has_current_translate_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::has_current_translate_animation_;
    d.actual = DebugStringForField(has_current_translate_animation__expr);
    d.correct = DebugStringForField(o_has_current_translate_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_explicit_overflow_x_visible__expr = misc_data_->has_explicit_overflow_x_visible_;
  const auto& o_has_explicit_overflow_x_visible__expr = o.misc_data_->has_explicit_overflow_x_visible_;
  if (!(has_explicit_overflow_x_visible__expr == o_has_explicit_overflow_x_visible__expr)) {
    DebugDiff d;
    d.field = DebugField::has_explicit_overflow_x_visible_;
    d.actual = DebugStringForField(has_explicit_overflow_x_visible__expr);
    d.correct = DebugStringForField(o_has_explicit_overflow_x_visible__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_explicit_overflow_y_visible__expr = misc_data_->has_explicit_overflow_y_visible_;
  const auto& o_has_explicit_overflow_y_visible__expr = o.misc_data_->has_explicit_overflow_y_visible_;
  if (!(has_explicit_overflow_y_visible__expr == o_has_explicit_overflow_y_visible__expr)) {
    DebugDiff d;
    d.field = DebugField::has_explicit_overflow_y_visible_;
    d.actual = DebugStringForField(has_explicit_overflow_y_visible__expr);
    d.correct = DebugStringForField(o_has_explicit_overflow_y_visible__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_overscroll_position__expr = misc_data_->internal_overscroll_position_;
  const auto& o_internal_overscroll_position__expr = o.misc_data_->internal_overscroll_position_;
  if (!(internal_overscroll_position__expr == o_internal_overscroll_position__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_overscroll_position_;
    d.actual = DebugStringForField(internal_overscroll_position__expr);
    d.correct = DebugStringForField(o_internal_overscroll_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_bottom_relative_to_safe_area_inset__expr = misc_data_->is_bottom_relative_to_safe_area_inset_;
  const auto& o_is_bottom_relative_to_safe_area_inset__expr = o.misc_data_->is_bottom_relative_to_safe_area_inset_;
  if (!(is_bottom_relative_to_safe_area_inset__expr == o_is_bottom_relative_to_safe_area_inset__expr)) {
    DebugDiff d;
    d.field = DebugField::is_bottom_relative_to_safe_area_inset_;
    d.actual = DebugStringForField(is_bottom_relative_to_safe_area_inset__expr);
    d.correct = DebugStringForField(o_is_bottom_relative_to_safe_area_inset__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_running_rotate_animation_on_compositor__expr = misc_data_->is_running_rotate_animation_on_compositor_;
  const auto& o_is_running_rotate_animation_on_compositor__expr = o.misc_data_->is_running_rotate_animation_on_compositor_;
  if (!(is_running_rotate_animation_on_compositor__expr == o_is_running_rotate_animation_on_compositor__expr)) {
    DebugDiff d;
    d.field = DebugField::is_running_rotate_animation_on_compositor_;
    d.actual = DebugStringForField(is_running_rotate_animation_on_compositor__expr);
    d.correct = DebugStringForField(o_is_running_rotate_animation_on_compositor__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_running_scale_animation_on_compositor__expr = misc_data_->is_running_scale_animation_on_compositor_;
  const auto& o_is_running_scale_animation_on_compositor__expr = o.misc_data_->is_running_scale_animation_on_compositor_;
  if (!(is_running_scale_animation_on_compositor__expr == o_is_running_scale_animation_on_compositor__expr)) {
    DebugDiff d;
    d.field = DebugField::is_running_scale_animation_on_compositor_;
    d.actual = DebugStringForField(is_running_scale_animation_on_compositor__expr);
    d.correct = DebugStringForField(o_is_running_scale_animation_on_compositor__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_running_transform_animation_on_compositor__expr = misc_data_->is_running_transform_animation_on_compositor_;
  const auto& o_is_running_transform_animation_on_compositor__expr = o.misc_data_->is_running_transform_animation_on_compositor_;
  if (!(is_running_transform_animation_on_compositor__expr == o_is_running_transform_animation_on_compositor__expr)) {
    DebugDiff d;
    d.field = DebugField::is_running_transform_animation_on_compositor_;
    d.actual = DebugStringForField(is_running_transform_animation_on_compositor__expr);
    d.correct = DebugStringForField(o_is_running_transform_animation_on_compositor__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_running_translate_animation_on_compositor__expr = misc_data_->is_running_translate_animation_on_compositor_;
  const auto& o_is_running_translate_animation_on_compositor__expr = o.misc_data_->is_running_translate_animation_on_compositor_;
  if (!(is_running_translate_animation_on_compositor__expr == o_is_running_translate_animation_on_compositor__expr)) {
    DebugDiff d;
    d.field = DebugField::is_running_translate_animation_on_compositor_;
    d.actual = DebugStringForField(is_running_translate_animation_on_compositor__expr);
    d.correct = DebugStringForField(o_is_running_translate_animation_on_compositor__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_secondary_body_element__expr = misc_data_->is_secondary_body_element_;
  const auto& o_is_secondary_body_element__expr = o.misc_data_->is_secondary_body_element_;
  if (!(is_secondary_body_element__expr == o_is_secondary_body_element__expr)) {
    DebugDiff d;
    d.field = DebugField::is_secondary_body_element_;
    d.actual = DebugStringForField(is_secondary_body_element__expr);
    d.correct = DebugStringForField(o_is_secondary_body_element__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_specified_display_webkit_box__expr = misc_data_->is_specified_display_webkit_box_;
  const auto& o_is_specified_display_webkit_box__expr = o.misc_data_->is_specified_display_webkit_box_;
  if (!(is_specified_display_webkit_box__expr == o_is_specified_display_webkit_box__expr)) {
    DebugDiff d;
    d.field = DebugField::is_specified_display_webkit_box_;
    d.actual = DebugStringForField(is_specified_display_webkit_box__expr);
    d.correct = DebugStringForField(o_is_specified_display_webkit_box__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_starting_style__expr = misc_data_->is_starting_style_;
  const auto& o_is_starting_style__expr = o.misc_data_->is_starting_style_;
  if (!(is_starting_style__expr == o_is_starting_style__expr)) {
    DebugDiff d;
    d.field = DebugField::is_starting_style_;
    d.actual = DebugStringForField(is_starting_style__expr);
    d.correct = DebugStringForField(o_is_starting_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& isolation__expr = misc_data_->isolation_;
  const auto& o_isolation__expr = o.misc_data_->isolation_;
  if (!(isolation__expr == o_isolation__expr)) {
    DebugDiff d;
    d.field = DebugField::isolation_;
    d.actual = DebugStringForField(isolation__expr);
    d.correct = DebugStringForField(o_isolation__expr);
    diff.push_back(std::move(d));
  }
  const auto& outline_style_is_auto__expr = misc_data_->outline_style_is_auto_;
  const auto& o_outline_style_is_auto__expr = o.misc_data_->outline_style_is_auto_;
  if (!(outline_style_is_auto__expr == o_outline_style_is_auto__expr)) {
    DebugDiff d;
    d.field = DebugField::outline_style_is_auto_;
    d.actual = DebugStringForField(outline_style_is_auto__expr);
    d.correct = DebugStringForField(o_outline_style_is_auto__expr);
    diff.push_back(std::move(d));
  }
  const auto& overlay__expr = misc_data_->overlay_;
  const auto& o_overlay__expr = o.misc_data_->overlay_;
  if (!(overlay__expr == o_overlay__expr)) {
    DebugDiff d;
    d.field = DebugField::overlay_;
    d.actual = DebugStringForField(overlay__expr);
    d.correct = DebugStringForField(o_overlay__expr);
    diff.push_back(std::move(d));
  }
  const auto& requires_accelerated_compositing_for_external_reasons__expr = misc_data_->requires_accelerated_compositing_for_external_reasons_;
  const auto& o_requires_accelerated_compositing_for_external_reasons__expr = o.misc_data_->requires_accelerated_compositing_for_external_reasons_;
  if (!(requires_accelerated_compositing_for_external_reasons__expr == o_requires_accelerated_compositing_for_external_reasons__expr)) {
    DebugDiff d;
    d.field = DebugField::requires_accelerated_compositing_for_external_reasons_;
    d.actual = DebugStringForField(requires_accelerated_compositing_for_external_reasons__expr);
    d.correct = DebugStringForField(o_requires_accelerated_compositing_for_external_reasons__expr);
    diff.push_back(std::move(d));
  }
  const auto& rule_overlap__expr = misc_data_->rule_overlap_;
  const auto& o_rule_overlap__expr = o.misc_data_->rule_overlap_;
  if (!(rule_overlap__expr == o_rule_overlap__expr)) {
    DebugDiff d;
    d.field = DebugField::rule_overlap_;
    d.actual = DebugStringForField(rule_overlap__expr);
    d.correct = DebugStringForField(o_rule_overlap__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_initial_target__expr = misc_data_->scroll_initial_target_;
  const auto& o_scroll_initial_target__expr = o.misc_data_->scroll_initial_target_;
  if (!(scroll_initial_target__expr == o_scroll_initial_target__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_initial_target_;
    d.actual = DebugStringForField(scroll_initial_target__expr);
    d.correct = DebugStringForField(o_scroll_initial_target__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_target_group__expr = misc_data_->scroll_target_group_;
  const auto& o_scroll_target_group__expr = o.misc_data_->scroll_target_group_;
  if (!(scroll_target_group__expr == o_scroll_target_group__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_target_group_;
    d.actual = DebugStringForField(scroll_target_group__expr);
    d.correct = DebugStringForField(o_scroll_target_group__expr);
    diff.push_back(std::move(d));
  }
  const auto& transform_style_3d__expr = misc_data_->transform_style_3d_;
  const auto& o_transform_style_3d__expr = o.misc_data_->transform_style_3d_;
  if (!(transform_style_3d__expr == o_transform_style_3d__expr)) {
    DebugDiff d;
    d.field = DebugField::transform_style_3d_;
    d.actual = DebugStringForField(transform_style_3d__expr);
    d.correct = DebugStringForField(o_transform_style_3d__expr);
    diff.push_back(std::move(d));
  }
  const auto& view_transition_scope__expr = misc_data_->view_transition_scope_;
  const auto& o_view_transition_scope__expr = o.misc_data_->view_transition_scope_;
  if (!(view_transition_scope__expr == o_view_transition_scope__expr)) {
    DebugDiff d;
    d.field = DebugField::view_transition_scope_;
    d.actual = DebugStringForField(view_transition_scope__expr);
    d.correct = DebugStringForField(o_view_transition_scope__expr);
    diff.push_back(std::move(d));
  }

      // Group: inherited_forced_colors
  const auto& internal_forced_visited_color__expr = inherited_data_->inherited_forced_colors_data_->internal_forced_visited_color_;
  const auto& o_internal_forced_visited_color__expr = o.inherited_data_->inherited_forced_colors_data_->internal_forced_visited_color_;
  if (!(internal_forced_visited_color__expr == o_internal_forced_visited_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_forced_visited_color_;
    d.actual = DebugStringForField(internal_forced_visited_color__expr);
    d.correct = DebugStringForField(o_internal_forced_visited_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_forced_color__expr = inherited_data_->inherited_forced_colors_data_->internal_forced_color_;
  const auto& o_internal_forced_color__expr = o.inherited_data_->inherited_forced_colors_data_->internal_forced_color_;
  if (!(internal_forced_color__expr == o_internal_forced_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_forced_color_;
    d.actual = DebugStringForField(internal_forced_color__expr);
    d.correct = DebugStringForField(o_internal_forced_color__expr);
    diff.push_back(std::move(d));
  }

    // Group: inherited_visited
  const auto& internal_visited_text_emphasis_color__expr = inherited_data_->inherited_visited_data_->internal_visited_text_emphasis_color_;
  const auto& o_internal_visited_text_emphasis_color__expr = o.inherited_data_->inherited_visited_data_->internal_visited_text_emphasis_color_;
  if (!(internal_visited_text_emphasis_color__expr == o_internal_visited_text_emphasis_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_text_emphasis_color_;
    d.actual = DebugStringForField(internal_visited_text_emphasis_color__expr);
    d.correct = DebugStringForField(o_internal_visited_text_emphasis_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_text_fill_color__expr = inherited_data_->inherited_visited_data_->internal_visited_text_fill_color_;
  const auto& o_internal_visited_text_fill_color__expr = o.inherited_data_->inherited_visited_data_->internal_visited_text_fill_color_;
  if (!(internal_visited_text_fill_color__expr == o_internal_visited_text_fill_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_text_fill_color_;
    d.actual = DebugStringForField(internal_visited_text_fill_color__expr);
    d.correct = DebugStringForField(o_internal_visited_text_fill_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_text_stroke_color__expr = inherited_data_->inherited_visited_data_->internal_visited_text_stroke_color_;
  const auto& o_internal_visited_text_stroke_color__expr = o.inherited_data_->inherited_visited_data_->internal_visited_text_stroke_color_;
  if (!(internal_visited_text_stroke_color__expr == o_internal_visited_text_stroke_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_text_stroke_color_;
    d.actual = DebugStringForField(internal_visited_text_stroke_color__expr);
    d.correct = DebugStringForField(o_internal_visited_text_stroke_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_caret_color__expr = inherited_data_->inherited_visited_data_->internal_visited_caret_color_;
  const auto& o_internal_visited_caret_color__expr = o.inherited_data_->inherited_visited_data_->internal_visited_caret_color_;
  if (!(internal_visited_caret_color__expr == o_internal_visited_caret_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_caret_color_;
    d.actual = DebugStringForField(internal_visited_caret_color__expr);
    d.correct = DebugStringForField(o_internal_visited_caret_color__expr);
    diff.push_back(std::move(d));
  }

    // Group: highlight-data
  const auto& highlight_data__expr = inherited_data_->highlight_data_data_->highlight_data_;
  const auto& o_highlight_data__expr = o.inherited_data_->highlight_data_data_->highlight_data_;
  if (!(highlight_data__expr == o_highlight_data__expr)) {
    DebugDiff d;
    d.field = DebugField::highlight_data_;
    d.actual = DebugStringForField(highlight_data__expr);
    d.correct = DebugStringForField(o_highlight_data__expr);
    diff.push_back(std::move(d));
  }

  // Group: inherited
  const auto& inherited_variables__expr = inherited_data_->inherited_variables_;
  const auto& o_inherited_variables__expr = o.inherited_data_->inherited_variables_;
  if (!(inherited_variables__expr == o_inherited_variables__expr)) {
    DebugDiff d;
    d.field = DebugField::inherited_variables_;
    d.actual = DebugStringForField(inherited_variables__expr);
    d.correct = DebugStringForField(o_inherited_variables__expr);
    diff.push_back(std::move(d));
  }
  const auto& font__expr = inherited_data_->font_;
  const auto& o_font__expr = o.inherited_data_->font_;
  if (!(base::ValuesEquivalent(font__expr, o_font__expr))) {
    DebugDiff d;
    d.field = DebugField::font_;
    d.actual = DebugStringForField(font__expr);
    d.correct = DebugStringForField(o_font__expr);
    diff.push_back(std::move(d));
  }
  const auto& container_font__expr = inherited_data_->container_font_;
  const auto& o_container_font__expr = o.inherited_data_->container_font_;
  if (!(base::ValuesEquivalent(container_font__expr, o_container_font__expr))) {
    DebugDiff d;
    d.field = DebugField::container_font_;
    d.actual = DebugStringForField(container_font__expr);
    d.correct = DebugStringForField(o_container_font__expr);
    diff.push_back(std::move(d));
  }
  const auto& letter_spacing__expr = inherited_data_->letter_spacing_;
  const auto& o_letter_spacing__expr = o.inherited_data_->letter_spacing_;
  if (!(letter_spacing__expr == o_letter_spacing__expr)) {
    DebugDiff d;
    d.field = DebugField::letter_spacing_;
    d.actual = DebugStringForField(letter_spacing__expr);
    d.correct = DebugStringForField(o_letter_spacing__expr);
    diff.push_back(std::move(d));
  }
  const auto& line_height__expr = inherited_data_->line_height_;
  const auto& o_line_height__expr = o.inherited_data_->line_height_;
  if (!(line_height__expr == o_line_height__expr)) {
    DebugDiff d;
    d.field = DebugField::line_height_;
    d.actual = DebugStringForField(line_height__expr);
    d.correct = DebugStringForField(o_line_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& word_spacing__expr = inherited_data_->word_spacing_;
  const auto& o_word_spacing__expr = o.inherited_data_->word_spacing_;
  if (!(word_spacing__expr == o_word_spacing__expr)) {
    DebugDiff d;
    d.field = DebugField::word_spacing_;
    d.actual = DebugStringForField(word_spacing__expr);
    d.correct = DebugStringForField(o_word_spacing__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_color__expr = inherited_data_->internal_visited_color_;
  const auto& o_internal_visited_color__expr = o.inherited_data_->internal_visited_color_;
  if (!(internal_visited_color__expr == o_internal_visited_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_color_;
    d.actual = DebugStringForField(internal_visited_color__expr);
    d.correct = DebugStringForField(o_internal_visited_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& color__expr = inherited_data_->color_;
  const auto& o_color__expr = o.inherited_data_->color_;
  if (!(color__expr == o_color__expr)) {
    DebugDiff d;
    d.field = DebugField::color_;
    d.actual = DebugStringForField(color__expr);
    d.correct = DebugStringForField(o_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& horizontal_border_spacing__expr = inherited_data_->horizontal_border_spacing_;
  const auto& o_horizontal_border_spacing__expr = o.inherited_data_->horizontal_border_spacing_;
  if (!(horizontal_border_spacing__expr == o_horizontal_border_spacing__expr)) {
    DebugDiff d;
    d.field = DebugField::horizontal_border_spacing_;
    d.actual = DebugStringForField(horizontal_border_spacing__expr);
    d.correct = DebugStringForField(o_horizontal_border_spacing__expr);
    diff.push_back(std::move(d));
  }
  const auto& vertical_border_spacing__expr = inherited_data_->vertical_border_spacing_;
  const auto& o_vertical_border_spacing__expr = o.inherited_data_->vertical_border_spacing_;
  if (!(vertical_border_spacing__expr == o_vertical_border_spacing__expr)) {
    DebugDiff d;
    d.field = DebugField::vertical_border_spacing_;
    d.actual = DebugStringForField(vertical_border_spacing__expr);
    d.correct = DebugStringForField(o_vertical_border_spacing__expr);
    diff.push_back(std::move(d));
  }
  const auto& cursor__expr = inherited_data_->cursor_;
  const auto& o_cursor__expr = o.inherited_data_->cursor_;
  if (!(cursor__expr == o_cursor__expr)) {
    DebugDiff d;
    d.field = DebugField::cursor_;
    d.actual = DebugStringForField(cursor__expr);
    d.correct = DebugStringForField(o_cursor__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_transform__expr = inherited_data_->text_transform_;
  const auto& o_text_transform__expr = o.inherited_data_->text_transform_;
  if (!(text_transform__expr == o_text_transform__expr)) {
    DebugDiff d;
    d.field = DebugField::text_transform_;
    d.actual = DebugStringForField(text_transform__expr);
    d.correct = DebugStringForField(o_text_transform__expr);
    diff.push_back(std::move(d));
  }
  const auto& color_is_current_color__expr = inherited_data_->color_is_current_color_;
  const auto& o_color_is_current_color__expr = o.inherited_data_->color_is_current_color_;
  if (!(color_is_current_color__expr == o_color_is_current_color__expr)) {
    DebugDiff d;
    d.field = DebugField::color_is_current_color_;
    d.actual = DebugStringForField(color_is_current_color__expr);
    d.correct = DebugStringForField(o_color_is_current_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& in_forced_colors_mode__expr = inherited_data_->in_forced_colors_mode_;
  const auto& o_in_forced_colors_mode__expr = o.inherited_data_->in_forced_colors_mode_;
  if (!(in_forced_colors_mode__expr == o_in_forced_colors_mode__expr)) {
    DebugDiff d;
    d.field = DebugField::in_forced_colors_mode_;
    d.actual = DebugStringForField(in_forced_colors_mode__expr);
    d.correct = DebugStringForField(o_in_forced_colors_mode__expr);
    diff.push_back(std::move(d));
  }
  const auto& internal_visited_color_is_current_color__expr = inherited_data_->internal_visited_color_is_current_color_;
  const auto& o_internal_visited_color_is_current_color__expr = o.inherited_data_->internal_visited_color_is_current_color_;
  if (!(internal_visited_color_is_current_color__expr == o_internal_visited_color_is_current_color__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_color_is_current_color_;
    d.actual = DebugStringForField(internal_visited_color_is_current_color__expr);
    d.correct = DebugStringForField(o_internal_visited_color_is_current_color__expr);
    diff.push_back(std::move(d));
  }

    // Group: visual
  const auto& base_text_decoration_data__expr = visual_data_->base_text_decoration_data_;
  const auto& o_base_text_decoration_data__expr = o.visual_data_->base_text_decoration_data_;
  if (!(base::ValuesEquivalent(base_text_decoration_data__expr, o_base_text_decoration_data__expr))) {
    DebugDiff d;
    d.field = DebugField::base_text_decoration_data_;
    d.actual = DebugStringForField(base_text_decoration_data__expr);
    d.correct = DebugStringForField(o_base_text_decoration_data__expr);
    diff.push_back(std::move(d));
  }
  const auto& clip__expr = visual_data_->clip_;
  const auto& o_clip__expr = o.visual_data_->clip_;
  if (!(clip__expr == o_clip__expr)) {
    DebugDiff d;
    d.field = DebugField::clip_;
    d.actual = DebugStringForField(clip__expr);
    d.correct = DebugStringForField(o_clip__expr);
    diff.push_back(std::move(d));
  }
  const auto& zoom__expr = visual_data_->zoom_;
  const auto& o_zoom__expr = o.visual_data_->zoom_;
  if (!(zoom__expr == o_zoom__expr)) {
    DebugDiff d;
    d.field = DebugField::zoom_;
    d.actual = DebugStringForField(zoom__expr);
    d.correct = DebugStringForField(o_zoom__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_decoration_line__expr = visual_data_->text_decoration_line_;
  const auto& o_text_decoration_line__expr = o.visual_data_->text_decoration_line_;
  if (!(text_decoration_line__expr == o_text_decoration_line__expr)) {
    DebugDiff d;
    d.field = DebugField::text_decoration_line_;
    d.actual = DebugStringForField(text_decoration_line__expr);
    d.correct = DebugStringForField(o_text_decoration_line__expr);
    diff.push_back(std::move(d));
  }
  const auto& field_sizing__expr = visual_data_->field_sizing_;
  const auto& o_field_sizing__expr = o.visual_data_->field_sizing_;
  if (!(field_sizing__expr == o_field_sizing__expr)) {
    DebugDiff d;
    d.field = DebugField::field_sizing_;
    d.actual = DebugStringForField(field_sizing__expr);
    d.correct = DebugStringForField(o_field_sizing__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_auto_clip__expr = visual_data_->has_auto_clip_;
  const auto& o_has_auto_clip__expr = o.visual_data_->has_auto_clip_;
  if (!(has_auto_clip__expr == o_has_auto_clip__expr)) {
    DebugDiff d;
    d.field = DebugField::has_auto_clip_;
    d.actual = DebugStringForField(has_auto_clip__expr);
    d.correct = DebugStringForField(o_has_auto_clip__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_clip_path__expr = visual_data_->has_clip_path_;
  const auto& o_has_clip_path__expr = o.visual_data_->has_clip_path_;
  if (!(has_clip_path__expr == o_has_clip_path__expr)) {
    DebugDiff d;
    d.field = DebugField::has_clip_path_;
    d.actual = DebugStringForField(has_clip_path__expr);
    d.correct = DebugStringForField(o_has_clip_path__expr);
    diff.push_back(std::move(d));
  }
  const auto& maybe_has_gap_decorations__expr = visual_data_->maybe_has_gap_decorations_;
  const auto& o_maybe_has_gap_decorations__expr = o.visual_data_->maybe_has_gap_decorations_;
  if (!(maybe_has_gap_decorations__expr == o_maybe_has_gap_decorations__expr)) {
    DebugDiff d;
    d.field = DebugField::maybe_has_gap_decorations_;
    d.actual = DebugStringForField(maybe_has_gap_decorations__expr);
    d.correct = DebugStringForField(o_maybe_has_gap_decorations__expr);
    diff.push_back(std::move(d));
  }

      // Group: fill
  const auto& internal_visited_fill_paint__expr = svginherited_data_->fill_data_->internal_visited_fill_paint_;
  const auto& o_internal_visited_fill_paint__expr = o.svginherited_data_->fill_data_->internal_visited_fill_paint_;
  if (!(internal_visited_fill_paint__expr == o_internal_visited_fill_paint__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_fill_paint_;
    d.actual = DebugStringForField(internal_visited_fill_paint__expr);
    d.correct = DebugStringForField(o_internal_visited_fill_paint__expr);
    diff.push_back(std::move(d));
  }
  const auto& fill_paint__expr = svginherited_data_->fill_data_->fill_paint_;
  const auto& o_fill_paint__expr = o.svginherited_data_->fill_data_->fill_paint_;
  if (!(fill_paint__expr == o_fill_paint__expr)) {
    DebugDiff d;
    d.field = DebugField::fill_paint_;
    d.actual = DebugStringForField(fill_paint__expr);
    d.correct = DebugStringForField(o_fill_paint__expr);
    diff.push_back(std::move(d));
  }
  const auto& fill_opacity__expr = svginherited_data_->fill_data_->fill_opacity_;
  const auto& o_fill_opacity__expr = o.svginherited_data_->fill_data_->fill_opacity_;
  if (!(fill_opacity__expr == o_fill_opacity__expr)) {
    DebugDiff d;
    d.field = DebugField::fill_opacity_;
    d.actual = DebugStringForField(fill_opacity__expr);
    d.correct = DebugStringForField(o_fill_opacity__expr);
    diff.push_back(std::move(d));
  }

    // Group: stroke
  const auto& internal_visited_stroke_paint__expr = svginherited_data_->stroke_data_->internal_visited_stroke_paint_;
  const auto& o_internal_visited_stroke_paint__expr = o.svginherited_data_->stroke_data_->internal_visited_stroke_paint_;
  if (!(internal_visited_stroke_paint__expr == o_internal_visited_stroke_paint__expr)) {
    DebugDiff d;
    d.field = DebugField::internal_visited_stroke_paint_;
    d.actual = DebugStringForField(internal_visited_stroke_paint__expr);
    d.correct = DebugStringForField(o_internal_visited_stroke_paint__expr);
    diff.push_back(std::move(d));
  }
  const auto& stroke_paint__expr = svginherited_data_->stroke_data_->stroke_paint_;
  const auto& o_stroke_paint__expr = o.svginherited_data_->stroke_data_->stroke_paint_;
  if (!(stroke_paint__expr == o_stroke_paint__expr)) {
    DebugDiff d;
    d.field = DebugField::stroke_paint_;
    d.actual = DebugStringForField(stroke_paint__expr);
    d.correct = DebugStringForField(o_stroke_paint__expr);
    diff.push_back(std::move(d));
  }
  const auto& stroke_dash_array__expr = svginherited_data_->stroke_data_->stroke_dash_array_;
  const auto& o_stroke_dash_array__expr = o.svginherited_data_->stroke_data_->stroke_dash_array_;
  if (!(base::ValuesEquivalent(stroke_dash_array__expr, o_stroke_dash_array__expr))) {
    DebugDiff d;
    d.field = DebugField::stroke_dash_array_;
    d.actual = DebugStringForField(stroke_dash_array__expr);
    d.correct = DebugStringForField(o_stroke_dash_array__expr);
    diff.push_back(std::move(d));
  }
  const auto& stroke_dash_offset__expr = svginherited_data_->stroke_data_->stroke_dash_offset_;
  const auto& o_stroke_dash_offset__expr = o.svginherited_data_->stroke_data_->stroke_dash_offset_;
  if (!(stroke_dash_offset__expr == o_stroke_dash_offset__expr)) {
    DebugDiff d;
    d.field = DebugField::stroke_dash_offset_;
    d.actual = DebugStringForField(stroke_dash_offset__expr);
    d.correct = DebugStringForField(o_stroke_dash_offset__expr);
    diff.push_back(std::move(d));
  }
  const auto& stroke_width__expr = svginherited_data_->stroke_data_->stroke_width_;
  const auto& o_stroke_width__expr = o.svginherited_data_->stroke_data_->stroke_width_;
  if (!(stroke_width__expr == o_stroke_width__expr)) {
    DebugDiff d;
    d.field = DebugField::stroke_width_;
    d.actual = DebugStringForField(stroke_width__expr);
    d.correct = DebugStringForField(o_stroke_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& stroke_miter_limit__expr = svginherited_data_->stroke_data_->stroke_miter_limit_;
  const auto& o_stroke_miter_limit__expr = o.svginherited_data_->stroke_data_->stroke_miter_limit_;
  if (!(stroke_miter_limit__expr == o_stroke_miter_limit__expr)) {
    DebugDiff d;
    d.field = DebugField::stroke_miter_limit_;
    d.actual = DebugStringForField(stroke_miter_limit__expr);
    d.correct = DebugStringForField(o_stroke_miter_limit__expr);
    diff.push_back(std::move(d));
  }
  const auto& stroke_opacity__expr = svginherited_data_->stroke_data_->stroke_opacity_;
  const auto& o_stroke_opacity__expr = o.svginherited_data_->stroke_data_->stroke_opacity_;
  if (!(stroke_opacity__expr == o_stroke_opacity__expr)) {
    DebugDiff d;
    d.field = DebugField::stroke_opacity_;
    d.actual = DebugStringForField(stroke_opacity__expr);
    d.correct = DebugStringForField(o_stroke_opacity__expr);
    diff.push_back(std::move(d));
  }
  const auto& cap_style__expr = svginherited_data_->stroke_data_->cap_style_;
  const auto& o_cap_style__expr = o.svginherited_data_->stroke_data_->cap_style_;
  if (!(cap_style__expr == o_cap_style__expr)) {
    DebugDiff d;
    d.field = DebugField::cap_style_;
    d.actual = DebugStringForField(cap_style__expr);
    d.correct = DebugStringForField(o_cap_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& join_style__expr = svginherited_data_->stroke_data_->join_style_;
  const auto& o_join_style__expr = o.svginherited_data_->stroke_data_->join_style_;
  if (!(join_style__expr == o_join_style__expr)) {
    DebugDiff d;
    d.field = DebugField::join_style_;
    d.actual = DebugStringForField(join_style__expr);
    d.correct = DebugStringForField(o_join_style__expr);
    diff.push_back(std::move(d));
  }

    // Group: resources
  const auto& marker_end_resource__expr = svginherited_data_->resources_data_->marker_end_resource_;
  const auto& o_marker_end_resource__expr = o.svginherited_data_->resources_data_->marker_end_resource_;
  if (!(base::ValuesEquivalent(marker_end_resource__expr, o_marker_end_resource__expr))) {
    DebugDiff d;
    d.field = DebugField::marker_end_resource_;
    d.actual = DebugStringForField(marker_end_resource__expr);
    d.correct = DebugStringForField(o_marker_end_resource__expr);
    diff.push_back(std::move(d));
  }
  const auto& marker_mid_resource__expr = svginherited_data_->resources_data_->marker_mid_resource_;
  const auto& o_marker_mid_resource__expr = o.svginherited_data_->resources_data_->marker_mid_resource_;
  if (!(base::ValuesEquivalent(marker_mid_resource__expr, o_marker_mid_resource__expr))) {
    DebugDiff d;
    d.field = DebugField::marker_mid_resource_;
    d.actual = DebugStringForField(marker_mid_resource__expr);
    d.correct = DebugStringForField(o_marker_mid_resource__expr);
    diff.push_back(std::move(d));
  }
  const auto& marker_start_resource__expr = svginherited_data_->resources_data_->marker_start_resource_;
  const auto& o_marker_start_resource__expr = o.svginherited_data_->resources_data_->marker_start_resource_;
  if (!(base::ValuesEquivalent(marker_start_resource__expr, o_marker_start_resource__expr))) {
    DebugDiff d;
    d.field = DebugField::marker_start_resource_;
    d.actual = DebugStringForField(marker_start_resource__expr);
    d.correct = DebugStringForField(o_marker_start_resource__expr);
    diff.push_back(std::move(d));
  }

  // Group: svginherited
  const auto& css_dominant_baseline__expr = svginherited_data_->css_dominant_baseline_;
  const auto& o_css_dominant_baseline__expr = o.svginherited_data_->css_dominant_baseline_;
  if (!(css_dominant_baseline__expr == o_css_dominant_baseline__expr)) {
    DebugDiff d;
    d.field = DebugField::css_dominant_baseline_;
    d.actual = DebugStringForField(css_dominant_baseline__expr);
    d.correct = DebugStringForField(o_css_dominant_baseline__expr);
    diff.push_back(std::move(d));
  }
  const auto& dominant_baseline__expr = svginherited_data_->dominant_baseline_;
  const auto& o_dominant_baseline__expr = o.svginherited_data_->dominant_baseline_;
  if (!(dominant_baseline__expr == o_dominant_baseline__expr)) {
    DebugDiff d;
    d.field = DebugField::dominant_baseline_;
    d.actual = DebugStringForField(dominant_baseline__expr);
    d.correct = DebugStringForField(o_dominant_baseline__expr);
    diff.push_back(std::move(d));
  }
  const auto& paint_order__expr = svginherited_data_->paint_order_;
  const auto& o_paint_order__expr = o.svginherited_data_->paint_order_;
  if (!(paint_order__expr == o_paint_order__expr)) {
    DebugDiff d;
    d.field = DebugField::paint_order_;
    d.actual = DebugStringForField(paint_order__expr);
    d.correct = DebugStringForField(o_paint_order__expr);
    diff.push_back(std::move(d));
  }
  const auto& color_interpolation__expr = svginherited_data_->color_interpolation_;
  const auto& o_color_interpolation__expr = o.svginherited_data_->color_interpolation_;
  if (!(color_interpolation__expr == o_color_interpolation__expr)) {
    DebugDiff d;
    d.field = DebugField::color_interpolation_;
    d.actual = DebugStringForField(color_interpolation__expr);
    d.correct = DebugStringForField(o_color_interpolation__expr);
    diff.push_back(std::move(d));
  }
  const auto& color_interpolation_filters__expr = svginherited_data_->color_interpolation_filters_;
  const auto& o_color_interpolation_filters__expr = o.svginherited_data_->color_interpolation_filters_;
  if (!(color_interpolation_filters__expr == o_color_interpolation_filters__expr)) {
    DebugDiff d;
    d.field = DebugField::color_interpolation_filters_;
    d.actual = DebugStringForField(color_interpolation_filters__expr);
    d.correct = DebugStringForField(o_color_interpolation_filters__expr);
    diff.push_back(std::move(d));
  }
  const auto& color_rendering__expr = svginherited_data_->color_rendering_;
  const auto& o_color_rendering__expr = o.svginherited_data_->color_rendering_;
  if (!(color_rendering__expr == o_color_rendering__expr)) {
    DebugDiff d;
    d.field = DebugField::color_rendering_;
    d.actual = DebugStringForField(color_rendering__expr);
    d.correct = DebugStringForField(o_color_rendering__expr);
    diff.push_back(std::move(d));
  }
  const auto& shape_rendering__expr = svginherited_data_->shape_rendering_;
  const auto& o_shape_rendering__expr = o.svginherited_data_->shape_rendering_;
  if (!(shape_rendering__expr == o_shape_rendering__expr)) {
    DebugDiff d;
    d.field = DebugField::shape_rendering_;
    d.actual = DebugStringForField(shape_rendering__expr);
    d.correct = DebugStringForField(o_shape_rendering__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_anchor__expr = svginherited_data_->text_anchor_;
  const auto& o_text_anchor__expr = o.svginherited_data_->text_anchor_;
  if (!(text_anchor__expr == o_text_anchor__expr)) {
    DebugDiff d;
    d.field = DebugField::text_anchor_;
    d.actual = DebugStringForField(text_anchor__expr);
    d.correct = DebugStringForField(o_text_anchor__expr);
    diff.push_back(std::move(d));
  }
  const auto& clip_rule__expr = svginherited_data_->clip_rule_;
  const auto& o_clip_rule__expr = o.svginherited_data_->clip_rule_;
  if (!(clip_rule__expr == o_clip_rule__expr)) {
    DebugDiff d;
    d.field = DebugField::clip_rule_;
    d.actual = DebugStringForField(clip_rule__expr);
    d.correct = DebugStringForField(o_clip_rule__expr);
    diff.push_back(std::move(d));
  }
  const auto& fill_rule__expr = svginherited_data_->fill_rule_;
  const auto& o_fill_rule__expr = o.svginherited_data_->fill_rule_;
  if (!(fill_rule__expr == o_fill_rule__expr)) {
    DebugDiff d;
    d.field = DebugField::fill_rule_;
    d.actual = DebugStringForField(fill_rule__expr);
    d.correct = DebugStringForField(o_fill_rule__expr);
    diff.push_back(std::move(d));
  }

    // Group: box
  const auto& overflow_clip_margin__expr = box_data_->overflow_clip_margin_;
  const auto& o_overflow_clip_margin__expr = o.box_data_->overflow_clip_margin_;
  if (!(overflow_clip_margin__expr == o_overflow_clip_margin__expr)) {
    DebugDiff d;
    d.field = DebugField::overflow_clip_margin_;
    d.actual = DebugStringForField(overflow_clip_margin__expr);
    d.correct = DebugStringForField(o_overflow_clip_margin__expr);
    diff.push_back(std::move(d));
  }
  const auto& height__expr = box_data_->height_;
  const auto& o_height__expr = o.box_data_->height_;
  if (!(height__expr == o_height__expr)) {
    DebugDiff d;
    d.field = DebugField::height_;
    d.actual = DebugStringForField(height__expr);
    d.correct = DebugStringForField(o_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& margin_bottom__expr = box_data_->margin_bottom_;
  const auto& o_margin_bottom__expr = o.box_data_->margin_bottom_;
  if (!(margin_bottom__expr == o_margin_bottom__expr)) {
    DebugDiff d;
    d.field = DebugField::margin_bottom_;
    d.actual = DebugStringForField(margin_bottom__expr);
    d.correct = DebugStringForField(o_margin_bottom__expr);
    diff.push_back(std::move(d));
  }
  const auto& margin_left__expr = box_data_->margin_left_;
  const auto& o_margin_left__expr = o.box_data_->margin_left_;
  if (!(margin_left__expr == o_margin_left__expr)) {
    DebugDiff d;
    d.field = DebugField::margin_left_;
    d.actual = DebugStringForField(margin_left__expr);
    d.correct = DebugStringForField(o_margin_left__expr);
    diff.push_back(std::move(d));
  }
  const auto& margin_right__expr = box_data_->margin_right_;
  const auto& o_margin_right__expr = o.box_data_->margin_right_;
  if (!(margin_right__expr == o_margin_right__expr)) {
    DebugDiff d;
    d.field = DebugField::margin_right_;
    d.actual = DebugStringForField(margin_right__expr);
    d.correct = DebugStringForField(o_margin_right__expr);
    diff.push_back(std::move(d));
  }
  const auto& margin_top__expr = box_data_->margin_top_;
  const auto& o_margin_top__expr = o.box_data_->margin_top_;
  if (!(margin_top__expr == o_margin_top__expr)) {
    DebugDiff d;
    d.field = DebugField::margin_top_;
    d.actual = DebugStringForField(margin_top__expr);
    d.correct = DebugStringForField(o_margin_top__expr);
    diff.push_back(std::move(d));
  }
  const auto& max_height__expr = box_data_->max_height_;
  const auto& o_max_height__expr = o.box_data_->max_height_;
  if (!(max_height__expr == o_max_height__expr)) {
    DebugDiff d;
    d.field = DebugField::max_height_;
    d.actual = DebugStringForField(max_height__expr);
    d.correct = DebugStringForField(o_max_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& max_width__expr = box_data_->max_width_;
  const auto& o_max_width__expr = o.box_data_->max_width_;
  if (!(max_width__expr == o_max_width__expr)) {
    DebugDiff d;
    d.field = DebugField::max_width_;
    d.actual = DebugStringForField(max_width__expr);
    d.correct = DebugStringForField(o_max_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& min_height__expr = box_data_->min_height_;
  const auto& o_min_height__expr = o.box_data_->min_height_;
  if (!(min_height__expr == o_min_height__expr)) {
    DebugDiff d;
    d.field = DebugField::min_height_;
    d.actual = DebugStringForField(min_height__expr);
    d.correct = DebugStringForField(o_min_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& min_width__expr = box_data_->min_width_;
  const auto& o_min_width__expr = o.box_data_->min_width_;
  if (!(min_width__expr == o_min_width__expr)) {
    DebugDiff d;
    d.field = DebugField::min_width_;
    d.actual = DebugStringForField(min_width__expr);
    d.correct = DebugStringForField(o_min_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& padding_bottom__expr = box_data_->padding_bottom_;
  const auto& o_padding_bottom__expr = o.box_data_->padding_bottom_;
  if (!(padding_bottom__expr == o_padding_bottom__expr)) {
    DebugDiff d;
    d.field = DebugField::padding_bottom_;
    d.actual = DebugStringForField(padding_bottom__expr);
    d.correct = DebugStringForField(o_padding_bottom__expr);
    diff.push_back(std::move(d));
  }
  const auto& padding_left__expr = box_data_->padding_left_;
  const auto& o_padding_left__expr = o.box_data_->padding_left_;
  if (!(padding_left__expr == o_padding_left__expr)) {
    DebugDiff d;
    d.field = DebugField::padding_left_;
    d.actual = DebugStringForField(padding_left__expr);
    d.correct = DebugStringForField(o_padding_left__expr);
    diff.push_back(std::move(d));
  }
  const auto& padding_right__expr = box_data_->padding_right_;
  const auto& o_padding_right__expr = o.box_data_->padding_right_;
  if (!(padding_right__expr == o_padding_right__expr)) {
    DebugDiff d;
    d.field = DebugField::padding_right_;
    d.actual = DebugStringForField(padding_right__expr);
    d.correct = DebugStringForField(o_padding_right__expr);
    diff.push_back(std::move(d));
  }
  const auto& padding_top__expr = box_data_->padding_top_;
  const auto& o_padding_top__expr = o.box_data_->padding_top_;
  if (!(padding_top__expr == o_padding_top__expr)) {
    DebugDiff d;
    d.field = DebugField::padding_top_;
    d.actual = DebugStringForField(padding_top__expr);
    d.correct = DebugStringForField(o_padding_top__expr);
    diff.push_back(std::move(d));
  }
  const auto& width__expr = box_data_->width_;
  const auto& o_width__expr = o.box_data_->width_;
  if (!(width__expr == o_width__expr)) {
    DebugDiff d;
    d.field = DebugField::width_;
    d.actual = DebugStringForField(width__expr);
    d.correct = DebugStringForField(o_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& vertical_align_length__expr = box_data_->vertical_align_length_;
  const auto& o_vertical_align_length__expr = o.box_data_->vertical_align_length_;
  if (!(vertical_align_length__expr == o_vertical_align_length__expr)) {
    DebugDiff d;
    d.field = DebugField::vertical_align_length_;
    d.actual = DebugStringForField(vertical_align_length__expr);
    d.correct = DebugStringForField(o_vertical_align_length__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_bottom_width__expr = box_data_->border_bottom_width_;
  const auto& o_border_bottom_width__expr = o.box_data_->border_bottom_width_;
  if (!(border_bottom_width__expr == o_border_bottom_width__expr)) {
    DebugDiff d;
    d.field = DebugField::border_bottom_width_;
    d.actual = DebugStringForField(border_bottom_width__expr);
    d.correct = DebugStringForField(o_border_bottom_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_left_width__expr = box_data_->border_left_width_;
  const auto& o_border_left_width__expr = o.box_data_->border_left_width_;
  if (!(border_left_width__expr == o_border_left_width__expr)) {
    DebugDiff d;
    d.field = DebugField::border_left_width_;
    d.actual = DebugStringForField(border_left_width__expr);
    d.correct = DebugStringForField(o_border_left_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_right_width__expr = box_data_->border_right_width_;
  const auto& o_border_right_width__expr = o.box_data_->border_right_width_;
  if (!(border_right_width__expr == o_border_right_width__expr)) {
    DebugDiff d;
    d.field = DebugField::border_right_width_;
    d.actual = DebugStringForField(border_right_width__expr);
    d.correct = DebugStringForField(o_border_right_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_top_width__expr = box_data_->border_top_width_;
  const auto& o_border_top_width__expr = o.box_data_->border_top_width_;
  if (!(border_top_width__expr == o_border_top_width__expr)) {
    DebugDiff d;
    d.field = DebugField::border_top_width_;
    d.actual = DebugStringForField(border_top_width__expr);
    d.correct = DebugStringForField(o_border_top_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& z_index__expr = box_data_->z_index_;
  const auto& o_z_index__expr = o.box_data_->z_index_;
  if (!(z_index__expr == o_z_index__expr)) {
    DebugDiff d;
    d.field = DebugField::z_index_;
    d.actual = DebugStringForField(z_index__expr);
    d.correct = DebugStringForField(o_z_index__expr);
    diff.push_back(std::move(d));
  }
  const auto& align_items__expr = box_data_->align_items_;
  const auto& o_align_items__expr = o.box_data_->align_items_;
  if (!(align_items__expr == o_align_items__expr)) {
    DebugDiff d;
    d.field = DebugField::align_items_;
    d.actual = DebugStringForField(align_items__expr);
    d.correct = DebugStringForField(o_align_items__expr);
    diff.push_back(std::move(d));
  }
  const auto& justify_content__expr = box_data_->justify_content_;
  const auto& o_justify_content__expr = o.box_data_->justify_content_;
  if (!(justify_content__expr == o_justify_content__expr)) {
    DebugDiff d;
    d.field = DebugField::justify_content_;
    d.actual = DebugStringForField(justify_content__expr);
    d.correct = DebugStringForField(o_justify_content__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_bottom_style__expr = box_data_->border_bottom_style_;
  const auto& o_border_bottom_style__expr = o.box_data_->border_bottom_style_;
  if (!(border_bottom_style__expr == o_border_bottom_style__expr)) {
    DebugDiff d;
    d.field = DebugField::border_bottom_style_;
    d.actual = DebugStringForField(border_bottom_style__expr);
    d.correct = DebugStringForField(o_border_bottom_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_left_style__expr = box_data_->border_left_style_;
  const auto& o_border_left_style__expr = o.box_data_->border_left_style_;
  if (!(border_left_style__expr == o_border_left_style__expr)) {
    DebugDiff d;
    d.field = DebugField::border_left_style_;
    d.actual = DebugStringForField(border_left_style__expr);
    d.correct = DebugStringForField(o_border_left_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_right_style__expr = box_data_->border_right_style_;
  const auto& o_border_right_style__expr = o.box_data_->border_right_style_;
  if (!(border_right_style__expr == o_border_right_style__expr)) {
    DebugDiff d;
    d.field = DebugField::border_right_style_;
    d.actual = DebugStringForField(border_right_style__expr);
    d.correct = DebugStringForField(o_border_right_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_top_style__expr = box_data_->border_top_style_;
  const auto& o_border_top_style__expr = o.box_data_->border_top_style_;
  if (!(border_top_style__expr == o_border_top_style__expr)) {
    DebugDiff d;
    d.field = DebugField::border_top_style_;
    d.actual = DebugStringForField(border_top_style__expr);
    d.correct = DebugStringForField(o_border_top_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& baseline_source__expr = box_data_->baseline_source_;
  const auto& o_baseline_source__expr = o.box_data_->baseline_source_;
  if (!(baseline_source__expr == o_baseline_source__expr)) {
    DebugDiff d;
    d.field = DebugField::baseline_source_;
    d.actual = DebugStringForField(baseline_source__expr);
    d.correct = DebugStringForField(o_baseline_source__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_box_trim__expr = box_data_->text_box_trim_;
  const auto& o_text_box_trim__expr = o.box_data_->text_box_trim_;
  if (!(text_box_trim__expr == o_text_box_trim__expr)) {
    DebugDiff d;
    d.field = DebugField::text_box_trim_;
    d.actual = DebugStringForField(text_box_trim__expr);
    d.correct = DebugStringForField(o_text_box_trim__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_decoration_break__expr = box_data_->box_decoration_break_;
  const auto& o_box_decoration_break__expr = o.box_data_->box_decoration_break_;
  if (!(box_decoration_break__expr == o_box_decoration_break__expr)) {
    DebugDiff d;
    d.field = DebugField::box_decoration_break_;
    d.actual = DebugStringForField(box_decoration_break__expr);
    d.correct = DebugStringForField(o_box_decoration_break__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_auto_z_index__expr = box_data_->has_auto_z_index_;
  const auto& o_has_auto_z_index__expr = o.box_data_->has_auto_z_index_;
  if (!(has_auto_z_index__expr == o_has_auto_z_index__expr)) {
    DebugDiff d;
    d.field = DebugField::has_auto_z_index_;
    d.actual = DebugStringForField(has_auto_z_index__expr);
    d.correct = DebugStringForField(o_has_auto_z_index__expr);
    diff.push_back(std::move(d));
  }

      // Group: svgmisc
  const auto& baseline_shift__expr = svg_data_->svgmisc_data_->baseline_shift_;
  const auto& o_baseline_shift__expr = o.svg_data_->svgmisc_data_->baseline_shift_;
  if (!(baseline_shift__expr == o_baseline_shift__expr)) {
    DebugDiff d;
    d.field = DebugField::baseline_shift_;
    d.actual = DebugStringForField(baseline_shift__expr);
    d.correct = DebugStringForField(o_baseline_shift__expr);
    diff.push_back(std::move(d));
  }
  const auto& flood_opacity__expr = svg_data_->svgmisc_data_->flood_opacity_;
  const auto& o_flood_opacity__expr = o.svg_data_->svgmisc_data_->flood_opacity_;
  if (!(flood_opacity__expr == o_flood_opacity__expr)) {
    DebugDiff d;
    d.field = DebugField::flood_opacity_;
    d.actual = DebugStringForField(flood_opacity__expr);
    d.correct = DebugStringForField(o_flood_opacity__expr);
    diff.push_back(std::move(d));
  }
  const auto& flood_color__expr = svg_data_->svgmisc_data_->flood_color_;
  const auto& o_flood_color__expr = o.svg_data_->svgmisc_data_->flood_color_;
  if (!(flood_color__expr == o_flood_color__expr)) {
    DebugDiff d;
    d.field = DebugField::flood_color_;
    d.actual = DebugStringForField(flood_color__expr);
    d.correct = DebugStringForField(o_flood_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& lighting_color__expr = svg_data_->svgmisc_data_->lighting_color_;
  const auto& o_lighting_color__expr = o.svg_data_->svgmisc_data_->lighting_color_;
  if (!(lighting_color__expr == o_lighting_color__expr)) {
    DebugDiff d;
    d.field = DebugField::lighting_color_;
    d.actual = DebugStringForField(lighting_color__expr);
    d.correct = DebugStringForField(o_lighting_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& baseline_shift_type__expr = svg_data_->svgmisc_data_->baseline_shift_type_;
  const auto& o_baseline_shift_type__expr = o.svg_data_->svgmisc_data_->baseline_shift_type_;
  if (!(baseline_shift_type__expr == o_baseline_shift_type__expr)) {
    DebugDiff d;
    d.field = DebugField::baseline_shift_type_;
    d.actual = DebugStringForField(baseline_shift_type__expr);
    d.correct = DebugStringForField(o_baseline_shift_type__expr);
    diff.push_back(std::move(d));
  }

    // Group: geometry
  const auto& d__expr = svg_data_->geometry_data_->d_;
  const auto& o_d__expr = o.svg_data_->geometry_data_->d_;
  if (!(base::ValuesEquivalent(d__expr, o_d__expr))) {
    DebugDiff d;
    d.field = DebugField::d_;
    d.actual = DebugStringForField(d__expr);
    d.correct = DebugStringForField(o_d__expr);
    diff.push_back(std::move(d));
  }
  const auto& cx__expr = svg_data_->geometry_data_->cx_;
  const auto& o_cx__expr = o.svg_data_->geometry_data_->cx_;
  if (!(cx__expr == o_cx__expr)) {
    DebugDiff d;
    d.field = DebugField::cx_;
    d.actual = DebugStringForField(cx__expr);
    d.correct = DebugStringForField(o_cx__expr);
    diff.push_back(std::move(d));
  }
  const auto& cy__expr = svg_data_->geometry_data_->cy_;
  const auto& o_cy__expr = o.svg_data_->geometry_data_->cy_;
  if (!(cy__expr == o_cy__expr)) {
    DebugDiff d;
    d.field = DebugField::cy_;
    d.actual = DebugStringForField(cy__expr);
    d.correct = DebugStringForField(o_cy__expr);
    diff.push_back(std::move(d));
  }
  const auto& r__expr = svg_data_->geometry_data_->r_;
  const auto& o_r__expr = o.svg_data_->geometry_data_->r_;
  if (!(r__expr == o_r__expr)) {
    DebugDiff d;
    d.field = DebugField::r_;
    d.actual = DebugStringForField(r__expr);
    d.correct = DebugStringForField(o_r__expr);
    diff.push_back(std::move(d));
  }
  const auto& rx__expr = svg_data_->geometry_data_->rx_;
  const auto& o_rx__expr = o.svg_data_->geometry_data_->rx_;
  if (!(rx__expr == o_rx__expr)) {
    DebugDiff d;
    d.field = DebugField::rx_;
    d.actual = DebugStringForField(rx__expr);
    d.correct = DebugStringForField(o_rx__expr);
    diff.push_back(std::move(d));
  }
  const auto& ry__expr = svg_data_->geometry_data_->ry_;
  const auto& o_ry__expr = o.svg_data_->geometry_data_->ry_;
  if (!(ry__expr == o_ry__expr)) {
    DebugDiff d;
    d.field = DebugField::ry_;
    d.actual = DebugStringForField(ry__expr);
    d.correct = DebugStringForField(o_ry__expr);
    diff.push_back(std::move(d));
  }
  const auto& x__expr = svg_data_->geometry_data_->x_;
  const auto& o_x__expr = o.svg_data_->geometry_data_->x_;
  if (!(x__expr == o_x__expr)) {
    DebugDiff d;
    d.field = DebugField::x_;
    d.actual = DebugStringForField(x__expr);
    d.correct = DebugStringForField(o_x__expr);
    diff.push_back(std::move(d));
  }
  const auto& y__expr = svg_data_->geometry_data_->y_;
  const auto& o_y__expr = o.svg_data_->geometry_data_->y_;
  if (!(y__expr == o_y__expr)) {
    DebugDiff d;
    d.field = DebugField::y_;
    d.actual = DebugStringForField(y__expr);
    d.correct = DebugStringForField(o_y__expr);
    diff.push_back(std::move(d));
  }
  const auto& path_length__expr = svg_data_->geometry_data_->path_length_;
  const auto& o_path_length__expr = o.svg_data_->geometry_data_->path_length_;
  if (!(path_length__expr == o_path_length__expr)) {
    DebugDiff d;
    d.field = DebugField::path_length_;
    d.actual = DebugStringForField(path_length__expr);
    d.correct = DebugStringForField(o_path_length__expr);
    diff.push_back(std::move(d));
  }

    // Group: stop
  const auto& stop_opacity__expr = svg_data_->stop_data_->stop_opacity_;
  const auto& o_stop_opacity__expr = o.svg_data_->stop_data_->stop_opacity_;
  if (!(stop_opacity__expr == o_stop_opacity__expr)) {
    DebugDiff d;
    d.field = DebugField::stop_opacity_;
    d.actual = DebugStringForField(stop_opacity__expr);
    d.correct = DebugStringForField(o_stop_opacity__expr);
    diff.push_back(std::move(d));
  }
  const auto& stop_color__expr = svg_data_->stop_data_->stop_color_;
  const auto& o_stop_color__expr = o.svg_data_->stop_data_->stop_color_;
  if (!(stop_color__expr == o_stop_color__expr)) {
    DebugDiff d;
    d.field = DebugField::stop_color_;
    d.actual = DebugStringForField(stop_color__expr);
    d.correct = DebugStringForField(o_stop_color__expr);
    diff.push_back(std::move(d));
  }

  // Group: svg
  const auto& transform__expr = svg_data_->transform_;
  const auto& o_transform__expr = o.svg_data_->transform_;
  if (!(transform__expr == o_transform__expr)) {
    DebugDiff d;
    d.field = DebugField::transform_;
    d.actual = DebugStringForField(transform__expr);
    d.correct = DebugStringForField(o_transform__expr);
    diff.push_back(std::move(d));
  }
  const auto& transform_origin__expr = svg_data_->transform_origin_;
  const auto& o_transform_origin__expr = o.svg_data_->transform_origin_;
  if (!(transform_origin__expr == o_transform_origin__expr)) {
    DebugDiff d;
    d.field = DebugField::transform_origin_;
    d.actual = DebugStringForField(transform_origin__expr);
    d.correct = DebugStringForField(o_transform_origin__expr);
    diff.push_back(std::move(d));
  }
  const auto& opacity__expr = svg_data_->opacity_;
  const auto& o_opacity__expr = o.svg_data_->opacity_;
  if (!(opacity__expr == o_opacity__expr)) {
    DebugDiff d;
    d.field = DebugField::opacity_;
    d.actual = DebugStringForField(opacity__expr);
    d.correct = DebugStringForField(o_opacity__expr);
    diff.push_back(std::move(d));
  }
  const auto& alignment_baseline__expr = svg_data_->alignment_baseline_;
  const auto& o_alignment_baseline__expr = o.svg_data_->alignment_baseline_;
  if (!(alignment_baseline__expr == o_alignment_baseline__expr)) {
    DebugDiff d;
    d.field = DebugField::alignment_baseline_;
    d.actual = DebugStringForField(alignment_baseline__expr);
    d.correct = DebugStringForField(o_alignment_baseline__expr);
    diff.push_back(std::move(d));
  }
  const auto& buffered_rendering__expr = svg_data_->buffered_rendering_;
  const auto& o_buffered_rendering__expr = o.svg_data_->buffered_rendering_;
  if (!(buffered_rendering__expr == o_buffered_rendering__expr)) {
    DebugDiff d;
    d.field = DebugField::buffered_rendering_;
    d.actual = DebugStringForField(buffered_rendering__expr);
    d.correct = DebugStringForField(o_buffered_rendering__expr);
    diff.push_back(std::move(d));
  }
  const auto& mask_type__expr = svg_data_->mask_type_;
  const auto& o_mask_type__expr = o.svg_data_->mask_type_;
  if (!(mask_type__expr == o_mask_type__expr)) {
    DebugDiff d;
    d.field = DebugField::mask_type_;
    d.actual = DebugStringForField(mask_type__expr);
    d.correct = DebugStringForField(o_mask_type__expr);
    diff.push_back(std::move(d));
  }
  const auto& vector_effect__expr = svg_data_->vector_effect_;
  const auto& o_vector_effect__expr = o.svg_data_->vector_effect_;
  if (!(vector_effect__expr == o_vector_effect__expr)) {
    DebugDiff d;
    d.field = DebugField::vector_effect_;
    d.actual = DebugStringForField(vector_effect__expr);
    d.correct = DebugStringForField(o_vector_effect__expr);
    diff.push_back(std::move(d));
  }

    // Group: surround
  const auto& corner_bottom_left_shape__expr = surround_data_->corner_bottom_left_shape_;
  const auto& o_corner_bottom_left_shape__expr = o.surround_data_->corner_bottom_left_shape_;
  if (!(corner_bottom_left_shape__expr == o_corner_bottom_left_shape__expr)) {
    DebugDiff d;
    d.field = DebugField::corner_bottom_left_shape_;
    d.actual = DebugStringForField(corner_bottom_left_shape__expr);
    d.correct = DebugStringForField(o_corner_bottom_left_shape__expr);
    diff.push_back(std::move(d));
  }
  const auto& corner_bottom_right_shape__expr = surround_data_->corner_bottom_right_shape_;
  const auto& o_corner_bottom_right_shape__expr = o.surround_data_->corner_bottom_right_shape_;
  if (!(corner_bottom_right_shape__expr == o_corner_bottom_right_shape__expr)) {
    DebugDiff d;
    d.field = DebugField::corner_bottom_right_shape_;
    d.actual = DebugStringForField(corner_bottom_right_shape__expr);
    d.correct = DebugStringForField(o_corner_bottom_right_shape__expr);
    diff.push_back(std::move(d));
  }
  const auto& corner_top_left_shape__expr = surround_data_->corner_top_left_shape_;
  const auto& o_corner_top_left_shape__expr = o.surround_data_->corner_top_left_shape_;
  if (!(corner_top_left_shape__expr == o_corner_top_left_shape__expr)) {
    DebugDiff d;
    d.field = DebugField::corner_top_left_shape_;
    d.actual = DebugStringForField(corner_top_left_shape__expr);
    d.correct = DebugStringForField(o_corner_top_left_shape__expr);
    diff.push_back(std::move(d));
  }
  const auto& corner_top_right_shape__expr = surround_data_->corner_top_right_shape_;
  const auto& o_corner_top_right_shape__expr = o.surround_data_->corner_top_right_shape_;
  if (!(corner_top_right_shape__expr == o_corner_top_right_shape__expr)) {
    DebugDiff d;
    d.field = DebugField::corner_top_right_shape_;
    d.actual = DebugStringForField(corner_top_right_shape__expr);
    d.correct = DebugStringForField(o_corner_top_right_shape__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_image__expr = surround_data_->border_image_;
  const auto& o_border_image__expr = o.surround_data_->border_image_;
  if (!(border_image__expr == o_border_image__expr)) {
    DebugDiff d;
    d.field = DebugField::border_image_;
    d.actual = DebugStringForField(border_image__expr);
    d.correct = DebugStringForField(o_border_image__expr);
    diff.push_back(std::move(d));
  }
  const auto& aspect_ratio__expr = surround_data_->aspect_ratio_;
  const auto& o_aspect_ratio__expr = o.surround_data_->aspect_ratio_;
  if (!(aspect_ratio__expr == o_aspect_ratio__expr)) {
    DebugDiff d;
    d.field = DebugField::aspect_ratio_;
    d.actual = DebugStringForField(aspect_ratio__expr);
    d.correct = DebugStringForField(o_aspect_ratio__expr);
    diff.push_back(std::move(d));
  }
  const auto& contain_intrinsic_height__expr = surround_data_->contain_intrinsic_height_;
  const auto& o_contain_intrinsic_height__expr = o.surround_data_->contain_intrinsic_height_;
  if (!(contain_intrinsic_height__expr == o_contain_intrinsic_height__expr)) {
    DebugDiff d;
    d.field = DebugField::contain_intrinsic_height_;
    d.actual = DebugStringForField(contain_intrinsic_height__expr);
    d.correct = DebugStringForField(o_contain_intrinsic_height__expr);
    diff.push_back(std::move(d));
  }
  const auto& contain_intrinsic_width__expr = surround_data_->contain_intrinsic_width_;
  const auto& o_contain_intrinsic_width__expr = o.surround_data_->contain_intrinsic_width_;
  if (!(contain_intrinsic_width__expr == o_contain_intrinsic_width__expr)) {
    DebugDiff d;
    d.field = DebugField::contain_intrinsic_width_;
    d.actual = DebugStringForField(contain_intrinsic_width__expr);
    d.correct = DebugStringForField(o_contain_intrinsic_width__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_bottom_left_radius__expr = surround_data_->border_bottom_left_radius_;
  const auto& o_border_bottom_left_radius__expr = o.surround_data_->border_bottom_left_radius_;
  if (!(border_bottom_left_radius__expr == o_border_bottom_left_radius__expr)) {
    DebugDiff d;
    d.field = DebugField::border_bottom_left_radius_;
    d.actual = DebugStringForField(border_bottom_left_radius__expr);
    d.correct = DebugStringForField(o_border_bottom_left_radius__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_bottom_right_radius__expr = surround_data_->border_bottom_right_radius_;
  const auto& o_border_bottom_right_radius__expr = o.surround_data_->border_bottom_right_radius_;
  if (!(border_bottom_right_radius__expr == o_border_bottom_right_radius__expr)) {
    DebugDiff d;
    d.field = DebugField::border_bottom_right_radius_;
    d.actual = DebugStringForField(border_bottom_right_radius__expr);
    d.correct = DebugStringForField(o_border_bottom_right_radius__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_top_left_radius__expr = surround_data_->border_top_left_radius_;
  const auto& o_border_top_left_radius__expr = o.surround_data_->border_top_left_radius_;
  if (!(border_top_left_radius__expr == o_border_top_left_radius__expr)) {
    DebugDiff d;
    d.field = DebugField::border_top_left_radius_;
    d.actual = DebugStringForField(border_top_left_radius__expr);
    d.correct = DebugStringForField(o_border_top_left_radius__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_top_right_radius__expr = surround_data_->border_top_right_radius_;
  const auto& o_border_top_right_radius__expr = o.surround_data_->border_top_right_radius_;
  if (!(border_top_right_radius__expr == o_border_top_right_radius__expr)) {
    DebugDiff d;
    d.field = DebugField::border_top_right_radius_;
    d.actual = DebugStringForField(border_top_right_radius__expr);
    d.correct = DebugStringForField(o_border_top_right_radius__expr);
    diff.push_back(std::move(d));
  }
  const auto& bottom__expr = surround_data_->bottom_;
  const auto& o_bottom__expr = o.surround_data_->bottom_;
  if (!(bottom__expr == o_bottom__expr)) {
    DebugDiff d;
    d.field = DebugField::bottom_;
    d.actual = DebugStringForField(bottom__expr);
    d.correct = DebugStringForField(o_bottom__expr);
    diff.push_back(std::move(d));
  }
  const auto& left__expr = surround_data_->left_;
  const auto& o_left__expr = o.surround_data_->left_;
  if (!(left__expr == o_left__expr)) {
    DebugDiff d;
    d.field = DebugField::left_;
    d.actual = DebugStringForField(left__expr);
    d.correct = DebugStringForField(o_left__expr);
    diff.push_back(std::move(d));
  }
  const auto& right__expr = surround_data_->right_;
  const auto& o_right__expr = o.surround_data_->right_;
  if (!(right__expr == o_right__expr)) {
    DebugDiff d;
    d.field = DebugField::right_;
    d.actual = DebugStringForField(right__expr);
    d.correct = DebugStringForField(o_right__expr);
    diff.push_back(std::move(d));
  }
  const auto& top__expr = surround_data_->top_;
  const auto& o_top__expr = o.surround_data_->top_;
  if (!(top__expr == o_top__expr)) {
    DebugDiff d;
    d.field = DebugField::top_;
    d.actual = DebugStringForField(top__expr);
    d.correct = DebugStringForField(o_top__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_bottom_color__expr = surround_data_->border_bottom_color_;
  const auto& o_border_bottom_color__expr = o.surround_data_->border_bottom_color_;
  if (!(border_bottom_color__expr == o_border_bottom_color__expr)) {
    DebugDiff d;
    d.field = DebugField::border_bottom_color_;
    d.actual = DebugStringForField(border_bottom_color__expr);
    d.correct = DebugStringForField(o_border_bottom_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_left_color__expr = surround_data_->border_left_color_;
  const auto& o_border_left_color__expr = o.surround_data_->border_left_color_;
  if (!(border_left_color__expr == o_border_left_color__expr)) {
    DebugDiff d;
    d.field = DebugField::border_left_color_;
    d.actual = DebugStringForField(border_left_color__expr);
    d.correct = DebugStringForField(o_border_left_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_right_color__expr = surround_data_->border_right_color_;
  const auto& o_border_right_color__expr = o.surround_data_->border_right_color_;
  if (!(border_right_color__expr == o_border_right_color__expr)) {
    DebugDiff d;
    d.field = DebugField::border_right_color_;
    d.actual = DebugStringForField(border_right_color__expr);
    d.correct = DebugStringForField(o_border_right_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_top_color__expr = surround_data_->border_top_color_;
  const auto& o_border_top_color__expr = o.surround_data_->border_top_color_;
  if (!(border_top_color__expr == o_border_top_color__expr)) {
    DebugDiff d;
    d.field = DebugField::border_top_color_;
    d.actual = DebugStringForField(border_top_color__expr);
    d.correct = DebugStringForField(o_border_top_color__expr);
    diff.push_back(std::move(d));
  }
  const auto& frame_sizing__expr = surround_data_->frame_sizing_;
  const auto& o_frame_sizing__expr = o.surround_data_->frame_sizing_;
  if (!(frame_sizing__expr == o_frame_sizing__expr)) {
    DebugDiff d;
    d.field = DebugField::frame_sizing_;
    d.actual = DebugStringForField(frame_sizing__expr);
    d.correct = DebugStringForField(o_frame_sizing__expr);
    diff.push_back(std::move(d));
  }

    // Group: background
  const auto& background__expr = background_data_->background_;
  const auto& o_background__expr = o.background_data_->background_;
  if (!(background__expr == o_background__expr)) {
    DebugDiff d;
    d.field = DebugField::background_;
    d.actual = DebugStringForField(background__expr);
    d.correct = DebugStringForField(o_background__expr);
    diff.push_back(std::move(d));
  }
  const auto& background_color__expr = background_data_->background_color_;
  const auto& o_background_color__expr = o.background_data_->background_color_;
  if (!(background_color__expr == o_background_color__expr)) {
    DebugDiff d;
    d.field = DebugField::background_color_;
    d.actual = DebugStringForField(background_color__expr);
    d.correct = DebugStringForField(o_background_color__expr);
    diff.push_back(std::move(d));
  }

  // Group: None
  const auto& display__expr = data_.display_;
  const auto& o_display__expr = o.data_.display_;
  if (!(display__expr == o_display__expr)) {
    DebugDiff d;
    d.field = DebugField::display_;
    d.actual = DebugStringForField(display__expr);
    d.correct = DebugStringForField(o_display__expr);
    diff.push_back(std::move(d));
  }
  const auto& vertical_align__expr = data_.vertical_align_;
  const auto& o_vertical_align__expr = o.data_.vertical_align_;
  if (!(vertical_align__expr == o_vertical_align__expr)) {
    DebugDiff d;
    d.field = DebugField::vertical_align_;
    d.actual = DebugStringForField(vertical_align__expr);
    d.correct = DebugStringForField(o_vertical_align__expr);
    diff.push_back(std::move(d));
  }
  const auto& clear__expr = data_.clear_;
  const auto& o_clear__expr = o.data_.clear_;
  if (!(clear__expr == o_clear__expr)) {
    DebugDiff d;
    d.field = DebugField::clear_;
    d.actual = DebugStringForField(clear__expr);
    d.correct = DebugStringForField(o_clear__expr);
    diff.push_back(std::move(d));
  }
  const auto& floating__expr = data_.floating_;
  const auto& o_floating__expr = o.data_.floating_;
  if (!(floating__expr == o_floating__expr)) {
    DebugDiff d;
    d.field = DebugField::floating_;
    d.actual = DebugStringForField(floating__expr);
    d.correct = DebugStringForField(o_floating__expr);
    diff.push_back(std::move(d));
  }
  const auto& overflow_x__expr = data_.overflow_x_;
  const auto& o_overflow_x__expr = o.data_.overflow_x_;
  if (!(overflow_x__expr == o_overflow_x__expr)) {
    DebugDiff d;
    d.field = DebugField::overflow_x_;
    d.actual = DebugStringForField(overflow_x__expr);
    d.correct = DebugStringForField(o_overflow_x__expr);
    diff.push_back(std::move(d));
  }
  const auto& overflow_y__expr = data_.overflow_y_;
  const auto& o_overflow_y__expr = o.data_.overflow_y_;
  if (!(overflow_y__expr == o_overflow_y__expr)) {
    DebugDiff d;
    d.field = DebugField::overflow_y_;
    d.actual = DebugStringForField(overflow_y__expr);
    d.correct = DebugStringForField(o_overflow_y__expr);
    diff.push_back(std::move(d));
  }
  const auto& position__expr = data_.position_;
  const auto& o_position__expr = o.data_.position_;
  if (!(position__expr == o_position__expr)) {
    DebugDiff d;
    d.field = DebugField::position_;
    d.actual = DebugStringForField(position__expr);
    d.correct = DebugStringForField(o_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& transform_box__expr = data_.transform_box_;
  const auto& o_transform_box__expr = o.data_.transform_box_;
  if (!(transform_box__expr == o_transform_box__expr)) {
    DebugDiff d;
    d.field = DebugField::transform_box_;
    d.actual = DebugStringForField(transform_box__expr);
    d.correct = DebugStringForField(o_transform_box__expr);
    diff.push_back(std::move(d));
  }
  const auto& unicode_bidi__expr = data_.unicode_bidi_;
  const auto& o_unicode_bidi__expr = o.data_.unicode_bidi_;
  if (!(unicode_bidi__expr == o_unicode_bidi__expr)) {
    DebugDiff d;
    d.field = DebugField::unicode_bidi_;
    d.actual = DebugStringForField(unicode_bidi__expr);
    d.correct = DebugStringForField(o_unicode_bidi__expr);
    diff.push_back(std::move(d));
  }
  const auto& content_visibility__expr = data_.content_visibility_;
  const auto& o_content_visibility__expr = o.data_.content_visibility_;
  if (!(content_visibility__expr == o_content_visibility__expr)) {
    DebugDiff d;
    d.field = DebugField::content_visibility_;
    d.actual = DebugStringForField(content_visibility__expr);
    d.correct = DebugStringForField(o_content_visibility__expr);
    diff.push_back(std::move(d));
  }
  const auto& inline_block_baseline_edge__expr = data_.inline_block_baseline_edge_;
  const auto& o_inline_block_baseline_edge__expr = o.data_.inline_block_baseline_edge_;
  if (!(inline_block_baseline_edge__expr == o_inline_block_baseline_edge__expr)) {
    DebugDiff d;
    d.field = DebugField::inline_block_baseline_edge_;
    d.actual = DebugStringForField(inline_block_baseline_edge__expr);
    d.correct = DebugStringForField(o_inline_block_baseline_edge__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_stacking_context_without_containment__expr = IsStackingContextWithoutContainment();
  const auto& o_is_stacking_context_without_containment__expr = o.IsStackingContextWithoutContainment();
  if (!(is_stacking_context_without_containment__expr == o_is_stacking_context_without_containment__expr)) {
    DebugDiff d;
    d.field = DebugField::is_stacking_context_without_containment_;
    d.actual = DebugStringForField(is_stacking_context_without_containment__expr);
    d.correct = DebugStringForField(o_is_stacking_context_without_containment__expr);
    diff.push_back(std::move(d));
  }
  const auto& overflow_anchor__expr = data_.overflow_anchor_;
  const auto& o_overflow_anchor__expr = o.data_.overflow_anchor_;
  if (!(overflow_anchor__expr == o_overflow_anchor__expr)) {
    DebugDiff d;
    d.field = DebugField::overflow_anchor_;
    d.actual = DebugStringForField(overflow_anchor__expr);
    d.correct = DebugStringForField(o_overflow_anchor__expr);
    diff.push_back(std::move(d));
  }
  const auto& viewport_unit_flags__expr = data_.viewport_unit_flags_;
  const auto& o_viewport_unit_flags__expr = o.data_.viewport_unit_flags_;
  if (!(viewport_unit_flags__expr == o_viewport_unit_flags__expr)) {
    DebugDiff d;
    d.field = DebugField::viewport_unit_flags_;
    d.actual = DebugStringForField(viewport_unit_flags__expr);
    d.correct = DebugStringForField(o_viewport_unit_flags__expr);
    diff.push_back(std::move(d));
  }
  const auto& allows_z_index__expr = data_.allows_z_index_;
  const auto& o_allows_z_index__expr = o.data_.allows_z_index_;
  if (!(allows_z_index__expr == o_allows_z_index__expr)) {
    DebugDiff d;
    d.field = DebugField::allows_z_index_;
    d.actual = DebugStringForField(allows_z_index__expr);
    d.correct = DebugStringForField(o_allows_z_index__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_collapse_is_inherited__expr = data_.border_collapse_is_inherited_;
  const auto& o_border_collapse_is_inherited__expr = o.data_.border_collapse_is_inherited_;
  if (!(border_collapse_is_inherited__expr == o_border_collapse_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::border_collapse_is_inherited_;
    d.actual = DebugStringForField(border_collapse_is_inherited__expr);
    d.correct = DebugStringForField(o_border_collapse_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_direction__expr = data_.box_direction_;
  const auto& o_box_direction__expr = o.data_.box_direction_;
  if (!(box_direction__expr == o_box_direction__expr)) {
    DebugDiff d;
    d.field = DebugField::box_direction_;
    d.actual = DebugStringForField(box_direction__expr);
    d.correct = DebugStringForField(o_box_direction__expr);
    diff.push_back(std::move(d));
  }
  const auto& box_sizing__expr = data_.box_sizing_;
  const auto& o_box_sizing__expr = o.data_.box_sizing_;
  if (!(box_sizing__expr == o_box_sizing__expr)) {
    DebugDiff d;
    d.field = DebugField::box_sizing_;
    d.actual = DebugStringForField(box_sizing__expr);
    d.correct = DebugStringForField(o_box_sizing__expr);
    diff.push_back(std::move(d));
  }
  const auto& caption_side_is_inherited__expr = data_.caption_side_is_inherited_;
  const auto& o_caption_side_is_inherited__expr = o.data_.caption_side_is_inherited_;
  if (!(caption_side_is_inherited__expr == o_caption_side_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::caption_side_is_inherited_;
    d.actual = DebugStringForField(caption_side_is_inherited__expr);
    d.correct = DebugStringForField(o_caption_side_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& color_is_inherited__expr = data_.color_is_inherited_;
  const auto& o_color_is_inherited__expr = o.data_.color_is_inherited_;
  if (!(color_is_inherited__expr == o_color_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::color_is_inherited_;
    d.actual = DebugStringForField(color_is_inherited__expr);
    d.correct = DebugStringForField(o_color_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& cursor_is_inherited__expr = data_.cursor_is_inherited_;
  const auto& o_cursor_is_inherited__expr = o.data_.cursor_is_inherited_;
  if (!(cursor_is_inherited__expr == o_cursor_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::cursor_is_inherited_;
    d.actual = DebugStringForField(cursor_is_inherited__expr);
    d.correct = DebugStringForField(o_cursor_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& empty_cells_is_inherited__expr = data_.empty_cells_is_inherited_;
  const auto& o_empty_cells_is_inherited__expr = o.data_.empty_cells_is_inherited_;
  if (!(empty_cells_is_inherited__expr == o_empty_cells_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::empty_cells_is_inherited_;
    d.actual = DebugStringForField(empty_cells_is_inherited__expr);
    d.correct = DebugStringForField(o_empty_cells_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& forces_stacking_context__expr = data_.forces_stacking_context_;
  const auto& o_forces_stacking_context__expr = o.data_.forces_stacking_context_;
  if (!(forces_stacking_context__expr == o_forces_stacking_context__expr)) {
    DebugDiff d;
    d.field = DebugField::forces_stacking_context_;
    d.actual = DebugStringForField(forces_stacking_context__expr);
    d.correct = DebugStringForField(o_forces_stacking_context__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_author_background__expr = data_.has_author_background_;
  const auto& o_has_author_background__expr = o.data_.has_author_background_;
  if (!(has_author_background__expr == o_has_author_background__expr)) {
    DebugDiff d;
    d.field = DebugField::has_author_background_;
    d.actual = DebugStringForField(has_author_background__expr);
    d.correct = DebugStringForField(o_has_author_background__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_author_border__expr = data_.has_author_border_;
  const auto& o_has_author_border__expr = o.data_.has_author_border_;
  if (!(has_author_border__expr == o_has_author_border__expr)) {
    DebugDiff d;
    d.field = DebugField::has_author_border_;
    d.actual = DebugStringForField(has_author_border__expr);
    d.correct = DebugStringForField(o_has_author_border__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_author_border_radius__expr = data_.has_author_border_radius_;
  const auto& o_has_author_border_radius__expr = o.data_.has_author_border_radius_;
  if (!(has_author_border_radius__expr == o_has_author_border_radius__expr)) {
    DebugDiff d;
    d.field = DebugField::has_author_border_radius_;
    d.actual = DebugStringForField(has_author_border_radius__expr);
    d.correct = DebugStringForField(o_has_author_border_radius__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_author_highlight_colors__expr = data_.has_author_highlight_colors_;
  const auto& o_has_author_highlight_colors__expr = o.data_.has_author_highlight_colors_;
  if (!(has_author_highlight_colors__expr == o_has_author_highlight_colors__expr)) {
    DebugDiff d;
    d.field = DebugField::has_author_highlight_colors_;
    d.actual = DebugStringForField(has_author_highlight_colors__expr);
    d.correct = DebugStringForField(o_has_author_highlight_colors__expr);
    diff.push_back(std::move(d));
  }
  const auto& has_explicit_inheritance__expr = data_.has_explicit_inheritance_;
  const auto& o_has_explicit_inheritance__expr = o.data_.has_explicit_inheritance_;
  if (!(has_explicit_inheritance__expr == o_has_explicit_inheritance__expr)) {
    DebugDiff d;
    d.field = DebugField::has_explicit_inheritance_;
    d.actual = DebugStringForField(has_explicit_inheritance__expr);
    d.correct = DebugStringForField(o_has_explicit_inheritance__expr);
    diff.push_back(std::move(d));
  }
  const auto& interactivity_is_inherited__expr = data_.interactivity_is_inherited_;
  const auto& o_interactivity_is_inherited__expr = o.data_.interactivity_is_inherited_;
  if (!(interactivity_is_inherited__expr == o_interactivity_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::interactivity_is_inherited_;
    d.actual = DebugStringForField(interactivity_is_inherited__expr);
    d.correct = DebugStringForField(o_interactivity_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_css_inert_is_inherited__expr = data_.is_css_inert_is_inherited_;
  const auto& o_is_css_inert_is_inherited__expr = o.data_.is_css_inert_is_inherited_;
  if (!(is_css_inert_is_inherited__expr == o_is_css_inert_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::is_css_inert_is_inherited_;
    d.actual = DebugStringForField(is_css_inert_is_inherited__expr);
    d.correct = DebugStringForField(o_is_css_inert_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_html_inert_is_inherited__expr = data_.is_html_inert_is_inherited_;
  const auto& o_is_html_inert_is_inherited__expr = o.data_.is_html_inert_is_inherited_;
  if (!(is_html_inert_is_inherited__expr == o_is_html_inert_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::is_html_inert_is_inherited_;
    d.actual = DebugStringForField(is_html_inert_is_inherited__expr);
    d.correct = DebugStringForField(o_is_html_inert_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_original_display_inline_type__expr = data_.is_original_display_inline_type_;
  const auto& o_is_original_display_inline_type__expr = o.data_.is_original_display_inline_type_;
  if (!(is_original_display_inline_type__expr == o_is_original_display_inline_type__expr)) {
    DebugDiff d;
    d.field = DebugField::is_original_display_inline_type_;
    d.actual = DebugStringForField(is_original_display_inline_type__expr);
    d.correct = DebugStringForField(o_is_original_display_inline_type__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_page_margin_box__expr = data_.is_page_margin_box_;
  const auto& o_is_page_margin_box__expr = o.data_.is_page_margin_box_;
  if (!(is_page_margin_box__expr == o_is_page_margin_box__expr)) {
    DebugDiff d;
    d.field = DebugField::is_page_margin_box_;
    d.actual = DebugStringForField(is_page_margin_box__expr);
    d.correct = DebugStringForField(o_is_page_margin_box__expr);
    diff.push_back(std::move(d));
  }
  const auto& list_style_position_is_inherited__expr = data_.list_style_position_is_inherited_;
  const auto& o_list_style_position_is_inherited__expr = o.data_.list_style_position_is_inherited_;
  if (!(list_style_position_is_inherited__expr == o_list_style_position_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::list_style_position_is_inherited_;
    d.actual = DebugStringForField(list_style_position_is_inherited__expr);
    d.correct = DebugStringForField(o_list_style_position_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& origin_trial_test_property__expr = data_.origin_trial_test_property_;
  const auto& o_origin_trial_test_property__expr = o.data_.origin_trial_test_property_;
  if (!(origin_trial_test_property__expr == o_origin_trial_test_property__expr)) {
    DebugDiff d;
    d.field = DebugField::origin_trial_test_property_;
    d.actual = DebugStringForField(origin_trial_test_property__expr);
    d.correct = DebugStringForField(o_origin_trial_test_property__expr);
    diff.push_back(std::move(d));
  }
  const auto& pointer_events_is_inherited__expr = data_.pointer_events_is_inherited_;
  const auto& o_pointer_events_is_inherited__expr = o.data_.pointer_events_is_inherited_;
  if (!(pointer_events_is_inherited__expr == o_pointer_events_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::pointer_events_is_inherited_;
    d.actual = DebugStringForField(pointer_events_is_inherited__expr);
    d.correct = DebugStringForField(o_pointer_events_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& rtl_ordering_is_inherited__expr = data_.rtl_ordering_is_inherited_;
  const auto& o_rtl_ordering_is_inherited__expr = o.data_.rtl_ordering_is_inherited_;
  if (!(rtl_ordering_is_inherited__expr == o_rtl_ordering_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::rtl_ordering_is_inherited_;
    d.actual = DebugStringForField(rtl_ordering_is_inherited__expr);
    d.correct = DebugStringForField(o_rtl_ordering_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& scroll_snap_stop__expr = data_.scroll_snap_stop_;
  const auto& o_scroll_snap_stop__expr = o.data_.scroll_snap_stop_;
  if (!(scroll_snap_stop__expr == o_scroll_snap_stop__expr)) {
    DebugDiff d;
    d.field = DebugField::scroll_snap_stop_;
    d.actual = DebugStringForField(scroll_snap_stop__expr);
    d.correct = DebugStringForField(o_scroll_snap_stop__expr);
    diff.push_back(std::move(d));
  }
  const auto& should_ignore_overflow_property_for_inline_block_baseline__expr = data_.should_ignore_overflow_property_for_inline_block_baseline_;
  const auto& o_should_ignore_overflow_property_for_inline_block_baseline__expr = o.data_.should_ignore_overflow_property_for_inline_block_baseline_;
  if (!(should_ignore_overflow_property_for_inline_block_baseline__expr == o_should_ignore_overflow_property_for_inline_block_baseline__expr)) {
    DebugDiff d;
    d.field = DebugField::should_ignore_overflow_property_for_inline_block_baseline_;
    d.actual = DebugStringForField(should_ignore_overflow_property_for_inline_block_baseline__expr);
    d.correct = DebugStringForField(o_should_ignore_overflow_property_for_inline_block_baseline__expr);
    diff.push_back(std::move(d));
  }
  const auto& skips_contents__expr = data_.skips_contents_;
  const auto& o_skips_contents__expr = o.data_.skips_contents_;
  if (!(skips_contents__expr == o_skips_contents__expr)) {
    DebugDiff d;
    d.field = DebugField::skips_contents_;
    d.actual = DebugStringForField(skips_contents__expr);
    d.correct = DebugStringForField(o_skips_contents__expr);
    diff.push_back(std::move(d));
  }
  const auto& table_layout__expr = data_.table_layout_;
  const auto& o_table_layout__expr = o.data_.table_layout_;
  if (!(table_layout__expr == o_table_layout__expr)) {
    DebugDiff d;
    d.field = DebugField::table_layout_;
    d.actual = DebugStringForField(table_layout__expr);
    d.correct = DebugStringForField(o_table_layout__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_transform_is_inherited__expr = data_.text_transform_is_inherited_;
  const auto& o_text_transform_is_inherited__expr = o.data_.text_transform_is_inherited_;
  if (!(text_transform_is_inherited__expr == o_text_transform_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::text_transform_is_inherited_;
    d.actual = DebugStringForField(text_transform_is_inherited__expr);
    d.correct = DebugStringForField(o_text_transform_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& visibility_is_inherited__expr = data_.visibility_is_inherited_;
  const auto& o_visibility_is_inherited__expr = o.data_.visibility_is_inherited_;
  if (!(visibility_is_inherited__expr == o_visibility_is_inherited__expr)) {
    DebugDiff d;
    d.field = DebugField::visibility_is_inherited_;
    d.actual = DebugStringForField(visibility_is_inherited__expr);
    d.correct = DebugStringForField(o_visibility_is_inherited__expr);
    diff.push_back(std::move(d));
  }
  const auto& pointer_events__expr = data_.pointer_events_;
  const auto& o_pointer_events__expr = o.data_.pointer_events_;
  if (!(pointer_events__expr == o_pointer_events__expr)) {
    DebugDiff d;
    d.field = DebugField::pointer_events_;
    d.actual = DebugStringForField(pointer_events__expr);
    d.correct = DebugStringForField(o_pointer_events__expr);
    diff.push_back(std::move(d));
  }
  const auto& caret_shape__expr = data_.caret_shape_;
  const auto& o_caret_shape__expr = o.data_.caret_shape_;
  if (!(caret_shape__expr == o_caret_shape__expr)) {
    DebugDiff d;
    d.field = DebugField::caret_shape_;
    d.actual = DebugStringForField(caret_shape__expr);
    d.correct = DebugStringForField(o_caret_shape__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_align__expr = data_.text_align_;
  const auto& o_text_align__expr = o.data_.text_align_;
  if (!(text_align__expr == o_text_align__expr)) {
    DebugDiff d;
    d.field = DebugField::text_align_;
    d.actual = DebugStringForField(text_align__expr);
    d.correct = DebugStringForField(o_text_align__expr);
    diff.push_back(std::move(d));
  }
  const auto& writing_mode__expr = data_.writing_mode_;
  const auto& o_writing_mode__expr = o.data_.writing_mode_;
  if (!(writing_mode__expr == o_writing_mode__expr)) {
    DebugDiff d;
    d.field = DebugField::writing_mode_;
    d.actual = DebugStringForField(writing_mode__expr);
    d.correct = DebugStringForField(o_writing_mode__expr);
    diff.push_back(std::move(d));
  }
  const auto& inside_link__expr = data_.inside_link_;
  const auto& o_inside_link__expr = o.data_.inside_link_;
  if (!(inside_link__expr == o_inside_link__expr)) {
    DebugDiff d;
    d.field = DebugField::inside_link_;
    d.actual = DebugStringForField(inside_link__expr);
    d.correct = DebugStringForField(o_inside_link__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_wrap_style__expr = data_.text_wrap_style_;
  const auto& o_text_wrap_style__expr = o.data_.text_wrap_style_;
  if (!(text_wrap_style__expr == o_text_wrap_style__expr)) {
    DebugDiff d;
    d.field = DebugField::text_wrap_style_;
    d.actual = DebugStringForField(text_wrap_style__expr);
    d.correct = DebugStringForField(o_text_wrap_style__expr);
    diff.push_back(std::move(d));
  }
  const auto& visibility__expr = data_.visibility_;
  const auto& o_visibility__expr = o.data_.visibility_;
  if (!(visibility__expr == o_visibility__expr)) {
    DebugDiff d;
    d.field = DebugField::visibility_;
    d.actual = DebugStringForField(visibility__expr);
    d.correct = DebugStringForField(o_visibility__expr);
    diff.push_back(std::move(d));
  }
  const auto& white_space_collapse__expr = data_.white_space_collapse_;
  const auto& o_white_space_collapse__expr = o.data_.white_space_collapse_;
  if (!(white_space_collapse__expr == o_white_space_collapse__expr)) {
    DebugDiff d;
    d.field = DebugField::white_space_collapse_;
    d.actual = DebugStringForField(white_space_collapse__expr);
    d.correct = DebugStringForField(o_white_space_collapse__expr);
    diff.push_back(std::move(d));
  }
  const auto& border_collapse__expr = data_.border_collapse_;
  const auto& o_border_collapse__expr = o.data_.border_collapse_;
  if (!(border_collapse__expr == o_border_collapse__expr)) {
    DebugDiff d;
    d.field = DebugField::border_collapse_;
    d.actual = DebugStringForField(border_collapse__expr);
    d.correct = DebugStringForField(o_border_collapse__expr);
    diff.push_back(std::move(d));
  }
  const auto& caption_side__expr = data_.caption_side_;
  const auto& o_caption_side__expr = o.data_.caption_side_;
  if (!(caption_side__expr == o_caption_side__expr)) {
    DebugDiff d;
    d.field = DebugField::caption_side_;
    d.actual = DebugStringForField(caption_side__expr);
    d.correct = DebugStringForField(o_caption_side__expr);
    diff.push_back(std::move(d));
  }
  const auto& caret_animation__expr = data_.caret_animation_;
  const auto& o_caret_animation__expr = o.data_.caret_animation_;
  if (!(caret_animation__expr == o_caret_animation__expr)) {
    DebugDiff d;
    d.field = DebugField::caret_animation_;
    d.actual = DebugStringForField(caret_animation__expr);
    d.correct = DebugStringForField(o_caret_animation__expr);
    diff.push_back(std::move(d));
  }
  const auto& direction__expr = data_.direction_;
  const auto& o_direction__expr = o.data_.direction_;
  if (!(direction__expr == o_direction__expr)) {
    DebugDiff d;
    d.field = DebugField::direction_;
    d.actual = DebugStringForField(direction__expr);
    d.correct = DebugStringForField(o_direction__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_css_inert__expr = data_.is_css_inert_;
  const auto& o_is_css_inert__expr = o.data_.is_css_inert_;
  if (!(is_css_inert__expr == o_is_css_inert__expr)) {
    DebugDiff d;
    d.field = DebugField::is_css_inert_;
    d.actual = DebugStringForField(is_css_inert__expr);
    d.correct = DebugStringForField(o_is_css_inert__expr);
    diff.push_back(std::move(d));
  }
  const auto& is_html_inert__expr = data_.is_html_inert_;
  const auto& o_is_html_inert__expr = o.data_.is_html_inert_;
  if (!(is_html_inert__expr == o_is_html_inert__expr)) {
    DebugDiff d;
    d.field = DebugField::is_html_inert_;
    d.actual = DebugStringForField(is_html_inert__expr);
    d.correct = DebugStringForField(o_is_html_inert__expr);
    diff.push_back(std::move(d));
  }
  const auto& list_style_position__expr = data_.list_style_position_;
  const auto& o_list_style_position__expr = o.data_.list_style_position_;
  if (!(list_style_position__expr == o_list_style_position__expr)) {
    DebugDiff d;
    d.field = DebugField::list_style_position_;
    d.actual = DebugStringForField(list_style_position__expr);
    d.correct = DebugStringForField(o_list_style_position__expr);
    diff.push_back(std::move(d));
  }
  const auto& prefers_default_scrollbar_styles__expr = data_.prefers_default_scrollbar_styles_;
  const auto& o_prefers_default_scrollbar_styles__expr = o.data_.prefers_default_scrollbar_styles_;
  if (!(prefers_default_scrollbar_styles__expr == o_prefers_default_scrollbar_styles__expr)) {
    DebugDiff d;
    d.field = DebugField::prefers_default_scrollbar_styles_;
    d.actual = DebugStringForField(prefers_default_scrollbar_styles__expr);
    d.correct = DebugStringForField(o_prefers_default_scrollbar_styles__expr);
    diff.push_back(std::move(d));
  }
  const auto& print_color_adjust__expr = data_.print_color_adjust_;
  const auto& o_print_color_adjust__expr = o.data_.print_color_adjust_;
  if (!(print_color_adjust__expr == o_print_color_adjust__expr)) {
    DebugDiff d;
    d.field = DebugField::print_color_adjust_;
    d.actual = DebugStringForField(print_color_adjust__expr);
    d.correct = DebugStringForField(o_print_color_adjust__expr);
    diff.push_back(std::move(d));
  }
  const auto& rtl_ordering__expr = data_.rtl_ordering_;
  const auto& o_rtl_ordering__expr = o.data_.rtl_ordering_;
  if (!(rtl_ordering__expr == o_rtl_ordering__expr)) {
    DebugDiff d;
    d.field = DebugField::rtl_ordering_;
    d.actual = DebugStringForField(rtl_ordering__expr);
    d.correct = DebugStringForField(o_rtl_ordering__expr);
    diff.push_back(std::move(d));
  }
  const auto& text_wrap_mode__expr = data_.text_wrap_mode_;
  const auto& o_text_wrap_mode__expr = o.data_.text_wrap_mode_;
  if (!(text_wrap_mode__expr == o_text_wrap_mode__expr)) {
    DebugDiff d;
    d.field = DebugField::text_wrap_mode_;
    d.actual = DebugStringForField(text_wrap_mode__expr);
    d.correct = DebugStringForField(o_text_wrap_mode__expr);
    diff.push_back(std::move(d));
  }

  return diff;
}

#endif // DCHECK_IS_ON()

ComputedStyleBase::StyleMiscInherited1Data::StyleMiscInherited1Data() :
      dynamic_range_limit_(DynamicRangeLimit(cc::PaintFlags::DynamicRangeLimit::kHigh))
      , color_scheme_(Vector<AtomicString, 0>())
      , hyphenation_string_(AtomicString())
      , quotes_(nullptr)
      , list_style_image_(nullptr)
      , list_style_type_(ListStyleTypeData::CreateCounterStyle(keywords::kDisc, nullptr))
      , scrollbar_color_(nullptr)
      , text_indent_(Length::Fixed())
      , text_size_adjust_(TextSizeAdjust::AdjustAuto())
      , tab_size_(TabSize(8))
      , text_emphasis_color_(StyleColor::CurrentColor())
      , accent_color_(StyleAutoColor::AutoColor())
      , caret_color_(StyleAutoColor::AutoColor())
      , hyphenate_limit_chars_(StyleHyphenateLimitChars())
      , math_depth_(0)
      , orphans_(2)
  {}

ComputedStyleBase::StyleMiscInherited1Data::StyleMiscInherited1Data(const StyleMiscInherited1Data& other) :
      dynamic_range_limit_(other.dynamic_range_limit_)
      , color_scheme_(other.color_scheme_)
      , hyphenation_string_(other.hyphenation_string_)
      , quotes_(MemberCopy(other.quotes_))
      , list_style_image_(MemberCopy(other.list_style_image_))
      , list_style_type_(MemberCopy(other.list_style_type_))
      , scrollbar_color_(MemberCopy(other.scrollbar_color_))
      , text_indent_(other.text_indent_)
      , text_size_adjust_(other.text_size_adjust_)
      , tab_size_(other.tab_size_)
      , text_emphasis_color_(other.text_emphasis_color_)
      , accent_color_(other.accent_color_)
      , caret_color_(other.caret_color_)
      , hyphenate_limit_chars_(other.hyphenate_limit_chars_)
      , math_depth_(other.math_depth_)
      , orphans_(other.orphans_)
  {}

ComputedStyleBase::StyleMiscInherited2Data::StyleMiscInherited2Data() :
      text_emphasis_custom_mark_(AtomicString())
      , ua_shadow_host_data_(nullptr)
      , text_shadow_(nullptr)
      , cursor_data_(nullptr)
      , initial_data_(nullptr)
      , text_underline_offset_(Length())
      , text_stroke_width_(0)
      , effective_zoom_(1.0f)
      , tap_highlight_color_(StyleColor(LayoutTheme::TapHighlightColor()))
      , text_fill_color_(StyleColor::CurrentColor())
      , text_stroke_color_(StyleColor::CurrentColor())
      , widows_(2)
      , effective_touch_action_(static_cast<unsigned>(TouchAction::kAuto))
  {}

ComputedStyleBase::StyleMiscInherited2Data::StyleMiscInherited2Data(const StyleMiscInherited2Data& other) :
      text_emphasis_custom_mark_(other.text_emphasis_custom_mark_)
      , ua_shadow_host_data_(MemberCopy(other.ua_shadow_host_data_))
      , text_shadow_(MemberCopy(other.text_shadow_))
      , cursor_data_(MemberCopy(other.cursor_data_))
      , initial_data_(MemberCopy(other.initial_data_))
      , text_underline_offset_(other.text_underline_offset_)
      , text_stroke_width_(other.text_stroke_width_)
      , effective_zoom_(other.effective_zoom_)
      , tap_highlight_color_(other.tap_highlight_color_)
      , text_fill_color_(other.text_fill_color_)
      , text_stroke_color_(other.text_stroke_color_)
      , widows_(other.widows_)
      , effective_touch_action_(other.effective_touch_action_)
  {}

ComputedStyleBase::StyleMiscInheritedData::StyleMiscInheritedData() :
    misc_inherited_1_data_(StyleMiscInherited1Data::Create())
    , misc_inherited_2_data_(StyleMiscInherited2Data::Create())
      , text_box_edge_(static_cast<unsigned>(TextBoxEdge()))
      , text_underline_position_(static_cast<unsigned>(TextUnderlinePosition::kAuto))
      , hanging_punctuation_(static_cast<unsigned>(HangingPunctuation::kNone))
      , image_rendering_(static_cast<unsigned>(EImageRendering::kAuto))
      , line_break_(static_cast<unsigned>(LineBreak::kAuto))
      , speak_(static_cast<unsigned>(ESpeak::kNormal))
      , text_align_last_(static_cast<unsigned>(ETextAlignLast::kAuto))
      , text_decoration_skip_spaces_(static_cast<unsigned>(TextDecorationSkipSpaces::kNone))
      , text_emphasis_mark_(static_cast<unsigned>(TextEmphasisMark::kNone))
      , block_ellipsis_(static_cast<unsigned>(EBlockEllipsis::kNoEllipsis))
      , text_emphasis_position_(static_cast<unsigned>(ComputedStyleInitialValues::InitialTextEmphasisPosition()))
      , user_select_(static_cast<unsigned>(EUserSelect::kAuto))
      , word_break_(static_cast<unsigned>(EWordBreak::kNormal))
      , forced_color_adjust_(static_cast<unsigned>(EForcedColorAdjust::kAuto))
      , hyphens_(static_cast<unsigned>(Hyphens::kManual))
      , image_animation_(static_cast<unsigned>(ImageAnimationEnum::kNormal))
      , overflow_wrap_(static_cast<unsigned>(EOverflowWrap::kNormal))
      , ruby_align_(static_cast<unsigned>(ERubyAlign::kSpaceAround))
      , text_decoration_skip_ink_(static_cast<unsigned>(ETextDecorationSkipInk::kAuto))
      , text_indent_flags_(static_cast<unsigned>(TextIndentFlags::kDefault))
      , text_justify_(static_cast<unsigned>(TextJustify::kAuto))
      , text_orientation_(static_cast<unsigned>(ETextOrientation::kMixed))
      , text_security_(static_cast<unsigned>(ETextSecurity::kNone))
      , user_modify_(static_cast<unsigned>(EUserModify::kReadOnly))
      , empty_cells_(static_cast<unsigned>(EEmptyCells::kShow))
      , has_line_if_empty_(static_cast<unsigned>(false))
      , image_orientation_(static_cast<unsigned>(kRespectImageOrientation))
      , in_base_appearance_(static_cast<unsigned>(false))
      , interactivity_(static_cast<unsigned>(EInteractivity::kAuto))
      , interpolate_size_(static_cast<unsigned>(EInterpolateSize::kNumericOnly))
      , math_shift_(static_cast<unsigned>(EMathShift::kNormal))
      , math_style_(static_cast<unsigned>(EMathStyle::kNormal))
      , ruby_overhang_(static_cast<unsigned>(ERubyOverhang::kAuto))
      , ruby_position_(static_cast<unsigned>(RubyPosition::kOver))
      , subtree_is_sticky_(static_cast<unsigned>(false))
      , subtree_will_change_contents_(static_cast<unsigned>(false))
      , text_autospace_(static_cast<unsigned>(ETextAutospace::kNoAutospace))
      , text_combine_(static_cast<unsigned>(ETextCombine::kNone))
      , text_emphasis_fill_(static_cast<unsigned>(TextEmphasisFill::kFilled))
  {}

ComputedStyleBase::StyleMiscInheritedData::StyleMiscInheritedData(const StyleMiscInheritedData& other) :
      misc_inherited_1_data_(other.misc_inherited_1_data_)
      , misc_inherited_2_data_(other.misc_inherited_2_data_)
      , text_box_edge_(other.text_box_edge_)
      , text_underline_position_(other.text_underline_position_)
      , hanging_punctuation_(other.hanging_punctuation_)
      , image_rendering_(other.image_rendering_)
      , line_break_(other.line_break_)
      , speak_(other.speak_)
      , text_align_last_(other.text_align_last_)
      , text_decoration_skip_spaces_(other.text_decoration_skip_spaces_)
      , text_emphasis_mark_(other.text_emphasis_mark_)
      , block_ellipsis_(other.block_ellipsis_)
      , text_emphasis_position_(other.text_emphasis_position_)
      , user_select_(other.user_select_)
      , word_break_(other.word_break_)
      , forced_color_adjust_(other.forced_color_adjust_)
      , hyphens_(other.hyphens_)
      , image_animation_(other.image_animation_)
      , overflow_wrap_(other.overflow_wrap_)
      , ruby_align_(other.ruby_align_)
      , text_decoration_skip_ink_(other.text_decoration_skip_ink_)
      , text_indent_flags_(other.text_indent_flags_)
      , text_justify_(other.text_justify_)
      , text_orientation_(other.text_orientation_)
      , text_security_(other.text_security_)
      , user_modify_(other.user_modify_)
      , empty_cells_(other.empty_cells_)
      , has_line_if_empty_(other.has_line_if_empty_)
      , image_orientation_(other.image_orientation_)
      , in_base_appearance_(other.in_base_appearance_)
      , interactivity_(other.interactivity_)
      , interpolate_size_(other.interpolate_size_)
      , math_shift_(other.math_shift_)
      , math_style_(other.math_style_)
      , ruby_overhang_(other.ruby_overhang_)
      , ruby_position_(other.ruby_position_)
      , subtree_is_sticky_(other.subtree_is_sticky_)
      , subtree_will_change_contents_(other.subtree_will_change_contents_)
      , text_autospace_(other.text_autospace_)
      , text_combine_(other.text_combine_)
      , text_emphasis_fill_(other.text_emphasis_fill_)
  {}

ComputedStyleBase::StyleMisc1Data::StyleMisc1Data() :
      backdrop_filter_(FilterOperations())
      , animation_trigger_({ nullptr })
      , anchor_scope_(StyleAnchorScope())
      , position_anchor_(StylePositionAnchor::Initial())
      , column_rule_color_(GapDataList<StyleColor>::DefaultGapColorDataList())
      , anchor_name_(nullptr)
      , border_shape_(nullptr)
      , box_shadow_(nullptr)
      , clip_path_(nullptr)
      , column_gap_(std::nullopt)
      , column_rule_inset_cap_end_(Length::Fixed(0))
      , column_height_(0.0f)
      , position_area_(PositionArea())
      , column_count_(1)
      , align_self_(StyleSelfAlignmentData(ItemPosition::kAuto, OverflowAlignment::kDefault))
      , align_content_(StyleContentAlignmentData(ContentPosition::kNormal, ContentDistributionType::kDefault, OverflowAlignment::kDefault))
  {}

ComputedStyleBase::StyleMisc1Data::StyleMisc1Data(const StyleMisc1Data& other) :
      backdrop_filter_(other.backdrop_filter_)
      , animation_trigger_(other.animation_trigger_)
      , anchor_scope_(other.anchor_scope_)
      , position_anchor_(other.position_anchor_)
      , column_rule_color_(other.column_rule_color_)
      , anchor_name_(MemberCopy(other.anchor_name_))
      , border_shape_(MemberCopy(other.border_shape_))
      , box_shadow_(MemberCopy(other.box_shadow_))
      , clip_path_(MemberCopy(other.clip_path_))
      , column_gap_(other.column_gap_)
      , column_rule_inset_cap_end_(other.column_rule_inset_cap_end_)
      , column_height_(other.column_height_)
      , position_area_(other.position_area_)
      , column_count_(other.column_count_)
      , align_self_(other.align_self_)
      , align_content_(other.align_content_)
  {}

ComputedStyleBase::StyleVisitedData::StyleVisitedData() :
      internal_visited_column_rule_color_(GapDataList<StyleColor>::DefaultGapColorDataList())
      , internal_visited_background_color_(StyleColor(Color::kTransparent))
      , internal_visited_border_bottom_color_(StyleColor::CurrentColor())
      , internal_visited_border_left_color_(StyleColor::CurrentColor())
      , internal_visited_border_right_color_(StyleColor::CurrentColor())
      , internal_visited_border_top_color_(StyleColor::CurrentColor())
      , internal_visited_outline_color_(StyleColor::CurrentColor())
      , internal_visited_text_decoration_color_(StyleColor::CurrentColor())
  {}

ComputedStyleBase::StyleVisitedData::StyleVisitedData(const StyleVisitedData& other) :
      internal_visited_column_rule_color_(other.internal_visited_column_rule_color_)
      , internal_visited_background_color_(other.internal_visited_background_color_)
      , internal_visited_border_bottom_color_(other.internal_visited_border_bottom_color_)
      , internal_visited_border_left_color_(other.internal_visited_border_left_color_)
      , internal_visited_border_right_color_(other.internal_visited_border_right_color_)
      , internal_visited_border_top_color_(other.internal_visited_border_top_color_)
      , internal_visited_outline_color_(other.internal_visited_outline_color_)
      , internal_visited_text_decoration_color_(other.internal_visited_text_decoration_color_)
  {}

ComputedStyleBase::StyleMisc2Data::StyleMisc2Data() :
      grid_auto_columns_(GridTrackList(GridTrackSize(Length::Auto())))
      , filter_(FilterOperations())
      , flow_tolerance_(FlowTolerance(CSSValueID::kNormal))
      , column_rule_width_(GapDataList<int>::DefaultGapWidthDataList())
      , column_rule_style_(GapDataList<EBorderStyle>::DefaultGapStyleDataList())
      , container_name_(nullptr)
      , content_(nullptr)
      , column_rule_inset_cap_start_(Length::Fixed(0))
      , column_rule_inset_junction_end_(Length::Fixed(0))
      , column_rule_inset_junction_start_(Length::Fixed(0))
      , flex_basis_(Length::Auto())
      , column_width_(0.0f)
      , flex_grow_(0.0f)
      , flex_shrink_(1.0f)
      , flex_line_count_(1u)
      , flex_wrap_(StyleFlexWrapData(FlexWrapMode::kNowrap))
  {}

ComputedStyleBase::StyleMisc2Data::StyleMisc2Data(const StyleMisc2Data& other) :
      grid_auto_columns_(other.grid_auto_columns_)
      , filter_(other.filter_)
      , flow_tolerance_(other.flow_tolerance_)
      , column_rule_width_(other.column_rule_width_)
      , column_rule_style_(other.column_rule_style_)
      , container_name_(MemberCopy(other.container_name_))
      , content_(MemberCopy(other.content_))
      , column_rule_inset_cap_start_(other.column_rule_inset_cap_start_)
      , column_rule_inset_junction_end_(other.column_rule_inset_junction_end_)
      , column_rule_inset_junction_start_(other.column_rule_inset_junction_start_)
      , flex_basis_(other.flex_basis_)
      , column_width_(other.column_width_)
      , flex_grow_(other.flex_grow_)
      , flex_shrink_(other.flex_shrink_)
      , flex_line_count_(other.flex_line_count_)
      , flex_wrap_(other.flex_wrap_)
  {}

ComputedStyleBase::StyleMisc3Data::StyleMisc3Data() :
      grid_auto_rows_(GridTrackList(GridTrackSize(Length::Auto())))
      , grid_column_end_(GridPosition())
      , grid_column_start_(GridPosition())
      , grid_row_end_(GridPosition())
      , grid_row_start_(GridPosition())
      , grid_template_areas_(nullptr)
      , grid_template_columns_(nullptr)
      , grid_template_rows_(nullptr)
      , initial_letter_(StyleInitialLetter())
      , object_position_(LengthPoint(Length::Percent(50.0), Length::Percent(50.0)))
      , interest_delay_end_(StyleInterestDelay())
      , interest_delay_start_(StyleInterestDelay())
      , max_lines_(0)
      , grid_lanes_direction_(GridLanesDirection())
      , justify_items_(StyleSelfAlignmentData(ItemPosition::kLegacy, OverflowAlignment::kDefault))
      , justify_self_(StyleSelfAlignmentData(ItemPosition::kAuto, OverflowAlignment::kDefault))
  {}

ComputedStyleBase::StyleMisc3Data::StyleMisc3Data(const StyleMisc3Data& other) :
      grid_auto_rows_(other.grid_auto_rows_)
      , grid_column_end_(other.grid_column_end_)
      , grid_column_start_(other.grid_column_start_)
      , grid_row_end_(other.grid_row_end_)
      , grid_row_start_(other.grid_row_start_)
      , grid_template_areas_(MemberCopy(other.grid_template_areas_))
      , grid_template_columns_(MemberCopy(other.grid_template_columns_))
      , grid_template_rows_(MemberCopy(other.grid_template_rows_))
      , initial_letter_(other.initial_letter_)
      , object_position_(other.object_position_)
      , interest_delay_end_(other.interest_delay_end_)
      , interest_delay_start_(other.interest_delay_start_)
      , max_lines_(other.max_lines_)
      , grid_lanes_direction_(other.grid_lanes_direction_)
      , justify_items_(other.justify_items_)
      , justify_self_(other.justify_self_)
  {}

ComputedStyleBase::StyleForcedColorsData::StyleForcedColorsData() :
      internal_forced_background_color_(StyleColor(CSSValueID::kCanvas))
      , internal_forced_border_color_(StyleColor::CurrentColor())
      , internal_forced_outline_color_(StyleColor::CurrentColor())
  {}

ComputedStyleBase::StyleForcedColorsData::StyleForcedColorsData(const StyleForcedColorsData& other) :
      internal_forced_background_color_(other.internal_forced_background_color_)
      , internal_forced_border_color_(other.internal_forced_border_color_)
      , internal_forced_outline_color_(other.internal_forced_outline_color_)
  {}

ComputedStyleBase::StyleMisc4Data::StyleMisc4Data() :
      page_(AtomicString())
      , object_view_box_(nullptr)
      , offset_path_(nullptr)
      , position_try_fallbacks_(nullptr)
      , rotate_(nullptr)
      , offset_rotate_(StyleOffsetRotation(0, OffsetRotationType::kAuto))
      , offset_anchor_(LengthPoint(Length::Auto(), Length::Auto()))
      , offset_position_(LengthPoint(Length::None(), Length::None()))
      , perspective_origin_(LengthPoint(Length::Percent(50.0), Length::Percent(50.0)))
      , offset_distance_(Length::Fixed(0))
      , perspective_(-1.0)
      , outline_color_(StyleColor::CurrentColor())
      , order_(0)
      , outline_offset_(0)
      , outline_width_(3)
      , reading_order_(0)
  {}

ComputedStyleBase::StyleMisc4Data::StyleMisc4Data(const StyleMisc4Data& other) :
      page_(other.page_)
      , object_view_box_(MemberCopy(other.object_view_box_))
      , offset_path_(MemberCopy(other.offset_path_))
      , position_try_fallbacks_(MemberCopy(other.position_try_fallbacks_))
      , rotate_(MemberCopy(other.rotate_))
      , offset_rotate_(other.offset_rotate_)
      , offset_anchor_(other.offset_anchor_)
      , offset_position_(other.offset_position_)
      , perspective_origin_(other.perspective_origin_)
      , offset_distance_(other.offset_distance_)
      , perspective_(other.perspective_)
      , outline_color_(other.outline_color_)
      , order_(other.order_)
      , outline_offset_(other.outline_offset_)
      , outline_width_(other.outline_width_)
      , reading_order_(other.reading_order_)
  {}

ComputedStyleBase::StyleMisc5Data::StyleMisc5Data() :
      row_rule_color_(GapDataList<StyleColor>::DefaultGapColorDataList())
      , row_rule_width_(GapDataList<int>::DefaultGapWidthDataList())
      , row_rule_style_(GapDataList<EBorderStyle>::DefaultGapStyleDataList())
      , scale_(nullptr)
      , scroll_marker_group_(nullptr)
      , row_gap_(std::nullopt)
      , row_rule_inset_cap_end_(Length::Fixed(0))
      , row_rule_inset_cap_start_(Length::Fixed(0))
      , row_rule_inset_junction_end_(Length::Fixed(0))
      , row_rule_inset_junction_start_(Length::Fixed(0))
      , scroll_padding_bottom_(Length())
      , scroll_padding_left_(Length())
      , scroll_margin_bottom_(0.0f)
      , scroll_margin_left_(0.0f)
      , scroll_margin_right_(0.0f)
      , scroll_margin_top_(0.0f)
  {}

ComputedStyleBase::StyleMisc5Data::StyleMisc5Data(const StyleMisc5Data& other) :
      row_rule_color_(other.row_rule_color_)
      , row_rule_width_(other.row_rule_width_)
      , row_rule_style_(other.row_rule_style_)
      , scale_(MemberCopy(other.scale_))
      , scroll_marker_group_(MemberCopy(other.scroll_marker_group_))
      , row_gap_(other.row_gap_)
      , row_rule_inset_cap_end_(other.row_rule_inset_cap_end_)
      , row_rule_inset_cap_start_(other.row_rule_inset_cap_start_)
      , row_rule_inset_junction_end_(other.row_rule_inset_junction_end_)
      , row_rule_inset_junction_start_(other.row_rule_inset_junction_start_)
      , scroll_padding_bottom_(other.scroll_padding_bottom_)
      , scroll_padding_left_(other.scroll_padding_left_)
      , scroll_margin_bottom_(other.scroll_margin_bottom_)
      , scroll_margin_left_(other.scroll_margin_left_)
      , scroll_margin_right_(other.scroll_margin_right_)
      , scroll_margin_top_(other.scroll_margin_top_)
  {}

ComputedStyleBase::StyleMisc6Data::StyleMisc6Data() :
      text_decoration_thickness_(TextDecorationThickness(Length::Auto()))
      , text_overflow_(TextOverflowData(TextOverflowData::Type::kClip))
      , trigger_scope_(StyleTriggerScope())
      , shape_outside_(nullptr)
      , timeline_trigger_name_(nullptr)
      , translate_(nullptr)
      , view_transition_class_(nullptr)
      , scroll_padding_right_(Length())
      , scroll_padding_top_(Length())
      , shape_margin_(Length::Fixed(0))
      , text_fit_(FitText())
      , shape_image_threshold_(0.0)
      , scroll_snap_type_(cc::ScrollSnapType())
      , scroll_snap_align_(cc::ScrollSnapAlign())
      , text_decoration_color_(StyleColor::CurrentColor())
      , touch_action_(static_cast<unsigned>(TouchAction::kAuto))
  {}

ComputedStyleBase::StyleMisc6Data::StyleMisc6Data(const StyleMisc6Data& other) :
      text_decoration_thickness_(other.text_decoration_thickness_)
      , text_overflow_(other.text_overflow_)
      , trigger_scope_(other.trigger_scope_)
      , shape_outside_(MemberCopy(other.shape_outside_))
      , timeline_trigger_name_(MemberCopy(other.timeline_trigger_name_))
      , translate_(MemberCopy(other.translate_))
      , view_transition_class_(MemberCopy(other.view_transition_class_))
      , scroll_padding_right_(other.scroll_padding_right_)
      , scroll_padding_top_(other.scroll_padding_top_)
      , shape_margin_(other.shape_margin_)
      , text_fit_(other.text_fit_)
      , shape_image_threshold_(other.shape_image_threshold_)
      , scroll_snap_type_(other.scroll_snap_type_)
      , scroll_snap_align_(other.scroll_snap_align_)
      , text_decoration_color_(other.text_decoration_color_)
      , touch_action_(other.touch_action_)
  {}

ComputedStyleBase::StyleTimelineData::StyleTimelineData() :
      scroll_timeline_name_(Vector<AtomicString>())
      , view_timeline_name_(Vector<AtomicString>())
      , scroll_timeline_axis_(Vector<TimelineAxis>())
      , view_timeline_axis_(Vector<TimelineAxis>())
      , view_timeline_inset_(Vector<TimelineInset>())
      , timeline_scope_(StyleTimelineScope())
  {}

ComputedStyleBase::StyleTimelineData::StyleTimelineData(const StyleTimelineData& other) :
      scroll_timeline_name_(other.scroll_timeline_name_)
      , view_timeline_name_(other.view_timeline_name_)
      , scroll_timeline_axis_(other.scroll_timeline_axis_)
      , view_timeline_axis_(other.view_timeline_axis_)
      , view_timeline_inset_(other.view_timeline_inset_)
      , timeline_scope_(other.timeline_scope_)
  {}

ComputedStyleBase::StyleMisc7Data::StyleMisc7Data() :
      view_transition_group_(StyleViewTransitionGroup::Normal())
      , display_layout_custom_name_(g_null_atom)
      , display_layout_custom_parent_name_(g_null_atom)
      , custom_highlight_names_(nullptr)
      , counter_directives_(nullptr)
      , mask_(FillLayer(EFillLayerType::kMask, true))
      , mask_box_image_(NinePieceImage::MaskDefaults())
      , unconditional_scrollbar_size_(gfx::Size())
      , view_transition_name_(nullptr)
      , box_reflect_(nullptr)
      , animations_(nullptr)
      , transitions_(nullptr)
      , page_size_(gfx::SizeF())
      , box_flex_(0.0f)
      , box_ordinal_group_(1)
      , webkit_line_clamp_(0)
  {}

ComputedStyleBase::StyleMisc7Data::StyleMisc7Data(const StyleMisc7Data& other) :
      view_transition_group_(other.view_transition_group_)
      , display_layout_custom_name_(other.display_layout_custom_name_)
      , display_layout_custom_parent_name_(other.display_layout_custom_parent_name_)
      , custom_highlight_names_(MemberCopy(other.custom_highlight_names_))
      , counter_directives_(MemberCopy(other.counter_directives_))
      , mask_(other.mask_)
      , mask_box_image_(other.mask_box_image_)
      , unconditional_scrollbar_size_(other.unconditional_scrollbar_size_)
      , view_transition_name_(MemberCopy(other.view_transition_name_))
      , box_reflect_(MemberCopy(other.box_reflect_))
      , animations_(MemberCopy(other.animations_))
      , transitions_(MemberCopy(other.transitions_))
      , page_size_(other.page_size_)
      , box_flex_(other.box_flex_)
      , box_ordinal_group_(other.box_ordinal_group_)
      , webkit_line_clamp_(other.webkit_line_clamp_)
  {}

ComputedStyleBase::StyleMisc8Data::StyleMisc8Data() :
      callback_selectors_(Vector<String>())
      , non_inherited_variables_(StyleNonInheritedVariables())
      , position_area_offsets_(std::nullopt)
      , anchor_center_offset_(std::nullopt)
      , document_rules_selectors_(nullptr)
      , paint_images_(nullptr)
  {}

ComputedStyleBase::StyleMisc8Data::StyleMisc8Data(const StyleMisc8Data& other) :
      callback_selectors_(other.callback_selectors_)
      , non_inherited_variables_(other.non_inherited_variables_)
      , position_area_offsets_(other.position_area_offsets_)
      , anchor_center_offset_(other.anchor_center_offset_)
      , document_rules_selectors_(MemberCopy(other.document_rules_selectors_))
      , paint_images_(MemberCopy(other.paint_images_))
  {}

ComputedStyleBase::StyleMathData::StyleMathData() :
      math_baseline_(Length())
      , math_fraction_bar_thickness_(Length())
      , math_l_space_(Length())
      , math_r_space_(Length())
      , math_padded_v_offset_(Length())
      , math_padded_depth_(Length())
      , math_min_size_(Length())
      , math_max_size_(Length())
  {}

ComputedStyleBase::StyleMathData::StyleMathData(const StyleMathData& other) :
      math_baseline_(other.math_baseline_)
      , math_fraction_bar_thickness_(other.math_fraction_bar_thickness_)
      , math_l_space_(other.math_l_space_)
      , math_r_space_(other.math_r_space_)
      , math_padded_v_offset_(other.math_padded_v_offset_)
      , math_padded_depth_(other.math_padded_depth_)
      , math_min_size_(other.math_min_size_)
      , math_max_size_(other.math_max_size_)
  {}

ComputedStyleBase::StyleMiscData::StyleMiscData() :
    misc_1_data_(StyleMisc1Data::Create())
    , visited_data_(StyleVisitedData::Create())
    , misc_2_data_(StyleMisc2Data::Create())
    , misc_3_data_(StyleMisc3Data::Create())
    , forced_colors_data_(StyleForcedColorsData::Create())
    , misc_4_data_(StyleMisc4Data::Create())
    , misc_5_data_(StyleMisc5Data::Create())
    , misc_6_data_(StyleMisc6Data::Create())
    , timeline_data_(StyleTimelineData::Create())
    , misc_7_data_(StyleMisc7Data::Create())
    , misc_8_data_(StyleMisc8Data::Create())
    , math_data_(StyleMathData::Create())
      , will_change_(nullptr)
      , appearance_(static_cast<unsigned>(AppearanceValue::kNone))
      , blend_mode_(static_cast<unsigned>(BlendMode::kNormal))
      , contain_(static_cast<unsigned>(kContainsNone))
      , effective_appearance_(static_cast<unsigned>(AppearanceValue::kNone))
      , break_after_(static_cast<unsigned>(EBreakBetween::kAuto))
      , break_before_(static_cast<unsigned>(EBreakBetween::kAuto))
      , container_type_(static_cast<unsigned>(kContainerTypeNormal))
      , grid_auto_flow_(static_cast<unsigned>(kAutoFlowRow))
      , margin_trim_(static_cast<unsigned>(kMarginTrimNone))
      , outline_style_(static_cast<unsigned>(EBorderStyle::kNone))
      , scrollbar_gutter_(static_cast<unsigned>(kScrollbarGutterAuto))
      , box_align_(static_cast<unsigned>(EBoxAlignment::kStretch))
      , object_fit_(static_cast<unsigned>(EObjectFit::kFill))
      , position_try_order_(static_cast<unsigned>(EPositionTryOrder::kNormal))
      , position_visibility_(static_cast<unsigned>(PositionVisibility::kAnchorsVisible))
      , reading_flow_(static_cast<unsigned>(EReadingFlow::kNormal))
      , affected_by_css_function_(static_cast<unsigned>(false))
      , resize_(static_cast<unsigned>(EResize::kNone))
      , text_decoration_style_(static_cast<unsigned>(ETextDecorationStyle::kSolid))
      , box_pack_(static_cast<unsigned>(EBoxPack::kStart))
      , break_inside_(static_cast<unsigned>(EBreakInside::kAuto))
      , column_rule_break_(static_cast<unsigned>(RuleBreak::kNormal))
      , column_rule_visibility_items_(static_cast<unsigned>(RuleVisibilityItems::kNormal))
      , column_wrap_(static_cast<unsigned>(EColumnWrap::kAuto))
      , continue_(static_cast<unsigned>(EContinue::kNormal))
      , draggable_region_mode_(static_cast<unsigned>(EDraggableRegionMode::kNone))
      , flex_direction_(static_cast<unsigned>(EFlexDirection::kRow))
      , internal_overscroll_area_(static_cast<unsigned>(EInternalOverscrollArea::kNone))
      , overscroll_behavior_x_(static_cast<unsigned>(EOverscrollBehavior::kAuto))
      , overscroll_behavior_y_(static_cast<unsigned>(EOverscrollBehavior::kAuto))
      , page_margin_safety_(static_cast<unsigned>(EPageMarginSafety::kNone))
      , page_orientation_(static_cast<unsigned>(PageOrientation::kUpright))
      , page_size_type_(static_cast<unsigned>(PageSizeType::kAuto))
      , row_rule_break_(static_cast<unsigned>(RuleBreak::kNormal))
      , row_rule_visibility_items_(static_cast<unsigned>(RuleVisibilityItems::kNormal))
      , scroll_behavior_(static_cast<unsigned>(mojom::blink::ScrollBehavior::kAuto))
      , scrollbar_width_(static_cast<unsigned>(EScrollbarWidth::kAuto))
      , user_drag_(static_cast<unsigned>(EUserDrag::kAuto))
      , affected_by_functional_media_(static_cast<unsigned>(false))
      , align_content_block_center_(static_cast<unsigned>(false))
      , backface_visibility_(static_cast<unsigned>(EBackfaceVisibility::kVisible))
      , box_orient_(static_cast<unsigned>(EBoxOrient::kHorizontal))
      , can_affect_animations_(static_cast<unsigned>(false))
      , column_fill_(static_cast<unsigned>(EColumnFill::kBalance))
      , column_span_(static_cast<unsigned>(EColumnSpan::kNone))
      , depends_on_anchored_container_queries_(static_cast<unsigned>(false))
      , depends_on_scroll_state_container_queries_(static_cast<unsigned>(false))
      , depends_on_size_container_queries_(static_cast<unsigned>(false))
      , depends_on_style_container_queries_(static_cast<unsigned>(false))
      , element_is_view_transition_participant_(static_cast<unsigned>(false))
      , first_line_depends_on_size_container_queries_(static_cast<unsigned>(false))
      , grid_lanes_pack_(static_cast<unsigned>(EGridLanesPack::kNormal))
      , has_auto_column_count_(static_cast<unsigned>(true))
      , has_auto_column_height_(static_cast<unsigned>(true))
      , has_auto_column_width_(static_cast<unsigned>(true))
      , has_current_backdrop_filter_animation_(static_cast<unsigned>(false))
      , has_current_background_color_animation_(static_cast<unsigned>(false))
      , has_current_clip_path_animation_(static_cast<unsigned>(false))
      , has_current_filter_animation_(static_cast<unsigned>(false))
      , has_current_opacity_animation_(static_cast<unsigned>(false))
      , has_current_rotate_animation_(static_cast<unsigned>(false))
      , has_current_scale_animation_(static_cast<unsigned>(false))
      , has_current_transform_animation_(static_cast<unsigned>(false))
      , has_current_translate_animation_(static_cast<unsigned>(false))
      , has_element_dependent_random_functions_(static_cast<unsigned>(false))
      , has_env_safe_area_inset_bottom_(static_cast<unsigned>(false))
      , has_explicit_overflow_x_visible_(static_cast<unsigned>(false))
      , has_explicit_overflow_y_visible_(static_cast<unsigned>(false))
      , has_line_height_relative_units_(static_cast<unsigned>(false))
      , has_non_ua_highlight_pseudo_styles_(static_cast<unsigned>(false))
      , has_non_universal_highlight_pseudo_styles_(static_cast<unsigned>(false))
      , has_sibling_functions_(static_cast<unsigned>(false))
      , highlights_depend_on_size_container_queries_(static_cast<unsigned>(false))
      , inline_style_lost_cascade_(static_cast<unsigned>(false))
      , internal_overscroll_position_(static_cast<unsigned>(EInternalOverscrollPosition::kNone))
      , is_bottom_relative_to_safe_area_inset_(static_cast<unsigned>(false))
      , is_running_backdrop_filter_animation_on_compositor_(static_cast<unsigned>(false))
      , is_running_filter_animation_on_compositor_(static_cast<unsigned>(false))
      , is_running_opacity_animation_on_compositor_(static_cast<unsigned>(false))
      , is_running_rotate_animation_on_compositor_(static_cast<unsigned>(false))
      , is_running_scale_animation_on_compositor_(static_cast<unsigned>(false))
      , is_running_transform_animation_on_compositor_(static_cast<unsigned>(false))
      , is_running_translate_animation_on_compositor_(static_cast<unsigned>(false))
      , is_secondary_body_element_(static_cast<unsigned>(false))
      , is_specified_display_webkit_box_(static_cast<unsigned>(false))
      , is_starting_style_(static_cast<unsigned>(false))
      , isolation_(static_cast<unsigned>(EIsolation::kAuto))
      , outline_style_is_auto_(static_cast<unsigned>(false))
      , overlay_(static_cast<unsigned>(EOverlay::kNone))
      , requires_accelerated_compositing_for_external_reasons_(static_cast<unsigned>(false))
      , rule_overlap_(static_cast<unsigned>(ERuleOverlap::kRowOverColumn))
      , scroll_initial_target_(static_cast<unsigned>(EScrollInitialTarget::kNone))
      , scroll_target_group_(static_cast<unsigned>(EScrollTargetGroup::kNone))
      , transform_style_3d_(static_cast<unsigned>(ETransformStyle3D::kFlat))
      , view_transition_scope_(static_cast<unsigned>(EViewTransitionScope::kNone))
  {}

ComputedStyleBase::StyleMiscData::StyleMiscData(const StyleMiscData& other) :
      misc_1_data_(other.misc_1_data_)
      , visited_data_(other.visited_data_)
      , misc_2_data_(other.misc_2_data_)
      , misc_3_data_(other.misc_3_data_)
      , forced_colors_data_(other.forced_colors_data_)
      , misc_4_data_(other.misc_4_data_)
      , misc_5_data_(other.misc_5_data_)
      , misc_6_data_(other.misc_6_data_)
      , timeline_data_(other.timeline_data_)
      , misc_7_data_(other.misc_7_data_)
      , misc_8_data_(other.misc_8_data_)
      , math_data_(other.math_data_)
      , will_change_(MemberCopy(other.will_change_))
      , appearance_(other.appearance_)
      , blend_mode_(other.blend_mode_)
      , contain_(other.contain_)
      , effective_appearance_(other.effective_appearance_)
      , break_after_(other.break_after_)
      , break_before_(other.break_before_)
      , container_type_(other.container_type_)
      , grid_auto_flow_(other.grid_auto_flow_)
      , margin_trim_(other.margin_trim_)
      , outline_style_(other.outline_style_)
      , scrollbar_gutter_(other.scrollbar_gutter_)
      , box_align_(other.box_align_)
      , object_fit_(other.object_fit_)
      , position_try_order_(other.position_try_order_)
      , position_visibility_(other.position_visibility_)
      , reading_flow_(other.reading_flow_)
      , affected_by_css_function_(other.affected_by_css_function_)
      , resize_(other.resize_)
      , text_decoration_style_(other.text_decoration_style_)
      , box_pack_(other.box_pack_)
      , break_inside_(other.break_inside_)
      , column_rule_break_(other.column_rule_break_)
      , column_rule_visibility_items_(other.column_rule_visibility_items_)
      , column_wrap_(other.column_wrap_)
      , continue_(other.continue_)
      , draggable_region_mode_(other.draggable_region_mode_)
      , flex_direction_(other.flex_direction_)
      , internal_overscroll_area_(other.internal_overscroll_area_)
      , overscroll_behavior_x_(other.overscroll_behavior_x_)
      , overscroll_behavior_y_(other.overscroll_behavior_y_)
      , page_margin_safety_(other.page_margin_safety_)
      , page_orientation_(other.page_orientation_)
      , page_size_type_(other.page_size_type_)
      , row_rule_break_(other.row_rule_break_)
      , row_rule_visibility_items_(other.row_rule_visibility_items_)
      , scroll_behavior_(other.scroll_behavior_)
      , scrollbar_width_(other.scrollbar_width_)
      , user_drag_(other.user_drag_)
      , affected_by_functional_media_(other.affected_by_functional_media_)
      , align_content_block_center_(other.align_content_block_center_)
      , backface_visibility_(other.backface_visibility_)
      , box_orient_(other.box_orient_)
      , can_affect_animations_(other.can_affect_animations_)
      , column_fill_(other.column_fill_)
      , column_span_(other.column_span_)
      , depends_on_anchored_container_queries_(other.depends_on_anchored_container_queries_)
      , depends_on_scroll_state_container_queries_(other.depends_on_scroll_state_container_queries_)
      , depends_on_size_container_queries_(other.depends_on_size_container_queries_)
      , depends_on_style_container_queries_(other.depends_on_style_container_queries_)
      , element_is_view_transition_participant_(other.element_is_view_transition_participant_)
      , first_line_depends_on_size_container_queries_(other.first_line_depends_on_size_container_queries_)
      , grid_lanes_pack_(other.grid_lanes_pack_)
      , has_auto_column_count_(other.has_auto_column_count_)
      , has_auto_column_height_(other.has_auto_column_height_)
      , has_auto_column_width_(other.has_auto_column_width_)
      , has_current_backdrop_filter_animation_(other.has_current_backdrop_filter_animation_)
      , has_current_background_color_animation_(other.has_current_background_color_animation_)
      , has_current_clip_path_animation_(other.has_current_clip_path_animation_)
      , has_current_filter_animation_(other.has_current_filter_animation_)
      , has_current_opacity_animation_(other.has_current_opacity_animation_)
      , has_current_rotate_animation_(other.has_current_rotate_animation_)
      , has_current_scale_animation_(other.has_current_scale_animation_)
      , has_current_transform_animation_(other.has_current_transform_animation_)
      , has_current_translate_animation_(other.has_current_translate_animation_)
      , has_element_dependent_random_functions_(other.has_element_dependent_random_functions_)
      , has_env_safe_area_inset_bottom_(other.has_env_safe_area_inset_bottom_)
      , has_explicit_overflow_x_visible_(other.has_explicit_overflow_x_visible_)
      , has_explicit_overflow_y_visible_(other.has_explicit_overflow_y_visible_)
      , has_line_height_relative_units_(other.has_line_height_relative_units_)
      , has_non_ua_highlight_pseudo_styles_(other.has_non_ua_highlight_pseudo_styles_)
      , has_non_universal_highlight_pseudo_styles_(other.has_non_universal_highlight_pseudo_styles_)
      , has_sibling_functions_(other.has_sibling_functions_)
      , highlights_depend_on_size_container_queries_(other.highlights_depend_on_size_container_queries_)
      , inline_style_lost_cascade_(other.inline_style_lost_cascade_)
      , internal_overscroll_position_(other.internal_overscroll_position_)
      , is_bottom_relative_to_safe_area_inset_(other.is_bottom_relative_to_safe_area_inset_)
      , is_running_backdrop_filter_animation_on_compositor_(other.is_running_backdrop_filter_animation_on_compositor_)
      , is_running_filter_animation_on_compositor_(other.is_running_filter_animation_on_compositor_)
      , is_running_opacity_animation_on_compositor_(other.is_running_opacity_animation_on_compositor_)
      , is_running_rotate_animation_on_compositor_(other.is_running_rotate_animation_on_compositor_)
      , is_running_scale_animation_on_compositor_(other.is_running_scale_animation_on_compositor_)
      , is_running_transform_animation_on_compositor_(other.is_running_transform_animation_on_compositor_)
      , is_running_translate_animation_on_compositor_(other.is_running_translate_animation_on_compositor_)
      , is_secondary_body_element_(other.is_secondary_body_element_)
      , is_specified_display_webkit_box_(other.is_specified_display_webkit_box_)
      , is_starting_style_(other.is_starting_style_)
      , isolation_(other.isolation_)
      , outline_style_is_auto_(other.outline_style_is_auto_)
      , overlay_(other.overlay_)
      , requires_accelerated_compositing_for_external_reasons_(other.requires_accelerated_compositing_for_external_reasons_)
      , rule_overlap_(other.rule_overlap_)
      , scroll_initial_target_(other.scroll_initial_target_)
      , scroll_target_group_(other.scroll_target_group_)
      , transform_style_3d_(other.transform_style_3d_)
      , view_transition_scope_(other.view_transition_scope_)
  {}

ComputedStyleBase::StyleInheritedForcedColorsData::StyleInheritedForcedColorsData() :
      internal_forced_visited_color_(StyleColor(CSSValueID::kCanvastext))
      , internal_forced_color_(StyleColor(CSSValueID::kCanvastext))
  {}

ComputedStyleBase::StyleInheritedForcedColorsData::StyleInheritedForcedColorsData(const StyleInheritedForcedColorsData& other) :
      internal_forced_visited_color_(other.internal_forced_visited_color_)
      , internal_forced_color_(other.internal_forced_color_)
  {}

ComputedStyleBase::StyleInheritedVisitedData::StyleInheritedVisitedData() :
      internal_visited_text_emphasis_color_(StyleColor::CurrentColor())
      , internal_visited_text_fill_color_(StyleColor::CurrentColor())
      , internal_visited_text_stroke_color_(StyleColor::CurrentColor())
      , internal_visited_caret_color_(StyleAutoColor::AutoColor())
  {}

ComputedStyleBase::StyleInheritedVisitedData::StyleInheritedVisitedData(const StyleInheritedVisitedData& other) :
      internal_visited_text_emphasis_color_(other.internal_visited_text_emphasis_color_)
      , internal_visited_text_fill_color_(other.internal_visited_text_fill_color_)
      , internal_visited_text_stroke_color_(other.internal_visited_text_stroke_color_)
      , internal_visited_caret_color_(other.internal_visited_caret_color_)
  {}

ComputedStyleBase::StyleHighlightDataData::StyleHighlightDataData() :
      highlight_data_(StyleHighlightData())
  {}

ComputedStyleBase::StyleHighlightDataData::StyleHighlightDataData(const StyleHighlightDataData& other) :
      highlight_data_(other.highlight_data_)
  {}

ComputedStyleBase::StyleInheritedData::StyleInheritedData() :
    inherited_forced_colors_data_(StyleInheritedForcedColorsData::Create())
    , inherited_visited_data_(StyleInheritedVisitedData::Create())
    , highlight_data_data_(StyleHighlightDataData::Create())
      , inherited_variables_(StyleInheritedVariables())
      , font_(MakeGarbageCollected<Font>())
      , container_font_(nullptr)
      , letter_spacing_(Length::Fixed())
      , line_height_(Length::Auto())
      , word_spacing_(Length::Fixed())
      , internal_visited_color_(StyleColor(Color::kBlack))
      , color_(StyleColor(Color::kBlack))
      , horizontal_border_spacing_(0)
      , vertical_border_spacing_(0)
      , cursor_(static_cast<unsigned>(ECursor::kAuto))
      , text_transform_(static_cast<unsigned>(ETextTransform::kNone))
      , color_is_current_color_(static_cast<unsigned>(true))
      , in_forced_colors_mode_(static_cast<unsigned>(false))
      , internal_visited_color_is_current_color_(static_cast<unsigned>(true))
  {}

ComputedStyleBase::StyleInheritedData::StyleInheritedData(const StyleInheritedData& other) :
      inherited_forced_colors_data_(other.inherited_forced_colors_data_)
      , inherited_visited_data_(other.inherited_visited_data_)
      , highlight_data_data_(other.highlight_data_data_)
      , inherited_variables_(other.inherited_variables_)
      , font_(MemberCopy(other.font_))
      , container_font_(MemberCopy(other.container_font_))
      , letter_spacing_(other.letter_spacing_)
      , line_height_(other.line_height_)
      , word_spacing_(other.word_spacing_)
      , internal_visited_color_(other.internal_visited_color_)
      , color_(other.color_)
      , horizontal_border_spacing_(other.horizontal_border_spacing_)
      , vertical_border_spacing_(other.vertical_border_spacing_)
      , cursor_(other.cursor_)
      , text_transform_(other.text_transform_)
      , color_is_current_color_(other.color_is_current_color_)
      , in_forced_colors_mode_(other.in_forced_colors_mode_)
      , internal_visited_color_is_current_color_(other.internal_visited_color_is_current_color_)
  {}

ComputedStyleBase::StyleVisualData::StyleVisualData() :
      base_text_decoration_data_(nullptr)
      , clip_(LengthBox())
      , zoom_(1.0)
      , text_decoration_line_(static_cast<unsigned>(TextDecorationLine::kNone))
      , field_sizing_(static_cast<unsigned>(EFieldSizing::kFixed))
      , has_auto_clip_(static_cast<unsigned>(true))
      , has_clip_path_(static_cast<unsigned>(false))
      , maybe_has_gap_decorations_(static_cast<unsigned>(false))
  {}

ComputedStyleBase::StyleVisualData::StyleVisualData(const StyleVisualData& other) :
      base_text_decoration_data_(MemberCopy(other.base_text_decoration_data_))
      , clip_(other.clip_)
      , zoom_(other.zoom_)
      , text_decoration_line_(other.text_decoration_line_)
      , field_sizing_(other.field_sizing_)
      , has_auto_clip_(other.has_auto_clip_)
      , has_clip_path_(other.has_clip_path_)
      , maybe_has_gap_decorations_(other.maybe_has_gap_decorations_)
  {}

ComputedStyleBase::StyleFillData::StyleFillData() :
      internal_visited_fill_paint_(SVGPaint(Color::kBlack))
      , fill_paint_(SVGPaint::CreateInitialBlack())
      , fill_opacity_(1)
  {}

ComputedStyleBase::StyleFillData::StyleFillData(const StyleFillData& other) :
      internal_visited_fill_paint_(other.internal_visited_fill_paint_)
      , fill_paint_(other.fill_paint_)
      , fill_opacity_(other.fill_opacity_)
  {}

ComputedStyleBase::StyleStrokeData::StyleStrokeData() :
      internal_visited_stroke_paint_(SVGPaint())
      , stroke_paint_(SVGPaint::CreateInitial())
      , stroke_dash_array_(nullptr)
      , stroke_dash_offset_(Length::Fixed())
      , stroke_width_(UnzoomedLength(Length::Fixed(1)))
      , stroke_miter_limit_(4)
      , stroke_opacity_(1)
      , cap_style_(static_cast<unsigned>(kButtCap))
      , join_style_(static_cast<unsigned>(kMiterJoin))
  {}

ComputedStyleBase::StyleStrokeData::StyleStrokeData(const StyleStrokeData& other) :
      internal_visited_stroke_paint_(other.internal_visited_stroke_paint_)
      , stroke_paint_(other.stroke_paint_)
      , stroke_dash_array_(MemberCopy(other.stroke_dash_array_))
      , stroke_dash_offset_(other.stroke_dash_offset_)
      , stroke_width_(other.stroke_width_)
      , stroke_miter_limit_(other.stroke_miter_limit_)
      , stroke_opacity_(other.stroke_opacity_)
      , cap_style_(other.cap_style_)
      , join_style_(other.join_style_)
  {}

ComputedStyleBase::StyleResourcesData::StyleResourcesData() :
      marker_end_resource_(nullptr)
      , marker_mid_resource_(nullptr)
      , marker_start_resource_(nullptr)
  {}

ComputedStyleBase::StyleResourcesData::StyleResourcesData(const StyleResourcesData& other) :
      marker_end_resource_(MemberCopy(other.marker_end_resource_))
      , marker_mid_resource_(MemberCopy(other.marker_mid_resource_))
      , marker_start_resource_(MemberCopy(other.marker_start_resource_))
  {}

ComputedStyleBase::StyleSvginheritedData::StyleSvginheritedData() :
    fill_data_(StyleFillData::Create())
    , stroke_data_(StyleStrokeData::Create())
    , resources_data_(StyleResourcesData::Create())
      , css_dominant_baseline_(static_cast<unsigned>(EDominantBaseline::kAuto))
      , dominant_baseline_(static_cast<unsigned>(EDominantBaseline::kAuto))
      , paint_order_(static_cast<unsigned>(kPaintOrderNormal))
      , color_interpolation_(static_cast<unsigned>(EColorInterpolation::kSRGB))
      , color_interpolation_filters_(static_cast<unsigned>(EColorInterpolation::kLinearrgb))
      , color_rendering_(static_cast<unsigned>(EColorRendering::kAuto))
      , shape_rendering_(static_cast<unsigned>(EShapeRendering::kAuto))
      , text_anchor_(static_cast<unsigned>(ETextAnchor::kStart))
      , clip_rule_(static_cast<unsigned>(RULE_NONZERO))
      , fill_rule_(static_cast<unsigned>(RULE_NONZERO))
  {}

ComputedStyleBase::StyleSvginheritedData::StyleSvginheritedData(const StyleSvginheritedData& other) :
      fill_data_(other.fill_data_)
      , stroke_data_(other.stroke_data_)
      , resources_data_(other.resources_data_)
      , css_dominant_baseline_(other.css_dominant_baseline_)
      , dominant_baseline_(other.dominant_baseline_)
      , paint_order_(other.paint_order_)
      , color_interpolation_(other.color_interpolation_)
      , color_interpolation_filters_(other.color_interpolation_filters_)
      , color_rendering_(other.color_rendering_)
      , shape_rendering_(other.shape_rendering_)
      , text_anchor_(other.text_anchor_)
      , clip_rule_(other.clip_rule_)
      , fill_rule_(other.fill_rule_)
  {}

ComputedStyleBase::StyleBoxData::StyleBoxData() :
      overflow_clip_margin_(std::nullopt)
      , height_(Length())
      , margin_bottom_(Length::Fixed())
      , margin_left_(Length::Fixed())
      , margin_right_(Length::Fixed())
      , margin_top_(Length::Fixed())
      , max_height_(Length::None())
      , max_width_(Length::None())
      , min_height_(Length())
      , min_width_(Length())
      , padding_bottom_(Length::Fixed())
      , padding_left_(Length::Fixed())
      , padding_right_(Length::Fixed())
      , padding_top_(Length::Fixed())
      , width_(Length())
      , vertical_align_length_(Length())
      , border_bottom_width_(3)
      , border_left_width_(3)
      , border_right_width_(3)
      , border_top_width_(3)
      , z_index_(0)
      , align_items_(StyleSelfAlignmentData(ItemPosition::kNormal, OverflowAlignment::kDefault))
      , justify_content_(StyleContentAlignmentData(ContentPosition::kNormal, ContentDistributionType::kDefault, OverflowAlignment::kDefault))
      , border_bottom_style_(static_cast<unsigned>(EBorderStyle::kNone))
      , border_left_style_(static_cast<unsigned>(EBorderStyle::kNone))
      , border_right_style_(static_cast<unsigned>(EBorderStyle::kNone))
      , border_top_style_(static_cast<unsigned>(EBorderStyle::kNone))
      , baseline_source_(static_cast<unsigned>(EBaselineSource::kAuto))
      , text_box_trim_(static_cast<unsigned>(ETextBoxTrim::kNone))
      , box_decoration_break_(static_cast<unsigned>(EBoxDecorationBreak::kSlice))
      , has_auto_z_index_(static_cast<unsigned>(true))
  {}

ComputedStyleBase::StyleBoxData::StyleBoxData(const StyleBoxData& other) :
      overflow_clip_margin_(other.overflow_clip_margin_)
      , height_(other.height_)
      , margin_bottom_(other.margin_bottom_)
      , margin_left_(other.margin_left_)
      , margin_right_(other.margin_right_)
      , margin_top_(other.margin_top_)
      , max_height_(other.max_height_)
      , max_width_(other.max_width_)
      , min_height_(other.min_height_)
      , min_width_(other.min_width_)
      , padding_bottom_(other.padding_bottom_)
      , padding_left_(other.padding_left_)
      , padding_right_(other.padding_right_)
      , padding_top_(other.padding_top_)
      , width_(other.width_)
      , vertical_align_length_(other.vertical_align_length_)
      , border_bottom_width_(other.border_bottom_width_)
      , border_left_width_(other.border_left_width_)
      , border_right_width_(other.border_right_width_)
      , border_top_width_(other.border_top_width_)
      , z_index_(other.z_index_)
      , align_items_(other.align_items_)
      , justify_content_(other.justify_content_)
      , border_bottom_style_(other.border_bottom_style_)
      , border_left_style_(other.border_left_style_)
      , border_right_style_(other.border_right_style_)
      , border_top_style_(other.border_top_style_)
      , baseline_source_(other.baseline_source_)
      , text_box_trim_(other.text_box_trim_)
      , box_decoration_break_(other.box_decoration_break_)
      , has_auto_z_index_(other.has_auto_z_index_)
  {}

ComputedStyleBase::StyleSvgmiscData::StyleSvgmiscData() :
      baseline_shift_(Length::Fixed())
      , flood_opacity_(1)
      , flood_color_(StyleColor(Color::kBlack))
      , lighting_color_(StyleColor(Color::kWhite))
      , baseline_shift_type_(static_cast<unsigned>(EBaselineShiftType::kLength))
  {}

ComputedStyleBase::StyleSvgmiscData::StyleSvgmiscData(const StyleSvgmiscData& other) :
      baseline_shift_(other.baseline_shift_)
      , flood_opacity_(other.flood_opacity_)
      , flood_color_(other.flood_color_)
      , lighting_color_(other.lighting_color_)
      , baseline_shift_type_(other.baseline_shift_type_)
  {}

ComputedStyleBase::StyleGeometryData::StyleGeometryData() :
      d_(nullptr)
      , cx_(Length::Fixed())
      , cy_(Length::Fixed())
      , r_(Length::Fixed())
      , rx_(Length::Auto())
      , ry_(Length::Auto())
      , x_(Length::Fixed())
      , y_(Length::Fixed())
      , path_length_(-1.0)
  {}

ComputedStyleBase::StyleGeometryData::StyleGeometryData(const StyleGeometryData& other) :
      d_(MemberCopy(other.d_))
      , cx_(other.cx_)
      , cy_(other.cy_)
      , r_(other.r_)
      , rx_(other.rx_)
      , ry_(other.ry_)
      , x_(other.x_)
      , y_(other.y_)
      , path_length_(other.path_length_)
  {}

ComputedStyleBase::StyleStopData::StyleStopData() :
      stop_opacity_(1)
      , stop_color_(StyleColor(Color::kBlack))
  {}

ComputedStyleBase::StyleStopData::StyleStopData(const StyleStopData& other) :
      stop_opacity_(other.stop_opacity_)
      , stop_color_(other.stop_color_)
  {}

ComputedStyleBase::StyleSVGData::StyleSVGData() :
    svgmisc_data_(StyleSvgmiscData::Create())
    , geometry_data_(StyleGeometryData::Create())
    , stop_data_(StyleStopData::Create())
      , transform_(EmptyTransformOperations())
      , transform_origin_(TransformOrigin(Length::Percent(50.0), Length::Percent(50.0), 0))
      , opacity_(1.0)
      , alignment_baseline_(static_cast<unsigned>(EAlignmentBaseline::kAuto))
      , buffered_rendering_(static_cast<unsigned>(EBufferedRendering::kAuto))
      , mask_type_(static_cast<unsigned>(EMaskType::kLuminance))
      , vector_effect_(static_cast<unsigned>(EVectorEffect::kNone))
  {}

ComputedStyleBase::StyleSVGData::StyleSVGData(const StyleSVGData& other) :
      svgmisc_data_(other.svgmisc_data_)
      , geometry_data_(other.geometry_data_)
      , stop_data_(other.stop_data_)
      , transform_(other.transform_)
      , transform_origin_(other.transform_origin_)
      , opacity_(other.opacity_)
      , alignment_baseline_(other.alignment_baseline_)
      , buffered_rendering_(other.buffered_rendering_)
      , mask_type_(other.mask_type_)
      , vector_effect_(other.vector_effect_)
  {}

ComputedStyleBase::StyleSurroundData::StyleSurroundData() :
      corner_bottom_left_shape_(Superellipse::Round())
      , corner_bottom_right_shape_(Superellipse::Round())
      , corner_top_left_shape_(Superellipse::Round())
      , corner_top_right_shape_(Superellipse::Round())
      , border_image_(NinePieceImage())
      , aspect_ratio_(StyleAspectRatio(EAspectRatioType::kAuto, gfx::SizeF()))
      , contain_intrinsic_height_(StyleIntrinsicLength())
      , contain_intrinsic_width_(StyleIntrinsicLength())
      , border_bottom_left_radius_(LengthSize(Length::Fixed(0), Length::Fixed(0)))
      , border_bottom_right_radius_(LengthSize(Length::Fixed(0), Length::Fixed(0)))
      , border_top_left_radius_(LengthSize(Length::Fixed(0), Length::Fixed(0)))
      , border_top_right_radius_(LengthSize(Length::Fixed(0), Length::Fixed(0)))
      , bottom_(Length())
      , left_(Length())
      , right_(Length())
      , top_(Length())
      , border_bottom_color_(StyleColor::CurrentColor())
      , border_left_color_(StyleColor::CurrentColor())
      , border_right_color_(StyleColor::CurrentColor())
      , border_top_color_(StyleColor::CurrentColor())
      , frame_sizing_(static_cast<unsigned>(EFrameSizing::kAuto))
      , has_anchor_evaluator_(static_cast<unsigned>(false))
      , has_anchor_functions_(static_cast<unsigned>(false))
      , may_have_margin_(static_cast<unsigned>(false))
      , may_have_padding_(static_cast<unsigned>(false))
  {}

ComputedStyleBase::StyleSurroundData::StyleSurroundData(const StyleSurroundData& other) :
      corner_bottom_left_shape_(other.corner_bottom_left_shape_)
      , corner_bottom_right_shape_(other.corner_bottom_right_shape_)
      , corner_top_left_shape_(other.corner_top_left_shape_)
      , corner_top_right_shape_(other.corner_top_right_shape_)
      , border_image_(other.border_image_)
      , aspect_ratio_(other.aspect_ratio_)
      , contain_intrinsic_height_(other.contain_intrinsic_height_)
      , contain_intrinsic_width_(other.contain_intrinsic_width_)
      , border_bottom_left_radius_(other.border_bottom_left_radius_)
      , border_bottom_right_radius_(other.border_bottom_right_radius_)
      , border_top_left_radius_(other.border_top_left_radius_)
      , border_top_right_radius_(other.border_top_right_radius_)
      , bottom_(other.bottom_)
      , left_(other.left_)
      , right_(other.right_)
      , top_(other.top_)
      , border_bottom_color_(other.border_bottom_color_)
      , border_left_color_(other.border_left_color_)
      , border_right_color_(other.border_right_color_)
      , border_top_color_(other.border_top_color_)
      , frame_sizing_(other.frame_sizing_)
      , has_anchor_evaluator_(other.has_anchor_evaluator_)
      , has_anchor_functions_(other.has_anchor_functions_)
      , may_have_margin_(other.may_have_margin_)
      , may_have_padding_(other.may_have_padding_)
  {}

ComputedStyleBase::StyleBackgroundData::StyleBackgroundData() :
      background_(FillLayer(EFillLayerType::kBackground, true))
      , background_color_(StyleColor(Color::kTransparent))
  {}

ComputedStyleBase::StyleBackgroundData::StyleBackgroundData(const StyleBackgroundData& other) :
      background_(other.background_)
      , background_color_(other.background_color_)
  {}


ComputedStyleBuilderBase::ComputedStyleBuilderBase(const ComputedStyleBase& style) :
  misc_inherited_data_(style.misc_inherited_data_)
  , misc_data_(style.misc_data_)
  , inherited_data_(style.inherited_data_)
  , visual_data_(style.visual_data_)
  , svginherited_data_(style.svginherited_data_)
  , box_data_(style.box_data_)
  , svg_data_(style.svg_data_)
  , surround_data_(style.surround_data_)
  , background_data_(style.background_data_)
  , base_data_(style.base_data_)
  , data_(style.data_)
  {}

ComputedStyleBuilderBase::ComputedStyleBuilderBase(
  const ComputedStyleBase &source_for_noninherited,
  const ComputedStyleBase &parent_style) :
  misc_inherited_data_(parent_style.misc_inherited_data_)
  , misc_data_(source_for_noninherited.misc_data_)
  , inherited_data_(parent_style.inherited_data_)
  , visual_data_(source_for_noninherited.visual_data_)
  , svginherited_data_(parent_style.svginherited_data_)
  , box_data_(source_for_noninherited.box_data_)
  , svg_data_(source_for_noninherited.svg_data_)
  , surround_data_(source_for_noninherited.surround_data_)
  , background_data_(source_for_noninherited.background_data_)
  , base_data_(nullptr /* base_data_ */)
{
  // Workaround for https://github.com/llvm/llvm-project/issues/126212
  ComputedStyleBase::Data new_data{
    static_cast<unsigned>(kPseudoIdNone) /* pseudo_element_styles_ */
    , source_for_noninherited.data_.display_
    , static_cast<unsigned>(false) /* affected_by_active_ */
    , static_cast<unsigned>(PseudoId::kPseudoIdNone) /* style_type_ */
    , source_for_noninherited.data_.vertical_align_
    , source_for_noninherited.data_.clear_
    , source_for_noninherited.data_.floating_
    , source_for_noninherited.data_.overflow_x_
    , source_for_noninherited.data_.overflow_y_
    , source_for_noninherited.data_.position_
    , source_for_noninherited.data_.transform_box_
    , source_for_noninherited.data_.unicode_bidi_
    , static_cast<unsigned>(false) /* affected_by_drag_ */
    , source_for_noninherited.data_.content_visibility_
    , source_for_noninherited.data_.inline_block_baseline_edge_
    , static_cast<unsigned>(0) /* is_stacking_context_without_containment_ (mutable) */
    , source_for_noninherited.data_.overflow_anchor_
    , source_for_noninherited.data_.viewport_unit_flags_
    , static_cast<unsigned>(false) /* affected_by_focus_within_ */
    , static_cast<unsigned>(false) /* affected_by_hover_ */
    , source_for_noninherited.data_.allows_z_index_
    , source_for_noninherited.data_.border_collapse_is_inherited_
    , source_for_noninherited.data_.box_direction_
    , source_for_noninherited.data_.box_sizing_
    , source_for_noninherited.data_.caption_side_is_inherited_
    , static_cast<unsigned>(false) /* child_has_explicit_inheritance_ (mutable) */
    , source_for_noninherited.data_.color_is_inherited_
    , source_for_noninherited.data_.cursor_is_inherited_
    , source_for_noninherited.data_.custom_style_callback_depends_on_font_
    , source_for_noninherited.data_.empty_cells_is_inherited_
    , source_for_noninherited.data_.forces_stacking_context_
    , static_cast<unsigned>(false) /* has_attr_function_ */
    , source_for_noninherited.data_.has_author_background_
    , source_for_noninherited.data_.has_author_border_
    , source_for_noninherited.data_.has_author_border_radius_
    , source_for_noninherited.data_.has_author_highlight_colors_
    , source_for_noninherited.data_.has_container_relative_value_
    , source_for_noninherited.data_.has_em_units_
    , source_for_noninherited.data_.has_env_
    , source_for_noninherited.data_.has_explicit_inheritance_
    , source_for_noninherited.data_.has_glyph_relative_units_
    , source_for_noninherited.data_.has_logical_direction_relative_units_
    , source_for_noninherited.data_.has_root_font_relative_units_
    , source_for_noninherited.data_.has_variable_declaration_
    , source_for_noninherited.data_.has_variable_reference_
    , source_for_noninherited.data_.interactivity_is_inherited_
    , source_for_noninherited.data_.is_css_inert_is_inherited_
    , source_for_noninherited.data_.is_ensured_in_display_none_
    , source_for_noninherited.data_.is_flex_or_grid_or_custom_item_
    , source_for_noninherited.data_.is_html_inert_is_inherited_
    , source_for_noninherited.data_.is_in_blockifying_display_
    , source_for_noninherited.data_.is_in_inlinifying_display_
    , source_for_noninherited.data_.is_inside_display_ignoring_floating_children_
    , static_cast<unsigned>(false) /* is_link_ */
    , source_for_noninherited.data_.is_original_display_inline_type_
    , source_for_noninherited.data_.is_page_margin_box_
    , source_for_noninherited.data_.list_style_position_is_inherited_
    , source_for_noninherited.data_.origin_trial_test_property_
    , source_for_noninherited.data_.pointer_events_is_inherited_
    , source_for_noninherited.data_.rtl_ordering_is_inherited_
    , source_for_noninherited.data_.scroll_snap_stop_
    , source_for_noninherited.data_.should_ignore_overflow_property_for_inline_block_baseline_
    , source_for_noninherited.data_.skips_contents_
    , source_for_noninherited.data_.table_layout_
    , source_for_noninherited.data_.text_transform_is_inherited_
    , source_for_noninherited.data_.visibility_is_inherited_
    , parent_style.data_.pointer_events_
    , parent_style.data_.caret_shape_
    , parent_style.data_.text_align_
    , parent_style.data_.writing_mode_
    , parent_style.data_.inside_link_
    , parent_style.data_.text_wrap_style_
    , parent_style.data_.visibility_
    , parent_style.data_.white_space_collapse_
    , parent_style.data_.border_collapse_
    , parent_style.data_.caption_side_
    , parent_style.data_.caret_animation_
    , parent_style.data_.color_scheme_flags_is_normal_
    , parent_style.data_.color_scheme_forced_
    , parent_style.data_.dark_color_scheme_
    , parent_style.data_.direction_
    , parent_style.data_.is_css_inert_
    , parent_style.data_.is_ensured_outside_flat_tree_
    , parent_style.data_.is_html_inert_
    , parent_style.data_.list_style_position_
    , parent_style.data_.prefers_default_scrollbar_styles_
    , parent_style.data_.print_color_adjust_
    , parent_style.data_.rtl_ordering_
    , parent_style.data_.text_wrap_mode_
  };
  memcpy(&data_, &new_data, sizeof(data_));


    // The following fields have the 'reset_on_new_style' flag set, but were
    // part of groups that were copied wholesale in the initialization.
    if (misc_data_->misc_7_data_->custom_highlight_names_ != nullptr) {
      Access(Access(misc_data_, access_.misc_data_)->misc_7_data_, access_.misc_7_data_)->custom_highlight_names_ = nullptr;
    }
    if (misc_data_->has_non_ua_highlight_pseudo_styles_ != static_cast<unsigned>(false)) {
      Access(misc_data_, access_.misc_data_)->has_non_ua_highlight_pseudo_styles_ = static_cast<unsigned>(false);
    }
    if (misc_data_->has_non_universal_highlight_pseudo_styles_ != static_cast<unsigned>(false)) {
      Access(misc_data_, access_.misc_data_)->has_non_universal_highlight_pseudo_styles_ = static_cast<unsigned>(false);
    }
    if (misc_data_->highlights_depend_on_size_container_queries_ != static_cast<unsigned>(false)) {
      Access(misc_data_, access_.misc_data_)->highlights_depend_on_size_container_queries_ = static_cast<unsigned>(false);
    }
}

void ComputedStyleBuilderBase::PropagateIndependentInheritedProperties(
    const ComputedStyleBase& parent_style) {
  if (EmptyCellsIsInherited()) {
    SetEmptyCells(parent_style.EmptyCells());
  }
  if (InteractivityIsInherited()) {
    SetInteractivity(parent_style.Interactivity());
  }
  if (ColorIsInherited()) {
    SetColor(parent_style.Color());
  }
  if (CursorIsInherited()) {
    SetCursor(parent_style.Cursor());
  }
  if (TextTransformIsInherited()) {
    SetTextTransform(parent_style.TextTransform());
  }
  if (PointerEventsIsInherited()) {
    SetPointerEvents(parent_style.PointerEvents());
  }
  if (VisibilityIsInherited()) {
    SetVisibility(parent_style.Visibility());
  }
  if (BorderCollapseIsInherited()) {
    SetBorderCollapse(parent_style.BorderCollapse());
  }
  if (CaptionSideIsInherited()) {
    SetCaptionSide(parent_style.CaptionSide());
  }
  if (IsCSSInertIsInherited()) {
    SetIsCSSInert(parent_style.IsCSSInert());
  }
  if (IsHTMLInertIsInherited()) {
    SetIsHTMLInert(parent_style.IsHTMLInert());
  }
  if (ListStylePositionIsInherited()) {
    SetListStylePosition(parent_style.ListStylePosition());
  }
  if (RtlOrderingIsInherited()) {
    SetRtlOrdering(parent_style.RtlOrdering());
  }
}

void ComputedStyleBuilderBase::CopyHighlightPropertiesFrom(
    const ComputedStyleBase& originating_element_style)
{
    SetForcedColorAdjust(originating_element_style.ForcedColorAdjust());
    SetNonInheritedVariablesInternal(originating_element_style.NonInheritedVariablesInternal());
    SetInheritedVariablesInternal(originating_element_style.InheritedVariablesInternal());
    SetFont(originating_element_style.GetFont());
    SetLineHeight(originating_element_style.LineHeight());
    SetInForcedColorsMode(originating_element_style.InForcedColorsMode());
    SetWritingMode(originating_element_style.GetWritingMode());
    SetDarkColorScheme(originating_element_style.DarkColorScheme());
}

} // namespace blink
