// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Phase 1 renders local/static resources through the standalone loader. Blink's
// preload helper otherwise opens script/module/prefetch/dictionary/Link-header
// machinery and network side effects, so keep it inert here.

#include "third_party/blink/renderer/core/loader/preload_helper.h"

#include "third_party/blink/renderer/core/loader/alternate_signed_exchange_resource_info.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

void PreloadHelper::LoadLinksFromHeader(
    const String&,
    const KURL&,
    LocalFrame&,
    Document*,
    LoadLinksFromHeaderMode,
    const ViewportDescription*,
    std::unique_ptr<AlternateSignedExchangeResourceInfo>,
    const base::UnguessableToken*) {}

Resource* PreloadHelper::StartPreload(ResourceType,
                                      FetchParameters&,
                                      Document&) {
  return nullptr;
}

void PreloadHelper::DnsPrefetchIfNeeded(const LinkLoadParameters&,
                                        Document*,
                                        LocalFrame*,
                                        LinkCaller) {}

void PreloadHelper::PreconnectIfNeeded(const LinkLoadParameters&,
                                       Document*,
                                       LocalFrame*,
                                       LinkCaller) {}

void PreloadHelper::PrefetchIfNeeded(const LinkLoadParameters&,
                                     Document&,
                                     PendingLinkPreload*) {}

void PreloadHelper::PreloadIfNeeded(const LinkLoadParameters&,
                                    Document&,
                                    const KURL&,
                                    LinkCaller,
                                    const ViewportDescription*,
                                    ParserDisposition,
                                    PendingLinkPreload*) {}

void PreloadHelper::ModulePreloadIfNeeded(const LinkLoadParameters&,
                                          Document&,
                                          const ViewportDescription*,
                                          PendingLinkPreload*) {}

void PreloadHelper::FetchCompressionDictionaryIfNeeded(
    const LinkLoadParameters&,
    Document&,
    PendingLinkPreload*) {}

std::optional<ResourceType> PreloadHelper::GetResourceTypeFromAsAttribute(
    const String& as) {
  if (as == "image") {
    return ResourceType::kImage;
  }
  if (as == "style") {
    return ResourceType::kCSSStyleSheet;
  }
  if (as == "font") {
    return ResourceType::kFont;
  }
  if (as == "fetch") {
    return ResourceType::kRaw;
  }
  if (as == "script") {
    return ResourceType::kScript;
  }
  if (as == "track") {
    return ResourceType::kTextTrack;
  }
  return std::nullopt;
}

String PreloadHelper::GetAsAttributeFromResourceType(ResourceType type) {
  switch (type) {
    case ResourceType::kImage:
      return "image";
    case ResourceType::kCSSStyleSheet:
      return "style";
    case ResourceType::kFont:
      return "font";
    case ResourceType::kRaw:
      return "fetch";
    case ResourceType::kScript:
      return "script";
    case ResourceType::kTextTrack:
      return "track";
    default:
      return String();
  }
}

}  // namespace blink
