// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gl/init/gl_initializer.h"

#include <EGL/egl.h>

extern "C" {
// The ANGLE internal eglGetProcAddress
__eglMustCastToProperFunctionPointerType EGLAPIENTRY
EGL_GetProcAddress(const char* procname);
}

namespace gl {
namespace init {

bool InitializeStaticANGLEEGL() {
  // Standalone static packages link ANGLE into the final executable instead of
  // shipping libEGL/libGLESv2 sidecars, so bind directly to ANGLE's in-process
  // EGL entry point.
  SetGLGetProcAddressProc(&EGL_GetProcAddress);
  return true;
}

}  // namespace init
}  // namespace gl
