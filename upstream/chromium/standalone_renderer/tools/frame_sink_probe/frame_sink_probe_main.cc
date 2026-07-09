// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "standalone_renderer/tools/frame_sink_probe/chromium_frame_sink_probe.h"

namespace {

bool ParseViewport(const std::string& value, int* width, int* height) {
  const size_t separator = value.find('x');
  if (separator == std::string::npos) {
    return false;
  }
  char* width_end = nullptr;
  char* height_end = nullptr;
  const long parsed_width = std::strtol(value.c_str(), &width_end, 10);
  const long parsed_height =
      std::strtol(value.c_str() + separator + 1, &height_end, 10);
  if (width_end != value.c_str() + separator ||
      height_end != value.c_str() + value.size() || parsed_width <= 0 ||
      parsed_height <= 0) {
    return false;
  }
  *width = static_cast<int>(std::min<long>(parsed_width, 16384));
  *height = static_cast<int>(std::min<long>(parsed_height, 16384));
  return true;
}

void PrintUsage() {
  std::fprintf(stderr,
               "Usage: blink_standalone_frame_sink_probe "
               "[--chromium-async-frame-sink-probe|"
               "--chromium-root-frame-sink-probe] [--viewport WxH]\n");
}

void InitializeFeatureList() {
  if (!base::FeatureList::GetInstance()) {
    base::FeatureList::InitInstance(
        base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
            switches::kEnableFeatures),
        base::CommandLine::ForCurrentProcess()->GetSwitchValueASCII(
            switches::kDisableFeatures),
        {});
  }
}

bool JsonReportsSuccess(const std::string& json) {
  return json.find("\"success\": true") != std::string::npos;
}

}  // namespace

int main(int argc, char** argv) {
  base::CommandLine::Init(argc, argv);
  bool run_async_probe = false;
  bool run_root_probe = false;
  int width = 256;
  int height = 128;

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i] ? argv[i] : "";
    if (arg == "--chromium-async-frame-sink-probe") {
      run_async_probe = true;
    } else if (arg == "--chromium-root-frame-sink-probe") {
      run_root_probe = true;
    } else if (arg == "--viewport" && i + 1 < argc) {
      if (!ParseViewport(argv[++i], &width, &height)) {
        PrintUsage();
        return 2;
      }
    } else if (arg.rfind("--viewport=", 0) == 0) {
      if (!ParseViewport(arg.substr(11), &width, &height)) {
        PrintUsage();
        return 2;
      }
    } else {
      PrintUsage();
      return 2;
    }
  }

  if (!run_async_probe && !run_root_probe) {
    run_async_probe = true;
  }

  base::AtExitManager at_exit_manager;
  InitializeFeatureList();
  base::SingleThreadTaskExecutor main_task_executor(
      base::MessagePumpType::DEFAULT, /*is_main_thread=*/true);
  if (!base::ThreadPoolInstance::Get()) {
    base::ThreadPoolInstance::CreateAndStartWithDefaultParams(
        "blink_standalone_frame_sink_probe");
  }

  const std::string result =
      run_async_probe
          ? html_css_renderer::RunChromiumAsyncFrameSinkProof(width, height)
          : html_css_renderer::RunChromiumRootFrameSinkProof(width, height);
  std::printf("%s", result.c_str());
  return JsonReportsSuccess(result) ? 0 : 1;
}
