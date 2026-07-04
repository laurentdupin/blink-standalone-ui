// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/renderer_c_api.h"

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "base/at_exit.h"
#include "base/base_switches.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/files/file_path.h"
#include "base/message_loop/message_pump_type.h"
#include "base/notimplemented.h"
#include "base/notreached.h"
#include "base/task/single_thread_task_executor.h"
#include "base/task/single_thread_task_runner.h"
#include "base/task/thread_pool/thread_pool_instance.h"
#include "base/trace_event/trace_event_impl.h"
#include "build/build_config.h"
#include "gpu/command_buffer/service/gpu_switches.h"
#include "gpu/vulkan/buildflags.h"
#if BUILDFLAG(ENABLE_VULKAN)
#include "gpu/vulkan/vulkan_device_queue.h"
#include "gpu/vulkan/vulkan_function_pointers.h"
#include "gpu/vulkan/vulkan_image.h"
#include "gpu/vulkan/vulkan_implementation.h"
#include "gpu/vulkan/vulkan_instance.h"
#include "gpu/vulkan/vulkan_surface.h"
#endif
#include "html_css_renderer/compositor_runtime.h"
#include "html_css_renderer/standalone_process.h"
#include "html_css_renderer/standalone_resource_provider.h"
#include "third_party/perfetto/include/perfetto/tracing/tracing.h"

#if BUILDFLAG(IS_WIN)
#include <d3d12.h>
#include <wrl/client.h>
#endif

#if BUILDFLAG(ENABLE_VULKAN)
namespace blink::standalone_renderer_probe {
void StandaloneBlinkLiveFrameBridgeInstallExternalVulkanForTesting(
    void* vulkan_implementation,
    void* vulkan_device_queue);
}  // namespace blink::standalone_renderer_probe
#endif

#if BUILDFLAG(IS_WIN)
namespace blink::standalone_renderer_probe {
void StandaloneBlinkLiveFrameBridgeInstallExternalD3D12AdapterLuidForTesting(
    uint32_t adapter_luid_low,
    int32_t adapter_luid_high,
    void* d3d12_device,
    void* d3d12_command_queue);
}  // namespace blink::standalone_renderer_probe
#endif

namespace {

#if BUILDFLAG(IS_WIN) && defined(BLINK_STANDALONE_HAVE_DAWN_D3D12)
constexpr bool kStandaloneD3D12ExternalTargetsAvailable = true;
#else
constexpr bool kStandaloneD3D12ExternalTargetsAvailable = false;
#endif

#if BUILDFLAG(ENABLE_VULKAN)
base::FilePath StandaloneVulkanLoaderPath() {
#if BUILDFLAG(IS_WIN)
  return base::FilePath(FILE_PATH_LITERAL("vulkan-1.dll"));
#elif BUILDFLAG(IS_LINUX) || BUILDFLAG(IS_CHROMEOS)
  return base::FilePath(FILE_PATH_LITERAL("libvulkan.so.1"));
#else
  return base::FilePath();
#endif
}

std::vector<std::string> CopyStringArray(const char* const* values,
                                         size_t count) {
  std::vector<std::string> strings;
  strings.reserve(count);
  for (size_t i = 0; i < count; ++i) {
    if (values[i] && values[i][0]) {
      strings.emplace_back(values[i]);
    }
  }
  return strings;
}

std::vector<const char*> StringPointers(const std::vector<std::string>& values) {
  std::vector<const char*> pointers;
  pointers.reserve(values.size());
  for (const std::string& value : values) {
    pointers.push_back(value.c_str());
  }
  return pointers;
}

gfx::ExtensionSet MakeExtensionSet(
    const std::vector<std::string>& extensions) {
  gfx::ExtensionSet set;
  for (const std::string& extension : extensions) {
    set.insert(extension);
  }
  return set;
}

class BorrowedVulkanImplementation final : public gpu::VulkanImplementation {
 public:
  BorrowedVulkanImplementation(
      VkInstance instance,
      VkPhysicalDevice physical_device,
      uint32_t api_version,
      std::vector<std::string> enabled_instance_extensions,
      std::vector<std::string> enabled_device_extensions)
      : gpu::VulkanImplementation(/*use_swiftshader=*/false),
        instance_(instance),
        physical_device_(physical_device),
        api_version_(api_version),
        enabled_instance_extensions_(std::move(enabled_instance_extensions)),
        enabled_device_extensions_(std::move(enabled_device_extensions)) {}

  bool InitializeBorrowed() {
    enabled_instance_extension_pointers_ =
        StringPointers(enabled_instance_extensions_);
    return vulkan_instance_.InitializeExternalBorrowed(
        StandaloneVulkanLoaderPath(), instance_, physical_device_, api_version_,
        enabled_instance_extension_pointers_);
  }

  bool InitializeVulkanInstance(bool using_surface = true) override {
    return vulkan_instance_.vk_instance() != VK_NULL_HANDLE;
  }

  gpu::VulkanInstance* GetVulkanInstance() override {
    return &vulkan_instance_;
  }

  std::unique_ptr<gpu::VulkanSurface> CreateViewSurface(
      gfx::AcceleratedWidget window) override {
    return nullptr;
  }

  bool GetPhysicalDevicePresentationSupport(
      VkPhysicalDevice device,
      const std::vector<VkQueueFamilyProperties>& queue_family_properties,
      uint32_t queue_family_index) override {
    return true;
  }

  std::vector<const char*> GetRequiredDeviceExtensions() override {
    return StringPointers(enabled_device_extensions_);
  }

  std::vector<const char*> GetOptionalDeviceExtensions() override {
    return {};
  }

  VkFence CreateVkFenceForGpuFence(VkDevice vk_device) override {
    NOTREACHED();
  }

  std::unique_ptr<gfx::GpuFence> ExportVkFenceToGpuFence(
      VkDevice vk_device,
      VkFence vk_fence) override {
    NOTREACHED();
  }

  VkExternalSemaphoreHandleTypeFlagBits
  GetExternalSemaphoreHandleType() override {
#if BUILDFLAG(IS_WIN)
    return VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_WIN32_BIT;
#else
    return VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT;
#endif
  }

  bool CanImportGpuMemoryBuffer(
      gpu::VulkanDeviceQueue* device_queue,
      gfx::GpuMemoryBufferType memory_buffer_type) override {
    return false;
  }

  std::unique_ptr<gpu::VulkanImage> CreateImageFromGpuMemoryHandle(
      gpu::VulkanDeviceQueue* device_queue,
      gfx::GpuMemoryBufferHandle gmb_handle,
      gfx::Size size,
      VkFormat vk_format,
      const gfx::ColorSpace& color_space) override {
    NOTIMPLEMENTED();
    return nullptr;
  }

  const std::vector<std::string>& enabled_device_extensions() const {
    return enabled_device_extensions_;
  }

