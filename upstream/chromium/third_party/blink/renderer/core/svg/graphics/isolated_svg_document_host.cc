/*
 * Copyright (C) 2006 Eric Seidel <eric@webkit.org>
 * Copyright (C) 2008, 2009 Apple Inc. All rights reserved.
 * Copyright (C) Research In Motion Limited 2011. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "third_party/blink/renderer/core/svg/graphics/isolated_svg_document_host.h"

#include "base/notreached.h"
#include "base/task/single_thread_task_runner.h"
#include "base/trace_event/trace_event.h"
#include "services/network/public/cpp/single_request_url_loader_factory.h"
#include "third_party/blink/public/common/tokens/tokens.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/dom/events/event_dispatch_forbidden_scope.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/core/frame/local_frame_client.h"
#include "third_party/blink/renderer/core/frame/settings.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"
#include "third_party/blink/renderer/core/page/page.h"
#include "third_party/blink/renderer/core/svg/graphics/svg_image_chrome_client.h"
#include "third_party/blink/renderer/core/svg/svg_svg_element.h"
#include "third_party/blink/renderer/platform/instrumentation/histogram.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"

#include <cstdio>
#include <cstdlib>

namespace blink {

#if defined(HTML_CSS_RENDERER_STANDALONE)
IsolatedSVGDocumentHost::LoadStateForStandaloneTrace
IsolatedSVGDocumentHost::LoadStateForStandaloneTraceForDiagnostics() const {
  switch (load_state_) {
    case kNotStarted:
      return LoadStateForStandaloneTrace::kNotStarted;
    case kPending:
      return LoadStateForStandaloneTrace::kPending;
    case kWaitingForAsyncLoadCompletion:
      return LoadStateForStandaloneTrace::kWaitingForAsyncLoadCompletion;
    case kCompleted:
      return LoadStateForStandaloneTrace::kCompleted;
  }
  return LoadStateForStandaloneTrace::kNotStarted;
}
#endif

namespace {

#if defined(HTML_CSS_RENDERER_STANDALONE)
bool TraceStandaloneSvgImageLoadStages() {
  static const bool enabled =
      std::getenv("HTML_CSS_RENDERER_TRACE_IMAGE_PAINT") != nullptr;
  return enabled;
}

const char* StandaloneSvgLoadStateName(
    IsolatedSVGDocumentHost::LoadStateForStandaloneTrace state) {
  switch (state) {
    case IsolatedSVGDocumentHost::LoadStateForStandaloneTrace::kNotStarted:
      return "not_started";
    case IsolatedSVGDocumentHost::LoadStateForStandaloneTrace::kPending:
      return "pending";
    case IsolatedSVGDocumentHost::LoadStateForStandaloneTrace::
        kWaitingForAsyncLoadCompletion:
      return "waiting_for_async_load_completion";
    case IsolatedSVGDocumentHost::LoadStateForStandaloneTrace::kCompleted:
      return "completed";
  }
  return "unknown";
}

void TraceStandaloneSvgImageLoadStage(
    const char* stage,
    IsolatedSVGDocumentHost::LoadStateForStandaloneTrace state,
    LocalFrame* frame) {
  if (!TraceStandaloneSvgImageLoadStages()) {
    return;
  }
  Document* document = frame ? frame->GetDocument() : nullptr;
  std::fprintf(
      stderr,
      "standalone_svg_load.stage=%s state=%s frame=%p document=%p "
      "load_event_finished=%d load_event_still_needed=%d "
      "is_delaying_load_event=%d has_finished_parsing=%d "
      "blocking_request_count=%d is_in_request_resource=%d\n",
      stage, StandaloneSvgLoadStateName(state), static_cast<void*>(frame),
      static_cast<void*>(document),
      document ? static_cast<int>(document->LoadEventFinished()) : -1,
      document ? static_cast<int>(document->LoadEventStillNeeded()) : -1,
      document ? static_cast<int>(document->IsDelayingLoadEvent()) : -1,
      document ? static_cast<int>(document->HasFinishedParsing()) : -1,
      document && document->Fetcher()
          ? document->Fetcher()->BlockingRequestCount()
          : -1,
      document && document->Fetcher()
          ? static_cast<int>(document->Fetcher()->IsInRequestResource())
          : -1);
  std::fflush(stderr);
}
#endif

}  // namespace

// IsolatedSVGDocumentHost::LocalFrameClient is used to wait until the SVG
// document's load event is fired in the case where there are subresources
// asynchronously loaded.
class IsolatedSVGDocumentHost::LocalFrameClient : public EmptyLocalFrameClient {
 public:
  explicit LocalFrameClient(IsolatedSVGDocumentHost* host) : host_(host) {}

  void ClearHost() { host_ = nullptr; }

  void Trace(Visitor* visitor) const override {
    visitor->Trace(host_);
    EmptyLocalFrameClient::Trace(visitor);
  }

 private:
  scoped_refptr<network::SharedURLLoaderFactory> GetURLLoaderFactory()
      override {
    // SVG Images have unique security rules that prevent all subresource
    // requests except for data urls.
    return base::MakeRefCounted<network::SingleRequestURLLoaderFactory>(
        BindOnce(
            [](const network::ResourceRequest& resource_request,
               mojo::PendingReceiver<network::mojom::URLLoader> receiver,
               mojo::PendingRemote<network::mojom::URLLoaderClient> client) {
              NOTREACHED();
            }));
  }

  void DispatchDidHandleOnloadEvents() override {
#if defined(HTML_CSS_RENDERER_STANDALONE)
    TraceStandaloneSvgImageLoadStage(
        "LocalFrameClient::DispatchDidHandleOnloadEvents",
        host_ ? host_->LoadStateForStandaloneTraceForDiagnostics()
              : IsolatedSVGDocumentHost::LoadStateForStandaloneTrace::
                    kNotStarted,
        host_ ? host_->GetFrame() : nullptr);
#endif
    if (host_) {
      host_->LoadCompleted();
    }
  }

  Member<IsolatedSVGDocumentHost> host_;
};

IsolatedSVGDocumentHost::IsolatedSVGDocumentHost(
    IsolatedSVGChromeClient& chrome_client,
    AgentGroupScheduler& agent_group_scheduler,
    scoped_refptr<const SharedBuffer> data,
    base::OnceClosure async_load_callback,
    const Settings* inherited_settings,
    const ColorProviderColorMaps* inherited_color_maps,
    ProcessingMode processing_mode)
    : async_load_callback_(std::move(async_load_callback)) {
  TRACE_EVENT("blink", "IsolatedSVGDocumentHost::IsolatedSVGDocumentHost");
#if defined(HTML_CSS_RENDERER_STANDALONE)
  TraceStandaloneSvgImageLoadStage("constructor begin",
                                   LoadStateForStandaloneTraceForDiagnostics(),
                                   nullptr);
#endif

  // The isolated document will fire events (and the default C++ handlers run)
  // but doesn't actually allow scripts to run so it's fine to call into it. We
  // allow this since it means an SVG data url can synchronously load like other
  // image types.
  EventDispatchForbiddenScope::AllowUserAgentEvents allow_user_agent_events;

  CHECK_EQ(load_state_, kNotStarted);
  load_state_ = kPending;

  Page* page;
  {
    TRACE_EVENT("blink",
                "IsolatedSVGDocumentHost::IsolatedSVGDocumentHost::createPage");
    page = Page::CreateNonOrdinary(chrome_client, agent_group_scheduler,
                                   inherited_color_maps);

    Settings& settings = page->GetSettings();
    settings.SetScriptEnabled(false);
    settings.SetPluginsEnabled(false);

    if (inherited_settings) {
      CopySettingsFrom(settings, *inherited_settings);
    }

    // If "secure static mode" is requested, set the animation policy to "no
    // animation". This will disable SMIL and image animations.
    if (processing_mode == ProcessingMode::kStatic) {
      settings.SetImageAnimationPolicy(
          mojom::blink::ImageAnimationPolicy::kImageAnimationPolicyNoAnimation);
    }
  }

  LocalFrame* frame = nullptr;
  {
    TRACE_EVENT(
        "blink",
        "IsolatedSVGDocumentHost::IsolatedSVGDocumentHost::createFrame");
    frame_client_ = MakeGarbageCollected<LocalFrameClient>(this);
    frame = MakeGarbageCollected<LocalFrame>(
        frame_client_, *page, nullptr, nullptr, nullptr,
        FrameInsertType::kInsertInConstructor, LocalFrameToken(), nullptr,
        nullptr, mojo::NullRemote());
    frame->SetView(MakeGarbageCollected<LocalFrameView>(*frame));
    frame->Init(/*opener=*/nullptr, DocumentToken(),
                /*policy_container=*/nullptr, StorageKey(),
                /*document_ukm_source_id=*/ukm::kInvalidSourceId,
                /*creator_base_url=*/NullUrl());
    frame->View()->SetParentVisible(true);
    frame->View()->SetSelfVisible(true);
  }

  // SVG Images will always synthesize a viewBox, if it's not available, and
  // thus never see scrollbars.
  frame->View()->SetCanHaveScrollbars(false);
  // SVG Images are transparent.
  frame->View()->SetBaseBackgroundColor(Color::kTransparent);

  {
    TRACE_EVENT("blink",
                "IsolatedSVGDocumentHost::IsolatedSVGDocumentHost::load");
    frame->ForceSynchronousDocumentInstall(AtomicString("image/svg+xml"),
                                           *data);
#if defined(HTML_CSS_RENDERER_STANDALONE)
    TraceStandaloneSvgImageLoadStage("after ForceSynchronousDocumentInstall",
                                     LoadStateForStandaloneTraceForDiagnostics(),
                                     frame);
#endif
  }

  // Set up our Page reference after installing our document. This avoids
  // tripping on a non-existing (null) Document if a GC is triggered during the
  // set up and ends up collecting the last owner/observer of this image.
  page_ = page;

  // Intrinsic sizing relies on computed style (e.g. font-size and
  // writing-mode).
  frame->GetDocument()->UpdateStyleAndLayoutTree();
