#ifndef SRC_TRACE_PROCESSOR_TABLES_JIT_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_JIT_TABLES_PY_H_

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
#include "src/trace_processor/tables/jit_tables_fwd.h"

#include "src/trace_processor/tables/profiler_tables_py.h"

namespace perfetto::trace_processor::tables {


class JitCodeTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","create_ts","estimated_delete_ts","utid","start_address","size","function_name","native_code_base64"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = JitCodeTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(JitCodeTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const JitCodeTable& table) const {
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
    static constexpr uint32_t create_ts = 1;
    static constexpr uint32_t estimated_delete_ts = 2;
    static constexpr uint32_t utid = 3;
    static constexpr uint32_t start_address = 4;
    static constexpr uint32_t size = 5;
    static constexpr uint32_t function_name = 6;
    static constexpr uint32_t native_code_base64 = 7;
  };
  struct RowReference {
   public:
    explicit RowReference(JitCodeTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    JitCodeTable::Id id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t create_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::create_ts>(kSpec, row_);
    }
        std::optional<int64_t> estimated_delete_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, row_);
    }
        uint32_t utid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int64_t start_address() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id function_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::function_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    void set_estimated_delete_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    JitCodeTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const JitCodeTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    JitCodeTable::Id id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t create_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::create_ts>(kSpec, row_);
    }
        std::optional<int64_t> estimated_delete_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, row_);
    }
        uint32_t utid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int64_t start_address() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id function_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::function_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const JitCodeTable* table_;
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
    JitCodeTable::Id id() const {
        
        return JitCodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t create_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::create_ts>(kSpec);
    }
    std::optional<int64_t> estimated_delete_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec);
    }
    uint32_t utid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec);
    }
    int64_t start_address() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::start_address>(kSpec);
    }
    int64_t size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
      StringPool::Id function_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::function_name>(kSpec);
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

    JitCodeTable::Id id() const {
        
        return JitCodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t create_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::create_ts>(kSpec);
    }
    std::optional<int64_t> estimated_delete_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec);
    }
    uint32_t utid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec);
    }
    int64_t start_address() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::start_address>(kSpec);
    }
    int64_t size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
      StringPool::Id function_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::function_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    void set_estimated_delete_ts(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(JitCodeTable* table) : table_(table) {
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
      JitCodeTable::Id id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t create_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::create_ts>(kSpec, row_);
    }
        std::optional<int64_t> estimated_delete_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, row_);
    }
        uint32_t utid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int64_t start_address() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id function_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::function_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      void set_estimated_delete_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, row_, res);
    }

    private:
      JitCodeTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const JitCodeTable* table) : table_(table) {
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
      JitCodeTable::Id id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t create_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::create_ts>(kSpec, row_);
    }
        std::optional<int64_t> estimated_delete_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::estimated_delete_ts>(kSpec, row_);
    }
        uint32_t utid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int64_t start_address() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id function_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::function_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const JitCodeTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _create_ts = {}, std::optional<int64_t> _estimated_delete_ts = {}, uint32_t _utid = {}, int64_t _start_address = {}, int64_t _size = {}, StringPool::Id _function_name = {}, std::optional<StringPool::Id> _native_code_base64 = {}) : create_ts(std::move(_create_ts)), estimated_delete_ts(std::move(_estimated_delete_ts)), utid(std::move(_utid)), start_address(std::move(_start_address)), size(std::move(_size)), function_name(std::move(_function_name)), native_code_base64(std::move(_native_code_base64)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(create_ts, other.create_ts) && std::equal_to<>()(estimated_delete_ts, other.estimated_delete_ts) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(start_address, other.start_address) && std::equal_to<>()(size, other.size) && std::equal_to<>()(function_name, other.function_name) && std::equal_to<>()(native_code_base64, other.native_code_base64);
    }

        int64_t create_ts;
    std::optional<int64_t> estimated_delete_ts;
    uint32_t utid;
    int64_t start_address;
    int64_t size;
    StringPool::Id function_name;
    std::optional<StringPool::Id> native_code_base64;
  };

  explicit JitCodeTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.create_ts, row.estimated_delete_ts, row.utid, row.start_address, row.size, std::make_optional(row.function_name), row.native_code_base64);
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
    return "__intrinsic_jit_code";
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
static_assert(sizeof(JitCodeTable) == sizeof(dataframe::Dataframe));



class JitFrameTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","jit_code_id","frame_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = JitFrameTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(JitFrameTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const JitFrameTable& table) const {
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
    static constexpr uint32_t jit_code_id = 1;
    static constexpr uint32_t frame_id = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(JitFrameTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    JitFrameTable::Id id() const {
        
        return JitFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          JitCodeTable::Id jit_code_id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::jit_code_id>(kSpec, row_)};
      }
          StackProfileFrameTable::Id frame_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    JitFrameTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const JitFrameTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    JitFrameTable::Id id() const {
        
        return JitFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          JitCodeTable::Id jit_code_id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::jit_code_id>(kSpec, row_)};
      }
          StackProfileFrameTable::Id frame_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const JitFrameTable* table_;
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
    JitFrameTable::Id id() const {
        
        return JitFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      JitCodeTable::Id jit_code_id() const {
        
        return JitCodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::jit_code_id>(kSpec)};
      }
      StackProfileFrameTable::Id frame_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return StackProfileFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::frame_id>(kSpec)};
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

    JitFrameTable::Id id() const {
        
        return JitFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      JitCodeTable::Id jit_code_id() const {
        
        return JitCodeTable::Id{cursor_.GetCellUnchecked<ColumnIndex::jit_code_id>(kSpec)};
      }
      StackProfileFrameTable::Id frame_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return StackProfileFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::frame_id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(JitFrameTable* table) : table_(table) {
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
      JitFrameTable::Id id() const {
        
        return JitFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          JitCodeTable::Id jit_code_id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::jit_code_id>(kSpec, row_)};
      }
          StackProfileFrameTable::Id frame_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }
      

    private:
      JitFrameTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const JitFrameTable* table) : table_(table) {
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
      JitFrameTable::Id id() const {
        
        return JitFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          JitCodeTable::Id jit_code_id() const {
        
        return JitCodeTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::jit_code_id>(kSpec, row_)};
      }
          StackProfileFrameTable::Id frame_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }

    private:
      const JitFrameTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(JitCodeTable::Id _jit_code_id = {}, StackProfileFrameTable::Id _frame_id = {}) : jit_code_id(std::move(_jit_code_id)), frame_id(std::move(_frame_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(jit_code_id, other.jit_code_id) && std::equal_to<>()(frame_id, other.frame_id);
    }

        JitCodeTable::Id jit_code_id;
    StackProfileFrameTable::Id frame_id;
  };

  explicit JitFrameTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.jit_code_id.value, row.frame_id.value);
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
    return "__intrinsic_jit_frame";
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
static_assert(sizeof(JitFrameTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_JIT_TABLES_PY_H_

