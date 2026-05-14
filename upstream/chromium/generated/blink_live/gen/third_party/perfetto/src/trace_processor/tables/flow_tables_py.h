#ifndef SRC_TRACE_PROCESSOR_TABLES_FLOW_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_FLOW_TABLES_PY_H_

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
#include "src/trace_processor/tables/flow_tables_fwd.h"

#include "src/trace_processor/tables/slice_tables_py.h"

namespace perfetto::trace_processor::tables {


class FlowTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","slice_out","slice_in","trace_id","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = FlowTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(FlowTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const FlowTable& table) const {
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
    static constexpr uint32_t slice_out = 1;
    static constexpr uint32_t slice_in = 2;
    static constexpr uint32_t trace_id = 3;
    static constexpr uint32_t arg_set_id = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(FlowTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    FlowTable::Id id() const {
        
        return FlowTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          SliceTable::Id slice_out() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_out>(kSpec, row_)};
      }
          SliceTable::Id slice_in() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_in>(kSpec, row_)};
      }
        std::optional<int64_t> trace_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    FlowTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const FlowTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    FlowTable::Id id() const {
        
        return FlowTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          SliceTable::Id slice_out() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_out>(kSpec, row_)};
      }
          SliceTable::Id slice_in() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_in>(kSpec, row_)};
      }
        std::optional<int64_t> trace_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const FlowTable* table_;
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
    FlowTable::Id id() const {
        
        return FlowTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      SliceTable::Id slice_out() const {
        
        return SliceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::slice_out>(kSpec)};
      }
      SliceTable::Id slice_in() const {
        
        return SliceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::slice_in>(kSpec)};
      }
    std::optional<int64_t> trace_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::trace_id>(kSpec);
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

    FlowTable::Id id() const {
        
        return FlowTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      SliceTable::Id slice_out() const {
        
        return SliceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::slice_out>(kSpec)};
      }
      SliceTable::Id slice_in() const {
        
        return SliceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::slice_in>(kSpec)};
      }
    std::optional<int64_t> trace_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::trace_id>(kSpec);
    }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(FlowTable* table) : table_(table) {
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
      FlowTable::Id id() const {
        
        return FlowTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          SliceTable::Id slice_out() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_out>(kSpec, row_)};
      }
          SliceTable::Id slice_in() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_in>(kSpec, row_)};
      }
        std::optional<int64_t> trace_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      

    private:
      FlowTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const FlowTable* table) : table_(table) {
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
      FlowTable::Id id() const {
        
        return FlowTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          SliceTable::Id slice_out() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_out>(kSpec, row_)};
      }
          SliceTable::Id slice_in() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::slice_in>(kSpec, row_)};
      }
        std::optional<int64_t> trace_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const FlowTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(SliceTable::Id _slice_out = {}, SliceTable::Id _slice_in = {}, std::optional<int64_t> _trace_id = {}, std::optional<uint32_t> _arg_set_id = {}) : slice_out(std::move(_slice_out)), slice_in(std::move(_slice_in)), trace_id(std::move(_trace_id)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(slice_out, other.slice_out) && std::equal_to<>()(slice_in, other.slice_in) && std::equal_to<>()(trace_id, other.trace_id) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        SliceTable::Id slice_out;
    SliceTable::Id slice_in;
    std::optional<int64_t> trace_id;
    std::optional<uint32_t> arg_set_id;
  };

  explicit FlowTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.slice_out.value, row.slice_in.value, row.trace_id, row.arg_set_id);
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
    return "__intrinsic_flow";
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
static_assert(sizeof(FlowTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_FLOW_TABLES_PY_H_

