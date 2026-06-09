#include <SDL3/SDL.h>

#if defined(_WIN32)
#include <windows.h>
#include <shobjidl.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cctype>
#include <array>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

#include "html_css_renderer/blink_adapter.h"
#include "html_css_renderer/cpu_renderer.h"
#include "html_css_renderer/css_file_loader.h"
#include "html_css_renderer/draw_command_serializer.h"
#include "html_css_renderer/renderer.h"
#include "html_css_renderer/standalone_resource_provider.h"
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
#include "html_css_renderer/skia_cpu_renderer.h"
#endif

namespace {

namespace fs = std::filesystem;

class EmptyAssets final : public html_css_renderer::AssetProvider {
 public:
  std::optional<html_css_renderer::Asset> Load(
      const std::string& resource_id) override {
    if (!font_bytes.empty() && resource_id == "viewer-font.ttf") {
      html_css_renderer::Asset asset;
      asset.id = resource_id;
      asset.mime_type = "font/ttf";
      asset.bytes = font_bytes;
      return asset;
    }
    return std::nullopt;
  }

  std::vector<uint8_t> font_bytes;
};

std::vector<uint8_t> ReadBinaryFile(const std::string& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return {};
  }
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>());
}

std::optional<std::string> ReadTextFile(const fs::path& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return std::nullopt;
  }
  return std::string(std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>());
}

std::string ToLowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return value;
}

std::string FileUrlForDirectory(const fs::path& directory) {
  std::string path = fs::absolute(directory).generic_string();
  if (!path.empty() && path.back() != '/') {
    path.push_back('/');
  }
  return "file:///" + path;
}

std::string InjectBaseHrefForHtmlFile(const std::string& html_path,
                                      std::string html) {
  const std::string lower = ToLowerAscii(html);
  if (lower.find("<base") != std::string::npos) {
    return html;
  }
  const std::string base =
      "<base href=\"" +
      FileUrlForDirectory(fs::absolute(fs::path(html_path)).parent_path()) +
      "\">\n";
  const size_t head = lower.find("<head");
  if (head != std::string::npos) {
    const size_t head_end = lower.find('>', head);
    if (head_end != std::string::npos) {
      html.insert(head_end + 1, "\n" + base);
      return html;
    }
  }
  html.insert(0, base);
  return html;
}

enum class ResourceRootPolicy {
  kUseHtmlDirectory,
  kUseHtmlDirectoryIfUnset,
};

bool LoadHtmlFileForViewer(
    const fs::path& html_path,
    ResourceRootPolicy resource_root_policy,
    html_css_renderer::RendererCreateInfo* create_info,
    std::string* resource_root,
    std::string* resource_base_path,
    std::vector<std::string>* stylesheet_loader_diagnostics) {
  std::optional<std::string> html = ReadTextFile(html_path);
  if (!html) {
    std::fprintf(stderr, "failed to read html file: %s\n",
                 html_path.string().c_str());
    return false;
  }
  const fs::path absolute_html_path = fs::absolute(html_path);
  create_info->html =
      InjectBaseHrefForHtmlFile(absolute_html_path.string(), std::move(*html));
  *resource_base_path = absolute_html_path.parent_path().string();
  if (resource_root_policy == ResourceRootPolicy::kUseHtmlDirectory ||
      resource_root->empty()) {
    *resource_root = *resource_base_path;
  }
  html_css_renderer::AddLocalLinkedStylesheetsForDocument(
      absolute_html_path, create_info->html, create_info,
      stylesheet_loader_diagnostics);
  return true;
}

#if defined(_WIN32)
std::optional<fs::path> ShowNativeHtmlFileDialog() {
  HRESULT initialize_result =
      CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED |
                                  COINIT_DISABLE_OLE1DDE);
  const bool should_uninitialize = SUCCEEDED(initialize_result);
  if (initialize_result == RPC_E_CHANGED_MODE) {
    initialize_result = S_OK;
  }
  if (FAILED(initialize_result)) {
    std::fprintf(stderr, "failed to initialize file dialog COM: 0x%08lx\n",
                 static_cast<unsigned long>(initialize_result));
    return std::nullopt;
  }

  IFileOpenDialog* dialog = nullptr;
  HRESULT result = CoCreateInstance(CLSID_FileOpenDialog, nullptr,
                                    CLSCTX_INPROC_SERVER,
                                    IID_PPV_ARGS(&dialog));
  if (FAILED(result)) {
    std::fprintf(stderr, "failed to create file dialog: 0x%08lx\n",
                 static_cast<unsigned long>(result));
    if (should_uninitialize) {
      CoUninitialize();
    }
    return std::nullopt;
  }

  COMDLG_FILTERSPEC filters[] = {
      {L"HTML files", L"*.html;*.htm"},
      {L"All files", L"*.*"},
  };
  dialog->SetTitle(L"Open HTML file");
  dialog->SetFileTypes(static_cast<UINT>(std::size(filters)), filters);
  dialog->SetFileTypeIndex(1);
  DWORD options = 0;
  if (SUCCEEDED(dialog->GetOptions(&options))) {
    dialog->SetOptions(options | FOS_FORCEFILESYSTEM | FOS_FILEMUSTEXIST |
                       FOS_PATHMUSTEXIST);
  }

  result = dialog->Show(nullptr);
  if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
    dialog->Release();
    if (should_uninitialize) {
      CoUninitialize();
    }
    return std::nullopt;
  }
  if (FAILED(result)) {
    std::fprintf(stderr, "file dialog failed: 0x%08lx\n",
                 static_cast<unsigned long>(result));
    dialog->Release();
    if (should_uninitialize) {
      CoUninitialize();
    }
    return std::nullopt;
  }

  IShellItem* item = nullptr;
  result = dialog->GetResult(&item);
  if (FAILED(result) || !item) {
    std::fprintf(stderr, "file dialog result failed: 0x%08lx\n",
                 static_cast<unsigned long>(result));
    dialog->Release();
    if (should_uninitialize) {
      CoUninitialize();
    }
    return std::nullopt;
  }

  PWSTR selected_path = nullptr;
  result = item->GetDisplayName(SIGDN_FILESYSPATH, &selected_path);
  std::optional<fs::path> path;
  if (SUCCEEDED(result) && selected_path) {
    path = fs::path(selected_path);
    CoTaskMemFree(selected_path);
  } else {
    std::fprintf(stderr, "file dialog path conversion failed: 0x%08lx\n",
                 static_cast<unsigned long>(result));
  }
  item->Release();
  dialog->Release();
  if (should_uninitialize) {
    CoUninitialize();
  }
  return path;
}
#else
std::optional<fs::path> ShowNativeHtmlFileDialog() {
  std::fprintf(stderr,
               "no native file dialog is wired for this platform; pass "
               "--html-file <path>\n");
  return std::nullopt;
}
#endif

bool ParseFloat(const std::string& value, float* output) {
  char* end = nullptr;
  const float parsed = std::strtof(value.c_str(), &end);
  if (end == value.c_str() || *end != '\0') {
    return false;
  }
  *output = parsed;
  return true;
}

bool ParseDouble(const std::string& value, double* output) {
  char* end = nullptr;
  const double parsed = std::strtod(value.c_str(), &end);
  if (end == value.c_str() || *end != '\0') {
    return false;
  }
  *output = parsed;
  return true;
}

bool ParseViewport(const std::string& value, html_css_renderer::Size* output) {
  const size_t separator = value.find('x');
  if (separator == std::string::npos) {
    return false;
  }
  float width = 0.0f;
  float height = 0.0f;
  if (!ParseFloat(value.substr(0, separator), &width) ||
      !ParseFloat(value.substr(separator + 1), &height)) {
    return false;
  }
  output->width = width;
  output->height = height;
  return true;
}

bool ParseElementAttributeOverride(const std::string& value,
                                   std::string* key,
                                   std::string* attribute_value) {
  const size_t colon = value.find(':');
  const size_t equals =
      value.find('=', colon == std::string::npos ? 0 : colon + 1);
  if (colon == std::string::npos || equals == std::string::npos || colon == 0 ||
      equals <= colon + 1) {
    return false;
  }
  *key = value.substr(0, equals);
  *attribute_value = value.substr(equals + 1);
  return true;
}

struct AttributeToggle {
  std::string key;
  std::string off_value;
  std::string on_value;
  bool is_on = false;
};

std::string AttributeToggleElementId(const AttributeToggle& toggle) {
  const size_t separator = toggle.key.find(':');
  return separator == std::string::npos ? std::string()
                                        : toggle.key.substr(0, separator);
}

bool ParseAttributeToggle(const std::string& value,
                          AttributeToggle* toggle) {
  std::string key;
  std::string values;
  if (!ParseElementAttributeOverride(value, &key, &values)) {
    return false;
  }
  const size_t comma = values.find(',');
  if (comma == std::string::npos || comma == 0 || comma + 1 >= values.size()) {
    return false;
  }
  toggle->key = key;
  toggle->off_value = values.substr(0, comma);
  toggle->on_value = values.substr(comma + 1);
  return true;
}

void PrintUsage() {
  std::fprintf(stderr,
               "Usage: html_css_renderer_sdl_viewer --html <html> "
               "[--html-file <path>] [--css <css>] [--css-file <path>] "
               "[--attr id:name=value] "
               "[--toggle-attr id:name=off,on] "
               "[--resource-root <path>] "
               "[--scroll-x px] [--scroll-y px] [--scroll-step px] "
               "[--viewport WxH] [--delta seconds] "
               "[--font-file path] [--window-scale factor] "
               "[--quit-after-ms ms] [--incremental] [--no-incremental] "
               "[--cpu] [--skia-cpu] [--direct-sdl]"
               " [--dump-paint-artifact path]"
               " [--profile] [--profile-summary-frames count]"
               " [--profile-auto-scroll-frames count]"
               " [--profile-auto-scroll-step px]"
               " [--profile-resize-to WxH]"
               " [--profile-resize-after-frame count]"
               " [--blink]"
               "\nIf no --html or --html-file input is provided, the viewer "
               "opens a native HTML file picker.\n"
               "Defaults: Skia CPU rendering and incremental updates are "
               "enabled. Use --direct-sdl for the old SDL render-target path, "
               "--cpu for the generic CPU rasterizer, or --no-incremental for "
               "full render updates.\n"
               "Controls: Space/T toggle configured attrs, left click toggles "
               "matching targets, mouse wheel scrolls the document viewport, "
               "arrow/Page/Home keys scroll the document, "
               "Esc quits.\n");
}

