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

struct SearchParamsVariance {
  enum class Tag { kNoVaryParams, kVaryParams };

  static std::unique_ptr<SearchParamsVariance> NewNoVaryParams(
      std::vector<std::string> params) {
    auto out = std::make_unique<SearchParamsVariance>();
    out->tag_ = Tag::kNoVaryParams;
    out->params_ = std::move(params);
    return out;
  }

  static std::unique_ptr<SearchParamsVariance> NewVaryParams(
      std::vector<std::string> params) {
    auto out = std::make_unique<SearchParamsVariance>();
    out->tag_ = Tag::kVaryParams;
    out->params_ = std::move(params);
    return out;
  }

  bool is_no_vary_params() const { return tag_ == Tag::kNoVaryParams; }
  bool is_vary_params() const { return tag_ == Tag::kVaryParams; }
  const std::vector<std::string>& get_no_vary_params() const {
    return params_;
  }
  const std::vector<std::string>& get_vary_params() const {
    return params_;
  }

 private:
  Tag tag_ = Tag::kNoVaryParams;
  std::vector<std::string> params_;
};
using SearchParamsVariancePtr = std::unique_ptr<SearchParamsVariance>;

struct NoVarySearch {
  static std::unique_ptr<NoVarySearch> New(
      SearchParamsVariancePtr search_params_variance,
      bool vary_on_key_order) {
    auto out = std::make_unique<NoVarySearch>();
    out->search_variance = std::move(search_params_variance);
    out->vary_on_key_order = vary_on_key_order;
    return out;
  }

  SearchParamsVariancePtr search_variance;
  bool vary_on_key_order = true;
};
using NoVarySearchPtr = std::unique_ptr<NoVarySearch>;

struct NoVarySearchWithParseError {
  static std::unique_ptr<NoVarySearchWithParseError> NewParseError(
      NoVarySearchParseError error) {
    auto out = std::make_unique<NoVarySearchWithParseError>();
    out->tag_ = Tag::kParseError;
    out->parse_error_ = error;
    return out;
  }

  static std::unique_ptr<NoVarySearchWithParseError> NewNoVarySearch(
      NoVarySearchPtr no_vary_search) {
    auto out = std::make_unique<NoVarySearchWithParseError>();
    out->tag_ = Tag::kNoVarySearch;
    out->no_vary_search_ = std::move(no_vary_search);
    return out;
  }

  bool is_parse_error() const { return tag_ == Tag::kParseError; }
  NoVarySearchParseError get_parse_error() const { return parse_error_; }
  const NoVarySearchPtr& get_no_vary_search() const {
    return no_vary_search_;
  }

 private:
  enum class Tag { kParseError, kNoVarySearch };
  Tag tag_ = Tag::kParseError;
  NoVarySearchParseError parse_error_ = NoVarySearchParseError::kOk;
  NoVarySearchPtr no_vary_search_;
};
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
