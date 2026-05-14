#ifndef SRC_TRACE_PROCESSOR_TABLES_SCHED_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_SCHED_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/metadata_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct SchedSliceTable_Id : BaseId {
  SchedSliceTable_Id() = default;
  explicit constexpr SchedSliceTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SchedSliceTable_Id& other) const {
    return value == other.value;
  }
};

struct SpuriousSchedWakeupTable_Id : BaseId {
  SpuriousSchedWakeupTable_Id() = default;
  explicit constexpr SpuriousSchedWakeupTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SpuriousSchedWakeupTable_Id& other) const {
    return value == other.value;
  }
};

struct ThreadStateTable_Id : BaseId {
  ThreadStateTable_Id() = default;
  explicit constexpr ThreadStateTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ThreadStateTable_Id& other) const {
    return value == other.value;
  }
};

class SchedSliceTable;
class SpuriousSchedWakeupTable;
class ThreadStateTable;

// Tuple of all table types in this header
using SCHED_TABLES_FWD_TABLES = std::tuple<SchedSliceTable, SpuriousSchedWakeupTable, ThreadStateTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_SCHED_TABLES_FWD_H_

