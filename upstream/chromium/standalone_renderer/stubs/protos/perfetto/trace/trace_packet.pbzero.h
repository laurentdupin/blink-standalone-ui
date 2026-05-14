// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACE_PACKET_PBZERO_H_
#define STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACE_PACKET_PBZERO_H_

#include "perfetto/protozero/message.h"

namespace perfetto::protos::pbzero {

class TrackDescriptor;

class TracePacket : public ::protozero::Message {
 public:
  enum SequenceFlags {
    SEQ_UNSPECIFIED = 0,
    SEQ_INCREMENTAL_STATE_CLEARED = 1,
    SEQ_NEEDS_INCREMENTAL_STATE = 2,
  };
  TrackDescriptor* set_track_descriptor() { return nullptr; }
};

}  // namespace perfetto::protos::pbzero

#endif  // STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_TRACE_TRACE_PACKET_PBZERO_H_
