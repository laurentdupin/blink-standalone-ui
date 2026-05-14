#ifndef SRC_TRACE_PROCESSOR_TABLES_WINSCOPE_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_WINSCOPE_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export



namespace perfetto::trace_processor::tables {

struct WinscopeRectTable_Id : BaseId {
  WinscopeRectTable_Id() = default;
  explicit constexpr WinscopeRectTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WinscopeRectTable_Id& other) const {
    return value == other.value;
  }
};

struct WinscopeTransformTable_Id : BaseId {
  WinscopeTransformTable_Id() = default;
  explicit constexpr WinscopeTransformTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WinscopeTransformTable_Id& other) const {
    return value == other.value;
  }
};

struct WinscopeTraceRectTable_Id : BaseId {
  WinscopeTraceRectTable_Id() = default;
  explicit constexpr WinscopeTraceRectTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WinscopeTraceRectTable_Id& other) const {
    return value == other.value;
  }
};

struct InputMethodClientsTable_Id : BaseId {
  InputMethodClientsTable_Id() = default;
  explicit constexpr InputMethodClientsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const InputMethodClientsTable_Id& other) const {
    return value == other.value;
  }
};

struct InputMethodManagerServiceTable_Id : BaseId {
  InputMethodManagerServiceTable_Id() = default;
  explicit constexpr InputMethodManagerServiceTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const InputMethodManagerServiceTable_Id& other) const {
    return value == other.value;
  }
};

struct InputMethodServiceTable_Id : BaseId {
  InputMethodServiceTable_Id() = default;
  explicit constexpr InputMethodServiceTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const InputMethodServiceTable_Id& other) const {
    return value == other.value;
  }
};

struct SurfaceFlingerLayersSnapshotTable_Id : BaseId {
  SurfaceFlingerLayersSnapshotTable_Id() = default;
  explicit constexpr SurfaceFlingerLayersSnapshotTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SurfaceFlingerLayersSnapshotTable_Id& other) const {
    return value == other.value;
  }
};

struct SurfaceFlingerDisplayTable_Id : BaseId {
  SurfaceFlingerDisplayTable_Id() = default;
  explicit constexpr SurfaceFlingerDisplayTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SurfaceFlingerDisplayTable_Id& other) const {
    return value == other.value;
  }
};

struct SurfaceFlingerLayerTable_Id : BaseId {
  SurfaceFlingerLayerTable_Id() = default;
  explicit constexpr SurfaceFlingerLayerTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SurfaceFlingerLayerTable_Id& other) const {
    return value == other.value;
  }
};

struct WinscopeFillRegionTable_Id : BaseId {
  WinscopeFillRegionTable_Id() = default;
  explicit constexpr WinscopeFillRegionTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WinscopeFillRegionTable_Id& other) const {
    return value == other.value;
  }
};

struct SurfaceFlingerTransactionsTable_Id : BaseId {
  SurfaceFlingerTransactionsTable_Id() = default;
  explicit constexpr SurfaceFlingerTransactionsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SurfaceFlingerTransactionsTable_Id& other) const {
    return value == other.value;
  }
};

struct SurfaceFlingerTransactionTable_Id : BaseId {
  SurfaceFlingerTransactionTable_Id() = default;
  explicit constexpr SurfaceFlingerTransactionTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SurfaceFlingerTransactionTable_Id& other) const {
    return value == other.value;
  }
};

struct SurfaceFlingerTransactionFlagTable_Id : BaseId {
  SurfaceFlingerTransactionFlagTable_Id() = default;
  explicit constexpr SurfaceFlingerTransactionFlagTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const SurfaceFlingerTransactionFlagTable_Id& other) const {
    return value == other.value;
  }
};

struct ViewCaptureTable_Id : BaseId {
  ViewCaptureTable_Id() = default;
  explicit constexpr ViewCaptureTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ViewCaptureTable_Id& other) const {
    return value == other.value;
  }
};

struct ViewCaptureViewTable_Id : BaseId {
  ViewCaptureViewTable_Id() = default;
  explicit constexpr ViewCaptureViewTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ViewCaptureViewTable_Id& other) const {
    return value == other.value;
  }
};

