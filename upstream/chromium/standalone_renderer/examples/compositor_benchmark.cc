#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/message_loop/message_pump_type.h"
#include "base/task/single_thread_task_executor.h"
#include "base/trace_event/trace_event_impl.h"
#include "gpu/command_buffer/service/gpu_switches.h"
#include "html_css_renderer/compositor_runtime.h"
#include "html_css_renderer/css_file_loader.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "third_party/perfetto/include/perfetto/tracing/tracing.h"
#include "ui/gl/gl_switches.h"

namespace {

bool ReadTextFile(const std::string& path, std::string* out) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    return false;
  std::ostringstream buffer;
  buffer << file.rdbuf();
  *out = buffer.str();
  return true;
}

std::string EscapeJson(const std::string& value) {
  std::string out;
  out.reserve(value.size() + 8);
  for (const char c : value) {
    switch (c) {
      case '\\':
        out += "\\\\";
        break;
      case '"':
        out += "\\\"";
        break;
      case '\n':
        out += "\\n";
        break;
      case '\r':
        out += "\\r";
        break;
      case '\t':
        out += "\\t";
        break;
      default:
        out += c;
        break;
    }
  }
  return out;
}

bool ParseViewport(const std::string& value, html_css_renderer::Size* size) {
  const size_t x = value.find('x');
  if (x == std::string::npos)
    return false;
  try {
    size->width = std::stof(value.substr(0, x));
    size->height = std::stof(value.substr(x + 1));
  } catch (...) {
    return false;
  }
  return size->width > 0.0f && size->height > 0.0f;
}

std::vector<std::string> SplitCommaList(const std::string& value) {
  std::vector<std::string> out;
  size_t start = 0;
  while (start <= value.size()) {
    const size_t comma = value.find(',', start);
    const size_t end = comma == std::string::npos ? value.size() : comma;
    std::string item = value.substr(start, end - start);
    while (!item.empty() &&
           (item.front() == ' ' || item.front() == '\t' ||
            item.front() == '\r' || item.front() == '\n')) {
      item.erase(item.begin());
    }
    while (!item.empty() &&
           (item.back() == ' ' || item.back() == '\t' ||
            item.back() == '\r' || item.back() == '\n')) {
      item.pop_back();
    }
    if (!item.empty())
      out.push_back(item);
    if (comma == std::string::npos)
      break;
    start = comma + 1;
  }
  return out;
}

bool ParseNonNegativeInt(const std::string& value, int* out) {
  try {
    size_t consumed = 0;
    const int parsed = std::stoi(value, &consumed);
    if (consumed != value.size() || parsed < 0)
      return false;
    *out = parsed;
    return true;
  } catch (...) {
    return false;
  }
}

void PrintUsage() {
  std::fprintf(
      stderr,
      "Usage: blink_standalone_render_benchmark_skia --html <markup>|--html-file <path> "
      "[--css <css>|--css-file <path>] [--viewport WxH] [--json <path>] "
      "[--paint-artifact-dump <path>] [--resource-root <dir>] "
      "[--trace-stages] [--lifecycle-stop <stage>] "
      "[--warm-iterations N] [--warm-scenario name[,name...]]\n"
      "This target now exercises the Chromium compositor path only. CPU BMP "
      "readback is removed from production; --out is intentionally unsupported "
      "until Viz/GPU readback is wired.\n");
}

bool FeatureSwitchContains(const std::string& enabled_features,
                           const char* feature_name) {
  size_t start = 0;
  while (start <= enabled_features.size()) {
    const size_t comma = enabled_features.find(',', start);
    const size_t end =
        comma == std::string::npos ? enabled_features.size() : comma;
    std::string token = enabled_features.substr(start, end - start);
    const size_t params = token.find_first_of("<:");
    if (params != std::string::npos)
      token = token.substr(0, params);
    if (token == feature_name)
      return true;
    if (comma == std::string::npos)
      break;
    start = comma + 1;
  }
  return false;
}

