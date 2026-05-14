// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Generated from template:
//   templates/make_qualified_names.cc.tmpl
// and input files:
//   ..\..\third_party\blink\renderer\core\mathml\mathml_attribute_names.json5
//   ..\..\third_party\blink\renderer\core\mathml\mathml_tag_names.json5


#include "third_party/blink/renderer/core/mathml_names.h"

#include "base/containers/span.h"
#include "third_party/blink/renderer/platform/wtf/static_constructors.h"
#include "third_party/blink/renderer/platform/wtf/std_lib_extras.h"
#include "third_party/blink/renderer/platform/wtf/text/string_hasher.h"

namespace blink {
namespace mathml_names {

DEFINE_GLOBAL(, AtomicString, kNamespaceURI);

// Tags

void* tag_storage[kTagsCount * ((sizeof(MathMLQualifiedName) + sizeof(void *) - 1) / sizeof(void *))];
const MathMLQualifiedName& kAnnotationTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[0];
const MathMLQualifiedName& kAnnotationXmlTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[1];
const MathMLQualifiedName& kMactionTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[2];
const MathMLQualifiedName& kMalignmarkTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[3];
const MathMLQualifiedName& kMathTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[4];
const MathMLQualifiedName& kMerrorTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[5];
const MathMLQualifiedName& kMfracTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[6];
const MathMLQualifiedName& kMglyphTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[7];
const MathMLQualifiedName& kMiTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[8];
const MathMLQualifiedName& kMmultiscriptsTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[9];
const MathMLQualifiedName& kMnTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[10];
const MathMLQualifiedName& kMoTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[11];
const MathMLQualifiedName& kMoverTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[12];
const MathMLQualifiedName& kMpaddedTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[13];
const MathMLQualifiedName& kMphantomTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[14];
const MathMLQualifiedName& kMprescriptsTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[15];
const MathMLQualifiedName& kMrootTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[16];
const MathMLQualifiedName& kMrowTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[17];
const MathMLQualifiedName& kMsTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[18];
const MathMLQualifiedName& kMspaceTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[19];
const MathMLQualifiedName& kMsqrtTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[20];
const MathMLQualifiedName& kMstyleTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[21];
const MathMLQualifiedName& kMsubTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[22];
const MathMLQualifiedName& kMsubsupTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[23];
const MathMLQualifiedName& kMsupTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[24];
const MathMLQualifiedName& kMtableTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[25];
const MathMLQualifiedName& kMtdTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[26];
const MathMLQualifiedName& kMtextTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[27];
const MathMLQualifiedName& kMtrTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[28];
const MathMLQualifiedName& kMunderTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[29];
const MathMLQualifiedName& kMunderoverTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[30];
const MathMLQualifiedName& kNoneTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[31];
const MathMLQualifiedName& kSemanticsTag = reinterpret_cast<MathMLQualifiedName*>(&tag_storage)[32];


base::HeapArray<const QualifiedName*> GetTags() {
  auto tags = base::HeapArray<const QualifiedName*>::Uninit(kTagsCount);
  for (size_t i = 0; i < kTagsCount; ++i) {
    tags[i] = reinterpret_cast<QualifiedNameWithHash*>(&tag_storage) + i;
  }
  return tags;
}

// Attributes

void* attr_storage[kAttrsCount * ((sizeof(QualifiedNameWithHash) + sizeof(void *) - 1) / sizeof(void *))];

const QualifiedNameWithHash& kAccentAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[0];
const QualifiedNameWithHash& kAccentunderAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[1];
const QualifiedNameWithHash& kColumnspanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[2];
const QualifiedNameWithHash& kDefinitionURLAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[3];
const QualifiedNameWithHash& kDepthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[4];
const QualifiedNameWithHash& kDisplayAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[5];
const QualifiedNameWithHash& kDisplaystyleAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[6];
const QualifiedNameWithHash& kEncodingAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[7];
const QualifiedNameWithHash& kFenceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[8];
const QualifiedNameWithHash& kFormAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[9];
const QualifiedNameWithHash& kHeightAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[10];
const QualifiedNameWithHash& kLargeopAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[11];
const QualifiedNameWithHash& kLinethicknessAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[12];
const QualifiedNameWithHash& kLspaceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[13];
const QualifiedNameWithHash& kMathbackgroundAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[14];
const QualifiedNameWithHash& kMathcolorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[15];
const QualifiedNameWithHash& kMathsizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[16];
const QualifiedNameWithHash& kMathvariantAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[17];
const QualifiedNameWithHash& kMaxsizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[18];
const QualifiedNameWithHash& kMinsizeAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[19];
const QualifiedNameWithHash& kMovablelimitsAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[20];
const QualifiedNameWithHash& kRowspanAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[21];
const QualifiedNameWithHash& kRspaceAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[22];
const QualifiedNameWithHash& kScriptlevelAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[23];
const QualifiedNameWithHash& kSeparatorAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[24];
const QualifiedNameWithHash& kStretchyAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[25];
const QualifiedNameWithHash& kSymmetricAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[26];
const QualifiedNameWithHash& kVoffsetAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[27];
const QualifiedNameWithHash& kWidthAttr = reinterpret_cast<QualifiedNameWithHash*>(&attr_storage)[28];

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
  new ((void*)&kNamespaceURI) AtomicString("http://www.w3.org/1998/Math/MathML");

