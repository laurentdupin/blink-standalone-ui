// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Keep the data: URL feature flags local to the standalone build while using
// Chromium's DataURL and HttpResponseHeaders implementations.

#include "net/base/features.h"

namespace net::features {

BASE_FEATURE(kSimdutfBase64Support,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kFurtherOptimizeParsingDataUrls,
             base::FEATURE_DISABLED_BY_DEFAULT);

BASE_FEATURE(kDataUrlMimeTypeParameterPreservation,
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace net::features
