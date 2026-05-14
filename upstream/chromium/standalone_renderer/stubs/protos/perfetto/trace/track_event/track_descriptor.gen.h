#ifndef STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_TRACK_DESCRIPTOR_GEN_H_
#define STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_TRACK_DESCRIPTOR_GEN_H_

#include <string>

namespace perfetto::protos::gen {
class TrackDescriptor {
 public:
  enum SiblingMergeBehavior {
    SIBLING_MERGE_BEHAVIOR_UNSPECIFIED = 0,
    SIBLING_MERGE_BEHAVIOR_NONE = 1,
    SIBLING_MERGE_BEHAVIOR_BY_SIBLING_MERGE_KEY = 2,
  };
  unsigned long long uuid() const { return 0; }
  std::string SerializeAsString() const { return {}; }
};
}  // namespace perfetto::protos::gen
#endif
