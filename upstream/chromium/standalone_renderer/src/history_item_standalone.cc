// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/loader/history_item.h"

#include "third_party/blink/renderer/bindings/core/v8/serialization/serialized_script_value.h"
#include "third_party/blink/renderer/platform/network/encoded_form_data.h"
#include "third_party/blink/renderer/platform/weborigin/security_origin.h"
#include "third_party/blink/renderer/platform/weborigin/kurl.h"

namespace blink {

HistoryItem* HistoryItem::Create(const PageState&) {
  return MakeGarbageCollected<HistoryItem>();
}

HistoryItem::HistoryItem()
    : item_sequence_number_(0), document_sequence_number_(0) {}

HistoryItem::~HistoryItem() = default;

const String& HistoryItem::UrlString() const {
  return url_string_;
}

KURL HistoryItem::Url() const {
  return KURL(url_string_);
}

const String& HistoryItem::GetReferrer() const {
  return referrer_;
}

network::mojom::ReferrerPolicy HistoryItem::GetReferrerPolicy() const {
  return referrer_policy_;
}

EncodedFormData* HistoryItem::FormData() const {
  return form_data_.get();
}

const AtomicString& HistoryItem::FormContentType() const {
  return form_content_type_;
}

void HistoryItem::SetVisualViewportScrollOffset(const ScrollOffset& offset) {
  GetOrCreateViewState().visual_viewport_scroll_offset_ = offset;
}

void HistoryItem::SetScrollOffset(const ScrollOffset& offset) {
  GetOrCreateViewState().scroll_offset_ = offset;
}

void HistoryItem::SetPageScaleFactor(float scale) {
  GetOrCreateViewState().page_scale_factor_ = scale;
}

Vector<String> HistoryItem::GetReferencedFilePaths() const {
  return {};
}

const Vector<String>& HistoryItem::GetDocumentState() const {
  return document_state_vector_;
}

void HistoryItem::SetDocumentState(const Vector<String>& state) {
  document_state_vector_ = state;
}

void HistoryItem::SetDocumentState(DocumentState*) {}

void HistoryItem::ClearDocumentState() {
  document_state_vector_.clear();
  document_state_ = nullptr;
}

void HistoryItem::SetURL(const KURL& url) {
  url_string_ = url.GetString();
}

void HistoryItem::SetURLString(const String& url) {
  url_string_ = url;
}

void HistoryItem::SetReferrer(const String& referrer) {
  referrer_ = referrer;
}

void HistoryItem::SetRequestorOrigin(
    const scoped_refptr<const SecurityOrigin>& origin) {
  requestor_origin_ = origin;
}

void HistoryItem::SetReferrerPolicy(network::mojom::ReferrerPolicy policy) {
  referrer_policy_ = policy;
}

void HistoryItem::SetStateObject(scoped_refptr<SerializedScriptValue> value) {
  state_object_ = std::move(value);
}

void HistoryItem::SetScrollAnchorData(const ScrollAnchorData& data) {
  GetOrCreateViewState().scroll_anchor_data_ = data;
}

void HistoryItem::SetFormData(scoped_refptr<EncodedFormData> data) {
  form_data_ = std::move(data);
}

void HistoryItem::SetFormContentType(const AtomicString& type) {
  form_content_type_ = type;
}

void HistoryItem::SetNavigationApiState(
    scoped_refptr<SerializedScriptValue> value) {
  navigation_api_state_ = std::move(value);
}

void HistoryItem::Trace(Visitor* visitor) const {
  (void)visitor;
}

std::vector<std::optional<std::u16string>>
HistoryItem::GetReferencedFilePathsForSerialization() const {
  return {};
}

HistoryItem::ViewState& HistoryItem::GetOrCreateViewState() {
  if (!view_state_) {
    view_state_.emplace();
  }
  return *view_state_;
}

}  // namespace blink
