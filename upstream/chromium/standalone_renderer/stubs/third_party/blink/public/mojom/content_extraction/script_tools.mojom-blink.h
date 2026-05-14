// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTENT_EXTRACTION_SCRIPT_TOOLS_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTENT_EXTRACTION_SCRIPT_TOOLS_MOJOM_BLINK_H_

#include "third_party/blink/public/mojom/content_extraction/script_tools.mojom-blink-forward.h"

#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink::mojom::blink {

class ScriptToolAnnotations {
 public:
  bool read_only = false;
  bool untrusted_content = false;
};

class ScriptTool {
 public:
  ::blink::String name;
  ::blink::String description;
  ::blink::String input_schema;
  ScriptToolAnnotationsPtr annotations;
};

class ScriptToolHost {
 public:
  class Proxy_ {};
  virtual ~ScriptToolHost() = default;
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_CONTENT_EXTRACTION_SCRIPT_TOOLS_MOJOM_BLINK_H_
