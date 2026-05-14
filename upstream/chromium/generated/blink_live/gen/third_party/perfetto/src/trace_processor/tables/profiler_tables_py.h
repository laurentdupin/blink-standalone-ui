#ifndef SRC_TRACE_PROCESSOR_TABLES_PROFILER_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_PROFILER_TABLES_PY_H_

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
#include "src/trace_processor/tables/profiler_tables_fwd.h"

#include "src/trace_processor/tables/counter_tables_py.h"
#include "src/trace_processor/tables/track_tables_py.h"

namespace perfetto::trace_processor::tables {


class StackProfileMappingTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","build_id","exact_offset","start_offset","start","end","load_bias","name"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = StackProfileMappingTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(StackProfileMappingTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const StackProfileMappingTable& table) const {
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
    static constexpr uint32_t build_id = 1;
    static constexpr uint32_t exact_offset = 2;
    static constexpr uint32_t start_offset = 3;
    static constexpr uint32_t start = 4;
    static constexpr uint32_t end = 5;
    static constexpr uint32_t load_bias = 6;
    static constexpr uint32_t name = 7;
  };
  struct RowReference {
   public:
    explicit RowReference(StackProfileMappingTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    StackProfileMappingTable::Id id() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id build_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::build_id>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t exact_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::exact_offset>(kSpec, row_);
    }
        int64_t start_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_offset>(kSpec, row_);
    }
        int64_t start() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start>(kSpec, row_);
    }
        int64_t end() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end>(kSpec, row_);
    }
        int64_t load_bias() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::load_bias>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    StackProfileMappingTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const StackProfileMappingTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    StackProfileMappingTable::Id id() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id build_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::build_id>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t exact_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::exact_offset>(kSpec, row_);
    }
        int64_t start_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_offset>(kSpec, row_);
    }
        int64_t start() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start>(kSpec, row_);
    }
        int64_t end() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end>(kSpec, row_);
    }
        int64_t load_bias() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::load_bias>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const StackProfileMappingTable* table_;
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
    StackProfileMappingTable::Id id() const {
        
        return StackProfileMappingTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id build_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::build_id>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t exact_offset() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::exact_offset>(kSpec);
    }
    int64_t start_offset() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start_offset>(kSpec);
    }
    int64_t start() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start>(kSpec);
    }
    int64_t end() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::end>(kSpec);
    }
    int64_t load_bias() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::load_bias>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
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

    StackProfileMappingTable::Id id() const {
        
        return StackProfileMappingTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id build_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::build_id>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t exact_offset() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::exact_offset>(kSpec);
    }
    int64_t start_offset() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start_offset>(kSpec);
    }
    int64_t start() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start>(kSpec);
    }
    int64_t end() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::end>(kSpec);
    }
    int64_t load_bias() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::load_bias>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(StackProfileMappingTable* table) : table_(table) {
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
      StackProfileMappingTable::Id id() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id build_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::build_id>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t exact_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::exact_offset>(kSpec, row_);
    }
        int64_t start_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_offset>(kSpec, row_);
    }
        int64_t start() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start>(kSpec, row_);
    }
        int64_t end() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end>(kSpec, row_);
    }
        int64_t load_bias() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::load_bias>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      

    private:
      StackProfileMappingTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const StackProfileMappingTable* table) : table_(table) {
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
      StackProfileMappingTable::Id id() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id build_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::build_id>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t exact_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::exact_offset>(kSpec, row_);
    }
        int64_t start_offset() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_offset>(kSpec, row_);
    }
        int64_t start() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start>(kSpec, row_);
    }
        int64_t end() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end>(kSpec, row_);
    }
        int64_t load_bias() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::load_bias>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const StackProfileMappingTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _build_id = {}, int64_t _exact_offset = {}, int64_t _start_offset = {}, int64_t _start = {}, int64_t _end = {}, int64_t _load_bias = {}, StringPool::Id _name = {}) : build_id(std::move(_build_id)), exact_offset(std::move(_exact_offset)), start_offset(std::move(_start_offset)), start(std::move(_start)), end(std::move(_end)), load_bias(std::move(_load_bias)), name(std::move(_name)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(build_id, other.build_id) && std::equal_to<>()(exact_offset, other.exact_offset) && std::equal_to<>()(start_offset, other.start_offset) && std::equal_to<>()(start, other.start) && std::equal_to<>()(end, other.end) && std::equal_to<>()(load_bias, other.load_bias) && std::equal_to<>()(name, other.name);
    }

        StringPool::Id build_id;
    int64_t exact_offset;
    int64_t start_offset;
    int64_t start;
    int64_t end;
    int64_t load_bias;
    StringPool::Id name;
  };

  explicit StackProfileMappingTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.build_id), row.exact_offset, row.start_offset, row.start, row.end, row.load_bias, std::make_optional(row.name));
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
    return "__intrinsic_stack_profile_mapping";
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
static_assert(sizeof(StackProfileMappingTable) == sizeof(dataframe::Dataframe));



class StackProfileFrameTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","name","mapping","rel_pc","symbol_set_id","deobfuscated_name"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = StackProfileFrameTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(StackProfileFrameTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const StackProfileFrameTable& table) const {
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
    static constexpr uint32_t name = 1;
    static constexpr uint32_t mapping = 2;
    static constexpr uint32_t rel_pc = 3;
    static constexpr uint32_t symbol_set_id = 4;
    static constexpr uint32_t deobfuscated_name = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(StackProfileFrameTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    StackProfileFrameTable::Id id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StackProfileMappingTable::Id mapping() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::mapping>(kSpec, row_)};
      }
        int64_t rel_pc() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::rel_pc>(kSpec, row_);
    }
        std::optional<uint32_t> symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
    void set_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
        void set_symbol_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_, res);
    }
          void set_deobfuscated_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    StackProfileFrameTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const StackProfileFrameTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    StackProfileFrameTable::Id id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StackProfileMappingTable::Id mapping() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::mapping>(kSpec, row_)};
      }
        int64_t rel_pc() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::rel_pc>(kSpec, row_);
    }
        std::optional<uint32_t> symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const StackProfileFrameTable* table_;
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
    StackProfileFrameTable::Id id() const {
        
        return StackProfileFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StackProfileMappingTable::Id mapping() const {
        
        return StackProfileMappingTable::Id{cursor_.GetCellUnchecked<ColumnIndex::mapping>(kSpec)};
      }
    int64_t rel_pc() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::rel_pc>(kSpec);
    }
    std::optional<uint32_t> symbol_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec);
    }
      std::optional<StringPool::Id> deobfuscated_name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec);
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

    StackProfileFrameTable::Id id() const {
        
        return StackProfileFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StackProfileMappingTable::Id mapping() const {
        
        return StackProfileMappingTable::Id{cursor_.GetCellUnchecked<ColumnIndex::mapping>(kSpec)};
      }
    int64_t rel_pc() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::rel_pc>(kSpec);
    }
    std::optional<uint32_t> symbol_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec);
    }
      std::optional<StringPool::Id> deobfuscated_name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec);
      }
    void set_name(StringPool::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, std::make_optional(res));
    }
    void set_symbol_set_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, res);
    }
      void set_deobfuscated_name(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(StackProfileFrameTable* table) : table_(table) {
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
      StackProfileFrameTable::Id id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StackProfileMappingTable::Id mapping() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::mapping>(kSpec, row_)};
      }
        int64_t rel_pc() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::rel_pc>(kSpec, row_);
    }
        std::optional<uint32_t> symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
      void set_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
        void set_symbol_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_, res);
    }
          void set_deobfuscated_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_, res);
    }

    private:
      StackProfileFrameTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const StackProfileFrameTable* table) : table_(table) {
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
      StackProfileFrameTable::Id id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StackProfileMappingTable::Id mapping() const {
        
        return StackProfileMappingTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::mapping>(kSpec, row_)};
      }
        int64_t rel_pc() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::rel_pc>(kSpec, row_);
    }
        std::optional<uint32_t> symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }

    private:
      const StackProfileFrameTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _name = {}, StackProfileMappingTable::Id _mapping = {}, int64_t _rel_pc = {}, std::optional<uint32_t> _symbol_set_id = {}, std::optional<StringPool::Id> _deobfuscated_name = {}) : name(std::move(_name)), mapping(std::move(_mapping)), rel_pc(std::move(_rel_pc)), symbol_set_id(std::move(_symbol_set_id)), deobfuscated_name(std::move(_deobfuscated_name)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(name, other.name) && std::equal_to<>()(mapping, other.mapping) && std::equal_to<>()(rel_pc, other.rel_pc) && std::equal_to<>()(symbol_set_id, other.symbol_set_id) && std::equal_to<>()(deobfuscated_name, other.deobfuscated_name);
    }

        StringPool::Id name;
    StackProfileMappingTable::Id mapping;
    int64_t rel_pc;
    std::optional<uint32_t> symbol_set_id;
    std::optional<StringPool::Id> deobfuscated_name;
  };

  explicit StackProfileFrameTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.name), row.mapping.value, row.rel_pc, row.symbol_set_id, row.deobfuscated_name);
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
    return "__intrinsic_stack_profile_frame";
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
static_assert(sizeof(StackProfileFrameTable) == sizeof(dataframe::Dataframe));



class AggregateProfileTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","scope","name","sample_type_type","sample_type_unit"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AggregateProfileTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AggregateProfileTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AggregateProfileTable& table) const {
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
    static constexpr uint32_t scope = 1;
    static constexpr uint32_t name = 2;
    static constexpr uint32_t sample_type_type = 3;
    static constexpr uint32_t sample_type_unit = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(AggregateProfileTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AggregateProfileTable::Id id() const {
        
        return AggregateProfileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AggregateProfileTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AggregateProfileTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AggregateProfileTable::Id id() const {
        
        return AggregateProfileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AggregateProfileTable* table_;
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
    AggregateProfileTable::Id id() const {
        
        return AggregateProfileTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    AggregateProfileTable::Id id() const {
        
        return AggregateProfileTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AggregateProfileTable* table) : table_(table) {
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
      AggregateProfileTable::Id id() const {
        
        return AggregateProfileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      AggregateProfileTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AggregateProfileTable* table) : table_(table) {
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
      AggregateProfileTable::Id id() const {
        
        return AggregateProfileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const AggregateProfileTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _scope = {}, StringPool::Id _name = {}, StringPool::Id _sample_type_type = {}, StringPool::Id _sample_type_unit = {}) : scope(std::move(_scope)), name(std::move(_name)), sample_type_type(std::move(_sample_type_type)), sample_type_unit(std::move(_sample_type_unit)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(scope, other.scope) && std::equal_to<>()(name, other.name) && std::equal_to<>()(sample_type_type, other.sample_type_type) && std::equal_to<>()(sample_type_unit, other.sample_type_unit);
    }

        StringPool::Id scope;
    StringPool::Id name;
    StringPool::Id sample_type_type;
    StringPool::Id sample_type_unit;
  };

  explicit AggregateProfileTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.scope), std::make_optional(row.name), std::make_optional(row.sample_type_type), std::make_optional(row.sample_type_unit));
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
    return "__intrinsic_aggregate_profile";
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
static_assert(sizeof(AggregateProfileTable) == sizeof(dataframe::Dataframe));



class StackProfileCallsiteTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","depth","parent_id","frame_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = StackProfileCallsiteTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(StackProfileCallsiteTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const StackProfileCallsiteTable& table) const {
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
    static constexpr uint32_t depth = 1;
    static constexpr uint32_t parent_id = 2;
    static constexpr uint32_t frame_id = 3;
  };
  struct RowReference {
   public:
    explicit RowReference(StackProfileCallsiteTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    StackProfileCallsiteTable::Id id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          StackProfileFrameTable::Id frame_id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }
    void set_depth(uint32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::depth>(kSpec, row_, res);
    }
          void set_parent_id(std::optional<StackProfileCallsiteTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    StackProfileCallsiteTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const StackProfileCallsiteTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    StackProfileCallsiteTable::Id id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          StackProfileFrameTable::Id frame_id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const StackProfileCallsiteTable* table_;
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
    StackProfileCallsiteTable::Id id() const {
        
        return StackProfileCallsiteTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t depth() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::depth>(kSpec);
    }
      std::optional<StackProfileCallsiteTable::Id> parent_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
      StackProfileFrameTable::Id frame_id() const {
        
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

    StackProfileCallsiteTable::Id id() const {
        
        return StackProfileCallsiteTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t depth() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::depth>(kSpec);
    }
      std::optional<StackProfileCallsiteTable::Id> parent_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
      StackProfileFrameTable::Id frame_id() const {
        
        return StackProfileFrameTable::Id{cursor_.GetCellUnchecked<ColumnIndex::frame_id>(kSpec)};
      }
    void set_depth(uint32_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::depth>(kSpec, res);
    }
      void set_parent_id(std::optional<StackProfileCallsiteTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, res_value);
      }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(StackProfileCallsiteTable* table) : table_(table) {
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
      StackProfileCallsiteTable::Id id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          StackProfileFrameTable::Id frame_id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }
      void set_depth(uint32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::depth>(kSpec, row_, res);
    }
          void set_parent_id(std::optional<StackProfileCallsiteTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }

    private:
      StackProfileCallsiteTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const StackProfileCallsiteTable* table) : table_(table) {
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
      StackProfileCallsiteTable::Id id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          StackProfileFrameTable::Id frame_id() const {
        
        return StackProfileFrameTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::frame_id>(kSpec, row_)};
      }

    private:
      const StackProfileCallsiteTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _depth = {}, std::optional<StackProfileCallsiteTable::Id> _parent_id = {}, StackProfileFrameTable::Id _frame_id = {}) : depth(std::move(_depth)), parent_id(std::move(_parent_id)), frame_id(std::move(_frame_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(depth, other.depth) && std::equal_to<>()(parent_id, other.parent_id) && std::equal_to<>()(frame_id, other.frame_id);
    }

        uint32_t depth;
    std::optional<StackProfileCallsiteTable::Id> parent_id;
    StackProfileFrameTable::Id frame_id;
  };

  explicit StackProfileCallsiteTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.depth, row.parent_id ? std::make_optional(row.parent_id->value) : std::nullopt, row.frame_id.value);
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
    return "__intrinsic_stack_profile_callsite";
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
static_assert(sizeof(StackProfileCallsiteTable) == sizeof(dataframe::Dataframe));



class AggregateSampleTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","aggregate_profile_id","callsite_id","value"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AggregateSampleTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AggregateSampleTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AggregateSampleTable& table) const {
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
    static constexpr uint32_t aggregate_profile_id = 1;
    static constexpr uint32_t callsite_id = 2;
    static constexpr uint32_t value = 3;
  };
  struct RowReference {
   public:
    explicit RowReference(AggregateSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    AggregateSampleTable::Id id() const {
        
        return AggregateSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AggregateSampleTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AggregateSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    AggregateSampleTable::Id id() const {
        
        return AggregateSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AggregateSampleTable* table_;
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
    AggregateSampleTable::Id id() const {
        
        return AggregateSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    AggregateSampleTable::Id id() const {
        
        return AggregateSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AggregateSampleTable* table) : table_(table) {
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
      AggregateSampleTable::Id id() const {
        
        return AggregateSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      AggregateSampleTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AggregateSampleTable* table) : table_(table) {
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
      AggregateSampleTable::Id id() const {
        
        return AggregateSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const AggregateSampleTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(AggregateProfileTable::Id _aggregate_profile_id = {}, StackProfileCallsiteTable::Id _callsite_id = {}, double _value = {}) : aggregate_profile_id(std::move(_aggregate_profile_id)), callsite_id(std::move(_callsite_id)), value(std::move(_value)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(aggregate_profile_id, other.aggregate_profile_id) && std::equal_to<>()(callsite_id, other.callsite_id) && std::equal_to<>()(value, other.value);
    }

        AggregateProfileTable::Id aggregate_profile_id;
    StackProfileCallsiteTable::Id callsite_id;
    double value;
  };

  explicit AggregateSampleTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.aggregate_profile_id.value, row.callsite_id.value, row.value);
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
    return "__intrinsic_aggregate_sample";
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
static_assert(sizeof(AggregateSampleTable) == sizeof(dataframe::Dataframe));



class CpuProfileStackSampleTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","callsite_id","utid","process_priority"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = CpuProfileStackSampleTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(CpuProfileStackSampleTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const CpuProfileStackSampleTable& table) const {
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
    static constexpr uint32_t callsite_id = 2;
    static constexpr uint32_t utid = 3;
    static constexpr uint32_t process_priority = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(CpuProfileStackSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    CpuProfileStackSampleTable::Id id() const {
        
        return CpuProfileStackSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int32_t process_priority() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_priority>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    CpuProfileStackSampleTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const CpuProfileStackSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    CpuProfileStackSampleTable::Id id() const {
        
        return CpuProfileStackSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int32_t process_priority() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_priority>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const CpuProfileStackSampleTable* table_;
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
    CpuProfileStackSampleTable::Id id() const {
        
        return CpuProfileStackSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec)};
      }
    uint32_t utid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec);
    }
    int32_t process_priority() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::process_priority>(kSpec);
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

    CpuProfileStackSampleTable::Id id() const {
        
        return CpuProfileStackSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec)};
      }
    uint32_t utid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec);
    }
    int32_t process_priority() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::process_priority>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(CpuProfileStackSampleTable* table) : table_(table) {
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
      CpuProfileStackSampleTable::Id id() const {
        
        return CpuProfileStackSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int32_t process_priority() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_priority>(kSpec, row_);
    }
      

    private:
      CpuProfileStackSampleTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const CpuProfileStackSampleTable* table) : table_(table) {
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
      CpuProfileStackSampleTable::Id id() const {
        
        return CpuProfileStackSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
        int32_t process_priority() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::process_priority>(kSpec, row_);
    }

    private:
      const CpuProfileStackSampleTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, StackProfileCallsiteTable::Id _callsite_id = {}, uint32_t _utid = {}, int32_t _process_priority = {}) : ts(std::move(_ts)), callsite_id(std::move(_callsite_id)), utid(std::move(_utid)), process_priority(std::move(_process_priority)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(callsite_id, other.callsite_id) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(process_priority, other.process_priority);
    }

        int64_t ts;
    StackProfileCallsiteTable::Id callsite_id;
    uint32_t utid;
    int32_t process_priority;
  };

  explicit CpuProfileStackSampleTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.callsite_id.value, row.utid, row.process_priority);
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
    return "__intrinsic_cpu_profile_stack_sample";
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
static_assert(sizeof(CpuProfileStackSampleTable) == sizeof(dataframe::Dataframe));



class ExperimentalFlamegraphTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","profile_type","ts_in","ts_constraint","upid","upid_group","focus_str","ts","depth","name","map_name","count","cumulative_count","size","cumulative_size","alloc_count","cumulative_alloc_count","alloc_size","cumulative_alloc_size","parent_id","source_file","line_number"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ExperimentalFlamegraphTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ExperimentalFlamegraphTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ExperimentalFlamegraphTable& table) const {
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
    static constexpr uint32_t profile_type = 1;
    static constexpr uint32_t ts_in = 2;
    static constexpr uint32_t ts_constraint = 3;
    static constexpr uint32_t upid = 4;
    static constexpr uint32_t upid_group = 5;
    static constexpr uint32_t focus_str = 6;
    static constexpr uint32_t ts = 7;
    static constexpr uint32_t depth = 8;
    static constexpr uint32_t name = 9;
    static constexpr uint32_t map_name = 10;
    static constexpr uint32_t count = 11;
    static constexpr uint32_t cumulative_count = 12;
    static constexpr uint32_t size = 13;
    static constexpr uint32_t cumulative_size = 14;
    static constexpr uint32_t alloc_count = 15;
    static constexpr uint32_t cumulative_alloc_count = 16;
    static constexpr uint32_t alloc_size = 17;
    static constexpr uint32_t cumulative_alloc_size = 18;
    static constexpr uint32_t parent_id = 19;
    static constexpr uint32_t source_file = 20;
    static constexpr uint32_t line_number = 21;
  };
  struct RowReference {
   public:
    explicit RowReference(ExperimentalFlamegraphTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ExperimentalFlamegraphTable::Id id() const {
        
        return ExperimentalFlamegraphTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id profile_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::profile_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> upid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t depth() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id map_name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::map_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t cumulative_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t cumulative_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, row_);
    }
        int64_t alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_count>(kSpec, row_);
    }
        int64_t cumulative_alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, row_);
    }
        int64_t alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_size>(kSpec, row_);
    }
        int64_t cumulative_alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, row_);
    }
          std::optional<ExperimentalFlamegraphTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(ExperimentalFlamegraphTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> source_file() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }
    void set_ts(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::ts>(kSpec, row_, res);
    }
        void set_depth(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::depth>(kSpec, row_, res);
    }
          void set_name(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
          void set_map_name(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::map_name>(kSpec, row_, std::make_optional(res));
    }
        void set_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::count>(kSpec, row_, res);
    }
        void set_cumulative_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, row_, res);
    }
        void set_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::size>(kSpec, row_, res);
    }
        void set_cumulative_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, row_, res);
    }
        void set_alloc_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::alloc_count>(kSpec, row_, res);
    }
        void set_cumulative_alloc_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, row_, res);
    }
        void set_alloc_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::alloc_size>(kSpec, row_, res);
    }
        void set_cumulative_alloc_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, row_, res);
    }
          void set_parent_id(std::optional<ExperimentalFlamegraphTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
          void set_source_file(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::source_file>(kSpec, row_, res);
    }
        void set_line_number(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::line_number>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ExperimentalFlamegraphTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ExperimentalFlamegraphTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ExperimentalFlamegraphTable::Id id() const {
        
        return ExperimentalFlamegraphTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id profile_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::profile_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> upid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t depth() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id map_name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::map_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t cumulative_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t cumulative_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, row_);
    }
        int64_t alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_count>(kSpec, row_);
    }
        int64_t cumulative_alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, row_);
    }
        int64_t alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_size>(kSpec, row_);
    }
        int64_t cumulative_alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, row_);
    }
          std::optional<ExperimentalFlamegraphTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(ExperimentalFlamegraphTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> source_file() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ExperimentalFlamegraphTable* table_;
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
    ExperimentalFlamegraphTable::Id id() const {
        
        return ExperimentalFlamegraphTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id profile_type() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::profile_type>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<uint32_t> upid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
    int64_t ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    uint32_t depth() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::depth>(kSpec);
    }
      StringPool::Id name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id map_name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::map_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::count>(kSpec);
    }
    int64_t cumulative_count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_count>(kSpec);
    }
    int64_t size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
    int64_t cumulative_size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_size>(kSpec);
    }
    int64_t alloc_count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::alloc_count>(kSpec);
    }
    int64_t cumulative_alloc_count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec);
    }
    int64_t alloc_size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::alloc_size>(kSpec);
    }
    int64_t cumulative_alloc_size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec);
    }
      std::optional<ExperimentalFlamegraphTable::Id> parent_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(ExperimentalFlamegraphTable::Id{*res}) : std::nullopt;
      }
      std::optional<StringPool::Id> source_file() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::source_file>(kSpec);
      }
    std::optional<uint32_t> line_number() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::line_number>(kSpec);
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

    ExperimentalFlamegraphTable::Id id() const {
        
        return ExperimentalFlamegraphTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id profile_type() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::profile_type>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<uint32_t> upid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
    int64_t ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    uint32_t depth() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::depth>(kSpec);
    }
      StringPool::Id name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id map_name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::map_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::count>(kSpec);
    }
    int64_t cumulative_count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_count>(kSpec);
    }
    int64_t size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
    int64_t cumulative_size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_size>(kSpec);
    }
    int64_t alloc_count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::alloc_count>(kSpec);
    }
    int64_t cumulative_alloc_count() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec);
    }
    int64_t alloc_size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::alloc_size>(kSpec);
    }
    int64_t cumulative_alloc_size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec);
    }
      std::optional<ExperimentalFlamegraphTable::Id> parent_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(ExperimentalFlamegraphTable::Id{*res}) : std::nullopt;
      }
      std::optional<StringPool::Id> source_file() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::source_file>(kSpec);
      }
    std::optional<uint32_t> line_number() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::line_number>(kSpec);
    }
    void set_ts(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::ts>(kSpec, res);
    }
    void set_depth(uint32_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::depth>(kSpec, res);
    }
      void set_name(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, std::make_optional(res));
    }
      void set_map_name(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::map_name>(kSpec, std::make_optional(res));
    }
    void set_count(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::count>(kSpec, res);
    }
    void set_cumulative_count(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, res);
    }
    void set_size(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::size>(kSpec, res);
    }
    void set_cumulative_size(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, res);
    }
    void set_alloc_count(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::alloc_count>(kSpec, res);
    }
    void set_cumulative_alloc_count(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, res);
    }
    void set_alloc_size(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::alloc_size>(kSpec, res);
    }
    void set_cumulative_alloc_size(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, res);
    }
      void set_parent_id(std::optional<ExperimentalFlamegraphTable::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, res_value);
      }
      void set_source_file(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::source_file>(kSpec, res);
    }
    void set_line_number(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::line_number>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ExperimentalFlamegraphTable* table) : table_(table) {
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
      ExperimentalFlamegraphTable::Id id() const {
        
        return ExperimentalFlamegraphTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id profile_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::profile_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> upid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t depth() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id map_name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::map_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t cumulative_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t cumulative_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, row_);
    }
        int64_t alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_count>(kSpec, row_);
    }
        int64_t cumulative_alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, row_);
    }
        int64_t alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_size>(kSpec, row_);
    }
        int64_t cumulative_alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, row_);
    }
          std::optional<ExperimentalFlamegraphTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(ExperimentalFlamegraphTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> source_file() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }
      void set_ts(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::ts>(kSpec, row_, res);
    }
        void set_depth(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::depth>(kSpec, row_, res);
    }
          void set_name(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
          void set_map_name(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::map_name>(kSpec, row_, std::make_optional(res));
    }
        void set_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::count>(kSpec, row_, res);
    }
        void set_cumulative_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, row_, res);
    }
        void set_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::size>(kSpec, row_, res);
    }
        void set_cumulative_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, row_, res);
    }
        void set_alloc_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::alloc_count>(kSpec, row_, res);
    }
        void set_cumulative_alloc_count(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, row_, res);
    }
        void set_alloc_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::alloc_size>(kSpec, row_, res);
    }
        void set_cumulative_alloc_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, row_, res);
    }
          void set_parent_id(std::optional<ExperimentalFlamegraphTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
          void set_source_file(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::source_file>(kSpec, row_, res);
    }
        void set_line_number(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::line_number>(kSpec, row_, res);
    }

    private:
      ExperimentalFlamegraphTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ExperimentalFlamegraphTable* table) : table_(table) {
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
      ExperimentalFlamegraphTable::Id id() const {
        
        return ExperimentalFlamegraphTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id profile_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::profile_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> upid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t depth() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id map_name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::map_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t cumulative_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_count>(kSpec, row_);
    }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
        int64_t cumulative_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_size>(kSpec, row_);
    }
        int64_t alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_count>(kSpec, row_);
    }
        int64_t cumulative_alloc_count() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_count>(kSpec, row_);
    }
        int64_t alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::alloc_size>(kSpec, row_);
    }
        int64_t cumulative_alloc_size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cumulative_alloc_size>(kSpec, row_);
    }
          std::optional<ExperimentalFlamegraphTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(ExperimentalFlamegraphTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> source_file() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }

    private:
      const ExperimentalFlamegraphTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _profile_type = {}, std::optional<int64_t> _ts_in = {}, std::optional<StringPool::Id> _ts_constraint = {}, std::optional<uint32_t> _upid = {}, std::optional<StringPool::Id> _upid_group = {}, std::optional<StringPool::Id> _focus_str = {}, int64_t _ts = {}, uint32_t _depth = {}, StringPool::Id _name = {}, StringPool::Id _map_name = {}, int64_t _count = {}, int64_t _cumulative_count = {}, int64_t _size = {}, int64_t _cumulative_size = {}, int64_t _alloc_count = {}, int64_t _cumulative_alloc_count = {}, int64_t _alloc_size = {}, int64_t _cumulative_alloc_size = {}, std::optional<ExperimentalFlamegraphTable::Id> _parent_id = {}, std::optional<StringPool::Id> _source_file = {}, std::optional<uint32_t> _line_number = {}) : profile_type(std::move(_profile_type)), ts_in(std::move(_ts_in)), ts_constraint(std::move(_ts_constraint)), upid(std::move(_upid)), upid_group(std::move(_upid_group)), focus_str(std::move(_focus_str)), ts(std::move(_ts)), depth(std::move(_depth)), name(std::move(_name)), map_name(std::move(_map_name)), count(std::move(_count)), cumulative_count(std::move(_cumulative_count)), size(std::move(_size)), cumulative_size(std::move(_cumulative_size)), alloc_count(std::move(_alloc_count)), cumulative_alloc_count(std::move(_cumulative_alloc_count)), alloc_size(std::move(_alloc_size)), cumulative_alloc_size(std::move(_cumulative_alloc_size)), parent_id(std::move(_parent_id)), source_file(std::move(_source_file)), line_number(std::move(_line_number)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(profile_type, other.profile_type) && std::equal_to<>()(ts_in, other.ts_in) && std::equal_to<>()(ts_constraint, other.ts_constraint) && std::equal_to<>()(upid, other.upid) && std::equal_to<>()(upid_group, other.upid_group) && std::equal_to<>()(focus_str, other.focus_str) && std::equal_to<>()(ts, other.ts) && std::equal_to<>()(depth, other.depth) && std::equal_to<>()(name, other.name) && std::equal_to<>()(map_name, other.map_name) && std::equal_to<>()(count, other.count) && std::equal_to<>()(cumulative_count, other.cumulative_count) && std::equal_to<>()(size, other.size) && std::equal_to<>()(cumulative_size, other.cumulative_size) && std::equal_to<>()(alloc_count, other.alloc_count) && std::equal_to<>()(cumulative_alloc_count, other.cumulative_alloc_count) && std::equal_to<>()(alloc_size, other.alloc_size) && std::equal_to<>()(cumulative_alloc_size, other.cumulative_alloc_size) && std::equal_to<>()(parent_id, other.parent_id) && std::equal_to<>()(source_file, other.source_file) && std::equal_to<>()(line_number, other.line_number);
    }

        StringPool::Id profile_type;
    std::optional<int64_t> ts_in;
    std::optional<StringPool::Id> ts_constraint;
    std::optional<uint32_t> upid;
    std::optional<StringPool::Id> upid_group;
    std::optional<StringPool::Id> focus_str;
    int64_t ts;
    uint32_t depth;
    StringPool::Id name;
    StringPool::Id map_name;
    int64_t count;
    int64_t cumulative_count;
    int64_t size;
    int64_t cumulative_size;
    int64_t alloc_count;
    int64_t cumulative_alloc_count;
    int64_t alloc_size;
    int64_t cumulative_alloc_size;
    std::optional<ExperimentalFlamegraphTable::Id> parent_id;
    std::optional<StringPool::Id> source_file;
    std::optional<uint32_t> line_number;
  };

  explicit ExperimentalFlamegraphTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.profile_type), row.ts_in, row.ts_constraint, row.upid, row.upid_group, row.focus_str, row.ts, row.depth, std::make_optional(row.name), std::make_optional(row.map_name), row.count, row.cumulative_count, row.size, row.cumulative_size, row.alloc_count, row.cumulative_alloc_count, row.alloc_size, row.cumulative_alloc_size, row.parent_id ? std::make_optional(row.parent_id->value) : std::nullopt, row.source_file, row.line_number);
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
    return "experimental_flamegraph";
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
static_assert(sizeof(ExperimentalFlamegraphTable) == sizeof(dataframe::Dataframe));



class GpuContextTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","context_id","pid","api"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = GpuContextTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(GpuContextTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const GpuContextTable& table) const {
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
    static constexpr uint32_t context_id = 1;
    static constexpr uint32_t pid = 2;
    static constexpr uint32_t api = 3;
  };
  struct RowReference {
   public:
    explicit RowReference(GpuContextTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    GpuContextTable::Id id() const {
        
        return GpuContextTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    GpuContextTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const GpuContextTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    GpuContextTable::Id id() const {
        
        return GpuContextTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const GpuContextTable* table_;
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
    GpuContextTable::Id id() const {
        
        return GpuContextTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    GpuContextTable::Id id() const {
        
        return GpuContextTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(GpuContextTable* table) : table_(table) {
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
      GpuContextTable::Id id() const {
        
        return GpuContextTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      GpuContextTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const GpuContextTable* table) : table_(table) {
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
      GpuContextTable::Id id() const {
        
        return GpuContextTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const GpuContextTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _context_id = {}, std::optional<uint32_t> _pid = {}, std::optional<StringPool::Id> _api = {}) : context_id(std::move(_context_id)), pid(std::move(_pid)), api(std::move(_api)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(context_id, other.context_id) && std::equal_to<>()(pid, other.pid) && std::equal_to<>()(api, other.api);
    }

        uint32_t context_id;
    std::optional<uint32_t> pid;
    std::optional<StringPool::Id> api;
  };

  explicit GpuContextTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.context_id, row.pid, row.api);
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
    return "__intrinsic_gpu_context";
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
static_assert(sizeof(GpuContextTable) == sizeof(dataframe::Dataframe));



class GpuCounterGroupTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","group_id","track_id","name","description"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = GpuCounterGroupTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(GpuCounterGroupTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const GpuCounterGroupTable& table) const {
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
    static constexpr uint32_t group_id = 1;
    static constexpr uint32_t track_id = 2;
    static constexpr uint32_t name = 3;
    static constexpr uint32_t description = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(GpuCounterGroupTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    GpuCounterGroupTable::Id id() const {
        
        return GpuCounterGroupTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    GpuCounterGroupTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const GpuCounterGroupTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    GpuCounterGroupTable::Id id() const {
        
        return GpuCounterGroupTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const GpuCounterGroupTable* table_;
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
    GpuCounterGroupTable::Id id() const {
        
        return GpuCounterGroupTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    GpuCounterGroupTable::Id id() const {
        
        return GpuCounterGroupTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(GpuCounterGroupTable* table) : table_(table) {
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
      GpuCounterGroupTable::Id id() const {
        
        return GpuCounterGroupTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      GpuCounterGroupTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const GpuCounterGroupTable* table) : table_(table) {
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
      GpuCounterGroupTable::Id id() const {
        
        return GpuCounterGroupTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const GpuCounterGroupTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int32_t _group_id = {}, TrackTable::Id _track_id = {}, std::optional<StringPool::Id> _name = {}, std::optional<StringPool::Id> _description = {}) : group_id(std::move(_group_id)), track_id(std::move(_track_id)), name(std::move(_name)), description(std::move(_description)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(group_id, other.group_id) && std::equal_to<>()(track_id, other.track_id) && std::equal_to<>()(name, other.name) && std::equal_to<>()(description, other.description);
    }

        int32_t group_id;
    TrackTable::Id track_id;
    std::optional<StringPool::Id> name;
    std::optional<StringPool::Id> description;
  };

  explicit GpuCounterGroupTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.group_id, row.track_id.value, row.name, row.description);
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
    return "__intrinsic_gpu_counter_group";
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
static_assert(sizeof(GpuCounterGroupTable) == sizeof(dataframe::Dataframe));



class HeapGraphClassTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","name","deobfuscated_name","location","superclass_id","classloader_id","kind"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = HeapGraphClassTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(HeapGraphClassTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const HeapGraphClassTable& table) const {
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
    static constexpr uint32_t name = 1;
    static constexpr uint32_t deobfuscated_name = 2;
    static constexpr uint32_t location = 3;
    static constexpr uint32_t superclass_id = 4;
    static constexpr uint32_t classloader_id = 5;
    static constexpr uint32_t kind = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(HeapGraphClassTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    HeapGraphClassTable::Id id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
          std::optional<StringPool::Id> location() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::location>(kSpec, row_);
      }
          std::optional<HeapGraphClassTable::Id> superclass_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::superclass_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphClassTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> classloader_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::classloader_id>(kSpec, row_);
    }
          StringPool::Id kind() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::kind>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    void set_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
          void set_deobfuscated_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_, res);
    }
          void set_location(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::location>(kSpec, row_, res);
    }
          void set_superclass_id(std::optional<HeapGraphClassTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::superclass_id>(kSpec, row_, res_value);
      }
        void set_classloader_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::classloader_id>(kSpec, row_, res);
    }
          void set_kind(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::kind>(kSpec, row_, std::make_optional(res));
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    HeapGraphClassTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const HeapGraphClassTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    HeapGraphClassTable::Id id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
          std::optional<StringPool::Id> location() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::location>(kSpec, row_);
      }
          std::optional<HeapGraphClassTable::Id> superclass_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::superclass_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphClassTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> classloader_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::classloader_id>(kSpec, row_);
    }
          StringPool::Id kind() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::kind>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const HeapGraphClassTable* table_;
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
    HeapGraphClassTable::Id id() const {
        
        return HeapGraphClassTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      std::optional<StringPool::Id> deobfuscated_name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec);
      }
      std::optional<StringPool::Id> location() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::location>(kSpec);
      }
      std::optional<HeapGraphClassTable::Id> superclass_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::superclass_id>(kSpec);
        return res ? std::make_optional(HeapGraphClassTable::Id{*res}) : std::nullopt;
      }
    std::optional<uint32_t> classloader_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::classloader_id>(kSpec);
    }
      StringPool::Id kind() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::kind>(kSpec);
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

    HeapGraphClassTable::Id id() const {
        
        return HeapGraphClassTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      std::optional<StringPool::Id> deobfuscated_name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec);
      }
      std::optional<StringPool::Id> location() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::location>(kSpec);
      }
      std::optional<HeapGraphClassTable::Id> superclass_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::superclass_id>(kSpec);
        return res ? std::make_optional(HeapGraphClassTable::Id{*res}) : std::nullopt;
      }
    std::optional<uint32_t> classloader_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::classloader_id>(kSpec);
    }
      StringPool::Id kind() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::kind>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    void set_name(StringPool::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, std::make_optional(res));
    }
      void set_deobfuscated_name(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, res);
    }
      void set_location(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::location>(kSpec, res);
    }
      void set_superclass_id(std::optional<HeapGraphClassTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::superclass_id>(kSpec, res_value);
      }
    void set_classloader_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::classloader_id>(kSpec, res);
    }
      void set_kind(StringPool::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::kind>(kSpec, std::make_optional(res));
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(HeapGraphClassTable* table) : table_(table) {
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
      HeapGraphClassTable::Id id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
          std::optional<StringPool::Id> location() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::location>(kSpec, row_);
      }
          std::optional<HeapGraphClassTable::Id> superclass_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::superclass_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphClassTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> classloader_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::classloader_id>(kSpec, row_);
    }
          StringPool::Id kind() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::kind>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      void set_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
          void set_deobfuscated_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_, res);
    }
          void set_location(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::location>(kSpec, row_, res);
    }
          void set_superclass_id(std::optional<HeapGraphClassTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::superclass_id>(kSpec, row_, res_value);
      }
        void set_classloader_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::classloader_id>(kSpec, row_, res);
    }
          void set_kind(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::kind>(kSpec, row_, std::make_optional(res));
    }

    private:
      HeapGraphClassTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const HeapGraphClassTable* table) : table_(table) {
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
      HeapGraphClassTable::Id id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_name>(kSpec, row_);
      }
          std::optional<StringPool::Id> location() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::location>(kSpec, row_);
      }
          std::optional<HeapGraphClassTable::Id> superclass_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::superclass_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphClassTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> classloader_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::classloader_id>(kSpec, row_);
    }
          StringPool::Id kind() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::kind>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const HeapGraphClassTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _name = {}, std::optional<StringPool::Id> _deobfuscated_name = {}, std::optional<StringPool::Id> _location = {}, std::optional<HeapGraphClassTable::Id> _superclass_id = {}, std::optional<uint32_t> _classloader_id = {}, StringPool::Id _kind = {}) : name(std::move(_name)), deobfuscated_name(std::move(_deobfuscated_name)), location(std::move(_location)), superclass_id(std::move(_superclass_id)), classloader_id(std::move(_classloader_id)), kind(std::move(_kind)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(name, other.name) && std::equal_to<>()(deobfuscated_name, other.deobfuscated_name) && std::equal_to<>()(location, other.location) && std::equal_to<>()(superclass_id, other.superclass_id) && std::equal_to<>()(classloader_id, other.classloader_id) && std::equal_to<>()(kind, other.kind);
    }

        StringPool::Id name;
    std::optional<StringPool::Id> deobfuscated_name;
    std::optional<StringPool::Id> location;
    std::optional<HeapGraphClassTable::Id> superclass_id;
    std::optional<uint32_t> classloader_id;
    StringPool::Id kind;
  };

  explicit HeapGraphClassTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.name), row.deobfuscated_name, row.location, row.superclass_id ? std::make_optional(row.superclass_id->value) : std::nullopt, row.classloader_id, std::make_optional(row.kind));
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
    return "__intrinsic_heap_graph_class";
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
static_assert(sizeof(HeapGraphClassTable) == sizeof(dataframe::Dataframe));



class HeapGraphObjectDataTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","field_set_id","value_string","array_element_type","array_element_count","array_data_id","array_data_hash"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = HeapGraphObjectDataTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(HeapGraphObjectDataTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const HeapGraphObjectDataTable& table) const {
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
    static constexpr uint32_t field_set_id = 1;
    static constexpr uint32_t value_string = 2;
    static constexpr uint32_t array_element_type = 3;
    static constexpr uint32_t array_element_count = 4;
    static constexpr uint32_t array_data_id = 5;
    static constexpr uint32_t array_data_hash = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(HeapGraphObjectDataTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    HeapGraphObjectDataTable::Id id() const {
        
        return HeapGraphObjectDataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    HeapGraphObjectDataTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const HeapGraphObjectDataTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    HeapGraphObjectDataTable::Id id() const {
        
        return HeapGraphObjectDataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const HeapGraphObjectDataTable* table_;
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
    HeapGraphObjectDataTable::Id id() const {
        
        return HeapGraphObjectDataTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    HeapGraphObjectDataTable::Id id() const {
        
        return HeapGraphObjectDataTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(HeapGraphObjectDataTable* table) : table_(table) {
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
      HeapGraphObjectDataTable::Id id() const {
        
        return HeapGraphObjectDataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      HeapGraphObjectDataTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const HeapGraphObjectDataTable* table) : table_(table) {
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
      HeapGraphObjectDataTable::Id id() const {
        
        return HeapGraphObjectDataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const HeapGraphObjectDataTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<uint32_t> _field_set_id = {}, std::optional<StringPool::Id> _value_string = {}, std::optional<StringPool::Id> _array_element_type = {}, std::optional<uint32_t> _array_element_count = {}, std::optional<uint32_t> _array_data_id = {}, std::optional<int64_t> _array_data_hash = {}) : field_set_id(std::move(_field_set_id)), value_string(std::move(_value_string)), array_element_type(std::move(_array_element_type)), array_element_count(std::move(_array_element_count)), array_data_id(std::move(_array_data_id)), array_data_hash(std::move(_array_data_hash)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(field_set_id, other.field_set_id) && std::equal_to<>()(value_string, other.value_string) && std::equal_to<>()(array_element_type, other.array_element_type) && std::equal_to<>()(array_element_count, other.array_element_count) && std::equal_to<>()(array_data_id, other.array_data_id) && std::equal_to<>()(array_data_hash, other.array_data_hash);
    }

        std::optional<uint32_t> field_set_id;
    std::optional<StringPool::Id> value_string;
    std::optional<StringPool::Id> array_element_type;
    std::optional<uint32_t> array_element_count;
    std::optional<uint32_t> array_data_id;
    std::optional<int64_t> array_data_hash;
  };

  explicit HeapGraphObjectDataTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.field_set_id, row.value_string, row.array_element_type, row.array_element_count, row.array_data_id, row.array_data_hash);
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
    return "__intrinsic_heap_graph_object_data";
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
static_assert(sizeof(HeapGraphObjectDataTable) == sizeof(dataframe::Dataframe));



class HeapGraphPrimitiveTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","field_set_id","field_name","field_type","bool_value","byte_value","char_value","short_value","int_value","long_value","float_value","double_value"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::SetIdSorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = HeapGraphPrimitiveTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(HeapGraphPrimitiveTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const HeapGraphPrimitiveTable& table) const {
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
    static constexpr uint32_t field_set_id = 1;
    static constexpr uint32_t field_name = 2;
    static constexpr uint32_t field_type = 3;
    static constexpr uint32_t bool_value = 4;
    static constexpr uint32_t byte_value = 5;
    static constexpr uint32_t char_value = 6;
    static constexpr uint32_t short_value = 7;
    static constexpr uint32_t int_value = 8;
    static constexpr uint32_t long_value = 9;
    static constexpr uint32_t float_value = 10;
    static constexpr uint32_t double_value = 11;
  };
  struct RowReference {
   public:
    explicit RowReference(HeapGraphPrimitiveTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    HeapGraphPrimitiveTable::Id id() const {
        
        return HeapGraphPrimitiveTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    HeapGraphPrimitiveTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const HeapGraphPrimitiveTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    HeapGraphPrimitiveTable::Id id() const {
        
        return HeapGraphPrimitiveTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const HeapGraphPrimitiveTable* table_;
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
    HeapGraphPrimitiveTable::Id id() const {
        
        return HeapGraphPrimitiveTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    HeapGraphPrimitiveTable::Id id() const {
        
        return HeapGraphPrimitiveTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(HeapGraphPrimitiveTable* table) : table_(table) {
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
      HeapGraphPrimitiveTable::Id id() const {
        
        return HeapGraphPrimitiveTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      HeapGraphPrimitiveTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const HeapGraphPrimitiveTable* table) : table_(table) {
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
      HeapGraphPrimitiveTable::Id id() const {
        
        return HeapGraphPrimitiveTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const HeapGraphPrimitiveTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _field_set_id = {}, StringPool::Id _field_name = {}, StringPool::Id _field_type = {}, std::optional<uint32_t> _bool_value = {}, std::optional<int64_t> _byte_value = {}, std::optional<int64_t> _char_value = {}, std::optional<int64_t> _short_value = {}, std::optional<int64_t> _int_value = {}, std::optional<int64_t> _long_value = {}, std::optional<double> _float_value = {}, std::optional<double> _double_value = {}) : field_set_id(std::move(_field_set_id)), field_name(std::move(_field_name)), field_type(std::move(_field_type)), bool_value(std::move(_bool_value)), byte_value(std::move(_byte_value)), char_value(std::move(_char_value)), short_value(std::move(_short_value)), int_value(std::move(_int_value)), long_value(std::move(_long_value)), float_value(std::move(_float_value)), double_value(std::move(_double_value)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(field_set_id, other.field_set_id) && std::equal_to<>()(field_name, other.field_name) && std::equal_to<>()(field_type, other.field_type) && std::equal_to<>()(bool_value, other.bool_value) && std::equal_to<>()(byte_value, other.byte_value) && std::equal_to<>()(char_value, other.char_value) && std::equal_to<>()(short_value, other.short_value) && std::equal_to<>()(int_value, other.int_value) && std::equal_to<>()(long_value, other.long_value) && std::equal_to<>()(float_value, other.float_value) && std::equal_to<>()(double_value, other.double_value);
    }

        uint32_t field_set_id;
    StringPool::Id field_name;
    StringPool::Id field_type;
    std::optional<uint32_t> bool_value;
    std::optional<int64_t> byte_value;
    std::optional<int64_t> char_value;
    std::optional<int64_t> short_value;
    std::optional<int64_t> int_value;
    std::optional<int64_t> long_value;
    std::optional<double> float_value;
    std::optional<double> double_value;
  };

  explicit HeapGraphPrimitiveTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.field_set_id, std::make_optional(row.field_name), std::make_optional(row.field_type), row.bool_value, row.byte_value, row.char_value, row.short_value, row.int_value, row.long_value, row.float_value, row.double_value);
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
    return "__intrinsic_heap_graph_primitive";
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
static_assert(sizeof(HeapGraphPrimitiveTable) == sizeof(dataframe::Dataframe));



class HeapGraphObjectTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","upid","graph_sample_ts","self_size","native_size","reference_set_id","reachable","heap_type","type_id","root_type","root_distance","object_data_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = HeapGraphObjectTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(HeapGraphObjectTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const HeapGraphObjectTable& table) const {
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
    static constexpr uint32_t upid = 1;
    static constexpr uint32_t graph_sample_ts = 2;
    static constexpr uint32_t self_size = 3;
    static constexpr uint32_t native_size = 4;
    static constexpr uint32_t reference_set_id = 5;
    static constexpr uint32_t reachable = 6;
    static constexpr uint32_t heap_type = 7;
    static constexpr uint32_t type_id = 8;
    static constexpr uint32_t root_type = 9;
    static constexpr uint32_t root_distance = 10;
    static constexpr uint32_t object_data_id = 11;
  };
  struct RowReference {
   public:
    explicit RowReference(HeapGraphObjectTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    HeapGraphObjectTable::Id id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t graph_sample_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::graph_sample_ts>(kSpec, row_);
    }
        int64_t self_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::self_size>(kSpec, row_);
    }
        int64_t native_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::native_size>(kSpec, row_);
    }
        std::optional<uint32_t> reference_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, row_);
    }
        int32_t reachable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reachable>(kSpec, row_);
    }
          std::optional<StringPool::Id> heap_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::heap_type>(kSpec, row_);
      }
          HeapGraphClassTable::Id type_id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::type_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> root_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_type>(kSpec, row_);
      }
        int32_t root_distance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_distance>(kSpec, row_);
    }
        std::optional<uint32_t> object_data_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::object_data_id>(kSpec, row_);
    }
    void set_self_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::self_size>(kSpec, row_, res);
    }
        void set_native_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::native_size>(kSpec, row_, res);
    }
        void set_reference_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, row_, res);
    }
        void set_reachable(int32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::reachable>(kSpec, row_, res);
    }
          void set_heap_type(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::heap_type>(kSpec, row_, res);
    }
          void set_type_id(HeapGraphClassTable::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::type_id>(kSpec, row_, res.value);
      }
          void set_root_type(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::root_type>(kSpec, row_, res);
    }
        void set_root_distance(int32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::root_distance>(kSpec, row_, res);
    }
        void set_object_data_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::object_data_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    HeapGraphObjectTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const HeapGraphObjectTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    HeapGraphObjectTable::Id id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t graph_sample_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::graph_sample_ts>(kSpec, row_);
    }
        int64_t self_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::self_size>(kSpec, row_);
    }
        int64_t native_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::native_size>(kSpec, row_);
    }
        std::optional<uint32_t> reference_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, row_);
    }
        int32_t reachable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reachable>(kSpec, row_);
    }
          std::optional<StringPool::Id> heap_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::heap_type>(kSpec, row_);
      }
          HeapGraphClassTable::Id type_id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::type_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> root_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_type>(kSpec, row_);
      }
        int32_t root_distance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_distance>(kSpec, row_);
    }
        std::optional<uint32_t> object_data_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::object_data_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const HeapGraphObjectTable* table_;
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
    HeapGraphObjectTable::Id id() const {
        
        return HeapGraphObjectTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t graph_sample_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::graph_sample_ts>(kSpec);
    }
    int64_t self_size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::self_size>(kSpec);
    }
    int64_t native_size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::native_size>(kSpec);
    }
    std::optional<uint32_t> reference_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::reference_set_id>(kSpec);
    }
    int32_t reachable() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::reachable>(kSpec);
    }
      std::optional<StringPool::Id> heap_type() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::heap_type>(kSpec);
      }
      HeapGraphClassTable::Id type_id() const {
        
        return HeapGraphClassTable::Id{cursor_.GetCellUnchecked<ColumnIndex::type_id>(kSpec)};
      }
      std::optional<StringPool::Id> root_type() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::root_type>(kSpec);
      }
    int32_t root_distance() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::root_distance>(kSpec);
    }
    std::optional<uint32_t> object_data_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::object_data_id>(kSpec);
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

    HeapGraphObjectTable::Id id() const {
        
        return HeapGraphObjectTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t graph_sample_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::graph_sample_ts>(kSpec);
    }
    int64_t self_size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::self_size>(kSpec);
    }
    int64_t native_size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::native_size>(kSpec);
    }
    std::optional<uint32_t> reference_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::reference_set_id>(kSpec);
    }
    int32_t reachable() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::reachable>(kSpec);
    }
      std::optional<StringPool::Id> heap_type() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::heap_type>(kSpec);
      }
      HeapGraphClassTable::Id type_id() const {
        
        return HeapGraphClassTable::Id{cursor_.GetCellUnchecked<ColumnIndex::type_id>(kSpec)};
      }
      std::optional<StringPool::Id> root_type() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::root_type>(kSpec);
      }
    int32_t root_distance() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::root_distance>(kSpec);
    }
    std::optional<uint32_t> object_data_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::object_data_id>(kSpec);
    }
    void set_self_size(int64_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::self_size>(kSpec, res);
    }
    void set_native_size(int64_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::native_size>(kSpec, res);
    }
    void set_reference_set_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, res);
    }
    void set_reachable(int32_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::reachable>(kSpec, res);
    }
      void set_heap_type(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::heap_type>(kSpec, res);
    }
      void set_type_id(HeapGraphClassTable::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::type_id>(kSpec, res.value);
      }
      void set_root_type(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::root_type>(kSpec, res);
    }
    void set_root_distance(int32_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::root_distance>(kSpec, res);
    }
    void set_object_data_id(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::object_data_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(HeapGraphObjectTable* table) : table_(table) {
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
      HeapGraphObjectTable::Id id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t graph_sample_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::graph_sample_ts>(kSpec, row_);
    }
        int64_t self_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::self_size>(kSpec, row_);
    }
        int64_t native_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::native_size>(kSpec, row_);
    }
        std::optional<uint32_t> reference_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, row_);
    }
        int32_t reachable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reachable>(kSpec, row_);
    }
          std::optional<StringPool::Id> heap_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::heap_type>(kSpec, row_);
      }
          HeapGraphClassTable::Id type_id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::type_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> root_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_type>(kSpec, row_);
      }
        int32_t root_distance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_distance>(kSpec, row_);
    }
        std::optional<uint32_t> object_data_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::object_data_id>(kSpec, row_);
    }
      void set_self_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::self_size>(kSpec, row_, res);
    }
        void set_native_size(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::native_size>(kSpec, row_, res);
    }
        void set_reference_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, row_, res);
    }
        void set_reachable(int32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::reachable>(kSpec, row_, res);
    }
          void set_heap_type(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::heap_type>(kSpec, row_, res);
    }
          void set_type_id(HeapGraphClassTable::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::type_id>(kSpec, row_, res.value);
      }
          void set_root_type(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::root_type>(kSpec, row_, res);
    }
        void set_root_distance(int32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::root_distance>(kSpec, row_, res);
    }
        void set_object_data_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::object_data_id>(kSpec, row_, res);
    }

    private:
      HeapGraphObjectTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const HeapGraphObjectTable* table) : table_(table) {
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
      HeapGraphObjectTable::Id id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t graph_sample_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::graph_sample_ts>(kSpec, row_);
    }
        int64_t self_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::self_size>(kSpec, row_);
    }
        int64_t native_size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::native_size>(kSpec, row_);
    }
        std::optional<uint32_t> reference_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reference_set_id>(kSpec, row_);
    }
        int32_t reachable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::reachable>(kSpec, row_);
    }
          std::optional<StringPool::Id> heap_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::heap_type>(kSpec, row_);
      }
          HeapGraphClassTable::Id type_id() const {
        
        return HeapGraphClassTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::type_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> root_type() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_type>(kSpec, row_);
      }
        int32_t root_distance() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::root_distance>(kSpec, row_);
    }
        std::optional<uint32_t> object_data_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::object_data_id>(kSpec, row_);
    }

    private:
      const HeapGraphObjectTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _upid = {}, int64_t _graph_sample_ts = {}, int64_t _self_size = {}, int64_t _native_size = {}, std::optional<uint32_t> _reference_set_id = {}, int32_t _reachable = {}, std::optional<StringPool::Id> _heap_type = {}, HeapGraphClassTable::Id _type_id = {}, std::optional<StringPool::Id> _root_type = {}, int32_t _root_distance = {}, std::optional<uint32_t> _object_data_id = {}) : upid(std::move(_upid)), graph_sample_ts(std::move(_graph_sample_ts)), self_size(std::move(_self_size)), native_size(std::move(_native_size)), reference_set_id(std::move(_reference_set_id)), reachable(std::move(_reachable)), heap_type(std::move(_heap_type)), type_id(std::move(_type_id)), root_type(std::move(_root_type)), root_distance(std::move(_root_distance)), object_data_id(std::move(_object_data_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(upid, other.upid) && std::equal_to<>()(graph_sample_ts, other.graph_sample_ts) && std::equal_to<>()(self_size, other.self_size) && std::equal_to<>()(native_size, other.native_size) && std::equal_to<>()(reference_set_id, other.reference_set_id) && std::equal_to<>()(reachable, other.reachable) && std::equal_to<>()(heap_type, other.heap_type) && std::equal_to<>()(type_id, other.type_id) && std::equal_to<>()(root_type, other.root_type) && std::equal_to<>()(root_distance, other.root_distance) && std::equal_to<>()(object_data_id, other.object_data_id);
    }

        uint32_t upid;
    int64_t graph_sample_ts;
    int64_t self_size;
    int64_t native_size;
    std::optional<uint32_t> reference_set_id;
    int32_t reachable;
    std::optional<StringPool::Id> heap_type;
    HeapGraphClassTable::Id type_id;
    std::optional<StringPool::Id> root_type;
    int32_t root_distance;
    std::optional<uint32_t> object_data_id;
  };

  explicit HeapGraphObjectTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.upid, row.graph_sample_ts, row.self_size, row.native_size, row.reference_set_id, row.reachable, row.heap_type, row.type_id.value, row.root_type, row.root_distance, row.object_data_id);
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
    return "__intrinsic_heap_graph_object";
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
static_assert(sizeof(HeapGraphObjectTable) == sizeof(dataframe::Dataframe));



class HeapGraphReferenceTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","reference_set_id","owner_id","owned_id","field_name","field_type_name","deobfuscated_field_name"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::SetIdSorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = HeapGraphReferenceTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(HeapGraphReferenceTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const HeapGraphReferenceTable& table) const {
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
    static constexpr uint32_t reference_set_id = 1;
    static constexpr uint32_t owner_id = 2;
    static constexpr uint32_t owned_id = 3;
    static constexpr uint32_t field_name = 4;
    static constexpr uint32_t field_type_name = 5;
    static constexpr uint32_t deobfuscated_field_name = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(HeapGraphReferenceTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    HeapGraphReferenceTable::Id id() const {
        
        return HeapGraphReferenceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          HeapGraphObjectTable::Id owner_id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::owner_id>(kSpec, row_)};
      }
          std::optional<HeapGraphObjectTable::Id> owned_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::owned_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphObjectTable::Id{*res}) : std::nullopt;
      }
          StringPool::Id field_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id field_type_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_type_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_field_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, row_);
      }
    void set_field_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::field_name>(kSpec, row_, std::make_optional(res));
    }
          void set_field_type_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::field_type_name>(kSpec, row_, std::make_optional(res));
    }
          void set_deobfuscated_field_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    HeapGraphReferenceTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const HeapGraphReferenceTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    HeapGraphReferenceTable::Id id() const {
        
        return HeapGraphReferenceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          HeapGraphObjectTable::Id owner_id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::owner_id>(kSpec, row_)};
      }
          std::optional<HeapGraphObjectTable::Id> owned_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::owned_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphObjectTable::Id{*res}) : std::nullopt;
      }
          StringPool::Id field_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id field_type_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_type_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_field_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, row_);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const HeapGraphReferenceTable* table_;
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
    HeapGraphReferenceTable::Id id() const {
        
        return HeapGraphReferenceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      HeapGraphObjectTable::Id owner_id() const {
        
        return HeapGraphObjectTable::Id{cursor_.GetCellUnchecked<ColumnIndex::owner_id>(kSpec)};
      }
      std::optional<HeapGraphObjectTable::Id> owned_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::owned_id>(kSpec);
        return res ? std::make_optional(HeapGraphObjectTable::Id{*res}) : std::nullopt;
      }
      StringPool::Id field_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::field_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id field_type_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::field_type_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      std::optional<StringPool::Id> deobfuscated_field_name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec);
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

    HeapGraphReferenceTable::Id id() const {
        
        return HeapGraphReferenceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      HeapGraphObjectTable::Id owner_id() const {
        
        return HeapGraphObjectTable::Id{cursor_.GetCellUnchecked<ColumnIndex::owner_id>(kSpec)};
      }
      std::optional<HeapGraphObjectTable::Id> owned_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::owned_id>(kSpec);
        return res ? std::make_optional(HeapGraphObjectTable::Id{*res}) : std::nullopt;
      }
      StringPool::Id field_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::field_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id field_type_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::field_type_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      std::optional<StringPool::Id> deobfuscated_field_name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec);
      }
    void set_field_name(StringPool::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::field_name>(kSpec, std::make_optional(res));
    }
      void set_field_type_name(StringPool::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::field_type_name>(kSpec, std::make_optional(res));
    }
      void set_deobfuscated_field_name(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(HeapGraphReferenceTable* table) : table_(table) {
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
      HeapGraphReferenceTable::Id id() const {
        
        return HeapGraphReferenceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          HeapGraphObjectTable::Id owner_id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::owner_id>(kSpec, row_)};
      }
          std::optional<HeapGraphObjectTable::Id> owned_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::owned_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphObjectTable::Id{*res}) : std::nullopt;
      }
          StringPool::Id field_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id field_type_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_type_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_field_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, row_);
      }
      void set_field_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::field_name>(kSpec, row_, std::make_optional(res));
    }
          void set_field_type_name(StringPool::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::field_type_name>(kSpec, row_, std::make_optional(res));
    }
          void set_deobfuscated_field_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, row_, res);
    }

    private:
      HeapGraphReferenceTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const HeapGraphReferenceTable* table) : table_(table) {
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
      HeapGraphReferenceTable::Id id() const {
        
        return HeapGraphReferenceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          HeapGraphObjectTable::Id owner_id() const {
        
        return HeapGraphObjectTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::owner_id>(kSpec, row_)};
      }
          std::optional<HeapGraphObjectTable::Id> owned_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::owned_id>(kSpec, row_);
        return res ? std::make_optional(HeapGraphObjectTable::Id{*res}) : std::nullopt;
      }
          StringPool::Id field_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id field_type_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::field_type_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> deobfuscated_field_name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::deobfuscated_field_name>(kSpec, row_);
      }

    private:
      const HeapGraphReferenceTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _reference_set_id = {}, HeapGraphObjectTable::Id _owner_id = {}, std::optional<HeapGraphObjectTable::Id> _owned_id = {}, StringPool::Id _field_name = {}, StringPool::Id _field_type_name = {}, std::optional<StringPool::Id> _deobfuscated_field_name = {}) : reference_set_id(std::move(_reference_set_id)), owner_id(std::move(_owner_id)), owned_id(std::move(_owned_id)), field_name(std::move(_field_name)), field_type_name(std::move(_field_type_name)), deobfuscated_field_name(std::move(_deobfuscated_field_name)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(reference_set_id, other.reference_set_id) && std::equal_to<>()(owner_id, other.owner_id) && std::equal_to<>()(owned_id, other.owned_id) && std::equal_to<>()(field_name, other.field_name) && std::equal_to<>()(field_type_name, other.field_type_name) && std::equal_to<>()(deobfuscated_field_name, other.deobfuscated_field_name);
    }

        uint32_t reference_set_id;
    HeapGraphObjectTable::Id owner_id;
    std::optional<HeapGraphObjectTable::Id> owned_id;
    StringPool::Id field_name;
    StringPool::Id field_type_name;
    std::optional<StringPool::Id> deobfuscated_field_name;
  };

  explicit HeapGraphReferenceTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.reference_set_id, row.owner_id.value, row.owned_id ? std::make_optional(row.owned_id->value) : std::nullopt, std::make_optional(row.field_name), std::make_optional(row.field_type_name), row.deobfuscated_field_name);
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
    return "__intrinsic_heap_graph_reference";
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
static_assert(sizeof(HeapGraphReferenceTable) == sizeof(dataframe::Dataframe));



class HeapProfileAllocationTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","upid","heap_name","callsite_id","count","size"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = HeapProfileAllocationTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(HeapProfileAllocationTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const HeapProfileAllocationTable& table) const {
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
    static constexpr uint32_t upid = 2;
    static constexpr uint32_t heap_name = 3;
    static constexpr uint32_t callsite_id = 4;
    static constexpr uint32_t count = 5;
    static constexpr uint32_t size = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(HeapProfileAllocationTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    HeapProfileAllocationTable::Id id() const {
        
        return HeapProfileAllocationTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        int64_t count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    HeapProfileAllocationTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const HeapProfileAllocationTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    HeapProfileAllocationTable::Id id() const {
        
        return HeapProfileAllocationTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        int64_t count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const HeapProfileAllocationTable* table_;
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
    HeapProfileAllocationTable::Id id() const {
        
        return HeapProfileAllocationTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    uint32_t upid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
      StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec)};
      }
    int64_t count() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::count>(kSpec);
    }
    int64_t size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
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

    HeapProfileAllocationTable::Id id() const {
        
        return HeapProfileAllocationTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    uint32_t upid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
      StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec)};
      }
    int64_t count() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::count>(kSpec);
    }
    int64_t size() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(HeapProfileAllocationTable* table) : table_(table) {
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
      HeapProfileAllocationTable::Id id() const {
        
        return HeapProfileAllocationTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        int64_t count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
      

    private:
      HeapProfileAllocationTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const HeapProfileAllocationTable* table) : table_(table) {
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
      HeapProfileAllocationTable::Id id() const {
        
        return HeapProfileAllocationTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
          StackProfileCallsiteTable::Id callsite_id() const {
        
        return StackProfileCallsiteTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_)};
      }
        int64_t count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::count>(kSpec, row_);
    }
        int64_t size() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }

    private:
      const HeapProfileAllocationTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, uint32_t _upid = {}, StringPool::Id _heap_name = {}, StackProfileCallsiteTable::Id _callsite_id = {}, int64_t _count = {}, int64_t _size = {}) : ts(std::move(_ts)), upid(std::move(_upid)), heap_name(std::move(_heap_name)), callsite_id(std::move(_callsite_id)), count(std::move(_count)), size(std::move(_size)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(upid, other.upid) && std::equal_to<>()(heap_name, other.heap_name) && std::equal_to<>()(callsite_id, other.callsite_id) && std::equal_to<>()(count, other.count) && std::equal_to<>()(size, other.size);
    }

        int64_t ts;
    uint32_t upid;
    StringPool::Id heap_name;
    StackProfileCallsiteTable::Id callsite_id;
    int64_t count;
    int64_t size;
  };

  explicit HeapProfileAllocationTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.upid, std::make_optional(row.heap_name), row.callsite_id.value, row.count, row.size);
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
    return "__intrinsic_heap_profile_allocation";
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
static_assert(sizeof(HeapProfileAllocationTable) == sizeof(dataframe::Dataframe));



class InstrumentsSampleTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","utid","callsite_id","cpu"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = InstrumentsSampleTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(InstrumentsSampleTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const InstrumentsSampleTable& table) const {
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
    static constexpr uint32_t callsite_id = 3;
    static constexpr uint32_t cpu = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(InstrumentsSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    InstrumentsSampleTable::Id id() const {
        
        return InstrumentsSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    InstrumentsSampleTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const InstrumentsSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    InstrumentsSampleTable::Id id() const {
        
        return InstrumentsSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const InstrumentsSampleTable* table_;
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
    InstrumentsSampleTable::Id id() const {
        
        return InstrumentsSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
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

    InstrumentsSampleTable::Id id() const {
        
        return InstrumentsSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(InstrumentsSampleTable* table) : table_(table) {
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
      InstrumentsSampleTable::Id id() const {
        
        return InstrumentsSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
      

    private:
      InstrumentsSampleTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const InstrumentsSampleTable* table) : table_(table) {
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
      InstrumentsSampleTable::Id id() const {
        
        return InstrumentsSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }

    private:
      const InstrumentsSampleTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, uint32_t _utid = {}, std::optional<StackProfileCallsiteTable::Id> _callsite_id = {}, std::optional<uint32_t> _cpu = {}) : ts(std::move(_ts)), utid(std::move(_utid)), callsite_id(std::move(_callsite_id)), cpu(std::move(_cpu)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(callsite_id, other.callsite_id) && std::equal_to<>()(cpu, other.cpu);
    }

        int64_t ts;
    uint32_t utid;
    std::optional<StackProfileCallsiteTable::Id> callsite_id;
    std::optional<uint32_t> cpu;
  };

  explicit InstrumentsSampleTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.utid, row.callsite_id ? std::make_optional(row.callsite_id->value) : std::nullopt, row.cpu);
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
    return "__intrinsic_instruments_sample";
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
static_assert(sizeof(InstrumentsSampleTable) == sizeof(dataframe::Dataframe));



class PackageListTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","package_name","uid","debuggable","profileable_from_shell","version_code"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = PackageListTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(PackageListTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const PackageListTable& table) const {
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
    static constexpr uint32_t debuggable = 3;
    static constexpr uint32_t profileable_from_shell = 4;
    static constexpr uint32_t version_code = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(PackageListTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    PackageListTable::Id id() const {
        
        return PackageListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id package_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::package_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t uid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int32_t debuggable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::debuggable>(kSpec, row_);
    }
        int32_t profileable_from_shell() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::profileable_from_shell>(kSpec, row_);
    }
        int64_t version_code() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version_code>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    PackageListTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const PackageListTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    PackageListTable::Id id() const {
        
        return PackageListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id package_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::package_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t uid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int32_t debuggable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::debuggable>(kSpec, row_);
    }
        int32_t profileable_from_shell() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::profileable_from_shell>(kSpec, row_);
    }
        int64_t version_code() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version_code>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const PackageListTable* table_;
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
    PackageListTable::Id id() const {
        
        return PackageListTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id package_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::package_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t uid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::uid>(kSpec);
    }
    int32_t debuggable() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::debuggable>(kSpec);
    }
    int32_t profileable_from_shell() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::profileable_from_shell>(kSpec);
    }
    int64_t version_code() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::version_code>(kSpec);
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

    PackageListTable::Id id() const {
        
        return PackageListTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id package_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::package_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t uid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::uid>(kSpec);
    }
    int32_t debuggable() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::debuggable>(kSpec);
    }
    int32_t profileable_from_shell() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::profileable_from_shell>(kSpec);
    }
    int64_t version_code() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::version_code>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(PackageListTable* table) : table_(table) {
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
      PackageListTable::Id id() const {
        
        return PackageListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id package_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::package_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t uid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int32_t debuggable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::debuggable>(kSpec, row_);
    }
        int32_t profileable_from_shell() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::profileable_from_shell>(kSpec, row_);
    }
        int64_t version_code() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version_code>(kSpec, row_);
    }
      

    private:
      PackageListTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const PackageListTable* table) : table_(table) {
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
      PackageListTable::Id id() const {
        
        return PackageListTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id package_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::package_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t uid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        int32_t debuggable() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::debuggable>(kSpec, row_);
    }
        int32_t profileable_from_shell() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::profileable_from_shell>(kSpec, row_);
    }
        int64_t version_code() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version_code>(kSpec, row_);
    }

    private:
      const PackageListTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _package_name = {}, int64_t _uid = {}, int32_t _debuggable = {}, int32_t _profileable_from_shell = {}, int64_t _version_code = {}) : package_name(std::move(_package_name)), uid(std::move(_uid)), debuggable(std::move(_debuggable)), profileable_from_shell(std::move(_profileable_from_shell)), version_code(std::move(_version_code)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(package_name, other.package_name) && std::equal_to<>()(uid, other.uid) && std::equal_to<>()(debuggable, other.debuggable) && std::equal_to<>()(profileable_from_shell, other.profileable_from_shell) && std::equal_to<>()(version_code, other.version_code);
    }

        StringPool::Id package_name;
    int64_t uid;
    int32_t debuggable;
    int32_t profileable_from_shell;
    int64_t version_code;
  };

  explicit PackageListTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.package_name), row.uid, row.debuggable, row.profileable_from_shell, row.version_code);
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
    return "__intrinsic_package_list";
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
static_assert(sizeof(PackageListTable) == sizeof(dataframe::Dataframe));



class PerfCounterSetTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","perf_counter_set_id","counter_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::SetIdSorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = PerfCounterSetTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(PerfCounterSetTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const PerfCounterSetTable& table) const {
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
    static constexpr uint32_t perf_counter_set_id = 1;
    static constexpr uint32_t counter_id = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(PerfCounterSetTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    PerfCounterSetTable::Id id() const {
        
        return PerfCounterSetTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t perf_counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, row_);
    }
          CounterTable::Id counter_id() const {
        
        return CounterTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_id>(kSpec, row_)};
      }
    void set_perf_counter_set_id(uint32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, row_, res);
    }
          void set_counter_id(CounterTable::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::counter_id>(kSpec, row_, res.value);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    PerfCounterSetTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const PerfCounterSetTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    PerfCounterSetTable::Id id() const {
        
        return PerfCounterSetTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t perf_counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, row_);
    }
          CounterTable::Id counter_id() const {
        
        return CounterTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const PerfCounterSetTable* table_;
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
    PerfCounterSetTable::Id id() const {
        
        return PerfCounterSetTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t perf_counter_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec);
    }
      CounterTable::Id counter_id() const {
        
        return CounterTable::Id{cursor_.GetCellUnchecked<ColumnIndex::counter_id>(kSpec)};
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

    PerfCounterSetTable::Id id() const {
        
        return PerfCounterSetTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t perf_counter_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec);
    }
      CounterTable::Id counter_id() const {
        
        return CounterTable::Id{cursor_.GetCellUnchecked<ColumnIndex::counter_id>(kSpec)};
      }
    void set_perf_counter_set_id(uint32_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, res);
    }
      void set_counter_id(CounterTable::Id res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::counter_id>(kSpec, res.value);
      }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(PerfCounterSetTable* table) : table_(table) {
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
      PerfCounterSetTable::Id id() const {
        
        return PerfCounterSetTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t perf_counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, row_);
    }
          CounterTable::Id counter_id() const {
        
        return CounterTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_id>(kSpec, row_)};
      }
      void set_perf_counter_set_id(uint32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, row_, res);
    }
          void set_counter_id(CounterTable::Id res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::counter_id>(kSpec, row_, res.value);
      }

    private:
      PerfCounterSetTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const PerfCounterSetTable* table) : table_(table) {
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
      PerfCounterSetTable::Id id() const {
        
        return PerfCounterSetTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t perf_counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::perf_counter_set_id>(kSpec, row_);
    }
          CounterTable::Id counter_id() const {
        
        return CounterTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_id>(kSpec, row_)};
      }

    private:
      const PerfCounterSetTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _perf_counter_set_id = {}, CounterTable::Id _counter_id = {}) : perf_counter_set_id(std::move(_perf_counter_set_id)), counter_id(std::move(_counter_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(perf_counter_set_id, other.perf_counter_set_id) && std::equal_to<>()(counter_id, other.counter_id);
    }

        uint32_t perf_counter_set_id;
    CounterTable::Id counter_id;
  };

  explicit PerfCounterSetTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.perf_counter_set_id, row.counter_id.value);
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
    return "__intrinsic_perf_counter_set";
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
static_assert(sizeof(PerfCounterSetTable) == sizeof(dataframe::Dataframe));



class PerfSessionTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","cmdline"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = PerfSessionTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(PerfSessionTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const PerfSessionTable& table) const {
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
    static constexpr uint32_t cmdline = 1;
  };
  struct RowReference {
   public:
    explicit RowReference(PerfSessionTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    PerfSessionTable::Id id() const {
        
        return PerfSessionTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> cmdline() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
    void set_cmdline(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    PerfSessionTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const PerfSessionTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    PerfSessionTable::Id id() const {
        
        return PerfSessionTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> cmdline() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const PerfSessionTable* table_;
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
    PerfSessionTable::Id id() const {
        
        return PerfSessionTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<StringPool::Id> cmdline() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::cmdline>(kSpec);
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

    PerfSessionTable::Id id() const {
        
        return PerfSessionTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<StringPool::Id> cmdline() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::cmdline>(kSpec);
      }
    void set_cmdline(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::cmdline>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(PerfSessionTable* table) : table_(table) {
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
      PerfSessionTable::Id id() const {
        
        return PerfSessionTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> cmdline() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
      void set_cmdline(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_, res);
    }

    private:
      PerfSessionTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const PerfSessionTable* table) : table_(table) {
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
      PerfSessionTable::Id id() const {
        
        return PerfSessionTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> cmdline() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }

    private:
      const PerfSessionTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<StringPool::Id> _cmdline = {}) : cmdline(std::move(_cmdline)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(cmdline, other.cmdline);
    }

        std::optional<StringPool::Id> cmdline;
  };

  explicit PerfSessionTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.cmdline);
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
    return "__intrinsic_perf_session";
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
static_assert(sizeof(PerfSessionTable) == sizeof(dataframe::Dataframe));



class PerfSampleTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","utid","cpu","cpu_mode","callsite_id","unwind_error","perf_session_id","counter_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = PerfSampleTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(PerfSampleTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const PerfSampleTable& table) const {
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
    static constexpr uint32_t cpu = 3;
    static constexpr uint32_t cpu_mode = 4;
    static constexpr uint32_t callsite_id = 5;
    static constexpr uint32_t unwind_error = 6;
    static constexpr uint32_t perf_session_id = 7;
    static constexpr uint32_t counter_set_id = 8;
  };
  struct RowReference {
   public:
    explicit RowReference(PerfSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    PerfSampleTable::Id id() const {
        
        return PerfSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, row_);
    }
    void set_counter_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    PerfSampleTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const PerfSampleTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    PerfSampleTable::Id id() const {
        
        return PerfSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const PerfSampleTable* table_;
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
    PerfSampleTable::Id id() const {
        
        return PerfSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    uint32_t utid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec);
    }
      std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
    std::optional<uint32_t> counter_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::counter_set_id>(kSpec);
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

    PerfSampleTable::Id id() const {
        
        return PerfSampleTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    uint32_t utid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec);
    }
      std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
    std::optional<uint32_t> counter_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::counter_set_id>(kSpec);
    }
    void set_counter_set_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(PerfSampleTable* table) : table_(table) {
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
      PerfSampleTable::Id id() const {
        
        return PerfSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, row_);
    }
      void set_counter_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, row_, res);
    }

    private:
      PerfSampleTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const PerfSampleTable* table) : table_(table) {
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
      PerfSampleTable::Id id() const {
        
        return PerfSampleTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        uint32_t utid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_);
    }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> counter_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::counter_set_id>(kSpec, row_);
    }

    private:
      const PerfSampleTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, uint32_t _utid = {}, std::optional<uint32_t> _cpu = {}, StringPool::Id _cpu_mode = {}, std::optional<StackProfileCallsiteTable::Id> _callsite_id = {}, std::optional<StringPool::Id> _unwind_error = {}, PerfSessionTable::Id _perf_session_id = {}, std::optional<uint32_t> _counter_set_id = {}) : ts(std::move(_ts)), utid(std::move(_utid)), cpu(std::move(_cpu)), cpu_mode(std::move(_cpu_mode)), callsite_id(std::move(_callsite_id)), unwind_error(std::move(_unwind_error)), perf_session_id(std::move(_perf_session_id)), counter_set_id(std::move(_counter_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(cpu, other.cpu) && std::equal_to<>()(cpu_mode, other.cpu_mode) && std::equal_to<>()(callsite_id, other.callsite_id) && std::equal_to<>()(unwind_error, other.unwind_error) && std::equal_to<>()(perf_session_id, other.perf_session_id) && std::equal_to<>()(counter_set_id, other.counter_set_id);
    }

        int64_t ts;
    uint32_t utid;
    std::optional<uint32_t> cpu;
    StringPool::Id cpu_mode;
    std::optional<StackProfileCallsiteTable::Id> callsite_id;
    std::optional<StringPool::Id> unwind_error;
    PerfSessionTable::Id perf_session_id;
    std::optional<uint32_t> counter_set_id;
  };

  explicit PerfSampleTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.utid, row.cpu, std::make_optional(row.cpu_mode), row.callsite_id ? std::make_optional(row.callsite_id->value) : std::nullopt, row.unwind_error, row.perf_session_id.value, row.counter_set_id);
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
    return "__intrinsic_perf_sample";
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
static_assert(sizeof(PerfSampleTable) == sizeof(dataframe::Dataframe));



class ProfilerSmapsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","upid","ts","path","size_kb","private_dirty_kb","swap_kb","file_name","start_address","module_timestamp","module_debugid","module_debug_path","protection_flags","private_clean_resident_kb","shared_dirty_resident_kb","shared_clean_resident_kb","locked_kb","proportional_resident_kb"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ProfilerSmapsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ProfilerSmapsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ProfilerSmapsTable& table) const {
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
    static constexpr uint32_t upid = 1;
    static constexpr uint32_t ts = 2;
    static constexpr uint32_t path = 3;
    static constexpr uint32_t size_kb = 4;
    static constexpr uint32_t private_dirty_kb = 5;
    static constexpr uint32_t swap_kb = 6;
    static constexpr uint32_t file_name = 7;
    static constexpr uint32_t start_address = 8;
    static constexpr uint32_t module_timestamp = 9;
    static constexpr uint32_t module_debugid = 10;
    static constexpr uint32_t module_debug_path = 11;
    static constexpr uint32_t protection_flags = 12;
    static constexpr uint32_t private_clean_resident_kb = 13;
    static constexpr uint32_t shared_dirty_resident_kb = 14;
    static constexpr uint32_t shared_clean_resident_kb = 15;
    static constexpr uint32_t locked_kb = 16;
    static constexpr uint32_t proportional_resident_kb = 17;
  };
  struct RowReference {
   public:
    explicit RowReference(ProfilerSmapsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ProfilerSmapsTable::Id id() const {
        
        return ProfilerSmapsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t size_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size_kb>(kSpec, row_);
    }
        int64_t private_dirty_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_dirty_kb>(kSpec, row_);
    }
        int64_t swap_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::swap_kb>(kSpec, row_);
    }
          StringPool::Id file_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::file_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t start_address() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t module_timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_timestamp>(kSpec, row_);
    }
          StringPool::Id module_debugid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debugid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id module_debug_path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debug_path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t protection_flags() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::protection_flags>(kSpec, row_);
    }
        int64_t private_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_clean_resident_kb>(kSpec, row_);
    }
        int64_t shared_dirty_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_dirty_resident_kb>(kSpec, row_);
    }
        int64_t shared_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_clean_resident_kb>(kSpec, row_);
    }
        int64_t proportional_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::proportional_resident_kb>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ProfilerSmapsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ProfilerSmapsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ProfilerSmapsTable::Id id() const {
        
        return ProfilerSmapsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t size_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size_kb>(kSpec, row_);
    }
        int64_t private_dirty_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_dirty_kb>(kSpec, row_);
    }
        int64_t swap_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::swap_kb>(kSpec, row_);
    }
          StringPool::Id file_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::file_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t start_address() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t module_timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_timestamp>(kSpec, row_);
    }
          StringPool::Id module_debugid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debugid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id module_debug_path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debug_path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t protection_flags() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::protection_flags>(kSpec, row_);
    }
        int64_t private_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_clean_resident_kb>(kSpec, row_);
    }
        int64_t shared_dirty_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_dirty_resident_kb>(kSpec, row_);
    }
        int64_t shared_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_clean_resident_kb>(kSpec, row_);
    }
        int64_t proportional_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::proportional_resident_kb>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ProfilerSmapsTable* table_;
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
    ProfilerSmapsTable::Id id() const {
        
        return ProfilerSmapsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t upid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    int64_t size_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::size_kb>(kSpec);
    }
    int64_t private_dirty_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::private_dirty_kb>(kSpec);
    }
    int64_t swap_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::swap_kb>(kSpec);
    }
      StringPool::Id file_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::file_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t start_address() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start_address>(kSpec);
    }
    int64_t module_timestamp() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::module_timestamp>(kSpec);
    }
      StringPool::Id module_debugid() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::module_debugid>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id module_debug_path() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::module_debug_path>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t protection_flags() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::protection_flags>(kSpec);
    }
    int64_t private_clean_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::private_clean_resident_kb>(kSpec);
    }
    int64_t shared_dirty_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::shared_dirty_resident_kb>(kSpec);
    }
    int64_t shared_clean_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::shared_clean_resident_kb>(kSpec);
    }
    int64_t proportional_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::proportional_resident_kb>(kSpec);
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

    ProfilerSmapsTable::Id id() const {
        
        return ProfilerSmapsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t upid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
    }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    int64_t size_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::size_kb>(kSpec);
    }
    int64_t private_dirty_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::private_dirty_kb>(kSpec);
    }
    int64_t swap_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::swap_kb>(kSpec);
    }
      StringPool::Id file_name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::file_name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t start_address() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start_address>(kSpec);
    }
    int64_t module_timestamp() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::module_timestamp>(kSpec);
    }
      StringPool::Id module_debugid() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::module_debugid>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id module_debug_path() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::module_debug_path>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    int64_t protection_flags() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::protection_flags>(kSpec);
    }
    int64_t private_clean_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::private_clean_resident_kb>(kSpec);
    }
    int64_t shared_dirty_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::shared_dirty_resident_kb>(kSpec);
    }
    int64_t shared_clean_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::shared_clean_resident_kb>(kSpec);
    }
    int64_t proportional_resident_kb() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::proportional_resident_kb>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ProfilerSmapsTable* table) : table_(table) {
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
      ProfilerSmapsTable::Id id() const {
        
        return ProfilerSmapsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t size_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size_kb>(kSpec, row_);
    }
        int64_t private_dirty_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_dirty_kb>(kSpec, row_);
    }
        int64_t swap_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::swap_kb>(kSpec, row_);
    }
          StringPool::Id file_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::file_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t start_address() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t module_timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_timestamp>(kSpec, row_);
    }
          StringPool::Id module_debugid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debugid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id module_debug_path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debug_path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t protection_flags() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::protection_flags>(kSpec, row_);
    }
        int64_t private_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_clean_resident_kb>(kSpec, row_);
    }
        int64_t shared_dirty_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_dirty_resident_kb>(kSpec, row_);
    }
        int64_t shared_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_clean_resident_kb>(kSpec, row_);
    }
        int64_t proportional_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::proportional_resident_kb>(kSpec, row_);
    }
      

    private:
      ProfilerSmapsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ProfilerSmapsTable* table) : table_(table) {
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
      ProfilerSmapsTable::Id id() const {
        
        return ProfilerSmapsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t upid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
    }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t size_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size_kb>(kSpec, row_);
    }
        int64_t private_dirty_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_dirty_kb>(kSpec, row_);
    }
        int64_t swap_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::swap_kb>(kSpec, row_);
    }
          StringPool::Id file_name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::file_name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t start_address() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_address>(kSpec, row_);
    }
        int64_t module_timestamp() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_timestamp>(kSpec, row_);
    }
          StringPool::Id module_debugid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debugid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id module_debug_path() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::module_debug_path>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        int64_t protection_flags() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::protection_flags>(kSpec, row_);
    }
        int64_t private_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::private_clean_resident_kb>(kSpec, row_);
    }
        int64_t shared_dirty_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_dirty_resident_kb>(kSpec, row_);
    }
        int64_t shared_clean_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::shared_clean_resident_kb>(kSpec, row_);
    }
        int64_t proportional_resident_kb() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::proportional_resident_kb>(kSpec, row_);
    }

    private:
      const ProfilerSmapsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _upid = {}, int64_t _ts = {}, StringPool::Id _path = {}, int64_t _size_kb = {}, int64_t _private_dirty_kb = {}, int64_t _swap_kb = {}, StringPool::Id _file_name = {}, int64_t _start_address = {}, int64_t _module_timestamp = {}, StringPool::Id _module_debugid = {}, StringPool::Id _module_debug_path = {}, int64_t _protection_flags = {}, int64_t _private_clean_resident_kb = {}, int64_t _shared_dirty_resident_kb = {}, int64_t _shared_clean_resident_kb = {}, int64_t _locked_kb = {}, int64_t _proportional_resident_kb = {}) : upid(std::move(_upid)), ts(std::move(_ts)), path(std::move(_path)), size_kb(std::move(_size_kb)), private_dirty_kb(std::move(_private_dirty_kb)), swap_kb(std::move(_swap_kb)), file_name(std::move(_file_name)), start_address(std::move(_start_address)), module_timestamp(std::move(_module_timestamp)), module_debugid(std::move(_module_debugid)), module_debug_path(std::move(_module_debug_path)), protection_flags(std::move(_protection_flags)), private_clean_resident_kb(std::move(_private_clean_resident_kb)), shared_dirty_resident_kb(std::move(_shared_dirty_resident_kb)), shared_clean_resident_kb(std::move(_shared_clean_resident_kb)), locked_kb(std::move(_locked_kb)), proportional_resident_kb(std::move(_proportional_resident_kb)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(upid, other.upid) && std::equal_to<>()(ts, other.ts) && std::equal_to<>()(path, other.path) && std::equal_to<>()(size_kb, other.size_kb) && std::equal_to<>()(private_dirty_kb, other.private_dirty_kb) && std::equal_to<>()(swap_kb, other.swap_kb) && std::equal_to<>()(file_name, other.file_name) && std::equal_to<>()(start_address, other.start_address) && std::equal_to<>()(module_timestamp, other.module_timestamp) && std::equal_to<>()(module_debugid, other.module_debugid) && std::equal_to<>()(module_debug_path, other.module_debug_path) && std::equal_to<>()(protection_flags, other.protection_flags) && std::equal_to<>()(private_clean_resident_kb, other.private_clean_resident_kb) && std::equal_to<>()(shared_dirty_resident_kb, other.shared_dirty_resident_kb) && std::equal_to<>()(shared_clean_resident_kb, other.shared_clean_resident_kb) && std::equal_to<>()(locked_kb, other.locked_kb) && std::equal_to<>()(proportional_resident_kb, other.proportional_resident_kb);
    }

        uint32_t upid;
    int64_t ts;
    StringPool::Id path;
    int64_t size_kb;
    int64_t private_dirty_kb;
    int64_t swap_kb;
    StringPool::Id file_name;
    int64_t start_address;
    int64_t module_timestamp;
    StringPool::Id module_debugid;
    StringPool::Id module_debug_path;
    int64_t protection_flags;
    int64_t private_clean_resident_kb;
    int64_t shared_dirty_resident_kb;
    int64_t shared_clean_resident_kb;
    int64_t locked_kb;
    int64_t proportional_resident_kb;
  };

  explicit ProfilerSmapsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.upid, row.ts, std::make_optional(row.path), row.size_kb, row.private_dirty_kb, row.swap_kb, std::make_optional(row.file_name), row.start_address, row.module_timestamp, std::make_optional(row.module_debugid), std::make_optional(row.module_debug_path), row.protection_flags, row.private_clean_resident_kb, row.shared_dirty_resident_kb, row.shared_clean_resident_kb, row.locked_kb, row.proportional_resident_kb);
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
    return "__intrinsic_profiler_smaps";
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
static_assert(sizeof(ProfilerSmapsTable) == sizeof(dataframe::Dataframe));



class SymbolTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","symbol_set_id","name","source_file","line_number","inlined"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::SetIdSorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = SymbolTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(SymbolTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const SymbolTable& table) const {
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
    static constexpr uint32_t symbol_set_id = 1;
    static constexpr uint32_t name = 2;
    static constexpr uint32_t source_file = 3;
    static constexpr uint32_t line_number = 4;
    static constexpr uint32_t inlined = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(SymbolTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    SymbolTable::Id id() const {
        
        return SymbolTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> source_file() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    SymbolTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const SymbolTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    SymbolTable::Id id() const {
        
        return SymbolTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> source_file() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const SymbolTable* table_;
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
    SymbolTable::Id id() const {
        
        return SymbolTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t symbol_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      std::optional<StringPool::Id> source_file() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::source_file>(kSpec);
      }
    std::optional<uint32_t> line_number() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::line_number>(kSpec);
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

    SymbolTable::Id id() const {
        
        return SymbolTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t symbol_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      std::optional<StringPool::Id> source_file() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::source_file>(kSpec);
      }
    std::optional<uint32_t> line_number() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::line_number>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(SymbolTable* table) : table_(table) {
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
      SymbolTable::Id id() const {
        
        return SymbolTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> source_file() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }
      

    private:
      SymbolTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const SymbolTable* table) : table_(table) {
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
      SymbolTable::Id id() const {
        
        return SymbolTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t symbol_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::symbol_set_id>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          std::optional<StringPool::Id> source_file() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::source_file>(kSpec, row_);
      }
        std::optional<uint32_t> line_number() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::line_number>(kSpec, row_);
    }

    private:
      const SymbolTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _symbol_set_id = {}, StringPool::Id _name = {}, std::optional<StringPool::Id> _source_file = {}, std::optional<uint32_t> _line_number = {}, std::optional<uint32_t> _inlined = {}) : symbol_set_id(std::move(_symbol_set_id)), name(std::move(_name)), source_file(std::move(_source_file)), line_number(std::move(_line_number)), inlined(std::move(_inlined)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(symbol_set_id, other.symbol_set_id) && std::equal_to<>()(name, other.name) && std::equal_to<>()(source_file, other.source_file) && std::equal_to<>()(line_number, other.line_number) && std::equal_to<>()(inlined, other.inlined);
    }

        uint32_t symbol_set_id;
    StringPool::Id name;
    std::optional<StringPool::Id> source_file;
    std::optional<uint32_t> line_number;
    std::optional<uint32_t> inlined;
  };

  explicit SymbolTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.symbol_set_id, std::make_optional(row.name), row.source_file, row.line_number, row.inlined);
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
    return "__intrinsic_stack_profile_symbol";
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
static_assert(sizeof(SymbolTable) == sizeof(dataframe::Dataframe));



class VulkanMemoryAllocationsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","arg_set_id","source","operation","timestamp","upid","device","device_memory","memory_type","heap","function_name","object_handle","memory_address","memory_size","scope"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = VulkanMemoryAllocationsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(VulkanMemoryAllocationsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const VulkanMemoryAllocationsTable& table) const {
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
    static constexpr uint32_t arg_set_id = 1;
    static constexpr uint32_t source = 2;
    static constexpr uint32_t operation = 3;
    static constexpr uint32_t timestamp = 4;
    static constexpr uint32_t upid = 5;
    static constexpr uint32_t device = 6;
    static constexpr uint32_t device_memory = 7;
    static constexpr uint32_t memory_type = 8;
    static constexpr uint32_t heap = 9;
    static constexpr uint32_t function_name = 10;
    static constexpr uint32_t object_handle = 11;
    static constexpr uint32_t memory_address = 12;
    static constexpr uint32_t memory_size = 13;
    static constexpr uint32_t scope = 14;
  };
  struct RowReference {
   public:
    explicit RowReference(VulkanMemoryAllocationsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    VulkanMemoryAllocationsTable::Id id() const {
        
        return VulkanMemoryAllocationsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    VulkanMemoryAllocationsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const VulkanMemoryAllocationsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    VulkanMemoryAllocationsTable::Id id() const {
        
        return VulkanMemoryAllocationsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const VulkanMemoryAllocationsTable* table_;
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
    VulkanMemoryAllocationsTable::Id id() const {
        
        return VulkanMemoryAllocationsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
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

    VulkanMemoryAllocationsTable::Id id() const {
        
        return VulkanMemoryAllocationsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(VulkanMemoryAllocationsTable* table) : table_(table) {
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
      VulkanMemoryAllocationsTable::Id id() const {
        
        return VulkanMemoryAllocationsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }

    private:
      VulkanMemoryAllocationsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const VulkanMemoryAllocationsTable* table) : table_(table) {
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
      VulkanMemoryAllocationsTable::Id id() const {
        
        return VulkanMemoryAllocationsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const VulkanMemoryAllocationsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<uint32_t> _arg_set_id = {}, StringPool::Id _source = {}, StringPool::Id _operation = {}, int64_t _timestamp = {}, std::optional<uint32_t> _upid = {}, std::optional<int64_t> _device = {}, std::optional<int64_t> _device_memory = {}, std::optional<uint32_t> _memory_type = {}, std::optional<uint32_t> _heap = {}, std::optional<StringPool::Id> _function_name = {}, std::optional<int64_t> _object_handle = {}, std::optional<int64_t> _memory_address = {}, std::optional<int64_t> _memory_size = {}, StringPool::Id _scope = {}) : arg_set_id(std::move(_arg_set_id)), source(std::move(_source)), operation(std::move(_operation)), timestamp(std::move(_timestamp)), upid(std::move(_upid)), device(std::move(_device)), device_memory(std::move(_device_memory)), memory_type(std::move(_memory_type)), heap(std::move(_heap)), function_name(std::move(_function_name)), object_handle(std::move(_object_handle)), memory_address(std::move(_memory_address)), memory_size(std::move(_memory_size)), scope(std::move(_scope)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(source, other.source) && std::equal_to<>()(operation, other.operation) && std::equal_to<>()(timestamp, other.timestamp) && std::equal_to<>()(upid, other.upid) && std::equal_to<>()(device, other.device) && std::equal_to<>()(device_memory, other.device_memory) && std::equal_to<>()(memory_type, other.memory_type) && std::equal_to<>()(heap, other.heap) && std::equal_to<>()(function_name, other.function_name) && std::equal_to<>()(object_handle, other.object_handle) && std::equal_to<>()(memory_address, other.memory_address) && std::equal_to<>()(memory_size, other.memory_size) && std::equal_to<>()(scope, other.scope);
    }

        std::optional<uint32_t> arg_set_id;
    StringPool::Id source;
    StringPool::Id operation;
    int64_t timestamp;
    std::optional<uint32_t> upid;
    std::optional<int64_t> device;
    std::optional<int64_t> device_memory;
    std::optional<uint32_t> memory_type;
    std::optional<uint32_t> heap;
    std::optional<StringPool::Id> function_name;
    std::optional<int64_t> object_handle;
    std::optional<int64_t> memory_address;
    std::optional<int64_t> memory_size;
    StringPool::Id scope;
  };

  explicit VulkanMemoryAllocationsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.arg_set_id, std::make_optional(row.source), std::make_optional(row.operation), row.timestamp, row.upid, row.device, row.device_memory, row.memory_type, row.heap, row.function_name, row.object_handle, row.memory_address, row.memory_size, std::make_optional(row.scope));
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
    return "__intrinsic_vulkan_memory_allocations";
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
static_assert(sizeof(VulkanMemoryAllocationsTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_PROFILER_TABLES_PY_H_

