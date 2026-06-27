#include <chrono>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <limits>
#include <sstream>
#include <string>
#include <algorithm>
#include <cerrno>
#include <cstdlib>
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
  std::string width_text = value.substr(0, x);
  std::string height_text = value.substr(x + 1);
  char* width_end = nullptr;
  char* height_end = nullptr;
  errno = 0;
  const float width = std::strtof(width_text.c_str(), &width_end);
  if (errno != 0 || width_end == width_text.c_str() || *width_end != '\0')
    return false;
  errno = 0;
  const float height = std::strtof(height_text.c_str(), &height_end);
  if (errno != 0 || height_end == height_text.c_str() || *height_end != '\0')
    return false;
  size->width = width;
  size->height = height;
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
  char* end = nullptr;
  errno = 0;
  const long parsed = std::strtol(value.c_str(), &end, 10);
  if (errno != 0 || end == value.c_str() || *end != '\0' || parsed < 0 ||
      parsed > std::numeric_limits<int>::max()) {
    return false;
  }
  *out = static_cast<int>(parsed);
  return true;
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
      "[--c-api-smoke] [--c-api-viewport-resize-smoke] "
      "[--c-api-empty-resource-smoke] "
      "[--c-api-transparent-background-smoke] "
      "[--c-api-separated-click-smoke] "
      "[--c-api-text-input-smoke] "
      "[--c-api-form-control-mutation-smoke] "
      "[--c-api-absolute-form-mutation-smoke] "
      "[--c-api-fragment-mutation-smoke] "
      "[--c-api-body-mutation-smoke] "
      "[--c-api-dom-mutation-smoke] "
      "[--c-api-two-instance-smoke] "
      "[--typeface-isolation-smoke]\n"
      "This target now exercises the Chromium compositor path only. CPU BMP "
      "readback is removed from production; --out is intentionally unsupported "
      "until Viz/GPU readback is wired.\n");
}

struct FramePixelContentStats {
  size_t nontransparent = 0;
  size_t nonwhite_colored = 0;
  size_t transparent = 0;
  size_t opaque_white = 0;
  size_t dark_blue_112233 = 0;
  size_t dark_blue_123456 = 0;
  size_t blue_2878d8 = 0;
  size_t blue_144a80 = 0;
  size_t orange_dd7744 = 0;
  size_t orange_d06329 = 0;
  size_t resource_red_e84444 = 0;
  size_t resource_green_237a57 = 0;
};

FramePixelContentStats AnalyzeFramePixelContent(
    const blink_standalone_frame_output_t& output);

bool ExpectNoScriptRejected(blink_standalone_renderer_t* renderer,
                            const char* label,
                            const char* html) {
  const blink_standalone_status_code_t status =
      blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status == BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
    return true;
  }
  std::fprintf(stderr,
               "c_api_smoke: no-script rejection failed for %s status=%d "
               "error=%s\n",
               label, status, blink_standalone_renderer_last_error(renderer));
  return false;
}

int RunCApiSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 160;
  config.height = 120;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status = blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr, "c_api_smoke: create failed status=%d\n", status);
    return 1;
  }
  struct RejectedCase {
    const char* label;
    const char* html;
  };
  const RejectedCase rejected_cases[] = {
      {"script", "<script>window.x=1</script>"},
      {"inline-event", "<button onclick=\"window.x=1\">Run</button>"},
      {"javascript-url", "<a href=\"javascript:alert(1)\">Run</a>"},
      {"javascript-url-case",
       "<a href=\"JaVaScRiPt:alert(1)\">Run</a>"},
      {"javascript-url-whitespace",
       "<a href=\"java\n\t script:alert(1)\">Run</a>"},
      {"iframe", "<iframe src=\"about:blank\"></iframe>"},
      {"object", "<object data=\"data:text/html,boom\"></object>"},
      {"embed", "<embed src=\"data:text/html,boom\">"},
  };
  for (const RejectedCase& rejected : rejected_cases) {
    if (!ExpectNoScriptRejected(renderer, rejected.label, rejected.html)) {
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }
  }
  const char* remote_image_html =
      "<!doctype html><style>body{margin:0;background:#144a80}"
      "#box{width:80px;height:60px;background:#d06329}</style>"
      "<img src=\"https://example.invalid/standalone-denied.png\" alt=\"remote\">"
      "<div id='box'>No network</div>";
  status =
      blink_standalone_renderer_set_document_html(renderer, remote_image_html,
                                                  "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_smoke: remote-image html failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_smoke: remote-image advance failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_frame_output_t remote_output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &remote_output);
  const FramePixelContentStats remote_pixel_stats =
      AnalyzeFramePixelContent(remote_output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      remote_pixel_stats.blue_144a80 < 4000 ||
      remote_pixel_stats.orange_d06329 < 3000) {
    std::fprintf(
        stderr,
        "c_api_smoke: remote-image/no-network raw output invalid status=%d "
        "colored=%zu bg144a80=%zu orange_d06329=%zu opaque_white=%zu "
        "error=%s\n",
        status, remote_pixel_stats.nonwhite_colored,
        remote_pixel_stats.blue_144a80,
        remote_pixel_stats.orange_d06329,
        remote_pixel_stats.opaque_white,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  // Public WASM execution requires a JavaScript entry point in this profile;
  // script, javascript: URL, object, and embed surfaces are rejected above.
  const char* html =
      "<!doctype html><style>body{margin:0}.card{width:80px;height:60px;"
      "background:#2878d8;color:white}input{margin:4px}</style><div id='card' "
      "class='card' data-godot-action='open'>Card</div><label><input "
      "id='agree' type='checkbox' data-godot-action='toggle'>Agree</label>"
      "<input id='name' value='abc' data-godot-action='name'>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "c_api_smoke: set html failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "c_api_smoke: advance failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || !output.pixels || output.width != 160 ||
      output.height != 120 || output.stride < output.width * 4 ||
      output.pixel_count == 0 || output.dirty_rect_count != 1) {
    std::fprintf(stderr,
                 "c_api_smoke: raw output invalid status=%d size=%dx%d "
                 "stride=%d bytes=%zu dirty=%zu format=%d error=%s\n",
                 status, output.width, output.height, output.stride,
                 output.pixel_count, output.dirty_rect_count,
                 output.pixel_format, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const FramePixelContentStats pixel_stats =
      AnalyzeFramePixelContent(output);
  if (pixel_stats.blue_2878d8 < 3000) {
    std::fprintf(stderr,
                 "c_api_smoke: raw output missing expected blue card pixels "
                 "format=%d nontransparent=%zu colored=%zu blue2878d8=%zu "
                 "opaque_white=%zu sample=%u,%u,%u,%u\n",
                 output.pixel_format, pixel_stats.nontransparent,
                 pixel_stats.nonwhite_colored, pixel_stats.blue_2878d8,
                 pixel_stats.opaque_white,
                 output.pixel_count >= 4 ? output.pixels[0] : 0,
                 output.pixel_count >= 4 ? output.pixels[1] : 0,
                 output.pixel_count >= 4 ? output.pixels[2] : 0,
                 output.pixel_count >= 4 ? output.pixels[3] : 0);
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  bool saw_card = false;
  bool saw_checkbox = false;
  bool saw_input = false;
  blink_standalone_rect_t card_bounds = {};
  blink_standalone_rect_t checkbox_bounds = {};
  blink_standalone_rect_t input_bounds = {};
  const size_t hit_count = blink_standalone_renderer_hit_metadata_count(renderer);
  for (size_t i = 0; i < hit_count; ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) != BLINK_STANDALONE_STATUS_OK) {
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
  blink_standalone_hit_metadata_t point_hit = {};
  if (saw_card &&
      blink_standalone_renderer_hit_test(renderer, card_bounds.x + card_bounds.width * 0.5f,
                             card_bounds.y + card_bounds.height * 0.5f,
                             &point_hit) != BLINK_STANDALONE_STATUS_OK) {
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
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float checkbox_x = checkbox_bounds.x + checkbox_bounds.width * 0.5f;
  const float checkbox_y = checkbox_bounds.y + checkbox_bounds.height * 0.5f;
  blink_standalone_renderer_mouse_move(renderer, checkbox_x, checkbox_y, 0);
  blink_standalone_renderer_mouse_down(renderer, checkbox_x, checkbox_y,
                           BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  blink_standalone_renderer_mouse_up(renderer, checkbox_x, checkbox_y,
                         BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  status = blink_standalone_renderer_advance_frame(renderer, 0.016);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_smoke: checkbox click advance failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  bool checkbox_checked = false;
  for (size_t i = 0; i < blink_standalone_renderer_hit_metadata_count(renderer); ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) != BLINK_STANDALONE_STATUS_OK) {
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
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float input_x = input_bounds.x + input_bounds.width * 0.5f;
  const float input_y = input_bounds.y + input_bounds.height * 0.5f;
  blink_standalone_renderer_mouse_move(renderer, input_x, input_y, 0);
  blink_standalone_renderer_mouse_down(renderer, input_x, input_y, BLINK_STANDALONE_MOUSE_BUTTON_LEFT,
                           0, 1);
  blink_standalone_renderer_mouse_up(renderer, input_x, input_y, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0,
                         1);
  blink_standalone_renderer_text_input(renderer, "Z");
  status = blink_standalone_renderer_advance_frame(renderer, 0.032);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_smoke: text focus advance failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  bool input_focused = false;
  for (size_t i = 0; i < blink_standalone_renderer_hit_metadata_count(renderer); ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) != BLINK_STANDALONE_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == "name" && hit.focused) {
      input_focused = true;
      break;
    }
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  if (!input_focused) {
    std::fprintf(stderr, "c_api_smoke: input did not focus through C API\n");
    return 1;
  }
  std::printf(
      "c_api_smoke: ok raw=%dx%d stride=%d bytes=%zu dirty=%zu hits=%zu "
      "colored=%zu blue2878d8=%zu\n",
      output.width, output.height, output.stride, output.pixel_count,
      output.dirty_rect_count, hit_count, pixel_stats.nonwhite_colored,
      pixel_stats.blue_2878d8);
  return 0;
}

bool HasHitId(blink_standalone_renderer_t* renderer, const char* expected_id);
bool HitCheckedStateIs(blink_standalone_renderer_t* renderer,
                       const char* expected_id,
                       bool checked);
bool GetFormStateById(blink_standalone_renderer_t* renderer,
                      const char* expected_id,
                      blink_standalone_form_control_state_t* out);
std::string FormStateValue(
    const blink_standalone_form_control_state_t& state);
bool AdvanceCApiFrameForSmoke(blink_standalone_renderer_t* renderer,
                              double time,
                              const char* label);
bool ClickPointForSmoke(blink_standalone_renderer_t* renderer,
                        float x,
                        float y,
                        int click_count,
                        double* time,
                        const char* label);

int RunCApiViewportResizeSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 256;
  config.height = 128;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: create failed status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style>body{margin:0;font:16px monospace}"
      "#box{width:100vw;height:100vh;background:linear-gradient(90deg,#135,#fa4)}"
      "label{position:absolute;left:12px;top:52px;background:white;padding:6px}"
      "#name{position:absolute;left:12px;top:14px;width:150px;font:16px monospace}"
      "</style><div id='box' data-godot-action='box'>"
      "<input id='name' value='persist' data-godot-action='name'>"
      "<label><input id='agree' type='checkbox' "
      "data-godot-action='toggle'>Agree</label></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: initial advance failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 256 ||
      output.height != 128 || !output.pixels || output.pixel_count == 0) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: initial raw output invalid "
                 "status=%d size=%dx%d bytes=%zu error=%s\n",
                 status, output.width, output.height, output.pixel_count,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_hit_metadata_t name_hit = {};
  blink_standalone_rect_t checkbox_bounds = {};
  bool saw_checkbox = false;
  bool saw_name = false;
  for (size_t i = 0; i < blink_standalone_renderer_hit_metadata_count(renderer);
       ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) !=
        BLINK_STANDALONE_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == "name") {
      name_hit = hit;
      saw_name = hit.bounds.width > 0.0f && hit.bounds.height > 0.0f;
    }
    if (id == "agree") {
      checkbox_bounds = hit.bounds;
      saw_checkbox = checkbox_bounds.width > 0.0f &&
                     checkbox_bounds.height > 0.0f;
    }
  }
  if (!saw_name || !saw_checkbox) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: form metadata missing "
                 "name=%d checkbox=%d\n",
                 saw_name ? 1 : 0, saw_checkbox ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  double time = 0.016;
  const float name_x = name_hit.bounds.x + name_hit.bounds.width - 8.0f;
  const float name_y = name_hit.bounds.y + name_hit.bounds.height * 0.5f;
  if (!ClickPointForSmoke(renderer, name_x, name_y, 1, &time,
                          "c_api_viewport_resize_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_text_input(renderer, "Z");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_viewport_resize_smoke")) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: text input failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_form_control_state_t form_state = {};
  if (!GetFormStateById(renderer, "name", &form_state) ||
      FormStateValue(form_state).find('Z') == std::string::npos) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: input state did not update "
                 "before resize value=%s\n",
                 FormStateValue(form_state).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  const float checkbox_x = checkbox_bounds.x + checkbox_bounds.width * 0.5f;
  const float checkbox_y = checkbox_bounds.y + checkbox_bounds.height * 0.5f;
  blink_standalone_renderer_mouse_move(renderer, checkbox_x, checkbox_y, 0);
  blink_standalone_renderer_mouse_down(renderer, checkbox_x, checkbox_y,
                                       BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0,
                                       1);
  blink_standalone_renderer_mouse_up(renderer, checkbox_x, checkbox_y,
                                     BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  status = blink_standalone_renderer_advance_frame(renderer, 0.016);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: checkbox advance failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status =
      blink_standalone_renderer_set_viewport(renderer, 256, 128, 2.0f);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: set viewport failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.032);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: resized advance failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 512 ||
      output.height != 256 || !output.pixels || output.pixel_count == 0) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: dsf raw output invalid "
                 "status=%d size=%dx%d bytes=%zu error=%s\n",
                 status, output.width, output.height, output.pixel_count,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  bool box_bounds_remain_logical = false;
  bool checkbox_still_checked = false;
  for (size_t i = 0; i < blink_standalone_renderer_hit_metadata_count(renderer);
       ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) !=
        BLINK_STANDALONE_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == "box" && hit.bounds.width <= 257.0f &&
        hit.bounds.height <= 129.0f) {
      box_bounds_remain_logical = true;
    }
    if (id == "agree" && hit.checked) {
      checkbox_still_checked = true;
    }
  }
  if (!GetFormStateById(renderer, "name", &form_state) ||
      FormStateValue(form_state).find('Z') == std::string::npos) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: input state was not preserved "
                 "across dsf change value=%s\n",
                 FormStateValue(form_state).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (!box_bounds_remain_logical || !checkbox_still_checked) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: state/logical metadata failed "
                 "after dsf change box_logical=%d checked=%d\n",
                 box_bounds_remain_logical ? 1 : 0,
                 checkbox_still_checked ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status =
      blink_standalone_renderer_set_viewport(renderer, 300, 160, 1.5f);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: second set viewport failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.048);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: second resized advance failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 450 ||
      output.height != 240 || !output.pixels || output.pixel_count == 0) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: second resized raw output "
                 "invalid status=%d size=%dx%d bytes=%zu error=%s\n",
                 status, output.width, output.height, output.pixel_count,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (!GetFormStateById(renderer, "name", &form_state) ||
      FormStateValue(form_state).find('Z') == std::string::npos ||
      !HitCheckedStateIs(renderer, "agree", true) || !HasHitId(renderer, "box")) {
    std::fprintf(stderr,
                 "c_api_viewport_resize_smoke: state was not preserved across "
                 "second resize value=%s\n",
                 FormStateValue(form_state).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const int final_width = output.width;
  const int final_height = output.height;
  const size_t final_bytes = output.pixel_count;
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_viewport_resize_smoke: ok initial=256x128 dsf2=512x256 "
      "resized=%dx%d bytes=%zu state=persisted\n",
      final_width, final_height, final_bytes);
  return 0;
}

