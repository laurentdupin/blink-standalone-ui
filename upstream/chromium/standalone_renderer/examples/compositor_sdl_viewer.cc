#include <SDL3/SDL.h>
#include <SDL3/SDL_properties.h>

#if defined(_WIN32)
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <shobjidl.h>
#include <windows.h>
#endif

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <filesystem>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/message_loop/message_pump_type.h"
#include "base/run_loop.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/threading/platform_thread.h"
#include "base/trace_event/trace_event_impl.h"
#include "gpu/command_buffer/service/gpu_switches.h"
#include "html_css_renderer/compositor_runtime.h"
#include "html_css_renderer/css_file_loader.h"
#include "html_css_renderer/renderer_c_api.h"
#include "html_css_renderer/standalone_process.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "third_party/perfetto/include/perfetto/tracing/tracing.h"
#include "third_party/skia/include/core/SkData.h"
#include "third_party/skia/include/core/SkImageInfo.h"
#include "third_party/skia/include/core/SkPixmap.h"
#include "third_party/skia/include/encode/SkPngEncoder.h"
#include "ui/gl/gl_switches.h"

namespace {

namespace fs = std::filesystem;

constexpr int kNavigationDeferralsAfterReset = 10;

bool ReadTextFile(const std::string& path, std::string* out) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    return false;
  std::ostringstream buffer;
  buffer << file.rdbuf();
  *out = buffer.str();
  return true;
}

bool WriteBinaryFileForCompositorViewer(const std::string& path,
                                        const std::vector<uint8_t>& bytes) {
  const fs::path output_path = fs::absolute(fs::path(path));
  const fs::path parent = output_path.parent_path();
  if (!parent.empty()) {
    std::error_code error;
    fs::create_directories(parent, error);
    if (error) {
      std::fprintf(stderr, "failed to create screenshot directory: %s (%s)\n",
                   parent.string().c_str(), error.message().c_str());
      return false;
    }
  }
  std::ofstream file(output_path, std::ios::binary);
  if (!file) {
    std::fprintf(stderr, "failed to open screenshot output: %s\n",
                 output_path.string().c_str());
    return false;
  }
  file.write(reinterpret_cast<const char*>(bytes.data()),
             static_cast<std::streamsize>(bytes.size()));
  if (!file) {
    std::fprintf(stderr, "failed to write screenshot output: %s\n",
                 output_path.string().c_str());
    return false;
  }
  return true;
}

std::string LowerAsciiForCompositorViewer(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](unsigned char c) {
                   return static_cast<char>(std::tolower(c));
                 });
  return value;
}

bool IsHtmlFileForCompositorViewer(const fs::path& path) {
  const std::string extension =
      LowerAsciiForCompositorViewer(path.extension().string());
  return extension == ".html" || extension == ".htm";
}

std::string RelativePathForCompositorViewer(const fs::path& path,
                                            const fs::path& root) {
  std::error_code error;
  fs::path relative_path = fs::relative(path, root, error);
  if (error)
    relative_path = path.filename();
  return relative_path.generic_string();
}

std::vector<fs::path> EnumerateHtmlFilesForCompositorViewer(
    const fs::path& directory) {
  std::vector<fs::path> files;
  std::error_code error;
  fs::path absolute_directory = fs::absolute(directory, error);
  if (error)
    absolute_directory = directory;
  if (!fs::is_directory(absolute_directory, error))
    return files;

  fs::recursive_directory_iterator iterator(
      absolute_directory, fs::directory_options::skip_permission_denied, error);
  const fs::recursive_directory_iterator end;
  while (!error && iterator != end) {
    const fs::directory_entry& entry = *iterator;
    std::error_code status_error;
    if (entry.is_regular_file(status_error)) {
      const fs::path path = entry.path();
      if (IsHtmlFileForCompositorViewer(path))
        files.push_back(fs::absolute(path));
    }
    iterator.increment(error);
    if (error)
      break;
  }
  std::sort(files.begin(), files.end(),
            [&](const fs::path& lhs, const fs::path& rhs) {
              return LowerAsciiForCompositorViewer(
                         RelativePathForCompositorViewer(
                             lhs, absolute_directory)) <
                     LowerAsciiForCompositorViewer(
                         RelativePathForCompositorViewer(
                             rhs, absolute_directory));
            });
  return files;
}

bool LoadHtmlFileForCompositorViewer(const fs::path& html_path,
                                     html_css_renderer::RendererCreateInfo* renderer,
                                     std::string* html_file,
                                     std::string* resource_root,
                                     std::string* resource_base_path,
                                     bool resource_root_explicit,
                                     bool resource_base_path_explicit) {
  const fs::path absolute_html_path = fs::absolute(html_path);
  std::string html;
  if (!ReadTextFile(absolute_html_path.string(), &html)) {
    std::fprintf(stderr, "failed to read HTML file: %s\n",
                 absolute_html_path.string().c_str());
    return false;
  }

  renderer->html = std::move(html);
  *html_file = absolute_html_path.string();
  const std::string html_directory = absolute_html_path.parent_path().string();
  std::vector<std::string> stylesheet_diagnostics;
  html_css_renderer::AddLocalLinkedStylesheetsForDocument(
      absolute_html_path, renderer->html, renderer, &stylesheet_diagnostics);
  for (const std::string& diagnostic : stylesheet_diagnostics) {
    std::fprintf(stderr, "stylesheet diagnostic: %s\n", diagnostic.c_str());
  }
  if (!resource_root_explicit) {
    *resource_root = html_directory;
  }
  if (!resource_base_path_explicit) {
    *resource_base_path = html_directory;
  }
  return true;
}

#if defined(_WIN32)
enum class NativeDirectoryDialogStatus {
  kSelected,
  kCancelled,
  kFailed,
};

struct NativeDirectoryDialogResult {
  NativeDirectoryDialogStatus status = NativeDirectoryDialogStatus::kFailed;
  fs::path path;
};

NativeDirectoryDialogResult ShowNativeHtmlDirectoryDialog() {
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
    return {NativeDirectoryDialogStatus::kFailed, {}};
  }

  IFileOpenDialog* dialog = nullptr;
  HRESULT result =
      CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC_SERVER,
                       IID_PPV_ARGS(&dialog));
  if (FAILED(result) || !dialog) {
    std::fprintf(stderr, "failed to create file dialog: 0x%08lx\n",
                 static_cast<unsigned long>(result));
    if (should_uninitialize) {
      CoUninitialize();
    }
    return {NativeDirectoryDialogStatus::kFailed, {}};
  }

  dialog->SetTitle(L"Open HTML directory");
  DWORD options = 0;
  if (SUCCEEDED(dialog->GetOptions(&options))) {
    dialog->SetOptions(options | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM |
                       FOS_PATHMUSTEXIST);
  }

  result = dialog->Show(nullptr);
  if (result == HRESULT_FROM_WIN32(ERROR_CANCELLED)) {
    dialog->Release();
    if (should_uninitialize) {
      CoUninitialize();
    }
    return {NativeDirectoryDialogStatus::kCancelled, {}};
  }
  if (FAILED(result)) {
    std::fprintf(stderr, "file dialog failed: 0x%08lx\n",
                 static_cast<unsigned long>(result));
    dialog->Release();
    if (should_uninitialize) {
      CoUninitialize();
    }
    return {NativeDirectoryDialogStatus::kFailed, {}};
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
    return {NativeDirectoryDialogStatus::kFailed, {}};
  }

  PWSTR selected_path = nullptr;
  result = item->GetDisplayName(SIGDN_FILESYSPATH, &selected_path);
  NativeDirectoryDialogResult dialog_result;
  if (SUCCEEDED(result) && selected_path) {
    dialog_result.status = NativeDirectoryDialogStatus::kSelected;
    dialog_result.path = fs::path(selected_path);
    CoTaskMemFree(selected_path);
  } else {
    std::fprintf(stderr, "file dialog path conversion failed: 0x%08lx\n",
                 static_cast<unsigned long>(result));
    dialog_result.status = NativeDirectoryDialogStatus::kFailed;
  }

  item->Release();
  dialog->Release();
  if (should_uninitialize) {
    CoUninitialize();
  }
  return dialog_result;
}
#else
enum class NativeDirectoryDialogStatus {
  kSelected,
  kCancelled,
  kFailed,
};

struct NativeDirectoryDialogResult {
  NativeDirectoryDialogStatus status = NativeDirectoryDialogStatus::kFailed;
  fs::path path;
};

NativeDirectoryDialogResult ShowNativeHtmlDirectoryDialog() {
  std::fprintf(stderr,
               "native HTML directory picker is only implemented on Windows; "
               "pass --html-dir <directory> or --html-file <path>\n");
  return {NativeDirectoryDialogStatus::kFailed, {}};
}
#endif

class ScopedBaseThreadPool {
 public:
  ScopedBaseThreadPool() {
    if (!base::ThreadPoolInstance::Get()) {
      base::ThreadPoolInstance::CreateAndStartWithDefaultParams(
          "BlinkStandaloneCompositor");
      owns_thread_pool_ = true;
    }
  }

  ScopedBaseThreadPool(const ScopedBaseThreadPool&) = delete;
  ScopedBaseThreadPool& operator=(const ScopedBaseThreadPool&) = delete;

  ~ScopedBaseThreadPool() {
    if (owns_thread_pool_ && base::ThreadPoolInstance::Get())
      base::ThreadPoolInstance::Get()->Shutdown();
  }

 private:
  bool owns_thread_pool_ = false;
};

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

