// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/frame.h"
#include "third_party/blink/renderer/core/loader/empty_clients.h"

#include <memory>

#include "cc/layers/layer.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"
#include "third_party/blink/renderer/core/html/forms/color_chooser.h"
#include "third_party/blink/renderer/core/html/forms/date_time_chooser.h"
#include "third_party/blink/renderer/core/html/forms/file_chooser.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"

namespace blink {

ChromeClient& GetStaticEmptyChromeClientInstance() {
  DEFINE_STATIC_LOCAL(Persistent<ChromeClient>, chrome_client,
                      (MakeGarbageCollected<EmptyChromeClient>()));
  return *chrome_client;
}

class EmptyPopupMenu final : public PopupMenu {
 public:
  void Show(ShowEventType) override {}
  void Hide() override {}
  void UpdateFromElement(UpdateReason) override {}
  void DisconnectClient() override {}
};

PopupMenu* EmptyChromeClient::OpenPopupMenu(LocalFrame&, HTMLSelectElement&) {
  return MakeGarbageCollected<EmptyPopupMenu>();
}

ColorChooser* EmptyChromeClient::OpenColorChooser(LocalFrame*,
                                                  ColorChooserClient*,
                                                  const Color&) {
  return nullptr;
}

DateTimeChooser* EmptyChromeClient::OpenDateTimeChooser(
    LocalFrame*,
    DateTimeChooserClient*,
    const DateTimeChooserParameters&) {
  return nullptr;
}

std::unique_ptr<cc::ScopedPauseRendering> EmptyChromeClient::PauseRendering(
    LocalFrame&) {
  return nullptr;
}

std::optional<int> EmptyChromeClient::GetMaxRenderBufferBounds(
    LocalFrame&) const {
  return std::nullopt;
}

void EmptyChromeClient::OpenTextDataListChooser(HTMLInputElement&) {}

void EmptyChromeClient::OpenFileChooser(LocalFrame*,
                                        scoped_refptr<FileChooser>) {}

void EmptyChromeClient::AttachRootLayer(scoped_refptr<cc::Layer>,
                                        LocalFrame*) {}

bool EmptyChromeClient::StartDeferringCommits(LocalFrame&,
                                              base::TimeDelta,
                                              cc::PaintHoldingReason) {
  return false;
}

void EmptyLocalFrameClient::BeginNavigation(
    const ResourceRequest&,
    const KURL&,
    mojom::RequestContextFrameType,
    LocalDOMWindow*,
    DocumentLoader*,
    WebNavigationType,
    NavigationPolicy,
    WebFrameLoadType,
    mojom::blink::ForceHistoryPush,
    bool,
    bool,
    mojom::blink::TriggeringEventInfo,
    HTMLFormElement*,
    network::mojom::CSPDisposition,
    mojo::PendingRemote<mojom::blink::BlobURLToken>,
    base::TimeTicks,
    base::TimeTicks,
    const String&,
    const std::optional<Impression>&,
    const LocalFrameToken*,
    SourceLocation*,
    mojo::PendingRemote<mojom::blink::NavigationStateKeepAliveHandle>,
    bool,
    bool,
    mojo::PendingReceiver<mojom::blink::NavigationResumeDeferredCommitListener>,
    std::optional<base::UnguessableToken>) {}

void EmptyLocalFrameClient::DispatchWillSendSubmitEvent(HTMLFormElement*) {}

LocalFrame* EmptyLocalFrameClient::CreateFrame(const AtomicString&,
                                               HTMLFrameOwnerElement*) {
  return nullptr;
}

RemoteFrame* EmptyLocalFrameClient::CreateFencedFrame(
    HTMLFencedFrameElement*,
    mojo::PendingAssociatedReceiver<mojom::blink::FencedFrameOwnerHost>) {
  return nullptr;
}

WebPluginContainerImpl* EmptyLocalFrameClient::CreatePlugin(
    HTMLPlugInElement&,
    const KURL&,
    const Vector<String>&,
    const Vector<String>&,
    const String&,
    bool) {
  return nullptr;
}

std::unique_ptr<WebMediaPlayer> EmptyLocalFrameClient::CreateWebMediaPlayer(
    HTMLMediaElement&,
    const WebMediaPlayerSource&,
    WebMediaPlayerClient*) {
  return nullptr;
}

RemotePlaybackClient* EmptyLocalFrameClient::CreateRemotePlaybackClient(
    HTMLMediaElement&) {
  return nullptr;
}

WebTextCheckClient* EmptyLocalFrameClient::GetTextCheckerClient() const {
  return text_check_client_;
}

void EmptyLocalFrameClient::SetTextCheckerClientForTesting(
    WebTextCheckClient* client) {
  text_check_client_ = client;
}

Frame* EmptyLocalFrameClient::FindFrame(const AtomicString&) const {
  return nullptr;
}

AssociatedInterfaceProvider*
EmptyLocalFrameClient::GetRemoteNavigationAssociatedInterfaces() {
  if (!associated_interface_provider_) {
    associated_interface_provider_ =
        std::make_unique<AssociatedInterfaceProvider>(
            scoped_refptr<base::SingleThreadTaskRunner>());
  }
  return associated_interface_provider_.get();
}

std::unique_ptr<WebServiceWorkerProvider>
EmptyLocalFrameClient::CreateServiceWorkerProvider() {
  return nullptr;
}

}  // namespace blink
