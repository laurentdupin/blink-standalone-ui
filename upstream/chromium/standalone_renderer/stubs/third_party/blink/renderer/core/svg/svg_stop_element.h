#ifndef STANDALONE_STUB_THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_STOP_ELEMENT_H_
#define STANDALONE_STUB_THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_STOP_ELEMENT_H_

#include "C:/Repos/blink-standalone-ui/upstream/chromium/third_party/blink/renderer/core/svg/svg_stop_element.h"

namespace blink {

template <>
struct DowncastTraits<SVGStopElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGStopElement;
  }
};

}  // namespace blink

#endif  // STANDALONE_STUB_THIRD_PARTY_BLINK_RENDERER_CORE_SVG_SVG_STOP_ELEMENT_H_
