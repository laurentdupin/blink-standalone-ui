// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/base/schemeful_site.h"
#include "services/network/public/cpp/permissions_policy/permissions_policy_declaration.h"
#include "third_party/blink/public/platform/web_security_origin.h"
#include "third_party/blink/renderer/platform/weborigin/security_origin.h"
#include "url/third_party/mozilla/url_parse.h"

#include "url/gurl.h"

namespace net {

SchemefulSite::SchemefulSite(const url::Origin& origin)
    : site_as_origin_(origin) {}
SchemefulSite::SchemefulSite(const GURL&) {}
SchemefulSite::SchemefulSite(const SchemefulSite& other) = default;
SchemefulSite::SchemefulSite(SchemefulSite&& other) noexcept = default;
SchemefulSite& SchemefulSite::operator=(const SchemefulSite& other) = default;
SchemefulSite& SchemefulSite::operator=(SchemefulSite&& other) noexcept =
    default;
bool SchemefulSite::IsSameSite(const url::Origin&, const url::Origin&) {
  return true;
}
bool SchemefulSite::IsSameSiteWith(const url::Origin&) const {
  return true;
}
bool SchemefulSite::IsSameSite(const GURL&, const GURL&) {
  return true;
}
bool SchemefulSite::IsSameSiteWith(const GURL&) const {
  return true;
}
bool SchemefulSite::FromWire(const url::Origin& site_as_origin,
                             SchemefulSite* out) {
  if (out) {
    *out = SchemefulSite(site_as_origin);
  }
  return true;
}
std::optional<SchemefulSite> SchemefulSite::CreateIfHasRegisterableDomain(
    const url::Origin& origin) {
  return SchemefulSite(origin);
}
void SchemefulSite::ConvertWebSocketToHttp() {}
SchemefulSite SchemefulSite::Deserialize(std::string_view) {
  return SchemefulSite();
}
std::string SchemefulSite::Serialize() const {
  return {};
}
std::string SchemefulSite::SerializeFileSiteWithHost() const {
  return {};
}
std::string SchemefulSite::GetDebugString() const {
  return {};
}
GURL SchemefulSite::GetURL() const {
  return GURL();
}
std::optional<SchemefulSite> SchemefulSite::DeserializeWithNonce(
    base::PassKey<NetworkAnonymizationKey>,
    std::string_view) {
  return SchemefulSite();
}
std::optional<std::string> SchemefulSite::SerializeWithNonce(
    base::PassKey<NetworkAnonymizationKey>) {
  return std::string();
}
const url::Origin& SchemefulSite::GetInternalOriginForTesting() const {
  return site_as_origin_;
}
size_t SchemefulSite::EstimateMemoryUsage() const {
  return 0;
}
std::optional<SchemefulSite> SchemefulSite::DeserializeWithNonce(
    std::string_view) {
  return SchemefulSite();
}
std::optional<std::string> SchemefulSite::SerializeWithNonce() {
  return std::string();
}
bool SchemefulSite::SchemelesslyEqual(const SchemefulSite&) const {
  return true;
}

}  // namespace net

namespace network {

OriginWithPossibleWildcards::OriginWithPossibleWildcards() = default;
OriginWithPossibleWildcards::OriginWithPossibleWildcards(
    const OriginWithPossibleWildcards&) = default;
OriginWithPossibleWildcards& OriginWithPossibleWildcards::operator=(
    const OriginWithPossibleWildcards&) = default;
OriginWithPossibleWildcards::~OriginWithPossibleWildcards() = default;
std::optional<OriginWithPossibleWildcards> OriginWithPossibleWildcards::FromOrigin(
    const url::Origin&) {
  return OriginWithPossibleWildcards();
}
std::optional<OriginWithPossibleWildcards>
OriginWithPossibleWildcards::FromOriginAndWildcardsForTest(const url::Origin&,
                                                           bool) {
  return OriginWithPossibleWildcards();
}
std::optional<OriginWithPossibleWildcards> OriginWithPossibleWildcards::Parse(
    const std::string&,
    const NodeType) {
  return OriginWithPossibleWildcards();
}
std::string OriginWithPossibleWildcards::Serialize() const {
  return {};
}
bool OriginWithPossibleWildcards::DoesMatchOrigin(const url::Origin&) const {
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
    : feature(network::mojom::PermissionsPolicyFeature(0)) {}
ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    network::mojom::PermissionsPolicyFeature input_feature)
    : feature(input_feature) {}
ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    network::mojom::PermissionsPolicyFeature input_feature,
    const std::vector<network::OriginWithPossibleWildcards>&,
    const std::optional<url::Origin>& input_self_if_matches,
    bool input_matches_all_origins,
    bool input_matches_opaque_src)
    : feature(input_feature),
      self_if_matches(input_self_if_matches),
      matches_all_origins(input_matches_all_origins),
      matches_opaque_src(input_matches_opaque_src) {}
ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    const ParsedPermissionsPolicyDeclaration& rhs)
    : feature(rhs.feature),
      self_if_matches(rhs.self_if_matches),
      matches_all_origins(rhs.matches_all_origins),
      matches_opaque_src(rhs.matches_opaque_src),
      reporting_endpoint(rhs.reporting_endpoint) {}
