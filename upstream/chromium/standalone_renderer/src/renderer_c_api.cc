// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/renderer_c_api.h"

#include <algorithm>
#include <cctype>
#include <cstring>
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

const char* NoScriptViolationReason(const std::string& html) {
  const std::string lower = LowerAscii(html);
  if (lower.find("<script") != std::string::npos) {
    return "script tag";
  }
  if (HasInlineEventHandlerAttribute(lower)) {
    return "inline event handler";
  }
  if (ContainsJavaScriptScheme(lower)) {
    return "javascript URL";
  }
  if (lower.find("<iframe") != std::string::npos) {
    return "iframe element";
  }
  if (lower.find("<object") != std::string::npos) {
    return "object element";
  }
  if (lower.find("<embed") != std::string::npos) {
    return "embed element";
  }
  return "";
}

bool ViolatesNoScriptProfile(const std::string& html) {
  return NoScriptViolationReason(html)[0] != '\0';
}

const char* AttributeNoScriptViolationReason(const std::string& attribute_name,
                                             const std::string& value) {
  const std::string lower_name = LowerAscii(attribute_name);
  if (lower_name.size() >= 2 && lower_name[0] == 'o' &&
      lower_name[1] == 'n') {
    return "inline event handler";
  }
  return ContainsJavaScriptScheme(LowerAscii(value)) ? "javascript URL" : "";
}

bool MutationViolatesNoScriptProfile(const std::string& attribute_name,
                                     const std::string& value) {
  return AttributeNoScriptViolationReason(attribute_name, value)[0] != '\0';
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

void CopyFormControlState(const html_css_renderer::FormControlEntry& source,
                          blink_standalone_form_control_state_t* state) {
  *state = blink_standalone_form_control_state_t{};
  state->element_id = source.element_id.c_str();
  state->tag_name = source.tag_name.c_str();
  state->value = source.value.c_str();
  state->type = source.type.c_str();
  state->min = source.min.c_str();
  state->max = source.max.c_str();
  state->step = source.step.c_str();
  state->checked = source.checked ? 1 : 0;
  state->focused = source.focused ? 1 : 0;
  state->selection_offsets_present =
      source.selection_offsets_present ? 1 : 0;
  state->selection_start = source.selection_start;
  state->selection_end = source.selection_end;
}

void CopyBackdropFilterRegion(
    const html_css_renderer::BackdropFilterRegion& source,
    blink_standalone_backdrop_filter_region_t* region) {
  *region = blink_standalone_backdrop_filter_region_t{};
  region->bounds = ToCRect(source.bounds);
  region->blur_radius_css_px = source.blur_radius_css_px;
  region->border_radius_top_left = source.border_radius_top_left;
  region->border_radius_top_right = source.border_radius_top_right;
  region->border_radius_bottom_right = source.border_radius_bottom_right;
  region->border_radius_bottom_left = source.border_radius_bottom_left;
  region->opacity = source.opacity;
  region->flags = source.flags;
  region->element_id = source.element_id.c_str();
  const size_t operation_count =
      std::min(source.filter_operations.size(),
               static_cast<size_t>(BLINK_STANDALONE_MAX_BACKDROP_FILTER_OPS));
  region->filter_op_count = static_cast<uint32_t>(operation_count);
  for (size_t i = 0; i < operation_count; ++i) {
    region->filter_ops[i].type = source.filter_operations[i].type;
    region->filter_ops[i].amount = source.filter_operations[i].amount;
  }
}

}  // namespace

