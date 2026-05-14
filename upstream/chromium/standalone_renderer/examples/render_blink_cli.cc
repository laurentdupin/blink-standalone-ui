#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "html_css_renderer/blink_adapter.h"
#include "html_css_renderer/draw_command_serializer.h"

namespace {

class CliAssets final : public html_css_renderer::AssetProvider {
 public:
  std::optional<html_css_renderer::Asset> Load(
      const std::string& resource_id) override {
    const auto found = assets.find(resource_id);
    if (found == assets.end()) {
      return std::nullopt;
    }
    html_css_renderer::Asset asset;
    asset.id = resource_id;
    asset.mime_type = found->second.mime_type;
    asset.bytes = found->second.bytes;
    return asset;
  }

  struct StoredAsset {
    std::string mime_type;
    std::vector<uint8_t> bytes;
  };

  std::unordered_map<std::string, StoredAsset> assets;
};

std::vector<uint8_t> ReadBinaryFile(const std::string& path) {
  std::ifstream file(path, std::ios::binary);
  if (!file) {
    return {};
  }
  return std::vector<uint8_t>(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>());
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

bool ParseDouble(const std::string& value, double* output) {
  char* end = nullptr;
  const double parsed = std::strtod(value.c_str(), &end);
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

bool ParseAssetSpec(const std::string& value,
                    std::string* resource_id,
                    std::string* path,
                    std::string* mime_type) {
  const size_t equals = value.find('=');
  if (equals == std::string::npos || equals == 0 ||
      equals + 1 >= value.size()) {
    return false;
  }
  *resource_id = value.substr(0, equals);
  std::string path_and_mime = value.substr(equals + 1);
  *mime_type = "application/octet-stream";

  const size_t comma = path_and_mime.rfind(',');
  if (comma != std::string::npos && comma + 1 < path_and_mime.size()) {
    *path = path_and_mime.substr(0, comma);
    *mime_type = path_and_mime.substr(comma + 1);
  } else {
    *path = path_and_mime;
  }
  return !path->empty() && !mime_type->empty();
}

void PrintUsage() {
  std::fprintf(stderr,
               "Usage: html_css_renderer_blink_cli --html <html> "
               "[--css <css>] [--viewport WxH] [--delta seconds] "
               "[--time seconds] [--hover id] [--focus id] [--active id] "
               "[--asset id=path[,mime]] [--incremental]\n");
}

}  // namespace

int main(int argc, char** argv) {
  CliAssets assets;
  html_css_renderer::BlinkPageEmbedderCreateInfo create_info;
  create_info.renderer.asset_provider = &assets;
  html_css_renderer::FrameInput input;
  bool incremental = false;
  std::vector<std::string> asset_specs;

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
      create_info.renderer.html = value;
    } else if (arg == "--css") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      create_info.renderer.stylesheets.push_back({"cli", value});
    } else if (arg == "--viewport") {
      const char* value = next_value();
      if (!value || !ParseViewport(value, &create_info.renderer.viewport)) {
        PrintUsage();
        return 2;
      }
    } else if (arg == "--delta") {
      const char* value = next_value();
      if (!value || !ParseDouble(value, &input.delta_time_seconds)) {
        PrintUsage();
        return 2;
      }
    } else if (arg == "--time") {
      const char* value = next_value();
      if (!value || !ParseDouble(value, &input.timeline_time_seconds)) {
        PrintUsage();
        return 2;
      }
    } else if (arg == "--hover") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      input.hovered_element_id = value;
    } else if (arg == "--focus") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      input.focused_element_id = value;
    } else if (arg == "--active") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      input.active_element_id = value;
    } else if (arg == "--asset") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      asset_specs.push_back(value);
    } else if (arg == "--incremental") {
      incremental = true;
    } else if (arg == "--help" || arg == "-h") {
      PrintUsage();
      return 0;
    } else {
      PrintUsage();
      return 2;
    }
  }

  if (create_info.renderer.html.empty()) {
    PrintUsage();
    return 2;
  }

  for (const std::string& spec : asset_specs) {
    std::string resource_id;
    std::string path;
    std::string mime_type;
    if (!ParseAssetSpec(spec, &resource_id, &path, &mime_type)) {
      PrintUsage();
      return 2;
    }
    CliAssets::StoredAsset asset;
    asset.mime_type = mime_type;
    asset.bytes = ReadBinaryFile(path);
    if (asset.bytes.empty()) {
      std::fprintf(stderr, "failed to read asset file for %s: %s\n",
                   resource_id.c_str(), path.c_str());
      return 2;
    }
    assets.assets[resource_id] = std::move(asset);
  }

  std::unique_ptr<html_css_renderer::BlinkPageEmbedder> embedder =
      html_css_renderer::CreateLiveBlinkPageEmbedder(std::move(create_info));
  if (!embedder) {
    std::fprintf(stderr, "failed to create Blink adapter\n");
    return 1;
  }

  const html_css_renderer::BlinkLifecycleReport init = embedder->Initialize();
  html_css_renderer::RenderResult result =
      incremental ? embedder->AdvanceAndRenderIncremental(input)
                  : embedder->AdvanceAndRender(input);
  result.diagnostics.insert(result.diagnostics.begin(),
                            init.diagnostics.begin(), init.diagnostics.end());

  const std::string output =
      html_css_renderer::SerializeRenderResultJson(result);
  std::printf("%s\n", output.c_str());
  return result.missing_resources.empty() ? 0 : 1;
}