bool ParseArgs(int argc,
               char** argv,
               html_css_renderer::RendererCreateInfo* create_info,
               html_css_renderer::FrameInput* input,
               uint64_t* quit_after_ms,
               float* window_scale,
               std::string* font_file,
               bool* incremental,
               bool* use_cpu,
               bool* use_skia_cpu,
               std::string* paint_artifact_dump_path,
               std::string* resource_root,
               std::string* resource_base_path,
               std::vector<AttributeToggle>* attribute_toggles,
               float* scroll_step,
               bool* profile_enabled,
               uint64_t* profile_summary_frames,
               uint64_t* profile_auto_scroll_frames,
               std::optional<float>* profile_auto_scroll_step,
               std::optional<html_css_renderer::Size>* profile_resize_to,
               uint64_t* profile_resize_after_frame,
               bool* use_blink,
               std::vector<std::string>* stylesheet_loader_diagnostics) {
  for (int i = 1; i < argc; ++i) {
    const std::string arg = argv[i];
    auto next_value = [&]() -> const char* {
      if (i + 1 >= argc) {
        return nullptr;
      }
      ++i;
      return argv[i];
    };

    if (arg == "--html") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      create_info->html = value;
    } else if (arg == "--html-file") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      if (!LoadHtmlFileForViewer(value, ResourceRootPolicy::kUseHtmlDirectory,
                                 create_info, resource_root,
                                 resource_base_path,
                                 stylesheet_loader_diagnostics)) {
        return false;
      }
    } else if (arg == "--resource-root") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      *resource_root = fs::absolute(value).string();
    } else if (arg == "--css") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      create_info->stylesheets.push_back({"viewer", value});
      html_css_renderer::AppendUnsupportedCssImportDiagnostic(
          value, "viewer", stylesheet_loader_diagnostics);
    } else if (arg == "--css-file") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      const fs::path css_path = value;
      const fs::path absolute_css_path = fs::absolute(css_path);
      const fs::path document_base =
          resource_base_path->empty() ? absolute_css_path.parent_path()
                                      : fs::path(*resource_base_path);
      std::optional<html_css_renderer::Stylesheet> stylesheet =
          html_css_renderer::LoadStylesheetFileForDocument(
              css_path, document_base, stylesheet_loader_diagnostics);
      if (!stylesheet) {
        std::fprintf(stderr, "failed to read css file: %s\n", value);
        return false;
      }
      create_info->stylesheets.push_back(std::move(*stylesheet));
    } else if (arg == "--viewport") {
      const char* value = next_value();
      if (!value || !ParseViewport(value, &create_info->viewport)) {
        return false;
      }
    } else if (arg == "--attr") {
      const char* value = next_value();
      std::string key;
      std::string attribute_value;
      if (!value ||
          !ParseElementAttributeOverride(value, &key, &attribute_value)) {
        return false;
      }
      input->element_attributes_by_id_and_name[key] = attribute_value;
    } else if (arg == "--toggle-attr") {
      const char* value = next_value();
      AttributeToggle toggle;
      if (!value || !ParseAttributeToggle(value, &toggle)) {
        return false;
      }
      if (input->element_attributes_by_id_and_name.find(toggle.key) ==
          input->element_attributes_by_id_and_name.end()) {
        input->element_attributes_by_id_and_name[toggle.key] =
            toggle.off_value;
      }
      attribute_toggles->push_back(std::move(toggle));
    } else if (arg == "--scroll-x") {
      const char* value = next_value();
      float scroll_x = 0.0f;
      if (!value || !ParseFloat(value, &scroll_x)) {
        return false;
      }
      input->scroll_offsets_by_element_id["document"].x = scroll_x;
    } else if (arg == "--scroll-y") {
      const char* value = next_value();
      float scroll_y = 0.0f;
      if (!value || !ParseFloat(value, &scroll_y)) {
        return false;
      }
      input->scroll_offsets_by_element_id["document"].y = scroll_y;
    } else if (arg == "--scroll-step") {
      const char* value = next_value();
      float parsed = 0.0f;
      if (!value || !ParseFloat(value, &parsed) || parsed <= 0.0f ||
          parsed > 10000.0f) {
        return false;
      }
      *scroll_step = parsed;
    } else if (arg == "--delta") {
      const char* value = next_value();
      if (!value || !ParseDouble(value, &input->delta_time_seconds)) {
        return false;
      }
    } else if (arg == "--quit-after-ms") {
      const char* value = next_value();
      double parsed = 0.0;
      if (!value || !ParseDouble(value, &parsed) || parsed < 0.0) {
        return false;
      }
      *quit_after_ms = static_cast<uint64_t>(parsed);
    } else if (arg == "--window-scale") {
      const char* value = next_value();
      float parsed = 0.0f;
      if (!value || !ParseFloat(value, &parsed) || parsed <= 0.0f ||
          parsed > 16.0f) {
        return false;
      }
      *window_scale = parsed;
    } else if (arg == "--font-file") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      *font_file = value;
    } else if (arg == "--incremental") {
      *incremental = true;
    } else if (arg == "--no-incremental") {
      *incremental = false;
    } else if (arg == "--cpu") {
      *use_cpu = true;
      *use_skia_cpu = false;
    } else if (arg == "--skia-cpu") {
      *use_skia_cpu = true;
      *use_cpu = true;
    } else if (arg == "--direct-sdl") {
      *use_skia_cpu = false;
      *use_cpu = false;
      *incremental = false;
    } else if (arg == "--dump-paint-artifact") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      *paint_artifact_dump_path = value;
    } else if (arg.rfind("--dump-paint-artifact=", 0) == 0) {
      *paint_artifact_dump_path = arg.substr(22);
    } else if (arg == "--profile") {
      *profile_enabled = true;
    } else if (arg == "--profile-summary-frames") {
      const char* value = next_value();
      double parsed = 0.0;
      if (!value || !ParseDouble(value, &parsed) || parsed < 0.0) {
        return false;
      }
      *profile_summary_frames = static_cast<uint64_t>(parsed);
    } else if (arg == "--profile-auto-scroll-frames") {
      const char* value = next_value();
      double parsed = 0.0;
      if (!value || !ParseDouble(value, &parsed) || parsed < 0.0) {
        return false;
      }
      *profile_auto_scroll_frames = static_cast<uint64_t>(parsed);
      *profile_enabled = true;
    } else if (arg == "--profile-auto-scroll-step") {
      const char* value = next_value();
      float parsed = 0.0f;
      if (!value || !ParseFloat(value, &parsed) ||
          std::abs(parsed) < 0.5f || std::abs(parsed) > 10000.0f) {
        return false;
      }
      *profile_auto_scroll_step = parsed;
    } else if (arg == "--profile-resize-to") {
      const char* value = next_value();
      html_css_renderer::Size parsed;
      if (!value || !ParseViewport(value, &parsed)) {
        return false;
      }
      *profile_resize_to = parsed;
      *profile_enabled = true;
    } else if (arg == "--profile-resize-after-frame") {
      const char* value = next_value();
      double parsed = 0.0;
      if (!value || !ParseDouble(value, &parsed) || parsed < 1.0) {
        return false;
      }
      *profile_resize_after_frame = static_cast<uint64_t>(parsed);
    } else if (arg == "--blink") {
      *use_blink = true;
    } else if (arg == "--manual") {
      std::fprintf(stderr,
                   "--manual is no longer supported; live Blink is required\n");
      return false;
    } else if (arg == "--help" || arg == "-h") {
      return false;
    } else {
      return false;
    }
  }
  return true;
}

struct ScrollDelta {
  float x = 0.0f;
  float y = 0.0f;
  bool home = false;
};

std::optional<ScrollDelta> KeyboardScrollDelta(SDL_Keycode key,
                                               float scroll_step,
                                               int frame_height) {
  const float page_step =
      std::max(scroll_step, std::max(1.0f, frame_height * 0.8f));
  switch (key) {
    case SDLK_LEFT:
      return ScrollDelta{-scroll_step, 0.0f, false};
    case SDLK_RIGHT:
      return ScrollDelta{scroll_step, 0.0f, false};
    case SDLK_UP:
      return ScrollDelta{0.0f, -scroll_step, false};
    case SDLK_DOWN:
      return ScrollDelta{0.0f, scroll_step, false};
    case SDLK_PAGEUP:
      return ScrollDelta{0.0f, -page_step, false};
    case SDLK_PAGEDOWN:
      return ScrollDelta{0.0f, page_step, false};
    case SDLK_HOME:
      return ScrollDelta{0.0f, 0.0f, true};
    default:
      return std::nullopt;
  }
}

float CurrentDocumentScrollX(const html_css_renderer::FrameInput& input) {
  const auto found = input.scroll_offsets_by_element_id.find("document");
  return found == input.scroll_offsets_by_element_id.end() ? 0.0f
                                                          : found->second.x;
}

float CurrentDocumentScrollY(const html_css_renderer::FrameInput& input) {
  const auto found = input.scroll_offsets_by_element_id.find("document");
  return found == input.scroll_offsets_by_element_id.end() ? 0.0f
                                                          : found->second.y;
}

void SetDocumentScroll(html_css_renderer::FrameInput* input,
                       float x,
                       float y) {
  html_css_renderer::Point& scroll =
      input->scroll_offsets_by_element_id["document"];
  scroll.x = std::max(0.0f, x);
  scroll.y = std::max(0.0f, y);
}

bool Contains(html_css_renderer::Rect rect, float x, float y);

using ProfileClock = std::chrono::steady_clock;

double ElapsedProfileMs(ProfileClock::time_point start,
                        ProfileClock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}

struct SdlProfileFrame {
  uint64_t frame = 0;
  std::string reason;
  bool incremental = false;
  double input_update_ms = 0.0;
  double blink_initialize_ms = 0.0;
  double blink_export_retained_ms = 0.0;
  double probe_html_document_setup_ms = 0.0;
  double probe_style_update_ms = 0.0;
  double probe_layout_lifecycle_ms = 0.0;
  double probe_prepaint_paint_lifecycle_ms = 0.0;
  double probe_paint_artifact_generation_ms = 0.0;
  double probe_paint_artifact_audit_json_ms = 0.0;
  double probe_paint_artifact_extraction_ms = 0.0;
  double probe_total_ms = 0.0;
  double cpu_replay_ms = 0.0;
  double pixel_convert_ms = 0.0;
  double texture_upload_ms = 0.0;
  double direct_render_ms = 0.0;
  double sdl_draw_present_ms = 0.0;
  double total_ms = 0.0;
  std::string cpu_replay_command_top;
};

double SdlProfileMeasuredSubtotal(const SdlProfileFrame& frame) {
  return frame.input_update_ms + frame.blink_initialize_ms +
         frame.blink_export_retained_ms + frame.cpu_replay_ms +
         frame.pixel_convert_ms + frame.texture_upload_ms +
         frame.direct_render_ms + frame.sdl_draw_present_ms;
}

struct PendingSdlProfileFrame {
  SdlProfileFrame frame;
  std::optional<ProfileClock::time_point> total_start;
};

std::optional<double> ExtractJsonNumberField(const std::string& json,
                                             const char* field_name) {
  const std::string needle = std::string("\"") + field_name + "\":";
  const size_t field = json.find(needle);
  if (field == std::string::npos) {
    return std::nullopt;
  }
  const char* begin = json.c_str() + field + needle.size();
  while (*begin == ' ' || *begin == '\t' || *begin == '\r' || *begin == '\n') {
    ++begin;
  }
  char* end = nullptr;
  const double value = std::strtod(begin, &end);
  if (end == begin) {
    return std::nullopt;
  }
  return value;
}

