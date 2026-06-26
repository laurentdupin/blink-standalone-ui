// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/renderer_c_api.h"

#include <algorithm>
#include <cctype>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/message_loop/message_pump_type.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/trace_event/trace_event_impl.h"
#include "gpu/command_buffer/service/gpu_switches.h"
#include "html_css_renderer/compositor_runtime.h"
#include "html_css_renderer/standalone_process.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "third_party/perfetto/include/perfetto/tracing/tracing.h"

namespace {

void EnsureStandaloneCApiProcessInitialized() {
  static std::once_flag once;
  std::call_once(once, [] {
    html_css_renderer::ConfigureStandaloneToolProcess();
    if (!base::CommandLine::InitializedForCurrentProcess()) {
      const char* argv[] = {"blink_standalone_renderer"};
      base::CommandLine::Init(1, argv);
    }
    const bool need_task_executor =
        !base::SingleThreadTaskRunner::HasCurrentDefault();
    if (need_task_executor) {
      static base::AtExitManager* at_exit_manager = new base::AtExitManager();
      (void)at_exit_manager;
    }
    html_css_renderer::InitializeStandaloneIcu();
    if (!base::FeatureList::GetInstance()) {
      const base::CommandLine* command_line =
          base::CommandLine::ForCurrentProcess();
      base::FeatureList::InitInstance(
          command_line->GetSwitchValueASCII(switches::kEnableFeatures),
          command_line->GetSwitchValueASCII(switches::kDisableFeatures), {});
    }
    static base::SingleThreadTaskExecutor* task_executor = nullptr;
    if (need_task_executor) {
      task_executor = new base::SingleThreadTaskExecutor(
          base::MessagePumpType::DEFAULT, /*is_main_thread=*/true);
    }
    if (!base::ThreadPoolInstance::Get()) {
      base::ThreadPoolInstance::CreateAndStartWithDefaultParams(
          "BlinkStandaloneRendererCApi");
    }
    if (!perfetto::Tracing::IsInitialized()) {
      base::trace_event::InitializeInProcessPerfettoBackend();
    }
  });
}

std::string LowerAscii(std::string value) {
  std::transform(value.begin(), value.end(), value.begin(), [](char c) {
    return static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
  });
  return value;
}

bool HasInlineEventHandlerAttribute(const std::string& lower_html) {
  size_t tag = lower_html.find('<');
  while (tag != std::string::npos) {
    const size_t end = lower_html.find('>', tag + 1);
    if (end == std::string::npos) {
      return false;
    }
    for (size_t i = tag + 1; i + 3 < end; ++i) {
      if (!std::isspace(static_cast<unsigned char>(lower_html[i]))) {
        continue;
      }
      size_t name = i + 1;
      while (name < end &&
             std::isspace(static_cast<unsigned char>(lower_html[name]))) {
        ++name;
      }
      if (name + 2 >= end || lower_html[name] != 'o' ||
          lower_html[name + 1] != 'n' ||
          !std::isalpha(static_cast<unsigned char>(lower_html[name + 2]))) {
        continue;
      }
      size_t cursor = name + 3;
      while (cursor < end &&
             (std::isalnum(static_cast<unsigned char>(lower_html[cursor])) ||
              lower_html[cursor] == '-' || lower_html[cursor] == '_')) {
        ++cursor;
      }
      while (cursor < end &&
             std::isspace(static_cast<unsigned char>(lower_html[cursor]))) {
        ++cursor;
      }
      if (cursor < end && lower_html[cursor] == '=') {
        return true;
      }
    }
    tag = lower_html.find('<', end + 1);
  }
  return false;
}

bool ContainsJavaScriptScheme(const std::string& lower_html) {
  std::string compact;
  compact.reserve(lower_html.size());
  for (char c : lower_html) {
    const unsigned char byte = static_cast<unsigned char>(c);
    if (std::isspace(byte) || c == '\0') {
      continue;
    }
    compact.push_back(c);
  }
  return compact.find("javascript:") != std::string::npos;
}

bool ViolatesNoScriptProfile(const std::string& html) {
  const std::string lower = LowerAscii(html);
  return lower.find("<script") != std::string::npos ||
         ContainsJavaScriptScheme(lower) ||
         lower.find("<iframe") != std::string::npos ||
         lower.find("<object") != std::string::npos ||
         lower.find("<embed") != std::string::npos ||
         HasInlineEventHandlerAttribute(lower);
}

blink_standalone_rect_t ToCRect(const html_css_renderer::Rect& rect) {
  return blink_standalone_rect_t{rect.x, rect.y, rect.width, rect.height};
}

blink_standalone_pixel_format_t ToCPixelFormat(
    html_css_renderer::RawFramePixelFormat format) {
  switch (format) {
    case html_css_renderer::RawFramePixelFormat::kRGBA8:
      return BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
    case html_css_renderer::RawFramePixelFormat::kBGRA8:
      return BLINK_STANDALONE_PIXEL_FORMAT_BGRA8;
    case html_css_renderer::RawFramePixelFormat::kNone:
      return BLINK_STANDALONE_PIXEL_FORMAT_NONE;
  }
  return BLINK_STANDALONE_PIXEL_FORMAT_NONE;
}

html_css_renderer::MouseInputButton ToRuntimeMouseButton(
    blink_standalone_mouse_button_t button) {
  switch (button) {
    case BLINK_STANDALONE_MOUSE_BUTTON_LEFT:
      return html_css_renderer::MouseInputButton::kLeft;
    case BLINK_STANDALONE_MOUSE_BUTTON_MIDDLE:
      return html_css_renderer::MouseInputButton::kMiddle;
    case BLINK_STANDALONE_MOUSE_BUTTON_RIGHT:
      return html_css_renderer::MouseInputButton::kRight;
    case BLINK_STANDALONE_MOUSE_BUTTON_NONE:
      return html_css_renderer::MouseInputButton::kNone;
  }
  return html_css_renderer::MouseInputButton::kNone;
}

html_css_renderer::KeyboardInputKey ToRuntimeKeyboardKey(blink_standalone_key_t key) {
  switch (key) {
    case BLINK_STANDALONE_KEY_BACKSPACE:
      return html_css_renderer::KeyboardInputKey::kBackspace;
    case BLINK_STANDALONE_KEY_TAB:
      return html_css_renderer::KeyboardInputKey::kTab;
    case BLINK_STANDALONE_KEY_ENTER:
      return html_css_renderer::KeyboardInputKey::kEnter;
    case BLINK_STANDALONE_KEY_DELETE:
      return html_css_renderer::KeyboardInputKey::kDelete;
    case BLINK_STANDALONE_KEY_UNKNOWN:
      return html_css_renderer::KeyboardInputKey::kUnknown;
  }
  return html_css_renderer::KeyboardInputKey::kUnknown;
}

bool PointInRect(float x, float y, const html_css_renderer::Rect& rect) {
  return x >= rect.x && y >= rect.y && x < rect.x + rect.width &&
         y < rect.y + rect.height;
}

void CopyHitMetadata(const html_css_renderer::HitTestEntry& source,
                     blink_standalone_hit_metadata_t* hit) {
  *hit = blink_standalone_hit_metadata_t{};
  hit->element_id = source.element_id.c_str();
  hit->tag_name = source.tag_name.c_str();
  hit->data_godot_action = source.data_godot_action.c_str();
  hit->bounds = ToCRect(source.bounds);
  hit->disabled = source.disabled ? 1 : 0;
  hit->editable = source.editable ? 1 : 0;
  hit->checked = source.checked ? 1 : 0;
  hit->focused = source.focused ? 1 : 0;
}

}  // namespace

