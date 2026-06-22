// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/frame.h"
#include "third_party/blink/renderer/core/loader/empty_clients.h"

#include <memory>
#include <vector>

#include "build/build_config.h"
#include "cc/layers/layer.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"
#include "third_party/blink/renderer/core/html/forms/color_chooser.h"
#include "third_party/blink/renderer/core/html/forms/date_time_chooser.h"
#include "third_party/blink/renderer/core/html/forms/file_chooser.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"
#include "third_party/blink/renderer/core/html/forms/html_opt_group_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/popup_menu.h"
#include "third_party/blink/renderer/core/html/html_hr_element.h"
#include "third_party/blink/renderer/core/layout/layout_object.h"

#if BUILDFLAG(IS_WIN)
#include <windows.h>
#endif

namespace blink {

#if BUILDFLAG(IS_WIN)
extern "C" void* StandaloneRendererNativeWindowHandleForStandaloneRenderer();

namespace {

std::wstring StandalonePopupLabel(const String& label) {
  if (label.empty()) {
    return std::wstring();
  }

  std::wstring result;
  result.reserve(label.length());
  if (label.Is8Bit()) {
    for (LChar character : label.Span8()) {
      result.push_back(static_cast<wchar_t>(character));
    }
    return result;
  }

  for (UChar character : label.Span16()) {
    result.push_back(static_cast<wchar_t>(character));
  }
  return result;
}

class StandaloneWinPopupMenu final : public PopupMenu {
 public:
  explicit StandaloneWinPopupMenu(HTMLSelectElement& owner_element)
      : owner_element_(owner_element) {}

  void Trace(Visitor* visitor) const override {
    visitor->Trace(owner_element_);
    PopupMenu::Trace(visitor);
  }

  void Show(ShowEventType) override {
    if (!owner_element_) {
      return;
    }
    HWND hwnd = static_cast<HWND>(
        StandaloneRendererNativeWindowHandleForStandaloneRenderer());
    if (!hwnd) {
      owner_element_->PopupDidHide();
      return;
    }

    HMENU menu = CreatePopupMenu();
    if (!menu) {
      owner_element_->PopupDidHide();
      return;
    }

    std::vector<int> list_indices_by_command;
    constexpr UINT kCommandBase = 1000;
    const HTMLSelectElement::ListItems& items = owner_element_->GetListItems();
    for (wtf_size_t i = 0; i < items.size(); ++i) {
      HTMLElement* item = items[i].Get();
      if (!item ||
          owner_element_->ItemIsDisplayNone(*item, /*ensure_style=*/true)) {
        continue;
      }

      if (IsA<HTMLHRElement>(*item)) {
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        continue;
      }

      UINT flags = MF_STRING;
      if (item->IsDisabledFormControl() || IsA<HTMLOptGroupElement>(*item)) {
        flags |= MF_GRAYED;
      }
      if (auto* option = DynamicTo<HTMLOptionElement>(item);
          option && option->Selected()) {
        flags |= MF_CHECKED;
      }

      const UINT command =
          kCommandBase + static_cast<UINT>(list_indices_by_command.size());
      list_indices_by_command.push_back(static_cast<int>(i));
      std::wstring label = StandalonePopupLabel(owner_element_->ItemText(*item));
      if (label.empty() && IsA<HTMLOptGroupElement>(*item)) {
        label = L" ";
      }
      AppendMenuW(menu, flags, command, label.c_str());
    }

    gfx::Rect select_rect = owner_element_->VisibleBoundsInLocalRoot();
    POINT point{select_rect.x(), select_rect.bottom()};
    ClientToScreen(hwnd, &point);
    const UINT command = TrackPopupMenuEx(
        menu,
        TPM_RETURNCMD | TPM_LEFTALIGN | TPM_TOPALIGN | TPM_LEFTBUTTON |
            TPM_RIGHTBUTTON,
        point.x, point.y, hwnd, nullptr);
    DestroyMenu(menu);

    HTMLSelectElement* owner = owner_element_;
    if (command >= kCommandBase) {
      const size_t index = command - kCommandBase;
      if (index < list_indices_by_command.size()) {
        owner->SelectOptionByPopup(list_indices_by_command[index]);
      }
    } else {
      owner->PopupDidCancel();
    }
    if (LayoutObject* layout_object = owner->GetLayoutObject()) {
      layout_object->SetShouldDoFullPaintInvalidation();
    }
    owner->PopupDidHide();
  }

  void Hide() override {
    if (owner_element_) {
      owner_element_->PopupDidHide();
    }
  }

  void UpdateFromElement(UpdateReason) override {}

  void DisconnectClient() override { owner_element_ = nullptr; }

 private:
  Member<HTMLSelectElement> owner_element_;
};

}  // namespace
#endif

ChromeClient& GetStaticEmptyChromeClientInstance() {
  DEFINE_STATIC_LOCAL(Persistent<ChromeClient>, chrome_client,
                      (MakeGarbageCollected<EmptyChromeClient>()));
  return *chrome_client;
}

PopupMenu* EmptyChromeClient::OpenPopupMenu(LocalFrame&,
                                            HTMLSelectElement& select) {
#if BUILDFLAG(IS_WIN)
  return MakeGarbageCollected<StandaloneWinPopupMenu>(select);
#else
  return nullptr;
#endif
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
