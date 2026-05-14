#ifndef SRC_TRACE_PROCESSOR_TABLES_COUNTER_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_COUNTER_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/track_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct CounterTable_Id : BaseId {
  CounterTable_Id() = default;
  explicit constexpr CounterTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const CounterTable_Id& other) const {
    return value == other.value;
  }
};

class CounterTable;

// Tuple of all table types in this header
using COUNTER_TABLES_FWD_TABLES = std::tuple<CounterTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_COUNTER_TABLES_FWD_H_

