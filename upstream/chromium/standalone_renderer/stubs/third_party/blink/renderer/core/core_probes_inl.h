// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_CORE_PROBES_INL_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_CORE_PROBES_INL_H_

#include "third_party/blink/renderer/core/probe/core_probes.h"

namespace blink {
class CharacterData;
class Node;
class ContainerNode;
class CSSStyleSheet;
class Document;
class Element;
class ExecutionContext;
class FontCustomPlatformData;
class FontFace;
class LocalFrame;
class String;
namespace probe {

class RecalculateStyle {
 public:
  explicit RecalculateStyle(Document*) {}
  RecalculateStyle(const RecalculateStyle&) = delete;
  RecalculateStyle& operator=(const RecalculateStyle&) = delete;
  ~RecalculateStyle() = default;
};

class UserCallback {
 public:
  template <typename... Args>
  explicit UserCallback(Args&&...) {}
  UserCallback(const UserCallback&) = delete;
  UserCallback& operator=(const UserCallback&) = delete;
  ~UserCallback() = default;
};

#define STANDALONE_RENDERER_SCOPED_PROBE(name) \
  class name {                                  \
   public:                                      \
    template <typename... Args>                 \
    explicit name(Args&&...) {}                 \
    name(const name&) = delete;                 \
    name& operator=(const name&) = delete;      \
    ~name() = default;                          \
  }

STANDALONE_RENDERER_SCOPED_PROBE(UpdateLayout);
STANDALONE_RENDERER_SCOPED_PROBE(EvaluateScriptBlock);
STANDALONE_RENDERER_SCOPED_PROBE(ExecuteScript);
STANDALONE_RENDERER_SCOPED_PROBE(CallFunction);
STANDALONE_RENDERER_SCOPED_PROBE(InvokeCallback);
STANDALONE_RENDERER_SCOPED_PROBE(InvokeEventHandler);
STANDALONE_RENDERER_SCOPED_PROBE(UserEntryPoint);
STANDALONE_RENDERER_SCOPED_PROBE(FrameRelatedTask);
STANDALONE_RENDERER_SCOPED_PROBE(V8Compile);

#undef STANDALONE_RENDERER_SCOPED_PROBE

#define STANDALONE_RENDERER_PROBE_FUNCTION(name) \
  template <typename... Args>                    \
  inline void name(Args&&...) {}

STANDALONE_RENDERER_PROBE_FUNCTION(DidClearDocumentOfWindowObject)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCreateMainWorldContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidModifyAdoptedStyleSheets)
STANDALONE_RENDERER_PROBE_FUNCTION(WillChangeStyleElement)
STANDALONE_RENDERER_PROBE_FUNCTION(DidPerformSlotDistribution)
STANDALONE_RENDERER_PROBE_FUNCTION(WillPopShadowRoot)
STANDALONE_RENDERER_PROBE_FUNCTION(WillSendXMLHttpOrFetchNetworkRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCreateCanvasContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCreateOffscreenCanvasContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFireWebGLError)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFireWebGLWarning)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFireWebGLErrorOrWarning)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyAcceptLanguageOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyHardwareConcurrencyOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyDataSaverOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyUserAgentOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyUserAgentMetadataOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(DidBlockRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(DidChangeResourcePriority)
STANDALONE_RENDERER_PROBE_FUNCTION(PrepareRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(WillSendRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(WillSendNavigationRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(WillSendWorkerMainRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(MarkResourceAsCached)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveResourceResponse)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveData)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveBlob)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveEncodedDataLength)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFinishLoading)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveCorsRedirectResponse)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFailLoading)
STANDALONE_RENDERER_PROBE_FUNCTION(WillSendEventSourceRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(WillDispatchEventSourceEvent)
STANDALONE_RENDERER_PROBE_FUNCTION(WillLoadXHR)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFinishXHR)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFinishSyncXHR)
STANDALONE_RENDERER_PROBE_FUNCTION(ScriptImported)
STANDALONE_RENDERER_PROBE_FUNCTION(ScriptExecutionBlockedByCSP)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveScriptResponse)
STANDALONE_RENDERER_PROBE_FUNCTION(LoadEventFired)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameAttachedToParent)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameDetachedFromParent)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameSubtreeWillBeDetached)
STANDALONE_RENDERER_PROBE_FUNCTION(DidStartProvisionalLoad)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFailProvisionalLoad)
STANDALONE_RENDERER_PROBE_FUNCTION(WillCommitLoad)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCommitLoad)
STANDALONE_RENDERER_PROBE_FUNCTION(DidNavigateWithinDocument)
STANDALONE_RENDERER_PROBE_FUNCTION(DidRestoreFromBackForwardCache)
STANDALONE_RENDERER_PROBE_FUNCTION(DidOpenDocument)
STANDALONE_RENDERER_PROBE_FUNCTION(WillCreateDocumentParser)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameDocumentUpdated)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameOwnerContentUpdated)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameStartedLoading)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameStoppedLoading)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameRequestedNavigation)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameScheduledNavigation)
STANDALONE_RENDERER_PROBE_FUNCTION(FrameClearedScheduledNavigation)
STANDALONE_RENDERER_PROBE_FUNCTION(WillCreateWebSocket)
STANDALONE_RENDERER_PROBE_FUNCTION(WillSendWebSocketHandshakeRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveWebSocketHandshakeResponse)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCloseWebSocket)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveWebSocketMessage)
STANDALONE_RENDERER_PROBE_FUNCTION(DidSendWebSocketMessage)
STANDALONE_RENDERER_PROBE_FUNCTION(DidReceiveWebSocketMessageError)
STANDALONE_RENDERER_PROBE_FUNCTION(WebTransportCreated)
STANDALONE_RENDERER_PROBE_FUNCTION(WebTransportConnectionEstablished)
STANDALONE_RENDERER_PROBE_FUNCTION(WebTransportClosed)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectTCPSocketCreated)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectTCPSocketOpened)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectTCPSocketAborted)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectTCPSocketClosed)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectTCPSocketChunkSent)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectTCPSocketChunkReceived)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketCreated)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketOpened)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketAborted)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketClosed)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketChunkSent)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketChunkReceived)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketJoinedMulticastGroup)
STANDALONE_RENDERER_PROBE_FUNCTION(DirectUDPSocketLeftMulticastGroup)
STANDALONE_RENDERER_PROBE_FUNCTION(WillCreateP2PSocketUdp)
STANDALONE_RENDERER_PROBE_FUNCTION(LayerTreeDidChange)
STANDALONE_RENDERER_PROBE_FUNCTION(LayerTreePainted)
STANDALONE_RENDERER_PROBE_FUNCTION(PseudoElementDestroyed)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCreateAnimation)
STANDALONE_RENDERER_PROBE_FUNCTION(AnimationUpdated)
STANDALONE_RENDERER_PROBE_FUNCTION(WindowOpen)
STANDALONE_RENDERER_PROBE_FUNCTION(ConsoleMessageAdded)
STANDALONE_RENDERER_PROBE_FUNCTION(InspectorIssueAdded)
STANDALONE_RENDERER_PROBE_FUNCTION(WillRunJavaScriptDialog)
STANDALONE_RENDERER_PROBE_FUNCTION(DidRunJavaScriptDialog)
STANDALONE_RENDERER_PROBE_FUNCTION(DocumentWriteFetchScript)
STANDALONE_RENDERER_PROBE_FUNCTION(DidChangeViewport)
STANDALONE_RENDERER_PROBE_FUNCTION(WillHandlePromise)
STANDALONE_RENDERER_PROBE_FUNCTION(ShouldForceCorsPreflight)
STANDALONE_RENDERER_PROBE_FUNCTION(ShouldBlockRequest)
STANDALONE_RENDERER_PROBE_FUNCTION(ShouldBypassServiceWorker)
STANDALONE_RENDERER_PROBE_FUNCTION(ConsoleTimeStamp)
STANDALONE_RENDERER_PROBE_FUNCTION(WillStartDebuggerTask)
STANDALONE_RENDERER_PROBE_FUNCTION(DidFinishDebuggerTask)
STANDALONE_RENDERER_PROBE_FUNCTION(LifecycleEvent)
STANDALONE_RENDERER_PROBE_FUNCTION(PaintTiming)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCreateAudioContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidCloseAudioContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidResumeAudioContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidSuspendAudioContext)
STANDALONE_RENDERER_PROBE_FUNCTION(DidProduceCompilationCache)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyCompilationModeOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(NodeCreated)
STANDALONE_RENDERER_PROBE_FUNCTION(FileChooserOpened)
STANDALONE_RENDERER_PROBE_FUNCTION(PlayerErrorsRaised)
STANDALONE_RENDERER_PROBE_FUNCTION(PlayerEventsAdded)
STANDALONE_RENDERER_PROBE_FUNCTION(PlayerMessagesLogged)
STANDALONE_RENDERER_PROBE_FUNCTION(PlayerPropertiesChanged)
STANDALONE_RENDERER_PROBE_FUNCTION(PlayerCreated)
STANDALONE_RENDERER_PROBE_FUNCTION(SetDevToolsIds)
STANDALONE_RENDERER_PROBE_FUNCTION(LocalFontsEnabled)
STANDALONE_RENDERER_PROBE_FUNCTION(GetDisabledImageTypes)
STANDALONE_RENDERER_PROBE_FUNCTION(OnContentSecurityPolicyViolation)
STANDALONE_RENDERER_PROBE_FUNCTION(IsCacheDisabled)
STANDALONE_RENDERER_PROBE_FUNCTION(ShouldApplyDevtoolsCookieSettingOverrides)
STANDALONE_RENDERER_PROBE_FUNCTION(PerformanceEntryAdded)
STANDALONE_RENDERER_PROBE_FUNCTION(ApplyAutomationOverride)
STANDALONE_RENDERER_PROBE_FUNCTION(DidAddSpeculationRuleSet)
STANDALONE_RENDERER_PROBE_FUNCTION(DidRemoveSpeculationRuleSet)
STANDALONE_RENDERER_PROBE_FUNCTION(SpeculationCandidatesUpdated)
STANDALONE_RENDERER_PROBE_FUNCTION(DidInitializeFrameWidget)
STANDALONE_RENDERER_PROBE_FUNCTION(UpdateScrollableFlag)
STANDALONE_RENDERER_PROBE_FUNCTION(UpdateAdRelatedState)
STANDALONE_RENDERER_PROBE_FUNCTION(WillHidePopover)
STANDALONE_RENDERER_PROBE_FUNCTION(WebMCPToolAdded)
STANDALONE_RENDERER_PROBE_FUNCTION(WebMCPToolRemoved)
STANDALONE_RENDERER_PROBE_FUNCTION(WebMCPToolExecuted)
STANDALONE_RENDERER_PROBE_FUNCTION(WebMCPToolResponded)
STANDALONE_RENDERER_PROBE_FUNCTION(WebMCPToolFailed)