namespace {

uint32_t ToCResourceType(html_css_renderer::StandaloneResourceTypeHint type) {
  switch (type) {
    case html_css_renderer::StandaloneResourceTypeHint::kImage:
      return BLINK_STANDALONE_RESOURCE_TYPE_IMAGE;
    case html_css_renderer::StandaloneResourceTypeHint::kStylesheet:
      return BLINK_STANDALONE_RESOURCE_TYPE_STYLESHEET;
    case html_css_renderer::StandaloneResourceTypeHint::kFont:
      return BLINK_STANDALONE_RESOURCE_TYPE_FONT;
    case html_css_renderer::StandaloneResourceTypeHint::kMedia:
      return BLINK_STANDALONE_RESOURCE_TYPE_MEDIA;
    case html_css_renderer::StandaloneResourceTypeHint::kUnknown:
      return BLINK_STANDALONE_RESOURCE_TYPE_UNKNOWN;
  }
  return BLINK_STANDALONE_RESOURCE_TYPE_UNKNOWN;
}

uint32_t ToCResourceInitiator(
    html_css_renderer::StandaloneResourceInitiator initiator) {
  switch (initiator) {
    case html_css_renderer::StandaloneResourceInitiator::kImgElement:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_IMG_ELEMENT;
    case html_css_renderer::StandaloneResourceInitiator::kCssBackgroundImage:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_BACKGROUND_IMAGE;
    case html_css_renderer::StandaloneResourceInitiator::kStylesheetLink:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_STYLESHEET_LINK;
    case html_css_renderer::StandaloneResourceInitiator::kCssImport:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_IMPORT;
    case html_css_renderer::StandaloneResourceInitiator::kFontFace:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_FONT_FACE;
    case html_css_renderer::StandaloneResourceInitiator::kMedia:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_MEDIA;
    case html_css_renderer::StandaloneResourceInitiator::kOther:
      return BLINK_STANDALONE_RESOURCE_INITIATOR_OTHER;
  }
  return BLINK_STANDALONE_RESOURCE_INITIATOR_OTHER;
}

html_css_renderer::StandaloneResourceStatus ToRuntimeResourceStatus(
    uint32_t status) {
  switch (status) {
    case BLINK_STANDALONE_RESOURCE_STATUS_OK:
      return html_css_renderer::StandaloneResourceStatus::kSuccess;
    case BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND:
      return html_css_renderer::StandaloneResourceStatus::kNotFound;
    case BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED:
      return html_css_renderer::StandaloneResourceStatus::kBlockedByPolicy;
    case BLINK_STANDALONE_RESOURCE_STATUS_UNSUPPORTED_SCHEME:
      return html_css_renderer::StandaloneResourceStatus::kUnsupportedScheme;
    case BLINK_STANDALONE_RESOURCE_STATUS_UNSUPPORTED_MIME:
      return html_css_renderer::StandaloneResourceStatus::kUnsupportedMime;
    case BLINK_STANDALONE_RESOURCE_STATUS_ERROR:
    default:
      return html_css_renderer::StandaloneResourceStatus::kError;
  }
}

std::string JoinAcceptedMimeTypes(const std::vector<std::string>& values) {
  std::string joined;
  for (const std::string& value : values) {
    if (!joined.empty()) {
      joined += ",";
    }
    joined += value;
  }
  return joined;
}

class CApiResourceProvider final
    : public html_css_renderer::StandaloneResourceProvider {
 public:
  CApiResourceProvider(blink_standalone_load_resource_callback load,
                       blink_standalone_release_resource_callback release,
                       void* user_data)
      : load_(load), release_(release), user_data_(user_data) {}

  html_css_renderer::StandaloneResourceResult LoadResource(
      const html_css_renderer::StandaloneResourceRequest& request) override {
    html_css_renderer::StandaloneResourceResult result;
    if (!load_) {
      result.status =
          html_css_renderer::StandaloneResourceStatus::kBlockedByPolicy;
      result.error = "C resource provider callback is not configured";
      return result;
    }

    const std::string accepted_mime_types =
        JoinAcceptedMimeTypes(request.accepted_mime_types);
    blink_standalone_resource_request_t c_request = {};
    c_request.url = request.url.c_str();
    c_request.document_url = request.document_url.c_str();
    c_request.base_url = request.base_url.c_str();
    c_request.type_hint = ToCResourceType(request.type_hint);
    c_request.initiator = ToCResourceInitiator(request.initiator);
    c_request.accepted_mime_types = accepted_mime_types.c_str();

    blink_standalone_resource_response_t c_response = {};
    c_response.status = BLINK_STANDALONE_RESOURCE_STATUS_OK;
    const blink_standalone_resource_status_t returned_status =
        load_(user_data_, &c_request, &c_response);
    const uint32_t effective_status =
        returned_status != BLINK_STANDALONE_RESOURCE_STATUS_OK
            ? returned_status
            : c_response.status;

    result.status = ToRuntimeResourceStatus(effective_status);
    result.source_kind = html_css_renderer::StandaloneResourceSourceKind::kMemory;
    if (c_response.mime_type) {
      result.mime_type = c_response.mime_type;
    }
    if (c_response.resolved_url_or_cache_key) {
      result.cache_key = c_response.resolved_url_or_cache_key;
    } else {
      result.cache_key = request.url;
    }
    if (result.status == html_css_renderer::StandaloneResourceStatus::kSuccess &&
        c_response.bytes && c_response.byte_count > 0) {
      result.encoded_bytes.assign(c_response.bytes,
                                  c_response.bytes + c_response.byte_count);
    }
    if (release_) {
      release_(user_data_, &c_response);
    }
    if (result.status != html_css_renderer::StandaloneResourceStatus::kSuccess &&
        result.error.empty()) {
      result.error = "C resource provider returned " +
                     std::string(html_css_renderer::ToString(result.status));
    }
    return result;
  }

 private:
  blink_standalone_load_resource_callback load_ = nullptr;
  blink_standalone_release_resource_callback release_ = nullptr;
  void* user_data_ = nullptr;
};

}  // namespace

