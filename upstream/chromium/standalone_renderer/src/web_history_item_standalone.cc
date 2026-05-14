// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/public/web/web_history_item.h"

#include "third_party/blink/public/platform/web_http_body.h"
#include "third_party/blink/renderer/core/loader/history_item.h"

namespace blink {

WebHistoryItem::WebHistoryItem(const PageState&) {}

WebHistoryItem::WebHistoryItem(const WebString& url,
                               const WebString& navigation_api_key,
                               const WebString& navigation_api_id,
                               int64_t item_sequence_number,
                               int64_t document_sequence_number,
                               const WebString&) {
  private_ = MakeGarbageCollected<HistoryItem>();
  private_->SetURLString(url);
  private_->SetNavigationApiKey(navigation_api_key);
  private_->SetNavigationApiId(navigation_api_id);
  private_->SetItemSequenceNumber(item_sequence_number);
  private_->SetDocumentSequenceNumber(document_sequence_number);
}

void WebHistoryItem::Reset() {
  private_.Reset();
}

void WebHistoryItem::Assign(const WebHistoryItem& other) {
  private_ = other.private_;
}

int64_t WebHistoryItem::ItemSequenceNumber() const {
  return private_ ? private_->ItemSequenceNumber() : 0;
}

int64_t WebHistoryItem::DocumentSequenceNumber() const {
  return private_ ? private_->DocumentSequenceNumber() : 0;
}

WebHTTPBody WebHistoryItem::HttpBody() const {
  return WebHTTPBody();
}

WebString WebHistoryItem::GetNavigationApiKey() const {
  if (!private_) {
    return WebString();
  }
  return WebString(private_->GetNavigationApiKey());
}

WebHistoryItem::WebHistoryItem(HistoryItem* item) : private_(item) {}

WebHistoryItem& WebHistoryItem::operator=(HistoryItem* item) {
  private_ = item;
  return *this;
}

WebHistoryItem::operator HistoryItem*() const {
  return private_.Get();
}

}  // namespace blink
