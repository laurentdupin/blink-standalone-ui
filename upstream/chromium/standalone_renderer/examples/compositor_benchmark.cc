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
#include "html_css_renderer/renderer_c_api.h"
#include "html_css_renderer/standalone_process.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "html_css_renderer/typeface_resource_registry.h"
#include "third_party/skia/include/core/SkTypeface.h"
#include "third_party/perfetto/include/perfetto/tracing/tracing.h"
#include "ui/gl/gl_switches.h"

extern "C" const char*
StandaloneBlinkLiveFrameBridgeRunCcSchedulerProbeForStandaloneRenderer(
    int width,
    int height);

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
      "[--warm-iterations N] [--warm-scenario name[,name...]] "
      "[--result-collection full|minimal] [--cc-scheduler-probe] "
      "[--c-api-smoke] [--c-api-two-instance-smoke] "
      "[--typeface-isolation-smoke]\n"
      "This target now exercises the Chromium compositor path only. CPU BMP "
      "readback is removed from production; --out is intentionally unsupported "
      "until Viz/GPU readback is wired.\n");
}

int RunCApiSmoke() {
  hcsr_renderer_config_t config = {};
  config.width = 160;
  config.height = 120;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  hcsr_renderer_t* renderer = nullptr;
  hcsr_status_code_t status = hcsr_renderer_create(&config, &renderer);
  if (status != HCSR_STATUS_OK || !renderer) {
    std::fprintf(stderr, "c_api_smoke: create failed status=%d\n", status);
    return 1;
  }
  const char* rejected_html = "<script>window.x=1</script>";
  status = hcsr_renderer_set_document_html(renderer, rejected_html, "", "");
  if (status != HCSR_STATUS_NO_SCRIPT_REJECTED) {
    std::fprintf(stderr,
                 "c_api_smoke: no-script rejection failed status=%d\n",
                 status);
    hcsr_renderer_destroy(renderer);
    return 1;
  }
  const char* html =
      "<!doctype html><style>body{margin:0}.card{width:80px;height:60px;"
      "background:#2878d8;color:white}input{margin:4px}</style><div id='card' "
      "class='card' data-godot-action='open'>Card</div><label><input "
      "id='agree' type='checkbox' data-godot-action='toggle'>Agree</label>"
      "<input id='name' value='abc' data-godot-action='name'>";
  status = hcsr_renderer_set_document_html(renderer, html, "", "");
  if (status != HCSR_STATUS_OK) {
    std::fprintf(stderr, "c_api_smoke: set html failed status=%d error=%s\n",
                 status, hcsr_renderer_last_error(renderer));
    hcsr_renderer_destroy(renderer);
    return 1;
  }
  status = hcsr_renderer_advance_frame(renderer, 0.0);
  if (status != HCSR_STATUS_OK) {
    std::fprintf(stderr, "c_api_smoke: advance failed status=%d error=%s\n",
                 status, hcsr_renderer_last_error(renderer));
    hcsr_renderer_destroy(renderer);
    return 1;
  }
  hcsr_frame_output_t output = {};
  status = hcsr_renderer_get_latest_output(renderer, &output);
  if (status != HCSR_STATUS_OK || !output.pixels || output.width != 160 ||
      output.height != 120 || output.stride < output.width * 4 ||
      output.pixel_count == 0 || output.dirty_rect_count != 1) {
    std::fprintf(stderr,
                 "c_api_smoke: raw output invalid status=%d size=%dx%d "
                 "stride=%d bytes=%zu dirty=%zu format=%d error=%s\n",
                 status, output.width, output.height, output.stride,
                 output.pixel_count, output.dirty_rect_count,
                 output.pixel_format, hcsr_renderer_last_error(renderer));
    hcsr_renderer_destroy(renderer);
    return 1;
  }
  bool saw_card = false;
  bool saw_checkbox = false;
  bool saw_input = false;
  hcsr_rect_t card_bounds = {};
  hcsr_rect_t checkbox_bounds = {};
  hcsr_rect_t input_bounds = {};
  const size_t hit_count = hcsr_renderer_hit_metadata_count(renderer);
  for (size_t i = 0; i < hit_count; ++i) {
    hcsr_hit_metadata_t hit = {};
    if (hcsr_renderer_get_hit_metadata(renderer, i, &hit) != HCSR_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    const std::string tag = hit.tag_name ? hit.tag_name : "";
    const std::string action =
        hit.data_godot_action ? hit.data_godot_action : "";
    if (id == "card" && tag == "div" && action == "open" &&
        hit.bounds.width > 0.0f && hit.bounds.height > 0.0f) {
      saw_card = true;
      card_bounds = hit.bounds;
    }
    if (id == "agree" && tag == "input" && action == "toggle" &&
        !hit.disabled && !hit.checked) {
      saw_checkbox = true;
      checkbox_bounds = hit.bounds;
    }
    if (id == "name" && tag == "input" && action == "name" &&
        hit.editable && !hit.focused && hit.bounds.width > 0.0f &&
        hit.bounds.height > 0.0f) {
      saw_input = true;
      input_bounds = hit.bounds;
    }
  }
  hcsr_hit_metadata_t point_hit = {};
  if (saw_card &&
      hcsr_renderer_hit_test(renderer, card_bounds.x + card_bounds.width * 0.5f,
                             card_bounds.y + card_bounds.height * 0.5f,
                             &point_hit) != HCSR_STATUS_OK) {
    saw_card = false;
  } else if (saw_card) {
    const std::string id = point_hit.element_id ? point_hit.element_id : "";
    saw_card = id == "card";
  }
  if (!saw_card || !saw_checkbox || !saw_input) {
    std::fprintf(stderr,
                 "c_api_smoke: expected hit metadata missing hit_count=%zu "
                 "card=%d checkbox=%d input=%d\n",
                 hit_count, saw_card ? 1 : 0, saw_checkbox ? 1 : 0,
                 saw_input ? 1 : 0);
    hcsr_renderer_release_latest_output(renderer);
    hcsr_renderer_destroy(renderer);
    return 1;
  }

  const float checkbox_x = checkbox_bounds.x + checkbox_bounds.width * 0.5f;
  const float checkbox_y = checkbox_bounds.y + checkbox_bounds.height * 0.5f;
  hcsr_renderer_mouse_move(renderer, checkbox_x, checkbox_y, 0);
  hcsr_renderer_mouse_down(renderer, checkbox_x, checkbox_y,
                           HCSR_MOUSE_BUTTON_LEFT, 0, 1);
  hcsr_renderer_mouse_up(renderer, checkbox_x, checkbox_y,
                         HCSR_MOUSE_BUTTON_LEFT, 0, 1);
  status = hcsr_renderer_advance_frame(renderer, 0.016);
  if (status != HCSR_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_smoke: checkbox click advance failed status=%d "
                 "error=%s\n",
                 status, hcsr_renderer_last_error(renderer));
    hcsr_renderer_destroy(renderer);
    return 1;
  }
  bool checkbox_checked = false;
  for (size_t i = 0; i < hcsr_renderer_hit_metadata_count(renderer); ++i) {
    hcsr_hit_metadata_t hit = {};
    if (hcsr_renderer_get_hit_metadata(renderer, i, &hit) != HCSR_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == "agree" && hit.checked) {
      checkbox_checked = true;
      break;
    }
  }
  if (!checkbox_checked) {
    std::fprintf(stderr, "c_api_smoke: checkbox did not toggle through C API\n");
    hcsr_renderer_destroy(renderer);
    return 1;
  }

  const float input_x = input_bounds.x + input_bounds.width * 0.5f;
  const float input_y = input_bounds.y + input_bounds.height * 0.5f;
  hcsr_renderer_mouse_move(renderer, input_x, input_y, 0);
  hcsr_renderer_mouse_down(renderer, input_x, input_y, HCSR_MOUSE_BUTTON_LEFT,
                           0, 1);
  hcsr_renderer_mouse_up(renderer, input_x, input_y, HCSR_MOUSE_BUTTON_LEFT, 0,
                         1);
  hcsr_renderer_text_input(renderer, "Z");
  status = hcsr_renderer_advance_frame(renderer, 0.032);
  if (status != HCSR_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_smoke: text focus advance failed status=%d error=%s\n",
                 status, hcsr_renderer_last_error(renderer));
    hcsr_renderer_destroy(renderer);
    return 1;
  }
  bool input_focused = false;
  for (size_t i = 0; i < hcsr_renderer_hit_metadata_count(renderer); ++i) {
    hcsr_hit_metadata_t hit = {};
    if (hcsr_renderer_get_hit_metadata(renderer, i, &hit) != HCSR_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == "name" && hit.focused) {
      input_focused = true;
      break;
    }
  }
  hcsr_renderer_release_latest_output(renderer);
  hcsr_renderer_destroy(renderer);
  if (!input_focused) {
    std::fprintf(stderr, "c_api_smoke: input did not focus through C API\n");
    return 1;
  }
  std::printf(
      "c_api_smoke: ok raw=%dx%d stride=%d bytes=%zu dirty=%zu hits=%zu\n",
      output.width, output.height, output.stride, output.pixel_count,
      output.dirty_rect_count, hit_count);
  return 0;
}