void AppendFeatureSwitchIfMissing(base::CommandLine* command_line,
                                  const char* feature_name) {
  std::string enabled_features =
      command_line->GetSwitchValueASCII(switches::kEnableFeatures);
  if (FeatureSwitchContains(enabled_features, feature_name)) {
    return;
  }
  if (!enabled_features.empty())
    enabled_features += ",";
  enabled_features += feature_name;
  command_line->AppendSwitchASCII(switches::kEnableFeatures, enabled_features);
}

void ApplyStandaloneGpuDefaults() {
  base::CommandLine* command_line = base::CommandLine::ForCurrentProcess();
  if (!command_line->HasSwitch(switches::kUseGL) &&
      !command_line->HasSwitch(switches::kUseANGLE)) {
    command_line->AppendSwitchASCII(switches::kUseGL,
                                    gl::kGLImplementationANGLEName);
    command_line->AppendSwitchASCII(switches::kUseANGLE,
                                    gl::kANGLEImplementationVulkanName);
  }
  if (!command_line->HasSwitch(switches::kUseVulkan)) {
    command_line->AppendSwitchASCII(switches::kUseVulkan,
                                    switches::kVulkanImplementationNameNative);
  }
  AppendFeatureSwitchIfMissing(command_line, "Vulkan");
}

void InitializeStandaloneFeatureList() {
  if (base::FeatureList::GetInstance())
    return;
  const base::CommandLine* command_line =
      base::CommandLine::ForCurrentProcess();
  base::FeatureList::InitInstance(
      command_line->GetSwitchValueASCII(switches::kEnableFeatures),
      command_line->GetSwitchValueASCII(switches::kDisableFeatures),
      {});
}

bool IsChromiumGpuSwitch(const std::string& arg, bool* consumes_value) {
  *consumes_value = false;
  const size_t equals = arg.find('=');
  const std::string name = equals == std::string::npos ? arg : arg.substr(0, equals);
  const bool has_inline_value = equals != std::string::npos;
  static constexpr const char* kValueSwitches[] = {
      "--use-gl",
      "--use-angle",
      "--use-vulkan",
      "--use-cmd-decoder",
      "--enable-angle-features",
      "--disable-angle-features",
      "--enable-features",
      "--disable-features",
      "--disable-gpu-driver-bug-workarounds",
      "--gpu-program-cache-size-kb",
      "--force-gpu-mem-discardable-limit-mb",
      "--force-max-texture-size",
  };
  static constexpr const char* kFlagSwitches[] = {
      "--disable-gpu-vsync",
      "--enable-gpu-service-logging",
      "--enable-gpu-service-tracing",
      "--disable-gl-drawing-for-tests",
      "--gpu-no-context-lost",
      "--disable-direct-composition",
      "--enable-unsafe-swiftshader",
      "--disable-vulkan-surface",
      "--disable-gpu-program-cache",
      "--disable-gpu-driver-bug-workarounds",
  };
  for (const char* value_switch : kValueSwitches) {
    if (name == value_switch) {
      *consumes_value = !has_inline_value;
      return true;
    }
  }
  for (const char* flag_switch : kFlagSwitches) {
    if (name == flag_switch)
      return true;
  }
  return false;
}

struct WarmFrameRecord {
  int iteration = 0;
  bool effective = true;
  double advance_frame_ms = 0.0;
  html_css_renderer::CompositorFrameResult result;
};

struct WarmScenarioRecord {
  std::string name;
  std::vector<WarmFrameRecord> frames;
};

html_css_renderer::FrameInput MakeBaseWarmInput(
    const html_css_renderer::RendererSnapshot& snapshot,
    int iteration) {
  html_css_renderer::FrameInput input;
  input.delta_time_seconds = 1.0 / 60.0;
  input.timeline_time_seconds = (iteration + 2) / 60.0;
  input.viewport = snapshot.viewport;
  input.element_attributes_by_id_and_name =
      snapshot.element_attributes_by_id_and_name;
  input.scroll_offsets_by_element_id = snapshot.scroll_offsets_by_element_id;
  input.focused_element_id = snapshot.focused_element_id;
  input.hovered_element_id = snapshot.hovered_element_id;
  input.active_element_id = snapshot.active_element_id;
  input.form_values_by_element_id = snapshot.form_values_by_element_id;
  return input;
}

