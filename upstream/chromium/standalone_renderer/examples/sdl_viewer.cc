#include <SDL3/SDL.h>

#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cctype>
#include <array>
#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <optional>
#include <unordered_map>
#include <string>
#include <utility>
#include <vector>

#include "html_css_renderer/blink_adapter.h"
#include "html_css_renderer/cpu_renderer.h"
#include "html_css_renderer/draw_command_serializer.h"
#include "html_css_renderer/renderer.h"
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
#include "html_css_renderer/skia_cpu_renderer.h"
#endif

namespace {

namespace fs = std::filesystem;

class EmptyAssets final : public html_css_renderer::AssetProvider {
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
    const std::optional<std::string> rel = ExtractAttribute(tag, "rel");
    const std::optional<std::string> href = ExtractAttribute(tag, "href");
    if (href && rel &&
        ToLowerAscii(*rel).find("stylesheet") != std::string::npos) {
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
    if (css) {
      create_info->stylesheets.push_back({css_path.string(), std::move(*css)});
    }
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

void PrintUsage() {
  std::fprintf(stderr,
               "Usage: html_css_renderer_sdl_viewer --html <html> "
               "[--html-file <path>] [--css <css>] [--css-file <path>] "
               "[--viewport WxH] [--delta seconds] "
               "[--font-file path] [--window-scale factor] "
               "[--quit-after-ms ms] [--incremental] [--cpu] [--skia-cpu]"
               " [--dump-paint-artifact path]"
               " [--blink]"
               "\n");
}

bool ParseArgs(int argc,
               char** argv,
               html_css_renderer::RendererCreateInfo* create_info,
               html_css_renderer::FrameInput* input,
               uint64_t* quit_after_ms,
               float* window_scale,
               std::string* font_file,
               bool* incremental,
               bool* use_cpu,
               bool* use_skia_cpu,
               std::string* paint_artifact_dump_path,
               bool* use_blink) {
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
        return false;
      }
      create_info->html = value;
    } else if (arg == "--html-file") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      std::optional<std::string> html = ReadTextFile(value);
      if (!html) {
        std::fprintf(stderr, "failed to read html file: %s\n", value);
        return false;
      }
      create_info->html = std::move(*html);
      AddLocalLinkedStylesheets(value, create_info->html, create_info);
    } else if (arg == "--css") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      create_info->stylesheets.push_back({"viewer", value});
    } else if (arg == "--css-file") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      std::optional<std::string> css = ReadTextFile(value);
      if (!css) {
        std::fprintf(stderr, "failed to read css file: %s\n", value);
        return false;
      }
      create_info->stylesheets.push_back({value, std::move(*css)});
    } else if (arg == "--viewport") {
      const char* value = next_value();
      if (!value || !ParseViewport(value, &create_info->viewport)) {
        return false;
      }
    } else if (arg == "--delta") {
      const char* value = next_value();
      if (!value || !ParseDouble(value, &input->delta_time_seconds)) {
        return false;
      }
    } else if (arg == "--quit-after-ms") {
      const char* value = next_value();
      double parsed = 0.0;
      if (!value || !ParseDouble(value, &parsed) || parsed < 0.0) {
        return false;
      }
      *quit_after_ms = static_cast<uint64_t>(parsed);
    } else if (arg == "--window-scale") {
      const char* value = next_value();
      float parsed = 0.0f;
      if (!value || !ParseFloat(value, &parsed) || parsed <= 0.0f ||
          parsed > 16.0f) {
        return false;
      }
      *window_scale = parsed;
    } else if (arg == "--font-file") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      *font_file = value;
    } else if (arg == "--incremental") {
      *incremental = true;
    } else if (arg == "--cpu") {
      *use_cpu = true;
    } else if (arg == "--skia-cpu") {
      *use_skia_cpu = true;
      *use_cpu = true;
    } else if (arg == "--dump-paint-artifact") {
      const char* value = next_value();
      if (!value) {
        return false;
      }
      *paint_artifact_dump_path = value;
    } else if (arg.rfind("--dump-paint-artifact=", 0) == 0) {
      *paint_artifact_dump_path = arg.substr(22);
    } else if (arg == "--blink") {
      *use_blink = true;
    } else if (arg == "--manual") {
      std::fprintf(stderr,
                   "--manual is no longer supported; live Blink is required\n");
      return false;
    } else if (arg == "--help" || arg == "-h") {
      return false;
    } else {
      return false;
    }
  }
  return !create_info->html.empty();
}

