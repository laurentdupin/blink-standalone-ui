// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32) && defined(BLINK_STANDALONE_RENDERER_C_API_STATIC)
#define BLINK_STANDALONE_RENDERER_C_API
#elif defined(_WIN32) && defined(BLINK_STANDALONE_RENDERER_C_API_IMPLEMENTATION)
#define BLINK_STANDALONE_RENDERER_C_API __declspec(dllexport)
#elif defined(_WIN32)
#define BLINK_STANDALONE_RENDERER_C_API __declspec(dllimport)
#else
#define BLINK_STANDALONE_RENDERER_C_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct blink_standalone_renderer blink_standalone_renderer_t;

/* Public status values returned by the embeddable C API. Calls with a null
 * renderer cannot store renderer-local diagnostics; use the return code. */
typedef enum blink_standalone_status_code {
  BLINK_STANDALONE_STATUS_OK = 0,
  BLINK_STANDALONE_STATUS_INVALID_ARGUMENT = 1,
  BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED = 2,
  BLINK_STANDALONE_STATUS_RENDER_FAILED = 3,
  BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED = 4,
  BLINK_STANDALONE_STATUS_UNSUPPORTED = 5,
  BLINK_STANDALONE_STATUS_PENDING = 6,
} blink_standalone_status_code_t;

/* Raw frame bytes are currently RGBA8 or BGRA8. Inspect pixel_format and stride
 * before reading pixels; do not assume tightly packed rows. */
typedef enum blink_standalone_pixel_format {
  BLINK_STANDALONE_PIXEL_FORMAT_NONE = 0,
  BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 = 1,
  BLINK_STANDALONE_PIXEL_FORMAT_BGRA8 = 2,
} blink_standalone_pixel_format_t;

typedef enum blink_standalone_gpu_backend {
  BLINK_STANDALONE_GPU_BACKEND_NONE = 0,
  BLINK_STANDALONE_GPU_BACKEND_CPU_RAW = 1,
  BLINK_STANDALONE_GPU_BACKEND_VULKAN = 2,
  BLINK_STANDALONE_GPU_BACKEND_D3D12 = 3,
} blink_standalone_gpu_backend_t;

typedef enum blink_standalone_gpu_capability_flags {
  BLINK_STANDALONE_GPU_CAPABILITY_AVAILABLE = 1u << 0,
  BLINK_STANDALONE_GPU_CAPABILITY_EXTERNAL_TARGET = 1u << 1,
  BLINK_STANDALONE_GPU_CAPABILITY_INTERNAL_TEST_STANDIN = 1u << 2,
} blink_standalone_gpu_capability_flags_t;

typedef enum blink_standalone_gpu_target_flags {
  /* Test-only stand-in target allocated by the standalone renderer on its
   * active GPU device. This exercises the public C ABI and target-writer path
   * without requiring an embedder-created native texture. Production embedders
   * should pass real backend handles instead. */
  BLINK_STANDALONE_GPU_TARGET_INTERNAL_TEST_STANDIN = 1u << 0,
} blink_standalone_gpu_target_flags_t;

typedef enum blink_standalone_alpha_mode {
  BLINK_STANDALONE_ALPHA_MODE_PREMULTIPLIED = 0,
  BLINK_STANDALONE_ALPHA_MODE_STRAIGHT = 1,
} blink_standalone_alpha_mode_t;

typedef enum blink_standalone_color_space {
  BLINK_STANDALONE_COLOR_SPACE_SRGB = 0,
  BLINK_STANDALONE_COLOR_SPACE_UNKNOWN = 1,
} blink_standalone_color_space_t;

typedef enum blink_standalone_mouse_button {
  BLINK_STANDALONE_MOUSE_BUTTON_NONE = 0,
  BLINK_STANDALONE_MOUSE_BUTTON_LEFT = 1,
  BLINK_STANDALONE_MOUSE_BUTTON_MIDDLE = 2,
  BLINK_STANDALONE_MOUSE_BUTTON_RIGHT = 3,
} blink_standalone_mouse_button_t;

typedef enum blink_standalone_key {
  BLINK_STANDALONE_KEY_UNKNOWN = 0,
  BLINK_STANDALONE_KEY_BACKSPACE = 8,
  BLINK_STANDALONE_KEY_TAB = 9,
  BLINK_STANDALONE_KEY_ENTER = 13,
  BLINK_STANDALONE_KEY_DELETE = 46,
} blink_standalone_key_t;

