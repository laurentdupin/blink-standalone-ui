#ifndef SRC_TRACE_PROCESSOR_TABLES_TRACE_PROTO_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_TRACE_PROTO_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export



namespace perfetto::trace_processor::tables {

struct ExperimentalProtoPathTable_Id : BaseId {
  ExperimentalProtoPathTable_Id() = default;
  explicit constexpr ExperimentalProtoPathTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ExperimentalProtoPathTable_Id& other) const {
    return value == other.value;
  }
};

struct ExperimentalProtoContentTable_Id : BaseId {
  ExperimentalProtoContentTable_Id() = default;
  explicit constexpr ExperimentalProtoContentTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ExperimentalProtoContentTable_Id& other) const {
    return value == other.value;
  }
};

class ExperimentalProtoPathTable;
class ExperimentalProtoContentTable;

// Tuple of all table types in this header
using TRACE_PROTO_TABLES_FWD_TABLES = std::tuple<ExperimentalProtoPathTable, ExperimentalProtoContentTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_TRACE_PROTO_TABLES_FWD_H_

