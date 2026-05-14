// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REMOTE_FRAME_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REMOTE_FRAME_MOJOM_BLINK_H_

#include <optional>

#include "base/unguessable_token.h"
#include "third_party/blink/public/common/tokens/tokens.h"
#include "third_party/blink/public/mojom/frame/frame_owner_properties.mojom-blink.h"
#include "third_party/blink/public/mojom/frame/frame_replication_state.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/fullscreen.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/remote_frame.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/tree_scope_type.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/user_activation_notification_type.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/frame/user_activation_update_types.mojom-shared.h"
#include "third_party/blink/public/mojom/input/scroll_direction.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/scroll/scroll_into_view_params.mojom-blink.h"
#include "third_party/blink/public/mojom/security_context/insecure_request_policy.mojom-blink-forward.h"
#include "third_party/blink/public/mojom/timing/resource_timing.mojom-blink-forward.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "ui/events/types/scroll_types.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/rect_f.h"
#include "ui/gfx/geometry/size.h"

namespace cc {
class RenderFrameMetadata;
}  // namespace cc

namespace network {
struct ParsedPermissionsPolicyDeclaration;
}  // namespace network

namespace viz {
class FrameSinkId;
}  // namespace viz

namespace blink {
class Frame;
struct FramePolicy;
class SecurityOrigin;
}  // namespace blink

namespace blink::mojom::blink {

struct IntrinsicSizingInfo {};
using IntrinsicSizingInfoPtr = std::unique_ptr<IntrinsicSizingInfo>;

struct FrameReplicationState {};

class RemoteMainFrame {
 public:
  class Proxy_ {};
  virtual ~RemoteMainFrame() = default;
};

class RemoteFrame {
 public:
  class Proxy_ {};
  virtual ~RemoteFrame() = default;

  virtual void AddResourceTimingFromChild(ResourceTimingInfoPtr) {}
  virtual void WillEnterFullscreen(FullscreenOptionsPtr) {}
  virtual void EnforceInsecureNavigationsSet(const Vector<uint32_t>&) {}
  virtual void SetFrameOwnerProperties(FrameOwnerPropertiesPtr) {}
  virtual void EnforceInsecureRequestPolicy(InsecureRequestPolicy) {}
  virtual void SetReplicatedOrigin(
      const scoped_refptr<const ::blink::SecurityOrigin>&,
      bool) {}
  virtual void SetReplicatedIsAdFrame(bool) {}
  virtual void SetReplicatedName(const String&, const String&) {}
  virtual void DispatchLoadEventForFrameOwner() {}
  virtual void Collapse(bool) {}
  virtual void Focus() {}
  virtual void SetHadStickyUserActivationBeforeNavigation(bool) {}
  virtual void SetNeedsOcclusionTracking(bool) {}
  virtual void BubbleLogicalScroll(ScrollDirection,
                                   ui::ScrollGranularity) {}
  virtual void UpdateUserActivationState(UserActivationUpdateType,
                                         UserActivationNotificationType) {}
  virtual void SetEmbeddingToken(const base::UnguessableToken&) {}
  virtual void SetPageFocus(bool) {}
  virtual void RenderFallbackContent() {}
  virtual void ScrollRectToVisible(const gfx::RectF&,
                                   ScrollIntoViewParamsPtr) {}
  virtual void DidStartLoading() {}
  virtual void DidStopLoading() {}
  virtual void IntrinsicSizingInfoOfChildChanged(IntrinsicSizingInfoPtr) {}
  virtual void DidSetFramePolicyHeaders(
      network::mojom::blink::WebSandboxFlags,
      const Vector<network::ParsedPermissionsPolicyDeclaration>&) {}
  virtual void DidUpdateFramePolicy(const ::blink::FramePolicy&) {}
  virtual void UpdateOpener(const std::optional<::blink::FrameToken>&) {}
  virtual void DetachAndDispose() {}
  virtual void EnableAutoResize(const gfx::Size&, const gfx::Size&) {}
  virtual void DisableAutoResize() {}
  virtual void DidUpdateVisualProperties(const cc::RenderFrameMetadata&) {}
  virtual void SetFrameSinkId(const viz::FrameSinkId&, bool) {}
  virtual void ChildProcessGone() {}
  virtual void CreateRemoteChild(
      const ::blink::RemoteFrameToken&,
      const std::optional<::blink::FrameToken>&,
      TreeScopeType,
      FrameReplicationStatePtr,
      FrameOwnerPropertiesPtr,
      bool,
      const base::UnguessableToken&,
      RemoteFrameInterfacesFromBrowserPtr) {}
  virtual void CreateRemoteChildren(
      Vector<CreateRemoteChildParamsPtr>,
      const std::optional<base::UnguessableToken>&) {}
  virtual gfx::Size GetOutermostMainFrameSize() const { return gfx::Size(); }
  virtual gfx::Point GetOutermostMainFrameScrollPosition() const {
    return gfx::Point();
  }
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FRAME_REMOTE_FRAME_MOJOM_BLINK_H_