std::vector<uint32_t> ConvertRgbaToAbgr(
    const html_css_renderer::CpuImage& image) {
  std::vector<uint32_t> pixels;
  pixels.reserve(image.pixels_rgba.size());
  for (const uint32_t rgba : image.pixels_rgba) {
    const uint32_t r = (rgba >> 24) & 0xff;
    const uint32_t g = (rgba >> 16) & 0xff;
    const uint32_t b = (rgba >> 8) & 0xff;
    const uint32_t a = rgba & 0xff;
    pixels.push_back((a << 24) | (b << 16) | (g << 8) | r);
  }
  return pixels;
}

uint8_t ClampByte(float value) {
  const float clamped = std::max(0.0f, std::min(1.0f, value));
  return static_cast<uint8_t>(std::round(clamped * 255.0f));
}

SDL_FRect ToSdlRect(html_css_renderer::Rect rect) {
  return SDL_FRect{rect.x, rect.y, rect.width, rect.height};
}

void SetSdlColor(SDL_Renderer* renderer,
                 html_css_renderer::Color color,
                 float opacity = 1.0f) {
  SDL_SetRenderDrawColor(renderer, ClampByte(color.r), ClampByte(color.g),
                         ClampByte(color.b), ClampByte(color.a * opacity));
}

std::vector<uint32_t> ConvertRawRgbaBytesToAbgr(
    const std::vector<uint8_t>& pixels) {
  std::vector<uint32_t> out;
  out.reserve(pixels.size() / 4u);
  for (size_t i = 0; i + 3 < pixels.size(); i += 4) {
    const uint32_t r = pixels[i + 0];
    const uint32_t g = pixels[i + 1];
    const uint32_t b = pixels[i + 2];
    const uint32_t a = pixels[i + 3];
    out.push_back((a << 24) | (b << 16) | (g << 8) | r);
  }
  return out;
}

std::vector<uint32_t> ConvertAlphaMaskToAbgr(
    const std::vector<uint8_t>& pixels,
    html_css_renderer::Color color) {
  std::vector<uint32_t> out;
  out.reserve(pixels.size());
  const uint32_t r = ClampByte(color.r);
  const uint32_t g = ClampByte(color.g);
  const uint32_t b = ClampByte(color.b);
  for (uint8_t alpha : pixels) {
    const uint32_t a =
        static_cast<uint32_t>(std::round(alpha * std::max(0.0f, std::min(1.0f, color.a))));
    out.push_back((a << 24) | (b << 16) | (g << 8) | r);
  }
  return out;
}

class SdlFrameRenderer {
 public:
  explicit SdlFrameRenderer(SDL_Renderer* renderer) : renderer_(renderer) {}
  SdlFrameRenderer(const SdlFrameRenderer&) = delete;
  SdlFrameRenderer& operator=(const SdlFrameRenderer&) = delete;
  ~SdlFrameRenderer() { Clear(); }

  bool Render(const html_css_renderer::RenderResult& result,
              SDL_Texture* target) {
    ApplyResourceCommands(result.frame.resource_commands);

    if (!SDL_SetRenderTarget(renderer_, target)) {
      std::fprintf(stderr, "SDL_SetRenderTarget failed: %s\n", SDL_GetError());
      return false;
    }
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);

