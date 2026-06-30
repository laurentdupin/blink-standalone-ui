#include <chrono>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <limits>
#include <sstream>
#include <string>
#include <thread>
#include <algorithm>
#include <cerrno>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "base/at_exit.h"
#include "base/base64.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/functional/callback_helpers.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop/message_pump_type.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/trace_event/trace_event_impl.h"
#include "build/build_config.h"
#include "components/viz/common/gpu/vulkan_in_process_context_provider.h"
#include "gpu/command_buffer/service/service_utils.h"
#include "gpu/command_buffer/service/shared_context_state.h"
#include "gpu/config/gpu_driver_bug_workarounds.h"
#include "gpu/config/gpu_feature_info.h"
#include "gpu/config/gpu_preferences.h"
#include "gpu/command_buffer/service/gpu_switches.h"
#include "gpu/vulkan/init/vulkan_factory.h"
#include "gpu/vulkan/vulkan_command_buffer.h"
#include "gpu/vulkan/vulkan_command_pool.h"
#include "gpu/vulkan/vulkan_device_queue.h"
#include "gpu/vulkan/vulkan_function_pointers.h"
#include "gpu/vulkan/vulkan_image.h"
#include "gpu/vulkan/vulkan_implementation.h"
#include "html_css_renderer/compositor_runtime.h"
#include "html_css_renderer/css_file_loader.h"
#include "html_css_renderer/renderer_c_api.h"
#include "html_css_renderer/standalone_process.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "html_css_renderer/typeface_resource_registry.h"
#include "skia/buildflags.h"
#include "third_party/skia/include/core/SkTypeface.h"
#include "third_party/skia/include/gpu/ganesh/GrDirectContext.h"
#include "third_party/perfetto/include/perfetto/tracing/tracing.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gl/gl_context.h"
#include "ui/gl/buildflags.h"
#include "ui/gl/gl_share_group.h"
#include "ui/gl/gl_surface.h"
#include "ui/gl/gl_utils.h"
#include "ui/gl/init/gl_factory.h"
#include "ui/gl/gl_switches.h"

#if BUILDFLAG(IS_WIN)
#include <d3d12.h>
#include <wrl/client.h>
#endif

#if defined(BLINK_STANDALONE_HAVE_DAWN_D3D12)
#include "dawn/dawn_proc.h"
#include "dawn/native/DawnNative.h"
#include "webgpu/webgpu_cpp.h"
#endif

extern "C" const char*
StandaloneBlinkLiveFrameBridgeRunCcSchedulerProbeForStandaloneRenderer(
    int width,
    int height);

namespace blink::standalone_renderer_probe {
void StandaloneBlinkLiveFrameBridgeInstallExternalVulkanForTesting(
    void* vulkan_implementation,
    void* vulkan_device_queue);
}

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
      "[--gpu-output-smoke] "
      "[--gpu-output-vulkan-smoke] "
      "[--gpu-output-vulkan-pixel-smoke] "
      "[--gpu-output-d3d12-pixel-smoke] "
      "[--gpu-output-d3d12-render-pixel-smoke] "
      "[--gpu-vulkan-ganesh-context-smoke] "
      "[--gpu-borrowed-vkimage-backing-smoke] "
      "[--gpu-borrowed-vkimage-render-copy-smoke] "
      "[--gpu-external-vulkan-runtime-target-smoke] "
      "[--gpu-borrowed-d3d12-render-copy-smoke] "
      "[--c-api-vulkan-external-target-smoke] "
      "[--c-api-vulkan-external-target-large-smoke] "
      "[--c-api-vulkan-external-target-resize-smoke] "
      "[--c-api-vulkan-external-target-rapid-resize-smoke] "
      "[--c-api-vulkan-external-target-pending-resize-smoke] "
      "[--c-api-vulkan-external-target-fps-timing-smoke] "
      "[--c-api-vulkan-external-target-click-timing-smoke] "
      "[--c-api-vulkan-external-target-click-resize-pending-smoke] "
      "[--c-api-vulkan-external-target-full-viewport-button-hit-metadata-smoke] "
      "[--c-api-vulkan-invalid-target-metadata-smoke] "
      "[--c-api-d3d12-external-target-smoke] "
      "[--c-api-d3d12-external-target-resize-smoke] "
      "[--c-api-d3d12-external-target-click-timing-smoke] "
      "[--c-api-d3d12-external-target-click-resize-smoke] "
      "[--c-api-d3d12-external-target-button-activation-smoke] "
      "[--c-api-d3d12-external-target-full-viewport-button-hit-metadata-smoke] "
      "[--c-api-d3d12-external-target-repeated-frame-smoke] "
      "[--c-api-vulkan-update-output-smoke] "
      "[--c-api-d3d12-update-output-smoke] "
      "[--c-api-vulkan-external-target-current-document-smoke] "
      "[--c-api-d3d12-external-target-current-document-smoke] "
      "[--c-api-d3d12-external-target-filter-backdrop-smoke] "
      "[--c-api-d3d12-external-target-transparent-filter-backdrop-smoke] "
      "[--c-api-smoke] [--c-api-viewport-resize-smoke] "
      "[--c-api-resource-provider-smoke] "
      "[--c-api-resource-provider-data-url-smoke] "
      "[--c-api-resource-provider-font-smoke] "
      "[--c-api-resource-provider-mask-svg-smoke] "
      "[--c-api-resource-provider-free-then-mask-smoke] "
      "[--c-api-empty-resource-smoke] "
      "[--c-api-full-viewport-button-hit-metadata-smoke] "
      "[--c-api-transparent-background-smoke] "
      "[--c-api-css-filter-blur-smoke] "
      "[--c-api-backdrop-filter-region-smoke] "
      "[--c-api-backdrop-filter-rounded-smoke] "
      "[--c-api-backdrop-filter-chain-smoke] "
      "[--c-api-backdrop-filter-unsupported-smoke] "
      "[--c-api-separated-click-smoke] "
      "[--c-api-frame-scheduling-smoke] "
      "[--c-api-text-input-smoke] "
      "[--c-api-form-control-mutation-smoke] "
      "[--c-api-absolute-form-mutation-smoke] "
      "[--c-api-slider-form-state-smoke] "
      "[--c-api-select-form-state-smoke] "
      "[--c-api-multiselect-form-state-smoke] "
      "[--c-api-fragment-mutation-smoke] "
      "[--c-api-structural-dom-mutation-smoke] "
      "[--c-api-mutation-diagnostics-smoke] "
      "[--c-api-mutation-stress-smoke] "
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

bool FindVulkanMemoryTypeForSmoke(VkPhysicalDevice physical_device,
                                  uint32_t memory_type_bits,
                                  VkMemoryPropertyFlags required_flags,
                                  uint32_t* memory_type_index) {
  if (!memory_type_index) {
    return false;
  }
  VkPhysicalDeviceMemoryProperties properties = {};
  vkGetPhysicalDeviceMemoryProperties(physical_device, &properties);
  for (uint32_t i = 0; i < properties.memoryTypeCount; ++i) {
    if (((1u << i) & memory_type_bits) == 0) {
      continue;
    }
    if ((properties.memoryTypes[i].propertyFlags & required_flags) ==
        required_flags) {
      *memory_type_index = i;
      return true;
    }
  }
  return false;
}

bool ReadbackVulkanImageForSmoke(gpu::VulkanDeviceQueue* queue,
                                 gpu::VulkanImage* image,
                                 uint32_t width,
                                 uint32_t height,
                                 std::vector<uint32_t>* pixels,
                                 std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    return false;
  };
  if (!queue || !image || image->image() == VK_NULL_HANDLE || !pixels ||
      width == 0 || height == 0) {
    return fail("invalid Vulkan readback arguments");
  }

  const VkDevice device = queue->GetVulkanDevice();
  const VkDeviceSize byte_count =
      static_cast<VkDeviceSize>(width) * height * sizeof(uint32_t);
  VkBuffer buffer = VK_NULL_HANDLE;
  VkDeviceMemory memory = VK_NULL_HANDLE;
  auto cleanup = [&] {
    if (memory != VK_NULL_HANDLE) {
      vkFreeMemory(device, memory, nullptr);
      memory = VK_NULL_HANDLE;
    }
    if (buffer != VK_NULL_HANDLE) {
      vkDestroyBuffer(device, buffer, nullptr);
      buffer = VK_NULL_HANDLE;
    }
  };

  VkBufferCreateInfo buffer_info = {};
  buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  buffer_info.size = byte_count;
  buffer_info.usage = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
  buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
  if (vkCreateBuffer(device, &buffer_info, nullptr, &buffer) != VK_SUCCESS) {
    return fail("Vulkan readback buffer creation failed");
  }

  VkMemoryRequirements requirements = {};
  vkGetBufferMemoryRequirements(device, buffer, &requirements);
  uint32_t memory_type_index = 0;
  if (!FindVulkanMemoryTypeForSmoke(
          queue->GetVulkanPhysicalDevice(), requirements.memoryTypeBits,
          VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT |
              VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
          &memory_type_index)) {
    cleanup();
    return fail("Vulkan readback host-visible memory type not found");
  }
  VkMemoryAllocateInfo allocate_info = {};
  allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocate_info.allocationSize = requirements.size;
  allocate_info.memoryTypeIndex = memory_type_index;
  if (vkAllocateMemory(device, &allocate_info, nullptr, &memory) !=
      VK_SUCCESS) {
    cleanup();
    return fail("Vulkan readback memory allocation failed");
  }
  if (vkBindBufferMemory(device, buffer, memory, 0) != VK_SUCCESS) {
    cleanup();
    return fail("Vulkan readback buffer bind failed");
  }

  auto command_pool = queue->CreateCommandPool();
  if (!command_pool) {
    cleanup();
    return fail("Vulkan readback command pool creation failed");
  }
  auto command_buffer = command_pool->CreatePrimaryCommandBuffer();
  if (!command_buffer) {
    command_pool->Destroy();
    cleanup();
    return fail("Vulkan readback command buffer creation failed");
  }
  {
    gpu::ScopedSingleUseCommandBufferRecorder recorder(*command_buffer);
    command_buffer->TransitionImageLayout(
        image->image(), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
        VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
    command_buffer->CopyImageToBuffer(buffer, image->image(), width, height,
                                      width, height);
    command_buffer->TransitionImageLayout(
        image->image(), VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
        VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
  }
  if (!command_buffer->Submit(/*num_wait_semaphores=*/0,
                              /*wait_semaphores=*/nullptr,
                              /*num_signal_semaphores=*/0,
                              /*signal_semaphores=*/nullptr)) {
    command_buffer->Destroy();
    command_pool->Destroy();
    cleanup();
    return fail("Vulkan readback command submit failed");
  }
  command_buffer->Wait(UINT64_MAX);
  command_buffer->Destroy();
  command_buffer.reset();
  command_pool->Destroy();

  void* mapped = nullptr;
  if (vkMapMemory(device, memory, 0, byte_count, 0, &mapped) != VK_SUCCESS ||
      !mapped) {
    cleanup();
    return fail("Vulkan readback memory map failed");
  }
  pixels->resize(static_cast<size_t>(width) * height);
  std::memcpy(pixels->data(), mapped, static_cast<size_t>(byte_count));
  vkUnmapMemory(device, memory);
  cleanup();
  return true;
}

#if BUILDFLAG(IS_WIN)
bool ReadbackD3D12TextureForSmoke(ID3D12Device* device,
                                  ID3D12CommandQueue* queue,
                                  ID3D12Resource* texture,
                                  uint32_t width,
                                  uint32_t height,
                                  std::vector<uint32_t>* pixels,
                                  std::string* failure) {
  auto fail = [&](const char* message) {
    if (failure) {
      *failure = message;
    }
    return false;
  };
  if (!device || !queue || !texture || !pixels || width == 0 || height == 0) {
    return fail("invalid D3D12 readback arguments");
  }

  D3D12_RESOURCE_DESC texture_desc = texture->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT footprint = {};
  UINT row_count = 0;
  UINT64 row_size_bytes = 0;
  UINT64 total_bytes = 0;
  device->GetCopyableFootprints(&texture_desc, 0, 1, 0, &footprint,
                                &row_count, &row_size_bytes, &total_bytes);
  if (row_count == 0 || row_size_bytes == 0 || total_bytes == 0) {
    return fail("D3D12 readback footprint is empty");
  }

  D3D12_HEAP_PROPERTIES readback_heap = {};
  readback_heap.Type = D3D12_HEAP_TYPE_READBACK;
  readback_heap.CreationNodeMask = 1;
  readback_heap.VisibleNodeMask = 1;
  D3D12_RESOURCE_DESC buffer_desc = {};
  buffer_desc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
  buffer_desc.Width = total_bytes;
  buffer_desc.Height = 1;
  buffer_desc.DepthOrArraySize = 1;
  buffer_desc.MipLevels = 1;
  buffer_desc.SampleDesc.Count = 1;
  buffer_desc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  Microsoft::WRL::ComPtr<ID3D12Resource> readback;
  if (FAILED(device->CreateCommittedResource(
          &readback_heap, D3D12_HEAP_FLAG_NONE, &buffer_desc,
          D3D12_RESOURCE_STATE_COPY_DEST, nullptr, IID_PPV_ARGS(&readback))) ||
      !readback) {
    return fail("D3D12 readback buffer creation failed");
  }

  Microsoft::WRL::ComPtr<ID3D12CommandAllocator> allocator;
  if (FAILED(device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT,
                                            IID_PPV_ARGS(&allocator))) ||
      !allocator) {
    return fail("D3D12 readback command allocator creation failed");
  }
  Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list;
  if (FAILED(device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT,
                                       allocator.Get(), nullptr,
                                       IID_PPV_ARGS(&command_list))) ||
      !command_list) {
    return fail("D3D12 readback command list creation failed");
  }

  D3D12_TEXTURE_COPY_LOCATION src = {};
  src.pResource = texture;
  src.Type = D3D12_TEXTURE_COPY_TYPE_SUBRESOURCE_INDEX;
  src.SubresourceIndex = 0;
  D3D12_TEXTURE_COPY_LOCATION dst = {};
  dst.pResource = readback.Get();
  dst.Type = D3D12_TEXTURE_COPY_TYPE_PLACED_FOOTPRINT;
  dst.PlacedFootprint = footprint;
  command_list->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);
  if (FAILED(command_list->Close())) {
    return fail("D3D12 readback command list close failed");
  }
  ID3D12CommandList* command_lists[] = {command_list.Get()};
  queue->ExecuteCommandLists(1, command_lists);

  Microsoft::WRL::ComPtr<ID3D12Fence> fence;
  if (FAILED(device->CreateFence(0, D3D12_FENCE_FLAG_NONE,
                                 IID_PPV_ARGS(&fence))) ||
      !fence) {
    return fail("D3D12 readback fence creation failed");
  }
  HANDLE event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
  if (!event_handle) {
    return fail("D3D12 readback event creation failed");
  }
  constexpr UINT64 kFenceValue = 1;
  if (FAILED(queue->Signal(fence.Get(), kFenceValue))) {
    ::CloseHandle(event_handle);
    return fail("D3D12 readback fence signal failed");
  }
  if (fence->GetCompletedValue() < kFenceValue) {
    if (FAILED(fence->SetEventOnCompletion(kFenceValue, event_handle))) {
      ::CloseHandle(event_handle);
      return fail("D3D12 readback fence wait setup failed");
    }
    ::WaitForSingleObject(event_handle, 5000);
  }
  ::CloseHandle(event_handle);
  if (fence->GetCompletedValue() < kFenceValue) {
    return fail("D3D12 readback fence wait timed out");
  }

  void* mapped = nullptr;
  D3D12_RANGE read_range = {0, static_cast<SIZE_T>(total_bytes)};
  if (FAILED(readback->Map(0, &read_range, &mapped)) || !mapped) {
    return fail("D3D12 readback map failed");
  }
  const uint8_t* mapped_bytes = static_cast<const uint8_t*>(mapped);
  pixels->assign(static_cast<size_t>(width) * static_cast<size_t>(height), 0);
  for (uint32_t y = 0; y < height; ++y) {
    const uint8_t* row =
        mapped_bytes + footprint.Offset +
        static_cast<size_t>(y) * footprint.Footprint.RowPitch;
    for (uint32_t x = 0; x < width; ++x) {
      const uint8_t* p = row + static_cast<size_t>(x) * 4u;
      (*pixels)[static_cast<size_t>(y) * width + x] =
          (static_cast<uint32_t>(p[3]) << 24) |
          (static_cast<uint32_t>(p[0]) << 16) |
          (static_cast<uint32_t>(p[1]) << 8) | static_cast<uint32_t>(p[2]);
    }
  }
  D3D12_RANGE written_range = {0, 0};
  readback->Unmap(0, &written_range);
  return true;
}
#endif

int RunCApiExternalGpuTargetSmoke(uint32_t backend,
                                  const char* label,
                                  bool require_external_target,
                                  uint32_t expected_background = 0xff123456u,
                                  uint32_t expected_box = 0xffd06329u,
                                  const char* background_css = "#123456",
                                  const char* box_css = "#d06329",
                                  uint32_t width = 128,
                                  uint32_t height = 64,
                                  const char* extra_css = "",
                                  const char* extra_body = "",
                                  bool require_full_nontransparent = true,
                                  bool exercise_update_output_sequence = false,
                                  bool expect_invalid_vulkan_metadata = false,
                                  int repeated_update_output_iterations = 0,
                                  bool exercise_resize_sequence = false,
                                  int repeated_click_output_iterations = 0,
                                  bool tolerate_pending_resize_retry = false,
                                  bool use_button_action_document = false,
                                  bool exercise_host_pending_resize_boundary =
                                      false,
                                  int repeated_same_target_render_iterations =
                                      0,
                                  int repeated_after_resize_render_iterations =
                                      0,
                                  bool omit_d3d12_resource_hint_after_resize =
                                      false,
                                  bool rotate_d3d12_shared_handle_after_resize =
                                      false,
                                  bool alias_d3d12_resource_hint_after_resize =
                                      false,
                                  bool invalidate_d3d12_shared_handle_after_resize =
                                      false,
                                  bool expect_invalid_uncached_d3d12_handle_after_resize =
                                      false,
                                  bool full_viewport_button_document = false,
                                  bool exercise_rapid_resize_sequence = false) {
  uint32_t active_width = width;
  uint32_t active_height = height;
  blink_standalone_renderer_config_t config = {};
  config.width = width;
  config.height = height;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr, "%s: create failed status=%d\n", label, status);
    return 1;
  }

  const uint32_t required_capability =
      require_external_target
          ? BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET
          : BLINK_STANDALONE_GPU_CAPABILITY_INTERNAL_TEST_STANDIN;

  std::string html;
  if (full_viewport_button_document) {
    html =
        "<!doctype html><html><head><style>"
        "html,body{margin:0;padding:0;width:100%;height:100%;overflow:hidden;"
        "background:#17212b}"
        "#play{position:fixed;inset:0;width:100vw;height:100vh;margin:0;"
        "padding:0;border:0;background:#237a57;color:white;"
        "font:700 72px Arial,sans-serif}"
        "#play:active{background:#144a80}"
        "</style></head><body>"
        "<button id=\"play\" data-godot-action=\"play\">Play</button>"
        "</body></html>";
  } else {
    const std::string box_element =
        use_button_action_document
            ? "<button id='box' type='button' data-godot-action='play'>Play</button>"
            : "<div id='box'></div>";
    const std::string box_control_css =
        use_button_action_document
            ? "appearance:none;-webkit-appearance:none;border:0;padding:0;"
              "color:white;text-align:center;"
            : "";
    html = std::string("<!doctype html><style>") +
           "html,body{margin:0;width:100%;height:100%;background:" +
           background_css +
           ";}#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
           "background:" +
           box_css + ";" + box_control_css + "}" + extra_css + "</style>" +
           box_element + extra_body;
  }

  blink_standalone_external_gpu_target_t target = {};
  target.common.backend = backend;
  target.common.flags =
      require_external_target ? 0
                              : BLINK_STANDALONE_GPU_TARGET_INTERNAL_TEST_STANDIN;
  target.common.logical_width = width;
  target.common.logical_height = height;
  target.common.physical_width = width;
  target.common.physical_height = height;
  target.common.device_scale_factor = 1.0f;
  target.common.pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  target.common.alpha_mode = BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED;
  target.common.color_space = BLINK_STANDALONE_COLOR_SPACE_SRGB;
  target.common.generation = 1;
#if BUILDFLAG(IS_WIN)
  Microsoft::WRL::ComPtr<ID3D12Device> d3d12_device;
  Microsoft::WRL::ComPtr<ID3D12CommandQueue> d3d12_queue;
  Microsoft::WRL::ComPtr<ID3D12Resource> d3d12_resource;
  Microsoft::WRL::ComPtr<ID3D12Resource1> d3d12_resource_alias;
  HANDLE d3d12_shared_handle = nullptr;
#endif
  std::unique_ptr<gpu::VulkanImplementation> vulkan_implementation;
  std::unique_ptr<gpu::VulkanDeviceQueue> vulkan_owner_queue;
  std::unique_ptr<gpu::VulkanImage> vulkan_target_image;
  std::vector<std::string> vulkan_instance_extension_storage;
  std::vector<std::string> vulkan_device_extension_storage;
  std::vector<const char*> vulkan_instance_extensions;
  std::vector<const char*> vulkan_device_extensions;
  std::function<bool(uint32_t, uint32_t)> create_vulkan_target;
#if BUILDFLAG(IS_WIN)
  std::function<bool(uint32_t, uint32_t)> create_d3d12_target;
#endif
  auto destroy_vulkan_target = [&] {
    if (vulkan_owner_queue) {
      vkDeviceWaitIdle(vulkan_owner_queue->GetVulkanDevice());
    }
    if (vulkan_target_image) {
      vulkan_target_image->Destroy();
      vulkan_target_image.reset();
    }
  };
  auto cleanup_vulkan_target = [&] {
    destroy_vulkan_target();
    if (vulkan_owner_queue) {
      vulkan_owner_queue->Destroy();
      vulkan_owner_queue.reset();
    }
  };
  if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
    vulkan_implementation = gpu::CreateVulkanImplementation(false);
    if (!vulkan_implementation ||
        !vulkan_implementation->InitializeVulkanInstance(true)) {
      std::fprintf(stderr, "%s: blocked vulkan_implementation=0\n", label);
      blink_standalone_renderer_destroy(renderer);
      return 0;
    }
    vulkan_owner_queue = gpu::CreateVulkanDeviceQueue(
        vulkan_implementation.get(),
        gpu::VulkanDeviceQueue::GRAPHICS_QUEUE_FLAG,
        /*gpu_info=*/nullptr,
        /*heap_memory_limit=*/0,
        /*is_thread_safe=*/true);
    if (!vulkan_owner_queue) {
      std::fprintf(stderr, "%s: blocked vulkan_owner_queue=0\n", label);
      blink_standalone_renderer_destroy(renderer);
      return 0;
    }
    const auto& instance_extensions =
        vulkan_implementation->GetVulkanInstance()
            ->vulkan_info()
            .enabled_instance_extensions;
    vulkan_instance_extension_storage.reserve(instance_extensions.size());
    vulkan_instance_extensions.reserve(instance_extensions.size());
    for (const char* extension : instance_extensions) {
      vulkan_instance_extension_storage.emplace_back(extension);
      vulkan_instance_extensions.push_back(
          vulkan_instance_extension_storage.back().c_str());
    }
    vulkan_device_extension_storage.reserve(
        vulkan_owner_queue->enabled_extensions().size());
    vulkan_device_extensions.reserve(
        vulkan_owner_queue->enabled_extensions().size());
    for (std::string_view extension :
         vulkan_owner_queue->enabled_extensions()) {
      vulkan_device_extension_storage.emplace_back(extension);
      vulkan_device_extensions.push_back(
          vulkan_device_extension_storage.back().c_str());
    }
    blink_standalone_vulkan_external_device_t vulkan_device = {};
    vulkan_device.vk_instance = vulkan_owner_queue->GetVulkanInstance();
    vulkan_device.vk_physical_device =
        vulkan_owner_queue->GetVulkanPhysicalDevice();
    vulkan_device.vk_device = vulkan_owner_queue->GetVulkanDevice();
    vulkan_device.vk_queue = vulkan_owner_queue->GetVulkanQueue();
    vulkan_device.queue_family_index =
        vulkan_owner_queue->GetVulkanQueueIndex();
    vulkan_device.api_version =
        vulkan_implementation->GetVulkanInstance()
            ->vulkan_info()
            .used_api_version;
    vulkan_device.enabled_instance_extensions =
        vulkan_instance_extensions.data();
    vulkan_device.enabled_instance_extension_count =
        vulkan_instance_extensions.size();
    vulkan_device.enabled_device_extensions = vulkan_device_extensions.data();
    vulkan_device.enabled_device_extension_count =
        vulkan_device_extensions.size();
    status = blink_standalone_renderer_configure_vulkan_external_device(
        renderer, &vulkan_device);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr, "%s: failed configure_vulkan status=%d error=%s\n",
                   label, status,
                   blink_standalone_renderer_last_error(renderer));
      blink_standalone_renderer_destroy(renderer);
      vulkan_owner_queue->Destroy();
      return 1;
    }
    create_vulkan_target = [&](uint32_t target_width,
                               uint32_t target_height) {
      destroy_vulkan_target();
      vulkan_target_image = gpu::VulkanImage::Create(
          vulkan_owner_queue.get(),
          gfx::Size(static_cast<int>(target_width),
                    static_cast<int>(target_height)),
          VK_FORMAT_R8G8B8A8_UNORM,
          VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
              VK_IMAGE_USAGE_TRANSFER_SRC_BIT |
              VK_IMAGE_USAGE_TRANSFER_DST_BIT);
      if (!vulkan_target_image ||
          vulkan_target_image->image() == VK_NULL_HANDLE) {
        return false;
      }
      target.vulkan.vk_image = vulkan_target_image->image();
      target.vulkan.vk_device = vulkan_owner_queue->GetVulkanDevice();
      target.vulkan.vk_physical_device =
          vulkan_owner_queue->GetVulkanPhysicalDevice();
      target.vulkan.vk_device_memory = vulkan_target_image->device_memory();
      target.vulkan.vk_format = VK_FORMAT_R8G8B8A8_UNORM;
      target.vulkan.width = target_width;
      target.vulkan.height = target_height;
      target.vulkan.current_layout = VK_IMAGE_LAYOUT_UNDEFINED;
      target.vulkan.required_final_layout =
          VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
      target.vulkan.queue_family_index =
          vulkan_owner_queue->GetVulkanQueueIndex();
      target.vulkan.allocation_size = vulkan_target_image->device_size();
      target.vulkan.memory_type_index = vulkan_target_image->memory_type_index();
      target.vulkan.image_tiling = vulkan_target_image->image_tiling();
      target.vulkan.image_usage_flags = vulkan_target_image->usage();
      target.vulkan.sample_count = VK_SAMPLE_COUNT_1_BIT;
      target.vulkan.level_count = 1;
      return true;
    };
    if (!create_vulkan_target(active_width, active_height)) {
      std::fprintf(stderr, "%s: failed vulkan_target_image=0\n", label);
      blink_standalone_renderer_destroy(renderer);
      vulkan_owner_queue->Destroy();
      return 1;
    }
  } else if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
#if BUILDFLAG(IS_WIN)
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0,
                                   IID_PPV_ARGS(&d3d12_device));
    if (FAILED(hr) || !d3d12_device) {
      std::fprintf(stderr, "%s: blocked d3d12_device=0 hr=0x%08lx\n", label,
                   static_cast<unsigned long>(hr));
      blink_standalone_renderer_destroy(renderer);
      return 0;
    }
    D3D12_COMMAND_QUEUE_DESC queue_desc = {};
    queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    hr = d3d12_device->CreateCommandQueue(&queue_desc,
                                          IID_PPV_ARGS(&d3d12_queue));
    if (FAILED(hr) || !d3d12_queue) {
      std::fprintf(stderr, "%s: failed d3d12_queue=0 hr=0x%08lx\n", label,
                   static_cast<unsigned long>(hr));
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }
    create_d3d12_target = [&](uint32_t target_width, uint32_t target_height) {
      if (d3d12_shared_handle) {
        CloseHandle(d3d12_shared_handle);
        d3d12_shared_handle = nullptr;
      }
      d3d12_resource.Reset();
      d3d12_resource_alias.Reset();
      target.d3d12.d3d12_resource = nullptr;
      target.d3d12.shared_handle = nullptr;
      D3D12_HEAP_PROPERTIES heap_properties = {};
      heap_properties.Type = D3D12_HEAP_TYPE_DEFAULT;
      heap_properties.CreationNodeMask = 1;
      heap_properties.VisibleNodeMask = 1;
      D3D12_RESOURCE_DESC resource_desc = {};
      resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
      resource_desc.Width = target_width;
      resource_desc.Height = target_height;
      resource_desc.DepthOrArraySize = 1;
      resource_desc.MipLevels = 1;
      resource_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
      resource_desc.SampleDesc.Count = 1;
      resource_desc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
      resource_desc.Flags = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET |
                            D3D12_RESOURCE_FLAG_ALLOW_SIMULTANEOUS_ACCESS;
      HRESULT create_hr = d3d12_device->CreateCommittedResource(
          &heap_properties, D3D12_HEAP_FLAG_SHARED, &resource_desc,
          D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&d3d12_resource));
      if (FAILED(create_hr) || !d3d12_resource) {
        return false;
      }
      create_hr = d3d12_device->CreateSharedHandle(
          d3d12_resource.Get(), nullptr, GENERIC_ALL, nullptr,
          &d3d12_shared_handle);
      if (FAILED(create_hr) || !d3d12_shared_handle) {
        d3d12_resource.Reset();
        return false;
      }
      target.d3d12.d3d12_device = d3d12_device.Get();
      target.d3d12.d3d12_command_queue = d3d12_queue.Get();
      target.d3d12.d3d12_resource = d3d12_resource.Get();
      target.d3d12.shared_handle = d3d12_shared_handle;
      target.d3d12.dxgi_format = DXGI_FORMAT_R8G8B8A8_UNORM;
      target.d3d12.width = target_width;
      target.d3d12.height = target_height;
      target.d3d12.current_state = D3D12_RESOURCE_STATE_COMMON;
      target.d3d12.required_final_state =
          D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
      return true;
    };
    if (!create_d3d12_target(active_width, active_height)) {
      std::fprintf(stderr, "%s: failed d3d12 target creation\n", label);
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }
    blink_standalone_d3d12_external_device_t d3d12_external_device = {};
    d3d12_external_device.d3d12_device = d3d12_device.Get();
    d3d12_external_device.d3d12_command_queue = d3d12_queue.Get();
    status = blink_standalone_renderer_configure_d3d12_external_device(
        renderer, &d3d12_external_device);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr, "%s: failed configure_d3d12 status=%d error=%s\n",
                   label, status,
                   blink_standalone_renderer_last_error(renderer));
      if (target.d3d12.shared_handle) {
        CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
      }
      blink_standalone_renderer_destroy(renderer);
      return 1;
    }
#else
    std::fprintf(stderr, "%s: blocked platform=non_windows\n", label);
    blink_standalone_renderer_destroy(renderer);
    return 0;
