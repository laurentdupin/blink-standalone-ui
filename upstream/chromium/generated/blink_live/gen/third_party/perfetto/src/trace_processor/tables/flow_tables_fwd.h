#ifndef SRC_TRACE_PROCESSOR_TABLES_FLOW_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_FLOW_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/slice_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct FlowTable_Id : BaseId {
  FlowTable_Id() = default;
  explicit constexpr FlowTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const FlowTable_Id& other) const {
    return value == other.value;
  }
};

class FlowTable;

// Tuple of all table types in this header
using FLOW_TABLES_FWD_TABLES = std::tuple<FlowTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_FLOW_TABLES_FWD_H_

