#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_FETCH_API_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_FETCH_API_MOJOM_SHARED_H_

namespace network::mojom {

#if !defined(STANDALONE_RENDERER_NETWORK_FETCH_API_ENUMS_DEFINED)
enum class RequestDestination {
  kEmpty = 0,
  kAudio = 1,
  kAudioWorklet = 2,
  kDocument = 3,
  kEmbed = 4,
  kFont = 5,
  kFrame = 6,
  kIframe = 7,
  kImage = 8,
  kManifest = 9,
  kObject = 10,
  kPaintWorklet = 11,
  kReport = 12,
  kScript = 13,
  kServiceWorker = 14,
  kSharedWorker = 15,
  kStyle = 16,
  kTrack = 17,
  kVideo = 18,
  kWebBundle = 19,
  kWorker = 20,
  kXslt = 21,
  kFencedframe = 22,
  kWebIdentity = 23,
  kDictionary = 24,
  kSpeculationRules = 25,
  kJson = 26,
  kSharedStorageWorklet = 27,
  kEmailVerification = 28,
  kMinValue = kEmpty,
  kMaxValue = kEmailVerification,
};

enum class RequestMode {
  kSameOrigin = 0,
  kNoCors = 1,
  kCors = 2,
  kCorsWithForcedPreflight = 3,
  kNavigate = 4,
};

enum class RedirectMode { kFollow, kError, kManual };
enum class CredentialsMode {
  kOmit,
  kSameOrigin,
  kInclude,
  kOmitBug_775438_Workaround,
};
#endif

enum class FetchResponseType {
  kBasic = 0,
  kCors = 1,
  kDefault = 2,
  kError = 3,
  kOpaque = 4,
  kOpaqueRedirect = 5,
};

enum class FetchResponseSource {
  kUnspecified,
  kNetwork,
  kHttpCache,
  kCacheStorage,
};

}  // namespace network::mojom

namespace network::mojom {
enum class DeviceBoundSessionUsage : int32_t;
class LoadTimingInfo;
class ServiceWorkerRouterInfo;
enum class PrivateNetworkAccessPreflightResult : int32_t;
}  // namespace network::mojom

namespace blink::network::mojom {

using FetchResponseSource = ::network::mojom::FetchResponseSource;
using FetchResponseType = ::network::mojom::FetchResponseType;
using DeviceBoundSessionUsage = ::network::mojom::DeviceBoundSessionUsage;
using LoadTimingInfo = ::network::mojom::LoadTimingInfo;
using PrivateNetworkAccessPreflightResult =
    ::network::mojom::PrivateNetworkAccessPreflightResult;
using ServiceWorkerRouterInfo = ::network::mojom::ServiceWorkerRouterInfo;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_FETCH_API_MOJOM_SHARED_H_