#if defined(HTML_CSS_RENDERER_STANDALONE)
  TraceStandaloneSvgImageLoadStage("after UpdateStyleAndLayoutTree",
                                   LoadStateForStandaloneTraceForDiagnostics(),
                                   frame);
#endif

  switch (load_state_) {
    case kPending:
      load_state_ = kWaitingForAsyncLoadCompletion;
      break;
    case kWaitingForAsyncLoadCompletion:
      break;
    case kCompleted:
      if (!frame->GetDocument()->LoadEventFinished()) {
        load_state_ = kWaitingForAsyncLoadCompletion;
#if defined(HTML_CSS_RENDERER_STANDALONE)
        TraceStandaloneSvgImageLoadStage(
            "constructor posting AsyncLoadCompleted",
            LoadStateForStandaloneTraceForDiagnostics(), frame);
#endif
        async_load_task_handle_ = PostCancellableTask(
            *frame->GetTaskRunner(TaskType::kInternalLoading), FROM_HERE,
            BindOnce(&IsolatedSVGDocumentHost::AsyncLoadCompleted,
                     WrapPersistent(this)));
      }
      break;
    case kNotStarted:
      NOTREACHED();
  }
#if defined(HTML_CSS_RENDERER_STANDALONE)
  ScheduleStandaloneLoadCompletionCheck();
  TraceStandaloneSvgImageLoadStage("constructor end",
                                   LoadStateForStandaloneTraceForDiagnostics(),
                                   frame);
