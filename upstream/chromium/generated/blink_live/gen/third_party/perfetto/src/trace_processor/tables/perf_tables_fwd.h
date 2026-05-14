#ifndef SRC_TRACE_PROCESSOR_TABLES_PERF_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_PERF_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/etm_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/metadata_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/profiler_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct SpeRecordTable_Id : BaseId {
  SpeRecordTable_Id() = default;
  explicit constexpr SpeRecordTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SpeRecordTable_Id& other) const {
    return value == other.value;
  }
};

struct MmapRecordTable_Id : BaseId {
  MmapRecordTable_Id() = default;
  explicit constexpr MmapRecordTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const MmapRecordTable_Id& other) const {
    return value == other.value;
  }
};

class SpeRecordTable;
class MmapRecordTable;

// Tuple of all table types in this header
using PERF_TABLES_FWD_TABLES = std::tuple<SpeRecordTable, MmapRecordTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_PERF_TABLES_FWD_H_

