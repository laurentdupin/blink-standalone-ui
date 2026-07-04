// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "services/network/public/cpp/resource_request_body.h"

#include <optional>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "base/feature_list.h"
#include "base/time/time.h"
#include "mojo/public/cpp/bindings/lib/wtf_serialization.h"
#include "openssl/pool.h"
#include "net/base/features.h"
#include "net/base/host_port_pair.h"
#include "net/base/isolation_info.h"
#include "net/base/network_anonymization_key.h"
#include "net/base/network_isolation_key.h"
#include "net/base/proxy_chain.h"
#include "net/base/proxy_server.h"
#include "net/cert/x509_certificate.h"
#include "net/cookies/cookie_partition_key.h"
#include "net/http/http_util.h"
#include "net/http/http_cache.h"
#include "net/http/http_request_headers.h"
#include "net/http/http_response_headers.h"
#include "net/ssl/ssl_cipher_suite_names.h"
#include "net/ssl/ssl_info.h"
#include "services/network/public/cpp/features.h"
#include "services/network/public/cpp/resource_request.h"
#include "services/network/public/cpp/auth_mojom_traits.h"
#include "services/network/public/cpp/http_response_headers_mojom_traits.h"
#include "services/network/public/cpp/network_param_mojom_traits.h"
#include "services/network/public/cpp/ssl_info_mojom_traits.h"
#include "services/network/public/cpp/url_request_mojom_traits.h"
#include "services/network/public/mojom/alternate_protocol_usage.mojom-shared.h"
#include "services/network/public/mojom/auth.mojom-shared-internal.h"
#include "services/network/public/mojom/client_security_state.mojom.h"
#include "services/network/public/mojom/declarative_performance_observer.mojom.h"
#include "services/network/public/mojom/declarative_performance_observer.mojom-blink.h"
#include "services/network/public/mojom/declarative_performance_observer.mojom-shared-internal.h"
#include "services/network/public/mojom/device_bound_sessions.mojom-shared.h"
#include "services/network/public/mojom/document_isolation_policy.mojom.h"
#include "services/network/public/mojom/document_isolation_policy.mojom-blink.h"
#include "services/network/public/mojom/document_isolation_policy.mojom-shared-internal.h"
#include "services/network/public/mojom/encoded_body_length.mojom.h"
#include "services/network/public/mojom/encoded_body_length.mojom-blink.h"
#include "services/network/public/mojom/encoded_body_length.mojom-shared-internal.h"
#include "services/network/public/mojom/hash_value.mojom.h"
#include "services/network/public/mojom/hash_value.mojom-blink.h"
#include "services/network/public/mojom/hash_value.mojom-shared-internal.h"
#include "services/network/public/mojom/http_response_headers.mojom-shared-internal.h"
#include "services/network/public/mojom/load_timing_internal_info.mojom.h"
#include "services/network/public/mojom/load_timing_internal_info.mojom-blink.h"
#include "services/network/public/mojom/load_timing_internal_info.mojom-shared-internal.h"
#include "services/network/public/mojom/no_vary_search.mojom.h"
#include "services/network/public/mojom/no_vary_search.mojom-blink.h"
#include "services/network/public/mojom/no_vary_search.mojom-shared-internal.h"
#include "services/network/public/mojom/parsed_headers.mojom.h"
#include "services/network/public/mojom/parsed_headers.mojom-blink.h"
#include "services/network/public/mojom/parsed_headers.mojom-shared-internal.h"
#include "services/network/public/mojom/parsed_request_cookie.mojom.h"
#include "services/network/public/mojom/parsed_request_cookie.mojom-blink.h"
#include "services/network/public/mojom/parsed_request_cookie.mojom-shared-internal.h"
#include "services/network/public/mojom/request_priority.mojom-shared.h"
#include "services/network/public/mojom/schemeful_site.mojom.h"
#include "services/network/public/mojom/schemeful_site.mojom-blink.h"
#include "services/network/public/mojom/schemeful_site.mojom-shared-internal.h"
#include "services/network/public/mojom/service_worker_router_info.mojom.h"
#include "services/network/public/mojom/service_worker_router_info.mojom-blink.h"
#include "services/network/public/mojom/source_type.mojom-shared.h"
#include "services/network/public/mojom/ssl_info.mojom.h"
#include "services/network/public/mojom/ssl_info.mojom-blink.h"
#include "services/network/public/mojom/ssl_info.mojom-shared-internal.h"
#include "services/network/public/mojom/storage_access_api.mojom-shared.h"
#include "services/network/public/mojom/timing_allow_origin.mojom.h"
#include "services/network/public/mojom/timing_allow_origin.mojom-blink.h"
#include "services/network/public/mojom/timing_allow_origin.mojom-shared-internal.h"
#include "services/network/public/mojom/unencoded_digest.mojom.h"
#include "services/network/public/mojom/unencoded_digest.mojom-blink.h"
#include "services/network/public/mojom/unencoded_digest.mojom-shared-internal.h"
#include "services/network/public/mojom/url_request.mojom-shared-internal.h"
#include "services/network/public/mojom/web_client_hints_types.mojom-shared.h"
#include "third_party/perfetto/include/perfetto/tracing/traced_value.h"

namespace net::features {
BASE_FEATURE(kThirdPartyStoragePartitioning,
             "ThirdPartyStoragePartitioning",
             base::FEATURE_DISABLED_BY_DEFAULT);
}  // namespace net::features

namespace network::features {
BASE_FEATURE(kPopulatePermissionsPolicyOnRequest,
             base::FEATURE_DISABLED_BY_DEFAULT);
}  // namespace network::features

