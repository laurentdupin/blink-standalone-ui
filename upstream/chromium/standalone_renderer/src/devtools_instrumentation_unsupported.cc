// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/core_probe_sink.h"

#include "third_party/blink/renderer/core/core_probes_inl.h"
#include "third_party/blink/renderer/core/ad_tracker/ad_tracker.h"
#include "third_party/blink/renderer/core/frame/animation_frame_timing_monitor.h"
#include "third_party/blink/renderer/core/frame/performance_monitor.h"
#include "third_party/blink/renderer/core/inspector/identifiers_factory.h"
#include "third_party/blink/renderer/core/inspector/inspector_animation_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_audits_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_css_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_dom_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_dom_debugger_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_dom_snapshot_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_emulation_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_event_breakpoints_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_issue_reporter.h"
#include "third_party/blink/renderer/core/inspector/inspector_layer_tree_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_log_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_media_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_network_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_overlay_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_page_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_performance_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_performance_timeline_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_preload_agent.h"
#include "third_party/blink/renderer/core/inspector/inspector_trace_events.h"
#include "third_party/blink/renderer/core/inspector/inspector_web_mcp_agent.h"
#include "third_party/blink/renderer/core/inspector/invalidation_set_to_selector_map.h"
#include "third_party/blink/renderer/core/lcp_critical_path_predictor/lcp_script_observer.h"
#include <atomic>

namespace blink {

std::atomic<unsigned> CoreProbeSink::s_existingAgents;

CoreProbeSink::CoreProbeSink() = default;

CoreProbeSink::~CoreProbeSink() = default;

void CoreProbeSink::Trace(Visitor*) const {}

#define DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(method_suffix, agent_type) \
  void CoreProbeSink::Add##method_suffix(agent_type*) {}                    \
  void CoreProbeSink::Remove##method_suffix(agent_type*) {}

DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(AdTracker, AdTracker)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(AnimationFrameTimingMonitor,
                                         AnimationFrameTimingMonitor)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(DevToolsSession, DevToolsSession)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorAnimationAgent,
                                         InspectorAnimationAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorAuditsAgent,
                                         InspectorAuditsAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorCSSAgent, InspectorCSSAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorDOMAgent, InspectorDOMAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorDOMDebuggerAgent,
                                         InspectorDOMDebuggerAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorDOMSnapshotAgent,
                                         InspectorDOMSnapshotAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorEmulationAgent,
                                         InspectorEmulationAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorEventBreakpointsAgent,
                                         InspectorEventBreakpointsAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorIssueReporter,
                                         InspectorIssueReporter)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorLayerTreeAgent,
                                         InspectorLayerTreeAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorLogAgent, InspectorLogAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorMediaAgent,
                                         InspectorMediaAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorNetworkAgent,
                                         InspectorNetworkAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorOverlayAgent,
                                         InspectorOverlayAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorPageAgent, InspectorPageAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorPerformanceAgent,
                                         InspectorPerformanceAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorPerformanceTimelineAgent,
                                         InspectorPerformanceTimelineAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorPreloadAgent,
                                         InspectorPreloadAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorTraceEvents,
                                         InspectorTraceEvents)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(InspectorWebMCPAgent,
                                         InspectorWebMCPAgent)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(LCPScriptObserver, LCPScriptObserver)
DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS(PerformanceMonitor,
                                         PerformanceMonitor)

#undef DEFINE_UNSUPPORTED_PROBE_AGENT_ACCESSORS

