#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LINK_TO_TEXT_LINK_TO_TEXT_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LINK_TO_TEXT_LINK_TO_TEXT_MOJOM_BLINK_FORWARD_H_

#include <functional>

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "ui/gfx/geometry/rect.h"

namespace blink::mojom::blink {

enum class LinkGenerationReadyStatus {
  kRequestedBeforeReady = 0,
  kRequestedAfterReady = 1,
};

enum class LinkGenerationError {
  kNone = -1,
  kIncorrectSelector = 0,
  kUnknown = 9,
  kNotGenerated = 14,
};

class TextFragmentReceiver {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.TextFragmentReceiver";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class RequestValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  using RequestSelectorCallback =
      std::function<void(const String&, LinkGenerationError,
                         LinkGenerationReadyStatus)>;
  using RequestSelectorForViewportCenterCallback = RequestSelectorCallback;
  using RequestSelectorForSelectionCallback = RequestSelectorCallback;
  using GetExistingSelectorsCallback = std::function<void(Vector<String>)>;
  using ExtractTextFragmentsMatchesCallback =
      std::function<void(Vector<String>)>;
  using ExtractFirstFragmentRectCallback =
      std::function<void(const gfx::Rect&)>;

  virtual ~TextFragmentReceiver() = default;
  virtual void Cancel() {}
  virtual void RequestSelector(RequestSelectorCallback) {}
  virtual void RequestSelectorForViewportCenter(
      RequestSelectorForViewportCenterCallback) {}
  virtual void RequestSelectorForSelection(
      RequestSelectorForSelectionCallback) {}
  virtual void GetExistingSelectors(GetExistingSelectorsCallback) {}
  virtual void RemoveFragments() {}
  virtual void ExtractTextFragmentsMatches(
      ExtractTextFragmentsMatchesCallback) {}
  virtual void ExtractFirstFragmentRect(ExtractFirstFragmentRectCallback) {}

  template <typename ImplRefTraits>
  class Stub_ {};
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LINK_TO_TEXT_LINK_TO_TEXT_MOJOM_BLINK_FORWARD_H_