 private:
  VkInstance instance_ = VK_NULL_HANDLE;
  VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
  uint32_t api_version_ = 0;
  std::vector<std::string> enabled_instance_extensions_;
  std::vector<std::string> enabled_device_extensions_;
  std::vector<const char*> enabled_instance_extension_pointers_;
  gpu::VulkanInstance vulkan_instance_;
};
#endif

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

void CopyGpuBackdropEffect(const html_css_renderer::BackdropFilterRegion& source,
                           uint32_t id,
                           uint64_t generation,
                           blink_standalone_gpu_backdrop_effect_t* effect) {
  *effect = blink_standalone_gpu_backdrop_effect_t{};
  effect->id = id;
  effect->generation = generation;
  effect->bounds = ToCRect(source.bounds);
  effect->blur_radius_css_px = source.blur_radius_css_px;
  effect->border_radius_top_left = source.border_radius_top_left;
  effect->border_radius_top_right = source.border_radius_top_right;
  effect->border_radius_bottom_right = source.border_radius_bottom_right;
  effect->border_radius_bottom_left = source.border_radius_bottom_left;
  effect->opacity = source.opacity;
  effect->flags = source.flags;
  effect->coordinate_space =
      BLINK_STANDALONE_BACKDROP_COORDINATE_SPACE_LOGICAL_CSS;
  effect->element_id = source.element_id.c_str();
  const size_t operation_count =
      std::min(source.filter_operations.size(),
               static_cast<size_t>(BLINK_STANDALONE_MAX_BACKDROP_FILTER_OPS));
  effect->filter_op_count = static_cast<uint32_t>(operation_count);
  for (size_t i = 0; i < operation_count; ++i) {
    effect->filter_ops[i].type = source.filter_operations[i].type;
    effect->filter_ops[i].amount = source.filter_operations[i].amount;
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
  bool dedicated_thread_shell = false;
  blink_standalone_renderer* dedicated_thread_inner = nullptr;
  void* dedicated_thread_sequence = nullptr;
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
#if BUILDFLAG(ENABLE_VULKAN)
  std::unique_ptr<BorrowedVulkanImplementation>
      external_vulkan_implementation;
  std::unique_ptr<gpu::VulkanDeviceQueue> external_vulkan_device_queue;
  bool external_vulkan_configured = false;
#endif
#if BUILDFLAG(IS_WIN)
  bool external_d3d12_configured = false;
  uint32_t external_d3d12_adapter_luid_low = 0;
  int32_t external_d3d12_adapter_luid_high = 0;
  Microsoft::WRL::ComPtr<ID3D12Device> external_d3d12_device;
  Microsoft::WRL::ComPtr<ID3D12CommandQueue> external_d3d12_command_queue;
#endif
  html_css_renderer::CompositorFrameResult latest_result;
  std::vector<blink_standalone_rect_t> dirty_rects;
  std::vector<html_css_renderer::MouseInputEvent> pending_mouse_events;
  std::vector<html_css_renderer::KeyboardInputEvent> pending_keyboard_events;
  std::vector<html_css_renderer::DomMutation> pending_dom_mutations;
  std::optional<html_css_renderer::WheelInput> pending_wheel;
  bool gpu_prepare_required_after_update = false;
  bool gpu_source_frame_pending = false;
  uint64_t gpu_backdrop_frame_generation = 0;
  struct PreparedGpuSourceFrame {
    bool valid = false;
    uint32_t backend = BLINK_STANDALONE_GPU_BACKEND_NONE;
    uint64_t request_generation = 0;
    uint32_t logical_width = 0;
    uint32_t logical_height = 0;
    uint32_t physical_width = 0;
    uint32_t physical_height = 0;
    float device_scale_factor = 1.0f;
  } prepared_gpu_source_frame;
  struct PendingAsyncGpuFrame {
    bool active = false;
    bool backdrop = false;
    bool mask_required = false;
    bool main_copy_completed = false;
    uint64_t request_id = 0;
    uint64_t request_generation = 0;
    uint32_t backend = BLINK_STANDALONE_GPU_BACKEND_NONE;
    uint32_t mask_encoding = BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_NONE;
    blink_standalone_external_gpu_target_t main_target = {};
    blink_standalone_external_gpu_target_t backdrop_mask_target = {};
    blink_standalone_gpu_async_render_result_t completed_main_result = {};
  } pending_async_gpu_frame;
  blink_standalone_status_code_t last_error_code =
      BLINK_STANDALONE_STATUS_OK;
  std::string last_error;
};

namespace {

struct DedicatedGpuFrameCommand {
  std::mutex mutex;
  std::condition_variable cv;
  blink_standalone_renderer* inner = nullptr;
  blink_standalone_dedicated_thread_gpu_frame_request_t request = {};
  bool started = false;
  bool done = false;
  bool cancel_requested = false;
  blink_standalone_dedicated_thread_gpu_frame_result_t result = {};
  std::string error;
};

class DedicatedRendererSequence {
 public:
  static DedicatedRendererSequence& Get() {
    static DedicatedRendererSequence* sequence = new DedicatedRendererSequence();
    return *sequence;
  }

  blink_standalone_status_code_t CallSync(
      std::function<blink_standalone_status_code_t()> task) {
    if (task) {
      return task();
    }
    return BLINK_STANDALONE_STATUS_OK;
  }

  void PostAsync(std::function<void()> task) {
    if (task) {
      task();
    }
  }

  uint64_t PostGpuFrame(
      blink_standalone_renderer* inner,
      blink_standalone_dedicated_thread_gpu_frame_request_t request) {
    auto command = std::make_shared<DedicatedGpuFrameCommand>();
    uint64_t command_id = 0;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      command_id = next_command_id_++;
      command->inner = inner;
      command->request = request;
      command->result.command_id = command_id;
      command->result.status = BLINK_STANDALONE_STATUS_PENDING;
      command->result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING;
      gpu_commands_[command_id] = command;
    }
    return command_id;
  }

  bool PollGpuFrame(
      uint64_t command_id,
      blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
    if (!command_id) {
      return false;
    }
    std::shared_ptr<DedicatedGpuFrameCommand> command;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      auto it = gpu_commands_.find(command_id);
      if (it == gpu_commands_.end()) {
        return false;
      }
      command = it->second;
    }
    bool run_command = false;
    {
      std::lock_guard<std::mutex> lock(command->mutex);
      if (!command->done && !command->started && !command->cancel_requested) {
        command->started = true;
        run_command = true;
      }
    }
    if (run_command) {
      RunGpuFrameCommand(command->inner, command->request, command, command_id);
    }
    std::lock_guard<std::mutex> lock(command->mutex);
    if (result) {
      *result = command->result;
      result->error_message =
          command->error.empty() ? nullptr : command->error.c_str();
    }
    return true;
  }

  bool CancelGpuFrame(
      uint64_t command_id,
      blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
    if (!command_id) {
      return false;
    }
    std::shared_ptr<DedicatedGpuFrameCommand> command;
    {
      std::lock_guard<std::mutex> lock(mutex_);
      auto it = gpu_commands_.find(command_id);
      if (it == gpu_commands_.end()) {
        return false;
      }
      command = it->second;
    }

    std::unique_lock<std::mutex> lock(command->mutex);
    if (!command->done && !command->started) {
      command->cancel_requested = true;
      command->done = true;
      command->result.command_id = command_id;
      command->result.status = BLINK_STANDALONE_STATUS_OK;
      command->result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_CANCELLED;
      command->result.render_result.status = BLINK_STANDALONE_STATUS_OK;
      command->result.render_result.state =
          BLINK_STANDALONE_GPU_ASYNC_STATE_CANCELLED;
      command->cv.notify_all();
    } else if (!command->done) {
      command->cancel_requested = true;
      command->cv.wait(lock, [&] { return command->done; });
    }
    if (result) {
      *result = command->result;
      result->error_message =
          command->error.empty() ? nullptr : command->error.c_str();
    }
    return true;
  }

 private:
  DedicatedRendererSequence() = default;

  ~DedicatedRendererSequence() = default;

  static void RunGpuFrameCommand(
      blink_standalone_renderer* inner,
      const blink_standalone_dedicated_thread_gpu_frame_request_t& request,
      const std::shared_ptr<DedicatedGpuFrameCommand>& command,
      uint64_t command_id) {
    blink_standalone_dedicated_thread_gpu_frame_result_t result = {};
    result.command_id = command_id;
    result.status = BLINK_STANDALONE_STATUS_OK;
    result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING;
    const auto command_start = std::chrono::steady_clock::now();

    if (DedicatedGpuFrameCancelRequested(command)) {
      CancelDedicatedGpuFrameAndReleaseExternalTargets(inner, &result);
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }

    const uint32_t max_polls =
        request.max_poll_iterations ? request.max_poll_iterations : 240;
    const uint32_t poll_interval_ms =
        request.poll_interval_ms ? request.poll_interval_ms : 1;
    blink_standalone_status_code_t status = BLINK_STANDALONE_STATUS_OK;
    auto tick_source_frame = [&]() {
      const auto source_start = std::chrono::steady_clock::now();
      blink_standalone_status_code_t tick_status =
          blink_standalone_renderer_tick_gpu_source_frame_async(
              inner, &request.source_request, &result.source_result);
      const auto source_end = std::chrono::steady_clock::now();
      result.source_tick_ms +=
          std::chrono::duration<double, std::milli>(source_end - source_start)
              .count();
      return tick_status;
    };
    status = tick_source_frame();
    result.update_result.status = result.source_result.status;
    result.update_result.needs_output = result.source_result.needs_output;
    result.update_result.frame_advanced = result.source_result.frame_advanced;
    result.update_result.frame_skipped_due_to_no_demand =
        result.source_result.frame_skipped_due_to_no_demand;
    result.update_result.full_frame_damage = result.source_result.full_frame_damage;
    result.update_result.damage_rect_count = result.source_result.damage_rect_count;
    if (status == BLINK_STANDALONE_STATUS_OK &&
        result.source_result.state ==
            BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_NO_DEMAND) {
      result.status = BLINK_STANDALONE_STATUS_OK;
      result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED;
      result.render_result.state = BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND;
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    if (DedicatedGpuFrameCancelRequested(command)) {
      CancelDedicatedGpuFrameAndReleaseExternalTargets(inner, &result);
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    while ((status == BLINK_STANDALONE_STATUS_PENDING ||
            result.source_result.state ==
                BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_PENDING) &&
           !DedicatedGpuFrameCancelRequested(command) &&
           result.poll_iterations < max_polls) {
      std::this_thread::sleep_for(std::chrono::milliseconds(poll_interval_ms));
      status = tick_source_frame();
      result.update_result.status = result.source_result.status;
      result.update_result.needs_output = result.source_result.needs_output;
      result.update_result.frame_advanced = result.source_result.frame_advanced;
      result.update_result.frame_skipped_due_to_no_demand =
          result.source_result.frame_skipped_due_to_no_demand;
      result.update_result.full_frame_damage =
          result.source_result.full_frame_damage;
      result.update_result.damage_rect_count =
          result.source_result.damage_rect_count;
      ++result.poll_iterations;
    }
    if (DedicatedGpuFrameCancelRequested(command)) {
      CancelDedicatedGpuFrameAndReleaseExternalTargets(inner, &result);
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    if (status == BLINK_STANDALONE_STATUS_OK &&
        result.source_result.state ==
            BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_NO_DEMAND) {
      result.status = BLINK_STANDALONE_STATUS_OK;
      result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED;
      result.render_result.state = BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND;
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    if (status != BLINK_STANDALONE_STATUS_OK ||
        result.source_result.state !=
            BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_SOURCE_READY) {
      result.status = status == BLINK_STANDALONE_STATUS_PENDING
                          ? BLINK_STANDALONE_STATUS_RENDER_FAILED
                          : status;
      result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED;
      SetDedicatedGpuFrameErrorFromRenderer(inner, &result);
      if (!result.error_message) {
        result.error_message =
            "dedicated GPU frame source work did not become ready";
      }
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }

    auto submit_gpu_frame = [&]() {
      const auto submit_start = std::chrono::steady_clock::now();
      blink_standalone_status_code_t submit_status =
          blink_standalone_renderer_submit_gpu_frame_async(
              inner, &request.render_request, &result.render_result);
      const auto submit_end = std::chrono::steady_clock::now();
      result.submit_ms +=
          std::chrono::duration<double, std::milli>(submit_end - submit_start)
              .count();
      return submit_status;
    };
    status = submit_gpu_frame();
    if (status == BLINK_STANDALONE_STATUS_OK &&
        result.render_result.state ==
            BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND) {
      result.status = BLINK_STANDALONE_STATUS_OK;
      result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED;
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    while (status == BLINK_STANDALONE_STATUS_PENDING &&
           result.render_result.request_id == 0 &&
           !DedicatedGpuFrameCancelRequested(command) &&
           result.poll_iterations < max_polls) {
      std::this_thread::sleep_for(std::chrono::milliseconds(poll_interval_ms));
      status = tick_source_frame();
      result.update_result.status = result.source_result.status;
      result.update_result.needs_output = result.source_result.needs_output;
      result.update_result.frame_advanced =
          result.source_result.frame_advanced;
      result.update_result.frame_skipped_due_to_no_demand =
          result.source_result.frame_skipped_due_to_no_demand;
      result.update_result.full_frame_damage =
          result.source_result.full_frame_damage;
      result.update_result.damage_rect_count =
          result.source_result.damage_rect_count;
      ++result.poll_iterations;
      if (status == BLINK_STANDALONE_STATUS_OK &&
          result.source_result.state ==
              BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_NO_DEMAND) {
        result.status = BLINK_STANDALONE_STATUS_OK;
        result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED;
        result.render_result.state = BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND;
        FinishGpuFrameCommand(command, result, command_start);
        return;
      }
      if (status != BLINK_STANDALONE_STATUS_OK ||
          result.source_result.state !=
              BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_SOURCE_READY) {
        continue;
      }
      status = submit_gpu_frame();
    }
    if (DedicatedGpuFrameCancelRequested(command)) {
      CancelDedicatedGpuFrameAndReleaseExternalTargets(inner, &result);
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    if ((status != BLINK_STANDALONE_STATUS_OK &&
         status != BLINK_STANDALONE_STATUS_PENDING) ||
        result.render_result.request_id == 0) {
      result.status = status;
      result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED;
      SetDedicatedGpuFrameErrorFromRenderer(inner, &result);
      if (!result.error_message) {
        result.error_message =
            "dedicated GPU frame submit did not accept a copy request";
      }
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }

    const uint64_t request_id = result.render_result.request_id;
    while ((result.render_result.state ==
                BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING ||
            result.render_result.state ==
                BLINK_STANDALONE_GPU_ASYNC_STATE_SUBMITTED) &&
           !DedicatedGpuFrameCancelRequested(command) &&
           result.poll_iterations < max_polls) {
      std::this_thread::sleep_for(std::chrono::milliseconds(poll_interval_ms));
      const auto poll_start = std::chrono::steady_clock::now();
      status = blink_standalone_renderer_poll_gpu_frame_async(
          inner, request_id, &result.render_result);
      const auto poll_end = std::chrono::steady_clock::now();
      result.poll_ms +=
          std::chrono::duration<double, std::milli>(poll_end - poll_start)
              .count();
      ++result.poll_iterations;
      if (status != BLINK_STANDALONE_STATUS_OK &&
          status != BLINK_STANDALONE_STATUS_PENDING) {
        break;
      }
    }
    if (result.render_result.state ==
            BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING ||
        result.render_result.state ==
            BLINK_STANDALONE_GPU_ASYNC_STATE_SUBMITTED) {
      blink_standalone_gpu_async_render_result_t cancel_result = {};
      blink_standalone_renderer_cancel_gpu_frame_async(inner, request_id,
                                                       &cancel_result);
      result.render_result = cancel_result;
      result.status = BLINK_STANDALONE_STATUS_OK;
      result.state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_CANCELLED;
      FinishGpuFrameCommand(command, result, command_start);
      return;
    }
    result.status = status;
    result.state =
        status == BLINK_STANDALONE_STATUS_OK &&
                result.render_result.state ==
                    BLINK_STANDALONE_GPU_ASYNC_STATE_COMPLETED
            ? BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_COMPLETED
            : BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED;
    if (result.state == BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED) {
      SetDedicatedGpuFrameErrorFromRenderer(inner, &result);
    }
    FinishGpuFrameCommand(command, result, command_start);
  }

  static void SetDedicatedGpuFrameErrorFromRenderer(
      blink_standalone_renderer* inner,
      blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
    if (!inner || !result) {
      return;
    }
    const char* error = blink_standalone_renderer_last_error(inner);
    if (error && error[0]) {
      result->error_message = error;
    }
  }

  static void CancelDedicatedGpuFrameAndReleaseExternalTargets(
      blink_standalone_renderer* inner,
      blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
    if (!result) {
      return;
    }
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_CANCELLED;
    result->render_result.status = BLINK_STANDALONE_STATUS_OK;
    result->render_result.state = BLINK_STANDALONE_GPU_ASYNC_STATE_CANCELLED;
    if (!inner) {
      return;
    }
    result->render_result.backend = inner->pending_async_gpu_frame.backend;
    result->render_result.request_generation =
        inner->pending_async_gpu_frame.request_generation;
    result->render_result.request_id =
        inner->pending_async_gpu_frame.request_id;
    if (inner->runtime) {
      inner->runtime->ReleaseExternalGpuTargetState();
    }
    inner->pending_async_gpu_frame.active = false;
    inner->gpu_source_frame_pending = false;
    inner->gpu_prepare_required_after_update = true;
    inner->prepared_gpu_source_frame = {};
  }

  static bool DedicatedGpuFrameCancelRequested(
      const std::shared_ptr<DedicatedGpuFrameCommand>& command) {
    std::lock_guard<std::mutex> lock(command->mutex);
    return command->cancel_requested;
  }

  static void FinishGpuFrameCommand(
      const std::shared_ptr<DedicatedGpuFrameCommand>& command,
      blink_standalone_dedicated_thread_gpu_frame_result_t result,
      std::chrono::steady_clock::time_point command_start) {
    const auto command_end = std::chrono::steady_clock::now();
    result.elapsed_ms =
        std::chrono::duration<double, std::milli>(command_end - command_start)
            .count();
    std::lock_guard<std::mutex> lock(command->mutex);
    command->error = result.error_message ? result.error_message : "";
    result.error_message =
        command->error.empty() ? nullptr : command->error.c_str();
    command->result = result;
    command->done = true;
    command->cv.notify_all();
  }

  std::mutex mutex_;
  std::map<uint64_t, std::shared_ptr<DedicatedGpuFrameCommand>> gpu_commands_;
  uint64_t next_command_id_ = 1;
};

bool IsDedicatedThreadShell(const blink_standalone_renderer* renderer) {
  return renderer && renderer->dedicated_thread_shell;
}

DedicatedRendererSequence& DedicatedSequenceFor(
    const blink_standalone_renderer* renderer) {
  if (renderer && renderer->dedicated_thread_sequence) {
    return *static_cast<DedicatedRendererSequence*>(
        renderer->dedicated_thread_sequence);
  }
  return DedicatedRendererSequence::Get();
}

const blink_standalone_renderer* PublicMetadataRendererFor(
    const blink_standalone_renderer* renderer) {
  if (IsDedicatedThreadShell(renderer) && renderer->dedicated_thread_inner) {
    return renderer->dedicated_thread_inner;
  }
  return renderer;
}

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

#if BUILDFLAG(ENABLE_VULKAN)
bool ValidateVulkanExternalTarget(
    const blink_standalone_external_gpu_target_t& target,
    std::string* failure) {
  const auto fail = [&](const char* reason) {
    if (failure) {
      std::ostringstream out;
      out << "render_to_gpu_target failed: invalid Vulkan external target "
          << reason << " common=" << target.common.physical_width << "x"
          << target.common.physical_height << " target="
          << target.vulkan.width << "x" << target.vulkan.height
          << " vk_image=" << target.vulkan.vk_image
          << " vk_memory=" << target.vulkan.vk_device_memory
          << " format=" << target.vulkan.vk_format
          << " allocation_size=" << target.vulkan.allocation_size
          << " allocation_offset=" << target.vulkan.allocation_offset
          << " memory_type_index=" << target.vulkan.memory_type_index
          << " tiling=" << target.vulkan.image_tiling
          << " usage=0x" << std::hex << target.vulkan.image_usage_flags
          << std::dec << " sample_count=" << target.vulkan.sample_count
          << " level_count=" << target.vulkan.level_count
          << " queue_family=" << target.vulkan.queue_family_index;
      *failure = out.str();
    }
    return false;
  };
  if (!target.vulkan.vk_image) {
    return fail("missing vk_image");
  }
  if (!target.vulkan.vk_device_memory) {
    return fail("missing vk_device_memory");
  }
  if (target.common.physical_width == 0 || target.common.physical_height == 0) {
    return fail("missing common physical size");
  }
  if (target.vulkan.width != target.common.physical_width ||
      target.vulkan.height != target.common.physical_height) {
    return fail("size mismatch");
  }
  if (target.vulkan.vk_format != VK_FORMAT_R8G8B8A8_UNORM) {
    return fail("unsupported vk_format");
  }
  if (target.vulkan.allocation_offset != 0) {
    return fail("non-zero allocation_offset is not supported");
  }
  if (target.vulkan.allocation_size == 0) {
    return fail("missing allocation_size");
  }
  if (target.vulkan.sample_count != 0 &&
      target.vulkan.sample_count != VK_SAMPLE_COUNT_1_BIT) {
    return fail("unsupported sample_count");
  }
  if (target.vulkan.level_count != 0 && target.vulkan.level_count != 1) {
    return fail("unsupported level_count");
  }
  constexpr uint32_t kRequiredUsage =
      VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT |
      VK_IMAGE_USAGE_TRANSFER_DST_BIT;
  if ((target.vulkan.image_usage_flags & kRequiredUsage) != kRequiredUsage) {
    return fail("missing required image_usage_flags");
  }
  return true;
}
#endif

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
#if BUILDFLAG(ENABLE_VULKAN)
  if (renderer->external_vulkan_configured &&
      renderer->external_vulkan_implementation &&
      renderer->external_vulkan_device_queue) {
    blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeInstallExternalVulkanForTesting(
        renderer->external_vulkan_implementation.get(),
        renderer->external_vulkan_device_queue.release());
  }
#endif
#if BUILDFLAG(IS_WIN)
  if (renderer->external_d3d12_configured) {
    blink::standalone_renderer_probe::
        StandaloneBlinkLiveFrameBridgeInstallExternalD3D12AdapterLuidForTesting(
            renderer->external_d3d12_adapter_luid_low,
            renderer->external_d3d12_adapter_luid_high,
            renderer->external_d3d12_device.Get(),
            renderer->external_d3d12_command_queue.Get());
  }
#endif
  html_css_renderer::CompositorRuntimeCreateInfo create_info;
  create_info.renderer.viewport = renderer->viewport;
  create_info.renderer.device_scale_factor = renderer->device_scale_factor;
  create_info.renderer.no_script_profile = renderer->no_script_profile;
  create_info.renderer.transparent_background = renderer->no_script_profile;
  create_info.no_script_profile = renderer->no_script_profile;
  create_info.transparent_background = renderer->no_script_profile;
  if (const char* trace_stages = std::getenv("HTML_CSS_RENDERER_TRACE_STAGES")) {
    create_info.trace_stages = trace_stages[0] && trace_stages[0] != '0';
  }
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

void InvalidatePreparedGpuSourceFrame(blink_standalone_renderer* renderer) {
  if (renderer) {
    renderer->prepared_gpu_source_frame = {};
  }
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
  InvalidatePreparedGpuSourceFrame(renderer);
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
  InvalidatePreparedGpuSourceFrame(renderer);
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
  InvalidatePreparedGpuSourceFrame(renderer);
}

bool StartsWith(const std::string& value, const char* prefix) {
  return value.rfind(prefix, 0) == 0;
}

bool HasPendingFrameInput(const blink_standalone_renderer* renderer) {
  return renderer->resource_provider_dirty ||
         !renderer->pending_mouse_events.empty() ||
         !renderer->pending_keyboard_events.empty() ||
         !renderer->pending_dom_mutations.empty() ||
         renderer->pending_wheel.has_value();
}

bool FrameResultHasGpuPreparePending(
    const html_css_renderer::CompositorFrameResult& result) {
  if (result.gpu_frame_failure == "GPU external target source frame is pending") {
    return true;
  }
  return std::find(result.diagnostics.begin(), result.diagnostics.end(),
                   "GPU external target source frame is pending") !=
         result.diagnostics.end();
}

bool FrameResultHasPublicFrameMetadata(
    const html_css_renderer::CompositorFrameResult& result) {
  return result.hit_test_metadata_collected &&
         result.backdrop_filter_metadata_collected;
}

uint32_t LatestPhysicalWidth(const blink_standalone_renderer* renderer) {
  if (renderer->latest_result.viz_display_output_size.width > 0) {
    return static_cast<uint32_t>(
        renderer->latest_result.viz_display_output_size.width);
  }
  return static_cast<uint32_t>(
      std::max(0.0f, renderer->viewport.width * renderer->device_scale_factor));
}

uint32_t LatestPhysicalHeight(const blink_standalone_renderer* renderer) {
  if (renderer->latest_result.viz_display_output_size.height > 0) {
    return static_cast<uint32_t>(
        renderer->latest_result.viz_display_output_size.height);
  }
  return static_cast<uint32_t>(
      std::max(0.0f,
               renderer->viewport.height * renderer->device_scale_factor));
}

void PopulateGpuFrameState(const blink_standalone_renderer* renderer,
                           blink_standalone_gpu_render_result_t* result) {
  result->needs_output = renderer->latest_result.needs_output ? 1 : 0;
  result->frame_advanced =
      renderer->latest_result.frame_advanced ? 1 : 0;
  result->frame_skipped_due_to_no_demand =
      renderer->latest_result.frame_skipped_due_to_no_demand ? 1 : 0;
  result->full_frame_damage = result->needs_output ? 1 : 0;
  result->dirty_rect_count = 0;
  result->physical_width = LatestPhysicalWidth(renderer);
  result->physical_height = LatestPhysicalHeight(renderer);
  result->frame_generation = renderer->gpu_backdrop_frame_generation;
}

bool CanSkipCleanGpuRender(
    const blink_standalone_renderer* renderer,
    const blink_standalone_external_gpu_target_t* target) {
  if ((target->common.flags & BLINK_STANDALONE_GPU_TARGET_SKIP_IF_CLEAN) == 0) {
    return false;
  }
  if (HasPendingFrameInput(renderer) || renderer->gpu_prepare_required_after_update ||
      renderer->gpu_source_frame_pending || renderer->latest_result.needs_output) {
    return false;
  }
  if (renderer->latest_result.viz_display_output_size.width <= 0 ||
      renderer->latest_result.viz_display_output_size.height <= 0) {
    return false;
  }
  const uint32_t target_width =
      target->common.physical_width ? target->common.physical_width
                                    : LatestPhysicalWidth(renderer);
  const uint32_t target_height =
      target->common.physical_height ? target->common.physical_height
                                     : LatestPhysicalHeight(renderer);
  return LatestPhysicalWidth(renderer) == target_width &&
         LatestPhysicalHeight(renderer) == target_height;
}

uint32_t TargetPhysicalWidth(
    const blink_standalone_external_gpu_target_t* target) {
  if (!target) {
    return 0;
  }
  if (target->common.backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
      target->d3d12.width) {
    return target->d3d12.width;
  }
  if (target->common.backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      target->vulkan.width) {
    return target->vulkan.width;
  }
  return target->common.physical_width;
}

uint32_t TargetPhysicalHeight(
    const blink_standalone_external_gpu_target_t* target) {
  if (!target) {
    return 0;
  }
  if (target->common.backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
      target->d3d12.height) {
    return target->d3d12.height;
  }
  if (target->common.backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      target->vulkan.height) {
    return target->vulkan.height;
  }
  return target->common.physical_height;
}

uint32_t TargetLogicalWidth(
    const blink_standalone_external_gpu_target_t* target) {
  if (!target) {
    return 0;
  }
  return target->common.logical_width;
}

uint32_t TargetLogicalHeight(
    const blink_standalone_external_gpu_target_t* target) {
  if (!target) {
    return 0;
  }
  return target->common.logical_height;
}

bool LatestGpuOutputSizeMatchesTarget(
    const blink_standalone_renderer* renderer,
    const blink_standalone_external_gpu_target_t* target) {
  const uint32_t target_width = TargetPhysicalWidth(target);
  const uint32_t target_height = TargetPhysicalHeight(target);
  if (target_width == 0 || target_height == 0) {
    return true;
  }
  const int submitted_width =
      renderer->latest_result.compositor_output_size.width;
  const int submitted_height =
      renderer->latest_result.compositor_output_size.height;
  if (submitted_width > 0 && submitted_height > 0 &&
      (submitted_width != static_cast<int>(target_width) ||
       submitted_height != static_cast<int>(target_height))) {
    return false;
  }
  const int latest_width =
      renderer->latest_result.viz_display_output_size.width;
  const int latest_height =
      renderer->latest_result.viz_display_output_size.height;
  if (latest_width <= 0 || latest_height <= 0) {
    return true;
  }
  return latest_width == static_cast<int>(target_width) &&
         latest_height == static_cast<int>(target_height);
}

bool PreparedGpuSourceMatchesTarget(
    const blink_standalone_renderer* renderer,
    uint32_t backend,
    const blink_standalone_external_gpu_target_t* target,
    uint64_t request_generation) {
  if (!renderer || !target || !renderer->prepared_gpu_source_frame.valid) {
    return false;
  }
  const auto& prepared = renderer->prepared_gpu_source_frame;
  if (prepared.backend != backend ||
      prepared.request_generation != request_generation) {
    return false;
  }
  const uint32_t logical_width = TargetLogicalWidth(target);
  const uint32_t logical_height = TargetLogicalHeight(target);
  if (logical_width && prepared.logical_width != logical_width) {
    return false;
  }
  if (logical_height && prepared.logical_height != logical_height) {
    return false;
  }
  if (prepared.physical_width != TargetPhysicalWidth(target) ||
      prepared.physical_height != TargetPhysicalHeight(target)) {
    return false;
  }
  const float target_dsf = target->common.device_scale_factor > 0.0f
                               ? target->common.device_scale_factor
                               : renderer->device_scale_factor;
  return std::abs(prepared.device_scale_factor - target_dsf) <= 0.001f;
}

bool IsRecoverableGpuCopyOutputNotReady(const std::string& failure) {
  return failure.find("Viz CopyOutput did not produce output") !=
             std::string::npos ||
         failure.find("Viz BlitRequest CopyOutput did not complete") !=
             std::string::npos;
}

uint32_t ToPublicAsyncState(
    html_css_renderer::ExternalGpuTargetCopyStatus status) {
  switch (status) {
    case html_css_renderer::ExternalGpuTargetCopyStatus::kNone:
      return BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kPending:
      return BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kCompleted:
      return BLINK_STANDALONE_GPU_ASYNC_STATE_COMPLETED;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kFailed:
      return BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kCancelled:
      return BLINK_STANDALONE_GPU_ASYNC_STATE_CANCELLED;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kStale:
      return BLINK_STANDALONE_GPU_ASYNC_STATE_STALE;
  }
  return BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
}

blink_standalone_status_code_t ToPublicAsyncStatus(
    html_css_renderer::ExternalGpuTargetCopyStatus status) {
  switch (status) {
    case html_css_renderer::ExternalGpuTargetCopyStatus::kNone:
    case html_css_renderer::ExternalGpuTargetCopyStatus::kCompleted:
    case html_css_renderer::ExternalGpuTargetCopyStatus::kCancelled:
    case html_css_renderer::ExternalGpuTargetCopyStatus::kStale:
      return BLINK_STANDALONE_STATUS_OK;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kPending:
      return BLINK_STANDALONE_STATUS_PENDING;
    case html_css_renderer::ExternalGpuTargetCopyStatus::kFailed:
      return BLINK_STANDALONE_STATUS_RENDER_FAILED;
  }
  return BLINK_STANDALONE_STATUS_RENDER_FAILED;
}

void PopulateAsyncGpuFrameState(
    const blink_standalone_renderer* renderer,
    const html_css_renderer::ExternalGpuTargetCopyResult& copy_result,
    blink_standalone_gpu_async_render_result_t* result) {
  result->status = ToPublicAsyncStatus(copy_result.status);
  result->state = ToPublicAsyncState(copy_result.status);
  result->request_id = copy_result.request_id;
  result->physical_width = static_cast<uint32_t>(std::max(0, copy_result.width));
  result->physical_height =
      static_cast<uint32_t>(std::max(0, copy_result.height));
  result->needs_output = renderer->latest_result.needs_output ? 1 : 0;
  result->frame_advanced =
      renderer->latest_result.frame_advanced ? 1 : 0;
  result->frame_skipped_due_to_no_demand =
      renderer->latest_result.frame_skipped_due_to_no_demand ? 1 : 0;
  result->full_frame_damage = result->needs_output ? 1 : 0;
  result->damage_rect_count = 0;
  result->frame_generation = renderer->gpu_backdrop_frame_generation;
}

void PopulateGpuSourceFrameTickResult(
    const blink_standalone_renderer* renderer,
    const blink_standalone_gpu_source_frame_tick_request_t* request,
    blink_standalone_gpu_source_frame_tick_result_t* result) {
  result->backend = request->backend;
  result->request_generation = request->request_generation;
  result->source_frame_generation =
      renderer->prepared_gpu_source_frame.valid
          ? renderer->prepared_gpu_source_frame.request_generation
          : 0;
  result->needs_output =
      (renderer->latest_result.needs_output ||
       renderer->gpu_prepare_required_after_update ||
       renderer->gpu_source_frame_pending)
          ? 1
          : 0;
  result->frame_advanced =
      renderer->latest_result.frame_advanced ? 1 : 0;
  result->frame_skipped_due_to_no_demand =
      renderer->latest_result.frame_skipped_due_to_no_demand ? 1 : 0;
  result->full_frame_damage = result->needs_output ? 1 : 0;
  result->damage_rect_count = 0;
  result->logical_width =
      request->logical_width
          ? request->logical_width
          : static_cast<uint32_t>(std::max(0.0f, renderer->viewport.width));
  result->logical_height =
      request->logical_height
          ? request->logical_height
          : static_cast<uint32_t>(std::max(0.0f, renderer->viewport.height));
  result->physical_width =
      request->physical_width ? request->physical_width
                              : LatestPhysicalWidth(renderer);
  result->physical_height =
      request->physical_height ? request->physical_height
                               : LatestPhysicalHeight(renderer);
  result->device_scale_factor =
      request->device_scale_factor > 0.0f ? request->device_scale_factor
                                          : renderer->device_scale_factor;
  result->max_work_budget_ms = request->max_work_budget_ms;
}

bool AsyncRequestIsTerminal(uint32_t state) {
  return state == BLINK_STANDALONE_GPU_ASYNC_STATE_COMPLETED ||
         state == BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED ||
         state == BLINK_STANDALONE_GPU_ASYNC_STATE_CANCELLED ||
         state == BLINK_STANDALONE_GPU_ASYNC_STATE_STALE ||
         state == BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND;
}

void RefreshPublicFrameMetadata(blink_standalone_renderer* renderer) {
  html_css_renderer::FrameInput input;
  input.viewport = renderer->viewport;
  input.device_scale_factor = renderer->device_scale_factor;
  input.html_override = renderer->html;
  input.resource_root = renderer->resource_root;
  input.resource_base_path = renderer->resource_base_path;
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  input.force_metadata_collection = true;
  input.request_backdrop_filter_regions = true;
  renderer->latest_result = renderer->runtime->AdvanceFrame(input);
}

blink_standalone_status_code_t AdvanceGpuFrameForBackend(
    blink_standalone_renderer* renderer,
    uint32_t backend,
    bool require_source_gpu_frame) {
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
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  input.request_backdrop_filter_regions = true;
  input.mouse_events = std::move(renderer->pending_mouse_events);
  input.keyboard_events = std::move(renderer->pending_keyboard_events);
  input.dom_mutations = std::move(renderer->pending_dom_mutations);
  input.wheel = renderer->pending_wheel;
  ClearPendingInput(renderer);
  if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
    if (require_source_gpu_frame) {
      input.request_vulkan_gpu_frame = true;
    } else {
      input.prepare_vulkan_gpu_frame = true;
    }
  } else if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
    if (require_source_gpu_frame) {
      input.request_d3d12_gpu_frame = true;
    } else {
      input.prepare_d3d12_gpu_frame = true;
    }
  } else {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "render_to_gpu_target failed: unsupported GPU backend");
  }
  renderer->latest_result = renderer->runtime->AdvanceFrame(input);
  renderer->resource_provider_dirty = false;
  if (require_source_gpu_frame &&
      (!renderer->latest_result.gpu_frame.shared_image_available ||
       renderer->latest_result.gpu_frame.is_software)) {
    if (IsRecoverableGpuCopyOutputNotReady(
            renderer->latest_result.gpu_frame_failure)) {
      renderer->gpu_source_frame_pending = true;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_PENDING,
          "render_to_gpu_target pending: Viz CopyOutput did not produce output");
    }
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
        renderer->latest_result.gpu_frame_failure.empty()
            ? "render_to_gpu_target failed: GPU frame output was not produced"
            : "render_to_gpu_target failed: " +
                  renderer->latest_result.gpu_frame_failure);
  }
  return BLINK_STANDALONE_STATUS_OK;
}

}  // namespace

blink_standalone_status_code_t CreateRendererOnCurrentThread(
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

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_create(
    const blink_standalone_renderer_config_t* config,
    blink_standalone_renderer_t** renderer_out) {
  return CreateRendererOnCurrentThread(config, renderer_out);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_create_dedicated_thread(
    const blink_standalone_renderer_config_t* config,
    blink_standalone_renderer_t** renderer_out) {
  if (!renderer_out) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  *renderer_out = nullptr;
  auto shell = std::make_unique<blink_standalone_renderer>();
  shell->dedicated_thread_shell = true;
  DedicatedRendererSequence& sequence = DedicatedRendererSequence::Get();
  shell->dedicated_thread_sequence = &sequence;
  blink_standalone_renderer_t* inner = nullptr;
  blink_standalone_status_code_t status =
      sequence.CallSync([&]() {
        return CreateRendererOnCurrentThread(config, &inner);
      });
  shell->dedicated_thread_inner = inner;
  if (status != BLINK_STANDALONE_STATUS_OK || !inner) {
    *renderer_out = shell.release();
    return status;
  }
  *renderer_out = shell.release();
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_destroy(
    blink_standalone_renderer_t* renderer) {
  if (!renderer) {
    return;
  }
  if (IsDedicatedThreadShell(renderer)) {
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    renderer->dedicated_thread_inner = nullptr;
    if (inner) {
      DedicatedSequenceFor(renderer).CallSync([inner]() {
        blink_standalone_renderer_destroy(inner);
        return BLINK_STANDALONE_STATUS_OK;
      });
    }
    delete renderer;
    return;
  }
  delete renderer;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_document_html(
    blink_standalone_renderer_t* renderer,
    const char* html,
    const char* resource_root,
    const char* resource_base_path) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!html) {
      return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    }
    std::string html_copy = html;
    std::string resource_root_copy = resource_root ? resource_root : "";
    std::string resource_base_path_copy =
        resource_base_path ? resource_base_path : "";
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, html_copy = std::move(html_copy),
         resource_root_copy = std::move(resource_root_copy),
         resource_base_path_copy = std::move(resource_base_path_copy)]() {
          return blink_standalone_renderer_set_document_html(
              inner, html_copy.c_str(), resource_root_copy.c_str(),
              resource_base_path_copy.c_str());
        });
  }
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
  renderer->gpu_backdrop_frame_generation = 0;
  renderer->pending_async_gpu_frame = {};
  InvalidatePreparedGpuSourceFrame(renderer);
  renderer->dirty_rects.clear();
  renderer->gpu_prepare_required_after_update = false;
  renderer->gpu_source_frame_pending = false;
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
    InvalidatePreparedGpuSourceFrame(renderer);
    return BLINK_STANDALONE_STATUS_OK;
  }
  renderer->resource_provider =
      std::make_shared<CApiResourceProvider>(load, release, user_data);
  renderer->resource_provider_flags = flags;
  renderer->resource_provider_dirty = true;
  InvalidatePreparedGpuSourceFrame(renderer);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_viewport(
    blink_standalone_renderer_t* renderer,
    int width,
    int height,
    float device_scale_factor) {
  if (IsDedicatedThreadShell(renderer)) {
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, width, height, device_scale_factor]() {
          return blink_standalone_renderer_set_viewport(
              inner, width, height, device_scale_factor);
        });
  }
  if (!renderer || width <= 0 || height <= 0 || device_scale_factor <= 0.0f) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "set_viewport failed: width, height, and device scale factor must be positive");
  }
  ClearLastError(renderer);
  const float old_width = renderer->viewport.width;
  const float old_height = renderer->viewport.height;
  const float old_device_scale_factor = renderer->device_scale_factor;
  renderer->viewport = {static_cast<float>(width), static_cast<float>(height)};
  renderer->device_scale_factor = device_scale_factor;
  const bool viewport_changed =
      old_width != renderer->viewport.width ||
      old_height != renderer->viewport.height ||
      old_device_scale_factor != renderer->device_scale_factor;
  if (viewport_changed) {
    renderer->pending_async_gpu_frame = {};
    InvalidatePreparedGpuSourceFrame(renderer);
    renderer->gpu_prepare_required_after_update = true;
    renderer->gpu_source_frame_pending = false;
    renderer->latest_result.viz_display_output_size = {};
    renderer->latest_result.gpu_frame = {};
    renderer->latest_result.gpu_frame_failure.clear();
    renderer->dirty_rects.clear();
    if (renderer->runtime) {
      renderer->runtime->ReleaseExternalGpuTargetState();
    }
  }
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
  InvalidatePreparedGpuSourceFrame(renderer);
  if (renderer->latest_result.raw_frame.pixels.empty()) {
    html_css_renderer::FrameInput retry_input;
    retry_input.viewport = renderer->viewport;
    retry_input.device_scale_factor = renderer->device_scale_factor;
    retry_input.html_override = renderer->html;
    retry_input.resource_root = renderer->resource_root;
    retry_input.resource_base_path = renderer->resource_base_path;
    retry_input.timeline_time_seconds = timeline_time_seconds;
    retry_input.request_raw_frame = true;
    retry_input.result_collection = html_css_renderer::FrameResultCollection::kFull;
    renderer->latest_result = renderer->runtime->AdvanceFrame(retry_input);
  }
  renderer->gpu_prepare_required_after_update = false;
  renderer->gpu_source_frame_pending = false;
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

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_update(
    blink_standalone_renderer_t* renderer,
    double timeline_time_seconds,
    blink_standalone_update_result_t* result) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!result) {
      return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    }
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, timeline_time_seconds, result]() {
          return blink_standalone_renderer_update(inner, timeline_time_seconds,
                                                  result);
        });
  }
  if (!renderer || !renderer->runtime || !result) {
    return BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
  }
  *result = blink_standalone_update_result_t{};
  ClearLastError(renderer);
  const bool had_gpu_source_frame_pending = renderer->gpu_source_frame_pending;
  html_css_renderer::CompositorFrameResult previous_result;
  if (had_gpu_source_frame_pending) {
    previous_result = renderer->latest_result;
  }
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
  input.result_collection = html_css_renderer::FrameResultCollection::kMinimal;
  input.request_backdrop_filter_regions = true;
  input.mouse_events = std::move(renderer->pending_mouse_events);
  input.keyboard_events = std::move(renderer->pending_keyboard_events);
  input.dom_mutations = std::move(renderer->pending_dom_mutations);
  input.wheel = renderer->pending_wheel;
  ClearPendingInput(renderer);
  renderer->latest_result = renderer->runtime->AdvanceFrame(input);
  renderer->resource_provider_dirty = false;
  renderer->gpu_source_frame_pending =
      had_gpu_source_frame_pending && !renderer->latest_result.needs_output &&
      renderer->latest_result.frame_skipped_due_to_no_demand;
  const bool update_skipped_for_pending_retry =
      renderer->gpu_source_frame_pending;
  const bool update_frame_advanced = renderer->latest_result.frame_advanced;
  const bool update_frame_skipped =
      renderer->latest_result.frame_skipped_due_to_no_demand;
  const bool update_needs_begin_frame =
      renderer->latest_result.needs_begin_frame;
  if (update_skipped_for_pending_retry) {
    renderer->latest_result = std::move(previous_result);
  }
  renderer->gpu_prepare_required_after_update =
      renderer->latest_result.needs_output &&
      !update_skipped_for_pending_retry;
  renderer->dirty_rects.clear();

  result->status = BLINK_STANDALONE_STATUS_OK;
  result->frame_advanced = update_frame_advanced ? 1 : 0;
  result->frame_skipped_due_to_no_demand =
      update_frame_skipped ? 1 : 0;
  result->needs_output =
      (renderer->latest_result.needs_output ||
       renderer->gpu_source_frame_pending)
          ? 1
          : 0;
  result->needs_begin_frame = update_needs_begin_frame ? 1 : 0;
  result->full_frame_damage = result->needs_output ? 1 : 0;
  result->damage_rect_count = 0;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API uint32_t blink_standalone_renderer_gpu_backend_capabilities(
    const blink_standalone_renderer_t* renderer,
    uint32_t backend) {
  if (IsDedicatedThreadShell(renderer)) {
    uint32_t capabilities = 0;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    DedicatedSequenceFor(renderer).CallSync([inner, backend, &capabilities]() {
      capabilities =
          blink_standalone_renderer_gpu_backend_capabilities(inner, backend);
      return BLINK_STANDALONE_STATUS_OK;
    });
    return capabilities;
  }
  if (!renderer) {
    return 0;
  }
  switch (backend) {
    case BLINK_STANDALONE_GPU_BACKEND_CPU_RAW:
      return BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE;
    case BLINK_STANDALONE_GPU_BACKEND_VULKAN:
      return BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE |
             BLINK_STANDALONE_GPU_CAPABILITY_INTERNAL_TEST_STANDIN
#if BUILDFLAG(ENABLE_VULKAN)
             | (renderer->external_vulkan_configured
                    ? BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET
                    : 0)
#endif
          ;
    case BLINK_STANDALONE_GPU_BACKEND_D3D12:
      if (!kStandaloneD3D12ExternalTargetsAvailable) {
        return 0;
      }
      return BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE |
             BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET |
             BLINK_STANDALONE_GPU_CAPABILITY_INTERNAL_TEST_STANDIN;
    case BLINK_STANDALONE_GPU_BACKEND_NONE:
    default:
      return 0;
  }
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_configure_vulkan_external_device(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_vulkan_external_device_t* device) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!device) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "configure_vulkan_external_device failed: renderer and device are required");
    }
    blink_standalone_vulkan_external_device_t device_copy = *device;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync([inner, device_copy]() {
      return blink_standalone_renderer_configure_vulkan_external_device(
          inner, &device_copy);
    });
  }
  if (!renderer || !device) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "configure_vulkan_external_device failed: renderer and device are required");
  }
  if (renderer->runtime && !renderer->html.empty()) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "configure_vulkan_external_device failed: Vulkan device must be configured before first frame/runtime initialization");
  }
  renderer->runtime.reset();
  renderer->latest_result = html_css_renderer::CompositorFrameResult();
