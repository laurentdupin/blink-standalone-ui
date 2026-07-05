// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gl/init/gl_factory.h"

#include "base/memory/scoped_refptr.h"
#include "ui/gl/gl_context_stub.h"
#include "ui/gl/gl_context.h"
#include "ui/gl/gl_display.h"
#include "ui/gl/gl_gl_api_implementation.h"
#include "ui/gl/gl_implementation.h"
#include "ui/gl/gl_surface_stub.h"
#include "ui/gl/gl_surface.h"
#include "ui/gl/init/gl_initializer.h"
#include "ui/gfx/color_space.h"

namespace gl::init {
namespace {

class StandaloneGLDisplay final : public GLDisplay {
 public:
  StandaloneGLDisplay()
      : GLDisplay(/*system_device_id=*/0, DisplayKey::kDefault, NONE) {}
  ~StandaloneGLDisplay() override = default;

  void* GetDisplay() const override { return nullptr; }
  void Shutdown() override {}
  bool IsInitialized() const override { return true; }
  bool Initialize(GLDisplay*) override { return true; }
};

StandaloneGLDisplay* GetStandaloneGLDisplay() {
  static StandaloneGLDisplay* display = new StandaloneGLDisplay();
  return display;
}

scoped_refptr<GLSurface> InitializeStandaloneSurface(GLSurfaceStub* surface,
                                                     const gfx::Size& size) {
  scoped_refptr<GLSurface> scoped_surface(surface);
  surface->Resize(size, /*scale_factor=*/1.0f, gfx::ColorSpace(),
                  /*has_alpha=*/true);
  return scoped_surface;
}

}  // namespace

std::vector<GLImplementationParts> GetAllowedGLImplementations() {
  return {GLImplementationParts(kGLImplementationStubGL),
          GLImplementationParts(kGLImplementationDisabled)};
}

GLDisplay* InitializeGLOneOffPlatform(gl::GpuPreference) {
  return GetStandaloneGLDisplay();
}

bool InitializeStaticGLBindings(GLImplementationParts implementation) {
  SetGLImplementationParts(implementation);
  InitializeStaticGLBindingsGL();
  return true;
}

bool InitializeExtensionSettingsOneOffPlatform(GLDisplay*) {
  return true;
}

void ShutdownGLPlatform(GLDisplay*) {
  ClearBindingsGL();
}

bool GetGLWindowSystemBindingInfo(const GLVersionInfo&,
                                  GLWindowSystemBindingInfo*) {
  return false;
}

scoped_refptr<GLContext> CreateGLContext(GLShareGroup*,
                                         GLSurface* compatible_surface,
                                         const GLContextAttribs& attribs) {
  if (GetGLImplementation() != kGLImplementationStubGL) {
    return nullptr;
  }
  auto context = base::MakeRefCounted<GLContextStub>();
  context->SetUseStubApi(true);
  context->Initialize(compatible_surface, attribs);
  return context;
}

scoped_refptr<GLSurface> CreateViewGLSurface(GLDisplay*,
                                             gfx::AcceleratedWidget) {
  return nullptr;
}

scoped_refptr<GLSurface> CreateOffscreenGLSurface(GLDisplay*,
                                                  const gfx::Size& size) {
  if (GetGLImplementation() != kGLImplementationStubGL) {
    return nullptr;
  }
  return InitializeStandaloneSurface(new GLSurfaceStub(), size);
}

}  // namespace gl::init
