// Copyright 2024 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/image-decoders/png/png_image_decoder.h"

#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/skia/include/codec/SkPngDecoder.h"
#include "third_party/skia/include/core/SkStream.h"

namespace blink {

PngImageDecoder::~PngImageDecoder() = default;

String PngImageDecoder::FilenameExtension() const {
  return "png";
}

const AtomicString& PngImageDecoder::MimeType() const {
  DEFINE_STATIC_LOCAL(const AtomicString, png_mime_type, ("image/png"));
  return png_mime_type;
}

std::unique_ptr<SkCodec> PngImageDecoder::OnCreateSkCodec(
    std::unique_ptr<SkStream> stream,
    SkCodec::Result* result) {
  std::fprintf(stderr,
               "image_reachability.stage=png_image_decoder_before_sk_png_decode\n");
  std::fflush(stderr);
  std::unique_ptr<SkCodec> codec =
      SkPngDecoder::Decode(std::move(stream), result);
  std::fprintf(stderr,
               "image_reachability.stage=png_image_decoder_after_sk_png_decode codec=%d result=%d\n",
               codec ? 1 : 0, result ? static_cast<int>(*result) : -1);
  std::fflush(stderr);
  return codec;
}

}  // namespace blink