namespace net {

X509Certificate::ParsedFields::ParsedFields() = default;
X509Certificate::ParsedFields::ParsedFields(const ParsedFields&) = default;
X509Certificate::ParsedFields::ParsedFields(ParsedFields&&) = default;
X509Certificate::ParsedFields::~ParsedFields() = default;

bool X509Certificate::ParsedFields::Initialize(const CRYPTO_BUFFER*,
                                               UnsafeCreateOptions) {
  return false;
}

X509Certificate::~X509Certificate() = default;

HttpRequestHeaders::~HttpRequestHeaders() = default;

bool HttpCache::IsSplitCacheEnabled() {
  return false;
}

void SSLCipherSuiteToStrings(const char** key_exchange_str,
                             const char** cipher_str,
                             const char** mac_str,
                             bool* is_aead,
                             bool* is_tls13,
                             uint16_t) {
  if (key_exchange_str) {
    *key_exchange_str = "???";
  }
  if (cipher_str) {
    *cipher_str = "???";
  }
  if (mac_str) {
    *mac_str = "???";
  }
  if (is_aead) {
    *is_aead = false;
  }
  if (is_tls13) {
    *is_tls13 = false;
  }
}

void SSLVersionToString(const char** name, int) {
  if (name) {
    *name = "???";
  }
}

bool ParseSSLCipherString(const std::string&, uint16_t*) {
  return false;
}

int ObsoleteSSLStatus(int, uint16_t) {
  return OBSOLETE_SSL_NONE;
}

bool IsTLSCipherSuiteAllowedByHTTP2(uint16_t) {
  return false;
}

scoped_refptr<NetworkIsolationKey::Data> NetworkIsolationKey::Data::GetEmptyData() {
  static scoped_refptr<Data> empty_data =
      base::MakeRefCounted<Data>(base::PassKey<Data>());
  return empty_data;
}

NetworkIsolationKey::Data::Data(base::PassKey<Data>)
    : network_isolation_partition_(NetworkIsolationPartition::kGeneral) {}

NetworkIsolationKey::Data::Data(
    std::optional<SchemefulSite>&& top_frame_site,
    std::optional<SchemefulSite>&& frame_site,
    std::optional<base::UnguessableToken>&& nonce,
    NetworkIsolationPartition network_isolation_partition)
    : top_frame_site_(std::move(top_frame_site)),
      frame_site_(std::move(frame_site)),
      nonce_(std::move(nonce)),
      network_isolation_partition_(network_isolation_partition) {}

NetworkIsolationKey::Data::~Data() = default;

NetworkIsolationKey::NetworkIsolationKey() : data_(Data::GetEmptyData()) {}
NetworkIsolationKey::NetworkIsolationKey(const NetworkIsolationKey&) = default;
NetworkIsolationKey::NetworkIsolationKey(NetworkIsolationKey&&) = default;
NetworkIsolationKey::~NetworkIsolationKey() = default;
NetworkIsolationKey& NetworkIsolationKey::operator=(const NetworkIsolationKey&) =
    default;
NetworkIsolationKey& NetworkIsolationKey::operator=(NetworkIsolationKey&&) =
    default;

NetworkIsolationKey::NetworkIsolationKey(const scoped_refptr<const Data>& data)
    : data_(data ? data : Data::GetEmptyData()) {}

NetworkIsolationKey::NetworkIsolationKey(
    const SchemefulSite& top_frame_site,
    const SchemefulSite& frame_site,
    const std::optional<base::UnguessableToken>& nonce,
    NetworkIsolationPartition network_isolation_partition)
    : NetworkIsolationKey(base::MakeRefCounted<Data>(
          std::optional<SchemefulSite>(top_frame_site),
          std::optional<SchemefulSite>(frame_site),
          std::optional<base::UnguessableToken>(nonce),
          network_isolation_partition)) {}

NetworkIsolationKey::NetworkIsolationKey(
    SchemefulSite&& top_frame_site,
    SchemefulSite&& frame_site,
    std::optional<base::UnguessableToken>&& nonce,
    NetworkIsolationPartition network_isolation_partition)
    : NetworkIsolationKey(base::MakeRefCounted<Data>(
          std::optional<SchemefulSite>(std::move(top_frame_site)),
          std::optional<SchemefulSite>(std::move(frame_site)),
          std::move(nonce),
          network_isolation_partition)) {}

NetworkIsolationKey NetworkIsolationKey::CreateEmptyWithPartition(
    NetworkIsolationPartition network_isolation_partition) {
  return NetworkIsolationKey(base::MakeRefCounted<Data>(
      std::nullopt, std::nullopt, std::nullopt, network_isolation_partition));
}

NetworkIsolationKey NetworkIsolationKey::CreateTransientForTesting() {
  return NetworkIsolationKey();
}

NetworkIsolationKey NetworkIsolationKey::CreateWithNewFrameSite(
    const SchemefulSite&) const {
  return NetworkIsolationKey();
}

std::optional<std::string> NetworkIsolationKey::ToCacheKeyString() const {
  return std::nullopt;
}

std::string NetworkIsolationKey::ToDebugString() const {
  return std::string();
}

bool NetworkIsolationKey::IsTransient() const {
  return true;
}

bool NetworkIsolationKey::IsEmpty() const {
  return true;
}

bool NetworkIsolationKey::IsOpaque() const {
  return false;
}

scoped_refptr<NetworkAnonymizationKey::Data>
NetworkAnonymizationKey::Data::GetEmptyData() {
  static scoped_refptr<Data> empty_data =
      base::MakeRefCounted<Data>(base::PassKey<Data>());
  return empty_data;
}

NetworkAnonymizationKey::Data::Data(base::PassKey<Data>)
    : is_cross_site_(false),
      network_isolation_partition_(NetworkIsolationPartition::kGeneral) {}

NetworkAnonymizationKey::Data::Data(
    std::optional<SchemefulSite> top_frame_site,
    bool is_cross_site,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition)
    : top_frame_site_(std::move(top_frame_site)),
      is_cross_site_(is_cross_site),
      nonce_(std::move(nonce)),
      network_isolation_partition_(network_isolation_partition) {}

NetworkAnonymizationKey::Data::~Data() = default;

NetworkAnonymizationKey::NetworkAnonymizationKey()
    : data_(Data::GetEmptyData()) {}
NetworkAnonymizationKey::NetworkAnonymizationKey(
    const NetworkAnonymizationKey&) = default;
NetworkAnonymizationKey::NetworkAnonymizationKey(NetworkAnonymizationKey&&) =
    default;
NetworkAnonymizationKey::~NetworkAnonymizationKey() = default;
NetworkAnonymizationKey& NetworkAnonymizationKey::operator=(
    const NetworkAnonymizationKey&) = default;
NetworkAnonymizationKey& NetworkAnonymizationKey::operator=(
    NetworkAnonymizationKey&&) = default;

NetworkAnonymizationKey::NetworkAnonymizationKey(
    std::optional<SchemefulSite> top_frame_site,
    bool is_cross_site,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition)
    : data_(base::MakeRefCounted<Data>(std::move(top_frame_site),
                                       is_cross_site,
                                       std::move(nonce),
                                       network_isolation_partition)) {}

NetworkAnonymizationKey NetworkAnonymizationKey::CreateEmptyWithPartition(
    NetworkIsolationPartition network_isolation_partition) {
  return NetworkAnonymizationKey(std::nullopt, false, std::nullopt,
                                 network_isolation_partition);
}

NetworkAnonymizationKey NetworkAnonymizationKey::CreateFromFrameSite(
    const SchemefulSite&,
    const SchemefulSite&,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition) {
  return NetworkAnonymizationKey(std::nullopt, false, std::move(nonce),
                                 network_isolation_partition);
}

NetworkAnonymizationKey NetworkAnonymizationKey::CreateFromNetworkIsolationKey(
    const net::NetworkIsolationKey&) {
  return NetworkAnonymizationKey();
}

NetworkAnonymizationKey NetworkAnonymizationKey::CreateTransient() {
  return NetworkAnonymizationKey();
}

std::string NetworkAnonymizationKey::ToDebugString() const {
  return std::string();
}

bool NetworkAnonymizationKey::IsEmpty() const {
  return true;
}

bool NetworkAnonymizationKey::IsTransient() const {
  return true;
}

bool NetworkAnonymizationKey::ToValue(base::Value*) const {
  return false;
}

bool NetworkAnonymizationKey::FromValue(const base::Value&,
                                        NetworkAnonymizationKey*) {
  return false;
}

bool NetworkAnonymizationKey::IsPartitioningEnabled() {
  return false;
}

void NetworkAnonymizationKey::PartitionByDefault() {}
void NetworkAnonymizationKey::ClearGlobalsForTesting() {}

std::string NetworkAnonymizationKey::GetSiteDebugString(
    const std::optional<SchemefulSite>&) const {
  return std::string();
}

std::optional<std::string> NetworkAnonymizationKey::SerializeSiteWithNonce(
    const SchemefulSite&) {
  return std::nullopt;
}

IsolationInfo::Data::Data(
    RequestType request_type,
    std::optional<url::Origin> top_frame_origin,
    std::optional<url::Origin> frame_origin,
    std::optional<FrameAncestorRelation> frame_ancestor_relation,
    SiteForCookies site_for_cookies,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition)
    : request_type_(request_type),
      top_frame_origin_(std::move(top_frame_origin)),
      frame_origin_(std::move(frame_origin)),
      frame_ancestor_relation_(frame_ancestor_relation),
      site_for_cookies_(std::move(site_for_cookies)),
      network_isolation_key_(),
      network_anonymization_key_() {}

IsolationInfo::Data::~Data() = default;

IsolationInfo::IsolationInfo()
    : data_(base::MakeRefCounted<Data>(
          RequestType::kOther,
          std::nullopt,
          std::nullopt,
          std::nullopt,
          SiteForCookies(),
          std::nullopt,
          NetworkIsolationPartition::kGeneral)) {}

IsolationInfo::IsolationInfo(const IsolationInfo&) = default;
IsolationInfo::IsolationInfo(IsolationInfo&&) = default;
IsolationInfo::~IsolationInfo() = default;
IsolationInfo& IsolationInfo::operator=(const IsolationInfo&) = default;
IsolationInfo& IsolationInfo::operator=(IsolationInfo&&) = default;

IsolationInfo::IsolationInfo(
    RequestType request_type,
    std::optional<url::Origin> top_frame_origin,
    std::optional<url::Origin> frame_origin,
    SiteForCookies site_for_cookies,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition,
    std::optional<FrameAncestorRelation> frame_ancestor_relation)
    : data_(base::MakeRefCounted<Data>(request_type,
                                       std::move(top_frame_origin),
                                       std::move(frame_origin),
                                       frame_ancestor_relation,
                                       std::move(site_for_cookies),
                                       std::move(nonce),
                                       network_isolation_partition)) {}

std::optional<IsolationInfo::FrameAncestorRelation>
IsolationInfo::OriginRelationToFrameAncestorRelation(
    std::optional<OriginRelation>) {
  return std::nullopt;
}

std::optional<IsolationInfo::FrameAncestorRelation>
IsolationInfo::ComputeNewFrameAncestorRelation(
    std::optional<FrameAncestorRelation> cur_relation,
    const url::Origin&,
    const url::Origin&) {
  return cur_relation;
}

std::string_view IsolationInfo::FrameAncestorRelationString(
    FrameAncestorRelation) {
  return "unsupported";
}

IsolationInfo IsolationInfo::CreateForInternalRequest(const url::Origin&) {
  return IsolationInfo();
}

IsolationInfo IsolationInfo::CreateTransient(
    std::optional<base::UnguessableToken>) {
  return IsolationInfo();
}

IsolationInfo IsolationInfo::CreateEmptyWithPartition(
    NetworkIsolationPartition network_isolation_partition) {
  return IsolationInfo(RequestType::kOther, std::nullopt, std::nullopt,
                       SiteForCookies(), std::nullopt,
                       network_isolation_partition, std::nullopt);
}

std::optional<IsolationInfo> IsolationInfo::Deserialize(const std::string&) {
  return std::nullopt;
}

IsolationInfo IsolationInfo::Create(
    RequestType request_type,
    url::Origin top_frame_origin,
    url::Origin frame_origin,
    SiteForCookies site_for_cookies,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition,
    std::optional<FrameAncestorRelation> frame_ancestor_relation) {
  return IsolationInfo(request_type, std::move(top_frame_origin),
                       std::move(frame_origin), std::move(site_for_cookies),
                       std::move(nonce), network_isolation_partition,
                       frame_ancestor_relation);
}

IsolationInfo IsolationInfo::DoNotUseCreatePartialFromNak(
    const net::NetworkAnonymizationKey&) {
  return IsolationInfo();
}

std::optional<IsolationInfo> IsolationInfo::CreateIfConsistent(
    RequestType request_type,
    std::optional<url::Origin> top_frame_origin,
    std::optional<url::Origin> frame_origin,
    SiteForCookies site_for_cookies,
    std::optional<base::UnguessableToken> nonce,
    NetworkIsolationPartition network_isolation_partition,
    std::optional<FrameAncestorRelation> frame_ancestor_relation) {
  return IsolationInfo(request_type, std::move(top_frame_origin),
                       std::move(frame_origin), std::move(site_for_cookies),
                       std::move(nonce), network_isolation_partition,
                       frame_ancestor_relation);
}

IsolationInfo IsolationInfo::CreateForRedirect(const url::Origin&) const {
  return *this;
}

NetworkIsolationPartition IsolationInfo::GetNetworkIsolationPartition() const {
  return NetworkIsolationPartition::kGeneral;
}

bool IsolationInfo::IsEqualForTesting(const IsolationInfo&) const {
  return true;
}

std::string IsolationInfo::Serialize() const {
  return std::string();
}

std::string IsolationInfo::DebugString() const {
  return std::string();
}

CookiePartitionKey::AncestorChainBit CookiePartitionKey::BoolToAncestorChainBit(
    bool val) {
  return val ? AncestorChainBit::kCrossSite : AncestorChainBit::kSameSite;
}

#if !BUILDFLAG(CRONET_BUILD)
CookiePartitionKey::CookiePartitionKey(mojo::DefaultConstruct::Tag) {}
#endif

CookiePartitionKey::CookiePartitionKey(const CookiePartitionKey&) = default;
CookiePartitionKey::CookiePartitionKey(CookiePartitionKey&&) = default;
CookiePartitionKey& CookiePartitionKey::operator=(const CookiePartitionKey&) =
    default;
CookiePartitionKey& CookiePartitionKey::operator=(CookiePartitionKey&&) =
    default;
CookiePartitionKey::~CookiePartitionKey() = default;

CookiePartitionKey::CookiePartitionKey(
    const SchemefulSite& site,
    std::optional<base::UnguessableToken> nonce,
    AncestorChainBit ancestor_chain_bit)
    : site_(site),
      nonce_(std::move(nonce)),
      ancestor_chain_bit_(ancestor_chain_bit) {}

std::optional<CookiePartitionKey> CookiePartitionKey::FromStorageKeyComponents(
    const SchemefulSite&,
    AncestorChainBit,
    base::optional_ref<const base::UnguessableToken>) {
  return std::nullopt;
}

}  // namespace net

