#ifndef STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_TRACK_EVENT_PBZERO_H_
#define STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACK_EVENT_TRACK_EVENT_PBZERO_H_

#include "perfetto/protozero/message.h"

namespace perfetto::protos::pbzero {
class TrackEvent : public ::protozero::Message {
 public:
  class LegacyEvent : public ::protozero::Message {
   public:
    enum Phase {
      PHASE_UNSPECIFIED = 0,
      PHASE_BEGIN = 1,
      PHASE_END = 2,
      PHASE_INSTANT = 3,
    };
    enum FlowDirection {
      FLOW_UNSPECIFIED = 0,
      FLOW_IN = 1,
      FLOW_OUT = 2,
      FLOW_INOUT = 3,
    };
    void set_pid_override(int) {}
    void set_tid_override(int) {}
    void set_phase(Phase) {}
    void set_phase(char) {}
    void set_use_async_tts(bool) {}
    void set_bind_to_enclosing(bool) {}
    void set_flow_direction(FlowDirection) {}
  };
  enum Type {
    TYPE_UNSPECIFIED = 0,
    TYPE_SLICE_BEGIN = 1,
    TYPE_SLICE_END = 2,
    TYPE_INSTANT = 3,
    TYPE_COUNTER = 4,
  };
  LegacyEvent* set_legacy_event() { return nullptr; }
  void add_flow_ids(unsigned long long) {}
  void add_terminating_flow_ids(unsigned long long) {}
  void set_counter_value(long long) {}
  void set_counter_value(unsigned long long) {}
  void set_double_counter_value(double) {}
  void add_categories(const char*) {}
  void add_categories(const char*, unsigned long long) {}
  void set_track_uuid(unsigned long long) {}
};
}
#endif