uint64_t HashFramePixels(const blink_standalone_frame_output_t& output) {
  uint64_t hash = 1469598103934665603ull;
  for (size_t i = 0; output.pixels && i < output.pixel_count; ++i) {
    hash ^= static_cast<uint64_t>(output.pixels[i]);
    hash *= 1099511628211ull;
  }
  return hash;
}

bool FrameHasNonUniformPixels(const blink_standalone_frame_output_t& output) {
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

FramePixelContentStats AnalyzeFramePixelContent(
    const blink_standalone_frame_output_t& output) {
  FramePixelContentStats stats;
  if (!output.pixels || output.width <= 0 || output.height <= 0 ||
      output.stride < output.width * 4) {
    return stats;
  }
  if (output.pixel_format != BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 &&
      output.pixel_format != BLINK_STANDALONE_PIXEL_FORMAT_BGRA8) {
    return stats;
  }
  auto near_color = [](uint8_t actual, uint8_t expected) {
    const int delta = static_cast<int>(actual) - static_cast<int>(expected);
    return delta >= -12 && delta <= 12;
  };
  auto matches = [&](uint8_t red,
                     uint8_t green,
                     uint8_t blue,
                     uint8_t expected_red,
                     uint8_t expected_green,
                     uint8_t expected_blue) {
    return near_color(red, expected_red) &&
           near_color(green, expected_green) &&
           near_color(blue, expected_blue);
  };
  for (int y = 0; y < output.height; ++y) {
    const uint8_t* row =
        output.pixels + static_cast<size_t>(y) * output.stride;
    for (int x = 0; x < output.width; ++x) {
      const uint8_t* pixel = row + static_cast<size_t>(x) * 4;
      const uint8_t red =
          output.pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 ? pixel[0]
                                                                     : pixel[2];
      const uint8_t green = pixel[1];
      const uint8_t blue =
          output.pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 ? pixel[2]
                                                                     : pixel[0];
      const uint8_t alpha = pixel[3];
      if (alpha == 0) {
        ++stats.transparent;
        continue;
      }
      ++stats.nontransparent;
      if (red >= 245 && green >= 245 && blue >= 245) {
        ++stats.opaque_white;
      } else {
        ++stats.nonwhite_colored;
      }
      if (matches(red, green, blue, 0x11, 0x22, 0x33)) {
        ++stats.dark_blue_112233;
      }
      if (matches(red, green, blue, 0x12, 0x34, 0x56)) {
        ++stats.dark_blue_123456;
      }
      if (matches(red, green, blue, 0x28, 0x78, 0xd8)) {
        ++stats.blue_2878d8;
      }
      if (matches(red, green, blue, 0x14, 0x4a, 0x80)) {
        ++stats.blue_144a80;
      }
      if (matches(red, green, blue, 0xdd, 0x77, 0x44)) {
        ++stats.orange_dd7744;
      }
      if (matches(red, green, blue, 0xd0, 0x63, 0x29)) {
        ++stats.orange_d06329;
      }
      if (matches(red, green, blue, 0xe8, 0x44, 0x44)) {
        ++stats.resource_red_e84444;
      }
      if (matches(red, green, blue, 0x23, 0x7a, 0x57)) {
        ++stats.resource_green_237a57;
      }
    }
  }
  return stats;
}

bool GetHitById(blink_standalone_renderer_t* renderer,
                const char* expected_id,
                blink_standalone_hit_metadata_t* out) {
  for (size_t i = 0; i < blink_standalone_renderer_hit_metadata_count(renderer); ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) != BLINK_STANDALONE_STATUS_OK) {
      continue;
    }
    const std::string id = hit.element_id ? hit.element_id : "";
    if (id == expected_id) {
      if (out) {
        *out = hit;
      }
      return true;
    }
  }
  return false;
}

bool HasHitId(blink_standalone_renderer_t* renderer, const char* expected_id) {
  return GetHitById(renderer, expected_id, nullptr);
}