    RenderState state;
    std::vector<RenderState> state_stack;
    for (const html_css_renderer::SceneCommand& scene :
         result.frame.scene_commands) {
      if (scene.type != html_css_renderer::SceneCommandType::kDrawCommand) {
        continue;
      }
      DrawCommand(scene.draw_command, state_stack, state);
    }
    SDL_SetRenderClipRect(renderer_, nullptr);
    SDL_SetRenderTarget(renderer_, nullptr);
    return true;
  }

 private:
  struct TextureResource {
    SDL_Texture* texture = nullptr;
    int width = 0;
    int height = 0;
    html_css_renderer::Rect bounds;
  };

  struct RenderState {
    html_css_renderer::Matrix4 transform;
    std::optional<SDL_Rect> clip;
    float opacity = 1.0f;
  };

  void Clear() {
    for (auto& entry : images_) {
      SDL_DestroyTexture(entry.second.texture);
    }
    for (auto& entry : glyphs_) {
      SDL_DestroyTexture(entry.second.texture);
    }
    images_.clear();
    glyphs_.clear();
  }

  static std::string GlyphKey(const std::string& font_id, uint32_t glyph_id) {
    return font_id + "#" + std::to_string(glyph_id);
  }

  TextureResource CreateTextureFromAbgr(const std::vector<uint32_t>& pixels,
                                        int width,
                                        int height) {
    TextureResource resource;
    if (width <= 0 || height <= 0 ||
        pixels.size() < static_cast<size_t>(width * height)) {
      return resource;
    }
    resource.texture = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_ABGR8888,
                                         SDL_TEXTUREACCESS_STATIC, width,
                                         height);
    if (!resource.texture) {
      std::fprintf(stderr, "SDL_CreateTexture resource failed: %s\n",
                   SDL_GetError());
      return resource;
    }
    SDL_SetTextureBlendMode(resource.texture, SDL_BLENDMODE_BLEND);
    SDL_UpdateTexture(resource.texture, nullptr, pixels.data(),
                      width * static_cast<int>(sizeof(uint32_t)));
    resource.width = width;
    resource.height = height;
    return resource;
  }

  void ApplyResourceCommands(
      const std::vector<html_css_renderer::ResourceCommand>& commands) {
    for (const html_css_renderer::ResourceCommand& resource : commands) {
      if (resource.type == html_css_renderer::ResourceCommandType::kDestroyResource) {
        if (auto found = images_.find(resource.resource_id);
            found != images_.end()) {
          SDL_DestroyTexture(found->second.texture);
          images_.erase(found);
        }
        continue;
      }
      if (resource.type ==
              html_css_renderer::ResourceCommandType::kCreateOrUpdateImage &&
          resource.load_command.type == html_css_renderer::LoadCommandType::kLoadImage) {
        const html_css_renderer::ImageLoadInfo& image =
            resource.load_command.image;
        if (image.decoded_format != html_css_renderer::PixelFormat::kRgba8888) {
          continue;
        }
        const int width = static_cast<int>(std::floor(image.decoded_size.width));
        const int height =
            static_cast<int>(std::floor(image.decoded_size.height));
        TextureResource texture =
            CreateTextureFromAbgr(ConvertRawRgbaBytesToAbgr(image.decoded_pixels),
                                  width, height);
        if (texture.texture) {
          if (auto found = images_.find(resource.resource_id);
              found != images_.end()) {
            SDL_DestroyTexture(found->second.texture);
          }
          images_[resource.resource_id] = texture;
        }
      } else if (
          resource.type ==
              html_css_renderer::ResourceCommandType::kCreateOrUpdateGlyphAtlas &&
          resource.load_command.type ==
              html_css_renderer::LoadCommandType::kGlyphAtlasUpdate) {
        const html_css_renderer::GlyphAtlasUpdate& glyph =
            resource.load_command.glyph_atlas_update;
        if (glyph.format != html_css_renderer::PixelFormat::kAlpha8) {
          continue;
        }
        const int width = static_cast<int>(std::floor(glyph.bounds.width));
        const int height = static_cast<int>(std::floor(glyph.bounds.height));
        TextureResource texture = CreateTextureFromAbgr(
            ConvertAlphaMaskToAbgr(glyph.pixels,
                                   html_css_renderer::Color::Rgba(1, 1, 1, 1)),
            width, height);
        if (texture.texture) {
          texture.bounds = glyph.bounds;
          const std::string key = GlyphKey(glyph.font_id, glyph.glyph_id);
          if (auto found = glyphs_.find(key); found != glyphs_.end()) {
            SDL_DestroyTexture(found->second.texture);
          }
          glyphs_[key] = texture;
        }
      }
    }
  }

  static bool IsIdentity(const html_css_renderer::Matrix4& matrix) {
    const auto& m = matrix.values;
    return m[0] == 1.0f && m[1] == 0.0f && m[4] == 0.0f &&
           m[5] == 1.0f && m[12] == 0.0f && m[13] == 0.0f;
  }

  static html_css_renderer::Point TransformPoint(
      const html_css_renderer::Matrix4& matrix,
      html_css_renderer::Point point) {
    const auto& m = matrix.values;
    return {m[0] * point.x + m[4] * point.y + m[12],
            m[1] * point.x + m[5] * point.y + m[13]};
  }

  static html_css_renderer::Matrix4 Multiply(
      const html_css_renderer::Matrix4& a,
      const html_css_renderer::Matrix4& b) {
    html_css_renderer::Matrix4 out;
    for (int row = 0; row < 4; ++row) {
      for (int col = 0; col < 4; ++col) {
        float value = 0.0f;
        for (int k = 0; k < 4; ++k) {
          value += a.values[k * 4 + row] * b.values[col * 4 + k];
        }
        out.values[col * 4 + row] = value;
      }
    }
    return out;
  }

  static std::array<html_css_renderer::Point, 4> TransformRectCorners(
      const html_css_renderer::Matrix4& matrix,
      html_css_renderer::Rect rect) {
    return {TransformPoint(matrix, {rect.x, rect.y}),
            TransformPoint(matrix, {rect.x + rect.width, rect.y}),
            TransformPoint(matrix,
                           {rect.x + rect.width, rect.y + rect.height}),
            TransformPoint(matrix, {rect.x, rect.y + rect.height})};
  }

  static SDL_Rect BoundsForTransformedRect(
      const html_css_renderer::Matrix4& matrix,
      html_css_renderer::Rect rect) {
    const auto points = TransformRectCorners(matrix, rect);
    float min_x = points[0].x;
    float min_y = points[0].y;
    float max_x = points[0].x;
    float max_y = points[0].y;
    for (const html_css_renderer::Point& point : points) {
      min_x = std::min(min_x, point.x);
      min_y = std::min(min_y, point.y);
      max_x = std::max(max_x, point.x);
      max_y = std::max(max_y, point.y);
    }
    const int left = static_cast<int>(std::floor(min_x));
    const int top = static_cast<int>(std::floor(min_y));
    const int right = static_cast<int>(std::ceil(max_x));
    const int bottom = static_cast<int>(std::ceil(max_y));
    return SDL_Rect{left, top, std::max(0, right - left),
                    std::max(0, bottom - top)};
  }

  static SDL_FColor ToSdlColor(html_css_renderer::Color color,
                               float opacity) {
    return SDL_FColor{std::max(0.0f, std::min(1.0f, color.r)),
                      std::max(0.0f, std::min(1.0f, color.g)),
                      std::max(0.0f, std::min(1.0f, color.b)),
                      std::max(0.0f,
                               std::min(1.0f, color.a * opacity))};
  }

  void DrawQuad(SDL_Texture* texture,
                html_css_renderer::Rect rect,
                html_css_renderer::Color color,
                const RenderState& state) {
    const auto points = TransformRectCorners(state.transform, rect);
    const SDL_FColor vertex_color = ToSdlColor(color, state.opacity);
    SDL_Vertex vertices[4] = {
        {SDL_FPoint{points[0].x, points[0].y}, vertex_color,
         SDL_FPoint{0.0f, 0.0f}},
        {SDL_FPoint{points[1].x, points[1].y}, vertex_color,
         SDL_FPoint{1.0f, 0.0f}},
        {SDL_FPoint{points[2].x, points[2].y}, vertex_color,
         SDL_FPoint{1.0f, 1.0f}},
        {SDL_FPoint{points[3].x, points[3].y}, vertex_color,
         SDL_FPoint{0.0f, 1.0f}},
    };
    constexpr int indices[6] = {0, 1, 2, 0, 2, 3};
    SDL_RenderGeometry(renderer_, texture, vertices, 4, indices, 6);
  }

  void FillRect(const html_css_renderer::DrawCommand& command,
                const RenderState& state) {
    if (IsIdentity(state.transform)) {
      SetSdlColor(renderer_, command.color, state.opacity);
      SDL_FRect rect = ToSdlRect(command.rect);
      SDL_RenderFillRect(renderer_, &rect);
      return;
    }
    DrawQuad(nullptr, command.rect, command.color, state);
  }

  void DrawRRectApprox(const html_css_renderer::DrawCommand& command,
                       bool stroke,
                       const RenderState& state) {
    if (!stroke) {
      FillRect(command, state);
      return;
    }
    SetSdlColor(renderer_, command.color, state.opacity);
    const float w = std::max(1.0f, command.stroke_width);
    const html_css_renderer::Rect r = command.rect;
    std::array<SDL_FRect, 4> sides = {
        SDL_FRect{r.x, r.y, r.width, w},
        SDL_FRect{r.x, r.y + r.height - w, r.width, w},
        SDL_FRect{r.x, r.y, w, r.height},
        SDL_FRect{r.x + r.width - w, r.y, w, r.height},
    };
    if (IsIdentity(state.transform)) {
      for (SDL_FRect& side : sides) {
        SDL_RenderFillRect(renderer_, &side);
      }
    } else {
      for (SDL_FRect& side : sides) {
        DrawQuad(nullptr, html_css_renderer::Rect{side.x, side.y, side.w,
                                                  side.h},
                 command.color, state);
      }
    }
  }

  static SDL_Rect IntersectClip(SDL_Rect a, SDL_Rect b) {
    const int left = std::max(a.x, b.x);
    const int top = std::max(a.y, b.y);
    const int right = std::min(a.x + a.w, b.x + b.w);
    const int bottom = std::min(a.y + a.h, b.y + b.h);
    return SDL_Rect{left, top, std::max(0, right - left),
                    std::max(0, bottom - top)};
  }

  void ApplyClip(const std::optional<SDL_Rect>& clip) {
    if (clip) {
      SDL_SetRenderClipRect(renderer_, &*clip);
    } else {
      SDL_SetRenderClipRect(renderer_, nullptr);
    }
  }

  void DrawImage(SDL_Texture* texture,
                 html_css_renderer::Rect rect,
                 html_css_renderer::Color color,
                 const RenderState& state) {
    if (IsIdentity(state.transform)) {
      SDL_FRect dst = ToSdlRect(rect);
      SDL_SetTextureColorMod(texture, ClampByte(color.r), ClampByte(color.g),
                             ClampByte(color.b));
      SDL_SetTextureAlphaMod(texture, ClampByte(color.a * state.opacity));
      SDL_RenderTexture(renderer_, texture, nullptr, &dst);
      return;
    }
    DrawQuad(texture, rect, color, state);
  }

  void DrawCommand(const html_css_renderer::DrawCommand& command,
                   std::vector<RenderState>& state_stack,
                   RenderState& state) {
    switch (command.type) {
      case html_css_renderer::DrawCommandType::kFillRect:
        FillRect(command, state);
        break;
      case html_css_renderer::DrawCommandType::kStrokeRect: {
        SetSdlColor(renderer_, command.color, state.opacity);
        const float w = std::max(1.0f, command.stroke_width);
        const html_css_renderer::Rect r = command.rect;
        std::array<html_css_renderer::Rect, 4> sides = {
            html_css_renderer::Rect{r.x, r.y, r.width, w},
            html_css_renderer::Rect{r.x, r.y + r.height - w, r.width, w},
            html_css_renderer::Rect{r.x, r.y, w, r.height},
            html_css_renderer::Rect{r.x + r.width - w, r.y, w, r.height},
        };
        for (const html_css_renderer::Rect& side : sides) {
          if (IsIdentity(state.transform)) {
            SDL_FRect sdl_side = ToSdlRect(side);
            SDL_RenderFillRect(renderer_, &sdl_side);
          } else {
            DrawQuad(nullptr, side, command.color, state);
          }
        }
        break;
      }
      case html_css_renderer::DrawCommandType::kFillRRect:
        DrawRRectApprox(command, false, state);
        break;
      case html_css_renderer::DrawCommandType::kStrokeRRect:
        DrawRRectApprox(command, true, state);
        break;
      case html_css_renderer::DrawCommandType::kFillRectShader:
        FillRect(command, state);
        break;
      case html_css_renderer::DrawCommandType::kFillRRectShader:
        DrawRRectApprox(command, false, state);
        break;
      case html_css_renderer::DrawCommandType::kDrawImage: {
        const auto found = images_.find(command.resource_id);
        if (found == images_.end()) {
          break;
        }
        DrawImage(found->second.texture, command.rect,
                  html_css_renderer::Color::Rgba(1, 1, 1, 1), state);
        break;
      }
      case html_css_renderer::DrawCommandType::kDrawImageRect: {
        const auto found = images_.find(command.resource_id);
        if (found == images_.end()) {
          break;
        }
        DrawImage(found->second.texture, command.rect,
                  html_css_renderer::Color::Rgba(1, 1, 1, 1), state);
        break;
      }
      case html_css_renderer::DrawCommandType::kDrawGlyphRun: {
        const size_t count = std::min(command.glyph_run.glyph_ids.size(),
                                      command.glyph_run.positions.size());
        for (size_t i = 0; i < count; ++i) {
          const std::string key = GlyphKey(command.glyph_run.font_id,
                                           command.glyph_run.glyph_ids[i]);
          const auto found = glyphs_.find(key);
          if (found == glyphs_.end()) {
            continue;
          }
          const html_css_renderer::Point origin =
              command.glyph_run.positions[i];
          const html_css_renderer::Rect dst{
              origin.x + found->second.bounds.x,
              origin.y + found->second.bounds.y,
              static_cast<float>(found->second.width),
              static_cast<float>(found->second.height)};
          DrawImage(found->second.texture, dst, command.glyph_run.color, state);
        }
        break;
      }
      case html_css_renderer::DrawCommandType::kDrawTextBlob:
        break;
      case html_css_renderer::DrawCommandType::kSave:
        state_stack.push_back(state);
        break;
      case html_css_renderer::DrawCommandType::kSaveLayer:
        state_stack.push_back(state);
        state.opacity *= command.opacity;
        break;
      case html_css_renderer::DrawCommandType::kRestore:
        if (!state_stack.empty()) {
          state = state_stack.back();
          state_stack.pop_back();
          ApplyClip(state.clip);
        }
        break;
      case html_css_renderer::DrawCommandType::kTransform:
        state.transform = Multiply(state.transform, command.transform);
        if (state.clip) {
          ApplyClip(state.clip);
        }
        break;
      case html_css_renderer::DrawCommandType::kClipRect: {
        SDL_Rect clip = BoundsForTransformedRect(state.transform, command.rect);
        state.clip = state.clip ? IntersectClip(*state.clip, clip) : clip;
        ApplyClip(state.clip);
        break;
      }
      case html_css_renderer::DrawCommandType::kClipRRect: {
        SDL_Rect clip = BoundsForTransformedRect(state.transform, command.rect);
        state.clip = state.clip ? IntersectClip(*state.clip, clip) : clip;
        ApplyClip(state.clip);
        break;
      }
      case html_css_renderer::DrawCommandType::kClipPath:
        break;
      case html_css_renderer::DrawCommandType::kFillPath:
      case html_css_renderer::DrawCommandType::kDrawText:
      case html_css_renderer::DrawCommandType::kDiagnostic:
        break;
    }
  }

  SDL_Renderer* renderer_ = nullptr;
  std::unordered_map<std::string, TextureResource> images_;
  std::unordered_map<std::string, TextureResource> glyphs_;
};