ParsedPermissionsPolicyDeclaration& ParsedPermissionsPolicyDeclaration::
operator=(const ParsedPermissionsPolicyDeclaration& rhs) {
  feature = rhs.feature;
  allowed_origins.clear();
  self_if_matches = rhs.self_if_matches;
  matches_all_origins = rhs.matches_all_origins;
  matches_opaque_src = rhs.matches_opaque_src;
  reporting_endpoint = rhs.reporting_endpoint;
  return *this;
}
ParsedPermissionsPolicyDeclaration::ParsedPermissionsPolicyDeclaration(
    ParsedPermissionsPolicyDeclaration&&) noexcept = default;
ParsedPermissionsPolicyDeclaration& ParsedPermissionsPolicyDeclaration::
operator=(ParsedPermissionsPolicyDeclaration&&) noexcept = default;
ParsedPermissionsPolicyDeclaration::~ParsedPermissionsPolicyDeclaration() =
    default;
bool ParsedPermissionsPolicyDeclaration::Contains(const url::Origin&) const {
  return matches_all_origins;
}

}  // namespace network

namespace blink {

WebSecurityOrigin WebSecurityOrigin::CreateFromString(const WebString&) {
  return WebSecurityOrigin();
}
WebSecurityOrigin WebSecurityOrigin::Create(const WebURL&) {
  return WebSecurityOrigin();
}
void WebSecurityOrigin::Reset() {
  private_.Reset();
}
void WebSecurityOrigin::Assign(const WebSecurityOrigin& other) {
  private_ = other.private_;
}
WebString WebSecurityOrigin::Protocol() const {
  return WebString();
}
WebString WebSecurityOrigin::Host() const {
  return WebString();
}
uint16_t WebSecurityOrigin::Port() const {
  return 0;
}
bool WebSecurityOrigin::IsOpaque() const {
  return IsNull();
}
bool WebSecurityOrigin::CanAccess(const WebSecurityOrigin&) const {
  return true;
}
bool WebSecurityOrigin::CanRequest(const WebURL&) const {
  return true;
}
bool WebSecurityOrigin::CanDisplay(const WebURL&) const {
  return true;
}
bool WebSecurityOrigin::IsPotentiallyTrustworthy() const {
  return true;
}
WebString WebSecurityOrigin::ToString() const {
  return WebString();
}
bool WebSecurityOrigin::CanAccessPasswordManager() const {
  return false;
}
bool WebSecurityOrigin::IsSameOriginWith(const WebSecurityOrigin&) const {
  return true;
}
WebSecurityOrigin::WebSecurityOrigin(scoped_refptr<const SecurityOrigin> origin)
    : private_(std::move(origin)) {}
WebSecurityOrigin& WebSecurityOrigin::operator=(
    scoped_refptr<const SecurityOrigin> origin) {
  private_ = std::move(origin);
  return *this;
}
WebSecurityOrigin::operator scoped_refptr<const SecurityOrigin>() const {
  return private_.Get();
}
const SecurityOrigin* WebSecurityOrigin::Get() const {
  return private_.Get();
}
WebSecurityOrigin::WebSecurityOrigin(const url::Origin&) {}
WebSecurityOrigin::operator url::Origin() const {
  return url::Origin();
}

}  // namespace blink
