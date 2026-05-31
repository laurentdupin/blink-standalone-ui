#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SUPPORTS_LOADING_MODE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SUPPORTS_LOADING_MODE_MOJOM_BLINK_H_

#include <memory>
#include <vector>

namespace network::mojom {

enum class LoadingMode {
  kCredentialedPrerender,
  kPrerenderCrossOriginFrames,
};

struct SupportsLoadingMode {
  static std::unique_ptr<SupportsLoadingMode> New(
      std::vector<LoadingMode> supported_modes = {}) {
    auto out = std::make_unique<SupportsLoadingMode>();
    out->supported_modes = std::move(supported_modes);
    return out;
  }

  std::vector<LoadingMode> supported_modes;
};
using SupportsLoadingModePtr = std::unique_ptr<SupportsLoadingMode>;

}  // namespace network::mojom

namespace network::mojom::blink {

enum class LoadingMode {
  kCredentialedPrerender,
  kPrerenderCrossOriginFrames,
};

struct SupportsLoadingMode {
  static std::unique_ptr<SupportsLoadingMode> New(
      std::vector<LoadingMode> supported_modes = {}) {
    auto out = std::make_unique<SupportsLoadingMode>();
    out->supported_modes = std::move(supported_modes);
    return out;
  }

  std::vector<LoadingMode> supported_modes;
};
using SupportsLoadingModePtr = std::unique_ptr<SupportsLoadingMode>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using LoadingMode = ::network::mojom::blink::LoadingMode;
using SupportsLoadingMode = ::network::mojom::blink::SupportsLoadingMode;
using SupportsLoadingModePtr =
    ::network::mojom::blink::SupportsLoadingModePtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SUPPORTS_LOADING_MODE_MOJOM_BLINK_H_
