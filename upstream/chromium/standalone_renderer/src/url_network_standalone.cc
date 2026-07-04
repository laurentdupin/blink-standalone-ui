// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/base/schemeful_site.h"
#include "net/base/net_errors.h"
#include "net/base/registry_controlled_domains/registry_controlled_domain.h"
#include "net/base/url_util.h"
#include "net/http/http_connection_info.h"
#include "services/network/public/cpp/net_ipc_param_traits.h"
#include "services/network/public/cpp/cors/cors.h"
#include "third_party/blink/public/platform/web_security_origin.h"
#include "third_party/blink/public/platform/web_url.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/weborigin/security_origin.h"

#include "base/check.h"
#include "base/pickle.h"
#include "base/trace_event/memory_usage_estimator.h"
#include "url/gurl.h"
#include "url/url_canon.h"
#include "url/url_constants.h"

namespace IPC {

void ParamTraits<net::HttpConnectionInfo>::Write(base::Pickle* m,
                                                 const param_type& p) {
  m->WriteInt(static_cast<int>(p));
}

bool ParamTraits<net::HttpConnectionInfo>::Read(const base::Pickle*,
                                                base::PickleIterator* iter,
                                                param_type* p) {
  int value = 0;
  if (!iter->ReadInt(&value)) {
    return false;
  }
  if (value < static_cast<int>(net::HttpConnectionInfo::kUNKNOWN) ||
      value > static_cast<int>(net::HttpConnectionInfo::kMaxValue)) {
    return false;
  }
  *p = static_cast<net::HttpConnectionInfo>(value);
  return true;
}

}  // namespace IPC

