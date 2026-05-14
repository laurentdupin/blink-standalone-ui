// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   core/css/properties/templates/css_properties.cc.tmpl
// and input files:
//   third_party\blink\renderer\core\css\computed_style_field_aliases.json5
//   third_party\blink\renderer\core\css\css_properties.json5
//   third_party\blink\renderer\core\css\properties\css_property_methods.json5
//   third_party\blink\renderer\platform\runtime_enabled_features.json5



#include "third_party/blink/renderer/core/css/properties/shorthands.h"

#include "third_party/blink/renderer/core/css/css_custom_ident_value.h"
#include "third_party/blink/renderer/core/css/css_identifier_value.h"
#include "third_party/blink/renderer/core/css/css_identifier_value_mappings.h"
#include "third_party/blink/renderer/core/css/css_counter_value.h"
#include "third_party/blink/renderer/core/css/css_primitive_value.h"
#include "third_party/blink/renderer/core/css/css_value_list.h"
#include "third_party/blink/renderer/core/css/css_value_pair.h"
#include "third_party/blink/renderer/core/css/properties/css_direction_aware_resolver.h"
#include "third_party/blink/renderer/core/css/properties/css_parsing_utils.h"
#include "third_party/blink/renderer/core/css/properties/style_building_utils.h"
#include "third_party/blink/renderer/core/css/resolver/font_builder.h"
#include "third_party/blink/renderer/core/css/resolver/style_builder_converter.h"
#include "third_party/blink/renderer/core/css/resolver/style_resolver_state.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/style/style_svg_resource.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"

namespace blink {
namespace css_shorthand {

// -alternative-webkit-line-clamp


CSSExposure AlternativeWebkitLineClamp::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSLineClampEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* AlternativeWebkitLineClamp::GetPropertyName() const {
  return "-webkit-line-clamp";
}

const AtomicString& AlternativeWebkitLineClamp::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-line-clamp"));
  return name;
}

const char* AlternativeWebkitLineClamp::GetJSPropertyName() const {
  return "webkitLineClamp";
}




 // animation



const char* Animation::GetPropertyName() const {
  return "animation";
}

const AtomicString& Animation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation"));
  return name;
}

const char* Animation::GetJSPropertyName() const {
  return "animation";
}




 // animation-range



const char* AnimationRange::GetPropertyName() const {
  return "animation-range";
}

const AtomicString& AnimationRange::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-range"));
  return name;
}

const char* AnimationRange::GetJSPropertyName() const {
  return "animationRange";
}




 // background



const char* Background::GetPropertyName() const {
  return "background";
}

const AtomicString& Background::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background"));
  return name;
}

const char* Background::GetJSPropertyName() const {
  return "background";
}




 // background-position



const char* BackgroundPosition::GetPropertyName() const {
  return "background-position";
}

const AtomicString& BackgroundPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-position"));
  return name;
}

const char* BackgroundPosition::GetJSPropertyName() const {
  return "backgroundPosition";
}




 // border



const char* Border::GetPropertyName() const {
  return "border";
}

const AtomicString& Border::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border"));
  return name;
}

const char* Border::GetJSPropertyName() const {
  return "border";
}




 // border-block



const char* BorderBlock::GetPropertyName() const {
  return "border-block";
}

const AtomicString& BorderBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block"));
  return name;
}

const char* BorderBlock::GetJSPropertyName() const {
  return "borderBlock";
}




 // border-block-color



const char* BorderBlockColor::GetPropertyName() const {
  return "border-block-color";
}

const AtomicString& BorderBlockColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-color"));
  return name;
}

const char* BorderBlockColor::GetJSPropertyName() const {
  return "borderBlockColor";
}




 // border-block-end



const char* BorderBlockEnd::GetPropertyName() const {
  return "border-block-end";
}

const AtomicString& BorderBlockEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-end"));
  return name;
}

const char* BorderBlockEnd::GetJSPropertyName() const {
  return "borderBlockEnd";
}


const CSSProperty* BorderBlockEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderMapping());
}

bool BorderBlockEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderMapping().Contains(id);
}


 // border-block-start



const char* BorderBlockStart::GetPropertyName() const {
  return "border-block-start";
}

const AtomicString& BorderBlockStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-start"));
  return name;
}

const char* BorderBlockStart::GetJSPropertyName() const {
  return "borderBlockStart";
}


const CSSProperty* BorderBlockStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderMapping());
}

bool BorderBlockStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderMapping().Contains(id);
}


 // border-block-style



const char* BorderBlockStyle::GetPropertyName() const {
  return "border-block-style";
}

const AtomicString& BorderBlockStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-style"));
  return name;
}

const char* BorderBlockStyle::GetJSPropertyName() const {
  return "borderBlockStyle";
}




 // border-block-width



const char* BorderBlockWidth::GetPropertyName() const {
  return "border-block-width";
}

const AtomicString& BorderBlockWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-width"));
  return name;
}

const char* BorderBlockWidth::GetJSPropertyName() const {
  return "borderBlockWidth";
}




 // border-bottom



const char* BorderBottom::GetPropertyName() const {
  return "border-bottom";
}

const AtomicString& BorderBottom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-bottom"));
  return name;
}

const char* BorderBottom::GetJSPropertyName() const {
  return "borderBottom";
}