struct ViewCaptureInternedDataTable_Id : BaseId {
  ViewCaptureInternedDataTable_Id() = default;
  explicit constexpr ViewCaptureInternedDataTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ViewCaptureInternedDataTable_Id& other) const {
    return value == other.value;
  }
};

struct WindowManagerShellTransitionsTable_Id : BaseId {
  WindowManagerShellTransitionsTable_Id() = default;
  explicit constexpr WindowManagerShellTransitionsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WindowManagerShellTransitionsTable_Id& other) const {
    return value == other.value;
  }
};

struct WindowManagerShellTransitionHandlersTable_Id : BaseId {
  WindowManagerShellTransitionHandlersTable_Id() = default;
  explicit constexpr WindowManagerShellTransitionHandlersTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WindowManagerShellTransitionHandlersTable_Id& other) const {
    return value == other.value;
  }
};

struct WindowManagerShellTransitionParticipantsTable_Id : BaseId {
  WindowManagerShellTransitionParticipantsTable_Id() = default;
  explicit constexpr WindowManagerShellTransitionParticipantsTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WindowManagerShellTransitionParticipantsTable_Id& other) const {
    return value == other.value;
  }
};

struct WindowManagerShellTransitionProtosTable_Id : BaseId {
  WindowManagerShellTransitionProtosTable_Id() = default;
  explicit constexpr WindowManagerShellTransitionProtosTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WindowManagerShellTransitionProtosTable_Id& other) const {
    return value == other.value;
  }
};

struct WindowManagerTable_Id : BaseId {
  WindowManagerTable_Id() = default;
  explicit constexpr WindowManagerTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WindowManagerTable_Id& other) const {
    return value == other.value;
  }
};

struct WindowManagerWindowContainerTable_Id : BaseId {
  WindowManagerWindowContainerTable_Id() = default;
  explicit constexpr WindowManagerWindowContainerTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const WindowManagerWindowContainerTable_Id& other) const {
    return value == other.value;
  }
};

struct ProtoLogTable_Id : BaseId {
  ProtoLogTable_Id() = default;
  explicit constexpr ProtoLogTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const ProtoLogTable_Id& other) const {
    return value == other.value;
  }
};

class WinscopeRectTable;
class WinscopeTransformTable;
class WinscopeTraceRectTable;
class InputMethodClientsTable;
class InputMethodManagerServiceTable;
class InputMethodServiceTable;
class SurfaceFlingerLayersSnapshotTable;
class SurfaceFlingerDisplayTable;
class SurfaceFlingerLayerTable;
class WinscopeFillRegionTable;
class SurfaceFlingerTransactionsTable;
class SurfaceFlingerTransactionTable;
class SurfaceFlingerTransactionFlagTable;
class ViewCaptureTable;
class ViewCaptureViewTable;
class ViewCaptureInternedDataTable;
class WindowManagerShellTransitionsTable;
class WindowManagerShellTransitionHandlersTable;
class WindowManagerShellTransitionParticipantsTable;
class WindowManagerShellTransitionProtosTable;
class WindowManagerTable;
class WindowManagerWindowContainerTable;
class ProtoLogTable;

// Tuple of all table types in this header
using WINSCOPE_TABLES_FWD_TABLES = std::tuple<WinscopeRectTable, WinscopeTransformTable, WinscopeTraceRectTable, InputMethodClientsTable, InputMethodManagerServiceTable, InputMethodServiceTable, SurfaceFlingerLayersSnapshotTable, SurfaceFlingerDisplayTable, SurfaceFlingerLayerTable, WinscopeFillRegionTable, SurfaceFlingerTransactionsTable, SurfaceFlingerTransactionTable, SurfaceFlingerTransactionFlagTable, ViewCaptureTable, ViewCaptureViewTable, ViewCaptureInternedDataTable, WindowManagerShellTransitionsTable, WindowManagerShellTransitionHandlersTable, WindowManagerShellTransitionParticipantsTable, WindowManagerShellTransitionProtosTable, WindowManagerTable, WindowManagerWindowContainerTable, ProtoLogTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_WINSCOPE_TABLES_FWD_H_

