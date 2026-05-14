// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/runtime_feature_state_override_context.cc.tmpl
// and input files:
//   ../../third_party/blink/renderer/platform/runtime_enabled_features.json5


#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/mojom/origin_trials/origin_trial_feature.mojom-shared.h"
#if !defined(STANDALONE_RENDERER_GN_PROBE)
#include "third_party/blink/public/common/thread_safe_browser_interface_broker_proxy.h"
#include "third_party/blink/public/mojom/origin_trials/origin_trial_state_host.mojom-blink.h"
#include "third_party/blink/public/platform/browser_interface_broker_proxy.h"
#include "third_party/blink/public/platform/platform.h"
#endif
#if !defined(STANDALONE_RENDERER_GN_PROBE)
#include "third_party/blink/renderer/core/frame/web_feature.h"
#endif
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "third_party/blink/renderer/platform/runtime_feature_state/runtime_feature_state_override_context.h"

namespace blink {

void RuntimeFeatureStateOverrideContext::ApplyOverrideValuesFromParams(
    const base::flat_map<mojom::RuntimeFeature, bool>&
        values_from_params) {
  for(const auto& override_value : values_from_params) {
    override_values_[override_value.first] = override_value.second;
  }
}

bool RuntimeFeatureStateOverrideContext::
    IsBlinkExtensionChromeOSForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kBlinkExtensionChromeOS);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsBlinkExtensionChromeOSForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kBlinkExtensionChromeOS);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetBlinkExtensionChromeOSForceDisabled() {
  override_values_[mojom::RuntimeFeature::kBlinkExtensionChromeOS] = false;
}

void RuntimeFeatureStateOverrideContext::SetBlinkExtensionChromeOSForceEnabled() {
  override_values_[mojom::RuntimeFeature::kBlinkExtensionChromeOS] = true;
}

bool RuntimeFeatureStateOverrideContext::
    IsBlinkExtensionChromeOSIsolatedWebAppSetShapeForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kBlinkExtensionChromeOSIsolatedWebAppSetShape);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsBlinkExtensionChromeOSIsolatedWebAppSetShapeForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kBlinkExtensionChromeOSIsolatedWebAppSetShape);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetBlinkExtensionChromeOSIsolatedWebAppSetShapeForceDisabled() {
  override_values_[mojom::RuntimeFeature::kBlinkExtensionChromeOSIsolatedWebAppSetShape] = false;
}

void RuntimeFeatureStateOverrideContext::SetBlinkExtensionChromeOSIsolatedWebAppSetShapeForceEnabled() {
  override_values_[mojom::RuntimeFeature::kBlinkExtensionChromeOSIsolatedWebAppSetShape] = true;
}

bool RuntimeFeatureStateOverrideContext::
    IsBlinkExtensionChromeOSKioskForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kBlinkExtensionChromeOSKiosk);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsBlinkExtensionChromeOSKioskForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kBlinkExtensionChromeOSKiosk);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetBlinkExtensionChromeOSKioskForceDisabled() {
  override_values_[mojom::RuntimeFeature::kBlinkExtensionChromeOSKiosk] = false;
}

void RuntimeFeatureStateOverrideContext::SetBlinkExtensionChromeOSKioskForceEnabled() {
  override_values_[mojom::RuntimeFeature::kBlinkExtensionChromeOSKiosk] = true;
}

bool RuntimeFeatureStateOverrideContext::
    IsDirectSocketsForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kDirectSockets);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsDirectSocketsForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kDirectSockets);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetDirectSocketsForceDisabled() {
  override_values_[mojom::RuntimeFeature::kDirectSockets] = false;
}

void RuntimeFeatureStateOverrideContext::SetDirectSocketsForceEnabled() {
  override_values_[mojom::RuntimeFeature::kDirectSockets] = true;
}

