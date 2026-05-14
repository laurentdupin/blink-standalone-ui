#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_V8_CACHE_OPTIONS_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_V8_CACHE_OPTIONS_MOJOM_BLINK_FORWARD_H_
namespace blink::mojom::blink {
enum class V8CacheOptions {
  kDefault,
  kNone,
  kCode,
  kCodeWithoutHeatCheck,
  kFullCodeWithoutHeatCheck,
};
}
#endif