#endif
  }

  status =
      blink_standalone_renderer_set_document_html(renderer, html.c_str(), "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: set document failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
#if BUILDFLAG(IS_WIN)
    if (target.d3d12.shared_handle) {
      CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
    }
#endif
    blink_standalone_renderer_destroy(renderer);
    if (vulkan_target_image) {
      cleanup_vulkan_target();
    }
    return 1;
  }

  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(renderer, backend);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0 ||
      (capabilities & required_capability) == 0) {
    std::fprintf(stderr,
                 "%s: blocked backend unavailable capabilities=%u\n", label,
                 capabilities);
#if BUILDFLAG(IS_WIN)
    if (target.d3d12.shared_handle) {
      CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
    }
#endif
    blink_standalone_renderer_destroy(renderer);
    cleanup_vulkan_target();
    return 0;
  }
  if (expect_invalid_vulkan_metadata) {
    if (backend != BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
      std::fprintf(stderr, "%s: invalid metadata smoke requires Vulkan\n",
                   label);
      blink_standalone_renderer_destroy(renderer);
      cleanup_vulkan_target();
      return 1;
    }
    target.vulkan.allocation_size = 0;
  }

  blink_standalone_gpu_render_result_t result = {};
  status =
      blink_standalone_renderer_render_to_gpu_target(renderer, &target, &result);
  if (!expect_invalid_vulkan_metadata) {
    constexpr int kMaxInitialPendingRetries = 32;
    int initial_pending_retries = 0;
    while (status == BLINK_STANDALONE_STATUS_PENDING &&
           result.target_written == 0 &&
           initial_pending_retries < kMaxInitialPendingRetries) {
      ++initial_pending_retries;
      blink_standalone_update_result_t pending_update = {};
      status = blink_standalone_renderer_update(
          renderer, 0.010 + static_cast<double>(initial_pending_retries) *
                              0.016,
          &pending_update);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        break;
      }
      if (pending_update.needs_output != 0) {
        target.common.generation++;
        target.vulkan.current_layout = target.vulkan.required_final_layout;
#if BUILDFLAG(IS_WIN)
        target.d3d12.current_state = target.d3d12.required_final_state;
#endif
      }
      result = blink_standalone_gpu_render_result_t{};
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      status = blink_standalone_renderer_render_to_gpu_target(renderer, &target,
                                                              &result);
    }
  }
  if (expect_invalid_vulkan_metadata) {
    const char* last_error = blink_standalone_renderer_last_error(renderer);
    const bool error_matches =
        last_error &&
        std::string(last_error).find("missing allocation_size") !=
            std::string::npos;
    if (status != BLINK_STANDALONE_STATUS_INVALID_ARGUMENT ||
        result.target_written != 0 || !error_matches) {
      std::fprintf(stderr,
                   "%s: invalid metadata was not rejected cleanly status=%d "
                   "result_status=%u written=%u error=%s\n",
                   label, status, result.status, result.target_written,
                   last_error ? last_error : "");
      blink_standalone_renderer_destroy(renderer);
      cleanup_vulkan_target();
      return 1;
    }
    std::printf("%s: ok rejected_invalid_metadata=1 error=%s\n", label,
                last_error);
    blink_standalone_renderer_destroy(renderer);
    cleanup_vulkan_target();
    return 0;
  }
  if (status != BLINK_STANDALONE_STATUS_OK || result.target_written == 0 ||
      result.backend != backend || result.width != active_width ||
      result.height != active_height) {
    std::fprintf(stderr,
                 "%s: failed status=%d result_status=%u backend=%u "
                 "written=%u size=%ux%u error=%s\n",
                 label, status, result.status, result.backend,
                 result.target_written, result.width, result.height,
                 blink_standalone_renderer_last_error(renderer));
#if BUILDFLAG(IS_WIN)
    if (target.d3d12.shared_handle) {
      CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
    }
#endif
    blink_standalone_renderer_destroy(renderer);
    cleanup_vulkan_target();
    return 1;
  }

  auto cleanup_and_fail = [&]() {
#if BUILDFLAG(IS_WIN)
    if (target.d3d12.shared_handle) {
      CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
    }
#endif
    blink_standalone_renderer_destroy(renderer);
    cleanup_vulkan_target();
    return 1;
  };

  uint32_t observed_background = 0;
  uint32_t observed_box = 0;
  uint32_t background_pixels = 0;
  uint32_t box_pixels = 0;
  uint32_t nontransparent_pixels = 0;
  int pending_resize_retries = 0;
  int repeated_same_target_renders = 0;
  int post_resize_repeated_renders = 0;
  int invalid_uncached_d3d12_target_checks = 0;
  auto verify_target_pixels = [&](const char* stage,
                                  uint32_t stage_expected_background,
                                  uint32_t stage_expected_box,
                                  bool stage_require_full_nontransparent,
                                  bool quiet) {
    observed_background = 0;
    observed_box = 0;
    background_pixels = 0;
    box_pixels = 0;
    nontransparent_pixels = 0;
#if BUILDFLAG(IS_WIN)
    if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
      std::vector<uint32_t> pixels;
      std::string failure;
      if (!ReadbackD3D12TextureForSmoke(d3d12_device.Get(), d3d12_queue.Get(),
                                        d3d12_resource.Get(), active_width,
                                        active_height, &pixels, &failure)) {
        std::fprintf(stderr,
                     "%s: failed %s external_readback=0 failure=%s\n", label,
                     stage, failure.c_str());
        return false;
      }
      auto pixel_at = [&](uint32_t x, uint32_t y) {
        return pixels[static_cast<size_t>(y) * active_width + x];
      };
      observed_background = pixel_at(4, 4);
      observed_box = pixel_at(20, 20);
      for (uint32_t pixel : pixels) {
        if ((pixel >> 24) != 0) {
          ++nontransparent_pixels;
        }
        if (pixel == stage_expected_background) {
          ++background_pixels;
        }
        if (pixel == stage_expected_box) {
          ++box_pixels;
        }
      }
      if (observed_background != stage_expected_background ||
          observed_box != stage_expected_box || background_pixels == 0 ||
          box_pixels == 0 ||
          (stage_require_full_nontransparent &&
           nontransparent_pixels != active_width * active_height)) {
        if (!quiet) {
          std::fprintf(stderr,
                       "%s: failed %s external_readback=1 "
                       "observed_background=%08x observed_box=%08x "
                       "background_pixels=%u box_pixels=%u "
                       "nontransparent_pixels=%u\n",
                       label, stage, observed_background, observed_box,
                       background_pixels, box_pixels, nontransparent_pixels);
        }
        return false;
      }
      return true;
    }
#endif
    if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
      std::vector<uint32_t> pixels;
      std::string failure;
      if (!ReadbackVulkanImageForSmoke(vulkan_owner_queue.get(),
                                       vulkan_target_image.get(), active_width,
                                       active_height, &pixels, &failure)) {
        std::fprintf(stderr,
                     "%s: failed %s vulkan_external_readback=0 failure=%s\n",
                     label, stage, failure.c_str());
        return false;
      }
      auto pixel_at = [&](uint32_t x, uint32_t y) {
        const uint32_t rgba = pixels[static_cast<size_t>(y) * active_width + x];
        return (rgba & 0xff000000u) | ((rgba & 0x000000ffu) << 16) |
               (rgba & 0x0000ff00u) | ((rgba & 0x00ff0000u) >> 16);
      };
      observed_background = pixel_at(4, 4);
      observed_box = pixel_at(20, 20);
      for (uint32_t rgba : pixels) {
        const uint32_t pixel = (rgba & 0xff000000u) |
                               ((rgba & 0x000000ffu) << 16) |
                               (rgba & 0x0000ff00u) |
                               ((rgba & 0x00ff0000u) >> 16);
        if ((pixel >> 24) != 0) {
          ++nontransparent_pixels;
        }
        if (pixel == stage_expected_background) {
          ++background_pixels;
        }
        if (pixel == stage_expected_box) {
          ++box_pixels;
        }
      }
      if (observed_background != stage_expected_background ||
          observed_box != stage_expected_box || background_pixels == 0 ||
          box_pixels == 0 ||
          (stage_require_full_nontransparent && nontransparent_pixels == 0)) {
        if (!quiet) {
          std::fprintf(stderr,
                       "%s: failed %s vulkan_external_readback=1 "
                       "observed_background=%08x observed_box=%08x "
                       "background_pixels=%u box_pixels=%u "
                       "nontransparent_pixels=%u\n",
                       label, stage, observed_background, observed_box,
                       background_pixels, box_pixels, nontransparent_pixels);
        }
        return false;
      }
      return true;
    }
    std::fprintf(stderr, "%s: failed %s unsupported backend=%u\n", label, stage,
                 backend);
    return false;
  };

  if (!verify_target_pixels("initial", expected_background, expected_box,
                            require_full_nontransparent, /*quiet=*/false)) {
    return cleanup_and_fail();
  }
  if (repeated_same_target_render_iterations > 0) {
    for (int i = 0; i < repeated_same_target_render_iterations; ++i) {
      target.common.generation++;
      target.vulkan.current_layout = target.vulkan.required_final_layout;
#if BUILDFLAG(IS_WIN)
      target.d3d12.current_state = target.d3d12.required_final_state;
#endif
      blink_standalone_gpu_render_result_t repeated_render = {};
      status = blink_standalone_renderer_render_to_gpu_target(
          renderer, &target, &repeated_render);
      if (status != BLINK_STANDALONE_STATUS_OK ||
          repeated_render.target_written == 0 ||
          repeated_render.backend != backend ||
          repeated_render.width != active_width ||
          repeated_render.height != active_height) {
        std::fprintf(stderr,
                     "%s: repeated same-target render %d failed status=%d "
                     "result_status=%u backend=%u written=%u size=%ux%u "
                     "error=%s\n",
                     label, i, status, repeated_render.status,
                     repeated_render.backend, repeated_render.target_written,
                     repeated_render.width, repeated_render.height,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (!verify_target_pixels("repeated-same-target", expected_background,
                                expected_box, require_full_nontransparent,
                                /*quiet=*/false)) {
        return cleanup_and_fail();
      }
      ++repeated_same_target_renders;
    }
  }
  if (use_button_action_document || full_viewport_button_document) {
    blink_standalone_hit_metadata_t hit = {};
    const float hit_x =
        full_viewport_button_document ? active_width * 0.5f : 24.0f;
    const float hit_y =
        full_viewport_button_document ? active_height * 0.5f : 24.0f;
    const char* expected_hit_id =
        full_viewport_button_document ? "play" : "box";
    status = blink_standalone_renderer_hit_test(renderer, hit_x, hit_y, &hit);
    if (status == BLINK_STANDALONE_STATUS_OK) {
      if (std::string(hit.element_id ? hit.element_id : "") !=
              expected_hit_id ||
          std::string(hit.data_godot_action ? hit.data_godot_action : "") !=
              "play") {
        std::fprintf(stderr,
                     "%s: button/action hit metadata mismatch element=%s "
                     "action=%s count=%zu\n",
                     label, hit.element_id ? hit.element_id : "",
                     hit.data_godot_action ? hit.data_godot_action : "",
                     blink_standalone_renderer_hit_metadata_count(renderer));
        return cleanup_and_fail();
      }
    } else {
      if (full_viewport_button_document) {
        std::fprintf(stderr,
                     "%s: full-viewport button hit metadata missing "
                     "status=%d count=%zu\n",
                     label, status,
                     blink_standalone_renderer_hit_metadata_count(renderer));
        return cleanup_and_fail();
      }
      std::printf(
          "%s: button/action metadata unavailable after gpu-only frame "
          "status=%d count=%zu\n",
          label, status, blink_standalone_renderer_hit_metadata_count(renderer));
    }
  }
  if (exercise_host_pending_resize_boundary) {
    status = blink_standalone_renderer_mouse_move(renderer, 24.0f, 24.0f, 0);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "%s: pre-resize mouse move failed status=%d error=%s\n",
                   label, status, blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    status = blink_standalone_renderer_mouse_down(
        renderer, 24.0f, 24.0f, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "%s: pre-resize mouse down failed status=%d error=%s\n",
                   label, status, blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    blink_standalone_update_result_t pre_resize_down_update = {};
    status = blink_standalone_renderer_update(renderer, 0.125,
                                              &pre_resize_down_update);
    if (status != BLINK_STANDALONE_STATUS_OK ||
        pre_resize_down_update.needs_output == 0) {
      std::fprintf(stderr,
                   "%s: pre-resize mouse down update failed status=%d "
                   "needs_output=%u error=%s\n",
                   label, status, pre_resize_down_update.needs_output,
                   blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    status = blink_standalone_renderer_mouse_up(
        renderer, 24.0f, 24.0f, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "%s: pre-resize mouse up failed status=%d error=%s\n",
                   label, status, blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    blink_standalone_update_result_t pre_resize_up_update = {};
    status = blink_standalone_renderer_update(renderer, 0.150,
                                              &pre_resize_up_update);
    if (status != BLINK_STANDALONE_STATUS_OK ||
        pre_resize_up_update.needs_output == 0) {
      std::fprintf(stderr,
                   "%s: pre-resize mouse up update failed status=%d "
                   "needs_output=%u error=%s\n",
                   label, status, pre_resize_up_update.needs_output,
                   blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
  }

  if (exercise_resize_sequence) {
    struct ResizeStep {
      uint32_t width;
      uint32_t height;
    };
    std::vector<ResizeStep> resize_steps;
    if (exercise_host_pending_resize_boundary) {
      resize_steps = {{2532, 1281}};
    } else if (repeated_after_resize_render_iterations > 0) {
      resize_steps = {{width, height + 1}};
    } else if (exercise_rapid_resize_sequence) {
      resize_steps = {{2512, 1301}, {2476, 1284}, {2440, 1267},
                      {2404, 1250}, {2368, 1223}, {2336, 1206},
                      {2316, 1199}, {2296, 1191}, {2240, 1164},
                      {2160, 1120}, {2048, 1088}, {1920, 1080},
                      {1800, 1000}, {1600, 900},  {1400, 780},
                      {1280, 720},  {1152, 648},  {1024, 600},
                      {900, 600},   {1152, 648},  {1280, 720},
                      {1800, 1000}, {2316, 1199}, {2548, 1320}};
    } else {
      resize_steps = {{1280, 720},
                      {1152, 648},
                      {1800, 1000},
                      {900, 600},
                      {2548, 1320}};
    }
    for (const ResizeStep& step : resize_steps) {
      status = blink_standalone_renderer_set_viewport(
          renderer, static_cast<int>(step.width), static_cast<int>(step.height),
          1.0f);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr, "%s: resize set_viewport %ux%u failed status=%d "
                             "error=%s\n",
                     label, step.width, step.height, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      active_width = step.width;
      active_height = step.height;
      target.common.logical_width = active_width;
      target.common.logical_height = active_height;
      target.common.physical_width = active_width;
      target.common.physical_height = active_height;
      target.common.generation++;
      if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
        if (!create_vulkan_target ||
            !create_vulkan_target(active_width, active_height)) {
          std::fprintf(stderr, "%s: resize Vulkan target %ux%u failed\n",
                       label, active_width, active_height);
          return cleanup_and_fail();
        }
      }
#if BUILDFLAG(IS_WIN)
      if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
        if (!create_d3d12_target ||
            !create_d3d12_target(active_width, active_height)) {
          std::fprintf(stderr, "%s: resize D3D12 target %ux%u failed\n",
                       label, active_width, active_height);
          return cleanup_and_fail();
        }
        if (omit_d3d12_resource_hint_after_resize) {
          target.d3d12.d3d12_resource = nullptr;
        }
      }
#endif
      if (exercise_host_pending_resize_boundary) {
        target.common.flags |=
            BLINK_STANDALONE_GPU_TARGET_INTERNAL_FORCE_PENDING_ONCE;
        blink_standalone_gpu_render_result_t pre_update_render = {};
        status = blink_standalone_renderer_render_to_gpu_target(
            renderer, &target, &pre_update_render);
        target.common.flags &=
            ~BLINK_STANDALONE_GPU_TARGET_INTERNAL_FORCE_PENDING_ONCE;
        if (status == BLINK_STANDALONE_STATUS_PENDING &&
            pre_update_render.target_written == 0) {
          ++pending_resize_retries;
          blink_standalone_update_result_t host_update = {};
          status = blink_standalone_renderer_update(
              renderer, 0.500 + static_cast<double>(target.common.generation) *
                                    0.016,
              &host_update);
          if (status != BLINK_STANDALONE_STATUS_OK ||
              host_update.needs_output == 0) {
            std::fprintf(stderr,
                         "%s: host-frame update after pre-update pending "
                         "failed status=%d needs_output=%u skipped=%u "
                         "error=%s\n",
                         label, status, host_update.needs_output,
                         host_update.frame_skipped_due_to_no_demand,
                         blink_standalone_renderer_last_error(renderer));
            return cleanup_and_fail();
          }
          int retry_count = 0;
          blink_standalone_gpu_render_result_t retry_render = {};
          do {
            retry_render = blink_standalone_gpu_render_result_t{};
            status = blink_standalone_renderer_render_to_gpu_target(
                renderer, &target, &retry_render);
            if (status == BLINK_STANDALONE_STATUS_PENDING &&
                retry_render.target_written == 0) {
              ++retry_count;
              ++pending_resize_retries;
              std::this_thread::sleep_for(std::chrono::milliseconds(1));
            } else {
              break;
            }
          } while (retry_count < 8);
          if (status != BLINK_STANDALONE_STATUS_OK ||
              retry_render.target_written == 0 ||
              retry_render.backend != backend ||
              retry_render.width != active_width ||
              retry_render.height != active_height) {
            std::fprintf(stderr,
                         "%s: host-boundary retry render %ux%u failed "
                         "status=%d result_status=%u backend=%u written=%u "
                         "size=%ux%u error=%s\n",
                         label, active_width, active_height, status,
                         retry_render.status, retry_render.backend,
                         retry_render.target_written, retry_render.width,
                         retry_render.height,
                         blink_standalone_renderer_last_error(renderer));
            return cleanup_and_fail();
          }
          if (!verify_target_pixels("host-boundary-resize",
                                    expected_background, expected_box,
                                    require_full_nontransparent,
                                    /*quiet=*/false)) {
            return cleanup_and_fail();
          }
          continue;
        }
        if (status == BLINK_STANDALONE_STATUS_OK &&
            pre_update_render.target_written != 0 &&
            pre_update_render.backend == backend &&
            pre_update_render.width == active_width &&
            pre_update_render.height == active_height) {
          if (!verify_target_pixels("host-boundary-resize-direct",
                                    expected_background, expected_box,
                                    require_full_nontransparent,
                                    /*quiet=*/false)) {
            return cleanup_and_fail();
          }
          continue;
        }
      }
      blink_standalone_update_result_t resize_update = {};
      status = blink_standalone_renderer_update(
          renderer, 0.250 + static_cast<double>(target.common.generation) *
                                0.016,
          &resize_update);
      if (status != BLINK_STANDALONE_STATUS_OK ||
          resize_update.needs_output == 0) {
        std::fprintf(stderr,
                     "%s: resize update %ux%u failed status=%d "
                     "needs_output=%u error=%s\n",
                     label, active_width, active_height, status,
                     resize_update.needs_output,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      blink_standalone_gpu_render_result_t resize_render = {};
      status = blink_standalone_renderer_render_to_gpu_target(
          renderer, &target, &resize_render);
      if (exercise_host_pending_resize_boundary &&
          status == BLINK_STANDALONE_STATUS_PENDING &&
          resize_render.target_written == 0) {
        ++pending_resize_retries;
        blink_standalone_update_result_t host_update = {};
        status = blink_standalone_renderer_update(
            renderer, 0.500 + static_cast<double>(target.common.generation) *
                                  0.016,
            &host_update);
        if (status != BLINK_STANDALONE_STATUS_OK ||
            host_update.needs_output == 0) {
          std::fprintf(stderr,
                       "%s: host-frame update after pending failed "
                       "status=%d needs_output=%u skipped=%u error=%s\n",
                       label, status, host_update.needs_output,
                       host_update.frame_skipped_due_to_no_demand,
                       blink_standalone_renderer_last_error(renderer));
          return cleanup_and_fail();
        }
        int retry_count = 0;
        do {
          resize_render = blink_standalone_gpu_render_result_t{};
          status = blink_standalone_renderer_render_to_gpu_target(
              renderer, &target, &resize_render);
          if (status == BLINK_STANDALONE_STATUS_PENDING &&
              resize_render.target_written == 0) {
            ++retry_count;
            ++pending_resize_retries;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
          } else {
            break;
          }
        } while (retry_count < 8);
      } else if (tolerate_pending_resize_retry) {
        int retry_count = 0;
        while (status == BLINK_STANDALONE_STATUS_PENDING &&
               resize_render.target_written == 0 && retry_count < 8) {
          ++retry_count;
          ++pending_resize_retries;
          resize_render = blink_standalone_gpu_render_result_t{};
          status = blink_standalone_renderer_render_to_gpu_target(
              renderer, &target, &resize_render);
        }
      }
      if (status != BLINK_STANDALONE_STATUS_OK ||
          resize_render.target_written == 0 || resize_render.backend != backend ||
          resize_render.width != active_width ||
          resize_render.height != active_height) {
        std::fprintf(stderr,
                     "%s: resize render %ux%u failed status=%d "
                     "result_status=%u backend=%u written=%u size=%ux%u "
                     "error=%s\n",
                     label, active_width, active_height, status,
                     resize_render.status, resize_render.backend,
                     resize_render.target_written, resize_render.width,
                     resize_render.height,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (!verify_target_pixels("resize", expected_background, expected_box,
                                require_full_nontransparent, /*quiet=*/false)) {
        return cleanup_and_fail();
      }
      for (int i = 0; i < repeated_after_resize_render_iterations; ++i) {
        target.common.generation++;
        target.vulkan.current_layout = target.vulkan.required_final_layout;
#if BUILDFLAG(IS_WIN)
        target.d3d12.current_state = target.d3d12.required_final_state;
        if (rotate_d3d12_shared_handle_after_resize &&
            backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
            d3d12_resource) {
          HANDLE rotated_handle = nullptr;
          HRESULT rotate_hr = d3d12_device->CreateSharedHandle(
              d3d12_resource.Get(), nullptr, GENERIC_ALL, nullptr,
              &rotated_handle);
          if (FAILED(rotate_hr) || !rotated_handle) {
            std::fprintf(stderr,
                         "%s: post-resize repeated render %d failed to "
                         "rotate D3D12 shared handle hr=0x%08lx\n",
                         label, i, static_cast<unsigned long>(rotate_hr));
            return cleanup_and_fail();
          }
          if (target.d3d12.shared_handle) {
            CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
          }
          d3d12_shared_handle = rotated_handle;
          target.d3d12.shared_handle = d3d12_shared_handle;
          if (!omit_d3d12_resource_hint_after_resize) {
            if (alias_d3d12_resource_hint_after_resize &&
                SUCCEEDED(d3d12_resource.As(&d3d12_resource_alias)) &&
                d3d12_resource_alias) {
              target.d3d12.d3d12_resource = d3d12_resource_alias.Get();
            } else {
              target.d3d12.d3d12_resource = d3d12_resource.Get();
            }
          }
        }
        const bool invalidated_d3d12_shared_handle =
            invalidate_d3d12_shared_handle_after_resize && i == 0 &&
            backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
            target.d3d12.shared_handle != nullptr;
        if (invalidated_d3d12_shared_handle) {
          target.d3d12.shared_handle = reinterpret_cast<void*>(uintptr_t{1});
        }
#endif
        blink_standalone_gpu_render_result_t repeated_render = {};
        status = blink_standalone_renderer_render_to_gpu_target(
            renderer, &target, &repeated_render);
#if BUILDFLAG(IS_WIN)
        if (invalidated_d3d12_shared_handle) {
          target.d3d12.shared_handle = d3d12_shared_handle;
        }
#endif
        if (status != BLINK_STANDALONE_STATUS_OK ||
            repeated_render.target_written == 0 ||
            repeated_render.backend != backend ||
            repeated_render.width != active_width ||
            repeated_render.height != active_height) {
          std::fprintf(stderr,
                       "%s: post-resize repeated render %d failed status=%d "
                       "result_status=%u backend=%u written=%u size=%ux%u "
                       "error=%s\n",
                       label, i, status, repeated_render.status,
                       repeated_render.backend, repeated_render.target_written,
                       repeated_render.width, repeated_render.height,
                       blink_standalone_renderer_last_error(renderer));
          return cleanup_and_fail();
        }
        if (!verify_target_pixels("post-resize-repeated", expected_background,
                                  expected_box, require_full_nontransparent,
                                  /*quiet=*/false)) {
          return cleanup_and_fail();
        }
        ++post_resize_repeated_renders;
      }
#if BUILDFLAG(IS_WIN)
      if (expect_invalid_uncached_d3d12_handle_after_resize &&
          backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
        target.common.generation++;
        if (!create_d3d12_target ||
            !create_d3d12_target(active_width, active_height)) {
          std::fprintf(stderr,
                       "%s: invalid uncached D3D12 target setup failed\n",
                       label);
          return cleanup_and_fail();
        }
        void* valid_shared_handle = target.d3d12.shared_handle;
        target.d3d12.shared_handle = reinterpret_cast<void*>(uintptr_t{1});
        blink_standalone_gpu_render_result_t invalid_render = {};
        status = blink_standalone_renderer_render_to_gpu_target(
            renderer, &target, &invalid_render);
        target.d3d12.shared_handle = valid_shared_handle;
        const char* invalid_error =
            blink_standalone_renderer_last_error(renderer);
        const std::string invalid_error_text =
            invalid_error ? invalid_error : "";
        const bool direct_resource_succeeded =
            status == BLINK_STANDALONE_STATUS_OK &&
            invalid_render.target_written != 0 &&
            invalid_render.backend == backend &&
            invalid_render.width == active_width &&
            invalid_render.height == active_height;
        const bool invalid_target_reported =
            status == BLINK_STANDALONE_STATUS_INVALID_ARGUMENT &&
            invalid_render.target_written == 0 &&
            invalid_error_text.find(
                "borrowed external D3D12 shared handle open failed") !=
                std::string::npos &&
            invalid_error_text.find("direct_resource_compatible=0") !=
                std::string::npos;
        if (!direct_resource_succeeded && !invalid_target_reported) {
          std::fprintf(stderr,
                       "%s: invalid uncached D3D12 target was not reported "
                       "cleanly status=%d result_status=%u written=%u "
                       "error=%s\n",
                       label, status, invalid_render.status,
                       invalid_render.target_written, invalid_error);
          return cleanup_and_fail();
        }
        if (direct_resource_succeeded &&
            !verify_target_pixels("invalid-handle-direct-resource",
                                  expected_background, expected_box,
                                  require_full_nontransparent,
                                  /*quiet=*/false)) {
          return cleanup_and_fail();
        }
        ++invalid_uncached_d3d12_target_checks;
      }
#endif
    }
  }

  if (exercise_update_output_sequence) {
    constexpr uint32_t kMutatedBox = 0xff00a050u;
    status = blink_standalone_renderer_set_element_style(
        renderer, "box",
        "position:absolute;left:16px;top:12px;width:80px;height:32px;"
        "background:#00a050");
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr, "%s: style mutation failed status=%d error=%s\n",
                   label, status, blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    blink_standalone_update_result_t update_result = {};
    status = blink_standalone_renderer_update(renderer, 0.050, &update_result);
    if (status != BLINK_STANDALONE_STATUS_OK ||
        update_result.needs_output == 0) {
      std::fprintf(stderr,
                   "%s: update failed status=%d needs_output=%u error=%s\n",
                   label, status, update_result.needs_output,
                   blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    target.common.generation++;
    target.vulkan.current_layout = target.vulkan.required_final_layout;
#if BUILDFLAG(IS_WIN)
    target.d3d12.current_state = target.d3d12.required_final_state;
#endif
    blink_standalone_gpu_render_result_t update_render_result = {};
    status = blink_standalone_renderer_render_to_gpu_target(
        renderer, &target, &update_render_result);
    if (status != BLINK_STANDALONE_STATUS_OK ||
        update_render_result.target_written == 0 ||
        update_render_result.backend != backend ||
        update_render_result.width != active_width ||
        update_render_result.height != active_height) {
      std::fprintf(stderr,
                   "%s: update render failed status=%d result_status=%u "
                   "backend=%u written=%u size=%ux%u error=%s\n",
                   label, status, update_render_result.status,
                   update_render_result.backend,
                   update_render_result.target_written,
                   update_render_result.width, update_render_result.height,
                   blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    if (!verify_target_pixels("mutated", expected_background, kMutatedBox,
                              require_full_nontransparent, /*quiet=*/false)) {
      return cleanup_and_fail();
    }
  }

  if (repeated_update_output_iterations > 0) {
    double update_total_ms = 0.0;
    double update_max_ms = 0.0;
    double render_total_ms = 0.0;
    double render_max_ms = 0.0;
    int render_count = 0;
    int pending_count = 0;
    uint32_t expected_timed_box = expected_box;
    for (int i = 0; i < repeated_update_output_iterations; ++i) {
      const bool green = (i % 2) == 0;
      expected_timed_box = green ? 0xff00a050u : 0xffd06329u;
      status = blink_standalone_renderer_set_element_style(
          renderer, "box",
          green ? "position:absolute;left:16px;top:12px;width:80px;"
                  "height:32px;background:#00a050"
                : "position:absolute;left:16px;top:12px;width:80px;"
                  "height:32px;background:#d06329");
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr, "%s: timed style mutation %d failed status=%d "
                             "error=%s\n",
                     label, i, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      status = blink_standalone_renderer_mouse_move(
          renderer, 549.0f + static_cast<float>(i % 7), 422.0f, 0);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr,
                     "%s: timed mouse move %d failed status=%d error=%s\n",
                     label, i, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }

      blink_standalone_update_result_t update_result = {};
      const auto update_start = std::chrono::steady_clock::now();
      status = blink_standalone_renderer_update(
          renderer, 0.100 + static_cast<double>(i) * 0.016, &update_result);
      const auto update_end = std::chrono::steady_clock::now();
      const double update_ms =
          std::chrono::duration<double, std::milli>(update_end - update_start)
              .count();
      update_total_ms += update_ms;
      update_max_ms = std::max(update_max_ms, update_ms);
      if (status != BLINK_STANDALONE_STATUS_OK ||
          update_result.needs_output == 0) {
        std::fprintf(stderr,
                     "%s: timed update %d failed status=%d needs_output=%u "
                     "error=%s\n",
                     label, i, status, update_result.needs_output,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }

      blink_standalone_gpu_render_result_t timed_render_result = {};
      constexpr int kMaxPendingRetries = 8;
      int attempt = 0;
      double last_render_ms = 0.0;
      for (; attempt <= kMaxPendingRetries; ++attempt) {
        target.common.generation++;
        target.vulkan.current_layout = target.vulkan.required_final_layout;
#if BUILDFLAG(IS_WIN)
        target.d3d12.current_state = target.d3d12.required_final_state;
#endif
        timed_render_result = blink_standalone_gpu_render_result_t{};
        const auto render_start = std::chrono::steady_clock::now();
        status = blink_standalone_renderer_render_to_gpu_target(
            renderer, &target, &timed_render_result);
        const auto render_end = std::chrono::steady_clock::now();
        const double render_ms =
            std::chrono::duration<double, std::milli>(render_end - render_start)
                .count();
        last_render_ms = render_ms;
        render_total_ms += render_ms;
        render_max_ms = std::max(render_max_ms, render_ms);
        ++render_count;
        if (status == BLINK_STANDALONE_STATUS_PENDING &&
            timed_render_result.target_written == 0) {
          ++pending_count;
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          continue;
        }
        break;
      }
      if (attempt > kMaxPendingRetries) {
        std::fprintf(stderr,
                     "%s: timed render %d stayed pending after retries "
                     "pending_count=%d error=%s\n",
                     label, i, pending_count,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (status != BLINK_STANDALONE_STATUS_OK ||
          timed_render_result.target_written == 0 ||
          timed_render_result.backend != backend ||
          timed_render_result.width != active_width ||
          timed_render_result.height != active_height) {
        std::fprintf(stderr,
                     "%s: timed render %d failed status=%d result_status=%u "
                     "backend=%u written=%u size=%ux%u elapsed_ms=%.3f "
                     "error=%s\n",
                     label, i, status, timed_render_result.status,
                     timed_render_result.backend,
                     timed_render_result.target_written,
                     timed_render_result.width, timed_render_result.height,
                     last_render_ms,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (last_render_ms > 4500.0) {
        std::fprintf(stderr,
                     "%s: timed render %d exceeded timeout budget "
                     "elapsed_ms=%.3f\n",
                     label, i, last_render_ms);
        return cleanup_and_fail();
      }
    }
    if (!verify_target_pixels("timed-final", expected_background,
                              expected_timed_box,
                              require_full_nontransparent, /*quiet=*/false)) {
      return cleanup_and_fail();
    }
    std::printf(
        "%s: timing iterations=%d update_avg_ms=%.3f update_max_ms=%.3f "
        "render_avg_ms=%.3f render_max_ms=%.3f pending=%d\n",
        label, repeated_update_output_iterations,
        update_total_ms / repeated_update_output_iterations, update_max_ms,
        render_total_ms / std::max(1, render_count), render_max_ms,
        pending_count);

    // Warm the hover state once, then verify inert moves stay bounded and do
    // not request output. This catches scheduler/frame-sink timeout regressions
    // seen in large-window visible embedder runs.
    status = blink_standalone_renderer_mouse_move(renderer, 549.0f, 422.0f, 0);
    blink_standalone_update_result_t warm_mouse_update = {};
    if (status != BLINK_STANDALONE_STATUS_OK ||
        blink_standalone_renderer_update(renderer, 0.400,
                                         &warm_mouse_update) !=
            BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr, "%s: mouse warmup update failed status=%d error=%s\n",
                   label, status, blink_standalone_renderer_last_error(renderer));
      return cleanup_and_fail();
    }
    constexpr int kInertMouseIterations = 12;
    double inert_update_total_ms = 0.0;
    double inert_update_max_ms = 0.0;
    for (int i = 0; i < kInertMouseIterations; ++i) {
      status = blink_standalone_renderer_mouse_move(
          renderer, 549.0f + static_cast<float>(i % 3), 422.0f, 0);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr,
                     "%s: inert mouse move %d failed status=%d error=%s\n",
                     label, i, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      blink_standalone_update_result_t inert_update = {};
      const auto inert_start = std::chrono::steady_clock::now();
      status = blink_standalone_renderer_update(
          renderer, 0.500 + static_cast<double>(i) * 0.016, &inert_update);
      const auto inert_end = std::chrono::steady_clock::now();
      const double inert_ms =
          std::chrono::duration<double, std::milli>(inert_end - inert_start)
              .count();
      inert_update_total_ms += inert_ms;
      inert_update_max_ms = std::max(inert_update_max_ms, inert_ms);
      if (status != BLINK_STANDALONE_STATUS_OK ||
          inert_update.needs_output != 0) {
        std::fprintf(stderr,
                     "%s: inert mouse update %d failed status=%d "
                     "needs_output=%u elapsed_ms=%.3f error=%s\n",
                     label, i, status, inert_update.needs_output, inert_ms,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (inert_ms > 250.0) {
        std::fprintf(stderr,
                     "%s: inert mouse update %d exceeded latency budget "
                     "elapsed_ms=%.3f\n",
                     label, i, inert_ms);
        return cleanup_and_fail();
      }
    }
    std::printf(
        "%s: inert_mouse iterations=%d update_avg_ms=%.3f "
        "update_max_ms=%.3f\n",
        label, kInertMouseIterations,
        inert_update_total_ms / kInertMouseIterations, inert_update_max_ms);
  }

  if (repeated_click_output_iterations > 0) {
    constexpr uint32_t kActiveBox = 0xff00a050u;
    double click_update_total_ms = 0.0;
    double click_update_max_ms = 0.0;
    double click_render_total_ms = 0.0;
    double click_render_max_ms = 0.0;
    int click_render_count = 0;
    int click_pending_count = 0;
    const auto render_click_stage = [&](const char* stage,
                                        int iteration,
                                        uint32_t stage_expected_box) {
      constexpr int kMaxPendingRetries = 8;
      for (int attempt = 0; attempt <= kMaxPendingRetries; ++attempt) {
        target.common.generation++;
        target.vulkan.current_layout = target.vulkan.required_final_layout;
#if BUILDFLAG(IS_WIN)
        target.d3d12.current_state = target.d3d12.required_final_state;
#endif
        blink_standalone_gpu_render_result_t click_render_result = {};
        const auto render_start = std::chrono::steady_clock::now();
        status = blink_standalone_renderer_render_to_gpu_target(
            renderer, &target, &click_render_result);
        const auto render_end = std::chrono::steady_clock::now();
        const double render_ms =
            std::chrono::duration<double, std::milli>(render_end - render_start)
                .count();
        click_render_total_ms += render_ms;
        click_render_max_ms = std::max(click_render_max_ms, render_ms);
        ++click_render_count;
        if (render_ms > 100.0) {
          std::fprintf(stderr,
                       "%s: click %s render %d attempt %d exceeded latency "
                       "budget elapsed_ms=%.3f status=%d result_status=%u "
                       "error=%s\n",
                       label, stage, iteration, attempt, render_ms, status,
                       click_render_result.status,
                       blink_standalone_renderer_last_error(renderer));
          return false;
        }
        if (status == BLINK_STANDALONE_STATUS_PENDING &&
            click_render_result.target_written == 0) {
          ++click_pending_count;
          blink_standalone_update_result_t pending_update = {};
          status = blink_standalone_renderer_update(
              renderer, 0.950 + static_cast<double>(iteration) * 0.050 +
                            static_cast<double>(attempt) * 0.004,
              &pending_update);
          if (status != BLINK_STANDALONE_STATUS_OK ||
              pending_update.needs_output == 0) {
            std::fprintf(stderr,
                         "%s: click %s pending update %d attempt %d failed "
                         "status=%d needs_output=%u error=%s\n",
                         label, stage, iteration, attempt, status,
                         pending_update.needs_output,
                         blink_standalone_renderer_last_error(renderer));
            return false;
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          continue;
        }
        if (status != BLINK_STANDALONE_STATUS_OK ||
            click_render_result.target_written == 0 ||
            click_render_result.backend != backend ||
            click_render_result.width != active_width ||
            click_render_result.height != active_height) {
          std::fprintf(stderr,
                       "%s: click %s render %d failed status=%d "
                       "result_status=%u backend=%u written=%u size=%ux%u "
                       "elapsed_ms=%.3f error=%s\n",
                       label, stage, iteration, status,
                       click_render_result.status, click_render_result.backend,
                       click_render_result.target_written,
                       click_render_result.width, click_render_result.height,
                       render_ms, blink_standalone_renderer_last_error(renderer));
          return false;
        }
        const std::string stage_name(stage);
        const bool allow_active_transition_retry =
            (stage_name == "click-down" && stage_expected_box == kActiveBox &&
             observed_box == expected_box) ||
            (stage_name == "click-up" && stage_expected_box != kActiveBox &&
             observed_box == kActiveBox);
        if (verify_target_pixels(stage, expected_background,
                                 stage_expected_box,
                                 require_full_nontransparent,
                                 allow_active_transition_retry)) {
          return true;
        }
        if (allow_active_transition_retry && attempt < kMaxPendingRetries) {
          blink_standalone_update_result_t settle_update = {};
          status = blink_standalone_renderer_update(
              renderer, 1.200 + static_cast<double>(iteration) * 0.050 +
                            static_cast<double>(attempt) * 0.004,
              &settle_update);
          if (status != BLINK_STANDALONE_STATUS_OK) {
            std::fprintf(stderr,
                         "%s: click %s settle update %d attempt %d failed "
                         "status=%d error=%s\n",
                         label, stage, iteration, attempt, status,
                         blink_standalone_renderer_last_error(renderer));
            return false;
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          continue;
        }
        verify_target_pixels(stage, expected_background, stage_expected_box,
                             require_full_nontransparent, /*quiet=*/false);
        return false;
      }
      std::fprintf(stderr,
                   "%s: click %s render %d stayed pending after retries "
                   "pending_count=%d error=%s\n",
                   label, stage, iteration, click_pending_count,
                   blink_standalone_renderer_last_error(renderer));
      return false;
    };
    for (int i = 0; i < repeated_click_output_iterations; ++i) {
      const float x = 24.0f + static_cast<float>(i % 5);
      const float y = 24.0f;
      status = blink_standalone_renderer_mouse_move(renderer, x, y, 0);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr,
                     "%s: click mouse move %d failed status=%d error=%s\n",
                     label, i, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      status = blink_standalone_renderer_mouse_down(
          renderer, x, y, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr,
                     "%s: click mouse down %d failed status=%d error=%s\n",
                     label, i, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      blink_standalone_update_result_t down_update = {};
      const auto down_start = std::chrono::steady_clock::now();
      status = blink_standalone_renderer_update(
          renderer, 0.900 + static_cast<double>(i) * 0.050, &down_update);
      const auto down_end = std::chrono::steady_clock::now();
      const double down_ms =
          std::chrono::duration<double, std::milli>(down_end - down_start)
              .count();
      click_update_total_ms += down_ms;
      click_update_max_ms = std::max(click_update_max_ms, down_ms);
      if (status != BLINK_STANDALONE_STATUS_OK ||
          down_update.needs_output == 0) {
        std::fprintf(stderr,
                     "%s: click mouse down update %d failed status=%d "
                     "needs_output=%u elapsed_ms=%.3f error=%s\n",
                     label, i, status, down_update.needs_output, down_ms,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (down_ms > 250.0) {
        std::fprintf(stderr,
                     "%s: click mouse down update %d exceeded latency budget "
                     "elapsed_ms=%.3f\n",
                     label, i, down_ms);
        return cleanup_and_fail();
      }
      if (!render_click_stage("click-down", i, kActiveBox)) {
        return cleanup_and_fail();
      }

      status = blink_standalone_renderer_mouse_up(
          renderer, x, y, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
      if (status != BLINK_STANDALONE_STATUS_OK) {
        std::fprintf(stderr,
                     "%s: click mouse up %d failed status=%d error=%s\n",
                     label, i, status,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      blink_standalone_update_result_t up_update = {};
      const auto up_start = std::chrono::steady_clock::now();
      status = blink_standalone_renderer_update(
          renderer, 0.925 + static_cast<double>(i) * 0.050, &up_update);
      const auto up_end = std::chrono::steady_clock::now();
      const double up_ms =
          std::chrono::duration<double, std::milli>(up_end - up_start).count();
      click_update_total_ms += up_ms;
      click_update_max_ms = std::max(click_update_max_ms, up_ms);
      if (status != BLINK_STANDALONE_STATUS_OK ||
          up_update.needs_output == 0) {
        std::fprintf(stderr,
                     "%s: click mouse up update %d failed status=%d "
                     "needs_output=%u elapsed_ms=%.3f error=%s\n",
                     label, i, status, up_update.needs_output, up_ms,
                     blink_standalone_renderer_last_error(renderer));
        return cleanup_and_fail();
      }
      if (up_ms > 250.0) {
        std::fprintf(stderr,
                     "%s: click mouse up update %d exceeded latency budget "
                     "elapsed_ms=%.3f\n",
                     label, i, up_ms);
        return cleanup_and_fail();
      }
      if (!render_click_stage("click-up", i, expected_box)) {
        return cleanup_and_fail();
      }
    }
    const int click_update_count = repeated_click_output_iterations * 2;
    std::printf(
        "%s: click_timing iterations=%d update_avg_ms=%.3f "
        "update_max_ms=%.3f render_avg_ms=%.3f render_max_ms=%.3f "
        "pending=%d\n",
        label, repeated_click_output_iterations,
        click_update_total_ms / click_update_count, click_update_max_ms,
        click_render_total_ms / click_render_count, click_render_max_ms,
        click_pending_count);
  }

  std::printf(
      "%s: ok backend=%u capabilities=%u target_written=%u size=%ux%u "
      "format=%u generation=%llu observed_background=%08x observed_box=%08x "
      "background_pixels=%u box_pixels=%u nontransparent_pixels=%u "
      "pending_resize_retries=%d repeated_same_target=%d "
      "post_resize_repeated=%d invalid_uncached_d3d12=%d\n",
      label, result.backend, capabilities, result.target_written, result.width,
      result.height, result.pixel_format,
      static_cast<unsigned long long>(result.generation), observed_background,
      observed_box, background_pixels, box_pixels, nontransparent_pixels,
      pending_resize_retries, repeated_same_target_renders,
      post_resize_repeated_renders, invalid_uncached_d3d12_target_checks);
#if BUILDFLAG(IS_WIN)
  if (target.d3d12.shared_handle) {
    CloseHandle(static_cast<HANDLE>(target.d3d12.shared_handle));
  }
#endif
  blink_standalone_renderer_destroy(renderer);
  cleanup_vulkan_target();
  return 0;
}

int RunCApiVulkanExternalTargetSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_smoke",
      /*require_external_target=*/true);
}

int RunCApiVulkanExternalTargetLargeSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_large_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320);
}

int RunCApiVulkanExternalTargetResizeSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_resize_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true);
}

int RunCApiVulkanExternalTargetRapidResizeSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_rapid_resize_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/0,
      /*tolerate_pending_resize_retry=*/true,
      /*use_button_action_document=*/false,
      /*exercise_host_pending_resize_boundary=*/false,
      /*repeated_same_target_render_iterations=*/0,
      /*repeated_after_resize_render_iterations=*/0,
      /*omit_d3d12_resource_hint_after_resize=*/false,
      /*rotate_d3d12_shared_handle_after_resize=*/false,
      /*alias_d3d12_resource_hint_after_resize=*/false,
      /*invalidate_d3d12_shared_handle_after_resize=*/false,
      /*expect_invalid_uncached_d3d12_handle_after_resize=*/false,
      /*full_viewport_button_document=*/false,
      /*exercise_rapid_resize_sequence=*/true);
}

int RunCApiVulkanExternalTargetPendingResizeSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_pending_resize_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/0,
      /*tolerate_pending_resize_retry=*/true);
}

int RunCApiVulkanExternalTargetFpsTimingSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_fps_timing_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"#counter{position:absolute;left:120px;top:12px;"
                    "font:32px sans-serif;color:white}",
      /*extra_body=*/"<div id='counter'>fps</div>",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/12);
}

int RunCApiVulkanExternalTargetClickTimingSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_click_timing_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"#box{cursor:pointer;}#box:active{background:#00a050;}",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/8);
}

int RunCApiVulkanExternalTargetClickResizePendingSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_click_resize_pending_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"#box{cursor:pointer;}#box:active{background:#00a050;}",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/4,
      /*tolerate_pending_resize_retry=*/true,
      /*use_button_action_document=*/true,
      /*exercise_host_pending_resize_boundary=*/true);
}

int RunCApiVulkanExternalTargetFullViewportButtonHitMetadataSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_full_viewport_button_hit_metadata_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff237a57u,
      /*expected_box=*/0xff237a57u,
      /*background_css=*/"#237a57",
      /*box_css=*/"#237a57",
      /*width=*/1280,
      /*height=*/720,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/false,
      /*repeated_click_output_iterations=*/0,
      /*tolerate_pending_resize_retry=*/false,
      /*use_button_action_document=*/false,
      /*exercise_host_pending_resize_boundary=*/false,
      /*repeated_same_target_render_iterations=*/0,
      /*repeated_after_resize_render_iterations=*/0,
      /*omit_d3d12_resource_hint_after_resize=*/false,
      /*rotate_d3d12_shared_handle_after_resize=*/false,
      /*alias_d3d12_resource_hint_after_resize=*/false,
      /*invalidate_d3d12_shared_handle_after_resize=*/false,
      /*expect_invalid_uncached_d3d12_handle_after_resize=*/false,
      /*full_viewport_button_document=*/true);
}

int RunCApiVulkanInvalidTargetMetadataSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_invalid_target_metadata_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/true);
}

int RunCApiVulkanUpdateOutputSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_update_output_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/128,
      /*height=*/64,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/true);
}

int RunCApiD3D12ExternalTargetSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_smoke",
      /*require_external_target=*/true);
}

int RunCApiD3D12ExternalTargetResizeSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_resize_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true);
}