namespace probe {

base::TimeTicks ProbeBase::CaptureStartTime() const {
  return base::TimeTicks();
}

base::TimeTicks ProbeBase::CaptureEndTime() const {
  return base::TimeTicks();
}

base::TimeDelta ProbeBase::Duration() const {
  return base::TimeDelta();
}

AsyncTask::AsyncTask(ExecutionContext*,
                     AsyncTaskContext* async_context,
                     const char* step,
                     bool)
    : debugger_(nullptr),
      task_context_(async_context),
      recurring_(step != nullptr) {}

AsyncTask::~AsyncTask() = default;

void WillInsertDOMNodeImpl(Node*) {}

void DidInsertDOMNodeImpl(Node*) {}

void WillRemoveDOMNodeImpl(Node*) {}

void WillChangeStyleElementImpl(Element*) {}

void CharacterDataModifiedImpl(CharacterData*) {}

void DocumentDetachedImpl(Document*) {}

void ActiveStyleSheetsUpdatedImpl(Document*) {}

void FontsUpdatedImpl(ExecutionContext*,
                      const FontFace*,
                      const String&,
                      const FontCustomPlatformData*) {}

void MediaQueryResultChangedImpl(Document*) {}

void DidResizeMainFrameImpl(LocalFrame*) {}

void DidCreateAnimationImpl(Document*, unsigned) {}

void AnimationUpdatedImpl(Document*, Animation*) {}

void BreakableLocationImpl(ExecutionContext*, const char*) {}

RecalculateStyle::RecalculateStyle(Document* document) : document(document) {}

RecalculateStyle::~RecalculateStyle() = default;

UpdateLayout::UpdateLayout(Document* document) : document(document) {}

UpdateLayout::~UpdateLayout() = default;

EvaluateScriptBlock::EvaluateScriptBlock(
    std::reference_wrapper<std::remove_reference_t<ScriptState&>> script_state,
    std::reference_wrapper<std::remove_reference_t<const KURL&>> source_url,
    bool is_module,
    bool sanitize)
    : script_state(script_state.get()),
      source_url(source_url.get()),
      is_module(is_module),
      sanitize(sanitize) {}

EvaluateScriptBlock::~EvaluateScriptBlock() = default;

ExecuteScript::ExecuteScript(ExecutionContext* context,
                             v8::Local<v8::Context> v8_context,
                             std::reference_wrapper<
                                 std::remove_reference_t<const String&>>
                                 script_url,
                             int script_id)
    : context(context),
      v8_context(v8_context),
      script_url(script_url.get()),
      script_id(script_id) {}

ExecuteScript::~ExecuteScript() = default;

CallFunction::CallFunction(ExecutionContext* context,
                           v8::Local<v8::Context> v8_context,
                           v8::Local<v8::Function> function,
                           int depth)
    : context(context),
      v8_context(v8_context),
      function(function),
      depth(depth) {}

CallFunction::~CallFunction() = default;

UserCallback::UserCallback(ExecutionContext* context,
                           const char* name,
                           AtomicString atomic_name,
                           bool recurring,
                           EventTarget* event_target,
                           Event* event,
                           EventListener* listener)
    : context(context),
      name(name),
      atomic_name(atomic_name),
      recurring(recurring),
      event_target(event_target),
      event(event),
      listener(listener) {}

UserCallback::~UserCallback() = default;

InvokeCallback::InvokeCallback(
    std::reference_wrapper<std::remove_reference_t<ScriptState&>> script_state,
    const char* name,
    CallbackFunctionBase* callback,
    v8::MaybeLocal<v8::Value> function)
    : script_state(script_state.get()),
      name(name),
      callback(callback),
      function(function) {}

InvokeCallback::~InvokeCallback() = default;

InvokeEventHandler::InvokeEventHandler(
    std::reference_wrapper<std::remove_reference_t<ScriptState&>> script_state,
    Event* event,
    JSBasedEventListener* listener)
    : script_state(script_state.get()), event(event), listener(listener) {}

InvokeEventHandler::~InvokeEventHandler() = default;

UserEntryPoint::UserEntryPoint(ExecutionContext* context,
                               v8::Local<v8::Object> callback_object,
                               size_t index)
    : context(context), callback_object(callback_object), index(index) {}

UserEntryPoint::~UserEntryPoint() = default;

FrameRelatedTask::FrameRelatedTask(ExecutionContext* context)
    : context(context) {}

FrameRelatedTask::~FrameRelatedTask() = default;

V8Compile::V8Compile(
    ExecutionContext* context,
    std::reference_wrapper<std::remove_reference_t<const String&>> file_name,
    int line,
    int column)
    : context(context),
      file_name(file_name.get()),
      line(line),
      column(column) {}

V8Compile::~V8Compile() = default;

ParseHTML::ParseHTML(Document* document, HTMLDocumentParser* parser)
    : document(document), parser(parser) {}

ParseHTML::~ParseHTML() = default;

void ForcePseudoStateImpl(Element*,
                          CSSSelector::PseudoType,
                          bool* result) {
  if (result) {
    *result = false;
  }
}

void ForceStartingStyleImpl(Element*, bool* result) {
  if (result) {
    *result = false;
  }
}

void DidMutateStyleSheetImpl(Document*, CSSStyleSheet*) {}

void DidReplaceStyleSheetTextImpl(Document*, CSSStyleSheet*, const String&) {}

void GetTextPositionImpl(Document*, wtf_size_t, const String*, TextPosition*) {}

// Generated probe dispatch is disabled with DevTools; keep these hooks no-op.
void DidClearDocumentOfWindowObjectImpl(LocalFrame*) {}
void DidCreateMainWorldContextImpl(LocalFrame*) {}
void WillModifyDOMAttrImpl(Element*, const AtomicString&, const AtomicString&) {}
void DidModifyDOMAttrImpl(Element*, const QualifiedName&, const AtomicString&) {}
void DidRemoveDOMAttrImpl(Element*, const QualifiedName&) {}
void DidModifyAdoptedStyleSheetsImpl(Node*) {}
void DidInvalidateStyleAttrImpl(Element*) {}
void DidPerformSlotDistributionImpl(HTMLSlotElement*) {}
void DidPushShadowRootImpl(Element*, ShadowRoot*) {}
void WillPopShadowRootImpl(Element*, ShadowRoot*) {}
void WillSendXMLHttpOrFetchNetworkRequestImpl(ExecutionContext*, const String&) {}
void DidCreateCanvasContextImpl(Document*) {}
void DidCreateOffscreenCanvasContextImpl(OffscreenCanvas*) {}
void DidFireWebGLErrorImpl(Element*, const String&) {}
void DidFireWebGLWarningImpl(Element*) {}
void DidFireWebGLErrorOrWarningImpl(Element*, const String&) {}
void ApplyAcceptLanguageOverrideImpl(ExecutionContext*, String*) {}
void ApplyHardwareConcurrencyOverrideImpl(CoreProbeSink*, unsigned int&) {}
void ApplyDataSaverOverrideImpl(CoreProbeSink*, bool&) {}
void ApplyUserAgentOverrideImpl(CoreProbeSink*, String*) {}
void ApplyUserAgentMetadataOverrideImpl(CoreProbeSink*, std::optional<blink::UserAgentMetadata>*) {}
void DidBlockRequestImpl(CoreProbeSink*, const ResourceRequest&, DocumentLoader*, const KURL&, const ResourceLoaderOptions&, ResourceRequestBlockedReason, ResourceType) {}
void DidChangeResourcePriorityImpl(LocalFrame*, DocumentLoader*, uint64_t, ResourceLoadPriority) {}
void PrepareRequestImpl(CoreProbeSink*, DocumentLoader*, ResourceRequest&, ResourceLoaderOptions&, ResourceType) {}
void WillSendRequestImpl(ExecutionContext*, DocumentLoader*, const KURL&, const ResourceRequest&, const ResourceResponse&, const ResourceLoaderOptions&, ResourceType, RenderBlockingBehavior, base::TimeTicks) {}
void WillSendNavigationRequestImpl(CoreProbeSink*, uint64_t, DocumentLoader*, const KURL&, const AtomicString&, EncodedFormData*) {}
void WillSendWorkerMainRequestImpl(ExecutionContext*, uint64_t, const KURL&) {}
void MarkResourceAsCachedImpl(LocalFrame*, DocumentLoader*, uint64_t) {}
void DidReceiveResourceResponseImpl(CoreProbeSink*, uint64_t, DocumentLoader*, const ResourceResponse&, const Resource*) {}
void DidReceiveDataImpl(CoreProbeSink*, uint64_t, DocumentLoader*, base::SpanOrSize<const char>) {}
void DidReceiveBlobImpl(CoreProbeSink*, uint64_t, DocumentLoader*, BlobDataHandle*) {}
void DidReceiveEncodedDataLengthImpl(CoreProbeSink*, DocumentLoader*, uint64_t, size_t) {}
void DidFinishLoadingImpl(CoreProbeSink*, uint64_t, DocumentLoader*, base::TimeTicks, int64_t, int64_t) {}
void DidReceiveCorsRedirectResponseImpl(ExecutionContext*, uint64_t, DocumentLoader*, const ResourceResponse&, Resource*) {}
void DidFailLoadingImpl(CoreProbeSink*, uint64_t, DocumentLoader*, const ResourceError&, const base::UnguessableToken&) {}
void WillSendEventSourceRequestImpl(ExecutionContext*) {}
void WillDispatchEventSourceEventImpl(ExecutionContext*, uint64_t, const AtomicString&, const AtomicString&, const String&) {}
void WillLoadXHRImpl(ExecutionContext*, const AtomicString&, const KURL&, bool, const HTTPHeaderMap&, bool) {}
void DidFinishXHRImpl(ExecutionContext*, XMLHttpRequest*) {}
void DidFinishSyncXHRImpl(ExecutionContext*, const base::TimeDelta) {}
void ScriptImportedImpl(ExecutionContext*, uint64_t, const String&) {}
void ScriptExecutionBlockedByCSPImpl(ExecutionContext*, const String&) {}
void DidReceiveScriptResponseImpl(ExecutionContext*, uint64_t) {}
void DomContentLoadedEventFiredImpl(LocalFrame*) {}
void LoadEventFiredImpl(LocalFrame*) {}
void FrameAttachedToParentImpl(LocalFrame*, const AdTracker::AdScriptAncestry&) {}
void FrameDetachedFromParentImpl(LocalFrame*, FrameDetachType) {}
void FrameSubtreeWillBeDetachedImpl(LocalFrame*, Frame*) {}
void DidStartProvisionalLoadImpl(LocalFrame*) {}
void DidFailProvisionalLoadImpl(LocalFrame*) {}
void WillCommitLoadImpl(LocalFrame*, DocumentLoader*) {}
void DidCommitLoadImpl(LocalFrame*, DocumentLoader*) {}
void DidNavigateWithinDocumentImpl(LocalFrame*, blink::mojom::SameDocumentNavigationType) {}
void DidRestoreFromBackForwardCacheImpl(LocalFrame*) {}
void DidOpenDocumentImpl(LocalFrame*, DocumentLoader*) {}
void WillCreateDocumentParserImpl(Document*, bool&) {}
void FrameDocumentUpdatedImpl(LocalFrame*) {}
void FrameOwnerContentUpdatedImpl(LocalFrame*, HTMLFrameOwnerElement*) {}
void FrameStartedLoadingImpl(LocalFrame*) {}
void FrameStoppedLoadingImpl(LocalFrame*) {}
void FrameRequestedNavigationImpl(LocalFrame*, Frame*, const KURL&, ClientNavigationReason, NavigationPolicy) {}
void FrameScheduledNavigationImpl(LocalFrame*, const KURL&, base::TimeDelta, ClientNavigationReason) {}
void FrameClearedScheduledNavigationImpl(LocalFrame*) {}
void WillCreateWebSocketImpl(ExecutionContext*, uint64_t, const KURL&, const String&, std::optional<base::UnguessableToken>*) {}
void WillSendWebSocketHandshakeRequestImpl(ExecutionContext*, uint64_t, network::mojom::blink::WebSocketHandshakeRequest*) {}
void DidReceiveWebSocketHandshakeResponseImpl(ExecutionContext*, uint64_t, network::mojom::blink::WebSocketHandshakeRequest*, network::mojom::blink::WebSocketHandshakeResponse*) {}
void DidCloseWebSocketImpl(ExecutionContext*, uint64_t) {}
void DidReceiveWebSocketMessageImpl(ExecutionContext*, uint64_t, int, bool, const Vector<base::span<const uint8_t>>&) {}
void DidSendWebSocketMessageImpl(ExecutionContext*, uint64_t, int, bool, base::span<const uint8_t>) {}
void DidReceiveWebSocketMessageErrorImpl(ExecutionContext*, uint64_t, const String&) {}
void WebTransportCreatedImpl(ExecutionContext*, uint64_t, const KURL&) {}
void WebTransportConnectionEstablishedImpl(ExecutionContext*, uint64_t) {}
void WebTransportClosedImpl(ExecutionContext*, uint64_t) {}
void DirectTCPSocketCreatedImpl(ExecutionContext*, uint64_t, const String&, uint16_t, protocol::Network::DirectTCPSocketOptions&) {}
void DirectTCPSocketOpenedImpl(ExecutionContext*, uint64_t, const String&, uint16_t, std::optional<String>, std::optional<uint16_t>) {}
void DirectTCPSocketAbortedImpl(ExecutionContext*, uint64_t, int) {}
void DirectTCPSocketClosedImpl(ExecutionContext*, uint64_t) {}
void DirectTCPSocketChunkSentImpl(ScriptState&, uint64_t, base::span<const uint8_t>) {}
void DirectTCPSocketChunkReceivedImpl(ScriptState&, uint64_t, base::span<const uint8_t>) {}
void DirectUDPSocketCreatedImpl(ExecutionContext*, uint64_t, protocol::Network::DirectUDPSocketOptions&) {}
void DirectUDPSocketOpenedImpl(ExecutionContext*, uint64_t, const String&, uint16_t, std::optional<String>, std::optional<uint16_t>) {}
void DirectUDPSocketAbortedImpl(ExecutionContext*, uint64_t, int) {}
void DirectUDPSocketClosedImpl(ExecutionContext*, uint64_t) {}
void DirectUDPSocketChunkSentImpl(ScriptState&, uint64_t, base::span<const uint8_t>, std::optional<String>, std::optional<uint16_t>) {}
void DirectUDPSocketChunkReceivedImpl(ScriptState&, uint64_t, base::span<const uint8_t>, std::optional<String>, std::optional<uint16_t>) {}
void DirectUDPSocketJoinedMulticastGroupImpl(ExecutionContext*, uint64_t, const String&) {}
void DirectUDPSocketLeftMulticastGroupImpl(ExecutionContext*, uint64_t, const String&) {}
void WillCreateP2PSocketUdpImpl(ExecutionContext*, std::optional<base::UnguessableToken>*) {}
void LayerTreeDidChangeImpl(LocalFrame*) {}
void LayerTreePaintedImpl(LocalFrame*) {}
void PseudoElementCreatedImpl(PseudoElement*) {}
void TopLayerElementsChangedImpl(Document*) {}
void PseudoElementDestroyedImpl(PseudoElement*) {}
void WindowOpenImpl(ExecutionContext*, const KURL&, const AtomicString&, const WebWindowFeatures&, bool) {}
void ConsoleMessageAddedImpl(ExecutionContext*, ConsoleMessage*) {}
void InspectorIssueAddedImpl(CoreProbeSink*, protocol::Audits::InspectorIssue*) {}
void WillRunJavaScriptDialogImpl(LocalFrame*) {}
void DidRunJavaScriptDialogImpl(LocalFrame*) {}
void DocumentWriteFetchScriptImpl(Document*) {}
void DidChangeViewportImpl(LocalFrame*) {}
void WillHandlePromiseImpl(ExecutionContext*, ScriptState*, bool, const char*, PropertyName, LazySourceLocation*) {}
void ShouldForceCorsPreflightImpl(ExecutionContext*, bool*) {}
void ShouldBlockRequestImpl(CoreProbeSink*, const KURL&, bool*) {}
void ShouldBypassServiceWorkerImpl(ExecutionContext*, bool*) {}
void ConsoleTimeStampImpl(v8::Isolate*, v8::Local<v8::String>) {}
void WillStartDebuggerTaskImpl(CoreProbeSink*) {}
void DidFinishDebuggerTaskImpl(CoreProbeSink*) {}
void LifecycleEventImpl(LocalFrame*, DocumentLoader*, const char*, double) {}
void PaintTimingImpl(Document*, const char*, double) {}
void DidCreateAudioContextImpl(ExecutionContext*) {}
void DidCloseAudioContextImpl(ExecutionContext*) {}
void DidResumeAudioContextImpl(ExecutionContext*) {}
void DidSuspendAudioContextImpl(ExecutionContext*) {}
void DidProduceCompilationCacheImpl(CoreProbeSink*, const ClassicScript&, v8::Local<v8::Script>) {}
void ApplyCompilationModeOverrideImpl(ExecutionContext*, const ClassicScript&, v8::ScriptCompiler::CachedData**, v8::ScriptCompiler::CompileOptions*) {}
void NodeCreatedImpl(Node*) {}
void FileChooserOpenedImpl(LocalFrame*, HTMLInputElement*, bool, bool*, bool*) {}
void PlayerErrorsRaisedImpl(ExecutionContext*, String, const Vector<InspectorPlayerError>&) {}
void PlayerEventsAddedImpl(ExecutionContext*, String, const Vector<InspectorPlayerEvent>&) {}
void PlayerMessagesLoggedImpl(ExecutionContext*, String, const Vector<InspectorPlayerMessage>&) {}
void PlayerPropertiesChangedImpl(ExecutionContext*, String, const Vector<InspectorPlayerProperty>&) {}
void PlayerCreatedImpl(ExecutionContext*, const MediaPlayer&) {}
void SetDevToolsIdsImpl(CoreProbeSink*, ResourceRequest&, const FetchInitiatorInfo&) {}
void LocalFontsEnabledImpl(ExecutionContext*, bool*) {}
void DidUpdateComputedStyleImpl(Element*, const ComputedStyle*, const ComputedStyle*) {}
void GetDisabledImageTypesImpl(ExecutionContext*, HashSet<String>*) {}
void OnContentSecurityPolicyViolationImpl(ExecutionContext*, const blink::ContentSecurityPolicyViolationType) {}
void IsCacheDisabledImpl(ExecutionContext*, bool*) {}
void ShouldApplyDevtoolsCookieSettingOverridesImpl(ExecutionContext*, bool*) {}
void PerformanceEntryAddedImpl(ExecutionContext*, PerformanceEntry*) {}
void ApplyAutomationOverrideImpl(ExecutionContext*, bool&) {}
void DidAddSpeculationRuleSetImpl(Document&, const SpeculationRuleSet&) {}
void DidRemoveSpeculationRuleSetImpl(Document&, const SpeculationRuleSet&) {}
void SpeculationCandidatesUpdatedImpl(Document&, const HeapVector<Member<SpeculationCandidate>>&) {}
void DidInitializeFrameWidgetImpl(LocalFrame*) {}
void UpdateScrollableFlagImpl(Node*, std::optional<bool>) {}
void UpdateAdRelatedStateImpl(Node&, std::optional<AdProvenance>) {}
void WillHidePopoverImpl(HTMLElement*, bool*) {}
void UpdateAffectedByStartingStylesFlagImpl(Node*, std::optional<bool>) {}
void WebMCPToolAddedImpl(Document*, const ToolData&) {}
void WebMCPToolRemovedImpl(Document*, const ToolData&) {}
void WebMCPToolExecutedImpl(Document*, const String&, const String&, const base::UnguessableToken&) {}
void WebMCPToolRespondedImpl(Document*, const String&, const base::UnguessableToken&) {}
void WebMCPToolFailedImpl(Document*, const ScriptToolError&, const base::UnguessableToken&, ScriptException) {}

}  // namespace probe

