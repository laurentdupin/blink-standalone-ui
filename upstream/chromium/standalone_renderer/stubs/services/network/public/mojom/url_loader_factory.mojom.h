#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_H_

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "mojo/public/cpp/base/big_buffer.h"
#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "mojo/public/cpp/system/data_pipe.h"
#include "net/base/request_priority.h"
#include "services/network/public/cpp/url_loader_completion_status.h"
#include "services/network/public/cpp/permissions_policy/permissions_policy_declaration.h"
#include "services/network/public/cpp/integrity_metadata.h"
#include "services/network/public/mojom/content_security_policy.mojom.h"
#include "services/network/public/mojom/content_security_policy.mojom-blink-forward.h"
#include "services/network/public/mojom/fetch_api.mojom-blink-forward.h"
#include "services/network/public/mojom/url_loader_factory.mojom-shared.h"
#include "services/network/public/mojom/url_response_head.mojom-forward.h"
#include "services/network/public/mojom/web_sandbox_flags.mojom-shared.h"
#include "third_party/blink/public/common/permissions_policy/document_policy_features.h"
#include "third_party/blink/public/mojom/frame/frame.mojom-blink-forward.h"
#include "third_party/blink/public/web/web_navigation_type.h"

namespace net {
class HttpRequestHeaders;
class MutableNetworkTrafficAnnotationTag;
struct RedirectInfo;
}

class GURL;

namespace network {
class OptionalTrustTokenParams;
class PendingSharedURLLoaderFactory;
struct ResourceRequest;
class SharedURLLoaderFactory;
}

namespace network::mojom {

enum class NavigationDeliveryType {
  kDefault,
  kNavigationalPrefetch,
};

struct EarlyHints {};
using EarlyHintsPtr = std::unique_ptr<EarlyHints>;
class URLResponseHead {};

class URLLoader {
 public:
  class Proxy_ {
   public:
    void FollowRedirect(const std::vector<std::string>&,
                        const net::HttpRequestHeaders&,
                        const net::HttpRequestHeaders&,
                        const std::optional<GURL>&) {}
    void SetPriority(net::RequestPriority, int32_t) {}
    void PauseReadingBodyFromNet() {}
    void ResumeReadingBodyFromNet() {}
  };

  virtual ~URLLoader() = default;
};

class URLLoaderClient {
 public:
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  using OnUploadProgressCallback = std::function<void()>;

  template <typename ImplRefTraits>
  class Stub_ {};

  virtual ~URLLoaderClient() = default;
  virtual void OnReceiveEarlyHints(EarlyHintsPtr) {}
  virtual void OnReceiveResponse(URLResponseHeadPtr,
                                 mojo::ScopedDataPipeConsumerHandle,
                                 std::optional<mojo_base::BigBuffer>) {}
  virtual void OnReceiveRedirect(const net::RedirectInfo&, URLResponseHeadPtr) {}
  virtual void OnUploadProgress(int64_t, int64_t, OnUploadProgressCallback) {}
  virtual void OnTransferSizeUpdated(int32_t) {}
  virtual void OnComplete(const network::URLLoaderCompletionStatus&) {}
};
struct URLLoaderClientEndpoints;
using URLLoaderClientEndpointsPtr = URLLoaderClientEndpoints*;

class URLLoaderFactory {
 public:
  using Base_ = URLLoaderFactoryInterfaceBase;

  class Proxy_ {
   public:
    void Clone(mojo::PendingReceiver<URLLoaderFactory> receiver) {}
  };

  virtual ~URLLoaderFactory() = default;
  virtual void CreateLoaderAndStart(
      mojo::PendingReceiver<URLLoader> loader,
      int32_t request_id,
      uint32_t options,
      const network::ResourceRequest& request,
      mojo::PendingRemote<URLLoaderClient> client,
      const net::MutableNetworkTrafficAnnotationTag& traffic_annotation) {}
  virtual void Clone(mojo::PendingReceiver<URLLoaderFactory> receiver) {}
};

}  // namespace network::mojom

namespace blink::network {
using OptionalTrustTokenParams = ::network::OptionalTrustTokenParams;
using IntegrityMetadata = ::network::IntegrityMetadata;
using ParsedPermissionsPolicy = ::network::ParsedPermissionsPolicy;
using ParsedPermissionsPolicyDeclaration =
    ::network::ParsedPermissionsPolicyDeclaration;
using PendingSharedURLLoaderFactory = ::network::PendingSharedURLLoaderFactory;
using ResourceRequest = ::network::ResourceRequest;
using SharedURLLoaderFactory = ::network::SharedURLLoaderFactory;
using URLLoaderCompletionStatus = ::network::URLLoaderCompletionStatus;
}

namespace blink::network::mojom {
using CSPDisposition = ::network::mojom::CSPDisposition;
using CSPDirectiveName = ::network::mojom::blink::CSPDirectiveName;
using CSPRequireTrustedTypesFor =
    ::network::mojom::blink::CSPRequireTrustedTypesFor;
using ContentSecurityPolicySource =
    ::network::mojom::ContentSecurityPolicySource;
using ContentSecurityPolicyType = ::network::mojom::ContentSecurityPolicyType;
using CorsPreflightPolicy = ::network::mojom::CorsPreflightPolicy;
using CredentialsMode = ::network::mojom::CredentialsMode;
using IntegrityAlgorithm = ::network::mojom::IntegrityAlgorithm;
using RedirectMode = ::network::mojom::RedirectMode;
using RequestDestination = ::network::mojom::RequestDestination;
using RequestMode = ::network::mojom::RequestMode;
using NavigationDeliveryType = ::network::mojom::NavigationDeliveryType;
using EarlyHints = ::network::mojom::EarlyHints;
using EarlyHintsPtr = ::network::mojom::EarlyHintsPtr;
using URLLoaderFactoryInterfaceBase =
    ::network::mojom::URLLoaderFactoryInterfaceBase;
using URLResponseHead = ::network::mojom::URLResponseHead;
using URLResponseHeadPtr = ::network::mojom::URLResponseHeadPtr;
using URLLoader = ::network::mojom::URLLoader;
using URLLoaderClient = ::network::mojom::URLLoaderClient;
using URLLoaderClientEndpoints = ::network::mojom::URLLoaderClientEndpoints;
using URLLoaderClientEndpointsPtr =
    ::network::mojom::URLLoaderClientEndpointsPtr;
using URLLoaderFactory = ::network::mojom::URLLoaderFactory;
using WebSandboxFlags = ::network::mojom::WebSandboxFlags;
}

namespace blink::network::mojom::blink {

using URLLoader = ::network::mojom::URLLoader;
using URLLoaderClient = ::network::mojom::URLLoaderClient;
using URLLoaderFactory = ::network::mojom::URLLoaderFactory;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_H_
