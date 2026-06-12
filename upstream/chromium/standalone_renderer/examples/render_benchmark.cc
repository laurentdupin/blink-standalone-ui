#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#if defined(_WIN32)
#define NOMINMAX
#include <windows.h>
#include <dbghelp.h>
#include <crtdbg.h>
#pragma comment(lib, "Dbghelp.lib")
#endif

#include "html_css_renderer/blink_adapter.h"
#include "html_css_renderer/cpu_renderer.h"
#include "html_css_renderer/css_file_loader.h"
#include "html_css_renderer/draw_command_serializer.h"
#include "html_css_renderer/renderer.h"
#include "html_css_renderer/standalone_resource_provider.h"

#if !defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
#error "blink_standalone_render_benchmark_skia requires Skia CPU rendering."
#endif
#include "html_css_renderer/skia_cpu_renderer.h"

namespace {

namespace fs = std::filesystem;

class BenchmarkAssets final : public html_css_renderer::AssetProvider {
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

struct Metrics {
  int width = 0;
  int height = 0;
  size_t pixel_count = 0;
  size_t non_white_pixels = 0;
  size_t unique_color_sample = 0;
  int content_left = 0;
  int content_top = 0;
  int content_right = 0;
  int content_bottom = 0;
};

struct BenchmarkTimingDiagnostics {
  double process_elapsed_ms = 0.0;
  double input_setup_ms = 0.0;
  double blink_embedder_create_ms = 0.0;
  double blink_initialize_ms = 0.0;
  double advance_and_render_ms = 0.0;
  double cpu_raster_replay_ms = 0.0;
  double output_image_write_ms = 0.0;
  double metrics_json_write_ms = 0.0;
  double audit_json_write_ms = 0.0;
  double page_setup_json_write_ms = 0.0;
  double oracle_advance_and_render_ms = 0.0;
  double oracle_cpu_raster_replay_ms = 0.0;
  double oracle_output_write_ms = 0.0;
  int measured_frame_count = 0;
  int measured_no_change_fast_path_count = 0;
  int measured_paint_artifact_translation_count = 0;
  int measured_lifecycle_count = 0;
  uint64_t raster_pixels_touched = 0;
  uint64_t damage_pixels = 0;
  uint64_t raw_damage_area = 0;
  uint64_t coalesced_damage_area = 0;
  uint64_t command_replay_count_before_grouping = 0;
  uint64_t command_replay_count_after_grouping = 0;
  size_t damage_clip_count = 0;
  size_t replay_group_count = 0;
  double damage_grouping_ms = 0.0;
  double skregion_clip_ms = 0.0;
  double cpu_replay_ms = 0.0;
  double copyback_ms = 0.0;
  bool partial_raster = false;
  bool used_blink = false;
  bool used_skia_cpu = false;
  bool cold_process = true;
  bool cpu_raster_replay_skipped = false;
};

using BenchmarkClock = std::chrono::steady_clock;

double ElapsedMs(BenchmarkClock::time_point start,
                 BenchmarkClock::time_point end) {
  return std::chrono::duration<double, std::milli>(end - start).count();
}

void AccumulateMeasuredFrameWork(
    BenchmarkTimingDiagnostics& timing,
    const html_css_renderer::RenderResult& result) {
  ++timing.measured_frame_count;
  if (result.frame_work.no_change_fast_path) {
    ++timing.measured_no_change_fast_path_count;
  }
  timing.measured_paint_artifact_translation_count +=
      result.frame_work.paint_artifact_translation_count;
  timing.measured_lifecycle_count += result.frame_work.style_update_count +
                                     result.frame_work.layout_count +
                                     result.frame_work.prepaint_count +
                                     result.frame_work.paint_count;
}

std::vector<uint8_t> ReadBinaryFile(const std::string& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return {};
  }
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>());
}

std::optional<std::string> ReadTextFile(const std::string& path) {
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

bool ParseFloat(const std::string& value, float* output) {
  char* end = nullptr;
  const float parsed = std::strtof(value.c_str(), &end);
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

bool ParsePoint(const std::string& value, html_css_renderer::Point* output) {
  const size_t separator = value.find(',');
  if (separator == std::string::npos) {
    return false;
  }
  float x = 0.0f;
  float y = 0.0f;
  if (!ParseFloat(value.substr(0, separator), &x) ||
      !ParseFloat(value.substr(separator + 1), &y)) {
    return false;
  }
  output->x = x;
  output->y = y;
  return true;
}

bool ParseWheelInput(const std::string& value,
                     html_css_renderer::WheelInput* output) {
  const size_t first = value.find(',');
  const size_t second =
      first == std::string::npos ? std::string::npos : value.find(',', first + 1);
  const size_t third =
      second == std::string::npos ? std::string::npos : value.find(',', second + 1);
  if (first == std::string::npos || second == std::string::npos ||
      third == std::string::npos) {
    return false;
  }
  float x = 0.0f;
  float y = 0.0f;
  float delta_x = 0.0f;
  float delta_y = 0.0f;
  if (!ParseFloat(value.substr(0, first), &x) ||
      !ParseFloat(value.substr(first + 1, second - first - 1), &y) ||
      !ParseFloat(value.substr(second + 1, third - second - 1), &delta_x) ||
      !ParseFloat(value.substr(third + 1), &delta_y)) {
    return false;
  }
  output->position = html_css_renderer::Point{x, y};
  output->delta = html_css_renderer::Point{delta_x, delta_y};
  return true;
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

bool ParseElementScrollOffset(const std::string& value,
                              std::string* element_id,
                              html_css_renderer::Point* scroll_offset) {
  const size_t colon = value.find(':');
  const size_t comma =
      colon == std::string::npos ? std::string::npos
                                 : value.find(',', colon + 1);
  if (colon == std::string::npos || comma == std::string::npos ||
      colon == 0) {
    return false;
  }
  float x = 0.0f;
  float y = 0.0f;
  if (!ParseFloat(value.substr(colon + 1, comma - colon - 1), &x) ||
      !ParseFloat(value.substr(comma + 1), &y)) {
    return false;
  }
  *element_id = value.substr(0, colon);
  *scroll_offset = html_css_renderer::Point{x, y};
  return true;
}

bool SameStylesheetList(
    const std::vector<html_css_renderer::Stylesheet>& a,
    const std::vector<html_css_renderer::Stylesheet>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i].css != b[i].css) {
      return false;
    }
  }
  return true;
}

bool SamePointMap(const std::unordered_map<std::string, html_css_renderer::Point>& a,
                  const std::unordered_map<std::string, html_css_renderer::Point>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (const auto& entry : a) {
    const auto found = b.find(entry.first);
    if (found == b.end() || found->second.x != entry.second.x ||
        found->second.y != entry.second.y) {
      return false;
    }
  }
  return true;
}

bool SamePointers(const std::vector<html_css_renderer::PointerState>& a,
                  const std::vector<html_css_renderer::PointerState>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i].id != b[i].id || a[i].position.x != b[i].position.x ||
        a[i].position.y != b[i].position.y || a[i].pressed != b[i].pressed) {
      return false;
    }
  }
  return true;
}

bool SameWheelInput(const std::optional<html_css_renderer::WheelInput>& a,
                    const std::optional<html_css_renderer::WheelInput>& b) {
  if (!a || !b) {
    return !a && !b;
  }
  return a->position.x == b->position.x && a->position.y == b->position.y &&
         a->delta.x == b->delta.x && a->delta.y == b->delta.y;
}

bool SameStringMap(
    const std::unordered_map<std::string, std::string>& a,
    const std::unordered_map<std::string, std::string>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (const auto& entry : a) {
    const auto found = b.find(entry.first);
    if (found == b.end() || found->second != entry.second) {
      return false;
    }
  }
  return true;
}

bool SameOptionalViewport(const std::optional<html_css_renderer::Size>& a,
                         const std::optional<html_css_renderer::Size>& b) {
  if (!a || !b) {
    return !a && !b;
  }
  return a->width == b->width && a->height == b->height;
}

bool IsNonWhite(uint32_t rgba) {
  const uint32_t r = (rgba >> 24) & 0xff;
  const uint32_t g = (rgba >> 16) & 0xff;
  const uint32_t b = (rgba >> 8) & 0xff;
  const uint32_t a = rgba & 0xff;
  return a < 250 || r < 245 || g < 245 || b < 245;
}

Metrics ComputeMetrics(const html_css_renderer::CpuImage& image) {
  Metrics metrics;
  metrics.width = image.width;
  metrics.height = image.height;
  metrics.pixel_count = image.pixels_rgba.size();
  metrics.content_left = image.width;
  metrics.content_top = image.height;
  std::unordered_set<uint32_t> unique_sample;
  for (int y = 0; y < image.height; ++y) {
    for (int x = 0; x < image.width; ++x) {
      const uint32_t pixel =
          image.pixels_rgba[static_cast<size_t>(y) * image.width + x];
      if (unique_sample.size() < 4096) {
        unique_sample.insert(pixel);
      }
      if (!IsNonWhite(pixel)) {
        continue;
      }
      ++metrics.non_white_pixels;
      metrics.content_left = std::min(metrics.content_left, x);
      metrics.content_top = std::min(metrics.content_top, y);
      metrics.content_right = std::max(metrics.content_right, x + 1);
      metrics.content_bottom = std::max(metrics.content_bottom, y + 1);
    }
  }
  metrics.unique_color_sample = unique_sample.size();
  if (metrics.non_white_pixels == 0) {
    metrics.content_left = 0;
    metrics.content_top = 0;
  }
  return metrics;
}

