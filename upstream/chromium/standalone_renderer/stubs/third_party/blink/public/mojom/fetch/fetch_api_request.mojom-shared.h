#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FETCH_FETCH_API_REQUEST_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FETCH_FETCH_API_REQUEST_MOJOM_SHARED_H_

#include "services/network/public/mojom/fetch_api.mojom-shared.h"

namespace blink::mojom {

enum class RequestContextType {
  UNSPECIFIED,
  ATTRIBUTION_SRC,
  AUDIO,
  BEACON,
  CSP_REPORT,
  DOWNLOAD,
  EMBED,
  EVENT_SOURCE,
  FAVICON,
  FETCH,
  FONT,
  FORM,
  FRAME,
  HYPERLINK,
  IFRAME,
  IMAGE,
  IMAGE_SET,
  INTERNAL,
  JSON,
  LOCATION,
  MANIFEST,
  OBJECT,
  PING,
  PLUGIN,
  PREFETCH,
  SCRIPT,
  SERVICE_WORKER,
  SHARED_WORKER,
  SPECULATION_RULES,
  SUBRESOURCE,
  SUBRESOURCE_WEBBUNDLE,
  STYLE,
  TRACK,
  VIDEO,
  WORKER,
  XML_HTTP_REQUEST,
  XSLT,
};

enum class RequestContextFrameType {
  kNone,
  kAuxiliary,
  kNested,
  kTopLevel,
};

enum class FetchCacheMode {
  kDefault,
  kNoStore,
  kBypassCache,
  kValidateCache,
  kForceCache,
  kOnlyIfCached,
  kUnspecifiedOnlyIfCachedStrict,
  kUnspecifiedForceCacheMiss,
};

enum class FetchPriorityHint { kLow, kAuto, kHigh };

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FETCH_FETCH_API_REQUEST_MOJOM_SHARED_H_