namespace inspector_schedule_style_invalidation_tracking_event {

const char kAttribute[] = "Attribute";
const char kClass[] = "Class";
const char kId[] = "Id";
const char kPseudo[] = "Pseudo";
const char kRuleSet[] = "RuleSet";

void AttributeChange(perfetto::TracedValue,
                     Element&,
                     const InvalidationSet&,
                     const QualifiedName&) {}

void ClassChange(perfetto::TracedValue,
                 Element&,
                 const InvalidationSet&,
                 const AtomicString&) {}

void IdChange(perfetto::TracedValue,
              Element&,
              const InvalidationSet&,
              const AtomicString&) {}

void PseudoChange(perfetto::TracedValue,
                  Element&,
                  const InvalidationSet&,
                  CSSSelector::PseudoType) {}

}  // namespace inspector_schedule_style_invalidation_tracking_event

namespace inspector_style_resolver_resolve_style_event {

void Data(perfetto::TracedValue, Element*, PseudoId) {}

}  // namespace inspector_style_resolver_resolve_style_event

namespace inspector_style_recalc_invalidation_tracking_event {

void Data(perfetto::TracedValue,
          Node*,
          StyleChangeType,
          const StyleChangeReasonForTracing&) {}

}  // namespace inspector_style_recalc_invalidation_tracking_event

