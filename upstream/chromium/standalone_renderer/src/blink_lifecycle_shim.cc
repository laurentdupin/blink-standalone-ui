#include "html_css_renderer/blink_adapter.h"

#include <memory>
#include <utility>

#include "html_css_renderer/blink_runtime_environment.h"
#include "html_css_renderer/render_policy.h"
#include "standalone_frame.h"

namespace html_css_renderer {
namespace {

class NoOpBlinkLifecycleShim final : public BlinkLifecycleShim {
 public:
  BlinkLifecycleReport CreatePage(const BlinkLifecycleInput& input) override {
    return EnsureFrame(input).CreatePage();
  }

  BlinkLifecycleReport CommitDocument(
      const BlinkLifecycleInput& input) override {
    return EnsureFrame(input).CommitDocument();
  }

  BlinkLifecycleReport UpdateStyle(const BlinkLifecycleInput& input) override {
    return EnsureFrame(input).UpdateStyle();
  }

  BlinkLifecycleReport Layout(const BlinkLifecycleInput& input) override {
    return EnsureFrame(input).Layout(input.frame_input);
  }

  BlinkLifecycleOutput CollectPaint(
      const BlinkLifecycleInput& input) override {
    return EnsureFrame(input).CollectPaint(input.frame_input);
  }

 private:
  StandaloneFrame& EnsureFrame(const BlinkLifecycleInput& input) {
    if (!frame_) {
      BlinkPageEmbedderCreateInfo create_info;
      create_info.renderer = input.renderer;
      frame_ = std::make_unique<StandaloneFrame>(std::move(create_info));
    }
    return *frame_;
  }

  std::unique_ptr<StandaloneFrame> frame_;
};

}  // namespace

std::unique_ptr<BlinkLifecycleShim> CreateNoOpBlinkLifecycleShim() {
  return std::make_unique<NoOpBlinkLifecycleShim>();
}

}  // namespace html_css_renderer
