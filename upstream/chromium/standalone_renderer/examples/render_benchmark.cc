#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <unordered_set>
#include <vector>

#if defined(HTML_CSS_RENDERER_USE_BLINK_ADAPTER)
#include "html_css_renderer/blink_adapter.h"
#endif
#include "html_css_renderer/cpu_renderer.h"
#include "html_css_renderer/draw_command_serializer.h"
#include "html_css_renderer/renderer.h"
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
#include "html_css_renderer/skia_cpu_renderer.h"
#endif
#include "html_css_renderer/source_text_backend.h"

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

std::optional<std::string> ExtractAttribute(const std::string& tag,
                                            const std::string& name) {
  const std::string lower = ToLowerAscii(tag);
  const std::string needle = ToLowerAscii(name) + "=";
  const size_t attr = lower.find(needle);
  if (attr == std::string::npos) {
    return std::nullopt;
  }
  size_t value_start = attr + needle.size();
  if (value_start >= tag.size()) {
    return std::nullopt;
  }
  const char quote = tag[value_start];
  if (quote == '"' || quote == '\'') {
    ++value_start;
    const size_t value_end = tag.find(quote, value_start);
    if (value_end == std::string::npos) {
      return std::nullopt;
    }
    return tag.substr(value_start, value_end - value_start);
  }
  size_t value_end = value_start;
  while (value_end < tag.size() &&
         !std::isspace(static_cast<unsigned char>(tag[value_end])) &&
         tag[value_end] != '>') {
    ++value_end;
  }
  return tag.substr(value_start, value_end - value_start);
}

std::vector<std::string> ExtractLinkedStylesheetHrefs(const std::string& html) {
  std::vector<std::string> hrefs;
  const std::string lower = ToLowerAscii(html);
  size_t search_offset = 0;
  while (true) {
    const size_t link_start = lower.find("<link", search_offset);
    if (link_start == std::string::npos) {
      break;
    }
    const size_t link_end = lower.find('>', link_start);
    if (link_end == std::string::npos) {
      break;
    }
    const std::string tag = html.substr(link_start, link_end - link_start + 1);
    const std::string lower_tag = lower.substr(link_start,
                                               link_end - link_start + 1);
    const std::optional<std::string> rel = ExtractAttribute(tag, "rel");
    const std::optional<std::string> href = ExtractAttribute(tag, "href");
    if (href && rel && ToLowerAscii(*rel).find("stylesheet") !=
                           std::string::npos) {
      hrefs.push_back(*href);
    } else if (href && lower_tag.find("stylesheet") != std::string::npos) {
      hrefs.push_back(*href);
    }
    search_offset = link_end + 1;
  }
  return hrefs;
}

