// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_REGISTRY_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_REGISTRY_MOJOM_BLINK_H_

#include <cstdint>

#include "mojo/public/cpp/bindings/message.h"
#include "mojo/public/cpp/bindings/message_metadata_helpers.h"
#include "third_party/blink/public/mojom/blob/blob_registry.mojom-blink-forward.h"

namespace blink::mojom::blink {

class BlobRegistry {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.BlobRegistry";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;

  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };

  class Proxy_ {
   public:
    template <typename... Args>
    explicit Proxy_(Args&&...) {}

    template <typename... Args>
    void RegisterFromStream(Args&&...) {}
  };
  virtual ~BlobRegistry() = default;

  template <typename... Args>
  void RegisterFromStream(Args&&...) {}
};

class ProgressClient {
 public:
  static constexpr bool PassesAssociatedKinds_ = false;
  static constexpr bool HasUninterruptableMethods_ = false;
  static constexpr uint32_t Version_ = 0;
  static constexpr const char Name_[] = "blink.mojom.ProgressClient";
  static constexpr mojo::MessageToMethodInfoCallback MessageToMethodInfo_ =
      nullptr;
  static constexpr mojo::MessageToMethodNameCallback MessageToMethodName_ =
      nullptr;

  template <typename ImplRefTraits>
  class Stub_ : public mojo::MessageReceiverWithResponderStatus {
   public:
    using ImplPointerType = typename ImplRefTraits::PointerType;
    Stub_() = default;

    void set_sink(ImplPointerType sink) { sink_ = std::move(sink); }
    ImplPointerType& sink() { return sink_; }

    bool Accept(mojo::Message*) override { return true; }
    bool AcceptWithResponder(mojo::Message*,
                             std::unique_ptr<mojo::MessageReceiverWithStatus>)
        override {
      return true;
    }

   private:
    ImplPointerType sink_;
  };

  class RequestValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };

  class ResponseValidator_ : public mojo::MessageReceiver {
   public:
    bool Accept(mojo::Message*) override { return true; }
  };

  class Proxy_ {
   public:
    template <typename... Args>
    explicit Proxy_(Args&&...) {}
  };
  virtual ~ProgressClient() = default;
  virtual void OnProgress(uint64_t delta) = 0;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_BLOB_BLOB_REGISTRY_MOJOM_BLINK_H_
