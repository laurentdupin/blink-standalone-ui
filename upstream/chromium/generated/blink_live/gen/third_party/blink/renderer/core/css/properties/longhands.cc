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



#include "third_party/blink/renderer/core/css/properties/longhands.h"

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
namespace css_longhand {

// color-scheme



const char* ColorScheme::GetPropertyName() const {
  return "color-scheme";
}

const AtomicString& ColorScheme::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("color-scheme"));
  return name;
}

const char* ColorScheme::GetJSPropertyName() const {
  return "colorScheme";
}




 // forced-color-adjust


CSSExposure ForcedColorAdjust::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::ForcedColorsEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ForcedColorAdjust::GetPropertyName() const {
  return "forced-color-adjust";
}

const AtomicString& ForcedColorAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("forced-color-adjust"));
  return name;
}

const char* ForcedColorAdjust::GetJSPropertyName() const {
  return "forcedColorAdjust";
}



void ForcedColorAdjust::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetForcedColorAdjust(ComputedStyleInitialValues::InitialForcedColorAdjust());
}
void ForcedColorAdjust::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetForcedColorAdjust(state.ParentStyle()->ForcedColorAdjust());
}
void ForcedColorAdjust::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetForcedColorAdjust(To<CSSIdentifierValue>(value).ConvertTo<blink::EForcedColorAdjust>());
}

 // math-depth



const char* MathDepth::GetPropertyName() const {
  return "math-depth";
}

const AtomicString& MathDepth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("math-depth"));
  return name;
}

const char* MathDepth::GetJSPropertyName() const {
  return "mathDepth";
}


const CSSValue* MathDepth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeMathDepth(stream, context, local_context);
}

void MathDepth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMathDepth(ComputedStyleInitialValues::InitialMathDepth());
}
void MathDepth::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMathDepth(state.ParentStyle()->MathDepth());
}

 // position



const char* Position::GetPropertyName() const {
  return "position";
}

const AtomicString& Position::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position"));
  return name;
}

const char* Position::GetJSPropertyName() const {
  return "position";
}



void Position::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPosition(ComputedStyleInitialValues::InitialPosition());
}
void Position::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPosition(state.ParentStyle()->GetPosition());
}
void Position::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPosition(To<CSSIdentifierValue>(value).ConvertTo<blink::EPosition>());
}

 // position-anchor



const char* PositionAnchor::GetPropertyName() const {
  return "position-anchor";
}

const AtomicString& PositionAnchor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position-anchor"));
  return name;
}

const char* PositionAnchor::GetJSPropertyName() const {
  return "positionAnchor";
}




 // text-size-adjust



const char* TextSizeAdjust::GetPropertyName() const {
  return "text-size-adjust";
}

const AtomicString& TextSizeAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-size-adjust"));
  return name;
}

const char* TextSizeAdjust::GetJSPropertyName() const {
  return "textSizeAdjust";
}




 // -internal-visited-color


CSSExposure InternalVisitedColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedColor::GetPropertyName() const {
  return "-internal-visited-color";
}

const AtomicString& InternalVisitedColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-color"));
  return name;
}

const char* InternalVisitedColor::GetJSPropertyName() const {
  return "internalVisitedColor";
}


const CSSValue* InternalVisitedColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}


 // appearance



const char* Appearance::GetPropertyName() const {
  return "appearance";
}

const AtomicString& Appearance::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("appearance"));
  return name;
}

const char* Appearance::GetJSPropertyName() const {
  return "appearance";
}



void Appearance::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAppearance(ComputedStyleInitialValues::InitialAppearance());
}
void Appearance::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAppearance(state.ParentStyle()->Appearance());
}
void Appearance::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAppearance(To<CSSIdentifierValue>(value).ConvertTo<blink::AppearanceValue>());
}

 // color



const char* Color::GetPropertyName() const {
  return "color";
}

const AtomicString& Color::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("color"));
  return name;
}

const char* Color::GetJSPropertyName() const {
  return "color";
}


const CSSValue* Color::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}


 // direction



const char* Direction::GetPropertyName() const {
  return "direction";
}

const AtomicString& Direction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("direction"));
  return name;
}

const char* Direction::GetJSPropertyName() const {
  return "direction";
}



void Direction::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetDirection(ComputedStyleInitialValues::InitialDirection());
}
void Direction::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetDirection(state.ParentStyle()->Direction());
}

 // font-family



const char* FontFamily::GetPropertyName() const {
  return "font-family";
}

const AtomicString& FontFamily::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-family"));
  return name;
}

const char* FontFamily::GetJSPropertyName() const {
  return "fontFamily";
}



void FontFamily::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFamilyDescription(StyleBuilderConverter::ConvertFontFamily(state, value));
}

 // font-feature-settings



const char* FontFeatureSettings::GetPropertyName() const {
  return "font-feature-settings";
}

const AtomicString& FontFeatureSettings::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-feature-settings"));
  return name;
}

const char* FontFeatureSettings::GetJSPropertyName() const {
  return "fontFeatureSettings";
}


const CSSValue* FontFeatureSettings::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFontFeatureSettings(stream, context, local_context);
}

void FontFeatureSettings::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFeatureSettings(FontBuilder::InitialFeatureSettings());
}
void FontFeatureSettings::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFeatureSettings(state.ParentFontDescription().FeatureSettings());
}
void FontFeatureSettings::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFeatureSettings(StyleBuilderConverter::ConvertFontFeatureSettings(state, value));
}

 // font-kerning



const char* FontKerning::GetPropertyName() const {
  return "font-kerning";
}

const AtomicString& FontKerning::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-kerning"));
  return name;
}

const char* FontKerning::GetJSPropertyName() const {
  return "fontKerning";
}



void FontKerning::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetKerning(FontBuilder::InitialKerning());
}
void FontKerning::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetKerning(state.ParentFontDescription().GetKerning());
}
void FontKerning::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetKerning(StyleBuilderConverter::ConvertFontKerning(state, value));
}

 // font-language-override


CSSExposure FontLanguageOverride::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::FontLanguageOverrideEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* FontLanguageOverride::GetPropertyName() const {
  return "font-language-override";
}

const AtomicString& FontLanguageOverride::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-language-override"));
  return name;
}

const char* FontLanguageOverride::GetJSPropertyName() const {
  return "fontLanguageOverride";
}



void FontLanguageOverride::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontLanguageOverride(FontBuilder::InitialFontLanguageOverride());
}
void FontLanguageOverride::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontLanguageOverride(state.ParentFontDescription().FontLanguageOverride());
}
void FontLanguageOverride::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontLanguageOverride(StyleBuilderConverter::ConvertFontLanguageOverride(state, value));
}

 // font-optical-sizing



const char* FontOpticalSizing::GetPropertyName() const {
  return "font-optical-sizing";
}

const AtomicString& FontOpticalSizing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-optical-sizing"));
  return name;
}

const char* FontOpticalSizing::GetJSPropertyName() const {
  return "fontOpticalSizing";
}



void FontOpticalSizing::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontOpticalSizing(FontBuilder::InitialFontOpticalSizing());
}
void FontOpticalSizing::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontOpticalSizing(state.ParentFontDescription().FontOpticalSizing());
}
void FontOpticalSizing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontOpticalSizing(StyleBuilderConverter::ConvertFontOpticalSizing(state, value));
}

 // font-palette



const char* FontPalette::GetPropertyName() const {
  return "font-palette";
}

const AtomicString& FontPalette::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-palette"));
  return name;
}

const char* FontPalette::GetJSPropertyName() const {
  return "fontPalette";
}


const CSSValue* FontPalette::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFontPalette(stream, context, local_context);
}

void FontPalette::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontPalette(FontBuilder::InitialFontPalette());
}
void FontPalette::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontPalette(state.ParentFontDescription().GetFontPalette());
}
void FontPalette::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontPalette(StyleBuilderConverter::ConvertFontPalette(state, value));
}

 // font-size



const char* FontSize::GetPropertyName() const {
  return "font-size";
}

const AtomicString& FontSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-size"));
  return name;
}

const char* FontSize::GetJSPropertyName() const {
  return "fontSize";
}



void FontSize::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetSize(FontBuilder::InitialSize());
}
void FontSize::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetSize(state.ParentFontDescription().GetSize());
}
void FontSize::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetSize(StyleBuilderConverter::ConvertFontSize(state, value));
}

 // font-size-adjust


CSSExposure FontSizeAdjust::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSFontSizeAdjustEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* FontSizeAdjust::GetPropertyName() const {
  return "font-size-adjust";
}

const AtomicString& FontSizeAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-size-adjust"));
  return name;
}

const char* FontSizeAdjust::GetJSPropertyName() const {
  return "fontSizeAdjust";
}



void FontSizeAdjust::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetSizeAdjust(FontBuilder::InitialSizeAdjust());
}
void FontSizeAdjust::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetSizeAdjust(state.ParentFontDescription().SizeAdjust());
}
void FontSizeAdjust::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetSizeAdjust(StyleBuilderConverter::ConvertFontSizeAdjust(state, value));
}

 // font-stretch



const char* FontStretch::GetPropertyName() const {
  return "font-stretch";
}

const AtomicString& FontStretch::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-stretch"));
  return name;
}

const char* FontStretch::GetJSPropertyName() const {
  return "fontStretch";
}


const CSSValue* FontStretch::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFontStretch(stream, context, local_context);
}

void FontStretch::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetStretch(FontBuilder::InitialStretch());
}
void FontStretch::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetStretch(state.ParentFontDescription().Stretch());
}
void FontStretch::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetStretch(StyleBuilderConverter::ConvertFontStretch(state, value));
}

 // font-style



const char* FontStyle::GetPropertyName() const {
  return "font-style";
}

const AtomicString& FontStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-style"));
  return name;
}

const char* FontStyle::GetJSPropertyName() const {
  return "fontStyle";
}


const CSSValue* FontStyle::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFontStyle(stream, context, local_context);
}

void FontStyle::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetStyle(FontBuilder::InitialStyle());
}
void FontStyle::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetStyle(state.ParentFontDescription().Style());
}
void FontStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetStyle(StyleBuilderConverter::ConvertFontStyle(state, value));
}

 // font-synthesis-small-caps



const char* FontSynthesisSmallCaps::GetPropertyName() const {
  return "font-synthesis-small-caps";
}

const AtomicString& FontSynthesisSmallCaps::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-synthesis-small-caps"));
  return name;
}

const char* FontSynthesisSmallCaps::GetJSPropertyName() const {
  return "fontSynthesisSmallCaps";
}



void FontSynthesisSmallCaps::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSynthesisSmallCaps(FontBuilder::InitialFontSynthesisSmallCaps());
}
void FontSynthesisSmallCaps::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSynthesisSmallCaps(state.ParentFontDescription().GetFontSynthesisSmallCaps());
}
void FontSynthesisSmallCaps::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontSynthesisSmallCaps(To<CSSIdentifierValue>(value).ConvertTo<blink::FontDescription::FontSynthesisSmallCaps>());
}

 // font-synthesis-style



const char* FontSynthesisStyle::GetPropertyName() const {
  return "font-synthesis-style";
}

const AtomicString& FontSynthesisStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-synthesis-style"));
  return name;
}

const char* FontSynthesisStyle::GetJSPropertyName() const {
  return "fontSynthesisStyle";
}



void FontSynthesisStyle::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSynthesisStyle(FontBuilder::InitialFontSynthesisStyle());
}
void FontSynthesisStyle::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSynthesisStyle(state.ParentFontDescription().GetFontSynthesisStyle());
}
void FontSynthesisStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontSynthesisStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::FontDescription::FontSynthesisStyle>());
}

 // font-synthesis-weight



const char* FontSynthesisWeight::GetPropertyName() const {
  return "font-synthesis-weight";
}

const AtomicString& FontSynthesisWeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-synthesis-weight"));
  return name;
}

const char* FontSynthesisWeight::GetJSPropertyName() const {
  return "fontSynthesisWeight";
}



void FontSynthesisWeight::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSynthesisWeight(FontBuilder::InitialFontSynthesisWeight());
}
void FontSynthesisWeight::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSynthesisWeight(state.ParentFontDescription().GetFontSynthesisWeight());
}
void FontSynthesisWeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontSynthesisWeight(To<CSSIdentifierValue>(value).ConvertTo<blink::FontDescription::FontSynthesisWeight>());
}

 // font-variant-alternates



const char* FontVariantAlternates::GetPropertyName() const {
  return "font-variant-alternates";
}

const AtomicString& FontVariantAlternates::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-alternates"));
  return name;
}

const char* FontVariantAlternates::GetJSPropertyName() const {
  return "fontVariantAlternates";
}



void FontVariantAlternates::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontVariantAlternates(FontBuilder::InitialFontVariantAlternates());
}
void FontVariantAlternates::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontVariantAlternates(state.ParentFontDescription().GetFontVariantAlternates());
}
void FontVariantAlternates::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontVariantAlternates(StyleBuilderConverter::ConvertFontVariantAlternates(state, value));
}

 // font-variant-caps



const char* FontVariantCaps::GetPropertyName() const {
  return "font-variant-caps";
}

const AtomicString& FontVariantCaps::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-caps"));
  return name;
}

const char* FontVariantCaps::GetJSPropertyName() const {
  return "fontVariantCaps";
}



void FontVariantCaps::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantCaps(FontBuilder::InitialVariantCaps());
}
void FontVariantCaps::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantCaps(state.ParentFontDescription().VariantCaps());
}
void FontVariantCaps::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariantCaps(StyleBuilderConverter::ConvertFontVariantCaps(state, value));
}

 // font-variant-east-asian



const char* FontVariantEastAsian::GetPropertyName() const {
  return "font-variant-east-asian";
}

const AtomicString& FontVariantEastAsian::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-east-asian"));
  return name;
}

const char* FontVariantEastAsian::GetJSPropertyName() const {
  return "fontVariantEastAsian";
}



void FontVariantEastAsian::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantEastAsian(FontBuilder::InitialVariantEastAsian());
}
void FontVariantEastAsian::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantEastAsian(state.ParentFontDescription().VariantEastAsian());
}
void FontVariantEastAsian::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariantEastAsian(StyleBuilderConverter::ConvertFontVariantEastAsian(state, value));
}

 // font-variant-emoji



const char* FontVariantEmoji::GetPropertyName() const {
  return "font-variant-emoji";
}

const AtomicString& FontVariantEmoji::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-emoji"));
  return name;
}

const char* FontVariantEmoji::GetJSPropertyName() const {
  return "fontVariantEmoji";
}



void FontVariantEmoji::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantEmoji(FontBuilder::InitialVariantEmoji());
}
void FontVariantEmoji::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantEmoji(state.ParentFontDescription().VariantEmoji());
}
void FontVariantEmoji::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariantEmoji(StyleBuilderConverter::ConvertFontVariantEmoji(state, value));
}

 // font-variant-ligatures



const char* FontVariantLigatures::GetPropertyName() const {
  return "font-variant-ligatures";
}

const AtomicString& FontVariantLigatures::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-ligatures"));
  return name;
}

const char* FontVariantLigatures::GetJSPropertyName() const {
  return "fontVariantLigatures";
}



void FontVariantLigatures::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantLigatures(FontBuilder::InitialVariantLigatures());
}
void FontVariantLigatures::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantLigatures(state.ParentFontDescription().GetVariantLigatures());
}
void FontVariantLigatures::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariantLigatures(StyleBuilderConverter::ConvertFontVariantLigatures(state, value));
}

 // font-variant-numeric



const char* FontVariantNumeric::GetPropertyName() const {
  return "font-variant-numeric";
}

const AtomicString& FontVariantNumeric::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-numeric"));
  return name;
}

const char* FontVariantNumeric::GetJSPropertyName() const {
  return "fontVariantNumeric";
}



void FontVariantNumeric::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantNumeric(FontBuilder::InitialVariantNumeric());
}
void FontVariantNumeric::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantNumeric(state.ParentFontDescription().VariantNumeric());
}
void FontVariantNumeric::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariantNumeric(StyleBuilderConverter::ConvertFontVariantNumeric(state, value));
}

 // font-variant-position



const char* FontVariantPosition::GetPropertyName() const {
  return "font-variant-position";
}

const AtomicString& FontVariantPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variant-position"));
  return name;
}

const char* FontVariantPosition::GetJSPropertyName() const {
  return "fontVariantPosition";
}



void FontVariantPosition::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantPosition(FontBuilder::InitialVariantPosition());
}
void FontVariantPosition::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariantPosition(state.ParentFontDescription().VariantPosition());
}
void FontVariantPosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariantPosition(StyleBuilderConverter::ConvertFontVariantPosition(state, value));
}

 // font-variation-settings



const char* FontVariationSettings::GetPropertyName() const {
  return "font-variation-settings";
}

const AtomicString& FontVariationSettings::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-variation-settings"));
  return name;
}

const char* FontVariationSettings::GetJSPropertyName() const {
  return "fontVariationSettings";
}



void FontVariationSettings::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariationSettings(FontBuilder::InitialVariationSettings());
}
void FontVariationSettings::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetVariationSettings(state.ParentFontDescription().VariationSettings());
}
void FontVariationSettings::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetVariationSettings(StyleBuilderConverter::ConvertFontVariationSettings(state, value));
}

 // font-weight



const char* FontWeight::GetPropertyName() const {
  return "font-weight";
}

const AtomicString& FontWeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-weight"));
  return name;
}

const char* FontWeight::GetJSPropertyName() const {
  return "fontWeight";
}


const CSSValue* FontWeight::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFontWeight(stream, context, local_context);
}

void FontWeight::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetWeight(FontBuilder::InitialWeight());
}
void FontWeight::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetWeight(state.ParentFontDescription().Weight());
}
void FontWeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetWeight(StyleBuilderConverter::ConvertFontWeight(state, value));
}

 // position-area



const char* PositionArea::GetPropertyName() const {
  return "position-area";
}

const AtomicString& PositionArea::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position-area"));
  return name;
}

const char* PositionArea::GetJSPropertyName() const {
  return "positionArea";
}



void PositionArea::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionArea(ComputedStyleInitialValues::InitialPositionArea());
}

 // text-orientation



const char* TextOrientation::GetPropertyName() const {
  return "text-orientation";
}

const AtomicString& TextOrientation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-orientation"));
  return name;
}

const char* TextOrientation::GetJSPropertyName() const {
  return "textOrientation";
}




 // text-rendering



const char* TextRendering::GetPropertyName() const {
  return "text-rendering";
}

const AtomicString& TextRendering::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-rendering"));
  return name;
}

const char* TextRendering::GetJSPropertyName() const {
  return "textRendering";
}



void TextRendering::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetTextRendering(FontBuilder::InitialTextRendering());
}
void TextRendering::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetTextRendering(state.ParentFontDescription().TextRendering());
}
void TextRendering::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetTextRendering(To<CSSIdentifierValue>(value).ConvertTo<blink::TextRenderingMode>());
}

 // text-spacing-trim



const char* TextSpacingTrim::GetPropertyName() const {
  return "text-spacing-trim";
}

const AtomicString& TextSpacingTrim::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-spacing-trim"));
  return name;
}

const char* TextSpacingTrim::GetJSPropertyName() const {
  return "textSpacingTrim";
}



void TextSpacingTrim::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetTextSpacingTrim(FontBuilder::InitialTextSpacingTrim());
}
void TextSpacingTrim::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetTextSpacingTrim(state.ParentFontDescription().GetTextSpacingTrim());
}
void TextSpacingTrim::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetTextSpacingTrim(To<CSSIdentifierValue>(value).ConvertTo<blink::TextSpacingTrim>());
}

 // -webkit-font-smoothing



const char* WebkitFontSmoothing::GetPropertyName() const {
  return "-webkit-font-smoothing";
}

const AtomicString& WebkitFontSmoothing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-font-smoothing"));
  return name;
}

const char* WebkitFontSmoothing::GetJSPropertyName() const {
  return "webkitFontSmoothing";
}



void WebkitFontSmoothing::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSmoothing(FontBuilder::InitialFontSmoothing());
}
void WebkitFontSmoothing::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetFontSmoothing(state.ParentFontDescription().FontSmoothing());
}
void WebkitFontSmoothing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.GetFontBuilder().SetFontSmoothing(To<CSSIdentifierValue>(value).ConvertTo<blink::FontSmoothingMode>());
}

 // -webkit-locale



const char* WebkitLocale::GetPropertyName() const {
  return "-webkit-locale";
}

const AtomicString& WebkitLocale::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-locale"));
  return name;
}

const char* WebkitLocale::GetJSPropertyName() const {
  return "webkitLocale";
}



void WebkitLocale::ApplyInitial(StyleResolverState& state) const {
  state.GetFontBuilder().SetLocale(FontBuilder::InitialLocale());
}
void WebkitLocale::ApplyInherit(StyleResolverState& state) const {
  state.GetFontBuilder().SetLocale(state.ParentFontDescription().Locale());
}

 // -webkit-text-orientation



const char* WebkitTextOrientation::GetPropertyName() const {
  return "-webkit-text-orientation";
}

const AtomicString& WebkitTextOrientation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-orientation"));
  return name;
}

const char* WebkitTextOrientation::GetJSPropertyName() const {
  return "webkitTextOrientation";
}


const CSSProperty* WebkitTextOrientation::SurrogateFor(WritingDirectionMode) const {
  return &GetCSSPropertyTextOrientation();
}


 // -webkit-writing-mode



const char* WebkitWritingMode::GetPropertyName() const {
  return "-webkit-writing-mode";
}

const AtomicString& WebkitWritingMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-writing-mode"));
  return name;
}

const char* WebkitWritingMode::GetJSPropertyName() const {
  return "webkitWritingMode";
}


const CSSProperty* WebkitWritingMode::SurrogateFor(WritingDirectionMode) const {
  return &GetCSSPropertyWritingMode();
}


 // writing-mode



const char* WritingMode::GetPropertyName() const {
  return "writing-mode";
}

const AtomicString& WritingMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("writing-mode"));
  return name;
}

const char* WritingMode::GetJSPropertyName() const {
  return "writingMode";
}




 // zoom



const char* Zoom::GetPropertyName() const {
  return "zoom";
}

const AtomicString& Zoom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("zoom"));
  return name;
}

const char* Zoom::GetJSPropertyName() const {
  return "zoom";
}




 // -internal-forced-visited-color


CSSExposure InternalForcedVisitedColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalForcedVisitedColor::GetPropertyName() const {
  return "-internal-forced-visited-color";
}

const AtomicString& InternalForcedVisitedColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-forced-visited-color"));
  return name;
}

const char* InternalForcedVisitedColor::GetJSPropertyName() const {
  return "internalForcedVisitedColor";
}


const CSSValue* InternalForcedVisitedColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}


 // -internal-visited-background-color


CSSExposure InternalVisitedBackgroundColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBackgroundColor::GetPropertyName() const {
  return "-internal-visited-background-color";
}

const AtomicString& InternalVisitedBackgroundColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-background-color"));
  return name;
}

const char* InternalVisitedBackgroundColor::GetJSPropertyName() const {
  return "internalVisitedBackgroundColor";
}


const CSSValue* InternalVisitedBackgroundColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}

void InternalVisitedBackgroundColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBackgroundColor(ComputedStyleInitialValues::InitialBackgroundColor());
}

void InternalVisitedBackgroundColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBackgroundColor(state.ParentStyle()->BackgroundColor());
}

void InternalVisitedBackgroundColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedBackgroundColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-border-block-end-color


CSSExposure InternalVisitedBorderBlockEndColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderBlockEndColor::GetPropertyName() const {
  return "-internal-visited-border-block-end-color";
}

const AtomicString& InternalVisitedBorderBlockEndColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-block-end-color"));
  return name;
}

const char* InternalVisitedBorderBlockEndColor::GetJSPropertyName() const {
  return "internalVisitedBorderBlockEndColor";
}


const CSSProperty* InternalVisitedBorderBlockEndColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InternalVisitedBorderBlockEndColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping());
}

bool InternalVisitedBorderBlockEndColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping().Contains(id);
}
const CSSValue* InternalVisitedBorderBlockEndColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}


 // -internal-visited-border-block-start-color


CSSExposure InternalVisitedBorderBlockStartColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderBlockStartColor::GetPropertyName() const {
  return "-internal-visited-border-block-start-color";
}

const AtomicString& InternalVisitedBorderBlockStartColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-block-start-color"));
  return name;
}

const char* InternalVisitedBorderBlockStartColor::GetJSPropertyName() const {
  return "internalVisitedBorderBlockStartColor";
}


const CSSProperty* InternalVisitedBorderBlockStartColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InternalVisitedBorderBlockStartColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping());
}

bool InternalVisitedBorderBlockStartColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping().Contains(id);
}
const CSSValue* InternalVisitedBorderBlockStartColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}


 // -internal-visited-border-bottom-color


CSSExposure InternalVisitedBorderBottomColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderBottomColor::GetPropertyName() const {
  return "-internal-visited-border-bottom-color";
}

const AtomicString& InternalVisitedBorderBottomColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-bottom-color"));
  return name;
}

const char* InternalVisitedBorderBottomColor::GetJSPropertyName() const {
  return "internalVisitedBorderBottomColor";
}


bool InternalVisitedBorderBottomColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping().Contains(id);
}
const CSSProperty& InternalVisitedBorderBottomColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping());
}
const CSSValue* InternalVisitedBorderBottomColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void InternalVisitedBorderBottomColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderBottomColor(StyleColor::CurrentColor());
}

void InternalVisitedBorderBottomColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderBottomColor(state.ParentStyle()->BorderBottomColor());
}

void InternalVisitedBorderBottomColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedBorderBottomColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-border-inline-end-color


CSSExposure InternalVisitedBorderInlineEndColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderInlineEndColor::GetPropertyName() const {
  return "-internal-visited-border-inline-end-color";
}

const AtomicString& InternalVisitedBorderInlineEndColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-inline-end-color"));
  return name;
}

const char* InternalVisitedBorderInlineEndColor::GetJSPropertyName() const {
  return "internalVisitedBorderInlineEndColor";
}


const CSSProperty* InternalVisitedBorderInlineEndColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InternalVisitedBorderInlineEndColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping());
}

bool InternalVisitedBorderInlineEndColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping().Contains(id);
}
const CSSValue* InternalVisitedBorderInlineEndColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}


 // -internal-visited-border-inline-start-color


CSSExposure InternalVisitedBorderInlineStartColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderInlineStartColor::GetPropertyName() const {
  return "-internal-visited-border-inline-start-color";
}

const AtomicString& InternalVisitedBorderInlineStartColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-inline-start-color"));
  return name;
}

const char* InternalVisitedBorderInlineStartColor::GetJSPropertyName() const {
  return "internalVisitedBorderInlineStartColor";
}


const CSSProperty* InternalVisitedBorderInlineStartColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InternalVisitedBorderInlineStartColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping());
}

bool InternalVisitedBorderInlineStartColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalVisitedBorderColorMapping().Contains(id);
}
const CSSValue* InternalVisitedBorderInlineStartColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}


 // -internal-visited-border-left-color


CSSExposure InternalVisitedBorderLeftColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderLeftColor::GetPropertyName() const {
  return "-internal-visited-border-left-color";
}

const AtomicString& InternalVisitedBorderLeftColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-left-color"));
  return name;
}

const char* InternalVisitedBorderLeftColor::GetJSPropertyName() const {
  return "internalVisitedBorderLeftColor";
}


bool InternalVisitedBorderLeftColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping().Contains(id);
}
const CSSProperty& InternalVisitedBorderLeftColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping());
}
const CSSValue* InternalVisitedBorderLeftColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void InternalVisitedBorderLeftColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderLeftColor(StyleColor::CurrentColor());
}

void InternalVisitedBorderLeftColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderLeftColor(state.ParentStyle()->BorderLeftColor());
}

void InternalVisitedBorderLeftColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedBorderLeftColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-border-right-color


CSSExposure InternalVisitedBorderRightColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderRightColor::GetPropertyName() const {
  return "-internal-visited-border-right-color";
}

const AtomicString& InternalVisitedBorderRightColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-right-color"));
  return name;
}

const char* InternalVisitedBorderRightColor::GetJSPropertyName() const {
  return "internalVisitedBorderRightColor";
}


bool InternalVisitedBorderRightColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping().Contains(id);
}
const CSSProperty& InternalVisitedBorderRightColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping());
}
const CSSValue* InternalVisitedBorderRightColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void InternalVisitedBorderRightColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderRightColor(StyleColor::CurrentColor());
}

void InternalVisitedBorderRightColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderRightColor(state.ParentStyle()->BorderRightColor());
}

void InternalVisitedBorderRightColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedBorderRightColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-border-top-color


CSSExposure InternalVisitedBorderTopColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedBorderTopColor::GetPropertyName() const {
  return "-internal-visited-border-top-color";
}

const AtomicString& InternalVisitedBorderTopColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-border-top-color"));
  return name;
}

const char* InternalVisitedBorderTopColor::GetJSPropertyName() const {
  return "internalVisitedBorderTopColor";
}


bool InternalVisitedBorderTopColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping().Contains(id);
}
const CSSProperty& InternalVisitedBorderTopColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalVisitedBorderColorMapping());
}
const CSSValue* InternalVisitedBorderTopColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void InternalVisitedBorderTopColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderTopColor(StyleColor::CurrentColor());
}

void InternalVisitedBorderTopColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedBorderTopColor(state.ParentStyle()->BorderTopColor());
}

void InternalVisitedBorderTopColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedBorderTopColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-caret-color


CSSExposure InternalVisitedCaretColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedCaretColor::GetPropertyName() const {
  return "-internal-visited-caret-color";
}

const AtomicString& InternalVisitedCaretColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-caret-color"));
  return name;
}

const char* InternalVisitedCaretColor::GetJSPropertyName() const {
  return "internalVisitedCaretColor";
}



void InternalVisitedCaretColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedCaretColor(StyleAutoColor::AutoColor());
}

void InternalVisitedCaretColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedCaretColor(state.ParentStyle()->CaretColor());
}

void InternalVisitedCaretColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedCaretColor(StyleBuilderConverter::ConvertStyleAutoColor(state, value, true));
}

 // -internal-visited-column-rule-color


CSSExposure InternalVisitedColumnRuleColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedColumnRuleColor::GetPropertyName() const {
  return "-internal-visited-column-rule-color";
}

const AtomicString& InternalVisitedColumnRuleColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-column-rule-color"));
  return name;
}

const char* InternalVisitedColumnRuleColor::GetJSPropertyName() const {
  return "internalVisitedColumnRuleColor";
}


const CSSValue* InternalVisitedColumnRuleColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void InternalVisitedColumnRuleColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedColumnRuleColor(ComputedStyleInitialValues::InitialInternalVisitedColumnRuleColor());
}
void InternalVisitedColumnRuleColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedColumnRuleColor(state.ParentStyle()->InternalVisitedColumnRuleColor());
}
void InternalVisitedColumnRuleColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedColumnRuleColor(StyleBuilderConverter::ConvertGapDecorationColorDataList(state, value));
}

 // -internal-visited-fill


CSSExposure InternalVisitedFill::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedFill::GetPropertyName() const {
  return "-internal-visited-fill";
}

const AtomicString& InternalVisitedFill::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-fill"));
  return name;
}

const char* InternalVisitedFill::GetJSPropertyName() const {
  return "internalVisitedFill";
}


const CSSValue* InternalVisitedFill::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeSVGPaint(stream, context, local_context);
}

void InternalVisitedFill::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedFillPaint(ComputedStyleInitialValues::InitialFillPaint());
}

void InternalVisitedFill::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedFillPaint(state.ParentStyle()->FillPaint());
}

void InternalVisitedFill::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedFillPaint(StyleBuilderConverter::ConvertSVGPaint(state, value, true));
}

 // -internal-visited-outline-color


CSSExposure InternalVisitedOutlineColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedOutlineColor::GetPropertyName() const {
  return "-internal-visited-outline-color";
}

const AtomicString& InternalVisitedOutlineColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-outline-color"));
  return name;
}

const char* InternalVisitedOutlineColor::GetJSPropertyName() const {
  return "internalVisitedOutlineColor";
}



void InternalVisitedOutlineColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedOutlineColor(StyleColor::CurrentColor());
}

void InternalVisitedOutlineColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedOutlineColor(state.ParentStyle()->OutlineColor());
}

void InternalVisitedOutlineColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedOutlineColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-stroke


CSSExposure InternalVisitedStroke::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedStroke::GetPropertyName() const {
  return "-internal-visited-stroke";
}

const AtomicString& InternalVisitedStroke::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-stroke"));
  return name;
}

const char* InternalVisitedStroke::GetJSPropertyName() const {
  return "internalVisitedStroke";
}


const CSSValue* InternalVisitedStroke::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeSVGPaint(stream, context, local_context);
}

void InternalVisitedStroke::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedStrokePaint(ComputedStyleInitialValues::InitialStrokePaint());
}

void InternalVisitedStroke::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedStrokePaint(state.ParentStyle()->StrokePaint());
}

void InternalVisitedStroke::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedStrokePaint(StyleBuilderConverter::ConvertSVGPaint(state, value, true));
}

 // -internal-visited-text-decoration-color


CSSExposure InternalVisitedTextDecorationColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedTextDecorationColor::GetPropertyName() const {
  return "-internal-visited-text-decoration-color";
}

const AtomicString& InternalVisitedTextDecorationColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-text-decoration-color"));
  return name;
}

const char* InternalVisitedTextDecorationColor::GetJSPropertyName() const {
  return "internalVisitedTextDecorationColor";
}


const CSSValue* InternalVisitedTextDecorationColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void InternalVisitedTextDecorationColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextDecorationColor(StyleColor::CurrentColor());
}

void InternalVisitedTextDecorationColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextDecorationColor(state.ParentStyle()->TextDecorationColor());
}

void InternalVisitedTextDecorationColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedTextDecorationColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-text-emphasis-color


CSSExposure InternalVisitedTextEmphasisColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedTextEmphasisColor::GetPropertyName() const {
  return "-internal-visited-text-emphasis-color";
}

const AtomicString& InternalVisitedTextEmphasisColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-text-emphasis-color"));
  return name;
}

const char* InternalVisitedTextEmphasisColor::GetJSPropertyName() const {
  return "internalVisitedTextEmphasisColor";
}


const CSSValue* InternalVisitedTextEmphasisColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void InternalVisitedTextEmphasisColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextEmphasisColor(StyleColor::CurrentColor());
}

void InternalVisitedTextEmphasisColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextEmphasisColor(state.ParentStyle()->TextEmphasisColor());
}

void InternalVisitedTextEmphasisColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedTextEmphasisColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-text-fill-color


CSSExposure InternalVisitedTextFillColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedTextFillColor::GetPropertyName() const {
  return "-internal-visited-text-fill-color";
}

const AtomicString& InternalVisitedTextFillColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-text-fill-color"));
  return name;
}

const char* InternalVisitedTextFillColor::GetJSPropertyName() const {
  return "internalVisitedTextFillColor";
}


const CSSValue* InternalVisitedTextFillColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void InternalVisitedTextFillColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextFillColor(StyleColor::CurrentColor());
}

void InternalVisitedTextFillColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextFillColor(state.ParentStyle()->TextFillColor());
}

void InternalVisitedTextFillColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedTextFillColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // -internal-visited-text-stroke-color


CSSExposure InternalVisitedTextStrokeColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalVisitedTextStrokeColor::GetPropertyName() const {
  return "-internal-visited-text-stroke-color";
}

const AtomicString& InternalVisitedTextStrokeColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-visited-text-stroke-color"));
  return name;
}

const char* InternalVisitedTextStrokeColor::GetJSPropertyName() const {
  return "internalVisitedTextStrokeColor";
}


const CSSValue* InternalVisitedTextStrokeColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void InternalVisitedTextStrokeColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextStrokeColor(StyleColor::CurrentColor());
}

void InternalVisitedTextStrokeColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalVisitedTextStrokeColor(state.ParentStyle()->TextStrokeColor());
}

void InternalVisitedTextStrokeColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalVisitedTextStrokeColor(StyleBuilderConverter::ConvertStyleColor(state, value, true));
}

 // accent-color



const char* AccentColor::GetPropertyName() const {
  return "accent-color";
}

const AtomicString& AccentColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("accent-color"));
  return name;
}

const char* AccentColor::GetJSPropertyName() const {
  return "accentColor";
}



void AccentColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAccentColor(ComputedStyleInitialValues::InitialAccentColor());
}
void AccentColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAccentColor(state.ParentStyle()->AccentColor());
}
void AccentColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAccentColor(StyleBuilderConverter::ConvertStyleAutoColor(state, value));
}

 // additive-symbols



const char* AdditiveSymbols::GetPropertyName() const {
  return "additive-symbols";
}

const AtomicString& AdditiveSymbols::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("additive-symbols"));
  return name;
}

const char* AdditiveSymbols::GetJSPropertyName() const {
  return "additiveSymbols";
}




 // align-content



const char* AlignContent::GetPropertyName() const {
  return "align-content";
}

const AtomicString& AlignContent::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("align-content"));
  return name;
}

const char* AlignContent::GetJSPropertyName() const {
  return "alignContent";
}



void AlignContent::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignContent(ComputedStyleInitialValues::InitialAlignContent());
}
void AlignContent::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignContent(state.ParentStyle()->AlignContent());
}
void AlignContent::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAlignContent(StyleBuilderConverter::ConvertContentAlignmentData(state, value));
}

 // align-items



const char* AlignItems::GetPropertyName() const {
  return "align-items";
}

const AtomicString& AlignItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("align-items"));
  return name;
}

const char* AlignItems::GetJSPropertyName() const {
  return "alignItems";
}



void AlignItems::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignItems(ComputedStyleInitialValues::InitialAlignItems());
}
void AlignItems::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignItems(state.ParentStyle()->AlignItems());
}
void AlignItems::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAlignItems(StyleBuilderConverter::ConvertSelfOrDefaultAlignmentData(state, value));
}

 // align-self



const char* AlignSelf::GetPropertyName() const {
  return "align-self";
}

const AtomicString& AlignSelf::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("align-self"));
  return name;
}

const char* AlignSelf::GetJSPropertyName() const {
  return "alignSelf";
}



void AlignSelf::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignSelf(ComputedStyleInitialValues::InitialAlignSelf());
}
void AlignSelf::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignSelf(state.ParentStyle()->AlignSelf());
}
void AlignSelf::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAlignSelf(StyleBuilderConverter::ConvertSelfOrDefaultAlignmentData(state, value));
}

 // alignment-baseline



const char* AlignmentBaseline::GetPropertyName() const {
  return "alignment-baseline";
}

const AtomicString& AlignmentBaseline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("alignment-baseline"));
  return name;
}

const char* AlignmentBaseline::GetJSPropertyName() const {
  return "alignmentBaseline";
}



void AlignmentBaseline::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignmentBaseline(ComputedStyleInitialValues::InitialAlignmentBaseline());
}
void AlignmentBaseline::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignmentBaseline(state.ParentStyle()->AlignmentBaseline());
}
void AlignmentBaseline::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAlignmentBaseline(To<CSSIdentifierValue>(value).ConvertTo<blink::EAlignmentBaseline>());
}

 // all



const char* All::GetPropertyName() const {
  return "all";
}

const AtomicString& All::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("all"));
  return name;
}

const char* All::GetJSPropertyName() const {
  return "all";
}



void All::ApplyInitial(StyleResolverState& state) const {
  // Intentionally empty.
}
void All::ApplyInherit(StyleResolverState& state) const {
  // Intentionally empty.
}
void All::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  // Intentionally empty.
}

 // anchor-name



const char* AnchorName::GetPropertyName() const {
  return "anchor-name";
}

const AtomicString& AnchorName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("anchor-name"));
  return name;
}

const char* AnchorName::GetJSPropertyName() const {
  return "anchorName";
}



void AnchorName::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAnchorName(ComputedStyleInitialValues::InitialAnchorName());
}
void AnchorName::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAnchorName(state.ParentStyle()->AnchorName());
}
void AnchorName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAnchorName(StyleBuilderConverter::ConvertAnchorName(state, value));
}

 // anchor-scope



const char* AnchorScope::GetPropertyName() const {
  return "anchor-scope";
}

const AtomicString& AnchorScope::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("anchor-scope"));
  return name;
}

const char* AnchorScope::GetJSPropertyName() const {
  return "anchorScope";
}


const CSSValue* AnchorScope::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeNameScope(stream, context, local_context);
}

void AnchorScope::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAnchorScope(ComputedStyleInitialValues::InitialAnchorScope());
}
void AnchorScope::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAnchorScope(state.ParentStyle()->AnchorScope());
}
void AnchorScope::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAnchorScope(StyleBuilderConverter::ConvertAnchorScope(state, value));
}

 // animation-composition



const char* AnimationComposition::GetPropertyName() const {
  return "animation-composition";
}

const AtomicString& AnimationComposition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-composition"));
  return name;
}

const char* AnimationComposition::GetJSPropertyName() const {
  return "animationComposition";
}



void AnimationComposition::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.CompositionList().clear();
  data.CompositionList().push_back(CSSAnimationData::InitialComposition());
}

void AnimationComposition::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().CompositionList() = parent_data->CompositionList();
}

void AnimationComposition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.CompositionList().clear();
  data.CompositionList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.CompositionList().push_back(CSSToStyleMap::MapAnimationComposition(state, item));
  }
}

 // animation-delay



const char* AnimationDelay::GetPropertyName() const {
  return "animation-delay";
}

const AtomicString& AnimationDelay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-delay"));
  return name;
}

const char* AnimationDelay::GetJSPropertyName() const {
  return "animationDelay";
}



void AnimationDelay::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.DelayStartList().clear();
  data.DelayStartList().push_back(CSSAnimationData::InitialDelayStart());
}

void AnimationDelay::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().DelayStartList() = parent_data->DelayStartList();
}

void AnimationDelay::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.DelayStartList().clear();
  data.DelayStartList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.DelayStartList().push_back(CSSToStyleMap::MapAnimationDelayStart(state, item));
  }
}

 // animation-direction



const char* AnimationDirection::GetPropertyName() const {
  return "animation-direction";
}

const AtomicString& AnimationDirection::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-direction"));
  return name;
}

const char* AnimationDirection::GetJSPropertyName() const {
  return "animationDirection";
}



void AnimationDirection::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.DirectionList().clear();
  data.DirectionList().push_back(CSSAnimationData::InitialDirection());
}

void AnimationDirection::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().DirectionList() = parent_data->DirectionList();
}

void AnimationDirection::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.DirectionList().clear();
  data.DirectionList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.DirectionList().push_back(CSSToStyleMap::MapAnimationDirection(state, item));
  }
}

 // animation-duration



const char* AnimationDuration::GetPropertyName() const {
  return "animation-duration";
}

const AtomicString& AnimationDuration::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-duration"));
  return name;
}

const char* AnimationDuration::GetJSPropertyName() const {
  return "animationDuration";
}



void AnimationDuration::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.DurationList().clear();
  data.DurationList().push_back(CSSAnimationData::InitialDuration());
}

void AnimationDuration::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().DurationList() = parent_data->DurationList();
}

void AnimationDuration::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.DurationList().clear();
  data.DurationList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.DurationList().push_back(CSSToStyleMap::MapAnimationDuration(state, item));
  }
}

 // animation-fill-mode



const char* AnimationFillMode::GetPropertyName() const {
  return "animation-fill-mode";
}

const AtomicString& AnimationFillMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-fill-mode"));
  return name;
}

const char* AnimationFillMode::GetJSPropertyName() const {
  return "animationFillMode";
}



void AnimationFillMode::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.FillModeList().clear();
  data.FillModeList().push_back(CSSAnimationData::InitialFillMode());
}

void AnimationFillMode::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().FillModeList() = parent_data->FillModeList();
}

void AnimationFillMode::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.FillModeList().clear();
  data.FillModeList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.FillModeList().push_back(CSSToStyleMap::MapAnimationFillMode(state, item));
  }
}

 // animation-iteration-count



const char* AnimationIterationCount::GetPropertyName() const {
  return "animation-iteration-count";
}

const AtomicString& AnimationIterationCount::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-iteration-count"));
  return name;
}

const char* AnimationIterationCount::GetJSPropertyName() const {
  return "animationIterationCount";
}



void AnimationIterationCount::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.IterationCountList().clear();
  data.IterationCountList().push_back(CSSAnimationData::InitialIterationCount());
}

void AnimationIterationCount::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().IterationCountList() = parent_data->IterationCountList();
}

void AnimationIterationCount::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.IterationCountList().clear();
  data.IterationCountList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.IterationCountList().push_back(CSSToStyleMap::MapAnimationIterationCount(state, item));
  }
}

 // animation-name



const char* AnimationName::GetPropertyName() const {
  return "animation-name";
}

const AtomicString& AnimationName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-name"));
  return name;
}

const char* AnimationName::GetJSPropertyName() const {
  return "animationName";
}



void AnimationName::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.NameList().clear();
  data.NameList().push_back(CSSAnimationData::InitialName());
}

void AnimationName::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().NameList() = parent_data->NameList();
}

void AnimationName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.NameList().clear();
  data.NameList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.NameList().push_back(CSSToStyleMap::MapAnimationName(state, item));
  }
}

 // animation-play-state



const char* AnimationPlayState::GetPropertyName() const {
  return "animation-play-state";
}

const AtomicString& AnimationPlayState::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-play-state"));
  return name;
}

const char* AnimationPlayState::GetJSPropertyName() const {
  return "animationPlayState";
}



void AnimationPlayState::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.PlayStateList().clear();
  data.PlayStateList().push_back(CSSAnimationData::InitialPlayState());
}

void AnimationPlayState::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().PlayStateList() = parent_data->PlayStateList();
}

void AnimationPlayState::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.PlayStateList().clear();
  data.PlayStateList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.PlayStateList().push_back(CSSToStyleMap::MapAnimationPlayState(state, item));
  }
}

 // animation-range-end



const char* AnimationRangeEnd::GetPropertyName() const {
  return "animation-range-end";
}

const AtomicString& AnimationRangeEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-range-end"));
  return name;
}

const char* AnimationRangeEnd::GetJSPropertyName() const {
  return "animationRangeEnd";
}



void AnimationRangeEnd::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.RangeEndList().clear();
  data.RangeEndList().push_back(CSSAnimationData::InitialRangeEnd());
}

void AnimationRangeEnd::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().RangeEndList() = parent_data->RangeEndList();
}

void AnimationRangeEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.RangeEndList().clear();
  data.RangeEndList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.RangeEndList().push_back(CSSToStyleMap::MapAnimationRangeEnd(state, item));
  }
}

 // animation-range-start



const char* AnimationRangeStart::GetPropertyName() const {
  return "animation-range-start";
}

const AtomicString& AnimationRangeStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-range-start"));
  return name;
}

const char* AnimationRangeStart::GetJSPropertyName() const {
  return "animationRangeStart";
}



void AnimationRangeStart::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.RangeStartList().clear();
  data.RangeStartList().push_back(CSSAnimationData::InitialRangeStart());
}

void AnimationRangeStart::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().RangeStartList() = parent_data->RangeStartList();
}

void AnimationRangeStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.RangeStartList().clear();
  data.RangeStartList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.RangeStartList().push_back(CSSToStyleMap::MapAnimationRangeStart(state, item));
  }
}

 // animation-timeline



const char* AnimationTimeline::GetPropertyName() const {
  return "animation-timeline";
}

const AtomicString& AnimationTimeline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-timeline"));
  return name;
}

const char* AnimationTimeline::GetJSPropertyName() const {
  return "animationTimeline";
}



void AnimationTimeline::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineList().clear();
  data.TimelineList().push_back(CSSAnimationData::InitialTimeline());
}

void AnimationTimeline::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineList() = parent_data->TimelineList();
}

void AnimationTimeline::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineList().clear();
  data.TimelineList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineList().push_back(CSSToStyleMap::MapAnimationTimeline(state, item));
  }
}

 // animation-timing-function



const char* AnimationTimingFunction::GetPropertyName() const {
  return "animation-timing-function";
}

const AtomicString& AnimationTimingFunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-timing-function"));
  return name;
}

const char* AnimationTimingFunction::GetJSPropertyName() const {
  return "animationTimingFunction";
}



void AnimationTimingFunction::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimingFunctionList().clear();
  data.TimingFunctionList().push_back(CSSAnimationData::InitialTimingFunction());
}

void AnimationTimingFunction::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimingFunctionList() = parent_data->TimingFunctionList();
}

void AnimationTimingFunction::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimingFunctionList().clear();
  data.TimingFunctionList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimingFunctionList().push_back(CSSToStyleMap::MapAnimationTimingFunction(state, item));
  }
}

 // animation-trigger


CSSExposure AnimationTrigger::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::AnimationTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* AnimationTrigger::GetPropertyName() const {
  return "animation-trigger";
}

const AtomicString& AnimationTrigger::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("animation-trigger"));
  return name;
}

const char* AnimationTrigger::GetJSPropertyName() const {
  return "animationTrigger";
}



void AnimationTrigger::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TriggerAttachmentsList().clear();
  data.TriggerAttachmentsList().push_back(CSSAnimationData::InitialTriggerAttachments());
}

void AnimationTrigger::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TriggerAttachmentsList() = parent_data->TriggerAttachmentsList();
}

void AnimationTrigger::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TriggerAttachmentsList().clear();
  data.TriggerAttachmentsList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TriggerAttachmentsList().push_back(CSSToStyleMap::MapAnimationTriggerAttachments(state, item));
  }
}

 // app-region



const char* AppRegion::GetPropertyName() const {
  return "app-region";
}

const AtomicString& AppRegion::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("app-region"));
  return name;
}

const char* AppRegion::GetJSPropertyName() const {
  return "appRegion";
}




 // ascent-override



const char* AscentOverride::GetPropertyName() const {
  return "ascent-override";
}

const AtomicString& AscentOverride::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("ascent-override"));
  return name;
}

const char* AscentOverride::GetJSPropertyName() const {
  return "ascentOverride";
}




 // aspect-ratio



const char* AspectRatio::GetPropertyName() const {
  return "aspect-ratio";
}

const AtomicString& AspectRatio::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("aspect-ratio"));
  return name;
}

const char* AspectRatio::GetJSPropertyName() const {
  return "aspectRatio";
}



void AspectRatio::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAspectRatio(ComputedStyleInitialValues::InitialAspectRatio());
}
void AspectRatio::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAspectRatio(state.ParentStyle()->AspectRatio());
}
void AspectRatio::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAspectRatio(StyleBuilderConverter::ConvertAspectRatio(state, value));
}

 // backdrop-filter



const char* BackdropFilter::GetPropertyName() const {
  return "backdrop-filter";
}

const AtomicString& BackdropFilter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("backdrop-filter"));
  return name;
}

const char* BackdropFilter::GetJSPropertyName() const {
  return "backdropFilter";
}


const CSSValue* BackdropFilter::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFilterFunctionList(stream, context, local_context);
}

void BackdropFilter::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBackdropFilter(ComputedStyleInitialValues::InitialBackdropFilter());
}
void BackdropFilter::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBackdropFilter(state.ParentStyle()->BackdropFilter());
}

 // backface-visibility



const char* BackfaceVisibility::GetPropertyName() const {
  return "backface-visibility";
}

const AtomicString& BackfaceVisibility::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("backface-visibility"));
  return name;
}

const char* BackfaceVisibility::GetJSPropertyName() const {
  return "backfaceVisibility";
}



void BackfaceVisibility::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBackfaceVisibility(ComputedStyleInitialValues::InitialBackfaceVisibility());
}
void BackfaceVisibility::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBackfaceVisibility(state.ParentStyle()->BackfaceVisibility());
}
void BackfaceVisibility::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBackfaceVisibility(To<CSSIdentifierValue>(value).ConvertTo<blink::EBackfaceVisibility>());
}

 // background-attachment



const char* BackgroundAttachment::GetPropertyName() const {
  return "background-attachment";
}

const AtomicString& BackgroundAttachment::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-attachment"));
  return name;
}

const char* BackgroundAttachment::GetJSPropertyName() const {
  return "backgroundAttachment";
}



void BackgroundAttachment::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetAttachment(FillLayer::InitialFillAttachment(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearAttachment();
}

void BackgroundAttachment::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsAttachmentSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetAttachment(curr_parent->Attachment());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearAttachment();
    curr_child = curr_child->Next();
  }
}

void BackgroundAttachment::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillAttachment(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillAttachment(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearAttachment();
    curr_child = curr_child->Next();
  }
}

 // background-blend-mode



const char* BackgroundBlendMode::GetPropertyName() const {
  return "background-blend-mode";
}

const AtomicString& BackgroundBlendMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-blend-mode"));
  return name;
}

const char* BackgroundBlendMode::GetJSPropertyName() const {
  return "backgroundBlendMode";
}



void BackgroundBlendMode::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetBlendMode(FillLayer::InitialFillBlendMode(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearBlendMode();
}

void BackgroundBlendMode::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsBlendModeSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetBlendMode(curr_parent->GetBlendMode());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearBlendMode();
    curr_child = curr_child->Next();
  }
}

void BackgroundBlendMode::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillBlendMode(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillBlendMode(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearBlendMode();
    curr_child = curr_child->Next();
  }
}

 // background-clip



const char* BackgroundClip::GetPropertyName() const {
  return "background-clip";
}

const AtomicString& BackgroundClip::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-clip"));
  return name;
}

const char* BackgroundClip::GetJSPropertyName() const {
  return "backgroundClip";
}



void BackgroundClip::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetClip(FillLayer::InitialFillClip(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearClip();
}

void BackgroundClip::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsClipSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetClip(curr_parent->Clip());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearClip();
    curr_child = curr_child->Next();
  }
}


 // background-color



const char* BackgroundColor::GetPropertyName() const {
  return "background-color";
}

const AtomicString& BackgroundColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-color"));
  return name;
}

const char* BackgroundColor::GetJSPropertyName() const {
  return "backgroundColor";
}


const CSSValue* BackgroundColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}

void BackgroundColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBackgroundColor(ComputedStyleInitialValues::InitialBackgroundColor());
}

void BackgroundColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBackgroundColor(state.ParentStyle()->BackgroundColor());
}

void BackgroundColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBackgroundColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // background-image



const char* BackgroundImage::GetPropertyName() const {
  return "background-image";
}

const AtomicString& BackgroundImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-image"));
  return name;
}

const char* BackgroundImage::GetJSPropertyName() const {
  return "backgroundImage";
}



void BackgroundImage::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetImage(FillLayer::InitialFillImage(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearImage();
}

void BackgroundImage::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsImageSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetImage(curr_parent->GetImage());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearImage();
    curr_child = curr_child->Next();
  }
}

void BackgroundImage::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillImage(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillImage(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearImage();
    curr_child = curr_child->Next();
  }
}

 // background-origin



const char* BackgroundOrigin::GetPropertyName() const {
  return "background-origin";
}

const AtomicString& BackgroundOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-origin"));
  return name;
}

const char* BackgroundOrigin::GetJSPropertyName() const {
  return "backgroundOrigin";
}



void BackgroundOrigin::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetOrigin(FillLayer::InitialFillOrigin(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearOrigin();
}

void BackgroundOrigin::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsOriginSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetOrigin(curr_parent->Origin());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearOrigin();
    curr_child = curr_child->Next();
  }
}

void BackgroundOrigin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillOrigin(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillOrigin(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearOrigin();
    curr_child = curr_child->Next();
  }
}

 // background-position-x



const char* BackgroundPositionX::GetPropertyName() const {
  return "background-position-x";
}

const AtomicString& BackgroundPositionX::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-position-x"));
  return name;
}

const char* BackgroundPositionX::GetJSPropertyName() const {
  return "backgroundPositionX";
}



void BackgroundPositionX::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetPositionX(FillLayer::InitialFillPositionX(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearPositionX();
}

void BackgroundPositionX::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsPositionXSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetPositionX(curr_parent->PositionX());
    if (curr_parent->IsBackgroundXOriginSet())
      curr_child->SetBackgroundXOrigin(curr_parent->BackgroundXOrigin());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearPositionX();
    curr_child = curr_child->Next();
  }
}

void BackgroundPositionX::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillPositionX(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillPositionX(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearPositionX();
    curr_child = curr_child->Next();
  }
}

 // background-position-y



const char* BackgroundPositionY::GetPropertyName() const {
  return "background-position-y";
}

const AtomicString& BackgroundPositionY::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-position-y"));
  return name;
}

const char* BackgroundPositionY::GetJSPropertyName() const {
  return "backgroundPositionY";
}



void BackgroundPositionY::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetPositionY(FillLayer::InitialFillPositionY(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearPositionY();
}

void BackgroundPositionY::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsPositionYSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetPositionY(curr_parent->PositionY());
    if (curr_parent->IsBackgroundYOriginSet())
      curr_child->SetBackgroundYOrigin(curr_parent->BackgroundYOrigin());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearPositionY();
    curr_child = curr_child->Next();
  }
}

void BackgroundPositionY::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillPositionY(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillPositionY(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearPositionY();
    curr_child = curr_child->Next();
  }
}

 // background-repeat



const char* BackgroundRepeat::GetPropertyName() const {
  return "background-repeat";
}

const AtomicString& BackgroundRepeat::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-repeat"));
  return name;
}

const char* BackgroundRepeat::GetJSPropertyName() const {
  return "backgroundRepeat";
}



void BackgroundRepeat::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetRepeat(FillLayer::InitialFillRepeat(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearRepeat();
}

void BackgroundRepeat::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsRepeatSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetRepeat(curr_parent->Repeat());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearRepeat();
    curr_child = curr_child->Next();
  }
}

void BackgroundRepeat::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillRepeat(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillRepeat(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearRepeat();
    curr_child = curr_child->Next();
  }
}

 // background-size



const char* BackgroundSize::GetPropertyName() const {
  return "background-size";
}

const AtomicString& BackgroundSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("background-size"));
  return name;
}

const char* BackgroundSize::GetJSPropertyName() const {
  return "backgroundSize";
}


const CSSValue* BackgroundSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBackgroundSize(stream, context, local_context);
}

void BackgroundSize::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  curr_child->SetSize(FillLayer::InitialFillSize(EFillLayerType::kBackground));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearSize();
}

void BackgroundSize::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->BackgroundLayers();
  while (curr_parent && curr_parent->IsSizeSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetSize(curr_parent->Size());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearSize();
    curr_child = curr_child->Next();
  }
}

void BackgroundSize::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessBackgroundLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillSize(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillSize(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearSize();
    curr_child = curr_child->Next();
  }
}

 // base-palette



const char* BasePalette::GetPropertyName() const {
  return "base-palette";
}

const AtomicString& BasePalette::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("base-palette"));
  return name;
}

const char* BasePalette::GetJSPropertyName() const {
  return "basePalette";
}




 // base-url


CSSExposure BaseUrl::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* BaseUrl::GetPropertyName() const {
  return "base-url";
}

const AtomicString& BaseUrl::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("base-url"));
  return name;
}

const char* BaseUrl::GetJSPropertyName() const {
  return "baseUrl";
}




 // baseline-shift



const char* BaselineShift::GetPropertyName() const {
  return "baseline-shift";
}

const AtomicString& BaselineShift::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("baseline-shift"));
  return name;
}

const char* BaselineShift::GetJSPropertyName() const {
  return "baselineShift";
}



void BaselineShift::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBaselineShift(ComputedStyleInitialValues::InitialBaselineShift());
}

 // baseline-source



const char* BaselineSource::GetPropertyName() const {
  return "baseline-source";
}

const AtomicString& BaselineSource::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("baseline-source"));
  return name;
}

const char* BaselineSource::GetJSPropertyName() const {
  return "baselineSource";
}



void BaselineSource::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBaselineSource(ComputedStyleInitialValues::InitialBaselineSource());
}
void BaselineSource::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBaselineSource(state.ParentStyle()->BaselineSource());
}
void BaselineSource::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBaselineSource(To<CSSIdentifierValue>(value).ConvertTo<blink::EBaselineSource>());
}

 // block-ellipsis


CSSExposure BlockEllipsis::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSLineClampEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* BlockEllipsis::GetPropertyName() const {
  return "block-ellipsis";
}

const AtomicString& BlockEllipsis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("block-ellipsis"));
  return name;
}

const char* BlockEllipsis::GetJSPropertyName() const {
  return "blockEllipsis";
}



void BlockEllipsis::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBlockEllipsis(ComputedStyleInitialValues::InitialBlockEllipsis());
}
void BlockEllipsis::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBlockEllipsis(state.ParentStyle()->BlockEllipsis());
}
void BlockEllipsis::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBlockEllipsis(To<CSSIdentifierValue>(value).ConvertTo<blink::EBlockEllipsis>());
}

 // block-size



const char* BlockSize::GetPropertyName() const {
  return "block-size";
}

const AtomicString& BlockSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("block-size"));
  return name;
}

const char* BlockSize::GetJSPropertyName() const {
  return "blockSize";
}


const CSSProperty* BlockSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BlockSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlock(writing_direction,
      CSSDirectionAwareResolver::PhysicalSizeMapping());
}

bool BlockSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalSizeMapping().Contains(id);
}
const CSSValue* BlockSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeWidthOrHeight(stream, context, local_context);
}


 // border-block-end-color



const char* BorderBlockEndColor::GetPropertyName() const {
  return "border-block-end-color";
}

const AtomicString& BorderBlockEndColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-end-color"));
  return name;
}

const char* BorderBlockEndColor::GetJSPropertyName() const {
  return "borderBlockEndColor";
}


const CSSProperty* BorderBlockEndColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockEndColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderColorMapping());
}

bool BorderBlockEndColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderColorMapping().Contains(id);
}
const CSSValue* BorderBlockEndColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}


 // border-block-end-style



const char* BorderBlockEndStyle::GetPropertyName() const {
  return "border-block-end-style";
}

const AtomicString& BorderBlockEndStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-end-style"));
  return name;
}

const char* BorderBlockEndStyle::GetJSPropertyName() const {
  return "borderBlockEndStyle";
}


const CSSProperty* BorderBlockEndStyle::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockEndStyle::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderStyleMapping());
}

bool BorderBlockEndStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderStyleMapping().Contains(id);
}


 // border-block-end-width



const char* BorderBlockEndWidth::GetPropertyName() const {
  return "border-block-end-width";
}

const AtomicString& BorderBlockEndWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-end-width"));
  return name;
}

const char* BorderBlockEndWidth::GetJSPropertyName() const {
  return "borderBlockEndWidth";
}


const CSSProperty* BorderBlockEndWidth::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockEndWidth::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderWidthMapping());
}

bool BorderBlockEndWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderWidthMapping().Contains(id);
}


 // border-block-start-color



const char* BorderBlockStartColor::GetPropertyName() const {
  return "border-block-start-color";
}

const AtomicString& BorderBlockStartColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-start-color"));
  return name;
}

const char* BorderBlockStartColor::GetJSPropertyName() const {
  return "borderBlockStartColor";
}


const CSSProperty* BorderBlockStartColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockStartColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderColorMapping());
}

bool BorderBlockStartColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderColorMapping().Contains(id);
}
const CSSValue* BorderBlockStartColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}


 // border-block-start-style



const char* BorderBlockStartStyle::GetPropertyName() const {
  return "border-block-start-style";
}

const AtomicString& BorderBlockStartStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-start-style"));
  return name;
}

const char* BorderBlockStartStyle::GetJSPropertyName() const {
  return "borderBlockStartStyle";
}


const CSSProperty* BorderBlockStartStyle::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockStartStyle::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderStyleMapping());
}

bool BorderBlockStartStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderStyleMapping().Contains(id);
}


 // border-block-start-width



const char* BorderBlockStartWidth::GetPropertyName() const {
  return "border-block-start-width";
}

const AtomicString& BorderBlockStartWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-block-start-width"));
  return name;
}

const char* BorderBlockStartWidth::GetJSPropertyName() const {
  return "borderBlockStartWidth";
}


const CSSProperty* BorderBlockStartWidth::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderBlockStartWidth::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderWidthMapping());
}

bool BorderBlockStartWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderWidthMapping().Contains(id);
}


 // border-bottom-color



const char* BorderBottomColor::GetPropertyName() const {
  return "border-bottom-color";
}

const AtomicString& BorderBottomColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-bottom-color"));
  return name;
}

const char* BorderBottomColor::GetJSPropertyName() const {
  return "borderBottomColor";
}


bool BorderBottomColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderColorMapping().Contains(id);
}
const CSSProperty& BorderBottomColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderColorMapping());
}
const CSSValue* BorderBottomColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void BorderBottomColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderBottomColor(StyleColor::CurrentColor());
}

void BorderBottomColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderBottomColor(state.ParentStyle()->BorderBottomColor());
}

void BorderBottomColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderBottomColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // border-bottom-left-radius



const char* BorderBottomLeftRadius::GetPropertyName() const {
  return "border-bottom-left-radius";
}

const AtomicString& BorderBottomLeftRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-bottom-left-radius"));
  return name;
}

const char* BorderBottomLeftRadius::GetJSPropertyName() const {
  return "borderBottomLeftRadius";
}


bool BorderBottomLeftRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderRadiusMapping().Contains(id);
}
const CSSProperty& BorderBottomLeftRadius::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottomLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderRadiusMapping());
}
const CSSValue* BorderBottomLeftRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}

void BorderBottomLeftRadius::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderBottomLeftRadius(ComputedStyleInitialValues::InitialBorderBottomLeftRadius());
}
void BorderBottomLeftRadius::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetBorderBottomLeftRadius(state.ParentStyle()->BorderBottomLeftRadius());
}
void BorderBottomLeftRadius::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderBottomLeftRadius(StyleBuilderConverter::ConvertRadius(state, value));
}

 // border-bottom-right-radius



const char* BorderBottomRightRadius::GetPropertyName() const {
  return "border-bottom-right-radius";
}

const AtomicString& BorderBottomRightRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-bottom-right-radius"));
  return name;
}

const char* BorderBottomRightRadius::GetJSPropertyName() const {
  return "borderBottomRightRadius";
}


bool BorderBottomRightRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderRadiusMapping().Contains(id);
}
const CSSProperty& BorderBottomRightRadius::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottomRight(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderRadiusMapping());
}
const CSSValue* BorderBottomRightRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}

void BorderBottomRightRadius::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderBottomRightRadius(ComputedStyleInitialValues::InitialBorderBottomRightRadius());
}
void BorderBottomRightRadius::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetBorderBottomRightRadius(state.ParentStyle()->BorderBottomRightRadius());
}
void BorderBottomRightRadius::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderBottomRightRadius(StyleBuilderConverter::ConvertRadius(state, value));
}

 // border-bottom-style



const char* BorderBottomStyle::GetPropertyName() const {
  return "border-bottom-style";
}

const AtomicString& BorderBottomStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-bottom-style"));
  return name;
}

const char* BorderBottomStyle::GetJSPropertyName() const {
  return "borderBottomStyle";
}


bool BorderBottomStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderStyleMapping().Contains(id);
}
const CSSProperty& BorderBottomStyle::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderStyleMapping());
}

void BorderBottomStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderBottomStyle(ComputedStyleInitialValues::InitialBorderBottomStyle());
}
void BorderBottomStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderBottomStyle(state.ParentStyle()->BorderBottomStyle());
}
void BorderBottomStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderBottomStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::EBorderStyle>());
}

 // border-bottom-width



const char* BorderBottomWidth::GetPropertyName() const {
  return "border-bottom-width";
}

const AtomicString& BorderBottomWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-bottom-width"));
  return name;
}

const char* BorderBottomWidth::GetJSPropertyName() const {
  return "borderBottomWidth";
}


bool BorderBottomWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderWidthMapping().Contains(id);
}
const CSSProperty& BorderBottomWidth::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderWidthMapping());
}
const CSSValue* BorderBottomWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderWidthSide(stream, context, local_context);
}

void BorderBottomWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderBottomWidth(StyleBuilderConverter::ConvertBorderWidth(state, value));
}

 // border-collapse



const char* BorderCollapse::GetPropertyName() const {
  return "border-collapse";
}

const AtomicString& BorderCollapse::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-collapse"));
  return name;
}

const char* BorderCollapse::GetJSPropertyName() const {
  return "borderCollapse";
}



void BorderCollapse::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderCollapse(ComputedStyleInitialValues::InitialBorderCollapse());
  state.StyleBuilder().SetBorderCollapseIsInherited(false);
}
void BorderCollapse::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderCollapse(state.ParentStyle()->BorderCollapse());
  state.StyleBuilder().SetBorderCollapseIsInherited(true);
}
void BorderCollapse::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderCollapse(To<CSSIdentifierValue>(value).ConvertTo<blink::EBorderCollapse>());
  state.StyleBuilder().SetBorderCollapseIsInherited(false);
}

 // border-end-end-radius



const char* BorderEndEndRadius::GetPropertyName() const {
  return "border-end-end-radius";
}

const AtomicString& BorderEndEndRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-end-end-radius"));
  return name;
}

const char* BorderEndEndRadius::GetJSPropertyName() const {
  return "borderEndEndRadius";
}


const CSSProperty* BorderEndEndRadius::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderEndEndRadius::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveEndEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderRadiusMapping());
}

bool BorderEndEndRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderRadiusMapping().Contains(id);
}
const CSSValue* BorderEndEndRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}


 // border-end-start-radius



const char* BorderEndStartRadius::GetPropertyName() const {
  return "border-end-start-radius";
}

const AtomicString& BorderEndStartRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-end-start-radius"));
  return name;
}

const char* BorderEndStartRadius::GetJSPropertyName() const {
  return "borderEndStartRadius";
}


const CSSProperty* BorderEndStartRadius::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderEndStartRadius::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveEndStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderRadiusMapping());
}

bool BorderEndStartRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderRadiusMapping().Contains(id);
}
const CSSValue* BorderEndStartRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}


 // border-image-outset



const char* BorderImageOutset::GetPropertyName() const {
  return "border-image-outset";
}

const AtomicString& BorderImageOutset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-image-outset"));
  return name;
}

const char* BorderImageOutset::GetJSPropertyName() const {
  return "borderImageOutset";
}


const CSSValue* BorderImageOutset::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderImageOutset(stream, context, local_context);
}

void BorderImageOutset::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().BorderImage();
  if (style_building_utils::BorderImageLengthMatchesAllSides(current_image.Outset(),
                                       BorderImageLength(0)))
    return;
  NinePieceImage image(current_image);
  image.SetOutset(0);
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageOutset::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  image.CopyOutsetFrom(state.ParentStyle()->BorderImage());
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageOutset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  image.SetOutset(CSSToStyleMap::MapNinePieceImageQuad(state, value));
  state.StyleBuilder().SetBorderImage(image);
}

 // border-image-repeat



const char* BorderImageRepeat::GetPropertyName() const {
  return "border-image-repeat";
}

const AtomicString& BorderImageRepeat::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-image-repeat"));
  return name;
}

const char* BorderImageRepeat::GetJSPropertyName() const {
  return "borderImageRepeat";
}



void BorderImageRepeat::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().BorderImage();
  if (current_image.HorizontalRule() == kStretchImageRule &&
      current_image.VerticalRule() == kStretchImageRule)
    return;
  NinePieceImage image(current_image);
  image.SetHorizontalRule(kStretchImageRule);
  image.SetVerticalRule(kStretchImageRule);
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageRepeat::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  image.CopyRepeatFrom(state.ParentStyle()->BorderImage());
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageRepeat::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  CSSToStyleMap::MapNinePieceImageRepeat(state, value, image);
  state.StyleBuilder().SetBorderImage(image);
}

 // border-image-slice



const char* BorderImageSlice::GetPropertyName() const {
  return "border-image-slice";
}

const AtomicString& BorderImageSlice::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-image-slice"));
  return name;
}

const char* BorderImageSlice::GetJSPropertyName() const {
  return "borderImageSlice";
}



void BorderImageSlice::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().BorderImage();
  if (current_image.Fill() == false &&
      style_building_utils::LengthMatchesAllSides(current_image.ImageSlices(), Length::Percent(100)))
    return;
  NinePieceImage image(current_image);
  image.SetImageSlices(LengthBox(Length::Percent(100), Length::Percent(100), Length::Percent(100), Length::Percent(100)));
  image.SetFill(false);
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageSlice::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  image.CopyImageSlicesFrom(state.ParentStyle()->BorderImage());
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageSlice::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  CSSToStyleMap::MapNinePieceImageSlice(state, value, image);
  state.StyleBuilder().SetBorderImage(image);
}

 // border-image-source



const char* BorderImageSource::GetPropertyName() const {
  return "border-image-source";
}

const AtomicString& BorderImageSource::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-image-source"));
  return name;
}

const char* BorderImageSource::GetJSPropertyName() const {
  return "borderImageSource";
}


const CSSValue* BorderImageSource::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeImageOrNone(stream, context, local_context);
}

void BorderImageSource::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderImageSource(ComputedStyleInitialValues::InitialBorderImageSource());
}
void BorderImageSource::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderImageSource(state.ParentStyle()->BorderImageSource());
}

 // border-image-width



const char* BorderImageWidth::GetPropertyName() const {
  return "border-image-width";
}

const AtomicString& BorderImageWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-image-width"));
  return name;
}

const char* BorderImageWidth::GetJSPropertyName() const {
  return "borderImageWidth";
}


const CSSValue* BorderImageWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderImageWidth(stream, context, local_context);
}

void BorderImageWidth::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().BorderImage();
  if (style_building_utils::BorderImageLengthMatchesAllSides(current_image.BorderSlices(),
                                       BorderImageLength(1.0)))
    return;
  NinePieceImage image(current_image);
  image.SetBorderSlices(1.0);
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageWidth::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  image.CopyBorderSlicesFrom(state.ParentStyle()->BorderImage());
  state.StyleBuilder().SetBorderImage(image);
}
void BorderImageWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().BorderImage());
  image.SetBorderSlices(CSSToStyleMap::MapNinePieceImageQuad(state, value));
  state.StyleBuilder().SetBorderImage(image);
}

 // border-inline-end-color



const char* BorderInlineEndColor::GetPropertyName() const {
  return "border-inline-end-color";
}

const AtomicString& BorderInlineEndColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-end-color"));
  return name;
}

const char* BorderInlineEndColor::GetJSPropertyName() const {
  return "borderInlineEndColor";
}


const CSSProperty* BorderInlineEndColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineEndColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderColorMapping());
}

bool BorderInlineEndColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderColorMapping().Contains(id);
}
const CSSValue* BorderInlineEndColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}


 // border-inline-end-style



const char* BorderInlineEndStyle::GetPropertyName() const {
  return "border-inline-end-style";
}

const AtomicString& BorderInlineEndStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-end-style"));
  return name;
}

const char* BorderInlineEndStyle::GetJSPropertyName() const {
  return "borderInlineEndStyle";
}


const CSSProperty* BorderInlineEndStyle::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineEndStyle::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderStyleMapping());
}

bool BorderInlineEndStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderStyleMapping().Contains(id);
}


 // border-inline-end-width



const char* BorderInlineEndWidth::GetPropertyName() const {
  return "border-inline-end-width";
}

const AtomicString& BorderInlineEndWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-end-width"));
  return name;
}

const char* BorderInlineEndWidth::GetJSPropertyName() const {
  return "borderInlineEndWidth";
}


const CSSProperty* BorderInlineEndWidth::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineEndWidth::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderWidthMapping());
}

bool BorderInlineEndWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderWidthMapping().Contains(id);
}


 // border-inline-start-color



const char* BorderInlineStartColor::GetPropertyName() const {
  return "border-inline-start-color";
}

const AtomicString& BorderInlineStartColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-start-color"));
  return name;
}

const char* BorderInlineStartColor::GetJSPropertyName() const {
  return "borderInlineStartColor";
}


const CSSProperty* BorderInlineStartColor::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineStartColor::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderColorMapping());
}

bool BorderInlineStartColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderColorMapping().Contains(id);
}
const CSSValue* BorderInlineStartColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}


 // border-inline-start-style



const char* BorderInlineStartStyle::GetPropertyName() const {
  return "border-inline-start-style";
}

const AtomicString& BorderInlineStartStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-start-style"));
  return name;
}

const char* BorderInlineStartStyle::GetJSPropertyName() const {
  return "borderInlineStartStyle";
}


const CSSProperty* BorderInlineStartStyle::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineStartStyle::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderStyleMapping());
}

bool BorderInlineStartStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderStyleMapping().Contains(id);
}


 // border-inline-start-width



const char* BorderInlineStartWidth::GetPropertyName() const {
  return "border-inline-start-width";
}

const AtomicString& BorderInlineStartWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-inline-start-width"));
  return name;
}

const char* BorderInlineStartWidth::GetJSPropertyName() const {
  return "borderInlineStartWidth";
}


const CSSProperty* BorderInlineStartWidth::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderInlineStartWidth::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderWidthMapping());
}

bool BorderInlineStartWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderWidthMapping().Contains(id);
}


 // border-left-color



const char* BorderLeftColor::GetPropertyName() const {
  return "border-left-color";
}

const AtomicString& BorderLeftColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-left-color"));
  return name;
}

const char* BorderLeftColor::GetJSPropertyName() const {
  return "borderLeftColor";
}


bool BorderLeftColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderColorMapping().Contains(id);
}
const CSSProperty& BorderLeftColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderColorMapping());
}
const CSSValue* BorderLeftColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void BorderLeftColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderLeftColor(StyleColor::CurrentColor());
}

void BorderLeftColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderLeftColor(state.ParentStyle()->BorderLeftColor());
}

void BorderLeftColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderLeftColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // border-left-style



const char* BorderLeftStyle::GetPropertyName() const {
  return "border-left-style";
}

const AtomicString& BorderLeftStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-left-style"));
  return name;
}

const char* BorderLeftStyle::GetJSPropertyName() const {
  return "borderLeftStyle";
}


bool BorderLeftStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderStyleMapping().Contains(id);
}
const CSSProperty& BorderLeftStyle::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderStyleMapping());
}

void BorderLeftStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderLeftStyle(ComputedStyleInitialValues::InitialBorderLeftStyle());
}
void BorderLeftStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderLeftStyle(state.ParentStyle()->BorderLeftStyle());
}
void BorderLeftStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderLeftStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::EBorderStyle>());
}

 // border-left-width



const char* BorderLeftWidth::GetPropertyName() const {
  return "border-left-width";
}

const AtomicString& BorderLeftWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-left-width"));
  return name;
}

const char* BorderLeftWidth::GetJSPropertyName() const {
  return "borderLeftWidth";
}


bool BorderLeftWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderWidthMapping().Contains(id);
}
const CSSProperty& BorderLeftWidth::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderWidthMapping());
}
const CSSValue* BorderLeftWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderWidthSide(stream, context, local_context);
}

void BorderLeftWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderLeftWidth(StyleBuilderConverter::ConvertBorderWidth(state, value));
}

 // border-right-color



const char* BorderRightColor::GetPropertyName() const {
  return "border-right-color";
}

const AtomicString& BorderRightColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-right-color"));
  return name;
}

const char* BorderRightColor::GetJSPropertyName() const {
  return "borderRightColor";
}


bool BorderRightColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderColorMapping().Contains(id);
}
const CSSProperty& BorderRightColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderColorMapping());
}
const CSSValue* BorderRightColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void BorderRightColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderRightColor(StyleColor::CurrentColor());
}

void BorderRightColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderRightColor(state.ParentStyle()->BorderRightColor());
}

void BorderRightColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderRightColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // border-right-style



const char* BorderRightStyle::GetPropertyName() const {
  return "border-right-style";
}

const AtomicString& BorderRightStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-right-style"));
  return name;
}

const char* BorderRightStyle::GetJSPropertyName() const {
  return "borderRightStyle";
}


bool BorderRightStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderStyleMapping().Contains(id);
}
const CSSProperty& BorderRightStyle::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderStyleMapping());
}

void BorderRightStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderRightStyle(ComputedStyleInitialValues::InitialBorderRightStyle());
}
void BorderRightStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderRightStyle(state.ParentStyle()->BorderRightStyle());
}
void BorderRightStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderRightStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::EBorderStyle>());
}

 // border-right-width



const char* BorderRightWidth::GetPropertyName() const {
  return "border-right-width";
}

const AtomicString& BorderRightWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-right-width"));
  return name;
}

const char* BorderRightWidth::GetJSPropertyName() const {
  return "borderRightWidth";
}


bool BorderRightWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderWidthMapping().Contains(id);
}
const CSSProperty& BorderRightWidth::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderWidthMapping());
}
const CSSValue* BorderRightWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderWidthSide(stream, context, local_context);
}

void BorderRightWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderRightWidth(StyleBuilderConverter::ConvertBorderWidth(state, value));
}

 // border-shape


CSSExposure BorderShape::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSBorderShapeEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* BorderShape::GetPropertyName() const {
  return "border-shape";
}

const AtomicString& BorderShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-shape"));
  return name;
}

const char* BorderShape::GetJSPropertyName() const {
  return "borderShape";
}



void BorderShape::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderShape(ComputedStyleInitialValues::InitialBorderShape());
}
void BorderShape::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderShape(state.ParentStyle()->BorderShape());
}
void BorderShape::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderShape(StyleBuilderConverter::ConvertBorderShape(state, value));
}

 // border-start-end-radius



const char* BorderStartEndRadius::GetPropertyName() const {
  return "border-start-end-radius";
}

const AtomicString& BorderStartEndRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-start-end-radius"));
  return name;
}

const char* BorderStartEndRadius::GetJSPropertyName() const {
  return "borderStartEndRadius";
}


const CSSProperty* BorderStartEndRadius::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderStartEndRadius::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveStartEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderRadiusMapping());
}

bool BorderStartEndRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderRadiusMapping().Contains(id);
}
const CSSValue* BorderStartEndRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}


 // border-start-start-radius



const char* BorderStartStartRadius::GetPropertyName() const {
  return "border-start-start-radius";
}

const AtomicString& BorderStartStartRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-start-start-radius"));
  return name;
}

const char* BorderStartStartRadius::GetJSPropertyName() const {
  return "borderStartStartRadius";
}


const CSSProperty* BorderStartStartRadius::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& BorderStartStartRadius::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveStartStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalBorderRadiusMapping());
}

bool BorderStartStartRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalBorderRadiusMapping().Contains(id);
}
const CSSValue* BorderStartStartRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}


 // border-top-color



const char* BorderTopColor::GetPropertyName() const {
  return "border-top-color";
}

const AtomicString& BorderTopColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-top-color"));
  return name;
}

const char* BorderTopColor::GetJSPropertyName() const {
  return "borderTopColor";
}


bool BorderTopColor::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderColorMapping().Contains(id);
}
const CSSProperty& BorderTopColor::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderColorMapping());
}
const CSSValue* BorderTopColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderColorSide(stream, context, local_context);
}

void BorderTopColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderTopColor(StyleColor::CurrentColor());
}

void BorderTopColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderTopColor(state.ParentStyle()->BorderTopColor());
}

void BorderTopColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderTopColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // border-top-left-radius



const char* BorderTopLeftRadius::GetPropertyName() const {
  return "border-top-left-radius";
}

const AtomicString& BorderTopLeftRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-top-left-radius"));
  return name;
}

const char* BorderTopLeftRadius::GetJSPropertyName() const {
  return "borderTopLeftRadius";
}


bool BorderTopLeftRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderRadiusMapping().Contains(id);
}
const CSSProperty& BorderTopLeftRadius::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTopLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderRadiusMapping());
}
const CSSValue* BorderTopLeftRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}

void BorderTopLeftRadius::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderTopLeftRadius(ComputedStyleInitialValues::InitialBorderTopLeftRadius());
}
void BorderTopLeftRadius::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetBorderTopLeftRadius(state.ParentStyle()->BorderTopLeftRadius());
}
void BorderTopLeftRadius::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderTopLeftRadius(StyleBuilderConverter::ConvertRadius(state, value));
}

 // border-top-right-radius



const char* BorderTopRightRadius::GetPropertyName() const {
  return "border-top-right-radius";
}

const AtomicString& BorderTopRightRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-top-right-radius"));
  return name;
}

const char* BorderTopRightRadius::GetJSPropertyName() const {
  return "borderTopRightRadius";
}


bool BorderTopRightRadius::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderRadiusMapping().Contains(id);
}
const CSSProperty& BorderTopRightRadius::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTopRight(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderRadiusMapping());
}
const CSSValue* BorderTopRightRadius::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderRadiusCorner(stream, context, local_context);
}

void BorderTopRightRadius::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderTopRightRadius(ComputedStyleInitialValues::InitialBorderTopRightRadius());
}
void BorderTopRightRadius::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetBorderTopRightRadius(state.ParentStyle()->BorderTopRightRadius());
}
void BorderTopRightRadius::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderTopRightRadius(StyleBuilderConverter::ConvertRadius(state, value));
}

 // border-top-style



const char* BorderTopStyle::GetPropertyName() const {
  return "border-top-style";
}

const AtomicString& BorderTopStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-top-style"));
  return name;
}

const char* BorderTopStyle::GetJSPropertyName() const {
  return "borderTopStyle";
}


bool BorderTopStyle::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderStyleMapping().Contains(id);
}
const CSSProperty& BorderTopStyle::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderStyleMapping());
}

void BorderTopStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderTopStyle(ComputedStyleInitialValues::InitialBorderTopStyle());
}
void BorderTopStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderTopStyle(state.ParentStyle()->BorderTopStyle());
}
void BorderTopStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderTopStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::EBorderStyle>());
}

 // border-top-width



const char* BorderTopWidth::GetPropertyName() const {
  return "border-top-width";
}

const AtomicString& BorderTopWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("border-top-width"));
  return name;
}

const char* BorderTopWidth::GetJSPropertyName() const {
  return "borderTopWidth";
}


bool BorderTopWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalBorderWidthMapping().Contains(id);
}
const CSSProperty& BorderTopWidth::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalBorderWidthMapping());
}
const CSSValue* BorderTopWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseBorderWidthSide(stream, context, local_context);
}

void BorderTopWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBorderTopWidth(StyleBuilderConverter::ConvertBorderWidth(state, value));
}

 // bottom



const char* Bottom::GetPropertyName() const {
  return "bottom";
}

const AtomicString& Bottom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("bottom"));
  return name;
}

const char* Bottom::GetJSPropertyName() const {
  return "bottom";
}


bool Bottom::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalInsetMapping().Contains(id);
}
const CSSProperty& Bottom::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalInsetMapping());
}

void Bottom::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBottom(ComputedStyleInitialValues::InitialBottom());
}
void Bottom::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetBottom(state.ParentStyle()->Bottom());
}
void Bottom::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kBottom,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetBottom(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // box-decoration-break



const char* BoxDecorationBreak::GetPropertyName() const {
  return "box-decoration-break";
}

const AtomicString& BoxDecorationBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("box-decoration-break"));
  return name;
}

const char* BoxDecorationBreak::GetJSPropertyName() const {
  return "boxDecorationBreak";
}



void BoxDecorationBreak::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxDecorationBreak(ComputedStyleInitialValues::InitialBoxDecorationBreak());
}
void BoxDecorationBreak::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxDecorationBreak(state.ParentStyle()->BoxDecorationBreak());
}
void BoxDecorationBreak::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxDecorationBreak(To<CSSIdentifierValue>(value).ConvertTo<blink::EBoxDecorationBreak>());
}

 // box-shadow



const char* BoxShadow::GetPropertyName() const {
  return "box-shadow";
}

const AtomicString& BoxShadow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("box-shadow"));
  return name;
}

const char* BoxShadow::GetJSPropertyName() const {
  return "boxShadow";
}



void BoxShadow::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxShadow(ComputedStyleInitialValues::InitialBoxShadow());
}
void BoxShadow::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxShadow(state.ParentStyle()->BoxShadow());
}
void BoxShadow::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxShadow(StyleBuilderConverter::ConvertShadowList(state, value));
}

 // box-sizing



const char* BoxSizing::GetPropertyName() const {
  return "box-sizing";
}

const AtomicString& BoxSizing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("box-sizing"));
  return name;
}

const char* BoxSizing::GetJSPropertyName() const {
  return "boxSizing";
}



void BoxSizing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxSizing(ComputedStyleInitialValues::InitialBoxSizing());
}
void BoxSizing::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxSizing(state.ParentStyle()->BoxSizing());
}
void BoxSizing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxSizing(To<CSSIdentifierValue>(value).ConvertTo<blink::EBoxSizing>());
}

 // break-after



const char* BreakAfter::GetPropertyName() const {
  return "break-after";
}

const AtomicString& BreakAfter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("break-after"));
  return name;
}

const char* BreakAfter::GetJSPropertyName() const {
  return "breakAfter";
}



void BreakAfter::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBreakAfter(ComputedStyleInitialValues::InitialBreakAfter());
}
void BreakAfter::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBreakAfter(state.ParentStyle()->BreakAfter());
}
void BreakAfter::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBreakAfter(To<CSSIdentifierValue>(value).ConvertTo<blink::EBreakBetween>());
}

 // break-before



const char* BreakBefore::GetPropertyName() const {
  return "break-before";
}

const AtomicString& BreakBefore::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("break-before"));
  return name;
}

const char* BreakBefore::GetJSPropertyName() const {
  return "breakBefore";
}



void BreakBefore::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBreakBefore(ComputedStyleInitialValues::InitialBreakBefore());
}
void BreakBefore::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBreakBefore(state.ParentStyle()->BreakBefore());
}
void BreakBefore::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBreakBefore(To<CSSIdentifierValue>(value).ConvertTo<blink::EBreakBetween>());
}

 // break-inside



const char* BreakInside::GetPropertyName() const {
  return "break-inside";
}

const AtomicString& BreakInside::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("break-inside"));
  return name;
}

const char* BreakInside::GetJSPropertyName() const {
  return "breakInside";
}



void BreakInside::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBreakInside(ComputedStyleInitialValues::InitialBreakInside());
}
void BreakInside::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBreakInside(state.ParentStyle()->BreakInside());
}
void BreakInside::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBreakInside(To<CSSIdentifierValue>(value).ConvertTo<blink::EBreakInside>());
}

 // buffered-rendering



const char* BufferedRendering::GetPropertyName() const {
  return "buffered-rendering";
}

const AtomicString& BufferedRendering::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("buffered-rendering"));
  return name;
}

const char* BufferedRendering::GetJSPropertyName() const {
  return "bufferedRendering";
}



void BufferedRendering::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBufferedRendering(ComputedStyleInitialValues::InitialBufferedRendering());
}
void BufferedRendering::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBufferedRendering(state.ParentStyle()->BufferedRendering());
}
void BufferedRendering::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBufferedRendering(To<CSSIdentifierValue>(value).ConvertTo<blink::EBufferedRendering>());
}

 // caption-side



const char* CaptionSide::GetPropertyName() const {
  return "caption-side";
}

const AtomicString& CaptionSide::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("caption-side"));
  return name;
}

const char* CaptionSide::GetJSPropertyName() const {
  return "captionSide";
}



void CaptionSide::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCaptionSide(ComputedStyleInitialValues::InitialCaptionSide());
  state.StyleBuilder().SetCaptionSideIsInherited(false);
}
void CaptionSide::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCaptionSide(state.ParentStyle()->CaptionSide());
  state.StyleBuilder().SetCaptionSideIsInherited(true);
}
void CaptionSide::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCaptionSide(To<CSSIdentifierValue>(value).ConvertTo<blink::ECaptionSide>());
  state.StyleBuilder().SetCaptionSideIsInherited(false);
}

 // caret-animation


CSSExposure CaretAnimation::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSCaretAnimationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* CaretAnimation::GetPropertyName() const {
  return "caret-animation";
}

const AtomicString& CaretAnimation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("caret-animation"));
  return name;
}

const char* CaretAnimation::GetJSPropertyName() const {
  return "caretAnimation";
}



void CaretAnimation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCaretAnimation(ComputedStyleInitialValues::InitialCaretAnimation());
}
void CaretAnimation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCaretAnimation(state.ParentStyle()->CaretAnimation());
}
void CaretAnimation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCaretAnimation(To<CSSIdentifierValue>(value).ConvertTo<blink::ECaretAnimation>());
}

 // caret-color



const char* CaretColor::GetPropertyName() const {
  return "caret-color";
}

const AtomicString& CaretColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("caret-color"));
  return name;
}

const char* CaretColor::GetJSPropertyName() const {
  return "caretColor";
}



void CaretColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCaretColor(ComputedStyleInitialValues::InitialCaretColor());
}
void CaretColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCaretColor(state.ParentStyle()->CaretColor());
}
void CaretColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCaretColor(StyleBuilderConverter::ConvertStyleAutoColor(state, value));
}

 // caret-shape


CSSExposure CaretShape::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSCaretShapeEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* CaretShape::GetPropertyName() const {
  return "caret-shape";
}

const AtomicString& CaretShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("caret-shape"));
  return name;
}

const char* CaretShape::GetJSPropertyName() const {
  return "caretShape";
}



void CaretShape::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCaretShape(ComputedStyleInitialValues::InitialCaretShape());
}
void CaretShape::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCaretShape(state.ParentStyle()->CaretShape());
}
void CaretShape::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCaretShape(To<CSSIdentifierValue>(value).ConvertTo<blink::ECaretShape>());
}

 // clear



const char* Clear::GetPropertyName() const {
  return "clear";
}

const AtomicString& Clear::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("clear"));
  return name;
}

const char* Clear::GetJSPropertyName() const {
  return "clear";
}



void Clear::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetClear(ComputedStyleInitialValues::InitialClear());
}
void Clear::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetClear(state.ParentStyle()->Clear());
}
void Clear::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetClear(To<CSSIdentifierValue>(value).ConvertTo<blink::EClear>());
}

 // clip



const char* Clip::GetPropertyName() const {
  return "clip";
}

const AtomicString& Clip::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("clip"));
  return name;
}

const char* Clip::GetJSPropertyName() const {
  return "clip";
}



void Clip::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHasAutoClip();
}
void Clip::ApplyInherit(StyleResolverState& state) const {
  if (state.ParentStyle()->HasAutoClip())
    state.StyleBuilder().SetHasAutoClip();
  else
    state.StyleBuilder().SetClip(state.ParentStyle()->Clip());
}
void Clip::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  auto* identifier_value = DynamicTo<CSSIdentifierValue>(value);
  if (identifier_value && identifier_value->GetValueID() == CSSValueID::kAuto)
    state.StyleBuilder().SetHasAutoClip();
  else
    state.StyleBuilder().SetClip(StyleBuilderConverter::ConvertClip(state, value));
}

 // clip-path



const char* ClipPath::GetPropertyName() const {
  return "clip-path";
}

const AtomicString& ClipPath::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("clip-path"));
  return name;
}

const char* ClipPath::GetJSPropertyName() const {
  return "clipPath";
}



void ClipPath::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetClipPath(ComputedStyleInitialValues::InitialClipPath());
}
void ClipPath::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetClipPath(state.ParentStyle()->ClipPath());
}
void ClipPath::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetClipPath(StyleBuilderConverter::ConvertClipPath(state, value));
}

 // clip-rule



const char* ClipRule::GetPropertyName() const {
  return "clip-rule";
}

const AtomicString& ClipRule::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("clip-rule"));
  return name;
}

const char* ClipRule::GetJSPropertyName() const {
  return "clipRule";
}



void ClipRule::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetClipRule(ComputedStyleInitialValues::InitialClipRule());
}
void ClipRule::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetClipRule(state.ParentStyle()->ClipRule());
}
void ClipRule::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetClipRule(To<CSSIdentifierValue>(value).ConvertTo<blink::WindRule>());
}

 // color-interpolation



const char* ColorInterpolation::GetPropertyName() const {
  return "color-interpolation";
}

const AtomicString& ColorInterpolation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("color-interpolation"));
  return name;
}

const char* ColorInterpolation::GetJSPropertyName() const {
  return "colorInterpolation";
}



void ColorInterpolation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColorInterpolation(ComputedStyleInitialValues::InitialColorInterpolation());
}
void ColorInterpolation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColorInterpolation(state.ParentStyle()->ColorInterpolation());
}
void ColorInterpolation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColorInterpolation(To<CSSIdentifierValue>(value).ConvertTo<blink::EColorInterpolation>());
}

 // color-interpolation-filters



const char* ColorInterpolationFilters::GetPropertyName() const {
  return "color-interpolation-filters";
}

const AtomicString& ColorInterpolationFilters::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("color-interpolation-filters"));
  return name;
}

const char* ColorInterpolationFilters::GetJSPropertyName() const {
  return "colorInterpolationFilters";
}



void ColorInterpolationFilters::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColorInterpolationFilters(ComputedStyleInitialValues::InitialColorInterpolationFilters());
}
void ColorInterpolationFilters::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColorInterpolationFilters(state.ParentStyle()->ColorInterpolationFilters());
}
void ColorInterpolationFilters::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColorInterpolationFilters(To<CSSIdentifierValue>(value).ConvertTo<blink::EColorInterpolation>());
}

 // color-rendering



const char* ColorRendering::GetPropertyName() const {
  return "color-rendering";
}

const AtomicString& ColorRendering::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("color-rendering"));
  return name;
}

const char* ColorRendering::GetJSPropertyName() const {
  return "colorRendering";
}



void ColorRendering::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColorRendering(ComputedStyleInitialValues::InitialColorRendering());
}
void ColorRendering::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColorRendering(state.ParentStyle()->ColorRendering());
}
void ColorRendering::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColorRendering(To<CSSIdentifierValue>(value).ConvertTo<blink::EColorRendering>());
}

 // column-count



const char* ColumnCount::GetPropertyName() const {
  return "column-count";
}

const AtomicString& ColumnCount::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-count"));
  return name;
}

const char* ColumnCount::GetJSPropertyName() const {
  return "columnCount";
}


const CSSValue* ColumnCount::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColumnCount(stream, context, local_context);
}

void ColumnCount::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHasAutoColumnCount();
}
void ColumnCount::ApplyInherit(StyleResolverState& state) const {
  if (state.ParentStyle()->HasAutoColumnCount())
    state.StyleBuilder().SetHasAutoColumnCount();
  else
    state.StyleBuilder().SetColumnCount(state.ParentStyle()->ColumnCount());
}
void ColumnCount::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  auto* identifier_value = DynamicTo<CSSIdentifierValue>(value);
  if (identifier_value && identifier_value->GetValueID() == CSSValueID::kAuto)
    state.StyleBuilder().SetHasAutoColumnCount();
  else
    state.StyleBuilder().SetColumnCount(To<CSSPrimitiveValue>(value).ConvertTo<unsigned short>(state.CssToLengthConversionData()));
}

 // column-fill



const char* ColumnFill::GetPropertyName() const {
  return "column-fill";
}

const AtomicString& ColumnFill::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-fill"));
  return name;
}

const char* ColumnFill::GetJSPropertyName() const {
  return "columnFill";
}



void ColumnFill::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnFill(ComputedStyleInitialValues::InitialColumnFill());
}
void ColumnFill::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnFill(state.ParentStyle()->GetColumnFill());
}
void ColumnFill::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnFill(To<CSSIdentifierValue>(value).ConvertTo<blink::EColumnFill>());
}

 // column-gap



const char* ColumnGap::GetPropertyName() const {
  return "column-gap";
}

const AtomicString& ColumnGap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-gap"));
  return name;
}

const char* ColumnGap::GetJSPropertyName() const {
  return "columnGap";
}


const CSSValue* ColumnGap::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGapLength(stream, context, local_context);
}

void ColumnGap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnGap(ComputedStyleInitialValues::InitialColumnGap());
}
void ColumnGap::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetColumnGap(state.ParentStyle()->ColumnGap());
}
void ColumnGap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnGap(StyleBuilderConverter::ConvertGapLength(state, value));
}

 // column-height


CSSExposure ColumnHeight::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::MulticolColumnWrappingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnHeight::GetPropertyName() const {
  return "column-height";
}

const AtomicString& ColumnHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-height"));
  return name;
}

const char* ColumnHeight::GetJSPropertyName() const {
  return "columnHeight";
}


const CSSValue* ColumnHeight::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColumnLength(stream, context, local_context);
}

void ColumnHeight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHasAutoColumnHeight();
}
void ColumnHeight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  if (state.ParentStyle()->HasAutoColumnHeight())
    state.StyleBuilder().SetHasAutoColumnHeight();
  else
    state.StyleBuilder().SetColumnHeight(state.ParentStyle()->ColumnHeight());
}
void ColumnHeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  auto* identifier_value = DynamicTo<CSSIdentifierValue>(value);
  if (identifier_value && identifier_value->GetValueID() == CSSValueID::kAuto)
    state.StyleBuilder().SetHasAutoColumnHeight();
  else
    state.StyleBuilder().SetColumnHeight(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // column-rule-break


CSSExposure ColumnRuleBreak::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleBreak::GetPropertyName() const {
  return "column-rule-break";
}

const AtomicString& ColumnRuleBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-break"));
  return name;
}

const char* ColumnRuleBreak::GetJSPropertyName() const {
  return "columnRuleBreak";
}



void ColumnRuleBreak::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleBreak(ComputedStyleInitialValues::InitialColumnRuleBreak());
}
void ColumnRuleBreak::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleBreak(state.ParentStyle()->ColumnRuleBreak());
}
void ColumnRuleBreak::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleBreak(To<CSSIdentifierValue>(value).ConvertTo<blink::RuleBreak>());
}

 // column-rule-color



const char* ColumnRuleColor::GetPropertyName() const {
  return "column-rule-color";
}

const AtomicString& ColumnRuleColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-color"));
  return name;
}

const char* ColumnRuleColor::GetJSPropertyName() const {
  return "columnRuleColor";
}



void ColumnRuleColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleColor(ComputedStyleInitialValues::InitialColumnRuleColor());
}
void ColumnRuleColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleColor(state.ParentStyle()->ColumnRuleColor());
}
void ColumnRuleColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleColor(StyleBuilderConverter::ConvertGapDecorationColorDataList(state, value));
}

 // column-rule-inset-cap-end


CSSExposure ColumnRuleInsetCapEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetCapEnd::GetPropertyName() const {
  return "column-rule-inset-cap-end";
}

const AtomicString& ColumnRuleInsetCapEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-cap-end"));
  return name;
}

const char* ColumnRuleInsetCapEnd::GetJSPropertyName() const {
  return "columnRuleInsetCapEnd";
}



void ColumnRuleInsetCapEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetCapEnd(ComputedStyleInitialValues::InitialColumnRuleInsetCapEnd());
}
void ColumnRuleInsetCapEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetCapEnd(state.ParentStyle()->ColumnRuleInsetCapEnd());
}
void ColumnRuleInsetCapEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleInsetCapEnd(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // column-rule-inset-cap-start


CSSExposure ColumnRuleInsetCapStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetCapStart::GetPropertyName() const {
  return "column-rule-inset-cap-start";
}

const AtomicString& ColumnRuleInsetCapStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-cap-start"));
  return name;
}

const char* ColumnRuleInsetCapStart::GetJSPropertyName() const {
  return "columnRuleInsetCapStart";
}



void ColumnRuleInsetCapStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetCapStart(ComputedStyleInitialValues::InitialColumnRuleInsetCapStart());
}
void ColumnRuleInsetCapStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetCapStart(state.ParentStyle()->ColumnRuleInsetCapStart());
}
void ColumnRuleInsetCapStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleInsetCapStart(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // column-rule-inset-junction-end


CSSExposure ColumnRuleInsetJunctionEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetJunctionEnd::GetPropertyName() const {
  return "column-rule-inset-junction-end";
}

const AtomicString& ColumnRuleInsetJunctionEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-junction-end"));
  return name;
}

const char* ColumnRuleInsetJunctionEnd::GetJSPropertyName() const {
  return "columnRuleInsetJunctionEnd";
}



void ColumnRuleInsetJunctionEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetJunctionEnd(ComputedStyleInitialValues::InitialColumnRuleInsetJunctionEnd());
}
void ColumnRuleInsetJunctionEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetJunctionEnd(state.ParentStyle()->ColumnRuleInsetJunctionEnd());
}
void ColumnRuleInsetJunctionEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleInsetJunctionEnd(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // column-rule-inset-junction-start


CSSExposure ColumnRuleInsetJunctionStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleInsetJunctionStart::GetPropertyName() const {
  return "column-rule-inset-junction-start";
}

const AtomicString& ColumnRuleInsetJunctionStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-inset-junction-start"));
  return name;
}

const char* ColumnRuleInsetJunctionStart::GetJSPropertyName() const {
  return "columnRuleInsetJunctionStart";
}



void ColumnRuleInsetJunctionStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetJunctionStart(ComputedStyleInitialValues::InitialColumnRuleInsetJunctionStart());
}
void ColumnRuleInsetJunctionStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleInsetJunctionStart(state.ParentStyle()->ColumnRuleInsetJunctionStart());
}
void ColumnRuleInsetJunctionStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleInsetJunctionStart(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // column-rule-style



const char* ColumnRuleStyle::GetPropertyName() const {
  return "column-rule-style";
}

const AtomicString& ColumnRuleStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-style"));
  return name;
}

const char* ColumnRuleStyle::GetJSPropertyName() const {
  return "columnRuleStyle";
}



void ColumnRuleStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleStyle(ComputedStyleInitialValues::InitialColumnRuleStyle());
}
void ColumnRuleStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleStyle(state.ParentStyle()->ColumnRuleStyle());
}
void ColumnRuleStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleStyle(StyleBuilderConverter::ConvertGapDecorationStyleDataList(state, value));
}

 // column-rule-visibility-items


CSSExposure ColumnRuleVisibilityItems::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnRuleVisibilityItems::GetPropertyName() const {
  return "column-rule-visibility-items";
}

const AtomicString& ColumnRuleVisibilityItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-visibility-items"));
  return name;
}

const char* ColumnRuleVisibilityItems::GetJSPropertyName() const {
  return "columnRuleVisibilityItems";
}



void ColumnRuleVisibilityItems::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleVisibilityItems(ComputedStyleInitialValues::InitialColumnRuleVisibilityItems());
}
void ColumnRuleVisibilityItems::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleVisibilityItems(state.ParentStyle()->ColumnRuleVisibilityItems());
}
void ColumnRuleVisibilityItems::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleVisibilityItems(To<CSSIdentifierValue>(value).ConvertTo<blink::RuleVisibilityItems>());
}

 // column-rule-width



const char* ColumnRuleWidth::GetPropertyName() const {
  return "column-rule-width";
}

const AtomicString& ColumnRuleWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-rule-width"));
  return name;
}

const char* ColumnRuleWidth::GetJSPropertyName() const {
  return "columnRuleWidth";
}



void ColumnRuleWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnRuleWidth(ComputedStyleInitialValues::InitialColumnRuleWidth());
}
void ColumnRuleWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnRuleWidth(StyleBuilderConverter::ConvertGapDecorationWidthDataList(state, value));
}

 // column-span



const char* ColumnSpan::GetPropertyName() const {
  return "column-span";
}

const AtomicString& ColumnSpan::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-span"));
  return name;
}

const char* ColumnSpan::GetJSPropertyName() const {
  return "columnSpan";
}



void ColumnSpan::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnSpan(ComputedStyleInitialValues::InitialColumnSpan());
}
void ColumnSpan::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnSpan(state.ParentStyle()->GetColumnSpan());
}
void ColumnSpan::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnSpan(To<CSSIdentifierValue>(value).ConvertTo<blink::EColumnSpan>());
}

 // column-width



const char* ColumnWidth::GetPropertyName() const {
  return "column-width";
}

const AtomicString& ColumnWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-width"));
  return name;
}

const char* ColumnWidth::GetJSPropertyName() const {
  return "columnWidth";
}


const CSSValue* ColumnWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColumnLength(stream, context, local_context);
}

void ColumnWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHasAutoColumnWidth();
}
void ColumnWidth::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  if (state.ParentStyle()->HasAutoColumnWidth())
    state.StyleBuilder().SetHasAutoColumnWidth();
  else
    state.StyleBuilder().SetColumnWidth(state.ParentStyle()->ColumnWidth());
}
void ColumnWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  auto* identifier_value = DynamicTo<CSSIdentifierValue>(value);
  if (identifier_value && identifier_value->GetValueID() == CSSValueID::kAuto)
    state.StyleBuilder().SetHasAutoColumnWidth();
  else
    state.StyleBuilder().SetColumnWidth(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // column-wrap


CSSExposure ColumnWrap::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::MulticolColumnWrappingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ColumnWrap::GetPropertyName() const {
  return "column-wrap";
}

const AtomicString& ColumnWrap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("column-wrap"));
  return name;
}

const char* ColumnWrap::GetJSPropertyName() const {
  return "columnWrap";
}



void ColumnWrap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnWrap(ComputedStyleInitialValues::InitialColumnWrap());
}
void ColumnWrap::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetColumnWrap(state.ParentStyle()->ColumnWrap());
}
void ColumnWrap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetColumnWrap(To<CSSIdentifierValue>(value).ConvertTo<blink::EColumnWrap>());
}

 // contain



const char* Contain::GetPropertyName() const {
  return "contain";
}

const AtomicString& Contain::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("contain"));
  return name;
}

const char* Contain::GetJSPropertyName() const {
  return "contain";
}



void Contain::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContain(ComputedStyleInitialValues::InitialContain());
}
void Contain::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContain(state.ParentStyle()->Contain());
}
void Contain::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContain(StyleBuilderConverter::ConvertFlags<Containment>(state, value));
}

 // contain-intrinsic-block-size



const char* ContainIntrinsicBlockSize::GetPropertyName() const {
  return "contain-intrinsic-block-size";
}

const AtomicString& ContainIntrinsicBlockSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("contain-intrinsic-block-size"));
  return name;
}

const char* ContainIntrinsicBlockSize::GetJSPropertyName() const {
  return "containIntrinsicBlockSize";
}


const CSSProperty* ContainIntrinsicBlockSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ContainIntrinsicBlockSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlock(writing_direction,
      CSSDirectionAwareResolver::PhysicalContainIntrinsicSizeMapping());
}

bool ContainIntrinsicBlockSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalContainIntrinsicSizeMapping().Contains(id);
}
const CSSValue* ContainIntrinsicBlockSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeIntrinsicSizeLonghand(stream, context, local_context);
}


 // contain-intrinsic-height



const char* ContainIntrinsicHeight::GetPropertyName() const {
  return "contain-intrinsic-height";
}

const AtomicString& ContainIntrinsicHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("contain-intrinsic-height"));
  return name;
}

const char* ContainIntrinsicHeight::GetJSPropertyName() const {
  return "containIntrinsicHeight";
}


const CSSValue* ContainIntrinsicHeight::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeIntrinsicSizeLonghand(stream, context, local_context);
}

void ContainIntrinsicHeight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContainIntrinsicHeight(ComputedStyleInitialValues::InitialContainIntrinsicHeight());
}
void ContainIntrinsicHeight::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContainIntrinsicHeight(state.ParentStyle()->ContainIntrinsicHeight());
}
void ContainIntrinsicHeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContainIntrinsicHeight(StyleBuilderConverter::ConvertIntrinsicDimension(state, value));
}

 // contain-intrinsic-inline-size



const char* ContainIntrinsicInlineSize::GetPropertyName() const {
  return "contain-intrinsic-inline-size";
}

const AtomicString& ContainIntrinsicInlineSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("contain-intrinsic-inline-size"));
  return name;
}

const char* ContainIntrinsicInlineSize::GetJSPropertyName() const {
  return "containIntrinsicInlineSize";
}


const CSSProperty* ContainIntrinsicInlineSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ContainIntrinsicInlineSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInline(writing_direction,
      CSSDirectionAwareResolver::PhysicalContainIntrinsicSizeMapping());
}

bool ContainIntrinsicInlineSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalContainIntrinsicSizeMapping().Contains(id);
}
const CSSValue* ContainIntrinsicInlineSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeIntrinsicSizeLonghand(stream, context, local_context);
}


 // contain-intrinsic-width



const char* ContainIntrinsicWidth::GetPropertyName() const {
  return "contain-intrinsic-width";
}

const AtomicString& ContainIntrinsicWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("contain-intrinsic-width"));
  return name;
}

const char* ContainIntrinsicWidth::GetJSPropertyName() const {
  return "containIntrinsicWidth";
}


const CSSValue* ContainIntrinsicWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeIntrinsicSizeLonghand(stream, context, local_context);
}

void ContainIntrinsicWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContainIntrinsicWidth(ComputedStyleInitialValues::InitialContainIntrinsicWidth());
}
void ContainIntrinsicWidth::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContainIntrinsicWidth(state.ParentStyle()->ContainIntrinsicWidth());
}
void ContainIntrinsicWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContainIntrinsicWidth(StyleBuilderConverter::ConvertIntrinsicDimension(state, value));
}

 // container-name



const char* ContainerName::GetPropertyName() const {
  return "container-name";
}

const AtomicString& ContainerName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("container-name"));
  return name;
}

const char* ContainerName::GetJSPropertyName() const {
  return "containerName";
}


const CSSValue* ContainerName::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeContainerName(stream, context, local_context);
}

void ContainerName::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContainerName(ComputedStyleInitialValues::InitialContainerName());
}
void ContainerName::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContainerName(state.ParentStyle()->ContainerName());
}
void ContainerName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContainerName(StyleBuilderConverter::ConvertContainerName(state, value));
}

 // container-type



const char* ContainerType::GetPropertyName() const {
  return "container-type";
}

const AtomicString& ContainerType::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("container-type"));
  return name;
}

const char* ContainerType::GetJSPropertyName() const {
  return "containerType";
}



void ContainerType::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContainerType(ComputedStyleInitialValues::InitialContainerType());
}
void ContainerType::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContainerType(state.ParentStyle()->ContainerType());
}
void ContainerType::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContainerType(StyleBuilderConverter::ConvertFlags<EContainerType, CSSValueID::kNormal>(state, value));
}

 // content



const char* Content::GetPropertyName() const {
  return "content";
}

const AtomicString& Content::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("content"));
  return name;
}

const char* Content::GetJSPropertyName() const {
  return "content";
}




 // content-visibility



const char* ContentVisibility::GetPropertyName() const {
  return "content-visibility";
}

const AtomicString& ContentVisibility::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("content-visibility"));
  return name;
}

const char* ContentVisibility::GetJSPropertyName() const {
  return "contentVisibility";
}



void ContentVisibility::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContentVisibility(ComputedStyleInitialValues::InitialContentVisibility());
}
void ContentVisibility::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContentVisibility(state.ParentStyle()->ContentVisibility());
}
void ContentVisibility::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContentVisibility(To<CSSIdentifierValue>(value).ConvertTo<blink::EContentVisibility>());
}

 // continue


CSSExposure Continue::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSLineClampEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Continue::GetPropertyName() const {
  return "continue";
}

const AtomicString& Continue::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("continue"));
  return name;
}

const char* Continue::GetJSPropertyName() const {
  return "continue";
}



void Continue::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetContinue(ComputedStyleInitialValues::InitialContinue());
}
void Continue::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetContinue(state.ParentStyle()->Continue());
}
void Continue::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetContinue(To<CSSIdentifierValue>(value).ConvertTo<blink::EContinue>());
}

 // corner-bottom-left-shape



const char* CornerBottomLeftShape::GetPropertyName() const {
  return "corner-bottom-left-shape";
}

const AtomicString& CornerBottomLeftShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-bottom-left-shape"));
  return name;
}

const char* CornerBottomLeftShape::GetJSPropertyName() const {
  return "cornerBottomLeftShape";
}


bool CornerBottomLeftShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalCornerShapeMapping().Contains(id);
}
const CSSProperty& CornerBottomLeftShape::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottomLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalCornerShapeMapping());
}
const CSSValue* CornerBottomLeftShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}

void CornerBottomLeftShape::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerBottomLeftShape(ComputedStyleInitialValues::InitialCornerBottomLeftShape());
}
void CornerBottomLeftShape::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerBottomLeftShape(state.ParentStyle()->CornerBottomLeftShape());
}
void CornerBottomLeftShape::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCornerBottomLeftShape(StyleBuilderConverter::ConvertCornerShape(state, value));
}

 // corner-bottom-right-shape



const char* CornerBottomRightShape::GetPropertyName() const {
  return "corner-bottom-right-shape";
}

const AtomicString& CornerBottomRightShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-bottom-right-shape"));
  return name;
}

const char* CornerBottomRightShape::GetJSPropertyName() const {
  return "cornerBottomRightShape";
}


bool CornerBottomRightShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalCornerShapeMapping().Contains(id);
}
const CSSProperty& CornerBottomRightShape::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottomRight(writing_direction,
      CSSDirectionAwareResolver::LogicalCornerShapeMapping());
}
const CSSValue* CornerBottomRightShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}

void CornerBottomRightShape::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerBottomRightShape(ComputedStyleInitialValues::InitialCornerBottomRightShape());
}
void CornerBottomRightShape::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerBottomRightShape(state.ParentStyle()->CornerBottomRightShape());
}
void CornerBottomRightShape::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCornerBottomRightShape(StyleBuilderConverter::ConvertCornerShape(state, value));
}

 // corner-end-end-shape



const char* CornerEndEndShape::GetPropertyName() const {
  return "corner-end-end-shape";
}

const AtomicString& CornerEndEndShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-end-end-shape"));
  return name;
}

const char* CornerEndEndShape::GetJSPropertyName() const {
  return "cornerEndEndShape";
}


const CSSProperty* CornerEndEndShape::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& CornerEndEndShape::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveEndEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalCornerShapeMapping());
}

bool CornerEndEndShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalCornerShapeMapping().Contains(id);
}
const CSSValue* CornerEndEndShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}


 // corner-end-start-shape



const char* CornerEndStartShape::GetPropertyName() const {
  return "corner-end-start-shape";
}

const AtomicString& CornerEndStartShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-end-start-shape"));
  return name;
}

const char* CornerEndStartShape::GetJSPropertyName() const {
  return "cornerEndStartShape";
}


const CSSProperty* CornerEndStartShape::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& CornerEndStartShape::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveEndStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalCornerShapeMapping());
}

bool CornerEndStartShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalCornerShapeMapping().Contains(id);
}
const CSSValue* CornerEndStartShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}


 // corner-start-end-shape



const char* CornerStartEndShape::GetPropertyName() const {
  return "corner-start-end-shape";
}

const AtomicString& CornerStartEndShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-start-end-shape"));
  return name;
}

const char* CornerStartEndShape::GetJSPropertyName() const {
  return "cornerStartEndShape";
}


const CSSProperty* CornerStartEndShape::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& CornerStartEndShape::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveStartEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalCornerShapeMapping());
}

bool CornerStartEndShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalCornerShapeMapping().Contains(id);
}
const CSSValue* CornerStartEndShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}


 // corner-start-start-shape



const char* CornerStartStartShape::GetPropertyName() const {
  return "corner-start-start-shape";
}

const AtomicString& CornerStartStartShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-start-start-shape"));
  return name;
}

const char* CornerStartStartShape::GetJSPropertyName() const {
  return "cornerStartStartShape";
}


const CSSProperty* CornerStartStartShape::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& CornerStartStartShape::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveStartStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalCornerShapeMapping());
}

bool CornerStartStartShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalCornerShapeMapping().Contains(id);
}
const CSSValue* CornerStartStartShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}


 // corner-top-left-shape



const char* CornerTopLeftShape::GetPropertyName() const {
  return "corner-top-left-shape";
}

const AtomicString& CornerTopLeftShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-top-left-shape"));
  return name;
}

const char* CornerTopLeftShape::GetJSPropertyName() const {
  return "cornerTopLeftShape";
}


bool CornerTopLeftShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalCornerShapeMapping().Contains(id);
}
const CSSProperty& CornerTopLeftShape::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTopLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalCornerShapeMapping());
}
const CSSValue* CornerTopLeftShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}

void CornerTopLeftShape::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerTopLeftShape(ComputedStyleInitialValues::InitialCornerTopLeftShape());
}
void CornerTopLeftShape::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerTopLeftShape(state.ParentStyle()->CornerTopLeftShape());
}
void CornerTopLeftShape::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCornerTopLeftShape(StyleBuilderConverter::ConvertCornerShape(state, value));
}

 // corner-top-right-shape



const char* CornerTopRightShape::GetPropertyName() const {
  return "corner-top-right-shape";
}

const AtomicString& CornerTopRightShape::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("corner-top-right-shape"));
  return name;
}

const char* CornerTopRightShape::GetJSPropertyName() const {
  return "cornerTopRightShape";
}


bool CornerTopRightShape::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalCornerShapeMapping().Contains(id);
}
const CSSProperty& CornerTopRightShape::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTopRight(writing_direction,
      CSSDirectionAwareResolver::LogicalCornerShapeMapping());
}
const CSSValue* CornerTopRightShape::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeCornerShape(stream, context, local_context);
}

void CornerTopRightShape::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerTopRightShape(ComputedStyleInitialValues::InitialCornerTopRightShape());
}
void CornerTopRightShape::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCornerTopRightShape(state.ParentStyle()->CornerTopRightShape());
}
void CornerTopRightShape::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCornerTopRightShape(StyleBuilderConverter::ConvertCornerShape(state, value));
}

 // counter-increment



const char* CounterIncrement::GetPropertyName() const {
  return "counter-increment";
}

const AtomicString& CounterIncrement::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("counter-increment"));
  return name;
}

const char* CounterIncrement::GetJSPropertyName() const {
  return "counterIncrement";
}



void CounterIncrement::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().ClearIncrementDirectives();
}

void CounterIncrement::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().ClearIncrementDirectives();
  const CounterDirectiveMap* parent_map = state.ParentStyle()->GetCounterDirectives();
  if (!parent_map)
    return;

  CounterDirectiveMap& map = state.StyleBuilder().AccessCounterDirectives();
  DCHECK(!parent_map->empty());

  typedef CounterDirectiveMap::const_iterator Iterator;
  Iterator end = parent_map->end();
  for (Iterator it = parent_map->begin(); it != end; ++it) {
    CounterDirectives& directives = map.insert(it->key, CounterDirectives()).stored_value->value;
    directives.InheritIncrement(it->value);
  }
}

void CounterIncrement::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().ClearIncrementDirectives();

  const auto* list = DynamicTo<CSSValueList>(value);
  if (!list) {
    DCHECK_EQ(To<CSSIdentifierValue>(value).GetValueID(), CSSValueID::kNone);
    return;
  }

  CounterDirectiveMap& map = state.StyleBuilder().AccessCounterDirectives();

  for (const CSSValue* item : *list) {
    const auto& counter_data = To<cssvalue::CSSCounterValue>(*item);
    AtomicString identifier(To<CSSCustomIdentValue>(counter_data.Identifier())->Value());
    CounterDirectives& directives =
        map.insert(identifier, CounterDirectives()).stored_value->value;
    if (const CSSPrimitiveValue* counter_data_value = counter_data.Value()) {
      int counter_value = counter_data_value->ComputeInteger(state.CssToLengthConversionData());

      directives.AddIncrementValue(counter_value);
    }
  }
  DCHECK(!map.empty());
}

 // counter-reset



const char* CounterReset::GetPropertyName() const {
  return "counter-reset";
}

const AtomicString& CounterReset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("counter-reset"));
  return name;
}

const char* CounterReset::GetJSPropertyName() const {
  return "counterReset";
}



void CounterReset::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().ClearResetDirectives();
}

void CounterReset::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().ClearResetDirectives();
  const CounterDirectiveMap* parent_map = state.ParentStyle()->GetCounterDirectives();
  if (!parent_map)
    return;

  CounterDirectiveMap& map = state.StyleBuilder().AccessCounterDirectives();
  DCHECK(!parent_map->empty());

  typedef CounterDirectiveMap::const_iterator Iterator;
  Iterator end = parent_map->end();
  for (Iterator it = parent_map->begin(); it != end; ++it) {
    CounterDirectives& directives = map.insert(it->key, CounterDirectives()).stored_value->value;
    directives.InheritReset(it->value);
  }
}

void CounterReset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().ClearResetDirectives();

  const auto* list = DynamicTo<CSSValueList>(value);
  if (!list) {
    DCHECK_EQ(To<CSSIdentifierValue>(value).GetValueID(), CSSValueID::kNone);
    return;
  }

  CounterDirectiveMap& map = state.StyleBuilder().AccessCounterDirectives();

  for (const CSSValue* item : *list) {
    const auto& counter_data = To<cssvalue::CSSCounterValue>(*item);
    AtomicString identifier(To<CSSCustomIdentValue>(counter_data.Identifier())->Value());
    CounterDirectives& directives =
        map.insert(identifier, CounterDirectives()).stored_value->value;
    if (counter_data.IsReversed()) {
      directives.SetIsResetReversed();
    }
    if (const CSSPrimitiveValue* counter_data_value = counter_data.Value()) {
      int64_t counter_value = counter_data_value->ComputeNumber(state.CssToLengthConversionData());

      directives.SetResetValue(counter_value);
    }
  }
  DCHECK(!map.empty());
}

 // counter-set



const char* CounterSet::GetPropertyName() const {
  return "counter-set";
}

const AtomicString& CounterSet::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("counter-set"));
  return name;
}

const char* CounterSet::GetJSPropertyName() const {
  return "counterSet";
}



void CounterSet::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().ClearSetDirectives();
}

void CounterSet::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().ClearSetDirectives();
  const CounterDirectiveMap* parent_map = state.ParentStyle()->GetCounterDirectives();
  if (!parent_map)
    return;

  CounterDirectiveMap& map = state.StyleBuilder().AccessCounterDirectives();
  DCHECK(!parent_map->empty());

  typedef CounterDirectiveMap::const_iterator Iterator;
  Iterator end = parent_map->end();
  for (Iterator it = parent_map->begin(); it != end; ++it) {
    CounterDirectives& directives = map.insert(it->key, CounterDirectives()).stored_value->value;
    directives.InheritSet(it->value);
  }
}

void CounterSet::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().ClearSetDirectives();

  const auto* list = DynamicTo<CSSValueList>(value);
  if (!list) {
    DCHECK_EQ(To<CSSIdentifierValue>(value).GetValueID(), CSSValueID::kNone);
    return;
  }

  CounterDirectiveMap& map = state.StyleBuilder().AccessCounterDirectives();

  for (const CSSValue* item : *list) {
    const auto& counter_data = To<cssvalue::CSSCounterValue>(*item);
    AtomicString identifier(To<CSSCustomIdentValue>(counter_data.Identifier())->Value());
    CounterDirectives& directives =
        map.insert(identifier, CounterDirectives()).stored_value->value;
    if (const CSSPrimitiveValue* counter_data_value = counter_data.Value()) {
      int counter_value = counter_data_value->ComputeInteger(state.CssToLengthConversionData());

      directives.SetSetValue(counter_value);
    }
  }
  DCHECK(!map.empty());
}

 // cursor



const char* Cursor::GetPropertyName() const {
  return "cursor";
}

const AtomicString& Cursor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("cursor"));
  return name;
}

const char* Cursor::GetJSPropertyName() const {
  return "cursor";
}




 // cx



const char* Cx::GetPropertyName() const {
  return "cx";
}

const AtomicString& Cx::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("cx"));
  return name;
}

const char* Cx::GetJSPropertyName() const {
  return "cx";
}



void Cx::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCx(ComputedStyleInitialValues::InitialCx());
}
void Cx::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCx(state.ParentStyle()->Cx());
}
void Cx::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCx(StyleBuilderConverter::ConvertLength(state, value));
}

 // cy



const char* Cy::GetPropertyName() const {
  return "cy";
}

const AtomicString& Cy::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("cy"));
  return name;
}

const char* Cy::GetJSPropertyName() const {
  return "cy";
}



void Cy::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCy(ComputedStyleInitialValues::InitialCy());
}
void Cy::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCy(state.ParentStyle()->Cy());
}
void Cy::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCy(StyleBuilderConverter::ConvertLength(state, value));
}

 // d



const char* D::GetPropertyName() const {
  return "d";
}

const AtomicString& D::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("d"));
  return name;
}

const char* D::GetJSPropertyName() const {
  return "d";
}



void D::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetD(ComputedStyleInitialValues::InitialD());
}
void D::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetD(state.ParentStyle()->D());
}
void D::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetD(StyleBuilderConverter::ConvertPathOrNone(state, value));
}

 // descent-override



const char* DescentOverride::GetPropertyName() const {
  return "descent-override";
}

const AtomicString& DescentOverride::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("descent-override"));
  return name;
}

const char* DescentOverride::GetJSPropertyName() const {
  return "descentOverride";
}




 // display



const char* Display::GetPropertyName() const {
  return "display";
}

const AtomicString& Display::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("display"));
  return name;
}

const char* Display::GetJSPropertyName() const {
  return "display";
}




 // dominant-baseline



const char* DominantBaseline::GetPropertyName() const {
  return "dominant-baseline";
}

const AtomicString& DominantBaseline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("dominant-baseline"));
  return name;
}

const char* DominantBaseline::GetJSPropertyName() const {
  return "dominantBaseline";
}



void DominantBaseline::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetDominantBaseline(ComputedStyleInitialValues::InitialDominantBaseline());
}
void DominantBaseline::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetDominantBaseline(state.ParentStyle()->DominantBaseline());
}
void DominantBaseline::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetDominantBaseline(To<CSSIdentifierValue>(value).ConvertTo<blink::EDominantBaseline>());
}

 // dynamic-range-limit


CSSExposure DynamicRangeLimit::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSDynamicRangeLimitEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* DynamicRangeLimit::GetPropertyName() const {
  return "dynamic-range-limit";
}

const AtomicString& DynamicRangeLimit::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("dynamic-range-limit"));
  return name;
}

const char* DynamicRangeLimit::GetJSPropertyName() const {
  return "dynamicRangeLimit";
}



void DynamicRangeLimit::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetDynamicRangeLimit(ComputedStyleInitialValues::InitialDynamicRangeLimit());
}
void DynamicRangeLimit::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetDynamicRangeLimit(state.ParentStyle()->GetDynamicRangeLimit());
}
void DynamicRangeLimit::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetDynamicRangeLimit(StyleBuilderConverter::ConvertDynamicRangeLimit(state, value));
}

 // empty-cells



const char* EmptyCells::GetPropertyName() const {
  return "empty-cells";
}

const AtomicString& EmptyCells::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("empty-cells"));
  return name;
}

const char* EmptyCells::GetJSPropertyName() const {
  return "emptyCells";
}



void EmptyCells::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetEmptyCells(ComputedStyleInitialValues::InitialEmptyCells());
  state.StyleBuilder().SetEmptyCellsIsInherited(false);
}
void EmptyCells::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetEmptyCells(state.ParentStyle()->EmptyCells());
  state.StyleBuilder().SetEmptyCellsIsInherited(true);
}
void EmptyCells::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetEmptyCells(To<CSSIdentifierValue>(value).ConvertTo<blink::EEmptyCells>());
  state.StyleBuilder().SetEmptyCellsIsInherited(false);
}

 // fallback



const char* Fallback::GetPropertyName() const {
  return "fallback";
}

const AtomicString& Fallback::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("fallback"));
  return name;
}

const char* Fallback::GetJSPropertyName() const {
  return "fallback";
}




 // field-sizing



const char* FieldSizing::GetPropertyName() const {
  return "field-sizing";
}

const AtomicString& FieldSizing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("field-sizing"));
  return name;
}

const char* FieldSizing::GetJSPropertyName() const {
  return "fieldSizing";
}



void FieldSizing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFieldSizing(ComputedStyleInitialValues::InitialFieldSizing());
}
void FieldSizing::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFieldSizing(state.ParentStyle()->FieldSizing());
}
void FieldSizing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFieldSizing(To<CSSIdentifierValue>(value).ConvertTo<blink::EFieldSizing>());
}

 // fill



const char* Fill::GetPropertyName() const {
  return "fill";
}

const AtomicString& Fill::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("fill"));
  return name;
}

const char* Fill::GetJSPropertyName() const {
  return "fill";
}


const CSSValue* Fill::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeSVGPaint(stream, context, local_context);
}

void Fill::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFillPaint(ComputedStyleInitialValues::InitialFillPaint());
}

void Fill::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFillPaint(state.ParentStyle()->FillPaint());
}


 // fill-opacity



const char* FillOpacity::GetPropertyName() const {
  return "fill-opacity";
}

const AtomicString& FillOpacity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("fill-opacity"));
  return name;
}

const char* FillOpacity::GetJSPropertyName() const {
  return "fillOpacity";
}


const CSSValue* FillOpacity::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeAlphaValue(stream, context, local_context);
}

void FillOpacity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFillOpacity(ComputedStyleInitialValues::InitialFillOpacity());
}
void FillOpacity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFillOpacity(state.ParentStyle()->FillOpacity());
}
void FillOpacity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFillOpacity(StyleBuilderConverter::ConvertAlpha(state, value));
}

 // fill-rule



const char* FillRule::GetPropertyName() const {
  return "fill-rule";
}

const AtomicString& FillRule::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("fill-rule"));
  return name;
}

const char* FillRule::GetJSPropertyName() const {
  return "fillRule";
}



void FillRule::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFillRule(ComputedStyleInitialValues::InitialFillRule());
}
void FillRule::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFillRule(state.ParentStyle()->FillRule());
}
void FillRule::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFillRule(To<CSSIdentifierValue>(value).ConvertTo<blink::WindRule>());
}

 // filter



const char* Filter::GetPropertyName() const {
  return "filter";
}

const AtomicString& Filter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("filter"));
  return name;
}

const char* Filter::GetJSPropertyName() const {
  return "filter";
}


const CSSValue* Filter::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFilterFunctionList(stream, context, local_context);
}

void Filter::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFilter(ComputedStyleInitialValues::InitialFilter());
}
void Filter::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFilter(state.ParentStyle()->Filter());
}

 // flex-basis



const char* FlexBasis::GetPropertyName() const {
  return "flex-basis";
}

const AtomicString& FlexBasis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-basis"));
  return name;
}

const char* FlexBasis::GetJSPropertyName() const {
  return "flexBasis";
}



void FlexBasis::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexBasis(ComputedStyleInitialValues::InitialFlexBasis());
}
void FlexBasis::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetFlexBasis(state.ParentStyle()->FlexBasis());
}
void FlexBasis::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlexBasis(StyleBuilderConverter::ConvertLengthSizing(state, value));
}

 // flex-direction



const char* FlexDirection::GetPropertyName() const {
  return "flex-direction";
}

const AtomicString& FlexDirection::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-direction"));
  return name;
}

const char* FlexDirection::GetJSPropertyName() const {
  return "flexDirection";
}



void FlexDirection::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexDirection(ComputedStyleInitialValues::InitialFlexDirection());
}
void FlexDirection::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexDirection(state.ParentStyle()->FlexDirection());
}
void FlexDirection::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlexDirection(To<CSSIdentifierValue>(value).ConvertTo<blink::EFlexDirection>());
}

 // flex-grow



const char* FlexGrow::GetPropertyName() const {
  return "flex-grow";
}

const AtomicString& FlexGrow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-grow"));
  return name;
}

const char* FlexGrow::GetJSPropertyName() const {
  return "flexGrow";
}



void FlexGrow::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexGrow(ComputedStyleInitialValues::InitialFlexGrow());
}
void FlexGrow::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexGrow(state.ParentStyle()->FlexGrow());
}
void FlexGrow::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlexGrow(To<CSSPrimitiveValue>(value).ConvertTo<float>(state.CssToLengthConversionData()));
}

 // flex-line-count


CSSExposure FlexLineCount::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::FlexWrapBalanceEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* FlexLineCount::GetPropertyName() const {
  return "flex-line-count";
}

const AtomicString& FlexLineCount::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-line-count"));
  return name;
}

const char* FlexLineCount::GetJSPropertyName() const {
  return "flexLineCount";
}



void FlexLineCount::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexLineCount(ComputedStyleInitialValues::InitialFlexLineCount());
}
void FlexLineCount::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexLineCount(state.ParentStyle()->FlexLineCount());
}
void FlexLineCount::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlexLineCount(To<CSSPrimitiveValue>(value).ConvertTo<uint16_t>(state.CssToLengthConversionData()));
}

 // flex-shrink



const char* FlexShrink::GetPropertyName() const {
  return "flex-shrink";
}

const AtomicString& FlexShrink::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-shrink"));
  return name;
}

const char* FlexShrink::GetJSPropertyName() const {
  return "flexShrink";
}



void FlexShrink::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexShrink(ComputedStyleInitialValues::InitialFlexShrink());
}
void FlexShrink::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexShrink(state.ParentStyle()->FlexShrink());
}
void FlexShrink::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlexShrink(To<CSSPrimitiveValue>(value).ConvertTo<float>(state.CssToLengthConversionData()));
}

 // flex-wrap



const char* FlexWrap::GetPropertyName() const {
  return "flex-wrap";
}

const AtomicString& FlexWrap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flex-wrap"));
  return name;
}

const char* FlexWrap::GetJSPropertyName() const {
  return "flexWrap";
}



void FlexWrap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexWrap(ComputedStyleInitialValues::InitialFlexWrap());
}
void FlexWrap::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFlexWrap(state.ParentStyle()->FlexWrap());
}
void FlexWrap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlexWrap(StyleBuilderConverter::ConvertFlexWrapData(state, value));
}

 // float



const char* Float::GetPropertyName() const {
  return "float";
}

const AtomicString& Float::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("float"));
  return name;
}

const char* Float::GetJSPropertyName() const {
  return "float";
}



void Float::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFloating(ComputedStyleInitialValues::InitialFloating());
}
void Float::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFloating(state.ParentStyle()->Floating());
}
void Float::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFloating(To<CSSIdentifierValue>(value).ConvertTo<blink::EFloat>());
}

 // flood-color



const char* FloodColor::GetPropertyName() const {
  return "flood-color";
}

const AtomicString& FloodColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flood-color"));
  return name;
}

const char* FloodColor::GetJSPropertyName() const {
  return "floodColor";
}


const CSSValue* FloodColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void FloodColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFloodColor(ComputedStyleInitialValues::InitialFloodColor());
}

void FloodColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFloodColor(state.ParentStyle()->FloodColor());
}

void FloodColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFloodColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // flood-opacity



const char* FloodOpacity::GetPropertyName() const {
  return "flood-opacity";
}

const AtomicString& FloodOpacity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flood-opacity"));
  return name;
}

const char* FloodOpacity::GetJSPropertyName() const {
  return "floodOpacity";
}


const CSSValue* FloodOpacity::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeAlphaValue(stream, context, local_context);
}

void FloodOpacity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFloodOpacity(ComputedStyleInitialValues::InitialFloodOpacity());
}
void FloodOpacity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFloodOpacity(state.ParentStyle()->FloodOpacity());
}
void FloodOpacity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFloodOpacity(StyleBuilderConverter::ConvertAlpha(state, value));
}

 // flow-tolerance


CSSExposure FlowTolerance::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGridLanesLayoutEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* FlowTolerance::GetPropertyName() const {
  return "flow-tolerance";
}

const AtomicString& FlowTolerance::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("flow-tolerance"));
  return name;
}

const char* FlowTolerance::GetJSPropertyName() const {
  return "flowTolerance";
}


const CSSValue* FlowTolerance::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFlowTolerance(stream, context, local_context);
}

void FlowTolerance::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFlowTolerance(ComputedStyleInitialValues::InitialFlowTolerance());
}
void FlowTolerance::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFlowTolerance(state.ParentStyle()->GetFlowTolerance());
}
void FlowTolerance::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFlowTolerance(StyleBuilderConverter::ConvertFlowTolerance(state, value));
}

 // font-display



const char* FontDisplay::GetPropertyName() const {
  return "font-display";
}

const AtomicString& FontDisplay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("font-display"));
  return name;
}

const char* FontDisplay::GetJSPropertyName() const {
  return "fontDisplay";
}




 // frame-sizing


CSSExposure FrameSizing::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::ResponsiveIframesEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* FrameSizing::GetPropertyName() const {
  return "frame-sizing";
}

const AtomicString& FrameSizing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("frame-sizing"));
  return name;
}

const char* FrameSizing::GetJSPropertyName() const {
  return "frameSizing";
}



void FrameSizing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetFrameSizing(ComputedStyleInitialValues::InitialFrameSizing());
}
void FrameSizing::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetFrameSizing(state.ParentStyle()->FrameSizing());
}
void FrameSizing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetFrameSizing(To<CSSIdentifierValue>(value).ConvertTo<blink::EFrameSizing>());
}

 // grid-auto-columns



const char* GridAutoColumns::GetPropertyName() const {
  return "grid-auto-columns";
}

const AtomicString& GridAutoColumns::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-auto-columns"));
  return name;
}

const char* GridAutoColumns::GetJSPropertyName() const {
  return "gridAutoColumns";
}



void GridAutoColumns::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridAutoColumns(ComputedStyleInitialValues::InitialGridAutoColumns());
}
void GridAutoColumns::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridAutoColumns(state.ParentStyle()->GridAutoColumns());
}
void GridAutoColumns::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridAutoColumns(StyleBuilderConverter::ConvertGridTrackSizeList(state, value));
}

 // grid-auto-flow



const char* GridAutoFlow::GetPropertyName() const {
  return "grid-auto-flow";
}

const AtomicString& GridAutoFlow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-auto-flow"));
  return name;
}

const char* GridAutoFlow::GetJSPropertyName() const {
  return "gridAutoFlow";
}



void GridAutoFlow::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridAutoFlow(ComputedStyleInitialValues::InitialGridAutoFlow());
}
void GridAutoFlow::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridAutoFlow(state.ParentStyle()->GetGridAutoFlow());
}
void GridAutoFlow::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridAutoFlow(StyleBuilderConverter::ConvertGridAutoFlow(state, value));
}

 // grid-auto-rows



const char* GridAutoRows::GetPropertyName() const {
  return "grid-auto-rows";
}

const AtomicString& GridAutoRows::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-auto-rows"));
  return name;
}

const char* GridAutoRows::GetJSPropertyName() const {
  return "gridAutoRows";
}



void GridAutoRows::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridAutoRows(ComputedStyleInitialValues::InitialGridAutoRows());
}
void GridAutoRows::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridAutoRows(state.ParentStyle()->GridAutoRows());
}
void GridAutoRows::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridAutoRows(StyleBuilderConverter::ConvertGridTrackSizeList(state, value));
}

 // grid-column-end



const char* GridColumnEnd::GetPropertyName() const {
  return "grid-column-end";
}

const AtomicString& GridColumnEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-column-end"));
  return name;
}

const char* GridColumnEnd::GetJSPropertyName() const {
  return "gridColumnEnd";
}


const CSSValue* GridColumnEnd::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGridLine(stream, context, local_context);
}

void GridColumnEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridColumnEnd(ComputedStyleInitialValues::InitialGridColumnEnd());
}
void GridColumnEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridColumnEnd(state.ParentStyle()->GridColumnEnd());
}
void GridColumnEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridColumnEnd(StyleBuilderConverter::ConvertGridPosition(state, value));
}

 // grid-column-start



const char* GridColumnStart::GetPropertyName() const {
  return "grid-column-start";
}

const AtomicString& GridColumnStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-column-start"));
  return name;
}

const char* GridColumnStart::GetJSPropertyName() const {
  return "gridColumnStart";
}


const CSSValue* GridColumnStart::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGridLine(stream, context, local_context);
}

void GridColumnStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridColumnStart(ComputedStyleInitialValues::InitialGridColumnStart());
}
void GridColumnStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridColumnStart(state.ParentStyle()->GridColumnStart());
}
void GridColumnStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridColumnStart(StyleBuilderConverter::ConvertGridPosition(state, value));
}

 // grid-lanes-direction


CSSExposure GridLanesDirection::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGridLanesLayoutEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* GridLanesDirection::GetPropertyName() const {
  return "grid-lanes-direction";
}

const AtomicString& GridLanesDirection::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-lanes-direction"));
  return name;
}

const char* GridLanesDirection::GetJSPropertyName() const {
  return "gridLanesDirection";
}



void GridLanesDirection::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridLanesDirection(ComputedStyleInitialValues::InitialGridLanesDirection());
}
void GridLanesDirection::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridLanesDirection(state.ParentStyle()->GetGridLanesDirection());
}
void GridLanesDirection::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridLanesDirection(StyleBuilderConverter::ConvertGridLanesDirection(state, value));
}

 // grid-lanes-pack


CSSExposure GridLanesPack::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGridLanesLayoutEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* GridLanesPack::GetPropertyName() const {
  return "grid-lanes-pack";
}

const AtomicString& GridLanesPack::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-lanes-pack"));
  return name;
}

const char* GridLanesPack::GetJSPropertyName() const {
  return "gridLanesPack";
}



void GridLanesPack::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridLanesPack(ComputedStyleInitialValues::InitialGridLanesPack());
}
void GridLanesPack::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridLanesPack(state.ParentStyle()->GridLanesPack());
}
void GridLanesPack::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridLanesPack(To<CSSIdentifierValue>(value).ConvertTo<blink::EGridLanesPack>());
}

 // grid-row-end



const char* GridRowEnd::GetPropertyName() const {
  return "grid-row-end";
}

const AtomicString& GridRowEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-row-end"));
  return name;
}

const char* GridRowEnd::GetJSPropertyName() const {
  return "gridRowEnd";
}


const CSSValue* GridRowEnd::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGridLine(stream, context, local_context);
}

void GridRowEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridRowEnd(ComputedStyleInitialValues::InitialGridRowEnd());
}
void GridRowEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridRowEnd(state.ParentStyle()->GridRowEnd());
}
void GridRowEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridRowEnd(StyleBuilderConverter::ConvertGridPosition(state, value));
}

 // grid-row-start



const char* GridRowStart::GetPropertyName() const {
  return "grid-row-start";
}

const AtomicString& GridRowStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-row-start"));
  return name;
}

const char* GridRowStart::GetJSPropertyName() const {
  return "gridRowStart";
}


const CSSValue* GridRowStart::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGridLine(stream, context, local_context);
}

void GridRowStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridRowStart(ComputedStyleInitialValues::InitialGridRowStart());
}
void GridRowStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridRowStart(state.ParentStyle()->GridRowStart());
}
void GridRowStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridRowStart(StyleBuilderConverter::ConvertGridPosition(state, value));
}

 // grid-template-areas



const char* GridTemplateAreas::GetPropertyName() const {
  return "grid-template-areas";
}

const AtomicString& GridTemplateAreas::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-template-areas"));
  return name;
}

const char* GridTemplateAreas::GetJSPropertyName() const {
  return "gridTemplateAreas";
}



void GridTemplateAreas::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridTemplateAreas(ComputedStyleInitialValues::InitialGridTemplateAreas());
}
void GridTemplateAreas::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetGridTemplateAreas(state.ParentStyle()->GridTemplateAreas());
}
void GridTemplateAreas::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridTemplateAreas(StyleBuilderConverter::ConvertGridTemplateAreas(state, value));
}

 // grid-template-columns



const char* GridTemplateColumns::GetPropertyName() const {
  return "grid-template-columns";
}

const AtomicString& GridTemplateColumns::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-template-columns"));
  return name;
}

const char* GridTemplateColumns::GetJSPropertyName() const {
  return "gridTemplateColumns";
}


const CSSValue* GridTemplateColumns::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGridTemplatesRowsOrColumns(stream, context, local_context);
}

void GridTemplateColumns::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridTemplateColumns(ComputedStyleInitialValues::InitialGridTemplateColumns());
}
void GridTemplateColumns::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridTemplateColumns(StyleBuilderConverter::ConvertGridTrackList(state, value));
}

 // grid-template-rows



const char* GridTemplateRows::GetPropertyName() const {
  return "grid-template-rows";
}

const AtomicString& GridTemplateRows::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-template-rows"));
  return name;
}

const char* GridTemplateRows::GetJSPropertyName() const {
  return "gridTemplateRows";
}


const CSSValue* GridTemplateRows::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGridTemplatesRowsOrColumns(stream, context, local_context);
}

void GridTemplateRows::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetGridTemplateRows(ComputedStyleInitialValues::InitialGridTemplateRows());
}
void GridTemplateRows::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetGridTemplateRows(StyleBuilderConverter::ConvertGridTrackList(state, value));
}

 // hanging-punctuation


CSSExposure HangingPunctuation::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSHangingPunctuationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* HangingPunctuation::GetPropertyName() const {
  return "hanging-punctuation";
}

const AtomicString& HangingPunctuation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("hanging-punctuation"));
  return name;
}

const char* HangingPunctuation::GetJSPropertyName() const {
  return "hangingPunctuation";
}



void HangingPunctuation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHangingPunctuation(ComputedStyleInitialValues::InitialHangingPunctuation());
}
void HangingPunctuation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetHangingPunctuation(state.ParentStyle()->GetHangingPunctuation());
}
void HangingPunctuation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetHangingPunctuation(StyleBuilderConverter::ConvertFlags<blink::HangingPunctuation>(state, value));
}

 // hash


CSSExposure Hash::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Hash::GetPropertyName() const {
  return "hash";
}

const AtomicString& Hash::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("hash"));
  return name;
}

const char* Hash::GetJSPropertyName() const {
  return "hash";
}




 // height



const char* Height::GetPropertyName() const {
  return "height";
}

const AtomicString& Height::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("height"));
  return name;
}

const char* Height::GetJSPropertyName() const {
  return "height";
}


bool Height::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalSizeMapping().Contains(id);
}
const CSSProperty& Height::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveVertical(writing_direction,
      CSSDirectionAwareResolver::LogicalSizeMapping());
}

void Height::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHeight(ComputedStyleInitialValues::InitialHeight());
}
void Height::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetHeight(state.ParentStyle()->Height());
}
void Height::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kHeight,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetHeight(StyleBuilderConverter::ConvertLengthSizing(state, value));
}

 // hostname


CSSExposure Hostname::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Hostname::GetPropertyName() const {
  return "hostname";
}

const AtomicString& Hostname::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("hostname"));
  return name;
}

const char* Hostname::GetJSPropertyName() const {
  return "hostname";
}




 // hyphenate-character



const char* HyphenateCharacter::GetPropertyName() const {
  return "hyphenate-character";
}

const AtomicString& HyphenateCharacter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("hyphenate-character"));
  return name;
}

const char* HyphenateCharacter::GetJSPropertyName() const {
  return "hyphenateCharacter";
}



void HyphenateCharacter::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHyphenationString(ComputedStyleInitialValues::InitialHyphenationString());
}
void HyphenateCharacter::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetHyphenationString(state.ParentStyle()->HyphenationString());
}
void HyphenateCharacter::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetHyphenationString(StyleBuilderConverter::ConvertString<CSSValueID::kAuto>(state, value));
}

 // hyphenate-limit-chars



const char* HyphenateLimitChars::GetPropertyName() const {
  return "hyphenate-limit-chars";
}

const AtomicString& HyphenateLimitChars::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("hyphenate-limit-chars"));
  return name;
}

const char* HyphenateLimitChars::GetJSPropertyName() const {
  return "hyphenateLimitChars";
}


const CSSValue* HyphenateLimitChars::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeHyphenateLimitChars(stream, context, local_context);
}

void HyphenateLimitChars::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHyphenateLimitChars(ComputedStyleInitialValues::InitialHyphenateLimitChars());
}
void HyphenateLimitChars::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetHyphenateLimitChars(state.ParentStyle()->HyphenateLimitChars());
}
void HyphenateLimitChars::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetHyphenateLimitChars(StyleBuilderConverter::ConvertHyphenateLimitChars(state, value));
}

 // hyphens



const char* Hyphens::GetPropertyName() const {
  return "hyphens";
}

const AtomicString& Hyphens::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("hyphens"));
  return name;
}

const char* Hyphens::GetJSPropertyName() const {
  return "hyphens";
}



void Hyphens::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHyphens(ComputedStyleInitialValues::InitialHyphens());
}
void Hyphens::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetHyphens(state.ParentStyle()->GetHyphens());
}
void Hyphens::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetHyphens(To<CSSIdentifierValue>(value).ConvertTo<blink::Hyphens>());
}

 // image-animation


CSSExposure ImageAnimation::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSImageAnimationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ImageAnimation::GetPropertyName() const {
  return "image-animation";
}

const AtomicString& ImageAnimation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("image-animation"));
  return name;
}

const char* ImageAnimation::GetJSPropertyName() const {
  return "imageAnimation";
}



void ImageAnimation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetImageAnimation(ComputedStyleInitialValues::InitialImageAnimation());
}
void ImageAnimation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetImageAnimation(state.ParentStyle()->ImageAnimation());
}
void ImageAnimation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetImageAnimation(To<CSSIdentifierValue>(value).ConvertTo<blink::ImageAnimationEnum>());
}

 // image-orientation



const char* ImageOrientation::GetPropertyName() const {
  return "image-orientation";
}

const AtomicString& ImageOrientation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("image-orientation"));
  return name;
}

const char* ImageOrientation::GetJSPropertyName() const {
  return "imageOrientation";
}



void ImageOrientation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetImageOrientation(ComputedStyleInitialValues::InitialImageOrientation());
}
void ImageOrientation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetImageOrientation(state.ParentStyle()->ImageOrientation());
}
void ImageOrientation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetImageOrientation(StyleBuilderConverter::ConvertImageOrientation(state, value));
}

 // image-rendering



const char* ImageRendering::GetPropertyName() const {
  return "image-rendering";
}

const AtomicString& ImageRendering::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("image-rendering"));
  return name;
}

const char* ImageRendering::GetJSPropertyName() const {
  return "imageRendering";
}



void ImageRendering::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetImageRendering(ComputedStyleInitialValues::InitialImageRendering());
}
void ImageRendering::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetImageRendering(state.ParentStyle()->ImageRendering());
}
void ImageRendering::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetImageRendering(To<CSSIdentifierValue>(value).ConvertTo<blink::EImageRendering>());
}

 // inherits



const char* Inherits::GetPropertyName() const {
  return "inherits";
}

const AtomicString& Inherits::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inherits"));
  return name;
}

const char* Inherits::GetJSPropertyName() const {
  return "inherits";
}




 // initial-letter



const char* InitialLetter::GetPropertyName() const {
  return "initial-letter";
}

const AtomicString& InitialLetter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("initial-letter"));
  return name;
}

const char* InitialLetter::GetJSPropertyName() const {
  return "initialLetter";
}


const CSSValue* InitialLetter::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeInitialLetter(stream, context, local_context);
}

void InitialLetter::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInitialLetter(ComputedStyleInitialValues::InitialInitialLetter());
}
void InitialLetter::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInitialLetter(state.ParentStyle()->InitialLetter());
}
void InitialLetter::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInitialLetter(StyleBuilderConverter::ConvertInitialLetter(state, value));
}

 // initial-value



const char* InitialValue::GetPropertyName() const {
  return "initial-value";
}

const AtomicString& InitialValue::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("initial-value"));
  return name;
}

const char* InitialValue::GetJSPropertyName() const {
  return "initialValue";
}




 // inline-size



const char* InlineSize::GetPropertyName() const {
  return "inline-size";
}

const AtomicString& InlineSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inline-size"));
  return name;
}

const char* InlineSize::GetJSPropertyName() const {
  return "inlineSize";
}


const CSSProperty* InlineSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InlineSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInline(writing_direction,
      CSSDirectionAwareResolver::PhysicalSizeMapping());
}

bool InlineSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalSizeMapping().Contains(id);
}
const CSSValue* InlineSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeWidthOrHeight(stream, context, local_context);
}


 // inset-block-end



const char* InsetBlockEnd::GetPropertyName() const {
  return "inset-block-end";
}

const AtomicString& InsetBlockEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset-block-end"));
  return name;
}

const char* InsetBlockEnd::GetJSPropertyName() const {
  return "insetBlockEnd";
}


const CSSProperty* InsetBlockEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InsetBlockEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalInsetMapping());
}

bool InsetBlockEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalInsetMapping().Contains(id);
}


 // inset-block-start



const char* InsetBlockStart::GetPropertyName() const {
  return "inset-block-start";
}

const AtomicString& InsetBlockStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset-block-start"));
  return name;
}

const char* InsetBlockStart::GetJSPropertyName() const {
  return "insetBlockStart";
}


const CSSProperty* InsetBlockStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InsetBlockStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalInsetMapping());
}

bool InsetBlockStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalInsetMapping().Contains(id);
}


 // inset-inline-end



const char* InsetInlineEnd::GetPropertyName() const {
  return "inset-inline-end";
}

const AtomicString& InsetInlineEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset-inline-end"));
  return name;
}

const char* InsetInlineEnd::GetJSPropertyName() const {
  return "insetInlineEnd";
}


const CSSProperty* InsetInlineEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InsetInlineEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalInsetMapping());
}

bool InsetInlineEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalInsetMapping().Contains(id);
}


 // inset-inline-start



const char* InsetInlineStart::GetPropertyName() const {
  return "inset-inline-start";
}

const AtomicString& InsetInlineStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("inset-inline-start"));
  return name;
}

const char* InsetInlineStart::GetJSPropertyName() const {
  return "insetInlineStart";
}


const CSSProperty* InsetInlineStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& InsetInlineStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalInsetMapping());
}

bool InsetInlineStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalInsetMapping().Contains(id);
}


 // interactivity



const char* Interactivity::GetPropertyName() const {
  return "interactivity";
}

const AtomicString& Interactivity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("interactivity"));
  return name;
}

const char* Interactivity::GetJSPropertyName() const {
  return "interactivity";
}



void Interactivity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInteractivity(ComputedStyleInitialValues::InitialInteractivity());
  state.StyleBuilder().SetInteractivityIsInherited(false);
}
void Interactivity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInteractivity(state.ParentStyle()->Interactivity());
  state.StyleBuilder().SetInteractivityIsInherited(true);
}
void Interactivity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInteractivity(To<CSSIdentifierValue>(value).ConvertTo<blink::EInteractivity>());
  state.StyleBuilder().SetInteractivityIsInherited(false);
}

 // interest-delay-end



const char* InterestDelayEnd::GetPropertyName() const {
  return "interest-delay-end";
}

const AtomicString& InterestDelayEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("interest-delay-end"));
  return name;
}

const char* InterestDelayEnd::GetJSPropertyName() const {
  return "interestDelayEnd";
}



void InterestDelayEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInterestDelayEnd(ComputedStyleInitialValues::InitialInterestDelayEnd());
}
void InterestDelayEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInterestDelayEnd(state.ParentStyle()->InterestDelayEnd());
}
void InterestDelayEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInterestDelayEnd(StyleBuilderConverter::ConvertInterestDelayValue(state, value));
}

 // interest-delay-start



const char* InterestDelayStart::GetPropertyName() const {
  return "interest-delay-start";
}

const AtomicString& InterestDelayStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("interest-delay-start"));
  return name;
}

const char* InterestDelayStart::GetJSPropertyName() const {
  return "interestDelayStart";
}



void InterestDelayStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInterestDelayStart(ComputedStyleInitialValues::InitialInterestDelayStart());
}
void InterestDelayStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInterestDelayStart(state.ParentStyle()->InterestDelayStart());
}
void InterestDelayStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInterestDelayStart(StyleBuilderConverter::ConvertInterestDelayValue(state, value));
}

 // -internal-align-content-block


CSSExposure InternalAlignContentBlock::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalAlignContentBlock::GetPropertyName() const {
  return "-internal-align-content-block";
}

const AtomicString& InternalAlignContentBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-align-content-block"));
  return name;
}

const char* InternalAlignContentBlock::GetJSPropertyName() const {
  return "internalAlignContentBlock";
}



void InternalAlignContentBlock::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignContentBlockCenter(ComputedStyleInitialValues::InitialAlignContentBlockCenter());
}
void InternalAlignContentBlock::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetAlignContentBlockCenter(state.ParentStyle()->AlignContentBlockCenter());
}
void InternalAlignContentBlock::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetAlignContentBlockCenter(StyleBuilderConverter::ConvertInternalAlignContentBlock(state, value));
}

 // -internal-empty-line-height


CSSExposure InternalEmptyLineHeight::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalEmptyLineHeight::GetPropertyName() const {
  return "-internal-empty-line-height";
}

const AtomicString& InternalEmptyLineHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-empty-line-height"));
  return name;
}

const char* InternalEmptyLineHeight::GetJSPropertyName() const {
  return "internalEmptyLineHeight";
}



void InternalEmptyLineHeight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHasLineIfEmpty(ComputedStyleInitialValues::InitialHasLineIfEmpty());
}
void InternalEmptyLineHeight::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetHasLineIfEmpty(state.ParentStyle()->HasLineIfEmpty());
}
void InternalEmptyLineHeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetHasLineIfEmpty(StyleBuilderConverter::ConvertInternalEmptyLineHeight(state, value));
}

 // -internal-font-size-delta


CSSExposure InternalFontSizeDelta::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalFontSizeDelta::GetPropertyName() const {
  return "-internal-font-size-delta";
}

const AtomicString& InternalFontSizeDelta::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-font-size-delta"));
  return name;
}

const char* InternalFontSizeDelta::GetJSPropertyName() const {
  return "internalFontSizeDelta";
}



void InternalFontSizeDelta::ApplyInitial(StyleResolverState& state) const {
  // Intentionally empty.
}
void InternalFontSizeDelta::ApplyInherit(StyleResolverState& state) const {
  // Intentionally empty.
}
void InternalFontSizeDelta::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  // Intentionally empty.
}

 // -internal-forced-background-color


CSSExposure InternalForcedBackgroundColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalForcedBackgroundColor::GetPropertyName() const {
  return "-internal-forced-background-color";
}

const AtomicString& InternalForcedBackgroundColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-forced-background-color"));
  return name;
}

const char* InternalForcedBackgroundColor::GetJSPropertyName() const {
  return "internalForcedBackgroundColor";
}


const CSSValue* InternalForcedBackgroundColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}

void InternalForcedBackgroundColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalForcedBackgroundColor(ComputedStyleInitialValues::InitialInternalForcedBackgroundColor());
}

void InternalForcedBackgroundColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalForcedBackgroundColor(state.ParentStyle()->InternalForcedBackgroundColor());
}

void InternalForcedBackgroundColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalForcedBackgroundColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // -internal-forced-border-color


CSSExposure InternalForcedBorderColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalForcedBorderColor::GetPropertyName() const {
  return "-internal-forced-border-color";
}

const AtomicString& InternalForcedBorderColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-forced-border-color"));
  return name;
}

const char* InternalForcedBorderColor::GetJSPropertyName() const {
  return "internalForcedBorderColor";
}


const CSSValue* InternalForcedBorderColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}

void InternalForcedBorderColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalForcedBorderColor(StyleColor::CurrentColor());
}

void InternalForcedBorderColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalForcedBorderColor(state.ParentStyle()->InternalForcedBorderColor());
}

void InternalForcedBorderColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalForcedBorderColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // -internal-forced-color


CSSExposure InternalForcedColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalForcedColor::GetPropertyName() const {
  return "-internal-forced-color";
}

const AtomicString& InternalForcedColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-forced-color"));
  return name;
}

const char* InternalForcedColor::GetJSPropertyName() const {
  return "internalForcedColor";
}


const CSSValue* InternalForcedColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}


 // -internal-forced-outline-color


CSSExposure InternalForcedOutlineColor::Exposure(const ExecutionContext* execution_context) const {
  return CSSExposure::kUA;
}

const char* InternalForcedOutlineColor::GetPropertyName() const {
  return "-internal-forced-outline-color";
}

const AtomicString& InternalForcedOutlineColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-forced-outline-color"));
  return name;
}

const char* InternalForcedOutlineColor::GetJSPropertyName() const {
  return "internalForcedOutlineColor";
}


const CSSValue* InternalForcedOutlineColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColorMaybeQuirky(stream, context, local_context);
}

void InternalForcedOutlineColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalForcedOutlineColor(StyleColor::CurrentColor());
}

void InternalForcedOutlineColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalForcedOutlineColor(state.ParentStyle()->InternalForcedOutlineColor());
}

void InternalForcedOutlineColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalForcedOutlineColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // -internal-overscroll-area


CSSExposure InternalOverscrollArea::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::OverscrollGesturesEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kUA;
}

const char* InternalOverscrollArea::GetPropertyName() const {
  return "-internal-overscroll-area";
}

const AtomicString& InternalOverscrollArea::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-overscroll-area"));
  return name;
}

const char* InternalOverscrollArea::GetJSPropertyName() const {
  return "internalOverscrollArea";
}



void InternalOverscrollArea::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalOverscrollArea(ComputedStyleInitialValues::InitialInternalOverscrollArea());
}
void InternalOverscrollArea::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalOverscrollArea(state.ParentStyle()->InternalOverscrollArea());
}
void InternalOverscrollArea::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalOverscrollArea(To<CSSIdentifierValue>(value).ConvertTo<blink::EInternalOverscrollArea>());
}

 // -internal-overscroll-position


CSSExposure InternalOverscrollPosition::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::OverscrollGesturesEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kUA;
}

const char* InternalOverscrollPosition::GetPropertyName() const {
  return "-internal-overscroll-position";
}

const AtomicString& InternalOverscrollPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-internal-overscroll-position"));
  return name;
}

const char* InternalOverscrollPosition::GetJSPropertyName() const {
  return "internalOverscrollPosition";
}



void InternalOverscrollPosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalOverscrollPosition(ComputedStyleInitialValues::InitialInternalOverscrollPosition());
}
void InternalOverscrollPosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInternalOverscrollPosition(state.ParentStyle()->InternalOverscrollPosition());
}
void InternalOverscrollPosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInternalOverscrollPosition(To<CSSIdentifierValue>(value).ConvertTo<blink::EInternalOverscrollPosition>());
}

 // interpolate-size



const char* InterpolateSize::GetPropertyName() const {
  return "interpolate-size";
}

const AtomicString& InterpolateSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("interpolate-size"));
  return name;
}

const char* InterpolateSize::GetJSPropertyName() const {
  return "interpolateSize";
}



void InterpolateSize::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetInterpolateSize(ComputedStyleInitialValues::InitialInterpolateSize());
}
void InterpolateSize::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetInterpolateSize(state.ParentStyle()->InterpolateSize());
}
void InterpolateSize::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetInterpolateSize(To<CSSIdentifierValue>(value).ConvertTo<blink::EInterpolateSize>());
}

 // isolation



const char* Isolation::GetPropertyName() const {
  return "isolation";
}

const AtomicString& Isolation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("isolation"));
  return name;
}

const char* Isolation::GetJSPropertyName() const {
  return "isolation";
}



void Isolation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetIsolation(ComputedStyleInitialValues::InitialIsolation());
}
void Isolation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetIsolation(state.ParentStyle()->Isolation());
}
void Isolation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetIsolation(To<CSSIdentifierValue>(value).ConvertTo<blink::EIsolation>());
}

 // justify-content



const char* JustifyContent::GetPropertyName() const {
  return "justify-content";
}

const AtomicString& JustifyContent::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("justify-content"));
  return name;
}

const char* JustifyContent::GetJSPropertyName() const {
  return "justifyContent";
}



void JustifyContent::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetJustifyContent(ComputedStyleInitialValues::InitialJustifyContent());
}
void JustifyContent::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetJustifyContent(state.ParentStyle()->JustifyContent());
}
void JustifyContent::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetJustifyContent(StyleBuilderConverter::ConvertContentAlignmentData(state, value));
}

 // justify-items



const char* JustifyItems::GetPropertyName() const {
  return "justify-items";
}

const AtomicString& JustifyItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("justify-items"));
  return name;
}

const char* JustifyItems::GetJSPropertyName() const {
  return "justifyItems";
}



void JustifyItems::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetJustifyItems(ComputedStyleInitialValues::InitialJustifyItems());
}
void JustifyItems::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetJustifyItems(state.ParentStyle()->JustifyItems());
}
void JustifyItems::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetJustifyItems(StyleBuilderConverter::ConvertSelfOrDefaultAlignmentData(state, value));
}

 // justify-self



const char* JustifySelf::GetPropertyName() const {
  return "justify-self";
}

const AtomicString& JustifySelf::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("justify-self"));
  return name;
}

const char* JustifySelf::GetJSPropertyName() const {
  return "justifySelf";
}



void JustifySelf::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetJustifySelf(ComputedStyleInitialValues::InitialJustifySelf());
}
void JustifySelf::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetJustifySelf(state.ParentStyle()->JustifySelf());
}
void JustifySelf::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetJustifySelf(StyleBuilderConverter::ConvertSelfOrDefaultAlignmentData(state, value));
}

 // left



const char* Left::GetPropertyName() const {
  return "left";
}

const AtomicString& Left::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("left"));
  return name;
}

const char* Left::GetJSPropertyName() const {
  return "left";
}


bool Left::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalInsetMapping().Contains(id);
}
const CSSProperty& Left::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalInsetMapping());
}

void Left::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetLeft(ComputedStyleInitialValues::InitialLeft());
}
void Left::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetLeft(state.ParentStyle()->Left());
}
void Left::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kLeft,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetLeft(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // letter-spacing



const char* LetterSpacing::GetPropertyName() const {
  return "letter-spacing";
}

const AtomicString& LetterSpacing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("letter-spacing"));
  return name;
}

const char* LetterSpacing::GetJSPropertyName() const {
  return "letterSpacing";
}


const CSSValue* LetterSpacing::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseSpacing(stream, context, local_context);
}

void LetterSpacing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetLetterSpacing(ComputedStyleInitialValues::InitialLetterSpacing());
}
void LetterSpacing::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetLetterSpacing(state.ParentStyle()->ComputedLetterSpacing());
}
void LetterSpacing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetLetterSpacing(StyleBuilderConverter::ConvertSpacing(state, value));
}

 // lighting-color



const char* LightingColor::GetPropertyName() const {
  return "lighting-color";
}

const AtomicString& LightingColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("lighting-color"));
  return name;
}

const char* LightingColor::GetJSPropertyName() const {
  return "lightingColor";
}


const CSSValue* LightingColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void LightingColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetLightingColor(ComputedStyleInitialValues::InitialLightingColor());
}

void LightingColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetLightingColor(state.ParentStyle()->LightingColor());
}

void LightingColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetLightingColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // line-break



const char* LineBreak::GetPropertyName() const {
  return "line-break";
}

const AtomicString& LineBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("line-break"));
  return name;
}

const char* LineBreak::GetJSPropertyName() const {
  return "lineBreak";
}



void LineBreak::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetLineBreak(ComputedStyleInitialValues::InitialLineBreak());
}
void LineBreak::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetLineBreak(state.ParentStyle()->GetLineBreak());
}
void LineBreak::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetLineBreak(To<CSSIdentifierValue>(value).ConvertTo<blink::LineBreak>());
}

 // line-gap-override



const char* LineGapOverride::GetPropertyName() const {
  return "line-gap-override";
}

const AtomicString& LineGapOverride::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("line-gap-override"));
  return name;
}

const char* LineGapOverride::GetJSPropertyName() const {
  return "lineGapOverride";
}




 // line-height



const char* LineHeight::GetPropertyName() const {
  return "line-height";
}

const AtomicString& LineHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("line-height"));
  return name;
}

const char* LineHeight::GetJSPropertyName() const {
  return "lineHeight";
}


const CSSValue* LineHeight::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeLineHeight(stream, context, local_context);
}

void LineHeight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetLineHeight(ComputedStyleInitialValues::InitialLineHeight());
}
void LineHeight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetLineHeight(state.ParentStyle()->LineHeight());
}
void LineHeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetLineHeight(StyleBuilderConverter::ConvertLineHeight(state, value));
}

 // list-style-image



const char* ListStyleImage::GetPropertyName() const {
  return "list-style-image";
}

const AtomicString& ListStyleImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("list-style-image"));
  return name;
}

const char* ListStyleImage::GetJSPropertyName() const {
  return "listStyleImage";
}


const CSSValue* ListStyleImage::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeImageOrNone(stream, context, local_context);
}

void ListStyleImage::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetListStyleImage(ComputedStyleInitialValues::InitialListStyleImage());
}
void ListStyleImage::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetListStyleImage(state.ParentStyle()->ListStyleImage());
}

 // list-style-position



const char* ListStylePosition::GetPropertyName() const {
  return "list-style-position";
}

const AtomicString& ListStylePosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("list-style-position"));
  return name;
}

const char* ListStylePosition::GetJSPropertyName() const {
  return "listStylePosition";
}



void ListStylePosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetListStylePosition(ComputedStyleInitialValues::InitialListStylePosition());
  state.StyleBuilder().SetListStylePositionIsInherited(false);
}
void ListStylePosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetListStylePosition(state.ParentStyle()->ListStylePosition());
  state.StyleBuilder().SetListStylePositionIsInherited(true);
}
void ListStylePosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetListStylePosition(To<CSSIdentifierValue>(value).ConvertTo<blink::EListStylePosition>());
  state.StyleBuilder().SetListStylePositionIsInherited(false);
}

 // list-style-type



const char* ListStyleType::GetPropertyName() const {
  return "list-style-type";
}

const AtomicString& ListStyleType::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("list-style-type"));
  return name;
}

const char* ListStyleType::GetJSPropertyName() const {
  return "listStyleType";
}



void ListStyleType::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetListStyleType(ComputedStyleInitialValues::InitialListStyleType());
}
void ListStyleType::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetListStyleType(state.ParentStyle()->ListStyleType());
}

 // margin-block-end



const char* MarginBlockEnd::GetPropertyName() const {
  return "margin-block-end";
}

const AtomicString& MarginBlockEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-block-end"));
  return name;
}

const char* MarginBlockEnd::GetJSPropertyName() const {
  return "marginBlockEnd";
}


const CSSProperty* MarginBlockEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MarginBlockEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalMarginMapping());
}

bool MarginBlockEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMarginMapping().Contains(id);
}


 // margin-block-start



const char* MarginBlockStart::GetPropertyName() const {
  return "margin-block-start";
}

const AtomicString& MarginBlockStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-block-start"));
  return name;
}

const char* MarginBlockStart::GetJSPropertyName() const {
  return "marginBlockStart";
}


const CSSProperty* MarginBlockStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MarginBlockStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalMarginMapping());
}

bool MarginBlockStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMarginMapping().Contains(id);
}


 // margin-bottom



const char* MarginBottom::GetPropertyName() const {
  return "margin-bottom";
}

const AtomicString& MarginBottom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-bottom"));
  return name;
}

const char* MarginBottom::GetJSPropertyName() const {
  return "marginBottom";
}


bool MarginBottom::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMarginMapping().Contains(id);
}
const CSSProperty& MarginBottom::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalMarginMapping());
}

void MarginBottom::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarginBottom(ComputedStyleInitialValues::InitialMarginBottom());
}
void MarginBottom::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMarginBottom(state.ParentStyle()->MarginBottom());
}
void MarginBottom::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kHeight,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMarginBottom(StyleBuilderConverter::ConvertQuirkyLength(state, value));
}

 // margin-inline-end



const char* MarginInlineEnd::GetPropertyName() const {
  return "margin-inline-end";
}

const AtomicString& MarginInlineEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-inline-end"));
  return name;
}

const char* MarginInlineEnd::GetJSPropertyName() const {
  return "marginInlineEnd";
}


const CSSProperty* MarginInlineEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MarginInlineEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalMarginMapping());
}

bool MarginInlineEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMarginMapping().Contains(id);
}


 // margin-inline-start



const char* MarginInlineStart::GetPropertyName() const {
  return "margin-inline-start";
}

const AtomicString& MarginInlineStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-inline-start"));
  return name;
}

const char* MarginInlineStart::GetJSPropertyName() const {
  return "marginInlineStart";
}


const CSSProperty* MarginInlineStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MarginInlineStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalMarginMapping());
}

bool MarginInlineStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMarginMapping().Contains(id);
}


 // margin-left



const char* MarginLeft::GetPropertyName() const {
  return "margin-left";
}

const AtomicString& MarginLeft::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-left"));
  return name;
}

const char* MarginLeft::GetJSPropertyName() const {
  return "marginLeft";
}


bool MarginLeft::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMarginMapping().Contains(id);
}
const CSSProperty& MarginLeft::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalMarginMapping());
}

void MarginLeft::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarginLeft(ComputedStyleInitialValues::InitialMarginLeft());
}
void MarginLeft::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMarginLeft(state.ParentStyle()->MarginLeft());
}
void MarginLeft::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kWidth,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMarginLeft(StyleBuilderConverter::ConvertQuirkyLength(state, value));
}

 // margin-right



const char* MarginRight::GetPropertyName() const {
  return "margin-right";
}

const AtomicString& MarginRight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-right"));
  return name;
}

const char* MarginRight::GetJSPropertyName() const {
  return "marginRight";
}


bool MarginRight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMarginMapping().Contains(id);
}
const CSSProperty& MarginRight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalMarginMapping());
}

void MarginRight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarginRight(ComputedStyleInitialValues::InitialMarginRight());
}
void MarginRight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMarginRight(state.ParentStyle()->MarginRight());
}
void MarginRight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kWidth,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMarginRight(StyleBuilderConverter::ConvertQuirkyLength(state, value));
}

 // margin-top



const char* MarginTop::GetPropertyName() const {
  return "margin-top";
}

const AtomicString& MarginTop::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-top"));
  return name;
}

const char* MarginTop::GetJSPropertyName() const {
  return "marginTop";
}


bool MarginTop::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMarginMapping().Contains(id);
}
const CSSProperty& MarginTop::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalMarginMapping());
}

void MarginTop::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarginTop(ComputedStyleInitialValues::InitialMarginTop());
}
void MarginTop::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMarginTop(state.ParentStyle()->MarginTop());
}
void MarginTop::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kHeight,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMarginTop(StyleBuilderConverter::ConvertQuirkyLength(state, value));
}

 // margin-trim


CSSExposure MarginTrim::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::MarginTrimEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* MarginTrim::GetPropertyName() const {
  return "margin-trim";
}

const AtomicString& MarginTrim::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("margin-trim"));
  return name;
}

const char* MarginTrim::GetJSPropertyName() const {
  return "marginTrim";
}



void MarginTrim::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarginTrim(ComputedStyleInitialValues::InitialMarginTrim());
}
void MarginTrim::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMarginTrim(state.ParentStyle()->MarginTrim());
}
void MarginTrim::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetMarginTrim(StyleBuilderConverter::ConvertFlags<EMarginTrim>(state, value));
}

 // marker-end



const char* MarkerEnd::GetPropertyName() const {
  return "marker-end";
}

const AtomicString& MarkerEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("marker-end"));
  return name;
}

const char* MarkerEnd::GetJSPropertyName() const {
  return "markerEnd";
}



void MarkerEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarkerEndResource(ComputedStyleInitialValues::InitialMarkerEndResource());
}
void MarkerEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMarkerEndResource(state.ParentStyle()->MarkerEndResource());
}

 // marker-mid



const char* MarkerMid::GetPropertyName() const {
  return "marker-mid";
}

const AtomicString& MarkerMid::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("marker-mid"));
  return name;
}

const char* MarkerMid::GetJSPropertyName() const {
  return "markerMid";
}



void MarkerMid::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarkerMidResource(ComputedStyleInitialValues::InitialMarkerMidResource());
}
void MarkerMid::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMarkerMidResource(state.ParentStyle()->MarkerMidResource());
}

 // marker-start



const char* MarkerStart::GetPropertyName() const {
  return "marker-start";
}

const AtomicString& MarkerStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("marker-start"));
  return name;
}

const char* MarkerStart::GetJSPropertyName() const {
  return "markerStart";
}



void MarkerStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMarkerStartResource(ComputedStyleInitialValues::InitialMarkerStartResource());
}
void MarkerStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMarkerStartResource(state.ParentStyle()->MarkerStartResource());
}

 // mask-clip



const char* MaskClip::GetPropertyName() const {
  return "mask-clip";
}

const AtomicString& MaskClip::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-clip"));
  return name;
}

const char* MaskClip::GetJSPropertyName() const {
  return "maskClip";
}



void MaskClip::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetClip(FillLayer::InitialFillClip(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearClip();
}

void MaskClip::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsClipSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetClip(curr_parent->Clip());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearClip();
    curr_child = curr_child->Next();
  }
}

void MaskClip::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillClip(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillClip(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearClip();
    curr_child = curr_child->Next();
  }
}

 // mask-image



const char* MaskImage::GetPropertyName() const {
  return "mask-image";
}

const AtomicString& MaskImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-image"));
  return name;
}

const char* MaskImage::GetJSPropertyName() const {
  return "maskImage";
}



void MaskImage::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetImage(FillLayer::InitialFillImage(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearImage();
}

void MaskImage::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsImageSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetImage(curr_parent->GetImage());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearImage();
    curr_child = curr_child->Next();
  }
}

void MaskImage::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillImage(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillImage(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearImage();
    curr_child = curr_child->Next();
  }
}

 // mask-mode



const char* MaskMode::GetPropertyName() const {
  return "mask-mode";
}

const AtomicString& MaskMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-mode"));
  return name;
}

const char* MaskMode::GetJSPropertyName() const {
  return "maskMode";
}



void MaskMode::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetMaskMode(FillLayer::InitialFillMaskMode(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearMaskMode();
}

void MaskMode::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsMaskModeSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetMaskMode(curr_parent->MaskMode());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearMaskMode();
    curr_child = curr_child->Next();
  }
}

void MaskMode::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillMaskMode(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillMaskMode(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearMaskMode();
    curr_child = curr_child->Next();
  }
}

 // mask-origin



const char* MaskOrigin::GetPropertyName() const {
  return "mask-origin";
}

const AtomicString& MaskOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-origin"));
  return name;
}

const char* MaskOrigin::GetJSPropertyName() const {
  return "maskOrigin";
}



void MaskOrigin::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetOrigin(FillLayer::InitialFillOrigin(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearOrigin();
}

void MaskOrigin::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsOriginSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetOrigin(curr_parent->Origin());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearOrigin();
    curr_child = curr_child->Next();
  }
}

void MaskOrigin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillOrigin(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillOrigin(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearOrigin();
    curr_child = curr_child->Next();
  }
}

 // mask-repeat



const char* MaskRepeat::GetPropertyName() const {
  return "mask-repeat";
}

const AtomicString& MaskRepeat::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-repeat"));
  return name;
}

const char* MaskRepeat::GetJSPropertyName() const {
  return "maskRepeat";
}



void MaskRepeat::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetRepeat(FillLayer::InitialFillRepeat(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearRepeat();
}

void MaskRepeat::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsRepeatSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetRepeat(curr_parent->Repeat());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearRepeat();
    curr_child = curr_child->Next();
  }
}

void MaskRepeat::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillRepeat(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillRepeat(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearRepeat();
    curr_child = curr_child->Next();
  }
}

 // mask-size



const char* MaskSize::GetPropertyName() const {
  return "mask-size";
}

const AtomicString& MaskSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-size"));
  return name;
}

const char* MaskSize::GetJSPropertyName() const {
  return "maskSize";
}


const CSSValue* MaskSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseMaskSize(stream, context, local_context);
}

void MaskSize::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetSize(FillLayer::InitialFillSize(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearSize();
}

void MaskSize::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsSizeSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetSize(curr_parent->Size());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearSize();
    curr_child = curr_child->Next();
  }
}

void MaskSize::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillSize(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillSize(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearSize();
    curr_child = curr_child->Next();
  }
}

 // mask-type



const char* MaskType::GetPropertyName() const {
  return "mask-type";
}

const AtomicString& MaskType::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-type"));
  return name;
}

const char* MaskType::GetJSPropertyName() const {
  return "maskType";
}



void MaskType::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMaskType(ComputedStyleInitialValues::InitialMaskType());
}
void MaskType::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMaskType(state.ParentStyle()->MaskType());
}
void MaskType::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetMaskType(To<CSSIdentifierValue>(value).ConvertTo<blink::EMaskType>());
}

 // math-shift



const char* MathShift::GetPropertyName() const {
  return "math-shift";
}

const AtomicString& MathShift::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("math-shift"));
  return name;
}

const char* MathShift::GetJSPropertyName() const {
  return "mathShift";
}



void MathShift::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMathShift(ComputedStyleInitialValues::InitialMathShift());
}
void MathShift::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMathShift(state.ParentStyle()->MathShift());
}
void MathShift::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetMathShift(To<CSSIdentifierValue>(value).ConvertTo<blink::EMathShift>());
}

 // math-style



const char* MathStyle::GetPropertyName() const {
  return "math-style";
}

const AtomicString& MathStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("math-style"));
  return name;
}

const char* MathStyle::GetJSPropertyName() const {
  return "mathStyle";
}



void MathStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMathStyle(ComputedStyleInitialValues::InitialMathStyle());
}
void MathStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMathStyle(state.ParentStyle()->MathStyle());
}
void MathStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetMathStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::EMathStyle>());
}

 // max-block-size



const char* MaxBlockSize::GetPropertyName() const {
  return "max-block-size";
}

const AtomicString& MaxBlockSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("max-block-size"));
  return name;
}

const char* MaxBlockSize::GetJSPropertyName() const {
  return "maxBlockSize";
}


const CSSProperty* MaxBlockSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MaxBlockSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlock(writing_direction,
      CSSDirectionAwareResolver::PhysicalMaxSizeMapping());
}

bool MaxBlockSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMaxSizeMapping().Contains(id);
}
const CSSValue* MaxBlockSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeMaxWidthOrHeight(stream, context, local_context);
}


 // max-height



const char* MaxHeight::GetPropertyName() const {
  return "max-height";
}

const AtomicString& MaxHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("max-height"));
  return name;
}

const char* MaxHeight::GetJSPropertyName() const {
  return "maxHeight";
}


bool MaxHeight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMaxSizeMapping().Contains(id);
}
const CSSProperty& MaxHeight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveVertical(writing_direction,
      CSSDirectionAwareResolver::LogicalMaxSizeMapping());
}

void MaxHeight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMaxHeight(ComputedStyleInitialValues::InitialMaxHeight());
}
void MaxHeight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMaxHeight(state.ParentStyle()->MaxHeight());
}
void MaxHeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kHeight,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMaxHeight(StyleBuilderConverter::ConvertLengthMaxSizing(state, value));
}

 // max-inline-size



const char* MaxInlineSize::GetPropertyName() const {
  return "max-inline-size";
}

const AtomicString& MaxInlineSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("max-inline-size"));
  return name;
}

const char* MaxInlineSize::GetJSPropertyName() const {
  return "maxInlineSize";
}


const CSSProperty* MaxInlineSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MaxInlineSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInline(writing_direction,
      CSSDirectionAwareResolver::PhysicalMaxSizeMapping());
}

bool MaxInlineSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMaxSizeMapping().Contains(id);
}
const CSSValue* MaxInlineSize::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeMaxWidthOrHeight(stream, context, local_context);
}


 // max-lines


CSSExposure MaxLines::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSLineClampEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* MaxLines::GetPropertyName() const {
  return "max-lines";
}

const AtomicString& MaxLines::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("max-lines"));
  return name;
}

const char* MaxLines::GetJSPropertyName() const {
  return "maxLines";
}



void MaxLines::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMaxLines(ComputedStyleInitialValues::InitialMaxLines());
}
void MaxLines::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMaxLines(state.ParentStyle()->MaxLines());
}
void MaxLines::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetMaxLines(StyleBuilderConverter::ConvertIntegerOrNone<0>(state, value));
}

 // max-width



const char* MaxWidth::GetPropertyName() const {
  return "max-width";
}

const AtomicString& MaxWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("max-width"));
  return name;
}

const char* MaxWidth::GetJSPropertyName() const {
  return "maxWidth";
}


bool MaxWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMaxSizeMapping().Contains(id);
}
const CSSProperty& MaxWidth::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveHorizontal(writing_direction,
      CSSDirectionAwareResolver::LogicalMaxSizeMapping());
}

void MaxWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMaxWidth(ComputedStyleInitialValues::InitialMaxWidth());
}
void MaxWidth::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMaxWidth(state.ParentStyle()->MaxWidth());
}
void MaxWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kWidth,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMaxWidth(StyleBuilderConverter::ConvertLengthMaxSizing(state, value));
}

 // min-block-size



const char* MinBlockSize::GetPropertyName() const {
  return "min-block-size";
}

const AtomicString& MinBlockSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("min-block-size"));
  return name;
}

const char* MinBlockSize::GetJSPropertyName() const {
  return "minBlockSize";
}


const CSSProperty* MinBlockSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MinBlockSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlock(writing_direction,
      CSSDirectionAwareResolver::PhysicalMinSizeMapping());
}

bool MinBlockSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMinSizeMapping().Contains(id);
}


 // min-height



const char* MinHeight::GetPropertyName() const {
  return "min-height";
}

const AtomicString& MinHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("min-height"));
  return name;
}

const char* MinHeight::GetJSPropertyName() const {
  return "minHeight";
}


bool MinHeight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMinSizeMapping().Contains(id);
}
const CSSProperty& MinHeight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveVertical(writing_direction,
      CSSDirectionAwareResolver::LogicalMinSizeMapping());
}

void MinHeight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMinHeight(ComputedStyleInitialValues::InitialMinHeight());
}
void MinHeight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMinHeight(state.ParentStyle()->MinHeight());
}
void MinHeight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kHeight,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMinHeight(StyleBuilderConverter::ConvertLengthSizing(state, value));
}

 // min-inline-size



const char* MinInlineSize::GetPropertyName() const {
  return "min-inline-size";
}

const AtomicString& MinInlineSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("min-inline-size"));
  return name;
}

const char* MinInlineSize::GetJSPropertyName() const {
  return "minInlineSize";
}


const CSSProperty* MinInlineSize::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& MinInlineSize::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInline(writing_direction,
      CSSDirectionAwareResolver::PhysicalMinSizeMapping());
}

bool MinInlineSize::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalMinSizeMapping().Contains(id);
}


 // min-width



const char* MinWidth::GetPropertyName() const {
  return "min-width";
}

const AtomicString& MinWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("min-width"));
  return name;
}

const char* MinWidth::GetJSPropertyName() const {
  return "minWidth";
}


bool MinWidth::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalMinSizeMapping().Contains(id);
}
const CSSProperty& MinWidth::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveHorizontal(writing_direction,
      CSSDirectionAwareResolver::LogicalMinSizeMapping());
}

void MinWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMinWidth(ComputedStyleInitialValues::InitialMinWidth());
}
void MinWidth::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetMinWidth(state.ParentStyle()->MinWidth());
}
void MinWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kWidth,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetMinWidth(StyleBuilderConverter::ConvertLengthSizing(state, value));
}

 // mix-blend-mode



const char* MixBlendMode::GetPropertyName() const {
  return "mix-blend-mode";
}

const AtomicString& MixBlendMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mix-blend-mode"));
  return name;
}

const char* MixBlendMode::GetJSPropertyName() const {
  return "mixBlendMode";
}



void MixBlendMode::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBlendMode(ComputedStyleInitialValues::InitialBlendMode());
}
void MixBlendMode::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBlendMode(state.ParentStyle()->GetBlendMode());
}
void MixBlendMode::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBlendMode(To<CSSIdentifierValue>(value).ConvertTo<blink::BlendMode>());
}

 // navigation



const char* Navigation::GetPropertyName() const {
  return "navigation";
}

const AtomicString& Navigation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("navigation"));
  return name;
}

const char* Navigation::GetJSPropertyName() const {
  return "navigation";
}




 // negative



const char* Negative::GetPropertyName() const {
  return "negative";
}

const AtomicString& Negative::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("negative"));
  return name;
}

const char* Negative::GetJSPropertyName() const {
  return "negative";
}




 // object-fit



const char* ObjectFit::GetPropertyName() const {
  return "object-fit";
}

const AtomicString& ObjectFit::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("object-fit"));
  return name;
}

const char* ObjectFit::GetJSPropertyName() const {
  return "objectFit";
}



void ObjectFit::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetObjectFit(ComputedStyleInitialValues::InitialObjectFit());
}
void ObjectFit::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetObjectFit(state.ParentStyle()->GetObjectFit());
}
void ObjectFit::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetObjectFit(To<CSSIdentifierValue>(value).ConvertTo<blink::EObjectFit>());
}

 // object-position



const char* ObjectPosition::GetPropertyName() const {
  return "object-position";
}

const AtomicString& ObjectPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("object-position"));
  return name;
}

const char* ObjectPosition::GetJSPropertyName() const {
  return "objectPosition";
}



void ObjectPosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetObjectPosition(ComputedStyleInitialValues::InitialObjectPosition());
}
void ObjectPosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetObjectPosition(state.ParentStyle()->ObjectPosition());
}
void ObjectPosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetObjectPosition(StyleBuilderConverter::ConvertPosition(state, value));
}

 // object-view-box



const char* ObjectViewBox::GetPropertyName() const {
  return "object-view-box";
}

const AtomicString& ObjectViewBox::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("object-view-box"));
  return name;
}

const char* ObjectViewBox::GetJSPropertyName() const {
  return "objectViewBox";
}



void ObjectViewBox::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetObjectViewBox(ComputedStyleInitialValues::InitialObjectViewBox());
}
void ObjectViewBox::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetObjectViewBox(state.ParentStyle()->ObjectViewBox());
}
void ObjectViewBox::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetObjectViewBox(StyleBuilderConverter::ConvertObjectViewBox(state, value));
}

 // offset-anchor



const char* OffsetAnchor::GetPropertyName() const {
  return "offset-anchor";
}

const AtomicString& OffsetAnchor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("offset-anchor"));
  return name;
}

const char* OffsetAnchor::GetJSPropertyName() const {
  return "offsetAnchor";
}



void OffsetAnchor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetAnchor(ComputedStyleInitialValues::InitialOffsetAnchor());
}
void OffsetAnchor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetAnchor(state.ParentStyle()->OffsetAnchor());
}
void OffsetAnchor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOffsetAnchor(StyleBuilderConverter::ConvertPositionOrAuto(state, value));
}

 // offset-distance



const char* OffsetDistance::GetPropertyName() const {
  return "offset-distance";
}

const AtomicString& OffsetDistance::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("offset-distance"));
  return name;
}

const char* OffsetDistance::GetJSPropertyName() const {
  return "offsetDistance";
}



void OffsetDistance::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetDistance(ComputedStyleInitialValues::InitialOffsetDistance());
}
void OffsetDistance::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetDistance(state.ParentStyle()->OffsetDistance());
}
void OffsetDistance::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOffsetDistance(StyleBuilderConverter::ConvertLength(state, value));
}

 // offset-path



const char* OffsetPath::GetPropertyName() const {
  return "offset-path";
}

const AtomicString& OffsetPath::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("offset-path"));
  return name;
}

const char* OffsetPath::GetJSPropertyName() const {
  return "offsetPath";
}


const CSSValue* OffsetPath::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeOffsetPath(stream, context, local_context);
}

void OffsetPath::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetPath(ComputedStyleInitialValues::InitialOffsetPath());
}
void OffsetPath::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetPath(state.ParentStyle()->OffsetPath());
}
void OffsetPath::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOffsetPath(StyleBuilderConverter::ConvertOffsetPath(state, value));
}

 // offset-position



const char* OffsetPosition::GetPropertyName() const {
  return "offset-position";
}

const AtomicString& OffsetPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("offset-position"));
  return name;
}

const char* OffsetPosition::GetJSPropertyName() const {
  return "offsetPosition";
}



void OffsetPosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetPosition(ComputedStyleInitialValues::InitialOffsetPosition());
}
void OffsetPosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetPosition(state.ParentStyle()->OffsetPosition());
}
void OffsetPosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOffsetPosition(StyleBuilderConverter::ConvertOffsetPosition(state, value));
}

 // offset-rotate



const char* OffsetRotate::GetPropertyName() const {
  return "offset-rotate";
}

const AtomicString& OffsetRotate::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("offset-rotate"));
  return name;
}

const char* OffsetRotate::GetJSPropertyName() const {
  return "offsetRotate";
}


const CSSValue* OffsetRotate::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeOffsetRotate(stream, context, local_context);
}

void OffsetRotate::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetRotate(ComputedStyleInitialValues::InitialOffsetRotate());
}
void OffsetRotate::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOffsetRotate(state.ParentStyle()->OffsetRotate());
}
void OffsetRotate::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOffsetRotate(StyleBuilderConverter::ConvertOffsetRotate(state, value));
}

 // opacity



const char* Opacity::GetPropertyName() const {
  return "opacity";
}

const AtomicString& Opacity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("opacity"));
  return name;
}

const char* Opacity::GetJSPropertyName() const {
  return "opacity";
}


const CSSValue* Opacity::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeAlphaValue(stream, context, local_context);
}

void Opacity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOpacity(ComputedStyleInitialValues::InitialOpacity());
}
void Opacity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOpacity(state.ParentStyle()->Opacity());
}
void Opacity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOpacity(To<CSSPrimitiveValue>(value).ConvertTo<float>(state.CssToLengthConversionData()));
}

 // order



const char* Order::GetPropertyName() const {
  return "order";
}

const AtomicString& Order::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("order"));
  return name;
}

const char* Order::GetJSPropertyName() const {
  return "order";
}


const CSSValue* Order::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeInteger(stream, context, local_context);
}

void Order::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOrder(ComputedStyleInitialValues::InitialOrder());
}
void Order::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOrder(state.ParentStyle()->Order());
}
void Order::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOrder(To<CSSPrimitiveValue>(value).ConvertTo<int>(state.CssToLengthConversionData()));
}

 // origin-trial-test-property


CSSExposure OriginTrialTestProperty::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::OriginTrialsSampleAPIEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* OriginTrialTestProperty::GetPropertyName() const {
  return "origin-trial-test-property";
}

const AtomicString& OriginTrialTestProperty::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("origin-trial-test-property"));
  return name;
}

const char* OriginTrialTestProperty::GetJSPropertyName() const {
  return "originTrialTestProperty";
}



void OriginTrialTestProperty::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOriginTrialTestProperty(ComputedStyleInitialValues::InitialOriginTrialTestProperty());
}
void OriginTrialTestProperty::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOriginTrialTestProperty(state.ParentStyle()->OriginTrialTestProperty());
}
void OriginTrialTestProperty::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOriginTrialTestProperty(To<CSSIdentifierValue>(value).ConvertTo<blink::EOriginTrialTestProperty>());
}

 // orphans



const char* Orphans::GetPropertyName() const {
  return "orphans";
}

const AtomicString& Orphans::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("orphans"));
  return name;
}

const char* Orphans::GetJSPropertyName() const {
  return "orphans";
}


const CSSValue* Orphans::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumePositiveInteger(stream, context, local_context);
}

void Orphans::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOrphans(ComputedStyleInitialValues::InitialOrphans());
}
void Orphans::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOrphans(state.ParentStyle()->Orphans());
}
void Orphans::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOrphans(To<CSSPrimitiveValue>(value).ConvertTo<short>(state.CssToLengthConversionData()));
}

 // outline-color



const char* OutlineColor::GetPropertyName() const {
  return "outline-color";
}

const AtomicString& OutlineColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("outline-color"));
  return name;
}

const char* OutlineColor::GetJSPropertyName() const {
  return "outlineColor";
}



void OutlineColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOutlineColor(StyleColor::CurrentColor());
}

void OutlineColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOutlineColor(state.ParentStyle()->OutlineColor());
}

void OutlineColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOutlineColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // outline-offset



const char* OutlineOffset::GetPropertyName() const {
  return "outline-offset";
}

const AtomicString& OutlineOffset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("outline-offset"));
  return name;
}

const char* OutlineOffset::GetJSPropertyName() const {
  return "outlineOffset";
}



void OutlineOffset::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOutlineOffset(ComputedStyleInitialValues::InitialOutlineOffset());
}
void OutlineOffset::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetOutlineOffset(state.ParentStyle()->OutlineOffset());
}
void OutlineOffset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOutlineOffset(StyleBuilderConverter::ConvertOutlineOffset(state, value));
}

 // outline-style



const char* OutlineStyle::GetPropertyName() const {
  return "outline-style";
}

const AtomicString& OutlineStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("outline-style"));
  return name;
}

const char* OutlineStyle::GetJSPropertyName() const {
  return "outlineStyle";
}




 // outline-width



const char* OutlineWidth::GetPropertyName() const {
  return "outline-width";
}

const AtomicString& OutlineWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("outline-width"));
  return name;
}

const char* OutlineWidth::GetJSPropertyName() const {
  return "outlineWidth";
}



void OutlineWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOutlineWidth(StyleBuilderConverter::ConvertBorderWidth(state, value));
}

 // overflow-anchor



const char* OverflowAnchor::GetPropertyName() const {
  return "overflow-anchor";
}

const AtomicString& OverflowAnchor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-anchor"));
  return name;
}

const char* OverflowAnchor::GetJSPropertyName() const {
  return "overflowAnchor";
}



void OverflowAnchor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOverflowAnchor(ComputedStyleInitialValues::InitialOverflowAnchor());
}
void OverflowAnchor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOverflowAnchor(state.ParentStyle()->OverflowAnchor());
}
void OverflowAnchor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOverflowAnchor(To<CSSIdentifierValue>(value).ConvertTo<blink::EOverflowAnchor>());
}

 // overflow-block



const char* OverflowBlock::GetPropertyName() const {
  return "overflow-block";
}

const AtomicString& OverflowBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-block"));
  return name;
}

const char* OverflowBlock::GetJSPropertyName() const {
  return "overflowBlock";
}


const CSSProperty* OverflowBlock::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& OverflowBlock::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlock(writing_direction,
      CSSDirectionAwareResolver::PhysicalOverflowMapping());
}

bool OverflowBlock::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalOverflowMapping().Contains(id);
}


 // overflow-clip-margin



const char* OverflowClipMargin::GetPropertyName() const {
  return "overflow-clip-margin";
}

const AtomicString& OverflowClipMargin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-clip-margin"));
  return name;
}

const char* OverflowClipMargin::GetJSPropertyName() const {
  return "overflowClipMargin";
}



void OverflowClipMargin::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOverflowClipMargin(ComputedStyleInitialValues::InitialOverflowClipMargin());
}
void OverflowClipMargin::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOverflowClipMargin(state.ParentStyle()->OverflowClipMargin());
}
void OverflowClipMargin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOverflowClipMargin(StyleBuilderConverter::ConvertOverflowClipMargin(state, value));
}

 // overflow-inline



const char* OverflowInline::GetPropertyName() const {
  return "overflow-inline";
}

const AtomicString& OverflowInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-inline"));
  return name;
}

const char* OverflowInline::GetJSPropertyName() const {
  return "overflowInline";
}


const CSSProperty* OverflowInline::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& OverflowInline::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInline(writing_direction,
      CSSDirectionAwareResolver::PhysicalOverflowMapping());
}

bool OverflowInline::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalOverflowMapping().Contains(id);
}


 // overflow-wrap



const char* OverflowWrap::GetPropertyName() const {
  return "overflow-wrap";
}

const AtomicString& OverflowWrap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-wrap"));
  return name;
}

const char* OverflowWrap::GetJSPropertyName() const {
  return "overflowWrap";
}



void OverflowWrap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOverflowWrap(ComputedStyleInitialValues::InitialOverflowWrap());
}
void OverflowWrap::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOverflowWrap(state.ParentStyle()->OverflowWrap());
}
void OverflowWrap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOverflowWrap(To<CSSIdentifierValue>(value).ConvertTo<blink::EOverflowWrap>());
}

 // overflow-x



const char* OverflowX::GetPropertyName() const {
  return "overflow-x";
}

const AtomicString& OverflowX::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-x"));
  return name;
}

const char* OverflowX::GetJSPropertyName() const {
  return "overflowX";
}


bool OverflowX::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalOverflowMapping().Contains(id);
}
const CSSProperty& OverflowX::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveHorizontal(writing_direction,
      CSSDirectionAwareResolver::LogicalOverflowMapping());
}


 // overflow-y



const char* OverflowY::GetPropertyName() const {
  return "overflow-y";
}

const AtomicString& OverflowY::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overflow-y"));
  return name;
}

const char* OverflowY::GetJSPropertyName() const {
  return "overflowY";
}


bool OverflowY::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalOverflowMapping().Contains(id);
}
const CSSProperty& OverflowY::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveVertical(writing_direction,
      CSSDirectionAwareResolver::LogicalOverflowMapping());
}


 // overlay


CSSExposure Overlay::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::OverlayPropertyEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Overlay::GetPropertyName() const {
  return "overlay";
}

const AtomicString& Overlay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overlay"));
  return name;
}

const char* Overlay::GetJSPropertyName() const {
  return "overlay";
}



void Overlay::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOverlay(ComputedStyleInitialValues::InitialOverlay());
}
void Overlay::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOverlay(state.ParentStyle()->Overlay());
}
void Overlay::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOverlay(To<CSSIdentifierValue>(value).ConvertTo<blink::EOverlay>());
}

 // override-colors



const char* OverrideColors::GetPropertyName() const {
  return "override-colors";
}

const AtomicString& OverrideColors::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("override-colors"));
  return name;
}

const char* OverrideColors::GetJSPropertyName() const {
  return "overrideColors";
}




 // overscroll-behavior-block



const char* OverscrollBehaviorBlock::GetPropertyName() const {
  return "overscroll-behavior-block";
}

const AtomicString& OverscrollBehaviorBlock::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overscroll-behavior-block"));
  return name;
}

const char* OverscrollBehaviorBlock::GetJSPropertyName() const {
  return "overscrollBehaviorBlock";
}


const CSSProperty* OverscrollBehaviorBlock::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& OverscrollBehaviorBlock::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlock(writing_direction,
      CSSDirectionAwareResolver::PhysicalOverscrollBehaviorMapping());
}

bool OverscrollBehaviorBlock::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalOverscrollBehaviorMapping().Contains(id);
}


 // overscroll-behavior-inline



const char* OverscrollBehaviorInline::GetPropertyName() const {
  return "overscroll-behavior-inline";
}

const AtomicString& OverscrollBehaviorInline::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overscroll-behavior-inline"));
  return name;
}

const char* OverscrollBehaviorInline::GetJSPropertyName() const {
  return "overscrollBehaviorInline";
}


const CSSProperty* OverscrollBehaviorInline::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& OverscrollBehaviorInline::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInline(writing_direction,
      CSSDirectionAwareResolver::PhysicalOverscrollBehaviorMapping());
}

bool OverscrollBehaviorInline::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalOverscrollBehaviorMapping().Contains(id);
}


 // overscroll-behavior-x



const char* OverscrollBehaviorX::GetPropertyName() const {
  return "overscroll-behavior-x";
}

const AtomicString& OverscrollBehaviorX::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overscroll-behavior-x"));
  return name;
}

const char* OverscrollBehaviorX::GetJSPropertyName() const {
  return "overscrollBehaviorX";
}


bool OverscrollBehaviorX::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalOverscrollBehaviorMapping().Contains(id);
}
const CSSProperty& OverscrollBehaviorX::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveHorizontal(writing_direction,
      CSSDirectionAwareResolver::LogicalOverscrollBehaviorMapping());
}

void OverscrollBehaviorX::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOverscrollBehaviorX(ComputedStyleInitialValues::InitialOverscrollBehaviorX());
}
void OverscrollBehaviorX::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOverscrollBehaviorX(state.ParentStyle()->OverscrollBehaviorX());
}
void OverscrollBehaviorX::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOverscrollBehaviorX(To<CSSIdentifierValue>(value).ConvertTo<blink::EOverscrollBehavior>());
}

 // overscroll-behavior-y



const char* OverscrollBehaviorY::GetPropertyName() const {
  return "overscroll-behavior-y";
}

const AtomicString& OverscrollBehaviorY::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("overscroll-behavior-y"));
  return name;
}

const char* OverscrollBehaviorY::GetJSPropertyName() const {
  return "overscrollBehaviorY";
}


bool OverscrollBehaviorY::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalOverscrollBehaviorMapping().Contains(id);
}
const CSSProperty& OverscrollBehaviorY::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveVertical(writing_direction,
      CSSDirectionAwareResolver::LogicalOverscrollBehaviorMapping());
}

void OverscrollBehaviorY::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetOverscrollBehaviorY(ComputedStyleInitialValues::InitialOverscrollBehaviorY());
}
void OverscrollBehaviorY::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetOverscrollBehaviorY(state.ParentStyle()->OverscrollBehaviorY());
}
void OverscrollBehaviorY::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetOverscrollBehaviorY(To<CSSIdentifierValue>(value).ConvertTo<blink::EOverscrollBehavior>());
}

 // pad



const char* Pad::GetPropertyName() const {
  return "pad";
}

const AtomicString& Pad::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("pad"));
  return name;
}

const char* Pad::GetJSPropertyName() const {
  return "pad";
}




 // padding-block-end



const char* PaddingBlockEnd::GetPropertyName() const {
  return "padding-block-end";
}

const AtomicString& PaddingBlockEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-block-end"));
  return name;
}

const char* PaddingBlockEnd::GetJSPropertyName() const {
  return "paddingBlockEnd";
}


const CSSProperty* PaddingBlockEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& PaddingBlockEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalPaddingMapping());
}

bool PaddingBlockEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalPaddingMapping().Contains(id);
}


 // padding-block-start



const char* PaddingBlockStart::GetPropertyName() const {
  return "padding-block-start";
}

const AtomicString& PaddingBlockStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-block-start"));
  return name;
}

const char* PaddingBlockStart::GetJSPropertyName() const {
  return "paddingBlockStart";
}


const CSSProperty* PaddingBlockStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& PaddingBlockStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalPaddingMapping());
}

bool PaddingBlockStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalPaddingMapping().Contains(id);
}


 // padding-bottom



const char* PaddingBottom::GetPropertyName() const {
  return "padding-bottom";
}

const AtomicString& PaddingBottom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-bottom"));
  return name;
}

const char* PaddingBottom::GetJSPropertyName() const {
  return "paddingBottom";
}


bool PaddingBottom::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalPaddingMapping().Contains(id);
}
const CSSProperty& PaddingBottom::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalPaddingMapping());
}

void PaddingBottom::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPaddingBottom(ComputedStyleInitialValues::InitialPaddingBottom());
}
void PaddingBottom::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetPaddingBottom(state.ParentStyle()->PaddingBottom());
}
void PaddingBottom::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPaddingBottom(StyleBuilderConverter::ConvertLength(state, value));
}

 // padding-inline-end



const char* PaddingInlineEnd::GetPropertyName() const {
  return "padding-inline-end";
}

const AtomicString& PaddingInlineEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-inline-end"));
  return name;
}

const char* PaddingInlineEnd::GetJSPropertyName() const {
  return "paddingInlineEnd";
}


const CSSProperty* PaddingInlineEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& PaddingInlineEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalPaddingMapping());
}

bool PaddingInlineEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalPaddingMapping().Contains(id);
}


 // padding-inline-start



const char* PaddingInlineStart::GetPropertyName() const {
  return "padding-inline-start";
}

const AtomicString& PaddingInlineStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-inline-start"));
  return name;
}

const char* PaddingInlineStart::GetJSPropertyName() const {
  return "paddingInlineStart";
}


const CSSProperty* PaddingInlineStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& PaddingInlineStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalPaddingMapping());
}

bool PaddingInlineStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalPaddingMapping().Contains(id);
}


 // padding-left



const char* PaddingLeft::GetPropertyName() const {
  return "padding-left";
}

const AtomicString& PaddingLeft::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-left"));
  return name;
}

const char* PaddingLeft::GetJSPropertyName() const {
  return "paddingLeft";
}


bool PaddingLeft::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalPaddingMapping().Contains(id);
}
const CSSProperty& PaddingLeft::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalPaddingMapping());
}

void PaddingLeft::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPaddingLeft(ComputedStyleInitialValues::InitialPaddingLeft());
}
void PaddingLeft::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetPaddingLeft(state.ParentStyle()->PaddingLeft());
}
void PaddingLeft::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPaddingLeft(StyleBuilderConverter::ConvertLength(state, value));
}

 // padding-right



const char* PaddingRight::GetPropertyName() const {
  return "padding-right";
}

const AtomicString& PaddingRight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-right"));
  return name;
}

const char* PaddingRight::GetJSPropertyName() const {
  return "paddingRight";
}


bool PaddingRight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalPaddingMapping().Contains(id);
}
const CSSProperty& PaddingRight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalPaddingMapping());
}

void PaddingRight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPaddingRight(ComputedStyleInitialValues::InitialPaddingRight());
}
void PaddingRight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetPaddingRight(state.ParentStyle()->PaddingRight());
}
void PaddingRight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPaddingRight(StyleBuilderConverter::ConvertLength(state, value));
}

 // padding-top



const char* PaddingTop::GetPropertyName() const {
  return "padding-top";
}

const AtomicString& PaddingTop::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("padding-top"));
  return name;
}

const char* PaddingTop::GetJSPropertyName() const {
  return "paddingTop";
}


bool PaddingTop::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalPaddingMapping().Contains(id);
}
const CSSProperty& PaddingTop::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalPaddingMapping());
}

void PaddingTop::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPaddingTop(ComputedStyleInitialValues::InitialPaddingTop());
}
void PaddingTop::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetPaddingTop(state.ParentStyle()->PaddingTop());
}
void PaddingTop::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPaddingTop(StyleBuilderConverter::ConvertLength(state, value));
}

 // page



const char* Page::GetPropertyName() const {
  return "page";
}

const AtomicString& Page::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("page"));
  return name;
}

const char* Page::GetJSPropertyName() const {
  return "page";
}



void Page::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPage(ComputedStyleInitialValues::InitialPage());
}
void Page::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPage(state.ParentStyle()->Page());
}
void Page::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPage(StyleBuilderConverter::ConvertPage(state, value));
}

 // page-margin-safety


CSSExposure PageMarginSafety::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSSafePrintableInsetEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* PageMarginSafety::GetPropertyName() const {
  return "page-margin-safety";
}

const AtomicString& PageMarginSafety::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("page-margin-safety"));
  return name;
}

const char* PageMarginSafety::GetJSPropertyName() const {
  return "pageMarginSafety";
}



void PageMarginSafety::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPageMarginSafety(ComputedStyleInitialValues::InitialPageMarginSafety());
}
void PageMarginSafety::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPageMarginSafety(state.ParentStyle()->GetPageMarginSafety());
}
void PageMarginSafety::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPageMarginSafety(To<CSSIdentifierValue>(value).ConvertTo<blink::EPageMarginSafety>());
}

 // page-orientation



const char* PageOrientation::GetPropertyName() const {
  return "page-orientation";
}

const AtomicString& PageOrientation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("page-orientation"));
  return name;
}

const char* PageOrientation::GetJSPropertyName() const {
  return "pageOrientation";
}



void PageOrientation::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPageOrientation(ComputedStyleInitialValues::InitialPageOrientation());
}
void PageOrientation::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPageOrientation(state.ParentStyle()->GetPageOrientation());
}
void PageOrientation::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPageOrientation(To<CSSIdentifierValue>(value).ConvertTo<blink::PageOrientation>());
}

 // paint-order



const char* PaintOrder::GetPropertyName() const {
  return "paint-order";
}

const AtomicString& PaintOrder::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("paint-order"));
  return name;
}

const char* PaintOrder::GetJSPropertyName() const {
  return "paintOrder";
}



void PaintOrder::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPaintOrder(ComputedStyleInitialValues::InitialPaintOrder());
}
void PaintOrder::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPaintOrder(state.ParentStyle()->PaintOrder());
}
void PaintOrder::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPaintOrder(StyleBuilderConverter::ConvertPaintOrder(state, value));
}

 // path-length


CSSExposure PathLength::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::SvgPathLengthCssPropertyEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* PathLength::GetPropertyName() const {
  return "path-length";
}

const AtomicString& PathLength::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("path-length"));
  return name;
}

const char* PathLength::GetJSPropertyName() const {
  return "pathLength";
}



void PathLength::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPathLength(ComputedStyleInitialValues::InitialPathLength());
}
void PathLength::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPathLength(state.ParentStyle()->PathLength());
}
void PathLength::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPathLength(StyleBuilderConverter::ConvertPathLength(state, value));
}

 // pathname


CSSExposure Pathname::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Pathname::GetPropertyName() const {
  return "pathname";
}

const AtomicString& Pathname::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("pathname"));
  return name;
}

const char* Pathname::GetJSPropertyName() const {
  return "pathname";
}




 // pattern


CSSExposure Pattern::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Pattern::GetPropertyName() const {
  return "pattern";
}

const AtomicString& Pattern::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("pattern"));
  return name;
}

const char* Pattern::GetJSPropertyName() const {
  return "pattern";
}




 // perspective



const char* Perspective::GetPropertyName() const {
  return "perspective";
}

const AtomicString& Perspective::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("perspective"));
  return name;
}

const char* Perspective::GetJSPropertyName() const {
  return "perspective";
}



void Perspective::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPerspective(ComputedStyleInitialValues::InitialPerspective());
}
void Perspective::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPerspective(state.ParentStyle()->Perspective());
}
void Perspective::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPerspective(StyleBuilderConverter::ConvertPerspective(state, value));
}

 // perspective-origin



const char* PerspectiveOrigin::GetPropertyName() const {
  return "perspective-origin";
}

const AtomicString& PerspectiveOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("perspective-origin"));
  return name;
}

const char* PerspectiveOrigin::GetJSPropertyName() const {
  return "perspectiveOrigin";
}



void PerspectiveOrigin::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPerspectiveOrigin(ComputedStyleInitialValues::InitialPerspectiveOrigin());
}
void PerspectiveOrigin::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPerspectiveOrigin(state.ParentStyle()->PerspectiveOrigin());
}
void PerspectiveOrigin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPerspectiveOrigin(StyleBuilderConverter::ConvertPosition(state, value));
}

 // pointer-events



const char* PointerEvents::GetPropertyName() const {
  return "pointer-events";
}

const AtomicString& PointerEvents::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("pointer-events"));
  return name;
}

const char* PointerEvents::GetJSPropertyName() const {
  return "pointerEvents";
}



void PointerEvents::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPointerEvents(ComputedStyleInitialValues::InitialPointerEvents());
  state.StyleBuilder().SetPointerEventsIsInherited(false);
}
void PointerEvents::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPointerEvents(state.ParentStyle()->PointerEvents());
  state.StyleBuilder().SetPointerEventsIsInherited(true);
}
void PointerEvents::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPointerEvents(To<CSSIdentifierValue>(value).ConvertTo<blink::EPointerEvents>());
  state.StyleBuilder().SetPointerEventsIsInherited(false);
}

 // port


CSSExposure Port::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Port::GetPropertyName() const {
  return "port";
}

const AtomicString& Port::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("port"));
  return name;
}

const char* Port::GetJSPropertyName() const {
  return "port";
}




 // position-try-fallbacks



const char* PositionTryFallbacks::GetPropertyName() const {
  return "position-try-fallbacks";
}

const AtomicString& PositionTryFallbacks::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position-try-fallbacks"));
  return name;
}

const char* PositionTryFallbacks::GetJSPropertyName() const {
  return "positionTryFallbacks";
}


const CSSValue* PositionTryFallbacks::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumePositionTryFallbacks(stream, context, local_context);
}

void PositionTryFallbacks::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionTryFallbacks(ComputedStyleInitialValues::InitialPositionTryFallbacks());
}
void PositionTryFallbacks::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionTryFallbacks(state.ParentStyle()->GetPositionTryFallbacks());
}

 // position-try-order



const char* PositionTryOrder::GetPropertyName() const {
  return "position-try-order";
}

const AtomicString& PositionTryOrder::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position-try-order"));
  return name;
}

const char* PositionTryOrder::GetJSPropertyName() const {
  return "positionTryOrder";
}



void PositionTryOrder::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionTryOrder(ComputedStyleInitialValues::InitialPositionTryOrder());
}
void PositionTryOrder::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionTryOrder(state.ParentStyle()->PositionTryOrder());
}
void PositionTryOrder::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPositionTryOrder(To<CSSIdentifierValue>(value).ConvertTo<blink::EPositionTryOrder>());
}

 // position-visibility



const char* PositionVisibility::GetPropertyName() const {
  return "position-visibility";
}

const AtomicString& PositionVisibility::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("position-visibility"));
  return name;
}

const char* PositionVisibility::GetJSPropertyName() const {
  return "positionVisibility";
}



void PositionVisibility::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionVisibility(ComputedStyleInitialValues::InitialPositionVisibility());
}
void PositionVisibility::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPositionVisibility(state.ParentStyle()->GetPositionVisibility());
}
void PositionVisibility::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPositionVisibility(StyleBuilderConverter::ConvertPositionVisibility(state, value));
}

 // prefix



const char* Prefix::GetPropertyName() const {
  return "prefix";
}

const AtomicString& Prefix::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("prefix"));
  return name;
}

const char* Prefix::GetJSPropertyName() const {
  return "prefix";
}




 // print-color-adjust



const char* PrintColorAdjust::GetPropertyName() const {
  return "print-color-adjust";
}

const AtomicString& PrintColorAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("print-color-adjust"));
  return name;
}

const char* PrintColorAdjust::GetJSPropertyName() const {
  return "printColorAdjust";
}



void PrintColorAdjust::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPrintColorAdjust(ComputedStyleInitialValues::InitialPrintColorAdjust());
}
void PrintColorAdjust::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetPrintColorAdjust(state.ParentStyle()->PrintColorAdjust());
}
void PrintColorAdjust::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPrintColorAdjust(To<CSSIdentifierValue>(value).ConvertTo<blink::EPrintColorAdjust>());
}

 // protocol


CSSExposure Protocol::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Protocol::GetPropertyName() const {
  return "protocol";
}

const AtomicString& Protocol::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("protocol"));
  return name;
}

const char* Protocol::GetJSPropertyName() const {
  return "protocol";
}




 // quotes



const char* Quotes::GetPropertyName() const {
  return "quotes";
}

const AtomicString& Quotes::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("quotes"));
  return name;
}

const char* Quotes::GetJSPropertyName() const {
  return "quotes";
}



void Quotes::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetQuotes(ComputedStyleInitialValues::InitialQuotes());
}
void Quotes::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetQuotes(state.ParentStyle()->Quotes());
}
void Quotes::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetQuotes(StyleBuilderConverter::ConvertQuotes(state, value));
}

 // r



const char* R::GetPropertyName() const {
  return "r";
}

const AtomicString& R::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("r"));
  return name;
}

const char* R::GetJSPropertyName() const {
  return "r";
}



void R::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetR(ComputedStyleInitialValues::InitialR());
}
void R::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetR(state.ParentStyle()->R());
}
void R::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetR(StyleBuilderConverter::ConvertLength(state, value));
}

 // range



const char* Range::GetPropertyName() const {
  return "range";
}

const AtomicString& Range::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("range"));
  return name;
}

const char* Range::GetJSPropertyName() const {
  return "range";
}




 // reading-flow



const char* ReadingFlow::GetPropertyName() const {
  return "reading-flow";
}

const AtomicString& ReadingFlow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("reading-flow"));
  return name;
}

const char* ReadingFlow::GetJSPropertyName() const {
  return "readingFlow";
}



void ReadingFlow::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetReadingFlow(ComputedStyleInitialValues::InitialReadingFlow());
}
void ReadingFlow::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetReadingFlow(state.ParentStyle()->ReadingFlow());
}
void ReadingFlow::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetReadingFlow(To<CSSIdentifierValue>(value).ConvertTo<blink::EReadingFlow>());
}

 // reading-order



const char* ReadingOrder::GetPropertyName() const {
  return "reading-order";
}

const AtomicString& ReadingOrder::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("reading-order"));
  return name;
}

const char* ReadingOrder::GetJSPropertyName() const {
  return "readingOrder";
}


const CSSValue* ReadingOrder::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeInteger(stream, context, local_context);
}

void ReadingOrder::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetReadingOrder(ComputedStyleInitialValues::InitialReadingOrder());
}
void ReadingOrder::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetReadingOrder(state.ParentStyle()->ReadingOrder());
}
void ReadingOrder::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetReadingOrder(To<CSSPrimitiveValue>(value).ConvertTo<int>(state.CssToLengthConversionData()));
}

 // resize



const char* Resize::GetPropertyName() const {
  return "resize";
}

const AtomicString& Resize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("resize"));
  return name;
}

const char* Resize::GetJSPropertyName() const {
  return "resize";
}



void Resize::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetResize(ComputedStyleInitialValues::InitialResize());
}
void Resize::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetResize(state.ParentStyle()->Resize());
}

 // result


CSSExposure Result::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSFunctionsEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Result::GetPropertyName() const {
  return "result";
}

const AtomicString& Result::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("result"));
  return name;
}

const char* Result::GetJSPropertyName() const {
  return "result";
}




 // right



const char* Right::GetPropertyName() const {
  return "right";
}

const AtomicString& Right::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("right"));
  return name;
}

const char* Right::GetJSPropertyName() const {
  return "right";
}


bool Right::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalInsetMapping().Contains(id);
}
const CSSProperty& Right::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalInsetMapping());
}

void Right::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRight(ComputedStyleInitialValues::InitialRight());
}
void Right::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetRight(state.ParentStyle()->Right());
}
void Right::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kRight,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetRight(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // rotate



const char* Rotate::GetPropertyName() const {
  return "rotate";
}

const AtomicString& Rotate::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rotate"));
  return name;
}

const char* Rotate::GetJSPropertyName() const {
  return "rotate";
}



void Rotate::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRotate(ComputedStyleInitialValues::InitialRotate());
}
void Rotate::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRotate(state.ParentStyle()->Rotate());
}
void Rotate::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRotate(StyleBuilderConverter::ConvertRotate(state, value));
}

 // row-gap



const char* RowGap::GetPropertyName() const {
  return "row-gap";
}

const AtomicString& RowGap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-gap"));
  return name;
}

const char* RowGap::GetJSPropertyName() const {
  return "rowGap";
}


const CSSValue* RowGap::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeGapLength(stream, context, local_context);
}

void RowGap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowGap(ComputedStyleInitialValues::InitialRowGap());
}
void RowGap::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowGap(state.ParentStyle()->RowGap());
}
void RowGap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowGap(StyleBuilderConverter::ConvertGapLength(state, value));
}

 // row-rule-break


CSSExposure RowRuleBreak::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleBreak::GetPropertyName() const {
  return "row-rule-break";
}

const AtomicString& RowRuleBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-break"));
  return name;
}

const char* RowRuleBreak::GetJSPropertyName() const {
  return "rowRuleBreak";
}



void RowRuleBreak::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleBreak(ComputedStyleInitialValues::InitialRowRuleBreak());
}
void RowRuleBreak::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleBreak(state.ParentStyle()->RowRuleBreak());
}
void RowRuleBreak::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleBreak(To<CSSIdentifierValue>(value).ConvertTo<blink::RuleBreak>());
}

 // row-rule-color


CSSExposure RowRuleColor::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleColor::GetPropertyName() const {
  return "row-rule-color";
}

const AtomicString& RowRuleColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-color"));
  return name;
}

const char* RowRuleColor::GetJSPropertyName() const {
  return "rowRuleColor";
}



void RowRuleColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleColor(ComputedStyleInitialValues::InitialRowRuleColor());
}
void RowRuleColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleColor(state.ParentStyle()->RowRuleColor());
}
void RowRuleColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleColor(StyleBuilderConverter::ConvertGapDecorationColorDataList(state, value));
}

 // row-rule-inset-cap-end


CSSExposure RowRuleInsetCapEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetCapEnd::GetPropertyName() const {
  return "row-rule-inset-cap-end";
}

const AtomicString& RowRuleInsetCapEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-cap-end"));
  return name;
}

const char* RowRuleInsetCapEnd::GetJSPropertyName() const {
  return "rowRuleInsetCapEnd";
}



void RowRuleInsetCapEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetCapEnd(ComputedStyleInitialValues::InitialRowRuleInsetCapEnd());
}
void RowRuleInsetCapEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetCapEnd(state.ParentStyle()->RowRuleInsetCapEnd());
}
void RowRuleInsetCapEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleInsetCapEnd(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // row-rule-inset-cap-start


CSSExposure RowRuleInsetCapStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetCapStart::GetPropertyName() const {
  return "row-rule-inset-cap-start";
}

const AtomicString& RowRuleInsetCapStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-cap-start"));
  return name;
}

const char* RowRuleInsetCapStart::GetJSPropertyName() const {
  return "rowRuleInsetCapStart";
}



void RowRuleInsetCapStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetCapStart(ComputedStyleInitialValues::InitialRowRuleInsetCapStart());
}
void RowRuleInsetCapStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetCapStart(state.ParentStyle()->RowRuleInsetCapStart());
}
void RowRuleInsetCapStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleInsetCapStart(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // row-rule-inset-junction-end


CSSExposure RowRuleInsetJunctionEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetJunctionEnd::GetPropertyName() const {
  return "row-rule-inset-junction-end";
}

const AtomicString& RowRuleInsetJunctionEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-junction-end"));
  return name;
}

const char* RowRuleInsetJunctionEnd::GetJSPropertyName() const {
  return "rowRuleInsetJunctionEnd";
}



void RowRuleInsetJunctionEnd::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetJunctionEnd(ComputedStyleInitialValues::InitialRowRuleInsetJunctionEnd());
}
void RowRuleInsetJunctionEnd::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetJunctionEnd(state.ParentStyle()->RowRuleInsetJunctionEnd());
}
void RowRuleInsetJunctionEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleInsetJunctionEnd(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // row-rule-inset-junction-start


CSSExposure RowRuleInsetJunctionStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleInsetJunctionStart::GetPropertyName() const {
  return "row-rule-inset-junction-start";
}

const AtomicString& RowRuleInsetJunctionStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-inset-junction-start"));
  return name;
}

const char* RowRuleInsetJunctionStart::GetJSPropertyName() const {
  return "rowRuleInsetJunctionStart";
}



void RowRuleInsetJunctionStart::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetJunctionStart(ComputedStyleInitialValues::InitialRowRuleInsetJunctionStart());
}
void RowRuleInsetJunctionStart::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleInsetJunctionStart(state.ParentStyle()->RowRuleInsetJunctionStart());
}
void RowRuleInsetJunctionStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleInsetJunctionStart(StyleBuilderConverter::ConvertGapDecorationInsetLength(state, value));
}

 // row-rule-style


CSSExposure RowRuleStyle::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleStyle::GetPropertyName() const {
  return "row-rule-style";
}

const AtomicString& RowRuleStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-style"));
  return name;
}

const char* RowRuleStyle::GetJSPropertyName() const {
  return "rowRuleStyle";
}



void RowRuleStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleStyle(ComputedStyleInitialValues::InitialRowRuleStyle());
}
void RowRuleStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleStyle(state.ParentStyle()->RowRuleStyle());
}
void RowRuleStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleStyle(StyleBuilderConverter::ConvertGapDecorationStyleDataList(state, value));
}

 // row-rule-visibility-items


CSSExposure RowRuleVisibilityItems::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleVisibilityItems::GetPropertyName() const {
  return "row-rule-visibility-items";
}

const AtomicString& RowRuleVisibilityItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-visibility-items"));
  return name;
}

const char* RowRuleVisibilityItems::GetJSPropertyName() const {
  return "rowRuleVisibilityItems";
}



void RowRuleVisibilityItems::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleVisibilityItems(ComputedStyleInitialValues::InitialRowRuleVisibilityItems());
}
void RowRuleVisibilityItems::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleVisibilityItems(state.ParentStyle()->RowRuleVisibilityItems());
}
void RowRuleVisibilityItems::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleVisibilityItems(To<CSSIdentifierValue>(value).ConvertTo<blink::RuleVisibilityItems>());
}

 // row-rule-width


CSSExposure RowRuleWidth::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RowRuleWidth::GetPropertyName() const {
  return "row-rule-width";
}

const AtomicString& RowRuleWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("row-rule-width"));
  return name;
}

const char* RowRuleWidth::GetJSPropertyName() const {
  return "rowRuleWidth";
}



void RowRuleWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleWidth(ComputedStyleInitialValues::InitialRowRuleWidth());
}
void RowRuleWidth::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRowRuleWidth(state.ParentStyle()->RowRuleWidth());
}
void RowRuleWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRowRuleWidth(StyleBuilderConverter::ConvertGapDecorationWidthDataList(state, value));
}

 // ruby-align



const char* RubyAlign::GetPropertyName() const {
  return "ruby-align";
}

const AtomicString& RubyAlign::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("ruby-align"));
  return name;
}

const char* RubyAlign::GetJSPropertyName() const {
  return "rubyAlign";
}



void RubyAlign::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRubyAlign(ComputedStyleInitialValues::InitialRubyAlign());
}
void RubyAlign::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRubyAlign(state.ParentStyle()->RubyAlign());
}
void RubyAlign::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRubyAlign(To<CSSIdentifierValue>(value).ConvertTo<blink::ERubyAlign>());
}

 // ruby-overhang


CSSExposure RubyOverhang::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSRubyOverhangEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RubyOverhang::GetPropertyName() const {
  return "ruby-overhang";
}

const AtomicString& RubyOverhang::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("ruby-overhang"));
  return name;
}

const char* RubyOverhang::GetJSPropertyName() const {
  return "rubyOverhang";
}



void RubyOverhang::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRubyOverhang(ComputedStyleInitialValues::InitialRubyOverhang());
}
void RubyOverhang::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRubyOverhang(state.ParentStyle()->RubyOverhang());
}
void RubyOverhang::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRubyOverhang(To<CSSIdentifierValue>(value).ConvertTo<blink::ERubyOverhang>());
}

 // ruby-position



const char* RubyPosition::GetPropertyName() const {
  return "ruby-position";
}

const AtomicString& RubyPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("ruby-position"));
  return name;
}

const char* RubyPosition::GetJSPropertyName() const {
  return "rubyPosition";
}



void RubyPosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRubyPosition(ComputedStyleInitialValues::InitialRubyPosition());
}
void RubyPosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRubyPosition(state.ParentStyle()->GetRubyPosition());
}
void RubyPosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRubyPosition(StyleBuilderConverter::ConvertRubyPosition(state, value));
}

 // rule-overlap


CSSExposure RuleOverlap::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSGapDecorationEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* RuleOverlap::GetPropertyName() const {
  return "rule-overlap";
}

const AtomicString& RuleOverlap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rule-overlap"));
  return name;
}

const char* RuleOverlap::GetJSPropertyName() const {
  return "ruleOverlap";
}



void RuleOverlap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRuleOverlap(ComputedStyleInitialValues::InitialRuleOverlap());
}
void RuleOverlap::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRuleOverlap(state.ParentStyle()->RuleOverlap());
}
void RuleOverlap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRuleOverlap(To<CSSIdentifierValue>(value).ConvertTo<blink::ERuleOverlap>());
}

 // rx



const char* Rx::GetPropertyName() const {
  return "rx";
}

const AtomicString& Rx::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("rx"));
  return name;
}

const char* Rx::GetJSPropertyName() const {
  return "rx";
}



void Rx::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRx(ComputedStyleInitialValues::InitialRx());
}
void Rx::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRx(state.ParentStyle()->Rx());
}
void Rx::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRx(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // ry



const char* Ry::GetPropertyName() const {
  return "ry";
}

const AtomicString& Ry::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("ry"));
  return name;
}

const char* Ry::GetJSPropertyName() const {
  return "ry";
}



void Ry::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRy(ComputedStyleInitialValues::InitialRy());
}
void Ry::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRy(state.ParentStyle()->Ry());
}
void Ry::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRy(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // scale



const char* Scale::GetPropertyName() const {
  return "scale";
}

const AtomicString& Scale::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scale"));
  return name;
}

const char* Scale::GetJSPropertyName() const {
  return "scale";
}



void Scale::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScale(ComputedStyleInitialValues::InitialScale());
}
void Scale::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScale(state.ParentStyle()->Scale());
}
void Scale::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScale(StyleBuilderConverter::ConvertScale(state, value));
}

 // scroll-behavior



const char* ScrollBehavior::GetPropertyName() const {
  return "scroll-behavior";
}

const AtomicString& ScrollBehavior::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-behavior"));
  return name;
}

const char* ScrollBehavior::GetJSPropertyName() const {
  return "scrollBehavior";
}



void ScrollBehavior::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollBehavior(ComputedStyleInitialValues::InitialScrollBehavior());
}
void ScrollBehavior::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollBehavior(state.ParentStyle()->GetScrollBehavior());
}
void ScrollBehavior::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollBehavior(To<CSSIdentifierValue>(value).ConvertTo<blink::mojom::blink::ScrollBehavior>());
}

 // scroll-initial-target


CSSExposure ScrollInitialTarget::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSScrollInitialTargetEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ScrollInitialTarget::GetPropertyName() const {
  return "scroll-initial-target";
}

const AtomicString& ScrollInitialTarget::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-initial-target"));
  return name;
}

const char* ScrollInitialTarget::GetJSPropertyName() const {
  return "scrollInitialTarget";
}



void ScrollInitialTarget::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollInitialTarget(ComputedStyleInitialValues::InitialScrollInitialTarget());
}
void ScrollInitialTarget::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollInitialTarget(state.ParentStyle()->ScrollInitialTarget());
}
void ScrollInitialTarget::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollInitialTarget(To<CSSIdentifierValue>(value).ConvertTo<blink::EScrollInitialTarget>());
}

 // scroll-margin-block-end



const char* ScrollMarginBlockEnd::GetPropertyName() const {
  return "scroll-margin-block-end";
}

const AtomicString& ScrollMarginBlockEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-block-end"));
  return name;
}

const char* ScrollMarginBlockEnd::GetJSPropertyName() const {
  return "scrollMarginBlockEnd";
}


const CSSProperty* ScrollMarginBlockEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollMarginBlockEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollMarginMapping());
}

bool ScrollMarginBlockEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollMarginMapping().Contains(id);
}


 // scroll-margin-block-start



const char* ScrollMarginBlockStart::GetPropertyName() const {
  return "scroll-margin-block-start";
}

const AtomicString& ScrollMarginBlockStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-block-start"));
  return name;
}

const char* ScrollMarginBlockStart::GetJSPropertyName() const {
  return "scrollMarginBlockStart";
}


const CSSProperty* ScrollMarginBlockStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollMarginBlockStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollMarginMapping());
}

bool ScrollMarginBlockStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollMarginMapping().Contains(id);
}


 // scroll-margin-bottom



const char* ScrollMarginBottom::GetPropertyName() const {
  return "scroll-margin-bottom";
}

const AtomicString& ScrollMarginBottom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-bottom"));
  return name;
}

const char* ScrollMarginBottom::GetJSPropertyName() const {
  return "scrollMarginBottom";
}


bool ScrollMarginBottom::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollMarginMapping().Contains(id);
}
const CSSProperty& ScrollMarginBottom::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollMarginMapping());
}

void ScrollMarginBottom::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollMarginBottom(ComputedStyleInitialValues::InitialScrollMarginBottom());
}
void ScrollMarginBottom::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollMarginBottom(state.ParentStyle()->ScrollMarginBottom());
}
void ScrollMarginBottom::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollMarginBottom(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // scroll-margin-inline-end



const char* ScrollMarginInlineEnd::GetPropertyName() const {
  return "scroll-margin-inline-end";
}

const AtomicString& ScrollMarginInlineEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-inline-end"));
  return name;
}

const char* ScrollMarginInlineEnd::GetJSPropertyName() const {
  return "scrollMarginInlineEnd";
}


const CSSProperty* ScrollMarginInlineEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollMarginInlineEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollMarginMapping());
}

bool ScrollMarginInlineEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollMarginMapping().Contains(id);
}


 // scroll-margin-inline-start



const char* ScrollMarginInlineStart::GetPropertyName() const {
  return "scroll-margin-inline-start";
}

const AtomicString& ScrollMarginInlineStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-inline-start"));
  return name;
}

const char* ScrollMarginInlineStart::GetJSPropertyName() const {
  return "scrollMarginInlineStart";
}


const CSSProperty* ScrollMarginInlineStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollMarginInlineStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollMarginMapping());
}

bool ScrollMarginInlineStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollMarginMapping().Contains(id);
}


 // scroll-margin-left



const char* ScrollMarginLeft::GetPropertyName() const {
  return "scroll-margin-left";
}

const AtomicString& ScrollMarginLeft::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-left"));
  return name;
}

const char* ScrollMarginLeft::GetJSPropertyName() const {
  return "scrollMarginLeft";
}


bool ScrollMarginLeft::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollMarginMapping().Contains(id);
}
const CSSProperty& ScrollMarginLeft::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollMarginMapping());
}

void ScrollMarginLeft::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollMarginLeft(ComputedStyleInitialValues::InitialScrollMarginLeft());
}
void ScrollMarginLeft::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollMarginLeft(state.ParentStyle()->ScrollMarginLeft());
}
void ScrollMarginLeft::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollMarginLeft(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // scroll-margin-right



const char* ScrollMarginRight::GetPropertyName() const {
  return "scroll-margin-right";
}

const AtomicString& ScrollMarginRight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-right"));
  return name;
}

const char* ScrollMarginRight::GetJSPropertyName() const {
  return "scrollMarginRight";
}


bool ScrollMarginRight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollMarginMapping().Contains(id);
}
const CSSProperty& ScrollMarginRight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollMarginMapping());
}

void ScrollMarginRight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollMarginRight(ComputedStyleInitialValues::InitialScrollMarginRight());
}
void ScrollMarginRight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollMarginRight(state.ParentStyle()->ScrollMarginRight());
}
void ScrollMarginRight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollMarginRight(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // scroll-margin-top



const char* ScrollMarginTop::GetPropertyName() const {
  return "scroll-margin-top";
}

const AtomicString& ScrollMarginTop::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-margin-top"));
  return name;
}

const char* ScrollMarginTop::GetJSPropertyName() const {
  return "scrollMarginTop";
}


bool ScrollMarginTop::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollMarginMapping().Contains(id);
}
const CSSProperty& ScrollMarginTop::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollMarginMapping());
}

void ScrollMarginTop::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollMarginTop(ComputedStyleInitialValues::InitialScrollMarginTop());
}
void ScrollMarginTop::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollMarginTop(state.ParentStyle()->ScrollMarginTop());
}
void ScrollMarginTop::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollMarginTop(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // scroll-marker-group


CSSExposure ScrollMarkerGroup::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSPseudoScrollMarkersEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ScrollMarkerGroup::GetPropertyName() const {
  return "scroll-marker-group";
}

const AtomicString& ScrollMarkerGroup::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-marker-group"));
  return name;
}

const char* ScrollMarkerGroup::GetJSPropertyName() const {
  return "scrollMarkerGroup";
}



void ScrollMarkerGroup::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollMarkerGroup(ComputedStyleInitialValues::InitialScrollMarkerGroup());
}
void ScrollMarkerGroup::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollMarkerGroup(state.ParentStyle()->GetScrollMarkerGroup());
}
void ScrollMarkerGroup::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollMarkerGroup(StyleBuilderConverter::ConvertScrollMarkerGroup(state, value));
}

 // scroll-padding-block-end



const char* ScrollPaddingBlockEnd::GetPropertyName() const {
  return "scroll-padding-block-end";
}

const AtomicString& ScrollPaddingBlockEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-block-end"));
  return name;
}

const char* ScrollPaddingBlockEnd::GetJSPropertyName() const {
  return "scrollPaddingBlockEnd";
}


const CSSProperty* ScrollPaddingBlockEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollPaddingBlockEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollPaddingMapping());
}

bool ScrollPaddingBlockEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollPaddingMapping().Contains(id);
}
const CSSValue* ScrollPaddingBlockEnd::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}


 // scroll-padding-block-start



const char* ScrollPaddingBlockStart::GetPropertyName() const {
  return "scroll-padding-block-start";
}

const AtomicString& ScrollPaddingBlockStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-block-start"));
  return name;
}

const char* ScrollPaddingBlockStart::GetJSPropertyName() const {
  return "scrollPaddingBlockStart";
}


const CSSProperty* ScrollPaddingBlockStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollPaddingBlockStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBlockStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollPaddingMapping());
}

bool ScrollPaddingBlockStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollPaddingMapping().Contains(id);
}
const CSSValue* ScrollPaddingBlockStart::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}


 // scroll-padding-bottom



const char* ScrollPaddingBottom::GetPropertyName() const {
  return "scroll-padding-bottom";
}

const AtomicString& ScrollPaddingBottom::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-bottom"));
  return name;
}

const char* ScrollPaddingBottom::GetJSPropertyName() const {
  return "scrollPaddingBottom";
}


bool ScrollPaddingBottom::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollPaddingMapping().Contains(id);
}
const CSSProperty& ScrollPaddingBottom::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveBottom(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollPaddingMapping());
}
const CSSValue* ScrollPaddingBottom::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}

void ScrollPaddingBottom::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollPaddingBottom(ComputedStyleInitialValues::InitialScrollPaddingBottom());
}
void ScrollPaddingBottom::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollPaddingBottom(state.ParentStyle()->ScrollPaddingBottom());
}
void ScrollPaddingBottom::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollPaddingBottom(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // scroll-padding-inline-end



const char* ScrollPaddingInlineEnd::GetPropertyName() const {
  return "scroll-padding-inline-end";
}

const AtomicString& ScrollPaddingInlineEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-inline-end"));
  return name;
}

const char* ScrollPaddingInlineEnd::GetJSPropertyName() const {
  return "scrollPaddingInlineEnd";
}


const CSSProperty* ScrollPaddingInlineEnd::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollPaddingInlineEnd::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineEnd(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollPaddingMapping());
}

bool ScrollPaddingInlineEnd::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollPaddingMapping().Contains(id);
}
const CSSValue* ScrollPaddingInlineEnd::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}


 // scroll-padding-inline-start



const char* ScrollPaddingInlineStart::GetPropertyName() const {
  return "scroll-padding-inline-start";
}

const AtomicString& ScrollPaddingInlineStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-inline-start"));
  return name;
}

const char* ScrollPaddingInlineStart::GetJSPropertyName() const {
  return "scrollPaddingInlineStart";
}


const CSSProperty* ScrollPaddingInlineStart::SurrogateFor(
    WritingDirectionMode writing_direction) const {
  return &ToPhysicalInternal(writing_direction);
}

const CSSProperty& ScrollPaddingInlineStart::ToPhysicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveInlineStart(writing_direction,
      CSSDirectionAwareResolver::PhysicalScrollPaddingMapping());
}

bool ScrollPaddingInlineStart::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::PhysicalScrollPaddingMapping().Contains(id);
}
const CSSValue* ScrollPaddingInlineStart::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}


 // scroll-padding-left



const char* ScrollPaddingLeft::GetPropertyName() const {
  return "scroll-padding-left";
}

const AtomicString& ScrollPaddingLeft::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-left"));
  return name;
}

const char* ScrollPaddingLeft::GetJSPropertyName() const {
  return "scrollPaddingLeft";
}


bool ScrollPaddingLeft::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollPaddingMapping().Contains(id);
}
const CSSProperty& ScrollPaddingLeft::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveLeft(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollPaddingMapping());
}
const CSSValue* ScrollPaddingLeft::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}

void ScrollPaddingLeft::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollPaddingLeft(ComputedStyleInitialValues::InitialScrollPaddingLeft());
}
void ScrollPaddingLeft::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollPaddingLeft(state.ParentStyle()->ScrollPaddingLeft());
}
void ScrollPaddingLeft::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollPaddingLeft(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // scroll-padding-right



const char* ScrollPaddingRight::GetPropertyName() const {
  return "scroll-padding-right";
}

const AtomicString& ScrollPaddingRight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-right"));
  return name;
}

const char* ScrollPaddingRight::GetJSPropertyName() const {
  return "scrollPaddingRight";
}


bool ScrollPaddingRight::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollPaddingMapping().Contains(id);
}
const CSSProperty& ScrollPaddingRight::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveRight(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollPaddingMapping());
}
const CSSValue* ScrollPaddingRight::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}

void ScrollPaddingRight::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollPaddingRight(ComputedStyleInitialValues::InitialScrollPaddingRight());
}
void ScrollPaddingRight::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollPaddingRight(state.ParentStyle()->ScrollPaddingRight());
}
void ScrollPaddingRight::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollPaddingRight(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // scroll-padding-top



const char* ScrollPaddingTop::GetPropertyName() const {
  return "scroll-padding-top";
}

const AtomicString& ScrollPaddingTop::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-padding-top"));
  return name;
}

const char* ScrollPaddingTop::GetJSPropertyName() const {
  return "scrollPaddingTop";
}


bool ScrollPaddingTop::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalScrollPaddingMapping().Contains(id);
}
const CSSProperty& ScrollPaddingTop::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalScrollPaddingMapping());
}
const CSSValue* ScrollPaddingTop::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeScrollPadding(stream, context, local_context);
}

void ScrollPaddingTop::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollPaddingTop(ComputedStyleInitialValues::InitialScrollPaddingTop());
}
void ScrollPaddingTop::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetScrollPaddingTop(state.ParentStyle()->ScrollPaddingTop());
}
void ScrollPaddingTop::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollPaddingTop(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // scroll-snap-align



const char* ScrollSnapAlign::GetPropertyName() const {
  return "scroll-snap-align";
}

const AtomicString& ScrollSnapAlign::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-snap-align"));
  return name;
}

const char* ScrollSnapAlign::GetJSPropertyName() const {
  return "scrollSnapAlign";
}



void ScrollSnapAlign::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollSnapAlign(ComputedStyleInitialValues::InitialScrollSnapAlign());
}
void ScrollSnapAlign::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollSnapAlign(state.ParentStyle()->GetScrollSnapAlign());
}
void ScrollSnapAlign::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollSnapAlign(StyleBuilderConverter::ConvertSnapAlign(state, value));
}

 // scroll-snap-stop



const char* ScrollSnapStop::GetPropertyName() const {
  return "scroll-snap-stop";
}

const AtomicString& ScrollSnapStop::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-snap-stop"));
  return name;
}

const char* ScrollSnapStop::GetJSPropertyName() const {
  return "scrollSnapStop";
}



void ScrollSnapStop::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollSnapStop(ComputedStyleInitialValues::InitialScrollSnapStop());
}
void ScrollSnapStop::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollSnapStop(state.ParentStyle()->ScrollSnapStop());
}
void ScrollSnapStop::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollSnapStop(To<CSSIdentifierValue>(value).ConvertTo<blink::EScrollSnapStop>());
}

 // scroll-snap-type



const char* ScrollSnapType::GetPropertyName() const {
  return "scroll-snap-type";
}

const AtomicString& ScrollSnapType::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-snap-type"));
  return name;
}

const char* ScrollSnapType::GetJSPropertyName() const {
  return "scrollSnapType";
}



void ScrollSnapType::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollSnapType(ComputedStyleInitialValues::InitialScrollSnapType());
}
void ScrollSnapType::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollSnapType(state.ParentStyle()->GetScrollSnapType());
}
void ScrollSnapType::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollSnapType(StyleBuilderConverter::ConvertSnapType(state, value));
}

 // scroll-target-group


CSSExposure ScrollTargetGroup::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSScrollTargetGroupEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ScrollTargetGroup::GetPropertyName() const {
  return "scroll-target-group";
}

const AtomicString& ScrollTargetGroup::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-target-group"));
  return name;
}

const char* ScrollTargetGroup::GetJSPropertyName() const {
  return "scrollTargetGroup";
}



void ScrollTargetGroup::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollTargetGroup(ComputedStyleInitialValues::InitialScrollTargetGroup());
}
void ScrollTargetGroup::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollTargetGroup(state.ParentStyle()->ScrollTargetGroup());
}
void ScrollTargetGroup::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollTargetGroup(To<CSSIdentifierValue>(value).ConvertTo<blink::EScrollTargetGroup>());
}

 // scroll-timeline-axis



const char* ScrollTimelineAxis::GetPropertyName() const {
  return "scroll-timeline-axis";
}

const AtomicString& ScrollTimelineAxis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-timeline-axis"));
  return name;
}

const char* ScrollTimelineAxis::GetJSPropertyName() const {
  return "scrollTimelineAxis";
}



void ScrollTimelineAxis::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollTimelineAxis(ComputedStyleInitialValues::InitialScrollTimelineAxis());
}
void ScrollTimelineAxis::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollTimelineAxis(state.ParentStyle()->ScrollTimelineAxis());
}
void ScrollTimelineAxis::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollTimelineAxis(StyleBuilderConverter::ConvertViewTimelineAxis(state, value));
}

 // scroll-timeline-name



const char* ScrollTimelineName::GetPropertyName() const {
  return "scroll-timeline-name";
}

const AtomicString& ScrollTimelineName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scroll-timeline-name"));
  return name;
}

const char* ScrollTimelineName::GetJSPropertyName() const {
  return "scrollTimelineName";
}



void ScrollTimelineName::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollTimelineName(ComputedStyleInitialValues::InitialScrollTimelineName());
}
void ScrollTimelineName::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollTimelineName(state.ParentStyle()->ScrollTimelineName());
}
void ScrollTimelineName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollTimelineName(StyleBuilderConverter::ConvertViewTimelineName(state, value));
}

 // scrollbar-color


CSSExposure ScrollbarColor::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::ScrollbarColorEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ScrollbarColor::GetPropertyName() const {
  return "scrollbar-color";
}

const AtomicString& ScrollbarColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scrollbar-color"));
  return name;
}

const char* ScrollbarColor::GetJSPropertyName() const {
  return "scrollbarColor";
}



void ScrollbarColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollbarColor(ComputedStyleInitialValues::InitialScrollbarColor());
}
void ScrollbarColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollbarColor(state.ParentStyle()->ScrollbarColor());
}
void ScrollbarColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollbarColor(StyleBuilderConverter::ConvertScrollbarColor(state, value));
}

 // scrollbar-gutter



const char* ScrollbarGutter::GetPropertyName() const {
  return "scrollbar-gutter";
}

const AtomicString& ScrollbarGutter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scrollbar-gutter"));
  return name;
}

const char* ScrollbarGutter::GetJSPropertyName() const {
  return "scrollbarGutter";
}



void ScrollbarGutter::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollbarGutter(ComputedStyleInitialValues::InitialScrollbarGutter());
}
void ScrollbarGutter::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollbarGutter(state.ParentStyle()->ScrollbarGutter());
}
void ScrollbarGutter::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollbarGutter(StyleBuilderConverter::ConvertScrollbarGutter(state, value));
}

 // scrollbar-width


CSSExposure ScrollbarWidth::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::ScrollbarWidthEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ScrollbarWidth::GetPropertyName() const {
  return "scrollbar-width";
}

const AtomicString& ScrollbarWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("scrollbar-width"));
  return name;
}

const char* ScrollbarWidth::GetJSPropertyName() const {
  return "scrollbarWidth";
}



void ScrollbarWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollbarWidth(ComputedStyleInitialValues::InitialScrollbarWidth());
}
void ScrollbarWidth::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetScrollbarWidth(state.ParentStyle()->ScrollbarWidth());
}
void ScrollbarWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetScrollbarWidth(To<CSSIdentifierValue>(value).ConvertTo<blink::EScrollbarWidth>());
}

 // search


CSSExposure Search::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::RouteMatchingEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* Search::GetPropertyName() const {
  return "search";
}

const AtomicString& Search::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("search"));
  return name;
}

const char* Search::GetJSPropertyName() const {
  return "search";
}




 // shape-image-threshold



const char* ShapeImageThreshold::GetPropertyName() const {
  return "shape-image-threshold";
}

const AtomicString& ShapeImageThreshold::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("shape-image-threshold"));
  return name;
}

const char* ShapeImageThreshold::GetJSPropertyName() const {
  return "shapeImageThreshold";
}


const CSSValue* ShapeImageThreshold::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeAlphaValue(stream, context, local_context);
}

void ShapeImageThreshold::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeImageThreshold(ComputedStyleInitialValues::InitialShapeImageThreshold());
}
void ShapeImageThreshold::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeImageThreshold(state.ParentStyle()->ShapeImageThreshold());
}
void ShapeImageThreshold::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetShapeImageThreshold(To<CSSPrimitiveValue>(value).ConvertTo<float>(state.CssToLengthConversionData()));
}

 // shape-margin



const char* ShapeMargin::GetPropertyName() const {
  return "shape-margin";
}

const AtomicString& ShapeMargin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("shape-margin"));
  return name;
}

const char* ShapeMargin::GetJSPropertyName() const {
  return "shapeMargin";
}



void ShapeMargin::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeMargin(ComputedStyleInitialValues::InitialShapeMargin());
}
void ShapeMargin::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeMargin(state.ParentStyle()->ShapeMargin());
}
void ShapeMargin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetShapeMargin(StyleBuilderConverter::ConvertLength(state, value));
}

 // shape-outside



const char* ShapeOutside::GetPropertyName() const {
  return "shape-outside";
}

const AtomicString& ShapeOutside::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("shape-outside"));
  return name;
}

const char* ShapeOutside::GetJSPropertyName() const {
  return "shapeOutside";
}



void ShapeOutside::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeOutside(ComputedStyleInitialValues::InitialShapeOutside());
}
void ShapeOutside::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeOutside(state.ParentStyle()->ShapeOutside());
}
void ShapeOutside::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetShapeOutside(StyleBuilderConverter::ConvertShapeValue(state, value));
}

 // shape-rendering



const char* ShapeRendering::GetPropertyName() const {
  return "shape-rendering";
}

const AtomicString& ShapeRendering::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("shape-rendering"));
  return name;
}

const char* ShapeRendering::GetJSPropertyName() const {
  return "shapeRendering";
}



void ShapeRendering::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeRendering(ComputedStyleInitialValues::InitialShapeRendering());
}
void ShapeRendering::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetShapeRendering(state.ParentStyle()->ShapeRendering());
}
void ShapeRendering::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetShapeRendering(To<CSSIdentifierValue>(value).ConvertTo<blink::EShapeRendering>());
}

 // size



const char* Size::GetPropertyName() const {
  return "size";
}

const AtomicString& Size::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("size"));
  return name;
}

const char* Size::GetJSPropertyName() const {
  return "size";
}




 // size-adjust



const char* SizeAdjust::GetPropertyName() const {
  return "size-adjust";
}

const AtomicString& SizeAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("size-adjust"));
  return name;
}

const char* SizeAdjust::GetJSPropertyName() const {
  return "sizeAdjust";
}




 // speak



const char* Speak::GetPropertyName() const {
  return "speak";
}

const AtomicString& Speak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("speak"));
  return name;
}

const char* Speak::GetJSPropertyName() const {
  return "speak";
}



void Speak::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetSpeak(ComputedStyleInitialValues::InitialSpeak());
}
void Speak::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetSpeak(state.ParentStyle()->Speak());
}
void Speak::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetSpeak(To<CSSIdentifierValue>(value).ConvertTo<blink::ESpeak>());
}

 // speak-as



const char* SpeakAs::GetPropertyName() const {
  return "speak-as";
}

const AtomicString& SpeakAs::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("speak-as"));
  return name;
}

const char* SpeakAs::GetJSPropertyName() const {
  return "speakAs";
}




 // src



const char* Src::GetPropertyName() const {
  return "src";
}

const AtomicString& Src::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("src"));
  return name;
}

const char* Src::GetJSPropertyName() const {
  return "src";
}




 // stop-color



const char* StopColor::GetPropertyName() const {
  return "stop-color";
}

const AtomicString& StopColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stop-color"));
  return name;
}

const char* StopColor::GetJSPropertyName() const {
  return "stopColor";
}


const CSSValue* StopColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void StopColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStopColor(ComputedStyleInitialValues::InitialStopColor());
}

void StopColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetStopColor(state.ParentStyle()->StopColor());
}

void StopColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStopColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // stop-opacity



const char* StopOpacity::GetPropertyName() const {
  return "stop-opacity";
}

const AtomicString& StopOpacity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stop-opacity"));
  return name;
}

const char* StopOpacity::GetJSPropertyName() const {
  return "stopOpacity";
}


const CSSValue* StopOpacity::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeAlphaValue(stream, context, local_context);
}

void StopOpacity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStopOpacity(ComputedStyleInitialValues::InitialStopOpacity());
}
void StopOpacity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetStopOpacity(state.ParentStyle()->StopOpacity());
}
void StopOpacity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStopOpacity(StyleBuilderConverter::ConvertAlpha(state, value));
}

 // stroke



const char* Stroke::GetPropertyName() const {
  return "stroke";
}

const AtomicString& Stroke::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke"));
  return name;
}

const char* Stroke::GetJSPropertyName() const {
  return "stroke";
}


const CSSValue* Stroke::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeSVGPaint(stream, context, local_context);
}

void Stroke::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokePaint(ComputedStyleInitialValues::InitialStrokePaint());
}

void Stroke::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokePaint(state.ParentStyle()->StrokePaint());
}


 // stroke-dasharray



const char* StrokeDasharray::GetPropertyName() const {
  return "stroke-dasharray";
}

const AtomicString& StrokeDasharray::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-dasharray"));
  return name;
}

const char* StrokeDasharray::GetJSPropertyName() const {
  return "strokeDasharray";
}



void StrokeDasharray::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeDashArray(ComputedStyleInitialValues::InitialStrokeDashArray());
}
void StrokeDasharray::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetStrokeDashArray(state.ParentStyle()->StrokeDashArray());
}
void StrokeDasharray::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStrokeDashArray(StyleBuilderConverter::ConvertStrokeDasharray(state, value));
}

 // stroke-dashoffset



const char* StrokeDashoffset::GetPropertyName() const {
  return "stroke-dashoffset";
}

const AtomicString& StrokeDashoffset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-dashoffset"));
  return name;
}

const char* StrokeDashoffset::GetJSPropertyName() const {
  return "strokeDashoffset";
}



void StrokeDashoffset::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeDashOffset(ComputedStyleInitialValues::InitialStrokeDashOffset());
}
void StrokeDashoffset::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetStrokeDashOffset(state.ParentStyle()->StrokeDashOffset());
}
void StrokeDashoffset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStrokeDashOffset(StyleBuilderConverter::ConvertLength(state, value));
}

 // stroke-linecap



const char* StrokeLinecap::GetPropertyName() const {
  return "stroke-linecap";
}

const AtomicString& StrokeLinecap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-linecap"));
  return name;
}

const char* StrokeLinecap::GetJSPropertyName() const {
  return "strokeLinecap";
}



void StrokeLinecap::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetCapStyle(ComputedStyleInitialValues::InitialCapStyle());
}
void StrokeLinecap::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetCapStyle(state.ParentStyle()->CapStyle());
}
void StrokeLinecap::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetCapStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::LineCap>());
}

 // stroke-linejoin



const char* StrokeLinejoin::GetPropertyName() const {
  return "stroke-linejoin";
}

const AtomicString& StrokeLinejoin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-linejoin"));
  return name;
}

const char* StrokeLinejoin::GetJSPropertyName() const {
  return "strokeLinejoin";
}



void StrokeLinejoin::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetJoinStyle(ComputedStyleInitialValues::InitialJoinStyle());
}
void StrokeLinejoin::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetJoinStyle(state.ParentStyle()->JoinStyle());
}
void StrokeLinejoin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetJoinStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::LineJoin>());
}

 // stroke-miterlimit



const char* StrokeMiterlimit::GetPropertyName() const {
  return "stroke-miterlimit";
}

const AtomicString& StrokeMiterlimit::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-miterlimit"));
  return name;
}

const char* StrokeMiterlimit::GetJSPropertyName() const {
  return "strokeMiterlimit";
}



void StrokeMiterlimit::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeMiterLimit(ComputedStyleInitialValues::InitialStrokeMiterLimit());
}
void StrokeMiterlimit::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeMiterLimit(state.ParentStyle()->StrokeMiterLimit());
}
void StrokeMiterlimit::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStrokeMiterLimit(To<CSSPrimitiveValue>(value).ConvertTo<float>(state.CssToLengthConversionData()));
}

 // stroke-opacity



const char* StrokeOpacity::GetPropertyName() const {
  return "stroke-opacity";
}

const AtomicString& StrokeOpacity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-opacity"));
  return name;
}

const char* StrokeOpacity::GetJSPropertyName() const {
  return "strokeOpacity";
}


const CSSValue* StrokeOpacity::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeAlphaValue(stream, context, local_context);
}

void StrokeOpacity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeOpacity(ComputedStyleInitialValues::InitialStrokeOpacity());
}
void StrokeOpacity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeOpacity(state.ParentStyle()->StrokeOpacity());
}
void StrokeOpacity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStrokeOpacity(StyleBuilderConverter::ConvertAlpha(state, value));
}

 // stroke-width



const char* StrokeWidth::GetPropertyName() const {
  return "stroke-width";
}

const AtomicString& StrokeWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("stroke-width"));
  return name;
}

const char* StrokeWidth::GetJSPropertyName() const {
  return "strokeWidth";
}



void StrokeWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetStrokeWidth(ComputedStyleInitialValues::InitialStrokeWidth());
}
void StrokeWidth::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetStrokeWidth(state.ParentStyle()->StrokeWidth());
}
void StrokeWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetStrokeWidth(StyleBuilderConverter::ConvertUnzoomedLength(state, value));
}

 // suffix



const char* Suffix::GetPropertyName() const {
  return "suffix";
}

const AtomicString& Suffix::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("suffix"));
  return name;
}

const char* Suffix::GetJSPropertyName() const {
  return "suffix";
}




 // symbols



const char* Symbols::GetPropertyName() const {
  return "symbols";
}

const AtomicString& Symbols::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("symbols"));
  return name;
}

const char* Symbols::GetJSPropertyName() const {
  return "symbols";
}




 // syntax



const char* Syntax::GetPropertyName() const {
  return "syntax";
}

const AtomicString& Syntax::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("syntax"));
  return name;
}

const char* Syntax::GetJSPropertyName() const {
  return "syntax";
}




 // system



const char* System::GetPropertyName() const {
  return "system";
}

const AtomicString& System::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("system"));
  return name;
}

const char* System::GetJSPropertyName() const {
  return "system";
}




 // tab-size



const char* TabSize::GetPropertyName() const {
  return "tab-size";
}

const AtomicString& TabSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("tab-size"));
  return name;
}

const char* TabSize::GetJSPropertyName() const {
  return "tabSize";
}



void TabSize::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTabSize(ComputedStyleInitialValues::InitialTabSize());
}
void TabSize::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTabSize(state.ParentStyle()->GetTabSize());
}
void TabSize::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTabSize(StyleBuilderConverter::ConvertLengthOrTabSpaces(state, value));
}

 // table-layout



const char* TableLayout::GetPropertyName() const {
  return "table-layout";
}

const AtomicString& TableLayout::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("table-layout"));
  return name;
}

const char* TableLayout::GetJSPropertyName() const {
  return "tableLayout";
}



void TableLayout::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTableLayout(ComputedStyleInitialValues::InitialTableLayout());
}
void TableLayout::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTableLayout(state.ParentStyle()->TableLayout());
}
void TableLayout::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTableLayout(To<CSSIdentifierValue>(value).ConvertTo<blink::ETableLayout>());
}

 // text-align



const char* TextAlign::GetPropertyName() const {
  return "text-align";
}

const AtomicString& TextAlign::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-align"));
  return name;
}

const char* TextAlign::GetJSPropertyName() const {
  return "textAlign";
}



void TextAlign::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAlign(ComputedStyleInitialValues::InitialTextAlign());
}
void TextAlign::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAlign(state.ParentStyle()->GetTextAlign());
}

 // text-align-last



const char* TextAlignLast::GetPropertyName() const {
  return "text-align-last";
}

const AtomicString& TextAlignLast::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-align-last"));
  return name;
}

const char* TextAlignLast::GetJSPropertyName() const {
  return "textAlignLast";
}



void TextAlignLast::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAlignLast(ComputedStyleInitialValues::InitialTextAlignLast());
}
void TextAlignLast::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAlignLast(state.ParentStyle()->TextAlignLast());
}
void TextAlignLast::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextAlignLast(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextAlignLast>());
}

 // text-anchor



const char* TextAnchor::GetPropertyName() const {
  return "text-anchor";
}

const AtomicString& TextAnchor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-anchor"));
  return name;
}

const char* TextAnchor::GetJSPropertyName() const {
  return "textAnchor";
}



void TextAnchor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAnchor(ComputedStyleInitialValues::InitialTextAnchor());
}
void TextAnchor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAnchor(state.ParentStyle()->TextAnchor());
}
void TextAnchor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextAnchor(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextAnchor>());
}

 // text-autospace



const char* TextAutospace::GetPropertyName() const {
  return "text-autospace";
}

const AtomicString& TextAutospace::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-autospace"));
  return name;
}

const char* TextAutospace::GetJSPropertyName() const {
  return "textAutospace";
}



void TextAutospace::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAutospace(ComputedStyleInitialValues::InitialTextAutospace());
}
void TextAutospace::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextAutospace(state.ParentStyle()->TextAutospace());
}
void TextAutospace::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextAutospace(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextAutospace>());
}

 // text-box-edge



const char* TextBoxEdge::GetPropertyName() const {
  return "text-box-edge";
}

const AtomicString& TextBoxEdge::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-box-edge"));
  return name;
}

const char* TextBoxEdge::GetJSPropertyName() const {
  return "textBoxEdge";
}



void TextBoxEdge::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextBoxEdge(ComputedStyleInitialValues::InitialTextBoxEdge());
}
void TextBoxEdge::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextBoxEdge(state.ParentStyle()->GetTextBoxEdge());
}
void TextBoxEdge::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextBoxEdge(StyleBuilderConverter::ConvertTextBoxEdge(state, value));
}

 // text-box-trim



const char* TextBoxTrim::GetPropertyName() const {
  return "text-box-trim";
}

const AtomicString& TextBoxTrim::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-box-trim"));
  return name;
}

const char* TextBoxTrim::GetJSPropertyName() const {
  return "textBoxTrim";
}



void TextBoxTrim::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextBoxTrim(ComputedStyleInitialValues::InitialTextBoxTrim());
}
void TextBoxTrim::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextBoxTrim(state.ParentStyle()->TextBoxTrim());
}
void TextBoxTrim::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextBoxTrim(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextBoxTrim>());
}

 // text-combine-upright



const char* TextCombineUpright::GetPropertyName() const {
  return "text-combine-upright";
}

const AtomicString& TextCombineUpright::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-combine-upright"));
  return name;
}

const char* TextCombineUpright::GetJSPropertyName() const {
  return "textCombineUpright";
}



void TextCombineUpright::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextCombine(ComputedStyleInitialValues::InitialTextCombine());
}
void TextCombineUpright::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextCombine(state.ParentStyle()->TextCombine());
}
void TextCombineUpright::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextCombine(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextCombine>());
}

 // text-decoration-color



const char* TextDecorationColor::GetPropertyName() const {
  return "text-decoration-color";
}

const AtomicString& TextDecorationColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration-color"));
  return name;
}

const char* TextDecorationColor::GetJSPropertyName() const {
  return "textDecorationColor";
}


const CSSValue* TextDecorationColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void TextDecorationColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationColor(StyleColor::CurrentColor());
}

void TextDecorationColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationColor(state.ParentStyle()->TextDecorationColor());
}

void TextDecorationColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextDecorationColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // text-decoration-line



const char* TextDecorationLine::GetPropertyName() const {
  return "text-decoration-line";
}

const AtomicString& TextDecorationLine::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration-line"));
  return name;
}

const char* TextDecorationLine::GetJSPropertyName() const {
  return "textDecorationLine";
}



void TextDecorationLine::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationLine(ComputedStyleInitialValues::InitialTextDecorationLine());
}
void TextDecorationLine::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationLine(state.ParentStyle()->GetTextDecorationLine());
}
void TextDecorationLine::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextDecorationLine(StyleBuilderConverter::ConvertFlags<blink::TextDecorationLine>(state, value));
}

 // text-decoration-skip-ink



const char* TextDecorationSkipInk::GetPropertyName() const {
  return "text-decoration-skip-ink";
}

const AtomicString& TextDecorationSkipInk::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration-skip-ink"));
  return name;
}

const char* TextDecorationSkipInk::GetJSPropertyName() const {
  return "textDecorationSkipInk";
}



void TextDecorationSkipInk::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationSkipInk(ComputedStyleInitialValues::InitialTextDecorationSkipInk());
}
void TextDecorationSkipInk::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationSkipInk(state.ParentStyle()->TextDecorationSkipInk());
}
void TextDecorationSkipInk::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextDecorationSkipInk(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextDecorationSkipInk>());
}

 // text-decoration-skip-spaces


CSSExposure TextDecorationSkipSpaces::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CSSTextDecorationSkipSpacesEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TextDecorationSkipSpaces::GetPropertyName() const {
  return "text-decoration-skip-spaces";
}

const AtomicString& TextDecorationSkipSpaces::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration-skip-spaces"));
  return name;
}

const char* TextDecorationSkipSpaces::GetJSPropertyName() const {
  return "textDecorationSkipSpaces";
}



void TextDecorationSkipSpaces::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationSkipSpaces(ComputedStyleInitialValues::InitialTextDecorationSkipSpaces());
}
void TextDecorationSkipSpaces::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationSkipSpaces(state.ParentStyle()->GetTextDecorationSkipSpaces());
}
void TextDecorationSkipSpaces::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextDecorationSkipSpaces(StyleBuilderConverter::ConvertFlags<blink::TextDecorationSkipSpaces>(state, value));
}

 // text-decoration-style



const char* TextDecorationStyle::GetPropertyName() const {
  return "text-decoration-style";
}

const AtomicString& TextDecorationStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration-style"));
  return name;
}

const char* TextDecorationStyle::GetJSPropertyName() const {
  return "textDecorationStyle";
}



void TextDecorationStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationStyle(ComputedStyleInitialValues::InitialTextDecorationStyle());
}
void TextDecorationStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationStyle(state.ParentStyle()->TextDecorationStyle());
}
void TextDecorationStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextDecorationStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextDecorationStyle>());
}

 // text-decoration-thickness



const char* TextDecorationThickness::GetPropertyName() const {
  return "text-decoration-thickness";
}

const AtomicString& TextDecorationThickness::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-decoration-thickness"));
  return name;
}

const char* TextDecorationThickness::GetJSPropertyName() const {
  return "textDecorationThickness";
}



void TextDecorationThickness::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationThickness(ComputedStyleInitialValues::InitialTextDecorationThickness());
}
void TextDecorationThickness::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextDecorationThickness(state.ParentStyle()->GetTextDecorationThickness());
}
void TextDecorationThickness::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextDecorationThickness(StyleBuilderConverter::ConvertTextDecorationThickness(state, value));
}

 // text-emphasis-color



const char* TextEmphasisColor::GetPropertyName() const {
  return "text-emphasis-color";
}

const AtomicString& TextEmphasisColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-emphasis-color"));
  return name;
}

const char* TextEmphasisColor::GetJSPropertyName() const {
  return "textEmphasisColor";
}


const CSSValue* TextEmphasisColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void TextEmphasisColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextEmphasisColor(StyleColor::CurrentColor());
}

void TextEmphasisColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextEmphasisColor(state.ParentStyle()->TextEmphasisColor());
}

void TextEmphasisColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextEmphasisColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // text-emphasis-position



const char* TextEmphasisPosition::GetPropertyName() const {
  return "text-emphasis-position";
}

const AtomicString& TextEmphasisPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-emphasis-position"));
  return name;
}

const char* TextEmphasisPosition::GetJSPropertyName() const {
  return "textEmphasisPosition";
}



void TextEmphasisPosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextEmphasisPosition(ComputedStyleInitialValues::InitialTextEmphasisPosition());
}
void TextEmphasisPosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextEmphasisPosition(state.ParentStyle()->GetTextEmphasisPosition());
}
void TextEmphasisPosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextEmphasisPosition(StyleBuilderConverter::ConvertTextTextEmphasisPosition(state, value));
}

 // text-emphasis-style



const char* TextEmphasisStyle::GetPropertyName() const {
  return "text-emphasis-style";
}

const AtomicString& TextEmphasisStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-emphasis-style"));
  return name;
}

const char* TextEmphasisStyle::GetJSPropertyName() const {
  return "textEmphasisStyle";
}




 // text-fit


CSSExposure TextFit::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::CssTextFitEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TextFit::GetPropertyName() const {
  return "text-fit";
}

const AtomicString& TextFit::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-fit"));
  return name;
}

const char* TextFit::GetJSPropertyName() const {
  return "textFit";
}


const CSSValue* TextFit::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeFitText(stream, context, local_context);
}

void TextFit::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextFit(ComputedStyleInitialValues::InitialTextFit());
}
void TextFit::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextFit(state.ParentStyle()->TextFit());
}
void TextFit::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextFit(StyleBuilderConverter::ConvertFitText(state, value));
}

 // text-indent



const char* TextIndent::GetPropertyName() const {
  return "text-indent";
}

const AtomicString& TextIndent::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-indent"));
  return name;
}

const char* TextIndent::GetJSPropertyName() const {
  return "textIndent";
}



void TextIndent::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextIndent(ComputedStyleInitialValues::InitialTextIndent());
}
void TextIndent::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetTextIndent(state.ParentStyle()->TextIndent());
}

 // text-justify



const char* TextJustify::GetPropertyName() const {
  return "text-justify";
}

const AtomicString& TextJustify::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-justify"));
  return name;
}

const char* TextJustify::GetJSPropertyName() const {
  return "textJustify";
}



void TextJustify::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextJustify(ComputedStyleInitialValues::InitialTextJustify());
}
void TextJustify::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextJustify(state.ParentStyle()->GetTextJustify());
}
void TextJustify::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextJustify(To<CSSIdentifierValue>(value).ConvertTo<blink::TextJustify>());
}

 // text-overflow



const char* TextOverflow::GetPropertyName() const {
  return "text-overflow";
}

const AtomicString& TextOverflow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-overflow"));
  return name;
}

const char* TextOverflow::GetJSPropertyName() const {
  return "textOverflow";
}



void TextOverflow::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextOverflow(ComputedStyleInitialValues::InitialTextOverflow());
}
void TextOverflow::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextOverflow(state.ParentStyle()->TextOverflow());
}
void TextOverflow::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextOverflow(StyleBuilderConverter::ConvertTextOverflow(state, value));
}

 // text-shadow



const char* TextShadow::GetPropertyName() const {
  return "text-shadow";
}

const AtomicString& TextShadow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-shadow"));
  return name;
}

const char* TextShadow::GetJSPropertyName() const {
  return "textShadow";
}



void TextShadow::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextShadow(ComputedStyleInitialValues::InitialTextShadow());
}
void TextShadow::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetTextShadow(state.ParentStyle()->TextShadow());
}
void TextShadow::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextShadow(StyleBuilderConverter::ConvertShadowList(state, value));
}

 // text-transform



const char* TextTransform::GetPropertyName() const {
  return "text-transform";
}

const AtomicString& TextTransform::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-transform"));
  return name;
}

const char* TextTransform::GetJSPropertyName() const {
  return "textTransform";
}



void TextTransform::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextTransform(ComputedStyleInitialValues::InitialTextTransform());
  state.StyleBuilder().SetTextTransformIsInherited(false);
}
void TextTransform::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextTransform(state.ParentStyle()->TextTransform());
  state.StyleBuilder().SetTextTransformIsInherited(true);
}
void TextTransform::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextTransform(StyleBuilderConverter::ConvertFlags<blink::ETextTransform>(state, value));
  state.StyleBuilder().SetTextTransformIsInherited(false);
}

 // text-underline-offset



const char* TextUnderlineOffset::GetPropertyName() const {
  return "text-underline-offset";
}

const AtomicString& TextUnderlineOffset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-underline-offset"));
  return name;
}

const char* TextUnderlineOffset::GetJSPropertyName() const {
  return "textUnderlineOffset";
}



void TextUnderlineOffset::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextUnderlineOffset(ComputedStyleInitialValues::InitialTextUnderlineOffset());
}
void TextUnderlineOffset::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetTextUnderlineOffset(state.ParentStyle()->TextUnderlineOffset());
}
void TextUnderlineOffset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextUnderlineOffset(StyleBuilderConverter::ConvertTextUnderlineOffset(state, value));
}

 // text-underline-position



const char* TextUnderlinePosition::GetPropertyName() const {
  return "text-underline-position";
}

const AtomicString& TextUnderlinePosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-underline-position"));
  return name;
}

const char* TextUnderlinePosition::GetJSPropertyName() const {
  return "textUnderlinePosition";
}



void TextUnderlinePosition::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextUnderlinePosition(ComputedStyleInitialValues::InitialTextUnderlinePosition());
}
void TextUnderlinePosition::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextUnderlinePosition(state.ParentStyle()->GetTextUnderlinePosition());
}
void TextUnderlinePosition::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextUnderlinePosition(StyleBuilderConverter::ConvertTextUnderlinePosition(state, value));
}

 // text-wrap-mode



const char* TextWrapMode::GetPropertyName() const {
  return "text-wrap-mode";
}

const AtomicString& TextWrapMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-wrap-mode"));
  return name;
}

const char* TextWrapMode::GetJSPropertyName() const {
  return "textWrapMode";
}



void TextWrapMode::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextWrapMode(ComputedStyleInitialValues::InitialTextWrapMode());
}
void TextWrapMode::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextWrapMode(state.ParentStyle()->GetTextWrapMode());
}
void TextWrapMode::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextWrapMode(To<CSSIdentifierValue>(value).ConvertTo<blink::TextWrapMode>());
}

 // text-wrap-style



const char* TextWrapStyle::GetPropertyName() const {
  return "text-wrap-style";
}

const AtomicString& TextWrapStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("text-wrap-style"));
  return name;
}

const char* TextWrapStyle::GetJSPropertyName() const {
  return "textWrapStyle";
}



void TextWrapStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextWrapStyle(ComputedStyleInitialValues::InitialTextWrapStyle());
}
void TextWrapStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextWrapStyle(state.ParentStyle()->GetTextWrapStyle());
}
void TextWrapStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextWrapStyle(To<CSSIdentifierValue>(value).ConvertTo<blink::TextWrapStyle>());
}

 // timeline-scope



const char* TimelineScope::GetPropertyName() const {
  return "timeline-scope";
}

const AtomicString& TimelineScope::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-scope"));
  return name;
}

const char* TimelineScope::GetJSPropertyName() const {
  return "timelineScope";
}



void TimelineScope::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTimelineScope(ComputedStyleInitialValues::InitialTimelineScope());
}
void TimelineScope::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTimelineScope(state.ParentStyle()->TimelineScope());
}
void TimelineScope::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTimelineScope(StyleBuilderConverter::ConvertTimelineScope(state, value));
}

 // timeline-trigger-activation-range-end


CSSExposure TimelineTriggerActivationRangeEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerActivationRangeEnd::GetPropertyName() const {
  return "timeline-trigger-activation-range-end";
}

const AtomicString& TimelineTriggerActivationRangeEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-activation-range-end"));
  return name;
}

const char* TimelineTriggerActivationRangeEnd::GetJSPropertyName() const {
  return "timelineTriggerActivationRangeEnd";
}



void TimelineTriggerActivationRangeEnd::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActivationRangeEndList().clear();
  data.TimelineTriggerActivationRangeEndList().push_back(CSSAnimationData::InitialTimelineTriggerActivationRangeEnd());
}

void TimelineTriggerActivationRangeEnd::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineTriggerActivationRangeEndList() = parent_data->TimelineTriggerActivationRangeEndList();
}

void TimelineTriggerActivationRangeEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActivationRangeEndList().clear();
  data.TimelineTriggerActivationRangeEndList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineTriggerActivationRangeEndList().push_back(CSSToStyleMap::MapAnimationTimelineTriggerActivationRangeEnd(state, item));
  }
}

 // timeline-trigger-activation-range-start


CSSExposure TimelineTriggerActivationRangeStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerActivationRangeStart::GetPropertyName() const {
  return "timeline-trigger-activation-range-start";
}

const AtomicString& TimelineTriggerActivationRangeStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-activation-range-start"));
  return name;
}

const char* TimelineTriggerActivationRangeStart::GetJSPropertyName() const {
  return "timelineTriggerActivationRangeStart";
}



void TimelineTriggerActivationRangeStart::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActivationRangeStartList().clear();
  data.TimelineTriggerActivationRangeStartList().push_back(CSSAnimationData::InitialTimelineTriggerActivationRangeStart());
}

void TimelineTriggerActivationRangeStart::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineTriggerActivationRangeStartList() = parent_data->TimelineTriggerActivationRangeStartList();
}

void TimelineTriggerActivationRangeStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActivationRangeStartList().clear();
  data.TimelineTriggerActivationRangeStartList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineTriggerActivationRangeStartList().push_back(CSSToStyleMap::MapAnimationTimelineTriggerActivationRangeStart(state, item));
  }
}

 // timeline-trigger-active-range-end


CSSExposure TimelineTriggerActiveRangeEnd::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerActiveRangeEnd::GetPropertyName() const {
  return "timeline-trigger-active-range-end";
}

const AtomicString& TimelineTriggerActiveRangeEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-active-range-end"));
  return name;
}

const char* TimelineTriggerActiveRangeEnd::GetJSPropertyName() const {
  return "timelineTriggerActiveRangeEnd";
}



void TimelineTriggerActiveRangeEnd::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActiveRangeEndList().clear();
  data.TimelineTriggerActiveRangeEndList().push_back(CSSAnimationData::InitialTimelineTriggerActiveRangeEnd());
}

void TimelineTriggerActiveRangeEnd::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineTriggerActiveRangeEndList() = parent_data->TimelineTriggerActiveRangeEndList();
}

void TimelineTriggerActiveRangeEnd::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActiveRangeEndList().clear();
  data.TimelineTriggerActiveRangeEndList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineTriggerActiveRangeEndList().push_back(CSSToStyleMap::MapAnimationTimelineTriggerActiveRangeEnd(state, item));
  }
}

 // timeline-trigger-active-range-start


CSSExposure TimelineTriggerActiveRangeStart::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerActiveRangeStart::GetPropertyName() const {
  return "timeline-trigger-active-range-start";
}

const AtomicString& TimelineTriggerActiveRangeStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-active-range-start"));
  return name;
}

const char* TimelineTriggerActiveRangeStart::GetJSPropertyName() const {
  return "timelineTriggerActiveRangeStart";
}



void TimelineTriggerActiveRangeStart::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActiveRangeStartList().clear();
  data.TimelineTriggerActiveRangeStartList().push_back(CSSAnimationData::InitialTimelineTriggerActiveRangeStart());
}

void TimelineTriggerActiveRangeStart::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineTriggerActiveRangeStartList() = parent_data->TimelineTriggerActiveRangeStartList();
}

void TimelineTriggerActiveRangeStart::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerActiveRangeStartList().clear();
  data.TimelineTriggerActiveRangeStartList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineTriggerActiveRangeStartList().push_back(CSSToStyleMap::MapAnimationTimelineTriggerActiveRangeStart(state, item));
  }
}

 // timeline-trigger-name


CSSExposure TimelineTriggerName::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerName::GetPropertyName() const {
  return "timeline-trigger-name";
}

const AtomicString& TimelineTriggerName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-name"));
  return name;
}

const char* TimelineTriggerName::GetJSPropertyName() const {
  return "timelineTriggerName";
}



void TimelineTriggerName::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerNameList().clear();
  data.TimelineTriggerNameList().push_back(CSSAnimationData::InitialTimelineTriggerName());
}

void TimelineTriggerName::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineTriggerNameList() = parent_data->TimelineTriggerNameList();
}

void TimelineTriggerName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerNameList().clear();
  data.TimelineTriggerNameList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineTriggerNameList().push_back(CSSToStyleMap::MapAnimationTimelineTriggerName(state, item));
  }
}

 // timeline-trigger-source


CSSExposure TimelineTriggerSource::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::TimelineTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TimelineTriggerSource::GetPropertyName() const {
  return "timeline-trigger-source";
}

const AtomicString& TimelineTriggerSource::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("timeline-trigger-source"));
  return name;
}

const char* TimelineTriggerSource::GetJSPropertyName() const {
  return "timelineTriggerSource";
}



void TimelineTriggerSource::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Animations())
    return;
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerSourceList().clear();
  data.TimelineTriggerSourceList().push_back(CSSAnimationData::InitialTimelineTriggerSource());
}

void TimelineTriggerSource::ApplyInherit(StyleResolverState& state) const {
  const CSSAnimationData* parent_data = state.ParentStyle()->Animations();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessAnimations().TimelineTriggerSourceList() = parent_data->TimelineTriggerSourceList();
}

void TimelineTriggerSource::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSAnimationData& data = state.StyleBuilder().AccessAnimations();
  data.TimelineTriggerSourceList().clear();
  data.TimelineTriggerSourceList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimelineTriggerSourceList().push_back(CSSToStyleMap::MapAnimationTimelineTriggerSource(state, item));
  }
}

 // top



const char* Top::GetPropertyName() const {
  return "top";
}

const AtomicString& Top::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("top"));
  return name;
}

const char* Top::GetJSPropertyName() const {
  return "top";
}


bool Top::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalInsetMapping().Contains(id);
}
const CSSProperty& Top::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveTop(writing_direction,
      CSSDirectionAwareResolver::LogicalInsetMapping());
}

void Top::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTop(ComputedStyleInitialValues::InitialTop());
}
void Top::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetTop(state.ParentStyle()->Top());
}
void Top::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kTop,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetTop(StyleBuilderConverter::ConvertLengthOrAuto(state, value));
}

 // touch-action



const char* TouchAction::GetPropertyName() const {
  return "touch-action";
}

const AtomicString& TouchAction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("touch-action"));
  return name;
}

const char* TouchAction::GetJSPropertyName() const {
  return "touchAction";
}



void TouchAction::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTouchAction(ComputedStyleInitialValues::InitialTouchAction());
}
void TouchAction::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTouchAction(state.ParentStyle()->GetTouchAction());
}
void TouchAction::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTouchAction(StyleBuilderConverter::ConvertFlags<blink::TouchAction>(state, value));
}

 // transform



const char* Transform::GetPropertyName() const {
  return "transform";
}

const AtomicString& Transform::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transform"));
  return name;
}

const char* Transform::GetJSPropertyName() const {
  return "transform";
}


const CSSValue* Transform::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeTransformList(stream, context, local_context);
}

void Transform::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransform(ComputedStyleInitialValues::InitialTransform());
}
void Transform::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTransform(state.ParentStyle()->Transform());
}
void Transform::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransform(StyleBuilderConverter::ConvertTransformOperations(state, value));
}

 // transform-box



const char* TransformBox::GetPropertyName() const {
  return "transform-box";
}

const AtomicString& TransformBox::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transform-box"));
  return name;
}

const char* TransformBox::GetJSPropertyName() const {
  return "transformBox";
}



void TransformBox::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformBox(ComputedStyleInitialValues::InitialTransformBox());
}
void TransformBox::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformBox(state.ParentStyle()->TransformBox());
}
void TransformBox::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransformBox(To<CSSIdentifierValue>(value).ConvertTo<blink::ETransformBox>());
}

 // transform-origin



const char* TransformOrigin::GetPropertyName() const {
  return "transform-origin";
}

const AtomicString& TransformOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transform-origin"));
  return name;
}

const char* TransformOrigin::GetJSPropertyName() const {
  return "transformOrigin";
}



void TransformOrigin::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformOrigin(ComputedStyleInitialValues::InitialTransformOrigin());
}
void TransformOrigin::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformOrigin(state.ParentStyle()->GetTransformOrigin());
}
void TransformOrigin::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransformOrigin(StyleBuilderConverter::ConvertTransformOrigin(state, value));
}

 // transform-style



const char* TransformStyle::GetPropertyName() const {
  return "transform-style";
}

const AtomicString& TransformStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transform-style"));
  return name;
}

const char* TransformStyle::GetJSPropertyName() const {
  return "transformStyle";
}



void TransformStyle::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformStyle3D(ComputedStyleInitialValues::InitialTransformStyle3D());
}
void TransformStyle::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformStyle3D(state.ParentStyle()->TransformStyle3D());
}
void TransformStyle::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransformStyle3D(To<CSSIdentifierValue>(value).ConvertTo<blink::ETransformStyle3D>());
}

 // transition-behavior



const char* TransitionBehavior::GetPropertyName() const {
  return "transition-behavior";
}

const AtomicString& TransitionBehavior::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transition-behavior"));
  return name;
}

const char* TransitionBehavior::GetJSPropertyName() const {
  return "transitionBehavior";
}



void TransitionBehavior::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Transitions())
    return;
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.BehaviorList().clear();
  data.BehaviorList().push_back(CSSTransitionData::InitialBehavior());
}

void TransitionBehavior::ApplyInherit(StyleResolverState& state) const {
  const CSSTransitionData* parent_data = state.ParentStyle()->Transitions();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessTransitions().BehaviorList() = parent_data->BehaviorList();
}

void TransitionBehavior::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.BehaviorList().clear();
  data.BehaviorList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.BehaviorList().push_back(CSSToStyleMap::MapAnimationBehavior(state, item));
  }
}

 // transition-delay



const char* TransitionDelay::GetPropertyName() const {
  return "transition-delay";
}

const AtomicString& TransitionDelay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transition-delay"));
  return name;
}

const char* TransitionDelay::GetJSPropertyName() const {
  return "transitionDelay";
}



void TransitionDelay::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Transitions())
    return;
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.DelayStartList().clear();
  data.DelayStartList().push_back(CSSTransitionData::InitialDelayStart());
}

void TransitionDelay::ApplyInherit(StyleResolverState& state) const {
  const CSSTransitionData* parent_data = state.ParentStyle()->Transitions();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessTransitions().DelayStartList() = parent_data->DelayStartList();
}

void TransitionDelay::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.DelayStartList().clear();
  data.DelayStartList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.DelayStartList().push_back(CSSToStyleMap::MapAnimationDelayStart(state, item));
  }
}

 // transition-duration



const char* TransitionDuration::GetPropertyName() const {
  return "transition-duration";
}

const AtomicString& TransitionDuration::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transition-duration"));
  return name;
}

const char* TransitionDuration::GetJSPropertyName() const {
  return "transitionDuration";
}



void TransitionDuration::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Transitions())
    return;
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.DurationList().clear();
  data.DurationList().push_back(CSSTransitionData::InitialDuration());
}

void TransitionDuration::ApplyInherit(StyleResolverState& state) const {
  const CSSTransitionData* parent_data = state.ParentStyle()->Transitions();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessTransitions().DurationList() = parent_data->DurationList();
}

void TransitionDuration::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.DurationList().clear();
  data.DurationList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.DurationList().push_back(CSSToStyleMap::MapAnimationDuration(state, item));
  }
}

 // transition-property



const char* TransitionProperty::GetPropertyName() const {
  return "transition-property";
}

const AtomicString& TransitionProperty::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transition-property"));
  return name;
}

const char* TransitionProperty::GetJSPropertyName() const {
  return "transitionProperty";
}



void TransitionProperty::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Transitions())
    return;
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.PropertyList().clear();
  data.PropertyList().push_back(CSSTransitionData::InitialProperty());
}

void TransitionProperty::ApplyInherit(StyleResolverState& state) const {
  const CSSTransitionData* parent_data = state.ParentStyle()->Transitions();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessTransitions().PropertyList() = parent_data->PropertyList();
}

void TransitionProperty::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.PropertyList().clear();
  data.PropertyList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.PropertyList().push_back(CSSToStyleMap::MapAnimationProperty(state, item));
  }
}

 // transition-timing-function



const char* TransitionTimingFunction::GetPropertyName() const {
  return "transition-timing-function";
}

const AtomicString& TransitionTimingFunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("transition-timing-function"));
  return name;
}

const char* TransitionTimingFunction::GetJSPropertyName() const {
  return "transitionTimingFunction";
}



void TransitionTimingFunction::ApplyInitial(StyleResolverState& state) const {
  if (!state.StyleBuilder().Transitions())
    return;
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.TimingFunctionList().clear();
  data.TimingFunctionList().push_back(CSSTransitionData::InitialTimingFunction());
}

void TransitionTimingFunction::ApplyInherit(StyleResolverState& state) const {
  const CSSTransitionData* parent_data = state.ParentStyle()->Transitions();
  if (!parent_data)
    ApplyInitial(state);
  else
    state.StyleBuilder().AccessTransitions().TimingFunctionList() = parent_data->TimingFunctionList();
}

void TransitionTimingFunction::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  const CSSValueList& list = To<CSSValueList>(value);
  CSSTransitionData& data = state.StyleBuilder().AccessTransitions();
  data.TimingFunctionList().clear();
  data.TimingFunctionList().reserve(list.length());
  for (const CSSValue* list_value : list) {
    const auto& item = *list_value;
    data.TimingFunctionList().push_back(CSSToStyleMap::MapAnimationTimingFunction(state, item));
  }
}

 // translate



const char* Translate::GetPropertyName() const {
  return "translate";
}

const AtomicString& Translate::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("translate"));
  return name;
}

const char* Translate::GetJSPropertyName() const {
  return "translate";
}



void Translate::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTranslate(ComputedStyleInitialValues::InitialTranslate());
}
void Translate::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTranslate(state.ParentStyle()->Translate());
}
void Translate::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTranslate(StyleBuilderConverter::ConvertTranslate(state, value));
}

 // trigger-scope


CSSExposure TriggerScope::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::AnimationTriggerEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* TriggerScope::GetPropertyName() const {
  return "trigger-scope";
}

const AtomicString& TriggerScope::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("trigger-scope"));
  return name;
}

const char* TriggerScope::GetJSPropertyName() const {
  return "triggerScope";
}


const CSSValue* TriggerScope::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeNameScope(stream, context, local_context);
}

void TriggerScope::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTriggerScope(ComputedStyleInitialValues::InitialTriggerScope());
}
void TriggerScope::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTriggerScope(state.ParentStyle()->TriggerScope());
}
void TriggerScope::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTriggerScope(StyleBuilderConverter::ConvertTriggerScope(state, value));
}

 // types



const char* Types::GetPropertyName() const {
  return "types";
}

const AtomicString& Types::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("types"));
  return name;
}

const char* Types::GetJSPropertyName() const {
  return "types";
}




 // unicode-bidi



const char* UnicodeBidi::GetPropertyName() const {
  return "unicode-bidi";
}

const AtomicString& UnicodeBidi::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("unicode-bidi"));
  return name;
}

const char* UnicodeBidi::GetJSPropertyName() const {
  return "unicodeBidi";
}



void UnicodeBidi::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetUnicodeBidi(ComputedStyleInitialValues::InitialUnicodeBidi());
}
void UnicodeBidi::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetUnicodeBidi(state.ParentStyle()->GetUnicodeBidi());
}
void UnicodeBidi::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetUnicodeBidi(To<CSSIdentifierValue>(value).ConvertTo<blink::UnicodeBidi>());
}

 // unicode-range



const char* UnicodeRange::GetPropertyName() const {
  return "unicode-range";
}

const AtomicString& UnicodeRange::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("unicode-range"));
  return name;
}

const char* UnicodeRange::GetJSPropertyName() const {
  return "unicodeRange";
}




 // user-select



const char* UserSelect::GetPropertyName() const {
  return "user-select";
}

const AtomicString& UserSelect::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("user-select"));
  return name;
}

const char* UserSelect::GetJSPropertyName() const {
  return "userSelect";
}



void UserSelect::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetUserSelect(ComputedStyleInitialValues::InitialUserSelect());
}
void UserSelect::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetUserSelect(state.ParentStyle()->UserSelect());
}
void UserSelect::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetUserSelect(To<CSSIdentifierValue>(value).ConvertTo<blink::EUserSelect>());
}

 // vector-effect



const char* VectorEffect::GetPropertyName() const {
  return "vector-effect";
}

const AtomicString& VectorEffect::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("vector-effect"));
  return name;
}

const char* VectorEffect::GetJSPropertyName() const {
  return "vectorEffect";
}



void VectorEffect::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetVectorEffect(ComputedStyleInitialValues::InitialVectorEffect());
}
void VectorEffect::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetVectorEffect(state.ParentStyle()->VectorEffect());
}
void VectorEffect::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetVectorEffect(To<CSSIdentifierValue>(value).ConvertTo<blink::EVectorEffect>());
}

 // vertical-align



const char* VerticalAlign::GetPropertyName() const {
  return "vertical-align";
}

const AtomicString& VerticalAlign::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("vertical-align"));
  return name;
}

const char* VerticalAlign::GetJSPropertyName() const {
  return "verticalAlign";
}



void VerticalAlign::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetVerticalAlign(ComputedStyleInitialValues::InitialVerticalAlign());
}

 // view-timeline-axis



const char* ViewTimelineAxis::GetPropertyName() const {
  return "view-timeline-axis";
}

const AtomicString& ViewTimelineAxis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-timeline-axis"));
  return name;
}

const char* ViewTimelineAxis::GetJSPropertyName() const {
  return "viewTimelineAxis";
}



void ViewTimelineAxis::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTimelineAxis(ComputedStyleInitialValues::InitialViewTimelineAxis());
}
void ViewTimelineAxis::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTimelineAxis(state.ParentStyle()->ViewTimelineAxis());
}
void ViewTimelineAxis::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTimelineAxis(StyleBuilderConverter::ConvertViewTimelineAxis(state, value));
}

 // view-timeline-inset



const char* ViewTimelineInset::GetPropertyName() const {
  return "view-timeline-inset";
}

const AtomicString& ViewTimelineInset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-timeline-inset"));
  return name;
}

const char* ViewTimelineInset::GetJSPropertyName() const {
  return "viewTimelineInset";
}



void ViewTimelineInset::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTimelineInset(ComputedStyleInitialValues::InitialViewTimelineInset());
}
void ViewTimelineInset::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTimelineInset(state.ParentStyle()->ViewTimelineInset());
}
void ViewTimelineInset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTimelineInset(StyleBuilderConverter::ConvertViewTimelineInset(state, value));
}

 // view-timeline-name



const char* ViewTimelineName::GetPropertyName() const {
  return "view-timeline-name";
}

const AtomicString& ViewTimelineName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-timeline-name"));
  return name;
}

const char* ViewTimelineName::GetJSPropertyName() const {
  return "viewTimelineName";
}



void ViewTimelineName::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTimelineName(ComputedStyleInitialValues::InitialViewTimelineName());
}
void ViewTimelineName::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTimelineName(state.ParentStyle()->ViewTimelineName());
}
void ViewTimelineName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTimelineName(StyleBuilderConverter::ConvertViewTimelineName(state, value));
}

 // view-transition-class



const char* ViewTransitionClass::GetPropertyName() const {
  return "view-transition-class";
}

const AtomicString& ViewTransitionClass::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-transition-class"));
  return name;
}

const char* ViewTransitionClass::GetJSPropertyName() const {
  return "viewTransitionClass";
}



void ViewTransitionClass::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionClass(ComputedStyleInitialValues::InitialViewTransitionClass());
}
void ViewTransitionClass::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionClass(state.ParentStyle()->ViewTransitionClass());
}
void ViewTransitionClass::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTransitionClass(StyleBuilderConverter::ConvertViewTransitionClass(state, value));
}

 // view-transition-group



const char* ViewTransitionGroup::GetPropertyName() const {
  return "view-transition-group";
}

const AtomicString& ViewTransitionGroup::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-transition-group"));
  return name;
}

const char* ViewTransitionGroup::GetJSPropertyName() const {
  return "viewTransitionGroup";
}



void ViewTransitionGroup::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionGroup(ComputedStyleInitialValues::InitialViewTransitionGroup());
}
void ViewTransitionGroup::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionGroup(state.ParentStyle()->ViewTransitionGroup());
}
void ViewTransitionGroup::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTransitionGroup(StyleBuilderConverter::ConvertViewTransitionGroup(state, value));
}

 // view-transition-name



const char* ViewTransitionName::GetPropertyName() const {
  return "view-transition-name";
}

const AtomicString& ViewTransitionName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-transition-name"));
  return name;
}

const char* ViewTransitionName::GetJSPropertyName() const {
  return "viewTransitionName";
}



void ViewTransitionName::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionName(ComputedStyleInitialValues::InitialViewTransitionName());
}
void ViewTransitionName::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionName(state.ParentStyle()->ViewTransitionName());
}
void ViewTransitionName::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTransitionName(StyleBuilderConverter::ConvertViewTransitionName(state, value));
}

 // view-transition-scope


CSSExposure ViewTransitionScope::Exposure(const ExecutionContext* execution_context) const {
  if (!RuntimeEnabledFeatures::ScopedViewTransitionsEnabled(execution_context)) {
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* ViewTransitionScope::GetPropertyName() const {
  return "view-transition-scope";
}

const AtomicString& ViewTransitionScope::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("view-transition-scope"));
  return name;
}

const char* ViewTransitionScope::GetJSPropertyName() const {
  return "viewTransitionScope";
}



void ViewTransitionScope::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionScope(ComputedStyleInitialValues::InitialViewTransitionScope());
}
void ViewTransitionScope::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetViewTransitionScope(state.ParentStyle()->ViewTransitionScope());
}
void ViewTransitionScope::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetViewTransitionScope(To<CSSIdentifierValue>(value).ConvertTo<blink::EViewTransitionScope>());
}

 // visibility



const char* Visibility::GetPropertyName() const {
  return "visibility";
}

const AtomicString& Visibility::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("visibility"));
  return name;
}

const char* Visibility::GetJSPropertyName() const {
  return "visibility";
}



void Visibility::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetVisibility(ComputedStyleInitialValues::InitialVisibility());
  state.StyleBuilder().SetVisibilityIsInherited(false);
}
void Visibility::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetVisibility(state.ParentStyle()->Visibility());
  state.StyleBuilder().SetVisibilityIsInherited(true);
}
void Visibility::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetVisibility(To<CSSIdentifierValue>(value).ConvertTo<blink::EVisibility>());
  state.StyleBuilder().SetVisibilityIsInherited(false);
}

 // -webkit-border-horizontal-spacing



const char* WebkitBorderHorizontalSpacing::GetPropertyName() const {
  return "-webkit-border-horizontal-spacing";
}

const AtomicString& WebkitBorderHorizontalSpacing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-horizontal-spacing"));
  return name;
}

const char* WebkitBorderHorizontalSpacing::GetJSPropertyName() const {
  return "webkitBorderHorizontalSpacing";
}



void WebkitBorderHorizontalSpacing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHorizontalBorderSpacing(ComputedStyleInitialValues::InitialHorizontalBorderSpacing());
}
void WebkitBorderHorizontalSpacing::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetHorizontalBorderSpacing(state.ParentStyle()->HorizontalBorderSpacing());
}
void WebkitBorderHorizontalSpacing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetHorizontalBorderSpacing(StyleBuilderConverter::ConvertComputedLength<short>(state, value));
}

 // -webkit-border-image



const char* WebkitBorderImage::GetPropertyName() const {
  return "-webkit-border-image";
}

const AtomicString& WebkitBorderImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-image"));
  return name;
}

const char* WebkitBorderImage::GetJSPropertyName() const {
  return "webkitBorderImage";
}


const CSSValue* WebkitBorderImage::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeWebkitBorderImage(stream, context, local_context);
}

void WebkitBorderImage::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderImage(ComputedStyleInitialValues::InitialBorderImage());
}
void WebkitBorderImage::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBorderImage(state.ParentStyle()->BorderImage());
}

 // -webkit-border-vertical-spacing



const char* WebkitBorderVerticalSpacing::GetPropertyName() const {
  return "-webkit-border-vertical-spacing";
}

const AtomicString& WebkitBorderVerticalSpacing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-vertical-spacing"));
  return name;
}

const char* WebkitBorderVerticalSpacing::GetJSPropertyName() const {
  return "webkitBorderVerticalSpacing";
}



void WebkitBorderVerticalSpacing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetVerticalBorderSpacing(ComputedStyleInitialValues::InitialVerticalBorderSpacing());
}
void WebkitBorderVerticalSpacing::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetVerticalBorderSpacing(state.ParentStyle()->VerticalBorderSpacing());
}
void WebkitBorderVerticalSpacing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetVerticalBorderSpacing(StyleBuilderConverter::ConvertComputedLength<short>(state, value));
}

 // -webkit-box-align



const char* WebkitBoxAlign::GetPropertyName() const {
  return "-webkit-box-align";
}

const AtomicString& WebkitBoxAlign::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-align"));
  return name;
}

const char* WebkitBoxAlign::GetJSPropertyName() const {
  return "webkitBoxAlign";
}



void WebkitBoxAlign::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxAlign(ComputedStyleInitialValues::InitialBoxAlign());
}
void WebkitBoxAlign::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxAlign(state.ParentStyle()->BoxAlign());
}
void WebkitBoxAlign::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxAlign(To<CSSIdentifierValue>(value).ConvertTo<blink::EBoxAlignment>());
}

 // -webkit-box-decoration-break



const char* WebkitBoxDecorationBreak::GetPropertyName() const {
  return "-webkit-box-decoration-break";
}

const AtomicString& WebkitBoxDecorationBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-decoration-break"));
  return name;
}

const char* WebkitBoxDecorationBreak::GetJSPropertyName() const {
  return "webkitBoxDecorationBreak";
}


const CSSProperty* WebkitBoxDecorationBreak::SurrogateFor(WritingDirectionMode) const {
  return &GetCSSPropertyBoxDecorationBreak();
}


 // -webkit-box-direction



const char* WebkitBoxDirection::GetPropertyName() const {
  return "-webkit-box-direction";
}

const AtomicString& WebkitBoxDirection::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-direction"));
  return name;
}

const char* WebkitBoxDirection::GetJSPropertyName() const {
  return "webkitBoxDirection";
}



void WebkitBoxDirection::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxDirection(ComputedStyleInitialValues::InitialBoxDirection());
}
void WebkitBoxDirection::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxDirection(state.ParentStyle()->BoxDirection());
}
void WebkitBoxDirection::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxDirection(To<CSSIdentifierValue>(value).ConvertTo<blink::EBoxDirection>());
}

 // -webkit-box-flex



const char* WebkitBoxFlex::GetPropertyName() const {
  return "-webkit-box-flex";
}

const AtomicString& WebkitBoxFlex::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-flex"));
  return name;
}

const char* WebkitBoxFlex::GetJSPropertyName() const {
  return "webkitBoxFlex";
}



void WebkitBoxFlex::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxFlex(ComputedStyleInitialValues::InitialBoxFlex());
}
void WebkitBoxFlex::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxFlex(state.ParentStyle()->BoxFlex());
}
void WebkitBoxFlex::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxFlex(To<CSSPrimitiveValue>(value).ConvertTo<float>(state.CssToLengthConversionData()));
}

 // -webkit-box-ordinal-group



const char* WebkitBoxOrdinalGroup::GetPropertyName() const {
  return "-webkit-box-ordinal-group";
}

const AtomicString& WebkitBoxOrdinalGroup::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-ordinal-group"));
  return name;
}

const char* WebkitBoxOrdinalGroup::GetJSPropertyName() const {
  return "webkitBoxOrdinalGroup";
}


const CSSValue* WebkitBoxOrdinalGroup::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumePositiveInteger(stream, context, local_context);
}

void WebkitBoxOrdinalGroup::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxOrdinalGroup(ComputedStyleInitialValues::InitialBoxOrdinalGroup());
}
void WebkitBoxOrdinalGroup::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxOrdinalGroup(state.ParentStyle()->BoxOrdinalGroup());
}
void WebkitBoxOrdinalGroup::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxOrdinalGroup(To<CSSPrimitiveValue>(value).ConvertTo<unsigned>(state.CssToLengthConversionData()));
}

 // -webkit-box-orient



const char* WebkitBoxOrient::GetPropertyName() const {
  return "-webkit-box-orient";
}

const AtomicString& WebkitBoxOrient::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-orient"));
  return name;
}

const char* WebkitBoxOrient::GetJSPropertyName() const {
  return "webkitBoxOrient";
}



void WebkitBoxOrient::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxOrient(ComputedStyleInitialValues::InitialBoxOrient());
}
void WebkitBoxOrient::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxOrient(state.ParentStyle()->BoxOrient());
}
void WebkitBoxOrient::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxOrient(To<CSSIdentifierValue>(value).ConvertTo<blink::EBoxOrient>());
}

 // -webkit-box-pack



const char* WebkitBoxPack::GetPropertyName() const {
  return "-webkit-box-pack";
}

const AtomicString& WebkitBoxPack::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-pack"));
  return name;
}

const char* WebkitBoxPack::GetJSPropertyName() const {
  return "webkitBoxPack";
}



void WebkitBoxPack::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxPack(ComputedStyleInitialValues::InitialBoxPack());
}
void WebkitBoxPack::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxPack(state.ParentStyle()->BoxPack());
}
void WebkitBoxPack::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxPack(To<CSSIdentifierValue>(value).ConvertTo<blink::EBoxPack>());
}

 // -webkit-box-reflect



const char* WebkitBoxReflect::GetPropertyName() const {
  return "-webkit-box-reflect";
}

const AtomicString& WebkitBoxReflect::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-reflect"));
  return name;
}

const char* WebkitBoxReflect::GetJSPropertyName() const {
  return "webkitBoxReflect";
}



void WebkitBoxReflect::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxReflect(ComputedStyleInitialValues::InitialBoxReflect());
}
void WebkitBoxReflect::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetBoxReflect(state.ParentStyle()->BoxReflect());
}
void WebkitBoxReflect::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetBoxReflect(StyleBuilderConverter::ConvertBoxReflect(state, value));
}

 // -webkit-line-break



const char* WebkitLineBreak::GetPropertyName() const {
  return "-webkit-line-break";
}

const AtomicString& WebkitLineBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-line-break"));
  return name;
}

const char* WebkitLineBreak::GetJSPropertyName() const {
  return "webkitLineBreak";
}


const CSSProperty* WebkitLineBreak::SurrogateFor(WritingDirectionMode) const {
  return &GetCSSPropertyLineBreak();
}


 // -webkit-line-clamp


CSSExposure WebkitLineClamp::Exposure(const ExecutionContext* execution_context) const {
  if (RuntimeEnabledFeatures::CSSLineClampEnabled(execution_context)) {
    // -alternative-webkit-line-clamp
    return CSSExposure::kNone;
  }
  return CSSExposure::kWeb;
}

const char* WebkitLineClamp::GetPropertyName() const {
  return "-webkit-line-clamp";
}

const AtomicString& WebkitLineClamp::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-line-clamp"));
  return name;
}

const char* WebkitLineClamp::GetJSPropertyName() const {
  return "webkitLineClamp";
}



void WebkitLineClamp::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetWebkitLineClamp(ComputedStyleInitialValues::InitialWebkitLineClamp());
}
void WebkitLineClamp::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetWebkitLineClamp(state.ParentStyle()->WebkitLineClamp());
}
void WebkitLineClamp::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetWebkitLineClamp(StyleBuilderConverter::ConvertIntegerOrNone<0>(state, value));
}

 // -webkit-mask-box-image-outset



const char* WebkitMaskBoxImageOutset::GetPropertyName() const {
  return "-webkit-mask-box-image-outset";
}

const AtomicString& WebkitMaskBoxImageOutset::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-box-image-outset"));
  return name;
}

const char* WebkitMaskBoxImageOutset::GetJSPropertyName() const {
  return "webkitMaskBoxImageOutset";
}


const CSSValue* WebkitMaskBoxImageOutset::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderImageOutset(stream, context, local_context);
}

void WebkitMaskBoxImageOutset::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().MaskBoxImage();
  if (style_building_utils::BorderImageLengthMatchesAllSides(current_image.Outset(),
                                       BorderImageLength(0)))
    return;
  NinePieceImage image(current_image);
  image.SetOutset(0);
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageOutset::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  image.CopyOutsetFrom(state.ParentStyle()->MaskBoxImage());
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageOutset::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  image.SetOutset(CSSToStyleMap::MapNinePieceImageQuad(state, value));
  state.StyleBuilder().SetMaskBoxImage(image);
}

 // -webkit-mask-box-image-repeat



const char* WebkitMaskBoxImageRepeat::GetPropertyName() const {
  return "-webkit-mask-box-image-repeat";
}

const AtomicString& WebkitMaskBoxImageRepeat::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-box-image-repeat"));
  return name;
}

const char* WebkitMaskBoxImageRepeat::GetJSPropertyName() const {
  return "webkitMaskBoxImageRepeat";
}



void WebkitMaskBoxImageRepeat::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().MaskBoxImage();
  if (current_image.HorizontalRule() == kStretchImageRule &&
      current_image.VerticalRule() == kStretchImageRule)
    return;
  NinePieceImage image(current_image);
  image.SetHorizontalRule(kStretchImageRule);
  image.SetVerticalRule(kStretchImageRule);
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageRepeat::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  image.CopyRepeatFrom(state.ParentStyle()->MaskBoxImage());
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageRepeat::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  CSSToStyleMap::MapNinePieceImageRepeat(state, value, image);
  state.StyleBuilder().SetMaskBoxImage(image);
}

 // -webkit-mask-box-image-slice



const char* WebkitMaskBoxImageSlice::GetPropertyName() const {
  return "-webkit-mask-box-image-slice";
}

const AtomicString& WebkitMaskBoxImageSlice::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-box-image-slice"));
  return name;
}

const char* WebkitMaskBoxImageSlice::GetJSPropertyName() const {
  return "webkitMaskBoxImageSlice";
}



void WebkitMaskBoxImageSlice::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().MaskBoxImage();
  // Masks have a different initial value for slices. Preserve the value of 0
  // for backwards compatibility.
  if (current_image.Fill() == true &&
      style_building_utils::LengthMatchesAllSides(current_image.ImageSlices(), Length::Fixed(0)))
    return;
  NinePieceImage image(current_image);
  image.SetImageSlices(LengthBox(Length::Fixed(0), Length::Fixed(0), Length::Fixed(0), Length::Fixed(0)));
  image.SetFill(true);
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageSlice::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  image.CopyImageSlicesFrom(state.ParentStyle()->MaskBoxImage());
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageSlice::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  CSSToStyleMap::MapNinePieceImageSlice(state, value, image);
  state.StyleBuilder().SetMaskBoxImage(image);
}

 // -webkit-mask-box-image-source



const char* WebkitMaskBoxImageSource::GetPropertyName() const {
  return "-webkit-mask-box-image-source";
}

const AtomicString& WebkitMaskBoxImageSource::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-box-image-source"));
  return name;
}

const char* WebkitMaskBoxImageSource::GetJSPropertyName() const {
  return "webkitMaskBoxImageSource";
}


const CSSValue* WebkitMaskBoxImageSource::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeImageOrNone(stream, context, local_context);
}

void WebkitMaskBoxImageSource::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetMaskBoxImageSource(ComputedStyleInitialValues::InitialMaskBoxImageSource());
}
void WebkitMaskBoxImageSource::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetMaskBoxImageSource(state.ParentStyle()->MaskBoxImageSource());
}

 // -webkit-mask-box-image-width



const char* WebkitMaskBoxImageWidth::GetPropertyName() const {
  return "-webkit-mask-box-image-width";
}

const AtomicString& WebkitMaskBoxImageWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-box-image-width"));
  return name;
}

const char* WebkitMaskBoxImageWidth::GetJSPropertyName() const {
  return "webkitMaskBoxImageWidth";
}


const CSSValue* WebkitMaskBoxImageWidth::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeBorderImageWidth(stream, context, local_context);
}

void WebkitMaskBoxImageWidth::ApplyInitial(StyleResolverState& state) const {
  const NinePieceImage& current_image = state.StyleBuilder().MaskBoxImage();
  // Masks have a different initial value for widths. Preserve the value of
  // 'auto' for backwards compatibility.
  if (style_building_utils::BorderImageLengthMatchesAllSides(current_image.BorderSlices(),
                                       BorderImageLength(Length::Auto())))
    return;
  NinePieceImage image(current_image);
  image.SetBorderSlices(Length::Auto());
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageWidth::ApplyInherit(StyleResolverState& state) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  image.CopyBorderSlicesFrom(state.ParentStyle()->MaskBoxImage());
  state.StyleBuilder().SetMaskBoxImage(image);
}
void WebkitMaskBoxImageWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  NinePieceImage image(state.StyleBuilder().MaskBoxImage());
  image.SetBorderSlices(CSSToStyleMap::MapNinePieceImageQuad(state, value));
  state.StyleBuilder().SetMaskBoxImage(image);
}

 // -webkit-mask-position-x



const char* WebkitMaskPositionX::GetPropertyName() const {
  return "-webkit-mask-position-x";
}

const AtomicString& WebkitMaskPositionX::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-position-x"));
  return name;
}

const char* WebkitMaskPositionX::GetJSPropertyName() const {
  return "webkitMaskPositionX";
}



void WebkitMaskPositionX::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetPositionX(FillLayer::InitialFillPositionX(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearPositionX();
}

void WebkitMaskPositionX::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsPositionXSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetPositionX(curr_parent->PositionX());
    if (curr_parent->IsBackgroundXOriginSet())
      curr_child->SetBackgroundXOrigin(curr_parent->BackgroundXOrigin());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearPositionX();
    curr_child = curr_child->Next();
  }
}

void WebkitMaskPositionX::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillPositionX(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillPositionX(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearPositionX();
    curr_child = curr_child->Next();
  }
}

 // -webkit-mask-position-y



const char* WebkitMaskPositionY::GetPropertyName() const {
  return "-webkit-mask-position-y";
}

const AtomicString& WebkitMaskPositionY::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-position-y"));
  return name;
}

const char* WebkitMaskPositionY::GetJSPropertyName() const {
  return "webkitMaskPositionY";
}



void WebkitMaskPositionY::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetPositionY(FillLayer::InitialFillPositionY(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearPositionY();
}

void WebkitMaskPositionY::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsPositionYSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetPositionY(curr_parent->PositionY());
    if (curr_parent->IsBackgroundYOriginSet())
      curr_child->SetBackgroundYOrigin(curr_parent->BackgroundYOrigin());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearPositionY();
    curr_child = curr_child->Next();
  }
}

void WebkitMaskPositionY::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillPositionY(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillPositionY(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearPositionY();
    curr_child = curr_child->Next();
  }
}

 // -webkit-perspective-origin-x



const char* WebkitPerspectiveOriginX::GetPropertyName() const {
  return "-webkit-perspective-origin-x";
}

const AtomicString& WebkitPerspectiveOriginX::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-perspective-origin-x"));
  return name;
}

const char* WebkitPerspectiveOriginX::GetJSPropertyName() const {
  return "webkitPerspectiveOriginX";
}



void WebkitPerspectiveOriginX::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPerspectiveOriginX(ComputedStyleInitialValues::InitialPerspectiveOriginX());
}
void WebkitPerspectiveOriginX::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPerspectiveOriginX(StyleBuilderConverter::ConvertLength(state, value));
}

 // -webkit-perspective-origin-y



const char* WebkitPerspectiveOriginY::GetPropertyName() const {
  return "-webkit-perspective-origin-y";
}

const AtomicString& WebkitPerspectiveOriginY::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-perspective-origin-y"));
  return name;
}

const char* WebkitPerspectiveOriginY::GetJSPropertyName() const {
  return "webkitPerspectiveOriginY";
}



void WebkitPerspectiveOriginY::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetPerspectiveOriginY(ComputedStyleInitialValues::InitialPerspectiveOriginY());
}
void WebkitPerspectiveOriginY::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetPerspectiveOriginY(StyleBuilderConverter::ConvertLength(state, value));
}

 // -webkit-rtl-ordering



const char* WebkitRtlOrdering::GetPropertyName() const {
  return "-webkit-rtl-ordering";
}

const AtomicString& WebkitRtlOrdering::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-rtl-ordering"));
  return name;
}

const char* WebkitRtlOrdering::GetJSPropertyName() const {
  return "webkitRtlOrdering";
}



void WebkitRtlOrdering::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetRtlOrdering(ComputedStyleInitialValues::InitialRtlOrdering());
  state.StyleBuilder().SetRtlOrderingIsInherited(false);
}
void WebkitRtlOrdering::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetRtlOrdering(state.ParentStyle()->RtlOrdering());
  state.StyleBuilder().SetRtlOrderingIsInherited(true);
}
void WebkitRtlOrdering::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetRtlOrdering(To<CSSIdentifierValue>(value).ConvertTo<blink::EOrder>());
  state.StyleBuilder().SetRtlOrderingIsInherited(false);
}

 // -webkit-ruby-position



const char* WebkitRubyPosition::GetPropertyName() const {
  return "-webkit-ruby-position";
}

const AtomicString& WebkitRubyPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-ruby-position"));
  return name;
}

const char* WebkitRubyPosition::GetJSPropertyName() const {
  return "webkitRubyPosition";
}


const CSSProperty* WebkitRubyPosition::SurrogateFor(WritingDirectionMode) const {
  return &GetCSSPropertyRubyPosition();
}


 // -webkit-tap-highlight-color



const char* WebkitTapHighlightColor::GetPropertyName() const {
  return "-webkit-tap-highlight-color";
}

const AtomicString& WebkitTapHighlightColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-tap-highlight-color"));
  return name;
}

const char* WebkitTapHighlightColor::GetJSPropertyName() const {
  return "webkitTapHighlightColor";
}


const CSSValue* WebkitTapHighlightColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void WebkitTapHighlightColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTapHighlightColor(ComputedStyleInitialValues::InitialTapHighlightColor());
}
void WebkitTapHighlightColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTapHighlightColor(state.ParentStyle()->TapHighlightColor());
}
void WebkitTapHighlightColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTapHighlightColor(StyleBuilderConverter::ConvertStyleColor(state, value));
}

 // -webkit-text-combine



const char* WebkitTextCombine::GetPropertyName() const {
  return "-webkit-text-combine";
}

const AtomicString& WebkitTextCombine::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-combine"));
  return name;
}

const char* WebkitTextCombine::GetJSPropertyName() const {
  return "webkitTextCombine";
}


const CSSProperty* WebkitTextCombine::SurrogateFor(WritingDirectionMode) const {
  return &GetCSSPropertyTextCombineUpright();
}


 // -webkit-text-decorations-in-effect



const char* WebkitTextDecorationsInEffect::GetPropertyName() const {
  return "-webkit-text-decorations-in-effect";
}

const AtomicString& WebkitTextDecorationsInEffect::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-decorations-in-effect"));
  return name;
}

const char* WebkitTextDecorationsInEffect::GetJSPropertyName() const {
  return "webkitTextDecorationsInEffect";
}



void WebkitTextDecorationsInEffect::ApplyInitial(StyleResolverState& state) const {
  // Intentionally empty.
}
void WebkitTextDecorationsInEffect::ApplyInherit(StyleResolverState& state) const {
  // Intentionally empty.
}
void WebkitTextDecorationsInEffect::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  // Intentionally empty.
}

 // -webkit-text-fill-color



const char* WebkitTextFillColor::GetPropertyName() const {
  return "-webkit-text-fill-color";
}

const AtomicString& WebkitTextFillColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-fill-color"));
  return name;
}

const char* WebkitTextFillColor::GetJSPropertyName() const {
  return "webkitTextFillColor";
}


const CSSValue* WebkitTextFillColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void WebkitTextFillColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextFillColor(StyleColor::CurrentColor());
}

void WebkitTextFillColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextFillColor(state.ParentStyle()->TextFillColor());
}

void WebkitTextFillColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextFillColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // -webkit-text-security



const char* WebkitTextSecurity::GetPropertyName() const {
  return "-webkit-text-security";
}

const AtomicString& WebkitTextSecurity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-security"));
  return name;
}

const char* WebkitTextSecurity::GetJSPropertyName() const {
  return "webkitTextSecurity";
}



void WebkitTextSecurity::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextSecurity(ComputedStyleInitialValues::InitialTextSecurity());
}
void WebkitTextSecurity::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextSecurity(state.ParentStyle()->TextSecurity());
}
void WebkitTextSecurity::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextSecurity(To<CSSIdentifierValue>(value).ConvertTo<blink::ETextSecurity>());
}

 // -webkit-text-stroke-color



const char* WebkitTextStrokeColor::GetPropertyName() const {
  return "-webkit-text-stroke-color";
}

const AtomicString& WebkitTextStrokeColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-stroke-color"));
  return name;
}

const char* WebkitTextStrokeColor::GetJSPropertyName() const {
  return "webkitTextStrokeColor";
}


const CSSValue* WebkitTextStrokeColor::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumeColor(stream, context, local_context);
}

void WebkitTextStrokeColor::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextStrokeColor(StyleColor::CurrentColor());
}

void WebkitTextStrokeColor::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetTextStrokeColor(state.ParentStyle()->TextStrokeColor());
}

void WebkitTextStrokeColor::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextStrokeColor(StyleBuilderConverter::ConvertStyleColor(state, value, false));
}

 // -webkit-text-stroke-width



const char* WebkitTextStrokeWidth::GetPropertyName() const {
  return "-webkit-text-stroke-width";
}

const AtomicString& WebkitTextStrokeWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-stroke-width"));
  return name;
}

const char* WebkitTextStrokeWidth::GetJSPropertyName() const {
  return "webkitTextStrokeWidth";
}



void WebkitTextStrokeWidth::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTextStrokeWidth(ComputedStyleInitialValues::InitialTextStrokeWidth());
}
void WebkitTextStrokeWidth::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetTextStrokeWidth(state.ParentStyle()->TextStrokeWidth());
}
void WebkitTextStrokeWidth::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTextStrokeWidth(StyleBuilderConverter::ConvertTextStrokeWidth(state, value));
}

 // -webkit-transform-origin-x



const char* WebkitTransformOriginX::GetPropertyName() const {
  return "-webkit-transform-origin-x";
}

const AtomicString& WebkitTransformOriginX::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transform-origin-x"));
  return name;
}

const char* WebkitTransformOriginX::GetJSPropertyName() const {
  return "webkitTransformOriginX";
}



void WebkitTransformOriginX::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformOriginX(ComputedStyleInitialValues::InitialTransformOriginX());
}
void WebkitTransformOriginX::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransformOriginX(StyleBuilderConverter::ConvertLength(state, value));
}

 // -webkit-transform-origin-y



const char* WebkitTransformOriginY::GetPropertyName() const {
  return "-webkit-transform-origin-y";
}

const AtomicString& WebkitTransformOriginY::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transform-origin-y"));
  return name;
}

const char* WebkitTransformOriginY::GetJSPropertyName() const {
  return "webkitTransformOriginY";
}



void WebkitTransformOriginY::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformOriginY(ComputedStyleInitialValues::InitialTransformOriginY());
}
void WebkitTransformOriginY::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransformOriginY(StyleBuilderConverter::ConvertLength(state, value));
}

 // -webkit-transform-origin-z



const char* WebkitTransformOriginZ::GetPropertyName() const {
  return "-webkit-transform-origin-z";
}

const AtomicString& WebkitTransformOriginZ::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transform-origin-z"));
  return name;
}

const char* WebkitTransformOriginZ::GetJSPropertyName() const {
  return "webkitTransformOriginZ";
}



void WebkitTransformOriginZ::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetTransformOriginZ(ComputedStyleInitialValues::InitialTransformOriginZ());
}
void WebkitTransformOriginZ::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetTransformOriginZ(StyleBuilderConverter::ConvertComputedLength<float>(state, value));
}

 // -webkit-user-drag



const char* WebkitUserDrag::GetPropertyName() const {
  return "-webkit-user-drag";
}

const AtomicString& WebkitUserDrag::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-user-drag"));
  return name;
}

const char* WebkitUserDrag::GetJSPropertyName() const {
  return "webkitUserDrag";
}



void WebkitUserDrag::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetUserDrag(ComputedStyleInitialValues::InitialUserDrag());
}
void WebkitUserDrag::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetUserDrag(state.ParentStyle()->UserDrag());
}
void WebkitUserDrag::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetUserDrag(To<CSSIdentifierValue>(value).ConvertTo<blink::EUserDrag>());
}

 // -webkit-user-modify



const char* WebkitUserModify::GetPropertyName() const {
  return "-webkit-user-modify";
}

const AtomicString& WebkitUserModify::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-user-modify"));
  return name;
}

const char* WebkitUserModify::GetJSPropertyName() const {
  return "webkitUserModify";
}



void WebkitUserModify::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetUserModify(ComputedStyleInitialValues::InitialUserModify());
}
void WebkitUserModify::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetUserModify(state.ParentStyle()->UserModify());
}
void WebkitUserModify::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetUserModify(To<CSSIdentifierValue>(value).ConvertTo<blink::EUserModify>());
}

 // white-space-collapse



const char* WhiteSpaceCollapse::GetPropertyName() const {
  return "white-space-collapse";
}

const AtomicString& WhiteSpaceCollapse::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("white-space-collapse"));
  return name;
}

const char* WhiteSpaceCollapse::GetJSPropertyName() const {
  return "whiteSpaceCollapse";
}



void WhiteSpaceCollapse::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetWhiteSpaceCollapse(ComputedStyleInitialValues::InitialWhiteSpaceCollapse());
}
void WhiteSpaceCollapse::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetWhiteSpaceCollapse(state.ParentStyle()->GetWhiteSpaceCollapse());
}
void WhiteSpaceCollapse::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetWhiteSpaceCollapse(To<CSSIdentifierValue>(value).ConvertTo<blink::WhiteSpaceCollapse>());
}

 // widows



const char* Widows::GetPropertyName() const {
  return "widows";
}

const AtomicString& Widows::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("widows"));
  return name;
}

const char* Widows::GetJSPropertyName() const {
  return "widows";
}


const CSSValue* Widows::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ConsumePositiveInteger(stream, context, local_context);
}

void Widows::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetWidows(ComputedStyleInitialValues::InitialWidows());
}
void Widows::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetWidows(state.ParentStyle()->Widows());
}
void Widows::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetWidows(To<CSSPrimitiveValue>(value).ConvertTo<short>(state.CssToLengthConversionData()));
}

 // width



const char* Width::GetPropertyName() const {
  return "width";
}

const AtomicString& Width::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("width"));
  return name;
}

const char* Width::GetJSPropertyName() const {
  return "width";
}


bool Width::IsInSameLogicalPropertyGroupWithDifferentMappingLogic(
    CSSPropertyID id) const {
  return CSSDirectionAwareResolver::LogicalSizeMapping().Contains(id);
}
const CSSProperty& Width::ToLogicalInternal(
    WritingDirectionMode writing_direction) const {
  return CSSDirectionAwareResolver::ResolveHorizontal(writing_direction,
      CSSDirectionAwareResolver::LogicalSizeMapping());
}

void Width::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetWidth(ComputedStyleInitialValues::InitialWidth());
}
void Width::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetWidth(state.ParentStyle()->Width());
}
void Width::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  blink::AnchorScope anchor_scope(
      blink::AnchorScope::Mode::kWidth,
      state.CssToLengthConversionData().GetAnchorEvaluator());
  state.StyleBuilder().SetWidth(StyleBuilderConverter::ConvertLengthSizing(state, value));
}

 // will-change



const char* WillChange::GetPropertyName() const {
  return "will-change";
}

const AtomicString& WillChange::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("will-change"));
  return name;
}

const char* WillChange::GetJSPropertyName() const {
  return "willChange";
}




 // word-break



const char* WordBreak::GetPropertyName() const {
  return "word-break";
}

const AtomicString& WordBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("word-break"));
  return name;
}

const char* WordBreak::GetJSPropertyName() const {
  return "wordBreak";
}



void WordBreak::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetWordBreak(ComputedStyleInitialValues::InitialWordBreak());
}
void WordBreak::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetWordBreak(state.ParentStyle()->WordBreak());
}

 // word-spacing



const char* WordSpacing::GetPropertyName() const {
  return "word-spacing";
}

const AtomicString& WordSpacing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("word-spacing"));
  return name;
}

const char* WordSpacing::GetJSPropertyName() const {
  return "wordSpacing";
}


const CSSValue* WordSpacing::ParseSingleValue(
    CSSParserTokenStream& stream,
    const CSSParserContext& context,
    CSSParserLocalContext& local_context) const {
  return css_parsing_utils::ParseSpacing(stream, context, local_context);
}

void WordSpacing::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetWordSpacing(ComputedStyleInitialValues::InitialWordSpacing());
}
void WordSpacing::ApplyInherit(StyleResolverState& state) const {
  if (state.GetDocument().StandardizedBrowserZoomEnabled()) {
    if (ApplyParentValueIfZoomChanged(state)) {
      return;
    }
  }
  state.StyleBuilder().SetWordSpacing(state.ParentStyle()->ComputedWordSpacing());
}
void WordSpacing::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetWordSpacing(StyleBuilderConverter::ConvertSpacing(state, value));
}

 // x



const char* X::GetPropertyName() const {
  return "x";
}

const AtomicString& X::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("x"));
  return name;
}

const char* X::GetJSPropertyName() const {
  return "x";
}



void X::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetX(ComputedStyleInitialValues::InitialX());
}
void X::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetX(state.ParentStyle()->X());
}
void X::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetX(StyleBuilderConverter::ConvertLength(state, value));
}

 // y



const char* Y::GetPropertyName() const {
  return "y";
}

const AtomicString& Y::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("y"));
  return name;
}

const char* Y::GetJSPropertyName() const {
  return "y";
}



void Y::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetY(ComputedStyleInitialValues::InitialY());
}
void Y::ApplyInherit(StyleResolverState& state) const {
  state.StyleBuilder().SetY(state.ParentStyle()->Y());
}
void Y::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  state.StyleBuilder().SetY(StyleBuilderConverter::ConvertLength(state, value));
}

 // z-index



const char* ZIndex::GetPropertyName() const {
  return "z-index";
}

const AtomicString& ZIndex::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("z-index"));
  return name;
}

const char* ZIndex::GetJSPropertyName() const {
  return "zIndex";
}



void ZIndex::ApplyInitial(StyleResolverState& state) const {
  state.StyleBuilder().SetHasAutoZIndex();
}
void ZIndex::ApplyInherit(StyleResolverState& state) const {
  if (state.ParentStyle()->HasAutoZIndex())
    state.StyleBuilder().SetHasAutoZIndex();
  else
    state.StyleBuilder().SetZIndex(state.ParentStyle()->ZIndex());
}
void ZIndex::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  auto* identifier_value = DynamicTo<CSSIdentifierValue>(value);
  if (identifier_value && identifier_value->GetValueID() == CSSValueID::kAuto)
    state.StyleBuilder().SetHasAutoZIndex();
  else
    state.StyleBuilder().SetZIndex(StyleBuilderConverter::ConvertInteger(state, value));
}

 // mask-composite



const char* MaskComposite::GetPropertyName() const {
  return "mask-composite";
}

const AtomicString& MaskComposite::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("mask-composite"));
  return name;
}

const char* MaskComposite::GetJSPropertyName() const {
  return "maskComposite";
}



void MaskComposite::ApplyInitial(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  curr_child->SetCompositingOperator(FillLayer::InitialFillCompositingOperator(EFillLayerType::kMask));
  for (curr_child = curr_child->Next(); curr_child; curr_child = curr_child->Next())
    curr_child->ClearCompositingOperator();
}

void MaskComposite::ApplyInherit(StyleResolverState& state) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const FillLayer* curr_parent = &state.ParentStyle()->MaskLayers();
  while (curr_parent && curr_parent->IsCompositingOperatorSet()) {
    if (!curr_child)
      curr_child = prev_child->EnsureNext();
    curr_child->SetCompositingOperator(curr_parent->CompositingOperator());
    prev_child = curr_child;
    curr_child = prev_child->Next();
    curr_parent = curr_parent->Next();
  }

  while (curr_child) {
    // Reset any remaining layers to not have the property set.
    curr_child->ClearCompositingOperator();
    curr_child = curr_child->Next();
  }
}

void MaskComposite::ApplyValue(StyleResolverState& state, const CSSValue& value, ValueModeFlags) const {
  FillLayer* curr_child = &state.StyleBuilder().AccessMaskLayers();
  FillLayer* prev_child = 0;
  const auto* value_list = DynamicTo<CSSValueList>(value);
  if (value_list && !value.IsImageSetValue()) {
    // Walk each value and put it into a layer, creating new layers as needed.
    for (unsigned int i = 0; i < value_list->length(); i++) {
      if (!curr_child)
        curr_child = prev_child->EnsureNext();
      CSSToStyleMap::MapFillCompositingOperator(state, curr_child, value_list->Item(i));
      prev_child = curr_child;
      curr_child = curr_child->Next();
    }
  } else {
    CSSToStyleMap::MapFillCompositingOperator(state, curr_child, value);
    curr_child = curr_child->Next();
  }
  while (curr_child) {
    // Reset all remaining layers to not have the property set.
    curr_child->ClearCompositingOperator();
    curr_child = curr_child->Next();
  }
}

 // -webkit-appearance



const char* WebkitAppearance::GetPropertyName() const {
  return "-webkit-appearance";
}

const AtomicString& WebkitAppearance::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-appearance"));
  return name;
}

const char* WebkitAppearance::GetJSPropertyName() const {
  return "webkitAppearance";
}

 // -webkit-app-region



const char* WebkitAppRegion::GetPropertyName() const {
  return "-webkit-app-region";
}

const AtomicString& WebkitAppRegion::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-app-region"));
  return name;
}

const char* WebkitAppRegion::GetJSPropertyName() const {
  return "webkitAppRegion";
}

 // -webkit-mask-clip



const char* WebkitMaskClip::GetPropertyName() const {
  return "-webkit-mask-clip";
}

const AtomicString& WebkitMaskClip::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-clip"));
  return name;
}

const char* WebkitMaskClip::GetJSPropertyName() const {
  return "webkitMaskClip";
}

 // -webkit-mask-composite



const char* WebkitMaskComposite::GetPropertyName() const {
  return "-webkit-mask-composite";
}

const AtomicString& WebkitMaskComposite::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-composite"));
  return name;
}

const char* WebkitMaskComposite::GetJSPropertyName() const {
  return "webkitMaskComposite";
}

 // -webkit-mask-image



const char* WebkitMaskImage::GetPropertyName() const {
  return "-webkit-mask-image";
}

const AtomicString& WebkitMaskImage::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-image"));
  return name;
}

const char* WebkitMaskImage::GetJSPropertyName() const {
  return "webkitMaskImage";
}

 // -webkit-mask-origin



const char* WebkitMaskOrigin::GetPropertyName() const {
  return "-webkit-mask-origin";
}

const AtomicString& WebkitMaskOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-origin"));
  return name;
}

const char* WebkitMaskOrigin::GetJSPropertyName() const {
  return "webkitMaskOrigin";
}

 // -webkit-mask-repeat



const char* WebkitMaskRepeat::GetPropertyName() const {
  return "-webkit-mask-repeat";
}

const AtomicString& WebkitMaskRepeat::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-repeat"));
  return name;
}

const char* WebkitMaskRepeat::GetJSPropertyName() const {
  return "webkitMaskRepeat";
}

 // -webkit-mask-size



const char* WebkitMaskSize::GetPropertyName() const {
  return "-webkit-mask-size";
}

const AtomicString& WebkitMaskSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-mask-size"));
  return name;
}

const char* WebkitMaskSize::GetJSPropertyName() const {
  return "webkitMaskSize";
}

 // -webkit-border-end-color



const char* WebkitBorderEndColor::GetPropertyName() const {
  return "-webkit-border-end-color";
}

const AtomicString& WebkitBorderEndColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-end-color"));
  return name;
}

const char* WebkitBorderEndColor::GetJSPropertyName() const {
  return "webkitBorderEndColor";
}

 // -webkit-border-end-style



const char* WebkitBorderEndStyle::GetPropertyName() const {
  return "-webkit-border-end-style";
}

const AtomicString& WebkitBorderEndStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-end-style"));
  return name;
}

const char* WebkitBorderEndStyle::GetJSPropertyName() const {
  return "webkitBorderEndStyle";
}

 // -webkit-border-end-width



const char* WebkitBorderEndWidth::GetPropertyName() const {
  return "-webkit-border-end-width";
}

const AtomicString& WebkitBorderEndWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-end-width"));
  return name;
}

const char* WebkitBorderEndWidth::GetJSPropertyName() const {
  return "webkitBorderEndWidth";
}

 // -webkit-border-start-color



const char* WebkitBorderStartColor::GetPropertyName() const {
  return "-webkit-border-start-color";
}

const AtomicString& WebkitBorderStartColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-start-color"));
  return name;
}

const char* WebkitBorderStartColor::GetJSPropertyName() const {
  return "webkitBorderStartColor";
}

 // -webkit-border-start-style



const char* WebkitBorderStartStyle::GetPropertyName() const {
  return "-webkit-border-start-style";
}

const AtomicString& WebkitBorderStartStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-start-style"));
  return name;
}

const char* WebkitBorderStartStyle::GetJSPropertyName() const {
  return "webkitBorderStartStyle";
}

 // -webkit-border-start-width



const char* WebkitBorderStartWidth::GetPropertyName() const {
  return "-webkit-border-start-width";
}

const AtomicString& WebkitBorderStartWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-start-width"));
  return name;
}

const char* WebkitBorderStartWidth::GetJSPropertyName() const {
  return "webkitBorderStartWidth";
}

 // -webkit-border-before-color



const char* WebkitBorderBeforeColor::GetPropertyName() const {
  return "-webkit-border-before-color";
}

const AtomicString& WebkitBorderBeforeColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-before-color"));
  return name;
}

const char* WebkitBorderBeforeColor::GetJSPropertyName() const {
  return "webkitBorderBeforeColor";
}

 // -webkit-border-before-style



const char* WebkitBorderBeforeStyle::GetPropertyName() const {
  return "-webkit-border-before-style";
}

const AtomicString& WebkitBorderBeforeStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-before-style"));
  return name;
}

const char* WebkitBorderBeforeStyle::GetJSPropertyName() const {
  return "webkitBorderBeforeStyle";
}

 // -webkit-border-before-width



const char* WebkitBorderBeforeWidth::GetPropertyName() const {
  return "-webkit-border-before-width";
}

const AtomicString& WebkitBorderBeforeWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-before-width"));
  return name;
}

const char* WebkitBorderBeforeWidth::GetJSPropertyName() const {
  return "webkitBorderBeforeWidth";
}

 // -webkit-border-after-color



const char* WebkitBorderAfterColor::GetPropertyName() const {
  return "-webkit-border-after-color";
}

const AtomicString& WebkitBorderAfterColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-after-color"));
  return name;
}

const char* WebkitBorderAfterColor::GetJSPropertyName() const {
  return "webkitBorderAfterColor";
}

 // -webkit-border-after-style



const char* WebkitBorderAfterStyle::GetPropertyName() const {
  return "-webkit-border-after-style";
}

const AtomicString& WebkitBorderAfterStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-after-style"));
  return name;
}

const char* WebkitBorderAfterStyle::GetJSPropertyName() const {
  return "webkitBorderAfterStyle";
}

 // -webkit-border-after-width



const char* WebkitBorderAfterWidth::GetPropertyName() const {
  return "-webkit-border-after-width";
}

const AtomicString& WebkitBorderAfterWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-after-width"));
  return name;
}

const char* WebkitBorderAfterWidth::GetJSPropertyName() const {
  return "webkitBorderAfterWidth";
}

 // -webkit-margin-end



const char* WebkitMarginEnd::GetPropertyName() const {
  return "-webkit-margin-end";
}

const AtomicString& WebkitMarginEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-margin-end"));
  return name;
}

const char* WebkitMarginEnd::GetJSPropertyName() const {
  return "webkitMarginEnd";
}

 // -webkit-margin-start



const char* WebkitMarginStart::GetPropertyName() const {
  return "-webkit-margin-start";
}

const AtomicString& WebkitMarginStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-margin-start"));
  return name;
}

const char* WebkitMarginStart::GetJSPropertyName() const {
  return "webkitMarginStart";
}

 // -webkit-margin-before



const char* WebkitMarginBefore::GetPropertyName() const {
  return "-webkit-margin-before";
}

const AtomicString& WebkitMarginBefore::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-margin-before"));
  return name;
}

const char* WebkitMarginBefore::GetJSPropertyName() const {
  return "webkitMarginBefore";
}

 // -webkit-margin-after



const char* WebkitMarginAfter::GetPropertyName() const {
  return "-webkit-margin-after";
}

const AtomicString& WebkitMarginAfter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-margin-after"));
  return name;
}

const char* WebkitMarginAfter::GetJSPropertyName() const {
  return "webkitMarginAfter";
}

 // -webkit-padding-end



const char* WebkitPaddingEnd::GetPropertyName() const {
  return "-webkit-padding-end";
}

const AtomicString& WebkitPaddingEnd::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-padding-end"));
  return name;
}

const char* WebkitPaddingEnd::GetJSPropertyName() const {
  return "webkitPaddingEnd";
}

 // -webkit-padding-start



const char* WebkitPaddingStart::GetPropertyName() const {
  return "-webkit-padding-start";
}

const AtomicString& WebkitPaddingStart::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-padding-start"));
  return name;
}

const char* WebkitPaddingStart::GetJSPropertyName() const {
  return "webkitPaddingStart";
}

 // -webkit-padding-before



const char* WebkitPaddingBefore::GetPropertyName() const {
  return "-webkit-padding-before";
}

const AtomicString& WebkitPaddingBefore::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-padding-before"));
  return name;
}

const char* WebkitPaddingBefore::GetJSPropertyName() const {
  return "webkitPaddingBefore";
}

 // -webkit-padding-after



const char* WebkitPaddingAfter::GetPropertyName() const {
  return "-webkit-padding-after";
}

const AtomicString& WebkitPaddingAfter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-padding-after"));
  return name;
}

const char* WebkitPaddingAfter::GetJSPropertyName() const {
  return "webkitPaddingAfter";
}

 // -webkit-logical-width



const char* WebkitLogicalWidth::GetPropertyName() const {
  return "-webkit-logical-width";
}

const AtomicString& WebkitLogicalWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-logical-width"));
  return name;
}

const char* WebkitLogicalWidth::GetJSPropertyName() const {
  return "webkitLogicalWidth";
}

 // -webkit-logical-height



const char* WebkitLogicalHeight::GetPropertyName() const {
  return "-webkit-logical-height";
}

const AtomicString& WebkitLogicalHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-logical-height"));
  return name;
}

const char* WebkitLogicalHeight::GetJSPropertyName() const {
  return "webkitLogicalHeight";
}

 // -webkit-min-logical-width



const char* WebkitMinLogicalWidth::GetPropertyName() const {
  return "-webkit-min-logical-width";
}

const AtomicString& WebkitMinLogicalWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-min-logical-width"));
  return name;
}

const char* WebkitMinLogicalWidth::GetJSPropertyName() const {
  return "webkitMinLogicalWidth";
}

 // -webkit-min-logical-height



const char* WebkitMinLogicalHeight::GetPropertyName() const {
  return "-webkit-min-logical-height";
}

const AtomicString& WebkitMinLogicalHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-min-logical-height"));
  return name;
}

const char* WebkitMinLogicalHeight::GetJSPropertyName() const {
  return "webkitMinLogicalHeight";
}

 // -webkit-max-logical-width



const char* WebkitMaxLogicalWidth::GetPropertyName() const {
  return "-webkit-max-logical-width";
}

const AtomicString& WebkitMaxLogicalWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-max-logical-width"));
  return name;
}

const char* WebkitMaxLogicalWidth::GetJSPropertyName() const {
  return "webkitMaxLogicalWidth";
}

 // -webkit-max-logical-height



const char* WebkitMaxLogicalHeight::GetPropertyName() const {
  return "-webkit-max-logical-height";
}

const AtomicString& WebkitMaxLogicalHeight::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-max-logical-height"));
  return name;
}

const char* WebkitMaxLogicalHeight::GetJSPropertyName() const {
  return "webkitMaxLogicalHeight";
}

 // -webkit-print-color-adjust



const char* WebkitPrintColorAdjust::GetPropertyName() const {
  return "-webkit-print-color-adjust";
}

const AtomicString& WebkitPrintColorAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-print-color-adjust"));
  return name;
}

const char* WebkitPrintColorAdjust::GetJSPropertyName() const {
  return "webkitPrintColorAdjust";
}

 // -epub-caption-side



const char* EpubCaptionSide::GetPropertyName() const {
  return "-epub-caption-side";
}

const AtomicString& EpubCaptionSide::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-caption-side"));
  return name;
}

const char* EpubCaptionSide::GetJSPropertyName() const {
  return "epubCaptionSide";
}

 // -epub-text-combine



const char* EpubTextCombine::GetPropertyName() const {
  return "-epub-text-combine";
}

const AtomicString& EpubTextCombine::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-text-combine"));
  return name;
}

const char* EpubTextCombine::GetJSPropertyName() const {
  return "epubTextCombine";
}

 // -epub-text-emphasis-color



const char* EpubTextEmphasisColor::GetPropertyName() const {
  return "-epub-text-emphasis-color";
}

const AtomicString& EpubTextEmphasisColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-text-emphasis-color"));
  return name;
}

const char* EpubTextEmphasisColor::GetJSPropertyName() const {
  return "epubTextEmphasisColor";
}

 // -epub-text-emphasis-style



const char* EpubTextEmphasisStyle::GetPropertyName() const {
  return "-epub-text-emphasis-style";
}

const AtomicString& EpubTextEmphasisStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-text-emphasis-style"));
  return name;
}

const char* EpubTextEmphasisStyle::GetJSPropertyName() const {
  return "epubTextEmphasisStyle";
}

 // -epub-text-orientation



const char* EpubTextOrientation::GetPropertyName() const {
  return "-epub-text-orientation";
}

const AtomicString& EpubTextOrientation::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-text-orientation"));
  return name;
}

const char* EpubTextOrientation::GetJSPropertyName() const {
  return "epubTextOrientation";
}

 // -epub-text-transform



const char* EpubTextTransform::GetPropertyName() const {
  return "-epub-text-transform";
}

const AtomicString& EpubTextTransform::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-text-transform"));
  return name;
}

const char* EpubTextTransform::GetJSPropertyName() const {
  return "epubTextTransform";
}

 // -epub-word-break



const char* EpubWordBreak::GetPropertyName() const {
  return "-epub-word-break";
}

const AtomicString& EpubWordBreak::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-word-break"));
  return name;
}

const char* EpubWordBreak::GetJSPropertyName() const {
  return "epubWordBreak";
}

 // -epub-writing-mode



const char* EpubWritingMode::GetPropertyName() const {
  return "-epub-writing-mode";
}

const AtomicString& EpubWritingMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-epub-writing-mode"));
  return name;
}

const char* EpubWritingMode::GetJSPropertyName() const {
  return "epubWritingMode";
}

 // -webkit-align-content



const char* WebkitAlignContent::GetPropertyName() const {
  return "-webkit-align-content";
}

const AtomicString& WebkitAlignContent::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-align-content"));
  return name;
}

const char* WebkitAlignContent::GetJSPropertyName() const {
  return "webkitAlignContent";
}

 // -webkit-align-items



const char* WebkitAlignItems::GetPropertyName() const {
  return "-webkit-align-items";
}

const AtomicString& WebkitAlignItems::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-align-items"));
  return name;
}

const char* WebkitAlignItems::GetJSPropertyName() const {
  return "webkitAlignItems";
}

 // -webkit-align-self



const char* WebkitAlignSelf::GetPropertyName() const {
  return "-webkit-align-self";
}

const AtomicString& WebkitAlignSelf::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-align-self"));
  return name;
}

const char* WebkitAlignSelf::GetJSPropertyName() const {
  return "webkitAlignSelf";
}

 // -webkit-animation-delay



const char* WebkitAnimationDelay::GetPropertyName() const {
  return "-webkit-animation-delay";
}

const AtomicString& WebkitAnimationDelay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-delay"));
  return name;
}

const char* WebkitAnimationDelay::GetJSPropertyName() const {
  return "webkitAnimationDelay";
}

 // -webkit-animation-direction



const char* WebkitAnimationDirection::GetPropertyName() const {
  return "-webkit-animation-direction";
}

const AtomicString& WebkitAnimationDirection::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-direction"));
  return name;
}

const char* WebkitAnimationDirection::GetJSPropertyName() const {
  return "webkitAnimationDirection";
}

 // -webkit-animation-duration



const char* WebkitAnimationDuration::GetPropertyName() const {
  return "-webkit-animation-duration";
}

const AtomicString& WebkitAnimationDuration::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-duration"));
  return name;
}

const char* WebkitAnimationDuration::GetJSPropertyName() const {
  return "webkitAnimationDuration";
}

 // -webkit-animation-fill-mode



const char* WebkitAnimationFillMode::GetPropertyName() const {
  return "-webkit-animation-fill-mode";
}

const AtomicString& WebkitAnimationFillMode::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-fill-mode"));
  return name;
}

const char* WebkitAnimationFillMode::GetJSPropertyName() const {
  return "webkitAnimationFillMode";
}

 // -webkit-animation-iteration-count



const char* WebkitAnimationIterationCount::GetPropertyName() const {
  return "-webkit-animation-iteration-count";
}

const AtomicString& WebkitAnimationIterationCount::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-iteration-count"));
  return name;
}

const char* WebkitAnimationIterationCount::GetJSPropertyName() const {
  return "webkitAnimationIterationCount";
}

 // -webkit-animation-name



const char* WebkitAnimationName::GetPropertyName() const {
  return "-webkit-animation-name";
}

const AtomicString& WebkitAnimationName::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-name"));
  return name;
}

const char* WebkitAnimationName::GetJSPropertyName() const {
  return "webkitAnimationName";
}

 // -webkit-animation-play-state



const char* WebkitAnimationPlayState::GetPropertyName() const {
  return "-webkit-animation-play-state";
}

const AtomicString& WebkitAnimationPlayState::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-play-state"));
  return name;
}

const char* WebkitAnimationPlayState::GetJSPropertyName() const {
  return "webkitAnimationPlayState";
}

 // -webkit-animation-timing-function



const char* WebkitAnimationTimingFunction::GetPropertyName() const {
  return "-webkit-animation-timing-function";
}

const AtomicString& WebkitAnimationTimingFunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-animation-timing-function"));
  return name;
}

const char* WebkitAnimationTimingFunction::GetJSPropertyName() const {
  return "webkitAnimationTimingFunction";
}

 // -webkit-backface-visibility



const char* WebkitBackfaceVisibility::GetPropertyName() const {
  return "-webkit-backface-visibility";
}

const AtomicString& WebkitBackfaceVisibility::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-backface-visibility"));
  return name;
}

const char* WebkitBackfaceVisibility::GetJSPropertyName() const {
  return "webkitBackfaceVisibility";
}

 // -webkit-background-clip



const char* WebkitBackgroundClip::GetPropertyName() const {
  return "-webkit-background-clip";
}

const AtomicString& WebkitBackgroundClip::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-background-clip"));
  return name;
}

const char* WebkitBackgroundClip::GetJSPropertyName() const {
  return "webkitBackgroundClip";
}

 // -webkit-background-origin



const char* WebkitBackgroundOrigin::GetPropertyName() const {
  return "-webkit-background-origin";
}

const AtomicString& WebkitBackgroundOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-background-origin"));
  return name;
}

const char* WebkitBackgroundOrigin::GetJSPropertyName() const {
  return "webkitBackgroundOrigin";
}

 // -webkit-background-size



const char* WebkitBackgroundSize::GetPropertyName() const {
  return "-webkit-background-size";
}

const AtomicString& WebkitBackgroundSize::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-background-size"));
  return name;
}

const char* WebkitBackgroundSize::GetJSPropertyName() const {
  return "webkitBackgroundSize";
}

 // -webkit-border-bottom-left-radius



const char* WebkitBorderBottomLeftRadius::GetPropertyName() const {
  return "-webkit-border-bottom-left-radius";
}

const AtomicString& WebkitBorderBottomLeftRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-bottom-left-radius"));
  return name;
}

const char* WebkitBorderBottomLeftRadius::GetJSPropertyName() const {
  return "webkitBorderBottomLeftRadius";
}

 // -webkit-border-bottom-right-radius



const char* WebkitBorderBottomRightRadius::GetPropertyName() const {
  return "-webkit-border-bottom-right-radius";
}

const AtomicString& WebkitBorderBottomRightRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-bottom-right-radius"));
  return name;
}

const char* WebkitBorderBottomRightRadius::GetJSPropertyName() const {
  return "webkitBorderBottomRightRadius";
}

 // -webkit-border-top-left-radius



const char* WebkitBorderTopLeftRadius::GetPropertyName() const {
  return "-webkit-border-top-left-radius";
}

const AtomicString& WebkitBorderTopLeftRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-top-left-radius"));
  return name;
}

const char* WebkitBorderTopLeftRadius::GetJSPropertyName() const {
  return "webkitBorderTopLeftRadius";
}

 // -webkit-border-top-right-radius



const char* WebkitBorderTopRightRadius::GetPropertyName() const {
  return "-webkit-border-top-right-radius";
}

const AtomicString& WebkitBorderTopRightRadius::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-border-top-right-radius"));
  return name;
}

const char* WebkitBorderTopRightRadius::GetJSPropertyName() const {
  return "webkitBorderTopRightRadius";
}

 // -webkit-box-shadow



const char* WebkitBoxShadow::GetPropertyName() const {
  return "-webkit-box-shadow";
}

const AtomicString& WebkitBoxShadow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-shadow"));
  return name;
}

const char* WebkitBoxShadow::GetJSPropertyName() const {
  return "webkitBoxShadow";
}

 // -webkit-box-sizing



const char* WebkitBoxSizing::GetPropertyName() const {
  return "-webkit-box-sizing";
}

const AtomicString& WebkitBoxSizing::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-box-sizing"));
  return name;
}

const char* WebkitBoxSizing::GetJSPropertyName() const {
  return "webkitBoxSizing";
}

 // -webkit-clip-path



const char* WebkitClipPath::GetPropertyName() const {
  return "-webkit-clip-path";
}

const AtomicString& WebkitClipPath::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-clip-path"));
  return name;
}

const char* WebkitClipPath::GetJSPropertyName() const {
  return "webkitClipPath";
}

 // -webkit-column-count



const char* WebkitColumnCount::GetPropertyName() const {
  return "-webkit-column-count";
}

const AtomicString& WebkitColumnCount::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-count"));
  return name;
}

const char* WebkitColumnCount::GetJSPropertyName() const {
  return "webkitColumnCount";
}

 // -webkit-column-gap



const char* WebkitColumnGap::GetPropertyName() const {
  return "-webkit-column-gap";
}

const AtomicString& WebkitColumnGap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-gap"));
  return name;
}

const char* WebkitColumnGap::GetJSPropertyName() const {
  return "webkitColumnGap";
}

 // -webkit-column-rule-color



const char* WebkitColumnRuleColor::GetPropertyName() const {
  return "-webkit-column-rule-color";
}

const AtomicString& WebkitColumnRuleColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-rule-color"));
  return name;
}

const char* WebkitColumnRuleColor::GetJSPropertyName() const {
  return "webkitColumnRuleColor";
}

 // -webkit-column-rule-style



const char* WebkitColumnRuleStyle::GetPropertyName() const {
  return "-webkit-column-rule-style";
}

const AtomicString& WebkitColumnRuleStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-rule-style"));
  return name;
}

const char* WebkitColumnRuleStyle::GetJSPropertyName() const {
  return "webkitColumnRuleStyle";
}

 // -webkit-column-rule-width



const char* WebkitColumnRuleWidth::GetPropertyName() const {
  return "-webkit-column-rule-width";
}

const AtomicString& WebkitColumnRuleWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-rule-width"));
  return name;
}

const char* WebkitColumnRuleWidth::GetJSPropertyName() const {
  return "webkitColumnRuleWidth";
}

 // -webkit-column-span



const char* WebkitColumnSpan::GetPropertyName() const {
  return "-webkit-column-span";
}

const AtomicString& WebkitColumnSpan::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-span"));
  return name;
}

const char* WebkitColumnSpan::GetJSPropertyName() const {
  return "webkitColumnSpan";
}

 // -webkit-column-width



const char* WebkitColumnWidth::GetPropertyName() const {
  return "-webkit-column-width";
}

const AtomicString& WebkitColumnWidth::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-column-width"));
  return name;
}

const char* WebkitColumnWidth::GetJSPropertyName() const {
  return "webkitColumnWidth";
}

 // -webkit-filter



const char* WebkitFilter::GetPropertyName() const {
  return "-webkit-filter";
}

const AtomicString& WebkitFilter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-filter"));
  return name;
}

const char* WebkitFilter::GetJSPropertyName() const {
  return "webkitFilter";
}

 // -webkit-flex-basis



const char* WebkitFlexBasis::GetPropertyName() const {
  return "-webkit-flex-basis";
}

const AtomicString& WebkitFlexBasis::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex-basis"));
  return name;
}

const char* WebkitFlexBasis::GetJSPropertyName() const {
  return "webkitFlexBasis";
}

 // -webkit-flex-direction



const char* WebkitFlexDirection::GetPropertyName() const {
  return "-webkit-flex-direction";
}

const AtomicString& WebkitFlexDirection::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex-direction"));
  return name;
}

const char* WebkitFlexDirection::GetJSPropertyName() const {
  return "webkitFlexDirection";
}

 // -webkit-flex-grow



const char* WebkitFlexGrow::GetPropertyName() const {
  return "-webkit-flex-grow";
}

const AtomicString& WebkitFlexGrow::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex-grow"));
  return name;
}

const char* WebkitFlexGrow::GetJSPropertyName() const {
  return "webkitFlexGrow";
}

 // -webkit-flex-shrink



const char* WebkitFlexShrink::GetPropertyName() const {
  return "-webkit-flex-shrink";
}

const AtomicString& WebkitFlexShrink::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex-shrink"));
  return name;
}

const char* WebkitFlexShrink::GetJSPropertyName() const {
  return "webkitFlexShrink";
}

 // -webkit-flex-wrap



const char* WebkitFlexWrap::GetPropertyName() const {
  return "-webkit-flex-wrap";
}

const AtomicString& WebkitFlexWrap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-flex-wrap"));
  return name;
}

const char* WebkitFlexWrap::GetJSPropertyName() const {
  return "webkitFlexWrap";
}

 // -webkit-font-feature-settings



const char* WebkitFontFeatureSettings::GetPropertyName() const {
  return "-webkit-font-feature-settings";
}

const AtomicString& WebkitFontFeatureSettings::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-font-feature-settings"));
  return name;
}

const char* WebkitFontFeatureSettings::GetJSPropertyName() const {
  return "webkitFontFeatureSettings";
}

 // -webkit-hyphenate-character



const char* WebkitHyphenateCharacter::GetPropertyName() const {
  return "-webkit-hyphenate-character";
}

const AtomicString& WebkitHyphenateCharacter::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-hyphenate-character"));
  return name;
}

const char* WebkitHyphenateCharacter::GetJSPropertyName() const {
  return "webkitHyphenateCharacter";
}

 // -webkit-justify-content



const char* WebkitJustifyContent::GetPropertyName() const {
  return "-webkit-justify-content";
}

const AtomicString& WebkitJustifyContent::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-justify-content"));
  return name;
}

const char* WebkitJustifyContent::GetJSPropertyName() const {
  return "webkitJustifyContent";
}

 // -webkit-opacity



const char* WebkitOpacity::GetPropertyName() const {
  return "-webkit-opacity";
}

const AtomicString& WebkitOpacity::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-opacity"));
  return name;
}

const char* WebkitOpacity::GetJSPropertyName() const {
  return "webkitOpacity";
}

 // -webkit-order



const char* WebkitOrder::GetPropertyName() const {
  return "-webkit-order";
}

const AtomicString& WebkitOrder::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-order"));
  return name;
}

const char* WebkitOrder::GetJSPropertyName() const {
  return "webkitOrder";
}

 // -webkit-perspective



const char* WebkitPerspective::GetPropertyName() const {
  return "-webkit-perspective";
}

const AtomicString& WebkitPerspective::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-perspective"));
  return name;
}

const char* WebkitPerspective::GetJSPropertyName() const {
  return "webkitPerspective";
}

 // -webkit-perspective-origin



const char* WebkitPerspectiveOrigin::GetPropertyName() const {
  return "-webkit-perspective-origin";
}

const AtomicString& WebkitPerspectiveOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-perspective-origin"));
  return name;
}

const char* WebkitPerspectiveOrigin::GetJSPropertyName() const {
  return "webkitPerspectiveOrigin";
}

 // -webkit-shape-image-threshold



const char* WebkitShapeImageThreshold::GetPropertyName() const {
  return "-webkit-shape-image-threshold";
}

const AtomicString& WebkitShapeImageThreshold::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-shape-image-threshold"));
  return name;
}

const char* WebkitShapeImageThreshold::GetJSPropertyName() const {
  return "webkitShapeImageThreshold";
}

 // -webkit-shape-margin



const char* WebkitShapeMargin::GetPropertyName() const {
  return "-webkit-shape-margin";
}

const AtomicString& WebkitShapeMargin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-shape-margin"));
  return name;
}

const char* WebkitShapeMargin::GetJSPropertyName() const {
  return "webkitShapeMargin";
}

 // -webkit-shape-outside



const char* WebkitShapeOutside::GetPropertyName() const {
  return "-webkit-shape-outside";
}

const AtomicString& WebkitShapeOutside::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-shape-outside"));
  return name;
}

const char* WebkitShapeOutside::GetJSPropertyName() const {
  return "webkitShapeOutside";
}

 // -webkit-text-emphasis-color



const char* WebkitTextEmphasisColor::GetPropertyName() const {
  return "-webkit-text-emphasis-color";
}

const AtomicString& WebkitTextEmphasisColor::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-emphasis-color"));
  return name;
}

const char* WebkitTextEmphasisColor::GetJSPropertyName() const {
  return "webkitTextEmphasisColor";
}

 // -webkit-text-emphasis-position



const char* WebkitTextEmphasisPosition::GetPropertyName() const {
  return "-webkit-text-emphasis-position";
}

const AtomicString& WebkitTextEmphasisPosition::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-emphasis-position"));
  return name;
}

const char* WebkitTextEmphasisPosition::GetJSPropertyName() const {
  return "webkitTextEmphasisPosition";
}

 // -webkit-text-emphasis-style



const char* WebkitTextEmphasisStyle::GetPropertyName() const {
  return "-webkit-text-emphasis-style";
}

const AtomicString& WebkitTextEmphasisStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-emphasis-style"));
  return name;
}

const char* WebkitTextEmphasisStyle::GetJSPropertyName() const {
  return "webkitTextEmphasisStyle";
}

 // -webkit-text-size-adjust



const char* WebkitTextSizeAdjust::GetPropertyName() const {
  return "-webkit-text-size-adjust";
}

const AtomicString& WebkitTextSizeAdjust::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-text-size-adjust"));
  return name;
}

const char* WebkitTextSizeAdjust::GetJSPropertyName() const {
  return "webkitTextSizeAdjust";
}

 // -webkit-transform



const char* WebkitTransform::GetPropertyName() const {
  return "-webkit-transform";
}

const AtomicString& WebkitTransform::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transform"));
  return name;
}

const char* WebkitTransform::GetJSPropertyName() const {
  return "webkitTransform";
}

 // -webkit-transform-origin



const char* WebkitTransformOrigin::GetPropertyName() const {
  return "-webkit-transform-origin";
}

const AtomicString& WebkitTransformOrigin::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transform-origin"));
  return name;
}

const char* WebkitTransformOrigin::GetJSPropertyName() const {
  return "webkitTransformOrigin";
}

 // -webkit-transform-style



const char* WebkitTransformStyle::GetPropertyName() const {
  return "-webkit-transform-style";
}

const AtomicString& WebkitTransformStyle::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transform-style"));
  return name;
}

const char* WebkitTransformStyle::GetJSPropertyName() const {
  return "webkitTransformStyle";
}

 // -webkit-transition-delay



const char* WebkitTransitionDelay::GetPropertyName() const {
  return "-webkit-transition-delay";
}

const AtomicString& WebkitTransitionDelay::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transition-delay"));
  return name;
}

const char* WebkitTransitionDelay::GetJSPropertyName() const {
  return "webkitTransitionDelay";
}

 // -webkit-transition-duration



const char* WebkitTransitionDuration::GetPropertyName() const {
  return "-webkit-transition-duration";
}

const AtomicString& WebkitTransitionDuration::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transition-duration"));
  return name;
}

const char* WebkitTransitionDuration::GetJSPropertyName() const {
  return "webkitTransitionDuration";
}

 // -webkit-transition-property



const char* WebkitTransitionProperty::GetPropertyName() const {
  return "-webkit-transition-property";
}

const AtomicString& WebkitTransitionProperty::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transition-property"));
  return name;
}

const char* WebkitTransitionProperty::GetJSPropertyName() const {
  return "webkitTransitionProperty";
}

 // -webkit-transition-timing-function



const char* WebkitTransitionTimingFunction::GetPropertyName() const {
  return "-webkit-transition-timing-function";
}

const AtomicString& WebkitTransitionTimingFunction::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-transition-timing-function"));
  return name;
}

const char* WebkitTransitionTimingFunction::GetJSPropertyName() const {
  return "webkitTransitionTimingFunction";
}

 // -webkit-user-select



const char* WebkitUserSelect::GetPropertyName() const {
  return "-webkit-user-select";
}

const AtomicString& WebkitUserSelect::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("-webkit-user-select"));
  return name;
}

const char* WebkitUserSelect::GetJSPropertyName() const {
  return "webkitUserSelect";
}

 // word-wrap



const char* WordWrap::GetPropertyName() const {
  return "word-wrap";
}

const AtomicString& WordWrap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("word-wrap"));
  return name;
}

const char* WordWrap::GetJSPropertyName() const {
  return "wordWrap";
}

 // grid-column-gap



const char* GridColumnGap::GetPropertyName() const {
  return "grid-column-gap";
}

const AtomicString& GridColumnGap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-column-gap"));
  return name;
}

const char* GridColumnGap::GetJSPropertyName() const {
  return "gridColumnGap";
}

 // grid-row-gap



const char* GridRowGap::GetPropertyName() const {
  return "grid-row-gap";
}

const AtomicString& GridRowGap::GetPropertyNameAtomicString() const {
  DEFINE_STATIC_LOCAL(const AtomicString, name, ("grid-row-gap"));
  return name;
}

const char* GridRowGap::GetJSPropertyName() const {
  return "gridRowGap";
}

  
}  // namespace css_longhand
}  // namespace blink
