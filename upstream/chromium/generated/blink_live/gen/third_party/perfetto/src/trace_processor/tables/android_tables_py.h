#ifndef SRC_TRACE_PROCESSOR_TABLES_ANDROID_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_ANDROID_TABLES_PY_H_

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
#include "src/trace_processor/tables/android_tables_fwd.h"

#include "src/trace_processor/tables/metadata_tables_py.h"
#include "src/trace_processor/tables/track_tables_py.h"

namespace perfetto::trace_processor::tables {


class AndroidAflagsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","package","name","flag_namespace","container","value","staged_value","permission","value_picked_from","storage_backend","type"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidAflagsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidAflagsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidAflagsTable& table) const {
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
    static constexpr uint32_t ts = 1;
    static constexpr uint32_t package = 2;
    static constexpr uint32_t name = 3;
    static constexpr uint32_t flag_namespace = 4;
    static constexpr uint32_t container = 5;
    static constexpr uint32_t value = 6;
    static constexpr uint32_t staged_value = 7;
    static constexpr uint32_t permission = 8;
    static constexpr uint32_t value_picked_from = 9;
    static constexpr uint32_t storage_backend = 10;
    static constexpr uint32_t type = 11;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidAflagsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidAflagsTable::Id id() const {
        
        return AndroidAflagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidAflagsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidAflagsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidAflagsTable::Id id() const {
        
        return AndroidAflagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidAflagsTable* table_;
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
    AndroidAflagsTable::Id id() const {
        
        return AndroidAflagsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    AndroidAflagsTable::Id id() const {
        
        return AndroidAflagsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidAflagsTable* table) : table_(table) {
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
      AndroidAflagsTable::Id id() const {
        
        return AndroidAflagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      AndroidAflagsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidAflagsTable* table) : table_(table) {
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
      AndroidAflagsTable::Id id() const {
        
        return AndroidAflagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const AndroidAflagsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, StringPool::Id _package = {}, StringPool::Id _name = {}, StringPool::Id _flag_namespace = {}, StringPool::Id _container = {}, StringPool::Id _value = {}, std::optional<StringPool::Id> _staged_value = {}, StringPool::Id _permission = {}, StringPool::Id _value_picked_from = {}, StringPool::Id _storage_backend = {}, StringPool::Id _type = {}) : ts(std::move(_ts)), package(std::move(_package)), name(std::move(_name)), flag_namespace(std::move(_flag_namespace)), container(std::move(_container)), value(std::move(_value)), staged_value(std::move(_staged_value)), permission(std::move(_permission)), value_picked_from(std::move(_value_picked_from)), storage_backend(std::move(_storage_backend)), type(std::move(_type)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(package, other.package) && std::equal_to<>()(name, other.name) && std::equal_to<>()(flag_namespace, other.flag_namespace) && std::equal_to<>()(container, other.container) && std::equal_to<>()(value, other.value) && std::equal_to<>()(staged_value, other.staged_value) && std::equal_to<>()(permission, other.permission) && std::equal_to<>()(value_picked_from, other.value_picked_from) && std::equal_to<>()(storage_backend, other.storage_backend) && std::equal_to<>()(type, other.type);
    }

        int64_t ts;
    StringPool::Id package;
    StringPool::Id name;
    StringPool::Id flag_namespace;
    StringPool::Id container;
    StringPool::Id value;
    std::optional<StringPool::Id> staged_value;
    StringPool::Id permission;
    StringPool::Id value_picked_from;
    StringPool::Id storage_backend;
    StringPool::Id type;
  };

  explicit AndroidAflagsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, std::make_optional(row.package), std::make_optional(row.name), std::make_optional(row.flag_namespace), std::make_optional(row.container), std::make_optional(row.value), row.staged_value, std::make_optional(row.permission), std::make_optional(row.value_picked_from), std::make_optional(row.storage_backend), std::make_optional(row.type));
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
    return "__intrinsic_android_aflags";
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
static_assert(sizeof(AndroidAflagsTable) == sizeof(dataframe::Dataframe));



class AndroidCpuPerUidTrackTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","track_id","uid","cluster","total_cpu_millis"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidCpuPerUidTrackTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidCpuPerUidTrackTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidCpuPerUidTrackTable& table) const {
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
    static constexpr uint32_t track_id = 1;
    static constexpr uint32_t uid = 2;
    static constexpr uint32_t cluster = 3;
    static constexpr uint32_t total_cpu_millis = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidCpuPerUidTrackTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidCpuPerUidTrackTable::Id id() const {
        
        return AndroidCpuPerUidTrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          TrackTable::Id track_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
        int64_t uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int64_t cluster() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster>(kSpec, row_);
    }
        int64_t total_cpu_millis() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::total_cpu_millis>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidCpuPerUidTrackTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidCpuPerUidTrackTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidCpuPerUidTrackTable::Id id() const {
        
        return AndroidCpuPerUidTrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          TrackTable::Id track_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
        int64_t uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int64_t cluster() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster>(kSpec, row_);
    }
        int64_t total_cpu_millis() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::total_cpu_millis>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidCpuPerUidTrackTable* table_;
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
    AndroidCpuPerUidTrackTable::Id id() const {
        
        return AndroidCpuPerUidTrackTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      TrackTable::Id track_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return TrackTable::Id{cursor_.GetCellUnchecked<ColumnIndex::track_id>(kSpec)};
      }
    int64_t uid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::uid>(kSpec);
    }
    int64_t cluster() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cluster>(kSpec);
    }
    int64_t total_cpu_millis() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::total_cpu_millis>(kSpec);
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

    AndroidCpuPerUidTrackTable::Id id() const {
        
        return AndroidCpuPerUidTrackTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      TrackTable::Id track_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return TrackTable::Id{cursor_.GetCellUnchecked<ColumnIndex::track_id>(kSpec)};
      }
    int64_t uid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::uid>(kSpec);
    }
    int64_t cluster() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cluster>(kSpec);
    }
    int64_t total_cpu_millis() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::total_cpu_millis>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidCpuPerUidTrackTable* table) : table_(table) {
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
      AndroidCpuPerUidTrackTable::Id id() const {
        
        return AndroidCpuPerUidTrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          TrackTable::Id track_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
        int64_t uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int64_t cluster() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster>(kSpec, row_);
    }
        int64_t total_cpu_millis() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::total_cpu_millis>(kSpec, row_);
    }
      

    private:
      AndroidCpuPerUidTrackTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidCpuPerUidTrackTable* table) : table_(table) {
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
      AndroidCpuPerUidTrackTable::Id id() const {
        
        return AndroidCpuPerUidTrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          TrackTable::Id track_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
        int64_t uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int64_t cluster() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster>(kSpec, row_);
    }
        int64_t total_cpu_millis() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::total_cpu_millis>(kSpec, row_);
    }

    private:
      const AndroidCpuPerUidTrackTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(TrackTable::Id _track_id = {}, int64_t _uid = {}, int64_t _cluster = {}, int64_t _total_cpu_millis = {}) : track_id(std::move(_track_id)), uid(std::move(_uid)), cluster(std::move(_cluster)), total_cpu_millis(std::move(_total_cpu_millis)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(track_id, other.track_id) && std::equal_to<>()(uid, other.uid) && std::equal_to<>()(cluster, other.cluster) && std::equal_to<>()(total_cpu_millis, other.total_cpu_millis);
    }

        TrackTable::Id track_id;
    int64_t uid;
    int64_t cluster;
    int64_t total_cpu_millis;
  };

  explicit AndroidCpuPerUidTrackTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.track_id.value, row.uid, row.cluster, row.total_cpu_millis);
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
    return "__intrinsic_android_cpu_per_uid_track";
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
static_assert(sizeof(AndroidCpuPerUidTrackTable) == sizeof(dataframe::Dataframe));



class AndroidDumpstateTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","section","service","line"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidDumpstateTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidDumpstateTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidDumpstateTable& table) const {
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
    static constexpr uint32_t section = 1;
    static constexpr uint32_t service = 2;
    static constexpr uint32_t line = 3;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidDumpstateTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidDumpstateTable::Id id() const {
        
        return AndroidDumpstateTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidDumpstateTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidDumpstateTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidDumpstateTable::Id id() const {
        
        return AndroidDumpstateTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidDumpstateTable* table_;
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
    AndroidDumpstateTable::Id id() const {
        
        return AndroidDumpstateTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    AndroidDumpstateTable::Id id() const {
        
        return AndroidDumpstateTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidDumpstateTable* table) : table_(table) {
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
      AndroidDumpstateTable::Id id() const {
        
        return AndroidDumpstateTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      AndroidDumpstateTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidDumpstateTable* table) : table_(table) {
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
      AndroidDumpstateTable::Id id() const {
        
        return AndroidDumpstateTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const AndroidDumpstateTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<StringPool::Id> _section = {}, std::optional<StringPool::Id> _service = {}, StringPool::Id _line = {}) : section(std::move(_section)), service(std::move(_service)), line(std::move(_line)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(section, other.section) && std::equal_to<>()(service, other.service) && std::equal_to<>()(line, other.line);
    }

        std::optional<StringPool::Id> section;
    std::optional<StringPool::Id> service;
    StringPool::Id line;
  };

  explicit AndroidDumpstateTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.section, row.service, std::make_optional(row.line));
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
    return "__intrinsic_android_dumpstate";
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
static_assert(sizeof(AndroidDumpstateTable) == sizeof(dataframe::Dataframe));



class AndroidGameInterventionListTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","package_name","uid","current_mode","standard_mode_supported","standard_mode_downscale","standard_mode_use_angle","standard_mode_fps","perf_mode_supported","perf_mode_downscale","perf_mode_use_angle","perf_mode_fps","battery_mode_supported","battery_mode_downscale","battery_mode_use_angle","battery_mode_fps"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidGameInterventionListTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidGameInterventionListTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidGameInterventionListTable& table) const {
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
    static constexpr uint32_t package_name = 1;
    static constexpr uint32_t uid = 2;
    static constexpr uint32_t current_mode = 3;
    static constexpr uint32_t standard_mode_supported = 4;
    static constexpr uint32_t standard_mode_downscale = 5;
    static constexpr uint32_t standard_mode_use_angle = 6;
    static constexpr uint32_t standard_mode_fps = 7;
    static constexpr uint32_t perf_mode_supported = 8;
    static constexpr uint32_t perf_mode_downscale = 9;
    static constexpr uint32_t perf_mode_use_angle = 10;
    static constexpr uint32_t perf_mode_fps = 11;
    static constexpr uint32_t battery_mode_supported = 12;
    static constexpr uint32_t battery_mode_downscale = 13;
    static constexpr uint32_t battery_mode_use_angle = 14;
    static constexpr uint32_t battery_mode_fps = 15;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidGameInterventionListTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidGameInterventionListTable::Id id() const {
        
        return AndroidGameInterventionListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidGameInterventionListTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidGameInterventionListTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidGameInterventionListTable::Id id() const {
        
        return AndroidGameInterventionListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidGameInterventionListTable* table_;
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
    AndroidGameInterventionListTable::Id id() const {
        
        return AndroidGameInterventionListTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    AndroidGameInterventionListTable::Id id() const {
        
        return AndroidGameInterventionListTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidGameInterventionListTable* table) : table_(table) {
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
      AndroidGameInterventionListTable::Id id() const {
        
        return AndroidGameInterventionListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      AndroidGameInterventionListTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidGameInterventionListTable* table) : table_(table) {
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
      AndroidGameInterventionListTable::Id id() const {
        
        return AndroidGameInterventionListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const AndroidGameInterventionListTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _package_name = {}, int64_t _uid = {}, int32_t _current_mode = {}, int32_t _standard_mode_supported = {}, std::optional<double> _standard_mode_downscale = {}, std::optional<int32_t> _standard_mode_use_angle = {}, std::optional<double> _standard_mode_fps = {}, int32_t _perf_mode_supported = {}, std::optional<double> _perf_mode_downscale = {}, std::optional<int32_t> _perf_mode_use_angle = {}, std::optional<double> _perf_mode_fps = {}, int32_t _battery_mode_supported = {}, std::optional<double> _battery_mode_downscale = {}, std::optional<int32_t> _battery_mode_use_angle = {}, std::optional<double> _battery_mode_fps = {}) : package_name(std::move(_package_name)), uid(std::move(_uid)), current_mode(std::move(_current_mode)), standard_mode_supported(std::move(_standard_mode_supported)), standard_mode_downscale(std::move(_standard_mode_downscale)), standard_mode_use_angle(std::move(_standard_mode_use_angle)), standard_mode_fps(std::move(_standard_mode_fps)), perf_mode_supported(std::move(_perf_mode_supported)), perf_mode_downscale(std::move(_perf_mode_downscale)), perf_mode_use_angle(std::move(_perf_mode_use_angle)), perf_mode_fps(std::move(_perf_mode_fps)), battery_mode_supported(std::move(_battery_mode_supported)), battery_mode_downscale(std::move(_battery_mode_downscale)), battery_mode_use_angle(std::move(_battery_mode_use_angle)), battery_mode_fps(std::move(_battery_mode_fps)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(package_name, other.package_name) && std::equal_to<>()(uid, other.uid) && std::equal_to<>()(current_mode, other.current_mode) && std::equal_to<>()(standard_mode_supported, other.standard_mode_supported) && std::equal_to<>()(standard_mode_downscale, other.standard_mode_downscale) && std::equal_to<>()(standard_mode_use_angle, other.standard_mode_use_angle) && std::equal_to<>()(standard_mode_fps, other.standard_mode_fps) && std::equal_to<>()(perf_mode_supported, other.perf_mode_supported) && std::equal_to<>()(perf_mode_downscale, other.perf_mode_downscale) && std::equal_to<>()(perf_mode_use_angle, other.perf_mode_use_angle) && std::equal_to<>()(perf_mode_fps, other.perf_mode_fps) && std::equal_to<>()(battery_mode_supported, other.battery_mode_supported) && std::equal_to<>()(battery_mode_downscale, other.battery_mode_downscale) && std::equal_to<>()(battery_mode_use_angle, other.battery_mode_use_angle) && std::equal_to<>()(battery_mode_fps, other.battery_mode_fps);
    }

        StringPool::Id package_name;
    int64_t uid;
    int32_t current_mode;
    int32_t standard_mode_supported;
    std::optional<double> standard_mode_downscale;
    std::optional<int32_t> standard_mode_use_angle;
    std::optional<double> standard_mode_fps;
    int32_t perf_mode_supported;
    std::optional<double> perf_mode_downscale;
    std::optional<int32_t> perf_mode_use_angle;
    std::optional<double> perf_mode_fps;
    int32_t battery_mode_supported;
    std::optional<double> battery_mode_downscale;
    std::optional<int32_t> battery_mode_use_angle;
    std::optional<double> battery_mode_fps;
  };

  explicit AndroidGameInterventionListTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.package_name), row.uid, row.current_mode, row.standard_mode_supported, row.standard_mode_downscale, row.standard_mode_use_angle, row.standard_mode_fps, row.perf_mode_supported, row.perf_mode_downscale, row.perf_mode_use_angle, row.perf_mode_fps, row.battery_mode_supported, row.battery_mode_downscale, row.battery_mode_use_angle, row.battery_mode_fps);
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
    return "__intrinsic_android_game_intervention_list";
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
static_assert(sizeof(AndroidGameInterventionListTable) == sizeof(dataframe::Dataframe));



class AndroidInputEventDispatchTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","event_id","arg_set_id","vsync_id","window_id","base64_proto_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidInputEventDispatchTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidInputEventDispatchTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidInputEventDispatchTable& table) const {
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
    static constexpr uint32_t event_id = 1;
    static constexpr uint32_t arg_set_id = 2;
    static constexpr uint32_t vsync_id = 3;
    static constexpr uint32_t window_id = 4;
    static constexpr uint32_t base64_proto_id = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidInputEventDispatchTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidInputEventDispatchTable::Id id() const {
        
        return AndroidInputEventDispatchTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_base64_proto_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidInputEventDispatchTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidInputEventDispatchTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidInputEventDispatchTable::Id id() const {
        
        return AndroidInputEventDispatchTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidInputEventDispatchTable* table_;
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
    AndroidInputEventDispatchTable::Id id() const {
        
        return AndroidInputEventDispatchTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<uint32_t> base64_proto_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec);
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

    AndroidInputEventDispatchTable::Id id() const {
        
        return AndroidInputEventDispatchTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<uint32_t> base64_proto_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }
    void set_base64_proto_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidInputEventDispatchTable* table) : table_(table) {
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
      AndroidInputEventDispatchTable::Id id() const {
        
        return AndroidInputEventDispatchTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
      void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_base64_proto_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_, res);
    }

    private:
      AndroidInputEventDispatchTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidInputEventDispatchTable* table) : table_(table) {
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
      AndroidInputEventDispatchTable::Id id() const {
        
        return AndroidInputEventDispatchTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }

    private:
      const AndroidInputEventDispatchTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _event_id = {}, std::optional<uint32_t> _arg_set_id = {}, int64_t _vsync_id = {}, int32_t _window_id = {}, std::optional<uint32_t> _base64_proto_id = {}) : event_id(std::move(_event_id)), arg_set_id(std::move(_arg_set_id)), vsync_id(std::move(_vsync_id)), window_id(std::move(_window_id)), base64_proto_id(std::move(_base64_proto_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(event_id, other.event_id) && std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(vsync_id, other.vsync_id) && std::equal_to<>()(window_id, other.window_id) && std::equal_to<>()(base64_proto_id, other.base64_proto_id);
    }

        uint32_t event_id;
    std::optional<uint32_t> arg_set_id;
    int64_t vsync_id;
    int32_t window_id;
    std::optional<uint32_t> base64_proto_id;
  };

  explicit AndroidInputEventDispatchTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.event_id, row.arg_set_id, row.vsync_id, row.window_id, row.base64_proto_id);
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
    return "__intrinsic_android_input_event_dispatch";
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
static_assert(sizeof(AndroidInputEventDispatchTable) == sizeof(dataframe::Dataframe));



class AndroidKeyEventsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","event_id","ts","arg_set_id","base64_proto_id","source","action","device_id","display_id","key_code"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidKeyEventsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidKeyEventsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidKeyEventsTable& table) const {
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
    static constexpr uint32_t event_id = 1;
    static constexpr uint32_t ts = 2;
    static constexpr uint32_t arg_set_id = 3;
    static constexpr uint32_t base64_proto_id = 4;
    static constexpr uint32_t source = 5;
    static constexpr uint32_t action = 6;
    static constexpr uint32_t device_id = 7;
    static constexpr uint32_t display_id = 8;
    static constexpr uint32_t key_code = 9;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidKeyEventsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidKeyEventsTable::Id id() const {
        
        return AndroidKeyEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_base64_proto_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidKeyEventsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidKeyEventsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidKeyEventsTable::Id id() const {
        
        return AndroidKeyEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidKeyEventsTable* table_;
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
    AndroidKeyEventsTable::Id id() const {
        
        return AndroidKeyEventsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<uint32_t> base64_proto_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec);
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

    AndroidKeyEventsTable::Id id() const {
        
        return AndroidKeyEventsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<uint32_t> base64_proto_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }
    void set_base64_proto_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidKeyEventsTable* table) : table_(table) {
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
      AndroidKeyEventsTable::Id id() const {
        
        return AndroidKeyEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
      void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_base64_proto_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_, res);
    }

    private:
      AndroidKeyEventsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidKeyEventsTable* table) : table_(table) {
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
      AndroidKeyEventsTable::Id id() const {
        
        return AndroidKeyEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }

    private:
      const AndroidKeyEventsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _event_id = {}, int64_t _ts = {}, std::optional<uint32_t> _arg_set_id = {}, std::optional<uint32_t> _base64_proto_id = {}, std::optional<uint32_t> _source = {}, std::optional<int64_t> _action = {}, std::optional<int64_t> _device_id = {}, std::optional<int64_t> _display_id = {}, std::optional<int64_t> _key_code = {}) : event_id(std::move(_event_id)), ts(std::move(_ts)), arg_set_id(std::move(_arg_set_id)), base64_proto_id(std::move(_base64_proto_id)), source(std::move(_source)), action(std::move(_action)), device_id(std::move(_device_id)), display_id(std::move(_display_id)), key_code(std::move(_key_code)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(event_id, other.event_id) && std::equal_to<>()(ts, other.ts) && std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(base64_proto_id, other.base64_proto_id) && std::equal_to<>()(source, other.source) && std::equal_to<>()(action, other.action) && std::equal_to<>()(device_id, other.device_id) && std::equal_to<>()(display_id, other.display_id) && std::equal_to<>()(key_code, other.key_code);
    }

        uint32_t event_id;
    int64_t ts;
    std::optional<uint32_t> arg_set_id;
    std::optional<uint32_t> base64_proto_id;
    std::optional<uint32_t> source;
    std::optional<int64_t> action;
    std::optional<int64_t> device_id;
    std::optional<int64_t> display_id;
    std::optional<int64_t> key_code;
  };

  explicit AndroidKeyEventsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.event_id, row.ts, row.arg_set_id, row.base64_proto_id, row.source, row.action, row.device_id, row.display_id, row.key_code);
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
    return "__intrinsic_android_key_events";
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
static_assert(sizeof(AndroidKeyEventsTable) == sizeof(dataframe::Dataframe));



class AndroidLogTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","utid","prio","tag","msg"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidLogTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidLogTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidLogTable& table) const {
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
    static constexpr uint32_t ts = 1;
    static constexpr uint32_t utid = 2;
    static constexpr uint32_t prio = 3;
    static constexpr uint32_t tag = 4;
    static constexpr uint32_t msg = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidLogTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidLogTable::Id id() const {
        
        return AndroidLogTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          uint32_t utid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t prio() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::prio>(kSpec, row_);
    }
          std::optional<StringPool::Id> tag() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tag>(kSpec, row_);
      }
          StringPool::Id msg() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::msg>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidLogTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidLogTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidLogTable::Id id() const {
        
        return AndroidLogTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          uint32_t utid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t prio() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::prio>(kSpec, row_);
    }
          std::optional<StringPool::Id> tag() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tag>(kSpec, row_);
      }
          StringPool::Id msg() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::msg>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidLogTable* table_;
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
    AndroidLogTable::Id id() const {
        
        return AndroidLogTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      uint32_t utid() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec)};
      }
    uint32_t prio() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::prio>(kSpec);
    }
      std::optional<StringPool::Id> tag() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::tag>(kSpec);
      }
      StringPool::Id msg() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::msg>(kSpec);
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

    AndroidLogTable::Id id() const {
        
        return AndroidLogTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      uint32_t utid() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec)};
      }
    uint32_t prio() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::prio>(kSpec);
    }
      std::optional<StringPool::Id> tag() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::tag>(kSpec);
      }
      StringPool::Id msg() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::msg>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidLogTable* table) : table_(table) {
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
      AndroidLogTable::Id id() const {
        
        return AndroidLogTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          uint32_t utid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t prio() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::prio>(kSpec, row_);
    }
          std::optional<StringPool::Id> tag() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tag>(kSpec, row_);
      }
          StringPool::Id msg() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::msg>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      

    private:
      AndroidLogTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidLogTable* table) : table_(table) {
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
      AndroidLogTable::Id id() const {
        
        return AndroidLogTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          uint32_t utid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t prio() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::prio>(kSpec, row_);
    }
          std::optional<StringPool::Id> tag() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tag>(kSpec, row_);
      }
          StringPool::Id msg() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::msg>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const AndroidLogTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, uint32_t _utid = {}, uint32_t _prio = {}, std::optional<StringPool::Id> _tag = {}, StringPool::Id _msg = {}) : ts(std::move(_ts)), utid(std::move(_utid)), prio(std::move(_prio)), tag(std::move(_tag)), msg(std::move(_msg)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(prio, other.prio) && std::equal_to<>()(tag, other.tag) && std::equal_to<>()(msg, other.msg);
    }

        int64_t ts;
    uint32_t utid;
    uint32_t prio;
    std::optional<StringPool::Id> tag;
    StringPool::Id msg;
  };

  explicit AndroidLogTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.utid, row.prio, row.tag, std::make_optional(row.msg));
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
    return "__intrinsic_android_logs";
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
static_assert(sizeof(AndroidLogTable) == sizeof(dataframe::Dataframe));



class AndroidMotionEventsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","event_id","ts","arg_set_id","base64_proto_id","source","action","device_id","display_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidMotionEventsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidMotionEventsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidMotionEventsTable& table) const {
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
    static constexpr uint32_t event_id = 1;
    static constexpr uint32_t ts = 2;
    static constexpr uint32_t arg_set_id = 3;
    static constexpr uint32_t base64_proto_id = 4;
    static constexpr uint32_t source = 5;
    static constexpr uint32_t action = 6;
    static constexpr uint32_t device_id = 7;
    static constexpr uint32_t display_id = 8;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidMotionEventsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidMotionEventsTable::Id id() const {
        
        return AndroidMotionEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_base64_proto_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidMotionEventsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidMotionEventsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidMotionEventsTable::Id id() const {
        
        return AndroidMotionEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidMotionEventsTable* table_;
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
    AndroidMotionEventsTable::Id id() const {
        
        return AndroidMotionEventsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<uint32_t> base64_proto_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec);
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

    AndroidMotionEventsTable::Id id() const {
        
        return AndroidMotionEventsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<uint32_t> base64_proto_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }
    void set_base64_proto_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidMotionEventsTable* table) : table_(table) {
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
      AndroidMotionEventsTable::Id id() const {
        
        return AndroidMotionEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }
      void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_base64_proto_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_, res);
    }

