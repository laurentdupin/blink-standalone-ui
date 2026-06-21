#ifndef STANDALONE_RENDERER_STUBS_STANDALONE_NETWORK_NAMESPACE_FORWARDS_H_
#define STANDALONE_RENDERER_STUBS_STANDALONE_NETWORK_NAMESPACE_FORWARDS_H_

#if defined(STANDALONE_RENDERER_NO_BLINK_PREINCLUDE)

#ifdef ERROR
#undef ERROR
#endif
#ifdef CALLBACK
#undef CALLBACK
#endif
#if defined(STANDALONE_RENDERER_NEEDS_WIN_CALLBACK) && !defined(CALLBACK)
#define CALLBACK __stdcall
#endif

#else

#define BLINK_STANDALONE_REFERRER_POLICY_ENUM_DEFINED
#define BLINK_STANDALONE_CORS_ENUMS_DEFINED

#include <memory>
#include <set>
#include <vector>

#include "unicode/utf8.h"
#define kMaxRecursionDepth kMojoValidationMaxRecursionDepth
#include "third_party/blink/renderer/core/css/css_selector.h"
#include "third_party/blink/renderer/core/dom/pseudo_element.h"
#include "third_party/blink/renderer/core/editing/position.h"
#include "third_party/blink/renderer/core/dom/static_range.h"
#include "third_party/blink/renderer/core/html/html_slot_element.h"
#include "third_party/blink/renderer/core/core_probe_sink.h"
#include "third_party/blink/renderer/core/svg/svg_script_element.h"
#include "third_party/blink/renderer/core/svg/svg_use_element.h"
#include "third_party/blink/renderer/platform/wtf/hash_set.h"
#include "third_party/blink/renderer/platform/wtf/text/code_point_iterator.h"
#include "third_party/blink/renderer/platform/wtf/text/text_position.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "../../third_party/perfetto/include/perfetto/tracing/traced_value.h"
#include "components/viz/common/quads/compositor_frame_metadata.h"
#include "gpu/ipc/common/exported_shared_image_mojom_traits.h"
#include "services/viz/public/cpp/compositing/frame_sink_bundle_id_mojom_traits.h"
#include "skia/public/mojom/image_info_mojom_traits.h"
#include "skia/public/mojom/surface_origin_mojom_traits.h"
#include "ui/gfx/mojom/color_space_mojom_traits.h"
#include "ui/gfx/mojom/gpu_fence_handle_mojom_traits.h"
#include "ui/gfx/mojom/selection_bound_mojom_traits.h"
#include "services/network/public/cpp/connection_allowlist.h"
#include "services/network/public/cpp/content_security_policy/content_security_policy.h"
#include "services/network/public/cpp/integrity_policy.h"
#include "services/network/public/cpp/no_vary_search_header_parser.h"
#include "services/network/public/cpp/parsed_headers.h"
#include "services/network/public/cpp/permissions_policy/permissions_policy_declaration.h"
#include "services/network/public/cpp/timing_allow_origin_parser.h"
#include "services/network/public/mojom/content_security_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/cross_origin_opener_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/permissions_policy/permissions_policy_feature.mojom-blink-forward.h"
#include "services/network/public/mojom/fetch_api.mojom-blink-forward.h"
#include "services/network/public/mojom/integrity_algorithm.mojom-blink.h"
#include "services/network/public/mojom/referrer_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/restricted_cookie_manager.mojom-blink-forward.h"
#include "services/network/public/mojom/trust_tokens.mojom-blink-forward.h"
#include "services/network/public/mojom/url_loader_factory.mojom-forward.h"
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
#if defined(STANDALONE_RENDERER_NEEDS_WIN_CALLBACK) && !defined(CALLBACK)
#define CALLBACK __stdcall
#endif
namespace blink {
class DataTransfer;
class Document;
struct StyleScopeActivation;
struct StyleScopeActivations;

class SVGScriptElement;
class SVGUseElement;
class SVGMarkerElement;
class SVGMPathElement;
class SVGFEDiffuseLightingElement;
class SVGFEDropShadowElement;
class SVGFEFloodElement;
class SVGFESpecularLightingElement;
class SVGSwitchElement;

}  // namespace blink

namespace network {
class OptionalTrustTokenParams;
class PermissionsPolicy;
class PendingSharedURLLoaderFactory;
class ResourceRequestBody;
class SharedURLLoaderFactory;
class SingleRequestURLLoaderFactory;
struct ParsedPermissionsPolicyDeclaration;
enum class MetaCHType;
bool NoVarySearchHasBooleanParamsMember(std::string_view);
namespace cors {}
}  // namespace network

namespace network::cors {
bool IsCorsSameOriginResponseType(::network::mojom::FetchResponseType);
bool IsCorsCrossOriginResponseType(::network::mojom::FetchResponseType);
}  // namespace network::cors

#include "third_party/blink/renderer/core/frame/csp/content_security_policy.h"

#endif  // defined(STANDALONE_RENDERER_NO_BLINK_PREINCLUDE)

#endif  // STANDALONE_RENDERER_STUBS_STANDALONE_NETWORK_NAMESPACE_FORWARDS_H_
