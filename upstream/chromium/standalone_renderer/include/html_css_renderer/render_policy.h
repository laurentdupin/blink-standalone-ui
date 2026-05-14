#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_POLICY_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_POLICY_H_

#include <optional>
#include <string>
#include <vector>

#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

struct SanitizedDocument {
  std::string html;
  std::vector<std::string> diagnostics;
};

struct SanitizedStylesheet {
  Stylesheet stylesheet;
  std::vector<std::string> diagnostics;
};

struct ResourceReference {
  std::string id;
  std::string element_kind;
};

struct ResourceResolution {
  ResourceReference reference;
  std::optional<Asset> asset;
  std::string diagnostic;
};

struct FrameStateUpdate {
  double timeline_time_seconds = 0.0;
  Size viewport;
  std::vector<PointerState> pointers;
  KeyboardState keyboard;
  std::unordered_map<std::string, Point> scroll_offsets_by_element_id;
  std::string focused_element_id;
  std::string hovered_element_id;
  std::string active_element_id;
  std::unordered_map<std::string, std::string> form_values_by_element_id;
  std::vector<std::string> diagnostics;
};

std::string ToLowerAscii(std::string value);
SanitizedDocument SanitizeHtmlForRendering(const std::string& html);
SanitizedStylesheet SanitizeStylesheetForRendering(const Stylesheet& stylesheet);
std::vector<SanitizedStylesheet> SanitizeStylesheetsForRendering(
    const std::vector<Stylesheet>& stylesheets);
std::string ExtractDocumentText(const std::string& html);
std::vector<ResourceReference> ExtractResourceReferences(
    const std::string& html,
    const std::vector<Stylesheet>& stylesheets = {});
bool IsPermittedResourceReference(const std::string& resource_id);
std::vector<ResourceResolution> ResolveResourceReferences(
    const std::vector<ResourceReference>& references,
    AssetProvider* asset_provider);
FrameStateUpdate BuildFrameStateUpdate(const RendererSnapshot& current,
                                       const FrameInput& input);
bool HasScriptCapableHtmlSurface(const std::string& html);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_POLICY_H_
