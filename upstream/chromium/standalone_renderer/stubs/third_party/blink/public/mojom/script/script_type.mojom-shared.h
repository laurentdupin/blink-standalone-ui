// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_TYPE_MOJOM_SHARED_H_
#define THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_TYPE_MOJOM_SHARED_H_

namespace blink::mojom {

#if !defined(STANDALONE_RENDERER_SCRIPT_TYPE_DEFINED)
#define STANDALONE_RENDERER_SCRIPT_TYPE_DEFINED
enum class ScriptType {
  kClassic,
  kModule,
};
#endif

}  // namespace blink::mojom

#endif  // THIRD_PARTY_BLINK_PUBLIC_MOJOM_SCRIPT_SCRIPT_TYPE_MOJOM_SHARED_H_
