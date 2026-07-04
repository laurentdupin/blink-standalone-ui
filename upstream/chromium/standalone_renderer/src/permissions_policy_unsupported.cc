// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "services/network/public/cpp/permissions_policy/permissions_policy_mojom_traits.h"

#include <compare>
#include <optional>
#include <string>
#include <vector>

#include "services/network/public/cpp/permissions_policy/permissions_policy.h"
#include "services/network/public/cpp/permissions_policy/permissions_policy_declaration.h"
#include "url/third_party/mozilla/url_parse.h"
#include "url/origin.h"

namespace network {

namespace {

const PermissionsPolicyFeatureList& EmptyFeatureList() {
  static const PermissionsPolicyFeatureList* feature_list =
      new PermissionsPolicyFeatureList();
  return *feature_list;
}

}  // namespace

OriginWithPossibleWildcards::OriginWithPossibleWildcards() = default;
OriginWithPossibleWildcards::OriginWithPossibleWildcards(
    const OriginWithPossibleWildcards& rhs) = default;
OriginWithPossibleWildcards& OriginWithPossibleWildcards::operator=(
    const OriginWithPossibleWildcards& rhs) = default;
OriginWithPossibleWildcards::~OriginWithPossibleWildcards() = default;

std::optional<OriginWithPossibleWildcards>
OriginWithPossibleWildcards::FromOrigin(const url::Origin& origin) {
  if (origin.opaque()) {
    return std::nullopt;
  }
  OriginWithPossibleWildcards result;
  result.csp_source.scheme = origin.scheme();
  result.csp_source.host = origin.host();
  result.csp_source.port = origin.port();
  return result;
}

std::optional<OriginWithPossibleWildcards>
OriginWithPossibleWildcards::FromOriginAndWildcardsForTest(
    const url::Origin& origin,
    bool has_subdomain_wildcard) {
  auto result = FromOrigin(origin);
  if (result) {
    result->csp_source.is_host_wildcard = has_subdomain_wildcard;
  }
  return result;
}

std::optional<OriginWithPossibleWildcards> OriginWithPossibleWildcards::Parse(
    const std::string&,
    const NodeType) {
  return std::nullopt;
}

std::string OriginWithPossibleWildcards::Serialize() const {
  std::string result = csp_source.scheme + "://";
  if (csp_source.is_host_wildcard) {
    result += "*.";
  }
  result += csp_source.host;
  if (!csp_source.is_port_wildcard &&
      csp_source.port != url::PORT_UNSPECIFIED) {
    result += ":" + std::to_string(csp_source.port);
  }
  return result;
}

bool OriginWithPossibleWildcards::DoesMatchOrigin(
    const url::Origin& match_origin) const {
  if (match_origin.opaque()) {
    return false;
  }
  if (csp_source.scheme != match_origin.scheme()) {
    return false;
  }

  const std::string& source_host = csp_source.host;
  const std::string& match_host = match_origin.host();
  if (csp_source.is_host_wildcard) {
    if (source_host.empty() || match_host.size() <= source_host.size()) {
      return false;
    }
    const size_t suffix_start = match_host.size() - source_host.size();
    if (match_host.compare(suffix_start, source_host.size(), source_host) !=
        0) {
      return false;
    }
    if (match_host[suffix_start - 1] != '.') {
      return false;
    }
  } else if (source_host != match_host) {
    return false;
  }

  if (!csp_source.is_port_wildcard &&
      csp_source.port != url::PORT_UNSPECIFIED &&
      csp_source.port != match_origin.port()) {
    return false;
  }
  return true;
}

bool operator==(const OriginWithPossibleWildcards&,
                const OriginWithPossibleWildcards&) {
  return true;
}

std::strong_ordering operator<=>(const OriginWithPossibleWildcards&,
                                 const OriginWithPossibleWildcards&) {
  return std::strong_ordering::equal;
}

ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration()
    : feature(static_cast<network::mojom::PermissionsPolicyFeature>(0)) {}

ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    network::mojom::PermissionsPolicyFeature feature)
    : feature(feature) {}

ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    network::mojom::PermissionsPolicyFeature feature,
    const std::vector<network::OriginWithPossibleWildcards>& allowed_origins,
    const std::optional<url::Origin>& self_if_matches,
    bool matches_all_origins,
    bool matches_opaque_src)
    : feature(feature),
      allowed_origins(allowed_origins),
      self_if_matches(self_if_matches),
      matches_all_origins(matches_all_origins),
      matches_opaque_src(matches_opaque_src) {}

ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    const ParsedPermissionsPolicyDeclaration& rhs) = default;
ParsedPermissionsPolicyDeclaration& ParsedPermissionsPolicyDeclaration::
operator=(const ParsedPermissionsPolicyDeclaration& rhs) = default;
ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    ParsedPermissionsPolicyDeclaration&&) noexcept = default;
ParsedPermissionsPolicyDeclaration& ParsedPermissionsPolicyDeclaration::
operator=(ParsedPermissionsPolicyDeclaration&&) noexcept = default;
ParsedPermissionsPolicyDeclaration::~ParsedPermissionsPolicyDeclaration() =
    default;

