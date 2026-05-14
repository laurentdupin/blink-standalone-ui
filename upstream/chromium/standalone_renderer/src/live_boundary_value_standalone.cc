// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <ostream>

#include "base/metrics/histogram_functions.h"
#include "base/feature_list.h"
#include "base/uuid.h"
#include "mojo/public/cpp/bindings/lib/pending_receiver_state.h"
#include "mojo/public/cpp/bindings/lib/pending_remote_state.h"
#include "mojo/public/cpp/bindings/connection_group.h"
#include "services/metrics/public/cpp/ukm_source_id.h"
#include "services/network/public/cpp/client_hints.h"
#include "openssl/pool.h"
#include "net/cert/x509_certificate.h"
#include "net/cert/x509_cert_types.h"
#include "net/cert/signed_certificate_timestamp_and_status.h"
#include "services/network/public/cpp/header_util.h"
#include "services/network/public/cpp/is_potentially_trustworthy.h"
#include "third_party/blink/public/common/client_hints/enabled_client_hints.h"
#include "third_party/blink/public/common/features.h"
#include "third_party/blink/public/common/fenced_frame/redacted_fenced_frame_config.h"
#include "third_party/blink/public/common/frame/user_activation_state.h"
#include "third_party/blink/public/common/origin_trials/trial_token.h"
#include "third_party/blink/public/platform/web_string.h"
#include "third_party/blink/public/platform/web_url_error.h"
#include "third_party/blink/public/web/web_navigation_params.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/dom/document_encoding_data.h"
#include "third_party/blink/renderer/core/frame/dom_window.h"
#include "third_party/blink/renderer/core/frame/local_frame.h"
#include "third_party/blink/renderer/bindings/core/v8/script_controller.h"
#include "third_party/blink/renderer/core/frame/policy_container.h"
#include "third_party/blink/renderer/core/frame/navigator_language.h"
#include "third_party/blink/renderer/core/frame/use_counter_impl.h"
#include "third_party/blink/renderer/core/html/html_head_element.h"
#include "third_party/blink/renderer/core/input/event_handler.h"
#include "third_party/blink/renderer/core/loader/frame_loader.h"
#include "third_party/blink/renderer/core/loader/idleness_detector.h"
#include "third_party/blink/renderer/core/loader/interactive_detector.h"
#include "third_party/blink/renderer/core/loader/old_document_info_for_commit.h"
#include "third_party/blink/renderer/core/loader/progress_tracker.h"
#include "third_party/blink/renderer/core/navigation_api/navigation_api.h"
#include "third_party/blink/renderer/core/timing/window_performance.h"
#include "third_party/blink/renderer/core/timing/profiler_group.h"
#include "third_party/blink/renderer/core/view_transition/view_transition_supplement.h"
#include "third_party/blink/renderer/core/dom/document_init.h"
#include "third_party/blink/renderer/core/display_lock/display_lock_utilities.h"
#include "third_party/blink/renderer/core/style/computed_style.h"
#include "third_party/blink/renderer/core/execution_context/window_agent_factory.h"
#include "third_party/blink/renderer/core/frame/frame_console.h"
#include "third_party/blink/renderer/core/inspector/console_message.h"
#include "third_party/blink/renderer/core/navigation_api/navigation_api.h"
#include "third_party/blink/renderer/core/page/focus_controller.h"
#include "third_party/blink/renderer/core/page/frame_tree.h"
#include "third_party/blink/renderer/core/dom/visited_link_state.h"
#include "third_party/blink/renderer/core/execution_context/security_context_init.h"
#include "third_party/blink/public/common/permissions_policy/document_policy.h"
#include "third_party/blink/renderer/core/loader/document_load_timing.h"
#include "third_party/blink/renderer/core/loader/frame_client_hints_preferences_context.h"
#include "third_party/blink/renderer/core/origin_trials/origin_trial_context.h"
#include "third_party/blink/renderer/core/speculation_rules/speculation_rules_header.h"
#include "third_party/blink/renderer/core/xml/document_xslt.h"
#include "third_party/blink/renderer/platform/loader/fetch/background_code_cache_host.h"
#include "third_party/blink/renderer/platform/loader/fetch/body_text_decoder.h"
#include "third_party/blink/renderer/platform/loader/fetch/client_hints_preferences.h"
#include "third_party/blink/renderer/platform/loader/fetch/code_cache_host.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_error.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_load_timing.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_response.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_timing_utils.h"
#include "third_party/blink/renderer/platform/loader/fetch/resource_fetcher.h"
#include "third_party/blink/renderer/platform/loader/fetch/service_worker_router_info.h"
#include "third_party/blink/renderer/platform/loader/fetch/unique_identifier.h"
#include "third_party/blink/renderer/platform/loader/fetch/url_loader/navigation_body_loader.h"
#include "third_party/blink/renderer/platform/network/http_parsers.h"
#include "third_party/blink/renderer/platform/network/encoded_form_data.h"
#include "third_party/blink/renderer/platform/runtime_feature_state/runtime_feature_state_override_context.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/scheduler/public/post_cancellable_task.h"
#include "third_party/blink/public/platform/scheduler/web_scoped_virtual_time_pauser.h"
#include "third_party/blink/renderer/platform/blob/blob_url_null_origin_map.h"
#include "third_party/blink/renderer/platform/blob/blob_url.h"
#include "third_party/blink/renderer/platform/bindings/wrapper_type_info.h"
#include "third_party/blink/renderer/platform/fonts/font_performance.h"
#include "third_party/blink/renderer/platform/weborigin/known_ports.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"
#include "third_party/blink/renderer/platform/weborigin/origin_access_entry.h"
#include "third_party/blink/renderer/platform/weborigin/scheme_registry.h"
#include "third_party/blink/renderer/platform/weborigin/security_policy.h"
#include "third_party/blink/renderer/platform/storage/blink_storage_key.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "url/url_canon.h"
#include "url/gurl.h"
#include "url/origin.h"
#include "url/scheme_host_port.h"
#include "url/url_util.h"

extern "C" void CRYPTO_BUFFER_free(CRYPTO_BUFFER*) {}

namespace base {

Uuid::Uuid() = default;
Uuid::Uuid(const Uuid& other) = default;
Uuid& Uuid::operator=(const Uuid& other) = default;
Uuid::Uuid(Uuid&& other) = default;
Uuid& Uuid::operator=(Uuid&& other) = default;
Uuid Uuid::GenerateRandomV4() {
  return Uuid();
}
Uuid Uuid::ParseLowercase(std::string_view) {
  return Uuid();
}
Uuid Uuid::ParseLowercase(std::u16string_view) {
  return Uuid();
}
const std::string& Uuid::AsLowercaseString() const {
  return lowercase_;
}
absl::uint128 Uuid::AsInteger() const {
  return 0;
}
void UmaHistogramTimes(std::string_view, TimeDelta) {}

}  // namespace base

namespace net {

CertPrincipal::CertPrincipal() = default;
CertPrincipal::CertPrincipal(const CertPrincipal&) = default;
CertPrincipal::CertPrincipal(CertPrincipal&&) = default;
CertPrincipal::~CertPrincipal() = default;
bool CertPrincipal::ParseDistinguishedName(
    bssl::der::Input,
    PrintableStringHandling) {
  return false;
}
std::string CertPrincipal::GetDisplayName() const {
  return common_name;
}
bool CertPrincipal::EqualsForTesting(const CertPrincipal& other) const {
  return common_name == other.common_name;
}

SignedCertificateTimestampAndStatus::SignedCertificateTimestampAndStatus() =
    default;
SignedCertificateTimestampAndStatus::SignedCertificateTimestampAndStatus(
    const scoped_refptr<ct::SignedCertificateTimestamp>& sct_in,
    ct::SCTVerifyStatus status_in)
    : sct(sct_in), status(status_in) {}
SignedCertificateTimestampAndStatus::SignedCertificateTimestampAndStatus(
    const SignedCertificateTimestampAndStatus& other)
    : sct(other.sct), status(other.status) {}
SignedCertificateTimestampAndStatus::~SignedCertificateTimestampAndStatus() =
    default;

namespace ct {
SignedEntryData::SignedEntryData() = default;
SignedEntryData::~SignedEntryData() = default;
void SignedEntryData::Reset() {
  *this = SignedEntryData();
}
DigitallySigned::DigitallySigned() = default;
DigitallySigned::~DigitallySigned() = default;
bool DigitallySigned::SignatureParametersMatch(
    HashAlgorithm other_hash_algorithm,
    SignatureAlgorithm other_signature_algorithm) const {
  return hash_algorithm == other_hash_algorithm &&
         signature_algorithm == other_signature_algorithm;
}
SignedCertificateTimestamp::SignedCertificateTimestamp() = default;
SignedCertificateTimestamp::~SignedCertificateTimestamp() = default;
bool SignedCertificateTimestamp::LessThan::operator()(
    const scoped_refptr<SignedCertificateTimestamp>& lhs,
    const scoped_refptr<SignedCertificateTimestamp>& rhs) const {
  return lhs.get() < rhs.get();
}
}  // namespace ct

X509Certificate::ParsedFields::~ParsedFields() = default;
X509Certificate::~X509Certificate() = default;

ResolveErrorInfo::ResolveErrorInfo() = default;
ResolveErrorInfo::ResolveErrorInfo(int resolve_error,
                                   bool secure_network_error)
    : error(resolve_error), is_secure_network_error(secure_network_error) {}
ResolveErrorInfo::ResolveErrorInfo(const ResolveErrorInfo&) = default;
ResolveErrorInfo::ResolveErrorInfo(ResolveErrorInfo&&) = default;
ResolveErrorInfo& ResolveErrorInfo::operator=(const ResolveErrorInfo&) =
    default;
ResolveErrorInfo& ResolveErrorInfo::operator=(ResolveErrorInfo&&) = default;

IPEndPoint::IPEndPoint() = default;
IPEndPoint::~IPEndPoint() = default;
IPEndPoint::IPEndPoint(const IPEndPoint&) = default;
SSLInfo::SSLInfo() = default;
SSLInfo::SSLInfo(const SSLInfo&) = default;
SSLInfo::SSLInfo(SSLInfo&&) = default;
SSLInfo& SSLInfo::operator=(const SSLInfo&) = default;
SSLInfo& SSLInfo::operator=(SSLInfo&&) = default;
SSLInfo::~SSLInfo() = default;
AuthChallengeInfo::AuthChallengeInfo() = default;
AuthChallengeInfo::AuthChallengeInfo(const AuthChallengeInfo&) = default;
AuthChallengeInfo::~AuthChallengeInfo() = default;
bool HostStringIsLocalhost(std::string_view) {
  return false;
}

}  // namespace net