namespace inspector_parse_author_style_sheet_event {

void Data(perfetto::TracedValue, const CSSStyleSheetResource*) {}

}  // namespace inspector_parse_author_style_sheet_event

namespace inspector_mark_load_event {

void Data(perfetto::TracedValue, LocalFrame*) {}

}  // namespace inspector_mark_load_event

namespace inspector_handle_post_message_event {

void Data(perfetto::TracedValue, ExecutionContext*, const MessageEvent&) {}

}  // namespace inspector_handle_post_message_event

namespace inspector_event_dispatch_event {

void Data(perfetto::TracedValue, const Event&, v8::Isolate*) {}

}  // namespace inspector_event_dispatch_event

namespace inspector_schedule_post_message_event {

void Data(perfetto::TracedValue, ExecutionContext*, uint64_t) {}

}  // namespace inspector_schedule_post_message_event

namespace inspector_layerize_event {

void Data(perfetto::TracedValue, LocalFrame*) {}

}  // namespace inspector_layerize_event

namespace inspector_invalidate_layout_event {

void Data(perfetto::TracedValue, LocalFrame*, DOMNodeId) {}

}  // namespace inspector_invalidate_layout_event

namespace inspector_hit_test_event {

void EndData(perfetto::TracedValue,
             const HitTestRequest&,
             const HitTestLocation&,
             const HitTestResult&) {}

}  // namespace inspector_hit_test_event

