#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_PARAMS_MOJOM_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_PARAMS_MOJOM_FORWARD_H_

#include "third_party/blink/public/mojom/navigation/navigation_params.mojom-shared.h"

namespace blink::mojom {

struct CommonNavigationParams;
struct CommitNavigationParams;
struct BeginNavigationParams;
using CommonNavigationParamsPtr = CommonNavigationParams*;
using CommitNavigationParamsPtr = CommitNavigationParams*;
using BeginNavigationParamsPtr = BeginNavigationParams*;

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_NAVIGATION_NAVIGATION_PARAMS_MOJOM_FORWARD_H_
