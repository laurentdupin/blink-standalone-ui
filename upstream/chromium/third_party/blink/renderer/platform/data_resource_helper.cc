// Copyright 2014 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "third_party/blink/renderer/platform/data_resource_helper.h"

#if !defined(STANDALONE_RENDERER_GN_PROBE)
#include "third_party/blink/public/platform/platform.h"
#endif
#include "third_party/blink/renderer/platform/wtf/shared_buffer.h"
#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"

namespace blink {

String UncompressResourceAsString(int resource_id) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
  return String();
#else
  std::string data = Platform::Current()->GetDataResourceString(resource_id);
  return String::FromUtf8(data);
#endif
}

String UncompressResourceAsASCIIString(int resource_id) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
  return String();
#else
  String result(Platform::Current()->GetDataResourceString(resource_id));
  DCHECK(result.ContainsOnlyAsciiOrEmpty());
  return result;
#endif
}

Vector<char> UncompressResourceAsBinary(int resource_id) {
#if defined(STANDALONE_RENDERER_GN_PROBE)
  return Vector<char>();
#else
  std::string data = Platform::Current()->GetDataResourceString(resource_id);
  Vector<char> result;
  result.append_range(data);
  return result;
#endif
}

}  // namespace blink