void AddLocalLinkedStylesheets(const std::string& html_path,
                               const std::string& html,
                               html_css_renderer::RendererCreateInfo*
                                   create_info) {
  const fs::path base_dir = fs::absolute(fs::path(html_path)).parent_path();
  for (const std::string& href : ExtractLinkedStylesheetHrefs(html)) {
    if (href.find("://") != std::string::npos || href.rfind("//", 0) == 0 ||
        href.rfind("data:", 0) == 0 || href.empty()) {
      continue;
    }
    fs::path css_path = fs::path(href);
    if (css_path.is_relative()) {
      css_path = base_dir / css_path;
    }
    std::optional<std::string> css = ReadTextFile(css_path.string());
    if (!css) {
      continue;
    }
    create_info->stylesheets.push_back({css_path.string(), std::move(*css)});
  }
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

bool WriteJson(const std::string& path,
               const Metrics& metrics,
               const html_css_renderer::RenderResult& result,
               const std::string& font_path) {
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

void PrintUsage() {
  std::fprintf(stderr,
               "Usage: blink_standalone_render_benchmark_skia --html <html> "
               "[--html-file <path>] [--css <css>] [--css-file <path>] "
               "[--viewport WxH] --out <out.bmp> "
               "[--json <metrics.json>] [--min-non-white pixels] "
               "[--font-file path]"
#if defined(HTML_CSS_RENDERER_USE_BLINK_ADAPTER)
               " [--blink] [--manual]"
#endif
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
               " [--skia-cpu]"
#endif
               "\n");
}

}  // namespace

int main(int argc, char** argv) {
  BenchmarkAssets assets;
  html_css_renderer::RendererCreateInfo create_info;
  create_info.asset_provider = &assets;
  create_info.viewport = {800.0f, 600.0f};
  html_css_renderer::FrameInput input;
  std::string out_path;
  std::string json_path;
  std::string font_file;
  size_t min_non_white = 1;
  bool use_skia_cpu = false;
#if defined(HTML_CSS_RENDERER_USE_BLINK_ADAPTER)
  bool use_blink = true;
#else
  bool use_blink = false;
#endif

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
      create_info.html = std::move(*html);
      AddLocalLinkedStylesheets(value, create_info.html, &create_info);
    } else if (arg == "--css") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      create_info.stylesheets.push_back({"benchmark", value});
    } else if (arg == "--css-file") {
      const char* value = next_value();
      if (!value) {
        PrintUsage();
        return 2;
      }
      std::optional<std::string> css = ReadTextFile(value);
      if (!css) {
        std::fprintf(stderr, "failed to read css file: %s\n", value);
        return 2;
      }
      create_info.stylesheets.push_back({value, std::move(*css)});
    } else if (arg == "--viewport") {
      const char* value = next_value();
      if (!value || !ParseViewport(value, &create_info.viewport)) {
        PrintUsage();
        return 2;
      }
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
    } else if (arg == "--skia-cpu") {
      use_skia_cpu = true;
#if defined(HTML_CSS_RENDERER_USE_BLINK_ADAPTER)
    } else if (arg == "--blink") {
      use_blink = true;
    } else if (arg == "--manual") {
      use_blink = false;
#endif
    } else {
      PrintUsage();
      return 2;
    }
  }

  if (create_info.html.empty() || out_path.empty()) {
    PrintUsage();
    return 2;
  }

  std::string loaded_font_path;
  if (!font_file.empty()) {
    assets.font_bytes = ReadBinaryFile(font_file);
    loaded_font_path = font_file;
  }
  std::unique_ptr<html_css_renderer::SourceTextBackend> text_backend =
      html_css_renderer::CreateSourceTextBackend();
  if (text_backend) {
    create_info.font_provider = text_backend.get();
    create_info.text_shaper = text_backend.get();
    create_info.glyph_rasterizer = text_backend.get();
  }

  html_css_renderer::RenderResult result;
#if defined(HTML_CSS_RENDERER_USE_BLINK_ADAPTER)
  std::unique_ptr<html_css_renderer::BlinkPageEmbedder> blink_embedder;
  if (use_blink) {
    html_css_renderer::BlinkPageEmbedderCreateInfo blink_create_info;
    blink_create_info.renderer = std::move(create_info);
    blink_embedder =
        html_css_renderer::CreateLiveBlinkPageEmbedder(std::move(blink_create_info));
    if (!blink_embedder) {
      std::fprintf(stderr, "failed to create Blink adapter\n");
      return 1;
    }
    const html_css_renderer::BlinkLifecycleReport init =
        blink_embedder->Initialize();
    result = blink_embedder->AdvanceAndRender(input);
    result.diagnostics.insert(result.diagnostics.begin(),
                              init.diagnostics.begin(), init.diagnostics.end());
    if (!HasRealBlinkPaintArtifact(result)) {
      std::fprintf(stderr,
                   "strict Blink benchmark requires real Blink PaintArtifact "
                   "draw extraction; current output was "
                   "not rasterized.\n");
      PrintDiagnostics(result);
      return 4;
    }
  } else
#endif
  {
    std::unique_ptr<html_css_renderer::RendererState> state =
        html_css_renderer::RendererState::Create(std::move(create_info));
    result = state->AdvanceAndRender(input);
  }

  html_css_renderer::CpuImage image =
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
      use_skia_cpu ? html_css_renderer::RasterizeRenderResultWithSkiaCpu(result)
                   :
#endif
                   html_css_renderer::RasterizeRenderResult(result);

  const Metrics metrics = ComputeMetrics(image);
  if (!WriteBmp(out_path, image)) {
    std::fprintf(stderr, "failed to write output image: %s\n", out_path.c_str());
    return 1;
  }
  if (!json_path.empty() && !WriteJson(json_path, metrics, result,
                                       loaded_font_path)) {
    std::fprintf(stderr, "failed to write metrics: %s\n", json_path.c_str());
    return 1;
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