uint64_t HashFramePixels(const hcsr_frame_output_t& output) {
  uint64_t hash = 1469598103934665603ull;
  for (size_t i = 0; output.pixels && i < output.pixel_count; ++i) {
    hash ^= static_cast<uint64_t>(output.pixels[i]);
    hash *= 1099511628211ull;
  }
  return hash;
}

bool FrameHasNonUniformPixels(const hcsr_frame_output_t& output) {
  if (!output.pixels || output.pixel_count < 8) {
    return false;
  }
  const uint8_t first = output.pixels[0];
  for (size_t i = 1; i < output.pixel_count; ++i) {
    if (output.pixels[i] != first) {
      return true;
    }
  }
  return false;
}

bool HasHitId(hcsr_renderer_t* renderer, const char* expected_id) {
  for (size_t i = 0; i < hcsr_renderer_hit_metadata_count(renderer); ++i) {
    hcsr_hit_metadata_t hit = {};
    if (hcsr_renderer_get_hit_metadata(renderer, i, &hit) != HCSR_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == expected_id) {
      return true;
    }
  }
  return false;
}

bool WriteSolidBmp(const std::filesystem::path& path,
                   uint8_t red,
                   uint8_t green,
                   uint8_t blue) {
  constexpr int kWidth = 8;
  constexpr int kHeight = 8;
  constexpr int kBytesPerPixel = 3;
  constexpr int kRowStride = ((kWidth * kBytesPerPixel + 3) / 4) * 4;
  constexpr int kPixelBytes = kRowStride * kHeight;
  constexpr int kFileSize = 54 + kPixelBytes;
  std::vector<uint8_t> bytes(kFileSize, 0);
  bytes[0] = 'B';
  bytes[1] = 'M';
  bytes[2] = static_cast<uint8_t>(kFileSize);
  bytes[3] = static_cast<uint8_t>(kFileSize >> 8);
  bytes[10] = 54;
  bytes[14] = 40;
  bytes[18] = static_cast<uint8_t>(kWidth);
  bytes[22] = static_cast<uint8_t>(kHeight);
  bytes[26] = 1;
  bytes[28] = 24;
  for (int y = 0; y < kHeight; ++y) {
    for (int x = 0; x < kWidth; ++x) {
      const int offset = 54 + y * kRowStride + x * kBytesPerPixel;
      bytes[offset + 0] = blue;
      bytes[offset + 1] = green;
      bytes[offset + 2] = red;
    }
  }
  std::ofstream file(path, std::ios::binary);
  if (!file)
    return false;
  file.write(reinterpret_cast<const char*>(bytes.data()),
             static_cast<std::streamsize>(bytes.size()));
  return file.good();
}

