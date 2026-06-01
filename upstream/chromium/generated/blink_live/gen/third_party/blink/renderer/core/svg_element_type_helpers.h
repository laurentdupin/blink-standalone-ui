// Minimal standalone probe substitute for Blink's generated SVG type helper.
// The real file is generated from svg_tag_names.json5.

#ifndef THIRD_PARTY_BLINK_RENDERER_CORE_SVG_ELEMENT_TYPE_HELPERS_H_
#define THIRD_PARTY_BLINK_RENDERER_CORE_SVG_ELEMENT_TYPE_HELPERS_H_

#include "third_party/blink/renderer/core/element_type_enum.h"
#include "third_party/blink/renderer/core/svg/svg_element.h"

namespace blink {

class SVGRectElement;
class SVGStyleElement;
class SVGFEImageElement;
class SVGForeignObjectElement;
class SVGImageElement;

template <>
struct DowncastTraits<SVGRectElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGRectElement;
  }
};

template <>
struct DowncastTraits<SVGStyleElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGStyleElement;
  }
};

template <>
struct DowncastTraits<SVGFEImageElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGFEImageElement;
  }
};

template <>
struct DowncastTraits<SVGForeignObjectElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGForeignObjectElement;
  }
};

template <>
struct DowncastTraits<SVGImageElement> {
  static bool AllowFrom(const Node& node) {
    return node.GetElementType() == ElementType::kSVGImageElement;
  }
};

}  // namespace blink

#endif  // THIRD_PARTY_BLINK_RENDERER_CORE_SVG_ELEMENT_TYPE_HELPERS_H_