namespace net {

namespace {

bool IsSameSiteInternal(const url::Origin& a,
                        const url::Origin& b,
                        bool a_is_site) {
  if (a.opaque() || b.opaque()) {
    return a == b;
  }

  if (a.scheme() != b.scheme()) {
    return false;
  }

  if (a.host() == b.host()) {
    return true;
  }

  if (!IsStandardSchemeWithNetworkHost(a.scheme())) {
    return false;
  }

  std::string_view b_site = GetDomainAndRegistryAsStringPiece(
      b, net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);
  if (b_site.empty()) {
    return false;
  }

  std::string_view a_site =
      a_is_site
          ? a.host()
          : GetDomainAndRegistryAsStringPiece(
                a,
                net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);
  return a_site == b_site;
}

}  // namespace

std::string ErrorToShortString(int error) {
  if (error == OK) {
    return "OK";
  }
  switch (error) {
#define NET_ERROR(label, value) \
  case ERR_##label:            \
    return "ERR_" #label;
#include "net/base/net_error_list.h"
#undef NET_ERROR
    default:
      return "ERR_UNKNOWN";
  }
}

std::string ErrorToString(int error) {
  return "net::" + ErrorToShortString(error);
}

std::string ExtendedErrorToString(int error, int) {
  return ErrorToString(error);
}

struct SchemefulSite::ObtainASiteResult {
  std::optional<url::Origin> origin;
  bool used_registerable_domain;
};

SchemefulSite::ObtainASiteResult SchemefulSite::ObtainASite(
    const url::Origin& origin) {
  if (origin.opaque()) {
    return {std::nullopt, false};
  }

  int port = url::DefaultPortForScheme(origin.scheme());
  if (port == url::PORT_UNSPECIFIED) {
    port = 0;
  }

  std::string_view registerable_domain;
  if (IsStandardSchemeWithNetworkHost(origin.scheme())) {
    registerable_domain = GetDomainAndRegistryAsStringPiece(
        origin, net::registry_controlled_domains::INCLUDE_PRIVATE_REGISTRIES);
    if (!registerable_domain.empty() &&
        registerable_domain.size() == origin.host().size() &&
        origin.port() == port) {
      return {std::nullopt, true};
    }
  }

  const bool used_registerable_domain = !registerable_domain.empty();
  if (!used_registerable_domain) {
    registerable_domain = origin.host();
  }

  return {url::Origin::CreateFromNormalizedTuple(
              origin.scheme(), std::string(registerable_domain), port),
          used_registerable_domain};
}

SchemefulSite::SchemefulSite(ObtainASiteResult result,
                             const url::Origin& origin) {
  site_as_origin_ = result.origin ? std::move(*result.origin) : origin;
}

SchemefulSite::SchemefulSite(const url::Origin& origin)
    : SchemefulSite(ObtainASite(origin), origin) {}
SchemefulSite::SchemefulSite(const GURL& url)
    : SchemefulSite(url::Origin::Create(url)) {}
SchemefulSite::SchemefulSite(const SchemefulSite& other) = default;
SchemefulSite::SchemefulSite(SchemefulSite&& other) noexcept = default;
SchemefulSite& SchemefulSite::operator=(const SchemefulSite& other) = default;
SchemefulSite& SchemefulSite::operator=(SchemefulSite&& other) noexcept =
    default;
bool SchemefulSite::IsSameSite(const url::Origin& a, const url::Origin& b) {
  const bool same_site = IsSameSiteInternal(a, b, false);
  DCHECK_EQ(same_site, SchemefulSite(a) == SchemefulSite(b));
  return same_site;
}
bool SchemefulSite::IsSameSiteWith(const url::Origin& other) const {
  const bool same_site = IsSameSiteInternal(internal_value(), other, true);
  DCHECK_EQ(same_site, *this == SchemefulSite(other));
  return same_site;
}
bool SchemefulSite::IsSameSite(const GURL& a, const GURL& b) {
  const bool same_site =
      IsSameSiteInternal(url::Origin::Create(a), url::Origin::Create(b), false);
  DCHECK_EQ(same_site, SchemefulSite(a) == SchemefulSite(b));
  return same_site;
}
bool SchemefulSite::IsSameSiteWith(const GURL& other) const {
  const bool same_site =
      IsSameSiteInternal(internal_value(), url::Origin::Create(other), true);
  DCHECK_EQ(same_site, *this == SchemefulSite(other));
  return same_site;
}
bool SchemefulSite::FromWire(const url::Origin& site_as_origin,
                             SchemefulSite* out) {
  SchemefulSite candidate(site_as_origin);
  if (candidate.site_as_origin_ != site_as_origin) {
    return false;
  }
  *out = std::move(candidate);
  return true;
}
std::optional<SchemefulSite> SchemefulSite::CreateIfHasRegisterableDomain(
    const url::Origin& origin) {
  ObtainASiteResult result = ObtainASite(origin);
  if (!result.used_registerable_domain) {
    return std::nullopt;
  }
  return SchemefulSite(std::move(result), origin);
}
void SchemefulSite::ConvertWebSocketToHttp() {
  if (site_as_origin_.scheme() == url::kWsScheme ||
      site_as_origin_.scheme() == url::kWssScheme) {
    site_as_origin_ = url::Origin::Create(
        ChangeWebSocketSchemeToHttpScheme(site_as_origin_.GetURL()));
  }
}
SchemefulSite SchemefulSite::Deserialize(std::string_view value) {
  return SchemefulSite(GURL(value));
}
std::string SchemefulSite::Serialize() const {
  return site_as_origin_.Serialize();
}
std::string SchemefulSite::SerializeFileSiteWithHost() const {
  DCHECK_EQ(url::kFileScheme, site_as_origin_.scheme());
  return site_as_origin_.GetTupleOrPrecursorTupleIfOpaque().Serialize();
}
std::string SchemefulSite::GetDebugString() const {
  return site_as_origin_.GetDebugString();
}
GURL SchemefulSite::GetURL() const {
  return site_as_origin_.GetURL();
}
std::optional<SchemefulSite> SchemefulSite::DeserializeWithNonce(
    base::PassKey<NetworkAnonymizationKey>,
    std::string_view value) {
  return DeserializeWithNonce(value);
}
std::optional<std::string> SchemefulSite::SerializeWithNonce(
    base::PassKey<NetworkAnonymizationKey>) {
  return SerializeWithNonce();
}
const url::Origin& SchemefulSite::GetInternalOriginForTesting() const {
  return site_as_origin_;
}
size_t SchemefulSite::EstimateMemoryUsage() const {
  return base::trace_event::EstimateMemoryUsage(site_as_origin_);
}
std::optional<SchemefulSite> SchemefulSite::DeserializeWithNonce(
    std::string_view value) {
  std::optional<url::Origin> result = url::Origin::Deserialize(value);
  if (!result) {
    return std::nullopt;
  }
  return SchemefulSite(*result);
}
std::optional<std::string> SchemefulSite::SerializeWithNonce() {
  return site_as_origin_.SerializeWithNonceAndInitIfNeeded();
}
bool SchemefulSite::SchemelesslyEqual(const SchemefulSite& other) const {
  return site_as_origin_.host() == other.site_as_origin_.host();
}

std::ostream& operator<<(std::ostream& os, const SchemefulSite& site) {
  os << site.Serialize();
  return os;
}

}  // namespace net

