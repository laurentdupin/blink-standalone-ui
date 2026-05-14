#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_NO_VARY_SEARCH_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_NO_VARY_SEARCH_MOJOM_BLINK_FORWARD_H_

#include <memory>
#include <vector>

namespace network::mojom {

enum class NoVarySearchParseError {
  kOk,
  kDefaultValue,
  kNotDictionary,
  kUnknownDictionaryKey,
  kNonBooleanKeyOrder,
  kParamsNotStringList,
  kExceptNotStringList,
  kExceptWithoutTrueParams,
};

struct NoVarySearch;
using NoVarySearchPtr = std::unique_ptr<NoVarySearch>;
struct NoVarySearchWithParseError;
using NoVarySearchWithParseErrorPtr =
    std::unique_ptr<NoVarySearchWithParseError>;

}  // namespace network::mojom

namespace network::mojom::blink {

struct NoVarySearch {
  bool vary_on_key_order = true;
};
using NoVarySearchPtr = std::unique_ptr<NoVarySearch>;

struct NoVarySearchWithParseError {
  static std::unique_ptr<NoVarySearchWithParseError> NewParseError(
      ::network::mojom::NoVarySearchParseError error) {
    return std::make_unique<NoVarySearchWithParseError>();
  }
  static std::unique_ptr<NoVarySearchWithParseError> NewNoVarySearch(
      NoVarySearchPtr no_vary_search) {
    return std::make_unique<NoVarySearchWithParseError>();
  }
};
using NoVarySearchWithParseErrorPtr =
    std::unique_ptr<NoVarySearchWithParseError>;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using NoVarySearch = ::network::mojom::blink::NoVarySearch;
using NoVarySearchPtr = ::network::mojom::blink::NoVarySearchPtr;
using NoVarySearchWithParseError =
    ::network::mojom::blink::NoVarySearchWithParseError;
using NoVarySearchWithParseErrorPtr =
    ::network::mojom::blink::NoVarySearchWithParseErrorPtr;

}  // namespace blink::network::mojom::blink

namespace blink::network::mojom {

using NoVarySearchParseError = ::network::mojom::NoVarySearchParseError;

}  // namespace blink::network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_NO_VARY_SEARCH_MOJOM_BLINK_FORWARD_H_
