// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/loader/fetch/policy_container_utils.h"

#include "base/containers/to_vector.h"
#include "services/network/public/mojom/content_security_policy.mojom-blink.h"
#include "third_party/blink/public/mojom/frame/policy_container.mojom-blink.h"
#include "third_party/blink/public/platform/web_content_security_policy_struct.h"
#include "third_party/blink/public/platform/web_string.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace blink {

namespace {

WebCSPSource ConvertSource(const network::mojom::blink::CSPSourcePtr& source) {
  return {source->scheme,
          source->host,
          source->port,
          source->path,
          source->is_host_wildcard,
          source->is_port_wildcard};
}

network::IntegrityMetadata ConvertIntegrityMetadata(
    const network::mojom::blink::IntegrityMetadataPtr& metadata) {
  if (!metadata) {
    return network::IntegrityMetadata();
  }
  return network::IntegrityMetadata(
      metadata->algorithm,
      base::span<const uint8_t>(metadata->value.data(),
                                metadata->value.size()));
}

WebCSPSourceList ConvertSourceList(
    const network::mojom::blink::CSPSourceListPtr& source_list) {
  return {base::ToVector(source_list->sources, ConvertSource),
          base::ToVector(source_list->nonces, ToWebString),
          base::ToVector(source_list->hashes, ConvertIntegrityMetadata),
          base::ToVector(source_list->url_hashes, ConvertIntegrityMetadata),
          base::ToVector(source_list->eval_hashes, ConvertIntegrityMetadata),
          source_list->allow_self,
          source_list->allow_star,
          source_list->allow_inline,
          source_list->allow_inline_speculation_rules,
          source_list->allow_eval,
          source_list->allow_wasm_eval,
          source_list->allow_wasm_unsafe_eval,
          source_list->allow_dynamic,
          source_list->allow_dynamic_url,
          source_list->allow_unsafe_hashes,
          source_list->report_sample,
          source_list->allow_trusted_types_eval,
          source_list->report_hash_algorithm};
}

std::optional<WebCSPTrustedTypes> ConvertTrustedTypes(
    const network::mojom::blink::CSPTrustedTypesPtr& trusted_types) {
  if (!trusted_types) {
    return std::nullopt;
  }
  return WebCSPTrustedTypes{base::ToVector(trusted_types->list, ToWebString),
                            trusted_types->allow_any,
                            trusted_types->allow_duplicates};
}

std::optional<network::ConnectionAllowlist> ConvertConnectionAllowlist(
    const network::mojom::blink::ConnectionAllowlistPtr& allowlist) {
  if (!allowlist) {
    return std::nullopt;
  }

  network::ConnectionAllowlist converted;
  converted.allowlist = base::ToVector(
      allowlist->allowlist,
      [](const String& item) { return std::string(item.Utf8()); });
  if (!allowlist->reporting_endpoint.empty()) {
    converted.reporting_endpoint =
        std::string(allowlist->reporting_endpoint.Utf8());
  }
  converted.issues = base::ToVector(allowlist->issues);
  converted.redirect_behavior =
      allowlist->redirect_behavior == network::mojom::RedirectBehavior::kAllow
          ? network::ConnectionAllowlist::RedirectBehavior::kAllow
          : network::ConnectionAllowlist::RedirectBehavior::kBlock;
  converted.webrtc_behavior =
      allowlist->webrtc_behavior == network::mojom::WebRtcBehavior::kAllow
          ? network::ConnectionAllowlist::WebRtcBehavior::kAllow
          : network::ConnectionAllowlist::WebRtcBehavior::kBlock;
  return converted;
}

network::ConnectionAllowlists ConvertConnectionAllowlists(
    const network::mojom::blink::ConnectionAllowlistsPtr& allowlists) {
  network::ConnectionAllowlists converted;
  if (!allowlists) {
    return converted;
  }
  converted.response_url = static_cast<GURL>(allowlists->response_url);
  converted.enforced = ConvertConnectionAllowlist(allowlists->enforced);
  converted.report_only = ConvertConnectionAllowlist(allowlists->report_only);
  converted.reporting_source = allowlists->reporting_source;
  return converted;
}

network::IntegrityPolicy ConvertIntegrityPolicy(
    const network::mojom::blink::IntegrityPolicyPtr& policy) {
  network::IntegrityPolicy converted;
  if (!policy) {
    return converted;
  }
  converted.blocked_destinations = base::ToVector(policy->blocked_destinations);
  converted.sources = base::ToVector(policy->sources);
  converted.endpoints = base::ToVector(
      policy->endpoints,
      [](const String& endpoint) { return std::string(endpoint.Utf8()); });
  converted.parsing_errors = base::ToVector(
      policy->parsing_errors,
      [](const String& error) { return std::string(error.Utf8()); });
  return converted;
}

network::mojom::blink::ConnectionAllowlistsPtr
ConvertConnectionAllowlistsToMojoBlink(
    const network::ConnectionAllowlists& allowlists);
network::mojom::blink::IntegrityPolicyPtr ConvertIntegrityPolicyToMojoBlink(
    const network::IntegrityPolicy& policy);

}  // namespace