namespace network {

DataElementBytes::DataElementBytes() = default;
DataElementBytes::DataElementBytes(std::vector<uint8_t> bytes)
    : bytes_(std::move(bytes)) {}
DataElementBytes::DataElementBytes(DataElementBytes&& other) = default;
DataElementBytes& DataElementBytes::operator=(DataElementBytes&& other) =
    default;
DataElementBytes::~DataElementBytes() = default;

std::string_view DataElementBytes::AsStringView() const {
  return std::string_view(reinterpret_cast<const char*>(bytes_.data()),
                          bytes_.size());
}

DataElementBytes DataElementBytes::Clone() const {
  return DataElementBytes(bytes_);
}

DataElementDataPipe::DataElementDataPipe() = default;
DataElementDataPipe::DataElementDataPipe(
    mojo::PendingRemote<mojom::DataPipeGetter> data_pipe_getter)
    : data_pipe_getter_(std::move(data_pipe_getter)) {}
DataElementDataPipe::DataElementDataPipe(DataElementDataPipe&& other) =
    default;
DataElementDataPipe& DataElementDataPipe::operator=(
    DataElementDataPipe&& other) = default;
DataElementDataPipe::~DataElementDataPipe() = default;

mojo::PendingRemote<mojom::DataPipeGetter>
DataElementDataPipe::ReleaseDataPipeGetter() {
  return std::move(data_pipe_getter_);
}

mojo::PendingRemote<mojom::DataPipeGetter>
DataElementDataPipe::CloneDataPipeGetter() const {
  return mojo::PendingRemote<mojom::DataPipeGetter>();
}

DataElementDataPipe DataElementDataPipe::Clone() const {
  return DataElementDataPipe();
}

DataElementChunkedDataPipe::DataElementChunkedDataPipe()
    : read_only_once_(false) {}
DataElementChunkedDataPipe::DataElementChunkedDataPipe(
    mojo::PendingRemote<mojom::ChunkedDataPipeGetter> data_pipe_getter,
    ReadOnlyOnce read_only_once)
    : chunked_data_pipe_getter_(std::move(data_pipe_getter)),
      read_only_once_(read_only_once) {}
DataElementChunkedDataPipe::DataElementChunkedDataPipe(
    DataElementChunkedDataPipe&& other) = default;
DataElementChunkedDataPipe& DataElementChunkedDataPipe::operator=(
    DataElementChunkedDataPipe&& other) = default;
DataElementChunkedDataPipe::~DataElementChunkedDataPipe() = default;

mojo::PendingRemote<mojom::ChunkedDataPipeGetter>
DataElementChunkedDataPipe::ReleaseChunkedDataPipeGetter() {
  return std::move(chunked_data_pipe_getter_);
}

DataElementFile::DataElementFile() = default;
DataElementFile::DataElementFile(
    const base::FilePath& path,
    uint64_t offset,
    uint64_t length,
    base::Time expected_modification_time)
    : path_(path),
      offset_(offset),
      length_(length),
      expected_modification_time_(expected_modification_time) {}
DataElementFile::DataElementFile(const DataElementFile&) = default;
DataElementFile& DataElementFile::operator=(const DataElementFile&) = default;
DataElementFile::DataElementFile(DataElementFile&&) = default;
DataElementFile& DataElementFile::operator=(DataElementFile&&) = default;
DataElementFile::~DataElementFile() = default;

DataElement::DataElement() = default;
DataElement::DataElement(DataElement&& other) = default;
DataElement& DataElement::operator=(DataElement&& other) = default;
DataElement::~DataElement() = default;

DataElement DataElement::Clone() const {
  if (const auto* bytes = TryAs<DataElementBytes>()) {
    return DataElement(bytes->Clone());
  }
  if (const auto* data_pipe = TryAs<DataElementDataPipe>()) {
    return DataElement(data_pipe->Clone());
  }
  if (const auto* file = TryAs<DataElementFile>()) {
    return DataElement(*file);
  }
  return DataElement();
}

OptionalTrustTokenParams::~OptionalTrustTokenParams() = default;

SharedDataPipeProducerHandle::~SharedDataPipeProducerHandle() = default;

ResourceRequest::TrustedParams::EnabledClientHints::~EnabledClientHints() =
    default;

ResourceRequest::TrustedParams::~TrustedParams() = default;

ResourceRequest::WebBundleTokenParams::~WebBundleTokenParams() = default;

ResourceRequestBody::ResourceRequestBody()
    : identifier_(0), contains_sensitive_info_(false) {}
ResourceRequestBody::~ResourceRequestBody() = default;

ResourceRequest::~ResourceRequest() = default;

scoped_refptr<ResourceRequestBody> ResourceRequestBody::CreateFromCopyOfBytes(
    base::span<const uint8_t>) {
  return base::MakeRefCounted<ResourceRequestBody>();
}

scoped_refptr<ResourceRequestBody> ResourceRequestBody::CreateFromBytes(
    std::vector<uint8_t>&&) {
  return base::MakeRefCounted<ResourceRequestBody>();
}

void ResourceRequestBody::AppendBytes(std::vector<uint8_t>&&) {}

void ResourceRequestBody::AppendCopyOfBytes(base::span<const uint8_t>) {}

void ResourceRequestBody::AppendFileRange(
    const base::FilePath&,
    uint64_t,
    uint64_t,
    const base::Time&) {}

void ResourceRequestBody::AppendDataPipe(
    mojo::PendingRemote<mojom::DataPipeGetter>) {}

void ResourceRequestBody::SetToChunkedDataPipe(
    mojo::PendingRemote<mojom::ChunkedDataPipeGetter>,
    ReadOnlyOnce) {}

void ResourceRequestBody::SetToReadOnceStream(
    mojo::PendingRemote<mojom::ChunkedDataPipeGetter>) {}

std::vector<base::FilePath> ResourceRequestBody::GetReferencedFiles() const {
  return {};
}

bool ResourceRequestBody::EnableToAppendElement() const {
  return true;
}

}  // namespace network

