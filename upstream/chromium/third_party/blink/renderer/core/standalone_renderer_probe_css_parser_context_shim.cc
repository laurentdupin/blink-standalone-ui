// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/core/css/parser/css_parser_context.h"

#include "third_party/blink/renderer/core/execution_context/security_context.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"

namespace blink {

CSSParserContext::CSSParserContext(const CSSParserContext* other,
                                   const Document* use_counter_document)
    : CSSParserContext(other->base_url_,
                       other->origin_clean_,
                       other->charset_,
                       other->mode_,
                       other->referrer_,
                       other->is_html_document_,
                       other->secure_context_mode_,
                       other->world_.Get(),
                       use_counter_document,
                       other->resource_fetch_restriction_) {
  is_ad_related_ = other->is_ad_related_;
}

CSSParserContext::CSSParserContext(const CSSParserContext* other,
                                   const KURL& base_url,
                                   bool origin_clean,
                                   const Referrer& referrer,
                                   const TextEncoding& charset,
                                   const Document* use_counter_document)
    : CSSParserContext(base_url,
                       origin_clean,
                       charset,
                       other->mode_,
                       referrer,
                       other->is_html_document_,
                       other->secure_context_mode_,
                       other->world_.Get(),
                       use_counter_document,
                       other->resource_fetch_restriction_) {
  is_ad_related_ = other->is_ad_related_;
}

CSSParserContext::CSSParserContext(CSSParserMode mode,
                                   SecureContextMode secure_context_mode,
                                   const Document* use_counter_document)
    : CSSParserContext(NullUrl(),
                       true,
                       TextEncoding(),
                       mode,
                       Referrer(),
                       false,
                       secure_context_mode,
                       nullptr,
                       use_counter_document,
                       ResourceFetchRestriction::kNone) {}

CSSParserContext::CSSParserContext(
    const KURL& base_url,
    bool origin_clean,
    const TextEncoding& charset,
    CSSParserMode mode,
    const Referrer& referrer,
    bool is_html_document,
    SecureContextMode secure_context_mode,
    const DOMWrapperWorld* world,
    const Document* use_counter_document,
    enum ResourceFetchRestriction resource_fetch_restriction)
    : base_url_(base_url),
      world_(world),
      origin_clean_(origin_clean),
      mode_(mode),
      referrer_(referrer),
      is_html_document_(is_html_document),
      secure_context_mode_(secure_context_mode),
      charset_(RuntimeEnabledFeatures::CSSParserIgnoreCharsetForURLsEnabled()
                   ? TextEncoding()
                   : charset),
      document_(use_counter_document),
      resource_fetch_restriction_(resource_fetch_restriction) {}

bool CSSParserContext::operator==(const CSSParserContext& other) const {
  return base_url_ == other.base_url_ && origin_clean_ == other.origin_clean_ &&
         charset_ == other.charset_ && mode_ == other.mode_ &&
         is_ad_related_ == other.is_ad_related_ &&
         is_html_document_ == other.is_html_document_ &&
         secure_context_mode_ == other.secure_context_mode_ &&
         resource_fetch_restriction_ == other.resource_fetch_restriction_;
}

const CSSParserContext* StrictCSSParserContext(
    SecureContextMode secure_context_mode) {
  static CSSParserContext* strict_context = nullptr;
  static CSSParserContext* secure_strict_context = nullptr;
  CSSParserContext*& context =
      secure_context_mode == SecureContextMode::kSecureContext
          ? secure_strict_context
          : strict_context;
  if (!context) {
    context = MakeGarbageCollected<CSSParserContext>(kHTMLStandardMode,
                                                     secure_context_mode);
  }
  return context;
}

bool CSSParserContext::IsOriginClean() const {
  return origin_clean_;
}

bool CSSParserContext::IsSecureContext() const {
  return secure_context_mode_ == SecureContextMode::kSecureContext;
}

KURL CSSParserContext::CompleteURL(const String& url) const {
  return KURL();
}

KURL CSSParserContext::CompleteNonEmptyURL(const String& url) const {
  return CompleteURL(url);
}

void CSSParserContext::Count(WebFeature) const {}

void CSSParserContext::Count(WebDXFeature) const {}

void CSSParserContext::Count(CSSPropertyID) const {}

void CSSParserContext::CountDeprecation(WebFeature) const {}

bool CSSParserContext::IsDocumentHandleEqual(const Document* other) const {
  return document_.Get() == other;
}

const Document* CSSParserContext::GetDocument() const {
  return document_.Get();
}

ExecutionContext* CSSParserContext::GetExecutionContext() const {
  return nullptr;
}

bool CSSParserContext::IsForMarkupSanitization() const {
  return false;
}

bool CSSParserContext::InElementContext() const {
  switch (Mode()) {
    case kCSSFontFaceRuleMode:
    case kCSSPropertyRuleMode:
    case kCSSFontPaletteValuesRuleMode:
      return false;
    case kHTMLStandardMode:
    case kHTMLQuirksMode:
    case kSVGAttributeMode:
    case kCSSKeyframeRuleMode:
    case kCSSPositionTryRuleMode:
    case kCSSFunctionDescriptorsMode:
    case kUASheetMode:
      return true;
    case kNumCSSParserModes:
      return true;
  }
}

void CSSParserContext::Trace(Visitor*) const {}

bool RuntimeEnabledFeaturesBase::is_css_parser_ignore_charset_for_urls_enabled_ =
    false;

}  // namespace blink
