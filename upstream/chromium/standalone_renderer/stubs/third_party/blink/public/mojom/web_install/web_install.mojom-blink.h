#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_WEB_INSTALL_WEB_INSTALL_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_WEB_INSTALL_WEB_INSTALL_MOJOM_BLINK_H_

#include <memory>
#include <utility>

#include "base/functional/callback_forward.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace blink::mojom::blink {

enum class WebInstallServiceResult {
  kAbortError,
  kDataError,
  kSuccess,
};

struct InstallOptions {
  static std::unique_ptr<InstallOptions> New() {
    return std::make_unique<InstallOptions>();
  }

  ::blink::KURL install_url;
  ::blink::KURL manifest_id;
};

using InstallOptionsPtr = std::unique_ptr<InstallOptions>;

class WebInstallService {
 public:
  using InstallFromElementCallback =
      base::OnceCallback<void(WebInstallServiceResult, const ::blink::KURL&)>;

  class Proxy_ {
   public:
    void InstallFromElement(InstallOptionsPtr,
                            InstallFromElementCallback callback) {
      std::move(callback).Run(WebInstallServiceResult::kAbortError,
                              ::blink::KURL());
    }
  };
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_WEB_INSTALL_WEB_INSTALL_MOJOM_BLINK_H_
