#include "html_css_renderer/renderer.h"

#include <algorithm>
#include <sstream>
#include <utility>

#include "html_css_renderer/paint_translator.h"
#include "html_css_renderer/render_policy.h"
#include "incremental_damage.h"

namespace html_css_renderer {
namespace {

void AppendDiagnostic(RenderResult& result, std::string message) {
  result.diagnostics.push_back(message);
}

std::optional<Color> ParseHexColor(const std::string& value) {
  const size_t hash = value.find('#');
  if (hash == std::string::npos || hash + 6 >= value.size()) {
    return std::nullopt;
  }

  auto parse_byte = [](const std::string& s) -> std::optional<int> {
    int value = 0;
    for (char c : s) {
      value *= 16;
      if (c >= '0' && c <= '9') {
        value += c - '0';
      } else if (c >= 'a' && c <= 'f') {
        value += 10 + c - 'a';
      } else if (c >= 'A' && c <= 'F') {
        value += 10 + c - 'A';
      } else {
        return std::nullopt;
      }
    }
    return value;
  };

  const auto red = parse_byte(value.substr(hash + 1, 2));
  const auto green = parse_byte(value.substr(hash + 3, 2));
  const auto blue = parse_byte(value.substr(hash + 5, 2));
  if (!red || !green || !blue) {
    return std::nullopt;
  }
  return Color::Rgba(*red / 255.0f, *green / 255.0f, *blue / 255.0f, 1.0f);
}

Color ResolveBackgroundColor(const RendererCreateInfo& create_info) {
  for (const auto& sheet : create_info.stylesheets) {
    const std::string lower = ToLowerAscii(sheet.css);
    if (lower.find("background") != std::string::npos) {
      if (auto parsed = ParseHexColor(sheet.css)) {
        return *parsed;
      }
    }
  }

  if (auto parsed = ParseHexColor(create_info.html)) {
    return *parsed;
  }

  return Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f);
}

void AppendPaintDiagnostics(RenderResult& result,
                            const PaintTranslationResult& paint_result) {
  for (const auto& diagnostic : paint_result.diagnostics) {
    result.diagnostics.push_back(diagnostic);
  }
}

bool HasTextBackend(const RendererCreateInfo& create_info) {
  return create_info.font_provider && create_info.text_shaper &&
         create_info.glyph_rasterizer;
}

}  // namespace

std::unique_ptr<RendererState> RendererState::Create(
    RendererCreateInfo create_info) {
  return std::unique_ptr<RendererState>(
      new RendererState(std::move(create_info)));
}

std::unique_ptr<RendererState> RendererState::Restore(
    RendererSnapshot snapshot,
    AssetProvider* asset_provider) {
  RendererCreateInfo create_info;
  create_info.html = std::move(snapshot.html);
  create_info.stylesheets = std::move(snapshot.stylesheets);
  create_info.viewport = snapshot.viewport;
  create_info.device_scale_factor = snapshot.device_scale_factor;
  create_info.asset_namespace = std::move(snapshot.asset_namespace);
  create_info.features = snapshot.features;
  create_info.asset_provider = asset_provider;

  auto state = std::unique_ptr<RendererState>(
      new RendererState(std::move(create_info)));
  state->timeline_time_seconds_ = snapshot.timeline_time_seconds;
  state->scroll_offsets_by_element_id_ =
      std::move(snapshot.scroll_offsets_by_element_id);
  state->focused_element_id_ = std::move(snapshot.focused_element_id);
  state->hovered_element_id_ = std::move(snapshot.hovered_element_id);
  state->active_element_id_ = std::move(snapshot.active_element_id);
  state->form_values_by_element_id_ =
      std::move(snapshot.form_values_by_element_id);
  return state;
}

RendererState::RendererState(RendererCreateInfo create_info)
    : create_info_(std::move(create_info)) {}

RendererState::RendererState(const RendererState&) = default;
RendererState& RendererState::operator=(const RendererState&) = default;
RendererState::RendererState(RendererState&&) noexcept = default;
RendererState& RendererState::operator=(RendererState&&) noexcept = default;
RendererState::~RendererState() = default;

std::unique_ptr<RendererState> RendererState::Fork() const {
  return std::make_unique<RendererState>(*this);
}

