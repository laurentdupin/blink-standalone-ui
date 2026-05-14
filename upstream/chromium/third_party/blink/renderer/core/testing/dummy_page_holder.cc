/*
 * Copyright (c) 2013, Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *     * Neither the name of Google Inc. nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "third_party/blink/renderer/core/testing/dummy_page_holder.h"

#include <cstdio>
#include <memory>

#include "base/memory/ptr_util.h"
#include "services/metrics/public/cpp/ukm_source_id.h"
#include "third_party/blink/public/common/storage_key/storage_key.h"
#include "third_party/blink/public/common/tokens/tokens.h"
#include "third_party/blink/public/mojom/frame/policy_container.mojom-blink.h"
#include "third_party/blink/renderer/core/core_initializer.h"
#include "third_party/blink/renderer/core/frame/local_dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_view.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/frame/visual_viewport.h"
#include "third_party/blink/renderer/core/loader/empty_clients.h"
#include "third_party/blink/renderer/platform/heap/garbage_collected.h"
#include "third_party/blink/renderer/platform/scheduler/public/agent_group_scheduler.h"
#include "third_party/blink/renderer/platform/scheduler/public/main_thread.h"
#include "third_party/blink/renderer/platform/scheduler/public/main_thread_scheduler.h"
#include "third_party/blink/renderer/platform/testing/unit_test_helpers.h"
#include "third_party/blink/renderer/platform/testing/url_loader_mock_factory.h"

namespace blink {

namespace {

void TraceStandaloneDummyPageHolderStage(const char* stage) {
}

class DummyLocalFrameClient : public EmptyLocalFrameClient {
 public:
  DummyLocalFrameClient() = default;

 private:
  std::unique_ptr<URLLoader> CreateURLLoaderForTesting() override {
    return URLLoaderMockFactory::GetSingletonInstance()->CreateURLLoader();
  }
};

}  // namespace

// static
std::unique_ptr<DummyPageHolder> DummyPageHolder::CreateAndCommitNavigation(
    const KURL& url,
    const gfx::Size& initial_view_size,
    ChromeClient* chrome_client,
    LocalFrameClient* local_frame_client,
    base::OnceCallback<void(Settings&)> setting_overrider,
    const base::TickClock* clock) {
  std::unique_ptr<DummyPageHolder> holder = std::make_unique<DummyPageHolder>(
      initial_view_size, chrome_client, local_frame_client,
      std::move(setting_overrider), clock);
  if (url.IsValid()) {
    holder->GetFrame().Loader().CommitNavigation(
        WebNavigationParams::CreateWithEmptyHTMLForTesting(url),
        /*extra_data=*/nullptr);
    blink::test::RunPendingTasks();
  }
  return holder;
}

