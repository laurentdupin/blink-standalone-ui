#ifndef STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_CONFIG_TRACK_EVENT_TRACK_EVENT_CONFIG_GEN_H_
#define STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_CONFIG_TRACK_EVENT_TRACK_EVENT_CONFIG_GEN_H_

#include <cstdint>
#include <string>
#include <vector>

namespace perfetto::protos::gen {
class TrackEventConfig {
 public:
  bool ParseFromArray(const void*, int) { return true; }
  bool ParseFromString(const std::string&) { return true; }
  const std::vector<std::string>& enabled_categories() const {
    static const std::vector<std::string>* empty = new std::vector<std::string>();
    return *empty;
  }
  const std::vector<std::string>& disabled_categories() const {
    return enabled_categories();
  }
  const std::vector<std::string>& enabled_tags() const {
    return enabled_categories();
  }
  const std::vector<std::string>& disabled_tags() const {
    return enabled_categories();
  }
  bool filter_debug_annotations() const { return false; }
  bool filter_dynamic_event_names() const { return false; }
  bool disable_incremental_timestamps() const { return false; }
  bool enable_thread_time_sampling() const { return false; }
  uint32_t thread_time_subsampling_ns() const { return 0; }
  bool has_timestamp_unit_multiplier() const { return false; }
  uint32_t timestamp_unit_multiplier() const { return 1; }
};
}
#endif