struct blink_standalone_renderer {
  std::unique_ptr<html_css_renderer::StandaloneCompositorRuntime> runtime;
  html_css_renderer::Size viewport = {800.0f, 600.0f};
  float device_scale_factor = 1.0f;
  bool no_script_profile = false;
  std::string html;
  std::string resource_root;
  std::string resource_base_path;
  std::shared_ptr<html_css_renderer::StandaloneResourceProvider>
      resource_provider;
  uint32_t resource_provider_flags = 0;
  bool resource_provider_dirty = false;
  html_css_renderer::CompositorFrameResult latest_result;
  std::vector<blink_standalone_rect_t> dirty_rects;
  std::vector<html_css_renderer::MouseInputEvent> pending_mouse_events;
  std::vector<html_css_renderer::KeyboardInputEvent> pending_keyboard_events;
  std::vector<html_css_renderer::DomMutation> pending_dom_mutations;
  std::optional<html_css_renderer::WheelInput> pending_wheel;
  blink_standalone_status_code_t last_error_code =
      BLINK_STANDALONE_STATUS_OK;
  std::string last_error;
};

namespace {

void ClearLastError(blink_standalone_renderer* renderer) {
  if (!renderer) {
    return;
  }
  renderer->last_error_code = BLINK_STANDALONE_STATUS_OK;
  renderer->last_error.clear();
}

blink_standalone_status_code_t SetLastError(
    blink_standalone_renderer* renderer,
    blink_standalone_status_code_t code,
    std::string message) {
  if (renderer) {
    renderer->last_error_code = code;
    renderer->last_error = std::move(message);
  }
  return code;
}

const char* DomMutationTypeName(html_css_renderer::DomMutationType type) {
  switch (type) {
    case html_css_renderer::DomMutationType::kSetTextContent:
      return "set_element_text";
    case html_css_renderer::DomMutationType::kSetAttribute:
      return "set_element_attribute";
    case html_css_renderer::DomMutationType::kRemoveAttribute:
      return "remove_element_attribute";
    case html_css_renderer::DomMutationType::kSetStyleAttribute:
      return "set_element_style";
    case html_css_renderer::DomMutationType::kReplaceStylesheetText:
      return "replace_stylesheet_text";
    case html_css_renderer::DomMutationType::kSetFormControlValue:
      return "set_form_control_value";
    case html_css_renderer::DomMutationType::kSetFormControlChecked:
      return "set_form_control_checked";
    case html_css_renderer::DomMutationType::kFocusElement:
      return "focus_element";
    case html_css_renderer::DomMutationType::kBlurFocusedElement:
      return "blur_focused_element";
    case html_css_renderer::DomMutationType::kSetTextSelection:
      return "set_text_selection";
    case html_css_renderer::DomMutationType::kSetElementInnerHtml:
      return "set_element_inner_html";
    case html_css_renderer::DomMutationType::kSetBodyInnerHtml:
      return "set_body_inner_html";
    case html_css_renderer::DomMutationType::kSetFormControlSelectedValues:
      return "set_form_control_selected_values";
    case html_css_renderer::DomMutationType::kInsertElementHtml:
      return "insert_element_html";
    case html_css_renderer::DomMutationType::kRemoveElement:
      return "remove_element";
  }
  return "dom_mutation";
}

std::string ElementLabel(const char* element_id) {
  return element_id && *element_id ? element_id : "<empty>";
}

bool HasLiveElement(blink_standalone_renderer* renderer,
                    const char* element_id) {
  return renderer && renderer->runtime &&
         renderer->runtime->HasLiveElement(element_id ? element_id : "");
}

blink_standalone_status_code_t RequireLiveElement(
    blink_standalone_renderer* renderer,
    const char* api_name,
    const char* element_id) {
  if (!renderer) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  if (!element_id || !*element_id) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        std::string(api_name) +
                            " failed: element id is required");
  }
  if (!HasLiveElement(renderer, element_id)) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        std::string(api_name) + " failed: element id '" +
                            element_id +
                            "' not found in current live document");
  }
  return BLINK_STANDALONE_STATUS_OK;
}