bool ParsedPermissionsPolicyDeclaration::Contains(
    const url::Origin& origin) const {
  if (matches_all_origins || (matches_opaque_src && origin.opaque())) {
    return true;
  }
  if (origin == self_if_matches) {
    return true;
  }
  for (const auto& allowed_origin : allowed_origins) {
    if (allowed_origin.DoesMatchOrigin(origin)) {
      return true;
    }
  }
  return false;
}

PermissionsPolicyFeaturesBitset::PermissionsPolicyFeaturesBitset() = default;
PermissionsPolicyFeaturesBitset::PermissionsPolicyFeaturesBitset(
    const PermissionsPolicyFeaturesBitset&) = default;
PermissionsPolicyFeaturesBitset& PermissionsPolicyFeaturesBitset::operator=(
    const PermissionsPolicyFeaturesBitset&) = default;
PermissionsPolicyFeaturesBitset::PermissionsPolicyFeaturesBitset(
    PermissionsPolicyFeaturesBitset&&) = default;
PermissionsPolicyFeaturesBitset& PermissionsPolicyFeaturesBitset::operator=(
    PermissionsPolicyFeaturesBitset&&) = default;

PermissionsPolicy::Allowlist::Allowlist() = default;
PermissionsPolicy::Allowlist::Allowlist(const Allowlist&) = default;
PermissionsPolicy::Allowlist::Allowlist(Allowlist&&) noexcept = default;
PermissionsPolicy::Allowlist::~Allowlist() = default;
PermissionsPolicy::Allowlist& PermissionsPolicy::Allowlist::operator=(
    Allowlist&&) noexcept = default;

PermissionsPolicy::Allowlist PermissionsPolicy::Allowlist::FromDeclaration(
    const network::ParsedPermissionsPolicyDeclaration& parsed_declaration) {
  PermissionsPolicy::Allowlist result;
  if (parsed_declaration.self_if_matches) {
    result.AddSelf(parsed_declaration.self_if_matches);
  }
  if (parsed_declaration.matches_all_origins) {
    result.AddAll();
  }
  if (parsed_declaration.matches_opaque_src) {
    result.AddOpaqueSrc();
  }
  for (const auto& origin : parsed_declaration.allowed_origins) {
    result.Add(origin);
  }
  return result;
}

void PermissionsPolicy::Allowlist::Add(
    const network::OriginWithPossibleWildcards& origin) {
  allowed_origins_.push_back(origin);
}

void PermissionsPolicy::Allowlist::AddSelf(std::optional<url::Origin> self) {
  self_if_matches_ = std::move(self);
}

void PermissionsPolicy::Allowlist::AddAll() {
  matches_all_origins_ = true;
}

void PermissionsPolicy::Allowlist::AddOpaqueSrc() {
  matches_opaque_src_ = true;
}

bool PermissionsPolicy::Allowlist::Contains(const url::Origin& origin) const {
  if (origin == self_if_matches_) {
    return true;
  }
  for (const auto& allowed_origin : allowed_origins_) {
    if (allowed_origin.DoesMatchOrigin(origin)) {
      return true;
    }
  }
  if (origin.opaque()) {
    return matches_opaque_src_;
  }
  return matches_all_origins_;
}

const std::optional<url::Origin>&
PermissionsPolicy::Allowlist::SelfIfMatches() const {
  return self_if_matches_;
}

