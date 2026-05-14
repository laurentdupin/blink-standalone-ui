#ifndef STANDALONE_RENDERER_SRC_STANDALONE_FRAME_H_
#define STANDALONE_RENDERER_SRC_STANDALONE_FRAME_H_

#include <string>
#include <vector>

#include "html_css_renderer/blink_adapter.h"
#include "html_css_renderer/blink_runtime_environment.h"

namespace html_css_renderer {

enum class StandaloneFrameSurface {
  kStandaloneOwned,
  kBlinkOwned,
  kDenied,
};

struct StandaloneFrameBoundary {
  std::string name;
  StandaloneFrameSurface surface = StandaloneFrameSurface::kStandaloneOwned;
  std::string responsibility;
};

struct StandaloneFrameState {
  bool page_created = false;
  bool frame_created = false;
  bool document_committed = false;
  bool style_updated = false;
  bool layout_updated = false;
  RendererSnapshot snapshot;
  std::vector<std::string> diagnostics;
};

class StandaloneFrame {
 public:
  explicit StandaloneFrame(BlinkPageEmbedderCreateInfo create_info);

  const RendererCreateInfo& Renderer() const;
  const RendererSnapshot& Snapshot() const;
  const std::vector<StandaloneFrameBoundary>& Boundaries() const;

  BlinkLifecycleReport CreatePage();
  BlinkLifecycleReport CommitDocument();
  BlinkLifecycleReport UpdateStyle();
  BlinkLifecycleReport Layout(const FrameInput& input);
  BlinkLifecycleOutput CollectPaint(const FrameInput& input);

 private:
  BlinkRuntimeEnvironment EnvironmentForCurrentSnapshot() const;
  void AppendBoundaryDiagnostics(BlinkLifecycleReport& report) const;
  void AppendPolicyDiagnostics(BlinkLifecycleReport& report) const;

  BlinkPageEmbedderCreateInfo create_info_;
  StandaloneFrameState state_;
  std::vector<StandaloneFrameBoundary> boundaries_;
};

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_SRC_STANDALONE_FRAME_H_
