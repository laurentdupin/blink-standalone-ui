// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "html_css_renderer/vulkan_window_host.h"

#include <memory>
#include <string>
#include <utility>

#include "build/build_config.h"

#if !BUILDFLAG(IS_WIN)

namespace html_css_renderer {
namespace {

NativePresentationResult UnsupportedResult(std::string operation) {
  NativePresentationResult result;
  result.failure_reason =
      "native Vulkan presentation is not part of the standalone Linux C API "
      "static package";
  result.diagnostics.push_back(std::move(operation) + " unsupported: " +
                               result.failure_reason);
  return result;
}

}  // namespace

class VulkanWindowHost::Impl {
 public:
  NativePresentationResult Initialize(const NativeWindowConfig&) {
    return UnsupportedResult("initialize");
  }

  NativePresentationResult Present(const CompositorFrameResult&) {
    return UnsupportedResult("present");
  }
};

VulkanWindowHost::VulkanWindowHost() : impl_(std::make_unique<Impl>()) {}

VulkanWindowHost::~VulkanWindowHost() = default;

NativePresentationResult VulkanWindowHost::Initialize(
    const NativeWindowConfig& config) {
  return impl_->Initialize(config);
}

NativePresentationResult VulkanWindowHost::Present(
    const CompositorFrameResult& frame) {
  return impl_->Present(frame);
}

}  // namespace html_css_renderer

#endif  // !BUILDFLAG(IS_WIN)
