#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_H_

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "html_css_renderer/draw_command.h"
#include "html_css_renderer/load_command.h"
#include "html_css_renderer/render_frame.h"
#include "html_css_renderer/text_engine.h"

namespace html_css_renderer {

struct Stylesheet {
  std::string id;
  std::string css;
};

struct Asset {
  std::string id;
  std::string mime_type;
  std::vector<uint8_t> bytes;
};

class AssetProvider {
 public:
  virtual ~AssetProvider() = default;
  virtual std::optional<Asset> Load(const std::string& resource_id) = 0;
};

struct RendererCreateInfo {
  std::string html;
  std::vector<Stylesheet> stylesheets;
  Size viewport = {800.0f, 600.0f};
  float device_scale_factor = 1.0f;
  std::string asset_namespace;
  AssetProvider* asset_provider = nullptr;
  FontProvider* font_provider = nullptr;
  TextShaper* text_shaper = nullptr;
  GlyphRasterizer* glyph_rasterizer = nullptr;
};

struct PointerState {
  int32_t id = 0;
  Point position;
  bool pressed = false;
};

struct WheelInput {
  Point position;
  Point delta;
};

struct KeyboardState {
  std::vector<uint32_t> pressed_key_codes;
};

struct FrameInput {
  double delta_time_seconds = 0.0;
  double timeline_time_seconds = 0.0;
  std::optional<Size> viewport;
  std::optional<std::string> html_override;
  std::optional<std::vector<Stylesheet>> stylesheets_override;
  std::unordered_map<std::string, std::string> element_attributes_by_id_and_name;
  std::vector<PointerState> pointers;
  std::optional<WheelInput> wheel;
  KeyboardState keyboard;
  std::unordered_map<std::string, Point> scroll_offsets_by_element_id;
  std::string focused_element_id;
  std::string hovered_element_id;
  std::string active_element_id;
  std::unordered_map<std::string, std::string> form_values_by_element_id;
};

struct RendererSnapshot {
  std::string html;
  std::vector<Stylesheet> stylesheets;
  Size viewport;
  float device_scale_factor = 1.0f;
  std::string asset_namespace;
  double timeline_time_seconds = 0.0;
  std::unordered_map<std::string, std::string> element_attributes_by_id_and_name;
  std::unordered_map<std::string, Point> scroll_offsets_by_element_id;
  std::string focused_element_id;
  std::string hovered_element_id;
  std::string active_element_id;
  std::unordered_map<std::string, std::string> form_values_by_element_id;
};

struct HitTestEntry {
  std::string element_id;
  Rect bounds;
};

struct ScrollableElementEntry {
  std::string element_id;
  Rect bounds;
  Point scroll_offset;
  Point max_scroll_offset;
  bool can_scroll_x = false;
  bool can_scroll_y = false;
};

struct SkippedTransformDiagnostic {
  std::string reason;
  Matrix4 matrix;
  Rect chunk_bounds;
  uint64_t transform_node_id = 0;
  uint64_t transform_parent_id = 0;
  uint32_t transform_chain_depth = 0;
  uint64_t scroll_node_id = 0;
  uint32_t clip_chain_depth = 0;
  uint32_t effect_chain_depth = 0;
  std::string source_chunk_key;
};

struct FrameWorkDiagnostics {
  bool no_change_fast_path = false;
  bool needs_document_commit = false;
  bool needs_style = false;
  bool needs_layout = false;
  bool needs_prepaint = false;
  bool needs_paint = false;
  bool needs_composite_translation = false;
  bool needs_raster = false;
  bool needs_present = false;
  bool needs_begin_frame = false;
  int document_commit_count = 0;
  int style_update_count = 0;
  int layout_count = 0;
  int prepaint_count = 0;
  int paint_count = 0;
  int paint_artifact_translation_count = 0;
  int retained_scene_plan_count = 0;
};

struct RenderResult {
  RenderFrame frame;
  Rect damage_bounds;
  std::vector<Rect> damage_rects;
  bool requires_full_redraw = true;
  bool needs_begin_frame = false;
  FrameWorkDiagnostics frame_work;
  std::string raw_paint_artifact_audit_json;
  std::vector<HitTestEntry> hit_test_entries;
  std::vector<ScrollableElementEntry> scrollable_element_entries;
  Point document_max_scroll_offset;
  std::vector<SkippedTransformDiagnostic> skipped_transform_diagnostics;
  std::vector<std::string> diagnostics;
  std::vector<std::string> missing_resources;
  RendererSnapshot successor_snapshot;
};

class RendererState {
 public:
  static std::unique_ptr<RendererState> Create(RendererCreateInfo create_info);
  static std::unique_ptr<RendererState> Restore(RendererSnapshot snapshot,
                                                AssetProvider* asset_provider);

  RendererState(const RendererState&);
  RendererState& operator=(const RendererState&);
  RendererState(RendererState&&) noexcept;
  RendererState& operator=(RendererState&&) noexcept;
  ~RendererState();

  std::unique_ptr<RendererState> Fork() const;
  RendererSnapshot Snapshot() const;
  RenderResult AdvanceAndRender(const FrameInput& input);
  RenderResult AdvanceAndRenderIncremental(const FrameInput& input);

 private:
  explicit RendererState(RendererCreateInfo create_info);

  RendererCreateInfo create_info_;
  double timeline_time_seconds_ = 0.0;
  std::unordered_map<std::string, Point> scroll_offsets_by_element_id_;
  std::string focused_element_id_;
  std::string hovered_element_id_;
  std::string active_element_id_;
  std::unordered_map<std::string, std::string> form_values_by_element_id_;
};

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_RENDERER_H_
