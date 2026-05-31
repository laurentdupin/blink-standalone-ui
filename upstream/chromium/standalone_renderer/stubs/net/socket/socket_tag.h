#ifndef STANDALONE_RENDERER_STUBS_NET_SOCKET_SOCKET_TAG_H_
#define STANDALONE_RENDERER_STUBS_NET_SOCKET_SOCKET_TAG_H_

namespace net {

class SocketTag {
 public:
  SocketTag() = default;
  bool operator==(const SocketTag&) const = default;
};

}  // namespace net

#endif  // STANDALONE_RENDERER_STUBS_NET_SOCKET_SOCKET_TAG_H_