WebContentSecurityPolicy ToWebContentSecurityPolicy(
    const network::mojom::blink::ContentSecurityPolicy& policy) {
  return {
      ConvertSource(policy.self_origin),
      base::ToVector(policy.raw_directives,
                     [](const auto& directive) {
                       return WebContentSecurityPolicyRawDirective{
                           directive.key, directive.value};
                     }),
      base::ToVector(policy.directives,
                     [](const auto& directive) {
                       return WebContentSecurityPolicyDirective{
                           directive.key, ConvertSourceList(directive.value)};
                     }),
      policy.upgrade_insecure_requests,
      policy.treat_as_public_address,
      policy.block_all_mixed_content,
      policy.sandbox,
      {policy.header->header_value, policy.header->type, policy.header->source},
      policy.use_reporting_api,
      base::ToVector(policy.report_endpoints, ToWebString),
      policy.require_trusted_types_for,
      ConvertTrustedTypes(policy.trusted_types),
      base::ToVector(policy.parsing_errors, ToWebString)};
}

WebPolicyContainerPolicies ToWebPolicyContainerPolicies(
    const mojom::blink::PolicyContainerPolicies& policies) {
  WebPolicyContainerPolicies web_policies;
  web_policies.connection_allowlists =
      ConvertConnectionAllowlists(policies.connection_allowlists);
  if (policies.cross_origin_embedder_policy) {
    web_policies.cross_origin_embedder_policy =
        policies.cross_origin_embedder_policy->value;
  }
  web_policies.integrity_policy =
      ConvertIntegrityPolicy(policies.integrity_policy);
  web_policies.integrity_policy_report_only =
      ConvertIntegrityPolicy(policies.integrity_policy_report_only);
  web_policies.referrer_policy = policies.referrer_policy;
  web_policies.content_security_policies = base::ToVector(
      policies.content_security_policies,
      [](const auto& content_security_policy) {
        return ToWebContentSecurityPolicy(*content_security_policy);
      });
  web_policies.is_credentialless = policies.is_credentialless;
  web_policies.sandbox_flags = policies.sandbox_flags;
  web_policies.ip_address_space = policies.ip_address_space;
  web_policies.can_navigate_top_without_user_gesture =
      policies.can_navigate_top_without_user_gesture;
  web_policies.cross_origin_isolation_enabled_by_dip =
      policies.cross_origin_isolation_enabled_by_dip;
  return web_policies;
}

mojom::blink::PolicyContainerPoliciesPtr FromWebPolicyContainerPolicies(
    const WebPolicyContainerPolicies& policies) {
  return mojom::blink::PolicyContainerPolicies::New(
      ConvertConnectionAllowlistsToMojoBlink(policies.connection_allowlists),
      network::mojom::blink::CrossOriginEmbedderPolicy::New(
          policies.cross_origin_embedder_policy, String(),
          network::mojom::CrossOriginEmbedderPolicyValue::kNone, String()),
      ConvertIntegrityPolicyToMojoBlink(policies.integrity_policy),
      ConvertIntegrityPolicyToMojoBlink(policies.integrity_policy_report_only),
      policies.referrer_policy,
      ToVector(policies.content_security_policies,
               FromWebContentSecurityPolicy),
      policies.is_credentialless, policies.sandbox_flags,
      policies.ip_address_space, policies.can_navigate_top_without_user_gesture,
      policies.cross_origin_isolation_enabled_by_dip);
}

