#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SPECULATION_RULES_SPECULATION_RULES_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SPECULATION_RULES_SPECULATION_RULES_MOJOM_BLINK_H_

#include <memory>

namespace blink::mojom::blink {

class SpeculationHost {
 public:
  using Base_ = SpeculationHost;
  class Proxy_ {
   public:
    template <typename... Args>
    void UpdateSpeculationCandidates(Args&&...) {}
    void OnLCPPredicted() {}
  };
  virtual ~SpeculationHost() = default;
};

enum class SpeculationAction {
  kPrefetch,
  kPrerenderUntilScript,
  kPrerender,
};

enum class SpeculationTargetHint {
  kNoHint,
  kBlank,
  kSelf,
};

enum class SpeculationEagerness {
  kConservative = 0,
  kModerate = 1,
  kImmediate = 2,
  kEager = 3,
};

enum class SpeculationInjectionType {
  kNone,
  kMainWorldScript,
  kIsolatedWorldScript,
  kAutoSpeculationRules,
};

struct SpeculationCandidate {
  template <typename... Args>
  static std::unique_ptr<SpeculationCandidate> New(Args&&...) {
    return std::make_unique<SpeculationCandidate>();
  }
};
using SpeculationCandidatePtr = std::unique_ptr<SpeculationCandidate>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SPECULATION_RULES_SPECULATION_RULES_MOJOM_BLINK_H_
