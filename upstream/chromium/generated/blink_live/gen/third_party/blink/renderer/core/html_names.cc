// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.cc.tmpl
// and input files:
//   ../../third_party/blink/renderer/core/html/aria_properties.json5
//   ../../third_party/blink/renderer/core/html/html_attribute_names.json5
//   ../../third_party/blink/renderer/core/html/html_tag_names.json5


#include "third_party/blink/renderer/core/html_names.h"

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/static_constructors.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_hasher.h"

namespace blink {
namespace html_names {

DEFINE_GLOBAL(, AtomicString, xhtmlNamespaceURI);

// Tags

void* tag_storage[kTagsCount * ((sizeof(HTMLQualifiedName) + sizeof(void *) - 1) / sizeof(void *))];
const HTMLQualifiedName& kATag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[0];
const HTMLQualifiedName& kAbbrTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[1];
const HTMLQualifiedName& kAcronymTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[2];
const HTMLQualifiedName& kAddressTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[3];
const HTMLQualifiedName& kAppletTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[4];
const HTMLQualifiedName& kAreaTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[5];
const HTMLQualifiedName& kArticleTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[6];
const HTMLQualifiedName& kAsideTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[7];
const HTMLQualifiedName& kAudioTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[8];
const HTMLQualifiedName& kBTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[9];
const HTMLQualifiedName& kBaseTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[10];
const HTMLQualifiedName& kBasefontTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[11];
const HTMLQualifiedName& kBdiTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[12];
const HTMLQualifiedName& kBdoTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[13];
const HTMLQualifiedName& kBgsoundTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[14];
const HTMLQualifiedName& kBigTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[15];
const HTMLQualifiedName& kBlockquoteTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[16];
const HTMLQualifiedName& kBodyTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[17];
const HTMLQualifiedName& kBrTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[18];
const HTMLQualifiedName& kButtonTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[19];
const HTMLQualifiedName& kCanvasTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[20];
const HTMLQualifiedName& kCaptionTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[21];
const HTMLQualifiedName& kCenterTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[22];
const HTMLQualifiedName& kCiteTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[23];
const HTMLQualifiedName& kCodeTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[24];
const HTMLQualifiedName& kColTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[25];
const HTMLQualifiedName& kColgroupTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[26];
const HTMLQualifiedName& kCommandTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[27];
const HTMLQualifiedName& kCredentialTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[28];
const HTMLQualifiedName& kDataTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[29];
const HTMLQualifiedName& kDatalistTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[30];
const HTMLQualifiedName& kDdTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[31];
const HTMLQualifiedName& kDelTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[32];
const HTMLQualifiedName& kDetailsTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[33];
const HTMLQualifiedName& kDfnTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[34];
const HTMLQualifiedName& kDialogTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[35];
const HTMLQualifiedName& kDirTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[36];
const HTMLQualifiedName& kDivTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[37];
const HTMLQualifiedName& kDlTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[38];
const HTMLQualifiedName& kDtTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[39];
const HTMLQualifiedName& kEmTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[40];
const HTMLQualifiedName& kEmbedTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[41];
const HTMLQualifiedName& kFencedframeTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[42];
const HTMLQualifiedName& kFieldsetTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[43];
const HTMLQualifiedName& kFigcaptionTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[44];
const HTMLQualifiedName& kFigureTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[45];
const HTMLQualifiedName& kFontTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[46];
const HTMLQualifiedName& kFooterTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[47];
const HTMLQualifiedName& kFormTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[48];
const HTMLQualifiedName& kFrameTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[49];
const HTMLQualifiedName& kFramesetTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[50];
const HTMLQualifiedName& kGeolocationTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[51];
const HTMLQualifiedName& kH1Tag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[52];
const HTMLQualifiedName& kH2Tag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[53];
const HTMLQualifiedName& kH3Tag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[54];
const HTMLQualifiedName& kH4Tag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[55];
const HTMLQualifiedName& kH5Tag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[56];
const HTMLQualifiedName& kH6Tag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[57];
const HTMLQualifiedName& kHeadTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[58];
const HTMLQualifiedName& kHeaderTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[59];
const HTMLQualifiedName& kHgroupTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[60];
const HTMLQualifiedName& kHrTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[61];
const HTMLQualifiedName& kHTMLTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[62];
const HTMLQualifiedName& kITag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[63];
const HTMLQualifiedName& kIFrameTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[64];
const HTMLQualifiedName& kImageTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[65];
const HTMLQualifiedName& kImgTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[66];
const HTMLQualifiedName& kInputTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[67];
const HTMLQualifiedName& kInsTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[68];
const HTMLQualifiedName& kInstallTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[69];
const HTMLQualifiedName& kKbdTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[70];
const HTMLQualifiedName& kKeygenTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[71];
const HTMLQualifiedName& kLabelTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[72];
const HTMLQualifiedName& kLayerTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[73];
const HTMLQualifiedName& kLegendTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[74];
const HTMLQualifiedName& kLiTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[75];
const HTMLQualifiedName& kLinkTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[76];
const HTMLQualifiedName& kListingTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[77];
const HTMLQualifiedName& kLoginTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[78];
const HTMLQualifiedName& kMainTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[79];
const HTMLQualifiedName& kMapTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[80];
const HTMLQualifiedName& kMarkTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[81];
const HTMLQualifiedName& kMarqueeTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[82];
const HTMLQualifiedName& kMenuTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[83];
const HTMLQualifiedName& kMenubarTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[84];
const HTMLQualifiedName& kMenuitemTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[85];
const HTMLQualifiedName& kMenulistTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[86];
const HTMLQualifiedName& kMetaTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[87];
const HTMLQualifiedName& kMeterTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[88];
const HTMLQualifiedName& kNavTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[89];
const HTMLQualifiedName& kNobrTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[90];
const HTMLQualifiedName& kNoembedTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[91];
const HTMLQualifiedName& kNoframesTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[92];
const HTMLQualifiedName& kNolayerTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[93];
const HTMLQualifiedName& kNoscriptTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[94];
const HTMLQualifiedName& kObjectTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[95];
const HTMLQualifiedName& kOlTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[96];
const HTMLQualifiedName& kOptgroupTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[97];
const HTMLQualifiedName& kOptionTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[98];
const HTMLQualifiedName& kOutputTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[99];
const HTMLQualifiedName& kPTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[100];
const HTMLQualifiedName& kParamTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[101];
const HTMLQualifiedName& kPictureTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[102];
const HTMLQualifiedName& kPlaintextTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[103];
const HTMLQualifiedName& kPreTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[104];
const HTMLQualifiedName& kProgressTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[105];
const HTMLQualifiedName& kQTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[106];
const HTMLQualifiedName& kRbTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[107];
const HTMLQualifiedName& kRpTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[108];
const HTMLQualifiedName& kRtTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[109];
const HTMLQualifiedName& kRTCTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[110];
const HTMLQualifiedName& kRubyTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[111];
const HTMLQualifiedName& kSTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[112];
const HTMLQualifiedName& kSampTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[113];
const HTMLQualifiedName& kScriptTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[114];
const HTMLQualifiedName& kSearchTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[115];
const HTMLQualifiedName& kSectionTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[116];
const HTMLQualifiedName& kSelectTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[117];
const HTMLQualifiedName& kSelectedcontentTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[118];
const HTMLQualifiedName& kSlotTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[119];
const HTMLQualifiedName& kSmallTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[120];
const HTMLQualifiedName& kSourceTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[121];
const HTMLQualifiedName& kSpanTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[122];
const HTMLQualifiedName& kStrikeTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[123];
const HTMLQualifiedName& kStrongTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[124];
const HTMLQualifiedName& kStyleTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[125];
const HTMLQualifiedName& kSubTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[126];
const HTMLQualifiedName& kSummaryTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[127];
const HTMLQualifiedName& kSupTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[128];
const HTMLQualifiedName& kTableTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[129];
const HTMLQualifiedName& kTbodyTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[130];
const HTMLQualifiedName& kTdTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[131];
const HTMLQualifiedName& kTemplateTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[132];
const HTMLQualifiedName& kTextareaTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[133];
const HTMLQualifiedName& kTfootTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[134];
const HTMLQualifiedName& kThTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[135];
const HTMLQualifiedName& kTheadTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[136];
const HTMLQualifiedName& kTimeTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[137];
const HTMLQualifiedName& kTitleTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[138];
const HTMLQualifiedName& kTrTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[139];
const HTMLQualifiedName& kTrackTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[140];
const HTMLQualifiedName& kTtTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[141];
const HTMLQualifiedName& kUTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[142];
const HTMLQualifiedName& kUlTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[143];
const HTMLQualifiedName& kUsermediaTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[144];
const HTMLQualifiedName& kVarTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[145];
const HTMLQualifiedName& kVideoTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[146];
const HTMLQualifiedName& kWbrTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[147];
const HTMLQualifiedName& kXmpTag = reinterpret_cast<HTMLQualifiedName*>(&tag_storage)[148];


base::HeapArray<const QualifiedName*> GetTags() {
  auto tags = base::HeapArray<const QualifiedName*>::Uninit(kTagsCount);
  for (size_t i = 0; i < kTagsCount; ++i) {
    tags[i] = reinterpret_cast<QualifiedNameWithHash*>(&tag_storage) + i;
  }
  return tags;
}

// Attributes

void* attr_storage[kAttrsCount * ((sizeof(QualifiedNameWithHash) + sizeof(void *) - 1) / sizeof(void *))];

const QualifiedNameWithHash& kAbbrAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[0];
const QualifiedNameWithHash& kAcceptAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[1];
const QualifiedNameWithHash& kAcceptCharsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[2];
const QualifiedNameWithHash& kAccesskeyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[3];
const QualifiedNameWithHash& kAccuracymodeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[4];
const QualifiedNameWithHash& kActionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[5];
const QualifiedNameWithHash& kAdauctionheadersAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[6];
const QualifiedNameWithHash& kAlignAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[7];
const QualifiedNameWithHash& kAlinkAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[8];
const QualifiedNameWithHash& kAllowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[9];
const QualifiedNameWithHash& kAllowfullscreenAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[10];
const QualifiedNameWithHash& kAllowpaymentrequestAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[11];
const QualifiedNameWithHash& kAltAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[12];
const QualifiedNameWithHash& kArchiveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[13];
const QualifiedNameWithHash& kAriaActionsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[14];
const QualifiedNameWithHash& kAriaActivedescendantAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[15];
const QualifiedNameWithHash& kAriaAtomicAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[16];
const QualifiedNameWithHash& kAriaAutocompleteAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[17];
const QualifiedNameWithHash& kAriaBraillelabelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[18];
const QualifiedNameWithHash& kAriaBrailleroledescriptionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[19];
const QualifiedNameWithHash& kAriaBusyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[20];
const QualifiedNameWithHash& kAriaCheckedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[21];
const QualifiedNameWithHash& kAriaColcountAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[22];
const QualifiedNameWithHash& kAriaColindexAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[23];
const QualifiedNameWithHash& kAriaColindextextAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[24];
const QualifiedNameWithHash& kAriaColspanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[25];
const QualifiedNameWithHash& kAriaControlsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[26];
const QualifiedNameWithHash& kAriaCurrentAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[27];
const QualifiedNameWithHash& kAriaDescribedbyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[28];
const QualifiedNameWithHash& kAriaDescriptionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[29];
const QualifiedNameWithHash& kAriaDetailsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[30];
const QualifiedNameWithHash& kAriaDisabledAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[31];
const QualifiedNameWithHash& kAriaErrormessageAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[32];
const QualifiedNameWithHash& kAriaExpandedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[33];
const QualifiedNameWithHash& kAriaFlowtoAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[34];
const QualifiedNameWithHash& kAriaHaspopupAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[35];
const QualifiedNameWithHash& kAriaHiddenAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[36];
const QualifiedNameWithHash& kAriaInvalidAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[37];
const QualifiedNameWithHash& kAriaKeyshortcutsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[38];
const QualifiedNameWithHash& kAriaLabelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[39];
const QualifiedNameWithHash& kAriaLabeledbyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[40];
const QualifiedNameWithHash& kAriaLabelledbyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[41];
const QualifiedNameWithHash& kAriaLevelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[42];
const QualifiedNameWithHash& kAriaLiveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[43];
const QualifiedNameWithHash& kAriaModalAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[44];
const QualifiedNameWithHash& kAriaMultilineAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[45];
const QualifiedNameWithHash& kAriaMultiselectableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[46];
const QualifiedNameWithHash& kAriaOrientationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[47];
const QualifiedNameWithHash& kAriaOwnsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[48];
const QualifiedNameWithHash& kAriaPlaceholderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[49];
const QualifiedNameWithHash& kAriaPosinsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[50];
const QualifiedNameWithHash& kAriaPressedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[51];
const QualifiedNameWithHash& kAriaReadonlyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[52];
const QualifiedNameWithHash& kAriaRelevantAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[53];
const QualifiedNameWithHash& kAriaRequiredAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[54];
const QualifiedNameWithHash& kAriaRoledescriptionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[55];
const QualifiedNameWithHash& kAriaRowcountAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[56];
const QualifiedNameWithHash& kAriaRowindexAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[57];
const QualifiedNameWithHash& kAriaRowindextextAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[58];
const QualifiedNameWithHash& kAriaRowspanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[59];
const QualifiedNameWithHash& kAriaSelectedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[60];
const QualifiedNameWithHash& kAriaSetsizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[61];
const QualifiedNameWithHash& kAriaSortAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[62];
const QualifiedNameWithHash& kAriaValuemaxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[63];
const QualifiedNameWithHash& kAriaValueminAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[64];
const QualifiedNameWithHash& kAriaValuenowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[65];
const QualifiedNameWithHash& kAriaValuetextAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[66];
const QualifiedNameWithHash& kAriaVirtualcontentAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[67];
const QualifiedNameWithHash& kAsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[68];
const QualifiedNameWithHash& kAsyncAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[69];
const QualifiedNameWithHash& kAttributionsrcAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[70];
const QualifiedNameWithHash& kAutocapitalizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[71];
const QualifiedNameWithHash& kAutocompleteAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[72];
const QualifiedNameWithHash& kAutocorrectAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[73];
const QualifiedNameWithHash& kAutofocusAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[74];
const QualifiedNameWithHash& kAutolocateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[75];
const QualifiedNameWithHash& kAutoplayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[76];
const QualifiedNameWithHash& kAxisAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[77];
const QualifiedNameWithHash& kBackgroundAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[78];
const QualifiedNameWithHash& kBehaviorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[79];
const QualifiedNameWithHash& kBgcolorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[80];
const QualifiedNameWithHash& kBlockingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[81];
const QualifiedNameWithHash& kBorderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[82];
const QualifiedNameWithHash& kBordercolorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[83];
const QualifiedNameWithHash& kBrowsingtopicsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[84];
const QualifiedNameWithHash& kCachehintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[85];
const QualifiedNameWithHash& kCaptureAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[86];
const QualifiedNameWithHash& kCellpaddingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[87];
const QualifiedNameWithHash& kCellspacingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[88];
const QualifiedNameWithHash& kChallengeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[89];
const QualifiedNameWithHash& kCharAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[90];
const QualifiedNameWithHash& kCharoffAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[91];
const QualifiedNameWithHash& kCharsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[92];
const QualifiedNameWithHash& kCheckableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[93];
const QualifiedNameWithHash& kCheckedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[94];
const QualifiedNameWithHash& kCiteAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[95];
const QualifiedNameWithHash& kClassAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[96];
const QualifiedNameWithHash& kClassidAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[97];
const QualifiedNameWithHash& kClearAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[98];
const QualifiedNameWithHash& kClientidAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[99];
const QualifiedNameWithHash& kClosedbyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[100];
const QualifiedNameWithHash& kCodeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[101];
const QualifiedNameWithHash& kCodebaseAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[102];
const QualifiedNameWithHash& kCodetypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[103];
const QualifiedNameWithHash& kColorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[104];
const QualifiedNameWithHash& kColsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[105];
const QualifiedNameWithHash& kColspanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[106];
const QualifiedNameWithHash& kCommandAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[107];
const QualifiedNameWithHash& kCommandforAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[108];
const QualifiedNameWithHash& kCompactAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[109];
const QualifiedNameWithHash& kConfigurlAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[110];
const QualifiedNameWithHash& kContainertimingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[111];
const QualifiedNameWithHash& kContainertimingIgnoreAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[112];
const QualifiedNameWithHash& kContentAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[113];
const QualifiedNameWithHash& kContenteditableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[114];
const QualifiedNameWithHash& kControlsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[115];
const QualifiedNameWithHash& kControlslistAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[116];
const QualifiedNameWithHash& kCoordsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[117];
const QualifiedNameWithHash& kCredentiallessAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[118];
const QualifiedNameWithHash& kCrossoriginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[119];
const QualifiedNameWithHash& kCspAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[120];
const QualifiedNameWithHash& kCustomelementregistryAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[121];
const QualifiedNameWithHash& kDataAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[122];
const QualifiedNameWithHash& kDataSrcAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[123];
const QualifiedNameWithHash& kDatetimeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[124];
const QualifiedNameWithHash& kDeclareAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[125];
const QualifiedNameWithHash& kDecodingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[126];
const QualifiedNameWithHash& kDefaultAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[127];
const QualifiedNameWithHash& kDefaultcheckedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[128];
const QualifiedNameWithHash& kDeferAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[129];
const QualifiedNameWithHash& kDelegatesfocusAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[130];
const QualifiedNameWithHash& kDirAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[131];
const QualifiedNameWithHash& kDirectionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[132];
const QualifiedNameWithHash& kDirnameAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[133];
const QualifiedNameWithHash& kDisabledAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[134];
const QualifiedNameWithHash& kDisablepictureinpictureAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[135];
const QualifiedNameWithHash& kDisableremoteplaybackAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[136];
const QualifiedNameWithHash& kDomainhintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[137];
const QualifiedNameWithHash& kDownloadAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[138];
const QualifiedNameWithHash& kDraggableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[139];
const QualifiedNameWithHash& kElementtimingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[140];
const QualifiedNameWithHash& kEnctypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[141];
const QualifiedNameWithHash& kEndAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[142];
const QualifiedNameWithHash& kEnterkeyhintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[143];
const QualifiedNameWithHash& kEventAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[144];
const QualifiedNameWithHash& kExportpartsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[145];
const QualifiedNameWithHash& kFaceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[146];
const QualifiedNameWithHash& kFetchpriorityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[147];
const QualifiedNameWithHash& kFieldsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[148];
const QualifiedNameWithHash& kFilterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[149];
const QualifiedNameWithHash& kFocusgroupAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[150];
const QualifiedNameWithHash& kFocusgroupstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[151];
const QualifiedNameWithHash& kForAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[152];
const QualifiedNameWithHash& kFormAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[153];
const QualifiedNameWithHash& kFormactionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[154];
const QualifiedNameWithHash& kFormenctypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[155];
const QualifiedNameWithHash& kFormmethodAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[156];
const QualifiedNameWithHash& kFormnovalidateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[157];
const QualifiedNameWithHash& kFormtargetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[158];
const QualifiedNameWithHash& kFrameAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[159];
const QualifiedNameWithHash& kFrameborderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[160];
const QualifiedNameWithHash& kHeadersAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[161];
const QualifiedNameWithHash& kHeadingoffsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[162];
const QualifiedNameWithHash& kHeadingresetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[163];
const QualifiedNameWithHash& kHeightAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[164];
const QualifiedNameWithHash& kHiddenAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[165];
const QualifiedNameWithHash& kHighAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[166];
const QualifiedNameWithHash& kHrefAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[167];
const QualifiedNameWithHash& kHreflangAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[168];
const QualifiedNameWithHash& kHreftranslateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[169];
const QualifiedNameWithHash& kHspaceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[170];
const QualifiedNameWithHash& kHttpEquivAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[171];
const QualifiedNameWithHash& kIdAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[172];
const QualifiedNameWithHash& kImagesizesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[173];
const QualifiedNameWithHash& kImagesrcsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[174];
const QualifiedNameWithHash& kIncrementalAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[175];
const QualifiedNameWithHash& kInertAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[176];
const QualifiedNameWithHash& kInputmodeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[177];
const QualifiedNameWithHash& kInstallurlAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[178];
const QualifiedNameWithHash& kIntegrityAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[179];
const QualifiedNameWithHash& kInterestforAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[180];
const QualifiedNameWithHash& kInvisibleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[181];
const QualifiedNameWithHash& kIsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[182];
const QualifiedNameWithHash& kIsmapAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[183];
const QualifiedNameWithHash& kItempropAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[184];
const QualifiedNameWithHash& kKeytypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[185];
const QualifiedNameWithHash& kKindAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[186];
const QualifiedNameWithHash& kLabelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[187];
const QualifiedNameWithHash& kLangAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[188];
const QualifiedNameWithHash& kLanguageAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[189];
const QualifiedNameWithHash& kLatencyhintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[190];
const QualifiedNameWithHash& kLayoutsubtreeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[191];
const QualifiedNameWithHash& kLeftmarginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[192];
const QualifiedNameWithHash& kLinkAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[193];
const QualifiedNameWithHash& kListAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[194];
const QualifiedNameWithHash& kLoadingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[195];
const QualifiedNameWithHash& kLoginhintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[196];
const QualifiedNameWithHash& kLongdescAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[197];
const QualifiedNameWithHash& kLoopAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[198];
const QualifiedNameWithHash& kLowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[199];
const QualifiedNameWithHash& kLowsrcAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[200];
const QualifiedNameWithHash& kManifestAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[201];
const QualifiedNameWithHash& kManifestidAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[202];
const QualifiedNameWithHash& kMarginheightAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[203];
const QualifiedNameWithHash& kMarginwidthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[204];
const QualifiedNameWithHash& kMarkerAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[205];
const QualifiedNameWithHash& kMaxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[206];
const QualifiedNameWithHash& kMaxlengthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[207];
const QualifiedNameWithHash& kMayscriptAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[208];
const QualifiedNameWithHash& kMediaAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[209];
const QualifiedNameWithHash& kMethodAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[210];
const QualifiedNameWithHash& kMinAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[211];
const QualifiedNameWithHash& kMinlengthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[212];
const QualifiedNameWithHash& kMultipleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[213];
const QualifiedNameWithHash& kMutedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[214];
const QualifiedNameWithHash& kNameAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[215];
const QualifiedNameWithHash& kNohrefAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[216];
const QualifiedNameWithHash& kNomoduleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[217];
const QualifiedNameWithHash& kNonceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[218];
const QualifiedNameWithHash& kNoresizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[219];
const QualifiedNameWithHash& kNoshadeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[220];
const QualifiedNameWithHash& kNovalidateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[221];
const QualifiedNameWithHash& kNowrapAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[222];
const QualifiedNameWithHash& kObjectAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[223];
const QualifiedNameWithHash& kOnabortAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[224];
const QualifiedNameWithHash& kOnafterprintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[225];
const QualifiedNameWithHash& kOnanimationcancelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[226];
const QualifiedNameWithHash& kOnanimationendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[227];
const QualifiedNameWithHash& kOnanimationiterationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[228];
const QualifiedNameWithHash& kOnanimationstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[229];
const QualifiedNameWithHash& kOnautofillAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[230];
const QualifiedNameWithHash& kOnauxclickAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[231];
const QualifiedNameWithHash& kOnbeforecopyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[232];
const QualifiedNameWithHash& kOnbeforecutAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[233];
const QualifiedNameWithHash& kOnbeforefilterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[234];
const QualifiedNameWithHash& kOnbeforeinputAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[235];
const QualifiedNameWithHash& kOnbeforepasteAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[236];
const QualifiedNameWithHash& kOnbeforeprintAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[237];
const QualifiedNameWithHash& kOnbeforetoggleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[238];
const QualifiedNameWithHash& kOnbeforeunloadAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[239];
const QualifiedNameWithHash& kOnblurAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[240];
const QualifiedNameWithHash& kOncancelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[241];
const QualifiedNameWithHash& kOncanplayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[242];
const QualifiedNameWithHash& kOncanplaythroughAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[243];
const QualifiedNameWithHash& kOnchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[244];
const QualifiedNameWithHash& kOnclickAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[245];
const QualifiedNameWithHash& kOncloseAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[246];
const QualifiedNameWithHash& kOncommandAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[247];
const QualifiedNameWithHash& kOncontentvisibilityautostatechangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[248];
const QualifiedNameWithHash& kOncontextlostAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[249];
const QualifiedNameWithHash& kOncontextmenuAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[250];
const QualifiedNameWithHash& kOncontextrestoredAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[251];
const QualifiedNameWithHash& kOncopyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[252];
const QualifiedNameWithHash& kOncuechangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[253];
const QualifiedNameWithHash& kOncutAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[254];
const QualifiedNameWithHash& kOndblclickAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[255];
const QualifiedNameWithHash& kOndismissAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[256];
const QualifiedNameWithHash& kOndragAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[257];
const QualifiedNameWithHash& kOndragendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[258];
const QualifiedNameWithHash& kOndragenterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[259];
const QualifiedNameWithHash& kOndragleaveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[260];
const QualifiedNameWithHash& kOndragoverAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[261];
const QualifiedNameWithHash& kOndragstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[262];
const QualifiedNameWithHash& kOndropAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[263];
const QualifiedNameWithHash& kOndurationchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[264];
const QualifiedNameWithHash& kOnemptiedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[265];
const QualifiedNameWithHash& kOnendedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[266];
const QualifiedNameWithHash& kOnerrorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[267];
const QualifiedNameWithHash& kOnfocusAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[268];
const QualifiedNameWithHash& kOnfocusinAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[269];
const QualifiedNameWithHash& kOnfocusoutAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[270];
const QualifiedNameWithHash& kOnformdataAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[271];
const QualifiedNameWithHash& kOngotpointercaptureAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[272];
const QualifiedNameWithHash& kOnhashchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[273];
const QualifiedNameWithHash& kOninputAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[274];
const QualifiedNameWithHash& kOninvalidAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[275];
const QualifiedNameWithHash& kOnkeydownAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[276];
const QualifiedNameWithHash& kOnkeypressAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[277];
const QualifiedNameWithHash& kOnkeyupAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[278];
const QualifiedNameWithHash& kOnlanguagechangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[279];
const QualifiedNameWithHash& kOnloadAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[280];
const QualifiedNameWithHash& kOnloadeddataAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[281];
const QualifiedNameWithHash& kOnloadedmetadataAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[282];
const QualifiedNameWithHash& kOnloadstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[283];
const QualifiedNameWithHash& kOnlocationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[284];
const QualifiedNameWithHash& kOnlostpointercaptureAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[285];
const QualifiedNameWithHash& kOnmessageAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[286];
const QualifiedNameWithHash& kOnmessageerrorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[287];
const QualifiedNameWithHash& kOnmousedownAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[288];
const QualifiedNameWithHash& kOnmouseenterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[289];
const QualifiedNameWithHash& kOnmouseleaveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[290];
const QualifiedNameWithHash& kOnmousemoveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[291];
const QualifiedNameWithHash& kOnmouseoutAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[292];
const QualifiedNameWithHash& kOnmouseoverAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[293];
const QualifiedNameWithHash& kOnmouseupAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[294];
const QualifiedNameWithHash& kOnmousewheelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[295];
const QualifiedNameWithHash& kOnmoveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[296];
const QualifiedNameWithHash& kOnofflineAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[297];
const QualifiedNameWithHash& kOnonlineAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[298];
const QualifiedNameWithHash& kOnorientationchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[299];
const QualifiedNameWithHash& kOnpagehideAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[300];
const QualifiedNameWithHash& kOnpageshowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[301];
const QualifiedNameWithHash& kOnpasteAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[302];
const QualifiedNameWithHash& kOnpauseAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[303];
const QualifiedNameWithHash& kOnplayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[304];
const QualifiedNameWithHash& kOnplayingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[305];
const QualifiedNameWithHash& kOnpointercancelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[306];
const QualifiedNameWithHash& kOnpointerdownAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[307];
const QualifiedNameWithHash& kOnpointerenterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[308];
const QualifiedNameWithHash& kOnpointerleaveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[309];
const QualifiedNameWithHash& kOnpointermoveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[310];
const QualifiedNameWithHash& kOnpointeroutAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[311];
const QualifiedNameWithHash& kOnpointeroverAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[312];
const QualifiedNameWithHash& kOnpointerrawupdateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[313];
const QualifiedNameWithHash& kOnpointerupAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[314];
const QualifiedNameWithHash& kOnpopstateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[315];
const QualifiedNameWithHash& kOnprogressAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[316];
const QualifiedNameWithHash& kOnpromptactionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[317];
const QualifiedNameWithHash& kOnpromptdismissAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[318];
const QualifiedNameWithHash& kOnratechangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[319];
const QualifiedNameWithHash& kOnresetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[320];
const QualifiedNameWithHash& kOnresizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[321];
const QualifiedNameWithHash& kOnresolveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[322];
const QualifiedNameWithHash& kOnscrollAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[323];
const QualifiedNameWithHash& kOnscrollendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[324];
const QualifiedNameWithHash& kOnscrollsnapchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[325];
const QualifiedNameWithHash& kOnscrollsnapchangingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[326];
const QualifiedNameWithHash& kOnsearchAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[327];
const QualifiedNameWithHash& kOnsecuritypolicyviolationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[328];
const QualifiedNameWithHash& kOnseekedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[329];
const QualifiedNameWithHash& kOnseekingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[330];
const QualifiedNameWithHash& kOnselectAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[331];
const QualifiedNameWithHash& kOnselectionchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[332];
const QualifiedNameWithHash& kOnselectstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[333];
const QualifiedNameWithHash& kOnshowAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[334];
const QualifiedNameWithHash& kOnslotchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[335];
const QualifiedNameWithHash& kOnstalledAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[336];
const QualifiedNameWithHash& kOnstorageAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[337];
const QualifiedNameWithHash& kOnstreamAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[338];
const QualifiedNameWithHash& kOnsubmitAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[339];
const QualifiedNameWithHash& kOnsuspendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[340];
const QualifiedNameWithHash& kOntimeupdateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[341];
const QualifiedNameWithHash& kOntimezonechangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[342];
const QualifiedNameWithHash& kOntoggleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[343];
const QualifiedNameWithHash& kOntouchcancelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[344];
const QualifiedNameWithHash& kOntouchendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[345];
const QualifiedNameWithHash& kOntouchmoveAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[346];
const QualifiedNameWithHash& kOntouchstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[347];
const QualifiedNameWithHash& kOntransitionendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[348];
const QualifiedNameWithHash& kOnunloadAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[349];
const QualifiedNameWithHash& kOnvalidationstatuschangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[350];
const QualifiedNameWithHash& kOnvolumechangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[351];
const QualifiedNameWithHash& kOnwaitingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[352];
const QualifiedNameWithHash& kOnwebkitanimationendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[353];
const QualifiedNameWithHash& kOnwebkitanimationiterationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[354];
const QualifiedNameWithHash& kOnwebkitanimationstartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[355];
const QualifiedNameWithHash& kOnwebkitfullscreenchangeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[356];
const QualifiedNameWithHash& kOnwebkitfullscreenerrorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[357];
const QualifiedNameWithHash& kOnwebkittransitionendAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[358];
const QualifiedNameWithHash& kOnwheelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[359];
const QualifiedNameWithHash& kOpenAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[360];
const QualifiedNameWithHash& kOptimumAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[361];
const QualifiedNameWithHash& kOverscrollareaAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[362];
const QualifiedNameWithHash& kOverscrollcontainerAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[363];
const QualifiedNameWithHash& kParamsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[364];
const QualifiedNameWithHash& kParsepartsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[365];
const QualifiedNameWithHash& kPartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[366];
const QualifiedNameWithHash& kPatternAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[367];
const QualifiedNameWithHash& kPingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[368];
const QualifiedNameWithHash& kPlaceholderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[369];
const QualifiedNameWithHash& kPlaysinlineAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[370];
const QualifiedNameWithHash& kPolicyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[371];
const QualifiedNameWithHash& kPopoverAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[372];
const QualifiedNameWithHash& kPopovertargetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[373];
const QualifiedNameWithHash& kPopovertargetactionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[374];
const QualifiedNameWithHash& kPosterAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[375];
const QualifiedNameWithHash& kPreciseAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[376];
const QualifiedNameWithHash& kPreciselocationAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[377];
const QualifiedNameWithHash& kPreloadAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[378];
const QualifiedNameWithHash& kPrivatetokenAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[379];
const QualifiedNameWithHash& kPropertyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[380];
const QualifiedNameWithHash& kPseudoAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[381];
const QualifiedNameWithHash& kReadonlyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[382];
const QualifiedNameWithHash& kReferrerpolicyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[383];
const QualifiedNameWithHash& kRelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[384];
const QualifiedNameWithHash& kRequiredAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[385];
const QualifiedNameWithHash& kRevAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[386];
const QualifiedNameWithHash& kReversedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[387];
const QualifiedNameWithHash& kRoleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[388];
const QualifiedNameWithHash& kRowsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[389];
const QualifiedNameWithHash& kRowspanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[390];
const QualifiedNameWithHash& kRulesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[391];
const QualifiedNameWithHash& kSandboxAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[392];
const QualifiedNameWithHash& kSchemeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[393];
const QualifiedNameWithHash& kScopeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[394];
const QualifiedNameWithHash& kScrollamountAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[395];
const QualifiedNameWithHash& kScrolldelayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[396];
const QualifiedNameWithHash& kScrollingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[397];
const QualifiedNameWithHash& kSelectAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[398];
const QualifiedNameWithHash& kSelectedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[399];
const QualifiedNameWithHash& kSelectedcontentelementAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[400];
const QualifiedNameWithHash& kShadowrootAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[401];
const QualifiedNameWithHash& kShadowrootadoptedstylesheetsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[402];
const QualifiedNameWithHash& kShadowrootclonableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[403];
const QualifiedNameWithHash& kShadowrootcustomelementregistryAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[404];
const QualifiedNameWithHash& kShadowrootdelegatesfocusAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[405];
const QualifiedNameWithHash& kShadowrootmodeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[406];
const QualifiedNameWithHash& kShadowrootreferencetargetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[407];
const QualifiedNameWithHash& kShadowrootserializableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[408];
const QualifiedNameWithHash& kShapeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[409];
const QualifiedNameWithHash& kSharedstoragewritableAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[410];
const QualifiedNameWithHash& kSignatureAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[411];
const QualifiedNameWithHash& kSizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[412];
const QualifiedNameWithHash& kSizesAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[413];
const QualifiedNameWithHash& kSlotAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[414];
const QualifiedNameWithHash& kSpanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[415];
const QualifiedNameWithHash& kSpecifierAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[416];
const QualifiedNameWithHash& kSpellcheckAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[417];
const QualifiedNameWithHash& kSrcAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[418];
const QualifiedNameWithHash& kSrcdocAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[419];
const QualifiedNameWithHash& kSrclangAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[420];
const QualifiedNameWithHash& kSrcsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[421];
const QualifiedNameWithHash& kStandbyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[422];
const QualifiedNameWithHash& kStartAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[423];
const QualifiedNameWithHash& kStepAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[424];
const QualifiedNameWithHash& kStyleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[425];
const QualifiedNameWithHash& kSummaryAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[426];
const QualifiedNameWithHash& kTabindexAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[427];
const QualifiedNameWithHash& kTargetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[428];
const QualifiedNameWithHash& kTextAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[429];
const QualifiedNameWithHash& kTitleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[430];
const QualifiedNameWithHash& kToolautosubmitAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[431];
const QualifiedNameWithHash& kTooldescriptionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[432];
const QualifiedNameWithHash& kToolnameAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[433];
const QualifiedNameWithHash& kToolparamdescriptionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[434];
const QualifiedNameWithHash& kTopmarginAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[435];
const QualifiedNameWithHash& kTranslateAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[436];
const QualifiedNameWithHash& kTruespeedAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[437];
const QualifiedNameWithHash& kTypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[438];
const QualifiedNameWithHash& kUsemapAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[439];
const QualifiedNameWithHash& kValignAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[440];
const QualifiedNameWithHash& kValueAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[441];
const QualifiedNameWithHash& kValuetypeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[442];
const QualifiedNameWithHash& kVersionAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[443];
const QualifiedNameWithHash& kVirtualkeyboardpolicyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[444];
const QualifiedNameWithHash& kVlinkAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[445];
const QualifiedNameWithHash& kVspaceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[446];
const QualifiedNameWithHash& kWatchAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[447];
const QualifiedNameWithHash& kWebkitdirectoryAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[448];
const QualifiedNameWithHash& kWidthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[449];
const QualifiedNameWithHash& kWrapAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[450];
const QualifiedNameWithHash& kWritingsuggestionsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[451];

base::HeapArray<const QualifiedName*> GetAttrs() {
  auto attrs = base::HeapArray<const QualifiedName*>::Uninit(kAttrsCount);
  for (size_t i = 0; i < kAttrsCount; ++i) {
    attrs[i] = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage) + i;
  }
  return attrs;
}


void Init() {
  struct NameEntry {
    const char* name;
    unsigned char length;
    unsigned char is_tag;
    unsigned char is_attr;
  };

  // Namespace
  // Use placement new to initialize the globals.
  new ((void*)&xhtmlNamespaceURI) AtomicString("http://www.w3.org/1999/xhtml");

  static constexpr NameEntry kNames[] = {
    { "a", 1, 1, 0 },
    { "abbr", 4, 1, 1 },
    { "accept", 6, 0, 1 },
    { "accept-charset", 14, 0, 1 },
    { "accesskey", 9, 0, 1 },
    { "accuracymode", 12, 0, 1 },
    { "acronym", 7, 1, 0 },
    { "action", 6, 0, 1 },
    { "adauctionheaders", 16, 0, 1 },
    { "address", 7, 1, 0 },
    { "align", 5, 0, 1 },
    { "alink", 5, 0, 1 },
    { "allow", 5, 0, 1 },
    { "allowfullscreen", 15, 0, 1 },
    { "allowpaymentrequest", 19, 0, 1 },
    { "alt", 3, 0, 1 },
    { "applet", 6, 1, 0 },
    { "archive", 7, 0, 1 },
    { "area", 4, 1, 0 },
    { "aria-actions", 12, 0, 1 },
    { "aria-activedescendant", 21, 0, 1 },
    { "aria-atomic", 11, 0, 1 },
    { "aria-autocomplete", 17, 0, 1 },
    { "aria-braillelabel", 17, 0, 1 },
    { "aria-brailleroledescription", 27, 0, 1 },
    { "aria-busy", 9, 0, 1 },
    { "aria-checked", 12, 0, 1 },
    { "aria-colcount", 13, 0, 1 },
    { "aria-colindex", 13, 0, 1 },
    { "aria-colindextext", 17, 0, 1 },
    { "aria-colspan", 12, 0, 1 },
    { "aria-controls", 13, 0, 1 },
    { "aria-current", 12, 0, 1 },
    { "aria-describedby", 16, 0, 1 },
    { "aria-description", 16, 0, 1 },
    { "aria-details", 12, 0, 1 },
    { "aria-disabled", 13, 0, 1 },
    { "aria-errormessage", 17, 0, 1 },
    { "aria-expanded", 13, 0, 1 },
    { "aria-flowto", 11, 0, 1 },
    { "aria-haspopup", 13, 0, 1 },
    { "aria-hidden", 11, 0, 1 },
    { "aria-invalid", 12, 0, 1 },
    { "aria-keyshortcuts", 17, 0, 1 },
    { "aria-label", 10, 0, 1 },
    { "aria-labeledby", 14, 0, 1 },
    { "aria-labelledby", 15, 0, 1 },
    { "aria-level", 10, 0, 1 },
    { "aria-live", 9, 0, 1 },
    { "aria-modal", 10, 0, 1 },
    { "aria-multiline", 14, 0, 1 },
    { "aria-multiselectable", 20, 0, 1 },
    { "aria-orientation", 16, 0, 1 },
    { "aria-owns", 9, 0, 1 },
    { "aria-placeholder", 16, 0, 1 },
    { "aria-posinset", 13, 0, 1 },
    { "aria-pressed", 12, 0, 1 },
    { "aria-readonly", 13, 0, 1 },
    { "aria-relevant", 13, 0, 1 },
    { "aria-required", 13, 0, 1 },
    { "aria-roledescription", 20, 0, 1 },
    { "aria-rowcount", 13, 0, 1 },
    { "aria-rowindex", 13, 0, 1 },
    { "aria-rowindextext", 17, 0, 1 },
    { "aria-rowspan", 12, 0, 1 },
    { "aria-selected", 13, 0, 1 },
    { "aria-setsize", 12, 0, 1 },
    { "aria-sort", 9, 0, 1 },
    { "aria-valuemax", 13, 0, 1 },
    { "aria-valuemin", 13, 0, 1 },
    { "aria-valuenow", 13, 0, 1 },
    { "aria-valuetext", 14, 0, 1 },
    { "aria-virtualcontent", 19, 0, 1 },
    { "article", 7, 1, 0 },
    { "as", 2, 0, 1 },
    { "aside", 5, 1, 0 },
    { "async", 5, 0, 1 },
    { "attributionsrc", 14, 0, 1 },
    { "audio", 5, 1, 0 },
    { "autocapitalize", 14, 0, 1 },
    { "autocomplete", 12, 0, 1 },
    { "autocorrect", 11, 0, 1 },
    { "autofocus", 9, 0, 1 },
    { "autolocate", 10, 0, 1 },
    { "autoplay", 8, 0, 1 },
    { "axis", 4, 0, 1 },
    { "b", 1, 1, 0 },
    { "background", 10, 0, 1 },
    { "base", 4, 1, 0 },
    { "basefont", 8, 1, 0 },
    { "bdi", 3, 1, 0 },
    { "bdo", 3, 1, 0 },
    { "behavior", 8, 0, 1 },
    { "bgcolor", 7, 0, 1 },
    { "bgsound", 7, 1, 0 },
    { "big", 3, 1, 0 },
    { "blocking", 8, 0, 1 },
    { "blockquote", 10, 1, 0 },
    { "body", 4, 1, 0 },
    { "border", 6, 0, 1 },
    { "bordercolor", 11, 0, 1 },
    { "br", 2, 1, 0 },
    { "browsingtopics", 14, 0, 1 },
    { "button", 6, 1, 0 },
    { "cachehint", 9, 0, 1 },
    { "canvas", 6, 1, 0 },
    { "caption", 7, 1, 0 },
    { "capture", 7, 0, 1 },
    { "cellpadding", 11, 0, 1 },
    { "cellspacing", 11, 0, 1 },
    { "center", 6, 1, 0 },
    { "challenge", 9, 0, 1 },
    { "char", 4, 0, 1 },
    { "charoff", 7, 0, 1 },
    { "charset", 7, 0, 1 },
    { "checkable", 9, 0, 1 },
    { "checked", 7, 0, 1 },
    { "cite", 4, 1, 1 },
    { "class", 5, 0, 1 },
    { "classid", 7, 0, 1 },
    { "clear", 5, 0, 1 },
    { "clientid", 8, 0, 1 },
    { "closedby", 8, 0, 1 },
    { "code", 4, 1, 1 },
    { "codebase", 8, 0, 1 },
    { "codetype", 8, 0, 1 },
    { "col", 3, 1, 0 },
    { "colgroup", 8, 1, 0 },
    { "color", 5, 0, 1 },
    { "cols", 4, 0, 1 },
    { "colspan", 7, 0, 1 },
    { "command", 7, 1, 1 },
    { "commandfor", 10, 0, 1 },
    { "compact", 7, 0, 1 },
    { "configurl", 9, 0, 1 },
    { "containertiming", 15, 0, 1 },
    { "containertiming-ignore", 22, 0, 1 },
    { "content", 7, 0, 1 },
    { "contenteditable", 15, 0, 1 },
    { "controls", 8, 0, 1 },
    { "controlslist", 12, 0, 1 },
    { "coords", 6, 0, 1 },
    { "credential", 10, 1, 0 },
    { "credentialless", 14, 0, 1 },
    { "crossorigin", 11, 0, 1 },
    { "csp", 3, 0, 1 },
    { "customelementregistry", 21, 0, 1 },
    { "data", 4, 1, 1 },
    { "data-src", 8, 0, 1 },
    { "datalist", 8, 1, 0 },
    { "datetime", 8, 0, 1 },
    { "dd", 2, 1, 0 },
    { "declare", 7, 0, 1 },
    { "decoding", 8, 0, 1 },
    { "default", 7, 0, 1 },
    { "defaultchecked", 14, 0, 1 },
    { "defer", 5, 0, 1 },
    { "del", 3, 1, 0 },
    { "delegatesfocus", 14, 0, 1 },
    { "details", 7, 1, 0 },
    { "dfn", 3, 1, 0 },
    { "dialog", 6, 1, 0 },
    { "dir", 3, 1, 1 },
    { "direction", 9, 0, 1 },
    { "dirname", 7, 0, 1 },
    { "disabled", 8, 0, 1 },
    { "disablepictureinpicture", 23, 0, 1 },
    { "disableremoteplayback", 21, 0, 1 },
    { "div", 3, 1, 0 },
    { "dl", 2, 1, 0 },
    { "domainhint", 10, 0, 1 },
    { "download", 8, 0, 1 },
    { "draggable", 9, 0, 1 },
    { "dt", 2, 1, 0 },
    { "elementtiming", 13, 0, 1 },
    { "em", 2, 1, 0 },
    { "embed", 5, 1, 0 },
    { "enctype", 7, 0, 1 },
    { "end", 3, 0, 1 },
    { "enterkeyhint", 12, 0, 1 },
    { "event", 5, 0, 1 },
    { "exportparts", 11, 0, 1 },
    { "face", 4, 0, 1 },
    { "fencedframe", 11, 1, 0 },
    { "fetchpriority", 13, 0, 1 },
    { "fields", 6, 0, 1 },
    { "fieldset", 8, 1, 0 },
    { "figcaption", 10, 1, 0 },
    { "figure", 6, 1, 0 },
    { "filter", 6, 0, 1 },
    { "focusgroup", 10, 0, 1 },
    { "focusgroupstart", 15, 0, 1 },
    { "font", 4, 1, 0 },
    { "footer", 6, 1, 0 },
    { "for", 3, 0, 1 },
    { "form", 4, 1, 1 },
    { "formaction", 10, 0, 1 },
    { "formenctype", 11, 0, 1 },
    { "formmethod", 10, 0, 1 },
    { "formnovalidate", 14, 0, 1 },
    { "formtarget", 10, 0, 1 },
    { "frame", 5, 1, 1 },
    { "frameborder", 11, 0, 1 },
    { "frameset", 8, 1, 0 },
    { "geolocation", 11, 1, 0 },
    { "h1", 2, 1, 0 },
    { "h2", 2, 1, 0 },
    { "h3", 2, 1, 0 },
    { "h4", 2, 1, 0 },
    { "h5", 2, 1, 0 },
    { "h6", 2, 1, 0 },
    { "head", 4, 1, 0 },
    { "header", 6, 1, 0 },
    { "headers", 7, 0, 1 },
    { "headingoffset", 13, 0, 1 },
    { "headingreset", 12, 0, 1 },
    { "height", 6, 0, 1 },
    { "hgroup", 6, 1, 0 },
    { "hidden", 6, 0, 1 },
    { "high", 4, 0, 1 },
    { "hr", 2, 1, 0 },
    { "href", 4, 0, 1 },
    { "hreflang", 8, 0, 1 },
    { "hreftranslate", 13, 0, 1 },
    { "hspace", 6, 0, 1 },
    { "html", 4, 1, 0 },
    { "http-equiv", 10, 0, 1 },
    { "i", 1, 1, 0 },
    { "id", 2, 0, 1 },
    { "iframe", 6, 1, 0 },
    { "image", 5, 1, 0 },
    { "imagesizes", 10, 0, 1 },
    { "imagesrcset", 11, 0, 1 },
    { "img", 3, 1, 0 },
    { "incremental", 11, 0, 1 },
    { "inert", 5, 0, 1 },
    { "input", 5, 1, 0 },
    { "inputmode", 9, 0, 1 },
    { "ins", 3, 1, 0 },
    { "install", 7, 1, 0 },
    { "installurl", 10, 0, 1 },
    { "integrity", 9, 0, 1 },
    { "interestfor", 11, 0, 1 },
    { "invisible", 9, 0, 1 },
    { "is", 2, 0, 1 },
    { "ismap", 5, 0, 1 },
    { "itemprop", 8, 0, 1 },
    { "kbd", 3, 1, 0 },
    { "keygen", 6, 1, 0 },
    { "keytype", 7, 0, 1 },
    { "kind", 4, 0, 1 },
    { "label", 5, 1, 1 },
    { "lang", 4, 0, 1 },
    { "language", 8, 0, 1 },
    { "latencyhint", 11, 0, 1 },
    { "layer", 5, 1, 0 },
    { "layoutsubtree", 13, 0, 1 },
    { "leftmargin", 10, 0, 1 },
    { "legend", 6, 1, 0 },
    { "li", 2, 1, 0 },
    { "link", 4, 1, 1 },
    { "list", 4, 0, 1 },
    { "listing", 7, 1, 0 },
    { "loading", 7, 0, 1 },
    { "login", 5, 1, 0 },
    { "loginhint", 9, 0, 1 },
    { "longdesc", 8, 0, 1 },
    { "loop", 4, 0, 1 },
    { "low", 3, 0, 1 },
    { "lowsrc", 6, 0, 1 },
    { "main", 4, 1, 0 },
    { "manifest", 8, 0, 1 },
    { "manifestid", 10, 0, 1 },
    { "map", 3, 1, 0 },
    { "marginheight", 12, 0, 1 },
    { "marginwidth", 11, 0, 1 },
    { "mark", 4, 1, 0 },
    { "marker", 6, 0, 1 },
    { "marquee", 7, 1, 0 },
    { "max", 3, 0, 1 },
    { "maxlength", 9, 0, 1 },
    { "mayscript", 9, 0, 1 },
    { "media", 5, 0, 1 },
    { "menu", 4, 1, 0 },
    { "menubar", 7, 1, 0 },
    { "menuitem", 8, 1, 0 },
    { "menulist", 8, 1, 0 },
    { "meta", 4, 1, 0 },
    { "meter", 5, 1, 0 },
    { "method", 6, 0, 1 },
    { "min", 3, 0, 1 },
    { "minlength", 9, 0, 1 },
    { "multiple", 8, 0, 1 },
    { "muted", 5, 0, 1 },
    { "name", 4, 0, 1 },
    { "nav", 3, 1, 0 },
    { "nobr", 4, 1, 0 },
    { "noembed", 7, 1, 0 },
    { "noframes", 8, 1, 0 },
    { "nohref", 6, 0, 1 },
    { "nolayer", 7, 1, 0 },
    { "nomodule", 8, 0, 1 },
    { "nonce", 5, 0, 1 },
    { "noresize", 8, 0, 1 },
    { "noscript", 8, 1, 0 },
    { "noshade", 7, 0, 1 },
    { "novalidate", 10, 0, 1 },
    { "nowrap", 6, 0, 1 },
    { "object", 6, 1, 1 },
    { "ol", 2, 1, 0 },
    { "onabort", 7, 0, 1 },
    { "onafterprint", 12, 0, 1 },
    { "onanimationcancel", 17, 0, 1 },
    { "onanimationend", 14, 0, 1 },
    { "onanimationiteration", 20, 0, 1 },
    { "onanimationstart", 16, 0, 1 },
    { "onautofill", 10, 0, 1 },
    { "onauxclick", 10, 0, 1 },
    { "onbeforecopy", 12, 0, 1 },
    { "onbeforecut", 11, 0, 1 },
    { "onbeforefilter", 14, 0, 1 },
    { "onbeforeinput", 13, 0, 1 },
    { "onbeforepaste", 13, 0, 1 },
    { "onbeforeprint", 13, 0, 1 },
    { "onbeforetoggle", 14, 0, 1 },
    { "onbeforeunload", 14, 0, 1 },
    { "onblur", 6, 0, 1 },
    { "oncancel", 8, 0, 1 },
    { "oncanplay", 9, 0, 1 },
    { "oncanplaythrough", 16, 0, 1 },
    { "onchange", 8, 0, 1 },
    { "onclick", 7, 0, 1 },
    { "onclose", 7, 0, 1 },
    { "oncommand", 9, 0, 1 },
    { "oncontentvisibilityautostatechange", 34, 0, 1 },
    { "oncontextlost", 13, 0, 1 },
    { "oncontextmenu", 13, 0, 1 },
    { "oncontextrestored", 17, 0, 1 },
    { "oncopy", 6, 0, 1 },
    { "oncuechange", 11, 0, 1 },
    { "oncut", 5, 0, 1 },
    { "ondblclick", 10, 0, 1 },
    { "ondismiss", 9, 0, 1 },
    { "ondrag", 6, 0, 1 },
    { "ondragend", 9, 0, 1 },
    { "ondragenter", 11, 0, 1 },
    { "ondragleave", 11, 0, 1 },
    { "ondragover", 10, 0, 1 },
    { "ondragstart", 11, 0, 1 },
    { "ondrop", 6, 0, 1 },
    { "ondurationchange", 16, 0, 1 },
    { "onemptied", 9, 0, 1 },
    { "onended", 7, 0, 1 },
    { "onerror", 7, 0, 1 },
    { "onfocus", 7, 0, 1 },
    { "onfocusin", 9, 0, 1 },
    { "onfocusout", 10, 0, 1 },
    { "onformdata", 10, 0, 1 },
    { "ongotpointercapture", 19, 0, 1 },
    { "onhashchange", 12, 0, 1 },
    { "oninput", 7, 0, 1 },
    { "oninvalid", 9, 0, 1 },
    { "onkeydown", 9, 0, 1 },
    { "onkeypress", 10, 0, 1 },
    { "onkeyup", 7, 0, 1 },
    { "onlanguagechange", 16, 0, 1 },
    { "onload", 6, 0, 1 },
    { "onloadeddata", 12, 0, 1 },
    { "onloadedmetadata", 16, 0, 1 },
    { "onloadstart", 11, 0, 1 },
    { "onlocation", 10, 0, 1 },
    { "onlostpointercapture", 20, 0, 1 },
    { "onmessage", 9, 0, 1 },
    { "onmessageerror", 14, 0, 1 },
    { "onmousedown", 11, 0, 1 },
    { "onmouseenter", 12, 0, 1 },
    { "onmouseleave", 12, 0, 1 },
    { "onmousemove", 11, 0, 1 },
    { "onmouseout", 10, 0, 1 },
    { "onmouseover", 11, 0, 1 },
    { "onmouseup", 9, 0, 1 },
    { "onmousewheel", 12, 0, 1 },
    { "onmove", 6, 0, 1 },
    { "onoffline", 9, 0, 1 },
    { "ononline", 8, 0, 1 },
    { "onorientationchange", 19, 0, 1 },
    { "onpagehide", 10, 0, 1 },
    { "onpageshow", 10, 0, 1 },
    { "onpaste", 7, 0, 1 },
    { "onpause", 7, 0, 1 },
    { "onplay", 6, 0, 1 },
    { "onplaying", 9, 0, 1 },
    { "onpointercancel", 15, 0, 1 },
    { "onpointerdown", 13, 0, 1 },
    { "onpointerenter", 14, 0, 1 },
    { "onpointerleave", 14, 0, 1 },
    { "onpointermove", 13, 0, 1 },
    { "onpointerout", 12, 0, 1 },
    { "onpointerover", 13, 0, 1 },
    { "onpointerrawupdate", 18, 0, 1 },
    { "onpointerup", 11, 0, 1 },
    { "onpopstate", 10, 0, 1 },
    { "onprogress", 10, 0, 1 },
    { "onpromptaction", 14, 0, 1 },
    { "onpromptdismiss", 15, 0, 1 },
    { "onratechange", 12, 0, 1 },
    { "onreset", 7, 0, 1 },
    { "onresize", 8, 0, 1 },
    { "onresolve", 9, 0, 1 },
    { "onscroll", 8, 0, 1 },
    { "onscrollend", 11, 0, 1 },
    { "onscrollsnapchange", 18, 0, 1 },
    { "onscrollsnapchanging", 20, 0, 1 },
    { "onsearch", 8, 0, 1 },
    { "onsecuritypolicyviolation", 25, 0, 1 },
    { "onseeked", 8, 0, 1 },
    { "onseeking", 9, 0, 1 },
    { "onselect", 8, 0, 1 },
    { "onselectionchange", 17, 0, 1 },
    { "onselectstart", 13, 0, 1 },
    { "onshow", 6, 0, 1 },
    { "onslotchange", 12, 0, 1 },
    { "onstalled", 9, 0, 1 },
    { "onstorage", 9, 0, 1 },
    { "onstream", 8, 0, 1 },
    { "onsubmit", 8, 0, 1 },
    { "onsuspend", 9, 0, 1 },
    { "ontimeupdate", 12, 0, 1 },
    { "ontimezonechange", 16, 0, 1 },
    { "ontoggle", 8, 0, 1 },
    { "ontouchcancel", 13, 0, 1 },
    { "ontouchend", 10, 0, 1 },
    { "ontouchmove", 11, 0, 1 },
    { "ontouchstart", 12, 0, 1 },
    { "ontransitionend", 15, 0, 1 },
    { "onunload", 8, 0, 1 },
    { "onvalidationstatuschange", 24, 0, 1 },
    { "onvolumechange", 14, 0, 1 },
    { "onwaiting", 9, 0, 1 },
    { "onwebkitanimationend", 20, 0, 1 },
    { "onwebkitanimationiteration", 26, 0, 1 },
    { "onwebkitanimationstart", 22, 0, 1 },
    { "onwebkitfullscreenchange", 24, 0, 1 },
    { "onwebkitfullscreenerror", 23, 0, 1 },
    { "onwebkittransitionend", 21, 0, 1 },
    { "onwheel", 7, 0, 1 },
    { "open", 4, 0, 1 },
    { "optgroup", 8, 1, 0 },
    { "optimum", 7, 0, 1 },
    { "option", 6, 1, 0 },
    { "output", 6, 1, 0 },
    { "overscrollarea", 14, 0, 1 },
    { "overscrollcontainer", 19, 0, 1 },
    { "p", 1, 1, 0 },
    { "param", 5, 1, 0 },
    { "params", 6, 0, 1 },
    { "parseparts", 10, 0, 1 },
    { "part", 4, 0, 1 },
    { "pattern", 7, 0, 1 },
    { "picture", 7, 1, 0 },
    { "ping", 4, 0, 1 },
    { "placeholder", 11, 0, 1 },
    { "plaintext", 9, 1, 0 },
    { "playsinline", 11, 0, 1 },
    { "policy", 6, 0, 1 },
    { "popover", 7, 0, 1 },
    { "popovertarget", 13, 0, 1 },
    { "popovertargetaction", 19, 0, 1 },
    { "poster", 6, 0, 1 },
    { "pre", 3, 1, 0 },
    { "precise", 7, 0, 1 },
    { "preciselocation", 15, 0, 1 },
    { "preload", 7, 0, 1 },
    { "privatetoken", 12, 0, 1 },
    { "progress", 8, 1, 0 },
    { "property", 8, 0, 1 },
    { "pseudo", 6, 0, 1 },
    { "q", 1, 1, 0 },
    { "rb", 2, 1, 0 },
    { "readonly", 8, 0, 1 },
    { "referrerpolicy", 14, 0, 1 },
    { "rel", 3, 0, 1 },
    { "required", 8, 0, 1 },
    { "rev", 3, 0, 1 },
    { "reversed", 8, 0, 1 },
    { "role", 4, 0, 1 },
    { "rows", 4, 0, 1 },
    { "rowspan", 7, 0, 1 },
    { "rp", 2, 1, 0 },
    { "rt", 2, 1, 0 },
    { "rtc", 3, 1, 0 },
    { "ruby", 4, 1, 0 },
    { "rules", 5, 0, 1 },
    { "s", 1, 1, 0 },
    { "samp", 4, 1, 0 },
    { "sandbox", 7, 0, 1 },
    { "scheme", 6, 0, 1 },
    { "scope", 5, 0, 1 },
    { "script", 6, 1, 0 },
    { "scrollamount", 12, 0, 1 },
    { "scrolldelay", 11, 0, 1 },
    { "scrolling", 9, 0, 1 },
    { "search", 6, 1, 0 },
    { "section", 7, 1, 0 },
    { "select", 6, 1, 1 },
    { "selected", 8, 0, 1 },
    { "selectedcontent", 15, 1, 0 },
    { "selectedcontentelement", 22, 0, 1 },
    { "shadowroot", 10, 0, 1 },
    { "shadowrootadoptedstylesheets", 28, 0, 1 },
    { "shadowrootclonable", 18, 0, 1 },
    { "shadowrootcustomelementregistry", 31, 0, 1 },
    { "shadowrootdelegatesfocus", 24, 0, 1 },
    { "shadowrootmode", 14, 0, 1 },
    { "shadowrootreferencetarget", 25, 0, 1 },
    { "shadowrootserializable", 22, 0, 1 },
    { "shape", 5, 0, 1 },
    { "sharedstoragewritable", 21, 0, 1 },
    { "signature", 9, 0, 1 },
    { "size", 4, 0, 1 },
    { "sizes", 5, 0, 1 },
    { "slot", 4, 1, 1 },
    { "small", 5, 1, 0 },
    { "source", 6, 1, 0 },
    { "span", 4, 1, 1 },
    { "specifier", 9, 0, 1 },
    { "spellcheck", 10, 0, 1 },
    { "src", 3, 0, 1 },
    { "srcdoc", 6, 0, 1 },
    { "srclang", 7, 0, 1 },
    { "srcset", 6, 0, 1 },
    { "standby", 7, 0, 1 },
    { "start", 5, 0, 1 },
    { "step", 4, 0, 1 },
    { "strike", 6, 1, 0 },
    { "strong", 6, 1, 0 },
    { "style", 5, 1, 1 },
    { "sub", 3, 1, 0 },
    { "summary", 7, 1, 1 },
    { "sup", 3, 1, 0 },
    { "tabindex", 8, 0, 1 },
    { "table", 5, 1, 0 },
    { "target", 6, 0, 1 },
    { "tbody", 5, 1, 0 },
    { "td", 2, 1, 0 },
    { "template", 8, 1, 0 },
    { "text", 4, 0, 1 },
    { "textarea", 8, 1, 0 },
    { "tfoot", 5, 1, 0 },
    { "th", 2, 1, 0 },
    { "thead", 5, 1, 0 },
    { "time", 4, 1, 0 },
    { "title", 5, 1, 1 },
    { "toolautosubmit", 14, 0, 1 },
    { "tooldescription", 15, 0, 1 },
    { "toolname", 8, 0, 1 },
    { "toolparamdescription", 20, 0, 1 },
    { "topmargin", 9, 0, 1 },
    { "tr", 2, 1, 0 },
    { "track", 5, 1, 0 },
    { "translate", 9, 0, 1 },
    { "truespeed", 9, 0, 1 },
    { "tt", 2, 1, 0 },
    { "type", 4, 0, 1 },
    { "u", 1, 1, 0 },
    { "ul", 2, 1, 0 },
    { "usemap", 6, 0, 1 },
    { "usermedia", 9, 1, 0 },
    { "valign", 6, 0, 1 },
    { "value", 5, 0, 1 },
    { "valuetype", 9, 0, 1 },
    { "var", 3, 1, 0 },
    { "version", 7, 0, 1 },
    { "video", 5, 1, 0 },
    { "virtualkeyboardpolicy", 21, 0, 1 },
    { "vlink", 5, 0, 1 },
    { "vspace", 6, 0, 1 },
    { "watch", 5, 0, 1 },
    { "wbr", 3, 1, 0 },
    { "webkitdirectory", 15, 0, 1 },
    { "width", 5, 0, 1 },
    { "wrap", 4, 0, 1 },
    { "writingsuggestions", 18, 0, 1 },
    { "xmp", 3, 1, 0 },
  };

  size_t tag_i = 0;
  size_t attr_i = 0;
  for (const NameEntry& name : kNames) {
    StringImpl* impl = StringImpl::CreateStatic(base::span(name.name, name.length));

    // We need a static version of the uppercase string, since the QualifiedNameWithHash
    // constructor will call LocalNameUpper(), and we cannot insert non-static strings
    // before we are done inserting static strings.
    char upper_buf[256];
    for (unsigned i = 0; i < name.length; ++i) {
      CHECK_LT(i, sizeof(upper_buf));
      upper_buf[i] = ToAsciiUpper(name.name[i]);
    }
    AtomicString upper(StringImpl::CreateStatic(base::span(upper_buf, name.length)));

    if (name.is_tag) {
      void* address = reinterpret_cast<HTMLQualifiedName*>(&tag_storage) + tag_i;
      QualifiedNameWithHash::CreateStatic(address, impl, xhtmlNamespaceURI);
      ++tag_i;
    }

    if (!name.is_attr)
      continue;
    void* address = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage) + attr_i;
    QualifiedNameWithHash::CreateStatic(address, impl);
    ++attr_i;
  }
  DCHECK_EQ(tag_i, kTagsCount);
  DCHECK_EQ(attr_i, kAttrsCount);
}

