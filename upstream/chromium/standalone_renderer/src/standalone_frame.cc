#include "standalone_frame.h"

#include <utility>

#include "html_css_renderer/render_policy.h"

namespace html_css_renderer {
namespace {

std::vector<StandaloneFrameBoundary> BuildBoundaries() {
  return {
      {"page clients", StandaloneFrameSurface::kStandaloneOwned,
       "provide null ChromeClient/PageClients without browser process services"},
      {"frame client", StandaloneFrameSurface::kStandaloneOwned,
       "own a standalone LocalFrameClient replacement for navigation, focus, and lifecycle callbacks"},
      {"document commit", StandaloneFrameSurface::kStandaloneOwned,
       "commit caller-supplied sanitized HTML/CSS from memory"},
      {"resource loading", StandaloneFrameSurface::kStandaloneOwned,
       "resolve images, CSS URLs, SVG references, and fonts through AssetProvider only"},
      {"browser interface broker", StandaloneFrameSurface::kDenied,
       "deny Mojo browser service access and report diagnostics"},
      {"script environment", StandaloneFrameSurface::kDenied,
       "deny scripts, event attributes, javascript URLs, workers, timers, and microtasks"},
      {"navigation and history", StandaloneFrameSurface::kDenied,
       "deny navigation, form submission, page-state restore, preloads, and history mutation"},
      {"scheduler", StandaloneFrameSurface::kStandaloneOwned,
       "sample lifecycle and animation time from FrameInput deterministically"},
      {"document/style/layout", StandaloneFrameSurface::kBlinkOwned,
       "delegate DOM attachment, CSS cascade, style resolution, and layout to reduced Blink once wired"},
      {"paint export", StandaloneFrameSurface::kBlinkOwned,
       "translate Blink paint artifacts and paint records into DrawCommandList"},
  };
}

const char* SurfaceName(StandaloneFrameSurface surface) {
  switch (surface) {
    case StandaloneFrameSurface::kStandaloneOwned:
      return "standalone-owned";
    case StandaloneFrameSurface::kBlinkOwned:
      return "blink-owned";
    case StandaloneFrameSurface::kDenied:
      return "denied";
  }
  return "unknown";
}

void AppendEnvironmentDiagnostics(BlinkLifecycleReport& report,
                                  const BlinkRuntimeEnvironment& environment) {
  const SanitizedDocument document = environment.BuildDocumentForCommit();
  for (const auto& diagnostic : document.diagnostics) {
    report.diagnostics.push_back(diagnostic);
  }
  const auto stylesheets = environment.BuildStylesheetsForCommit();
  for (const auto& stylesheet : stylesheets) {
    for (const auto& diagnostic : stylesheet.diagnostics) {
      report.diagnostics.push_back(diagnostic);
    }
  }
}

}  // namespace

StandaloneFrame::StandaloneFrame(BlinkPageEmbedderCreateInfo create_info)
    : create_info_(std::move(create_info)), boundaries_(BuildBoundaries()) {
  state_.snapshot.html = create_info_.renderer.html;
  state_.snapshot.stylesheets = create_info_.renderer.stylesheets;
  state_.snapshot.viewport = create_info_.renderer.viewport;
  state_.snapshot.device_scale_factor =
      create_info_.renderer.device_scale_factor;
  state_.snapshot.asset_namespace = create_info_.renderer.asset_namespace;
  state_.snapshot.features = create_info_.renderer.features;
}

const RendererCreateInfo& StandaloneFrame::Renderer() const {
  return create_info_.renderer;
}

const RendererSnapshot& StandaloneFrame::Snapshot() const {
  return state_.snapshot;
}

const std::vector<StandaloneFrameBoundary>& StandaloneFrame::Boundaries()
    const {
  return boundaries_;
}

BlinkRuntimeEnvironment StandaloneFrame::EnvironmentForCurrentSnapshot()
    const {
  BlinkRuntimeEnvironmentCreateInfo environment_info;
  environment_info.renderer = create_info_.renderer;
  environment_info.snapshot = state_.snapshot;
  return BlinkRuntimeEnvironment(std::move(environment_info));
}

void StandaloneFrame::AppendBoundaryDiagnostics(
    BlinkLifecycleReport& report) const {
  for (const auto& boundary : boundaries_) {
    report.diagnostics.push_back("StandaloneFrame boundary [" +
                                 std::string(SurfaceName(boundary.surface)) +
                                 "] " + boundary.name + ": " +
                                 boundary.responsibility);
  }
}

void StandaloneFrame::AppendPolicyDiagnostics(
    BlinkLifecycleReport& report) const {
  const BlinkRuntimeEnvironment environment = EnvironmentForCurrentSnapshot();
  AppendEnvironmentDiagnostics(report, environment);
}

BlinkLifecycleReport StandaloneFrame::CreatePage() {
  BlinkLifecycleReport report;
  state_.page_created = true;
  report.page_created = true;
  report.replacements = RequiredBlinkBoundaryReplacements();
  AppendBoundaryDiagnostics(report);
  if (!create_info_.renderer.asset_provider) {
    report.diagnostics.push_back(
        "StandaloneFrame resource loading will report missing assets without AssetProvider");
  }
  report.diagnostics.push_back(
      "StandaloneFrame created mixed frame shell with rewritten browser-facing boundaries");
  return report;
}

BlinkLifecycleReport StandaloneFrame::CommitDocument() {
  BlinkLifecycleReport report;
  state_.page_created = true;
  state_.frame_created = true;
  state_.document_committed = true;
  report.page_created = true;
  report.frame_created = true;
  report.document_committed = true;

  const BlinkRuntimeEnvironment environment = EnvironmentForCurrentSnapshot();
  const SanitizedDocument document = environment.BuildDocumentForCommit();
  state_.snapshot.html = document.html;
  state_.snapshot.stylesheets.clear();
  for (const auto& stylesheet : environment.BuildStylesheetsForCommit()) {
    state_.snapshot.stylesheets.push_back(stylesheet.stylesheet);
  }
  AppendEnvironmentDiagnostics(report, environment);
  report.diagnostics.push_back(
      "StandaloneFrame committed sanitized in-memory document; Blink parser hookup remains behind the frame shell");
  return report;
}

BlinkLifecycleReport StandaloneFrame::UpdateStyle() {
  BlinkLifecycleReport report;
  state_.page_created = true;
  state_.frame_created = true;
  state_.document_committed = true;
  state_.style_updated = true;
  report.page_created = true;
  report.frame_created = true;
  report.document_committed = true;
  report.style_updated = true;
  AppendPolicyDiagnostics(report);
  report.diagnostics.push_back(
      "StandaloneFrame updated style boundary from sanitized author stylesheets");
  return report;
}

BlinkLifecycleReport StandaloneFrame::Layout(const FrameInput& input) {
  BlinkLifecycleReport report;
  state_.page_created = true;
  state_.frame_created = true;
  state_.document_committed = true;
  state_.style_updated = true;
  state_.layout_updated = true;
  report.page_created = true;
  report.frame_created = true;
  report.document_committed = true;
  report.style_updated = true;
  report.layout_updated = true;

  BlinkRuntimeEnvironment environment = EnvironmentForCurrentSnapshot();
  const FrameStateUpdate update = environment.AdvanceFrameState(input);
  state_.snapshot.timeline_time_seconds = update.timeline_time_seconds;
  state_.snapshot.viewport = update.viewport;
  state_.snapshot.scroll_offsets_by_element_id =
      update.scroll_offsets_by_element_id;
  state_.snapshot.focused_element_id = update.focused_element_id;
  state_.snapshot.hovered_element_id = update.hovered_element_id;
  state_.snapshot.active_element_id = update.active_element_id;
  state_.snapshot.form_values_by_element_id = update.form_values_by_element_id;
  for (const auto& diagnostic : update.diagnostics) {
    report.diagnostics.push_back(diagnostic);
  }
  report.diagnostics.push_back(
      "StandaloneFrame advanced deterministic frame state before Blink layout delegation");
  return report;
}

BlinkLifecycleOutput StandaloneFrame::CollectPaint(const FrameInput& input) {
  BlinkLifecycleOutput output;
  if (!state_.layout_updated) {
    const BlinkLifecycleReport layout = Layout(input);
    for (const auto& diagnostic : layout.diagnostics) {
      output.diagnostics.push_back(diagnostic);
    }
  }
  output.next_snapshot = state_.snapshot;

  BlinkRuntimeEnvironment environment = EnvironmentForCurrentSnapshot();
  RendererCreateInfo renderer = environment.Renderer();
  renderer.viewport = state_.snapshot.viewport;
  const SanitizedDocument document = environment.BuildDocumentForCommit();
  renderer.html = document.html;
  for (const auto& diagnostic : document.diagnostics) {
    output.diagnostics.push_back(diagnostic);
  }

  const auto sanitized_stylesheets = environment.BuildStylesheetsForCommit();
  renderer.stylesheets.clear();
  for (const auto& stylesheet : sanitized_stylesheets) {
    renderer.stylesheets.push_back(stylesheet.stylesheet);
    for (const auto& diagnostic : stylesheet.diagnostics) {
      output.diagnostics.push_back(diagnostic);
    }
  }

  const Rect viewport_rect{0.0f, 0.0f, renderer.viewport.width,
                           renderer.viewport.height};
  output.damage_bounds = viewport_rect;
  output.damage_rects.push_back(viewport_rect);
  output.requires_full_redraw = true;
  output.paint_source = BlinkPaintArtifactSource::kStandaloneSnapshot;
  output.real_blink_paint_attempted = create_info_.allow_transitional_v8_link;
  output.real_blink_paint_available = false;
  if (output.real_blink_paint_attempted) {
    output.diagnostics.push_back(
        "real Blink paint artifact requested; waiting for cppgc-backed "
        "Document/Layout/PaintController bridge");
  }
  PaintArtifactChunk background_chunk;
  background_chunk.chunk_id = "blink-artifact:viewport-background";
  background_chunk.bounds = viewport_rect;
  background_chunk.paint_record_ops.push_back(PaintRecordDrawRect(
      viewport_rect, Color::Rgba(1.0f, 1.0f, 1.0f, 1.0f)));
  output.paint_artifact.chunks.push_back(std::move(background_chunk));

  float y = 24.0f;
  const auto resolutions = environment.ResolveDeclaredResources();
  for (const auto& resolution : resolutions) {
    if (!resolution.asset) {
      output.missing_resources.push_back(resolution.reference.id);
      output.diagnostics.push_back(resolution.diagnostic);
      continue;
    }
    if (resolution.reference.element_kind == "image") {
      const Rect image_bounds{16.0f, y, 96.0f, 72.0f};
      PaintArtifactChunk image_chunk;
      image_chunk.chunk_id = "blink-artifact:image:" + resolution.reference.id;
      image_chunk.bounds = image_bounds;
      image_chunk.paint_record_ops.push_back(PaintRecordDrawImageRect(
          resolution.reference.id, Rect{0.0f, 0.0f, 0.0f, 0.0f},
          image_bounds));
      output.paint_artifact.chunks.push_back(std::move(image_chunk));
      output.hit_test_entries.push_back(
          {resolution.reference.id, image_bounds});
      y += 84.0f;
    } else {
      output.diagnostics.push_back("StandaloneFrame resolved " +
                                   resolution.reference.element_kind +
                                   " asset: " + resolution.reference.id);
    }
  }

  const std::string text = ExtractDocumentText(renderer.html);
  if (!text.empty()) {
    GlyphRun text_run;
    text_run.font_id = "standalone-default";
    text_run.font_size = 16.0f;
    text_run.color = Color::Rgba(0.05f, 0.05f, 0.05f, 1.0f);
    text_run.glyph_ids.reserve(text.size());
    text_run.positions.reserve(text.size());
    float x = 16.0f;
    for (const unsigned char c : text) {
      if (c < 0x20) {
        continue;
      }
      text_run.glyph_ids.push_back(static_cast<uint32_t>(c));
      text_run.positions.push_back(Point{x, y});
      x += 8.0f;
    }
    PaintArtifactChunk text_chunk;
    text_chunk.chunk_id = "blink-artifact:text:document-text";
    text_chunk.bounds =
        Rect{16.0f, y - 16.0f, renderer.viewport.width - 32.0f, 24.0f};
    text_chunk.paint_record_ops.push_back(PaintRecordDrawTextBlob(text_run));
    output.paint_artifact.chunks.push_back(std::move(text_chunk));
    output.hit_test_entries.push_back(
         {"document-text",
         Rect{16.0f, y - 16.0f, renderer.viewport.width - 32.0f, 24.0f}});
  }

  output.diagnostics.push_back(
      "StandaloneFrame collected standalone paint artifact snapshot for "
      "retained presentation");
  return output;
}

}  // namespace html_css_renderer