bool BorderBottom::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderMapping().Contains(id);
}
const CSSProperty& BorderBottom::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderMapping());
}


 // border-color



const char* BorderColor::GetPropertyName() const {
  return "border-color";
}

const AtomicString& BorderColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-color"));
  return name;
}

const char* BorderColor::GetJSPropertyName() const {
  return "borderColor";
}




 // border-image



const char* BorderImage::GetPropertyName() const {
  return "border-image";
}

const AtomicString& BorderImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-image"));
  return name;
}

const char* BorderImage::GetJSPropertyName() const {
  return "borderImage";
}




 // border-inline



const char* BorderInline::GetPropertyName() const {
  return "border-inline";
}

const AtomicString& BorderInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline"));
  return name;
}

const char* BorderInline::GetJSPropertyName() const {
  return "borderInline";
}




 // border-inline-color



const char* BorderInlineColor::GetPropertyName() const {
  return "border-inline-color";
}

const AtomicString& BorderInlineColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-color"));
  return name;
}

const char* BorderInlineColor::GetJSPropertyName() const {
  return "borderInlineColor";
}




 // border-inline-end



const char* BorderInlineEnd::GetPropertyName() const {
  return "border-inline-end";
}

const AtomicString& BorderInlineEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-end"));
  return name;
}

const char* BorderInlineEnd::GetJSPropertyName() const {
  return "borderInlineEnd";
}


const CSSProperty* BorderInlineEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderMapping());
}

bool BorderInlineEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderMapping().Contains(id);
}


 // border-inline-start



const char* BorderInlineStart::GetPropertyName() const {
  return "border-inline-start";
}

const AtomicString& BorderInlineStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-start"));
  return name;
}

const char* BorderInlineStart::GetJSPropertyName() const {
  return "borderInlineStart";
}


const CSSProperty* BorderInlineStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderMapping());
}

bool BorderInlineStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderMapping().Contains(id);
}


 // border-inline-style



const char* BorderInlineStyle::GetPropertyName() const {
  return "border-inline-style";
}

const AtomicString& BorderInlineStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-style"));
  return name;
}

const char* BorderInlineStyle::GetJSPropertyName() const {
  return "borderInlineStyle";
}




 // border-inline-width



const char* BorderInlineWidth::GetPropertyName() const {
  return "border-inline-width";
}

const AtomicString& BorderInlineWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-width"));
  return name;
}

const char* BorderInlineWidth::GetJSPropertyName() const {
  return "borderInlineWidth";
}




 // border-left



const char* BorderLeft::GetPropertyName() const {
  return "border-left";
}

const AtomicString& BorderLeft::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-left"));
  return name;
}

const char* BorderLeft::GetJSPropertyName() const {
  return "borderLeft";
}


bool BorderLeft::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderMapping().Contains(id);
}
const CSSProperty& BorderLeft::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderMapping());
}


 // border-radius



const char* BorderRadius::GetPropertyName() const {
  return "border-radius";
}

const AtomicString& BorderRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-radius"));
  return name;
}

const char* BorderRadius::GetJSPropertyName() const {
  return "borderRadius";
}




 // border-right



const char* BorderRight::GetPropertyName() const {
  return "border-right";
}

const AtomicString& BorderRight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-right"));
  return name;
}

const char* BorderRight::GetJSPropertyName() const {
  return "borderRight";
}


bool BorderRight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderMapping().Contains(id);
}
const CSSProperty& BorderRight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderMapping());
}


 // border-spacing



const char* BorderSpacing::GetPropertyName() const {
  return "border-spacing";
}

const AtomicString& BorderSpacing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-spacing"));
  return name;
}

const char* BorderSpacing::GetJSPropertyName() const {
  return "borderSpacing";
}




 // border-style



const char* BorderStyle::GetPropertyName() const {
  return "border-style";
}

const AtomicString& BorderStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-style"));
  return name;
}

const char* BorderStyle::GetJSPropertyName() const {
  return "borderStyle";
}




 // border-top



const char* BorderTop::GetPropertyName() const {
  return "border-top";
}

const AtomicString& BorderTop::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-top"));
  return name;
}

const char* BorderTop::GetJSPropertyName() const {
  return "borderTop";
}


bool BorderTop::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderMapping().Contains(id);
}
const CSSProperty& BorderTop::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderMapping());
}


 // border-width



const char* BorderWidth::GetPropertyName() const {
  return "border-width";
}

const AtomicString& BorderWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-width"));
  return name;
}

const char* BorderWidth::GetJSPropertyName() const {
  return "borderWidth";
}




 // column-rule



const char* ColumnRule::GetPropertyName() const {
  return "column-rule";
}

const AtomicString& ColumnRule::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule"));
  return name;
}

const char* ColumnRule::GetJSPropertyName() const {
  return "columnRule";
}




 // column-rule-inset


CSSExposure ColumnRuleInset::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInset::GetPropertyName() const {
  return "column-rule-inset";
}

const AtomicString& ColumnRuleInset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset"));
  return name;
}

const char* ColumnRuleInset::GetJSPropertyName() const {
  return "columnRuleInset";
}




 // column-rule-inset-cap