namespace inspector_paint_image_event {

void Data(perfetto::TracedValue,
          const LayoutImage&,
          const gfx::RectF&,
          const gfx::RectF&) {}

void Data(perfetto::TracedValue, const LayoutObject&, const StyleImage&) {}

void Data(perfetto::TracedValue,
          Node*,
          const StyleImage&,
          const gfx::RectF&,
          const gfx::RectF&) {}

void Data(perfetto::TracedValue, const LayoutObject*, const ImageResourceContent&) {}

}  // namespace inspector_paint_image_event

String DescendantInvalidationSetToIdString(const InvalidationSet&) {
  return String();
}

namespace inspector_style_invalidator_invalidate_event {

const char kElementHasPendingInvalidationList[] =
    "Element has pending invalidation list";
const char kInvalidateCustomPseudo[] = "Invalidate custom pseudo-element";
const char kInvalidationSetInvalidatesSelf[] =
    "Invalidation set invalidates self";
const char kInvalidationSetInvalidatesSubtree[] =
    "Invalidation set invalidates subtree";
const char kInvalidationSetMatchedAttribute[] =
    "Invalidation set matched attribute";
const char kInvalidationSetMatchedClass[] = "Invalidation set matched class";
const char kInvalidationSetMatchedId[] = "Invalidation set matched id";
const char kInvalidationSetMatchedTagName[] =
    "Invalidation set matched tagName";
const char kInvalidationSetMatchedPart[] = "Invalidation set matched part";
const char kInvalidationSetInvalidatesTreeCounting[] =
    "Invalidation set invalidates tree-counting";
const char kInvalidationSetMatchedCustomPseudoName[] =
    "Invalidation set matched custom pseudo element name";

void Data(perfetto::TracedValue, Element&, const char*) {}

void SelectorPart(perfetto::TracedValue,
                  Element&,
                  const char*,
                  const InvalidationSet&,
                  const AtomicString&) {}

void InvalidationList(perfetto::TracedValue,
                      ContainerNode&,
                      const Vector<scoped_refptr<InvalidationSet>>&) {}

}  // namespace inspector_style_invalidator_invalidate_event