typedef enum blink_standalone_insert_position {
  BLINK_STANDALONE_INSERT_BEFORE_BEGIN = 0,
  BLINK_STANDALONE_INSERT_AFTER_BEGIN = 1,
  BLINK_STANDALONE_INSERT_BEFORE_END = 2,
  BLINK_STANDALONE_INSERT_AFTER_END = 3,
} blink_standalone_insert_position_t;

typedef enum blink_standalone_resource_type_hint {
  BLINK_STANDALONE_RESOURCE_TYPE_UNKNOWN = 0,
  BLINK_STANDALONE_RESOURCE_TYPE_IMAGE = 1,
  BLINK_STANDALONE_RESOURCE_TYPE_STYLESHEET = 2,
  BLINK_STANDALONE_RESOURCE_TYPE_FONT = 3,
  BLINK_STANDALONE_RESOURCE_TYPE_MEDIA = 4,
} blink_standalone_resource_type_hint_t;

typedef enum blink_standalone_resource_initiator {
  BLINK_STANDALONE_RESOURCE_INITIATOR_OTHER = 0,
  BLINK_STANDALONE_RESOURCE_INITIATOR_IMG_ELEMENT = 1,
  BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_BACKGROUND_IMAGE = 2,
  BLINK_STANDALONE_RESOURCE_INITIATOR_STYLESHEET_LINK = 3,
  BLINK_STANDALONE_RESOURCE_INITIATOR_CSS_IMPORT = 4,
  BLINK_STANDALONE_RESOURCE_INITIATOR_FONT_FACE = 5,
  BLINK_STANDALONE_RESOURCE_INITIATOR_MEDIA = 6,
} blink_standalone_resource_initiator_t;

typedef enum blink_standalone_resource_status {
  BLINK_STANDALONE_RESOURCE_STATUS_OK = 0,
  BLINK_STANDALONE_RESOURCE_STATUS_NOT_FOUND = 1,
  BLINK_STANDALONE_RESOURCE_STATUS_BLOCKED = 2,
  BLINK_STANDALONE_RESOURCE_STATUS_UNSUPPORTED_SCHEME = 3,
  BLINK_STANDALONE_RESOURCE_STATUS_UNSUPPORTED_MIME = 4,
  BLINK_STANDALONE_RESOURCE_STATUS_ERROR = 5,
} blink_standalone_resource_status_t;

typedef enum blink_standalone_resource_provider_flags {
  BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_FILE_FALLBACK = 1u << 0,
  BLINK_STANDALONE_RESOURCE_PROVIDER_DISABLE_NETWORK = 1u << 1,
  BLINK_STANDALONE_RESOURCE_PROVIDER_CALLBACK_FOR_DATA_URLS = 1u << 2,
  BLINK_STANDALONE_RESOURCE_PROVIDER_REQUIRE_PROVIDER_FOR_EXTERNAL = 1u << 3,
} blink_standalone_resource_provider_flags_t;

typedef struct blink_standalone_resource_request {
  const char* url;
  const char* document_url;
  const char* base_url;
  uint32_t type_hint;
  uint32_t initiator;
  const char* accepted_mime_types;
} blink_standalone_resource_request_t;

typedef struct blink_standalone_resource_response {
  uint32_t status;
  const char* mime_type;
  const uint8_t* bytes;
  size_t byte_count;
  const char* resolved_url_or_cache_key;
} blink_standalone_resource_response_t;

typedef blink_standalone_resource_status_t (
    *blink_standalone_load_resource_callback)(
    void* user_data,
    const blink_standalone_resource_request_t* request,
    blink_standalone_resource_response_t* response);

typedef void (*blink_standalone_release_resource_callback)(
    void* user_data,
    blink_standalone_resource_response_t* response);

typedef enum blink_standalone_backdrop_filter_flags {
  BLINK_STANDALONE_BACKDROP_FILTER_ROUNDED_RECT = 1u << 0,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_COMPLEX_CLIP = 1u << 1,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_TRANSFORM = 1u << 2,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_FILTER_OP = 1u << 3,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_MASK_OR_BLEND = 1u << 4,
} blink_standalone_backdrop_filter_flags_t;

