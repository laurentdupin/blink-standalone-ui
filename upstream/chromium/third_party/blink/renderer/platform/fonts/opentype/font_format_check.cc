// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/fonts/opentype/font_format_check.h"

#include "base/containers/span.h"
#if !defined(STANDALONE_RENDERER_NO_RUST)
#include "base/containers/span_rust.h"
#include "third_party/blink/renderer/platform/fonts/opentype/format_check.rs.h"
#endif

#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "third_party/skia/include/core/SkTypeface.h"

namespace blink {

#if defined(STANDALONE_RENDERER_NO_RUST)
namespace {

uint16_t ReadU16(base::span<const uint8_t> data, size_t offset) {
  return (static_cast<uint16_t>(data[offset]) << 8) |
         static_cast<uint16_t>(data[offset + 1]);
}

uint32_t ReadU32(base::span<const uint8_t> data, size_t offset) {
  return (static_cast<uint32_t>(data[offset]) << 24) |
         (static_cast<uint32_t>(data[offset + 1]) << 16) |
         (static_cast<uint32_t>(data[offset + 2]) << 8) |
         static_cast<uint32_t>(data[offset + 3]);
}

uint32_t Tag(const char tag[4]) {
  return SkSetFourByteTag(tag[0], tag[1], tag[2], tag[3]);
}

struct TableInfo {
  size_t offset = 0;
  size_t length = 0;
  bool found = false;
};

TableInfo FindTable(base::span<const uint8_t> data, uint32_t tag) {
  if (data.size() < 12)
    return {};

  const uint16_t num_tables = ReadU16(data, 4);
  const size_t table_directory_offset = 12;
  const size_t table_record_size = 16;
  if (data.size() < table_directory_offset ||
      num_tables > (data.size() - table_directory_offset) / table_record_size) {
    return {};
  }

  for (uint16_t i = 0; i < num_tables; ++i) {
    const size_t record = table_directory_offset + i * table_record_size;
    if (ReadU32(data, record) != tag)
      continue;
    const size_t offset = ReadU32(data, record + 8);
    const size_t length = ReadU32(data, record + 12);
    if (offset > data.size() || length > data.size() - offset)
      return {};
    return {offset, length, true};
  }

  return {};
}

bool HasTable(base::span<const uint8_t> data, const char tag[4]) {
  return FindTable(data, Tag(tag)).found;
}

bool ColrTableIsVersion1(base::span<const uint8_t> data) {
  const TableInfo table = FindTable(data, Tag("COLR"));
  return table.found && table.length >= 2 && ReadU16(data, table.offset) >= 1;
}

}  // namespace

FontFormatCheck::FontFormatCheck(sk_sp<SkData> sk_data) {
  auto bytes = base::span(static_cast<const uint8_t*>(sk_data->data()),
                          sk_data->size());
  has_fvar_ = HasTable(bytes, "fvar");
  has_cbdt_ = HasTable(bytes, "CBDT");
  has_cblc_ = HasTable(bytes, "CBLC");
  has_colr_ = HasTable(bytes, "COLR");
  has_cpal_ = HasTable(bytes, "CPAL");
  has_colr_v1_ = ColrTableIsVersion1(bytes);
  has_sbix_ = HasTable(bytes, "sbix");
  has_cff2_ = HasTable(bytes, "CFF2");
  has_avar2_ = HasTable(bytes, "avar");
}

bool FontFormatCheck::IsVariableFont() const {
  return has_fvar_;
}

bool FontFormatCheck::IsCbdtCblcColorFont() const {
  return has_cbdt_ && has_cblc_;
}

bool FontFormatCheck::IsColrCpalColorFontV0() const {
  return has_colr_ && has_cpal_ && !has_colr_v1_;
}

bool FontFormatCheck::IsColrCpalColorFontV1() const {
  return has_colr_ && has_cpal_ && has_colr_v1_;
}

bool FontFormatCheck::IsSbixColorFont() const {
  return has_sbix_;
}

bool FontFormatCheck::IsCff2OutlineFont() const {
  return has_cff2_;
}

#else

FontFormatCheck::FontFormatCheck(sk_sp<SkData> sk_data)
    : format_info_(font_format_check::get_font_format_info(
          base::SpanToRustSlice(sk_data->byteSpan()))) {}

bool FontFormatCheck::IsVariableFont() const {
  return font_format_check::is_variable(*format_info_);
}

bool FontFormatCheck::IsCbdtCblcColorFont() const {
  return font_format_check::is_cbdt_cblc(*format_info_);
}

bool FontFormatCheck::IsColrCpalColorFontV0() const {
  return font_format_check::is_colrv0(*format_info_);
}

bool FontFormatCheck::IsColrCpalColorFontV1() const {
  return font_format_check::is_colrv1(*format_info_);
}

bool FontFormatCheck::IsSbixColorFont() const {
  return font_format_check::is_sbix(*format_info_);
}

bool FontFormatCheck::IsCff2OutlineFont() const {
  return font_format_check::is_cff2(*format_info_);
}

#endif

bool FontFormatCheck::IsVariableColrV0Font() const {
  return IsColrCpalColorFontV0() && IsVariableFont();
}

bool FontFormatCheck::IsColorFont() const {
  return IsSbixColorFont() || IsCbdtCblcColorFont() ||
         IsColrCpalColorFontV0() || IsColrCpalColorFontV1();
}

bool FontFormatCheck::IsAvar2Font() const {
  return RuntimeEnabledFeatures::FontFormatAvar2Enabled() &&
#if defined(STANDALONE_RENDERER_NO_RUST)
         has_avar2_;
#else
         font_format_check::is_avar2(*format_info_);
#endif
}

FontFormatCheck::VariableFontSubType FontFormatCheck::ProbeVariableFont(
    sk_sp<SkTypeface> typeface) {
  if (!typeface->getTableSize(
          SkFontTableTag(SkSetFourByteTag('f', 'v', 'a', 'r'))))
    return VariableFontSubType::kNotVariable;

  if (typeface->getTableSize(
          SkFontTableTag(SkSetFourByteTag('C', 'F', 'F', '2'))))
    return VariableFontSubType::kVariableCFF2;
  return VariableFontSubType::kVariableTrueType;
}

}  // namespace blink
