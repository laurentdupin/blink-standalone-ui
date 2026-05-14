// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "perfetto/tracing/traced_value.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace network::mojom {
enum class CorsDomainMatchMode;
enum class CorsOriginAccessMatchPriority;
}  // namespace network::mojom

namespace network::cors {
class OriginAccessEntry {
 public:
  enum class MatchResult {
    kDoesNotMatchOrigin,
    kMatchesOrigin,
    kMatchesOriginButIsPublicSuffix,
  };
};
}  // namespace network::cors

namespace blink {

class SecurityOrigin;
class OriginAccessEntry {
 public:
  OriginAccessEntry(const SecurityOrigin&,
                    network::mojom::CorsDomainMatchMode,
                    network::mojom::CorsOriginAccessMatchPriority);
  network::cors::OriginAccessEntry::MatchResult MatchesOrigin(
      const SecurityOrigin&) const;
};

OriginAccessEntry::OriginAccessEntry(
    const SecurityOrigin&,
    network::mojom::CorsDomainMatchMode,
    network::mojom::CorsOriginAccessMatchPriority) {}

network::cors::OriginAccessEntry::MatchResult
OriginAccessEntry::MatchesOrigin(const SecurityOrigin&) const {
  return network::cors::OriginAccessEntry::MatchResult::kDoesNotMatchOrigin;
}

}  // namespace blink
