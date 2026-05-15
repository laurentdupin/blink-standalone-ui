#include "html_css_renderer/render_frame.h"

#include <utility>

namespace html_css_renderer {

ResourceCommand ResourceCommand::FromLoadCommand(const LoadCommand& command) {
  ResourceCommand resource;
  resource.load_command = command;
  switch (command.type) {
    case LoadCommandType::kLoadImage:
      resource.type = ResourceCommandType::kCreateOrUpdateImage;
      resource.resource_id = command.image.image_id.empty()
                                 ? command.image.resource_id
                                 : command.image.image_id;
      break;
    case LoadCommandType::kLoadFont:
      resource.type = ResourceCommandType::kCreateOrUpdateFont;
      resource.resource_id = command.font.font_id.empty()
                                 ? command.font.resource_id
                                 : command.font.font_id;
      break;
    case LoadCommandType::kGlyphAtlasUpdate:
      resource.type = ResourceCommandType::kCreateOrUpdateGlyphAtlas;
      resource.resource_id = command.glyph_atlas_update.atlas_id;
      break;
  }
  return resource;
}

ResourceCommand ResourceCommand::Destroy(std::string resource_id) {
  ResourceCommand resource;
  resource.type = ResourceCommandType::kDestroyResource;
  resource.resource_id = std::move(resource_id);
  return resource;
}

ResourceCommand ResourceCommand::LoadTypeface(
    uint64_t typeface_id,
    std::string family_name,
    int weight,
    int width,
    std::string slant,
    bool same_process_only,
    bool portable_font_data_available) {
  ResourceCommand resource;
  resource.type = ResourceCommandType::kLoadTypeface;
  resource.typeface_resource_id = typeface_id;
  resource.resource_id = "typeface-" + std::to_string(typeface_id);
  resource.family_name = std::move(family_name);
  resource.font_weight = weight;
  resource.font_width = width;
  resource.font_slant = std::move(slant);
  resource.same_process_only = same_process_only;
  resource.portable_font_data_available = portable_font_data_available;
  resource.portability_status =
      portable_font_data_available ? "portable_font_data" : "same_process_only";
  return resource;
}

ResourceCommand ResourceCommand::LoadTextBlob(
    uint64_t text_blob_id,
    std::vector<uint8_t> blob_bytes,
    std::vector<uint64_t> typeface_ids,
    Rect bounds,
    std::string portability_status) {
  ResourceCommand resource;
  resource.type = ResourceCommandType::kLoadTextBlob;
  resource.text_blob_resource_id = text_blob_id;
  resource.resource_id = "text-blob-" + std::to_string(text_blob_id);
  resource.serialized_text_blob_bytes = std::move(blob_bytes);
  resource.dependent_typeface_resource_ids = std::move(typeface_ids);
  resource.resource_bounds = bounds;
  resource.portability_status = std::move(portability_status);
  resource.same_process_only = resource.portability_status == "same_process_only";
  return resource;
}

SceneCommand SceneCommand::BeginChunk(std::string chunk_id, Rect bounds) {
  SceneCommand command;
  command.type = SceneCommandType::kBeginChunk;
  command.chunk_id = std::move(chunk_id);
  command.bounds = bounds;
  return command;
}

SceneCommand SceneCommand::EndChunk(std::string chunk_id) {
  SceneCommand command;
  command.type = SceneCommandType::kEndChunk;
  command.chunk_id = std::move(chunk_id);
  return command;
}

SceneCommand SceneCommand::Draw(DrawCommand draw_command) {
  SceneCommand command;
  command.type = SceneCommandType::kDrawCommand;
  command.draw_command = std::move(draw_command);
  return command;
}

const char* ToString(ResourceCommandType type) {
  switch (type) {
    case ResourceCommandType::kCreateOrUpdateImage:
      return "CreateOrUpdateImage";
    case ResourceCommandType::kCreateOrUpdateFont:
      return "CreateOrUpdateFont";
    case ResourceCommandType::kCreateOrUpdateGlyphAtlas:
      return "CreateOrUpdateGlyphAtlas";
    case ResourceCommandType::kLoadTypeface:
      return "LoadTypeface";
    case ResourceCommandType::kLoadTextBlob:
      return "LoadTextBlob";
    case ResourceCommandType::kDestroyResource:
      return "DestroyResource";
  }
  return "Unknown";
}

const char* ToString(SceneCommandType type) {
  switch (type) {
    case SceneCommandType::kBeginChunk:
      return "BeginChunk";
    case SceneCommandType::kEndChunk:
      return "EndChunk";
    case SceneCommandType::kDrawCommand:
      return "DrawCommand";
  }
  return "Unknown";
}

const char* ToString(RenderPassTargetKind kind) {
  switch (kind) {
    case RenderPassTargetKind::kCallerOwnedFramebuffer:
      return "CallerOwnedFramebuffer";
    case RenderPassTargetKind::kIntermediateSurface:
      return "IntermediateSurface";
  }
  return "Unknown";
}

RenderFrame BuildFlatRenderFrame(const LoadCommandList& load_commands,
                                 const DrawCommandList& draw_commands,
                                 Size viewport,
                                 const std::vector<Rect>& damage_rects,
                                 Rect damage_bounds,
                                 bool requires_full_redraw,
                                 std::string chunk_id) {
  RenderFrame frame;
  frame.damage_rects = damage_rects;
  frame.damage_bounds = damage_bounds;
  frame.requires_full_redraw = requires_full_redraw;
  frame.resource_commands.reserve(load_commands.size());
  for (const LoadCommand& command : load_commands) {
    frame.resource_commands.push_back(ResourceCommand::FromLoadCommand(command));
  }

  SceneChunk chunk;
  chunk.chunk_id = std::move(chunk_id);
  chunk.bounds = Rect{0.0f, 0.0f, viewport.width, viewport.height};
  chunk.damage_bounds = damage_bounds;
  chunk.retained_from_previous_frame = !requires_full_redraw;
  chunk.commands = draw_commands;

  frame.scene_commands.push_back(
      SceneCommand::BeginChunk(chunk.chunk_id, chunk.bounds));
  for (const DrawCommand& command : chunk.commands) {
    frame.scene_commands.push_back(SceneCommand::Draw(command));
  }
  frame.scene_commands.push_back(SceneCommand::EndChunk(chunk.chunk_id));
  frame.scene_chunks.push_back(std::move(chunk));

  RenderPass pass;
  pass.pass_id = "root";
  pass.viewport = Rect{0.0f, 0.0f, viewport.width, viewport.height};
  pass.first_scene_command = 0;
  pass.scene_command_count = frame.scene_commands.size();
  pass.clear_before_render = requires_full_redraw;
  frame.render_passes.push_back(pass);
  return frame;
}

LoadCommandList FlattenResourceCommands(
    const std::vector<ResourceCommand>& resource_commands) {
  LoadCommandList load_commands;
  for (const ResourceCommand& command : resource_commands) {
    if (command.type == ResourceCommandType::kCreateOrUpdateImage ||
        command.type == ResourceCommandType::kCreateOrUpdateFont ||
        command.type == ResourceCommandType::kCreateOrUpdateGlyphAtlas) {
      load_commands.push_back(command.load_command);
    }
  }
  return load_commands;
}

DrawCommandList FlattenSceneDrawCommands(
    const std::vector<SceneCommand>& scene_commands) {
  DrawCommandList draw_commands;
  for (const SceneCommand& command : scene_commands) {
    if (command.type == SceneCommandType::kDrawCommand) {
      draw_commands.push_back(command.draw_command);
    }
  }
  return draw_commands;
}

}  // namespace html_css_renderer
