// Copyright 2016 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from third_party/blink/renderer/core/css/css_primitive_value_units.json5.

#include "third_party/blink/renderer/core/css/css_primitive_value.h"

namespace blink {
namespace {

template <typename CharacterType>
bool UnitStringEquals(base::span<const CharacterType> chars, const char* literal) {
  for (wtf_size_t i = 0; i < chars.size(); ++i) {
    if (chars[i] != static_cast<CharacterType>(literal[i]))
      return false;
  }
  return true;
}

template <typename CharacterType>
CSSPrimitiveValue::UnitType CssPrimitiveValueUnitFromTrie(
    base::span<const CharacterType> chars) {
  switch (chars.size()) {
    case 1:
      if (UnitStringEquals(chars, "q"))
        return CSSPrimitiveValue::UnitType::kQuarterMillimeters;
      if (UnitStringEquals(chars, "s"))
        return CSSPrimitiveValue::UnitType::kSeconds;
      if (UnitStringEquals(chars, "x"))
        return CSSPrimitiveValue::UnitType::kX;
      break;
    case 2:
      if (UnitStringEquals(chars, "ch"))
        return CSSPrimitiveValue::UnitType::kChs;
      if (UnitStringEquals(chars, "cm"))
        return CSSPrimitiveValue::UnitType::kCentimeters;
      if (UnitStringEquals(chars, "em"))
        return CSSPrimitiveValue::UnitType::kEms;
      if (UnitStringEquals(chars, "ex"))
        return CSSPrimitiveValue::UnitType::kExs;
      if (UnitStringEquals(chars, "fr"))
        return CSSPrimitiveValue::UnitType::kFlex;
      if (UnitStringEquals(chars, "hz"))
        return CSSPrimitiveValue::UnitType::kHertz;
      if (UnitStringEquals(chars, "ic"))
        return CSSPrimitiveValue::UnitType::kIcs;
      if (UnitStringEquals(chars, "in"))
        return CSSPrimitiveValue::UnitType::kInches;
      if (UnitStringEquals(chars, "lh"))
        return CSSPrimitiveValue::UnitType::kLhs;
      if (UnitStringEquals(chars, "mm"))
        return CSSPrimitiveValue::UnitType::kMillimeters;
      if (UnitStringEquals(chars, "ms"))
        return CSSPrimitiveValue::UnitType::kMilliseconds;
      if (UnitStringEquals(chars, "pc"))
        return CSSPrimitiveValue::UnitType::kPicas;
      if (UnitStringEquals(chars, "pt"))
        return CSSPrimitiveValue::UnitType::kPoints;
      if (UnitStringEquals(chars, "px"))
        return CSSPrimitiveValue::UnitType::kPixels;
      if (UnitStringEquals(chars, "vb"))
        return CSSPrimitiveValue::UnitType::kViewportBlockSize;
      if (UnitStringEquals(chars, "vh"))
        return CSSPrimitiveValue::UnitType::kViewportHeight;
      if (UnitStringEquals(chars, "vi"))
        return CSSPrimitiveValue::UnitType::kViewportInlineSize;
      if (UnitStringEquals(chars, "vw"))
        return CSSPrimitiveValue::UnitType::kViewportWidth;
      break;
    case 3:
      if (UnitStringEquals(chars, "cap"))
        return CSSPrimitiveValue::UnitType::kCaps;
      if (UnitStringEquals(chars, "cqb"))
        return CSSPrimitiveValue::UnitType::kContainerBlockSize;
      if (UnitStringEquals(chars, "cqh"))
        return CSSPrimitiveValue::UnitType::kContainerHeight;
      if (UnitStringEquals(chars, "cqi"))
        return CSSPrimitiveValue::UnitType::kContainerInlineSize;
      if (UnitStringEquals(chars, "cqw"))
        return CSSPrimitiveValue::UnitType::kContainerWidth;
      if (UnitStringEquals(chars, "deg"))
        return CSSPrimitiveValue::UnitType::kDegrees;
      if (UnitStringEquals(chars, "dpi"))
        return CSSPrimitiveValue::UnitType::kDotsPerInch;
      if (UnitStringEquals(chars, "dvb"))
        return CSSPrimitiveValue::UnitType::kDynamicViewportBlockSize;
      if (UnitStringEquals(chars, "dvh"))
        return CSSPrimitiveValue::UnitType::kDynamicViewportHeight;
      if (UnitStringEquals(chars, "dvi"))
        return CSSPrimitiveValue::UnitType::kDynamicViewportInlineSize;
      if (UnitStringEquals(chars, "dvw"))
        return CSSPrimitiveValue::UnitType::kDynamicViewportWidth;
      if (UnitStringEquals(chars, "khz"))
        return CSSPrimitiveValue::UnitType::kKilohertz;
      if (UnitStringEquals(chars, "lvb"))
        return CSSPrimitiveValue::UnitType::kLargeViewportBlockSize;
      if (UnitStringEquals(chars, "lvh"))
        return CSSPrimitiveValue::UnitType::kLargeViewportHeight;
      if (UnitStringEquals(chars, "lvi"))
        return CSSPrimitiveValue::UnitType::kLargeViewportInlineSize;
      if (UnitStringEquals(chars, "lvw"))
        return CSSPrimitiveValue::UnitType::kLargeViewportWidth;
      if (UnitStringEquals(chars, "rad"))
        return CSSPrimitiveValue::UnitType::kRadians;
      if (UnitStringEquals(chars, "rch"))
        return CSSPrimitiveValue::UnitType::kRchs;
      if (UnitStringEquals(chars, "rem"))
        return CSSPrimitiveValue::UnitType::kRems;
      if (UnitStringEquals(chars, "rex"))
        return CSSPrimitiveValue::UnitType::kRexs;
      if (UnitStringEquals(chars, "ric"))
        return CSSPrimitiveValue::UnitType::kRics;
      if (UnitStringEquals(chars, "rlh"))
        return CSSPrimitiveValue::UnitType::kRlhs;
      if (UnitStringEquals(chars, "svb"))
        return CSSPrimitiveValue::UnitType::kSmallViewportBlockSize;
      if (UnitStringEquals(chars, "svh"))
        return CSSPrimitiveValue::UnitType::kSmallViewportHeight;
      if (UnitStringEquals(chars, "svi"))
        return CSSPrimitiveValue::UnitType::kSmallViewportInlineSize;
      if (UnitStringEquals(chars, "svw"))
        return CSSPrimitiveValue::UnitType::kSmallViewportWidth;
      break;
    case 4:
      if (UnitStringEquals(chars, "dpcm"))
        return CSSPrimitiveValue::UnitType::kDotsPerCentimeter;
      if (UnitStringEquals(chars, "dppx"))
        return CSSPrimitiveValue::UnitType::kDotsPerPixel;
      if (UnitStringEquals(chars, "grad"))
        return CSSPrimitiveValue::UnitType::kGradians;
      if (UnitStringEquals(chars, "rcap"))
        return CSSPrimitiveValue::UnitType::kRcaps;
      if (UnitStringEquals(chars, "turn"))
        return CSSPrimitiveValue::UnitType::kTurns;
      if (UnitStringEquals(chars, "vmax"))
        return CSSPrimitiveValue::UnitType::kViewportMax;
      if (UnitStringEquals(chars, "vmin"))
        return CSSPrimitiveValue::UnitType::kViewportMin;
      break;
    case 5:
      if (UnitStringEquals(chars, "__qem"))
        return CSSPrimitiveValue::UnitType::kQuirkyEms;
      if (UnitStringEquals(chars, "cqmax"))
        return CSSPrimitiveValue::UnitType::kContainerMax;
      if (UnitStringEquals(chars, "cqmin"))
        return CSSPrimitiveValue::UnitType::kContainerMin;
      if (UnitStringEquals(chars, "dvmax"))
        return CSSPrimitiveValue::UnitType::kDynamicViewportMax;
      if (UnitStringEquals(chars, "dvmin"))
        return CSSPrimitiveValue::UnitType::kDynamicViewportMin;
      if (UnitStringEquals(chars, "lvmax"))
        return CSSPrimitiveValue::UnitType::kLargeViewportMax;
      if (UnitStringEquals(chars, "lvmin"))
        return CSSPrimitiveValue::UnitType::kLargeViewportMin;
      if (UnitStringEquals(chars, "svmax"))
        return CSSPrimitiveValue::UnitType::kSmallViewportMax;
      if (UnitStringEquals(chars, "svmin"))
        return CSSPrimitiveValue::UnitType::kSmallViewportMin;
      break;
  }
  return CSSPrimitiveValue::UnitType::kUnknown;
}

}  // namespace

CSSPrimitiveValue::UnitType CSSPrimitiveValue::StringToUnitType(
    base::span<const LChar> chars) {
  return CssPrimitiveValueUnitFromTrie(chars);
}

CSSPrimitiveValue::UnitType CSSPrimitiveValue::StringToUnitType(
    base::span<const UChar> chars) {
  return CssPrimitiveValueUnitFromTrie(chars);
}

}  // namespace blink
