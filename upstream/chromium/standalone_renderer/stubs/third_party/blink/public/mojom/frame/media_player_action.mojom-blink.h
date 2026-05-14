#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_MEDIA_PLAYER_ACTION_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_MEDIA_PLAYER_ACTION_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/frame/media_player_action.mojom-blink-forward.h"

namespace blink::mojom::blink {

struct MediaPlayerAction {
  MediaPlayerActionType type = MediaPlayerActionType::kPictureInPicture;
  bool enable = false;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_MEDIA_PLAYER_ACTION_MOJOM_BLINK_H_