typedef enum blink_standalone_backdrop_filter_op_type {
  BLINK_STANDALONE_BACKDROP_FILTER_OP_BLUR = 0,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_BRIGHTNESS = 1,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_CONTRAST = 2,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_SATURATE = 3,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_GRAYSCALE = 4,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_SEPIA = 5,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_INVERT = 6,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_HUE_ROTATE = 7,
  BLINK_STANDALONE_BACKDROP_FILTER_OP_OPACITY = 8,
} blink_standalone_backdrop_filter_op_type_t;

#define BLINK_STANDALONE_MAX_BACKDROP_FILTER_OPS 8

typedef struct blink_standalone_backdrop_filter_op {
  uint32_t type;
  /* CSS px for blur, degrees for hue-rotate, multipliers for brightness,
   * contrast, and saturate, and normalized fractions for grayscale, sepia,
   * invert, and opacity. */
  float amount;
} blink_standalone_backdrop_filter_op_t;

/* Rects and input coordinates are in logical CSS/view coordinates unless they
 * describe raw frame output dimensions. */
typedef struct blink_standalone_rect {
  float x;
  float y;
  float width;
  float height;
} blink_standalone_rect_t;

typedef struct blink_standalone_renderer_config {
  /* Logical CSS viewport size. device_scale_factor controls physical raw output
   * size, e.g. 256x128 at 2.0 produces a 512x256 raw frame. */
  int width;
  int height;
  float device_scale_factor;
  /* Non-zero enables the public no-script profile: JavaScript, inline event
   * handlers, javascript: URLs, and executable embedded surfaces are rejected or
   * made inert at the C API boundary. */
  int no_script_profile;
} blink_standalone_renderer_config_t;

typedef struct blink_standalone_gpu_target_common {
  uint32_t backend;
  uint32_t flags;
  uint32_t logical_width;
  uint32_t logical_height;
  uint32_t physical_width;
  uint32_t physical_height;
  float device_scale_factor;
  uint32_t pixel_format;
  uint32_t alpha_mode;
  uint32_t color_space;
  uint64_t generation;
} blink_standalone_gpu_target_common_t;

typedef struct blink_standalone_vulkan_external_target {
  /* Raw VkImage owned by the embedder. The renderer must already have been
   * configured with blink_standalone_renderer_configure_vulkan_external_device
   * for the same VkDevice/queue domain. */
  void* vk_image;
  /* Optional duplicate of the configured device/physical-device handles for
   * caller diagnostics. The current same-device writer validates against the
   * configured renderer device and uses vk_image/vk_device_memory metadata. */
  void* vk_device;
  void* vk_physical_device;
  /* Required today: Skia/Vulkan wrapping needs allocation metadata for the
   * borrowed image. Blink never frees this memory. allocation_offset must be
   * zero in the current same-device path and allocation_size must be non-zero. */
  void* vk_device_memory;
  /* Reserved for future cross-device external-memory import; ignored by the
   * current same-device path. */
  void* shared_memory_handle;
  uint32_t vk_format;
  uint32_t width;
  uint32_t height;
  /* Reserved for explicit layout ownership. The current implementation writes
   * synchronously and leaves the validated target usable as
   * VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL. */
  uint32_t current_layout;
  uint32_t required_final_layout;
  uint32_t queue_family_index;
  /* allocation_offset is reserved and currently expected to be zero. */
  uint64_t allocation_offset;
  uint64_t allocation_size;
  uint32_t memory_type_index;
  uint32_t image_tiling;
  /* Must include COLOR_ATTACHMENT, SAMPLED, and TRANSFER_DST usage bits for the
   * current Viz blit request path. TRANSFER_SRC is only needed by callers that
   * read the image back themselves for diagnostics. */
  uint32_t image_usage_flags;
  /* Current path supports single-sample, single-level 2D targets. Zero is
   * accepted for backward compatibility and treated as unspecified; embedders
   * should pass sample_count=1 and level_count=1. */
  uint32_t sample_count;
  uint32_t level_count;
  uint32_t sharing_mode;
  uint32_t external_memory_handle_type;
  /* Reserved for explicit async synchronization. The current implementation is
   * synchronous for validated smokes and does not consume or signal these. */
  void* wait_semaphore;
  uint64_t wait_value;
  void* signal_semaphore;
  uint64_t signal_value;
} blink_standalone_vulkan_external_target_t;

