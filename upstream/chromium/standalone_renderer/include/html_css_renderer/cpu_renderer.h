#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_CPU_RENDERER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_CPU_RENDERER_H_

#include <cstdint>
#include <vector>

#include "html_css_renderer/draw_command.h"
#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

struct CpuImage {
  int width = 0;
  int height = 0;
  std::vector<uint32_t> pixels_rgba;
  // Optional RGBA byte-order mirror used by retained Skia/SDL paths to reuse
  // the previous frame surface without reconstructing it from packed pixels.
  std::vector<uint8_t> pixels_rgba_bytes;
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
  bool raster_skipped = false;
  bool partial_raster = false;
};

struct CpuRenderOptions {
  Color clear_color = Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f);
  bool strict_text_blob_typefaces = true;
  bool debug_command_coverage = false;
  bool profile_command_timings = false;
  bool disable_damage_clip_grouping = false;
};

CpuImage RasterizeDrawCommands(const DrawCommandList& commands,
                               Size viewport,
                               CpuRenderOptions options = {});
CpuImage RasterizeRenderResult(const RenderResult& result,
                               CpuRenderOptions options = {});
CpuImage RasterizeRenderResultIncremental(const RenderResult& result,
                                          const CpuImage* previous,
                                          CpuRenderOptions options = {});

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_CPU_RENDERER_H_