#endif
}

void IsolatedSVGDocumentHost::CopySettingsFrom(
    Settings& settings,
    const Settings& inherited_settings) {
  settings.GetGenericFontFamilySettings() =
      inherited_settings.GetGenericFontFamilySettings();
  settings.SetMinimumFontSize(inherited_settings.GetMinimumFontSize());
  settings.SetMinimumLogicalFontSize(
      inherited_settings.GetMinimumLogicalFontSize());
  settings.SetDefaultFontSize(inherited_settings.GetDefaultFontSize());
  settings.SetDefaultFixedFontSize(
      inherited_settings.GetDefaultFixedFontSize());

  settings.SetImageAnimationPolicy(
      inherited_settings.GetImageAnimationPolicy());
  settings.SetPrefersReducedMotion(
      inherited_settings.GetPrefersReducedMotion());

  // Also copy the preferred-color-scheme to ensure a responsiveness to
  // dark/light color schemes.
  settings.SetPreferredColorScheme(
      inherited_settings.GetPreferredColorScheme());
  settings.SetInForcedColors(inherited_settings.GetInForcedColors());

  settings.SetAcceptLanguages(inherited_settings.GetAcceptLanguages());
}

LocalFrame* IsolatedSVGDocumentHost::GetFrame() {
  return page_ ? To<LocalFrame>(page_->MainFrame()) : nullptr;
}