void WriteLe16(std::ofstream& file, uint16_t value) {
  const char bytes[2] = {
      static_cast<char>(value & 0xff),
      static_cast<char>((value >> 8) & 0xff),
  };
  file.write(bytes, sizeof(bytes));
}

void WriteLe32(std::ofstream& file, uint32_t value) {
  const char bytes[4] = {
      static_cast<char>(value & 0xff),
      static_cast<char>((value >> 8) & 0xff),
      static_cast<char>((value >> 16) & 0xff),
      static_cast<char>((value >> 24) & 0xff),
  };
  file.write(bytes, sizeof(bytes));
}

bool WriteBmp(const std::string& path, const html_css_renderer::CpuImage& image) {
  std::ofstream file(path, std::ios::binary);
  if (!file) {
    return false;
  }
  constexpr uint32_t kFileHeaderSize = 14;
  constexpr uint32_t kInfoHeaderSize = 40;
  constexpr uint32_t kBytesPerPixel = 4;
  const uint32_t pixel_data_size =
      static_cast<uint32_t>(image.width * image.height * kBytesPerPixel);
  const uint32_t pixel_data_offset = kFileHeaderSize + kInfoHeaderSize;
  const uint32_t file_size = pixel_data_offset + pixel_data_size;

  file.put('B');
  file.put('M');
  WriteLe32(file, file_size);
  WriteLe16(file, 0);
  WriteLe16(file, 0);
  WriteLe32(file, pixel_data_offset);

  WriteLe32(file, kInfoHeaderSize);
  WriteLe32(file, static_cast<uint32_t>(image.width));
  WriteLe32(file, static_cast<uint32_t>(-image.height));  // Top-down bitmap.
  WriteLe16(file, 1);
  WriteLe16(file, 32);
  WriteLe32(file, 0);  // BI_RGB.
  WriteLe32(file, pixel_data_size);
  WriteLe32(file, 2835);
  WriteLe32(file, 2835);
  WriteLe32(file, 0);
  WriteLe32(file, 0);

  for (const uint32_t rgba : image.pixels_rgba) {
    const char bgra[4] = {
        static_cast<char>((rgba >> 8) & 0xff),
        static_cast<char>((rgba >> 16) & 0xff),
        static_cast<char>((rgba >> 24) & 0xff),
        static_cast<char>(rgba & 0xff),
    };
    file.write(bgra, sizeof(bgra));
  }
  return true;
}

void WriteJsonString(std::ofstream& file, const std::string& value) {
  file << "\"";
  for (char c : value) {
    switch (c) {
      case '\\':
        file << "\\\\";
        break;
      case '"':
        file << "\\\"";
        break;
      case '\n':
        file << "\\n";
        break;
      case '\r':
        file << "\\r";
        break;
      case '\t':
        file << "\\t";
        break;
      default:
        file << c;
        break;
    }
  }
  file << "\"";
}

bool WriteJson(const std::string& path,
               const Metrics& metrics,
               const html_css_renderer::RenderResult& result,
               const std::string& font_path,
               const BenchmarkTimingDiagnostics& timing) {
  std::ofstream file(path);
  if (!file) {
    return false;
  }
  file << "{\n";
  file << "  \"width\": " << metrics.width << ",\n";
  file << "  \"height\": " << metrics.height << ",\n";
  file << "  \"pixel_count\": " << metrics.pixel_count << ",\n";
  file << "  \"non_white_pixels\": " << metrics.non_white_pixels << ",\n";
  file << "  \"unique_color_sample\": " << metrics.unique_color_sample << ",\n";
  file << "  \"content_bounds\": {\"left\": " << metrics.content_left
       << ", \"top\": " << metrics.content_top
       << ", \"right\": " << metrics.content_right
       << ", \"bottom\": " << metrics.content_bottom << "},\n";
  file << "  \"diagnostic_count\": " << result.diagnostics.size() << ",\n";
  file << "  \"missing_resource_count\": " << result.missing_resources.size()
       << ",\n";
  file << "  \"default_font_path\": \"" << font_path << "\",\n";
  file << "  \"render_timing_diagnostics\": {\n";
  file << "    \"mode\": \"in_process_benchmark_chrono\",\n";
  file << "    \"warm_or_cold\": "
       << (timing.cold_process ? "\"cold_process\"" : "\"warm_process\"")
       << ",\n";
  file << "    \"caveat\": \"internal timings exclude subprocess startup; "
          "comparison summaries separately report command wall-clock elapsed "
          "time where available\",\n";
  file << "    \"used_blink\": " << (timing.used_blink ? "true" : "false")
       << ",\n";
  file << "    \"used_skia_cpu\": "
       << (timing.used_skia_cpu ? "true" : "false") << ",\n";
  file << "    \"viewport\": {\"width\": "
       << result.successor_snapshot.viewport.width << ", \"height\": "
       << result.successor_snapshot.viewport.height << "},\n";
  const auto requested_document_scroll =
      result.successor_snapshot.scroll_offsets_by_element_id.find("document");
  file << "    \"scroll_input\": {\"x\": "
       << (requested_document_scroll ==
                   result.successor_snapshot.scroll_offsets_by_element_id.end()
               ? 0.0f
               : requested_document_scroll->second.x)
       << ", \"y\": "
       << (requested_document_scroll ==
                   result.successor_snapshot.scroll_offsets_by_element_id.end()
               ? 0.0f
               : requested_document_scroll->second.y)
       << "},\n";
  file << "    \"time_input_ms\": "
       << result.successor_snapshot.timeline_time_seconds * 1000.0 << ",\n";
  file << "    \"process_elapsed_ms\": " << timing.process_elapsed_ms
       << ",\n";
  file << "    \"input_setup_ms\": " << timing.input_setup_ms << ",\n";
  file << "    \"blink_embedder_create_ms\": "
       << timing.blink_embedder_create_ms << ",\n";
  file << "    \"blink_initialize_ms\": " << timing.blink_initialize_ms
       << ",\n";
  file << "    \"advance_and_render_ms\": " << timing.advance_and_render_ms
       << ",\n";
  file << "    \"cpu_raster_replay_ms\": " << timing.cpu_raster_replay_ms
       << ",\n";
  file << "    \"cpu_raster_replay_skipped\": "
       << (timing.cpu_raster_replay_skipped ? "true" : "false") << ",\n";
  file << "    \"raster_pixels_touched\": "
       << timing.raster_pixels_touched << ",\n";
  file << "    \"damage_pixels\": " << timing.damage_pixels << ",\n";
  file << "    \"damage_clip_count\": " << timing.damage_clip_count << ",\n";
  file << "    \"replay_group_count\": " << timing.replay_group_count << ",\n";
  file << "    \"command_replay_count_before_grouping\": "
       << timing.command_replay_count_before_grouping << ",\n";
  file << "    \"command_replay_count_after_grouping\": "
       << timing.command_replay_count_after_grouping << ",\n";
  file << "    \"raw_damage_area\": " << timing.raw_damage_area << ",\n";
  file << "    \"coalesced_damage_area\": "
       << timing.coalesced_damage_area << ",\n";
  file << "    \"damage_grouping_ms\": " << timing.damage_grouping_ms
       << ",\n";
  file << "    \"skregion_clip_ms\": " << timing.skregion_clip_ms << ",\n";
  file << "    \"cpu_replay_ms\": " << timing.cpu_replay_ms << ",\n";
  file << "    \"copyback_ms\": " << timing.copyback_ms << ",\n";
  file << "    \"partial_raster\": "
       << (timing.partial_raster ? "true" : "false") << ",\n";
  file << "    \"output_image_write_ms\": " << timing.output_image_write_ms
       << ",\n";
  file << "    \"metrics_json_write_ms\": " << timing.metrics_json_write_ms
       << ",\n";
  file << "    \"audit_json_write_ms\": " << timing.audit_json_write_ms
       << ",\n";
  file << "    \"page_setup_json_write_ms\": "
       << timing.page_setup_json_write_ms << ",\n";
  file << "    \"oracle_advance_and_render_ms\": "
       << timing.oracle_advance_and_render_ms << ",\n";
  file << "    \"oracle_cpu_raster_replay_ms\": "
       << timing.oracle_cpu_raster_replay_ms << ",\n";
  file << "    \"oracle_output_write_ms\": " << timing.oracle_output_write_ms
       << ",\n";
  file << "    \"measured_frame_count\": " << timing.measured_frame_count
       << ",\n";
  file << "    \"measured_no_change_fast_path_count\": "
       << timing.measured_no_change_fast_path_count << ",\n";
  file << "    \"measured_paint_artifact_translation_count\": "
       << timing.measured_paint_artifact_translation_count << ",\n";
  file << "    \"measured_lifecycle_count\": "
       << timing.measured_lifecycle_count << ",\n";
  file << "    \"raw_chunk_count\": " << result.frame.scene_chunks.size()
       << ",\n";
  file << "    \"retained_command_count\": "
       << result.frame.scene_commands.size() << ",\n";
  file << "    \"frame_work\": "
       << html_css_renderer::SerializeFrameWorkDiagnosticsJson(
              result.frame_work)
       << "\n";
  file << "  },\n";
  file << "  \"diagnostics\": [";
  for (size_t i = 0; i < result.diagnostics.size(); ++i) {
    if (i != 0) {
      file << ", ";
    }
    file << "\"";
    for (char c : result.diagnostics[i]) {
      switch (c) {
        case '\\':
          file << "\\\\";
          break;
        case '"':
          file << "\\\"";
          break;
        case '\n':
          file << "\\n";
          break;
        case '\r':
          file << "\\r";
          break;
        case '\t':
          file << "\\t";
          break;
        default:
          file << c;
          break;
      }
    }
    file << "\"";
  }
  file << "],\n";
  file << "  \"render_result\": "
       << html_css_renderer::SerializeRenderResultJson(result) << "\n";
  file << "}\n";
  return true;
}