void PopulateProbeProfileTimings(
    const html_css_renderer::RenderResult& result,
    SdlProfileFrame* frame) {
  if (!frame || result.raw_paint_artifact_audit_json.empty()) {
    return;
  }
  const std::string& json = result.raw_paint_artifact_audit_json;
  auto set_if_present = [&](const char* name, double* target) {
    if (std::optional<double> value = ExtractJsonNumberField(json, name)) {
      *target = *value;
    }
  };
  set_if_present("html_parse_document_setup_ms",
                 &frame->probe_html_document_setup_ms);
  set_if_present("style_update_ms", &frame->probe_style_update_ms);
  set_if_present("layout_lifecycle_ms", &frame->probe_layout_lifecycle_ms);
  set_if_present("prepaint_paint_lifecycle_ms",
                 &frame->probe_prepaint_paint_lifecycle_ms);
  set_if_present("paint_artifact_generation_ms",
                 &frame->probe_paint_artifact_generation_ms);
  set_if_present("paint_artifact_audit_json_ms",
                 &frame->probe_paint_artifact_audit_json_ms);
  set_if_present("paint_artifact_extraction_ms",
                 &frame->probe_paint_artifact_extraction_ms);
  set_if_present("total_probe_ms", &frame->probe_total_ms);
}

std::string FormatCpuReplayCommandTimingTop(size_t max_records) {
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
  std::vector<html_css_renderer::CpuReplayCommandTimingRecord> records =
      html_css_renderer::SnapshotCpuReplayCommandTimingDiagnostics();
  std::sort(records.begin(), records.end(), [](const auto& left,
                                               const auto& right) {
    return left.elapsed_ms > right.elapsed_ms;
  });
  std::string output;
  size_t written = 0;
  for (const auto& record : records) {
    if (record.count == 0 || record.elapsed_ms <= 0.0) {
      continue;
    }
    if (written >= max_records) {
      break;
    }
    char buffer[160];
    std::snprintf(buffer, sizeof(buffer), "%s:%llux/%.3fms",
                  record.command_type.c_str(),
                  static_cast<unsigned long long>(record.count),
                  record.elapsed_ms);
    if (!output.empty()) {
      output += ",";
    }
    output += buffer;
    ++written;
  }
  return output;
#else
  (void)max_records;
  return {};
#endif
}

class SdlFrameProfiler {
 public:
  SdlFrameProfiler(bool enabled, uint64_t summary_interval)
      : enabled_(enabled), summary_interval_(summary_interval) {}

  bool enabled() const { return enabled_; }

  void Record(SdlProfileFrame frame) {
    if (!enabled_) {
      return;
    }
    if (frame.total_ms <= 0.0) {
      frame.total_ms = SdlProfileMeasuredSubtotal(frame);
    }
    PrintFrame(frame);
    frames_.push_back(std::move(frame));
    if (summary_interval_ > 0 &&
        frames_.size() % static_cast<size_t>(summary_interval_) == 0) {
      PrintSummary("interval");
    }
  }

  void PrintSummary(const char* label) const {
    if (!enabled_ || frames_.empty()) {
      return;
    }
    std::fprintf(stderr, "viewer profile summary: %s frames=%zu\n", label,
                 frames_.size());
    PrintMetric("input_update", [](const SdlProfileFrame& frame) {
      return frame.input_update_ms;
    });
    PrintMetric("blink_init", [](const SdlProfileFrame& frame) {
      return frame.blink_initialize_ms;
    });
    PrintMetric("blink_export_retained", [](const SdlProfileFrame& frame) {
      return frame.blink_export_retained_ms;
    });
    PrintMetric("probe_html_document_setup", [](const SdlProfileFrame& frame) {
      return frame.probe_html_document_setup_ms;
    });
    PrintMetric("probe_style_update", [](const SdlProfileFrame& frame) {
      return frame.probe_style_update_ms;
    });
    PrintMetric("probe_layout_lifecycle", [](const SdlProfileFrame& frame) {
      return frame.probe_layout_lifecycle_ms;
    });
    PrintMetric("probe_prepaint_paint_lifecycle",
                [](const SdlProfileFrame& frame) {
                  return frame.probe_prepaint_paint_lifecycle_ms;
                });
    PrintMetric("probe_paint_artifact_generation",
                [](const SdlProfileFrame& frame) {
                  return frame.probe_paint_artifact_generation_ms;
                });
    PrintMetric("probe_paint_artifact_audit_json",
                [](const SdlProfileFrame& frame) {
                  return frame.probe_paint_artifact_audit_json_ms;
                });
    PrintMetric("probe_paint_artifact_extraction",
                [](const SdlProfileFrame& frame) {
                  return frame.probe_paint_artifact_extraction_ms;
                });
    PrintMetric("probe_total", [](const SdlProfileFrame& frame) {
      return frame.probe_total_ms;
    });
    PrintMetric("cpu_replay", [](const SdlProfileFrame& frame) {
      return frame.cpu_replay_ms;
    });
    PrintMetric("pixel_convert", [](const SdlProfileFrame& frame) {
      return frame.pixel_convert_ms;
    });
    PrintMetric("texture_upload", [](const SdlProfileFrame& frame) {
      return frame.texture_upload_ms;
    });
    PrintMetric("direct_render", [](const SdlProfileFrame& frame) {
      return frame.direct_render_ms;
    });
    PrintMetric("sdl_draw_present", [](const SdlProfileFrame& frame) {
      return frame.sdl_draw_present_ms;
    });
    PrintMetric("total", [](const SdlProfileFrame& frame) {
      return frame.total_ms;
    });
  }

 private:
  using MetricSelector = double (*)(const SdlProfileFrame&);

  void PrintFrame(const SdlProfileFrame& frame) const {
    std::fprintf(
        stderr,
        "viewer profile: frame=%llu event=%s incremental=%d "
        "input=%.3fms blink_init=%.3fms blink_export_retained=%.3fms "
        "probe_html=%.3fms probe_style=%.3fms probe_layout=%.3fms "
        "probe_prepaint_paint=%.3fms probe_artifact=%.3fms "
        "probe_audit=%.3fms probe_extraction=%.3fms probe_total=%.3fms "
        "cpu_replay=%.3fms pixel_convert=%.3fms texture_upload=%.3fms "
        "direct_render=%.3fms sdl_draw_present=%.3fms total=%.3fms%s%s\n",
        static_cast<unsigned long long>(frame.frame), frame.reason.c_str(),
        frame.incremental ? 1 : 0, frame.input_update_ms,
        frame.blink_initialize_ms, frame.blink_export_retained_ms,
        frame.probe_html_document_setup_ms, frame.probe_style_update_ms,
        frame.probe_layout_lifecycle_ms,
        frame.probe_prepaint_paint_lifecycle_ms,
        frame.probe_paint_artifact_generation_ms,
        frame.probe_paint_artifact_audit_json_ms,
        frame.probe_paint_artifact_extraction_ms, frame.probe_total_ms,
        frame.cpu_replay_ms, frame.pixel_convert_ms, frame.texture_upload_ms,
        frame.direct_render_ms, frame.sdl_draw_present_ms, frame.total_ms,
        frame.cpu_replay_command_top.empty() ? "" : " cpu_replay_top=",
        frame.cpu_replay_command_top.empty()
            ? ""
            : frame.cpu_replay_command_top.c_str());
  }

  void PrintMetric(const char* name, MetricSelector selector) const {
    std::vector<double> values;
    values.reserve(frames_.size());
    double total = 0.0;
    for (const SdlProfileFrame& frame : frames_) {
      const double value = selector(frame);
      values.push_back(value);
      total += value;
    }
    std::sort(values.begin(), values.end());
    const size_t p95_index =
        values.empty()
            ? 0
            : std::min(values.size() - 1,
                       static_cast<size_t>(std::ceil(values.size() * 0.95)) -
                           1);
    const double average =
        values.empty() ? 0.0 : total / static_cast<double>(values.size());
    std::fprintf(stderr,
                 "  %s min=%.3fms avg=%.3fms p95=%.3fms max=%.3fms\n",
                 name, values.empty() ? 0.0 : values.front(), average,
                 values.empty() ? 0.0 : values[p95_index],
                 values.empty() ? 0.0 : values.back());
  }

  bool enabled_ = false;
  uint64_t summary_interval_ = 0;
  std::vector<SdlProfileFrame> frames_;
};

const std::vector<html_css_renderer::Rect>& ViewerDamageRects(
    const html_css_renderer::RenderResult& result) {
  return result.frame.damage_rects.empty() ? result.damage_rects
                                           : result.frame.damage_rects;
}

bool ViewerRequiresFullRedraw(const html_css_renderer::RenderResult& result) {
  return result.frame.requires_full_redraw || result.requires_full_redraw;
}

bool ViewerUsesScrollTranslationReuse(
    const html_css_renderer::RenderResult& result) {
  return result.frame.allows_scroll_translation_reuse ||
         std::abs(result.frame.scroll_translation_delta.x) > 0.5f ||
         std::abs(result.frame.scroll_translation_delta.y) > 0.5f;
}

bool SameViewerSize(html_css_renderer::Size left,
                    html_css_renderer::Size right) {
  return std::abs(left.width - right.width) < 0.5f &&
         std::abs(left.height - right.height) < 0.5f;
}

html_css_renderer::Size RendererOutputViewportSize(SDL_Renderer* renderer,
                                                   SDL_Window* window) {
  int width = 0;
  int height = 0;
  if (!SDL_GetRenderOutputSize(renderer, &width, &height) || width <= 0 ||
      height <= 0) {
    SDL_GetWindowSize(window, &width, &height);
  }
  return html_css_renderer::Size{
      static_cast<float>(std::max(1, width)),
      static_cast<float>(std::max(1, height)),
  };
}

bool RecreateFrameTexture(SDL_Renderer* renderer,
                          SDL_PixelFormat pixel_format,
                          SDL_TextureAccess texture_access,
                          int width,
                          int height,
                          SDL_Texture** texture) {
  SDL_Texture* next_texture =
      SDL_CreateTexture(renderer, pixel_format, texture_access,
                        std::max(1, width), std::max(1, height));
  if (!next_texture) {
    std::fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    return false;
  }
  if (*texture) {
    SDL_DestroyTexture(*texture);
  }
  *texture = next_texture;
  return true;
}

