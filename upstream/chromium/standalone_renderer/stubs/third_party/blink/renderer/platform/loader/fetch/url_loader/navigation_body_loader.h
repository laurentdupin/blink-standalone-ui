#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_URL_LOADER_NAVIGATION_BODY_LOADER_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_URL_LOADER_NAVIGATION_BODY_LOADER_H_

#include <memory>

#include "third_party/blink/public/platform/web_navigation_body_loader.h"
#include "third_party/blink/renderer/platform/loader/fetch/body_text_decoder.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"

namespace blink {

class NavigationBodyLoader final : public WebNavigationBodyLoader {
 public:
  ~NavigationBodyLoader() override = default;

  void StartLoadingBodyInBackground(std::unique_ptr<BodyTextDecoder>, bool);
  void FlushOffThreadBodyReaderForTesting() {}

  void SetDefersLoading(WebLoaderFreezeMode) override {}
  void StartLoadingBody(WebNavigationBodyLoader::Client* client) override {
    if (client) {
      client->BodyLoadingFinished(base::TimeTicks(), 0, 0, 0, std::nullopt);
    }
  }
  BodyLoaderType GetType() const override { return BodyLoaderType::kNetwork; }
};

template <>
struct DowncastTraits<NavigationBodyLoader> {
  static bool AllowFrom(const WebNavigationBodyLoader& body_loader) {
    return body_loader.GetType() ==
           NavigationBodyLoader::BodyLoaderType::kNetwork;
  }
};

}  // namespace blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_RENDERER_PLATFORM_LOADER_FETCH_URL_LOADER_NAVIGATION_BODY_LOADER_H_