bool ParsePoint(const std::string& value, html_css_renderer::Point* point) {
  const size_t comma = value.find(',');
  if (comma == std::string::npos)
    return false;
  try {
    point->x = std::stof(value.substr(0, comma));
    point->y = std::stof(value.substr(comma + 1));
  } catch (...) {
    return false;
  }
  return point->x >= 0.0f && point->y >= 0.0f;
}

html_css_renderer::Size SdlWindowPixelViewport(SDL_Window* window) {
  int width = 0;
  int height = 0;
  SDL_GetWindowSizeInPixels(window, &width, &height);
  if (width <= 0 || height <= 0) {
    SDL_GetWindowSize(window, &width, &height);
  }
  return html_css_renderer::Size{static_cast<float>(std::max(1, width)),
                                 static_cast<float>(std::max(1, height))};
}

html_css_renderer::Point SdlWindowPointToPixelViewport(
    SDL_Window* window,
    html_css_renderer::Point window_point) {
  int window_width = 0;
  int window_height = 0;
  SDL_GetWindowSize(window, &window_width, &window_height);
  const html_css_renderer::Size pixel_viewport = SdlWindowPixelViewport(window);
  if (window_width <= 0 || window_height <= 0) {
    return window_point;
  }
  return html_css_renderer::Point{
      window_point.x * pixel_viewport.width / static_cast<float>(window_width),
      window_point.y * pixel_viewport.height /
          static_cast<float>(window_height)};
}

bool SameViewportSize(html_css_renderer::Size lhs,
                      html_css_renderer::Size rhs) {
  return static_cast<int>(lhs.width) == static_cast<int>(rhs.width) &&
         static_cast<int>(lhs.height) == static_cast<int>(rhs.height);
}

bool SamePointerState(const html_css_renderer::PointerState& lhs,
                      const html_css_renderer::PointerState& rhs) {
  return lhs.id == rhs.id &&
         static_cast<int>(lhs.position.x) == static_cast<int>(rhs.position.x) &&
         static_cast<int>(lhs.position.y) == static_cast<int>(rhs.position.y) &&
         lhs.pressed == rhs.pressed;
}

blink_standalone_mouse_button_t CApiMouseButtonFromRuntimeButton(
    html_css_renderer::MouseInputButton button) {
  switch (button) {
    case html_css_renderer::MouseInputButton::kLeft:
      return BLINK_STANDALONE_MOUSE_BUTTON_LEFT;
    case html_css_renderer::MouseInputButton::kMiddle:
      return BLINK_STANDALONE_MOUSE_BUTTON_MIDDLE;
    case html_css_renderer::MouseInputButton::kRight:
      return BLINK_STANDALONE_MOUSE_BUTTON_RIGHT;
    case html_css_renderer::MouseInputButton::kNone:
      return BLINK_STANDALONE_MOUSE_BUTTON_NONE;
  }
  return BLINK_STANDALONE_MOUSE_BUTTON_NONE;
}

blink_standalone_key_t CApiKeyFromRuntimeKey(
    html_css_renderer::KeyboardInputKey key) {
  switch (key) {
    case html_css_renderer::KeyboardInputKey::kBackspace:
      return BLINK_STANDALONE_KEY_BACKSPACE;
    case html_css_renderer::KeyboardInputKey::kTab:
      return BLINK_STANDALONE_KEY_TAB;
    case html_css_renderer::KeyboardInputKey::kEnter:
      return BLINK_STANDALONE_KEY_ENTER;
    case html_css_renderer::KeyboardInputKey::kDelete:
      return BLINK_STANDALONE_KEY_DELETE;
    case html_css_renderer::KeyboardInputKey::kUnknown:
      return BLINK_STANDALONE_KEY_UNKNOWN;
  }
  return BLINK_STANDALONE_KEY_UNKNOWN;
}

const char* CApiStatusName(blink_standalone_status_code_t status) {
  switch (status) {
    case BLINK_STANDALONE_STATUS_OK:
      return "ok";
    case BLINK_STANDALONE_STATUS_INVALID_ARGUMENT:
      return "invalid_argument";
    case BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED:
      return "initialization_failed";
    case BLINK_STANDALONE_STATUS_RENDER_FAILED:
      return "render_failed";
    case BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED:
      return "no_script_rejected";
  }
  return "unknown";
}

bool IsDirectoryNavigationKeyDownEventForCompositorViewer(
    const SDL_Event& event) {
  return event.type == SDL_EVENT_KEY_DOWN &&
         (event.key.key == SDLK_F1 || event.key.key == SDLK_F2 ||
          event.key.key == SDLK_F5);
}

void DrainStandaloneViewerTaskQueueForNavigation() {
  base::RunLoop run_loop(base::RunLoop::Type::kNestableTasksAllowed);
  run_loop.RunUntilIdle();
}

void QuiesceStandaloneViewerAfterDocumentTeardown() {
  DrainStandaloneViewerTaskQueueForNavigation();
  base::PlatformThread::Sleep(base::Milliseconds(200));
  DrainStandaloneViewerTaskQueueForNavigation();
}

int MouseButtonModifierForCompositorViewer(
    html_css_renderer::MouseInputButton button) {
  switch (button) {
    case html_css_renderer::MouseInputButton::kLeft:
      return 1 << 6;  // blink::WebInputEvent::kLeftButtonDown.
    case html_css_renderer::MouseInputButton::kMiddle:
      return 1 << 7;  // blink::WebInputEvent::kMiddleButtonDown.
    case html_css_renderer::MouseInputButton::kRight:
      return 1 << 8;  // blink::WebInputEvent::kRightButtonDown.
    case html_css_renderer::MouseInputButton::kNone:
      return 0;
  }
  return 0;
}

html_css_renderer::MouseInputButton MouseButtonFromSdlForCompositorViewer(
    Uint8 button) {
  if (button == SDL_BUTTON_LEFT)
    return html_css_renderer::MouseInputButton::kLeft;
  if (button == SDL_BUTTON_MIDDLE)
    return html_css_renderer::MouseInputButton::kMiddle;
  if (button == SDL_BUTTON_RIGHT)
    return html_css_renderer::MouseInputButton::kRight;
  return html_css_renderer::MouseInputButton::kNone;
}

void AppendMouseInputEventForCompositorViewer(
    html_css_renderer::FrameInput* input,
    html_css_renderer::MouseInputEventType type,
    html_css_renderer::Point position,
    html_css_renderer::MouseInputButton button,
    int modifiers,
    int click_count) {
  input->mouse_events.push_back(
      html_css_renderer::MouseInputEvent{type, position, button, modifiers,
                                         click_count});
}

int KeyboardModifiersFromSdlForCompositorViewer(SDL_Keymod mod) {
  int modifiers = 0;
  if ((mod & SDL_KMOD_SHIFT) != 0)
    modifiers |= 1 << 1;  // blink::WebInputEvent::kShiftKey.
  if ((mod & SDL_KMOD_CTRL) != 0)
    modifiers |= 1 << 2;  // blink::WebInputEvent::kControlKey.
  if ((mod & SDL_KMOD_ALT) != 0)
    modifiers |= 1 << 3;  // blink::WebInputEvent::kAltKey.
  if ((mod & SDL_KMOD_GUI) != 0)
    modifiers |= 1 << 4;  // blink::WebInputEvent::kMetaKey.
  return modifiers;
}

html_css_renderer::KeyboardInputKey KeyboardInputKeyFromSdlForCompositorViewer(
    SDL_Keycode key) {
  switch (key) {
    case SDLK_BACKSPACE:
      return html_css_renderer::KeyboardInputKey::kBackspace;
    case SDLK_TAB:
      return html_css_renderer::KeyboardInputKey::kTab;
    case SDLK_RETURN:
    case SDLK_KP_ENTER:
      return html_css_renderer::KeyboardInputKey::kEnter;
    case SDLK_DELETE:
      return html_css_renderer::KeyboardInputKey::kDelete;
    default:
      return html_css_renderer::KeyboardInputKey::kUnknown;
  }
}

std::optional<html_css_renderer::KeyboardInputKey>
KeyboardInputKeyFromNameForCompositorViewer(const std::string& name) {
  const std::string lower = LowerAsciiForCompositorViewer(name);
  if (lower == "backspace")
    return html_css_renderer::KeyboardInputKey::kBackspace;
  if (lower == "delete")
    return html_css_renderer::KeyboardInputKey::kDelete;
  if (lower == "enter" || lower == "return")
    return html_css_renderer::KeyboardInputKey::kEnter;
  if (lower == "tab")
    return html_css_renderer::KeyboardInputKey::kTab;
  return std::nullopt;
}

void AppendKeyboardTextInputEventForCompositorViewer(
    html_css_renderer::FrameInput* input,
    const std::string& text,
    int modifiers) {
  if (text.empty())
    return;
  input->keyboard_events.push_back(html_css_renderer::KeyboardInputEvent{
      html_css_renderer::KeyboardInputEventType::kText,
      html_css_renderer::KeyboardInputKey::kUnknown, text, modifiers});
}

void AppendKeyboardKeyInputEventForCompositorViewer(
    html_css_renderer::FrameInput* input,
    html_css_renderer::KeyboardInputEventType type,
    html_css_renderer::KeyboardInputKey key,
    int modifiers) {
  if (key == html_css_renderer::KeyboardInputKey::kUnknown)
    return;
  input->keyboard_events.push_back(
      html_css_renderer::KeyboardInputEvent{type, key, std::string(),
                                            modifiers});
}

struct SyntheticWheelBurst {
  int count = 0;
  html_css_renderer::Point delta;
};

