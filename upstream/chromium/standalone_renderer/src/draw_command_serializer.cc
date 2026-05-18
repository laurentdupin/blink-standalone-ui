#include "html_css_renderer/draw_command_serializer.h"

#include <iomanip>
#include <map>
#include <sstream>

#include "html_css_renderer/skia_cpu_renderer.h"

namespace html_css_renderer {
namespace {

extern "C" int StandaloneRendererSameProcessTypefaceResourceCount();
extern "C" int StandaloneRendererTextBlobReplayDiagnosticsEnabled();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupAttemptCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupSuccessCount();
extern "C" uint64_t
StandaloneRendererSameProcessTypefaceLookupFailureCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeAttemptCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeSuccessCount();
extern "C" uint64_t StandaloneRendererTextBlobDeserializeFailureCount();
extern "C" uint64_t StandaloneRendererDiagnosticTypefaceFallbackCount();
extern "C" int StandaloneRendererSameProcessTypefaceFamilyAt(int,
                                                              char*,
                                                              int);

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

void WriteMatrix(std::ostringstream& out, const Matrix4& matrix) {
  out << "[";
  for (size_t i = 0; i < matrix.values.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << matrix.values[i];
  }
  out << "]";
}

void WriteMatrix3(std::ostringstream& out,
                  const std::array<float, 9>& matrix) {
  out << "[";
  for (size_t i = 0; i < matrix.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    out << matrix[i];
  }
  out << "]";
}

void WriteCommandCoverageRecords(std::ostringstream& out) {
  const std::vector<CommandCoverageRecord> records =
      SnapshotCommandCoverageDiagnostics();
  out << "[";
  for (size_t i = 0; i < records.size(); ++i) {
    if (i > 0) {
      out << ",";
    }
    const CommandCoverageRecord& record = records[i];
    out << "{\"command_index\":" << record.command_index
        << ",\"command_type\":\"" << EscapeJson(record.command_type) << "\""
        << ",\"bounds\":";
    WriteRect(out, record.bounds);
    out << ",\"active_matrix\":";
    WriteMatrix3(out, record.active_matrix);
    out << ",\"has_active_clip\":"
        << (record.has_active_clip ? "true" : "false")
        << ",\"active_clip_bounds\":";
    WriteRect(out, record.active_clip_bounds);
    out << ",\"save_depth_before\":" << record.save_depth_before
        << ",\"save_depth_after\":" << record.save_depth_after
        << ",\"pixels_changed\":" << record.pixels_changed
        << ",\"skipped\":" << (record.skipped ? "true" : "false")
        << ",\"skip_reason\":\"" << EscapeJson(record.skip_reason) << "\""
        << ",\"shader_resource_present\":"
        << (record.shader_resource_present ? "true" : "false")
        << ",\"shader_byte_count\":" << record.shader_byte_count
        << ",\"shader_deserialize_success\":"
        << (record.shader_deserialize_success ? "true" : "false")
        << ",\"text_blob_resource_present\":"
        << (record.text_blob_resource_present ? "true" : "false")
        << ",\"text_blob_byte_count\":" << record.text_blob_byte_count
        << ",\"text_blob_deserialize_success\":"
        << (record.text_blob_deserialize_success ? "true" : "false")
        << "}";
  }
  out << "]";
}

void WritePropertyState(std::ostringstream& out,
                        const PaintPropertyStateSnapshot& state) {
  out << "{\"state_hash\":" << state.state_hash
      << ",\"transform_to_root\":";
  WriteMatrix(out, state.transform_to_root);
  out << ",\"transform_is_2d\":"
      << (state.transform_is_2d ? "true" : "false")
      << ",\"transform_has_perspective\":"
      << (state.transform_has_perspective ? "true" : "false")
      << ",\"transform_has_non_translation\":"
      << (state.transform_has_non_translation ? "true" : "false")
      << ",\"transform_node_id\":" << state.transform_node_id
      << ",\"transform_parent_id\":" << state.transform_parent_id
      << ",\"transform_chain_depth\":" << state.transform_chain_depth
      << ",\"has_clip_rect\":" << (state.has_clip_rect ? "true" : "false")
      << ",\"clip_rect\":";
  WriteRect(out, state.clip_rect);
  out << ",\"clip_node_id\":" << state.clip_node_id
      << ",\"clip_parent_id\":" << state.clip_parent_id
      << ",\"clip_local_transform_id\":" << state.clip_local_transform_id
      << ",\"clip_chain_depth\":" << state.clip_chain_depth
      << ",\"clip_has_rounded_clip\":"
      << (state.clip_has_rounded_clip ? "true" : "false")
      << ",\"clip_has_path_clip\":"
      << (state.clip_has_path_clip ? "true" : "false")
      << ",\"effect_node_id\":" << state.effect_node_id
      << ",\"effect_parent_id\":" << state.effect_parent_id
      << ",\"effect_chain_depth\":" << state.effect_chain_depth
      << ",\"effect_opacity\":" << state.effect_opacity
      << ",\"effect_has_non_default_opacity\":"
      << (state.effect_has_non_default_opacity ? "true" : "false")
      << ",\"effect_has_filter\":"
      << (state.effect_has_filter ? "true" : "false")
      << ",\"effect_has_backdrop_filter\":"
      << (state.effect_has_backdrop_filter ? "true" : "false")
      << ",\"effect_has_blend_mode\":"
      << (state.effect_has_blend_mode ? "true" : "false")
      << ",\"effect_output_clip_id\":" << state.effect_output_clip_id
      << ",\"scroll_node_id\":" << state.scroll_node_id
      << ",\"scroll_parent_id\":" << state.scroll_parent_id
      << ",\"has_scroll_offset\":"
      << (state.has_scroll_offset ? "true" : "false")
      << ",\"scroll_offset_x\":" << state.scroll_offset_x
      << ",\"scroll_offset_y\":" << state.scroll_offset_y
      << ",\"scroll_container_rect\":";
  WriteRect(out, state.scroll_container_rect);
  out << ",\"scroll_contents_rect\":";
  WriteRect(out, state.scroll_contents_rect);
  out << "}";
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

void WriteStringIntMap(std::ostringstream& out,
                       const std::map<std::string, int>& values) {
  out << "{";
  bool first = true;
  for (const auto& [key, value] : values) {
    if (!first) {
      out << ",";
    }
    first = false;
    out << "\"" << EscapeJson(key) << "\":" << value;
  }
  out << "}";
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
    if (commands[i].type == ResourceCommandType::kLoadTypeface) {
      out << ",\"typeface_resource_id\":" << commands[i].typeface_resource_id
          << ",\"family\":\"" << EscapeJson(commands[i].family_name)
          << "\",\"weight\":" << commands[i].font_weight
          << ",\"width\":" << commands[i].font_width
          << ",\"slant\":\"" << EscapeJson(commands[i].font_slant)
          << "\",\"same_process_only\":"
          << (commands[i].same_process_only ? "true" : "false")
          << ",\"portable_font_data_available\":"
          << (commands[i].portable_font_data_available ? "true" : "false")
          << ",\"portability_status\":\""
          << EscapeJson(commands[i].portability_status) << "\"";
    } else if (commands[i].type == ResourceCommandType::kLoadTextBlob) {
      out << ",\"text_blob_resource_id\":"
          << commands[i].text_blob_resource_id
          << ",\"blob_byte_count\":"
          << commands[i].serialized_text_blob_bytes.size()
          << ",\"dependent_typeface_resource_ids\":[";
      for (size_t id_index = 0;
           id_index < commands[i].dependent_typeface_resource_ids.size();
           ++id_index) {
        if (id_index > 0) {
          out << ",";
        }
        out << commands[i].dependent_typeface_resource_ids[id_index];
      }
      out << "],\"bounds\":";
      WriteRect(out, commands[i].resource_bounds);
      out << ",\"portability_status\":\""
          << EscapeJson(commands[i].portability_status) << "\"";
    } else if (commands[i].type != ResourceCommandType::kDestroyResource) {
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
    out << "{\"debug_index\":" << chunks[i].debug_index
        << ",\"stable_key\":\"" << EscapeJson(chunks[i].stable_key)
        << "\",\"chunk_id\":\"" << EscapeJson(chunks[i].chunk_id)
        << "\",\"bounds\":";
    WriteRect(out, chunks[i].bounds);
    out << ",\"damage_bounds\":";
    WriteRect(out, chunks[i].damage_bounds);
    out << ",\"property_state\":";
    WritePropertyState(out, chunks[i].property_state);
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
      out << ",\"matrix\":";
      WriteMatrix(out, command.transform);
      break;
    case DrawCommandType::kClipRect:
      out << ",\"rect\":";
      WriteRect(out, command.rect);
      break;
    case DrawCommandType::kClipRRect:
      out << ",\"rect\":";
      WriteRect(out, command.rect);
      out << ",\"radius_x\":" << command.radius_x
          << ",\"radius_y\":" << command.radius_y
          << ",\"clip_op\":\""
          << (command.clip_difference ? "Difference" : "Intersect") << "\""
          << ",\"corner_radii\":[";
      for (size_t i = 0; i < command.corner_radii.size(); ++i) {
        if (i > 0) {
          out << ",";
        }
        WritePoint(out, command.corner_radii[i]);
      }
      out << "]";
      break;
    case DrawCommandType::kClipPath:
      out << ",\"clip_op\":\""
          << (command.clip_difference ? "Difference" : "Intersect")
          << "\",\"path_byte_count\":" << command.path_bytes.size();
      break;
    case DrawCommandType::kSaveLayer:
      out << ",\"bounds\":";
      WriteRect(out, command.rect);
      out << ",\"opacity\":" << command.opacity;
      break;
    case DrawCommandType::kFillRect:
    case DrawCommandType::kStrokeRect:
    case DrawCommandType::kFillRectShader:
    case DrawCommandType::kFillRRect:
    case DrawCommandType::kStrokeRRect:
    case DrawCommandType::kFillRRectShader:
      out << ",\"rect\":";
      WriteRect(out, command.rect);
      out << ",\"color\":";
      WriteColor(out, command.color);
      if (command.type == DrawCommandType::kFillRRect ||
          command.type == DrawCommandType::kStrokeRRect ||
          command.type == DrawCommandType::kFillRRectShader) {
        out << ",\"radius_x\":" << command.radius_x
            << ",\"radius_y\":" << command.radius_y;
      }
      if (command.type == DrawCommandType::kStrokeRect ||
          command.type == DrawCommandType::kStrokeRRect) {
        out << ",\"stroke_width\":" << command.stroke_width;
      }
      if (command.type == DrawCommandType::kFillRectShader ||
          command.type == DrawCommandType::kFillRRectShader) {
        out << ",\"shader_byte_count\":" << command.shader_bytes.size();
      }
      break;
    case DrawCommandType::kFillPath:
      out << ",\"path_byte_count\":" << command.path_bytes.size()
          << ",\"shader_byte_count\":" << command.shader_bytes.size()
          << ",\"stroke_width\":" << command.stroke_width
          << ",\"color\":";
      WriteColor(out, command.color);
      break;
    case DrawCommandType::kDrawImage:
      out << ",\"resource_id\":\"" << EscapeJson(command.resource_id)
          << "\",\"destination\":";
      WriteRect(out, command.rect);
      break;
    case DrawCommandType::kDrawImageRect:
      out << ",\"resource_id\":\"" << EscapeJson(command.resource_id)
          << "\",\"source\":";
      WriteRect(out, command.source_rect);
      out << ",\"destination\":";
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
    case DrawCommandType::kDrawTextBlob:
      out << ",\"origin\":";
      WritePoint(out, Point{command.rect.x, command.rect.y});
      out << ",\"color\":";
      WriteColor(out, command.color);
      out << ",\"blob_byte_count\":" << command.text_blob_bytes.size();
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
  if (!result.raw_paint_artifact_audit_json.empty()) {
    out << ",\"raw_paint_artifact_audit_json\":"
        << result.raw_paint_artifact_audit_json;
  }
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

std::string SerializePaintArtifactAuditJson(const RenderResult& result) {
  std::map<std::string, int> command_histogram;
  std::map<std::string, int> unsupported_histogram;
  std::map<std::string, int> fallback_histogram;
  int text_blob_count = 0;
  int image_count = 0;
  int shader_count = 0;
  int path_count = 0;
  int filter_count = 0;

  for (const SceneCommand& scene_command : result.frame.scene_commands) {
    if (scene_command.type != SceneCommandType::kDrawCommand) {
      continue;
    }
    const DrawCommand& command = scene_command.draw_command;
    ++command_histogram[ToString(command.type)];
    if (command.type == DrawCommandType::kDrawTextBlob) {
      ++text_blob_count;
    }
    if (command.type == DrawCommandType::kDrawImage ||
        command.type == DrawCommandType::kDrawImageRect) {
      ++image_count;
    }
    if (!command.shader_bytes.empty()) {
      ++shader_count;
    }
    if (!command.path_bytes.empty()) {
      ++path_count;
    }
  }
  for (const std::string& diagnostic : result.diagnostics) {
    const size_t unsupported = diagnostic.find("unsupported op=");
    if (unsupported != std::string::npos) {
      ++unsupported_histogram[diagnostic.substr(unsupported + 15)];
    }
    if (diagnostic.find("bitmap-backed PaintOp resource") !=
            std::string::npos ||
        diagnostic.find("diagnostic_bitmap_fallback") != std::string::npos) {
      ++fallback_histogram["diagnostic_bitmap_fallback"];
    }
    if (diagnostic.find("SaveLayerFilters") != std::string::npos ||
        diagnostic.find("filter") != std::string::npos) {
      ++filter_count;
    }
  }

  if (!result.raw_paint_artifact_audit_json.empty()) {
    std::ostringstream retained;
    retained << ",\"retained_draw_command_histogram\":";
    WriteStringIntMap(retained, command_histogram);
    retained << ",\"extracted_retained_scene\":{\"chunk_count\":"
             << result.frame.scene_chunks.size()
             << ",\"scene_command_count\":" << result.frame.scene_commands.size()
             << ",\"resource_command_count\":"
             << result.frame.resource_commands.size()
             << ",\"chunks\":";
    WriteSceneChunks(retained, result.frame.scene_chunks);
    retained << "}";
    retained << ",\"missing_from_retained\":[]";
    retained << ",\"damage\":{\"requires_full_redraw\":"
             << (result.frame.requires_full_redraw ? "true" : "false")
             << ",\"mapping_source\":\"property_state.transform_to_root\","
             << "\"fallback_full_viewport_reason\":"
             << (result.frame.requires_full_redraw
                     ? "\"conservative retained damage until raw property-tree mapping is complete\""
                     : "null")
             << ",\"damage_bounds\":";
    WriteRect(retained, result.frame.damage_bounds);
    retained << "}";
    retained << ",\"retained_warnings\":";
    WriteStringArray(retained, result.diagnostics);
    retained << ",\"post_replay_typeface_resources\":{\"count\":"
             << StandaloneRendererSameProcessTypefaceResourceCount()
             << ",\"same_process_only\":true"
             << ",\"raw_pointer_payloads\":0"
             << ",\"lookup_attempt_count\":"
             << StandaloneRendererSameProcessTypefaceLookupAttemptCount()
             << ",\"lookup_success_count\":"
             << StandaloneRendererSameProcessTypefaceLookupSuccessCount()
             << ",\"lookup_failure_count\":"
             << StandaloneRendererSameProcessTypefaceLookupFailureCount()
             << ",\"families\":[";
    for (int i = 0; i < StandaloneRendererSameProcessTypefaceResourceCount();
         ++i) {
      char family[256] = {};
      if (StandaloneRendererSameProcessTypefaceFamilyAt(i, family,
                                                        sizeof(family)) <= 0) {
        continue;
      }
      if (i > 0) {
        retained << ",";
      }
      retained << "\"" << EscapeJson(family) << "\"";
    }
    retained << "]}"
             << ",\"replay_text_blob_diagnostics\":{\"enabled\":"
             << (StandaloneRendererTextBlobReplayDiagnosticsEnabled() ? "true"
                                                                       : "false")
             << ",\"strict_typeface_payloads\":true"
             << ",\"retained_blob_count\":" << text_blob_count
             << ",\"deserialize_attempt_count\":"
             << StandaloneRendererTextBlobDeserializeAttemptCount()
             << ",\"deserialize_success_count\":"
             << StandaloneRendererTextBlobDeserializeSuccessCount()
             << ",\"deserialize_failure_count\":"
             << StandaloneRendererTextBlobDeserializeFailureCount()
             << ",\"typeface_resource_count\":"
             << StandaloneRendererSameProcessTypefaceResourceCount()
             << ",\"typeface_lookup_attempt_count\":"
             << StandaloneRendererSameProcessTypefaceLookupAttemptCount()
             << ",\"typeface_lookup_success_count\":"
             << StandaloneRendererSameProcessTypefaceLookupSuccessCount()
             << ",\"typeface_lookup_failure_count\":"
             << StandaloneRendererSameProcessTypefaceLookupFailureCount()
             << ",\"diagnostic_typeface_fallback_count\":"
             << StandaloneRendererDiagnosticTypefaceFallbackCount()
             << ",\"same_process_only\":true"
             << ",\"raw_pointer_payloads\":0}"
             << ",\"post_replay_text_blob_replay\":{\"enabled\":"
             << (StandaloneRendererTextBlobReplayDiagnosticsEnabled() ? "true"
                                                                       : "false")
             << ",\"retained_blob_count\":"
             << text_blob_count
             << ",\"deserialize_attempt_count\":"
             << StandaloneRendererTextBlobDeserializeAttemptCount()
             << ",\"deserialize_success_count\":"
             << StandaloneRendererTextBlobDeserializeSuccessCount()
             << ",\"deserialize_failure_count\":"
             << StandaloneRendererTextBlobDeserializeFailureCount()
             << ",\"typeface_lookup_attempt_count\":"
             << StandaloneRendererSameProcessTypefaceLookupAttemptCount()
             << ",\"typeface_lookup_success_count\":"
             << StandaloneRendererSameProcessTypefaceLookupSuccessCount()
             << ",\"typeface_lookup_failure_count\":"
             << StandaloneRendererSameProcessTypefaceLookupFailureCount()
             << ",\"diagnostic_typeface_fallback_count\":"
             << StandaloneRendererDiagnosticTypefaceFallbackCount()
             << "}";
    retained << ",\"debug_command_coverage\":";
    WriteCommandCoverageRecords(retained);

    std::string raw = result.raw_paint_artifact_audit_json;
    const size_t object_end = raw.find_last_of('}');
    if (object_end != std::string::npos) {
      raw.insert(object_end, retained.str());
      return raw;
    }
  }

  std::ostringstream out;
  out << "{\"source\":\"real Blink PaintArtifact\"";
  out << ",\"viewport\":{\"width\":"
      << result.successor_snapshot.viewport.width << ",\"height\":"
      << result.successor_snapshot.viewport.height << "}";
  out << ",\"device_scale_factor\":1";
  out << ",\"chunk_count\":" << result.frame.scene_chunks.size();
  out << ",\"display_item_count\":null";
  out << ",\"drawing_display_item_count\":null";
  out << ",\"non_drawing_display_item_count\":null";
  out << ",\"op_histogram\":";
  WriteStringIntMap(out, command_histogram);
  out << ",\"unsupported_op_histogram\":";
  WriteStringIntMap(out, unsupported_histogram);
  out << ",\"fallback_rasterized_op_histogram\":";
  WriteStringIntMap(out, fallback_histogram);
  out << ",\"resource_summary\":{\"text_blob_count\":" << text_blob_count
      << ",\"image_count\":" << image_count
      << ",\"shader_count\":" << shader_count
      << ",\"path_count\":" << path_count
      << ",\"filter_count\":" << filter_count << "}";
  out << ",\"chunks\":[";
  for (size_t i = 0; i < result.frame.scene_chunks.size(); ++i) {
    const SceneChunk& chunk = result.frame.scene_chunks[i];
    if (i > 0) {
      out << ",";
    }
    std::map<std::string, int> chunk_histogram;
    for (const DrawCommand& command : chunk.commands) {
      ++chunk_histogram[ToString(command.type)];
    }
    out << "{\"index\":" << i << ",\"id\":\"" << EscapeJson(chunk.chunk_id)
        << "\",\"stable_key\":\"" << EscapeJson(chunk.stable_key)
        << "\",\"bounds\":";
    WriteRect(out, chunk.bounds);
    out << ",\"drawable_bounds\":";
    WriteRect(out, chunk.damage_bounds);
    out << ",\"display_item_begin\":null,\"display_item_end\":null";
    out << ",\"has_text\":"
        << (chunk_histogram["DrawTextBlob"] > 0 ? "true" : "false");
    out << ",\"property_state\":";
    WritePropertyState(out, chunk.property_state);
    out << ",\"op_histogram\":";
    WriteStringIntMap(out, chunk_histogram);
    out << ",\"unsupported_ops\":[],\"fallback_rasterized_ops\":[]";
    out << ",\"display_items\":[]}";
  }
  out << "],\"warnings\":";
  WriteStringArray(out, result.diagnostics);
  out << "}";
  return out.str();
}

}  // namespace html_css_renderer
