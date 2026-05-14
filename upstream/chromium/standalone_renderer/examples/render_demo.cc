#include <cstdio>
#include <optional>
#include <string>

#include "html_css_renderer/draw_command_serializer.h"
#include "html_css_renderer/renderer.h"

namespace {

class DemoAssets final : public html_css_renderer::AssetProvider {
 public:
  std::optional<html_css_renderer::Asset> Load(
      const std::string& resource_id) override {
    if (resource_id != "logo.png") {
      return std::nullopt;
    }
    html_css_renderer::Asset asset;
    asset.id = resource_id;
    asset.mime_type = "image/png";
    asset.bytes = {0x89, 'P', 'N', 'G'};
    return asset;
  }
};

}  // namespace

int main() {
  DemoAssets assets;

  html_css_renderer::RendererCreateInfo create_info;
  create_info.html =
      "<main onclick=\"alert(1)\"><script>alert(1)</script>"
      "<img src=\"logo.png\"><h1>Hello renderer</h1></main>";
  create_info.stylesheets.push_back({"demo", "body { background: #f5f7fb; }"});
  create_info.asset_provider = &assets;

  auto state = html_css_renderer::RendererState::Create(std::move(create_info));
  html_css_renderer::FrameInput input;
  input.delta_time_seconds = 1.0 / 60.0;
  input.hovered_element_id = "document-text";

  const auto result = state->AdvanceAndRender(input);
  const std::string output = html_css_renderer::SerializeRenderResultJson(result);
  std::printf("%s\n", output.c_str());
  return result.missing_resources.empty() ? 0 : 1;
}