bool ParseWheelBurst(const std::string& value, SyntheticWheelBurst* burst) {
  int count = 0;
  float first = 0.0f;
  float second = 0.0f;
  if (std::sscanf(value.c_str(), "%d,%f,%f", &count, &first, &second) == 3) {
    if (count <= 0)
      return false;
    burst->count = count;
    burst->delta = html_css_renderer::Point{first, second};
    return true;
  }
  if (std::sscanf(value.c_str(), "%d,%f", &count, &second) == 2) {
    if (count <= 0)
      return false;
    burst->count = count;
    burst->delta = html_css_renderer::Point{0.0f, second};
    return true;
  }
  return false;
}

void AccumulateWheelInput(std::optional<html_css_renderer::WheelInput>* wheel,
                          html_css_renderer::Point position,
                          html_css_renderer::Point delta) {
  if (wheel->has_value()) {
    (*wheel)->position = position;
    (*wheel)->delta.x += delta.x;
    (*wheel)->delta.y += delta.y;
    return;
  }
  *wheel = html_css_renderer::WheelInput{position, delta};
}

std::string HtmlWithInlineStylesForCompositorViewer(
    const std::string& html,
    const std::vector<html_css_renderer::Stylesheet>& stylesheets) {
  if (stylesheets.empty()) {
    return html;
  }
  std::ostringstream style_markup;
  for (const html_css_renderer::Stylesheet& stylesheet : stylesheets) {
    style_markup << "<style data-standalone-source=\"";
    for (char c : stylesheet.id) {
      if (c == '"')
        style_markup << "&quot;";
      else
        style_markup << c;
    }
    style_markup << "\">\n" << stylesheet.css << "\n</style>\n";
  }
  std::string combined = html;
  const std::string lower = LowerAsciiForCompositorViewer(combined);
  const size_t head_end = lower.find("</head>");
  if (head_end != std::string::npos) {
    combined.insert(head_end, style_markup.str());
    return combined;
  }
  const size_t html_start = lower.find("<html");
  if (html_start != std::string::npos) {
    const size_t html_tag_end = lower.find('>', html_start);
    if (html_tag_end != std::string::npos) {
      combined.insert(html_tag_end + 1,
                      std::string("<head>\n") + style_markup.str() +
                          "</head>\n");
      return combined;
    }
  }
  return style_markup.str() + combined;
}

std::optional<std::vector<uint8_t>> EncodeRawFramePngForCompositorViewer(
    const blink_standalone_frame_output_t& output) {
  if (!output.pixels || output.width <= 0 || output.height <= 0 ||
      output.stride <= 0) {
    return std::nullopt;
  }
  SkColorType color_type = kUnknown_SkColorType;
  switch (output.pixel_format) {
    case BLINK_STANDALONE_PIXEL_FORMAT_RGBA8:
      color_type = kRGBA_8888_SkColorType;
      break;
    case BLINK_STANDALONE_PIXEL_FORMAT_BGRA8:
      color_type = kBGRA_8888_SkColorType;
      break;
    case BLINK_STANDALONE_PIXEL_FORMAT_NONE:
      return std::nullopt;
  }
  const SkImageInfo info = SkImageInfo::Make(
      output.width, output.height, color_type,
      output.premultiplied_alpha ? kPremul_SkAlphaType
                                 : kUnpremul_SkAlphaType);
  const SkPixmap pixmap(info, output.pixels,
                        static_cast<size_t>(output.stride));
  SkPngEncoder::Options options;
  sk_sp<SkData> png = SkPngEncoder::Encode(pixmap, options);
  if (!png) {
    return std::nullopt;
  }
  const uint8_t* data = static_cast<const uint8_t*>(png->data());
  return std::vector<uint8_t>(data, data + png->size());
}

SDL_PixelFormat SdlPixelFormatForCompositorViewer(
    blink_standalone_pixel_format_t pixel_format) {
  switch (pixel_format) {
    case BLINK_STANDALONE_PIXEL_FORMAT_RGBA8:
      return SDL_PIXELFORMAT_RGBA8888;
    case BLINK_STANDALONE_PIXEL_FORMAT_BGRA8:
      return SDL_PIXELFORMAT_BGRA8888;
    case BLINK_STANDALONE_PIXEL_FORMAT_NONE:
      return SDL_PIXELFORMAT_UNKNOWN;
  }
  return SDL_PIXELFORMAT_UNKNOWN;
}

void AppendSyntheticSdlClickEventsForCompositorViewer(
    html_css_renderer::Point point,
    int repeats,
    std::deque<SDL_Event>* events) {
  const int safe_repeats = std::max(1, repeats);
  for (int i = 0; i < safe_repeats; ++i) {
    SDL_Event motion{};
    motion.type = SDL_EVENT_MOUSE_MOTION;
    motion.motion.x = point.x;
    motion.motion.y = point.y;
    motion.motion.state = 0;
    events->push_back(motion);

    SDL_Event down{};
    down.type = SDL_EVENT_MOUSE_BUTTON_DOWN;
    down.button.x = point.x;
    down.button.y = point.y;
    down.button.button = SDL_BUTTON_LEFT;
    events->push_back(down);

    SDL_Event up{};
    up.type = SDL_EVENT_MOUSE_BUTTON_UP;
    up.button.x = point.x;
    up.button.y = point.y;
    up.button.button = SDL_BUTTON_LEFT;
    events->push_back(up);
  }
}

html_css_renderer::Point DocumentScrollForCompositorViewer(
    const html_css_renderer::CompositorFrameResult& result) {
  const auto& offsets = result.successor_snapshot.scroll_offsets_by_element_id;
  const auto document = offsets.find("document");
  if (document != offsets.end())
    return document->second;
  const auto body = offsets.find("body");
  if (body != offsets.end())
    return body->second;
  return html_css_renderer::Point{0.0f, 0.0f};
}

void PrintUsage() {
  std::fprintf(
      stderr,
      "Usage: blink_standalone_sdl_viewer_skia --html <markup>|--html-file <path> "
      "|--html-dir <dir> [--css <css>|--css-file <path>] [--viewport WxH] "
      "[--quit-after-ms N] [--paint-artifact-dump <path>] [--resource-root <dir>] "
      "[--screenshot-out <png>] [--screenshot-after-ms N] "
      "[--synthetic-input-smoke] [--synthetic-resize WxH] "
      "[--synthetic-click x,y] [--synthetic-sdl-click x,y] "
      "[--synthetic-sdl-text text] [--synthetic-sdl-key name] "
      "[--synthetic-sdl-click-repeats N] [--synthetic-navigation-smoke] "
      "[--synthetic-navigation-stress N] "
      "[--synthetic-wheel-burst count,deltaY|count,deltaX,deltaY] "
      "[--trace-stages] [--full-frame-diagnostics]\n"
      "Launching without --html, --html-file, or --html-dir opens a native "
      "HTML directory picker on Windows and recursively lists HTML files. "
      "F1/F2 switch files; F5 resets the current file.\n"
      "SDL owns the host window/event pump only. HTML/CSS frames are driven "
      "through Blink PaintArtifactCompositor/cc/Viz/GPU/Vulkan.\n");
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
  const std::string name =
      equals == std::string::npos ? arg : arg.substr(0, equals);
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

void PrintFrameStatus(const char* reason,
                      uint64_t frame,
                      const html_css_renderer::CompositorFrameResult& result) {
  std::fprintf(stderr,
               "frame=%llu reason=%s paint_clean=%d root_layer=%d layers=%d "
               "viewport=%dx%d "
               "cc_output=%dx%d viz_output=%dx%d "
               "chunks=%d display_items=%d begin_frame=%d cc_host=%d "
               "cc_attached=%d cc_commit=%d frame_sink_request=%d "
               "frame_sink_bound=%d gpu_context=%d raster_context=%d "
               "shared_image=%d viz_submit=%d viz_display=%d skia_gpu=%d\n",
               static_cast<unsigned long long>(frame), reason,
               result.paint_clean ? 1 : 0,
               result.root_layer_available ? 1 : 0,
               result.compositor_layer_count,
               static_cast<int>(result.successor_snapshot.viewport.width),
               static_cast<int>(result.successor_snapshot.viewport.height),
               static_cast<int>(result.compositor_output_size.width),
               static_cast<int>(result.compositor_output_size.height),
               static_cast<int>(result.viz_display_output_size.width),
               static_cast<int>(result.viz_display_output_size.height),
               result.paint_chunk_count,
               result.display_item_count, result.needs_begin_frame ? 1 : 0,
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
               result.skia_renderer_gpu_path_reached ? 1 : 0);
}

void PrintPresentationStatus(
    const char* reason,
    const html_css_renderer::NativePresentationResult& result,
    bool include_diagnostics = true) {
  std::fprintf(stderr,
               "presentation=%s native_window=%d vulkan_instance=%d "
               "vulkan_queue=%d vulkan_surface=%d vulkan_swapchain=%d "
               "vulkan_present=%d surface=%dx%d viz_manager=%d viz_support=%d "
               "cc_output=%dx%d viz_output=%dx%d "
               "viz_display=%d cc_host=%d cc_attached=%d cc_commit=%d "
               "frame_sink_request=%d frame_sink_bound=%d gpu_context=%d "
               "raster_context=%d shared_image=%d viz_submit=%d skia_gpu=%d",
               reason, result.native_window_available ? 1 : 0,
               result.vulkan_instance_initialized ? 1 : 0,
               result.vulkan_device_queue_initialized ? 1 : 0,
               result.vulkan_surface_created ? 1 : 0,
               result.vulkan_swapchain_created ? 1 : 0,
               result.vulkan_presented ? 1 : 0,
               static_cast<int>(result.surface_size.width),
               static_cast<int>(result.surface_size.height),
               result.viz_frame_sink_manager_created ? 1 : 0,
               result.viz_frame_sink_support_created ? 1 : 0,
               static_cast<int>(result.compositor_output_size.width),
               static_cast<int>(result.compositor_output_size.height),
               static_cast<int>(result.viz_display_output_size.width),
               static_cast<int>(result.viz_display_output_size.height),
               result.viz_display_created ? 1 : 0,
               result.cc_host_created ? 1 : 0,
               result.cc_root_layer_attached ? 1 : 0,
               result.cc_commit_requested ? 1 : 0,
               result.cc_frame_sink_requested ? 1 : 0,
               result.cc_frame_sink_bound ? 1 : 0,
               result.gpu_context_created ? 1 : 0,
               result.raster_context_created ? 1 : 0,
               result.shared_image_interface_available ? 1 : 0,
               result.compositor_frame_submitted ? 1 : 0,
               result.skia_renderer_gpu_path_reached ? 1 : 0);
  if (!result.failure_reason.empty())
    std::fprintf(stderr, " failure='%s'", result.failure_reason.c_str());
  std::fprintf(stderr, "\n");
  if (result.vulkan_presented)
    std::fprintf(stderr, "diagnostic: Chromium Vulkan swap result: SWAP_ACK\n");
  if (include_diagnostics) {
    for (const std::string& diagnostic : result.diagnostics)
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
  }
}

}  // namespace

