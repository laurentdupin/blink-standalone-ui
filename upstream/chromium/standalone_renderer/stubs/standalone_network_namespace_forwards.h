#ifndef STANDALONE_RENDERER_STUBS_STANDALONE_NETWORK_NAMESPACE_FORWARDS_H_
#define STANDALONE_RENDERER_STUBS_STANDALONE_NETWORK_NAMESPACE_FORWARDS_H_

#define BLINK_STANDALONE_REFERRER_POLICY_ENUM_DEFINED
#define BLINK_STANDALONE_CORS_ENUMS_DEFINED

#include <memory>
#include <set>
#include <vector>

#include "unicode/utf8.h"
#define SkTraceEventCommon_DEFINED
#define kMaxRecursionDepth kMojoValidationMaxRecursionDepth
#include "third_party/blink/renderer/core/css/css_selector.h"
#include "third_party/blink/renderer/core/dom/pseudo_element.h"
#include "third_party/blink/renderer/core/editing/position.h"
#include "third_party/blink/renderer/core/dom/static_range.h"
#include "third_party/blink/renderer/core/html/html_slot_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_fraction_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_operator_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_padded_element.h"
#include "third_party/blink/renderer/core/mathml/mathml_space_element.h"
#include "standalone_renderer/stubs/third_party/blink/renderer/core/messaging/blink_transferable_message.h"
#include "standalone_renderer/stubs/third_party/blink/renderer/core/core_probe_sink.h"
#include "third_party/blink/renderer/core/svg/svg_script_element.h"
#include "third_party/blink/renderer/core/svg/svg_use_element.h"
#include "third_party/blink/renderer/platform/wtf/hash_set.h"
#include "third_party/blink/renderer/platform/wtf/text/code_point_iterator.h"
#include "third_party/blink/renderer/platform/wtf/text/text_position.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/blink/renderer/platform/instrumentation/tracing/trace_event.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"
#include "services/network/public/cpp/connection_allowlist.h"
#include "services/network/public/cpp/content_security_policy/content_security_policy.h"
#include "services/network/public/cpp/integrity_policy.h"
#include "services/network/public/cpp/permissions_policy/permissions_policy_declaration.h"
#include "services/network/public/mojom/content_security_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/cross_origin_opener_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/permissions_policy/permissions_policy_feature.mojom-blink-forward.h"
#include "services/network/public/mojom/fetch_api.mojom-blink-forward.h"
#include "services/network/public/mojom/integrity_algorithm.mojom-blink.h"
#include "services/network/public/mojom/referrer_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/restricted_cookie_manager.mojom-blink-forward.h"
#include "services/network/public/mojom/trust_tokens.mojom-blink-forward.h"
#include "services/network/public/mojom/url_loader_factory.mojom.h"
#include "services/network/public/mojom/url_response_head.mojom-forward.h"
#include "services/network/public/mojom/web_client_hints_types.mojom-shared.h"
#include "services/network/public/mojom/web_sandbox_flags.mojom-shared.h"
#include "services/network/public/mojom/web_sandbox_flags.mojom-blink-forward.h"
#undef kMaxRecursionDepth

#ifdef ERROR
#undef ERROR
#endif
#ifdef CALLBACK
#undef CALLBACK
#endif