int RunCApiD3D12ExternalTargetClickTimingSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_click_timing_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/2548,
      /*height=*/1320,
      /*extra_css=*/"#box{cursor:pointer;}#box:active{background:#00a050;}",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/8);
}

int RunCApiD3D12ExternalTargetButtonActivationSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_button_activation_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/1280,
      /*height=*/721,
      /*extra_css=*/"#box{cursor:pointer;}#box:active{background:#00a050;}",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/false,
      /*repeated_click_output_iterations=*/4,
      /*tolerate_pending_resize_retry=*/false,
      /*use_button_action_document=*/true);
}

int RunCApiD3D12ExternalTargetClickResizeSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_click_resize_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/1280,
      /*height=*/721,
      /*extra_css=*/"#box{cursor:pointer;}#box:active{background:#00a050;}",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/4,
      /*tolerate_pending_resize_retry=*/false,
      /*use_button_action_document=*/true);
}

int RunCApiD3D12ExternalTargetFullViewportButtonHitMetadataSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_full_viewport_button_hit_metadata_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff237a57u,
      /*expected_box=*/0xff237a57u,
      /*background_css=*/"#237a57",
      /*box_css=*/"#237a57",
      /*width=*/1280,
      /*height=*/720,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/false,
      /*repeated_click_output_iterations=*/0,
      /*tolerate_pending_resize_retry=*/false,
      /*use_button_action_document=*/false,
      /*exercise_host_pending_resize_boundary=*/false,
      /*repeated_same_target_render_iterations=*/0,
      /*repeated_after_resize_render_iterations=*/0,
      /*omit_d3d12_resource_hint_after_resize=*/false,
      /*rotate_d3d12_shared_handle_after_resize=*/false,
      /*alias_d3d12_resource_hint_after_resize=*/false,
      /*invalidate_d3d12_shared_handle_after_resize=*/false,
      /*expect_invalid_uncached_d3d12_handle_after_resize=*/false,
      /*full_viewport_button_document=*/true);
}

int RunCApiD3D12ExternalTargetRepeatedFrameSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_repeated_frame_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/1280,
      /*height=*/720,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/false,
      /*expect_invalid_vulkan_metadata=*/false,
      /*repeated_update_output_iterations=*/0,
      /*exercise_resize_sequence=*/true,
      /*repeated_click_output_iterations=*/0,
      /*tolerate_pending_resize_retry=*/false,
      /*use_button_action_document=*/false,
      /*exercise_host_pending_resize_boundary=*/false,
      /*repeated_same_target_render_iterations=*/0,
      /*repeated_after_resize_render_iterations=*/4,
      /*omit_d3d12_resource_hint_after_resize=*/false,
      /*rotate_d3d12_shared_handle_after_resize=*/true,
      /*alias_d3d12_resource_hint_after_resize=*/true,
      /*invalidate_d3d12_shared_handle_after_resize=*/true,
      /*expect_invalid_uncached_d3d12_handle_after_resize=*/true);
}

int RunCApiD3D12UpdateOutputSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_update_output_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff123456u,
      /*expected_box=*/0xffd06329u,
      /*background_css=*/"#123456",
      /*box_css=*/"#d06329",
      /*width=*/128,
      /*height=*/64,
      /*extra_css=*/"",
      /*extra_body=*/"",
      /*require_full_nontransparent=*/true,
      /*exercise_update_output_sequence=*/true);
}

int RunCApiVulkanExternalTargetCurrentDocumentSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_VULKAN,
      "c_api_vulkan_external_target_current_document_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff144a80u,
      /*expected_box=*/0xff237a57u,
      /*background_css=*/"#144a80",
      /*box_css=*/"#237a57");
}

int RunCApiD3D12ExternalTargetCurrentDocumentSmoke() {
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_current_document_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff144a80u,
      /*expected_box=*/0xff237a57u,
      /*background_css=*/"#144a80",
      /*box_css=*/"#237a57");
}

int RunCApiD3D12ExternalTargetFilterBackdropSmoke() {
  const char* extra_css =
      "#blurred{position:absolute;left:160px;top:96px;width:480px;"
      "height:220px;background:#d06329;filter:blur(6px) saturate(130%);}"
      "#backdrop{position:absolute;left:640px;top:120px;width:360px;"
      "height:220px;border-radius:28px;background:rgba(255,255,255,.22);"
      "backdrop-filter:blur(12px) saturate(180%) brightness(1.08);"
      "-webkit-backdrop-filter:blur(12px) saturate(180%) brightness(1.08);}"
      "#stripe{position:absolute;left:0;top:360px;width:1280px;height:160px;"
      "background:linear-gradient(90deg,#144a80,#237a57,#d06329);}";
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_filter_backdrop_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0xff144a80u,
      /*expected_box=*/0xff237a57u,
      /*background_css=*/"#144a80",
      /*box_css=*/"#237a57",
      /*width=*/1280,
      /*height=*/720,
      extra_css,
      /*extra_body=*/
      "<div id='blurred'></div><div id='backdrop'></div><div id='stripe'></div>");
}

int RunCApiD3D12ExternalTargetTransparentFilterBackdropSmoke() {
  const char* extra_css =
      "#box{width:260px;height:160px;}"
      "#blurred{position:absolute;left:360px;top:96px;width:480px;"
      "height:220px;background:#d06329;filter:blur(6px) saturate(130%);}"
      "#backdrop{position:absolute;left:720px;top:120px;width:360px;"
      "height:220px;border-radius:28px;background:rgba(255,255,255,.22);"
      "backdrop-filter:blur(12px) saturate(180%) brightness(1.08);"
      "-webkit-backdrop-filter:blur(12px) saturate(180%) brightness(1.08);}";
  return RunCApiExternalGpuTargetSmoke(
      BLINK_STANDALONE_GPU_BACKEND_D3D12,
      "c_api_d3d12_external_target_transparent_filter_backdrop_smoke",
      /*require_external_target=*/true,
      /*expected_background=*/0x00000000u,
      /*expected_box=*/0xff237a57u,
      /*background_css=*/"rgba(0,0,0,0)",
      /*box_css=*/"#237a57",
      /*width=*/1280,
      /*height=*/720,
      extra_css,
      /*extra_body=*/"<div id='blurred'></div><div id='backdrop'></div>",
      /*require_full_nontransparent=*/false);
}

std::vector<uint8_t> MakeSolidBmp(int width,
                                  int height,
                                  uint8_t red,
                                  uint8_t green,
                                  uint8_t blue) {
  const int row_stride = ((width * 3 + 3) / 4) * 4;
  const uint32_t pixel_bytes = static_cast<uint32_t>(row_stride * height);
  const uint32_t file_size = 54u + pixel_bytes;
  std::vector<uint8_t> bytes(file_size, 0);
  auto put16 = [&](size_t offset, uint16_t value) {
    bytes[offset] = static_cast<uint8_t>(value & 0xff);
    bytes[offset + 1] = static_cast<uint8_t>((value >> 8) & 0xff);
  };
  auto put32 = [&](size_t offset, uint32_t value) {
    bytes[offset] = static_cast<uint8_t>(value & 0xff);
    bytes[offset + 1] = static_cast<uint8_t>((value >> 8) & 0xff);
    bytes[offset + 2] = static_cast<uint8_t>((value >> 16) & 0xff);
    bytes[offset + 3] = static_cast<uint8_t>((value >> 24) & 0xff);
  };
  bytes[0] = 'B';
  bytes[1] = 'M';
  put32(2, file_size);
  put32(10, 54);
  put32(14, 40);
  put32(18, static_cast<uint32_t>(width));
  put32(22, static_cast<uint32_t>(height));
  put16(26, 1);
  put16(28, 24);
  put32(34, pixel_bytes);
  for (int y = 0; y < height; ++y) {
    uint8_t* row = bytes.data() + 54 + static_cast<size_t>(y) * row_stride;
    for (int x = 0; x < width; ++x) {
      row[x * 3 + 0] = blue;
      row[x * 3 + 1] = green;
      row[x * 3 + 2] = red;
    }
  }
  return bytes;
}

std::string MakeBmpDataUrl(const std::vector<uint8_t>& bytes) {
  return "data:image/bmp;base64," +
         base::Base64Encode(base::span<const uint8_t>(bytes.data(),
                                                      bytes.size()));
}

struct CApiResourceProviderSmokeState {
  std::vector<uint8_t> green_bmp = MakeSolidBmp(4, 4, 0x23, 0x7a, 0x57);
  std::string theme_css =
      "@import url('asset://imported.css');"
      "body{margin:0;background:#112233}"
      "#bg{position:absolute;left:0;top:0;width:80px;height:80px;"
      "background-image:url('asset://green.bmp');background-size:80px 80px}";
  std::string imported_css =
      "#imported{position:absolute;left:90px;top:0;width:40px;height:40px;"
      "background:#e84444}";
  int request_count = 0;
  int image_request_count = 0;
  int stylesheet_request_count = 0;
  int stylesheet_link_request_count = 0;
  int css_import_request_count = 0;
  int css_background_request_count = 0;
  int not_found_count = 0;
  int release_count = 0;
};

blink_standalone_resource_status_t CApiResourceProviderSmokeLoad(
    void* user_data,
    const blink_standalone_resource_request_t* request,
    blink_standalone_resource_response_t* response) {
  auto* state = static_cast<CApiResourceProviderSmokeState*>(user_data);
  if (!state || !request || !response || !request->url) {
    return BLINK_STANDALONE_RESOURCE_STATUS_ERROR;
  }
  ++state->request_count;
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_IMAGE) {
    ++state->image_request_count;
  }
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_STYLESHEET) {
    ++state->stylesheet_request_count;
  }
  if (request->initiator ==
      BLINK_STANDALONE_RESOURCE_INITIATOR_STYLESHEET_LINK) {
    ++state->stylesheet_link_request_count;
  }
  if (request->initiator == BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_IMPORT) {
    ++state->css_import_request_count;
  }
  if (request->initiator ==
      BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_BACKGROUND_IMAGE) {
    ++state->css_background_request_count;
  }
  const std::string url = request->url;
  if (url.find("theme.css") != std::string::npos) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes = reinterpret_cast<const uint8_t*>(state->theme_css.data());
    response->byte_count = state->theme_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  if (url.find("imported.css") != std::string::npos) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes =
        reinterpret_cast<const uint8_t*>(state->imported_css.data());
    response->byte_count = state->imported_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  const std::vector<uint8_t>* bytes = nullptr;
  if (url.find("green.bmp") != std::string::npos) {
    bytes = &state->green_bmp;
  }
  if (!bytes) {
    ++state->not_found_count;
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
    return BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
  }
  response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
  response->mime_type = "image/bmp";
  response->bytes = bytes->data();
  response->byte_count = bytes->size();
  response->resolved_url_or_cache_key = request->url;
  return BLINK_STANDALONE_RESOURCE_STATUS_OK;
}

void CApiResourceProviderSmokeRelease(
    void* user_data,
    blink_standalone_resource_response_t*) {
  auto* state = static_cast<CApiResourceProviderSmokeState*>(user_data);
  if (state) {
    ++state->release_count;
  }
}

int RunCApiResourceProviderSmoke() {
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
                 "c_api_resource_provider_smoke: create failed status=%d\n",
                 status);
    return 1;
  }
  CApiResourceProviderSmokeState provider_state;
  status = blink_standalone_renderer_set_resource_provider(
      renderer, CApiResourceProviderSmokeLoad,
      CApiResourceProviderSmokeRelease, &provider_state,
      BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_smoke: provider set failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const char* html =
      "<!doctype html><link rel='stylesheet' href='asset://theme.css'>"
      "<div id='bg'></div><div id='imported'></div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_smoke: set html failed status=%d "
                 "error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  blink_standalone_frame_output_t output = {};
  const blink_standalone_status_code_t output_status =
      blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.request_count < 3 ||
      provider_state.image_request_count < 1 ||
      provider_state.stylesheet_request_count < 2 ||
      provider_state.stylesheet_link_request_count < 1 ||
      provider_state.css_import_request_count < 1 ||
      provider_state.css_background_request_count < 1 ||
      provider_state.release_count != provider_state.request_count ||
      stats.resource_red_e84444 < 1200 ||
      stats.resource_green_237a57 < 1500) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_smoke: provider render failed status=%d "
        "output_status=%d requests=%d images=%d stylesheets=%d "
        "link=%d import=%d css_bg=%d releases=%d red=%zu green=%zu "
        "error=%s\n",
        status, output_status, provider_state.request_count,
        provider_state.image_request_count,
        provider_state.stylesheet_request_count,
        provider_state.stylesheet_link_request_count,
        provider_state.css_import_request_count,
        provider_state.css_background_request_count,
        provider_state.release_count, stats.resource_red_e84444,
        stats.resource_green_237a57,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  const int requests_before_missing = provider_state.request_count;
  const char* missing_html =
      "<!doctype html><link rel='stylesheet' href='asset://missing.css'>"
      "<div id='missing'></div>";
  status =
      blink_standalone_renderer_set_document_html(renderer, missing_html, "",
                                                  "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_smoke: missing set html failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 1.0 / 60.0);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.request_count <= requests_before_missing ||
      provider_state.not_found_count < 1 ||
      provider_state.release_count != provider_state.request_count) {
    std::fprintf(stderr,
                 "c_api_resource_provider_smoke: missing resource did not "
                 "fail recoverably status=%d requests=%d before=%d "
                 "not_found=%d releases=%d error=%s\n",
                 status, provider_state.request_count, requests_before_missing,
                 provider_state.not_found_count, provider_state.release_count,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_resource_provider_smoke: ok requests=%d images=%d "
      "stylesheets=%d link=%d import=%d css_bg=%d not_found=%d "
      "releases=%d red=%zu green=%zu fallback=disabled\n",
      provider_state.request_count, provider_state.image_request_count,
      provider_state.stylesheet_request_count,
      provider_state.stylesheet_link_request_count,
      provider_state.css_import_request_count,
      provider_state.css_background_request_count,
      provider_state.not_found_count, provider_state.release_count,
      stats.resource_red_e84444, stats.resource_green_237a57);
  return 0;
}