const html_css_renderer::FormControlEntry* FindFormControlEntry(
    const blink_standalone_renderer* renderer,
    const char* element_id) {
  if (!renderer || !element_id) {
    return nullptr;
  }
  for (const html_css_renderer::FormControlEntry& entry :
       renderer->latest_result.form_control_entries) {
    if (entry.element_id == element_id) {
      return &entry;
    }
  }
  return nullptr;
}

bool IsCheckboxOrRadio(const html_css_renderer::FormControlEntry& entry) {
  return entry.type == "checkbox" || entry.type == "radio";
}

bool IsSelect(const html_css_renderer::FormControlEntry& entry) {
  return LowerAscii(entry.tag_name) == "select";
}

bool IsTextSelectionCapable(const html_css_renderer::FormControlEntry& entry) {
  return entry.selection_offsets_present;
}

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
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED,
                        "failed to initialize standalone compositor runtime");
  }
  return BLINK_STANDALONE_STATUS_OK;
}

void ClearPendingInput(blink_standalone_renderer* renderer) {
  renderer->pending_mouse_events.clear();
  renderer->pending_keyboard_events.clear();
  renderer->pending_dom_mutations.clear();
  renderer->pending_wheel.reset();
}

std::string SerializeSelectedValuesForMutation(const char* const* values,
                                               size_t value_count) {
  std::string serialized;
  for (size_t i = 0; i < value_count; ++i) {
    const char* value = values[i] ? values[i] : "";
    const size_t length = std::strlen(value);
    serialized += std::to_string(length);
    serialized += ':';
    serialized.append(value, length);
  }
  return serialized;
}

const char* InsertPositionName(blink_standalone_insert_position_t position) {
  switch (position) {
    case BLINK_STANDALONE_INSERT_BEFORE_BEGIN:
      return "beforebegin";
    case BLINK_STANDALONE_INSERT_AFTER_BEGIN:
      return "afterbegin";
    case BLINK_STANDALONE_INSERT_BEFORE_END:
      return "beforeend";
    case BLINK_STANDALONE_INSERT_AFTER_END:
      return "afterend";
  }
  return nullptr;
}