CSSExposure ColumnRuleInsetCap::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetCap::GetPropertyName() const {
  return "column-rule-inset-cap";
}

const AtomicString& ColumnRuleInsetCap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-cap"));
  return name;
}

const char* ColumnRuleInsetCap::GetJSPropertyName() const {
  return "columnRuleInsetCap";
}




 // column-rule-inset-end


CSSExposure ColumnRuleInsetEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetEnd::GetPropertyName() const {
  return "column-rule-inset-end";
}

const AtomicString& ColumnRuleInsetEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-end"));
  return name;
}

const char* ColumnRuleInsetEnd::GetJSPropertyName() const {
  return "columnRuleInsetEnd";
}




 // column-rule-inset-junction


CSSExposure ColumnRuleInsetJunction::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetJunction::GetPropertyName() const {
  return "column-rule-inset-junction";
}

const AtomicString& ColumnRuleInsetJunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-junction"));
  return name;
}

const char* ColumnRuleInsetJunction::GetJSPropertyName() const {
  return "columnRuleInsetJunction";
}




 // column-rule-inset-start


CSSExposure ColumnRuleInsetStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetStart::GetPropertyName() const {
  return "column-rule-inset-start";
}

const AtomicString& ColumnRuleInsetStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-start"));
  return name;
}

const char* ColumnRuleInsetStart::GetJSPropertyName() const {
  return "columnRuleInsetStart";
}




 // columns



const char* Columns::GetPropertyName() const {
  return "columns";
}

const AtomicString& Columns::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("columns"));
  return name;
}

const char* Columns::GetJSPropertyName() const {
  return "columns";
}




 // contain-intrinsic-size



const char* ContainIntrinsicSize::GetPropertyName() const {
  return "contain-intrinsic-size";
}

const AtomicString& ContainIntrinsicSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("contain-intrinsic-size"));
  return name;
}

const char* ContainIntrinsicSize::GetJSPropertyName() const {
  return "containIntrinsicSize";
}




 // container



const char* Container::GetPropertyName() const {
  return "container";
}

const AtomicString& Container::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("container"));
  return name;
}

const char* Container::GetJSPropertyName() const {
  return "container";
}




 // corner-block-end-shape



const char* CornerBlockEndShape::GetPropertyName() const {
  return "corner-block-end-shape";
}

const AtomicString& CornerBlockEndShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-block-end-shape"));
  return name;
}

const char* CornerBlockEndShape::GetJSPropertyName() const {
  return "cornerBlockEndShape";
}




 // corner-block-start-shape



const char* CornerBlockStartShape::GetPropertyName() const {
  return "corner-block-start-shape";
}

const AtomicString& CornerBlockStartShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-block-start-shape"));
  return name;
}

const char* CornerBlockStartShape::GetJSPropertyName() const {
  return "cornerBlockStartShape";
}




 // corner-bottom-shape



const char* CornerBottomShape::GetPropertyName() const {
  return "corner-bottom-shape";
}

const AtomicString& CornerBottomShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-bottom-shape"));
  return name;
}

const char* CornerBottomShape::GetJSPropertyName() const {
  return "cornerBottomShape";
}




 // corner-inline-end-shape



const char* CornerInlineEndShape::GetPropertyName() const {
  return "corner-inline-end-shape";
}

const AtomicString& CornerInlineEndShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-inline-end-shape"));
  return name;
}

const char* CornerInlineEndShape::GetJSPropertyName() const {
  return "cornerInlineEndShape";
}




 // corner-inline-start-shape



const char* CornerInlineStartShape::GetPropertyName() const {
  return "corner-inline-start-shape";
}

const AtomicString& CornerInlineStartShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-inline-start-shape"));
  return name;
}

const char* CornerInlineStartShape::GetJSPropertyName() const {
  return "cornerInlineStartShape";
}




 // corner-left-shape



const char* CornerLeftShape::GetPropertyName() const {
  return "corner-left-shape";
}

const AtomicString& CornerLeftShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-left-shape"));
  return name;
}

const char* CornerLeftShape::GetJSPropertyName() const {
  return "cornerLeftShape";
}




 // corner-right-shape



const char* CornerRightShape::GetPropertyName() const {
  return "corner-right-shape";
}

const AtomicString& CornerRightShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-right-shape"));
  return name;
}

const char* CornerRightShape::GetJSPropertyName() const {
  return "cornerRightShape";
}




 // corner-shape



const char* CornerShape::GetPropertyName() const {
  return "corner-shape";
}

const AtomicString& CornerShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-shape"));
  return name;
}

const char* CornerShape::GetJSPropertyName() const {
  return "cornerShape";
}




 // corner-top-shape



const char* CornerTopShape::GetPropertyName() const {
  return "corner-top-shape";
}

const AtomicString& CornerTopShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-top-shape"));
  return name;
}

const char* CornerTopShape::GetJSPropertyName() const {
  return "cornerTopShape";
}




 // corners


CSSExposure Corners::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSCornersShorthandEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Corners::GetPropertyName() const {
  return "corners";
}

const AtomicString& Corners::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corners"));
  return name;
}

const char* Corners::GetJSPropertyName() const {
  return "corners";
}




 // flex



const char* Flex::GetPropertyName() const {
  return "flex";
}

const AtomicString& Flex::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex"));
  return name;
}

