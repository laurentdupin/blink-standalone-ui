// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Data URLs are local resource data and remain supported for image/CSS
// rendering. This file intentionally implements only ParseDataURL; external
// network helpers from network_utils.cc remain out of Phase 1.

#include "third_party/blink/renderer/platform/network/network_utils.h"

#include <string>
#include <tuple>

#include "net/base/data_url.h"
#include "net/base/net_errors.h"
#include "net/http/http_response_headers.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_response.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/wtf/shared_buffer.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "url/gurl.h"

namespace blink::network_utils {

std::tuple<int, ResourceResponse, scoped_refptr<SharedBuffer>> ParseDataURL(
    const KURL& url,
    const String& method,
    ukm::SourceId,
    ukm::UkmRecorder*) {
  std::string mime_type;
  std::string charset;
  std::string data;
  scoped_refptr<net::HttpResponseHeaders> headers;

  net::Error result =
      net::DataURL::BuildResponse(GURL(url), method.Ascii(), &mime_type,
                                  &charset, &data, &headers);
  if (result != net::OK)
    return std::make_tuple(result, ResourceResponse(), nullptr);

  auto buffer = SharedBuffer::Create(data);

  ResourceResponse response;
  response.SetHttpStatusCode(200);
  response.SetHttpStatusText(AtomicString("OK"));
  response.SetCurrentRequestUrl(url);
  response.SetMimeType(AtomicString(String::FromUtf8(mime_type)));
  response.SetExpectedContentLength(buffer->size());
  response.SetTextEncodingName(AtomicString(String::FromUtf8(charset)));
  size_t iter = 0;
  std::string name;
  std::string value;
  while (headers && headers->EnumerateHeaderLines(&iter, &name, &value)) {
    response.AddHttpHeaderField(AtomicString(base::as_byte_span(name)),
                                AtomicString(base::as_byte_span(value)));
  }

  return std::make_tuple(net::OK, std::move(response), std::move(buffer));
}

bool IsCertificateTransparencyRequiredError(int error_code) {
  return error_code == net::ERR_CERTIFICATE_TRANSPARENCY_REQUIRED;
}

}  // namespace blink::network_utils
