// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gfx/font_fallback_linux.h"
#include "ui/gfx/font_list.h"

namespace gfx {

size_t GetFallbackFontEntriesCacheSizeForTesting() {
  return 0;
}

size_t GetFallbackFontListCacheSizeForTesting() {
  return 0;
}

void ClearAllFontFallbackCachesForTesting() {}

FallbackFontData::FallbackFontData() = default;

FallbackFontData::FallbackFontData(const FallbackFontData& other) = default;

FallbackFontData& FallbackFontData::operator=(const FallbackFontData& other) =
    default;

bool GetFallbackFontForChar(UChar32,
                            const std::string&,
                            FallbackFontData*) {
  return false;
}

std::string FontList::FirstAvailableOrFirst(std::string_view font_name_list) {
  return std::string(font_name_list);
}

}  // namespace gfx
