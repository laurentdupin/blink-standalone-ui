// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/base_paths.h"

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/path_service.h"
#include "base/process/process_metrics.h"

namespace base {

bool PathProviderPosix(int key, FilePath* result) {
  switch (key) {
    case FILE_EXE:
    case FILE_MODULE:
      return ReadSymbolicLink(FilePath(kProcSelfExe), result);
    case DIR_EXE:
    case DIR_MODULE:
    case DIR_ASSETS: {
      FilePath exe_path;
      if (!PathService::Get(FILE_EXE, &exe_path)) {
        return false;
      }
      *result = exe_path.DirName();
      return true;
    }
    case DIR_TEMP:
      *result = FilePath("/tmp");
      return true;
    case DIR_HOME: {
      const char* home = getenv("HOME");
      if (!home || !*home) {
        return false;
      }
      *result = FilePath(home);
      return true;
    }
    case DIR_CURRENT: {
      char cwd[PATH_MAX];
      if (!getcwd(cwd, sizeof(cwd))) {
        return false;
      }
      *result = FilePath(cwd);
      return true;
    }
    case DIR_USER_DESKTOP: {
      FilePath home;
      if (!PathService::Get(DIR_HOME, &home)) {
        return false;
      }
      *result = home.Append("Desktop");
      return true;
    }
    case DIR_SRC_TEST_DATA_ROOT:
    case DIR_OUT_TEST_DATA_ROOT:
    case DIR_GEN_TEST_DATA_ROOT:
    case DIR_TEST_DATA:
      return PathService::Get(DIR_EXE, result);
  }
  return false;
}

}  // namespace base