const blink::HTMLQualifiedName& TagToQualifiedName(
    HTMLTag tag) {
  switch (tag) {
    case HTMLTag::kA:
      return kATag;
    case HTMLTag::kAbbr:
      return kAbbrTag;
    case HTMLTag::kAcronym:
      return kAcronymTag;
    case HTMLTag::kAddress:
      return kAddressTag;
    case HTMLTag::kApplet:
      return kAppletTag;
    case HTMLTag::kArea:
      return kAreaTag;
    case HTMLTag::kArticle:
      return kArticleTag;
    case HTMLTag::kAside:
      return kAsideTag;
    case HTMLTag::kAudio:
      return kAudioTag;
    case HTMLTag::kB:
      return kBTag;
    case HTMLTag::kBase:
      return kBaseTag;
    case HTMLTag::kBasefont:
      return kBasefontTag;
    case HTMLTag::kBdi:
      return kBdiTag;
    case HTMLTag::kBdo:
      return kBdoTag;
    case HTMLTag::kBgsound:
      return kBgsoundTag;
    case HTMLTag::kBig:
      return kBigTag;
    case HTMLTag::kBlockquote:
      return kBlockquoteTag;
    case HTMLTag::kBody:
      return kBodyTag;
    case HTMLTag::kBr:
      return kBrTag;
    case HTMLTag::kButton:
      return kButtonTag;
    case HTMLTag::kCanvas:
      return kCanvasTag;
    case HTMLTag::kCaption:
      return kCaptionTag;
    case HTMLTag::kCenter:
      return kCenterTag;
    case HTMLTag::kCite:
      return kCiteTag;
    case HTMLTag::kCode:
      return kCodeTag;
    case HTMLTag::kCol:
      return kColTag;
    case HTMLTag::kColgroup:
      return kColgroupTag;
    case HTMLTag::kCommand:
      return kCommandTag;
    case HTMLTag::kCredential:
      return kCredentialTag;
    case HTMLTag::kData:
      return kDataTag;
    case HTMLTag::kDatalist:
      return kDatalistTag;
    case HTMLTag::kDd:
      return kDdTag;
    case HTMLTag::kDel:
      return kDelTag;
    case HTMLTag::kDetails:
      return kDetailsTag;
    case HTMLTag::kDfn:
      return kDfnTag;
    case HTMLTag::kDialog:
      return kDialogTag;
    case HTMLTag::kDir:
      return kDirTag;
    case HTMLTag::kDiv:
      return kDivTag;
    case HTMLTag::kDl:
      return kDlTag;
    case HTMLTag::kDt:
      return kDtTag;
    case HTMLTag::kEm:
      return kEmTag;
    case HTMLTag::kEmbed:
      return kEmbedTag;
    case HTMLTag::kFencedframeOrUnknown:
      return kFencedframeTag;
    case HTMLTag::kFieldset:
      return kFieldsetTag;
    case HTMLTag::kFigcaption:
      return kFigcaptionTag;
    case HTMLTag::kFigure:
      return kFigureTag;
    case HTMLTag::kFont:
      return kFontTag;
    case HTMLTag::kFooter:
      return kFooterTag;
    case HTMLTag::kForm:
      return kFormTag;
    case HTMLTag::kFrame:
      return kFrameTag;
    case HTMLTag::kFrameset:
      return kFramesetTag;
    case HTMLTag::kGeolocation:
      return kGeolocationTag;
    case HTMLTag::kH1:
      return kH1Tag;
    case HTMLTag::kH2:
      return kH2Tag;
    case HTMLTag::kH3:
      return kH3Tag;
    case HTMLTag::kH4:
      return kH4Tag;
    case HTMLTag::kH5:
      return kH5Tag;
    case HTMLTag::kH6:
      return kH6Tag;
    case HTMLTag::kHead:
      return kHeadTag;
    case HTMLTag::kHeader:
      return kHeaderTag;
    case HTMLTag::kHgroup:
      return kHgroupTag;
    case HTMLTag::kHr:
      return kHrTag;
    case HTMLTag::kHTML:
      return kHTMLTag;
    case HTMLTag::kI:
      return kITag;
    case HTMLTag::kIFrame:
      return kIFrameTag;
    case HTMLTag::kImage:
      return kImageTag;
    case HTMLTag::kImg:
      return kImgTag;
    case HTMLTag::kInput:
      return kInputTag;
    case HTMLTag::kIns:
      return kInsTag;
    case HTMLTag::kInstallOrUnknown:
      return kInstallTag;
    case HTMLTag::kKbd:
      return kKbdTag;
    case HTMLTag::kKeygen:
      return kKeygenTag;
    case HTMLTag::kLabel:
      return kLabelTag;
    case HTMLTag::kLayer:
      return kLayerTag;
    case HTMLTag::kLegend:
      return kLegendTag;
    case HTMLTag::kLi:
      return kLiTag;
    case HTMLTag::kLink:
      return kLinkTag;
    case HTMLTag::kListing:
      return kListingTag;
    case HTMLTag::kLogin:
      return kLoginTag;
    case HTMLTag::kMain:
      return kMainTag;
    case HTMLTag::kMap:
      return kMapTag;
    case HTMLTag::kMark:
      return kMarkTag;
    case HTMLTag::kMarquee:
      return kMarqueeTag;
    case HTMLTag::kMenu:
      return kMenuTag;
    case HTMLTag::kMenubar:
      return kMenubarTag;
    case HTMLTag::kMenuitem:
      return kMenuitemTag;
    case HTMLTag::kMenulist:
      return kMenulistTag;
    case HTMLTag::kMeta:
      return kMetaTag;
    case HTMLTag::kMeter:
      return kMeterTag;
    case HTMLTag::kNav:
      return kNavTag;
    case HTMLTag::kNobr:
      return kNobrTag;
    case HTMLTag::kNoembed:
      return kNoembedTag;
    case HTMLTag::kNoframes:
      return kNoframesTag;
    case HTMLTag::kNolayer:
      return kNolayerTag;
    case HTMLTag::kNoscript:
      return kNoscriptTag;
    case HTMLTag::kObject:
      return kObjectTag;
    case HTMLTag::kOl:
      return kOlTag;
    case HTMLTag::kOptgroup:
      return kOptgroupTag;
    case HTMLTag::kOption:
      return kOptionTag;
    case HTMLTag::kOutput:
      return kOutputTag;
    case HTMLTag::kP:
      return kPTag;
    case HTMLTag::kParam:
      return kParamTag;
    case HTMLTag::kPicture:
      return kPictureTag;
    case HTMLTag::kPlaintext:
      return kPlaintextTag;
    case HTMLTag::kPre:
      return kPreTag;
    case HTMLTag::kProgress:
      return kProgressTag;
    case HTMLTag::kQ:
      return kQTag;
    case HTMLTag::kRb:
      return kRbTag;
    case HTMLTag::kRp:
      return kRpTag;
    case HTMLTag::kRt:
      return kRtTag;
    case HTMLTag::kRTC:
      return kRTCTag;
    case HTMLTag::kRuby:
      return kRubyTag;
    case HTMLTag::kS:
      return kSTag;
    case HTMLTag::kSamp:
      return kSampTag;
    case HTMLTag::kScript:
      return kScriptTag;
    case HTMLTag::kSearch:
      return kSearchTag;
    case HTMLTag::kSection:
      return kSectionTag;
    case HTMLTag::kSelect:
      return kSelectTag;
    case HTMLTag::kSelectedcontent:
      return kSelectedcontentTag;
    case HTMLTag::kSlot:
      return kSlotTag;
    case HTMLTag::kSmall:
      return kSmallTag;
    case HTMLTag::kSource:
      return kSourceTag;
    case HTMLTag::kSpan:
      return kSpanTag;
    case HTMLTag::kStrike:
      return kStrikeTag;
    case HTMLTag::kStrong:
      return kStrongTag;
    case HTMLTag::kStyle:
      return kStyleTag;
    case HTMLTag::kSub:
      return kSubTag;
    case HTMLTag::kSummary:
      return kSummaryTag;
    case HTMLTag::kSup:
      return kSupTag;
    case HTMLTag::kTable:
      return kTableTag;
    case HTMLTag::kTbody:
      return kTbodyTag;
    case HTMLTag::kTd:
      return kTdTag;
    case HTMLTag::kTemplate:
      return kTemplateTag;
    case HTMLTag::kTextarea:
      return kTextareaTag;
    case HTMLTag::kTfoot:
      return kTfootTag;
    case HTMLTag::kTh:
      return kThTag;
    case HTMLTag::kThead:
      return kTheadTag;
    case HTMLTag::kTime:
      return kTimeTag;
    case HTMLTag::kTitle:
      return kTitleTag;
    case HTMLTag::kTr:
      return kTrTag;
    case HTMLTag::kTrack:
      return kTrackTag;
    case HTMLTag::kTt:
      return kTtTag;
    case HTMLTag::kU:
      return kUTag;
    case HTMLTag::kUl:
      return kUlTag;
    case HTMLTag::kUsermediaOrUnknown:
      return kUsermediaTag;
    case HTMLTag::kVar:
      return kVarTag;
    case HTMLTag::kVideo:
      return kVideoTag;
    case HTMLTag::kWbr:
      return kWbrTag;
    case HTMLTag::kXmp:
      return kXmpTag;
    case HTMLTag::kUnknown:
      return static_cast<const blink::HTMLQualifiedName&>(g_null_name);
  }
}

}  // namespace html_names
}  // namespace blink
