#ifndef SRC_TRACE_PROCESSOR_TABLES_SLICE_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_SLICE_TABLES_PY_H_

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
#include "src/trace_processor/tables/slice_tables_fwd.h"

#include "src/trace_processor/tables/profiler_tables_py.h"
#include "src/trace_processor/tables/track_tables_py.h"

namespace perfetto::trace_processor::tables {


class SliceTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","dur","track_id","category","name","depth","parent_id","arg_set_id","thread_ts","thread_dur","thread_instruction_count","thread_instruction_delta"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = SliceTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(SliceTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const SliceTable& table) const {
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
    static constexpr uint32_t dur = 2;
    static constexpr uint32_t track_id = 3;
    static constexpr uint32_t category = 4;
    static constexpr uint32_t name = 5;
    static constexpr uint32_t depth = 6;
    static constexpr uint32_t parent_id = 7;
    static constexpr uint32_t arg_set_id = 8;
    static constexpr uint32_t thread_ts = 9;
    static constexpr uint32_t thread_dur = 10;
    static constexpr uint32_t thread_instruction_count = 11;
    static constexpr uint32_t thread_instruction_delta = 12;
  };
  struct RowReference {
   public:
    explicit RowReference(SliceTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    SliceTable::Id id() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::dur>(kSpec, row_);
    }
          TrackTable::Id track_id() const {
        
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> category() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::category>(kSpec, row_);
      }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<SliceTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(SliceTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<int64_t> thread_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_ts>(kSpec, row_);
    }
        std::optional<int64_t> thread_dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_dur>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_delta() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, row_);
    }
    void set_dur(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::dur>(kSpec, row_, res);
    }
          void set_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_depth(uint32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::depth>(kSpec, row_, res);
    }
          void set_parent_id(std::optional<SliceTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
        void set_arg_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_thread_ts(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_ts>(kSpec, row_, res);
    }
        void set_thread_dur(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_dur>(kSpec, row_, res);
    }
        void set_thread_instruction_count(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, row_, res);
    }
        void set_thread_instruction_delta(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    SliceTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const SliceTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    SliceTable::Id id() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::dur>(kSpec, row_);
    }
          TrackTable::Id track_id() const {
        
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> category() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::category>(kSpec, row_);
      }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<SliceTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(SliceTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<int64_t> thread_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_ts>(kSpec, row_);
    }
        std::optional<int64_t> thread_dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_dur>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_delta() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const SliceTable* table_;
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
    SliceTable::Id id() const {
        
        return SliceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    int64_t dur() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::dur>(kSpec);
    }
      TrackTable::Id track_id() const {
        
        return TrackTable::Id{cursor_.GetCellUnchecked<ColumnIndex::track_id>(kSpec)};
      }
      std::optional<StringPool::Id> category() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::category>(kSpec);
      }
      std::optional<StringPool::Id> name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    uint32_t depth() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::depth>(kSpec);
    }
      std::optional<SliceTable::Id> parent_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(SliceTable::Id{*res}) : std::nullopt;
      }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<int64_t> thread_ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_ts>(kSpec);
    }
    std::optional<int64_t> thread_dur() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_dur>(kSpec);
    }
    std::optional<int64_t> thread_instruction_count() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec);
    }
    std::optional<int64_t> thread_instruction_delta() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec);
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

    SliceTable::Id id() const {
        
        return SliceTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    int64_t dur() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::dur>(kSpec);
    }
      TrackTable::Id track_id() const {
        
        return TrackTable::Id{cursor_.GetCellUnchecked<ColumnIndex::track_id>(kSpec)};
      }
      std::optional<StringPool::Id> category() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::category>(kSpec);
      }
      std::optional<StringPool::Id> name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    uint32_t depth() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::depth>(kSpec);
    }
      std::optional<SliceTable::Id> parent_id() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(SliceTable::Id{*res}) : std::nullopt;
      }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    std::optional<int64_t> thread_ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_ts>(kSpec);
    }
    std::optional<int64_t> thread_dur() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_dur>(kSpec);
    }
    std::optional<int64_t> thread_instruction_count() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec);
    }
    std::optional<int64_t> thread_instruction_delta() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec);
    }
    void set_dur(int64_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::dur>(kSpec, res);
    }
      void set_name(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, res);
    }
    void set_depth(uint32_t res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::depth>(kSpec, res);
    }
      void set_parent_id(std::optional<SliceTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, res_value);
      }
    void set_arg_set_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }
    void set_thread_ts(std::optional<int64_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::thread_ts>(kSpec, res);
    }
    void set_thread_dur(std::optional<int64_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::thread_dur>(kSpec, res);
    }
    void set_thread_instruction_count(std::optional<int64_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, res);
    }
    void set_thread_instruction_delta(std::optional<int64_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(SliceTable* table) : table_(table) {
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
      SliceTable::Id id() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::dur>(kSpec, row_);
    }
          TrackTable::Id track_id() const {
        
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> category() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::category>(kSpec, row_);
      }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<SliceTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(SliceTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<int64_t> thread_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_ts>(kSpec, row_);
    }
        std::optional<int64_t> thread_dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_dur>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_delta() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, row_);
    }
      void set_dur(int64_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::dur>(kSpec, row_, res);
    }
          void set_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_depth(uint32_t res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::depth>(kSpec, row_, res);
    }
          void set_parent_id(std::optional<SliceTable::Id> res) {
        
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
        void set_arg_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
        void set_thread_ts(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_ts>(kSpec, row_, res);
    }
        void set_thread_dur(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_dur>(kSpec, row_, res);
    }
        void set_thread_instruction_count(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, row_, res);
    }
        void set_thread_instruction_delta(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, row_, res);
    }

    private:
      SliceTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const SliceTable* table) : table_(table) {
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
      SliceTable::Id id() const {
        
        return SliceTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::dur>(kSpec, row_);
    }
          TrackTable::Id track_id() const {
        
        return TrackTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::track_id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> category() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::category>(kSpec, row_);
      }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        uint32_t depth() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::depth>(kSpec, row_);
    }
          std::optional<SliceTable::Id> parent_id() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(SliceTable::Id{*res}) : std::nullopt;
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
        std::optional<int64_t> thread_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_ts>(kSpec, row_);
    }
        std::optional<int64_t> thread_dur() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_dur>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_count() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_count>(kSpec, row_);
    }
        std::optional<int64_t> thread_instruction_delta() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::thread_instruction_delta>(kSpec, row_);
    }

    private:
      const SliceTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, int64_t _dur = {}, TrackTable::Id _track_id = {}, std::optional<StringPool::Id> _category = {}, std::optional<StringPool::Id> _name = {}, uint32_t _depth = {}, std::optional<SliceTable::Id> _parent_id = {}, std::optional<uint32_t> _arg_set_id = {}, std::optional<int64_t> _thread_ts = {}, std::optional<int64_t> _thread_dur = {}, std::optional<int64_t> _thread_instruction_count = {}, std::optional<int64_t> _thread_instruction_delta = {}) : ts(std::move(_ts)), dur(std::move(_dur)), track_id(std::move(_track_id)), category(std::move(_category)), name(std::move(_name)), depth(std::move(_depth)), parent_id(std::move(_parent_id)), arg_set_id(std::move(_arg_set_id)), thread_ts(std::move(_thread_ts)), thread_dur(std::move(_thread_dur)), thread_instruction_count(std::move(_thread_instruction_count)), thread_instruction_delta(std::move(_thread_instruction_delta)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(dur, other.dur) && std::equal_to<>()(track_id, other.track_id) && std::equal_to<>()(category, other.category) && std::equal_to<>()(name, other.name) && std::equal_to<>()(depth, other.depth) && std::equal_to<>()(parent_id, other.parent_id) && std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(thread_ts, other.thread_ts) && std::equal_to<>()(thread_dur, other.thread_dur) && std::equal_to<>()(thread_instruction_count, other.thread_instruction_count) && std::equal_to<>()(thread_instruction_delta, other.thread_instruction_delta);
    }

        int64_t ts;
    int64_t dur;
    TrackTable::Id track_id;
    std::optional<StringPool::Id> category;
    std::optional<StringPool::Id> name;
    uint32_t depth;
    std::optional<SliceTable::Id> parent_id;
    std::optional<uint32_t> arg_set_id;
    std::optional<int64_t> thread_ts;
    std::optional<int64_t> thread_dur;
    std::optional<int64_t> thread_instruction_count;
    std::optional<int64_t> thread_instruction_delta;
  };

  explicit SliceTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.dur, row.track_id.value, row.category, row.name, row.depth, row.parent_id ? std::make_optional(row.parent_id->value) : std::nullopt, row.arg_set_id, row.thread_ts, row.thread_dur, row.thread_instruction_count, row.thread_instruction_delta);
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
    return "__intrinsic_slice";
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
static_assert(sizeof(SliceTable) == sizeof(dataframe::Dataframe));



class AndroidNetworkPacketsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","iface","direction","packet_transport","packet_length","packet_count","socket_tag","socket_tag_str","socket_uid","local_port","remote_port","packet_icmp_type","packet_icmp_code","packet_tcp_flags","packet_tcp_flags_str"},
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = AndroidNetworkPacketsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(AndroidNetworkPacketsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const AndroidNetworkPacketsTable& table) const {
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
    static constexpr uint32_t iface = 1;
    static constexpr uint32_t direction = 2;
    static constexpr uint32_t packet_transport = 3;
    static constexpr uint32_t packet_length = 4;
    static constexpr uint32_t packet_count = 5;
    static constexpr uint32_t socket_tag = 6;
    static constexpr uint32_t socket_tag_str = 7;
    static constexpr uint32_t socket_uid = 8;
    static constexpr uint32_t local_port = 9;
    static constexpr uint32_t remote_port = 10;
    static constexpr uint32_t packet_icmp_type = 11;
    static constexpr uint32_t packet_icmp_code = 12;
    static constexpr uint32_t packet_tcp_flags = 13;
    static constexpr uint32_t packet_tcp_flags_str = 14;
  };
  struct RowReference {
   public:
    explicit RowReference(AndroidNetworkPacketsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    AndroidNetworkPacketsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const AndroidNetworkPacketsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const AndroidNetworkPacketsTable* table_;
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

    
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(AndroidNetworkPacketsTable* table) : table_(table) {
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
      
      

    private:
      AndroidNetworkPacketsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const AndroidNetworkPacketsTable* table) : table_(table) {
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
      

    private:
      const AndroidNetworkPacketsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(SliceTable::Id _id = {}, StringPool::Id _iface = {}, StringPool::Id _direction = {}, StringPool::Id _packet_transport = {}, int64_t _packet_length = {}, int64_t _packet_count = {}, uint32_t _socket_tag = {}, StringPool::Id _socket_tag_str = {}, uint32_t _socket_uid = {}, std::optional<uint32_t> _local_port = {}, std::optional<uint32_t> _remote_port = {}, std::optional<uint32_t> _packet_icmp_type = {}, std::optional<uint32_t> _packet_icmp_code = {}, std::optional<uint32_t> _packet_tcp_flags = {}, std::optional<StringPool::Id> _packet_tcp_flags_str = {}) : id(std::move(_id)), iface(std::move(_iface)), direction(std::move(_direction)), packet_transport(std::move(_packet_transport)), packet_length(std::move(_packet_length)), packet_count(std::move(_packet_count)), socket_tag(std::move(_socket_tag)), socket_tag_str(std::move(_socket_tag_str)), socket_uid(std::move(_socket_uid)), local_port(std::move(_local_port)), remote_port(std::move(_remote_port)), packet_icmp_type(std::move(_packet_icmp_type)), packet_icmp_code(std::move(_packet_icmp_code)), packet_tcp_flags(std::move(_packet_tcp_flags)), packet_tcp_flags_str(std::move(_packet_tcp_flags_str)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(id, other.id) && std::equal_to<>()(iface, other.iface) && std::equal_to<>()(direction, other.direction) && std::equal_to<>()(packet_transport, other.packet_transport) && std::equal_to<>()(packet_length, other.packet_length) && std::equal_to<>()(packet_count, other.packet_count) && std::equal_to<>()(socket_tag, other.socket_tag) && std::equal_to<>()(socket_tag_str, other.socket_tag_str) && std::equal_to<>()(socket_uid, other.socket_uid) && std::equal_to<>()(local_port, other.local_port) && std::equal_to<>()(remote_port, other.remote_port) && std::equal_to<>()(packet_icmp_type, other.packet_icmp_type) && std::equal_to<>()(packet_icmp_code, other.packet_icmp_code) && std::equal_to<>()(packet_tcp_flags, other.packet_tcp_flags) && std::equal_to<>()(packet_tcp_flags_str, other.packet_tcp_flags_str);
    }

        SliceTable::Id id;
    StringPool::Id iface;
    StringPool::Id direction;
    StringPool::Id packet_transport;
    int64_t packet_length;
    int64_t packet_count;
    uint32_t socket_tag;
    StringPool::Id socket_tag_str;
    uint32_t socket_uid;
    std::optional<uint32_t> local_port;
    std::optional<uint32_t> remote_port;
    std::optional<uint32_t> packet_icmp_type;
    std::optional<uint32_t> packet_icmp_code;
    std::optional<uint32_t> packet_tcp_flags;
    std::optional<StringPool::Id> packet_tcp_flags_str;
  };

  explicit AndroidNetworkPacketsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, row.id.value, std::make_optional(row.iface), std::make_optional(row.direction), std::make_optional(row.packet_transport), row.packet_length, row.packet_count, row.socket_tag, std::make_optional(row.socket_tag_str), row.socket_uid, row.local_port, row.remote_port, row.packet_icmp_type, row.packet_icmp_code, row.packet_tcp_flags, row.packet_tcp_flags_str);
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
    return "__intrinsic_android_network_packets";
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
static_assert(sizeof(AndroidNetworkPacketsTable) == sizeof(dataframe::Dataframe));



class TrackEventCallstacksTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","slice_id","track_id","callsite_id","end_callsite_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = TrackEventCallstacksTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(TrackEventCallstacksTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const TrackEventCallstacksTable& table) const {
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
    static constexpr uint32_t slice_id = 1;
    static constexpr uint32_t track_id = 2;
    static constexpr uint32_t callsite_id = 3;
    static constexpr uint32_t end_callsite_id = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(TrackEventCallstacksTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    TrackEventCallstacksTable::Id id() const {
        
        return TrackEventCallstacksTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          std::optional<StackProfileCallsiteTable::Id> end_callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
    void set_callsite_id(std::optional<StackProfileCallsiteTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_, res_value);
      }
          void set_end_callsite_id(std::optional<StackProfileCallsiteTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, row_, res_value);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    TrackEventCallstacksTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const TrackEventCallstacksTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    TrackEventCallstacksTable::Id id() const {
        
        return TrackEventCallstacksTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          std::optional<StackProfileCallsiteTable::Id> end_callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const TrackEventCallstacksTable* table_;
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
    TrackEventCallstacksTable::Id id() const {
        
        return TrackEventCallstacksTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
      std::optional<StackProfileCallsiteTable::Id> end_callsite_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
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

    TrackEventCallstacksTable::Id id() const {
        
        return TrackEventCallstacksTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::callsite_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
      std::optional<StackProfileCallsiteTable::Id> end_callsite_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
    void set_callsite_id(std::optional<StackProfileCallsiteTable::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::callsite_id>(kSpec, res_value);
      }
      void set_end_callsite_id(std::optional<StackProfileCallsiteTable::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, res_value);
      }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(TrackEventCallstacksTable* table) : table_(table) {
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
      TrackEventCallstacksTable::Id id() const {
        
        return TrackEventCallstacksTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          std::optional<StackProfileCallsiteTable::Id> end_callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
      void set_callsite_id(std::optional<StackProfileCallsiteTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_, res_value);
      }
          void set_end_callsite_id(std::optional<StackProfileCallsiteTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, row_, res_value);
      }

    private:
      TrackEventCallstacksTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const TrackEventCallstacksTable* table) : table_(table) {
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
      TrackEventCallstacksTable::Id id() const {
        
        return TrackEventCallstacksTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StackProfileCallsiteTable::Id> callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }
          std::optional<StackProfileCallsiteTable::Id> end_callsite_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_callsite_id>(kSpec, row_);
        return res ? std::make_optional(StackProfileCallsiteTable::Id{*res}) : std::nullopt;
      }

    private:
      const TrackEventCallstacksTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(SliceTable::Id _slice_id = {}, TrackTable::Id _track_id = {}, std::optional<StackProfileCallsiteTable::Id> _callsite_id = {}, std::optional<StackProfileCallsiteTable::Id> _end_callsite_id = {}) : slice_id(std::move(_slice_id)), track_id(std::move(_track_id)), callsite_id(std::move(_callsite_id)), end_callsite_id(std::move(_end_callsite_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(slice_id, other.slice_id) && std::equal_to<>()(track_id, other.track_id) && std::equal_to<>()(callsite_id, other.callsite_id) && std::equal_to<>()(end_callsite_id, other.end_callsite_id);
    }

        SliceTable::Id slice_id;
    TrackTable::Id track_id;
    std::optional<StackProfileCallsiteTable::Id> callsite_id;
    std::optional<StackProfileCallsiteTable::Id> end_callsite_id;
  };

  explicit TrackEventCallstacksTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.slice_id.value, row.track_id.value, row.callsite_id ? std::make_optional(row.callsite_id->value) : std::nullopt, row.end_callsite_id ? std::make_optional(row.end_callsite_id->value) : std::nullopt);
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
    return "__intrinsic_track_event_callstacks";
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
static_assert(sizeof(TrackEventCallstacksTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_SLICE_TABLES_PY_H_

