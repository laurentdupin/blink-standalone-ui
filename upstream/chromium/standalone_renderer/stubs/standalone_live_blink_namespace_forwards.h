#ifndef STANDALONE_RENDERER_STUBS_STANDALONE_LIVE_BLINK_NAMESPACE_FORWARDS_H_
#define STANDALONE_RENDERER_STUBS_STANDALONE_LIVE_BLINK_NAMESPACE_FORWARDS_H_

#include "../../third_party/perfetto/include/perfetto/tracing/event_context.h"
#include "mojo/public/cpp/system/data_pipe.h"
#include "services/network/public/cpp/header_util.h"
#include "services/network/public/cpp/client_hints.h"
#include "services/network/public/cpp/connection_allowlist.h"
#include "services/network/public/cpp/no_vary_search_header_parser.h"
#include "services/network/public/mojom/referrer_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/url_loader_factory.mojom.h"
#include "third_party/blink/public/mojom/css/preferred_contrast.mojom-blink-forward.h"
#include "third_party/skia/include/core/SkColor.h"
#include "third_party/blink/renderer/core/core_probe_sink.h"
#include "third_party/blink/renderer/platform/wtf/text/text_position.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

#include <memory>
#include <optional>
#include <set>
#include <utility>
#include <vector>

#include "third_party/blink/renderer/core/html/html_slot_element.h"

namespace perfetto::protos::pbzero {
class ChromeCompositorStateMachineV2 {
 public:
  class MajorStateV2 {
   public:
    enum LayerTreeFrameSinkState {};
    enum BeginImplFrameState {};
    enum BeginMainFrameState {};
    enum ForcedRedrawOnTimeoutState {};
  };
  class MinorStateV2 {
   public:
    enum TreePriority {};
  };
};
class ChromeCompositorSchedulerStateV2 {
 public:
  enum BeginImplFrameDeadlineMode {};
};
enum ChromeCompositorSchedulerActionV2 {};
}  // namespace perfetto::protos::pbzero

namespace network {
struct ResourceRequest;
class PendingSharedURLLoaderFactory;
class SharedURLLoaderFactory;
struct ParsedPermissionsPolicyDeclaration;
using ParsedPermissionsPolicy =
    std::vector<ParsedPermissionsPolicyDeclaration>;
class OptionalTrustTokenParams;
class CSPCheckResult;
struct ConnectionAllowlists;
struct IntegrityMetadata;
struct IntegrityPolicy;
struct URLLoaderCompletionStatus;
class OriginWithPossibleWildcards;
namespace mojom {
class PermissionsPolicyDataView;
class URLLoader;
class URLLoaderClient;
class URLLoaderFactory;
enum class AttributionSupport;
enum class CSPDisposition;
enum class CorsPreflightPolicy;
#define STANDALONE_RENDERER_HAS_CORS_ORIGIN_PATTERN_ENUMS 1
#define BLINK_STANDALONE_CORS_ENUMS_DEFINED 1
enum class CorsDomainMatchMode {
  kDisallowSubdomains,
  kAllowSubdomains,
  kAllowRegistrableDomains,
};
enum class CorsOriginAccessMatchPriority {
  kDefaultPriority,
  kLowPriority,
};
enum class CorsPortMatchMode {
  kAllowOnlySpecifiedPort,
  kAllowAnyPort,
};
enum class CredentialsMode;
enum class IntegrityAlgorithm;
enum class RedirectMode;
enum class RequestDestination;
enum class RequestMode;
enum class WebSandboxFlags : int32_t;
class URLResponseHead;
using URLResponseHeadPtr = std::unique_ptr<URLResponseHead>;
namespace blink {
enum class CSPDirectiveName;
enum class CSPRequireTrustedTypesFor;
struct TrustTokenParams;
using TrustTokenParamsPtr = TrustTokenParams*;
}  // namespace blink
}  // namespace mojom
}  // namespace network