#undef STANDALONE_RENDERER_PROBE_FUNCTION

inline void ActiveStyleSheetsUpdated(Document*) {}
inline void CharacterDataModified(CharacterData*) {}
inline void WillInsertDOMNode(ContainerNode*) {}
inline void DidInsertDOMNode(Node*) {}
inline void WillRemoveDOMNode(Node*) {}
inline void DidMutateStyleSheet(Document*, CSSStyleSheet*) {}
inline void DidReplaceStyleSheetText(Document*, CSSStyleSheet*, const String&) {}
inline void DocumentDetached(Document*) {}
inline void MediaQueryResultChanged(Document*) {}
inline void BreakableLocation(ExecutionContext*, const char*) {}
inline void DidResizeMainFrame(LocalFrame*) {}
inline void DomContentLoadedEventFired(LocalFrame*) {}
inline void TopLayerElementsChanged(Document*) {}
template <typename... Args>
inline void UpdateAffectedByStartingStylesFlag(Args&&...) {}
template <typename... Args>
inline void DidUpdateComputedStyle(Args&&...) {}
template <typename... Args>
inline void DidPushShadowRoot(Args&&...) {}
template <typename... Args>
inline void PseudoElementCreated(Args&&...) {}
template <typename... Args>
inline void WillModifyDOMAttr(Args&&...) {}
template <typename... Args>
inline void DidModifyDOMAttr(Args&&...) {}
template <typename... Args>
inline void DidRemoveDOMAttr(Args&&...) {}
template <typename... Args>
inline void DidInvalidateStyleAttr(Args&&...) {}
inline void FontsUpdated(ExecutionContext*,
                         const FontFace*,
                         const String&,
                         const FontCustomPlatformData*) {}
inline void ForceStartingStyle(Element*, bool*) {}

}  // namespace probe
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_CORE_PROBES_INL_H_
