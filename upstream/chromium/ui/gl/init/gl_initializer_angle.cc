// Copyright 2020 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gl/init/gl_initializer.h"

#include <EGL/egl.h>

#if !defined(HTML_CSS_RENDERER_STANDALONE)
extern "C" {
// The ANGLE internal eglGetProcAddress
EGLAPI __eglMustCastToProperFunctionPointerType EGLAPIENTRY
EGL_GetProcAddress(const char* procname);
}
#endif

namespace gl {
namespace init {

bool InitializeStaticANGLEEGL() {
#if defined(HTML_CSS_RENDERER_STANDALONE)
  return false;
#else
  SetGLGetProcAddressProc(&EGL_GetProcAddress);
  return true;
#endif
}

}  // namespace init
}  // namespace gl