struct CApiResourceProviderFontSmokeState {
  std::vector<uint8_t> font_bytes = {0x77, 0x4f, 0x46, 0x32, 0x00, 0x00,
                                     0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  std::string font_css =
      "@font-face{font-family:'ProviderFont';"
      "src:url('asset://provider-font.woff2') format('woff2');}"
      "body{margin:0;background:#112233;color:white}"
      "#font-text{font-family:'ProviderFont',serif;font-size:24px}";
  std::string blocked_font_css =
      "@font-face{font-family:'BlockedProviderFont';"
      "src:url('asset://blocked-font.woff2') format('woff2');}"
      "body{margin:0;background:#112233;color:white}"
      "#font-text{font-family:'BlockedProviderFont',serif;font-size:24px}";
  int request_count = 0;
  int stylesheet_request_count = 0;
  int font_request_count = 0;
  int font_face_initiator_count = 0;
  int font_success_count = 0;
  int font_blocked_count = 0;
  int release_count = 0;
  bool block_fonts = false;
};

blink_standalone_resource_status_t CApiResourceProviderFontSmokeLoad(
    void* user_data,
    const blink_standalone_resource_request_t* request,
    blink_standalone_resource_response_t* response) {
  auto* state = static_cast<CApiResourceProviderFontSmokeState*>(user_data);
  if (!state || !request || !response || !request->url) {
    return BLINK_STANDALONE_RESOURCE_STATUS_ERROR;
  }
  ++state->request_count;
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_STYLESHEET) {
    ++state->stylesheet_request_count;
  }
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_FONT) {
    ++state->font_request_count;
  }
  if (request->initiator == BLINK_STANDALONE_RESOURCE_INITIATOR_FONT_FACE) {
    ++state->font_face_initiator_count;
  }

  const std::string url = request->url;
  if (url.find("font-theme.css") != std::string::npos) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes = reinterpret_cast<const uint8_t*>(state->font_css.data());
    response->byte_count = state->font_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  if (url.find("font-blocked.css") != std::string::npos) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes =
        reinterpret_cast<const uint8_t*>(state->blocked_font_css.data());
    response->byte_count = state->blocked_font_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  if (url.find("provider-font.woff2") != std::string::npos ||
      url.find("blocked-font.woff2") != std::string::npos) {
    if (state->block_fonts ||
        url.find("blocked-font.woff2") != std::string::npos) {
      ++state->font_blocked_count;
      response->status = BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED;
      return BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED;
    }
    ++state->font_success_count;
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "font/woff2";
    response->bytes = state->font_bytes.data();
    response->byte_count = state->font_bytes.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  response->status = BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
  return BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
}

void CApiResourceProviderFontSmokeRelease(
    void* user_data,
    blink_standalone_resource_response_t*) {
  auto* state = static_cast<CApiResourceProviderFontSmokeState*>(user_data);
  if (state) {
    ++state->release_count;
  }
}

int RunCApiResourceProviderFontSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 220;
  config.height = 100;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_resource_provider_font_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }

  CApiResourceProviderFontSmokeState provider_state;
  status = blink_standalone_renderer_set_resource_provider(
      renderer, CApiResourceProviderFontSmokeLoad,
      CApiResourceProviderFontSmokeRelease, &provider_state,
      BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_font_smoke: provider set failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const char* html =
      "<!doctype html><link rel='stylesheet' href='asset://font-theme.css'>"
      "<div id='font-text'>Provider Font Route</div>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 0.0)
               : status;
  const char* advance_error = blink_standalone_renderer_last_error(renderer);
  blink_standalone_frame_output_t output = {};
  blink_standalone_status_code_t output_status =
      blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.stylesheet_request_count < 1 ||
      provider_state.font_request_count < 1 ||
      provider_state.font_face_initiator_count < 1 ||
      provider_state.font_success_count < 1 ||
      provider_state.font_blocked_count != 0 ||
      provider_state.release_count != provider_state.request_count) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_font_smoke: font route failed status=%d "
        "output_status=%d requests=%d stylesheets=%d fonts=%d font_face=%d "
        "font_ok=%d blocked=%d releases=%d advance_error=%s error=%s\n",
        status, output_status, provider_state.request_count,
        provider_state.stylesheet_request_count,
        provider_state.font_request_count,
        provider_state.font_face_initiator_count,
        provider_state.font_success_count, provider_state.font_blocked_count,
        provider_state.release_count, advance_error ? advance_error : "",
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  const int requests_before_blocked = provider_state.request_count;
  const int blocked_before = provider_state.font_blocked_count;
  const char* blocked_html =
      "<!doctype html><link rel='stylesheet' href='asset://font-blocked.css'>"
      "<div id='font-text'>Blocked Font Route</div>";
  status =
      blink_standalone_renderer_set_document_html(renderer, blocked_html, "",
                                                  "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 1.0 / 60.0)
               : status;
  output = {};
  output_status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.request_count <= requests_before_blocked ||
      provider_state.font_blocked_count <= blocked_before ||
      provider_state.release_count != provider_state.request_count) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_font_smoke: blocked font did not fail "
        "recoverably status=%d output_status=%d requests=%d before=%d "
        "blocked=%d before_blocked=%d releases=%d error=%s\n",
        status, output_status, provider_state.request_count,
        requests_before_blocked, provider_state.font_blocked_count,
        blocked_before, provider_state.release_count,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_resource_provider_font_smoke: ok requests=%d stylesheets=%d "
      "fonts=%d font_face=%d font_ok=%d blocked=%d releases=%d "
      "decode=unsupported\n",
      provider_state.request_count, provider_state.stylesheet_request_count,
      provider_state.font_request_count,
      provider_state.font_face_initiator_count,
      provider_state.font_success_count, provider_state.font_blocked_count,
      provider_state.release_count);
  return 0;
}

struct CApiResourceProviderDataUrlSmokeState {
  std::vector<uint8_t> green_bmp = MakeSolidBmp(4, 4, 0x23, 0x7a, 0x57);
  std::vector<uint8_t> red_img_bmp = MakeSolidBmp(5, 5, 0xe8, 0x44, 0x44);
  std::vector<uint8_t> red_bg_bmp = MakeSolidBmp(4, 4, 0xe8, 0x44, 0x44);
  std::string img_data_url = MakeBmpDataUrl(red_img_bmp);
  std::string bg_data_url = MakeBmpDataUrl(red_bg_bmp);
  std::string theme_css =
      "body{margin:0;background:#112233}"
      "#data-img{position:absolute;left:0;top:0;width:60px;height:60px}"
      "#data-bg{position:absolute;left:80px;top:0;width:60px;height:60px;"
      "background-image:url('" +
      bg_data_url + "');background-size:60px 60px}";
  int request_count = 0;
  int data_url_request_count = 0;
  int data_url_img_request_count = 0;
  int data_url_css_background_request_count = 0;
  int stylesheet_request_count = 0;
  int blocked_count = 0;
  int release_count = 0;
  bool block_data_urls = false;
};

blink_standalone_resource_status_t CApiResourceProviderDataUrlSmokeLoad(
    void* user_data,
    const blink_standalone_resource_request_t* request,
    blink_standalone_resource_response_t* response) {
  auto* state =
      static_cast<CApiResourceProviderDataUrlSmokeState*>(user_data);
  if (!state || !request || !response || !request->url) {
    return BLINK_STANDALONE_RESOURCE_STATUS_ERROR;
  }
  ++state->request_count;
  const std::string url = request->url;
  if (url.find("data-theme.css") != std::string::npos) {
    ++state->stylesheet_request_count;
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes = reinterpret_cast<const uint8_t*>(state->theme_css.data());
    response->byte_count = state->theme_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  if (url.rfind("data:", 0) == 0) {
    ++state->data_url_request_count;
    if (request->initiator == BLINK_STANDALONE_RESOURCE_INITIATOR_IMG_ELEMENT) {
      ++state->data_url_img_request_count;
    }
    if (request->initiator ==
        BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_BACKGROUND_IMAGE) {
      ++state->data_url_css_background_request_count;
    }
    if (state->block_data_urls) {
      ++state->blocked_count;
      response->status = BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED;
      return BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED;
    }
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "image/bmp";
    response->bytes = state->green_bmp.data();
    response->byte_count = state->green_bmp.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  response->status = BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
  return BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
}

void CApiResourceProviderDataUrlSmokeRelease(
    void* user_data,
    blink_standalone_resource_response_t*) {
  auto* state =
      static_cast<CApiResourceProviderDataUrlSmokeState*>(user_data);
  if (state) {
    ++state->release_count;
  }
}

int RunCApiResourceProviderDataUrlSmoke() {
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
                 "c_api_resource_provider_data_url_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }

  CApiResourceProviderDataUrlSmokeState provider_state;
  const std::string html_base =
      "<!doctype html><link rel='stylesheet' href='asset://data-theme.css'>"
      "<img id='data-img' src='" +
      provider_state.img_data_url + "'><div id='data-bg'></div>";
  const std::string html_default = html_base + "<!--default-data-url-->";
  const std::string html_callback = html_base + "<!--callback-data-url-->";
  const std::string html_blocked = html_base + "<!--blocked-data-url-->";

  status = blink_standalone_renderer_set_resource_provider(
      renderer, CApiResourceProviderDataUrlSmokeLoad,
      CApiResourceProviderDataUrlSmokeRelease, &provider_state,
      BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_data_url_smoke: provider set "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_set_document_html(
      renderer, html_default.c_str(), "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_data_url_smoke: set html failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  blink_standalone_frame_output_t output = {};
  blink_standalone_status_code_t output_status =
      blink_standalone_renderer_get_latest_output(renderer, &output);
  FramePixelContentStats stats = AnalyzeFramePixelContent(output);
  const int default_requests = provider_state.request_count;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.stylesheet_request_count < 1 ||
      provider_state.data_url_request_count != 0 ||
      stats.resource_red_e84444 < 6000 ||
      stats.resource_green_237a57 != 0) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_data_url_smoke: default data URL failed "
        "status=%d output_status=%d requests=%d stylesheets=%d data=%d "
        "red=%zu green=%zu error=%s\n",
        status, output_status, provider_state.request_count,
        provider_state.stylesheet_request_count,
        provider_state.data_url_request_count, stats.resource_red_e84444,
        stats.resource_green_237a57,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_set_resource_provider(
      renderer, CApiResourceProviderDataUrlSmokeLoad,
      CApiResourceProviderDataUrlSmokeRelease, &provider_state,
      BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL |
          BLINK_STANDALONE_RESOURCE_PROVIDER_CALLBACK_FOR_DATA_URLS);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_data_url_smoke: callback-for-data "
                 "provider set failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const int data_before_callback = provider_state.data_url_request_count;
  const int img_before_callback = provider_state.data_url_img_request_count;
  const int css_bg_before_callback =
      provider_state.data_url_css_background_request_count;
  const int blocked_before_callback = provider_state.blocked_count;
  status = blink_standalone_renderer_set_document_html(
      renderer, html_callback.c_str(), "", "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 1.0 / 60.0)
               : status;
  output = {};
  output_status = blink_standalone_renderer_get_latest_output(renderer, &output);
  stats = AnalyzeFramePixelContent(output);
  const int callback_data_requests =
      provider_state.data_url_request_count - data_before_callback;
  const int callback_img_requests =
      provider_state.data_url_img_request_count - img_before_callback;
  const int callback_css_bg_requests =
      provider_state.data_url_css_background_request_count -
      css_bg_before_callback;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      callback_data_requests < 2 ||
      callback_img_requests < 1 ||
      callback_css_bg_requests < 1 ||
      provider_state.blocked_count != blocked_before_callback ||
      stats.resource_green_237a57 < 6000 ||
      stats.resource_red_e84444 != 0) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_data_url_smoke: callback data URL failed "
        "status=%d output_status=%d data=%d img=%d css_bg=%d red=%zu "
        "green=%zu error=%s\n",
        status, output_status, callback_data_requests, callback_img_requests,
        callback_css_bg_requests,
        stats.resource_red_e84444, stats.resource_green_237a57,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  provider_state.block_data_urls = true;
  const int blocked_before = provider_state.blocked_count;
  status = blink_standalone_renderer_set_document_html(
      renderer, html_blocked.c_str(), "", "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 2.0 / 60.0)
               : status;
  output = {};
  output_status = blink_standalone_renderer_get_latest_output(renderer, &output);
  stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.blocked_count < blocked_before + 2 ||
      stats.resource_red_e84444 != 0 ||
      stats.resource_green_237a57 != 0) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_data_url_smoke: blocked data URL failed "
        "status=%d output_status=%d blocked=%d before=%d red=%zu green=%zu "
        "error=%s\n",
        status, output_status, provider_state.blocked_count, blocked_before,
        stats.resource_red_e84444, stats.resource_green_237a57,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_resource_provider_data_url_smoke: ok default_requests=%d "
      "data_requests=%d img=%d css_bg=%d blocked=%d releases=%d "
      "default=internal callback=replaced blocked=no_fallback\n",
      default_requests, provider_state.data_url_request_count,
      provider_state.data_url_img_request_count,
      provider_state.data_url_css_background_request_count,
      provider_state.blocked_count, provider_state.release_count);
  return 0;
}

struct CApiResourceProviderMaskSvgSmokeState {
  std::vector<uint8_t> white_mask_bmp = MakeSolidBmp(4, 4, 0xff, 0xff, 0xff);
  std::string svg_icon =
      "<svg xmlns='http://www.w3.org/2000/svg' width='32' height='32'>"
      "<rect width='32' height='32' fill='rgb(208,99,41)'/>"
      "</svg>";
  int request_count = 0;
  int image_request_count = 0;
  int img_element_request_count = 0;
  int css_image_request_count = 0;
  int mask_request_count = 0;
  int svg_request_count = 0;
  int blocked_count = 0;
  int release_count = 0;
};

blink_standalone_resource_status_t CApiResourceProviderMaskSvgSmokeLoad(
    void* user_data,
    const blink_standalone_resource_request_t* request,
    blink_standalone_resource_response_t* response) {
  auto* state =
      static_cast<CApiResourceProviderMaskSvgSmokeState*>(user_data);
  if (!state || !request || !response || !request->url) {
    return BLINK_STANDALONE_RESOURCE_STATUS_ERROR;
  }
  ++state->request_count;
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_IMAGE) {
    ++state->image_request_count;
  }
  if (request->initiator == BLINK_STANDALONE_RESOURCE_INITIATOR_IMG_ELEMENT) {
    ++state->img_element_request_count;
  }
  if (request->initiator ==
      BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_BACKGROUND_IMAGE) {
    ++state->css_image_request_count;
  }

  const std::string url = request->url;
  if (url.find("blocked") != std::string::npos) {
    ++state->blocked_count;
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED;
    return BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED;
  }
  if (url.find("mask.bmp") != std::string::npos) {
    ++state->mask_request_count;
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "image/bmp";
    response->bytes = state->white_mask_bmp.data();
    response->byte_count = state->white_mask_bmp.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  if (url.find("icon.svg") != std::string::npos) {
    ++state->svg_request_count;
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "image/svg+xml";
    response->bytes = reinterpret_cast<const uint8_t*>(state->svg_icon.data());
    response->byte_count = state->svg_icon.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  response->status = BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
  return BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
}

void CApiResourceProviderMaskSvgSmokeRelease(
    void* user_data,
    blink_standalone_resource_response_t*) {
  auto* state =
      static_cast<CApiResourceProviderMaskSvgSmokeState*>(user_data);
  if (state) {
    ++state->release_count;
  }
}

int RunCApiResourceProviderMaskSvgSmoke() {
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
                 "c_api_resource_provider_mask_svg_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }

  CApiResourceProviderMaskSvgSmokeState provider_state;
  status = blink_standalone_renderer_set_resource_provider(
      renderer, CApiResourceProviderMaskSvgSmokeLoad,
      CApiResourceProviderMaskSvgSmokeRelease, &provider_state,
      BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_mask_svg_smoke: provider set "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;background:#112233}"
      "#masked{position:absolute;left:0;top:0;width:60px;height:60px;"
      "background:#237a57;-webkit-mask-image:url('asset://mask.bmp');"
      "-webkit-mask-size:60px 60px;mask-image:url('asset://mask.bmp');"
      "mask-size:60px 60px}"
      "#svg-img{position:absolute;left:80px;top:0;width:40px;height:40px}"
      "</style><div id='masked'></div>"
      "<img id='svg-img' src='asset://icon.svg'>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 0.0)
               : status;
  blink_standalone_frame_output_t output = {};
  blink_standalone_status_code_t output_status =
      blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK) {
    blink_standalone_renderer_release_latest_output(renderer);
    status = blink_standalone_renderer_advance_frame(renderer, 1.0 / 60.0);
    output = {};
    output_status = blink_standalone_renderer_get_latest_output(renderer,
                                                                &output);
  }
  const FramePixelContentStats stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.request_count < 2 ||
      provider_state.image_request_count < 2 ||
      provider_state.mask_request_count < 1 ||
      provider_state.svg_request_count < 1 ||
      provider_state.css_image_request_count < 1 ||
      provider_state.img_element_request_count < 1 ||
      provider_state.release_count != provider_state.request_count ||
      stats.nontransparent < 1000) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_mask_svg_smoke: route failed status=%d "
        "output_status=%d requests=%d images=%d img=%d css_image=%d "
        "mask=%d svg=%d releases=%d nontransparent=%zu error=%s\n",
        status, output_status, provider_state.request_count,
        provider_state.image_request_count,
        provider_state.img_element_request_count,
        provider_state.css_image_request_count, provider_state.mask_request_count,
        provider_state.svg_request_count, provider_state.release_count,
        stats.nontransparent, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  const int blocked_before = provider_state.blocked_count;
  const int requests_before_blocked = provider_state.request_count;
  const char* blocked_html =
      "<!doctype html><style>body{margin:0;background:#112233}"
      "#masked{position:absolute;left:0;top:0;width:60px;height:60px;"
      "background:#237a57;-webkit-mask-image:url('asset://blocked-mask.bmp');"
      "-webkit-mask-size:60px 60px}"
      "#svg-img{position:absolute;left:80px;top:0;width:40px;height:40px}"
      "</style><div id='masked'></div>"
      "<img id='svg-img' src='asset://blocked-icon.svg'>";
  status =
      blink_standalone_renderer_set_document_html(renderer, blocked_html, "",
                                                  "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 1.0 / 60.0)
               : status;
  output = {};
  output_status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      output_status != BLINK_STANDALONE_STATUS_OK ||
      provider_state.request_count <= requests_before_blocked ||
      provider_state.blocked_count < blocked_before + 2 ||
      provider_state.release_count != provider_state.request_count) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_mask_svg_smoke: blocked resources did not "
        "fail recoverably status=%d output_status=%d requests=%d before=%d "
        "blocked=%d before_blocked=%d releases=%d error=%s\n",
        status, output_status, provider_state.request_count,
        requests_before_blocked, provider_state.blocked_count, blocked_before,
        provider_state.release_count,
        blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_resource_provider_mask_svg_smoke: ok requests=%d images=%d "
      "img=%d css_image=%d mask=%d svg=%d blocked=%d releases=%d "
      "svg_nested_external=unsupported\n",
      provider_state.request_count, provider_state.image_request_count,
      provider_state.img_element_request_count,
      provider_state.css_image_request_count, provider_state.mask_request_count,
      provider_state.svg_request_count, provider_state.blocked_count,
      provider_state.release_count);
  return 0;
}

struct CApiResourceProviderFreeThenMaskSmokeState {
  std::vector<uint8_t> red_bmp = MakeSolidBmp(2, 2, 0xe8, 0x44, 0x44);
  std::vector<uint8_t> white_mask_bmp = MakeSolidBmp(2, 2, 0xff, 0xff, 0xff);
  std::string theme_css =
      "@import url('asset://imported.css');"
      "body{margin:0;background:#112233}"
      "#linked{position:absolute;left:50px;top:0;width:40px;height:40px;"
      "background:#e84444}";
  std::string imported_css =
      "#image{position:absolute;left:0;top:0;width:40px;height:40px;"
      "background-image:url('asset://red_2x2.bmp');"
      "background-size:40px 40px}";
  int request_count = 0;
  int image_request_count = 0;
  int stylesheet_request_count = 0;
  int stylesheet_link_request_count = 0;
  int css_import_request_count = 0;
  int css_image_request_count = 0;
  int red_request_count = 0;
  int mask_request_count = 0;
  int release_count = 0;
};

blink_standalone_resource_status_t CApiResourceProviderFreeThenMaskSmokeLoad(
    void* user_data,
    const blink_standalone_resource_request_t* request,
    blink_standalone_resource_response_t* response) {
  auto* state =
      static_cast<CApiResourceProviderFreeThenMaskSmokeState*>(user_data);
  if (!state || !request || !response || !request->url) {
    return BLINK_STANDALONE_RESOURCE_STATUS_ERROR;
  }
  ++state->request_count;
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_IMAGE) {
    ++state->image_request_count;
  }
  if (request->type_hint == BLINK_STANDALONE_RESOURCE_TYPE_STYLESHEET) {
    ++state->stylesheet_request_count;
  }
  if (request->initiator ==
      BLINK_STANDALONE_RESOURCE_INITIATOR_STYLESHEET_LINK) {
    ++state->stylesheet_link_request_count;
  }
  if (request->initiator == BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_IMPORT) {
    ++state->css_import_request_count;
  }
  if (request->initiator ==
      BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_BACKGROUND_IMAGE) {
    ++state->css_image_request_count;
  }

  const std::string url = request->url;
  if (url.find("theme.css") != std::string::npos) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes = reinterpret_cast<const uint8_t*>(state->theme_css.data());
    response->byte_count = state->theme_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  if (url.find("imported.css") != std::string::npos) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    response->mime_type = "text/css";
    response->bytes =
        reinterpret_cast<const uint8_t*>(state->imported_css.data());
    response->byte_count = state->imported_css.size();
    response->resolved_url_or_cache_key = request->url;
    return BLINK_STANDALONE_RESOURCE_STATUS_OK;
  }
  const std::vector<uint8_t>* bytes = nullptr;
  if (url.find("red_2x2.bmp") != std::string::npos) {
    ++state->red_request_count;
    bytes = &state->red_bmp;
  } else if (url.find("mask_2x2.bmp") != std::string::npos) {
    ++state->mask_request_count;
    bytes = &state->white_mask_bmp;
  }
  if (!bytes) {
    response->status = BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
    return BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND;
  }
  response->status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
  response->mime_type = "image/bmp";
  response->bytes = bytes->data();
  response->byte_count = bytes->size();
  response->resolved_url_or_cache_key = request->url;
  return BLINK_STANDALONE_RESOURCE_STATUS_OK;
}

void CApiResourceProviderFreeThenMaskSmokeRelease(
    void* user_data,
    blink_standalone_resource_response_t*) {
  auto* state =
      static_cast<CApiResourceProviderFreeThenMaskSmokeState*>(user_data);
  if (state) {
    ++state->release_count;
  }
}

bool RenderProviderDocumentForFreeThenMaskSmoke(
    CApiResourceProviderFreeThenMaskSmokeState* provider_state,
    const char* html,
    const char* label,
    size_t* red_pixels_out) {
  blink_standalone_renderer_config_t config = {};
  config.width = 120;
  config.height = 80;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_resource_provider_free_then_mask_smoke: %s create "
                 "failed status=%d\n",
                 label, status);
    return false;
  }
  status = blink_standalone_renderer_set_resource_provider(
      renderer, CApiResourceProviderFreeThenMaskSmokeLoad,
      CApiResourceProviderFreeThenMaskSmokeRelease, provider_state,
      BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK |
          BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_resource_provider_free_then_mask_smoke: %s provider "
                 "set failed status=%d error=%s\n",
                 label, status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return false;
  }
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer, 0.0)
               : status;
  blink_standalone_frame_output_t output = {};
  blink_standalone_status_code_t output_status =
      blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats stats = AnalyzeFramePixelContent(output);
  if (red_pixels_out) {
    *red_pixels_out = stats.resource_red_e84444;
  }
  const bool ok = status == BLINK_STANDALONE_STATUS_OK &&
                  output_status == BLINK_STANDALONE_STATUS_OK &&
                  stats.resource_red_e84444 >= 1200;
  if (!ok) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_free_then_mask_smoke: %s render failed "
        "status=%d output_status=%d red=%zu error=%s\n",
        label, status, output_status, stats.resource_red_e84444,
        blink_standalone_renderer_last_error(renderer));
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  return ok;
}

int RunCApiResourceProviderFreeThenMaskSmoke() {
  CApiResourceProviderFreeThenMaskSmokeState provider_state;
  const char* linked_html =
      "<!doctype html><link rel='stylesheet' href='asset://theme.css'>"
      "<div id='linked'></div><div id='image'></div>";
  size_t linked_red = 0;
  if (!RenderProviderDocumentForFreeThenMaskSmoke(
          &provider_state, linked_html, "linked", &linked_red)) {
    return 1;
  }

  const int requests_after_linked = provider_state.request_count;
  const int releases_after_linked = provider_state.release_count;
  const char* mask_html =
      "<!doctype html><style>body{margin:0;background:#112233}"
      "#masked{position:absolute;left:0;top:0;width:40px;height:40px;"
      "background:#e84444;-webkit-mask-image:url('asset://mask_2x2.bmp');"
      "mask-image:url('asset://mask_2x2.bmp');"
      "-webkit-mask-size:40px 40px;mask-size:40px 40px}</style>"
      "<div id='masked'></div>";
  size_t mask_red = 0;
  if (!RenderProviderDocumentForFreeThenMaskSmoke(
          &provider_state, mask_html, "mask", &mask_red)) {
    return 1;
  }

  if (provider_state.stylesheet_link_request_count < 1 ||
      provider_state.css_import_request_count < 1 ||
      provider_state.red_request_count < 1 ||
      provider_state.mask_request_count < 1 ||
      provider_state.release_count != provider_state.request_count ||
      provider_state.request_count <= requests_after_linked ||
      releases_after_linked <= 0) {
    std::fprintf(
        stderr,
        "c_api_resource_provider_free_then_mask_smoke: provider counts failed "
        "requests=%d after_linked=%d images=%d stylesheets=%d link=%d "
        "import=%d css_image=%d red_req=%d mask_req=%d releases=%d "
        "after_linked_releases=%d linked_red=%zu mask_red=%zu\n",
        provider_state.request_count, requests_after_linked,
        provider_state.image_request_count,
        provider_state.stylesheet_request_count,
        provider_state.stylesheet_link_request_count,
        provider_state.css_import_request_count,
        provider_state.css_image_request_count, provider_state.red_request_count,
        provider_state.mask_request_count, provider_state.release_count,
        releases_after_linked, linked_red, mask_red);
    return 1;
  }

  std::printf(
      "c_api_resource_provider_free_then_mask_smoke: ok linked_red=%zu "
      "mask_red=%zu requests=%d images=%d stylesheets=%d link=%d import=%d "
      "css_image=%d red_req=%d mask_req=%d releases=%d\n",
      linked_red, mask_red, provider_state.request_count,
      provider_state.image_request_count, provider_state.stylesheet_request_count,
      provider_state.stylesheet_link_request_count,
      provider_state.css_import_request_count,
      provider_state.css_image_request_count, provider_state.red_request_count,
      provider_state.mask_request_count, provider_state.release_count);
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

size_t CountPixelsInRectNearColor(const blink_standalone_frame_output_t& output,
                                  int left,
                                  int top,
                                  int width,
                                  int height,
                                  uint8_t expected_red,
                                  uint8_t expected_green,
                                  uint8_t expected_blue,
                                  int tolerance) {
  if (!output.pixels || output.width <= 0 || output.height <= 0 ||
      output.stride < output.width * 4 ||
      (output.pixel_format != BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 &&
       output.pixel_format != BLINK_STANDALONE_PIXEL_FORMAT_BGRA8)) {
    return 0;
  }
  const int x0 = std::max(0, left);
  const int y0 = std::max(0, top);
  const int x1 = std::min(output.width, left + width);
  const int y1 = std::min(output.height, top + height);
  size_t count = 0;
  for (int y = y0; y < y1; ++y) {
    const uint8_t* row =
        output.pixels + static_cast<size_t>(y) * output.stride;
    for (int x = x0; x < x1; ++x) {
      const uint8_t* pixel = row + static_cast<size_t>(x) * 4;
      const uint8_t red =
          output.pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 ? pixel[0]
                                                                     : pixel[2];
      const uint8_t green = pixel[1];
      const uint8_t blue =
          output.pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 ? pixel[2]
                                                                     : pixel[0];
      const auto near_channel = [tolerance](uint8_t actual, uint8_t expected) {
        const int delta = static_cast<int>(actual) - static_cast<int>(expected);
        return delta >= -tolerance && delta <= tolerance;
      };
      if (near_channel(red, expected_red) &&
          near_channel(green, expected_green) &&
          near_channel(blue, expected_blue)) {
        ++count;
      }
    }
  }
  return count;
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

std::string FormStateCString(const char* value) {
  return value ? value : "";
}

std::vector<std::string> SelectedValuesForSmoke(
    blink_standalone_renderer_t* renderer,
    const char* element_id) {
  std::vector<std::string> values;
  const size_t count =
      blink_standalone_renderer_form_control_selected_value_count(renderer,
                                                                  element_id);
  for (size_t i = 0; i < count; ++i) {
    const char* value = nullptr;
    if (blink_standalone_renderer_get_form_control_selected_value(
            renderer, element_id, i, &value) == BLINK_STANDALONE_STATUS_OK) {
      values.push_back(value ? value : "");
    }
  }
  return values;
}

bool SelectedValuesEqual(const std::vector<std::string>& actual,
                         std::initializer_list<const char*> expected) {
  if (actual.size() != expected.size()) {
    return false;
  }
  size_t index = 0;
  for (const char* value : expected) {
    if (actual[index] != value) {
      return false;
    }
    ++index;
  }
  return true;
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

bool UpdateCApiFrameForSmoke(blink_standalone_renderer_t* renderer,
                             double time,
                             const char* label,
                             blink_standalone_update_result_t* result) {
  const blink_standalone_status_code_t status =
      blink_standalone_renderer_update(renderer, time, result);
  if (status == BLINK_STANDALONE_STATUS_OK) {
    return true;
  }
  std::fprintf(stderr, "%s: update failed status=%d error=%s\n", label, status,
               blink_standalone_renderer_last_error(renderer));
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

int RunCApiFrameSchedulingSmoke() {
  constexpr const char* kLabel = "c_api_frame_scheduling_smoke";
  blink_standalone_renderer_config_t config = {};
  config.width = 220;
  config.height = 150;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr, "%s: create failed status=%d\n", kLabel, status);
    return 1;
  }
  std::unique_ptr<blink_standalone_renderer_t,
                  decltype(&blink_standalone_renderer_destroy)>
      renderer_guard(renderer, blink_standalone_renderer_destroy);
  const char* html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#112233}"
      "#hot{position:absolute;left:80px;top:40px;width:80px;height:40px;"
      "background:#2878d8}"
      "#hot:hover{background:#d06329}"
      "#name{position:absolute;left:0;top:105px;width:120px;height:24px}"
      "</style><div id='hot'></div><input id='name' value='seed'>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: set html failed status=%d error=%s\n", kLabel,
                 status, blink_standalone_renderer_last_error(renderer));
    return 1;
  }
  double time = 0.016;
  if (!AdvanceCApiFrameForSmoke(renderer, time, kLabel)) {
    return 1;
  }
  time += 0.016;

  blink_standalone_update_result_t inert_first = {};
  blink_standalone_renderer_mouse_move(renderer, 10.0f, 10.0f, 0);
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &inert_first)) {
    return 1;
  }
  time += 0.016;

  blink_standalone_update_result_t inert_stable = {};
  blink_standalone_renderer_mouse_move(renderer, 12.0f, 12.0f, 0);
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &inert_stable)) {
    return 1;
  }
  if (inert_stable.needs_output != 0 ||
      inert_stable.frame_skipped_due_to_no_demand != 0) {
    std::fprintf(stderr,
                 "%s: stable inert mouse move demanded output=%u skipped=%u\n",
                 kLabel, inert_stable.needs_output,
                 inert_stable.frame_skipped_due_to_no_demand);
    return 1;
  }
  time += 0.016;

  blink_standalone_update_result_t hover_enter = {};
  blink_standalone_renderer_mouse_move(renderer, 90.0f, 50.0f, 0);
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &hover_enter)) {
    return 1;
  }
  if (hover_enter.needs_output == 0) {
    std::fprintf(stderr, "%s: hover transition did not demand output\n",
                 kLabel);
    return 1;
  }
  time += 0.016;

  blink_standalone_update_result_t hover_stable = {};
  blink_standalone_renderer_mouse_move(renderer, 94.0f, 54.0f, 0);
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &hover_stable)) {
    return 1;
  }
  if (hover_stable.needs_output != 0) {
    std::fprintf(stderr,
                 "%s: stable hover mouse move demanded output=%u\n", kLabel,
                 hover_stable.needs_output);
    return 1;
  }
  time += 0.016;

  blink_standalone_update_result_t mouse_down = {};
  blink_standalone_renderer_mouse_down(
      renderer, 90.0f, 50.0f, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &mouse_down)) {
    return 1;
  }
  if (mouse_down.needs_output == 0) {
    std::fprintf(stderr, "%s: mouse down did not demand output\n", kLabel);
    return 1;
  }
  time += 0.016;

  blink_standalone_update_result_t mouse_up = {};
  blink_standalone_renderer_mouse_up(
      renderer, 90.0f, 50.0f, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &mouse_up)) {
    return 1;
  }
  if (mouse_up.needs_output == 0) {
    std::fprintf(stderr, "%s: mouse up did not demand output\n", kLabel);
    return 1;
  }
  time += 0.016;

  status = blink_standalone_renderer_focus_element(renderer, "name");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: focus mutation failed status=%d error=%s\n",
                 kLabel, status, blink_standalone_renderer_last_error(renderer));
    return 1;
  }
  blink_standalone_update_result_t focus = {};
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &focus)) {
    return 1;
  }
  if (focus.needs_output == 0) {
    std::fprintf(stderr, "%s: focus mutation did not demand output\n", kLabel);
    return 1;
  }
  time += 0.016;

  status = blink_standalone_renderer_text_input(renderer, "Z");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: text input failed status=%d error=%s\n", kLabel,
                 status, blink_standalone_renderer_last_error(renderer));
    return 1;
  }
  blink_standalone_update_result_t text = {};
  if (!UpdateCApiFrameForSmoke(renderer, time, kLabel, &text)) {
    return 1;
  }
  if (text.needs_output == 0) {
    std::fprintf(stderr, "%s: text input did not demand output\n", kLabel);
    return 1;
  }

  std::printf(
      "%s: ok inert_first=%u inert_stable=%u hover_enter=%u hover_stable=%u "
      "down=%u up=%u focus=%u text=%u\n",
      kLabel, inert_first.needs_output, inert_stable.needs_output,
      hover_enter.needs_output, hover_stable.needs_output,
      mouse_down.needs_output, mouse_up.needs_output, focus.needs_output,
      text.needs_output);
  return 0;
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

int RunCApiStructuralDomMutationSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 360;
  config.height = 220;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style id='theme'>body{margin:0;font:16px monospace;"
      "background:#112233;color:white}"
      "#target{position:absolute;left:10px;top:10px;width:250px;height:74px}"
      ".tile{position:absolute;top:0;width:76px;height:44px;color:white}"
      "#old{left:0;background:#2878d8}"
      "#name{position:absolute;left:10px;top:104px;width:150px}"
      "label{position:absolute;left:10px;top:140px}</style>"
      "<div id='target'><div id='old' class='tile' "
      "data-godot-action='old'>Old</div></div>"
      "<input id='name' value='seed' data-godot-action='name'>"
      "<label><input id='agree' type='checkbox' "
      "data-godot-action='toggle'>Agree</label>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: set html failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.0;
  if (!AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_structural_dom_mutation_smoke")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats initial_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      initial_stats.blue_2878d8 < 2500 || !HasHitId(renderer, "old") ||
      !HasHitId(renderer, "target") || !HasHitId(renderer, "name") ||
      !HasHitId(renderer, "agree")) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: initial output invalid "
                 "status=%d blue=%zu old=%d target=%d name=%d agree=%d\n",
                 status, initial_stats.blue_2878d8,
                 HasHitId(renderer, "old") ? 1 : 0,
                 HasHitId(renderer, "target") ? 1 : 0,
                 HasHitId(renderer, "name") ? 1 : 0,
                 HasHitId(renderer, "agree") ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  if (blink_standalone_renderer_insert_element_html(
          renderer, "missing-target", BLINK_STANDALONE_INSERT_BEFORE_END,
          "<span>Missing</span>") != BLINK_STANDALONE_STATUS_INVALID_ARGUMENT ||
      blink_standalone_renderer_remove_element(renderer, "missing-target") !=
          BLINK_STANDALONE_STATUS_INVALID_ARGUMENT) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: missing target was "
                 "accepted\n");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (blink_standalone_renderer_insert_element_html(
          renderer, "target", BLINK_STANDALONE_INSERT_BEFORE_END,
          "<button onclick='alert(1)'>Bad</button>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_insert_element_html(
          renderer, "target", BLINK_STANDALONE_INSERT_BEFORE_END,
          "<a href='javascript:alert(1)'>Bad</a>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
      blink_standalone_renderer_insert_element_html(
          renderer, "target", BLINK_STANDALONE_INSERT_BEFORE_END,
          "<iframe src='about:blank'></iframe>") !=
          BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: no-script insert "
                 "rejection failed\n");
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
                                "c_api_structural_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: state setup failed "
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
                 "c_api_structural_dom_mutation_smoke: persisted state setup "
                 "invalid value=%s focused=%d checked=%d\n",
                 FormStateValue(name_state).c_str(), name_state.focused,
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_element_inner_html(
      renderer, "target",
      "<section id='panel' class='tile' data-godot-action='panel' "
      "style='left:0;background:#e84444'>Panel</section>");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_structural_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: inner html mutation "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats replaced_stats = AnalyzeFramePixelContent(output);
  blink_standalone_hit_metadata_t panel_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      replaced_stats.resource_red_e84444 < 2500 || HasHitId(renderer, "old") ||
      !GetHitById(renderer, "panel", &panel_hit) ||
      std::string(panel_hit.data_godot_action ? panel_hit.data_godot_action
                                              : "") != "panel" ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: replacement invalid "
                 "status=%d red=%zu old=%d panel=%d value=%s checked=%d "
                 "action=%s\n",
                 status, replaced_stats.resource_red_e84444,
                 HasHitId(renderer, "old") ? 1 : 0,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 FormStateValue(name_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0,
                 panel_hit.data_godot_action ? panel_hit.data_godot_action : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_insert_element_html(
      renderer, "panel", BLINK_STANDALONE_INSERT_AFTER_END,
      "<section id='inserted' class='tile' data-godot-action='inserted' "
      "style='left:90px;background:#d06329'>Inserted</section>");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_insert_element_html(
                     renderer, "panel", BLINK_STANDALONE_INSERT_BEFORE_END,
                     "<span id='innerchild' data-godot-action='innerchild' "
                     "style='display:block;position:absolute;left:4px;top:22px;"
                     "width:54px;height:18px;background:#237a57'>Child</span>")
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_structural_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: insert mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats inserted_stats = AnalyzeFramePixelContent(output);
  blink_standalone_hit_metadata_t inserted_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      inserted_stats.orange_d06329 < 2500 ||
      inserted_stats.resource_green_237a57 < 600 ||
      !GetHitById(renderer, "inserted", &inserted_hit) ||
      std::string(inserted_hit.data_godot_action
                      ? inserted_hit.data_godot_action
                      : "") != "inserted" ||
      !HasHitId(renderer, "innerchild") || !HasHitId(renderer, "panel") ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: insert not reflected "
                 "status=%d orange=%zu green=%zu inserted=%d inner=%d "
                 "panel=%d value=%s checked=%d action=%s\n",
                 status, inserted_stats.orange_d06329,
                 inserted_stats.resource_green_237a57,
                 HasHitId(renderer, "inserted") ? 1 : 0,
                 HasHitId(renderer, "innerchild") ? 1 : 0,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 FormStateValue(name_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0,
                 inserted_hit.data_godot_action ? inserted_hit.data_godot_action
                                                : "");
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_remove_element(renderer, "inserted");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_structural_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: remove mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  time += 0.016;
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  const FramePixelContentStats removed_stats = AnalyzeFramePixelContent(output);
  if (status != BLINK_STANDALONE_STATUS_OK || HasHitId(renderer, "inserted") ||
      !HasHitId(renderer, "panel") || !HasHitId(renderer, "innerchild") ||
      removed_stats.resource_red_e84444 < 2000 ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: removal invalid "
                 "status=%d inserted=%d panel=%d inner=%d red=%zu value=%s "
                 "checked=%d\n",
                 status, HasHitId(renderer, "inserted") ? 1 : 0,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 HasHitId(renderer, "innerchild") ? 1 : 0,
                 removed_stats.resource_red_e84444,
                 FormStateValue(name_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);

  status = blink_standalone_renderer_set_viewport(renderer, 360, 220, 2.0f);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_structural_dom_mutation_smoke")) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: resize failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || output.width != 720 ||
      output.height != 440 || !HasHitId(renderer, "panel") ||
      HasHitId(renderer, "inserted") ||
      !GetFormStateById(renderer, "name", &name_state) ||
      FormStateValue(name_state) != "persisted" ||
      !HitCheckedStateIs(renderer, "agree", true)) {
    std::fprintf(stderr,
                 "c_api_structural_dom_mutation_smoke: resize/state invalid "
                 "status=%d raw=%dx%d panel=%d inserted=%d value=%s "
                 "checked=%d\n",
                 status, output.width, output.height,
                 HasHitId(renderer, "panel") ? 1 : 0,
                 HasHitId(renderer, "inserted") ? 1 : 0,
                 FormStateValue(name_state).c_str(),
                 HitCheckedStateIs(renderer, "agree", true) ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_structural_dom_mutation_smoke: ok blue=%zu red=%zu orange=%zu "
      "green=%zu raw=%dx%d state=persisted\n",
      initial_stats.blue_2878d8, replaced_stats.resource_red_e84444,
      inserted_stats.orange_d06329, inserted_stats.resource_green_237a57,
      output.width, output.height);
  return 0;
}

int RunCApiMutationDiagnosticsSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 260;
  config.height = 160;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_mutation_diagnostics_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;font:16px monospace;background:#112233}"
      "#target{position:absolute;left:8px;top:8px;width:110px;height:42px;"
      "background:#2878d8;color:white}"
      "#box{position:absolute;left:130px;top:8px;width:80px;height:42px;"
      "background:#d06329;color:white}"
      "#name{position:absolute;left:8px;top:70px;width:150px}</style>"
      "<div id='target' data-godot-action='target'>Target</div>"
      "<div id='box'>Box</div>"
      "<input id='name' value='seed'>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, 0.0,
                                "c_api_mutation_diagnostics_smoke")) {
    std::fprintf(stderr,
                 "c_api_mutation_diagnostics_smoke: initial render failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  const auto expect_error = [&](blink_standalone_status_code_t actual,
                                blink_standalone_status_code_t expected,
                                const char* required_a,
                                const char* required_b) -> bool {
    const std::string message =
        blink_standalone_renderer_get_last_error_message(renderer);
    const blink_standalone_status_code_t code =
        blink_standalone_renderer_get_last_error_code(renderer);
    const bool ok = actual == expected && code == expected &&
                    message.find(required_a) != std::string::npos &&
                    (!required_b ||
                     message.find(required_b) != std::string::npos);
    if (!ok) {
      std::fprintf(stderr,
                   "c_api_mutation_diagnostics_smoke: expected error "
                   "status=%d code=%d contains='%s'/'%s' actual_status=%d "
                   "actual_code=%d message=%s\n",
                   expected, expected, required_a,
                   required_b ? required_b : "", actual, code,
                   message.c_str());
    }
    return ok;
  };

  if (!expect_error(blink_standalone_renderer_set_element_text(
                        renderer, "missing-text", "Text"),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "set_element_text", "missing-text") ||
      !expect_error(blink_standalone_renderer_set_element_style(
                        renderer, "missing-style", "color:red"),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "set_element_style", "missing-style") ||
      !expect_error(blink_standalone_renderer_remove_element(
                        renderer, "missing-remove"),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "remove_element", "missing-remove") ||
      !expect_error(blink_standalone_renderer_insert_element_html(
                        renderer, "missing-insert",
                        BLINK_STANDALONE_INSERT_BEFORE_END,
                        "<span>Missing</span>"),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "insert_element_html", "missing-insert")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (!expect_error(blink_standalone_renderer_insert_element_html(
                        renderer, "target",
                        static_cast<blink_standalone_insert_position_t>(99),
                        "<span>Bad</span>"),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "insert_element_html", "insert position is invalid")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (!expect_error(blink_standalone_renderer_set_element_inner_html(
                        renderer, "target", "<script>alert(1)</script>"),
                    BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED,
                    "set_element_inner_html", "script tag") ||
      !expect_error(blink_standalone_renderer_set_body_inner_html(
                        renderer, "<button onclick='alert(1)'>Bad</button>"),
                    BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED,
                    "set_body_inner_html", "inline event handler") ||
      !expect_error(blink_standalone_renderer_insert_element_html(
                        renderer, "target",
                        BLINK_STANDALONE_INSERT_BEFORE_END,
                        "<a href=' javascript:alert(1)'>Bad</a>"),
                    BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED,
                    "insert_element_html", "javascript URL")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  if (!expect_error(blink_standalone_renderer_set_form_control_value(
                        renderer, "box", "not-a-form"),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "set_form_control_value", "not a supported form control") ||
      !expect_error(blink_standalone_renderer_set_form_control_checked(
                        renderer, "name", 1),
                    BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                    "set_form_control_checked", "not a checkbox or radio")) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  status = blink_standalone_renderer_set_element_text(renderer, "target",
                                                      "Updated");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      blink_standalone_renderer_get_last_error_code(renderer) !=
          BLINK_STANDALONE_STATUS_OK ||
      std::strlen(blink_standalone_renderer_get_last_error_message(renderer)) !=
          0 ||
      !AdvanceCApiFrameForSmoke(renderer, 0.016,
                                "c_api_mutation_diagnostics_smoke")) {
    std::fprintf(stderr,
                 "c_api_mutation_diagnostics_smoke: successful mutation did "
                 "not clear diagnostics status=%d code=%d message=%s\n",
                 status, blink_standalone_renderer_get_last_error_code(renderer),
                 blink_standalone_renderer_get_last_error_message(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || !HasHitId(renderer, "target") ||
      !HasHitId(renderer, "box") || output.width != 260 ||
      output.height != 160) {
    std::fprintf(stderr,
                 "c_api_mutation_diagnostics_smoke: output invalid after "
                 "failed mutations status=%d raw=%dx%d target=%d box=%d "
                 "error=%s\n",
                 status, output.width, output.height,
                 HasHitId(renderer, "target") ? 1 : 0,
                 HasHitId(renderer, "box") ? 1 : 0,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_mutation_diagnostics_smoke: ok missing/unsafe/unsupported "
      "diagnostics covered raw=%dx%d\n",
      output.width, output.height);
  return 0;
}

int RunCApiMutationStressSmoke() {
  constexpr int kIterations = 40;
  blink_standalone_renderer_config_t config_a = {};
  config_a.width = 320;
  config_a.height = 180;
  config_a.device_scale_factor = 1.0f;
  config_a.no_script_profile = 1;
  blink_standalone_renderer_config_t config_b = {};
  config_b.width = 180;
  config_b.height = 100;
  config_b.device_scale_factor = 1.0f;
  config_b.no_script_profile = 1;
  blink_standalone_renderer_t* renderer_a = nullptr;
  blink_standalone_renderer_t* renderer_b = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config_a, &renderer_a);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer_a) {
    std::fprintf(stderr,
                 "c_api_mutation_stress_smoke: create A failed status=%d\n",
                 status);
    return 1;
  }
  status = blink_standalone_renderer_create(&config_b, &renderer_b);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer_b) {
    std::fprintf(stderr,
                 "c_api_mutation_stress_smoke: create B failed status=%d\n",
                 status);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  const char* html_a =
      "<!doctype html><html><head><style id='theme'>"
      "html,body{margin:0;padding:0;background:#112233;font:15px monospace}"
      "#target{position:absolute;left:8px;top:8px;width:112px;height:42px;"
      "background:#2878d8;color:white}"
      "#slot{position:absolute;left:128px;top:8px;width:150px;height:54px}"
      "#name{position:absolute;left:8px;top:72px;width:120px}"
      "#range{position:absolute;left:8px;top:104px;width:120px}"
      "#choice{position:absolute;left:140px;top:72px;width:90px}"
      "#tags{position:absolute;left:240px;top:72px;width:70px;height:70px}"
      "label{position:absolute;left:8px;top:138px;color:white}"
      "select{display:none}"
      "</style></head><body>"
      "<div id='target' data-godot-action='start'>Start</div>"
      "<div id='slot'><span id='slot_child' data-godot-action='slot'>Slot</span></div>"
      "<input id='name' value='seed'>"
      "<input id='range' type='range' min='0' max='100' step='5' value='10'>"
      "<select id='choice'><option value='a' selected>A</option>"
      "<option value='b'>B</option><option value='c'>C</option></select>"
      "<select id='tags' multiple><option value='alpha' selected>Alpha</option>"
      "<option value='beta'>Beta</option><option value='gamma' selected>Gamma</option>"
      "</select><label><input id='agree' type='checkbox'>Agree</label>"
      "</body></html>";
  const char* html_b =
      "<!doctype html><style>html,body{margin:0;background:transparent}"
      "#panel_b{width:100px;height:40px;background:#d06329}"
      "#stable_b{position:absolute;left:0;top:48px;width:110px;height:28px;"
      "background:#237a57;color:white}</style>"
      "<div id='panel_b'></div><div id='stable_b' "
      "data-godot-action='stable-b'>Stable</div>"
      "<input id='name_b' value='stable'>";
  status = blink_standalone_renderer_set_document_html(renderer_a, html_a, "",
                                                       "");
  if (status == BLINK_STANDALONE_STATUS_OK) {
    status = blink_standalone_renderer_set_document_html(renderer_b, html_b,
                                                         "", "");
  }
  const bool initial_a_ok =
      AdvanceCApiFrameForSmoke(renderer_a, 0.0,
                               "c_api_mutation_stress_smoke");
  const bool initial_b_ok =
      AdvanceCApiFrameForSmoke(renderer_b, 0.0,
                               "c_api_mutation_stress_smoke");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !initial_a_ok ||
      !initial_b_ok) {
    std::fprintf(stderr,
                 "c_api_mutation_stress_smoke: initial render failed "
                 "status=%d Aerr=%s Berr=%s\n",
                 status, blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  const auto capture_hash = [](blink_standalone_renderer_t* renderer,
                               const char* label,
                               int expected_width,
                               int expected_height,
                               uint64_t* hash_out,
                               FramePixelContentStats* stats_out) -> bool {
    blink_standalone_frame_output_t output = {};
    const blink_standalone_status_code_t output_status =
        blink_standalone_renderer_get_latest_output(renderer, &output);
    const uint64_t hash = HashFramePixels(output);
    const FramePixelContentStats stats = AnalyzeFramePixelContent(output);
    const bool ok =
        output_status == BLINK_STANDALONE_STATUS_OK &&
        output.width == expected_width && output.height == expected_height &&
        output.stride >= expected_width * 4 && output.pixel_count > 0 &&
        output.pixel_format != BLINK_STANDALONE_PIXEL_FORMAT_NONE &&
        hash != 0 && FrameHasNonUniformPixels(output);
    if (!ok) {
      std::fprintf(stderr,
                   "c_api_mutation_stress_smoke: %s output invalid status=%d "
                   "raw=%dx%d stride=%d bytes=%zu format=%d hash=%llu "
                   "error=%s\n",
                   label, output_status, output.width, output.height,
                   output.stride, output.pixel_count, output.pixel_format,
                   static_cast<unsigned long long>(hash),
                   blink_standalone_renderer_last_error(renderer));
    }
    blink_standalone_renderer_release_latest_output(renderer);
    if (hash_out) {
      *hash_out = hash;
    }
    if (stats_out) {
      *stats_out = stats;
    }
    return ok;
  };

  uint64_t initial_a_hash = 0;
  FramePixelContentStats initial_a_stats;
  uint64_t initial_b_hash = 0;
  FramePixelContentStats initial_b_stats;
  if (!capture_hash(renderer_a, "A initial", 320, 180, &initial_a_hash,
                    &initial_a_stats) ||
      !capture_hash(renderer_b, "B initial", 180, 100, &initial_b_hash,
                    &initial_b_stats) ||
      initial_a_stats.dark_blue_112233 < 8000 ||
      initial_b_stats.transparent < 8000 ||
      initial_b_stats.orange_d06329 < 3000 ||
      !HasHitId(renderer_a, "target") || !HasHitId(renderer_a, "slot_child") ||
      !HasHitId(renderer_b, "stable_b")) {
    std::fprintf(stderr,
                 "c_api_mutation_stress_smoke: initial invariants failed "
                 "Ahash=%llu Bhash=%llu Ablue=%zu Btransparent=%zu "
                 "Borange=%zu Ahit=%d Bhit=%d\n",
                 static_cast<unsigned long long>(initial_a_hash),
                 static_cast<unsigned long long>(initial_b_hash),
                 initial_a_stats.dark_blue_112233,
                 initial_b_stats.transparent, initial_b_stats.orange_d06329,
                 HasHitId(renderer_a, "target") ? 1 : 0,
                 HasHitId(renderer_b, "stable_b") ? 1 : 0);
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  double time = 0.016;
  uint64_t previous_a_hash = initial_a_hash;
  uint64_t final_a_hash = initial_a_hash;
  int resize_count = 0;
  int failure_recovery_count = 0;
  int insert_remove_count = 0;
  int body_replace_count = 0;
  for (int i = 0; i < kIterations; ++i) {
    const std::string index = std::to_string(i);
    const char* color =
        i % 4 == 0   ? "#2878d8"
        : i % 4 == 1 ? "#d06329"
        : i % 4 == 2 ? "#e84444"
                     : "#237a57";
    const std::string style =
        std::string("position:absolute;left:8px;top:8px;width:112px;"
                    "height:42px;color:white;background:") +
        color;
    const std::string action = "action-" + index;
    const std::string target_text = "T" + index;
    status = blink_standalone_renderer_set_element_text(
        renderer_a, "target", target_text.c_str());
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_element_attribute(
                       renderer_a, "target", "data-godot-action",
                       action.c_str())
                 : status;
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_element_style(
                       renderer_a, "target", style.c_str())
                 : status;
    const std::string css =
        std::string("html,body{margin:0;padding:0;background:#112233;"
                    "font:15px monospace}#target{position:absolute;left:8px;"
                    "top:8px;width:112px;height:42px;color:white}#slot{"
                    "position:absolute;left:128px;top:8px;width:150px;"
                    "height:54px}#name{position:absolute;left:8px;top:72px;"
                    "width:120px}#range{position:absolute;left:8px;top:104px;"
                    "width:120px}#choice{position:absolute;left:140px;top:72px;"
                    "width:90px}#tags{position:absolute;left:240px;top:72px;"
                    "width:70px;height:70px}label{position:absolute;left:8px;"
                    "top:138px;color:") +
        (i % 2 == 0 ? "white" : "#d06329") + "}select{display:none}";
    if (status == BLINK_STANDALONE_STATUS_OK && i % 9 == 5) {
      status = blink_standalone_renderer_replace_stylesheet_text(
          renderer_a, "theme", css.c_str());
    }
    const std::string name_value = "value-" + index;
    const std::string range_value = std::to_string((i * 5) % 105);
    const char* choice_value = i % 3 == 0 ? "a" : (i % 3 == 1 ? "b" : "c");
    const char* selected_values_even[] = {"alpha", "gamma"};
    const char* selected_values_odd[] = {"beta"};
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_form_control_value(
                       renderer_a, "name", name_value.c_str())
                 : status;
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_form_control_value(
                       renderer_a, "range", range_value.c_str())
                 : status;
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_form_control_value(
                       renderer_a, "choice", choice_value)
                 : status;
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_form_control_checked(
                       renderer_a, "agree", i % 2 == 0 ? 1 : 0)
                 : status;
    status = status == BLINK_STANDALONE_STATUS_OK
                 ? blink_standalone_renderer_set_form_control_selected_values(
                       renderer_a, "tags",
                       i % 2 == 0 ? selected_values_even : selected_values_odd,
                       i % 2 == 0 ? 2 : 1)
                 : status;

    if (status == BLINK_STANDALONE_STATUS_OK && i % 8 == 4) {
      const std::string fragment =
          "<span id='slot_child' data-godot-action='slot-" + index +
          "' style='display:block;width:120px;height:28px;background:" +
          color + ";color:white'>Slot " + index + "</span>";
      status = blink_standalone_renderer_set_element_inner_html(
          renderer_a, "slot", fragment.c_str());
    }
    if (status == BLINK_STANDALONE_STATUS_OK && i % 7 == 3) {
      const std::string inserted =
          "<span id='temp' data-godot-action='temp-" + index +
          "' style='display:block;width:90px;height:18px;background:#e84444;"
          "color:white'>Temp</span>";
      status = blink_standalone_renderer_insert_element_html(
          renderer_a, "slot", BLINK_STANDALONE_INSERT_BEFORE_END,
          inserted.c_str());
      ++insert_remove_count;
    }
    if (status == BLINK_STANDALONE_STATUS_OK && i % 7 == 4 &&
        HasHitId(renderer_a, "temp")) {
      status = blink_standalone_renderer_remove_element(renderer_a, "temp");
    }
    if (status == BLINK_STANDALONE_STATUS_OK && i == 20) {
      const char* body =
          "<div id='target' data-godot-action='body-replaced' "
          "style='position:absolute;left:8px;top:8px;width:112px;height:42px;"
          "background:#2878d8;color:white'>Body</div>"
          "<div id='slot'><span id='slot_child' data-godot-action='slot-body' "
          "style='display:block;width:120px;height:28px;background:#d06329;"
          "color:white'>Slot body</span></div>"
          "<input id='name' value='body-seed'>"
          "<input id='range' type='range' min='0' max='100' step='5' value='20'>"
          "<select id='choice'><option value='a'>A</option>"
          "<option value='b' selected>B</option><option value='c'>C</option></select>"
          "<select id='tags' multiple><option value='alpha' selected>Alpha</option>"
          "<option value='beta' selected>Beta</option><option value='gamma'>Gamma</option>"
          "</select><label><input id='agree' type='checkbox' checked>Agree</label>";
      status = blink_standalone_renderer_set_body_inner_html(renderer_a, body);
      ++body_replace_count;
    }
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "c_api_mutation_stress_smoke: queue failed iteration=%d "
                   "status=%d error=%s\n",
                   i, status, blink_standalone_renderer_last_error(renderer_a));
      blink_standalone_renderer_destroy(renderer_b);
      blink_standalone_renderer_destroy(renderer_a);
      return 1;
    }

    if (i % 11 == 3) {
      if (blink_standalone_renderer_insert_element_html(
              renderer_a, "target", BLINK_STANDALONE_INSERT_BEFORE_END,
              "<button onclick='alert(1)'>Bad</button>") !=
              BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED ||
          blink_standalone_renderer_get_last_error_code(renderer_a) !=
              BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED) {
        std::fprintf(stderr,
                     "c_api_mutation_stress_smoke: unsafe failure diagnostic "
                     "missing iteration=%d status=%d error=%s\n",
                     i, blink_standalone_renderer_get_last_error_code(renderer_a),
                     blink_standalone_renderer_last_error(renderer_a));
        blink_standalone_renderer_destroy(renderer_b);
        blink_standalone_renderer_destroy(renderer_a);
        return 1;
      }
      status = blink_standalone_renderer_set_element_text(
          renderer_a, "target", target_text.c_str());
      ++failure_recovery_count;
    } else if (i % 11 == 7) {
      if (blink_standalone_renderer_remove_element(renderer_a, "missing") !=
              BLINK_STANDALONE_STATUS_INVALID_ARGUMENT ||
          blink_standalone_renderer_get_last_error_code(renderer_a) !=
              BLINK_STANDALONE_STATUS_INVALID_ARGUMENT) {
        std::fprintf(stderr,
                     "c_api_mutation_stress_smoke: missing-id diagnostic "
                     "missing iteration=%d status=%d error=%s\n",
                     i, blink_standalone_renderer_get_last_error_code(renderer_a),
                     blink_standalone_renderer_last_error(renderer_a));
        blink_standalone_renderer_destroy(renderer_b);
        blink_standalone_renderer_destroy(renderer_a);
        return 1;
      }
      status = blink_standalone_renderer_set_element_text(
          renderer_a, "target", target_text.c_str());
      ++failure_recovery_count;
    } else if (i % 11 == 9) {
      if (blink_standalone_renderer_insert_element_html(
              renderer_a, "target",
              static_cast<blink_standalone_insert_position_t>(-1),
              "<span>Bad</span>") != BLINK_STANDALONE_STATUS_INVALID_ARGUMENT ||
          blink_standalone_renderer_get_last_error_code(renderer_a) !=
              BLINK_STANDALONE_STATUS_INVALID_ARGUMENT) {
        std::fprintf(stderr,
                     "c_api_mutation_stress_smoke: invalid-position "
                     "diagnostic missing iteration=%d status=%d error=%s\n",
                     i, blink_standalone_renderer_get_last_error_code(renderer_a),
                     blink_standalone_renderer_last_error(renderer_a));
        blink_standalone_renderer_destroy(renderer_b);
        blink_standalone_renderer_destroy(renderer_a);
        return 1;
      }
      status = blink_standalone_renderer_set_element_text(
          renderer_a, "target", target_text.c_str());
      ++failure_recovery_count;
    }
    if (status != BLINK_STANDALONE_STATUS_OK ||
        blink_standalone_renderer_get_last_error_code(renderer_a) !=
            BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "c_api_mutation_stress_smoke: recovery mutation failed "
                   "iteration=%d status=%d code=%d error=%s\n",
                   i, status,
                   blink_standalone_renderer_get_last_error_code(renderer_a),
                   blink_standalone_renderer_last_error(renderer_a));
      blink_standalone_renderer_destroy(renderer_b);
      blink_standalone_renderer_destroy(renderer_a);
      return 1;
    }

    int expected_width = 320;
    int expected_height = 180;
    if (i % 13 == 5) {
      status = blink_standalone_renderer_set_viewport(renderer_a, 320, 180,
                                                      2.0f);
      expected_width = 640;
      expected_height = 360;
      ++resize_count;
    } else if (i % 13 == 6) {
      status = blink_standalone_renderer_set_viewport(renderer_a, 320, 180,
                                                      1.0f);
      ++resize_count;
    }
    if (status == BLINK_STANDALONE_STATUS_OK) {
      status = blink_standalone_renderer_advance_frame(renderer_a, time);
    }
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr,
                   "c_api_mutation_stress_smoke: advance failed iteration=%d "
                   "status=%d error=%s\n",
                   i, status, blink_standalone_renderer_last_error(renderer_a));
      blink_standalone_renderer_destroy(renderer_b);
      blink_standalone_renderer_destroy(renderer_a);
      return 1;
    }
    uint64_t frame_hash = 0;
    FramePixelContentStats frame_stats;
    if (!capture_hash(renderer_a, "A stress", expected_width, expected_height,
                      &frame_hash, &frame_stats)) {
      blink_standalone_renderer_destroy(renderer_b);
      blink_standalone_renderer_destroy(renderer_a);
      return 1;
    }
    final_a_hash = frame_hash;
    blink_standalone_form_control_state_t name_state = {};
    blink_standalone_form_control_state_t range_state = {};
    blink_standalone_form_control_state_t choice_state = {};
    const size_t selected_count =
        blink_standalone_renderer_form_control_selected_value_count(renderer_a,
                                                                    "tags");
    blink_standalone_hit_metadata_t target_hit = {};
    const std::string expected_action = i == 20 ? "body-replaced" : action;
    if (!GetFormStateById(renderer_a, "name", &name_state) ||
        !GetFormStateById(renderer_a, "range", &range_state) ||
        !GetFormStateById(renderer_a, "choice", &choice_state) ||
        FormStateValue(name_state) != (i == 20 ? "body-seed" : name_value) ||
        selected_count == 0 || !HasHitId(renderer_a, "slot_child") ||
        !GetHitById(renderer_a, "target", &target_hit) ||
        std::string(target_hit.data_godot_action
                        ? target_hit.data_godot_action
                        : "") != expected_action ||
        (i % 7 == 1 && HasHitId(renderer_a, "temp")) ||
        frame_stats.dark_blue_112233 < 4000 || frame_hash == 0) {
      std::fprintf(stderr,
                   "c_api_mutation_stress_smoke: invariant failed iteration=%d "
                   "hash=%llu prev=%llu raw=%dx%d blue=%zu name=%s range=%s "
                   "choice=%s selected=%zu target_action=%s expected=%s "
                   "temp=%d error=%s\n",
                   i, static_cast<unsigned long long>(frame_hash),
                   static_cast<unsigned long long>(previous_a_hash),
                   expected_width, expected_height,
                   frame_stats.dark_blue_112233,
                   FormStateValue(name_state).c_str(),
                   FormStateValue(range_state).c_str(),
                   FormStateValue(choice_state).c_str(), selected_count,
                   target_hit.data_godot_action ? target_hit.data_godot_action
                                                : "",
                   expected_action.c_str(), HasHitId(renderer_a, "temp") ? 1 : 0,
                   blink_standalone_renderer_last_error(renderer_a));
      blink_standalone_renderer_destroy(renderer_b);
      blink_standalone_renderer_destroy(renderer_a);
      return 1;
    }
    previous_a_hash = frame_hash;
    time += 0.016;
  }

  status = blink_standalone_renderer_advance_frame(renderer_b, time + 1.0);
  uint64_t stable_b_hash = 0;
  FramePixelContentStats stable_b_stats;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_hash(renderer_b, "B stable", 180, 100, &stable_b_hash,
                    &stable_b_stats) ||
      stable_b_hash != initial_b_hash || !HasHitId(renderer_b, "stable_b") ||
      HasHitId(renderer_b, "target") || stable_b_stats.transparent < 8000 ||
      stable_b_stats.orange_d06329 < 3000) {
    std::fprintf(stderr,
                 "c_api_mutation_stress_smoke: B isolation failed status=%d "
                 "initial_hash=%llu stable_hash=%llu transparent=%zu "
                 "orange=%zu target_leak=%d Berr=%s\n",
                 status, static_cast<unsigned long long>(initial_b_hash),
                 static_cast<unsigned long long>(stable_b_hash),
                 stable_b_stats.transparent, stable_b_stats.orange_d06329,
                 HasHitId(renderer_b, "target") ? 1 : 0,
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  status = blink_standalone_renderer_set_element_text(renderer_b, "stable_b",
                                                      "Mutated B");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_element_attribute(
                     renderer_b, "stable_b", "data-godot-action", "mutated-b")
               : status;
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_advance_frame(renderer_b, time + 2.0)
               : status;
  uint64_t mutated_b_hash = 0;
  FramePixelContentStats mutated_b_stats;
  blink_standalone_hit_metadata_t stable_b_hit = {};
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !capture_hash(renderer_b, "B mutated", 180, 100, &mutated_b_hash,
                    &mutated_b_stats) ||
      mutated_b_hash == stable_b_hash ||
      !GetHitById(renderer_b, "stable_b", &stable_b_hit) ||
      std::string(stable_b_hit.data_godot_action
                      ? stable_b_hit.data_godot_action
                      : "") != "mutated-b" ||
      !HasHitId(renderer_a, "target") || HasHitId(renderer_a, "stable_b")) {
    std::fprintf(stderr,
                 "c_api_mutation_stress_smoke: B mutation/A isolation failed "
                 "status=%d stable=%llu mutated=%llu Baction=%s Aleak=%d "
                 "Aerr=%s Berr=%s\n",
                 status, static_cast<unsigned long long>(stable_b_hash),
                 static_cast<unsigned long long>(mutated_b_hash),
                 stable_b_hit.data_godot_action ? stable_b_hit.data_godot_action
                                                : "",
                 HasHitId(renderer_a, "stable_b") ? 1 : 0,
                 blink_standalone_renderer_last_error(renderer_a),
                 blink_standalone_renderer_last_error(renderer_b));
    blink_standalone_renderer_destroy(renderer_b);
    blink_standalone_renderer_destroy(renderer_a);
    return 1;
  }

  blink_standalone_renderer_destroy(renderer_b);
  blink_standalone_renderer_destroy(renderer_a);
  std::printf(
      "c_api_mutation_stress_smoke: ok iterations=%d failures=%d "
      "insert_remove=%d body_replaces=%d resizes=%d A_initial=%llu "
      "A_final=%llu B_stable=%llu B_mutated=%llu\n",
      kIterations, failure_recovery_count, insert_remove_count,
      body_replace_count, resize_count,
      static_cast<unsigned long long>(initial_a_hash),
      static_cast<unsigned long long>(final_a_hash),
      static_cast<unsigned long long>(stable_b_hash),
      static_cast<unsigned long long>(mutated_b_hash));
  return 0;
}

