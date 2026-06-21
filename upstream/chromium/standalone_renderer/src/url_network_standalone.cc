// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/base/schemeful_site.h"
#include "net/base/net_errors.h"
#include "net/http/http_connection_info.h"
#include "services/network/public/cpp/net_ipc_param_traits.h"
#include "services/network/public/cpp/cors/cors.h"
#include "third_party/blink/public/platform/web_security_origin.h"
#include "third_party/blink/renderer/platform/weborigin/scheme_registry.h"
#include "third_party/blink/renderer/platform/weborigin/security_origin.h"
#include "url/third_party/mozilla/url_parse.h"

#include "base/pickle.h"
#include "url/gurl.h"

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

bool SchemeRegistry::IsSpecialScheme(const String& scheme) {
  return EqualIgnoringAsciiCase(scheme, "http") ||
         EqualIgnoringAsciiCase(scheme, "https") ||
         EqualIgnoringAsciiCase(scheme, "file") ||
         EqualIgnoringAsciiCase(scheme, "ftp") ||
         EqualIgnoringAsciiCase(scheme, "ws") ||
         EqualIgnoringAsciiCase(scheme, "wss");
}

bool SchemeRegistry::ShouldTreatURLSchemeAsAllowedForReferrer(
    const String& scheme) {
  return EqualIgnoringAsciiCase(scheme, "http") ||
         EqualIgnoringAsciiCase(scheme, "https") ||
         EqualIgnoringAsciiCase(scheme, "file") ||
         EqualIgnoringAsciiCase(scheme, "data");
}

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