blink_standalone_status_code_t QueueDomMutation(
    blink_standalone_renderer_t* renderer,
    html_css_renderer::DomMutationType type,
    const char* element_id,
    const char* name,
    const char* value) {
  if (!renderer || ((type != html_css_renderer::DomMutationType::kBlurFocusedElement) &&
                    (!element_id || !*element_id))) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        std::string(DomMutationTypeName(type)) +
                            " failed: element id is required");
  }
  const std::string mutation_name = name ? name : "";
  const std::string mutation_value = value ? value : "";
  if ((type == html_css_renderer::DomMutationType::kSetAttribute ||
       type == html_css_renderer::DomMutationType::kRemoveAttribute) &&
      mutation_name.empty()) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        std::string(DomMutationTypeName(type)) +
                            " failed: attribute name is required for element id '" +
                            ElementLabel(element_id) + "'");
  }
  if (renderer->no_script_profile) {
    const bool html_fragment_mutation =
        type == html_css_renderer::DomMutationType::kSetElementInnerHtml ||
        type == html_css_renderer::DomMutationType::kSetBodyInnerHtml ||
        type == html_css_renderer::DomMutationType::kInsertElementHtml;
    const char* reason =
        type == html_css_renderer::DomMutationType::kSetAttribute
            ? AttributeNoScriptViolationReason(mutation_name, mutation_value)
            : html_fragment_mutation
                  ? NoScriptViolationReason(mutation_value)
                  : type == html_css_renderer::DomMutationType::kSetStyleAttribute
                        ? AttributeNoScriptViolationReason("style",
                                                           mutation_value)
                        : type ==
                                  html_css_renderer::DomMutationType::
                                      kReplaceStylesheetText
                              ? (ContainsJavaScriptScheme(
                                     LowerAscii(mutation_value))
                                     ? "javascript URL"
                                     : "")
                              : "";
    if (reason[0] != '\0') {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED,
          std::string(DomMutationTypeName(type)) +
              " rejected by no-script profile: " + reason);
    }
  }
  html_css_renderer::DomMutation mutation;
  mutation.type = type;
  mutation.element_id = element_id ? element_id : "";
  mutation.name = mutation_name;
  mutation.value = mutation_value;
  renderer->pending_dom_mutations.push_back(std::move(mutation));
  return BLINK_STANDALONE_STATUS_OK;
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
  ClearLastError(renderer);
  renderer->html = html;
  if (renderer->no_script_profile && ViolatesNoScriptProfile(renderer->html)) {
    renderer->html.clear();
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED,
        std::string("set_document_html rejected by no-script profile: ") +
            NoScriptViolationReason(html));
  }
  renderer->resource_root = resource_root ? resource_root : "";
  renderer->resource_base_path = resource_base_path ? resource_base_path : "";
  renderer->latest_result = html_css_renderer::CompositorFrameResult();
  renderer->dirty_rects.clear();
  ClearPendingInput(renderer);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_resource_provider(
    blink_standalone_renderer_t* renderer,
    blink_standalone_load_resource_callback load,
    blink_standalone_release_resource_callback release,
    void* user_data,
    uint32_t flags) {
  if (!renderer) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  ClearLastError(renderer);
  if (!load) {
    renderer->resource_provider.reset();
    renderer->resource_provider_flags = 0;
    renderer->resource_provider_dirty = true;
    return BLINK_STANDALONE_STATUS_OK;
  }
  renderer->resource_provider =
      std::make_shared<CApiResourceProvider>(load, release, user_data);
  renderer->resource_provider_flags = flags;
  renderer->resource_provider_dirty = true;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_viewport(
    blink_standalone_renderer_t* renderer,
    int width,
    int height,
    float device_scale_factor) {
  if (!renderer || width <= 0 || height <= 0 || device_scale_factor <= 0.0f) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_viewport failed: width, height, and device scale factor must be positive");
  }
  ClearLastError(renderer);
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
  ClearLastError(renderer);
  html_css_renderer::FrameInput input;
  input.viewport = renderer->viewport;
  input.device_scale_factor = renderer->device_scale_factor;
  input.html_override = renderer->html;
  input.resource_root = renderer->resource_root;
  input.resource_base_path = renderer->resource_base_path;
  if (renderer->resource_provider_dirty) {
    input.resource_provider = renderer->resource_provider;
    input.resource_provider_flags = renderer->resource_provider_flags;
    input.resource_provider_changed = true;
  }
  input.timeline_time_seconds = timeline_time_seconds;
  input.request_raw_frame = true;
  input.result_collection = html_css_renderer::FrameResultCollection::kFull;
  input.mouse_events = std::move(renderer->pending_mouse_events);
  input.keyboard_events = std::move(renderer->pending_keyboard_events);
  input.dom_mutations = std::move(renderer->pending_dom_mutations);
  input.wheel = renderer->pending_wheel;
  ClearPendingInput(renderer);
  renderer->latest_result = renderer->runtime->AdvanceFrame(input);
  renderer->resource_provider_dirty = false;
  renderer->dirty_rects.clear();
  for (const html_css_renderer::Rect& rect :
       renderer->latest_result.raw_frame.dirty_rects) {
    renderer->dirty_rects.push_back(ToCRect(rect));
  }
  if (!renderer->latest_result.raw_frame.pixels.empty()) {
    return BLINK_STANDALONE_STATUS_OK;
  }
  return SetLastError(
      renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
      renderer->latest_result.raw_frame_failure.empty()
          ? "advance_frame failed: raw frame output was not produced"
          : "advance_frame failed: " +
                renderer->latest_result.raw_frame_failure);
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
  ClearLastError(renderer);
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
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "mouse_down failed: valid renderer and mouse button are required");
  }
  ClearLastError(renderer);
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
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "mouse_up failed: valid renderer and mouse button are required");
  }
  ClearLastError(renderer);
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
  ClearLastError(renderer);
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
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "key_down failed: valid renderer and key are required");
  }
  ClearLastError(renderer);
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
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "key_up failed: valid renderer and key are required");
  }
  ClearLastError(renderer);
  AppendKeyboardEvent(renderer, html_css_renderer::KeyboardInputEventType::kKeyUp,
                      key, std::string(), modifiers);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_text_input(
    blink_standalone_renderer_t* renderer,
    const char* utf8_text) {
  if (!renderer || !utf8_text) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "text_input failed: renderer and UTF-8 text are required");
  }
  ClearLastError(renderer);
  AppendKeyboardEvent(renderer, html_css_renderer::KeyboardInputEventType::kText,
                      BLINK_STANDALONE_KEY_UNKNOWN, utf8_text, 0);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_text(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* utf8_text) {
  if (!utf8_text) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_element_text failed: UTF-8 text is required");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_element_text", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kSetTextContent,
                          element_id, "", utf8_text);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_inner_html(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* html_fragment) {
  if (!html_fragment) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "set_element_inner_html failed: HTML fragment is required");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_element_inner_html", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kSetElementInnerHtml,
                          element_id, "", html_fragment);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_body_inner_html(
    blink_standalone_renderer_t* renderer,
    const char* html_fragment) {
  if (!html_fragment) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_body_inner_html failed: HTML fragment is required");
  }
  ClearLastError(renderer);
  if (!renderer || !renderer->runtime || !renderer->runtime->HasLiveBody()) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "set_body_inner_html failed: document body not available in current live document");
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kSetBodyInnerHtml,
                          "__body__", "", html_fragment);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_insert_element_html(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    blink_standalone_insert_position_t position,
    const char* html_fragment) {
  if (!html_fragment) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "insert_element_html failed: HTML fragment is required");
  }
  const char* position_name = InsertPositionName(position);
  if (!position_name) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "insert_element_html failed: insert position is invalid");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "insert_element_html", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kInsertElementHtml,
                          element_id, position_name, html_fragment);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_remove_element(
    blink_standalone_renderer_t* renderer,
    const char* element_id) {
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "remove_element", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kRemoveElement,
                          element_id, "", "");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_attribute(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* attribute_name,
    const char* attribute_value) {
  if (!attribute_value) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_element_attribute failed: attribute value is required");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_element_attribute", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kSetAttribute,
                          element_id, attribute_name, attribute_value);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_remove_element_attribute(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* attribute_name) {
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "remove_element_attribute", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kRemoveAttribute,
                          element_id, attribute_name, "");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_style(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* style_attribute_value) {
  if (!style_attribute_value) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_element_style failed: style attribute value is required");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_element_style", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(
      renderer, html_css_renderer::DomMutationType::kSetStyleAttribute,
      element_id, "style", style_attribute_value);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_replace_stylesheet_text(
    blink_standalone_renderer_t* renderer,
    const char* style_element_id,
    const char* css_text) {
  if (!css_text) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "replace_stylesheet_text failed: CSS text is required");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "replace_stylesheet_text", style_element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(
      renderer, html_css_renderer::DomMutationType::kReplaceStylesheetText,
      style_element_id, "", css_text);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_form_control_value(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* value) {
  if (!value) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_form_control_value failed: value is required");
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_form_control_value", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  const html_css_renderer::FormControlEntry* entry =
      FindFormControlEntry(renderer, element_id);
  if (!entry) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        std::string("set_form_control_value failed: element id '") +
                            ElementLabel(element_id) +
                            "' is not a supported form control");
  }
  return QueueDomMutation(
      renderer, html_css_renderer::DomMutationType::kSetFormControlValue,
      element_id, "value", value);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_form_control_checked(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    int checked) {
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_form_control_checked", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  const html_css_renderer::FormControlEntry* entry =
      FindFormControlEntry(renderer, element_id);
  if (!entry || !IsCheckboxOrRadio(*entry)) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        std::string("set_form_control_checked failed: element id '") +
            ElementLabel(element_id) +
            "' is not a checkbox or radio form control");
  }
  return QueueDomMutation(
      renderer, html_css_renderer::DomMutationType::kSetFormControlChecked,
      element_id, "checked", checked ? "1" : "0");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_form_control_selected_values(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* const* values,
    size_t value_count) {
  if (!renderer || !element_id || (!values && value_count != 0)) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_form_control_selected_values failed: renderer, element id, and values are required");
  }
  for (size_t i = 0; i < value_count; ++i) {
    if (!values[i]) {
      return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                          "set_form_control_selected_values failed: selected value entries must be non-null");
    }
  }
  ClearLastError(renderer);
  blink_standalone_status_code_t status = RequireLiveElement(
      renderer, "set_form_control_selected_values", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  const html_css_renderer::FormControlEntry* entry =
      FindFormControlEntry(renderer, element_id);
  if (!entry || !IsSelect(*entry)) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        std::string("set_form_control_selected_values failed: element id '") +
            ElementLabel(element_id) + "' is not a select form control");
  }
  return QueueDomMutation(
      renderer,
      html_css_renderer::DomMutationType::kSetFormControlSelectedValues,
      element_id, "selected_values",
      SerializeSelectedValuesForMutation(values, value_count).c_str());
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_focus_element(
    blink_standalone_renderer_t* renderer,
    const char* element_id) {
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "focus_element", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  return QueueDomMutation(renderer,
                          html_css_renderer::DomMutationType::kFocusElement,
                          element_id, "", "");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_blur_focused_element(
    blink_standalone_renderer_t* renderer) {
  ClearLastError(renderer);
  return QueueDomMutation(
      renderer, html_css_renderer::DomMutationType::kBlurFocusedElement, "",
      "", "");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_text_selection(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    unsigned start,
    unsigned end) {
  ClearLastError(renderer);
  blink_standalone_status_code_t status =
      RequireLiveElement(renderer, "set_text_selection", element_id);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  const html_css_renderer::FormControlEntry* entry =
      FindFormControlEntry(renderer, element_id);
  if (!entry || !IsTextSelectionCapable(*entry)) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        std::string("set_text_selection failed: element id '") +
            ElementLabel(element_id) +
            "' is not a text-editable form control");
  }
  const std::string range =
      std::to_string(start) + ":" + std::to_string(end);
  return QueueDomMutation(
      renderer, html_css_renderer::DomMutationType::kSetTextSelection,
      element_id, "selection", range.c_str());
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_reset_state(
    blink_standalone_renderer_t* renderer) {
  if (!renderer) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  ClearLastError(renderer);
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
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "get_latest_output failed: renderer and output pointer are required");
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
  if (output->pixels) {
    ClearLastError(renderer);
    return BLINK_STANDALONE_STATUS_OK;
  }
  return SetLastError(renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
                      "get_latest_output failed: no raw frame output is available");
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
    return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "get_hit_metadata failed: renderer, hit pointer, and valid index are required");
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
    return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "hit_test failed: renderer and hit pointer are required");
  }
  const auto& entries = renderer->latest_result.hit_test_entries;
  for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
    if (PointInRect(x, y, it->bounds)) {
      CopyHitMetadata(*it, hit);
      return BLINK_STANDALONE_STATUS_OK;
    }
  }
  return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                      BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                      "hit_test failed: no hit metadata entry contains the requested point");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_form_control_state_count(
    const blink_standalone_renderer_t* renderer) {
  return renderer ? renderer->latest_result.form_control_entries.size() : 0;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_form_control_state(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_form_control_state_t* state) {
  if (!renderer || !state ||
      index >= renderer->latest_result.form_control_entries.size()) {
    return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "get_form_control_state failed: renderer, state pointer, and valid index are required");
  }
  CopyFormControlState(renderer->latest_result.form_control_entries[index],
                       state);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_form_control_state_by_id(
    const blink_standalone_renderer_t* renderer,
    const char* element_id,
    blink_standalone_form_control_state_t* state) {
  if (!renderer || !element_id || !state) {
    return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "get_form_control_state_by_id failed: renderer, element id, and state pointer are required");
  }
  for (const html_css_renderer::FormControlEntry& entry :
       renderer->latest_result.form_control_entries) {
    if (entry.element_id == element_id) {
      CopyFormControlState(entry, state);
      return BLINK_STANDALONE_STATUS_OK;
    }
  }
  return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                      BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                      std::string("get_form_control_state_by_id failed: element id '") +
                          element_id + "' is not a known form control");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_form_control_selected_value_count(
    const blink_standalone_renderer_t* renderer,
    const char* element_id) {
  if (!renderer || !element_id) {
    return 0;
  }
  for (const html_css_renderer::FormControlEntry& entry :
       renderer->latest_result.form_control_entries) {
    if (entry.element_id == element_id) {
      return entry.selected_values.size();
    }
  }
  return 0;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_form_control_selected_value(
    const blink_standalone_renderer_t* renderer,
    const char* element_id,
    size_t index,
    const char** value_out) {
  if (!renderer || !element_id || !value_out) {
    return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "get_form_control_selected_value failed: renderer, element id, and value pointer are required");
  }
  for (const html_css_renderer::FormControlEntry& entry :
       renderer->latest_result.form_control_entries) {
    if (entry.element_id != element_id) {
      continue;
    }
    if (index >= entry.selected_values.size()) {
      return SetLastError(
          const_cast<blink_standalone_renderer_t*>(renderer),
          BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "get_form_control_selected_value failed: selected value index is out of range");
    }
    *value_out = entry.selected_values[index].c_str();
    return BLINK_STANDALONE_STATUS_OK;
  }
  return SetLastError(const_cast<blink_standalone_renderer_t*>(renderer),
                      BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                      std::string("get_form_control_selected_value failed: element id '") +
                          element_id + "' is not a known form control");
}

