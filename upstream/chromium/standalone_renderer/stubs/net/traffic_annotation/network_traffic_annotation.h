#ifndef STANDALONE_RENDERER_STUBS_NET_TRAFFIC_ANNOTATION_NETWORK_TRAFFIC_ANNOTATION_H_
#define STANDALONE_RENDERER_STUBS_NET_TRAFFIC_ANNOTATION_NETWORK_TRAFFIC_ANNOTATION_H_

#include <cstdint>

namespace net {

struct NetworkTrafficAnnotationTag {
  int32_t unique_id_hash_code = 0;

  static constexpr NetworkTrafficAnnotationTag NotReached() { return {}; }
};

class MutableNetworkTrafficAnnotationTag {
 public:
  constexpr MutableNetworkTrafficAnnotationTag() = default;
  constexpr MutableNetworkTrafficAnnotationTag(NetworkTrafficAnnotationTag tag)
      : tag_(tag) {}

  constexpr operator NetworkTrafficAnnotationTag() const { return tag_; }

 private:
  NetworkTrafficAnnotationTag tag_;
};

class MutablePartialNetworkTrafficAnnotationTag {
 public:
  constexpr MutablePartialNetworkTrafficAnnotationTag() = default;
  constexpr explicit MutablePartialNetworkTrafficAnnotationTag(
      NetworkTrafficAnnotationTag tag)
      : tag_(tag) {}

  constexpr operator MutableNetworkTrafficAnnotationTag() const {
    return MutableNetworkTrafficAnnotationTag(tag_);
  }

 private:
  NetworkTrafficAnnotationTag tag_;
};

template <size_t N>
constexpr NetworkTrafficAnnotationTag DefineNetworkTrafficAnnotation(
    const char (&)[N],
    const char*) {
  return {};
}

template <size_t N>
constexpr NetworkTrafficAnnotationTag DefineNetworkTrafficAnnotation(
    const char (&)[N],
    NetworkTrafficAnnotationTag) {
  return {};
}

template <size_t N>
constexpr MutablePartialNetworkTrafficAnnotationTag
DefinePartialNetworkTrafficAnnotation(const char (&)[N], const char*) {
  return {};
}

}  // namespace net

#endif  // STANDALONE_RENDERER_STUBS_NET_TRAFFIC_ANNOTATION_NETWORK_TRAFFIC_ANNOTATION_H_