namespace network {

CorsErrorStatus::CorsErrorStatus(const CorsErrorStatus&) = default;
CorsErrorStatus::~CorsErrorStatus() = default;
IntegrityMetadata::IntegrityMetadata() = default;
IntegrityMetadata::~IntegrityMetadata() = default;
IntegrityMetadata::IntegrityMetadata(const IntegrityMetadata&) = default;
IntegrityMetadata& IntegrityMetadata::operator=(const IntegrityMetadata&) =
    default;
IntegrityMetadata::IntegrityMetadata(IntegrityMetadata&&) = default;
IntegrityMetadata& IntegrityMetadata::operator=(IntegrityMetadata&&) = default;

bool NoVarySearchHasBooleanParamsMember(std::string_view) {
  return false;
}
bool IsOriginPotentiallyTrustworthy(const url::Origin&) {
  return true;
}
bool IsUrlPotentiallyTrustworthy(const GURL&) {
  return true;
}
bool IsSuccessfulStatus(int status) {
  return status >= 200 && status < 300;
}
const ClientHintToNameMap& GetClientHintToNameMap() {
  static const ClientHintToNameMap* map = new ClientHintToNameMap();
  return *map;
}

}  // namespace network

namespace url {

Parsed::Parsed() = default;
Parsed::Parsed(const Parsed& other)
    : scheme(other.scheme),
      username(other.username),
      password(other.password),
      host(other.host),
      port(other.port),
      path(other.path),
      query(other.query),
      ref(other.ref),
      potentially_dangling_markup(other.potentially_dangling_markup),
      has_opaque_path(other.has_opaque_path) {
  if (other.inner_parsed()) {
    set_inner_parsed(*other.inner_parsed());
  }
}
Parsed& Parsed::operator=(const Parsed& other) {
  if (this == &other) {
    return *this;
  }
  scheme = other.scheme;
  username = other.username;
  password = other.password;
  host = other.host;
  port = other.port;
  path = other.path;
  query = other.query;
  ref = other.ref;
  potentially_dangling_markup = other.potentially_dangling_markup;
  has_opaque_path = other.has_opaque_path;
  clear_inner_parsed();
  if (other.inner_parsed()) {
    set_inner_parsed(*other.inner_parsed());
  }
  return *this;
}
Parsed::~Parsed() {
  clear_inner_parsed();
}
int Parsed::Length() const {
  int length = 0;
  for (const Component* component :
       {&scheme, &username, &password, &host, &port, &path, &query, &ref}) {
    if (component->is_valid() && component->end() > length) {
      length = component->end();
    }
  }
  return length;
}
int Parsed::CountCharactersBefore(ComponentType, bool) const {
  return 0;
}
Component Parsed::GetContent() const {
  return Component();
}

SchemeHostPort::SchemeHostPort() = default;
SchemeHostPort::SchemeHostPort(std::string_view scheme,
                               std::string_view host,
                               uint16_t port)
    : port_(port), scheme_(scheme), host_(host) {}
SchemeHostPort::SchemeHostPort(std::string scheme,
                               std::string host,
                               uint16_t port,
                               ConstructPolicy)
    : port_(port), scheme_(std::move(scheme)), host_(std::move(host)) {}
SchemeHostPort::SchemeHostPort(const GURL&) {}
SchemeHostPort::~SchemeHostPort() = default;
bool SchemeHostPort::IsValid() const {
  return !scheme_.empty();
}
std::string SchemeHostPort::Serialize() const {
  return scheme_.empty() ? std::string() : scheme_ + "://" + host_;
}
GURL SchemeHostPort::GetURL() const {
  return GURL();
}
size_t SchemeHostPort::EstimateMemoryUsage() const {
  return 0;
}
bool SchemeHostPort::ShouldDiscardHostAndPort(std::string_view) {
  return false;
}
std::string SchemeHostPort::SerializeInternal(url::Parsed*) const {
  return Serialize();
}

Origin::Origin() = default;
Origin::Origin(const Origin&) = default;
Origin& Origin::operator=(const Origin&) = default;
Origin::Origin(Origin&&) noexcept = default;
Origin& Origin::operator=(Origin&&) noexcept = default;
Origin::~Origin() = default;
Origin Origin::Create(const GURL&) {
  return Origin();
}
Origin Origin::Resolve(const GURL&, const Origin& base_origin) {
  return base_origin;
}
std::optional<Origin> Origin::UnsafelyCreateTupleOriginWithoutNormalization(
    std::string_view,
    std::string_view,
    uint16_t) {
  return Origin();
}
Origin Origin::CreateFromNormalizedTuple(std::string, std::string, uint16_t) {
  return Origin();
}
Origin Origin::CreateOpaqueFromNormalizedPrecursorTuple(std::string,
                                                        std::string,
                                                        uint16_t,
                                                        const Nonce& nonce) {
  return Origin(nonce, SchemeHostPort());
}
std::string Origin::Serialize() const {
  return {};
}
bool Origin::IsSameOriginWith(const Origin&) const {
  return true;
}
bool Origin::IsSameOriginWith(const GURL&) const {
  return true;
}
bool Origin::CanBeDerivedFrom(const GURL&) const {
  return true;
}
GURL Origin::GetURL() const {
  return GURL();
}
bool Origin::DomainIs(std::string_view) const {
  return false;
}
Origin Origin::DeriveNewOpaqueOrigin() const {
  return Origin();
}
const base::UnguessableToken* Origin::GetNonceForTesting() const {
  return nullptr;
}
std::string Origin::GetDebugString(bool) const {
  return {};
}
void Origin::WriteIntoTrace(perfetto::TracedValue) const {}
size_t Origin::EstimateMemoryUsage() const {
  return 0;
}
Origin::Origin(SchemeHostPort tuple) : tuple_(std::move(tuple)) {}
Origin::Origin(const Nonce& nonce, SchemeHostPort precursor)
    : tuple_(std::move(precursor)), nonce_(nonce) {}
const base::UnguessableToken* Origin::GetNonceForSerialization() const {
  return nullptr;
}
std::optional<std::string> Origin::SerializeWithNonce() const {
  return std::string();
}
std::optional<std::string> Origin::SerializeWithNonceAndInitIfNeeded() {
  return std::string();
}
std::optional<std::string> Origin::SerializeWithNonceImpl() const {
  return std::string();
}
std::optional<Origin> Origin::Deserialize(std::string_view) {
  return Origin();
}
Origin::Nonce::Nonce() = default;
Origin::Nonce::Nonce(const base::UnguessableToken& token) : token_(token) {}
Origin::Nonce::Nonce(const Nonce&) = default;
Origin::Nonce& Origin::Nonce::operator=(const Nonce&) = default;
Origin::Nonce::Nonce(Nonce&&) noexcept = default;
Origin::Nonce& Origin::Nonce::operator=(Nonce&&) noexcept = default;
const base::UnguessableToken& Origin::Nonce::token() const {
  return token_;
}
const base::UnguessableToken& Origin::Nonce::raw_token() const {
  return token_;
}
std::strong_ordering Origin::Nonce::operator<=>(const Nonce&) const {
  return std::strong_ordering::equal;
}
bool Origin::Nonce::operator==(const Nonce&) const {
  return true;
}
bool IsSameOriginWith(const GURL&, const GURL&) {
  return true;
}
const std::vector<std::string>& GetLocalSchemes() {
  static const std::vector<std::string>* schemes = new std::vector<std::string>();
  return *schemes;
}
const std::vector<std::string>& GetNoAccessSchemes() {
  static const std::vector<std::string>* schemes = new std::vector<std::string>();
  return *schemes;
}
bool AllowNonStandardSchemesForAndroidWebView() {
  return false;
}
bool CanonicalizeSpecialHost(std::string_view,
                             const Component&,
                             CanonOutput&,
                             Component& out_host) {
  out_host = Component();
  return false;
}
bool CanonicalizeSpecialHost(std::u16string_view,
                             const Component&,
                             CanonOutput&,
                             Component& out_host) {
  out_host = Component();
  return false;
}
bool CanonicalizeFileHost(std::string_view,
                          const Component&,
                          CanonOutput&,
                          Component& out_host) {
  out_host = Component();
  return false;
}
bool CanonicalizeFileHost(std::u16string_view,
                          const Component&,
                          CanonOutput&,
                          Component& out_host) {
  out_host = Component();
  return false;
}

}  // namespace url

GURL::GURL() : is_valid_(false) {}
GURL::GURL(const GURL& other)
    : spec_(other.spec_), is_valid_(other.is_valid_), parsed_(other.parsed_) {}
GURL::GURL(GURL&& other) noexcept = default;
GURL::GURL(std::string_view url_string)
    : spec_(url_string), is_valid_(!url_string.empty()) {}
GURL::GURL(std::u16string_view) : is_valid_(false) {}
GURL::GURL(std::string_view canonical_spec,
           const url::Parsed& parsed,
           bool is_valid)
    : spec_(canonical_spec), is_valid_(is_valid), parsed_(parsed) {}
GURL::GURL(std::string canonical_spec,
           const url::Parsed& parsed,
           bool is_valid)
    : spec_(std::move(canonical_spec)), is_valid_(is_valid), parsed_(parsed) {}
GURL::~GURL() = default;
GURL& GURL::operator=(const GURL& other) {
  spec_ = other.spec_;
  is_valid_ = other.is_valid_;
  parsed_ = other.parsed_;
  inner_url_.reset();
  return *this;
}
GURL& GURL::operator=(GURL&& other) noexcept = default;
const std::string& GURL::spec() const {
  return spec_;
}
GURL GURL::Resolve(std::string_view) const {
  return GURL();
}
GURL GURL::Resolve(std::u16string_view) const {
  return GURL();
}
GURL GURL::ReplaceComponents(const Replacements&) const {
  return *this;
}
GURL GURL::ReplaceComponents(const ReplacementsW&) const {
  return *this;
}
GURL GURL::GetWithEmptyPath() const {
  return *this;
}
GURL GURL::GetWithoutFilename() const {
  return *this;
}
GURL GURL::GetWithoutRef() const {
  return *this;
}
GURL GURL::DeprecatedGetOriginAsURL() const {
  return *this;
}
GURL GURL::GetAsReferrer() const {
  return *this;
}
bool GURL::IsStandard() const {
  return true;
}
bool GURL::IsAboutBlank() const {
  return false;
}
bool GURL::IsAboutSrcdoc() const {
  return false;
}
bool GURL::SchemeIs(std::string_view lower_ascii_scheme) const {
  return scheme() == lower_ascii_scheme;
}
bool GURL::SchemeIsHTTPOrHTTPS() const {
  return SchemeIs("http") || SchemeIs("https");
}
bool GURL::SchemeIsWSOrWSS() const {
  return SchemeIs("ws") || SchemeIs("wss");
}
bool GURL::SchemeIsCryptographic() const {
  return SchemeIs("https") || SchemeIs("wss");
}
bool GURL::SchemeIsCryptographic(std::string_view lower_ascii_scheme) {
  return lower_ascii_scheme == "https" || lower_ascii_scheme == "wss";
}
bool GURL::SchemeIsLocal() const {
  return SchemeIs("file") || SchemeIs("about");
}
std::string GURL::GetContent() const {
  return {};
}
std::string_view GURL::GetContentPiece() const {
  return {};
}
bool GURL::HostIsIPAddress() const {
  return false;
}
int GURL::IntPort() const {
  return 0;
}
int GURL::EffectiveIntPort() const {
  return 0;
}
std::string GURL::ExtractFileName() const {
  return {};
}
std::string GURL::PathForRequest() const {
  return {};
}
std::string_view GURL::PathForRequestPiece() const {
  return {};
}
std::string GURL::HostNoBrackets() const {
  return GetHost();
}
std::string_view GURL::HostNoBracketsPiece() const {
  return host();
}
bool GURL::DomainIs(std::string_view) const {
  return false;
}
bool GURL::EqualsIgnoringRef(const GURL& other) const {
  return spec_ == other.spec_;
}
void GURL::Swap(GURL* other) {
  std::swap(*this, *other);
}
const GURL& GURL::EmptyGURL() {
  static const GURL* empty = new GURL();
  return *empty;
}
size_t GURL::EstimateMemoryUsage() const {
  return 0;
}
bool GURL::IsAboutPath(std::string_view, std::string_view) {
  return false;
}
void GURL::WriteIntoTrace(perfetto::TracedValue) const {}
bool operator==(const GURL& x, const GURL& y) {
  return x.possibly_invalid_spec() == y.possibly_invalid_spec();
}
bool operator==(const GURL& x, std::string_view spec) {
  return x.possibly_invalid_spec() == spec;
}