namespace network::mojom {

ClientSecurityState::~ClientSecurityState() = default;

}  // namespace network::mojom

namespace net {

HostPortPair::HostPortPair() : port_(0) {}
HostPortPair::HostPortPair(std::string_view in_host, uint16_t in_port)
    : port_(in_port), host_(in_host) {}
HostPortPair::HostPortPair(const char* in_host, uint16_t in_port)
    : HostPortPair(std::string_view(in_host), in_port) {}
HostPortPair::HostPortPair(std::string&& in_host, uint16_t in_port)
    : port_(in_port), host_(std::move(in_host)) {}

ProxyServer::ProxyServer(Scheme scheme, const HostPortPair& host_port_pair)
    : scheme_(scheme), host_port_pair_(host_port_pair) {
  if (scheme_ == SCHEME_INVALID) {
    host_port_pair_ = HostPortPair();
  }
}

const HostPortPair& ProxyServer::host_port_pair() const {
  return host_port_pair_;
}

int ProxyServer::GetDefaultPortForScheme(Scheme scheme) {
  return -1;
}

ProxyChain::ProxyChain() = default;
ProxyChain::ProxyChain(const ProxyChain& other) = default;
ProxyChain::ProxyChain(ProxyChain&& other) noexcept = default;
ProxyChain& ProxyChain::operator=(const ProxyChain& other) = default;
ProxyChain& ProxyChain::operator=(ProxyChain&& other) noexcept = default;
ProxyChain::~ProxyChain() = default;
ProxyChain::ProxyChain(ProxyServer::Scheme scheme,
                       const HostPortPair& host_port_pair)
    : ProxyChain(ProxyServer(scheme, host_port_pair)) {}
ProxyChain::ProxyChain(std::vector<ProxyServer> proxy_server_list)
    : proxy_server_list_(std::move(proxy_server_list)) {}
ProxyChain::ProxyChain(ProxyServer proxy_server) {
  if (proxy_server.is_valid()) {
    proxy_server_list_ = std::vector<ProxyServer>{std::move(proxy_server)};
  }
}

struct HttpResponseHeaders::ParsedHeader {
  bool operator==(const ParsedHeader&) const = default;

