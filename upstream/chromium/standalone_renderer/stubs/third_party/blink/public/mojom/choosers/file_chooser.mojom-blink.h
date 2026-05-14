// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_FILE_CHOOSER_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_FILE_CHOOSER_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/choosers/file_chooser.mojom-blink-forward.h"

namespace blink::mojom::blink {

class FileChooserParams {
 public:
  FileChooserParams() = default;
};

class NativeFileInfo {
 public:
  NativeFileInfo() = default;
};

class FileSystemFileInfo {
 public:
  FileSystemFileInfo() = default;
};

class FileChooserFileInfo {
 public:
  FileChooserFileInfo() = default;
};

class FileChooserResult {
 public:
  FileChooserResult() = default;
};

class FileChooser {
 public:
  class Proxy_ {};
  virtual ~FileChooser() = default;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_FILE_CHOOSER_MOJOM_BLINK_H_