SVGSVGElement* IsolatedSVGDocumentHost::RootElement() {
  LocalFrame* frame = GetFrame();
  Node* document_element =
      frame ? frame->GetDocument()->documentElement() : nullptr;
  return DynamicTo<SVGSVGElement>(document_element);
}

void IsolatedSVGDocumentHost::LoadCompleted() {
#if defined(HTML_CSS_RENDERER_STANDALONE)
  TraceStandaloneSvgImageLoadStage("LoadCompleted begin",
                                   LoadStateForStandaloneTraceForDiagnostics(),
                                   GetFrame());
#endif
  switch (load_state_) {
    case kPending:
      if (GetFrame()->GetDocument()->LoadEventFinished()) {
        load_state_ = kCompleted;
#if defined(HTML_CSS_RENDERER_STANDALONE)
        TraceStandaloneSvgImageLoadStage(
            "LoadCompleted marked completed",
            LoadStateForStandaloneTraceForDiagnostics(), GetFrame());
#endif
      } else {
        load_state_ = kWaitingForAsyncLoadCompletion;
#if defined(HTML_CSS_RENDERER_STANDALONE)
        TraceStandaloneSvgImageLoadStage(
            "LoadCompleted posting AsyncLoadCompleted from pending",
            LoadStateForStandaloneTraceForDiagnostics(), GetFrame());
#endif
        async_load_task_handle_ = PostCancellableTask(
            *GetFrame()->GetTaskRunner(TaskType::kInternalLoading), FROM_HERE,
            BindOnce(&IsolatedSVGDocumentHost::AsyncLoadCompleted,
                     WrapPersistent(this)));
      }
      break;

    case kWaitingForAsyncLoadCompletion:
      // Because LoadCompleted() is called synchronously from
      // Document::DispatchLoadEventAndFinalize(), we defer AsyncLoadCompleted()
      // to avoid potential bugs and timing dependencies around
      // DispatchLoadEventAndFinalize() and to make LoadEventFinished() true
      // when AsyncLoadCompleted() is called.
#if defined(HTML_CSS_RENDERER_STANDALONE)
      TraceStandaloneSvgImageLoadStage(
          "LoadCompleted posting AsyncLoadCompleted from waiting",
          LoadStateForStandaloneTraceForDiagnostics(), GetFrame());
#endif
      async_load_task_handle_ = PostCancellableTask(
          *GetFrame()->GetTaskRunner(TaskType::kInternalLoading), FROM_HERE,
          BindOnce(&IsolatedSVGDocumentHost::AsyncLoadCompleted,
                   WrapPersistent(this)));
      break;

    case kNotStarted:
    case kCompleted:
      NOTREACHED();
  }
}

void IsolatedSVGDocumentHost::AsyncLoadCompleted() {
#if defined(HTML_CSS_RENDERER_STANDALONE)
  TraceStandaloneSvgImageLoadStage("AsyncLoadCompleted begin",
                                   LoadStateForStandaloneTraceForDiagnostics(),
                                   GetFrame());
#endif
  if (!GetFrame()->GetDocument()->LoadEventFinished()) {
#if defined(HTML_CSS_RENDERER_STANDALONE)
    TraceStandaloneSvgImageLoadStage(
        "AsyncLoadCompleted reposting because load event unfinished",
        LoadStateForStandaloneTraceForDiagnostics(), GetFrame());
#endif
    async_load_task_handle_ = PostCancellableTask(
        *GetFrame()->GetTaskRunner(TaskType::kInternalLoading), FROM_HERE,
        BindOnce(&IsolatedSVGDocumentHost::AsyncLoadCompleted,
                 WrapPersistent(this)));
    return;
  }

  load_state_ = kCompleted;
#if defined(HTML_CSS_RENDERER_STANDALONE)
  TraceStandaloneSvgImageLoadStage("AsyncLoadCompleted running callback",
                                   LoadStateForStandaloneTraceForDiagnostics(),
                                   GetFrame());
#endif
  std::move(async_load_callback_).Run();
}

