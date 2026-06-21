// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/policy_helper.cc.tmpl
// and input files:
//   C:\Repos\chromium\services\network\public\cpp\permissions_policy\permissions_policy_features.json5
//   C:\Repos\chromium\third_party\blink\renderer\core\permissions_policy\document_policy_features.json5
//   C:\Repos\chromium\third_party\blink\renderer\platform\runtime_enabled_features.json5


#include "third_party/blink/renderer/core/permissions_policy/policy_helper.h"

#include "third_party/blink/public/mojom/permissions_policy/document_policy_feature.mojom-blink.h"
#include "services/network/public/mojom/permissions_policy/permissions_policy_feature.mojom-blink.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/inspector/protocol/page.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"

namespace blink {
namespace {

const char kAccelerometerPolicyName[] = "accelerometer";
const char kAllScreensCapturePolicyName[] = "all-screens-capture";
const char kAmbientLightSensorPolicyName[] = "ambient-light-sensor";
const char kAriaNotifyPolicyName[] = "aria-notify";
const char kAttributionReportingPolicyName[] = "attribution-reporting";
const char kAutofillPolicyName[] = "autofill";
const char kAutoplayPolicyName[] = "autoplay";
const char kBluetoothPolicyName[] = "bluetooth";
const char kBrowsingTopicsPolicyName[] = "browsing-topics";
const char kBrowsingTopicsBackwardCompatiblePolicyName[] = "interest-cohort";
const char kCameraPolicyName[] = "camera";
const char kCapturedSurfaceControlPolicyName[] = "captured-surface-control";
const char kClientHintDPRPolicyName[] = "ch-dpr";
const char kClientHintDeviceMemoryPolicyName[] = "ch-device-memory";
const char kClientHintDownlinkPolicyName[] = "ch-downlink";
const char kClientHintECTPolicyName[] = "ch-ect";
const char kClientHintPrefersColorSchemePolicyName[] = "ch-prefers-color-scheme";
const char kClientHintPrefersReducedMotionPolicyName[] = "ch-prefers-reduced-motion";
const char kClientHintPrefersReducedTransparencyPolicyName[] = "ch-prefers-reduced-transparency";
const char kClientHintRTTPolicyName[] = "ch-rtt";
const char kClientHintSaveDataPolicyName[] = "ch-save-data";
const char kClientHintUAPolicyName[] = "ch-ua";
const char kClientHintUAArchPolicyName[] = "ch-ua-arch";
const char kClientHintUABitnessPolicyName[] = "ch-ua-bitness";
const char kClientHintUAFormFactorsPolicyName[] = "ch-ua-form-factors";
const char kClientHintUAHighEntropyValuesPolicyName[] = "ch-ua-high-entropy-values";
const char kClientHintUAPlatformPolicyName[] = "ch-ua-platform";
const char kClientHintUAModelPolicyName[] = "ch-ua-model";
const char kClientHintUAMobilePolicyName[] = "ch-ua-mobile";
const char kClientHintUAFullVersionPolicyName[] = "ch-ua-full-version";
const char kClientHintUAFullVersionListPolicyName[] = "ch-ua-full-version-list";
const char kClientHintUAPlatformVersionPolicyName[] = "ch-ua-platform-version";
const char kClientHintUAWoW64PolicyName[] = "ch-ua-wow64";
const char kClientHintViewportHeightPolicyName[] = "ch-viewport-height";
const char kClientHintViewportWidthPolicyName[] = "ch-viewport-width";
const char kClientHintWidthPolicyName[] = "ch-width";
const char kClipboardReadPolicyName[] = "clipboard-read";
const char kClipboardWritePolicyName[] = "clipboard-write";
const char kComputePressurePolicyName[] = "compute-pressure";
const char kControlledFramePolicyName[] = "controlled-frame";
const char kCrossOriginIsolatedPolicyName[] = "cross-origin-isolated";
const char kDeferredFetchPolicyName[] = "deferred-fetch";
const char kDeferredFetchMinimalPolicyName[] = "deferred-fetch-minimal";
const char kDeviceAttributesPolicyName[] = "device-attributes";
const char kDigitalCredentialsCreatePolicyName[] = "digital-credentials-create";
const char kDigitalCredentialsGetPolicyName[] = "digital-credentials-get";
const char kDirectSocketsPolicyName[] = "direct-sockets";
const char kDirectSocketsPrivatePolicyName[] = "direct-sockets-private";
const char kDisplayCapturePolicyName[] = "display-capture";
const char kEncryptedMediaPolicyName[] = "encrypted-media";
const char kExecutionWhileOutOfViewportPolicyName[] = "execution-while-out-of-viewport";
const char kExecutionWhileNotRenderedPolicyName[] = "execution-while-not-rendered";
const char kFocusWithoutUserActivationPolicyName[] = "focus-without-user-activation";
const char kFullscreenPolicyName[] = "fullscreen";
const char kFrobulatePolicyName[] = "frobulate";
const char kGamepadPolicyName[] = "gamepad";
const char kGeolocationPolicyName[] = "geolocation";
const char kGyroscopePolicyName[] = "gyroscope";
const char kHidPolicyName[] = "hid";
const char kIdentityCredentialsGetPolicyName[] = "identity-credentials-get";
const char kIdleDetectionPolicyName[] = "idle-detection";
const char kJoinAdInterestGroupPolicyName[] = "join-ad-interest-group";
const char kKeyboardMapPolicyName[] = "keyboard-map";
const char kLanguageDetectorPolicyName[] = "language-detector";
const char kLanguageModelPolicyName[] = "language-model";
const char kLocalFontsPolicyName[] = "local-fonts";
const char kLocalNetworkPolicyName[] = "local-network";
const char kLocalNetworkAccessPolicyName[] = "local-network-access";
const char kLoopbackNetworkPolicyName[] = "loopback-network";
const char kMagnetometerPolicyName[] = "magnetometer";
const char kManualTextPolicyName[] = "manual-text";
const char kMediaPlaybackWhileNotVisiblePolicyName[] = "media-playback-while-not-visible";
const char kMicrophonePolicyName[] = "microphone";
const char kMidiFeaturePolicyName[] = "midi";
const char kMulticastInDirectSocketsPolicyName[] = "direct-sockets-multicast";
const char kOnDeviceSpeechRecognitionPolicyName[] = "on-device-speech-recognition";
const char kOTPCredentialsPolicyName[] = "otp-credentials";
const char kPaymentPolicyName[] = "payment";
const char kPictureInPicturePolicyName[] = "picture-in-picture";
const char kPrivateAggregationPolicyName[] = "private-aggregation";
const char kPrivateStateTokenIssuancePolicyName[] = "private-state-token-issuance";
const char kPublicKeyCredentialsCreatePolicyName[] = "publickey-credentials-create";
const char kPublicKeyCredentialsGetPolicyName[] = "publickey-credentials-get";
const char kRecordAdAuctionEventsPolicyName[] = "record-ad-auction-events";
const char kRewriterPolicyName[] = "rewriter";
const char kRunAdAuctionPolicyName[] = "run-ad-auction";
const char kScreenWakeLockPolicyName[] = "screen-wake-lock";
const char kSerialPolicyName[] = "serial";
const char kSharedStoragePolicyName[] = "shared-storage";
const char kSharedStorageSelectUrlPolicyName[] = "shared-storage-select-url";
const char kSmartCardPolicyName[] = "smart-card";
const char kSpeakerSelectionPolicyName[] = "speaker-selection";
const char kStorageAccessAPIPolicyName[] = "storage-access";
const char kSubAppsPolicyName[] = "sub-apps";
const char kSummarizerPolicyName[] = "summarizer";
const char kSyncXHRPolicyName[] = "sync-xhr";
const char kTranslatorPolicyName[] = "translator";
const char kTrustTokenRedemptionPolicyName[] = "private-state-token-redemption";
const char kUsbPolicyName[] = "usb";
const char kUsbUnrestrictedPolicyName[] = "usb-unrestricted";
const char kUnloadPolicyName[] = "unload";
const char kVerticalScrollPolicyName[] = "vertical-scroll";
const char kWebAppInstallationPolicyName[] = "web-app-installation";
const char kToolsPolicyName[] = "tools";
const char kWebNNPolicyName[] = "webnn";
const char kWebPrintingPolicyName[] = "web-printing";
const char kWebSharePolicyName[] = "web-share";
const char kWebXrPolicyName[] = "xr-spatial-tracking";
const char kWindowManagementPolicyName[] = "window-management";
const char kWriterPolicyName[] = "writer";

}  // namespace

// Features which depend on a flag also have the same flag controlling whether
// they are in this map. Features which are shipping as part of an origin trial
// add their feature names to this map unconditionally, as the trial token could
// be added after the HTTP header needs to be parsed. This also means that
// top-level documents which simply want to embed another page which uses an
// origin trial feature, without using the feature themselves, can use
// permissions policy to allow use of the feature in subframes (The framed
// document will still require a valid origin trial token to use the feature in
// this scenario).
const FeatureNameMap& GetDefaultFeatureNameMap(bool is_isolated_context) {
  DEFINE_STATIC_LOCAL(FeatureNameMap, isolated_default_feature_name_map, ());
  DEFINE_STATIC_LOCAL(FeatureNameMap, non_isolated_default_feature_name_map, ());

  FeatureNameMap& default_feature_name_map = is_isolated_context ?
    isolated_default_feature_name_map : non_isolated_default_feature_name_map;

  // If we've already computed the map, return it.
  if (default_feature_name_map.size() > 0) {
    return default_feature_name_map;
  }

  // Build the map for the first time.
  default_feature_name_map.ReserveCapacityForSize(110);

  default_feature_name_map.Set(
      kAccelerometerPolicyName,
      network::mojom::PermissionsPolicyFeature::kAccelerometer);
  default_feature_name_map.Set(
      kAutoplayPolicyName,
      network::mojom::PermissionsPolicyFeature::kAutoplay);
  default_feature_name_map.Set(
      kCameraPolicyName,
      network::mojom::PermissionsPolicyFeature::kCamera);
  default_feature_name_map.Set(
      kClientHintDPRPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintDPR);
  default_feature_name_map.Set(
      kClientHintDeviceMemoryPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintDeviceMemory);
  default_feature_name_map.Set(
      kClientHintDownlinkPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintDownlink);
  default_feature_name_map.Set(
      kClientHintECTPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintECT);
  default_feature_name_map.Set(
      kClientHintPrefersColorSchemePolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintPrefersColorScheme);
  default_feature_name_map.Set(
      kClientHintPrefersReducedMotionPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintPrefersReducedMotion);
  default_feature_name_map.Set(
      kClientHintPrefersReducedTransparencyPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintPrefersReducedTransparency);
  default_feature_name_map.Set(
      kClientHintRTTPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintRTT);
  default_feature_name_map.Set(
      kClientHintSaveDataPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintSaveData);
  default_feature_name_map.Set(
      kClientHintUAPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUA);
  default_feature_name_map.Set(
      kClientHintUAArchPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAArch);
  default_feature_name_map.Set(
      kClientHintUABitnessPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUABitness);
  default_feature_name_map.Set(
      kClientHintUAFormFactorsPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAFormFactors);
  default_feature_name_map.Set(
      kClientHintUAHighEntropyValuesPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAHighEntropyValues);
  default_feature_name_map.Set(
      kClientHintUAPlatformPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAPlatform);
  default_feature_name_map.Set(
      kClientHintUAModelPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAModel);
  default_feature_name_map.Set(
      kClientHintUAMobilePolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAMobile);
  default_feature_name_map.Set(
      kClientHintUAFullVersionPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAFullVersion);
  default_feature_name_map.Set(
      kClientHintUAFullVersionListPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAFullVersionList);
  default_feature_name_map.Set(
      kClientHintUAPlatformVersionPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAPlatformVersion);
  default_feature_name_map.Set(
      kClientHintUAWoW64PolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintUAWoW64);
  default_feature_name_map.Set(
      kClientHintViewportWidthPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintViewportWidth);
  default_feature_name_map.Set(
      kClientHintWidthPolicyName,
      network::mojom::PermissionsPolicyFeature::kClientHintWidth);
  default_feature_name_map.Set(
      kClipboardReadPolicyName,
      network::mojom::PermissionsPolicyFeature::kClipboardRead);
  default_feature_name_map.Set(
      kClipboardWritePolicyName,
      network::mojom::PermissionsPolicyFeature::kClipboardWrite);
  default_feature_name_map.Set(
      kCrossOriginIsolatedPolicyName,
      network::mojom::PermissionsPolicyFeature::kCrossOriginIsolated);
  default_feature_name_map.Set(
      kDigitalCredentialsCreatePolicyName,
      network::mojom::PermissionsPolicyFeature::kDigitalCredentialsCreate);
  if (is_isolated_context) {
    default_feature_name_map.Set(
        kDirectSocketsPolicyName,
        network::mojom::PermissionsPolicyFeature::kDirectSockets);
  }
  if (is_isolated_context) {
    default_feature_name_map.Set(
        kDirectSocketsPrivatePolicyName,
        network::mojom::PermissionsPolicyFeature::kDirectSocketsPrivate);
  }
  default_feature_name_map.Set(
      kDisplayCapturePolicyName,
      network::mojom::PermissionsPolicyFeature::kDisplayCapture);
  default_feature_name_map.Set(
      kEncryptedMediaPolicyName,
      network::mojom::PermissionsPolicyFeature::kEncryptedMedia);
  default_feature_name_map.Set(
      kFocusWithoutUserActivationPolicyName,
      network::mojom::PermissionsPolicyFeature::kFocusWithoutUserActivation);
  default_feature_name_map.Set(
      kFullscreenPolicyName,
      network::mojom::PermissionsPolicyFeature::kFullscreen);
  default_feature_name_map.Set(
      kFrobulatePolicyName,
      network::mojom::PermissionsPolicyFeature::kFrobulate);
  default_feature_name_map.Set(
      kGamepadPolicyName,
      network::mojom::PermissionsPolicyFeature::kGamepad);
  default_feature_name_map.Set(
      kGeolocationPolicyName,
      network::mojom::PermissionsPolicyFeature::kGeolocation);
  default_feature_name_map.Set(
      kGyroscopePolicyName,
      network::mojom::PermissionsPolicyFeature::kGyroscope);
  default_feature_name_map.Set(
      kIdentityCredentialsGetPolicyName,
      network::mojom::PermissionsPolicyFeature::kIdentityCredentialsGet);
  default_feature_name_map.Set(
      kIdleDetectionPolicyName,
      network::mojom::PermissionsPolicyFeature::kIdleDetection);
  default_feature_name_map.Set(
      kJoinAdInterestGroupPolicyName,
      network::mojom::PermissionsPolicyFeature::kJoinAdInterestGroup);
  default_feature_name_map.Set(
      kKeyboardMapPolicyName,
      network::mojom::PermissionsPolicyFeature::kKeyboardMap);
  default_feature_name_map.Set(
      kLocalNetworkPolicyName,
      network::mojom::PermissionsPolicyFeature::kLocalNetwork);
  default_feature_name_map.Set(
      kLoopbackNetworkPolicyName,
      network::mojom::PermissionsPolicyFeature::kLoopbackNetwork);
  default_feature_name_map.Set(
      kMagnetometerPolicyName,
      network::mojom::PermissionsPolicyFeature::kMagnetometer);
  default_feature_name_map.Set(
      kMediaPlaybackWhileNotVisiblePolicyName,
      network::mojom::PermissionsPolicyFeature::kMediaPlaybackWhileNotVisible);
  default_feature_name_map.Set(
      kMicrophonePolicyName,
      network::mojom::PermissionsPolicyFeature::kMicrophone);
  default_feature_name_map.Set(
      kMidiFeaturePolicyName,
      network::mojom::PermissionsPolicyFeature::kMidiFeature);
  if (is_isolated_context) {
    default_feature_name_map.Set(
        kMulticastInDirectSocketsPolicyName,
        network::mojom::PermissionsPolicyFeature::kMulticastInDirectSockets);
  }
  default_feature_name_map.Set(
      kPaymentPolicyName,
      network::mojom::PermissionsPolicyFeature::kPayment);
  default_feature_name_map.Set(
      kPictureInPicturePolicyName,
      network::mojom::PermissionsPolicyFeature::kPictureInPicture);
  default_feature_name_map.Set(
      kPublicKeyCredentialsCreatePolicyName,
      network::mojom::PermissionsPolicyFeature::kPublicKeyCredentialsCreate);
  default_feature_name_map.Set(
      kPublicKeyCredentialsGetPolicyName,
      network::mojom::PermissionsPolicyFeature::kPublicKeyCredentialsGet);
  default_feature_name_map.Set(
      kRewriterPolicyName,
      network::mojom::PermissionsPolicyFeature::kRewriter);
  default_feature_name_map.Set(
      kStorageAccessAPIPolicyName,
      network::mojom::PermissionsPolicyFeature::kStorageAccessAPI);
  default_feature_name_map.Set(
      kSyncXHRPolicyName,
      network::mojom::PermissionsPolicyFeature::kSyncXHR);
  default_feature_name_map.Set(
      kUnloadPolicyName,
      network::mojom::PermissionsPolicyFeature::kUnload);
  default_feature_name_map.Set(
      kWebAppInstallationPolicyName,
      network::mojom::PermissionsPolicyFeature::kWebAppInstallation);
  default_feature_name_map.Set(
      kToolsPolicyName,
      network::mojom::PermissionsPolicyFeature::kTools);
  default_feature_name_map.Set(
      kWindowManagementPolicyName,
      network::mojom::PermissionsPolicyFeature::kWindowManagement);
  default_feature_name_map.Set(
      kWriterPolicyName,
      network::mojom::PermissionsPolicyFeature::kWriter);
  if (RuntimeEnabledFeatures::AIPromptAPIEnabled()) {
    default_feature_name_map.Set(kLanguageModelPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kLanguageModel);
  }
  if (RuntimeEnabledFeatures::AISummarizationAPIEnabled()) {
    default_feature_name_map.Set(kSummarizerPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kSummarizer);
  }
  if (RuntimeEnabledFeatures::AriaNotifyEnabled()) {
    default_feature_name_map.Set(kAriaNotifyPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kAriaNotify);
  }
  if (RuntimeEnabledFeatures::AttributionReportingEnabled()) {
    default_feature_name_map.Set(kAttributionReportingPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kAttributionReporting);
  }
  if (RuntimeEnabledFeatures::AutofillEnabled()) {
    default_feature_name_map.Set(kAutofillPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kAutofill);
  }
  if (RuntimeEnabledFeatures::CapturedSurfaceControlEnabled()) {
    default_feature_name_map.Set(kCapturedSurfaceControlPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kCapturedSurfaceControl);
  }
  if (RuntimeEnabledFeatures::ComputePressureEnabled()) {
    default_feature_name_map.Set(kComputePressurePolicyName,
                                 network::mojom::PermissionsPolicyFeature::kComputePressure);
  }
  if (RuntimeEnabledFeatures::ControlledFrameEnabled()) {
    if (is_isolated_context) {
      default_feature_name_map.Set(
          kControlledFramePolicyName,
          network::mojom::PermissionsPolicyFeature::kControlledFrame);
    }
  }
  if (RuntimeEnabledFeatures::DeviceAttributesEnabled()) {
    default_feature_name_map.Set(kDeviceAttributesPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kDeviceAttributes);
  }
  if (RuntimeEnabledFeatures::ExperimentalPoliciesEnabled()) {
    default_feature_name_map.Set(kVerticalScrollPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kVerticalScroll);
  }
  if (RuntimeEnabledFeatures::FetchLaterAPIEnabled()) {
    default_feature_name_map.Set(kDeferredFetchPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kDeferredFetch);
    default_feature_name_map.Set(kDeferredFetchMinimalPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kDeferredFetchMinimal);
  }
  if (RuntimeEnabledFeatures::FledgeEnabled()) {
    default_feature_name_map.Set(kPrivateAggregationPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kPrivateAggregation);
    default_feature_name_map.Set(kRunAdAuctionPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kRunAdAuction);
  }
  if (RuntimeEnabledFeatures::FledgeClickinessEnabled()) {
    default_feature_name_map.Set(kRecordAdAuctionEventsPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kRecordAdAuctionEvents);
  }
  if (RuntimeEnabledFeatures::FontAccessEnabled()) {
    default_feature_name_map.Set(kLocalFontsPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kLocalFonts);
  }
  if (RuntimeEnabledFeatures::FreezeFramesOnVisibilityEnabled()) {
    default_feature_name_map.Set(kExecutionWhileOutOfViewportPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kExecutionWhileOutOfViewport);
    default_feature_name_map.Set(kExecutionWhileNotRenderedPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kExecutionWhileNotRendered);
  }
  if (RuntimeEnabledFeatures::GetAllScreensMediaEnabled()) {
    if (is_isolated_context) {
      default_feature_name_map.Set(
          kAllScreensCapturePolicyName,
          network::mojom::PermissionsPolicyFeature::kAllScreensCapture);
    }
  }
  if (RuntimeEnabledFeatures::LanguageDetectionAPIEnabled()) {
    default_feature_name_map.Set(kLanguageDetectorPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kLanguageDetector);
  }
  if (RuntimeEnabledFeatures::LocalNetworkAccessPermissionPolicyEnabled()) {
    default_feature_name_map.Set(kLocalNetworkAccessPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kLocalNetworkAccess);
  }
  if (RuntimeEnabledFeatures::MachineLearningNeuralNetworkEnabled()) {
    default_feature_name_map.Set(kWebNNPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kWebNN);
  }
  if (RuntimeEnabledFeatures::ManualTextEnabled()) {
    default_feature_name_map.Set(kManualTextPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kManualText);
  }
  if (RuntimeEnabledFeatures::OnDeviceWebSpeechAvailableEnabled()) {
    default_feature_name_map.Set(kOnDeviceSpeechRecognitionPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kOnDeviceSpeechRecognition);
  }
  if (RuntimeEnabledFeatures::PrivateStateTokensEnabled()) {
    default_feature_name_map.Set(kPrivateStateTokenIssuancePolicyName,
                                 network::mojom::PermissionsPolicyFeature::kPrivateStateTokenIssuance);
    default_feature_name_map.Set(kTrustTokenRedemptionPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kTrustTokenRedemption);
  }
  if (RuntimeEnabledFeatures::SensorExtraClassesEnabled()) {
    default_feature_name_map.Set(kAmbientLightSensorPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kAmbientLightSensor);
  }
  if (RuntimeEnabledFeatures::SerialEnabled()) {
    default_feature_name_map.Set(kSerialPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kSerial);
  }
  if (RuntimeEnabledFeatures::SharedStorageAPIEnabled()) {
    default_feature_name_map.Set(kPrivateAggregationPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kPrivateAggregation);
    default_feature_name_map.Set(kSharedStoragePolicyName,
                                 network::mojom::PermissionsPolicyFeature::kSharedStorage);
    default_feature_name_map.Set(kSharedStorageSelectUrlPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kSharedStorageSelectUrl);
  }
  if (RuntimeEnabledFeatures::SmartCardEnabled()) {
    if (is_isolated_context) {
      default_feature_name_map.Set(
          kSmartCardPolicyName,
          network::mojom::PermissionsPolicyFeature::kSmartCard);
    }
  }
  if (RuntimeEnabledFeatures::SpeakerSelectionEnabled()) {
    default_feature_name_map.Set(kSpeakerSelectionPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kSpeakerSelection);
  }
  if (RuntimeEnabledFeatures::SubAppsEnabled()) {
    if (is_isolated_context) {
      default_feature_name_map.Set(
          kSubAppsPolicyName,
          network::mojom::PermissionsPolicyFeature::kSubApps);
    }
  }
  if (RuntimeEnabledFeatures::TopicsAPIEnabled()) {
    default_feature_name_map.Set(kBrowsingTopicsPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kBrowsingTopics);
    default_feature_name_map.Set(kBrowsingTopicsBackwardCompatiblePolicyName,
                                 network::mojom::PermissionsPolicyFeature::kBrowsingTopicsBackwardCompatible);
  }
  if (RuntimeEnabledFeatures::TranslationAPIEnabled()) {
    default_feature_name_map.Set(kTranslatorPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kTranslator);
  }
  if (RuntimeEnabledFeatures::UnrestrictedUsbEnabled()) {
    if (is_isolated_context) {
      default_feature_name_map.Set(
          kUsbUnrestrictedPolicyName,
          network::mojom::PermissionsPolicyFeature::kUsbUnrestricted);
    }
  }
  if (RuntimeEnabledFeatures::ViewportHeightClientHintHeaderEnabled()) {
    default_feature_name_map.Set(kClientHintViewportHeightPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kClientHintViewportHeight);
  }
  if (RuntimeEnabledFeatures::WakeLockEnabled()) {
    default_feature_name_map.Set(kScreenWakeLockPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kScreenWakeLock);
  }
  if (RuntimeEnabledFeatures::WebBluetoothEnabled()) {
    default_feature_name_map.Set(kBluetoothPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kBluetooth);
  }
  if (RuntimeEnabledFeatures::WebHIDEnabled()) {
    default_feature_name_map.Set(kHidPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kHid);
  }
  if (RuntimeEnabledFeatures::WebIdentityDigitalCredentialsEnabled()) {
    default_feature_name_map.Set(kDigitalCredentialsGetPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kDigitalCredentialsGet);
  }
  if (RuntimeEnabledFeatures::WebOTPAssertionFeaturePolicyEnabled()) {
    default_feature_name_map.Set(kOTPCredentialsPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kOTPCredentials);
  }
  if (RuntimeEnabledFeatures::WebPrintingEnabled()) {
    if (is_isolated_context) {
      default_feature_name_map.Set(
          kWebPrintingPolicyName,
          network::mojom::PermissionsPolicyFeature::kWebPrinting);
    }
  }
  if (RuntimeEnabledFeatures::WebShareEnabled()) {
    default_feature_name_map.Set(kWebSharePolicyName,
                                 network::mojom::PermissionsPolicyFeature::kWebShare);
  }
  if (RuntimeEnabledFeatures::WebUSBEnabled()) {
    default_feature_name_map.Set(kUsbPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kUsb);
  }
  if (RuntimeEnabledFeatures::WebXREnabled()) {
    default_feature_name_map.Set(kWebXrPolicyName,
                                 network::mojom::PermissionsPolicyFeature::kWebXr);
  }

  return default_feature_name_map;
}


DocumentPolicyFeatureSet& GetAvailableDocumentPolicyFeaturesInternal() {
  DEFINE_STATIC_LOCAL(DocumentPolicyFeatureSet, features, ());
  return features;
}


void ResetAvailableDocumentPolicyFeaturesForTest() {
  GetAvailableDocumentPolicyFeaturesInternal().clear();
}

bool IsPrivacySensitiveFeature(network::mojom::blink::PermissionsPolicyFeature feature) {
  switch (feature) {
    case network::mojom::PermissionsPolicyFeature::kBluetooth:
      return true;
    case network::mojom::PermissionsPolicyFeature::kCamera:
      return true;
    case network::mojom::PermissionsPolicyFeature::kClipboardRead:
      return true;
    case network::mojom::PermissionsPolicyFeature::kClipboardWrite:
      return true;
    case network::mojom::PermissionsPolicyFeature::kDisplayCapture:
      return true;
    case network::mojom::PermissionsPolicyFeature::kGeolocation:
      return true;
    case network::mojom::PermissionsPolicyFeature::kMicrophone:
      return true;
    case network::mojom::PermissionsPolicyFeature::kSerial:
      return true;
    case network::mojom::PermissionsPolicyFeature::kUsb:
      return true;
    default:
      return false;
  }
  NOTREACHED();
}

const DocumentPolicyFeatureSet& GetAvailableDocumentPolicyFeatures() {
  DocumentPolicyFeatureSet& features = GetAvailableDocumentPolicyFeaturesInternal();
  if (features.empty()) {
    features.insert(mojom::DocumentPolicyFeature::kDefault);
    features.insert(mojom::DocumentPolicyFeature::kForceLoadAtTop);
    features.insert(mojom::DocumentPolicyFeature::kJSProfiling);
    features.insert(mojom::DocumentPolicyFeature::kIncludeJSCallStacksInCrashReports);
    if (RuntimeEnabledFeatures::DocumentPolicyExpectNoLinkedResourcesEnabled()) {
      features.insert(mojom::DocumentPolicyFeature::kExpectNoLinkedResources);
    }
    if (RuntimeEnabledFeatures::DocumentPolicyNetworkEfficiencyGuardrailsEnabled()) {
      features.insert(mojom::DocumentPolicyFeature::kNetworkEfficiencyGuardrails);
    }
    if (RuntimeEnabledFeatures::DocumentPolicySyncXHREnabled()) {
      features.insert(mojom::DocumentPolicyFeature::kSyncXHR);
    }
  }
  return features;
}

// If any of the origin trial runtime feature is enabled, returns false,
// i.e. the feature is considered enabled by origin trial.
bool DisabledByOriginTrial(const String& feature_name,
                           FeatureContext* feature_context) {
  if (feature_name == kDigitalCredentialsCreatePolicyName) {
    return !RuntimeEnabledFeatures::WebIdentityDigitalCredentialsCreationEnabled(feature_context);
  }
  if (feature_name == kFocusWithoutUserActivationPolicyName) {
    return !RuntimeEnabledFeatures::BlockingFocusWithoutUserActivationEnabled(feature_context);
  }
  if (feature_name == kFrobulatePolicyName) {
    return !RuntimeEnabledFeatures::OriginTrialsSampleAPIEnabled(feature_context);
  }
  if (feature_name == kJoinAdInterestGroupPolicyName) {
    return !RuntimeEnabledFeatures::AdInterestGroupAPIEnabled(feature_context);
  }
  if (feature_name == kMediaPlaybackWhileNotVisiblePolicyName) {
    return !RuntimeEnabledFeatures::MediaPlaybackWhileNotVisiblePermissionPolicyEnabled(feature_context);
  }
  if (feature_name == kRewriterPolicyName) {
    return !RuntimeEnabledFeatures::AIRewriterAPIEnabled(feature_context);
  }
  if (feature_name == kToolsPolicyName) {
    return !RuntimeEnabledFeatures::WebMCPEnabled(feature_context);
  }
  if (feature_name == kWebAppInstallationPolicyName) {
    return !RuntimeEnabledFeatures::WebAppInstallationEnabled(feature_context);
  }
  if (feature_name == kWriterPolicyName) {
    return !RuntimeEnabledFeatures::AIWriterAPIEnabled(feature_context);
  }
  return false;
}

bool DisabledByOriginTrial(mojom::blink::DocumentPolicyFeature feature,
                           FeatureContext* feature_context) {
  return false;
}

String PermissionsPolicyFeatureToProtocol(network::mojom::PermissionsPolicyFeature feature, ExecutionContext* execution_context) {
  if (execution_context && execution_context->IsIsolatedContext()) {
    switch (feature) {
      case network::mojom::PermissionsPolicyFeature::kAllScreensCapture:
        return protocol::Page::PermissionsPolicyFeatureEnum::AllScreensCapture;
      case network::mojom::PermissionsPolicyFeature::kControlledFrame:
        return protocol::Page::PermissionsPolicyFeatureEnum::ControlledFrame;
      case network::mojom::PermissionsPolicyFeature::kDirectSockets:
        return protocol::Page::PermissionsPolicyFeatureEnum::DirectSockets;
      case network::mojom::PermissionsPolicyFeature::kDirectSocketsPrivate:
        return protocol::Page::PermissionsPolicyFeatureEnum::DirectSocketsPrivate;
      case network::mojom::PermissionsPolicyFeature::kMulticastInDirectSockets:
        return protocol::Page::PermissionsPolicyFeatureEnum::DirectSocketsMulticast;
      case network::mojom::PermissionsPolicyFeature::kSmartCard:
        return protocol::Page::PermissionsPolicyFeatureEnum::SmartCard;
      case network::mojom::PermissionsPolicyFeature::kSubApps:
        return protocol::Page::PermissionsPolicyFeatureEnum::SubApps;
      case network::mojom::PermissionsPolicyFeature::kUsbUnrestricted:
        return protocol::Page::PermissionsPolicyFeatureEnum::UsbUnrestricted;
      case network::mojom::PermissionsPolicyFeature::kWebPrinting:
        return protocol::Page::PermissionsPolicyFeatureEnum::WebPrinting;
      default:
        break;
    }
  }
  switch (feature) {
    case network::mojom::PermissionsPolicyFeature::kAccelerometer:
      return protocol::Page::PermissionsPolicyFeatureEnum::Accelerometer;
    case network::mojom::PermissionsPolicyFeature::kAmbientLightSensor:
      return protocol::Page::PermissionsPolicyFeatureEnum::AmbientLightSensor;
    case network::mojom::PermissionsPolicyFeature::kAriaNotify:
      return protocol::Page::PermissionsPolicyFeatureEnum::AriaNotify;
    case network::mojom::PermissionsPolicyFeature::kAttributionReporting:
      return protocol::Page::PermissionsPolicyFeatureEnum::AttributionReporting;
    case network::mojom::PermissionsPolicyFeature::kAutofill:
      return protocol::Page::PermissionsPolicyFeatureEnum::Autofill;
    case network::mojom::PermissionsPolicyFeature::kAutoplay:
      return protocol::Page::PermissionsPolicyFeatureEnum::Autoplay;
    case network::mojom::PermissionsPolicyFeature::kBluetooth:
      return protocol::Page::PermissionsPolicyFeatureEnum::Bluetooth;
    case network::mojom::PermissionsPolicyFeature::kBrowsingTopics:
      return protocol::Page::PermissionsPolicyFeatureEnum::BrowsingTopics;
    case network::mojom::PermissionsPolicyFeature::kBrowsingTopicsBackwardCompatible:
      return protocol::Page::PermissionsPolicyFeatureEnum::InterestCohort;
    case network::mojom::PermissionsPolicyFeature::kCamera:
      return protocol::Page::PermissionsPolicyFeatureEnum::Camera;
    case network::mojom::PermissionsPolicyFeature::kCapturedSurfaceControl:
      return protocol::Page::PermissionsPolicyFeatureEnum::CapturedSurfaceControl;
    case network::mojom::PermissionsPolicyFeature::kClientHintDPR:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChDpr;
    case network::mojom::PermissionsPolicyFeature::kClientHintDeviceMemory:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChDeviceMemory;
    case network::mojom::PermissionsPolicyFeature::kClientHintDownlink:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChDownlink;
    case network::mojom::PermissionsPolicyFeature::kClientHintECT:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChEct;
    case network::mojom::PermissionsPolicyFeature::kClientHintPrefersColorScheme:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChPrefersColorScheme;
    case network::mojom::PermissionsPolicyFeature::kClientHintPrefersReducedMotion:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChPrefersReducedMotion;
    case network::mojom::PermissionsPolicyFeature::kClientHintPrefersReducedTransparency:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChPrefersReducedTransparency;
    case network::mojom::PermissionsPolicyFeature::kClientHintRTT:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChRtt;
    case network::mojom::PermissionsPolicyFeature::kClientHintSaveData:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChSaveData;
    case network::mojom::PermissionsPolicyFeature::kClientHintUA:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUa;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAArch:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaArch;
    case network::mojom::PermissionsPolicyFeature::kClientHintUABitness:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaBitness;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAFormFactors:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaFormFactors;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAHighEntropyValues:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaHighEntropyValues;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAPlatform:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaPlatform;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAModel:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaModel;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAMobile:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaMobile;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAFullVersion:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaFullVersion;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAFullVersionList:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaFullVersionList;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAPlatformVersion:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaPlatformVersion;
    case network::mojom::PermissionsPolicyFeature::kClientHintUAWoW64:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChUaWow64;
    case network::mojom::PermissionsPolicyFeature::kClientHintViewportHeight:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChViewportHeight;
    case network::mojom::PermissionsPolicyFeature::kClientHintViewportWidth:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChViewportWidth;
    case network::mojom::PermissionsPolicyFeature::kClientHintWidth:
      return protocol::Page::PermissionsPolicyFeatureEnum::ChWidth;
    case network::mojom::PermissionsPolicyFeature::kClipboardRead:
      return protocol::Page::PermissionsPolicyFeatureEnum::ClipboardRead;
    case network::mojom::PermissionsPolicyFeature::kClipboardWrite:
      return protocol::Page::PermissionsPolicyFeatureEnum::ClipboardWrite;
    case network::mojom::PermissionsPolicyFeature::kComputePressure:
      return protocol::Page::PermissionsPolicyFeatureEnum::ComputePressure;
    case network::mojom::PermissionsPolicyFeature::kCrossOriginIsolated:
      return protocol::Page::PermissionsPolicyFeatureEnum::CrossOriginIsolated;
    case network::mojom::PermissionsPolicyFeature::kDeferredFetch:
      return protocol::Page::PermissionsPolicyFeatureEnum::DeferredFetch;
    case network::mojom::PermissionsPolicyFeature::kDeferredFetchMinimal:
      return protocol::Page::PermissionsPolicyFeatureEnum::DeferredFetchMinimal;
    case network::mojom::PermissionsPolicyFeature::kDeviceAttributes:
      return protocol::Page::PermissionsPolicyFeatureEnum::DeviceAttributes;
    case network::mojom::PermissionsPolicyFeature::kDigitalCredentialsCreate:
      return protocol::Page::PermissionsPolicyFeatureEnum::DigitalCredentialsCreate;
    case network::mojom::PermissionsPolicyFeature::kDigitalCredentialsGet:
      return protocol::Page::PermissionsPolicyFeatureEnum::DigitalCredentialsGet;
    case network::mojom::PermissionsPolicyFeature::kDisplayCapture:
      return protocol::Page::PermissionsPolicyFeatureEnum::DisplayCapture;
    case network::mojom::PermissionsPolicyFeature::kEncryptedMedia:
      return protocol::Page::PermissionsPolicyFeatureEnum::EncryptedMedia;
    case network::mojom::PermissionsPolicyFeature::kExecutionWhileOutOfViewport:
      return protocol::Page::PermissionsPolicyFeatureEnum::ExecutionWhileOutOfViewport;
    case network::mojom::PermissionsPolicyFeature::kExecutionWhileNotRendered:
      return protocol::Page::PermissionsPolicyFeatureEnum::ExecutionWhileNotRendered;
    case network::mojom::PermissionsPolicyFeature::kFocusWithoutUserActivation:
      return protocol::Page::PermissionsPolicyFeatureEnum::FocusWithoutUserActivation;
    case network::mojom::PermissionsPolicyFeature::kFullscreen:
      return protocol::Page::PermissionsPolicyFeatureEnum::Fullscreen;
    case network::mojom::PermissionsPolicyFeature::kFrobulate:
      return protocol::Page::PermissionsPolicyFeatureEnum::Frobulate;
    case network::mojom::PermissionsPolicyFeature::kGamepad:
      return protocol::Page::PermissionsPolicyFeatureEnum::Gamepad;
    case network::mojom::PermissionsPolicyFeature::kGeolocation:
      return protocol::Page::PermissionsPolicyFeatureEnum::Geolocation;
    case network::mojom::PermissionsPolicyFeature::kGyroscope:
      return protocol::Page::PermissionsPolicyFeatureEnum::Gyroscope;
    case network::mojom::PermissionsPolicyFeature::kHid:
      return protocol::Page::PermissionsPolicyFeatureEnum::Hid;
    case network::mojom::PermissionsPolicyFeature::kIdentityCredentialsGet:
      return protocol::Page::PermissionsPolicyFeatureEnum::IdentityCredentialsGet;
    case network::mojom::PermissionsPolicyFeature::kIdleDetection:
      return protocol::Page::PermissionsPolicyFeatureEnum::IdleDetection;
    case network::mojom::PermissionsPolicyFeature::kJoinAdInterestGroup:
      return protocol::Page::PermissionsPolicyFeatureEnum::JoinAdInterestGroup;
    case network::mojom::PermissionsPolicyFeature::kKeyboardMap:
      return protocol::Page::PermissionsPolicyFeatureEnum::KeyboardMap;
    case network::mojom::PermissionsPolicyFeature::kLanguageDetector:
      return protocol::Page::PermissionsPolicyFeatureEnum::LanguageDetector;
    case network::mojom::PermissionsPolicyFeature::kLanguageModel:
      return protocol::Page::PermissionsPolicyFeatureEnum::LanguageModel;
    case network::mojom::PermissionsPolicyFeature::kLocalFonts:
      return protocol::Page::PermissionsPolicyFeatureEnum::LocalFonts;
    case network::mojom::PermissionsPolicyFeature::kLocalNetwork:
      return protocol::Page::PermissionsPolicyFeatureEnum::LocalNetwork;
    case network::mojom::PermissionsPolicyFeature::kLocalNetworkAccess:
      return protocol::Page::PermissionsPolicyFeatureEnum::LocalNetworkAccess;
    case network::mojom::PermissionsPolicyFeature::kLoopbackNetwork:
      return protocol::Page::PermissionsPolicyFeatureEnum::LoopbackNetwork;
    case network::mojom::PermissionsPolicyFeature::kMagnetometer:
      return protocol::Page::PermissionsPolicyFeatureEnum::Magnetometer;
    case network::mojom::PermissionsPolicyFeature::kManualText:
      return protocol::Page::PermissionsPolicyFeatureEnum::ManualText;
    case network::mojom::PermissionsPolicyFeature::kMediaPlaybackWhileNotVisible:
      return protocol::Page::PermissionsPolicyFeatureEnum::MediaPlaybackWhileNotVisible;
    case network::mojom::PermissionsPolicyFeature::kMicrophone:
      return protocol::Page::PermissionsPolicyFeatureEnum::Microphone;
    case network::mojom::PermissionsPolicyFeature::kMidiFeature:
      return protocol::Page::PermissionsPolicyFeatureEnum::Midi;
    case network::mojom::PermissionsPolicyFeature::kOnDeviceSpeechRecognition:
      return protocol::Page::PermissionsPolicyFeatureEnum::OnDeviceSpeechRecognition;
    case network::mojom::PermissionsPolicyFeature::kOTPCredentials:
      return protocol::Page::PermissionsPolicyFeatureEnum::OtpCredentials;
    case network::mojom::PermissionsPolicyFeature::kPayment:
      return protocol::Page::PermissionsPolicyFeatureEnum::Payment;
    case network::mojom::PermissionsPolicyFeature::kPictureInPicture:
      return protocol::Page::PermissionsPolicyFeatureEnum::PictureInPicture;
    case network::mojom::PermissionsPolicyFeature::kPrivateAggregation:
      return protocol::Page::PermissionsPolicyFeatureEnum::PrivateAggregation;
    case network::mojom::PermissionsPolicyFeature::kPrivateStateTokenIssuance:
      return protocol::Page::PermissionsPolicyFeatureEnum::PrivateStateTokenIssuance;
    case network::mojom::PermissionsPolicyFeature::kPublicKeyCredentialsCreate:
      return protocol::Page::PermissionsPolicyFeatureEnum::PublickeyCredentialsCreate;
    case network::mojom::PermissionsPolicyFeature::kPublicKeyCredentialsGet:
      return protocol::Page::PermissionsPolicyFeatureEnum::PublickeyCredentialsGet;
    case network::mojom::PermissionsPolicyFeature::kRecordAdAuctionEvents:
      return protocol::Page::PermissionsPolicyFeatureEnum::RecordAdAuctionEvents;
    case network::mojom::PermissionsPolicyFeature::kRewriter:
      return protocol::Page::PermissionsPolicyFeatureEnum::Rewriter;
    case network::mojom::PermissionsPolicyFeature::kRunAdAuction:
      return protocol::Page::PermissionsPolicyFeatureEnum::RunAdAuction;
    case network::mojom::PermissionsPolicyFeature::kScreenWakeLock:
      return protocol::Page::PermissionsPolicyFeatureEnum::ScreenWakeLock;
    case network::mojom::PermissionsPolicyFeature::kSerial:
      return protocol::Page::PermissionsPolicyFeatureEnum::Serial;
    case network::mojom::PermissionsPolicyFeature::kSharedStorage:
      return protocol::Page::PermissionsPolicyFeatureEnum::SharedStorage;
    case network::mojom::PermissionsPolicyFeature::kSharedStorageSelectUrl:
      return protocol::Page::PermissionsPolicyFeatureEnum::SharedStorageSelectUrl;
    case network::mojom::PermissionsPolicyFeature::kSpeakerSelection:
      return protocol::Page::PermissionsPolicyFeatureEnum::SpeakerSelection;
    case network::mojom::PermissionsPolicyFeature::kStorageAccessAPI:
      return protocol::Page::PermissionsPolicyFeatureEnum::StorageAccess;
    case network::mojom::PermissionsPolicyFeature::kSummarizer:
      return protocol::Page::PermissionsPolicyFeatureEnum::Summarizer;
    case network::mojom::PermissionsPolicyFeature::kSyncXHR:
      return protocol::Page::PermissionsPolicyFeatureEnum::SyncXhr;
    case network::mojom::PermissionsPolicyFeature::kTranslator:
      return protocol::Page::PermissionsPolicyFeatureEnum::Translator;
    case network::mojom::PermissionsPolicyFeature::kTrustTokenRedemption:
      return protocol::Page::PermissionsPolicyFeatureEnum::PrivateStateTokenRedemption;
    case network::mojom::PermissionsPolicyFeature::kUsb:
      return protocol::Page::PermissionsPolicyFeatureEnum::Usb;
    case network::mojom::PermissionsPolicyFeature::kUnload:
      return protocol::Page::PermissionsPolicyFeatureEnum::Unload;
    case network::mojom::PermissionsPolicyFeature::kVerticalScroll:
      return protocol::Page::PermissionsPolicyFeatureEnum::VerticalScroll;
    case network::mojom::PermissionsPolicyFeature::kWebAppInstallation:
      return protocol::Page::PermissionsPolicyFeatureEnum::WebAppInstallation;
    case network::mojom::PermissionsPolicyFeature::kTools:
      return protocol::Page::PermissionsPolicyFeatureEnum::Tools;
    case network::mojom::PermissionsPolicyFeature::kWebNN:
      return protocol::Page::PermissionsPolicyFeatureEnum::Webnn;
    case network::mojom::PermissionsPolicyFeature::kWebShare:
      return protocol::Page::PermissionsPolicyFeatureEnum::WebShare;
    case network::mojom::PermissionsPolicyFeature::kWebXr:
      return protocol::Page::PermissionsPolicyFeatureEnum::XrSpatialTracking;
    case network::mojom::PermissionsPolicyFeature::kWindowManagement:
      return protocol::Page::PermissionsPolicyFeatureEnum::WindowManagement;
    case network::mojom::PermissionsPolicyFeature::kWriter:
      return protocol::Page::PermissionsPolicyFeatureEnum::Writer;
    default:
      // This default case also handles the mojom entry for
      // network::mojom::PermissionsPolicyFeature::kNotFound.
      NOTREACHED();
  }
}

}  // namespace blink
