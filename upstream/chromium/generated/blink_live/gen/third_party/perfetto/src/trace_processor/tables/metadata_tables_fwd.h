#ifndef SRC_TRACE_PROCESSOR_TABLES_METADATA_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_METADATA_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export



namespace perfetto::trace_processor::tables {

struct MachineTable_Id : BaseId {
  MachineTable_Id() = default;
  explicit constexpr MachineTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const MachineTable_Id& other) const {
    return value == other.value;
  }
};

struct ProcessTable_Id : BaseId {
  ProcessTable_Id() = default;
  explicit constexpr ProcessTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ProcessTable_Id& other) const {
    return value == other.value;
  }
};

struct ThreadTable_Id : BaseId {
  ThreadTable_Id() = default;
  explicit constexpr ThreadTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ThreadTable_Id& other) const {
    return value == other.value;
  }
};

struct ArgTable_Id : BaseId {
  ArgTable_Id() = default;
  explicit constexpr ArgTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ArgTable_Id& other) const {
    return value == other.value;
  }
};

struct BuildFlagsTable_Id : BaseId {
  BuildFlagsTable_Id() = default;
  explicit constexpr BuildFlagsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const BuildFlagsTable_Id& other) const {
    return value == other.value;
  }
};

struct ChromeRawTable_Id : BaseId {
  ChromeRawTable_Id() = default;
  explicit constexpr ChromeRawTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ChromeRawTable_Id& other) const {
    return value == other.value;
  }
};

struct ClockSnapshotTable_Id : BaseId {
  ClockSnapshotTable_Id() = default;
  explicit constexpr ClockSnapshotTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ClockSnapshotTable_Id& other) const {
    return value == other.value;
  }
};

struct CpuTable_Id : BaseId {
  CpuTable_Id() = default;
  explicit constexpr CpuTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const CpuTable_Id& other) const {
    return value == other.value;
  }
};

struct CpuFreqTable_Id : BaseId {
  CpuFreqTable_Id() = default;
  explicit constexpr CpuFreqTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const CpuFreqTable_Id& other) const {
    return value == other.value;
  }
};

struct ExpMissingChromeProcTable_Id : BaseId {
  ExpMissingChromeProcTable_Id() = default;
  explicit constexpr ExpMissingChromeProcTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ExpMissingChromeProcTable_Id& other) const {
    return value == other.value;
  }
};

struct FiledescriptorTable_Id : BaseId {
  FiledescriptorTable_Id() = default;
  explicit constexpr FiledescriptorTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const FiledescriptorTable_Id& other) const {
    return value == other.value;
  }
};

struct FtraceEventTable_Id : BaseId {
  FtraceEventTable_Id() = default;
  explicit constexpr FtraceEventTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const FtraceEventTable_Id& other) const {
    return value == other.value;
  }
};

struct GpuTable_Id : BaseId {
  GpuTable_Id() = default;
  explicit constexpr GpuTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const GpuTable_Id& other) const {
    return value == other.value;
  }
};

struct TraceFileTable_Id : BaseId {
  TraceFileTable_Id() = default;
  explicit constexpr TraceFileTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const TraceFileTable_Id& other) const {
    return value == other.value;
  }
};

struct TraceImportLogsTable_Id : BaseId {
  TraceImportLogsTable_Id() = default;
  explicit constexpr TraceImportLogsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const TraceImportLogsTable_Id& other) const {
    return value == other.value;
  }
};

struct MetadataTable_Id : BaseId {
  MetadataTable_Id() = default;
  explicit constexpr MetadataTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const MetadataTable_Id& other) const {
    return value == other.value;
  }
};

struct ModulesTable_Id : BaseId {
  ModulesTable_Id() = default;
  explicit constexpr ModulesTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ModulesTable_Id& other) const {
    return value == other.value;
  }
};

class MachineTable;
class ProcessTable;
class ThreadTable;
class ArgTable;
class BuildFlagsTable;
class ChromeRawTable;
class ClockSnapshotTable;
class CpuTable;
class CpuFreqTable;
class ExpMissingChromeProcTable;
class FiledescriptorTable;
class FtraceEventTable;
class GpuTable;
class TraceFileTable;
class TraceImportLogsTable;
class MetadataTable;
class ModulesTable;

// Tuple of all table types in this header
using METADATA_TABLES_FWD_TABLES = std::tuple<MachineTable, ProcessTable, ThreadTable, ArgTable, BuildFlagsTable, ChromeRawTable, ClockSnapshotTable, CpuTable, CpuFreqTable, ExpMissingChromeProcTable, FiledescriptorTable, FtraceEventTable, GpuTable, TraceFileTable, TraceImportLogsTable, MetadataTable, ModulesTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_METADATA_TABLES_FWD_H_