bool RenderHtmlForBackdropSmoke(blink_standalone_renderer_t* renderer,
                                const char* html,
                                const char* label,
                                blink_standalone_frame_output_t* output) {
  blink_standalone_status_code_t status =
      blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: set html failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: advance failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  status = blink_standalone_renderer_get_latest_output(renderer, output);
  if (status != BLINK_STANDALONE_STATUS_OK || !output->pixels) {
    std::fprintf(stderr, "%s: output failed status=%d error=%s\n", label,
                 status, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  return true;
}

int RunCApiCssFilterBlurSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 160;
  config.height = 120;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_css_filter_blur_smoke: create failed status=%d\n",
                 status);
    return 1;
  }
  const char* unfiltered =
      "<!doctype html><style>body{margin:0;background:#112233}"
      "#box{position:absolute;left:40px;top:32px;width:72px;height:56px;"
      "background:#d06329}</style><div id='box'></div>";
  blink_standalone_frame_output_t output = {};
  if (!RenderHtmlForBackdropSmoke(renderer, unfiltered,
                                  "c_api_css_filter_blur_smoke", &output)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const size_t unfiltered_edge_orange =
      CountPixelsInRectNearColor(output, 40, 32, 8, 56, 0xd0, 0x63, 0x29, 12);
  const uint64_t unfiltered_hash = HashFramePixels(output);
  blink_standalone_renderer_release_latest_output(renderer);

  const char* filtered =
      "<!doctype html><style>body{margin:0;background:#112233}"
      "#box{position:absolute;left:40px;top:32px;width:72px;height:56px;"
      "background:#d06329;filter:blur(8px)}</style><div id='box'></div>";
  output = {};
  if (!RenderHtmlForBackdropSmoke(renderer, filtered,
                                  "c_api_css_filter_blur_smoke", &output)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const size_t filtered_edge_orange =
      CountPixelsInRectNearColor(output, 40, 32, 8, 56, 0xd0, 0x63, 0x29, 12);
  const uint64_t filtered_hash = HashFramePixels(output);
  if (unfiltered_hash == filtered_hash ||
      filtered_edge_orange >= unfiltered_edge_orange) {
    std::fprintf(
        stderr,
        "c_api_css_filter_blur_smoke: blur did not affect raw pixels "
        "unfiltered_edge=%zu filtered_edge=%zu hashes=%llu/%llu\n",
        unfiltered_edge_orange, filtered_edge_orange,
        static_cast<unsigned long long>(unfiltered_hash),
        static_cast<unsigned long long>(filtered_hash));
    blink_standalone_renderer_release_latest_output(renderer);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_css_filter_blur_smoke: ok unfiltered_edge=%zu "
      "filtered_edge=%zu\n",
      unfiltered_edge_orange, filtered_edge_orange);
  return 0;
}

bool GetSingleBackdropRegion(blink_standalone_renderer_t* renderer,
                             const char* label,
                             blink_standalone_backdrop_filter_region_t* region) {
  const size_t count =
      blink_standalone_renderer_backdrop_filter_region_count(renderer);
  if (count != 1 ||
      blink_standalone_renderer_get_backdrop_filter_region(renderer, 0,
                                                           region) !=
          BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: expected one backdrop region, got %zu error=%s\n",
                 label, count, blink_standalone_renderer_last_error(renderer));
    return false;
  }
  return true;
}

int RunCApiBackdropFilterRegionSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 256;
  config.height = 128;
  config.device_scale_factor = 2.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_backdrop_filter_region_smoke: create failed status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style>body{margin:0;background:#123456}"
      "#panel{position:absolute;left:32px;top:24px;width:96px;height:48px;"
      "background:rgba(255,255,255,.25);backdrop-filter:blur(8px);"
      "-webkit-backdrop-filter:blur(8px)}</style><div id='panel'></div>";
  blink_standalone_frame_output_t output = {};
  if (!RenderHtmlForBackdropSmoke(renderer, html,
                                  "c_api_backdrop_filter_region_smoke",
                                  &output)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  const bool dsf_ok = output.width == 512 && output.height == 256;
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_backdrop_filter_region_t region = {};
  if (!GetSingleBackdropRegion(renderer, "c_api_backdrop_filter_region_smoke",
                               &region) ||
      !dsf_ok || region.blur_radius_css_px < 7.5f ||
      region.blur_radius_css_px > 8.5f || region.bounds.x < 31.0f ||
      region.bounds.x > 33.0f || region.bounds.y < 23.0f ||
      region.bounds.y > 25.0f || region.bounds.width < 95.0f ||
      region.bounds.width > 97.0f || region.bounds.height < 47.0f ||
      region.bounds.height > 49.0f ||
      (region.flags &
       (BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_COMPLEX_CLIP |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_TRANSFORM |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_FILTER_OP |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_MASK_OR_BLEND)) != 0) {
    std::fprintf(
        stderr,
        "c_api_backdrop_filter_region_smoke: invalid region raw_dsf=%d "
        "bounds=%.1f,%.1f %.1fx%.1f blur=%.1f flags=%u\n",
        dsf_ok ? 1 : 0, region.bounds.x, region.bounds.y,
        region.bounds.width, region.bounds.height, region.blur_radius_css_px,
        region.flags);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_backdrop_filter_region_smoke: ok bounds=%.0f,%.0f %.0fx%.0f "
      "blur=%.1f flags=%u raw=512x256\n",
      region.bounds.x, region.bounds.y, region.bounds.width,
      region.bounds.height, region.blur_radius_css_px, region.flags);
  return 0;
}

int RunCApiBackdropFilterRoundedSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 220;
  config.height = 140;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_backdrop_filter_rounded_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style>body{margin:0;background:#123456}"
      "#panel{position:absolute;left:24px;top:20px;width:120px;height:64px;"
      "border-radius:14px;background:rgba(255,255,255,.2);"
      "backdrop-filter:blur(6px);-webkit-backdrop-filter:blur(6px)}"
      "</style><div id='panel'></div>";
  blink_standalone_frame_output_t output = {};
  if (!RenderHtmlForBackdropSmoke(renderer, html,
                                  "c_api_backdrop_filter_rounded_smoke",
                                  &output)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_backdrop_filter_region_t region = {};
  if (!GetSingleBackdropRegion(renderer, "c_api_backdrop_filter_rounded_smoke",
                               &region) ||
      (region.flags & BLINK_STANDALONE_BACKDROP_FILTER_ROUNDED_RECT) == 0 ||
      region.border_radius_top_left < 13.0f ||
      region.border_radius_top_right < 13.0f ||
      region.border_radius_bottom_right < 13.0f ||
      region.border_radius_bottom_left < 13.0f) {
    std::fprintf(
        stderr,
        "c_api_backdrop_filter_rounded_smoke: invalid rounded region "
        "flags=%u radii=%.1f/%.1f/%.1f/%.1f blur=%.1f\n",
        region.flags, region.border_radius_top_left,
        region.border_radius_top_right, region.border_radius_bottom_right,
        region.border_radius_bottom_left, region.blur_radius_css_px);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_backdrop_filter_rounded_smoke: ok blur=%.1f radii=%.1f/%.1f/"
      "%.1f/%.1f flags=%u\n",
      region.blur_radius_css_px, region.border_radius_top_left,
      region.border_radius_top_right, region.border_radius_bottom_right,
      region.border_radius_bottom_left, region.flags);
  return 0;
}

int RunCApiBackdropFilterChainSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 260;
  config.height = 150;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_backdrop_filter_chain_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style>body{margin:0;background:#123456}"
      "#panel{position:absolute;left:28px;top:22px;width:136px;height:72px;"
      "border-radius:12px;background:rgba(255,255,255,.2);"
      "backdrop-filter:blur(12px) saturate(180%) brightness(1.08) "
      "hue-rotate(30deg);"
      "-webkit-backdrop-filter:blur(12px) saturate(180%) brightness(1.08) "
      "hue-rotate(30deg)}"
      "</style><div id='panel'></div>";
  blink_standalone_frame_output_t output = {};
  if (!RenderHtmlForBackdropSmoke(renderer, html,
                                  "c_api_backdrop_filter_chain_smoke",
                                  &output)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_backdrop_filter_region_t region = {};
  if (!GetSingleBackdropRegion(renderer, "c_api_backdrop_filter_chain_smoke",
                               &region) ||
      (region.flags &
       (BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_COMPLEX_CLIP |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_TRANSFORM |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_FILTER_OP |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_MASK_OR_BLEND)) != 0 ||
      region.filter_op_count != 4 ||
      region.filter_ops[0].type != BLINK_STANDALONE_BACKDROP_FILTER_OP_BLUR ||
      region.filter_ops[1].type !=
          BLINK_STANDALONE_BACKDROP_FILTER_OP_SATURATE ||
      region.filter_ops[2].type !=
          BLINK_STANDALONE_BACKDROP_FILTER_OP_BRIGHTNESS ||
      region.filter_ops[3].type !=
          BLINK_STANDALONE_BACKDROP_FILTER_OP_HUE_ROTATE ||
      std::abs(region.filter_ops[0].amount - 12.0f) > 0.25f ||
      std::abs(region.filter_ops[1].amount - 1.8f) > 0.05f ||
      std::abs(region.filter_ops[2].amount - 1.08f) > 0.03f ||
      std::abs(region.filter_ops[3].amount - 30.0f) > 0.25f) {
    std::fprintf(
        stderr,
        "c_api_backdrop_filter_chain_smoke: invalid chain flags=%u "
        "count=%u blur=%.1f ops=%u:%.2f,%u:%.2f,%u:%.2f,%u:%.2f\n",
        region.flags, region.filter_op_count, region.blur_radius_css_px,
        region.filter_ops[0].type, region.filter_ops[0].amount,
        region.filter_ops[1].type, region.filter_ops[1].amount,
        region.filter_ops[2].type, region.filter_ops[2].amount,
        region.filter_ops[3].type, region.filter_ops[3].amount);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_backdrop_filter_chain_smoke: ok count=%u ops=%u:%.1f,%u:%.2f,"
      "%u:%.2f,%u:%.1f\n",
      region.filter_op_count, region.filter_ops[0].type,
      region.filter_ops[0].amount, region.filter_ops[1].type,
      region.filter_ops[1].amount, region.filter_ops[2].type,
      region.filter_ops[2].amount, region.filter_ops[3].type,
      region.filter_ops[3].amount);
  return 0;
}

int RunCApiBackdropFilterUnsupportedSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 240;
  config.height = 160;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_backdrop_filter_unsupported_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }
  const char* html =
      "<!doctype html><style>body{margin:0;background:#123456}"
      "#panel{position:absolute;left:40px;top:32px;width:100px;height:56px;"
      "transform:rotate(4deg);clip-path:inset(0 round 10px);"
      "mix-blend-mode:multiply;background:rgba(255,255,255,.2);"
      "backdrop-filter:blur(4px) drop-shadow(0 0 2px black);"
      "-webkit-backdrop-filter:blur(4px) drop-shadow(0 0 2px black)}"
      "</style><div id='panel'></div>";
  blink_standalone_frame_output_t output = {};
  if (!RenderHtmlForBackdropSmoke(renderer, html,
                                  "c_api_backdrop_filter_unsupported_smoke",
                                  &output)) {
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_backdrop_filter_region_t region = {};
  if (!GetSingleBackdropRegion(renderer,
                               "c_api_backdrop_filter_unsupported_smoke",
                               &region) ||
      (region.flags &
       (BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_COMPLEX_CLIP |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_TRANSFORM |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_FILTER_OP |
        BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_MASK_OR_BLEND)) == 0) {
    std::fprintf(stderr,
                 "c_api_backdrop_filter_unsupported_smoke: unsupported flags "
                 "missing flags=%u blur=%.1f bounds=%.1f,%.1f %.1fx%.1f\n",
                 region.flags, region.blur_radius_css_px, region.bounds.x,
                 region.bounds.y, region.bounds.width, region.bounds.height);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_backdrop_filter_unsupported_smoke: ok flags=%u blur=%.1f\n",
      region.flags, region.blur_radius_css_px);
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

int RunCApiSliderFormStateSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 320;
  config.height = 160;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_slider_form_state_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;padding:12px;background:#112233;"
      "color:white;font:16px sans-serif}#volume{position:absolute;left:20px;"
      "top:70px;width:220px;height:24px}#label{position:absolute;left:20px;"
      "top:28px;width:160px;height:28px;background:#2878d8;color:white}"
      "</style><div id='label' data-godot-action='label'>Volume</div>"
      "<input id='volume' type='range' min='0' max='100' step='5' "
      "value='35' data-godot-action='volume'>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, 0.0,
                                "c_api_slider_form_state_smoke")) {
    std::fprintf(stderr,
                 "c_api_slider_form_state_smoke: initial render failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_form_control_state_t state = {};
  if (!GetFormStateById(renderer, "volume", &state) ||
      FormStateValue(state) != "35" ||
      FormStateCString(state.type) != "range" ||
      FormStateCString(state.min) != "0" ||
      FormStateCString(state.max) != "100" ||
      FormStateCString(state.step) != "5" ||
      !HasHitId(renderer, "volume")) {
    std::fprintf(stderr,
                 "c_api_slider_form_state_smoke: initial state mismatch "
                 "value=%s type=%s min=%s max=%s step=%s\n",
                 FormStateValue(state).c_str(),
                 FormStateCString(state.type).c_str(),
                 FormStateCString(state.min).c_str(),
                 FormStateCString(state.max).c_str(),
                 FormStateCString(state.step).c_str());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.016;
  status = blink_standalone_renderer_set_form_control_value(renderer, "volume",
                                                            "80");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_slider_form_state_smoke") ||
      !GetFormStateById(renderer, "volume", &state) ||
      FormStateValue(state) != "80") {
    std::fprintf(stderr,
                 "c_api_slider_form_state_smoke: set value failed status=%d "
                 "value=%s error=%s\n",
                 status, FormStateValue(state).c_str(),
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  time += 0.016;
  status = blink_standalone_renderer_set_form_control_value(renderer, "volume",
                                                            "103");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_slider_form_state_smoke") ||
      !GetFormStateById(renderer, "volume", &state) ||
      FormStateValue(state) != "103") {
    std::fprintf(stderr,
                 "c_api_slider_form_state_smoke: out-of-range value failed "
                 "status=%d value=%s error=%s\n",
                 status, FormStateValue(state).c_str(),
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_slider_form_state_smoke: ok value=103 type=range min=0 max=100 "
      "step=5 out_of_range=preserved\n");
  return 0;
}

int RunCApiSelectFormStateSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 320;
  config.height = 160;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_select_form_state_smoke: create failed status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;padding:12px;background:#112233;"
      "color:white;font:16px sans-serif}select{position:absolute;left:20px;"
      "top:60px;width:180px;height:34px;font:16px sans-serif}#label{"
      "position:absolute;left:20px;top:22px;width:160px;height:26px;"
      "background:#2878d8;color:white}</style>"
      "<div id='label' data-godot-action='label'>Choice</div>"
      "<select id='choice' data-godot-action='choice'>"
      "<option value='a' selected>A</option>"
      "<option value='b'>B</option>"
      "<option value='c'>C</option>"
      "</select>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, 0.0,
                                "c_api_select_form_state_smoke")) {
    std::fprintf(stderr,
                 "c_api_select_form_state_smoke: initial render failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_form_control_state_t state = {};
  if (!GetFormStateById(renderer, "choice", &state) ||
      FormStateValue(state) != "a" || !HasHitId(renderer, "choice")) {
    std::fprintf(stderr,
                 "c_api_select_form_state_smoke: initial state mismatch "
                 "value=%s hit=%d\n",
                 FormStateValue(state).c_str(),
                 HasHitId(renderer, "choice") ? 1 : 0);
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.016;
  status = blink_standalone_renderer_set_form_control_value(renderer, "choice",
                                                            "b");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_select_form_state_smoke") ||
      !GetFormStateById(renderer, "choice", &state) ||
      FormStateValue(state) != "b") {
    std::fprintf(stderr,
                 "c_api_select_form_state_smoke: set b failed status=%d "
                 "value=%s error=%s\n",
                 status, FormStateValue(state).c_str(),
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  time += 0.016;
  status = blink_standalone_renderer_set_form_control_value(renderer, "choice",
                                                            "missing");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_select_form_state_smoke") ||
      !GetFormStateById(renderer, "choice", &state) ||
      !FormStateValue(state).empty()) {
    std::fprintf(stderr,
                 "c_api_select_form_state_smoke: missing value behavior "
                 "changed status=%d value=%s error=%s\n",
                 status, FormStateValue(state).c_str(),
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  time += 0.016;
  status = blink_standalone_renderer_set_form_control_value(renderer, "choice",
                                                            "c");
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_viewport(renderer, 320, 160,
                                                         2.0f)
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_select_form_state_smoke") ||
      !GetFormStateById(renderer, "choice", &state) ||
      FormStateValue(state) != "c" || !HasHitId(renderer, "choice")) {
    std::fprintf(stderr,
                 "c_api_select_form_state_smoke: resize persistence failed "
                 "status=%d value=%s hit=%d error=%s\n",
                 status, FormStateValue(state).c_str(),
                 HasHitId(renderer, "choice") ? 1 : 0,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_select_form_state_smoke: ok initial=a set=b missing=empty "
      "resize_value=c\n");
  return 0;
}

int RunCApiMultiSelectFormStateSmoke() {
  blink_standalone_renderer_config_t config = {};
  config.width = 360;
  config.height = 200;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: create failed "
                 "status=%d\n",
                 status);
    return 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0;padding:12px;background:#112233;"
      "color:white;font:16px sans-serif}select{display:none}#label{"
      "position:absolute;left:20px;top:16px;width:190px;height:26px;"
      "background:#2878d8;color:white}</style>"
      "<div id='label' data-godot-action='label'>Tags</div>"
      "<select id='tags' multiple data-godot-action='tags'>"
      "<option value='alpha' selected>Alpha</option>"
      "<option value='beta'>Beta</option>"
      "<option value='gamma' selected>Gamma</option>"
      "<option value='delta'>Delta</option>"
      "</select>";
  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, 0.0,
                                "c_api_multiselect_form_state_smoke")) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: initial render failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_form_control_state_t state = {};
  std::vector<std::string> values = SelectedValuesForSmoke(renderer, "tags");
  if (!GetFormStateById(renderer, "tags", &state) ||
      FormStateValue(state) != "alpha" ||
      !SelectedValuesEqual(values, {"alpha", "gamma"})) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: initial mismatch "
                 "value=%s selected_count=%zu\n",
                 FormStateValue(state).c_str(), values.size());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  double time = 0.016;
  const char* beta_gamma[] = {"beta", "gamma"};
  status = blink_standalone_renderer_set_form_control_selected_values(
      renderer, "tags", beta_gamma, 2);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_multiselect_form_state_smoke") ||
      !GetFormStateById(renderer, "tags", &state)) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: beta/gamma mutation "
                 "failed status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  values = SelectedValuesForSmoke(renderer, "tags");
  if (FormStateValue(state) != "beta" ||
      !SelectedValuesEqual(values, {"beta", "gamma"})) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: beta/gamma mismatch "
                 "value=%s selected_count=%zu\n",
                 FormStateValue(state).c_str(), values.size());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  time += 0.016;
  const char* beta_missing[] = {"beta", "missing"};
  status = blink_standalone_renderer_set_form_control_selected_values(
      renderer, "tags", beta_missing, 2);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_multiselect_form_state_smoke") ||
      !GetFormStateById(renderer, "tags", &state)) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: missing mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  values = SelectedValuesForSmoke(renderer, "tags");
  if (FormStateValue(state) != "beta" ||
      !SelectedValuesEqual(values, {"beta"})) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: missing value behavior "
                 "changed value=%s selected_count=%zu\n",
                 FormStateValue(state).c_str(), values.size());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  time += 0.016;
  const char* alpha_delta[] = {"alpha", "delta"};
  status = blink_standalone_renderer_set_form_control_selected_values(
      renderer, "tags", alpha_delta, 2);
  status = status == BLINK_STANDALONE_STATUS_OK
               ? blink_standalone_renderer_set_viewport(renderer, 360, 200,
                                                         2.0f)
               : status;
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !AdvanceCApiFrameForSmoke(renderer, time,
                                "c_api_multiselect_form_state_smoke") ||
      !GetFormStateById(renderer, "tags", &state)) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: resize mutation failed "
                 "status=%d error=%s\n",
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  values = SelectedValuesForSmoke(renderer, "tags");
  if (FormStateValue(state) != "alpha" ||
      !SelectedValuesEqual(values, {"alpha", "delta"})) {
    std::fprintf(stderr,
                 "c_api_multiselect_form_state_smoke: resize persistence "
                 "failed value=%s selected_count=%zu\n",
                 FormStateValue(state).c_str(), values.size());
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }

  blink_standalone_renderer_destroy(renderer);
  std::printf(
      "c_api_multiselect_form_state_smoke: ok initial=alpha,gamma "
      "set=beta,gamma missing=ignored resize=alpha,delta\n");
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

const char* FullViewportButtonHitMetadataHtml() {
  return "<!doctype html>"
         "<html>"
         "<head>"
         "<style>"
         "html, body {"
         "  margin: 0;"
         "  padding: 0;"
         "  width: 100%;"
         "  height: 100%;"
         "  overflow: hidden;"
         "  background: #17212b;"
         "}"
         "#play {"
         "  position: fixed;"
         "  inset: 0;"
         "  width: 100vw;"
         "  height: 100vh;"
         "  margin: 0;"
         "  padding: 0;"
         "  border: 0;"
         "  background: #237a57;"
         "  color: white;"
         "  font: 700 72px Arial, sans-serif;"
         "}"
         "#play:active { background: #144a80; }"
         "</style>"
         "</head>"
         "<body>"
         "  <button id=\"play\" data-godot-action=\"play\">Play</button>"
         "</body>"
         "</html>";
}

bool CheckFullViewportButtonCenterHit(blink_standalone_renderer_t* renderer,
                                      const char* label,
                                      const char* stage) {
  blink_standalone_hit_metadata_t hit = {};
  const blink_standalone_status_code_t status =
      blink_standalone_renderer_hit_test(renderer, 640.0f, 360.0f, &hit);
  if (status == BLINK_STANDALONE_STATUS_OK &&
      std::string(hit.element_id ? hit.element_id : "") == "play" &&
      std::string(hit.data_godot_action ? hit.data_godot_action : "") ==
          "play") {
    return true;
  }
  std::fprintf(stderr,
               "%s: %s center hit failed status=%d count=%zu element=%s "
               "action=%s\n",
               label, stage, status,
               blink_standalone_renderer_hit_metadata_count(renderer),
               hit.element_id ? hit.element_id : "",
               hit.data_godot_action ? hit.data_godot_action : "");
  return false;
}