int ExtractJsonHistogramCount(const std::string& json,
                              const std::string& histogram_name,
                              const std::string& key) {
  const std::string histogram = "\"" + histogram_name + "\":";
  const size_t histogram_pos = json.find(histogram);
  if (histogram_pos == std::string::npos) {
    return 0;
  }
  const size_t object_begin = json.find('{', histogram_pos + histogram.size());
  if (object_begin == std::string::npos) {
    return 0;
  }
  int depth = 0;
  size_t object_end = object_begin;
  for (; object_end < json.size(); ++object_end) {
    if (json[object_end] == '{') {
      ++depth;
    } else if (json[object_end] == '}') {
      --depth;
      if (depth == 0) {
        break;
      }
    }
  }
  if (object_end <= object_begin) {
    return 0;
  }
  const std::string object =
      json.substr(object_begin, object_end - object_begin);
  const std::string needle = "\"" + key + "\":";
  const size_t key_pos = object.find(needle);
  if (key_pos == std::string::npos) {
    return 0;
  }
  size_t value_pos = key_pos + needle.size();
  while (value_pos < object.size() &&
         std::isspace(static_cast<unsigned char>(object[value_pos]))) {
    ++value_pos;
  }
  char* end = nullptr;
  const long value = std::strtol(object.c_str() + value_pos, &end, 10);
  return value > 0 ? static_cast<int>(value) : 0;
}

int CountJsonSubstring(const std::string& json, const std::string& needle) {
  int count = 0;
  size_t offset = 0;
  while (true) {
    offset = json.find(needle, offset);
    if (offset == std::string::npos) {
      break;
    }
    ++count;
    offset += needle.size();
  }
  return count;
}

std::string ExtractJsonStringBefore(const std::string& json,
                                    const std::string& key,
                                    size_t before) {
  const size_t key_pos = json.rfind(key, before);
  if (key_pos == std::string::npos) {
    return {};
  }
  const size_t value_start = json.find('"', key_pos + key.size());
  if (value_start == std::string::npos) {
    return {};
  }
  const size_t value_end = json.find('"', value_start + 1);
  if (value_end == std::string::npos) {
    return {};
  }
  return json.substr(value_start + 1, value_end - value_start - 1);
}

std::string ExtractJsonArrayAfter(const std::string& json,
                                  const std::string& key,
                                  size_t after) {
  const size_t key_pos = json.find(key, after);
  if (key_pos == std::string::npos) {
    return "null";
  }
  const size_t array_start = json.find('[', key_pos + key.size());
  const size_t array_end = json.find(']', array_start);
  if (array_start == std::string::npos || array_end == std::string::npos) {
    return "null";
  }
  return json.substr(array_start, array_end - array_start + 1);
}

void WriteOracleImageOpExamples(std::ofstream& file,
                                const std::string& raw_json) {
  file << "    \"raw_image_op_examples\": [";
  bool first = true;
  size_t offset = 0;
  while (true) {
    size_t op_pos = raw_json.find("\"type\":\"DrawImage", offset);
    if (op_pos == std::string::npos) {
      break;
    }
    const bool is_rect =
        raw_json.compare(op_pos, std::strlen("\"type\":\"DrawImageRectOp\""),
                         "\"type\":\"DrawImageRectOp\"") == 0;
    const char* op_type = is_rect ? "DrawImageRectOp" : "DrawImageOp";
    if (!first) {
      file << ", ";
    }
    first = false;
    file << "{\"chunk_id\": ";
    WriteJsonString(file, ExtractJsonStringBefore(raw_json,
                                                  "\"paint_chunk_id\":",
                                                  op_pos));
    file << ", \"display_item_id\": ";
    WriteJsonString(file, ExtractJsonStringBefore(raw_json, "\"id\":",
                                                  op_pos));
    file << ", \"recursive_path\": ";
    WriteJsonString(file, std::string("paint_ops/") + op_type);
    file << ", \"op_type\": ";
    WriteJsonString(file, op_type);
    file << ", \"src_rect\": null, \"dst_rect\": "
         << ExtractJsonArrayAfter(raw_json, "\"bounds_or_geometry\":", op_pos)
         << ", \"decoded_size\": null, \"retained_command_id\": null}";
    offset = op_pos + 1;
  }
  file << "],\n";
}

bool WriteOracleProvenanceJson(
    const std::string& path,
    const Metrics& metrics,
    const html_css_renderer::RenderResult& oracle_result,
    const std::string& requested_mode,
    const std::string& transform_mode) {
  std::ofstream file(path);
  if (!file) {
    return false;
  }
  file << "{\n";
  file << "  \"oracle\": {\n";
  file << "    \"implemented\": true,\n";
  file << "    \"source\": \"manual_chunk_property_replay\",\n";
  file << "    \"oracle_provenance\": {";
  file << "\"requested_mode\": ";
  WriteJsonString(file, requested_mode);
  file << ", \"actual_mode\": \"manual_chunk_property_replay\"";
  file << ", \"uses_blink_paintartifact_direct_playback\": false";
  file << ", \"uses_retained_exported_commands\": true";
  file << ", \"uses_transform_stripping\": "
       << (transform_mode == "record-only" ? "true" : "false");
  file << ", \"blink_flattened_get_paint_record_available\": false";
  file << ", \"reason_if_not_independent\": "
       << "\"standalone PaintArtifact::GetPaintRecord is currently an empty "
          "stub, so this oracle replays exported PaintArtifact commands "
          "through the retained Skia CPU path\"";
  file << "},\n";
  file << "    \"uses_retained_draw_commands\": true,\n";
  file << "    \"uses_live_exported_draw_ops_for_paint_generation\": true,\n";
  file << "    \"uses_bitmap_transport_for_output\": false,\n";
  file << "    \"uses_diagnostic_bitmap_fallback_as_rendering\": false,\n";
  file << "    \"retained_command_count_for_oracle_generation\": 0,\n";
  const std::string& raw_json = oracle_result.raw_paint_artifact_audit_json;
  const int draw_image_count = ExtractJsonHistogramCount(
      raw_json, "recursive_raw_blink_paint_op_histogram", "DrawImageOp");
  const int draw_image_rect_count = ExtractJsonHistogramCount(
      raw_json, "recursive_raw_blink_paint_op_histogram", "DrawImageRectOp");
  const int image_backed_shader_count =
      CountJsonSubstring(raw_json, "\"image_backed_shader\":true");
  file << "    \"raw_image_op_histogram\": {\"DrawImageOp\": "
       << draw_image_count << ", \"DrawImageRectOp\": "
       << draw_image_rect_count << ", \"image_backed_shader\": "
       << image_backed_shader_count << "},\n";
  WriteOracleImageOpExamples(file, raw_json);
  file << "    \"image_resource_count\": "
       << (draw_image_count + draw_image_rect_count +
           image_backed_shader_count)
       << ",\n";
  file << "    \"non_white_pixels\": " << metrics.non_white_pixels << ",\n";
  file << "    \"content_bounds\": {\"left\": " << metrics.content_left
       << ", \"top\": " << metrics.content_top
       << ", \"right\": " << metrics.content_right
       << ", \"bottom\": " << metrics.content_bottom << "},\n";
  file << "    \"raw_paint_artifact_audit\": ";
  if (!oracle_result.raw_paint_artifact_audit_json.empty()) {
    file << oracle_result.raw_paint_artifact_audit_json << "\n";
  } else {
    file << "null\n";
  }
  file << "  },\n";
  file << "  \"diagnostics\": [";
  for (size_t i = 0; i < oracle_result.diagnostics.size(); ++i) {
    if (i != 0) {
      file << ", ";
    }
    WriteJsonString(file, oracle_result.diagnostics[i]);
  }
  file << "]\n";
  file << "}\n";
  return true;
}

