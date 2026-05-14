#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_POLICY_DOCUMENT_POLICY_FEATURE_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_PERMISSIONS_POLICY_DOCUMENT_POLICY_FEATURE_MOJOM_BLINK_FORWARD_H_
namespace blink::mojom::blink {
enum class DocumentPolicyFeature {
  kForceLoadAtTop,
  kSyncXHR,
  kNetworkEfficiencyGuardrails,
  kExpectNoLinkedResources,
  kMaxValue = kExpectNoLinkedResources,
};
}
#endif
