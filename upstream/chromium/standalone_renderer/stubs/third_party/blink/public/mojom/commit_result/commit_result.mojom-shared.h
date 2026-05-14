#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_COMMIT_RESULT_COMMIT_RESULT_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_COMMIT_RESULT_COMMIT_RESULT_MOJOM_SHARED_H_

#include <cstdint>

namespace blink::mojom {

enum class CommitResult : int32_t {
  Ok,
  Aborted,
  RestartCrossDocument,
};

}  // namespace blink::mojom

namespace blink::mojom::blink {

using CommitResult = ::blink::mojom::CommitResult;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_COMMIT_RESULT_COMMIT_RESULT_MOJOM_SHARED_H_
