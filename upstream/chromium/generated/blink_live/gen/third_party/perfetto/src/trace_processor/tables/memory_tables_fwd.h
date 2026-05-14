#ifndef SRC_TRACE_PROCESSOR_TABLES_MEMORY_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_MEMORY_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/track_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct MemorySnapshotTable_Id : BaseId {
  MemorySnapshotTable_Id() = default;
  explicit constexpr MemorySnapshotTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const MemorySnapshotTable_Id& other) const {
    return value == other.value;
  }
};

struct ProcessMemorySnapshotTable_Id : BaseId {
  ProcessMemorySnapshotTable_Id() = default;
  explicit constexpr ProcessMemorySnapshotTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ProcessMemorySnapshotTable_Id& other) const {
    return value == other.value;
  }
};

struct MemorySnapshotNodeTable_Id : BaseId {
  MemorySnapshotNodeTable_Id() = default;
  explicit constexpr MemorySnapshotNodeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const MemorySnapshotNodeTable_Id& other) const {
    return value == other.value;
  }
};

struct MemorySnapshotEdgeTable_Id : BaseId {
  MemorySnapshotEdgeTable_Id() = default;
  explicit constexpr MemorySnapshotEdgeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const MemorySnapshotEdgeTable_Id& other) const {
    return value == other.value;
  }
};

class MemorySnapshotTable;
class ProcessMemorySnapshotTable;
class MemorySnapshotNodeTable;
class MemorySnapshotEdgeTable;

// Tuple of all table types in this header
using MEMORY_TABLES_FWD_TABLES = std::tuple<MemorySnapshotTable, ProcessMemorySnapshotTable, MemorySnapshotNodeTable, MemorySnapshotEdgeTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_MEMORY_TABLES_FWD_H_