int RunCApiTwoInstanceSmoke() {
  hcsr_renderer_config_t config_a = {};
  config_a.width = 180;
  config_a.height = 120;
  config_a.device_scale_factor = 1.0f;
  config_a.no_script_profile = 1;
  hcsr_renderer_config_t config_b = {};
  config_b.width = 96;
  config_b.height = 64;
  config_b.device_scale_factor = 1.0f;
  config_b.no_script_profile = 1;

  hcsr_renderer_t* renderer_a = nullptr;
  hcsr_renderer_t* renderer_b = nullptr;
  hcsr_status_code_t status = hcsr_renderer_create(&config_a, &renderer_a);
  if (status != HCSR_STATUS_OK || !renderer_a) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: create A failed status=%d\n",
                 status);
    return 1;
  }
  status = hcsr_renderer_create(&config_b, &renderer_b);
  if (status != HCSR_STATUS_OK || !renderer_b) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: create B failed status=%d\n",
                 status);
    hcsr_renderer_destroy(renderer_a);
    return 1;
  }

  const auto resource_root =
      std::filesystem::temp_directory_path() /
      ("blink_standalone_two_instance_resources_" +
       std::to_string(std::chrono::steady_clock::now()
                          .time_since_epoch()
                          .count()));
  const auto root_a = resource_root / "a";
  const auto root_b = resource_root / "b";
  std::error_code fs_error;
  std::filesystem::create_directories(root_a, fs_error);
  std::filesystem::create_directories(root_b, fs_error);
  if (fs_error || !WriteSolidBmp(root_a / "icon.bmp", 232, 68, 68) ||
      !WriteSolidBmp(root_b / "icon.bmp", 35, 122, 87)) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: failed to create resource roots "
                 "under %s\n",
                 resource_root.string().c_str());
    hcsr_renderer_destroy(renderer_b);
    hcsr_renderer_destroy(renderer_a);
    return 1;
  }

  const char* html_a =
      "<!doctype html><style>body{margin:0;background:white}.a{width:64px;"
      "height:64px;background-image:url(icon.bmp);background-size:64px 64px}"
      "</style><div id='alpha' class='a' data-godot-action='alpha'>Alpha</div>";
  const char* html_b =
      "<!doctype html><style>body{margin:0;background:white}.b{width:48px;"
      "height:48px;background-image:url(icon.bmp);background-size:48px 48px}"
      "</style><div id='beta' class='b' data-godot-action='beta'>Beta</div>";

  const std::string root_a_string = root_a.string();
  const std::string root_b_string = root_b.string();
  status = hcsr_renderer_set_document_html(
      renderer_a, html_a, root_a_string.c_str(), root_a_string.c_str());
  if (status == HCSR_STATUS_OK) {
    status = hcsr_renderer_set_document_html(
        renderer_b, html_b, root_b_string.c_str(), root_b_string.c_str());
  }
  if (status != HCSR_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: set html failed status=%d A=%s B=%s\n",
                 status, hcsr_renderer_last_error(renderer_a),
                 hcsr_renderer_last_error(renderer_b));
    hcsr_renderer_destroy(renderer_b);
    hcsr_renderer_destroy(renderer_a);
    return 1;
  }

  status = hcsr_renderer_advance_frame(renderer_a, 0.0);
  hcsr_frame_output_t first_output_a = {};
  uint64_t first_hash_a = 0;
  if (status == HCSR_STATUS_OK &&
      hcsr_renderer_get_latest_output(renderer_a, &first_output_a) ==
          HCSR_STATUS_OK) {
    first_hash_a = HashFramePixels(first_output_a);
    hcsr_renderer_release_latest_output(renderer_a);
  }
  if (status == HCSR_STATUS_OK) {
    status = hcsr_renderer_advance_frame(renderer_b, 0.0);
  }
  const char* html_a_reload =
      "<!doctype html><!--reload--><style>body{margin:0;background:white}.a{"
      "width:64px;height:64px;background-image:url(icon.bmp);"
      "background-size:64px 64px}</style><div id='alpha' class='a' "
      "data-godot-action='alpha'>Alpha</div>";
  if (status == HCSR_STATUS_OK) {
    status = hcsr_renderer_set_document_html(
        renderer_a, html_a_reload, root_a_string.c_str(), root_a_string.c_str());
  }
  if (status == HCSR_STATUS_OK) {
    status = hcsr_renderer_advance_frame(renderer_a, 0.016);
  }
  if (status != HCSR_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: advance failed status=%d A=%s B=%s\n",
                 status, hcsr_renderer_last_error(renderer_a),
                 hcsr_renderer_last_error(renderer_b));
    hcsr_renderer_destroy(renderer_b);
    hcsr_renderer_destroy(renderer_a);
    return 1;
  }

  hcsr_frame_output_t output_a = {};
  hcsr_frame_output_t output_b = {};
  const hcsr_status_code_t output_a_status =
      hcsr_renderer_get_latest_output(renderer_a, &output_a);
  const hcsr_status_code_t output_b_status =
      hcsr_renderer_get_latest_output(renderer_b, &output_b);
  const uint64_t hash_a = HashFramePixels(output_a);
  const uint64_t hash_b = HashFramePixels(output_b);
  const bool ok =
      output_a_status == HCSR_STATUS_OK && output_b_status == HCSR_STATUS_OK &&
      output_a.width == 180 && output_a.height == 120 && output_b.width == 96 &&
      output_b.height == 64 && output_a.pixel_count > 0 &&
      output_b.pixel_count > 0 && FrameHasNonUniformPixels(output_a) &&
      FrameHasNonUniformPixels(output_b) && first_hash_a != 0 &&
      hash_a == first_hash_a && hash_a != hash_b &&
      HasHitId(renderer_a, "alpha") && !HasHitId(renderer_a, "beta") &&
      HasHitId(renderer_b, "beta") && !HasHitId(renderer_b, "alpha");
  if (!ok) {
    std::fprintf(
        stderr,
        "c_api_two_instance_smoke: failed A_status=%d A=%dx%d bytes=%zu "
        "hash=%llu first_hash=%llu hits=%zu B_status=%d B=%dx%d bytes=%zu hash=%llu hits=%zu "
        "Aerr=%s Berr=%s\n",
        output_a_status, output_a.width, output_a.height, output_a.pixel_count,
        static_cast<unsigned long long>(hash_a),
        static_cast<unsigned long long>(first_hash_a),
        hcsr_renderer_hit_metadata_count(renderer_a), output_b_status,
        output_b.width, output_b.height, output_b.pixel_count,
        static_cast<unsigned long long>(hash_b),
        hcsr_renderer_hit_metadata_count(renderer_b),
        hcsr_renderer_last_error(renderer_a), hcsr_renderer_last_error(renderer_b));
    hcsr_renderer_destroy(renderer_b);
    hcsr_renderer_destroy(renderer_a);
    return 1;
  }

  std::printf(
      "c_api_two_instance_smoke: ok A=%dx%d hash=%llu hits=%zu B=%dx%d "
      "hash=%llu hits=%zu\n",
      output_a.width, output_a.height, static_cast<unsigned long long>(hash_a),
      hcsr_renderer_hit_metadata_count(renderer_a), output_b.width,
      output_b.height, static_cast<unsigned long long>(hash_b),
      hcsr_renderer_hit_metadata_count(renderer_b));
  hcsr_renderer_release_latest_output(renderer_a);
  hcsr_renderer_release_latest_output(renderer_b);
  hcsr_renderer_destroy(renderer_b);
  hcsr_renderer_destroy(renderer_a);
  return 0;
}

