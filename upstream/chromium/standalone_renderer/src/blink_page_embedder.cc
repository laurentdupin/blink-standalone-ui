#include "html_css_renderer/blink_adapter.h"

#include <memory>
#include <optional>
#include <utility>

#include "html_css_renderer/blink_runtime_environment.h"
#include "html_css_renderer/render_policy.h"
#include "html_css_renderer/retained_scene.h"
#include "incremental_damage.h"

namespace html_css_renderer {
namespace {

RendererSnapshot InitialSnapshotFromRenderer(const RendererCreateInfo& renderer) {
  RendererSnapshot snapshot;
  snapshot.html = renderer.html;
  snapshot.stylesheets = renderer.stylesheets;
  snapshot.viewport = renderer.viewport;
  snapshot.device_scale_factor = renderer.device_scale_factor;
  snapshot.asset_namespace = renderer.asset_namespace;
  snapshot.features = renderer.features;
  return snapshot;
}

Point DocumentScrollOffset(const RendererSnapshot& snapshot) {
  const auto document_scroll =
      snapshot.scroll_offsets_by_element_id.find("document");
  if (document_scroll != snapshot.scroll_offsets_by_element_id.end()) {
    return document_scroll->second;
  }
  const auto body_scroll = snapshot.scroll_offsets_by_element_id.find("body");
  if (body_scroll != snapshot.scroll_offsets_by_element_id.end()) {
    return body_scroll->second;
  }
  return Point{};
}

Rect ViewportRect(const RendererSnapshot& snapshot) {
  return Rect{0.0f, 0.0f, snapshot.viewport.width, snapshot.viewport.height};
}

const char* PaintSourceName(BlinkPaintArtifactSource source) {
  switch (source) {
    case BlinkPaintArtifactSource::kNone:
      return "none";
    case BlinkPaintArtifactSource::kStandaloneSnapshot:
      return "standalone snapshot";
    case BlinkPaintArtifactSource::kReducedBlinkExport:
      return "reduced Blink export";
    case BlinkPaintArtifactSource::kRealBlinkPaintArtifact:
      return "real Blink PaintArtifact";
  }
  return "unknown";
}

void ApplyRetainedPresentationToResult(const RetainedScene& current_scene,
                                       const RetainedScene* previous_scene,
                                       Point current_scroll_offset,
                                       Point previous_scroll_offset,
                                       RenderResult& result) {
  const PresentationUpdatePlan plan = PlanPresentationUpdate(
      current_scene, previous_scene, result.successor_snapshot.viewport,
      current_scroll_offset, previous_scroll_offset);
  result.frame = BuildRenderFrame(current_scene, {}, plan);
  result.damage_rects = plan.dirty_rects;
  result.damage_bounds = Rect{};
  for (const Rect dirty_rect : result.damage_rects) {
    result.damage_bounds = UnionRectBounds(result.damage_bounds, dirty_rect);
  }
  if (result.damage_rects.empty()) {
    result.damage_bounds = Rect{};
  }
  result.requires_full_redraw = plan.requires_full_redraw;
  if (plan.allows_scroll_translation_reuse) {
    result.diagnostics.push_back(
        "retained Blink presentation allows scroll translation reuse");
  }
  result.diagnostics.push_back(
      "Blink paint output routed through retained scene presentation plan");
}

class NoOpBlinkPageEmbedder final : public BlinkPageEmbedder {
 public:
  explicit NoOpBlinkPageEmbedder(BlinkPageEmbedderCreateInfo create_info)
      : create_info_(std::move(create_info)) {
    lifecycle_shim_ = CreateNoOpBlinkLifecycleShim();
    snapshot_ = InitialSnapshotFromRenderer(create_info_.renderer);

    BlinkRuntimeEnvironmentCreateInfo environment_info;
    environment_info.renderer = create_info_.renderer;
    environment_info.snapshot = snapshot_;
    const BlinkRuntimeEnvironment environment(std::move(environment_info));
    sanitized_document_ = environment.BuildDocumentForCommit();
    sanitized_stylesheets_ =
        environment.BuildStylesheetsForCommit();
    resource_references_ = environment.ExtractDeclaredResources();
    snapshot_.html = sanitized_document_.html;
    snapshot_.stylesheets.clear();
    snapshot_.stylesheets.reserve(sanitized_stylesheets_.size());
    for (const auto& stylesheet : sanitized_stylesheets_) {
      snapshot_.stylesheets.push_back(stylesheet.stylesheet);
    }
  }

