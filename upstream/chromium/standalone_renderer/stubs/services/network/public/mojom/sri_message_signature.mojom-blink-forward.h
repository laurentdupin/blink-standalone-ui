#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SRI_MESSAGE_SIGNATURE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SRI_MESSAGE_SIGNATURE_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace network::mojom::blink {

struct SRIMessageSignatureComponentParameter {
  enum class Type {
    kName,
    kRequest,
    kStrictStructuredFieldSerialization,
    kBinaryRepresentation,
  };

  template <typename... Args>
  static std::unique_ptr<SRIMessageSignatureComponentParameter> New(
      Args&&...) {
    return std::make_unique<SRIMessageSignatureComponentParameter>();
  }
};
using SRIMessageSignatureComponentParameterPtr =
    std::unique_ptr<SRIMessageSignatureComponentParameter>;

struct SRIMessageSignatureComponent {
  template <typename... Args>
  static std::unique_ptr<SRIMessageSignatureComponent> New(Args&&...) {
    return std::make_unique<SRIMessageSignatureComponent>();
  }
};
using SRIMessageSignatureComponentPtr =
    std::unique_ptr<SRIMessageSignatureComponent>;

enum class SRIMessageSignatureError {
  kMissingSignatureHeader,
  kMissingSignatureInputHeader,
  kInvalidSignatureHeader,
  kInvalidSignatureInputHeader,
  kSignatureHeaderValueIsNotByteSequence,
  kSignatureHeaderValueIsParameterized,
  kSignatureHeaderValueIsIncorrectLength,
  kSignatureInputHeaderMissingLabel,
  kSignatureInputHeaderValueNotInnerList,
  kSignatureInputHeaderValueMissingComponents,
  kSignatureInputHeaderInvalidComponentType,
  kSignatureInputHeaderInvalidComponentName,
  kSignatureInputHeaderInvalidHeaderComponentParameter,
  kSignatureInputHeaderInvalidDerivedComponentParameter,
  kSignatureInputHeaderKeyIdLength,
  kSignatureInputHeaderInvalidParameter,
  kSignatureInputHeaderMissingRequiredParameters,
  kValidationFailedSignatureExpired,
  kValidationFailedInvalidLength,
  kValidationFailedSignatureMismatch,
  kValidationFailedIntegrityMismatch,
};

struct SRIMessageSignatureIssue {
  template <typename... Args>
  static std::unique_ptr<SRIMessageSignatureIssue> New(Args&&...) {
    return std::make_unique<SRIMessageSignatureIssue>();
  }
};
using SRIMessageSignatureIssuePtr =
    std::unique_ptr<SRIMessageSignatureIssue>;

struct SRIMessageSignature {
  template <typename... Args>
  static std::unique_ptr<SRIMessageSignature> New(Args&&...) {
    return std::make_unique<SRIMessageSignature>();
  }
};
using SRIMessageSignaturePtr = std::unique_ptr<SRIMessageSignature>;

struct SRIMessageSignatures {
  template <typename... Args>
  static std::unique_ptr<SRIMessageSignatures> New(Args&&...) {
    return std::make_unique<SRIMessageSignatures>();
  }
};
using SRIMessageSignaturesPtr = std::unique_ptr<SRIMessageSignatures>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using SRIMessageSignatureComponentParameter =
    ::network::mojom::blink::SRIMessageSignatureComponentParameter;
using SRIMessageSignatureComponentParameterPtr =
    ::network::mojom::blink::SRIMessageSignatureComponentParameterPtr;
using SRIMessageSignatureComponent =
    ::network::mojom::blink::SRIMessageSignatureComponent;
using SRIMessageSignatureComponentPtr =
    ::network::mojom::blink::SRIMessageSignatureComponentPtr;
using SRIMessageSignatureError =
    ::network::mojom::blink::SRIMessageSignatureError;
using SRIMessageSignatureIssue =
    ::network::mojom::blink::SRIMessageSignatureIssue;
using SRIMessageSignatureIssuePtr =
    ::network::mojom::blink::SRIMessageSignatureIssuePtr;
using SRIMessageSignature = ::network::mojom::blink::SRIMessageSignature;
using SRIMessageSignaturePtr =
    ::network::mojom::blink::SRIMessageSignaturePtr;
using SRIMessageSignatures = ::network::mojom::blink::SRIMessageSignatures;
using SRIMessageSignaturesPtr =
    ::network::mojom::blink::SRIMessageSignaturesPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_SRI_MESSAGE_SIGNATURE_MOJOM_BLINK_FORWARD_H_