namespace blink {
class DataTransfer;
class Document;
struct StyleScopeActivation;
struct StyleScopeActivations;

#ifndef STANDALONE_RENDERER_MATHML_DOWNCAST_TRAITS_DEFINED
#define STANDALONE_RENDERER_MATHML_DOWNCAST_TRAITS_DEFINED
template <>
struct DowncastTraits<MathMLFractionElement> {
  static bool AllowFrom(const Element& element) {
    return element.GetElementType() == ElementType::kMathMLFractionElement;
  }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<MathMLOperatorElement> {
  static bool AllowFrom(const Element& element) {
    return element.GetElementType() == ElementType::kMathMLOperatorElement;
  }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<MathMLPaddedElement> {
  static bool AllowFrom(const Element& element) {
    return element.GetElementType() == ElementType::kMathMLPaddedElement;
  }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<MathMLSpaceElement> {
  static bool AllowFrom(const Element& element) {
    return element.GetElementType() == ElementType::kMathMLSpaceElement;
  }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<SVGScriptElement> {
  static bool AllowFrom(const Element& element) {
    return element.GetElementType() == ElementType::kSVGScriptElement;
  }
  static bool AllowFrom(const Node&) { return false; }
};
template <>
struct DowncastTraits<SVGUseElement> {
  static bool AllowFrom(const Element& element) {
    return element.GetElementType() == ElementType::kSVGUseElement;
  }
  static bool AllowFrom(const Node&) { return false; }
};
#endif  // STANDALONE_RENDERER_MATHML_DOWNCAST_TRAITS_DEFINED

namespace probe {
inline void ForcePseudoState(Element*,
                             CSSSelector::PseudoType,
                             bool* result) {
  if (result) {
    *result = false;
  }
}

inline void GetTextPosition(Document*,
                            wtf_size_t,
                            const String*,
                            TextPosition* result) {
  if (result) {
    *result = TextPosition::MinimumPosition();
  }
}
}  // namespace probe
}  // namespace blink

namespace network {
class OptionalTrustTokenParams;
class PermissionsPolicy;
class PendingSharedURLLoaderFactory;
class SharedURLLoaderFactory;
struct ParsedPermissionsPolicyDeclaration;
enum class MetaCHType;
}  // namespace network

namespace blink::network {
using ConnectionAllowlists = ::network::ConnectionAllowlists;
using CSPCheckResult = ::network::CSPCheckResult;
using IntegrityPolicy = ::network::IntegrityPolicy;
using MetaCHType = ::network::MetaCHType;
using OptionalTrustTokenParams = ::network::OptionalTrustTokenParams;
using OriginWithPossibleWildcards = ::network::OriginWithPossibleWildcards;
using ParsedPermissionsPolicy = ::network::ParsedPermissionsPolicy;
using ParsedPermissionsPolicyDeclaration =
    ::network::ParsedPermissionsPolicyDeclaration;
using PendingSharedURLLoaderFactory = ::network::PendingSharedURLLoaderFactory;
using PermissionsPolicy = ::network::PermissionsPolicy;
using ResourceRequest = ::network::ResourceRequest;
using SharedURLLoaderFactory = ::network::SharedURLLoaderFactory;
}  // namespace blink::network

namespace blink::network::mojom {
using CSPDisposition = ::network::mojom::CSPDisposition;
using CorsPreflightPolicy = ::network::mojom::CorsPreflightPolicy;
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
using CredentialsMode = ::network::mojom::CredentialsMode;
using RedirectMode = ::network::mojom::RedirectMode;
using ReferrerPolicy = ::network::mojom::ReferrerPolicy;
using RequestDestination = ::network::mojom::RequestDestination;
using RequestMode = ::network::mojom::RequestMode;
using URLLoader = ::network::mojom::URLLoader;
using URLLoaderClient = ::network::mojom::URLLoaderClient;
using URLLoaderFactory = ::network::mojom::URLLoaderFactory;
using URLResponseHeadPtr = ::network::mojom::URLResponseHeadPtr;
using WebSandboxFlags = ::network::mojom::WebSandboxFlags;
using WebClientHintsType = ::network::mojom::WebClientHintsType;

class SchemefulSiteDataView;
}  // namespace blink::network::mojom

namespace blink::network::cors {
class OriginAccessEntry {
 public:
  enum class MatchResult {
    kDoesNotMatchOrigin,
    kMatchesOrigin,
    kMatchesOriginButIsPublicSuffix,
  };
};
}  // namespace blink::network::cors

namespace blink::network::mojom::blink {
using CoopAccessReportType = ::network::mojom::blink::CoopAccessReportType;
using CrossOriginOpenerPolicyReporter =
    ::network::mojom::blink::CrossOriginOpenerPolicyReporter;
using CrossOriginOpenerPolicyReporterParamsPtr =
    ::network::mojom::blink::CrossOriginOpenerPolicyReporterParamsPtr;
using IntegrityAlgorithm = ::network::mojom::blink::IntegrityAlgorithm;
using ReferrerPolicy = ::network::mojom::blink::ReferrerPolicy;
using RedirectMode = ::network::mojom::blink::RedirectMode;
using TrustTokenParamsPtr = ::network::mojom::blink::TrustTokenParamsPtr;
}  // namespace blink::network::mojom::blink

#include "third_party/blink/renderer/core/frame/csp/content_security_policy.h"

#endif  // STANDALONE_RENDERER_STUBS_STANDALONE_NETWORK_NAMESPACE_FORWARDS_H_
