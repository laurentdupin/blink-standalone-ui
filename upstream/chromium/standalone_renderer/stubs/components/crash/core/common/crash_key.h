// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_COMPONENTS_CRASH_CORE_COMMON_CRASH_KEY_H_
#define STANDALONE_RENDERER_STUBS_COMPONENTS_CRASH_CORE_COMMON_CRASH_KEY_H_

#include <cstdint>
#include <string>
#include <string_view>

namespace base::debug {
class StackTrace;
}  // namespace base::debug

namespace crash_reporter {

template <uint32_t MaxLength>
class CrashKeyString {
 public:
  explicit CrashKeyString(const char*) {}
  CrashKeyString(const CrashKeyString&) = delete;
  CrashKeyString& operator=(const CrashKeyString&) = delete;

  void Set(std::string_view) {}
  void Clear() {}
};

class ScopedCrashKeyString {
 public:
  template <class T>
  ScopedCrashKeyString(T*, std::string_view) {}
  ScopedCrashKeyString(const ScopedCrashKeyString&) = delete;
  ScopedCrashKeyString& operator=(const ScopedCrashKeyString&) = delete;
  ~ScopedCrashKeyString() = default;
};

template <uint32_t Size>
void SetCrashKeyStringToStackTrace(CrashKeyString<Size>*,
                                   const base::debug::StackTrace&) {}

inline void InitializeCrashKeys() {}

}  // namespace crash_reporter

#endif  // STANDALONE_RENDERER_STUBS_COMPONENTS_CRASH_CORE_COMMON_CRASH_KEY_H_
