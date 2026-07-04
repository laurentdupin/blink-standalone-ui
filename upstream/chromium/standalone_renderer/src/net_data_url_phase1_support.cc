// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Keep the data: URL response-header factory local to the standalone build
// while using Chromium's DataURL::BuildResponse parsing path.

#include "net/http/http_response_headers.h"
#include "net/base/features.h"
#include "net/http/http_version.h"

namespace net::features {

BASE_FEATURE(kSimdutfBase64Support,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kFurtherOptimizeParsingDataUrls,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kDataUrlMimeTypeParameterPreservation,
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace net::features

namespace net {

scoped_refptr<HttpResponseHeaders> HttpResponseHeaders::TryToCreateForDataURL(
    std::string_view content_type) {
  return HttpResponseHeaders::Builder(HttpVersion(1, 1), "200 OK")
      .AddHeader("Content-Type", content_type)
      .Build();
}

}  // namespace net
