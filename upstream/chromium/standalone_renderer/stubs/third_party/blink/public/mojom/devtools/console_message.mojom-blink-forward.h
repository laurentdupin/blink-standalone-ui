#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_CONSOLE_MESSAGE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_DEVTOOLS_CONSOLE_MESSAGE_MOJOM_BLINK_FORWARD_H_
namespace blink::mojom::blink {
enum class ConsoleMessageCategory { kCors, kOther };
enum class ConsoleMessageLevel { kVerbose, kInfo, kWarning, kError };
enum class ConsoleMessageSource {
  kOther,
  kJavaScript,
  kSecurity,
  kRendering,
  kDeprecation,
  kViolation,
  kWorker,
  kRecommendation,
};
}
namespace blink::mojom {
using ConsoleMessageCategory = ::blink::mojom::blink::ConsoleMessageCategory;
using ConsoleMessageLevel = ::blink::mojom::blink::ConsoleMessageLevel;
using ConsoleMessageSource = ::blink::mojom::blink::ConsoleMessageSource;
}
#endif