bool RuntimeFeatureStateOverrideContext::
    IsGetDisplayMediaWindowAudioCaptureForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kGetDisplayMediaWindowAudioCapture);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsGetDisplayMediaWindowAudioCaptureForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kGetDisplayMediaWindowAudioCapture);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetGetDisplayMediaWindowAudioCaptureForceDisabled() {
  override_values_[mojom::RuntimeFeature::kGetDisplayMediaWindowAudioCapture] = false;
}

void RuntimeFeatureStateOverrideContext::SetGetDisplayMediaWindowAudioCaptureForceEnabled() {
  override_values_[mojom::RuntimeFeature::kGetDisplayMediaWindowAudioCapture] = true;
}

bool RuntimeFeatureStateOverrideContext::
    IsOriginTrialsSampleAPIBrowserReadWriteForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsOriginTrialsSampleAPIBrowserReadWriteForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetOriginTrialsSampleAPIBrowserReadWriteForceDisabled() {
  override_values_[mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite] = false;
}

void RuntimeFeatureStateOverrideContext::SetOriginTrialsSampleAPIBrowserReadWriteForceEnabled() {
  override_values_[mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite] = true;
}

bool RuntimeFeatureStateOverrideContext::
    SetOriginTrialsSampleAPIBrowserReadWriteEnabled(const Vector<String>& tokens) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
  override_values_[mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite] = true;
  return true;
#else
  // Origin Trial feature values should not override any sent from
  // the browser, so we only add a value if has not already been set
  // in the override_values_ map with an identical token set. Return
  // whether the override was successful.
  auto value = mojom::blink::OriginTrialFeatureState::New(true, tokens);
  if(!override_values_.contains(
      mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite) ||
     origin_trial_overrides_[
      mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite] != value) {
    // Update the state of all feature overrides in this class.
    override_values_
      [mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite] = true;
    // Add successful overrides to the list of features we sent back
    // to the browser process.
    origin_trial_overrides_[
      mojom::RuntimeFeature::kOriginTrialsSampleAPIBrowserReadWrite] = std::move(value);
    return true;
  }
  return false;
#endif
}
bool RuntimeFeatureStateOverrideContext::
    IsTestFeatureForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kTestFeature);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsTestFeatureForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kTestFeature);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetTestFeatureForceDisabled() {
  override_values_[mojom::RuntimeFeature::kTestFeature] = false;
}

void RuntimeFeatureStateOverrideContext::SetTestFeatureForceEnabled() {
  override_values_[mojom::RuntimeFeature::kTestFeature] = true;
}

bool RuntimeFeatureStateOverrideContext::
    IsTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceDisabled() const {
  auto it = override_values_.find(
      mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial);
  if (it != override_values_.end() && it->second == false)
    return true;

  return false;
}

bool RuntimeFeatureStateOverrideContext::
    IsTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceEnabled() const {
  auto it = override_values_.find(mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial);
  if(it != override_values_.end() && it->second == true)
    return true;

  return false;
}

void RuntimeFeatureStateOverrideContext::SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceDisabled() {
  override_values_[mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial] = false;
}

void RuntimeFeatureStateOverrideContext::SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceEnabled() {
  override_values_[mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial] = true;
}

bool RuntimeFeatureStateOverrideContext::
    SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(const Vector<String>& tokens) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
  override_values_[mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial] = true;
  return true;
#else
  // Origin Trial feature values should not override any sent from
  // the browser, so we only add a value if has not already been set
  // in the override_values_ map with an identical token set. Return
  // whether the override was successful.
  auto value = mojom::blink::OriginTrialFeatureState::New(true, tokens);
  if(!override_values_.contains(
      mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial) ||
     origin_trial_overrides_[
      mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial] != value) {
    // Update the state of all feature overrides in this class.
    override_values_
      [mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial] = true;
    // Add successful overrides to the list of features we sent back
    // to the browser process.
    origin_trial_overrides_[
      mojom::RuntimeFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial] = std::move(value);
    return true;
  }
  return false;
#endif
}