int main(int argc, char** argv) {
  html_css_renderer::ConfigureStandaloneToolProcess();
  base::CommandLine::Init(argc, argv);
  ApplyStandaloneGpuDefaults();
  base::AtExitManager at_exit_manager;
  InitializeStandaloneFeatureList();
  base::SingleThreadTaskExecutor main_task_executor(
      base::MessagePumpType::UI, /*is_main_thread=*/true);
  if (!perfetto::Tracing::IsInitialized())
    base::trace_event::InitializeInProcessPerfettoBackend();
  ScopedBaseThreadPool thread_pool;

  html_css_renderer::RendererCreateInfo renderer;
  renderer.viewport = {800.0f, 600.0f};
  std::string css;
  enum class HtmlInputMode {
    kNone,
    kInline,
    kFile,
    kDirectory,
  };
  HtmlInputMode html_input_mode = HtmlInputMode::kNone;
  std::optional<fs::path> html_file_arg;
  std::optional<fs::path> html_directory_arg;
  fs::path html_directory_root;
  std::vector<fs::path> html_files;
  size_t current_html_index = 0;
  bool inline_html_input = false;
  std::string paint_artifact_dump_path;
  std::string resource_root;
  std::string resource_base_path;
  std::string screenshot_out;
  int screenshot_after_ms = 0;
  int quit_after_ms = 0;
  bool synthetic_input_smoke = false;
  bool synthetic_navigation_smoke = false;
  int synthetic_navigation_stress = 0;
  std::optional<html_css_renderer::Size> synthetic_resize;
  std::optional<SyntheticWheelBurst> synthetic_wheel_burst;
  std::vector<html_css_renderer::Point> synthetic_click_points;
  std::vector<html_css_renderer::Point> synthetic_sdl_click_points;
  std::vector<std::string> synthetic_sdl_text_inputs;
  std::vector<html_css_renderer::KeyboardInputKey> synthetic_sdl_key_inputs;
  int synthetic_sdl_click_repeats = 1;
  bool html_input_provided = false;
  bool resource_root_explicit = false;
  bool resource_base_path_explicit = false;
  bool full_frame_diagnostics = false;
  bool trace_stages = false;

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
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kInline;
      inline_html_input = true;
    } else if (arg.rfind("--html=", 0) == 0) {
      renderer.html = arg.substr(7);
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kInline;
      inline_html_input = true;
    } else if (arg == "--html-file") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      html_file_arg = fs::path(value);
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kFile;
      inline_html_input = false;
    } else if (arg.rfind("--html-file=", 0) == 0) {
      html_file_arg = fs::path(arg.substr(12));
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kFile;
      inline_html_input = false;
    } else if (arg == "--html-dir" || arg == "--directory") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      html_directory_arg = fs::path(value);
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kDirectory;
      inline_html_input = false;
    } else if (arg.rfind("--html-dir=", 0) == 0) {
      html_directory_arg = fs::path(arg.substr(11));
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kDirectory;
      inline_html_input = false;
    } else if (arg.rfind("--directory=", 0) == 0) {
      html_directory_arg = fs::path(arg.substr(12));
      html_input_provided = true;
      html_input_mode = HtmlInputMode::kDirectory;
      inline_html_input = false;
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
    } else if (arg == "--quit-after-ms") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      quit_after_ms = std::max(0, std::atoi(value));
    } else if (arg == "--paint-artifact-dump") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      paint_artifact_dump_path = value;
    } else if (arg == "--screenshot-out" || arg == "--snapshot-out") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      screenshot_out = value;
    } else if (arg.rfind("--screenshot-out=", 0) == 0) {
      screenshot_out = arg.substr(17);
    } else if (arg.rfind("--snapshot-out=", 0) == 0) {
      screenshot_out = arg.substr(15);
    } else if (arg == "--screenshot-after-ms") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      screenshot_after_ms = std::max(0, std::atoi(value));
    } else if (arg.rfind("--screenshot-after-ms=", 0) == 0) {
      screenshot_after_ms = std::max(0, std::atoi(arg.substr(22).c_str()));
    } else if (arg == "--resource-root") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      resource_root = value;
      resource_root_explicit = true;
    } else if (arg == "--resource-base-path") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      resource_base_path = value;
      resource_base_path_explicit = true;
    } else if (arg == "--synthetic-input-smoke") {
      synthetic_input_smoke = true;
    } else if (arg == "--synthetic-click") {
      const char* value = next_value();
      html_css_renderer::Point parsed_point;
      if (!value || !ParsePoint(value, &parsed_point)) {
        std::fprintf(stderr, "invalid --synthetic-click\n");
        return 2;
      }
      synthetic_click_points.push_back(parsed_point);
    } else if (arg.rfind("--synthetic-click=", 0) == 0) {
      html_css_renderer::Point parsed_point;
      if (!ParsePoint(arg.substr(18), &parsed_point)) {
        std::fprintf(stderr, "invalid --synthetic-click\n");
        return 2;
      }
      synthetic_click_points.push_back(parsed_point);
    } else if (arg == "--synthetic-sdl-click") {
      const char* value = next_value();
      html_css_renderer::Point parsed_point;
      if (!value || !ParsePoint(value, &parsed_point)) {
        std::fprintf(stderr, "invalid --synthetic-sdl-click\n");
        return 2;
      }
      synthetic_sdl_click_points.push_back(parsed_point);
    } else if (arg.rfind("--synthetic-sdl-click=", 0) == 0) {
      html_css_renderer::Point parsed_point;
      if (!ParsePoint(arg.substr(22), &parsed_point)) {
        std::fprintf(stderr, "invalid --synthetic-sdl-click\n");
        return 2;
      }
      synthetic_sdl_click_points.push_back(parsed_point);
    } else if (arg == "--synthetic-sdl-text") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      synthetic_sdl_text_inputs.push_back(value);
    } else if (arg.rfind("--synthetic-sdl-text=", 0) == 0) {
      synthetic_sdl_text_inputs.push_back(arg.substr(21));
    } else if (arg == "--synthetic-sdl-key") {
      const char* value = next_value();
      std::optional<html_css_renderer::KeyboardInputKey> key =
          value ? KeyboardInputKeyFromNameForCompositorViewer(value)
                : std::nullopt;
      if (!key) {
        std::fprintf(stderr, "invalid --synthetic-sdl-key\n");
        return 2;
      }
      synthetic_sdl_key_inputs.push_back(*key);
    } else if (arg.rfind("--synthetic-sdl-key=", 0) == 0) {
      std::optional<html_css_renderer::KeyboardInputKey> key =
          KeyboardInputKeyFromNameForCompositorViewer(arg.substr(20));
      if (!key) {
        std::fprintf(stderr, "invalid --synthetic-sdl-key\n");
        return 2;
      }
      synthetic_sdl_key_inputs.push_back(*key);
    } else if (arg == "--synthetic-sdl-click-repeats") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      synthetic_sdl_click_repeats = std::max(1, std::atoi(value));
    } else if (arg.rfind("--synthetic-sdl-click-repeats=", 0) == 0) {
      synthetic_sdl_click_repeats =
          std::max(1, std::atoi(arg.substr(30).c_str()));
    } else if (arg == "--synthetic-navigation-smoke") {
      synthetic_navigation_smoke = true;
    } else if (arg == "--synthetic-navigation-stress") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      synthetic_navigation_stress = std::max(0, std::atoi(value));
    } else if (arg.rfind("--synthetic-navigation-stress=", 0) == 0) {
      synthetic_navigation_stress =
          std::max(0, std::atoi(arg.substr(30).c_str()));
    } else if (arg == "--synthetic-wheel-burst") {
      const char* value = next_value();
      SyntheticWheelBurst parsed_burst;
      if (!value || !ParseWheelBurst(value, &parsed_burst)) {
        std::fprintf(stderr, "invalid --synthetic-wheel-burst\n");
        return 2;
      }
      synthetic_wheel_burst = parsed_burst;
    } else if (arg.rfind("--synthetic-wheel-burst=", 0) == 0) {
      SyntheticWheelBurst parsed_burst;
      if (!ParseWheelBurst(arg.substr(24), &parsed_burst)) {
        std::fprintf(stderr, "invalid --synthetic-wheel-burst\n");
        return 2;
      }
      synthetic_wheel_burst = parsed_burst;
    } else if (arg == "--full-frame-diagnostics") {
      full_frame_diagnostics = true;
    } else if (arg == "--trace-stages") {
      trace_stages = true;
    } else if (arg == "--synthetic-resize") {
      const char* value = next_value();
      html_css_renderer::Size parsed_size;
      if (!value || !ParseViewport(value, &parsed_size)) {
        std::fprintf(stderr, "invalid --synthetic-resize\n");
        return 2;
      }
      synthetic_resize = parsed_size;
    } else if (arg.rfind("--synthetic-resize=", 0) == 0) {
      html_css_renderer::Size parsed_size;
      if (!ParseViewport(arg.substr(19), &parsed_size)) {
        std::fprintf(stderr, "invalid --synthetic-resize\n");
        return 2;
      }
      synthetic_resize = parsed_size;
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

  if (!html_input_provided) {
    std::fprintf(
        stderr,
        "no HTML input provided; opening native HTML directory picker...\n");
    NativeDirectoryDialogResult selected_directory =
        ShowNativeHtmlDirectoryDialog();
    if (selected_directory.status == NativeDirectoryDialogStatus::kCancelled) {
      std::fprintf(stderr, "no HTML directory selected; exiting\n");
      return 0;
    }
    if (selected_directory.status != NativeDirectoryDialogStatus::kSelected ||
        selected_directory.path.empty()) {
      return 2;
    }
    html_directory_arg = selected_directory.path;
    html_input_mode = HtmlInputMode::kDirectory;
  }

  if (html_input_mode == HtmlInputMode::kFile) {
    if (!html_file_arg) {
      std::fprintf(stderr, "--html-file requires a file path\n");
      return 2;
    }
    html_files.push_back(fs::absolute(*html_file_arg));
  } else if (html_input_mode == HtmlInputMode::kDirectory) {
    if (!html_directory_arg) {
      std::fprintf(stderr, "--html-dir requires a directory path\n");
      return 2;
    }
    html_directory_root = fs::absolute(*html_directory_arg);
    html_files = EnumerateHtmlFilesForCompositorViewer(html_directory_root);
    if (html_files.empty()) {
      std::fprintf(stderr, "no .html or .htm files found in directory: %s\n",
                   html_directory_root.string().c_str());
      return 2;
    }
    std::fprintf(stderr, "selected HTML directory: %s (%zu files recursive)\n",
                 html_directory_root.string().c_str(), html_files.size());
  } else if (html_input_mode == HtmlInputMode::kNone) {
    PrintUsage();
    return 2;
  }
  if (!css.empty())
    renderer.stylesheets.push_back({"viewer", css});

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }
  SDL_Window* window = SDL_CreateWindow(
      "Chromium Viz/GPU/Vulkan SDL Host",
      std::max(1, static_cast<int>(renderer.viewport.width)),
      std::max(1, static_cast<int>(renderer.viewport.height)),
      SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  if (!SDL_StartTextInput(window)) {
    std::fprintf(stderr, "SDL_StartTextInput failed: %s\n", SDL_GetError());
  }

  SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, nullptr);
  if (!sdl_renderer) {
    std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_StopTextInput(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  struct ViewerCApiRenderer {
    blink_standalone_renderer_t* renderer = nullptr;
    blink_standalone_frame_output_t latest_output = {};
    bool output_valid = false;
    SDL_Texture* texture = nullptr;
    int texture_width = 0;
    int texture_height = 0;
    blink_standalone_pixel_format_t texture_format =
        BLINK_STANDALONE_PIXEL_FORMAT_NONE;
  } c_api;

  auto clear_c_api_output = [&]() {
    if (c_api.renderer && c_api.output_valid) {
      blink_standalone_renderer_release_latest_output(c_api.renderer);
    }
    c_api.latest_output = blink_standalone_frame_output_t{};
    c_api.output_valid = false;
  };

  auto destroy_c_api_renderer = [&]() {
    clear_c_api_output();
    if (c_api.renderer) {
      blink_standalone_renderer_destroy(c_api.renderer);
      c_api.renderer = nullptr;
      QuiesceStandaloneViewerAfterDocumentTeardown();
    }
  };

  auto destroy_texture = [&]() {
    if (c_api.texture) {
      SDL_DestroyTexture(c_api.texture);
      c_api.texture = nullptr;
    }
    c_api.texture_width = 0;
    c_api.texture_height = 0;
    c_api.texture_format = BLINK_STANDALONE_PIXEL_FORMAT_NONE;
  };

  auto current_document_label = [&]() {
    if (inline_html_input)
      return std::string("inline HTML");
    if (html_files.empty())
      return std::string("no document");
    std::ostringstream label;
    const std::string path_label =
        html_input_mode == HtmlInputMode::kDirectory &&
                !html_directory_root.empty()
            ? RelativePathForCompositorViewer(html_files[current_html_index],
                                              html_directory_root)
            : html_files[current_html_index].filename().string();
    label << "[" << (current_html_index + 1) << "/" << html_files.size()
          << "] " << path_label;
    return label.str();
  };

  auto update_window_title = [&]() {
    std::string title = "Blink standalone C API SDL host: ";
    title += c_api.output_valid ? "presented " : "waiting ";
    title += current_document_label();
    SDL_SetWindowTitle(window, title.c_str());
  };

  uint64_t frame_count = 0;
  bool screenshot_written = false;
  int document_load_error_code = 1;
  uint64_t document_start_ms = SDL_GetTicks();
  std::string current_document_html;
  std::vector<html_css_renderer::Stylesheet> current_document_stylesheets;
  std::string current_resource_root;
  std::string current_resource_base_path;
  html_css_renderer::Size current_viewport = SdlWindowPixelViewport(window);

  auto present_latest_output = [&](const char* reason) {
    clear_c_api_output();
    const blink_standalone_status_code_t output_status =
        blink_standalone_renderer_get_latest_output(c_api.renderer,
                                                    &c_api.latest_output);
    if (output_status != BLINK_STANDALONE_STATUS_OK ||
        !c_api.latest_output.pixels) {
      std::fprintf(stderr, "C API output failed after %s: %s (%s)\n",
                   reason ? reason : "frame", CApiStatusName(output_status),
                   blink_standalone_renderer_last_error(c_api.renderer));
      return false;
    }
    const SDL_PixelFormat sdl_format =
        SdlPixelFormatForCompositorViewer(c_api.latest_output.pixel_format);
    if (sdl_format == SDL_PIXELFORMAT_UNKNOWN) {
      std::fprintf(stderr, "unsupported C API pixel format: %d\n",
                   static_cast<int>(c_api.latest_output.pixel_format));
      return false;
    }
    if (!c_api.texture || c_api.texture_width != c_api.latest_output.width ||
        c_api.texture_height != c_api.latest_output.height ||
        c_api.texture_format != c_api.latest_output.pixel_format) {
      destroy_texture();
      c_api.texture = SDL_CreateTexture(
          sdl_renderer, sdl_format, SDL_TEXTUREACCESS_STREAMING,
          c_api.latest_output.width, c_api.latest_output.height);
      if (!c_api.texture) {
        std::fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
        return false;
      }
      c_api.texture_width = c_api.latest_output.width;
      c_api.texture_height = c_api.latest_output.height;
      c_api.texture_format = c_api.latest_output.pixel_format;
    }
    if (!SDL_UpdateTexture(c_api.texture, nullptr, c_api.latest_output.pixels,
                           c_api.latest_output.stride)) {
      std::fprintf(stderr, "SDL_UpdateTexture failed: %s\n", SDL_GetError());
      return false;
    }
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255);
    SDL_RenderClear(sdl_renderer);
    SDL_RenderTexture(sdl_renderer, c_api.texture, nullptr, nullptr);
    SDL_RenderPresent(sdl_renderer);
    c_api.output_valid = true;
    return true;
  };

  auto write_current_paint_artifact_dump = [&]() {
    if (!paint_artifact_dump_path.empty()) {
      std::fprintf(stderr,
                   "paint artifact dump is unavailable through the public C API viewer path\n");
    }
  };

  auto write_current_screenshot = [&]() {
    if (!c_api.output_valid) {
      std::fprintf(stderr, "screenshot capture failed: no C API raw frame output\n");
      return false;
    }
    std::optional<std::vector<uint8_t>> png =
        EncodeRawFramePngForCompositorViewer(c_api.latest_output);
    if (!png) {
      std::fprintf(stderr, "screenshot capture failed: raw frame PNG encoding failed\n");
      return false;
    }
    if (!WriteBinaryFileForCompositorViewer(screenshot_out, *png)) {
      return false;
    }
    std::fprintf(stderr, "wrote compositor screenshot: %s\n",
                 fs::absolute(fs::path(screenshot_out)).string().c_str());
    screenshot_written = true;
    return true;
  };

  auto print_c_api_frame_status = [&](const char* reason) {
    const size_t hit_count = c_api.renderer
                                 ? blink_standalone_renderer_hit_metadata_count(
                                       c_api.renderer)
                                 : 0;
    std::fprintf(stderr,
                 "frame=%llu reason=%s raw_output=%dx%d stride=%d bytes=%zu "
                 "dirty=%zu hits=%zu begin_frame=%d\n",
                 static_cast<unsigned long long>(frame_count),
                 reason ? reason : "unknown", c_api.latest_output.width,
                 c_api.latest_output.height, c_api.latest_output.stride,
                 c_api.latest_output.pixel_count,
                 c_api.latest_output.dirty_rect_count, hit_count,
                 c_api.renderer
                     ? blink_standalone_renderer_needs_begin_frame(c_api.renderer)
                     : 0);
  };

  auto advance_c_api_frame = [&](const char* reason, double timeline_seconds) {
    clear_c_api_output();
    const blink_standalone_status_code_t status =
        blink_standalone_renderer_advance_frame(c_api.renderer,
                                                timeline_seconds);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr, "C API frame failed for %s: %s (%s)\n",
                   reason ? reason : "frame", CApiStatusName(status),
                   blink_standalone_renderer_last_error(c_api.renderer));
      return false;
    }
    ++frame_count;
    if (!present_latest_output(reason)) {
      return false;
    }
    print_c_api_frame_status(reason);
    write_current_paint_artifact_dump();
    update_window_title();
    return true;
  };

  auto create_c_api_renderer_for_viewport =
      [&](html_css_renderer::Size viewport) {
    destroy_c_api_renderer();
    current_viewport = viewport;
    blink_standalone_renderer_config_t config = {};
    config.width = std::max(1, static_cast<int>(current_viewport.width));
    config.height = std::max(1, static_cast<int>(current_viewport.height));
    config.device_scale_factor = renderer.device_scale_factor;
    const blink_standalone_status_code_t create_status =
        blink_standalone_renderer_create(&config, &c_api.renderer);
    if (create_status != BLINK_STANDALONE_STATUS_OK || !c_api.renderer) {
      std::fprintf(stderr, "failed to create C API renderer: %s\n",
                   CApiStatusName(create_status));
      return false;
    }
    return true;
  };
  auto create_c_api_renderer = [&]() {
    return create_c_api_renderer_for_viewport(SdlWindowPixelViewport(window));
  };

  auto set_current_document_on_c_api_renderer = [&]() {
    const std::string html_for_api = HtmlWithInlineStylesForCompositorViewer(
        current_document_html, current_document_stylesheets);
    const blink_standalone_status_code_t document_status =
        blink_standalone_renderer_set_document_html(
            c_api.renderer, html_for_api.c_str(), current_resource_root.c_str(),
            current_resource_base_path.c_str());
    if (document_status != BLINK_STANDALONE_STATUS_OK) {
      std::fprintf(stderr, "failed to set C API document: %s (%s)\n",
                   CApiStatusName(document_status),
                   blink_standalone_renderer_last_error(c_api.renderer));
      return false;
    }
    return true;
  };

  auto load_current_document = [&](const char* reason,
                                   bool request_png_snapshot,
                                   bool force_document_reload = false) {
    document_load_error_code = 1;
    html_css_renderer::RendererCreateInfo document_renderer = renderer;
    document_renderer.viewport = SdlWindowPixelViewport(window);
    std::string effective_resource_root = resource_root;
    bool effective_resource_root_explicit = resource_root_explicit;
    std::string effective_resource_base_path = resource_base_path;
    std::string loaded_html_file;

    if (!html_files.empty()) {
      if (!LoadHtmlFileForCompositorViewer(
              html_files[current_html_index], &document_renderer,
              &loaded_html_file, &effective_resource_root,
              &effective_resource_base_path, effective_resource_root_explicit,
              resource_base_path_explicit)) {
        document_load_error_code = 2;
        return false;
      }
      std::fprintf(stderr, "loaded HTML file: %s\n", loaded_html_file.c_str());
    }

    current_document_html = document_renderer.html;
    current_document_stylesheets = document_renderer.stylesheets;
    current_resource_root = effective_resource_root;
    current_resource_base_path = effective_resource_base_path;

    if (!create_c_api_renderer() || !set_current_document_on_c_api_renderer()) {
      document_load_error_code = 1;
      return false;
    }
    document_start_ms = SDL_GetTicks();
    if (!advance_c_api_frame(reason, 0.0)) {
      document_load_error_code = 3;
      return false;
    }
    if (request_png_snapshot && !write_current_screenshot()) {
      document_load_error_code = 3;
      return false;
    }
    return true;
  };

  if (!load_current_document(
          "initial", !screenshot_out.empty() && screenshot_after_ms <= 0)) {
    destroy_c_api_renderer();
    destroy_texture();
    SDL_DestroyRenderer(sdl_renderer);
    SDL_StopTextInput(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return document_load_error_code;
  }

  int post_reset_navigation_deferrals = 0;

  auto navigate_to_file = [&](int offset, const char* reason) {
    if (html_files.empty()) {
      std::fprintf(stderr, "navigation ignored for inline HTML input\n");
      return true;
    }
    if (post_reset_navigation_deferrals > 0) {
      --post_reset_navigation_deferrals;
      QuiesceStandaloneViewerAfterDocumentTeardown();
      std::fprintf(stderr, "navigation deferred after reset: %s\n",
                   reason ? reason : "unknown");
      return true;
    }
    const int count = static_cast<int>(html_files.size());
    int next_index = static_cast<int>(current_html_index) + offset;
    next_index %= count;
    if (next_index < 0)
      next_index += count;
    current_html_index = static_cast<size_t>(next_index);
    return load_current_document(reason, false);
  };

  auto reset_current_document = [&]() {
    if (!create_c_api_renderer_for_viewport(current_viewport) ||
        !set_current_document_on_c_api_renderer() ||
        !advance_c_api_frame("reset", 0.0)) {
      return false;
    }
    post_reset_navigation_deferrals = kNavigationDeferralsAfterReset;
    QuiesceStandaloneViewerAfterDocumentTeardown();
    std::fprintf(stderr, "reset current document state: reloaded current document\n");
    return true;
  };

  float initial_mouse_x = 0.0f;
  float initial_mouse_y = 0.0f;
  const SDL_MouseButtonFlags initial_mouse_buttons =
      SDL_GetMouseState(&initial_mouse_x, &initial_mouse_y);
  std::optional<html_css_renderer::PointerState> last_sdl_pointer =
      html_css_renderer::PointerState{
          1,
          SdlWindowPointToPixelViewport(
              window, html_css_renderer::Point{initial_mouse_x,
                                               initial_mouse_y}),
          (initial_mouse_buttons & SDL_BUTTON_LMASK) != 0};

  auto send_mouse_move = [&](html_css_renderer::Point point, int modifiers) {
    return blink_standalone_renderer_mouse_move(c_api.renderer, point.x, point.y,
                                                modifiers) ==
           BLINK_STANDALONE_STATUS_OK;
  };
  auto send_mouse_button = [&](bool down, html_css_renderer::Point point,
                               html_css_renderer::MouseInputButton button,
                               int modifiers, int click_count) {
    const blink_standalone_mouse_button_t c_button =
        CApiMouseButtonFromRuntimeButton(button);
    if (down) {
      return blink_standalone_renderer_mouse_down(c_api.renderer, point.x,
                                                  point.y, c_button, modifiers,
                                                  click_count) ==
             BLINK_STANDALONE_STATUS_OK;
    }
    return blink_standalone_renderer_mouse_up(c_api.renderer, point.x, point.y,
                                              c_button, modifiers,
                                              click_count) ==
           BLINK_STANDALONE_STATUS_OK;
  };
  auto send_wheel = [&](html_css_renderer::Point point,
                        html_css_renderer::Point delta) {
    return blink_standalone_renderer_wheel(c_api.renderer, point.x, point.y,
                                           delta.x, delta.y) ==
           BLINK_STANDALONE_STATUS_OK;
  };
  auto send_key = [&](bool down, html_css_renderer::KeyboardInputKey key,
                      int modifiers) {
    const blink_standalone_key_t c_key = CApiKeyFromRuntimeKey(key);
    if (c_key == BLINK_STANDALONE_KEY_UNKNOWN) {
      return false;
    }
    if (down) {
      return blink_standalone_renderer_key_down(c_api.renderer, c_key,
                                                modifiers) ==
             BLINK_STANDALONE_STATUS_OK;
    }
    return blink_standalone_renderer_key_up(c_api.renderer, c_key, modifiers) ==
           BLINK_STANDALONE_STATUS_OK;
  };
  auto send_text = [&](const std::string& text) {
    if (text.empty()) {
      return true;
    }
    return blink_standalone_renderer_text_input(c_api.renderer, text.c_str()) ==
           BLINK_STANDALONE_STATUS_OK;
  };

  auto apply_sdl_mouse_event = [&](const SDL_Event& event, bool* needs_frame) {
    if (event.type == SDL_EVENT_MOUSE_MOTION) {
      const html_css_renderer::Point pixel_position =
          SdlWindowPointToPixelViewport(
              window,
              html_css_renderer::Point{event.motion.x, event.motion.y});
      html_css_renderer::PointerState pointer{
          1, pixel_position, (event.motion.state & SDL_BUTTON_LMASK) != 0};
      if (!last_sdl_pointer || !SamePointerState(pointer, *last_sdl_pointer)) {
        if (!send_mouse_move(
                pixel_position,
                pointer.pressed ? MouseButtonModifierForCompositorViewer(
                                      html_css_renderer::MouseInputButton::kLeft)
                                : 0)) {
          return false;
        }
        last_sdl_pointer = pointer;
        *needs_frame = true;
      }
      return true;
    }
    if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
        event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
      const html_css_renderer::MouseInputButton button =
          MouseButtonFromSdlForCompositorViewer(event.button.button);
      const html_css_renderer::Point pixel_position =
          SdlWindowPointToPixelViewport(
              window,
              html_css_renderer::Point{event.button.x, event.button.y});
      html_css_renderer::PointerState pointer{
          1, pixel_position, event.type == SDL_EVENT_MOUSE_BUTTON_DOWN};
      if (!last_sdl_pointer || !SamePointerState(pointer, *last_sdl_pointer)) {
        if (!send_mouse_button(
                event.type == SDL_EVENT_MOUSE_BUTTON_DOWN, pixel_position,
                button,
                event.type == SDL_EVENT_MOUSE_BUTTON_DOWN
                    ? MouseButtonModifierForCompositorViewer(button)
                    : 0,
                1)) {
          return false;
        }
        last_sdl_pointer = pointer;
        *needs_frame = true;
      }
      return true;
    }
    if (event.type == SDL_EVENT_MOUSE_WHEEL) {
      float mouse_x = 0.0f;
      float mouse_y = 0.0f;
      SDL_GetMouseState(&mouse_x, &mouse_y);
      const html_css_renderer::Point pixel_position =
          SdlWindowPointToPixelViewport(
              window, html_css_renderer::Point{mouse_x, mouse_y});
      if (!send_wheel(pixel_position,
                      html_css_renderer::Point{-event.wheel.x * 48.0f,
                                               -event.wheel.y * 48.0f})) {
        return false;
      }
      *needs_frame = true;
      return true;
    }
    return false;
  };

  auto run_update_frame = [&](const char* reason, double timeline_seconds) {
    return advance_c_api_frame(reason, timeline_seconds);
  };

  if (synthetic_input_smoke || synthetic_resize || synthetic_wheel_burst ||
      synthetic_navigation_smoke || synthetic_navigation_stress > 0 ||
      !synthetic_click_points.empty()) {
    bool synthetic_ok = c_api.output_valid;
    double synthetic_time = 1.0 / 60.0;
    if (synthetic_navigation_smoke) {
      synthetic_ok = navigate_to_file(1, "synthetic_next") && synthetic_ok;
      synthetic_ok = navigate_to_file(-1, "synthetic_previous") && synthetic_ok;
      synthetic_ok = reset_current_document() && synthetic_ok;
      synthetic_time += 3.0 / 60.0;
    }
    for (int i = 0; i < synthetic_navigation_stress; ++i) {
      const char* reason = nullptr;
      if (i % 13 == 12) {
        reason = "synthetic_stress_reset";
        synthetic_ok = reset_current_document() && synthetic_ok;
      } else if (i % 11 == 10) {
        reason = "synthetic_stress_previous";
        synthetic_ok = navigate_to_file(-1, reason) && synthetic_ok;
      } else {
        reason = "synthetic_stress_next";
        synthetic_ok = navigate_to_file(1, reason) && synthetic_ok;
      }
      synthetic_time += 1.0 / 60.0;
      if (!synthetic_ok) {
        break;
      }
      if (synthetic_input_smoke) {
        const html_css_renderer::Point point{
            32.0f + static_cast<float>((i * 37) % 320),
            32.0f + static_cast<float>((i * 23) % 220)};
        synthetic_ok = send_mouse_move(point, 0) &&
                       run_update_frame("synthetic_stress_pointer_move",
                                        synthetic_time) &&
                       synthetic_ok;
        synthetic_time += 1.0 / 60.0;
        synthetic_ok = send_mouse_button(
                           true, point, html_css_renderer::MouseInputButton::kLeft,
                           MouseButtonModifierForCompositorViewer(
                               html_css_renderer::MouseInputButton::kLeft),
                           1) &&
                       run_update_frame("synthetic_stress_pointer_down",
                                        synthetic_time) &&
                       synthetic_ok;
        synthetic_time += 1.0 / 60.0;
        synthetic_ok = send_mouse_button(
                           false, point,
                           html_css_renderer::MouseInputButton::kLeft, 0, 1) &&
                       run_update_frame("synthetic_stress_pointer_up",
                                        synthetic_time) &&
                       synthetic_ok;
        synthetic_time += 1.0 / 60.0;
        synthetic_ok = send_wheel(point, html_css_renderer::Point{0.0f, 48.0f}) &&
                       run_update_frame("synthetic_stress_wheel",
                                        synthetic_time) &&
                       synthetic_ok;
        synthetic_time += 1.0 / 60.0;
        if (!synthetic_ok) {
          break;
        }
      }
    }
    if (synthetic_resize) {
      SDL_SetWindowSize(window, static_cast<int>(synthetic_resize->width),
                        static_cast<int>(synthetic_resize->height));
      current_viewport = *synthetic_resize;
      synthetic_ok =
          blink_standalone_renderer_set_viewport(
              c_api.renderer, static_cast<int>(current_viewport.width),
              static_cast<int>(current_viewport.height),
              renderer.device_scale_factor) == BLINK_STANDALONE_STATUS_OK &&
          run_update_frame("synthetic_resize", synthetic_time) && synthetic_ok;
      if (!screenshot_out.empty() && !screenshot_written &&
          !write_current_screenshot()) {
        synthetic_ok = false;
      }
      synthetic_time += 1.0 / 60.0;
    }
    if (synthetic_wheel_burst) {
      const html_css_renderer::Point position{32.0f, 32.0f};
      for (int i = 0; i < synthetic_wheel_burst->count; ++i) {
        synthetic_ok = send_wheel(position, synthetic_wheel_burst->delta) &&
                       synthetic_ok;
      }
      synthetic_ok = run_update_frame("synthetic_wheel_burst", synthetic_time) &&
                     synthetic_ok;
      std::fprintf(stderr,
                   "synthetic_wheel_burst_result count=%d unit_delta=%.3f,%.3f "
                   "raw_output=%dx%d\n",
                   synthetic_wheel_burst->count,
                   synthetic_wheel_burst->delta.x,
                   synthetic_wheel_burst->delta.y, c_api.latest_output.width,
                   c_api.latest_output.height);
      synthetic_time += 1.0 / 60.0;
    }
    for (const html_css_renderer::Point& point : synthetic_click_points) {
      synthetic_ok = send_mouse_move(point, 0) &&
                     run_update_frame("synthetic_click_move", synthetic_time) &&
                     synthetic_ok;
      synthetic_time += 1.0 / 60.0;
      synthetic_ok = send_mouse_button(
                         true, point, html_css_renderer::MouseInputButton::kLeft,
                         MouseButtonModifierForCompositorViewer(
                             html_css_renderer::MouseInputButton::kLeft),
                         1) &&
                     run_update_frame("synthetic_click_down", synthetic_time) &&
                     synthetic_ok;
      synthetic_time += 1.0 / 60.0;
      synthetic_ok = send_mouse_button(
                         false, point,
                         html_css_renderer::MouseInputButton::kLeft, 0, 1) &&
                     run_update_frame("synthetic_click_up", synthetic_time) &&
                     synthetic_ok;
      synthetic_time += 1.0 / 60.0;
    }
    if (synthetic_input_smoke) {
      const html_css_renderer::Point point{32.0f, 32.0f};
      synthetic_ok = send_mouse_move(point, 0) &&
                     run_update_frame("synthetic_pointer_move", synthetic_time) &&
                     synthetic_ok;
      synthetic_time += 1.0 / 60.0;
      synthetic_ok = send_mouse_button(
                         true, point, html_css_renderer::MouseInputButton::kLeft,
                         MouseButtonModifierForCompositorViewer(
                             html_css_renderer::MouseInputButton::kLeft),
                         1) &&
                     run_update_frame("synthetic_pointer_down", synthetic_time) &&
                     synthetic_ok;
      synthetic_time += 1.0 / 60.0;
      synthetic_ok = send_mouse_button(
                         false, point,
                         html_css_renderer::MouseInputButton::kLeft, 0, 1) &&
                     run_update_frame("synthetic_pointer_up", synthetic_time) &&
                     synthetic_ok;
      synthetic_time += 1.0 / 60.0;
      synthetic_ok = send_wheel(point, html_css_renderer::Point{0.0f, 48.0f}) &&
                     run_update_frame("synthetic_wheel", synthetic_time) &&
                     synthetic_ok;
    }

    const int exit_code = synthetic_ok ? 0 : 5;
    destroy_c_api_renderer();
    destroy_texture();
    SDL_DestroyRenderer(sdl_renderer);
    SDL_StopTextInput(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return exit_code;
  }

  const uint64_t start_ms = SDL_GetTicks();
  uint64_t advanced_update_frames = 0;
  uint64_t idle_waits = 0;
  uint64_t idle_no_frame_ticks = 0;
  enum class NavigationAction {
    kNone,
    kPrevious,
    kNext,
    kReset,
  };
  std::deque<SDL_Event> pending_synthetic_sdl_events;
  for (const html_css_renderer::Point& point : synthetic_sdl_click_points) {
    AppendSyntheticSdlClickEventsForCompositorViewer(
        point, synthetic_sdl_click_repeats, &pending_synthetic_sdl_events);
  }
  std::deque<std::string> pending_synthetic_sdl_text_inputs(
      synthetic_sdl_text_inputs.begin(), synthetic_sdl_text_inputs.end());
  std::deque<html_css_renderer::KeyboardInputKey> pending_synthetic_sdl_key_inputs(
      synthetic_sdl_key_inputs.begin(), synthetic_sdl_key_inputs.end());
  if (!pending_synthetic_sdl_events.empty()) {
    std::fprintf(stderr, "synthetic_sdl_click_queue events=%zu repeats=%d\n",
                 pending_synthetic_sdl_events.size(),
                 synthetic_sdl_click_repeats);
  }
  bool running = true;
  while (running) {
    SDL_Event event;
    bool needs_frame =
        blink_standalone_renderer_needs_begin_frame(c_api.renderer) != 0;
    NavigationAction navigation_action = NavigationAction::kNone;
    double timeline_seconds =
        static_cast<double>(SDL_GetTicks() - document_start_ms) / 1000.0;

    auto handle_event = [&](const SDL_Event& event) {
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
        running = false;
        return false;
      } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_F1) {
        navigation_action = NavigationAction::kPrevious;
        return false;
      } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_F2) {
        navigation_action = NavigationAction::kNext;
        return false;
      } else if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_F5) {
        navigation_action = NavigationAction::kReset;
        return false;
      } else if (event.type == SDL_EVENT_TEXT_INPUT) {
        if (!send_text(event.text.text ? event.text.text : "")) {
          return false;
        }
        needs_frame = true;
        return true;
      } else if (event.type == SDL_EVENT_KEY_DOWN ||
                 event.type == SDL_EVENT_KEY_UP) {
        const html_css_renderer::KeyboardInputKey key =
            KeyboardInputKeyFromSdlForCompositorViewer(event.key.key);
        if (key != html_css_renderer::KeyboardInputKey::kUnknown) {
          if (!send_key(event.type == SDL_EVENT_KEY_DOWN, key,
                        KeyboardModifiersFromSdlForCompositorViewer(
                            event.key.mod))) {
            return false;
          }
          needs_frame = true;
          return event.type == SDL_EVENT_KEY_DOWN;
        }
        return false;
      } else if (event.type == SDL_EVENT_WINDOW_RESIZED ||
                 event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED) {
        const html_css_renderer::Size new_viewport =
            SdlWindowPixelViewport(window);
        if (!SameViewportSize(new_viewport, current_viewport)) {
          current_viewport = new_viewport;
          const blink_standalone_status_code_t viewport_status =
              blink_standalone_renderer_set_viewport(
                  c_api.renderer, static_cast<int>(current_viewport.width),
                  static_cast<int>(current_viewport.height),
                  renderer.device_scale_factor);
          if (viewport_status != BLINK_STANDALONE_STATUS_OK) {
            std::fprintf(stderr, "C API viewport update failed: %s (%s)\n",
                         CApiStatusName(viewport_status),
                         blink_standalone_renderer_last_error(c_api.renderer));
            return false;
          }
          needs_frame = true;
        }
        return false;
      } else if (apply_sdl_mouse_event(event, &needs_frame)) {
        return needs_frame && (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN ||
                               event.type == SDL_EVENT_MOUSE_BUTTON_UP);
      }
      return false;
    };

    auto drain_pending_navigation_events =
        [&](NavigationAction initial_action) {
          bool reset_requested = initial_action == NavigationAction::kReset;
          int navigation_offset = 0;
          if (initial_action == NavigationAction::kPrevious) {
            navigation_offset = -1;
          } else if (initial_action == NavigationAction::kNext) {
            navigation_offset = 1;
          }

          SDL_Event pending_event;
          while (SDL_PollEvent(&pending_event)) {
            if (pending_event.type == SDL_EVENT_QUIT ||
                (pending_event.type == SDL_EVENT_KEY_DOWN &&
                 pending_event.key.key == SDLK_ESCAPE)) {
              running = false;
              continue;
            }
            if (!IsDirectoryNavigationKeyDownEventForCompositorViewer(
                    pending_event)) {
              continue;
            }
            if (pending_event.key.key == SDLK_F5) {
              reset_requested = true;
              navigation_offset = 0;
            } else if (!reset_requested && pending_event.key.key == SDLK_F1) {
              --navigation_offset;
            } else if (!reset_requested && pending_event.key.key == SDLK_F2) {
              ++navigation_offset;
            }
          }

          if (reset_requested) {
            return NavigationAction::kReset;
          }
          if (navigation_offset < 0) {
            return NavigationAction::kPrevious;
          }
          if (navigation_offset > 0) {
            return NavigationAction::kNext;
          }
          return NavigationAction::kNone;
        };

    auto screenshot_due = [&]() {
      return !screenshot_out.empty() && !screenshot_written &&
             screenshot_after_ms > 0 &&
             SDL_GetTicks() - start_ms >=
                 static_cast<uint64_t>(screenshot_after_ms);
    };

    bool flush_frame_now = false;
    if (!pending_synthetic_sdl_events.empty()) {
      event = pending_synthetic_sdl_events.front();
      pending_synthetic_sdl_events.pop_front();
      flush_frame_now = handle_event(event);
    } else if (!pending_synthetic_sdl_text_inputs.empty()) {
      const std::string text = pending_synthetic_sdl_text_inputs.front();
      pending_synthetic_sdl_text_inputs.pop_front();
      if (send_text(text)) {
        needs_frame = true;
        flush_frame_now = true;
      }
    } else if (!pending_synthetic_sdl_key_inputs.empty()) {
      const html_css_renderer::KeyboardInputKey key =
          pending_synthetic_sdl_key_inputs.front();
      pending_synthetic_sdl_key_inputs.pop_front();
      if (send_key(true, key,
                   KeyboardModifiersFromSdlForCompositorViewer(SDL_GetModState()))) {
        needs_frame = true;
        flush_frame_now = true;
      }
    } else if (!needs_frame && !screenshot_due()) {
      int wait_ms = 50;
      const uint64_t now_ms = SDL_GetTicks();
      if (!screenshot_out.empty() && !screenshot_written &&
          screenshot_after_ms > 0) {
        const uint64_t capture_ms = static_cast<uint64_t>(screenshot_after_ms);
        const int until_capture_ms =
            capture_ms > now_ms - start_ms
                ? static_cast<int>(capture_ms - (now_ms - start_ms))
                : 0;
        wait_ms = std::min(wait_ms, until_capture_ms);
      }
      if (quit_after_ms > 0) {
        const uint64_t quit_ms = static_cast<uint64_t>(quit_after_ms);
        const int until_quit_ms =
            quit_ms > now_ms - start_ms
                ? static_cast<int>(quit_ms - (now_ms - start_ms))
                : 0;
        wait_ms = std::min(wait_ms, until_quit_ms);
      }
      wait_ms = std::max(0, wait_ms);
      if (SDL_WaitEventTimeout(&event, wait_ms)) {
        flush_frame_now = handle_event(event);
      } else {
        ++idle_waits;
      }
    }

    while (!flush_frame_now && SDL_PollEvent(&event)) {
      flush_frame_now = handle_event(event);
    }

    if (navigation_action != NavigationAction::kNone) {
      navigation_action = drain_pending_navigation_events(navigation_action);
      bool navigation_ok = false;
      if (navigation_action == NavigationAction::kPrevious) {
        navigation_ok = navigate_to_file(-1, "previous");
      } else if (navigation_action == NavigationAction::kNext) {
        navigation_ok = navigate_to_file(1, "next");
      } else if (navigation_action == NavigationAction::kReset) {
        navigation_ok = reset_current_document();
      } else {
        continue;
      }
      if (!navigation_ok) {
        destroy_c_api_renderer();
        destroy_texture();
        SDL_DestroyRenderer(sdl_renderer);
        SDL_StopTextInput(window);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return document_load_error_code;
      }
      ++advanced_update_frames;
      continue;
    }

    if (screenshot_due()) {
      if (!write_current_screenshot()) {
        return 3;
      }
    }

    if (needs_frame) {
      timeline_seconds =
          static_cast<double>(SDL_GetTicks() - document_start_ms) / 1000.0;
      if (!run_update_frame("update", timeline_seconds)) {
        return 4;
      }
      ++advanced_update_frames;
    } else {
      ++idle_no_frame_ticks;
    }

    if (quit_after_ms > 0 && SDL_GetTicks() - start_ms >=
                                 static_cast<uint64_t>(quit_after_ms)) {
      running = false;
    }
    if (needs_frame)
      SDL_Delay(8);
    if (!synthetic_sdl_click_points.empty() &&
        pending_synthetic_sdl_events.empty() && quit_after_ms <= 0 &&
        pending_synthetic_sdl_text_inputs.empty() &&
        pending_synthetic_sdl_key_inputs.empty() && !needs_frame) {
      running = false;
    }
    if (!synthetic_sdl_text_inputs.empty() &&
        pending_synthetic_sdl_events.empty() &&
        pending_synthetic_sdl_text_inputs.empty() &&
        pending_synthetic_sdl_key_inputs.empty() && quit_after_ms <= 0 &&
        !needs_frame) {
      running = false;
    }
    if (!synthetic_sdl_key_inputs.empty() &&
        pending_synthetic_sdl_events.empty() &&
        pending_synthetic_sdl_text_inputs.empty() &&
        pending_synthetic_sdl_key_inputs.empty() && quit_after_ms <= 0 &&
        !needs_frame) {
      running = false;
    }
  }

  std::fprintf(stderr,
               "idle_summary advanced_update_frames=%llu idle_waits=%llu "
               "idle_no_frame_ticks=%llu\n",
               static_cast<unsigned long long>(advanced_update_frames),
               static_cast<unsigned long long>(idle_waits),
               static_cast<unsigned long long>(idle_no_frame_ticks));

  const int exit_code = c_api.output_valid ? 0 : 4;
  destroy_c_api_renderer();
  destroy_texture();
  SDL_DestroyRenderer(sdl_renderer);
  SDL_StopTextInput(window);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return exit_code;
}
