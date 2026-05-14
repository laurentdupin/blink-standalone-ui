// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_POINTER_LOCK_RESULT_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_POINTER_LOCK_RESULT_MOJOM_BLINK_FORWARD_H_

namespace blink::mojom::blink {

enum class PointerLockResult {
  kSuccess = 0,
  kUnsupportedOptions,
  kRequiresUserGesture,
  kUserRejected,
  kPermissionDenied,
  kAlreadyLocked,
  kWrongDocument,
  kElementDestroyed,
  kUserEscapeCooldown,
  kUnknownError,
};

}  // namespace blink::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_INPUT_POINTER_LOCK_RESULT_MOJOM_BLINK_FORWARD_H_
