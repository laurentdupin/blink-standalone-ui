// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// DataURL::BuildResponse is not used by the Phase 1 Blink data: wrapper, but
// net/base/data_url.cc contains the symbol reference. Keep the HTTP-header
// factory inert instead of importing the broader net/http response-header owner.

#include "net/http/http_response_headers.h"
#include "net/base/features.h"

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
    std::string_view) {
  return nullptr;
}

}  // namespace net
