// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/standalone_process.h"

#include <cstdio>
#include <cstring>
#include <mutex>

#include "base/check.h"
#include "base/i18n/icu_util.h"

#if defined(_WIN32)
#include <cstdlib>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

namespace html_css_renderer {

#if defined(_WIN32)
namespace {

char g_standalone_crash_breadcrumb[512] = "(startup)";
bool g_exception_handler_installed = false;

LONG WINAPI StandaloneUnhandledExceptionFilter(EXCEPTION_POINTERS* exception) {
  const DWORD code = exception && exception->ExceptionRecord
                         ? exception->ExceptionRecord->ExceptionCode
                         : 0;
  if (code == DBG_PRINTEXCEPTION_C || code == 0xe06d7363) {
    return EXCEPTION_CONTINUE_SEARCH;
  }
  const void* address = exception && exception->ExceptionRecord
                            ? exception->ExceptionRecord->ExceptionAddress
                            : nullptr;
  const void* module_base = GetModuleHandle(nullptr);
  HMODULE fault_module = nullptr;
  char fault_module_path[MAX_PATH] = {};
  if (address) {
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       static_cast<const char*>(address), &fault_module);
    if (fault_module) {
      GetModuleFileNameA(fault_module, fault_module_path,
                         static_cast<DWORD>(sizeof(fault_module_path)));
    }
  }
  std::fprintf(stderr,
               "standalone_crash exception=0x%08lx address=%p module_base=%p "
               "fault_module=%p fault_module_path=%s breadcrumb=%s\n",
               static_cast<unsigned long>(code), address, module_base,
               fault_module, fault_module_path[0] ? fault_module_path : "",
               g_standalone_crash_breadcrumb);
  void* stack[64] = {};
  const USHORT frame_count = CaptureStackBackTrace(0, 64, stack, nullptr);
  std::fprintf(stderr, "standalone_crash_stack frames=%hu", frame_count);
  for (USHORT i = 0; i < frame_count; ++i) {
    std::fprintf(stderr, " %p", stack[i]);
  }
  std::fprintf(stderr, "\n");
  std::fflush(stderr);
  return EXCEPTION_CONTINUE_SEARCH;
}

}  // namespace
#endif

void SetStandaloneCrashBreadcrumb(const char* stage) {
#if defined(_WIN32)
  const char* value = stage && stage[0] ? stage : "(null)";
  std::strncpy(g_standalone_crash_breadcrumb, value,
               sizeof(g_standalone_crash_breadcrumb) - 1);
  g_standalone_crash_breadcrumb[sizeof(g_standalone_crash_breadcrumb) - 1] =
      '\0';
#else
  (void)stage;
#endif
}

void ConfigureStandaloneToolProcess() {
#if defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX |
               SEM_NOOPENFILEERRORBOX);
  _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
  if (!g_exception_handler_installed) {
    AddVectoredExceptionHandler(/*First=*/1, StandaloneUnhandledExceptionFilter);
    g_exception_handler_installed = true;
  }
#endif
}

void InitializeStandaloneIcu() {
  static std::once_flag once;
  std::call_once(once, [] { CHECK(base::i18n::InitializeICU()); });
}

}  // namespace html_css_renderer

extern "C" void HtmlCssRendererStandaloneSetCrashBreadcrumb(const char* stage) {
  html_css_renderer::SetStandaloneCrashBreadcrumb(stage);
}
