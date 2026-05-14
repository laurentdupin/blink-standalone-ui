// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/loader/prefetched_signed_exchange_manager.h"
#include "third_party/blink/renderer/core/loader/subresource_filter.h"
#include "third_party/blink/renderer/core/navigation_api/navigate_event_dispatch_params.h"
#include "third_party/blink/renderer/platform/mhtml/mhtml_archive.h"

#include "third_party/blink/renderer/bindings/core/v8/serialization/serialized_script_value.h"
#include "third_party/blink/renderer/core/loader/alternate_signed_exchange_resource_info.h"

namespace blink {

PrefetchedSignedExchangeManager* PrefetchedSignedExchangeManager::MaybeCreate(
    LocalFrame*,
    const String&,
    const String&,
    std::vector<std::unique_ptr<WebNavigationParams::PrefetchedSignedExchange>>) {
  return nullptr;
}

PrefetchedSignedExchangeManager::PrefetchedSignedExchangeManager(
    LocalFrame* frame,
    std::unique_ptr<AlternateSignedExchangeResourceInfo> alternative_resources,
    HashMap<KURL, std::unique_ptr<WebNavigationParams::PrefetchedSignedExchange>>
        prefetched_exchanges_map)
    : frame_(frame),
      alternative_resources_(std::move(alternative_resources)),
      prefetched_exchanges_map_(std::move(prefetched_exchanges_map)) {}

PrefetchedSignedExchangeManager::~PrefetchedSignedExchangeManager() = default;

void PrefetchedSignedExchangeManager::Trace(Visitor* visitor) const {
  (void)visitor;
}

std::unique_ptr<URLLoader> PrefetchedSignedExchangeManager::MaybeCreateURLLoader(
    const network::ResourceRequest&,
    base::OnceCallback<Vector<std::unique_ptr<URLLoaderThrottle>>(void)>) {
  return nullptr;
}

void PrefetchedSignedExchangeManager::StartPrefetchedLinkHeaderPreloads() {}

SubresourceFilter::SubresourceFilter(
    ExecutionContext* execution_context,
    std::unique_ptr<WebDocumentSubresourceFilter> subresource_filter)
    : execution_context_(execution_context),
      subresource_filter_(std::move(subresource_filter)) {}

SubresourceFilter::~SubresourceFilter() = default;

bool SubresourceFilter::AllowLoad(const KURL&,
                                  network::mojom::RequestDestination,
                                  ReportingDisposition) {
  return true;
}

bool SubresourceFilter::AllowWebSocketConnection(const KURL&) {
  return true;
}

bool SubresourceFilter::AllowWebTransportConnection(const KURL&) {
  return true;
}

bool SubresourceFilter::IsAdResource(const KURL&,
                                     network::mojom::RequestDestination,
                                     subresource_filter::ScopedRule*) {
  return false;
}

void SubresourceFilter::Trace(Visitor* visitor) const {
  (void)visitor;
}

NavigateEventDispatchParams::NavigateEventDispatchParams(
    const KURL& input_url,
    NavigateEventType input_event_type,
    WebFrameLoadType input_frame_load_type)
    : url(input_url),
      event_type(input_event_type),
      frame_load_type(input_frame_load_type),
      should_skip_screenshot(false) {}

NavigateEventDispatchParams::~NavigateEventDispatchParams() = default;

void NavigateEventDispatchParams::Trace(Visitor* visitor) const {
  (void)visitor;
}

MHTMLArchive* MHTMLArchive::Create(const KURL&, scoped_refptr<const SharedBuffer>) {
  return nullptr;
}

MHTMLArchive::MHTMLArchive() = default;

void MHTMLArchive::GenerateMHTMLHeader(const String&,
                                       const KURL&,
                                       const String&,
                                       const String&,
                                       base::Time,
                                       Vector<char>&) {}

void MHTMLArchive::GenerateMHTMLPart(const String&,
                                     const String&,
                                     EncodingPolicy,
                                     const SerializedResource&,
                                     Vector<char>&) {}

void MHTMLArchive::GenerateMHTMLFooterForTesting(const String&, Vector<char>&) {}

ArchiveResource* MHTMLArchive::SubresourceForURL(const KURL&) const {
  return nullptr;
}

String MHTMLArchive::GetCacheIdentifier() const {
  return String();
}

void MHTMLArchive::Trace(Visitor* visitor) const {
  (void)visitor;
}

}  // namespace blink