typedef struct blink_standalone_vulkan_external_device {
  /* Raw Vulkan handles borrowed from the embedder. Call once after renderer
   * creation and before document/frame use. Blink wraps these handles in
   * non-owning Chromium Vulkan objects and never destroys the VkDevice/queue. */
  void* vk_instance;
  void* vk_physical_device;
  void* vk_device;
  void* vk_queue;
  uint32_t queue_family_index;
  uint32_t api_version;
  const char* const* enabled_instance_extensions;
  size_t enabled_instance_extension_count;
  const char* const* enabled_device_extensions;
  size_t enabled_device_extension_count;
} blink_standalone_vulkan_external_device_t;

typedef struct blink_standalone_d3d12_external_target {
  /* Raw ID3D12Resource* is reserved for a future same-device D3D12 setup API.
   * The public D3D12 path currently requires shared_handle. Call
   * blink_standalone_renderer_configure_d3d12_external_device before document
   * use when the shared handle comes from an embedder-owned D3D12 device so
   * Blink can choose the matching adapter before creating its Dawn device. */
  void* d3d12_device;
  void* d3d12_command_queue;
  void* d3d12_resource;
  /* Required today for external D3D12 targets. The renderer opens the handle
   * during render_to_gpu_target and does not retain it after the synchronous
   * call returns. */
  void* shared_handle;
  uint32_t dxgi_format;
  uint32_t width;
  uint32_t height;
  /* Reserved for explicit resource-state ownership. The current validated path
   * is synchronous and suitable for caller-side readback/sampling after return
   * when the target resource was created with simultaneous access/shared usage. */
  uint32_t current_state;
  uint32_t required_final_state;
  /* Reserved for explicit async synchronization. The current implementation is
   * synchronous for validated smokes and does not consume or signal these. */
  void* wait_fence;
  uint64_t wait_value;
  void* signal_fence;
  uint64_t signal_value;
} blink_standalone_d3d12_external_target_t;

typedef struct blink_standalone_d3d12_external_device {
  /* Optional borrowed ID3D12Device*. */
  void* d3d12_device;
  /* Optional borrowed ID3D12CommandQueue*. Reserved for future same-device
   * Dawn setup; the current implementation uses the adapter LUID only. */
  void* d3d12_command_queue;
  /* Optional explicit DXGI adapter LUID. If both fields are zero, Blink derives
   * the LUID from d3d12_device via ID3D12Device::GetAdapterLuid(). */
  uint32_t adapter_luid_low;
  int32_t adapter_luid_high;
  uint32_t node_mask;
} blink_standalone_d3d12_external_device_t;

/* Explicit GPU output target. CPU raw output remains the default path and is
 * requested only through advance_frame/get_latest_output. render_to_gpu_target
 * never silently falls back to CPU output: unsupported backends, missing native
 * handles, or invalid synchronization metadata return a non-OK status. Native
 * objects are always borrowed; Blink never destroys embedder-owned
 * device/queue/resource/image/sync handles. */
typedef struct blink_standalone_external_gpu_target {
  blink_standalone_gpu_target_common_t common;
  blink_standalone_vulkan_external_target_t vulkan;
  blink_standalone_d3d12_external_target_t d3d12;
} blink_standalone_external_gpu_target_t;

typedef struct blink_standalone_gpu_render_result {
  uint32_t backend;
  uint32_t status;
  uint32_t target_written;
  uint32_t width;
  uint32_t height;
  uint32_t pixel_format;
  uint32_t dirty_rect_count;
  uint64_t generation;
} blink_standalone_gpu_render_result_t;

typedef struct blink_standalone_update_result {
  uint32_t status;
  uint32_t frame_advanced;
  uint32_t frame_skipped_due_to_no_demand;
  uint32_t needs_output;
  uint32_t needs_begin_frame;
  uint32_t full_frame_damage;
  uint32_t damage_rect_count;
} blink_standalone_update_result_t;

/* Pointers returned in this struct are owned by the renderer and are valid
 * until the next output release, renderer mutation, frame advance, or destroy.
 * Call release_latest_output when the embedder has finished reading pixels. */