int RunTypefaceIsolationSmoke() {
  const uint64_t context_a =
      html_css_renderer::CreateTypefaceResourceRegistryContext();
  const uint64_t context_b =
      html_css_renderer::CreateTypefaceResourceRegistryContext();
  sk_sp<SkTypeface> typeface = SkTypeface::MakeEmpty();
  if (!typeface) {
    std::fprintf(stderr, "typeface_isolation_smoke: default typeface missing\n");
    html_css_renderer::DestroyTypefaceResourceRegistryContext(context_b);
    html_css_renderer::DestroyTypefaceResourceRegistryContext(context_a);
    return 1;
  }

  html_css_renderer::SetCurrentTypefaceResourceRegistryContext(context_a);
  html_css_renderer::ResetTypefaceResourceRegistryForFrame();
  const uint64_t id_a =
      html_css_renderer::RegisterSameProcessTypefaceResource(typeface.get());
  const size_t count_a_initial =
      html_css_renderer::SnapshotTypefaceResources().size();

  html_css_renderer::SetCurrentTypefaceResourceRegistryContext(context_b);
  html_css_renderer::ResetTypefaceResourceRegistryForFrame();
  const size_t count_b_before =
      html_css_renderer::SnapshotTypefaceResources().size();
  const bool a_id_missing_from_b =
      !html_css_renderer::LookupSameProcessTypefaceResource(id_a);
  const uint64_t id_b =
      html_css_renderer::RegisterSameProcessTypefaceResource(typeface.get());
  const size_t count_b_after =
      html_css_renderer::SnapshotTypefaceResources().size();

  html_css_renderer::SetCurrentTypefaceResourceRegistryContext(context_a);
  const size_t count_a_after_b =
      html_css_renderer::SnapshotTypefaceResources().size();
  const bool a_lookup_still_valid =
      !!html_css_renderer::LookupSameProcessTypefaceResource(id_a);

  html_css_renderer::SetCurrentTypefaceResourceRegistryContext(0);
  html_css_renderer::DestroyTypefaceResourceRegistryContext(context_b);
  html_css_renderer::DestroyTypefaceResourceRegistryContext(context_a);

  const bool ok = id_a != 0 && id_b != 0 && count_a_initial == 1 &&
                  count_b_before == 0 && a_id_missing_from_b &&
                  count_b_after == 1 && count_a_after_b == 1 &&
                  a_lookup_still_valid;
  if (!ok) {
    std::fprintf(stderr,
                 "typeface_isolation_smoke: failed id_a=%llu id_b=%llu "
                 "A_initial=%zu B_before=%zu A_missing_from_B=%d "
                 "B_after=%zu A_after_B=%zu A_lookup=%d\n",
                 static_cast<unsigned long long>(id_a),
                 static_cast<unsigned long long>(id_b), count_a_initial,
                 count_b_before, a_id_missing_from_b ? 1 : 0, count_b_after,
                 count_a_after_b, a_lookup_still_valid ? 1 : 0);
    return 1;
  }
  std::printf("typeface_isolation_smoke: ok A_count=%zu B_count=%zu\n",
              count_a_after_b, count_b_after);
  return 0;
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
  input.form_values_by_element_id = snapshot.form_values_by_element_id;
  return input;
}