void PrintViewerStatus(
    const char* reason,
    uint64_t frame_count,
    const html_css_renderer::FrameInput& input,
    const html_css_renderer::RenderResult& result,
    const std::vector<AttributeToggle>& attribute_toggles,
    bool incremental_update) {
  const std::vector<html_css_renderer::Rect>& damage_rects =
      ViewerDamageRects(result);
  const bool requires_full_redraw = ViewerRequiresFullRedraw(result);
  const bool scroll_reuse = ViewerUsesScrollTranslationReuse(result);
  const html_css_renderer::Size viewport = result.successor_snapshot.viewport;
  std::fprintf(stderr,
               "viewer status: frame=%llu event=%s incremental=%d "
               "viewport=(%.0fx%.0f) time=%.3f dt=%.3f "
               "scroll=(%.1f,%.1f) "
               "full_redraw=%d scroll_reuse=%d scroll_delta=(%.1f,%.1f) "
               "needs_begin_frame=%d damage_rects=%zu",
               static_cast<unsigned long long>(frame_count), reason,
               incremental_update ? 1 : 0, viewport.width, viewport.height,
               input.timeline_time_seconds, input.delta_time_seconds,
               CurrentDocumentScrollX(input),
               CurrentDocumentScrollY(input), requires_full_redraw ? 1 : 0,
               scroll_reuse ? 1 : 0,
               result.frame.scroll_translation_delta.x,
               result.frame.scroll_translation_delta.y,
               result.needs_begin_frame ? 1 : 0,
               damage_rects.size());
  for (size_t i = 0; i < damage_rects.size(); ++i) {
    const html_css_renderer::Rect& rect = damage_rects[i];
    std::fprintf(stderr, " rect%zu=(%.1f,%.1f %.1fx%.1f)", i, rect.x, rect.y,
                 rect.width, rect.height);
  }
  std::fprintf(stderr,
               " chunks=%zu commands=%zu resources=%zu missing_resources=%zu",
               result.frame.scene_chunks.size(),
               result.frame.scene_commands.size(),
               result.frame.resource_commands.size(),
               result.missing_resources.size());
  for (const html_css_renderer::ScrollableElementEntry& entry :
       result.scrollable_element_entries) {
    std::fprintf(stderr,
                 " scrollable[%s]=(%.1f,%.1f max=%.1f,%.1f axes=%c%c)",
                 entry.element_id.c_str(), entry.scroll_offset.x,
                 entry.scroll_offset.y, entry.max_scroll_offset.x,
                 entry.max_scroll_offset.y, entry.can_scroll_x ? 'x' : '-',
                 entry.can_scroll_y ? 'y' : '-');
  }
  for (const AttributeToggle& toggle : attribute_toggles) {
    const auto found = input.element_attributes_by_id_and_name.find(toggle.key);
    const char* value =
        found == input.element_attributes_by_id_and_name.end()
            ? ""
            : found->second.c_str();
    std::fprintf(stderr, " attr[%s]=%s(%s)", toggle.key.c_str(), value,
                 toggle.is_on ? "on" : "off");
  }
  std::fprintf(stderr, "\n");
}

void SetViewerWindowTitle(
    SDL_Window* window,
    const char* reason,
    uint64_t frame_count,
    const html_css_renderer::FrameInput& input,
    const html_css_renderer::RenderResult& result,
    const std::vector<AttributeToggle>& attribute_toggles,
    bool incremental_update) {
  const char* render_mode =
      ViewerRequiresFullRedraw(result) ? "full"
                                       : (incremental_update ? "inc" : "render");
  const html_css_renderer::Size viewport = result.successor_snapshot.viewport;
  char buffer[192];
  std::snprintf(buffer, sizeof(buffer),
                "HTML/CSS SDL | f%llu %s | %.0fx%.0f | s=%.0f,%.0f | %s dmg=%zu",
                static_cast<unsigned long long>(frame_count), reason,
                viewport.width, viewport.height, CurrentDocumentScrollX(input),
                CurrentDocumentScrollY(input),
                render_mode, ViewerDamageRects(result).size());
  std::string title(buffer);
  if (!attribute_toggles.empty()) {
    title += " | attr=";
    title += attribute_toggles.front().is_on ? "on" : "off";
  }
  SDL_SetWindowTitle(window, title.c_str());
}

std::optional<SDL_Rect> DamageRectToTextureRect(
    const html_css_renderer::Rect& rect,
    int width,
    int height) {
  const int left = std::max(0, static_cast<int>(std::floor(rect.x)));
  const int top = std::max(0, static_cast<int>(std::floor(rect.y)));
  const int right =
      std::min(width, static_cast<int>(std::ceil(rect.x + rect.width)));
  const int bottom =
      std::min(height, static_cast<int>(std::ceil(rect.y + rect.height)));
  if (right <= left || bottom <= top) {
    return std::nullopt;
  }
  return SDL_Rect{left, top, right - left, bottom - top};
}

std::vector<SDL_Rect> TextureUpdateRectsForFrame(
    const html_css_renderer::RenderResult& result,
    const html_css_renderer::CpuImage& image,
    bool incremental_update) {
  if (!incremental_update || ViewerRequiresFullRedraw(result) ||
      ViewerUsesScrollTranslationReuse(result)) {
    return {SDL_Rect{0, 0, image.width, image.height}};
  }
  std::vector<SDL_Rect> rects;
  for (const html_css_renderer::Rect& damage : ViewerDamageRects(result)) {
    std::optional<SDL_Rect> texture_rect =
        DamageRectToTextureRect(damage, image.width, image.height);
    if (texture_rect) {
      rects.push_back(*texture_rect);
    }
  }
  return rects;
}

bool UploadCpuImageRectsToTexture(SDL_Texture* texture,
                                  const html_css_renderer::CpuImage& image,
                                  const std::vector<SDL_Rect>& rects) {
  const size_t expected_byte_count =
      static_cast<size_t>(image.width) * static_cast<size_t>(image.height) * 4u;
  const bool has_rgba_bytes =
      image.pixels_rgba_bytes.size() == expected_byte_count;
  for (const SDL_Rect& rect : rects) {
    void* texture_pixels = nullptr;
    int pitch = 0;
    if (!SDL_LockTexture(texture, &rect, &texture_pixels, &pitch)) {
      std::fprintf(stderr, "SDL_LockTexture failed: %s\n", SDL_GetError());
      return false;
    }
    auto* dst = static_cast<uint8_t*>(texture_pixels);
    for (int y = 0; y < rect.h; ++y) {
      auto* dst_row = dst + static_cast<size_t>(y) * pitch;
      const size_t src_row =
          static_cast<size_t>(rect.y + y) * image.width + rect.x;
      if (has_rgba_bytes) {
        const uint8_t* src =
            image.pixels_rgba_bytes.data() + src_row * 4u;
        std::copy_n(src, static_cast<size_t>(rect.w) * 4u, dst_row);
        continue;
      }
      for (int x = 0; x < rect.w; ++x) {
        const uint32_t rgba = image.pixels_rgba[src_row + x];
        dst_row[x * 4 + 0] = static_cast<uint8_t>((rgba >> 24) & 0xff);
        dst_row[x * 4 + 1] = static_cast<uint8_t>((rgba >> 16) & 0xff);
        dst_row[x * 4 + 2] = static_cast<uint8_t>((rgba >> 8) & 0xff);
        dst_row[x * 4 + 3] = static_cast<uint8_t>(rgba & 0xff);
      }
    }
    SDL_UnlockTexture(texture);
  }
  return true;
}

uint8_t ClampByte(float value) {
  const float clamped = std::max(0.0f, std::min(1.0f, value));
  return static_cast<uint8_t>(std::round(clamped * 255.0f));
}

SDL_FRect ToSdlRect(html_css_renderer::Rect rect) {
  return SDL_FRect{rect.x, rect.y, rect.width, rect.height};
}

void SetSdlColor(SDL_Renderer* renderer,
                 html_css_renderer::Color color,
                 float opacity = 1.0f) {
  SDL_SetRenderDrawColor(renderer, ClampByte(color.r), ClampByte(color.g),
                         ClampByte(color.b), ClampByte(color.a * opacity));
}

std::vector<uint32_t> ConvertRawRgbaBytesToAbgr(
    const std::vector<uint8_t>& pixels) {
  std::vector<uint32_t> out;
  out.reserve(pixels.size() / 4u);
  for (size_t i = 0; i + 3 < pixels.size(); i += 4) {
    const uint32_t r = pixels[i + 0];
    const uint32_t g = pixels[i + 1];
    const uint32_t b = pixels[i + 2];
    const uint32_t a = pixels[i + 3];
    out.push_back((a << 24) | (b << 16) | (g << 8) | r);
  }
  return out;
}

std::vector<uint32_t> ConvertAlphaMaskToAbgr(
    const std::vector<uint8_t>& pixels,
    html_css_renderer::Color color) {
  std::vector<uint32_t> out;
  out.reserve(pixels.size());
  const uint32_t r = ClampByte(color.r);
  const uint32_t g = ClampByte(color.g);
  const uint32_t b = ClampByte(color.b);
  for (uint8_t alpha : pixels) {
    const uint32_t a =
        static_cast<uint32_t>(std::round(alpha * std::max(0.0f, std::min(1.0f, color.a))));
    out.push_back((a << 24) | (b << 16) | (g << 8) | r);
  }
  return out;
}

class SdlFrameRenderer {
 public:
  explicit SdlFrameRenderer(SDL_Renderer* renderer) : renderer_(renderer) {}
  SdlFrameRenderer(const SdlFrameRenderer&) = delete;
  SdlFrameRenderer& operator=(const SdlFrameRenderer&) = delete;
  ~SdlFrameRenderer() { Clear(); }

  bool Render(const html_css_renderer::RenderResult& result,
              SDL_Texture* target) {
    ApplyResourceCommands(result.frame.resource_commands);

    if (!SDL_SetRenderTarget(renderer_, target)) {
      std::fprintf(stderr, "SDL_SetRenderTarget failed: %s\n", SDL_GetError());
      return false;
    }
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);

