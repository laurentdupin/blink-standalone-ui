// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Standalone generated-name owners for small Blink name tables that are
// not generated in this CMake build. Keep these inert until Init() so they
// do not pre-populate the AtomicString table before WTF/core initialization.

#include "third_party/blink/renderer/core/css/media_feature_names.h"
#include "third_party/blink/renderer/core/html/shadow/shadow_element_names.h"
#include "third_party/blink/renderer/core/input_type_names.h"
#include "third_party/blink/renderer/core/media_type_names.h"
#include "third_party/blink/renderer/core/script_type_names.h"

#include <iterator>

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/text/string_impl.h"

namespace blink::media_feature_names {

namespace {

void* names_storage[kNamesCount *
                    ((sizeof(AtomicString) + sizeof(void*) - 1) /
                     sizeof(void*))];

AtomicString& NameAt(size_t index) {
  return reinterpret_cast<AtomicString*>(&names_storage)[index];
}

}  // namespace

const AtomicString& kAnyHoverMediaFeature = NameAt(0);
const AtomicString& kAnyPointerMediaFeature = NameAt(1);
const AtomicString& kAspectRatioMediaFeature = NameAt(2);
const AtomicString& kBlockSizeMediaFeature = NameAt(3);
const AtomicString& kColorGamutMediaFeature = NameAt(4);
const AtomicString& kColorIndexMediaFeature = NameAt(5);
const AtomicString& kColorMediaFeature = NameAt(6);
const AtomicString& kDeviceAspectRatioMediaFeature = NameAt(7);
const AtomicString& kDeviceHeightMediaFeature = NameAt(8);
const AtomicString& kDevicePixelRatioMediaFeature = NameAt(9);
const AtomicString& kDevicePostureMediaFeature = NameAt(10);
const AtomicString& kDeviceWidthMediaFeature = NameAt(11);
const AtomicString& kDisplayModeMediaFeature = NameAt(12);
const AtomicString& kDisplayStateMediaFeature = NameAt(13);
const AtomicString& kDynamicRangeMediaFeature = NameAt(14);
const AtomicString& kFallbackMediaFeature = NameAt(15);
const AtomicString& kForcedColorsMediaFeature = NameAt(16);
const AtomicString& kGridMediaFeature = NameAt(17);
const AtomicString& kHeightMediaFeature = NameAt(18);
const AtomicString& kHorizontalViewportSegmentsMediaFeature = NameAt(19);
const AtomicString& kHoverMediaFeature = NameAt(20);
const AtomicString& kInlineSizeMediaFeature = NameAt(21);
const AtomicString& kInvertedColorsMediaFeature = NameAt(22);
const AtomicString& kMaxAspectRatioMediaFeature = NameAt(23);
const AtomicString& kMaxBlockSizeMediaFeature = NameAt(24);
const AtomicString& kMaxColorIndexMediaFeature = NameAt(25);
const AtomicString& kMaxColorMediaFeature = NameAt(26);
const AtomicString& kMaxDeviceAspectRatioMediaFeature = NameAt(27);
const AtomicString& kMaxDeviceHeightMediaFeature = NameAt(28);
const AtomicString& kMaxDevicePixelRatioMediaFeature = NameAt(29);
const AtomicString& kMaxDeviceWidthMediaFeature = NameAt(30);
const AtomicString& kMaxHeightMediaFeature = NameAt(31);
const AtomicString& kMaxInlineSizeMediaFeature = NameAt(32);
const AtomicString& kMaxMonochromeMediaFeature = NameAt(33);
const AtomicString& kMaxResolutionMediaFeature = NameAt(34);
const AtomicString& kMaxWidthMediaFeature = NameAt(35);
const AtomicString& kMinAspectRatioMediaFeature = NameAt(36);
const AtomicString& kMinBlockSizeMediaFeature = NameAt(37);
const AtomicString& kMinColorIndexMediaFeature = NameAt(38);
const AtomicString& kMinColorMediaFeature = NameAt(39);
const AtomicString& kMinDeviceAspectRatioMediaFeature = NameAt(40);
const AtomicString& kMinDeviceHeightMediaFeature = NameAt(41);
const AtomicString& kMinDevicePixelRatioMediaFeature = NameAt(42);
const AtomicString& kMinDeviceWidthMediaFeature = NameAt(43);
const AtomicString& kMinHeightMediaFeature = NameAt(44);
const AtomicString& kMinInlineSizeMediaFeature = NameAt(45);
const AtomicString& kMinMonochromeMediaFeature = NameAt(46);
const AtomicString& kMinResolutionMediaFeature = NameAt(47);
const AtomicString& kMinWidthMediaFeature = NameAt(48);
const AtomicString& kMonochromeMediaFeature = NameAt(49);
const AtomicString& kNavigationControlsMediaFeature = NameAt(50);
const AtomicString& kOrientationMediaFeature = NameAt(51);
const AtomicString& kOriginTrialTestMediaFeature = NameAt(52);
const AtomicString& kOverflowBlockMediaFeature = NameAt(53);
const AtomicString& kOverflowInlineMediaFeature = NameAt(54);
const AtomicString& kPointerMediaFeature = NameAt(55);
const AtomicString& kPrefersColorSchemeMediaFeature = NameAt(56);
const AtomicString& kPrefersContrastMediaFeature = NameAt(57);
const AtomicString& kPrefersReducedDataMediaFeature = NameAt(58);
const AtomicString& kPrefersReducedMotionMediaFeature = NameAt(59);
const AtomicString& kPrefersReducedTransparencyMediaFeature = NameAt(60);
const AtomicString& kResizableMediaFeature = NameAt(61);
const AtomicString& kResolutionMediaFeature = NameAt(62);
const AtomicString& kScanMediaFeature = NameAt(63);
const AtomicString& kScriptingMediaFeature = NameAt(64);
const AtomicString& kScrollableMediaFeature = NameAt(65);
const AtomicString& kScrolledMediaFeature = NameAt(66);
const AtomicString& kSnappedMediaFeature = NameAt(67);
const AtomicString& kStuckMediaFeature = NameAt(68);
const AtomicString& kTransform3dMediaFeature = NameAt(69);
const AtomicString& kUpdateMediaFeature = NameAt(70);
const AtomicString& kVerticalViewportSegmentsMediaFeature = NameAt(71);
const AtomicString& kVideoDynamicRangeMediaFeature = NameAt(72);
const AtomicString& kWidthMediaFeature = NameAt(73);

void Init() {
  static bool is_loaded = false;
  if (is_loaded) {
    return;
  }
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
      {"any-hover", 9},
      {"any-pointer", 11},
      {"aspect-ratio", 12},
      {"block-size", 10},
      {"color-gamut", 11},
      {"color-index", 11},
      {"color", 5},
      {"device-aspect-ratio", 19},
      {"device-height", 13},
      {"device-pixel-ratio", 18},
      {"device-posture", 14},
      {"device-width", 12},
      {"display-mode", 12},
      {"display-state", 13},
      {"dynamic-range", 13},
      {"fallback", 8},
      {"forced-colors", 13},
      {"grid", 4},
      {"height", 6},
      {"horizontal-viewport-segments", 28},
      {"hover", 5},
      {"inline-size", 11},
      {"inverted-colors", 15},
      {"max-aspect-ratio", 16},
      {"max-block-size", 14},
      {"max-color-index", 15},
      {"max-color", 9},
      {"max-device-aspect-ratio", 23},
      {"max-device-height", 17},
      {"max-device-pixel-ratio", 22},
      {"max-device-width", 16},
      {"max-height", 10},
      {"max-inline-size", 15},
      {"max-monochrome", 14},
      {"max-resolution", 14},
      {"max-width", 9},
      {"min-aspect-ratio", 16},
      {"min-block-size", 14},
      {"min-color-index", 15},
      {"min-color", 9},
      {"min-device-aspect-ratio", 23},
      {"min-device-height", 17},
      {"min-device-pixel-ratio", 22},
      {"min-device-width", 16},
      {"min-height", 10},
      {"min-inline-size", 15},
      {"min-monochrome", 14},
      {"min-resolution", 14},
      {"min-width", 9},
      {"monochrome", 10},
      {"navigation-controls", 19},
      {"orientation", 11},
      {"origin-trial-test", 17},
      {"overflow-block", 14},
      {"overflow-inline", 15},
      {"pointer", 7},
      {"prefers-color-scheme", 20},
      {"prefers-contrast", 16},
      {"prefers-reduced-data", 20},
      {"prefers-reduced-motion", 22},
      {"prefers-reduced-transparency", 28},
      {"resizable", 9},
      {"resolution", 10},
      {"scan", 4},
      {"scripting", 9},
      {"scrollable", 10},
      {"scrolled", 8},
      {"snapped", 7},
      {"stuck", 5},
      {"transform-3d", 12},
      {"update", 6},
      {"vertical-viewport-segments", 26},
      {"video-dynamic-range", 19},
      {"width", 5},
  };