int RunCApiFullViewportButtonHitMetadataSmoke() {
  constexpr const char* kLabel = "c_api_full_viewport_button_hit_metadata_smoke";
  blink_standalone_renderer_config_t config = {};
  config.width = 1280;
  config.height = 720;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;
  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    std::fprintf(stderr, "%s: create failed status=%d\n", kLabel, status);
    return 1;
  }
  status = blink_standalone_renderer_set_document_html(
      renderer, FullViewportButtonHitMetadataHtml(), "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    std::fprintf(stderr, "%s: set html failed status=%d error=%s\n", kLabel,
                 status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !CheckFullViewportButtonCenterHit(renderer, kLabel, "initial")) {
    std::fprintf(stderr, "%s: initial frame failed status=%d error=%s\n",
                 kLabel, status, blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_mouse_down(
      renderer, 640.0f, 360.0f, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  blink_standalone_update_result_t down_update = {};
  if (status == BLINK_STANDALONE_STATUS_OK) {
    status = blink_standalone_renderer_update(renderer, 0.016, &down_update);
  }
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !CheckFullViewportButtonCenterHit(renderer, kLabel, "mouse-down")) {
    std::fprintf(stderr,
                 "%s: mouse-down metadata failed status=%d needs_output=%u "
                 "error=%s\n",
                 kLabel, status, down_update.needs_output,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  status = blink_standalone_renderer_mouse_up(
      renderer, 640.0f, 360.0f, BLINK_STANDALONE_MOUSE_BUTTON_LEFT, 0, 1);
  blink_standalone_update_result_t up_update = {};
  if (status == BLINK_STANDALONE_STATUS_OK) {
    status = blink_standalone_renderer_update(renderer, 0.032, &up_update);
  }
  if (status != BLINK_STANDALONE_STATUS_OK ||
      !CheckFullViewportButtonCenterHit(renderer, kLabel, "mouse-up")) {
    std::fprintf(stderr,
                 "%s: mouse-up metadata failed status=%d needs_output=%u "
                 "error=%s\n",
                 kLabel, status, up_update.needs_output,
                 blink_standalone_renderer_last_error(renderer));
    blink_standalone_renderer_destroy(renderer);
    return 1;
  }
  std::printf("%s: ok hits=%zu center=play action=play down_output=%u "
              "up_output=%u\n",
              kLabel, blink_standalone_renderer_hit_metadata_count(renderer),
              down_update.needs_output, up_update.needs_output);
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

int RunGpuOutputSmoke() {
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(stderr, "gpu_output_smoke: runtime initialization failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult result = runtime->AdvanceFrame(input);
  if (!result.gpu_frame.shared_image_available ||
      result.gpu_frame.mailbox.empty() ||
      !result.viz_display_created ||
      !result.skia_renderer_gpu_path_reached ||
      !result.shared_image_interface_available ||
      result.gpu_frame.is_software) {
    std::fprintf(stderr,
                 "gpu_output_smoke: failed shared_image=%d mailbox=%s "
                 "software=%d viz_display=%d skia_gpu=%d shared_interface=%d "
                 "failure=%s\n",
                 result.gpu_frame.shared_image_available ? 1 : 0,
                 result.gpu_frame.mailbox.c_str(),
                 result.gpu_frame.is_software ? 1 : 0,
                 result.viz_display_created ? 1 : 0,
                 result.skia_renderer_gpu_path_reached ? 1 : 0,
                 result.shared_image_interface_available ? 1 : 0,
                 result.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : result.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }
  std::printf(
      "gpu_output_smoke: ok size=%dx%d format=%s mailbox=%s sync=%s "
      "viz_display=%d skia_gpu=%d shared_interface=%d\n",
      result.gpu_frame.width, result.gpu_frame.height,
      result.gpu_frame.format.c_str(), result.gpu_frame.mailbox.c_str(),
      result.gpu_frame.creation_sync_token.c_str(),
      result.viz_display_created ? 1 : 0,
      result.skia_renderer_gpu_path_reached ? 1 : 0,
      result.shared_image_interface_available ? 1 : 0);
  return 0;
}

int RunGpuOutputVulkanSmoke() {
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(stderr,
                 "gpu_output_vulkan_smoke: runtime initialization failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_vulkan_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult result = runtime->AdvanceFrame(input);
  if (!result.gpu_frame.shared_image_available ||
      result.gpu_frame.mailbox.empty() ||
      !result.gpu_frame.vk_context_provider_available ||
      !result.gpu_frame.shared_context_state_is_vulkan ||
      !result.viz_display_created ||
      !result.skia_renderer_gpu_path_reached ||
      !result.shared_image_interface_available ||
      result.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_output_vulkan_smoke: failed shared_image=%d mailbox=%s "
        "software=%d vk_context_provider=%d is_vulkan=%d viz_display=%d "
        "skia_gpu=%d shared_interface=%d failure=%s\n",
        result.gpu_frame.shared_image_available ? 1 : 0,
        result.gpu_frame.mailbox.c_str(),
        result.gpu_frame.is_software ? 1 : 0,
        result.gpu_frame.vk_context_provider_available ? 1 : 0,
        result.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
        result.viz_display_created ? 1 : 0,
        result.skia_renderer_gpu_path_reached ? 1 : 0,
        result.shared_image_interface_available ? 1 : 0,
        result.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : result.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }
  std::printf(
      "gpu_output_vulkan_smoke: ok size=%dx%d format=%s mailbox=%s sync=%s "
      "vk_context_provider=%d is_vulkan=%d viz_display=%d skia_gpu=%d "
      "shared_interface=%d\n",
      result.gpu_frame.width, result.gpu_frame.height,
      result.gpu_frame.format.c_str(), result.gpu_frame.mailbox.c_str(),
      result.gpu_frame.creation_sync_token.c_str(),
      result.gpu_frame.vk_context_provider_available ? 1 : 0,
      result.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
      result.viz_display_created ? 1 : 0,
      result.skia_renderer_gpu_path_reached ? 1 : 0,
      result.shared_image_interface_available ? 1 : 0);
  return 0;
}

int RunGpuOutputVulkanPixelSmoke() {
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(
        stderr,
        "gpu_output_vulkan_pixel_smoke: failed failure=runtime initialization "
        "failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_vulkan_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult result = runtime->AdvanceFrame(input);
  if (!result.gpu_frame.shared_image_available ||
      result.gpu_frame.mailbox.empty() ||
      !result.gpu_frame.vk_context_provider_available ||
      !result.gpu_frame.shared_context_state_is_vulkan ||
      !result.viz_display_created ||
      !result.skia_renderer_gpu_path_reached ||
      !result.shared_image_interface_available ||
      result.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_output_vulkan_pixel_smoke: failed failure=setup shared_image=%d "
        "mailbox=%s software=%d vk_context_provider=%d is_vulkan=%d "
        "viz_display=%d skia_gpu=%d shared_interface=%d copy_failure=%s\n",
        result.gpu_frame.shared_image_available ? 1 : 0,
        result.gpu_frame.mailbox.c_str(),
        result.gpu_frame.is_software ? 1 : 0,
        result.gpu_frame.vk_context_provider_available ? 1 : 0,
        result.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
        result.viz_display_created ? 1 : 0,
        result.skia_renderer_gpu_path_reached ? 1 : 0,
        result.shared_image_interface_available ? 1 : 0,
        result.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : result.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  const std::string result_line =
      runtime->RunGpuOutputVulkanPixelSmokeForTesting();
  if (result_line.find("gpu_output_vulkan_pixel_smoke: ok") != 0 &&
      result_line.find("gpu_output_vulkan_pixel_smoke: blocked") != 0) {
    std::fprintf(stderr, "%s\n", result_line.c_str());
    return 1;
  }
  std::printf("%s\n", result_line.c_str());
  return 0;
}

int RunGpuOutputD3D12PixelSmoke() {
#if !BUILDFLAG(IS_WIN)
  std::printf(
      "gpu_output_d3d12_pixel_smoke: blocked platform=non_windows "
      "native_d3d12=0 failure=native D3D12 is a Windows backend; Linux and "
      "other platforms need Vulkan or a separately proven translation layer\n");
  return 0;
#elif defined(BLINK_STANDALONE_HAVE_DAWN_D3D12)
  constexpr uint32_t kWidth = 16;
  constexpr uint32_t kHeight = 16;
  constexpr uint32_t kBytesPerPixel = 4;
  constexpr uint32_t kReadbackBytesPerRow = 256;
  constexpr uint32_t kExpectedR = 0x12;
  constexpr uint32_t kExpectedG = 0x34;
  constexpr uint32_t kExpectedB = 0x56;
  constexpr uint32_t kExpectedA = 0xff;

  DawnProcTable procs = dawn::native::GetProcs();
  dawnProcSetProcs(&procs);

  dawn::native::DawnInstanceDescriptor native_desc;
  wgpu::InstanceDescriptor instance_desc;
  instance_desc.nextInChain = &native_desc;
  dawn::native::Instance instance(&instance_desc);
  wgpu::Instance wgpu_instance(instance.Get());

  wgpu::RequestAdapterOptions adapter_options;
  adapter_options.backendType = wgpu::BackendType::D3D12;
  adapter_options.powerPreference = wgpu::PowerPreference::HighPerformance;

  wgpu::Adapter adapter;
  wgpu::RequestAdapterStatus adapter_status =
      wgpu::RequestAdapterStatus::Error;
  bool adapter_done = false;
  wgpu_instance.RequestAdapter(
      &adapter_options, wgpu::CallbackMode::AllowProcessEvents,
      [&adapter_done, &adapter_status, &adapter](
          wgpu::RequestAdapterStatus status, wgpu::Adapter requested_adapter,
          wgpu::StringView) {
        adapter_status = status;
        adapter = std::move(requested_adapter);
        adapter_done = true;
      });
  for (int attempt = 0; !adapter_done && attempt < 500; ++attempt) {
    wgpu_instance.ProcessEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  if (!adapter_done || adapter_status != wgpu::RequestAdapterStatus::Success ||
      !adapter) {
    std::printf(
        "gpu_output_d3d12_pixel_smoke: blocked dawn=1 adapters=0 "
        "adapter_status=%u adapter_done=%d "
        "failure=no D3D12 adapter was enumerated\n",
        static_cast<unsigned>(adapter_status), adapter_done ? 1 : 0);
    return 0;
  }

  wgpu::DeviceDescriptor device_desc;
  wgpu::Device device = adapter.CreateDevice(&device_desc);
  if (!device) {
    std::printf(
        "gpu_output_d3d12_pixel_smoke: failed dawn=1 adapters=1 device=0\n");
    return 1;
  }

  wgpu::Queue queue = device.GetQueue();

  wgpu::TextureDescriptor texture_desc;
  texture_desc.usage =
      wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::CopySrc;
  texture_desc.dimension = wgpu::TextureDimension::e2D;
  texture_desc.size = {kWidth, kHeight, 1};
  texture_desc.format = wgpu::TextureFormat::RGBA8Unorm;
  texture_desc.mipLevelCount = 1;
  texture_desc.sampleCount = 1;
  wgpu::Texture texture = device.CreateTexture(&texture_desc);
  if (!texture) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_pixel_smoke: failed dawn=1 texture=0\n");
    return 1;
  }

  wgpu::TextureView texture_view = texture.CreateView();
  if (!texture_view) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_pixel_smoke: failed dawn=1 view=0\n");
    return 1;
  }

  wgpu::BufferDescriptor readback_desc;
  readback_desc.usage = wgpu::BufferUsage::CopyDst | wgpu::BufferUsage::MapRead;
  readback_desc.size = kReadbackBytesPerRow * kHeight;
  wgpu::Buffer readback = device.CreateBuffer(&readback_desc);
  if (!readback) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_pixel_smoke: failed dawn=1 readback=0\n");
    return 1;
  }

  wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
  wgpu::RenderPassColorAttachment color_attachment;
  color_attachment.view = texture_view;
  color_attachment.loadOp = wgpu::LoadOp::Clear;
  color_attachment.storeOp = wgpu::StoreOp::Store;
  color_attachment.clearValue = {
      static_cast<double>(kExpectedR) / 255.0,
      static_cast<double>(kExpectedG) / 255.0,
      static_cast<double>(kExpectedB) / 255.0,
      static_cast<double>(kExpectedA) / 255.0,
  };
  wgpu::RenderPassDescriptor pass_desc;
  pass_desc.colorAttachmentCount = 1;
  pass_desc.colorAttachments = &color_attachment;
  {
    wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&pass_desc);
    pass.End();
  }

  wgpu::TexelCopyTextureInfo copy_source;
  copy_source.texture = texture;
  copy_source.aspect = wgpu::TextureAspect::All;
  wgpu::TexelCopyBufferInfo copy_destination;
  copy_destination.buffer = readback;
  copy_destination.layout.bytesPerRow = kReadbackBytesPerRow;
  copy_destination.layout.rowsPerImage = kHeight;
  wgpu::Extent3D copy_size = {kWidth, kHeight, 1};
  encoder.CopyTextureToBuffer(&copy_source, &copy_destination, &copy_size);
  wgpu::CommandBuffer commands = encoder.Finish();
  queue.Submit(1, &commands);

  wgpu::MapAsyncStatus map_status = wgpu::MapAsyncStatus::Error;
  bool map_done = false;
  readback.MapAsync(
      wgpu::MapMode::Read, 0, readback_desc.size,
      wgpu::CallbackMode::AllowProcessEvents,
      [&map_done, &map_status](wgpu::MapAsyncStatus status,
                               wgpu::StringView) {
        map_status = status;
        map_done = true;
      });
  for (int attempt = 0; !map_done && attempt < 500; ++attempt) {
    device.Tick();
    wgpu_instance.ProcessEvents();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  if (!map_done || map_status != wgpu::MapAsyncStatus::Success) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_pixel_smoke: failed dawn=1 map_status=%u "
                 "map_done=%d\n",
                 static_cast<unsigned>(map_status), map_done ? 1 : 0);
    return 1;
  }

  const auto* pixels =
      static_cast<const uint8_t*>(readback.GetConstMappedRange());
  if (!pixels) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_pixel_smoke: failed dawn=1 mapped=0\n");
    return 1;
  }

  uint32_t matching_pixels = 0;
  uint32_t nontransparent_pixels = 0;
  for (uint32_t y = 0; y < kHeight; ++y) {
    for (uint32_t x = 0; x < kWidth; ++x) {
      const uint8_t* pixel =
          pixels + y * kReadbackBytesPerRow + x * kBytesPerPixel;
      if (pixel[3] != 0) {
        ++nontransparent_pixels;
      }
      if (pixel[0] == kExpectedR && pixel[1] == kExpectedG &&
          pixel[2] == kExpectedB && pixel[3] == kExpectedA) {
        ++matching_pixels;
      }
    }
  }
  const uint8_t first_r = pixels[0];
  const uint8_t first_g = pixels[1];
  const uint8_t first_b = pixels[2];
  const uint8_t first_a = pixels[3];
  readback.Unmap();

  if (matching_pixels != kWidth * kHeight) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_pixel_smoke: failed dawn=1 "
                 "expected_rgba=%02x%02x%02x%02x observed_first=%02x%02x%02x%02x "
                 "matching=%u nontransparent=%u\n",
                 kExpectedR, kExpectedG, kExpectedB, kExpectedA, first_r,
                 first_g, first_b, first_a, matching_pixels,
                 nontransparent_pixels);
    return 1;
  }

  std::printf(
      "gpu_output_d3d12_pixel_smoke: ok dawn=1 path=dawn_d3d12_clear_copy_readback "
      "adapters=%zu size=%ux%u format=RGBA8Unorm observed_first=%02x%02x%02x%02x "
      "matching_pixels=%u nontransparent_pixels=%u graphite=0 viz=0\n",
      size_t{1}, kWidth, kHeight, first_r, first_g, first_b, first_a,
      matching_pixels, nontransparent_pixels);
  return 0;
#elif !BUILDFLAG(USE_DAWN) || !BUILDFLAG(SKIA_USE_DAWN)
  std::printf(
      "gpu_output_d3d12_pixel_smoke: blocked use_dawn=%d skia_use_dawn=%d "
      "failure=standalone generated buildflags compile out Dawn/Graphite, "
      "and this renderer build has not consumed generated Dawn native "
      "libraries/headers yet\n",
      BUILDFLAG(USE_DAWN) ? 1 : 0, BUILDFLAG(SKIA_USE_DAWN) ? 1 : 0);
  return 0;
#else
  std::printf(
      "gpu_output_d3d12_pixel_smoke: blocked use_dawn=1 skia_use_dawn=1 "
      "failure=Dawn/Graphite buildflags are enabled, but standalone has not "
      "yet wired a D3D12 DawnContextProvider into SharedContextState and Viz "
      "SkiaOutputSurface\n");
  return 0;
#endif
}

int RunGpuOutputD3D12RenderPixelSmoke() {
#if !BUILDFLAG(IS_WIN)
  std::printf(
      "gpu_output_d3d12_render_pixel_smoke: blocked platform=non_windows "
      "native_d3d12=0 failure=native D3D12 is a Windows backend; Linux and "
      "other platforms need Vulkan or a separately proven translation layer\n");
  return 0;
#else
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(stderr,
                 "gpu_output_d3d12_render_pixel_smoke: failed "
                 "failure=runtime initialization failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_d3d12_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult result =
      runtime->AdvanceFrame(input);
  if (!result.gpu_frame.shared_image_available ||
      result.gpu_frame.mailbox.empty() || !result.viz_display_created ||
      !result.skia_renderer_gpu_path_reached ||
      !result.shared_image_interface_available || result.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_output_d3d12_render_pixel_smoke: failed failure=setup "
        "shared_image=%d mailbox=%s software=%d viz_display=%d skia_gpu=%d "
        "shared_interface=%d copy_failure=%s\n",
        result.gpu_frame.shared_image_available ? 1 : 0,
        result.gpu_frame.mailbox.c_str(),
        result.gpu_frame.is_software ? 1 : 0,
        result.viz_display_created ? 1 : 0,
        result.skia_renderer_gpu_path_reached ? 1 : 0,
        result.shared_image_interface_available ? 1 : 0,
        result.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : result.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput readback_input;
  readback_input.viewport = runtime->Snapshot().viewport;
  readback_input.request_raw_frame = true;
  readback_input.result_collection =
      html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult readback_result =
      runtime->AdvanceFrame(readback_input);
  const html_css_renderer::RawFrameOutput& raw = readback_result.raw_frame;
  auto raw_pixel_matches = [&raw](int x,
                                  int y,
                                  uint8_t expected_red,
                                  uint8_t expected_green,
                                  uint8_t expected_blue) {
    if (raw.width <= x || raw.height <= y || raw.stride < raw.width * 4 ||
        raw.pixels.empty() ||
        (raw.pixel_format != html_css_renderer::RawFramePixelFormat::kRGBA8 &&
         raw.pixel_format != html_css_renderer::RawFramePixelFormat::kBGRA8)) {
      return false;
    }
    const uint8_t* pixel =
        raw.pixels.data() + static_cast<size_t>(y) * raw.stride +
        static_cast<size_t>(x) * 4;
    const uint8_t red =
        raw.pixel_format == html_css_renderer::RawFramePixelFormat::kRGBA8
            ? pixel[0]
            : pixel[2];
    const uint8_t green = pixel[1];
    const uint8_t blue =
        raw.pixel_format == html_css_renderer::RawFramePixelFormat::kRGBA8
            ? pixel[2]
            : pixel[0];
    const auto near_channel = [](uint8_t actual, uint8_t expected) {
      const int delta = static_cast<int>(actual) - static_cast<int>(expected);
      return delta >= -12 && delta <= 12;
    };
    return pixel[3] != 0 && near_channel(red, expected_red) &&
           near_channel(green, expected_green) &&
           near_channel(blue, expected_blue);
  };
  if (!readback_result.raw_frame_requested ||
      readback_result.raw_frame_failure.size() > 0 ||
      !raw_pixel_matches(4, 4, 0x12, 0x34, 0x56) ||
      !raw_pixel_matches(24, 24, 0xd0, 0x63, 0x29)) {
    std::fprintf(
        stderr,
        "gpu_output_d3d12_render_pixel_smoke: failed failure=raw readback "
        "raw_requested=%d raw=%dx%d bytes=%zu format=%d raw_failure=%s\n",
        readback_result.raw_frame_requested ? 1 : 0, raw.width, raw.height,
        raw.pixels.size(), static_cast<int>(raw.pixel_format),
        readback_result.raw_frame_failure.c_str());
    return 1;
  }

  std::printf(
      "gpu_output_d3d12_render_pixel_smoke: ok rendered_html=1 graphite=1 "
      "viz=1 shared_image=1 readback=1 size=%dx%d format=%s mailbox=%s "
      "raw=%dx%d\n",
      result.gpu_frame.width, result.gpu_frame.height,
      result.gpu_frame.format.c_str(), result.gpu_frame.mailbox.c_str(),
      raw.width, raw.height);
  return 0;
#endif
}

int RunGpuBorrowedD3D12RenderCopySmoke() {
#if !BUILDFLAG(IS_WIN)
  std::printf(
      "gpu_borrowed_d3d12_render_copy_smoke: blocked platform=non_windows "
      "native_d3d12=0 failure=native D3D12 is a Windows backend; Linux and "
      "other platforms need Vulkan or a separately proven translation layer\n");
  return 0;
#else
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";

  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(stderr,
                 "gpu_borrowed_d3d12_render_copy_smoke: failed "
                 "failure=runtime initialization failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_d3d12_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult frame =
      runtime->AdvanceFrame(input);
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke after AdvanceFrame");
  if (!frame.gpu_frame.shared_image_available ||
      frame.gpu_frame.mailbox.empty() || !frame.viz_display_created ||
      !frame.skia_renderer_gpu_path_reached ||
      !frame.shared_image_interface_available || frame.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_borrowed_d3d12_render_copy_smoke: failed setup "
        "shared_image=%d mailbox=%s software=%d viz_display=%d skia_gpu=%d "
        "shared_interface=%d copy_failure=%s\n",
        frame.gpu_frame.shared_image_available ? 1 : 0,
        frame.gpu_frame.mailbox.c_str(),
        frame.gpu_frame.is_software ? 1 : 0,
        frame.viz_display_created ? 1 : 0,
        frame.skia_renderer_gpu_path_reached ? 1 : 0,
        frame.shared_image_interface_available ? 1 : 0,
        frame.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : frame.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  const std::string result_line =
      runtime->RunBorrowedD3D12RenderCopySmokeForTesting();
  if (result_line.find("gpu_borrowed_d3d12_render_copy_smoke: ok") != 0 &&
      result_line.find("gpu_borrowed_d3d12_render_copy_smoke: blocked") != 0) {
    std::fprintf(stderr, "%s\n", result_line.c_str());
    return 1;
  }
  std::printf("%s\n", result_line.c_str());
  return 0;
#endif
}

int RunGpuBorrowedVkImageBackingSmoke() {
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(
        stderr,
        "gpu_borrowed_vkimage_backing_smoke: runtime initialization failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_vulkan_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult frame =
      runtime->AdvanceFrame(input);
  if (!frame.gpu_frame.shared_image_available ||
      !frame.gpu_frame.vk_context_provider_available ||
      !frame.gpu_frame.shared_context_state_is_vulkan ||
      !frame.viz_display_created || !frame.skia_renderer_gpu_path_reached ||
      frame.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_borrowed_vkimage_backing_smoke: failed setup shared_image=%d "
        "vk_context_provider=%d is_vulkan=%d viz_display=%d skia_gpu=%d "
        "software=%d failure=%s\n",
        frame.gpu_frame.shared_image_available ? 1 : 0,
        frame.gpu_frame.vk_context_provider_available ? 1 : 0,
        frame.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
        frame.viz_display_created ? 1 : 0,
        frame.skia_renderer_gpu_path_reached ? 1 : 0,
        frame.gpu_frame.is_software ? 1 : 0,
        frame.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : frame.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  const std::string result_line =
      runtime->RunBorrowedVkImageBackingSmokeForTesting();
  if (result_line.find("gpu_borrowed_vkimage_backing_smoke: ok") != 0) {
    std::fprintf(stderr, "%s\n", result_line.c_str());
    return 1;
  }
  std::printf("%s\n", result_line.c_str());
  return 0;
}

int RunGpuBorrowedVkImageRenderCopySmoke() {
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(
        stderr,
        "gpu_borrowed_vkimage_render_copy_smoke: runtime initialization "
        "failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_vulkan_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult frame =
      runtime->AdvanceFrame(input);
  if (!frame.gpu_frame.shared_image_available ||
      !frame.gpu_frame.vk_context_provider_available ||
      !frame.gpu_frame.shared_context_state_is_vulkan ||
      !frame.viz_display_created || !frame.skia_renderer_gpu_path_reached ||
      frame.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_borrowed_vkimage_render_copy_smoke: failed setup "
        "shared_image=%d vk_context_provider=%d is_vulkan=%d "
        "viz_display=%d skia_gpu=%d software=%d failure=%s\n",
        frame.gpu_frame.shared_image_available ? 1 : 0,
        frame.gpu_frame.vk_context_provider_available ? 1 : 0,
        frame.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
        frame.viz_display_created ? 1 : 0,
        frame.skia_renderer_gpu_path_reached ? 1 : 0,
        frame.gpu_frame.is_software ? 1 : 0,
        frame.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : frame.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    return 1;
  }

  const std::string result_line =
      runtime->RunBorrowedVkImageRenderCopySmokeForTesting();
  if (result_line.find("gpu_borrowed_vkimage_render_copy_smoke: ok") != 0 &&
      result_line.find("gpu_borrowed_vkimage_render_copy_smoke: blocked") !=
          0) {
    std::fprintf(stderr, "%s\n", result_line.c_str());
    return 1;
  }
  std::printf("%s\n", result_line.c_str());
  return 0;
}

int RunGpuExternalVulkanRuntimeTargetSmoke() {
  std::unique_ptr<gpu::VulkanImplementation> implementation =
      gpu::CreateVulkanImplementation(false);
  if (!implementation) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_runtime_target_smoke: failed "
                 "failure=Vulkan implementation creation failed\n");
    return 1;
  }
  if (!implementation->InitializeVulkanInstance(true)) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_runtime_target_smoke: failed "
                 "failure=Vulkan instance initialization failed\n");
    return 1;
  }

  std::unique_ptr<gpu::VulkanDeviceQueue> owner_queue =
      gpu::CreateVulkanDeviceQueue(
          implementation.get(), gpu::VulkanDeviceQueue::GRAPHICS_QUEUE_FLAG,
          /*gpu_info=*/nullptr,
          /*heap_memory_limit=*/0,
          /*is_thread_safe=*/true);
  if (!owner_queue) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_runtime_target_smoke: failed "
                 "failure=Vulkan device queue creation failed\n");
    return 1;
  }

  const VkInstance borrowed_instance = owner_queue->GetVulkanInstance();
  const VkPhysicalDevice borrowed_physical_device =
      owner_queue->GetVulkanPhysicalDevice();
  const VkDevice borrowed_device = owner_queue->GetVulkanDevice();
  const VkQueue borrowed_queue = owner_queue->GetVulkanQueue();
  const uint32_t borrowed_queue_family = owner_queue->GetVulkanQueueIndex();
  const gfx::ExtensionSet borrowed_extensions =
      owner_queue->enabled_extensions();

  auto runtime_queue_wrapper =
      std::make_unique<gpu::VulkanDeviceQueue>(borrowed_instance);
  const bool runtime_queue_initialized =
      runtime_queue_wrapper->InitializeForCompositorGpuThread(
          borrowed_physical_device, borrowed_device, borrowed_queue,
          owner_queue->GetVulkanQueueLockContext(), borrowed_queue_family,
          borrowed_extensions, owner_queue->enabled_device_features_2(),
          owner_queue->vk_physical_device_properties(),
          owner_queue->vk_physical_device_driver_properties(),
          owner_queue->vma_allocator(),
          /*register_memory_dump_provider=*/false);
  if (!runtime_queue_initialized) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_runtime_target_smoke: failed "
                 "failure=non-owning runtime queue wrapper initialization "
                 "failed\n");
    owner_queue->Destroy();
    return 1;
  }

  blink::standalone_renderer_probe::
      StandaloneBlinkLiveFrameBridgeInstallExternalVulkanForTesting(
          implementation.get(), runtime_queue_wrapper.release());

  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = {128.0f, 64.0f};
  create_info.renderer.device_scale_factor = 1.0f;
  create_info.renderer.html =
      "<!doctype html><style>"
      "html,body{margin:0;width:100%;height:100%;background:#123456;}"
      "#box{position:absolute;left:16px;top:12px;width:80px;height:32px;"
      "background:#d06329;}"
      "</style><div id='box'></div>";
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(
          std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!runtime || !runtime->Initialize(&diagnostics)) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_runtime_target_smoke: failed "
                 "failure=runtime initialization failed\n");
    for (const std::string& diagnostic : diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    owner_queue->Destroy();
    return 1;
  }

  html_css_renderer::FrameInput input;
  input.viewport = runtime->Snapshot().viewport;
  input.request_vulkan_gpu_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  html_css_renderer::CompositorFrameResult frame =
      runtime->AdvanceFrame(input);
  if (!frame.gpu_frame.shared_image_available ||
      !frame.gpu_frame.vk_context_provider_available ||
      !frame.gpu_frame.shared_context_state_is_vulkan ||
      !frame.viz_display_created || !frame.skia_renderer_gpu_path_reached ||
      frame.gpu_frame.is_software) {
    std::fprintf(
        stderr,
        "gpu_external_vulkan_runtime_target_smoke: failed setup "
        "shared_image=%d vk_context_provider=%d is_vulkan=%d "
        "viz_display=%d skia_gpu=%d software=%d failure=%s\n",
        frame.gpu_frame.shared_image_available ? 1 : 0,
        frame.gpu_frame.vk_context_provider_available ? 1 : 0,
        frame.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
        frame.viz_display_created ? 1 : 0,
        frame.skia_renderer_gpu_path_reached ? 1 : 0,
        frame.gpu_frame.is_software ? 1 : 0,
        frame.gpu_frame_failure.c_str());
    for (const std::string& diagnostic : frame.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
    runtime.reset();
    owner_queue->Destroy();
    return 1;
  }

  const gfx::Size target_size(128, 64);
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before caller VkImage create");
  std::unique_ptr<gpu::VulkanImage> target_image = gpu::VulkanImage::Create(
      owner_queue.get(), target_size, VK_FORMAT_R8G8B8A8_UNORM,
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
          VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT);
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke after caller VkImage create");
  if (!target_image || target_image->image() == VK_NULL_HANDLE) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_runtime_target_smoke: failed "
                 "failure=caller-owned VkImage creation failed\n");
    runtime.reset();
    owner_queue->Destroy();
    return 1;
  }

  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before external VkImage render copy");
  html_css_renderer::ExternalVulkanImageTarget external_target;
  external_target.vk_image = target_image->image();
  external_target.vk_device_memory = target_image->device_memory();
  external_target.width = target_size.width();
  external_target.height = target_size.height();
  external_target.vk_format = VK_FORMAT_R8G8B8A8_UNORM;
  external_target.image_tiling = target_image->image_tiling();
  external_target.allocation_size = target_image->device_size();
  external_target.memory_type_index = target_image->memory_type_index();
  external_target.image_usage_flags = target_image->usage();
  external_target.image_create_flags = target_image->flags();
  external_target.queue_family_index = owner_queue->GetVulkanQueueIndex();
  const std::string result_line =
      runtime->RunExternalVkImageRenderCopyForTesting(external_target);
  vkDeviceWaitIdle(owner_queue->GetVulkanDevice());
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke after external VkImage render copy");
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before result validation");
  if (result_line.find("gpu_borrowed_vkimage_render_copy_smoke: ok") != 0) {
    std::fprintf(stderr,
                 "%s frame_shared_image=%d frame_vk_context=%d "
                 "frame_is_vulkan=%d frame_mailbox=%s frame_failure=%s\n",
                 result_line.c_str(),
                 frame.gpu_frame.shared_image_available ? 1 : 0,
                 frame.gpu_frame.vk_context_provider_available ? 1 : 0,
                 frame.gpu_frame.shared_context_state_is_vulkan ? 1 : 0,
                 frame.gpu_frame.mailbox.c_str(),
                 frame.gpu_frame_failure.c_str());
    runtime.reset();
    target_image->Destroy();
    owner_queue->Destroy();
    return 1;
  }

  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before success print");
  std::printf(
      "gpu_external_vulkan_runtime_target_smoke: ok external_provider=1 "
      "caller_image=1 %s\n",
      result_line.c_str());
  vkDeviceWaitIdle(owner_queue->GetVulkanDevice());
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before runtime teardown");
  runtime.reset();
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before caller VkImage destroy");
  target_image->Destroy();
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke before owner queue destroy");
  owner_queue->Destroy();
  html_css_renderer::SetStandaloneCrashBreadcrumb(
      "vulkan runtime smoke done");
  return 0;
}

