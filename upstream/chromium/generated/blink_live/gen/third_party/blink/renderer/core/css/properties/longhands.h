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



#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CSS_PROPERTIES_CSS_PROPERTIES_LONGHANDS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CSS_PROPERTIES_CSS_PROPERTIES_LONGHANDS_H_

#include "third_party/blink/renderer/core/css/properties/longhand.h"

namespace blink {

class ComputedStyle;
class CSSParserContext;
class CSSParserLocalContext;
class CSSValue;
class LayoutObject;
class Node;

namespace css_longhand {

// color-scheme
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColorScheme final : public Longhand {
 public:
  constexpr ColorScheme() : Longhand(CSSPropertyID::kColorScheme, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// forced-color-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ForcedColorAdjust final : public Longhand {
 public:
  constexpr ForcedColorAdjust() : Longhand(CSSPropertyID::kForcedColorAdjust, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// math-depth
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MathDepth final : public Longhand {
 public:
  constexpr MathDepth() : Longhand(CSSPropertyID::kMathDepth, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Position final : public Longhand {
 public:
  constexpr Position() : Longhand(CSSPropertyID::kPosition, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// position-anchor
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PositionAnchor final : public Longhand {
 public:
  constexpr PositionAnchor() : Longhand(CSSPropertyID::kPositionAnchor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-size-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextSizeAdjust final : public Longhand {
 public:
  constexpr TextSizeAdjust() : Longhand(CSSPropertyID::kTextSizeAdjust, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedColor final : public Longhand {
 public:
  constexpr InternalVisitedColor() : Longhand(CSSPropertyID::kInternalVisitedColor, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kVisitedHighlightColors | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// appearance
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Appearance final : public Longhand {
 public:
  constexpr Appearance() : Longhand(CSSPropertyID::kAppearance, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Color final : public Longhand {
 public:
  constexpr Color() : Longhand(CSSPropertyID::kColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kHighlightColors | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Direction final : public Longhand {
 public:
  constexpr Direction() : Longhand(CSSPropertyID::kDirection, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-family
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontFamily final : public Longhand {
 public:
  constexpr FontFamily() : Longhand(CSSPropertyID::kFontFamily, kDescriptor | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-feature-settings
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontFeatureSettings final : public Longhand {
 public:
  constexpr FontFeatureSettings() : Longhand(CSSPropertyID::kFontFeatureSettings, kDescriptor | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-kerning
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontKerning final : public Longhand {
 public:
  constexpr FontKerning() : Longhand(CSSPropertyID::kFontKerning, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-language-override
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontLanguageOverride final : public Longhand {
 public:
  constexpr FontLanguageOverride() : Longhand(CSSPropertyID::kFontLanguageOverride, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-optical-sizing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontOpticalSizing final : public Longhand {
 public:
  constexpr FontOpticalSizing() : Longhand(CSSPropertyID::kFontOpticalSizing, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-palette
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontPalette final : public Longhand {
 public:
  constexpr FontPalette() : Longhand(CSSPropertyID::kFontPalette, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontSize final : public Longhand {
 public:
  constexpr FontSize() : Longhand(CSSPropertyID::kFontSize, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kAffectsFont | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-size-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontSizeAdjust final : public Longhand {
 public:
  constexpr FontSizeAdjust() : Longhand(CSSPropertyID::kFontSizeAdjust, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-stretch
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontStretch final : public Longhand {
 public:
  constexpr FontStretch() : Longhand(CSSPropertyID::kFontStretch, kInterpolable | kDescriptor | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kAffectsFont | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontStyle final : public Longhand {
 public:
  constexpr FontStyle() : Longhand(CSSPropertyID::kFontStyle, kInterpolable | kDescriptor | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-synthesis-small-caps
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontSynthesisSmallCaps final : public Longhand {
 public:
  constexpr FontSynthesisSmallCaps() : Longhand(CSSPropertyID::kFontSynthesisSmallCaps, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-synthesis-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontSynthesisStyle final : public Longhand {
 public:
  constexpr FontSynthesisStyle() : Longhand(CSSPropertyID::kFontSynthesisStyle, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-synthesis-weight
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontSynthesisWeight final : public Longhand {
 public:
  constexpr FontSynthesisWeight() : Longhand(CSSPropertyID::kFontSynthesisWeight, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-alternates
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantAlternates final : public Longhand {
 public:
  constexpr FontVariantAlternates() : Longhand(CSSPropertyID::kFontVariantAlternates, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-caps
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantCaps final : public Longhand {
 public:
  constexpr FontVariantCaps() : Longhand(CSSPropertyID::kFontVariantCaps, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-east-asian
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantEastAsian final : public Longhand {
 public:
  constexpr FontVariantEastAsian() : Longhand(CSSPropertyID::kFontVariantEastAsian, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-emoji
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantEmoji final : public Longhand {
 public:
  constexpr FontVariantEmoji() : Longhand(CSSPropertyID::kFontVariantEmoji, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-ligatures
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantLigatures final : public Longhand {
 public:
  constexpr FontVariantLigatures() : Longhand(CSSPropertyID::kFontVariantLigatures, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-numeric
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantNumeric final : public Longhand {
 public:
  constexpr FontVariantNumeric() : Longhand(CSSPropertyID::kFontVariantNumeric, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variant-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariantPosition final : public Longhand {
 public:
  constexpr FontVariantPosition() : Longhand(CSSPropertyID::kFontVariantPosition, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-variation-settings
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontVariationSettings final : public Longhand {
 public:
  constexpr FontVariationSettings() : Longhand(CSSPropertyID::kFontVariationSettings, kInterpolable | kDescriptor | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-weight
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontWeight final : public Longhand {
 public:
  constexpr FontWeight() : Longhand(CSSPropertyID::kFontWeight, kInterpolable | kDescriptor | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// position-area
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PositionArea final : public Longhand {
 public:
  constexpr PositionArea() : Longhand(CSSPropertyID::kPositionArea, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-orientation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextOrientation final : public Longhand {
 public:
  constexpr TextOrientation() : Longhand(CSSPropertyID::kTextOrientation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-rendering
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextRendering final : public Longhand {
 public:
  constexpr TextRendering() : Longhand(CSSPropertyID::kTextRendering, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-spacing-trim
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextSpacingTrim final : public Longhand {
 public:
  constexpr TextSpacingTrim() : Longhand(CSSPropertyID::kTextSpacingTrim, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-font-smoothing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFontSmoothing final : public Longhand {
 public:
  constexpr WebkitFontSmoothing() : Longhand(CSSPropertyID::kWebkitFontSmoothing, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPermissionElement | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-locale
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitLocale final : public Longhand {
 public:
  constexpr WebkitLocale() : Longhand(CSSPropertyID::kWebkitLocale, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kAffectsFont, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-text-orientation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextOrientation final : public Longhand {
 public:
  constexpr WebkitTextOrientation() : Longhand(CSSPropertyID::kWebkitTextOrientation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kSurrogate, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-writing-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitWritingMode final : public Longhand {
 public:
  constexpr WebkitWritingMode() : Longhand(CSSPropertyID::kWebkitWritingMode, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kSurrogate, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// writing-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WritingMode final : public Longhand {
 public:
  constexpr WritingMode() : Longhand(CSSPropertyID::kWritingMode, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// zoom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Zoom final : public Longhand {
 public:
  constexpr Zoom() : Longhand(CSSPropertyID::kZoom, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-forced-visited-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalForcedVisitedColor final : public Longhand {
 public:
  constexpr InternalForcedVisitedColor() : Longhand(CSSPropertyID::kInternalForcedVisitedColor, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-background-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBackgroundColor final : public Longhand {
 public:
  constexpr InternalVisitedBackgroundColor() : Longhand(CSSPropertyID::kInternalVisitedBackgroundColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kVisitedHighlightColors | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-border-block-end-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderBlockEndColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderBlockEndColor() : Longhand(CSSPropertyID::kInternalVisitedBorderBlockEndColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// -internal-visited-border-block-start-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderBlockStartColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderBlockStartColor() : Longhand(CSSPropertyID::kInternalVisitedBorderBlockStartColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// -internal-visited-border-bottom-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderBottomColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderBottomColor() : Longhand(CSSPropertyID::kInternalVisitedBorderBottomColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-border-inline-end-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderInlineEndColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderInlineEndColor() : Longhand(CSSPropertyID::kInternalVisitedBorderInlineEndColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// -internal-visited-border-inline-start-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderInlineStartColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderInlineStartColor() : Longhand(CSSPropertyID::kInternalVisitedBorderInlineStartColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// -internal-visited-border-left-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderLeftColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderLeftColor() : Longhand(CSSPropertyID::kInternalVisitedBorderLeftColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-border-right-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderRightColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderRightColor() : Longhand(CSSPropertyID::kInternalVisitedBorderRightColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-border-top-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedBorderTopColor final : public Longhand {
 public:
  constexpr InternalVisitedBorderTopColor() : Longhand(CSSPropertyID::kInternalVisitedBorderTopColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-caret-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedCaretColor final : public Longhand {
 public:
  constexpr InternalVisitedCaretColor() : Longhand(CSSPropertyID::kInternalVisitedCaretColor, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-column-rule-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedColumnRuleColor final : public Longhand {
 public:
  constexpr InternalVisitedColumnRuleColor() : Longhand(CSSPropertyID::kInternalVisitedColumnRuleColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-fill
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedFill final : public Longhand {
 public:
  constexpr InternalVisitedFill() : Longhand(CSSPropertyID::kInternalVisitedFill, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-outline-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedOutlineColor final : public Longhand {
 public:
  constexpr InternalVisitedOutlineColor() : Longhand(CSSPropertyID::kInternalVisitedOutlineColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-stroke
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedStroke final : public Longhand {
 public:
  constexpr InternalVisitedStroke() : Longhand(CSSPropertyID::kInternalVisitedStroke, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-text-decoration-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedTextDecorationColor final : public Longhand {
 public:
  constexpr InternalVisitedTextDecorationColor() : Longhand(CSSPropertyID::kInternalVisitedTextDecorationColor, kProperty | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-text-emphasis-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedTextEmphasisColor final : public Longhand {
 public:
  constexpr InternalVisitedTextEmphasisColor() : Longhand(CSSPropertyID::kInternalVisitedTextEmphasisColor, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-text-fill-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedTextFillColor final : public Longhand {
 public:
  constexpr InternalVisitedTextFillColor() : Longhand(CSSPropertyID::kInternalVisitedTextFillColor, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-visited-text-stroke-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalVisitedTextStrokeColor final : public Longhand {
 public:
  constexpr InternalVisitedTextStrokeColor() : Longhand(CSSPropertyID::kInternalVisitedTextStrokeColor, kProperty | kInherited | kVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// accent-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AccentColor final : public Longhand {
 public:
  constexpr AccentColor() : Longhand(CSSPropertyID::kAccentColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// additive-symbols
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AdditiveSymbols final : public Longhand {
 public:
  constexpr AdditiveSymbols() : Longhand(CSSPropertyID::kAdditiveSymbols, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// align-content
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AlignContent final : public Longhand {
 public:
  constexpr AlignContent() : Longhand(CSSPropertyID::kAlignContent, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// align-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AlignItems final : public Longhand {
 public:
  constexpr AlignItems() : Longhand(CSSPropertyID::kAlignItems, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// align-self
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AlignSelf final : public Longhand {
 public:
  constexpr AlignSelf() : Longhand(CSSPropertyID::kAlignSelf, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// alignment-baseline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AlignmentBaseline final : public Longhand {
 public:
  constexpr AlignmentBaseline() : Longhand(CSSPropertyID::kAlignmentBaseline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// all
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT All final : public Longhand {
 public:
  constexpr All() : Longhand(CSSPropertyID::kAll, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// anchor-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnchorName final : public Longhand {
 public:
  constexpr AnchorName() : Longhand(CSSPropertyID::kAnchorName, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// anchor-scope
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnchorScope final : public Longhand {
 public:
  constexpr AnchorScope() : Longhand(CSSPropertyID::kAnchorScope, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-composition
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationComposition final : public Longhand {
 public:
  constexpr AnimationComposition() : Longhand(CSSPropertyID::kAnimationComposition, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-delay
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationDelay final : public Longhand {
 public:
  constexpr AnimationDelay() : Longhand(CSSPropertyID::kAnimationDelay, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationDirection final : public Longhand {
 public:
  constexpr AnimationDirection() : Longhand(CSSPropertyID::kAnimationDirection, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-duration
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationDuration final : public Longhand {
 public:
  constexpr AnimationDuration() : Longhand(CSSPropertyID::kAnimationDuration, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-fill-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationFillMode final : public Longhand {
 public:
  constexpr AnimationFillMode() : Longhand(CSSPropertyID::kAnimationFillMode, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-iteration-count
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationIterationCount final : public Longhand {
 public:
  constexpr AnimationIterationCount() : Longhand(CSSPropertyID::kAnimationIterationCount, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationName final : public Longhand {
 public:
  constexpr AnimationName() : Longhand(CSSPropertyID::kAnimationName, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-play-state
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationPlayState final : public Longhand {
 public:
  constexpr AnimationPlayState() : Longhand(CSSPropertyID::kAnimationPlayState, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-range-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationRangeEnd final : public Longhand {
 public:
  constexpr AnimationRangeEnd() : Longhand(CSSPropertyID::kAnimationRangeEnd, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kPercentagesDoNotDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-range-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationRangeStart final : public Longhand {
 public:
  constexpr AnimationRangeStart() : Longhand(CSSPropertyID::kAnimationRangeStart, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kPercentagesDoNotDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-timeline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationTimeline final : public Longhand {
 public:
  constexpr AnimationTimeline() : Longhand(CSSPropertyID::kAnimationTimeline, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-timing-function
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationTimingFunction final : public Longhand {
 public:
  constexpr AnimationTimingFunction() : Longhand(CSSPropertyID::kAnimationTimingFunction, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// animation-trigger
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AnimationTrigger final : public Longhand {
 public:
  constexpr AnimationTrigger() : Longhand(CSSPropertyID::kAnimationTrigger, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// app-region
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AppRegion final : public Longhand {
 public:
  constexpr AppRegion() : Longhand(CSSPropertyID::kAppRegion, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// ascent-override
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AscentOverride final : public Longhand {
 public:
  constexpr AscentOverride() : Longhand(CSSPropertyID::kAscentOverride, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// aspect-ratio
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT AspectRatio final : public Longhand {
 public:
  constexpr AspectRatio() : Longhand(CSSPropertyID::kAspectRatio, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// backdrop-filter
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackdropFilter final : public Longhand {
 public:
  constexpr BackdropFilter() : Longhand(CSSPropertyID::kBackdropFilter, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// backface-visibility
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackfaceVisibility final : public Longhand {
 public:
  constexpr BackfaceVisibility() : Longhand(CSSPropertyID::kBackfaceVisibility, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-attachment
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundAttachment final : public Longhand {
 public:
  constexpr BackgroundAttachment() : Longhand(CSSPropertyID::kBackgroundAttachment, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-blend-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundBlendMode final : public Longhand {
 public:
  constexpr BackgroundBlendMode() : Longhand(CSSPropertyID::kBackgroundBlendMode, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPageContext, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-clip
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundClip final : public Longhand {
 public:
  constexpr BackgroundClip() : Longhand(CSSPropertyID::kBackgroundClip, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundColor final : public Longhand {
 public:
  constexpr BackgroundColor() : Longhand(CSSPropertyID::kBackgroundColor, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kBackground | kHighlightColors | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// background-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundImage final : public Longhand {
 public:
  constexpr BackgroundImage() : Longhand(CSSPropertyID::kBackgroundImage, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// background-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundOrigin final : public Longhand {
 public:
  constexpr BackgroundOrigin() : Longhand(CSSPropertyID::kBackgroundOrigin, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-position-x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundPositionX final : public Longhand {
 public:
  constexpr BackgroundPositionX() : Longhand(CSSPropertyID::kBackgroundPositionX, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-position-y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundPositionY final : public Longhand {
 public:
  constexpr BackgroundPositionY() : Longhand(CSSPropertyID::kBackgroundPositionY, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-repeat
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundRepeat final : public Longhand {
 public:
  constexpr BackgroundRepeat() : Longhand(CSSPropertyID::kBackgroundRepeat, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// background-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BackgroundSize final : public Longhand {
 public:
  constexpr BackgroundSize() : Longhand(CSSPropertyID::kBackgroundSize, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kBackground | kPercentagesDependOnUsedValue, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// base-palette
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BasePalette final : public Longhand {
 public:
  constexpr BasePalette() : Longhand(CSSPropertyID::kBasePalette, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// base-url
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BaseUrl final : public Longhand {
 public:
  constexpr BaseUrl() : Longhand(CSSPropertyID::kBaseUrl, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// baseline-shift
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BaselineShift final : public Longhand {
 public:
  constexpr BaselineShift() : Longhand(CSSPropertyID::kBaselineShift, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// baseline-source
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BaselineSource final : public Longhand {
 public:
  constexpr BaselineSource() : Longhand(CSSPropertyID::kBaselineSource, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// block-ellipsis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BlockEllipsis final : public Longhand {
 public:
  constexpr BlockEllipsis() : Longhand(CSSPropertyID::kBlockEllipsis, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// block-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BlockSize final : public Longhand {
 public:
  constexpr BlockSize() : Longhand(CSSPropertyID::kBlockSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-block-end-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockEndColor final : public Longhand {
 public:
  constexpr BorderBlockEndColor() : Longhand(CSSPropertyID::kBorderBlockEndColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-block-end-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockEndStyle final : public Longhand {
 public:
  constexpr BorderBlockEndStyle() : Longhand(CSSPropertyID::kBorderBlockEndStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// border-block-end-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockEndWidth final : public Longhand {
 public:
  constexpr BorderBlockEndWidth() : Longhand(CSSPropertyID::kBorderBlockEndWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-block-start-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockStartColor final : public Longhand {
 public:
  constexpr BorderBlockStartColor() : Longhand(CSSPropertyID::kBorderBlockStartColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-block-start-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockStartStyle final : public Longhand {
 public:
  constexpr BorderBlockStartStyle() : Longhand(CSSPropertyID::kBorderBlockStartStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// border-block-start-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBlockStartWidth final : public Longhand {
 public:
  constexpr BorderBlockStartWidth() : Longhand(CSSPropertyID::kBorderBlockStartWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-bottom-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBottomColor final : public Longhand {
 public:
  constexpr BorderBottomColor() : Longhand(CSSPropertyID::kBorderBottomColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// border-bottom-left-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBottomLeftRadius final : public Longhand {
 public:
  constexpr BorderBottomLeftRadius() : Longhand(CSSPropertyID::kBorderBottomLeftRadius, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kBorderRadius | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-bottom-right-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBottomRightRadius final : public Longhand {
 public:
  constexpr BorderBottomRightRadius() : Longhand(CSSPropertyID::kBorderBottomRightRadius, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kBorderRadius | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-bottom-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBottomStyle final : public Longhand {
 public:
  constexpr BorderBottomStyle() : Longhand(CSSPropertyID::kBorderBottomStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-bottom-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderBottomWidth final : public Longhand {
 public:
  constexpr BorderBottomWidth() : Longhand(CSSPropertyID::kBorderBottomWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-collapse
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderCollapse final : public Longhand {
 public:
  constexpr BorderCollapse() : Longhand(CSSPropertyID::kBorderCollapse, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-end-end-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderEndEndRadius final : public Longhand {
 public:
  constexpr BorderEndEndRadius() : Longhand(CSSPropertyID::kBorderEndEndRadius, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-end-start-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderEndStartRadius final : public Longhand {
 public:
  constexpr BorderEndStartRadius() : Longhand(CSSPropertyID::kBorderEndStartRadius, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-image-outset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderImageOutset final : public Longhand {
 public:
  constexpr BorderImageOutset() : Longhand(CSSPropertyID::kBorderImageOutset, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kBorder, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-image-repeat
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderImageRepeat final : public Longhand {
 public:
  constexpr BorderImageRepeat() : Longhand(CSSPropertyID::kBorderImageRepeat, kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kBorder, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-image-slice
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderImageSlice final : public Longhand {
 public:
  constexpr BorderImageSlice() : Longhand(CSSPropertyID::kBorderImageSlice, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kBorder | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-image-source
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderImageSource final : public Longhand {
 public:
  constexpr BorderImageSource() : Longhand(CSSPropertyID::kBorderImageSource, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kBorder, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// border-image-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderImageWidth final : public Longhand {
 public:
  constexpr BorderImageWidth() : Longhand(CSSPropertyID::kBorderImageWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kBorder | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-inline-end-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineEndColor final : public Longhand {
 public:
  constexpr BorderInlineEndColor() : Longhand(CSSPropertyID::kBorderInlineEndColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-inline-end-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineEndStyle final : public Longhand {
 public:
  constexpr BorderInlineEndStyle() : Longhand(CSSPropertyID::kBorderInlineEndStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// border-inline-end-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineEndWidth final : public Longhand {
 public:
  constexpr BorderInlineEndWidth() : Longhand(CSSPropertyID::kBorderInlineEndWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-inline-start-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineStartColor final : public Longhand {
 public:
  constexpr BorderInlineStartColor() : Longhand(CSSPropertyID::kBorderInlineStartColor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-inline-start-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineStartStyle final : public Longhand {
 public:
  constexpr BorderInlineStartStyle() : Longhand(CSSPropertyID::kBorderInlineStartStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// border-inline-start-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderInlineStartWidth final : public Longhand {
 public:
  constexpr BorderInlineStartWidth() : Longhand(CSSPropertyID::kBorderInlineStartWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-left-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderLeftColor final : public Longhand {
 public:
  constexpr BorderLeftColor() : Longhand(CSSPropertyID::kBorderLeftColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// border-left-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderLeftStyle final : public Longhand {
 public:
  constexpr BorderLeftStyle() : Longhand(CSSPropertyID::kBorderLeftStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-left-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderLeftWidth final : public Longhand {
 public:
  constexpr BorderLeftWidth() : Longhand(CSSPropertyID::kBorderLeftWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-right-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderRightColor final : public Longhand {
 public:
  constexpr BorderRightColor() : Longhand(CSSPropertyID::kBorderRightColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// border-right-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderRightStyle final : public Longhand {
 public:
  constexpr BorderRightStyle() : Longhand(CSSPropertyID::kBorderRightStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-right-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderRightWidth final : public Longhand {
 public:
  constexpr BorderRightWidth() : Longhand(CSSPropertyID::kBorderRightWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderShape final : public Longhand {
 public:
  constexpr BorderShape() : Longhand(CSSPropertyID::kBorderShape, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-start-end-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderStartEndRadius final : public Longhand {
 public:
  constexpr BorderStartEndRadius() : Longhand(CSSPropertyID::kBorderStartEndRadius, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-start-start-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderStartStartRadius final : public Longhand {
 public:
  constexpr BorderStartStartRadius() : Longhand(CSSPropertyID::kBorderStartStartRadius, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// border-top-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderTopColor final : public Longhand {
 public:
  constexpr BorderTopColor() : Longhand(CSSPropertyID::kBorderTopColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// border-top-left-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderTopLeftRadius final : public Longhand {
 public:
  constexpr BorderTopLeftRadius() : Longhand(CSSPropertyID::kBorderTopLeftRadius, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kBorderRadius | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-top-right-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderTopRightRadius final : public Longhand {
 public:
  constexpr BorderTopRightRadius() : Longhand(CSSPropertyID::kBorderTopRightRadius, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kBorderRadius | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-top-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderTopStyle final : public Longhand {
 public:
  constexpr BorderTopStyle() : Longhand(CSSPropertyID::kBorderTopStyle, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// border-top-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BorderTopWidth final : public Longhand {
 public:
  constexpr BorderTopWidth() : Longhand(CSSPropertyID::kBorderTopWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kBorder | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// bottom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Bottom final : public Longhand {
 public:
  constexpr Bottom() : Longhand(CSSPropertyID::kBottom, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// box-decoration-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BoxDecorationBreak final : public Longhand {
 public:
  constexpr BoxDecorationBreak() : Longhand(CSSPropertyID::kBoxDecorationBreak, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// box-shadow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BoxShadow final : public Longhand {
 public:
  constexpr BoxShadow() : Longhand(CSSPropertyID::kBoxShadow, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// box-sizing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BoxSizing final : public Longhand {
 public:
  constexpr BoxSizing() : Longhand(CSSPropertyID::kBoxSizing, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// break-after
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BreakAfter final : public Longhand {
 public:
  constexpr BreakAfter() : Longhand(CSSPropertyID::kBreakAfter, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// break-before
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BreakBefore final : public Longhand {
 public:
  constexpr BreakBefore() : Longhand(CSSPropertyID::kBreakBefore, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// break-inside
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BreakInside final : public Longhand {
 public:
  constexpr BreakInside() : Longhand(CSSPropertyID::kBreakInside, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// buffered-rendering
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT BufferedRendering final : public Longhand {
 public:
  constexpr BufferedRendering() : Longhand(CSSPropertyID::kBufferedRendering, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// caption-side
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CaptionSide final : public Longhand {
 public:
  constexpr CaptionSide() : Longhand(CSSPropertyID::kCaptionSide, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// caret-animation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CaretAnimation final : public Longhand {
 public:
  constexpr CaretAnimation() : Longhand(CSSPropertyID::kCaretAnimation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// caret-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CaretColor final : public Longhand {
 public:
  constexpr CaretColor() : Longhand(CSSPropertyID::kCaretColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForVisited, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// caret-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CaretShape final : public Longhand {
 public:
  constexpr CaretShape() : Longhand(CSSPropertyID::kCaretShape, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// clear
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Clear final : public Longhand {
 public:
  constexpr Clear() : Longhand(CSSPropertyID::kClear, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// clip
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Clip final : public Longhand {
 public:
  constexpr Clip() : Longhand(CSSPropertyID::kClip, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// clip-path
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ClipPath final : public Longhand {
 public:
  constexpr ClipPath() : Longhand(CSSPropertyID::kClipPath, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// clip-rule
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ClipRule final : public Longhand {
 public:
  constexpr ClipRule() : Longhand(CSSPropertyID::kClipRule, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// color-interpolation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColorInterpolation final : public Longhand {
 public:
  constexpr ColorInterpolation() : Longhand(CSSPropertyID::kColorInterpolation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// color-interpolation-filters
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColorInterpolationFilters final : public Longhand {
 public:
  constexpr ColorInterpolationFilters() : Longhand(CSSPropertyID::kColorInterpolationFilters, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// color-rendering
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColorRendering final : public Longhand {
 public:
  constexpr ColorRendering() : Longhand(CSSPropertyID::kColorRendering, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-count
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnCount final : public Longhand {
 public:
  constexpr ColumnCount() : Longhand(CSSPropertyID::kColumnCount, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-fill
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnFill final : public Longhand {
 public:
  constexpr ColumnFill() : Longhand(CSSPropertyID::kColumnFill, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnGap final : public Longhand {
 public:
  constexpr ColumnGap() : Longhand(CSSPropertyID::kColumnGap, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnHeight final : public Longhand {
 public:
  constexpr ColumnHeight() : Longhand(CSSPropertyID::kColumnHeight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleBreak final : public Longhand {
 public:
  constexpr ColumnRuleBreak() : Longhand(CSSPropertyID::kColumnRuleBreak, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleColor final : public Longhand {
 public:
  constexpr ColumnRuleColor() : Longhand(CSSPropertyID::kColumnRuleColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForVisited, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// column-rule-inset-cap-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetCapEnd final : public Longhand {
 public:
  constexpr ColumnRuleInsetCapEnd() : Longhand(CSSPropertyID::kColumnRuleInsetCapEnd, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-inset-cap-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetCapStart final : public Longhand {
 public:
  constexpr ColumnRuleInsetCapStart() : Longhand(CSSPropertyID::kColumnRuleInsetCapStart, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-inset-junction-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetJunctionEnd final : public Longhand {
 public:
  constexpr ColumnRuleInsetJunctionEnd() : Longhand(CSSPropertyID::kColumnRuleInsetJunctionEnd, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-inset-junction-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleInsetJunctionStart final : public Longhand {
 public:
  constexpr ColumnRuleInsetJunctionStart() : Longhand(CSSPropertyID::kColumnRuleInsetJunctionStart, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleStyle final : public Longhand {
 public:
  constexpr ColumnRuleStyle() : Longhand(CSSPropertyID::kColumnRuleStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-visibility-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleVisibilityItems final : public Longhand {
 public:
  constexpr ColumnRuleVisibilityItems() : Longhand(CSSPropertyID::kColumnRuleVisibilityItems, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-rule-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnRuleWidth final : public Longhand {
 public:
  constexpr ColumnRuleWidth() : Longhand(CSSPropertyID::kColumnRuleWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-span
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnSpan final : public Longhand {
 public:
  constexpr ColumnSpan() : Longhand(CSSPropertyID::kColumnSpan, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnWidth final : public Longhand {
 public:
  constexpr ColumnWidth() : Longhand(CSSPropertyID::kColumnWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// column-wrap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ColumnWrap final : public Longhand {
 public:
  constexpr ColumnWrap() : Longhand(CSSPropertyID::kColumnWrap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// contain
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Contain final : public Longhand {
 public:
  constexpr Contain() : Longhand(CSSPropertyID::kContain, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// contain-intrinsic-block-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainIntrinsicBlockSize final : public Longhand {
 public:
  constexpr ContainIntrinsicBlockSize() : Longhand(CSSPropertyID::kContainIntrinsicBlockSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// contain-intrinsic-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainIntrinsicHeight final : public Longhand {
 public:
  constexpr ContainIntrinsicHeight() : Longhand(CSSPropertyID::kContainIntrinsicHeight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// contain-intrinsic-inline-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainIntrinsicInlineSize final : public Longhand {
 public:
  constexpr ContainIntrinsicInlineSize() : Longhand(CSSPropertyID::kContainIntrinsicInlineSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// contain-intrinsic-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainIntrinsicWidth final : public Longhand {
 public:
  constexpr ContainIntrinsicWidth() : Longhand(CSSPropertyID::kContainIntrinsicWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// container-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainerName final : public Longhand {
 public:
  constexpr ContainerName() : Longhand(CSSPropertyID::kContainerName, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// container-type
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContainerType final : public Longhand {
 public:
  constexpr ContainerType() : Longhand(CSSPropertyID::kContainerType, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// content
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Content final : public Longhand {
 public:
  constexpr Content() : Longhand(CSSPropertyID::kContent, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kValidForPageContext, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// content-visibility
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ContentVisibility final : public Longhand {
 public:
  constexpr ContentVisibility() : Longhand(CSSPropertyID::kContentVisibility, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// continue
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Continue final : public Longhand {
 public:
  constexpr Continue() : Longhand(CSSPropertyID::kContinue, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// corner-bottom-left-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerBottomLeftShape final : public Longhand {
 public:
  constexpr CornerBottomLeftShape() : Longhand(CSSPropertyID::kCornerBottomLeftShape, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// corner-bottom-right-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerBottomRightShape final : public Longhand {
 public:
  constexpr CornerBottomRightShape() : Longhand(CSSPropertyID::kCornerBottomRightShape, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// corner-end-end-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerEndEndShape final : public Longhand {
 public:
  constexpr CornerEndEndShape() : Longhand(CSSPropertyID::kCornerEndEndShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// corner-end-start-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerEndStartShape final : public Longhand {
 public:
  constexpr CornerEndStartShape() : Longhand(CSSPropertyID::kCornerEndStartShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// corner-start-end-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerStartEndShape final : public Longhand {
 public:
  constexpr CornerStartEndShape() : Longhand(CSSPropertyID::kCornerStartEndShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// corner-start-start-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerStartStartShape final : public Longhand {
 public:
  constexpr CornerStartStartShape() : Longhand(CSSPropertyID::kCornerStartStartShape, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// corner-top-left-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerTopLeftShape final : public Longhand {
 public:
  constexpr CornerTopLeftShape() : Longhand(CSSPropertyID::kCornerTopLeftShape, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// corner-top-right-shape
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CornerTopRightShape final : public Longhand {
 public:
  constexpr CornerTopRightShape() : Longhand(CSSPropertyID::kCornerTopRightShape, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// counter-increment
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CounterIncrement final : public Longhand {
 public:
  constexpr CounterIncrement() : Longhand(CSSPropertyID::kCounterIncrement, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// counter-reset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CounterReset final : public Longhand {
 public:
  constexpr CounterReset() : Longhand(CSSPropertyID::kCounterReset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// counter-set
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT CounterSet final : public Longhand {
 public:
  constexpr CounterSet() : Longhand(CSSPropertyID::kCounterSet, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// cursor
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Cursor final : public Longhand {
 public:
  constexpr Cursor() : Longhand(CSSPropertyID::kCursor, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// cx
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Cx final : public Longhand {
 public:
  constexpr Cx() : Longhand(CSSPropertyID::kCx, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// cy
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Cy final : public Longhand {
 public:
  constexpr Cy() : Longhand(CSSPropertyID::kCy, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// d
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT D final : public Longhand {
 public:
  constexpr D() : Longhand(CSSPropertyID::kD, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// descent-override
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT DescentOverride final : public Longhand {
 public:
  constexpr DescentOverride() : Longhand(CSSPropertyID::kDescentOverride, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// display
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Display final : public Longhand {
 public:
  constexpr Display() : Longhand(CSSPropertyID::kDisplay, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kValidForPermissionIcon, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// dominant-baseline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT DominantBaseline final : public Longhand {
 public:
  constexpr DominantBaseline() : Longhand(CSSPropertyID::kDominantBaseline, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// dynamic-range-limit
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT DynamicRangeLimit final : public Longhand {
 public:
  constexpr DynamicRangeLimit() : Longhand(CSSPropertyID::kDynamicRangeLimit, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// empty-cells
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EmptyCells final : public Longhand {
 public:
  constexpr EmptyCells() : Longhand(CSSPropertyID::kEmptyCells, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// fallback
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Fallback final : public Longhand {
 public:
  constexpr Fallback() : Longhand(CSSPropertyID::kFallback, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// field-sizing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FieldSizing final : public Longhand {
 public:
  constexpr FieldSizing() : Longhand(CSSPropertyID::kFieldSizing, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// fill
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Fill final : public Longhand {
 public:
  constexpr Fill() : Longhand(CSSPropertyID::kFill, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionIcon | kValidForVisited | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// fill-opacity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FillOpacity final : public Longhand {
 public:
  constexpr FillOpacity() : Longhand(CSSPropertyID::kFillOpacity, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// fill-rule
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FillRule final : public Longhand {
 public:
  constexpr FillRule() : Longhand(CSSPropertyID::kFillRule, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// filter
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Filter final : public Longhand {
 public:
  constexpr Filter() : Longhand(CSSPropertyID::kFilter, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// flex-basis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexBasis final : public Longhand {
 public:
  constexpr FlexBasis() : Longhand(CSSPropertyID::kFlexBasis, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flex-direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexDirection final : public Longhand {
 public:
  constexpr FlexDirection() : Longhand(CSSPropertyID::kFlexDirection, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flex-grow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexGrow final : public Longhand {
 public:
  constexpr FlexGrow() : Longhand(CSSPropertyID::kFlexGrow, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flex-line-count
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexLineCount final : public Longhand {
 public:
  constexpr FlexLineCount() : Longhand(CSSPropertyID::kFlexLineCount, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flex-shrink
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexShrink final : public Longhand {
 public:
  constexpr FlexShrink() : Longhand(CSSPropertyID::kFlexShrink, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flex-wrap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlexWrap final : public Longhand {
 public:
  constexpr FlexWrap() : Longhand(CSSPropertyID::kFlexWrap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// float
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Float final : public Longhand {
 public:
  constexpr Float() : Longhand(CSSPropertyID::kFloat, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flood-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FloodColor final : public Longhand {
 public:
  constexpr FloodColor() : Longhand(CSSPropertyID::kFloodColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// flood-opacity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FloodOpacity final : public Longhand {
 public:
  constexpr FloodOpacity() : Longhand(CSSPropertyID::kFloodOpacity, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// flow-tolerance
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FlowTolerance final : public Longhand {
 public:
  constexpr FlowTolerance() : Longhand(CSSPropertyID::kFlowTolerance, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// font-display
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FontDisplay final : public Longhand {
 public:
  constexpr FontDisplay() : Longhand(CSSPropertyID::kFontDisplay, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// frame-sizing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT FrameSizing final : public Longhand {
 public:
  constexpr FrameSizing() : Longhand(CSSPropertyID::kFrameSizing, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-auto-columns
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridAutoColumns final : public Longhand {
 public:
  constexpr GridAutoColumns() : Longhand(CSSPropertyID::kGridAutoColumns, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-auto-flow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridAutoFlow final : public Longhand {
 public:
  constexpr GridAutoFlow() : Longhand(CSSPropertyID::kGridAutoFlow, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-auto-rows
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridAutoRows final : public Longhand {
 public:
  constexpr GridAutoRows() : Longhand(CSSPropertyID::kGridAutoRows, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-column-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridColumnEnd final : public Longhand {
 public:
  constexpr GridColumnEnd() : Longhand(CSSPropertyID::kGridColumnEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-column-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridColumnStart final : public Longhand {
 public:
  constexpr GridColumnStart() : Longhand(CSSPropertyID::kGridColumnStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-lanes-direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridLanesDirection final : public Longhand {
 public:
  constexpr GridLanesDirection() : Longhand(CSSPropertyID::kGridLanesDirection, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-lanes-pack
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridLanesPack final : public Longhand {
 public:
  constexpr GridLanesPack() : Longhand(CSSPropertyID::kGridLanesPack, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-row-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridRowEnd final : public Longhand {
 public:
  constexpr GridRowEnd() : Longhand(CSSPropertyID::kGridRowEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-row-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridRowStart final : public Longhand {
 public:
  constexpr GridRowStart() : Longhand(CSSPropertyID::kGridRowStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-template-areas
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridTemplateAreas final : public Longhand {
 public:
  constexpr GridTemplateAreas() : Longhand(CSSPropertyID::kGridTemplateAreas, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-template-columns
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridTemplateColumns final : public Longhand {
 public:
  constexpr GridTemplateColumns() : Longhand(CSSPropertyID::kGridTemplateColumns, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// grid-template-rows
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridTemplateRows final : public Longhand {
 public:
  constexpr GridTemplateRows() : Longhand(CSSPropertyID::kGridTemplateRows, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// hanging-punctuation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT HangingPunctuation final : public Longhand {
 public:
  constexpr HangingPunctuation() : Longhand(CSSPropertyID::kHangingPunctuation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// hash
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Hash final : public Longhand {
 public:
  constexpr Hash() : Longhand(CSSPropertyID::kHash, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Height final : public Longhand {
 public:
  constexpr Height() : Longhand(CSSPropertyID::kHeight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// hostname
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Hostname final : public Longhand {
 public:
  constexpr Hostname() : Longhand(CSSPropertyID::kHostname, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// hyphenate-character
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT HyphenateCharacter final : public Longhand {
 public:
  constexpr HyphenateCharacter() : Longhand(CSSPropertyID::kHyphenateCharacter, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// hyphenate-limit-chars
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT HyphenateLimitChars final : public Longhand {
 public:
  constexpr HyphenateLimitChars() : Longhand(CSSPropertyID::kHyphenateLimitChars, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// hyphens
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Hyphens final : public Longhand {
 public:
  constexpr Hyphens() : Longhand(CSSPropertyID::kHyphens, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// image-animation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ImageAnimation final : public Longhand {
 public:
  constexpr ImageAnimation() : Longhand(CSSPropertyID::kImageAnimation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// image-orientation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ImageOrientation final : public Longhand {
 public:
  constexpr ImageOrientation() : Longhand(CSSPropertyID::kImageOrientation, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// image-rendering
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ImageRendering final : public Longhand {
 public:
  constexpr ImageRendering() : Longhand(CSSPropertyID::kImageRendering, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// inherits
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Inherits final : public Longhand {
 public:
  constexpr Inherits() : Longhand(CSSPropertyID::kInherits, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// initial-letter
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InitialLetter final : public Longhand {
 public:
  constexpr InitialLetter() : Longhand(CSSPropertyID::kInitialLetter, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// initial-value
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InitialValue final : public Longhand {
 public:
  constexpr InitialValue() : Longhand(CSSPropertyID::kInitialValue, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// inline-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InlineSize final : public Longhand {
 public:
  constexpr InlineSize() : Longhand(CSSPropertyID::kInlineSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// inset-block-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InsetBlockEnd final : public Longhand {
 public:
  constexpr InsetBlockEnd() : Longhand(CSSPropertyID::kInsetBlockEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// inset-block-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InsetBlockStart final : public Longhand {
 public:
  constexpr InsetBlockStart() : Longhand(CSSPropertyID::kInsetBlockStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// inset-inline-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InsetInlineEnd final : public Longhand {
 public:
  constexpr InsetInlineEnd() : Longhand(CSSPropertyID::kInsetInlineEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// inset-inline-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InsetInlineStart final : public Longhand {
 public:
  constexpr InsetInlineStart() : Longhand(CSSPropertyID::kInsetInlineStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// interactivity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Interactivity final : public Longhand {
 public:
  constexpr Interactivity() : Longhand(CSSPropertyID::kInteractivity, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// interest-delay-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InterestDelayEnd final : public Longhand {
 public:
  constexpr InterestDelayEnd() : Longhand(CSSPropertyID::kInterestDelayEnd, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// interest-delay-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InterestDelayStart final : public Longhand {
 public:
  constexpr InterestDelayStart() : Longhand(CSSPropertyID::kInterestDelayStart, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-align-content-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalAlignContentBlock final : public Longhand {
 public:
  constexpr InternalAlignContentBlock() : Longhand(CSSPropertyID::kInternalAlignContentBlock, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-empty-line-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalEmptyLineHeight final : public Longhand {
 public:
  constexpr InternalEmptyLineHeight() : Longhand(CSSPropertyID::kInternalEmptyLineHeight, kProperty | kInherited | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-font-size-delta
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalFontSizeDelta final : public Longhand {
 public:
  constexpr InternalFontSizeDelta() : Longhand(CSSPropertyID::kInternalFontSizeDelta, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-forced-background-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalForcedBackgroundColor final : public Longhand {
 public:
  constexpr InternalForcedBackgroundColor() : Longhand(CSSPropertyID::kInternalForcedBackgroundColor, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-forced-border-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalForcedBorderColor final : public Longhand {
 public:
  constexpr InternalForcedBorderColor() : Longhand(CSSPropertyID::kInternalForcedBorderColor, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-forced-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalForcedColor final : public Longhand {
 public:
  constexpr InternalForcedColor() : Longhand(CSSPropertyID::kInternalForcedColor, kProperty | kInherited | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForVisited, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-forced-outline-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalForcedOutlineColor final : public Longhand {
 public:
  constexpr InternalForcedOutlineColor() : Longhand(CSSPropertyID::kInternalForcedOutlineColor, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-overscroll-area
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalOverscrollArea final : public Longhand {
 public:
  constexpr InternalOverscrollArea() : Longhand(CSSPropertyID::kInternalOverscrollArea, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -internal-overscroll-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InternalOverscrollPosition final : public Longhand {
 public:
  constexpr InternalOverscrollPosition() : Longhand(CSSPropertyID::kInternalOverscrollPosition, kProperty | kNotVisited | kInternal | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// interpolate-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT InterpolateSize final : public Longhand {
 public:
  constexpr InterpolateSize() : Longhand(CSSPropertyID::kInterpolateSize, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// isolation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Isolation final : public Longhand {
 public:
  constexpr Isolation() : Longhand(CSSPropertyID::kIsolation, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// justify-content
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT JustifyContent final : public Longhand {
 public:
  constexpr JustifyContent() : Longhand(CSSPropertyID::kJustifyContent, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// justify-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT JustifyItems final : public Longhand {
 public:
  constexpr JustifyItems() : Longhand(CSSPropertyID::kJustifyItems, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// justify-self
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT JustifySelf final : public Longhand {
 public:
  constexpr JustifySelf() : Longhand(CSSPropertyID::kJustifySelf, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// left
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Left final : public Longhand {
 public:
  constexpr Left() : Longhand(CSSPropertyID::kLeft, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// letter-spacing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT LetterSpacing final : public Longhand {
 public:
  constexpr LetterSpacing() : Longhand(CSSPropertyID::kLetterSpacing, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// lighting-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT LightingColor final : public Longhand {
 public:
  constexpr LightingColor() : Longhand(CSSPropertyID::kLightingColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// line-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT LineBreak final : public Longhand {
 public:
  constexpr LineBreak() : Longhand(CSSPropertyID::kLineBreak, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// line-gap-override
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT LineGapOverride final : public Longhand {
 public:
  constexpr LineGapOverride() : Longhand(CSSPropertyID::kLineGapOverride, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// line-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT LineHeight final : public Longhand {
 public:
  constexpr LineHeight() : Longhand(CSSPropertyID::kLineHeight, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// list-style-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ListStyleImage final : public Longhand {
 public:
  constexpr ListStyleImage() : Longhand(CSSPropertyID::kListStyleImage, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// list-style-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ListStylePosition final : public Longhand {
 public:
  constexpr ListStylePosition() : Longhand(CSSPropertyID::kListStylePosition, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// list-style-type
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ListStyleType final : public Longhand {
 public:
  constexpr ListStyleType() : Longhand(CSSPropertyID::kListStyleType, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// margin-block-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginBlockEnd final : public Longhand {
 public:
  constexpr MarginBlockEnd() : Longhand(CSSPropertyID::kMarginBlockEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// margin-block-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginBlockStart final : public Longhand {
 public:
  constexpr MarginBlockStart() : Longhand(CSSPropertyID::kMarginBlockStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// margin-bottom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginBottom final : public Longhand {
 public:
  constexpr MarginBottom() : Longhand(CSSPropertyID::kMarginBottom, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// margin-inline-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginInlineEnd final : public Longhand {
 public:
  constexpr MarginInlineEnd() : Longhand(CSSPropertyID::kMarginInlineEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// margin-inline-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginInlineStart final : public Longhand {
 public:
  constexpr MarginInlineStart() : Longhand(CSSPropertyID::kMarginInlineStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// margin-left
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginLeft final : public Longhand {
 public:
  constexpr MarginLeft() : Longhand(CSSPropertyID::kMarginLeft, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// margin-right
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginRight final : public Longhand {
 public:
  constexpr MarginRight() : Longhand(CSSPropertyID::kMarginRight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// margin-top
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginTop final : public Longhand {
 public:
  constexpr MarginTop() : Longhand(CSSPropertyID::kMarginTop, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// margin-trim
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarginTrim final : public Longhand {
 public:
  constexpr MarginTrim() : Longhand(CSSPropertyID::kMarginTrim, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// marker-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarkerEnd final : public Longhand {
 public:
  constexpr MarkerEnd() : Longhand(CSSPropertyID::kMarkerEnd, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// marker-mid
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarkerMid final : public Longhand {
 public:
  constexpr MarkerMid() : Longhand(CSSPropertyID::kMarkerMid, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// marker-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MarkerStart final : public Longhand {
 public:
  constexpr MarkerStart() : Longhand(CSSPropertyID::kMarkerStart, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-clip
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskClip final : public Longhand {
 public:
  constexpr MaskClip() : Longhand(CSSPropertyID::kMaskClip, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskImage final : public Longhand {
 public:
  constexpr MaskImage() : Longhand(CSSPropertyID::kMaskImage, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// mask-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskMode final : public Longhand {
 public:
  constexpr MaskMode() : Longhand(CSSPropertyID::kMaskMode, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskOrigin final : public Longhand {
 public:
  constexpr MaskOrigin() : Longhand(CSSPropertyID::kMaskOrigin, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-repeat
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskRepeat final : public Longhand {
 public:
  constexpr MaskRepeat() : Longhand(CSSPropertyID::kMaskRepeat, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskSize final : public Longhand {
 public:
  constexpr MaskSize() : Longhand(CSSPropertyID::kMaskSize, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-type
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskType final : public Longhand {
 public:
  constexpr MaskType() : Longhand(CSSPropertyID::kMaskType, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// math-shift
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MathShift final : public Longhand {
 public:
  constexpr MathShift() : Longhand(CSSPropertyID::kMathShift, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// math-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MathStyle final : public Longhand {
 public:
  constexpr MathStyle() : Longhand(CSSPropertyID::kMathStyle, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// max-block-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaxBlockSize final : public Longhand {
 public:
  constexpr MaxBlockSize() : Longhand(CSSPropertyID::kMaxBlockSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// max-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaxHeight final : public Longhand {
 public:
  constexpr MaxHeight() : Longhand(CSSPropertyID::kMaxHeight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// max-inline-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaxInlineSize final : public Longhand {
 public:
  constexpr MaxInlineSize() : Longhand(CSSPropertyID::kMaxInlineSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// max-lines
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaxLines final : public Longhand {
 public:
  constexpr MaxLines() : Longhand(CSSPropertyID::kMaxLines, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// max-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaxWidth final : public Longhand {
 public:
  constexpr MaxWidth() : Longhand(CSSPropertyID::kMaxWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// min-block-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MinBlockSize final : public Longhand {
 public:
  constexpr MinBlockSize() : Longhand(CSSPropertyID::kMinBlockSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// min-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MinHeight final : public Longhand {
 public:
  constexpr MinHeight() : Longhand(CSSPropertyID::kMinHeight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// min-inline-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MinInlineSize final : public Longhand {
 public:
  constexpr MinInlineSize() : Longhand(CSSPropertyID::kMinInlineSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// min-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MinWidth final : public Longhand {
 public:
  constexpr MinWidth() : Longhand(CSSPropertyID::kMinWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mix-blend-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MixBlendMode final : public Longhand {
 public:
  constexpr MixBlendMode() : Longhand(CSSPropertyID::kMixBlendMode, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// navigation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Navigation final : public Longhand {
 public:
  constexpr Navigation() : Longhand(CSSPropertyID::kNavigation, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// negative
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Negative final : public Longhand {
 public:
  constexpr Negative() : Longhand(CSSPropertyID::kNegative, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// object-fit
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ObjectFit final : public Longhand {
 public:
  constexpr ObjectFit() : Longhand(CSSPropertyID::kObjectFit, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// object-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ObjectPosition final : public Longhand {
 public:
  constexpr ObjectPosition() : Longhand(CSSPropertyID::kObjectPosition, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// object-view-box
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ObjectViewBox final : public Longhand {
 public:
  constexpr ObjectViewBox() : Longhand(CSSPropertyID::kObjectViewBox, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// offset-anchor
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OffsetAnchor final : public Longhand {
 public:
  constexpr OffsetAnchor() : Longhand(CSSPropertyID::kOffsetAnchor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// offset-distance
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OffsetDistance final : public Longhand {
 public:
  constexpr OffsetDistance() : Longhand(CSSPropertyID::kOffsetDistance, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// offset-path
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OffsetPath final : public Longhand {
 public:
  constexpr OffsetPath() : Longhand(CSSPropertyID::kOffsetPath, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// offset-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OffsetPosition final : public Longhand {
 public:
  constexpr OffsetPosition() : Longhand(CSSPropertyID::kOffsetPosition, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// offset-rotate
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OffsetRotate final : public Longhand {
 public:
  constexpr OffsetRotate() : Longhand(CSSPropertyID::kOffsetRotate, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// opacity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Opacity final : public Longhand {
 public:
  constexpr Opacity() : Longhand(CSSPropertyID::kOpacity, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// order
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Order final : public Longhand {
 public:
  constexpr Order() : Longhand(CSSPropertyID::kOrder, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// origin-trial-test-property
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OriginTrialTestProperty final : public Longhand {
 public:
  constexpr OriginTrialTestProperty() : Longhand(CSSPropertyID::kOriginTrialTestProperty, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// orphans
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Orphans final : public Longhand {
 public:
  constexpr Orphans() : Longhand(CSSPropertyID::kOrphans, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// outline-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OutlineColor final : public Longhand {
 public:
  constexpr OutlineColor() : Longhand(CSSPropertyID::kOutlineColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kValidForVisited, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// outline-offset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OutlineOffset final : public Longhand {
 public:
  constexpr OutlineOffset() : Longhand(CSSPropertyID::kOutlineOffset, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// outline-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OutlineStyle final : public Longhand {
 public:
  constexpr OutlineStyle() : Longhand(CSSPropertyID::kOutlineStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// outline-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OutlineWidth final : public Longhand {
 public:
  constexpr OutlineWidth() : Longhand(CSSPropertyID::kOutlineWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overflow-anchor
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowAnchor final : public Longhand {
 public:
  constexpr OverflowAnchor() : Longhand(CSSPropertyID::kOverflowAnchor, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overflow-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowBlock final : public Longhand {
 public:
  constexpr OverflowBlock() : Longhand(CSSPropertyID::kOverflowBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// overflow-clip-margin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowClipMargin final : public Longhand {
 public:
  constexpr OverflowClipMargin() : Longhand(CSSPropertyID::kOverflowClipMargin, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overflow-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowInline final : public Longhand {
 public:
  constexpr OverflowInline() : Longhand(CSSPropertyID::kOverflowInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// overflow-wrap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowWrap final : public Longhand {
 public:
  constexpr OverflowWrap() : Longhand(CSSPropertyID::kOverflowWrap, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overflow-x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowX final : public Longhand {
 public:
  constexpr OverflowX() : Longhand(CSSPropertyID::kOverflowX, kProperty | kNotVisited | kNotAnimation | kNotLegacyOverlapping | kValidForKeyframe | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overflow-y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverflowY final : public Longhand {
 public:
  constexpr OverflowY() : Longhand(CSSPropertyID::kOverflowY, kProperty | kNotVisited | kNotAnimation | kNotLegacyOverlapping | kValidForKeyframe | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overlay
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Overlay final : public Longhand {
 public:
  constexpr Overlay() : Longhand(CSSPropertyID::kOverlay, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// override-colors
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverrideColors final : public Longhand {
 public:
  constexpr OverrideColors() : Longhand(CSSPropertyID::kOverrideColors, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// overscroll-behavior-block
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverscrollBehaviorBlock final : public Longhand {
 public:
  constexpr OverscrollBehaviorBlock() : Longhand(CSSPropertyID::kOverscrollBehaviorBlock, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// overscroll-behavior-inline
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverscrollBehaviorInline final : public Longhand {
 public:
  constexpr OverscrollBehaviorInline() : Longhand(CSSPropertyID::kOverscrollBehaviorInline, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
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

// overscroll-behavior-x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverscrollBehaviorX final : public Longhand {
 public:
  constexpr OverscrollBehaviorX() : Longhand(CSSPropertyID::kOverscrollBehaviorX, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// overscroll-behavior-y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT OverscrollBehaviorY final : public Longhand {
 public:
  constexpr OverscrollBehaviorY() : Longhand(CSSPropertyID::kOverscrollBehaviorY, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// pad
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Pad final : public Longhand {
 public:
  constexpr Pad() : Longhand(CSSPropertyID::kPad, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// padding-block-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingBlockEnd final : public Longhand {
 public:
  constexpr PaddingBlockEnd() : Longhand(CSSPropertyID::kPaddingBlockEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// padding-block-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingBlockStart final : public Longhand {
 public:
  constexpr PaddingBlockStart() : Longhand(CSSPropertyID::kPaddingBlockStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// padding-bottom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingBottom final : public Longhand {
 public:
  constexpr PaddingBottom() : Longhand(CSSPropertyID::kPaddingBottom, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// padding-inline-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingInlineEnd final : public Longhand {
 public:
  constexpr PaddingInlineEnd() : Longhand(CSSPropertyID::kPaddingInlineEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// padding-inline-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingInlineStart final : public Longhand {
 public:
  constexpr PaddingInlineStart() : Longhand(CSSPropertyID::kPaddingInlineStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// padding-left
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingLeft final : public Longhand {
 public:
  constexpr PaddingLeft() : Longhand(CSSPropertyID::kPaddingLeft, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// padding-right
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingRight final : public Longhand {
 public:
  constexpr PaddingRight() : Longhand(CSSPropertyID::kPaddingRight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// padding-top
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaddingTop final : public Longhand {
 public:
  constexpr PaddingTop() : Longhand(CSSPropertyID::kPaddingTop, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// page
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Page final : public Longhand {
 public:
  constexpr Page() : Longhand(CSSPropertyID::kPage, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// page-margin-safety
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PageMarginSafety final : public Longhand {
 public:
  constexpr PageMarginSafety() : Longhand(CSSPropertyID::kPageMarginSafety, kDescriptor | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// page-orientation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PageOrientation final : public Longhand {
 public:
  constexpr PageOrientation() : Longhand(CSSPropertyID::kPageOrientation, kDescriptor | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// paint-order
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PaintOrder final : public Longhand {
 public:
  constexpr PaintOrder() : Longhand(CSSPropertyID::kPaintOrder, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// path-length
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PathLength final : public Longhand {
 public:
  constexpr PathLength() : Longhand(CSSPropertyID::kPathLength, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// pathname
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Pathname final : public Longhand {
 public:
  constexpr Pathname() : Longhand(CSSPropertyID::kPathname, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// pattern
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Pattern final : public Longhand {
 public:
  constexpr Pattern() : Longhand(CSSPropertyID::kPattern, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// perspective
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Perspective final : public Longhand {
 public:
  constexpr Perspective() : Longhand(CSSPropertyID::kPerspective, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// perspective-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PerspectiveOrigin final : public Longhand {
 public:
  constexpr PerspectiveOrigin() : Longhand(CSSPropertyID::kPerspectiveOrigin, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// pointer-events
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PointerEvents final : public Longhand {
 public:
  constexpr PointerEvents() : Longhand(CSSPropertyID::kPointerEvents, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// port
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Port final : public Longhand {
 public:
  constexpr Port() : Longhand(CSSPropertyID::kPort, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// position-try-fallbacks
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PositionTryFallbacks final : public Longhand {
 public:
  constexpr PositionTryFallbacks() : Longhand(CSSPropertyID::kPositionTryFallbacks, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// position-try-order
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PositionTryOrder final : public Longhand {
 public:
  constexpr PositionTryOrder() : Longhand(CSSPropertyID::kPositionTryOrder, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// position-visibility
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PositionVisibility final : public Longhand {
 public:
  constexpr PositionVisibility() : Longhand(CSSPropertyID::kPositionVisibility, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// prefix
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Prefix final : public Longhand {
 public:
  constexpr Prefix() : Longhand(CSSPropertyID::kPrefix, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// print-color-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT PrintColorAdjust final : public Longhand {
 public:
  constexpr PrintColorAdjust() : Longhand(CSSPropertyID::kPrintColorAdjust, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// protocol
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Protocol final : public Longhand {
 public:
  constexpr Protocol() : Longhand(CSSPropertyID::kProtocol, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// quotes
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Quotes final : public Longhand {
 public:
  constexpr Quotes() : Longhand(CSSPropertyID::kQuotes, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// r
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT R final : public Longhand {
 public:
  constexpr R() : Longhand(CSSPropertyID::kR, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// range
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Range final : public Longhand {
 public:
  constexpr Range() : Longhand(CSSPropertyID::kRange, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// reading-flow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ReadingFlow final : public Longhand {
 public:
  constexpr ReadingFlow() : Longhand(CSSPropertyID::kReadingFlow, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// reading-order
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ReadingOrder final : public Longhand {
 public:
  constexpr ReadingOrder() : Longhand(CSSPropertyID::kReadingOrder, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// resize
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Resize final : public Longhand {
 public:
  constexpr Resize() : Longhand(CSSPropertyID::kResize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// result
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Result final : public Longhand {
 public:
  constexpr Result() : Longhand(CSSPropertyID::kResult, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// right
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Right final : public Longhand {
 public:
  constexpr Right() : Longhand(CSSPropertyID::kRight, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// rotate
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Rotate final : public Longhand {
 public:
  constexpr Rotate() : Longhand(CSSPropertyID::kRotate, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowGap final : public Longhand {
 public:
  constexpr RowGap() : Longhand(CSSPropertyID::kRowGap, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleBreak final : public Longhand {
 public:
  constexpr RowRuleBreak() : Longhand(CSSPropertyID::kRowRuleBreak, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleColor final : public Longhand {
 public:
  constexpr RowRuleColor() : Longhand(CSSPropertyID::kRowRuleColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// row-rule-inset-cap-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetCapEnd final : public Longhand {
 public:
  constexpr RowRuleInsetCapEnd() : Longhand(CSSPropertyID::kRowRuleInsetCapEnd, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-inset-cap-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetCapStart final : public Longhand {
 public:
  constexpr RowRuleInsetCapStart() : Longhand(CSSPropertyID::kRowRuleInsetCapStart, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-inset-junction-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetJunctionEnd final : public Longhand {
 public:
  constexpr RowRuleInsetJunctionEnd() : Longhand(CSSPropertyID::kRowRuleInsetJunctionEnd, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-inset-junction-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleInsetJunctionStart final : public Longhand {
 public:
  constexpr RowRuleInsetJunctionStart() : Longhand(CSSPropertyID::kRowRuleInsetJunctionStart, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleStyle final : public Longhand {
 public:
  constexpr RowRuleStyle() : Longhand(CSSPropertyID::kRowRuleStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-visibility-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleVisibilityItems final : public Longhand {
 public:
  constexpr RowRuleVisibilityItems() : Longhand(CSSPropertyID::kRowRuleVisibilityItems, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// row-rule-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RowRuleWidth final : public Longhand {
 public:
  constexpr RowRuleWidth() : Longhand(CSSPropertyID::kRowRuleWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// ruby-align
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RubyAlign final : public Longhand {
 public:
  constexpr RubyAlign() : Longhand(CSSPropertyID::kRubyAlign, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// ruby-overhang
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RubyOverhang final : public Longhand {
 public:
  constexpr RubyOverhang() : Longhand(CSSPropertyID::kRubyOverhang, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// ruby-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RubyPosition final : public Longhand {
 public:
  constexpr RubyPosition() : Longhand(CSSPropertyID::kRubyPosition, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLine | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// rule-overlap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT RuleOverlap final : public Longhand {
 public:
  constexpr RuleOverlap() : Longhand(CSSPropertyID::kRuleOverlap, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// rx
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Rx final : public Longhand {
 public:
  constexpr Rx() : Longhand(CSSPropertyID::kRx, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// ry
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Ry final : public Longhand {
 public:
  constexpr Ry() : Longhand(CSSPropertyID::kRy, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scale
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Scale final : public Longhand {
 public:
  constexpr Scale() : Longhand(CSSPropertyID::kScale, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-behavior
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollBehavior final : public Longhand {
 public:
  constexpr ScrollBehavior() : Longhand(CSSPropertyID::kScrollBehavior, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-initial-target
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollInitialTarget final : public Longhand {
 public:
  constexpr ScrollInitialTarget() : Longhand(CSSPropertyID::kScrollInitialTarget, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-margin-block-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginBlockEnd final : public Longhand {
 public:
  constexpr ScrollMarginBlockEnd() : Longhand(CSSPropertyID::kScrollMarginBlockEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-margin-block-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginBlockStart final : public Longhand {
 public:
  constexpr ScrollMarginBlockStart() : Longhand(CSSPropertyID::kScrollMarginBlockStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-margin-bottom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginBottom final : public Longhand {
 public:
  constexpr ScrollMarginBottom() : Longhand(CSSPropertyID::kScrollMarginBottom, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-margin-inline-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginInlineEnd final : public Longhand {
 public:
  constexpr ScrollMarginInlineEnd() : Longhand(CSSPropertyID::kScrollMarginInlineEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-margin-inline-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginInlineStart final : public Longhand {
 public:
  constexpr ScrollMarginInlineStart() : Longhand(CSSPropertyID::kScrollMarginInlineStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-margin-left
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginLeft final : public Longhand {
 public:
  constexpr ScrollMarginLeft() : Longhand(CSSPropertyID::kScrollMarginLeft, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-margin-right
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginRight final : public Longhand {
 public:
  constexpr ScrollMarginRight() : Longhand(CSSPropertyID::kScrollMarginRight, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-margin-top
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarginTop final : public Longhand {
 public:
  constexpr ScrollMarginTop() : Longhand(CSSPropertyID::kScrollMarginTop, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-marker-group
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollMarkerGroup final : public Longhand {
 public:
  constexpr ScrollMarkerGroup() : Longhand(CSSPropertyID::kScrollMarkerGroup, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-padding-block-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingBlockEnd final : public Longhand {
 public:
  constexpr ScrollPaddingBlockEnd() : Longhand(CSSPropertyID::kScrollPaddingBlockEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-padding-block-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingBlockStart final : public Longhand {
 public:
  constexpr ScrollPaddingBlockStart() : Longhand(CSSPropertyID::kScrollPaddingBlockStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-padding-bottom
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingBottom final : public Longhand {
 public:
  constexpr ScrollPaddingBottom() : Longhand(CSSPropertyID::kScrollPaddingBottom, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-padding-inline-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingInlineEnd final : public Longhand {
 public:
  constexpr ScrollPaddingInlineEnd() : Longhand(CSSPropertyID::kScrollPaddingInlineEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-padding-inline-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingInlineStart final : public Longhand {
 public:
  constexpr ScrollPaddingInlineStart() : Longhand(CSSPropertyID::kScrollPaddingInlineStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
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

// scroll-padding-left
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingLeft final : public Longhand {
 public:
  constexpr ScrollPaddingLeft() : Longhand(CSSPropertyID::kScrollPaddingLeft, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-padding-right
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingRight final : public Longhand {
 public:
  constexpr ScrollPaddingRight() : Longhand(CSSPropertyID::kScrollPaddingRight, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-padding-top
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollPaddingTop final : public Longhand {
 public:
  constexpr ScrollPaddingTop() : Longhand(CSSPropertyID::kScrollPaddingTop, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-snap-align
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollSnapAlign final : public Longhand {
 public:
  constexpr ScrollSnapAlign() : Longhand(CSSPropertyID::kScrollSnapAlign, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-snap-stop
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollSnapStop final : public Longhand {
 public:
  constexpr ScrollSnapStop() : Longhand(CSSPropertyID::kScrollSnapStop, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-snap-type
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollSnapType final : public Longhand {
 public:
  constexpr ScrollSnapType() : Longhand(CSSPropertyID::kScrollSnapType, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-target-group
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollTargetGroup final : public Longhand {
 public:
  constexpr ScrollTargetGroup() : Longhand(CSSPropertyID::kScrollTargetGroup, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-timeline-axis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollTimelineAxis final : public Longhand {
 public:
  constexpr ScrollTimelineAxis() : Longhand(CSSPropertyID::kScrollTimelineAxis, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scroll-timeline-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollTimelineName final : public Longhand {
 public:
  constexpr ScrollTimelineName() : Longhand(CSSPropertyID::kScrollTimelineName, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scrollbar-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollbarColor final : public Longhand {
 public:
  constexpr ScrollbarColor() : Longhand(CSSPropertyID::kScrollbarColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scrollbar-gutter
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollbarGutter final : public Longhand {
 public:
  constexpr ScrollbarGutter() : Longhand(CSSPropertyID::kScrollbarGutter, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// scrollbar-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ScrollbarWidth final : public Longhand {
 public:
  constexpr ScrollbarWidth() : Longhand(CSSPropertyID::kScrollbarWidth, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// search
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Search final : public Longhand {
 public:
  constexpr Search() : Longhand(CSSPropertyID::kSearch, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
 };

// shape-image-threshold
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ShapeImageThreshold final : public Longhand {
 public:
  constexpr ShapeImageThreshold() : Longhand(CSSPropertyID::kShapeImageThreshold, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// shape-margin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ShapeMargin final : public Longhand {
 public:
  constexpr ShapeMargin() : Longhand(CSSPropertyID::kShapeMargin, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// shape-outside
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ShapeOutside final : public Longhand {
 public:
  constexpr ShapeOutside() : Longhand(CSSPropertyID::kShapeOutside, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// shape-rendering
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ShapeRendering final : public Longhand {
 public:
  constexpr ShapeRendering() : Longhand(CSSPropertyID::kShapeRendering, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Size final : public Longhand {
 public:
  constexpr Size() : Longhand(CSSPropertyID::kSize, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// size-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT SizeAdjust final : public Longhand {
 public:
  constexpr SizeAdjust() : Longhand(CSSPropertyID::kSizeAdjust, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// speak
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Speak final : public Longhand {
 public:
  constexpr Speak() : Longhand(CSSPropertyID::kSpeak, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// speak-as
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT SpeakAs final : public Longhand {
 public:
  constexpr SpeakAs() : Longhand(CSSPropertyID::kSpeakAs, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// src
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Src final : public Longhand {
 public:
  constexpr Src() : Longhand(CSSPropertyID::kSrc, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// stop-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StopColor final : public Longhand {
 public:
  constexpr StopColor() : Longhand(CSSPropertyID::kStopColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// stop-opacity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StopOpacity final : public Longhand {
 public:
  constexpr StopOpacity() : Longhand(CSSPropertyID::kStopOpacity, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Stroke final : public Longhand {
 public:
  constexpr Stroke() : Longhand(CSSPropertyID::kStroke, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionIcon | kValidForVisited | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// stroke-dasharray
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeDasharray final : public Longhand {
 public:
  constexpr StrokeDasharray() : Longhand(CSSPropertyID::kStrokeDasharray, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke-dashoffset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeDashoffset final : public Longhand {
 public:
  constexpr StrokeDashoffset() : Longhand(CSSPropertyID::kStrokeDashoffset, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke-linecap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeLinecap final : public Longhand {
 public:
  constexpr StrokeLinecap() : Longhand(CSSPropertyID::kStrokeLinecap, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke-linejoin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeLinejoin final : public Longhand {
 public:
  constexpr StrokeLinejoin() : Longhand(CSSPropertyID::kStrokeLinejoin, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke-miterlimit
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeMiterlimit final : public Longhand {
 public:
  constexpr StrokeMiterlimit() : Longhand(CSSPropertyID::kStrokeMiterlimit, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke-opacity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeOpacity final : public Longhand {
 public:
  constexpr StrokeOpacity() : Longhand(CSSPropertyID::kStrokeOpacity, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// stroke-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT StrokeWidth final : public Longhand {
 public:
  constexpr StrokeWidth() : Longhand(CSSPropertyID::kStrokeWidth, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionIcon | kValidForHighlight | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// suffix
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Suffix final : public Longhand {
 public:
  constexpr Suffix() : Longhand(CSSPropertyID::kSuffix, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// symbols
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Symbols final : public Longhand {
 public:
  constexpr Symbols() : Longhand(CSSPropertyID::kSymbols, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// syntax
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Syntax final : public Longhand {
 public:
  constexpr Syntax() : Longhand(CSSPropertyID::kSyntax, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// system
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT System final : public Longhand {
 public:
  constexpr System() : Longhand(CSSPropertyID::kSystem, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// tab-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TabSize final : public Longhand {
 public:
  constexpr TabSize() : Longhand(CSSPropertyID::kTabSize, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// table-layout
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TableLayout final : public Longhand {
 public:
  constexpr TableLayout() : Longhand(CSSPropertyID::kTableLayout, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-align
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextAlign final : public Longhand {
 public:
  constexpr TextAlign() : Longhand(CSSPropertyID::kTextAlign, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-align-last
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextAlignLast final : public Longhand {
 public:
  constexpr TextAlignLast() : Longhand(CSSPropertyID::kTextAlignLast, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-anchor
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextAnchor final : public Longhand {
 public:
  constexpr TextAnchor() : Longhand(CSSPropertyID::kTextAnchor, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-autospace
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextAutospace final : public Longhand {
 public:
  constexpr TextAutospace() : Longhand(CSSPropertyID::kTextAutospace, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-box-edge
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextBoxEdge final : public Longhand {
 public:
  constexpr TextBoxEdge() : Longhand(CSSPropertyID::kTextBoxEdge, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-box-trim
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextBoxTrim final : public Longhand {
 public:
  constexpr TextBoxTrim() : Longhand(CSSPropertyID::kTextBoxTrim, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-combine-upright
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextCombineUpright final : public Longhand {
 public:
  constexpr TextCombineUpright() : Longhand(CSSPropertyID::kTextCombineUpright, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-decoration-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecorationColor final : public Longhand {
 public:
  constexpr TextDecorationColor() : Longhand(CSSPropertyID::kTextDecorationColor, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForVisited | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// text-decoration-line
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecorationLine final : public Longhand {
 public:
  constexpr TextDecorationLine() : Longhand(CSSPropertyID::kTextDecorationLine, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-decoration-skip-ink
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecorationSkipInk final : public Longhand {
 public:
  constexpr TextDecorationSkipInk() : Longhand(CSSPropertyID::kTextDecorationSkipInk, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-decoration-skip-spaces
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecorationSkipSpaces final : public Longhand {
 public:
  constexpr TextDecorationSkipSpaces() : Longhand(CSSPropertyID::kTextDecorationSkipSpaces, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForHighlight, ' ') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-decoration-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecorationStyle final : public Longhand {
 public:
  constexpr TextDecorationStyle() : Longhand(CSSPropertyID::kTextDecorationStyle, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-decoration-thickness
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextDecorationThickness final : public Longhand {
 public:
  constexpr TextDecorationThickness() : Longhand(CSSPropertyID::kTextDecorationThickness, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPageContext | kValidForHighlight | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-emphasis-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextEmphasisColor final : public Longhand {
 public:
  constexpr TextEmphasisColor() : Longhand(CSSPropertyID::kTextEmphasisColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kValidForVisited | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// text-emphasis-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextEmphasisPosition final : public Longhand {
 public:
  constexpr TextEmphasisPosition() : Longhand(CSSPropertyID::kTextEmphasisPosition, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-emphasis-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextEmphasisStyle final : public Longhand {
 public:
  constexpr TextEmphasisStyle() : Longhand(CSSPropertyID::kTextEmphasisStyle, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-fit
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextFit final : public Longhand {
 public:
  constexpr TextFit() : Longhand(CSSPropertyID::kTextFit, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-indent
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextIndent final : public Longhand {
 public:
  constexpr TextIndent() : Longhand(CSSPropertyID::kTextIndent, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-justify
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextJustify final : public Longhand {
 public:
  constexpr TextJustify() : Longhand(CSSPropertyID::kTextJustify, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-overflow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextOverflow final : public Longhand {
 public:
  constexpr TextOverflow() : Longhand(CSSPropertyID::kTextOverflow, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-shadow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextShadow final : public Longhand {
 public:
  constexpr TextShadow() : Longhand(CSSPropertyID::kTextShadow, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForHighlight, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// text-transform
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextTransform final : public Longhand {
 public:
  constexpr TextTransform() : Longhand(CSSPropertyID::kTextTransform, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-underline-offset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextUnderlineOffset final : public Longhand {
 public:
  constexpr TextUnderlineOffset() : Longhand(CSSPropertyID::kTextUnderlineOffset, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPageContext | kValidForHighlight | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-underline-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextUnderlinePosition final : public Longhand {
 public:
  constexpr TextUnderlinePosition() : Longhand(CSSPropertyID::kTextUnderlinePosition, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-wrap-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextWrapMode final : public Longhand {
 public:
  constexpr TextWrapMode() : Longhand(CSSPropertyID::kTextWrapMode, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// text-wrap-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TextWrapStyle final : public Longhand {
 public:
  constexpr TextWrapStyle() : Longhand(CSSPropertyID::kTextWrapStyle, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-scope
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineScope final : public Longhand {
 public:
  constexpr TimelineScope() : Longhand(CSSPropertyID::kTimelineScope, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-trigger-activation-range-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerActivationRangeEnd final : public Longhand {
 public:
  constexpr TimelineTriggerActivationRangeEnd() : Longhand(CSSPropertyID::kTimelineTriggerActivationRangeEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-trigger-activation-range-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerActivationRangeStart final : public Longhand {
 public:
  constexpr TimelineTriggerActivationRangeStart() : Longhand(CSSPropertyID::kTimelineTriggerActivationRangeStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-trigger-active-range-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerActiveRangeEnd final : public Longhand {
 public:
  constexpr TimelineTriggerActiveRangeEnd() : Longhand(CSSPropertyID::kTimelineTriggerActiveRangeEnd, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-trigger-active-range-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerActiveRangeStart final : public Longhand {
 public:
  constexpr TimelineTriggerActiveRangeStart() : Longhand(CSSPropertyID::kTimelineTriggerActiveRangeStart, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe | kPercentagesDoNotDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-trigger-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerName final : public Longhand {
 public:
  constexpr TimelineTriggerName() : Longhand(CSSPropertyID::kTimelineTriggerName, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// timeline-trigger-source
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TimelineTriggerSource final : public Longhand {
 public:
  constexpr TimelineTriggerSource() : Longhand(CSSPropertyID::kTimelineTriggerSource, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// top
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Top final : public Longhand {
 public:
  constexpr Top() : Longhand(CSSPropertyID::kTop, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPermissionElement | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// touch-action
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TouchAction final : public Longhand {
 public:
  constexpr TouchAction() : Longhand(CSSPropertyID::kTouchAction, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transform
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Transform final : public Longhand {
 public:
  constexpr Transform() : Longhand(CSSPropertyID::kTransform, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transform-box
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransformBox final : public Longhand {
 public:
  constexpr TransformBox() : Longhand(CSSPropertyID::kTransformBox, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transform-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransformOrigin final : public Longhand {
 public:
  constexpr TransformOrigin() : Longhand(CSSPropertyID::kTransformOrigin, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kOverlapping | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transform-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransformStyle final : public Longhand {
 public:
  constexpr TransformStyle() : Longhand(CSSPropertyID::kTransformStyle, kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transition-behavior
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransitionBehavior final : public Longhand {
 public:
  constexpr TransitionBehavior() : Longhand(CSSPropertyID::kTransitionBehavior, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transition-delay
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransitionDelay final : public Longhand {
 public:
  constexpr TransitionDelay() : Longhand(CSSPropertyID::kTransitionDelay, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transition-duration
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransitionDuration final : public Longhand {
 public:
  constexpr TransitionDuration() : Longhand(CSSPropertyID::kTransitionDuration, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transition-property
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransitionProperty final : public Longhand {
 public:
  constexpr TransitionProperty() : Longhand(CSSPropertyID::kTransitionProperty, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// transition-timing-function
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TransitionTimingFunction final : public Longhand {
 public:
  constexpr TransitionTimingFunction() : Longhand(CSSPropertyID::kTransitionTimingFunction, kProperty | kNotVisited | kAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// translate
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Translate final : public Longhand {
 public:
  constexpr Translate() : Longhand(CSSPropertyID::kTranslate, kInterpolable | kCompositableProperty | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// trigger-scope
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT TriggerScope final : public Longhand {
 public:
  constexpr TriggerScope() : Longhand(CSSPropertyID::kTriggerScope, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// types
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Types final : public Longhand {
 public:
  constexpr Types() : Longhand(CSSPropertyID::kTypes, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// unicode-bidi
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT UnicodeBidi final : public Longhand {
 public:
  constexpr UnicodeBidi() : Longhand(CSSPropertyID::kUnicodeBidi, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// unicode-range
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT UnicodeRange final : public Longhand {
 public:
  constexpr UnicodeRange() : Longhand(CSSPropertyID::kUnicodeRange, kDescriptor | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// user-select
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT UserSelect final : public Longhand {
 public:
  constexpr UserSelect() : Longhand(CSSPropertyID::kUserSelect, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// vector-effect
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT VectorEffect final : public Longhand {
 public:
  constexpr VectorEffect() : Longhand(CSSPropertyID::kVectorEffect, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// vertical-align
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT VerticalAlign final : public Longhand {
 public:
  constexpr VerticalAlign() : Longhand(CSSPropertyID::kVerticalAlign, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-timeline-axis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTimelineAxis final : public Longhand {
 public:
  constexpr ViewTimelineAxis() : Longhand(CSSPropertyID::kViewTimelineAxis, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-timeline-inset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTimelineInset final : public Longhand {
 public:
  constexpr ViewTimelineInset() : Longhand(CSSPropertyID::kViewTimelineInset, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-timeline-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTimelineName final : public Longhand {
 public:
  constexpr ViewTimelineName() : Longhand(CSSPropertyID::kViewTimelineName, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, ',') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-transition-class
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTransitionClass final : public Longhand {
 public:
  constexpr ViewTransitionClass() : Longhand(CSSPropertyID::kViewTransitionClass, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-transition-group
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTransitionGroup final : public Longhand {
 public:
  constexpr ViewTransitionGroup() : Longhand(CSSPropertyID::kViewTransitionGroup, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-transition-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTransitionName final : public Longhand {
 public:
  constexpr ViewTransitionName() : Longhand(CSSPropertyID::kViewTransitionName, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// view-transition-scope
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ViewTransitionScope final : public Longhand {
 public:
  constexpr ViewTransitionScope() : Longhand(CSSPropertyID::kViewTransitionScope, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// visibility
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Visibility final : public Longhand {
 public:
  constexpr Visibility() : Longhand(CSSPropertyID::kVisibility, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForCue | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-border-horizontal-spacing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderHorizontalSpacing final : public Longhand {
 public:
  constexpr WebkitBorderHorizontalSpacing() : Longhand(CSSPropertyID::kWebkitBorderHorizontalSpacing, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-border-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderImage final : public Longhand {
 public:
  constexpr WebkitBorderImage() : Longhand(CSSPropertyID::kWebkitBorderImage, kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-border-vertical-spacing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderVerticalSpacing final : public Longhand {
 public:
  constexpr WebkitBorderVerticalSpacing() : Longhand(CSSPropertyID::kWebkitBorderVerticalSpacing, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-align
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxAlign final : public Longhand {
 public:
  constexpr WebkitBoxAlign() : Longhand(CSSPropertyID::kWebkitBoxAlign, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-decoration-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxDecorationBreak final : public Longhand {
 public:
  constexpr WebkitBoxDecorationBreak() : Longhand(CSSPropertyID::kWebkitBoxDecorationBreak, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kSurrogate, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-box-direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxDirection final : public Longhand {
 public:
  constexpr WebkitBoxDirection() : Longhand(CSSPropertyID::kWebkitBoxDirection, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-flex
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxFlex final : public Longhand {
 public:
  constexpr WebkitBoxFlex() : Longhand(CSSPropertyID::kWebkitBoxFlex, kProperty | kNotVisited | kNotAnimation | kIdempotent | kAcceptsNumericLiteral | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-ordinal-group
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxOrdinalGroup final : public Longhand {
 public:
  constexpr WebkitBoxOrdinalGroup() : Longhand(CSSPropertyID::kWebkitBoxOrdinalGroup, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-orient
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxOrient final : public Longhand {
 public:
  constexpr WebkitBoxOrient() : Longhand(CSSPropertyID::kWebkitBoxOrient, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-pack
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxPack final : public Longhand {
 public:
  constexpr WebkitBoxPack() : Longhand(CSSPropertyID::kWebkitBoxPack, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-box-reflect
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxReflect final : public Longhand {
 public:
  constexpr WebkitBoxReflect() : Longhand(CSSPropertyID::kWebkitBoxReflect, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// -webkit-line-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitLineBreak final : public Longhand {
 public:
  constexpr WebkitLineBreak() : Longhand(CSSPropertyID::kWebkitLineBreak, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kSurrogate, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-line-clamp
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitLineClamp final : public Longhand {
 public:
  constexpr WebkitLineClamp() : Longhand(CSSPropertyID::kWebkitLineClamp, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  CSSExposure Exposure(const ExecutionContext*) const override;
  CSSPropertyID GetAlternative() const override {
    return CSSPropertyID::kAlternativeWebkitLineClamp;
  }
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-mask-box-image-outset
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskBoxImageOutset final : public Longhand {
 public:
  constexpr WebkitMaskBoxImageOutset() : Longhand(CSSPropertyID::kWebkitMaskBoxImageOutset, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-mask-box-image-repeat
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskBoxImageRepeat final : public Longhand {
 public:
  constexpr WebkitMaskBoxImageRepeat() : Longhand(CSSPropertyID::kWebkitMaskBoxImageRepeat, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-mask-box-image-slice
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskBoxImageSlice final : public Longhand {
 public:
  constexpr WebkitMaskBoxImageSlice() : Longhand(CSSPropertyID::kWebkitMaskBoxImageSlice, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-mask-box-image-source
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskBoxImageSource final : public Longhand {
 public:
  constexpr WebkitMaskBoxImageSource() : Longhand(CSSPropertyID::kWebkitMaskBoxImageSource, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// -webkit-mask-box-image-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskBoxImageWidth final : public Longhand {
 public:
  constexpr WebkitMaskBoxImageWidth() : Longhand(CSSPropertyID::kWebkitMaskBoxImageWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-mask-position-x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskPositionX final : public Longhand {
 public:
  constexpr WebkitMaskPositionX() : Longhand(CSSPropertyID::kWebkitMaskPositionX, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-mask-position-y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskPositionY final : public Longhand {
 public:
  constexpr WebkitMaskPositionY() : Longhand(CSSPropertyID::kWebkitMaskPositionY, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-perspective-origin-x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPerspectiveOriginX final : public Longhand {
 public:
  constexpr WebkitPerspectiveOriginX() : Longhand(CSSPropertyID::kWebkitPerspectiveOriginX, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-perspective-origin-y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPerspectiveOriginY final : public Longhand {
 public:
  constexpr WebkitPerspectiveOriginY() : Longhand(CSSPropertyID::kWebkitPerspectiveOriginY, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-rtl-ordering
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitRtlOrdering final : public Longhand {
 public:
  constexpr WebkitRtlOrdering() : Longhand(CSSPropertyID::kWebkitRtlOrdering, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-ruby-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitRubyPosition final : public Longhand {
 public:
  constexpr WebkitRubyPosition() : Longhand(CSSPropertyID::kWebkitRubyPosition, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kSurrogate, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-tap-highlight-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTapHighlightColor final : public Longhand {
 public:
  constexpr WebkitTapHighlightColor() : Longhand(CSSPropertyID::kWebkitTapHighlightColor, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// -webkit-text-combine
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextCombine final : public Longhand {
 public:
  constexpr WebkitTextCombine() : Longhand(CSSPropertyID::kWebkitTextCombine, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kSurrogate, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSProperty* SurrogateFor(WritingDirectionMode) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
 };

// -webkit-text-decorations-in-effect
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextDecorationsInEffect final : public Longhand {
 public:
  constexpr WebkitTextDecorationsInEffect() : Longhand(CSSPropertyID::kWebkitTextDecorationsInEffect, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-text-fill-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextFillColor final : public Longhand {
 public:
  constexpr WebkitTextFillColor() : Longhand(CSSPropertyID::kWebkitTextFillColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForVisited, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-text-security
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextSecurity final : public Longhand {
 public:
  constexpr WebkitTextSecurity() : Longhand(CSSPropertyID::kWebkitTextSecurity, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-text-stroke-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextStrokeColor final : public Longhand {
 public:
  constexpr WebkitTextStrokeColor() : Longhand(CSSPropertyID::kWebkitTextStrokeColor, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForVisited, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const blink::Color ColorIncludingFallback(bool, const ComputedStyle&, bool* is_current_color = nullptr) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
  [[nodiscard]] bool IsAffectedByCurrentColor(const ComputedStyle& style) const override;
 };

// -webkit-text-stroke-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextStrokeWidth final : public Longhand {
 public:
  constexpr WebkitTextStrokeWidth() : Longhand(CSSPropertyID::kWebkitTextStrokeWidth, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-transform-origin-x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransformOriginX final : public Longhand {
 public:
  constexpr WebkitTransformOriginX() : Longhand(CSSPropertyID::kWebkitTransformOriginX, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-transform-origin-y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransformOriginY final : public Longhand {
 public:
  constexpr WebkitTransformOriginY() : Longhand(CSSPropertyID::kWebkitTransformOriginY, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-transform-origin-z
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransformOriginZ final : public Longhand {
 public:
  constexpr WebkitTransformOriginZ() : Longhand(CSSPropertyID::kWebkitTransformOriginZ, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kOverlapping | kLegacyOverlapping | kValidForKeyframe | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-user-drag
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitUserDrag final : public Longhand {
 public:
  constexpr WebkitUserDrag() : Longhand(CSSPropertyID::kWebkitUserDrag, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-user-modify
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitUserModify final : public Longhand {
 public:
  constexpr WebkitUserModify() : Longhand(CSSPropertyID::kWebkitUserModify, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsAffectedByAll() const override { return false; }
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// white-space-collapse
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WhiteSpaceCollapse final : public Longhand {
 public:
  constexpr WhiteSpaceCollapse() : Longhand(CSSPropertyID::kWhiteSpaceCollapse, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForCue | kValidForMarker | kValidForKeyframe | kValidForPageContext, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// widows
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Widows final : public Longhand {
 public:
  constexpr Widows() : Longhand(CSSPropertyID::kWidows, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Width final : public Longhand {
 public:
  constexpr Width() : Longhand(CSSPropertyID::kWidth, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPositionTry | kValidForPageContext | kValidForPermissionElement | kValidForPermissionIcon | kInLogicalPropertyGroup | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  bool IsLayoutDependentProperty() const override { return true; }
  bool IsLayoutDependent(const ComputedStyle*, LayoutObject*) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  bool IsInSameLogicalPropertyGroupWithDifferentMappingLogic(CSSPropertyID) const override;
  const CSSProperty& ToLogicalInternal(
      WritingDirectionMode) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// will-change
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WillChange final : public Longhand {
 public:
  constexpr WillChange() : Longhand(CSSPropertyID::kWillChange, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// word-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WordBreak final : public Longhand {
 public:
  constexpr WordBreak() : Longhand(CSSPropertyID::kWordBreak, kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForMarker | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// word-spacing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WordSpacing final : public Longhand {
 public:
  constexpr WordSpacing() : Longhand(CSSPropertyID::kWordSpacing, kInterpolable | kProperty | kInherited | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForFirstLetter | kValidForFirstLine | kValidForMarker | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement | kPercentagesDoNotDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// x
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT X final : public Longhand {
 public:
  constexpr X() : Longhand(CSSPropertyID::kX, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// y
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT Y final : public Longhand {
 public:
  constexpr Y() : Longhand(CSSPropertyID::kY, kInterpolable | kProperty | kNotVisited | kNotAnimation | kSupportsIncrementalStyle | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPermissionElement | kPercentagesDependOnUsedValue, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// z-index
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT ZIndex final : public Longhand {
 public:
  constexpr ZIndex() : Longhand(CSSPropertyID::kZIndex, kInterpolable | kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe | kValidForPageContext | kValidForPermissionElement, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// mask-composite
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT MaskComposite final : public Longhand {
 public:
  constexpr MaskComposite() : Longhand(CSSPropertyID::kMaskComposite, kProperty | kNotVisited | kNotAnimation | kIdempotent | kNotLegacyOverlapping | kValidForKeyframe, '\0') { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
  const CSSValue* ParseSingleValue(CSSParserTokenStream&, const CSSParserContext&, CSSParserLocalContext&) const override;
  const CSSValue* CSSValueFromComputedStyleInternal(const ComputedStyle&, const LayoutObject*, bool allow_visited_style, CSSValuePhase value_phase) const override;
  const CSSValue* InitialValue() const override;
  void ApplyInitial(StyleResolverState&) const override;
  void ApplyInherit(StyleResolverState&) const override;
  void ApplyValue(StyleResolverState&, const CSSValue&, ValueModeFlags) const override;
 };

// -webkit-appearance
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAppearance final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAppearance() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-app-region
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAppRegion final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAppRegion() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-clip
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskClip final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskClip() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-composite
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskComposite final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskComposite() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-image
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskImage final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskImage() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskOrigin final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskOrigin() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-repeat
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskRepeat final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskRepeat() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-mask-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaskSize final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaskSize() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-end-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderEndColor final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderEndColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-end-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderEndStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderEndStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-end-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderEndWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderEndWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-start-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderStartColor final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderStartColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-start-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderStartStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderStartStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-start-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderStartWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderStartWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-before-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderBeforeColor final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderBeforeColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-before-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderBeforeStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderBeforeStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-before-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderBeforeWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderBeforeWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-after-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderAfterColor final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderAfterColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-after-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderAfterStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderAfterStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-after-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderAfterWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderAfterWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-margin-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMarginEnd final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMarginEnd() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-margin-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMarginStart final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMarginStart() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-margin-before
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMarginBefore final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMarginBefore() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-margin-after
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMarginAfter final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMarginAfter() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-padding-end
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPaddingEnd final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPaddingEnd() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-padding-start
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPaddingStart final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPaddingStart() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-padding-before
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPaddingBefore final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPaddingBefore() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-padding-after
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPaddingAfter final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPaddingAfter() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-logical-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitLogicalWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitLogicalWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-logical-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitLogicalHeight final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitLogicalHeight() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-min-logical-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMinLogicalWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMinLogicalWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-min-logical-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMinLogicalHeight final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMinLogicalHeight() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-max-logical-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaxLogicalWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaxLogicalWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-max-logical-height
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitMaxLogicalHeight final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitMaxLogicalHeight() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-print-color-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPrintColorAdjust final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPrintColorAdjust() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-caption-side
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubCaptionSide final : public CSSUnresolvedProperty {
 public:
  constexpr EpubCaptionSide() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-text-combine
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubTextCombine final : public CSSUnresolvedProperty {
 public:
  constexpr EpubTextCombine() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-text-emphasis-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubTextEmphasisColor final : public CSSUnresolvedProperty {
 public:
  constexpr EpubTextEmphasisColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-text-emphasis-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubTextEmphasisStyle final : public CSSUnresolvedProperty {
 public:
  constexpr EpubTextEmphasisStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-text-orientation
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubTextOrientation final : public CSSUnresolvedProperty {
 public:
  constexpr EpubTextOrientation() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-text-transform
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubTextTransform final : public CSSUnresolvedProperty {
 public:
  constexpr EpubTextTransform() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-word-break
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubWordBreak final : public CSSUnresolvedProperty {
 public:
  constexpr EpubWordBreak() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -epub-writing-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT EpubWritingMode final : public CSSUnresolvedProperty {
 public:
  constexpr EpubWritingMode() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-align-content
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAlignContent final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAlignContent() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-align-items
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAlignItems final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAlignItems() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-align-self
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAlignSelf final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAlignSelf() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-delay
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationDelay final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationDelay() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationDirection final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationDirection() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-duration
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationDuration final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationDuration() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-fill-mode
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationFillMode final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationFillMode() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-iteration-count
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationIterationCount final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationIterationCount() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-name
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationName final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationName() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-play-state
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationPlayState final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationPlayState() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-animation-timing-function
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitAnimationTimingFunction final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitAnimationTimingFunction() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-backface-visibility
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBackfaceVisibility final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBackfaceVisibility() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-background-clip
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBackgroundClip final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBackgroundClip() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-background-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBackgroundOrigin final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBackgroundOrigin() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-background-size
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBackgroundSize final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBackgroundSize() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-bottom-left-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderBottomLeftRadius final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderBottomLeftRadius() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-bottom-right-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderBottomRightRadius final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderBottomRightRadius() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-top-left-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderTopLeftRadius final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderTopLeftRadius() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-border-top-right-radius
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBorderTopRightRadius final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBorderTopRightRadius() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-box-shadow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxShadow final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBoxShadow() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-box-sizing
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitBoxSizing final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitBoxSizing() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-clip-path
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitClipPath final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitClipPath() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-count
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnCount final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnCount() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnGap final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnGap() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-rule-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnRuleColor final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnRuleColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-rule-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnRuleStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnRuleStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-rule-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnRuleWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnRuleWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-span
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnSpan final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnSpan() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-column-width
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitColumnWidth final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitColumnWidth() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-filter
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFilter final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFilter() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex-basis
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlexBasis final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlexBasis() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex-direction
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlexDirection final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlexDirection() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex-grow
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlexGrow final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlexGrow() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex-shrink
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlexShrink final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlexShrink() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-flex-wrap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFlexWrap final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFlexWrap() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-font-feature-settings
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitFontFeatureSettings final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitFontFeatureSettings() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-hyphenate-character
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitHyphenateCharacter final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitHyphenateCharacter() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-justify-content
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitJustifyContent final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitJustifyContent() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-opacity
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitOpacity final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitOpacity() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-order
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitOrder final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitOrder() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-perspective
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPerspective final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPerspective() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-perspective-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitPerspectiveOrigin final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitPerspectiveOrigin() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-shape-image-threshold
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitShapeImageThreshold final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitShapeImageThreshold() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-shape-margin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitShapeMargin final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitShapeMargin() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-shape-outside
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitShapeOutside final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitShapeOutside() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-text-emphasis-color
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextEmphasisColor final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTextEmphasisColor() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-text-emphasis-position
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextEmphasisPosition final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTextEmphasisPosition() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-text-emphasis-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextEmphasisStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTextEmphasisStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-text-size-adjust
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTextSizeAdjust final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTextSizeAdjust() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transform
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransform final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransform() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transform-origin
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransformOrigin final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransformOrigin() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transform-style
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransformStyle final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransformStyle() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transition-delay
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransitionDelay final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransitionDelay() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transition-duration
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransitionDuration final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransitionDuration() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transition-property
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransitionProperty final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransitionProperty() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-transition-timing-function
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitTransitionTimingFunction final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitTransitionTimingFunction() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// -webkit-user-select
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WebkitUserSelect final : public CSSUnresolvedProperty {
 public:
  constexpr WebkitUserSelect() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// word-wrap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT WordWrap final : public CSSUnresolvedProperty {
 public:
  constexpr WordWrap() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// grid-column-gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridColumnGap final : public CSSUnresolvedProperty {
 public:
  constexpr GridColumnGap() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

// grid-row-gap
// NOTE: Multiple inheritance is not allowed here, since the class must be
// reinterpret_cast-able to CSSUnresolvedProperty. See css_property_instances.cc.tmpl
// (the cast happens in GetPropertyInternal()).
class CORE_EXPORT GridRowGap final : public CSSUnresolvedProperty {
 public:
  constexpr GridRowGap() : CSSUnresolvedProperty() { }
  const char* GetPropertyName() const override;
  const AtomicString& GetPropertyNameAtomicString() const override;
  const char* GetJSPropertyName() const override;
 };

 
}  // namespace css_longhand
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CSS_PROPERTIES_CSS_PROPERTIES_LONGHANDS_H_
