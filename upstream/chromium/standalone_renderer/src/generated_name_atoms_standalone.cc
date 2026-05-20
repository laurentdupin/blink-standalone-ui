// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/css/media_feature_names.h"
#include "third_party/blink/renderer/core/html/shadow/shadow_element_names.h"

namespace blink::media_feature_names {

#define DEFINE_MEDIA_FEATURE_NAME(name, value) const AtomicString name(value);
DEFINE_MEDIA_FEATURE_NAME(kAnyHoverMediaFeature, "any-hover")
DEFINE_MEDIA_FEATURE_NAME(kAnyPointerMediaFeature, "any-pointer")
DEFINE_MEDIA_FEATURE_NAME(kAspectRatioMediaFeature, "aspect-ratio")
DEFINE_MEDIA_FEATURE_NAME(kBlockSizeMediaFeature, "block-size")
DEFINE_MEDIA_FEATURE_NAME(kColorGamutMediaFeature, "color-gamut")
DEFINE_MEDIA_FEATURE_NAME(kColorIndexMediaFeature, "color-index")
DEFINE_MEDIA_FEATURE_NAME(kColorMediaFeature, "color")
DEFINE_MEDIA_FEATURE_NAME(kDeviceAspectRatioMediaFeature, "device-aspect-ratio")
DEFINE_MEDIA_FEATURE_NAME(kDeviceHeightMediaFeature, "device-height")
DEFINE_MEDIA_FEATURE_NAME(kDevicePixelRatioMediaFeature, "device-pixel-ratio")
DEFINE_MEDIA_FEATURE_NAME(kDevicePostureMediaFeature, "device-posture")
DEFINE_MEDIA_FEATURE_NAME(kDeviceWidthMediaFeature, "device-width")
DEFINE_MEDIA_FEATURE_NAME(kDisplayModeMediaFeature, "display-mode")
DEFINE_MEDIA_FEATURE_NAME(kDisplayStateMediaFeature, "display-state")
DEFINE_MEDIA_FEATURE_NAME(kDynamicRangeMediaFeature, "dynamic-range")
DEFINE_MEDIA_FEATURE_NAME(kFallbackMediaFeature, "fallback")
DEFINE_MEDIA_FEATURE_NAME(kForcedColorsMediaFeature, "forced-colors")
DEFINE_MEDIA_FEATURE_NAME(kGridMediaFeature, "grid")
DEFINE_MEDIA_FEATURE_NAME(kHeightMediaFeature, "height")
DEFINE_MEDIA_FEATURE_NAME(kHorizontalViewportSegmentsMediaFeature,
                          "horizontal-viewport-segments")
DEFINE_MEDIA_FEATURE_NAME(kHoverMediaFeature, "hover")
DEFINE_MEDIA_FEATURE_NAME(kInlineSizeMediaFeature, "inline-size")
DEFINE_MEDIA_FEATURE_NAME(kInvertedColorsMediaFeature, "inverted-colors")
DEFINE_MEDIA_FEATURE_NAME(kMaxAspectRatioMediaFeature, "max-aspect-ratio")
DEFINE_MEDIA_FEATURE_NAME(kMaxBlockSizeMediaFeature, "max-block-size")
DEFINE_MEDIA_FEATURE_NAME(kMaxColorIndexMediaFeature, "max-color-index")
DEFINE_MEDIA_FEATURE_NAME(kMaxColorMediaFeature, "max-color")
DEFINE_MEDIA_FEATURE_NAME(kMaxDeviceAspectRatioMediaFeature,
                          "max-device-aspect-ratio")
DEFINE_MEDIA_FEATURE_NAME(kMaxDeviceHeightMediaFeature, "max-device-height")
DEFINE_MEDIA_FEATURE_NAME(kMaxDevicePixelRatioMediaFeature,
                          "max-device-pixel-ratio")
DEFINE_MEDIA_FEATURE_NAME(kMaxDeviceWidthMediaFeature, "max-device-width")
DEFINE_MEDIA_FEATURE_NAME(kMaxHeightMediaFeature, "max-height")
DEFINE_MEDIA_FEATURE_NAME(kMaxInlineSizeMediaFeature, "max-inline-size")
DEFINE_MEDIA_FEATURE_NAME(kMaxMonochromeMediaFeature, "max-monochrome")
DEFINE_MEDIA_FEATURE_NAME(kMaxResolutionMediaFeature, "max-resolution")
DEFINE_MEDIA_FEATURE_NAME(kMaxWidthMediaFeature, "max-width")
DEFINE_MEDIA_FEATURE_NAME(kMinAspectRatioMediaFeature, "min-aspect-ratio")
DEFINE_MEDIA_FEATURE_NAME(kMinBlockSizeMediaFeature, "min-block-size")
DEFINE_MEDIA_FEATURE_NAME(kMinColorIndexMediaFeature, "min-color-index")
DEFINE_MEDIA_FEATURE_NAME(kMinColorMediaFeature, "min-color")
DEFINE_MEDIA_FEATURE_NAME(kMinDeviceAspectRatioMediaFeature,
                          "min-device-aspect-ratio")
DEFINE_MEDIA_FEATURE_NAME(kMinDeviceHeightMediaFeature, "min-device-height")
DEFINE_MEDIA_FEATURE_NAME(kMinDevicePixelRatioMediaFeature,
                          "min-device-pixel-ratio")
DEFINE_MEDIA_FEATURE_NAME(kMinDeviceWidthMediaFeature, "min-device-width")
DEFINE_MEDIA_FEATURE_NAME(kMinHeightMediaFeature, "min-height")
DEFINE_MEDIA_FEATURE_NAME(kMinInlineSizeMediaFeature, "min-inline-size")
DEFINE_MEDIA_FEATURE_NAME(kMinMonochromeMediaFeature, "min-monochrome")
DEFINE_MEDIA_FEATURE_NAME(kMinResolutionMediaFeature, "min-resolution")
DEFINE_MEDIA_FEATURE_NAME(kMinWidthMediaFeature, "min-width")
DEFINE_MEDIA_FEATURE_NAME(kMonochromeMediaFeature, "monochrome")
DEFINE_MEDIA_FEATURE_NAME(kNavigationControlsMediaFeature, "navigation-controls")
DEFINE_MEDIA_FEATURE_NAME(kOrientationMediaFeature, "orientation")
DEFINE_MEDIA_FEATURE_NAME(kOriginTrialTestMediaFeature, "origin-trial-test")
DEFINE_MEDIA_FEATURE_NAME(kOverflowBlockMediaFeature, "overflow-block")
DEFINE_MEDIA_FEATURE_NAME(kOverflowInlineMediaFeature, "overflow-inline")
DEFINE_MEDIA_FEATURE_NAME(kPointerMediaFeature, "pointer")
DEFINE_MEDIA_FEATURE_NAME(kPrefersColorSchemeMediaFeature,
                          "prefers-color-scheme")
DEFINE_MEDIA_FEATURE_NAME(kPrefersContrastMediaFeature, "prefers-contrast")
DEFINE_MEDIA_FEATURE_NAME(kPrefersReducedDataMediaFeature,
                          "prefers-reduced-data")
DEFINE_MEDIA_FEATURE_NAME(kPrefersReducedMotionMediaFeature,
                          "prefers-reduced-motion")
DEFINE_MEDIA_FEATURE_NAME(kPrefersReducedTransparencyMediaFeature,
                          "prefers-reduced-transparency")
DEFINE_MEDIA_FEATURE_NAME(kResizableMediaFeature, "resizable")
DEFINE_MEDIA_FEATURE_NAME(kResolutionMediaFeature, "resolution")
DEFINE_MEDIA_FEATURE_NAME(kScanMediaFeature, "scan")
DEFINE_MEDIA_FEATURE_NAME(kScriptingMediaFeature, "scripting")
DEFINE_MEDIA_FEATURE_NAME(kScrollableMediaFeature, "scrollable")
DEFINE_MEDIA_FEATURE_NAME(kScrolledMediaFeature, "scrolled")
DEFINE_MEDIA_FEATURE_NAME(kSnappedMediaFeature, "snapped")
DEFINE_MEDIA_FEATURE_NAME(kStuckMediaFeature, "stuck")
DEFINE_MEDIA_FEATURE_NAME(kTransform3dMediaFeature, "transform-3d")
DEFINE_MEDIA_FEATURE_NAME(kUpdateMediaFeature, "update")
DEFINE_MEDIA_FEATURE_NAME(kVerticalViewportSegmentsMediaFeature,
                          "vertical-viewport-segments")
DEFINE_MEDIA_FEATURE_NAME(kVideoDynamicRangeMediaFeature, "video-dynamic-range")
DEFINE_MEDIA_FEATURE_NAME(kWidthMediaFeature, "width")
#undef DEFINE_MEDIA_FEATURE_NAME

}  // namespace blink::media_feature_names

