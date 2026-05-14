#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_EVALUATION_PARAMS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_EVALUATION_PARAMS_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class UserActivationOption { kDoNotActivate, kActivate };
enum class WantResultOption {
  kNoResult,
  kWantResult,
  kWantResultDateAndRegExpAllowed,
};
enum class PromiseResultOption { kAwait, kDoNotWait };
enum class EvaluationTiming { kAsynchronous, kSynchronous };
enum class LoadEventBlockingOption { kDoNotBlock, kBlock };

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_EVALUATION_PARAMS_MOJOM_BLINK_FORWARD_H_