struct blink_standalone_renderer {
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime;
  html_css_renderer::Size viewport = {800.0f, 600.0f};
  float device_scale_factor = 1.0f;
  bool no_script_profile = false;
  std::string html;
  std::string resource_root;
  std::string resource_base_path;
  html_css_renderer::CompositorFrameResult latest_result;
  std::vector<blink_standalone_rect_t> dirty_rects;
  std::vector<html_css_renderer::MouseInputEvent> pending_mouse_events;
  std::vector<html_css_renderer::KeyboardInputEvent> pending_keyboard_events;
  std::optional<html_css_renderer::WheelInput> pending_wheel;
  std::string last_error;
};

namespace {

blink_standalone_status_code_t InitializeRuntime(blink_standalone_renderer* renderer) {
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = renderer->viewport;
  create_info.renderer.device_scale_factor = renderer->device_scale_factor;
  create_info.renderer.no_script_profile = renderer->no_script_profile;
  create_info.renderer.transparent_background = renderer->no_script_profile;
  create_info.no_script_profile = renderer->no_script_profile;
  create_info.transparent_background = renderer->no_script_profile;
  renderer->runtime =
      html_css_renderer::CreateStandaloneCompositorRuntime(std::move(create_info));
  std::vector<std::string> diagnostics;
  if (!renderer->runtime || !renderer->runtime->Initialize(&diagnostics)) {
    renderer->last_error = "failed to initialize standalone compositor runtime";
    return BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED;
  }
  return BLINK_STANDALONE_STATUS_OK;
}

void ClearPendingInput(blink_standalone_renderer* renderer) {
  renderer->pending_mouse_events.clear();
  renderer->pending_keyboard_events.clear();
  renderer->pending_wheel.reset();
}

void AppendMouseEvent(blink_standalone_renderer* renderer,
                      html_css_renderer::MouseInputEventType type,
                      float x,
                      float y,
                      blink_standalone_mouse_button_t button,
                      int modifiers,
                      int click_count) {
  html_css_renderer::MouseInputEvent event;
  event.type = type;
  event.position = {x, y};
  event.button = ToRuntimeMouseButton(button);
  event.modifiers = modifiers;
  event.click_count = click_count;
  renderer->pending_mouse_events.push_back(event);
}

void AppendKeyboardEvent(blink_standalone_renderer* renderer,
                         html_css_renderer::KeyboardInputEventType type,
                         blink_standalone_key_t key,
                         std::string text,
                         int modifiers) {
  html_css_renderer::KeyboardInputEvent event;
  event.type = type;
  event.key = ToRuntimeKeyboardKey(key);
  event.text = std::move(text);
  event.modifiers = modifiers;
  renderer->pending_keyboard_events.push_back(std::move(event));
}

}  // namespace

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_create(
    const blink_standalone_renderer_config_t* config,
    blink_standalone_renderer_t** renderer_out) {
  if (!renderer_out) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  *renderer_out = nullptr;
  EnsureStandaloneCApiProcessInitialized();
  auto renderer = std::make_unique<blink_standalone_renderer>();
  if (config) {
    if (config->width > 0) {
      renderer->viewport.width = static_cast<float>(config->width);
    }
    if (config->height > 0) {
      renderer->viewport.height = static_cast<float>(config->height);
    }
    if (config->device_scale_factor > 0.0f) {
      renderer->device_scale_factor = config->device_scale_factor;
    }
    renderer->no_script_profile = config->no_script_profile != 0;
  }

  blink_standalone_status_code_t status = InitializeRuntime(renderer.get());
  if (status != BLINK_STANDALONE_STATUS_OK) {
    *renderer_out = renderer.release();
    return status;
  }

  *renderer_out = renderer.release();
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_destroy(
    blink_standalone_renderer_t* renderer) {
  if (!renderer) {
    return;
  }
  delete renderer;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_document_html(
    blink_standalone_renderer_t* renderer,
    const char* html,
    const char* resource_root,
    const char* resource_base_path) {
  if (!renderer || !html) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  renderer->last_error.clear();
  renderer->html = html;
  if (renderer->no_script_profile && ViolatesNoScriptProfile(renderer->html)) {
    renderer->last_error =
        "document rejected by no-script profile (script/event handler/navigation surface)";
    renderer->html.clear();
    return BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED;
  }
  renderer->resource_root = resource_root ? resource_root : "";
  renderer->resource_base_path = resource_base_path ? resource_base_path : "";
  renderer->latest_result = html_css_renderer::CompositorFrameResult();
  renderer->dirty_rects.clear();
  ClearPendingInput(renderer);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_viewport(
    blink_standalone_renderer_t* renderer,
    int width,
    int height,
    float device_scale_factor) {
  if (!renderer || width <= 0 || height <= 0 || device_scale_factor <= 0.0f) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  renderer->viewport = {static_cast<float>(width), static_cast<float>(height)};
  renderer->device_scale_factor = device_scale_factor;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_advance_frame(
    blink_standalone_renderer_t* renderer,
    double timeline_time_seconds) {
  if (!renderer || !renderer->runtime) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  renderer->last_error.clear();
  html_css_renderer::FrameInput input;
  input.viewport = renderer->viewport;
  input.html_override = renderer->html;
  input.resource_root = renderer->resource_root;
  input.resource_base_path = renderer->resource_base_path;
  input.timeline_time_seconds = timeline_time_seconds;
  input.request_raw_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kFull;
  input.mouse_events = std::move(renderer->pending_mouse_events);
  input.keyboard_events = std::move(renderer->pending_keyboard_events);
  input.wheel = renderer->pending_wheel;
  ClearPendingInput(renderer);
  renderer->latest_result = renderer->runtime->AdvanceFrame(input);
  renderer->dirty_rects.clear();
  for (const html_css_renderer::Rect& rect :
       renderer->latest_result.raw_frame.dirty_rects) {
    renderer->dirty_rects.push_back(ToCRect(rect));
  }
  if (!renderer->latest_result.raw_frame.pixels.empty()) {
    return BLINK_STANDALONE_STATUS_OK;
  }
  renderer->last_error =
      renderer->latest_result.raw_frame_failure.empty()
          ? "raw frame output was not produced"
          : renderer->latest_result.raw_frame_failure;
  return BLINK_STANDALONE_STATUS_RENDER_FAILED;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API int blink_standalone_renderer_needs_begin_frame(
    const blink_standalone_renderer_t* renderer) {
  return renderer && renderer->latest_result.needs_begin_frame ? 1 : 0;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_mouse_move(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    int modifiers) {
  if (!renderer) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  AppendMouseEvent(renderer, html_css_renderer::MouseInputEventType::kMove, x, y,
                   BLINK_STANDALONE_MOUSE_BUTTON_NONE, modifiers, 0);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_mouse_down(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    blink_standalone_mouse_button_t button,
    int modifiers,
    int click_count) {
  if (!renderer || ToRuntimeMouseButton(button) ==
                       html_css_renderer::MouseInputButton::kNone) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  AppendMouseEvent(renderer, html_css_renderer::MouseInputEventType::kDown, x, y,
                   button, modifiers, click_count > 0 ? click_count : 1);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_mouse_up(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    blink_standalone_mouse_button_t button,
    int modifiers,
    int click_count) {
  if (!renderer || ToRuntimeMouseButton(button) ==
                       html_css_renderer::MouseInputButton::kNone) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  AppendMouseEvent(renderer, html_css_renderer::MouseInputEventType::kUp, x, y,
                   button, modifiers, click_count > 0 ? click_count : 1);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_wheel(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    float delta_x,
    float delta_y) {
  if (!renderer) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  if (!renderer->pending_wheel) {
    renderer->pending_wheel = html_css_renderer::WheelInput();
  }
  renderer->pending_wheel->position = {x, y};
  renderer->pending_wheel->delta.x += delta_x;
  renderer->pending_wheel->delta.y += delta_y;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_key_down(
    blink_standalone_renderer_t* renderer,
    blink_standalone_key_t key,
    int modifiers) {
  if (!renderer || ToRuntimeKeyboardKey(key) ==
                       html_css_renderer::KeyboardInputKey::kUnknown) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  AppendKeyboardEvent(renderer, html_css_renderer::KeyboardInputEventType::kKeyDown,
                      key, std::string(), modifiers);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_key_up(
    blink_standalone_renderer_t* renderer,
    blink_standalone_key_t key,
    int modifiers) {
  if (!renderer || ToRuntimeKeyboardKey(key) ==
                       html_css_renderer::KeyboardInputKey::kUnknown) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  AppendKeyboardEvent(renderer, html_css_renderer::KeyboardInputEventType::kKeyUp,
                      key, std::string(), modifiers);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_text_input(
    blink_standalone_renderer_t* renderer,
    const char* utf8_text) {
  if (!renderer || !utf8_text) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  AppendKeyboardEvent(renderer, html_css_renderer::KeyboardInputEventType::kText,
                      BLINK_STANDALONE_KEY_UNKNOWN, utf8_text, 0);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_reset_state(
    blink_standalone_renderer_t* renderer) {
  if (!renderer) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  renderer->last_error.clear();
  renderer->runtime.reset();
  renderer->latest_result = html_css_renderer::CompositorFrameResult();
  renderer->dirty_rects.clear();
  ClearPendingInput(renderer);
  return InitializeRuntime(renderer);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_latest_output(
    blink_standalone_renderer_t* renderer,
    blink_standalone_frame_output_t* output) {
  if (!renderer || !output) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  const html_css_renderer::RawFrameOutput& raw =
      renderer->latest_result.raw_frame;
  *output = blink_standalone_frame_output_t{};
  output->pixels = raw.pixels.empty() ? nullptr : raw.pixels.data();
  output->pixel_count = raw.pixels.size();
  output->width = raw.width;
  output->height = raw.height;
  output->stride = raw.stride;
  output->pixel_format = ToCPixelFormat(raw.pixel_format);
  output->premultiplied_alpha = raw.premultiplied_alpha ? 1 : 0;
  output->dirty_rects =
      renderer->dirty_rects.empty() ? nullptr : renderer->dirty_rects.data();
  output->dirty_rect_count = renderer->dirty_rects.size();
  return output->pixels ? BLINK_STANDALONE_STATUS_OK : BLINK_STANDALONE_STATUS_RENDER_FAILED;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_release_latest_output(
    blink_standalone_renderer_t* renderer) {
  if (!renderer) {
    return;
  }
  renderer->latest_result.raw_frame = html_css_renderer::RawFrameOutput();
  renderer->latest_result.png_snapshot_bytes.clear();
  renderer->dirty_rects.clear();
}

extern "C" BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_hit_metadata_count(
    const blink_standalone_renderer_t* renderer) {
  return renderer ? renderer->latest_result.hit_test_entries.size() : 0;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_hit_metadata(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_hit_metadata_t* hit) {
  if (!renderer || !hit ||
      index >= renderer->latest_result.hit_test_entries.size()) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  const html_css_renderer::HitTestEntry& source =
      renderer->latest_result.hit_test_entries[index];
  CopyHitMetadata(source, hit);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_hit_test(
    const blink_standalone_renderer_t* renderer,
    float x,
    float y,
    blink_standalone_hit_metadata_t* hit) {
  if (!renderer || !hit) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  const auto& entries = renderer->latest_result.hit_test_entries;
  for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
    if (PointInRect(x, y, it->bounds)) {
      CopyHitMetadata(*it, hit);
      return BLINK_STANDALONE_STATUS_OK;
    }
  }
  return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API const char* blink_standalone_renderer_last_error(
    const blink_standalone_renderer_t* renderer) {
  if (!renderer || renderer->last_error.empty()) {
    return "";
  }
  return renderer->last_error.c_str();
}
