#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_TYPES_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_TYPES_H_

#include <cstdint>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace html_css_renderer {

struct Point {
  float x = 0.0f;
  float y = 0.0f;
};

struct Size {
  float width = 0.0f;
  float height = 0.0f;
};

struct Rect {
  float x = 0.0f;
  float y = 0.0f;
  float width = 0.0f;
  float height = 0.0f;
};

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
};

struct PointerState {
  int32_t id = 0;
  Point position;
  bool pressed = false;
};

enum class MouseInputEventType {
  kMove = 1,
  kDown = 2,
  kUp = 3,
};

enum class MouseInputButton {
  kNone = 0,
  kLeft = 1,
  kMiddle = 2,
  kRight = 3,
};

struct MouseInputEvent {
  MouseInputEventType type = MouseInputEventType::kMove;
  Point position;
  MouseInputButton button = MouseInputButton::kNone;
  int modifiers = 0;
  int click_count = 0;
};

struct WheelInput {
  Point position;
  Point delta;
};

struct KeyboardState {
  std::vector<uint32_t> pressed_key_codes;
};

enum class FrameResultCollection {
  kFull,
  kMinimal,
};

struct FrameInput {
  double delta_time_seconds = 0.0;
  double timeline_time_seconds = 0.0;
  bool request_png_snapshot = false;
  FrameResultCollection result_collection = FrameResultCollection::kFull;
  std::optional<Size> viewport;
  std::optional<std::string> html_override;
  std::optional<std::vector<Stylesheet>> stylesheets_override;
  std::unordered_map<std::string, std::string> element_attributes_by_id_and_name;
  std::vector<MouseInputEvent> mouse_events;
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

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_COMPOSITOR_TYPES_H_