const char* Flex::GetJSPropertyName() const {
  return "flex";
}




 // flex-flow



const char* FlexFlow::GetPropertyName() const {
  return "flex-flow";
}

const AtomicString& FlexFlow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-flow"));
  return name;
}

const char* FlexFlow::GetJSPropertyName() const {
  return "flexFlow";
}




 // font



const char* Font::GetPropertyName() const {
  return "font";
}

const AtomicString& Font::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font"));
  return name;
}

const char* Font::GetJSPropertyName() const {
  return "font";
}




 // font-synthesis



const char* FontSynthesis::GetPropertyName() const {
  return "font-synthesis";
}

const AtomicString& FontSynthesis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-synthesis"));
  return name;
}

const char* FontSynthesis::GetJSPropertyName() const {
  return "fontSynthesis";
}




 // font-variant



const char* FontVariant::GetPropertyName() const {
  return "font-variant";
}

const AtomicString& FontVariant::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant"));
  return name;
}

const char* FontVariant::GetJSPropertyName() const {
  return "fontVariant";
}




 // gap



const char* Gap::GetPropertyName() const {
  return "gap";
}

const AtomicString& Gap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("gap"));
  return name;
}

const char* Gap::GetJSPropertyName() const {
  return "gap";
}




 // grid



const char* Grid::GetPropertyName() const {
  return "grid";
}

const AtomicString& Grid::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid"));
  return name;
}

const char* Grid::GetJSPropertyName() const {
  return "grid";
}




 // grid-area



const char* GridArea::GetPropertyName() const {
  return "grid-area";
}

const AtomicString& GridArea::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-area"));
  return name;
}

const char* GridArea::GetJSPropertyName() const {
  return "gridArea";
}




 // grid-column



const char* GridColumn::GetPropertyName() const {
  return "grid-column";
}

const AtomicString& GridColumn::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-column"));
  return name;
}

const char* GridColumn::GetJSPropertyName() const {
  return "gridColumn";
}




 // grid-lanes


CSSExposure GridLanes::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGridLanesLayoutEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* GridLanes::GetPropertyName() const {
  return "grid-lanes";
}

const AtomicString& GridLanes::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-lanes"));
  return name;
}

const char* GridLanes::GetJSPropertyName() const {
  return "gridLanes";
}




 // grid-row



const char* GridRow::GetPropertyName() const {
  return "grid-row";
}

const AtomicString& GridRow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-row"));
  return name;
}

const char* GridRow::GetJSPropertyName() const {
  return "gridRow";
}




 // grid-template



const char* GridTemplate::GetPropertyName() const {
  return "grid-template";
}

const AtomicString& GridTemplate::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-template"));
  return name;
}

const char* GridTemplate::GetJSPropertyName() const {
  return "gridTemplate";
}




 // inset



const char* Inset::GetPropertyName() const {
  return "inset";
}

const AtomicString& Inset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset"));
  return name;
}

const char* Inset::GetJSPropertyName() const {
  return "inset";
}




 // inset-block



const char* InsetBlock::GetPropertyName() const {
  return "inset-block";
}

const AtomicString& InsetBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset-block"));
  return name;
}

const char* InsetBlock::GetJSPropertyName() const {
  return "insetBlock";
}




 // inset-inline



const char* InsetInline::GetPropertyName() const {
  return "inset-inline";
}

const AtomicString& InsetInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset-inline"));
  return name;
}

const char* InsetInline::GetJSPropertyName() const {
  return "insetInline";
}




 // interest-delay



const char* InterestDelay::GetPropertyName() const {
  return "interest-delay";
}

const AtomicString& InterestDelay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("interest-delay"));
  return name;
}

const char* InterestDelay::GetJSPropertyName() const {
  return "interestDelay";
}




 // line-clamp


CSSExposure LineClamp::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSLineClampEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* LineClamp::GetPropertyName() const {
  return "line-clamp";
}

const AtomicString& LineClamp::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("line-clamp"));
  return name;
}

const char* LineClamp::GetJSPropertyName() const {
  return "lineClamp";
}




 // list-style



const char* ListStyle::GetPropertyName() const {
  return "list-style";
}

const AtomicString& ListStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("list-style"));
  return name;
}

const char* ListStyle::GetJSPropertyName() const {
  return "listStyle";
}




 // margin



const char* Margin::GetPropertyName() const {
  return "margin";
}

const AtomicString& Margin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin"));
  return name;
}

const char* Margin::GetJSPropertyName() const {
  return "margin";
}




 // margin-block



const char* MarginBlock::GetPropertyName() const {
  return "margin-block";
}

const AtomicString& MarginBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-block"));
  return name;
}

const char* MarginBlock::GetJSPropertyName() const {
  return "marginBlock";
}




 // margin-inline



const char* MarginInline::GetPropertyName() const {
  return "margin-inline";
}

const AtomicString& MarginInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-inline"));
  return name;
}

const char* MarginInline::GetJSPropertyName() const {
  return "marginInline";
}




 // marker



const char* Marker::GetPropertyName() const {
  return "marker";
}

const AtomicString& Marker::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("marker"));
  return name;
}

const char* Marker::GetJSPropertyName() const {
  return "marker";
}




 // mask



