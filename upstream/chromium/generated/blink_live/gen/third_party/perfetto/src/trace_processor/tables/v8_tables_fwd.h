#ifndef SRC_TRACE_PROCESSOR_TABLES_V8_TABLES_FWD_H_
#define SRC_TRACE_PROCESSOR_TABLES_V8_TABLES_FWD_H_

#include <cstdint>
#include <tuple>

#include "src/trace_processor/tables/macros_internal.h"  // IWYU pragma: export

#include "src/trace_processor/tables/jit_tables_fwd.h"  // IWYU pragma: export

namespace perfetto::trace_processor::tables {

struct V8IsolateTable_Id : BaseId {
  V8IsolateTable_Id() = default;
  explicit constexpr V8IsolateTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8IsolateTable_Id& other) const {
    return value == other.value;
  }
};

struct V8JsScriptTable_Id : BaseId {
  V8JsScriptTable_Id() = default;
  explicit constexpr V8JsScriptTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8JsScriptTable_Id& other) const {
    return value == other.value;
  }
};

struct V8WasmScriptTable_Id : BaseId {
  V8WasmScriptTable_Id() = default;
  explicit constexpr V8WasmScriptTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8WasmScriptTable_Id& other) const {
    return value == other.value;
  }
};

struct V8JsFunctionTable_Id : BaseId {
  V8JsFunctionTable_Id() = default;
  explicit constexpr V8JsFunctionTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8JsFunctionTable_Id& other) const {
    return value == other.value;
  }
};

struct V8JsCodeTable_Id : BaseId {
  V8JsCodeTable_Id() = default;
  explicit constexpr V8JsCodeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8JsCodeTable_Id& other) const {
    return value == other.value;
  }
};

struct V8InternalCodeTable_Id : BaseId {
  V8InternalCodeTable_Id() = default;
  explicit constexpr V8InternalCodeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8InternalCodeTable_Id& other) const {
    return value == other.value;
  }
};

struct V8WasmCodeTable_Id : BaseId {
  V8WasmCodeTable_Id() = default;
  explicit constexpr V8WasmCodeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8WasmCodeTable_Id& other) const {
    return value == other.value;
  }
};

struct V8RegexpCodeTable_Id : BaseId {
  V8RegexpCodeTable_Id() = default;
  explicit constexpr V8RegexpCodeTable_Id(uint32_t _value) : BaseId(_value) {}

  bool operator==(const V8RegexpCodeTable_Id& other) const {
    return value == other.value;
  }
};

class V8IsolateTable;
class V8JsScriptTable;
class V8WasmScriptTable;
class V8JsFunctionTable;
class V8JsCodeTable;
class V8InternalCodeTable;
class V8WasmCodeTable;
class V8RegexpCodeTable;

// Tuple of all table types in this header
using V8_TABLES_FWD_TABLES = std::tuple<V8IsolateTable, V8JsScriptTable, V8WasmScriptTable, V8JsFunctionTable, V8JsCodeTable, V8InternalCodeTable, V8WasmCodeTable, V8RegexpCodeTable>;

}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_V8_TABLES_FWD_H_

