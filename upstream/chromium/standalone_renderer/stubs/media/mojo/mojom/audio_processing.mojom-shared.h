#ifndef STANDALONE_RENDERER_STUBS_MEDIA_MOJO_MOJOM_AUDIO_PROCESSING_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_MEDIA_MOJO_MOJOM_AUDIO_PROCESSING_MOJOM_SHARED_H_

#include <memory>

namespace media::mojom {

struct AudioProcessingStats {};
using AudioProcessingStatsPtr = std::unique_ptr<AudioProcessingStats>;

struct AudioProcessingSettings {
  bool echo_cancellation = false;
  bool noise_suppression = false;
  bool automatic_gain_control = false;
  bool multi_channel_capture_processing = false;
  bool use_loopback_aec_reference = false;
};

class AudioProcessorControls;
using AudioProcessorControlsInterfaceBase = AudioProcessorControls;

struct AudioProcessingConfig {
  AudioProcessingSettings settings;
};

}  // namespace media::mojom

#endif  // STANDALONE_RENDERER_STUBS_MEDIA_MOJO_MOJOM_AUDIO_PROCESSING_MOJOM_SHARED_H_