  size_t name_begin = 0;
  size_t name_end = 0;
  size_t value_begin = 0;
  size_t value_end = 0;
};

HttpResponseHeaders::~HttpResponseHeaders() = default;

bool HttpUtil::IsTokenChar(char c) {
  return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z') ||
         c == '!' || c == '#' || c == '$' || c == '%' || c == '&' ||
         c == '\'' || c == '*' || c == '+' || c == '-' || c == '.' ||
         c == '^' || c == '_' || c == '`' || c == '|' || c == '~';
}

bool HttpUtil::IsToken(std::string_view str) {
  if (str.empty()) {
    return false;
  }
  for (char c : str) {
    if (!IsTokenChar(c)) {
      return false;
    }
  }
  return true;
}

}  // namespace net

namespace network::mojom {

EncodedBodyLength::EncodedBodyLength() : value(0) {}
EncodedBodyLength::EncodedBodyLength(uint64_t value_in) : value(value_in) {}
EncodedBodyLength::~EncodedBodyLength() = default;

size_t EncodedBodyLength::Hash(size_t seed) const {
  seed = mojo::internal::Hash(seed, value);
  return seed;
}

void EncodedBodyLength::WriteIntoTrace(perfetto::TracedValue) const {}

ParsedHeaders::ParsedHeaders() = default;
ParsedHeaders::~ParsedHeaders() = default;

void ParsedHeaders::WriteIntoTrace(perfetto::TracedValue) const {}

SSLInfo::SSLInfo() = default;
SSLInfo::~SSLInfo() = default;

void SSLInfo::WriteIntoTrace(perfetto::TracedValue) const {}

ServiceWorkerRouterInfo::ServiceWorkerRouterInfo() = default;
ServiceWorkerRouterInfo::~ServiceWorkerRouterInfo() = default;

void ServiceWorkerRouterInfo::WriteIntoTrace(perfetto::TracedValue) const {}

DohResolutionDetails::DohResolutionDetails() = default;
DohResolutionDetails::~DohResolutionDetails() = default;

void DohResolutionDetails::WriteIntoTrace(perfetto::TracedValue) const {}

ResolutionDetails::ResolutionDetails() = default;
ResolutionDetails::~ResolutionDetails() = default;

void ResolutionDetails::WriteIntoTrace(perfetto::TracedValue) const {}

LoadTimingInternalInfo::LoadTimingInternalInfo() = default;
LoadTimingInternalInfo::~LoadTimingInternalInfo() = default;

void LoadTimingInternalInfo::WriteIntoTrace(perfetto::TracedValue) const {}

UnencodedDigests::UnencodedDigests() = default;
UnencodedDigests::~UnencodedDigests() = default;

void UnencodedDigests::WriteIntoTrace(perfetto::TracedValue) const {}

ParsedRequestCookie::ParsedRequestCookie() = default;
ParsedRequestCookie::~ParsedRequestCookie() = default;

void ParsedRequestCookie::WriteIntoTrace(perfetto::TracedValue) const {}

DeclarativePerformanceObserverPolicy::DeclarativePerformanceObserverPolicy()
    : capture_early_failures(false) {}
DeclarativePerformanceObserverPolicy::DeclarativePerformanceObserverPolicy(
    const std::optional<std::string>& reporting_endpoint_in,
    std::vector<PerformanceEntryType> entry_types_in,
    std::optional<std::vector<std::string>> include_user_timing_in,
    bool capture_early_failures_in)
    : reporting_endpoint(reporting_endpoint_in),
      entry_types(std::move(entry_types_in)),
      include_user_timing(std::move(include_user_timing_in)),
      capture_early_failures(capture_early_failures_in) {}
DeclarativePerformanceObserverPolicy::~DeclarativePerformanceObserverPolicy() =
    default;

void DeclarativePerformanceObserverPolicy::WriteIntoTrace(
    perfetto::TracedValue) const {}

NoVarySearchWithParseError::~NoVarySearchWithParseError() {}

TimingAllowOrigin::~TimingAllowOrigin() {}

DocumentIsolationPolicy::DocumentIsolationPolicy()
    : value(DocumentIsolationPolicyValue()),
      report_only_value(DocumentIsolationPolicyValue()) {}
DocumentIsolationPolicy::DocumentIsolationPolicy(
    DocumentIsolationPolicyValue value_in,
    const std::optional<std::string>& reporting_endpoint_in,
    DocumentIsolationPolicyValue report_only_value_in,
    const std::optional<std::string>& report_only_reporting_endpoint_in)
    : value(value_in),
      reporting_endpoint(reporting_endpoint_in),
      report_only_value(report_only_value_in),
      report_only_reporting_endpoint(report_only_reporting_endpoint_in) {}
DocumentIsolationPolicy::~DocumentIsolationPolicy() = default;

void DocumentIsolationPolicy::WriteIntoTrace(perfetto::TracedValue) const {}

SHA256HashValue::SHA256HashValue() = default;
SHA256HashValue::SHA256HashValue(std::vector<uint8_t> data_in)
    : data(std::move(data_in)) {}
SHA256HashValue::~SHA256HashValue() = default;

void SHA256HashValue::WriteIntoTrace(perfetto::TracedValue) const {}

}  // namespace network::mojom

