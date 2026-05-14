#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_MEDIA_PLAYER_ACTION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_MEDIA_PLAYER_ACTION_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace blink::mojom::blink {
enum class MediaPlayerActionType {
  kLoop,
  kControls,
  kSaveVideoFrameAs,
  kCopyVideoFrame,
  kPictureInPicture,
  kDefaultActionType = kPictureInPicture,
};
struct MediaPlayerAction;
using MediaPlayerActionPtr = std::unique_ptr<MediaPlayerAction>;
}
#endif
