// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/frame/frame.h"
#include "third_party/blink/renderer/core/loader/empty_clients.h"

#include <memory>
#include <cstring>
#include <string>
#include <vector>

#include "cc/layers/layer.h"
#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"
#include "third_party/blink/renderer/core/html/forms/color_chooser.h"
#include "third_party/blink/renderer/core/html/forms/date_time_chooser.h"
#include "third_party/blink/renderer/core/html/forms/file_chooser.h"
#include "third_party/blink/renderer/core/html/forms/html_form_element.h"
#include "third_party/blink/renderer/core/html/forms/html_select_element.h"
#include "third_party/blink/renderer/core/html/forms/html_option_element.h"
#include "third_party/blink/renderer/core/html/html_hr_element.h"
#include "third_party/blink/renderer/core/html/forms/html_opt_group_element.h"
#include "third_party/blink/renderer/platform/wtf/casting.h"
#include "third_party/blink/renderer/platform/wtf/vector.h"
#include "ui/gfx/geometry/rect.h"

namespace blink {

namespace {

std::string BlinkStringToStdStringForStandalonePopup(const String& value) {
  return value.Utf8();
}

struct StandaloneSelectPopupItem {
  int list_index = -1;
  std::string label;
  bool enabled = false;
  bool selected = false;
  bool separator = false;
  bool group = false;
};

struct StandaloneSelectPopupState {
  Persistent<HTMLSelectElement> owner;
  std::vector<StandaloneSelectPopupItem> items;
  gfx::Rect anchor_bounds;
  int selected_list_index = -1;
  bool open = false;
};

StandaloneSelectPopupState& SelectPopupStateForStandaloneRenderer() {
  static StandaloneSelectPopupState state;
  return state;
}

void RefreshSelectPopupStateForStandaloneRenderer(HTMLSelectElement& select) {
  StandaloneSelectPopupState& state = SelectPopupStateForStandaloneRenderer();
  state.owner = &select;
  state.items.clear();
  state.anchor_bounds = select.VisibleBoundsInLocalRoot();
  state.selected_list_index = select.SelectedListIndex();
  const HTMLSelectElement::ListItems& items = select.GetListItems();
  for (wtf_size_t i = 0; i < items.size(); ++i) {
    HTMLElement* item_element = items[i].Get();
    if (!item_element) {
      continue;
    }
    StandaloneSelectPopupItem item;
    item.list_index = static_cast<int>(i);
    item.label =
        BlinkStringToStdStringForStandalonePopup(select.ItemText(*item_element));
    item.separator = IsA<HTMLHRElement>(item_element);
    item.group = IsA<HTMLOptGroupElement>(item_element);
    item.enabled = !item_element->IsDisabledFormControl() && !item.separator &&
                   !item.group;
    if (auto* option = DynamicTo<HTMLOptionElement>(item_element)) {
      item.selected = option->Selected();
    }
    state.items.push_back(std::move(item));
  }
  state.open = true;
}

bool ShowSelectPopupForStandaloneRenderer(HTMLSelectElement& select) {
  RefreshSelectPopupStateForStandaloneRenderer(select);
  return SelectPopupStateForStandaloneRenderer().open &&
         !SelectPopupStateForStandaloneRenderer().items.empty();
}

void CloseSelectPopupStateForStandaloneRenderer(bool notify_owner) {
  StandaloneSelectPopupState& state = SelectPopupStateForStandaloneRenderer();
  HTMLSelectElement* owner = state.owner.Get();
  state.open = false;
  state.items.clear();
  state.selected_list_index = -1;
  state.anchor_bounds = gfx::Rect();
  state.owner = nullptr;
  if (notify_owner && owner) {
    owner->PopupDidHide();
  }
}

}  // namespace

bool StandaloneSelectPopupOpenForStandaloneRenderer() {
  return SelectPopupStateForStandaloneRenderer().open;
}

void StandaloneSelectPopupAnchorBoundsForStandaloneRenderer(float* x,
                                                            float* y,
                                                            float* width,
                                                            float* height) {
  const gfx::Rect& bounds =
      SelectPopupStateForStandaloneRenderer().anchor_bounds;
  if (x) {
    *x = static_cast<float>(bounds.x());
  }
  if (y) {
    *y = static_cast<float>(bounds.y());
  }
  if (width) {
    *width = static_cast<float>(bounds.width());
  }
  if (height) {
    *height = static_cast<float>(bounds.height());
  }
}

int StandaloneSelectPopupSelectedListIndexForStandaloneRenderer() {
  return SelectPopupStateForStandaloneRenderer().selected_list_index;
}

int StandaloneSelectPopupItemCountForStandaloneRenderer() {
  return static_cast<int>(SelectPopupStateForStandaloneRenderer().items.size());
}

int StandaloneSelectPopupItemAtForStandaloneRenderer(int item_index,
                                                     int* list_index,
                                                     char* label,
                                                     int label_capacity,
                                                     int* enabled,
                                                     int* selected,
                                                     int* separator,
                                                     int* group) {
  const auto& items = SelectPopupStateForStandaloneRenderer().items;
  if (item_index < 0 || static_cast<size_t>(item_index) >= items.size()) {
    return 0;
  }
  const StandaloneSelectPopupItem& item = items[static_cast<size_t>(item_index)];
  if (list_index) {
    *list_index = item.list_index;
  }
  if (label && label_capacity > 0) {
    const size_t copied =
        std::min(item.label.size(), static_cast<size_t>(label_capacity - 1));
    std::memcpy(label, item.label.data(), copied);
    label[copied] = '\0';
  }
  if (enabled) {
    *enabled = item.enabled ? 1 : 0;
  }
  if (selected) {
    *selected = item.selected ? 1 : 0;
  }
  if (separator) {
    *separator = item.separator ? 1 : 0;
  }
  if (group) {
    *group = item.group ? 1 : 0;
  }
  return 1;
}

int StandaloneSelectPopupApplyChoiceForStandaloneRenderer(int list_index,
                                                          int cancel) {
  StandaloneSelectPopupState& state = SelectPopupStateForStandaloneRenderer();
  HTMLSelectElement* owner = state.owner.Get();
  if (!state.open || !owner) {
    CloseSelectPopupStateForStandaloneRenderer(false);
    return 0;
  }

  if (cancel) {
    CloseSelectPopupStateForStandaloneRenderer(false);
    return 1;
  }

  bool enabled_choice = false;
  for (const StandaloneSelectPopupItem& item : state.items) {
    if (item.list_index == list_index) {
      enabled_choice = item.enabled;
      break;
    }
  }
  if (!enabled_choice) {
    return 0;
  }

  owner->SelectOptionByPopup(list_index);
  CloseSelectPopupStateForStandaloneRenderer(false);
  return 1;
}

void StandaloneSelectPopupClearForStandaloneRenderer() {
  CloseSelectPopupStateForStandaloneRenderer(false);
}

bool StandaloneSelectPopupShowForStandaloneRenderer(HTMLSelectElement& select) {
  return ShowSelectPopupForStandaloneRenderer(select);
}

ChromeClient& GetStaticEmptyChromeClientInstance() {
  DEFINE_STATIC_LOCAL(Persistent<ChromeClient>, chrome_client,
                      (MakeGarbageCollected<EmptyChromeClient>()));
  return *chrome_client;
}

class StandaloneSelectPopupMenu final : public PopupMenu {
 public:
  explicit StandaloneSelectPopupMenu(HTMLSelectElement& owner)
      : owner_(&owner) {}

  void Trace(Visitor* visitor) const override {
    visitor->Trace(owner_);
    PopupMenu::Trace(visitor);
  }

  void Show(ShowEventType) override {
    if (owner_) {
      RefreshSelectPopupStateForStandaloneRenderer(*owner_);
    }
  }

  void Hide() override { CloseSelectPopupStateForStandaloneRenderer(true); }

  void UpdateFromElement(UpdateReason) override {
    if (owner_) {
      RefreshSelectPopupStateForStandaloneRenderer(*owner_);
    }
  }

  void DisconnectClient() override {
    owner_ = nullptr;
    CloseSelectPopupStateForStandaloneRenderer(false);
  }

 private:
  Member<HTMLSelectElement> owner_;
};

PopupMenu* EmptyChromeClient::OpenPopupMenu(LocalFrame&,
                                            HTMLSelectElement& select) {
  return MakeGarbageCollected<StandaloneSelectPopupMenu>(select);
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
