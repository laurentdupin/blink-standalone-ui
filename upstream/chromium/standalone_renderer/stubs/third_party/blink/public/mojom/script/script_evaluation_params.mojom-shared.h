#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_EVALUATION_PARAMS_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_EVALUATION_PARAMS_MOJOM_SHARED_H_

namespace blink::mojom {

enum class UserActivationOption { kDoNotActivate, kActivate };
enum class WantResultOption {
  kNoResult,
  kWantResult,
  kWantResultDateAndRegExpAllowed,
};
enum class PromiseResultOption { kAwait, kDoNotWait };
enum class EvaluationTiming { kAsynchronous, kSynchronous };
enum class LoadEventBlockingOption { kDoNotBlock, kBlock };

}  // namespace blink::mojom

namespace blink::mojom::blink {

enum class ScriptEvaluationSharedHeaderIsPresent {};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_EVALUATION_PARAMS_MOJOM_SHARED_H_