html_css_renderer::FrameInput MakeWarmInput(
    const std::string& scenario,
    int iteration,
    const html_css_renderer::RendererSnapshot& snapshot,
    const html_css_renderer::CompositorFrameResult& previous_result,
    bool* effective) {
  html_css_renderer::FrameInput input = MakeBaseWarmInput(snapshot, iteration);
  *effective = true;
  if (scenario == "no-change") {
    return input;
  }
  if (scenario == "document-scroll") {
    const float max_y = previous_result.document_max_scroll_offset.y;
    if (max_y <= 0.0f) {
      *effective = false;
      return input;
    }
    const float target_y =
        std::min(max_y, (iteration % 2 == 0) ? 72.0f : 144.0f);
    input.scroll_offsets_by_element_id["document"] = {0.0f, target_y};
    return input;
  }
  if (scenario == "element-scroll") {
    for (const html_css_renderer::ScrollableElementEntry& entry :
         previous_result.scrollable_element_entries) {
      if (entry.can_scroll_y && entry.max_scroll_offset.y > 0.0f) {
        const float target_y =
            std::min(entry.max_scroll_offset.y,
                     (iteration % 2 == 0) ? 48.0f : 96.0f);
        input.scroll_offsets_by_element_id[entry.element_id] = {0.0f,
                                                                target_y};
        return input;
      }
    }
    *effective = false;
    return input;
  }
  if (scenario == "attr-toggle") {
    const std::string state = (iteration % 2 == 0) ? "on" : "off";
    input.element_attributes_by_id_and_name["card:data-state"] = state;
    input.element_attributes_by_id_and_name["target:data-state"] = state;
    input.element_attributes_by_id_and_name["png-card:data-state"] = state;
    input.element_attributes_by_id_and_name["svg-card:data-state"] = state;
    input.element_attributes_by_id_and_name["mask-card:data-state"] = state;
    return input;
  }
  if (scenario == "pointer-move") {
    input.pointers = {html_css_renderer::PointerState{
        1,
        html_css_renderer::Point{32.0f + static_cast<float>(iteration % 4) * 8.0f,
                                 32.0f},
        false}};
    return input;
  }
  if (scenario == "pointer-click") {
    input.pointers = {html_css_renderer::PointerState{
        1,
        html_css_renderer::Point{32.0f, 32.0f},
        iteration % 2 == 0}};
    return input;
  }
  if (scenario == "wheel-scroll") {
    input.wheel = html_css_renderer::WheelInput{
        html_css_renderer::Point{32.0f, 32.0f},
        html_css_renderer::Point{0.0f, iteration % 2 == 0 ? 48.0f : -48.0f}};
    return input;
  }
  *effective = false;
  return input;
}

double Percentile(std::vector<double> values, double percentile) {
  values.erase(std::remove_if(values.begin(), values.end(),
                              [](double value) { return value < 0.0; }),
               values.end());
  if (values.empty())
    return 0.0;
  std::sort(values.begin(), values.end());
  if (values.size() == 1)
    return values.front();
  const double rank = (values.size() - 1) * percentile;
  const size_t lower = static_cast<size_t>(rank);
  const size_t upper = std::min(values.size() - 1, lower + 1);
  const double fraction = rank - lower;
  return values[lower] + (values[upper] - values[lower]) * fraction;
}

std::vector<double> WarmDurations(const WarmScenarioRecord& scenario) {
  std::vector<double> values;
  values.reserve(scenario.frames.size());
  for (const WarmFrameRecord& frame : scenario.frames)
    values.push_back(frame.advance_frame_ms);
  return values;
}

int WarmFailureCount(const WarmScenarioRecord& scenario) {
  int failures = 0;
  for (const WarmFrameRecord& frame : scenario.frames) {
    const auto& result = frame.result;
    if (!result.paint_clean || !result.root_layer_available ||
        !result.cc_host_created || !result.cc_root_layer_attached ||
        !result.cc_commit_requested || !result.cc_frame_sink_requested ||
        !result.cc_frame_sink_bound || !result.gpu_context_created ||
        !result.raster_context_created ||
        !result.shared_image_interface_available ||
        !result.compositor_frame_submitted) {
      ++failures;
    }
  }
  return failures;
}

