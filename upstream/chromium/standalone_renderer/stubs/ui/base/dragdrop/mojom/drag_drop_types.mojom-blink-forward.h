// Copyright 2026 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_DRAGDROP_MOJOM_DRAG_DROP_TYPES_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_DRAGDROP_MOJOM_DRAG_DROP_TYPES_MOJOM_BLINK_FORWARD_H_

namespace ui::mojom::blink {

enum class DragEventSource {
  kMouse,
  kTouch,
};

enum class DragOperation {
  kNone = 0,
  kCopy = 1,
  kLink = 2,
  kMove = 16,
};

}  // namespace ui::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_UI_BASE_DRAGDROP_MOJOM_DRAG_DROP_TYPES_MOJOM_BLINK_FORWARD_H_
