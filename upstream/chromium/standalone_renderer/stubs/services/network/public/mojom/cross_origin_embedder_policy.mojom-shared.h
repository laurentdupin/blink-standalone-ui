#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CROSS_ORIGIN_EMBEDDER_POLICY_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CROSS_ORIGIN_EMBEDDER_POLICY_MOJOM_SHARED_H_

namespace network::mojom {

enum class CrossOriginEmbedderPolicyValue {
  kNone,
  kRequireCorp,
  kCredentialless,
};

}  // namespace network::mojom

namespace blink::network {

using ConnectionAllowlists = ::network::ConnectionAllowlists;
using IntegrityPolicy = ::network::IntegrityPolicy;

}  // namespace blink::network

namespace blink::network::mojom {

using CrossOriginEmbedderPolicyValue =
    ::network::mojom::CrossOriginEmbedderPolicyValue;

}  // namespace blink::network::mojom

namespace network::mojom::blink {

using CrossOriginEmbedderPolicyValue =
    ::network::mojom::CrossOriginEmbedderPolicyValue;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using CrossOriginEmbedderPolicyValue =
    ::network::mojom::CrossOriginEmbedderPolicyValue;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CROSS_ORIGIN_EMBEDDER_POLICY_MOJOM_SHARED_H_