namespace blink::shadow_element_names {

#define DEFINE_SHADOW_ELEMENT_NAME(name) const AtomicString name(#name);
DEFINE_SHADOW_ELEMENT_NAME(kIdClearButton)
DEFINE_SHADOW_ELEMENT_NAME(kIdDateTimeEdit)
DEFINE_SHADOW_ELEMENT_NAME(kIdDetailsContent)
DEFINE_SHADOW_ELEMENT_NAME(kIdDetailsSummary)
DEFINE_SHADOW_ELEMENT_NAME(kIdEditingViewPort)
DEFINE_SHADOW_ELEMENT_NAME(kIdFileUploadButton)
DEFINE_SHADOW_ELEMENT_NAME(kIdOptGroupLabel)
DEFINE_SHADOW_ELEMENT_NAME(kIdPasswordRevealButton)
DEFINE_SHADOW_ELEMENT_NAME(kIdPermissionIcon)
DEFINE_SHADOW_ELEMENT_NAME(kIdPickerIndicator)
DEFINE_SHADOW_ELEMENT_NAME(kIdPlaceholder)
DEFINE_SHADOW_ELEMENT_NAME(kIdPlaceholderBreak)
DEFINE_SHADOW_ELEMENT_NAME(kIdSearchClearButton)
DEFINE_SHADOW_ELEMENT_NAME(kIdSliderThumb)
DEFINE_SHADOW_ELEMENT_NAME(kIdSliderTrack)
DEFINE_SHADOW_ELEMENT_NAME(kIdSpinButton)
DEFINE_SHADOW_ELEMENT_NAME(kIdTextFieldContainer)
DEFINE_SHADOW_ELEMENT_NAME(kOptionLabelContainer)
DEFINE_SHADOW_ELEMENT_NAME(kOptionSlot)
DEFINE_SHADOW_ELEMENT_NAME(kPickerSelect)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoCalendarPickerIndicator)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoFileUploadButton)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoInputPlaceholder)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoInternalDatetimeContainer)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoInternalInputSuggested)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoInternalPermissionContainer)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoInternalPermissionTextSpan)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoMediaSliderContainer)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoMediaSliderThumb)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoMeterInnerElement)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoSliderContainer)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoSliderThumb)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoSliderTrack)
DEFINE_SHADOW_ELEMENT_NAME(kPseudoTextFieldDecorationContainer)
DEFINE_SHADOW_ELEMENT_NAME(kSelectAutofillPreview)
DEFINE_SHADOW_ELEMENT_NAME(kSelectAutofillPreviewText)
DEFINE_SHADOW_ELEMENT_NAME(kSelectButtonSlot)
DEFINE_SHADOW_ELEMENT_NAME(kSelectInnerElement)
DEFINE_SHADOW_ELEMENT_NAME(kSelectOptions)
DEFINE_SHADOW_ELEMENT_NAME(kSelectPopoverOptions)
#undef DEFINE_SHADOW_ELEMENT_NAME

}  // namespace blink::shadow_element_names