namespace blink::network {
using ResourceRequest = ::network::ResourceRequest;
using PendingSharedURLLoaderFactory =
    ::network::PendingSharedURLLoaderFactory;
using SharedURLLoaderFactory = ::network::SharedURLLoaderFactory;
using ParsedPermissionsPolicyDeclaration =
    ::network::ParsedPermissionsPolicyDeclaration;
using ParsedPermissionsPolicy = ::network::ParsedPermissionsPolicy;
using OptionalTrustTokenParams = ::network::OptionalTrustTokenParams;
using CSPCheckResult = ::network::CSPCheckResult;
using ConnectionAllowlists = ::network::ConnectionAllowlists;
using IntegrityMetadata = ::network::IntegrityMetadata;
using IntegrityPolicy = ::network::IntegrityPolicy;
using URLLoaderCompletionStatus = ::network::URLLoaderCompletionStatus;
using OriginWithPossibleWildcards = ::network::OriginWithPossibleWildcards;
using ::network::IsSuccessfulStatus;
using ::network::NoVarySearchHasBooleanParamsMember;
using ::network::GetClientHintToNameMap;
}  // namespace blink::network

namespace blink {
class Document;
class CharacterData;
namespace probe {
void GetTextPosition(Document*, unsigned, const String*, TextPosition*);
void CharacterDataModified(CharacterData*);
}  // namespace probe
}  // namespace blink

namespace network::cors {
class OriginAccessEntry {
 public:
  enum class MatchResult {
    kDoesNotMatchOrigin,
    kMatchesOrigin,
    kMatchesOriginButIsPublicSuffix,
  };
};
}

namespace blink::network::cors {
using OriginAccessEntry = ::network::cors::OriginAccessEntry;
}

namespace blink::network::mojom {
using AttributionSupport = ::network::mojom::AttributionSupport;
using URLLoader = ::network::mojom::URLLoader;
using URLLoaderClient = ::network::mojom::URLLoaderClient;
using URLLoaderFactory = ::network::mojom::URLLoaderFactory;
using CSPDisposition = ::network::mojom::CSPDisposition;
using CSPDirectiveName = ::network::mojom::blink::CSPDirectiveName;
using CSPRequireTrustedTypesFor =
    ::network::mojom::blink::CSPRequireTrustedTypesFor;
using ContentSecurityPolicySource =
    ::network::mojom::ContentSecurityPolicySource;
using ContentSecurityPolicyType = ::network::mojom::ContentSecurityPolicyType;
using CorsPreflightPolicy = ::network::mojom::CorsPreflightPolicy;
using CorsDomainMatchMode = ::network::mojom::CorsDomainMatchMode;
using CorsOriginAccessMatchPriority =
    ::network::mojom::CorsOriginAccessMatchPriority;
using CorsPortMatchMode = ::network::mojom::CorsPortMatchMode;
using CredentialsMode = ::network::mojom::CredentialsMode;
using IntegrityAlgorithm = ::network::mojom::IntegrityAlgorithm;
using RedirectMode = ::network::mojom::RedirectMode;
using RequestDestination = ::network::mojom::RequestDestination;
using RequestMode = ::network::mojom::RequestMode;
using NavigationDeliveryType = ::network::mojom::NavigationDeliveryType;
using URLLoaderClientEndpointsPtr =
    ::network::mojom::URLLoaderClientEndpointsPtr;
using URLLoaderFactoryInterfaceBase =
    ::network::mojom::URLLoaderFactoryInterfaceBase;
using URLResponseHead = ::network::mojom::URLResponseHead;
using URLResponseHeadPtr = ::network::mojom::URLResponseHeadPtr;
using WebSandboxFlags = ::network::mojom::WebSandboxFlags;
class SchemefulSiteDataView;
}  // namespace blink::network::mojom

namespace blink::network::mojom::blink {
using RedirectMode = ::network::mojom::RedirectMode;
using TrustTokenParamsPtr = ::network::mojom::blink::TrustTokenParamsPtr;
using URLLoaderFactory = ::network::mojom::URLLoaderFactory;
}  // namespace blink::network::mojom::blink

namespace blink {
struct BlinkTransferableMessage {};
class DocumentLoader;
class Element;
class Frame;
class Node;
class AgentGroupScheduler;
class LocalFrame;
class ResourceResponse;
class MathMLFractionElement;
class MathMLOperatorElement;
class MathMLPaddedElement;
class MathMLSpaceElement;
class SVGFilterElement;
class SVGStyleElement;
enum class SameDocumentNavigationType;

#ifndef STANDALONE_RENDERER_MATHML_DOWNCAST_TRAITS_DEFINED
#define STANDALONE_RENDERER_MATHML_DOWNCAST_TRAITS_DEFINED
template <>
struct DowncastTraits<MathMLFractionElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<MathMLOperatorElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<MathMLPaddedElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<MathMLSpaceElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};
#endif  // STANDALONE_RENDERER_MATHML_DOWNCAST_TRAITS_DEFINED
template <>
struct DowncastTraits<SVGFilterElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<SVGStyleElement> {
  static bool AllowFrom(const Element&) { return false; }
  static bool AllowFrom(const Node&) { return false; }
};

