#include "html_css_renderer/blink_runtime_environment.h"

#include <utility>

namespace html_css_renderer {

bool BlinkFrameIslandPlan::ReadyForRealPaintArtifact() const {
  return PendingRequiredStepCount() == 0;
}

int BlinkFrameIslandPlan::PendingRequiredStepCount() const {
  int pending = 0;
  for (const BlinkFrameIslandStep& step : steps) {
    if (step.required && !step.implemented) {
      ++pending;
    }
  }
  return pending;
}

BlinkRuntimeEnvironment::BlinkRuntimeEnvironment(
    BlinkRuntimeEnvironmentCreateInfo create_info)
    : renderer_(std::move(create_info.renderer)),
      snapshot_(std::move(create_info.snapshot)) {}

const RendererCreateInfo& BlinkRuntimeEnvironment::Renderer() const {
  return renderer_;
}

const RendererSnapshot& BlinkRuntimeEnvironment::Snapshot() const {
  return snapshot_;
}

SanitizedDocument BlinkRuntimeEnvironment::BuildDocumentForCommit() const {
  return SanitizeHtmlForRendering(renderer_.html);
}

std::vector<SanitizedStylesheet>
BlinkRuntimeEnvironment::BuildStylesheetsForCommit() const {
  return SanitizeStylesheetsForRendering(renderer_.stylesheets);
}

std::vector<ResourceReference>
BlinkRuntimeEnvironment::ExtractDeclaredResources() const {
  const SanitizedDocument document = BuildDocumentForCommit();
  std::vector<SanitizedStylesheet> sanitized = BuildStylesheetsForCommit();
  std::vector<Stylesheet> stylesheets;
  stylesheets.reserve(sanitized.size());
  for (const SanitizedStylesheet& stylesheet : sanitized) {
    stylesheets.push_back(stylesheet.stylesheet);
  }
  return ExtractResourceReferences(document.html, stylesheets);
}

std::vector<ResourceResolution>
BlinkRuntimeEnvironment::ResolveDeclaredResources() const {
  return ResolveResourceReferences(ExtractDeclaredResources(),
                                   renderer_.asset_provider);
}

FrameStateUpdate BlinkRuntimeEnvironment::AdvanceFrameState(
    const FrameInput& input) const {
  return BuildFrameStateUpdate(snapshot_, input);
}

BlinkRuntimeDecision BlinkRuntimeEnvironment::CanUseInternalV8Runtime(
    const std::string& purpose) const {
  BlinkRuntimeDecision decision;
  decision.allowed = true;
  decision.diagnostic =
      "allowed internal V8/cppgc runtime for Blink " + purpose +
      "; JavaScript execution surfaces remain denied";
  return decision;
}

BlinkRuntimeDecision BlinkRuntimeEnvironment::CanExecuteScriptSurface(
    const std::string& surface) const {
  BlinkRuntimeDecision decision;
  decision.allowed = false;
  decision.diagnostic =
      "blocked script-capable Blink surface: " + surface;
  return decision;
}

BlinkRuntimeDecision BlinkRuntimeEnvironment::CanProvideBrowserInterface(
    const std::string& interface_name) const {
  BlinkRuntimeDecision decision;
  decision.allowed = false;
  decision.diagnostic =
      "denied browser interface request: " + interface_name;
  return decision;
}

BlinkRuntimeDecision BlinkRuntimeEnvironment::CanNavigateTo(
    const std::string& url_or_resource_id) const {
  BlinkRuntimeDecision decision;
  decision.allowed = false;
  if (IsPermittedResourceReference(url_or_resource_id)) {
    decision.diagnostic =
        "blocked navigation side effect for local resource token: " +
        url_or_resource_id;
  } else {
    decision.diagnostic =
        "blocked navigation side effect for external target: " +
        url_or_resource_id;
  }
  return decision;
}

BlinkFrameIslandPlan BlinkRuntimeEnvironment::BuildFrameIslandPlan() const {
  BlinkFrameIslandPlan plan;
  plan.steps = {
      {"internal cppgc/V8 runtime",
       "ThreadState / cppgc heap used by Blink Oilpan objects",
       "allow internal runtime only for Blink memory and lifecycle invariants",
       true,
       CanUseInternalV8Runtime("frame island").allowed},
      {"standalone page clients",
       "DummyPageHolder Page/ChromeClient/LocalFrameClient shape",
       "own null clients without browser process services",
       true,
       false},
      {"live frame bridge recipe",
       "standalone_live_frame_bridge_probe.cc using DummyPageHolder, "
       "Document body mutation, LocalFrameView lifecycle, and GetPaintArtifact",
       "keep the real Blink document/style/layout/paint path explicit while "
       "runtime shims are filled in",
       true,
       true},
      {"in-memory document commit",
       "PageTestBase::SetBodyInnerHTML / Document mutation path",
       "commit sanitized caller HTML/CSS with scripts and network side effects "
       "removed",
       true,
       false},
      {"asset provider resource loading",
       "ResourceFetcher / URLLoaderFactory",
       "resolve images, CSS URLs, SVG references, and fonts only from "
       "AssetProvider bytes",
       true,
       false},
      {"disabled script surface",
       "ScriptController / LocalDOMWindow script context",
       "prevent script contexts, inline handlers, javascript URLs, workers, "
       "timers, and microtasks",
       true,
       false},
      {"deterministic lifecycle clock",
       "FrameScheduler / animation clock",
       "advance lifecycle and CSS animation sampling from FrameInput time",
       true,
       false},
      {"local frame view lifecycle",
       "LocalFrameView::UpdateAllLifecyclePhasesForTest",
       "drive style, layout, pre-paint, and paint until PaintClean",
       true,
       false},
      {"real paint artifact export",
       "LocalFrameView::GetPaintArtifact",
       "read Blink-owned PaintArtifact after DocumentLifecycle::kPaintClean",
       true,
       false},
      {"paint artifact translation",
       "PaintArtifact::GetPaintChunks / GetDisplayItemList / GetPaintRecord",
       "translate chunks and display items into retained backend-neutral draw "
       "commands",
       true,
       false},
  };

  plan.diagnostics.push_back(
      "Blink frame island target: sanitized HTML/CSS -> LocalFrameView "
      "lifecycle -> PaintClean -> LocalFrameView::GetPaintArtifact");
  plan.diagnostics.push_back(
      CanUseInternalV8Runtime("frame island").diagnostic);
  plan.diagnostics.push_back(
      CanExecuteScriptSurface("LocalDOMWindow script context").diagnostic);
  plan.diagnostics.push_back(
      CanProvideBrowserInterface("BrowserInterfaceBroker").diagnostic);
  plan.diagnostics.push_back(
      "current frame island is not ready for real PaintArtifact export until "
      "standalone page clients, document commit, resource loading, scheduler, "
      "and LocalFrameView lifecycle are wired");
  return plan;
}

}  // namespace html_css_renderer
