#ifndef SRC_TRACE_PROCESSOR_TABLES_JIT_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_JIT_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/profiler_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct JitCodeTable_Id : BaseId {
  JitCodeTable_Id() = default;
  explicit constexpr JitCodeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const JitCodeTable_Id& other) const {
    return value == other.value;
  }
};

struct JitFrameTable_Id : BaseId {
  JitFrameTable_Id() = default;
  explicit constexpr JitFrameTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const JitFrameTable_Id& other) const {
    return value == other.value;
  }
};

class JitCodeTable;
class JitFrameTable;

// Tuple of all table types in this header
using JIT_TABLES_FWD_TABLES = std::tuple<JitCodeTable, JitFrameTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_JIT_TABLES_FWD_H_

