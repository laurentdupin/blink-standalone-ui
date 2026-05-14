#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FRAME_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FRAME_MOJOM_BLINK_FORWARD_H_
#include <memory>
#include <functional>

#include "base/memory/scoped_refptr.h"
#include "base/memory/read_only_shared_memory_region.h"
#include "base/time/time.h"
#include "base/values.h"
#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "mojo/public/cpp/bindings/pending_associated_receiver.h"
#include "mojo/public/cpp/bindings/pending_associated_remote.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "services/network/public/mojom/source_location.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/confidence_level.mojom-blink-forward.h"
#include "third_party/blink/public/common/tokens/tokens.h"
#include "third_party/blink/public/mojom/devtools/console_message.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/devtools/devtools_agent.mojom-shared.h"
#include "third_party/blink/public/mojom/frame/frame_owner_properties.mojom-blink.h"
#include "third_party/blink/public/mojom/frame/lifecycle.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/media_player_action.mojom-blink.h"
#include "third_party/blink/public/mojom/frame/reporting_observer.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/user_activation_notification_type.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/input/focus_type.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/fetch/fetch_api_request.mojom-shared.h"
#include "third_party/blink/public/mojom/loader/request_context_frame_type.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/messaging/delegated_capability.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/navigation/navigation_api_history_entry_arrays.mojom-blink.h"
#include "third_party/blink/public/mojom/navigation/navigation_params.mojom-blink.h"
#include "third_party/blink/public/mojom/permissions/permission.mojom-blink.h"
#include "third_party/blink/public/mojom/use_counter/metrics/web_feature.mojom-shared.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"

