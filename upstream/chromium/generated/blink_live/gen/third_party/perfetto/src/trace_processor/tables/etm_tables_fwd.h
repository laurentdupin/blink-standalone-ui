#ifndef SRC_TRACE_PROCESSOR_TABLES_ETM_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_ETM_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export



namespace perfetto::trace_processor::tables {

struct EtmV4ConfigurationTable_Id : BaseId {
  EtmV4ConfigurationTable_Id() = default;
  explicit constexpr EtmV4ConfigurationTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const EtmV4ConfigurationTable_Id& other) const {
    return value == other.value;
  }
};

struct EtmV4SessionTable_Id : BaseId {
  EtmV4SessionTable_Id() = default;
  explicit constexpr EtmV4SessionTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const EtmV4SessionTable_Id& other) const {
    return value == other.value;
  }
};

struct EtmV4ChunkTable_Id : BaseId {
  EtmV4ChunkTable_Id() = default;
  explicit constexpr EtmV4ChunkTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const EtmV4ChunkTable_Id& other) const {
    return value == other.value;
  }
};

struct FileTable_Id : BaseId {
  FileTable_Id() = default;
  explicit constexpr FileTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const FileTable_Id& other) const {
    return value == other.value;
  }
};

struct ElfFileTable_Id : BaseId {
  ElfFileTable_Id() = default;
  explicit constexpr ElfFileTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ElfFileTable_Id& other) const {
    return value == other.value;
  }
};

class EtmV4ConfigurationTable;
class EtmV4SessionTable;
class EtmV4ChunkTable;
class FileTable;
class ElfFileTable;

// Tuple of all table types in this header
using ETM_TABLES_FWD_TABLES = std::tuple<EtmV4ConfigurationTable, EtmV4SessionTable, EtmV4ChunkTable, FileTable, ElfFileTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_ETM_TABLES_FWD_H_