typedef struct blink_standalone_frame_output {
  const uint8_t* pixels;
  size_t pixel_count;
  int width;
  int height;
  int stride;
  blink_standalone_pixel_format_t pixel_format;
  int premultiplied_alpha;
  const blink_standalone_rect_t* dirty_rects;
  size_t dirty_rect_count;
} blink_standalone_frame_output_t;

/* Hit metadata is collected from the latest frame. String pointers are
 * renderer-owned and valid until the next renderer operation that replaces
 * frame metadata. bounds are logical CSS/view coordinates. */
typedef struct blink_standalone_hit_metadata {
  const char* element_id;
  const char* tag_name;
  const char* data_godot_action;
  blink_standalone_rect_t bounds;
  int disabled;
  int editable;
  int checked;
  int focused;
} blink_standalone_hit_metadata_t;

/* Form control state is collected from real Blink form controls in the latest
 * frame. value is the current value for inputs, textareas, sliders/ranges and
 * single-selects; multi-selects expose all selected option values through the
 * explicit selected-value accessors below. */
typedef struct blink_standalone_form_control_state {
  const char* element_id;
  const char* tag_name;
  const char* value;
  int checked;
  int focused;
  int selection_offsets_present;
  unsigned selection_start;
  unsigned selection_end;
  const char* type;
  const char* min;
  const char* max;
  const char* step;
} blink_standalone_form_control_state_t;

/* Backdrop-filter metadata describes regions Blink would sample behind the HTML
 * surface. Blink does not sample host-scene pixels; embedders can use this
 * metadata to apply ordered operations to their own framebuffer behind the raw
 * HTML output. Bounds and radii are logical CSS px. Unsupported flags mean the
 * region exists but should not be treated as an exact supported operation chain.
 */
typedef struct blink_standalone_backdrop_filter_region {
  blink_standalone_rect_t bounds;
  /* Compatibility shortcut for the largest blur() operation in filter_ops. */
  float blur_radius_css_px;
  float border_radius_top_left;
  float border_radius_top_right;
  float border_radius_bottom_right;
  float border_radius_bottom_left;
  float opacity;
  uint32_t flags;
  const char* element_id;
  uint32_t filter_op_count;
  blink_standalone_backdrop_filter_op_t filter_ops[BLINK_STANDALONE_MAX_BACKDROP_FILTER_OPS];
} blink_standalone_backdrop_filter_region_t;

BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_create(
    const blink_standalone_renderer_config_t* config,
    blink_standalone_renderer_t** renderer_out);
BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_destroy(blink_standalone_renderer_t* renderer);

BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_document_html(
    blink_standalone_renderer_t* renderer,
    const char* html,
    const char* resource_root,
    const char* resource_base_path);
/* Optional per-renderer resource provider. When provider-required/file-fallback
 * flags are set, non-data external resources are loaded only through this
 * callback and missing/blocked resources fail recoverably. Response bytes and
 * strings are copied before the release callback is invoked. */
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_resource_provider(
    blink_standalone_renderer_t* renderer,
    blink_standalone_load_resource_callback load,
    blink_standalone_release_resource_callback release,
    void* user_data,
    uint32_t flags);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_viewport(
    blink_standalone_renderer_t* renderer,
    int width,
    int height,
    float device_scale_factor);
/* Advance applies queued input and mutations, runs Blink lifecycle/compositor
 * work, and makes a latest raw output/metadata snapshot available. */
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_advance_frame(
    blink_standalone_renderer_t* renderer,
    double timeline_time_seconds);
/* Applies queued input/mutations/timeline without requesting raw pixels or a
 * GPU target write. Embedders should call this once per host frame while input
 * or animation work is pending, then call advance_frame/render_to_gpu_target
 * only if needs_output is non-zero or an explicit/manual render is required. */
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_update(
    blink_standalone_renderer_t* renderer,
    double timeline_time_seconds,
    blink_standalone_update_result_t* result);