namespace base {
class ListValue;
class ReadOnlySharedMemoryRegion;
class UnguessableToken;
class TimeTicks;
}
namespace cc {
enum class BrowserControlsState;
struct BrowserControlsOffsetTagModifications;
}
namespace gfx {
class Point;
class Rect;
class Size;
}
namespace net {
enum class HttpConnectionInfo;
}
namespace network {
struct URLLoaderCompletionStatus;
}
namespace network::mojom::blink {
struct CSPViolation {};
using CSPViolationPtr = std::unique_ptr<CSPViolation>;
struct CrossOriginOpenerPolicyReporterParams;
using CrossOriginOpenerPolicyReporterParamsPtr =
    CrossOriginOpenerPolicyReporterParams*;
struct LoadTimingInfo {};
using LoadTimingInfoPtr = std::unique_ptr<LoadTimingInfo>;
}
namespace blink::network::mojom::blink {
using CSPViolationPtr = ::network::mojom::blink::CSPViolationPtr;
using LoadTimingInfoPtr = ::network::mojom::blink::LoadTimingInfoPtr;
using SourceLocationPtr = ::network::mojom::blink::SourceLocationPtr;
}
namespace blink {
class KURL;
class SecurityOrigin;
struct BlinkTransferableMessage;
struct FramePolicy;
class String;
}  // namespace blink
namespace blink::mojom::blink {
inline constexpr wtf_size_t kMaxTitleChars = 4096;
enum class StorageTypeAccessed {
  kCacheStorage,
  kIndexedDB,
  kFileSystem,
  kWebLocks,
  kLocalStorage,
  kSessionStorage,
};
enum class WindowProxyAccessType {
  kIndexedGetter,
  kNamedGetter,
  kGetter,
  kSetter,
};
enum class SameDocumentNavigationType {
  kFragment = 0,
  kHistoryApi = 1,
  kNavigationApiIntercept = 2,
  kPrerenderNoVarySearchActivation = 3,
};
enum class TraverseCancelledReason {
  kAbort,
  kCancel,
};
enum class NavigationApiEntryRestoreReason {
  kNavigation,
  kReload,
};
enum class ViewTransitionSameOriginOptIn {
  kEnabled,
  kDisabled,
};
enum class ForceHistoryPush {
  kNo,
  kYes,
};
enum class PluginActionType {
  kNone,
};
class LocalFrameHost {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.LocalFrameHost";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_;
  void ReceivedDelegatedCapability(DelegatedCapability) {}
  void DidInferColorScheme(PreferredColorScheme) {}
  template <typename... Args>
  void BubbleLogicalScrollInParentFrame(Args&&...) {}
  template <typename... Args>
  void SuddenTerminationDisablerChanged(Args&&...) {}
  void DidFocusFrame() {}
  template <typename... Args>
  void TextSelectionChanged(Args&&...) {}
  template <typename... Args>
  void DidBlockNavigation(Args&&...) {}
  template <typename... Args>
  void DidChangeOpener(Args&&...) {}
  template <typename... Args>
  void UpdateUserActivationState(Args&&...) {}
  void DidConsumeHistoryUserActivation() {}
  template <typename... Args>
  void UpdateFaviconURL(Args&&...) {}
  template <typename... Args>
  void DownloadURL(Args&&...) {}
  template <typename... Args>
  void IssueKeepAliveHandle(Args&&...) {}
  template <typename... Args>
  void NotifyStorageAccessed(Args&&...) {}
  template <typename... Args>
  void FrameSizeChanged(Args&&...) {}
  template <typename... Args>
  void ScrollRectToVisibleInParentFrame(Args&&...) {}
  template <typename... Args>
  void VisibilityChanged(Args&&...) {}
  template <typename... Args>
  void NotifyDocumentInteractive(Args&&...) {}
  template <typename... Args>
  void UpdateTitle(Args&&...) {}
  template <typename... Args>
  void FocusedElementChanged(Args&&...) {}
  template <typename... Args>
  void DocumentOnLoadCompleted(Args&&...) {}
  template <typename... Args>
  void DidFinishLoad(Args&&...) {}
  template <typename... Args>
  void UpdateApplicationTitle(Args&&...) {}
  template <typename... Args>
  void HadStickyUserActivationBeforeNavigationChanged(Args&&...) {}
};
class LocalFrameHost::Proxy_ : public LocalFrameHost {
 public:
  template <typename... Args>
  explicit Proxy_(Args&&...) {}
};
class NonAssociatedLocalFrameHost {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] =
      "blink.mojom.NonAssociatedLocalFrameHost";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_;
  template <typename... Args>
  void MaybeStartOutermostMainFrameNavigation(Args&&...) {}
};
class NonAssociatedLocalFrameHost::Proxy_
    : public NonAssociatedLocalFrameHost {
 public:
  template <typename... Args>
  explicit Proxy_(Args&&...) {}
};
using RequestContextType = ::blink::mojom::RequestContextType;
class LocalFrame {
 public:
  using GetTextSurroundingSelectionCallback = std::function<void()>;
  using BeforeUnloadCallback = std::function<void()>;
  using RequestVideoFrameAtWithBoundsHintCallback = std::function<void()>;
  using JavaScriptMethodExecuteRequestCallback = std::function<void()>;
  using JavaScriptExecuteRequestCallback = std::function<void()>;
  using JavaScriptExecuteRequestForTestsCallback = std::function<void()>;
  using JavaScriptExecuteRequestInIsolatedWorldCallback = std::function<void()>;
  using GetSavableResourceLinksCallback = std::function<void()>;
  using GetCanonicalUrlForSharingCallback = std::function<void()>;
  using GetOpenGraphMetadataCallback = std::function<void()>;
  using UpdatePrerenderURLCallback = std::function<void()>;
  using SnapshotDocumentForViewTransitionCallback = std::function<void()>;
  using GetScrollPositionCallback = std::function<void()>;