namespace network::mojom::blink {

EncodedBodyLength::EncodedBodyLength() : value(0) {}
EncodedBodyLength::EncodedBodyLength(uint64_t value_in) : value(value_in) {}
EncodedBodyLength::~EncodedBodyLength() = default;

size_t EncodedBodyLength::Hash(size_t seed) const {
  seed = mojo::internal::WTFHash(seed, value);
  return seed;
}

void EncodedBodyLength::WriteIntoTrace(perfetto::TracedValue) const {}

ParsedHeaders::ParsedHeaders() = default;
ParsedHeaders::~ParsedHeaders() = default;

void ParsedHeaders::WriteIntoTrace(perfetto::TracedValue) const {}

SSLInfo::SSLInfo() = default;
SSLInfo::~SSLInfo() = default;

void SSLInfo::WriteIntoTrace(perfetto::TracedValue) const {}

ServiceWorkerRouterInfo::ServiceWorkerRouterInfo() = default;
ServiceWorkerRouterInfo::~ServiceWorkerRouterInfo() = default;

void ServiceWorkerRouterInfo::WriteIntoTrace(perfetto::TracedValue) const {}

DohResolutionDetails::DohResolutionDetails() = default;
DohResolutionDetails::~DohResolutionDetails() = default;

void DohResolutionDetails::WriteIntoTrace(perfetto::TracedValue) const {}

ResolutionDetails::ResolutionDetails() = default;
ResolutionDetails::~ResolutionDetails() = default;

void ResolutionDetails::WriteIntoTrace(perfetto::TracedValue) const {}

LoadTimingInternalInfo::LoadTimingInternalInfo() = default;
LoadTimingInternalInfo::~LoadTimingInternalInfo() = default;

void LoadTimingInternalInfo::WriteIntoTrace(perfetto::TracedValue) const {}

UnencodedDigests::UnencodedDigests() = default;
UnencodedDigests::~UnencodedDigests() = default;

void UnencodedDigests::WriteIntoTrace(perfetto::TracedValue) const {}

ParsedRequestCookie::ParsedRequestCookie() = default;
ParsedRequestCookie::~ParsedRequestCookie() = default;

void ParsedRequestCookie::WriteIntoTrace(perfetto::TracedValue) const {}

DeclarativePerformanceObserverPolicy::DeclarativePerformanceObserverPolicy()
    : capture_early_failures(false) {}
DeclarativePerformanceObserverPolicy::DeclarativePerformanceObserverPolicy(
    const ::blink::String& reporting_endpoint_in,
    ::blink::Vector<PerformanceEntryType> entry_types_in,
    std::optional<::blink::Vector<::blink::String>> include_user_timing_in,
    bool capture_early_failures_in)
    : reporting_endpoint(reporting_endpoint_in),
      entry_types(std::move(entry_types_in)),
      include_user_timing(std::move(include_user_timing_in)),
      capture_early_failures(capture_early_failures_in) {}
DeclarativePerformanceObserverPolicy::~DeclarativePerformanceObserverPolicy() =
    default;

void DeclarativePerformanceObserverPolicy::WriteIntoTrace(
    perfetto::TracedValue) const {}

NoVarySearchWithParseError::~NoVarySearchWithParseError() {}

TimingAllowOrigin::~TimingAllowOrigin() {}

DocumentIsolationPolicy::DocumentIsolationPolicy()
    : value(DocumentIsolationPolicyValue()),
      report_only_value(DocumentIsolationPolicyValue()) {}
DocumentIsolationPolicy::DocumentIsolationPolicy(
    DocumentIsolationPolicyValue value_in,
    const ::blink::String& reporting_endpoint_in,
    DocumentIsolationPolicyValue report_only_value_in,
    const ::blink::String& report_only_reporting_endpoint_in)
    : value(value_in),
      reporting_endpoint(reporting_endpoint_in),
      report_only_value(report_only_value_in),
      report_only_reporting_endpoint(report_only_reporting_endpoint_in) {}
DocumentIsolationPolicy::~DocumentIsolationPolicy() = default;

void DocumentIsolationPolicy::WriteIntoTrace(perfetto::TracedValue) const {}

SHA256HashValue::SHA256HashValue() = default;
SHA256HashValue::SHA256HashValue(::blink::Vector<uint8_t> data_in)
    : data(std::move(data_in)) {}
SHA256HashValue::~SHA256HashValue() = default;

void SHA256HashValue::WriteIntoTrace(perfetto::TracedValue) const {}

}  // namespace network::mojom::blink

namespace network::mojom::internal {

bool DataElement_Data::Validate(const void*,
                                mojo::internal::ValidationContext*,
                                bool) {
  return true;
}

bool URLRequestBody_Data::Validate(const void*,
                                   mojo::internal::ValidationContext*) {
  return true;
}
URLRequestBody_Data::URLRequestBody_Data()
    : header_({sizeof(*this), 0}),
      identifier(0),
      contains_sensitive_info(0),
      allow_http1_for_streaming_upload(0),
      padfinal_{} {}

bool DataElementBytes_Data::Validate(const void*,
                                     mojo::internal::ValidationContext*) {
  return true;
}
DataElementBytes_Data::DataElementBytes_Data()
    : header_({sizeof(*this), 0}) {}

bool DataElementFile_Data::Validate(const void*,
                                    mojo::internal::ValidationContext*) {
  return true;
}
DataElementFile_Data::DataElementFile_Data()
    : header_({sizeof(*this), 0}), offset(0), length(0) {}

bool DataElementDataPipe_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
DataElementDataPipe_Data::DataElementDataPipe_Data()
    : header_({sizeof(*this), 0}) {}

bool DataElementChunkedDataPipe_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}
DataElementChunkedDataPipe_Data::DataElementChunkedDataPipe_Data()
    : header_({sizeof(*this), 0}), read_only_once(0), padfinal_{} {}

