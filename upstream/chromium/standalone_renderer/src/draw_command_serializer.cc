#include "html_css_renderer/draw_command_serializer.h"

#include <iomanip>
#include <sstream>

namespace html_css_renderer {
namespace {

std::string EscapeJson(const std::string& value) {
  std::ostringstream out;
  for (const unsigned char c : value) {
    switch (c) {
      case '"':
        out << "\\\"";
        break;
      case '\\':
        out << "\\\\";
        break;
      case '\b':
        out << "\\b";
        break;
      case '\f':
        out << "\\f";
        break;
      case '\n':
        out << "\\n";
        break;
      case '\r':
        out << "\\r";
        break;
      case '\t':
        out << "\\t";
        break;
      default:
        if (c < 0x20) {
          out << "\\u" << std::hex << std::setw(4) << std::setfill('0')
              << static_cast<int>(c) << std::dec;
        } else {
          out << static_cast<char>(c);
        }
        break;
    }
  }
  return out.str();
}

void WriteColor(std::ostringstream& out, const Color& color) {
  out << "{\"r\":" << color.r << ",\"g\":" << color.g
      << ",\"b\":" << color.b << ",\"a\":" << color.a << "}";
}

void WritePoint(std::ostringstream& out, const Point& point) {
  out << "{\"x\":" << point.x << ",\"y\":" << point.y << "}";
}

void WriteRect(std::ostringstream& out, const Rect& rect) {
  out << "{\"x\":" << rect.x << ",\"y\":" << rect.y
      << ",\"width\":" << rect.width << ",\"height\":" << rect.height
      << "}";
}

void WriteStringArray(std::ostringstream& out,
                      const std::vector<std::string>& values) {
  out << "[";
  for (size_t i = 0; i < values.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << "\"" << EscapeJson(values[i]) << "\"";
  }
  out << "]";
}

void WriteBytesSummary(std::ostringstream& out,
                       uint64_t bytes_hash,
                       size_t byte_count) {
  out << "\"bytes_hash\":" << bytes_hash << ",\"byte_count\":"
      << byte_count;
}

void WriteHitTestEntries(std::ostringstream& out,
                         const std::vector<HitTestEntry>& entries) {
  out << "[";
  for (size_t i = 0; i < entries.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << "{\"element_id\":\"" << EscapeJson(entries[i].element_id)
        << "\",\"bounds\":";
    WriteRect(out, entries[i].bounds);
    out << "}";
  }
  out << "]";
}

void WriteResourceCommands(std::ostringstream& out,
                           const std::vector<ResourceCommand>& commands) {
  out << "[";
  for (size_t i = 0; i < commands.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << "{\"type\":\"" << ToString(commands[i].type)
        << "\",\"resource_id\":\"" << EscapeJson(commands[i].resource_id)
        << "\"";
    if (commands[i].type != ResourceCommandType::kDestroyResource) {
      out << ",\"load_command\":"
          << SerializeLoadCommandJson(commands[i].load_command);
    }
    out << "}";
  }
  out << "]";
}

void WriteSceneChunks(std::ostringstream& out,
                      const std::vector<SceneChunk>& chunks) {
  out << "[";
  for (size_t i = 0; i < chunks.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << "{\"chunk_id\":\"" << EscapeJson(chunks[i].chunk_id)
        << "\",\"bounds\":";
    WriteRect(out, chunks[i].bounds);
    out << ",\"damage_bounds\":";
    WriteRect(out, chunks[i].damage_bounds);
    out << ",\"content_hash\":" << chunks[i].content_hash
        << ",\"resource_hash\":" << chunks[i].resource_hash
        << ",\"retained_from_previous_frame\":"
        << (chunks[i].retained_from_previous_frame ? "true" : "false")
        << ",\"command_count\":" << chunks[i].commands.size() << "}";
  }
  out << "]";
}

void WriteSceneCommands(std::ostringstream& out,
                        const std::vector<SceneCommand>& commands) {
  out << "[";
  for (size_t i = 0; i < commands.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << "{\"type\":\"" << ToString(commands[i].type) << "\"";
    if (!commands[i].chunk_id.empty()) {
      out << ",\"chunk_id\":\"" << EscapeJson(commands[i].chunk_id) << "\"";
    }
    switch (commands[i].type) {
      case SceneCommandType::kBeginChunk:
        out << ",\"bounds\":";
        WriteRect(out, commands[i].bounds);
        break;
      case SceneCommandType::kEndChunk:
        break;
      case SceneCommandType::kDrawCommand:
        out << ",\"draw_command\":"
            << SerializeDrawCommandJson(commands[i].draw_command);
        break;
    }
    out << "}";
  }
  out << "]";
}

void WriteRenderPasses(std::ostringstream& out,
                       const std::vector<RenderPass>& passes) {
  out << "[";
  for (size_t i = 0; i < passes.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << "{\"pass_id\":\"" << EscapeJson(passes[i].pass_id)
        << "\",\"target\":\"" << ToString(passes[i].target_kind)
        << "\",\"viewport\":";
    WriteRect(out, passes[i].viewport);
    out << ",\"first_scene_command\":" << passes[i].first_scene_command
        << ",\"scene_command_count\":" << passes[i].scene_command_count
        << ",\"clear_before_render\":"
        << (passes[i].clear_before_render ? "true" : "false")
        << ",\"clear_color\":";
    WriteColor(out, passes[i].clear_color);
    out << "}";
  }
  out << "]";
}

}  // namespace

std::string SerializeLoadCommandJson(const LoadCommand& command) {
  std::ostringstream out;
  out << std::setprecision(9);
  out << "{\"type\":\"" << ToString(command.type) << "\"";

  switch (command.type) {
    case LoadCommandType::kLoadImage:
      out << ",\"image_id\":\"" << EscapeJson(command.image.image_id)
          << "\",\"resource_id\":\"" << EscapeJson(command.image.resource_id)
          << "\",\"mime_type\":\"" << EscapeJson(command.image.mime_type)
          << "\",";
      WriteBytesSummary(out, command.image.bytes_hash,
                        command.image.byte_count);
      out << ",\"decoded_format\":\""
          << ToString(command.image.decoded_format)
          << "\",\"decoded_size\":";
      WriteRect(out, Rect{0.0f, 0.0f, command.image.decoded_size.width,
                          command.image.decoded_size.height});
      out << ",\"decoded_byte_count\":"
          << command.image.decoded_pixels.size();
      break;
    case LoadCommandType::kLoadFont:
      out << ",\"font_id\":\"" << EscapeJson(command.font.font_id)
          << "\",\"resource_id\":\"" << EscapeJson(command.font.resource_id)
          << "\",\"mime_type\":\"" << EscapeJson(command.font.mime_type)
          << "\",";
      WriteBytesSummary(out, command.font.bytes_hash,
                        command.font.byte_count);
      break;
    case LoadCommandType::kGlyphAtlasUpdate:
      out << ",\"atlas_id\":\""
          << EscapeJson(command.glyph_atlas_update.atlas_id)
          << "\",\"font_id\":\""
          << EscapeJson(command.glyph_atlas_update.font_id)
          << "\",\"glyph_id\":"
          << command.glyph_atlas_update.glyph_id
          << ",\"bounds\":";
      WriteRect(out, command.glyph_atlas_update.bounds);
      out << ",\"format\":\""
          << ToString(command.glyph_atlas_update.format)
          << "\",\"byte_count\":"
          << command.glyph_atlas_update.pixels.size();
      break;
  }

  out << "}";
  return out.str();
}

std::string SerializeLoadCommandListJsonLines(
    const LoadCommandList& commands) {
  std::ostringstream out;
  for (const auto& command : commands) {
    out << SerializeLoadCommandJson(command) << "\n";
  }
  return out.str();
}

std::string SerializeDrawCommandJson(const DrawCommand& command) {
  std::ostringstream out;
  out << std::setprecision(9);
  out << "{\"type\":\"" << ToString(command.type) << "\"";

  switch (command.type) {
    case DrawCommandType::kSave:
    case DrawCommandType::kRestore:
      break;
    case DrawCommandType::kTransform:
      out << ",\"matrix\":[";
      for (size_t i = 0; i < command.transform.values.size(); ++i) {
        if (i > 0) {
          out << ",";
        }
        out << command.transform.values[i];
      }
      out << "]";
      break;
    case DrawCommandType::kClipRect:
      out << ",\"rect\":";
      WriteRect(out, command.rect);
      break;
    case DrawCommandType::kSaveLayer:
      out << ",\"bounds\":";
      WriteRect(out, command.rect);
      out << ",\"opacity\":" << command.opacity;
      break;
    case DrawCommandType::kFillRect:
    case DrawCommandType::kStrokeRect:
    case DrawCommandType::kFillRRect:
    case DrawCommandType::kStrokeRRect:
      out << ",\"rect\":";
      WriteRect(out, command.rect);
      out << ",\"color\":";
      WriteColor(out, command.color);
      if (command.type == DrawCommandType::kFillRRect ||
          command.type == DrawCommandType::kStrokeRRect) {
        out << ",\"radius_x\":" << command.radius_x
            << ",\"radius_y\":" << command.radius_y;
      }
      if (command.type == DrawCommandType::kStrokeRect ||
          command.type == DrawCommandType::kStrokeRRect) {
        out << ",\"stroke_width\":" << command.stroke_width;
      }
      break;
    case DrawCommandType::kFillPath:
      out << ",\"path\":\"" << EscapeJson(command.path_data)
          << "\",\"color\":";
      WriteColor(out, command.color);
      break;
    case DrawCommandType::kDrawImage:
      out << ",\"resource_id\":\"" << EscapeJson(command.resource_id)
          << "\",\"destination\":";
      WriteRect(out, command.rect);
      break;
    case DrawCommandType::kDrawGlyphRun:
      out << ",\"font_id\":\"" << EscapeJson(command.glyph_run.font_id)
          << "\",\"font_size\":" << command.glyph_run.font_size
          << ",\"color\":";
      WriteColor(out, command.glyph_run.color);
      out << ",\"glyph_ids\":[";
      for (size_t i = 0; i < command.glyph_run.glyph_ids.size(); ++i) {
        if (i > 0) {
          out << ",";
        }
        out << command.glyph_run.glyph_ids[i];
      }
      out << "],\"positions\":[";
      for (size_t i = 0; i < command.glyph_run.positions.size(); ++i) {
        if (i > 0) {
          out << ",";
        }
        WritePoint(out, command.glyph_run.positions[i]);
      }
      out << "]";
      break;
    case DrawCommandType::kDrawText:
      out << ",\"text\":\"" << EscapeJson(command.text) << "\",\"origin\":";
      WritePoint(out, Point{command.rect.x, command.rect.y});
      out << ",\"font_size\":" << command.glyph_run.font_size
          << ",\"color\":";
      WriteColor(out, command.color);
      break;
    case DrawCommandType::kDiagnostic:
      out << ",\"message\":\"" << EscapeJson(command.text) << "\"";
      break;
  }

  out << "}";
  return out.str();
}

std::string SerializeDrawCommandListJsonLines(
    const DrawCommandList& commands) {
  std::ostringstream out;
  for (const auto& command : commands) {
    out << SerializeDrawCommandJson(command) << "\n";
  }
  return out.str();
}

std::string SerializeRenderResultJson(const RenderResult& result) {
  std::ostringstream out;
  out << std::setprecision(9);
  out << "{";
  out << "\"requires_full_redraw\":"
      << (result.frame.requires_full_redraw ? "true" : "false")
      << ",\"damage_bounds\":";
  WriteRect(out, result.frame.damage_bounds);
  out << ",\"damage_rects\":[";
  for (size_t i = 0; i < result.frame.damage_rects.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    WriteRect(out, result.frame.damage_rects[i]);
  }
  out << "],\"resource_commands\":";
  WriteResourceCommands(out, result.frame.resource_commands);
  out << ",\"scene_chunks\":";
  WriteSceneChunks(out, result.frame.scene_chunks);
  out << ",\"scene_commands\":";
  WriteSceneCommands(out, result.frame.scene_commands);
  out << ",\"render_passes\":";
  WriteRenderPasses(out, result.frame.render_passes);
  out << ",\"hit_test_entries\":";
  WriteHitTestEntries(out, result.hit_test_entries);
  out << ",\"diagnostics\":";
  WriteStringArray(out, result.diagnostics);
  out << ",\"missing_resources\":";
  WriteStringArray(out, result.missing_resources);
  out << ",\"successor_snapshot\":{\"timeline_time_seconds\":"
      << result.successor_snapshot.timeline_time_seconds << ",\"viewport\":";
  WriteRect(out, Rect{0.0f, 0.0f, result.successor_snapshot.viewport.width,
                      result.successor_snapshot.viewport.height});
  out << ",\"focused_element_id\":\""
      << EscapeJson(result.successor_snapshot.focused_element_id)
      << "\",\"hovered_element_id\":\""
      << EscapeJson(result.successor_snapshot.hovered_element_id)
      << "\",\"active_element_id\":\""
      << EscapeJson(result.successor_snapshot.active_element_id) << "\"}}";
  return out.str();
}

}  // namespace html_css_renderer
