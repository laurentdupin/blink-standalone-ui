#include "html_css_renderer/load_command.h"

#include <utility>

namespace html_css_renderer {

LoadCommand LoadCommand::LoadFont(FontLoadInfo info) {
  LoadCommand command;
  command.type = LoadCommandType::kLoadFont;
  command.font = std::move(info);
  return command;
}

LoadCommand LoadCommand::LoadImage(ImageLoadInfo info) {
  LoadCommand command;
  command.type = LoadCommandType::kLoadImage;
  command.image = std::move(info);
  return command;
}

LoadCommand LoadCommand::UpdateGlyphAtlas(GlyphAtlasUpdate update) {
  LoadCommand command;
  command.type = LoadCommandType::kGlyphAtlasUpdate;
  command.glyph_atlas_update = std::move(update);
  return command;
}

const char* ToString(LoadCommandType type) {
  switch (type) {
    case LoadCommandType::kLoadImage:
      return "LoadImage";
    case LoadCommandType::kLoadFont:
      return "LoadFont";
    case LoadCommandType::kGlyphAtlasUpdate:
      return "GlyphAtlasUpdate";
  }
  return "Unknown";
}

const char* ToString(PixelFormat format) {
  switch (format) {
    case PixelFormat::kUnknown:
      return "Unknown";
    case PixelFormat::kRgba8888:
      return "Rgba8888";
    case PixelFormat::kAlpha8:
      return "Alpha8";
  }
  return "Unknown";
}

uint64_t HashBytes(const std::vector<uint8_t>& bytes) {
  uint64_t hash = 1469598103934665603ull;
  for (const uint8_t byte : bytes) {
    hash ^= byte;
    hash *= 1099511628211ull;
  }
  return hash;
}

}  // namespace html_css_renderer
