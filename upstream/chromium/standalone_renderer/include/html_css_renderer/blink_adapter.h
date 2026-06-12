#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_ADAPTER_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_ADAPTER_H_

#include <memory>
#include <string>
#include <vector>

#include "html_css_renderer/paint_translator.h"
#include "html_css_renderer/renderer.h"

namespace html_css_renderer {

struct ChromiumSourcePath {
  std::string role;
  std::string relative_path;
  bool required = true;
  bool present = false;
  int file_count = 0;
};

struct ChromiumBuildEdge {
  std::string file;
  int line = 0;
  std::string token;
  std::string text;
};

struct BlinkSourceFile {
  std::string relative_path;
  std::string category;
  bool accepted = false;
  std::string reason;
};

struct BlinkSourceManifest {
  std::string chromium_root;
  std::vector<BlinkSourceFile> files;

  int AcceptedCount() const;
  int RejectedCount() const;
  std::vector<BlinkSourceFile> AcceptedFiles() const;
  std::vector<BlinkSourceFile> RejectedFiles() const;
};

struct BlinkBoundaryReplacement {
  std::string upstream_surface;
  std::string standalone_replacement;
  bool required_for_v1 = true;
};

struct BlinkRuntimeShim {
  std::string name;
  std::vector<std::string> upstream_surfaces;
  std::string standalone_responsibility;
  std::vector<std::string> source_seed_files;
  std::vector<std::string> forbidden_runtime_edges;
  bool required_for_live_runtime = true;
  bool implemented = false;
};

struct BlinkAdapterInventory {
  std::string chromium_root;
  std::vector<ChromiumSourcePath> source_paths;
  std::vector<ChromiumBuildEdge> blocked_edges;

  bool HasRequiredSources() const;
  bool HasBlockedBroadTargets() const;
  std::vector<std::string> MissingRequiredPaths() const;
};

struct BlinkRuntimeAdapterStatus {
  bool live_runtime_enabled = false;
  bool can_attempt_compile = false;
  std::vector<std::string> seed_files;
  std::vector<std::string> required_generated_files;
  std::vector<std::string> missing_generated_files;
  std::vector<BlinkBoundaryReplacement> required_replacements;
  std::vector<BlinkRuntimeShim> required_shims;
  std::vector<std::string> diagnostics;
};

BlinkAdapterInventory InspectChromiumCheckoutForBlinkAdapter(
    const std::string& chromium_root);
BlinkSourceManifest BuildBlinkSourceManifest(const std::string& chromium_root);
BlinkRuntimeAdapterStatus InspectBlinkRuntimeAdapterStatus(
    const std::string& chromium_root,
    bool live_runtime_enabled);

struct BlinkPageEmbedderCreateInfo {
  RendererCreateInfo renderer;
  std::string chromium_root;
  bool allow_transitional_v8_link = true;
  bool enable_paint_artifact_audit = false;
  bool trace_stages = false;
  bool debug_text_blob_replay = false;
  std::string lifecycle_stop;
};

struct BlinkLifecycleReport {
  bool page_created = false;
  bool frame_created = false;
  bool document_committed = false;
  bool style_updated = false;
  bool layout_updated = false;
  bool paint_artifact_collected = false;
  bool used_blink_runtime = false;
  std::vector<std::string> diagnostics;
  std::vector<BlinkBoundaryReplacement> replacements;
};

class BlinkPageEmbedder {
 public:
  virtual ~BlinkPageEmbedder() = default;

  virtual BlinkLifecycleReport Initialize() = 0;
  virtual RenderResult AdvanceAndRender(const FrameInput& input) = 0;
  virtual RenderResult AdvanceAndRenderIncremental(
      const FrameInput& input) = 0;
  virtual RendererSnapshot Snapshot() const = 0;
};

std::vector<BlinkBoundaryReplacement> RequiredBlinkBoundaryReplacements();
std::vector<BlinkRuntimeShim> RequiredBlinkRuntimeShims();
std::unique_ptr<BlinkPageEmbedder> CreateLiveBlinkPageEmbedder(
    BlinkPageEmbedderCreateInfo create_info);

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_BLINK_ADAPTER_H_