  static_assert(std::size(kNames) == kNamesCount,
                "Generated-name storage must match kNamesCount.");

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl =
        StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    new (&NameAt(i)) AtomicString(impl);
  }
}

}  // namespace blink::media_feature_names

namespace blink::shadow_element_names {

namespace {

void* names_storage[kNamesCount *
                    ((sizeof(AtomicString) + sizeof(void*) - 1) /
                     sizeof(void*))];

AtomicString& NameAt(size_t index) {
  return reinterpret_cast<AtomicString*>(&names_storage)[index];
}

}  // namespace

const AtomicString& kIdClearButton = NameAt(0);
const AtomicString& kIdDateTimeEdit = NameAt(1);
const AtomicString& kIdDetailsContent = NameAt(2);
const AtomicString& kIdDetailsSummary = NameAt(3);
const AtomicString& kIdEditingViewPort = NameAt(4);
const AtomicString& kIdFileUploadButton = NameAt(5);
const AtomicString& kIdOptGroupLabel = NameAt(6);
const AtomicString& kIdPasswordRevealButton = NameAt(7);
const AtomicString& kIdPermissionIcon = NameAt(8);
const AtomicString& kIdPickerIndicator = NameAt(9);
const AtomicString& kIdPlaceholder = NameAt(10);
const AtomicString& kIdPlaceholderBreak = NameAt(11);
const AtomicString& kIdSearchClearButton = NameAt(12);
const AtomicString& kIdSliderThumb = NameAt(13);
const AtomicString& kIdSliderTrack = NameAt(14);
const AtomicString& kIdSpinButton = NameAt(15);
const AtomicString& kIdTextFieldContainer = NameAt(16);
const AtomicString& kOptionLabelContainer = NameAt(17);
const AtomicString& kOptionSlot = NameAt(18);
const AtomicString& kPickerSelect = NameAt(19);
const AtomicString& kPseudoCalendarPickerIndicator = NameAt(20);
const AtomicString& kPseudoFileUploadButton = NameAt(21);
const AtomicString& kPseudoInputPlaceholder = NameAt(22);
const AtomicString& kPseudoInternalDatetimeContainer = NameAt(23);
const AtomicString& kPseudoInternalInputSuggested = NameAt(24);
const AtomicString& kPseudoInternalPermissionContainer = NameAt(25);
const AtomicString& kPseudoInternalPermissionTextSpan = NameAt(26);
const AtomicString& kPseudoMediaSliderContainer = NameAt(27);
const AtomicString& kPseudoMediaSliderThumb = NameAt(28);
const AtomicString& kPseudoMeterInnerElement = NameAt(29);
const AtomicString& kPseudoSliderContainer = NameAt(30);
const AtomicString& kPseudoSliderThumb = NameAt(31);
const AtomicString& kPseudoSliderTrack = NameAt(32);
const AtomicString& kPseudoTextFieldDecorationContainer = NameAt(33);
const AtomicString& kSelectAutofillPreview = NameAt(34);
const AtomicString& kSelectAutofillPreviewText = NameAt(35);
const AtomicString& kSelectButtonSlot = NameAt(36);
const AtomicString& kSelectInnerElement = NameAt(37);
const AtomicString& kSelectOptions = NameAt(38);
const AtomicString& kSelectPopoverOptions = NameAt(39);

void Init() {
  static bool is_loaded = false;
  if (is_loaded) {
    return;
  }
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
      {"kIdClearButton", 14},
      {"kIdDateTimeEdit", 15},
      {"kIdDetailsContent", 17},
      {"kIdDetailsSummary", 17},
      {"kIdEditingViewPort", 18},
      {"kIdFileUploadButton", 19},
      {"kIdOptGroupLabel", 16},
      {"kIdPasswordRevealButton", 23},
      {"kIdPermissionIcon", 17},
      {"kIdPickerIndicator", 18},
      {"kIdPlaceholder", 14},
      {"kIdPlaceholderBreak", 19},
      {"kIdSearchClearButton", 20},
      {"kIdSliderThumb", 14},
      {"kIdSliderTrack", 14},
      {"kIdSpinButton", 13},
      {"kIdTextFieldContainer", 21},
      {"kOptionLabelContainer", 21},
      {"kOptionSlot", 11},
      {"kPickerSelect", 13},
      {"kPseudoCalendarPickerIndicator", 30},
      {"kPseudoFileUploadButton", 23},
      {"kPseudoInputPlaceholder", 23},
      {"kPseudoInternalDatetimeContainer", 32},
      {"kPseudoInternalInputSuggested", 29},
      {"kPseudoInternalPermissionContainer", 34},
      {"kPseudoInternalPermissionTextSpan", 33},
      {"kPseudoMediaSliderContainer", 27},
      {"kPseudoMediaSliderThumb", 23},
      {"kPseudoMeterInnerElement", 24},
      {"kPseudoSliderContainer", 22},
      {"kPseudoSliderThumb", 18},
      {"kPseudoSliderTrack", 18},
      {"kPseudoTextFieldDecorationContainer", 35},
      {"kSelectAutofillPreview", 22},
      {"kSelectAutofillPreviewText", 26},
      {"kSelectButtonSlot", 17},
      {"kSelectInnerElement", 19},
      {"kSelectOptions", 14},
      {"kSelectPopoverOptions", 21},
  };