const char* Mask::GetPropertyName() const {
  return "mask";
}

const AtomicString& Mask::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask"));
  return name;
}

const char* Mask::GetJSPropertyName() const {
  return "mask";
}




 // mask-position



const char* MaskPosition::GetPropertyName() const {
  return "mask-position";
}

const AtomicString& MaskPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-position"));
  return name;
}

const char* MaskPosition::GetJSPropertyName() const {
  return "maskPosition";
}




 // offset



const char* Offset::GetPropertyName() const {
  return "offset";
}

const AtomicString& Offset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("offset"));
  return name;
}

const char* Offset::GetJSPropertyName() const {
  return "offset";
}




 // outline



const char* Outline::GetPropertyName() const {
  return "outline";
}

const AtomicString& Outline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("outline"));
  return name;
}

const char* Outline::GetJSPropertyName() const {
  return "outline";
}




 // overflow



const char* Overflow::GetPropertyName() const {
  return "overflow";
}

const AtomicString& Overflow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow"));
  return name;
}

const char* Overflow::GetJSPropertyName() const {
  return "overflow";
}




 // overscroll-behavior



const char* OverscrollBehavior::GetPropertyName() const {
  return "overscroll-behavior";
}

const AtomicString& OverscrollBehavior::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overscroll-behavior"));
  return name;
}

const char* OverscrollBehavior::GetJSPropertyName() const {
  return "overscrollBehavior";
}




 // padding



const char* Padding::GetPropertyName() const {
  return "padding";
}

const AtomicString& Padding::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding"));
  return name;
}

const char* Padding::GetJSPropertyName() const {
  return "padding";
}




 // padding-block



const char* PaddingBlock::GetPropertyName() const {
  return "padding-block";
}

const AtomicString& PaddingBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-block"));
  return name;
}

const char* PaddingBlock::GetJSPropertyName() const {
  return "paddingBlock";
}




 // padding-inline



const char* PaddingInline::GetPropertyName() const {
  return "padding-inline";
}

const AtomicString& PaddingInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-inline"));
  return name;
}

const char* PaddingInline::GetJSPropertyName() const {
  return "paddingInline";
}




 // page-break-after



const char* PageBreakAfter::GetPropertyName() const {
  return "page-break-after";
}

const AtomicString& PageBreakAfter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("page-break-after"));
  return name;
}

const char* PageBreakAfter::GetJSPropertyName() const {
  return "pageBreakAfter";
}




 // page-break-before



const char* PageBreakBefore::GetPropertyName() const {
  return "page-break-before";
}

const AtomicString& PageBreakBefore::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("page-break-before"));
  return name;
}

const char* PageBreakBefore::GetJSPropertyName() const {
  return "pageBreakBefore";
}




 // page-break-inside



const char* PageBreakInside::GetPropertyName() const {
  return "page-break-inside";
}

const AtomicString& PageBreakInside::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("page-break-inside"));
  return name;
}

const char* PageBreakInside::GetJSPropertyName() const {
  return "pageBreakInside";
}




 // place-content



const char* PlaceContent::GetPropertyName() const {
  return "place-content";
}

const AtomicString& PlaceContent::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("place-content"));
  return name;
}

const char* PlaceContent::GetJSPropertyName() const {
  return "placeContent";
}




 // place-items



const char* PlaceItems::GetPropertyName() const {
  return "place-items";
}

const AtomicString& PlaceItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("place-items"));
  return name;
}

const char* PlaceItems::GetJSPropertyName() const {
  return "placeItems";
}




 // place-self



const char* PlaceSelf::GetPropertyName() const {
  return "place-self";
}

const AtomicString& PlaceSelf::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("place-self"));
  return name;
}

const char* PlaceSelf::GetJSPropertyName() const {
  return "placeSelf";
}




 // position-try



const char* PositionTry::GetPropertyName() const {
  return "position-try";
}

const AtomicString& PositionTry::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position-try"));
  return name;
}

const char* PositionTry::GetJSPropertyName() const {
  return "positionTry";
}




 // row-rule


CSSExposure RowRule::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRule::GetPropertyName() const {
  return "row-rule";
}

const AtomicString& RowRule::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule"));
  return name;
}

const char* RowRule::GetJSPropertyName() const {
  return "rowRule";
}




 // row-rule-inset


CSSExposure RowRuleInset::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInset::GetPropertyName() const {
  return "row-rule-inset";
}

const AtomicString& RowRuleInset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset"));
  return name;
}

const char* RowRuleInset::GetJSPropertyName() const {
  return "rowRuleInset";
}




 // row-rule-inset-cap


CSSExposure RowRuleInsetCap::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetCap::GetPropertyName() const {
  return "row-rule-inset-cap";
}

const AtomicString& RowRuleInsetCap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-cap"));
  return name;
}

const char* RowRuleInsetCap::GetJSPropertyName() const {
  return "rowRuleInsetCap";
}




 // row-rule-inset-end


CSSExposure RowRuleInsetEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetEnd::GetPropertyName() const {
  return "row-rule-inset-end";
}

const AtomicString& RowRuleInsetEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-end"));
  return name;
}

const char* RowRuleInsetEnd::GetJSPropertyName() const {
  return "rowRuleInsetEnd";
}




 // row-rule-inset-junction


