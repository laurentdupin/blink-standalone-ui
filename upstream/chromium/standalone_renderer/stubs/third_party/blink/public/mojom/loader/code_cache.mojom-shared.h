#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CODE_CACHE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CODE_CACHE_MOJOM_SHARED_H_

namespace blink::mojom::blink {

class CodeCacheHost;
using CodeCacheHostInterfaceBase = CodeCacheHost;

}  // namespace blink::mojom::blink

namespace blink::mojom {

enum class CodeCacheType {
  kJavascript,
  kWebAssembly,
  kMaxValue = kWebAssembly,
};

using CodeCacheHostInterfaceBase = ::blink::mojom::blink::CodeCacheHost;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_LOADER_CODE_CACHE_MOJOM_SHARED_H_
