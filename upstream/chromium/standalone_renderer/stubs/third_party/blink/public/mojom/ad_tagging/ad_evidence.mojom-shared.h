#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_AD_TAGGING_AD_EVIDENCE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_AD_TAGGING_AD_EVIDENCE_MOJOM_SHARED_H_

namespace blink::mojom {

enum class FilterListResult {
  kNotChecked = 0,
  kMatchedAllowingRule = 1,
  kMatchedNoRules = 2,
  kMatchedBlockingRule = 3,
};

enum class FrameCreationStackEvidence {
  kNotCreatedByAdScript,
  kCreatedByAdScript,
};

}  // namespace blink::mojom

#endif
