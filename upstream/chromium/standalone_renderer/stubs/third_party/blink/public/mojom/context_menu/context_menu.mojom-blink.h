// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTEXT_MENU_CONTEXT_MENU_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTEXT_MENU_CONTEXT_MENU_MOJOM_BLINK_H_

#include <optional>
#include <memory>
#include <utility>

#include "mojo/public/cpp/bindings/message.h"
#include "third_party/blink/public/mojom/context_menu/context_menu.mojom-blink-forward.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace blink {
struct Impression;
}  // namespace blink

namespace blink::mojom::blink {

class ContextMenuClient {
 public:
  static constexpr const char Name_[] = "blink.mojom.ContextMenuClient";
  static constexpr uint32_t Version_ = 0;
  static constexpr bool PassesAssociatedKinds_ = false;
  using IPCStableHashFunction = uint32_t (*)(::mojo::Message&);

  class Proxy_ {};
  virtual ~ContextMenuClient() = default;
  virtual void CustomContextMenuAction(uint32_t) {}
  virtual void ContextMenuClosed(const KURL&,
                                 const std::optional<::blink::Impression>&) {}

  class RequestValidator_ : public ::mojo::MessageReceiver {
   public:
    bool Accept(::mojo::Message*) override { return true; }
  };
  class ResponseValidator_ : public ::mojo::MessageReceiver {
   public:
    bool Accept(::mojo::Message*) override { return true; }
  };

  static IPCStableHashFunction MessageToMethodInfo_(::mojo::Message&) {
    return nullptr;
  }
  static const char* MessageToMethodName_(::mojo::Message&) { return ""; }

  template <typename ImplRefTraits>
  class Stub_ : public ::mojo::MessageReceiverWithResponderStatus {
   public:
    using ImplPointerType = typename ImplRefTraits::PointerType;
    void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
    ImplPointerType& sink() { return sink_; }
    bool Accept(::mojo::Message*) override { return true; }
    bool AcceptWithResponder(
        ::mojo::Message*,
        std::unique_ptr<::mojo::MessageReceiverWithStatus>) override {
      return true;
    }
    bool PrefersSerializedMessages() override { return false; }

   private:
    ImplPointerType sink_{};
  };
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTEXT_MENU_CONTEXT_MENU_MOJOM_BLINK_H_
