// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   core/css/properties/templates/css_properties.h.tmpl
// and input files:
//   third_party\blink\renderer\core\css\computed_style_field_aliases.json5
//   third_party\blink\renderer\core\css\css_properties.json5
//   third_party\blink\renderer\core\css\properties\css_property_methods.json5
//   third_party\blink\renderer\platform\runtime_enabled_features.json5



#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_PROPERTIES_CSS_PROPERTIES_SHORTHANDS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_PROPERTIES_CSS_PROPERTIES_SHORTHANDS_H_

#include "third_party/blink/renderer/core/css/properties/shorthand.h"

namespace blink {

class ComputedStyle;
class CSSParserContext;
class CSSParserLocalContext;
class CSSValue;
class LayoutObject;
class Node;

namespace css_shorthand {

// -alternative-webkit-line-clamp
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AlternativeWebkitLineClamp final : public Shorthand {
 public:
  constexpr AlternativeWebkitLineClamp() : Shorthand(CSSPropertyID::kAlternativeWebkitLineClamp, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// animation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Animation final : public Shorthand {
 public:
  constexpr Animation() : Shorthand(CSSPropertyID::kAnimation, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// animation-range
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationRange final : public Shorthand {
 public:
  constexpr AnimationRange() : Shorthand(CSSPropertyID::kAnimationRange, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// background
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Background final : public Shorthand {
 public:
  constexpr Background() : Shorthand(CSSPropertyID::kBackground, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// background-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundPosition final : public Shorthand {
 public:
  constexpr BackgroundPosition() : Shorthand(CSSPropertyID::kBackgroundPosition, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Border final : public Shorthand {
 public:
  constexpr Border() : Shorthand(CSSPropertyID::kBorder, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlock final : public Shorthand {
 public:
  constexpr BorderBlock() : Shorthand(CSSPropertyID::kBorderBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-block-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockColor final : public Shorthand {
 public:
  constexpr BorderBlockColor() : Shorthand(CSSPropertyID::kBorderBlockColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-block-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockEnd final : public Shorthand {
 public:
  constexpr BorderBlockEnd() : Shorthand(CSSPropertyID::kBorderBlockEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToPhysicalInternal(
      WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(
      const ComputedStyle&,
      const LayoutObject*,
      bool allow_visited_style,
      CSSValuePhase value_phase) const override {
    // Directional properties are resolved by CSSDirectionAwareResolver
    // before calling CSSValueFromComputedStyleInternal.
    NOTREACHED();
  }
 };

// border-block-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockStart final : public Shorthand {
 public:
  constexpr BorderBlockStart() : Shorthand(CSSPropertyID::kBorderBlockStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToPhysicalInternal(
      WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(
      const ComputedStyle&,
      const LayoutObject*,
      bool allow_visited_style,
      CSSValuePhase value_phase) const override {
    // Directional properties are resolved by CSSDirectionAwareResolver
    // before calling CSSValueFromComputedStyleInternal.
    NOTREACHED();
  }
 };

// border-block-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockStyle final : public Shorthand {
 public:
  constexpr BorderBlockStyle() : Shorthand(CSSPropertyID::kBorderBlockStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-block-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockWidth final : public Shorthand {
 public:
  constexpr BorderBlockWidth() : Shorthand(CSSPropertyID::kBorderBlockWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-bottom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBottom final : public Shorthand {
 public:
  constexpr BorderBottom() : Shorthand(CSSPropertyID::kBorderBottom, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
 };

// border-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderColor final : public Shorthand {
 public:
  constexpr BorderColor() : Shorthand(CSSPropertyID::kBorderColor, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderImage final : public Shorthand {
 public:
  constexpr BorderImage() : Shorthand(CSSPropertyID::kBorderImage, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInline final : public Shorthand {
 public:
  constexpr BorderInline() : Shorthand(CSSPropertyID::kBorderInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-inline-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineColor final : public Shorthand {
 public:
  constexpr BorderInlineColor() : Shorthand(CSSPropertyID::kBorderInlineColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-inline-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineEnd final : public Shorthand {
 public:
  constexpr BorderInlineEnd() : Shorthand(CSSPropertyID::kBorderInlineEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToPhysicalInternal(
      WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(
      const ComputedStyle&,
      const LayoutObject*,
      bool allow_visited_style,
      CSSValuePhase value_phase) const override {
    // Directional properties are resolved by CSSDirectionAwareResolver
    // before calling CSSValueFromComputedStyleInternal.
    NOTREACHED();
  }
 };

// border-inline-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineStart final : public Shorthand {
 public:
  constexpr BorderInlineStart() : Shorthand(CSSPropertyID::kBorderInlineStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToPhysicalInternal(
      WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(
      const ComputedStyle&,
      const LayoutObject*,
      bool allow_visited_style,
      CSSValuePhase value_phase) const override {
    // Directional properties are resolved by CSSDirectionAwareResolver
    // before calling CSSValueFromComputedStyleInternal.
    NOTREACHED();
  }
 };

// border-inline-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineStyle final : public Shorthand {
 public:
  constexpr BorderInlineStyle() : Shorthand(CSSPropertyID::kBorderInlineStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-inline-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineWidth final : public Shorthand {
 public:
  constexpr BorderInlineWidth() : Shorthand(CSSPropertyID::kBorderInlineWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-left
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderLeft final : public Shorthand {
 public:
  constexpr BorderLeft() : Shorthand(CSSPropertyID::kBorderLeft, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
 };

// border-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderRadius final : public Shorthand {
 public:
  constexpr BorderRadius() : Shorthand(CSSPropertyID::kBorderRadius, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-right
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderRight final : public Shorthand {
 public:
  constexpr BorderRight() : Shorthand(CSSPropertyID::kBorderRight, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
 };

// border-spacing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderSpacing final : public Shorthand {
 public:
  constexpr BorderSpacing() : Shorthand(CSSPropertyID::kBorderSpacing, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderStyle final : public Shorthand {
 public:
  constexpr BorderStyle() : Shorthand(CSSPropertyID::kBorderStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// border-top
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderTop final : public Shorthand {
 public:
  constexpr BorderTop() : Shorthand(CSSPropertyID::kBorderTop, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
 };

// border-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderWidth final : public Shorthand {
 public:
  constexpr BorderWidth() : Shorthand(CSSPropertyID::kBorderWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// column-rule
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRule final : public Shorthand {
 public:
  constexpr ColumnRule() : Shorthand(CSSPropertyID::kColumnRule, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// column-rule-inset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInset final : public Shorthand {
 public:
  constexpr ColumnRuleInset() : Shorthand(CSSPropertyID::kColumnRuleInset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// column-rule-inset-cap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetCap final : public Shorthand {
 public:
  constexpr ColumnRuleInsetCap() : Shorthand(CSSPropertyID::kColumnRuleInsetCap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// column-rule-inset-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetEnd final : public Shorthand {
 public:
  constexpr ColumnRuleInsetEnd() : Shorthand(CSSPropertyID::kColumnRuleInsetEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// column-rule-inset-junction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetJunction final : public Shorthand {
 public:
  constexpr ColumnRuleInsetJunction() : Shorthand(CSSPropertyID::kColumnRuleInsetJunction, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// column-rule-inset-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetStart final : public Shorthand {
 public:
  constexpr ColumnRuleInsetStart() : Shorthand(CSSPropertyID::kColumnRuleInsetStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// columns
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Columns final : public Shorthand {
 public:
  constexpr Columns() : Shorthand(CSSPropertyID::kColumns, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// contain-intrinsic-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainIntrinsicSize final : public Shorthand {
 public:
  constexpr ContainIntrinsicSize() : Shorthand(CSSPropertyID::kContainIntrinsicSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// container
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Container final : public Shorthand {
 public:
  constexpr Container() : Shorthand(CSSPropertyID::kContainer, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-block-end-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerBlockEndShape final : public Shorthand {
 public:
  constexpr CornerBlockEndShape() : Shorthand(CSSPropertyID::kCornerBlockEndShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-block-start-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerBlockStartShape final : public Shorthand {
 public:
  constexpr CornerBlockStartShape() : Shorthand(CSSPropertyID::kCornerBlockStartShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-bottom-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerBottomShape final : public Shorthand {
 public:
  constexpr CornerBottomShape() : Shorthand(CSSPropertyID::kCornerBottomShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-inline-end-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerInlineEndShape final : public Shorthand {
 public:
  constexpr CornerInlineEndShape() : Shorthand(CSSPropertyID::kCornerInlineEndShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-inline-start-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerInlineStartShape final : public Shorthand {
 public:
  constexpr CornerInlineStartShape() : Shorthand(CSSPropertyID::kCornerInlineStartShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-left-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerLeftShape final : public Shorthand {
 public:
  constexpr CornerLeftShape() : Shorthand(CSSPropertyID::kCornerLeftShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-right-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerRightShape final : public Shorthand {
 public:
  constexpr CornerRightShape() : Shorthand(CSSPropertyID::kCornerRightShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerShape final : public Shorthand {
 public:
  constexpr CornerShape() : Shorthand(CSSPropertyID::kCornerShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corner-top-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerTopShape final : public Shorthand {
 public:
  constexpr CornerTopShape() : Shorthand(CSSPropertyID::kCornerTopShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// corners
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Corners final : public Shorthand {
 public:
  constexpr Corners() : Shorthand(CSSPropertyID::kCorners, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// flex
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Flex final : public Shorthand {
 public:
  constexpr Flex() : Shorthand(CSSPropertyID::kFlex, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// flex-flow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexFlow final : public Shorthand {
 public:
  constexpr FlexFlow() : Shorthand(CSSPropertyID::kFlexFlow, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// font
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Font final : public Shorthand {
 public:
  constexpr Font() : Shorthand(CSSPropertyID::kFont, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// font-synthesis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontSynthesis final : public Shorthand {
 public:
  constexpr FontSynthesis() : Shorthand(CSSPropertyID::kFontSynthesis, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// font-variant
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariant final : public Shorthand {
 public:
  constexpr FontVariant() : Shorthand(CSSPropertyID::kFontVariant, kDescriptor | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Gap final : public Shorthand {
 public:
  constexpr Gap() : Shorthand(CSSPropertyID::kGap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// grid
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Grid final : public Shorthand {
 public:
  constexpr Grid() : Shorthand(CSSPropertyID::kGrid, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// grid-area
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridArea final : public Shorthand {
 public:
  constexpr GridArea() : Shorthand(CSSPropertyID::kGridArea, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// grid-column
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridColumn final : public Shorthand {
 public:
  constexpr GridColumn() : Shorthand(CSSPropertyID::kGridColumn, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// grid-lanes
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridLanes final : public Shorthand {
 public:
  constexpr GridLanes() : Shorthand(CSSPropertyID::kGridLanes, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// grid-row
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridRow final : public Shorthand {
 public:
  constexpr GridRow() : Shorthand(CSSPropertyID::kGridRow, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// grid-template
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridTemplate final : public Shorthand {
 public:
  constexpr GridTemplate() : Shorthand(CSSPropertyID::kGridTemplate, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// inset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Inset final : public Shorthand {
 public:
  constexpr Inset() : Shorthand(CSSPropertyID::kInset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// inset-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InsetBlock final : public Shorthand {
 public:
  constexpr InsetBlock() : Shorthand(CSSPropertyID::kInsetBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// inset-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InsetInline final : public Shorthand {
 public:
  constexpr InsetInline() : Shorthand(CSSPropertyID::kInsetInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// interest-delay
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InterestDelay final : public Shorthand {
 public:
  constexpr InterestDelay() : Shorthand(CSSPropertyID::kInterestDelay, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// line-clamp
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT LineClamp final : public Shorthand {
 public:
  constexpr LineClamp() : Shorthand(CSSPropertyID::kLineClamp, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// list-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ListStyle final : public Shorthand {
 public:
  constexpr ListStyle() : Shorthand(CSSPropertyID::kListStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// margin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Margin final : public Shorthand {
 public:
  constexpr Margin() : Shorthand(CSSPropertyID::kMargin, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// margin-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginBlock final : public Shorthand {
 public:
  constexpr MarginBlock() : Shorthand(CSSPropertyID::kMarginBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// margin-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginInline final : public Shorthand {
 public:
  constexpr MarginInline() : Shorthand(CSSPropertyID::kMarginInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// marker
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Marker final : public Shorthand {
 public:
  constexpr Marker() : Shorthand(CSSPropertyID::kMarker, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// mask
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Mask final : public Shorthand {
 public:
  constexpr Mask() : Shorthand(CSSPropertyID::kMask, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// mask-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskPosition final : public Shorthand {
 public:
  constexpr MaskPosition() : Shorthand(CSSPropertyID::kMaskPosition, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// offset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Offset final : public Shorthand {
 public:
  constexpr Offset() : Shorthand(CSSPropertyID::kOffset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// outline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Outline final : public Shorthand {
 public:
  constexpr Outline() : Shorthand(CSSPropertyID::kOutline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// overflow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Overflow final : public Shorthand {
 public:
  constexpr Overflow() : Shorthand(CSSPropertyID::kOverflow, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// overscroll-behavior
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverscrollBehavior final : public Shorthand {
 public:
  constexpr OverscrollBehavior() : Shorthand(CSSPropertyID::kOverscrollBehavior, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// padding
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Padding final : public Shorthand {
 public:
  constexpr Padding() : Shorthand(CSSPropertyID::kPadding, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// padding-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingBlock final : public Shorthand {
 public:
  constexpr PaddingBlock() : Shorthand(CSSPropertyID::kPaddingBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// padding-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingInline final : public Shorthand {
 public:
  constexpr PaddingInline() : Shorthand(CSSPropertyID::kPaddingInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// page-break-after
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PageBreakAfter final : public Shorthand {
 public:
  constexpr PageBreakAfter() : Shorthand(CSSPropertyID::kPageBreakAfter, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// page-break-before
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PageBreakBefore final : public Shorthand {
 public:
  constexpr PageBreakBefore() : Shorthand(CSSPropertyID::kPageBreakBefore, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// page-break-inside
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PageBreakInside final : public Shorthand {
 public:
  constexpr PageBreakInside() : Shorthand(CSSPropertyID::kPageBreakInside, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// place-content
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PlaceContent final : public Shorthand {
 public:
  constexpr PlaceContent() : Shorthand(CSSPropertyID::kPlaceContent, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// place-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PlaceItems final : public Shorthand {
 public:
  constexpr PlaceItems() : Shorthand(CSSPropertyID::kPlaceItems, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// place-self
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PlaceSelf final : public Shorthand {
 public:
  constexpr PlaceSelf() : Shorthand(CSSPropertyID::kPlaceSelf, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// position-try
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PositionTry final : public Shorthand {
 public:
  constexpr PositionTry() : Shorthand(CSSPropertyID::kPositionTry, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// row-rule
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRule final : public Shorthand {
 public:
  constexpr RowRule() : Shorthand(CSSPropertyID::kRowRule, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// row-rule-inset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInset final : public Shorthand {
 public:
  constexpr RowRuleInset() : Shorthand(CSSPropertyID::kRowRuleInset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// row-rule-inset-cap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetCap final : public Shorthand {
 public:
  constexpr RowRuleInsetCap() : Shorthand(CSSPropertyID::kRowRuleInsetCap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// row-rule-inset-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetEnd final : public Shorthand {
 public:
  constexpr RowRuleInsetEnd() : Shorthand(CSSPropertyID::kRowRuleInsetEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// row-rule-inset-junction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetJunction final : public Shorthand {
 public:
  constexpr RowRuleInsetJunction() : Shorthand(CSSPropertyID::kRowRuleInsetJunction, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// row-rule-inset-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetStart final : public Shorthand {
 public:
  constexpr RowRuleInsetStart() : Shorthand(CSSPropertyID::kRowRuleInsetStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Rule final : public Shorthand {
 public:
  constexpr Rule() : Shorthand(CSSPropertyID::kRule, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleBreak final : public Shorthand {
 public:
  constexpr RuleBreak() : Shorthand(CSSPropertyID::kRuleBreak, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleColor final : public Shorthand {
 public:
  constexpr RuleColor() : Shorthand(CSSPropertyID::kRuleColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-inset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleInset final : public Shorthand {
 public:
  constexpr RuleInset() : Shorthand(CSSPropertyID::kRuleInset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-inset-cap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleInsetCap final : public Shorthand {
 public:
  constexpr RuleInsetCap() : Shorthand(CSSPropertyID::kRuleInsetCap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-inset-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleInsetEnd final : public Shorthand {
 public:
  constexpr RuleInsetEnd() : Shorthand(CSSPropertyID::kRuleInsetEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-inset-junction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleInsetJunction final : public Shorthand {
 public:
  constexpr RuleInsetJunction() : Shorthand(CSSPropertyID::kRuleInsetJunction, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-inset-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleInsetStart final : public Shorthand {
 public:
  constexpr RuleInsetStart() : Shorthand(CSSPropertyID::kRuleInsetStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleStyle final : public Shorthand {
 public:
  constexpr RuleStyle() : Shorthand(CSSPropertyID::kRuleStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-visibility-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleVisibilityItems final : public Shorthand {
 public:
  constexpr RuleVisibilityItems() : Shorthand(CSSPropertyID::kRuleVisibilityItems, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// rule-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleWidth final : public Shorthand {
 public:
  constexpr RuleWidth() : Shorthand(CSSPropertyID::kRuleWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-margin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMargin final : public Shorthand {
 public:
  constexpr ScrollMargin() : Shorthand(CSSPropertyID::kScrollMargin, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-margin-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginBlock final : public Shorthand {
 public:
  constexpr ScrollMarginBlock() : Shorthand(CSSPropertyID::kScrollMarginBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-margin-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginInline final : public Shorthand {
 public:
  constexpr ScrollMarginInline() : Shorthand(CSSPropertyID::kScrollMarginInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-padding
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPadding final : public Shorthand {
 public:
  constexpr ScrollPadding() : Shorthand(CSSPropertyID::kScrollPadding, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-padding-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingBlock final : public Shorthand {
 public:
  constexpr ScrollPaddingBlock() : Shorthand(CSSPropertyID::kScrollPaddingBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-padding-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingInline final : public Shorthand {
 public:
  constexpr ScrollPaddingInline() : Shorthand(CSSPropertyID::kScrollPaddingInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// scroll-timeline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollTimeline final : public Shorthand {
 public:
  constexpr ScrollTimeline() : Shorthand(CSSPropertyID::kScrollTimeline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// text-box
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextBox final : public Shorthand {
 public:
  constexpr TextBox() : Shorthand(CSSPropertyID::kTextBox, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// text-decoration
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecoration final : public Shorthand {
 public:
  constexpr TextDecoration() : Shorthand(CSSPropertyID::kTextDecoration, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// text-emphasis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextEmphasis final : public Shorthand {
 public:
  constexpr TextEmphasis() : Shorthand(CSSPropertyID::kTextEmphasis, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// text-spacing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextSpacing final : public Shorthand {
 public:
  constexpr TextSpacing() : Shorthand(CSSPropertyID::kTextSpacing, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// text-wrap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextWrap final : public Shorthand {
 public:
  constexpr TextWrap() : Shorthand(CSSPropertyID::kTextWrap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// timeline-trigger
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTrigger final : public Shorthand {
 public:
  constexpr TimelineTrigger() : Shorthand(CSSPropertyID::kTimelineTrigger, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// timeline-trigger-activation-range
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerActivationRange final : public Shorthand {
 public:
  constexpr TimelineTriggerActivationRange() : Shorthand(CSSPropertyID::kTimelineTriggerActivationRange, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// timeline-trigger-active-range
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerActiveRange final : public Shorthand {
 public:
  constexpr TimelineTriggerActiveRange() : Shorthand(CSSPropertyID::kTimelineTriggerActiveRange, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// transition
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Transition final : public Shorthand {
 public:
  constexpr Transition() : Shorthand(CSSPropertyID::kTransition, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// view-timeline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTimeline final : public Shorthand {
 public:
  constexpr ViewTimeline() : Shorthand(CSSPropertyID::kViewTimeline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-column-break-after
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnBreakAfter final : public Shorthand {
 public:
  constexpr WebkitColumnBreakAfter() : Shorthand(CSSPropertyID::kWebkitColumnBreakAfter, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-column-break-before
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnBreakBefore final : public Shorthand {
 public:
  constexpr WebkitColumnBreakBefore() : Shorthand(CSSPropertyID::kWebkitColumnBreakBefore, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-column-break-inside
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnBreakInside final : public Shorthand {
 public:
  constexpr WebkitColumnBreakInside() : Shorthand(CSSPropertyID::kWebkitColumnBreakInside, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-mask-box-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskBoxImage final : public Shorthand {
 public:
  constexpr WebkitMaskBoxImage() : Shorthand(CSSPropertyID::kWebkitMaskBoxImage, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-text-stroke
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextStroke final : public Shorthand {
 public:
  constexpr WebkitTextStroke() : Shorthand(CSSPropertyID::kWebkitTextStroke, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// white-space
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WhiteSpace final : public Shorthand {
 public:
  constexpr WhiteSpace() : Shorthand(CSSPropertyID::kWhiteSpace, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool ParseShorthand(bool, CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&, HeapVector<CSSPropertyValue, 64>&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-border-after
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderAfter final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderAfter() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-before
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderBefore final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderBefore() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderEnd final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderEnd() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderStart final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderStart() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMask final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMask() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskPosition final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskPosition() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-text-emphasis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubTextEmphasis final : public CSSUnresolvedProperty {
 public:
  constexpr EpubTextEmphasis() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimation final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimation() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderRadius final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderRadius() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-rule
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnRule final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnRule() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-columns
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumns final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumns() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlex final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlex() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex-flow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlexFlow final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlexFlow() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-text-emphasis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextEmphasis final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTextEmphasis() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transition
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransition final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransition() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// grid-gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridGap final : public CSSUnresolvedProperty {
 public:
  constexpr GridGap() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

 
}  // namespace css_shorthand
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_PROPERTIES_CSS_PROPERTIES_SHORTHANDS_H_
