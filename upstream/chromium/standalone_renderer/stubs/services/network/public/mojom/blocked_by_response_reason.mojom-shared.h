#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_BLOCKED_BY_RESPONSE_REASON_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_BLOCKED_BY_RESPONSE_REASON_MOJOM_SHARED_H_

namespace network::mojom {

enum class BlockedByResponseReason {
  kCoepFrameResourceNeedsCoepHeader,
  kCoopSandboxedIFrameCannotNavigateToCoopPage,
  kCorpNotSameOrigin,
  kCorpNotSameOriginAfterDefaultedToSameOriginByCoep,
  kCorpNotSameOriginAfterDefaultedToSameOriginByDip,
  kCorpNotSameOriginAfterDefaultedToSameOriginByCoepAndDip,
  kCorpNotSameSite,
  kSRIMessageSignatureMismatch,
  kMaxValue = kSRIMessageSignatureMismatch,
};

}  // namespace network::mojom

namespace blink::network::mojom {

using BlockedByResponseReason = ::network::mojom::BlockedByResponseReason;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_BLOCKED_BY_RESPONSE_REASON_MOJOM_SHARED_H_
