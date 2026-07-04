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

#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "media/base/mime_util.h"
#include "media/filters/stream_parser_factory.h"
#include "net/base/mime_util.h"

namespace blink {

namespace {

bool MatchesStaticMime(std::string_view mime_type,
                       std::string_view expected_mime_type) {
  return base::EqualsCaseInsensitiveASCII(mime_type, expected_mime_type);
}

bool IsStaticImageMime(std::string_view mime_type) {
  return MatchesStaticMime(mime_type, "image/png") ||
         MatchesStaticMime(mime_type, "image/apng") ||
         MatchesStaticMime(mime_type, "image/jpeg") ||
         MatchesStaticMime(mime_type, "image/jpg") ||
         MatchesStaticMime(mime_type, "image/pjpeg") ||
         MatchesStaticMime(mime_type, "image/gif") ||
         MatchesStaticMime(mime_type, "image/webp") ||
         MatchesStaticMime(mime_type, "image/bmp") ||
         MatchesStaticMime(mime_type, "image/x-icon") ||
         MatchesStaticMime(mime_type, "image/vnd.microsoft.icon") ||
         MatchesStaticMime(mime_type, "image/x-png") ||
         MatchesStaticMime(mime_type, "image/svg+xml");
}

}  // namespace

bool IsSupportedImageMimeType(std::string_view mime_type) {
  return IsStaticImageMime(mime_type);
}

bool IsSupportedNonImageMimeType(std::string_view mime_type) {
  return MatchesStaticMime(mime_type, "text/css") ||
         MatchesStaticMime(mime_type, "text/plain") ||
         MatchesStaticMime(mime_type, "text/html") ||
         MatchesStaticMime(mime_type, "application/xml") ||
         MatchesStaticMime(mime_type, "text/xml") ||
         MatchesStaticMime(mime_type, "application/xhtml+xml") ||
         MatchesStaticMime(mime_type, "application/json");
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
  *codecs_out = base::SplitString(codecs, ",", base::TRIM_WHITESPACE,
                                  base::SPLIT_WANT_NONEMPTY);
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
