// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_CONFIG_DATA_SOURCE_CONFIG_GEN_H_
#define STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_CONFIG_DATA_SOURCE_CONFIG_GEN_H_

#include <string>

namespace perfetto::protos::gen {

class DataSourceConfig {
 public:
  const std::string& track_event_config_raw() const {
    static const std::string* empty = new std::string();
    return *empty;
  }
  bool disable_incremental_timestamps() const { return false; }
  bool filter_debug_annotations() const { return false; }
  bool filter_dynamic_event_names() const { return false; }
  bool enable_thread_time_sampling() const { return false; }
  unsigned thread_time_subsampling_ns() const { return 0; }
  bool has_timestamp_unit_multiplier() const { return false; }
  unsigned timestamp_unit_multiplier() const { return 1; }
};

}  // namespace perfetto::protos::gen

#endif  // STANDALONE_RENDERER_STUBS_PROTOS_PERFETTO_CONFIG_DATA_SOURCE_CONFIG_GEN_H_