    RenderState state;
    std::vector<RenderState> state_stack;
    for (const html_css_renderer::SceneCommand& scene :
         result.frame.scene_commands) {
      if (scene.type != html_css_renderer::SceneCommandType::kDrawCommand) {
        continue;
      }
      DrawCommand(scene.draw_command, state_stack, state);
    }
    SDL_SetRenderClipRect(renderer_, nullptr);
    SDL_SetRenderTarget(renderer_, nullptr);
    return true;
  }

 private:
  struct TextureResource {
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
    html_css_renderer::Rect bounds;
  };

  struct RenderState {
    html_css_renderer::Matrix4 transform;
    std::optional<SDL_Rect> clip;
    float opacity = 1.0f;
  };

  void Clear() {
    for (auto& entry : images_) {
      SDL_DestroyTexture(entry.second.texture);
    }
    for (auto& entry : glyphs_) {
      SDL_DestroyTexture(entry.second.texture);
    }
    images_.clear();
    glyphs_.clear();
  }

  static std::string GlyphKey(const std::string& font_id, uint32_t glyph_id) {
    return font_id + "#" + std::to_string(glyph_id);
  }

  TextureResource CreateTextureFromAbgr(const std::vector<uint32_t>& pixels,
                                        int width,
                                        int height) {
    TextureResource resource;
    if (width <= 0 || height <= 0 ||
        pixels.size() < static_cast<size_t>(width * height)) {
      return resource;
    }
    resource.texture = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ABGR8888,
                                         SDL_TEXTUREACCESS_STATIC, width,
                                         height);
    if (!resource.texture) {
      std::fprintf(stderr, "SDL_CreateTexture resource failed: %s\n",
                   SDL_GetError());
      return resource;
    }
    SDL_SetTextureBlendMode(resource.texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(resource.texture, nullptr, pixels.data(),
                      width * static_cast<int>(sizeof(uint32_t)));
    resource.width = width;
    resource.height = height;
    return resource;
  }

  void ApplyResourceCommands(
      const std::vector<html_css_renderer::ResourceCommand>& commands) {
    for (const html_css_renderer::ResourceCommand& resource : commands) {
      if (resource.type == html_css_renderer::ResourceCommandType::kDestroyResource) {
        if (auto found = images_.find(resource.resource_id);
            found != images_.end()) {
          SDL_DestroyTexture(found->second.texture);
          images_.erase(found);
        }
        continue;
      }
      if (resource.type ==
              html_css_renderer::ResourceCommandType::kCreateOrUpdateImage &&
          resource.load_command.type == html_css_renderer::LoadCommandType::kLoadImage) {
        const html_css_renderer::ImageLoadInfo& image =
            resource.load_command.image;
        if (image.decoded_format != html_css_renderer::PixelFormat::kRgba8888) {
          continue;
        }
        const int width = static_cast<int>(std::floor(image.decoded_size.width));
        const int height =
            static_cast<int>(std::floor(image.decoded_size.height));
        TextureResource texture =
            CreateTextureFromAbgr(ConvertRawRgbaBytesToAbgr(image.decoded_pixels),
                                  width, height);
        if (texture.texture) {
          if (auto found = images_.find(resource.resource_id);
              found != images_.end()) {
            SDL_DestroyTexture(found->second.texture);
          }
          images_[resource.resource_id] = texture;
        }
      } else if (
          resource.type ==
              html_css_renderer::ResourceCommandType::kCreateOrUpdateGlyphAtlas &&
          resource.load_command.type ==
              html_css_renderer::LoadCommandType::kGlyphAtlasUpdate) {
        const html_css_renderer::GlyphAtlasUpdate& glyph =
            resource.load_command.glyph_atlas_update;
        if (glyph.format != html_css_renderer::PixelFormat::kAlpha8) {
          continue;
        }
        const int width = static_cast<int>(std::floor(glyph.bounds.width));
        const int height = static_cast<int>(std::floor(glyph.bounds.height));
        TextureResource texture = CreateTextureFromAbgr(
            ConvertAlphaMaskToAbgr(glyph.pixels,
                                   html_css_renderer::Color::Rgba(1, 1, 1, 1)),
            width, height);
        if (texture.texture) {
          texture.bounds = glyph.bounds;
          const std::string key = GlyphKey(glyph.font_id, glyph.glyph_id);
          if (auto found = glyphs_.find(key); found != glyphs_.end()) {
            SDL_DestroyTexture(found->second.texture);
          }
          glyphs_[key] = texture;
        }
      }
    }
  }

  static bool IsIdentity(const html_css_renderer::Matrix4& matrix) {
    const auto& m = matrix.values;
    return m[0] == 1.0f && m[1] == 0.0f && m[4] == 0.0f &&
           m[5] == 1.0f && m[12] == 0.0f && m[13] == 0.0f;
  }

  static html_css_renderer::Point TransformPoint(
      const html_css_renderer::Matrix4& matrix,
      html_css_renderer::Point point) {
    const auto& m = matrix.values;
    return {m[0] * point.x + m[4] * point.y + m[12],
            m[1] * point.x + m[5] * point.y + m[13]};
  }

  static html_css_renderer::Matrix4 Multiply(
      const html_css_renderer::Matrix4& a,
      const html_css_renderer::Matrix4& b) {
    html_css_renderer::Matrix4 out;
    for (int row = 0; row < 4; ++row) {
      for (int col = 0; col < 4; ++col) {
        float value = 0.0f;
        for (int k = 0; k < 4; ++k) {
          value += a.values[k * 4 + row] * b.values[col * 4 + k];
        }
        out.values[col * 4 + row] = value;
      }
    }
    return out;
  }

  static std::array<html_css_renderer::Point, 4> TransformRectCorners(
      const html_css_renderer::Matrix4& matrix,
      html_css_renderer::Rect rect) {
    return {TransformPoint(matrix, {rect.x, rect.y}),
            TransformPoint(matrix, {rect.x + rect.width, rect.y}),
            TransformPoint(matrix,
                           {rect.x + rect.width, rect.y + rect.height}),
            TransformPoint(matrix, {rect.x, rect.y + rect.height})};
  }

  static SDL_Rect BoundsForTransformedRect(
      const html_css_renderer::Matrix4& matrix,
      html_css_renderer::Rect rect) {
    const auto points = TransformRectCorners(matrix, rect);
    float min_x = points[0].x;
    float min_y = points[0].y;
    float max_x = points[0].x;
    float max_y = points[0].y;
    for (const html_css_renderer::Point& point : points) {
      min_x = std::min(min_x, point.x);
      min_y = std::min(min_y, point.y);
      max_x = std::max(max_x, point.x);
      max_y = std::max(max_y, point.y);
    }
    const int left = static_cast<int>(std::floor(min_x));
    const int top = static_cast<int>(std::floor(min_y));
    const int right = static_cast<int>(std::ceil(max_x));
    const int bottom = static_cast<int>(std::ceil(max_y));
    return SDL_Rect{left, top, std::max(0, right - left),
                    std::max(0, bottom - top)};
  }

  static SDL_FColor ToSdlColor(html_css_renderer::Color color,
                               float opacity) {
    return SDL_FColor{std::max(0.0f, std::min(1.0f, color.r)),
                      std::max(0.0f, std::min(1.0f, color.g)),
                      std::max(0.0f, std::min(1.0f, color.b)),
                      std::max(0.0f,
                               std::min(1.0f, color.a * opacity))};
  }

  void DrawQuad(SDL_Texture* texture,
                html_css_renderer::Rect rect,
                html_css_renderer::Color color,
                const RenderState& state) {
    const auto points = TransformRectCorners(state.transform, rect);
    const SDL_FColor vertex_color = ToSdlColor(color, state.opacity);
    SDL_Vertex vertices[4] = {
        {SDL_FPoint{points[0].x, points[0].y}, vertex_color,
         SDL_FPoint{0.0f, 0.0f}},
        {SDL_FPoint{points[1].x, points[1].y}, vertex_color,
         SDL_FPoint{1.0f, 0.0f}},
        {SDL_FPoint{points[2].x, points[2].y}, vertex_color,
         SDL_FPoint{1.0f, 1.0f}},
        {SDL_FPoint{points[3].x, points[3].y}, vertex_color,
         SDL_FPoint{0.0f, 1.0f}},
    };
    constexpr int indices[6] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometry(renderer_, texture, vertices, 4, indices, 6);
  }

  void FillRect(const html_css_renderer::DrawCommand& command,
                const RenderState& state) {
    if (IsIdentity(state.transform)) {
      SetSdlColor(renderer_, command.color, state.opacity);
      SDL_FRect rect = ToSdlRect(command.rect);
      SDL_RenderFillRect(renderer_, &rect);
      return;
    }
    DrawQuad(nullptr, command.rect, command.color, state);
  }

  void DrawRRectApprox(const html_css_renderer::DrawCommand& command,
                       bool stroke,
                       const RenderState& state) {
    if (!stroke) {
      FillRect(command, state);
      return;
    }
    SetSdlColor(renderer_, command.color, state.opacity);
    const float w = std::max(1.0f, command.stroke_width);
    const html_css_renderer::Rect r = command.rect;
    std::array<SDL_FRect, 4> sides = {
        SDL_FRect{r.x, r.y, r.width, w},
        SDL_FRect{r.x, r.y + r.height - w, r.width, w},
        SDL_FRect{r.x, r.y, w, r.height},
        SDL_FRect{r.x + r.width - w, r.y, w, r.height},
    };
    if (IsIdentity(state.transform)) {
      for (SDL_FRect& side : sides) {
        SDL_RenderFillRect(renderer_, &side);
      }
    } else {
      for (SDL_FRect& side : sides) {
        DrawQuad(nullptr, html_css_renderer::Rect{side.x, side.y, side.w,
                                                  side.h},
                 command.color, state);
      }
    }
  }

  static SDL_Rect IntersectClip(SDL_Rect a, SDL_Rect b) {
    const int left = std::max(a.x, b.x);
    const int top = std::max(a.y, b.y);
    const int right = std::min(a.x + a.w, b.x + b.w);
    const int bottom = std::min(a.y + a.h, b.y + b.h);
    return SDL_Rect{left, top, std::max(0, right - left),
                    std::max(0, bottom - top)};
  }

  void ApplyClip(const std::optional<SDL_Rect>& clip) {
    if (clip) {
      SDL_SetRenderClipRect(renderer_, &*clip);
    } else {
      SDL_SetRenderClipRect(renderer_, nullptr);
    }
  }

  void DrawImage(SDL_Texture* texture,
                 html_css_renderer::Rect rect,
                 html_css_renderer::Color color,
                 const RenderState& state) {
    if (IsIdentity(state.transform)) {
      SDL_FRect dst = ToSdlRect(rect);
      SDL_SetTextureColorMod(texture, ClampByte(color.r), ClampByte(color.g),
                             ClampByte(color.b));
      SDL_SetTextureAlphaMod(texture, ClampByte(color.a * state.opacity));
      SDL_RenderTexture(renderer_, texture, nullptr, &dst);
      return;
    }
    DrawQuad(texture, rect, color, state);
  }

  void DrawCommand(const html_css_renderer::DrawCommand& command,
                   std::vector<RenderState>& state_stack,
                   RenderState& state) {
    switch (command.type) {
      case html_css_renderer::DrawCommandType::kFillRect:
        FillRect(command, state);
        break;
      case html_css_renderer::DrawCommandType::kStrokeRect: {
        SetSdlColor(renderer_, command.color, state.opacity);
        const float w = std::max(1.0f, command.stroke_width);
        const html_css_renderer::Rect r = command.rect;
        std::array<html_css_renderer::Rect, 4> sides = {
            html_css_renderer::Rect{r.x, r.y, r.width, w},
            html_css_renderer::Rect{r.x, r.y + r.height - w, r.width, w},
            html_css_renderer::Rect{r.x, r.y, w, r.height},
            html_css_renderer::Rect{r.x + r.width - w, r.y, w, r.height},
        };
        for (const html_css_renderer::Rect& side : sides) {
          if (IsIdentity(state.transform)) {
            SDL_FRect sdl_side = ToSdlRect(side);
            SDL_RenderFillRect(renderer_, &sdl_side);
          } else {
            DrawQuad(nullptr, side, command.color, state);
          }
        }
        break;
      }
      case html_css_renderer::DrawCommandType::kFillRRect:
        DrawRRectApprox(command, false, state);
        break;
      case html_css_renderer::DrawCommandType::kStrokeRRect:
        DrawRRectApprox(command, true, state);
        break;
      case html_css_renderer::DrawCommandType::kFillRectShader:
        FillRect(command, state);
        break;
      case html_css_renderer::DrawCommandType::kFillRRectShader:
        DrawRRectApprox(command, false, state);
        break;
      case html_css_renderer::DrawCommandType::kDrawImage: {
        const auto found = images_.find(command.resource_id);
        if (found == images_.end()) {
          break;
        }
        DrawImage(found->second.texture, command.rect,
                  html_css_renderer::Color::Rgba(1, 1, 1, 1), state);
        break;
      }
      case html_css_renderer::DrawCommandType::kDrawImageRect: {
        const auto found = images_.find(command.resource_id);
        if (found == images_.end()) {
          break;
        }
        DrawImage(found->second.texture, command.rect,
                  html_css_renderer::Color::Rgba(1, 1, 1, 1), state);
        break;
      }
      case html_css_renderer::DrawCommandType::kDrawGlyphRun: {
        const size_t count = std::min(command.glyph_run.glyph_ids.size(),
                                      command.glyph_run.positions.size());
        for (size_t i = 0; i < count; ++i) {
          const std::string key = GlyphKey(command.glyph_run.font_id,
                                           command.glyph_run.glyph_ids[i]);
          const auto found = glyphs_.find(key);
          if (found == glyphs_.end()) {
            continue;
          }
          const html_css_renderer::Point origin =
              command.glyph_run.positions[i];
          const html_css_renderer::Rect dst{
              origin.x + found->second.bounds.x,
              origin.y + found->second.bounds.y,
              static_cast<float>(found->second.width),
              static_cast<float>(found->second.height)};
          DrawImage(found->second.texture, dst, command.glyph_run.color, state);
        }
        break;
      }
      case html_css_renderer::DrawCommandType::kDrawTextBlob:
        break;
      case html_css_renderer::DrawCommandType::kSave:
        state_stack.push_back(state);
        break;
      case html_css_renderer::DrawCommandType::kSaveLayer:
        state_stack.push_back(state);
        state.opacity *= command.opacity;
        break;
      case html_css_renderer::DrawCommandType::kRestore:
        if (!state_stack.empty()) {
          state = state_stack.back();
          state_stack.pop_back();
          ApplyClip(state.clip);
        }
        break;
      case html_css_renderer::DrawCommandType::kTransform:
        state.transform = Multiply(state.transform, command.transform);
        if (state.clip) {
          ApplyClip(state.clip);
        }
        break;
      case html_css_renderer::DrawCommandType::kClipRect: {
        SDL_Rect clip = BoundsForTransformedRect(state.transform, command.rect);
        state.clip = state.clip ? IntersectClip(*state.clip, clip) : clip;
        ApplyClip(state.clip);
        break;
      }
      case html_css_renderer::DrawCommandType::kClipRRect: {
        SDL_Rect clip = BoundsForTransformedRect(state.transform, command.rect);
        state.clip = state.clip ? IntersectClip(*state.clip, clip) : clip;
        ApplyClip(state.clip);
        break;
      }
      case html_css_renderer::DrawCommandType::kClipPath:
        break;
      case html_css_renderer::DrawCommandType::kFillPath:
      case html_css_renderer::DrawCommandType::kDrawText:
      case html_css_renderer::DrawCommandType::kDiagnostic:
        break;
    }
  }

  SDL_Renderer* renderer_ = nullptr;
  std::unordered_map<std::string, TextureResource> images_;
  std::unordered_map<std::string, TextureResource> glyphs_;
};

