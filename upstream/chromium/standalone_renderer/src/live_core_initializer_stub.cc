// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// Standalone renderer replacement for the modules-side CoreInitializer.
// Blink core calls this singleton from frame/page construction to let modules
// install browser-facing supplements. The standalone renderer denies those
// services and keeps the core frame/document/lifecycle path available.

#include "third_party/blink/renderer/core/core_initializer.h"

#include <memory>

#include "base/notreached.h"
#include "third_party/blink/public/platform/web_string.h"
#include "third_party/blink/renderer/core/event_target_names.h"
#include "third_party/blink/renderer/core/event_type_names.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/core/html_tokenizer_names.h"
#include "third_party/blink/renderer/core/mathml_names.h"
#include "third_party/blink/renderer/core/svg_names.h"
#include "third_party/blink/renderer/core/trustedtypes/trusted_types_names.h"
#include "third_party/blink/renderer/core/xlink_names.h"
#include "third_party/blink/renderer/core/xml_names.h"
#include "third_party/blink/renderer/core/xmlns_names.h"
#include "third_party/blink/renderer/platform/font_family_names.h"
#include "third_party/blink/renderer/platform/loader/fetch/fetch_initiator_type_names.h"
#include "third_party/blink/renderer/platform/network/http_names.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string.h"
#include "third_party/blink/renderer/platform/wtf/text/atomic_string_table.h"
#include "third_party/blink/renderer/platform/wtf/text/string_impl.h"

namespace blink {

namespace {

class StandaloneCoreInitializer final : public CoreInitializer {
 public:
  void RegisterInterfaces(mojo::BinderMap&) override {}
  void InitLocalFrame(LocalFrame&) const override {}
  void InitServiceWorkerGlobalScope(ServiceWorkerGlobalScope&) const override {}
  void InstallSupplements(LocalFrame&) const override {}
  MediaControls* CreateMediaControls(HTMLMediaElement&, ShadowRoot&) const override {
    return nullptr;
  }
  PictureInPictureController* CreatePictureInPictureController(
      Document&) const override {
    return nullptr;
  }
  void InitInspectorAgentSession(DevToolsSession*,
                                 InspectorDOMAgent*,
                                 InspectedFrames*,
                                 Page*) const override {}
  void InitWorkerInspectorAgentSession(DevToolsSession*,
                                       WorkerGlobalScope*) const override {}
  void OnClearWindowObjectInMainWorld(Document&, const Settings&) const override {}
  std::unique_ptr<WebMediaPlayer> CreateWebMediaPlayer(
      WebLocalFrameClient*,
      HTMLMediaElement&,
      const WebMediaPlayerSource&,
      WebMediaPlayerClient*) const override {
    return nullptr;
  }
  RemotePlaybackClient* CreateRemotePlaybackClient(
      HTMLMediaElement&) const override {
    return nullptr;
  }
  void ProvideModulesToPage(Page&,
                            const SessionStorageNamespaceId&) const override {}
  void ForceNextWebGLContextCreationToFail() const override {}
  void CollectAllGarbageForAnimationAndPaintWorkletForTesting()
      const override {}
  void CloneSessionStorage(Page*,
                           const SessionStorageNamespaceId&) override {}
  void EvictSessionStorageCachedData(Page*) override {}
  void DidChangeManifest(LocalFrame&) override {}
  void NotifyOrientationChanged(LocalFrame&) override {}
  void DidUpdateScreens(LocalFrame&, const display::ScreenInfos&) override {}
  void SetLocalStorageArea(
      LocalFrame&,
      mojo::PendingRemote<mojom::blink::StorageArea>) override {}
  void SetSessionStorageArea(
      LocalFrame&,
      mojo::PendingRemote<mojom::blink::StorageArea>) override {}
  mojom::blink::FileSystemManager& GetFileSystemManager(
      ExecutionContext*) override {
    NOTREACHED();
    static mojom::blink::FileSystemManager* manager = nullptr;
    return *manager;
  }
};

StandaloneCoreInitializer g_standalone_core_initializer;

}  // namespace

CoreInitializer* CoreInitializer::instance_ = &g_standalone_core_initializer;

void ForceNextWebGLContextCreationToFailForTest() {
  CoreInitializer::GetInstance().ForceNextWebGLContextCreationToFail();
}

void CoreInitializer::Initialize() {
  static bool initialized = false;
  if (initialized)
    return;
  initialized = true;

  const unsigned kQualifiedNamesCount =
      html_names::kTagsCount + html_names::kAttrsCount +
      mathml_names::kTagsCount + mathml_names::kAttrsCount +
      svg_names::kTagsCount + svg_names::kAttrsCount +
      xlink_names::kAttrsCount + xml_names::kAttrsCount +
      xmlns_names::kAttrsCount;

  const unsigned kCoreStaticStringsCount =
      kQualifiedNamesCount + event_target_names::kNamesCount +
      event_type_names::kNamesCount + fetch_initiator_type_names::kNamesCount +
      html_tokenizer_names::kNamesCount + trusted_types_names::kNamesCount;

  StringImpl::ReserveStaticStringsCapacityForSize(
      kCoreStaticStringsCount + StringImpl::AllStaticStrings().size());
  QualifiedName::InitAndReserveCapacityForSize(kQualifiedNamesCount);
  AtomicStringTable::Instance().ReserveCapacity(kCoreStaticStringsCount);

  html_names::Init();
  mathml_names::Init();
  svg_names::Init();
  xlink_names::Init();
  xml_names::Init();
  xmlns_names::Init();

  event_target_names::Init();
  event_type_names::Init();
  html_tokenizer_names::Init();
  trusted_types_names::Init();
}

}  // namespace blink