  virtual ~LocalFrame() = default;
  virtual void GetTextSurroundingSelection(uint32_t,
                                           GetTextSurroundingSelectionCallback) {}
  virtual void SendInterventionReport(
      const ::blink::String&,
      const ::blink::String&,
      const std::optional<::blink::FrameToken>&) {}
  virtual void SetFrameOwnerProperties(FrameOwnerPropertiesPtr) {}
  virtual void NotifyUserActivation(UserActivationNotificationType) {}
  virtual void NotifyVirtualKeyboardOverlayRect(const gfx::Rect&) {}
  virtual void ShowInterestInElement(int) {}
  virtual void AddMessageToConsole(ConsoleMessageLevel,
                                   const ::blink::String&,
                                   bool) {}
  virtual void SwapInImmediately() {}
  virtual void CheckCompleted() {}
  virtual void StopLoading() {}
  virtual void Collapse(bool) {}
  virtual void EnableViewSourceMode() {}
  virtual void Focus() {}
  virtual void ClearFocusedElement() {}
  virtual void CopyImageAt(const gfx::Point&) {}
  virtual void SaveImageAt(const gfx::Point&) {}
  virtual void ReportBlinkFeatureUsage(const ::blink::Vector<WebFeature>&) {}
  virtual void RenderFallbackContent() {}
  virtual void BeforeUnload(bool, bool, BeforeUnloadCallback) {}
  virtual void MediaPlayerActionAt(const gfx::Point&, MediaPlayerActionPtr) {}
  virtual void RequestVideoFrameAtWithBoundsHint(
      const gfx::Point&,
      const gfx::Size&,
      int,
      RequestVideoFrameAtWithBoundsHintCallback) {}
  virtual void AdvanceFocusInFrame(
      FocusType,
      const std::optional<::blink::RemoteFrameToken>&) {}
  virtual void AdvanceFocusForIME(FocusType) {}
  virtual void ReportContentSecurityPolicyViolation(
      ::network::mojom::blink::CSPViolationPtr) {}
  virtual void DidUpdateFramePolicy(const ::blink::FramePolicy&) {}
  virtual void OnFrameVisibilityChanged(FrameVisibility) {}
  virtual void PostMessageEvent(
      const std::optional<::blink::RemoteFrameToken>&,
      const ::scoped_refptr<const ::blink::SecurityOrigin>&,
      const ::scoped_refptr<const ::blink::SecurityOrigin>&,
      ::blink::BlinkTransferableMessage) = 0;
  virtual void JavaScriptMethodExecuteRequest(
      const ::blink::String&,
      const ::blink::String&,
      base::ListValue,
      bool,
      JavaScriptMethodExecuteRequestCallback) {}
  virtual void JavaScriptExecuteRequest(const ::blink::String&,
                                        bool,
                                        JavaScriptExecuteRequestCallback) {}
  virtual void JavaScriptExecuteRequestForTests(
      const ::blink::String&,
      bool,
      bool,
      bool,
      int32_t,
      JavaScriptExecuteRequestForTestsCallback) {}
  virtual void JavaScriptExecuteRequestInIsolatedWorld(
      const ::blink::String&,
      bool,
      int32_t,
      JavaScriptExecuteRequestInIsolatedWorldCallback) {}
  virtual void BindReportingObserver(
      mojo::PendingReceiver<ReportingObserver>) {}
  virtual void UpdateOpener(const std::optional<::blink::FrameToken>&) {}
  virtual void GetSavableResourceLinks(GetSavableResourceLinksCallback) {}
  virtual void MixedContentFound(
      const ::blink::KURL&,
      const ::blink::KURL&,
      RequestContextType,
      bool,
      const ::blink::KURL&,
      bool,
      ::network::mojom::blink::SourceLocationPtr) {}
  virtual void BindDevToolsAgent(
      mojo::PendingAssociatedRemote<DevToolsAgentHost>,
      mojo::PendingAssociatedReceiver<DevToolsAgent>) {}
  virtual void HandleRendererDebugURL(const ::blink::KURL&) {}
  virtual void GetCanonicalUrlForSharing(GetCanonicalUrlForSharingCallback) {}
  virtual void GetOpenGraphMetadata(GetOpenGraphMetadataCallback) {}
  virtual void SetNavigationApiHistoryEntriesForRestore(
      NavigationApiHistoryEntryArraysPtr,
      NavigationApiEntryRestoreReason) {}
  virtual void UpdatePrerenderURL(const ::blink::KURL&,
                                  UpdatePrerenderURLCallback) {}
  virtual void NotifyNavigationApiOfDisposedEntries(
      const ::blink::Vector<::blink::String>&) {}
  virtual void TraverseCancelled(const ::blink::String&,
                                 TraverseCancelledReason) {}
  virtual void DispatchNavigateEventForCrossDocumentTraversal(
      const ::blink::KURL&,
      const std::string&,
      bool) {}
  virtual void SnapshotDocumentForViewTransition(
      const ::blink::ViewTransitionToken&,
      PageSwapEventParamsPtr,
      SnapshotDocumentForViewTransitionCallback) {}
  virtual void NotifyViewTransitionAbortedToOldDocument() {}
  virtual void DispatchPageSwap(PageSwapEventParamsPtr) {}
  virtual void AddResourceTimingEntryForFailedSubframeNavigation(
      const ::blink::FrameToken&,
      const ::blink::KURL&,
      base::TimeTicks,
      base::TimeTicks,
      base::TimeTicks,
      base::TimeTicks,
      uint32_t,
      const ::blink::String&,
      ::network::mojom::blink::LoadTimingInfoPtr,
      net::HttpConnectionInfo,
      const ::blink::String&,
      bool,
      bool,
      const ::blink::String&,
      const ::network::URLLoaderCompletionStatus&) {}
  virtual void GetScrollPosition(GetScrollPositionCallback) {}
};
class LocalMainFrame {
 public:
  using ClosePageCallback = std::function<void()>;
  using GetFullPageSizeCallback = std::function<void()>;
  using DiscardCallback = std::function<void()>;
  virtual ~LocalMainFrame() = default;
  virtual void AnimateDoubleTapZoom(const gfx::Point&, const gfx::Rect&) {}
  virtual void SetScaleFactor(float) {}
  virtual void ClosePage(ClosePageCallback) {}
  virtual void GetFullPageSize(GetFullPageSizeCallback) {}
  virtual void PluginActionAt(const gfx::Point&, PluginActionType) {}
  virtual void SetInitialFocus(bool) {}
  virtual void EnablePreferredSizeChangedMode() {}
  virtual void ZoomToFindInPageRect(const gfx::Rect&) {}
  virtual void InstallCoopAccessMonitor(
      const ::blink::FrameToken&,
      ::network::mojom::blink::CrossOriginOpenerPolicyReporterParamsPtr) {}
  virtual void UpdateBrowserControlsState(
      cc::BrowserControlsState,
      cc::BrowserControlsState,
      bool,
      const std::optional<cc::BrowserControlsOffsetTagModifications>&) {}
  virtual void Discard(DiscardCallback) {}
  virtual void FinalizeNavigationConfidence(double, ConfidenceLevel) {}
  virtual void SetV8CompileHints(base::ReadOnlySharedMemoryRegion) {}
};
class RemoteFrameHost {
 public:
  class Proxy_ {};
  static constexpr bool PassesAssociatedKinds_ = false;
};
class RemoteFrame;
class NavigationStateKeepAliveHandle;
class NavigationResumeDeferredCommitListener;
struct BlockingDetails;
using BlockingDetailsPtr = std::unique_ptr<BlockingDetails>;
}

namespace blink::mojom {

using ForceHistoryPush = ::blink::mojom::blink::ForceHistoryPush;
using SameDocumentNavigationType =
    ::blink::mojom::blink::SameDocumentNavigationType;
using StorageTypeAccessed = ::blink::mojom::blink::StorageTypeAccessed;
using WindowProxyAccessType = ::blink::mojom::blink::WindowProxyAccessType;

class NavigationStateKeepAliveHandleInterfaceBase {};
class NavigationResumeDeferredCommitListener;

enum class ParentResourceTimingAccess {
  kDoNotReport,
  kReport,
  kReportWithoutResponseDetails,
};

using PermissionName = ::blink::mojom::blink::PermissionName;
using PermissionStatus = ::blink::mojom::blink::PermissionStatus;

}  // namespace blink::mojom

namespace blink::mojom::blink {

using ParentResourceTimingAccess =
    ::blink::mojom::ParentResourceTimingAccess;

}  // namespace blink::mojom::blink
#endif
