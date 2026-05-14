// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_MESSAGING_BLINK_TRANSFERABLE_MESSAGE_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_MESSAGING_BLINK_TRANSFERABLE_MESSAGE_H_

#include "third_party/blink/renderer/core/core_export.h"

namespace blink {

// Standalone renderer builds disable script, workers and cross-frame messaging.
// Keep the type complete for Blink APIs that take it by value, without pulling
// transferable message serialization, blob mojoms or GPU shared-image support.
struct CORE_EXPORT BlinkTransferableMessage {};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_MESSAGING_BLINK_TRANSFERABLE_MESSAGE_H_