  static constexpr NameEntry kNames[] = {
    { "accent", 6, 0, 1 },
    { "accentunder", 11, 0, 1 },
    { "annotation", 10, 1, 0 },
    { "annotation-xml", 14, 1, 0 },
    { "columnspan", 10, 0, 1 },
    { "definitionURL", 13, 0, 1 },
    { "depth", 5, 0, 1 },
    { "display", 7, 0, 1 },
    { "displaystyle", 12, 0, 1 },
    { "encoding", 8, 0, 1 },
    { "fence", 5, 0, 1 },
    { "form", 4, 0, 1 },
    { "height", 6, 0, 1 },
    { "largeop", 7, 0, 1 },
    { "linethickness", 13, 0, 1 },
    { "lspace", 6, 0, 1 },
    { "maction", 7, 1, 0 },
    { "malignmark", 10, 1, 0 },
    { "math", 4, 1, 0 },
    { "mathbackground", 14, 0, 1 },
    { "mathcolor", 9, 0, 1 },
    { "mathsize", 8, 0, 1 },
    { "mathvariant", 11, 0, 1 },
    { "maxsize", 7, 0, 1 },
    { "merror", 6, 1, 0 },
    { "mfrac", 5, 1, 0 },
    { "mglyph", 6, 1, 0 },
    { "mi", 2, 1, 0 },
    { "minsize", 7, 0, 1 },
    { "mmultiscripts", 13, 1, 0 },
    { "mn", 2, 1, 0 },
    { "mo", 2, 1, 0 },
    { "movablelimits", 13, 0, 1 },
    { "mover", 5, 1, 0 },
    { "mpadded", 7, 1, 0 },
    { "mphantom", 8, 1, 0 },
    { "mprescripts", 11, 1, 0 },
    { "mroot", 5, 1, 0 },
    { "mrow", 4, 1, 0 },
    { "ms", 2, 1, 0 },
    { "mspace", 6, 1, 0 },
    { "msqrt", 5, 1, 0 },
    { "mstyle", 6, 1, 0 },
    { "msub", 4, 1, 0 },
    { "msubsup", 7, 1, 0 },
    { "msup", 4, 1, 0 },
    { "mtable", 6, 1, 0 },
    { "mtd", 3, 1, 0 },
    { "mtext", 5, 1, 0 },
    { "mtr", 3, 1, 0 },
    { "munder", 6, 1, 0 },
    { "munderover", 10, 1, 0 },
    { "none", 4, 1, 0 },
    { "rowspan", 7, 0, 1 },
    { "rspace", 6, 0, 1 },
    { "scriptlevel", 11, 0, 1 },
    { "semantics", 9, 1, 0 },
    { "separator", 9, 0, 1 },
    { "stretchy", 8, 0, 1 },
    { "symmetric", 9, 0, 1 },
    { "voffset", 7, 0, 1 },
    { "width", 5, 0, 1 },
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
      void* address = reinterpret_cast<MathMLQualifiedName*>(&tag_storage) + tag_i;
      QualifiedNameWithHash::CreateStatic(address, impl, kNamespaceURI);
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


}  // namespace mathml_names
}  // namespace blink
