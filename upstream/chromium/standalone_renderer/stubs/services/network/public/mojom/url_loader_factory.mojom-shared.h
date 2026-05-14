#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_SHARED_H_

#include <cstdint>

namespace network::mojom {

inline constexpr uint32_t kURLLoadOptionNone = 0;
inline constexpr uint32_t kURLLoadOptionSendSSLInfoWithResponse = 1;
inline constexpr uint32_t kURLLoadOptionSniffMimeType = 2;
inline constexpr uint32_t kURLLoadOptionSynchronous = 4;
inline constexpr uint32_t kURLLoadOptionSendSSLInfoForCertificateError = 8;
inline constexpr uint32_t kURLLoadOptionUseHeaderClient = 16;
inline constexpr uint32_t kURLLoadOptionBlockAllCookies = 32;
inline constexpr uint32_t kURLLoadOptionBlockThirdPartyCookies = 64;
inline constexpr uint32_t kURLLoadOptionAsCorsPreflight = 128;
inline constexpr uint32_t kURLLoadOptionBlockLocalRequest = 256;
inline constexpr uint32_t kURLLoadOptionReadAndDiscardBody = 512;

class URLLoaderFactoryInterfaceBase {};

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_URL_LOADER_FACTORY_MOJOM_SHARED_H_
