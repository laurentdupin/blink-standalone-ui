#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_FRAME_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_FRAME_H_

#include <cstdint>
#include <string>
#include <vector>

#include "html_css_renderer/draw_command.h"
#include "html_css_renderer/load_command.h"

namespace html_css_renderer {

enum class ResourceCommandType {
  kCreateOrUpdateImage,
  kCreateOrUpdateFont,
  kCreateOrUpdateGlyphAtlas,
  kDestroyResource,
};

enum class SceneCommandType {
  kBeginChunk,
  kEndChunk,
  kDrawCommand,
};

enum class RenderPassTargetKind {
  kCallerOwnedFramebuffer,
  kIntermediateSurface,
};

struct ResourceCommand {
  ResourceCommandType type = ResourceCommandType::kCreateOrUpdateImage;
  std::string resource_id;
  LoadCommand load_command;

  static ResourceCommand FromLoadCommand(const LoadCommand& command);
  static ResourceCommand Destroy(std::string resource_id);
};

struct PaintPropertyStateSnapshot {
  uint64_t state_hash = 0;
  Matrix4 transform_to_root;
  bool transform_is_2d = true;
  bool transform_has_perspective = false;
  bool transform_has_non_translation = false;
  uint64_t transform_node_id = 0;
  uint64_t transform_parent_id = 0;
  uint32_t transform_chain_depth = 0;
  bool has_clip_rect = false;
  Rect clip_rect;
  uint64_t clip_node_id = 0;
  uint64_t clip_parent_id = 0;
  uint64_t clip_local_transform_id = 0;
  uint32_t clip_chain_depth = 0;
  bool clip_has_rounded_clip = false;
  bool clip_has_path_clip = false;
  uint64_t effect_node_id = 0;
  uint64_t effect_parent_id = 0;
  uint32_t effect_chain_depth = 0;
  float effect_opacity = 1.0f;
  bool effect_has_non_default_opacity = false;
  bool effect_has_filter = false;
  bool effect_has_backdrop_filter = false;
  bool effect_has_blend_mode = false;
  uint64_t effect_output_clip_id = 0;
  uint64_t scroll_node_id = 0;
  uint64_t scroll_parent_id = 0;
  bool has_scroll_offset = false;
  float scroll_offset_x = 0.0f;
  float scroll_offset_y = 0.0f;
  Rect scroll_container_rect;
  Rect scroll_contents_rect;
};
struct SceneChunk {
  int debug_index = -1;
  std::string stable_key;
  std::string chunk_id;
  Rect bounds;
  Rect damage_bounds;
  PaintPropertyStateSnapshot property_state;
  uint64_t content_hash = 0;
  uint64_t resource_hash = 0;
  bool retained_from_previous_frame = false;
  DrawCommandList commands;
};

struct SceneCommand {
  SceneCommandType type = SceneCommandType::kDrawCommand;
  std::string chunk_id;
  Rect bounds;
  DrawCommand draw_command;

  static SceneCommand BeginChunk(std::string chunk_id, Rect bounds);
  static SceneCommand EndChunk(std::string chunk_id);
  static SceneCommand Draw(DrawCommand command);
};

struct RenderPass {
  std::string pass_id = "root";
  RenderPassTargetKind target_kind =
      RenderPassTargetKind::kCallerOwnedFramebuffer;
  Rect viewport;
  size_t first_scene_command = 0;
  size_t scene_command_count = 0;
  bool clear_before_render = true;
  Color clear_color = Color::Rgba(0.0f, 0.0f, 0.0f, 0.0f);
};

struct RenderFrame {
  std::vector<ResourceCommand> resource_commands;
  std::vector<SceneChunk> scene_chunks;
  std::vector<SceneCommand> scene_commands;
  std::vector<RenderPass> render_passes;
  std::vector<Rect> damage_rects;
  Rect damage_bounds;
  bool requires_full_redraw = true;
};

const char* ToString(ResourceCommandType type);
const char* ToString(SceneCommandType type);
const char* ToString(RenderPassTargetKind kind);
RenderFrame BuildFlatRenderFrame(const LoadCommandList& load_commands,
                                 const DrawCommandList& draw_commands,
                                 Size viewport,
                                 const std::vector<Rect>& damage_rects,
                                 Rect damage_bounds,
                                 bool requires_full_redraw,
                                 std::string chunk_id);
LoadCommandList FlattenResourceCommands(
    const std::vector<ResourceCommand>& resource_commands);
DrawCommandList FlattenSceneDrawCommands(
    const std::vector<SceneCommand>& scene_commands);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_FRAME_H_
