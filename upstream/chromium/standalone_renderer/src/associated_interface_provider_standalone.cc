// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/public/common/associated_interfaces/associated_interface_provider.h"

namespace blink {

class AssociatedInterfaceProvider::LocalProvider {};

AssociatedInterfaceProvider::AssociatedInterfaceProvider(
    mojo::PendingAssociatedRemote<mojom::AssociatedInterfaceProvider> proxy,
    scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : task_runner_(std::move(task_runner)) {}

AssociatedInterfaceProvider::AssociatedInterfaceProvider(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner)
    : task_runner_(std::move(task_runner)) {}

AssociatedInterfaceProvider::~AssociatedInterfaceProvider() = default;

void AssociatedInterfaceProvider::GetInterface(
    const std::string&,
    mojo::ScopedInterfaceEndpointHandle) {}

void AssociatedInterfaceProvider::OverrideBinderForTesting(
    const std::string&,
    const base::RepeatingCallback<void(mojo::ScopedInterfaceEndpointHandle)>&) {
}

AssociatedInterfaceProvider*
AssociatedInterfaceProvider::GetEmptyAssociatedInterfaceProvider() {
  static AssociatedInterfaceProvider* provider =
      new AssociatedInterfaceProvider(scoped_refptr<base::SingleThreadTaskRunner>());
  return provider;
}

}  // namespace blink