void WriteCompositorResultJsonFields(
    std::ofstream& file,
    const html_css_renderer::CompositorFrameResult& result,
    const std::string& indent,
    bool trailing_comma) {
  file << indent << "\"paint_clean\": " << (result.paint_clean ? "true" : "false")
       << ",\n";
  file << indent << "\"root_layer_available\": "
       << (result.root_layer_available ? "true" : "false") << ",\n";
  file << indent << "\"cc_host_created\": "
       << (result.cc_host_created ? "true" : "false") << ",\n";
  file << indent << "\"cc_root_layer_attached\": "
       << (result.cc_root_layer_attached ? "true" : "false") << ",\n";
  file << indent << "\"cc_commit_requested\": "
       << (result.cc_commit_requested ? "true" : "false") << ",\n";
  file << indent << "\"cc_frame_sink_requested\": "
       << (result.cc_frame_sink_requested ? "true" : "false") << ",\n";
  file << indent << "\"cc_frame_sink_bound\": "
       << (result.cc_frame_sink_bound ? "true" : "false") << ",\n";
  file << indent << "\"gpu_context_created\": "
       << (result.gpu_context_created ? "true" : "false") << ",\n";
  file << indent << "\"raster_context_created\": "
       << (result.raster_context_created ? "true" : "false") << ",\n";
  file << indent << "\"shared_image_interface_available\": "
       << (result.shared_image_interface_available ? "true" : "false")
       << ",\n";
  file << indent << "\"compositor_frame_submitted\": "
       << (result.compositor_frame_submitted ? "true" : "false") << ",\n";
  file << indent << "\"viz_display_created\": "
       << (result.viz_display_created ? "true" : "false") << ",\n";
  file << indent << "\"skia_renderer_gpu_path_reached\": "
       << (result.skia_renderer_gpu_path_reached ? "true" : "false")
       << ",\n";
  file << indent << "\"compositor_layer_count\": "
       << result.compositor_layer_count << ",\n";
  file << indent << "\"paint_chunk_count\": " << result.paint_chunk_count
       << ",\n";
  file << indent << "\"display_item_count\": " << result.display_item_count
       << (trailing_comma ? ",\n" : "\n");
}

