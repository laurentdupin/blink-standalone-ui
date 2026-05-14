// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_MENU_SOURCE_TYPE_MOJOM_BLINK_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_MENU_SOURCE_TYPE_MOJOM_BLINK_H_

namespace ui::mojom::blink {

enum class MenuSourceType {
  kNone,
  kMouse,
  kKeyboard,
  kTouch,
  kTouchEditMenu,
};

}  // namespace ui::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_MENU_SOURCE_TYPE_MOJOM_BLINK_H_