bool WritePageSetupJson(const std::string& path,
                        const html_css_renderer::RendererCreateInfo& info,
                        const html_css_renderer::RenderResult& result,
                        const std::string& html_file,
                        const std::string& lifecycle_stop,
                        bool used_live_blink) {
  std::ofstream file(path);
  if (!file) {
    return false;
  }
  file << "{\n";
  file << "  \"page_setup\": {\n";
  file << "    \"viewport\": {\"width\": " << info.viewport.width
       << ", \"height\": " << info.viewport.height << "},\n";
  const auto requested_document_scroll =
      result.successor_snapshot.scroll_offsets_by_element_id.find("document");
  file << "    \"requested_scroll\": {\"x\": "
       << (requested_document_scroll ==
                   result.successor_snapshot.scroll_offsets_by_element_id.end()
               ? 0.0f
               : requested_document_scroll->second.x)
       << ", \"y\": "
       << (requested_document_scroll ==
                   result.successor_snapshot.scroll_offsets_by_element_id.end()
               ? 0.0f
               : requested_document_scroll->second.y)
       << "},\n";
  file << "    \"device_scale_factor\": 1,\n";
  file << "    \"css_pixel_ratio\": 1,\n";
  file << "    \"page_scale\": 1,\n";
  file << "    \"compat_mode\": \"standards_expected_from_doctype_or_unknown\",\n";
  file << "    \"base_url\": ";
  WriteJsonString(file, html_file.empty() ? std::string() : fs::absolute(html_file).parent_path().string());
  file << ",\n";
  file << "    \"document_url\": ";
  WriteJsonString(file, html_file.empty() ? std::string("about:blank") : fs::absolute(html_file).string());
  file << ",\n";
  file << "    \"security_origin_summary\": \"standalone local document\",\n";
  file << "    \"ua_stylesheet_status\": \"embedded standalone UA stylesheet\",\n";
  file << "    \"default_font\": \"benchmark default font provider / system fallback\",\n";
  file << "    \"author_stylesheet_count\": " << info.stylesheets.size()
       << ",\n";
  file << "    \"css_injection_path\": \"inline head style plus local linked CSS loader\",\n";
  file << "    \"injected_default_demo_css\": false,\n";
  file << "    \"scrollbar_policy\": \"standalone browser scrollbar/resizer paint properties skipped under guard\",\n";
  file << "    \"media_query_environment\": {\"width\": " << info.viewport.width
       << ", \"height\": " << info.viewport.height
       << ", \"hover\": \"unknown\", \"pointer\": \"unknown\","
       << " \"prefers_color_scheme\": \"unknown\", \"reduced_motion\": \"unknown\"},\n";
  file << "    \"lifecycle_stop\": ";
  WriteJsonString(file, lifecycle_stop);
  file << ",\n";
  file << "    \"used_blink\": " << (used_live_blink ? "true" : "false") << ",\n";
  file << "    \"html_computed_style\": {\"status\": \"see raw_audit.page_evidence when available\"},\n";
  file << "    \"body_computed_style\": {\"status\": \"see raw_audit.page_evidence when available\"},\n";
  file << "    \"document_element_layout_rect\": {\"status\": \"not yet exported as dedicated field\"},\n";
  file << "    \"body_layout_rect\": {\"status\": \"not yet exported as dedicated field\"},\n";
  file << "    \"layout_view_size\": {\"width\": " << result.successor_snapshot.viewport.width
       << ", \"height\": " << result.successor_snapshot.viewport.height << "}\n";
  file << "  },\n";
  file << "  \"raw_audit\": ";
  if (!result.raw_paint_artifact_audit_json.empty()) {
    file << result.raw_paint_artifact_audit_json << "\n";
  } else {
    file << "null\n";
  }
  file << "}\n";
  return true;
}

bool HasRealBlinkPaintArtifact(const html_css_renderer::RenderResult& result) {
  for (const std::string& diagnostic : result.diagnostics) {
    if (diagnostic.find("paint artifact source: real Blink PaintArtifact") !=
            std::string::npos ||
        diagnostic.find("real Blink PaintArtifact translated into draw "
                        "commands") != std::string::npos) {
      return true;
    }
  }
  return false;
}

void PrintDiagnostics(const html_css_renderer::RenderResult& result) {
  for (const std::string& diagnostic : result.diagnostics) {
    std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
  }
}

void StripTransformCommandsForDiagnosticOracle(
    html_css_renderer::RenderResult& result) {
  for (html_css_renderer::SceneChunk& chunk : result.frame.scene_chunks) {
    chunk.commands.erase(
        std::remove_if(chunk.commands.begin(), chunk.commands.end(),
                       [](const html_css_renderer::DrawCommand& command) {
                         return command.type ==
                                html_css_renderer::DrawCommandType::kTransform;
                       }),
        chunk.commands.end());
  }
  result.frame.scene_commands.erase(
      std::remove_if(
          result.frame.scene_commands.begin(), result.frame.scene_commands.end(),
          [](const html_css_renderer::SceneCommand& command) {
            return command.type ==
                       html_css_renderer::SceneCommandType::kDrawCommand &&
                   command.draw_command.type ==
                       html_css_renderer::DrawCommandType::kTransform;
          }),
      result.frame.scene_commands.end());
  result.diagnostics.push_back(
      "diagnostic_transform_mode=record-only stripped retained Transform "
      "commands for diagnostic playback only");
}

void PrintUsage() {
  std::fprintf(stderr,
               "Usage: blink_standalone_render_benchmark_skia --html <html> "
               "[--html-file <path>] [--css <css>] [--css-file <path>] "
               "[--previous-css-file <path>] "
               "[--attr id:name=value] [--previous-attr id:name=value] "
               "[--hover id] [--previous-hover id] "
               "[--active id] [--previous-active id] "
               "[--pointer x,y] [--pointer-down] "
               "[--previous-pointer x,y] [--previous-pointer-down] "
               "[--wheel x,y,dx,dy] "
               "[--resource-root <path>] "
               "[--viewport WxH] [--previous-scroll-x px] [--previous-scroll-y px] "
               "[--scroll-x px] [--scroll-y px] "
               "[--previous-scroll-element id:x,y] "
               "[--scroll-element id:x,y] "
               "[--time-ms ms] [--incremental] [--previous-time-ms ms] "
               "[--repeat-no-change-frames count] "
               "--out <out.bmp> "
               "[--json <metrics.json>] [--min-non-white pixels] "
               "[--dump-paint-artifact <artifact.json>] "
               "[--dump-page-setup <setup.json>] "
               "[--audit-only] "
               "[--lifecycle-stop <html|style|layout|prepaint|paint|artifact>] "
               "[--crash-dump <path>] "
               "[--paint-oracle=skia-paint-record] [--oracle-out <out.bmp>] "
               "[--paint-oracle-transform-mode=normal|record-only] "
               "[--retained-transform-mode=normal|record-only] "
               "[--debug-text-blob-replay] "
               "[--debug-command-coverage] "
               "[--disable-damage-clip-grouping] "
               "[--self-test-damage-grouping] "
               "[--strict-text-blob-typefaces] "
               "[--compat-text-blob-typefaces] "
               "[--font-file path]"
               "\n");
  std::fprintf(stderr,
               "Note: this executable always uses live Blink PaintArtifact "
               "input and the Skia CPU raster path. Backend selector flags "
               "are not supported.\n");
}

#if defined(_WIN32)
std::string g_crash_dump_path;

LONG WINAPI WriteBenchmarkCrashDump(EXCEPTION_POINTERS* exception_pointers) {
  if (g_crash_dump_path.empty()) {
    return EXCEPTION_CONTINUE_SEARCH;
  }
  HANDLE file = CreateFileA(g_crash_dump_path.c_str(), GENERIC_WRITE, 0, nullptr,
                            CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
  if (file == INVALID_HANDLE_VALUE) {
    std::fprintf(stderr, "crash_dump.failed path=%s gle=%lu\n",
                 g_crash_dump_path.c_str(), GetLastError());
    std::fflush(stderr);
    return EXCEPTION_CONTINUE_SEARCH;
  }
  MINIDUMP_EXCEPTION_INFORMATION exception_info;
  exception_info.ThreadId = GetCurrentThreadId();
  exception_info.ExceptionPointers = exception_pointers;
  exception_info.ClientPointers = FALSE;
  const BOOL ok = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(),
                                    file, MiniDumpWithDataSegs,
                                    &exception_info, nullptr, nullptr);
  CloseHandle(file);
  const DWORD code =
      exception_pointers && exception_pointers->ExceptionRecord
          ? exception_pointers->ExceptionRecord->ExceptionCode
          : 0;
  const void* address =
      exception_pointers && exception_pointers->ExceptionRecord
          ? exception_pointers->ExceptionRecord->ExceptionAddress
          : nullptr;
  std::fprintf(stderr,
               "crash_dump.%s path=%s exception_code=0x%08lx address=%p "
               "thread_id=%lu gle=%lu\n",
               ok ? "written" : "failed", g_crash_dump_path.c_str(), code,
               address, GetCurrentThreadId(), ok ? 0 : GetLastError());
  std::fflush(stderr);
  return EXCEPTION_EXECUTE_HANDLER;
}
#endif

html_css_renderer::Rect BoundsForRects(
    const std::vector<html_css_renderer::Rect>& rects) {
  bool have_bounds = false;
  html_css_renderer::Rect bounds;
  for (const html_css_renderer::Rect& rect : rects) {
    if (rect.width <= 0.0f || rect.height <= 0.0f) {
      continue;
    }
    if (!have_bounds) {
      bounds = rect;
      have_bounds = true;
      continue;
    }
    const float left = std::min(bounds.x, rect.x);
    const float top = std::min(bounds.y, rect.y);
    const float right =
        std::max(bounds.x + bounds.width, rect.x + rect.width);
    const float bottom =
        std::max(bounds.y + bounds.height, rect.y + rect.height);
    bounds = {left, top, right - left, bottom - top};
  }
  return have_bounds ? bounds : html_css_renderer::Rect{};
}

