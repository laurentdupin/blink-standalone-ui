// Copyright 2017 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_PLATFORM_FONTS_OPENTYPE_FONT_FORMAT_CHECK_H_
#define THIRD_PARTY_BLINK_RENDERER_PLATFORM_FONTS_OPENTYPE_FONT_FORMAT_CHECK_H_

#include "third_party/blink/renderer/platform/platform_export.h"
#include "third_party/blink/renderer/platform/wtf/allocator/allocator.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkRefCnt.h"
#include "third_party/skia/include/core/SkTypeface.h"

#if !defined(STANDALONE_RENDERER_NO_RUST)
#include "third_party/blink/renderer/platform/fonts/opentype/format_check.rs.h"
#endif

namespace blink {

class PLATFORM_EXPORT FontFormatCheck {
  STACK_ALLOCATED();

 public:
  explicit FontFormatCheck(sk_sp<SkData>);
  virtual ~FontFormatCheck() = default;
  virtual bool IsVariableFont() const;
  virtual bool IsCbdtCblcColorFont() const;
  virtual bool IsColrCpalColorFont() const {
    return IsColrCpalColorFontV0() || IsColrCpalColorFontV1();
  }
  virtual bool IsColrCpalColorFontV0() const;
  virtual bool IsColrCpalColorFontV1() const;
  bool IsVariableColrV0Font() const;
  virtual bool IsSbixColorFont() const;
  virtual bool IsCff2OutlineFont() const;
  bool IsColorFont() const;
  bool IsAvar2Font() const;

  // Still needed in FontCustomPlatformData.
  enum class VariableFontSubType {
    kNotVariable,
    kVariableTrueType,
    kVariableCFF2
  };

  static VariableFontSubType ProbeVariableFont(sk_sp<SkTypeface>);

  // hb-common.h: typedef uint32_t hb_tag_t;
  using TableTagsVector = Vector<uint32_t>;

  enum class COLRVersion { kCOLRV0, kCOLRV1, kNoCOLR };

 private:
#if defined(STANDALONE_RENDERER_NO_RUST)
  bool has_fvar_ = false;
  bool has_cbdt_ = false;
  bool has_cblc_ = false;
  bool has_colr_ = false;
  bool has_cpal_ = false;
  bool has_colr_v1_ = false;
  bool has_sbix_ = false;
  bool has_cff2_ = false;
  bool has_avar2_ = false;
#else
  rust::Box<font_format_check::FontFormatInfo> format_info_;
#endif
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_PLATFORM_FONTS_OPENTYPE_FONT_FORMAT_CHECK_H_