namespace inspector_animation_event {

void Data(perfetto::TracedValue, const Animation&) {}

}  // namespace inspector_animation_event

namespace inspector_animation_state_event {

void Data(perfetto::TracedValue, const Animation&) {}

}  // namespace inspector_animation_state_event

namespace inspector_animation_compositor_event {

void Data(perfetto::TracedValue,
          blink::CompositorAnimations::FailureReasons,
          const blink::PropertyHandleSet&) {}

}  // namespace inspector_animation_compositor_event

InvalidationSetToSelectorMap::IndexedSelector::IndexedSelector(
    StyleRule* style_rule,
    unsigned selector_index)
    : style_rule_(style_rule), selector_index_(selector_index) {}

void InvalidationSetToSelectorMap::IndexedSelector::Trace(
    Visitor*) const {}

StyleRule* InvalidationSetToSelectorMap::IndexedSelector::GetStyleRule() const {
  return style_rule_;
}

unsigned InvalidationSetToSelectorMap::IndexedSelector::GetSelectorIndex()
    const {
  return selector_index_;
}

String InvalidationSetToSelectorMap::IndexedSelector::GetSelectorText() const {
  return String();
}

const StyleSheetContents*
InvalidationSetToSelectorMap::IndexedSelector::GetStyleSheetContents() const {
  return nullptr;
}

