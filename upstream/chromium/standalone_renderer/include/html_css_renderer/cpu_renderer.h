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
};

struct CpuRenderOptions {
  Color clear_color = Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f);
  bool strict_text_blob_typefaces = true;
  bool debug_command_coverage = false;
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