bool HitCheckedStateIs(blink_standalone_renderer_t* renderer,
                       const char* expected_id,
                       bool checked) {
  blink_standalone_hit_metadata_t hit = {};
  return GetHitById(renderer, expected_id, &hit) &&
         ((hit.checked != 0) == checked);
}

bool GetFormStateById(blink_standalone_renderer_t* renderer,
                      const char* expected_id,
                      blink_standalone_form_control_state_t* out) {
  return blink_standalone_renderer_get_form_control_state_by_id(
             renderer, expected_id, out) == BLINK_STANDALONE_STATUS_OK;
}

std::string FormStateValue(
    const blink_standalone_form_control_state_t& state) {
  return state.value ? state.value : "";
}

bool AdvanceCApiFrameForSmoke(blink_standalone_renderer_t* renderer,
                              double time,
                              const char* label) {
  const blink_standalone_status_code_t status =
      blink_standalone_renderer_advance_frame(renderer, time);
  if (status == BLINK_STANDALONE_STATUS_OK) {
    return true;
  }
  std::fprintf(stderr, "%s: advance failed status=%d error=%s\n", label,
               status, blink_standalone_renderer_last_error(renderer));
  return false;
}

bool ClickPointForSmoke(blink_standalone_renderer_t* renderer,
                        float x,
                        float y,
                        int click_count,
                        double* time,
                        const char* label) {
  blink_standalone_renderer_mouse_move(renderer, x, y, 0);
  if (!AdvanceCApiFrameForSmoke(renderer, *time, label)) {
    return false;
  }
  *time += 0.016;
  blink_standalone_renderer_mouse_down(
      renderer, x, y, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, click_count);
  if (!AdvanceCApiFrameForSmoke(renderer, *time, label)) {
    return false;
  }
  *time += 0.016;
  blink_standalone_renderer_mouse_up(renderer, x, y,
                                     BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0,
                                     click_count);
  if (!AdvanceCApiFrameForSmoke(renderer, *time, label)) {
    return false;
  }
  *time += 0.016;
  return true;
}

bool TextInputForSmoke(blink_standalone_renderer_t* renderer,
                       const char* text,
                       double* time,
                       const char* label) {
  const blink_standalone_status_code_t status =
      blink_standalone_renderer_text_input(renderer, text);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: text_input failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  if (!AdvanceCApiFrameForSmoke(renderer, *time, label)) {
    return false;
  }
  *time += 0.016;
  return true;
}