  BlinkLifecycleReport Initialize() override {
    initialized_ = true;

    BlinkLifecycleInput input;
    input.renderer = create_info_.renderer;
    input.current_snapshot = snapshot_;
    BlinkLifecycleReport report = lifecycle_shim_->CreatePage(input);
    const BlinkLifecycleReport commit = lifecycle_shim_->CommitDocument(input);
    const BlinkLifecycleReport style = lifecycle_shim_->UpdateStyle(input);
    const BlinkLifecycleReport layout = lifecycle_shim_->Layout(input);

    report.frame_created = commit.frame_created;
    report.document_committed = commit.document_committed;
    report.style_updated = style.style_updated;
    report.layout_updated = layout.layout_updated;
    report.paint_artifact_collected = false;
    report.used_blink_runtime = false;
    report.diagnostics.insert(report.diagnostics.end(),
                              commit.diagnostics.begin(),
                              commit.diagnostics.end());
    report.diagnostics.insert(report.diagnostics.end(),
                              style.diagnostics.begin(),
                              style.diagnostics.end());
    report.diagnostics.insert(report.diagnostics.end(),
                              layout.diagnostics.begin(),
                              layout.diagnostics.end());

    report.diagnostics.push_back(
        create_info_.allow_transitional_v8_link
            ? "V8/cppgc internal runtime link allowed by v1 policy; "
              "JavaScript execution remains denied"
            : "V8/cppgc internal runtime link disabled by adapter policy");
    for (const auto& diagnostic : sanitized_document_.diagnostics) {
      report.diagnostics.push_back(diagnostic);
    }
    for (const auto& stylesheet : sanitized_stylesheets_) {
      for (const auto& diagnostic : stylesheet.diagnostics) {
        report.diagnostics.push_back(diagnostic);
      }
    }
    if (HasScriptCapableHtmlSurface(create_info_.renderer.html)) {
      report.diagnostics.push_back(
          "script-capable HTML surfaces will be stripped before Blink commit");
    }
    if (!create_info_.renderer.asset_provider) {
      report.diagnostics.push_back(
          "resource loads will report missing assets without AssetProvider");
    }
    if (!resource_references_.empty()) {
      report.diagnostics.push_back(
          "resource references will resolve through AssetProvider only");
    }
    report.diagnostics.push_back(
        "NoOpBlinkPageEmbedder is a buildable replacement recipe; Blink runtime "
        "wiring is intentionally not active yet");
    return report;
  }

  RenderResult AdvanceAndRender(const FrameInput& input) override {
    return Render(input, false);
  }

  RenderResult AdvanceAndRenderIncremental(
      const FrameInput& input) override {
    return Render(input, true);
  }

  RendererSnapshot Snapshot() const override { return snapshot_; }

