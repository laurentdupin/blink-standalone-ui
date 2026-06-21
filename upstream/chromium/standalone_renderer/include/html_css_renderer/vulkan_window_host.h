#ifndef STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_VULKAN_WINDOW_HOST_H_
#define STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_VULKAN_WINDOW_HOST_H_

#include <memory>

#include "html_css_renderer/compositor_runtime.h"

namespace html_css_renderer {

class VulkanWindowHost {
 public:
  VulkanWindowHost();
  ~VulkanWindowHost();

  VulkanWindowHost(const VulkanWindowHost&) = delete;
  VulkanWindowHost& operator=(const VulkanWindowHost&) = delete;

  NativePresentationResult Initialize(const NativeWindowConfig& config);
  NativePresentationResult Present(const CompositorFrameResult& frame);

 private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace html_css_renderer

#endif  // STANDALONE_RENDERER_INCLUDE_HTML_CSS_RENDERER_VULKAN_WINDOW_HOST_H_