namespace network {

namespace cors {

bool IsCorsSameOriginResponseType(mojom::FetchResponseType type) {
  return type == mojom::FetchResponseType::kDefault ||
         type == mojom::FetchResponseType::kBasic ||
         type == mojom::FetchResponseType::kCors;
}

bool IsCorsCrossOriginResponseType(mojom::FetchResponseType type) {
  return type == mojom::FetchResponseType::kOpaque ||
         type == mojom::FetchResponseType::kOpaqueRedirect;
}

}  // namespace cors

}  // namespace network

namespace blink {

WebSecurityOrigin WebSecurityOrigin::CreateFromString(
    const WebString& origin) {
  return WebSecurityOrigin(SecurityOrigin::CreateFromString(origin));
}
WebSecurityOrigin WebSecurityOrigin::Create(const WebURL& url) {
  return WebSecurityOrigin(SecurityOrigin::Create(url));
}
void WebSecurityOrigin::Reset() {
  private_ = nullptr;
}
void WebSecurityOrigin::Assign(const WebSecurityOrigin& other) {
  private_ = other.private_;
}
WebString WebSecurityOrigin::Protocol() const {
  DCHECK(private_);
  return private_->Protocol();
}
WebString WebSecurityOrigin::Host() const {
  DCHECK(private_);
  return private_->Host();
}
uint16_t WebSecurityOrigin::Port() const {
  DCHECK(private_);
  return private_->Port();
}
bool WebSecurityOrigin::IsOpaque() const {
  DCHECK(private_);
  return private_->IsOpaque();
}
bool WebSecurityOrigin::CanAccess(const WebSecurityOrigin& other) const {
  DCHECK(private_);
  DCHECK(other.private_);
  return private_->CanAccess(other.private_.Get());
}
bool WebSecurityOrigin::CanRequest(const WebURL& url) const {
  DCHECK(private_);
  return private_->CanRequest(url);
}
bool WebSecurityOrigin::CanDisplay(const WebURL& url) const {
  DCHECK(private_);
  return private_->CanDisplay(url);
}
bool WebSecurityOrigin::IsPotentiallyTrustworthy() const {
  DCHECK(private_);
  return private_->IsPotentiallyTrustworthy();
}
WebString WebSecurityOrigin::ToString() const {
  DCHECK(private_);
  return private_->ToString();
}
bool WebSecurityOrigin::CanAccessPasswordManager() const {
  DCHECK(private_);
  return private_->CanAccessPasswordManager();
}
bool WebSecurityOrigin::IsSameOriginWith(const WebSecurityOrigin& other) const {
  DCHECK(private_);
  DCHECK(other.private_);
  return private_->IsSameOriginWith(other.private_.Get());
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
WebSecurityOrigin::WebSecurityOrigin(const url::Origin& origin) {
  *this = SecurityOrigin::CreateFromUrlOrigin(origin);
}
WebSecurityOrigin::operator url::Origin() const {
  return Get()->ToUrlOrigin();
}

bool IsContentDispositionAttachment(const String&) {
  return false;
}

}  // namespace blink