namespace probe {
class UpdateLayout {
 public:
  template <typename... Args>
  explicit UpdateLayout(Args&&...) {}
};
class RecalculateStyle {
 public:
  template <typename... Args>
  explicit RecalculateStyle(Args&&...) {}
};
class FrameRelatedTask {
 public:
  template <typename... Args>
  explicit FrameRelatedTask(Args&&...) {}
};
class UserCallback {
 public:
  template <typename... Args>
  explicit UserCallback(Args&&...) {}
};
void WillRunJavaScriptDialog(LocalFrame*);
void DidRunJavaScriptDialog(LocalFrame*);
void LoadEventFired(LocalFrame*);
template <typename... Args>
void FrameScheduledNavigation(Args&&...) {}
template <typename... Args>
void FrameClearedScheduledNavigation(Args&&...) {}
template <typename... Args>
void FrameDetachedFromParent(Args&&...) {}
template <typename... Args>
void FrameAttachedToParent(Args&&...) {}
template <typename... Args>
void LifecycleEvent(Args&&...) {}
template <typename... Args>
void DidChangeViewport(Args&&...) {}
template <typename... Args>
void MediaQueryResultChanged(Args&&...) {}
template <typename... Args>
void DocumentDetached(Args&&...) {}
template <typename... Args>
void WillCreateDocumentParser(Args&&...) {}
template <typename... Args>
void BreakableLocation(Args&&...) {}
template <typename... Args>
void DidResizeMainFrame(Args&&...) {}
template <typename... Args>
void DomContentLoadedEventFired(Args&&...) {}
template <typename... Args>
void TopLayerElementsChanged(Args&&...) {}
template <typename... Args>
void DidNavigateWithinDocument(Args&&...) {}
template <typename... Args>
void DidReceiveData(Args&&...) {}
template <typename... Args>
void DidFinishLoading(Args&&...) {}
template <typename... Args>
void DidFailLoading(Args&&...) {}
template <typename... Args>
void WillSendNavigationRequest(Args&&...) {}
template <typename... Args>
void DidReceiveResourceResponse(Args&&...) {}
template <typename... Args>
void WillCommitLoad(Args&&...) {}
template <typename... Args>
void DidCommitLoad(Args&&...) {}
template <typename... Args>
void UpdateAffectedByStartingStylesFlag(Args&&...) {}
template <typename... Args>
void DidUpdateComputedStyle(Args&&...) {}
template <typename... Args>
void DidPushShadowRoot(Args&&...) {}
template <typename... Args>
void PseudoElementCreated(Args&&...) {}
template <typename... Args>
void PseudoElementDestroyed(Args&&...) {}
template <typename... Args>
void WillModifyDOMAttr(Args&&...) {}
template <typename... Args>
void DidModifyDOMAttr(Args&&...) {}
template <typename... Args>
void DidRemoveDOMAttr(Args&&...) {}
template <typename... Args>
void DidInvalidateStyleAttr(Args&&...) {}
template <typename... Args>
void NodeCreated(Args&&...) {}
template <typename... Args>
void DidPerformSlotDistribution(Args&&...) {}
template <typename... Args>
void ActiveStyleSheetsUpdated(Args&&...) {}
template <typename... Args>
void FontsUpdated(Args&&...) {}
template <typename... Args>
void WillHidePopover(Args&&...) {}
template <typename... Args>
void DidMutateStyleSheet(Args&&...) {}
template <typename... Args>
void DidReplaceStyleSheetText(Args&&...) {}
template <typename... Args>
void DidModifyAdoptedStyleSheets(Args&&...) {}
template <typename... Args>
void ForceStartingStyle(Args&&...) {}
template <typename... Args>
void ForcePseudoState(Args&&...) {}
template <typename... Args>
void DidCreateAnimation(Args&&...) {}
template <typename... Args>
void AnimationUpdated(Args&&...) {}
}  // namespace probe
}  // namespace blink

#endif  // STANDALONE_RENDERER_STUBS_STANDALONE_LIVE_BLINK_NAMESPACE_FORWARDS_H_
