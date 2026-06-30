// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/renderer_c_api.h"

#include <cstdint>
#include <cstdio>
#include <cstring>

namespace {

bool Fail(const char* message) {
  std::fprintf(stderr, "static_raw_output_smoke: failed %s\n", message);
  return false;
}

bool IsExpectedColor(const uint8_t* pixel,
                     blink_standalone_pixel_format_t format,
                     uint8_t expected_r,
                     uint8_t expected_g,
                     uint8_t expected_b) {
  uint8_t r = 0;
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t a = 0;
  if (format == BLINK_STANDALONE_PIXEL_FORMAT_RGBA8) {
    r = pixel[0];
    g = pixel[1];
    b = pixel[2];
    a = pixel[3];
  } else if (format == BLINK_STANDALONE_PIXEL_FORMAT_BGRA8) {
    b = pixel[0];
    g = pixel[1];
    r = pixel[2];
    a = pixel[3];
  } else {
    return false;
  }
  return a > 200 && r == expected_r && g == expected_g && b == expected_b;
}

}  // namespace

int main() {
  blink_standalone_renderer_config_t config = {};
  config.width = 160;
  config.height = 120;
  config.device_scale_factor = 1.0f;
  config.no_script_profile = 1;

  blink_standalone_renderer_t* renderer = nullptr;
  blink_standalone_status_code_t status =
      blink_standalone_renderer_create(&config, &renderer);
  if (status != BLINK_STANDALONE_STATUS_OK || !renderer) {
    return Fail("create") ? 0 : 1;
  }

  const char* html =
      "<!doctype html><style>body{margin:0}.card{width:80px;height:60px;"
      "background:#2878d8;color:white}input{margin:4px}</style><div id='card' "
      "class='card' data-godot-action='open'>Card</div><label><input "
      "id='agree' type='checkbox' data-godot-action='toggle'>Agree</label>"
      "<input id='name' value='abc' data-godot-action='name'>";

  status = blink_standalone_renderer_set_document_html(renderer, html, "", "");
  if (status != BLINK_STANDALONE_STATUS_OK) {
    blink_standalone_renderer_destroy(renderer);
    return Fail("set_document_html") ? 0 : 1;
  }

  status = blink_standalone_renderer_advance_frame(renderer, 0.0);
  if (status != BLINK_STANDALONE_STATUS_OK) {
    blink_standalone_renderer_destroy(renderer);
    return Fail("advance_frame") ? 0 : 1;
  }

  blink_standalone_frame_output_t output = {};
  status = blink_standalone_renderer_get_latest_output(renderer, &output);
  if (status != BLINK_STANDALONE_STATUS_OK || !output.pixels) {
    blink_standalone_renderer_destroy(renderer);
    return Fail("get_latest_output") ? 0 : 1;
  }

  bool ok = true;
  if (output.width != 160 || output.height != 120) {
    ok = Fail("dimensions");
  }
  if (output.stride < output.width * 4) {
    ok = Fail("stride");
  }
  if (output.pixel_count < static_cast<size_t>(output.stride) * output.height) {
    ok = Fail("pixel_count");
  }
  if (output.dirty_rect_count == 0 || !output.dirty_rects) {
    ok = Fail("dirty_rects");
  }

  size_t blue_pixels = 0;
  size_t nonwhite_pixels = 0;
  size_t nontransparent_pixels = 0;
  for (int y = 0; y < output.height; ++y) {
    const uint8_t* row = output.pixels + static_cast<size_t>(y) * output.stride;
    for (int x = 0; x < output.width; ++x) {
      const uint8_t* pixel = row + x * 4;
      uint8_t r = output.pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_BGRA8
                      ? pixel[2]
                      : pixel[0];
      uint8_t g = pixel[1];
      uint8_t b = output.pixel_format == BLINK_STANDALONE_PIXEL_FORMAT_BGRA8
                      ? pixel[0]
                      : pixel[2];
      uint8_t a = pixel[3];
      if (a != 0) {
        ++nontransparent_pixels;
      }
      if (!(r > 245 && g > 245 && b > 245 && a > 245)) {
        ++nonwhite_pixels;
      }
      if (IsExpectedColor(pixel, output.pixel_format, 0x28, 0x78, 0xd8)) {
        ++blue_pixels;
      }
    }
  }
  if (blue_pixels < 3500) {
    ok = Fail("expected_color_pixels");
  }
  if (nonwhite_pixels < 3500 || nontransparent_pixels < 3500) {
    ok = Fail("pixel_coverage");
  }

  const size_t hit_count = blink_standalone_renderer_hit_metadata_count(renderer);
  if (hit_count == 0) {
    ok = Fail("hit_count");
  }

  bool saw_card = false;
  bool saw_checkbox = false;
  bool saw_input = false;
  blink_standalone_rect_t card_bounds = {};
  for (size_t i = 0; i < hit_count; ++i) {
    blink_standalone_hit_metadata_t hit = {};
    if (blink_standalone_renderer_get_hit_metadata(renderer, i, &hit) !=
        BLINK_STANDALONE_STATUS_OK) {
      continue;
    }
    if (hit.element_id && std::strcmp(hit.element_id, "card") == 0 &&
        hit.tag_name && std::strcmp(hit.tag_name, "div") == 0 &&
        hit.data_godot_action &&
        std::strcmp(hit.data_godot_action, "open") == 0 &&
        hit.bounds.width > 0.0f && hit.bounds.height > 0.0f) {
      saw_card = true;
      card_bounds = hit.bounds;
    }
    if (hit.element_id && std::strcmp(hit.element_id, "agree") == 0 &&
        hit.tag_name && std::strcmp(hit.tag_name, "input") == 0 &&
        hit.data_godot_action &&
        std::strcmp(hit.data_godot_action, "toggle") == 0 &&
        !hit.disabled && !hit.checked) {
      saw_checkbox = true;
    }
    if (hit.element_id && std::strcmp(hit.element_id, "name") == 0 &&
        hit.tag_name && std::strcmp(hit.tag_name, "input") == 0 &&
        hit.data_godot_action &&
        std::strcmp(hit.data_godot_action, "name") == 0 && hit.editable &&
        !hit.focused && hit.bounds.width > 0.0f && hit.bounds.height > 0.0f) {
      saw_input = true;
    }
  }

  blink_standalone_hit_metadata_t point_hit = {};
  if (saw_card) {
    status = blink_standalone_renderer_hit_test(
        renderer, card_bounds.x + card_bounds.width * 0.5f,
        card_bounds.y + card_bounds.height * 0.5f, &point_hit);
    if (status != BLINK_STANDALONE_STATUS_OK || !point_hit.element_id ||
        std::strcmp(point_hit.element_id, "card") != 0) {
      saw_card = false;
    }
  }
  if (!saw_card || !saw_checkbox || !saw_input) {
    ok = Fail("hit_metadata");
  }

  blink_standalone_renderer_release_latest_output(renderer);
  blink_standalone_renderer_destroy(renderer);

  if (!ok) {
    return 1;
  }
  std::printf(
      "static_raw_output_smoke: ok raw=%dx%d stride=%d bytes=%zu dirty=%zu "
      "hits=%zu blue2878d8=%zu nonwhite=%zu nontransparent=%zu\n",
      output.width, output.height, output.stride, output.pixel_count,
      output.dirty_rect_count, hit_count, blue_pixels, nonwhite_pixels,
      nontransparent_pixels);
  return 0;
}