#if BUILDFLAG(ENABLE_VULKAN)
  if (!device->vk_instance ||
      !device->vk_physical_device || !device->vk_device ||
      !device->vk_queue || device->queue_family_index == UINT32_MAX) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "configure_vulkan_external_device failed: native Vulkan handles are required");
  }
  const bool invalid_instance_extensions =
      device->enabled_instance_extension_count > 0 &&
      !device->enabled_instance_extensions;
  const bool invalid_device_extensions =
      device->enabled_device_extension_count > 0 &&
      !device->enabled_device_extensions;
  if (invalid_instance_extensions || invalid_device_extensions) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "configure_vulkan_external_device failed: extension arrays are required when extension counts are non-zero");
  }

  auto implementation = std::make_unique<BorrowedVulkanImplementation>(
      static_cast<VkInstance>(device->vk_instance),
      static_cast<VkPhysicalDevice>(device->vk_physical_device),
      device->api_version,
      CopyStringArray(device->enabled_instance_extensions,
                      device->enabled_instance_extension_count),
      CopyStringArray(device->enabled_device_extensions,
                      device->enabled_device_extension_count));
  if (!implementation->InitializeBorrowed()) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED,
        "configure_vulkan_external_device failed: could not wrap borrowed Vulkan instance or bind instance functions");
  }
  const gfx::ExtensionSet enabled_device_extensions =
      MakeExtensionSet(implementation->enabled_device_extensions());
  if (!gpu::GetVulkanFunctionPointers()->BindDeviceFunctionPointers(
          static_cast<VkDevice>(device->vk_device),
          device->api_version ? device->api_version
                              : gpu::kVulkanRequiredApiVersion,
          enabled_device_extensions)) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED,
        "configure_vulkan_external_device failed: could not bind borrowed Vulkan device functions");
  }

  VkPhysicalDeviceFeatures2 features = {
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2};
  vkGetPhysicalDeviceFeatures2(
      static_cast<VkPhysicalDevice>(device->vk_physical_device), &features);
  VkPhysicalDeviceProperties properties = {};
  vkGetPhysicalDeviceProperties(
      static_cast<VkPhysicalDevice>(device->vk_physical_device), &properties);
  VkPhysicalDeviceDriverProperties driver_properties = {
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_DRIVER_PROPERTIES};
  VkPhysicalDeviceProperties2 properties2 = {
      VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2};
  properties2.pNext = &driver_properties;
  vkGetPhysicalDeviceProperties2(
      static_cast<VkPhysicalDevice>(device->vk_physical_device), &properties2);

  auto queue = std::make_unique<gpu::VulkanDeviceQueue>(
      static_cast<VkInstance>(device->vk_instance));
  if (!queue->InitializeForCompositorGpuThread(
          static_cast<VkPhysicalDevice>(device->vk_physical_device),
          static_cast<VkDevice>(device->vk_device),
          static_cast<VkQueue>(device->vk_queue),
          /*vk_queue_lock_context=*/nullptr, device->queue_family_index,
          enabled_device_extensions, features, properties, driver_properties,
          /*vma_allocator=*/VK_NULL_HANDLE,
          /*register_memory_dump_provider=*/false)) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED,
        "configure_vulkan_external_device failed: could not wrap borrowed Vulkan device queue");
  }

  renderer->external_vulkan_implementation = std::move(implementation);
  renderer->external_vulkan_device_queue = std::move(queue);
  renderer->external_vulkan_configured = true;
  return InitializeRuntime(renderer);
