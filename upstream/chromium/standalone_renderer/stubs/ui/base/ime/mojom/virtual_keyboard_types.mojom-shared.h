// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_VIRTUAL_KEYBOARD_TYPES_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_VIRTUAL_KEYBOARD_TYPES_MOJOM_SHARED_H_

namespace ui::mojom {

enum class VirtualKeyboardVisibilityRequest {
  NONE,
  SHOW,
  HIDE,
};

enum class VirtualKeyboardPolicy {
  AUTO,
  MANUAL,
};

}  // namespace ui::mojom

#endif  // STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_VIRTUAL_KEYBOARD_TYPES_MOJOM_SHARED_H_