RendererSnapshot RendererState::Snapshot() const {
  RendererSnapshot snapshot;
  snapshot.html = create_info_.html;
  snapshot.stylesheets = create_info_.stylesheets;
  snapshot.viewport = create_info_.viewport;
  snapshot.device_scale_factor = create_info_.device_scale_factor;
  snapshot.asset_namespace = create_info_.asset_namespace;
  snapshot.features = create_info_.features;
  snapshot.timeline_time_seconds = timeline_time_seconds_;
  snapshot.scroll_offsets_by_element_id = scroll_offsets_by_element_id_;
  snapshot.focused_element_id = focused_element_id_;
  snapshot.hovered_element_id = hovered_element_id_;
  snapshot.active_element_id = active_element_id_;
  snapshot.form_values_by_element_id = form_values_by_element_id_;
  return snapshot;
}

RenderResult RendererState::AdvanceAndRender(const FrameInput& input) {
  RenderResult result;
  LoadCommandList load_commands;
  DrawCommandList draw_commands;
  const FrameStateUpdate state_update = BuildFrameStateUpdate(Snapshot(), input);
  timeline_time_seconds_ = state_update.timeline_time_seconds;
  create_info_.viewport = state_update.viewport;
  scroll_offsets_by_element_id_ = state_update.scroll_offsets_by_element_id;
  focused_element_id_ = state_update.focused_element_id;
  hovered_element_id_ = state_update.hovered_element_id;
  active_element_id_ = state_update.active_element_id;
  form_values_by_element_id_ = state_update.form_values_by_element_id;
  for (const auto& diagnostic : state_update.diagnostics) {
    AppendDiagnostic(result, diagnostic);
  }

  const Rect viewport_rect{0.0f, 0.0f, create_info_.viewport.width,
                           create_info_.viewport.height};
  MarkFullRedraw(result, viewport_rect);
  std::vector<PaintOp> paint_ops;
  paint_ops.push_back(
      PaintFillRect(viewport_rect, ResolveBackgroundColor(create_info_)));

  const SanitizedDocument safe_document =
      SanitizeHtmlForRendering(create_info_.html);
  for (const auto& diagnostic : safe_document.diagnostics) {
    AppendDiagnostic(result, diagnostic);
  }
  std::vector<Stylesheet> safe_stylesheets;
  const auto sanitized_stylesheets =
      SanitizeStylesheetsForRendering(create_info_.stylesheets);
  safe_stylesheets.reserve(sanitized_stylesheets.size());
  for (const auto& stylesheet : sanitized_stylesheets) {
    safe_stylesheets.push_back(stylesheet.stylesheet);
    for (const auto& diagnostic : stylesheet.diagnostics) {
      AppendDiagnostic(result, diagnostic);
    }
  }

  float y = 24.0f;
  std::string active_font_id;
  const auto resource_references =
      ExtractResourceReferences(safe_document.html, safe_stylesheets);
  const auto resource_resolutions = ResolveResourceReferences(
      resource_references, create_info_.asset_provider);
  for (const auto& resolution : resource_resolutions) {
    const std::string& resource_id = resolution.reference.id;
    if (!resolution.asset) {
      result.missing_resources.push_back(resource_id);
      AppendDiagnostic(result, resolution.diagnostic);
    } else if (resolution.reference.element_kind == "image") {
      ImageLoadInfo image;
      image.image_id = resource_id;
      image.resource_id = resource_id;
      image.mime_type = resolution.asset->mime_type;
      image.byte_count = resolution.asset->bytes.size();
      image.bytes_hash = HashBytes(resolution.asset->bytes);
      load_commands.push_back(LoadCommand::LoadImage(std::move(image)));
      paint_ops.push_back(
          PaintDrawImage(resource_id, Rect{16.0f, y, 96.0f, 72.0f}));
      result.hit_test_entries.push_back(
          HitTestEntry{resource_id, Rect{16.0f, y, 96.0f, 72.0f}});
      y += 84.0f;
    } else if (resolution.reference.element_kind == "font") {
      FontLoadInfo font;
      font.font_id = resource_id;
      font.resource_id = resource_id;
      font.mime_type = resolution.asset->mime_type;
      font.byte_count = resolution.asset->bytes.size();
      font.bytes_hash = HashBytes(resolution.asset->bytes);
      load_commands.push_back(LoadCommand::LoadFont(std::move(font)));
      active_font_id = resource_id;
      if (HasTextBackend(create_info_)) {
        FontAsset font_asset;
        font_asset.font_id = resource_id;
        font_asset.resource_id = resource_id;
        font_asset.mime_type = resolution.asset->mime_type;
        font_asset.bytes = resolution.asset->bytes;
        if (create_info_.font_provider->RegisterFont(font_asset)) {
          AppendDiagnostic(result,
                           "registered font asset for text backend: " +
                               resource_id);
        } else {
          AppendDiagnostic(result,
                           "failed to register font asset for text backend: " +
                               resource_id);
          active_font_id.clear();
        }
      }
      AppendDiagnostic(result, "resolved font asset: " + resource_id);
    } else {
      AppendDiagnostic(result, "resolved " + resolution.reference.element_kind +
                                   " asset: " + resource_id);
    }
  }

  std::string text = ExtractDocumentText(safe_document.html);
  if (!text.empty()) {
    const Point text_origin{16.0f, y};
    const Color text_color = Color::Rgba(0.05f, 0.05f, 0.05f, 1.0f);
    constexpr float kFontSize = 16.0f;
    if (HasTextBackend(create_info_) && !active_font_id.empty()) {
      TextShapeInput shape_input;
      shape_input.text = text;
      shape_input.font_id = active_font_id;
      shape_input.font_size = kFontSize;
      shape_input.direction = TextDirection::kLeftToRight;
      shape_input.origin = text_origin;
      shape_input.color = text_color;
      const TextShapeResult shaped =
          create_info_.text_shaper->ShapeText(shape_input);
      for (const auto& diagnostic : shaped.diagnostics) {
        AppendDiagnostic(result, diagnostic);
      }
      if (!shaped.glyph_run.glyph_ids.empty()) {
        GlyphRasterInput raster_input;
        raster_input.glyph_run = shaped.glyph_run;
        raster_input.atlas_id = "document-text-atlas";
        const GlyphRasterResult rasterized =
            create_info_.glyph_rasterizer->RasterizeGlyphs(raster_input);
        for (const auto& update : rasterized.atlas_updates) {
          load_commands.push_back(LoadCommand::UpdateGlyphAtlas(update));
        }
        for (const auto& diagnostic : rasterized.diagnostics) {
          AppendDiagnostic(result, diagnostic);
        }
        paint_ops.push_back(PaintDrawGlyphRun(shaped.glyph_run));
      } else {
        AppendDiagnostic(result, "text shaping produced no glyphs");
      }
    } else {
      AppendDiagnostic(result, "text backend unavailable; no text emitted");
    }
    result.hit_test_entries.push_back(
        HitTestEntry{"document-text", Rect{16.0f, y - 16.0f,
                                           create_info_.viewport.width - 32.0f,
                                           24.0f}});
  }

  const PaintTranslationResult paint_result =
      PaintTranslator().Translate(paint_ops);
  draw_commands.insert(draw_commands.end(), paint_result.draw_commands.begin(),
                       paint_result.draw_commands.end());
  result.damage_bounds = paint_result.damage_bounds.width > 0.0f &&
                                 paint_result.damage_bounds.height > 0.0f
                             ? paint_result.damage_bounds
                             : viewport_rect;
  result.damage_rects.clear();
  result.damage_rects.push_back(result.damage_bounds);
  AppendPaintDiagnostics(result, paint_result);

  if (!focused_element_id_.empty()) {
    AppendDiagnostic(result, "focused element: " + focused_element_id_);
  }
  if (!hovered_element_id_.empty()) {
    AppendDiagnostic(result, "hovered element: " + hovered_element_id_);
  }
  if (!active_element_id_.empty()) {
    AppendDiagnostic(result, "active element: " + active_element_id_);
  }
  for (const auto& form_value : form_values_by_element_id_) {
    AppendDiagnostic(result, "form value: " + form_value.first);
  }

  result.successor_snapshot = Snapshot();
  result.frame = BuildFlatRenderFrame(
      load_commands, draw_commands, create_info_.viewport, result.damage_rects,
      result.damage_bounds, result.requires_full_redraw, "document");
  return result;
}

RenderResult RendererState::AdvanceAndRenderIncremental(
    const FrameInput& input) {
  const RendererSnapshot previous = Snapshot();
  RenderResult result = AdvanceAndRender(input);
  ApplyIncrementalDamage(previous, result, "incremental render");
  return result;
}

}  // namespace html_css_renderer