 private:
  RenderResult Render(const FrameInput& input, bool incremental) {
    if (!initialized_) {
      Initialize();
    }

    const RendererSnapshot previous = snapshot_;
    BlinkLifecycleInput lifecycle_input;
    lifecycle_input.renderer = create_info_.renderer;
    lifecycle_input.current_snapshot = snapshot_;
    lifecycle_input.frame_input = input;

    const BlinkLifecycleReport layout =
        lifecycle_shim_->Layout(lifecycle_input);
    const BlinkLifecycleOutput paint =
        lifecycle_shim_->CollectPaint(lifecycle_input);
    PaintTranslator translator;
    const PaintTranslationResult translated =
        !paint.paint_artifact.chunks.empty()
            ? translator.TranslatePaintArtifact(paint.paint_artifact)
            : paint.paint_record_ops.empty()
                  ? translator.Translate(paint.paint_ops)
                  : translator.TranslatePaintRecord(paint.paint_record_ops);

    RenderResult result;
    result.hit_test_entries = paint.hit_test_entries;
    result.diagnostics = layout.diagnostics;
    result.diagnostics.insert(result.diagnostics.end(),
                              paint.diagnostics.begin(),
                              paint.diagnostics.end());
    result.diagnostics.insert(result.diagnostics.end(),
                              translated.diagnostics.begin(),
                              translated.diagnostics.end());
    result.missing_resources = paint.missing_resources;
    result.successor_snapshot = paint.next_snapshot;
    result.diagnostics.push_back(
        std::string("Blink paint artifact source: ") +
        PaintSourceName(paint.paint_source));
    if (paint.real_blink_paint_attempted && !paint.real_blink_paint_available) {
      result.diagnostics.push_back(
          "real Blink paint was attempted but not available; continuing "
          "through the single retained paint pipeline");
    }

    Rect retained_bounds = paint.damage_bounds.width > 0.0f &&
                                   paint.damage_bounds.height > 0.0f
                               ? paint.damage_bounds
                               : translated.damage_bounds;
    if (retained_bounds.width <= 0.0f || retained_bounds.height <= 0.0f) {
      retained_bounds = ViewportRect(result.successor_snapshot);
    }
    RetainedScene current_scene =
        !paint.paint_artifact.chunks.empty()
            ? MakeRetainedSceneFromPaintArtifact(paint.paint_artifact,
                                                 translator)
            : MakeSingleChunkScene("blink-document", retained_bounds,
                                   translated.draw_commands);
    if (current_scene.chunks.empty()) {
      current_scene = MakeSingleChunkScene("blink-document", retained_bounds,
                                           translated.draw_commands);
    }
    const Point previous_scroll_offset = DocumentScrollOffset(previous);
    const Point current_scroll_offset =
        DocumentScrollOffset(result.successor_snapshot);
    ApplyRetainedPresentationToResult(
        current_scene, incremental && previous_retained_scene_
                           ? &*previous_retained_scene_
                           : nullptr,
        current_scroll_offset, previous_scroll_offset, result);
    previous_retained_scene_ = std::move(current_scene);
    snapshot_ = result.successor_snapshot;

    result.diagnostics.push_back(
        "rendered through standalone Blink lifecycle shim");

    if (incremental) {
      if (result.requires_full_redraw) {
        result.diagnostics.push_back(
            "Blink adapter retained incremental render requires full redraw");
      } else if (result.damage_rects.empty() &&
                 (previous.focused_element_id !=
                      result.successor_snapshot.focused_element_id ||
                  previous.hovered_element_id !=
                      result.successor_snapshot.hovered_element_id ||
                  previous.active_element_id !=
                      result.successor_snapshot.active_element_id ||
                  !SameStringMap(previous.form_values_by_element_id,
                                 result.successor_snapshot
                                     .form_values_by_element_id))) {
        html_css_renderer::ApplyIncrementalDamage(
            previous, result,
            "Blink adapter retained state incremental render");
      } else if (result.damage_rects.empty()) {
        result.frame = RenderFrame{};
        result.frame.requires_full_redraw = false;
        result.diagnostics.push_back(
            "Blink adapter retained incremental render has no visual damage");
      } else {
        result.diagnostics.push_back(
            "Blink adapter retained incremental render used retained damage");
      }
    } else {
      MarkFullRedraw(result, result.damage_bounds);
    }
    return result;
  }