std::vector<html_css_renderer::SceneCommand> DamageGroupingSelfTestCommands() {
  using html_css_renderer::Color;
  using html_css_renderer::DrawCommand;
  using html_css_renderer::DrawLooperLayer;
  using html_css_renderer::FilterOperationKind;
  using html_css_renderer::FilterOperationSnapshot;
  using html_css_renderer::SceneCommand;

  FilterOperationSnapshot blur;
  blur.kind = FilterOperationKind::kBlur;
  blur.amount = 1.25f;

  DrawCommand shadow =
      DrawCommand::FillRRect({24.0f, 24.0f, 132.0f, 84.0f}, 14.0f, 14.0f,
                             Color::Rgba(0.22f, 0.45f, 0.78f, 0.96f));
  DrawLooperLayer shadow_layer;
  shadow_layer.offset_x = 3.0f;
  shadow_layer.offset_y = 4.0f;
  shadow_layer.blur_sigma = 3.0f;
  shadow_layer.color = Color::Rgba(0.0f, 0.0f, 0.0f, 0.32f);
  shadow.draw_looper_layers.push_back(shadow_layer);

  return {
      SceneCommand::Draw(
          DrawCommand::FillRect({0.0f, 0.0f, 220.0f, 160.0f},
                                Color::Rgba(0.98f, 0.98f, 0.96f, 1.0f))),
      SceneCommand::Draw(DrawCommand::SaveLayer(
          {12.0f, 12.0f, 176.0f, 116.0f}, 0.9f, "src_over", {blur})),
      SceneCommand::Draw(DrawCommand::ClipRRect(
          {18.0f, 18.0f, 164.0f, 102.0f}, 18.0f, 18.0f)),
      SceneCommand::Draw(shadow),
      SceneCommand::Draw(
          DrawCommand::FillRect({40.0f, 40.0f, 36.0f, 34.0f},
                                Color::Rgba(0.96f, 0.68f, 0.18f, 1.0f))),
      SceneCommand::Draw(
          DrawCommand::FillRect({104.0f, 52.0f, 42.0f, 38.0f},
                                Color::Rgba(0.20f, 0.72f, 0.55f, 0.94f))),
      SceneCommand::Draw(DrawCommand::Restore()),
      SceneCommand::Draw(DrawCommand::Save()),
      SceneCommand::Draw(
          DrawCommand::ClipRect({20.0f, 118.0f, 180.0f, 24.0f})),
      SceneCommand::Draw(
          DrawCommand::FillRect({14.0f, 112.0f, 192.0f, 36.0f},
                                Color::Rgba(0.42f, 0.24f, 0.78f, 0.82f))),
      SceneCommand::Draw(DrawCommand::Restore()),
  };
}

html_css_renderer::RenderResult DamageGroupingSelfTestResult(
    const std::vector<html_css_renderer::Rect>& damage_rects,
    bool full_redraw) {
  html_css_renderer::RenderResult result;
  const html_css_renderer::Size viewport{220.0f, 160.0f};
  result.successor_snapshot.viewport = viewport;
  result.frame.scene_commands = DamageGroupingSelfTestCommands();
  result.frame.damage_rects = damage_rects;
  result.frame.damage_bounds = BoundsForRects(damage_rects);
  result.frame.requires_full_redraw = full_redraw;
  result.requires_full_redraw = full_redraw;
  result.damage_rects = damage_rects;
  result.damage_bounds = result.frame.damage_bounds;
  return result;
}

bool SamePixels(const html_css_renderer::CpuImage& a,
                const html_css_renderer::CpuImage& b) {
  return a.width == b.width && a.height == b.height &&
         a.pixels_rgba == b.pixels_rgba;
}

int RunDamageGroupingSelfTest() {
  struct SelfTestCase {
    const char* name;
    std::vector<html_css_renderer::Rect> damage_rects;
    bool expect_skipped = false;
    bool expect_grouped = false;
  };
  const std::vector<SelfTestCase> cases = {
      {"empty_damage", {}, true, false},
      {"outside_viewport_damage", {{260.0f, 180.0f, 20.0f, 20.0f}}, true,
       false},
      {"overlapping_damage",
       {{20.0f, 20.0f, 42.0f, 42.0f}, {38.0f, 38.0f, 42.0f, 42.0f}},
       false, false},
      {"many_tiny_disjoint_damage",
       {{22.0f, 24.0f, 10.0f, 10.0f},
        {33.0f, 24.0f, 10.0f, 10.0f},
        {44.0f, 24.0f, 10.0f, 10.0f},
        {55.0f, 24.0f, 10.0f, 10.0f},
        {66.0f, 24.0f, 10.0f, 10.0f},
        {77.0f, 24.0f, 10.0f, 10.0f}},
       false, true},
      {"effect_rounded_shadow_disjoint_damage",
       {{20.0f, 20.0f, 26.0f, 26.0f},
        {70.0f, 28.0f, 26.0f, 26.0f},
        {120.0f, 36.0f, 26.0f, 26.0f},
        {24.0f, 120.0f, 26.0f, 18.0f},
        {84.0f, 120.0f, 26.0f, 18.0f}},
       false, false},
  };

  const html_css_renderer::RenderResult full_result =
      DamageGroupingSelfTestResult({}, true);
  html_css_renderer::CpuRenderOptions full_options;
  const html_css_renderer::CpuImage previous =
      html_css_renderer::RasterizeRenderResultWithSkiaCpu(full_result,
                                                          full_options);

  bool failed = false;
  for (const SelfTestCase& test_case : cases) {
    html_css_renderer::RenderResult result =
        DamageGroupingSelfTestResult(test_case.damage_rects, false);
    html_css_renderer::CpuRenderOptions grouped_options;
    html_css_renderer::CpuRenderOptions ungrouped_options;
    ungrouped_options.disable_damage_clip_grouping = true;
    const html_css_renderer::CpuImage grouped =
        html_css_renderer::RasterizeRenderResultIncrementalWithSkiaCpu(
            result, &previous, grouped_options);
    const html_css_renderer::CpuImage ungrouped =
        html_css_renderer::RasterizeRenderResultIncrementalWithSkiaCpu(
            result, &previous, ungrouped_options);

    auto fail = [&](const char* reason) {
      failed = true;
      std::fprintf(stderr,
                   "damage_grouping_self_test.%s failed: %s "
                   "clips=%zu groups=%zu before=%llu after=%llu "
                   "raw=%llu coalesced=%llu skipped=%d\n",
                   test_case.name, reason, grouped.damage_clip_count,
                   grouped.replay_group_count,
                   static_cast<unsigned long long>(
                       grouped.command_replay_count_before_grouping),
                   static_cast<unsigned long long>(
                       grouped.command_replay_count_after_grouping),
                   static_cast<unsigned long long>(grouped.raw_damage_area),
                   static_cast<unsigned long long>(
                       grouped.coalesced_damage_area),
                   grouped.raster_skipped ? 1 : 0);
    };

    if (!SamePixels(grouped, ungrouped)) {
      fail("grouped_output_differs_from_ungrouped");
    }
    if (test_case.expect_skipped) {
      if (!grouped.raster_skipped ||
          grouped.command_replay_count_after_grouping != 0 ||
          grouped.raw_damage_area != 0 || grouped.coalesced_damage_area != 0) {
        fail("empty_or_outside_damage_did_not_skip_replay");
      }
    } else {
      if (grouped.damage_pixels != grouped.raw_damage_area) {
        fail("damage_pixels_do_not_match_raw_clamped_damage_area");
      }
      if (grouped.coalesced_damage_area > grouped.raw_damage_area) {
        fail("coalesced_damage_area_exceeds_raw_damage_area");
      }
      if (grouped.command_replay_count_after_grouping >
          grouped.command_replay_count_before_grouping) {
        fail("grouping_increased_command_replay_count");
      }
    }
    if (test_case.expect_grouped &&
        grouped.replay_group_count >= grouped.damage_clip_count) {
      fail("expected_damage_clips_to_be_grouped");
    }
  }
  if (!failed) {
    std::printf("damage_grouping_self_test passed cases=%zu\n", cases.size());
  }
  return failed ? 1 : 0;
}

}  // namespace

int main(int argc, char** argv) {
  const auto process_start = BenchmarkClock::now();
#if defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX |
               SEM_NOOPENFILEERRORBOX);
  _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
