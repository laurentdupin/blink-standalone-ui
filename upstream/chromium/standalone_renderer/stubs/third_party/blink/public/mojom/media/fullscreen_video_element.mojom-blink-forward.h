#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_MEDIA_FULLSCREEN_VIDEO_ELEMENT_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_MEDIA_FULLSCREEN_VIDEO_ELEMENT_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

class FullscreenVideoElementHandler {
 public:
  static constexpr bool PassesAssociatedKinds_ = true;
  static constexpr bool HasUninterruptableMethods_ = false;
  class Proxy_ {
   public:
    void RequestFullscreenVideoElement() {}
  };
  template <typename ImplRefTraits>
  class Stub_ {};
  virtual ~FullscreenVideoElementHandler() = default;
  virtual void RequestFullscreenVideoElement() {}
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_MEDIA_FULLSCREEN_VIDEO_ELEMENT_MOJOM_BLINK_FORWARD_H_
