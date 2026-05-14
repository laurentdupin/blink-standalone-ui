// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.cc.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\xml\xmlns_attribute_names.json5


#include "third_party/blink/renderer/core/xmlns_names.h"

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/static_constructors.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_hasher.h"

namespace blink {
namespace xmlns_names {

DEFINE_GLOBAL(, AtomicString, kNamespaceURI);

// Attributes

void* attr_storage[kAttrsCount * ((sizeof(QualifiedNameWithHash) + sizeof(void *) - 1) / sizeof(void *))];

const QualifiedNameWithHash& kXmlnsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[0];

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
  new ((void*)&kNamespaceURI) AtomicString("http://www.w3.org/2000/xmlns/");

  static constexpr NameEntry kNames[] = {
    { "xmlns", 5, 0, 1 },
  };

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

    void* address = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage) + attr_i;
    QualifiedNameWithHash::CreateStatic(address, impl, kNamespaceURI);
    ++attr_i;
  }
  DCHECK_EQ(attr_i, kAttrsCount);
}


}  // namespace xmlns_names
}  // namespace blink