  static_assert(std::size(kNames) == kNamesCount,
                "Generated-name storage must match kNamesCount.");

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl =
        StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    new (&NameAt(i)) AtomicString(impl);
  }
}

}  // namespace blink::shadow_element_names

namespace blink::input_type_names {

namespace {

void* names_storage[kNamesCount *
                    ((sizeof(AtomicString) + sizeof(void*) - 1) /
                     sizeof(void*))];

AtomicString& NameAt(size_t index) {
  return reinterpret_cast<AtomicString*>(&names_storage)[index];
}

}  // namespace

const AtomicString& kButton = NameAt(0);
const AtomicString& kCheckbox = NameAt(1);
const AtomicString& kColor = NameAt(2);
const AtomicString& kDate = NameAt(3);
const AtomicString& kDatetime = NameAt(4);
const AtomicString& kDatetimeLocal = NameAt(5);
const AtomicString& kEmail = NameAt(6);
const AtomicString& kImage = NameAt(7);
const AtomicString& kFile = NameAt(8);
const AtomicString& kHidden = NameAt(9);
const AtomicString& kMonth = NameAt(10);
const AtomicString& kNumber = NameAt(11);
const AtomicString& kPassword = NameAt(12);
const AtomicString& kRadio = NameAt(13);
const AtomicString& kRange = NameAt(14);
const AtomicString& kReset = NameAt(15);
const AtomicString& kSearch = NameAt(16);
const AtomicString& kSubmit = NameAt(17);
const AtomicString& kTel = NameAt(18);
const AtomicString& kText = NameAt(19);
const AtomicString& kTime = NameAt(20);
const AtomicString& kUrl = NameAt(21);
const AtomicString& kWeek = NameAt(22);

void Init() {
  static bool is_loaded = false;
  if (is_loaded) {
    return;
  }
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
      {"button", 6},
      {"checkbox", 8},
      {"color", 5},
      {"date", 4},
      {"datetime", 8},
      {"datetime-local", 14},
      {"email", 5},
      {"image", 5},
      {"file", 4},
      {"hidden", 6},
      {"month", 5},
      {"number", 6},
      {"password", 8},
      {"radio", 5},
      {"range", 5},
      {"reset", 5},
      {"search", 6},
      {"submit", 6},
      {"tel", 3},
      {"text", 4},
      {"time", 4},
      {"url", 3},
      {"week", 4},
  };

