#ifndef SRC_TRACE_PROCESSOR_TABLES_MEMORY_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_MEMORY_TABLES_PY_H_

#include <cstdint>
#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

#include "perfetto/base/compiler.h"
#include "perfetto/public/compiler.h"
#include "src/trace_processor/containers/string_pool.h"
#include "src/trace_processor/tables/macros_internal.h"
#include "src/trace_processor/core/dataframe/dataframe.h"
#include "src/trace_processor/core/dataframe/specs.h"
#include "src/trace_processor/core/dataframe/typed_cursor.h"
#include "src/trace_processor/tables/memory_tables_fwd.h"

#include "src/trace_processor/tables/track_tables_py.h"

namespace perfetto::trace_processor::tables {


class MemorySnapshotTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","timestamp","track_id","detail_level"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = MemorySnapshotTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(MemorySnapshotTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const MemorySnapshotTable& table) const {
      return ConstRowReference(&table, value_);
    }

    bool operator==(const RowNumber& other) const {
      return value_ == other.value_;
    }
    bool operator<(const RowNumber& other) const {
      return value_ < other.value_;
    }
   private:
    uint32_t value_;
  };
  struct ColumnIndex {
    static constexpr uint32_t id = 0;
    static constexpr uint32_t timestamp = 1;
    static constexpr uint32_t track_id = 2;
    static constexpr uint32_t detail_level = 3;
  };
  struct RowReference {
   public:
    explicit RowReference(MemorySnapshotTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    MemorySnapshotTable::Id id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::timestamp>(kSpec, row_);
    }
          StringPool::Id detail_level() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::detail_level>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    MemorySnapshotTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const MemorySnapshotTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    MemorySnapshotTable::Id id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::timestamp>(kSpec, row_);
    }
          StringPool::Id detail_level() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::detail_level>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const MemorySnapshotTable* table_;
    uint32_t row_;
  };
  class ConstCursor {
   public:
    explicit ConstCursor(const dataframe::Dataframe& df,
                         std::vector<dataframe::FilterSpec> filters,
                         std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }
    MemorySnapshotTable::Id id() const {
        
        return MemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t timestamp() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::timestamp>(kSpec);
    }
      StringPool::Id detail_level() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::detail_level>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }

   private:
    const dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Cursor {
   public:
    explicit Cursor(dataframe::Dataframe& df,
                    std::vector<dataframe::FilterSpec> filters,
                    std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }

    MemorySnapshotTable::Id id() const {
        
        return MemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t timestamp() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::timestamp>(kSpec);
    }
      StringPool::Id detail_level() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::detail_level>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(MemorySnapshotTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      Iterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      RowReference ToRowReference() const {
        return RowReference(table_, row_);
      }
      MemorySnapshotTable::Id id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::timestamp>(kSpec, row_);
    }
          StringPool::Id detail_level() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::detail_level>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      

    private:
      MemorySnapshotTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const MemorySnapshotTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      ConstIterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      ConstRowReference ToRowReference() const {
        return ConstRowReference(table_, row_);
      }
      MemorySnapshotTable::Id id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::timestamp>(kSpec, row_);
    }
          StringPool::Id detail_level() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::detail_level>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const MemorySnapshotTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _timestamp = {}, TrackTable::Id _track_id = {}, StringPool::Id _detail_level = {}) : timestamp(std::move(_timestamp)), track_id(std::move(_track_id)), detail_level(std::move(_detail_level)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(timestamp, other.timestamp) && std::equal_to<>()(track_id, other.track_id) && std::equal_to<>()(detail_level, other.detail_level);
    }

        int64_t timestamp;
    TrackTable::Id track_id;
    StringPool::Id detail_level;
  };

  explicit MemorySnapshotTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.timestamp, row.track_id.value, std::make_optional(row.detail_level));
    return IdAndRow{Id{row_count}, RowNumber{row_count}, row_count, RowReference(this, row_count)};
  }

  uint32_t row_count() const {
    return dataframe_.row_count();
  }

  uint64_t mutations() const {
    return dataframe_.mutations();
  }

  std::optional<ConstRowReference> FindById(Id id) const {
    return ConstRowReference(this, id.value);
  }
  ConstRowReference operator[](uint32_t row) const {
    return ConstRowReference(this, row);
  }

  std::optional<RowReference> FindById(Id id) {
    return RowReference(this, id.value);
  }
  RowReference operator[](uint32_t row) {
    return RowReference(this, row);
  }

  ConstCursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) const {
    return ConstCursor(dataframe_, std::move(filters), std::move(sorts));
  }
  Cursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) {
    return Cursor(dataframe_, std::move(filters), std::move(sorts));
  }

  Iterator IterateRows() { return Iterator(this); }
  ConstIterator IterateRows() const { return ConstIterator(this); }

  void Finalize() { dataframe_.Finalize(); }

  void Clear() { dataframe_.Clear(); }

  static const char* Name() {
    return "__intrinsic_memory_snapshot";
  }

  dataframe::Dataframe& dataframe() {
    return dataframe_;
  }
  const dataframe::Dataframe& dataframe() const {
    return dataframe_;
  }

 private:
  dataframe::Dataframe dataframe_;
};
static_assert(sizeof(MemorySnapshotTable) == sizeof(dataframe::Dataframe));



class ProcessMemorySnapshotTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","snapshot_id","upid"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ProcessMemorySnapshotTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ProcessMemorySnapshotTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ProcessMemorySnapshotTable& table) const {
      return ConstRowReference(&table, value_);
    }

    bool operator==(const RowNumber& other) const {
      return value_ == other.value_;
    }
    bool operator<(const RowNumber& other) const {
      return value_ < other.value_;
    }
   private:
    uint32_t value_;
  };
  struct ColumnIndex {
    static constexpr uint32_t id = 0;
    static constexpr uint32_t snapshot_id = 1;
    static constexpr uint32_t upid = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(ProcessMemorySnapshotTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ProcessMemorySnapshotTable::Id id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotTable::Id snapshot_id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::snapshot_id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ProcessMemorySnapshotTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ProcessMemorySnapshotTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ProcessMemorySnapshotTable::Id id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotTable::Id snapshot_id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::snapshot_id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ProcessMemorySnapshotTable* table_;
    uint32_t row_;
  };
  class ConstCursor {
   public:
    explicit ConstCursor(const dataframe::Dataframe& df,
                         std::vector<dataframe::FilterSpec> filters,
                         std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }
    ProcessMemorySnapshotTable::Id id() const {
        
        return ProcessMemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      MemorySnapshotTable::Id snapshot_id() const {
        
        return MemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::snapshot_id>(kSpec)};
      }
    uint32_t upid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }

   private:
    const dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Cursor {
   public:
    explicit Cursor(dataframe::Dataframe& df,
                    std::vector<dataframe::FilterSpec> filters,
                    std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }

    ProcessMemorySnapshotTable::Id id() const {
        
        return ProcessMemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      MemorySnapshotTable::Id snapshot_id() const {
        
        return MemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::snapshot_id>(kSpec)};
      }
    uint32_t upid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ProcessMemorySnapshotTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      Iterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      RowReference ToRowReference() const {
        return RowReference(table_, row_);
      }
      ProcessMemorySnapshotTable::Id id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotTable::Id snapshot_id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::snapshot_id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
      

    private:
      ProcessMemorySnapshotTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ProcessMemorySnapshotTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      ConstIterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      ConstRowReference ToRowReference() const {
        return ConstRowReference(table_, row_);
      }
      ProcessMemorySnapshotTable::Id id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotTable::Id snapshot_id() const {
        
        return MemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::snapshot_id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }

    private:
      const ProcessMemorySnapshotTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(MemorySnapshotTable::Id _snapshot_id = {}, uint32_t _upid = {}) : snapshot_id(std::move(_snapshot_id)), upid(std::move(_upid)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(snapshot_id, other.snapshot_id) && std::equal_to<>()(upid, other.upid);
    }

        MemorySnapshotTable::Id snapshot_id;
    uint32_t upid;
  };

  explicit ProcessMemorySnapshotTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.snapshot_id.value, row.upid);
    return IdAndRow{Id{row_count}, RowNumber{row_count}, row_count, RowReference(this, row_count)};
  }

  uint32_t row_count() const {
    return dataframe_.row_count();
  }

  uint64_t mutations() const {
    return dataframe_.mutations();
  }

  std::optional<ConstRowReference> FindById(Id id) const {
    return ConstRowReference(this, id.value);
  }
  ConstRowReference operator[](uint32_t row) const {
    return ConstRowReference(this, row);
  }

  std::optional<RowReference> FindById(Id id) {
    return RowReference(this, id.value);
  }
  RowReference operator[](uint32_t row) {
    return RowReference(this, row);
  }

  ConstCursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) const {
    return ConstCursor(dataframe_, std::move(filters), std::move(sorts));
  }
  Cursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) {
    return Cursor(dataframe_, std::move(filters), std::move(sorts));
  }

  Iterator IterateRows() { return Iterator(this); }
  ConstIterator IterateRows() const { return ConstIterator(this); }

  void Finalize() { dataframe_.Finalize(); }

  void Clear() { dataframe_.Clear(); }

  static const char* Name() {
    return "__intrinsic_process_memory_snapshot";
  }

  dataframe::Dataframe& dataframe() {
    return dataframe_;
  }
  const dataframe::Dataframe& dataframe() const {
    return dataframe_;
  }

 private:
  dataframe::Dataframe dataframe_;
};
static_assert(sizeof(ProcessMemorySnapshotTable) == sizeof(dataframe::Dataframe));



class MemorySnapshotNodeTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","process_snapshot_id","parent_node_id","path","size","effective_size","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = MemorySnapshotNodeTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(MemorySnapshotNodeTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const MemorySnapshotNodeTable& table) const {
      return ConstRowReference(&table, value_);
    }

    bool operator==(const RowNumber& other) const {
      return value_ == other.value_;
    }
    bool operator<(const RowNumber& other) const {
      return value_ < other.value_;
    }
   private:
    uint32_t value_;
  };
  struct ColumnIndex {
    static constexpr uint32_t id = 0;
    static constexpr uint32_t process_snapshot_id = 1;
    static constexpr uint32_t parent_node_id = 2;
    static constexpr uint32_t path = 3;
    static constexpr uint32_t size = 4;
    static constexpr uint32_t effective_size = 5;
    static constexpr uint32_t arg_set_id = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(MemorySnapshotNodeTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    MemorySnapshotNodeTable::Id id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          ProcessMemorySnapshotTable::Id process_snapshot_id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_snapshot_id>(kSpec, row_)};
      }
          StringPool::Id path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t effective_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::effective_size>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    void set_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::size>(kSpec, row_, res);
    }
        void set_effective_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::effective_size>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    MemorySnapshotNodeTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const MemorySnapshotNodeTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    MemorySnapshotNodeTable::Id id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          ProcessMemorySnapshotTable::Id process_snapshot_id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_snapshot_id>(kSpec, row_)};
      }
          StringPool::Id path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t effective_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::effective_size>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const MemorySnapshotNodeTable* table_;
    uint32_t row_;
  };
  class ConstCursor {
   public:
    explicit ConstCursor(const dataframe::Dataframe& df,
                         std::vector<dataframe::FilterSpec> filters,
                         std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }
    MemorySnapshotNodeTable::Id id() const {
        
        return MemorySnapshotNodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      ProcessMemorySnapshotTable::Id process_snapshot_id() const {
        
        return ProcessMemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::process_snapshot_id>(kSpec)};
      }
      StringPool::Id path() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::path>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
    int64_t effective_size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::effective_size>(kSpec);
    }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }

   private:
    const dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Cursor {
   public:
    explicit Cursor(dataframe::Dataframe& df,
                    std::vector<dataframe::FilterSpec> filters,
                    std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }

    MemorySnapshotNodeTable::Id id() const {
        
        return MemorySnapshotNodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      ProcessMemorySnapshotTable::Id process_snapshot_id() const {
        
        return ProcessMemorySnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::process_snapshot_id>(kSpec)};
      }
      StringPool::Id path() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::path>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
    int64_t effective_size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::effective_size>(kSpec);
    }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    void set_size(int64_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::size>(kSpec, res);
    }
    void set_effective_size(int64_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::effective_size>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(MemorySnapshotNodeTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      Iterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      RowReference ToRowReference() const {
        return RowReference(table_, row_);
      }
      MemorySnapshotNodeTable::Id id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          ProcessMemorySnapshotTable::Id process_snapshot_id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_snapshot_id>(kSpec, row_)};
      }
          StringPool::Id path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t effective_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::effective_size>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      void set_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::size>(kSpec, row_, res);
    }
        void set_effective_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::effective_size>(kSpec, row_, res);
    }

    private:
      MemorySnapshotNodeTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const MemorySnapshotNodeTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      ConstIterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      ConstRowReference ToRowReference() const {
        return ConstRowReference(table_, row_);
      }
      MemorySnapshotNodeTable::Id id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          ProcessMemorySnapshotTable::Id process_snapshot_id() const {
        
        return ProcessMemorySnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_snapshot_id>(kSpec, row_)};
      }
          StringPool::Id path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t effective_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::effective_size>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const MemorySnapshotNodeTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(ProcessMemorySnapshotTable::Id _process_snapshot_id = {}, std::optional<MemorySnapshotNodeTable::Id> _parent_node_id = {}, StringPool::Id _path = {}, int64_t _size = {}, int64_t _effective_size = {}, std::optional<uint32_t> _arg_set_id = {}) : process_snapshot_id(std::move(_process_snapshot_id)), parent_node_id(std::move(_parent_node_id)), path(std::move(_path)), size(std::move(_size)), effective_size(std::move(_effective_size)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(process_snapshot_id, other.process_snapshot_id) && std::equal_to<>()(parent_node_id, other.parent_node_id) && std::equal_to<>()(path, other.path) && std::equal_to<>()(size, other.size) && std::equal_to<>()(effective_size, other.effective_size) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        ProcessMemorySnapshotTable::Id process_snapshot_id;
    std::optional<MemorySnapshotNodeTable::Id> parent_node_id;
    StringPool::Id path;
    int64_t size;
    int64_t effective_size;
    std::optional<uint32_t> arg_set_id;
  };

  explicit MemorySnapshotNodeTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.process_snapshot_id.value, row.parent_node_id ? std::make_optional(row.parent_node_id->value) : std::nullopt, std::make_optional(row.path), row.size, row.effective_size, row.arg_set_id);
    return IdAndRow{Id{row_count}, RowNumber{row_count}, row_count, RowReference(this, row_count)};
  }

  uint32_t row_count() const {
    return dataframe_.row_count();
  }

  uint64_t mutations() const {
    return dataframe_.mutations();
  }

  std::optional<ConstRowReference> FindById(Id id) const {
    return ConstRowReference(this, id.value);
  }
  ConstRowReference operator[](uint32_t row) const {
    return ConstRowReference(this, row);
  }

  std::optional<RowReference> FindById(Id id) {
    return RowReference(this, id.value);
  }
  RowReference operator[](uint32_t row) {
    return RowReference(this, row);
  }

  ConstCursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) const {
    return ConstCursor(dataframe_, std::move(filters), std::move(sorts));
  }
  Cursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) {
    return Cursor(dataframe_, std::move(filters), std::move(sorts));
  }

  Iterator IterateRows() { return Iterator(this); }
  ConstIterator IterateRows() const { return ConstIterator(this); }

  void Finalize() { dataframe_.Finalize(); }

  void Clear() { dataframe_.Clear(); }

  static const char* Name() {
    return "__intrinsic_memory_snapshot_node";
  }

  dataframe::Dataframe& dataframe() {
    return dataframe_;
  }
  const dataframe::Dataframe& dataframe() const {
    return dataframe_;
  }

 private:
  dataframe::Dataframe dataframe_;
};
static_assert(sizeof(MemorySnapshotNodeTable) == sizeof(dataframe::Dataframe));



class MemorySnapshotEdgeTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","source_node_id","target_node_id","importance"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = MemorySnapshotEdgeTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(MemorySnapshotEdgeTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const MemorySnapshotEdgeTable& table) const {
      return ConstRowReference(&table, value_);
    }

    bool operator==(const RowNumber& other) const {
      return value_ == other.value_;
    }
    bool operator<(const RowNumber& other) const {
      return value_ < other.value_;
    }
   private:
    uint32_t value_;
  };
  struct ColumnIndex {
    static constexpr uint32_t id = 0;
    static constexpr uint32_t source_node_id = 1;
    static constexpr uint32_t target_node_id = 2;
    static constexpr uint32_t importance = 3;
  };
  struct RowReference {
   public:
    explicit RowReference(MemorySnapshotEdgeTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    MemorySnapshotEdgeTable::Id id() const {
        
        return MemorySnapshotEdgeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id source_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_node_id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id target_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::target_node_id>(kSpec, row_)};
      }
        uint32_t importance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::importance>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    MemorySnapshotEdgeTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const MemorySnapshotEdgeTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    MemorySnapshotEdgeTable::Id id() const {
        
        return MemorySnapshotEdgeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id source_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_node_id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id target_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::target_node_id>(kSpec, row_)};
      }
        uint32_t importance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::importance>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const MemorySnapshotEdgeTable* table_;
    uint32_t row_;
  };
  class ConstCursor {
   public:
    explicit ConstCursor(const dataframe::Dataframe& df,
                         std::vector<dataframe::FilterSpec> filters,
                         std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }
    MemorySnapshotEdgeTable::Id id() const {
        
        return MemorySnapshotEdgeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      MemorySnapshotNodeTable::Id source_node_id() const {
        
        return MemorySnapshotNodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::source_node_id>(kSpec)};
      }
      MemorySnapshotNodeTable::Id target_node_id() const {
        
        return MemorySnapshotNodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::target_node_id>(kSpec)};
      }
    uint32_t importance() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::importance>(kSpec);
    }

   private:
    const dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Cursor {
   public:
    explicit Cursor(dataframe::Dataframe& df,
                    std::vector<dataframe::FilterSpec> filters,
                    std::vector<dataframe::SortSpec> sorts)
      : dataframe_(&df), cursor_(&df, std::move(filters), std::move(sorts)) {
      base::ignore_result(dataframe_);
    }

    PERFETTO_ALWAYS_INLINE void Execute() { cursor_.ExecuteUnchecked(); }
    PERFETTO_ALWAYS_INLINE bool Eof() const { return cursor_.Eof(); }
    PERFETTO_ALWAYS_INLINE void Next() { cursor_.Next(); }
    template <typename C>
    PERFETTO_ALWAYS_INLINE void SetFilterValueUnchecked(uint32_t index, C value) {
      cursor_.SetFilterValueUnchecked(index, std::move(value));
    }
    PERFETTO_ALWAYS_INLINE void SetFilterValueListUnchecked(
        uint32_t index,
        const dataframe::TypedCursor::FilterValue* values,
        uint32_t count) {
      cursor_.SetFilterValueListUnchecked(index, values, count);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{cursor_.RowIndex()};
    }
    void Reset() { cursor_.Reset(); }

    MemorySnapshotEdgeTable::Id id() const {
        
        return MemorySnapshotEdgeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      MemorySnapshotNodeTable::Id source_node_id() const {
        
        return MemorySnapshotNodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::source_node_id>(kSpec)};
      }
      MemorySnapshotNodeTable::Id target_node_id() const {
        
        return MemorySnapshotNodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::target_node_id>(kSpec)};
      }
    uint32_t importance() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::importance>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(MemorySnapshotEdgeTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      Iterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      RowReference ToRowReference() const {
        return RowReference(table_, row_);
      }
      MemorySnapshotEdgeTable::Id id() const {
        
        return MemorySnapshotEdgeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id source_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_node_id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id target_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::target_node_id>(kSpec, row_)};
      }
        uint32_t importance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::importance>(kSpec, row_);
    }
      

    private:
      MemorySnapshotEdgeTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const MemorySnapshotEdgeTable* table) : table_(table) {
        base::ignore_result(table_);
      }
      explicit operator bool() const { return row_ < table_->row_count(); }
      ConstIterator& operator++() {
        ++row_;
        return *this;
      }
      RowNumber row_number() const {
        return RowNumber{row_};
      }
      ConstRowReference ToRowReference() const {
        return ConstRowReference(table_, row_);
      }
      MemorySnapshotEdgeTable::Id id() const {
        
        return MemorySnapshotEdgeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id source_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_node_id>(kSpec, row_)};
      }
          MemorySnapshotNodeTable::Id target_node_id() const {
        
        return MemorySnapshotNodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::target_node_id>(kSpec, row_)};
      }
        uint32_t importance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::importance>(kSpec, row_);
    }

    private:
      const MemorySnapshotEdgeTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(MemorySnapshotNodeTable::Id _source_node_id = {}, MemorySnapshotNodeTable::Id _target_node_id = {}, uint32_t _importance = {}) : source_node_id(std::move(_source_node_id)), target_node_id(std::move(_target_node_id)), importance(std::move(_importance)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(source_node_id, other.source_node_id) && std::equal_to<>()(target_node_id, other.target_node_id) && std::equal_to<>()(importance, other.importance);
    }

        MemorySnapshotNodeTable::Id source_node_id;
    MemorySnapshotNodeTable::Id target_node_id;
    uint32_t importance;
  };

  explicit MemorySnapshotEdgeTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.source_node_id.value, row.target_node_id.value, row.importance);
    return IdAndRow{Id{row_count}, RowNumber{row_count}, row_count, RowReference(this, row_count)};
  }

  uint32_t row_count() const {
    return dataframe_.row_count();
  }

  uint64_t mutations() const {
    return dataframe_.mutations();
  }

  std::optional<ConstRowReference> FindById(Id id) const {
    return ConstRowReference(this, id.value);
  }
  ConstRowReference operator[](uint32_t row) const {
    return ConstRowReference(this, row);
  }

  std::optional<RowReference> FindById(Id id) {
    return RowReference(this, id.value);
  }
  RowReference operator[](uint32_t row) {
    return RowReference(this, row);
  }

  ConstCursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) const {
    return ConstCursor(dataframe_, std::move(filters), std::move(sorts));
  }
  Cursor CreateCursor(
      std::vector<dataframe::FilterSpec> filters = {},
      std::vector<dataframe::SortSpec> sorts = {}) {
    return Cursor(dataframe_, std::move(filters), std::move(sorts));
  }

  Iterator IterateRows() { return Iterator(this); }
  ConstIterator IterateRows() const { return ConstIterator(this); }

  void Finalize() { dataframe_.Finalize(); }

  void Clear() { dataframe_.Clear(); }

  static const char* Name() {
    return "__intrinsic_memory_snapshot_edge";
  }

  dataframe::Dataframe& dataframe() {
    return dataframe_;
  }
  const dataframe::Dataframe& dataframe() const {
    return dataframe_;
  }

 private:
  dataframe::Dataframe dataframe_;
};
static_assert(sizeof(MemorySnapshotEdgeTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_MEMORY_TABLES_PY_H_

