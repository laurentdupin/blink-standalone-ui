// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/internal_runtime_flags.h.tmpl
// and input files:
//   ../../third_party/blink/renderer/platform/runtime_enabled_features.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_TESTING_INTERNAL_RUNTIME_FLAGS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_TESTING_INTERNAL_RUNTIME_FLAGS_H_

#include "third_party/blink/renderer/platform/bindings/script_wrappable.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "base/memory/scoped_refptr.h"
#include "third_party/blink/renderer/platform/wtf/ref_counted.h"

namespace blink {

class InternalRuntimeFlags : public ScriptWrappable {
  DEFINE_WRAPPERTYPEINFO();
 public:
  static InternalRuntimeFlags* create() {
    return MakeGarbageCollected<InternalRuntimeFlags>();
  }

  InternalRuntimeFlags() {}

  // These are reset between web tests from Internals::resetToConsistentState
  // using RuntimeEnabledFeatures::Backup.
  void setAccelerated2dCanvasEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetAccelerated2dCanvasEnabled(isEnabled);
  }
  void setAutomationControlledEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetAutomationControlledEnabled(isEnabled);
  }
  void setConnectionAllowlistEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetConnectionAllowlistEnabled(isEnabled);
  }
  void setEditContextHandleTextOrSelectionUpdateDuringCompositionEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetEditContextHandleTextOrSelectionUpdateDuringCompositionEnabled(isEnabled);
  }
  void setImplicitRootScrollerEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetImplicitRootScrollerEnabled(isEnabled);
  }
  void setLangAttributeAwareFormControlUIEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetLangAttributeAwareFormControlUIEnabled(isEnabled);
  }
  void setMediaControlsOverlayPlayButtonEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetMediaControlsOverlayPlayButtonEnabled(isEnabled);
  }
  void setPaintUnderInvalidationCheckingEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetPaintUnderInvalidationCheckingEnabled(isEnabled);
  }
  void setPreferNonCompositedScrollingEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetPreferNonCompositedScrollingEnabled(isEnabled);
  }
  void setRemotePlaybackBackendEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetRemotePlaybackBackendEnabled(isEnabled);
  }
  void setSelectionSetBaseAndExtentNonNullNodeEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetSelectionSetBaseAndExtentNonNullNodeEnabled(isEnabled);
  }
  void setVideoAutoFullscreenEnabled(bool isEnabled) {
    RuntimeEnabledFeatures::SetVideoAutoFullscreenEnabled(isEnabled);
  }

  bool aboutBlankPageRespectsDarkModeOnUserActionEnabled() {
    return RuntimeEnabledFeatures::AboutBlankPageRespectsDarkModeOnUserActionEnabled();
  }
  bool accelerated2dCanvasEnabled() {
    return RuntimeEnabledFeatures::Accelerated2dCanvasEnabled();
  }
  bool acceleratedSmallCanvasesEnabled() {
    return RuntimeEnabledFeatures::AcceleratedSmallCanvasesEnabled();
  }
  bool accessibilityAriaVirtualContentEnabled() {
    return RuntimeEnabledFeatures::AccessibilityAriaVirtualContentEnabled();
  }
  bool accessibilityCustomElementRoleNoneEnabled() {
    return RuntimeEnabledFeatures::AccessibilityCustomElementRoleNoneEnabled();
  }
  bool accessibilityExposeDisplayNoneEnabled() {
    return RuntimeEnabledFeatures::AccessibilityExposeDisplayNoneEnabled();
  }
  bool accessibilityImplicitActionsEnabled() {
    return RuntimeEnabledFeatures::AccessibilityImplicitActionsEnabled();
  }
  bool accessibilityMinRoleTabbableEnabled() {
    return RuntimeEnabledFeatures::AccessibilityMinRoleTabbableEnabled();
  }
  bool accessibilityOSLevelBoldTextEnabled() {
    return RuntimeEnabledFeatures::AccessibilityOSLevelBoldTextEnabled();
  }
  bool accessibilityProhibitedNamesEnabled() {
    return RuntimeEnabledFeatures::AccessibilityProhibitedNamesEnabled();
  }
  bool accessibilitySerializationSizeMetricsEnabled() {
    return RuntimeEnabledFeatures::AccessibilitySerializationSizeMetricsEnabled();
  }
  bool accessibilityUseAXPositionForDocumentMarkersEnabled() {
    return RuntimeEnabledFeatures::AccessibilityUseAXPositionForDocumentMarkersEnabled();
  }
  bool accessKeyLabelEnabled() {
    return RuntimeEnabledFeatures::AccessKeyLabelEnabled();
  }
  bool addressSpaceEnabled() {
    return RuntimeEnabledFeatures::AddressSpaceEnabled();
  }
  bool adInterestGroupAPIEnabled() {
    return RuntimeEnabledFeatures::AdInterestGroupAPIEnabledByRuntimeFlag();
  }
  bool adjustDOMOffsetToLayoutOffsetForSecureTextEnabled() {
    return RuntimeEnabledFeatures::AdjustDOMOffsetToLayoutOffsetForSecureTextEnabled();
  }
  bool adjustEndOfNextParagraphIfMovedParagraphIsUpdatedEnabled() {
    return RuntimeEnabledFeatures::AdjustEndOfNextParagraphIfMovedParagraphIsUpdatedEnabled();
  }
  bool adTaggingEnabled() {
    return RuntimeEnabledFeatures::AdTaggingEnabled();
  }
  bool aiClassifierAPIEnabled() {
    return RuntimeEnabledFeatures::AIClassifierAPIEnabled();
  }
  bool aiPageContentAnchoredOffscreenNonActionabilityEnabled() {
    return RuntimeEnabledFeatures::AIPageContentAnchoredOffscreenNonActionabilityEnabled();
  }
  bool aiPageContentBuildOnLoadForTestingEnabled() {
    return RuntimeEnabledFeatures::AIPageContentBuildOnLoadForTestingEnabled();
  }
  bool aiPageContentCheckGeometryEnabled() {
    return RuntimeEnabledFeatures::AIPageContentCheckGeometryEnabled();
  }
  bool aiPageContentConvertNodeTextToUtf8Enabled() {
    return RuntimeEnabledFeatures::AIPageContentConvertNodeTextToUtf8Enabled();
  }
  bool aiPageContentElementCSSRedactionEnabled() {
    return RuntimeEnabledFeatures::AIPageContentElementCSSRedactionEnabled();
  }
  bool aiPageContentIncludeSVGSubtreeEnabled() {
    return RuntimeEnabledFeatures::AIPageContentIncludeSVGSubtreeEnabled();
  }
  bool aiPageContentOuterBoxMapToAncestorSpaceEnabled() {
    return RuntimeEnabledFeatures::AIPageContentOuterBoxMapToAncestorSpaceEnabled();
  }
  bool aiPageContentPaidContentAnnotationEnabled() {
    return RuntimeEnabledFeatures::AIPageContentPaidContentAnnotationEnabled();
  }
  bool aiPageContentVisualViewportClampEnabled() {
    return RuntimeEnabledFeatures::AIPageContentVisualViewportClampEnabled();
  }
  bool aiPromptAPIEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIEnabled();
  }
  bool aiPromptAPIForExtensionEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIForExtensionEnabled();
  }
  bool aiPromptAPIForWorkersEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIForWorkersEnabled();
  }
  bool aiPromptAPILegacyIdentifiersEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPILegacyIdentifiersEnabled();
  }
  bool aiPromptAPILegacyParamsEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPILegacyParamsEnabledByRuntimeFlag();
  }
  bool aiPromptAPIMultimodalInputEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIMultimodalInputEnabled();
  }
  bool aiPromptAPIParamsEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIParamsEnabledByRuntimeFlag();
  }
  bool aiPromptAPIStructuredOutputEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIStructuredOutputEnabled();
  }
  bool aiPromptAPIToolUseEnabled() {
    return RuntimeEnabledFeatures::AIPromptAPIToolUseEnabled();
  }
  bool aiProofreadingAPIEnabled() {
    return RuntimeEnabledFeatures::AIProofreadingAPIEnabledByRuntimeFlag();
  }
  bool aiRewriterAPIEnabled() {
    return RuntimeEnabledFeatures::AIRewriterAPIEnabledByRuntimeFlag();
  }
  bool aiRewriterAPIForWorkersEnabled() {
    return RuntimeEnabledFeatures::AIRewriterAPIForWorkersEnabled();
  }
  bool aiSummarizationAPIEnabled() {
    return RuntimeEnabledFeatures::AISummarizationAPIEnabled();
  }
  bool aiSummarizationAPIForWorkersEnabled() {
    return RuntimeEnabledFeatures::AISummarizationAPIForWorkersEnabled();
  }
  bool aiSummarizationPerformancePreferenceEnabled() {
    return RuntimeEnabledFeatures::AISummarizationPerformancePreferenceEnabled();
  }
  bool aiWriterAPIEnabled() {
    return RuntimeEnabledFeatures::AIWriterAPIEnabledByRuntimeFlag();
  }
  bool aiWriterAPIForWorkersEnabled() {
    return RuntimeEnabledFeatures::AIWriterAPIForWorkersEnabled();
  }
  bool alignZoomToCenterEnabled() {
    return RuntimeEnabledFeatures::AlignZoomToCenterEnabled();
  }
  bool allImagesPaintedSentToElementTimingEnabled() {
    return RuntimeEnabledFeatures::AllImagesPaintedSentToElementTimingEnabled();
  }
  bool allowContentInitiatedDataUrlNavigationsEnabled() {
    return RuntimeEnabledFeatures::AllowContentInitiatedDataUrlNavigationsEnabled();
  }
  bool allowPreloadingWithCSPMetaTagEnabled() {
    return RuntimeEnabledFeatures::AllowPreloadingWithCSPMetaTagEnabled();
  }
  bool allowSameSiteNoneCookiesInSandboxEnabled() {
    return RuntimeEnabledFeatures::AllowSameSiteNoneCookiesInSandboxEnabled();
  }
  bool allowSkippingEditingBoundaryToMergeEndEnabled() {
    return RuntimeEnabledFeatures::AllowSkippingEditingBoundaryToMergeEndEnabled();
  }
  bool allowSvgUseToReferenceExternalDocumentRootEnabled() {
    return RuntimeEnabledFeatures::AllowSvgUseToReferenceExternalDocumentRootEnabled();
  }
  bool allowSyntheticTimingForCanvasCaptureEnabled() {
    return RuntimeEnabledFeatures::AllowSyntheticTimingForCanvasCaptureEnabled();
  }
  bool allowURNsInIframesEnabled() {
    return RuntimeEnabledFeatures::AllowURNsInIframesEnabled();
  }
  bool ancestorOriginsStoredOnDocumentEnabled() {
    return RuntimeEnabledFeatures::AncestorOriginsStoredOnDocumentEnabled();
  }
  bool ancestorRevealingNewSpecEnabled() {
    return RuntimeEnabledFeatures::AncestorRevealingNewSpecEnabled();
  }
  bool anchorFocusRingFixEnabled() {
    return RuntimeEnabledFeatures::AnchorFocusRingFixEnabled();
  }
  bool anchorPositionAdjustmentWithoutOverflowEnabled() {
    return RuntimeEnabledFeatures::AnchorPositionAdjustmentWithoutOverflowEnabled();
  }
  bool androidDownloadableFontsMatchingEnabled() {
    return RuntimeEnabledFeatures::AndroidDownloadableFontsMatchingEnabled();
  }
  bool animationProgressAPIEnabled() {
    return RuntimeEnabledFeatures::AnimationProgressAPIEnabled();
  }
  bool animationTriggerEnabled() {
    return RuntimeEnabledFeatures::AnimationTriggerEnabled();
  }
  bool animationWorkletEnabled() {
    return RuntimeEnabledFeatures::AnimationWorkletEnabled();
  }
  bool anonymousIframeEnabled() {
    return RuntimeEnabledFeatures::AnonymousIframeEnabled();
  }
  bool aomAriaRelationshipPropertiesEnabled() {
    return RuntimeEnabledFeatures::AOMAriaRelationshipPropertiesEnabled();
  }
  bool aomAriaRelationshipPropertiesAriaOwnsEnabled() {
    return RuntimeEnabledFeatures::AOMAriaRelationshipPropertiesAriaOwnsEnabled();
  }
  bool appearanceBaseEnabled() {
    return RuntimeEnabledFeatures::AppearanceBaseEnabled();
  }
  bool approximateGeolocationPermissionEnabled() {
    return RuntimeEnabledFeatures::ApproximateGeolocationPermissionEnabled();
  }
  bool approximateGeolocationPermissionAPIEnabled() {
    return RuntimeEnabledFeatures::ApproximateGeolocationPermissionAPIEnabled();
  }
  bool approximateGeolocationWebVisibleAPIEnabled() {
    return RuntimeEnabledFeatures::ApproximateGeolocationWebVisibleAPIEnabled();
  }
  bool appTitleEnabled() {
    return RuntimeEnabledFeatures::AppTitleEnabledByRuntimeFlag();
  }
  bool ariaActionsEnabled() {
    return RuntimeEnabledFeatures::AriaActionsEnabled();
  }
  bool ariaNotifyEnabled() {
    return RuntimeEnabledFeatures::AriaNotifyEnabled();
  }
  bool ariaNotifyV2Enabled() {
    return RuntimeEnabledFeatures::AriaNotifyV2Enabled();
  }
  bool ariaRowColIndexTextEnabled() {
    return RuntimeEnabledFeatures::AriaRowColIndexTextEnabled();
  }
  bool asyncSetCookieEnabled() {
    return RuntimeEnabledFeatures::AsyncSetCookieEnabled();
  }
  bool attributionReportingEnabled() {
    return RuntimeEnabledFeatures::AttributionReportingEnabled();
  }
  bool audioContextAsyncStateTransitionsEnabled() {
    return RuntimeEnabledFeatures::AudioContextAsyncStateTransitionsEnabled();
  }
  bool audioContextPlaybackStatsEnabled() {
    return RuntimeEnabledFeatures::AudioContextPlaybackStatsEnabled();
  }
  bool audioContextPlayoutStatsEnabled() {
    return RuntimeEnabledFeatures::AudioContextPlayoutStatsEnabledByRuntimeFlag();
  }
  bool audioContextSetSinkIdEnabled() {
    return RuntimeEnabledFeatures::AudioContextSetSinkIdEnabled();
  }
  bool audioOutputDevicesEnabled() {
    return RuntimeEnabledFeatures::AudioOutputDevicesEnabled();
  }
  bool audioVideoTracksEnabled() {
    return RuntimeEnabledFeatures::AudioVideoTracksEnabled();
  }
  bool authenticatorPasswordsOnlyImmediateRequestsEnabled() {
    return RuntimeEnabledFeatures::AuthenticatorPasswordsOnlyImmediateRequestsEnabled();
  }
  bool authorSpecifiedLayoutScrollSnapBehaviorEnabled() {
    return RuntimeEnabledFeatures::AuthorSpecifiedLayoutScrollSnapBehaviorEnabled();
  }
  bool autoDarkModeEnabled() {
    return RuntimeEnabledFeatures::AutoDarkModeEnabledByRuntimeFlag();
  }
  bool autofillEnabled() {
    return RuntimeEnabledFeatures::AutofillEnabled();
  }
  bool autofillEventEnabled() {
    return RuntimeEnabledFeatures::AutofillEventEnabledByRuntimeFlag();
  }
  bool automationControlledEnabled() {
    return RuntimeEnabledFeatures::AutomationControlledEnabled();
  }
  bool autoPictureInPictureVideoHeuristicsEnabled() {
    return RuntimeEnabledFeatures::AutoPictureInPictureVideoHeuristicsEnabled();
  }
  bool avoidForcedLayoutOnInvisibleDocumentCloseEnabled() {
    return RuntimeEnabledFeatures::AvoidForcedLayoutOnInvisibleDocumentCloseEnabled();
  }
  bool avoidMergingStyledSpanWithSiblingsEnabled() {
    return RuntimeEnabledFeatures::AvoidMergingStyledSpanWithSiblingsEnabled();
  }
  bool avoidNormalizingVisiblePositionsWhenStartEqualsEndEnabled() {
    return RuntimeEnabledFeatures::AvoidNormalizingVisiblePositionsWhenStartEqualsEndEnabled();
  }
  bool backfaceVisibilityInteropEnabled() {
    return RuntimeEnabledFeatures::BackfaceVisibilityInteropEnabled();
  }
  bool backForwardCacheEnabled() {
    return RuntimeEnabledFeatures::BackForwardCacheEnabled();
  }
  bool backForwardCacheExperimentHTTPHeaderEnabled() {
    return RuntimeEnabledFeatures::BackForwardCacheExperimentHTTPHeaderEnabledByRuntimeFlag();
  }
  bool backForwardCacheNotRestoredReasonsEnabled() {
    return RuntimeEnabledFeatures::BackForwardCacheNotRestoredReasonsEnabledByRuntimeFlag();
  }
  bool backForwardCacheRestorationPerformanceEntryEnabled() {
    return RuntimeEnabledFeatures::BackForwardCacheRestorationPerformanceEntryEnabled();
  }
  bool backForwardCacheUpdateNotRestoredReasonsNameEnabled() {
    return RuntimeEnabledFeatures::BackForwardCacheUpdateNotRestoredReasonsNameEnabled();
  }
  bool backgroundClipTextDecorationEnabled() {
    return RuntimeEnabledFeatures::BackgroundClipTextDecorationEnabled();
  }
  bool backgroundFetchEnabled() {
    return RuntimeEnabledFeatures::BackgroundFetchEnabled();
  }
  bool backgroundPageFreezeOptOutEnabled() {
    return RuntimeEnabledFeatures::BackgroundPageFreezeOptOutEnabledByRuntimeFlag();
  }
  bool barcodeDetectorEnabled() {
    return RuntimeEnabledFeatures::BarcodeDetectorEnabled();
  }
  bool baseAppearanceInlineSizingEnabled() {
    return RuntimeEnabledFeatures::BaseAppearanceInlineSizingEnabled();
  }
  bool bidiCaretAffinityEnabled() {
    return RuntimeEnabledFeatures::BidiCaretAffinityEnabled();
  }
  bool blinkExtensionChromeOSEnabled() {
    return RuntimeEnabledFeatures::BlinkExtensionChromeOSEnabled();
  }
  bool blinkExtensionChromeOSIsolatedWebAppSetShapeEnabled() {
    return RuntimeEnabledFeatures::BlinkExtensionChromeOSIsolatedWebAppSetShapeEnabled();
  }
  bool blinkExtensionChromeOSKioskEnabled() {
    return RuntimeEnabledFeatures::BlinkExtensionChromeOSKioskEnabled();
  }
  bool blinkExtensionWebViewEnabled() {
    return RuntimeEnabledFeatures::BlinkExtensionWebViewEnabled();
  }
  bool blinkExtensionWebViewMediaIntegrityEnabled() {
    return RuntimeEnabledFeatures::BlinkExtensionWebViewMediaIntegrityEnabled();
  }
  bool blinkGeometryMapperViewportFastPathEnabled() {
    return RuntimeEnabledFeatures::BlinkGeometryMapperViewportFastPathEnabled();
  }
  bool blinkLifecycleScriptForbiddenEnabled() {
    return RuntimeEnabledFeatures::BlinkLifecycleScriptForbiddenEnabled();
  }
  bool blinkRuntimeCallStatsEnabled() {
    return RuntimeEnabledFeatures::BlinkRuntimeCallStatsEnabled();
  }
  bool blobBytesEnabled() {
    return RuntimeEnabledFeatures::BlobBytesEnabled();
  }
  bool blockingFocusWithoutUserActivationEnabled() {
    return RuntimeEnabledFeatures::BlockingFocusWithoutUserActivationEnabledByRuntimeFlag();
  }
  bool blockSelectPopupUnfocusedWindowEnabled() {
    return RuntimeEnabledFeatures::BlockSelectPopupUnfocusedWindowEnabled();
  }
  bool boundaryEventDispatchTracksNodeRemovalEnabled() {
    return RuntimeEnabledFeatures::BoundaryEventDispatchTracksNodeRemovalEnabled();
  }
  bool browserInitiatedAutomaticPictureInPictureEnabled() {
    return RuntimeEnabledFeatures::BrowserInitiatedAutomaticPictureInPictureEnabled();
  }
  bool browserVerifiedUserActivationKeyboardEnabled() {
    return RuntimeEnabledFeatures::BrowserVerifiedUserActivationKeyboardEnabled();
  }
  bool browserVerifiedUserActivationMouseEnabled() {
    return RuntimeEnabledFeatures::BrowserVerifiedUserActivationMouseEnabled();
  }
  bool bufferedBytesConsumerLimitSizeEnabled() {
    return RuntimeEnabledFeatures::BufferedBytesConsumerLimitSizeEnabled();
  }
  bool bypassPepcSecurityForTestingEnabled() {
    return RuntimeEnabledFeatures::BypassPepcSecurityForTestingEnabled();
  }
  bool cacheControlRFC7234ParsingEnabled() {
    return RuntimeEnabledFeatures::CacheControlRFC7234ParsingEnabled();
  }
  bool cacheControlRFC7234ParsingMetricsEnabled() {
    return RuntimeEnabledFeatures::CacheControlRFC7234ParsingMetricsEnabled();
  }
  bool cacheStorageCodeCacheHintEnabled() {
    return RuntimeEnabledFeatures::CacheStorageCodeCacheHintEnabledByRuntimeFlag();
  }
  bool cacheStyleAdjusterEnabled() {
    return RuntimeEnabledFeatures::CacheStyleAdjusterEnabled();
  }
  bool callExitNodeWithoutLayoutObjectEnabled() {
    return RuntimeEnabledFeatures::CallExitNodeWithoutLayoutObjectEnabled();
  }
  bool canvas2dCanvasFilterEnabled() {
    return RuntimeEnabledFeatures::Canvas2dCanvasFilterEnabled();
  }
  bool canvas2dGPUTransferEnabled() {
    return RuntimeEnabledFeatures::Canvas2dGPUTransferEnabled();
  }
  bool canvas2dLayersEnabled() {
    return RuntimeEnabledFeatures::Canvas2dLayersEnabled();
  }
  bool canvas2dLayersWithOptionsEnabled() {
    return RuntimeEnabledFeatures::Canvas2dLayersWithOptionsEnabled();
  }
  bool canvas2dMeshEnabled() {
    return RuntimeEnabledFeatures::Canvas2dMeshEnabledByRuntimeFlag();
  }
  bool canvasDrawElementEnabled() {
    return RuntimeEnabledFeatures::CanvasDrawElementEnabledByRuntimeFlag();
  }
  bool canvasFloatingPointEnabled() {
    return RuntimeEnabledFeatures::CanvasFloatingPointEnabled();
  }
  bool canvasGlobalHDRHeadroomEnabled() {
    return RuntimeEnabledFeatures::CanvasGlobalHDRHeadroomEnabled();
  }
  bool canvasGradientCSSColor4Enabled() {
    return RuntimeEnabledFeatures::CanvasGradientCSSColor4Enabled();
  }
  bool canvasHDREnabled() {
    return RuntimeEnabledFeatures::CanvasHDREnabled();
  }
  bool canvasTextMetricsPreciseBoundsEnabled() {
    return RuntimeEnabledFeatures::CanvasTextMetricsPreciseBoundsEnabled();
  }
  bool canvasToneMappingEnabled() {
    return RuntimeEnabledFeatures::CanvasToneMappingEnabled();
  }
  bool canvasUsesArcPaintOpEnabled() {
    return RuntimeEnabledFeatures::CanvasUsesArcPaintOpEnabled();
  }
  bool capabilityDelegationDisplayCaptureRequestEnabled() {
    return RuntimeEnabledFeatures::CapabilityDelegationDisplayCaptureRequestEnabled();
  }
  bool captureControllerEnabled() {
    return RuntimeEnabledFeatures::CaptureControllerEnabled();
  }
  bool capturedMouseEventsEnabled() {
    return RuntimeEnabledFeatures::CapturedMouseEventsEnabled();
  }
  bool capturedSurfaceControlEnabled() {
    return RuntimeEnabledFeatures::CapturedSurfaceControlEnabled();
  }
  bool capturedSurfaceResolutionEnabled() {
    return RuntimeEnabledFeatures::CapturedSurfaceResolutionEnabled();
  }
  bool captureHandleEnabled() {
    return RuntimeEnabledFeatures::CaptureHandleEnabled();
  }
  bool caretWithTextAffinityUpstreamEnabled() {
    return RuntimeEnabledFeatures::CaretWithTextAffinityUpstreamEnabled();
  }
  bool cctNewRFMPushBehaviorEnabled() {
    return RuntimeEnabledFeatures::CCTNewRFMPushBehaviorEnabled();
  }
  bool checkableInputTypeLayoutInlineEnabled() {
    return RuntimeEnabledFeatures::CheckableInputTypeLayoutInlineEnabled();
  }
  bool checkForCanonicalPositionInIdleSpellCheckEnabled() {
    return RuntimeEnabledFeatures::CheckForCanonicalPositionInIdleSpellCheckEnabled();
  }
  bool checkVisibilityExtraPropertiesEnabled() {
    return RuntimeEnabledFeatures::CheckVisibilityExtraPropertiesEnabled();
  }
  bool clampWordBoundaryToContentEditableScopeEnabled() {
    return RuntimeEnabledFeatures::ClampWordBoundaryToContentEditableScopeEnabled();
  }
  bool clearCurrentTargetAfterDispatchEnabled() {
    return RuntimeEnabledFeatures::ClearCurrentTargetAfterDispatchEnabled();
  }
  bool clearFocusWithinOnSubtreeRemovalEnabled() {
    return RuntimeEnabledFeatures::ClearFocusWithinOnSubtreeRemovalEnabled();
  }
  bool clearTargetOnlyIfInShadowTreeEnabled() {
    return RuntimeEnabledFeatures::ClearTargetOnlyIfInShadowTreeEnabled();
  }
  bool clickFocusDoesntPersistStatusBubbleEnabled() {
    return RuntimeEnabledFeatures::ClickFocusDoesntPersistStatusBubbleEnabled();
  }
  bool clipboardEventTargetCanBeFocusedElementEnabled() {
    return RuntimeEnabledFeatures::ClipboardEventTargetCanBeFocusedElementEnabled();
  }
  bool clipboardEventTargetUsesContainerNodeEnabled() {
    return RuntimeEnabledFeatures::ClipboardEventTargetUsesContainerNodeEnabled();
  }
  bool clipboardItemWithDOMStringSupportEnabled() {
    return RuntimeEnabledFeatures::ClipboardItemWithDOMStringSupportEnabled();
  }
  bool clipElementVisibleBoundsInLocalRootEnabled() {
    return RuntimeEnabledFeatures::ClipElementVisibleBoundsInLocalRootEnabled();
  }
  bool clipPathNestedRasterOptimizationEnabled() {
    return RuntimeEnabledFeatures::ClipPathNestedRasterOptimizationEnabled();
  }
  bool coalesceSelectionchangeEventEnabled() {
    return RuntimeEnabledFeatures::CoalesceSelectionchangeEventEnabled();
  }
  bool coepReflectionEnabled() {
    return RuntimeEnabledFeatures::CoepReflectionEnabled();
  }
  bool collapseZeroWidthSpaceWhenReuseItemEnabled() {
    return RuntimeEnabledFeatures::CollapseZeroWidthSpaceWhenReuseItemEnabled();
  }
  bool colorInputAcceptsCSSColorsEnabled() {
    return RuntimeEnabledFeatures::ColorInputAcceptsCSSColorsEnabled();
  }
  bool colorSpaceDisplayP3LinearEnabled() {
    return RuntimeEnabledFeatures::ColorSpaceDisplayP3LinearEnabled();
  }
  bool colorSpacePredefinedLinearSpacesEnabled() {
    return RuntimeEnabledFeatures::ColorSpacePredefinedLinearSpacesEnabled();
  }
  bool colorSpaceRec2100LinearEnabled() {
    return RuntimeEnabledFeatures::ColorSpaceRec2100LinearEnabled();
  }
  bool commandEventNotComposedEnabled() {
    return RuntimeEnabledFeatures::CommandEventNotComposedEnabled();
  }
  bool commaSeparatedContainerQueriesEnabled() {
    return RuntimeEnabledFeatures::CommaSeparatedContainerQueriesEnabled();
  }
  bool composedPathReturnTargetBeingDispatchedEnabled() {
    return RuntimeEnabledFeatures::ComposedPathReturnTargetBeingDispatchedEnabled();
  }
  bool compositeBGColorAnimationEnabled() {
    return RuntimeEnabledFeatures::CompositeBGColorAnimationEnabled();
  }
  bool compositeBoxShadowAnimationEnabled() {
    return RuntimeEnabledFeatures::CompositeBoxShadowAnimationEnabled();
  }
  bool compositeClipPathAnimationEnabled() {
    return RuntimeEnabledFeatures::CompositeClipPathAnimationEnabled();
  }
  bool compositedAnimationsCancelledAsynchronouslyEnabled() {
    return RuntimeEnabledFeatures::CompositedAnimationsCancelledAsynchronouslyEnabled();
  }
  bool compositedSelectionUpdateEnabled() {
    return RuntimeEnabledFeatures::CompositedSelectionUpdateEnabled();
  }
  bool compositingDecisionAtAnimationPhaseBoundariesEnabled() {
    return RuntimeEnabledFeatures::CompositingDecisionAtAnimationPhaseBoundariesEnabled();
  }
  bool compositionForegroundMarkersEnabled() {
    return RuntimeEnabledFeatures::CompositionForegroundMarkersEnabled();
  }
  bool compositorEventTriggerEnabled() {
    return RuntimeEnabledFeatures::CompositorEventTriggerEnabled();
  }
  bool compositorTimelineTriggerEnabled() {
    return RuntimeEnabledFeatures::CompositorTimelineTriggerEnabled();
  }
  bool compressionDictionaryTransportEnabled() {
    return RuntimeEnabledFeatures::CompressionDictionaryTransportEnabled();
  }
  bool computedAccessibilityInfoEnabled() {
    return RuntimeEnabledFeatures::ComputedAccessibilityInfoEnabled();
  }
  bool computeInlineContentsSafeRetargetEnabled() {
    return RuntimeEnabledFeatures::ComputeInlineContentsSafeRetargetEnabled();
  }
  bool computePressureEnabled() {
    return RuntimeEnabledFeatures::ComputePressureEnabled();
  }
  bool computePressureOwnContributionEstimateEnabled() {
    return RuntimeEnabledFeatures::ComputePressureOwnContributionEstimateEnabled();
  }
  bool connectionAllowlistEnabled() {
    return RuntimeEnabledFeatures::ConnectionAllowlistEnabledByRuntimeFlag();
  }
  bool considerSubOrSuperScriptAncestorAlignForCaretSelectionEnabled() {
    return RuntimeEnabledFeatures::ConsiderSubOrSuperScriptAncestorAlignForCaretSelectionEnabled();
  }
  bool contactsManagerEnabled() {
    return RuntimeEnabledFeatures::ContactsManagerEnabled();
  }
  bool contactsManagerExtraPropertiesEnabled() {
    return RuntimeEnabledFeatures::ContactsManagerExtraPropertiesEnabled();
  }
  bool containerNameOnlyEnabled() {
    return RuntimeEnabledFeatures::ContainerNameOnlyEnabled();
  }
  bool containerTimingEnabled() {
    return RuntimeEnabledFeatures::ContainerTimingEnabledByRuntimeFlag();
  }
  bool contentIndexEnabled() {
    return RuntimeEnabledFeatures::ContentIndexEnabled();
  }
  bool contextMenuEnabled() {
    return RuntimeEnabledFeatures::ContextMenuEnabled();
  }
  bool controlledFrameEnabled() {
    return RuntimeEnabledFeatures::ControlledFrameEnabled();
  }
  bool controlledFrameWebRequestSecurityInfoEnabled() {
    return RuntimeEnabledFeatures::ControlledFrameWebRequestSecurityInfoEnabled();
  }
  bool cookieStoreAPIMaxAgeEnabled() {
    return RuntimeEnabledFeatures::CookieStoreAPIMaxAgeEnabled();
  }
  bool cookieStoreAPIWhitespaceStrippingEnabled() {
    return RuntimeEnabledFeatures::CookieStoreAPIWhitespaceStrippingEnabled();
  }
  bool coopRestrictPropertiesEnabled() {
    return RuntimeEnabledFeatures::CoopRestrictPropertiesEnabledByRuntimeFlag();
  }
  bool correctTemplateFormParsingEnabled() {
    return RuntimeEnabledFeatures::CorrectTemplateFormParsingEnabled();
  }
  bool corsRFC1918Enabled() {
    return RuntimeEnabledFeatures::CorsRFC1918Enabled();
  }
  bool cpuPerformanceEnabled() {
    return RuntimeEnabledFeatures::CpuPerformanceEnabledByRuntimeFlag();
  }
  bool crashReportingStorageAPIEnabled() {
    return RuntimeEnabledFeatures::CrashReportingStorageAPIEnabledByRuntimeFlag();
  }
  bool createInlineContentsExcludeOutOfFlowEnabled() {
    return RuntimeEnabledFeatures::CreateInlineContentsExcludeOutOfFlowEnabled();
  }
  bool cspHashesV1Enabled() {
    return RuntimeEnabledFeatures::CSPHashesV1EnabledByRuntimeFlag();
  }
  bool cspReportHashEnabled() {
    return RuntimeEnabledFeatures::CSPReportHashEnabled();
  }
  bool cssAccentColorKeywordEnabled() {
    return RuntimeEnabledFeatures::CSSAccentColorKeywordEnabled();
  }
  bool cssActiveCaptionMapsToCanvasEnabled() {
    return RuntimeEnabledFeatures::CSSActiveCaptionMapsToCanvasEnabled();
  }
  bool cssAlphaColorFunctionEnabled() {
    return RuntimeEnabledFeatures::CSSAlphaColorFunctionEnabled();
  }
  bool cssAltCounterEnabled() {
    return RuntimeEnabledFeatures::CSSAltCounterEnabled();
  }
  bool cssAnchorWithTransformsEnabled() {
    return RuntimeEnabledFeatures::CSSAnchorWithTransformsEnabled();
  }
  bool cssAnimationIterationCompositeEnabled() {
    return RuntimeEnabledFeatures::CSSAnimationIterationCompositeEnabled();
  }
  bool cssArgumentGrammarEnabled() {
    return RuntimeEnabledFeatures::CSSArgumentGrammarEnabled();
  }
  bool cssAtRuleCounterStyleImageSymbolsEnabled() {
    return RuntimeEnabledFeatures::CSSAtRuleCounterStyleImageSymbolsEnabled();
  }
  bool cssAtRuleCounterStyleSpeakAsDescriptorEnabled() {
    return RuntimeEnabledFeatures::CSSAtRuleCounterStyleSpeakAsDescriptorEnabled();
  }
  bool cssBackgroundClipBorderAreaEnabled() {
    return RuntimeEnabledFeatures::CSSBackgroundClipBorderAreaEnabled();
  }
  bool cssBorderShapeEnabled() {
    return RuntimeEnabledFeatures::CSSBorderShapeEnabled();
  }
  bool cssCalcSimplificationAndSerializationEnabled() {
    return RuntimeEnabledFeatures::CSSCalcSimplificationAndSerializationEnabled();
  }
  bool cssCaretAnimationEnabled() {
    return RuntimeEnabledFeatures::CSSCaretAnimationEnabled();
  }
  bool cssCaretShapeEnabled() {
    return RuntimeEnabledFeatures::CSSCaretShapeEnabled();
  }
  bool cssCaseSensitiveSelectorEnabled() {
    return RuntimeEnabledFeatures::CSSCaseSensitiveSelectorEnabled();
  }
  bool cssChUnitSpecCompliantFallbackEnabled() {
    return RuntimeEnabledFeatures::CSSChUnitSpecCompliantFallbackEnabled();
  }
  bool cssColorTypedOMEnabled() {
    return RuntimeEnabledFeatures::CSSColorTypedOMEnabled();
  }
  bool cssContainerProgressNotationEnabled() {
    return RuntimeEnabledFeatures::CSSContainerProgressNotationEnabled();
  }
  bool cssContainerStyleQueriesRangeEnabled() {
    return RuntimeEnabledFeatures::CSSContainerStyleQueriesRangeEnabled();
  }
  bool cssContrastColorEnabled() {
    return RuntimeEnabledFeatures::CSSContrastColorEnabled();
  }
  bool cssCornersShorthandEnabled() {
    return RuntimeEnabledFeatures::CSSCornersShorthandEnabled();
  }
  bool cssCounterResetReversedEnabled() {
    return RuntimeEnabledFeatures::CSSCounterResetReversedEnabled();
  }
  bool cssCrossFadeEnabled() {
    return RuntimeEnabledFeatures::CSSCrossFadeEnabled();
  }
  bool cssCustomMediaEnabled() {
    return RuntimeEnabledFeatures::CSSCustomMediaEnabled();
  }
  bool cssDynamicRangeLimitEnabled() {
    return RuntimeEnabledFeatures::CSSDynamicRangeLimitEnabled();
  }
  bool cssEnumeratedCustomPropertiesEnabled() {
    return RuntimeEnabledFeatures::CSSEnumeratedCustomPropertiesEnabled();
  }
  bool cssFontFamilySerializationEnabled() {
    return RuntimeEnabledFeatures::CSSFontFamilySerializationEnabled();
  }
  bool cssFontSizeAdjustEnabled() {
    return RuntimeEnabledFeatures::CSSFontSizeAdjustEnabled();
  }
  bool cssFunctionsEnabled() {
    return RuntimeEnabledFeatures::CSSFunctionsEnabled();
  }
  bool cssGapDecorationEnabled() {
    return RuntimeEnabledFeatures::CSSGapDecorationEnabled();
  }
  bool cssGridGapSuppressionEnabled() {
    return RuntimeEnabledFeatures::CSSGridGapSuppressionEnabled();
  }
  bool cssGridLanesLayoutEnabled() {
    return RuntimeEnabledFeatures::CSSGridLanesLayoutEnabled();
  }
  bool cssHangingPunctuationEnabled() {
    return RuntimeEnabledFeatures::CSSHangingPunctuationEnabled();
  }
  bool cssHexAlphaColorEnabled() {
    return RuntimeEnabledFeatures::CSSHexAlphaColorEnabled();
  }
  bool cssIdentFunctionEnabled() {
    return RuntimeEnabledFeatures::CSSIdentFunctionEnabled();
  }
  bool cssImageAnimationEnabled() {
    return RuntimeEnabledFeatures::CSSImageAnimationEnabled();
  }
  bool cssInheritFunctionEnabled() {
    return RuntimeEnabledFeatures::CSSInheritFunctionEnabled();
  }
  bool cssKeyframesRuleLengthEnabled() {
    return RuntimeEnabledFeatures::CSSKeyframesRuleLengthEnabled();
  }
  bool cssLangExtendedRangesEnabled() {
    return RuntimeEnabledFeatures::CSSLangExtendedRangesEnabled();
  }
  bool cssLayoutAPIEnabled() {
    return RuntimeEnabledFeatures::CSSLayoutAPIEnabled();
  }
  bool cssLetterAndWordSpacingPercentageEnabled() {
    return RuntimeEnabledFeatures::CSSLetterAndWordSpacingPercentageEnabled();
  }
  bool cssLightDarkImageEnabled() {
    return RuntimeEnabledFeatures::CSSLightDarkImageEnabled();
  }
  bool cssLineClampEnabled() {
    return RuntimeEnabledFeatures::CSSLineClampEnabled();
  }
  bool cssLineClampLineBreakingEllipsisEnabled() {
    return RuntimeEnabledFeatures::CSSLineClampLineBreakingEllipsisEnabled();
  }
  bool cssLineClampLinesAndHeightEnabled() {
    return RuntimeEnabledFeatures::CSSLineClampLinesAndHeightEnabled();
  }
  bool cssListCounterAccountingEnabled() {
    return RuntimeEnabledFeatures::CSSListCounterAccountingEnabled();
  }
  bool cssLogicalCombinationPseudoEnabled() {
    return RuntimeEnabledFeatures::CSSLogicalCombinationPseudoEnabled();
  }
  bool cssMarkerNestedPseudoElementEnabled() {
    return RuntimeEnabledFeatures::CSSMarkerNestedPseudoElementEnabled();
  }
  bool cssMediaProgressNotationEnabled() {
    return RuntimeEnabledFeatures::CSSMediaProgressNotationEnabled();
  }
  bool cssMixinsEnabled() {
    return RuntimeEnabledFeatures::CSSMixinsEnabled();
  }
  bool cssNestedPseudoElementsEnabled() {
    return RuntimeEnabledFeatures::CSSNestedPseudoElementsEnabled();
  }
  bool cssomGetComputedStylePseudoElementRequiresColonEnabled() {
    return RuntimeEnabledFeatures::CSSOMGetComputedStylePseudoElementRequiresColonEnabled();
  }
  bool cssOverscrollBehaviorChainEnabled() {
    return RuntimeEnabledFeatures::CSSOverscrollBehaviorChainEnabled();
  }
  bool cssPaintAPIArgumentsEnabled() {
    return RuntimeEnabledFeatures::CSSPaintAPIArgumentsEnabled();
  }
  bool cssParserIgnoreCharsetForURLsEnabled() {
    return RuntimeEnabledFeatures::CSSParserIgnoreCharsetForURLsEnabled();
  }
  bool cssPolygonRoundingEnabled() {
    return RuntimeEnabledFeatures::CSSPolygonRoundingEnabled();
  }
  bool cssPositionStickyStaticScrollPositionEnabled() {
    return RuntimeEnabledFeatures::CSSPositionStickyStaticScrollPositionEnabled();
  }
  bool cssProgressNotationEnabled() {
    return RuntimeEnabledFeatures::CSSProgressNotationEnabled();
  }
  bool cssPseudoColumnEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoColumnEnabled();
  }
  bool cssPseudoElementBackdropEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoElementBackdropEnabled();
  }
  bool cssPseudoElementInterfaceEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoElementInterfaceEnabled();
  }
  bool cssPseudoElementViewTransitionsEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoElementViewTransitionsEnabled();
  }
  bool cssPseudoHasSlottedEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoHasSlottedEnabled();
  }
  bool cssPseudoPlayingPausedEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoPlayingPausedEnabled();
  }
  bool cssPseudoScrollButtonsEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoScrollButtonsEnabled();
  }
  bool cssPseudoScrollMarkersEnabled() {
    return RuntimeEnabledFeatures::CSSPseudoScrollMarkersEnabled();
  }
  bool cssRandomFunctionEnabled() {
    return RuntimeEnabledFeatures::CSSRandomFunctionEnabled();
  }
  bool cssRandomFunctionTypedOMEnabled() {
    return RuntimeEnabledFeatures::CSSRandomFunctionTypedOMEnabled();
  }
  bool cssResizeAutoEnabled() {
    return RuntimeEnabledFeatures::CSSResizeAutoEnabled();
  }
  bool cssResourceIntegrityEnforcementEnabled() {
    return RuntimeEnabledFeatures::CSSResourceIntegrityEnforcementEnabled();
  }
  bool cssRevertRuleEnabled() {
    return RuntimeEnabledFeatures::CSSRevertRuleEnabled();
  }
  bool cssRubyOverhangEnabled() {
    return RuntimeEnabledFeatures::CSSRubyOverhangEnabled();
  }
  bool cssSafePrintableInsetEnabled() {
    return RuntimeEnabledFeatures::CSSSafePrintableInsetEnabled();
  }
  bool cssScopeifiedParentPseudoClassEnabled() {
    return RuntimeEnabledFeatures::CSSScopeifiedParentPseudoClassEnabled();
  }
  bool cssScopeImportEnabled() {
    return RuntimeEnabledFeatures::CSSScopeImportEnabled();
  }
  bool cssScrolledContainerQueriesEnabled() {
    return RuntimeEnabledFeatures::CSSScrolledContainerQueriesEnabled();
  }
  bool cssScrollInitialTargetEnabled() {
    return RuntimeEnabledFeatures::CSSScrollInitialTargetEnabled();
  }
  bool cssScrollMarkerGroupModesEnabled() {
    return RuntimeEnabledFeatures::CSSScrollMarkerGroupModesEnabled();
  }
  bool cssScrollMarkerTargetBeforeAfterEnabled() {
    return RuntimeEnabledFeatures::CSSScrollMarkerTargetBeforeAfterEnabled();
  }
  bool cssScrollSnapChangeEventEnabled() {
    return RuntimeEnabledFeatures::CSSScrollSnapChangeEventEnabled();
  }
  bool cssScrollSnapChangingEventEnabled() {
    return RuntimeEnabledFeatures::CSSScrollSnapChangingEventEnabled();
  }
  bool cssScrollSnapEventConstructorExposedEnabled() {
    return RuntimeEnabledFeatures::CSSScrollSnapEventConstructorExposedEnabled();
  }
  bool cssScrollSnapEventsEnabled() {
    return RuntimeEnabledFeatures::CSSScrollSnapEventsEnabled();
  }
  bool cssScrollTargetGroupEnabled() {
    return RuntimeEnabledFeatures::CSSScrollTargetGroupEnabled();
  }
  bool cssScrollTargetGroupAriaCurrentEnabled() {
    return RuntimeEnabledFeatures::CSSScrollTargetGroupAriaCurrentEnabled();
  }
  bool cssShapeEllipseCirclePositionSerializationEnabled() {
    return RuntimeEnabledFeatures::CSSShapeEllipseCirclePositionSerializationEnabled();
  }
  bool cssShapeOutsidePathAndShapeSupportEnabled() {
    return RuntimeEnabledFeatures::CSSShapeOutsidePathAndShapeSupportEnabled();
  }
  bool cssShapeOutsideRectAndXywhSupportEnabled() {
    return RuntimeEnabledFeatures::CSSShapeOutsideRectAndXywhSupportEnabled();
  }
  bool cssStyleSheetInitBaseURLEnabled() {
    return RuntimeEnabledFeatures::CSSStyleSheetInitBaseURLEnabled();
  }
  bool cssSupportsAtRuleFunctionEnabled() {
    return RuntimeEnabledFeatures::CSSSupportsAtRuleFunctionEnabled();
  }
  bool cssSupportsForImportRulesEnabled() {
    return RuntimeEnabledFeatures::CSSSupportsForImportRulesEnabled();
  }
  bool cssSupportsNamedFeatureFunctionEnabled() {
    return RuntimeEnabledFeatures::CSSSupportsNamedFeatureFunctionEnabled();
  }
  bool cssSystemAccentColorEnabled() {
    return RuntimeEnabledFeatures::CSSSystemAccentColorEnabled();
  }
  bool cssTextAlignMatchParentEnabled() {
    return RuntimeEnabledFeatures::CSSTextAlignMatchParentEnabled();
  }
  bool cssTextDecorationSkipInkAllEnabled() {
    return RuntimeEnabledFeatures::CSSTextDecorationSkipInkAllEnabled();
  }
  bool cssTextDecorationSkipSpacesEnabled() {
    return RuntimeEnabledFeatures::CSSTextDecorationSkipSpacesEnabled();
  }
  bool cssTextFitEnabled() {
    return RuntimeEnabledFeatures::CssTextFitEnabled();
  }
  bool cssTextFitReshapingEnabled() {
    return RuntimeEnabledFeatures::CssTextFitReshapingEnabled();
  }
  bool cssTextIndentEnabled() {
    return RuntimeEnabledFeatures::CssTextIndentEnabled();
  }
  bool cssTextIndentAsPrimitiveEnabled() {
    return RuntimeEnabledFeatures::CssTextIndentAsPrimitiveEnabled();
  }
  bool cssTextSpacingEnabled() {
    return RuntimeEnabledFeatures::CSSTextSpacingEnabled();
  }
  bool cssTextTransformFullSizeKanaEnabled() {
    return RuntimeEnabledFeatures::CSSTextTransformFullSizeKanaEnabled();
  }
  bool cssTextTransformFullWidthEnabled() {
    return RuntimeEnabledFeatures::CSSTextTransformFullWidthEnabled();
  }
  bool cssTextTransformMultiKeywordEnabled() {
    return RuntimeEnabledFeatures::CSSTextTransformMultiKeywordEnabled();
  }
  bool cssTimelineScopeAllEnabled() {
    return RuntimeEnabledFeatures::CSSTimelineScopeAllEnabled();
  }
  bool cssTimelineScopeGlobalEnabled() {
    return RuntimeEnabledFeatures::CSSTimelineScopeGlobalEnabled();
  }
  bool cssTypedArithmeticEnabled() {
    return RuntimeEnabledFeatures::CSSTypedArithmeticEnabled();
  }
  bool cssURLRequestModifiersEnabled() {
    return RuntimeEnabledFeatures::CSSURLRequestModifiersEnabled();
  }
  bool cssUserSelectContainEnabled() {
    return RuntimeEnabledFeatures::CSSUserSelectContainEnabled();
  }
  bool cssUserValidAndUserInvalidForRadioEnabled() {
    return RuntimeEnabledFeatures::CSSUserValidAndUserInvalidForRadioEnabled();
  }
  bool cssVideoDynamicRangeMediaQueriesEnabled() {
    return RuntimeEnabledFeatures::CSSVideoDynamicRangeMediaQueriesEnabled();
  }
  bool cssViewTransitionAutoNameEnabled() {
    return RuntimeEnabledFeatures::CSSViewTransitionAutoNameEnabled();
  }
  bool customElementsDisableFormattingFixupsEnabled() {
    return RuntimeEnabledFeatures::CustomElementsDisableFormattingFixupsEnabled();
  }
  bool customizableComboboxEnabled() {
    return RuntimeEnabledFeatures::CustomizableComboboxEnabled();
  }
  bool customizableSelectMultiplePopupEnabled() {
    return RuntimeEnabledFeatures::CustomizableSelectMultiplePopupEnabled();
  }
  bool customScrollbarApplyMinimumThumbLengthEnabled() {
    return RuntimeEnabledFeatures::CustomScrollbarApplyMinimumThumbLengthEnabled();
  }
  bool databaseEnabled() {
    return RuntimeEnabledFeatures::DatabaseEnabled();
  }
  bool dateTimeLocalArabicCommaWorkaroundEnabled() {
    return RuntimeEnabledFeatures::DateTimeLocalArabicCommaWorkaroundEnabled();
  }
  bool declarativeCSSModulesEnabled() {
    return RuntimeEnabledFeatures::DeclarativeCSSModulesEnabledByRuntimeFlag();
  }
  bool declarativeCSSModulesStyleTagEnabled() {
    return RuntimeEnabledFeatures::DeclarativeCSSModulesStyleTagEnabledByRuntimeFlag();
  }
  bool decoupleComputedBorderWidthFromStyleEnabled() {
    return RuntimeEnabledFeatures::DecoupleComputedBorderWidthFromStyleEnabled();
  }
  bool decoupleResolvedColumnRuleWidthFromStyleEnabled() {
    return RuntimeEnabledFeatures::DecoupleResolvedColumnRuleWidthFromStyleEnabled();
  }
  bool delegatesFocusTextControlInputFixEnabled() {
    return RuntimeEnabledFeatures::DelegatesFocusTextControlInputFixEnabled();
  }
  bool deleteTextInContentEditableBeforeRemovingChildrenEnabled() {
    return RuntimeEnabledFeatures::DeleteTextInContentEditableBeforeRemovingChildrenEnabled();
  }
  bool deprecateUnloadOptOutEnabled() {
    return RuntimeEnabledFeatures::DeprecateUnloadOptOutEnabledByRuntimeFlag();
  }
  bool desktopCaptureDisableLocalEchoControlEnabled() {
    return RuntimeEnabledFeatures::DesktopCaptureDisableLocalEchoControlEnabled();
  }
  bool desktopPWAsAdditionalWindowingControlsEnabled() {
    return RuntimeEnabledFeatures::DesktopPWAsAdditionalWindowingControlsEnabled();
  }
  bool desktopPWAsAdditionalWindowingControlsOnMoveEnabled() {
    return RuntimeEnabledFeatures::DesktopPWAsAdditionalWindowingControlsOnMoveEnabled();
  }
  bool deviceAttributesEnabled() {
    return RuntimeEnabledFeatures::DeviceAttributesEnabled();
  }
  bool deviceOrientationRequestPermissionEnabled() {
    return RuntimeEnabledFeatures::DeviceOrientationRequestPermissionEnabled();
  }
  bool devicePostureEnabled() {
    return RuntimeEnabledFeatures::DevicePostureEnabled();
  }
  bool dialogCloseWhenOpenRemovedEnabled() {
    return RuntimeEnabledFeatures::DialogCloseWhenOpenRemovedEnabled();
  }
  bool dialogNewFocusBehaviorEnabled() {
    return RuntimeEnabledFeatures::DialogNewFocusBehaviorEnabled();
  }
  bool digitalGoodsEnabled() {
    return RuntimeEnabledFeatures::DigitalGoodsEnabledByRuntimeFlag();
  }
  bool digitalGoodsV21Enabled() {
    return RuntimeEnabledFeatures::DigitalGoodsV2_1Enabled();
  }
  bool directSocketsEnabled() {
    return RuntimeEnabledFeatures::DirectSocketsEnabled();
  }
  bool directSocketsInServiceWorkersEnabled() {
    return RuntimeEnabledFeatures::DirectSocketsInServiceWorkersEnabled();
  }
  bool directSocketsInSharedWorkersEnabled() {
    return RuntimeEnabledFeatures::DirectSocketsInSharedWorkersEnabled();
  }
  bool disableAnchorCenterOnAlignJustifyItemsEnabled() {
    return RuntimeEnabledFeatures::DisableAnchorCenterOnAlignJustifyItemsEnabled();
  }
  bool disableDifferentOriginSubframeDialogSuppressionEnabled() {
    return RuntimeEnabledFeatures::DisableDifferentOriginSubframeDialogSuppressionEnabledByRuntimeFlag();
  }
  bool disableEllipsisWhenScrolledEnabled() {
    return RuntimeEnabledFeatures::DisableEllipsisWhenScrolledEnabled();
  }
  bool disableReduceAcceptLanguageEnabled() {
    return RuntimeEnabledFeatures::DisableReduceAcceptLanguageEnabledByRuntimeFlag();
  }
  bool disableRemoveFormatForPlainTextOnlyEditableDivEnabled() {
    return RuntimeEnabledFeatures::DisableRemoveFormatForPlainTextOnlyEditableDivEnabled();
  }
  bool disallowDisconnectedAreaNavigationEnabled() {
    return RuntimeEnabledFeatures::DisallowDisconnectedAreaNavigationEnabled();
  }
  bool disallowPickerForReadonlyInputsEnabled() {
    return RuntimeEnabledFeatures::DisallowPickerForReadonlyInputsEnabled();
  }
  bool disconnectWebSocketOnBFCacheEnabled() {
    return RuntimeEnabledFeatures::DisconnectWebSocketOnBFCacheEnabled();
  }
  bool dispatchHiddenVisibilityTransitionsEnabled() {
    return RuntimeEnabledFeatures::DispatchHiddenVisibilityTransitionsEnabled();
  }
  bool dispatchSelectionchangeEventPerElementEnabled() {
    return RuntimeEnabledFeatures::DispatchSelectionchangeEventPerElementEnabled();
  }
  bool displayContentsFocusableEnabled() {
    return RuntimeEnabledFeatures::DisplayContentsFocusableEnabled();
  }
  bool displayCutoutAPIEnabled() {
    return RuntimeEnabledFeatures::DisplayCutoutAPIEnabled();
  }
  bool documentActiveViewTransitionEnabled() {
    return RuntimeEnabledFeatures::DocumentActiveViewTransitionEnabled();
  }
  bool documentCookieEnabled() {
    return RuntimeEnabledFeatures::DocumentCookieEnabled();
  }
  bool documentDomainEnabled() {
    return RuntimeEnabledFeatures::DocumentDomainEnabled();
  }
  bool documentIsolationPolicyEnabled() {
    return RuntimeEnabledFeatures::DocumentIsolationPolicyEnabledByRuntimeFlag();
  }
  bool documentOpenIframeUnloadEventsEnabled() {
    return RuntimeEnabledFeatures::DocumentOpenIframeUnloadEventsEnabled();
  }
  bool documentOpenOriginAliasRemovalEnabled() {
    return RuntimeEnabledFeatures::DocumentOpenOriginAliasRemovalEnabled();
  }
  bool documentOpenSandboxInheritanceRemovalEnabled() {
    return RuntimeEnabledFeatures::DocumentOpenSandboxInheritanceRemovalEnabled();
  }
  bool documentPatchingEnabled() {
    return RuntimeEnabledFeatures::DocumentPatchingEnabled();
  }
  bool documentPictureInPictureAPIEnabled() {
    return RuntimeEnabledFeatures::DocumentPictureInPictureAPIEnabled();
  }
  bool documentPictureInPicturePreferInitialPlacementEnabled() {
    return RuntimeEnabledFeatures::DocumentPictureInPicturePreferInitialPlacementEnabled();
  }
  bool documentPictureInPictureUserActivationEnabled() {
    return RuntimeEnabledFeatures::DocumentPictureInPictureUserActivationEnabled();
  }
  bool documentPolicyDocumentDomainEnabled() {
    return RuntimeEnabledFeatures::DocumentPolicyDocumentDomainEnabled();
  }
  bool documentPolicyExpectNoLinkedResourcesEnabled() {
    return RuntimeEnabledFeatures::DocumentPolicyExpectNoLinkedResourcesEnabled();
  }
  bool documentPolicyIncludeJSCallStacksInCrashReportsEnabled() {
    return RuntimeEnabledFeatures::DocumentPolicyIncludeJSCallStacksInCrashReportsEnabled();
  }
  bool documentPolicyInDedicatedWorkerEnabled() {
    return RuntimeEnabledFeatures::DocumentPolicyInDedicatedWorkerEnabled();
  }
  bool documentPolicyNegotiationEnabled() {
    return RuntimeEnabledFeatures::DocumentPolicyNegotiationEnabledByRuntimeFlag();
  }
  bool documentPolicyNetworkEfficiencyGuardrailsEnabled() {
    return RuntimeEnabledFeatures::DocumentPolicyNetworkEfficiencyGuardrailsEnabled();
  }
  bool documentPolicySyncXHREnabled() {
    return RuntimeEnabledFeatures::DocumentPolicySyncXHREnabled();
  }
  bool documentWriteEnabled() {
    return RuntimeEnabledFeatures::DocumentWriteEnabled();
  }
  bool domActivateBubblesInheritanceEnabled() {
    return RuntimeEnabledFeatures::DOMActivateBubblesInheritanceEnabled();
  }
  bool dontLeakShadowTreesInDragEventsEnabled() {
    return RuntimeEnabledFeatures::DontLeakShadowTreesInDragEventsEnabled();
  }
  bool editContextAssignmentAsPerSpecEnabled() {
    return RuntimeEnabledFeatures::EditContextAssignmentAsPerSpecEnabled();
  }
  bool editContextHandleTextOrSelectionUpdateDuringCompositionEnabled() {
    return RuntimeEnabledFeatures::EditContextHandleTextOrSelectionUpdateDuringCompositionEnabled();
  }
  bool editEmojiTagSequenceEnabled() {
    return RuntimeEnabledFeatures::EditEmojiTagSequenceEnabled();
  }
  bool editingLineMovementWithRubyFixEnabled() {
    return RuntimeEnabledFeatures::EditingLineMovementWithRubyFixEnabled();
  }
  bool elementCaptureEnabled() {
    return RuntimeEnabledFeatures::ElementCaptureEnabled();
  }
  bool elementInnerTextHandleFirstLineStyleEnabled() {
    return RuntimeEnabledFeatures::ElementInnerTextHandleFirstLineStyleEnabled();
  }
  bool elementInternalsBehaviorsEnabled() {
    return RuntimeEnabledFeatures::ElementInternalsBehaviorsEnabled();
  }
  bool elementSpecificReadOnlyConstraintValidationEnabled() {
    return RuntimeEnabledFeatures::ElementSpecificReadOnlyConstraintValidationEnabled();
  }
  bool emailVerificationProtocolEnabled() {
    return RuntimeEnabledFeatures::EmailVerificationProtocolEnabled();
  }
  bool emojiMonochromeRenderingEnabled() {
    return RuntimeEnabledFeatures::EmojiMonochromeRenderingEnabled();
  }
  bool endpointInclusiveCommitStylesEnabled() {
    return RuntimeEnabledFeatures::EndpointInclusiveCommitStylesEnabled();
  }
  bool enforceAnonymityExposureEnabled() {
    return RuntimeEnabledFeatures::EnforceAnonymityExposureEnabled();
  }
  bool enterInOpenShadowRootsEnabled() {
    return RuntimeEnabledFeatures::EnterInOpenShadowRootsEnabled();
  }
  bool entropyIgnoredForFirstVideoFrameLCPEnabled() {
    return RuntimeEnabledFeatures::EntropyIgnoredForFirstVideoFrameLCPEnabled();
  }
  bool eventPseudoTargetPropertyEnabled() {
    return RuntimeEnabledFeatures::EventPseudoTargetPropertyEnabled();
  }
  bool eventTimingInteractionCountEnabled() {
    return RuntimeEnabledFeatures::EventTimingInteractionCountEnabled();
  }
  bool eventTimingTargetSelectorEnabled() {
    return RuntimeEnabledFeatures::EventTimingTargetSelectorEnabled();
  }
  bool eventTriggerEnabled() {
    return RuntimeEnabledFeatures::EventTriggerEnabled();
  }
  bool experimentalContentSecurityPolicyFeaturesEnabled() {
    return RuntimeEnabledFeatures::ExperimentalContentSecurityPolicyFeaturesEnabled();
  }
  bool experimentalJSProfilerMarkersEnabled() {
    return RuntimeEnabledFeatures::ExperimentalJSProfilerMarkersEnabled();
  }
  bool experimentalMachineLearningNeuralNetworkEnabled() {
    return RuntimeEnabledFeatures::ExperimentalMachineLearningNeuralNetworkEnabled();
  }
  bool experimentalPoliciesEnabled() {
    return RuntimeEnabledFeatures::ExperimentalPoliciesEnabled();
  }
  bool exposeCSSFontFeatureValuesRuleEnabled() {
    return RuntimeEnabledFeatures::ExposeCSSFontFeatureValuesRuleEnabled();
  }
  bool exposeRenderTimeNonTaoDelayedImageEnabled() {
    return RuntimeEnabledFeatures::ExposeRenderTimeNonTaoDelayedImageEnabled();
  }
  bool extendedShapeCacheEnabled() {
    return RuntimeEnabledFeatures::ExtendedShapeCacheEnabled();
  }
  bool extendedTextMetricsEnabled() {
    return RuntimeEnabledFeatures::ExtendedTextMetricsEnabledByRuntimeFlag();
  }
  bool externalPopupMenuClickEventEnabled() {
    return RuntimeEnabledFeatures::ExternalPopupMenuClickEventEnabled();
  }
  bool eyeDropperAPIEnabled() {
    return RuntimeEnabledFeatures::EyeDropperAPIEnabled();
  }
  bool faceDetectorEnabled() {
    return RuntimeEnabledFeatures::FaceDetectorEnabled();
  }
  bool fastPositionIteratorEnabled() {
    return RuntimeEnabledFeatures::FastPositionIteratorEnabled();
  }
  bool fedCmEnabled() {
    return RuntimeEnabledFeatures::FedCmEnabled();
  }
  bool fedCmAutofillEnabled() {
    return RuntimeEnabledFeatures::FedCmAutofillEnabled();
  }
  bool fedCmDelegationEnabled() {
    return RuntimeEnabledFeatures::FedCmDelegationEnabled();
  }
  bool fedCmErrorAttributeEnabled() {
    return RuntimeEnabledFeatures::FedCmErrorAttributeEnabled();
  }
  bool fedCmIdPRegistrationEnabled() {
    return RuntimeEnabledFeatures::FedCmIdPRegistrationEnabled();
  }
  bool fedCmLightweightModeEnabled() {
    return RuntimeEnabledFeatures::FedCmLightweightModeEnabled();
  }
  bool fedCmMultipleIdentityProvidersEnabled() {
    return RuntimeEnabledFeatures::FedCmMultipleIdentityProvidersEnabledByRuntimeFlag();
  }
  bool fedCmNavigationInterceptionEnabled() {
    return RuntimeEnabledFeatures::FedCmNavigationInterceptionEnabled();
  }
  bool fedCmNonStringTokenEnabled() {
    return RuntimeEnabledFeatures::FedCmNonStringTokenEnabled();
  }
  bool fencedFramesEnabled() {
    return RuntimeEnabledFeatures::FencedFramesEnabled();
  }
  bool fencedFramesAPIChangesEnabled() {
    return RuntimeEnabledFeatures::FencedFramesAPIChangesEnabled();
  }
  bool fencedFramesDefaultModeEnabled() {
    return RuntimeEnabledFeatures::FencedFramesDefaultModeEnabled();
  }
  bool fencedFramesLocalUnpartitionedDataAccessEnabled() {
    return RuntimeEnabledFeatures::FencedFramesLocalUnpartitionedDataAccessEnabled();
  }
  bool fetchBodyBytesEnabled() {
    return RuntimeEnabledFeatures::FetchBodyBytesEnabled();
  }
  bool fetchLaterAPIEnabled() {
    return RuntimeEnabledFeatures::FetchLaterAPIEnabled();
  }
  bool fetchRetryEnabled() {
    return RuntimeEnabledFeatures::FetchRetryEnabledByRuntimeFlag();
  }
  bool fetchUploadStreamingEnabled() {
    return RuntimeEnabledFeatures::FetchUploadStreamingEnabled();
  }
  bool fileHandlingEnabled() {
    return RuntimeEnabledFeatures::FileHandlingEnabled();
  }
  bool fileHandlingIconsEnabled() {
    return RuntimeEnabledFeatures::FileHandlingIconsEnabled();
  }
  bool fileSystemEnabled() {
    return RuntimeEnabledFeatures::FileSystemEnabled();
  }
  bool fileSystemAccessEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessEnabled();
  }
  bool fileSystemAccessAPIExperimentalEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessAPIExperimentalEnabled();
  }
  bool fileSystemAccessGetCloudIdentifiersEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessGetCloudIdentifiersEnabled();
  }
  bool fileSystemAccessLocalEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessLocalEnabled();
  }
  bool fileSystemAccessLockingSchemeEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessLockingSchemeEnabled();
  }
  bool fileSystemAccessOriginPrivateEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessOriginPrivateEnabled();
  }
  bool fileSystemAccessRevokeReadOnRemoveEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessRevokeReadOnRemoveEnabled();
  }
  bool fileSystemAccessWriteModeEnabled() {
    return RuntimeEnabledFeatures::FileSystemAccessWriteModeEnabled();
  }
  bool fileSystemObserverEnabled() {
    return RuntimeEnabledFeatures::FileSystemObserverEnabled();
  }
  bool fileSystemObserverUnobserveEnabled() {
    return RuntimeEnabledFeatures::FileSystemObserverUnobserveEnabled();
  }
  bool filterableSelectEnabled() {
    return RuntimeEnabledFeatures::FilterableSelectEnabled();
  }
  bool filterContainerLevelStylesEnabled() {
    return RuntimeEnabledFeatures::FilterContainerLevelStylesEnabled();
  }
  bool filteringPrimitivesEnabled() {
    return RuntimeEnabledFeatures::FilteringPrimitivesEnabled();
  }
  bool findFirstMisspellingEndWhenNonEditableEnabled() {
    return RuntimeEnabledFeatures::FindFirstMisspellingEndWhenNonEditableEnabled();
  }
  bool firstLineOnListItemEnabled() {
    return RuntimeEnabledFeatures::FirstLineOnListItemEnabled();
  }
  bool firstLineTextMetricsEnabled() {
    return RuntimeEnabledFeatures::FirstLineTextMetricsEnabled();
  }
  bool fixHTMLFormControlElementIsReadOnlyEnabled() {
    return RuntimeEnabledFeatures::FixHTMLFormControlElementIsReadOnlyEnabled();
  }
  bool fixJustifyQueryCommandValueEnabled() {
    return RuntimeEnabledFeatures::FixJustifyQueryCommandValueEnabled();
  }
  bool fixLinebreakForPreTagEnabled() {
    return RuntimeEnabledFeatures::FixLinebreakForPreTagEnabled();
  }
  bool fixMapElementEmptyNameBugEnabled() {
    return RuntimeEnabledFeatures::FixMapElementEmptyNameBugEnabled();
  }
  bool fixMarkerSuppressionForAppearanceAutoEnabled() {
    return RuntimeEnabledFeatures::FixMarkerSuppressionForAppearanceAutoEnabled();
  }
  bool fixNextPositionCalculationInInsertListEnabled() {
    return RuntimeEnabledFeatures::FixNextPositionCalculationInInsertListEnabled();
  }
  bool fixStrikethroughToggleInEmptyContentEditableEnabled() {
    return RuntimeEnabledFeatures::FixStrikethroughToggleInEmptyContentEditableEnabled();
  }
  bool fixVisualRectRemoteViewportTransformEnabled() {
    return RuntimeEnabledFeatures::FixVisualRectRemoteViewportTransformEnabled();
  }
  bool fledgeEnabled() {
    return RuntimeEnabledFeatures::FledgeEnabled();
  }
  bool fledgeAuctionDealSupportEnabled() {
    return RuntimeEnabledFeatures::FledgeAuctionDealSupportEnabled();
  }
  bool fledgeBiddingAndAuctionServerAPIEnabled() {
    return RuntimeEnabledFeatures::FledgeBiddingAndAuctionServerAPIEnabledByRuntimeFlag();
  }
  bool fledgeBiddingAndAuctionServerAPIMultiSellerEnabled() {
    return RuntimeEnabledFeatures::FledgeBiddingAndAuctionServerAPIMultiSellerEnabled();
  }
  bool fledgeClickinessEnabled() {
    return RuntimeEnabledFeatures::FledgeClickinessEnabled();
  }
  bool fledgeCustomMaxAuctionAdComponentsEnabled() {
    return RuntimeEnabledFeatures::FledgeCustomMaxAuctionAdComponentsEnabled();
  }
  bool fledgeDeprecatedRenderURLReplacementsEnabled() {
    return RuntimeEnabledFeatures::FledgeDeprecatedRenderURLReplacementsEnabled();
  }
  bool fledgeDirectFromSellerSignalsHeaderAdSlotEnabled() {
    return RuntimeEnabledFeatures::FledgeDirectFromSellerSignalsHeaderAdSlotEnabled();
  }
  bool fledgeDirectFromSellerSignalsWebBundlesEnabled() {
    return RuntimeEnabledFeatures::FledgeDirectFromSellerSignalsWebBundlesEnabled();
  }
  bool fledgeMultiBidEnabled() {
    return RuntimeEnabledFeatures::FledgeMultiBidEnabled();
  }
  bool fledgePrivateModelTrainingEnabled() {
    return RuntimeEnabledFeatures::FledgePrivateModelTrainingEnabled();
  }
  bool fledgeRealTimeReportingEnabled() {
    return RuntimeEnabledFeatures::FledgeRealTimeReportingEnabled();
  }
  bool fledgeSellerNonceEnabled() {
    return RuntimeEnabledFeatures::FledgeSellerNonceEnabled();
  }
  bool fledgeSellerScriptExecutionModeEnabled() {
    return RuntimeEnabledFeatures::FledgeSellerScriptExecutionModeEnabled();
  }
  bool fledgeTrustedSignalsKVv1CreativeScanningEnabled() {
    return RuntimeEnabledFeatures::FledgeTrustedSignalsKVv1CreativeScanningEnabled();
  }
  bool fledgeTrustedSignalsKVv2ContextualDataEnabled() {
    return RuntimeEnabledFeatures::FledgeTrustedSignalsKVv2ContextualDataEnabled();
  }
  bool fledgeTrustedSignalsKVv2SupportEnabled() {
    return RuntimeEnabledFeatures::FledgeTrustedSignalsKVv2SupportEnabled();
  }
  bool flexWrapBalanceEnabled() {
    return RuntimeEnabledFeatures::FlexWrapBalanceEnabled();
  }
  bool focusgroupEnabled() {
    return RuntimeEnabledFeatures::FocusgroupEnabledByRuntimeFlag();
  }
  bool focusgroupGridEnabled() {
    return RuntimeEnabledFeatures::FocusgroupGridEnabledByRuntimeFlag();
  }
  bool fontAccessEnabled() {
    return RuntimeEnabledFeatures::FontAccessEnabled();
  }
  bool fontDataServiceEnabled() {
    return RuntimeEnabledFeatures::FontDataServiceEnabled();
  }
  bool fontFallbackForTabSizeEnabled() {
    return RuntimeEnabledFeatures::FontFallbackForTabSizeEnabled();
  }
  bool fontFamilyPostscriptMatchingCTMigrationEnabled() {
    return RuntimeEnabledFeatures::FontFamilyPostscriptMatchingCTMigrationEnabled();
  }
  bool fontFamilyStyleMatchingCTMigrationEnabled() {
    return RuntimeEnabledFeatures::FontFamilyStyleMatchingCTMigrationEnabled();
  }
  bool fontFeatureSettingsDescriptorEnabled() {
    return RuntimeEnabledFeatures::FontFeatureSettingsDescriptorEnabled();
  }
  bool fontFormatAvar2Enabled() {
    return RuntimeEnabledFeatures::FontFormatAvar2Enabled();
  }
  bool fontLanguageOverrideEnabled() {
    return RuntimeEnabledFeatures::FontLanguageOverrideEnabled();
  }
  bool fontMatchAliasesAsLastResortEnabled() {
    return RuntimeEnabledFeatures::FontMatchAliasesAsLastResortEnabled();
  }
  bool fontStyleObliqueZeroDegreeAsNormalEnabled() {
    return RuntimeEnabledFeatures::FontStyleObliqueZeroDegreeAsNormalEnabled();
  }
  bool fontVariationSettingsDescriptorEnabled() {
    return RuntimeEnabledFeatures::FontVariationSettingsDescriptorEnabled();
  }
  bool forcedColorsEnabled() {
    return RuntimeEnabledFeatures::ForcedColorsEnabled();
  }
  bool forceEagerMeasureMemoryEnabled() {
    return RuntimeEnabledFeatures::ForceEagerMeasureMemoryEnabled();
  }
  bool forceReduceMotionEnabled() {
    return RuntimeEnabledFeatures::ForceReduceMotionEnabled();
  }
  bool fractionalScrollOffsetsEnabled() {
    return RuntimeEnabledFeatures::FractionalScrollOffsetsEnabled();
  }
  bool fragmentedOofInCbEnabled() {
    return RuntimeEnabledFeatures::FragmentedOofInCbEnabled();
  }
  bool freezeFramesOnVisibilityEnabled() {
    return RuntimeEnabledFeatures::FreezeFramesOnVisibilityEnabled();
  }
  bool gamepadMultitouchEnabled() {
    return RuntimeEnabledFeatures::GamepadMultitouchEnabled();
  }
  bool gamepadRawInputChangeEventEnabled() {
    return RuntimeEnabledFeatures::GamepadRawInputChangeEventEnabled();
  }
  bool gamepadWindowEventHandlersEnabled() {
    return RuntimeEnabledFeatures::GamepadWindowEventHandlersEnabled();
  }
  bool geolocationElementEnabled() {
    return RuntimeEnabledFeatures::GeolocationElementEnabled();
  }
  bool geometryMapperSingularTransformFixEnabled() {
    return RuntimeEnabledFeatures::GeometryMapperSingularTransformFixEnabled();
  }
  bool geometryUtilsEnabled() {
    return RuntimeEnabledFeatures::GeometryUtilsEnabled();
  }
  bool geometryUtilsForCSSPseudoElementEnabled() {
    return RuntimeEnabledFeatures::GeometryUtilsForCSSPseudoElementEnabled();
  }
  bool getAllScreensMediaEnabled() {
    return RuntimeEnabledFeatures::GetAllScreensMediaEnabled();
  }
  bool getComputedStyleOutsideFlatTreeEnabled() {
    return RuntimeEnabledFeatures::GetComputedStyleOutsideFlatTreeEnabled();
  }
  bool getDisplayMediaEnabled() {
    return RuntimeEnabledFeatures::GetDisplayMediaEnabled();
  }
  bool getDisplayMediaRequiresUserActivationEnabled() {
    return RuntimeEnabledFeatures::GetDisplayMediaRequiresUserActivationEnabled();
  }
  bool getDisplayMediaWindowAudioCaptureEnabled() {
    return RuntimeEnabledFeatures::GetDisplayMediaWindowAudioCaptureEnabled();
  }
  bool getElementsByNameOnlyHTMLElementsEnabled() {
    return RuntimeEnabledFeatures::GetElementsByNameOnlyHTMLElementsEnabled();
  }
  bool getUserMediaEchoCancellationModesEnabled() {
    return RuntimeEnabledFeatures::GetUserMediaEchoCancellationModesEnabled();
  }
  bool groupEffectEnabled() {
    return RuntimeEnabledFeatures::GroupEffectEnabled();
  }
  bool handleDeletionAtStartAndEndBoundaryContainingHiddenElementEnabled() {
    return RuntimeEnabledFeatures::HandleDeletionAtStartAndEndBoundaryContainingHiddenElementEnabled();
  }
  bool handleDisconnectedSelectionDuringDOMChangesEnabled() {
    return RuntimeEnabledFeatures::HandleDisconnectedSelectionDuringDOMChangesEnabled();
  }
  bool handleInvalidMaskImageWithBackdropFilterEnabled() {
    return RuntimeEnabledFeatures::HandleInvalidMaskImageWithBackdropFilterEnabled();
  }
  bool handleShadowDOMInSubstringUtilEnabled() {
    return RuntimeEnabledFeatures::HandleShadowDOMInSubstringUtilEnabled();
  }
  bool handwritingRecognitionEnabled() {
    return RuntimeEnabledFeatures::HandwritingRecognitionEnabled();
  }
  bool hasUAVisualTransitionEnabled() {
    return RuntimeEnabledFeatures::HasUAVisualTransitionEnabled();
  }
  bool headingOffsetEnabled() {
    return RuntimeEnabledFeatures::HeadingOffsetEnabled();
  }
  bool hideVideoControlsWhenUnneededEnabled() {
    return RuntimeEnabledFeatures::HideVideoControlsWhenUnneededEnabled();
  }
  bool highlightsFromPointEnabled() {
    return RuntimeEnabledFeatures::HighlightsFromPointEnabled();
  }
  bool hitTestBorderRadiusForStackingContextEnabled() {
    return RuntimeEnabledFeatures::HitTestBorderRadiusForStackingContextEnabled();
  }
  bool hitTestContainerTransformStateForPreserve3dEnabled() {
    return RuntimeEnabledFeatures::HitTestContainerTransformStateForPreserve3dEnabled();
  }
  bool hrefTranslateEnabled() {
    return RuntimeEnabledFeatures::HrefTranslateEnabledByRuntimeFlag();
  }
  bool hstsTopLevelNavigationsOnlyEnabled() {
    return RuntimeEnabledFeatures::HstsTopLevelNavigationsOnlyEnabled();
  }
  bool htmlAdoptionAlgorithmNewStepsEnabled() {
    return RuntimeEnabledFeatures::HTMLAdoptionAlgorithmNewStepsEnabled();
  }
  bool htmlCommandActionsV2Enabled() {
    return RuntimeEnabledFeatures::HTMLCommandActionsV2Enabled();
  }
  bool htmlCommandElementRemovalEnabled() {
    return RuntimeEnabledFeatures::HTMLCommandElementRemovalEnabled();
  }
  bool htmlCommandForScrollCommandsEnabled() {
    return RuntimeEnabledFeatures::HTMLCommandForScrollCommandsEnabled();
  }
  bool htmlElementScrollParentEnabled() {
    return RuntimeEnabledFeatures::HTMLElementScrollParentEnabled();
  }
  bool htmlImageElementActualNaturalSizeEnabled() {
    return RuntimeEnabledFeatures::HTMLImageElementActualNaturalSizeEnabled();
  }
  bool htmlInputElementDropWebkitClearButtonEnabled() {
    return RuntimeEnabledFeatures::HTMLInputElementDropWebkitClearButtonEnabled();
  }
  bool htmlInterestForInterestButtonPseudoEnabled() {
    return RuntimeEnabledFeatures::HTMLInterestForInterestButtonPseudoEnabled();
  }
  bool htmlLinkElementAttributeValueChangesEnabled() {
    return RuntimeEnabledFeatures::HTMLLinkElementAttributeValueChangesEnabled();
  }
  bool htmlParserYieldAndDelayOftenForTestingEnabled() {
    return RuntimeEnabledFeatures::HTMLParserYieldAndDelayOftenForTestingEnabled();
  }
  bool htmlParserYieldByUserTimingEnabled() {
    return RuntimeEnabledFeatures::HTMLParserYieldByUserTimingEnabled();
  }
  bool htmlPrintingArtifactAnnotationsEnabled() {
    return RuntimeEnabledFeatures::HTMLPrintingArtifactAnnotationsEnabled();
  }
  bool htmlProcessingInstructionEnabled() {
    return RuntimeEnabledFeatures::HTMLProcessingInstructionEnabled();
  }
  bool icuCapitalizationEnabled() {
    return RuntimeEnabledFeatures::ICUCapitalizationEnabled();
  }
  bool ignoreLetterSpacingInCursiveScriptsEnabled() {
    return RuntimeEnabledFeatures::IgnoreLetterSpacingInCursiveScriptsEnabled();
  }
  bool imageDataPixelFormatEnabled() {
    return RuntimeEnabledFeatures::ImageDataPixelFormatEnabled();
  }
  bool imageDocumentUseLayoutWidthEnabled() {
    return RuntimeEnabledFeatures::ImageDocumentUseLayoutWidthEnabled();
  }
  bool imageSrcsetReselectionEnabled() {
    return RuntimeEnabledFeatures::ImageSrcsetReselectionEnabled();
  }
  bool implicitRootScrollerEnabled() {
    return RuntimeEnabledFeatures::ImplicitRootScrollerEnabled();
  }
  bool improvedSourceRetargetingEnabled() {
    return RuntimeEnabledFeatures::ImprovedSourceRetargetingEnabled();
  }
  bool incomingCallNotificationsEnabled() {
    return RuntimeEnabledFeatures::IncomingCallNotificationsEnabledByRuntimeFlag();
  }
  bool inertElementNonEditableEnabled() {
    return RuntimeEnabledFeatures::InertElementNonEditableEnabled();
  }
  bool infiniteCullRectEnabled() {
    return RuntimeEnabledFeatures::InfiniteCullRectEnabled();
  }
  bool inheritUserModifyWithoutContenteditableEnabled() {
    return RuntimeEnabledFeatures::InheritUserModifyWithoutContenteditableEnabled();
  }
  bool inlineBlockLineNavigationEnabled() {
    return RuntimeEnabledFeatures::InlineBlockLineNavigationEnabled();
  }
  bool inlineScriptCacheHintEnabled() {
    return RuntimeEnabledFeatures::InlineScriptCacheHintEnabled();
  }
  bool innerHTMLParserFastpathLogFailureEnabled() {
    return RuntimeEnabledFeatures::InnerHTMLParserFastpathLogFailureEnabled();
  }
  bool inputEventDataTransferForInsertCmdEnabled() {
    return RuntimeEnabledFeatures::InputEventDataTransferForInsertCmdEnabled();
  }
  bool inputEventsDeleteNonCollapsedSelectionEnabled() {
    return RuntimeEnabledFeatures::InputEventsDeleteNonCollapsedSelectionEnabled();
  }
  bool inputInSelectEnabled() {
    return RuntimeEnabledFeatures::InputInSelectEnabled();
  }
  bool inputMultipleFieldsUIEnabled() {
    return RuntimeEnabledFeatures::InputMultipleFieldsUIEnabled();
  }
  bool insertBlockquoteBeforeOuterBlockEnabled() {
    return RuntimeEnabledFeatures::InsertBlockquoteBeforeOuterBlockEnabled();
  }
  bool installedAppEnabled() {
    return RuntimeEnabledFeatures::InstalledAppEnabled();
  }
  bool installElementEnabled() {
    return RuntimeEnabledFeatures::InstallElementEnabledByRuntimeFlag();
  }
  bool installOnDeviceSpeechRecognitionEnabled() {
    return RuntimeEnabledFeatures::InstallOnDeviceSpeechRecognitionEnabled();
  }
  bool integrityPolicyScriptEnabled() {
    return RuntimeEnabledFeatures::IntegrityPolicyScriptEnabled();
  }
  bool interestEventsNonComposedEnabled() {
    return RuntimeEnabledFeatures::InterestEventsNonComposedEnabled();
  }
  bool interestGroupsInSharedStorageWorkletEnabled() {
    return RuntimeEnabledFeatures::InterestGroupsInSharedStorageWorkletEnabled();
  }
  bool intersectionObserverCompositedAnimationsForceMainFramesEnabled() {
    return RuntimeEnabledFeatures::IntersectionObserverCompositedAnimationsForceMainFramesEnabled();
  }
  bool invertedColorsEnabled() {
    return RuntimeEnabledFeatures::InvertedColorsEnabled();
  }
  bool invisibleSVGAnimationThrottlingEnabled() {
    return RuntimeEnabledFeatures::InvisibleSVGAnimationThrottlingEnabled();
  }
  bool javaScriptCompileHintsPerFunctionMagicRuntimeEnabled() {
    return RuntimeEnabledFeatures::JavaScriptCompileHintsPerFunctionMagicRuntimeEnabledByRuntimeFlag();
  }
  bool javaScriptSourcePhaseImportsEnabled() {
    return RuntimeEnabledFeatures::JavaScriptSourcePhaseImportsEnabled();
  }
  bool keyboardAccessibleTooltipEnabled() {
    return RuntimeEnabledFeatures::KeyboardAccessibleTooltipEnabled();
  }
  bool keySystemTrackConfigurationEncryptionSchemeEnabled() {
    return RuntimeEnabledFeatures::KeySystemTrackConfigurationEncryptionSchemeEnabled();
  }
  bool labelInteractiveContentCheckBeforeHandlerEnabled() {
    return RuntimeEnabledFeatures::LabelInteractiveContentCheckBeforeHandlerEnabled();
  }
  bool langAttributeAwareFormControlUIEnabled() {
    return RuntimeEnabledFeatures::LangAttributeAwareFormControlUIEnabled();
  }
  bool languageDetectionAPIEnabled() {
    return RuntimeEnabledFeatures::LanguageDetectionAPIEnabled();
  }
  bool languageDetectionAPIForWorkersEnabled() {
    return RuntimeEnabledFeatures::LanguageDetectionAPIForWorkersEnabled();
  }
  bool layoutBoxRectGettersUseFragmentsEnabled() {
    return RuntimeEnabledFeatures::LayoutBoxRectGettersUseFragmentsEnabled();
  }
  bool layoutIgnoreMarginsForStickyEnabled() {
    return RuntimeEnabledFeatures::LayoutIgnoreMarginsForStickyEnabled();
  }
  bool layoutImageEmptyNaturalSizeBeforeSizeAvailableEnabled() {
    return RuntimeEnabledFeatures::LayoutImageEmptyNaturalSizeBeforeSizeAvailableEnabled();
  }
  bool layoutTableCellAlignmentSafeEnabled() {
    return RuntimeEnabledFeatures::LayoutTableCellAlignmentSafeEnabled();
  }
  bool lazyImageConformantLoadEventTimingEnabled() {
    return RuntimeEnabledFeatures::LazyImageConformantLoadEventTimingEnabled();
  }
  bool lazyLoadVideoAndAudioEnabled() {
    return RuntimeEnabledFeatures::LazyLoadVideoAndAudioEnabled();
  }
  bool leftClickToHandleSuggestionEnabled() {
    return RuntimeEnabledFeatures::LeftClickToHandleSuggestionEnabled();
  }
  bool lightDismissFromClickEnabled() {
    return RuntimeEnabledFeatures::LightDismissFromClickEnabled();
  }
  bool linkBlurImprovementEnabled() {
    return RuntimeEnabledFeatures::LinkBlurImprovementEnabled();
  }
  bool listOwnerMustHaveCSSBoxEnabled() {
    return RuntimeEnabledFeatures::ListOwnerMustHaveCSSBoxEnabled();
  }
  bool localNetworkAccessNonSecureContextAllowedEnabled() {
    return RuntimeEnabledFeatures::LocalNetworkAccessNonSecureContextAllowedEnabledByRuntimeFlag();
  }
  bool localNetworkAccessPermissionPolicyEnabled() {
    return RuntimeEnabledFeatures::LocalNetworkAccessPermissionPolicyEnabled();
  }
  bool localNetworkAccessSplitPermissionsEnabled() {
    return RuntimeEnabledFeatures::LocalNetworkAccessSplitPermissionsEnabled();
  }
  bool localNetworkAccessWebRTCEnabled() {
    return RuntimeEnabledFeatures::LocalNetworkAccessWebRTCEnabled();
  }
  bool lockedModeEnabled() {
    return RuntimeEnabledFeatures::LockedModeEnabled();
  }
  bool logicalStartOfLineBlockFallbackEnabled() {
    return RuntimeEnabledFeatures::LogicalStartOfLineBlockFallbackEnabled();
  }
  bool loginElementEnabled() {
    return RuntimeEnabledFeatures::LoginElementEnabled();
  }
  bool longAnimationFrameSourceCharPositionEnabled() {
    return RuntimeEnabledFeatures::LongAnimationFrameSourceCharPositionEnabled();
  }
  bool longAnimationFrameSourceLineColumnEnabled() {
    return RuntimeEnabledFeatures::LongAnimationFrameSourceLineColumnEnabled();
  }
  bool longAnimationFrameSourceLineColumnInterfaceEnabled() {
    return RuntimeEnabledFeatures::LongAnimationFrameSourceLineColumnInterfaceEnabled();
  }
  bool longAnimationFrameStyleDurationEnabled() {
    return RuntimeEnabledFeatures::LongAnimationFrameStyleDurationEnabledByRuntimeFlag();
  }
  bool longPressLinkSelectTextEnabled() {
    return RuntimeEnabledFeatures::LongPressLinkSelectTextEnabled();
  }
  bool longTaskFromLongAnimationFrameEnabled() {
    return RuntimeEnabledFeatures::LongTaskFromLongAnimationFrameEnabled();
  }
  bool macCharacterFallbackCacheEnabled() {
    return RuntimeEnabledFeatures::MacCharacterFallbackCacheEnabled();
  }
  bool macDisableCtrlHomeEndEnabled() {
    return RuntimeEnabledFeatures::MacDisableCtrlHomeEndEnabled();
  }
  bool machineLearningNeuralNetworkEnabled() {
    return RuntimeEnabledFeatures::MachineLearningNeuralNetworkEnabled();
  }
  bool macSystemClipboardPermissionCheckEnabled() {
    return RuntimeEnabledFeatures::MacSystemClipboardPermissionCheckEnabled();
  }
  bool managedConfigurationEnabled() {
    return RuntimeEnabledFeatures::ManagedConfigurationEnabled();
  }
  bool manualTextEnabled() {
    return RuntimeEnabledFeatures::ManualTextEnabled();
  }
  bool marginTrimEnabled() {
    return RuntimeEnabledFeatures::MarginTrimEnabled();
  }
  bool maskDeserializationTimeForCrossOriginMessagesEnabled() {
    return RuntimeEnabledFeatures::MaskDeserializationTimeForCrossOriginMessagesEnabled();
  }
  bool mathmlOperatorRTLMirroringEnabled() {
    return RuntimeEnabledFeatures::MathMLOperatorRTLMirroringEnabled();
  }
  bool mathmlSerializationOnCopyEnabled() {
    return RuntimeEnabledFeatures::MathMLSerializationOnCopyEnabled();
  }
  bool mathmlSkipMtrTagInAncestorWrappingEnabled() {
    return RuntimeEnabledFeatures::MathMLSkipMtrTagInAncestorWrappingEnabled();
  }
  bool measureMemoryEnabled() {
    return RuntimeEnabledFeatures::MeasureMemoryEnabled();
  }
  bool mediaCapabilitiesEncodingInfoEnabled() {
    return RuntimeEnabledFeatures::MediaCapabilitiesEncodingInfoEnabled();
  }
  bool mediaCapabilitiesSpatialAudioEnabled() {
    return RuntimeEnabledFeatures::MediaCapabilitiesSpatialAudioEnabled();
  }
  bool mediaCaptureEnabled() {
    return RuntimeEnabledFeatures::MediaCaptureEnabled();
  }
  bool mediaCaptureBackgroundBlurEnabled() {
    return RuntimeEnabledFeatures::MediaCaptureBackgroundBlurEnabledByRuntimeFlag();
  }
  bool mediaCaptureCameraControlsEnabled() {
    return RuntimeEnabledFeatures::MediaCaptureCameraControlsEnabled();
  }
  bool mediaCaptureConfigurationChangeEnabled() {
    return RuntimeEnabledFeatures::MediaCaptureConfigurationChangeEnabledByRuntimeFlag();
  }
  bool mediaCaptureVoiceIsolationEnabled() {
    return RuntimeEnabledFeatures::MediaCaptureVoiceIsolationEnabled();
  }
  bool mediaControlsExpandGestureEnabled() {
    return RuntimeEnabledFeatures::MediaControlsExpandGestureEnabled();
  }
  bool mediaControlsOverlayPlayButtonEnabled() {
    return RuntimeEnabledFeatures::MediaControlsOverlayPlayButtonEnabled();
  }
  bool mediaElementVolumeGreaterThanOneEnabled() {
    return RuntimeEnabledFeatures::MediaElementVolumeGreaterThanOneEnabled();
  }
  bool mediaEngagementBypassAutoplayPoliciesEnabled() {
    return RuntimeEnabledFeatures::MediaEngagementBypassAutoplayPoliciesEnabled();
  }
  bool mediaLatencyHintEnabled() {
    return RuntimeEnabledFeatures::MediaLatencyHintEnabled();
  }
  bool mediaPlaybackWhileNotVisiblePermissionPolicyEnabled() {
    return RuntimeEnabledFeatures::MediaPlaybackWhileNotVisiblePermissionPolicyEnabledByRuntimeFlag();
  }
  bool mediaQueryNavigationControlsEnabled() {
    return RuntimeEnabledFeatures::MediaQueryNavigationControlsEnabled();
  }
  bool mediaSessionEnabled() {
    return RuntimeEnabledFeatures::MediaSessionEnabled();
  }
  bool mediaSessionChapterInformationEnabled() {
    return RuntimeEnabledFeatures::MediaSessionChapterInformationEnabled();
  }
  bool mediaSourceExperimentalEnabled() {
    return RuntimeEnabledFeatures::MediaSourceExperimentalEnabled();
  }
  bool mediaSourceExtensionsForWebCodecsEnabled() {
    return RuntimeEnabledFeatures::MediaSourceExtensionsForWebCodecsEnabledByRuntimeFlag();
  }
  bool mediaStreamTrackTransferEnabled() {
    return RuntimeEnabledFeatures::MediaStreamTrackTransferEnabled();
  }
  bool mediaStreamTrackWebSpeechEnabled() {
    return RuntimeEnabledFeatures::MediaStreamTrackWebSpeechEnabled();
  }
  bool memoryConsumerForNGShapeCacheEnabled() {
    return RuntimeEnabledFeatures::MemoryConsumerForNGShapeCacheEnabled();
  }
  bool menuElementsEnabled() {
    return RuntimeEnabledFeatures::MenuElementsEnabled();
  }
  bool mergeFixedLayersEnabled() {
    return RuntimeEnabledFeatures::MergeFixedLayersEnabled();
  }
  bool mergeStickyLayersEnabled() {
    return RuntimeEnabledFeatures::MergeStickyLayersEnabled();
  }
  bool messagePortCloseEventEnabled() {
    return RuntimeEnabledFeatures::MessagePortCloseEventEnabled();
  }
  bool middleClickAutoscrollEnabled() {
    return RuntimeEnabledFeatures::MiddleClickAutoscrollEnabled();
  }
  bool mixedContentAutoupgradesUseIsMixedContentRestrictedInFrameEnabled() {
    return RuntimeEnabledFeatures::MixedContentAutoupgradesUseIsMixedContentRestrictedInFrameEnabled();
  }
  bool mobileLayoutThemeEnabled() {
    return RuntimeEnabledFeatures::MobileLayoutThemeEnabled();
  }
  bool modifyParagraphCrossEditingoundaryEnabled() {
    return RuntimeEnabledFeatures::ModifyParagraphCrossEditingoundaryEnabled();
  }
  bool modulePreloadReferrerEnabled() {
    return RuntimeEnabledFeatures::ModulePreloadReferrerEnabled();
  }
  bool modulePreloadStyleJsonEnabled() {
    return RuntimeEnabledFeatures::ModulePreloadStyleJsonEnabled();
  }
  bool mojoJSEnabled() {
    return RuntimeEnabledFeatures::MojoJSEnabled();
  }
  bool mojoJSTestEnabled() {
    return RuntimeEnabledFeatures::MojoJSTestEnabled();
  }
  bool moveEndingSelectionToListChildEnabled() {
    return RuntimeEnabledFeatures::MoveEndingSelectionToListChildEnabled();
  }
  bool multicolColumnWrappingEnabled() {
    return RuntimeEnabledFeatures::MulticolColumnWrappingEnabled();
  }
  bool navigateEventAddHandlerOnPrecommitEnabled() {
    return RuntimeEnabledFeatures::NavigateEventAddHandlerOnPrecommitEnabled();
  }
  bool navigateEventClearOnRestoreEnabled() {
    return RuntimeEnabledFeatures::NavigateEventClearOnRestoreEnabled();
  }
  bool navigateEventDeferCrossDocumentCommitEnabled() {
    return RuntimeEnabledFeatures::NavigateEventDeferCrossDocumentCommitEnabled();
  }
  bool navigationEventTimingEnabled() {
    return RuntimeEnabledFeatures::NavigationEventTimingEnabled();
  }
  bool navigationIdEnabled() {
    return RuntimeEnabledFeatures::NavigationIdEnabledByRuntimeFlag();
  }
  bool navigatorContentUtilsEnabled() {
    return RuntimeEnabledFeatures::NavigatorContentUtilsEnabled();
  }
  bool netInfoConstantTypeEnabled() {
    return RuntimeEnabledFeatures::NetInfoConstantTypeEnabled();
  }
  bool netInfoDownlinkMaxEnabled() {
    return RuntimeEnabledFeatures::NetInfoDownlinkMaxEnabled();
  }
  bool newHTMLSettingMethodsEnabled() {
    return RuntimeEnabledFeatures::NewHTMLSettingMethodsEnabled();
  }
  bool noExtendSelectionToUserSelectNoneOutOfFlowEnabled() {
    return RuntimeEnabledFeatures::NoExtendSelectionToUserSelectNoneOutOfFlowEnabled();
  }
  bool noFontAntialiasingEnabled() {
    return RuntimeEnabledFeatures::NoFontAntialiasingEnabled();
  }
  bool noIdleEncodingForWebTestsEnabled() {
    return RuntimeEnabledFeatures::NoIdleEncodingForWebTestsEnabled();
  }
  bool nonEmptyBlockquotesOnOutdentingEnabled() {
    return RuntimeEnabledFeatures::NonEmptyBlockquotesOnOutdentingEnabled();
  }
  bool nonEmptyVisibleTextSelectionForTextFragmentEnabled() {
    return RuntimeEnabledFeatures::NonEmptyVisibleTextSelectionForTextFragmentEnabled();
  }
  bool nonStandardAppearanceValueSliderVerticalEnabled() {
    return RuntimeEnabledFeatures::NonStandardAppearanceValueSliderVerticalEnabled();
  }
  bool normalizeLineEndingsInInsertTextEnabled() {
    return RuntimeEnabledFeatures::NormalizeLineEndingsInInsertTextEnabled();
  }
  bool normalizeNbspForPasteAndDropEnabled() {
    return RuntimeEnabledFeatures::NormalizeNbspForPasteAndDropEnabled();
  }
  bool notificationConstructorEnabled() {
    return RuntimeEnabledFeatures::NotificationConstructorEnabled();
  }
  bool notificationContentImageEnabled() {
    return RuntimeEnabledFeatures::NotificationContentImageEnabled();
  }
  bool notificationsEnabled() {
    return RuntimeEnabledFeatures::NotificationsEnabled();
  }
  bool notificationTriggersEnabled() {
    return RuntimeEnabledFeatures::NotificationTriggersEnabledByRuntimeFlag();
  }
  bool numberInputFullWidthCharsEnabled() {
    return RuntimeEnabledFeatures::NumberInputFullWidthCharsEnabled();
  }
  bool offMainThreadCSSPaintEnabled() {
    return RuntimeEnabledFeatures::OffMainThreadCSSPaintEnabled();
  }
  bool offscreenCanvasGetContextAttributesEnabled() {
    return RuntimeEnabledFeatures::OffscreenCanvasGetContextAttributesEnabled();
  }
  bool offsetPathTransformUpdateFixEnabled() {
    return RuntimeEnabledFeatures::OffsetPathTransformUpdateFixEnabled();
  }
  bool omitBlurEventOnElementRemovalEnabled() {
    return RuntimeEnabledFeatures::OmitBlurEventOnElementRemovalEnabled();
  }
  bool onDeviceWebSpeechAvailableEnabled() {
    return RuntimeEnabledFeatures::OnDeviceWebSpeechAvailableEnabled();
  }
  bool onDeviceWebSpeechQualityEnabled() {
    return RuntimeEnabledFeatures::OnDeviceWebSpeechQualityEnabled();
  }
  bool opaqueRangeEnabled() {
    return RuntimeEnabledFeatures::OpaqueRangeEnabledByRuntimeFlag();
  }
  bool openPopoverInvokerRestrictToSameTreeScopeEnabled() {
    return RuntimeEnabledFeatures::OpenPopoverInvokerRestrictToSameTreeScopeEnabled();
  }
  bool orientationEventEnabled() {
    return RuntimeEnabledFeatures::OrientationEventEnabled();
  }
  bool originAPIEnabled() {
    return RuntimeEnabledFeatures::OriginAPIEnabled();
  }
  bool originIsolationHeaderEnabled() {
    return RuntimeEnabledFeatures::OriginIsolationHeaderEnabled();
  }
  bool originPolicyEnabled() {
    return RuntimeEnabledFeatures::OriginPolicyEnabled();
  }
  bool originTrialsSampleAPIEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIBrowserReadWriteEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIBrowserReadWriteEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIDependentEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIDependentEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIDeprecationEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIDeprecationEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIExpiryGracePeriodEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIExpiryGracePeriodEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIExpiryGracePeriodThirdPartyEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIExpiryGracePeriodThirdPartyEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIImpliedEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIImpliedEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIInvalidOSEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIInvalidOSEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPINavigationEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPINavigationEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIPersistentExpiryGracePeriodEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIPersistentExpiryGracePeriodEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIPersistentFeatureEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIPersistentFeatureEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIPersistentInvalidOSEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIPersistentInvalidOSEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIPersistentThirdPartyDeprecationFeatureEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIPersistentThirdPartyDeprecationFeatureEnabledByRuntimeFlag();
  }
  bool originTrialsSampleAPIThirdPartyEnabled() {
    return RuntimeEnabledFeatures::OriginTrialsSampleAPIThirdPartyEnabledByRuntimeFlag();
  }
  bool outlineDrawAutoStyleZeroWidthEnabled() {
    return RuntimeEnabledFeatures::OutlineDrawAutoStyleZeroWidthEnabled();
  }
  bool overlayGlobalRuleRemovalEnabled() {
    return RuntimeEnabledFeatures::OverlayGlobalRuleRemovalEnabled();
  }
  bool overlayPropertyEnabled() {
    return RuntimeEnabledFeatures::OverlayPropertyEnabled();
  }
  bool overscrollGesturesEnabled() {
    return RuntimeEnabledFeatures::OverscrollGesturesEnabled();
  }
  bool pagePopupEnabled() {
    return RuntimeEnabledFeatures::PagePopupEnabled();
  }
  bool pagePopupCopyPasteEnabled() {
    return RuntimeEnabledFeatures::PagePopupCopyPasteEnabled();
  }
  bool pageRevealEventEnabled() {
    return RuntimeEnabledFeatures::PageRevealEventEnabled();
  }
  bool pageSwapEventEnabled() {
    return RuntimeEnabledFeatures::PageSwapEventEnabled();
  }
  bool paintHoldingForIframesEnabled() {
    return RuntimeEnabledFeatures::PaintHoldingForIframesEnabled();
  }
  bool paintOffsetTranslationForCompositedEnabled() {
    return RuntimeEnabledFeatures::PaintOffsetTranslationForCompositedEnabled();
  }
  bool paintTimingMixinEnabled() {
    return RuntimeEnabledFeatures::PaintTimingMixinEnabled();
  }
  bool paintUnderInvalidationCheckingEnabled() {
    return RuntimeEnabledFeatures::PaintUnderInvalidationCheckingEnabled();
  }
  bool parakeetEnabled() {
    return RuntimeEnabledFeatures::ParakeetEnabledByRuntimeFlag();
  }
  bool partialCompletionNotAllowedInMoveParagraphsEnabled() {
    return RuntimeEnabledFeatures::PartialCompletionNotAllowedInMoveParagraphsEnabled();
  }
  bool partitionVisitedLinkDatabaseWithSelfLinksEnabled() {
    return RuntimeEnabledFeatures::PartitionVisitedLinkDatabaseWithSelfLinksEnabled();
  }
  bool passwordRevealEnabled() {
    return RuntimeEnabledFeatures::PasswordRevealEnabled();
  }
  bool paymentAppEnabled() {
    return RuntimeEnabledFeatures::PaymentAppEnabled();
  }
  bool paymentLinkDetectionEnabled() {
    return RuntimeEnabledFeatures::PaymentLinkDetectionEnabled();
  }
  bool paymentMethodChangeEventEnabled() {
    return RuntimeEnabledFeatures::PaymentMethodChangeEventEnabled();
  }
  bool paymentRequestEnabled() {
    return RuntimeEnabledFeatures::PaymentRequestEnabled();
  }
  bool performanceManagerInstrumentationEnabled() {
    return RuntimeEnabledFeatures::PerformanceManagerInstrumentationEnabled();
  }
  bool performanceMarkCustomUserTimingFromSubframeEnabled() {
    return RuntimeEnabledFeatures::PerformanceMarkCustomUserTimingFromSubframeEnabled();
  }
  bool performanceMarkFeatureUsageEnabled() {
    return RuntimeEnabledFeatures::PerformanceMarkFeatureUsageEnabled();
  }
  bool performanceNavigationTimingConfidenceEnabled() {
    return RuntimeEnabledFeatures::PerformanceNavigationTimingConfidenceEnabled();
  }
  bool periodicBackgroundSyncEnabled() {
    return RuntimeEnabledFeatures::PeriodicBackgroundSyncEnabled();
  }
  bool perMethodCanMakePaymentQuotaEnabled() {
    return RuntimeEnabledFeatures::PerMethodCanMakePaymentQuotaEnabledByRuntimeFlag();
  }
  bool permissionsRequestRevokeEnabled() {
    return RuntimeEnabledFeatures::PermissionsRequestRevokeEnabled();
  }
  bool placeholderVisibilityEnabled() {
    return RuntimeEnabledFeatures::PlaceholderVisibilityEnabled();
  }
  bool pNaClEnabled() {
    return RuntimeEnabledFeatures::PNaClEnabledByRuntimeFlag();
  }
  bool pointerEventDeviceIdEnabled() {
    return RuntimeEnabledFeatures::PointerEventDeviceIdEnabled();
  }
  bool pointerLockOnAndroidEnabled() {
    return RuntimeEnabledFeatures::PointerLockOnAndroidEnabled();
  }
  bool pointerRawUpdateOnlyInSecureContextEnabled() {
    return RuntimeEnabledFeatures::PointerRawUpdateOnlyInSecureContextEnabled();
  }
  bool popoverHintNewBehaviorEnabled() {
    return RuntimeEnabledFeatures::PopoverHintNewBehaviorEnabled();
  }
  bool positionOutsideTabSpanCheckSiblingNodeEnabled() {
    return RuntimeEnabledFeatures::PositionOutsideTabSpanCheckSiblingNodeEnabled();
  }
  bool positionVisibilityIgnoreNonClipAncestorsEnabled() {
    return RuntimeEnabledFeatures::PositionVisibilityIgnoreNonClipAncestorsEnabled();
  }
  bool potentialPermissionsPolicyReportingEnabled() {
    return RuntimeEnabledFeatures::PotentialPermissionsPolicyReportingEnabled();
  }
  bool preciseMemoryInfoEnabled() {
    return RuntimeEnabledFeatures::PreciseMemoryInfoEnabled();
  }
  bool preferDefaultScrollbarStylesEnabled() {
    return RuntimeEnabledFeatures::PreferDefaultScrollbarStylesEnabled();
  }
  bool preferNonCompositedScrollingEnabled() {
    return RuntimeEnabledFeatures::PreferNonCompositedScrollingEnabled();
  }
  bool preferredAudioOutputDevicesEnabled() {
    return RuntimeEnabledFeatures::PreferredAudioOutputDevicesEnabledByRuntimeFlag();
  }
  bool prefersReducedDataEnabled() {
    return RuntimeEnabledFeatures::PrefersReducedDataEnabled();
  }
  bool preloadLinkRelDataUrlsEnabled() {
    return RuntimeEnabledFeatures::PreloadLinkRelDataUrlsEnabled();
  }
  bool prerender2Enabled() {
    return RuntimeEnabledFeatures::Prerender2Enabled();
  }
  bool prerender2CrossOriginIframesEnabled() {
    return RuntimeEnabledFeatures::Prerender2CrossOriginIframesEnabledByRuntimeFlag();
  }
  bool prerenderActivationByFormSubmissionEnabled() {
    return RuntimeEnabledFeatures::PrerenderActivationByFormSubmissionEnabledByRuntimeFlag();
  }
  bool prerenderUntilScriptEnabled() {
    return RuntimeEnabledFeatures::PrerenderUntilScriptEnabledByRuntimeFlag();
  }
  bool presentationEnabled() {
    return RuntimeEnabledFeatures::PresentationEnabled();
  }
  bool preserveDropEffectEnabled() {
    return RuntimeEnabledFeatures::PreserveDropEffectEnabled();
  }
  bool preventUndoIfNotEditableEnabled() {
    return RuntimeEnabledFeatures::PreventUndoIfNotEditableEnabled();
  }
  bool privateAggregationApiErrorReportingEnabled() {
    return RuntimeEnabledFeatures::PrivateAggregationApiErrorReportingEnabled();
  }
  bool privateAggregationApiMaxContributionsEnabled() {
    return RuntimeEnabledFeatures::PrivateAggregationApiMaxContributionsEnabled();
  }
  bool privateNetworkAccessNullIpAddressEnabled() {
    return RuntimeEnabledFeatures::PrivateNetworkAccessNullIpAddressEnabled();
  }
  bool privateStateTokensEnabled() {
    return RuntimeEnabledFeatures::PrivateStateTokensEnabled();
  }
  bool privateStateTokensAlwaysAllowIssuanceEnabled() {
    return RuntimeEnabledFeatures::PrivateStateTokensAlwaysAllowIssuanceEnabled();
  }
  bool profilerAPIEnabled() {
    return RuntimeEnabledFeatures::ProfilerAPIEnabled();
  }
  bool profilerAPIForDedicatedWorkerEnabled() {
    return RuntimeEnabledFeatures::ProfilerAPIForDedicatedWorkerEnabled();
  }
  bool programmaticScrollPromiseEnabled() {
    return RuntimeEnabledFeatures::ProgrammaticScrollPromiseEnabled();
  }
  bool progressMaxIsPositiveEnabled() {
    return RuntimeEnabledFeatures::ProgressMaxIsPositiveEnabled();
  }
  bool propagateOverscrollBehaviorFromRootEnabled() {
    return RuntimeEnabledFeatures::PropagateOverscrollBehaviorFromRootEnabled();
  }
  bool protectedOriginTrialsSampleAPIEnabled() {
    return RuntimeEnabledFeatures::ProtectedOriginTrialsSampleAPIEnabledByRuntimeFlag();
  }
  bool protectedOriginTrialsSampleAPIDependentEnabled() {
    return RuntimeEnabledFeatures::ProtectedOriginTrialsSampleAPIDependentEnabledByRuntimeFlag();
  }
  bool protectedOriginTrialsSampleAPIImpliedEnabled() {
    return RuntimeEnabledFeatures::ProtectedOriginTrialsSampleAPIImpliedEnabledByRuntimeFlag();
  }
  bool pseudoElementsFocusableEnabled() {
    return RuntimeEnabledFeatures::PseudoElementsFocusableEnabled();
  }
  bool pseudoElementsHitTestableEnabled() {
    return RuntimeEnabledFeatures::PseudoElementsHitTestableEnabled();
  }
  bool pseudoElementsHoverableEnabled() {
    return RuntimeEnabledFeatures::PseudoElementsHoverableEnabled();
  }
  bool pushMessageDataBytesEnabled() {
    return RuntimeEnabledFeatures::PushMessageDataBytesEnabled();
  }
  bool pushMessagingEnabled() {
    return RuntimeEnabledFeatures::PushMessagingEnabled();
  }
  bool pushMessagingSubscriptionChangeEnabled() {
    return RuntimeEnabledFeatures::PushMessagingSubscriptionChangeEnabled();
  }
  bool quotaExceededErrorUpdateEnabled() {
    return RuntimeEnabledFeatures::QuotaExceededErrorUpdateEnabled();
  }
  bool quoteFirstLineStyleEnabled() {
    return RuntimeEnabledFeatures::QuoteFirstLineStyleEnabled();
  }
  bool rasterInducingScrollEnabled() {
    return RuntimeEnabledFeatures::RasterInducingScrollEnabled();
  }
  bool readableStreamBYOBReaderReadMinOptionEnabled() {
    return RuntimeEnabledFeatures::ReadableStreamBYOBReaderReadMinOptionEnabled();
  }
  bool readClipboardDataOnClipboardItemGetTypeEnabled() {
    return RuntimeEnabledFeatures::ReadClipboardDataOnClipboardItemGetTypeEnabled();
  }
  bool readingFlowWithSlotsEnabled() {
    return RuntimeEnabledFeatures::ReadingFlowWithSlotsEnabled();
  }
  bool recheckParentDuringNodeVectorInsertionEnabled() {
    return RuntimeEnabledFeatures::RecheckParentDuringNodeVectorInsertionEnabled();
  }
  bool recordSameDocumentPresentationTimeOnceEnabled() {
    return RuntimeEnabledFeatures::RecordSameDocumentPresentationTimeOnceEnabled();
  }
  bool reduceAcceptLanguageEnabled() {
    return RuntimeEnabledFeatures::ReduceAcceptLanguageEnabled();
  }
  bool reduceUserAgentDataLinuxPlatformVersionEnabled() {
    return RuntimeEnabledFeatures::ReduceUserAgentDataLinuxPlatformVersionEnabled();
  }
  bool reduceUserAgentMinorVersionEnabled() {
    return RuntimeEnabledFeatures::ReduceUserAgentMinorVersionEnabled();
  }
  bool regionCaptureEnabled() {
    return RuntimeEnabledFeatures::RegionCaptureEnabled();
  }
  bool relatedWebsitePartitionAPIEnabled() {
    return RuntimeEnabledFeatures::RelatedWebsitePartitionAPIEnabled();
  }
  bool relOpenerBcgDependencyHintEnabled() {
    return RuntimeEnabledFeatures::RelOpenerBcgDependencyHintEnabled();
  }
  bool remotePlaybackEnabled() {
    return RuntimeEnabledFeatures::RemotePlaybackEnabled();
  }
  bool remotePlaybackBackendEnabled() {
    return RuntimeEnabledFeatures::RemotePlaybackBackendEnabled();
  }
  bool removeCharsetAutoDetectionForISO2022JPEnabled() {
    return RuntimeEnabledFeatures::RemoveCharsetAutoDetectionForISO2022JPEnabled();
  }
  bool removeChildrenInReplaceChildrenEnabled() {
    return RuntimeEnabledFeatures::RemoveChildrenInReplaceChildrenEnabled();
  }
  bool removeCollapsedPlaceholderForContentEditableEnabled() {
    return RuntimeEnabledFeatures::RemoveCollapsedPlaceholderForContentEditableEnabled();
  }
  bool removeDanglingMarkupInTargetEnabled() {
    return RuntimeEnabledFeatures::RemoveDanglingMarkupInTargetEnabled();
  }
  bool removeDataUrlInSvgUseEnabled() {
    return RuntimeEnabledFeatures::RemoveDataUrlInSvgUseEnabled();
  }
  bool removeFormatFilterBackgroundColorEnabled() {
    return RuntimeEnabledFeatures::RemoveFormatFilterBackgroundColorEnabled();
  }
  bool removeNonAllowlistedCreateEventEnabled() {
    return RuntimeEnabledFeatures::RemoveNonAllowlistedCreateEventEnabled();
  }
  bool removeScrollNodeWorkaroundEnabled() {
    return RuntimeEnabledFeatures::RemoveScrollNodeWorkaroundEnabled();
  }
  bool removeSelectionCanonicalizationInMoveParagraphEnabled() {
    return RuntimeEnabledFeatures::RemoveSelectionCanonicalizationInMoveParagraphEnabled();
  }
  bool removeVisibleSelectionInDOMSelectionEnabled() {
    return RuntimeEnabledFeatures::RemoveVisibleSelectionInDOMSelectionEnabled();
  }
  bool renderBlockingFullFrameRateEnabled() {
    return RuntimeEnabledFeatures::RenderBlockingFullFrameRateEnabledByRuntimeFlag();
  }
  bool renderBlockingStatusEnabled() {
    return RuntimeEnabledFeatures::RenderBlockingStatusEnabled();
  }
  bool renderPriorityAttributeEnabled() {
    return RuntimeEnabledFeatures::RenderPriorityAttributeEnabled();
  }
  bool reportFirstFrameTimeAsRenderTimeEnabled() {
    return RuntimeEnabledFeatures::ReportFirstFrameTimeAsRenderTimeEnabled();
  }
  bool reportLayoutShiftRectsInCssPixelsEnabled() {
    return RuntimeEnabledFeatures::ReportLayoutShiftRectsInCssPixelsEnabled();
  }
  bool requestIsReloadNavigationEnabled() {
    return RuntimeEnabledFeatures::RequestIsReloadNavigationEnabled();
  }
  bool requestMainFrameAfterFirstVideoFrameEnabled() {
    return RuntimeEnabledFeatures::RequestMainFrameAfterFirstVideoFrameEnabled();
  }
  bool resolveVarStylesOnCopyEnabled() {
    return RuntimeEnabledFeatures::ResolveVarStylesOnCopyEnabled();
  }
  bool resourceTimingContentEncodingEnabled() {
    return RuntimeEnabledFeatures::ResourceTimingContentEncodingEnabled();
  }
  bool resourceTimingContentTypeEnabled() {
    return RuntimeEnabledFeatures::ResourceTimingContentTypeEnabled();
  }
  bool resourceTimingInitiatorEnabled() {
    return RuntimeEnabledFeatures::ResourceTimingInitiatorEnabled();
  }
  bool resourceTimingUseCORSForBodySizesEnabled() {
    return RuntimeEnabledFeatures::ResourceTimingUseCORSForBodySizesEnabled();
  }
  bool respectOverscrollBehaviorForScrollBubblingEnabled() {
    return RuntimeEnabledFeatures::RespectOverscrollBehaviorForScrollBubblingEnabled();
  }
  bool responsiveIframesEnabled() {
    return RuntimeEnabledFeatures::ResponsiveIframesEnabled();
  }
  bool restrictGamepadAccessEnabled() {
    return RuntimeEnabledFeatures::RestrictGamepadAccessEnabled();
  }
  bool restrictOwnAudioEnabled() {
    return RuntimeEnabledFeatures::RestrictOwnAudioEnabled();
  }
  bool rootScrollbarFollowsBrowserThemeEnabled() {
    return RuntimeEnabledFeatures::RootScrollbarFollowsBrowserThemeEnabled();
  }
  bool routeMatchingEnabled() {
    return RuntimeEnabledFeatures::RouteMatchingEnabled();
  }
  bool rtcAlwaysNegotiateDataChannelsEnabled() {
    return RuntimeEnabledFeatures::RtcAlwaysNegotiateDataChannelsEnabled();
  }
  bool rtcAudioJitterBufferMaxPacketsEnabled() {
    return RuntimeEnabledFeatures::RtcAudioJitterBufferMaxPacketsEnabledByRuntimeFlag();
  }
  bool rtcDataChannelPriorityEnabled() {
    return RuntimeEnabledFeatures::RTCDataChannelPriorityEnabled();
  }
  bool rtcDiagnosticLoggingEnabled() {
    return RuntimeEnabledFeatures::RTCDiagnosticLoggingEnabled();
  }
  bool rtcEncodedFrameAudioLevelEnabled() {
    return RuntimeEnabledFeatures::RTCEncodedFrameAudioLevelEnabled();
  }
  bool rtcEncodedFrameSetMetadataEnabled() {
    return RuntimeEnabledFeatures::RTCEncodedFrameSetMetadataEnabledByRuntimeFlag();
  }
  bool rtcEncodedFrameTimestampsEnabled() {
    return RuntimeEnabledFeatures::RTCEncodedFrameTimestampsEnabled();
  }
  bool rtcEncodedVideoFrameAdditionalMetadataEnabled() {
    return RuntimeEnabledFeatures::RTCEncodedVideoFrameAdditionalMetadataEnabled();
  }
  bool rtcJitterBufferTargetEnabled() {
    return RuntimeEnabledFeatures::RTCJitterBufferTargetEnabled();
  }
  bool rtcLegacyCallbackBasedGetStatsEnabled() {
    return RuntimeEnabledFeatures::RTCLegacyCallbackBasedGetStatsEnabledByRuntimeFlag();
  }
  bool rtcRtpEncodingParametersCodecEnabled() {
    return RuntimeEnabledFeatures::RTCRtpEncodingParametersCodecEnabled();
  }
  bool rtcRtpScaleResolutionDownToEnabled() {
    return RuntimeEnabledFeatures::RTCRtpScaleResolutionDownToEnabled();
  }
  bool rtcRtpScriptTransformEnabled() {
    return RuntimeEnabledFeatures::RTCRtpScriptTransformEnabled();
  }
  bool rtcRtpTransportEnabled() {
    return RuntimeEnabledFeatures::RTCRtpTransportEnabled();
  }
  bool rtcStatsRelativePacketArrivalDelayEnabled() {
    return RuntimeEnabledFeatures::RTCStatsRelativePacketArrivalDelayEnabledByRuntimeFlag();
  }
  bool rtcSvcScalabilityModeEnabled() {
    return RuntimeEnabledFeatures::RTCSvcScalabilityModeEnabled();
  }
  bool runMicrotaskBeforeXmlScriptEnabled() {
    return RuntimeEnabledFeatures::RunMicrotaskBeforeXmlScriptEnabled();
  }
  bool runSnapshotPostLayoutStateStepsEnabled() {
    return RuntimeEnabledFeatures::RunSnapshotPostLayoutStateStepsEnabled();
  }
  bool sanitizerAPIEnabled() {
    return RuntimeEnabledFeatures::SanitizerAPIEnabled();
  }
  bool scopedCustomElementRegistryEnabled() {
    return RuntimeEnabledFeatures::ScopedCustomElementRegistryEnabled();
  }
  bool scopedViewTransitionsEnabled() {
    return RuntimeEnabledFeatures::ScopedViewTransitionsEnabled();
  }
  bool screenDetailedHdrHeadroomEnabled() {
    return RuntimeEnabledFeatures::ScreenDetailedHdrHeadroomEnabled();
  }
  bool scriptBasedOnUnicodeBlockEnabled() {
    return RuntimeEnabledFeatures::ScriptBasedOnUnicodeBlockEnabled();
  }
  bool scriptedSpeechRecognitionEnabled() {
    return RuntimeEnabledFeatures::ScriptedSpeechRecognitionEnabled();
  }
  bool scriptedSpeechSynthesisEnabled() {
    return RuntimeEnabledFeatures::ScriptedSpeechSynthesisEnabled();
  }
  bool scrollAnchorPriorityCandidateSubtreeEnabled() {
    return RuntimeEnabledFeatures::ScrollAnchorPriorityCandidateSubtreeEnabled();
  }
  bool scrollAnchorSerializationUseParentForTextNodeEnabled() {
    return RuntimeEnabledFeatures::ScrollAnchorSerializationUseParentForTextNodeEnabled();
  }
  bool scrollbarColorEnabled() {
    return RuntimeEnabledFeatures::ScrollbarColorEnabled();
  }
  bool scrollbarGutterBugFixEnabled() {
    return RuntimeEnabledFeatures::ScrollbarGutterBugFixEnabled();
  }
  bool scrollbarWidthEnabled() {
    return RuntimeEnabledFeatures::ScrollbarWidthEnabled();
  }
  bool scrollIntoViewNearestEnabled() {
    return RuntimeEnabledFeatures::ScrollIntoViewNearestEnabled();
  }
  bool scrollIntoViewRootFrameViewportBugFixEnabled() {
    return RuntimeEnabledFeatures::ScrollIntoViewRootFrameViewportBugFixEnabled();
  }
  bool scrollTimelineCurrentTimeEnabled() {
    return RuntimeEnabledFeatures::ScrollTimelineCurrentTimeEnabled();
  }
  bool scrollTimelineNamedRangeScrollEnabled() {
    return RuntimeEnabledFeatures::ScrollTimelineNamedRangeScrollEnabled();
  }
  bool scrollTopLeftInteropEnabled() {
    return RuntimeEnabledFeatures::ScrollTopLeftInteropEnabled();
  }
  bool scrollToTextFragmentUniqueFragmentsEnabled() {
    return RuntimeEnabledFeatures::ScrollToTextFragmentUniqueFragmentsEnabled();
  }
  bool searchTextHighlightPseudoEnabled() {
    return RuntimeEnabledFeatures::SearchTextHighlightPseudoEnabled();
  }
  bool securePaymentConfirmationEnabled() {
    return RuntimeEnabledFeatures::SecurePaymentConfirmationEnabled();
  }
  bool securePaymentConfirmationAvailabilityAPIEnabled() {
    return RuntimeEnabledFeatures::SecurePaymentConfirmationAvailabilityAPIEnabled();
  }
  bool securePaymentConfirmationCapabilitiesEnabled() {
    return RuntimeEnabledFeatures::SecurePaymentConfirmationCapabilitiesEnabled();
  }
  bool securePaymentConfirmationDebugEnabled() {
    return RuntimeEnabledFeatures::SecurePaymentConfirmationDebugEnabled();
  }
  bool securePaymentConfirmationOptOutEnabled() {
    return RuntimeEnabledFeatures::SecurePaymentConfirmationOptOutEnabledByRuntimeFlag();
  }
  bool selectAudioOutputEnabled() {
    return RuntimeEnabledFeatures::SelectAudioOutputEnabled();
  }
  bool selectedcontentelementAttributeEnabled() {
    return RuntimeEnabledFeatures::SelectedcontentelementAttributeEnabled();
  }
  bool selectedcontentMultipleEnabled() {
    return RuntimeEnabledFeatures::SelectedcontentMultipleEnabled();
  }
  bool selectedcontentSpecEnabled() {
    return RuntimeEnabledFeatures::SelectedcontentSpecEnabled();
  }
  bool selectionAndFocusedVisiblePositionMatchEnabled() {
    return RuntimeEnabledFeatures::SelectionAndFocusedVisiblePositionMatchEnabled();
  }
  bool selectionCollapsedDirectionNoneEnabled() {
    return RuntimeEnabledFeatures::SelectionCollapsedDirectionNoneEnabled();
  }
  bool selectionFocusAffinityEnabled() {
    return RuntimeEnabledFeatures::SelectionFocusAffinityEnabled();
  }
  bool selectionHandleWithBottomClippedEnabled() {
    return RuntimeEnabledFeatures::SelectionHandleWithBottomClippedEnabled();
  }
  bool selectionRemoveRangeNotFoundErrorEnabled() {
    return RuntimeEnabledFeatures::SelectionRemoveRangeNotFoundErrorEnabled();
  }
  bool selectionSetBaseAndExtentNonNullNodeEnabled() {
    return RuntimeEnabledFeatures::SelectionSetBaseAndExtentNonNullNodeEnabled();
  }
  bool selectionToStringSkipsUserSelectNoneEnabled() {
    return RuntimeEnabledFeatures::SelectionToStringSkipsUserSelectNoneEnabled();
  }
  bool selectionUpdateOnlyAfterAutoscrollEnabled() {
    return RuntimeEnabledFeatures::SelectionUpdateOnlyAfterAutoscrollEnabled();
  }
  bool selectionUpdateToInitialSelectionInListifyEnabled() {
    return RuntimeEnabledFeatures::SelectionUpdateToInitialSelectionInListifyEnabled();
  }
  bool selectiveClipboardFormatReadEnabled() {
    return RuntimeEnabledFeatures::SelectiveClipboardFormatReadEnabled();
  }
  bool selectivePermissionsInterventionEnabled() {
    return RuntimeEnabledFeatures::SelectivePermissionsInterventionEnabled();
  }
  bool selectRemoveOverflowHiddenEnabled() {
    return RuntimeEnabledFeatures::SelectRemoveOverflowHiddenEnabled();
  }
  bool sendBeaconThrowForBlobWithNonSimpleTypeEnabled() {
    return RuntimeEnabledFeatures::SendBeaconThrowForBlobWithNonSimpleTypeEnabled();
  }
  bool sendSlotChangeSignalAfterNodeInsertedEnabled() {
    return RuntimeEnabledFeatures::SendSlotChangeSignalAfterNodeInsertedEnabled();
  }
  bool sensorExtraClassesEnabled() {
    return RuntimeEnabledFeatures::SensorExtraClassesEnabled();
  }
  bool separateDeferModuleScriptTasksEnabled() {
    return RuntimeEnabledFeatures::SeparateDeferModuleScriptTasksEnabled();
  }
  bool serialEnabled() {
    return RuntimeEnabledFeatures::SerialEnabled();
  }
  bool serializeViewTransitionStateInSPAEnabled() {
    return RuntimeEnabledFeatures::SerializeViewTransitionStateInSPAEnabled();
  }
  bool serialPortConnectedEnabled() {
    return RuntimeEnabledFeatures::SerialPortConnectedEnabled();
  }
  bool serviceWorkerBackgroundSyncInDedicatedWorkerEnabled() {
    return RuntimeEnabledFeatures::ServiceWorkerBackgroundSyncInDedicatedWorkerEnabled();
  }
  bool serviceWorkerClientLifecycleStateEnabled() {
    return RuntimeEnabledFeatures::ServiceWorkerClientLifecycleStateEnabled();
  }
  bool serviceWorkerInDedicatedWorkerEnabled() {
    return RuntimeEnabledFeatures::ServiceWorkerInDedicatedWorkerEnabled();
  }
  bool serviceWorkerStaticRouterTimingInfoEnabled() {
    return RuntimeEnabledFeatures::ServiceWorkerStaticRouterTimingInfoEnabled();
  }
  bool setDefaultDropEffectEnabled() {
    return RuntimeEnabledFeatures::SetDefaultDropEffectEnabled();
  }
  bool setHTMLCanRunScriptsEnabled() {
    return RuntimeEnabledFeatures::SetHTMLCanRunScriptsEnabled();
  }
  bool setSequentialFocusStartingPointEnabled() {
    return RuntimeEnabledFeatures::SetSequentialFocusStartingPointEnabled();
  }
  bool shadowContourFollowsBorderEnabled() {
    return RuntimeEnabledFeatures::ShadowContourFollowsBorderEnabled();
  }
  bool shadowRootAdoptedStyleSheetEnabled() {
    return RuntimeEnabledFeatures::ShadowRootAdoptedStyleSheetEnabledByRuntimeFlag();
  }
  bool shadowRootReferenceTargetEnabled() {
    return RuntimeEnabledFeatures::ShadowRootReferenceTargetEnabledByRuntimeFlag();
  }
  bool shadowRootReferenceTargetAriaOwnsEnabled() {
    return RuntimeEnabledFeatures::ShadowRootReferenceTargetAriaOwnsEnabled();
  }
  bool sharedArrayBufferEnabled() {
    return RuntimeEnabledFeatures::SharedArrayBufferEnabled();
  }
  bool sharedArrayBufferUnrestrictedAccessAllowedEnabled() {
    return RuntimeEnabledFeatures::SharedArrayBufferUnrestrictedAccessAllowedEnabled();
  }
  bool sharedStorageAPIEnabled() {
    return RuntimeEnabledFeatures::SharedStorageAPIEnabled();
  }
  bool sharedStorageWebLocksEnabled() {
    return RuntimeEnabledFeatures::SharedStorageWebLocksEnabled();
  }
  bool sharedWorkerEnabled() {
    return RuntimeEnabledFeatures::SharedWorkerEnabled();
  }
  bool sharedWorkerExtendedLifetimeEnabled() {
    return RuntimeEnabledFeatures::SharedWorkerExtendedLifetimeEnabledByRuntimeFlag();
  }
  bool sideRelativeBackgroundPositionEnabled() {
    return RuntimeEnabledFeatures::SideRelativeBackgroundPositionEnabled();
  }
  bool signatureBasedInlineIntegrityEnabled() {
    return RuntimeEnabledFeatures::SignatureBasedInlineIntegrityEnabled();
  }
  bool singleAxisScrollContainersEnabled() {
    return RuntimeEnabledFeatures::SingleAxisScrollContainersEnabled();
  }
  bool skipAdEnabled() {
    return RuntimeEnabledFeatures::SkipAdEnabled();
  }
  bool skipCallbacksWhenDevToolsNotOpenEnabled() {
    return RuntimeEnabledFeatures::SkipCallbacksWhenDevToolsNotOpenEnabled();
  }
  bool skipEventCaptureEnabled() {
    return RuntimeEnabledFeatures::SkipEventCaptureEnabled();
  }
  bool skipNonEditableInAtomicMoveEnabled() {
    return RuntimeEnabledFeatures::SkipNonEditableInAtomicMoveEnabled();
  }
  bool skipOofItemForBreakCandidateEnabled() {
    return RuntimeEnabledFeatures::SkipOofItemForBreakCandidateEnabled();
  }
  bool skipParagraphSplitForInlineInsertHTMLEnabled() {
    return RuntimeEnabledFeatures::SkipParagraphSplitForInlineInsertHTMLEnabled();
  }
  bool skipPseudoOnlyLinesInLineNavigationEnabled() {
    return RuntimeEnabledFeatures::SkipPseudoOnlyLinesInLineNavigationEnabled();
  }
  bool skipTouchEventFilterEnabled() {
    return RuntimeEnabledFeatures::SkipTouchEventFilterEnabled();
  }
  bool skipUnselectableContentInSerializationEnabled() {
    return RuntimeEnabledFeatures::SkipUnselectableContentInSerializationEnabled();
  }
  bool skipUnselectableElementsInParagraphBoundaryEnabled() {
    return RuntimeEnabledFeatures::SkipUnselectableElementsInParagraphBoundaryEnabled();
  }
  bool smallerViewportUnitsEnabled() {
    return RuntimeEnabledFeatures::SmallerViewportUnitsEnabled();
  }
  bool smartCardEnabled() {
    return RuntimeEnabledFeatures::SmartCardEnabled();
  }
  bool smartZoomEnabled() {
    return RuntimeEnabledFeatures::SmartZoomEnabled();
  }
  bool snapshotScrollTimelinesPostLayoutEnabled() {
    return RuntimeEnabledFeatures::SnapshotScrollTimelinesPostLayoutEnabled();
  }
  bool softNavigationDetectionEnabled() {
    return RuntimeEnabledFeatures::SoftNavigationDetectionEnabled();
  }
  bool softNavigationDetectionIncludeReplaceStateEnabled() {
    return RuntimeEnabledFeatures::SoftNavigationDetectionIncludeReplaceStateEnabled();
  }
  bool softNavigationHeuristicsEnabled() {
    return RuntimeEnabledFeatures::SoftNavigationHeuristicsEnabledByRuntimeFlag();
  }
  bool sortedLayoutShiftSourcesByImpactAreaEnabled() {
    return RuntimeEnabledFeatures::SortedLayoutShiftSourcesByImpactAreaEnabled();
  }
  bool sourceSpecificMulticastInDirectSocketsEnabled() {
    return RuntimeEnabledFeatures::SourceSpecificMulticastInDirectSocketsEnabled();
  }
  bool spatNavUsesCursorInheritanceEnabled() {
    return RuntimeEnabledFeatures::SpatNavUsesCursorInheritanceEnabled();
  }
  bool speakerSelectionEnabled() {
    return RuntimeEnabledFeatures::SpeakerSelectionEnabled();
  }
  bool speculationMeasurementEnabled() {
    return RuntimeEnabledFeatures::SpeculationMeasurementEnabled();
  }
  bool spellCheckCustomDictionaryAPIEnabled() {
    return RuntimeEnabledFeatures::SpellCheckCustomDictionaryAPIEnabled();
  }
  bool splitTextNotCleanupDummySpansEnabled() {
    return RuntimeEnabledFeatures::SplitTextNotCleanupDummySpansEnabled();
  }
  bool splitViewLinkOpenEnabled() {
    return RuntimeEnabledFeatures::SplitViewLinkOpenEnabled();
  }
  bool srcsetSelectionMatchesImageSetEnabled() {
    return RuntimeEnabledFeatures::SrcsetSelectionMatchesImageSetEnabled();
  }
  bool stableBlinkFeaturesEnabled() {
    return RuntimeEnabledFeatures::StableBlinkFeaturesEnabled();
  }
  bool stackingContextIsNotStackedEnabled() {
    return RuntimeEnabledFeatures::StackingContextIsNotStackedEnabled();
  }
  bool standardizedBrowserZoomEnabled() {
    return RuntimeEnabledFeatures::StandardizedBrowserZoomEnabled();
  }
  bool standardizedBrowserZoomOptOutEnabled() {
    return RuntimeEnabledFeatures::StandardizedBrowserZoomOptOutEnabledByRuntimeFlag();
  }
  bool stickyPositionHasOverflowPerAxisEnabled() {
    return RuntimeEnabledFeatures::StickyPositionHasOverflowPerAxisEnabled();
  }
  bool stickyUserActivationAcrossSameOriginNavigationEnabled() {
    return RuntimeEnabledFeatures::StickyUserActivationAcrossSameOriginNavigationEnabled();
  }
  bool storageBucketsEnabled() {
    return RuntimeEnabledFeatures::StorageBucketsEnabled();
  }
  bool storageBucketsDurabilityEnabled() {
    return RuntimeEnabledFeatures::StorageBucketsDurabilityEnabled();
  }
  bool storageBucketsLocksEnabled() {
    return RuntimeEnabledFeatures::StorageBucketsLocksEnabled();
  }
  bool streamingSanitizerEnabled() {
    return RuntimeEnabledFeatures::StreamingSanitizerEnabled();
  }
  bool strictMimeTypesForWorkersEnabled() {
    return RuntimeEnabledFeatures::StrictMimeTypesForWorkersEnabled();
  }
  bool stylusHandwritingEnabled() {
    return RuntimeEnabledFeatures::StylusHandwritingEnabled();
  }
  bool subAppsEnabled() {
    return RuntimeEnabledFeatures::SubAppsEnabled();
  }
  bool suppressPointerStreamAfterDragEnabled() {
    return RuntimeEnabledFeatures::SuppressPointerStreamAfterDragEnabled();
  }
  bool svgAnchorElementAttributesEnabled() {
    return RuntimeEnabledFeatures::SvgAnchorElementAttributesEnabled();
  }
  bool svgAnchorElementDownloadAttributeEnabled() {
    return RuntimeEnabledFeatures::SvgAnchorElementDownloadAttributeEnabled();
  }
  bool svgAnimateMotionDiscreteCalcModeEnabled() {
    return RuntimeEnabledFeatures::SvgAnimateMotionDiscreteCalcModeEnabled();
  }
  bool svgAvoidResettingFilterQualityForTiledPatternEnabled() {
    return RuntimeEnabledFeatures::SvgAvoidResettingFilterQualityForTiledPatternEnabled();
  }
  bool svgEmbeddedAsReplacedElementEnabled() {
    return RuntimeEnabledFeatures::SVGEmbeddedAsReplacedElementEnabled();
  }
  bool svgEnableTextDecorationCssStylingEnabled() {
    return RuntimeEnabledFeatures::SvgEnableTextDecorationCssStylingEnabled();
  }
  bool svgFallBackToContainerSizeEnabled() {
    return RuntimeEnabledFeatures::SvgFallBackToContainerSizeEnabled();
  }
  bool svgFeImageSkipHiddenContainerViewportDependenceEnabled() {
    return RuntimeEnabledFeatures::SvgFeImageSkipHiddenContainerViewportDependenceEnabled();
  }
  bool svgFilterPaintsForHiddenContentEnabled() {
    return RuntimeEnabledFeatures::SvgFilterPaintsForHiddenContentEnabled();
  }
  bool svgFilterUserSpaceViewportForSvgEnabled() {
    return RuntimeEnabledFeatures::SvgFilterUserSpaceViewportForSvgEnabled();
  }
  bool svgIgnoreNegativeEllipseRadiiEnabled() {
    return RuntimeEnabledFeatures::SvgIgnoreNegativeEllipseRadiiEnabled();
  }
  bool svgInlineRootPixelSnappingScaleAdjustmentEnabled() {
    return RuntimeEnabledFeatures::SvgInlineRootPixelSnappingScaleAdjustmentEnabled();
  }
  bool svgLengthListClearOnParsingFailureEnabled() {
    return RuntimeEnabledFeatures::SvgLengthListClearOnParsingFailureEnabled();
  }
  bool svgLengthResolveUnparsedValueEnabled() {
    return RuntimeEnabledFeatures::SvgLengthResolveUnparsedValueEnabled();
  }
  bool svgNumberListClearOnParsingFailureEnabled() {
    return RuntimeEnabledFeatures::SvgNumberListClearOnParsingFailureEnabled();
  }
  bool svgPartitionSVGDocumentResourcesInMemoryCacheEnabled() {
    return RuntimeEnabledFeatures::SvgPartitionSVGDocumentResourcesInMemoryCacheEnabled();
  }
  bool svgPathLengthCssPropertyEnabled() {
    return RuntimeEnabledFeatures::SvgPathLengthCssPropertyEnabled();
  }
  bool svgPointListClearOnParsingFailureEnabled() {
    return RuntimeEnabledFeatures::SvgPointListClearOnParsingFailureEnabled();
  }
  bool svgScriptElementAsyncAttributeEnabled() {
    return RuntimeEnabledFeatures::SvgScriptElementAsyncAttributeEnabled();
  }
  bool svgSizingWithPreserveAspectRatioNoneEnabled() {
    return RuntimeEnabledFeatures::SvgSizingWithPreserveAspectRatioNoneEnabled();
  }
  bool svgSmilClockValueValidationEnabled() {
    return RuntimeEnabledFeatures::SvgSmilClockValueValidationEnabled();
  }
  bool svgTextPathPathAttributeEnabled() {
    return RuntimeEnabledFeatures::SvgTextPathPathAttributeEnabled();
  }
  bool svgTransformOnNestedSvgElementEnabled() {
    return RuntimeEnabledFeatures::SvgTransformOnNestedSvgElementEnabled();
  }
  bool synthesizedKeyboardEventsForAccessibilityActionsEnabled() {
    return RuntimeEnabledFeatures::SynthesizedKeyboardEventsForAccessibilityActionsEnabled();
  }
  bool syntheticMouseHoverOverInactivePageEnabled() {
    return RuntimeEnabledFeatures::SyntheticMouseHoverOverInactivePageEnabled();
  }
  bool systemDefaultAccentColorsEnabled() {
    return RuntimeEnabledFeatures::SystemDefaultAccentColorsEnabled();
  }
  bool systemFallbackEmojiVSSupportEnabled() {
    return RuntimeEnabledFeatures::SystemFallbackEmojiVSSupportEnabled();
  }
  bool systemWakeLockEnabled() {
    return RuntimeEnabledFeatures::SystemWakeLockEnabled();
  }
  bool tableBorderColorNoImplicitBorderEnabled() {
    return RuntimeEnabledFeatures::TableBorderColorNoImplicitBorderEnabled();
  }
  bool tableDefaultBorderColorCurrentColorEnabled() {
    return RuntimeEnabledFeatures::TableDefaultBorderColorCurrentColorEnabled();
  }
  bool tableIsAutoFixedLayoutEnabled() {
    return RuntimeEnabledFeatures::TableIsAutoFixedLayoutEnabled();
  }
  bool tabSizeAncestorEnabled() {
    return RuntimeEnabledFeatures::TabSizeAncestorEnabled();
  }
  bool tabSizeWithSpacingEnabled() {
    return RuntimeEnabledFeatures::TabSizeWithSpacingEnabled();
  }
  bool targetInShadowDeterminedBeforeListenerEnabled() {
    return RuntimeEnabledFeatures::TargetInShadowDeterminedBeforeListenerEnabled();
  }
  bool testBlinkFeatureDefaultEnabled() {
    return RuntimeEnabledFeatures::TestBlinkFeatureDefaultEnabled();
  }
  bool testFeatureEnabled() {
    return RuntimeEnabledFeatures::TestFeatureEnabled();
  }
  bool testFeatureDependentEnabled() {
    return RuntimeEnabledFeatures::TestFeatureDependentEnabled();
  }
  bool testFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled() {
    return RuntimeEnabledFeatures::TestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabledByRuntimeFlag();
  }
  bool testFeatureImpliedEnabled() {
    return RuntimeEnabledFeatures::TestFeatureImpliedEnabled();
  }
  bool testFeatureProtectedEnabled() {
    return RuntimeEnabledFeatures::TestFeatureProtectedEnabled();
  }
  bool testFeatureProtectedDependentEnabled() {
    return RuntimeEnabledFeatures::TestFeatureProtectedDependentEnabled();
  }
  bool testFeatureProtectedImpliedEnabled() {
    return RuntimeEnabledFeatures::TestFeatureProtectedImpliedEnabled();
  }
  bool testFeatureStableEnabled() {
    return RuntimeEnabledFeatures::TestFeatureStableEnabled();
  }
  bool textAreaScrollTopPreviewEnabled() {
    return RuntimeEnabledFeatures::TextAreaScrollTopPreviewEnabled();
  }
  bool textDetectorEnabled() {
    return RuntimeEnabledFeatures::TextDetectorEnabled();
  }
  bool textEmphasisLetterSpacingEnabled() {
    return RuntimeEnabledFeatures::TextEmphasisLetterSpacingEnabled();
  }
  bool textEmphasisPositionAutoEnabled() {
    return RuntimeEnabledFeatures::TextEmphasisPositionAutoEnabled();
  }
  bool textEmphasisPunctuationExceptionsEnabled() {
    return RuntimeEnabledFeatures::TextEmphasisPunctuationExceptionsEnabled();
  }
  bool textEmphasisWithRubyEnabled() {
    return RuntimeEnabledFeatures::TextEmphasisWithRubyEnabled();
  }
  bool textFragmentAPIEnabled() {
    return RuntimeEnabledFeatures::TextFragmentAPIEnabled();
  }
  bool textFragmentIdentifiersEnabled() {
    return RuntimeEnabledFeatures::TextFragmentIdentifiersEnabledByRuntimeFlag();
  }
  bool textFragmentTapOpensContextMenuEnabled() {
    return RuntimeEnabledFeatures::TextFragmentTapOpensContextMenuEnabled();
  }
  bool textMetricsBaselinesEnabled() {
    return RuntimeEnabledFeatures::TextMetricsBaselinesEnabled();
  }
  bool textOverflowClipWithSelectionEnabled() {
    return RuntimeEnabledFeatures::TextOverflowClipWithSelectionEnabled();
  }
  bool textOverflowStringEnabled() {
    return RuntimeEnabledFeatures::TextOverflowStringEnabled();
  }
  bool textScaleMetaTagEnabled() {
    return RuntimeEnabledFeatures::TextScaleMetaTagEnabled();
  }
  bool textSpacingTrimFallbackEnabled() {
    return RuntimeEnabledFeatures::TextSpacingTrimFallbackEnabled();
  }
  bool textSpacingTrimFallback2Enabled() {
    return RuntimeEnabledFeatures::TextSpacingTrimFallback2Enabled();
  }
  bool textSpacingTrimFallbackChwsEnabled() {
    return RuntimeEnabledFeatures::TextSpacingTrimFallbackChwsEnabled();
  }
  bool textSpacingTrimYuGothicUIEnabled() {
    return RuntimeEnabledFeatures::TextSpacingTrimYuGothicUIEnabled();
  }
  bool throttledHistoryAPIThrowsSecurityErrorEnabled() {
    return RuntimeEnabledFeatures::ThrottledHistoryAPIThrowsSecurityErrorEnabled();
  }
  bool timelineTriggerEnabled() {
    return RuntimeEnabledFeatures::TimelineTriggerEnabled();
  }
  bool timerThrottlingForBackgroundTabsEnabled() {
    return RuntimeEnabledFeatures::TimerThrottlingForBackgroundTabsEnabled();
  }
  bool timestampBasedCLSTrackingEnabled() {
    return RuntimeEnabledFeatures::TimestampBasedCLSTrackingEnabled();
  }
  bool timeZoneChangeEventEnabled() {
    return RuntimeEnabledFeatures::TimeZoneChangeEventEnabled();
  }
  bool topicsAPIEnabled() {
    return RuntimeEnabledFeatures::TopicsAPIEnabled();
  }
  bool topicsDocumentAPIEnabled() {
    return RuntimeEnabledFeatures::TopicsDocumentAPIEnabled();
  }
  bool topicsImgAPIEnabled() {
    return RuntimeEnabledFeatures::TopicsImgAPIEnabled();
  }
  bool touchDragAndContextMenuEnabled() {
    return RuntimeEnabledFeatures::TouchDragAndContextMenuEnabled();
  }
  bool touchDragAndDropEnabled() {
    return RuntimeEnabledFeatures::TouchDragAndDropEnabled();
  }
  bool touchDragOnShortPressEnabled() {
    return RuntimeEnabledFeatures::TouchDragOnShortPressEnabled();
  }
  bool touchEventFeatureDetectionEnabled() {
    return RuntimeEnabledFeatures::TouchEventFeatureDetectionEnabledByRuntimeFlag();
  }
  bool touchTextEditingRedesignEnabled() {
    return RuntimeEnabledFeatures::TouchTextEditingRedesignEnabled();
  }
  bool transferableRTCDataChannelEnabled() {
    return RuntimeEnabledFeatures::TransferableRTCDataChannelEnabled();
  }
  bool transitionNavigationQuietSkipEnabled() {
    return RuntimeEnabledFeatures::TransitionNavigationQuietSkipEnabled();
  }
  bool translateServiceEnabled() {
    return RuntimeEnabledFeatures::TranslateServiceEnabled();
  }
  bool translationAPIEnabled() {
    return RuntimeEnabledFeatures::TranslationAPIEnabled();
  }
  bool translationAPIForWorkersEnabled() {
    return RuntimeEnabledFeatures::TranslationAPIForWorkersEnabled();
  }
  bool traverseFlatTreeToHandleSlotsEnabled() {
    return RuntimeEnabledFeatures::TraverseFlatTreeToHandleSlotsEnabled();
  }
  bool treatMhtmlInitialDocumentLoadsAsCrossDocumentEnabled() {
    return RuntimeEnabledFeatures::TreatMhtmlInitialDocumentLoadsAsCrossDocumentEnabled();
  }
  bool trustedTypesCreateParserOptionsEnabled() {
    return RuntimeEnabledFeatures::TrustedTypesCreateParserOptionsEnabled();
  }
  bool trustedTypesFromLiteralEnabled() {
    return RuntimeEnabledFeatures::TrustedTypesFromLiteralEnabled();
  }
  bool trustedTypesHTMLEnabled() {
    return RuntimeEnabledFeatures::TrustedTypesHTMLEnabled();
  }
  bool trustedTypesUseCodeLikeEnabled() {
    return RuntimeEnabledFeatures::TrustedTypesUseCodeLikeEnabled();
  }
  bool twoPhaseViewTransitionEnabled() {
    return RuntimeEnabledFeatures::TwoPhaseViewTransitionEnabled();
  }
  bool unclosedFormControlIsInvalidEnabled() {
    return RuntimeEnabledFeatures::UnclosedFormControlIsInvalidEnabled();
  }
  bool unexposedTaskIdsEnabled() {
    return RuntimeEnabledFeatures::UnexposedTaskIdsEnabled();
  }
  bool unprefixedSpeechRecognitionEnabled() {
    return RuntimeEnabledFeatures::UnprefixedSpeechRecognitionEnabled();
  }
  bool unrestrictedMeasureUserAgentSpecificMemoryEnabled() {
    return RuntimeEnabledFeatures::UnrestrictedMeasureUserAgentSpecificMemoryEnabled();
  }
  bool unrestrictedSharedArrayBufferEnabled() {
    return RuntimeEnabledFeatures::UnrestrictedSharedArrayBufferEnabledByRuntimeFlag();
  }
  bool unrestrictedUsbEnabled() {
    return RuntimeEnabledFeatures::UnrestrictedUsbEnabled();
  }
  bool updateComplexSafaAreaConstraintsEnabled() {
    return RuntimeEnabledFeatures::UpdateComplexSafaAreaConstraintsEnabled();
  }
  bool updateSelectionOnNodeInsertionEnabled() {
    return RuntimeEnabledFeatures::UpdateSelectionOnNodeInsertionEnabled();
  }
  bool updateTrivalTextAfterFragmentCreationFromTextEnabled() {
    return RuntimeEnabledFeatures::UpdateTrivalTextAfterFragmentCreationFromTextEnabled();
  }
  bool urlPatternCompareComponentEnabled() {
    return RuntimeEnabledFeatures::URLPatternCompareComponentEnabled();
  }
  bool urlPatternGenerateEnabled() {
    return RuntimeEnabledFeatures::URLPatternGenerateEnabled();
  }
  bool urlSearchParamsHasAndDeleteMultipleArgsEnabled() {
    return RuntimeEnabledFeatures::URLSearchParamsHasAndDeleteMultipleArgsEnabled();
  }
  bool useBeginFramePresentationFeedbackEnabled() {
    return RuntimeEnabledFeatures::UseBeginFramePresentationFeedbackEnabled();
  }
  bool useBoundedSelectionOffsetsInEditContextDeleteOperationsEnabled() {
    return RuntimeEnabledFeatures::UseBoundedSelectionOffsetsInEditContextDeleteOperationsEnabled();
  }
  bool useLargestPaintedImageForLCPCandidateEnabled() {
    return RuntimeEnabledFeatures::UseLargestPaintedImageForLCPCandidateEnabled();
  }
  bool useLowQualityInterpolationEnabled() {
    return RuntimeEnabledFeatures::UseLowQualityInterpolationEnabled();
  }
  bool useOriginalDomOffsetsForOffsetMapEnabled() {
    return RuntimeEnabledFeatures::UseOriginalDomOffsetsForOffsetMapEnabled();
  }
  bool usePositionForPointInFlexibleBoxWithSingleChildElementEnabled() {
    return RuntimeEnabledFeatures::UsePositionForPointInFlexibleBoxWithSingleChildElementEnabled();
  }
  bool usePositionIfIsVisuallyEquivalentCandidateEnabled() {
    return RuntimeEnabledFeatures::UsePositionIfIsVisuallyEquivalentCandidateEnabled();
  }
  bool userActionPseudosStopAtTopLayerEnabled() {
    return RuntimeEnabledFeatures::UserActionPseudosStopAtTopLayerEnabled();
  }
  bool userDefinedEntryPointTimingEnabled() {
    return RuntimeEnabledFeatures::UserDefinedEntryPointTimingEnabled();
  }
  bool userMediaElementEnabled() {
    return RuntimeEnabledFeatures::UserMediaElementEnabledByRuntimeFlag();
  }
  bool useSelectionInDOMTreeAnchorInExtendSelectionEnabled() {
    return RuntimeEnabledFeatures::UseSelectionInDOMTreeAnchorInExtendSelectionEnabled();
  }
  bool useShadowHostStyleCheckEditableEnabled() {
    return RuntimeEnabledFeatures::UseShadowHostStyleCheckEditableEnabled();
  }
  bool useUndoStepElementDispatchBeforeInputEnabled() {
    return RuntimeEnabledFeatures::UseUndoStepElementDispatchBeforeInputEnabled();
  }
  bool v8IdleTasksEnabled() {
    return RuntimeEnabledFeatures::V8IdleTasksEnabled();
  }
  bool videoAutoFullscreenEnabled() {
    return RuntimeEnabledFeatures::VideoAutoFullscreenEnabled();
  }
  bool videoFrameMetadataBackgroundBlurEnabled() {
    return RuntimeEnabledFeatures::VideoFrameMetadataBackgroundBlurEnabled();
  }
  bool videoFrameMetadataRtpTimestampEnabled() {
    return RuntimeEnabledFeatures::VideoFrameMetadataRtpTimestampEnabled();
  }
  bool videoFullscreenOrientationLockEnabled() {
    return RuntimeEnabledFeatures::VideoFullscreenOrientationLockEnabled();
  }
  bool videoRotateToFullscreenEnabled() {
    return RuntimeEnabledFeatures::VideoRotateToFullscreenEnabled();
  }
  bool videoTrackGeneratorEnabled() {
    return RuntimeEnabledFeatures::VideoTrackGeneratorEnabled();
  }
  bool videoTrackGeneratorInWindowEnabled() {
    return RuntimeEnabledFeatures::VideoTrackGeneratorInWindowEnabled();
  }
  bool videoTrackGeneratorInWorkerEnabled() {
    return RuntimeEnabledFeatures::VideoTrackGeneratorInWorkerEnabled();
  }
  bool viewportHeightClientHintHeaderEnabled() {
    return RuntimeEnabledFeatures::ViewportHeightClientHintHeaderEnabled();
  }
  bool viewportSegmentsEnabled() {
    return RuntimeEnabledFeatures::ViewportSegmentsEnabled();
  }
  bool viewTransitionAsyncFinishedEnabled() {
    return RuntimeEnabledFeatures::ViewTransitionAsyncFinishedEnabled();
  }
  bool viewTransitionDelayUnpauseOnTeardownEnabled() {
    return RuntimeEnabledFeatures::ViewTransitionDelayUnpauseOnTeardownEnabled();
  }
  bool viewTransitionHoistBackdropFilterEffectEnabled() {
    return RuntimeEnabledFeatures::ViewTransitionHoistBackdropFilterEffectEnabled();
  }
  bool viewTransitionLongCallbackTimeoutForTestingEnabled() {
    return RuntimeEnabledFeatures::ViewTransitionLongCallbackTimeoutForTestingEnabled();
  }
  bool viewTransitionUpdateLifecycleBeforeReadyEnabled() {
    return RuntimeEnabledFeatures::ViewTransitionUpdateLifecycleBeforeReadyEnabled();
  }
  bool viewTransitionWaitUntilEnabled() {
    return RuntimeEnabledFeatures::ViewTransitionWaitUntilEnabled();
  }
  bool visibilityCollapseColumnEnabled() {
    return RuntimeEnabledFeatures::VisibilityCollapseColumnEnabled();
  }
  bool visualRectMappingFixForExpansionEnabled() {
    return RuntimeEnabledFeatures::VisualRectMappingFixForExpansionEnabled();
  }
  bool wakeLockEnabled() {
    return RuntimeEnabledFeatures::WakeLockEnabled();
  }
  bool warnOnContentVisibilityRenderAccessEnabled() {
    return RuntimeEnabledFeatures::WarnOnContentVisibilityRenderAccessEnabled();
  }
  bool webAppInstallationEnabled() {
    return RuntimeEnabledFeatures::WebAppInstallationEnabledByRuntimeFlag();
  }
  bool webAppLaunchQueueEnabled() {
    return RuntimeEnabledFeatures::WebAppLaunchQueueEnabled();
  }
  bool webAppScopeExtensionsEnabled() {
    return RuntimeEnabledFeatures::WebAppScopeExtensionsEnabledByRuntimeFlag();
  }
  bool webAppScopeSystemAccentColorEnabled() {
    return RuntimeEnabledFeatures::WebAppScopeSystemAccentColorEnabled();
  }
  bool webAppTabStripEnabled() {
    return RuntimeEnabledFeatures::WebAppTabStripEnabled();
  }
  bool webAppTabStripCustomizationsEnabled() {
    return RuntimeEnabledFeatures::WebAppTabStripCustomizationsEnabled();
  }
  bool webAppTranslationsEnabled() {
    return RuntimeEnabledFeatures::WebAppTranslationsEnabled();
  }
  bool webAssemblyCustomDescriptorsV2Enabled() {
    return RuntimeEnabledFeatures::WebAssemblyCustomDescriptorsV2EnabledByRuntimeFlag();
  }
  bool webAssemblyJSPromiseIntegrationEnabled() {
    return RuntimeEnabledFeatures::WebAssemblyJSPromiseIntegrationEnabledByRuntimeFlag();
  }
  bool webAudioBypassOutputBufferingEnabled() {
    return RuntimeEnabledFeatures::WebAudioBypassOutputBufferingEnabled();
  }
  bool webAudioBypassOutputBufferingOptOutEnabled() {
    return RuntimeEnabledFeatures::WebAudioBypassOutputBufferingOptOutEnabled();
  }
  bool webAudioConfigurableRenderQuantumEnabled() {
    return RuntimeEnabledFeatures::WebAudioConfigurableRenderQuantumEnabledByRuntimeFlag();
  }
  bool webAuthEnabled() {
    return RuntimeEnabledFeatures::WebAuthEnabled();
  }
  bool webAuthAuthenticatorAttachmentEnabled() {
    return RuntimeEnabledFeatures::WebAuthAuthenticatorAttachmentEnabled();
  }
  bool webAuthenticationAmbientEnabled() {
    return RuntimeEnabledFeatures::WebAuthenticationAmbientEnabled();
  }
  bool webAuthenticationAttestationFormatsEnabled() {
    return RuntimeEnabledFeatures::WebAuthenticationAttestationFormatsEnabledByRuntimeFlag();
  }
  bool webAuthenticationImmediateGetEnabled() {
    return RuntimeEnabledFeatures::WebAuthenticationImmediateGetEnabled();
  }
  bool webAuthenticationRemoteDesktopSupportEnabled() {
    return RuntimeEnabledFeatures::WebAuthenticationRemoteDesktopSupportEnabled();
  }
  bool webAuthenticationSupplementalPubKeysEnabled() {
    return RuntimeEnabledFeatures::WebAuthenticationSupplementalPubKeysEnabled();
  }
  bool webBluetoothEnabled() {
    return RuntimeEnabledFeatures::WebBluetoothEnabled();
  }
  bool webBluetoothGetDevicesEnabled() {
    return RuntimeEnabledFeatures::WebBluetoothGetDevicesEnabled();
  }
  bool webBluetoothScanningEnabled() {
    return RuntimeEnabledFeatures::WebBluetoothScanningEnabled();
  }
  bool webBluetoothWatchAdvertisementsEnabled() {
    return RuntimeEnabledFeatures::WebBluetoothWatchAdvertisementsEnabled();
  }
  bool webcodecsVideoEncoderBuffersEnabled() {
    return RuntimeEnabledFeatures::WebCodecsVideoEncoderBuffersEnabled();
  }
  bool webCryptoPQCEnabled() {
    return RuntimeEnabledFeatures::WebCryptoPQCEnabled();
  }
  bool webFontResizeLCPEnabled() {
    return RuntimeEnabledFeatures::WebFontResizeLCPEnabled();
  }
  bool webglDeveloperExtensionsEnabled() {
    return RuntimeEnabledFeatures::WebGLDeveloperExtensionsEnabled();
  }
  bool webglDraftExtensionsEnabled() {
    return RuntimeEnabledFeatures::WebGLDraftExtensionsEnabled();
  }
  bool webglDrawingBufferStorageEnabled() {
    return RuntimeEnabledFeatures::WebGLDrawingBufferStorageEnabled();
  }
  bool webglOnWebGPUEnabled() {
    return RuntimeEnabledFeatures::WebGLOnWebGPUEnabled();
  }
  bool webgpuCompatibilityModeEnabled() {
    return RuntimeEnabledFeatures::WebGPUCompatibilityModeEnabledByRuntimeFlag();
  }
  bool webgpuDeveloperFeaturesEnabled() {
    return RuntimeEnabledFeatures::WebGPUDeveloperFeaturesEnabled();
  }
  bool webgpuExperimentalFeaturesEnabled() {
    return RuntimeEnabledFeatures::WebGPUExperimentalFeaturesEnabled();
  }
  bool webgpuImmediatesFeatureEnabled() {
    return RuntimeEnabledFeatures::WebGPUImmediatesFeatureEnabled();
  }
  bool webgpuMapSyncOnWorkersEnabled() {
    return RuntimeEnabledFeatures::WebGPUMapSyncOnWorkersEnabled();
  }
  bool webgpuMultithreadDawnWireOnWorkersEnabled() {
    return RuntimeEnabledFeatures::WebGPUMultithreadDawnWireOnWorkersEnabled();
  }
  bool webgpuTransientAttachmentEnabled() {
    return RuntimeEnabledFeatures::WebGPUTransientAttachmentEnabled();
  }
  bool webHIDEnabled() {
    return RuntimeEnabledFeatures::WebHIDEnabled();
  }
  bool webHIDOnServiceWorkersEnabled() {
    return RuntimeEnabledFeatures::WebHIDOnServiceWorkersEnabled();
  }
  bool webIdentityDigitalCredentialsEnabled() {
    return RuntimeEnabledFeatures::WebIdentityDigitalCredentialsEnabled();
  }
  bool webIdentityDigitalCredentialsCreationEnabled() {
    return RuntimeEnabledFeatures::WebIdentityDigitalCredentialsCreationEnabledByRuntimeFlag();
  }
  bool webIDLBigIntUsesToBigIntEnabled() {
    return RuntimeEnabledFeatures::WebIDLBigIntUsesToBigIntEnabled();
  }
  bool webMCPEnabled() {
    return RuntimeEnabledFeatures::WebMCPEnabledByRuntimeFlag();
  }
  bool webMCPDeclarativeFileInputEnabled() {
    return RuntimeEnabledFeatures::WebMCPDeclarativeFileInputEnabled();
  }
  bool webMCPFormAssociatedCustomElementsEnabled() {
    return RuntimeEnabledFeatures::WebMCPFormAssociatedCustomElementsEnabled();
  }
  bool webMCPTestingEnabled() {
    return RuntimeEnabledFeatures::WebMCPTestingEnabled();
  }
  bool webNFCEnabled() {
    return RuntimeEnabledFeatures::WebNFCEnabled();
  }
  bool webOTPEnabled() {
    return RuntimeEnabledFeatures::WebOTPEnabled();
  }
  bool webOTPAssertionFeaturePolicyEnabled() {
    return RuntimeEnabledFeatures::WebOTPAssertionFeaturePolicyEnabled();
  }
  bool webPreferencesEnabled() {
    return RuntimeEnabledFeatures::WebPreferencesEnabled();
  }
  bool webPrintingEnabled() {
    return RuntimeEnabledFeatures::WebPrintingEnabled();
  }
  bool webShareEnabled() {
    return RuntimeEnabledFeatures::WebShareEnabled();
  }
  bool websocketStreamEnabled() {
    return RuntimeEnabledFeatures::WebSocketStreamEnabled();
  }
  bool websocketStreamStandardBinaryChunkTypeEnabled() {
    return RuntimeEnabledFeatures::WebSocketStreamStandardBinaryChunkTypeEnabled();
  }
  bool webSpeechRecognitionContextEnabled() {
    return RuntimeEnabledFeatures::WebSpeechRecognitionContextEnabled();
  }
  bool webTransportApplicationProtocolEnabled() {
    return RuntimeEnabledFeatures::WebTransportApplicationProtocolEnabled();
  }
  bool webTransportCongestionControlEnabled() {
    return RuntimeEnabledFeatures::WebTransportCongestionControlEnabled();
  }
  bool webTransportCustomCertificatesEnabled() {
    return RuntimeEnabledFeatures::WebTransportCustomCertificatesEnabledByRuntimeFlag();
  }
  bool webTransportSendGroupEnabled() {
    return RuntimeEnabledFeatures::WebTransportSendGroupEnabled();
  }
  bool webTransportStatsEnabled() {
    return RuntimeEnabledFeatures::WebTransportStatsEnabled();
  }
  bool webUIBundledCodeCacheAsyncFetchEnabled() {
    return RuntimeEnabledFeatures::WebUIBundledCodeCacheAsyncFetchEnabled();
  }
  bool webUSBEnabled() {
    return RuntimeEnabledFeatures::WebUSBEnabled();
  }
  bool webUSBOnDedicatedWorkersEnabled() {
    return RuntimeEnabledFeatures::WebUSBOnDedicatedWorkersEnabled();
  }
  bool webUSBOnServiceWorkersEnabled() {
    return RuntimeEnabledFeatures::WebUSBOnServiceWorkersEnabled();
  }
  bool webVTTRegionsEnabled() {
    return RuntimeEnabledFeatures::WebVTTRegionsEnabled();
  }
  bool webXREnabled() {
    return RuntimeEnabledFeatures::WebXREnabled();
  }
  bool webXREnabledFeaturesEnabled() {
    return RuntimeEnabledFeatures::WebXREnabledFeaturesEnabled();
  }
  bool webXRFrameRateEnabled() {
    return RuntimeEnabledFeatures::WebXRFrameRateEnabled();
  }
  bool webXRFrontFacingEnabled() {
    return RuntimeEnabledFeatures::WebXRFrontFacingEnabled();
  }
  bool webXRGPUBindingEnabled() {
    return RuntimeEnabledFeatures::WebXRGPUBindingEnabled();
  }
  bool webXRHitTestEntityTypesEnabled() {
    return RuntimeEnabledFeatures::WebXRHitTestEntityTypesEnabled();
  }
  bool webXRImageTrackingEnabled() {
    return RuntimeEnabledFeatures::WebXRImageTrackingEnabledByRuntimeFlag();
  }
  bool webXRLayersEnabled() {
    return RuntimeEnabledFeatures::WebXRLayersEnabled();
  }
  bool webXRLayersCommonEnabled() {
    return RuntimeEnabledFeatures::WebXRLayersCommonEnabled();
  }
  bool webXRMeshDetectionEnabled() {
    return RuntimeEnabledFeatures::WebXRMeshDetectionEnabled();
  }
  bool webXRPlaneDetectionEnabled() {
    return RuntimeEnabledFeatures::WebXRPlaneDetectionEnabledByRuntimeFlag();
  }
  bool webXRPoseMotionDataEnabled() {
    return RuntimeEnabledFeatures::WebXRPoseMotionDataEnabled();
  }
  bool webXRSpecParityEnabled() {
    return RuntimeEnabledFeatures::WebXRSpecParityEnabled();
  }
  bool webXRVisibilityMaskEnabled() {
    return RuntimeEnabledFeatures::WebXRVisibilityMaskEnabled();
  }
  bool windowDefaultStatusEnabled() {
    return RuntimeEnabledFeatures::WindowDefaultStatusEnabled();
  }
  bool wordSkipSpacesPunctuationFixEnabled() {
    return RuntimeEnabledFeatures::WordSkipSpacesPunctuationFixEnabled();
  }
  bool wordSpacingWhiteSpacePreEnabled() {
    return RuntimeEnabledFeatures::WordSpacingWhiteSpacePreEnabled();
  }
  bool xmlNoExternalEntitiesEnabled() {
    return RuntimeEnabledFeatures::XMLNoExternalEntitiesEnabled();
  }
  bool xmlParsingRustEnabled() {
    return RuntimeEnabledFeatures::XMLParsingRustEnabled();
  }
  bool xmlRustForNonXsltEnabled() {
    return RuntimeEnabledFeatures::XMLRustForNonXsltEnabled();
  }
  bool xmlSerializerConsistentDefaultNsDeclMatchingEnabled() {
    return RuntimeEnabledFeatures::XMLSerializerConsistentDefaultNsDeclMatchingEnabled();
  }
  bool xpathShadowDOMSupportEnabled() {
    return RuntimeEnabledFeatures::XPathShadowDOMSupportEnabled();
  }
  bool xsltEnabled() {
    return RuntimeEnabledFeatures::XSLTEnabled();
  }
  bool xsltSpecialTrialEnabled() {
    return RuntimeEnabledFeatures::XSLTSpecialTrialEnabled();
  }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_TESTING_INTERNAL_RUNTIME_FLAGS_H_