#else
  return SetLastError(renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
                      "configure_vulkan_external_device failed: Vulkan is not enabled");
#endif
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_configure_d3d12_external_device(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_d3d12_external_device_t* device) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!device) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "configure_d3d12_external_device failed: renderer and device are required");
    }
    blink_standalone_d3d12_external_device_t device_copy = *device;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync([inner, device_copy]() {
      return blink_standalone_renderer_configure_d3d12_external_device(
          inner, &device_copy);
    });
  }
  if (!renderer || !device) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "configure_d3d12_external_device failed: renderer and device are required");
  }
  if (renderer->runtime && !renderer->html.empty()) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "configure_d3d12_external_device failed: D3D12 device must be configured before first frame/runtime initialization");
  }
  if (!kStandaloneD3D12ExternalTargetsAvailable) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "configure_d3d12_external_device failed: D3D12/Dawn external targets are not enabled in this build");
  }
#if BUILDFLAG(IS_WIN)
  uint32_t luid_low = device->adapter_luid_low;
  int32_t luid_high = device->adapter_luid_high;
  if (luid_low == 0 && luid_high == 0) {
    if (!device->d3d12_device) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "configure_d3d12_external_device failed: pass adapter LUID or ID3D12Device");
    }
    LUID luid = static_cast<ID3D12Device*>(device->d3d12_device)
                    ->GetAdapterLuid();
    luid_low = luid.LowPart;
    luid_high = luid.HighPart;
  }
  renderer->runtime.reset();
  renderer->latest_result = html_css_renderer::CompositorFrameResult();
  renderer->external_d3d12_adapter_luid_low = luid_low;
  renderer->external_d3d12_adapter_luid_high = luid_high;
  renderer->external_d3d12_device =
      static_cast<ID3D12Device*>(device->d3d12_device);
  renderer->external_d3d12_command_queue =
      static_cast<ID3D12CommandQueue*>(device->d3d12_command_queue);
  renderer->external_d3d12_configured = true;
  return InitializeRuntime(renderer);