int RunGpuExternalVulkanDeviceSmoke() {
  std::unique_ptr<gpu::VulkanImplementation> implementation =
      gpu::CreateVulkanImplementation(false);
  if (!implementation) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_device_smoke: Vulkan implementation "
                 "creation failed\n");
    return 1;
  }

  if (!implementation->InitializeVulkanInstance(true)) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_device_smoke: Vulkan instance "
                 "initialization failed\n");
    return 1;
  }

  std::unique_ptr<gpu::VulkanDeviceQueue> owned_queue =
      gpu::CreateVulkanDeviceQueue(
          implementation.get(), gpu::VulkanDeviceQueue::GRAPHICS_QUEUE_FLAG);
  if (!owned_queue) {
    std::fprintf(stderr,
                 "gpu_external_vulkan_device_smoke: owned Vulkan device queue "
                 "initialization failed\n");
    return 1;
  }

  const VkInstance borrowed_instance = owned_queue->GetVulkanInstance();
  const VkPhysicalDevice borrowed_physical_device =
      owned_queue->GetVulkanPhysicalDevice();
  const VkDevice borrowed_device = owned_queue->GetVulkanDevice();
  const VkQueue borrowed_queue = owned_queue->GetVulkanQueue();
  const uint32_t borrowed_queue_family = owned_queue->GetVulkanQueueIndex();
  const gfx::ExtensionSet borrowed_extensions =
      owned_queue->enabled_extensions();

  bool borrowed_initialized = false;
  bool command_pool_initialized = false;
  bool context_provider_created = false;
  bool borrowed_gr_context_initialized = false;
  bool borrowed_gr_context_available = false;
  {
    auto borrowed_queue_wrapper =
        std::make_unique<gpu::VulkanDeviceQueue>(borrowed_instance);
    borrowed_initialized = borrowed_queue_wrapper->InitializeForWebView(
        borrowed_physical_device, borrowed_device, borrowed_queue,
        borrowed_queue_family, borrowed_extensions);
    if (!borrowed_initialized) {
      std::fprintf(stderr,
                   "gpu_external_vulkan_device_smoke: non-owning Vulkan device "
                   "queue wrapper initialization failed\n");
      borrowed_queue_wrapper->Destroy();
      owned_queue->Destroy();
      return 1;
    }

    auto command_pool =
        std::make_unique<gpu::VulkanCommandPool>(borrowed_queue_wrapper.get());
    command_pool_initialized = command_pool->Initialize();
    if (!command_pool_initialized) {
      std::fprintf(stderr,
                   "gpu_external_vulkan_device_smoke: command pool creation "
                   "through borrowed queue failed\n");
      command_pool->Destroy();
      borrowed_queue_wrapper->Destroy();
      owned_queue->Destroy();
      return 1;
    }
    command_pool->Destroy();

    auto compositor_queue_wrapper =
        std::make_unique<gpu::VulkanDeviceQueue>(borrowed_instance);
    const bool compositor_queue_initialized =
        compositor_queue_wrapper->InitializeForCompositorGpuThread(
            borrowed_physical_device, borrowed_device, borrowed_queue,
            /*vk_queue_lock_context=*/nullptr, borrowed_queue_family,
            borrowed_extensions, owned_queue->enabled_device_features_2(),
            owned_queue->vk_physical_device_properties(),
            owned_queue->vk_physical_device_driver_properties(),
            owned_queue->vma_allocator(),
            /*register_memory_dump_provider=*/false);
    if (!compositor_queue_initialized) {
      std::fprintf(stderr,
                   "gpu_external_vulkan_device_smoke: non-owning compositor "
                   "Vulkan queue wrapper initialization failed\n");
      borrowed_queue_wrapper->Destroy();
      owned_queue->Destroy();
      return 1;
    }

    scoped_refptr<viz::VulkanInProcessContextProvider>
        borrowed_context_provider =
            viz::VulkanInProcessContextProvider::CreateForCompositorGpuThread(
                implementation.get(), std::move(compositor_queue_wrapper));
    context_provider_created = borrowed_context_provider != nullptr;
    if (!borrowed_context_provider) {
      std::fprintf(stderr,
                   "gpu_external_vulkan_device_smoke: borrowed Vulkan context "
                   "provider creation failed\n");
      borrowed_queue_wrapper->Destroy();
      owned_queue->Destroy();
      return 1;
    }
    GrContextOptions context_options;
    borrowed_gr_context_initialized =
        borrowed_context_provider->InitializeGrContext(context_options);
    borrowed_gr_context_available =
        borrowed_context_provider->GetGrContext() != nullptr;
    borrowed_context_provider->Destroy();
    if (!borrowed_gr_context_initialized || !borrowed_gr_context_available) {
      std::fprintf(stderr,
                   "gpu_external_vulkan_device_smoke: borrowed Vulkan Skia "
                   "context initialization failed initialized=%d gr_context=%d\n",
                   borrowed_gr_context_initialized ? 1 : 0,
                   borrowed_gr_context_available ? 1 : 0);
      borrowed_queue_wrapper->Destroy();
      owned_queue->Destroy();
      return 1;
    }
    borrowed_queue_wrapper->Destroy();
  }

  owned_queue->Destroy();

  std::printf(
      "gpu_external_vulkan_device_smoke: ok borrowed_queue=%d "
      "command_pool=%d context_provider=%d gr_context=%d queue_family=%u "
      "extensions=%zu owns_device=0\n",
      borrowed_initialized ? 1 : 0, command_pool_initialized ? 1 : 0,
      context_provider_created ? 1 : 0,
      borrowed_gr_context_available ? 1 : 0, borrowed_queue_family,
      borrowed_extensions.size());
  return 0;
}

int RunGpuVulkanGaneshContextSmoke() {
  std::unique_ptr<gpu::VulkanImplementation> implementation =
      gpu::CreateVulkanImplementation(false);
  if (!implementation) {
    std::fprintf(stderr,
                 "gpu_vulkan_ganesh_context_smoke: Vulkan implementation "
                 "creation failed\n");
    return 1;
  }

  if (!implementation->InitializeVulkanInstance(true)) {
    std::fprintf(stderr,
                 "gpu_vulkan_ganesh_context_smoke: Vulkan instance "
                 "initialization failed\n");
    return 1;
  }

  scoped_refptr<viz::VulkanInProcessContextProvider> vulkan_context_provider =
      viz::VulkanInProcessContextProvider::Create(implementation.get());
  if (!vulkan_context_provider) {
    std::fprintf(stderr,
                 "gpu_vulkan_ganesh_context_smoke: Vulkan context provider "
                 "creation failed\n");
    return 1;
  }

  if (gl::GetGLImplementation() == gl::kGLImplementationNone) {
    if (!gl::init::InitializeStaticGLBindingsOneOff()) {
      std::fprintf(stderr,
                   "gpu_vulkan_ganesh_context_smoke: GL static bindings "
                   "initialization failed\n");
      vulkan_context_provider->Destroy();
      return 1;
    }
    if (gl::GetGLImplementation() != gl::kGLImplementationDisabled &&
        !gl::init::InitializeGLOneOffPlatformImplementation(
            /*disable_gl_drawing=*/false, /*init_extensions=*/true,
            gl::GpuPreference::kDefault)) {
      std::fprintf(stderr,
                   "gpu_vulkan_ganesh_context_smoke: GL platform "
                   "initialization failed\n");
      vulkan_context_provider->Destroy();
      return 1;
    }
  }

  scoped_refptr<gl::GLShareGroup> share_group =
      base::MakeRefCounted<gl::GLShareGroup>();
  scoped_refptr<gl::GLSurface> gl_surface =
      gl::init::CreateOffscreenGLSurface(gl::GetDefaultDisplay(), gfx::Size());
  if (!gl_surface) {
    std::fprintf(stderr,
                 "gpu_vulkan_ganesh_context_smoke: offscreen GL surface "
                 "creation failed\n");
    vulkan_context_provider->Destroy();
    return 1;
  }

  gpu::GpuPreferences gpu_preferences;
  gpu_preferences.gr_context_type = gpu::GrContextType::kVulkan;
  gl::GLContextAttribs attribs =
      gpu::gles2::GenerateGLContextAttribsForCompositor(
          gpu_preferences.use_passthrough_cmd_decoder);
  scoped_refptr<gl::GLContext> gl_context =
      gl::init::CreateGLContext(share_group.get(), gl_surface.get(), attribs);
  if (!gl_context || !gl_context->MakeCurrent(gl_surface.get())) {
    std::fprintf(stderr,
                 "gpu_vulkan_ganesh_context_smoke: offscreen GL context "
                 "creation failed\n");
    vulkan_context_provider->Destroy();
    return 1;
  }

  gpu::GpuFeatureInfo gpu_feature_info;
  gpu::GpuDriverBugWorkarounds workarounds(
      gpu_feature_info.enabled_gpu_driver_bug_workarounds);
  scoped_refptr<gpu::SharedContextState> context_state =
      base::MakeRefCounted<gpu::SharedContextState>(
          share_group, gl_surface, gl_context,
          /*use_virtualized_gl_contexts=*/false, base::DoNothing(),
          gpu::GrContextType::kVulkan, vulkan_context_provider.get());
  const bool initialized = context_state->InitializeSkia(
      gpu_preferences, workarounds, /*gr_cache=*/nullptr,
      /*persistent_cache=*/nullptr, /*use_shader_cache_shm_count=*/nullptr,
      /*progress_reporter=*/nullptr);
  const bool has_vulkan_provider =
      context_state->vk_context_provider() == vulkan_context_provider.get();
  const bool is_vulkan = context_state->GrContextIsVulkan();
  const bool has_gr_context = context_state->gr_context() != nullptr;
  const size_t extension_count =
      vulkan_context_provider->GetDeviceQueue()
          ? vulkan_context_provider->GetDeviceQueue()->enabled_extensions().size()
          : 0u;

  context_state.reset();
  if (gl_context->IsCurrent(gl_surface.get()))
    gl_context->ReleaseCurrent(gl_surface.get());
  vulkan_context_provider->Destroy();

  if (!initialized || !has_vulkan_provider || !is_vulkan || !has_gr_context) {
    std::fprintf(stderr,
                 "gpu_vulkan_ganesh_context_smoke: failed initialized=%d "
                 "vk_provider=%d is_vulkan=%d gr_context=%d extensions=%zu\n",
                 initialized ? 1 : 0, has_vulkan_provider ? 1 : 0,
                 is_vulkan ? 1 : 0, has_gr_context ? 1 : 0, extension_count);
    return 1;
  }

  std::printf(
      "gpu_vulkan_ganesh_context_smoke: ok initialized=%d vk_provider=%d "
      "is_vulkan=%d gr_context=%d extensions=%zu offscreen=1 "
      "viz_runtime=not_wired\n",
      initialized ? 1 : 0, has_vulkan_provider ? 1 : 0,
      is_vulkan ? 1 : 0, has_gr_context ? 1 : 0, extension_count);
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
        arg == "--c-api-resource-provider-smoke" ||
        arg == "--c-api-resource-provider-data-url-smoke" ||
        arg == "--c-api-resource-provider-font-smoke" ||
        arg == "--c-api-resource-provider-mask-svg-smoke" ||
        arg == "--c-api-resource-provider-free-then-mask-smoke" ||
        arg == "--c-api-full-viewport-button-hit-metadata-smoke" ||
        arg == "--c-api-empty-resource-smoke" ||
        arg == "--c-api-transparent-background-smoke" ||
        arg == "--c-api-css-filter-blur-smoke" ||
        arg == "--c-api-backdrop-filter-region-smoke" ||
        arg == "--c-api-backdrop-filter-rounded-smoke" ||
        arg == "--c-api-backdrop-filter-chain-smoke" ||
        arg == "--c-api-backdrop-filter-unsupported-smoke" ||
        arg == "--c-api-vulkan-external-target-large-smoke" ||
        arg == "--c-api-vulkan-external-target-resize-smoke" ||
        arg == "--c-api-vulkan-external-target-pending-resize-smoke" ||
        arg == "--c-api-vulkan-external-target-fps-timing-smoke" ||
        arg == "--c-api-vulkan-external-target-click-timing-smoke" ||
        arg == "--c-api-vulkan-external-target-click-resize-pending-smoke" ||
        arg ==
            "--c-api-vulkan-external-target-full-viewport-button-hit-metadata-smoke" ||
        arg == "--c-api-vulkan-invalid-target-metadata-smoke" ||
        arg == "--c-api-d3d12-external-target-resize-smoke" ||
        arg == "--c-api-d3d12-external-target-click-timing-smoke" ||
        arg == "--c-api-d3d12-external-target-click-resize-smoke" ||
        arg == "--c-api-d3d12-external-target-button-activation-smoke" ||
        arg ==
            "--c-api-d3d12-external-target-full-viewport-button-hit-metadata-smoke" ||
        arg == "--c-api-d3d12-external-target-repeated-frame-smoke" ||
        arg == "--c-api-vulkan-update-output-smoke" ||
        arg == "--c-api-d3d12-update-output-smoke" ||
        arg == "--c-api-separated-click-smoke" ||
        arg == "--c-api-frame-scheduling-smoke" ||
        arg == "--c-api-dom-mutation-smoke" ||
        arg == "--c-api-fragment-mutation-smoke" ||
        arg == "--c-api-structural-dom-mutation-smoke" ||
        arg == "--c-api-mutation-diagnostics-smoke" ||
        arg == "--c-api-mutation-stress-smoke" ||
        arg == "--c-api-body-mutation-smoke" ||
        arg == "--c-api-text-input-smoke" ||
        arg == "--c-api-form-control-mutation-smoke" ||
        arg == "--c-api-absolute-form-mutation-smoke" ||
        arg == "--c-api-slider-form-state-smoke" ||
        arg == "--c-api-select-form-state-smoke" ||
        arg == "--c-api-multiselect-form-state-smoke" ||
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
  if (!base::ThreadPoolInstance::Get()) {
    base::ThreadPoolInstance::CreateAndStartWithDefaultParams(
        "blink_standalone_render_benchmark");
  }
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
  bool gpu_output_smoke = false;
  bool gpu_output_vulkan_smoke = false;
  bool gpu_output_vulkan_pixel_smoke = false;
  bool gpu_output_d3d12_pixel_smoke = false;
  bool gpu_output_d3d12_render_pixel_smoke = false;
  bool gpu_borrowed_vkimage_backing_smoke = false;
  bool gpu_borrowed_vkimage_render_copy_smoke = false;
  bool gpu_external_vulkan_runtime_target_smoke = false;
  bool gpu_borrowed_d3d12_render_copy_smoke = false;
  bool gpu_external_vulkan_device_smoke = false;
  bool gpu_vulkan_ganesh_context_smoke = false;
  bool c_api_vulkan_external_target_smoke = false;
  bool c_api_vulkan_external_target_large_smoke = false;
  bool c_api_vulkan_external_target_resize_smoke = false;
  bool c_api_vulkan_external_target_rapid_resize_smoke = false;
  bool c_api_vulkan_external_target_pending_resize_smoke = false;
  bool c_api_vulkan_external_target_fps_timing_smoke = false;
  bool c_api_vulkan_external_target_click_timing_smoke = false;
  bool c_api_vulkan_external_target_click_resize_pending_smoke = false;
  bool c_api_vulkan_external_target_full_viewport_button_hit_metadata_smoke =
      false;
  bool c_api_vulkan_invalid_target_metadata_smoke = false;
  bool c_api_d3d12_external_target_smoke = false;
  bool c_api_d3d12_external_target_resize_smoke = false;
  bool c_api_d3d12_external_target_click_timing_smoke = false;
  bool c_api_d3d12_external_target_click_resize_smoke = false;
  bool c_api_d3d12_external_target_button_activation_smoke = false;
  bool c_api_d3d12_external_target_full_viewport_button_hit_metadata_smoke =
      false;
  bool c_api_d3d12_external_target_repeated_frame_smoke = false;
  bool c_api_vulkan_update_output_smoke = false;
  bool c_api_d3d12_update_output_smoke = false;
  bool c_api_vulkan_external_target_current_document_smoke = false;
  bool c_api_d3d12_external_target_current_document_smoke = false;
  bool c_api_d3d12_external_target_filter_backdrop_smoke = false;
  bool c_api_d3d12_external_target_transparent_filter_backdrop_smoke = false;
  bool c_api_smoke = false;
  bool c_api_viewport_resize_smoke = false;
  bool c_api_resource_provider_smoke = false;
  bool c_api_resource_provider_data_url_smoke = false;
  bool c_api_resource_provider_font_smoke = false;
  bool c_api_resource_provider_mask_svg_smoke = false;
  bool c_api_resource_provider_free_then_mask_smoke = false;
  bool c_api_full_viewport_button_hit_metadata_smoke = false;
  bool c_api_empty_resource_smoke = false;
  bool c_api_transparent_background_smoke = false;
  bool c_api_css_filter_blur_smoke = false;
  bool c_api_backdrop_filter_region_smoke = false;
  bool c_api_backdrop_filter_rounded_smoke = false;
  bool c_api_backdrop_filter_chain_smoke = false;
  bool c_api_backdrop_filter_unsupported_smoke = false;
  bool c_api_separated_click_smoke = false;
  bool c_api_frame_scheduling_smoke = false;
  bool c_api_dom_mutation_smoke = false;
  bool c_api_fragment_mutation_smoke = false;
  bool c_api_structural_dom_mutation_smoke = false;
  bool c_api_mutation_diagnostics_smoke = false;
  bool c_api_mutation_stress_smoke = false;
  bool c_api_body_mutation_smoke = false;
  bool c_api_text_input_smoke = false;
  bool c_api_form_control_mutation_smoke = false;
  bool c_api_absolute_form_mutation_smoke = false;
  bool c_api_slider_form_state_smoke = false;
  bool c_api_select_form_state_smoke = false;
  bool c_api_multiselect_form_state_smoke = false;
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
    } else if (arg == "--gpu-output-smoke") {
      gpu_output_smoke = true;
    } else if (arg == "--gpu-output-vulkan-smoke") {
      gpu_output_vulkan_smoke = true;
    } else if (arg == "--gpu-output-vulkan-pixel-smoke") {
      gpu_output_vulkan_pixel_smoke = true;
    } else if (arg == "--gpu-output-d3d12-pixel-smoke") {
      gpu_output_d3d12_pixel_smoke = true;
    } else if (arg == "--gpu-output-d3d12-render-pixel-smoke") {
      gpu_output_d3d12_render_pixel_smoke = true;
    } else if (arg == "--gpu-borrowed-vkimage-backing-smoke") {
      gpu_borrowed_vkimage_backing_smoke = true;
    } else if (arg == "--gpu-borrowed-vkimage-render-copy-smoke") {
      gpu_borrowed_vkimage_render_copy_smoke = true;
    } else if (arg == "--gpu-external-vulkan-runtime-target-smoke") {
      gpu_external_vulkan_runtime_target_smoke = true;
    } else if (arg == "--gpu-borrowed-d3d12-render-copy-smoke") {
      gpu_borrowed_d3d12_render_copy_smoke = true;
    } else if (arg == "--gpu-external-vulkan-device-smoke") {
      gpu_external_vulkan_device_smoke = true;
    } else if (arg == "--gpu-vulkan-ganesh-context-smoke") {
      gpu_vulkan_ganesh_context_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-smoke") {
      c_api_vulkan_external_target_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-large-smoke") {
      c_api_vulkan_external_target_large_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-resize-smoke") {
      c_api_vulkan_external_target_resize_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-rapid-resize-smoke") {
      c_api_vulkan_external_target_rapid_resize_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-pending-resize-smoke") {
      c_api_vulkan_external_target_pending_resize_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-fps-timing-smoke") {
      c_api_vulkan_external_target_fps_timing_smoke = true;
    } else if (arg == "--c-api-vulkan-external-target-click-timing-smoke") {
      c_api_vulkan_external_target_click_timing_smoke = true;
    } else if (
        arg == "--c-api-vulkan-external-target-click-resize-pending-smoke") {
      c_api_vulkan_external_target_click_resize_pending_smoke = true;
    } else if (
        arg ==
        "--c-api-vulkan-external-target-full-viewport-button-hit-metadata-smoke") {
      c_api_vulkan_external_target_full_viewport_button_hit_metadata_smoke =
          true;
    } else if (arg == "--c-api-vulkan-invalid-target-metadata-smoke") {
      c_api_vulkan_invalid_target_metadata_smoke = true;
    } else if (arg == "--c-api-d3d12-external-target-smoke") {
      c_api_d3d12_external_target_smoke = true;
    } else if (arg == "--c-api-d3d12-external-target-resize-smoke") {
      c_api_d3d12_external_target_resize_smoke = true;
    } else if (arg == "--c-api-d3d12-external-target-click-timing-smoke") {
      c_api_d3d12_external_target_click_timing_smoke = true;
    } else if (
        arg == "--c-api-d3d12-external-target-click-resize-smoke") {
      c_api_d3d12_external_target_click_resize_smoke = true;
    } else if (
        arg == "--c-api-d3d12-external-target-button-activation-smoke") {
      c_api_d3d12_external_target_button_activation_smoke = true;
    } else if (
        arg ==
        "--c-api-d3d12-external-target-full-viewport-button-hit-metadata-smoke") {
      c_api_d3d12_external_target_full_viewport_button_hit_metadata_smoke =
          true;
    } else if (
        arg == "--c-api-d3d12-external-target-repeated-frame-smoke") {
      c_api_d3d12_external_target_repeated_frame_smoke = true;
    } else if (arg == "--c-api-vulkan-update-output-smoke") {
      c_api_vulkan_update_output_smoke = true;
    } else if (arg == "--c-api-d3d12-update-output-smoke") {
      c_api_d3d12_update_output_smoke = true;
    } else if (arg ==
               "--c-api-vulkan-external-target-current-document-smoke") {
      c_api_vulkan_external_target_current_document_smoke = true;
    } else if (arg ==
               "--c-api-d3d12-external-target-current-document-smoke") {
      c_api_d3d12_external_target_current_document_smoke = true;
    } else if (arg ==
               "--c-api-d3d12-external-target-filter-backdrop-smoke") {
      c_api_d3d12_external_target_filter_backdrop_smoke = true;
    } else if (
        arg ==
        "--c-api-d3d12-external-target-transparent-filter-backdrop-smoke") {
      c_api_d3d12_external_target_transparent_filter_backdrop_smoke = true;
    } else if (arg == "--c-api-smoke") {
      c_api_smoke = true;
    } else if (arg == "--c-api-viewport-resize-smoke") {
      c_api_viewport_resize_smoke = true;
    } else if (arg == "--c-api-resource-provider-smoke") {
      c_api_resource_provider_smoke = true;
    } else if (arg == "--c-api-resource-provider-data-url-smoke") {
      c_api_resource_provider_data_url_smoke = true;
    } else if (arg == "--c-api-resource-provider-font-smoke") {
      c_api_resource_provider_font_smoke = true;
    } else if (arg == "--c-api-resource-provider-mask-svg-smoke") {
      c_api_resource_provider_mask_svg_smoke = true;
    } else if (arg == "--c-api-resource-provider-free-then-mask-smoke") {
      c_api_resource_provider_free_then_mask_smoke = true;
    } else if (arg == "--c-api-full-viewport-button-hit-metadata-smoke") {
      c_api_full_viewport_button_hit_metadata_smoke = true;
    } else if (arg == "--c-api-empty-resource-smoke") {
      c_api_empty_resource_smoke = true;
    } else if (arg == "--c-api-transparent-background-smoke") {
      c_api_transparent_background_smoke = true;
    } else if (arg == "--c-api-css-filter-blur-smoke") {
      c_api_css_filter_blur_smoke = true;
    } else if (arg == "--c-api-backdrop-filter-region-smoke") {
      c_api_backdrop_filter_region_smoke = true;
    } else if (arg == "--c-api-backdrop-filter-rounded-smoke") {
      c_api_backdrop_filter_rounded_smoke = true;
    } else if (arg == "--c-api-backdrop-filter-chain-smoke") {
      c_api_backdrop_filter_chain_smoke = true;
    } else if (arg == "--c-api-backdrop-filter-unsupported-smoke") {
      c_api_backdrop_filter_unsupported_smoke = true;
    } else if (arg == "--c-api-separated-click-smoke") {
      c_api_separated_click_smoke = true;
    } else if (arg == "--c-api-frame-scheduling-smoke") {
      c_api_frame_scheduling_smoke = true;
    } else if (arg == "--c-api-dom-mutation-smoke") {
      c_api_dom_mutation_smoke = true;
    } else if (arg == "--c-api-fragment-mutation-smoke") {
      c_api_fragment_mutation_smoke = true;
    } else if (arg == "--c-api-structural-dom-mutation-smoke") {
      c_api_structural_dom_mutation_smoke = true;
    } else if (arg == "--c-api-mutation-diagnostics-smoke") {
      c_api_mutation_diagnostics_smoke = true;
    } else if (arg == "--c-api-mutation-stress-smoke") {
      c_api_mutation_stress_smoke = true;
    } else if (arg == "--c-api-body-mutation-smoke") {
      c_api_body_mutation_smoke = true;
    } else if (arg == "--c-api-text-input-smoke") {
      c_api_text_input_smoke = true;
    } else if (arg == "--c-api-form-control-mutation-smoke") {
      c_api_form_control_mutation_smoke = true;
    } else if (arg == "--c-api-absolute-form-mutation-smoke") {
      c_api_absolute_form_mutation_smoke = true;
    } else if (arg == "--c-api-slider-form-state-smoke") {
      c_api_slider_form_state_smoke = true;
    } else if (arg == "--c-api-select-form-state-smoke") {
      c_api_select_form_state_smoke = true;
    } else if (arg == "--c-api-multiselect-form-state-smoke") {
      c_api_multiselect_form_state_smoke = true;
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

  if (gpu_output_smoke) {
    return RunGpuOutputSmoke();
  }

  if (gpu_output_vulkan_smoke) {
    return RunGpuOutputVulkanSmoke();
  }

  if (gpu_output_vulkan_pixel_smoke) {
    return RunGpuOutputVulkanPixelSmoke();
  }

  if (gpu_output_d3d12_pixel_smoke) {
    return RunGpuOutputD3D12PixelSmoke();
  }

  if (gpu_output_d3d12_render_pixel_smoke) {
    return RunGpuOutputD3D12RenderPixelSmoke();
  }

  if (gpu_borrowed_vkimage_backing_smoke) {
    return RunGpuBorrowedVkImageBackingSmoke();
  }

  if (gpu_borrowed_vkimage_render_copy_smoke) {
    return RunGpuBorrowedVkImageRenderCopySmoke();
  }

  if (gpu_external_vulkan_runtime_target_smoke) {
    return RunGpuExternalVulkanRuntimeTargetSmoke();
  }

  if (gpu_borrowed_d3d12_render_copy_smoke) {
    return RunGpuBorrowedD3D12RenderCopySmoke();
  }

  if (gpu_external_vulkan_device_smoke) {
    return RunGpuExternalVulkanDeviceSmoke();
  }

  if (gpu_vulkan_ganesh_context_smoke) {
    return RunGpuVulkanGaneshContextSmoke();
  }

  if (c_api_vulkan_external_target_smoke) {
    return RunCApiVulkanExternalTargetSmoke();
  }

  if (c_api_vulkan_external_target_large_smoke) {
    return RunCApiVulkanExternalTargetLargeSmoke();
  }

  if (c_api_vulkan_external_target_resize_smoke) {
    return RunCApiVulkanExternalTargetResizeSmoke();
  }

  if (c_api_vulkan_external_target_rapid_resize_smoke) {
    return RunCApiVulkanExternalTargetRapidResizeSmoke();
  }

  if (c_api_vulkan_external_target_pending_resize_smoke) {
    return RunCApiVulkanExternalTargetPendingResizeSmoke();
  }

  if (c_api_vulkan_external_target_fps_timing_smoke) {
    return RunCApiVulkanExternalTargetFpsTimingSmoke();
  }

  if (c_api_vulkan_external_target_click_timing_smoke) {
    return RunCApiVulkanExternalTargetClickTimingSmoke();
  }

  if (c_api_vulkan_external_target_click_resize_pending_smoke) {
    return RunCApiVulkanExternalTargetClickResizePendingSmoke();
  }

  if (c_api_vulkan_external_target_full_viewport_button_hit_metadata_smoke) {
    return RunCApiVulkanExternalTargetFullViewportButtonHitMetadataSmoke();
  }

  if (c_api_vulkan_invalid_target_metadata_smoke) {
    return RunCApiVulkanInvalidTargetMetadataSmoke();
  }

  if (c_api_d3d12_external_target_smoke) {
    return RunCApiD3D12ExternalTargetSmoke();
  }

  if (c_api_d3d12_external_target_resize_smoke) {
    return RunCApiD3D12ExternalTargetResizeSmoke();
  }

  if (c_api_d3d12_external_target_click_timing_smoke) {
    return RunCApiD3D12ExternalTargetClickTimingSmoke();
  }

  if (c_api_d3d12_external_target_click_resize_smoke) {
    return RunCApiD3D12ExternalTargetClickResizeSmoke();
  }

  if (c_api_d3d12_external_target_button_activation_smoke) {
    return RunCApiD3D12ExternalTargetButtonActivationSmoke();
  }

  if (c_api_d3d12_external_target_full_viewport_button_hit_metadata_smoke) {
    return RunCApiD3D12ExternalTargetFullViewportButtonHitMetadataSmoke();
  }

  if (c_api_d3d12_external_target_repeated_frame_smoke) {
    return RunCApiD3D12ExternalTargetRepeatedFrameSmoke();
  }

  if (c_api_vulkan_update_output_smoke) {
    return RunCApiVulkanUpdateOutputSmoke();
  }

  if (c_api_d3d12_update_output_smoke) {
    return RunCApiD3D12UpdateOutputSmoke();
  }

  if (c_api_vulkan_external_target_current_document_smoke) {
    return RunCApiVulkanExternalTargetCurrentDocumentSmoke();
  }

  if (c_api_d3d12_external_target_current_document_smoke) {
    return RunCApiD3D12ExternalTargetCurrentDocumentSmoke();
  }

  if (c_api_d3d12_external_target_filter_backdrop_smoke) {
    return RunCApiD3D12ExternalTargetFilterBackdropSmoke();
  }

  if (c_api_d3d12_external_target_transparent_filter_backdrop_smoke) {
    return RunCApiD3D12ExternalTargetTransparentFilterBackdropSmoke();
  }

  if (c_api_smoke) {
    return RunCApiSmoke();
  }

  if (c_api_viewport_resize_smoke) {
    return RunCApiViewportResizeSmoke();
  }

  if (c_api_resource_provider_smoke) {
    return RunCApiResourceProviderSmoke();
  }

  if (c_api_resource_provider_data_url_smoke) {
    return RunCApiResourceProviderDataUrlSmoke();
  }

  if (c_api_resource_provider_font_smoke) {
    return RunCApiResourceProviderFontSmoke();
  }

  if (c_api_resource_provider_mask_svg_smoke) {
    return RunCApiResourceProviderMaskSvgSmoke();
  }

  if (c_api_resource_provider_free_then_mask_smoke) {
    return RunCApiResourceProviderFreeThenMaskSmoke();
  }

  if (c_api_full_viewport_button_hit_metadata_smoke) {
    return RunCApiFullViewportButtonHitMetadataSmoke();
  }

  if (c_api_empty_resource_smoke) {
    return RunCApiEmptyResourceSmoke();
  }

  if (c_api_transparent_background_smoke) {
    return RunCApiTransparentBackgroundSmoke();
  }

  if (c_api_css_filter_blur_smoke) {
    return RunCApiCssFilterBlurSmoke();
  }

  if (c_api_backdrop_filter_region_smoke) {
    return RunCApiBackdropFilterRegionSmoke();
  }

  if (c_api_backdrop_filter_rounded_smoke) {
    return RunCApiBackdropFilterRoundedSmoke();
  }

  if (c_api_backdrop_filter_chain_smoke) {
    return RunCApiBackdropFilterChainSmoke();
  }

  if (c_api_backdrop_filter_unsupported_smoke) {
    return RunCApiBackdropFilterUnsupportedSmoke();
  }

  if (c_api_separated_click_smoke) {
    return RunCApiSeparatedClickSmoke();
  }

  if (c_api_frame_scheduling_smoke) {
    return RunCApiFrameSchedulingSmoke();
  }

  if (c_api_dom_mutation_smoke) {
    return RunCApiDomMutationSmoke();
  }

  if (c_api_fragment_mutation_smoke) {
    return RunCApiFragmentMutationSmoke();
  }

  if (c_api_structural_dom_mutation_smoke) {
    return RunCApiStructuralDomMutationSmoke();
  }

  if (c_api_mutation_diagnostics_smoke) {
    return RunCApiMutationDiagnosticsSmoke();
  }

  if (c_api_mutation_stress_smoke) {
    return RunCApiMutationStressSmoke();
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

  if (c_api_slider_form_state_smoke) {
    return RunCApiSliderFormStateSmoke();
  }

  if (c_api_select_form_state_smoke) {
    return RunCApiSelectFormStateSmoke();
  }

  if (c_api_multiselect_form_state_smoke) {
    return RunCApiMultiSelectFormStateSmoke();
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
