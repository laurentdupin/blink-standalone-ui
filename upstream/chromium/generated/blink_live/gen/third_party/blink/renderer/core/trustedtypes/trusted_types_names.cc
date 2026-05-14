// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_names.cc.tmpl
// and input files:
//   ../../third_party/blink/renderer/core/trustedtypes/trusted_types_names.json5


#include "third_party/blink/renderer/core/trustedtypes/trusted_types_names.h"

#include <iterator>

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_hasher.h"

namespace blink {
namespace trusted_types_names {

void* names_storage[kNamesCount * ((sizeof(AtomicString) + sizeof(void *) - 1) / sizeof(void *))];

const AtomicString& kDOMParser = reinterpret_cast<AtomicString*>(&names_storage)[0];
const AtomicString& kDocument = reinterpret_cast<AtomicString*>(&names_storage)[1];
const AtomicString& kElement = reinterpret_cast<AtomicString*>(&names_storage)[2];
const AtomicString& kFunction = reinterpret_cast<AtomicString*>(&names_storage)[3];
const AtomicString& kHTMLEmbedElement = reinterpret_cast<AtomicString*>(&names_storage)[4];
const AtomicString& kHTMLIFrameElement = reinterpret_cast<AtomicString*>(&names_storage)[5];
const AtomicString& kHTMLObjectElement = reinterpret_cast<AtomicString*>(&names_storage)[6];
const AtomicString& kHTMLScriptElement = reinterpret_cast<AtomicString*>(&names_storage)[7];
const AtomicString& kLocation = reinterpret_cast<AtomicString*>(&names_storage)[8];
const AtomicString& kNode = reinterpret_cast<AtomicString*>(&names_storage)[9];
const AtomicString& kRange = reinterpret_cast<AtomicString*>(&names_storage)[10];
const AtomicString& kSVGAnimatedString = reinterpret_cast<AtomicString*>(&names_storage)[11];
const AtomicString& kSVGScriptElement = reinterpret_cast<AtomicString*>(&names_storage)[12];
const AtomicString& kServiceWorkerContainer = reinterpret_cast<AtomicString*>(&names_storage)[13];
const AtomicString& kShadowRoot = reinterpret_cast<AtomicString*>(&names_storage)[14];
const AtomicString& kSharedWorker = reinterpret_cast<AtomicString*>(&names_storage)[15];
const AtomicString& kStorageAccessHandle = reinterpret_cast<AtomicString*>(&names_storage)[16];
const AtomicString& kWindow = reinterpret_cast<AtomicString*>(&names_storage)[17];
const AtomicString& kWorker = reinterpret_cast<AtomicString*>(&names_storage)[18];
const AtomicString& kWorkerGlobalScope = reinterpret_cast<AtomicString*>(&names_storage)[19];
const AtomicString& kAfter = reinterpret_cast<AtomicString*>(&names_storage)[20];
const AtomicString& kAfterHTML = reinterpret_cast<AtomicString*>(&names_storage)[21];
const AtomicString& kAfterHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[22];
const AtomicString& kAppend = reinterpret_cast<AtomicString*>(&names_storage)[23];
const AtomicString& kAppendHTML = reinterpret_cast<AtomicString*>(&names_storage)[24];
const AtomicString& kAppendHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[25];
const AtomicString& kBaseVal = reinterpret_cast<AtomicString*>(&names_storage)[26];
const AtomicString& kBefore = reinterpret_cast<AtomicString*>(&names_storage)[27];
const AtomicString& kBeforeHTML = reinterpret_cast<AtomicString*>(&names_storage)[28];
const AtomicString& kBeforeHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[29];
const AtomicString& kCodeBase = reinterpret_cast<AtomicString*>(&names_storage)[30];
const AtomicString& kConstructor = reinterpret_cast<AtomicString*>(&names_storage)[31];
const AtomicString& kCreate = reinterpret_cast<AtomicString*>(&names_storage)[32];
const AtomicString& kCreateContextualFragment = reinterpret_cast<AtomicString*>(&names_storage)[33];
const AtomicString& kData = reinterpret_cast<AtomicString*>(&names_storage)[34];
const AtomicString& kEval = reinterpret_cast<AtomicString*>(&names_storage)[35];
const AtomicString& kExecCommand = reinterpret_cast<AtomicString*>(&names_storage)[36];
const AtomicString& kHref = reinterpret_cast<AtomicString*>(&names_storage)[37];
const AtomicString& kImportScripts = reinterpret_cast<AtomicString*>(&names_storage)[38];
const AtomicString& kInnerHTML = reinterpret_cast<AtomicString*>(&names_storage)[39];
const AtomicString& kInnerText = reinterpret_cast<AtomicString*>(&names_storage)[40];
const AtomicString& kInsertAdjacentHTML = reinterpret_cast<AtomicString*>(&names_storage)[41];
const AtomicString& kOuterHTML = reinterpret_cast<AtomicString*>(&names_storage)[42];
const AtomicString& kParseFromString = reinterpret_cast<AtomicString*>(&names_storage)[43];
const AtomicString& kParseHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[44];
const AtomicString& kPrepend = reinterpret_cast<AtomicString*>(&names_storage)[45];
const AtomicString& kPrependHTML = reinterpret_cast<AtomicString*>(&names_storage)[46];
const AtomicString& kPrependHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[47];
const AtomicString& kRegister = reinterpret_cast<AtomicString*>(&names_storage)[48];
const AtomicString& kReplace = reinterpret_cast<AtomicString*>(&names_storage)[49];
const AtomicString& kReplaceChildren = reinterpret_cast<AtomicString*>(&names_storage)[50];
const AtomicString& kReplaceWith = reinterpret_cast<AtomicString*>(&names_storage)[51];
const AtomicString& kReplaceWithHTML = reinterpret_cast<AtomicString*>(&names_storage)[52];
const AtomicString& kReplaceWithHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[53];
const AtomicString& kSetHTML = reinterpret_cast<AtomicString*>(&names_storage)[54];
const AtomicString& kSetHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[55];
const AtomicString& kSetInterval = reinterpret_cast<AtomicString*>(&names_storage)[56];
const AtomicString& kSetTimeout = reinterpret_cast<AtomicString*>(&names_storage)[57];
const AtomicString& kSrc = reinterpret_cast<AtomicString*>(&names_storage)[58];
const AtomicString& kSrcdoc = reinterpret_cast<AtomicString*>(&names_storage)[59];
const AtomicString& kStreamAfterHTML = reinterpret_cast<AtomicString*>(&names_storage)[60];
const AtomicString& kStreamAfterHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[61];
const AtomicString& kStreamAppendHTML = reinterpret_cast<AtomicString*>(&names_storage)[62];
const AtomicString& kStreamAppendHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[63];
const AtomicString& kStreamBeforeHTML = reinterpret_cast<AtomicString*>(&names_storage)[64];
const AtomicString& kStreamBeforeHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[65];
const AtomicString& kStreamHTML = reinterpret_cast<AtomicString*>(&names_storage)[66];
const AtomicString& kStreamHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[67];
const AtomicString& kStreamPrependHTML = reinterpret_cast<AtomicString*>(&names_storage)[68];
const AtomicString& kStreamPrependHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[69];
const AtomicString& kStreamReplaceWithHTML = reinterpret_cast<AtomicString*>(&names_storage)[70];
const AtomicString& kStreamReplaceWithHTMLUnsafe = reinterpret_cast<AtomicString*>(&names_storage)[71];
const AtomicString& kText = reinterpret_cast<AtomicString*>(&names_storage)[72];
const AtomicString& kTextContent = reinterpret_cast<AtomicString*>(&names_storage)[73];
const AtomicString& kWrite = reinterpret_cast<AtomicString*>(&names_storage)[74];
const AtomicString& kWriteln = reinterpret_cast<AtomicString*>(&names_storage)[75];

void Init() {
  static bool is_loaded = false;
  if (is_loaded) return;
  is_loaded = true;

  struct NameEntry {
    const char* name;
    unsigned char length;
  };

  static constexpr NameEntry kNames[] = {
    { "DOMParser", 9 },
    { "Document", 8 },
    { "Element", 7 },
    { "Function", 8 },
    { "HTMLEmbedElement", 16 },
    { "HTMLIFrameElement", 17 },
    { "HTMLObjectElement", 17 },
    { "HTMLScriptElement", 17 },
    { "Location", 8 },
    { "Node", 4 },
    { "Range", 5 },
    { "SVGAnimatedString", 17 },
    { "SVGScriptElement", 16 },
    { "ServiceWorkerContainer", 22 },
    { "ShadowRoot", 10 },
    { "SharedWorker", 12 },
    { "StorageAccessHandle", 19 },
    { "Window", 6 },
    { "Worker", 6 },
    { "WorkerGlobalScope", 17 },
    { "after", 5 },
    { "afterHTML", 9 },
    { "afterHTMLUnsafe", 15 },
    { "append", 6 },
    { "appendHTML", 10 },
    { "appendHTMLUnsafe", 16 },
    { "baseVal", 7 },
    { "before", 6 },
    { "beforeHTML", 10 },
    { "beforeHTMLUnsafe", 16 },
    { "codeBase", 8 },
    { "constructor", 11 },
    { "create", 6 },
    { "createContextualFragment", 24 },
    { "data", 4 },
    { "eval", 4 },
    { "execCommand", 11 },
    { "href", 4 },
    { "importScripts", 13 },
    { "innerHTML", 9 },
    { "innerText", 9 },
    { "insertAdjacentHTML", 18 },
    { "outerHTML", 9 },
    { "parseFromString", 15 },
    { "parseHTMLUnsafe", 15 },
    { "prepend", 7 },
    { "prependHTML", 11 },
    { "prependHTMLUnsafe", 17 },
    { "register", 8 },
    { "replace", 7 },
    { "replaceChildren", 15 },
    { "replaceWith", 11 },
    { "replaceWithHTML", 15 },
    { "replaceWithHTMLUnsafe", 21 },
    { "setHTML", 7 },
    { "setHTMLUnsafe", 13 },
    { "setInterval", 11 },
    { "setTimeout", 10 },
    { "src", 3 },
    { "srcdoc", 6 },
    { "streamAfterHTML", 15 },
    { "streamAfterHTMLUnsafe", 21 },
    { "streamAppendHTML", 16 },
    { "streamAppendHTMLUnsafe", 22 },
    { "streamBeforeHTML", 16 },
    { "streamBeforeHTMLUnsafe", 22 },
    { "streamHTML", 10 },
    { "streamHTMLUnsafe", 16 },
    { "streamPrependHTML", 17 },
    { "streamPrependHTMLUnsafe", 23 },
    { "streamReplaceWithHTML", 21 },
    { "streamReplaceWithHTMLUnsafe", 27 },
    { "text", 4 },
    { "textContent", 11 },
    { "write", 5 },
    { "writeln", 7 },
  };

  for (size_t i = 0; i < std::size(kNames); ++i) {
    StringImpl* impl = StringImpl::CreateStatic(base::span(kNames[i].name, kNames[i].length));
    void* address = reinterpret_cast<AtomicString*>(&names_storage) + i;
    new (address) AtomicString(impl);
  }
}

}  // namespace trusted_types_names
}  // namespace blink