#endif

  BenchmarkAssets assets;
  html_css_renderer::RendererCreateInfo create_info;
  create_info.asset_provider = &assets;
  create_info.viewport = {800.0f, 600.0f};
  html_css_renderer::FrameInput input;
  html_css_renderer::FrameInput previous_input;
  bool pointer_pressed = false;
  bool previous_pointer_pressed = false;
  std::string out_path;
  std::string json_path;
  std::string paint_artifact_dump_path;
  std::string page_setup_dump_path;
  std::string paint_oracle;
  std::string paint_oracle_transform_mode = "normal";
  std::string retained_transform_mode = "normal";
  std::string oracle_out_path;
  std::string crash_dump_path;
  std::string lifecycle_stop;
  std::string font_file;
  std::string html_file;
  std::string previous_css_file;
  std::string current_css_file;
  std::string resource_root;
  std::string resource_base_path;
  size_t min_non_white = 1;
  bool audit_only = false;
  bool trace_stages = false;
  bool debug_text_blob_replay = false;
  bool debug_command_coverage = false;
  bool disable_damage_clip_grouping = false;
  bool self_test_damage_grouping = false;
  bool strict_text_blob_typefaces = true;
  bool incremental = false;
  int repeat_no_change_frames = 1;
  BenchmarkTimingDiagnostics timing;
  std::vector<std::string> stylesheet_loader_diagnostics;
  std::vector<html_css_renderer::Stylesheet> previous_stylesheets_override;

  const auto input_setup_start = BenchmarkClock::now();
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
        PrintUsage();
        return 2;
      }
      create_info.html = value;
    } else if (arg == "--html-file") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      std::optional<std::string> html = ReadTextFile(value);
      if (!html) {
        std::fprintf(stderr, "failed to read html file: %s\n", value);
        return 2;
      }
      html_file = value;
      resource_base_path = fs::absolute(value).parent_path().string();
      resource_root = resource_base_path;
      create_info.html = InjectBaseHrefForHtmlFile(value, std::move(*html));
      html_css_renderer::AddLocalLinkedStylesheetsForDocument(
          value, create_info.html, &create_info,
          &stylesheet_loader_diagnostics);
    } else if (arg == "--resource-root") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      resource_root = fs::absolute(value).string();
    } else if (arg == "--css") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      create_info.stylesheets.push_back({"benchmark", value});
      html_css_renderer::AppendUnsupportedCssImportDiagnostic(
          value, "benchmark", &stylesheet_loader_diagnostics);
    } else if (arg == "--css-file") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      current_css_file = value;
      const fs::path css_path = value;
      const fs::path absolute_css_path = fs::absolute(css_path);
      const fs::path document_base =
          resource_base_path.empty() ? absolute_css_path.parent_path()
                                     : fs::path(resource_base_path);
      std::optional<html_css_renderer::Stylesheet> stylesheet =
          html_css_renderer::LoadStylesheetFileForDocument(
              css_path, document_base, &stylesheet_loader_diagnostics);
      if (!stylesheet) {
        std::fprintf(stderr, "failed to read css file: %s\n", value);
        return 2;
      }
      create_info.stylesheets.push_back(std::move(*stylesheet));
    } else if (arg == "--previous-css-file") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      previous_css_file = value;
      const fs::path css_path = value;
      const fs::path absolute_css_path = fs::absolute(css_path);
      const fs::path document_base =
          resource_base_path.empty() ? absolute_css_path.parent_path()
                                     : fs::path(resource_base_path);
      std::optional<html_css_renderer::Stylesheet> stylesheet =
          html_css_renderer::LoadStylesheetFileForDocument(
              css_path, document_base, &stylesheet_loader_diagnostics);
      if (!stylesheet) {
        std::fprintf(stderr, "failed to read previous css file: %s\n", value);
        return 2;
      }
      previous_stylesheets_override.push_back(std::move(*stylesheet));
    } else if (arg == "--attr") {
      const char* value = next_value();
      std::string key;
      std::string attribute_value;
      if (!value ||
          !ParseElementAttributeOverride(value, &key, &attribute_value)) {
        PrintUsage();
        return 2;
      }
      input.element_attributes_by_id_and_name[key] = attribute_value;
    } else if (arg == "--previous-attr") {
      const char* value = next_value();
      std::string key;
      std::string attribute_value;
      if (!value ||
          !ParseElementAttributeOverride(value, &key, &attribute_value)) {
        PrintUsage();
        return 2;
      }
      previous_input.element_attributes_by_id_and_name[key] = attribute_value;
    } else if (arg == "--hover") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      input.hovered_element_id = value;
    } else if (arg == "--previous-hover") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      previous_input.hovered_element_id = value;
    } else if (arg == "--active") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      input.active_element_id = value;
    } else if (arg == "--previous-active") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      previous_input.active_element_id = value;
    } else if (arg == "--pointer") {
      const char* value = next_value();
      html_css_renderer::Point point;
      if (!value || !ParsePoint(value, &point)) {
        PrintUsage();
        return 2;
      }
      SetPrimaryPointer(&input, point, pointer_pressed);
    } else if (arg == "--pointer-down") {
      pointer_pressed = true;
      if (!input.pointers.empty()) {
        input.pointers.front().pressed = true;
      }
    } else if (arg == "--previous-pointer") {
      const char* value = next_value();
      html_css_renderer::Point point;
      if (!value || !ParsePoint(value, &point)) {
        PrintUsage();
        return 2;
      }
      SetPrimaryPointer(&previous_input, point, previous_pointer_pressed);
    } else if (arg == "--previous-pointer-down") {
      previous_pointer_pressed = true;
      if (!previous_input.pointers.empty()) {
        previous_input.pointers.front().pressed = true;
      }
    } else if (arg == "--wheel") {
      const char* value = next_value();
      html_css_renderer::WheelInput wheel;
      if (!value || !ParseWheelInput(value, &wheel)) {
        PrintUsage();
        return 2;
      }
      input.wheel = wheel;
    } else if (arg == "--viewport") {
      const char* value = next_value();
      if (!value || !ParseViewport(value, &create_info.viewport)) {
        PrintUsage();
        return 2;
      }
    } else if (arg == "--previous-scroll-x") {
      const char* value = next_value();
      float scroll_x = 0.0f;
      if (!value || !ParseFloat(value, &scroll_x)) {
        PrintUsage();
        return 2;
      }
      previous_input.scroll_offsets_by_element_id["document"].x = scroll_x;
    } else if (arg == "--previous-scroll-y") {
      const char* value = next_value();
      float scroll_y = 0.0f;
      if (!value || !ParseFloat(value, &scroll_y)) {
        PrintUsage();
        return 2;
      }
      previous_input.scroll_offsets_by_element_id["document"].y = scroll_y;
    } else if (arg == "--scroll-x") {
      const char* value = next_value();
      float scroll_x = 0.0f;
      if (!value || !ParseFloat(value, &scroll_x)) {
        PrintUsage();
        return 2;
      }
      input.scroll_offsets_by_element_id["document"].x = scroll_x;
    } else if (arg == "--scroll-y") {
      const char* value = next_value();
      float scroll_y = 0.0f;
      if (!value || !ParseFloat(value, &scroll_y)) {
        PrintUsage();
        return 2;
      }
      input.scroll_offsets_by_element_id["document"].y = scroll_y;
    } else if (arg == "--previous-scroll-element") {
      const char* value = next_value();
      std::string element_id;
      html_css_renderer::Point scroll_offset;
      if (!value ||
          !ParseElementScrollOffset(value, &element_id, &scroll_offset)) {
        PrintUsage();
        return 2;
      }
      previous_input.scroll_offsets_by_element_id[element_id] = scroll_offset;
    } else if (arg == "--scroll-element") {
      const char* value = next_value();
      std::string element_id;
      html_css_renderer::Point scroll_offset;
      if (!value ||
          !ParseElementScrollOffset(value, &element_id, &scroll_offset)) {
        PrintUsage();
        return 2;
      }
      input.scroll_offsets_by_element_id[element_id] = scroll_offset;
    } else if (arg == "--time-ms") {
      const char* value = next_value();
      float time_ms = 0.0f;
      if (!value || !ParseFloat(value, &time_ms)) {
        PrintUsage();
        return 2;
      }
      input.timeline_time_seconds = std::max(0.0f, time_ms) / 1000.0;
    } else if (arg == "--previous-time-ms") {
      const char* value = next_value();
      float time_ms = 0.0f;
      if (!value || !ParseFloat(value, &time_ms)) {
        PrintUsage();
        return 2;
      }
      previous_input.timeline_time_seconds = std::max(0.0f, time_ms) / 1000.0;
    } else if (arg == "--incremental") {
      incremental = true;
    } else if (arg == "--repeat-no-change-frames") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      repeat_no_change_frames =
          std::max(1, static_cast<int>(std::strtol(value, nullptr, 10)));
    } else if (arg.rfind("--repeat-no-change-frames=", 0) == 0) {
      repeat_no_change_frames = std::max(
          1, static_cast<int>(std::strtol(arg.c_str() + 26, nullptr, 10)));
    } else if (arg == "--out") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      out_path = value;
    } else if (arg == "--json") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      json_path = value;
    } else if (arg == "--dump-paint-artifact") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      paint_artifact_dump_path = value;
    } else if (arg.rfind("--dump-paint-artifact=", 0) == 0) {
      paint_artifact_dump_path = arg.substr(22);
    } else if (arg == "--dump-page-setup") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      page_setup_dump_path = value;
    } else if (arg.rfind("--dump-page-setup=", 0) == 0) {
      page_setup_dump_path = arg.substr(18);
    } else if (arg == "--audit-only") {
      audit_only = true;
      min_non_white = 0;
    } else if (arg == "--lifecycle-stop") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      lifecycle_stop = value;
    } else if (arg.rfind("--lifecycle-stop=", 0) == 0) {
      lifecycle_stop = arg.substr(17);
    } else if (arg == "--crash-dump") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      crash_dump_path = value;
    } else if (arg.rfind("--crash-dump=", 0) == 0) {
      crash_dump_path = arg.substr(13);
    } else if (arg == "--trace-stages") {
      trace_stages = true;
    } else if (arg == "--debug-text-blob-replay") {
      debug_text_blob_replay = true;
    } else if (arg == "--debug-command-coverage") {
      debug_command_coverage = true;
    } else if (arg == "--disable-damage-clip-grouping") {
      disable_damage_clip_grouping = true;
    } else if (arg == "--self-test-damage-grouping") {
      self_test_damage_grouping = true;
    } else if (arg == "--strict-text-blob-typefaces") {
      strict_text_blob_typefaces = true;
    } else if (arg == "--compat-text-blob-typefaces") {
      strict_text_blob_typefaces = false;
    } else if (arg == "--paint-oracle") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      paint_oracle = value;
    } else if (arg.rfind("--paint-oracle=", 0) == 0) {
      paint_oracle = arg.substr(15);
    } else if (arg == "--oracle-out") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      oracle_out_path = value;
    } else if (arg == "--paint-oracle-transform-mode") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      paint_oracle_transform_mode = value;
    } else if (arg.rfind("--paint-oracle-transform-mode=", 0) == 0) {
      paint_oracle_transform_mode = arg.substr(30);
    } else if (arg == "--retained-transform-mode") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      retained_transform_mode = value;
    } else if (arg.rfind("--retained-transform-mode=", 0) == 0) {
      retained_transform_mode = arg.substr(26);
    } else if (arg == "--min-non-white") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      min_non_white = static_cast<size_t>(std::strtoull(value, nullptr, 10));
    } else if (arg == "--font-file") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      font_file = value;
    } else {
      PrintUsage();
      return 2;
    }
  }
  timing.input_setup_ms =
      ElapsedMs(input_setup_start, BenchmarkClock::now());
  timing.used_blink = true;
  timing.used_skia_cpu = true;

  if (self_test_damage_grouping) {
    return RunDamageGroupingSelfTest();
  }

  if (create_info.html.empty() || (out_path.empty() && !audit_only)) {
    PrintUsage();
    return 2;
  }

  html_css_renderer::SetStandaloneResourceProviderResourceRoot(resource_root);
  html_css_renderer::SetStandaloneResourceProviderDocumentBasePath(
      resource_base_path);

