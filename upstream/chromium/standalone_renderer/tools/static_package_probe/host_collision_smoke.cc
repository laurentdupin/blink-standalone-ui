// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <cstddef>

struct png_struct_def;
using png_const_charp = const char*;
using png_voidp = void*;
using png_error_ptr = void (*)(png_struct_def*, const char*);

extern "C" void* png_create_write_struct(png_const_charp,
                                          png_voidp,
                                          png_error_ptr,
                                          png_error_ptr) {
  return nullptr;
}

extern "C" const char* uprv_getDefaultCodepage() {
  return "UTF-8";
}

extern "C" int vmaCreateAllocator(const void*, void**) {
  return 0;
}

extern "C" void vmaDestroyAllocator(void*) {}

class VmaJsonWriter {
 public:
  VmaJsonWriter();
  ~VmaJsonWriter();
};

VmaJsonWriter::VmaJsonWriter() = default;
VmaJsonWriter::~VmaJsonWriter() = default;

int main() {
  return 0;
}
