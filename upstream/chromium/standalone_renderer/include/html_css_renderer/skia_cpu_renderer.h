#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SKIA_CPU_RENDERER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SKIA_CPU_RENDERER_H_

#include "html_css_renderer/cpu_renderer.h"
#include "html_css_renderer/renderer.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace html_css_renderer {

struct CommandCoverageRecord {
  int command_index = 0;
  std::string command_type;
  Rect bounds;
  std::array<float, 9> active_matrix = {
      1.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f,
  };
  bool has_active_clip = false;
  Rect active_clip_bounds;
  int save_depth_before = 0;
  int save_depth_after = 0;
  uint64_t pixels_changed = 0;
  bool skipped = false;
  std::string skip_reason;
  bool shader_resource_present = false;
  uint64_t shader_byte_count = 0;
  bool shader_deserialize_success = false;
  bool text_blob_resource_present = false;
  uint64_t text_blob_byte_count = 0;
  bool text_blob_deserialize_success = false;
  bool image_resource_present = false;
  uint64_t image_byte_count = 0;
  bool image_resource_cache_hit = false;
  bool image_resource_cache_miss = false;
  int image_width = 0;
  int image_height = 0;
};

void ResetCommandCoverageDiagnostics();
std::vector<CommandCoverageRecord> SnapshotCommandCoverageDiagnostics();

CpuImage RasterizeDrawCommandsWithSkiaCpu(
    const DrawCommandList& commands,
    Size viewport,
    CpuRenderOptions options = {});
CpuImage RasterizeRenderResultWithSkiaCpu(
    const RenderResult& result,
    CpuRenderOptions options = {});

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SKIA_CPU_RENDERER_H_