namespace {

network::mojom::blink::CSPSourcePtr ConvertSourceToMojoBlink(
    const WebCSPSource& source) {
  return network::mojom::blink::CSPSource::New(
      source.scheme, source.host, source.port, source.path,
      source.is_host_wildcard, source.is_port_wildcard);
}

network::mojom::blink::IntegrityMetadataPtr ConvertIntegrityMetadataToMojoBlink(
    const network::IntegrityMetadata& metadata) {
  return network::mojom::blink::IntegrityMetadata::New(
      metadata.algorithm,
      Vector<uint8_t>(base::span<const uint8_t>(metadata.value.data(),
                                                metadata.value.size())));
}

network::mojom::blink::ConnectionAllowlistPtr
ConvertConnectionAllowlistToMojoBlink(
    const std::optional<network::ConnectionAllowlist>& allowlist) {
  if (!allowlist) {
    return nullptr;
  }
  return network::mojom::blink::ConnectionAllowlist::New(
      ToVector(allowlist->allowlist,
               [](const std::string& item) { return String::FromUtf8(item); }),
      allowlist->reporting_endpoint
          ? String::FromUtf8(*allowlist->reporting_endpoint)
          : String(),
      ToVector(allowlist->issues),
      allowlist->redirect_behavior ==
              network::ConnectionAllowlist::RedirectBehavior::kAllow
          ? network::mojom::RedirectBehavior::kAllow
          : network::mojom::RedirectBehavior::kBlock,
      allowlist->webrtc_behavior ==
              network::ConnectionAllowlist::WebRtcBehavior::kAllow
          ? network::mojom::WebRtcBehavior::kAllow
          : network::mojom::WebRtcBehavior::kBlock);
}

network::mojom::blink::ConnectionAllowlistsPtr
ConvertConnectionAllowlistsToMojoBlink(
    const network::ConnectionAllowlists& allowlists) {
  return network::mojom::blink::ConnectionAllowlists::New(
      KURL(allowlists.response_url),
      ConvertConnectionAllowlistToMojoBlink(allowlists.enforced),
      ConvertConnectionAllowlistToMojoBlink(allowlists.report_only),
      allowlists.reporting_source);
}

network::mojom::blink::IntegrityPolicyPtr ConvertIntegrityPolicyToMojoBlink(
    const network::IntegrityPolicy& policy) {
  return network::mojom::blink::IntegrityPolicy::New(
      ToVector(policy.blocked_destinations),
      ToVector(policy.sources),
      ToVector(policy.endpoints, [](const std::string& endpoint) {
        return String::FromUtf8(endpoint);
      }),
      ToVector(policy.parsing_errors, [](const std::string& error) {
        return String::FromUtf8(error);
      }));
}

network::mojom::blink::CSPSourceListPtr ConvertSourceListToMojoBlink(
    const WebCSPSourceList& source_list) {
  return network::mojom::blink::CSPSourceList::New(
      ToVector(source_list.sources, ConvertSourceToMojoBlink),
      Vector<String>(source_list.nonces),
      ToVector(source_list.hashes, ConvertIntegrityMetadataToMojoBlink),
      ToVector(source_list.url_hashes, ConvertIntegrityMetadataToMojoBlink),
      ToVector(source_list.eval_hashes, ConvertIntegrityMetadataToMojoBlink),
      source_list.allow_self, source_list.allow_star, source_list.allow_inline,
      source_list.allow_inline_speculation_rules, source_list.allow_eval,
      source_list.allow_wasm_eval, source_list.allow_wasm_unsafe_eval,
      source_list.allow_dynamic, source_list.allow_dynamic_url,
      source_list.allow_unsafe_hashes, source_list.report_sample,
      source_list.allow_trusted_types_eval, source_list.report_hash_algorithm);
}

}  // namespace

network::mojom::blink::ContentSecurityPolicyPtr FromWebContentSecurityPolicy(
    const WebContentSecurityPolicy& policy_in) {
  HashMap<network::mojom::CSPDirectiveName, String> raw_directives;
  for (const auto& directive : policy_in.raw_directives) {
    raw_directives.insert(directive.name, directive.value);
  }

  HashMap<network::mojom::CSPDirectiveName,
          network::mojom::blink::CSPSourceListPtr>
      directives;
  for (const auto& directive : policy_in.directives) {
    directives.insert(directive.name,
                      ConvertSourceListToMojoBlink(directive.source_list));
  }

  return network::mojom::blink::ContentSecurityPolicy::New(
      ConvertSourceToMojoBlink(policy_in.self_origin),
      std::move(raw_directives), std::move(directives),
      policy_in.upgrade_insecure_requests, policy_in.treat_as_public_address,
      policy_in.block_all_mixed_content, policy_in.sandbox,
      network::mojom::blink::ContentSecurityPolicyHeader::New(
          policy_in.header.header_value, policy_in.header.type,
          policy_in.header.source),
      policy_in.use_reporting_api, Vector<String>(policy_in.report_endpoints),
      policy_in.require_trusted_types_for,
      policy_in.trusted_types
          ? network::mojom::blink::CSPTrustedTypes::New(
                Vector<String>(policy_in.trusted_types->list),
                policy_in.trusted_types->allow_any,
                policy_in.trusted_types->allow_duplicates)
          : nullptr,
      Vector<String>(policy_in.parsing_errors));
}

}  // namespace blink
