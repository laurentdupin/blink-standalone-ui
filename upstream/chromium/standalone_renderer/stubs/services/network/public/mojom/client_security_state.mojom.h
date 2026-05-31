#ifndef STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CLIENT_SECURITY_STATE_MOJOM_H_
#define STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CLIENT_SECURITY_STATE_MOJOM_H_

#include <memory>
#include <utility>

#include "services/network/public/mojom/cross_origin_embedder_policy.mojom-shared.h"
#include "services/network/public/mojom/web_sandbox_flags.mojom-shared.h"

namespace network::mojom {

struct ClientSecurityState {
  std::unique_ptr<ClientSecurityState> Clone() const {
    return std::make_unique<ClientSecurityState>(*this);
  }
};

class ClientSecurityStatePtr {
 public:
  ClientSecurityStatePtr() = default;
  ClientSecurityStatePtr(std::nullptr_t) {}
  explicit ClientSecurityStatePtr(std::unique_ptr<ClientSecurityState> value)
      : value_(std::move(value)) {}

  ClientSecurityStatePtr(const ClientSecurityStatePtr& other)
      : value_(other.value_ ? other.value_->Clone() : nullptr) {}
  ClientSecurityStatePtr& operator=(const ClientSecurityStatePtr& other) {
    value_ = other.value_ ? other.value_->Clone() : nullptr;
    return *this;
  }
  ClientSecurityStatePtr(ClientSecurityStatePtr&&) = default;
  ClientSecurityStatePtr& operator=(ClientSecurityStatePtr&&) = default;
  ClientSecurityStatePtr& operator=(std::nullptr_t) {
    value_.reset();
    return *this;
  }

  explicit operator bool() const { return !!value_; }
  ClientSecurityState* get() const { return value_.get(); }
  ClientSecurityState* operator->() const { return value_.get(); }
  ClientSecurityState& operator*() const { return *value_; }
  std::unique_ptr<ClientSecurityState> Clone() const {
    return value_ ? value_->Clone() : nullptr;
  }

 private:
  std::unique_ptr<ClientSecurityState> value_;
};

}  // namespace network::mojom

#endif  // STANDALONE_RENDERER_STUBS_SERVICES_NETWORK_PUBLIC_MOJOM_CLIENT_SECURITY_STATE_MOJOM_H_