DummyPageHolder::DummyPageHolder(
    const gfx::Size& initial_view_size,
    ChromeClient* chrome_client,
    LocalFrameClient* local_frame_client,
    base::OnceCallback<void(Settings&)> setting_overrider,
    const base::TickClock* clock)
    : enable_mock_scrollbars_(true),
      agent_group_scheduler_(Thread::MainThread()
                                 ->Scheduler()
                                 ->ToMainThreadScheduler()
                                 ->CreateAgentGroupScheduler()) {
  TraceStandaloneDummyPageHolderStage("after initializer list");
  if (!chrome_client)
    chrome_client = MakeGarbageCollected<EmptyChromeClient>();
  TraceStandaloneDummyPageHolderStage("after chrome client");
  TraceStandaloneDummyPageHolderStage("before browsing context token");
  base::UnguessableToken browsing_context_group_token =
      base::UnguessableToken::Create();
  TraceStandaloneDummyPageHolderStage("after browsing context token");
  TraceStandaloneDummyPageHolderStage("before Page::CreateOrdinary");
  page_ = Page::CreateOrdinary(*chrome_client, /*opener=*/nullptr,
                               *agent_group_scheduler_,
                               browsing_context_group_token,
                               /*color_provider_colors=*/nullptr);
  TraceStandaloneDummyPageHolderStage("after Page::CreateOrdinary");
  Settings& settings = page_->GetSettings();
  settings.SetDefaultFontSize(16);
  settings.SetDefaultFixedFontSize(13);
  if (setting_overrider)
    std::move(setting_overrider).Run(settings);
  TraceStandaloneDummyPageHolderStage("after settings");

  // Color providers are required for painting, so we ensure they are not null
  // even in unittests.
  page_->UpdateColorProvidersForTest();
  TraceStandaloneDummyPageHolderStage("after color providers");

  // DummyPageHolder doesn't provide a browser interface, so code caches cannot
  // be fetched. If testing for code caches provide a mock code cache host.
  DocumentLoader::DisableCodeCacheForTesting();
  TraceStandaloneDummyPageHolderStage("after DisableCodeCacheForTesting");
  local_frame_client_ = local_frame_client;
  if (!local_frame_client_)
    local_frame_client_ = MakeGarbageCollected<DummyLocalFrameClient>();
  TraceStandaloneDummyPageHolderStage("after local frame client");

  // Create new WindowAgentFactory as this page will be isolated from others.
  TraceStandaloneDummyPageHolderStage("before LocalFrame token");
  LocalFrameToken frame_token;
  TraceStandaloneDummyPageHolderStage("after LocalFrame token");
  TraceStandaloneDummyPageHolderStage("before LocalFrame allocation");
  frame_ = MakeGarbageCollected<LocalFrame>(
      local_frame_client_.Get(), *page_,
      /* FrameOwner* */ nullptr, /* Frame* parent */ nullptr,
      /* Frame* previous_sibling */ nullptr,
      FrameInsertType::kInsertInConstructor, frame_token,
      /* WindowAgentFactory* */ nullptr,
      /* InterfaceRegistry* */ nullptr,
      /* BrowserInterfaceBroker */ mojo::NullRemote(), clock);
  TraceStandaloneDummyPageHolderStage("after LocalFrame");
  frame_->SetView(
      MakeGarbageCollected<LocalFrameView>(*frame_, initial_view_size));
  TraceStandaloneDummyPageHolderStage("after LocalFrameView");
  TraceStandaloneDummyPageHolderStage("before visual viewport");
  page_->GetVisualViewport().SetSize(initial_view_size);
  TraceStandaloneDummyPageHolderStage("after visual viewport");
  frame_->Init(/*opener=*/nullptr, DocumentToken(),
               /*policy_container=*/nullptr, StorageKey(),
               /*document_ukm_source_id=*/ukm::kInvalidSourceId,
               /*creator_base_url=*/KURL());
  TraceStandaloneDummyPageHolderStage("after frame Init");

  TraceStandaloneDummyPageHolderStage("before ProvideModulesToPage");
  CoreInitializer::GetInstance().ProvideModulesToPage(*page_, std::string());
  TraceStandaloneDummyPageHolderStage("after ProvideModulesToPage");
}

DummyPageHolder::~DummyPageHolder() {
  page_->WillBeDestroyed();
  page_.Clear();
  frame_.Clear();
}

Page& DummyPageHolder::GetPage() const {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
  CHECK(IsMainThread());
#endif
  return *page_;
}

LocalFrame& DummyPageHolder::GetFrame() const {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
  CHECK(IsMainThread());
#endif
  DCHECK(frame_);
  return *frame_;
}

LocalFrameView& DummyPageHolder::GetFrameView() const {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
  CHECK(IsMainThread());
#endif
  return *frame_->View();
}

Document& DummyPageHolder::GetDocument() const {
#if !defined(HTML_CSS_RENDERER_STANDALONE)
  CHECK(IsMainThread());
#endif
  return *frame_->DomWindow()->document();
}

}  // namespace blink