bool Contains(html_css_renderer::Rect rect, float x, float y) {
  return x >= rect.x && y >= rect.y && x < rect.x + rect.width &&
         y < rect.y + rect.height;
}

std::string HitTest(const std::vector<html_css_renderer::HitTestEntry>& entries,
                    float x,
                    float y) {
  for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
    if (Contains(it->bounds, x, y)) {
      return it->element_id;
    }
  }
  return {};
}

html_css_renderer::Point WindowToDocumentPoint(int window_width,
                                               int window_height,
                                               int image_width,
                                               int image_height,
                                               float window_x,
                                               float window_y) {
  const float scale_x =
      window_width > 0 ? window_width / static_cast<float>(image_width) : 1.0f;
  const float scale_y = window_height > 0
                            ? window_height / static_cast<float>(image_height)
                            : 1.0f;
  const float scale = std::min(scale_x, scale_y);
  const float target_width = image_width * scale;
  const float target_height = image_height * scale;
  const float target_x = (window_width - target_width) * 0.5f;
  const float target_y = (window_height - target_height) * 0.5f;
  if (scale <= 0.0f) {
    return {};
  }
  return {(window_x - target_x) / scale, (window_y - target_y) / scale};
}

html_css_renderer::Point WindowEventToDocumentPoint(SDL_Renderer* renderer,
                                                    int image_width,
                                                    int image_height,
                                                    float window_x,
                                                    float window_y) {
  float render_x = window_x;
  float render_y = window_y;
  SDL_RenderCoordinatesFromWindow(renderer, window_x, window_y, &render_x,
                                  &render_y);
  int output_width = 0;
  int output_height = 0;
  if (!SDL_GetRenderOutputSize(renderer, &output_width, &output_height) ||
      output_width <= 0 || output_height <= 0) {
    output_width = image_width;
    output_height = image_height;
  }
  return WindowToDocumentPoint(output_width, output_height, image_width,
                               image_height, render_x, render_y);
}

bool PrimaryPointerPressed(const html_css_renderer::FrameInput& input) {
  return !input.pointers.empty() && input.pointers.front().pressed;
}

bool SamePrimaryPointer(const html_css_renderer::FrameInput& a,
                        const html_css_renderer::FrameInput& b) {
  const bool a_has_pointer = !a.pointers.empty();
  const bool b_has_pointer = !b.pointers.empty();
  if (a_has_pointer != b_has_pointer) {
    return false;
  }
  if (!a_has_pointer) {
    return true;
  }
  const html_css_renderer::PointerState& a_pointer = a.pointers.front();
  const html_css_renderer::PointerState& b_pointer = b.pointers.front();
  return a_pointer.id == b_pointer.id &&
         a_pointer.position.x == b_pointer.position.x &&
         a_pointer.position.y == b_pointer.position.y &&
         a_pointer.pressed == b_pointer.pressed;
}

void SetPrimaryPointer(html_css_renderer::FrameInput* input,
                       html_css_renderer::Point point,
                       bool pressed) {
  html_css_renderer::PointerState pointer;
  pointer.id = 0;
  pointer.position = point;
  pointer.pressed = pressed;
  input->pointers.clear();
  input->pointers.push_back(pointer);
  input->hovered_element_id.clear();
  input->active_element_id.clear();
}

}  // namespace

