// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Keep only the resource-priority value helper and scheduler weak-pointer
// accessor needed by the local image/canvas fetch path. The rest of
// resource_request_utils.cc stays out because it owns CSP/referrer/network
// request preparation.

#include "third_party/blink/public/mojom/fetch/fetch_api_request.mojom-blink.h"
#include "third_party/blink/public/platform/web_url_error.h"
#include "third_party/blink/public/platform/web_url_response.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_client_settings_object.h"
#include "third_party/blink/renderer/platform/loader/fetch/raw_resource.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher_properties.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_load_scheduler.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_loader.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_request_utils.h"
#include "third_party/blink/renderer/platform/loader/fetch/stale_revalidation_resource_client.h"
#include "third_party/blink/renderer/platform/loader/fetch/subresource_web_bundle_list.h"
#include "third_party/blink/renderer/platform/scheduler/public/frame_or_worker_scheduler.h"

namespace blink {

void SetReferrer(ResourceRequest&,
                 const FetchClientSettingsObject&) {}

ResourceLoadPriority AdjustPriorityWithPriorityHintAndRenderBlocking(
    ResourceLoadPriority priority,
    ResourceType type,
    mojom::blink::FetchPriorityHint fetch_priority_hint,
    RenderBlockingBehavior render_blocking_behavior) {
  ResourceLoadPriority new_priority = priority;

  switch (fetch_priority_hint) {
    case mojom::blink::FetchPriorityHint::kAuto:
      break;
    case mojom::blink::FetchPriorityHint::kHigh:
      // Boost priority of any request type that supports priority hints.
      if (new_priority < ResourceLoadPriority::kHigh) {
        new_priority = ResourceLoadPriority::kHigh;
      }
      CHECK_LE(priority, new_priority);
      break;
    case mojom::blink::FetchPriorityHint::kLow:
      // Demote priority of any request type that supports priority hints.
      // Most content types go to kLow. The one exception is early
      // render-blocking CSS which defaults to the highest priority but
      // can be lowered to match the "high" priority of everything else
      // to allow for ordering if necessary without causing too much of a
      // foot-gun.
      if (type == ResourceType::kCSSStyleSheet &&
          new_priority == ResourceLoadPriority::kVeryHigh) {
        new_priority = ResourceLoadPriority::kHigh;
      } else if (new_priority > ResourceLoadPriority::kLow) {
        new_priority = ResourceLoadPriority::kLow;
      }
      CHECK_LE(new_priority, priority);
      break;
  }

  // Render-blocking is a signal that the resource is important, so we bump it
  // to at least kHigh.
  if (render_blocking_behavior == RenderBlockingBehavior::kBlocking &&
      new_priority < ResourceLoadPriority::kHigh) {
    new_priority = ResourceLoadPriority::kHigh;
  }

  return new_priority;
}

bool ShouldLoadIncremental(ResourceType type) {
  switch (type) {
    case ResourceType::kCSSStyleSheet:
    case ResourceType::kScript:
    case ResourceType::kFont:
    case ResourceType::kXSLStyleSheet:
    case ResourceType::kManifest:
      return false;
    case ResourceType::kImage:
    case ResourceType::kRaw:
    case ResourceType::kSVGDocument:
    case ResourceType::kLinkPrefetch:
    case ResourceType::kTextTrack:
    case ResourceType::kAudio:
    case ResourceType::kVideo:
    case ResourceType::kSpeculationRules:
    case ResourceType::kMock:
    case ResourceType::kDictionary:
      return true;
  }
  NOTREACHED();
}

std::optional<ResourceRequestBlockedReason> PrepareResourceRequestForCacheAccess(
    ResourceType,
    const FetchClientSettingsObject&,
    const KURL&,
    ResourceRequestContext&,
    FetchContext&,
    FetchParameters&) {
  return std::nullopt;
}

void UpgradeResourceRequestForLoader(ResourceType,
                                     FetchParameters&,
                                     FetchContext&,
                                     ResourceRequestContext&,
                                     WebScopedVirtualTimePauser&) {}

base::WeakPtr<FrameOrWorkerScheduler> FrameOrWorkerScheduler::GetWeakPtr() {
  return weak_factory_.GetWeakPtr();
}

void ResourceLoadScheduler::Shutdown() {}

ResourceLoadScheduler::ResourceLoadScheduler(
    ThrottlingPolicy initial_throttling_policy,
    ThrottleOptionOverride throttle_option_override,
    const DetachableResourceFetcherProperties& properties,
    FrameOrWorkerScheduler*,
    DetachableConsoleLogger& console_logger,
    LoadingBehaviorObserver* loading_behavior_observer)
    : resource_fetcher_properties_(&properties),
      policy_(initial_throttling_policy),
      outstanding_limit_for_throttled_frame_scheduler_(kOutstandingUnlimited),
      console_logger_(&console_logger),
      clock_(nullptr),
      throttle_option_override_(throttle_option_override),
      loading_behavior_observer_(loading_behavior_observer) {}

ResourceLoadScheduler::~ResourceLoadScheduler() = default;

void ResourceLoadScheduler::Trace(Visitor*) const {}

void DetachableResourceFetcherProperties::Detach() {}

SubresourceWebBundle* SubresourceWebBundleList::GetMatchingBundle(
    const KURL&) const {
  return nullptr;
}

void SubresourceWebBundleList::Trace(Visitor*) const {}

ResourceLoader::ResourceLoader(ResourceFetcher* fetcher,
                               ResourceLoadScheduler* scheduler,
                               Resource* resource,
                               ContextLifecycleNotifier* context,
                               ResourceRequestBody request_body,
                               uint32_t inflight_keepalive_bytes)
    : scheduler_client_id_(ResourceLoadScheduler::kInvalidClientId),
      fetcher_(fetcher),
      scheduler_(scheduler),
      resource_(resource),
      request_body_(std::move(request_body)),
      inflight_keepalive_bytes_(inflight_keepalive_bytes),
      is_cache_aware_loading_activated_(false),
      progress_receiver_(this, context),
      cancel_timer_(fetcher ? fetcher->GetUnfreezableTaskRunner() : nullptr,
                    this,
                    &ResourceLoader::CancelTimerFired) {
  if (resource_) {
    resource_->SetLoader(this);
  }
}

ResourceLoader::~ResourceLoader() = default;

void ResourceLoader::Dispose() {}

void ResourceLoader::Start() {}

void ResourceLoader::Run() {}

void ResourceLoader::Cancel() {}

void ResourceLoader::SetDefersLoading(LoaderFreezeMode mode) {
  freeze_mode_ = mode;
}

void ResourceLoader::CancelIfWebBundleTokenMatches(
    const base::UnguessableToken&) {}

bool ResourceLoader::ShouldBeKeptAliveWhenDetached() const {
  return false;
}

void ResourceLoader::CancelTimerFired(TimerBase*) {}

bool ResourceLoader::WillFollowRedirect(
    const WebURL&,
    const net::SiteForCookies&,
    const WebString&,
    network::mojom::ReferrerPolicy,
    const WebString&,
    const WebURLResponse&,
    bool& has_devtools_request_id,
    std::vector<std::string>*,
    net::HttpRequestHeaders&,
    bool) {
  has_devtools_request_id = false;
  return false;
}

void ResourceLoader::DidSendData(uint64_t, uint64_t) {}

void ResourceLoader::DidReceiveResponse(
    const WebURLResponse&,
    std::variant<mojo::ScopedDataPipeConsumerHandle, SegmentedBuffer>,
    std::optional<mojo_base::BigBuffer>) {}

void ResourceLoader::DidReceiveDataForTesting(base::span<const char>) {}

void ResourceLoader::DidReceiveTransferSizeUpdate(int) {}

void ResourceLoader::DidFail(const WebURLError&,
                             base::TimeTicks,
                             int64_t,
                             uint64_t,
                             int64_t) {}

void ResourceLoader::CountFeature(blink::mojom::WebFeature) {}

void ResourceLoader::DidReceiveData(base::span<const char>) {}

void ResourceLoader::DidReceiveDecodedData(
    const String&,
    std::unique_ptr<SecureStringDigest>) {}

void ResourceLoader::DidFinishLoadingBody() {}

void ResourceLoader::DidFailLoadingBody() {}

void ResourceLoader::DidCancelLoadingBody() {}

void ResourceLoader::OnProgress(uint64_t) {}

StaleRevalidationResourceClient::StaleRevalidationResourceClient(Resource*) {}

StaleRevalidationResourceClient::~StaleRevalidationResourceClient() = default;

void StaleRevalidationResourceClient::NotifyFinished(Resource*) {
  ClearResource();
}

void StaleRevalidationResourceClient::Trace(Visitor* visitor) const {
  RawResourceClient::Trace(visitor);
}

String StaleRevalidationResourceClient::DebugName() const {
  return "Phase1StaleRevalidationUnsupported";
}

}  // namespace blink