  BlinkPageEmbedderCreateInfo create_info_;
  std::unique_ptr<BlinkLifecycleShim> lifecycle_shim_;
  SanitizedDocument sanitized_document_;
  std::vector<SanitizedStylesheet> sanitized_stylesheets_;
  std::vector<ResourceReference> resource_references_;
  std::optional<RetainedScene> previous_retained_scene_;
  RendererSnapshot snapshot_;
  bool initialized_ = false;
};

}  // namespace

std::vector<BlinkBoundaryReplacement> RequiredBlinkBoundaryReplacements() {
  return {
      {"ChromeClient", "no-op standalone chrome client", true},
      {"LocalFrameClient", "no-op standalone local frame client", true},
      {"DocumentLoader", "in-memory HTML commit from RendererCreateInfo", true},
      {"URLLoader", "AssetProvider-only resource resolver", true},
      {"BrowserInterfaceBroker", "null broker with no Mojo surface", true},
      {"CodeCacheHost", "disabled code cache", true},
      {"ScriptController", "no script context creation or execution", true},
      {"V8/cppgc runtime",
       "transitional internal memory/runtime dependency only; no public script "
       "API or script execution",
       true},
      {"background execution startup", "blocked at feature policy boundary",
       true},
      {"Timer/microtask scheduling", "deterministic caller-provided timeline",
       true},
      {"GPU/compositor presentation",
       "PaintArtifact/cc paint translation to DrawCommandList", true},
      {"Navigation/form submission/preload",
       "diagnostic-only rejected side effect", true},
      {"Remote @import/fetch/XHR", "diagnostic-only missing resource", true},
  };
}

std::vector<BlinkRuntimeShim> RequiredBlinkRuntimeShims() {
  return {
      {"standalone page clients",
       {"ChromeClient", "LocalFrameClient", "Page::PageClients"},
       "own the minimal Page/Frame client surface with no browser process, UI "
       "chrome, accessibility tree, inspector, or navigation side effects",
       {"third_party/blink/renderer/core/testing/dummy_page_holder.cc",
        "third_party/blink/renderer/core/loader/empty_clients.h"},
       {"chrome/", "content/", "extensions/", "mojo/", "services/network/"},
       true,
       false},
      {"in-memory document commit",
       {"DocumentLoader", "WebNavigationParams", "PolicyContainer"},
       "commit caller-supplied sanitized HTML and stylesheets directly into a "
       "LocalFrame without navigation, history, preload, or form submission",
       {"third_party/blink/renderer/core/frame/local_frame.h",
        "third_party/blink/renderer/core/loader/document_loader.h"},
       {"content/", "net/", "services/network/", "mojo/"},
       true,
       false},
      {"asset-provider resource loading",
       {"URLLoaderFactory", "ResourceFetcher", "URLLoaderMockFactory"},
       "resolve url(...), images, SVG references, and font-face sources only "
       "through AssetProvider bytes and report deterministic missing resources",
       {"third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h",
        "third_party/blink/renderer/platform/testing/url_loader_mock_factory.h"},
       {"net/", "services/network/", "mojo/", "storage/"},
       true,
       false},
      {"disabled script environment",
       {"ScriptController", "LocalDOMWindow", "V8PerContextData",
        "worker execution"},
       "allow V8/cppgc only as internal Blink memory/runtime plumbing while "
       "preventing script context creation, inline event handlers, "
       "javascript: URLs, custom element execution, workers, timers, and "
       "microtasks",
       {"third_party/blink/renderer/bindings/core/v8/script_controller.h",
        "third_party/blink/renderer/core/frame/local_dom_window.h"},
       {"v8/src/builtins/", "v8/src/compiler/",
        "third_party/blink/renderer/modules/workers/",
        "third_party/blink/renderer/core/workers/"},
       true,
       false},
      {"null browser interface broker",
       {"BrowserInterfaceBrokerProxy", "CodeCacheHost", "Remote<...>"},
       "return null/denied interfaces for every Mojo-facing browser service "
       "and keep code cache, permissions, storage, and metrics unavailable",
       {"third_party/blink/renderer/platform/browser_interface_broker_proxy.h",
        "third_party/blink/renderer/platform/loader/fetch/code_cache_host.h"},
       {"mojo/", "services/", "components/", "content/"},
       true,
       false},
      {"deterministic lifecycle scheduler",
       {"FrameScheduler", "ThreadScheduler", "TaskRunner", "TickClock"},
       "advance lifecycle, animation sampling, timers allowed by CSS, and "
       "paint invalidation from FrameInput time only",
       {"third_party/blink/renderer/platform/scheduler/public/frame_scheduler.h",
        "base/time/tick_clock.h"},
       {"base/task/thread_pool/", "content/", "services/"},
       true,
       false},
      {"paint artifact exporter",
       {"PaintArtifact", "PaintController", "cc::PaintRecord"},
       "collect Blink paint chunks and convert paint ops into backend-neutral "
       "DrawCommandList plus damage and hit-test metadata",
       {"third_party/blink/renderer/platform/graphics/paint/paint_artifact.h",
        "cc/paint/paint_record.h"},
       {"gpu/", "services/viz/", "ui/compositor/", "components/viz/"},
       true,
       false},
  };
}

std::unique_ptr<BlinkPageEmbedder> CreateNoOpBlinkPageEmbedder(
    BlinkPageEmbedderCreateInfo create_info) {
  return std::make_unique<NoOpBlinkPageEmbedder>(std::move(create_info));
}

}  // namespace html_css_renderer
