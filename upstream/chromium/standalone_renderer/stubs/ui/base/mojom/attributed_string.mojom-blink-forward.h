#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_ATTRIBUTED_STRING_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_ATTRIBUTED_STRING_MOJOM_BLINK_FORWARD_H_

#include <memory>
#include <vector>

#include "third_party/blink/renderer/platform/wtf/text/wtf_string.h"
#include "ui/gfx/range/range.h"

namespace ui::mojom::blink {

struct FontAttribute {
  String font_name;
  float font_point_size = 0.0f;
  gfx::Range effective_range;
};

struct AttributedString {
  String string;
  std::vector<FontAttribute> attributes;
};
using AttributedStringPtr = std::unique_ptr<AttributedString>;

}  // namespace ui::mojom::blink

#endif  // STANDALONE_RENDERER_STUBS_UI_BASE_MOJOM_ATTRIBUTED_STRING_MOJOM_BLINK_FORWARD_H_
