#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FIND_IN_PAGE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FIND_IN_PAGE_MOJOM_BLINK_H_

#include <functional>
#include <memory>

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "mojo/public/cpp/bindings/pending_remote.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "ui/gfx/geometry/rect.h"

namespace blink::mojom {

enum class StopFindAction {
  kStopFindActionClearSelection,
  kStopFindActionKeepSelection,
  kStopFindActionActivateSelection,
};

enum class FindMatchUpdateType {
  kFinalUpdate,
  kMoreUpdatesComing,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

struct FindOptions {
  bool forward = true;
  bool match_case = false;
  bool new_session = true;
  bool find_match = true;
  bool force = false;
  bool run_synchronously_for_testing = false;
};
using FindOptionsPtr = std::unique_ptr<FindOptions>;

class FindInPageClient {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.FindInPageClient";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;
  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };
  class Proxy_;
  virtual ~FindInPageClient() = default;
  virtual void SetNumberOfMatches(int, uint32_t, FindMatchUpdateType) {}
  virtual void SetActiveMatch(int, const gfx::Rect&, int, FindMatchUpdateType) {}
};
class FindInPageClient::Proxy_ : public FindInPageClient {
 public:
  template <typename... Args>
  explicit Proxy_(Args&&...) {}
};

class FindInPage {
 public:
  using GetNearestFindResultCallback = std::function<void(float)>;
  using FindMatchRectsCallback = std::function<void()>;
  virtual ~FindInPage() = default;
  virtual void Find(int, const String&, FindOptionsPtr) {}
  virtual void StopFinding(::blink::mojom::StopFindAction) {}
  virtual void ClearActiveFindMatch() {}
  virtual void SetClient(mojo::PendingRemote<FindInPageClient>) {}
};

using FindMatchUpdateType = ::blink::mojom::FindMatchUpdateType;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_FIND_IN_PAGE_MOJOM_BLINK_H_
