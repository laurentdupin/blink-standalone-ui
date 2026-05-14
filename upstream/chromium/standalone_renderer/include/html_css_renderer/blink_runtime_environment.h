#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_RUNTIME_ENVIRONMENT_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_RUNTIME_ENVIRONMENT_H_

#include <string>
#include <vector>

#include "html_css_renderer/render_policy.h"
#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

struct BlinkRuntimeEnvironmentCreateInfo {
  RendererCreateInfo renderer;
  RendererSnapshot snapshot;
};

struct BlinkRuntimeDecision {
  bool allowed = false;
  std::string diagnostic;
};

struct BlinkFrameIslandStep {
  std::string name;
  std::string upstream_surface;
  std::string standalone_responsibility;
  bool required = true;
  bool implemented = false;
};

struct BlinkFrameIslandPlan {
  std::vector<BlinkFrameIslandStep> steps;
  std::vector<std::string> diagnostics;

  bool ReadyForRealPaintArtifact() const;
  int PendingRequiredStepCount() const;
};

class BlinkRuntimeEnvironment {
 public:
  explicit BlinkRuntimeEnvironment(BlinkRuntimeEnvironmentCreateInfo create_info);

  const RendererCreateInfo& Renderer() const;
  const RendererSnapshot& Snapshot() const;

  SanitizedDocument BuildDocumentForCommit() const;
  std::vector<SanitizedStylesheet> BuildStylesheetsForCommit() const;
  std::vector<ResourceReference> ExtractDeclaredResources() const;
  std::vector<ResourceResolution> ResolveDeclaredResources() const;
  FrameStateUpdate AdvanceFrameState(const FrameInput& input) const;

  BlinkRuntimeDecision CanUseInternalV8Runtime(
      const std::string& purpose) const;
  BlinkRuntimeDecision CanExecuteScriptSurface(
      const std::string& surface) const;
  BlinkRuntimeDecision CanProvideBrowserInterface(
      const std::string& interface_name) const;
  BlinkRuntimeDecision CanNavigateTo(
      const std::string& url_or_resource_id) const;

  BlinkFrameIslandPlan BuildFrameIslandPlan() const;

 private:
  RendererCreateInfo renderer_;
  RendererSnapshot snapshot_;
};

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_RUNTIME_ENVIRONMENT_H_