bool Contains(html_css_renderer::Rect rect, float x, float y) {
  return x >= rect.x && y >= rect.y && x < rect.x + rect.width &&
         y < rect.y + rect.height;
}

std::string HitTest(const std::vector<html_css_renderer::HitTestEntry>& entries,
                    float x,
                    float y) {
  for (auto it = entries.rbegin(); it != entries.rend(); ++it) {
    if (Contains(it->bounds, x, y)) {
      return it->element_id;
    }
  }
  return {};
}

html_css_renderer::Point WindowToDocumentPoint(int window_width,
                                               int window_height,
                                               int image_width,
                                               int image_height,
                                               float window_x,
                                               float window_y) {
  const float scale_x =
      window_width > 0 ? window_width / static_cast<float>(image_width) : 1.0f;
  const float scale_y = window_height > 0
                            ? window_height / static_cast<float>(image_height)
                            : 1.0f;
  const float scale = std::min(scale_x, scale_y);
  const float target_width = image_width * scale;
  const float target_height = image_height * scale;
  const float target_x = (window_width - target_width) * 0.5f;
  const float target_y = (window_height - target_height) * 0.5f;
  if (scale <= 0.0f) {
    return {};
  }
  return {(window_x - target_x) / scale, (window_y - target_y) / scale};
}

}  // namespace