bool WriteJson(const std::string& path,
               const html_css_renderer::CompositorFrameResult& result,
               const std::vector<std::string>& init_diagnostics,
               const std::vector<WarmScenarioRecord>& warm_scenarios,
               double runtime_create_ms,
               double initialize_ms,
               double advance_frame_ms,
               double process_elapsed_ms) {
  std::ofstream file(path, std::ios::binary);
  if (!file)
    return false;
  file << "{\n";
  file << "  \"renderer_path\": \"blink_paint_artifact_compositor_cc_viz_gpu_vulkan\",\n";
  file << "  \"single_chromium_compositor_path\": true,\n";
  file << "  \"paint_clean\": " << (result.paint_clean ? "true" : "false")
       << ",\n";
  file << "  \"root_layer_available\": "
       << (result.root_layer_available ? "true" : "false") << ",\n";
  file << "  \"cc_host_created\": "
       << (result.cc_host_created ? "true" : "false") << ",\n";
  file << "  \"cc_root_layer_attached\": "
       << (result.cc_root_layer_attached ? "true" : "false") << ",\n";
  file << "  \"cc_commit_requested\": "
       << (result.cc_commit_requested ? "true" : "false") << ",\n";
  file << "  \"cc_frame_sink_requested\": "
       << (result.cc_frame_sink_requested ? "true" : "false") << ",\n";
  file << "  \"cc_frame_sink_bound\": "
       << (result.cc_frame_sink_bound ? "true" : "false") << ",\n";
  file << "  \"gpu_context_created\": "
       << (result.gpu_context_created ? "true" : "false") << ",\n";
  file << "  \"raster_context_created\": "
       << (result.raster_context_created ? "true" : "false") << ",\n";
  file << "  \"shared_image_interface_available\": "
       << (result.shared_image_interface_available ? "true" : "false")
       << ",\n";
  file << "  \"compositor_frame_submitted\": "
       << (result.compositor_frame_submitted ? "true" : "false") << ",\n";
  file << "  \"viz_display_created\": "
       << (result.viz_display_created ? "true" : "false") << ",\n";
  file << "  \"skia_renderer_gpu_path_reached\": "
       << (result.skia_renderer_gpu_path_reached ? "true" : "false")
       << ",\n";
  file << "  \"compositor_layer_count\": " << result.compositor_layer_count
       << ",\n";
  file << "  \"paint_chunk_count\": " << result.paint_chunk_count << ",\n";
  file << "  \"display_item_count\": " << result.display_item_count << ",\n";
  file << "  \"needs_begin_frame\": "
       << (result.needs_begin_frame ? "true" : "false") << ",\n";
  file << "  \"viewport\": {\"width\": "
       << result.successor_snapshot.viewport.width << ", \"height\": "
       << result.successor_snapshot.viewport.height << "},\n";
  file << "  \"hit_test_entry_count\": " << result.hit_test_entries.size()
       << ",\n";
  file << "  \"scrollable_element_count\": "
       << result.scrollable_element_entries.size() << ",\n";
  file << "  \"timing\": {\n";
  file << "    \"runtime_create_ms\": " << runtime_create_ms << ",\n";
  file << "    \"initialize_ms\": " << initialize_ms << ",\n";
  file << "    \"advance_frame_ms\": " << advance_frame_ms << ",\n";
  file << "    \"process_elapsed_ms\": " << process_elapsed_ms << "\n";
  file << "  },\n";
  file << "  \"warm_scenarios\": [\n";
  for (size_t i = 0; i < warm_scenarios.size(); ++i) {
    const WarmScenarioRecord& scenario = warm_scenarios[i];
    std::vector<double> durations = WarmDurations(scenario);
    file << "    {\n";
    file << "      \"scenario\": \"" << EscapeJson(scenario.name) << "\",\n";
    file << "      \"frame_count\": " << scenario.frames.size() << ",\n";
    file << "      \"failure_count\": " << WarmFailureCount(scenario)
         << ",\n";
    file << "      \"advance_frame_ms\": {\"p50\": "
         << Percentile(durations, 0.50) << ", \"p95\": "
         << Percentile(durations, 0.95) << ", \"max\": "
         << (durations.empty() ? 0.0
                               : *std::max_element(durations.begin(),
                                                   durations.end()))
         << "},\n";
    file << "      \"frames\": [\n";
    for (size_t frame_index = 0; frame_index < scenario.frames.size();
         ++frame_index) {
      const WarmFrameRecord& frame = scenario.frames[frame_index];
      file << "        {\n";
      file << "          \"iteration\": " << frame.iteration << ",\n";
      file << "          \"effective\": "
           << (frame.effective ? "true" : "false") << ",\n";
      file << "          \"advance_frame_ms\": " << frame.advance_frame_ms
           << ",\n";
      WriteCompositorResultJsonFields(file, frame.result, "          ",
                                      /*trailing_comma=*/false);
      file << "        }"
           << (frame_index + 1 == scenario.frames.size() ? "\n" : ",\n");
    }
    file << "      ]\n";
    file << "    }" << (i + 1 == warm_scenarios.size() ? "\n" : ",\n");
  }
  file << "  ],\n";
  file << "  \"diagnostics\": [\n";
  bool first = true;
  const auto write_diag = [&](const std::string& diagnostic) {
    if (!first)
      file << ",\n";
    first = false;
    file << "    \"" << EscapeJson(diagnostic) << "\"";
  };
  for (const std::string& diagnostic : init_diagnostics)
    write_diag(diagnostic);
  for (const std::string& diagnostic : result.diagnostics)
    write_diag(diagnostic);
  file << "\n  ]\n";
  file << "}\n";
  return true;
}

}  // namespace

