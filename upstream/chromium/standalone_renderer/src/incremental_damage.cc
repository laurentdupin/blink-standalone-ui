#include "incremental_damage.h"

#include <algorithm>
#include <optional>
#include <utility>

namespace html_css_renderer {
namespace {

bool SameSize(const Size& a, const Size& b) {
  return a.width == b.width && a.height == b.height;
}

std::optional<Rect> FindHitTestBounds(
    const std::vector<HitTestEntry>& entries,
    const std::string& element_id) {
  if (element_id.empty()) {
    return std::nullopt;
  }
  for (const auto& entry : entries) {
    if (entry.element_id == element_id) {
      return entry.bounds;
    }
  }
  return std::nullopt;
}

}  // namespace

bool SamePointMap(const std::unordered_map<std::string, Point>& a,
                  const std::unordered_map<std::string, Point>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (const auto& entry : a) {
    const auto found = b.find(entry.first);
    if (found == b.end() || found->second.x != entry.second.x ||
        found->second.y != entry.second.y) {
      return false;
    }
  }
  return true;
}

bool SameStringMap(
    const std::unordered_map<std::string, std::string>& a,
    const std::unordered_map<std::string, std::string>& b) {
  if (a.size() != b.size()) {
    return false;
  }
  for (const auto& entry : a) {
    const auto found = b.find(entry.first);
    if (found == b.end() || found->second != entry.second) {
      return false;
    }
  }
  return true;
}

bool SameDocumentInputs(const RendererSnapshot& a, const RendererSnapshot& b) {
  if (a.html != b.html || a.stylesheets.size() != b.stylesheets.size() ||
      !SameSize(a.viewport, b.viewport) ||
      a.device_scale_factor != b.device_scale_factor ||
      a.asset_namespace != b.asset_namespace) {
    return false;
  }
  for (size_t i = 0; i < a.stylesheets.size(); ++i) {
    if (a.stylesheets[i].id != b.stylesheets[i].id ||
        a.stylesheets[i].css != b.stylesheets[i].css) {
      return false;
    }
  }
  return true;
}

bool SameVisualState(const RendererSnapshot& a, const RendererSnapshot& b) {
  return a.focused_element_id == b.focused_element_id &&
         a.hovered_element_id == b.hovered_element_id &&
         a.active_element_id == b.active_element_id &&
         SamePointMap(a.scroll_offsets_by_element_id,
                      b.scroll_offsets_by_element_id) &&
         SameStringMap(a.form_values_by_element_id,
                       b.form_values_by_element_id);
}

Rect UnionRect(Rect a, Rect b) {
  if (a.width <= 0.0f || a.height <= 0.0f) {
    return b;
  }
  if (b.width <= 0.0f || b.height <= 0.0f) {
    return a;
  }
  const float left = std::min(a.x, b.x);
  const float top = std::min(a.y, b.y);
  const float right = std::max(a.x + a.width, b.x + b.width);
  const float bottom = std::max(a.y + a.height, b.y + b.height);
  return Rect{left, top, right - left, bottom - top};
}

Rect EstimateIncrementalDamage(const RendererSnapshot& previous,
                               const RendererSnapshot& successor,
                               const RenderResult& full_result) {
  Rect damage{0.0f, 0.0f, 0.0f, 0.0f};
  auto add_element = [&](const std::string& element_id) {
    if (const auto bounds = FindHitTestBounds(full_result.hit_test_entries,
                                             element_id)) {
      damage = UnionRect(damage, *bounds);
    }
  };

  if (previous.focused_element_id != successor.focused_element_id) {
    add_element(previous.focused_element_id);
    add_element(successor.focused_element_id);
  }
  if (previous.hovered_element_id != successor.hovered_element_id) {
    add_element(previous.hovered_element_id);
    add_element(successor.hovered_element_id);
  }
  if (previous.active_element_id != successor.active_element_id) {
    add_element(previous.active_element_id);
    add_element(successor.active_element_id);
  }

  if (!SameStringMap(previous.form_values_by_element_id,
                     successor.form_values_by_element_id)) {
    for (const auto& value : previous.form_values_by_element_id) {
      add_element(value.first);
    }
    for (const auto& value : successor.form_values_by_element_id) {
      add_element(value.first);
    }
  }

  return damage;
}

void MarkFullRedraw(RenderResult& result, Rect viewport_rect) {
  result.requires_full_redraw = true;
  result.damage_bounds = viewport_rect;
  result.damage_rects.clear();
  result.damage_rects.push_back(viewport_rect);
  result.frame.requires_full_redraw = true;
  result.frame.damage_bounds = viewport_rect;
  result.frame.damage_rects = result.damage_rects;
}

void ApplyIncrementalDamage(const RendererSnapshot& previous,
                            RenderResult& result,
                            const char* diagnostic_prefix) {
  const RendererSnapshot& successor = result.successor_snapshot;
  const Rect viewport_rect{0.0f, 0.0f, successor.viewport.width,
                           successor.viewport.height};
  const std::string prefix = diagnostic_prefix ? diagnostic_prefix : "incremental render";

  if (!SameDocumentInputs(previous, successor) ||
      !SamePointMap(previous.scroll_offsets_by_element_id,
                   successor.scroll_offsets_by_element_id)) {
    MarkFullRedraw(result, viewport_rect);
    result.diagnostics.push_back(prefix + " requires full redraw");
    return;
  }

  if (SameVisualState(previous, successor) &&
      previous.timeline_time_seconds == successor.timeline_time_seconds) {
    result.frame = RenderFrame{};
    result.frame.requires_full_redraw = false;
    result.damage_bounds = Rect{0.0f, 0.0f, 0.0f, 0.0f};
    result.damage_rects.clear();
    result.requires_full_redraw = false;
    result.diagnostics.push_back(prefix + " has no visual damage");
    return;
  }

  const Rect damage = EstimateIncrementalDamage(previous, successor, result);
  if (damage.width <= 0.0f || damage.height <= 0.0f) {
    MarkFullRedraw(result, viewport_rect);
    result.diagnostics.push_back(prefix + " fell back to full redraw");
    return;
  }

  DrawCommandList draw_commands = FlattenSceneDrawCommands(result.frame.scene_commands);
  LoadCommandList load_commands =
      FlattenResourceCommands(result.frame.resource_commands);
  DrawCommandList clipped;
  clipped.reserve(draw_commands.size() + 3);
  clipped.push_back(DrawCommand::Save());
  clipped.push_back(DrawCommand::ClipRect(damage));
  clipped.insert(clipped.end(), draw_commands.begin(), draw_commands.end());
  clipped.push_back(DrawCommand::Restore());
  result.damage_bounds = damage;
  result.damage_rects.clear();
  result.damage_rects.push_back(damage);
  result.requires_full_redraw = false;
  result.frame = BuildFlatRenderFrame(
      load_commands, clipped, successor.viewport, result.damage_rects,
      result.damage_bounds, result.requires_full_redraw, "document");
  result.diagnostics.push_back(prefix + " clipped to damage bounds");
}

}  // namespace html_css_renderer
