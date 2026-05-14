#ifndef SRC_TRACE_PROCESSOR_TABLES_SLICE_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_SLICE_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/profiler_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/track_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct SliceTable_Id : BaseId {
  SliceTable_Id() = default;
  explicit constexpr SliceTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SliceTable_Id& other) const {
    return value == other.value;
  }
};

struct AndroidNetworkPacketsTable_Id : BaseId {
  AndroidNetworkPacketsTable_Id() = default;
  explicit constexpr AndroidNetworkPacketsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const AndroidNetworkPacketsTable_Id& other) const {
    return value == other.value;
  }
};

struct TrackEventCallstacksTable_Id : BaseId {
  TrackEventCallstacksTable_Id() = default;
  explicit constexpr TrackEventCallstacksTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const TrackEventCallstacksTable_Id& other) const {
    return value == other.value;
  }
};

class SliceTable;
class AndroidNetworkPacketsTable;
class TrackEventCallstacksTable;

// Tuple of all table types in this header
using SLICE_TABLES_FWD_TABLES = std::tuple<SliceTable, AndroidNetworkPacketsTable, TrackEventCallstacksTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_SLICE_TABLES_FWD_H_