bool PermissionsPolicy::Allowlist::MatchesAll() const {
  return matches_all_origins_;
}

void PermissionsPolicy::Allowlist::RemoveMatchesAll() {
  matches_all_origins_ = false;
}

bool PermissionsPolicy::Allowlist::MatchesOpaqueSrc() const {
  return matches_opaque_src_;
}

PermissionsPolicy::PermissionsPolicy(mojo::DefaultConstruct::Tag)
    : origin_(url::Origin()),
      headerless_(false),
      feature_list_(EmptyFeatureList()) {}

PermissionsPolicy::PermissionsPolicy(const PermissionsPolicy& other)
    : origin_(other.origin_),
      headerless_(other.headerless_),
      allowlists_(other.allowlists_),
      reporting_endpoints_(other.reporting_endpoints_),
      inherited_policies_(other.inherited_policies_),
      feature_list_(EmptyFeatureList()) {}

PermissionsPolicy& PermissionsPolicy::operator=(
    const PermissionsPolicy& other) {
  if (this != &other) {
    origin_ = other.origin_;
    headerless_ = other.headerless_;
    allowlists_ = other.allowlists_;
    reporting_endpoints_ = other.reporting_endpoints_;
    inherited_policies_ = other.inherited_policies_;
  }
  return *this;
}

PermissionsPolicy::PermissionsPolicy(PermissionsPolicy&& other) noexcept
    : origin_(std::move(other.origin_)),
      headerless_(other.headerless_),
      allowlists_(std::move(other.allowlists_)),
      reporting_endpoints_(std::move(other.reporting_endpoints_)),
      inherited_policies_(std::move(other.inherited_policies_)),
      feature_list_(EmptyFeatureList()) {}

PermissionsPolicy& PermissionsPolicy::operator=(
    PermissionsPolicy&& other) noexcept {
  if (this != &other) {
    origin_ = std::move(other.origin_);
    headerless_ = other.headerless_;
    allowlists_ = std::move(other.allowlists_);
    reporting_endpoints_ = std::move(other.reporting_endpoints_);
    inherited_policies_ = std::move(other.inherited_policies_);
  }
  return *this;
}

PermissionsPolicy::~PermissionsPolicy() = default;

std::unique_ptr<PermissionsPolicy> PermissionsPolicy::CreateFromParsedPolicy(
    const network::ParsedPermissionsPolicy&,
    const url::Origin&) {
  return nullptr;
}

bool PermissionsPolicy::IsFeatureEnabledForOrigin(
    mojom::PermissionsPolicyFeature,
    const url::Origin&,
    bool) const {
  return false;
}

}  // namespace network

namespace mojo {

bool StructTraits<network::mojom::OriginWithPossibleWildcardsDataView,
                  network::OriginWithPossibleWildcards>::
    Read(network::mojom::OriginWithPossibleWildcardsDataView in,
         network::OriginWithPossibleWildcards* out) {
  out->csp_source.is_host_wildcard = in.is_host_wildcard();
  out->csp_source.is_port_wildcard = in.is_port_wildcard();
  out->csp_source.port = in.port();
  return in.ReadScheme(&out->csp_source.scheme) &&
         in.ReadHost(&out->csp_source.host) &&
         !out->csp_source.scheme.empty();
}

bool StructTraits<network::mojom::ParsedPermissionsPolicyDeclarationDataView,
                  network::ParsedPermissionsPolicyDeclaration>::
    Read(network::mojom::ParsedPermissionsPolicyDeclarationDataView in,
         network::ParsedPermissionsPolicyDeclaration* out) {
  out->matches_all_origins = in.matches_all_origins();
  out->matches_opaque_src = in.matches_opaque_src();
  if (!in.ReadReportingEndpoint(&out->reporting_endpoint)) {
    return false;
  }
  return in.ReadFeature(&out->feature) &&
         in.ReadAllowedOrigins(&out->allowed_origins) &&
         in.ReadSelfIfMatches(&out->self_if_matches);
}

bool StructTraits<network::mojom::PermissionsPolicyDataView,
                  network::PermissionsPolicy>::
    Read(network::mojom::PermissionsPolicyDataView,
         network::PermissionsPolicy*) {
  return false;
}

}  // namespace mojo
