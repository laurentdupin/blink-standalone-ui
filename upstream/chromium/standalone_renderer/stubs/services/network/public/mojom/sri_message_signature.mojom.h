#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SRI_MESSAGE_SIGNATURE_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SRI_MESSAGE_SIGNATURE_MOJOM_H_

#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "services/network/public/mojom/sri_message_signature.mojom-blink-forward.h"

namespace network::mojom {

using SRIMessageSignatureError =
    ::network::mojom::blink::SRIMessageSignatureError;

struct SRIMessageSignatureComponentParameter {
  using Type = ::network::mojom::blink::SRIMessageSignatureComponentParameter::
      Type;

  static std::unique_ptr<SRIMessageSignatureComponentParameter> New(
      Type type,
      std::optional<std::string> value) {
    auto out = std::make_unique<SRIMessageSignatureComponentParameter>();
    out->type = type;
    out->value = std::move(value);
    return out;
  }

  Type type = Type::kRequest;
  std::optional<std::string> value;
};
using SRIMessageSignatureComponentParameterPtr =
    std::unique_ptr<SRIMessageSignatureComponentParameter>;

struct SRIMessageSignatureComponent {
  static std::unique_ptr<SRIMessageSignatureComponent> New() {
    return std::make_unique<SRIMessageSignatureComponent>();
  }

  std::string name;
  std::vector<SRIMessageSignatureComponentParameterPtr> params;
};
using SRIMessageSignatureComponentPtr =
    std::unique_ptr<SRIMessageSignatureComponent>;

struct SRIMessageSignatureIssue {
  static std::unique_ptr<SRIMessageSignatureIssue> New() {
    return std::make_unique<SRIMessageSignatureIssue>();
  }

  SRIMessageSignatureError error =
      SRIMessageSignatureError::kMissingSignatureHeader;
  std::optional<std::string> signature_base;
  std::optional<std::vector<std::string>> integrity_assertions;
};
using SRIMessageSignatureIssuePtr =
    std::unique_ptr<SRIMessageSignatureIssue>;

struct SRIMessageSignature {
  static std::unique_ptr<SRIMessageSignature> New() {
    return std::make_unique<SRIMessageSignature>();
  }

  std::string label;
  std::vector<uint8_t> signature;
  std::vector<SRIMessageSignatureComponentPtr> components;
  std::optional<int64_t> created;
  std::optional<int64_t> expires;
  std::optional<std::vector<uint8_t>> keyid;
  std::optional<std::string> nonce;
  std::optional<std::string> tag;
  std::string serialized_signature_params;
};
using SRIMessageSignaturePtr = std::unique_ptr<SRIMessageSignature>;

struct SRIMessageSignatures {
  static std::unique_ptr<SRIMessageSignatures> New() {
    return std::make_unique<SRIMessageSignatures>();
  }

  std::vector<SRIMessageSignaturePtr> signatures;
  std::vector<SRIMessageSignatureIssuePtr> issues;
};
using SRIMessageSignaturesPtr = std::unique_ptr<SRIMessageSignatures>;

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SRI_MESSAGE_SIGNATURE_MOJOM_H_
