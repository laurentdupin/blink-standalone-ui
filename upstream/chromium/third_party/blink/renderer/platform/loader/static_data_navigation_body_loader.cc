// Copyright 2019 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/loader/static_data_navigation_body_loader.h"

#include "standalone_renderer/include/html_css_renderer/standalone_process.h"

namespace blink {

namespace {

void TraceStandaloneStaticBodyLoaderStage(const char* stage) {
#if defined(HTML_CSS_RENDERER_STANDALONE)
  html_css_renderer::SetStandaloneCrashBreadcrumb(stage);
#endif
}

}  // namespace

// static
std::unique_ptr<StaticDataNavigationBodyLoader>
StaticDataNavigationBodyLoader::CreateWithData(
    scoped_refptr<SharedBuffer> data) {
  auto body_loader = std::make_unique<StaticDataNavigationBodyLoader>();
  body_loader->data_ = std::move(data);
  if (!body_loader->data_) {
    body_loader->data_ = SharedBuffer::Create();
  }
  body_loader->Finish();
  return body_loader;
}

StaticDataNavigationBodyLoader::StaticDataNavigationBodyLoader() = default;

StaticDataNavigationBodyLoader::~StaticDataNavigationBodyLoader() = default;

void StaticDataNavigationBodyLoader::Write(base::span<const char> data) {
  DCHECK(!received_all_data_);
  if (!data_) {
    data_ = SharedBuffer::Create(data);
  } else {
    data_->Append(data);
  }
  Continue();
}

void StaticDataNavigationBodyLoader::Finish() {
  DCHECK(!received_all_data_);
  received_all_data_ = true;
  Continue();
}

void StaticDataNavigationBodyLoader::SetDefersLoading(LoaderFreezeMode mode) {
  freeze_mode_ = mode;
  Continue();
}

void StaticDataNavigationBodyLoader::StartLoadingBody(
    WebNavigationBodyLoader::Client* client) {
  DCHECK(!is_in_continue_);
  TraceStandaloneStaticBodyLoaderStage("StaticBodyLoader StartLoadingBody");
  client_ = client;
  Continue();
}

void StaticDataNavigationBodyLoader::Continue() {
  TraceStandaloneStaticBodyLoaderStage("StaticBodyLoader Continue entry");
  if (freeze_mode_ != LoaderFreezeMode::kNone || !client_ || is_in_continue_)
    return;

  // We don't want reentrancy in this method -
  // protect with a boolean. Cannot use AutoReset
  // because |this| can be deleted before reset.
  is_in_continue_ = true;
  base::WeakPtr<StaticDataNavigationBodyLoader> weak_self =
      weak_factory_.GetWeakPtr();

  if (!sent_all_data_) {
    while (data_ && data_->size()) {
      total_encoded_data_length_ += data_->size();

      // Cleanup |data_| before dispatching, so that
      // we can reentrantly append some data again.
      scoped_refptr<SharedBuffer> data = std::move(data_);

      for (const auto& span : *data) {
        TraceStandaloneStaticBodyLoaderStage(
            "StaticBodyLoader before BodyDataReceived");
        client_->BodyDataReceived(span);
        TraceStandaloneStaticBodyLoaderStage(
            "StaticBodyLoader after BodyDataReceived");
        // |this| can be destroyed from BodyDataReceived.
        if (!weak_self)
          return;
      }

      if (freeze_mode_ != LoaderFreezeMode::kNone) {
        is_in_continue_ = false;
        return;
      }
    }
    if (received_all_data_)
      sent_all_data_ = true;
  }

  if (sent_all_data_) {
    // Clear |client_| to avoid any extra notifications from reentrancy.
    WebNavigationBodyLoader::Client* client = client_;
    client_ = nullptr;
    TraceStandaloneStaticBodyLoaderStage(
        "StaticBodyLoader before BodyLoadingFinished");
    client->BodyLoadingFinished(
        base::TimeTicks::Now(), total_encoded_data_length_,
        total_encoded_data_length_, total_encoded_data_length_, std::nullopt);
    TraceStandaloneStaticBodyLoaderStage(
        "StaticBodyLoader after BodyLoadingFinished");
    // |this| can be destroyed from BodyLoadingFinished.
    if (!weak_self)
      return;
  }

  is_in_continue_ = false;
}

}  // namespace blink
