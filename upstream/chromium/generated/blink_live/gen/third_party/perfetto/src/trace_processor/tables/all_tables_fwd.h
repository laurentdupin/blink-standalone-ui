#ifndef SRC_TRACE_PROCESSOR_TABLES_ALL_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_ALL_TABLES_FWD_H_

#include <cstddef>
#include <variant>

#include "perfetto/ext/base/variant.h"

#include "src/trace_processor/tables/android_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/counter_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/etm_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/flow_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/jit_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/memory_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/metadata_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/perf_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/profiler_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/sched_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/slice_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/trace_proto_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/track_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/v8_tables_fwd.h"  // IWYU pragma: export
#include "src/trace_processor/tables/winscope_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

// Variant of all table types (use base::variant_index<AllTables, T>() to get index)
using AllTables = std::variant<AndroidAflagsTable, AndroidCpuPerUidTrackTable, AndroidDumpstateTable, AndroidGameInterventionListTable, AndroidInputEventDispatchTable, AndroidKeyEventsTable, AndroidLogTable, AndroidMotionEventsTable, AndroidUserListTable, MachineTable, ProcessTable, ThreadTable, ArgTable, BuildFlagsTable, ChromeRawTable, ClockSnapshotTable, CpuTable, CpuFreqTable, ExpMissingChromeProcTable, FiledescriptorTable, FtraceEventTable, GpuTable, TraceFileTable, TraceImportLogsTable, MetadataTable, ModulesTable, TrackTable, CounterTable, EtmV4ConfigurationTable, EtmV4SessionTable, EtmV4ChunkTable, FileTable, ElfFileTable, SliceTable, AndroidNetworkPacketsTable, TrackEventCallstacksTable, FlowTable, JitCodeTable, JitFrameTable, StackProfileMappingTable, StackProfileFrameTable, AggregateProfileTable, StackProfileCallsiteTable, AggregateSampleTable, CpuProfileStackSampleTable, ExperimentalFlamegraphTable, GpuContextTable, GpuCounterGroupTable, HeapGraphClassTable, HeapGraphObjectDataTable, HeapGraphPrimitiveTable, HeapGraphObjectTable, HeapGraphReferenceTable, HeapProfileAllocationTable, InstrumentsSampleTable, PackageListTable, PerfCounterSetTable, PerfSessionTable, PerfSampleTable, ProfilerSmapsTable, SymbolTable, VulkanMemoryAllocationsTable, MemorySnapshotTable, ProcessMemorySnapshotTable, MemorySnapshotNodeTable, MemorySnapshotEdgeTable, SpeRecordTable, MmapRecordTable, SchedSliceTable, SpuriousSchedWakeupTable, ThreadStateTable, ExperimentalProtoPathTable, ExperimentalProtoContentTable, V8IsolateTable, V8JsScriptTable, V8WasmScriptTable, V8JsFunctionTable, V8JsCodeTable, V8InternalCodeTable, V8WasmCodeTable, V8RegexpCodeTable, WinscopeRectTable, WinscopeTransformTable, WinscopeTraceRectTable, InputMethodClientsTable, InputMethodManagerServiceTable, InputMethodServiceTable, SurfaceFlingerLayersSnapshotTable, SurfaceFlingerDisplayTable, SurfaceFlingerLayerTable, WinscopeFillRegionTable, SurfaceFlingerTransactionsTable, SurfaceFlingerTransactionTable, SurfaceFlingerTransactionFlagTable, ViewCaptureTable, ViewCaptureViewTable, ViewCaptureInternedDataTable, WindowManagerShellTransitionsTable, WindowManagerShellTransitionHandlersTable, WindowManagerShellTransitionParticipantsTable, WindowManagerShellTransitionProtosTable, WindowManagerTable, WindowManagerWindowContainerTable, ProtoLogTable>;

// Count of all tables
inline constexpr size_t kTableCount = std::variant_size_v<AllTables>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_ALL_TABLES_FWD_H_
