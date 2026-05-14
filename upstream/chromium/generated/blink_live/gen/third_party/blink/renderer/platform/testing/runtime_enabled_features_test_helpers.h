// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/runtime_enabled_features_test_helpers.h.tmpl
// and input files:
//   ../../third_party/blink/renderer/platform/runtime_enabled_features.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_ENABLED_FEATURES_TEST_HELPERS_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_ENABLED_FEATURES_TEST_HELPERS_H_

#include "base/check_op.h"
#include "base/memory/protected_memory.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"

namespace blink {

// Don't use this class directly. Use Scoped*ForTest instead.
class RuntimeEnabledFeaturesTestHelpers {
 public:
  template <bool& data_member>
  class [[nodiscard]] ScopedRuntimeEnabledFeature {
   public:
    ScopedRuntimeEnabledFeature(bool enabled)
        : enabled_(enabled), original_(data_member) { data_member = enabled; }
    ~ScopedRuntimeEnabledFeature() {
      CHECK_EQ(enabled_, data_member);
      data_member = original_;
    }
   private:
    bool enabled_;
    bool original_;
  };

  template <base::ProtectedMemory<bool>& data_member>
  class [[nodiscard]] ScopedRuntimeEnabledProtectedFeature {
   public:
    ScopedRuntimeEnabledProtectedFeature(bool enabled)
        : enabled_(enabled), original_(*data_member) {
      base::AutoWritableMemory data_member_writer(data_member);
      data_member_writer.GetProtectedData() = enabled;
    }
    ~ScopedRuntimeEnabledProtectedFeature() {
      CHECK_EQ(enabled_, *data_member);
      base::AutoWritableMemory data_member_writer(data_member);
      data_member_writer.GetProtectedData() = original_;
    }
   private:
    bool enabled_;
    bool original_;
  };