void AppendMouseInputEvent(html_css_renderer::FrameInput* input,
                           html_css_renderer::MouseInputEventType type,
                           html_css_renderer::Point position,
                           html_css_renderer::MouseInputButton button,
                           int modifiers,
                           int click_count) {
  input->mouse_events.push_back(
      html_css_renderer::MouseInputEvent{type, position, button, modifiers,
                                         click_count});
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
    AppendMouseInputEvent(
        &input, html_css_renderer::MouseInputEventType::kMove,
        html_css_renderer::Point{32.0f +
                                     static_cast<float>(iteration % 4) * 8.0f,
                                 32.0f},
        html_css_renderer::MouseInputButton::kNone, 0, 0);
    return input;
  }
  if (scenario == "pointer-click") {
    const bool pressed = iteration % 2 == 0;
    AppendMouseInputEvent(
        &input,
        pressed ? html_css_renderer::MouseInputEventType::kDown
                : html_css_renderer::MouseInputEventType::kUp,
        html_css_renderer::Point{32.0f, 32.0f},
        html_css_renderer::MouseInputButton::kLeft,
        pressed ? (1 << 6) : 0, 1);
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
    if (result.frame_skipped_due_to_no_demand)
      continue;
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

void WriteFrameTimingJsonFields(
    std::ofstream& file,
    const html_css_renderer::CompositorFrameTiming& timing,
    const std::string& indent,
    bool trailing_comma) {
  file << indent << "\"frame_timing\": {\n";
  file << indent << "  \"runtime_apply_state_ms\": "
       << timing.runtime_apply_state_ms << ",\n";
  file << indent << "  \"runtime_bridge_query_ms\": "
       << timing.runtime_bridge_query_ms << ",\n";
  file << indent << "  \"runtime_total_ms\": " << timing.runtime_total_ms
       << ",\n";
  file << indent << "  \"bridge_total_ms\": " << timing.bridge_total_ms
       << ",\n";
  file << indent << "  \"bridge_input_setup_ms\": "
       << timing.bridge_input_setup_ms << ",\n";
  file << indent << "  \"bridge_html_document_setup_ms\": "
       << timing.bridge_html_document_setup_ms << ",\n";
  file << indent << "  \"bridge_style_update_ms\": "
       << timing.bridge_style_update_ms << ",\n";
  file << indent << "  \"bridge_layout_lifecycle_ms\": "
       << timing.bridge_layout_lifecycle_ms << ",\n";
  file << indent << "  \"bridge_prepaint_and_paint_lifecycle_ms\": "
       << timing.bridge_prepaint_and_paint_lifecycle_ms << ",\n";
  file << indent << "  \"bridge_paint_artifact_generation_ms\": "
       << timing.bridge_paint_artifact_generation_ms << ",\n";
  file << indent << "  \"bridge_paint_artifact_audit_ms\": "
       << timing.bridge_paint_artifact_audit_ms << ",\n";
  file << indent << "  \"bridge_paint_artifact_extraction_ms\": "
       << timing.bridge_paint_artifact_extraction_ms << ",\n";
  file << indent << "  \"bridge_cc_composite_ms\": "
       << timing.bridge_cc_composite_ms << ",\n";
  file << indent << "  \"bridge_cache_hit\": "
       << (timing.bridge_cache_hit ? "true" : "false") << ",\n";
  file << indent << "  \"bridge_reused_live_document\": "
       << (timing.bridge_reused_live_document ? "true" : "false")
       << ",\n";
  file << indent << "  \"bridge_rebuilt_for_attributes\": "
       << (timing.bridge_rebuilt_for_attributes ? "true" : "false")
       << "\n";
  file << indent << "}" << (trailing_comma ? ",\n" : "\n");
}

void WriteCompositorResultJsonFields(
    std::ofstream& file,
    const html_css_renderer::CompositorFrameResult& result,
    const std::string& indent,
    bool trailing_comma) {
  file << indent << "\"frame_advanced\": "
       << (result.frame_advanced ? "true" : "false") << ",\n";
  file << indent << "\"frame_skipped_due_to_no_demand\": "
       << (result.frame_skipped_due_to_no_demand ? "true" : "false")
       << ",\n";
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
  file << indent << "\"compositor_output_size\": {\"width\": "
       << result.compositor_output_size.width << ", \"height\": "
       << result.compositor_output_size.height << "},\n";
  file << indent << "\"viz_display_output_size\": {\"width\": "
       << result.viz_display_output_size.width << ", \"height\": "
       << result.viz_display_output_size.height << "},\n";
  file << indent << "\"compositor_layer_count\": "
       << result.compositor_layer_count << ",\n";
  file << indent << "\"paint_chunk_count\": " << result.paint_chunk_count
       << ",\n";
  file << indent << "\"display_item_count\": " << result.display_item_count
       << ",\n";
  WriteFrameTimingJsonFields(file, result.timing, indent, trailing_comma);
}

bool WriteJson(const std::string& path,
               const html_css_renderer::CompositorFrameResult& result,
               const std::vector<std::string>& init_diagnostics,
               const std::vector<WarmScenarioRecord>& warm_scenarios,
               html_css_renderer::FrameResultCollection result_collection,
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
  file << "  \"result_collection\": \""
       << (result_collection == html_css_renderer::FrameResultCollection::kFull
               ? "full"
               : "minimal")
       << "\",\n";
  file << "  \"frame_advanced\": "
       << (result.frame_advanced ? "true" : "false") << ",\n";
  file << "  \"frame_skipped_due_to_no_demand\": "
       << (result.frame_skipped_due_to_no_demand ? "true" : "false")
       << ",\n";
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
  file << "  \"compositor_output_size\": {\"width\": "
       << result.compositor_output_size.width << ", \"height\": "
       << result.compositor_output_size.height << "},\n";
  file << "  \"viz_display_output_size\": {\"width\": "
       << result.viz_display_output_size.width << ", \"height\": "
       << result.viz_display_output_size.height << "},\n";
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
  WriteFrameTimingJsonFields(file, result.timing, "  ",
                             /*trailing_comma=*/true);
  file << "  \"warm_scenarios\": [\n";
  for (size_t i = 0; i < warm_scenarios.size(); ++i) {
    const WarmScenarioRecord& scenario = warm_scenarios[i];
    std::vector<double> durations = WarmDurations(scenario);
    file << "    {\n";
    file << "      \"scenario\": \"" << EscapeJson(scenario.name) << "\",\n";
    file << "      \"frame_count\": " << scenario.frames.size() << ",\n";
    file << "      \"failure_count\": " << WarmFailureCount(scenario)
         << ",\n";
    file << "      \"skipped_frame_count\": "
         << std::count_if(scenario.frames.begin(), scenario.frames.end(),
                          [](const WarmFrameRecord& frame) {
                            return frame.result.frame_skipped_due_to_no_demand;
                          })
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
  html_css_renderer::ConfigureStandaloneToolProcess();
  const auto process_start = std::chrono::steady_clock::now();
  base::CommandLine::Init(argc, argv);
  bool c_api_smoke_requested = false;
  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    if (arg == "--c-api-smoke" || arg == "--c-api-two-instance-smoke" ||
        arg == "--typeface-isolation-smoke") {
      c_api_smoke_requested = true;
      break;
    }
  }
  if (!c_api_smoke_requested)
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
  bool cc_scheduler_probe = false;
  bool c_api_smoke = false;
  bool c_api_two_instance_smoke = false;
  bool typeface_isolation_smoke = false;
  int warm_iterations = 0;
  std::vector<std::string> warm_scenarios;
  html_css_renderer::FrameResultCollection result_collection =
      html_css_renderer::FrameResultCollection::kFull;

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
    } else if (arg == "--cc-scheduler-probe") {
      cc_scheduler_probe = true;
    } else if (arg == "--c-api-smoke") {
      c_api_smoke = true;
    } else if (arg == "--c-api-two-instance-smoke") {
      c_api_two_instance_smoke = true;
    } else if (arg == "--typeface-isolation-smoke") {
      typeface_isolation_smoke = true;
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
    } else if (arg == "--result-collection") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      const std::string mode = value;
      if (mode == "full") {
        result_collection = html_css_renderer::FrameResultCollection::kFull;
      } else if (mode == "minimal") {
        result_collection = html_css_renderer::FrameResultCollection::kMinimal;
      } else {
        std::fprintf(stderr, "invalid --result-collection\n");
        return 2;
      }
    } else if (arg.rfind("--result-collection=", 0) == 0) {
      const std::string mode = arg.substr(20);
      if (mode == "full") {
        result_collection = html_css_renderer::FrameResultCollection::kFull;
      } else if (mode == "minimal") {
        result_collection = html_css_renderer::FrameResultCollection::kMinimal;
      } else {
        std::fprintf(stderr, "invalid --result-collection\n");
        return 2;
      }
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

  if (cc_scheduler_probe) {
    const char* probe_json =
        StandaloneBlinkLiveFrameBridgeRunCcSchedulerProbeForStandaloneRenderer(
            static_cast<int>(renderer.viewport.width),
            static_cast<int>(renderer.viewport.height));
    const std::string json = probe_json ? probe_json : "{}\n";
    if (!json_path.empty()) {
      std::ofstream file(json_path, std::ios::binary);
      if (!file) {
        std::fprintf(stderr, "failed to write json: %s\n",
                     json_path.c_str());
        return 1;
      }
      file << json;
    }
    std::printf("%s", json.c_str());
    return json.find("\"success\": true") != std::string::npos ? 0 : 6;
  }

  if (c_api_smoke) {
    return RunCApiSmoke();
  }

  if (c_api_two_instance_smoke) {
    return RunCApiTwoInstanceSmoke();
  }

  if (typeface_isolation_smoke) {
    return RunTypefaceIsolationSmoke();
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
      !paint_artifact_dump_path.empty() ||
      (!json_path.empty() &&
       result_collection == html_css_renderer::FrameResultCollection::kFull);
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
  input.result_collection =
      !paint_artifact_dump_path.empty()
          ? html_css_renderer::FrameResultCollection::kFull
          : result_collection;
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
      warm_input.result_collection = result_collection;
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
                 result_collection, runtime_create_ms,
                 initialize_ms, advance_frame_ms, process_elapsed_ms)) {
    std::fprintf(stderr, "failed to write json: %s\n", json_path.c_str());
    return 1;
  }

  std::printf("compositor_metrics width=%d height=%d cc_output=%dx%d "
              "viz_output=%dx%d paint_clean=%d root_layer=%d "
              "cc_host=%d cc_attached=%d cc_commit=%d frame_sink_request=%d "
              "frame_sink_bound=%d gpu_context=%d raster_context=%d "
              "shared_image=%d viz_submit=%d viz_display=%d skia_gpu=%d "
              "layers=%d chunks=%d "
              "display_items=%d\n",
              static_cast<int>(result.successor_snapshot.viewport.width),
              static_cast<int>(result.successor_snapshot.viewport.height),
              static_cast<int>(result.compositor_output_size.width),
              static_cast<int>(result.compositor_output_size.height),
              static_cast<int>(result.viz_display_output_size.width),
              static_cast<int>(result.viz_display_output_size.height),
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
    int skipped_count = 0;
    for (const WarmFrameRecord& frame : scenario.frames) {
      if (frame.result.frame_skipped_due_to_no_demand) {
        ++skipped_count;
      } else if (frame.result.compositor_frame_submitted) {
        ++viz_submit_count;
      }
      if (frame.effective)
        ++effective_count;
    }
    const double max_ms =
        durations.empty()
            ? 0.0
            : *std::max_element(durations.begin(), durations.end());
    std::printf("compositor_warm scenario=%s frame_count=%zu effective_count=%d "
                "skipped_count=%d failures=%d p50_ms=%.3f p95_ms=%.3f "
                "max_ms=%.3f viz_submit_count=%d\n",
                scenario.name.c_str(), scenario.frames.size(), effective_count,
                skipped_count, failure_count, Percentile(durations, 0.50),
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
