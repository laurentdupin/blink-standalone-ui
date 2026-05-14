// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/element_type_helpers.cc.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\html\html_tag_names.json5


#include "third_party/blink/renderer/core/html_element_type_helpers.h"

#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"
#include "third_party/blink/renderer/core/html_names.h"
#include "third_party/blink/renderer/platform/runtime_enabled_features.h"
#include "third_party/blink/renderer/platform/wtf/hash_map.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"

namespace blink {
using HTMLTypeMap = HashMap<AtomicString, ElementType>;

HTMLTypeMap CreateHTMLTypeMap() {
  HTMLTypeMap html_type_map;
  html_type_map.ReserveCapacityForSize(149);
  static const struct {
    const QualifiedName* name;
    ElementType type;
  } kTags[] = {
    { &html_names::kATag, ElementType::kHTMLAnchorElement },
    { &html_names::kAbbrTag, ElementType::kHTMLElement },
    { &html_names::kAcronymTag, ElementType::kHTMLElement },
    { &html_names::kAddressTag, ElementType::kHTMLElement },
    { &html_names::kAppletTag, ElementType::kHTMLUnknownElement },
    { &html_names::kAreaTag, ElementType::kHTMLAreaElement },
    { &html_names::kArticleTag, ElementType::kHTMLElement },
    { &html_names::kAsideTag, ElementType::kHTMLElement },
    { &html_names::kAudioTag, ElementType::kHTMLAudioElement },
    { &html_names::kBTag, ElementType::kHTMLElement },
    { &html_names::kBaseTag, ElementType::kHTMLBaseElement },
    { &html_names::kBasefontTag, ElementType::kHTMLElement },
    { &html_names::kBdiTag, ElementType::kHTMLElement },
    { &html_names::kBdoTag, ElementType::kHTMLElement },
    { &html_names::kBgsoundTag, ElementType::kHTMLUnknownElement },
    { &html_names::kBigTag, ElementType::kHTMLElement },
    { &html_names::kBlockquoteTag, ElementType::kHTMLQuoteElement },
    { &html_names::kBodyTag, ElementType::kHTMLBodyElement },
    { &html_names::kBrTag, ElementType::kHTMLBRElement },
    { &html_names::kButtonTag, ElementType::kHTMLButtonElement },
    { &html_names::kCanvasTag, ElementType::kHTMLCanvasElement },
    { &html_names::kCaptionTag, ElementType::kHTMLTableCaptionElement },
    { &html_names::kCenterTag, ElementType::kHTMLElement },
    { &html_names::kCiteTag, ElementType::kHTMLElement },
    { &html_names::kCodeTag, ElementType::kHTMLElement },
    { &html_names::kColTag, ElementType::kHTMLTableColElement },
    { &html_names::kColgroupTag, ElementType::kHTMLTableColElement },
    { &html_names::kCommandTag, ElementType::kHTMLUnknownElement },
    { &html_names::kCredentialTag, ElementType::kHTMLCredentialElement },
    { &html_names::kDataTag, ElementType::kHTMLDataElement },
    { &html_names::kDatalistTag, ElementType::kHTMLDataListElement },
    { &html_names::kDdTag, ElementType::kHTMLElement },
    { &html_names::kDelTag, ElementType::kHTMLModElement },
    { &html_names::kDetailsTag, ElementType::kHTMLDetailsElement },
    { &html_names::kDfnTag, ElementType::kHTMLElement },
    { &html_names::kDialogTag, ElementType::kHTMLDialogElement },
    { &html_names::kDirTag, ElementType::kHTMLDirectoryElement },
    { &html_names::kDivTag, ElementType::kHTMLDivElement },
    { &html_names::kDlTag, ElementType::kHTMLDListElement },
    { &html_names::kDtTag, ElementType::kHTMLElement },
    { &html_names::kEmTag, ElementType::kHTMLElement },
    { &html_names::kEmbedTag, ElementType::kHTMLEmbedElement },
    { &html_names::kFencedframeTag, ElementType::kHTMLFencedFrameElement },
    { &html_names::kFieldsetTag, ElementType::kHTMLFieldSetElement },
    { &html_names::kFigcaptionTag, ElementType::kHTMLElement },
    { &html_names::kFigureTag, ElementType::kHTMLElement },
    { &html_names::kFontTag, ElementType::kHTMLFontElement },
    { &html_names::kFooterTag, ElementType::kHTMLElement },
    { &html_names::kFormTag, ElementType::kHTMLFormElement },
    { &html_names::kFrameTag, ElementType::kHTMLFrameElement },
    { &html_names::kFramesetTag, ElementType::kHTMLFrameSetElement },
    { &html_names::kGeolocationTag, ElementType::kHTMLGeolocationElement },
    { &html_names::kH1Tag, ElementType::kHTMLHeadingElement },
    { &html_names::kH2Tag, ElementType::kHTMLHeadingElement },
    { &html_names::kH3Tag, ElementType::kHTMLHeadingElement },
    { &html_names::kH4Tag, ElementType::kHTMLHeadingElement },
    { &html_names::kH5Tag, ElementType::kHTMLHeadingElement },
    { &html_names::kH6Tag, ElementType::kHTMLHeadingElement },
    { &html_names::kHeadTag, ElementType::kHTMLHeadElement },
    { &html_names::kHeaderTag, ElementType::kHTMLElement },
    { &html_names::kHgroupTag, ElementType::kHTMLElement },
    { &html_names::kHrTag, ElementType::kHTMLHRElement },
    { &html_names::kHTMLTag, ElementType::kHTMLHtmlElement },
    { &html_names::kITag, ElementType::kHTMLElement },
    { &html_names::kIFrameTag, ElementType::kHTMLIFrameElement },
    { &html_names::kImageTag, ElementType::kHTMLUnknownElement },
    { &html_names::kImgTag, ElementType::kHTMLImageElement },
    { &html_names::kInputTag, ElementType::kHTMLInputElement },
    { &html_names::kInsTag, ElementType::kHTMLModElement },
    { &html_names::kInstallTag, ElementType::kHTMLInstallElement },
    { &html_names::kKbdTag, ElementType::kHTMLElement },
    { &html_names::kKeygenTag, ElementType::kHTMLUnknownElement },
    { &html_names::kLabelTag, ElementType::kHTMLLabelElement },
    { &html_names::kLayerTag, ElementType::kHTMLElement },
    { &html_names::kLegendTag, ElementType::kHTMLLegendElement },
    { &html_names::kLiTag, ElementType::kHTMLLIElement },
    { &html_names::kLinkTag, ElementType::kHTMLLinkElement },
    { &html_names::kListingTag, ElementType::kHTMLPreElement },
    { &html_names::kLoginTag, ElementType::kHTMLLoginElement },
    { &html_names::kMainTag, ElementType::kHTMLElement },
    { &html_names::kMapTag, ElementType::kHTMLMapElement },
    { &html_names::kMarkTag, ElementType::kHTMLElement },
    { &html_names::kMarqueeTag, ElementType::kHTMLMarqueeElement },
    { &html_names::kMenuTag, ElementType::kHTMLMenuElement },
    { &html_names::kMenubarTag, ElementType::kHTMLMenuBarElement },
    { &html_names::kMenuitemTag, ElementType::kHTMLMenuItemElement },
    { &html_names::kMenulistTag, ElementType::kHTMLMenuListElement },
    { &html_names::kMetaTag, ElementType::kHTMLMetaElement },
    { &html_names::kMeterTag, ElementType::kHTMLMeterElement },
    { &html_names::kNavTag, ElementType::kHTMLElement },
    { &html_names::kNobrTag, ElementType::kHTMLElement },
    { &html_names::kNoembedTag, ElementType::kHTMLElement },
    { &html_names::kNoframesTag, ElementType::kHTMLElement },
    { &html_names::kNolayerTag, ElementType::kHTMLElement },
    { &html_names::kNoscriptTag, ElementType::kHTMLElement },
    { &html_names::kObjectTag, ElementType::kHTMLObjectElement },
    { &html_names::kOlTag, ElementType::kHTMLOListElement },
    { &html_names::kOptgroupTag, ElementType::kHTMLOptGroupElement },
    { &html_names::kOptionTag, ElementType::kHTMLOptionElement },
    { &html_names::kOutputTag, ElementType::kHTMLOutputElement },
    { &html_names::kPTag, ElementType::kHTMLParagraphElement },
    { &html_names::kParamTag, ElementType::kHTMLParamElement },
    { &html_names::kPictureTag, ElementType::kHTMLPictureElement },
    { &html_names::kPlaintextTag, ElementType::kHTMLElement },
    { &html_names::kPreTag, ElementType::kHTMLPreElement },
    { &html_names::kProgressTag, ElementType::kHTMLProgressElement },
    { &html_names::kQTag, ElementType::kHTMLQuoteElement },
    { &html_names::kRbTag, ElementType::kHTMLElement },
    { &html_names::kRpTag, ElementType::kHTMLElement },
    { &html_names::kRtTag, ElementType::kHTMLElement },
    { &html_names::kRTCTag, ElementType::kHTMLElement },
    { &html_names::kRubyTag, ElementType::kHTMLElement },
    { &html_names::kSTag, ElementType::kHTMLElement },
    { &html_names::kSampTag, ElementType::kHTMLElement },
    { &html_names::kScriptTag, ElementType::kHTMLScriptElement },
    { &html_names::kSearchTag, ElementType::kHTMLSearchElement },
    { &html_names::kSectionTag, ElementType::kHTMLElement },
    { &html_names::kSelectTag, ElementType::kHTMLSelectElement },
    { &html_names::kSelectedcontentTag, ElementType::kHTMLSelectedContentElement },
    { &html_names::kSlotTag, ElementType::kHTMLSlotElement },
    { &html_names::kSmallTag, ElementType::kHTMLElement },
    { &html_names::kSourceTag, ElementType::kHTMLSourceElement },
    { &html_names::kSpanTag, ElementType::kHTMLSpanElement },
    { &html_names::kStrikeTag, ElementType::kHTMLElement },
    { &html_names::kStrongTag, ElementType::kHTMLElement },
    { &html_names::kStyleTag, ElementType::kHTMLStyleElement },
    { &html_names::kSubTag, ElementType::kHTMLElement },
    { &html_names::kSummaryTag, ElementType::kHTMLElement },
    { &html_names::kSupTag, ElementType::kHTMLElement },
    { &html_names::kTableTag, ElementType::kHTMLTableElement },
    { &html_names::kTbodyTag, ElementType::kHTMLTableSectionElement },
    { &html_names::kTdTag, ElementType::kHTMLTableCellElement },
    { &html_names::kTemplateTag, ElementType::kHTMLTemplateElement },
    { &html_names::kTextareaTag, ElementType::kHTMLTextAreaElement },
    { &html_names::kTfootTag, ElementType::kHTMLTableSectionElement },
    { &html_names::kThTag, ElementType::kHTMLTableCellElement },
    { &html_names::kTheadTag, ElementType::kHTMLTableSectionElement },
    { &html_names::kTimeTag, ElementType::kHTMLTimeElement },
    { &html_names::kTitleTag, ElementType::kHTMLTitleElement },
    { &html_names::kTrTag, ElementType::kHTMLTableRowElement },
    { &html_names::kTrackTag, ElementType::kHTMLTrackElement },
    { &html_names::kTtTag, ElementType::kHTMLElement },
    { &html_names::kUTag, ElementType::kHTMLElement },
    { &html_names::kUlTag, ElementType::kHTMLUListElement },
    { &html_names::kUsermediaTag, ElementType::kHTMLUserMediaElement },
    { &html_names::kVarTag, ElementType::kHTMLElement },
    { &html_names::kVideoTag, ElementType::kHTMLVideoElement },
    { &html_names::kWbrTag, ElementType::kHTMLElement },
    { &html_names::kXmpTag, ElementType::kHTMLPreElement },
  };
  for (const auto& tag : kTags)
    html_type_map.insert(tag.name->LocalName(), tag.type);
  return html_type_map;
}

static const HTMLTypeMap& GetHTMLTypeMap() {
  DEFINE_STATIC_LOCAL(const HTMLTypeMap, html_type_map, (CreateHTMLTypeMap()));
  return html_type_map;
}

ElementType HtmlElementTypeForTag(const AtomicString& tag_name, const Document* document) {
  const auto& html_type_map = GetHTMLTypeMap();
  auto it = html_type_map.find(tag_name);
  if (it == html_type_map.end())
    return ElementType::kHTMLUnknownElement;

  if (tag_name == "credential") {
    if (!RuntimeEnabledFeatures::LoginElementEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "fencedframe") {
    if (!RuntimeEnabledFeatures::FencedFramesEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "geolocation") {
    if (!RuntimeEnabledFeatures::GeolocationElementEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "install") {
    if (!RuntimeEnabledFeatures::InstallElementEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "login") {
    if (!RuntimeEnabledFeatures::LoginElementEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "menubar") {
    if (!RuntimeEnabledFeatures::MenuElementsEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "menuitem") {
    if (!RuntimeEnabledFeatures::MenuElementsEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "menulist") {
    if (!RuntimeEnabledFeatures::MenuElementsEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  if (tag_name == "usermedia") {
    if (!RuntimeEnabledFeatures::UserMediaElementEnabled(document->GetExecutionContext())) {
      return ElementType::kHTMLUnknownElement;
    }
  }
  return it->value;
}

bool IsKnownBuiltinTagName(const AtomicString& tag_name) {
  return GetHTMLTypeMap().Contains(tag_name);
}
}  // namespace blink
