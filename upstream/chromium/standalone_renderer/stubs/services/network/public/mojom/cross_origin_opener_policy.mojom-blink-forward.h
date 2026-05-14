#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CROSS_ORIGIN_OPENER_POLICY_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CROSS_ORIGIN_OPENER_POLICY_MOJOM_BLINK_FORWARD_H_

namespace network::mojom {

enum class CoopAccessReportType {
  kAccessFromCoopPageToOpener,
  kAccessFromCoopPageToOpenee,
  kAccessFromCoopPageToOther,
  kAccessToCoopPageFromOpener,
  kAccessToCoopPageFromOpenee,
  kAccessToCoopPageFromOther,
};

enum class CrossOriginOpenerPolicyValue {
  kUnsafeNone,
  kSameOriginAllowPopups,
  kSameOrigin,
  kSameOriginPlusCoep,
  kNoopenerAllowPopups,
};

class CrossOriginOpenerPolicyReporter;
struct CrossOriginOpenerPolicy;
struct CrossOriginOpenerPolicyReporterParams;
using CrossOriginOpenerPolicyReporterParamsPtr =
    CrossOriginOpenerPolicyReporterParams*;

}  // namespace network::mojom

namespace network::mojom::blink {

enum class CoopAccessReportType {
  kAccessFromCoopPageToOpener,
  kAccessFromCoopPageToOpenee,
  kAccessFromCoopPageToOther,
  kAccessToCoopPageFromOpener,
  kAccessToCoopPageFromOpenee,
  kAccessToCoopPageFromOther,
};

enum class CrossOriginOpenerPolicyValue {
  kUnsafeNone,
  kSameOriginAllowPopups,
  kSameOrigin,
  kSameOriginPlusCoep,
  kNoopenerAllowPopups,
};

class CrossOriginOpenerPolicyReporter;
struct CrossOriginOpenerPolicy;
struct CrossOriginOpenerPolicyReporterParams;
using CrossOriginOpenerPolicyReporterParamsPtr =
    CrossOriginOpenerPolicyReporterParams*;

}  // namespace network::mojom::blink

namespace blink::network::mojom::blink {

using CoopAccessReportType = ::network::mojom::blink::CoopAccessReportType;
using CrossOriginOpenerPolicyValue =
    ::network::mojom::blink::CrossOriginOpenerPolicyValue;
using CrossOriginOpenerPolicyReporter =
    ::network::mojom::blink::CrossOriginOpenerPolicyReporter;
using CrossOriginOpenerPolicyReporterParams =
    ::network::mojom::blink::CrossOriginOpenerPolicyReporterParams;
using CrossOriginOpenerPolicyReporterParamsPtr =
    ::network::mojom::blink::CrossOriginOpenerPolicyReporterParamsPtr;

}  // namespace blink::network::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CROSS_ORIGIN_OPENER_POLICY_MOJOM_BLINK_FORWARD_H_
