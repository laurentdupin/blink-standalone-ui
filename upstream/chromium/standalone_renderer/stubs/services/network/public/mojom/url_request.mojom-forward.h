#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_REQUEST_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_REQUEST_MOJOM_FORWARD_H_

#include <memory>

#include "services/network/public/mojom/url_request.mojom-shared.h"

namespace network::mojom {

struct DataElementBytes;
struct DataElementFile;
struct DataElementDataPipe;
struct DataElementChunkedDataPipe;
struct DataElement;
struct EnabledClientHints;
struct TrustedUrlRequestParams;
struct WebBundleTokenParams;
struct URLRequest;
struct URLRequestBody;

using DataElementBytesPtr = std::unique_ptr<DataElementBytes>;
using DataElementFilePtr = std::unique_ptr<DataElementFile>;
using DataElementDataPipePtr = std::unique_ptr<DataElementDataPipe>;
using DataElementChunkedDataPipePtr =
    std::unique_ptr<DataElementChunkedDataPipe>;
using DataElementPtr = std::unique_ptr<DataElement>;
using EnabledClientHintsPtr = std::unique_ptr<EnabledClientHints>;
using TrustedUrlRequestParamsPtr = std::unique_ptr<TrustedUrlRequestParams>;
using WebBundleTokenParamsPtr = std::unique_ptr<WebBundleTokenParams>;
using URLRequestPtr = std::unique_ptr<URLRequest>;
using URLRequestBodyPtr = std::unique_ptr<URLRequestBody>;

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_REQUEST_MOJOM_FORWARD_H_
