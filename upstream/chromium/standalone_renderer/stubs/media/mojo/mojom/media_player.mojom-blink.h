// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_MEDIA_MOJO_MOJOM_MEDIA_PLAYER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_MEDIA_MOJO_MOJOM_MEDIA_PLAYER_MOJOM_BLINK_H_

namespace media::mojom::blink {

class MediaPlayer {
 public:
  class Proxy_ {};
  virtual ~MediaPlayer() = default;
};

class MediaPlayerHost {
 public:
  class Proxy_ {};
  virtual ~MediaPlayerHost() = default;
};

class MediaPlayerObserver {
 public:
  class Proxy_ {};
  virtual ~MediaPlayerObserver() = default;
};

}  // namespace media::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_MEDIA_MOJO_MOJOM_MEDIA_PLAYER_MOJOM_BLINK_H_