  static_assert(std::size(kNames) == kNamesCount,
                "Generated-name storage must match kNamesCount.");

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl =
        StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    new (&NameAt(i)) AtomicString(impl);
  }
}

}  // namespace blink::input_type_names

namespace blink::media_type_names {

namespace {

void* names_storage[kNamesCount *
                    ((sizeof(AtomicString) + sizeof(void*) - 1) /
                     sizeof(void*))];

AtomicString& NameAt(size_t index) {
  return reinterpret_cast<AtomicString*>(&names_storage)[index];
}

}  // namespace

const AtomicString& kAll = NameAt(0);
const AtomicString& kScreen = NameAt(1);
const AtomicString& kPrint = NameAt(2);
const AtomicString& kTv = NameAt(3);

void Init() {
  static bool is_loaded = false;
  if (is_loaded) {
    return;
  }
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
      {"all", 3},
      {"screen", 6},
      {"print", 5},
      {"tv", 2},
  };

  static_assert(std::size(kNames) == kNamesCount,
                "Generated-name storage must match kNamesCount.");

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl =
        StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    new (&NameAt(i)) AtomicString(impl);
  }
}

}  // namespace blink::media_type_names

namespace blink::script_type_names {

namespace {

void* names_storage[kNamesCount *
                    ((sizeof(AtomicString) + sizeof(void*) - 1) /
                     sizeof(void*))];

AtomicString& NameAt(size_t index) {
  return reinterpret_cast<AtomicString*>(&names_storage)[index];
}

}  // namespace

const AtomicString& kClassic = NameAt(0);
const AtomicString& kImportmap = NameAt(1);
const AtomicString& kModule = NameAt(2);
const AtomicString& kRoutemap = NameAt(3);
const AtomicString& kSpeculationrules = NameAt(4);
const AtomicString& kWebbundle = NameAt(5);

void Init() {
  static bool is_loaded = false;
  if (is_loaded) {
    return;
  }
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
      {"classic", 7},
      {"importmap", 9},
      {"module", 6},
      {"routemap", 8},
      {"speculationrules", 16},
      {"webbundle", 9},
  };

  static_assert(std::size(kNames) == kNamesCount,
                "Generated-name storage must match kNamesCount.");

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl =
        StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    new (&NameAt(i)) AtomicString(impl);
  }
}

}  // namespace blink::script_type_names