int main(int argc, char** argv) {
  EmptyAssets assets;
  html_css_renderer::RendererCreateInfo create_info;
  create_info.asset_provider = &assets;
  html_css_renderer::FrameInput input;
  uint64_t quit_after_ms = 0;
  float window_scale = 1.0f;
  std::string font_file;
  std::string paint_artifact_dump_path;
  std::string resource_root;
  std::string resource_base_path;
  std::vector<AttributeToggle> attribute_toggles;
  std::vector<std::string> stylesheet_loader_diagnostics;
  float scroll_step = 80.0f;
  bool profile_enabled = false;
  uint64_t profile_summary_frames = 0;
  uint64_t profile_auto_scroll_frames = 0;
  std::optional<float> profile_auto_scroll_step;
  std::optional<html_css_renderer::Size> profile_resize_to;
  uint64_t profile_resize_after_frame = 1;
  bool incremental = true;
  bool use_cpu = true;
  bool use_skia_cpu = true;
  bool use_blink = true;

  if (argc > 1 && !ParseArgs(argc, argv, &create_info, &input,
                             &quit_after_ms, &window_scale, &font_file,
                             &incremental, &use_cpu, &use_skia_cpu,
                             &paint_artifact_dump_path, &resource_root,
                             &resource_base_path,
                             &attribute_toggles, &scroll_step,
                             &profile_enabled, &profile_summary_frames,
                             &profile_auto_scroll_frames,
                             &profile_auto_scroll_step,
                             &profile_resize_to,
                             &profile_resize_after_frame,
                             &use_blink,
                             &stylesheet_loader_diagnostics)) {
    PrintUsage();
    return 2;
  }

  if (create_info.html.empty()) {
    std::fprintf(stderr, "no HTML input provided; opening file dialog...\n");
    std::optional<fs::path> selected_html = ShowNativeHtmlFileDialog();
    if (!selected_html) {
      std::fprintf(stderr, "no HTML file selected; exiting\n");
      return 0;
    }
    if (!LoadHtmlFileForViewer(
            *selected_html, ResourceRootPolicy::kUseHtmlDirectoryIfUnset,
            &create_info, &resource_root, &resource_base_path,
            &stylesheet_loader_diagnostics)) {
      return 2;
    }
    std::fprintf(stderr, "selected HTML file: %s\n",
                 selected_html->string().c_str());
  }

  for (AttributeToggle& toggle : attribute_toggles) {
    const auto found = input.element_attributes_by_id_and_name.find(toggle.key);
    toggle.is_on =
        found != input.element_attributes_by_id_and_name.end() &&
        found->second == toggle.on_value;
  }

  if (!font_file.empty()) {
    assets.font_bytes = ReadBinaryFile(font_file);
    if (assets.font_bytes.empty()) {
      std::fprintf(stderr, "failed to read font file: %s\n",
                   font_file.c_str());
      return 2;
    }
    std::fprintf(stderr, "font asset available: %s\n",
                 font_file.c_str());
  }
  const html_css_renderer::Size initial_viewport = create_info.viewport;
  input.viewport = initial_viewport;
  html_css_renderer::SetStandaloneResourceProviderResourceRoot(resource_root);
  html_css_renderer::SetStandaloneResourceProviderDocumentBasePath(
      resource_base_path);

  std::unique_ptr<html_css_renderer::BlinkPageEmbedder> blink_embedder;
  std::unique_ptr<html_css_renderer::RendererState> state;
  html_css_renderer::RenderResult result;
  SdlFrameProfiler profiler(profile_enabled, profile_summary_frames);
  SdlProfileFrame initial_profile;
  initial_profile.frame = 1;
  initial_profile.reason = "initial";

  if (use_blink) {
    html_css_renderer::BlinkPageEmbedderCreateInfo blink_create_info;
    blink_create_info.renderer = std::move(create_info);
    blink_embedder =
        html_css_renderer::CreateLiveBlinkPageEmbedder(std::move(blink_create_info));
    if (!blink_embedder) {
      std::fprintf(stderr, "failed to create Blink adapter\n");
      return 1;
    }
    ProfileClock::time_point blink_init_start;
    if (profiler.enabled()) {
      blink_init_start = ProfileClock::now();
    }
    const html_css_renderer::BlinkLifecycleReport init =
        blink_embedder->Initialize();
    if (profiler.enabled()) {
      initial_profile.blink_initialize_ms =
          ElapsedProfileMs(blink_init_start, ProfileClock::now());
    }
    ProfileClock::time_point blink_render_start;
    if (profiler.enabled()) {
      blink_render_start = ProfileClock::now();
    }
    result = blink_embedder->AdvanceAndRender(input);
    if (profiler.enabled()) {
      initial_profile.blink_export_retained_ms =
          ElapsedProfileMs(blink_render_start, ProfileClock::now());
      PopulateProbeProfileTimings(result, &initial_profile);
    }
    result.diagnostics.insert(result.diagnostics.begin(),
                              init.diagnostics.begin(), init.diagnostics.end());
    result.diagnostics.insert(result.diagnostics.begin(),
                              stylesheet_loader_diagnostics.begin(),
                              stylesheet_loader_diagnostics.end());
    if (!paint_artifact_dump_path.empty()) {
      std::ofstream audit_file(paint_artifact_dump_path);
      if (!audit_file) {
        std::fprintf(stderr, "failed to write paint artifact dump: %s\n",
                     paint_artifact_dump_path.c_str());
        return 1;
      }
      audit_file << html_css_renderer::SerializePaintArtifactAuditJson(result)
                 << "\n";
    }
    for (const std::string& diagnostic : result.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
  }

  int frame_width =
      std::max(1, static_cast<int>(std::floor(initial_viewport.width)));
  int frame_height =
      std::max(1, static_cast<int>(std::floor(initial_viewport.height)));
  html_css_renderer::CpuImage image;
  if (use_cpu) {
    html_css_renderer::CpuRenderOptions cpu_options;
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
    cpu_options.profile_command_timings = profiler.enabled() && use_skia_cpu;
#endif
    ProfileClock::time_point cpu_replay_start;
    if (profiler.enabled()) {
      cpu_replay_start = ProfileClock::now();
    }
    image =
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
        use_skia_cpu ? html_css_renderer::RasterizeRenderResultWithSkiaCpu(
                           result, cpu_options)
                     :
#endif
                     html_css_renderer::RasterizeRenderResult(result,
                                                              cpu_options);
    if (profiler.enabled()) {
      initial_profile.cpu_replay_ms =
          ElapsedProfileMs(cpu_replay_start, ProfileClock::now());
      if (use_skia_cpu) {
        initial_profile.cpu_replay_command_top =
            FormatCpuReplayCommandTimingTop(5);
      }
    }
    frame_width = image.width;
    frame_height = image.height;
  }

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  const int window_width =
      std::max(320, static_cast<int>(frame_width * window_scale));
  const int window_height =
      std::max(240, static_cast<int>(frame_height * window_scale));

  SDL_Window* window = SDL_CreateWindow(
      "HTML/CSS Renderer CPU SDL Viewer", window_width, window_height,
      SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  SDL_SetWindowMinimumSize(window, 320, 240);

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }
  const char* renderer_name = SDL_GetRendererName(renderer);
  std::fprintf(stderr, "viewer renderer: %s\n",
               renderer_name ? renderer_name : "unknown");

  const SDL_PixelFormat frame_texture_format =
      use_cpu ? SDL_PIXELFORMAT_RGBA32 : SDL_PIXELFORMAT_ABGR8888;
  const SDL_TextureAccess texture_access =
      use_cpu ? SDL_TEXTUREACCESS_STREAMING : SDL_TEXTUREACCESS_TARGET;
  SDL_Texture* texture =
      SDL_CreateTexture(renderer, frame_texture_format,
                        texture_access, frame_width, frame_height);
  if (!texture) {
    std::fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  std::unique_ptr<SdlFrameRenderer> direct_renderer;
  std::optional<PendingSdlProfileFrame> pending_profile_frame;
  if (use_cpu) {
    ProfileClock::time_point texture_upload_start;
    if (profiler.enabled()) {
      texture_upload_start = ProfileClock::now();
    }
    if (!UploadCpuImageRectsToTexture(
            texture, image, {SDL_Rect{0, 0, image.width, image.height}})) {
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }
    if (profiler.enabled()) {
      initial_profile.texture_upload_ms =
          ElapsedProfileMs(texture_upload_start, ProfileClock::now());
    }
  } else {
    direct_renderer = std::make_unique<SdlFrameRenderer>(renderer);
    ProfileClock::time_point direct_render_start;
    if (profiler.enabled()) {
      direct_render_start = ProfileClock::now();
    }
    if (!direct_renderer->Render(result, texture)) {
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }
    if (profiler.enabled()) {
      initial_profile.direct_render_ms =
          ElapsedProfileMs(direct_render_start, ProfileClock::now());
    }
  }
  if (profiler.enabled()) {
    pending_profile_frame = PendingSdlProfileFrame{initial_profile, std::nullopt};
  }

  if (!attribute_toggles.empty()) {
    std::fprintf(stderr,
                 "viewer controls: Space/T toggles %zu attribute target(s)\n",
                 attribute_toggles.size());
  }
  std::fprintf(stderr,
               "viewer controls: mouse wheel scrolls the document viewport "
               "by %.1f px\n",
               scroll_step);
  std::fprintf(stderr,
               "viewer controls: arrow keys scroll by %.1f px; PageUp/"
               "PageDown scroll by viewport; Home returns to top\n",
               scroll_step);
  uint64_t rendered_frame_count = 1;
  PrintViewerStatus("initial", rendered_frame_count, input, result,
                    attribute_toggles, false);
  SetViewerWindowTitle(window, "initial", rendered_frame_count, input, result,
                       attribute_toggles, false);

  const uint64_t animation_start_ms = SDL_GetTicks();
  auto current_timeline_seconds = [&]() -> double {
    return static_cast<double>(SDL_GetTicks() - animation_start_ms) / 1000.0;
  };
  auto stamp_frame_time =
      [&](html_css_renderer::FrameInput* next_input) -> double {
    const double next_timeline_time = current_timeline_seconds();
    next_input->delta_time_seconds =
        std::max(0.0, next_timeline_time - input.timeline_time_seconds);
    next_input->timeline_time_seconds = next_timeline_time;
    return next_input->delta_time_seconds;
  };

  auto render_updated_input =
      [&](const char* reason,
          html_css_renderer::FrameInput next_input,
          double input_update_ms,
          ProfileClock::time_point frame_start,
          bool force_full_render = false) -> bool {
    stamp_frame_time(&next_input);
    const bool use_incremental = incremental && use_cpu && !force_full_render;
    const bool profile = profiler.enabled();
    SdlProfileFrame profile_frame;
    ProfileClock::time_point blink_render_start;
    if (profile) {
      profile_frame.frame = rendered_frame_count + 1;
      profile_frame.reason = reason;
      profile_frame.incremental = use_incremental;
      profile_frame.input_update_ms = input_update_ms;
      blink_render_start = ProfileClock::now();
    }
    html_css_renderer::RenderResult next_result =
        use_incremental ? blink_embedder->AdvanceAndRenderIncremental(next_input)
                        : blink_embedder->AdvanceAndRender(next_input);
    if (profile) {
      profile_frame.blink_export_retained_ms =
          ElapsedProfileMs(blink_render_start, ProfileClock::now());
      PopulateProbeProfileTimings(next_result, &profile_frame);
    }
    if (use_cpu) {
      html_css_renderer::CpuRenderOptions cpu_options;
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
      cpu_options.profile_command_timings = profile && use_skia_cpu;
#endif
      ProfileClock::time_point cpu_replay_start;
      if (profile) {
        cpu_replay_start = ProfileClock::now();
      }
      image =
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
          use_skia_cpu
              ? (use_incremental
                     ? html_css_renderer::
                           RasterizeRenderResultIncrementalWithSkiaCpu(
                               next_result, &image, cpu_options)
                     : html_css_renderer::RasterizeRenderResultWithSkiaCpu(
                           next_result, cpu_options))
              :
#endif
              (use_incremental
                   ? html_css_renderer::RasterizeRenderResultIncremental(
                         next_result, &image, cpu_options)
                   : html_css_renderer::RasterizeRenderResult(next_result,
                                                              cpu_options));
      if (profile) {
        profile_frame.cpu_replay_ms =
            ElapsedProfileMs(cpu_replay_start, ProfileClock::now());
        if (use_skia_cpu) {
          profile_frame.cpu_replay_command_top =
              FormatCpuReplayCommandTimingTop(5);
        }
      }
      const bool texture_size_changed =
          image.width != frame_width || image.height != frame_height;
      if (texture_size_changed) {
        if (!RecreateFrameTexture(renderer, frame_texture_format,
                                  texture_access, image.width,
                                  image.height, &texture)) {
          return false;
        }
        frame_width = image.width;
        frame_height = image.height;
      }
      ProfileClock::time_point pixel_convert_start;
      if (profile) {
        pixel_convert_start = ProfileClock::now();
      }
      std::vector<SDL_Rect> texture_update_rects =
          TextureUpdateRectsForFrame(next_result, image,
                                     use_incremental && !texture_size_changed);
      if (profile) {
        profile_frame.pixel_convert_ms =
            ElapsedProfileMs(pixel_convert_start, ProfileClock::now());
      }
      ProfileClock::time_point texture_upload_start;
      if (profile) {
        texture_upload_start = ProfileClock::now();
      }
      if (!UploadCpuImageRectsToTexture(texture, image,
                                        texture_update_rects)) {
        return false;
      }
      if (profile) {
        profile_frame.texture_upload_ms =
            ElapsedProfileMs(texture_upload_start, ProfileClock::now());
      }
    } else if (direct_renderer) {
      ProfileClock::time_point direct_render_start;
      if (profile) {
        direct_render_start = ProfileClock::now();
      }
      const int next_frame_width = std::max(
          1, static_cast<int>(std::floor(
                 next_result.successor_snapshot.viewport.width)));
      const int next_frame_height = std::max(
          1, static_cast<int>(std::floor(
                 next_result.successor_snapshot.viewport.height)));
      if (next_frame_width != frame_width ||
          next_frame_height != frame_height) {
        if (!RecreateFrameTexture(renderer, frame_texture_format,
                                  texture_access, next_frame_width,
                                  next_frame_height, &texture)) {
          return false;
        }
        frame_width = next_frame_width;
        frame_height = next_frame_height;
      }
      if (!direct_renderer->Render(next_result, texture)) {
        return false;
      }
      if (profile) {
        profile_frame.direct_render_ms =
            ElapsedProfileMs(direct_render_start, ProfileClock::now());
      }
    }
    ++rendered_frame_count;
    next_input.scroll_offsets_by_element_id =
        next_result.successor_snapshot.scroll_offsets_by_element_id;
    next_input.wheel = std::nullopt;
    PrintViewerStatus(reason, rendered_frame_count, next_input, next_result,
                      attribute_toggles, use_incremental);
    SetViewerWindowTitle(window, reason, rendered_frame_count, next_input,
                         next_result, attribute_toggles, use_incremental);
    result = std::move(next_result);
    input = std::move(next_input);
    if (profile) {
      if (pending_profile_frame) {
        profiler.Record(std::move(pending_profile_frame->frame));
      }
      pending_profile_frame =
          PendingSdlProfileFrame{std::move(profile_frame), frame_start};
    }
    return true;
  };

  bool running = true;
  const uint64_t start_ms = SDL_GetTicks();
  const bool profile_auto_scroll_requested = profile_auto_scroll_frames > 0;
  uint64_t profile_auto_scroll_remaining = profile_auto_scroll_frames;
  const float profile_auto_scroll_delta =
      profile_auto_scroll_step.value_or(scroll_step);
  const bool profile_resize_requested = profile_resize_to.has_value();
  bool profile_resize_done = false;
  bool first_present_complete = false;
  while (running) {
    bool texture_dirty = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
        running = false;
      } else if (event.type == SDL_EVENT_WINDOW_RESIZED ||
                 event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        const html_css_renderer::Size next_viewport =
            RendererOutputViewportSize(renderer, window);
        if (!SameViewerSize(next_viewport, result.successor_snapshot.viewport)) {
          html_css_renderer::FrameInput next_input = input;
          next_input.viewport = next_viewport;
          const double input_update_ms =
              profiler.enabled()
                  ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                  : 0.0;
          if (!render_updated_input("resize", std::move(next_input),
                                    input_update_ms, input_update_start,
                                    true)) {
            running = false;
            break;
          }
          texture_dirty = true;
        }
      } else if (event.type == SDL_EVENT_MOUSE_WHEEL) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        html_css_renderer::FrameInput next_input = input;
        const ScrollDelta wheel_delta{event.wheel.x * scroll_step,
                                      -event.wheel.y * scroll_step, false};
        const html_css_renderer::Point document_point =
            WindowEventToDocumentPoint(renderer, frame_width, frame_height,
                                       event.wheel.mouse_x,
                                       event.wheel.mouse_y);
        next_input.wheel = html_css_renderer::WheelInput{
            document_point,
            html_css_renderer::Point{wheel_delta.x, wheel_delta.y}};
        const double input_update_ms =
            profiler.enabled()
                ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                : 0.0;
        if (!render_updated_input("wheel-scroll", std::move(next_input),
                                  input_update_ms, input_update_start)) {
          running = false;
          break;
        }
        texture_dirty = true;
      } else if (event.type == SDL_EVENT_KEY_DOWN &&
                 (event.key.key == ' ' || event.key.key == 't' ||
                  event.key.key == 'T')) {
        if (!attribute_toggles.empty()) {
          const ProfileClock::time_point input_update_start =
              profiler.enabled() ? ProfileClock::now()
                                 : ProfileClock::time_point{};
          html_css_renderer::FrameInput next_input = input;
          for (AttributeToggle& toggle : attribute_toggles) {
            toggle.is_on = !toggle.is_on;
            next_input.element_attributes_by_id_and_name[toggle.key] =
                toggle.is_on ? toggle.on_value : toggle.off_value;
          }
          const double input_update_ms =
              profiler.enabled()
                  ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                  : 0.0;
          if (!render_updated_input("toggle", std::move(next_input),
                                    input_update_ms, input_update_start)) {
            running = false;
            break;
          }
          texture_dirty = true;
        }
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        const std::optional<ScrollDelta> scroll_delta =
            KeyboardScrollDelta(event.key.key, scroll_step, frame_height);
        if (scroll_delta) {
          html_css_renderer::FrameInput next_input = input;
          if (scroll_delta->home) {
            SetDocumentScroll(&next_input, 0.0f, 0.0f);
          } else {
            SetDocumentScroll(&next_input,
                              CurrentDocumentScrollX(next_input) +
                                  scroll_delta->x,
                              CurrentDocumentScrollY(next_input) +
                                  scroll_delta->y);
          }
          if (CurrentDocumentScrollX(next_input) !=
                  CurrentDocumentScrollX(input) ||
              CurrentDocumentScrollY(next_input) !=
                  CurrentDocumentScrollY(input)) {
            const double input_update_ms =
                profiler.enabled()
                    ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                    : 0.0;
            if (!render_updated_input("key-scroll", std::move(next_input),
                                      input_update_ms, input_update_start)) {
              running = false;
              break;
            }
            texture_dirty = true;
          }
        }
      } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP &&
                 event.button.button == SDL_BUTTON_LEFT) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        const html_css_renderer::Point pointer_point =
            WindowEventToDocumentPoint(renderer, frame_width, frame_height,
                                       event.button.x, event.button.y);
        html_css_renderer::FrameInput next_input = input;
        SetPrimaryPointer(&next_input, pointer_point, false);
        const bool pointer_changed =
            !SamePrimaryPointer(input, next_input) ||
            !input.active_element_id.empty() ||
            !input.hovered_element_id.empty();
        if (pointer_changed) {
          const double input_update_ms =
              profiler.enabled()
                  ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                  : 0.0;
          if (!render_updated_input("pointer-up", std::move(next_input),
                                    input_update_ms, input_update_start)) {
            running = false;
            break;
          }
          texture_dirty = true;
        }
      } else if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN &&
                 event.button.button == SDL_BUTTON_LEFT) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        const html_css_renderer::Point pointer_point =
            WindowEventToDocumentPoint(renderer, frame_width, frame_height,
                                       event.button.x, event.button.y);
        const std::string clicked =
            HitTest(result.hit_test_entries, pointer_point.x, pointer_point.y);
        html_css_renderer::FrameInput next_input = input;
        SetPrimaryPointer(&next_input, pointer_point, true);
        const bool pointer_changed = !SamePrimaryPointer(input, next_input);
        bool toggle_changed = false;
        if (!clicked.empty()) {
          for (AttributeToggle& toggle : attribute_toggles) {
            if (AttributeToggleElementId(toggle) != clicked) {
              continue;
            }
            toggle.is_on = !toggle.is_on;
            next_input.element_attributes_by_id_and_name[toggle.key] =
                toggle.is_on ? toggle.on_value : toggle.off_value;
            toggle_changed = true;
          }
        }
        if (pointer_changed || toggle_changed) {
          const double input_update_ms =
              profiler.enabled()
                  ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                  : 0.0;
          if (!render_updated_input(toggle_changed ? "click" : "pointer-down",
                                    std::move(next_input), input_update_ms,
                                    input_update_start)) {
            running = false;
            break;
          }
          texture_dirty = true;
        }
      } else if (event.type == SDL_EVENT_MOUSE_MOTION) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        const html_css_renderer::Point pointer_point =
            WindowEventToDocumentPoint(renderer, frame_width, frame_height,
                                       event.motion.x, event.motion.y);
        html_css_renderer::FrameInput next_input = input;
        SetPrimaryPointer(&next_input, pointer_point,
                          PrimaryPointerPressed(input));
        if (!SamePrimaryPointer(input, next_input)) {
          const double input_update_ms =
              profiler.enabled()
                  ? ElapsedProfileMs(input_update_start, ProfileClock::now())
                  : 0.0;
          if (!render_updated_input("pointer-move", std::move(next_input),
                                    input_update_ms, input_update_start)) {
            running = false;
            break;
          }
          texture_dirty = true;
        }
      }
    }
    if (first_present_complete && profile_auto_scroll_remaining > 0) {
      const ProfileClock::time_point input_update_start = ProfileClock::now();
      html_css_renderer::FrameInput next_input = input;
      SetDocumentScroll(&next_input, CurrentDocumentScrollX(next_input),
                        CurrentDocumentScrollY(next_input) +
                            profile_auto_scroll_delta);
      const double input_update_ms =
          ElapsedProfileMs(input_update_start, ProfileClock::now());
      if (!render_updated_input("profile-auto-scroll", std::move(next_input),
                                input_update_ms, input_update_start)) {
        running = false;
      }
      --profile_auto_scroll_remaining;
      texture_dirty = true;
    }
    if (first_present_complete && profile_resize_requested &&
        !profile_resize_done &&
        rendered_frame_count >= profile_resize_after_frame) {
      const ProfileClock::time_point input_update_start = ProfileClock::now();
      html_css_renderer::FrameInput next_input = input;
      SDL_SetWindowSize(window, static_cast<int>(profile_resize_to->width),
                        static_cast<int>(profile_resize_to->height));
      next_input.viewport = RendererOutputViewportSize(renderer, window);
      const double input_update_ms =
          ElapsedProfileMs(input_update_start, ProfileClock::now());
      if (!render_updated_input("profile-resize", std::move(next_input),
                                input_update_ms, input_update_start, true)) {
        running = false;
      }
      profile_resize_done = true;
      texture_dirty = true;
    }
    if (running && result.needs_begin_frame) {
      html_css_renderer::FrameInput next_input = input;
      const double delta_time_seconds = stamp_frame_time(&next_input);
      if (delta_time_seconds > 0.0) {
        const ProfileClock::time_point input_update_start =
            profiler.enabled() ? ProfileClock::now()
                               : ProfileClock::time_point{};
        if (!render_updated_input("animation-tick", std::move(next_input),
                                  0.0, input_update_start)) {
          running = false;
        }
        texture_dirty = true;
      }
    }
    (void)texture_dirty;
    ProfileClock::time_point draw_present_start;
    if (pending_profile_frame) {
      draw_present_start = ProfileClock::now();
    }
    int drawable_width = 0;
    int drawable_height = 0;
    if (!SDL_GetRenderOutputSize(renderer, &drawable_width, &drawable_height) ||
        drawable_width <= 0 || drawable_height <= 0) {
      SDL_GetWindowSize(window, &drawable_width, &drawable_height);
    }
    SDL_SetRenderDrawColor(renderer, 245, 247, 251, 255);
    SDL_RenderClear(renderer);
    const float scale_x =
        drawable_width > 0 ? drawable_width / static_cast<float>(frame_width)
                           : 1.0f;
    const float scale_y =
        drawable_height > 0 ? drawable_height / static_cast<float>(frame_height)
                            : 1.0f;
    const float scale = std::min(scale_x, scale_y);
    const float target_width = frame_width * scale;
    const float target_height = frame_height * scale;
    const SDL_FRect target{
        (drawable_width - target_width) * 0.5f,
        (drawable_height - target_height) * 0.5f,
        target_width,
        target_height,
    };
    SDL_RenderTexture(renderer, texture, nullptr, &target);
    SDL_RenderPresent(renderer);
    if (pending_profile_frame) {
      const ProfileClock::time_point draw_present_end = ProfileClock::now();
      pending_profile_frame->frame.sdl_draw_present_ms =
          ElapsedProfileMs(draw_present_start, draw_present_end);
      pending_profile_frame->frame.total_ms =
          pending_profile_frame->total_start
              ? ElapsedProfileMs(*pending_profile_frame->total_start,
                                 draw_present_end)
              : SdlProfileMeasuredSubtotal(pending_profile_frame->frame);
      profiler.Record(std::move(pending_profile_frame->frame));
      pending_profile_frame.reset();
    }
    if (profile_auto_scroll_requested && first_present_complete &&
        profile_auto_scroll_remaining == 0 && quit_after_ms == 0) {
      running = false;
    }
    if (profile_resize_requested && first_present_complete &&
        profile_resize_done && profile_auto_scroll_remaining == 0 &&
        quit_after_ms == 0) {
      running = false;
    }
    first_present_complete = true;
    if (quit_after_ms > 0 && SDL_GetTicks() - start_ms >= quit_after_ms) {
      running = false;
    }
    SDL_Delay(16);
  }

  if (pending_profile_frame) {
    profiler.Record(std::move(pending_profile_frame->frame));
    pending_profile_frame.reset();
  }
  profiler.PrintSummary("exit");

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return result.missing_resources.empty() ? 0 : 1;
}