bool AuthChallengeInfo_Data::Validate(const void*,
                                      mojo::internal::ValidationContext*) {
  return true;
}

bool HttpResponseHeaders_Data::Validate(const void*,
                                        mojo::internal::ValidationContext*) {
  return true;
}

bool EncodedBodyLength_Data::Validate(const void*,
                                      mojo::internal::ValidationContext*) {
  return true;
}

bool LoadTimingInternalInfo_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

bool SSLInfo_Data::Validate(const void*,
                            mojo::internal::ValidationContext*) {
  return true;
}

bool ParsedHeaders_Data::Validate(const void*,
                                  mojo::internal::ValidationContext*) {
  return true;
}

bool UnencodedDigests_Data::Validate(const void*,
                                     mojo::internal::ValidationContext*) {
  return true;
}

bool ParsedRequestCookie_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

bool DeclarativePerformanceObserverPolicy_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

bool NoVarySearchWithParseError_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*,
    bool) {
  return true;
}

bool TimingAllowOrigin_Data::Validate(const void*,
                                      mojo::internal::ValidationContext*,
                                      bool) {
  return true;
}

bool DocumentIsolationPolicy_Data::Validate(
    const void*,
    mojo::internal::ValidationContext*) {
  return true;
}

bool SHA256HashValue_Data::Validate(const void*,
                                    mojo::internal::ValidationContext*) {
  return true;
}

}  // namespace network::mojom::internal

