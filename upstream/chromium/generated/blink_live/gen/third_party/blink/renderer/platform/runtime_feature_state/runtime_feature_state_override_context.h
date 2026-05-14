// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/runtime_feature_state_override_context.h.tmpl
// and input files:
//   ../../third_party/blink/renderer/platform/runtime_enabled_features.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_FEATURE_STATE_RUNTIME_FEATURE_STATE_OVERRIDE_CONTEXT_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_FEATURE_STATE_RUNTIME_FEATURE_STATE_OVERRIDE_CONTEXT_H_

#include "base/containers/flat_map.h"
#if !defined(STANDALONE_RENDERER_GN_PROBE)
#include "mojo/public/cpp/bindings/remote.h"
#endif
#include "third_party/blink/public/mojom/origin_trials/origin_trial_feature.mojom-blink-forward.h"
#if !defined(STANDALONE_RENDERER_GN_PROBE)
#include "third_party/blink/public/mojom/origin_trials/origin_trial_state_host.mojom-blink.h"
#endif
#include "third_party/blink/public/mojom/runtime_feature_state/runtime_feature.mojom-shared.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/instrumentation/use_counter.h"
#if !defined(STANDALONE_RENDERER_GN_PROBE)
#include "third_party/blink/renderer/platform/mojo/heap_mojo_remote.h"
#endif
#include "third_party/blink/renderer/platform/mojo/mojo_binding_context.h"
#include "third_party/blink/renderer/platform/platform_export.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace blink {

class SecurityOrigin;

// This class coalesces browser side runtime feature state into a final value
// which is then used to determine whether a given Blink runtime feature is
// enabled.
//
// Use `Is*ForceEnabled()` or `Is*ForceDisabled()` to query the final value.
class PLATFORM_EXPORT RuntimeFeatureStateOverrideContext
    : public GarbageCollected<RuntimeFeatureStateOverrideContext> {
 public:
  RuntimeFeatureStateOverrideContext(MojoBindingContext* binding_context,
                                   UseCounter* use_counter,
                                   bool send_runtime_features_to_browser)
    : binding_context_(binding_context),
      use_counter_(use_counter),
#if !defined(STANDALONE_RENDERER_GN_PROBE)
      origin_trial_state_host_remote_(binding_context),
#endif
      send_runtime_features_to_browser_(send_runtime_features_to_browser) {
  DCHECK(binding_context);
  DCHECK(use_counter);
  override_values_.reserve(8);
#if !defined(STANDALONE_RENDERER_GN_PROBE)
  origin_trial_overrides_.reserve(8);
#endif
}

  void ApplyOverrideValuesFromParams(
      const base::flat_map<mojom::RuntimeFeature, bool>&
          values_from_params);

  void ApplyOriginTrialOverride(
    const blink::mojom::blink::OriginTrialFeature& origin_trial_feature,
    const Vector<String>& tokens);

  bool IsBlinkExtensionChromeOSForceDisabled() const;

  bool IsBlinkExtensionChromeOSForceEnabled() const;

  void SetBlinkExtensionChromeOSForceDisabled();

  void SetBlinkExtensionChromeOSForceEnabled();

  bool IsBlinkExtensionChromeOSIsolatedWebAppSetShapeForceDisabled() const;

  bool IsBlinkExtensionChromeOSIsolatedWebAppSetShapeForceEnabled() const;

  void SetBlinkExtensionChromeOSIsolatedWebAppSetShapeForceDisabled();

  void SetBlinkExtensionChromeOSIsolatedWebAppSetShapeForceEnabled();

  bool IsBlinkExtensionChromeOSKioskForceDisabled() const;

  bool IsBlinkExtensionChromeOSKioskForceEnabled() const;

  void SetBlinkExtensionChromeOSKioskForceDisabled();

  void SetBlinkExtensionChromeOSKioskForceEnabled();

  bool IsDirectSocketsForceDisabled() const;

  bool IsDirectSocketsForceEnabled() const;

  void SetDirectSocketsForceDisabled();

  void SetDirectSocketsForceEnabled();

  bool IsGetDisplayMediaWindowAudioCaptureForceDisabled() const;

  bool IsGetDisplayMediaWindowAudioCaptureForceEnabled() const;

  void SetGetDisplayMediaWindowAudioCaptureForceDisabled();

  void SetGetDisplayMediaWindowAudioCaptureForceEnabled();

  bool IsOriginTrialsSampleAPIBrowserReadWriteForceDisabled() const;

  bool IsOriginTrialsSampleAPIBrowserReadWriteForceEnabled() const;

  void SetOriginTrialsSampleAPIBrowserReadWriteForceDisabled();

  void SetOriginTrialsSampleAPIBrowserReadWriteForceEnabled();

  bool SetOriginTrialsSampleAPIBrowserReadWriteEnabled(const Vector<String>& tokens);
  bool IsTestFeatureForceDisabled() const;

  bool IsTestFeatureForceEnabled() const;

  void SetTestFeatureForceDisabled();

  void SetTestFeatureForceEnabled();

  bool IsTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceDisabled() const;

  bool IsTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceEnabled() const;

  void SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceDisabled();

  void SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialForceEnabled();

  bool SetTestFeatureForBrowserProcessReadWriteAccessOriginTrialEnabled(const Vector<String>& tokens);

  void EnablePersistentTrial(
      const String& raw_token,
      const Vector<scoped_refptr<const blink::SecurityOrigin>>&
          script_origins);

  const base::flat_map<mojom::RuntimeFeature, bool>&
  GetOverrideValuesForTesting() const {
    return override_values_;
  }

  void Trace(Visitor*) const;

 private:
#if !defined(STANDALONE_RENDERER_GN_PROBE)
  mojom::blink::OriginTrialStateHost* GetOrBindOriginTrialStateHost();
#endif

  base::flat_map<mojom::RuntimeFeature, bool> override_values_;
#if !defined(STANDALONE_RENDERER_GN_PROBE)
  base::flat_map<mojom::RuntimeFeature,
                 mojom::blink::OriginTrialFeatureStatePtr>
      origin_trial_overrides_;
#endif
  Member<MojoBindingContext> binding_context_;
  Member<UseCounter> use_counter_;
#if !defined(STANDALONE_RENDERER_GN_PROBE)
  blink::HeapMojoRemote<mojom::blink::OriginTrialStateHost>
      origin_trial_state_host_remote_;
#endif

  // TODO(https://crbug.com/1410817): add support for workers/non-frames that
  // are enabling origin trials to send their information to the browser too.
  bool send_runtime_features_to_browser_ = false;
};

}  // namespace blink

#endif // THIRD_PARTY_BLINK_RENDERER_PLATFORM_RUNTIME_FEATURE_STATE_RUNTIME_FEATURE_STATE_OVERRIDE_CONTEXT_H_