CSSExposure RowRuleInsetJunction::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetJunction::GetPropertyName() const {
  return "row-rule-inset-junction";
}

const AtomicString& RowRuleInsetJunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-junction"));
  return name;
}

const char* RowRuleInsetJunction::GetJSPropertyName() const {
  return "rowRuleInsetJunction";
}




 // row-rule-inset-start


CSSExposure RowRuleInsetStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetStart::GetPropertyName() const {
  return "row-rule-inset-start";
}

const AtomicString& RowRuleInsetStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-start"));
  return name;
}

const char* RowRuleInsetStart::GetJSPropertyName() const {
  return "rowRuleInsetStart";
}




 // rule


CSSExposure Rule::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Rule::GetPropertyName() const {
  return "rule";
}

const AtomicString& Rule::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule"));
  return name;
}

const char* Rule::GetJSPropertyName() const {
  return "rule";
}




 // rule-break


CSSExposure RuleBreak::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleBreak::GetPropertyName() const {
  return "rule-break";
}

const AtomicString& RuleBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-break"));
  return name;
}

const char* RuleBreak::GetJSPropertyName() const {
  return "ruleBreak";
}




 // rule-color


CSSExposure RuleColor::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleColor::GetPropertyName() const {
  return "rule-color";
}

const AtomicString& RuleColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-color"));
  return name;
}

const char* RuleColor::GetJSPropertyName() const {
  return "ruleColor";
}




 // rule-inset


CSSExposure RuleInset::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleInset::GetPropertyName() const {
  return "rule-inset";
}

const AtomicString& RuleInset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-inset"));
  return name;
}

const char* RuleInset::GetJSPropertyName() const {
  return "ruleInset";
}




 // rule-inset-cap


CSSExposure RuleInsetCap::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleInsetCap::GetPropertyName() const {
  return "rule-inset-cap";
}

const AtomicString& RuleInsetCap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-inset-cap"));
  return name;
}

const char* RuleInsetCap::GetJSPropertyName() const {
  return "ruleInsetCap";
}




 // rule-inset-end


CSSExposure RuleInsetEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleInsetEnd::GetPropertyName() const {
  return "rule-inset-end";
}

const AtomicString& RuleInsetEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-inset-end"));
  return name;
}

const char* RuleInsetEnd::GetJSPropertyName() const {
  return "ruleInsetEnd";
}




 // rule-inset-junction


CSSExposure RuleInsetJunction::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleInsetJunction::GetPropertyName() const {
  return "rule-inset-junction";
}

const AtomicString& RuleInsetJunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-inset-junction"));
  return name;
}

const char* RuleInsetJunction::GetJSPropertyName() const {
  return "ruleInsetJunction";
}




 // rule-inset-start


CSSExposure RuleInsetStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleInsetStart::GetPropertyName() const {
  return "rule-inset-start";
}

const AtomicString& RuleInsetStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-inset-start"));
  return name;
}

const char* RuleInsetStart::GetJSPropertyName() const {
  return "ruleInsetStart";
}




 // rule-style


CSSExposure RuleStyle::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleStyle::GetPropertyName() const {
  return "rule-style";
}

const AtomicString& RuleStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-style"));
  return name;
}

const char* RuleStyle::GetJSPropertyName() const {
  return "ruleStyle";
}




 // rule-visibility-items


CSSExposure RuleVisibilityItems::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleVisibilityItems::GetPropertyName() const {
  return "rule-visibility-items";
}

const AtomicString& RuleVisibilityItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-visibility-items"));
  return name;
}

const char* RuleVisibilityItems::GetJSPropertyName() const {
  return "ruleVisibilityItems";
}




 // rule-width


CSSExposure RuleWidth::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleWidth::GetPropertyName() const {
  return "rule-width";
}

const AtomicString& RuleWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-width"));
  return name;
}

const char* RuleWidth::GetJSPropertyName() const {
  return "ruleWidth";
}




 // scroll-margin



const char* ScrollMargin::GetPropertyName() const {
  return "scroll-margin";
}

const AtomicString& ScrollMargin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin"));
  return name;
}

const char* ScrollMargin::GetJSPropertyName() const {
  return "scrollMargin";
}




 // scroll-margin-block



const char* ScrollMarginBlock::GetPropertyName() const {
  return "scroll-margin-block";
}

const AtomicString& ScrollMarginBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-block"));
  return name;
}

const char* ScrollMarginBlock::GetJSPropertyName() const {
  return "scrollMarginBlock";
}




 // scroll-margin-inline



const char* ScrollMarginInline::GetPropertyName() const {
  return "scroll-margin-inline";
}

const AtomicString& ScrollMarginInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-inline"));
  return name;
}

const char* ScrollMarginInline::GetJSPropertyName() const {
  return "scrollMarginInline";
}




 // scroll-padding



const char* ScrollPadding::GetPropertyName() const {
  return "scroll-padding";
}

const AtomicString& ScrollPadding::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding"));
  return name;
}

const char* ScrollPadding::GetJSPropertyName() const {
  return "scrollPadding";
}




 // scroll-padding-block



const char* ScrollPaddingBlock::GetPropertyName() const {
  return "scroll-padding-block";
}

const AtomicString& ScrollPaddingBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-block"));
  return name;
}

