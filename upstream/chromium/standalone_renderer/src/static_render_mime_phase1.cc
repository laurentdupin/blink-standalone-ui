// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Static-render MIME support for Phase 1. This intentionally excludes
// video/audio/media MIME types while keeping images, SVG, CSS, and text/html
// surfaces needed by the standalone renderer.

#include "third_party/blink/public/common/mime_util/mime_util.h"

#include <string>
#include <string_view>
#include <vector>

#include "base/containers/fixed_flat_set.h"
#include "base/strings/string_split.h"
#include "base/strings/string_util.h"
#include "media/base/mime_util.h"
#include "media/filters/stream_parser_factory.h"
#include "net/base/mime_util.h"

namespace blink {

namespace {

// Mirrors Chromium's MIME registry shape while keeping the standalone
// renderer's no-script/no-media policy for Phase 1.
constexpr auto kStandaloneSupportedImageTypes =
    base::MakeFixedFlatSet<std::string_view>({
        "image/jpeg", "image/pjpeg", "image/jpg",
        "image/webp", "image/png",   "image/apng",
        "image/gif",  "image/bmp",   "image/vnd.microsoft.icon",
        "image/x-icon", "image/x-xbitmap", "image/x-png",
        "image/svg+xml",
    });

constexpr auto kStandaloneSupportedNonImageTypes =
    base::MakeFixedFlatSet<std::string_view>({
        "text/css",
        "text/plain",
        "text/html",
        "application/xml",
        "text/xml",
        "application/xhtml+xml",
        "application/json",
    });

constexpr auto kStandaloneUnsupportedTextTypes =
    base::MakeFixedFlatSet<std::string_view>({
        "text/calendar",
        "text/x-calendar",
        "text/x-vcalendar",
        "text/vcalendar",
        "text/vcard",
        "text/x-vcard",
        "text/directory",
        "text/ldif",
        "text/qif",
        "text/x-qif",
        "text/x-csv",
        "text/x-vcf",
        "text/rtf",
        "text/comma-separated-values",
        "text/csv",
        "text/tab-separated-values",
        "text/tsv",
        "text/ofx",
        "text/vnd.sun.j2me.app-descriptor",
        "text/x-ms-iqy",
        "text/x-ms-odc",
        "text/x-ms-rqy",
        "text/x-ms-contact",
    });

}  // namespace

bool IsSupportedImageMimeType(std::string_view mime_type) {
  return kStandaloneSupportedImageTypes.contains(base::ToLowerASCII(mime_type));
}

bool IsSupportedNonImageMimeType(std::string_view mime_type) {
  return kStandaloneSupportedNonImageTypes.contains(
      base::ToLowerASCII(mime_type));
}

bool IsUnsupportedTextMimeType(std::string_view mime_type) {
  return kStandaloneUnsupportedTextTypes.contains(base::ToLowerASCII(mime_type));
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

bool IsXMLMimeType(std::string_view mime_type) {
  return net::MatchesMimeType("text/xml", mime_type) ||
         net::MatchesMimeType("application/xml", mime_type) ||
         net::MatchesMimeType("application/*+xml", mime_type);
}

bool IsSVGMimeType(std::string_view mime_type) {
  return net::MatchesMimeType("image/svg+xml", mime_type);
}

bool IsSupportedMimeType(std::string_view mime_type) {
  return (base::StartsWith(mime_type, "image/",
                           base::CompareCase::INSENSITIVE_ASCII) &&
          IsSupportedImageMimeType(mime_type)) ||
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