void InvalidationSetToSelectorMap::StartOrStopTrackingIfNeeded(
    const TreeScope&,
    const StyleEngine&) {}

bool InvalidationSetToSelectorMap::IsTracking() {
  return false;
}

void InvalidationSetToSelectorMap::BeginStyleSheetContents(
    const StyleSheetContents*) {}

void InvalidationSetToSelectorMap::EndStyleSheetContents() {}

InvalidationSetToSelectorMap::StyleSheetContentsScope::StyleSheetContentsScope(
    const StyleSheetContents*) {}

InvalidationSetToSelectorMap::StyleSheetContentsScope::
    ~StyleSheetContentsScope() = default;

void InvalidationSetToSelectorMap::BeginSelector(StyleRule*, unsigned) {}

void InvalidationSetToSelectorMap::EndSelector() {}

InvalidationSetToSelectorMap::SelectorScope::SelectorScope(StyleRule*,
                                                           unsigned) {}

InvalidationSetToSelectorMap::SelectorScope::~SelectorScope() = default;

void InvalidationSetToSelectorMap::RecordInvalidationSetEntry(
    const InvalidationSet*,
    SelectorFeatureType,
    const AtomicString&) {}

void InvalidationSetToSelectorMap::BeginInvalidationSetCombine(
    const InvalidationSet*,
    const InvalidationSet*) {}

