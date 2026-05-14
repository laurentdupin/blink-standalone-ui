#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_RENDERER_CONTENT_SETTINGS_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_RENDERER_CONTENT_SETTINGS_MOJOM_H_

#include <memory>

namespace blink::mojom {

struct RendererContentSettings {
  bool allow_script = false;
  bool allow_image = true;
  bool allow_popup = false;
  bool allow_mixed_content = false;
  bool allow_controlled_frame = false;

  std::unique_ptr<RendererContentSettings> Clone() const {
    return std::make_unique<RendererContentSettings>(*this);
  }
};

using RendererContentSettingsPtr = std::unique_ptr<RendererContentSettings>;

}  // namespace blink::mojom

#endif
