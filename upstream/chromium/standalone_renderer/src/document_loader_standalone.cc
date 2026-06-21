// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Standalone renderer cut: DocumentLoader is a browser/network/navigation
// boundary. The live Blink island keeps Document and frame lifecycle code, but
// does not link Chromium's full loader implementation.

#include "third_party/blink/renderer/core/loader/document_loader.h"

#include "third_party/blink/renderer/core/loader/document_load_timing.h"

namespace blink {

const AtomicString& DocumentLoader::MimeType() const {
  return response_.MimeType();
}

const KURL& DocumentLoader::Url() const {
  return url_;
}

const AtomicString& DocumentLoader::GetReferrer() const {
  return referrer_;
}

void DocumentLoader::DispatchLinkHeaderPreloads(
    const ViewportDescription*,
    PreloadHelper::LoadLinksFromHeaderMode) {}

void DocumentLoader::DispatchLcppFontPreloads(
    const ViewportDescription*,
    PreloadHelper::LoadLinksFromHeaderMode) {}

void DocumentLoader::DidObserveLoadingBehavior(LoadingBehaviorFlag) {}

void DocumentLoader::DidOpenDocumentInputStream(const KURL& url) {
  url_ = url;
}

PrefetchedSignedExchangeManager*
DocumentLoader::GetPrefetchedSignedExchangeManager() const {
  return nullptr;
}

void DocumentLoader::NotifyPrerenderingDocumentActivated(
    const mojom::blink::PrerenderPageActivationParams&) {}

CodeCacheHost* DocumentLoader::GetCodeCacheHost() {
  return nullptr;
}

void DocumentLoader::DisableCodeCacheForTesting() {}

const mojom::RendererContentSettingsPtr& DocumentLoader::GetContentSettings() {
  return content_settings_;
}

void DocumentLoader::ReportTotalTakenTimeToUpdateSubresourceLoadMetrics() {}

DocumentLoadTiming::DocumentLoadTiming(DocumentLoader& document_loader)
    : document_loader_(document_loader),
      document_load_timing_values_(
          MakeGarbageCollected<DocumentLoadTimingValues>()) {}

void DocumentLoadTiming::SetNavigationStart(base::TimeTicks value) {
  reference_monotonic_time_ = value;
  navigation_start_ = value;
}

void DocumentLoadTiming::SetInputStart(base::TimeTicks value) {
  input_start_ = value;
}

void DocumentLoadTiming::SetRedirectStart(base::TimeTicks value) {
  document_load_timing_values_->redirect_start = value;
}

void DocumentLoadTiming::SetRedirectEnd(base::TimeTicks value) {
  document_load_timing_values_->redirect_end = value;
}

void DocumentLoadTiming::SetFetchStart(base::TimeTicks value) {
  document_load_timing_values_->fetch_start = value;
}

void DocumentLoadTiming::SetCriticalCHRestart(base::TimeTicks value) {
  document_load_timing_values_->critical_ch_restart = value;
}

void DocumentLoadTiming::Trace(Visitor* visitor) const {
  visitor->Trace(document_load_timing_values_);
  visitor->Trace(document_loader_);
}

}  // namespace blink
