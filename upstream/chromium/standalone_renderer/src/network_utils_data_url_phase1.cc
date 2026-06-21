// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Data URLs are local resource data and remain supported for image/CSS
// rendering. This file intentionally implements only ParseDataURL; external
// network helpers from network_utils.cc remain out of Phase 1.

#include "third_party/blink/renderer/platform/network/network_utils.h"

#include <string>
#include <string_view>
#include <tuple>

#include "base/base64.h"
#include "base/strings/escape.h"
#include "base/strings/string_util.h"
#include "net/base/net_errors.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_response.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/wtf/shared_buffer.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink::network_utils {
namespace {

std::string_view ConsumeToken(std::string_view* input) {
  const size_t semicolon = input->find(';');
  if (semicolon == std::string_view::npos) {
    std::string_view token = *input;
    *input = std::string_view();
    return token;
  }
  std::string_view token = input->substr(0, semicolon);
  *input = input->substr(semicolon + 1);
  return token;
}

}  // namespace

std::tuple<int, ResourceResponse, scoped_refptr<SharedBuffer>> ParseDataURL(
    const KURL& url,
    const String& method,
    ukm::SourceId,
    ukm::UkmRecorder*) {
  std::string mime_type = "text/plain";
  std::string charset = "US-ASCII";
  std::string data;

  const std::string url_string = url.GetString().Utf8();
  constexpr std::string_view kDataPrefix = "data:";
  if (!base::StartsWith(url_string, kDataPrefix,
                        base::CompareCase::INSENSITIVE_ASCII)) {
    return std::make_tuple(net::ERR_INVALID_URL, ResourceResponse(), nullptr);
  }
  const size_t comma = url_string.find(',', kDataPrefix.size());
  if (comma == std::string::npos) {
    return std::make_tuple(net::ERR_INVALID_URL, ResourceResponse(), nullptr);
  }

  std::string_view metadata(url_string.data() + kDataPrefix.size(),
                            comma - kDataPrefix.size());
  const std::string_view body(url_string.data() + comma + 1,
                              url_string.size() - comma - 1);

  bool is_base64 = false;
  bool first_token = true;
  while (!metadata.empty() || first_token) {
    std::string_view token = ConsumeToken(&metadata);
    if (first_token) {
      first_token = false;
      if (!token.empty()) {
        mime_type = base::ToLowerASCII(token);
        charset.clear();
      }
      continue;
    }
    if (base::EqualsCaseInsensitiveASCII(token, "base64")) {
      is_base64 = true;
      continue;
    }
    constexpr std::string_view kCharsetPrefix = "charset=";
    if (base::StartsWith(token, kCharsetPrefix,
                         base::CompareCase::INSENSITIVE_ASCII)) {
      charset = std::string(token.substr(kCharsetPrefix.size()));
    }
  }

  if (is_base64) {
    if (!base::Base64Decode(body, &data,
                            base::Base64DecodePolicy::kForgiving)) {
      return std::make_tuple(net::ERR_INVALID_URL, ResourceResponse(), nullptr);
    }
  } else {
    data = base::UnescapeBinaryURLComponent(body);
  }

  if (method == "HEAD") {
    data.clear();
  }

  auto buffer = SharedBuffer::Create(data);

  ResourceResponse response;
  response.SetHttpStatusCode(200);
  response.SetHttpStatusText(AtomicString("OK"));
  response.SetCurrentRequestUrl(url);
  response.SetMimeType(AtomicString(String::FromUtf8(mime_type)));
  response.SetExpectedContentLength(buffer->size());
  response.SetTextEncodingName(AtomicString(String::FromUtf8(charset)));

  return std::make_tuple(net::OK, std::move(response), std::move(buffer));
}

bool IsCertificateTransparencyRequiredError(int) {
  return false;
}

}  // namespace blink::network_utils
