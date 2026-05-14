// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.h.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\xml\xml_attribute_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_XML_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_XML_NAMES_H_

#include "base/containers/heap_array.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/qualified_name.h"

namespace blink {

class XMLQualifiedName : public QualifiedNameWithHash { };

namespace xml_names {

// Namespace
CORE_EXPORT extern const AtomicString& kNamespaceURI;

// Tags



// Attributes
CORE_EXPORT extern const blink::QualifiedNameWithHash& kLangAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kSpaceAttr;


constexpr unsigned kAttrsCount = 2;
CORE_EXPORT base::HeapArray<const QualifiedName*> GetAttrs();


void Init();

}  // namespace xml_names
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_XML_NAMES_H_