bool KeyPressForSmoke(blink_standalone_renderer_t* renderer,
                      blink_standalone_key_t key,
                      double* time,
                      const char* label) {
  blink_standalone_status_code_t status =
      blink_standalone_renderer_key_down(renderer, key, 0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: key_down failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  if (!AdvanceCApiFrameForSmoke(renderer, *time, label)) {
    return false;
  }
  *time += 0.016;
  status = blink_standalone_renderer_key_up(renderer, key, 0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: key_up failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  if (!AdvanceCApiFrameForSmoke(renderer, *time, label)) {
    return false;
  }
  *time += 0.016;
  return true;
}

int RunCApiDomMutationSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 260;
  config.height = 170;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: create failed status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style id='theme'>body{margin:0;font:16px monospace}"
      "#card{position:absolute;left:12px;top:12px;width:130px;height:58px;"
      "background:#2878d8;color:white;padding:8px}"
      "#name{position:absolute;left:12px;top:92px;width:150px}"
      "label{position:absolute;left:12px;top:124px}</style>"
      "<div id='card' data-godot-action='start'>Before</div>"
      "<input id='name' value='persist' data-godot-action='name'>"
      "<label><input id='agree' type='checkbox' "
      "data-godot-action='toggle'>Agree</label>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_dom_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats initial_stats = AnalyzeFramePixelContent(output);
  const uint64_t initial_hash = HashFramePixels(output);
  blink_standalone_hit_metadata_t card_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      initial_stats.blue_2878d8 < 3000 ||
      !GetHitById(renderer, "card", &card_hit) ||
      std::string(card_hit.data_godot_action ? card_hit.data_godot_action
                                             : "") != "start") {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: initial state invalid "
                 "status=%d blue=%zu action=%s\n",
                 status, initial_stats.blue_2878d8,
                 card_hit.data_godot_action ? card_hit.data_godot_action : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_hit_metadata_t name_hit = {};
  blink_standalone_hit_metadata_t checkbox_hit = {};
  if (!GetHitById(renderer, "name", &name_hit) ||
      !GetHitById(renderer, "agree", &checkbox_hit)) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: form hit metadata missing\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  const float name_x = name_hit.bounds.x + name_hit.bounds.width - 8.0f;
  const float name_y = name_hit.bounds.y + name_hit.bounds.height * 0.5f;
  if (!ClickPointForSmoke(renderer, name_x, name_y, 1, &time,
                          "c_api_dom_mutation_smoke") ||
      !TextInputForSmoke(renderer, "Z", &time,
                         "c_api_dom_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const float checkbox_x =
      checkbox_hit.bounds.x + checkbox_hit.bounds.width * 0.5f;
  const float checkbox_y =
      checkbox_hit.bounds.y + checkbox_hit.bounds.height * 0.5f;
  if (!ClickPointForSmoke(renderer, checkbox_x, checkbox_y, 1, &time,
                          "c_api_dom_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (blink_standalone_renderer_set_element_attribute(
          renderer, "card", "onclick", "alert(1)") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_set_element_attribute(
          renderer, "card", "href", " javascript:alert(1)") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: no-script mutation rejection "
                 "failed\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_element_text(renderer, "card", "After");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_element_attribute(
                     renderer, "card", "data-godot-action", "updated")
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_element_style(
                     renderer,
                     "card",
                     "position:absolute;left:12px;top:12px;width:130px;"
                     "height:58px;background:#d06329;color:white;padding:8px")
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: first mutation failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats orange_stats = AnalyzeFramePixelContent(output);
  const uint64_t orange_hash = HashFramePixels(output);
  card_hit = {};
  blink_standalone_form_control_state_t form_state = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      orange_stats.orange_d06329 < 3000 || orange_hash == initial_hash ||
      !GetHitById(renderer, "card", &card_hit) ||
      std::string(card_hit.data_godot_action ? card_hit.data_godot_action
                                             : "") != "updated" ||
      !GetFormStateById(renderer, "name", &form_state) ||
      FormStateValue(form_state).find('Z') == std::string::npos ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: first mutation not reflected "
                 "status=%d orange=%zu action=%s value=%s checked=%d\n",
                 status, orange_stats.orange_d06329,
                 card_hit.data_godot_action ? card_hit.data_godot_action : "",
                 FormStateValue(form_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_remove_element_attribute(
      renderer, "card", "data-godot-action");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: remove attribute failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  card_hit = {};
  if (!GetHitById(renderer, "card", &card_hit) ||
      (card_hit.data_godot_action && *card_hit.data_godot_action)) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: action attribute still present "
                 "action=%s\n",
                 card_hit.data_godot_action ? card_hit.data_godot_action : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_remove_element_attribute(
      renderer, "card", "style");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_replace_stylesheet_text(
                     renderer,
                     "theme",
                     "body{margin:0;font:16px monospace}"
                     "#card{position:absolute;left:12px;top:12px;width:130px;"
                     "height:58px;background:#237a57;color:white;padding:8px}"
                     "#name{position:absolute;left:12px;top:92px;width:150px}"
                     "label{position:absolute;left:12px;top:124px}")
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: stylesheet mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats green_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      green_stats.resource_green_237a57 < 3000 ||
      !GetFormStateById(renderer, "name", &form_state) ||
      FormStateValue(form_state).find('Z') == std::string::npos ||
      !HitCheckedStateIs(renderer, "agree", true) ||
      !HasHitId(renderer, "card")) {
    std::fprintf(stderr,
                 "c_api_dom_mutation_smoke: stylesheet mutation not reflected "
                 "status=%d green=%zu orange=%zu blue=%zu value=%s "
                 "checked=%d\n",
                 status, green_stats.resource_green_237a57,
                 green_stats.orange_d06329, green_stats.blue_2878d8,
                 FormStateValue(form_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_dom_mutation_smoke: ok blue=%zu orange=%zu green=%zu "
      "state=persisted\n",
      initial_stats.blue_2878d8, orange_stats.orange_d06329,
      green_stats.resource_green_237a57);
  return 0;
}

int RunCApiFragmentMutationSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 300;
  config.height = 180;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style id='theme'>body{margin:0;font:16px monospace}"
      "#target{position:absolute;left:10px;top:10px;width:150px;height:62px}"
      "#old{position:absolute;left:0;top:0;width:120px;height:46px;"
      "background:#2878d8;color:white}"
      "#name{position:absolute;left:10px;top:92px;width:140px}"
      "label{position:absolute;left:10px;top:128px}</style>"
      "<div id='target'><div id='old' data-godot-action='old'>Old</div></div>"
      "<input id='name' value='seed' data-godot-action='name'>"
      "<label><input id='agree' type='checkbox' "
      "data-godot-action='toggle'>Agree</label>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_fragment_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats initial_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      initial_stats.blue_2878d8 < 2000 || !HasHitId(renderer, "old") ||
      !HasHitId(renderer, "target")) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: initial output invalid "
                 "status=%d blue=%zu old=%d target=%d\n",
                 status, initial_stats.blue_2878d8,
                 HasHitId(renderer, "old") ? 1 : 0,
                 HasHitId(renderer, "target") ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  if (blink_standalone_renderer_set_element_inner_html(
          renderer, "missing-target", "<span>Missing</span>") !=
      BLINK_STANDALONE_STATUS_INVALID_ARGUMENT) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: missing target was accepted\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_form_control_value(renderer, "name",
                                                            "persisted");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_form_control_checked(
                     renderer, "agree", 1)
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_focus_element(renderer, "name")
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_fragment_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: state setup failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;

  if (blink_standalone_renderer_set_element_inner_html(
          renderer, "target", "<script>alert(1)</script>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_set_element_inner_html(
          renderer, "target", "<button onclick='alert(1)'>Bad</button>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_set_element_inner_html(
          renderer, "target", "<a href=' javaScript:alert(1)'>Bad</a>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: no-script fragment rejection "
                 "failed\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_element_inner_html(
      renderer, "target",
      "<section id='panel' data-godot-action='panel' "
      "style='position:absolute;left:0;top:0;width:130px;height:50px;"
      "background:#e84444;color:white'><span id='child'>New</span></section>");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_fragment_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: fragment mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;

  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats replaced_stats = AnalyzeFramePixelContent(output);
  blink_standalone_form_control_state_t name_state = {};
  blink_standalone_hit_metadata_t panel_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      replaced_stats.resource_red_e84444 < 3000 || HasHitId(renderer, "old") ||
      !GetHitById(renderer, "panel", &panel_hit) ||
      std::string(panel_hit.data_godot_action ? panel_hit.data_godot_action
                                              : "") != "panel" ||
      !HasHitId(renderer, "child") ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" || name_state.focused == 0 ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: replacement not reflected "
                 "status=%d red=%zu old=%d panel=%d child=%d value=%s "
                 "focused=%d checked=%d action=%s\n",
                 status, replaced_stats.resource_red_e84444,
                 HasHitId(renderer, "old") ? 1 : 0,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 HasHitId(renderer, "child") ? 1 : 0,
                 FormStateValue(name_state).c_str(), name_state.focused,
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0,
                 panel_hit.data_godot_action ? panel_hit.data_godot_action : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_set_element_inner_html(
      renderer, "target",
      "<input id='inner' value='inside' style='position:absolute;left:0;top:0;"
      "width:120px;height:24px'>");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_focus_element(renderer, "inner")
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_fragment_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: focused subtree setup failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_form_control_state_t inner_state = {};
  if (!GetFormStateById(renderer, "inner", &inner_state) ||
      inner_state.focused == 0) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: inner focus setup invalid\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_element_inner_html(
      renderer, "target",
      "<section id='panel2' data-godot-action='panel2' "
      "style='position:absolute;left:0;top:0;width:110px;height:44px;"
      "background:#d06329;color:white'>Done</section>");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_fragment_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: focused subtree replace "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats final_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      final_stats.orange_d06329 < 2000 || HasHitId(renderer, "inner") ||
      !HasHitId(renderer, "panel2") ||
      GetFormStateById(renderer, "inner", &inner_state) ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_fragment_mutation_smoke: focused subtree replacement "
                 "invalid status=%d orange=%zu inner_hit=%d inner_state=%d "
                 "panel2=%d value=%s checked=%d\n",
                 status, final_stats.orange_d06329,
                 HasHitId(renderer, "inner") ? 1 : 0,
                 GetFormStateById(renderer, "inner", &inner_state) ? 1 : 0,
                 HasHitId(renderer, "panel2") ? 1 : 0,
                 FormStateValue(name_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_fragment_mutation_smoke: ok blue=%zu red=%zu orange=%zu "
      "state=persisted\n",
      initial_stats.blue_2878d8, replaced_stats.resource_red_e84444,
      final_stats.orange_d06329);
  return 0;
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

int RunCApiBodyMutationSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 320;
  config.height = 200;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  if (blink_standalone_renderer_set_body_inner_html(
          renderer, "<main id='early'>Early</main>") !=
      BLINK_STANDALONE_STATUS_INVALID_ARGUMENT) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: missing live body was accepted\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const char* html =
      "<!doctype html><html><head><style id='theme'>"
      "html,body{margin:0;padding:0;background:rgba(0,0,0,0);"
      "font:16px monospace}"
      "#panel{position:absolute;left:8px;top:8px;width:140px;height:56px;"
      "background:#2878d8;color:white}"
      "#body_panel{position:absolute;left:0;top:0;width:165px;height:70px;"
      "background:#e84444;color:white}"
      "#body_button{position:absolute;left:0;top:90px;width:120px;height:34px}"
      "#name{position:absolute;left:8px;top:82px;width:150px}"
      "label{position:absolute;left:8px;top:120px}"
      "</style></head><body>"
      "<div id='panel' data-godot-action='old'>Old body</div>"
      "<input id='name' value='seed' data-godot-action='name'>"
      "<label><input id='agree' type='checkbox' "
      "data-godot-action='agree'>Agree</label>"
      "</body></html>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_body_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats initial_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      initial_stats.blue_2878d8 < 3000 || !HasHitId(renderer, "panel") ||
      !HasHitId(renderer, "name") || !HasHitId(renderer, "agree")) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: initial output invalid status=%d "
                 "blue=%zu panel=%d name=%d agree=%d\n",
                 status, initial_stats.blue_2878d8,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 HasHitId(renderer, "name") ? 1 : 0,
                 HasHitId(renderer, "agree") ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_set_form_control_value(renderer, "name",
                                                            "persisted");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_form_control_checked(
                     renderer, "agree", 1)
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_focus_element(renderer, "name")
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_body_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: old body state setup failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_form_control_state_t name_state = {};
  if (!GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" || name_state.focused == 0 ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: old body state was not set "
                 "value=%s focused=%d checked=%d\n",
                 FormStateValue(name_state).c_str(), name_state.focused,
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (blink_standalone_renderer_set_body_inner_html(
          renderer, "<script>alert(1)</script>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_set_body_inner_html(
          renderer, "<button onclick='alert(1)'>Bad</button>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_set_body_inner_html(
          renderer, "<a href='javascript:alert(1)'>Bad</a>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_set_body_inner_html(
          renderer, "<iframe src='about:blank'></iframe>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: no-script fragment rejection "
                 "failed\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_body_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  if (!HasHitId(renderer, "panel") || !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted") {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: rejected body fragment mutated "
                 "document panel=%d value=%s\n",
                 HasHitId(renderer, "panel") ? 1 : 0,
                 FormStateValue(name_state).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_body_inner_html(
      renderer,
      "<main id='body_panel' data-godot-action='body'>"
      "<span id='body_child'>New body</span></main>"
      "<button id='body_button' data-godot-action='button'>Press</button>");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_body_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: body replacement failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats replaced_stats = AnalyzeFramePixelContent(output);
  blink_standalone_hit_metadata_t body_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      replaced_stats.resource_red_e84444 < 6000 ||
      !GetHitById(renderer, "body_panel", &body_hit) ||
      std::string(body_hit.data_godot_action ? body_hit.data_godot_action
                                             : "") != "body" ||
      !HasHitId(renderer, "body_child") ||
      !HasHitId(renderer, "body_button") || HasHitId(renderer, "panel") ||
      HasHitId(renderer, "name") || HasHitId(renderer, "agree") ||
      GetFormStateById(renderer, "name", &name_state)) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: body replacement not reflected "
                 "status=%d red=%zu body=%d child=%d button=%d old=%d "
                 "name_hit=%d name_state=%d action=%s\n",
                 status, replaced_stats.resource_red_e84444,
                 HasHitId(renderer, "body_panel") ? 1 : 0,
                 HasHitId(renderer, "body_child") ? 1 : 0,
                 HasHitId(renderer, "body_button") ? 1 : 0,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 HasHitId(renderer, "name") ? 1 : 0,
                 GetFormStateById(renderer, "name", &name_state) ? 1 : 0,
                 body_hit.data_godot_action ? body_hit.data_godot_action : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_replace_stylesheet_text(
      renderer,
      "theme",
      "html,body{margin:0;padding:0;background:rgba(0,0,0,0);"
      "font:16px monospace}"
      "#body_panel{position:absolute;left:0;top:0;width:165px;height:70px;"
      "background:#237a57;color:white}"
      "#body_button{position:absolute;left:0;top:90px;width:120px;height:34px}");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_body_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: stylesheet after body replacement "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats stylesheet_stats =
      AnalyzeFramePixelContent(output);
  body_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      stylesheet_stats.resource_green_237a57 < 6000 ||
      !GetHitById(renderer, "body_panel", &body_hit) ||
      std::string(body_hit.data_godot_action ? body_hit.data_godot_action
                                             : "") != "body" ||
      !HasHitId(renderer, "body_button") || HasHitId(renderer, "name")) {
    std::fprintf(stderr,
                 "c_api_body_mutation_smoke: stylesheet after body replacement "
                 "not reflected status=%d green=%zu body=%d button=%d "
                 "name=%d action=%s\n",
                 status, stylesheet_stats.resource_green_237a57,
                 HasHitId(renderer, "body_panel") ? 1 : 0,
                 HasHitId(renderer, "body_button") ? 1 : 0,
                 HasHitId(renderer, "name") ? 1 : 0,
                 body_hit.data_godot_action ? body_hit.data_godot_action : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_body_mutation_smoke: ok blue=%zu red=%zu green=%zu "
      "old_state_cleared=1\n",
      initial_stats.blue_2878d8, replaced_stats.resource_red_e84444,
      stylesheet_stats.resource_green_237a57);
  return 0;
}

int RunCApiSeparatedClickSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 240;
  config.height = 120;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_separated_click_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style>html,body{margin:0;background:transparent}"
      "button{font-size:32px;padding:12px 24px;background:#d06329;color:#fff;"
      "border:2px solid #112233}</style><button id='play' "
      "data-godot-action='play'>Play</button>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_separated_click_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const auto capture_and_check = [&](const char* phase) -> bool {
    blink_standalone_frame_output_t output = {};
    const blink_standalone_status_code_t output_status =
        blink_standalone_renderer_get_latest_output(renderer, &output);
    const FramePixelContentStats stats = AnalyzeFramePixelContent(output);
    const bool ok = output_status == BLINK_STANDALONE_STATUS_OK &&
                    output.width == 240 && output.height == 120 &&
                    output.stride >= output.width * 4 && output.pixels &&
                    output.pixel_count > 0 && stats.orange_d06329 > 2000 &&
                    HasHitId(renderer, "play");
    if (!ok) {
      std::fprintf(stderr,
                   "c_api_separated_click_smoke: %s output invalid "
                   "status=%d size=%dx%d bytes=%zu orange=%zu hits=%zu "
                   "error=%s\n",
                   phase, output_status, output.width, output.height,
                   output.pixel_count, stats.orange_d06329,
                   blink_standalone_renderer_hit_metadata_count(renderer),
                   blink_standalone_renderer_last_error(renderer));
    }
    blink_standalone_renderer_release_latest_output(renderer);
    return ok;
  };

  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK || !capture_and_check("initial")) {
    std::fprintf(stderr,
                 "c_api_separated_click_smoke: initial advance failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_hit_metadata_t play_hit = {};
  if (!GetHitById(renderer, "play", &play_hit) ||
      std::string(play_hit.tag_name ? play_hit.tag_name : "") != "button" ||
      std::string(play_hit.data_godot_action ? play_hit.data_godot_action
                                             : "") != "play") {
    std::fprintf(stderr,
                 "c_api_separated_click_smoke: button metadata missing\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float x = play_hit.bounds.x + play_hit.bounds.width * 0.5f;
  const float y = play_hit.bounds.y + play_hit.bounds.height * 0.5f;
  for (int click_index = 0; click_index < 3; ++click_index) {
    char phase[64];

    blink_standalone_renderer_mouse_move(renderer, x, y, 0);
    status =
        blink_standalone_renderer_advance_frame(renderer,
                                                0.016 + click_index * 0.050);
    std::snprintf(phase, sizeof(phase), "after move %d", click_index + 1);
    if (status != BLINK_STANDALONE_STATUS_OK || !capture_and_check(phase)) {
      std::fprintf(stderr,
                   "c_api_separated_click_smoke: mouse-move advance failed "
                   "click=%d status=%d error=%s\n",
                   click_index + 1, status,
                   blink_standalone_renderer_last_error(renderer));
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }

    const int click_count = click_index + 1;
    blink_standalone_renderer_mouse_down(renderer, x, y,
                                         BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0,
                                         click_count);
    status =
        blink_standalone_renderer_advance_frame(renderer,
                                                0.032 + click_index * 0.050);
    std::snprintf(phase, sizeof(phase), "after down %d", click_index + 1);
    if (status != BLINK_STANDALONE_STATUS_OK || !capture_and_check(phase)) {
      std::fprintf(stderr,
                   "c_api_separated_click_smoke: mouse-down advance failed "
                   "click=%d status=%d error=%s\n",
                   click_index + 1, status,
                   blink_standalone_renderer_last_error(renderer));
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }

    blink_standalone_renderer_mouse_up(
        renderer, x, y, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, click_count);
    status =
        blink_standalone_renderer_advance_frame(renderer,
                                                0.048 + click_index * 0.050);
    std::snprintf(phase, sizeof(phase), "after up %d", click_index + 1);
    if (status != BLINK_STANDALONE_STATUS_OK || !capture_and_check(phase) ||
        !HasHitId(renderer, "play")) {
      std::fprintf(stderr,
                   "c_api_separated_click_smoke: mouse-up advance failed "
                   "click=%d status=%d error=%s\n",
                   click_index + 1, status,
                   blink_standalone_renderer_last_error(renderer));
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }
  }

  std::printf(
      "c_api_separated_click_smoke: ok raw=240x120 clicks=3 hits=%zu "
      "action=play\n",
      blink_standalone_renderer_hit_metadata_count(renderer));
  blink_standalone_renderer_destroy(renderer);
  return 0;
}

int RunCApiTextInputSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 520;
  config.height = 260;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr, "c_api_text_input_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;padding:12px;font:20px monospace;"
      "background:#112233;color:#fff}.row{margin:10px 0}input,textarea{"
      "font:20px monospace;padding:4px;border:2px solid #d06329;background:#fff;"
      "color:#111}#name{width:260px}#bio{width:360px;height:70px}</style>"
      "<div class='row'><input id='name' value='abcdef' "
      "data-godot-action='name'></div>"
      "<div class='row'><textarea id='bio' data-godot-action='bio'></textarea>"
      "</div><label><input id='agree' type='checkbox' "
      "data-godot-action='agree'>Agree</label>"
      "<label><input id='r1' type='radio' name='mode' checked "
      "data-godot-action='r1'>One</label>"
      "<label><input id='r2' type='radio' name='mode' "
      "data-godot-action='r2'>Two</label>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: set html failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time, "c_api_text_input_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;

  blink_standalone_hit_metadata_t name_hit = {};
  blink_standalone_hit_metadata_t bio_hit = {};
  blink_standalone_hit_metadata_t agree_hit = {};
  blink_standalone_hit_metadata_t r2_hit = {};
  if (!GetHitById(renderer, "name", &name_hit) ||
      !GetHitById(renderer, "bio", &bio_hit) ||
      !GetHitById(renderer, "agree", &agree_hit) ||
      !GetHitById(renderer, "r2", &r2_hit)) {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: expected hit metadata missing "
                 "hits=%zu\n",
                 blink_standalone_renderer_hit_metadata_count(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_form_control_state_t state = {};
  if (!GetFormStateById(renderer, "name", &state) ||
      FormStateValue(state) != "abcdef" || state.selection_offsets_present == 0) {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: initial input state invalid "
                 "value=%s selection=%d\n",
                 state.value ? state.value : "(null)",
                 state.selection_offsets_present);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float name_y = name_hit.bounds.y + name_hit.bounds.height * 0.5f;
  const float name_left_x = name_hit.bounds.x + 8.0f;
  const float name_right_x = name_hit.bounds.x + name_hit.bounds.width - 8.0f;
  if (!ClickPointForSmoke(renderer, name_left_x, name_y, 1, &time,
                          "c_api_text_input_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (!GetFormStateById(renderer, "name", &state) || state.focused == 0) {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: input did not focus after click\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (!TextInputForSmoke(renderer, "Z", &time, "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "name", &state)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const std::string after_left_insert = FormStateValue(state);
  if (after_left_insert != "Zabcdef") {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: left caret insertion failed "
                 "value=%s\n",
                 after_left_insert.c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (!ClickPointForSmoke(renderer, name_right_x, name_y, 1, &time,
                          "c_api_text_input_smoke") ||
      !TextInputForSmoke(renderer, "Y", &time, "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "name", &state)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (FormStateValue(state) != "ZabcdefY") {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: right caret insertion failed "
                 "value=%s\n",
                 FormStateValue(state).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (!KeyPressForSmoke(renderer, BLINK_STANDALONE_KEY_BACKSPACE, &time,
                        "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "name", &state) ||
      FormStateValue(state) != "Zabcdef") {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: Backspace failed value=%s\n",
                 state.value ? state.value : "(null)");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (!ClickPointForSmoke(renderer, name_left_x, name_y, 1, &time,
                          "c_api_text_input_smoke") ||
      !KeyPressForSmoke(renderer, BLINK_STANDALONE_KEY_DELETE, &time,
                        "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "name", &state) ||
      FormStateValue(state) != "abcdef") {
    std::fprintf(stderr, "c_api_text_input_smoke: Delete failed value=%s\n",
                 state.value ? state.value : "(null)");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float bio_x = bio_hit.bounds.x + 8.0f;
  const float bio_y = bio_hit.bounds.y + 12.0f;
  if (!ClickPointForSmoke(renderer, bio_x, bio_y, 1, &time,
                          "c_api_text_input_smoke") ||
      !TextInputForSmoke(renderer, "h\xC3\xA9", &time,
                         "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "bio", &state) ||
      FormStateValue(state) != "h\xC3\xA9") {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: textarea text insert failed "
                 "value=%s\n",
                 state.value ? state.value : "(null)");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  if (!KeyPressForSmoke(renderer, BLINK_STANDALONE_KEY_ENTER, &time,
                        "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "bio", &state) ||
      FormStateValue(state).find('\n') == std::string::npos) {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: textarea Enter failed value=%s\n",
                 state.value ? state.value : "(null)");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float agree_x = agree_hit.bounds.x + agree_hit.bounds.width * 0.5f;
  const float agree_y = agree_hit.bounds.y + agree_hit.bounds.height * 0.5f;
  if (!ClickPointForSmoke(renderer, agree_x, agree_y, 1, &time,
                          "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "agree", &state) || state.checked == 0) {
    std::fprintf(stderr,
                 "c_api_text_input_smoke: checkbox activation failed\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const float r2_x = r2_hit.bounds.x + r2_hit.bounds.width * 0.5f;
  const float r2_y = r2_hit.bounds.y + r2_hit.bounds.height * 0.5f;
  if (!ClickPointForSmoke(renderer, r2_x, r2_y, 1, &time,
                          "c_api_text_input_smoke") ||
      !GetFormStateById(renderer, "r2", &state) || state.checked == 0 ||
      !GetFormStateById(renderer, "r1", &state) || state.checked != 0) {
    std::fprintf(stderr, "c_api_text_input_smoke: radio activation failed\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  for (int i = 0; i < 3; ++i) {
    if (!ClickPointForSmoke(renderer, name_left_x, name_y, i + 1, &time,
                            "c_api_text_input_smoke") ||
        !GetFormStateById(renderer, "name", &state) || state.focused == 0) {
      std::fprintf(stderr,
                   "c_api_text_input_smoke: repeated text-control click failed "
                   "iteration=%d\n",
                   i + 1);
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }
  }

  const std::string final_name = FormStateValue(state);
  const size_t form_control_count =
      blink_standalone_renderer_form_control_state_count(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_text_input_smoke: ok name=%s textarea=%s form_controls=%zu\n",
      final_name.c_str(), "utf8+newline", form_control_count);
  return 0;
}

int RunCApiFormControlMutationSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 420;
  config.height = 240;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style id='theme'>body{margin:0;padding:12px;"
      "font:18px monospace;background:#112233;color:white}"
      "#panel{position:absolute;left:10px;top:10px;width:390px;height:205px;"
      "background:#2878d8;padding:8px}input,textarea{font:18px monospace;"
      "margin:4px;padding:4px;background:white;color:#111}#name{width:230px}"
      "#bio{width:300px;height:54px}</style>"
      "<div id='panel' data-godot-action='panel'>"
      "<input id='name' value='old' data-godot-action='name'>"
      "<textarea id='bio' data-godot-action='bio'>before</textarea>"
      "<label><input id='agree' type='checkbox' "
      "data-godot-action='agree'>Agree</label>"
      "<label><input id='r1' type='radio' name='mode' checked "
      "data-godot-action='r1'>One</label>"
      "<label><input id='r2' type='radio' name='mode' "
      "data-godot-action='r2'>Two</label></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: set html failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_form_control_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const uint64_t initial_hash = HashFramePixels(output);
  const FramePixelContentStats initial_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      initial_stats.blue_2878d8 < 3000 || !HasHitId(renderer, "panel")) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: initial output invalid "
                 "status=%d blue=%zu\n",
                 status, initial_stats.blue_2878d8);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  if (blink_standalone_renderer_set_element_attribute(
          renderer, "panel", "onclick", "alert(1)") !=
      BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: no-script rejection "
                 "failed\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_form_control_value(renderer, "name",
                                                            "api-value");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_form_control_value(
                     renderer, "bio", "line one\nprogrammatic")
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_form_control_checked(
                     renderer, "agree", 1)
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_form_control_checked(
                     renderer, "r2", 1)
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_focus_element(renderer, "name")
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_text_selection(renderer, "name",
                                                               3, 6)
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_form_control_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: form mutations failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;

  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const uint64_t mutated_hash = HashFramePixels(output);
  blink_standalone_form_control_state_t name_state = {};
  blink_standalone_form_control_state_t bio_state = {};
  if (status != BLINK_STANDALONE_STATUS_OK || mutated_hash == initial_hash ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "api-value" || name_state.focused == 0 ||
      name_state.selection_offsets_present == 0 ||
      name_state.selection_start != 3 || name_state.selection_end != 6 ||
      !GetFormStateById(renderer, "bio", &bio_state) ||
      FormStateValue(bio_state) != "line one\nprogrammatic" ||
      !HitCheckedStateIs(renderer, "agree", true) ||
      !HitCheckedStateIs(renderer, "r2", true) ||
      !HitCheckedStateIs(renderer, "r1", false)) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: mutated state invalid "
                 "status=%d name=%s focused=%d sel=%u:%u bio=%s "
                 "agree=%d r1=%d r2=%d\n",
                 status, FormStateValue(name_state).c_str(),
                 name_state.focused, name_state.selection_start,
                 name_state.selection_end, FormStateValue(bio_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0,
                 HitCheckedStateIs(renderer, "r1", true) ? 1 : 0,
                 HitCheckedStateIs(renderer, "r2", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_focus_element(renderer, "bio");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_text_selection(renderer, "bio",
                                                               0, 4)
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_form_control_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: textarea focus failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  if (!GetFormStateById(renderer, "bio", &bio_state) ||
      bio_state.focused == 0 || bio_state.selection_offsets_present == 0 ||
      bio_state.selection_start != 0 || bio_state.selection_end != 4) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: textarea selection "
                 "invalid focused=%d sel=%u:%u\n",
                 bio_state.focused, bio_state.selection_start,
                 bio_state.selection_end);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_blur_focused_element(renderer);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_form_control_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: blur failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  if (!GetFormStateById(renderer, "bio", &bio_state) ||
      bio_state.focused != 0) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: blur did not clear "
                 "focused state\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_set_element_style(
      renderer, "panel",
      "position:absolute;left:10px;top:10px;width:390px;height:205px;"
      "background:#d06329;padding:8px");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_replace_stylesheet_text(
                     renderer, "theme",
                     "body{margin:0;padding:12px;font:18px monospace;"
                     "background:#112233;color:white}input,textarea{"
                     "font:18px monospace;margin:4px;padding:4px;background:"
                     "white;color:#111}#name{width:230px}#bio{width:300px;"
                     "height:54px}")
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_viewport(renderer, 420, 240,
                                                         2.0f)
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_form_control_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: preservation mutation "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats final_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 840 ||
      output.height != 480 || final_stats.orange_d06329 < 12000 ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "api-value" ||
      !GetFormStateById(renderer, "bio", &bio_state) ||
      FormStateValue(bio_state) != "line one\nprogrammatic" ||
      !HitCheckedStateIs(renderer, "agree", true) ||
      !HitCheckedStateIs(renderer, "r2", true) ||
      !HitCheckedStateIs(renderer, "r1", false) ||
      !HasHitId(renderer, "panel")) {
    std::fprintf(stderr,
                 "c_api_form_control_mutation_smoke: state did not persist "
                 "status=%d size=%dx%d orange=%zu name=%s bio=%s\n",
                 status, output.width, output.height, final_stats.orange_d06329,
                 FormStateValue(name_state).c_str(),
                 FormStateValue(bio_state).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_form_control_mutation_smoke: ok value=api-value textarea=value "
      "checked=agree,r2 selection=covered resize=840x480\n");
  return 0;
}

int RunCApiAbsoluteFormMutationSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 320;
  config.height = 180;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_absolute_form_mutation_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><html><head><style id='theme'>"
      "html,body{margin:0;padding:0;background:rgba(0,0,0,0)}"
      "#box_theme{position:absolute;left:50px;top:0;width:40px;height:40px;"
      "background:rgb(40,120,216)}"
      "button{position:absolute;left:0;top:60px;width:100px;height:36px;"
      "padding:0;border:0;color:white;background:black;font-size:20px}"
      "#name{position:absolute;left:0;top:105px;width:130px;height:22px;"
      "font-size:14px}"
      "#bio{position:absolute;left:140px;top:90px;width:130px;height:48px;"
      "font-size:14px}"
      "#agree{position:absolute;left:0;top:142px}"
      "#r1{position:absolute;left:40px;top:142px}"
      "#r2{position:absolute;left:80px;top:142px}"
      "</style></head><body>"
      "<div id='box_style' style='position:absolute;left:0;top:0;width:40px;"
      "height:40px;background:rgb(40,120,216)'></div>"
      "<div id='box_theme'></div>"
      "<div id='label' style='position:absolute;left:120px;top:0;width:180px;"
      "height:34px;color:white;background:black;font-size:24px;'>A</div>"
      "<button id='action' data-godot-action='old'>Old</button>"
      "<input id='name' value='seed'>"
      "<textarea id='bio'>bio-seed</textarea>"
      "<input id='agree' type='checkbox'>"
      "<input id='r1' type='radio' name='choice' checked>"
      "<input id='r2' type='radio' name='choice'>"
      "</body></html>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_absolute_form_mutation_smoke: set html failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_absolute_form_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_renderer_release_latest_output(renderer);
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_absolute_form_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;

  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats initial_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 320 ||
      output.height != 180 || initial_stats.blue_2878d8 < 2500 ||
      !HasHitId(renderer, "name") || !HasHitId(renderer, "action")) {
    std::fprintf(stderr,
                 "c_api_absolute_form_mutation_smoke: initial output invalid "
                 "status=%d size=%dx%d blue=%zu hits_name=%d hits_action=%d\n",
                 status, output.width, output.height, initial_stats.blue_2878d8,
                 HasHitId(renderer, "name") ? 1 : 0,
                 HasHitId(renderer, "action") ? 1 : 0);
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_set_form_control_value(renderer, "name",
                                                            "api-value");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, 0.0,
                                "c_api_absolute_form_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_absolute_form_mutation_smoke: value mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats mutated_stats = AnalyzeFramePixelContent(output);
  blink_standalone_form_control_state_t name_state = {};
  blink_standalone_form_control_state_t bio_state = {};
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 320 ||
      output.height != 180 || mutated_stats.blue_2878d8 < 2500 ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "api-value" ||
      !GetFormStateById(renderer, "bio", &bio_state) ||
      FormStateValue(bio_state) != "bio-seed" ||
      !HitCheckedStateIs(renderer, "r1", true) ||
      !HitCheckedStateIs(renderer, "r2", false)) {
    std::fprintf(stderr,
                 "c_api_absolute_form_mutation_smoke: mutated state invalid "
                 "status=%d size=%dx%d blue=%zu name=%s bio=%s r1=%d "
                 "r2=%d\n",
                 status, output.width, output.height, mutated_stats.blue_2878d8,
                 FormStateValue(name_state).c_str(),
                 FormStateValue(bio_state).c_str(),
                 HitCheckedStateIs(renderer, "r1", true) ? 1 : 0,
                 HitCheckedStateIs(renderer, "r2", true) ? 1 : 0);
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_absolute_form_mutation_smoke: ok value=api-value raw=320x180\n");
  return 0;
}

int RunCApiEmptyResourceSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 180;
  config.height = 100;
  config.device_scale_factor = 1.0f;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_empty_resource_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  status = blink_standalone_renderer_set_viewport(renderer, 180, 100, 1.0f);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_empty_resource_smoke: set viewport failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;background:#123;color:white}"
      "#box{width:100px;height:40px;background:#d74}</style>"
      "<div id='box' data-godot-action='empty-resource'>OK</div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_empty_resource_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_empty_resource_smoke: advance failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const size_t hit_count =
      blink_standalone_renderer_hit_metadata_count(renderer);
  const bool output_ok =
      status == BLINK_STANDALONE_STATUS_OK && output.pixels &&
      output.width == 180 && output.height == 100 && output.pixel_count > 0;
  const FramePixelContentStats pixel_stats =
      AnalyzeFramePixelContent(output);
  if (!output_ok || hit_count == 0 || pixel_stats.dark_blue_112233 < 5000 ||
      pixel_stats.orange_dd7744 < 3000) {
    std::fprintf(stderr,
                 "c_api_empty_resource_smoke: output/metadata invalid "
                 "status=%d size=%dx%d bytes=%zu hits=%zu format=%d "
                 "nontransparent=%zu colored=%zu bg112233=%zu "
                 "orange_dd7744=%zu opaque_white=%zu sample=%u,%u,%u,%u\n",
                 status, output.width, output.height, output.pixel_count,
                 hit_count, output.pixel_format, pixel_stats.nontransparent,
                 pixel_stats.nonwhite_colored, pixel_stats.dark_blue_112233,
                 pixel_stats.orange_dd7744, pixel_stats.opaque_white,
                 output.pixel_count >= 4 ? output.pixels[0] : 0,
                 output.pixel_count >= 4 ? output.pixels[1] : 0,
                 output.pixel_count >= 4 ? output.pixels[2] : 0,
                 output.pixel_count >= 4 ? output.pixels[3] : 0);
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  std::printf(
      "c_api_empty_resource_smoke: ok raw=%dx%d stride=%d bytes=%zu hits=%zu "
      "colored=%zu bg112233=%zu orange_dd7744=%zu\n",
      output.width, output.height, output.stride, output.pixel_count,
      hit_count, pixel_stats.nonwhite_colored, pixel_stats.dark_blue_112233,
      pixel_stats.orange_dd7744);
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  return 0;
}

int RunCApiTransparentBackgroundSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 180;
  config.height = 100;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_transparent_background_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style>html,body{margin:0;background:transparent}"
      "#panel{width:100px;height:40px;background:#d06329}</style>"
      "<div id='panel' data-godot-action='panel'></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_transparent_background_smoke: set html failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_transparent_background_smoke: advance failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats pixel_stats =
      AnalyzeFramePixelContent(output);
  const bool output_ok =
      status == BLINK_STANDALONE_STATUS_OK && output.pixels &&
      output.width == 180 && output.height == 100 && output.pixel_count > 0;
  if (!output_ok || pixel_stats.transparent < 8000 ||
      pixel_stats.orange_d06329 < 3000) {
    std::fprintf(stderr,
                 "c_api_transparent_background_smoke: output invalid "
                 "status=%d size=%dx%d bytes=%zu format=%d transparent=%zu "
                 "opaque_white=%zu colored=%zu orange_d06329=%zu "
                 "sample=%u,%u,%u,%u error=%s\n",
                 status, output.width, output.height, output.pixel_count,
                 output.pixel_format, pixel_stats.transparent,
                 pixel_stats.opaque_white, pixel_stats.nonwhite_colored,
                 pixel_stats.orange_d06329,
                 output.pixel_count >= 4 ? output.pixels[0] : 0,
                 output.pixel_count >= 4 ? output.pixels[1] : 0,
                 output.pixel_count >= 4 ? output.pixels[2] : 0,
                 output.pixel_count >= 4 ? output.pixels[3] : 0,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  std::printf(
      "c_api_transparent_background_smoke: ok raw=%dx%d transparent=%zu "
      "opaque_white=%zu colored=%zu orange_d06329=%zu\n",
      output.width, output.height, pixel_stats.transparent,
      pixel_stats.opaque_white, pixel_stats.nonwhite_colored,
      pixel_stats.orange_d06329);
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  return 0;
}

int RunCApiTwoInstanceSmoke() {
  blink_standalone_renderer_config_t config_a = {};
  config_a.width = 256;
  config_a.height = 128;
  config_a.device_scale_factor = 1.0f;
  config_a.no_script_profile = 1;
  blink_standalone_renderer_config_t config_b = {};
  config_b.width = 180;
  config_b.height = 100;
  config_b.device_scale_factor = 1.0f;
  config_b.no_script_profile = 1;

  blink_standalone_renderer_t* renderer_a = nullptr;
  blink_standalone_renderer_t* renderer_b = nullptr;
  blink_standalone_status_code_t status = blink_standalone_renderer_create(&config_a, &renderer_a);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer_a) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: create A failed status=%d\n",
                 status);
    return 1;
  }
  status = blink_standalone_renderer_create(&config_b, &renderer_b);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer_b) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: create B failed status=%d\n",
                 status);
    blink_standalone_renderer_destroy(renderer_a);
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
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  const char* html_a =
      "<!doctype html><style>body{margin:0;background:#112233}.a{width:64px;"
      "height:64px;background-image:url(icon.bmp);background-size:64px 64px}"
      "label{display:block;margin-top:4px;color:white}</style><div id='alpha' "
      "class='a' data-godot-action='alpha'>Alpha</div><label><input "
      "id='check_a' type='checkbox' data-godot-action='check-a'>A</label>";
  const char* html_b =
      "<!doctype html><style>html,body{margin:0;background:transparent}.panel{"
      "width:100px;height:40px;background:#d06329}.b{width:48px;height:48px;"
      "background-image:url(icon.bmp);background-size:48px 48px}label{display:"
      "block;margin-top:4px;color:#102030}</style><div id='panel_b' "
      "class='panel'></div><div id='beta' class='b' data-godot-action='beta'>"
      "Beta</div><label><input id='check_b' type='checkbox' "
      "data-godot-action='check-b'>B</label>";

  const std::string root_a_string = root_a.string();
  const std::string root_b_string = root_b.string();
  status = blink_standalone_renderer_set_document_html(
      renderer_a, html_a, root_a_string.c_str(), root_a_string.c_str());
  if (status == BLINK_STANDALONE_STATUS_OK) {
    status = blink_standalone_renderer_set_document_html(
        renderer_b, html_b, root_b_string.c_str(), root_b_string.c_str());
  }
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: set html failed status=%d A=%s B=%s\n",
                 status, blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  struct CapturedFrame {
    blink_standalone_frame_output_t output = {};
    uint64_t hash = 0;
    FramePixelContentStats pixel_stats;
  };
  const auto capture_frame = [](blink_standalone_renderer_t* renderer,
                                const char* label,
                                int expected_width,
                                int expected_height,
                                CapturedFrame* captured) -> bool {
    const blink_standalone_status_code_t output_status =
        blink_standalone_renderer_get_latest_output(renderer,
                                                    &captured->output);
    captured->hash = HashFramePixels(captured->output);
    captured->pixel_stats = AnalyzeFramePixelContent(captured->output);
    const bool ok =
        output_status == BLINK_STANDALONE_STATUS_OK &&
        captured->output.width == expected_width &&
        captured->output.height == expected_height &&
        captured->output.stride >= expected_width * 4 &&
        captured->output.pixel_count >=
            static_cast<size_t>(expected_width * expected_height * 4) &&
        captured->hash != 0 && FrameHasNonUniformPixels(captured->output);
    if (!ok) {
      std::fprintf(stderr,
                   "c_api_two_instance_smoke: %s output invalid status=%d "
                   "size=%dx%d stride=%d bytes=%zu hash=%llu hits=%zu "
                   "error=%s\n",
                   label, output_status, captured->output.width,
                   captured->output.height, captured->output.stride,
                   captured->output.pixel_count,
                   static_cast<unsigned long long>(captured->hash),
                   blink_standalone_renderer_hit_metadata_count(renderer),
                   blink_standalone_renderer_last_error(renderer));
    }
    blink_standalone_renderer_release_latest_output(renderer);
    return ok;
  };

  status = blink_standalone_renderer_advance_frame(renderer_a, 0.0);
  CapturedFrame first_a;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_frame(renderer_a, "A first", 256, 128, &first_a) ||
      !HasHitId(renderer_a, "alpha") || HasHitId(renderer_a, "beta") ||
      !HitCheckedStateIs(renderer_a, "check_a", false) ||
      first_a.pixel_stats.transparent != 0 ||
      first_a.pixel_stats.dark_blue_112233 < 4000 ||
      first_a.pixel_stats.resource_red_e84444 < 2500 ||
      first_a.pixel_stats.resource_green_237a57 != 0) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: A first advance failed status=%d "
                 "transparent=%zu bg112233=%zu red=%zu green=%zu Aerr=%s\n",
                 status, first_a.pixel_stats.transparent,
                 first_a.pixel_stats.dark_blue_112233,
                 first_a.pixel_stats.resource_red_e84444,
                 first_a.pixel_stats.resource_green_237a57,
                 blink_standalone_renderer_last_error(renderer_a));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  status = blink_standalone_renderer_advance_frame(renderer_b, 0.0);
  CapturedFrame first_b;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_frame(renderer_b, "B first", 180, 100, &first_b) ||
      !HasHitId(renderer_b, "beta") || HasHitId(renderer_b, "alpha") ||
      !HitCheckedStateIs(renderer_b, "check_b", false) ||
      first_b.hash == first_a.hash || first_b.pixel_stats.transparent < 5000 ||
      first_b.pixel_stats.orange_d06329 < 3000 ||
      first_b.pixel_stats.resource_green_237a57 < 1500 ||
      first_b.pixel_stats.resource_red_e84444 != 0) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: B first advance failed status=%d "
                 "A_hash=%llu B_hash=%llu transparent=%zu orange=%zu "
                 "red=%zu green=%zu Aerr=%s Berr=%s\n",
                 status, static_cast<unsigned long long>(first_a.hash),
                 static_cast<unsigned long long>(first_b.hash),
                 first_b.pixel_stats.transparent,
                 first_b.pixel_stats.orange_d06329,
                 first_b.pixel_stats.resource_red_e84444,
                 first_b.pixel_stats.resource_green_237a57,
                 blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  blink_standalone_hit_metadata_t check_a = {};
  if (!GetHitById(renderer_a, "check_a", &check_a)) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: A checkbox metadata missing\n");
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }
  const float check_a_x = check_a.bounds.x + check_a.bounds.width * 0.5f;
  const float check_a_y = check_a.bounds.y + check_a.bounds.height * 0.5f;
  blink_standalone_renderer_mouse_move(renderer_a, check_a_x, check_a_y, 0);
  blink_standalone_renderer_mouse_down(renderer_a, check_a_x, check_a_y,
                                       BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0,
                                       1);
  blink_standalone_renderer_mouse_up(renderer_a, check_a_x, check_a_y,
                                     BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  status = blink_standalone_renderer_advance_frame(renderer_a, 0.008);
  CapturedFrame checked_a;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_frame(renderer_a, "A checked", 256, 128, &checked_a) ||
      !HitCheckedStateIs(renderer_a, "check_a", true) ||
      !HitCheckedStateIs(renderer_b, "check_b", false) ||
      checked_a.hash == first_a.hash) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: A checkbox isolation failed "
                 "status=%d first_hash=%llu checked_hash=%llu Aerr=%s Berr=%s\n",
                 status, static_cast<unsigned long long>(first_a.hash),
                 static_cast<unsigned long long>(checked_a.hash),
                 blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  const char* html_a_reload =
      "<!doctype html><!--reload--><style>body{margin:0;background:#112233}.a{"
      "width:64px;height:64px;background-image:url(icon.bmp);"
      "background-size:64px 64px}label{display:block;margin-top:4px;"
      "color:white}</style><div id='alpha' class='a' "
      "data-godot-action='alpha'>Alpha</div><label><input id='check_a' "
      "type='checkbox' data-godot-action='check-a'>A</label>";
  status = blink_standalone_renderer_set_document_html(
      renderer_a, html_a_reload, root_a_string.c_str(), root_a_string.c_str());
  if (status == BLINK_STANDALONE_STATUS_OK)
    status = blink_standalone_renderer_advance_frame(renderer_a, 0.016);
  CapturedFrame second_a;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_frame(renderer_a, "A second", 256, 128, &second_a) ||
      second_a.hash != first_a.hash || !HasHitId(renderer_a, "alpha") ||
      HasHitId(renderer_a, "beta") ||
      !HitCheckedStateIs(renderer_a, "check_a", false) ||
      !HitCheckedStateIs(renderer_b, "check_b", false)) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: A second advance failed status=%d "
                 "first_hash=%llu second_hash=%llu Aerr=%s Berr=%s\n",
                 status, static_cast<unsigned long long>(first_a.hash),
                 static_cast<unsigned long long>(second_a.hash),
                 blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  const char* html_b_reload =
      "<!doctype html><!--reload--><style>html,body{margin:0;background:transparent}"
      ".c{width:72px;height:54px;background-image:url(icon.bmp);"
      "background-size:72px 54px;color:white}.panel{width:80px;height:32px;"
      "background:#d06329}</style><div id='panel_b_reload' "
      "class='panel'></div><div id='gamma' class='c' "
      "data-godot-action='gamma'>Gamma</div>";
  status = blink_standalone_renderer_set_viewport(renderer_b, 128, 96, 1.0f);
  if (status == BLINK_STANDALONE_STATUS_OK) {
    status = blink_standalone_renderer_set_document_html(
        renderer_b, html_b_reload, root_b_string.c_str(),
        root_b_string.c_str());
  }
  if (status == BLINK_STANDALONE_STATUS_OK)
    status = blink_standalone_renderer_advance_frame(renderer_b, 0.032);
  CapturedFrame second_b;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_frame(renderer_b, "B second", 128, 96, &second_b) ||
      second_b.hash == first_b.hash || second_b.hash == second_a.hash ||
      !HasHitId(renderer_b, "gamma") || HasHitId(renderer_b, "alpha") ||
      HasHitId(renderer_b, "beta") || !HasHitId(renderer_a, "alpha") ||
      HasHitId(renderer_a, "gamma") ||
      second_b.pixel_stats.transparent < 3000 ||
      second_b.pixel_stats.orange_d06329 < 2000 ||
      second_b.pixel_stats.resource_green_237a57 < 2500 ||
      second_b.pixel_stats.resource_red_e84444 != 0) {
    std::fprintf(
        stderr,
        "c_api_two_instance_smoke: B second advance failed status=%d "
        "A=%dx%d hash=%llu hits=%zu B=%dx%d hash=%llu first_b=%llu hits=%zu "
        "Aerr=%s Berr=%s\n",
        status, second_a.output.width, second_a.output.height,
        static_cast<unsigned long long>(second_a.hash),
        blink_standalone_renderer_hit_metadata_count(renderer_a),
        second_b.output.width, second_b.output.height,
        static_cast<unsigned long long>(second_b.hash),
        static_cast<unsigned long long>(first_b.hash),
        blink_standalone_renderer_hit_metadata_count(renderer_b),
        blink_standalone_renderer_last_error(renderer_a),
        blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  status = blink_standalone_renderer_advance_frame(renderer_a, 0.048);
  CapturedFrame final_a;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_frame(renderer_a, "A final", 256, 128, &final_a) ||
      final_a.hash != second_a.hash || !HasHitId(renderer_a, "alpha") ||
      HasHitId(renderer_a, "gamma") ||
      !HitCheckedStateIs(renderer_a, "check_a", false)) {
    std::fprintf(stderr,
                 "c_api_two_instance_smoke: A final isolation failed "
                 "status=%d second_hash=%llu final_hash=%llu Aerr=%s Berr=%s\n",
                 status, static_cast<unsigned long long>(second_a.hash),
                 static_cast<unsigned long long>(final_a.hash),
                 blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  std::printf(
      "c_api_two_instance_smoke: ok A=%dx%d hash=%llu hits=%zu B=%dx%d "
      "hash=%llu hits=%zu B_reloaded=%dx%d hash=%llu transparent=%zu "
      "A_final=%dx%d hash=%llu\n",
      final_a.output.width, final_a.output.height,
      static_cast<unsigned long long>(final_a.hash),
      blink_standalone_renderer_hit_metadata_count(renderer_a),
      first_b.output.width, first_b.output.height,
      static_cast<unsigned long long>(first_b.hash),
      blink_standalone_renderer_hit_metadata_count(renderer_b),
      second_b.output.width, second_b.output.height,
      static_cast<unsigned long long>(second_b.hash),
      second_b.pixel_stats.transparent, final_a.output.width,
      final_a.output.height, static_cast<unsigned long long>(final_a.hash));
  blink_standalone_renderer_destroy(renderer_b);
  blink_standalone_renderer_destroy(renderer_a);
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
  file << indent << "  \"bridge_cc_frame_sink_warmup_ms\": "
       << timing.bridge_cc_frame_sink_warmup_ms << ",\n";
  file << indent << "  \"bridge_cc_root_preattach_ms\": "
       << timing.bridge_cc_root_preattach_ms << ",\n";
  file << indent << "  \"bridge_cc_pending_update_ms\": "
       << timing.bridge_cc_pending_update_ms << ",\n";
  file << indent << "  \"bridge_cc_scheduler_run_loop_ms\": "
       << timing.bridge_cc_scheduler_run_loop_ms << ",\n";
  file << indent << "  \"bridge_cc_submit_wait_ms\": "
       << timing.bridge_cc_submit_wait_ms << ",\n";
  file << indent << "  \"bridge_cc_startup_prewarm_ms\": "
       << timing.bridge_cc_startup_prewarm_ms << ",\n";
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
    if (arg == "--c-api-smoke" ||
        arg == "--c-api-viewport-resize-smoke" ||
        arg == "--c-api-empty-resource-smoke" ||
        arg == "--c-api-transparent-background-smoke" ||
        arg == "--c-api-separated-click-smoke" ||
        arg == "--c-api-dom-mutation-smoke" ||
        arg == "--c-api-fragment-mutation-smoke" ||
        arg == "--c-api-body-mutation-smoke" ||
        arg == "--c-api-text-input-smoke" ||
        arg == "--c-api-form-control-mutation-smoke" ||
        arg == "--c-api-absolute-form-mutation-smoke" ||
        arg == "--c-api-two-instance-smoke" ||
        arg == "--typeface-isolation-smoke") {
      c_api_smoke_requested = true;
      break;
    }
  }
  if (!c_api_smoke_requested)
    ApplyStandaloneGpuDefaults();
  base::AtExitManager at_exit_manager;
  html_css_renderer::InitializeStandaloneIcu();
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
  bool c_api_viewport_resize_smoke = false;
  bool c_api_empty_resource_smoke = false;
  bool c_api_transparent_background_smoke = false;
  bool c_api_separated_click_smoke = false;
  bool c_api_dom_mutation_smoke = false;
  bool c_api_fragment_mutation_smoke = false;
  bool c_api_body_mutation_smoke = false;
  bool c_api_text_input_smoke = false;
  bool c_api_form_control_mutation_smoke = false;
  bool c_api_absolute_form_mutation_smoke = false;
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
    } else if (arg == "--c-api-viewport-resize-smoke") {
      c_api_viewport_resize_smoke = true;
    } else if (arg == "--c-api-empty-resource-smoke") {
      c_api_empty_resource_smoke = true;
    } else if (arg == "--c-api-transparent-background-smoke") {
      c_api_transparent_background_smoke = true;
    } else if (arg == "--c-api-separated-click-smoke") {
      c_api_separated_click_smoke = true;
    } else if (arg == "--c-api-dom-mutation-smoke") {
      c_api_dom_mutation_smoke = true;
    } else if (arg == "--c-api-fragment-mutation-smoke") {
      c_api_fragment_mutation_smoke = true;
    } else if (arg == "--c-api-body-mutation-smoke") {
      c_api_body_mutation_smoke = true;
    } else if (arg == "--c-api-text-input-smoke") {
      c_api_text_input_smoke = true;
    } else if (arg == "--c-api-form-control-mutation-smoke") {
      c_api_form_control_mutation_smoke = true;
    } else if (arg == "--c-api-absolute-form-mutation-smoke") {
      c_api_absolute_form_mutation_smoke = true;
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

  if (c_api_viewport_resize_smoke) {
    return RunCApiViewportResizeSmoke();
  }

  if (c_api_empty_resource_smoke) {
    return RunCApiEmptyResourceSmoke();
  }

  if (c_api_transparent_background_smoke) {
    return RunCApiTransparentBackgroundSmoke();
  }

  if (c_api_separated_click_smoke) {
    return RunCApiSeparatedClickSmoke();
  }

  if (c_api_dom_mutation_smoke) {
    return RunCApiDomMutationSmoke();
  }

  if (c_api_fragment_mutation_smoke) {
    return RunCApiFragmentMutationSmoke();
  }

  if (c_api_body_mutation_smoke) {
    return RunCApiBodyMutationSmoke();
  }

  if (c_api_text_input_smoke) {
    return RunCApiTextInputSmoke();
  }

  if (c_api_form_control_mutation_smoke) {
    return RunCApiFormControlMutationSmoke();
  }

  if (c_api_absolute_form_mutation_smoke) {
    return RunCApiAbsoluteFormMutationSmoke();
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
