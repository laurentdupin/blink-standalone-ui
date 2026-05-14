// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/html/forms/file_chooser.h"

namespace blink {

FileChooserClient::~FileChooserClient() = default;

void FileChooserClient::DisconnectFileChooser() {
  if (chooser_) {
    chooser_->DisconnectClient();
    chooser_ = nullptr;
  }
}

FileChooser* FileChooserClient::NewFileChooser(
    const mojom::blink::FileChooserParams& params) {
  chooser_ = FileChooser::Create(this, params);
  return chooser_.get();
}

FileChooser::FileChooser(FileChooserClient* client,
                         const mojom::blink::FileChooserParams&)
    : client_(client) {}

scoped_refptr<FileChooser> FileChooser::Create(
    FileChooserClient* client,
    const mojom::blink::FileChooserParams& params) {
  return base::AdoptRef(new FileChooser(client, params));
}

FileChooser::~FileChooser() = default;

bool FileChooser::OpenFileChooser(ChromeClientImpl&) {
  DidCloseChooser();
  return false;
}

void FileChooser::EnumerateChosenDirectory() {
  DidCloseChooser();
}

void FileChooser::DidChooseFiles(mojom::blink::FileChooserResultPtr) {
  DidCloseChooser();
}

void FileChooser::DidCloseChooser() {
  if (client_) {
    client_->DisconnectFileChooser();
  }
}

mojom::blink::FileChooserFileInfoPtr CreateFileChooserFileInfoNative(
    const String&,
    const String&,
    const Vector<String>&) {
  return nullptr;
}

mojom::blink::FileChooserFileInfoPtr CreateFileChooserFileInfoFileSystem(
    const KURL&,
    base::Time,
    int64_t) {
  return nullptr;
}

}  // namespace blink