    private:
      AndroidMotionEventsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidMotionEventsTable* table) : table_(table) {
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
      AndroidMotionEventsTable::Id id() const {
        
        return AndroidMotionEventsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<uint32_t> base64_proto_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::base64_proto_id>(kSpec, row_);
    }

    private:
      const AndroidMotionEventsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _event_id = {}, int64_t _ts = {}, std::optional<uint32_t> _arg_set_id = {}, std::optional<uint32_t> _base64_proto_id = {}, std::optional<uint32_t> _source = {}, std::optional<int64_t> _action = {}, std::optional<int64_t> _device_id = {}, std::optional<int64_t> _display_id = {}) : event_id(std::move(_event_id)), ts(std::move(_ts)), arg_set_id(std::move(_arg_set_id)), base64_proto_id(std::move(_base64_proto_id)), source(std::move(_source)), action(std::move(_action)), device_id(std::move(_device_id)), display_id(std::move(_display_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(event_id, other.event_id) && std::equal_to<>()(ts, other.ts) && std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(base64_proto_id, other.base64_proto_id) && std::equal_to<>()(source, other.source) && std::equal_to<>()(action, other.action) && std::equal_to<>()(device_id, other.device_id) && std::equal_to<>()(display_id, other.display_id);
    }

        uint32_t event_id;
    int64_t ts;
    std::optional<uint32_t> arg_set_id;
    std::optional<uint32_t> base64_proto_id;
    std::optional<uint32_t> source;
    std::optional<int64_t> action;
    std::optional<int64_t> device_id;
    std::optional<int64_t> display_id;
  };

  explicit AndroidMotionEventsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.event_id, row.ts, row.arg_set_id, row.base64_proto_id, row.source, row.action, row.device_id, row.display_id);
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
    return "__intrinsic_android_motion_events";
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
static_assert(sizeof(AndroidMotionEventsTable) == sizeof(dataframe::Dataframe));



class AndroidUserListTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","type","android_user_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidUserListTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidUserListTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidUserListTable& table) const {
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
    static constexpr uint32_t type = 1;
    static constexpr uint32_t android_user_id = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidUserListTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AndroidUserListTable::Id id() const {
        
        return AndroidUserListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    void set_type(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::type>(kSpec, row_, std::make_optional(res));
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidUserListTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidUserListTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AndroidUserListTable::Id id() const {
        
        return AndroidUserListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidUserListTable* table_;
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
    AndroidUserListTable::Id id() const {
        
        return AndroidUserListTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id type() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::type>(kSpec);
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

    AndroidUserListTable::Id id() const {
        
        return AndroidUserListTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id type() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::type>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    void set_type(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::type>(kSpec, std::make_optional(res));
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidUserListTable* table) : table_(table) {
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
      AndroidUserListTable::Id id() const {
        
        return AndroidUserListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      void set_type(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::type>(kSpec, row_, std::make_optional(res));
    }

    private:
      AndroidUserListTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidUserListTable* table) : table_(table) {
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
      AndroidUserListTable::Id id() const {
        
        return AndroidUserListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const AndroidUserListTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _type = {}, int64_t _android_user_id = {}) : type(std::move(_type)), android_user_id(std::move(_android_user_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(type, other.type) && std::equal_to<>()(android_user_id, other.android_user_id);
    }

        StringPool::Id type;
    int64_t android_user_id;
  };

  explicit AndroidUserListTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.type), row.android_user_id);
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
    return "__intrinsic_android_user_list";
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
static_assert(sizeof(AndroidUserListTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_ANDROID_TABLES_PY_H_