BLINK_STANDALONE_RENDERER_C_API int blink_standalone_renderer_needs_begin_frame(
    const blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API uint32_t blink_standalone_renderer_gpu_backend_capabilities(
    const blink_standalone_renderer_t* renderer,
    uint32_t backend);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_configure_vulkan_external_device(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_vulkan_external_device_t* device);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_configure_d3d12_external_device(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_d3d12_external_device_t* device);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_render_to_gpu_target(
    blink_standalone_renderer_t* renderer,
    const blink_standalone_external_gpu_target_t* target,
    blink_standalone_gpu_render_result_t* result);

BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_mouse_move(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    int modifiers);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_mouse_down(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    blink_standalone_mouse_button_t button,
    int modifiers,
    int click_count);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_mouse_up(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    blink_standalone_mouse_button_t button,
    int modifiers,
    int click_count);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_wheel(
    blink_standalone_renderer_t* renderer,
    float x,
    float y,
    float delta_x,
    float delta_y);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_key_down(
    blink_standalone_renderer_t* renderer,
    blink_standalone_key_t key,
    int modifiers);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_key_up(
    blink_standalone_renderer_t* renderer,
    blink_standalone_key_t key,
    int modifiers);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_text_input(
    blink_standalone_renderer_t* renderer,
    const char* utf8_text);
/* Queue no-JS Blink DOM/form/style mutations for the next advance_frame call.
 * These mutate the current live document through Blink APIs and do not reload
 * the document. State outside the mutated/replaced subtree is preserved when
 * Blink preserves it. The no-script profile rejects script tags, inline event
 * handlers, javascript: URL surfaces, and executable embedded surfaces. */
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_text(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* utf8_text);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_inner_html(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* html_fragment);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_body_inner_html(
    blink_standalone_renderer_t* renderer,
    const char* html_fragment);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_insert_element_html(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    blink_standalone_insert_position_t position,
    const char* html_fragment);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_remove_element(
    blink_standalone_renderer_t* renderer,
    const char* element_id);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_attribute(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* attribute_name,
    const char* attribute_value);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_remove_element_attribute(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* attribute_name);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_element_style(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* style_attribute_value);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_replace_stylesheet_text(
    blink_standalone_renderer_t* renderer,
    const char* style_element_id,
    const char* css_text);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_form_control_value(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* value);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_form_control_checked(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    int checked);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_focus_element(
    blink_standalone_renderer_t* renderer,
    const char* element_id);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_blur_focused_element(
    blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_text_selection(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    unsigned start,
    unsigned end);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_reset_state(
    blink_standalone_renderer_t* renderer);

BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_latest_output(
    blink_standalone_renderer_t* renderer,
    blink_standalone_frame_output_t* output);
BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_release_latest_output(blink_standalone_renderer_t* renderer);

/* Metadata and form-state accessors read the latest frame snapshot. String
 * lifetimes match the latest renderer-owned metadata snapshot. */
BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_hit_metadata_count(
    const blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_hit_metadata(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_hit_metadata_t* hit);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_hit_test(
    const blink_standalone_renderer_t* renderer,
    float x,
    float y,
    blink_standalone_hit_metadata_t* hit);
BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_form_control_state_count(
    const blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_form_control_state(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_form_control_state_t* state);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_form_control_state_by_id(
    const blink_standalone_renderer_t* renderer,
    const char* element_id,
    blink_standalone_form_control_state_t* state);
BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_form_control_selected_value_count(
    const blink_standalone_renderer_t* renderer,
    const char* element_id);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_form_control_selected_value(
    const blink_standalone_renderer_t* renderer,
    const char* element_id,
    size_t index,
    const char** value_out);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_set_form_control_selected_values(
    blink_standalone_renderer_t* renderer,
    const char* element_id,
    const char* const* values,
    size_t value_count);
BLINK_STANDALONE_RENDERER_C_API size_t blink_standalone_renderer_backdrop_filter_region_count(
    const blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_backdrop_filter_region(
    const blink_standalone_renderer_t* renderer,
    size_t index,
    blink_standalone_backdrop_filter_region_t* out);

/* Renderer-local diagnostics describe the last API failure. Successful
 * renderer operations clear stale diagnostics. get_last_error_message and
 * last_error return renderer-owned strings valid until the next renderer
 * operation that replaces diagnostics, or destroy. */
BLINK_STANDALONE_RENDERER_C_API blink_standalone_status_code_t blink_standalone_renderer_get_last_error_code(
    const blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API const char* blink_standalone_renderer_get_last_error_message(
    const blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API void blink_standalone_renderer_clear_last_error(
    blink_standalone_renderer_t* renderer);
BLINK_STANDALONE_RENDERER_C_API const char* blink_standalone_renderer_last_error(
    const blink_standalone_renderer_t* renderer);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_
