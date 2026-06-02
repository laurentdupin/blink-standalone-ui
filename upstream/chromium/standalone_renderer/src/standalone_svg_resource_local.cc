// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/svg/svg_resource.h"

#include "third_party/blink/renderer/core/dom/element.h"
#include "third_party/blink/renderer/core/dom/id_target_observer.h"
#include "third_party/blink/renderer/core/dom/tree_scope.h"
#include "third_party/blink/renderer/core/layout/svg/layout_svg_resource_container.h"
#include "third_party/blink/renderer/core/loader/resource/image_resource_observer.h"
#include "third_party/blink/renderer/core/svg/svg_resource_client.h"
#include "third_party/blink/renderer/core/svg/svg_uri_reference.h"

namespace blink {

SVGResource::SVGResource() = default;

SVGResource::~SVGResource() = default;

void SVGResource::Trace(Visitor* visitor) const {
  visitor->Trace(target_);
  visitor->Trace(clients_);
  visitor->Trace(observer_wrappers_);
}

void SVGResource::AddClient(SVGResourceClient& client) {
  auto& entry = clients_.insert(&client, ClientEntry()).stored_value->value;
  entry.count++;
  entry.cached_cycle_check = kNeedCheck;
  if (LayoutSVGResourceContainer* container = ResourceContainerNoCycleCheck()) {
    container->ClearInvalidationMask();
  }
}

void SVGResource::RemoveClient(SVGResourceClient& client) {
  auto it = clients_.find(&client);
  CHECK_NE(it, clients_.end());
  it->value.count--;
  if (it->value.count) {
    return;
  }
  clients_.erase(it);
  if (LayoutSVGResourceContainer* container = ResourceContainerNoCycleCheck()) {
    container->RemoveClientFromCache(client);
  }
}

class SVGResource::ImageResourceObserverWrapper
    : public GarbageCollected<SVGResource::ImageResourceObserverWrapper>,
      public SVGResourceClient {
 public:
  explicit ImageResourceObserverWrapper(ImageResourceObserver& observer)
      : observer_(observer) {}

  void IncRef() { count_++; }
  bool DecRef() {
    --count_;
    return count_ == 0;
  }

  void Trace(Visitor* visitor) const override {
    visitor->Trace(observer_);
    SVGResourceClient::Trace(visitor);
  }

 private:
  void ResourceContentChanged(SVGResource* resource) override {
    observer_->ImageChanged(static_cast<WrappedImagePtr>(resource),
                            ImageResourceObserver::CanDeferInvalidation::kNo);
  }

  Member<ImageResourceObserver> observer_;
  int count_ = 0;
};

void SVGResource::AddObserver(ImageResourceObserver& observer) {
  auto& wrapper =
      observer_wrappers_.insert(&observer, nullptr).stored_value->value;
  if (!wrapper) {
    wrapper = MakeGarbageCollected<ImageResourceObserverWrapper>(observer);
    AddClient(*wrapper);
  }
  wrapper->IncRef();
}

void SVGResource::RemoveObserver(ImageResourceObserver& observer) {
  auto it = observer_wrappers_.find(&observer);
  CHECK_NE(it, observer_wrappers_.end());
  if (it->value->DecRef()) {
    RemoveClient(*it->value);
    observer_wrappers_.erase(it);
  }
}

SVGResourceClient* SVGResource::GetObserverResourceClient(
    ImageResourceObserver& observer) {
  auto it = observer_wrappers_.find(&observer);
  return it != observer_wrappers_.end() ? it->value : nullptr;
}

void SVGResource::InvalidateCycleCache() {
  for (auto& client_entry : clients_.Values()) {
    client_entry.cached_cycle_check = kNeedCheck;
  }
}

void SVGResource::NotifyContentChanged() {
  InvalidateCycleCache();

  HeapVector<Member<SVGResourceClient>> clients(clients_.Keys());
  for (SVGResourceClient* client : clients) {
    client->ResourceContentChanged(this);
  }
}

LayoutSVGResourceContainer* SVGResource::ResourceContainerNoCycleCheck() const {
  if (!target_) {
    return nullptr;
  }
  return DynamicTo<LayoutSVGResourceContainer>(target_->GetLayoutObject());
}

LayoutSVGResourceContainer* SVGResource::ResourceContainer(
    SVGResourceClient& client) const {
  auto it = clients_.find(&client);
  if (it == clients_.end()) {
    return nullptr;
  }
  auto* container = ResourceContainerNoCycleCheck();
  if (!container) {
    return nullptr;
  }
  ClientEntry& entry = it->value;
  if (entry.cached_cycle_check == kNeedCheck) {
    entry.cached_cycle_check = kPerformingCheck;
    bool has_cycle = container->FindCycle();
    DCHECK_EQ(entry.cached_cycle_check, kPerformingCheck);
    entry.cached_cycle_check = has_cycle ? kHasCycle : kNoCycle;
  }
  if (entry.cached_cycle_check == kHasCycle) {
    return nullptr;
  }
  DCHECK_EQ(entry.cached_cycle_check, kNoCycle);
  return container;
}

bool SVGResource::FindCycle(SVGResourceClient& client) const {
  auto it = clients_.find(&client);
  if (it == clients_.end()) {
    return false;
  }
  auto* container = ResourceContainerNoCycleCheck();
  if (!container) {
    return false;
  }
  ClientEntry& entry = it->value;
  switch (entry.cached_cycle_check) {
    case kNeedCheck: {
      entry.cached_cycle_check = kPerformingCheck;
      bool has_cycle = container->FindCycle();
      DCHECK_EQ(entry.cached_cycle_check, kPerformingCheck);
      entry.cached_cycle_check = has_cycle ? kHasCycle : kNoCycle;
      return false;
    }
    case kNoCycle: {
      entry.cached_cycle_check = kPerformingCheck;
      bool has_cycle = container->FindCycle();
      DCHECK_EQ(entry.cached_cycle_check, kPerformingCheck);
      entry.cached_cycle_check = kNoCycle;
      return has_cycle;
    }
    case kPerformingCheck:
      return true;
    case kHasCycle:
      return false;
  }
}

LocalSVGResource::LocalSVGResource(TreeScope& tree_scope, const AtomicString& id)
    : tree_scope_(tree_scope) {
  target_ = SVGURIReference::ObserveTarget(
      id_observer_, tree_scope, id,
      BindRepeating(&LocalSVGResource::TargetChanged, WrapWeakPersistent(this),
                    id));
}

void LocalSVGResource::Unregister() {
  SVGURIReference::UnobserveTarget(id_observer_);
}

void LocalSVGResource::NotifyFilterPrimitiveChanged(
    SVGFilterPrimitiveStandardAttributes& primitive,
    const QualifiedName& attribute) {
  HeapVector<Member<SVGResourceClient>> clients(clients_.Keys());
  for (SVGResourceClient* client : clients) {
    client->FilterPrimitiveChanged(this, primitive, attribute);
  }
}

void LocalSVGResource::TargetChanged(const AtomicString& id) {
  Element* new_target = tree_scope_->getElementById(id);
  if (new_target == target_) {
    return;
  }
  LayoutSVGResourceContainer* old_resource = ResourceContainerNoCycleCheck();
  if (old_resource) {
    old_resource->RemoveAllClientsFromCache();
  }
  target_ = new_target;
  NotifyContentChanged();
}

void LocalSVGResource::Trace(Visitor* visitor) const {
  visitor->Trace(tree_scope_);
  visitor->Trace(id_observer_);
  SVGResource::Trace(visitor);
}

}  // namespace blink
