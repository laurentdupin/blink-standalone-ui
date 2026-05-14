#ifndef STANDALONE_RENDERER_STUBS_SERVICES_MEDIA_SESSION_PUBLIC_MOJOM_MEDIA_SESSION_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_MEDIA_SESSION_PUBLIC_MOJOM_MEDIA_SESSION_MOJOM_BLINK_FORWARD_H_

#include <memory>

namespace media_session::mojom::blink {

struct MediaPosition {};
using MediaPositionPtr = std::unique_ptr<MediaPosition>;
class MediaSession;
class MediaSessionObserver;

}  // namespace media_session::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_MEDIA_SESSION_PUBLIC_MOJOM_MEDIA_SESSION_MOJOM_BLINK_FORWARD_H_