const char* ScrollPaddingBlock::GetJSPropertyName() const {
  return "scrollPaddingBlock";
}




 // scroll-padding-inline



const char* ScrollPaddingInline::GetPropertyName() const {
  return "scroll-padding-inline";
}

const AtomicString& ScrollPaddingInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-inline"));
  return name;
}

const char* ScrollPaddingInline::GetJSPropertyName() const {
  return "scrollPaddingInline";
}




 // scroll-timeline



const char* ScrollTimeline::GetPropertyName() const {
  return "scroll-timeline";
}

const AtomicString& ScrollTimeline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-timeline"));
  return name;
}

const char* ScrollTimeline::GetJSPropertyName() const {
  return "scrollTimeline";
}




 // text-box



const char* TextBox::GetPropertyName() const {
  return "text-box";
}

const AtomicString& TextBox::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-box"));
  return name;
}

const char* TextBox::GetJSPropertyName() const {
  return "textBox";
}




 // text-decoration



const char* TextDecoration::GetPropertyName() const {
  return "text-decoration";
}

const AtomicString& TextDecoration::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration"));
  return name;
}

const char* TextDecoration::GetJSPropertyName() const {
  return "textDecoration";
}




 // text-emphasis



const char* TextEmphasis::GetPropertyName() const {
  return "text-emphasis";
}

const AtomicString& TextEmphasis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-emphasis"));
  return name;
}

const char* TextEmphasis::GetJSPropertyName() const {
  return "textEmphasis";
}




 // text-spacing


CSSExposure TextSpacing::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSTextSpacingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TextSpacing::GetPropertyName() const {
  return "text-spacing";
}

const AtomicString& TextSpacing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-spacing"));
  return name;
}

const char* TextSpacing::GetJSPropertyName() const {
  return "textSpacing";
}




 // text-wrap



const char* TextWrap::GetPropertyName() const {
  return "text-wrap";
}

const AtomicString& TextWrap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-wrap"));
  return name;
}

const char* TextWrap::GetJSPropertyName() const {
  return "textWrap";
}




 // timeline-trigger


CSSExposure TimelineTrigger::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTrigger::GetPropertyName() const {
  return "timeline-trigger";
}

const AtomicString& TimelineTrigger::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger"));
  return name;
}

const char* TimelineTrigger::GetJSPropertyName() const {
  return "timelineTrigger";
}




 // timeline-trigger-activation-range


CSSExposure TimelineTriggerActivationRange::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerActivationRange::GetPropertyName() const {
  return "timeline-trigger-activation-range";
}

const AtomicString& TimelineTriggerActivationRange::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-activation-range"));
  return name;
}

const char* TimelineTriggerActivationRange::GetJSPropertyName() const {
  return "timelineTriggerActivationRange";
}




 // timeline-trigger-active-range


CSSExposure TimelineTriggerActiveRange::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerActiveRange::GetPropertyName() const {
  return "timeline-trigger-active-range";
}

const AtomicString& TimelineTriggerActiveRange::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-active-range"));
  return name;
}

const char* TimelineTriggerActiveRange::GetJSPropertyName() const {
  return "timelineTriggerActiveRange";
}




 // transition



const char* Transition::GetPropertyName() const {
  return "transition";
}

const AtomicString& Transition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transition"));
  return name;
}

const char* Transition::GetJSPropertyName() const {
  return "transition";
}




 // view-timeline



const char* ViewTimeline::GetPropertyName() const {
  return "view-timeline";
}

const AtomicString& ViewTimeline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-timeline"));
  return name;
}

const char* ViewTimeline::GetJSPropertyName() const {
  return "viewTimeline";
}




 // -webkit-column-break-after



const char* WebkitColumnBreakAfter::GetPropertyName() const {
  return "-webkit-column-break-after";
}

const AtomicString& WebkitColumnBreakAfter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-break-after"));
  return name;
}

const char* WebkitColumnBreakAfter::GetJSPropertyName() const {
  return "webkitColumnBreakAfter";
}




 // -webkit-column-break-before



const char* WebkitColumnBreakBefore::GetPropertyName() const {
  return "-webkit-column-break-before";
}

const AtomicString& WebkitColumnBreakBefore::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-break-before"));
  return name;
}

const char* WebkitColumnBreakBefore::GetJSPropertyName() const {
  return "webkitColumnBreakBefore";
}




 // -webkit-column-break-inside



const char* WebkitColumnBreakInside::GetPropertyName() const {
  return "-webkit-column-break-inside";
}

const AtomicString& WebkitColumnBreakInside::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-break-inside"));
  return name;
}

const char* WebkitColumnBreakInside::GetJSPropertyName() const {
  return "webkitColumnBreakInside";
}




 // -webkit-mask-box-image



const char* WebkitMaskBoxImage::GetPropertyName() const {
  return "-webkit-mask-box-image";
}

const AtomicString& WebkitMaskBoxImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-box-image"));
  return name;
}

const char* WebkitMaskBoxImage::GetJSPropertyName() const {
  return "webkitMaskBoxImage";
}




 // -webkit-text-stroke



const char* WebkitTextStroke::GetPropertyName() const {
  return "-webkit-text-stroke";
}

const AtomicString& WebkitTextStroke::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-stroke"));
  return name;
}