  using ScopedAboutBlankPageRespectsDarkModeOnUserAction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_about_blank_page_respects_dark_mode_on_user_action_enabled_>;
  using ScopedAccelerated2dCanvas = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accelerated_2d_canvas_enabled_>;
  using ScopedAcceleratedSmallCanvases = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accelerated_small_canvases_enabled_>;
  using ScopedAccessibilityAriaVirtualContent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_aria_virtual_content_enabled_>;
  using ScopedAccessibilityCustomElementRoleNone = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_custom_element_role_none_enabled_>;
  using ScopedAccessibilityExposeDisplayNone = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_expose_display_none_enabled_>;
  using ScopedAccessibilityImplicitActions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_implicit_actions_enabled_>;
  using ScopedAccessibilityMinRoleTabbable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_min_role_tabbable_enabled_>;
  using ScopedAccessibilityOSLevelBoldText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_os_level_bold_text_enabled_>;
  using ScopedAccessibilityProhibitedNames = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_prohibited_names_enabled_>;
  using ScopedAccessibilitySerializationSizeMetrics = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_serialization_size_metrics_enabled_>;
  using ScopedAccessibilityUseAXPositionForDocumentMarkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_accessibility_use_ax_position_for_document_markers_enabled_>;
  using ScopedAccessKeyLabel = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_access_key_label_enabled_>;
  using ScopedAddressSpace = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_address_space_enabled_>;
  using ScopedAdInterestGroupAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ad_interest_group_api_enabled_>;
  using ScopedAdjustDOMOffsetToLayoutOffsetForSecureText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_adjust_dom_offset_to_layout_offset_for_secure_text_enabled_>;
  using ScopedAdjustEndOfNextParagraphIfMovedParagraphIsUpdated = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_adjust_end_of_next_paragraph_if_moved_paragraph_is_updated_enabled_>;
  using ScopedAdTagging = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ad_tagging_enabled_>;
  using ScopedAIClassifierAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_classifier_api_enabled_>;
  using ScopedAIPageContentAnchoredOffscreenNonActionability = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_anchored_offscreen_non_actionability_enabled_>;
  using ScopedAIPageContentBuildOnLoadForTesting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_build_on_load_for_testing_enabled_>;
  using ScopedAIPageContentCheckGeometry = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_check_geometry_enabled_>;
  using ScopedAIPageContentConvertNodeTextToUtf8 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_convert_node_text_to_utf_8_enabled_>;
  using ScopedAIPageContentElementCSSRedaction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_element_css_redaction_enabled_>;
  using ScopedAIPageContentIncludeSVGSubtree = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_include_svg_subtree_enabled_>;
  using ScopedAIPageContentOuterBoxMapToAncestorSpace = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_outer_box_map_to_ancestor_space_enabled_>;
  using ScopedAIPageContentPaidContentAnnotation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_paid_content_annotation_enabled_>;
  using ScopedAIPageContentVisualViewportClamp = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_page_content_visual_viewport_clamp_enabled_>;
  using ScopedAIPromptAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_enabled_>;
  using ScopedAIPromptAPIForExtension = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_for_extension_enabled_>;
  using ScopedAIPromptAPIForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_for_workers_enabled_>;
  using ScopedAIPromptAPILegacyIdentifiers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_legacy_identifiers_enabled_>;
  using ScopedAIPromptAPILegacyParams = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_legacy_params_enabled_>;
  using ScopedAIPromptAPIMultimodalInput = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_multimodal_input_enabled_>;
  using ScopedAIPromptAPIParams = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_params_enabled_>;
  using ScopedAIPromptAPIStructuredOutput = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_structured_output_enabled_>;
  using ScopedAIPromptAPIToolUse = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_prompt_api_tool_use_enabled_>;
  using ScopedAIProofreadingAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_proofreading_api_enabled_>;
  using ScopedAIRewriterAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_rewriter_api_enabled_>;
  using ScopedAIRewriterAPIForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_rewriter_api_for_workers_enabled_>;
  using ScopedAISummarizationAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_summarization_api_enabled_>;
  using ScopedAISummarizationAPIForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_summarization_api_for_workers_enabled_>;
  using ScopedAISummarizationPerformancePreference = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_summarization_performance_preference_enabled_>;
  using ScopedAIWriterAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_writer_api_enabled_>;
  using ScopedAIWriterAPIForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ai_writer_api_for_workers_enabled_>;
  using ScopedAlignZoomToCenter = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_align_zoom_to_center_enabled_>;
  using ScopedAllImagesPaintedSentToElementTiming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_all_images_painted_sent_to_element_timing_enabled_>;
  using ScopedAllowContentInitiatedDataUrlNavigations = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_content_initiated_data_url_navigations_enabled_>;
  using ScopedAllowPreloadingWithCSPMetaTag = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_preloading_with_csp_meta_tag_enabled_>;
  using ScopedAllowSameSiteNoneCookiesInSandbox = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_same_site_none_cookies_in_sandbox_enabled_>;
  using ScopedAllowSkippingEditingBoundaryToMergeEnd = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_skipping_editing_boundary_to_merge_end_enabled_>;
  using ScopedAllowSvgUseToReferenceExternalDocumentRoot = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_svg_use_to_reference_external_document_root_enabled_>;
  using ScopedAllowSyntheticTimingForCanvasCapture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_synthetic_timing_for_canvas_capture_enabled_>;
  using ScopedAllowURNsInIframes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_allow_ur_ns_in_iframes_enabled_>;
  using ScopedAncestorOriginsStoredOnDocument = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ancestor_origins_stored_on_document_enabled_>;
  using ScopedAncestorRevealingNewSpec = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ancestor_revealing_new_spec_enabled_>;
  using ScopedAnchorFocusRingFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_anchor_focus_ring_fix_enabled_>;
  using ScopedAnchorPositionAdjustmentWithoutOverflow = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_anchor_position_adjustment_without_overflow_enabled_>;
  using ScopedAndroidDownloadableFontsMatching = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_android_downloadable_fonts_matching_enabled_>;
  using ScopedAnimationProgressAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_animation_progress_api_enabled_>;
  using ScopedAnimationTrigger = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_animation_trigger_enabled_>;
  using ScopedAnimationWorklet = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_animation_worklet_enabled_>;
  using ScopedAnonymousIframe = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_anonymous_iframe_enabled_>;
  using ScopedAOMAriaRelationshipProperties = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_aom_aria_relationship_properties_enabled_>;
  using ScopedAOMAriaRelationshipPropertiesAriaOwns = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_aom_aria_relationship_properties_aria_owns_enabled_>;
  using ScopedAppearanceBase = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_appearance_base_enabled_>;
  using ScopedApproximateGeolocationPermission = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_approximate_geolocation_permission_enabled_>;
  using ScopedApproximateGeolocationPermissionAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_approximate_geolocation_permission_api_enabled_>;
  using ScopedApproximateGeolocationWebVisibleAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_approximate_geolocation_web_visible_api_enabled_>;
  using ScopedAppTitle = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_app_title_enabled_>;
  using ScopedAriaActions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_aria_actions_enabled_>;
  using ScopedAriaNotify = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_aria_notify_enabled_>;
  using ScopedAriaNotifyV2 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_aria_notify_v_2_enabled_>;
  using ScopedAriaRowColIndexText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_aria_row_col_index_text_enabled_>;
  using ScopedAsyncSetCookie = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_async_set_cookie_enabled_>;
  using ScopedAttributionReporting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_attribution_reporting_enabled_>;
  using ScopedAudioContextAsyncStateTransitions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_audio_context_async_state_transitions_enabled_>;
  using ScopedAudioContextPlaybackStats = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_audio_context_playback_stats_enabled_>;
  using ScopedAudioContextPlayoutStats = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_audio_context_playout_stats_enabled_>;
  using ScopedAudioContextSetSinkId = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_audio_context_set_sink_id_enabled_>;
  using ScopedAudioOutputDevices = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_audio_output_devices_enabled_>;
  using ScopedAudioVideoTracks = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_audio_video_tracks_enabled_>;
  using ScopedAuthenticatorPasswordsOnlyImmediateRequests = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_authenticator_passwords_only_immediate_requests_enabled_>;
  using ScopedAuthorSpecifiedLayoutScrollSnapBehavior = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_author_specified_layout_scroll_snap_behavior_enabled_>;
  using ScopedAutoDarkMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_auto_dark_mode_enabled_>;
  using ScopedAutofill = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_autofill_enabled_>;
  using ScopedAutofillEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_autofill_event_enabled_>;
  using ScopedAutomationControlled = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_automation_controlled_enabled_>;
  using ScopedAutoPictureInPictureVideoHeuristics = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_auto_picture_in_picture_video_heuristics_enabled_>;
  using ScopedAvoidForcedLayoutOnInvisibleDocumentClose = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_avoid_forced_layout_on_invisible_document_close_enabled_>;
  using ScopedAvoidMergingStyledSpanWithSiblings = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_avoid_merging_styled_span_with_siblings_enabled_>;
  using ScopedAvoidNormalizingVisiblePositionsWhenStartEqualsEnd = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_avoid_normalizing_visible_positions_when_start_equals_end_enabled_>;
  using ScopedBackfaceVisibilityInterop = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_backface_visibility_interop_enabled_>;
  using ScopedBackForwardCache = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_back_forward_cache_enabled_>;
  using ScopedBackForwardCacheExperimentHTTPHeader = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_back_forward_cache_experiment_http_header_enabled_>;
  using ScopedBackForwardCacheNotRestoredReasons = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_back_forward_cache_not_restored_reasons_enabled_>;
  using ScopedBackForwardCacheRestorationPerformanceEntry = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_back_forward_cache_restoration_performance_entry_enabled_>;
  using ScopedBackForwardCacheUpdateNotRestoredReasonsName = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_back_forward_cache_update_not_restored_reasons_name_enabled_>;
  using ScopedBackgroundClipTextDecoration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_background_clip_text_decoration_enabled_>;
  using ScopedBackgroundFetch = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_background_fetch_enabled_>;
  using ScopedBackgroundPageFreezeOptOut = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_background_page_freeze_opt_out_enabled_>;
  using ScopedBarcodeDetector = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_barcode_detector_enabled_>;
  using ScopedBaseAppearanceInlineSizing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_base_appearance_inline_sizing_enabled_>;
  using ScopedBidiCaretAffinity = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_bidi_caret_affinity_enabled_>;
  using ScopedBlinkExtensionChromeOS = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_extension_chrome_os_enabled_>;
  using ScopedBlinkExtensionChromeOSIsolatedWebAppSetShape = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_extension_chrome_os_isolated_web_app_set_shape_enabled_>;
  using ScopedBlinkExtensionChromeOSKiosk = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_extension_chrome_os_kiosk_enabled_>;
  using ScopedBlinkExtensionWebView = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_extension_web_view_enabled_>;
  using ScopedBlinkExtensionWebViewMediaIntegrity = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_extension_web_view_media_integrity_enabled_>;
  using ScopedBlinkGeometryMapperViewportFastPath = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_geometry_mapper_viewport_fast_path_enabled_>;
  using ScopedBlinkLifecycleScriptForbidden = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_lifecycle_script_forbidden_enabled_>;
  using ScopedBlinkRuntimeCallStats = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blink_runtime_call_stats_enabled_>;
  using ScopedBlobBytes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blob_bytes_enabled_>;
  using ScopedBlockingFocusWithoutUserActivation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_blocking_focus_without_user_activation_enabled_>;
  using ScopedBlockSelectPopupUnfocusedWindow = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_block_select_popup_unfocused_window_enabled_>;
  using ScopedBoundaryEventDispatchTracksNodeRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_boundary_event_dispatch_tracks_node_removal_enabled_>;
  using ScopedBrowserInitiatedAutomaticPictureInPicture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_browser_initiated_automatic_picture_in_picture_enabled_>;
  using ScopedBrowserVerifiedUserActivationKeyboard = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_browser_verified_user_activation_keyboard_enabled_>;
  using ScopedBrowserVerifiedUserActivationMouse = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_browser_verified_user_activation_mouse_enabled_>;
  using ScopedBufferedBytesConsumerLimitSize = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_buffered_bytes_consumer_limit_size_enabled_>;
  using ScopedBypassPepcSecurityForTesting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_bypass_pepc_security_for_testing_enabled_>;
  using ScopedCacheControlRFC7234Parsing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cache_control_rfc_7234_parsing_enabled_>;
  using ScopedCacheControlRFC7234ParsingMetrics = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cache_control_rfc_7234_parsing_metrics_enabled_>;
  using ScopedCacheStorageCodeCacheHint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cache_storage_code_cache_hint_enabled_>;
  using ScopedCacheStyleAdjuster = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cache_style_adjuster_enabled_>;
  using ScopedCallExitNodeWithoutLayoutObject = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_call_exit_node_without_layout_object_enabled_>;
  using ScopedCanvas2dCanvasFilter = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_2d_canvas_filter_enabled_>;
  using ScopedCanvas2dGPUTransfer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_2d_gpu_transfer_enabled_>;
  using ScopedCanvas2dLayers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_2d_layers_enabled_>;
  using ScopedCanvas2dLayersWithOptions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_2d_layers_with_options_enabled_>;
  using ScopedCanvas2dMesh = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_2d_mesh_enabled_>;
  using ScopedCanvasDrawElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_draw_element_enabled_>;
  using ScopedCanvasFloatingPoint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_floating_point_enabled_>;
  using ScopedCanvasGlobalHDRHeadroom = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_global_hdr_headroom_enabled_>;
  using ScopedCanvasGradientCSSColor4 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_gradient_css_color_4_enabled_>;
  using ScopedCanvasHDR = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_hdr_enabled_>;
  using ScopedCanvasTextMetricsPreciseBounds = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_text_metrics_precise_bounds_enabled_>;
  using ScopedCanvasToneMapping = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_tone_mapping_enabled_>;
  using ScopedCanvasUsesArcPaintOp = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_canvas_uses_arc_paint_op_enabled_>;
  using ScopedCapabilityDelegationDisplayCaptureRequest = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_capability_delegation_display_capture_request_enabled_>;
  using ScopedCaptureController = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_capture_controller_enabled_>;
  using ScopedCapturedMouseEvents = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_captured_mouse_events_enabled_>;
  using ScopedCapturedSurfaceControl = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_captured_surface_control_enabled_>;
  using ScopedCapturedSurfaceResolution = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_captured_surface_resolution_enabled_>;
  using ScopedCaptureHandle = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_capture_handle_enabled_>;
  using ScopedCaretWithTextAffinityUpstream = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_caret_with_text_affinity_upstream_enabled_>;
  using ScopedCCTNewRFMPushBehavior = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cct_new_rfm_push_behavior_enabled_>;
  using ScopedCheckableInputTypeLayoutInline = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_checkable_input_type_layout_inline_enabled_>;
  using ScopedCheckForCanonicalPositionInIdleSpellCheck = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_check_for_canonical_position_in_idle_spell_check_enabled_>;
  using ScopedCheckVisibilityExtraProperties = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_check_visibility_extra_properties_enabled_>;
  using ScopedClampWordBoundaryToContentEditableScope = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clamp_word_boundary_to_content_editable_scope_enabled_>;
  using ScopedClearCurrentTargetAfterDispatch = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clear_current_target_after_dispatch_enabled_>;
  using ScopedClearFocusWithinOnSubtreeRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clear_focus_within_on_subtree_removal_enabled_>;
  using ScopedClearTargetOnlyIfInShadowTree = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clear_target_only_if_in_shadow_tree_enabled_>;
  using ScopedClickFocusDoesntPersistStatusBubble = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_click_focus_doesnt_persist_status_bubble_enabled_>;
  using ScopedClipboardEventTargetCanBeFocusedElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clipboard_event_target_can_be_focused_element_enabled_>;
  using ScopedClipboardEventTargetUsesContainerNode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clipboard_event_target_uses_container_node_enabled_>;
  using ScopedClipboardItemWithDOMStringSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clipboard_item_with_dom_string_support_enabled_>;
  using ScopedClipElementVisibleBoundsInLocalRoot = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clip_element_visible_bounds_in_local_root_enabled_>;
  using ScopedClipPathNestedRasterOptimization = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_clip_path_nested_raster_optimization_enabled_>;
  using ScopedCoalesceSelectionchangeEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_coalesce_selectionchange_event_enabled_>;
  using ScopedCoepReflection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_coep_reflection_enabled_>;
  using ScopedCollapseZeroWidthSpaceWhenReuseItem = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_collapse_zero_width_space_when_reuse_item_enabled_>;
  using ScopedColorInputAcceptsCSSColors = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_color_input_accepts_css_colors_enabled_>;
  using ScopedColorSpaceDisplayP3Linear = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_color_space_display_p_3_linear_enabled_>;
  using ScopedColorSpacePredefinedLinearSpaces = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_color_space_predefined_linear_spaces_enabled_>;
  using ScopedColorSpaceRec2100Linear = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_color_space_rec_2100_linear_enabled_>;
  using ScopedCommandEventNotComposed = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_command_event_not_composed_enabled_>;
  using ScopedCommaSeparatedContainerQueries = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_comma_separated_container_queries_enabled_>;
  using ScopedComposedPathReturnTargetBeingDispatched = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composed_path_return_target_being_dispatched_enabled_>;
  using ScopedCompositeBGColorAnimation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composite_bg_color_animation_enabled_>;
  using ScopedCompositeBoxShadowAnimation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composite_box_shadow_animation_enabled_>;
  using ScopedCompositeClipPathAnimation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composite_clip_path_animation_enabled_>;
  using ScopedCompositedAnimationsCancelledAsynchronously = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composited_animations_cancelled_asynchronously_enabled_>;
  using ScopedCompositedSelectionUpdate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composited_selection_update_enabled_>;
  using ScopedCompositingDecisionAtAnimationPhaseBoundaries = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compositing_decision_at_animation_phase_boundaries_enabled_>;
  using ScopedCompositionForegroundMarkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_composition_foreground_markers_enabled_>;
  using ScopedCompositorEventTrigger = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compositor_event_trigger_enabled_>;
  using ScopedCompositorTimelineTrigger = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compositor_timeline_trigger_enabled_>;
  using ScopedCompressionDictionaryTransport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compression_dictionary_transport_enabled_>;
  using ScopedComputedAccessibilityInfo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_computed_accessibility_info_enabled_>;
  using ScopedComputeInlineContentsSafeRetarget = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compute_inline_contents_safe_retarget_enabled_>;
  using ScopedComputePressure = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compute_pressure_enabled_>;
  using ScopedComputePressureOwnContributionEstimate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_compute_pressure_own_contribution_estimate_enabled_>;
  using ScopedConnectionAllowlist = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_connection_allowlist_enabled_>;
  using ScopedConsiderSubOrSuperScriptAncestorAlignForCaretSelection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_consider_sub_or_super_script_ancestor_align_for_caret_selection_enabled_>;
  using ScopedContactsManager = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_contacts_manager_enabled_>;
  using ScopedContactsManagerExtraProperties = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_contacts_manager_extra_properties_enabled_>;
  using ScopedContainerNameOnly = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_container_name_only_enabled_>;
  using ScopedContainerTiming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_container_timing_enabled_>;
  using ScopedContentIndex = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_content_index_enabled_>;
  using ScopedContextMenu = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_context_menu_enabled_>;
  using ScopedControlledFrame = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_controlled_frame_enabled_>;
  using ScopedControlledFrameWebRequestSecurityInfo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_controlled_frame_web_request_security_info_enabled_>;
  using ScopedCookieStoreAPIMaxAge = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cookie_store_api_max_age_enabled_>;
  using ScopedCookieStoreAPIWhitespaceStripping = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cookie_store_api_whitespace_stripping_enabled_>;
  using ScopedCoopRestrictProperties = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_coop_restrict_properties_enabled_>;
  using ScopedCorrectTemplateFormParsing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_correct_template_form_parsing_enabled_>;
  using ScopedCorsRFC1918 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cors_rfc_1918_enabled_>;
  using ScopedCpuPerformance = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cpu_performance_enabled_>;
  using ScopedCrashReportingStorageAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_crash_reporting_storage_api_enabled_>;
  using ScopedCreateInlineContentsExcludeOutOfFlow = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_create_inline_contents_exclude_out_of_flow_enabled_>;
  using ScopedCSPHashesV1 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_csp_hashes_v_1_enabled_>;
  using ScopedCSPReportHash = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_csp_report_hash_enabled_>;
  using ScopedCSSAccentColorKeyword = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_accent_color_keyword_enabled_>;
  using ScopedCSSActiveCaptionMapsToCanvas = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_active_caption_maps_to_canvas_enabled_>;
  using ScopedCSSAlphaColorFunction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_alpha_color_function_enabled_>;
  using ScopedCSSAltCounter = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_alt_counter_enabled_>;
  using ScopedCSSAnchorWithTransforms = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_anchor_with_transforms_enabled_>;
  using ScopedCSSAnimationIterationComposite = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_animation_iteration_composite_enabled_>;
  using ScopedCSSArgumentGrammar = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_argument_grammar_enabled_>;
  using ScopedCSSAtRuleCounterStyleImageSymbols = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_at_rule_counter_style_image_symbols_enabled_>;
  using ScopedCSSAtRuleCounterStyleSpeakAsDescriptor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_at_rule_counter_style_speak_as_descriptor_enabled_>;
  using ScopedCSSBackgroundClipBorderArea = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_background_clip_border_area_enabled_>;
  using ScopedCSSBorderShape = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_border_shape_enabled_>;
  using ScopedCSSCalcSimplificationAndSerialization = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_calc_simplification_and_serialization_enabled_>;
  using ScopedCSSCaretAnimation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_caret_animation_enabled_>;
  using ScopedCSSCaretShape = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_caret_shape_enabled_>;
  using ScopedCSSCaseSensitiveSelector = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_case_sensitive_selector_enabled_>;
  using ScopedCSSChUnitSpecCompliantFallback = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_ch_unit_spec_compliant_fallback_enabled_>;
  using ScopedCSSColorTypedOM = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_color_typed_om_enabled_>;
  using ScopedCSSContainerProgressNotation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_container_progress_notation_enabled_>;
  using ScopedCSSContainerStyleQueriesRange = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_container_style_queries_range_enabled_>;
  using ScopedCSSContrastColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_contrast_color_enabled_>;
  using ScopedCSSCornersShorthand = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_corners_shorthand_enabled_>;
  using ScopedCSSCounterResetReversed = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_counter_reset_reversed_enabled_>;
  using ScopedCSSCrossFade = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_cross_fade_enabled_>;
  using ScopedCSSCustomMedia = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_custom_media_enabled_>;
  using ScopedCSSDynamicRangeLimit = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_dynamic_range_limit_enabled_>;
  using ScopedCSSEnumeratedCustomProperties = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_enumerated_custom_properties_enabled_>;
  using ScopedCSSFontFamilySerialization = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_font_family_serialization_enabled_>;
  using ScopedCSSFontSizeAdjust = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_font_size_adjust_enabled_>;
  using ScopedCSSFunctions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_functions_enabled_>;
  using ScopedCSSGapDecoration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_gap_decoration_enabled_>;
  using ScopedCSSGridGapSuppression = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_grid_gap_suppression_enabled_>;
  using ScopedCSSGridLanesLayout = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_grid_lanes_layout_enabled_>;
  using ScopedCSSHangingPunctuation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_hanging_punctuation_enabled_>;
  using ScopedCSSHexAlphaColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_hex_alpha_color_enabled_>;
  using ScopedCSSIdentFunction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_ident_function_enabled_>;
  using ScopedCSSImageAnimation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_image_animation_enabled_>;
  using ScopedCSSInheritFunction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_inherit_function_enabled_>;
  using ScopedCSSKeyframesRuleLength = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_keyframes_rule_length_enabled_>;
  using ScopedCSSLangExtendedRanges = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_lang_extended_ranges_enabled_>;
  using ScopedCSSLayoutAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_layout_api_enabled_>;
  using ScopedCSSLetterAndWordSpacingPercentage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_letter_and_word_spacing_percentage_enabled_>;
  using ScopedCSSLightDarkImage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_light_dark_image_enabled_>;
  using ScopedCSSLineClamp = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_line_clamp_enabled_>;
  using ScopedCSSLineClampLineBreakingEllipsis = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_line_clamp_line_breaking_ellipsis_enabled_>;
  using ScopedCSSLineClampLinesAndHeight = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_line_clamp_lines_and_height_enabled_>;
  using ScopedCSSListCounterAccounting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_list_counter_accounting_enabled_>;
  using ScopedCSSLogicalCombinationPseudo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_logical_combination_pseudo_enabled_>;
  using ScopedCSSMarkerNestedPseudoElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_marker_nested_pseudo_element_enabled_>;
  using ScopedCSSMediaProgressNotation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_media_progress_notation_enabled_>;
  using ScopedCSSMixins = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_mixins_enabled_>;
  using ScopedCSSNestedPseudoElements = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_nested_pseudo_elements_enabled_>;
  using ScopedCSSOMGetComputedStylePseudoElementRequiresColon = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_cssom_get_computed_style_pseudo_element_requires_colon_enabled_>;
  using ScopedCSSOverscrollBehaviorChain = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_overscroll_behavior_chain_enabled_>;
  using ScopedCSSPaintAPIArguments = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_paint_api_arguments_enabled_>;
  using ScopedCSSParserIgnoreCharsetForURLs = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_parser_ignore_charset_for_urls_enabled_>;
  using ScopedCSSPolygonRounding = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_polygon_rounding_enabled_>;
  using ScopedCSSPositionStickyStaticScrollPosition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_position_sticky_static_scroll_position_enabled_>;
  using ScopedCSSProgressNotation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_progress_notation_enabled_>;
  using ScopedCSSPseudoColumn = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_column_enabled_>;
  using ScopedCSSPseudoElementBackdrop = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_element_backdrop_enabled_>;
  using ScopedCSSPseudoElementInterface = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_element_interface_enabled_>;
  using ScopedCSSPseudoElementViewTransitions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_element_view_transitions_enabled_>;
  using ScopedCSSPseudoHasSlotted = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_has_slotted_enabled_>;
  using ScopedCSSPseudoPlayingPaused = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_playing_paused_enabled_>;
  using ScopedCSSPseudoScrollButtons = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_scroll_buttons_enabled_>;
  using ScopedCSSPseudoScrollMarkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_pseudo_scroll_markers_enabled_>;
  using ScopedCSSRandomFunction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_random_function_enabled_>;
  using ScopedCSSRandomFunctionTypedOM = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_random_function_typed_om_enabled_>;
  using ScopedCSSResizeAuto = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_resize_auto_enabled_>;
  using ScopedCSSResourceIntegrityEnforcement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_resource_integrity_enforcement_enabled_>;
  using ScopedCSSRevertRule = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_revert_rule_enabled_>;
  using ScopedCSSRubyOverhang = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_ruby_overhang_enabled_>;
  using ScopedCSSSafePrintableInset = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_safe_printable_inset_enabled_>;
  using ScopedCSSScopeifiedParentPseudoClass = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scopeified_parent_pseudo_class_enabled_>;
  using ScopedCSSScopeImport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scope_import_enabled_>;
  using ScopedCSSScrolledContainerQueries = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scrolled_container_queries_enabled_>;
  using ScopedCSSScrollInitialTarget = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_initial_target_enabled_>;
  using ScopedCSSScrollMarkerGroupModes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_marker_group_modes_enabled_>;
  using ScopedCSSScrollMarkerTargetBeforeAfter = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_marker_target_before_after_enabled_>;
  using ScopedCSSScrollSnapChangeEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_snap_change_event_enabled_>;
  using ScopedCSSScrollSnapChangingEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_snap_changing_event_enabled_>;
  using ScopedCSSScrollSnapEventConstructorExposed = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_snap_event_constructor_exposed_enabled_>;
  using ScopedCSSScrollSnapEvents = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_snap_events_enabled_>;
  using ScopedCSSScrollTargetGroup = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_target_group_enabled_>;
  using ScopedCSSScrollTargetGroupAriaCurrent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_scroll_target_group_aria_current_enabled_>;
  using ScopedCSSShapeEllipseCirclePositionSerialization = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_shape_ellipse_circle_position_serialization_enabled_>;
  using ScopedCSSShapeOutsidePathAndShapeSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_shape_outside_path_and_shape_support_enabled_>;
  using ScopedCSSShapeOutsideRectAndXywhSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_shape_outside_rect_and_xywh_support_enabled_>;
  using ScopedCSSStyleSheetInitBaseURL = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_style_sheet_init_base_url_enabled_>;
  using ScopedCSSSupportsAtRuleFunction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_supports_at_rule_function_enabled_>;
  using ScopedCSSSupportsForImportRules = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_supports_for_import_rules_enabled_>;
  using ScopedCSSSupportsNamedFeatureFunction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_supports_named_feature_function_enabled_>;
  using ScopedCSSSystemAccentColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_system_accent_color_enabled_>;
  using ScopedCSSTextAlignMatchParent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_align_match_parent_enabled_>;
  using ScopedCSSTextDecorationSkipInkAll = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_decoration_skip_ink_all_enabled_>;
  using ScopedCSSTextDecorationSkipSpaces = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_decoration_skip_spaces_enabled_>;
  using ScopedCssTextFit = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_fit_enabled_>;
  using ScopedCssTextFitReshaping = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_fit_reshaping_enabled_>;
  using ScopedCssTextIndent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_indent_enabled_>;
  using ScopedCssTextIndentAsPrimitive = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_indent_as_primitive_enabled_>;
  using ScopedCSSTextSpacing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_spacing_enabled_>;
  using ScopedCSSTextTransformFullSizeKana = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_transform_full_size_kana_enabled_>;
  using ScopedCSSTextTransformFullWidth = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_transform_full_width_enabled_>;
  using ScopedCSSTextTransformMultiKeyword = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_text_transform_multi_keyword_enabled_>;
  using ScopedCSSTimelineScopeAll = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_timeline_scope_all_enabled_>;
  using ScopedCSSTimelineScopeGlobal = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_timeline_scope_global_enabled_>;
  using ScopedCSSTypedArithmetic = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_typed_arithmetic_enabled_>;
  using ScopedCSSURLRequestModifiers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_url_request_modifiers_enabled_>;
  using ScopedCSSUserSelectContain = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_user_select_contain_enabled_>;
  using ScopedCSSUserValidAndUserInvalidForRadio = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_user_valid_and_user_invalid_for_radio_enabled_>;
  using ScopedCSSVideoDynamicRangeMediaQueries = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_video_dynamic_range_media_queries_enabled_>;
  using ScopedCSSViewTransitionAutoName = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_css_view_transition_auto_name_enabled_>;
  using ScopedCustomElementsDisableFormattingFixups = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_custom_elements_disable_formatting_fixups_enabled_>;
  using ScopedCustomizableCombobox = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_customizable_combobox_enabled_>;
  using ScopedCustomizableSelectMultiplePopup = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_customizable_select_multiple_popup_enabled_>;
  using ScopedCustomScrollbarApplyMinimumThumbLength = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_custom_scrollbar_apply_minimum_thumb_length_enabled_>;
  using ScopedDatabase = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_database_enabled_>;
  using ScopedDateTimeLocalArabicCommaWorkaround = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_date_time_local_arabic_comma_workaround_enabled_>;
  using ScopedDeclarativeCSSModules = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_declarative_css_modules_enabled_>;
  using ScopedDeclarativeCSSModulesStyleTag = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_declarative_css_modules_style_tag_enabled_>;
  using ScopedDecoupleComputedBorderWidthFromStyle = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_decouple_computed_border_width_from_style_enabled_>;
  using ScopedDecoupleResolvedColumnRuleWidthFromStyle = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_decouple_resolved_column_rule_width_from_style_enabled_>;
  using ScopedDelegatesFocusTextControlInputFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_delegates_focus_text_control_input_fix_enabled_>;
  using ScopedDeleteTextInContentEditableBeforeRemovingChildren = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_delete_text_in_content_editable_before_removing_children_enabled_>;
  using ScopedDeprecateUnloadOptOut = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_deprecate_unload_opt_out_enabled_>;
  using ScopedDesktopCaptureDisableLocalEchoControl = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_desktop_capture_disable_local_echo_control_enabled_>;
  using ScopedDesktopPWAsAdditionalWindowingControls = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_desktop_pw_as_additional_windowing_controls_enabled_>;
  using ScopedDesktopPWAsAdditionalWindowingControlsOnMove = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_desktop_pw_as_additional_windowing_controls_on_move_enabled_>;
  using ScopedDeviceAttributes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_device_attributes_enabled_>;
  using ScopedDeviceOrientationRequestPermission = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_device_orientation_request_permission_enabled_>;
  using ScopedDevicePosture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_device_posture_enabled_>;
  using ScopedDialogCloseWhenOpenRemoved = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_dialog_close_when_open_removed_enabled_>;
  using ScopedDialogNewFocusBehavior = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_dialog_new_focus_behavior_enabled_>;
  using ScopedDigitalGoods = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_digital_goods_enabled_>;
  using ScopedDigitalGoodsV2_1 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_digital_goods_v_2_1_enabled_>;
  using ScopedDirectSockets = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_direct_sockets_enabled_>;
  using ScopedDirectSocketsInServiceWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_direct_sockets_in_service_workers_enabled_>;
  using ScopedDirectSocketsInSharedWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_direct_sockets_in_shared_workers_enabled_>;
  using ScopedDisableAnchorCenterOnAlignJustifyItems = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disable_anchor_center_on_align_justify_items_enabled_>;
  using ScopedDisableDifferentOriginSubframeDialogSuppression = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disable_different_origin_subframe_dialog_suppression_enabled_>;
  using ScopedDisableEllipsisWhenScrolled = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disable_ellipsis_when_scrolled_enabled_>;
  using ScopedDisableReduceAcceptLanguage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disable_reduce_accept_language_enabled_>;
  using ScopedDisableRemoveFormatForPlainTextOnlyEditableDiv = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disable_remove_format_for_plain_text_only_editable_div_enabled_>;
  using ScopedDisallowDisconnectedAreaNavigation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disallow_disconnected_area_navigation_enabled_>;
  using ScopedDisallowPickerForReadonlyInputs = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disallow_picker_for_readonly_inputs_enabled_>;
  using ScopedDisconnectWebSocketOnBFCache = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_disconnect_websocket_on_bf_cache_enabled_>;
  using ScopedDispatchHiddenVisibilityTransitions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_dispatch_hidden_visibility_transitions_enabled_>;
  using ScopedDispatchSelectionchangeEventPerElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_dispatch_selectionchange_event_per_element_enabled_>;
  using ScopedDisplayContentsFocusable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_display_contents_focusable_enabled_>;
  using ScopedDisplayCutoutAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_display_cutout_api_enabled_>;
  using ScopedDocumentActiveViewTransition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_active_view_transition_enabled_>;
  using ScopedDocumentCookie = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_cookie_enabled_>;
  using ScopedDocumentDomain = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_domain_enabled_>;
  using ScopedDocumentIsolationPolicy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_isolation_policy_enabled_>;
  using ScopedDocumentOpenIframeUnloadEvents = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_open_iframe_unload_events_enabled_>;
  using ScopedDocumentOpenOriginAliasRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_open_origin_alias_removal_enabled_>;
  using ScopedDocumentOpenSandboxInheritanceRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_open_sandbox_inheritance_removal_enabled_>;
  using ScopedDocumentPatching = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_patching_enabled_>;
  using ScopedDocumentPictureInPictureAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_picture_in_picture_api_enabled_>;
  using ScopedDocumentPictureInPicturePreferInitialPlacement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_picture_in_picture_prefer_initial_placement_enabled_>;
  using ScopedDocumentPictureInPictureUserActivation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_picture_in_picture_user_activation_enabled_>;
  using ScopedDocumentPolicyDocumentDomain = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_document_domain_enabled_>;
  using ScopedDocumentPolicyExpectNoLinkedResources = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_expect_no_linked_resources_enabled_>;
  using ScopedDocumentPolicyIncludeJSCallStacksInCrashReports = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_include_js_call_stacks_in_crash_reports_enabled_>;
  using ScopedDocumentPolicyInDedicatedWorker = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_in_dedicated_worker_enabled_>;
  using ScopedDocumentPolicyNegotiation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_negotiation_enabled_>;
  using ScopedDocumentPolicyNetworkEfficiencyGuardrails = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_network_efficiency_guardrails_enabled_>;
  using ScopedDocumentPolicySyncXHR = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_policy_sync_xhr_enabled_>;
  using ScopedDocumentWrite = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_document_write_enabled_>;
  using ScopedDOMActivateBubblesInheritance = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_dom_activate_bubbles_inheritance_enabled_>;
  using ScopedDontLeakShadowTreesInDragEvents = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_dont_leak_shadow_trees_in_drag_events_enabled_>;
  using ScopedEditContextAssignmentAsPerSpec = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_edit_context_assignment_as_per_spec_enabled_>;
  using ScopedEditContextHandleTextOrSelectionUpdateDuringComposition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_edit_context_handle_text_or_selection_update_during_composition_enabled_>;
  using ScopedEditEmojiTagSequence = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_edit_emoji_tag_sequence_enabled_>;
  using ScopedEditingLineMovementWithRubyFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_editing_line_movement_with_ruby_fix_enabled_>;
  using ScopedElementCapture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_element_capture_enabled_>;
  using ScopedElementInnerTextHandleFirstLineStyle = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_element_inner_text_handle_first_line_style_enabled_>;
  using ScopedElementInternalsBehaviors = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_element_internals_behaviors_enabled_>;
  using ScopedElementSpecificReadOnlyConstraintValidation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_element_specific_read_only_constraint_validation_enabled_>;
  using ScopedEmailVerificationProtocol = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_email_verification_protocol_enabled_>;
  using ScopedEmojiMonochromeRendering = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_emoji_monochrome_rendering_enabled_>;
  using ScopedEndpointInclusiveCommitStyles = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_endpoint_inclusive_commit_styles_enabled_>;
  using ScopedEnforceAnonymityExposure = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_enforce_anonymity_exposure_enabled_>;
  using ScopedEnterInOpenShadowRoots = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_enter_in_open_shadow_roots_enabled_>;
  using ScopedEntropyIgnoredForFirstVideoFrameLCP = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_entropy_ignored_for_first_video_frame_lcp_enabled_>;
  using ScopedEventPseudoTargetProperty = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_event_pseudo_target_property_enabled_>;
  using ScopedEventTimingInteractionCount = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_event_timing_interaction_count_enabled_>;
  using ScopedEventTimingTargetSelector = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_event_timing_target_selector_enabled_>;
  using ScopedEventTrigger = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_event_trigger_enabled_>;
  using ScopedExperimentalContentSecurityPolicyFeatures = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_experimental_content_security_policy_features_enabled_>;
  using ScopedExperimentalJSProfilerMarkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_experimental_js_profiler_markers_enabled_>;
  using ScopedExperimentalMachineLearningNeuralNetwork = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_experimental_machine_learning_neural_network_enabled_>;
  using ScopedExperimentalPolicies = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_experimental_policies_enabled_>;
  using ScopedExposeCSSFontFeatureValuesRule = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_expose_css_font_feature_values_rule_enabled_>;
  using ScopedExposeRenderTimeNonTaoDelayedImage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_expose_render_time_non_tao_delayed_image_enabled_>;
  using ScopedExtendedShapeCache = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_extended_shape_cache_enabled_>;
  using ScopedExtendedTextMetrics = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_extended_text_metrics_enabled_>;
  using ScopedExternalPopupMenuClickEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_external_popup_menu_click_event_enabled_>;
  using ScopedEyeDropperAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_eye_dropper_api_enabled_>;
  using ScopedFaceDetector = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_face_detector_enabled_>;
  using ScopedFastPositionIterator = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fast_position_iterator_enabled_>;
  using ScopedFedCm = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_enabled_>;
  using ScopedFedCmAutofill = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_autofill_enabled_>;
  using ScopedFedCmDelegation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_delegation_enabled_>;
  using ScopedFedCmErrorAttribute = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_error_attribute_enabled_>;
  using ScopedFedCmIdPRegistration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_id_p_registration_enabled_>;
  using ScopedFedCmLightweightMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_lightweight_mode_enabled_>;
  using ScopedFedCmMultipleIdentityProviders = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_multiple_identity_providers_enabled_>;
  using ScopedFedCmNavigationInterception = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_navigation_interception_enabled_>;
  using ScopedFedCmNonStringToken = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fed_cm_non_string_token_enabled_>;
  using ScopedFencedFrames = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fenced_frames_enabled_>;
  using ScopedFencedFramesAPIChanges = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fenced_frames_api_changes_enabled_>;
  using ScopedFencedFramesDefaultMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fenced_frames_default_mode_enabled_>;
  using ScopedFencedFramesLocalUnpartitionedDataAccess = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fenced_frames_local_unpartitioned_data_access_enabled_>;
  using ScopedFetchBodyBytes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fetch_body_bytes_enabled_>;
  using ScopedFetchLaterAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fetch_later_api_enabled_>;
  using ScopedFetchRetry = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fetch_retry_enabled_>;
  using ScopedFetchUploadStreaming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fetch_upload_streaming_enabled_>;
  using ScopedFileHandling = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_handling_enabled_>;
  using ScopedFileHandlingIcons = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_handling_icons_enabled_>;
  using ScopedFileSystem = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_enabled_>;
  using ScopedFileSystemAccess = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_enabled_>;
  using ScopedFileSystemAccessAPIExperimental = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_api_experimental_enabled_>;
  using ScopedFileSystemAccessGetCloudIdentifiers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_get_cloud_identifiers_enabled_>;
  using ScopedFileSystemAccessLocal = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_local_enabled_>;
  using ScopedFileSystemAccessLockingScheme = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_locking_scheme_enabled_>;
  using ScopedFileSystemAccessOriginPrivate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_origin_private_enabled_>;
  using ScopedFileSystemAccessRevokeReadOnRemove = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_revoke_read_on_remove_enabled_>;
  using ScopedFileSystemAccessWriteMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_access_write_mode_enabled_>;
  using ScopedFileSystemObserver = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_observer_enabled_>;
  using ScopedFileSystemObserverUnobserve = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_file_system_observer_unobserve_enabled_>;
  using ScopedFilterableSelect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_filterable_select_enabled_>;
  using ScopedFilterContainerLevelStyles = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_filter_container_level_styles_enabled_>;
  using ScopedFilteringPrimitives = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_filtering_primitives_enabled_>;
  using ScopedFindFirstMisspellingEndWhenNonEditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_find_first_misspelling_end_when_non_editable_enabled_>;
  using ScopedFirstLineOnListItem = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_first_line_on_list_item_enabled_>;
  using ScopedFirstLineTextMetrics = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_first_line_text_metrics_enabled_>;
  using ScopedFixHTMLFormControlElementIsReadOnly = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_html_form_control_element_is_read_only_enabled_>;
  using ScopedFixJustifyQueryCommandValue = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_justify_query_command_value_enabled_>;
  using ScopedFixLinebreakForPreTag = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_linebreak_for_pre_tag_enabled_>;
  using ScopedFixMapElementEmptyNameBug = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_map_element_empty_name_bug_enabled_>;
  using ScopedFixMarkerSuppressionForAppearanceAuto = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_marker_suppression_for_appearance_auto_enabled_>;
  using ScopedFixNextPositionCalculationInInsertList = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_next_position_calculation_in_insert_list_enabled_>;
  using ScopedFixStrikethroughToggleInEmptyContentEditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_strikethrough_toggle_in_empty_content_editable_enabled_>;
  using ScopedFixVisualRectRemoteViewportTransform = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fix_visual_rect_remote_viewport_transform_enabled_>;
  using ScopedFledge = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_enabled_>;
  using ScopedFledgeAuctionDealSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_auction_deal_support_enabled_>;
  using ScopedFledgeBiddingAndAuctionServerAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_bidding_and_auction_server_api_enabled_>;
  using ScopedFledgeBiddingAndAuctionServerAPIMultiSeller = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_bidding_and_auction_server_api_multi_seller_enabled_>;
  using ScopedFledgeClickiness = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_clickiness_enabled_>;
  using ScopedFledgeCustomMaxAuctionAdComponents = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_custom_max_auction_ad_components_enabled_>;
  using ScopedFledgeDeprecatedRenderURLReplacements = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_deprecated_render_url_replacements_enabled_>;
  using ScopedFledgeDirectFromSellerSignalsHeaderAdSlot = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_direct_from_seller_signals_header_ad_slot_enabled_>;
  using ScopedFledgeDirectFromSellerSignalsWebBundles = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_direct_from_seller_signals_web_bundles_enabled_>;
  using ScopedFledgeMultiBid = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_multi_bid_enabled_>;
  using ScopedFledgePrivateModelTraining = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_private_model_training_enabled_>;
  using ScopedFledgeRealTimeReporting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_real_time_reporting_enabled_>;
  using ScopedFledgeSellerNonce = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_seller_nonce_enabled_>;
  using ScopedFledgeSellerScriptExecutionMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_seller_script_execution_mode_enabled_>;
  using ScopedFledgeTrustedSignalsKVv1CreativeScanning = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_trusted_signals_k_vv_1_creative_scanning_enabled_>;
  using ScopedFledgeTrustedSignalsKVv2ContextualData = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_trusted_signals_k_vv_2_contextual_data_enabled_>;
  using ScopedFledgeTrustedSignalsKVv2Support = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fledge_trusted_signals_k_vv_2_support_enabled_>;
  using ScopedFlexWrapBalance = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_flex_wrap_balance_enabled_>;
  using ScopedFocusgroup = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_focusgroup_enabled_>;
  using ScopedFocusgroupGrid = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_focusgroup_grid_enabled_>;
  using ScopedFontAccess = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_access_enabled_>;
  using ScopedFontDataService = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_data_service_enabled_>;
  using ScopedFontFallbackForTabSize = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_fallback_for_tab_size_enabled_>;
  using ScopedFontFamilyPostscriptMatchingCTMigration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_family_postscript_matching_ct_migration_enabled_>;
  using ScopedFontFamilyStyleMatchingCTMigration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_family_style_matching_ct_migration_enabled_>;
  using ScopedFontFeatureSettingsDescriptor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_feature_settings_descriptor_enabled_>;
  using ScopedFontFormatAvar2 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_format_avar_2_enabled_>;
  using ScopedFontLanguageOverride = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_language_override_enabled_>;
  using ScopedFontMatchAliasesAsLastResort = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_match_aliases_as_last_resort_enabled_>;
  using ScopedFontStyleObliqueZeroDegreeAsNormal = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_style_oblique_zero_degree_as_normal_enabled_>;
  using ScopedFontVariationSettingsDescriptor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_font_variation_settings_descriptor_enabled_>;
  using ScopedForcedColors = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_forced_colors_enabled_>;
  using ScopedForceEagerMeasureMemory = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_force_eager_measure_memory_enabled_>;
  using ScopedForceReduceMotion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_force_reduce_motion_enabled_>;
  using ScopedFractionalScrollOffsets = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fractional_scroll_offsets_enabled_>;
  using ScopedFragmentedOofInCb = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_fragmented_oof_in_cb_enabled_>;
  using ScopedFreezeFramesOnVisibility = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_freeze_frames_on_visibility_enabled_>;
  using ScopedGamepadMultitouch = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_gamepad_multitouch_enabled_>;
  using ScopedGamepadRawInputChangeEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_gamepad_raw_input_change_event_enabled_>;
  using ScopedGamepadWindowEventHandlers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_gamepad_window_event_handlers_enabled_>;
  using ScopedGeolocationElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_geolocation_element_enabled_>;
  using ScopedGeometryMapperSingularTransformFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_geometry_mapper_singular_transform_fix_enabled_>;
  using ScopedGeometryUtils = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_geometry_utils_enabled_>;
  using ScopedGeometryUtilsForCSSPseudoElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_geometry_utils_for_css_pseudo_element_enabled_>;
  using ScopedGetAllScreensMedia = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_all_screens_media_enabled_>;
  using ScopedGetComputedStyleOutsideFlatTree = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_computed_style_outside_flat_tree_enabled_>;
  using ScopedGetDisplayMedia = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_display_media_enabled_>;
  using ScopedGetDisplayMediaRequiresUserActivation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_display_media_requires_user_activation_enabled_>;
  using ScopedGetDisplayMediaWindowAudioCapture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_display_media_window_audio_capture_enabled_>;
  using ScopedGetElementsByNameOnlyHTMLElements = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_elements_by_name_only_html_elements_enabled_>;
  using ScopedGetUserMediaEchoCancellationModes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_get_user_media_echo_cancellation_modes_enabled_>;
  using ScopedGroupEffect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_group_effect_enabled_>;
  using ScopedHandleDeletionAtStartAndEndBoundaryContainingHiddenElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_handle_deletion_at_start_and_end_boundary_containing_hidden_element_enabled_>;
  using ScopedHandleDisconnectedSelectionDuringDOMChanges = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_handle_disconnected_selection_during_dom_changes_enabled_>;
  using ScopedHandleInvalidMaskImageWithBackdropFilter = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_handle_invalid_mask_image_with_backdrop_filter_enabled_>;
  using ScopedHandleShadowDOMInSubstringUtil = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_handle_shadow_dom_in_substring_util_enabled_>;
  using ScopedHandwritingRecognition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_handwriting_recognition_enabled_>;
  using ScopedHasUAVisualTransition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_has_ua_visual_transition_enabled_>;
  using ScopedHeadingOffset = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_heading_offset_enabled_>;
  using ScopedHideVideoControlsWhenUnneeded = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_hide_video_controls_when_unneeded_enabled_>;
  using ScopedHighlightsFromPoint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_highlights_from_point_enabled_>;
  using ScopedHitTestBorderRadiusForStackingContext = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_hit_test_border_radius_for_stacking_context_enabled_>;
  using ScopedHitTestContainerTransformStateForPreserve3d = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_hit_test_container_transform_state_for_preserve_3d_enabled_>;
  using ScopedHrefTranslate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_href_translate_enabled_>;
  using ScopedHstsTopLevelNavigationsOnly = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_hsts_top_level_navigations_only_enabled_>;
  using ScopedHTMLAdoptionAlgorithmNewSteps = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_adoption_algorithm_new_steps_enabled_>;
  using ScopedHTMLCommandActionsV2 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_command_actions_v_2_enabled_>;
  using ScopedHTMLCommandElementRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_command_element_removal_enabled_>;
  using ScopedHTMLCommandForScrollCommands = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_command_for_scroll_commands_enabled_>;
  using ScopedHTMLElementScrollParent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_element_scroll_parent_enabled_>;
  using ScopedHTMLImageElementActualNaturalSize = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_image_element_actual_natural_size_enabled_>;
  using ScopedHTMLInputElementDropWebkitClearButton = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_input_element_drop_webkit_clear_button_enabled_>;
  using ScopedHTMLInterestForInterestButtonPseudo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_interest_for_interest_button_pseudo_enabled_>;
  using ScopedHTMLLinkElementAttributeValueChanges = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_link_element_attribute_value_changes_enabled_>;
  using ScopedHTMLParserYieldAndDelayOftenForTesting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_parser_yield_and_delay_often_for_testing_enabled_>;
  using ScopedHTMLParserYieldByUserTiming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_parser_yield_by_user_timing_enabled_>;
  using ScopedHTMLPrintingArtifactAnnotations = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_printing_artifact_annotations_enabled_>;
  using ScopedHTMLProcessingInstruction = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_html_processing_instruction_enabled_>;
  using ScopedICUCapitalization = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_icu_capitalization_enabled_>;
  using ScopedIgnoreLetterSpacingInCursiveScripts = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_ignore_letter_spacing_in_cursive_scripts_enabled_>;
  using ScopedImageDataPixelFormat = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_image_data_pixel_format_enabled_>;
  using ScopedImageDocumentUseLayoutWidth = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_image_document_use_layout_width_enabled_>;
  using ScopedImageSrcsetReselection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_image_srcset_reselection_enabled_>;
  using ScopedImplicitRootScroller = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_implicit_root_scroller_enabled_>;
  using ScopedImprovedSourceRetargeting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_improved_source_retargeting_enabled_>;
  using ScopedIncomingCallNotifications = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_incoming_call_notifications_enabled_>;
  using ScopedInertElementNonEditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_inert_element_non_editable_enabled_>;
  using ScopedInfiniteCullRect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_infinite_cull_rect_enabled_>;
  using ScopedInheritUserModifyWithoutContenteditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_inherit_user_modify_without_contenteditable_enabled_>;
  using ScopedInlineBlockLineNavigation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_inline_block_line_navigation_enabled_>;
  using ScopedInlineScriptCacheHint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_inline_script_cache_hint_enabled_>;
  using ScopedInnerHTMLParserFastpathLogFailure = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_inner_html_parser_fastpath_log_failure_enabled_>;
  using ScopedInputEventDataTransferForInsertCmd = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_input_event_data_transfer_for_insert_cmd_enabled_>;
  using ScopedInputEventsDeleteNonCollapsedSelection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_input_events_delete_non_collapsed_selection_enabled_>;
  using ScopedInputInSelect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_input_in_select_enabled_>;
  using ScopedInputMultipleFieldsUI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_input_multiple_fields_ui_enabled_>;
  using ScopedInsertBlockquoteBeforeOuterBlock = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_insert_blockquote_before_outer_block_enabled_>;
  using ScopedInstalledApp = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_installed_app_enabled_>;
  using ScopedInstallElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_install_element_enabled_>;
  using ScopedInstallOnDeviceSpeechRecognition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_install_on_device_speech_recognition_enabled_>;
  using ScopedIntegrityPolicyScript = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_integrity_policy_script_enabled_>;
  using ScopedInterestEventsNonComposed = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_interest_events_non_composed_enabled_>;
  using ScopedInterestGroupsInSharedStorageWorklet = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_interest_groups_in_shared_storage_worklet_enabled_>;
  using ScopedIntersectionObserverCompositedAnimationsForceMainFrames = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_intersection_observer_composited_animations_force_main_frames_enabled_>;
  using ScopedInvertedColors = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_inverted_colors_enabled_>;
  using ScopedInvisibleSVGAnimationThrottling = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_invisible_svg_animation_throttling_enabled_>;
  using ScopedJavaScriptCompileHintsPerFunctionMagicRuntime = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_java_script_compile_hints_per_function_magic_runtime_enabled_>;
  using ScopedJavaScriptSourcePhaseImports = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_java_script_source_phase_imports_enabled_>;
  using ScopedKeyboardAccessibleTooltip = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_keyboard_accessible_tooltip_enabled_>;
  using ScopedKeySystemTrackConfigurationEncryptionScheme = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_key_system_track_configuration_encryption_scheme_enabled_>;
  using ScopedLabelInteractiveContentCheckBeforeHandler = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_label_interactive_content_check_before_handler_enabled_>;
  using ScopedLangAttributeAwareFormControlUI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_lang_attribute_aware_form_control_ui_enabled_>;
  using ScopedLanguageDetectionAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_language_detection_api_enabled_>;
  using ScopedLanguageDetectionAPIForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_language_detection_api_for_workers_enabled_>;
  using ScopedLayoutBoxRectGettersUseFragments = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_layout_box_rect_getters_use_fragments_enabled_>;
  using ScopedLayoutIgnoreMarginsForSticky = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_layout_ignore_margins_for_sticky_enabled_>;
  using ScopedLayoutImageEmptyNaturalSizeBeforeSizeAvailable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_layout_image_empty_natural_size_before_size_available_enabled_>;
  using ScopedLayoutTableCellAlignmentSafe = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_layout_table_cell_alignment_safe_enabled_>;
  using ScopedLazyImageConformantLoadEventTiming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_lazy_image_conformant_load_event_timing_enabled_>;
  using ScopedLazyLoadVideoAndAudio = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_lazy_load_video_and_audio_enabled_>;
  using ScopedLeftClickToHandleSuggestion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_left_click_to_handle_suggestion_enabled_>;
  using ScopedLightDismissFromClick = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_light_dismiss_from_click_enabled_>;
  using ScopedLinkBlurImprovement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_link_blur_improvement_enabled_>;
  using ScopedListOwnerMustHaveCSSBox = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_list_owner_must_have_css_box_enabled_>;
  using ScopedLocalNetworkAccessNonSecureContextAllowed = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_local_network_access_non_secure_context_allowed_enabled_>;
  using ScopedLocalNetworkAccessPermissionPolicy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_local_network_access_permission_policy_enabled_>;
  using ScopedLocalNetworkAccessSplitPermissions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_local_network_access_split_permissions_enabled_>;
  using ScopedLocalNetworkAccessWebRTC = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_local_network_access_web_rtc_enabled_>;
  using ScopedLockedMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_locked_mode_enabled_>;
  using ScopedLogicalStartOfLineBlockFallback = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_logical_start_of_line_block_fallback_enabled_>;
  using ScopedLoginElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_login_element_enabled_>;
  using ScopedLongAnimationFrameSourceCharPosition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_long_animation_frame_source_char_position_enabled_>;
  using ScopedLongAnimationFrameSourceLineColumn = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_long_animation_frame_source_line_column_enabled_>;
  using ScopedLongAnimationFrameSourceLineColumnInterface = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_long_animation_frame_source_line_column_interface_enabled_>;
  using ScopedLongAnimationFrameStyleDuration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_long_animation_frame_style_duration_enabled_>;
  using ScopedLongPressLinkSelectText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_long_press_link_select_text_enabled_>;
  using ScopedLongTaskFromLongAnimationFrame = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_long_task_from_long_animation_frame_enabled_>;
  using ScopedMacCharacterFallbackCache = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mac_character_fallback_cache_enabled_>;
  using ScopedMacDisableCtrlHomeEnd = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mac_disable_ctrl_home_end_enabled_>;
  using ScopedMachineLearningNeuralNetwork = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_machine_learning_neural_network_enabled_>;
  using ScopedMacSystemClipboardPermissionCheck = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mac_system_clipboard_permission_check_enabled_>;
  using ScopedManagedConfiguration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_managed_configuration_enabled_>;
  using ScopedManualText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_manual_text_enabled_>;
  using ScopedMarginTrim = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_margin_trim_enabled_>;
  using ScopedMaskDeserializationTimeForCrossOriginMessages = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mask_deserialization_time_for_cross_origin_messages_enabled_>;
  using ScopedMathMLOperatorRTLMirroring = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mathml_operator_rtl_mirroring_enabled_>;
  using ScopedMathMLSerializationOnCopy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mathml_serialization_on_copy_enabled_>;
  using ScopedMathMLSkipMtrTagInAncestorWrapping = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mathml_skip_mtr_tag_in_ancestor_wrapping_enabled_>;
  using ScopedMeasureMemory = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_measure_memory_enabled_>;
  using ScopedMediaCapabilitiesEncodingInfo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capabilities_encoding_info_enabled_>;
  using ScopedMediaCapabilitiesSpatialAudio = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capabilities_spatial_audio_enabled_>;
  using ScopedMediaCapture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capture_enabled_>;
  using ScopedMediaCaptureBackgroundBlur = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capture_background_blur_enabled_>;
  using ScopedMediaCaptureCameraControls = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capture_camera_controls_enabled_>;
  using ScopedMediaCaptureConfigurationChange = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capture_configuration_change_enabled_>;
  using ScopedMediaCaptureVoiceIsolation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_capture_voice_isolation_enabled_>;
  using ScopedMediaControlsExpandGesture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_controls_expand_gesture_enabled_>;
  using ScopedMediaControlsOverlayPlayButton = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_controls_overlay_play_button_enabled_>;
  using ScopedMediaElementVolumeGreaterThanOne = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_element_volume_greater_than_one_enabled_>;
  using ScopedMediaEngagementBypassAutoplayPolicies = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_engagement_bypass_autoplay_policies_enabled_>;
  using ScopedMediaLatencyHint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_latency_hint_enabled_>;
  using ScopedMediaPlaybackWhileNotVisiblePermissionPolicy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_playback_while_not_visible_permission_policy_enabled_>;
  using ScopedMediaQueryNavigationControls = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_query_navigation_controls_enabled_>;
  using ScopedMediaSession = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_session_enabled_>;
  using ScopedMediaSessionChapterInformation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_session_chapter_information_enabled_>;
  using ScopedMediaSourceExperimental = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_source_experimental_enabled_>;
  using ScopedMediaSourceExtensionsForWebCodecs = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_source_extensions_for_webcodecs_enabled_>;
  using ScopedMediaStreamTrackTransfer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_stream_track_transfer_enabled_>;
  using ScopedMediaStreamTrackWebSpeech = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_media_stream_track_web_speech_enabled_>;
  using ScopedMemoryConsumerForNGShapeCache = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_memory_consumer_for_ng_shape_cache_enabled_>;
  using ScopedMenuElements = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_menu_elements_enabled_>;
  using ScopedMergeFixedLayers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_merge_fixed_layers_enabled_>;
  using ScopedMergeStickyLayers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_merge_sticky_layers_enabled_>;
  using ScopedMessagePortCloseEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_message_port_close_event_enabled_>;
  using ScopedMiddleClickAutoscroll = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_middle_click_autoscroll_enabled_>;
  using ScopedMixedContentAutoupgradesUseIsMixedContentRestrictedInFrame = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mixed_content_autoupgrades_use_is_mixed_content_restricted_in_frame_enabled_>;
  using ScopedMobileLayoutTheme = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_mobile_layout_theme_enabled_>;
  using ScopedModifyParagraphCrossEditingoundary = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_modify_paragraph_cross_editingoundary_enabled_>;
  using ScopedModulePreloadReferrer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_module_preload_referrer_enabled_>;
  using ScopedModulePreloadStyleJson = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_module_preload_style_json_enabled_>;
  using ScopedMojoJS = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_mojo_js_enabled_>;
  using ScopedMojoJSTest = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_mojo_js_test_enabled_>;
  using ScopedMoveEndingSelectionToListChild = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_move_ending_selection_to_list_child_enabled_>;
  using ScopedMulticolColumnWrapping = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_multicol_column_wrapping_enabled_>;
  using ScopedNavigateEventAddHandlerOnPrecommit = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_navigate_event_add_handler_on_precommit_enabled_>;
  using ScopedNavigateEventClearOnRestore = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_navigate_event_clear_on_restore_enabled_>;
  using ScopedNavigateEventDeferCrossDocumentCommit = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_navigate_event_defer_cross_document_commit_enabled_>;
  using ScopedNavigationEventTiming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_navigation_event_timing_enabled_>;
  using ScopedNavigationId = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_navigation_id_enabled_>;
  using ScopedNavigatorContentUtils = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_navigator_content_utils_enabled_>;
  using ScopedNetInfoConstantType = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_net_info_constant_type_enabled_>;
  using ScopedNetInfoDownlinkMax = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_net_info_downlink_max_enabled_>;
  using ScopedNewHTMLSettingMethods = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_new_html_setting_methods_enabled_>;
  using ScopedNoExtendSelectionToUserSelectNoneOutOfFlow = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_no_extend_selection_to_user_select_none_out_of_flow_enabled_>;
  using ScopedNoFontAntialiasing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_no_font_antialiasing_enabled_>;
  using ScopedNoIdleEncodingForWebTests = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_no_idle_encoding_for_web_tests_enabled_>;
  using ScopedNonEmptyBlockquotesOnOutdenting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_non_empty_blockquotes_on_outdenting_enabled_>;
  using ScopedNonEmptyVisibleTextSelectionForTextFragment = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_non_empty_visible_text_selection_for_text_fragment_enabled_>;
  using ScopedNonStandardAppearanceValueSliderVertical = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_non_standard_appearance_value_slider_vertical_enabled_>;
  using ScopedNormalizeLineEndingsInInsertText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_normalize_line_endings_in_insert_text_enabled_>;
  using ScopedNormalizeNbspForPasteAndDrop = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_normalize_nbsp_for_paste_and_drop_enabled_>;
  using ScopedNotificationConstructor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_notification_constructor_enabled_>;
  using ScopedNotificationContentImage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_notification_content_image_enabled_>;
  using ScopedNotifications = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_notifications_enabled_>;
  using ScopedNotificationTriggers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_notification_triggers_enabled_>;
  using ScopedNumberInputFullWidthChars = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_number_input_full_width_chars_enabled_>;
  using ScopedOffMainThreadCSSPaint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_off_main_thread_css_paint_enabled_>;
  using ScopedOffscreenCanvasGetContextAttributes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_offscreen_canvas_get_context_attributes_enabled_>;
  using ScopedOffsetPathTransformUpdateFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_offset_path_transform_update_fix_enabled_>;
  using ScopedOmitBlurEventOnElementRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_omit_blur_event_on_element_removal_enabled_>;
  using ScopedOnDeviceWebSpeechAvailable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_on_device_web_speech_available_enabled_>;
  using ScopedOnDeviceWebSpeechQuality = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_on_device_web_speech_quality_enabled_>;
  using ScopedOpaqueRange = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_opaque_range_enabled_>;
  using ScopedOpenPopoverInvokerRestrictToSameTreeScope = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_open_popover_invoker_restrict_to_same_tree_scope_enabled_>;
  using ScopedOrientationEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_orientation_event_enabled_>;
  using ScopedOriginAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_api_enabled_>;
  using ScopedOriginIsolationHeader = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_isolation_header_enabled_>;
  using ScopedOriginPolicy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_policy_enabled_>;
  using ScopedOriginTrialsSampleAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_enabled_>;
  using ScopedOriginTrialsSampleAPIBrowserReadWrite = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_browser_read_write_enabled_>;
  using ScopedOriginTrialsSampleAPIDependent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_dependent_enabled_>;
  using ScopedOriginTrialsSampleAPIDeprecation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_deprecation_enabled_>;
  using ScopedOriginTrialsSampleAPIExpiryGracePeriod = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_expiry_grace_period_enabled_>;
  using ScopedOriginTrialsSampleAPIExpiryGracePeriodThirdParty = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_expiry_grace_period_third_party_enabled_>;
  using ScopedOriginTrialsSampleAPIImplied = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_implied_enabled_>;
  using ScopedOriginTrialsSampleAPIInvalidOS = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_invalid_os_enabled_>;
  using ScopedOriginTrialsSampleAPINavigation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_navigation_enabled_>;
  using ScopedOriginTrialsSampleAPIPersistentExpiryGracePeriod = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_persistent_expiry_grace_period_enabled_>;
  using ScopedOriginTrialsSampleAPIPersistentFeature = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_persistent_feature_enabled_>;
  using ScopedOriginTrialsSampleAPIPersistentInvalidOS = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_persistent_invalid_os_enabled_>;
  using ScopedOriginTrialsSampleAPIPersistentThirdPartyDeprecationFeature = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_persistent_third_party_deprecation_feature_enabled_>;
  using ScopedOriginTrialsSampleAPIThirdParty = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_origin_trials_sample_api_third_party_enabled_>;
  using ScopedOutlineDrawAutoStyleZeroWidth = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_outline_draw_auto_style_zero_width_enabled_>;
  using ScopedOverlayGlobalRuleRemoval = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_overlay_global_rule_removal_enabled_>;
  using ScopedOverlayProperty = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_overlay_property_enabled_>;
  using ScopedOverscrollGestures = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_overscroll_gestures_enabled_>;
  using ScopedPagePopup = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_page_popup_enabled_>;
  using ScopedPagePopupCopyPaste = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_page_popup_copy_paste_enabled_>;
  using ScopedPageRevealEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_page_reveal_event_enabled_>;
  using ScopedPageSwapEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_page_swap_event_enabled_>;
  using ScopedPaintHoldingForIframes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_paint_holding_for_iframes_enabled_>;
  using ScopedPaintOffsetTranslationForComposited = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_paint_offset_translation_for_composited_enabled_>;
  using ScopedPaintTimingMixin = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_paint_timing_mixin_enabled_>;
  using ScopedPaintUnderInvalidationChecking = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_paint_under_invalidation_checking_enabled_>;
  using ScopedParakeet = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_parakeet_enabled_>;
  using ScopedPartialCompletionNotAllowedInMoveParagraphs = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_partial_completion_not_allowed_in_move_paragraphs_enabled_>;
  using ScopedPartitionVisitedLinkDatabaseWithSelfLinks = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_partition_visited_link_database_with_self_links_enabled_>;
  using ScopedPasswordReveal = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_password_reveal_enabled_>;
  using ScopedPaymentApp = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_payment_app_enabled_>;
  using ScopedPaymentLinkDetection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_payment_link_detection_enabled_>;
  using ScopedPaymentMethodChangeEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_payment_method_change_event_enabled_>;
  using ScopedPaymentRequest = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_payment_request_enabled_>;
  using ScopedPerformanceManagerInstrumentation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_performance_manager_instrumentation_enabled_>;
  using ScopedPerformanceMarkCustomUserTimingFromSubframe = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_performance_mark_custom_user_timing_from_subframe_enabled_>;
  using ScopedPerformanceMarkFeatureUsage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_performance_mark_feature_usage_enabled_>;
  using ScopedPerformanceNavigationTimingConfidence = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_performance_navigation_timing_confidence_enabled_>;
  using ScopedPeriodicBackgroundSync = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_periodic_background_sync_enabled_>;
  using ScopedPerMethodCanMakePaymentQuota = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_per_method_can_make_payment_quota_enabled_>;
  using ScopedPermissionsRequestRevoke = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_permissions_request_revoke_enabled_>;
  using ScopedPlaceholderVisibility = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_placeholder_visibility_enabled_>;
  using ScopedPNaCl = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_p_na_cl_enabled_>;
  using ScopedPointerEventDeviceId = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_pointer_event_device_id_enabled_>;
  using ScopedPointerLockOnAndroid = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_pointer_lock_on_android_enabled_>;
  using ScopedPointerRawUpdateOnlyInSecureContext = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_pointer_raw_update_only_in_secure_context_enabled_>;
  using ScopedPopoverHintNewBehavior = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_popover_hint_new_behavior_enabled_>;
  using ScopedPositionOutsideTabSpanCheckSiblingNode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_position_outside_tab_span_check_sibling_node_enabled_>;
  using ScopedPositionVisibilityIgnoreNonClipAncestors = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_position_visibility_ignore_non_clip_ancestors_enabled_>;
  using ScopedPotentialPermissionsPolicyReporting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_potential_permissions_policy_reporting_enabled_>;
  using ScopedPreciseMemoryInfo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_precise_memory_info_enabled_>;
  using ScopedPreferDefaultScrollbarStyles = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prefer_default_scrollbar_styles_enabled_>;
  using ScopedPreferNonCompositedScrolling = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prefer_non_composited_scrolling_enabled_>;
  using ScopedPreferredAudioOutputDevices = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_preferred_audio_output_devices_enabled_>;
  using ScopedPrefersReducedData = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prefers_reduced_data_enabled_>;
  using ScopedPreloadLinkRelDataUrls = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_preload_link_rel_data_urls_enabled_>;
  using ScopedPrerender2 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prerender_2_enabled_>;
  using ScopedPrerender2CrossOriginIframes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prerender_2_cross_origin_iframes_enabled_>;
  using ScopedPrerenderActivationByFormSubmission = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prerender_activation_by_form_submission_enabled_>;
  using ScopedPrerenderUntilScript = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prerender_until_script_enabled_>;
  using ScopedPresentation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_presentation_enabled_>;
  using ScopedPreserveDropEffect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_preserve_drop_effect_enabled_>;
  using ScopedPreventUndoIfNotEditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_prevent_undo_if_not_editable_enabled_>;
  using ScopedPrivateAggregationApiErrorReporting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_private_aggregation_api_error_reporting_enabled_>;
  using ScopedPrivateAggregationApiMaxContributions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_private_aggregation_api_max_contributions_enabled_>;
  using ScopedPrivateNetworkAccessNullIpAddress = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_private_network_access_null_ip_address_enabled_>;
  using ScopedPrivateStateTokens = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_private_state_tokens_enabled_>;
  using ScopedPrivateStateTokensAlwaysAllowIssuance = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_private_state_tokens_always_allow_issuance_enabled_>;
  using ScopedProfilerAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_profiler_api_enabled_>;
  using ScopedProfilerAPIForDedicatedWorker = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_profiler_api_for_dedicated_worker_enabled_>;
  using ScopedProgrammaticScrollPromise = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_programmatic_scroll_promise_enabled_>;
  using ScopedProgressMaxIsPositive = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_progress_max_is_positive_enabled_>;
  using ScopedPropagateOverscrollBehaviorFromRoot = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_propagate_overscroll_behavior_from_root_enabled_>;
  using ScopedProtectedOriginTrialsSampleAPI = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_protected_origin_trials_sample_api_enabled_>;
  using ScopedProtectedOriginTrialsSampleAPIDependent = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_protected_origin_trials_sample_api_dependent_enabled_>;
  using ScopedProtectedOriginTrialsSampleAPIImplied = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_protected_origin_trials_sample_api_implied_enabled_>;
  using ScopedPseudoElementsFocusable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_pseudo_elements_focusable_enabled_>;
  using ScopedPseudoElementsHitTestable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_pseudo_elements_hit_testable_enabled_>;
  using ScopedPseudoElementsHoverable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_pseudo_elements_hoverable_enabled_>;
  using ScopedPushMessageDataBytes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_push_message_data_bytes_enabled_>;
  using ScopedPushMessaging = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_push_messaging_enabled_>;
  using ScopedPushMessagingSubscriptionChange = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_push_messaging_subscription_change_enabled_>;
  using ScopedQuotaExceededErrorUpdate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_quota_exceeded_error_update_enabled_>;
  using ScopedQuoteFirstLineStyle = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_quote_first_line_style_enabled_>;
  using ScopedRasterInducingScroll = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_raster_inducing_scroll_enabled_>;
  using ScopedReadableStreamBYOBReaderReadMinOption = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_readable_stream_byob_reader_read_min_option_enabled_>;
  using ScopedReadClipboardDataOnClipboardItemGetType = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_read_clipboard_data_on_clipboard_item_get_type_enabled_>;
  using ScopedReadingFlowWithSlots = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_reading_flow_with_slots_enabled_>;
  using ScopedRecheckParentDuringNodeVectorInsertion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_recheck_parent_during_node_vector_insertion_enabled_>;
  using ScopedRecordSameDocumentPresentationTimeOnce = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_record_same_document_presentation_time_once_enabled_>;
  using ScopedReduceAcceptLanguage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_reduce_accept_language_enabled_>;
  using ScopedReduceUserAgentDataLinuxPlatformVersion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_reduce_user_agent_data_linux_platform_version_enabled_>;
  using ScopedReduceUserAgentMinorVersion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_reduce_user_agent_minor_version_enabled_>;
  using ScopedRegionCapture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_region_capture_enabled_>;
  using ScopedRelatedWebsitePartitionAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_related_website_partition_api_enabled_>;
  using ScopedRelOpenerBcgDependencyHint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rel_opener_bcg_dependency_hint_enabled_>;
  using ScopedRemotePlayback = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remote_playback_enabled_>;
  using ScopedRemotePlaybackBackend = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remote_playback_backend_enabled_>;
  using ScopedRemoveCharsetAutoDetectionForISO2022JP = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_charset_auto_detection_for_iso_2022_jp_enabled_>;
  using ScopedRemoveChildrenInReplaceChildren = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_children_in_replace_children_enabled_>;
  using ScopedRemoveCollapsedPlaceholderForContentEditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_collapsed_placeholder_for_content_editable_enabled_>;
  using ScopedRemoveDanglingMarkupInTarget = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_dangling_markup_in_target_enabled_>;
  using ScopedRemoveDataUrlInSvgUse = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_data_url_in_svg_use_enabled_>;
  using ScopedRemoveFormatFilterBackgroundColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_format_filter_background_color_enabled_>;
  using ScopedRemoveNonAllowlistedCreateEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_non_allowlisted_create_event_enabled_>;
  using ScopedRemoveScrollNodeWorkaround = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_scroll_node_workaround_enabled_>;
  using ScopedRemoveSelectionCanonicalizationInMoveParagraph = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_selection_canonicalization_in_move_paragraph_enabled_>;
  using ScopedRemoveVisibleSelectionInDOMSelection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_remove_visible_selection_in_dom_selection_enabled_>;
  using ScopedRenderBlockingFullFrameRate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_render_blocking_full_frame_rate_enabled_>;
  using ScopedRenderBlockingStatus = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_render_blocking_status_enabled_>;
  using ScopedRenderPriorityAttribute = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_render_priority_attribute_enabled_>;
  using ScopedReportFirstFrameTimeAsRenderTime = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_report_first_frame_time_as_render_time_enabled_>;
  using ScopedReportLayoutShiftRectsInCssPixels = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_report_layout_shift_rects_in_css_pixels_enabled_>;
  using ScopedRequestIsReloadNavigation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_request_is_reload_navigation_enabled_>;
  using ScopedRequestMainFrameAfterFirstVideoFrame = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_request_main_frame_after_first_video_frame_enabled_>;
  using ScopedResolveVarStylesOnCopy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_resolve_var_styles_on_copy_enabled_>;
  using ScopedResourceTimingContentEncoding = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_resource_timing_content_encoding_enabled_>;
  using ScopedResourceTimingContentType = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_resource_timing_content_type_enabled_>;
  using ScopedResourceTimingInitiator = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_resource_timing_initiator_enabled_>;
  using ScopedResourceTimingUseCORSForBodySizes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_resource_timing_use_cors_for_body_sizes_enabled_>;
  using ScopedRespectOverscrollBehaviorForScrollBubbling = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_respect_overscroll_behavior_for_scroll_bubbling_enabled_>;
  using ScopedResponsiveIframes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_responsive_iframes_enabled_>;
  using ScopedRestrictGamepadAccess = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_restrict_gamepad_access_enabled_>;
  using ScopedRestrictOwnAudio = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_restrict_own_audio_enabled_>;
  using ScopedRootScrollbarFollowsBrowserTheme = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_root_scrollbar_follows_browser_theme_enabled_>;
  using ScopedRouteMatching = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_route_matching_enabled_>;
  using ScopedRtcAlwaysNegotiateDataChannels = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_always_negotiate_data_channels_enabled_>;
  using ScopedRtcAudioJitterBufferMaxPackets = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_audio_jitter_buffer_max_packets_enabled_>;
  using ScopedRTCDataChannelPriority = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_data_channel_priority_enabled_>;
  using ScopedRTCDiagnosticLogging = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_diagnostic_logging_enabled_>;
  using ScopedRTCEncodedFrameAudioLevel = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_encoded_frame_audio_level_enabled_>;
  using ScopedRTCEncodedFrameSetMetadata = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_encoded_frame_set_metadata_enabled_>;
  using ScopedRTCEncodedFrameTimestamps = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_encoded_frame_timestamps_enabled_>;
  using ScopedRTCEncodedVideoFrameAdditionalMetadata = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_encoded_video_frame_additional_metadata_enabled_>;
  using ScopedRTCJitterBufferTarget = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_jitter_buffer_target_enabled_>;
  using ScopedRTCLegacyCallbackBasedGetStats = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_legacy_callback_based_get_stats_enabled_>;
  using ScopedRTCRtpEncodingParametersCodec = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_rtp_encoding_parameters_codec_enabled_>;
  using ScopedRTCRtpScaleResolutionDownTo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_rtp_scale_resolution_down_to_enabled_>;
  using ScopedRTCRtpScriptTransform = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_rtp_script_transform_enabled_>;
  using ScopedRTCRtpTransport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_rtp_transport_enabled_>;
  using ScopedRTCStatsRelativePacketArrivalDelay = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_stats_relative_packet_arrival_delay_enabled_>;
  using ScopedRTCSvcScalabilityMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_rtc_svc_scalability_mode_enabled_>;
  using ScopedRunMicrotaskBeforeXmlScript = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_run_microtask_before_xml_script_enabled_>;
  using ScopedRunSnapshotPostLayoutStateSteps = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_run_snapshot_post_layout_state_steps_enabled_>;
  using ScopedSanitizerAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_sanitizer_api_enabled_>;
  using ScopedScopedCustomElementRegistry = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scoped_custom_element_registry_enabled_>;
  using ScopedScopedViewTransitions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scoped_view_transitions_enabled_>;
  using ScopedScreenDetailedHdrHeadroom = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_screen_detailed_hdr_headroom_enabled_>;
  using ScopedScriptBasedOnUnicodeBlock = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_script_based_on_unicode_block_enabled_>;
  using ScopedScriptedSpeechRecognition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scripted_speech_recognition_enabled_>;
  using ScopedScriptedSpeechSynthesis = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scripted_speech_synthesis_enabled_>;
  using ScopedScrollAnchorPriorityCandidateSubtree = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_anchor_priority_candidate_subtree_enabled_>;
  using ScopedScrollAnchorSerializationUseParentForTextNode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_anchor_serialization_use_parent_for_text_node_enabled_>;
  using ScopedScrollbarColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scrollbar_color_enabled_>;
  using ScopedScrollbarGutterBugFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scrollbar_gutter_bug_fix_enabled_>;
  using ScopedScrollbarWidth = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scrollbar_width_enabled_>;
  using ScopedScrollIntoViewNearest = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_into_view_nearest_enabled_>;
  using ScopedScrollIntoViewRootFrameViewportBugFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_into_view_root_frame_viewport_bug_fix_enabled_>;
  using ScopedScrollTimelineCurrentTime = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_timeline_current_time_enabled_>;
  using ScopedScrollTimelineNamedRangeScroll = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_timeline_named_range_scroll_enabled_>;
  using ScopedScrollTopLeftInterop = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_top_left_interop_enabled_>;
  using ScopedScrollToTextFragmentUniqueFragments = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_scroll_to_text_fragment_unique_fragments_enabled_>;
  using ScopedSearchTextHighlightPseudo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_search_text_highlight_pseudo_enabled_>;
  using ScopedSecurePaymentConfirmation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_secure_payment_confirmation_enabled_>;
  using ScopedSecurePaymentConfirmationAvailabilityAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_secure_payment_confirmation_availability_api_enabled_>;
  using ScopedSecurePaymentConfirmationCapabilities = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_secure_payment_confirmation_capabilities_enabled_>;
  using ScopedSecurePaymentConfirmationDebug = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_secure_payment_confirmation_debug_enabled_>;
  using ScopedSecurePaymentConfirmationOptOut = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_secure_payment_confirmation_opt_out_enabled_>;
  using ScopedSelectAudioOutput = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_select_audio_output_enabled_>;
  using ScopedSelectedcontentelementAttribute = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selectedcontentelement_attribute_enabled_>;
  using ScopedSelectedcontentMultiple = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selectedcontent_multiple_enabled_>;
  using ScopedSelectedcontentSpec = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selectedcontent_spec_enabled_>;
  using ScopedSelectionAndFocusedVisiblePositionMatch = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_and_focused_visible_position_match_enabled_>;
  using ScopedSelectionCollapsedDirectionNone = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_collapsed_direction_none_enabled_>;
  using ScopedSelectionFocusAffinity = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_focus_affinity_enabled_>;
  using ScopedSelectionHandleWithBottomClipped = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_handle_with_bottom_clipped_enabled_>;
  using ScopedSelectionRemoveRangeNotFoundError = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_remove_range_not_found_error_enabled_>;
  using ScopedSelectionSetBaseAndExtentNonNullNode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_set_base_and_extent_non_null_node_enabled_>;
  using ScopedSelectionToStringSkipsUserSelectNone = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_to_string_skips_user_select_none_enabled_>;
  using ScopedSelectionUpdateOnlyAfterAutoscroll = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_update_only_after_autoscroll_enabled_>;
  using ScopedSelectionUpdateToInitialSelectionInListify = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selection_update_to_initial_selection_in_listify_enabled_>;
  using ScopedSelectiveClipboardFormatRead = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selective_clipboard_format_read_enabled_>;
  using ScopedSelectivePermissionsIntervention = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_selective_permissions_intervention_enabled_>;
  using ScopedSelectRemoveOverflowHidden = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_select_remove_overflow_hidden_enabled_>;
  using ScopedSendBeaconThrowForBlobWithNonSimpleType = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_send_beacon_throw_for_blob_with_non_simple_type_enabled_>;
  using ScopedSendSlotChangeSignalAfterNodeInserted = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_send_slot_change_signal_after_node_inserted_enabled_>;
  using ScopedSensorExtraClasses = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_sensor_extra_classes_enabled_>;
  using ScopedSeparateDeferModuleScriptTasks = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_separate_defer_module_script_tasks_enabled_>;
  using ScopedSerial = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_serial_enabled_>;
  using ScopedSerializeViewTransitionStateInSPA = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_serialize_view_transition_state_in_spa_enabled_>;
  using ScopedSerialPortConnected = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_serial_port_connected_enabled_>;
  using ScopedServiceWorkerBackgroundSyncInDedicatedWorker = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_service_worker_background_sync_in_dedicated_worker_enabled_>;
  using ScopedServiceWorkerClientLifecycleState = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_service_worker_client_lifecycle_state_enabled_>;
  using ScopedServiceWorkerInDedicatedWorker = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_service_worker_in_dedicated_worker_enabled_>;
  using ScopedServiceWorkerStaticRouterTimingInfo = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_service_worker_static_router_timing_info_enabled_>;
  using ScopedSetDefaultDropEffect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_set_default_drop_effect_enabled_>;
  using ScopedSetHTMLCanRunScripts = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_set_html_can_run_scripts_enabled_>;
  using ScopedSetSequentialFocusStartingPoint = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_set_sequential_focus_starting_point_enabled_>;
  using ScopedShadowContourFollowsBorder = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shadow_contour_follows_border_enabled_>;
  using ScopedShadowRootAdoptedStyleSheet = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shadow_root_adopted_style_sheet_enabled_>;
  using ScopedShadowRootReferenceTarget = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shadow_root_reference_target_enabled_>;
  using ScopedShadowRootReferenceTargetAriaOwns = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shadow_root_reference_target_aria_owns_enabled_>;
  using ScopedSharedArrayBuffer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shared_array_buffer_enabled_>;
  using ScopedSharedArrayBufferUnrestrictedAccessAllowed = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shared_array_buffer_unrestricted_access_allowed_enabled_>;
  using ScopedSharedStorageAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shared_storage_api_enabled_>;
  using ScopedSharedStorageWebLocks = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shared_storage_web_locks_enabled_>;
  using ScopedSharedWorker = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shared_worker_enabled_>;
  using ScopedSharedWorkerExtendedLifetime = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_shared_worker_extended_lifetime_enabled_>;
  using ScopedSideRelativeBackgroundPosition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_side_relative_background_position_enabled_>;
  using ScopedSignatureBasedInlineIntegrity = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_signature_based_inline_integrity_enabled_>;
  using ScopedSingleAxisScrollContainers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_single_axis_scroll_containers_enabled_>;
  using ScopedSkipAd = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_ad_enabled_>;
  using ScopedSkipCallbacksWhenDevToolsNotOpen = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_callbacks_when_dev_tools_not_open_enabled_>;
  using ScopedSkipEventCapture = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_event_capture_enabled_>;
  using ScopedSkipNonEditableInAtomicMove = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_non_editable_in_atomic_move_enabled_>;
  using ScopedSkipOofItemForBreakCandidate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_oof_item_for_break_candidate_enabled_>;
  using ScopedSkipParagraphSplitForInlineInsertHTML = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_paragraph_split_for_inline_insert_html_enabled_>;
  using ScopedSkipPseudoOnlyLinesInLineNavigation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_pseudo_only_lines_in_line_navigation_enabled_>;
  using ScopedSkipTouchEventFilter = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_touch_event_filter_enabled_>;
  using ScopedSkipUnselectableContentInSerialization = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_unselectable_content_in_serialization_enabled_>;
  using ScopedSkipUnselectableElementsInParagraphBoundary = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_skip_unselectable_elements_in_paragraph_boundary_enabled_>;
  using ScopedSmallerViewportUnits = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_smaller_viewport_units_enabled_>;
  using ScopedSmartCard = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_smart_card_enabled_>;
  using ScopedSmartZoom = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_smart_zoom_enabled_>;
  using ScopedSnapshotScrollTimelinesPostLayout = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_snapshot_scroll_timelines_post_layout_enabled_>;
  using ScopedSoftNavigationDetection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_soft_navigation_detection_enabled_>;
  using ScopedSoftNavigationDetectionIncludeReplaceState = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_soft_navigation_detection_include_replace_state_enabled_>;
  using ScopedSoftNavigationHeuristics = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_soft_navigation_heuristics_enabled_>;
  using ScopedSortedLayoutShiftSourcesByImpactArea = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_sorted_layout_shift_sources_by_impact_area_enabled_>;
  using ScopedSourceSpecificMulticastInDirectSockets = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_source_specific_multicast_in_direct_sockets_enabled_>;
  using ScopedSpatNavUsesCursorInheritance = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_spat_nav_uses_cursor_inheritance_enabled_>;
  using ScopedSpeakerSelection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_speaker_selection_enabled_>;
  using ScopedSpeculationMeasurement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_speculation_measurement_enabled_>;
  using ScopedSpellCheckCustomDictionaryAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_spell_check_custom_dictionary_api_enabled_>;
  using ScopedSplitTextNotCleanupDummySpans = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_split_text_not_cleanup_dummy_spans_enabled_>;
  using ScopedSplitViewLinkOpen = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_split_view_link_open_enabled_>;
  using ScopedSrcsetSelectionMatchesImageSet = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_srcset_selection_matches_image_set_enabled_>;
  using ScopedStableBlinkFeatures = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_stable_blink_features_enabled_>;
  using ScopedStackingContextIsNotStacked = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_stacking_context_is_not_stacked_enabled_>;
  using ScopedStandardizedBrowserZoom = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_standardized_browser_zoom_enabled_>;
  using ScopedStandardizedBrowserZoomOptOut = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_standardized_browser_zoom_opt_out_enabled_>;
  using ScopedStickyPositionHasOverflowPerAxis = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_sticky_position_has_overflow_per_axis_enabled_>;
  using ScopedStickyUserActivationAcrossSameOriginNavigation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_sticky_user_activation_across_same_origin_navigation_enabled_>;
  using ScopedStorageBuckets = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_storage_buckets_enabled_>;
  using ScopedStorageBucketsDurability = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_storage_buckets_durability_enabled_>;
  using ScopedStorageBucketsLocks = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_storage_buckets_locks_enabled_>;
  using ScopedStreamingSanitizer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_streaming_sanitizer_enabled_>;
  using ScopedStrictMimeTypesForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_strict_mime_types_for_workers_enabled_>;
  using ScopedStylusHandwriting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_stylus_handwriting_enabled_>;
  using ScopedSubApps = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_sub_apps_enabled_>;
  using ScopedSuppressPointerStreamAfterDrag = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_suppress_pointer_stream_after_drag_enabled_>;
  using ScopedSvgAnchorElementAttributes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_anchor_element_attributes_enabled_>;
  using ScopedSvgAnchorElementDownloadAttribute = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_anchor_element_download_attribute_enabled_>;
  using ScopedSvgAnimateMotionDiscreteCalcMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_animate_motion_discrete_calc_mode_enabled_>;
  using ScopedSvgAvoidResettingFilterQualityForTiledPattern = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_avoid_resetting_filter_quality_for_tiled_pattern_enabled_>;
  using ScopedSVGEmbeddedAsReplacedElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_embedded_as_replaced_element_enabled_>;
  using ScopedSvgEnableTextDecorationCssStyling = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_enable_text_decoration_css_styling_enabled_>;
  using ScopedSvgFallBackToContainerSize = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_fall_back_to_container_size_enabled_>;
  using ScopedSvgFeImageSkipHiddenContainerViewportDependence = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_fe_image_skip_hidden_container_viewport_dependence_enabled_>;
  using ScopedSvgFilterPaintsForHiddenContent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_filter_paints_for_hidden_content_enabled_>;
  using ScopedSvgFilterUserSpaceViewportForSvg = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_filter_user_space_viewport_for_svg_enabled_>;
  using ScopedSvgIgnoreNegativeEllipseRadii = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_ignore_negative_ellipse_radii_enabled_>;
  using ScopedSvgInlineRootPixelSnappingScaleAdjustment = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_inline_root_pixel_snapping_scale_adjustment_enabled_>;
  using ScopedSvgLengthListClearOnParsingFailure = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_length_list_clear_on_parsing_failure_enabled_>;
  using ScopedSvgLengthResolveUnparsedValue = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_length_resolve_unparsed_value_enabled_>;
  using ScopedSvgNumberListClearOnParsingFailure = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_number_list_clear_on_parsing_failure_enabled_>;
  using ScopedSvgPartitionSVGDocumentResourcesInMemoryCache = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_partition_svg_document_resources_in_memory_cache_enabled_>;
  using ScopedSvgPathLengthCssProperty = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_path_length_css_property_enabled_>;
  using ScopedSvgPointListClearOnParsingFailure = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_point_list_clear_on_parsing_failure_enabled_>;
  using ScopedSvgScriptElementAsyncAttribute = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_script_element_async_attribute_enabled_>;
  using ScopedSvgSizingWithPreserveAspectRatioNone = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_sizing_with_preserve_aspect_ratio_none_enabled_>;
  using ScopedSvgSmilClockValueValidation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_smil_clock_value_validation_enabled_>;
  using ScopedSvgTextPathPathAttribute = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_text_path_path_attribute_enabled_>;
  using ScopedSvgTransformOnNestedSvgElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_svg_transform_on_nested_svg_element_enabled_>;
  using ScopedSynthesizedKeyboardEventsForAccessibilityActions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_synthesized_keyboard_events_for_accessibility_actions_enabled_>;
  using ScopedSyntheticMouseHoverOverInactivePage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_synthetic_mouse_hover_over_inactive_page_enabled_>;
  using ScopedSystemDefaultAccentColors = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_system_default_accent_colors_enabled_>;
  using ScopedSystemFallbackEmojiVSSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_system_fallback_emoji_vs_support_enabled_>;
  using ScopedSystemWakeLock = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_system_wake_lock_enabled_>;
  using ScopedTableBorderColorNoImplicitBorder = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_table_border_color_no_implicit_border_enabled_>;
  using ScopedTableDefaultBorderColorCurrentColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_table_default_border_color_current_color_enabled_>;
  using ScopedTableIsAutoFixedLayout = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_table_is_auto_fixed_layout_enabled_>;
  using ScopedTabSizeAncestor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_tab_size_ancestor_enabled_>;
  using ScopedTabSizeWithSpacing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_tab_size_with_spacing_enabled_>;
  using ScopedTargetInShadowDeterminedBeforeListener = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_target_in_shadow_determined_before_listener_enabled_>;
  using ScopedTestBlinkFeatureDefault = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_test_blink_feature_default_enabled_>;
  using ScopedTestFeature = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_test_feature_enabled_>;
  using ScopedTestFeatureDependent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_test_feature_dependent_enabled_>;
  using ScopedTestFeatureForBrowserProcessReadWriteAccessOriginTrial = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_test_feature_for_browser_process_read_write_access_origin_trial_enabled_>;
  using ScopedTestFeatureImplied = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_test_feature_implied_enabled_>;
  using ScopedTestFeatureProtected = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_test_feature_protected_enabled_>;
  using ScopedTestFeatureProtectedDependent = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_test_feature_protected_dependent_enabled_>;
  using ScopedTestFeatureProtectedImplied = ScopedRuntimeEnabledProtectedFeature<
    RuntimeEnabledFeaturesBase::is_test_feature_protected_implied_enabled_>;
  using ScopedTestFeatureStable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_test_feature_stable_enabled_>;
  using ScopedTextAreaScrollTopPreview = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_area_scroll_top_preview_enabled_>;
  using ScopedTextDetector = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_detector_enabled_>;
  using ScopedTextEmphasisLetterSpacing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_emphasis_letter_spacing_enabled_>;
  using ScopedTextEmphasisPositionAuto = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_emphasis_position_auto_enabled_>;
  using ScopedTextEmphasisPunctuationExceptions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_emphasis_punctuation_exceptions_enabled_>;
  using ScopedTextEmphasisWithRuby = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_emphasis_with_ruby_enabled_>;
  using ScopedTextFragmentAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_fragment_api_enabled_>;
  using ScopedTextFragmentIdentifiers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_fragment_identifiers_enabled_>;
  using ScopedTextFragmentTapOpensContextMenu = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_fragment_tap_opens_context_menu_enabled_>;
  using ScopedTextMetricsBaselines = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_metrics_baselines_enabled_>;
  using ScopedTextOverflowClipWithSelection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_overflow_clip_with_selection_enabled_>;
  using ScopedTextOverflowString = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_overflow_string_enabled_>;
  using ScopedTextScaleMetaTag = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_scale_meta_tag_enabled_>;
  using ScopedTextSpacingTrimFallback = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_spacing_trim_fallback_enabled_>;
  using ScopedTextSpacingTrimFallback2 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_spacing_trim_fallback_2_enabled_>;
  using ScopedTextSpacingTrimFallbackChws = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_spacing_trim_fallback_chws_enabled_>;
  using ScopedTextSpacingTrimYuGothicUI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_text_spacing_trim_yu_gothic_ui_enabled_>;
  using ScopedThrottledHistoryAPIThrowsSecurityError = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_throttled_history_api_throws_security_error_enabled_>;
  using ScopedTimelineTrigger = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_timeline_trigger_enabled_>;
  using ScopedTimerThrottlingForBackgroundTabs = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_timer_throttling_for_background_tabs_enabled_>;
  using ScopedTimestampBasedCLSTracking = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_timestamp_based_cls_tracking_enabled_>;
  using ScopedTimeZoneChangeEvent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_time_zone_change_event_enabled_>;
  using ScopedTopicsAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_topics_api_enabled_>;
  using ScopedTopicsDocumentAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_topics_document_api_enabled_>;
  using ScopedTopicsImgAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_topics_img_api_enabled_>;
  using ScopedTouchDragAndContextMenu = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_touch_drag_and_context_menu_enabled_>;
  using ScopedTouchDragAndDrop = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_touch_drag_and_drop_enabled_>;
  using ScopedTouchDragOnShortPress = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_touch_drag_on_short_press_enabled_>;
  using ScopedTouchEventFeatureDetection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_touch_event_feature_detection_enabled_>;
  using ScopedTouchTextEditingRedesign = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_touch_text_editing_redesign_enabled_>;
  using ScopedTransferableRTCDataChannel = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_transferable_rtc_data_channel_enabled_>;
  using ScopedTransitionNavigationQuietSkip = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_transition_navigation_quiet_skip_enabled_>;
  using ScopedTranslateService = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_translate_service_enabled_>;
  using ScopedTranslationAPI = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_translation_api_enabled_>;
  using ScopedTranslationAPIForWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_translation_api_for_workers_enabled_>;
  using ScopedTraverseFlatTreeToHandleSlots = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_traverse_flat_tree_to_handle_slots_enabled_>;
  using ScopedTreatMhtmlInitialDocumentLoadsAsCrossDocument = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_treat_mhtml_initial_document_loads_as_cross_document_enabled_>;
  using ScopedTrustedTypesCreateParserOptions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_trusted_types_create_parser_options_enabled_>;
  using ScopedTrustedTypesFromLiteral = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_trusted_types_from_literal_enabled_>;
  using ScopedTrustedTypesHTML = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_trusted_types_html_enabled_>;
  using ScopedTrustedTypesUseCodeLike = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_trusted_types_use_code_like_enabled_>;
  using ScopedTwoPhaseViewTransition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_two_phase_view_transition_enabled_>;
  using ScopedUnclosedFormControlIsInvalid = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_unclosed_form_control_is_invalid_enabled_>;
  using ScopedUnexposedTaskIds = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_unexposed_task_ids_enabled_>;
  using ScopedUnprefixedSpeechRecognition = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_unprefixed_speech_recognition_enabled_>;
  using ScopedUnrestrictedMeasureUserAgentSpecificMemory = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_unrestricted_measure_user_agent_specific_memory_enabled_>;
  using ScopedUnrestrictedSharedArrayBuffer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_unrestricted_shared_array_buffer_enabled_>;
  using ScopedUnrestrictedUsb = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_unrestricted_usb_enabled_>;
  using ScopedUpdateComplexSafaAreaConstraints = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_update_complex_safa_area_constraints_enabled_>;
  using ScopedUpdateSelectionOnNodeInsertion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_update_selection_on_node_insertion_enabled_>;
  using ScopedUpdateTrivalTextAfterFragmentCreationFromText = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_update_trival_text_after_fragment_creation_from_text_enabled_>;
  using ScopedURLPatternCompareComponent = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_url_pattern_compare_component_enabled_>;
  using ScopedURLPatternGenerate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_url_pattern_generate_enabled_>;
  using ScopedURLSearchParamsHasAndDeleteMultipleArgs = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_url_search_params_has_and_delete_multiple_args_enabled_>;
  using ScopedUseBeginFramePresentationFeedback = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_begin_frame_presentation_feedback_enabled_>;
  using ScopedUseBoundedSelectionOffsetsInEditContextDeleteOperations = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_bounded_selection_offsets_in_edit_context_delete_operations_enabled_>;
  using ScopedUseLargestPaintedImageForLCPCandidate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_largest_painted_image_for_lcp_candidate_enabled_>;
  using ScopedUseLowQualityInterpolation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_low_quality_interpolation_enabled_>;
  using ScopedUseOriginalDomOffsetsForOffsetMap = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_original_dom_offsets_for_offset_map_enabled_>;
  using ScopedUsePositionForPointInFlexibleBoxWithSingleChildElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_position_for_point_in_flexible_box_with_single_child_element_enabled_>;
  using ScopedUsePositionIfIsVisuallyEquivalentCandidate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_position_if_is_visually_equivalent_candidate_enabled_>;
  using ScopedUserActionPseudosStopAtTopLayer = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_user_action_pseudos_stop_at_top_layer_enabled_>;
  using ScopedUserDefinedEntryPointTiming = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_user_defined_entry_point_timing_enabled_>;
  using ScopedUserMediaElement = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_user_media_element_enabled_>;
  using ScopedUseSelectionInDOMTreeAnchorInExtendSelection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_selection_in_dom_tree_anchor_in_extend_selection_enabled_>;
  using ScopedUseShadowHostStyleCheckEditable = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_shadow_host_style_check_editable_enabled_>;
  using ScopedUseUndoStepElementDispatchBeforeInput = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_use_undo_step_element_dispatch_before_input_enabled_>;
  using ScopedV8IdleTasks = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_v8_idle_tasks_enabled_>;
  using ScopedVideoAutoFullscreen = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_auto_fullscreen_enabled_>;
  using ScopedVideoFrameMetadataBackgroundBlur = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_frame_metadata_background_blur_enabled_>;
  using ScopedVideoFrameMetadataRtpTimestamp = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_frame_metadata_rtp_timestamp_enabled_>;
  using ScopedVideoFullscreenOrientationLock = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_fullscreen_orientation_lock_enabled_>;
  using ScopedVideoRotateToFullscreen = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_rotate_to_fullscreen_enabled_>;
  using ScopedVideoTrackGenerator = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_track_generator_enabled_>;
  using ScopedVideoTrackGeneratorInWindow = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_track_generator_in_window_enabled_>;
  using ScopedVideoTrackGeneratorInWorker = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_video_track_generator_in_worker_enabled_>;
  using ScopedViewportHeightClientHintHeader = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_viewport_height_client_hint_header_enabled_>;
  using ScopedViewportSegments = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_viewport_segments_enabled_>;
  using ScopedViewTransitionAsyncFinished = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_view_transition_async_finished_enabled_>;
  using ScopedViewTransitionDelayUnpauseOnTeardown = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_view_transition_delay_unpause_on_teardown_enabled_>;
  using ScopedViewTransitionHoistBackdropFilterEffect = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_view_transition_hoist_backdrop_filter_effect_enabled_>;
  using ScopedViewTransitionLongCallbackTimeoutForTesting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_view_transition_long_callback_timeout_for_testing_enabled_>;
  using ScopedViewTransitionUpdateLifecycleBeforeReady = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_view_transition_update_lifecycle_before_ready_enabled_>;
  using ScopedViewTransitionWaitUntil = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_view_transition_wait_until_enabled_>;
  using ScopedVisibilityCollapseColumn = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_visibility_collapse_column_enabled_>;
  using ScopedVisualRectMappingFixForExpansion = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_visual_rect_mapping_fix_for_expansion_enabled_>;
  using ScopedWakeLock = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_wake_lock_enabled_>;
  using ScopedWarnOnContentVisibilityRenderAccess = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_warn_on_content_visibility_render_access_enabled_>;
  using ScopedWebAppInstallation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_installation_enabled_>;
  using ScopedWebAppLaunchQueue = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_launch_queue_enabled_>;
  using ScopedWebAppScopeExtensions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_scope_extensions_enabled_>;
  using ScopedWebAppScopeSystemAccentColor = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_scope_system_accent_color_enabled_>;
  using ScopedWebAppTabStrip = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_tab_strip_enabled_>;
  using ScopedWebAppTabStripCustomizations = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_tab_strip_customizations_enabled_>;
  using ScopedWebAppTranslations = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_app_translations_enabled_>;
  using ScopedWebAssemblyCustomDescriptorsV2 = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_assembly_custom_descriptors_v_2_enabled_>;
  using ScopedWebAssemblyJSPromiseIntegration = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_assembly_js_promise_integration_enabled_>;
  using ScopedWebAudioBypassOutputBuffering = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_audio_bypass_output_buffering_enabled_>;
  using ScopedWebAudioBypassOutputBufferingOptOut = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_audio_bypass_output_buffering_opt_out_enabled_>;
  using ScopedWebAudioConfigurableRenderQuantum = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_audio_configurable_render_quantum_enabled_>;
  using ScopedWebAuth = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_auth_enabled_>;
  using ScopedWebAuthAuthenticatorAttachment = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_auth_authenticator_attachment_enabled_>;
  using ScopedWebAuthenticationAmbient = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_authentication_ambient_enabled_>;
  using ScopedWebAuthenticationAttestationFormats = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_authentication_attestation_formats_enabled_>;
  using ScopedWebAuthenticationImmediateGet = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_authentication_immediate_get_enabled_>;
  using ScopedWebAuthenticationRemoteDesktopSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_authentication_remote_desktop_support_enabled_>;
  using ScopedWebAuthenticationSupplementalPubKeys = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_authentication_supplemental_pub_keys_enabled_>;
  using ScopedWebBluetooth = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_bluetooth_enabled_>;
  using ScopedWebBluetoothGetDevices = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_bluetooth_get_devices_enabled_>;
  using ScopedWebBluetoothScanning = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_bluetooth_scanning_enabled_>;
  using ScopedWebBluetoothWatchAdvertisements = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_bluetooth_watch_advertisements_enabled_>;
  using ScopedWebCodecsVideoEncoderBuffers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webcodecs_video_encoder_buffers_enabled_>;
  using ScopedWebCryptoPQC = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_crypto_pqc_enabled_>;
  using ScopedWebFontResizeLCP = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_font_resize_lcp_enabled_>;
  using ScopedWebGLDeveloperExtensions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgl_developer_extensions_enabled_>;
  using ScopedWebGLDraftExtensions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgl_draft_extensions_enabled_>;
  using ScopedWebGLDrawingBufferStorage = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgl_drawing_buffer_storage_enabled_>;
  using ScopedWebGLOnWebGPU = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgl_on_webgpu_enabled_>;
  using ScopedWebGPUCompatibilityMode = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_compatibility_mode_enabled_>;
  using ScopedWebGPUDeveloperFeatures = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_developer_features_enabled_>;
  using ScopedWebGPUExperimentalFeatures = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_experimental_features_enabled_>;
  using ScopedWebGPUImmediatesFeature = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_immediates_feature_enabled_>;
  using ScopedWebGPUMapSyncOnWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_map_sync_on_workers_enabled_>;
  using ScopedWebGPUMultithreadDawnWireOnWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_multithread_dawn_wire_on_workers_enabled_>;
  using ScopedWebGPUTransientAttachment = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_webgpu_transient_attachment_enabled_>;
  using ScopedWebHID = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_hid_enabled_>;
  using ScopedWebHIDOnServiceWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_hid_on_service_workers_enabled_>;
  using ScopedWebIdentityDigitalCredentials = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_identity_digital_credentials_enabled_>;
  using ScopedWebIdentityDigitalCredentialsCreation = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_identity_digital_credentials_creation_enabled_>;
  using ScopedWebIDLBigIntUsesToBigInt = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_idl_big_int_uses_to_big_int_enabled_>;
  using ScopedWebMCP = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_mcp_enabled_>;
  using ScopedWebMCPDeclarativeFileInput = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_mcp_declarative_file_input_enabled_>;
  using ScopedWebMCPFormAssociatedCustomElements = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_mcp_form_associated_custom_elements_enabled_>;
  using ScopedWebMCPTesting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_mcp_testing_enabled_>;
  using ScopedWebNFC = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_nfc_enabled_>;
  using ScopedWebOTP = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_otp_enabled_>;
  using ScopedWebOTPAssertionFeaturePolicy = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_otp_assertion_feature_policy_enabled_>;
  using ScopedWebPreferences = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_preferences_enabled_>;
  using ScopedWebPrinting = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_printing_enabled_>;
  using ScopedWebShare = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_share_enabled_>;
  using ScopedWebSocketStream = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_websocket_stream_enabled_>;
  using ScopedWebSocketStreamStandardBinaryChunkType = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_websocket_stream_standard_binary_chunk_type_enabled_>;
  using ScopedWebSpeechRecognitionContext = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_speech_recognition_context_enabled_>;
  using ScopedWebTransportApplicationProtocol = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_transport_application_protocol_enabled_>;
  using ScopedWebTransportCongestionControl = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_transport_congestion_control_enabled_>;
  using ScopedWebTransportCustomCertificates = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_transport_custom_certificates_enabled_>;
  using ScopedWebTransportSendGroup = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_transport_send_group_enabled_>;
  using ScopedWebTransportStats = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_transport_stats_enabled_>;
  using ScopedWebUIBundledCodeCacheAsyncFetch = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_ui_bundled_code_cache_async_fetch_enabled_>;
  using ScopedWebUSB = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_usb_enabled_>;
  using ScopedWebUSBOnDedicatedWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_usb_on_dedicated_workers_enabled_>;
  using ScopedWebUSBOnServiceWorkers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_usb_on_service_workers_enabled_>;
  using ScopedWebVTTRegions = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_vtt_regions_enabled_>;
  using ScopedWebXR = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_enabled_>;
  using ScopedWebXREnabledFeatures = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_enabled_features_enabled_>;
  using ScopedWebXRFrameRate = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_frame_rate_enabled_>;
  using ScopedWebXRFrontFacing = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_front_facing_enabled_>;
  using ScopedWebXRGPUBinding = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_gpu_binding_enabled_>;
  using ScopedWebXRHitTestEntityTypes = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_hit_test_entity_types_enabled_>;
  using ScopedWebXRImageTracking = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_image_tracking_enabled_>;
  using ScopedWebXRLayers = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_layers_enabled_>;
  using ScopedWebXRLayersCommon = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_layers_common_enabled_>;
  using ScopedWebXRMeshDetection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_mesh_detection_enabled_>;
  using ScopedWebXRPlaneDetection = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_plane_detection_enabled_>;
  using ScopedWebXRPoseMotionData = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_pose_motion_data_enabled_>;
  using ScopedWebXRSpecParity = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_spec_parity_enabled_>;
  using ScopedWebXRVisibilityMask = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_web_xr_visibility_mask_enabled_>;
  using ScopedWindowDefaultStatus = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_window_default_status_enabled_>;
  using ScopedWordSkipSpacesPunctuationFix = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_word_skip_spaces_punctuation_fix_enabled_>;
  using ScopedWordSpacingWhiteSpacePre = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_word_spacing_white_space_pre_enabled_>;
  using ScopedXMLNoExternalEntities = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xml_no_external_entities_enabled_>;
  using ScopedXMLParsingRust = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xml_parsing_rust_enabled_>;
  using ScopedXMLRustForNonXslt = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xml_rust_for_non_xslt_enabled_>;
  using ScopedXMLSerializerConsistentDefaultNsDeclMatching = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xml_serializer_consistent_default_ns_decl_matching_enabled_>;
  using ScopedXPathShadowDOMSupport = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xpath_shadow_dom_support_enabled_>;
  using ScopedXSLT = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xslt_enabled_>;
  using ScopedXSLTSpecialTrial = ScopedRuntimeEnabledFeature<
      RuntimeEnabledFeaturesBase::is_xslt_special_trial_enabled_>;
};

using ScopedAboutBlankPageRespectsDarkModeOnUserActionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAboutBlankPageRespectsDarkModeOnUserAction;
using ScopedAccelerated2dCanvasForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccelerated2dCanvas;
using ScopedAcceleratedSmallCanvasesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAcceleratedSmallCanvases;
using ScopedAccessibilityAriaVirtualContentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityAriaVirtualContent;
using ScopedAccessibilityCustomElementRoleNoneForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityCustomElementRoleNone;
using ScopedAccessibilityExposeDisplayNoneForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityExposeDisplayNone;
using ScopedAccessibilityImplicitActionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityImplicitActions;
using ScopedAccessibilityMinRoleTabbableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityMinRoleTabbable;
using ScopedAccessibilityOSLevelBoldTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityOSLevelBoldText;
using ScopedAccessibilityProhibitedNamesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityProhibitedNames;
using ScopedAccessibilitySerializationSizeMetricsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilitySerializationSizeMetrics;
using ScopedAccessibilityUseAXPositionForDocumentMarkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessibilityUseAXPositionForDocumentMarkers;
using ScopedAccessKeyLabelForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAccessKeyLabel;
using ScopedAddressSpaceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAddressSpace;
using ScopedAdInterestGroupAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAdInterestGroupAPI;
using ScopedAdjustDOMOffsetToLayoutOffsetForSecureTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAdjustDOMOffsetToLayoutOffsetForSecureText;
using ScopedAdjustEndOfNextParagraphIfMovedParagraphIsUpdatedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAdjustEndOfNextParagraphIfMovedParagraphIsUpdated;
using ScopedAdTaggingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAdTagging;
using ScopedAIClassifierAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIClassifierAPI;
using ScopedAIPageContentAnchoredOffscreenNonActionabilityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentAnchoredOffscreenNonActionability;
using ScopedAIPageContentBuildOnLoadForTestingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentBuildOnLoadForTesting;
using ScopedAIPageContentCheckGeometryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentCheckGeometry;
using ScopedAIPageContentConvertNodeTextToUtf8ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentConvertNodeTextToUtf8;
using ScopedAIPageContentElementCSSRedactionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentElementCSSRedaction;
using ScopedAIPageContentIncludeSVGSubtreeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentIncludeSVGSubtree;
using ScopedAIPageContentOuterBoxMapToAncestorSpaceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentOuterBoxMapToAncestorSpace;
using ScopedAIPageContentPaidContentAnnotationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentPaidContentAnnotation;
using ScopedAIPageContentVisualViewportClampForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPageContentVisualViewportClamp;
using ScopedAIPromptAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPI;
using ScopedAIPromptAPIForExtensionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPIForExtension;
using ScopedAIPromptAPIForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPIForWorkers;
using ScopedAIPromptAPILegacyIdentifiersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPILegacyIdentifiers;
using ScopedAIPromptAPILegacyParamsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPILegacyParams;
using ScopedAIPromptAPIMultimodalInputForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPIMultimodalInput;
using ScopedAIPromptAPIParamsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPIParams;
using ScopedAIPromptAPIStructuredOutputForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPIStructuredOutput;
using ScopedAIPromptAPIToolUseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIPromptAPIToolUse;
using ScopedAIProofreadingAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIProofreadingAPI;
using ScopedAIRewriterAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIRewriterAPI;
using ScopedAIRewriterAPIForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIRewriterAPIForWorkers;
using ScopedAISummarizationAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAISummarizationAPI;
using ScopedAISummarizationAPIForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAISummarizationAPIForWorkers;
using ScopedAISummarizationPerformancePreferenceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAISummarizationPerformancePreference;
using ScopedAIWriterAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIWriterAPI;
using ScopedAIWriterAPIForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAIWriterAPIForWorkers;
using ScopedAlignZoomToCenterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAlignZoomToCenter;
using ScopedAllImagesPaintedSentToElementTimingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllImagesPaintedSentToElementTiming;
using ScopedAllowContentInitiatedDataUrlNavigationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowContentInitiatedDataUrlNavigations;
using ScopedAllowPreloadingWithCSPMetaTagForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowPreloadingWithCSPMetaTag;
using ScopedAllowSameSiteNoneCookiesInSandboxForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowSameSiteNoneCookiesInSandbox;
using ScopedAllowSkippingEditingBoundaryToMergeEndForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowSkippingEditingBoundaryToMergeEnd;
using ScopedAllowSvgUseToReferenceExternalDocumentRootForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowSvgUseToReferenceExternalDocumentRoot;
using ScopedAllowSyntheticTimingForCanvasCaptureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowSyntheticTimingForCanvasCapture;
using ScopedAllowURNsInIframesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAllowURNsInIframes;
using ScopedAncestorOriginsStoredOnDocumentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAncestorOriginsStoredOnDocument;
using ScopedAncestorRevealingNewSpecForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAncestorRevealingNewSpec;
using ScopedAnchorFocusRingFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAnchorFocusRingFix;
using ScopedAnchorPositionAdjustmentWithoutOverflowForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAnchorPositionAdjustmentWithoutOverflow;
using ScopedAndroidDownloadableFontsMatchingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAndroidDownloadableFontsMatching;
using ScopedAnimationProgressAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAnimationProgressAPI;
using ScopedAnimationTriggerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAnimationTrigger;
using ScopedAnimationWorkletForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAnimationWorklet;
using ScopedAnonymousIframeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAnonymousIframe;
using ScopedAOMAriaRelationshipPropertiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAOMAriaRelationshipProperties;
using ScopedAOMAriaRelationshipPropertiesAriaOwnsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAOMAriaRelationshipPropertiesAriaOwns;
using ScopedAppearanceBaseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAppearanceBase;
using ScopedApproximateGeolocationPermissionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedApproximateGeolocationPermission;
using ScopedApproximateGeolocationPermissionAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedApproximateGeolocationPermissionAPI;
using ScopedApproximateGeolocationWebVisibleAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedApproximateGeolocationWebVisibleAPI;
using ScopedAppTitleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAppTitle;
using ScopedAriaActionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAriaActions;
using ScopedAriaNotifyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAriaNotify;
using ScopedAriaNotifyV2ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAriaNotifyV2;
using ScopedAriaRowColIndexTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAriaRowColIndexText;
using ScopedAsyncSetCookieForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAsyncSetCookie;
using ScopedAttributionReportingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAttributionReporting;
using ScopedAudioContextAsyncStateTransitionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAudioContextAsyncStateTransitions;
using ScopedAudioContextPlaybackStatsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAudioContextPlaybackStats;
using ScopedAudioContextPlayoutStatsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAudioContextPlayoutStats;
using ScopedAudioContextSetSinkIdForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAudioContextSetSinkId;
using ScopedAudioOutputDevicesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAudioOutputDevices;
using ScopedAudioVideoTracksForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAudioVideoTracks;
using ScopedAuthenticatorPasswordsOnlyImmediateRequestsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAuthenticatorPasswordsOnlyImmediateRequests;
using ScopedAuthorSpecifiedLayoutScrollSnapBehaviorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAuthorSpecifiedLayoutScrollSnapBehavior;
using ScopedAutoDarkModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAutoDarkMode;
using ScopedAutofillForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAutofill;
using ScopedAutofillEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAutofillEvent;
using ScopedAutomationControlledForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAutomationControlled;
using ScopedAutoPictureInPictureVideoHeuristicsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAutoPictureInPictureVideoHeuristics;
using ScopedAvoidForcedLayoutOnInvisibleDocumentCloseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAvoidForcedLayoutOnInvisibleDocumentClose;
using ScopedAvoidMergingStyledSpanWithSiblingsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAvoidMergingStyledSpanWithSiblings;
using ScopedAvoidNormalizingVisiblePositionsWhenStartEqualsEndForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedAvoidNormalizingVisiblePositionsWhenStartEqualsEnd;
using ScopedBackfaceVisibilityInteropForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackfaceVisibilityInterop;
using ScopedBackForwardCacheForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackForwardCache;
using ScopedBackForwardCacheExperimentHTTPHeaderForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackForwardCacheExperimentHTTPHeader;
using ScopedBackForwardCacheNotRestoredReasonsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackForwardCacheNotRestoredReasons;
using ScopedBackForwardCacheRestorationPerformanceEntryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackForwardCacheRestorationPerformanceEntry;
using ScopedBackForwardCacheUpdateNotRestoredReasonsNameForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackForwardCacheUpdateNotRestoredReasonsName;
using ScopedBackgroundClipTextDecorationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackgroundClipTextDecoration;
using ScopedBackgroundFetchForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackgroundFetch;
using ScopedBackgroundPageFreezeOptOutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBackgroundPageFreezeOptOut;
using ScopedBarcodeDetectorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBarcodeDetector;
using ScopedBaseAppearanceInlineSizingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBaseAppearanceInlineSizing;
using ScopedBidiCaretAffinityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBidiCaretAffinity;
using ScopedBlinkExtensionChromeOSForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkExtensionChromeOS;
using ScopedBlinkExtensionChromeOSIsolatedWebAppSetShapeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkExtensionChromeOSIsolatedWebAppSetShape;
using ScopedBlinkExtensionChromeOSKioskForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkExtensionChromeOSKiosk;
using ScopedBlinkExtensionWebViewForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkExtensionWebView;
using ScopedBlinkExtensionWebViewMediaIntegrityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkExtensionWebViewMediaIntegrity;
using ScopedBlinkGeometryMapperViewportFastPathForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkGeometryMapperViewportFastPath;
using ScopedBlinkLifecycleScriptForbiddenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkLifecycleScriptForbidden;
using ScopedBlinkRuntimeCallStatsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlinkRuntimeCallStats;
using ScopedBlobBytesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlobBytes;
using ScopedBlockingFocusWithoutUserActivationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlockingFocusWithoutUserActivation;
using ScopedBlockSelectPopupUnfocusedWindowForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBlockSelectPopupUnfocusedWindow;
using ScopedBoundaryEventDispatchTracksNodeRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBoundaryEventDispatchTracksNodeRemoval;
using ScopedBrowserInitiatedAutomaticPictureInPictureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBrowserInitiatedAutomaticPictureInPicture;
using ScopedBrowserVerifiedUserActivationKeyboardForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBrowserVerifiedUserActivationKeyboard;
using ScopedBrowserVerifiedUserActivationMouseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBrowserVerifiedUserActivationMouse;
using ScopedBufferedBytesConsumerLimitSizeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBufferedBytesConsumerLimitSize;
using ScopedBypassPepcSecurityForTestingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedBypassPepcSecurityForTesting;
using ScopedCacheControlRFC7234ParsingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCacheControlRFC7234Parsing;
using ScopedCacheControlRFC7234ParsingMetricsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCacheControlRFC7234ParsingMetrics;
using ScopedCacheStorageCodeCacheHintForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCacheStorageCodeCacheHint;
using ScopedCacheStyleAdjusterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCacheStyleAdjuster;
using ScopedCallExitNodeWithoutLayoutObjectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCallExitNodeWithoutLayoutObject;
using ScopedCanvas2dCanvasFilterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvas2dCanvasFilter;
using ScopedCanvas2dGPUTransferForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvas2dGPUTransfer;
using ScopedCanvas2dLayersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvas2dLayers;
using ScopedCanvas2dLayersWithOptionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvas2dLayersWithOptions;
using ScopedCanvas2dMeshForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvas2dMesh;
using ScopedCanvasDrawElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasDrawElement;
using ScopedCanvasFloatingPointForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasFloatingPoint;
using ScopedCanvasGlobalHDRHeadroomForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasGlobalHDRHeadroom;
using ScopedCanvasGradientCSSColor4ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasGradientCSSColor4;
using ScopedCanvasHDRForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasHDR;
using ScopedCanvasTextMetricsPreciseBoundsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasTextMetricsPreciseBounds;
using ScopedCanvasToneMappingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasToneMapping;
using ScopedCanvasUsesArcPaintOpForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCanvasUsesArcPaintOp;
using ScopedCapabilityDelegationDisplayCaptureRequestForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCapabilityDelegationDisplayCaptureRequest;
using ScopedCaptureControllerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCaptureController;
using ScopedCapturedMouseEventsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCapturedMouseEvents;
using ScopedCapturedSurfaceControlForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCapturedSurfaceControl;
using ScopedCapturedSurfaceResolutionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCapturedSurfaceResolution;
using ScopedCaptureHandleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCaptureHandle;
using ScopedCaretWithTextAffinityUpstreamForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCaretWithTextAffinityUpstream;
using ScopedCCTNewRFMPushBehaviorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCCTNewRFMPushBehavior;
using ScopedCheckableInputTypeLayoutInlineForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCheckableInputTypeLayoutInline;
using ScopedCheckForCanonicalPositionInIdleSpellCheckForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCheckForCanonicalPositionInIdleSpellCheck;
using ScopedCheckVisibilityExtraPropertiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCheckVisibilityExtraProperties;
using ScopedClampWordBoundaryToContentEditableScopeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClampWordBoundaryToContentEditableScope;
using ScopedClearCurrentTargetAfterDispatchForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClearCurrentTargetAfterDispatch;
using ScopedClearFocusWithinOnSubtreeRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClearFocusWithinOnSubtreeRemoval;
using ScopedClearTargetOnlyIfInShadowTreeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClearTargetOnlyIfInShadowTree;
using ScopedClickFocusDoesntPersistStatusBubbleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClickFocusDoesntPersistStatusBubble;
using ScopedClipboardEventTargetCanBeFocusedElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClipboardEventTargetCanBeFocusedElement;
using ScopedClipboardEventTargetUsesContainerNodeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClipboardEventTargetUsesContainerNode;
using ScopedClipboardItemWithDOMStringSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClipboardItemWithDOMStringSupport;
using ScopedClipElementVisibleBoundsInLocalRootForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClipElementVisibleBoundsInLocalRoot;
using ScopedClipPathNestedRasterOptimizationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedClipPathNestedRasterOptimization;
using ScopedCoalesceSelectionchangeEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCoalesceSelectionchangeEvent;
using ScopedCoepReflectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCoepReflection;
using ScopedCollapseZeroWidthSpaceWhenReuseItemForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCollapseZeroWidthSpaceWhenReuseItem;
using ScopedColorInputAcceptsCSSColorsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedColorInputAcceptsCSSColors;
using ScopedColorSpaceDisplayP3LinearForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedColorSpaceDisplayP3Linear;
using ScopedColorSpacePredefinedLinearSpacesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedColorSpacePredefinedLinearSpaces;
using ScopedColorSpaceRec2100LinearForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedColorSpaceRec2100Linear;
using ScopedCommandEventNotComposedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCommandEventNotComposed;
using ScopedCommaSeparatedContainerQueriesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCommaSeparatedContainerQueries;
using ScopedComposedPathReturnTargetBeingDispatchedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedComposedPathReturnTargetBeingDispatched;
using ScopedCompositeBGColorAnimationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositeBGColorAnimation;
using ScopedCompositeBoxShadowAnimationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositeBoxShadowAnimation;
using ScopedCompositeClipPathAnimationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositeClipPathAnimation;
using ScopedCompositedAnimationsCancelledAsynchronouslyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositedAnimationsCancelledAsynchronously;
using ScopedCompositedSelectionUpdateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositedSelectionUpdate;
using ScopedCompositingDecisionAtAnimationPhaseBoundariesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositingDecisionAtAnimationPhaseBoundaries;
using ScopedCompositionForegroundMarkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositionForegroundMarkers;
using ScopedCompositorEventTriggerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositorEventTrigger;
using ScopedCompositorTimelineTriggerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompositorTimelineTrigger;
using ScopedCompressionDictionaryTransportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCompressionDictionaryTransport;
using ScopedComputedAccessibilityInfoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedComputedAccessibilityInfo;
using ScopedComputeInlineContentsSafeRetargetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedComputeInlineContentsSafeRetarget;
using ScopedComputePressureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedComputePressure;
using ScopedComputePressureOwnContributionEstimateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedComputePressureOwnContributionEstimate;
using ScopedConnectionAllowlistForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedConnectionAllowlist;
using ScopedConsiderSubOrSuperScriptAncestorAlignForCaretSelectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedConsiderSubOrSuperScriptAncestorAlignForCaretSelection;
using ScopedContactsManagerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedContactsManager;
using ScopedContactsManagerExtraPropertiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedContactsManagerExtraProperties;
using ScopedContainerNameOnlyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedContainerNameOnly;
using ScopedContainerTimingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedContainerTiming;
using ScopedContentIndexForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedContentIndex;
using ScopedContextMenuForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedContextMenu;
using ScopedControlledFrameForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedControlledFrame;
using ScopedControlledFrameWebRequestSecurityInfoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedControlledFrameWebRequestSecurityInfo;
using ScopedCookieStoreAPIMaxAgeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCookieStoreAPIMaxAge;
using ScopedCookieStoreAPIWhitespaceStrippingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCookieStoreAPIWhitespaceStripping;
using ScopedCoopRestrictPropertiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCoopRestrictProperties;
using ScopedCorrectTemplateFormParsingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCorrectTemplateFormParsing;
using ScopedCorsRFC1918ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCorsRFC1918;
using ScopedCpuPerformanceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCpuPerformance;
using ScopedCrashReportingStorageAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCrashReportingStorageAPI;
using ScopedCreateInlineContentsExcludeOutOfFlowForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCreateInlineContentsExcludeOutOfFlow;
using ScopedCSPHashesV1ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSPHashesV1;
using ScopedCSPReportHashForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSPReportHash;
using ScopedCSSAccentColorKeywordForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAccentColorKeyword;
using ScopedCSSActiveCaptionMapsToCanvasForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSActiveCaptionMapsToCanvas;
using ScopedCSSAlphaColorFunctionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAlphaColorFunction;
using ScopedCSSAltCounterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAltCounter;
using ScopedCSSAnchorWithTransformsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAnchorWithTransforms;
using ScopedCSSAnimationIterationCompositeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAnimationIterationComposite;
using ScopedCSSArgumentGrammarForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSArgumentGrammar;
using ScopedCSSAtRuleCounterStyleImageSymbolsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAtRuleCounterStyleImageSymbols;
using ScopedCSSAtRuleCounterStyleSpeakAsDescriptorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSAtRuleCounterStyleSpeakAsDescriptor;
using ScopedCSSBackgroundClipBorderAreaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSBackgroundClipBorderArea;
using ScopedCSSBorderShapeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSBorderShape;
using ScopedCSSCalcSimplificationAndSerializationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCalcSimplificationAndSerialization;
using ScopedCSSCaretAnimationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCaretAnimation;
using ScopedCSSCaretShapeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCaretShape;
using ScopedCSSCaseSensitiveSelectorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCaseSensitiveSelector;
using ScopedCSSChUnitSpecCompliantFallbackForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSChUnitSpecCompliantFallback;
using ScopedCSSColorTypedOMForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSColorTypedOM;
using ScopedCSSContainerProgressNotationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSContainerProgressNotation;
using ScopedCSSContainerStyleQueriesRangeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSContainerStyleQueriesRange;
using ScopedCSSContrastColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSContrastColor;
using ScopedCSSCornersShorthandForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCornersShorthand;
using ScopedCSSCounterResetReversedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCounterResetReversed;
using ScopedCSSCrossFadeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCrossFade;
using ScopedCSSCustomMediaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSCustomMedia;
using ScopedCSSDynamicRangeLimitForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSDynamicRangeLimit;
using ScopedCSSEnumeratedCustomPropertiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSEnumeratedCustomProperties;
using ScopedCSSFontFamilySerializationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSFontFamilySerialization;
using ScopedCSSFontSizeAdjustForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSFontSizeAdjust;
using ScopedCSSFunctionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSFunctions;
using ScopedCSSGapDecorationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSGapDecoration;
using ScopedCSSGridGapSuppressionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSGridGapSuppression;
using ScopedCSSGridLanesLayoutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSGridLanesLayout;
using ScopedCSSHangingPunctuationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSHangingPunctuation;
using ScopedCSSHexAlphaColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSHexAlphaColor;
using ScopedCSSIdentFunctionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSIdentFunction;
using ScopedCSSImageAnimationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSImageAnimation;
using ScopedCSSInheritFunctionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSInheritFunction;
using ScopedCSSKeyframesRuleLengthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSKeyframesRuleLength;
using ScopedCSSLangExtendedRangesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLangExtendedRanges;
using ScopedCSSLayoutAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLayoutAPI;
using ScopedCSSLetterAndWordSpacingPercentageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLetterAndWordSpacingPercentage;
using ScopedCSSLightDarkImageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLightDarkImage;
using ScopedCSSLineClampForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLineClamp;
using ScopedCSSLineClampLineBreakingEllipsisForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLineClampLineBreakingEllipsis;
using ScopedCSSLineClampLinesAndHeightForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLineClampLinesAndHeight;
using ScopedCSSListCounterAccountingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSListCounterAccounting;
using ScopedCSSLogicalCombinationPseudoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSLogicalCombinationPseudo;
using ScopedCSSMarkerNestedPseudoElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSMarkerNestedPseudoElement;
using ScopedCSSMediaProgressNotationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSMediaProgressNotation;
using ScopedCSSMixinsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSMixins;
using ScopedCSSNestedPseudoElementsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSNestedPseudoElements;
using ScopedCSSOMGetComputedStylePseudoElementRequiresColonForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSOMGetComputedStylePseudoElementRequiresColon;
using ScopedCSSOverscrollBehaviorChainForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSOverscrollBehaviorChain;
using ScopedCSSPaintAPIArgumentsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPaintAPIArguments;
using ScopedCSSParserIgnoreCharsetForURLsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSParserIgnoreCharsetForURLs;
using ScopedCSSPolygonRoundingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPolygonRounding;
using ScopedCSSPositionStickyStaticScrollPositionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPositionStickyStaticScrollPosition;
using ScopedCSSProgressNotationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSProgressNotation;
using ScopedCSSPseudoColumnForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoColumn;
using ScopedCSSPseudoElementBackdropForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoElementBackdrop;
using ScopedCSSPseudoElementInterfaceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoElementInterface;
using ScopedCSSPseudoElementViewTransitionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoElementViewTransitions;
using ScopedCSSPseudoHasSlottedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoHasSlotted;
using ScopedCSSPseudoPlayingPausedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoPlayingPaused;
using ScopedCSSPseudoScrollButtonsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoScrollButtons;
using ScopedCSSPseudoScrollMarkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSPseudoScrollMarkers;
using ScopedCSSRandomFunctionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSRandomFunction;
using ScopedCSSRandomFunctionTypedOMForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSRandomFunctionTypedOM;
using ScopedCSSResizeAutoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSResizeAuto;
using ScopedCSSResourceIntegrityEnforcementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSResourceIntegrityEnforcement;
using ScopedCSSRevertRuleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSRevertRule;
using ScopedCSSRubyOverhangForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSRubyOverhang;
using ScopedCSSSafePrintableInsetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSSafePrintableInset;
using ScopedCSSScopeifiedParentPseudoClassForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScopeifiedParentPseudoClass;
using ScopedCSSScopeImportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScopeImport;
using ScopedCSSScrolledContainerQueriesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrolledContainerQueries;
using ScopedCSSScrollInitialTargetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollInitialTarget;
using ScopedCSSScrollMarkerGroupModesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollMarkerGroupModes;
using ScopedCSSScrollMarkerTargetBeforeAfterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollMarkerTargetBeforeAfter;
using ScopedCSSScrollSnapChangeEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollSnapChangeEvent;
using ScopedCSSScrollSnapChangingEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollSnapChangingEvent;
using ScopedCSSScrollSnapEventConstructorExposedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollSnapEventConstructorExposed;
using ScopedCSSScrollSnapEventsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollSnapEvents;
using ScopedCSSScrollTargetGroupForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollTargetGroup;
using ScopedCSSScrollTargetGroupAriaCurrentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSScrollTargetGroupAriaCurrent;
using ScopedCSSShapeEllipseCirclePositionSerializationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSShapeEllipseCirclePositionSerialization;
using ScopedCSSShapeOutsidePathAndShapeSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSShapeOutsidePathAndShapeSupport;
using ScopedCSSShapeOutsideRectAndXywhSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSShapeOutsideRectAndXywhSupport;
using ScopedCSSStyleSheetInitBaseURLForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSStyleSheetInitBaseURL;
using ScopedCSSSupportsAtRuleFunctionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSSupportsAtRuleFunction;
using ScopedCSSSupportsForImportRulesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSSupportsForImportRules;
using ScopedCSSSupportsNamedFeatureFunctionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSSupportsNamedFeatureFunction;
using ScopedCSSSystemAccentColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSSystemAccentColor;
using ScopedCSSTextAlignMatchParentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextAlignMatchParent;
using ScopedCSSTextDecorationSkipInkAllForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextDecorationSkipInkAll;
using ScopedCSSTextDecorationSkipSpacesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextDecorationSkipSpaces;
using ScopedCssTextFitForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCssTextFit;
using ScopedCssTextFitReshapingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCssTextFitReshaping;
using ScopedCssTextIndentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCssTextIndent;
using ScopedCssTextIndentAsPrimitiveForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCssTextIndentAsPrimitive;
using ScopedCSSTextSpacingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextSpacing;
using ScopedCSSTextTransformFullSizeKanaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextTransformFullSizeKana;
using ScopedCSSTextTransformFullWidthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextTransformFullWidth;
using ScopedCSSTextTransformMultiKeywordForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTextTransformMultiKeyword;
using ScopedCSSTimelineScopeAllForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTimelineScopeAll;
using ScopedCSSTimelineScopeGlobalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTimelineScopeGlobal;
using ScopedCSSTypedArithmeticForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSTypedArithmetic;
using ScopedCSSURLRequestModifiersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSURLRequestModifiers;
using ScopedCSSUserSelectContainForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSUserSelectContain;
using ScopedCSSUserValidAndUserInvalidForRadioForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSUserValidAndUserInvalidForRadio;
using ScopedCSSVideoDynamicRangeMediaQueriesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSVideoDynamicRangeMediaQueries;
using ScopedCSSViewTransitionAutoNameForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCSSViewTransitionAutoName;
using ScopedCustomElementsDisableFormattingFixupsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCustomElementsDisableFormattingFixups;
using ScopedCustomizableComboboxForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCustomizableCombobox;
using ScopedCustomizableSelectMultiplePopupForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCustomizableSelectMultiplePopup;
using ScopedCustomScrollbarApplyMinimumThumbLengthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedCustomScrollbarApplyMinimumThumbLength;
using ScopedDatabaseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDatabase;
using ScopedDateTimeLocalArabicCommaWorkaroundForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDateTimeLocalArabicCommaWorkaround;
using ScopedDeclarativeCSSModulesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDeclarativeCSSModules;
using ScopedDeclarativeCSSModulesStyleTagForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDeclarativeCSSModulesStyleTag;
using ScopedDecoupleComputedBorderWidthFromStyleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDecoupleComputedBorderWidthFromStyle;
using ScopedDecoupleResolvedColumnRuleWidthFromStyleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDecoupleResolvedColumnRuleWidthFromStyle;
using ScopedDelegatesFocusTextControlInputFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDelegatesFocusTextControlInputFix;
using ScopedDeleteTextInContentEditableBeforeRemovingChildrenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDeleteTextInContentEditableBeforeRemovingChildren;
using ScopedDeprecateUnloadOptOutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDeprecateUnloadOptOut;
using ScopedDesktopCaptureDisableLocalEchoControlForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDesktopCaptureDisableLocalEchoControl;
using ScopedDesktopPWAsAdditionalWindowingControlsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDesktopPWAsAdditionalWindowingControls;
using ScopedDesktopPWAsAdditionalWindowingControlsOnMoveForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDesktopPWAsAdditionalWindowingControlsOnMove;
using ScopedDeviceAttributesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDeviceAttributes;
using ScopedDeviceOrientationRequestPermissionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDeviceOrientationRequestPermission;
using ScopedDevicePostureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDevicePosture;
using ScopedDialogCloseWhenOpenRemovedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDialogCloseWhenOpenRemoved;
using ScopedDialogNewFocusBehaviorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDialogNewFocusBehavior;
using ScopedDigitalGoodsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDigitalGoods;
using ScopedDigitalGoodsV2_1ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDigitalGoodsV2_1;
using ScopedDirectSocketsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDirectSockets;
using ScopedDirectSocketsInServiceWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDirectSocketsInServiceWorkers;
using ScopedDirectSocketsInSharedWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDirectSocketsInSharedWorkers;
using ScopedDisableAnchorCenterOnAlignJustifyItemsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisableAnchorCenterOnAlignJustifyItems;
using ScopedDisableDifferentOriginSubframeDialogSuppressionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisableDifferentOriginSubframeDialogSuppression;
using ScopedDisableEllipsisWhenScrolledForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisableEllipsisWhenScrolled;
using ScopedDisableReduceAcceptLanguageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisableReduceAcceptLanguage;
using ScopedDisableRemoveFormatForPlainTextOnlyEditableDivForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisableRemoveFormatForPlainTextOnlyEditableDiv;
using ScopedDisallowDisconnectedAreaNavigationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisallowDisconnectedAreaNavigation;
using ScopedDisallowPickerForReadonlyInputsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisallowPickerForReadonlyInputs;
using ScopedDisconnectWebSocketOnBFCacheForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisconnectWebSocketOnBFCache;
using ScopedDispatchHiddenVisibilityTransitionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDispatchHiddenVisibilityTransitions;
using ScopedDispatchSelectionchangeEventPerElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDispatchSelectionchangeEventPerElement;
using ScopedDisplayContentsFocusableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisplayContentsFocusable;
using ScopedDisplayCutoutAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDisplayCutoutAPI;
using ScopedDocumentActiveViewTransitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentActiveViewTransition;
using ScopedDocumentCookieForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentCookie;
using ScopedDocumentDomainForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentDomain;
using ScopedDocumentIsolationPolicyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentIsolationPolicy;
using ScopedDocumentOpenIframeUnloadEventsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentOpenIframeUnloadEvents;
using ScopedDocumentOpenOriginAliasRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentOpenOriginAliasRemoval;
using ScopedDocumentOpenSandboxInheritanceRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentOpenSandboxInheritanceRemoval;
using ScopedDocumentPatchingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPatching;
using ScopedDocumentPictureInPictureAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPictureInPictureAPI;
using ScopedDocumentPictureInPicturePreferInitialPlacementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPictureInPicturePreferInitialPlacement;
using ScopedDocumentPictureInPictureUserActivationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPictureInPictureUserActivation;
using ScopedDocumentPolicyDocumentDomainForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicyDocumentDomain;
using ScopedDocumentPolicyExpectNoLinkedResourcesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicyExpectNoLinkedResources;
using ScopedDocumentPolicyIncludeJSCallStacksInCrashReportsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicyIncludeJSCallStacksInCrashReports;
using ScopedDocumentPolicyInDedicatedWorkerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicyInDedicatedWorker;
using ScopedDocumentPolicyNegotiationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicyNegotiation;
using ScopedDocumentPolicyNetworkEfficiencyGuardrailsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicyNetworkEfficiencyGuardrails;
using ScopedDocumentPolicySyncXHRForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentPolicySyncXHR;
using ScopedDocumentWriteForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDocumentWrite;
using ScopedDOMActivateBubblesInheritanceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDOMActivateBubblesInheritance;
using ScopedDontLeakShadowTreesInDragEventsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedDontLeakShadowTreesInDragEvents;
using ScopedEditContextAssignmentAsPerSpecForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEditContextAssignmentAsPerSpec;
using ScopedEditContextHandleTextOrSelectionUpdateDuringCompositionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEditContextHandleTextOrSelectionUpdateDuringComposition;
using ScopedEditEmojiTagSequenceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEditEmojiTagSequence;
using ScopedEditingLineMovementWithRubyFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEditingLineMovementWithRubyFix;
using ScopedElementCaptureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedElementCapture;
using ScopedElementInnerTextHandleFirstLineStyleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedElementInnerTextHandleFirstLineStyle;
using ScopedElementInternalsBehaviorsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedElementInternalsBehaviors;
using ScopedElementSpecificReadOnlyConstraintValidationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedElementSpecificReadOnlyConstraintValidation;
using ScopedEmailVerificationProtocolForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEmailVerificationProtocol;
using ScopedEmojiMonochromeRenderingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEmojiMonochromeRendering;
using ScopedEndpointInclusiveCommitStylesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEndpointInclusiveCommitStyles;
using ScopedEnforceAnonymityExposureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEnforceAnonymityExposure;
using ScopedEnterInOpenShadowRootsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEnterInOpenShadowRoots;
using ScopedEntropyIgnoredForFirstVideoFrameLCPForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEntropyIgnoredForFirstVideoFrameLCP;
using ScopedEventPseudoTargetPropertyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEventPseudoTargetProperty;
using ScopedEventTimingInteractionCountForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEventTimingInteractionCount;
using ScopedEventTimingTargetSelectorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEventTimingTargetSelector;
using ScopedEventTriggerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEventTrigger;
using ScopedExperimentalContentSecurityPolicyFeaturesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExperimentalContentSecurityPolicyFeatures;
using ScopedExperimentalJSProfilerMarkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExperimentalJSProfilerMarkers;
using ScopedExperimentalMachineLearningNeuralNetworkForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExperimentalMachineLearningNeuralNetwork;
using ScopedExperimentalPoliciesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExperimentalPolicies;
using ScopedExposeCSSFontFeatureValuesRuleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExposeCSSFontFeatureValuesRule;
using ScopedExposeRenderTimeNonTaoDelayedImageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExposeRenderTimeNonTaoDelayedImage;
using ScopedExtendedShapeCacheForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExtendedShapeCache;
using ScopedExtendedTextMetricsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExtendedTextMetrics;
using ScopedExternalPopupMenuClickEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedExternalPopupMenuClickEvent;
using ScopedEyeDropperAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedEyeDropperAPI;
using ScopedFaceDetectorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFaceDetector;
using ScopedFastPositionIteratorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFastPositionIterator;
using ScopedFedCmForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCm;
using ScopedFedCmAutofillForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmAutofill;
using ScopedFedCmDelegationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmDelegation;
using ScopedFedCmErrorAttributeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmErrorAttribute;
using ScopedFedCmIdPRegistrationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmIdPRegistration;
using ScopedFedCmLightweightModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmLightweightMode;
using ScopedFedCmMultipleIdentityProvidersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmMultipleIdentityProviders;
using ScopedFedCmNavigationInterceptionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmNavigationInterception;
using ScopedFedCmNonStringTokenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFedCmNonStringToken;
using ScopedFencedFramesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFencedFrames;
using ScopedFencedFramesAPIChangesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFencedFramesAPIChanges;
using ScopedFencedFramesDefaultModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFencedFramesDefaultMode;
using ScopedFencedFramesLocalUnpartitionedDataAccessForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFencedFramesLocalUnpartitionedDataAccess;
using ScopedFetchBodyBytesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFetchBodyBytes;
using ScopedFetchLaterAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFetchLaterAPI;
using ScopedFetchRetryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFetchRetry;
using ScopedFetchUploadStreamingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFetchUploadStreaming;
using ScopedFileHandlingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileHandling;
using ScopedFileHandlingIconsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileHandlingIcons;
using ScopedFileSystemForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystem;
using ScopedFileSystemAccessForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccess;
using ScopedFileSystemAccessAPIExperimentalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessAPIExperimental;
using ScopedFileSystemAccessGetCloudIdentifiersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessGetCloudIdentifiers;
using ScopedFileSystemAccessLocalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessLocal;
using ScopedFileSystemAccessLockingSchemeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessLockingScheme;
using ScopedFileSystemAccessOriginPrivateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessOriginPrivate;
using ScopedFileSystemAccessRevokeReadOnRemoveForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessRevokeReadOnRemove;
using ScopedFileSystemAccessWriteModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemAccessWriteMode;
using ScopedFileSystemObserverForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemObserver;
using ScopedFileSystemObserverUnobserveForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFileSystemObserverUnobserve;
using ScopedFilterableSelectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFilterableSelect;
using ScopedFilterContainerLevelStylesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFilterContainerLevelStyles;
using ScopedFilteringPrimitivesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFilteringPrimitives;
using ScopedFindFirstMisspellingEndWhenNonEditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFindFirstMisspellingEndWhenNonEditable;
using ScopedFirstLineOnListItemForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFirstLineOnListItem;
using ScopedFirstLineTextMetricsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFirstLineTextMetrics;
using ScopedFixHTMLFormControlElementIsReadOnlyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixHTMLFormControlElementIsReadOnly;
using ScopedFixJustifyQueryCommandValueForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixJustifyQueryCommandValue;
using ScopedFixLinebreakForPreTagForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixLinebreakForPreTag;
using ScopedFixMapElementEmptyNameBugForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixMapElementEmptyNameBug;
using ScopedFixMarkerSuppressionForAppearanceAutoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixMarkerSuppressionForAppearanceAuto;
using ScopedFixNextPositionCalculationInInsertListForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixNextPositionCalculationInInsertList;
using ScopedFixStrikethroughToggleInEmptyContentEditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixStrikethroughToggleInEmptyContentEditable;
using ScopedFixVisualRectRemoteViewportTransformForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFixVisualRectRemoteViewportTransform;
using ScopedFledgeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledge;
using ScopedFledgeAuctionDealSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeAuctionDealSupport;
using ScopedFledgeBiddingAndAuctionServerAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeBiddingAndAuctionServerAPI;
using ScopedFledgeBiddingAndAuctionServerAPIMultiSellerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeBiddingAndAuctionServerAPIMultiSeller;
using ScopedFledgeClickinessForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeClickiness;
using ScopedFledgeCustomMaxAuctionAdComponentsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeCustomMaxAuctionAdComponents;
using ScopedFledgeDeprecatedRenderURLReplacementsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeDeprecatedRenderURLReplacements;
using ScopedFledgeDirectFromSellerSignalsHeaderAdSlotForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeDirectFromSellerSignalsHeaderAdSlot;
using ScopedFledgeDirectFromSellerSignalsWebBundlesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeDirectFromSellerSignalsWebBundles;
using ScopedFledgeMultiBidForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeMultiBid;
using ScopedFledgePrivateModelTrainingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgePrivateModelTraining;
using ScopedFledgeRealTimeReportingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeRealTimeReporting;
using ScopedFledgeSellerNonceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeSellerNonce;
using ScopedFledgeSellerScriptExecutionModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeSellerScriptExecutionMode;
using ScopedFledgeTrustedSignalsKVv1CreativeScanningForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeTrustedSignalsKVv1CreativeScanning;
using ScopedFledgeTrustedSignalsKVv2ContextualDataForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeTrustedSignalsKVv2ContextualData;
using ScopedFledgeTrustedSignalsKVv2SupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFledgeTrustedSignalsKVv2Support;
using ScopedFlexWrapBalanceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFlexWrapBalance;
using ScopedFocusgroupForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFocusgroup;
using ScopedFocusgroupGridForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFocusgroupGrid;
using ScopedFontAccessForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontAccess;
using ScopedFontDataServiceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontDataService;
using ScopedFontFallbackForTabSizeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontFallbackForTabSize;
using ScopedFontFamilyPostscriptMatchingCTMigrationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontFamilyPostscriptMatchingCTMigration;
using ScopedFontFamilyStyleMatchingCTMigrationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontFamilyStyleMatchingCTMigration;
using ScopedFontFeatureSettingsDescriptorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontFeatureSettingsDescriptor;
using ScopedFontFormatAvar2ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontFormatAvar2;
using ScopedFontLanguageOverrideForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontLanguageOverride;
using ScopedFontMatchAliasesAsLastResortForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontMatchAliasesAsLastResort;
using ScopedFontStyleObliqueZeroDegreeAsNormalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontStyleObliqueZeroDegreeAsNormal;
using ScopedFontVariationSettingsDescriptorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFontVariationSettingsDescriptor;
using ScopedForcedColorsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedForcedColors;
using ScopedForceEagerMeasureMemoryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedForceEagerMeasureMemory;
using ScopedForceReduceMotionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedForceReduceMotion;
using ScopedFractionalScrollOffsetsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFractionalScrollOffsets;
using ScopedFragmentedOofInCbForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFragmentedOofInCb;
using ScopedFreezeFramesOnVisibilityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedFreezeFramesOnVisibility;
using ScopedGamepadMultitouchForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGamepadMultitouch;
using ScopedGamepadRawInputChangeEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGamepadRawInputChangeEvent;
using ScopedGamepadWindowEventHandlersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGamepadWindowEventHandlers;
using ScopedGeolocationElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGeolocationElement;
using ScopedGeometryMapperSingularTransformFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGeometryMapperSingularTransformFix;
using ScopedGeometryUtilsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGeometryUtils;
using ScopedGeometryUtilsForCSSPseudoElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGeometryUtilsForCSSPseudoElement;
using ScopedGetAllScreensMediaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetAllScreensMedia;
using ScopedGetComputedStyleOutsideFlatTreeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetComputedStyleOutsideFlatTree;
using ScopedGetDisplayMediaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetDisplayMedia;
using ScopedGetDisplayMediaRequiresUserActivationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetDisplayMediaRequiresUserActivation;
using ScopedGetDisplayMediaWindowAudioCaptureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetDisplayMediaWindowAudioCapture;
using ScopedGetElementsByNameOnlyHTMLElementsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetElementsByNameOnlyHTMLElements;
using ScopedGetUserMediaEchoCancellationModesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGetUserMediaEchoCancellationModes;
using ScopedGroupEffectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedGroupEffect;
using ScopedHandleDeletionAtStartAndEndBoundaryContainingHiddenElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHandleDeletionAtStartAndEndBoundaryContainingHiddenElement;
using ScopedHandleDisconnectedSelectionDuringDOMChangesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHandleDisconnectedSelectionDuringDOMChanges;
using ScopedHandleInvalidMaskImageWithBackdropFilterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHandleInvalidMaskImageWithBackdropFilter;
using ScopedHandleShadowDOMInSubstringUtilForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHandleShadowDOMInSubstringUtil;
using ScopedHandwritingRecognitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHandwritingRecognition;
using ScopedHasUAVisualTransitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHasUAVisualTransition;
using ScopedHeadingOffsetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHeadingOffset;
using ScopedHideVideoControlsWhenUnneededForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHideVideoControlsWhenUnneeded;
using ScopedHighlightsFromPointForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHighlightsFromPoint;
using ScopedHitTestBorderRadiusForStackingContextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHitTestBorderRadiusForStackingContext;
using ScopedHitTestContainerTransformStateForPreserve3dForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHitTestContainerTransformStateForPreserve3d;
using ScopedHrefTranslateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHrefTranslate;
using ScopedHstsTopLevelNavigationsOnlyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHstsTopLevelNavigationsOnly;
using ScopedHTMLAdoptionAlgorithmNewStepsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLAdoptionAlgorithmNewSteps;
using ScopedHTMLCommandActionsV2ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLCommandActionsV2;
using ScopedHTMLCommandElementRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLCommandElementRemoval;
using ScopedHTMLCommandForScrollCommandsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLCommandForScrollCommands;
using ScopedHTMLElementScrollParentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLElementScrollParent;
using ScopedHTMLImageElementActualNaturalSizeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLImageElementActualNaturalSize;
using ScopedHTMLInputElementDropWebkitClearButtonForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLInputElementDropWebkitClearButton;
using ScopedHTMLInterestForInterestButtonPseudoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLInterestForInterestButtonPseudo;
using ScopedHTMLLinkElementAttributeValueChangesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLLinkElementAttributeValueChanges;
using ScopedHTMLParserYieldAndDelayOftenForTestingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLParserYieldAndDelayOftenForTesting;
using ScopedHTMLParserYieldByUserTimingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLParserYieldByUserTiming;
using ScopedHTMLPrintingArtifactAnnotationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLPrintingArtifactAnnotations;
using ScopedHTMLProcessingInstructionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedHTMLProcessingInstruction;
using ScopedICUCapitalizationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedICUCapitalization;
using ScopedIgnoreLetterSpacingInCursiveScriptsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedIgnoreLetterSpacingInCursiveScripts;
using ScopedImageDataPixelFormatForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedImageDataPixelFormat;
using ScopedImageDocumentUseLayoutWidthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedImageDocumentUseLayoutWidth;
using ScopedImageSrcsetReselectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedImageSrcsetReselection;
using ScopedImplicitRootScrollerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedImplicitRootScroller;
using ScopedImprovedSourceRetargetingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedImprovedSourceRetargeting;
using ScopedIncomingCallNotificationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedIncomingCallNotifications;
using ScopedInertElementNonEditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInertElementNonEditable;
using ScopedInfiniteCullRectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInfiniteCullRect;
using ScopedInheritUserModifyWithoutContenteditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInheritUserModifyWithoutContenteditable;
using ScopedInlineBlockLineNavigationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInlineBlockLineNavigation;
using ScopedInlineScriptCacheHintForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInlineScriptCacheHint;
using ScopedInnerHTMLParserFastpathLogFailureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInnerHTMLParserFastpathLogFailure;
using ScopedInputEventDataTransferForInsertCmdForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInputEventDataTransferForInsertCmd;
using ScopedInputEventsDeleteNonCollapsedSelectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInputEventsDeleteNonCollapsedSelection;
using ScopedInputInSelectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInputInSelect;
using ScopedInputMultipleFieldsUIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInputMultipleFieldsUI;
using ScopedInsertBlockquoteBeforeOuterBlockForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInsertBlockquoteBeforeOuterBlock;
using ScopedInstalledAppForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInstalledApp;
using ScopedInstallElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInstallElement;
using ScopedInstallOnDeviceSpeechRecognitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInstallOnDeviceSpeechRecognition;
using ScopedIntegrityPolicyScriptForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedIntegrityPolicyScript;
using ScopedInterestEventsNonComposedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInterestEventsNonComposed;
using ScopedInterestGroupsInSharedStorageWorkletForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInterestGroupsInSharedStorageWorklet;
using ScopedIntersectionObserverCompositedAnimationsForceMainFramesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedIntersectionObserverCompositedAnimationsForceMainFrames;
using ScopedInvertedColorsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInvertedColors;
using ScopedInvisibleSVGAnimationThrottlingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedInvisibleSVGAnimationThrottling;
using ScopedJavaScriptCompileHintsPerFunctionMagicRuntimeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedJavaScriptCompileHintsPerFunctionMagicRuntime;
using ScopedJavaScriptSourcePhaseImportsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedJavaScriptSourcePhaseImports;
using ScopedKeyboardAccessibleTooltipForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedKeyboardAccessibleTooltip;
using ScopedKeySystemTrackConfigurationEncryptionSchemeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedKeySystemTrackConfigurationEncryptionScheme;
using ScopedLabelInteractiveContentCheckBeforeHandlerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLabelInteractiveContentCheckBeforeHandler;
using ScopedLangAttributeAwareFormControlUIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLangAttributeAwareFormControlUI;
using ScopedLanguageDetectionAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLanguageDetectionAPI;
using ScopedLanguageDetectionAPIForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLanguageDetectionAPIForWorkers;
using ScopedLayoutBoxRectGettersUseFragmentsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLayoutBoxRectGettersUseFragments;
using ScopedLayoutIgnoreMarginsForStickyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLayoutIgnoreMarginsForSticky;
using ScopedLayoutImageEmptyNaturalSizeBeforeSizeAvailableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLayoutImageEmptyNaturalSizeBeforeSizeAvailable;
using ScopedLayoutTableCellAlignmentSafeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLayoutTableCellAlignmentSafe;
using ScopedLazyImageConformantLoadEventTimingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLazyImageConformantLoadEventTiming;
using ScopedLazyLoadVideoAndAudioForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLazyLoadVideoAndAudio;
using ScopedLeftClickToHandleSuggestionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLeftClickToHandleSuggestion;
using ScopedLightDismissFromClickForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLightDismissFromClick;
using ScopedLinkBlurImprovementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLinkBlurImprovement;
using ScopedListOwnerMustHaveCSSBoxForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedListOwnerMustHaveCSSBox;
using ScopedLocalNetworkAccessNonSecureContextAllowedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLocalNetworkAccessNonSecureContextAllowed;
using ScopedLocalNetworkAccessPermissionPolicyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLocalNetworkAccessPermissionPolicy;
using ScopedLocalNetworkAccessSplitPermissionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLocalNetworkAccessSplitPermissions;
using ScopedLocalNetworkAccessWebRTCForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLocalNetworkAccessWebRTC;
using ScopedLockedModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLockedMode;
using ScopedLogicalStartOfLineBlockFallbackForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLogicalStartOfLineBlockFallback;
using ScopedLoginElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLoginElement;
using ScopedLongAnimationFrameSourceCharPositionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLongAnimationFrameSourceCharPosition;
using ScopedLongAnimationFrameSourceLineColumnForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLongAnimationFrameSourceLineColumn;
using ScopedLongAnimationFrameSourceLineColumnInterfaceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLongAnimationFrameSourceLineColumnInterface;
using ScopedLongAnimationFrameStyleDurationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLongAnimationFrameStyleDuration;
using ScopedLongPressLinkSelectTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLongPressLinkSelectText;
using ScopedLongTaskFromLongAnimationFrameForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedLongTaskFromLongAnimationFrame;
using ScopedMacCharacterFallbackCacheForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMacCharacterFallbackCache;
using ScopedMacDisableCtrlHomeEndForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMacDisableCtrlHomeEnd;
using ScopedMachineLearningNeuralNetworkForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMachineLearningNeuralNetwork;
using ScopedMacSystemClipboardPermissionCheckForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMacSystemClipboardPermissionCheck;
using ScopedManagedConfigurationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedManagedConfiguration;
using ScopedManualTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedManualText;
using ScopedMarginTrimForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMarginTrim;
using ScopedMaskDeserializationTimeForCrossOriginMessagesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMaskDeserializationTimeForCrossOriginMessages;
using ScopedMathMLOperatorRTLMirroringForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMathMLOperatorRTLMirroring;
using ScopedMathMLSerializationOnCopyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMathMLSerializationOnCopy;
using ScopedMathMLSkipMtrTagInAncestorWrappingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMathMLSkipMtrTagInAncestorWrapping;
using ScopedMeasureMemoryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMeasureMemory;
using ScopedMediaCapabilitiesEncodingInfoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCapabilitiesEncodingInfo;
using ScopedMediaCapabilitiesSpatialAudioForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCapabilitiesSpatialAudio;
using ScopedMediaCaptureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCapture;
using ScopedMediaCaptureBackgroundBlurForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCaptureBackgroundBlur;
using ScopedMediaCaptureCameraControlsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCaptureCameraControls;
using ScopedMediaCaptureConfigurationChangeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCaptureConfigurationChange;
using ScopedMediaCaptureVoiceIsolationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaCaptureVoiceIsolation;
using ScopedMediaControlsExpandGestureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaControlsExpandGesture;
using ScopedMediaControlsOverlayPlayButtonForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaControlsOverlayPlayButton;
using ScopedMediaElementVolumeGreaterThanOneForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaElementVolumeGreaterThanOne;
using ScopedMediaEngagementBypassAutoplayPoliciesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaEngagementBypassAutoplayPolicies;
using ScopedMediaLatencyHintForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaLatencyHint;
using ScopedMediaPlaybackWhileNotVisiblePermissionPolicyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaPlaybackWhileNotVisiblePermissionPolicy;
using ScopedMediaQueryNavigationControlsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaQueryNavigationControls;
using ScopedMediaSessionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaSession;
using ScopedMediaSessionChapterInformationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaSessionChapterInformation;
using ScopedMediaSourceExperimentalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaSourceExperimental;
using ScopedMediaSourceExtensionsForWebCodecsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaSourceExtensionsForWebCodecs;
using ScopedMediaStreamTrackTransferForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaStreamTrackTransfer;
using ScopedMediaStreamTrackWebSpeechForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMediaStreamTrackWebSpeech;
using ScopedMemoryConsumerForNGShapeCacheForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMemoryConsumerForNGShapeCache;
using ScopedMenuElementsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMenuElements;
using ScopedMergeFixedLayersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMergeFixedLayers;
using ScopedMergeStickyLayersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMergeStickyLayers;
using ScopedMessagePortCloseEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMessagePortCloseEvent;
using ScopedMiddleClickAutoscrollForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMiddleClickAutoscroll;
using ScopedMixedContentAutoupgradesUseIsMixedContentRestrictedInFrameForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMixedContentAutoupgradesUseIsMixedContentRestrictedInFrame;
using ScopedMobileLayoutThemeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMobileLayoutTheme;
using ScopedModifyParagraphCrossEditingoundaryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedModifyParagraphCrossEditingoundary;
using ScopedModulePreloadReferrerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedModulePreloadReferrer;
using ScopedModulePreloadStyleJsonForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedModulePreloadStyleJson;
using ScopedMojoJSForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMojoJS;
using ScopedMojoJSTestForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMojoJSTest;
using ScopedMoveEndingSelectionToListChildForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMoveEndingSelectionToListChild;
using ScopedMulticolColumnWrappingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedMulticolColumnWrapping;
using ScopedNavigateEventAddHandlerOnPrecommitForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNavigateEventAddHandlerOnPrecommit;
using ScopedNavigateEventClearOnRestoreForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNavigateEventClearOnRestore;
using ScopedNavigateEventDeferCrossDocumentCommitForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNavigateEventDeferCrossDocumentCommit;
using ScopedNavigationEventTimingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNavigationEventTiming;
using ScopedNavigationIdForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNavigationId;
using ScopedNavigatorContentUtilsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNavigatorContentUtils;
using ScopedNetInfoConstantTypeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNetInfoConstantType;
using ScopedNetInfoDownlinkMaxForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNetInfoDownlinkMax;
using ScopedNewHTMLSettingMethodsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNewHTMLSettingMethods;
using ScopedNoExtendSelectionToUserSelectNoneOutOfFlowForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNoExtendSelectionToUserSelectNoneOutOfFlow;
using ScopedNoFontAntialiasingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNoFontAntialiasing;
using ScopedNoIdleEncodingForWebTestsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNoIdleEncodingForWebTests;
using ScopedNonEmptyBlockquotesOnOutdentingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNonEmptyBlockquotesOnOutdenting;
using ScopedNonEmptyVisibleTextSelectionForTextFragmentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNonEmptyVisibleTextSelectionForTextFragment;
using ScopedNonStandardAppearanceValueSliderVerticalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNonStandardAppearanceValueSliderVertical;
using ScopedNormalizeLineEndingsInInsertTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNormalizeLineEndingsInInsertText;
using ScopedNormalizeNbspForPasteAndDropForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNormalizeNbspForPasteAndDrop;
using ScopedNotificationConstructorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNotificationConstructor;
using ScopedNotificationContentImageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNotificationContentImage;
using ScopedNotificationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNotifications;
using ScopedNotificationTriggersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNotificationTriggers;
using ScopedNumberInputFullWidthCharsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedNumberInputFullWidthChars;
using ScopedOffMainThreadCSSPaintForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOffMainThreadCSSPaint;
using ScopedOffscreenCanvasGetContextAttributesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOffscreenCanvasGetContextAttributes;
using ScopedOffsetPathTransformUpdateFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOffsetPathTransformUpdateFix;
using ScopedOmitBlurEventOnElementRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOmitBlurEventOnElementRemoval;
using ScopedOnDeviceWebSpeechAvailableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOnDeviceWebSpeechAvailable;
using ScopedOnDeviceWebSpeechQualityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOnDeviceWebSpeechQuality;
using ScopedOpaqueRangeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOpaqueRange;
using ScopedOpenPopoverInvokerRestrictToSameTreeScopeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOpenPopoverInvokerRestrictToSameTreeScope;
using ScopedOrientationEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOrientationEvent;
using ScopedOriginAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginAPI;
using ScopedOriginIsolationHeaderForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginIsolationHeader;
using ScopedOriginPolicyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginPolicy;
using ScopedOriginTrialsSampleAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPI;
using ScopedOriginTrialsSampleAPIBrowserReadWriteForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIBrowserReadWrite;
using ScopedOriginTrialsSampleAPIDependentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIDependent;
using ScopedOriginTrialsSampleAPIDeprecationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIDeprecation;
using ScopedOriginTrialsSampleAPIExpiryGracePeriodForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIExpiryGracePeriod;
using ScopedOriginTrialsSampleAPIExpiryGracePeriodThirdPartyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIExpiryGracePeriodThirdParty;
using ScopedOriginTrialsSampleAPIImpliedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIImplied;
using ScopedOriginTrialsSampleAPIInvalidOSForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIInvalidOS;
using ScopedOriginTrialsSampleAPINavigationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPINavigation;
using ScopedOriginTrialsSampleAPIPersistentExpiryGracePeriodForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIPersistentExpiryGracePeriod;
using ScopedOriginTrialsSampleAPIPersistentFeatureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIPersistentFeature;
using ScopedOriginTrialsSampleAPIPersistentInvalidOSForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIPersistentInvalidOS;
using ScopedOriginTrialsSampleAPIPersistentThirdPartyDeprecationFeatureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIPersistentThirdPartyDeprecationFeature;
using ScopedOriginTrialsSampleAPIThirdPartyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOriginTrialsSampleAPIThirdParty;
using ScopedOutlineDrawAutoStyleZeroWidthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOutlineDrawAutoStyleZeroWidth;
using ScopedOverlayGlobalRuleRemovalForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOverlayGlobalRuleRemoval;
using ScopedOverlayPropertyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOverlayProperty;
using ScopedOverscrollGesturesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedOverscrollGestures;
using ScopedPagePopupForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPagePopup;
using ScopedPagePopupCopyPasteForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPagePopupCopyPaste;
using ScopedPageRevealEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPageRevealEvent;
using ScopedPageSwapEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPageSwapEvent;
using ScopedPaintHoldingForIframesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaintHoldingForIframes;
using ScopedPaintOffsetTranslationForCompositedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaintOffsetTranslationForComposited;
using ScopedPaintTimingMixinForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaintTimingMixin;
using ScopedPaintUnderInvalidationCheckingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaintUnderInvalidationChecking;
using ScopedParakeetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedParakeet;
using ScopedPartialCompletionNotAllowedInMoveParagraphsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPartialCompletionNotAllowedInMoveParagraphs;
using ScopedPartitionVisitedLinkDatabaseWithSelfLinksForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPartitionVisitedLinkDatabaseWithSelfLinks;
using ScopedPasswordRevealForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPasswordReveal;
using ScopedPaymentAppForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaymentApp;
using ScopedPaymentLinkDetectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaymentLinkDetection;
using ScopedPaymentMethodChangeEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaymentMethodChangeEvent;
using ScopedPaymentRequestForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPaymentRequest;
using ScopedPerformanceManagerInstrumentationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPerformanceManagerInstrumentation;
using ScopedPerformanceMarkCustomUserTimingFromSubframeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPerformanceMarkCustomUserTimingFromSubframe;
using ScopedPerformanceMarkFeatureUsageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPerformanceMarkFeatureUsage;
using ScopedPerformanceNavigationTimingConfidenceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPerformanceNavigationTimingConfidence;
using ScopedPeriodicBackgroundSyncForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPeriodicBackgroundSync;
using ScopedPerMethodCanMakePaymentQuotaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPerMethodCanMakePaymentQuota;
using ScopedPermissionsRequestRevokeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPermissionsRequestRevoke;
using ScopedPlaceholderVisibilityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPlaceholderVisibility;
using ScopedPNaClForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPNaCl;
using ScopedPointerEventDeviceIdForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPointerEventDeviceId;
using ScopedPointerLockOnAndroidForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPointerLockOnAndroid;
using ScopedPointerRawUpdateOnlyInSecureContextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPointerRawUpdateOnlyInSecureContext;
using ScopedPopoverHintNewBehaviorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPopoverHintNewBehavior;
using ScopedPositionOutsideTabSpanCheckSiblingNodeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPositionOutsideTabSpanCheckSiblingNode;
using ScopedPositionVisibilityIgnoreNonClipAncestorsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPositionVisibilityIgnoreNonClipAncestors;
using ScopedPotentialPermissionsPolicyReportingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPotentialPermissionsPolicyReporting;
using ScopedPreciseMemoryInfoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreciseMemoryInfo;
using ScopedPreferDefaultScrollbarStylesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreferDefaultScrollbarStyles;
using ScopedPreferNonCompositedScrollingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreferNonCompositedScrolling;
using ScopedPreferredAudioOutputDevicesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreferredAudioOutputDevices;
using ScopedPrefersReducedDataForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrefersReducedData;
using ScopedPreloadLinkRelDataUrlsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreloadLinkRelDataUrls;
using ScopedPrerender2ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrerender2;
using ScopedPrerender2CrossOriginIframesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrerender2CrossOriginIframes;
using ScopedPrerenderActivationByFormSubmissionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrerenderActivationByFormSubmission;
using ScopedPrerenderUntilScriptForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrerenderUntilScript;
using ScopedPresentationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPresentation;
using ScopedPreserveDropEffectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreserveDropEffect;
using ScopedPreventUndoIfNotEditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPreventUndoIfNotEditable;
using ScopedPrivateAggregationApiErrorReportingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrivateAggregationApiErrorReporting;
using ScopedPrivateAggregationApiMaxContributionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrivateAggregationApiMaxContributions;
using ScopedPrivateNetworkAccessNullIpAddressForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrivateNetworkAccessNullIpAddress;
using ScopedPrivateStateTokensForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrivateStateTokens;
using ScopedPrivateStateTokensAlwaysAllowIssuanceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPrivateStateTokensAlwaysAllowIssuance;
using ScopedProfilerAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProfilerAPI;
using ScopedProfilerAPIForDedicatedWorkerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProfilerAPIForDedicatedWorker;
using ScopedProgrammaticScrollPromiseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProgrammaticScrollPromise;
using ScopedProgressMaxIsPositiveForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProgressMaxIsPositive;
using ScopedPropagateOverscrollBehaviorFromRootForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPropagateOverscrollBehaviorFromRoot;
using ScopedProtectedOriginTrialsSampleAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProtectedOriginTrialsSampleAPI;
using ScopedProtectedOriginTrialsSampleAPIDependentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProtectedOriginTrialsSampleAPIDependent;
using ScopedProtectedOriginTrialsSampleAPIImpliedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedProtectedOriginTrialsSampleAPIImplied;
using ScopedPseudoElementsFocusableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPseudoElementsFocusable;
using ScopedPseudoElementsHitTestableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPseudoElementsHitTestable;
using ScopedPseudoElementsHoverableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPseudoElementsHoverable;
using ScopedPushMessageDataBytesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPushMessageDataBytes;
using ScopedPushMessagingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPushMessaging;
using ScopedPushMessagingSubscriptionChangeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedPushMessagingSubscriptionChange;
using ScopedQuotaExceededErrorUpdateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedQuotaExceededErrorUpdate;
using ScopedQuoteFirstLineStyleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedQuoteFirstLineStyle;
using ScopedRasterInducingScrollForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRasterInducingScroll;
using ScopedReadableStreamBYOBReaderReadMinOptionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReadableStreamBYOBReaderReadMinOption;
using ScopedReadClipboardDataOnClipboardItemGetTypeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReadClipboardDataOnClipboardItemGetType;
using ScopedReadingFlowWithSlotsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReadingFlowWithSlots;
using ScopedRecheckParentDuringNodeVectorInsertionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRecheckParentDuringNodeVectorInsertion;
using ScopedRecordSameDocumentPresentationTimeOnceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRecordSameDocumentPresentationTimeOnce;
using ScopedReduceAcceptLanguageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReduceAcceptLanguage;
using ScopedReduceUserAgentDataLinuxPlatformVersionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReduceUserAgentDataLinuxPlatformVersion;
using ScopedReduceUserAgentMinorVersionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReduceUserAgentMinorVersion;
using ScopedRegionCaptureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRegionCapture;
using ScopedRelatedWebsitePartitionAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRelatedWebsitePartitionAPI;
using ScopedRelOpenerBcgDependencyHintForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRelOpenerBcgDependencyHint;
using ScopedRemotePlaybackForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemotePlayback;
using ScopedRemotePlaybackBackendForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemotePlaybackBackend;
using ScopedRemoveCharsetAutoDetectionForISO2022JPForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveCharsetAutoDetectionForISO2022JP;
using ScopedRemoveChildrenInReplaceChildrenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveChildrenInReplaceChildren;
using ScopedRemoveCollapsedPlaceholderForContentEditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveCollapsedPlaceholderForContentEditable;
using ScopedRemoveDanglingMarkupInTargetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveDanglingMarkupInTarget;
using ScopedRemoveDataUrlInSvgUseForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveDataUrlInSvgUse;
using ScopedRemoveFormatFilterBackgroundColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveFormatFilterBackgroundColor;
using ScopedRemoveNonAllowlistedCreateEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveNonAllowlistedCreateEvent;
using ScopedRemoveScrollNodeWorkaroundForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveScrollNodeWorkaround;
using ScopedRemoveSelectionCanonicalizationInMoveParagraphForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveSelectionCanonicalizationInMoveParagraph;
using ScopedRemoveVisibleSelectionInDOMSelectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRemoveVisibleSelectionInDOMSelection;
using ScopedRenderBlockingFullFrameRateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRenderBlockingFullFrameRate;
using ScopedRenderBlockingStatusForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRenderBlockingStatus;
using ScopedRenderPriorityAttributeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRenderPriorityAttribute;
using ScopedReportFirstFrameTimeAsRenderTimeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReportFirstFrameTimeAsRenderTime;
using ScopedReportLayoutShiftRectsInCssPixelsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedReportLayoutShiftRectsInCssPixels;
using ScopedRequestIsReloadNavigationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRequestIsReloadNavigation;
using ScopedRequestMainFrameAfterFirstVideoFrameForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRequestMainFrameAfterFirstVideoFrame;
using ScopedResolveVarStylesOnCopyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedResolveVarStylesOnCopy;
using ScopedResourceTimingContentEncodingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedResourceTimingContentEncoding;
using ScopedResourceTimingContentTypeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedResourceTimingContentType;
using ScopedResourceTimingInitiatorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedResourceTimingInitiator;
using ScopedResourceTimingUseCORSForBodySizesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedResourceTimingUseCORSForBodySizes;
using ScopedRespectOverscrollBehaviorForScrollBubblingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRespectOverscrollBehaviorForScrollBubbling;
using ScopedResponsiveIframesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedResponsiveIframes;
using ScopedRestrictGamepadAccessForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRestrictGamepadAccess;
using ScopedRestrictOwnAudioForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRestrictOwnAudio;
using ScopedRootScrollbarFollowsBrowserThemeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRootScrollbarFollowsBrowserTheme;
using ScopedRouteMatchingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRouteMatching;
using ScopedRtcAlwaysNegotiateDataChannelsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRtcAlwaysNegotiateDataChannels;
using ScopedRtcAudioJitterBufferMaxPacketsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRtcAudioJitterBufferMaxPackets;
using ScopedRTCDataChannelPriorityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCDataChannelPriority;
using ScopedRTCDiagnosticLoggingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCDiagnosticLogging;
using ScopedRTCEncodedFrameAudioLevelForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCEncodedFrameAudioLevel;
using ScopedRTCEncodedFrameSetMetadataForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCEncodedFrameSetMetadata;
using ScopedRTCEncodedFrameTimestampsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCEncodedFrameTimestamps;
using ScopedRTCEncodedVideoFrameAdditionalMetadataForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCEncodedVideoFrameAdditionalMetadata;
using ScopedRTCJitterBufferTargetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCJitterBufferTarget;
using ScopedRTCLegacyCallbackBasedGetStatsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCLegacyCallbackBasedGetStats;
using ScopedRTCRtpEncodingParametersCodecForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCRtpEncodingParametersCodec;
using ScopedRTCRtpScaleResolutionDownToForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCRtpScaleResolutionDownTo;
using ScopedRTCRtpScriptTransformForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCRtpScriptTransform;
using ScopedRTCRtpTransportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCRtpTransport;
using ScopedRTCStatsRelativePacketArrivalDelayForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCStatsRelativePacketArrivalDelay;
using ScopedRTCSvcScalabilityModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRTCSvcScalabilityMode;
using ScopedRunMicrotaskBeforeXmlScriptForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRunMicrotaskBeforeXmlScript;
using ScopedRunSnapshotPostLayoutStateStepsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedRunSnapshotPostLayoutStateSteps;
using ScopedSanitizerAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSanitizerAPI;
using ScopedScopedCustomElementRegistryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScopedCustomElementRegistry;
using ScopedScopedViewTransitionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScopedViewTransitions;
using ScopedScreenDetailedHdrHeadroomForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScreenDetailedHdrHeadroom;
using ScopedScriptBasedOnUnicodeBlockForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScriptBasedOnUnicodeBlock;
using ScopedScriptedSpeechRecognitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScriptedSpeechRecognition;
using ScopedScriptedSpeechSynthesisForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScriptedSpeechSynthesis;
using ScopedScrollAnchorPriorityCandidateSubtreeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollAnchorPriorityCandidateSubtree;
using ScopedScrollAnchorSerializationUseParentForTextNodeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollAnchorSerializationUseParentForTextNode;
using ScopedScrollbarColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollbarColor;
using ScopedScrollbarGutterBugFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollbarGutterBugFix;
using ScopedScrollbarWidthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollbarWidth;
using ScopedScrollIntoViewNearestForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollIntoViewNearest;
using ScopedScrollIntoViewRootFrameViewportBugFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollIntoViewRootFrameViewportBugFix;
using ScopedScrollTimelineCurrentTimeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollTimelineCurrentTime;
using ScopedScrollTimelineNamedRangeScrollForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollTimelineNamedRangeScroll;
using ScopedScrollTopLeftInteropForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollTopLeftInterop;
using ScopedScrollToTextFragmentUniqueFragmentsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedScrollToTextFragmentUniqueFragments;
using ScopedSearchTextHighlightPseudoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSearchTextHighlightPseudo;
using ScopedSecurePaymentConfirmationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSecurePaymentConfirmation;
using ScopedSecurePaymentConfirmationAvailabilityAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSecurePaymentConfirmationAvailabilityAPI;
using ScopedSecurePaymentConfirmationCapabilitiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSecurePaymentConfirmationCapabilities;
using ScopedSecurePaymentConfirmationDebugForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSecurePaymentConfirmationDebug;
using ScopedSecurePaymentConfirmationOptOutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSecurePaymentConfirmationOptOut;
using ScopedSelectAudioOutputForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectAudioOutput;
using ScopedSelectedcontentelementAttributeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectedcontentelementAttribute;
using ScopedSelectedcontentMultipleForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectedcontentMultiple;
using ScopedSelectedcontentSpecForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectedcontentSpec;
using ScopedSelectionAndFocusedVisiblePositionMatchForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionAndFocusedVisiblePositionMatch;
using ScopedSelectionCollapsedDirectionNoneForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionCollapsedDirectionNone;
using ScopedSelectionFocusAffinityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionFocusAffinity;
using ScopedSelectionHandleWithBottomClippedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionHandleWithBottomClipped;
using ScopedSelectionRemoveRangeNotFoundErrorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionRemoveRangeNotFoundError;
using ScopedSelectionSetBaseAndExtentNonNullNodeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionSetBaseAndExtentNonNullNode;
using ScopedSelectionToStringSkipsUserSelectNoneForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionToStringSkipsUserSelectNone;
using ScopedSelectionUpdateOnlyAfterAutoscrollForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionUpdateOnlyAfterAutoscroll;
using ScopedSelectionUpdateToInitialSelectionInListifyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectionUpdateToInitialSelectionInListify;
using ScopedSelectiveClipboardFormatReadForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectiveClipboardFormatRead;
using ScopedSelectivePermissionsInterventionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectivePermissionsIntervention;
using ScopedSelectRemoveOverflowHiddenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSelectRemoveOverflowHidden;
using ScopedSendBeaconThrowForBlobWithNonSimpleTypeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSendBeaconThrowForBlobWithNonSimpleType;
using ScopedSendSlotChangeSignalAfterNodeInsertedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSendSlotChangeSignalAfterNodeInserted;
using ScopedSensorExtraClassesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSensorExtraClasses;
using ScopedSeparateDeferModuleScriptTasksForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSeparateDeferModuleScriptTasks;
using ScopedSerialForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSerial;
using ScopedSerializeViewTransitionStateInSPAForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSerializeViewTransitionStateInSPA;
using ScopedSerialPortConnectedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSerialPortConnected;
using ScopedServiceWorkerBackgroundSyncInDedicatedWorkerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedServiceWorkerBackgroundSyncInDedicatedWorker;
using ScopedServiceWorkerClientLifecycleStateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedServiceWorkerClientLifecycleState;
using ScopedServiceWorkerInDedicatedWorkerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedServiceWorkerInDedicatedWorker;
using ScopedServiceWorkerStaticRouterTimingInfoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedServiceWorkerStaticRouterTimingInfo;
using ScopedSetDefaultDropEffectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSetDefaultDropEffect;
using ScopedSetHTMLCanRunScriptsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSetHTMLCanRunScripts;
using ScopedSetSequentialFocusStartingPointForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSetSequentialFocusStartingPoint;
using ScopedShadowContourFollowsBorderForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedShadowContourFollowsBorder;
using ScopedShadowRootAdoptedStyleSheetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedShadowRootAdoptedStyleSheet;
using ScopedShadowRootReferenceTargetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedShadowRootReferenceTarget;
using ScopedShadowRootReferenceTargetAriaOwnsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedShadowRootReferenceTargetAriaOwns;
using ScopedSharedArrayBufferForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSharedArrayBuffer;
using ScopedSharedArrayBufferUnrestrictedAccessAllowedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSharedArrayBufferUnrestrictedAccessAllowed;
using ScopedSharedStorageAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSharedStorageAPI;
using ScopedSharedStorageWebLocksForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSharedStorageWebLocks;
using ScopedSharedWorkerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSharedWorker;
using ScopedSharedWorkerExtendedLifetimeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSharedWorkerExtendedLifetime;
using ScopedSideRelativeBackgroundPositionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSideRelativeBackgroundPosition;
using ScopedSignatureBasedInlineIntegrityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSignatureBasedInlineIntegrity;
using ScopedSingleAxisScrollContainersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSingleAxisScrollContainers;
using ScopedSkipAdForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipAd;
using ScopedSkipCallbacksWhenDevToolsNotOpenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipCallbacksWhenDevToolsNotOpen;
using ScopedSkipEventCaptureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipEventCapture;
using ScopedSkipNonEditableInAtomicMoveForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipNonEditableInAtomicMove;
using ScopedSkipOofItemForBreakCandidateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipOofItemForBreakCandidate;
using ScopedSkipParagraphSplitForInlineInsertHTMLForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipParagraphSplitForInlineInsertHTML;
using ScopedSkipPseudoOnlyLinesInLineNavigationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipPseudoOnlyLinesInLineNavigation;
using ScopedSkipTouchEventFilterForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipTouchEventFilter;
using ScopedSkipUnselectableContentInSerializationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipUnselectableContentInSerialization;
using ScopedSkipUnselectableElementsInParagraphBoundaryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSkipUnselectableElementsInParagraphBoundary;
using ScopedSmallerViewportUnitsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSmallerViewportUnits;
using ScopedSmartCardForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSmartCard;
using ScopedSmartZoomForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSmartZoom;
using ScopedSnapshotScrollTimelinesPostLayoutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSnapshotScrollTimelinesPostLayout;
using ScopedSoftNavigationDetectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSoftNavigationDetection;
using ScopedSoftNavigationDetectionIncludeReplaceStateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSoftNavigationDetectionIncludeReplaceState;
using ScopedSoftNavigationHeuristicsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSoftNavigationHeuristics;
using ScopedSortedLayoutShiftSourcesByImpactAreaForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSortedLayoutShiftSourcesByImpactArea;
using ScopedSourceSpecificMulticastInDirectSocketsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSourceSpecificMulticastInDirectSockets;
using ScopedSpatNavUsesCursorInheritanceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSpatNavUsesCursorInheritance;
using ScopedSpeakerSelectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSpeakerSelection;
using ScopedSpeculationMeasurementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSpeculationMeasurement;
using ScopedSpellCheckCustomDictionaryAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSpellCheckCustomDictionaryAPI;
using ScopedSplitTextNotCleanupDummySpansForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSplitTextNotCleanupDummySpans;
using ScopedSplitViewLinkOpenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSplitViewLinkOpen;
using ScopedSrcsetSelectionMatchesImageSetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSrcsetSelectionMatchesImageSet;
using ScopedStableBlinkFeaturesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStableBlinkFeatures;
using ScopedStackingContextIsNotStackedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStackingContextIsNotStacked;
using ScopedStandardizedBrowserZoomForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStandardizedBrowserZoom;
using ScopedStandardizedBrowserZoomOptOutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStandardizedBrowserZoomOptOut;
using ScopedStickyPositionHasOverflowPerAxisForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStickyPositionHasOverflowPerAxis;
using ScopedStickyUserActivationAcrossSameOriginNavigationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStickyUserActivationAcrossSameOriginNavigation;
using ScopedStorageBucketsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStorageBuckets;
using ScopedStorageBucketsDurabilityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStorageBucketsDurability;
using ScopedStorageBucketsLocksForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStorageBucketsLocks;
using ScopedStreamingSanitizerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStreamingSanitizer;
using ScopedStrictMimeTypesForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStrictMimeTypesForWorkers;
using ScopedStylusHandwritingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedStylusHandwriting;
using ScopedSubAppsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSubApps;
using ScopedSuppressPointerStreamAfterDragForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSuppressPointerStreamAfterDrag;
using ScopedSvgAnchorElementAttributesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgAnchorElementAttributes;
using ScopedSvgAnchorElementDownloadAttributeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgAnchorElementDownloadAttribute;
using ScopedSvgAnimateMotionDiscreteCalcModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgAnimateMotionDiscreteCalcMode;
using ScopedSvgAvoidResettingFilterQualityForTiledPatternForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgAvoidResettingFilterQualityForTiledPattern;
using ScopedSVGEmbeddedAsReplacedElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSVGEmbeddedAsReplacedElement;
using ScopedSvgEnableTextDecorationCssStylingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgEnableTextDecorationCssStyling;
using ScopedSvgFallBackToContainerSizeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgFallBackToContainerSize;
using ScopedSvgFeImageSkipHiddenContainerViewportDependenceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgFeImageSkipHiddenContainerViewportDependence;
using ScopedSvgFilterPaintsForHiddenContentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgFilterPaintsForHiddenContent;
using ScopedSvgFilterUserSpaceViewportForSvgForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgFilterUserSpaceViewportForSvg;
using ScopedSvgIgnoreNegativeEllipseRadiiForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgIgnoreNegativeEllipseRadii;
using ScopedSvgInlineRootPixelSnappingScaleAdjustmentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgInlineRootPixelSnappingScaleAdjustment;
using ScopedSvgLengthListClearOnParsingFailureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgLengthListClearOnParsingFailure;
using ScopedSvgLengthResolveUnparsedValueForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgLengthResolveUnparsedValue;
using ScopedSvgNumberListClearOnParsingFailureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgNumberListClearOnParsingFailure;
using ScopedSvgPartitionSVGDocumentResourcesInMemoryCacheForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgPartitionSVGDocumentResourcesInMemoryCache;
using ScopedSvgPathLengthCssPropertyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgPathLengthCssProperty;
using ScopedSvgPointListClearOnParsingFailureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgPointListClearOnParsingFailure;
using ScopedSvgScriptElementAsyncAttributeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgScriptElementAsyncAttribute;
using ScopedSvgSizingWithPreserveAspectRatioNoneForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgSizingWithPreserveAspectRatioNone;
using ScopedSvgSmilClockValueValidationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgSmilClockValueValidation;
using ScopedSvgTextPathPathAttributeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgTextPathPathAttribute;
using ScopedSvgTransformOnNestedSvgElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSvgTransformOnNestedSvgElement;
using ScopedSynthesizedKeyboardEventsForAccessibilityActionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSynthesizedKeyboardEventsForAccessibilityActions;
using ScopedSyntheticMouseHoverOverInactivePageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSyntheticMouseHoverOverInactivePage;
using ScopedSystemDefaultAccentColorsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSystemDefaultAccentColors;
using ScopedSystemFallbackEmojiVSSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSystemFallbackEmojiVSSupport;
using ScopedSystemWakeLockForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedSystemWakeLock;
using ScopedTableBorderColorNoImplicitBorderForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTableBorderColorNoImplicitBorder;
using ScopedTableDefaultBorderColorCurrentColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTableDefaultBorderColorCurrentColor;
using ScopedTableIsAutoFixedLayoutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTableIsAutoFixedLayout;
using ScopedTabSizeAncestorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTabSizeAncestor;
using ScopedTabSizeWithSpacingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTabSizeWithSpacing;
using ScopedTargetInShadowDeterminedBeforeListenerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTargetInShadowDeterminedBeforeListener;
using ScopedTestBlinkFeatureDefaultForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestBlinkFeatureDefault;
using ScopedTestFeatureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeature;
using ScopedTestFeatureDependentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureDependent;
using ScopedTestFeatureForBrowserProcessReadWriteAccessOriginTrialForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureForBrowserProcessReadWriteAccessOriginTrial;
using ScopedTestFeatureImpliedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureImplied;
using ScopedTestFeatureProtectedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureProtected;
using ScopedTestFeatureProtectedDependentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureProtectedDependent;
using ScopedTestFeatureProtectedImpliedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureProtectedImplied;
using ScopedTestFeatureStableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTestFeatureStable;
using ScopedTextAreaScrollTopPreviewForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextAreaScrollTopPreview;
using ScopedTextDetectorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextDetector;
using ScopedTextEmphasisLetterSpacingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextEmphasisLetterSpacing;
using ScopedTextEmphasisPositionAutoForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextEmphasisPositionAuto;
using ScopedTextEmphasisPunctuationExceptionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextEmphasisPunctuationExceptions;
using ScopedTextEmphasisWithRubyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextEmphasisWithRuby;
using ScopedTextFragmentAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextFragmentAPI;
using ScopedTextFragmentIdentifiersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextFragmentIdentifiers;
using ScopedTextFragmentTapOpensContextMenuForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextFragmentTapOpensContextMenu;
using ScopedTextMetricsBaselinesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextMetricsBaselines;
using ScopedTextOverflowClipWithSelectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextOverflowClipWithSelection;
using ScopedTextOverflowStringForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextOverflowString;
using ScopedTextScaleMetaTagForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextScaleMetaTag;
using ScopedTextSpacingTrimFallbackForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextSpacingTrimFallback;
using ScopedTextSpacingTrimFallback2ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextSpacingTrimFallback2;
using ScopedTextSpacingTrimFallbackChwsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextSpacingTrimFallbackChws;
using ScopedTextSpacingTrimYuGothicUIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTextSpacingTrimYuGothicUI;
using ScopedThrottledHistoryAPIThrowsSecurityErrorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedThrottledHistoryAPIThrowsSecurityError;
using ScopedTimelineTriggerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTimelineTrigger;
using ScopedTimerThrottlingForBackgroundTabsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTimerThrottlingForBackgroundTabs;
using ScopedTimestampBasedCLSTrackingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTimestampBasedCLSTracking;
using ScopedTimeZoneChangeEventForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTimeZoneChangeEvent;
using ScopedTopicsAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTopicsAPI;
using ScopedTopicsDocumentAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTopicsDocumentAPI;
using ScopedTopicsImgAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTopicsImgAPI;
using ScopedTouchDragAndContextMenuForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTouchDragAndContextMenu;
using ScopedTouchDragAndDropForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTouchDragAndDrop;
using ScopedTouchDragOnShortPressForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTouchDragOnShortPress;
using ScopedTouchEventFeatureDetectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTouchEventFeatureDetection;
using ScopedTouchTextEditingRedesignForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTouchTextEditingRedesign;
using ScopedTransferableRTCDataChannelForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTransferableRTCDataChannel;
using ScopedTransitionNavigationQuietSkipForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTransitionNavigationQuietSkip;
using ScopedTranslateServiceForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTranslateService;
using ScopedTranslationAPIForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTranslationAPI;
using ScopedTranslationAPIForWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTranslationAPIForWorkers;
using ScopedTraverseFlatTreeToHandleSlotsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTraverseFlatTreeToHandleSlots;
using ScopedTreatMhtmlInitialDocumentLoadsAsCrossDocumentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTreatMhtmlInitialDocumentLoadsAsCrossDocument;
using ScopedTrustedTypesCreateParserOptionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTrustedTypesCreateParserOptions;
using ScopedTrustedTypesFromLiteralForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTrustedTypesFromLiteral;
using ScopedTrustedTypesHTMLForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTrustedTypesHTML;
using ScopedTrustedTypesUseCodeLikeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTrustedTypesUseCodeLike;
using ScopedTwoPhaseViewTransitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedTwoPhaseViewTransition;
using ScopedUnclosedFormControlIsInvalidForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUnclosedFormControlIsInvalid;
using ScopedUnexposedTaskIdsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUnexposedTaskIds;
using ScopedUnprefixedSpeechRecognitionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUnprefixedSpeechRecognition;
using ScopedUnrestrictedMeasureUserAgentSpecificMemoryForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUnrestrictedMeasureUserAgentSpecificMemory;
using ScopedUnrestrictedSharedArrayBufferForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUnrestrictedSharedArrayBuffer;
using ScopedUnrestrictedUsbForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUnrestrictedUsb;
using ScopedUpdateComplexSafaAreaConstraintsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUpdateComplexSafaAreaConstraints;
using ScopedUpdateSelectionOnNodeInsertionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUpdateSelectionOnNodeInsertion;
using ScopedUpdateTrivalTextAfterFragmentCreationFromTextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUpdateTrivalTextAfterFragmentCreationFromText;
using ScopedURLPatternCompareComponentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedURLPatternCompareComponent;
using ScopedURLPatternGenerateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedURLPatternGenerate;
using ScopedURLSearchParamsHasAndDeleteMultipleArgsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedURLSearchParamsHasAndDeleteMultipleArgs;
using ScopedUseBeginFramePresentationFeedbackForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseBeginFramePresentationFeedback;
using ScopedUseBoundedSelectionOffsetsInEditContextDeleteOperationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseBoundedSelectionOffsetsInEditContextDeleteOperations;
using ScopedUseLargestPaintedImageForLCPCandidateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseLargestPaintedImageForLCPCandidate;
using ScopedUseLowQualityInterpolationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseLowQualityInterpolation;
using ScopedUseOriginalDomOffsetsForOffsetMapForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseOriginalDomOffsetsForOffsetMap;
using ScopedUsePositionForPointInFlexibleBoxWithSingleChildElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUsePositionForPointInFlexibleBoxWithSingleChildElement;
using ScopedUsePositionIfIsVisuallyEquivalentCandidateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUsePositionIfIsVisuallyEquivalentCandidate;
using ScopedUserActionPseudosStopAtTopLayerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUserActionPseudosStopAtTopLayer;
using ScopedUserDefinedEntryPointTimingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUserDefinedEntryPointTiming;
using ScopedUserMediaElementForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUserMediaElement;
using ScopedUseSelectionInDOMTreeAnchorInExtendSelectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseSelectionInDOMTreeAnchorInExtendSelection;
using ScopedUseShadowHostStyleCheckEditableForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseShadowHostStyleCheckEditable;
using ScopedUseUndoStepElementDispatchBeforeInputForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedUseUndoStepElementDispatchBeforeInput;
using ScopedV8IdleTasksForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedV8IdleTasks;
using ScopedVideoAutoFullscreenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoAutoFullscreen;
using ScopedVideoFrameMetadataBackgroundBlurForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoFrameMetadataBackgroundBlur;
using ScopedVideoFrameMetadataRtpTimestampForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoFrameMetadataRtpTimestamp;
using ScopedVideoFullscreenOrientationLockForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoFullscreenOrientationLock;
using ScopedVideoRotateToFullscreenForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoRotateToFullscreen;
using ScopedVideoTrackGeneratorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoTrackGenerator;
using ScopedVideoTrackGeneratorInWindowForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoTrackGeneratorInWindow;
using ScopedVideoTrackGeneratorInWorkerForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVideoTrackGeneratorInWorker;
using ScopedViewportHeightClientHintHeaderForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewportHeightClientHintHeader;
using ScopedViewportSegmentsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewportSegments;
using ScopedViewTransitionAsyncFinishedForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewTransitionAsyncFinished;
using ScopedViewTransitionDelayUnpauseOnTeardownForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewTransitionDelayUnpauseOnTeardown;
using ScopedViewTransitionHoistBackdropFilterEffectForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewTransitionHoistBackdropFilterEffect;
using ScopedViewTransitionLongCallbackTimeoutForTestingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewTransitionLongCallbackTimeoutForTesting;
using ScopedViewTransitionUpdateLifecycleBeforeReadyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewTransitionUpdateLifecycleBeforeReady;
using ScopedViewTransitionWaitUntilForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedViewTransitionWaitUntil;
using ScopedVisibilityCollapseColumnForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVisibilityCollapseColumn;
using ScopedVisualRectMappingFixForExpansionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedVisualRectMappingFixForExpansion;
using ScopedWakeLockForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWakeLock;
using ScopedWarnOnContentVisibilityRenderAccessForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWarnOnContentVisibilityRenderAccess;
using ScopedWebAppInstallationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppInstallation;
using ScopedWebAppLaunchQueueForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppLaunchQueue;
using ScopedWebAppScopeExtensionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppScopeExtensions;
using ScopedWebAppScopeSystemAccentColorForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppScopeSystemAccentColor;
using ScopedWebAppTabStripForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppTabStrip;
using ScopedWebAppTabStripCustomizationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppTabStripCustomizations;
using ScopedWebAppTranslationsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAppTranslations;
using ScopedWebAssemblyCustomDescriptorsV2ForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAssemblyCustomDescriptorsV2;
using ScopedWebAssemblyJSPromiseIntegrationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAssemblyJSPromiseIntegration;
using ScopedWebAudioBypassOutputBufferingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAudioBypassOutputBuffering;
using ScopedWebAudioBypassOutputBufferingOptOutForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAudioBypassOutputBufferingOptOut;
using ScopedWebAudioConfigurableRenderQuantumForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAudioConfigurableRenderQuantum;
using ScopedWebAuthForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuth;
using ScopedWebAuthAuthenticatorAttachmentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuthAuthenticatorAttachment;
using ScopedWebAuthenticationAmbientForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuthenticationAmbient;
using ScopedWebAuthenticationAttestationFormatsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuthenticationAttestationFormats;
using ScopedWebAuthenticationImmediateGetForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuthenticationImmediateGet;
using ScopedWebAuthenticationRemoteDesktopSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuthenticationRemoteDesktopSupport;
using ScopedWebAuthenticationSupplementalPubKeysForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebAuthenticationSupplementalPubKeys;
using ScopedWebBluetoothForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebBluetooth;
using ScopedWebBluetoothGetDevicesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebBluetoothGetDevices;
using ScopedWebBluetoothScanningForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebBluetoothScanning;
using ScopedWebBluetoothWatchAdvertisementsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebBluetoothWatchAdvertisements;
using ScopedWebCodecsVideoEncoderBuffersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebCodecsVideoEncoderBuffers;
using ScopedWebCryptoPQCForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebCryptoPQC;
using ScopedWebFontResizeLCPForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebFontResizeLCP;
using ScopedWebGLDeveloperExtensionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGLDeveloperExtensions;
using ScopedWebGLDraftExtensionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGLDraftExtensions;
using ScopedWebGLDrawingBufferStorageForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGLDrawingBufferStorage;
using ScopedWebGLOnWebGPUForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGLOnWebGPU;
using ScopedWebGPUCompatibilityModeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUCompatibilityMode;
using ScopedWebGPUDeveloperFeaturesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUDeveloperFeatures;
using ScopedWebGPUExperimentalFeaturesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUExperimentalFeatures;
using ScopedWebGPUImmediatesFeatureForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUImmediatesFeature;
using ScopedWebGPUMapSyncOnWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUMapSyncOnWorkers;
using ScopedWebGPUMultithreadDawnWireOnWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUMultithreadDawnWireOnWorkers;
using ScopedWebGPUTransientAttachmentForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebGPUTransientAttachment;
using ScopedWebHIDForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebHID;
using ScopedWebHIDOnServiceWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebHIDOnServiceWorkers;
using ScopedWebIdentityDigitalCredentialsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebIdentityDigitalCredentials;
using ScopedWebIdentityDigitalCredentialsCreationForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebIdentityDigitalCredentialsCreation;
using ScopedWebIDLBigIntUsesToBigIntForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebIDLBigIntUsesToBigInt;
using ScopedWebMCPForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebMCP;
using ScopedWebMCPDeclarativeFileInputForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebMCPDeclarativeFileInput;
using ScopedWebMCPFormAssociatedCustomElementsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebMCPFormAssociatedCustomElements;
using ScopedWebMCPTestingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebMCPTesting;
using ScopedWebNFCForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebNFC;
using ScopedWebOTPForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebOTP;
using ScopedWebOTPAssertionFeaturePolicyForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebOTPAssertionFeaturePolicy;
using ScopedWebPreferencesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebPreferences;
using ScopedWebPrintingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebPrinting;
using ScopedWebShareForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebShare;
using ScopedWebSocketStreamForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebSocketStream;
using ScopedWebSocketStreamStandardBinaryChunkTypeForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebSocketStreamStandardBinaryChunkType;
using ScopedWebSpeechRecognitionContextForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebSpeechRecognitionContext;
using ScopedWebTransportApplicationProtocolForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebTransportApplicationProtocol;
using ScopedWebTransportCongestionControlForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebTransportCongestionControl;
using ScopedWebTransportCustomCertificatesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebTransportCustomCertificates;
using ScopedWebTransportSendGroupForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebTransportSendGroup;
using ScopedWebTransportStatsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebTransportStats;
using ScopedWebUIBundledCodeCacheAsyncFetchForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebUIBundledCodeCacheAsyncFetch;
using ScopedWebUSBForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebUSB;
using ScopedWebUSBOnDedicatedWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebUSBOnDedicatedWorkers;
using ScopedWebUSBOnServiceWorkersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebUSBOnServiceWorkers;
using ScopedWebVTTRegionsForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebVTTRegions;
using ScopedWebXRForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXR;
using ScopedWebXREnabledFeaturesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXREnabledFeatures;
using ScopedWebXRFrameRateForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRFrameRate;
using ScopedWebXRFrontFacingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRFrontFacing;
using ScopedWebXRGPUBindingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRGPUBinding;
using ScopedWebXRHitTestEntityTypesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRHitTestEntityTypes;
using ScopedWebXRImageTrackingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRImageTracking;
using ScopedWebXRLayersForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRLayers;
using ScopedWebXRLayersCommonForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRLayersCommon;
using ScopedWebXRMeshDetectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRMeshDetection;
using ScopedWebXRPlaneDetectionForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRPlaneDetection;
using ScopedWebXRPoseMotionDataForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRPoseMotionData;
using ScopedWebXRSpecParityForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRSpecParity;
using ScopedWebXRVisibilityMaskForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWebXRVisibilityMask;
using ScopedWindowDefaultStatusForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWindowDefaultStatus;
using ScopedWordSkipSpacesPunctuationFixForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWordSkipSpacesPunctuationFix;
using ScopedWordSpacingWhiteSpacePreForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedWordSpacingWhiteSpacePre;
using ScopedXMLNoExternalEntitiesForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXMLNoExternalEntities;
using ScopedXMLParsingRustForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXMLParsingRust;
using ScopedXMLRustForNonXsltForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXMLRustForNonXslt;
using ScopedXMLSerializerConsistentDefaultNsDeclMatchingForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXMLSerializerConsistentDefaultNsDeclMatching;
using ScopedXPathShadowDOMSupportForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXPathShadowDOMSupport;
using ScopedXSLTForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXSLT;
using ScopedXSLTSpecialTrialForTest =
    RuntimeEnabledFeaturesTestHelpers::ScopedXSLTSpecialTrial;
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_ENABLED_FEATURES_TEST_HELPERS_H_