#if defined(_WIN32)
  if (!crash_dump_path.empty()) {
    g_crash_dump_path = crash_dump_path;
    SetUnhandledExceptionFilter(&WriteBenchmarkCrashDump);
  }
#endif

  std::string loaded_font_path;
  if (!font_file.empty()) {
    assets.font_bytes = ReadBinaryFile(font_file);
    loaded_font_path = font_file;
  }
  const html_css_renderer::RendererCreateInfo renderer_info_for_oracle =
      create_info;

  html_css_renderer::RenderResult result;
  html_css_renderer::RenderResult previous_result;
  bool have_previous_result = false;
  bool identical_incremental_requested = false;
  std::unique_ptr<html_css_renderer::BlinkPageEmbedder> blink_embedder;
  html_css_renderer::BlinkPageEmbedderCreateInfo blink_create_info;
  blink_create_info.renderer = std::move(create_info);
  blink_create_info.enable_paint_artifact_audit =
      audit_only || !json_path.empty() || !paint_artifact_dump_path.empty();
  blink_create_info.trace_stages = trace_stages;
  blink_create_info.debug_text_blob_replay = debug_text_blob_replay;
  blink_create_info.lifecycle_stop = lifecycle_stop;
  const auto create_start = BenchmarkClock::now();
  blink_embedder =
      html_css_renderer::CreateLiveBlinkPageEmbedder(std::move(blink_create_info));
  timing.blink_embedder_create_ms =
      ElapsedMs(create_start, BenchmarkClock::now());
  if (!blink_embedder) {
    std::fprintf(stderr, "failed to create Blink adapter\n");
    return 1;
  }
  const auto initialize_start = BenchmarkClock::now();
  const html_css_renderer::BlinkLifecycleReport init =
      blink_embedder->Initialize();
  timing.blink_initialize_ms =
      ElapsedMs(initialize_start, BenchmarkClock::now());
  BenchmarkClock::time_point render_start;
  if (incremental) {
    if (!previous_stylesheets_override.empty()) {
      previous_input.stylesheets_override = previous_stylesheets_override;
      input.stylesheets_override = renderer_info_for_oracle.stylesheets;
    }
    const bool same_delta =
        previous_input.delta_time_seconds == input.delta_time_seconds;
    const bool same_timeline =
        previous_input.timeline_time_seconds == input.timeline_time_seconds;
    const bool same_viewport =
        SameOptionalViewport(previous_input.viewport, input.viewport);
    const bool same_html =
        previous_input.html_override == input.html_override;
    const bool same_element_attributes =
        SameStringMap(previous_input.element_attributes_by_id_and_name,
                      input.element_attributes_by_id_and_name);
    const std::vector<html_css_renderer::Stylesheet>& previous_stylesheets =
        previous_input.stylesheets_override ? *previous_input.stylesheets_override
                                           : renderer_info_for_oracle.stylesheets;
    const std::vector<html_css_renderer::Stylesheet>& current_stylesheets =
        input.stylesheets_override ? *input.stylesheets_override
                                   : renderer_info_for_oracle.stylesheets;
    const bool same_stylesheets =
        SameStylesheetList(previous_stylesheets, current_stylesheets);
    const bool same_requested_css_file =
        !previous_css_file.empty() && previous_css_file == current_css_file;
    const bool same_scroll = SamePointMap(previous_input.scroll_offsets_by_element_id,
                                          input.scroll_offsets_by_element_id);
    const bool same_focus =
        previous_input.focused_element_id == input.focused_element_id;
    const bool same_hover =
        previous_input.hovered_element_id == input.hovered_element_id;
    const bool same_active =
        previous_input.active_element_id == input.active_element_id;
    const bool same_form =
        SameStringMap(previous_input.form_values_by_element_id,
                      input.form_values_by_element_id);
    const bool same_pointers =
        SamePointers(previous_input.pointers, input.pointers);
    const bool same_wheel = SameWheelInput(previous_input.wheel, input.wheel);
    identical_incremental_requested =
        same_delta && same_timeline && same_viewport && same_html &&
        same_element_attributes &&
        (same_stylesheets || same_requested_css_file) && same_scroll &&
        same_focus && same_hover && same_active && same_form &&
        same_pointers && same_wheel;
    previous_result = blink_embedder->AdvanceAndRender(previous_input);
    have_previous_result = true;
    render_start = BenchmarkClock::now();
    const int measured_incremental_frames =
        identical_incremental_requested ? repeat_no_change_frames : 1;
    for (int frame_index = 0; frame_index < measured_incremental_frames;
         ++frame_index) {
      result = blink_embedder->AdvanceAndRenderIncremental(input);
      AccumulateMeasuredFrameWork(timing, result);
    }
  } else {
    render_start = BenchmarkClock::now();
    result = blink_embedder->AdvanceAndRender(input);
    AccumulateMeasuredFrameWork(timing, result);
  }
  timing.advance_and_render_ms =
      ElapsedMs(render_start, BenchmarkClock::now());
  result.diagnostics.insert(result.diagnostics.begin(),
                            init.diagnostics.begin(), init.diagnostics.end());
  result.diagnostics.insert(result.diagnostics.begin(),
                            stylesheet_loader_diagnostics.begin(),
                            stylesheet_loader_diagnostics.end());
  if (!HasRealBlinkPaintArtifact(result) && !audit_only) {
    if (!paint_artifact_dump_path.empty()) {
      std::ofstream audit_file(paint_artifact_dump_path);
      if (audit_file) {
        audit_file << html_css_renderer::SerializePaintArtifactAuditJson(result)
                   << "\n";
      }
    }
    std::fprintf(stderr,
                 "strict Blink benchmark requires real Blink PaintArtifact "
                 "draw extraction; current output was "
                 "not rasterized.\n");
    PrintDiagnostics(result);
    return 4;
  }

  if (!paint_artifact_dump_path.empty()) {
    const auto audit_write_start = BenchmarkClock::now();
    std::ofstream audit_file(paint_artifact_dump_path);
    if (!audit_file) {
      std::fprintf(stderr, "failed to write paint artifact dump: %s\n",
                   paint_artifact_dump_path.c_str());
      return 1;
    }
    audit_file << html_css_renderer::SerializePaintArtifactAuditJson(result)
               << "\n";
    timing.audit_json_write_ms +=
        ElapsedMs(audit_write_start, BenchmarkClock::now());
  }
  if (!page_setup_dump_path.empty() &&
      true) {
    const auto page_setup_write_start = BenchmarkClock::now();
    const bool wrote_page_setup =
        WritePageSetupJson(page_setup_dump_path, renderer_info_for_oracle,
                           result, html_file, lifecycle_stop, true);
    timing.page_setup_json_write_ms +=
        ElapsedMs(page_setup_write_start, BenchmarkClock::now());
    if (!wrote_page_setup) {
      std::fprintf(stderr, "failed to write page setup dump: %s\n",
                   page_setup_dump_path.c_str());
      return 1;
    }
  }

  if (audit_only) {
    if (!json_path.empty()) {
      Metrics empty_metrics;
      empty_metrics.width = static_cast<int>(result.successor_snapshot.viewport.width);
      empty_metrics.height = static_cast<int>(result.successor_snapshot.viewport.height);
      timing.process_elapsed_ms =
          ElapsedMs(process_start, BenchmarkClock::now());
      const auto metrics_write_start = BenchmarkClock::now();
      const bool wrote_metrics =
          WriteJson(json_path, empty_metrics, result, loaded_font_path, timing);
      timing.metrics_json_write_ms =
          ElapsedMs(metrics_write_start, BenchmarkClock::now());
      if (!wrote_metrics) {
        std::fprintf(stderr, "failed to write metrics: %s\n", json_path.c_str());
        return 1;
      }
    }
    std::printf("render_metrics width=%d height=%d non_white=%zu unique=%zu\n",
                static_cast<int>(result.successor_snapshot.viewport.width),
                static_cast<int>(result.successor_snapshot.viewport.height),
                static_cast<size_t>(0), static_cast<size_t>(0));
    return 0;
  }

  if (retained_transform_mode == "record-only") {
    StripTransformCommandsForDiagnosticOracle(result);
  } else if (retained_transform_mode != "normal") {
    std::fprintf(stderr, "unknown retained transform mode: %s\n",
                 retained_transform_mode.c_str());
    return 2;
  }

  html_css_renderer::CpuRenderOptions cpu_options;
  cpu_options.strict_text_blob_typefaces = strict_text_blob_typefaces;
  cpu_options.debug_command_coverage = debug_command_coverage;
  cpu_options.disable_damage_clip_grouping = disable_damage_clip_grouping;
  std::optional<html_css_renderer::CpuImage> previous_image;
  if (incremental && have_previous_result) {
    previous_image =
        html_css_renderer::RasterizeRenderResultWithSkiaCpu(previous_result,
                                                            cpu_options);
  }
  const auto raster_start = BenchmarkClock::now();
  html_css_renderer::CpuImage image;
  if (identical_incremental_requested && previous_image) {
    timing.cpu_raster_replay_skipped = result.frame_work.no_change_fast_path &&
                                       !result.frame_work.needs_raster;
    image = *previous_image;
  } else {
    image = incremental && have_previous_result
                ? html_css_renderer::RasterizeRenderResultIncrementalWithSkiaCpu(
                      result, &*previous_image, cpu_options)
                : html_css_renderer::RasterizeRenderResultWithSkiaCpu(
                      result, cpu_options);
  }
  timing.cpu_raster_replay_ms =
      ElapsedMs(raster_start, BenchmarkClock::now());
  timing.cpu_raster_replay_skipped =
      timing.cpu_raster_replay_skipped || image.raster_skipped;
  timing.raster_pixels_touched =
      timing.cpu_raster_replay_skipped || image.raster_skipped
          ? 0
          : image.raster_pixels_touched;
  timing.damage_pixels =
      timing.cpu_raster_replay_skipped || image.raster_skipped
          ? 0
          : image.damage_pixels;
  timing.raw_damage_area =
      timing.cpu_raster_replay_skipped ? 0 : image.raw_damage_area;
  timing.coalesced_damage_area =
      timing.cpu_raster_replay_skipped ? 0 : image.coalesced_damage_area;
  timing.command_replay_count_before_grouping =
      timing.cpu_raster_replay_skipped
          ? 0
          : image.command_replay_count_before_grouping;
  timing.command_replay_count_after_grouping =
      timing.cpu_raster_replay_skipped
          ? 0
          : image.command_replay_count_after_grouping;
  timing.damage_clip_count =
      timing.cpu_raster_replay_skipped ? 0 : image.damage_clip_count;
  timing.replay_group_count =
      timing.cpu_raster_replay_skipped ? 0 : image.replay_group_count;
  timing.damage_grouping_ms =
      timing.cpu_raster_replay_skipped ? 0.0 : image.damage_grouping_ms;
  timing.skregion_clip_ms =
      timing.cpu_raster_replay_skipped ? 0.0 : image.skregion_clip_ms;
  timing.cpu_replay_ms =
      timing.cpu_raster_replay_skipped ? 0.0 : image.cpu_replay_ms;
  timing.copyback_ms =
      timing.cpu_raster_replay_skipped ? 0.0 : image.copyback_ms;
  timing.partial_raster =
      !timing.cpu_raster_replay_skipped && image.partial_raster;

  const Metrics metrics = ComputeMetrics(image);
  const auto output_write_start = BenchmarkClock::now();
  if (!WriteBmp(out_path, image)) {
    std::fprintf(stderr, "failed to write output image: %s\n", out_path.c_str());
    return 1;
  }
  timing.output_image_write_ms =
      ElapsedMs(output_write_start, BenchmarkClock::now());
  if (!json_path.empty()) {
    timing.process_elapsed_ms =
        ElapsedMs(process_start, BenchmarkClock::now());
    const auto metrics_write_start = BenchmarkClock::now();
    const bool wrote_metrics =
        WriteJson(json_path, metrics, result, loaded_font_path, timing);
    timing.metrics_json_write_ms =
        ElapsedMs(metrics_write_start, BenchmarkClock::now());
    if (!wrote_metrics) {
      std::fprintf(stderr, "failed to write metrics: %s\n", json_path.c_str());
      return 1;
    }
  }
  if (!paint_artifact_dump_path.empty()) {
    const auto audit_write_start = BenchmarkClock::now();
    std::ofstream audit_file(paint_artifact_dump_path);
    if (!audit_file) {
      std::fprintf(stderr, "failed to write paint artifact dump: %s\n",
                   paint_artifact_dump_path.c_str());
      return 1;
    }
    audit_file << html_css_renderer::SerializePaintArtifactAuditJson(result)
               << "\n";
    timing.audit_json_write_ms +=
        ElapsedMs(audit_write_start, BenchmarkClock::now());
  }
  if (!page_setup_dump_path.empty() &&
      true) {
    const auto page_setup_write_start = BenchmarkClock::now();
    const bool wrote_page_setup =
        WritePageSetupJson(page_setup_dump_path, renderer_info_for_oracle,
                           result, html_file, lifecycle_stop, true);
    timing.page_setup_json_write_ms +=
        ElapsedMs(page_setup_write_start, BenchmarkClock::now());
    if (!wrote_page_setup) {
      std::fprintf(stderr, "failed to write page setup dump: %s\n",
                   page_setup_dump_path.c_str());
      return 1;
    }
  }

  if (!paint_oracle.empty()) {
    if (paint_oracle == "skia-paint-record") {
      if (oracle_out_path.empty()) {
        std::fprintf(stderr, "--paint-oracle requires --oracle-out\n");
        return 2;
      }
      html_css_renderer::BlinkPageEmbedderCreateInfo oracle_create_info;
      oracle_create_info.renderer = renderer_info_for_oracle;
      oracle_create_info.trace_stages = trace_stages;
      oracle_create_info.debug_text_blob_replay = debug_text_blob_replay;
      oracle_create_info.force_paint_oracle_bitmap = false;
      std::unique_ptr<html_css_renderer::BlinkPageEmbedder> oracle_embedder =
          html_css_renderer::CreateLiveBlinkPageEmbedder(
              std::move(oracle_create_info));
      if (!oracle_embedder) {
        std::fprintf(stderr, "failed to create Blink oracle adapter\n");
        return 1;
      }
      (void)oracle_embedder->Initialize();
      const auto oracle_render_start = BenchmarkClock::now();
      html_css_renderer::RenderResult oracle_result =
          oracle_embedder->AdvanceAndRender(input);
      timing.oracle_advance_and_render_ms =
          ElapsedMs(oracle_render_start, BenchmarkClock::now());
      if (!HasRealBlinkPaintArtifact(oracle_result)) {
        std::fprintf(stderr,
                     "skia_paint_record_oracle failed before PaintArtifact\n");
        PrintDiagnostics(oracle_result);
        return 1;
      }
      if (paint_oracle_transform_mode == "record-only") {
        StripTransformCommandsForDiagnosticOracle(oracle_result);
      } else if (paint_oracle_transform_mode != "normal") {
        std::fprintf(stderr, "unknown paint oracle transform mode: %s\n",
                     paint_oracle_transform_mode.c_str());
        return 2;
      }
      html_css_renderer::CpuRenderOptions oracle_options;
      oracle_options.strict_text_blob_typefaces = strict_text_blob_typefaces;
      oracle_options.debug_command_coverage = false;
      const auto oracle_raster_start = BenchmarkClock::now();
      const html_css_renderer::CpuImage oracle_image =
          html_css_renderer::RasterizeRenderResultWithSkiaCpu(oracle_result,
                                                              oracle_options);
      timing.oracle_cpu_raster_replay_ms =
          ElapsedMs(oracle_raster_start, BenchmarkClock::now());
      const auto oracle_output_start = BenchmarkClock::now();
      if (!WriteBmp(oracle_out_path, oracle_image)) {
        std::fprintf(stderr, "failed to write oracle image: %s\n",
                     oracle_out_path.c_str());
        return 1;
      }
      timing.oracle_output_write_ms =
          ElapsedMs(oracle_output_start, BenchmarkClock::now());
      const Metrics oracle_metrics = ComputeMetrics(oracle_image);
      const std::string oracle_json_path = oracle_out_path + ".json";
      if (!WriteOracleProvenanceJson(oracle_json_path, oracle_metrics,
                                     oracle_result, paint_oracle,
                                     paint_oracle_transform_mode)) {
        std::fprintf(stderr, "failed to write oracle provenance: %s\n",
                     oracle_json_path.c_str());
        return 1;
      }
    } else if (paint_oracle == "blink-flattened-paint-record") {
      std::fprintf(
          stderr,
          "blink-flattened-paint-record oracle unavailable: "
          "PaintArtifact::GetPaintRecord is not linked in the standalone "
          "runtime and currently resolves to the live_link_boundary_stubs.cc "
          "empty stub\n");
      return 2;
    } else {
      std::fprintf(stderr, "unknown paint oracle: %s\n", paint_oracle.c_str());
      return 2;
    }
  }

  if (!json_path.empty()) {
    timing.process_elapsed_ms =
        ElapsedMs(process_start, BenchmarkClock::now());
    const auto metrics_write_start = BenchmarkClock::now();
    const bool wrote_metrics =
        WriteJson(json_path, metrics, result, loaded_font_path, timing);
    timing.metrics_json_write_ms =
        ElapsedMs(metrics_write_start, BenchmarkClock::now());
    if (!wrote_metrics) {
      std::fprintf(stderr, "failed to write metrics: %s\n", json_path.c_str());
      return 1;
    }
  }

  std::printf("render_metrics width=%d height=%d non_white=%zu unique=%zu\n",
              metrics.width, metrics.height, metrics.non_white_pixels,
              metrics.unique_color_sample);
  if (metrics.non_white_pixels < min_non_white) {
    std::fprintf(stderr,
                 "render output failed non-white threshold: %zu < %zu\n",
                 metrics.non_white_pixels, min_non_white);
    return 3;
  }
  return 0;
}