const char* WebkitTextStroke::GetJSPropertyName() const {
  return "webkitTextStroke";
}




 // white-space



const char* WhiteSpace::GetPropertyName() const {
  return "white-space";
}

const AtomicString& WhiteSpace::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("white-space"));
  return name;
}

const char* WhiteSpace::GetJSPropertyName() const {
  return "whiteSpace";
}




 // -webkit-border-after



const char* WebkitBorderAfter::GetPropertyName() const {
  return "-webkit-border-after";
}

const AtomicString& WebkitBorderAfter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-after"));
  return name;
}

const char* WebkitBorderAfter::GetJSPropertyName() const {
  return "webkitBorderAfter";
}

 // -webkit-border-before



const char* WebkitBorderBefore::GetPropertyName() const {
  return "-webkit-border-before";
}

const AtomicString& WebkitBorderBefore::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-before"));
  return name;
}

const char* WebkitBorderBefore::GetJSPropertyName() const {
  return "webkitBorderBefore";
}

 // -webkit-border-end



const char* WebkitBorderEnd::GetPropertyName() const {
  return "-webkit-border-end";
}

const AtomicString& WebkitBorderEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-end"));
  return name;
}

const char* WebkitBorderEnd::GetJSPropertyName() const {
  return "webkitBorderEnd";
}

 // -webkit-border-start



const char* WebkitBorderStart::GetPropertyName() const {
  return "-webkit-border-start";
}

const AtomicString& WebkitBorderStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-start"));
  return name;
}

const char* WebkitBorderStart::GetJSPropertyName() const {
  return "webkitBorderStart";
}

 // -webkit-mask



const char* WebkitMask::GetPropertyName() const {
  return "-webkit-mask";
}

const AtomicString& WebkitMask::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask"));
  return name;
}

const char* WebkitMask::GetJSPropertyName() const {
  return "webkitMask";
}

 // -webkit-mask-position



const char* WebkitMaskPosition::GetPropertyName() const {
  return "-webkit-mask-position";
}

const AtomicString& WebkitMaskPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-position"));
  return name;
}

const char* WebkitMaskPosition::GetJSPropertyName() const {
  return "webkitMaskPosition";
}

 // -epub-text-emphasis



const char* EpubTextEmphasis::GetPropertyName() const {
  return "-epub-text-emphasis";
}

const AtomicString& EpubTextEmphasis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-text-emphasis"));
  return name;
}

const char* EpubTextEmphasis::GetJSPropertyName() const {
  return "epubTextEmphasis";
}

 // -webkit-animation



const char* WebkitAnimation::GetPropertyName() const {
  return "-webkit-animation";
}

const AtomicString& WebkitAnimation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation"));
  return name;
}

const char* WebkitAnimation::GetJSPropertyName() const {
  return "webkitAnimation";
}

 // -webkit-border-radius



const char* WebkitBorderRadius::GetPropertyName() const {
  return "-webkit-border-radius";
}

const AtomicString& WebkitBorderRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-radius"));
  return name;
}

const char* WebkitBorderRadius::GetJSPropertyName() const {
  return "webkitBorderRadius";
}

 // -webkit-column-rule



const char* WebkitColumnRule::GetPropertyName() const {
  return "-webkit-column-rule";
}

const AtomicString& WebkitColumnRule::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-rule"));
  return name;
}

const char* WebkitColumnRule::GetJSPropertyName() const {
  return "webkitColumnRule";
}

 // -webkit-columns



const char* WebkitColumns::GetPropertyName() const {
  return "-webkit-columns";
}

const AtomicString& WebkitColumns::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-columns"));
  return name;
}

const char* WebkitColumns::GetJSPropertyName() const {
  return "webkitColumns";
}

 // -webkit-flex



const char* WebkitFlex::GetPropertyName() const {
  return "-webkit-flex";
}

const AtomicString& WebkitFlex::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex"));
  return name;
}

const char* WebkitFlex::GetJSPropertyName() const {
  return "webkitFlex";
}

 // -webkit-flex-flow



const char* WebkitFlexFlow::GetPropertyName() const {
  return "-webkit-flex-flow";
}

const AtomicString& WebkitFlexFlow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex-flow"));
  return name;
}

const char* WebkitFlexFlow::GetJSPropertyName() const {
  return "webkitFlexFlow";
}

 // -webkit-text-emphasis



const char* WebkitTextEmphasis::GetPropertyName() const {
  return "-webkit-text-emphasis";
}

const AtomicString& WebkitTextEmphasis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-emphasis"));
  return name;
}

const char* WebkitTextEmphasis::GetJSPropertyName() const {
  return "webkitTextEmphasis";
}

 // -webkit-transition



const char* WebkitTransition::GetPropertyName() const {
  return "-webkit-transition";
}

const AtomicString& WebkitTransition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transition"));
  return name;
}

const char* WebkitTransition::GetJSPropertyName() const {
  return "webkitTransition";
}

 // grid-gap



const char* GridGap::GetPropertyName() const {
  return "grid-gap";
}

const AtomicString& GridGap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-gap"));
  return name;
}

const char* GridGap::GetJSPropertyName() const {
  return "gridGap";
}

  
}  // namespace css_shorthand
}  // namespace blink
