// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_

#include <stddef.h>
#include <stdint.h>

#if defined(_WIN32)
#define HCSR_C_API __declspec(dllexport)
#else
#define HCSR_C_API
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hcsr_renderer hcsr_renderer_t;

typedef enum hcsr_status_code {
  HCSR_STATUS_OK = 0,
  HCSR_STATUS_INVALID_ARGUMENT = 1,
  HCSR_STATUS_INITIALIZATION_FAILED = 2,
  HCSR_STATUS_RENDER_FAILED = 3,
  HCSR_STATUS_NO_SCRIPT_REJECTED = 4,
} hcsr_status_code_t;

typedef enum hcsr_pixel_format {
  HCSR_PIXEL_FORMAT_NONE = 0,
  HCSR_PIXEL_FORMAT_RGBA8 = 1,
  HCSR_PIXEL_FORMAT_BGRA8 = 2,
} hcsr_pixel_format_t;

typedef struct hcsr_rect {
  float x;
  float y;
  float width;
  float height;
} hcsr_rect_t;

typedef struct hcsr_renderer_config {
  int width;
  int height;
  float device_scale_factor;
  int no_script_profile;
} hcsr_renderer_config_t;

typedef struct hcsr_frame_output {
  const uint8_t* pixels;
  size_t pixel_count;
  int width;
  int height;
  int stride;
  hcsr_pixel_format_t pixel_format;
  int premultiplied_alpha;
  const hcsr_rect_t* dirty_rects;
  size_t dirty_rect_count;
} hcsr_frame_output_t;

typedef struct hcsr_hit_metadata {
  const char* element_id;
  const char* tag_name;
  const char* data_godot_action;
  hcsr_rect_t bounds;
  int disabled;
  int editable;
  int checked;
  int focused;
} hcsr_hit_metadata_t;

HCSR_C_API hcsr_status_code_t hcsr_renderer_create(
    const hcsr_renderer_config_t* config,
    hcsr_renderer_t** renderer_out);
HCSR_C_API void hcsr_renderer_destroy(hcsr_renderer_t* renderer);

HCSR_C_API hcsr_status_code_t hcsr_renderer_set_document_html(
    hcsr_renderer_t* renderer,
    const char* html,
    const char* resource_root,
    const char* resource_base_path);
HCSR_C_API hcsr_status_code_t hcsr_renderer_set_viewport(
    hcsr_renderer_t* renderer,
    int width,
    int height,
    float device_scale_factor);
HCSR_C_API hcsr_status_code_t hcsr_renderer_advance_frame(
    hcsr_renderer_t* renderer,
    double timeline_time_seconds);

HCSR_C_API hcsr_status_code_t hcsr_renderer_get_latest_output(
    hcsr_renderer_t* renderer,
    hcsr_frame_output_t* output);
HCSR_C_API void hcsr_renderer_release_latest_output(hcsr_renderer_t* renderer);

HCSR_C_API size_t hcsr_renderer_hit_metadata_count(
    const hcsr_renderer_t* renderer);
HCSR_C_API hcsr_status_code_t hcsr_renderer_get_hit_metadata(
    const hcsr_renderer_t* renderer,
    size_t index,
    hcsr_hit_metadata_t* hit);

HCSR_C_API const char* hcsr_renderer_last_error(
    const hcsr_renderer_t* renderer);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_C_API_H_