namespace mojo::internal {

PendingReceiverState::PendingReceiverState() = default;
PendingReceiverState::PendingReceiverState(ScopedMessagePipeHandle input_pipe)
    : pipe(std::move(input_pipe)) {}
PendingReceiverState::PendingReceiverState(PendingReceiverState&&) noexcept =
    default;
PendingReceiverState::~PendingReceiverState() = default;
PendingReceiverState& PendingReceiverState::operator=(
    PendingReceiverState&&) noexcept = default;
void PendingReceiverState::reset() {
  pipe.reset();
}

PendingRemoteState::PendingRemoteState() = default;
PendingRemoteState::PendingRemoteState(ScopedMessagePipeHandle input_pipe,
                                       uint32_t input_version)
    : pipe(std::move(input_pipe)), version(input_version) {}
PendingRemoteState::PendingRemoteState(PendingRemoteState&&) noexcept =
    default;
PendingRemoteState::~PendingRemoteState() = default;
PendingRemoteState& PendingRemoteState::operator=(
    PendingRemoteState&&) noexcept = default;
void PendingRemoteState::reset() {
  pipe.reset();
  version = 0;
}

}  // namespace mojo::internal

namespace mojo {

ConnectionGroupRef::ConnectionGroupRef() = default;
ConnectionGroupRef::ConnectionGroupRef(const ConnectionGroupRef&) = default;
ConnectionGroupRef::ConnectionGroupRef(ConnectionGroupRef&&) noexcept = default;
ConnectionGroupRef::~ConnectionGroupRef() = default;
ConnectionGroupRef& ConnectionGroupRef::operator=(const ConnectionGroupRef&) =
    default;
ConnectionGroupRef& ConnectionGroupRef::operator=(ConnectionGroupRef&&) noexcept =
    default;
void ConnectionGroupRef::reset() {
  group_.reset();
}
ConnectionGroupRef ConnectionGroupRef::WeakCopy() const {
  return ConnectionGroupRef();
}
bool ConnectionGroupRef::HasZeroRefs() const {
  return true;
}
void ConnectionGroupRef::SetParentGroup(ConnectionGroupRef) {}
ConnectionGroupRef::ConnectionGroupRef(scoped_refptr<ConnectionGroup> group)
    : type_(Type::kStrong), group_(std::move(group)) {}

}  // namespace mojo

