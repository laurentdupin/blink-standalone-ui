#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SKIA_CPU_RENDERER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SKIA_CPU_RENDERER_H_

#include "html_css_renderer/cpu_renderer.h"
#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

CpuImage RasterizeDrawCommandsWithSkiaCpu(
    const DrawCommandList& commands,
    Size viewport,
    CpuRenderOptions options = {});
CpuImage RasterizeRenderResultWithSkiaCpu(
    const RenderResult& result,
    CpuRenderOptions options = {});

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_SKIA_CPU_RENDERER_H_
