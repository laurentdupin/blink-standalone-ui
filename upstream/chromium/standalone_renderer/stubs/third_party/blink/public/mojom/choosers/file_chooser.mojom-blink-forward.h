// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_FILE_CHOOSER_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_FILE_CHOOSER_MOJOM_BLINK_FORWARD_H_

#include "mojo/public/cpp/bindings/struct_ptr.h"

namespace blink::mojom::blink {

class FileChooserParams;
class NativeFileInfo;
class FileSystemFileInfo;
class FileChooserFileInfo;
class FileChooserResult;
class FileChooser;

using FileChooserParamsPtr = mojo::StructPtr<FileChooserParams>;
using NativeFileInfoPtr = mojo::StructPtr<NativeFileInfo>;
using FileSystemFileInfoPtr = mojo::StructPtr<FileSystemFileInfo>;
using FileChooserFileInfoPtr = mojo::StructPtr<FileChooserFileInfo>;
using FileChooserResultPtr = mojo::StructPtr<FileChooserResult>;

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CHOOSERS_FILE_CHOOSER_MOJOM_BLINK_FORWARD_H_
