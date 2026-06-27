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
} blink_standalone_status_code_t;

/* Raw frame bytes are currently RGBA8 or BGRA8. Inspect pixel_format and stride
 * before reading pixels; do not assume tightly packed rows. */
typedef enum blink_standalone_pixel_format {
  BLINK_STANDALONE_PIXEL_FORMAT_NONE = 0,
  BLINK_STANDALONE_PIXEL_FORMAT_RGBA8 = 1,
  BLINK_STANDALONE_PIXEL_FORMAT_BGRA8 = 2,
} blink_standalone_pixel_format_t;

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

typedef enum blink_standalone_backdrop_filter_flags {
  BLINK_STANDALONE_BACKDROP_FILTER_ROUNDED_RECT = 1u << 0,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_COMPLEX_CLIP = 1u << 1,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_TRANSFORM = 1u << 2,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_FILTER_OP = 1u << 3,
  BLINK_STANDALONE_BACKDROP_FILTER_UNSUPPORTED_MASK_OR_BLEND = 1u << 4,
} blink_standalone_backdrop_filter_flags_t;

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
 * metadata to blur their own framebuffer behind the raw HTML output. Bounds and
 * radii are logical CSS px. Unsupported flags mean the region exists but should
 * not be treated as an exact simple blur. */
typedef struct blink_standalone_backdrop_filter_region {
  blink_standalone_rect_t bounds;
  float blur_radius_css_px;
  float border_radius_top_left;
  float border_radius_top_right;
  float border_radius_bottom_right;
  float border_radius_bottom_left;
  float opacity;
  uint32_t flags;
  const char* element_id;
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
BLINK_STANDALONE_RENDERER_C_API int blink_standalone_renderer_needs_begin_frame(
    const blink_standalone_renderer_t* renderer);

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