namespace blink::features {

BASE_FEATURE(kRenderBlockingFonts,
             "RenderBlockingFonts",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(int,
                   kMaxBlockingTimeMsForRenderBlockingFonts,
                   &kRenderBlockingFonts,
                   "max_blocking_time_ms",
                   0);
BASE_FEATURE(kPaintHolding,
             "PaintHolding",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kThreadedBodyLoader,
             "ThreadedBodyLoader",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kServiceWorkerSyntheticResponse,
             "ServiceWorkerSyntheticResponse",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE_PARAM(bool,
                   kServiceWorkerSyntheticResponseDryRun,
                   &kServiceWorkerSyntheticResponse,
                   "dry_run",
                   false);
BASE_FEATURE(kStreamlineRendererInit,
             "StreamlineRendererInit",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kPartitionVisitedLinkDatabaseWithSelfLinks,
             "PartitionVisitedLinkDatabaseWithSelfLinks",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kUseSandboxTokenForOriginDerivation,
             "UseSandboxTokenForOriginDerivation",
             base::FEATURE_DISABLED_BY_DEFAULT);
BASE_FEATURE(kIsolateSandboxedIframes,
             "IsolateSandboxedIframes",
             base::FEATURE_DISABLED_BY_DEFAULT);

}  // namespace blink::features

namespace blink::FencedFrame {

RedactedFencedFrameConfig::RedactedFencedFrameConfig() = default;
RedactedFencedFrameConfig::~RedactedFencedFrameConfig() = default;
RedactedFencedFrameProperties::RedactedFencedFrameProperties() = default;
RedactedFencedFrameProperties::~RedactedFencedFrameProperties() = default;

}  // namespace blink::FencedFrame

namespace blink {

bool EnabledClientHints::IsEnabled(
    network::mojom::WebClientHintsType type) const {
  int index = static_cast<int>(type);
  if (index < 0 || index >= static_cast<int>(enabled_types_.size())) {
    return false;
  }
  return enabled_types_[index];
}

void EnabledClientHints::SetIsEnabled(network::mojom::WebClientHintsType type,
                                      bool should_send) {
  int index = static_cast<int>(type);
  if (index < 0 || index >= static_cast<int>(enabled_types_.size())) {
    return;
  }
  enabled_types_[index] = should_send;
}

std::vector<network::mojom::WebClientHintsType>
EnabledClientHints::GetEnabledHints() const {
  std::vector<network::mojom::WebClientHintsType> hints;
  for (int i = 0; i < static_cast<int>(enabled_types_.size()); ++i) {
    if (enabled_types_[i]) {
      hints.push_back(static_cast<network::mojom::WebClientHintsType>(i));
    }
  }
  return hints;
}

ClientHintsPreferences::ClientHintsPreferences() = default;
void ClientHintsPreferences::UpdateFrom(const ClientHintsPreferences& other) {
  enabled_hints_ = other.enabled_hints_;
}
void ClientHintsPreferences::CombineWith(const ClientHintsPreferences& other) {
  for (auto hint : other.enabled_hints_.GetEnabledHints()) {
    enabled_hints_.SetIsEnabled(hint, true);
  }
}
bool ClientHintsPreferences::UpdateFromMetaCH(const String&,
                                              const KURL&,
                                              Context*,
                                              network::MetaCHType,
                                              bool,
                                              bool) {
  return false;
}
bool ClientHintsPreferences::ShouldSend(
    network::mojom::WebClientHintsType type) const {
  return enabled_hints_.IsEnabled(type);
}
void ClientHintsPreferences::SetShouldSend(
    network::mojom::WebClientHintsType type) {
  enabled_hints_.SetIsEnabled(type, true);
}
bool ClientHintsPreferences::IsClientHintsAllowed(const KURL&) {
  return false;
}
EnabledClientHints ClientHintsPreferences::GetEnabledClientHints() const {
  return enabled_hints_;
}

FrameClientHintsPreferencesContext::FrameClientHintsPreferencesContext(
    LocalFrame* frame)
    : frame_(frame) {}
ukm::SourceId FrameClientHintsPreferencesContext::GetUkmSourceId() {
  return ukm::kInvalidSourceId;
}
ukm::UkmRecorder* FrameClientHintsPreferencesContext::GetUkmRecorder() {
  return nullptr;
}
void FrameClientHintsPreferencesContext::CountClientHints(
    network::mojom::WebClientHintsType) {}

OriginTrialTokenResult::OriginTrialTokenResult(
    const String& raw_token,
    OriginTrialTokenStatus status,
    const std::optional<TrialToken>& parsed_token)
    : raw_token(raw_token), status(status), parsed_token(parsed_token) {}
TrialToken::~TrialToken() = default;

OriginTrialContext::OriginTrialContext(ExecutionContext* context)
    : context_(context) {}
void OriginTrialContext::SetTrialTokenValidatorForTesting(
    std::unique_ptr<TrialTokenValidator>) {}
std::unique_ptr<Vector<String>> OriginTrialContext::ParseHeaderValue(
    const String&) {
  return std::make_unique<Vector<String>>();
}
void OriginTrialContext::AddTokensFromHeader(ExecutionContext*,
                                             const String&) {}
void OriginTrialContext::AddTokens(ExecutionContext*, const Vector<String>*) {}
std::unique_ptr<Vector<String>> OriginTrialContext::GetTokens(
    ExecutionContext*) {
  return nullptr;
}
std::unique_ptr<Vector<mojom::blink::OriginTrialFeature>>
OriginTrialContext::GetInheritedTrialFeatures(ExecutionContext*) {
  return nullptr;
}
std::unique_ptr<Vector<mojom::blink::OriginTrialFeature>>
OriginTrialContext::GetEnabledNavigationFeatures(ExecutionContext*) {
  return nullptr;
}
void OriginTrialContext::ActivateWorkerInheritedFeatures(
    ExecutionContext*,
    const Vector<mojom::blink::OriginTrialFeature>*) {}
void OriginTrialContext::ActivateNavigationFeaturesFromInitiator(
    ExecutionContext*,
    const Vector<mojom::blink::OriginTrialFeature>*) {}
void OriginTrialContext::AddToken(const String&) {}
void OriginTrialContext::AddTokenFromExternalScript(
    const String&,
    const Vector<scoped_refptr<SecurityOrigin>>&) {}
void OriginTrialContext::AddTokens(const Vector<String>&) {}
void OriginTrialContext::ActivateWorkerInheritedFeatures(
    const Vector<mojom::blink::OriginTrialFeature>&) {}
void OriginTrialContext::ActivateNavigationFeaturesFromInitiator(
    const Vector<mojom::blink::OriginTrialFeature>&) {}
void OriginTrialContext::AddFeature(mojom::blink::OriginTrialFeature feature) {
  enabled_features_.insert(feature);
}
void OriginTrialContext::AddForceEnabledTrials(const Vector<String>&) {}
bool OriginTrialContext::IsFeatureEnabled(
    mojom::blink::OriginTrialFeature feature) const {
  return enabled_features_.Contains(feature);
}
base::Time OriginTrialContext::GetFeatureExpiry(
    mojom::blink::OriginTrialFeature) {
  return base::Time();
}
std::unique_ptr<Vector<mojom::blink::OriginTrialFeature>>
OriginTrialContext::GetInheritedTrialFeatures() const {
  return nullptr;
}
std::unique_ptr<Vector<mojom::blink::OriginTrialFeature>>
OriginTrialContext::GetEnabledNavigationFeatures() const {
  return nullptr;
}
bool OriginTrialContext::IsNavigationFeatureActivated(
    const mojom::blink::OriginTrialFeature feature) const {
  return navigation_activated_features_.Contains(feature);
}
void OriginTrialContext::InitializePendingFeatures() {}
void OriginTrialContext::Trace(Visitor* visitor) const {
  visitor->Trace(context_);
}

void SpeculationRulesHeader::ProcessHeadersForDocumentResponse(
    const ResourceResponse&,
    LocalDOMWindow&) {}

const char DocumentXSLT::kSupplementName[] = "DocumentXSLT";
void DocumentXSLT::SetHasTransformSource(Document&) {}
void DocumentXSLT::ApplyXSLTransform(Document&, ProcessingInstruction*) {}
ProcessingInstruction* DocumentXSLT::FindXSLStyleSheet(Document&) {
  return nullptr;
}
bool DocumentXSLT::ProcessingInstructionInsertedIntoDocument(
    Document&,
    ProcessingInstruction*) {
  return false;
}
bool DocumentXSLT::ProcessingInstructionRemovedFromDocument(
    Document&,
    ProcessingInstruction*) {
  return false;
}
bool DocumentXSLT::SheetLoaded(Document&, ProcessingInstruction*) {
  return false;
}
bool DocumentXSLT::HasTransformSourceDocument(Document&) {
  return false;
}
DocumentXSLT::DocumentXSLT(Document& document)
    : Supplement<Document>(document) {}
void DocumentXSLT::Trace(Visitor* visitor) const {
  Supplement<Document>::Trace(visitor);
}

#if DCHECK_IS_ON()
bool DisplayLockUtilities::AssertStyleAllowed(const Node&) {
  return true;
}
#endif
bool DisplayLockUtilities::IsPotentialStyleRecalcRoot(const Node&) {
  return false;
}
namespace http_names {
const AtomicString& kContentEncoding = *new AtomicString("content-encoding");
const AtomicString& kOriginTrial = *new AtomicString("origin-trial");
const AtomicString& kReferrerPolicy = *new AtomicString("referrer-policy");
const AtomicString& kFeaturePolicy = *new AtomicString("feature-policy");
const AtomicString& kPermissionsPolicy = *new AtomicString("permissions-policy");
const AtomicString& kDocumentPolicyReportOnly =
    *new AtomicString("document-policy-report-only");
const AtomicString& kRefresh = *new AtomicString("refresh");
const AtomicString& kXDNSPrefetchControl =
    *new AtomicString("x-dns-prefetch-control");
const AtomicString& kContentLanguage = *new AtomicString("content-language");
const AtomicString& kReportTo = *new AtomicString("report-to");
const AtomicString& kReportingEndpoints =
    *new AtomicString("reporting-endpoints");
const AtomicString& kNoVarySearch = *new AtomicString("no-vary-search");
const AtomicString& kRequestOTR = *new AtomicString("request-otr");
const AtomicString& kSecSessionRegistration =
    *new AtomicString("sec-session-registration");
const AtomicString& kSecureSessionRegistration =
    *new AtomicString("secure-session-registration");
}  // namespace http_names

KURL::KURL(const AtomicString& canonical_string,
           const url::Parsed& parsed,
           bool is_valid)
    : is_valid_(is_valid),
      protocol_is_in_http_family_(false),
      parsed_(parsed),
      string_(canonical_string) {}

bool KURL::IsStandard() const {
  return true;
}
uint16_t KURL::Port() const {
  return 0;
}
bool KURL::HasPort() const {
  return false;
}
bool KURL::HasFragmentIdentifier() const {
  return false;
}
StringView KURL::GetPath() const {
  return StringView();
}
std::ostream& operator<<(std::ostream& ostream, const KURL& url) {
  return ostream << url.GetString().Utf8();
}
uint16_t DefaultPortForProtocol(const String& protocol) {
  if (protocol == "http") {
    return 80;
  }
  if (protocol == "https") {
    return 443;
  }
  return 0;
}

KURL BlobURL::CreatePublicURL(const SecurityOrigin*) {
  return KURL();
}
String BlobURL::GetOrigin(const KURL&) {
  return String();
}
ThreadSpecific<BlobURLNullOriginMap>& BlobURLNullOriginMap::GetInstance() {
  static ThreadSpecific<BlobURLNullOriginMap>* instance =
      new ThreadSpecific<BlobURLNullOriginMap>();
  return *instance;
}
void BlobURLNullOriginMap::Add(const KURL&, SecurityOrigin*) {}
void BlobURLNullOriginMap::Remove(const KURL&) {}
SecurityOrigin* BlobURLNullOriginMap::Get(const KURL&) {
  return nullptr;
}
BlobURLOpaqueOriginNonceMap& BlobURLOpaqueOriginNonceMap::GetInstance() {
  static BlobURLOpaqueOriginNonceMap* instance =
      new BlobURLOpaqueOriginNonceMap();
  return *instance;
}
base::UnguessableToken BlobURLOpaqueOriginNonceMap::Get(const KURL&) {
  return base::UnguessableToken();
}

bool SecurityPolicy::IsOriginAccessAllowed(const SecurityOrigin*,
                                           const SecurityOrigin*) {
  return true;
}
bool SecurityPolicy::IsOriginAccessToURLAllowed(const SecurityOrigin*,
                                                const KURL&) {
  return true;
}
bool SecurityPolicy::ReferrerPolicyFromString(
    const StringView&,
    ReferrerPolicyLegacyKeywordsSupport,
    network::mojom::ReferrerPolicy*) {
  return false;
}
bool SecurityPolicy::ReferrerPolicyFromHeaderValue(
    const String&,
    ReferrerPolicyLegacyKeywordsSupport,
    network::mojom::ReferrerPolicy*) {
  return false;
}
String SecurityPolicy::ReferrerPolicyAsString(
    network::mojom::ReferrerPolicy) {
  return String();
}

bool SchemeRegistry::CanDisplayOnlyIfCanRequest(const String&) {
  return false;
}
bool SchemeRegistry::ShouldTreatURLSchemeAsDisplayIsolated(const String&) {
  return false;
}

void ExecutionContext::SetContentSecurityPolicy(
    ContentSecurityPolicy* content_security_policy) {
  content_security_policy_ = content_security_policy;
}
void ExecutionContext::ParseAndSetReferrerPolicy(const String&,
                                                 ReferrerPolicySource) {}
void ExecutionContext::SetPolicyContainer(
    std::unique_ptr<PolicyContainer> container) {
  policy_container_ = std::move(container);
}
std::unique_ptr<PolicyContainer> ExecutionContext::TakePolicyContainer() {
  return std::move(policy_container_);
}
bool ExecutionContext::IsFeatureEnabled(
    mojom::blink::DocumentPolicyFeature,
    ReportOptions,
    const String&,
    const String&) {
  return true;
}

Vector<network::mojom::blink::ContentSecurityPolicyPtr>
ParseContentSecurityPolicies(
    const String&,
    network::mojom::blink::ContentSecurityPolicyType,
    network::mojom::blink::ContentSecurityPolicySource,
    const KURL&) {
  return {};
}

void RuntimeFeatureStateOverrideContext::ApplyOverrideValuesFromParams(
    const base::flat_map<mojom::RuntimeFeature, bool>& values_from_params) {
  for (const auto& override_value : values_from_params) {
    override_values_[override_value.first] = override_value.second;
  }
}

void UserActivationState::SetHasBeenActive() {
  has_been_active_ = true;
}
void UserActivationState::Clear() {
  has_been_active_ = false;
  last_activation_was_restricted_ = false;
}

bool RuntimeEnabledFeaturesBase::
    is_resource_timing_use_cors_for_body_sizes_enabled_ = false;

class TaskHandle::Runner {
 public:
  void AddRef() const {}
  void Release() const {}
};
TaskHandle::TaskHandle() = default;
TaskHandle::~TaskHandle() = default;
TaskHandle::TaskHandle(TaskHandle&&) = default;
TaskHandle& TaskHandle::operator=(TaskHandle&&) = default;
bool TaskHandle::IsActive() const {
  return false;
}
void TaskHandle::Cancel() {}
TaskHandle PostDelayedCancellableTask(base::SequencedTaskRunner&,
                                      const base::Location&,
                                      base::OnceClosure,
                                      base::TimeDelta) {
  return TaskHandle();
}

uint64_t CreateUniqueIdentifier() {
  static uint64_t next_identifier = 1;
  return next_identifier++;
}

WebScopedVirtualTimePauser::WebScopedVirtualTimePauser() = default;
WebScopedVirtualTimePauser::WebScopedVirtualTimePauser(
    scheduler::ThreadSchedulerBase* scheduler,
    VirtualTaskDuration duration,
    const WebString& debug_name)
    : duration_(duration), scheduler_(scheduler), debug_name_(debug_name),
      trace_id_(0) {}
WebScopedVirtualTimePauser::~WebScopedVirtualTimePauser() = default;
WebScopedVirtualTimePauser::WebScopedVirtualTimePauser(
    WebScopedVirtualTimePauser&& other) = default;
WebScopedVirtualTimePauser& WebScopedVirtualTimePauser::operator=(
    WebScopedVirtualTimePauser&& other) = default;
void WebScopedVirtualTimePauser::PauseVirtualTime() {
  paused_ = true;
}
void WebScopedVirtualTimePauser::UnpauseVirtualTime() {
  paused_ = false;
}
void WebScopedVirtualTimePauser::DecrementVirtualTimePauseCount() {
  paused_ = false;
}

void ProgressTracker::WillStartLoading(uint64_t, ResourceLoadPriority) {}
void ProgressTracker::IncrementProgress(uint64_t, const ResourceResponse&) {}
void ProgressTracker::IncrementProgress(uint64_t, uint64_t) {}
void ProgressTracker::CompleteProgress(uint64_t) {}

void DocumentLoadTiming::MarkNavigationStart() {}
void DocumentLoadTiming::SetResponseEnd(base::TimeTicks) {}
void DocumentLoadTiming::AddRedirect(const KURL&, const KURL&) {}

void FrameConsole::DidFailLoading(DocumentLoader*, uint64_t,
                                  const ResourceError&) {}
void WindowPerformance::OnBodyLoadFinished(int64_t, int64_t) {}
NavigationApi::DispatchResult NavigationApi::DispatchNavigateEvent(
    NavigateEventDispatchParams*) {
  return DispatchResult::kContinue;
}
void FrameLoader::SaveScrollState() {}
void FrameLoader::ProcessScrollForSameDocumentNavigation(
    const KURL&,
    WebFrameLoadType,
    std::optional<HistoryItem::ViewState>,
    mojom::blink::ScrollRestorationType,
    mojom::blink::ScrollBehavior) {}
void FrameLoader::DispatchDidClearDocumentOfWindowObject() {}
void EventHandler::StopAutoscroll() {}
void ResourceFetcher::StopFetching() {}
void ScriptController::UpdateDocument() {}
void DocumentEncodingData::SetEncoding(const TextEncoding&) {}
DOMWindow* DOMWindow::parent() const {
  return const_cast<DOMWindow*>(this);
}

class BlobDataHandle {
 public:
  void AddRef() const {}
  void Release() const {}
};
class WrappedDataPipeGetter {
 public:
  void AddRef() const {}
  void Release() const {}
};
FormDataElement::FormDataElement()
    : type_(kData), file_start_(0), file_length_(0) {}
FormDataElement::FormDataElement(const Vector<char>& data)
    : type_(kData), data_(data), file_start_(0), file_length_(0) {}
FormDataElement::FormDataElement(Vector<char>&& data)
    : type_(kData),
      data_(std::move(data)),
      file_start_(0),
      file_length_(0) {}
FormDataElement::FormDataElement(
    const String& filename,
    int64_t file_start,
    int64_t file_length,
    const std::optional<base::Time>& expected_file_modification_time)
    : type_(kEncodedFile),
      filename_(filename),
      file_start_(file_start),
      file_length_(file_length),
      expected_file_modification_time_(expected_file_modification_time) {}
FormDataElement::FormDataElement(scoped_refptr<BlobDataHandle>)
    : type_(kEncodedBlob), file_start_(0), file_length_(0) {}
FormDataElement::FormDataElement(scoped_refptr<WrappedDataPipeGetter>)
    : type_(kDataPipe), file_start_(0), file_length_(0) {}
FormDataElement::FormDataElement(const FormDataElement& other)
    : type_(other.type_),
      data_(other.data_),
      filename_(other.filename_),
      file_start_(other.file_start_),
      file_length_(other.file_length_),
      expected_file_modification_time_(other.expected_file_modification_time_) {}
FormDataElement::FormDataElement(FormDataElement&&) = default;
FormDataElement::~FormDataElement() = default;
FormDataElement& FormDataElement::operator=(const FormDataElement& other) {
  type_ = other.type_;
  data_ = other.data_;
  filename_ = other.filename_;
  blob_data_handle_ = nullptr;
  file_start_ = other.file_start_;
  file_length_ = other.file_length_;
  expected_file_modification_time_ = other.expected_file_modification_time_;
  data_pipe_getter_ = nullptr;
  return *this;
}
FormDataElement& FormDataElement::operator=(FormDataElement&&) = default;
bool operator==(const FormDataElement& a, const FormDataElement& b) {
  return a.type_ == b.type_ && a.data_ == b.data_ && a.filename_ == b.filename_;
}
scoped_refptr<EncodedFormData> EncodedFormData::Create() {
  return base::AdoptRef(new EncodedFormData());
}
scoped_refptr<EncodedFormData> EncodedFormData::Create(
    base::span<const uint8_t> data) {
  scoped_refptr<EncodedFormData> form_data = Create();
  form_data->AppendData(data);
  return form_data;
}
scoped_refptr<EncodedFormData> EncodedFormData::Create(SegmentedBuffer&&) {
  return Create();
}
EncodedFormData::EncodedFormData()
    : identifier_(0), contains_password_data_(false) {}
EncodedFormData::EncodedFormData(const EncodedFormData& other)
    : elements_(other.elements_),
      identifier_(other.identifier_),
      boundary_(other.boundary_),
      contains_password_data_(other.contains_password_data_) {}
EncodedFormData::~EncodedFormData() = default;
scoped_refptr<EncodedFormData> EncodedFormData::Copy() const {
  return base::AdoptRef(new EncodedFormData(*this));
}
scoped_refptr<EncodedFormData> EncodedFormData::DeepCopy() const {
  return Copy();
}
void EncodedFormData::AppendData(base::span<const uint8_t> data) {
  Vector<char> bytes;
  bytes.Append(reinterpret_cast<const char*>(data.data()), data.size());
  elements_.emplace_back(std::move(bytes));
}
void EncodedFormData::AppendData(SegmentedBuffer&&) {}
void EncodedFormData::AppendFile(const String&,
                                 const std::optional<base::Time>&) {}
void EncodedFormData::AppendFileRange(const String&,
                                      int64_t,
                                      int64_t,
                                      const std::optional<base::Time>&) {}
void EncodedFormData::AppendBlob(scoped_refptr<BlobDataHandle>) {}
void EncodedFormData::AppendDataPipe(scoped_refptr<WrappedDataPipeGetter>) {}
void EncodedFormData::Flatten(Vector<char>& data) const {
  for (const auto& element : elements_) {
    data.Append(element.data_.data(), element.data_.size());
  }
}
String EncodedFormData::FlattenToString() const {
  Vector<char> data;
  Flatten(data);
  return data.empty() ? String()
                      : String(base::span<const char>(data.data(), data.size()));
}
String EncodedFormData::FormatContentTypeWithBoundary() const {
  return String("multipart/form-data");
}
uint64_t EncodedFormData::SizeInBytes() const {
  uint64_t size = 0;
  for (const auto& element : elements_) {
    size += element.data_.size();
  }
  return size;
}
bool EncodedFormData::IsSafeToSendToAnotherThread() const {
  return false;
}

void ViewTransitionSupplement::CreateFromSnapshotForNavigation(
    Document&,
    ViewTransitionState) {}
void IdlenessDetector::WillCommitLoad() {}
void InteractiveDetector::SetNavigationStartTime(base::TimeTicks) {}
ScopedOldDocumentInfoForCommitCapturer*
    ScopedOldDocumentInfoForCommitCapturer::current_capturer_ = nullptr;
base::TimeDelta FontPerformance::primary_font_;
base::TimeDelta FontPerformance::primary_font_in_style_;
base::TimeDelta FontPerformance::system_fallback_;

namespace {
const WrapperTypeInfo& StandaloneHTMLHeadElementWrapperTypeInfo() {
  static const WrapperTypeInfo info{
      {0},
      nullptr,
      nullptr,
      "HTMLHeadElement",
      nullptr,
      v8::CppHeapPointerTag{},
      v8::CppHeapPointerTag{},
      WrapperTypeInfo::kWrapperTypeObjectPrototype,
      WrapperTypeInfo::kNodeClassId,
      WrapperTypeInfo::kIdlInterface,
      false};
  return info;
}
}  // namespace
const WrapperTypeInfo& HTMLHeadElement::wrapper_type_info_ =
    StandaloneHTMLHeadElementWrapperTypeInfo();

void VisitedLinkState::UpdateSalt(uint64_t) {}
void NavigationApi::InitializeForNewWindow(
    HistoryItem&,
    WebFrameLoadType,
    CommitReason,
    NavigationApi*,
    const std::vector<WebHistoryItem>&,
    const std::vector<WebHistoryItem>&,
    HistoryItem*) {}
void WindowPerformance::CreateNavigationTimingInstance(
    mojom::blink::ResourceTimingInfoPtr) {}
void ProfilerGroup::InitializeIfEnabled(ExecutionContext*) {}
void FrameConsole::ReportResourceResponseReceived(DocumentLoader*,
                                                  uint64_t,
                                                  const ResourceResponse&) {}
FocusController::FocusController(Page* page)
    : page_(page),
      is_active_(true),
      is_focused_(true),
      is_changing_focused_frame_(false),
      is_emulating_focus_(false) {}
const ContainerNode* FocusController::ReadingFlowContainerOrDisplayContents(
    const ContainerNode*,
    bool) {
  return nullptr;
}
void FocusController::SetFocusedFrame(Frame* frame, bool) {
  focused_frame_ = frame;
}
void FocusController::FocusDocumentView(Frame* frame, bool) {
  focused_frame_ = frame;
}
LocalFrame* FocusController::FocusedFrame() const {
  return DynamicTo<LocalFrame>(focused_frame_.Get());
}
Frame* FocusController::FocusedOrMainFrame() const {
  return focused_frame_.Get();
}
void FocusController::FrameDetached(Frame* detached_frame) {
  if (focused_frame_ == detached_frame) {
    focused_frame_ = nullptr;
  }
}
HTMLFrameOwnerElement* FocusController::FocusedFrameOwnerElement(
    LocalFrame&) const {
  return nullptr;
}
bool FocusController::IsDocumentFocused(const Document&) const {
  return IsFocused();
}
bool FocusController::SetInitialFocus(mojom::blink::FocusType) {
  return false;
}
bool FocusController::AdvanceFocusAcrossFrames(mojom::blink::FocusType,
                                               RemoteFrame*,
                                               LocalFrame*,
                                               InputDeviceCapabilities*) {
  return false;
}
Element* FocusController::FindScopeOwnerSlotOrScrollMarkerOrReadingFlowContainer(
    const Element&) {
  return nullptr;
}
Element* FocusController::NextFocusableElementForIme(
    Element*,
    mojom::blink::FocusType) {
  return nullptr;
}
Element* FocusController::FindFocusableElementForImeAutofillAndTesting(
    mojom::blink::FocusType,
    Element&,
    OwnerMap&) {
  return nullptr;
}
bool FocusController::SetFocusedElement(Element*, Frame* frame,
                                        const FocusParams&) {
  focused_frame_ = frame;
  return true;
}
bool FocusController::SetFocusedElement(Element*, Frame* frame) {
  focused_frame_ = frame;
  return true;
}
void FocusController::SetActive(bool active) {
  is_active_ = active;
}
void FocusController::SetFocused(bool focused) {
  is_focused_ = focused;
}
void FocusController::SetFocusEmulationEnabled(bool enabled) {
  is_emulating_focus_ = enabled;
}
void FocusController::UpdateFocusOnNavigationCommit(Frame* frame, bool) {
  focused_frame_ = frame;
}
void FocusController::RegisterFocusChangedObserver(FocusChangedObserver*) {}
int FocusController::AdjustedTabIndex(const Element&) {
  return 0;
}
bool FocusController::AdvanceFocus(mojom::blink::FocusType,
                                   bool,
                                   InputDeviceCapabilities*) {
  return false;
}
bool FocusController::AdvanceFocusInDocumentOrder(LocalFrame*,
                                                  Element*,
                                                  mojom::blink::FocusType,
                                                  bool,
                                                  InputDeviceCapabilities*) {
  return false;
}
void FocusController::NotifyFocusChangedObservers() const {}
void FocusController::ActiveHasChanged() {}
void FocusController::FocusHasChanged() {}
void FocusController::Trace(Visitor* visitor) const {
  visitor->Trace(focused_frame_);
}
FrameTree::FrameTree(Frame* frame)
    : this_frame_(frame),
      scoped_child_count_(0),
      experimental_set_nulled_name_(false),
      cross_site_cross_browsing_context_group_set_nulled_name_(false) {}
FrameTree::~FrameTree() = default;
const AtomicString& FrameTree::GetName() const {
  return name_;
}
void FrameTree::CrossSiteCrossBrowsingContextGroupSetNulledName() {
  cross_site_cross_browsing_context_group_set_nulled_name_ = true;
}
void FrameTree::SetName(const AtomicString& name, ReplicationPolicy) {
  name_ = name;
}
void FrameTree::ExperimentalSetNulledName() {
  experimental_set_nulled_name_ = true;
}
Frame* FrameTree::Parent() const {
  return nullptr;
}
Frame& FrameTree::Top() const {
  return *this_frame_;
}
Frame* FrameTree::NextSibling() const {
  return nullptr;
}
Frame* FrameTree::FirstChild() const {
  return nullptr;
}
bool FrameTree::IsDescendantOf(const Frame*) const {
  return false;
}
Frame* FrameTree::TraverseNext(const Frame*) const {
  return nullptr;
}
Frame* FrameTree::FindFrameByName(const AtomicString&) const {
  return nullptr;
}
FrameTree::FindResult FrameTree::FindOrCreateFrameForNavigation(
    FrameLoadRequest&,
    const AtomicString&) const {
  return FindResult(nullptr, false);
}
unsigned FrameTree::ChildCount() const {
  return 0;
}
Frame* FrameTree::ScopedChild(unsigned) const {
  return nullptr;
}
Frame* FrameTree::ScopedChild(const AtomicString&) const {
  return nullptr;
}
unsigned FrameTree::ScopedChildCount() const {
  return 0;
}
void FrameTree::InvalidateScopedChildCount() {
  scoped_child_count_ = 0;
}
Frame* FrameTree::FindFrameForNavigationInternal(
    const AtomicString&,
    const KURL&,
    FrameLoadRequest*) const {
  return nullptr;
}
void FrameTree::Trace(Visitor* visitor) const {
  visitor->Trace(this_frame_);
}
WindowAgentFactory::WindowAgentFactory(AgentGroupScheduler& scheduler)
    : agent_group_scheduler_(&scheduler) {}
WindowAgent* WindowAgentFactory::GetAgentForAgentClusterKey(
    bool,
    const AgentClusterKey&) {
  return nullptr;
}
void WindowAgentFactory::Trace(Visitor* visitor) const {
}
BlinkSchemefulSite::BlinkSchemefulSite()
    : site_as_origin_(SecurityOrigin::CreateUniqueOpaque()) {}
BlinkSchemefulSite::BlinkSchemefulSite(scoped_refptr<const SecurityOrigin> origin)
    : site_as_origin_(std::move(origin)) {}
BlinkSchemefulSite::BlinkSchemefulSite(const url::Origin&)
    : site_as_origin_(SecurityOrigin::CreateUniqueOpaque()) {}
BlinkSchemefulSite::BlinkSchemefulSite(const net::SchemefulSite&)
    : site_as_origin_(SecurityOrigin::CreateUniqueOpaque()) {}
BlinkSchemefulSite::operator net::SchemefulSite() const {
  return net::SchemefulSite();
}
String BlinkSchemefulSite::Serialize() const {
  return site_as_origin_ ? site_as_origin_->ToString() : String("null");
}
String BlinkSchemefulSite::GetDebugString() const {
  return Serialize();
}
bool BlinkSchemefulSite::FromWire(const url::Origin&, BlinkSchemefulSite* out) {
  if (out) {
    *out = BlinkSchemefulSite();
  }
  return true;
}
BlinkStorageKey::BlinkStorageKey()
    : origin_(SecurityOrigin::CreateUniqueOpaque()),
      top_level_site_(origin_),
      top_level_site_if_third_party_enabled_(top_level_site_),
      ancestor_chain_bit_(mojom::blink::AncestorChainBit::kSameSite),
      ancestor_chain_bit_if_third_party_enabled_(
          mojom::blink::AncestorChainBit::kSameSite) {}
BlinkStorageKey::BlinkStorageKey(scoped_refptr<const SecurityOrigin> origin,
                                 const BlinkSchemefulSite& top_level_site,
                                 const base::UnguessableToken* nonce,
                                 mojom::blink::AncestorChainBit ancestor_chain)
    : origin_(std::move(origin)),
      top_level_site_(top_level_site),
      top_level_site_if_third_party_enabled_(top_level_site),
      ancestor_chain_bit_(ancestor_chain),
      ancestor_chain_bit_if_third_party_enabled_(ancestor_chain) {
  if (nonce) {
    nonce_ = *nonce;
  }
}
BlinkStorageKey BlinkStorageKey::CreateFirstParty(
    scoped_refptr<const SecurityOrigin> origin) {
  return BlinkStorageKey(origin, BlinkSchemefulSite(origin), nullptr,
                         mojom::blink::AncestorChainBit::kSameSite);
}
BlinkStorageKey BlinkStorageKey::CreateWithNonce(
    scoped_refptr<const SecurityOrigin> origin,
    const base::UnguessableToken& nonce) {
  return BlinkStorageKey(origin, BlinkSchemefulSite(origin), &nonce,
                         mojom::blink::AncestorChainBit::kCrossSite);
}
BlinkStorageKey BlinkStorageKey::Create(
    scoped_refptr<const SecurityOrigin> origin,
    const BlinkSchemefulSite& top_level_site,
    mojom::blink::AncestorChainBit ancestor_chain_bit) {
  return BlinkStorageKey(std::move(origin), top_level_site, nullptr,
                         ancestor_chain_bit);
}
BlinkStorageKey BlinkStorageKey::CreateFromStringForTesting(
    const String&) {
  return BlinkStorageKey();
}
BlinkStorageKey BlinkStorageKey::WithOrigin(
    scoped_refptr<const SecurityOrigin> origin) const {
  BlinkStorageKey copy = *this;
  copy.origin_ = std::move(origin);
  return copy;
}
BlinkStorageKey::BlinkStorageKey(const StorageKey&) : BlinkStorageKey() {}
BlinkStorageKey::operator StorageKey() const {
  return StorageKey();
}
bool BlinkStorageKey::FromWire(
    scoped_refptr<const SecurityOrigin> origin,
    const BlinkSchemefulSite& top_level_site,
    const BlinkSchemefulSite& top_level_site_if_third_party_enabled,
    const std::optional<base::UnguessableToken>& nonce,
    mojom::blink::AncestorChainBit ancestor_chain_bit,
    mojom::blink::AncestorChainBit ancestor_chain_bit_if_third_party_enabled,
    BlinkStorageKey& out) {
  out = BlinkStorageKey(std::move(origin), top_level_site,
                        nonce ? &*nonce : nullptr, ancestor_chain_bit);
  out.top_level_site_if_third_party_enabled_ =
      top_level_site_if_third_party_enabled;
  out.ancestor_chain_bit_if_third_party_enabled_ =
      ancestor_chain_bit_if_third_party_enabled;
  return true;
}
String BlinkStorageKey::ToDebugString() const {
  return origin_ ? origin_->ToString() : String("null");
}
bool BlinkStorageKey::ExactMatchForTesting(const BlinkStorageKey& other) const {
  return origin_ && other.origin_ &&
         origin_->IsSameOriginWith(other.origin_.get());
}
bool BlinkStorageKey::IsValid() const {
  return !!origin_;
}
std::ostream& operator<<(std::ostream& ostream, const BlinkStorageKey& sk) {
  return ostream << sk.ToDebugString().Utf8();
}
ConsoleMessage::ConsoleMessage(Source source,
                               Level level,
                               const String& message,
                               const String&,
                               DocumentLoader*,
                               uint64_t)
    : source_(source), level_(level), message_(message), timestamp_(0.0) {}
ConsoleMessage::ConsoleMessage(Level level,
                               const String& message,
                               SourceLocation* source_location,
                               WorkerThread*)
    : source_(Source::kWorker),
      level_(level),
      message_(message),
      location_(source_location),
      timestamp_(0.0) {}
ConsoleMessage::ConsoleMessage(const WebConsoleMessage&, LocalFrame*)
    : source_(Source::kOther), level_(Level::kInfo), timestamp_(0.0) {}
ConsoleMessage::ConsoleMessage(Source source,
                               Level level,
                               const String& message,
                               SourceLocation* source_location)
    : source_(source),
      level_(level),
      message_(message),
      location_(source_location),
      timestamp_(0.0) {}
ConsoleMessage::~ConsoleMessage() = default;
SourceLocation* ConsoleMessage::Location() const {
  return location_.Get();
}
const String& ConsoleMessage::RequestIdentifier() const {
  return request_identifier_;
}
double ConsoleMessage::Timestamp() const {
  return timestamp_;
}
ConsoleMessage::Source ConsoleMessage::GetSource() const {
  return source_;
}
ConsoleMessage::Level ConsoleMessage::GetLevel() const {
  return level_;
}
const String& ConsoleMessage::Message() const {
  return message_;
}
const String& ConsoleMessage::WorkerId() const {
  return worker_id_;
}
LocalFrame* ConsoleMessage::Frame() const {
  return frame_.Get();
}
Vector<DOMNodeId>& ConsoleMessage::Nodes() {
  return nodes_;
}
void ConsoleMessage::SetNodes(LocalFrame* frame, Vector<DOMNodeId> nodes) {
  frame_ = frame;
  nodes_ = std::move(nodes);
}
const std::optional<mojom::blink::ConsoleMessageCategory>&
ConsoleMessage::Category() const {
  return category_;
}
void ConsoleMessage::SetCategory(mojom::blink::ConsoleMessageCategory category) {
  category_ = category;
}
void ConsoleMessage::Trace(Visitor* visitor) const {
  visitor->Trace(location_);
  visitor->Trace(frame_);
}
std::optional<std::string> DocumentPolicy::Serialize(
    const DocumentPolicyFeatureState&) {
  return std::nullopt;
}

WebURLError WebURLError::Create(const network::URLLoaderCompletionStatus&,
                                const WebURL& url) {
  return WebURLError(-2, url);
}
WebURLError::WebURLError(int reason, const WebURL& url)
    : reason_(reason), url_(url) {}
WebURLError::WebURLError(int reason,
                         int extended_reason,
                         net::ResolveErrorInfo resolve_error_info,
                         HasCopyInCache has_copy_in_cache,
                         IsWebSecurityViolation is_web_security_violation,
                         const WebURL& url,
                         ShouldCollapseInitiator should_collapse_initiator)
    : reason_(reason),
      extended_reason_(extended_reason),
      resolve_error_info_(resolve_error_info),
      has_copy_in_cache_(has_copy_in_cache == HasCopyInCache::kTrue),
      is_web_security_violation_(
          is_web_security_violation == IsWebSecurityViolation::kTrue),
      url_(url),
      should_collapse_initiator_(
          should_collapse_initiator == ShouldCollapseInitiator::kTrue) {}
WebURLError::WebURLError(network::mojom::BlockedByResponseReason blocked_reason,
                         net::ResolveErrorInfo resolve_error_info,
                         HasCopyInCache has_copy_in_cache,
                         const WebURL& url)
    : reason_(-2),
      resolve_error_info_(resolve_error_info),
      has_copy_in_cache_(has_copy_in_cache == HasCopyInCache::kTrue),
      url_(url),
      blocked_by_response_reason_(blocked_reason) {}
WebURLError::WebURLError(const network::CorsErrorStatus& status,
                         HasCopyInCache has_copy_in_cache,
                         const WebURL& url)
    : reason_(-2),
      has_copy_in_cache_(has_copy_in_cache == HasCopyInCache::kTrue),
      url_(url),
      cors_error_status_(status) {}
WebURLError::WebURLError(
    int reason,
    network::mojom::TrustTokenOperationStatus trust_token_operation_error,
    const WebURL& url)
    : reason_(reason),
      url_(url),
      trust_token_operation_error_(trust_token_operation_error) {}

ResourceError ResourceError::CancelledError(const KURL& url) {
  return ResourceError(-3, url, std::nullopt);
}
ResourceError ResourceError::CancelledDueToAccessCheckError(
    const KURL& url,
    ResourceRequestBlockedReason reason) {
  ResourceError error(-3, url, std::nullopt);
  error.is_access_check_ = true;
  return error;
}
ResourceError ResourceError::CancelledDueToAccessCheckError(
    const KURL& url,
    ResourceRequestBlockedReason,
    const String& localized_description) {
  ResourceError error = CancelledDueToAccessCheckError(
      url, static_cast<ResourceRequestBlockedReason>(0));
  error.localized_description_ = localized_description;
  return error;
}
ResourceError ResourceError::BlockedByResponse(
    const KURL& url,
    network::mojom::BlockedByResponseReason reason) {
  ResourceError error(-2, url, std::nullopt);
  error.blocked_by_response_reason_ = reason;
  return error;
}
ResourceError ResourceError::CacheMissError(const KURL& url) {
  ResourceError error(-400, url, std::nullopt);
  error.has_copy_in_cache_ = true;
  return error;
}
ResourceError ResourceError::TimeoutError(const KURL& url) {
  return ResourceError(-7, url, std::nullopt);
}
ResourceError ResourceError::Failure(const KURL& url) {
  return ResourceError(-2, url, std::nullopt);
}
ResourceError ResourceError::HttpError(const KURL& url) {
  ResourceError error = CancelledError(url);
  error.is_cancelled_from_http_error_ = true;
  return error;
}
ResourceError::ResourceError(
    int error_code,
    const KURL& failing_url,
    std::optional<network::CorsErrorStatus> cors_error_status)
    : error_code_(error_code),
      failing_url_(failing_url),
      is_access_check_(cors_error_status.has_value()),
      cors_error_status_(cors_error_status) {
  InitializeDescription();
}
ResourceError::ResourceError(const KURL& failing_url,
                             const network::CorsErrorStatus& status)
    : ResourceError(-2, failing_url, status) {}
ResourceError::ResourceError(const WebURLError& error)
    : error_code_(error.reason()),
      extended_error_code_(error.extended_reason()),
      resolve_error_info_(error.resolve_error_info()),
      failing_url_(error.url()),
      is_access_check_(error.is_web_security_violation()),
      has_copy_in_cache_(error.has_copy_in_cache()),
      cors_error_status_(error.cors_error_status()),
      should_collapse_inititator_(error.should_collapse_initiator()),
      blocked_by_response_reason_(error.blocked_by_response_reason()),
      trust_token_operation_error_(error.trust_token_operation_error()) {
  InitializeDescription();
}
bool ResourceError::IsCancellation() const {
  return error_code_ == -3;
}
bool ResourceError::IsTrustTokenCacheHit() const {
  return false;
}
bool ResourceError::IsUnactionableTrustTokensStatus() const {
  return false;
}
bool ResourceError::IsTimeout() const {
  return error_code_ == -7;
}
bool ResourceError::IsCacheMiss() const {
  return error_code_ == -400;
}
bool ResourceError::WasBlockedByResponse() const {
  return blocked_by_response_reason_.has_value();
}
bool ResourceError::WasBlockedByORB() const {
  return false;
}
std::optional<ResourceRequestBlockedReason>
ResourceError::GetResourceRequestBlockedReason() const {
  return std::nullopt;
}
std::optional<network::mojom::BlockedByResponseReason>
ResourceError::GetBlockedByResponseReason() const {
  return blocked_by_response_reason_;
}
ResourceError::operator WebURLError() const {
  return WebURLError(error_code_, failing_url_);
}
bool ResourceError::Compare(const ResourceError& a, const ResourceError& b) {
  return a.error_code_ == b.error_code_ && a.failing_url_ == b.failing_url_;
}
void ResourceError::InitializeDescription() {
  localized_description_ = String();
}
std::ostream& operator<<(std::ostream& stream, const ResourceError& error) {
  return stream << "ResourceError(" << error.ErrorCode() << ")";
}

ResourceResponse::ResourceResponse()
    : was_cached_(false),
      connection_reused_(false),
      is_null_(true),
      have_parsed_age_header_(false),
      have_parsed_date_header_(false),
      have_parsed_expires_header_(false),
      have_parsed_last_modified_header_(false),
      has_major_certificate_errors_(false),
      has_range_requested_(false),
      timing_allow_passed_(false),
      was_fetched_via_spdy_(false),
      was_fetched_via_service_worker_(false),
      from_synthetic_response_(false),
      did_service_worker_navigation_preload_(false),
      did_use_shared_dictionary_(false),
      async_revalidation_requested_(false),
      is_signed_exchange_inner_response_(false),
      is_web_bundle_inner_response_(false),
      was_in_prefetch_cache_(false),
      was_cookie_in_request_(false),
      network_accessed_(false),
      from_archive_(false),
      was_alternate_protocol_available_(false),
      was_alpn_negotiated_(false),
      has_authorization_covered_by_wildcard_on_preflight_(false),
      is_validated_(false),
      request_include_credentials_(false),
      should_use_source_hash_for_js_code_cache_(false) {}
ResourceResponse::ResourceResponse(const KURL& current_request_url)
    : ResourceResponse() {
  current_request_url_ = current_request_url;
  is_null_ = false;
}
ResourceResponse::ResourceResponse(const ResourceResponse&) = default;
ResourceResponse& ResourceResponse::operator=(const ResourceResponse&) =
    default;
ResourceResponse::~ResourceResponse() = default;
bool ResourceResponse::IsHTTP() const {
  return current_request_url_.ProtocolIsInHttpFamily();
}
bool ResourceResponse::ShouldPopulateResourceTiming() const {
  return !is_null_;
}
const KURL& ResourceResponse::CurrentRequestUrl() const {
  return current_request_url_;
}
void ResourceResponse::SetCurrentRequestUrl(const KURL& url) {
  current_request_url_ = url;
  is_null_ = false;
}
KURL ResourceResponse::ResponseUrl() const {
  return current_request_url_;
}
bool ResourceResponse::IsServiceWorkerPassThrough() const {
  return false;
}
const AtomicString& ResourceResponse::MimeType() const {
  return mime_type_;
}
void ResourceResponse::SetMimeType(const AtomicString& mime_type) {
  mime_type_ = mime_type;
}
int64_t ResourceResponse::ExpectedContentLength() const {
  return expected_content_length_;
}
void ResourceResponse::SetExpectedContentLength(int64_t length) {
  expected_content_length_ = length;
}
const AtomicString& ResourceResponse::TextEncodingName() const {
  return text_encoding_name_;
}
void ResourceResponse::SetTextEncodingName(const AtomicString& name) {
  text_encoding_name_ = name;
}
int ResourceResponse::HttpStatusCode() const {
  return http_status_code_;
}
void ResourceResponse::SetHttpStatusCode(int code) {
  http_status_code_ = code;
}
const AtomicString& ResourceResponse::HttpStatusText() const {
  return http_status_text_;
}
void ResourceResponse::SetHttpStatusText(const AtomicString& text) {
  http_status_text_ = text;
}
const AtomicString& ResourceResponse::HttpHeaderField(
    const AtomicString& name) const {
  return http_header_fields_.Get(name);
}
void ResourceResponse::SetHttpHeaderField(const AtomicString& name,
                                          const AtomicString& value) {
  http_header_fields_.Set(name, value);
}
void ResourceResponse::AddHttpHeaderField(const AtomicString& name,
                                          const AtomicString& value) {
  http_header_fields_.Add(name, value);
}
void ResourceResponse::AddHttpHeaderFieldWithMultipleValues(
    const AtomicString& name,
    const Vector<AtomicString>& values) {
  for (const auto& value : values) {
    AddHttpHeaderField(name, value);
  }
}
void ResourceResponse::ClearHttpHeaderField(const AtomicString& name) {
  http_header_fields_.Remove(name);
}
const HTTPHeaderMap& ResourceResponse::HttpHeaderFields() const {
  return http_header_fields_;
}
bool ResourceResponse::IsAttachment() const {
  return false;
}
AtomicString ResourceResponse::HttpContentType() const {
  return mime_type_;
}
AtomicString ResourceResponse::GetFilteredHttpContentEncoding() const {
  return g_null_atom;
}
bool ResourceResponse::CacheControlContainsNoCache() const {
  return false;
}
bool ResourceResponse::CacheControlContainsNoStore() const {
  return false;
}
bool ResourceResponse::CacheControlContainsMustRevalidate() const {
  return false;
}
bool ResourceResponse::HasCacheValidatorFields() const {
  return false;
}
std::optional<base::TimeDelta> ResourceResponse::CacheControlMaxAge() const {
  return std::nullopt;
}
std::optional<base::Time> ResourceResponse::Date() const {
  return std::nullopt;
}
std::optional<base::TimeDelta> ResourceResponse::Age() const {
  return std::nullopt;
}
std::optional<base::Time> ResourceResponse::Expires() const {
  return std::nullopt;
}
std::optional<base::Time> ResourceResponse::LastModified() const {
  return std::nullopt;
}
base::TimeDelta ResourceResponse::CacheControlStaleWhileRevalidate() const {
  return base::TimeDelta();
}
unsigned ResourceResponse::ConnectionID() const {
  return connection_id_;
}
void ResourceResponse::SetConnectionID(unsigned id) {
  connection_id_ = id;
}
bool ResourceResponse::ConnectionReused() const {
  return connection_reused_;
}
void ResourceResponse::SetConnectionReused(bool value) {
  connection_reused_ = value;
}
bool ResourceResponse::WasCached() const {
  return was_cached_;
}
void ResourceResponse::SetWasCached(bool value) {
  was_cached_ = value;
}
ResourceLoadTiming* ResourceResponse::GetResourceLoadTiming() const {
  return resource_load_timing_.get();
}
void ResourceResponse::SetResourceLoadTiming(
    scoped_refptr<ResourceLoadTiming> timing) {
  resource_load_timing_ = std::move(timing);
}
void ResourceResponse::SetSSLInfo(const net::SSLInfo& ssl_info) {
  ssl_info_ = ssl_info;
}
void ResourceResponse::SetServiceWorkerRouterInfo(
    scoped_refptr<ServiceWorkerRouterInfo> value) {
  service_worker_router_info_ = std::move(value);
}
bool ResourceResponse::IsCorsSameOrigin() const {
  return response_type_ == network::mojom::FetchResponseType::kDefault ||
         response_type_ == network::mojom::FetchResponseType::kBasic ||
         response_type_ == network::mojom::FetchResponseType::kCors;
}
bool ResourceResponse::IsCorsCrossOrigin() const {
  return !IsCorsSameOrigin();
}
AtomicString ResourceResponse::ConnectionInfoString() const {
  return g_null_atom;
}
mojom::blink::CacheState ResourceResponse::CacheState() const {
  return was_cached_ ? mojom::blink::CacheState::kLocal
                     : mojom::blink::CacheState::kNone;
}
void ResourceResponse::SetIsValidated(bool is_validated) {
  is_validated_ = is_validated;
}
void ResourceResponse::SetEncodedDataLength(int64_t value) {
  encoded_data_length_ = value;
}
void ResourceResponse::SetEncodedBodyLength(uint64_t value) {
  encoded_body_length_ = value;
}
void ResourceResponse::SetDecodedBodyLength(int64_t value) {
  decoded_body_length_ = value;
}
network::mojom::CrossOriginEmbedderPolicyValue
ResourceResponse::GetCrossOriginEmbedderPolicy() const {
  return network::mojom::CrossOriginEmbedderPolicyValue::kNone;
}
const Vector<network::IntegrityMetadata>&
ResourceResponse::GetUnencodedDigests() const {
  return unencoded_digests_;
}
void ResourceResponse::SetUnencodedDigests(
    Vector<network::IntegrityMetadata> digests) {
  unencoded_digests_ = std::move(digests);
}
void ResourceResponse::UpdateHeaderParsedState(const AtomicString&) {}

void NavigationBodyLoader::StartLoadingBodyInBackground(
    std::unique_ptr<BodyTextDecoder>,
    bool) {}

StringView KURL::User() const {
  return StringView();
}
StringView KURL::Pass() const {
  return StringView();
}

mojom::blink::ResourceTimingInfoPtr CreateResourceTimingInfo(
    base::TimeTicks start_time,
    const KURL& initial_url,
    const ResourceResponse* response) {
  auto info = mojom::blink::ResourceTimingInfo::New();
  info->start_time = start_time;
  info->name = initial_url;
  if (response) {
    info->response_status = response->HttpStatusCode();
    info->encoded_body_size = response->EncodedBodyLength();
    info->decoded_body_size = response->DecodedBodyLength();
    info->content_type = response->MimeType().GetString();
    info->cache_state = response->CacheState();
  }
  return info;
}

HTTPHeaderMap::HTTPHeaderMap() = default;
HTTPHeaderMap::~HTTPHeaderMap() = default;
std::unique_ptr<CrossThreadHTTPHeaderMapData> HTTPHeaderMap::CopyData() const {
  auto data = std::make_unique<CrossThreadHTTPHeaderMapData>();
  for (const auto& header : headers_) {
    data->push_back(std::make_pair(header.key, header.value));
  }
  return data;
}
void HTTPHeaderMap::Adopt(std::unique_ptr<CrossThreadHTTPHeaderMapData> data) {
  headers_.clear();
  if (!data) {
    return;
  }
  for (const auto& header : *data) {
    headers_.Set(AtomicString(header.first), AtomicString(header.second));
  }
}
String HTTPHeaderMap::GetAsRawString(int, String) const {
  return String();
}

WebString::~WebString() = default;
WebString::WebString() = default;
WebString::WebString(std::u16string_view) {}
WebString::WebString(const WebString&) = default;
WebString::WebString(WebString&&) = default;
WebString& WebString::operator=(const WebString&) = default;
WebString& WebString::operator=(WebString&&) = default;
void WebString::Reset() {
  impl_.reset();
}
bool WebString::Equals(const WebString&) const {
  return true;
}
bool WebString::Equals(std::string_view characters) const {
  return characters.empty();
}
size_t WebString::Find(const WebString&) const {
  return std::string::npos;
}
size_t WebString::Find(std::string_view) const {
  return std::string::npos;
}
size_t WebString::length() const {
  return 0;
}
std::string WebString::Utf8(Utf8ConversionMode) const {
  return {};
}
WebString WebString::Substring(size_t, size_t) const {
  return WebString();
}
WebString WebString::FromUtf8(std::string_view) {
  return WebString();
}
std::u16string WebString::Utf16() const {
  return {};
}
WebString WebString::FromUtf16(std::optional<std::u16string_view>) {
  return WebString();
}
std::string WebString::Latin1() const {
  return {};
}
WebString WebString::FromLatin1(std::string_view) {
  return WebString();
}
std::string WebString::Ascii() const {
  return {};
}
bool WebString::ContainsOnlyAscii() const {
  return true;
}
WebString WebString::FromAscii(std::string_view) {
  return WebString();
}
bool WebString::operator<(const WebString&) const {
  return false;
}
bool WebString::Is8Bit() const {
  return true;
}
WebString::WebString(const String&) {}
WebString& WebString::operator=(const String&) {
  Reset();
  return *this;
}
WebString::operator String() const {
  return String();
}
WebString::operator StringView() const {
  return StringView();
}
WebString::WebString(const AtomicString&) {}
WebString& WebString::operator=(const AtomicString&) {
  Reset();
  return *this;
}
WebString::operator AtomicString() const {
  return AtomicString();
}

WebURLResponse::~WebURLResponse() = default;
WebURLResponse::WebURLResponse() : resource_response_(nullptr) {}
WebURLResponse::WebURLResponse(const WebURLResponse&)
    : resource_response_(nullptr) {}
WebURLResponse::WebURLResponse(const WebURL&) : resource_response_(nullptr) {}
WebURLResponse& WebURLResponse::operator=(const WebURLResponse&) {
  return *this;
}
bool WebURLResponse::IsNull() const {
  return resource_response_ == nullptr;
}

NavigatorLanguage::NavigatorLanguage(ExecutionContext*) {}
AtomicString NavigatorLanguage::language() {
  return AtomicString("en-US");
}
const Vector<String>& NavigatorLanguage::languages() {
  DEFINE_STATIC_LOCAL(Vector<String>, empty_languages, ());
  return empty_languages;
}
bool NavigatorLanguage::IsLanguagesDirty() const {
  return false;
}
void NavigatorLanguage::SetLanguagesDirty() {}
void NavigatorLanguage::SetLanguagesForTesting(const String&) {}
void NavigatorLanguage::Trace(Visitor*) const {}

UseCounterImpl::UseCounterImpl(Context context, CommitState commit_state)
    : mute_count_(0), context_(context), commit_state_(commit_state) {}
void UseCounterImpl::Count(CSSPropertyID, CSSPropertyType, const LocalFrame*) {}
void UseCounterImpl::Count(WebFeature, const LocalFrame*) {}
void UseCounterImpl::CountWebDXFeature(WebDXFeature, const LocalFrame*) {}
void UseCounterImpl::CountPermissionsPolicyUsage(
    network::mojom::PermissionsPolicyFeature,
    PermissionsPolicyUsageType,
    const LocalFrame&) {}
bool UseCounterImpl::IsCounted(WebFeature) const {
  return false;
}
bool UseCounterImpl::IsWebDXFeatureCounted(WebDXFeature) const {
  return false;
}
bool UseCounterImpl::IsCounted(CSSPropertyID, CSSPropertyType) const {
  return false;
}
void UseCounterImpl::AddObserver(Observer*) {}
void UseCounterImpl::DidCommitLoad(const LocalFrame*) {}
void UseCounterImpl::MuteForInspector() {
  ++mute_count_;
}
void UseCounterImpl::UnmuteForInspector() {
  if (mute_count_) {
    --mute_count_;
  }
}
void UseCounterImpl::ClearMeasurementForTesting(WebFeature) {}
void UseCounterImpl::ClearMeasurementForTesting(WebDXFeature) {}
void UseCounterImpl::ReportTotalTakenTime(const LocalFrame*, bool) {}
void UseCounterImpl::Trace(Visitor*) const {}

void DocumentLoadTiming::SetActivationStart(base::TimeTicks value) {
  document_load_timing_values_->activation_start = value;
}

std::unique_ptr<CodeCacheHost> CodeCacheHost::Create(
    mojo::Remote<mojom::blink::CodeCacheHost>) {
  return nullptr;
}
BackgroundCodeCacheHost::BackgroundCodeCacheHost(
    mojo::PendingRemote<mojom::blink::CodeCacheHost> pending_remote)
    : pending_remote_(std::move(pending_remote)) {}
BackgroundCodeCacheHost::~BackgroundCodeCacheHost() = default;
CodeCacheHost& BackgroundCodeCacheHost::GetCodeCacheHost(
    scoped_refptr<base::SequencedTaskRunner>) {
  CHECK(false);
}

WebNavigationParams::PrefetchedSignedExchange::PrefetchedSignedExchange() =
    default;
WebNavigationParams::PrefetchedSignedExchange::PrefetchedSignedExchange(
    const WebURL& input_outer_url,
    const WebString& input_header_integrity,
    const WebURL& input_inner_url,
    const WebURLResponse& input_inner_response,
    CrossVariantMojoRemote<network::mojom::URLLoaderFactoryInterfaceBase>
        input_loader_factory)
    : outer_url(input_outer_url),
      header_integrity(input_header_integrity),
      inner_url(input_inner_url),
      inner_response(input_inner_response),
      loader_factory(std::move(input_loader_factory)) {}
WebNavigationParams::PrefetchedSignedExchange::~PrefetchedSignedExchange() =
    default;

SecurityContextInit::SecurityContextInit(ExecutionContext* execution_context)
    : execution_context_(execution_context) {}
void SecurityContextInit::InitPermissionsPolicyFrom(const SecurityContext&) {}
void SecurityContextInit::InitDocumentPolicyFrom(const SecurityContext&) {}
void SecurityContextInit::ApplyPermissionsPolicy(
    LocalFrame&,
    const ResourceResponse&,
    const FramePolicy&,
    const base::optional_ref<const Vector<IsolatedAppPermissionPolicyEntry>>,
    const base::optional_ref<const FencedFrame::RedactedFencedFrameProperties>,
    const KURL&) {}
void SecurityContextInit::ApplyDocumentPolicy(
    DocumentPolicy::ParsedDocumentPolicy&,
    const String&) {}
network::ParsedPermissionsPolicy SecurityContextInit::ParseIsolatedAppPermissionsPolicy(
    const Vector<IsolatedAppPermissionPolicyEntry>&) {
  return {};
}

}  // namespace blink

namespace blink::pointer_type_names {

const AtomicString& kTouch = AtomicString("touch");

}  // namespace blink::pointer_type_names