void InvalidationSetToSelectorMap::EndInvalidationSetCombine() {}

InvalidationSetToSelectorMap::CombineScope::CombineScope(
    const InvalidationSet*,
    const InvalidationSet*) {}

InvalidationSetToSelectorMap::CombineScope::~CombineScope() = default;

void InvalidationSetToSelectorMap::RemoveEntriesForInvalidationSet(
    const InvalidationSet*) {}

const InvalidationSetToSelectorMap::IndexedSelectorList*
InvalidationSetToSelectorMap::Lookup(const InvalidationSet*,
                                     SelectorFeatureType,
                                     const AtomicString&) {
  return nullptr;
}

const StyleSheetContents*
InvalidationSetToSelectorMap::LookupStyleSheetContentsForRule(
    const StyleRule*) {
  return nullptr;
}

InvalidationSetToSelectorMap::InvalidationSetToSelectorMap() = default;

void InvalidationSetToSelectorMap::Trace(Visitor*) const {}

void InvalidationSetToSelectorMap::RevisitActiveStyleSheets(
    const ActiveStyleSheetVector&,
    const StyleEngine&) {}

void InvalidationSetToSelectorMap::RevisitStylesheetOnce(
    const StyleEngine*,
    StyleSheetContents*,
    const RuleFeatureSet*) {}

Persistent<InvalidationSetToSelectorMap>&
InvalidationSetToSelectorMap::GetInstanceReference() {
  DEFINE_STATIC_LOCAL(Persistent<InvalidationSetToSelectorMap>, instance, ());
  return instance;
}

namespace inspector_commit_load_event {

void Data(perfetto::TracedValue, LocalFrame*) {}

}  // namespace inspector_commit_load_event

}  // namespace blink
