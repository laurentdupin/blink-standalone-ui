#include "third_party/blink/renderer/core/css/font_face.h"

namespace blink {

FontFace* FontFace::Create(
    Document*,
    const CascadeLayered<const StyleRuleFontFace>&,
    bool) {
  return nullptr;
}

}  // namespace blink
