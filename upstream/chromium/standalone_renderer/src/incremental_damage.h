#ifndef STANDALONE_RENDERER_SRC_INCREMENTAL_DAMAGE_H_
#define STANDALONE_RENDERER_SRC_INCREMENTAL_DAMAGE_H_

#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

bool SamePointMap(const std::unordered_map<std::string, Point>& a,
                  const std::unordered_map<std::string, Point>& b);
bool SameStringMap(
    const std::unordered_map<std::string, std::string>& a,
    const std::unordered_map<std::string, std::string>& b);
bool SameDocumentInputs(const RendererSnapshot& a, const RendererSnapshot& b);
bool SameVisualState(const RendererSnapshot& a, const RendererSnapshot& b);
Rect UnionRect(Rect a, Rect b);
Rect EstimateIncrementalDamage(const RendererSnapshot& previous,
                               const RendererSnapshot& successor,
                               const RenderResult& full_result);
void MarkFullRedraw(RenderResult& result, Rect viewport_rect);
void ApplyIncrementalDamage(const RendererSnapshot& previous,
                            RenderResult& result,
                            const char* diagnostic_prefix);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_SRC_INCREMENTAL_DAMAGE_H_
