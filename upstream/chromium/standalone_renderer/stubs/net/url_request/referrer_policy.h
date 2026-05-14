// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_NET_URL_REQUEST_REFERRER_POLICY_H_
#define STANDALONE_RENDERER_STUBS_NET_URL_REQUEST_REFERRER_POLICY_H_

#include <optional>
#include <string_view>

namespace net {

enum class ReferrerPolicy {
  CLEAR_ON_TRANSITION_FROM_SECURE_TO_INSECURE = 0,
  REDUCE_GRANULARITY_ON_TRANSITION_CROSS_ORIGIN = 1,
  ORIGIN_ONLY_ON_TRANSITION_CROSS_ORIGIN = 2,
  NEVER_CLEAR = 3,
  ORIGIN = 4,
  CLEAR_ON_TRANSITION_CROSS_ORIGIN = 5,
  ORIGIN_CLEAR_ON_TRANSITION_FROM_SECURE_TO_INSECURE = 6,
  NO_REFERRER = 7,
  MAX = NO_REFERRER,
};

inline std::optional<ReferrerPolicy> ReferrerPolicyFromHeader(
    std::string_view) {
  return std::nullopt;
}

}  // namespace net

#endif  // STANDALONE_RENDERER_STUBS_NET_URL_REQUEST_REFERRER_POLICY_H_
