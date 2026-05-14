#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CONTENT_SECURITY_NOTIFIER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CONTENT_SECURITY_NOTIFIER_MOJOM_BLINK_H_

#include "mojo/public/cpp/bindings/message.h"
#include "third_party/blink/public/mojom/loader/content_security_notifier.mojom-blink-forward.h"

namespace blink {
class KURL;
}  // namespace blink

namespace blink::mojom::blink {

class ContentSecurityNotifier {
 public:
  using Base_ = ContentSecurityNotifier;
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;

  enum class InsecureContentOrigin {
    kTopFrame,
    kCurrentFrame,
  };

  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };

  class Proxy_;

  static constexpr const char Name_[] =
      "blink.mojom.ContentSecurityNotifier";

  virtual ~ContentSecurityNotifier() = default;
  virtual void NotifyContentWithCertificateErrorsRan() {}
  virtual void NotifyContentWithCertificateErrorsDisplayed() {}
  virtual void NotifyInsecureContentRan(
      const ::blink::KURL& insecure_url,
      InsecureContentOrigin origin_type) {}
};

class ContentSecurityNotifier::Proxy_ : public ContentSecurityNotifier {
 public:
  explicit Proxy_(mojo::InterfaceEndpointClient*) {}
  void NotifyContentWithCertificateErrorsRan() override {}
  void NotifyContentWithCertificateErrorsDisplayed() override {}
  void NotifyInsecureContentRan(const ::blink::KURL& insecure_url,
                                InsecureContentOrigin origin_type) override {}
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CONTENT_SECURITY_NOTIFIER_MOJOM_BLINK_H_