int main(int argc, char** argv) {
  EmptyAssets assets;
  html_css_renderer::RendererCreateInfo create_info;
  create_info.asset_provider = &assets;
  if (argc <= 1) {
    create_info.html =
        "<main><img src=\"missing.png\"><h1>SDL renderer</h1></main>";
    create_info.stylesheets.push_back(
        {"viewer", "body { background: #f5f7fb; }"});
  }
  html_css_renderer::FrameInput input;
  uint64_t quit_after_ms = 0;
  float window_scale = 2.0f;
  std::string font_file;
  std::string paint_artifact_dump_path;
  bool incremental = false;
  bool use_cpu = false;
  bool use_skia_cpu = false;
  bool use_blink = true;

  if (argc > 1 && !ParseArgs(argc, argv, &create_info, &input,
                             &quit_after_ms, &window_scale, &font_file,
                             &incremental, &use_cpu, &use_skia_cpu,
                             &paint_artifact_dump_path,
                             &use_blink)) {
    PrintUsage();
    return 2;
  }

  if (!font_file.empty()) {
    assets.font_bytes = ReadBinaryFile(font_file);
    if (assets.font_bytes.empty()) {
      std::fprintf(stderr, "failed to read font file: %s\n",
                   font_file.c_str());
      return 2;
    }
    std::fprintf(stderr, "font asset available: %s\n",
                 font_file.c_str());
  }
  const html_css_renderer::Size initial_viewport = create_info.viewport;

  std::unique_ptr<html_css_renderer::BlinkPageEmbedder> blink_embedder;
  std::unique_ptr<html_css_renderer::RendererState> state;
  html_css_renderer::RenderResult result;

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
    if (!paint_artifact_dump_path.empty()) {
      std::ofstream audit_file(paint_artifact_dump_path);
      if (!audit_file) {
        std::fprintf(stderr, "failed to write paint artifact dump: %s\n",
                     paint_artifact_dump_path.c_str());
        return 1;
      }
      audit_file << html_css_renderer::SerializePaintArtifactAuditJson(result)
                 << "\n";
    }
    for (const std::string& diagnostic : result.diagnostics) {
      std::fprintf(stderr, "diagnostic: %s\n", diagnostic.c_str());
    }
  }

  int frame_width =
      std::max(1, static_cast<int>(std::floor(initial_viewport.width)));
  int frame_height =
      std::max(1, static_cast<int>(std::floor(initial_viewport.height)));
  html_css_renderer::CpuImage image;
  std::vector<uint32_t> pixels;
  if (use_cpu) {
    image =
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
        use_skia_cpu ? html_css_renderer::RasterizeRenderResultWithSkiaCpu(result)
                     :
#endif
                     html_css_renderer::RasterizeRenderResult(result);
    frame_width = image.width;
    frame_height = image.height;
    pixels = ConvertRgbaToAbgr(image);
  }

  SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");

  if (!SDL_Init(SDL_INIT_VIDEO)) {
    std::fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
    return 1;
  }

  const int window_width =
      std::max(640, static_cast<int>(frame_width * window_scale));
  const int window_height =
      std::max(480, static_cast<int>(frame_height * window_scale));

  SDL_Window* window = SDL_CreateWindow(
      "HTML/CSS Renderer CPU SDL Viewer", window_width, window_height,
      SDL_WINDOW_RESIZABLE);
  if (!window) {
    std::fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  SDL_SetWindowMinimumSize(window, 320, 240);

  SDL_Renderer* renderer =
      SDL_CreateRenderer(window, nullptr);
  if (!renderer) {
    std::fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  const SDL_TextureAccess texture_access =
      use_cpu ? SDL_TEXTUREACCESS_STATIC : SDL_TEXTUREACCESS_TARGET;
  SDL_Texture* texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
                        texture_access, frame_width, frame_height);
  if (!texture) {
    std::fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  std::unique_ptr<SdlFrameRenderer> direct_renderer;
  if (use_cpu) {
    SDL_UpdateTexture(texture, nullptr, pixels.data(),
                      image.width * static_cast<int>(sizeof(uint32_t)));
  } else {
    direct_renderer = std::make_unique<SdlFrameRenderer>(renderer);
    if (!direct_renderer->Render(result, texture)) {
      SDL_DestroyTexture(texture);
      SDL_DestroyRenderer(renderer);
      SDL_DestroyWindow(window);
      SDL_Quit();
      return 1;
    }
  }

  bool running = true;
  const uint64_t start_ms = SDL_GetTicks();
  while (running) {
    bool texture_dirty = false;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT ||
          (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE)) {
        running = false;
      } else if (incremental && event.type == SDL_EVENT_MOUSE_MOTION) {
        int window_width_for_hit = 0;
        int window_height_for_hit = 0;
        SDL_GetWindowSize(window, &window_width_for_hit,
                          &window_height_for_hit);
        const html_css_renderer::Point document_point = WindowToDocumentPoint(
            window_width_for_hit, window_height_for_hit, frame_width,
            frame_height, event.motion.x, event.motion.y);
        const std::string hovered =
            HitTest(result.hit_test_entries, document_point.x,
                    document_point.y);
        if (hovered != input.hovered_element_id) {
          html_css_renderer::FrameInput next_input;
          next_input.hovered_element_id = hovered;
          next_input.delta_time_seconds = input.delta_time_seconds;
          const html_css_renderer::RenderResult next_result =
              blink_embedder->AdvanceAndRenderIncremental(next_input);
          if (use_cpu) {
            image =
#if defined(HTML_CSS_RENDERER_USE_SKIA_CPU_RENDERER)
                use_skia_cpu
                    ? html_css_renderer::RasterizeRenderResultWithSkiaCpu(
                          next_result)
                    :
#endif
                    html_css_renderer::RasterizeRenderResultIncremental(
                        next_result, &image);
            pixels = ConvertRgbaToAbgr(image);
            SDL_UpdateTexture(texture, nullptr, pixels.data(),
                              frame_width *
                                  static_cast<int>(sizeof(uint32_t)));
          } else if (direct_renderer) {
            direct_renderer->Render(next_result, texture);
          }
          result = next_result;
          input = std::move(next_input);
          texture_dirty = true;
        }
      }
    }
    (void)texture_dirty;
    int drawable_width = 0;
    int drawable_height = 0;
    SDL_GetWindowSize(window, &drawable_width, &drawable_height);
    SDL_SetRenderDrawColor(renderer, 245, 247, 251, 255);
    SDL_RenderClear(renderer);
    const float scale_x =
        drawable_width > 0 ? drawable_width / static_cast<float>(frame_width)
                           : 1.0f;
    const float scale_y =
        drawable_height > 0 ? drawable_height / static_cast<float>(frame_height)
                            : 1.0f;
    const float scale = std::min(scale_x, scale_y);
    const float target_width = frame_width * scale;
    const float target_height = frame_height * scale;
    const SDL_FRect target{
        (drawable_width - target_width) * 0.5f,
        (drawable_height - target_height) * 0.5f,
        target_width,
        target_height,
    };
    SDL_RenderTexture(renderer, texture, nullptr, &target);
    SDL_RenderPresent(renderer);
    if (quit_after_ms > 0 && SDL_GetTicks() - start_ms >= quit_after_ms) {
      running = false;
    }
    SDL_Delay(16);
  }

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return result.missing_resources.empty() ? 0 : 1;
}