void RuntimeFeatureStateOverrideContext::ApplyOriginTrialOverride(
    const blink::mojom::blink::OriginTrialFeature& origin_trial_feature,
    const Vector<String>& tokens) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
  // Standalone renderer builds have no browser process or origin-trial IPC.
  // Keep local feature override state only.
  (void)tokens;
  if(origin_trial_feature == blink::mojom::blink::OriginTrialFeature::kOriginTrialsSampleAPIBrowserReadWrite) {
    SetOriginTrialsSampleAPIBrowserReadWriteEnabled(tokens);
  }
  if(origin_trial_feature == blink::mojom::blink::OriginTrialFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial) {
    SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(tokens);
  }
#else
  // Determine which of the overrideable features has been set
  // via Origin Trial.
  bool overridden = false;
  if(origin_trial_feature == blink::mojom::blink::OriginTrialFeature::kOriginTrialsSampleAPIBrowserReadWrite) {
    overridden = SetOriginTrialsSampleAPIBrowserReadWriteEnabled(tokens);
  }
  if(origin_trial_feature == blink::mojom::blink::OriginTrialFeature::kTestFeatureForBrowserProcessReadWriteAccessOriginTrial) {
    overridden = SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(tokens);
  }
  // Send the newly overriden values to the browser via IPC.
  if(overridden){
    // We must convert from std:: types to WTF types.
    // TODO(https://crbug.com/1377000): make origin_trial_overrides_ a
    // WTF type in a follow-up CL.
    HashMap<mojom::blink::RuntimeFeature,
            mojom::blink::OriginTrialFeatureStatePtr>
        blink_overrides;
    for (auto& o : origin_trial_overrides_){
      blink_overrides.insert(o.first, std::move(o.second));
    }
    // Feature overrides and origin trial information should only be
    // sent to the browser process if the corresponding base::Feature
    // is enabled.
    GetOrBindOriginTrialStateHost()->ApplyFeatureDiffForOriginTrial(
        std::move(blink_overrides));
    // TODO(https://crbug.com/1377000): when we convert to WTF types,
    // we use std::move, so we have to do some cleanup.
    origin_trial_overrides_.clear();
  }
#endif
}

void RuntimeFeatureStateOverrideContext::EnablePersistentTrial(
      const String& raw_token,
      const Vector<scoped_refptr<const blink::SecurityOrigin>>&
          script_origins) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
    (void)raw_token;
    (void)script_origins;
#else
    GetOrBindOriginTrialStateHost()->EnablePersistentTrial(
        raw_token, script_origins);
#endif
  }

#if !defined(STANDALONE_RENDERER_GN_PROBE)
mojom::blink::OriginTrialStateHost*
RuntimeFeatureStateOverrideContext::GetOrBindOriginTrialStateHost(){
  // It's possible that the prior interface we bound is no longer available
  // in which case we should reset the connection and re-bind a new one.
  if (origin_trial_state_host_remote_.is_bound() &&
      !origin_trial_state_host_remote_.is_connected()) {
    origin_trial_state_host_remote_.reset();
  }
  // TODO(https://crbug.com/1410817): add support for workers/non-frames that
  // are enabling origin trials to send their information to the browser too.
  if (!origin_trial_state_host_remote_.is_bound()) {
      CHECK(send_runtime_features_to_browser_);
      binding_context_->GetBrowserInterfaceBroker().GetInterface(
          origin_trial_state_host_remote_.BindNewPipeAndPassReceiver(
              binding_context_->GetTaskRunner(TaskType::kInternalDefault)));
    }
  return origin_trial_state_host_remote_.get();
}
#endif

void RuntimeFeatureStateOverrideContext::Trace(Visitor* visitor) const{
  visitor->Trace(binding_context_);
  visitor->Trace(use_counter_);
#if !defined(STANDALONE_RENDERER_GN_PROBE)
  visitor->Trace(origin_trial_state_host_remote_);
#endif
}

}  // namespace blink
