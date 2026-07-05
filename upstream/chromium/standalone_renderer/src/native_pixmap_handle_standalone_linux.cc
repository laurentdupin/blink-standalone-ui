// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gfx/native_pixmap_handle.h"

#include <utility>

namespace gfx {

NativePixmapPlane::NativePixmapPlane() : stride(0), offset(0), size(0) {}

NativePixmapPlane::NativePixmapPlane(uint32_t stride,
                                     uint64_t offset,
                                     uint64_t size,
                                     base::ScopedFD fd)
    : stride(stride), offset(offset), size(size), fd(std::move(fd)) {}

NativePixmapPlane::NativePixmapPlane(NativePixmapPlane&& other) = default;
NativePixmapPlane::~NativePixmapPlane() = default;
NativePixmapPlane& NativePixmapPlane::operator=(NativePixmapPlane&& other) =
    default;

NativePixmapHandle::NativePixmapHandle() = default;
NativePixmapHandle::NativePixmapHandle(NativePixmapHandle&& other) = default;
NativePixmapHandle::~NativePixmapHandle() = default;
NativePixmapHandle& NativePixmapHandle::operator=(NativePixmapHandle&& other) =
    default;

NativePixmapHandle CloneHandleForIPC(const NativePixmapHandle&) {
  return NativePixmapHandle();
}

bool CanFitImageForSizeAndFormat(const gfx::NativePixmapHandle&,
                                 const gfx::Size&,
                                 viz::SharedImageFormat,
                                 bool,
                                 bool) {
  return false;
}

}  // namespace gfx
