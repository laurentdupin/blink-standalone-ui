#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_REQUEST_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_REQUEST_MOJOM_SHARED_H_

namespace network::mojom {

struct DataElementDataView {
  enum class Tag {
    kBytes,
    kFile,
    kDataPipe,
    kChunkedDataPipe,
  };
};

struct URLRequestBodyDataView {};

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_REQUEST_MOJOM_SHARED_H_
