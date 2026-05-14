#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SOURCE_LOCATION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SOURCE_LOCATION_MOJOM_BLINK_FORWARD_H_

#include <cstdint>
#include <memory>

#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink::mojom::blink {

struct ScriptSourceLocation {
  static std::unique_ptr<ScriptSourceLocation> New(
      const KURL& url,
      const String& function_name,
      uint64_t line_number,
      uint64_t column_number) {
    auto result = std::make_unique<ScriptSourceLocation>();
    result->url = url;
    result->function_name = function_name;
    result->line_number = line_number;
    result->column_number = column_number;
    return result;
  }

  KURL url;
  String function_name;
  uint64_t line_number = 0;
  uint64_t column_number = 0;
};
using ScriptSourceLocationPtr = std::unique_ptr<ScriptSourceLocation>;

}  // namespace blink::mojom::blink

namespace blink::mojom {

using ScriptSourceLocation = ::blink::mojom::blink::ScriptSourceLocation;
using ScriptSourceLocationPtr =
    ::blink::mojom::blink::ScriptSourceLocationPtr;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SOURCE_LOCATION_MOJOM_BLINK_FORWARD_H_