#if defined(HTML_CSS_RENDERER_STANDALONE)
void IsolatedSVGDocumentHost::ScheduleStandaloneLoadCompletionCheck() {
  if (load_state_ != kWaitingForAsyncLoadCompletion || !GetFrame()) {
    return;
  }
  TraceStandaloneSvgImageLoadStage(
      "posting standalone load completion check",
      LoadStateForStandaloneTraceForDiagnostics(), GetFrame());
  scoped_refptr<base::SingleThreadTaskRunner> task_runner =
      base::SingleThreadTaskRunner::HasCurrentDefault()
          ? base::SingleThreadTaskRunner::GetCurrentDefault()
          : GetFrame()->GetTaskRunner(TaskType::kInternalLoading);
  standalone_load_completion_task_handle_ = PostCancellableTask(
      *task_runner, FROM_HERE,
      BindOnce(&IsolatedSVGDocumentHost::MaybeFinalizeStandaloneSynchronousLoad,
               WrapPersistent(this)));
}

void IsolatedSVGDocumentHost::MaybeFinalizeStandaloneSynchronousLoad() {
  LocalFrame* frame = GetFrame();
  Document* document = frame ? frame->GetDocument() : nullptr;
  TraceStandaloneSvgImageLoadStage(
      "standalone load completion check begin",
      LoadStateForStandaloneTraceForDiagnostics(), frame);
  if (!document || document->LoadEventFinished() ||
      load_state_ != kWaitingForAsyncLoadCompletion) {
    return;
  }
  ResourceFetcher* fetcher = document->Fetcher();
  if (!document->HasFinishedParsing() || document->IsDelayingLoadEvent() ||
      (fetcher && (fetcher->BlockingRequestCount() ||
                   fetcher->IsInRequestResource()))) {
    TraceStandaloneSvgImageLoadStage(
        "standalone load completion check deferred",
        LoadStateForStandaloneTraceForDiagnostics(), frame);
    ScheduleStandaloneLoadCompletionCheck();
    return;
  }

  TraceStandaloneSvgImageLoadStage(
      "standalone load completion check before CheckCompleted",
      LoadStateForStandaloneTraceForDiagnostics(), frame);
  EventDispatchForbiddenScope::AllowUserAgentEvents allow_events;
  document->CheckCompleted();
  TraceStandaloneSvgImageLoadStage(
      "standalone load completion check after CheckCompleted",
      LoadStateForStandaloneTraceForDiagnostics(), frame);
  if (load_state_ == kWaitingForAsyncLoadCompletion &&
      document->LoadEventFinished()) {
    async_load_task_handle_.Cancel();
    TraceStandaloneSvgImageLoadStage(
        "standalone load completion check running AsyncLoadCompleted directly",
        LoadStateForStandaloneTraceForDiagnostics(), frame);
    AsyncLoadCompleted();
  }
}
#endif

void IsolatedSVGDocumentHost::Shutdown() {
  AllowDestroyingLayoutObjectInFinalizerScope scope;

  // The constructor initializes `page_` and we tear it down here. Shutdown()
  // shouldn't be called twice. Ditto for `frame_client_`.
  DCHECK(page_);
  DCHECK(frame_client_);

  // Sever the link from the frame client back to us to prevent any pending
  // loads from completing.
  frame_client_->ClearHost();

  // Cancel any in-flight async load task.
  async_load_task_handle_.Cancel();
#if defined(HTML_CSS_RENDERER_STANDALONE)
  standalone_load_completion_task_handle_.Cancel();
#endif

  // It is safe to allow UA events within this scope, because event
  // dispatching inside the isolated document doesn't trigger JavaScript
  // execution. All script execution is forbidden when an SVG is loaded as an
  // image subresource - see SetScriptEnabled in IsolatedSVGDocumentHost().
  EventDispatchForbiddenScope::AllowUserAgentEvents allow_events;
  Page* current_page = page_.Release();
  // Break both the loader and view references to the frame.
  current_page->WillBeDestroyed();
}

IsolatedSVGDocumentHost::~IsolatedSVGDocumentHost() {
  DCHECK(!page_);  // Expecting explicit shutdown.
}

void IsolatedSVGDocumentHost::Trace(Visitor* visitor) const {
  visitor->Trace(page_);
  visitor->Trace(frame_client_);
}

}  // namespace blink
