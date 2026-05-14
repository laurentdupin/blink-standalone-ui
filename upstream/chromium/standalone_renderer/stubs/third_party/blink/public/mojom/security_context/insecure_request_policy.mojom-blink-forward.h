#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SECURITY_CONTEXT_INSECURE_REQUEST_POLICY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SECURITY_CONTEXT_INSECURE_REQUEST_POLICY_MOJOM_BLINK_FORWARD_H_

#include <cstdint>

namespace blink::mojom::blink {

enum class InsecureRequestPolicy : uint32_t {
  kLeaveInsecureRequestsAlone = 0,
  kUpgradeInsecureRequests = 1 << 0,
  kBlockAllMixedContent = 1 << 1,
};

constexpr InsecureRequestPolicy operator|(InsecureRequestPolicy lhs,
                                          InsecureRequestPolicy rhs) {
  return static_cast<InsecureRequestPolicy>(static_cast<uint32_t>(lhs) |
                                            static_cast<uint32_t>(rhs));
}

constexpr InsecureRequestPolicy operator&(InsecureRequestPolicy lhs,
                                          InsecureRequestPolicy rhs) {
  return static_cast<InsecureRequestPolicy>(static_cast<uint32_t>(lhs) &
                                            static_cast<uint32_t>(rhs));
}

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SECURITY_CONTEXT_INSECURE_REQUEST_POLICY_MOJOM_BLINK_FORWARD_H_
