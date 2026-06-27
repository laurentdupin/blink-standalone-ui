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

typedef enum blink_standalone_status_code {
  BLINK_STANDALONE_STATUS_OK = 0,
  BLINK_STANDALONE_STATUS_INVALID_ARGUMENT = 1,
  BLINK_STANDALONE_STATUS_INITIALIZATION_FAILED = 2,
  BLINK_STANDALONE_STATUS_RENDER_FAILED = 3,
  BLINK_STANDALONE_STATUS_NO_SCRIPT_REJECTED = 4,
} blink_standalone_status_code_t;

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

typedef struct blink_standalone_rect {
  float x;
  float y;
  float width;
  float height;
} blink_standalone_rect_t;

typedef struct blink_standalone_renderer_config {
  int width;
  int height;
  float device_scale_factor;
  int no_script_profile;
} blink_standalone_renderer_config_t;

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
/* Queue no-JS Blink DOM mutations for the next advance_frame call. These
 * mutate the current live document through Blink DOM APIs and do not reload the
 * document. The no-script profile rejects inline event handlers and
 * javascript: URL surfaces. */
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

BLINK_STANDALONE_RENDERER_C_API const char* blink_standalone_renderer_last_error(
    const blink_standalone_renderer_t* renderer);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_
