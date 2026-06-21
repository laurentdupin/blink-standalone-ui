// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/features_generated.cc.tmpl
// and input files:
//   C:\Repos\chromium\third_party\blink\renderer\platform\runtime_enabled_features.json5


#include "third_party/blink/public/common/features_generated.h"

namespace blink {
namespace features {

BASE_FEATURE(kAboutBlankPageRespectsDarkModeOnUserAction,
    "AboutBlankPageRespectsDarkModeOnUserAction",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAccelerated2dCanvas,
    "Accelerated2dCanvas",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAcceleratedSmallCanvases,
    "AcceleratedSmallCanvases",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessibilityExposeDisplayNone,
    "AccessibilityExposeDisplayNone",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessibilityImplicitActions,
    "AccessibilityImplicitActions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessibilityMinRoleTabbable,
    "AccessibilityMinRoleTabbable",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessibilityOSLevelBoldText,
    "AccessibilityOSLevelBoldText",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessibilityProhibitedNames,
    "AccessibilityProhibitedNames",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessibilitySerializationSizeMetrics,
    "AccessibilitySerializationSizeMetrics",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAccessKeyLabel,
    "AccessKeyLabel",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAddressSpace,
    "AddressSpace",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAdInterestGroupAPI,
    "AdInterestGroupAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAdjustDOMOffsetToLayoutOffsetForSecureText,
    "AdjustDOMOffsetToLayoutOffsetForSecureText",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAdjustEndOfNextParagraphIfMovedParagraphIsUpdated,
    "AdjustEndOfNextParagraphIfMovedParagraphIsUpdated",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIClassifierAPI,
    "AIClassifierAPI",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAIEmbeddingsAPI,
    "AIEmbeddingsAPI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIEmbeddingsAPIForWorkers,
    "AIEmbeddingsAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentAnchoredFixedOffscreenNonActionability,
    "AIPageContentAnchoredFixedOffscreenNonActionability",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentAnchoredNonFixedOffscreenNonActionability,
    "AIPageContentAnchoredNonFixedOffscreenNonActionability",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentBuildOnLoadForTesting,
    "AIPageContentBuildOnLoadForTesting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentCheckGeometry,
    "AIPageContentCheckGeometry",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentConvertNodeTextToUtf8,
    "AIPageContentConvertNodeTextToUtf8",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentElementCSSRedaction,
    "AIPageContentElementCSSRedaction",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentIncludeSVGSubtree,
    "AIPageContentIncludeSVGSubtree",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentOuterBoxMapToAncestorSpace,
    "AIPageContentOuterBoxMapToAncestorSpace",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentPaidContentAnnotation,
    "AIPageContentPaidContentAnnotation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentTrackedElementsIframe,
    "AIPageContentTrackedElementsIframe",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentTrackedElementsPassword,
    "AIPageContentTrackedElementsPassword",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPageContentVisualViewportClamp,
    "AIPageContentVisualViewportClamp",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPromptAPI,
    "AIPromptAPI",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAIPromptAPIForExtension,
    "AIPromptAPIForExtension",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAIPromptAPIForWorkers,
    "AIPromptAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPromptAPILegacyIdentifiers,
    "AIPromptAPILegacyIdentifiers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPromptAPILegacyParams,
    "AIPromptAPILegacyParams",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPromptAPIMultimodalInput,
    "AIPromptAPIMultimodalInput",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAIPromptAPIParams,
    "AIPromptAPIParams",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAIPromptAPIStructuredOutput,
    "AIPromptAPIStructuredOutput",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIPromptAPIToolUse,
    "AIPromptAPIToolUse",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAIProofreadingAPI,
    "AIProofreadingAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIRewriterAPI,
    "AIRewriterAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIRewriterAPIForWorkers,
    "AIRewriterAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAISummarizationAPI,
    "AISummarizationAPI",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAISummarizationAPIForWorkers,
    "AISummarizationAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAISummarizationPerformancePreference,
    "AISummarizationPerformancePreference",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAIWriterAPI,
    "AIWriterAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAIWriterAPIForWorkers,
    "AIWriterAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAlignZoomToCenter,
    "AlignZoomToCenter",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAllImagesPaintedSentToElementTiming,
    "AllImagesPaintedSentToElementTiming",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAllowPreloadingWithCSPMetaTag,
    "AllowPreloadingWithCSPMetaTag",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAllowSkippingEditingBoundaryToMergeEnd,
    "AllowSkippingEditingBoundaryToMergeEnd",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAllowSvgUseToReferenceExternalDocumentRoot,
    "AllowSvgUseToReferenceExternalDocumentRoot",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAncestorOriginsStoredOnDocument,
    "AncestorOriginsStoredOnDocument",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAnchorFocusRingFix,
    "AnchorFocusRingFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAnchorPositionAdjustmentWithoutOverflow,
    "AnchorPositionAdjustmentWithoutOverflow",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAnimationProgressAPI,
    "AnimationProgressAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAnimationTrigger,
    "AnimationTrigger",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAnimationWorklet,
    "AnimationWorklet",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAnonymousIframe,
    "AnonymousIframe",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAOMAriaRelationshipProperties,
    "AOMAriaRelationshipProperties",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAOMAriaRelationshipPropertiesAriaOwns,
    "AOMAriaRelationshipPropertiesAriaOwns",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAppearanceBase,
    "AppearanceBase",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kApproximateGeolocationPermissionAccuracyMode,
    "ApproximateGeolocationPermissionAccuracyMode",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kApproximateGeolocationPermissionAPI,
    "ApproximateGeolocationPermissionAPI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kApproximateGeolocationWebVisibleAPI,
    "ApproximateGeolocationWebVisibleAPI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAppEnableAppTitle,
    "WebAppEnableAppTitle",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAriaActions,
    "AriaActions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAriaNotify,
    "AriaNotify",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAriaNotifyV2,
    "AriaNotifyV2",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kAriaRowColIndexText,
    "AriaRowColIndexText",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAudioContextAsyncStateTransitions,
    "AudioContextAsyncStateTransitions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAudioContextPlaybackStats,
    "AudioContextPlaybackStats",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAudioContextPlayoutStats,
    "AudioContextPlayoutStats",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAudioContextSetSinkId,
    "AudioContextSetSinkId",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAudioVideoTracks,
    "AudioVideoTracks",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAuthorSpecifiedLayoutScrollSnapBehavior,
    "AuthorSpecifiedLayoutScrollSnapBehavior",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAutofillEvent,
    "AutofillEvent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAutoPictureInPictureVideoHeuristics,
    "AutoPictureInPictureVideoHeuristics",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAvoidMergingStyledSpanWithSiblings,
    "AvoidMergingStyledSpanWithSiblings",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kAvoidNormalizingVisiblePositionsWhenStartEqualsEnd,
    "AvoidNormalizingVisiblePositionsWhenStartEqualsEnd",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBackfaceVisibilityInterop,
    "BackfaceVisibilityInterop",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBackForwardCacheSendNotRestoredReasons,
    "BackForwardCacheSendNotRestoredReasons",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBackForwardCacheRestorationPerformanceEntry,
    "BackForwardCacheRestorationPerformanceEntry",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBackForwardCacheUpdateNotRestoredReasonsName,
    "BackForwardCacheUpdateNotRestoredReasonsName",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBackgroundClipTextDecoration,
    "BackgroundClipTextDecoration",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBarcodeDetector,
    "BarcodeDetector",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kBaseAppearanceInlineSizing,
    "BaseAppearanceInlineSizing",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBasicShapeCornerRadius,
    "BasicShapeCornerRadius",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBidiCaretAffinity,
    "BidiCaretAffinity",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkExtensionChromeOS,
    "BlinkExtensionChromeOS",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkExtensionChromeOSIsolatedWebAppSetShape,
    "BlinkExtensionChromeOSIsolatedWebAppSetShape",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kBlinkExtensionChromeOSKiosk,
    "BlinkExtensionChromeOSKiosk",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkExtensionWebView,
    "BlinkExtensionWebView",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkExtensionWebViewMediaIntegrity,
    "BlinkExtensionWebViewMediaIntegrity",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkGeometryMapperViewportFastPath,
    "BlinkGeometryMapperViewportFastPath",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkLifecycleScriptForbidden,
    "BlinkLifecycleScriptForbidden",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlinkRuntimeCallStats,
    "BlinkRuntimeCallStats",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlobBytes,
    "BlobBytes",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBlockingFocusWithoutUserActivation,
    "BlockingFocusWithoutUserActivation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBlockSelectPopupUnfocusedWindow,
    "BlockSelectPopupUnfocusedWindow",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBoundaryEventDispatchTracksNodeRemoval,
    "BoundaryEventDispatchTracksNodeRemoval",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBoxDecorationBreakCloneLineBreaking,
    "BoxDecorationBreakCloneLineBreaking",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBrowserInitiatedAutomaticPictureInPicture,
    "BrowserInitiatedAutomaticPictureInPicture",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kBufferedBytesConsumerLimitSize,
    "BufferedBytesConsumerLimitSize",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kBypassPepcSecurityForTesting,
    "BypassPepcSecurityForTesting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCacheControlRFC7234Parsing,
    "CacheControlRFC7234Parsing",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCacheControlRFC7234ParsingMetrics,
    "CacheControlRFC7234ParsingMetrics",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCacheStyleAdjuster,
    "CacheStyleAdjuster",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCallExitNodeWithoutLayoutObject,
    "CallExitNodeWithoutLayoutObject",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvas2dCanvasFilter,
    "Canvas2dCanvasFilter",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvas2dLayers,
    "Canvas2dLayers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvas2dLayersWithOptions,
    "Canvas2dLayersWithOptions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvas2dMesh,
    "Canvas2dMesh",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasDrawElement,
    "CanvasDrawElement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasFloatingPoint,
    "CanvasFloatingPoint",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasGlobalHDRHeadroom,
    "CanvasGlobalHDRHeadroom",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasGradientCSSColor4,
    "CanvasGradientCSSColor4",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasHDR,
    "CanvasHDR",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasTextMetricsPreciseBounds,
    "CanvasTextMetricsPreciseBounds",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasToneMapping,
    "CanvasToneMapping",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvasUsesArcPaintOp,
    "CanvasUsesArcPaintOp",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCapabilityDelegationDigitalCredentials,
    "CapabilityDelegationDigitalCredentials",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCapabilityDelegationDisplayCaptureRequest,
    "CapabilityDelegationDisplayCaptureRequest",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCaptureController,
    "CaptureController",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCapturedMouseEvents,
    "CapturedMouseEvents",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCapturedSurfaceControl,
    "CapturedSurfaceControl",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCapturedSurfaceResolution,
    "CapturedSurfaceResolution",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCaptureHandle,
    "CaptureHandle",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCaretWithTextAffinityUpstream,
    "CaretWithTextAffinityUpstream",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCCTNewRFMPushBehavior,
    "CCTNewRFMPushBehavior",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCheckableInputTypeLayoutInline,
    "CheckableInputTypeLayoutInline",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCheckForCanonicalPositionInIdleSpellCheck,
    "CheckForCanonicalPositionInIdleSpellCheck",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCheckVisibilityExtraProperties,
    "CheckVisibilityExtraProperties",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClampWordBoundaryToContentEditableScope,
    "ClampWordBoundaryToContentEditableScope",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClearCurrentTargetAfterDispatch,
    "ClearCurrentTargetAfterDispatch",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClearFocusWithinOnSubtreeRemoval,
    "ClearFocusWithinOnSubtreeRemoval",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClearTargetOnlyIfInShadowTree,
    "ClearTargetOnlyIfInShadowTree",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClickFocusDoesntPersistStatusBubble,
    "ClickFocusDoesntPersistStatusBubble",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClipboardEventTargetCanBeFocusedElement,
    "ClipboardEventTargetCanBeFocusedElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClipboardEventTargetUsesContainerNode,
    "ClipboardEventTargetUsesContainerNode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClipboardItemWithDOMStringSupport,
    "ClipboardItemWithDOMStringSupport",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kClipElementVisibleBoundsInLocalRoot,
    "ClipElementVisibleBoundsInLocalRoot",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kClipPathNestedRasterOptimization,
    "ClipPathNestedRasterOptimization",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCoalesceSelectionchangeEvent,
    "CoalesceSelectionchangeEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCoepReflection,
    "CoepReflection",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCollapseZeroWidthSpaceWhenReuseItem,
    "CollapseZeroWidthSpaceWhenReuseItem",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kColorInputAcceptsCSSColors,
    "ColorInputAcceptsCSSColors",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kColorSpaceDisplayP3Linear,
    "ColorSpaceDisplayP3Linear",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kColorSpacePredefinedLinearSpaces,
    "ColorSpacePredefinedLinearSpaces",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kColorSpaceRec2100Linear,
    "ColorSpaceRec2100Linear",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCommaSeparatedContainerQueries,
    "CommaSeparatedContainerQueries",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kComposedPathReturnTargetBeingDispatched,
    "ComposedPathReturnTargetBeingDispatched",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCompositeBoxShadowAnimation,
    "CompositeBoxShadowAnimation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCompositeClipPathAnimation,
    "CompositeClipPathAnimation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCompositedAnimationsCancelledAsynchronously,
    "CompositedAnimationsCancelledAsynchronously",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCompositingDecisionAtAnimationPhaseBoundaries,
    "CompositingDecisionAtAnimationPhaseBoundaries",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCompositionForegroundMarkers,
    "CompositionForegroundMarkers",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCompositorEventTrigger,
    "CompositorEventTrigger",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCompositorTimelineTrigger,
    "CompositorTimelineTrigger",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kComputedAccessibilityInfo,
    "ComputedAccessibilityInfo",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kComputeInlineContentsSafeRetarget,
    "ComputeInlineContentsSafeRetarget",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kComputePressure,
    "ComputePressure",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kConcurrentNativePaintWorklets,
    "ConcurrentNativePaintWorklets",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kOverrideConnectionAllowlistOriginTrial,
    "OverrideConnectionAllowlistOriginTrial",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kConsiderSubOrSuperScriptAncestorAlignForCaretSelection,
    "ConsiderSubOrSuperScriptAncestorAlignForCaretSelection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kContactsManager,
    "ContactsManager",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kContactsManagerExtraProperties,
    "ContactsManagerExtraProperties",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kContainerNameOnly,
    "ContainerNameOnly",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kContainerTiming,
    "ContainerTiming",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kContentIndex,
    "ContentIndex",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kContextMenu,
    "ContextMenu",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kControlledFrame,
    "ControlledFrame",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kControlledFrameWebRequestSecurityInfo,
    "ControlledFrameWebRequestSecurityInfo",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCookieStoreAPIMaxAge,
    "CookieStoreAPIMaxAge",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCookieStoreAPIWhitespaceStripping,
    "CookieStoreAPIWhitespaceStripping",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCorrectTemplateFormParsing,
    "CorrectTemplateFormParsing",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCorsRFC1918,
    "CorsRFC1918",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCpuPerformance,
    "CpuPerformance",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCrashReportingStorageAPI,
    "CrashReportingStorageAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCreateInlineContentsExcludeOutOfFlow,
    "CreateInlineContentsExcludeOutOfFlow",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSPReportHash,
    "CSPReportHash",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAccentColorKeyword,
    "CSSAccentColorKeyword",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCSSActiveCaptionMapsToCanvas,
    "CSSActiveCaptionMapsToCanvas",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAlphaColorFunction,
    "CSSAlphaColorFunction",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAltCounter,
    "CSSAltCounter",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAnchorWithTransforms,
    "CSSAnchorWithTransforms",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAnimationIterationComposite,
    "CSSAnimationIterationComposite",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSArgumentGrammar,
    "CSSArgumentGrammar",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAtRuleCounterStyleImageSymbols,
    "CSSAtRuleCounterStyleImageSymbols",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSAtRuleCounterStyleSpeakAsDescriptor,
    "CSSAtRuleCounterStyleSpeakAsDescriptor",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSBackgroundClipBorderArea,
    "CSSBackgroundClipBorderArea",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSBorderShape,
    "CSSBorderShape",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCalcSimplificationAndSerialization,
    "CSSCalcSimplificationAndSerialization",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCaretAnimation,
    "CSSCaretAnimation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCaretColorWithOptionalSecondValue,
    "CSSCaretColorWithOptionalSecondValue",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCaretShape,
    "CSSCaretShape",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCaseSensitiveSelector,
    "CSSCaseSensitiveSelector",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSChUnitSpecCompliantFallback,
    "CSSChUnitSpecCompliantFallback",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSColorTypedOM,
    "CSSColorTypedOM",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSContainerProgressNotation,
    "CSSContainerProgressNotation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSContainerStyleQueriesRange,
    "CSSContainerStyleQueriesRange",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSContrastColor,
    "CSSContrastColor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCornersShorthand,
    "CSSCornersShorthand",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCounterResetReversed,
    "CSSCounterResetReversed",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCrossFade,
    "CSSCrossFade",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSCustomMedia,
    "CSSCustomMedia",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSDynamicRangeLimit,
    "CSSDynamicRangeLimit",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSEnumeratedCustomProperties,
    "CSSEnumeratedCustomProperties",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSFontFamilySerialization,
    "CSSFontFamilySerialization",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSFontSizeAdjust,
    "CSSFontSizeAdjust",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSFunctions,
    "CSSFunctions",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSGapDecoration,
    "CSSGapDecoration",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSGridGapSuppression,
    "CSSGridGapSuppression",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSGridLanesLayout,
    "CSSGridLanesLayout",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSHangingPunctuation,
    "CSSHangingPunctuation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSHexAlphaColor,
    "CSSHexAlphaColor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSIdentFunction,
    "CSSIdentFunction",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSImageAnimation,
    "CSSImageAnimation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSImageFunction,
    "CSSImageFunction",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSInheritFunction,
    "CSSInheritFunction",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSKeyframesRuleLength,
    "CSSKeyframesRuleLength",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLangExtendedRanges,
    "CSSLangExtendedRanges",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLayoutAPI,
    "CSSLayoutAPI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLetterAndWordSpacingPercentage,
    "CSSLetterAndWordSpacingPercentage",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLightDarkImage,
    "CSSLightDarkImage",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLineClamp,
    "CSSLineClamp",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLineClampLineBreakingEllipsis,
    "CSSLineClampLineBreakingEllipsis",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSListCounterAccounting,
    "CSSListCounterAccounting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLogicalCombinationPseudo,
    "CSSLogicalCombinationPseudo",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSMarkerNestedPseudoElement,
    "CSSMarkerNestedPseudoElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSMediaElementPseudos,
    "CSSMediaElementPseudos",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSMediaProgressNotation,
    "CSSMediaProgressNotation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSMixins,
    "CSSMixins",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSNestedPseudoElements,
    "CSSNestedPseudoElements",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSOMGetComputedStylePseudoElementRequiresColon,
    "CSSOMGetComputedStylePseudoElementRequiresColon",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSOverscrollBehaviorChain,
    "CSSOverscrollBehaviorChain",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPaintAPIArguments,
    "CSSPaintAPIArguments",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSParserIgnoreCharsetForURLs,
    "CSSParserIgnoreCharsetForURLs",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPolygonRounding,
    "CSSPolygonRounding",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPositionStickyStaticScrollPosition,
    "CSSPositionStickyStaticScrollPosition",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSProgressNotation,
    "CSSProgressNotation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoColumn,
    "CSSPseudoColumn",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoElementBackdrop,
    "CSSPseudoElementBackdrop",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoElementInterface,
    "CSSPseudoElementInterface",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoElementViewTransitions,
    "CSSPseudoElementViewTransitions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoHasSlotted,
    "CSSPseudoHasSlotted",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoScrollButtons,
    "CSSPseudoScrollButtons",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoScrollMarkers,
    "CSSPseudoScrollMarkers",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSRandomFunction,
    "CSSRandomFunction",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSRandomFunctionTypedOM,
    "CSSRandomFunctionTypedOM",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSResizeAuto,
    "CSSResizeAuto",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSResourceIntegrityEnforcement,
    "CSSResourceIntegrityEnforcement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSRevertRule,
    "CSSRevertRule",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSRubyOverhang,
    "CSSRubyOverhang",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSSafePrintableInset,
    "CSSSafePrintableInset",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScopeifiedParentPseudoClass,
    "CSSScopeifiedParentPseudoClass",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScopeImport,
    "CSSScopeImport",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrolledContainerQueries,
    "CSSScrolledContainerQueries",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollInitialTarget,
    "CSSScrollInitialTarget",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollMarkerGroupModes,
    "CSSScrollMarkerGroupModes",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollMarkerTargetBeforeAfter,
    "CSSScrollMarkerTargetBeforeAfter",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollSnapChangeEvent,
    "CSSScrollSnapChangeEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollSnapChangingEvent,
    "CSSScrollSnapChangingEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollSnapEventConstructorExposed,
    "CSSScrollSnapEventConstructorExposed",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollSnapEvents,
    "CSSScrollSnapEvents",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollTargetGroup,
    "CSSScrollTargetGroup",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSScrollTargetGroupAriaCurrent,
    "CSSScrollTargetGroupAriaCurrent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSShapeEllipseCirclePositionSerialization,
    "CSSShapeEllipseCirclePositionSerialization",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSShapeOutsidePathAndShapeSupport,
    "CSSShapeOutsidePathAndShapeSupport",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSShapeOutsideRectAndXywhSupport,
    "CSSShapeOutsideRectAndXywhSupport",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSStyleSheetInitBaseURL,
    "CSSStyleSheetInitBaseURL",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSSupportsAtRuleFunction,
    "CSSSupportsAtRuleFunction",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSSupportsForImportRules,
    "CSSSupportsForImportRules",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSSupportsNamedFeatureFunction,
    "CSSSupportsNamedFeatureFunction",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSSystemAccentColor,
    "CSSSystemAccentColor",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kCSSTextAlignMatchParent,
    "CSSTextAlignMatchParent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTextDecorationSkipInkAll,
    "CSSTextDecorationSkipInkAll",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTextDecorationSkipSpaces,
    "CSSTextDecorationSkipSpaces",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCssTextFit,
    "CssTextFit",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCssTextFitReshaping,
    "CssTextFitReshaping",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCssTextIndent,
    "CssTextIndent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTextSpacing,
    "CSSTextSpacing",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTextTransformFullSizeKana,
    "CSSTextTransformFullSizeKana",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTextTransformFullWidth,
    "CSSTextTransformFullWidth",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTextTransformMultiKeyword,
    "CSSTextTransformMultiKeyword",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTimelineNameConflictResolution,
    "CSSTimelineNameConflictResolution",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTimelineScopeAll,
    "CSSTimelineScopeAll",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTimelineScopeGlobal,
    "CSSTimelineScopeGlobal",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSTypedArithmetic,
    "CSSTypedArithmetic",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSURLRequestModifiers,
    "CSSURLRequestModifiers",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSUserSelectContain,
    "CSSUserSelectContain",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSUserValidAndUserInvalidForRadio,
    "CSSUserValidAndUserInvalidForRadio",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSVideoDynamicRangeMediaQueries,
    "CSSVideoDynamicRangeMediaQueries",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSViewTransitionAutoName,
    "CSSViewTransitionAutoName",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSZoomAnimation,
    "CSSZoomAnimation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCustomElementsDisableFormattingFixups,
    "CustomElementsDisableFormattingFixups",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kCustomizableCombobox,
    "CustomizableCombobox",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCustomizableSelectMultiplePopup,
    "CustomizableSelectMultiplePopup",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCustomScrollbarApplyMinimumThumbLength,
    "CustomScrollbarApplyMinimumThumbLength",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDatabase,
    "Database",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDateTimeInputTypeEarlyAdvanceFix,
    "DateTimeInputTypeEarlyAdvanceFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDeclarativeCSSModules,
    "DeclarativeCSSModules",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDeclarativeCSSModulesStyleTag,
    "DeclarativeCSSModulesStyleTag",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDeclarativeSkeletons,
    "DeclarativeSkeletons",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDecoupleComputedBorderWidthFromStyle,
    "DecoupleComputedBorderWidthFromStyle",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDecoupleResolvedColumnRuleWidthFromStyle,
    "DecoupleResolvedColumnRuleWidthFromStyle",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDelegatesFocusTextControlInputFix,
    "DelegatesFocusTextControlInputFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDeleteTextInContentEditableBeforeRemovingChildren,
    "DeleteTextInContentEditableBeforeRemovingChildren",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDeprecateUnloadOptOut,
    "DeprecateUnloadOptOut",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDesktopCaptureDisableLocalEchoControl,
    "DesktopCaptureDisableLocalEchoControl",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDesktopPWAsAdditionalWindowingControls,
    "DesktopPWAsAdditionalWindowingControls",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDesktopPWAsAdditionalWindowingControlsOnMove,
    "DesktopPWAsAdditionalWindowingControlsOnMove",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDeviceAttributes,
    "DeviceAttributes",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kDeviceOrientationRequestPermission,
    "DeviceOrientationRequestPermission",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDevicePosture,
    "DevicePosture",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDialogCloseWhenOpenRemoved,
    "DialogCloseWhenOpenRemoved",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDialogNewFocusBehavior,
    "DialogNewFocusBehavior",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDigitalGoodsV2_1,
    "DigitalGoodsV2_1",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kDirectSockets,
    "DirectSockets",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDirectSocketsInServiceWorkers,
    "DirectSocketsInServiceWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDirectSocketsInSharedWorkers,
    "DirectSocketsInSharedWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDisableAnchorCenterOnAlignJustifyItems,
    "DisableAnchorCenterOnAlignJustifyItems",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDisableEllipsisWhenScrolled,
    "DisableEllipsisWhenScrolled",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDisableRemoveFormatForPlainTextOnlyEditableDiv,
    "DisableRemoveFormatForPlainTextOnlyEditableDiv",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDisallowDisconnectedAreaNavigation,
    "DisallowDisconnectedAreaNavigation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDisallowPickerForReadonlyInputs,
    "DisallowPickerForReadonlyInputs",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDisconnectWebSocketOnBFCache,
    "DisconnectWebSocketOnBFCache",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDispatchHiddenVisibilityTransitions,
    "DispatchHiddenVisibilityTransitions",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDispatchSelectionchangeEventPerElement,
    "DispatchSelectionchangeEventPerElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDisplayContentsFocusable,
    "DisplayContentsFocusable",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentActiveViewTransition,
    "DocumentActiveViewTransition",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentCookie,
    "DocumentCookie",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentDomain,
    "DocumentDomain",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentOpenIframeUnloadEvents,
    "DocumentOpenIframeUnloadEvents",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentOpenOriginAliasRemoval,
    "DocumentOpenOriginAliasRemoval",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentOpenSandboxInheritanceRemoval,
    "DocumentOpenSandboxInheritanceRemoval",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPatching,
    "DocumentPatching",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPictureInPictureAPI,
    "DocumentPictureInPictureAPI",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kDocumentPictureInPicturePreferInitialPlacement,
    "DocumentPictureInPicturePreferInitialPlacement",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kDocumentPictureInPictureUserActivation,
    "DocumentPictureInPictureUserActivation",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kDocumentPolicyDocumentDomain,
    "DocumentPolicyDocumentDomain",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPolicyExpectNoLinkedResources,
    "DocumentPolicyExpectNoLinkedResources",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPolicyIncludeJSCallStacksInCrashReports,
    "DocumentPolicyIncludeJSCallStacksInCrashReports",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPolicyInDedicatedWorker,
    "DocumentPolicyInDedicatedWorker",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPolicyNetworkEfficiencyGuardrails,
    "DocumentPolicyNetworkEfficiencyGuardrails",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentPolicySyncXHR,
    "DocumentPolicySyncXHR",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDocumentWrite,
    "DocumentWrite",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDOMActivateBubblesInheritance,
    "DOMActivateBubblesInheritance",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDontLeakShadowTreesInDragEvents,
    "DontLeakShadowTreesInDragEvents",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDragAndDropJSFileObjects,
    "DragAndDropJSFileObjects",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kEditContextAssignmentAsPerSpec,
    "EditContextAssignmentAsPerSpec",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kEditContextHandleTextOrSelectionUpdateDuringComposition,
    "EditContextHandleTextOrSelectionUpdateDuringComposition",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kEditingLineMovementWithRubyFix,
    "EditingLineMovementWithRubyFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEditingUseDomPositionApi,
    "EditingUseDomPositionApi",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kElasticOverscrollUseEventDeltaForAxisSelection,
    "ElasticOverscrollUseEventDeltaForAxisSelection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kElementCapture,
    "ElementCapture",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kElementInnerTextHandleFirstLineStyle,
    "ElementInnerTextHandleFirstLineStyle",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kElementInternalsBehaviors,
    "ElementInternalsBehaviors",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kElementMatchContainer,
    "ElementMatchContainer",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kElementSpecificReadOnlyConstraintValidation,
    "ElementSpecificReadOnlyConstraintValidation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEmojiMonochromeRendering,
    "EmojiMonochromeRendering",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEndpointInclusiveCommitStyles,
    "EndpointInclusiveCommitStyles",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEnforceAnonymityExposure,
    "EnforceAnonymityExposure",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEnterInOpenShadowRoots,
    "EnterInOpenShadowRoots",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEntropyIgnoredForFirstVideoFrameLCP,
    "EntropyIgnoredForFirstVideoFrameLCP",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kEventPseudoTargetProperty,
    "EventPseudoTargetProperty",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEventTimingInteractionCount,
    "EventTimingInteractionCount",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kEventTimingTargetSelector,
    "EventTimingTargetSelector",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kEventTrigger,
    "EventTrigger",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kExperimentalJSProfilerMarkers,
    "ExperimentalJSProfilerMarkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kExperimentalPolicies,
    "ExperimentalPolicies",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kExposeCSSFontFeatureValuesRule,
    "ExposeCSSFontFeatureValuesRule",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kExposeRenderTimeNonTaoDelayedImage,
    "ExposeRenderTimeNonTaoDelayedImage",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kExtendedShapeCache,
    "ExtendedShapeCache",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kExtendedTextMetrics,
    "ExtendedTextMetrics",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kExternalPopupMenuClickEvent,
    "ExternalPopupMenuClickEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFaceDetector,
    "FaceDetector",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFastPositionIterator,
    "FastPositionIterator",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFencedFramesAPIChanges,
    "FencedFramesAPIChanges",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFencedFramesDefaultMode,
    "FencedFramesDefaultMode",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFetchBodyBytes,
    "FetchBodyBytes",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFetchLaterAPI,
    "FetchLaterAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFetchRetry,
    "FetchRetry",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFetchUploadStreaming,
    "FetchUploadStreaming",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileColorPickerConsumeActivation,
    "FileColorPickerConsumeActivation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileHandlingAPI,
    "FileHandlingAPI",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kFilePickerEventsFix,
    "FilePickerEventsFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemAccess,
    "FileSystemAccess",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemAccessAPIExperimental,
    "FileSystemAccessAPIExperimental",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemAccessGetCloudIdentifiers,
    "FileSystemAccessGetCloudIdentifiers",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kFileSystemAccessLocal,
    "FileSystemAccessLocal",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kFileSystemAccessLockingScheme,
    "FileSystemAccessLockingScheme",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemAccessOriginPrivate,
    "FileSystemAccessOriginPrivate",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemAccessRevokeReadOnRemove,
    "FileSystemAccessRevokeReadOnRemove",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemAccessWriteMode,
    "FileSystemAccessWriteMode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFileSystemObserver,
    "FileSystemObserver",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kFileSystemObserverUnobserve,
    "FileSystemObserverUnobserve",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFilterableSelect,
    "FilterableSelect",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFilterContainerLevelStyles,
    "FilterContainerLevelStyles",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFilteringPrimitives,
    "FilteringPrimitives",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFindFirstMisspellingEndWhenNonEditable,
    "FindFirstMisspellingEndWhenNonEditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFirstLineOnListItem,
    "FirstLineOnListItem",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFirstLineTextMetrics,
    "FirstLineTextMetrics",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFirstLineTextTransform,
    "FirstLineTextTransform",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixHTMLFormControlElementIsReadOnly,
    "FixHTMLFormControlElementIsReadOnly",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixJustifyQueryCommandValue,
    "FixJustifyQueryCommandValue",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixLinebreakForPreTag,
    "FixLinebreakForPreTag",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixMapElementEmptyNameBug,
    "FixMapElementEmptyNameBug",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixMarkerSuppressionForAppearanceAuto,
    "FixMarkerSuppressionForAppearanceAuto",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFixNextPositionCalculationInInsertList,
    "FixNextPositionCalculationInInsertList",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixSelectionPaintRangeNullOpt,
    "FixSelectionPaintRangeNullOpt",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixStrikethroughToggleInEmptyContentEditable,
    "FixStrikethroughToggleInEmptyContentEditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFixVisualRectRemoteViewportTransform,
    "FixVisualRectRemoteViewportTransform",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeAuctionDealSupport,
    "FledgeAuctionDealSupport",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeBiddingAndAuctionServerAPIMultiSeller,
    "FledgeBiddingAndAuctionServerAPIMultiSeller",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeClickiness,
    "FledgeClickiness",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeCustomMaxAuctionAdComponents,
    "FledgeCustomMaxAuctionAdComponents",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeDeprecatedRenderURLReplacements,
    "FledgeDeprecatedRenderURLReplacements",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeDirectFromSellerSignalsHeaderAdSlot,
    "FledgeDirectFromSellerSignalsHeaderAdSlot",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeDirectFromSellerSignalsWebBundles,
    "FledgeDirectFromSellerSignalsWebBundles",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeMultiBid,
    "FledgeMultiBid",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgePrivateModelTraining,
    "FledgePrivateModelTraining",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeRealTimeReporting,
    "FledgeRealTimeReporting",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeSellerNonce,
    "FledgeSellerNonce",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeSellerScriptExecutionMode,
    "FledgeSellerScriptExecutionMode",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeTrustedSignalsKVv1CreativeScanning,
    "FledgeTrustedSignalsKVv1CreativeScanning",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeTrustedSignalsKVv2ContextualData,
    "FledgeTrustedSignalsKVv2ContextualData",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFledgeTrustedSignalsKVv2Support,
    "FledgeTrustedSignalsKVv2Support",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFlexWrapBalance,
    "FlexWrapBalance",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFocusgroup,
    "Focusgroup",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFocusgroupGrid,
    "FocusgroupGrid",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFontAccess,
    "FontAccess",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kFontFallbackForTabSize,
    "FontFallbackForTabSize",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFontFamilyPostscriptMatchingCTMigration,
    "FontFamilyPostscriptMatchingCTMigration",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFontFamilyStyleMatchingCTMigration,
    "FontFamilyStyleMatchingCTMigration",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFontFeatureSettingsDescriptor,
    "FontFeatureSettingsDescriptor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFontFormatAvar2,
    "FontFormatAvar2",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFontLanguageOverride,
    "FontLanguageOverride",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFontMatchAliasesAsLastResort,
    "FontMatchAliasesAsLastResort",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFontStyleObliqueZeroDegreeAsNormal,
    "FontStyleObliqueZeroDegreeAsNormal",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kFontVariationSettingsDescriptor,
    "FontVariationSettingsDescriptor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kForceEagerMeasureMemory,
    "ForceEagerMeasureMemory",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kForceReduceMotion,
    "ForceReduceMotion",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFragmentedOofInCb,
    "FragmentedOofInCb",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kFreezeFramesOnVisibility,
    "FreezeFramesOnVisibility",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGamepadMultitouch,
    "GamepadMultitouch",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGamepadRawInputChangeEvent,
    "GamepadRawInputChangeEvent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGamepadWindowEventHandlers,
    "GamepadWindowEventHandlers",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGeolocationElement,
    "GeolocationElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGeometryMapperSingularTransformFix,
    "GeometryMapperSingularTransformFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGeometryUtils,
    "GeometryUtils",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGeometryUtilsForCSSPseudoElement,
    "GeometryUtilsForCSSPseudoElement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGetAllScreensMedia,
    "GetAllScreensMedia",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kGetComputedStyleOutsideFlatTree,
    "GetComputedStyleOutsideFlatTree",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGetDisplayMediaRequiresUserActivation,
    "GetDisplayMediaRequiresUserActivation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kGetDisplayMediaWindowAudioCapture,
    "GetDisplayMediaWindowAudioCapture",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGetElementsByNameOnlyHTMLElements,
    "GetElementsByNameOnlyHTMLElements",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGetUserMediaEchoCancellationModes,
    "GetUserMediaEchoCancellationModes",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGraphemeClusterBoundsCheck,
    "GraphemeClusterBoundsCheck",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kGroupEffect,
    "GroupEffect",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHandleDeletionAtStartAndEndBoundaryContainingHiddenElement,
    "HandleDeletionAtStartAndEndBoundaryContainingHiddenElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHandleDisconnectedSelectionDuringDOMChanges,
    "HandleDisconnectedSelectionDuringDOMChanges",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHandleInvalidMaskImageWithBackdropFilter,
    "HandleInvalidMaskImageWithBackdropFilter",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHandleShadowDOMInSubstringUtil,
    "HandleShadowDOMInSubstringUtil",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHandwritingRecognition,
    "HandwritingRecognition",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kHarfRustShaping,
    "HarfRustShaping",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHasUAVisualTransition,
    "HasUAVisualTransition",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHeadingOffset,
    "HeadingOffset",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHideVideoControlsWhenUnneeded,
    "HideVideoControlsWhenUnneeded",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHighlightsFromPoint,
    "HighlightsFromPoint",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHitTestBorderRadiusForStackingContext,
    "HitTestBorderRadiusForStackingContext",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHitTestContainerTransformStateForPreserve3d,
    "HitTestContainerTransformStateForPreserve3d",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLAdoptionAlgorithmNewSteps,
    "HTMLAdoptionAlgorithmNewSteps",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLCommandActionsV2,
    "HTMLCommandActionsV2",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLCommandElementRemoval,
    "HTMLCommandElementRemoval",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLCommandForScrollCommands,
    "HTMLCommandForScrollCommands",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLElementScrollParent,
    "HTMLElementScrollParent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLImageElementActualNaturalSize,
    "HTMLImageElementActualNaturalSize",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLInputElementDropWebkitClearButton,
    "HTMLInputElementDropWebkitClearButton",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLInterestForInterestButtonPseudo,
    "HTMLInterestForInterestButtonPseudo",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLLinkElementAttributeValueChanges,
    "HTMLLinkElementAttributeValueChanges",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLParserYieldAndDelayOftenForTesting,
    "HTMLParserYieldAndDelayOftenForTesting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLParserYieldByUserTiming,
    "HTMLParserYieldByUserTiming",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLPrintingArtifactAnnotations,
    "HTMLPrintingArtifactAnnotations",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kHTMLProcessingInstruction,
    "HTMLProcessingInstruction",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kICUCapitalization,
    "ICUCapitalization",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kIgnoreLetterSpacingInCursiveScripts,
    "IgnoreLetterSpacingInCursiveScripts",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kImageDataPixelFormat,
    "ImageDataPixelFormat",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kImageDocumentUseLayoutWidth,
    "ImageDocumentUseLayoutWidth",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kImageSrcsetReselection,
    "ImageSrcsetReselection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kIncomingCallNotifications,
    "IncomingCallNotifications",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kInertElementNonEditable,
    "InertElementNonEditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInfiniteCullRect,
    "InfiniteCullRect",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kInheritUserModifyWithoutContenteditable,
    "InheritUserModifyWithoutContenteditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInlineBlockLineNavigation,
    "InlineBlockLineNavigation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInlineScriptCacheHint,
    "InlineScriptCacheHint",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kInnerHTMLParserFastpathLogFailure,
    "InnerHTMLParserFastpathLogFailure",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kInputEventDataTransferForInsertCmd,
    "InputEventDataTransferForInsertCmd",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInputEventsDeleteNonCollapsedSelection,
    "InputEventsDeleteNonCollapsedSelection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInputInSelect,
    "InputInSelect",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kInputMultipleFieldsUI,
    "InputMultipleFieldsUI",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kInsertBlockquoteBeforeOuterBlock,
    "InsertBlockquoteBeforeOuterBlock",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInstallElement,
    "InstallElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInstallOnDeviceSpeechRecognition,
    "InstallOnDeviceSpeechRecognition",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInterestEventsNonComposed,
    "InterestEventsNonComposed",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInterestGroupsInSharedStorageWorklet,
    "InterestGroupsInSharedStorageWorklet",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kIntersectionObserverCompositedAnimationsForceMainFrames,
    "IntersectionObserverCompositedAnimationsForceMainFrames",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kInvertedColors,
    "InvertedColors",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kInvisibleSVGAnimationThrottling,
    "InvisibleSVGAnimationThrottling",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kJavaScriptCompileHintsPerFunctionMagicRuntime,
    "JavaScriptCompileHintsPerFunctionMagicRuntime",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kJavaScriptSourcePhaseImports,
    "JavaScriptSourcePhaseImports",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kKeySystemTrackConfigurationEncryptionScheme,
    "KeySystemTrackConfigurationEncryptionScheme",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLabelInteractiveContentCheckBeforeHandler,
    "LabelInteractiveContentCheckBeforeHandler",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLangAttributeAwareFormControlUI,
    "LangAttributeAwareFormControlUI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLanguageDetectionAPI,
    "LanguageDetectionAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLanguageDetectionAPIForWorkers,
    "LanguageDetectionAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLayoutBoxRectGettersUseFragments,
    "LayoutBoxRectGettersUseFragments",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLayoutIgnoreMarginsForSticky,
    "LayoutIgnoreMarginsForSticky",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLayoutOOFCollectInlinesFix,
    "LayoutOOFCollectInlinesFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLayoutTableCellAlignmentSafe,
    "LayoutTableCellAlignmentSafe",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLazyImageConformantLoadEventTiming,
    "LazyImageConformantLoadEventTiming",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLazyLoadVideoAndAudio,
    "LazyLoadVideoAndAudio",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLeftClickToHandleSuggestion,
    "LeftClickToHandleSuggestion",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kLightDismissFromClick,
    "LightDismissFromClick",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kListOwnerMustHaveCSSBox,
    "ListOwnerMustHaveCSSBox",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLockedMode,
    "LockedMode",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLogicalStartOfLineBlockFallback,
    "LogicalStartOfLineBlockFallback",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLongAnimationFrameSourceCharPosition,
    "LongAnimationFrameSourceCharPosition",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kLongAnimationFrameSourceLineColumn,
    "LongAnimationFrameSourceLineColumn",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLongAnimationFrameSourceLineColumnInterface,
    "LongAnimationFrameSourceLineColumnInterface",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLongAnimationFrameStyleDuration,
    "LongAnimationFrameStyleDuration",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLongPressLinkSelectText,
    "LongPressLinkSelectText",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLongTaskFromLongAnimationFrame,
    "LongTaskFromLongAnimationFrame",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMacCharacterFallbackCache,
    "MacCharacterFallbackCache",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMacDisableCtrlHomeEnd,
    "MacDisableCtrlHomeEnd",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMacSystemClipboardPermissionCheck,
    "MacSystemClipboardPermissionCheck",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kManagedConfiguration,
    "ManagedConfiguration",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMarginTrim,
    "MarginTrim",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMaskDeserializationTimeForCrossOriginMessages,
    "MaskDeserializationTimeForCrossOriginMessages",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMathMLOperatorRTLMirroring,
    "MathMLOperatorRTLMirroring",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMathMLSerializationOnCopy,
    "MathMLSerializationOnCopy",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMathMLSkipMtrTagInAncestorWrapping,
    "MathMLSkipMtrTagInAncestorWrapping",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMeasureMemory,
    "MeasureMemory",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaCapabilitiesEncodingInfo,
    "MediaCapabilitiesEncodingInfo",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaCapabilitiesSpatialAudio,
    "MediaCapabilitiesSpatialAudio",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaCapture,
    "MediaCapture",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kMediaCaptureCameraControls,
    "MediaCaptureCameraControls",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaCaptureVoiceIsolation,
    "MediaCaptureVoiceIsolation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaElementMutedDefaultState,
    "MediaElementMutedDefaultState",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaElementVolumeGreaterThanOne,
    "MediaElementVolumeGreaterThanOne",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaLatencyHint,
    "MediaLatencyHint",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaPlaybackWhileNotVisiblePermissionPolicy,
    "MediaPlaybackWhileNotVisiblePermissionPolicy",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaQueryNavigationControls,
    "MediaQueryNavigationControls",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaSessionChapterInformation,
    "MediaSessionChapterInformation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaSourceExperimental,
    "MediaSourceExperimental",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaStreamTrackProcessorStats,
    "MediaStreamTrackProcessorStats",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMediaStreamTrackWebSpeech,
    "MediaStreamTrackWebSpeech",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kMemoryConsumerForNGShapeCache,
    "MemoryConsumerForNGShapeCache",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMenuElements,
    "MenuElements",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMergeFixedLayers,
    "MergeFixedLayers",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMergeStickyLayers,
    "MergeStickyLayers",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMessagePortCloseEvent,
    "MessagePortCloseEvent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMiddleClickAutoscroll,
    "MiddleClickAutoscroll",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMixedContentAutoupgradesUseIsMixedContentRestrictedInFrame,
    "MixedContentAutoupgradesUseIsMixedContentRestrictedInFrame",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMobileLayoutTheme,
    "MobileLayoutTheme",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kModifyParagraphCrossEditingoundary,
    "ModifyParagraphCrossEditingoundary",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kModulePreloadReferrer,
    "ModulePreloadReferrer",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kModulePreloadStyleJson,
    "ModulePreloadStyleJson",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMojoJS,
    "MojoJS",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kMoveEndingSelectionToListChild,
    "MoveEndingSelectionToListChild",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kMulticolColumnWrapping,
    "MulticolColumnWrapping",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNavigateEventAddHandlerOnPrecommit,
    "NavigateEventAddHandlerOnPrecommit",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNavigateEventClearOnRestore,
    "NavigateEventClearOnRestore",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNavigateEventDeferCrossDocumentCommit,
    "NavigateEventDeferCrossDocumentCommit",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNavigationEventTiming,
    "NavigationEventTiming",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNavigationId,
    "NavigationId",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNavigatorContentUtils,
    "NavigatorContentUtils",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kNetInfoConstantType,
    "NetInfoConstantType",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNewHTMLSettingMethods,
    "NewHTMLSettingMethods",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNoExtendSelectionToUserSelectNoneOutOfFlow,
    "NoExtendSelectionToUserSelectNoneOutOfFlow",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNoFontAntialiasing,
    "NoFontAntialiasing",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNoIdleEncodingForWebTests,
    "NoIdleEncodingForWebTests",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kNonEmptyBlockquotesOnOutdenting,
    "NonEmptyBlockquotesOnOutdenting",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNonEmptyVisibleTextSelectionForTextFragment,
    "NonEmptyVisibleTextSelectionForTextFragment",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNonStandardAppearanceValueSliderVertical,
    "NonStandardAppearanceValueSliderVertical",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNormalizeLineEndingsInInsertText,
    "NormalizeLineEndingsInInsertText",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNormalizeNbspForPasteAndDrop,
    "NormalizeNbspForPasteAndDrop",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNormalizeNbspRichTextOnly,
    "NormalizeNbspRichTextOnly",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kNotificationConstructor,
    "NotificationConstructor",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kNumberInputFullWidthChars,
    "NumberInputFullWidthChars",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOffMainThreadCSSPaint,
    "OffMainThreadCSSPaint",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOffscreenCanvasGetContextAttributes,
    "OffscreenCanvasGetContextAttributes",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOffsetMappingReuseFullWidthSpaceFix,
    "OffsetMappingReuseFullWidthSpaceFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOffsetPathTransformUpdateFix,
    "OffsetPathTransformUpdateFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOmitBlurEventOnElementRemoval,
    "OmitBlurEventOnElementRemoval",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kOnDeviceWebSpeechAvailable,
    "OnDeviceWebSpeechAvailable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOnDeviceWebSpeechQuality,
    "OnDeviceWebSpeechQuality",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOpaqueRange,
    "OpaqueRange",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kOpenPopoverInvokerRestrictToSameTreeScope,
    "OpenPopoverInvokerRestrictToSameTreeScope",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOptionDisablednessCheckAncestors,
    "OptionDisablednessCheckAncestors",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOrientationEvent,
    "OrientationEvent",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kOriginAPI,
    "OriginAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOriginPolicy,
    "OriginPolicy",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kOutlineDrawAutoStyleZeroWidth,
    "OutlineDrawAutoStyleZeroWidth",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOverlayGlobalRuleRemoval,
    "OverlayGlobalRuleRemoval",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOverlayProperty,
    "OverlayProperty",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kOverscrollGestures,
    "OverscrollGestures",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPagePopup,
    "PagePopup",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kPagePopupCopyPaste,
    "PagePopupCopyPaste",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPageRevealEvent,
    "PageRevealEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPageSwapEvent,
    "PageSwapEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPaintCaretAfterInnerEditorPaint,
    "PaintCaretAfterInnerEditorPaint",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPaintHoldingForIframes,
    "PaintHoldingForIframes",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPaintOffsetTranslationForComposited,
    "PaintOffsetTranslationForComposited",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPaintTimingMixin,
    "PaintTimingMixin",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPaintUnderInvalidationChecking,
    "PaintUnderInvalidationChecking",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kParakeet,
    "Parakeet",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPartialCompletionNotAllowedInMoveParagraphs,
    "PartialCompletionNotAllowedInMoveParagraphs",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPartitionVisitedLinkDatabaseWithSelfLinks,
    "PartitionVisitedLinkDatabaseWithSelfLinks",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kPasswordReveal,
    "PasswordReveal",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPaymentLinkDetection,
    "PaymentLinkDetection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPaymentMethodChangeEvent,
    "PaymentMethodChangeEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPerformanceMarkCustomUserTimingFromSubframe,
    "PerformanceMarkCustomUserTimingFromSubframe",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPerformanceMarkFeatureUsage,
    "PerformanceMarkFeatureUsage",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPerformanceNavigationTimingConfidence,
    "PerformanceNavigationTimingConfidence",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPermissionsRequestRevoke,
    "PermissionsRequestRevoke",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPlaceholderVisibility,
    "PlaceholderVisibility",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPointerEventDeviceId,
    "PointerEventDeviceId",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPointerLockOnAndroid,
    "PointerLockOnAndroid",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPointerRawUpdateOnlyInSecureContext,
    "PointerRawUpdateOnlyInSecureContext",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPopoverHintNewBehavior,
    "PopoverHintNewBehavior",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPositionOutsideTabSpanCheckSiblingNode,
    "PositionOutsideTabSpanCheckSiblingNode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPositionVisibilityIgnoreNonClipAncestors,
    "PositionVisibilityIgnoreNonClipAncestors",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPotentialPermissionsPolicyReporting,
    "PotentialPermissionsPolicyReporting",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPreferDefaultScrollbarStyles,
    "PreferDefaultScrollbarStyles",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPreferNonCompositedScrolling,
    "PreferNonCompositedScrolling",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPreferredAudioOutputDevices,
    "PreferredAudioOutputDevices",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPrefersReducedData,
    "PrefersReducedData",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPreloadLinkRelDataUrls,
    "PreloadLinkRelDataUrls",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPrerender2,
    "Prerender2",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPrerender2CrossOriginIframes,
    "Prerender2CrossOriginIframes",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPrerenderActivationByFormSubmission,
    "PrerenderActivationByFormSubmission",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPrerenderUntilScript,
    "PrerenderUntilScript",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPreserveDropEffect,
    "PreserveDropEffect",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPreventTextSelectionJump,
    "PreventTextSelectionJump",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPreventUndoIfNotEditable,
    "PreventUndoIfNotEditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPrivateAggregationApiErrorReporting,
    "PrivateAggregationApiErrorReporting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kPrivateAggregationApiMaxContributions,
    "PrivateAggregationApiMaxContributions",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kProfilerAPI,
    "ProfilerAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kProfilerAPIForDedicatedWorker,
    "ProfilerAPIForDedicatedWorker",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kProgrammaticScrollPromise,
    "ProgrammaticScrollPromise",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kProgressMaxIsPositive,
    "ProgressMaxIsPositive",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPropagateOverscrollBehaviorFromRoot,
    "PropagateOverscrollBehaviorFromRoot",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPseudoElementsFocusable,
    "PseudoElementsFocusable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPseudoElementsHitTestable,
    "PseudoElementsHitTestable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kPseudoElementsHoverable,
    "PseudoElementsHoverable",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kQuotaExceededErrorUpdate,
    "QuotaExceededErrorUpdate",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kQuoteFirstLineStyle,
    "QuoteFirstLineStyle",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRasterInducingScroll,
    "RasterInducingScroll",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kReadableStreamBYOBReaderReadMinOption,
    "ReadableStreamBYOBReaderReadMinOption",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kReadClipboardDataOnClipboardItemGetType,
    "ReadClipboardDataOnClipboardItemGetType",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kReadingFlowWithSlots,
    "ReadingFlowWithSlots",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRecheckParentDuringNodeVectorInsertion,
    "RecheckParentDuringNodeVectorInsertion",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRecordSameDocumentPresentationTimeOnce,
    "RecordSameDocumentPresentationTimeOnce",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kReduceUserAgentMinorVersion,
    "ReduceUserAgentMinorVersion",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRegionCapture,
    "RegionCapture",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kRelOpenerBcgDependencyHint,
    "RelOpenerBcgDependencyHint",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRemotePlaybackBackend,
    "RemotePlaybackBackend",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kRemoveCharsetAutoDetectionForISO2022JP,
    "RemoveCharsetAutoDetectionForISO2022JP",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveChildrenInReplaceChildren,
    "RemoveChildrenInReplaceChildren",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveCollapsedPlaceholderForContentEditable,
    "RemoveCollapsedPlaceholderForContentEditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveDanglingMarkupInTarget,
    "RemoveDanglingMarkupInTarget",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveDataUrlInSvgUse,
    "RemoveDataUrlInSvgUse",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveFormatFilterBackgroundColor,
    "RemoveFormatFilterBackgroundColor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveNonAllowlistedCreateEvent,
    "RemoveNonAllowlistedCreateEvent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveScrollNodeWorkaround,
    "RemoveScrollNodeWorkaround",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveSelectionCanonicalizationInMoveParagraph,
    "RemoveSelectionCanonicalizationInMoveParagraph",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRemoveVisibleSelectionInDOMSelection,
    "RemoveVisibleSelectionInDOMSelection",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRenderBlockingFullFrameRate,
    "RenderBlockingFullFrameRate",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRenderBlockingStatus,
    "RenderBlockingStatus",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRenderPriorityAttribute,
    "RenderPriorityAttribute",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kReplacedNormalFlowStackingInlinePaint,
    "ReplacedNormalFlowStackingInlinePaint",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kReportFirstFrameTimeAsRenderTime,
    "ReportFirstFrameTimeAsRenderTime",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kReportLayoutShiftRectsInCssPixels,
    "ReportLayoutShiftRectsInCssPixels",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRequestIsReloadNavigation,
    "RequestIsReloadNavigation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRequestMainFrameAfterFirstVideoFrame,
    "RequestMainFrameAfterFirstVideoFrame",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kResolveVarStylesOnCopy,
    "ResolveVarStylesOnCopy",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kResourceTimingContentEncoding,
    "ResourceTimingContentEncoding",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kResourceTimingContentType,
    "ResourceTimingContentType",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kResourceTimingInitiator,
    "ResourceTimingInitiator",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kResourceTimingUseCORSForBodySizes,
    "ResourceTimingUseCORSForBodySizes",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRespectOverscrollBehaviorForScrollBubbling,
    "RespectOverscrollBehaviorForScrollBubbling",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kResponsiveIframes,
    "ResponsiveIframes",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRestrictOwnAudio,
    "RestrictOwnAudio",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRootScrollbarFollowsBrowserTheme,
    "RootScrollbarFollowsBrowserTheme",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kRouteMatching,
    "RouteMatching",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRtcAlwaysNegotiateDataChannels,
    "RtcAlwaysNegotiateDataChannels",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCDataChannelPriority,
    "RTCDataChannelPriority",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCDiagnosticLogging,
    "RTCDiagnosticLogging",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCEncodedFrameAudioLevel,
    "RTCEncodedFrameAudioLevel",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCEncodedFrameSetMetadata,
    "RTCEncodedFrameSetMetadata",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCEncodedFrameTimestamps,
    "RTCEncodedFrameTimestamps",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCEncodedVideoFrameAdditionalMetadata,
    "RTCEncodedVideoFrameAdditionalMetadata",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCJitterBufferTarget,
    "RTCJitterBufferTarget",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCRtpEncodingParametersCodec,
    "RTCRtpEncodingParametersCodec",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCRtpScaleResolutionDownTo,
    "RTCRtpScaleResolutionDownTo",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCRtpScriptTransform,
    "RTCRtpScriptTransform",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCRtpTransport,
    "RTCRtpTransport",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kRTCSvcScalabilityMode,
    "RTCSvcScalabilityMode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRunMicrotaskBeforeXmlScript,
    "RunMicrotaskBeforeXmlScript",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kRunSnapshotPostLayoutStateSteps,
    "RunSnapshotPostLayoutStateSteps",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSanitizeIDNEmailFormInput,
    "SanitizeIDNEmailFormInput",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSanitizerAPI,
    "SanitizerAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScopedCustomElementRegistry,
    "ScopedCustomElementRegistry",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScopedViewTransitions,
    "ScopedViewTransitions",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScoreLineBreakerAbort,
    "ScoreLineBreakerAbort",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScreenDetailedHdrHeadroom,
    "ScreenDetailedHdrHeadroom",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kScriptBasedOnUnicodeBlock,
    "ScriptBasedOnUnicodeBlock",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollAnchorPriorityCandidateSubtree,
    "ScrollAnchorPriorityCandidateSubtree",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollAnchorSerializationUseParentForTextNode,
    "ScrollAnchorSerializationUseParentForTextNode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollAxisLock,
    "ScrollAxisLock",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollbarColor,
    "ScrollbarColor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollbarGutterBugFix,
    "ScrollbarGutterBugFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollbarWidth,
    "ScrollbarWidth",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollIntoViewAlignAuto,
    "ScrollIntoViewAlignAuto",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollIntoViewNearest,
    "ScrollIntoViewNearest",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollIntoViewRootFrameViewportBugFix,
    "ScrollIntoViewRootFrameViewportBugFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollPerformanceTiming,
    "ScrollPerformanceTiming",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollTimelineCurrentTime,
    "ScrollTimelineCurrentTime",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollTimelineNamedRangeScroll,
    "ScrollTimelineNamedRangeScroll",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollTopLeftInterop,
    "ScrollTopLeftInterop",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kScrollToTextFragmentUniqueFragments,
    "ScrollToTextFragmentUniqueFragments",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSearchTextHighlightPseudo,
    "SearchTextHighlightPseudo",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSecurePaymentConfirmationAvailabilityAPI,
    "SecurePaymentConfirmationAvailabilityAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSecurePaymentConfirmationCapabilities,
    "SecurePaymentConfirmationCapabilities",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectAnchorInViewport,
    "SelectAnchorInViewport",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectAudioOutput,
    "SelectAudioOutput",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kSelectedcontentelementAttribute,
    "SelectedcontentelementAttribute",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectedcontentMultiple,
    "SelectedcontentMultiple",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectedcontentSpec,
    "SelectedcontentSpec",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionAndFocusedVisiblePositionMatch,
    "SelectionAndFocusedVisiblePositionMatch",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionCollapsedDirectionNone,
    "SelectionCollapsedDirectionNone",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionFocusAffinity,
    "SelectionFocusAffinity",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionHandleWithBottomClipped,
    "SelectionHandleWithBottomClipped",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionRemoveRangeNotFoundError,
    "SelectionRemoveRangeNotFoundError",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionSetBaseAndExtentNonNullNode,
    "SelectionSetBaseAndExtentNonNullNode",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionToStringSkipsUserSelectNone,
    "SelectionToStringSkipsUserSelectNone",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionUpdateOnlyAfterAutoscroll,
    "SelectionUpdateOnlyAfterAutoscroll",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectionUpdateToInitialSelectionInListify,
    "SelectionUpdateToInitialSelectionInListify",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectiveClipboardFormatRead,
    "SelectiveClipboardFormatRead",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectivePermissionsIntervention,
    "SelectivePermissionsIntervention",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectRemoveOverflowHidden,
    "SelectRemoveOverflowHidden",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSelectWebViewUntrustedEventRemoval,
    "SelectWebViewUntrustedEventRemoval",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSendEarlyLastBeginMainFrame,
    "SendEarlyLastBeginMainFrame",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSendSlotChangeSignalAfterNodeInserted,
    "SendSlotChangeSignalAfterNodeInserted",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSeparateDeferModuleScriptTasks,
    "SeparateDeferModuleScriptTasks",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebSerialAPI,
    "WebSerialAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSerializeViewTransitionStateInSPA,
    "SerializeViewTransitionStateInSPA",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kServiceWorkerBackgroundSyncInDedicatedWorker,
    "ServiceWorkerBackgroundSyncInDedicatedWorker",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kServiceWorkerClientLifecycleState,
    "ServiceWorkerClientLifecycleState",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kServiceWorkerInDedicatedWorker,
    "ServiceWorkerInDedicatedWorker",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kServiceWorkerStaticRouterTimingInfo,
    "ServiceWorkerStaticRouterTimingInfo",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSetDefaultDropEffect,
    "SetDefaultDropEffect",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSetHTMLCanRunScripts,
    "SetHTMLCanRunScripts",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSetSequentialFocusStartingPoint,
    "SetSequentialFocusStartingPoint",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kShadowContourFollowsBorder,
    "ShadowContourFollowsBorder",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kShadowRootAdoptedStyleSheet,
    "ShadowRootAdoptedStyleSheet",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kShadowRootReferenceTarget,
    "ShadowRootReferenceTarget",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kShadowRootReferenceTargetAriaOwns,
    "ShadowRootReferenceTargetAriaOwns",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSharedStorageWebLocks,
    "SharedStorageWebLocks",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSharedWorker,
    "SharedWorker",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSharedWorkerExtendedLifetime,
    "SharedWorkerExtendedLifetime",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSideRelativeBackgroundPosition,
    "SideRelativeBackgroundPosition",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSignatureBasedInlineIntegrity,
    "SignatureBasedInlineIntegrity",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSingleAxisScrollContainers,
    "SingleAxisScrollContainers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipAd,
    "SkipAd",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipCallbacksWhenDevToolsNotOpen,
    "SkipCallbacksWhenDevToolsNotOpen",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipEventCapture,
    "SkipEventCapture",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipNonEditableInAtomicMove,
    "SkipNonEditableInAtomicMove",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipOofItemForBreakCandidate,
    "SkipOofItemForBreakCandidate",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipParagraphSplitForInlineInsertHTML,
    "SkipParagraphSplitForInlineInsertHTML",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipPseudoOnlyLinesInLineNavigation,
    "SkipPseudoOnlyLinesInLineNavigation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipTouchEventFilter,
    "SkipTouchEventFilter",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipUnselectableContentInSerialization,
    "SkipUnselectableContentInSerialization",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSkipUnselectableElementsInParagraphBoundary,
    "SkipUnselectableElementsInParagraphBoundary",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSmallerViewportUnits,
    "SmallerViewportUnits",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSmartCard,
    "SmartCard",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kSnapshotScrollTimelinesPostLayout,
    "SnapshotScrollTimelinesPostLayout",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSoftNavigationDetection,
    "SoftNavigationDetection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSoftNavigationDetectionIncludeReplaceState,
    "SoftNavigationDetectionIncludeReplaceState",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSoftNavigationHeuristics,
    "SoftNavigationHeuristics",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSortedLayoutShiftSourcesByImpactArea,
    "SortedLayoutShiftSourcesByImpactArea",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSourceSpecificMulticastInDirectSockets,
    "SourceSpecificMulticastInDirectSockets",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSpatNavUsesCursorInheritance,
    "SpatNavUsesCursorInheritance",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSpeakerSelection,
    "SpeakerSelection",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSpeculationMeasurement,
    "SpeculationMeasurement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSpellCheckChunking,
    "SpellCheckChunking",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kSpellCheckCustomDictionaryAPI,
    "SpellCheckCustomDictionaryAPI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSplitTextNotCleanupDummySpans,
    "SplitTextNotCleanupDummySpans",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSrcsetSelectionMatchesImageSet,
    "SrcsetSelectionMatchesImageSet",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStackingContextIsNotStacked,
    "StackingContextIsNotStacked",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStaleImageNaturalSizeDuringRevalidation,
    "StaleImageNaturalSizeDuringRevalidation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStandardizedBrowserZoom,
    "StandardizedBrowserZoom",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStandardizedBrowserZoomOptOut,
    "StandardizedBrowserZoomOptOut",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kStickyPositionHasOverflowPerAxis,
    "StickyPositionHasOverflowPerAxis",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStickyUserActivationAcrossSameOriginNavigation,
    "StickyUserActivationAcrossSameOriginNavigation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStorageBuckets,
    "StorageBuckets",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kStorageBucketsDurability,
    "StorageBucketsDurability",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kStorageBucketsLocks,
    "StorageBucketsLocks",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kStreamingSanitizer,
    "StreamingSanitizer",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kStrictMimeTypesForWorkers,
    "StrictMimeTypesForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSubApps,
    "SubApps",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSuppressPointerStreamAfterDrag,
    "SuppressPointerStreamAfterDrag",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgAnchorElementAttributes,
    "SvgAnchorElementAttributes",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgAnchorElementDownloadAttribute,
    "SvgAnchorElementDownloadAttribute",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgAnimateMotionDiscreteCalcMode,
    "SvgAnimateMotionDiscreteCalcMode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgAvoidResettingFilterQualityForTiledPattern,
    "SvgAvoidResettingFilterQualityForTiledPattern",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSVGEmbeddedAsReplacedElement,
    "SVGEmbeddedAsReplacedElement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgEnableTextDecorationCssStyling,
    "SvgEnableTextDecorationCssStyling",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgFallBackToContainerSize,
    "SvgFallBackToContainerSize",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgFeImageEXIFOrientation,
    "SvgFeImageEXIFOrientation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgFeImageSkipHiddenContainerViewportDependence,
    "SvgFeImageSkipHiddenContainerViewportDependence",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgFilterPaintsForHiddenContent,
    "SvgFilterPaintsForHiddenContent",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgFilterUserSpaceViewportForSvg,
    "SvgFilterUserSpaceViewportForSvg",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgIgnoreNegativeEllipseRadii,
    "SvgIgnoreNegativeEllipseRadii",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgInlineRootPixelSnappingScaleAdjustment,
    "SvgInlineRootPixelSnappingScaleAdjustment",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgLengthResolveUnparsedValue,
    "SvgLengthResolveUnparsedValue",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgPathLengthCssProperty,
    "SvgPathLengthCssProperty",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgPointListClearOnParsingFailure,
    "SvgPointListClearOnParsingFailure",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgScriptElementAsyncAttribute,
    "SvgScriptElementAsyncAttribute",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgSizingWithPreserveAspectRatioNone,
    "SvgSizingWithPreserveAspectRatioNone",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgSmilClockValueValidation,
    "SvgSmilClockValueValidation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgSupportMediaFragments,
    "SvgSupportMediaFragments",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgTextPathPathAttribute,
    "SvgTextPathPathAttribute",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgUseNestedResourceDocuments,
    "SvgUseNestedResourceDocuments",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgUseNestedResourceDocumentsDelayLoad,
    "SvgUseNestedResourceDocumentsDelayLoad",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSynthesizedKeyboardEventsForAccessibilityActions,
    "SynthesizedKeyboardEventsForAccessibilityActions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSyntheticMouseHoverOverInactivePage,
    "SyntheticMouseHoverOverInactivePage",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSystemFallbackEmojiVSSupport,
    "SystemFallbackEmojiVSSupport",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kSystemWakeLock,
    "SystemWakeLock",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTableBorderColorNoImplicitBorder,
    "TableBorderColorNoImplicitBorder",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTableDefaultBorderColorCurrentColor,
    "TableDefaultBorderColorCurrentColor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTableIsAutoFixedLayout,
    "TableIsAutoFixedLayout",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTabSizeAncestor,
    "TabSizeAncestor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTabSizeWithSpacing,
    "TabSizeWithSpacing",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTargetInShadowDeterminedBeforeListener,
    "TargetInShadowDeterminedBeforeListener",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTestBlinkFeatureDefault,
    "TestBlinkFeatureDefault",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTestFeatureStable,
    "TestFeatureStable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextAreaScrollTopPreview,
    "TextAreaScrollTopPreview",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextBoxTrimForNestedList,
    "TextBoxTrimForNestedList",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextDetector,
    "TextDetector",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTextEmphasisLetterSpacing,
    "TextEmphasisLetterSpacing",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextEmphasisPositionAuto,
    "TextEmphasisPositionAuto",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTextEmphasisPunctuationExceptions,
    "TextEmphasisPunctuationExceptions",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextEmphasisWithRuby,
    "TextEmphasisWithRuby",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextFragmentAPI,
    "TextFragmentAPI",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTextFragmentAnchor,
    "TextFragmentAnchor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextFragmentTapOpensContextMenu,
    "TextFragmentTapOpensContextMenu",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kTextMetricsBaselines,
    "TextMetricsBaselines",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextOverflowClipWithSelection,
    "TextOverflowClipWithSelection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextOverflowString,
    "TextOverflowString",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTextScaleMetaTag,
    "TextScaleMetaTag",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextSpacingTrimFallback,
    "TextSpacingTrimFallback",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextSpacingTrimFallback2,
    "TextSpacingTrimFallback2",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTextSpacingTrimFallbackChws,
    "TextSpacingTrimFallbackChws",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTextStreamMethod,
    "TextStreamMethod",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kThrottledHistoryAPIThrowsSecurityError,
    "ThrottledHistoryAPIThrowsSecurityError",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTimelineTrigger,
    "TimelineTrigger",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTimestampBasedCLSTracking,
    "TimestampBasedCLSTracking",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTimeZoneChangeEvent,
    "TimeZoneChangeEvent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTouchDragOnShortPress,
    "TouchDragOnShortPress",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kTransferableRTCDataChannel,
    "TransferableRTCDataChannel",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTransitionNavigationQuietSkip,
    "TransitionNavigationQuietSkip",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTranslateService,
    "TranslateService",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTranslationAPI,
    "TranslationAPI",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTranslationAPIForWorkers,
    "TranslationAPIForWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTraverseFlatTreeToHandleSlots,
    "TraverseFlatTreeToHandleSlots",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTreatMhtmlInitialDocumentLoadsAsCrossDocument,
    "TreatMhtmlInitialDocumentLoadsAsCrossDocument",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTrustedTypesCreateParserOptions,
    "TrustedTypesCreateParserOptions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTrustedTypesHTML,
    "TrustedTypesHTML",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kTrustedTypesUseCodeLike,
    "TrustedTypesUseCodeLike",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTwoPhaseViewTransition,
    "TwoPhaseViewTransition",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUnboundedElement,
    "UnboundedElement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUnboundedElementOnTheOpenWeb,
    "UnboundedElementOnTheOpenWeb",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUnclosedFormControlIsInvalid,
    "UnclosedFormControlIsInvalid",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUnexposedTaskIds,
    "UnexposedTaskIds",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUnprefixedSpeechRecognition,
    "UnprefixedSpeechRecognition",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUnrestrictedMeasureUserAgentSpecificMemory,
    "UnrestrictedMeasureUserAgentSpecificMemory",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUnrestrictedUsb,
    "UnrestrictedUsb",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUpdateComplexSafaAreaConstraints,
    "UpdateComplexSafaAreaConstraints",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kUpdateSelectionOnNodeInsertion,
    "UpdateSelectionOnNodeInsertion",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUpdateTrivalTextAfterFragmentCreationFromText,
    "UpdateTrivalTextAfterFragmentCreationFromText",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kURLPatternCompareComponent,
    "URLPatternCompareComponent",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kURLPatternGenerate,
    "URLPatternGenerate",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kURLSearchParamsHasAndDeleteMultipleArgs,
    "URLSearchParamsHasAndDeleteMultipleArgs",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUseBeginFramePresentationFeedback,
    "UseBeginFramePresentationFeedback",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kUseBoundedSelectionOffsetsInEditContextDeleteOperations,
    "UseBoundedSelectionOffsetsInEditContextDeleteOperations",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUseLargestPaintedImageForLCPCandidate,
    "UseLargestPaintedImageForLCPCandidate",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUseLowQualityInterpolation,
    "UseLowQualityInterpolation",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kUseOriginalDomOffsetsForOffsetMap,
    "UseOriginalDomOffsetsForOffsetMap",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUsePositionForPointInFlexibleBoxWithSingleChildElement,
    "UsePositionForPointInFlexibleBoxWithSingleChildElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUsePositionIfIsVisuallyEquivalentCandidate,
    "UsePositionIfIsVisuallyEquivalentCandidate",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUserActionPseudosStopAtTopLayer,
    "UserActionPseudosStopAtTopLayer",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUserDefinedEntryPointTiming,
    "UserDefinedEntryPointTiming",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kUserMediaElement,
    "UserMediaElement",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUseSelectionInDOMTreeAnchorInExtendSelection,
    "UseSelectionInDOMTreeAnchorInExtendSelection",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUseShadowHostStyleCheckEditable,
    "UseShadowHostStyleCheckEditable",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kUseUndoStepElementDispatchBeforeInput,
    "UseUndoStepElementDispatchBeforeInput",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoAutoFullscreen,
    "VideoAutoFullscreen",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoFrameMetadataBackgroundBlur,
    "VideoFrameMetadataBackgroundBlur",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoFrameMetadataRtpTimestamp,
    "VideoFrameMetadataRtpTimestamp",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoFullscreenOrientationLock,
    "VideoFullscreenOrientationLock",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoRotateToFullscreen,
    "VideoRotateToFullscreen",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoTrackGenerator,
    "VideoTrackGenerator",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoTrackGeneratorInWindow,
    "VideoTrackGeneratorInWindow",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVideoTrackGeneratorInWorker,
    "VideoTrackGeneratorInWorker",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kViewportHeightClientHintHeader,
    "ViewportHeightClientHintHeader",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kViewportSegments,
    "ViewportSegments",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kViewTransitionAsyncFinished,
    "ViewTransitionAsyncFinished",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kViewTransitionDelayUnpauseOnTeardown,
    "ViewTransitionDelayUnpauseOnTeardown",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kViewTransitionHoistBackdropFilterEffect,
    "ViewTransitionHoistBackdropFilterEffect",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kViewTransitionLongCallbackTimeoutForTesting,
    "ViewTransitionLongCallbackTimeoutForTesting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kViewTransitionUpdateLifecycleBeforeReady,
    "ViewTransitionUpdateLifecycleBeforeReady",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kViewTransitionWaitUntil,
    "ViewTransitionWaitUntil",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kVisibilityCollapseColumn,
    "VisibilityCollapseColumn",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kVisualRectMappingFixForExpansion,
    "VisualRectMappingFixForExpansion",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWakeLock,
    "WakeLock",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWarnOnContentVisibilityRenderAccess,
    "WarnOnContentVisibilityRenderAccess",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAppInstallation,
    "WebAppInstallation",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAppLaunchQueue,
    "WebAppLaunchQueue",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAppScopeSystemAccentColor,
    "WebAppScopeSystemAccentColor",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDesktopPWAsTabStrip,
    "DesktopPWAsTabStrip",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kDesktopPWAsTabStripCustomizations,
    "DesktopPWAsTabStripCustomizations",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAppEnableTranslations,
    "WebAppEnableTranslations",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAudioBypassOutputBuffering,
    "WebAudioBypassOutputBuffering",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kWebAudioBypassOutputBufferingOptOut,
    "WebAudioBypassOutputBufferingOptOut",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAudioConfigurableRenderQuantum,
    "WebAudioConfigurableRenderQuantum",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAuth,
    "WebAuth",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAuthAuthenticatorAttachment,
    "WebAuthAuthenticatorAttachment",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAuthenticationAttestationFormats,
    "WebAuthenticationAttestationFormats",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAuthenticationCmtgKey,
    "WebAuthenticationCmtgKey",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebAuthenticationSupplementalPubKeys,
    "WebAuthenticationSupplementalPubKeys",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebBluetoothScanning,
    "WebBluetoothScanning",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebCodecsVideoEncoderBuffers,
    "WebCodecsVideoEncoderBuffers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebCryptoPQC,
    "WebCryptoPQC",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebFontResizeLCP,
    "WebFontResizeLCP",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGLDrawingBufferStorage,
    "WebGLDrawingBufferStorage",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGLOnWebGPU,
    "WebGLOnWebGPU",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGPUCompatibilityMode,
    "WebGPUCompatibilityMode",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGPUExperimentalFeatures,
    "WebGPUExperimentalFeatures",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGPUImmediatesFeature,
    "WebGPUImmediatesFeature",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGPUMapSyncOnWorkers,
    "WebGPUMapSyncOnWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGPUMultithreadDawnWireOnWorkers,
    "WebGPUMultithreadDawnWireOnWorkers",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebGPUTransientAttachment,
    "WebGPUTransientAttachment",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebHID,
    "WebHID",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kWebIDLBigIntUsesToBigInt,
    "WebIDLBigIntUsesToBigInt",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebMCP,
    "WebMCP",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebMCPDeclarativeFileInput,
    "WebMCPDeclarativeFileInput",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebMCPFormAssociatedCustomElements,
    "WebMCPFormAssociatedCustomElements",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebMCPTesting,
    "WebMCPTesting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebPreferences,
    "WebPreferences",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebPrinting,
    "WebPrinting",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kWebRtcSctpSnap,
    "WebRtcSctpSnap",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebShare,
    "WebShare",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebSocketStream,
    "WebSocketStream",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebSocketStreamStandardBinaryChunkType,
    "WebSocketStreamStandardBinaryChunkType",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebSpeechRecognitionContext,
    "WebSpeechRecognitionContext",
#if BUILDFLAG(IS_ANDROID)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_WIN)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_CHROMEOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_MAC)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_LINUX)
    base::FEATURE_ENABLED_BY_DEFAULT
#endif
#if BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
#if !BUILDFLAG(IS_ANDROID) && !BUILDFLAG(IS_WIN) && !BUILDFLAG(IS_CHROMEOS) && !BUILDFLAG(IS_MAC) && !BUILDFLAG(IS_LINUX) && !BUILDFLAG(IS_IOS)
    base::FEATURE_DISABLED_BY_DEFAULT
#endif
);

BASE_FEATURE(kWebSpeechUnspokenPunctuation,
    "WebSpeechUnspokenPunctuation",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebUIBundledCodeCacheAsyncFetch,
    "WebUIBundledCodeCacheAsyncFetch",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebUSBOnDedicatedWorkers,
    "WebUSBOnDedicatedWorkers",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebVTTRegions,
    "WebVTTRegions",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebXREnabledFeatures,
    "WebXREnabledFeatures",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWebXRHitTestEntityTypes,
    "WebXRHitTestEntityTypes",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebXRMediaBinding,
    "WebXRMediaBinding",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebXRMeshDetection,
    "WebXRMeshDetection",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebXRSpecParity,
    "WebXRSpecParity",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWebXRVisibilityMask,
    "WebXRVisibilityMask",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWheelEventMomentum,
    "WheelEventMomentum",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWindowDefaultStatus,
    "WindowDefaultStatus",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kWordSkipSpacesPunctuationFix,
    "WordSkipSpacesPunctuationFix",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kWordSpacingWhiteSpacePre,
    "WordSpacingWhiteSpacePre",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kXMLNoExternalEntities,
    "XMLNoExternalEntities",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kXMLParsingRust,
    "XMLParsingRust",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kXMLRustForNonXslt,
    "XMLRustForNonXslt",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kXMLSerializerConsistentDefaultNsDeclMatching,
    "XMLSerializerConsistentDefaultNsDeclMatching",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kXPathShadowDOMSupport,
    "XPathShadowDOMSupport",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kXSLT,
    "XSLT",
    base::FEATURE_ENABLED_BY_DEFAULT
);

BASE_FEATURE(kXSLTSpecialTrial,
    "XSLTSpecialTrial",
    base::FEATURE_DISABLED_BY_DEFAULT
);

// Standalone generated-artifact alignment: this checked generated source was
// missing definitions for declarations emitted in features_generated.h and
// referenced by runtime_enabled_features.cc.
BASE_FEATURE(kAIPageContentAnchoredOffscreenNonActionability,
    "AIPageContentAnchoredOffscreenNonActionability",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAncestorRevealingNewSpec,
    "AncestorRevealingNewSpec",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAsyncSetCookie,
    "AsyncSetCookie",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kAvoidForcedLayoutOnInvisibleDocumentClose,
    "AvoidForcedLayoutOnInvisibleDocumentClose",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCanvas2dGPUTransfer,
    "Canvas2dGPUTransfer",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCommandEventNotComposed,
    "CommandEventNotComposed",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kComputePressureOwnContributionEstimate,
    "ComputePressureOwnContributionEstimate",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSLineClampLinesAndHeight,
    "CSSLineClampLinesAndHeight",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCSSPseudoPlayingPaused,
    "CSSPseudoPlayingPaused",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kCssTextIndentAsPrimitive,
    "CssTextIndentAsPrimitive",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kDateTimeLocalArabicCommaWorkaround,
    "DateTimeLocalArabicCommaWorkaround",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kEditEmojiTagSequence,
    "EditEmojiTagSequence",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kImprovedSourceRetargeting,
    "ImprovedSourceRetargeting",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLayoutImageEmptyNaturalSizeBeforeSizeAvailable,
    "LayoutImageEmptyNaturalSizeBeforeSizeAvailable",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kLinkBlurImprovement,
    "LinkBlurImprovement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kReduceUserAgentDataLinuxPlatformVersion,
    "ReduceUserAgentDataLinuxPlatformVersion",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgLengthListClearOnParsingFailure,
    "SvgLengthListClearOnParsingFailure",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgNumberListClearOnParsingFailure,
    "SvgNumberListClearOnParsingFailure",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgPartitionSVGDocumentResourcesInMemoryCache,
    "SvgPartitionSVGDocumentResourcesInMemoryCache",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kSvgTransformOnNestedSvgElement,
    "SvgTransformOnNestedSvgElement",
    base::FEATURE_DISABLED_BY_DEFAULT
);

BASE_FEATURE(kTextSpacingTrimYuGothicUI,
    "TextSpacingTrimYuGothicUI",
    base::FEATURE_DISABLED_BY_DEFAULT
);


}  // namespace features
}  // namespace blink
