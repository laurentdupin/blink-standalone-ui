#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_SERIALIZER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_SERIALIZER_H_

#include <string>

#include "html_css_renderer/draw_command.h"
#include "html_css_renderer/load_command.h"
#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

std::string SerializeDrawCommandJson(const DrawCommand& command);
std::string SerializeLoadCommandJson(const LoadCommand& command);
std::string SerializeLoadCommandListJsonLines(
    const LoadCommandList& commands);
std::string SerializeDrawCommandListJsonLines(
    const DrawCommandList& commands);
std::string SerializeRenderResultJson(const RenderResult& result);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_DRAW_COMMAND_SERIALIZER_H_