extern "C" BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_backdrop_filter_region_count(
    const blink_standalone_renderer_t* renderer) {
  return renderer ? renderer->latest_result.backdrop_filter_regions.size() : 0;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_backdrop_filter_region(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_backdrop_filter_region_t* out) {
  if (!renderer || !out ||
      index >= renderer->latest_result.backdrop_filter_regions.size()) {
    return SetLastError(
        const_cast<blink_standalone_renderer_t*>(renderer),
        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "get_backdrop_filter_region failed: renderer, output pointer, and valid index are required");
  }
  CopyBackdropFilterRegion(renderer->latest_result.backdrop_filter_regions[index],
                           out);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_last_error_code(
    const blink_standalone_renderer_t* renderer) {
  return renderer ? renderer->last_error_code
                  : BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API const char* blink_standalone_renderer_get_last_error_message(
    const blink_standalone_renderer_t* renderer) {
  if (!renderer || renderer->last_error.empty()) {
    return "";
  }
  return renderer->last_error.c_str();
}

extern "C" BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_clear_last_error(
    blink_standalone_renderer_t* renderer) {
  ClearLastError(renderer);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API const char* blink_standalone_renderer_last_error(
    const blink_standalone_renderer_t* renderer) {
  return blink_standalone_renderer_get_last_error_message(renderer);
}
