#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_DISPLAY_CUTOUT_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_DISPLAY_CUTOUT_MOJOM_BLINK_H_

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "ui/gfx/geometry/insets.h"

namespace blink::mojom::blink {

enum class ViewportFit {
  kAuto,
  kContain,
  kCover,
  kCoverForcedByUserAgent,
};

class DisplayCutoutHost {
 public:
  using Base_ = DisplayCutoutHost;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.DisplayCutoutHost";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_ {
   public:
    template <typename... Args>
    explicit Proxy_(Args&&...) {}
    void NotifyViewportFitChanged(ViewportFit value) {}
    void NotifyComplexSafeAreaConstraintChanged(bool value) {}
  };
  virtual ~DisplayCutoutHost() = default;
};

class DisplayCutoutClient {
 public:
  using Base_ = DisplayCutoutClient;
  virtual ~DisplayCutoutClient() = default;
  virtual void SetSafeArea(const class gfx::Insets& safe_area) = 0;
};

}  // namespace blink::mojom::blink

namespace blink::mojom {

using ViewportFit = ::blink::mojom::blink::ViewportFit;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PAGE_DISPLAY_CUTOUT_MOJOM_BLINK_H_