#else
  return SetLastError(
      renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
      "configure_d3d12_external_device failed: D3D12 is only available on Windows");
#endif
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_tick_gpu_source_frame_async(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_gpu_source_frame_tick_request_t* request,
    blink_standalone_gpu_source_frame_tick_result_t* result) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!request || !result) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "tick_gpu_source_frame_async failed: renderer, request, and result are required");
    }
    blink_standalone_gpu_source_frame_tick_request_t request_copy = *request;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, request_copy, result]() {
          return blink_standalone_renderer_tick_gpu_source_frame_async(
              inner, &request_copy, result);
        });
  }
  if (!renderer || !renderer->runtime || !request || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "tick_gpu_source_frame_async failed: renderer, request, and result are required");
  }
  *result = blink_standalone_gpu_source_frame_tick_result_t{};
  ClearLastError(renderer);
  PopulateGpuSourceFrameTickResult(renderer, request, result);

  const uint32_t backend = request->backend;
  if (backend != BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      backend != BLINK_STANDALONE_GPU_BACKEND_D3D12) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "tick_gpu_source_frame_async failed: backend must be Vulkan or D3D12");
  }
  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(renderer, backend);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "tick_gpu_source_frame_async failed: requested GPU backend is unavailable");
  }
  if (renderer->pending_async_gpu_frame.active) {
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "tick_gpu_source_frame_async pending: an async GPU frame is already in flight");
  }

  const uint32_t expected_logical_width =
      request->logical_width
          ? request->logical_width
          : static_cast<uint32_t>(std::max(0.0f, renderer->viewport.width));
  const uint32_t expected_logical_height =
      request->logical_height
          ? request->logical_height
          : static_cast<uint32_t>(std::max(0.0f, renderer->viewport.height));
  const float expected_dsf =
      request->device_scale_factor > 0.0f ? request->device_scale_factor
                                          : renderer->device_scale_factor;
  if (expected_logical_width !=
          static_cast<uint32_t>(std::max(0.0f, renderer->viewport.width)) ||
      expected_logical_height !=
          static_cast<uint32_t>(std::max(0.0f, renderer->viewport.height)) ||
      std::abs(expected_dsf - renderer->device_scale_factor) > 0.001f) {
    result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_STALE;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "tick_gpu_source_frame_async failed: expected logical size/DSF does not match renderer viewport");
  }

  const bool prepared_source_matches_request =
      renderer->prepared_gpu_source_frame.valid &&
      renderer->prepared_gpu_source_frame.backend == backend &&
      renderer->prepared_gpu_source_frame.request_generation ==
          request->request_generation &&
      renderer->prepared_gpu_source_frame.logical_width ==
          expected_logical_width &&
      renderer->prepared_gpu_source_frame.logical_height ==
          expected_logical_height &&
      std::abs(renderer->prepared_gpu_source_frame.device_scale_factor -
               expected_dsf) <= 0.001f &&
      (!request->physical_width ||
       renderer->prepared_gpu_source_frame.physical_width ==
           request->physical_width) &&
      (!request->physical_height ||
       renderer->prepared_gpu_source_frame.physical_height ==
           request->physical_height);
  if (prepared_source_matches_request && !HasPendingFrameInput(renderer) &&
      !renderer->gpu_prepare_required_after_update &&
      !renderer->gpu_source_frame_pending &&
      !renderer->latest_result.needs_output) {
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_NO_DEMAND;
    result->needs_output = 0;
    result->frame_skipped_due_to_no_demand = 1;
    return BLINK_STANDALONE_STATUS_OK;
  }

  InvalidatePreparedGpuSourceFrame(renderer);
  const bool request_pending_source_frame = renderer->gpu_source_frame_pending;
  const auto tick_start = std::chrono::steady_clock::now();
  const blink_standalone_status_code_t status =
      AdvanceGpuFrameForBackend(renderer, backend,
                                request_pending_source_frame);
  const auto tick_end = std::chrono::steady_clock::now();
  result->elapsed_ms =
      std::chrono::duration<double, std::milli>(tick_end - tick_start).count();
  PopulateGpuSourceFrameTickResult(renderer, request, result);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    result->status = status;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_FAILED;
    return status;
  }

  if (FrameResultHasGpuPreparePending(renderer->latest_result)) {
    renderer->gpu_source_frame_pending = true;
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "tick_gpu_source_frame_async pending: GPU source frame is not ready");
  }

  const uint32_t expected_physical_width =
      request->physical_width ? request->physical_width
                              : LatestPhysicalWidth(renderer);
  const uint32_t expected_physical_height =
      request->physical_height ? request->physical_height
                               : LatestPhysicalHeight(renderer);
  if ((expected_physical_width && LatestPhysicalWidth(renderer) &&
       LatestPhysicalWidth(renderer) != expected_physical_width) ||
      (expected_physical_height && LatestPhysicalHeight(renderer) &&
       LatestPhysicalHeight(renderer) != expected_physical_height)) {
    renderer->gpu_prepare_required_after_update = true;
    renderer->gpu_source_frame_pending = false;
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "tick_gpu_source_frame_async pending: GPU source frame size does not match the requested output");
  }

  renderer->prepared_gpu_source_frame.valid = true;
  renderer->prepared_gpu_source_frame.backend = backend;
  renderer->prepared_gpu_source_frame.request_generation =
      request->request_generation;
  renderer->prepared_gpu_source_frame.logical_width = expected_logical_width;
  renderer->prepared_gpu_source_frame.logical_height = expected_logical_height;
  renderer->prepared_gpu_source_frame.physical_width = expected_physical_width;
  renderer->prepared_gpu_source_frame.physical_height =
      expected_physical_height;
  renderer->prepared_gpu_source_frame.device_scale_factor = expected_dsf;
  renderer->gpu_prepare_required_after_update = false;
  renderer->gpu_source_frame_pending = false;
  PopulateGpuSourceFrameTickResult(renderer, request, result);
  result->status = BLINK_STANDALONE_STATUS_OK;
  result->state = BLINK_STANDALONE_GPU_SOURCE_FRAME_STATE_SOURCE_READY;
  result->source_frame_generation = request->request_generation;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_render_to_gpu_target(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_external_gpu_target_t* target,
    blink_standalone_gpu_render_result_t* result) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!target || !result) {
      return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                          "render_to_gpu_target failed: renderer, target, and result are required");
    }
    blink_standalone_external_gpu_target_t target_copy = *target;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, target_copy, result]() {
          return blink_standalone_renderer_render_to_gpu_target(
              inner, &target_copy, result);
        });
  }
  if (!renderer || !renderer->runtime || !target || !result) {
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                        "render_to_gpu_target failed: renderer, target, and result are required");
  }
  *result = blink_standalone_gpu_render_result_t{};
  ClearLastError(renderer);

  const uint32_t backend = target->common.backend;
  result->backend = backend;
  result->generation = target->common.generation;
  result->width = target->common.physical_width;
  result->height = target->common.physical_height;
  result->pixel_format = target->common.pixel_format;
  PopulateGpuFrameState(renderer, result);
  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(renderer, backend);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
                        "render_to_gpu_target failed: requested GPU backend is unavailable");
  }
  const bool internal_standin =
      (target->common.flags &
       BLINK_STANDALONE_GPU_TARGET_INTERNAL_TEST_STANDIN) != 0;
  const bool force_pending_once =
      (target->common.flags &
       BLINK_STANDALONE_GPU_TARGET_INTERNAL_FORCE_PENDING_ONCE) != 0;
  const bool d3d12_external =
      backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
      target->d3d12.shared_handle != nullptr;
  const bool vulkan_external =
      backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      target->vulkan.vk_image != nullptr;
  if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
      !target->d3d12.shared_handle && target->d3d12.d3d12_resource) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "render_to_gpu_target failed: raw D3D12 resource pointers require "
        "same-device setup, which is not part of this checkpoint; pass a "
        "shared_handle for the external D3D12 target path");
  }
  if (!internal_standin && !d3d12_external && !vulkan_external) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "render_to_gpu_target failed: external native target handles are not "
        "accepted by this experimental build; use the internal stand-in smoke "
        "or wait for embedder handle adoption");
  }
  if (CanSkipCleanGpuRender(renderer, target)) {
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->target_written = 0;
    result->needs_output = 0;
    result->frame_advanced = 0;
    result->frame_skipped_due_to_no_demand = 1;
    result->full_frame_damage = 0;
    return BLINK_STANDALONE_STATUS_OK;
  }

  const bool external_target = d3d12_external || vulkan_external;
  const bool collect_updated_frame =
      external_target && renderer->latest_result.frame_advanced &&
      renderer->latest_result.needs_output &&
      !FrameResultHasGpuPreparePending(renderer->latest_result) &&
      FrameResultHasPublicFrameMetadata(renderer->latest_result) &&
      !renderer->gpu_prepare_required_after_update &&
      !renderer->gpu_source_frame_pending &&
      !HasPendingFrameInput(renderer);
  if (!collect_updated_frame) {
    const bool request_prepared_external_source =
        external_target && renderer->gpu_source_frame_pending;
    blink_standalone_status_code_t status =
        AdvanceGpuFrameForBackend(renderer, backend,
                                  /*require_source_gpu_frame=*/
                                  !external_target ||
                                      request_prepared_external_source);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      if (external_target &&
          IsRecoverableGpuCopyOutputNotReady(
              renderer->latest_result.gpu_frame_failure)) {
        renderer->gpu_prepare_required_after_update = true;
        renderer->gpu_source_frame_pending = false;
        renderer->runtime->ReleaseExternalGpuTargetState();
        result->status = BLINK_STANDALONE_STATUS_PENDING;
        return SetLastError(
            renderer, BLINK_STANDALONE_STATUS_PENDING,
            "render_to_gpu_target pending: Viz CopyOutput did not produce "
            "output");
      }
      result->status = status;
      return status;
    }
    if (external_target &&
        FrameResultHasGpuPreparePending(renderer->latest_result)) {
      renderer->gpu_source_frame_pending = true;
      renderer->runtime->ReleaseExternalGpuTargetState();
      result->status = BLINK_STANDALONE_STATUS_PENDING;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_PENDING,
          "render_to_gpu_target pending: GPU source frame is not ready");
    }
    if (external_target &&
        !LatestGpuOutputSizeMatchesTarget(renderer, target)) {
      renderer->gpu_prepare_required_after_update = true;
      renderer->gpu_source_frame_pending = false;
      renderer->runtime->ReleaseExternalGpuTargetState();
      result->status = BLINK_STANDALONE_STATUS_PENDING;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_PENDING,
          "render_to_gpu_target pending: GPU source frame size does not match "
          "the external target");
    }
    renderer->gpu_source_frame_pending = false;
  }
  if (force_pending_once) {
    renderer->gpu_source_frame_pending = true;
    renderer->runtime->ReleaseExternalGpuTargetState();
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "render_to_gpu_target pending: forced internal retry test");
  }

  std::string target_result;
  if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
    if (vulkan_external) {
      if (!renderer->external_vulkan_configured) {
        result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
        return SetLastError(
            renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
            "render_to_gpu_target failed: Vulkan external targets require configure_vulkan_external_device before first frame");
      }
      std::string validation_failure;
      if (!ValidateVulkanExternalTarget(*target, &validation_failure)) {
        result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
        return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                            validation_failure);
      }
      html_css_renderer::ExternalVulkanImageTarget external_target;
      external_target.vk_image = target->vulkan.vk_image;
      external_target.vk_device_memory = target->vulkan.vk_device_memory;
      external_target.width = static_cast<int>(target->vulkan.width);
      external_target.height = static_cast<int>(target->vulkan.height);
      external_target.vk_format = target->vulkan.vk_format;
      external_target.image_tiling = target->vulkan.image_tiling;
      external_target.allocation_size = target->vulkan.allocation_size;
      external_target.memory_type_index = target->vulkan.memory_type_index;
      external_target.image_usage_flags = target->vulkan.image_usage_flags;
      external_target.image_create_flags = 0;
      external_target.queue_family_index = target->vulkan.queue_family_index;
      target_result =
          renderer->runtime->RenderExternalVkImageToTarget(external_target);
    } else {
      target_result =
          renderer->runtime->RunBorrowedVkImageRenderCopySmokeForTesting();
    }
  } else if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
    if (d3d12_external) {
      const int d3d12_target_width =
          target->d3d12.width ? static_cast<int>(target->d3d12.width)
                              : static_cast<int>(target->common.physical_width);
      const int d3d12_target_height =
          target->d3d12.height
              ? static_cast<int>(target->d3d12.height)
              : static_cast<int>(target->common.physical_height);
      target_result = renderer->runtime->RenderExternalD3D12ToTarget(
          target->d3d12.d3d12_resource, target->d3d12.shared_handle,
          d3d12_target_width, d3d12_target_height);
    } else {
      target_result =
          renderer->runtime->RunBorrowedD3D12RenderCopySmokeForTesting();
    }
  } else {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    return SetLastError(renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
                        "render_to_gpu_target failed: backend is not a GPU target backend");
  }

  const bool expected_result_prefix =
      StartsWith(target_result, "gpu_borrowed_") ||
      StartsWith(target_result, "gpu_external_");
  if (target_result.find("cannot initialize without LocalSurfaceId") !=
      std::string::npos) {
    renderer->gpu_source_frame_pending = true;
    renderer->runtime->ReleaseExternalGpuTargetState();
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "render_to_gpu_target pending: GPU source frame is not ready");
  }
  if (IsRecoverableGpuCopyOutputNotReady(target_result)) {
    renderer->gpu_prepare_required_after_update = true;
    renderer->gpu_source_frame_pending = false;
    renderer->runtime->ReleaseExternalGpuTargetState();
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "render_to_gpu_target pending: Viz CopyOutput did not produce output");
  }
  if (!expected_result_prefix ||
      target_result.find(": ok") == std::string::npos) {
    const bool invalid_external_d3d12_target =
        backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
        target_result.find(
            "borrowed external D3D12 shared handle open failed") !=
            std::string::npos;
    const blink_standalone_status_code_t failure_status =
        invalid_external_d3d12_target
            ? BLINK_STANDALONE_STATUS_INVALID_ARGUMENT
            : BLINK_STANDALONE_STATUS_RENDER_FAILED;
    result->status = failure_status;
    return SetLastError(
        renderer, failure_status,
        target_result.empty()
            ? "render_to_gpu_target failed: GPU target writer returned no result"
            : target_result);
  }
  result->status = BLINK_STANDALONE_STATUS_OK;
  result->target_written = 1;
  if (external_target) {
    RefreshPublicFrameMetadata(renderer);
  }
  renderer->latest_result.needs_output = false;
  renderer->gpu_prepare_required_after_update = false;
  renderer->gpu_source_frame_pending = false;
  if (result->width == 0) {
    result->width = static_cast<uint32_t>(
        renderer->latest_result.viz_display_output_size.width);
  }
  if (result->height == 0) {
    result->height = static_cast<uint32_t>(
        renderer->latest_result.viz_display_output_size.height);
  }
  if (result->pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_NONE) {
    result->pixel_format = BLINK_STANDALONE_PIXEL_FORMAT_RGBA8;
  }
  PopulateGpuFrameState(renderer, result);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_render_gpu_backdrop_frame(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_gpu_backdrop_render_request_t* request,
    blink_standalone_gpu_backdrop_render_result_t* result) {
  if (!renderer || !renderer->runtime || !request || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "render_gpu_backdrop_frame failed: renderer, request, and result are required");
  }
  *result = blink_standalone_gpu_backdrop_render_result_t{};
  ClearLastError(renderer);

  const bool mask_required =
      (request->flags & BLINK_STANDALONE_GPU_BACKDROP_MASK_REQUIRED) != 0;
  const uint32_t backend = request->backend;
  if (backend != BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      backend != BLINK_STANDALONE_GPU_BACKEND_D3D12) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "render_gpu_backdrop_frame failed: backend must be Vulkan or D3D12");
  }
  if (request->mask_encoding !=
      BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_RGBA8_ID_COVERAGE) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "render_gpu_backdrop_frame failed: unsupported backdrop mask encoding");
  }
  const bool mask_target_backend_specified =
      request->backdrop_mask_target.common.backend !=
      BLINK_STANDALONE_GPU_BACKEND_NONE;
  if (request->main_target.common.backend != backend ||
      ((mask_required || mask_target_backend_specified) &&
       request->backdrop_mask_target.common.backend != backend)) {
    result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "render_gpu_backdrop_frame failed: main and mask targets must match the requested backend");
  }

  blink_standalone_gpu_render_result_t main_result = {};
  blink_standalone_status_code_t status =
      blink_standalone_renderer_render_to_gpu_target(
          renderer, &request->main_target, &main_result);
  result->backend = backend;
  result->status = status;
  result->main_target_written = main_result.target_written;
  result->width = main_result.width;
  result->height = main_result.height;
  result->pixel_format = main_result.pixel_format;
  result->frame_generation = request->main_target.common.generation;
  result->main_target_generation = main_result.generation;
  result->backdrop_mask_generation =
      request->backdrop_mask_target.common.generation;
  result->mask_encoding = request->mask_encoding;
  result->needs_output = main_result.needs_output;
  result->frame_advanced = main_result.frame_advanced;
  result->frame_skipped_due_to_no_demand =
      main_result.frame_skipped_due_to_no_demand;
  result->full_frame_damage = main_result.full_frame_damage;
  result->damage_rect_count = main_result.dirty_rect_count;
  result->physical_width = main_result.physical_width;
  result->physical_height = main_result.physical_height;
  if (status != BLINK_STANDALONE_STATUS_OK) {
    return status;
  }
  if (main_result.target_written == 0) {
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->backdrop_mask_written = 0;
    result->effect_count = 0;
    result->max_effect_id = 0;
    result->frame_generation = main_result.frame_generation;
    return BLINK_STANDALONE_STATUS_OK;
  }

  const size_t effect_count =
      std::min(renderer->latest_result.backdrop_filter_regions.size(),
               static_cast<size_t>(255u));
  result->effect_count = static_cast<uint32_t>(effect_count);
  result->max_effect_id = static_cast<uint32_t>(effect_count);
  if (mask_required && effect_count == 0) {
    result->status = BLINK_STANDALONE_STATUS_RENDER_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
        "render_gpu_backdrop_frame failed: no backdrop effects were collected for the rendered frame");
  }

  const bool mask_internal_standin =
      (request->backdrop_mask_target.common.flags &
       BLINK_STANDALONE_GPU_TARGET_INTERNAL_TEST_STANDIN) != 0;
  const bool mask_has_vulkan_target =
      backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      request->backdrop_mask_target.vulkan.vk_image != nullptr;
  const bool mask_has_d3d12_target =
      backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
      (request->backdrop_mask_target.d3d12.shared_handle != nullptr ||
       request->backdrop_mask_target.d3d12.d3d12_resource != nullptr);
  if (!mask_internal_standin && !mask_has_vulkan_target &&
      !mask_has_d3d12_target) {
    result->status = mask_required ? BLINK_STANDALONE_STATUS_INVALID_ARGUMENT
                                   : BLINK_STANDALONE_STATUS_OK;
    if (!mask_required) {
      return BLINK_STANDALONE_STATUS_OK;
    }
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "render_gpu_backdrop_frame failed: a backdrop mask target is required");
  }

  std::string mask_result;
  const char* expected_mask_prefix = "";
  if (mask_internal_standin) {
    mask_result =
        backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN
            ? renderer->runtime->RunVulkanBackdropMaskPrototypeForTesting()
            : renderer->runtime->RunD3D12BackdropMaskPrototypeForTesting();
    expected_mask_prefix =
        backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN
            ? "gpu_vulkan_backdrop_mask_prototype_smoke: ok"
            : "gpu_d3d12_backdrop_mask_prototype_smoke: ok";
  } else if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
    std::string validation_failure;
    if (!ValidateVulkanExternalTarget(request->backdrop_mask_target,
                                      &validation_failure)) {
      result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
      return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                          "render_gpu_backdrop_frame failed: " +
                              validation_failure);
    }
    html_css_renderer::ExternalVulkanImageTarget mask_target;
    mask_target.vk_image = request->backdrop_mask_target.vulkan.vk_image;
    mask_target.vk_device_memory =
        request->backdrop_mask_target.vulkan.vk_device_memory;
    mask_target.width =
        static_cast<int>(request->backdrop_mask_target.vulkan.width);
    mask_target.height =
        static_cast<int>(request->backdrop_mask_target.vulkan.height);
    mask_target.vk_format = request->backdrop_mask_target.vulkan.vk_format;
    mask_target.image_tiling =
        request->backdrop_mask_target.vulkan.image_tiling;
    mask_target.allocation_size =
        request->backdrop_mask_target.vulkan.allocation_size;
    mask_target.memory_type_index =
        request->backdrop_mask_target.vulkan.memory_type_index;
    mask_target.image_usage_flags =
        request->backdrop_mask_target.vulkan.image_usage_flags;
    mask_target.image_create_flags = 0;
    mask_target.queue_family_index =
        request->backdrop_mask_target.vulkan.queue_family_index;
    mask_result =
        renderer->runtime->RenderBackdropMaskToExternalVkImage(mask_target);
    expected_mask_prefix = "gpu_external_vkimage_backdrop_mask: ok";
  } else {
    const int mask_width =
        request->backdrop_mask_target.d3d12.width
            ? static_cast<int>(request->backdrop_mask_target.d3d12.width)
            : static_cast<int>(
                  request->backdrop_mask_target.common.physical_width);
    const int mask_height =
        request->backdrop_mask_target.d3d12.height
            ? static_cast<int>(request->backdrop_mask_target.d3d12.height)
            : static_cast<int>(
                  request->backdrop_mask_target.common.physical_height);
    mask_result = renderer->runtime->RenderBackdropMaskToExternalD3D12Target(
        request->backdrop_mask_target.d3d12.d3d12_resource,
        request->backdrop_mask_target.d3d12.shared_handle, mask_width,
        mask_height);
    expected_mask_prefix = "gpu_external_d3d12_backdrop_mask: ok";
  }
  if (!StartsWith(mask_result, expected_mask_prefix)) {
    const blink_standalone_status_code_t failure_status =
        mask_result.find(": blocked") != std::string::npos
            ? BLINK_STANDALONE_STATUS_UNSUPPORTED
            : BLINK_STANDALONE_STATUS_RENDER_FAILED;
    result->status = failure_status;
    return SetLastError(
        renderer, failure_status,
        mask_result.empty()
            ? "render_gpu_backdrop_frame failed: backdrop mask writer returned no result"
            : mask_result);
  }

  result->status = BLINK_STANDALONE_STATUS_OK;
  result->backdrop_mask_written = 1;
  renderer->gpu_backdrop_frame_generation =
      std::max(request->main_target.common.generation,
               request->backdrop_mask_target.common.generation);
  result->frame_generation = renderer->gpu_backdrop_frame_generation;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_poll_gpu_frame_async(
    blink_standalone_renderer_t* renderer,
    uint64_t request_id,
    blink_standalone_gpu_async_render_result_t* result);

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_submit_gpu_frame_async(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_gpu_async_render_request_t* request,
    blink_standalone_gpu_async_render_result_t* result) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!request || !result) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "submit_gpu_frame_async failed: renderer, request, and result are required");
    }
    blink_standalone_gpu_async_render_request_t request_copy = *request;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, request_copy, result]() {
          return blink_standalone_renderer_submit_gpu_frame_async(
              inner, &request_copy, result);
        });
  }
  if (!renderer || !renderer->runtime || !request || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "submit_gpu_frame_async failed: renderer, request, and result are required");
  }
  *result = blink_standalone_gpu_async_render_result_t{};
  ClearLastError(renderer);

  if (renderer->pending_async_gpu_frame.active) {
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
    result->request_id = renderer->pending_async_gpu_frame.request_id;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        "submit_gpu_frame_async pending: an async GPU frame is already in flight");
  }

  const uint32_t backend = request->backend;
  result->backend = backend;
  result->request_generation = request->request_generation;
  result->main_target_generation = request->main_target.common.generation;
  result->backdrop_mask_generation =
      request->backdrop_mask_target.common.generation;
  result->pixel_format = request->main_target.common.pixel_format;
  result->mask_encoding = request->mask_encoding;

  const bool wants_backdrop_mask =
      request->backdrop_mask_target.common.backend !=
          BLINK_STANDALONE_GPU_BACKEND_NONE ||
      (request->flags & BLINK_STANDALONE_GPU_ASYNC_BACKDROP_MASK_REQUIRED) != 0;
  if (backend != BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      backend != BLINK_STANDALONE_GPU_BACKEND_D3D12) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "submit_gpu_frame_async failed: backend must be Vulkan or D3D12");
  }
  if (request->main_target.common.backend != backend ||
      (wants_backdrop_mask &&
       request->backdrop_mask_target.common.backend != backend)) {
    result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "submit_gpu_frame_async failed: main and mask targets must match the requested backend");
  }
  if (wants_backdrop_mask &&
      request->mask_encoding !=
          BLINK_STANDALONE_GPU_BACKDROP_MASK_ENCODING_RGBA8_ID_COVERAGE) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "submit_gpu_frame_async failed: unsupported backdrop mask encoding");
  }

  blink_standalone_external_gpu_target_t main_target = request->main_target;
  if ((request->flags & BLINK_STANDALONE_GPU_ASYNC_SKIP_IF_CLEAN) != 0) {
    main_target.common.flags |= BLINK_STANDALONE_GPU_TARGET_SKIP_IF_CLEAN;
  }
  const bool prepared_source_matches =
      PreparedGpuSourceMatchesTarget(renderer, backend, &main_target,
                                     request->request_generation);
  if (!prepared_source_matches && CanSkipCleanGpuRender(renderer, &main_target)) {
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_NO_DEMAND;
    result->needs_output = 0;
    result->frame_skipped_due_to_no_demand = 1;
    result->physical_width = main_target.common.physical_width;
    result->physical_height = main_target.common.physical_height;
    return BLINK_STANDALONE_STATUS_OK;
  }

  const uint32_t capabilities =
      blink_standalone_renderer_gpu_backend_capabilities(renderer, backend);
  if ((capabilities & BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE) == 0) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "submit_gpu_frame_async failed: requested GPU backend is unavailable");
  }
  const bool d3d12_external =
      backend == BLINK_STANDALONE_GPU_BACKEND_D3D12 &&
      main_target.d3d12.shared_handle != nullptr;
  const bool vulkan_external =
      backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN &&
      main_target.vulkan.vk_image != nullptr;
  if (!d3d12_external && !vulkan_external) {
    result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
        "submit_gpu_frame_async failed: async rendering requires a real external target handle");
  }

  if (!prepared_source_matches) {
    blink_standalone_status_code_t status =
        AdvanceGpuFrameForBackend(renderer, backend,
                                  /*require_source_gpu_frame=*/false);
    if (status != BLINK_STANDALONE_STATUS_OK) {
      result->status = status;
      result->state = status == BLINK_STANDALONE_STATUS_PENDING
                          ? BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING
                          : BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
      return status;
    }
    if (FrameResultHasGpuPreparePending(renderer->latest_result)) {
      renderer->gpu_source_frame_pending = true;
      // No external copy request has been accepted yet. Keep the offscreen
      // Display/output state alive so pending source-frame work can settle
      // before the embedder retries.
      result->status = BLINK_STANDALONE_STATUS_PENDING;
      result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_PENDING,
          "submit_gpu_frame_async pending: GPU source frame is not ready");
    }
    if (!LatestGpuOutputSizeMatchesTarget(renderer, &main_target)) {
      renderer->gpu_prepare_required_after_update = true;
      renderer->gpu_source_frame_pending = false;
      renderer->runtime->ReleaseExternalGpuTargetState();
      result->status = BLINK_STANDALONE_STATUS_PENDING;
      result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_PENDING,
          "submit_gpu_frame_async pending: GPU source frame size does not match the external target");
    }
  } else {
    renderer->gpu_source_frame_pending = false;
  }

  html_css_renderer::ExternalGpuTargetCopyResult copy_result;
  if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
    if (!renderer->external_vulkan_configured) {
      result->status = BLINK_STANDALONE_STATUS_UNSUPPORTED;
      result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_UNSUPPORTED,
          "submit_gpu_frame_async failed: Vulkan external targets require configure_vulkan_external_device before first frame");
    }
    std::string validation_failure;
    if (!ValidateVulkanExternalTarget(main_target, &validation_failure)) {
      result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
      result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
      return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                          validation_failure);
    }
    html_css_renderer::ExternalVulkanImageTarget external_target;
    external_target.vk_image = main_target.vulkan.vk_image;
    external_target.vk_device_memory = main_target.vulkan.vk_device_memory;
    external_target.width = static_cast<int>(main_target.vulkan.width);
    external_target.height = static_cast<int>(main_target.vulkan.height);
    external_target.vk_format = main_target.vulkan.vk_format;
    external_target.image_tiling = main_target.vulkan.image_tiling;
    external_target.allocation_size = main_target.vulkan.allocation_size;
    external_target.memory_type_index = main_target.vulkan.memory_type_index;
    external_target.image_usage_flags = main_target.vulkan.image_usage_flags;
    external_target.image_create_flags = 0;
    external_target.queue_family_index =
        main_target.vulkan.queue_family_index;
    copy_result =
        renderer->runtime->BeginRenderExternalVkImageToTargetAsync(
            external_target);
  } else {
    const int d3d12_target_width =
        main_target.d3d12.width ? static_cast<int>(main_target.d3d12.width)
                                : static_cast<int>(
                                      main_target.common.physical_width);
    const int d3d12_target_height =
        main_target.d3d12.height ? static_cast<int>(main_target.d3d12.height)
                                 : static_cast<int>(
                                       main_target.common.physical_height);
    copy_result = renderer->runtime->BeginRenderExternalD3D12ToTargetAsync(
        main_target.d3d12.d3d12_resource, main_target.d3d12.shared_handle,
        d3d12_target_width, d3d12_target_height);
  }

  PopulateAsyncGpuFrameState(renderer, copy_result, result);
  result->backend = backend;
  result->request_generation = request->request_generation;
  result->main_target_generation = main_target.common.generation;
  result->backdrop_mask_generation =
      request->backdrop_mask_target.common.generation;
  result->pixel_format = main_target.common.pixel_format;
  result->mask_encoding = request->mask_encoding;
  if (copy_result.status ==
      html_css_renderer::ExternalGpuTargetCopyStatus::kFailed) {
    if (copy_result.request_id == 0 &&
        IsRecoverableGpuCopyOutputNotReady(copy_result.diagnostic)) {
      renderer->gpu_source_frame_pending = true;
      result->status = BLINK_STANDALONE_STATUS_PENDING;
      result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_PENDING,
          copy_result.diagnostic.empty()
              ? "submit_gpu_frame_async pending: Viz CopyOutput did not produce output"
              : copy_result.diagnostic);
    }
    return SetLastError(renderer,
                        static_cast<blink_standalone_status_code_t>(
                            result->status),
                        copy_result.diagnostic.empty()
                            ? "submit_gpu_frame_async failed"
                            : copy_result.diagnostic);
  }
  if (copy_result.status ==
          html_css_renderer::ExternalGpuTargetCopyStatus::kPending &&
      copy_result.request_id == 0) {
    renderer->gpu_source_frame_pending = true;
    result->status = BLINK_STANDALONE_STATUS_PENDING;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_PENDING,
        copy_result.diagnostic.empty()
            ? "submit_gpu_frame_async pending: GPU copy request was not accepted yet"
            : copy_result.diagnostic);
  }

  InvalidatePreparedGpuSourceFrame(renderer);
  renderer->pending_async_gpu_frame.active = true;
  renderer->pending_async_gpu_frame.backdrop = wants_backdrop_mask;
  renderer->pending_async_gpu_frame.mask_required =
      (request->flags & BLINK_STANDALONE_GPU_ASYNC_BACKDROP_MASK_REQUIRED) != 0;
  renderer->pending_async_gpu_frame.main_copy_completed = false;
  renderer->pending_async_gpu_frame.request_id = copy_result.request_id;
  renderer->pending_async_gpu_frame.request_generation =
      request->request_generation;
  renderer->pending_async_gpu_frame.backend = backend;
  renderer->pending_async_gpu_frame.mask_encoding = request->mask_encoding;
  renderer->pending_async_gpu_frame.main_target = main_target;
  renderer->pending_async_gpu_frame.backdrop_mask_target =
      request->backdrop_mask_target;
  renderer->pending_async_gpu_frame.completed_main_result = {};
  if (result->state == BLINK_STANDALONE_GPU_ASYNC_STATE_COMPLETED) {
    renderer->pending_async_gpu_frame.active = false;
    result->main_target_written = 1;
    renderer->latest_result.needs_output = false;
  }
  if ((request->flags & BLINK_STANDALONE_GPU_ASYNC_BLOCK_UNTIL_COMPLETE) != 0) {
    while (result->state == BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING ||
           result->state == BLINK_STANDALONE_GPU_ASYNC_STATE_SUBMITTED) {
      blink_standalone_status_code_t poll_status =
          blink_standalone_renderer_poll_gpu_frame_async(
              renderer, result->request_id, result);
      if (poll_status != BLINK_STANDALONE_STATUS_OK &&
          poll_status != BLINK_STANDALONE_STATUS_PENDING) {
        return poll_status;
      }
    }
  }
  return result->status == BLINK_STANDALONE_STATUS_PENDING
             ? BLINK_STANDALONE_STATUS_PENDING
             : BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_poll_gpu_frame_async(
    blink_standalone_renderer_t* renderer,
    uint64_t request_id,
    blink_standalone_gpu_async_render_result_t* result) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!result) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "poll_gpu_frame_async failed: renderer and result are required");
    }
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, request_id, result]() {
          return blink_standalone_renderer_poll_gpu_frame_async(
              inner, request_id, result);
        });
  }
  if (!renderer || !renderer->runtime || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "poll_gpu_frame_async failed: renderer and result are required");
  }
  *result = blink_standalone_gpu_async_render_result_t{};
  ClearLastError(renderer);
  if (!renderer->pending_async_gpu_frame.active ||
      renderer->pending_async_gpu_frame.request_id != request_id) {
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_STALE;
    result->request_id = request_id;
    return BLINK_STANDALONE_STATUS_OK;
  }

  if (renderer->pending_async_gpu_frame.main_copy_completed) {
    *result = renderer->pending_async_gpu_frame.completed_main_result;
  } else {
    html_css_renderer::ExternalGpuTargetCopyResult copy_result =
        renderer->runtime->PollExternalGpuTargetAsyncCopy();
    PopulateAsyncGpuFrameState(renderer, copy_result, result);
    result->backend = renderer->pending_async_gpu_frame.backend;
    result->request_generation =
        renderer->pending_async_gpu_frame.request_generation;
    result->main_target_generation =
        renderer->pending_async_gpu_frame.main_target.common.generation;
    result->backdrop_mask_generation =
        renderer->pending_async_gpu_frame.backdrop_mask_target.common.generation;
    result->pixel_format =
        renderer->pending_async_gpu_frame.main_target.common.pixel_format;
    result->mask_encoding = renderer->pending_async_gpu_frame.mask_encoding;
    if (result->state == BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING) {
      return BLINK_STANDALONE_STATUS_PENDING;
    }
    if (result->state != BLINK_STANDALONE_GPU_ASYNC_STATE_COMPLETED) {
      renderer->pending_async_gpu_frame.active = false;
      if (result->state == BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED) {
        return SetLastError(renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
                            copy_result.diagnostic.empty()
                                ? "poll_gpu_frame_async failed"
                                : copy_result.diagnostic);
      }
      return BLINK_STANDALONE_STATUS_OK;
    }

    result->main_target_written = 1;
    renderer->pending_async_gpu_frame.main_copy_completed = true;
    renderer->pending_async_gpu_frame.completed_main_result = *result;
  }

  if (renderer->pending_async_gpu_frame.backdrop) {
    if (renderer->latest_result.backdrop_filter_regions.empty()) {
      RefreshPublicFrameMetadata(renderer);
    }
    const size_t effect_count =
        std::min(renderer->latest_result.backdrop_filter_regions.size(),
                 static_cast<size_t>(255u));
    result->effect_count = static_cast<uint32_t>(effect_count);
    result->max_effect_id = static_cast<uint32_t>(effect_count);
    if (renderer->pending_async_gpu_frame.mask_required && effect_count == 0) {
      renderer->pending_async_gpu_frame.active = false;
      result->status = BLINK_STANDALONE_STATUS_RENDER_FAILED;
      result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
          "poll_gpu_frame_async failed: no backdrop effects were collected for the rendered frame");
    }

    std::string mask_result;
    const uint32_t backend = renderer->pending_async_gpu_frame.backend;
    if (backend == BLINK_STANDALONE_GPU_BACKEND_VULKAN) {
      std::string validation_failure;
      if (!ValidateVulkanExternalTarget(
              renderer->pending_async_gpu_frame.backdrop_mask_target,
              &validation_failure)) {
        renderer->pending_async_gpu_frame.active = false;
        result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
        result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
        return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                            validation_failure);
      }
      html_css_renderer::ExternalVulkanImageTarget mask_target;
      const auto& target =
          renderer->pending_async_gpu_frame.backdrop_mask_target;
      mask_target.vk_image = target.vulkan.vk_image;
      mask_target.vk_device_memory = target.vulkan.vk_device_memory;
      mask_target.width = static_cast<int>(target.vulkan.width);
      mask_target.height = static_cast<int>(target.vulkan.height);
      mask_target.vk_format = target.vulkan.vk_format;
      mask_target.image_tiling = target.vulkan.image_tiling;
      mask_target.allocation_size = target.vulkan.allocation_size;
      mask_target.memory_type_index = target.vulkan.memory_type_index;
      mask_target.image_usage_flags = target.vulkan.image_usage_flags;
      mask_target.image_create_flags = 0;
      mask_target.queue_family_index = target.vulkan.queue_family_index;
      mask_result =
          renderer->runtime->RenderBackdropMaskToExternalVkImage(mask_target);
      if (!StartsWith(mask_result, "gpu_external_vkimage_backdrop_mask: ok")) {
        if (renderer->pending_async_gpu_frame.mask_required &&
            mask_result.find("backdrop mask target remained empty") !=
                std::string::npos) {
          result->status = BLINK_STANDALONE_STATUS_PENDING;
          result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_PENDING;
          result->main_target_written = 0;
          result->backdrop_mask_written = 0;
          result->effect_count = 0;
          result->max_effect_id = 0;
          return SetLastError(renderer, BLINK_STANDALONE_STATUS_PENDING,
                              mask_result);
        }
        renderer->pending_async_gpu_frame.active = false;
        result->status = BLINK_STANDALONE_STATUS_RENDER_FAILED;
        result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
        return SetLastError(renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
                            mask_result);
      }
    } else if (backend == BLINK_STANDALONE_GPU_BACKEND_D3D12) {
      const auto& target =
          renderer->pending_async_gpu_frame.backdrop_mask_target;
      const int mask_width =
          target.d3d12.width
              ? static_cast<int>(target.d3d12.width)
              : static_cast<int>(target.common.physical_width);
      const int mask_height =
          target.d3d12.height
              ? static_cast<int>(target.d3d12.height)
              : static_cast<int>(target.common.physical_height);
      mask_result = renderer->runtime->RenderBackdropMaskToExternalD3D12Target(
          target.d3d12.d3d12_resource, target.d3d12.shared_handle, mask_width,
          mask_height);
      if (!StartsWith(mask_result, "gpu_external_d3d12_backdrop_mask: ok")) {
        renderer->pending_async_gpu_frame.active = false;
        result->status = BLINK_STANDALONE_STATUS_RENDER_FAILED;
        result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_FAILED;
        return SetLastError(renderer, BLINK_STANDALONE_STATUS_RENDER_FAILED,
                            mask_result);
      }
    }
    result->backdrop_mask_written = 1;
    renderer->gpu_backdrop_frame_generation = std::max(
        renderer->pending_async_gpu_frame.main_target.common.generation,
        renderer->pending_async_gpu_frame.backdrop_mask_target.common.generation);
    result->frame_generation = renderer->gpu_backdrop_frame_generation;
  }

  renderer->latest_result.needs_output = false;
  renderer->gpu_prepare_required_after_update = false;
  renderer->gpu_source_frame_pending = false;
  renderer->pending_async_gpu_frame.active = false;
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_cancel_gpu_frame_async(
    blink_standalone_renderer_t* renderer,
    uint64_t request_id,
    blink_standalone_gpu_async_render_result_t* result) {
  if (IsDedicatedThreadShell(renderer)) {
    if (!result) {
      return SetLastError(
          renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
          "cancel_gpu_frame_async failed: renderer and result are required");
    }
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    return DedicatedSequenceFor(renderer).CallSync(
        [inner, request_id, result]() {
          return blink_standalone_renderer_cancel_gpu_frame_async(
              inner, request_id, result);
        });
  }
  if (!renderer || !renderer->runtime || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "cancel_gpu_frame_async failed: renderer and result are required");
  }
  *result = blink_standalone_gpu_async_render_result_t{};
  ClearLastError(renderer);
  if (!renderer->pending_async_gpu_frame.active ||
      renderer->pending_async_gpu_frame.request_id != request_id) {
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_GPU_ASYNC_STATE_STALE;
    result->request_id = request_id;
    return BLINK_STANDALONE_STATUS_OK;
  }
  html_css_renderer::ExternalGpuTargetCopyResult copy_result =
      renderer->runtime->CancelExternalGpuTargetAsyncCopy();
  PopulateAsyncGpuFrameState(renderer, copy_result, result);
  result->backend = renderer->pending_async_gpu_frame.backend;
  result->request_generation =
      renderer->pending_async_gpu_frame.request_generation;
  renderer->pending_async_gpu_frame.active = false;
  renderer->gpu_source_frame_pending = false;
  renderer->gpu_prepare_required_after_update = true;
  InvalidatePreparedGpuSourceFrame(renderer);
  renderer->runtime->ReleaseExternalGpuTargetState();
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_post_dedicated_thread_gpu_frame(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_dedicated_thread_gpu_frame_request_t* request,
    blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
  if (!renderer || !request || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "post_dedicated_thread_gpu_frame failed: renderer, request, and result are required");
  }
  *result = blink_standalone_dedicated_thread_gpu_frame_result_t{};
  if (!IsDedicatedThreadShell(renderer) || !renderer->dedicated_thread_inner) {
    result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "post_dedicated_thread_gpu_frame failed: renderer was not created with create_dedicated_thread");
  }
  ClearLastError(renderer);
  const uint64_t command_id = DedicatedSequenceFor(renderer).PostGpuFrame(
      renderer->dedicated_thread_inner, *request);
  result->command_id = command_id;
  result->status = BLINK_STANDALONE_STATUS_PENDING;
  result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING;
  return BLINK_STANDALONE_STATUS_PENDING;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_poll_dedicated_thread_gpu_frame(
    blink_standalone_renderer_t* renderer,
    uint64_t command_id,
    blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
  if (!renderer || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "poll_dedicated_thread_gpu_frame failed: renderer and result are required");
  }
  *result = blink_standalone_dedicated_thread_gpu_frame_result_t{};
  if (!IsDedicatedThreadShell(renderer)) {
    result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "poll_dedicated_thread_gpu_frame failed: renderer was not created with create_dedicated_thread");
  }
  ClearLastError(renderer);
  if (!DedicatedSequenceFor(renderer).PollGpuFrame(command_id, result)) {
    result->command_id = command_id;
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_STALE;
    return BLINK_STANDALONE_STATUS_OK;
  }
  return result->state == BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING
             ? BLINK_STANDALONE_STATUS_PENDING
             : static_cast<blink_standalone_status_code_t>(result->status);
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_cancel_dedicated_thread_gpu_frame(
    blink_standalone_renderer_t* renderer,
    uint64_t command_id,
    blink_standalone_dedicated_thread_gpu_frame_result_t* result) {
  if (!renderer || !result) {
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "cancel_dedicated_thread_gpu_frame failed: renderer and result are required");
  }
  *result = blink_standalone_dedicated_thread_gpu_frame_result_t{};
  if (!IsDedicatedThreadShell(renderer)) {
    result->status = BLINK_STANDALONE_STATUS_INVALID_ARGUMENT;
    result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_FAILED;
    return SetLastError(
        renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "cancel_dedicated_thread_gpu_frame failed: renderer was not created with create_dedicated_thread");
  }
  ClearLastError(renderer);
  if (!DedicatedSequenceFor(renderer).CancelGpuFrame(command_id, result)) {
    result->command_id = command_id;
    result->status = BLINK_STANDALONE_STATUS_OK;
    result->state = BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_STALE;
    return BLINK_STANDALONE_STATUS_OK;
  }
  return result->state == BLINK_STANDALONE_DEDICATED_THREAD_COMMAND_PENDING
             ? BLINK_STANDALONE_STATUS_PENDING
             : static_cast<blink_standalone_status_code_t>(result->status);
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
  InvalidatePreparedGpuSourceFrame(renderer);
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
  if (IsDedicatedThreadShell(renderer)) {
    if (!utf8_text) {
      return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                          "set_element_text failed: UTF-8 text is required");
    }
    std::string element_id_copy = element_id ? element_id : "";
    std::string text_copy = utf8_text;
    blink_standalone_renderer* inner = renderer->dedicated_thread_inner;
    if (!inner || element_id_copy.empty()) {
      return SetLastError(renderer, BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
                          "set_element_text failed: element id is required");
    }
    ClearLastError(renderer);
    DedicatedSequenceFor(renderer).PostAsync(
        [inner, element_id_copy = std::move(element_id_copy),
         text_copy = std::move(text_copy)]() mutable {
          ClearLastError(inner);
          QueueDomMutation(inner,
                           html_css_renderer::DomMutationType::kSetTextContent,
                           element_id_copy.c_str(), "", text_copy.c_str());
        });
    return BLINK_STANDALONE_STATUS_OK;
  }
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
  renderer->gpu_backdrop_frame_generation = 0;
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
  const blink_standalone_renderer* source = PublicMetadataRendererFor(renderer);
  return source ? source->latest_result.backdrop_filter_regions.size() : 0;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_backdrop_filter_region(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_backdrop_filter_region_t* out) {
  const blink_standalone_renderer* source = PublicMetadataRendererFor(renderer);
  if (!source || !out ||
      index >= source->latest_result.backdrop_filter_regions.size()) {
    return SetLastError(
        const_cast<blink_standalone_renderer_t*>(renderer),
        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "get_backdrop_filter_region failed: renderer, output pointer, and valid index are required");
  }
  CopyBackdropFilterRegion(source->latest_result.backdrop_filter_regions[index],
                           out);
  return BLINK_STANDALONE_STATUS_OK;
}

extern "C" BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_gpu_backdrop_effect_count(
    const blink_standalone_renderer_t* renderer) {
  const blink_standalone_renderer* source = PublicMetadataRendererFor(renderer);
  if (!source) {
    return 0;
  }
  return std::min(source->latest_result.backdrop_filter_regions.size(),
                  static_cast<size_t>(255u));
}

extern "C" BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_gpu_backdrop_effect(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_gpu_backdrop_effect_t* out) {
  const blink_standalone_renderer* source = PublicMetadataRendererFor(renderer);
  const size_t effect_count =
      blink_standalone_renderer_gpu_backdrop_effect_count(renderer);
  if (!source || !out || index >= effect_count) {
    return SetLastError(
        const_cast<blink_standalone_renderer_t*>(renderer),
        BLINK_STANDALONE_STATUS_INVALID_ARGUMENT,
        "get_gpu_backdrop_effect failed: renderer, output pointer, and valid index are required");
  }
  CopyGpuBackdropEffect(
      source->latest_result.backdrop_filter_regions[index],
      static_cast<uint32_t>(index + 1u),
      source->gpu_backdrop_frame_generation, out);
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