int main(int argc, char** argv) {
  const auto process_start = std::chrono::steady_clock::now();
  base::CommandLine::Init(argc, argv);
  ApplyStandaloneGpuDefaults();
  base::AtExitManager at_exit_manager;
  InitializeStandaloneFeatureList();
  base::SingleThreadTaskExecutor main_task_executor(
      base::MessagePumpType::DEFAULT, /*is_main_thread=*/true);
  if (!perfetto::Tracing::IsInitialized())
    base::trace_event::InitializeInProcessPerfettoBackend();

  html_css_renderer::RendererCreateInfo renderer;
  renderer.viewport = {800.0f, 600.0f};
  std::string html_file;
  std::string css;
  std::string css_file;
  std::string json_path;
  std::string paint_artifact_dump_path;
  std::string resource_root;
  std::string resource_base_path;
  bool trace_stages = false;
  std::string lifecycle_stop;
  bool unsupported_out_requested = false;
  int warm_iterations = 0;
  std::vector<std::string> warm_scenarios;

  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    const auto next_value = [&]() -> const char* {
      if (i + 1 >= argc)
        return nullptr;
      return argv[++i];
    };
    if (arg == "--help" || arg == "-h") {
      PrintUsage();
      return 0;
    } else if (arg == "--html") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      renderer.html = value;
    } else if (arg.rfind("--html=", 0) == 0) {
      renderer.html = arg.substr(7);
    } else if (arg == "--html-file") {
      const char* value = next_value();
      if (!value || !ReadTextFile(value, &renderer.html)) {
        std::fprintf(stderr, "failed to read --html-file\n");
        return 2;
      }
      html_file = value;
    } else if (arg.rfind("--html-file=", 0) == 0) {
      html_file = arg.substr(12);
      if (!ReadTextFile(html_file, &renderer.html)) {
        std::fprintf(stderr, "failed to read --html-file: %s\n",
                     html_file.c_str());
        return 2;
      }
    } else if (arg == "--css") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      css = value;
    } else if (arg == "--css-file") {
      const char* value = next_value();
      if (!value || !ReadTextFile(value, &css)) {
        std::fprintf(stderr, "failed to read --css-file\n");
        return 2;
      }
      css_file = value;
    } else if (arg == "--viewport") {
      const char* value = next_value();
      if (!value || !ParseViewport(value, &renderer.viewport)) {
        std::fprintf(stderr, "invalid --viewport\n");
        return 2;
      }
    } else if (arg.rfind("--viewport=", 0) == 0) {
      if (!ParseViewport(arg.substr(11), &renderer.viewport)) {
        std::fprintf(stderr, "invalid --viewport\n");
        return 2;
      }
    } else if (arg == "--json") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      json_path = value;
    } else if (arg.rfind("--json=", 0) == 0) {
      json_path = arg.substr(7);
    } else if (arg == "--paint-artifact-dump") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      paint_artifact_dump_path = value;
    } else if (arg == "--resource-root") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      resource_root = value;
    } else if (arg == "--resource-base-path") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      resource_base_path = value;
    } else if (arg == "--trace-stages") {
      trace_stages = true;
    } else if (arg == "--lifecycle-stop") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      lifecycle_stop = value;
    } else if (arg.rfind("--lifecycle-stop=", 0) == 0) {
      lifecycle_stop = arg.substr(17);
    } else if (arg == "--warm-iterations") {
      const char* value = next_value();
      if (!value || !ParseNonNegativeInt(value, &warm_iterations)) {
        std::fprintf(stderr, "invalid --warm-iterations\n");
        return 2;
      }
    } else if (arg.rfind("--warm-iterations=", 0) == 0) {
      if (!ParseNonNegativeInt(arg.substr(18), &warm_iterations)) {
        std::fprintf(stderr, "invalid --warm-iterations\n");
        return 2;
      }
    } else if (arg == "--warm-scenario" || arg == "--warm-scenarios") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      std::vector<std::string> parsed = SplitCommaList(value);
      warm_scenarios.insert(warm_scenarios.end(), parsed.begin(),
                            parsed.end());
    } else if (arg.rfind("--warm-scenario=", 0) == 0) {
      std::vector<std::string> parsed = SplitCommaList(arg.substr(16));
      warm_scenarios.insert(warm_scenarios.end(), parsed.begin(),
                            parsed.end());
    } else if (arg.rfind("--warm-scenarios=", 0) == 0) {
      std::vector<std::string> parsed = SplitCommaList(arg.substr(17));
      warm_scenarios.insert(warm_scenarios.end(), parsed.begin(),
                            parsed.end());
    } else if (arg == "--out" || arg.rfind("--out=", 0) == 0) {
      if (arg == "--out" && !next_value()) {
        PrintUsage();
        return 2;
      }
      unsupported_out_requested = true;
    } else if (arg == "--audit-only") {
      // Kept for script compatibility. The compositor path is always an audit
      // of the Chromium layerization boundary until Viz readback is available.
    } else {
      bool consumes_value = false;
      if (IsChromiumGpuSwitch(arg, &consumes_value)) {
        if (consumes_value && i + 1 < argc && argv[i + 1][0] != '-')
          ++i;
        continue;
      }
      std::fprintf(stderr, "unknown argument: %s\n", arg.c_str());
      PrintUsage();
      return 2;
    }
  }

  if (renderer.html.empty()) {
    PrintUsage();
    return 2;
  }
  if (!html_file.empty()) {
    std::vector<std::string> stylesheet_diagnostics;
    html_css_renderer::AddLocalLinkedStylesheetsForDocument(
        std::filesystem::absolute(std::filesystem::path(html_file)),
        renderer.html, &renderer, &stylesheet_diagnostics);
    for (const std::string& diagnostic : stylesheet_diagnostics) {
      std::fprintf(stderr, "stylesheet diagnostic: %s\n", diagnostic.c_str());
    }
  }
  if (!css.empty())
    renderer.stylesheets.push_back({"cli", css});
  if (!css_file.empty() && renderer.stylesheets.empty())
    renderer.stylesheets.push_back({css_file, css});
  if (!resource_root.empty()) {
    html_css_renderer::SetStandaloneResourceProviderResourceRoot(resource_root);
  }
  if (!resource_base_path.empty()) {
    html_css_renderer::SetStandaloneResourceProviderDocumentBasePath(
        resource_base_path);
  } else if (!html_file.empty()) {
    html_css_renderer::SetStandaloneResourceProviderDocumentBasePath(
        std::filesystem::absolute(std::filesystem::path(html_file))
            .parent_path()
            .string());
  }

  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer = std::move(renderer);
  create_info.enable_paint_artifact_audit =
      !paint_artifact_dump_path.empty() || !json_path.empty();
  create_info.trace_stages = trace_stages;
  create_info.lifecycle_stop = lifecycle_stop;
  const auto create_start = std::chrono::steady_clock::now();
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(std::move(create_info));
  const auto create_end = std::chrono::steady_clock::now();
  std::vector<std::string> init_diagnostics;
  const auto initialize_start = std::chrono::steady_clock::now();
  if (!runtime || !runtime->Initialize(&init_diagnostics)) {
    std::fprintf(stderr, "failed to initialize Chromium compositor runtime\n");
    return 1;
  }
  const auto initialize_end = std::chrono::steady_clock::now();

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  const auto advance_start = std::chrono::steady_clock::now();
  html_css_renderer::CompositorFrameResult result = runtime->AdvanceFrame(input);
  const auto advance_end = std::chrono::steady_clock::now();
  if (warm_iterations > 0 && warm_scenarios.empty())
    warm_scenarios.push_back("no-change");
  std::vector<WarmScenarioRecord> warm_reports;
  html_css_renderer::CompositorFrameResult previous_warm_result = result;
  const auto millis_between = [](auto start, auto end) {
    return std::chrono::duration<double, std::milli>(end - start).count();
  };
  for (const std::string& scenario : warm_scenarios) {
    WarmScenarioRecord report;
    report.name = scenario;
    for (int iteration = 0; iteration < warm_iterations; ++iteration) {
      bool effective = true;
      html_css_renderer::FrameInput warm_input =
          MakeWarmInput(scenario, iteration, runtime->Snapshot(),
                        previous_warm_result, &effective);
      const auto warm_start = std::chrono::steady_clock::now();
      html_css_renderer::CompositorFrameResult warm_result =
          runtime->AdvanceFrame(warm_input);
      const auto warm_end = std::chrono::steady_clock::now();
      WarmFrameRecord frame;
      frame.iteration = iteration + 1;
      frame.effective = effective;
      frame.advance_frame_ms = millis_between(warm_start, warm_end);
      frame.result = warm_result;
      previous_warm_result = warm_result;
      report.frames.push_back(std::move(frame));
    }
    warm_reports.push_back(std::move(report));
  }
  const auto process_end = std::chrono::steady_clock::now();
  const double runtime_create_ms = millis_between(create_start, create_end);
  const double initialize_ms = millis_between(initialize_start, initialize_end);
  const double advance_frame_ms = millis_between(advance_start, advance_end);
  const double process_elapsed_ms = millis_between(process_start, process_end);
  for (const std::string& diagnostic : init_diagnostics)
    std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
  for (const std::string& diagnostic : result.diagnostics)
    std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());

  if (!paint_artifact_dump_path.empty()) {
    std::ofstream audit_file(paint_artifact_dump_path, std::ios::binary);
    if (!audit_file) {
      std::fprintf(stderr, "failed to write paint artifact dump: %s\n",
                   paint_artifact_dump_path.c_str());
      return 1;
    }
    audit_file << result.raw_paint_artifact_audit_json << "\n";
  }
  if (!json_path.empty() &&
      !WriteJson(json_path, result, init_diagnostics, warm_reports,
                 runtime_create_ms,
                 initialize_ms, advance_frame_ms, process_elapsed_ms)) {
    std::fprintf(stderr, "failed to write json: %s\n", json_path.c_str());
    return 1;
  }

  std::printf("compositor_metrics width=%d height=%d paint_clean=%d root_layer=%d "
              "cc_host=%d cc_attached=%d cc_commit=%d frame_sink_request=%d "
              "frame_sink_bound=%d gpu_context=%d raster_context=%d "
              "shared_image=%d viz_submit=%d viz_display=%d skia_gpu=%d "
              "layers=%d chunks=%d "
              "display_items=%d\n",
              static_cast<int>(result.successor_snapshot.viewport.width),
              static_cast<int>(result.successor_snapshot.viewport.height),
              result.paint_clean ? 1 : 0, result.root_layer_available ? 1 : 0,
              result.cc_host_created ? 1 : 0,
              result.cc_root_layer_attached ? 1 : 0,
              result.cc_commit_requested ? 1 : 0,
              result.cc_frame_sink_requested ? 1 : 0,
              result.cc_frame_sink_bound ? 1 : 0,
              result.gpu_context_created ? 1 : 0,
              result.raster_context_created ? 1 : 0,
              result.shared_image_interface_available ? 1 : 0,
              result.compositor_frame_submitted ? 1 : 0,
              result.viz_display_created ? 1 : 0,
              result.skia_renderer_gpu_path_reached ? 1 : 0,
              result.compositor_layer_count, result.paint_chunk_count,
              result.display_item_count);
  std::printf("compositor_timing runtime_create_ms=%.3f initialize_ms=%.3f "
              "advance_frame_ms=%.3f process_elapsed_ms=%.3f\n",
              runtime_create_ms, initialize_ms, advance_frame_ms,
              process_elapsed_ms);
  for (const WarmScenarioRecord& scenario : warm_reports) {
    std::vector<double> durations = WarmDurations(scenario);
    const int failure_count = WarmFailureCount(scenario);
    int viz_submit_count = 0;
    int effective_count = 0;
    for (const WarmFrameRecord& frame : scenario.frames) {
      if (frame.result.compositor_frame_submitted)
        ++viz_submit_count;
      if (frame.effective)
        ++effective_count;
    }
    const double max_ms =
        durations.empty()
            ? 0.0
            : *std::max_element(durations.begin(), durations.end());
    std::printf("compositor_warm scenario=%s frame_count=%zu effective_count=%d "
                "failures=%d p50_ms=%.3f p95_ms=%.3f max_ms=%.3f "
                "viz_submit_count=%d\n",
                scenario.name.c_str(), scenario.frames.size(), effective_count,
                failure_count, Percentile(durations, 0.50),
                Percentile(durations, 0.95), max_ms, viz_submit_count);
  }
  if (unsupported_out_requested) {
    std::fprintf(stderr,
                 "--out is not available until Viz/GPU readback is wired; "
                 "the benchmark does not provide a fallback pixel renderer.\n");
    return 5;
  }
  return result.paint_clean && result.root_layer_available ? 0 : 4;
}
