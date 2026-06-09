#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_FRAME_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDER_FRAME_H_

#include <array>
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
  kLoadTypeface,
  kLoadTextBlob,
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
  uint64_t typeface_resource_id = 0;
  uint64_t text_blob_resource_id = 0;
  std::vector<uint64_t> dependent_typeface_resource_ids;
  std::vector<uint8_t> serialized_text_blob_bytes;
  Rect resource_bounds;
  std::string family_name;
  int font_weight = 0;
  int font_width = 0;
  std::string font_slant;
  std::string portability_status;
  bool same_process_only = false;
  bool portable_font_data_available = false;

  static ResourceCommand FromLoadCommand(const LoadCommand& command);
  static ResourceCommand LoadTypeface(uint64_t typeface_id,
                                      std::string family_name,
                                      int weight,
                                      int width,
                                      std::string slant,
                                      bool same_process_only,
                                      bool portable_font_data_available);
  static ResourceCommand LoadTextBlob(uint64_t text_blob_id,
                                      std::vector<uint8_t> blob_bytes,
                                      std::vector<uint64_t> typeface_ids,
                                      Rect bounds,
                                      std::string portability_status);
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
  bool has_clip_rrect = false;
  Rect clip_rrect;
  std::array<Point, 4> clip_rrect_radii = {};
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
  bool effect_has_unsupported_filter = false;
  bool effect_has_backdrop_filter = false;
  bool effect_has_blend_mode = false;
  int effect_blend_mode = 3;
  uint64_t effect_output_clip_id = 0;
  std::vector<FilterOperationSnapshot> effect_filter_operations;
  uint64_t scroll_node_id = 0;
  uint64_t scroll_parent_id = 0;
  bool has_scroll_offset = false;
  float scroll_offset_x = 0.0f;
  float scroll_offset_y = 0.0f;
  Rect scroll_container_rect;
  Rect scroll_contents_rect;
};

struct FinerCacheUnitDescriptor {
  std::string stable_key;
  int parent_chunk_debug_index = -1;
  std::string parent_chunk_stable_key;
  int unit_index = -1;
  int begin_display_item_index = -1;
  int end_display_item_index = -1;
  uint64_t display_item_client_id = 0;
  bool display_item_client_id_valid = false;
  Rect visual_bounds;
  uint64_t content_hash = 0;
  uint64_t resource_signal_hash = 0;
  int display_item_count = 0;
  int drawing_item_count = 0;
  int paint_op_count = 0;
  int recursive_paint_op_count = 0;
  int visual_op_count = 0;
  bool translated_command_span_available = false;
  int translated_command_begin_index = -1;
  int translated_command_end_index = -1;
  bool scene_command_span_available = false;
  int scene_command_begin_index = -1;
  int scene_command_end_index = -1;
  bool flattened_draw_command_span_available = false;
  int flattened_draw_command_begin_index = -1;
  int flattened_draw_command_end_index = -1;
  bool entry_local_save_depth_available = false;
  int entry_local_save_depth = -1;
  bool entry_clip_bounds_available = false;
  Rect entry_clip_bounds;
  bool entry_transform_available = false;
  Matrix4 entry_transform;
  bool entry_effect_layer_depth_available = false;
  int entry_effect_layer_depth = -1;
  std::string entry_state_status = "unavailable";
  bool entry_state_complete = false;
  std::vector<std::string> entry_state_blockers;
  std::string entry_clip_kind = "unavailable";
  std::string entry_transform_kind = "unavailable";
  bool conservative_candidate = false;
  bool has_save_layer_ops = false;
  bool has_non_rect_clip_ops = false;
  bool has_non_translation_transform = false;
  bool has_effect_opacity = false;
  bool has_shader_ops = false;
  bool has_image_ops = false;
  bool has_path_ops = false;
  bool has_filter_ops = false;
  bool has_path_effect_ops = false;
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
  std::vector<FinerCacheUnitDescriptor> finer_cache_units;
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
  bool allows_scroll_translation_reuse = false;
  Point scroll_translation_delta;
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
