#ifndef SRC_TRACE_PROCESSOR_TABLES_METADATA_TABLES_PY_H_
#define SRC_TRACE_PROCESSOR_TABLES_METADATA_TABLES_PY_H_

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
#include "src/trace_processor/tables/metadata_tables_fwd.h"



namespace perfetto::trace_processor::tables {


class MachineTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","raw_id","sysname","release","version","arch","num_cpus","android_build_fingerprint","android_device_manufacturer","android_sdk_version","system_ram_bytes","system_ram_gb"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = MachineTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(MachineTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const MachineTable& table) const {
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
    static constexpr uint32_t raw_id = 1;
    static constexpr uint32_t sysname = 2;
    static constexpr uint32_t release = 3;
    static constexpr uint32_t version = 4;
    static constexpr uint32_t arch = 5;
    static constexpr uint32_t num_cpus = 6;
    static constexpr uint32_t android_build_fingerprint = 7;
    static constexpr uint32_t android_device_manufacturer = 8;
    static constexpr uint32_t android_sdk_version = 9;
    static constexpr uint32_t system_ram_bytes = 10;
    static constexpr uint32_t system_ram_gb = 11;
  };
  struct RowReference {
   public:
    explicit RowReference(MachineTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    MachineTable::Id id() const {
        
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> sysname() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::sysname>(kSpec, row_);
      }
          std::optional<StringPool::Id> release() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::release>(kSpec, row_);
      }
          std::optional<StringPool::Id> version() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version>(kSpec, row_);
      }
          std::optional<StringPool::Id> arch() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arch>(kSpec, row_);
      }
        std::optional<uint32_t> num_cpus() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::num_cpus>(kSpec, row_);
    }
          std::optional<StringPool::Id> android_build_fingerprint() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, row_);
      }
          std::optional<StringPool::Id> android_device_manufacturer() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, row_);
      }
        std::optional<int64_t> android_sdk_version() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_bytes() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_gb() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, row_);
    }
    void set_sysname(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::sysname>(kSpec, row_, res);
    }
          void set_release(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::release>(kSpec, row_, res);
    }
          void set_version(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::version>(kSpec, row_, res);
    }
          void set_arch(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::arch>(kSpec, row_, res);
    }
        void set_num_cpus(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::num_cpus>(kSpec, row_, res);
    }
          void set_android_build_fingerprint(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, row_, res);
    }
          void set_android_device_manufacturer(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, row_, res);
    }
        void set_android_sdk_version(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, row_, res);
    }
        void set_system_ram_bytes(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, row_, res);
    }
        void set_system_ram_gb(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    MachineTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const MachineTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    MachineTable::Id id() const {
        
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> sysname() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::sysname>(kSpec, row_);
      }
          std::optional<StringPool::Id> release() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::release>(kSpec, row_);
      }
          std::optional<StringPool::Id> version() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version>(kSpec, row_);
      }
          std::optional<StringPool::Id> arch() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arch>(kSpec, row_);
      }
        std::optional<uint32_t> num_cpus() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::num_cpus>(kSpec, row_);
    }
          std::optional<StringPool::Id> android_build_fingerprint() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, row_);
      }
          std::optional<StringPool::Id> android_device_manufacturer() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, row_);
      }
        std::optional<int64_t> android_sdk_version() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_bytes() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_gb() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const MachineTable* table_;
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
    MachineTable::Id id() const {
        
        return MachineTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<StringPool::Id> sysname() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::sysname>(kSpec);
      }
      std::optional<StringPool::Id> release() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::release>(kSpec);
      }
      std::optional<StringPool::Id> version() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::version>(kSpec);
      }
      std::optional<StringPool::Id> arch() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::arch>(kSpec);
      }
    std::optional<uint32_t> num_cpus() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::num_cpus>(kSpec);
    }
      std::optional<StringPool::Id> android_build_fingerprint() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec);
      }
      std::optional<StringPool::Id> android_device_manufacturer() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec);
      }
    std::optional<int64_t> android_sdk_version() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec);
    }
    std::optional<int64_t> system_ram_bytes() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec);
    }
    std::optional<int64_t> system_ram_gb() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec);
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

    MachineTable::Id id() const {
        
        return MachineTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<StringPool::Id> sysname() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::sysname>(kSpec);
      }
      std::optional<StringPool::Id> release() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::release>(kSpec);
      }
      std::optional<StringPool::Id> version() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::version>(kSpec);
      }
      std::optional<StringPool::Id> arch() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::arch>(kSpec);
      }
    std::optional<uint32_t> num_cpus() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::num_cpus>(kSpec);
    }
      std::optional<StringPool::Id> android_build_fingerprint() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec);
      }
      std::optional<StringPool::Id> android_device_manufacturer() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec);
      }
    std::optional<int64_t> android_sdk_version() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec);
    }
    std::optional<int64_t> system_ram_bytes() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec);
    }
    std::optional<int64_t> system_ram_gb() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec);
    }
    void set_sysname(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::sysname>(kSpec, res);
    }
      void set_release(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::release>(kSpec, res);
    }
      void set_version(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::version>(kSpec, res);
    }
      void set_arch(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::arch>(kSpec, res);
    }
    void set_num_cpus(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::num_cpus>(kSpec, res);
    }
      void set_android_build_fingerprint(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, res);
    }
      void set_android_device_manufacturer(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, res);
    }
    void set_android_sdk_version(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, res);
    }
    void set_system_ram_bytes(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, res);
    }
    void set_system_ram_gb(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(MachineTable* table) : table_(table) {
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
      MachineTable::Id id() const {
        
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> sysname() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::sysname>(kSpec, row_);
      }
          std::optional<StringPool::Id> release() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::release>(kSpec, row_);
      }
          std::optional<StringPool::Id> version() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version>(kSpec, row_);
      }
          std::optional<StringPool::Id> arch() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arch>(kSpec, row_);
      }
        std::optional<uint32_t> num_cpus() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::num_cpus>(kSpec, row_);
    }
          std::optional<StringPool::Id> android_build_fingerprint() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, row_);
      }
          std::optional<StringPool::Id> android_device_manufacturer() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, row_);
      }
        std::optional<int64_t> android_sdk_version() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_bytes() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_gb() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, row_);
    }
      void set_sysname(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::sysname>(kSpec, row_, res);
    }
          void set_release(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::release>(kSpec, row_, res);
    }
          void set_version(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::version>(kSpec, row_, res);
    }
          void set_arch(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::arch>(kSpec, row_, res);
    }
        void set_num_cpus(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::num_cpus>(kSpec, row_, res);
    }
          void set_android_build_fingerprint(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, row_, res);
    }
          void set_android_device_manufacturer(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, row_, res);
    }
        void set_android_sdk_version(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, row_, res);
    }
        void set_system_ram_bytes(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, row_, res);
    }
        void set_system_ram_gb(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, row_, res);
    }

    private:
      MachineTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const MachineTable* table) : table_(table) {
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
      MachineTable::Id id() const {
        
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<StringPool::Id> sysname() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::sysname>(kSpec, row_);
      }
          std::optional<StringPool::Id> release() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::release>(kSpec, row_);
      }
          std::optional<StringPool::Id> version() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::version>(kSpec, row_);
      }
          std::optional<StringPool::Id> arch() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arch>(kSpec, row_);
      }
        std::optional<uint32_t> num_cpus() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::num_cpus>(kSpec, row_);
    }
          std::optional<StringPool::Id> android_build_fingerprint() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_build_fingerprint>(kSpec, row_);
      }
          std::optional<StringPool::Id> android_device_manufacturer() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_device_manufacturer>(kSpec, row_);
      }
        std::optional<int64_t> android_sdk_version() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_sdk_version>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_bytes() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_bytes>(kSpec, row_);
    }
        std::optional<int64_t> system_ram_gb() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::system_ram_gb>(kSpec, row_);
    }

    private:
      const MachineTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _raw_id = {}, std::optional<StringPool::Id> _sysname = {}, std::optional<StringPool::Id> _release = {}, std::optional<StringPool::Id> _version = {}, std::optional<StringPool::Id> _arch = {}, std::optional<uint32_t> _num_cpus = {}, std::optional<StringPool::Id> _android_build_fingerprint = {}, std::optional<StringPool::Id> _android_device_manufacturer = {}, std::optional<int64_t> _android_sdk_version = {}, std::optional<int64_t> _system_ram_bytes = {}, std::optional<int64_t> _system_ram_gb = {}) : raw_id(std::move(_raw_id)), sysname(std::move(_sysname)), release(std::move(_release)), version(std::move(_version)), arch(std::move(_arch)), num_cpus(std::move(_num_cpus)), android_build_fingerprint(std::move(_android_build_fingerprint)), android_device_manufacturer(std::move(_android_device_manufacturer)), android_sdk_version(std::move(_android_sdk_version)), system_ram_bytes(std::move(_system_ram_bytes)), system_ram_gb(std::move(_system_ram_gb)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(raw_id, other.raw_id) && std::equal_to<>()(sysname, other.sysname) && std::equal_to<>()(release, other.release) && std::equal_to<>()(version, other.version) && std::equal_to<>()(arch, other.arch) && std::equal_to<>()(num_cpus, other.num_cpus) && std::equal_to<>()(android_build_fingerprint, other.android_build_fingerprint) && std::equal_to<>()(android_device_manufacturer, other.android_device_manufacturer) && std::equal_to<>()(android_sdk_version, other.android_sdk_version) && std::equal_to<>()(system_ram_bytes, other.system_ram_bytes) && std::equal_to<>()(system_ram_gb, other.system_ram_gb);
    }

        uint32_t raw_id;
    std::optional<StringPool::Id> sysname;
    std::optional<StringPool::Id> release;
    std::optional<StringPool::Id> version;
    std::optional<StringPool::Id> arch;
    std::optional<uint32_t> num_cpus;
    std::optional<StringPool::Id> android_build_fingerprint;
    std::optional<StringPool::Id> android_device_manufacturer;
    std::optional<int64_t> android_sdk_version;
    std::optional<int64_t> system_ram_bytes;
    std::optional<int64_t> system_ram_gb;
  };

  explicit MachineTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.raw_id, row.sysname, row.release, row.version, row.arch, row.num_cpus, row.android_build_fingerprint, row.android_device_manufacturer, row.android_sdk_version, row.system_ram_bytes, row.system_ram_gb);
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
    return "__intrinsic_machine";
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
static_assert(sizeof(MachineTable) == sizeof(dataframe::Dataframe));



class ProcessTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","pid","name","start_ts","end_ts","parent_upid","uid","android_appid","android_user_id","cmdline","arg_set_id","machine_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ProcessTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ProcessTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ProcessTable& table) const {
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
    static constexpr uint32_t pid = 1;
    static constexpr uint32_t name = 2;
    static constexpr uint32_t start_ts = 3;
    static constexpr uint32_t end_ts = 4;
    static constexpr uint32_t parent_upid = 5;
    static constexpr uint32_t uid = 6;
    static constexpr uint32_t android_appid = 7;
    static constexpr uint32_t android_user_id = 8;
    static constexpr uint32_t cmdline = 9;
    static constexpr uint32_t arg_set_id = 10;
    static constexpr uint32_t machine_id = 11;
  };
  struct RowReference {
   public:
    explicit RowReference(ProcessTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t pid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::pid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> parent_upid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        std::optional<uint32_t> android_appid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_appid>(kSpec, row_);
    }
        std::optional<uint32_t> android_user_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_user_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> cmdline() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    void set_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_start_ts(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_, res);
    }
        void set_end_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_, res);
    }
        void set_parent_upid(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_upid>(kSpec, row_, res);
    }
        void set_uid(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::uid>(kSpec, row_, res);
    }
        void set_android_appid(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::android_appid>(kSpec, row_, res);
    }
        void set_android_user_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::android_user_id>(kSpec, row_, res);
    }
          void set_cmdline(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_, res);
    }
        void set_arg_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ProcessTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ProcessTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t pid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::pid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> parent_upid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        std::optional<uint32_t> android_appid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_appid>(kSpec, row_);
    }
        std::optional<uint32_t> android_user_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_user_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> cmdline() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ProcessTable* table_;
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
    uint32_t id() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t pid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::pid>(kSpec);
    }
      std::optional<StringPool::Id> name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    std::optional<int64_t> start_ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start_ts>(kSpec);
    }
    std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::end_ts>(kSpec);
    }
      std::optional<uint32_t> parent_upid() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_upid>(kSpec);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
    std::optional<uint32_t> uid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::uid>(kSpec);
    }
    std::optional<uint32_t> android_appid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::android_appid>(kSpec);
    }
    std::optional<uint32_t> android_user_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::android_user_id>(kSpec);
    }
      std::optional<StringPool::Id> cmdline() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::cmdline>(kSpec);
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

    uint32_t id() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t pid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::pid>(kSpec);
    }
      std::optional<StringPool::Id> name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    std::optional<int64_t> start_ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::start_ts>(kSpec);
    }
    std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::end_ts>(kSpec);
    }
      std::optional<uint32_t> parent_upid() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_upid>(kSpec);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
    std::optional<uint32_t> uid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::uid>(kSpec);
    }
    std::optional<uint32_t> android_appid() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::android_appid>(kSpec);
    }
    std::optional<uint32_t> android_user_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::android_user_id>(kSpec);
    }
      std::optional<StringPool::Id> cmdline() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::cmdline>(kSpec);
      }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    void set_name(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, res);
    }
    void set_start_ts(std::optional<int64_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::start_ts>(kSpec, res);
    }
    void set_end_ts(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::end_ts>(kSpec, res);
    }
    void set_parent_upid(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::parent_upid>(kSpec, res);
    }
    void set_uid(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::uid>(kSpec, res);
    }
    void set_android_appid(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::android_appid>(kSpec, res);
    }
    void set_android_user_id(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::android_user_id>(kSpec, res);
    }
      void set_cmdline(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::cmdline>(kSpec, res);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ProcessTable* table) : table_(table) {
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
      uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t pid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::pid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> parent_upid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        std::optional<uint32_t> android_appid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_appid>(kSpec, row_);
    }
        std::optional<uint32_t> android_user_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_user_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> cmdline() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      void set_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_start_ts(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_, res);
    }
        void set_end_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_, res);
    }
        void set_parent_upid(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_upid>(kSpec, row_, res);
    }
        void set_uid(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::uid>(kSpec, row_, res);
    }
        void set_android_appid(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::android_appid>(kSpec, row_, res);
    }
        void set_android_user_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::android_user_id>(kSpec, row_, res);
    }
          void set_cmdline(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_, res);
    }
        void set_arg_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }

    private:
      ProcessTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ProcessTable* table) : table_(table) {
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
      uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t pid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::pid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> parent_upid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> uid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::uid>(kSpec, row_);
    }
        std::optional<uint32_t> android_appid() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_appid>(kSpec, row_);
    }
        std::optional<uint32_t> android_user_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::android_user_id>(kSpec, row_);
    }
          std::optional<StringPool::Id> cmdline() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cmdline>(kSpec, row_);
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const ProcessTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _pid = {}, std::optional<StringPool::Id> _name = {}, std::optional<int64_t> _start_ts = {}, std::optional<int64_t> _end_ts = {}, std::optional<uint32_t> _parent_upid = {}, std::optional<uint32_t> _uid = {}, std::optional<uint32_t> _android_appid = {}, std::optional<uint32_t> _android_user_id = {}, std::optional<StringPool::Id> _cmdline = {}, std::optional<uint32_t> _arg_set_id = {}, MachineTable::Id _machine_id = {}) : pid(std::move(_pid)), name(std::move(_name)), start_ts(std::move(_start_ts)), end_ts(std::move(_end_ts)), parent_upid(std::move(_parent_upid)), uid(std::move(_uid)), android_appid(std::move(_android_appid)), android_user_id(std::move(_android_user_id)), cmdline(std::move(_cmdline)), arg_set_id(std::move(_arg_set_id)), machine_id(std::move(_machine_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(pid, other.pid) && std::equal_to<>()(name, other.name) && std::equal_to<>()(start_ts, other.start_ts) && std::equal_to<>()(end_ts, other.end_ts) && std::equal_to<>()(parent_upid, other.parent_upid) && std::equal_to<>()(uid, other.uid) && std::equal_to<>()(android_appid, other.android_appid) && std::equal_to<>()(android_user_id, other.android_user_id) && std::equal_to<>()(cmdline, other.cmdline) && std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(machine_id, other.machine_id);
    }

        int64_t pid;
    std::optional<StringPool::Id> name;
    std::optional<int64_t> start_ts;
    std::optional<int64_t> end_ts;
    std::optional<uint32_t> parent_upid;
    std::optional<uint32_t> uid;
    std::optional<uint32_t> android_appid;
    std::optional<uint32_t> android_user_id;
    std::optional<StringPool::Id> cmdline;
    std::optional<uint32_t> arg_set_id;
    MachineTable::Id machine_id;
  };

  explicit ProcessTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.pid, row.name, row.start_ts, row.end_ts, row.parent_upid, row.uid, row.android_appid, row.android_user_id, row.cmdline, row.arg_set_id, row.machine_id.value);
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
    return "__intrinsic_process";
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
static_assert(sizeof(ProcessTable) == sizeof(dataframe::Dataframe));



class ThreadTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","tid","name","start_ts","end_ts","upid","is_main_thread","is_idle","machine_id","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ThreadTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ThreadTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ThreadTable& table) const {
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
    static constexpr uint32_t tid = 1;
    static constexpr uint32_t name = 2;
    static constexpr uint32_t start_ts = 3;
    static constexpr uint32_t end_ts = 4;
    static constexpr uint32_t upid = 5;
    static constexpr uint32_t is_main_thread = 6;
    static constexpr uint32_t is_idle = 7;
    static constexpr uint32_t machine_id = 8;
    static constexpr uint32_t arg_set_id = 9;
  };
  struct RowReference {
   public:
    explicit RowReference(ThreadTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t tid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> upid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> is_main_thread() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, row_);
    }
        uint32_t is_idle() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_idle>(kSpec, row_);
    }
          MachineTable::Id machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    void set_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_start_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_, res);
    }
        void set_end_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_, res);
    }
        void set_upid(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::upid>(kSpec, row_, res);
    }
        void set_is_main_thread(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, row_, res);
    }
        void set_is_idle(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::is_idle>(kSpec, row_, res);
    }
        void set_arg_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ThreadTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ThreadTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t tid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> upid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> is_main_thread() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, row_);
    }
        uint32_t is_idle() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_idle>(kSpec, row_);
    }
          MachineTable::Id machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ThreadTable* table_;
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
    uint32_t id() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t tid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::tid>(kSpec);
    }
      std::optional<StringPool::Id> name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    std::optional<int64_t> start_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::start_ts>(kSpec);
    }
    std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::end_ts>(kSpec);
    }
      std::optional<uint32_t> upid() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
    std::optional<uint32_t> is_main_thread() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::is_main_thread>(kSpec);
    }
    uint32_t is_idle() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::is_idle>(kSpec);
    }
      MachineTable::Id machine_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return MachineTable::Id{cursor_.GetCellUnchecked<ColumnIndex::machine_id>(kSpec)};
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

    uint32_t id() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t tid() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::tid>(kSpec);
    }
      std::optional<StringPool::Id> name() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    std::optional<int64_t> start_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::start_ts>(kSpec);
    }
    std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::end_ts>(kSpec);
    }
      std::optional<uint32_t> upid() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::upid>(kSpec);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
    std::optional<uint32_t> is_main_thread() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::is_main_thread>(kSpec);
    }
    uint32_t is_idle() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::is_idle>(kSpec);
    }
      MachineTable::Id machine_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return MachineTable::Id{cursor_.GetCellUnchecked<ColumnIndex::machine_id>(kSpec)};
      }
    std::optional<uint32_t> arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    void set_name(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, res);
    }
    void set_start_ts(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::start_ts>(kSpec, res);
    }
    void set_end_ts(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::end_ts>(kSpec, res);
    }
    void set_upid(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::upid>(kSpec, res);
    }
    void set_is_main_thread(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, res);
    }
    void set_is_idle(uint32_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::is_idle>(kSpec, res);
    }
    void set_arg_set_id(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ThreadTable* table) : table_(table) {
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
      uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t tid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> upid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> is_main_thread() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, row_);
    }
        uint32_t is_idle() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_idle>(kSpec, row_);
    }
          MachineTable::Id machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      void set_name(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_start_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_, res);
    }
        void set_end_ts(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_, res);
    }
        void set_upid(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::upid>(kSpec, row_, res);
    }
        void set_is_main_thread(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, row_, res);
    }
        void set_is_idle(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::is_idle>(kSpec, row_, res);
    }
        void set_arg_set_id(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }

    private:
      ThreadTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ThreadTable* table) : table_(table) {
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
      uint32_t id() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t tid() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::tid>(kSpec, row_);
    }
          std::optional<StringPool::Id> name() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        std::optional<int64_t> start_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::start_ts>(kSpec, row_);
    }
        std::optional<int64_t> end_ts() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::end_ts>(kSpec, row_);
    }
          std::optional<uint32_t> upid() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::upid>(kSpec, row_);
        return res ? std::make_optional(uint32_t{*res}) : std::nullopt;
      }
        std::optional<uint32_t> is_main_thread() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_main_thread>(kSpec, row_);
    }
        uint32_t is_idle() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_idle>(kSpec, row_);
    }
          MachineTable::Id machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return MachineTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const ThreadTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _tid = {}, std::optional<StringPool::Id> _name = {}, std::optional<int64_t> _start_ts = {}, std::optional<int64_t> _end_ts = {}, std::optional<uint32_t> _upid = {}, std::optional<uint32_t> _is_main_thread = {}, uint32_t _is_idle = {}, MachineTable::Id _machine_id = {}, std::optional<uint32_t> _arg_set_id = {}) : tid(std::move(_tid)), name(std::move(_name)), start_ts(std::move(_start_ts)), end_ts(std::move(_end_ts)), upid(std::move(_upid)), is_main_thread(std::move(_is_main_thread)), is_idle(std::move(_is_idle)), machine_id(std::move(_machine_id)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(tid, other.tid) && std::equal_to<>()(name, other.name) && std::equal_to<>()(start_ts, other.start_ts) && std::equal_to<>()(end_ts, other.end_ts) && std::equal_to<>()(upid, other.upid) && std::equal_to<>()(is_main_thread, other.is_main_thread) && std::equal_to<>()(is_idle, other.is_idle) && std::equal_to<>()(machine_id, other.machine_id) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        int64_t tid;
    std::optional<StringPool::Id> name;
    std::optional<int64_t> start_ts;
    std::optional<int64_t> end_ts;
    std::optional<uint32_t> upid;
    std::optional<uint32_t> is_main_thread;
    uint32_t is_idle;
    MachineTable::Id machine_id;
    std::optional<uint32_t> arg_set_id;
  };

  explicit ThreadTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.tid, row.name, row.start_ts, row.end_ts, row.upid, row.is_main_thread, row.is_idle, row.machine_id.value, row.arg_set_id);
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
    return "__intrinsic_thread";
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
static_assert(sizeof(ThreadTable) == sizeof(dataframe::Dataframe));



class ArgTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","arg_set_id","flat_key","key","int_value","string_value","real_value","value_type"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::SetIdSorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Double{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ArgTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ArgTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ArgTable& table) const {
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
    static constexpr uint32_t flat_key = 2;
    static constexpr uint32_t key = 3;
    static constexpr uint32_t int_value = 4;
    static constexpr uint32_t string_value = 5;
    static constexpr uint32_t real_value = 6;
    static constexpr uint32_t value_type = 7;
  };
  struct RowReference {
   public:
    explicit RowReference(ArgTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ArgTable::Id id() const {
        
        return ArgTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          StringPool::Id flat_key() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::flat_key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id key() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> string_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::string_value>(kSpec, row_);
      }
        std::optional<double> real_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::real_value>(kSpec, row_);
    }
          StringPool::Id value_type() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::value_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ArgTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ArgTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ArgTable::Id id() const {
        
        return ArgTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          StringPool::Id flat_key() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::flat_key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id key() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> string_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::string_value>(kSpec, row_);
      }
        std::optional<double> real_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::real_value>(kSpec, row_);
    }
          StringPool::Id value_type() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::value_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ArgTable* table_;
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
    ArgTable::Id id() const {
        
        return ArgTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
      StringPool::Id flat_key() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::flat_key>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id key() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::key>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<int64_t> int_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::int_value>(kSpec);
    }
      std::optional<StringPool::Id> string_value() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::string_value>(kSpec);
      }
    std::optional<double> real_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::real_value>(kSpec);
    }
      StringPool::Id value_type() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::value_type>(kSpec);
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

    ArgTable::Id id() const {
        
        return ArgTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    uint32_t arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
      StringPool::Id flat_key() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::flat_key>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id key() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::key>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<int64_t> int_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::int_value>(kSpec);
    }
      std::optional<StringPool::Id> string_value() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::string_value>(kSpec);
      }
    std::optional<double> real_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::real_value>(kSpec);
    }
      StringPool::Id value_type() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::value_type>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ArgTable* table) : table_(table) {
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
      ArgTable::Id id() const {
        
        return ArgTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          StringPool::Id flat_key() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::flat_key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id key() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> string_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::string_value>(kSpec, row_);
      }
        std::optional<double> real_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::real_value>(kSpec, row_);
    }
          StringPool::Id value_type() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::value_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
      

    private:
      ArgTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ArgTable* table) : table_(table) {
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
      ArgTable::Id id() const {
        
        return ArgTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          StringPool::Id flat_key() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::flat_key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id key() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::key>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> string_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::string_value>(kSpec, row_);
      }
        std::optional<double> real_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::real_value>(kSpec, row_);
    }
          StringPool::Id value_type() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::value_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }

    private:
      const ArgTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _arg_set_id = {}, StringPool::Id _flat_key = {}, StringPool::Id _key = {}, std::optional<int64_t> _int_value = {}, std::optional<StringPool::Id> _string_value = {}, std::optional<double> _real_value = {}, StringPool::Id _value_type = {}) : arg_set_id(std::move(_arg_set_id)), flat_key(std::move(_flat_key)), key(std::move(_key)), int_value(std::move(_int_value)), string_value(std::move(_string_value)), real_value(std::move(_real_value)), value_type(std::move(_value_type)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(flat_key, other.flat_key) && std::equal_to<>()(key, other.key) && std::equal_to<>()(int_value, other.int_value) && std::equal_to<>()(string_value, other.string_value) && std::equal_to<>()(real_value, other.real_value) && std::equal_to<>()(value_type, other.value_type);
    }

        uint32_t arg_set_id;
    StringPool::Id flat_key;
    StringPool::Id key;
    std::optional<int64_t> int_value;
    std::optional<StringPool::Id> string_value;
    std::optional<double> real_value;
    StringPool::Id value_type;
  };

  explicit ArgTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.arg_set_id, std::make_optional(row.flat_key), std::make_optional(row.key), row.int_value, row.string_value, row.real_value, std::make_optional(row.value_type));
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
    return "__intrinsic_args";
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
static_assert(sizeof(ArgTable) == sizeof(dataframe::Dataframe));



class BuildFlagsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","name","enabled"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = BuildFlagsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(BuildFlagsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const BuildFlagsTable& table) const {
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
    static constexpr uint32_t enabled = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(BuildFlagsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    BuildFlagsTable::Id id() const {
        
        return BuildFlagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    BuildFlagsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const BuildFlagsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    BuildFlagsTable::Id id() const {
        
        return BuildFlagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const BuildFlagsTable* table_;
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
    BuildFlagsTable::Id id() const {
        
        return BuildFlagsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    BuildFlagsTable::Id id() const {
        
        return BuildFlagsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(BuildFlagsTable* table) : table_(table) {
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
      BuildFlagsTable::Id id() const {
        
        return BuildFlagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      BuildFlagsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const BuildFlagsTable* table) : table_(table) {
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
      BuildFlagsTable::Id id() const {
        
        return BuildFlagsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const BuildFlagsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _name = {}, uint32_t _enabled = {}) : name(std::move(_name)), enabled(std::move(_enabled)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(name, other.name) && std::equal_to<>()(enabled, other.enabled);
    }

        StringPool::Id name;
    uint32_t enabled;
  };

  explicit BuildFlagsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.name), row.enabled);
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
    return "__intrinsic_build_flags";
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
static_assert(sizeof(BuildFlagsTable) == sizeof(dataframe::Dataframe));



class ChromeRawTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","name","utid","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ChromeRawTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ChromeRawTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ChromeRawTable& table) const {
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
    static constexpr uint32_t name = 2;
    static constexpr uint32_t utid = 3;
    static constexpr uint32_t arg_set_id = 4;
  };
  struct RowReference {
   public:
    explicit RowReference(ChromeRawTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ChromeRawTable::Id id() const {
        
        return ChromeRawTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ChromeRawTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ChromeRawTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ChromeRawTable::Id id() const {
        
        return ChromeRawTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ChromeRawTable* table_;
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
    ChromeRawTable::Id id() const {
        
        return ChromeRawTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      uint32_t utid() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec)};
      }
    uint32_t arg_set_id() const {
      
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

    ChromeRawTable::Id id() const {
        
        return ChromeRawTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      uint32_t utid() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec)};
      }
    uint32_t arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ChromeRawTable* table) : table_(table) {
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
      ChromeRawTable::Id id() const {
        
        return ChromeRawTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      

    private:
      ChromeRawTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ChromeRawTable* table) : table_(table) {
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
      ChromeRawTable::Id id() const {
        
        return ChromeRawTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const ChromeRawTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, StringPool::Id _name = {}, uint32_t _utid = {}, uint32_t _arg_set_id = {}) : ts(std::move(_ts)), name(std::move(_name)), utid(std::move(_utid)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(name, other.name) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        int64_t ts;
    StringPool::Id name;
    uint32_t utid;
    uint32_t arg_set_id;
  };

  explicit ChromeRawTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, std::make_optional(row.name), row.utid, row.arg_set_id);
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
    return "__intrinsic_chrome_raw";
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
static_assert(sizeof(ChromeRawTable) == sizeof(dataframe::Dataframe));



class ClockSnapshotTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","clock_id","clock_name","clock_value","snapshot_id","machine_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ClockSnapshotTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ClockSnapshotTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ClockSnapshotTable& table) const {
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
    static constexpr uint32_t clock_id = 2;
    static constexpr uint32_t clock_name = 3;
    static constexpr uint32_t clock_value = 4;
    static constexpr uint32_t snapshot_id = 5;
    static constexpr uint32_t machine_id = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(ClockSnapshotTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ClockSnapshotTable::Id id() const {
        
        return ClockSnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t clock_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_id>(kSpec, row_);
    }
        int64_t clock_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_value>(kSpec, row_);
    }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ClockSnapshotTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ClockSnapshotTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ClockSnapshotTable::Id id() const {
        
        return ClockSnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t clock_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_id>(kSpec, row_);
    }
        int64_t clock_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_value>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ClockSnapshotTable* table_;
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
    ClockSnapshotTable::Id id() const {
        
        return ClockSnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    int64_t clock_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::clock_id>(kSpec);
    }
    int64_t clock_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::clock_value>(kSpec);
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

    ClockSnapshotTable::Id id() const {
        
        return ClockSnapshotTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
    int64_t clock_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::clock_id>(kSpec);
    }
    int64_t clock_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::clock_value>(kSpec);
    }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ClockSnapshotTable* table) : table_(table) {
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
      ClockSnapshotTable::Id id() const {
        
        return ClockSnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t clock_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_id>(kSpec, row_);
    }
        int64_t clock_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_value>(kSpec, row_);
    }
      

    private:
      ClockSnapshotTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ClockSnapshotTable* table) : table_(table) {
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
      ClockSnapshotTable::Id id() const {
        
        return ClockSnapshotTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
        int64_t clock_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_id>(kSpec, row_);
    }
        int64_t clock_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::clock_value>(kSpec, row_);
    }

    private:
      const ClockSnapshotTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, int64_t _clock_id = {}, std::optional<StringPool::Id> _clock_name = {}, int64_t _clock_value = {}, uint32_t _snapshot_id = {}, MachineTable::Id _machine_id = {}) : ts(std::move(_ts)), clock_id(std::move(_clock_id)), clock_name(std::move(_clock_name)), clock_value(std::move(_clock_value)), snapshot_id(std::move(_snapshot_id)), machine_id(std::move(_machine_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(clock_id, other.clock_id) && std::equal_to<>()(clock_name, other.clock_name) && std::equal_to<>()(clock_value, other.clock_value) && std::equal_to<>()(snapshot_id, other.snapshot_id) && std::equal_to<>()(machine_id, other.machine_id);
    }

        int64_t ts;
    int64_t clock_id;
    std::optional<StringPool::Id> clock_name;
    int64_t clock_value;
    uint32_t snapshot_id;
    MachineTable::Id machine_id;
  };

  explicit ClockSnapshotTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, row.clock_id, row.clock_name, row.clock_value, row.snapshot_id, row.machine_id.value);
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
    return "__intrinsic_clock_snapshot";
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
static_assert(sizeof(ClockSnapshotTable) == sizeof(dataframe::Dataframe));



class CpuTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","cpu","cluster_id","processor","machine_id","capacity","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = CpuTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(CpuTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const CpuTable& table) const {
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
    static constexpr uint32_t cpu = 1;
    static constexpr uint32_t cluster_id = 2;
    static constexpr uint32_t processor = 3;
    static constexpr uint32_t machine_id = 4;
    static constexpr uint32_t capacity = 5;
    static constexpr uint32_t arg_set_id = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(CpuTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    CpuTable::Id id() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> cpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cpu>(kSpec, row_);
    }
        uint32_t cluster_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster_id>(kSpec, row_);
    }
          StringPool::Id processor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::processor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> capacity() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::capacity>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    void set_cpu(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cpu>(kSpec, row_, res);
    }
        void set_cluster_id(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cluster_id>(kSpec, row_, res);
    }
          void set_processor(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::processor>(kSpec, row_, std::make_optional(res));
    }
        void set_capacity(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::capacity>(kSpec, row_, res);
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
    CpuTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const CpuTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    CpuTable::Id id() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> cpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cpu>(kSpec, row_);
    }
        uint32_t cluster_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster_id>(kSpec, row_);
    }
          StringPool::Id processor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::processor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> capacity() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::capacity>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const CpuTable* table_;
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
    CpuTable::Id id() const {
        
        return CpuTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> cpu() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::cpu>(kSpec);
    }
    uint32_t cluster_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cluster_id>(kSpec);
    }
      StringPool::Id processor() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::processor>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<uint32_t> capacity() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::capacity>(kSpec);
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

    CpuTable::Id id() const {
        
        return CpuTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> cpu() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::cpu>(kSpec);
    }
    uint32_t cluster_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::cluster_id>(kSpec);
    }
      StringPool::Id processor() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::processor>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<uint32_t> capacity() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::capacity>(kSpec);
    }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    void set_cpu(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::cpu>(kSpec, res);
    }
    void set_cluster_id(uint32_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::cluster_id>(kSpec, res);
    }
      void set_processor(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::processor>(kSpec, std::make_optional(res));
    }
    void set_capacity(std::optional<uint32_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::capacity>(kSpec, res);
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
      explicit Iterator(CpuTable* table) : table_(table) {
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
      CpuTable::Id id() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> cpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cpu>(kSpec, row_);
    }
        uint32_t cluster_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster_id>(kSpec, row_);
    }
          StringPool::Id processor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::processor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> capacity() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::capacity>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      void set_cpu(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cpu>(kSpec, row_, res);
    }
        void set_cluster_id(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::cluster_id>(kSpec, row_, res);
    }
          void set_processor(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::processor>(kSpec, row_, std::make_optional(res));
    }
        void set_capacity(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::capacity>(kSpec, row_, res);
    }
        void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }

    private:
      CpuTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const CpuTable* table) : table_(table) {
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
      CpuTable::Id id() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> cpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cpu>(kSpec, row_);
    }
        uint32_t cluster_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::cluster_id>(kSpec, row_);
    }
          StringPool::Id processor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::processor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> capacity() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::capacity>(kSpec, row_);
    }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const CpuTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<uint32_t> _cpu = {}, uint32_t _cluster_id = {}, StringPool::Id _processor = {}, MachineTable::Id _machine_id = {}, std::optional<uint32_t> _capacity = {}, std::optional<uint32_t> _arg_set_id = {}) : cpu(std::move(_cpu)), cluster_id(std::move(_cluster_id)), processor(std::move(_processor)), machine_id(std::move(_machine_id)), capacity(std::move(_capacity)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(cpu, other.cpu) && std::equal_to<>()(cluster_id, other.cluster_id) && std::equal_to<>()(processor, other.processor) && std::equal_to<>()(machine_id, other.machine_id) && std::equal_to<>()(capacity, other.capacity) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        std::optional<uint32_t> cpu;
    uint32_t cluster_id;
    StringPool::Id processor;
    MachineTable::Id machine_id;
    std::optional<uint32_t> capacity;
    std::optional<uint32_t> arg_set_id;
  };

  explicit CpuTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.cpu, row.cluster_id, std::make_optional(row.processor), row.machine_id.value, row.capacity, row.arg_set_id);
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
    return "__intrinsic_cpu";
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
static_assert(sizeof(CpuTable) == sizeof(dataframe::Dataframe));



class CpuFreqTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ucpu","freq"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = CpuFreqTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(CpuFreqTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const CpuFreqTable& table) const {
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
    static constexpr uint32_t ucpu = 1;
    static constexpr uint32_t freq = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(CpuFreqTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    CpuFreqTable::Id id() const {
        
        return CpuFreqTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    CpuFreqTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const CpuFreqTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    CpuFreqTable::Id id() const {
        
        return CpuFreqTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const CpuFreqTable* table_;
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
    CpuFreqTable::Id id() const {
        
        return CpuFreqTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    CpuFreqTable::Id id() const {
        
        return CpuFreqTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(CpuFreqTable* table) : table_(table) {
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
      CpuFreqTable::Id id() const {
        
        return CpuFreqTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      CpuFreqTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const CpuFreqTable* table) : table_(table) {
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
      CpuFreqTable::Id id() const {
        
        return CpuFreqTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const CpuFreqTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(CpuTable::Id _ucpu = {}, uint32_t _freq = {}) : ucpu(std::move(_ucpu)), freq(std::move(_freq)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ucpu, other.ucpu) && std::equal_to<>()(freq, other.freq);
    }

        CpuTable::Id ucpu;
    uint32_t freq;
  };

  explicit CpuFreqTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ucpu.value, row.freq);
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
    return "__intrinsic_cpu_freq";
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
static_assert(sizeof(CpuFreqTable) == sizeof(dataframe::Dataframe));



class ExpMissingChromeProcTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","upid","reliable_from"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ExpMissingChromeProcTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ExpMissingChromeProcTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ExpMissingChromeProcTable& table) const {
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
    static constexpr uint32_t reliable_from = 2;
  };
  struct RowReference {
   public:
    explicit RowReference(ExpMissingChromeProcTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ExpMissingChromeProcTable::Id id() const {
        
        return ExpMissingChromeProcTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ExpMissingChromeProcTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ExpMissingChromeProcTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ExpMissingChromeProcTable::Id id() const {
        
        return ExpMissingChromeProcTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ExpMissingChromeProcTable* table_;
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
    ExpMissingChromeProcTable::Id id() const {
        
        return ExpMissingChromeProcTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    ExpMissingChromeProcTable::Id id() const {
        
        return ExpMissingChromeProcTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ExpMissingChromeProcTable* table) : table_(table) {
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
      ExpMissingChromeProcTable::Id id() const {
        
        return ExpMissingChromeProcTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      ExpMissingChromeProcTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ExpMissingChromeProcTable* table) : table_(table) {
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
      ExpMissingChromeProcTable::Id id() const {
        
        return ExpMissingChromeProcTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const ExpMissingChromeProcTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(uint32_t _upid = {}, std::optional<int64_t> _reliable_from = {}) : upid(std::move(_upid)), reliable_from(std::move(_reliable_from)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(upid, other.upid) && std::equal_to<>()(reliable_from, other.reliable_from);
    }

        uint32_t upid;
    std::optional<int64_t> reliable_from;
  };

  explicit ExpMissingChromeProcTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.upid, row.reliable_from);
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
    return "__intrinsic_experimental_missing_chrome_processes";
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
static_assert(sizeof(ExpMissingChromeProcTable) == sizeof(dataframe::Dataframe));



class FiledescriptorTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ufd","fd","ts","upid","path"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = FiledescriptorTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(FiledescriptorTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const FiledescriptorTable& table) const {
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
    static constexpr uint32_t ufd = 1;
    static constexpr uint32_t fd = 2;
    static constexpr uint32_t ts = 3;
    static constexpr uint32_t upid = 4;
    static constexpr uint32_t path = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(FiledescriptorTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    FiledescriptorTable::Id id() const {
        
        return FiledescriptorTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    FiledescriptorTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const FiledescriptorTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    FiledescriptorTable::Id id() const {
        
        return FiledescriptorTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const FiledescriptorTable* table_;
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
    FiledescriptorTable::Id id() const {
        
        return FiledescriptorTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    FiledescriptorTable::Id id() const {
        
        return FiledescriptorTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(FiledescriptorTable* table) : table_(table) {
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
      FiledescriptorTable::Id id() const {
        
        return FiledescriptorTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      FiledescriptorTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const FiledescriptorTable* table) : table_(table) {
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
      FiledescriptorTable::Id id() const {
        
        return FiledescriptorTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const FiledescriptorTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ufd = {}, int64_t _fd = {}, std::optional<int64_t> _ts = {}, std::optional<uint32_t> _upid = {}, std::optional<StringPool::Id> _path = {}) : ufd(std::move(_ufd)), fd(std::move(_fd)), ts(std::move(_ts)), upid(std::move(_upid)), path(std::move(_path)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ufd, other.ufd) && std::equal_to<>()(fd, other.fd) && std::equal_to<>()(ts, other.ts) && std::equal_to<>()(upid, other.upid) && std::equal_to<>()(path, other.path);
    }

        int64_t ufd;
    int64_t fd;
    std::optional<int64_t> ts;
    std::optional<uint32_t> upid;
    std::optional<StringPool::Id> path;
  };

  explicit FiledescriptorTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ufd, row.fd, row.ts, row.upid, row.path);
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
    return "__intrinsic_filedescriptor";
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
static_assert(sizeof(FiledescriptorTable) == sizeof(dataframe::Dataframe));



class FtraceEventTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","ts","name","utid","arg_set_id","common_flags","ucpu"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Sorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = FtraceEventTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(FtraceEventTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const FtraceEventTable& table) const {
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
    static constexpr uint32_t name = 2;
    static constexpr uint32_t utid = 3;
    static constexpr uint32_t arg_set_id = 4;
    static constexpr uint32_t common_flags = 5;
    static constexpr uint32_t ucpu = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(FtraceEventTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    FtraceEventTable::Id id() const {
        
        return FtraceEventTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          CpuTable::Id ucpu() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::ucpu>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    FtraceEventTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const FtraceEventTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    FtraceEventTable::Id id() const {
        
        return FtraceEventTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          CpuTable::Id ucpu() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::ucpu>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const FtraceEventTable* table_;
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
    FtraceEventTable::Id id() const {
        
        return FtraceEventTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      uint32_t utid() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec)};
      }
    uint32_t arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
      CpuTable::Id ucpu() const {
        
        return CpuTable::Id{cursor_.GetCellUnchecked<ColumnIndex::ucpu>(kSpec)};
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

    FtraceEventTable::Id id() const {
        
        return FtraceEventTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    int64_t ts() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::ts>(kSpec);
    }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      uint32_t utid() const {
        
        return uint32_t{cursor_.GetCellUnchecked<ColumnIndex::utid>(kSpec)};
      }
    uint32_t arg_set_id() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
      CpuTable::Id ucpu() const {
        
        return CpuTable::Id{cursor_.GetCellUnchecked<ColumnIndex::ucpu>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(FtraceEventTable* table) : table_(table) {
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
      FtraceEventTable::Id id() const {
        
        return FtraceEventTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          CpuTable::Id ucpu() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::ucpu>(kSpec, row_)};
      }
      

    private:
      FtraceEventTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const FtraceEventTable* table) : table_(table) {
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
      FtraceEventTable::Id id() const {
        
        return FtraceEventTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        int64_t ts() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::ts>(kSpec, row_);
    }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          uint32_t utid() const {
        
        return uint32_t{table_->dataframe_.template GetCellUnchecked<ColumnIndex::utid>(kSpec, row_)};
      }
        uint32_t arg_set_id() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
          CpuTable::Id ucpu() const {
        
        return CpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::ucpu>(kSpec, row_)};
      }

    private:
      const FtraceEventTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(int64_t _ts = {}, StringPool::Id _name = {}, uint32_t _utid = {}, uint32_t _arg_set_id = {}, uint32_t _common_flags = {}, CpuTable::Id _ucpu = {}) : ts(std::move(_ts)), name(std::move(_name)), utid(std::move(_utid)), arg_set_id(std::move(_arg_set_id)), common_flags(std::move(_common_flags)), ucpu(std::move(_ucpu)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(ts, other.ts) && std::equal_to<>()(name, other.name) && std::equal_to<>()(utid, other.utid) && std::equal_to<>()(arg_set_id, other.arg_set_id) && std::equal_to<>()(common_flags, other.common_flags) && std::equal_to<>()(ucpu, other.ucpu);
    }

        int64_t ts;
    StringPool::Id name;
    uint32_t utid;
    uint32_t arg_set_id;
    uint32_t common_flags;
    CpuTable::Id ucpu;
  };

  explicit FtraceEventTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.ts, std::make_optional(row.name), row.utid, row.arg_set_id, row.common_flags, row.ucpu.value);
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
    return "__intrinsic_ftrace_event";
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
static_assert(sizeof(FtraceEventTable) == sizeof(dataframe::Dataframe));



class GpuTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","gpu","machine_id","name","vendor","model","architecture","uuid","pci_bdf","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = GpuTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(GpuTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const GpuTable& table) const {
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
    static constexpr uint32_t gpu = 1;
    static constexpr uint32_t machine_id = 2;
    static constexpr uint32_t name = 3;
    static constexpr uint32_t vendor = 4;
    static constexpr uint32_t model = 5;
    static constexpr uint32_t architecture = 6;
    static constexpr uint32_t uuid = 7;
    static constexpr uint32_t pci_bdf = 8;
    static constexpr uint32_t arg_set_id = 9;
  };
  struct RowReference {
   public:
    explicit RowReference(GpuTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    GpuTable::Id id() const {
        
        return GpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> gpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::gpu>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id vendor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::vendor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id model() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::model>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id architecture() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::architecture>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id uuid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::uuid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id pci_bdf() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    void set_gpu(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::gpu>(kSpec, row_, res);
    }
          void set_name(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
          void set_vendor(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::vendor>(kSpec, row_, std::make_optional(res));
    }
          void set_model(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::model>(kSpec, row_, std::make_optional(res));
    }
          void set_architecture(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::architecture>(kSpec, row_, std::make_optional(res));
    }
          void set_uuid(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::uuid>(kSpec, row_, std::make_optional(res));
    }
          void set_pci_bdf(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, row_, std::make_optional(res));
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
    GpuTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const GpuTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    GpuTable::Id id() const {
        
        return GpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> gpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::gpu>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id vendor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::vendor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id model() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::model>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id architecture() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::architecture>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id uuid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::uuid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id pci_bdf() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const GpuTable* table_;
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
    GpuTable::Id id() const {
        
        return GpuTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> gpu() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::gpu>(kSpec);
    }
      StringPool::Id name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id vendor() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::vendor>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id model() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::model>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id architecture() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::architecture>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id uuid() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::uuid>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id pci_bdf() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::pci_bdf>(kSpec);
        return res ? *res : StringPool::Id::Null();
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

    GpuTable::Id id() const {
        
        return GpuTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    std::optional<uint32_t> gpu() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::gpu>(kSpec);
    }
      StringPool::Id name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id vendor() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::vendor>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id model() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::model>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id architecture() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::architecture>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id uuid() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::uuid>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
      StringPool::Id pci_bdf() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::pci_bdf>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec);
    }
    void set_gpu(std::optional<uint32_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::gpu>(kSpec, res);
    }
      void set_name(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, std::make_optional(res));
    }
      void set_vendor(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::vendor>(kSpec, std::make_optional(res));
    }
      void set_model(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::model>(kSpec, std::make_optional(res));
    }
      void set_architecture(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::architecture>(kSpec, std::make_optional(res));
    }
      void set_uuid(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::uuid>(kSpec, std::make_optional(res));
    }
      void set_pci_bdf(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, std::make_optional(res));
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
      explicit Iterator(GpuTable* table) : table_(table) {
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
      GpuTable::Id id() const {
        
        return GpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> gpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::gpu>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id vendor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::vendor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id model() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::model>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id architecture() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::architecture>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id uuid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::uuid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id pci_bdf() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
      void set_gpu(std::optional<uint32_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::gpu>(kSpec, row_, res);
    }
          void set_name(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, std::make_optional(res));
    }
          void set_vendor(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::vendor>(kSpec, row_, std::make_optional(res));
    }
          void set_model(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::model>(kSpec, row_, std::make_optional(res));
    }
          void set_architecture(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::architecture>(kSpec, row_, std::make_optional(res));
    }
          void set_uuid(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::uuid>(kSpec, row_, std::make_optional(res));
    }
          void set_pci_bdf(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, row_, std::make_optional(res));
    }
        void set_arg_set_id(std::optional<uint32_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_, res);
    }

    private:
      GpuTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const GpuTable* table) : table_(table) {
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
      GpuTable::Id id() const {
        
        return GpuTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> gpu() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::gpu>(kSpec, row_);
    }
          StringPool::Id name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id vendor() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::vendor>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id model() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::model>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id architecture() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::architecture>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id uuid() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::uuid>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
          StringPool::Id pci_bdf() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::pci_bdf>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const GpuTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<uint32_t> _gpu = {}, MachineTable::Id _machine_id = {}, StringPool::Id _name = {}, StringPool::Id _vendor = {}, StringPool::Id _model = {}, StringPool::Id _architecture = {}, StringPool::Id _uuid = {}, StringPool::Id _pci_bdf = {}, std::optional<uint32_t> _arg_set_id = {}) : gpu(std::move(_gpu)), machine_id(std::move(_machine_id)), name(std::move(_name)), vendor(std::move(_vendor)), model(std::move(_model)), architecture(std::move(_architecture)), uuid(std::move(_uuid)), pci_bdf(std::move(_pci_bdf)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(gpu, other.gpu) && std::equal_to<>()(machine_id, other.machine_id) && std::equal_to<>()(name, other.name) && std::equal_to<>()(vendor, other.vendor) && std::equal_to<>()(model, other.model) && std::equal_to<>()(architecture, other.architecture) && std::equal_to<>()(uuid, other.uuid) && std::equal_to<>()(pci_bdf, other.pci_bdf) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        std::optional<uint32_t> gpu;
    MachineTable::Id machine_id;
    StringPool::Id name;
    StringPool::Id vendor;
    StringPool::Id model;
    StringPool::Id architecture;
    StringPool::Id uuid;
    StringPool::Id pci_bdf;
    std::optional<uint32_t> arg_set_id;
  };

  explicit GpuTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.gpu, row.machine_id.value, std::make_optional(row.name), std::make_optional(row.vendor), std::make_optional(row.model), std::make_optional(row.architecture), std::make_optional(row.uuid), std::make_optional(row.pci_bdf), row.arg_set_id);
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
    return "__intrinsic_gpu";
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
static_assert(sizeof(GpuTable) == sizeof(dataframe::Dataframe));



class TraceFileTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","parent_id","name","size","trace_type","processing_order","is_container"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = TraceFileTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(TraceFileTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const TraceFileTable& table) const {
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
    static constexpr uint32_t parent_id = 1;
    static constexpr uint32_t name = 2;
    static constexpr uint32_t size = 3;
    static constexpr uint32_t trace_type = 4;
    static constexpr uint32_t processing_order = 5;
    static constexpr uint32_t is_container = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(TraceFileTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    TraceFileTable::Id id() const {
        
        return TraceFileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<TraceFileTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id trace_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> processing_order() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::processing_order>(kSpec, row_);
    }
        uint32_t is_container() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_container>(kSpec, row_);
    }
    void set_parent_id(std::optional<TraceFileTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
          void set_name(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::size>(kSpec, row_, res);
    }
          void set_trace_type(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::trace_type>(kSpec, row_, std::make_optional(res));
    }
        void set_processing_order(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::processing_order>(kSpec, row_, res);
    }
        void set_is_container(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::is_container>(kSpec, row_, res);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    TraceFileTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const TraceFileTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    TraceFileTable::Id id() const {
        
        return TraceFileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<TraceFileTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id trace_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> processing_order() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::processing_order>(kSpec, row_);
    }
        uint32_t is_container() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_container>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const TraceFileTable* table_;
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
    TraceFileTable::Id id() const {
        
        return TraceFileTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<TraceFileTable::Id> parent_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
      std::optional<StringPool::Id> name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    int64_t size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
      StringPool::Id trace_type() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::trace_type>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<int64_t> processing_order() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::processing_order>(kSpec);
    }
    uint32_t is_container() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::is_container>(kSpec);
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

    TraceFileTable::Id id() const {
        
        return TraceFileTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      std::optional<TraceFileTable::Id> parent_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::parent_id>(kSpec);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
      std::optional<StringPool::Id> name() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        return cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
      }
    int64_t size() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::size>(kSpec);
    }
      StringPool::Id trace_type() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::trace_type>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<int64_t> processing_order() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::processing_order>(kSpec);
    }
    uint32_t is_container() const {
      PERFETTO_DCHECK(!dataframe_->finalized());
      return cursor_.GetCellUnchecked<ColumnIndex::is_container>(kSpec);
    }
    void set_parent_id(std::optional<TraceFileTable::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, res_value);
      }
      void set_name(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::name>(kSpec, res);
    }
    void set_size(int64_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::size>(kSpec, res);
    }
      void set_trace_type(StringPool::Id res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        cursor_.SetCellUnchecked<ColumnIndex::trace_type>(kSpec, std::make_optional(res));
    }
    void set_processing_order(std::optional<int64_t> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::processing_order>(kSpec, res);
    }
    void set_is_container(uint32_t res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
      cursor_.SetCellUnchecked<ColumnIndex::is_container>(kSpec, res);
    }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(TraceFileTable* table) : table_(table) {
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
      TraceFileTable::Id id() const {
        
        return TraceFileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<TraceFileTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id trace_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> processing_order() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::processing_order>(kSpec, row_);
    }
        uint32_t is_container() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_container>(kSpec, row_);
    }
      void set_parent_id(std::optional<TraceFileTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_, res_value);
      }
          void set_name(std::optional<StringPool::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::name>(kSpec, row_, res);
    }
        void set_size(int64_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::size>(kSpec, row_, res);
    }
          void set_trace_type(StringPool::Id res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        table_->dataframe_.SetCellUnchecked<ColumnIndex::trace_type>(kSpec, row_, std::make_optional(res));
    }
        void set_processing_order(std::optional<int64_t> res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::processing_order>(kSpec, row_, res);
    }
        void set_is_container(uint32_t res) {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      table_->dataframe_.SetCellUnchecked<ColumnIndex::is_container>(kSpec, row_, res);
    }

    private:
      TraceFileTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const TraceFileTable* table) : table_(table) {
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
      TraceFileTable::Id id() const {
        
        return TraceFileTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          std::optional<TraceFileTable::Id> parent_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::parent_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
          std::optional<StringPool::Id> name() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
      }
        int64_t size() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::size>(kSpec, row_);
    }
          StringPool::Id trace_type() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_type>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> processing_order() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::processing_order>(kSpec, row_);
    }
        uint32_t is_container() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::is_container>(kSpec, row_);
    }

    private:
      const TraceFileTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(std::optional<TraceFileTable::Id> _parent_id = {}, std::optional<StringPool::Id> _name = {}, int64_t _size = {}, StringPool::Id _trace_type = {}, std::optional<int64_t> _processing_order = {}, uint32_t _is_container = {}) : parent_id(std::move(_parent_id)), name(std::move(_name)), size(std::move(_size)), trace_type(std::move(_trace_type)), processing_order(std::move(_processing_order)), is_container(std::move(_is_container)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(parent_id, other.parent_id) && std::equal_to<>()(name, other.name) && std::equal_to<>()(size, other.size) && std::equal_to<>()(trace_type, other.trace_type) && std::equal_to<>()(processing_order, other.processing_order) && std::equal_to<>()(is_container, other.is_container);
    }

        std::optional<TraceFileTable::Id> parent_id;
    std::optional<StringPool::Id> name;
    int64_t size;
    StringPool::Id trace_type;
    std::optional<int64_t> processing_order;
    uint32_t is_container;
  };

  explicit TraceFileTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.parent_id ? std::make_optional(row.parent_id->value) : std::nullopt, row.name, row.size, std::make_optional(row.trace_type), row.processing_order, row.is_container);
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
    return "__intrinsic_trace_file";
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
static_assert(sizeof(TraceFileTable) == sizeof(dataframe::Dataframe));



class TraceImportLogsTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","trace_id","ts","byte_offset","stat_key","arg_set_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::NonNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::SparseNullWithPopcountUntilFinalization{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = TraceImportLogsTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(TraceImportLogsTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const TraceImportLogsTable& table) const {
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
    static constexpr uint32_t trace_id = 1;
    static constexpr uint32_t ts = 2;
    static constexpr uint32_t byte_offset = 3;
    static constexpr uint32_t stat_key = 4;
    static constexpr uint32_t arg_set_id = 5;
  };
  struct RowReference {
   public:
    explicit RowReference(TraceImportLogsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    TraceImportLogsTable::Id id() const {
        
        return TraceImportLogsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
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
    TraceImportLogsTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const TraceImportLogsTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    TraceImportLogsTable::Id id() const {
        
        return TraceImportLogsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const TraceImportLogsTable* table_;
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
    TraceImportLogsTable::Id id() const {
        
        return TraceImportLogsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    TraceImportLogsTable::Id id() const {
        
        return TraceImportLogsTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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
      explicit Iterator(TraceImportLogsTable* table) : table_(table) {
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
      TraceImportLogsTable::Id id() const {
        
        return TraceImportLogsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
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
      TraceImportLogsTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const TraceImportLogsTable* table) : table_(table) {
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
      TraceImportLogsTable::Id id() const {
        
        return TraceImportLogsTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
        std::optional<uint32_t> arg_set_id() const {
      PERFETTO_DCHECK(!table_->dataframe_.finalized());
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::arg_set_id>(kSpec, row_);
    }

    private:
      const TraceImportLogsTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(TraceFileTable::Id _trace_id = {}, std::optional<int64_t> _ts = {}, std::optional<int64_t> _byte_offset = {}, int64_t _stat_key = {}, std::optional<uint32_t> _arg_set_id = {}) : trace_id(std::move(_trace_id)), ts(std::move(_ts)), byte_offset(std::move(_byte_offset)), stat_key(std::move(_stat_key)), arg_set_id(std::move(_arg_set_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(trace_id, other.trace_id) && std::equal_to<>()(ts, other.ts) && std::equal_to<>()(byte_offset, other.byte_offset) && std::equal_to<>()(stat_key, other.stat_key) && std::equal_to<>()(arg_set_id, other.arg_set_id);
    }

        TraceFileTable::Id trace_id;
    std::optional<int64_t> ts;
    std::optional<int64_t> byte_offset;
    int64_t stat_key;
    std::optional<uint32_t> arg_set_id;
  };

  explicit TraceImportLogsTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), row.trace_id.value, row.ts, row.byte_offset, row.stat_key, row.arg_set_id);
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
    return "__intrinsic_trace_import_logs";
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
static_assert(sizeof(TraceImportLogsTable) == sizeof(dataframe::Dataframe));



class MetadataTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","name","key_type","int_value","str_value","machine_id","trace_id"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNullWithPopcountAlways{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Int64{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::Uint32{}, dataframe::DenseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = MetadataTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(MetadataTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const MetadataTable& table) const {
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
    static constexpr uint32_t key_type = 2;
    static constexpr uint32_t int_value = 3;
    static constexpr uint32_t str_value = 4;
    static constexpr uint32_t machine_id = 5;
    static constexpr uint32_t trace_id = 6;
  };
  struct RowReference {
   public:
    explicit RowReference(MetadataTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    MetadataTable::Id id() const {
        
        return MetadataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> str_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::str_value>(kSpec, row_);
      }
          std::optional<MachineTable::Id> machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_);
        return res ? std::make_optional(MachineTable::Id{*res}) : std::nullopt;
      }
          std::optional<TraceFileTable::Id> trace_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
    void set_int_value(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::int_value>(kSpec, row_, res);
    }
          void set_str_value(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::str_value>(kSpec, row_, res);
    }
          void set_machine_id(std::optional<MachineTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_, res_value);
      }
          void set_trace_id(std::optional<TraceFileTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_, res_value);
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    MetadataTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const MetadataTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    MetadataTable::Id id() const {
        
        return MetadataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> str_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::str_value>(kSpec, row_);
      }
          std::optional<MachineTable::Id> machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_);
        return res ? std::make_optional(MachineTable::Id{*res}) : std::nullopt;
      }
          std::optional<TraceFileTable::Id> trace_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const MetadataTable* table_;
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
    MetadataTable::Id id() const {
        
        return MetadataTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<int64_t> int_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::int_value>(kSpec);
    }
      std::optional<StringPool::Id> str_value() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::str_value>(kSpec);
      }
      std::optional<MachineTable::Id> machine_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::machine_id>(kSpec);
        return res ? std::make_optional(MachineTable::Id{*res}) : std::nullopt;
      }
      std::optional<TraceFileTable::Id> trace_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::trace_id>(kSpec);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
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

    MetadataTable::Id id() const {
        
        return MetadataTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
      StringPool::Id name() const {
        
        auto res = cursor_.GetCellUnchecked<ColumnIndex::name>(kSpec);
        return res ? *res : StringPool::Id::Null();
      }
    std::optional<int64_t> int_value() const {
      
      return cursor_.GetCellUnchecked<ColumnIndex::int_value>(kSpec);
    }
      std::optional<StringPool::Id> str_value() const {
        
        return cursor_.GetCellUnchecked<ColumnIndex::str_value>(kSpec);
      }
      std::optional<MachineTable::Id> machine_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::machine_id>(kSpec);
        return res ? std::make_optional(MachineTable::Id{*res}) : std::nullopt;
      }
      std::optional<TraceFileTable::Id> trace_id() const {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res = cursor_.GetCellUnchecked<ColumnIndex::trace_id>(kSpec);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
    void set_int_value(std::optional<int64_t> res) {
        
      cursor_.SetCellUnchecked<ColumnIndex::int_value>(kSpec, res);
    }
      void set_str_value(std::optional<StringPool::Id> res) {
        
        cursor_.SetCellUnchecked<ColumnIndex::str_value>(kSpec, res);
    }
      void set_machine_id(std::optional<MachineTable::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::machine_id>(kSpec, res_value);
      }
      void set_trace_id(std::optional<TraceFileTable::Id> res) {
        PERFETTO_DCHECK(!dataframe_->finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        cursor_.SetCellUnchecked<ColumnIndex::trace_id>(kSpec, res_value);
      }

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(MetadataTable* table) : table_(table) {
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
      MetadataTable::Id id() const {
        
        return MetadataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> str_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::str_value>(kSpec, row_);
      }
          std::optional<MachineTable::Id> machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_);
        return res ? std::make_optional(MachineTable::Id{*res}) : std::nullopt;
      }
          std::optional<TraceFileTable::Id> trace_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }
      void set_int_value(std::optional<int64_t> res) {
      
      table_->dataframe_.SetCellUnchecked<ColumnIndex::int_value>(kSpec, row_, res);
    }
          void set_str_value(std::optional<StringPool::Id> res) {
        
        table_->dataframe_.SetCellUnchecked<ColumnIndex::str_value>(kSpec, row_, res);
    }
          void set_machine_id(std::optional<MachineTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_, res_value);
      }
          void set_trace_id(std::optional<TraceFileTable::Id> res) {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res_value = res ? std::make_optional(res->value) : std::nullopt;
        table_->dataframe_.SetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_, res_value);
      }

    private:
      MetadataTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const MetadataTable* table) : table_(table) {
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
      MetadataTable::Id id() const {
        
        return MetadataTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
          StringPool::Id name() const {
        
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::name>(kSpec, row_);
        return res ? *res : StringPool::Id::Null();
      }
        std::optional<int64_t> int_value() const {
      
      return table_->dataframe_.template GetCellUnchecked<ColumnIndex::int_value>(kSpec, row_);
    }
          std::optional<StringPool::Id> str_value() const {
        
        return table_->dataframe_.template GetCellUnchecked<ColumnIndex::str_value>(kSpec, row_);
      }
          std::optional<MachineTable::Id> machine_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::machine_id>(kSpec, row_);
        return res ? std::make_optional(MachineTable::Id{*res}) : std::nullopt;
      }
          std::optional<TraceFileTable::Id> trace_id() const {
        PERFETTO_DCHECK(!table_->dataframe_.finalized());
        auto res = table_->dataframe_.template GetCellUnchecked<ColumnIndex::trace_id>(kSpec, row_);
        return res ? std::make_optional(TraceFileTable::Id{*res}) : std::nullopt;
      }

    private:
      const MetadataTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _name = {}, StringPool::Id _key_type = {}, std::optional<int64_t> _int_value = {}, std::optional<StringPool::Id> _str_value = {}, std::optional<MachineTable::Id> _machine_id = {}, std::optional<TraceFileTable::Id> _trace_id = {}) : name(std::move(_name)), key_type(std::move(_key_type)), int_value(std::move(_int_value)), str_value(std::move(_str_value)), machine_id(std::move(_machine_id)), trace_id(std::move(_trace_id)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(name, other.name) && std::equal_to<>()(key_type, other.key_type) && std::equal_to<>()(int_value, other.int_value) && std::equal_to<>()(str_value, other.str_value) && std::equal_to<>()(machine_id, other.machine_id) && std::equal_to<>()(trace_id, other.trace_id);
    }

        StringPool::Id name;
    StringPool::Id key_type;
    std::optional<int64_t> int_value;
    std::optional<StringPool::Id> str_value;
    std::optional<MachineTable::Id> machine_id;
    std::optional<TraceFileTable::Id> trace_id;
  };

  explicit MetadataTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.name), std::make_optional(row.key_type), row.int_value, row.str_value, row.machine_id ? std::make_optional(row.machine_id->value) : std::nullopt, row.trace_id ? std::make_optional(row.trace_id->value) : std::nullopt);
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
    return "__intrinsic_metadata";
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
static_assert(sizeof(MetadataTable) == sizeof(dataframe::Dataframe));



class ModulesTable {
 public:
  static constexpr auto kSpec = dataframe::CreateTypedDataframeSpec(
    {"id","name"},
    dataframe::CreateTypedColumnSpec(dataframe::Id{}, dataframe::NonNull{}, dataframe::IdSorted{}, dataframe::NoDuplicates{}),
    dataframe::CreateTypedColumnSpec(dataframe::String{}, dataframe::SparseNull{}, dataframe::Unsorted{}, dataframe::HasDuplicates{}));

  using Id = ModulesTable_Id;
  struct RowReference;
  struct ConstRowReference;
  struct RowNumber {
   public:
    explicit constexpr RowNumber(uint32_t value) : value_(value) {}
    uint32_t row_number() const { return value_; }

    RowReference ToRowReference(ModulesTable* table) const {
      return RowReference(table, value_);
    }
    ConstRowReference ToRowReference(const ModulesTable& table) const {
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
  };
  struct RowReference {
   public:
    explicit RowReference(ModulesTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ModulesTable::Id id() const {
        
        return ModulesTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }

   private:
    friend struct ConstRowReference;
    ModulesTable* table_;
    uint32_t row_;
  };
  struct ConstRowReference {
   public:
    explicit ConstRowReference(const ModulesTable* table, uint32_t row)
        : table_(table), row_(row) {
        base::ignore_result(table_);
    }
    ConstRowReference(const RowReference& other)
        : table_(other.table_), row_(other.row_) {}
    ModulesTable::Id id() const {
        
        return ModulesTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
    RowNumber ToRowNumber() const {
      return RowNumber{row_};
    }
   private:
    const ModulesTable* table_;
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
    ModulesTable::Id id() const {
        
        return ModulesTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
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

    ModulesTable::Id id() const {
        
        return ModulesTable::Id{cursor_.GetCellUnchecked<ColumnIndex::id>(kSpec)};
      }
    

   private:
    dataframe::Dataframe* dataframe_;
    dataframe::TypedCursor cursor_;
  };
  class Iterator {
    public:
      explicit Iterator(ModulesTable* table) : table_(table) {
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
      ModulesTable::Id id() const {
        
        return ModulesTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }
      

    private:
      ModulesTable* table_;
      uint32_t row_ = 0;
  };
  class ConstIterator {
    public:
      explicit ConstIterator(const ModulesTable* table) : table_(table) {
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
      ModulesTable::Id id() const {
        
        return ModulesTable::Id{table_->dataframe_.template GetCellUnchecked<ColumnIndex::id>(kSpec, row_)};
      }

    private:
      const ModulesTable* table_;
      uint32_t row_ = 0;
  };
  struct IdAndRow {
    Id id;
    RowNumber row_number;
    uint32_t row;
    RowReference row_reference;
  };
  
  struct Row {
    Row(StringPool::Id _name = {}) : name(std::move(_name)) {}

    bool operator==(const Row& other) const {
      return std::equal_to<>()(name, other.name);
    }

        StringPool::Id name;
  };

  explicit ModulesTable(StringPool* pool)
      : dataframe_(
        dataframe::Dataframe::CreateFromTypedSpec(kSpec, pool)) {}

  template <typename = void>
  IdAndRow Insert(const Row& row) {
    uint32_t row_count = dataframe_.row_count();
    dataframe_.InsertUnchecked(kSpec, std::monostate(), std::make_optional(row.name));
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
    return "__intrinsic_modules";
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
static_assert(sizeof(ModulesTable) == sizeof(dataframe::Dataframe));


}  // namespace perfetto::trace_processor::tables

#endif  // SRC_TRACE_PROCESSOR_TABLES_METADATA_TABLES_PY_H_