namespace mojo {

bool StructTraits<network::mojom::URLRequestBodyDataView,
                  scoped_refptr<network::ResourceRequestBody>>::
    Read(network::mojom::URLRequestBodyDataView,
         scoped_refptr<network::ResourceRequestBody>* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::DataElementBytesDataView,
                  network::DataElementBytes>::
    Read(network::mojom::DataElementBytesDataView,
         network::DataElementBytes*) {
  return false;
}

bool StructTraits<network::mojom::DataElementDataPipeDataView,
                  network::DataElementDataPipe>::
    Read(network::mojom::DataElementDataPipeDataView,
         network::DataElementDataPipe*) {
  return false;
}

bool StructTraits<network::mojom::DataElementChunkedDataPipeDataView,
                  network::DataElementChunkedDataPipe>::
    Read(network::mojom::DataElementChunkedDataPipeDataView,
         network::DataElementChunkedDataPipe*) {
  return false;
}

bool StructTraits<network::mojom::DataElementFileDataView,
                  network::DataElementFile>::
    Read(network::mojom::DataElementFileDataView,
         network::DataElementFile*) {
  return false;
}

bool UnionTraits<network::mojom::DataElementDataView, network::DataElement>::
    Read(network::mojom::DataElementDataView, network::DataElement*) {
  return false;
}

bool StructTraits<network::mojom::HostPortPairDataView, net::HostPortPair>::
    Read(network::mojom::HostPortPairDataView data, net::HostPortPair* out) {
  std::string host;
  if (!data.ReadHost(&host)) {
    return false;
  }
  *out = net::HostPortPair(std::move(host), data.port());
  return true;
}

network::mojom::ProxyScheme
EnumTraits<network::mojom::ProxyScheme, net::ProxyServer::Scheme>::ToMojom(
    net::ProxyServer::Scheme scheme) {
  switch (scheme) {
    case net::ProxyServer::SCHEME_HTTP:
      return network::mojom::ProxyScheme::kHttp;
    case net::ProxyServer::SCHEME_SOCKS4:
      return network::mojom::ProxyScheme::kSocks4;
    case net::ProxyServer::SCHEME_SOCKS5:
      return network::mojom::ProxyScheme::kSocks5;
    case net::ProxyServer::SCHEME_HTTPS:
      return network::mojom::ProxyScheme::kHttps;
    case net::ProxyServer::SCHEME_QUIC:
      return network::mojom::ProxyScheme::kQuic;
    case net::ProxyServer::SCHEME_INVALID:
      return network::mojom::ProxyScheme::kInvalid;
  }
  return network::mojom::ProxyScheme::kInvalid;
}

net::ProxyServer::Scheme
EnumTraits<network::mojom::ProxyScheme, net::ProxyServer::Scheme>::FromMojom(
    network::mojom::ProxyScheme scheme) {
  switch (scheme) {
    case network::mojom::ProxyScheme::kHttp:
      return net::ProxyServer::SCHEME_HTTP;
    case network::mojom::ProxyScheme::kSocks4:
      return net::ProxyServer::SCHEME_SOCKS4;
    case network::mojom::ProxyScheme::kSocks5:
      return net::ProxyServer::SCHEME_SOCKS5;
    case network::mojom::ProxyScheme::kHttps:
      return net::ProxyServer::SCHEME_HTTPS;
    case network::mojom::ProxyScheme::kQuic:
      return net::ProxyServer::SCHEME_QUIC;
    case network::mojom::ProxyScheme::kInvalid:
      return net::ProxyServer::SCHEME_INVALID;
  }
  return net::ProxyServer::SCHEME_INVALID;
}

std::optional<net::HostPortPair>
StructTraits<network::mojom::ProxyServerDataView,
             net::ProxyServer>::host_and_port(const net::ProxyServer& server) {
  if (!server.is_valid()) {
    return std::nullopt;
  }
  return server.host_port_pair();
}

bool StructTraits<network::mojom::ProxyServerDataView, net::ProxyServer>::Read(
    network::mojom::ProxyServerDataView data,
    net::ProxyServer* out) {
  net::ProxyServer::Scheme scheme;
  if (!data.ReadScheme(&scheme)) {
    return false;
  }

  std::optional<net::HostPortPair> host_and_port;
  if (!data.ReadHostAndPort(&host_and_port)) {
    return false;
  }

  *out = net::ProxyServer(
      scheme, host_and_port.value_or(net::HostPortPair()));
  return true;
}

bool StructTraits<network::mojom::ProxyChainDataView, net::ProxyChain>::Read(
    network::mojom::ProxyChainDataView,
    net::ProxyChain* out) {
  *out = net::ProxyChain();
  return false;
}

bool StructTraits<network::mojom::HttpResponseHeadersDataView,
                  scoped_refptr<net::HttpResponseHeaders>>::
    Read(network::mojom::HttpResponseHeadersDataView,
         scoped_refptr<net::HttpResponseHeaders>* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::blink::EncodedBodyLength::DataView,
                  network::mojom::blink::EncodedBodyLengthPtr>::
    Read(network::mojom::blink::EncodedBodyLength::DataView,
         network::mojom::blink::EncodedBodyLengthPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::EncodedBodyLength::DataView,
                  network::mojom::EncodedBodyLengthPtr>::
    Read(network::mojom::EncodedBodyLength::DataView,
         network::mojom::EncodedBodyLengthPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::LoadTimingInternalInfoDataView,
                  network::mojom::blink::LoadTimingInternalInfoPtr>::
    Read(network::mojom::LoadTimingInternalInfoDataView,
         network::mojom::blink::LoadTimingInternalInfoPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::LoadTimingInternalInfoDataView,
                  network::mojom::LoadTimingInternalInfoPtr>::
    Read(network::mojom::LoadTimingInternalInfoDataView,
         network::mojom::LoadTimingInternalInfoPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::ServiceWorkerRouterInfoDataView,
                  network::mojom::blink::ServiceWorkerRouterInfoPtr>::
    Read(network::mojom::ServiceWorkerRouterInfoDataView,
         network::mojom::blink::ServiceWorkerRouterInfoPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::ServiceWorkerRouterInfoDataView,
                  network::mojom::ServiceWorkerRouterInfoPtr>::
    Read(network::mojom::ServiceWorkerRouterInfoDataView,
         network::mojom::ServiceWorkerRouterInfoPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::SSLInfoDataView,
                  network::mojom::blink::SSLInfoPtr>::
    Read(network::mojom::SSLInfoDataView,
         network::mojom::blink::SSLInfoPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::SSLInfoDataView,
                  network::mojom::SSLInfoPtr>::
    Read(network::mojom::SSLInfoDataView,
         network::mojom::SSLInfoPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::SSLInfoDataView, net::SSLInfo>::Read(
    network::mojom::SSLInfoDataView,
    net::SSLInfo*) {
  return false;
}

bool StructTraits<network::mojom::ParsedRequestCookieDataView,
                  network::mojom::blink::ParsedRequestCookiePtr>::
    Read(network::mojom::ParsedRequestCookieDataView,
         network::mojom::blink::ParsedRequestCookiePtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::ParsedRequestCookieDataView,
                  network::mojom::ParsedRequestCookiePtr>::
    Read(network::mojom::ParsedRequestCookieDataView,
         network::mojom::ParsedRequestCookiePtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::AuthChallengeInfoDataView,
                  net::AuthChallengeInfo>::
    Read(network::mojom::AuthChallengeInfoDataView,
         net::AuthChallengeInfo*) {
  return false;
}

bool StructTraits<network::mojom::ParsedHeadersDataView,
                  network::mojom::blink::ParsedHeadersPtr>::
    Read(network::mojom::ParsedHeadersDataView,
         network::mojom::blink::ParsedHeadersPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::ParsedHeadersDataView,
                  network::mojom::ParsedHeadersPtr>::
    Read(network::mojom::ParsedHeadersDataView,
         network::mojom::ParsedHeadersPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::UnencodedDigestsDataView,
                  network::mojom::blink::UnencodedDigestsPtr>::
    Read(network::mojom::UnencodedDigestsDataView,
         network::mojom::blink::UnencodedDigestsPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::UnencodedDigestsDataView,
                  network::mojom::UnencodedDigestsPtr>::
    Read(network::mojom::UnencodedDigestsDataView,
         network::mojom::UnencodedDigestsPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<
         network::mojom::blink::DeclarativePerformanceObserverPolicy::DataView,
         network::mojom::blink::DeclarativePerformanceObserverPolicyPtr>::
    Read(network::mojom::blink::DeclarativePerformanceObserverPolicy::DataView,
         network::mojom::blink::DeclarativePerformanceObserverPolicyPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<
         network::mojom::DeclarativePerformanceObserverPolicy::DataView,
         network::mojom::DeclarativePerformanceObserverPolicyPtr>::
    Read(network::mojom::DeclarativePerformanceObserverPolicy::DataView,
         network::mojom::DeclarativePerformanceObserverPolicyPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::blink::DocumentIsolationPolicy::DataView,
                  network::mojom::blink::DocumentIsolationPolicyPtr>::
    Read(network::mojom::blink::DocumentIsolationPolicy::DataView,
         network::mojom::blink::DocumentIsolationPolicyPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::DocumentIsolationPolicy::DataView,
                  network::mojom::DocumentIsolationPolicyPtr>::
    Read(network::mojom::DocumentIsolationPolicy::DataView,
         network::mojom::DocumentIsolationPolicyPtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::blink::SHA256HashValue::DataView,
                  network::mojom::blink::SHA256HashValuePtr>::
    Read(network::mojom::blink::SHA256HashValue::DataView,
         network::mojom::blink::SHA256HashValuePtr* out) {
  out->reset();
  return false;
}

bool StructTraits<network::mojom::SHA256HashValue::DataView,
                  network::mojom::SHA256HashValuePtr>::
    Read(network::mojom::SHA256HashValue::DataView,
         network::mojom::SHA256HashValuePtr* out) {
  out->reset();
  return false;
}

}  // namespace mojo

namespace perfetto {

void TraceFormatTraits<network::mojom::RequestPriority>::WriteIntoTrace(
    TracedValue,
    network::mojom::RequestPriority) {}

void TraceFormatTraits<network::mojom::FetchPriorityAttribute>::WriteIntoTrace(
    TracedValue,
    network::mojom::FetchPriorityAttribute) {}

void TraceFormatTraits<network::mojom::AlternateProtocolUsage>::WriteIntoTrace(
    TracedValue,
    network::mojom::AlternateProtocolUsage) {}

void TraceFormatTraits<network::mojom::SourceType>::WriteIntoTrace(
    TracedValue,
    network::mojom::SourceType) {}

void TraceFormatTraits<network::mojom::DeviceBoundSessionUsage>::WriteIntoTrace(
    TracedValue,
    network::mojom::DeviceBoundSessionUsage) {}

void TraceFormatTraits<network::mojom::WebClientHintsType>::WriteIntoTrace(
    TracedValue,
    network::mojom::WebClientHintsType) {}

void TraceFormatTraits<network::mojom::StorageAccessApiStatus>::WriteIntoTrace(
    TracedValue,
    network::mojom::StorageAccessApiStatus) {}

void TraceFormatTraits<
    network::mojom::DocumentIsolationPolicyValue>::WriteIntoTrace(
    TracedValue,
    network::mojom::DocumentIsolationPolicyValue) {}

}  // namespace perfetto
