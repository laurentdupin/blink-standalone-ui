// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.h.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\svg\xlink_attribute_names.json5


#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_XLINK_NAMES_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_XLINK_NAMES_H_

#include "base/containers/heap_array.h"
#include "third_party/blink/renderer/core/core_export.h"
#include "third_party/blink/renderer/core/dom/qualified_name.h"

namespace blink {

class XLinkQualifiedName : public QualifiedNameWithHash { };

namespace xlink_names {

// Namespace
CORE_EXPORT extern const AtomicString& kNamespaceURI;

// Tags



// Attributes
CORE_EXPORT extern const blink::QualifiedNameWithHash& kActuateAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kArcroleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kHrefAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kRoleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kShowAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTitleAttr;
CORE_EXPORT extern const blink::QualifiedNameWithHash& kTypeAttr;


constexpr unsigned kAttrsCount = 7;
CORE_EXPORT base::HeapArray<const QualifiedName*> GetAttrs();


void Init();

}  // namespace xlink_names
}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_XLINK_NAMES_H_
