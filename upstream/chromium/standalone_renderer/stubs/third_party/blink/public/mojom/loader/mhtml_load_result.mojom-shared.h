#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_MHTML_LOAD_RESULT_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_MHTML_LOAD_RESULT_MOJOM_SHARED_H_

namespace blink::mojom {

enum class MHTMLLoadResult {
  kSuccess,
  kEmptyFile,
  kUrlSchemeNotAllowed,
  kInvalidArchive,
  kMissingMainResource,
  kMaxValue = kMissingMainResource,
};

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_MHTML_LOAD_RESULT_MOJOM_SHARED_H_
