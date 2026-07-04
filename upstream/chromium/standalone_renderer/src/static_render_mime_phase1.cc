// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Static-render MIME support for Phase 1. This intentionally excludes
// video/audio/media MIME types while keeping images, SVG, CSS, and text/html
// surfaces needed by the standalone renderer.

#include "third_party/blink/public/common/mime_util/mime_util.h"

#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "base/strings/string_util.h"
#include "media/base/mime_util.h"
#include "media/filters/stream_parser_factory.h"
#include "net/base/mime_util.h"

namespace blink {

namespace {

std::string NormalizeMime(std::string_view mime_type) {
  return base::ToLowerASCII(mime_type);
}

bool IsStaticImageMime(std::string_view mime_type) {
  const std::string mime = NormalizeMime(mime_type);
  return mime == "image/png" || mime == "image/apng" ||
         mime == "image/jpeg" || mime == "image/jpg" ||
         mime == "image/pjpeg" || mime == "image/gif" ||
         mime == "image/webp" || mime == "image/bmp" ||
         mime == "image/x-icon" || mime == "image/vnd.microsoft.icon" ||
         mime == "image/x-png" || mime == "image/svg+xml";
}

}  // namespace

bool IsSupportedImageMimeType(std::string_view mime_type) {
  return IsStaticImageMime(mime_type);
}

bool IsSupportedNonImageMimeType(std::string_view mime_type) {
  const std::string mime = NormalizeMime(mime_type);
  return mime == "text/css" || mime == "text/plain" ||
         mime == "text/html" || mime == "application/xml" ||
         mime == "text/xml" || mime == "application/xhtml+xml" ||
         mime == "application/json";
}

bool IsSupportedJavascriptMimeType(std::string_view) {
  return false;
}

bool IsWasmMIMEType(std::string_view) {
  return false;
}

bool IsJSONMimeType(std::string_view mime_type) {
  return net::MatchesMimeType("application/json", mime_type) ||
         net::MatchesMimeType("text/json", mime_type) ||
         net::MatchesMimeType(
             "*+json", mime_type,
             net::MimeTypeValidationLevel::kWildcardSlashAndTokens);
}

bool IsSupportedMimeType(std::string_view mime_type) {
  return IsSupportedImageMimeType(mime_type) ||
         IsSupportedNonImageMimeType(mime_type);
}

}  // namespace blink

namespace media {

void SplitCodecs(std::string_view codecs,
                 std::vector<std::string>* codecs_out) {
  if (!codecs_out) {
    return;
  }
  codecs_out->clear();
  size_t start = 0;
  while (start <= codecs.size()) {
    size_t comma = codecs.find(',', start);
    std::string codec(codecs.substr(
        start, comma == std::string_view::npos ? std::string_view::npos
                                               : comma - start));
    base::TrimWhitespaceASCII(codec, base::TRIM_ALL, &codec);
    if (!codec.empty()) {
      codecs_out->push_back(std::move(codec));
    }
    if (comma == std::string_view::npos) {
      break;
    }
    start = comma + 1;
  }
}

SupportsType IsSupportedMediaFormat(std::string_view,
                                    const std::vector<std::string>&) {
  return SupportsType::kNotSupported;
}

SupportsType StreamParserFactory::IsTypeSupported(
    std::string_view,
    base::span<const std::string>) {
  return SupportsType::kNotSupported;
}

}  // namespace media
