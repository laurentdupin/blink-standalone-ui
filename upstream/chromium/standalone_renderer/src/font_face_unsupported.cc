#include "third_party/blink/renderer/core/css/font_face.h"

#include "third_party/blink/renderer/core/css/css_font_face_src_value.h"
#include "third_party/blink/renderer/core/css/css_property_value_set.h"
#include "third_party/blink/renderer/core/css/css_value_list.h"
#include "third_party/blink/renderer/core/css/style_rule.h"
#include "third_party/blink/renderer/core/dom/document.h"
#include "third_party/blink/renderer/core/execution_context/execution_context.h"

namespace blink {

FontFace* FontFace::Create(
    Document* document,
    const CascadeLayered<const StyleRuleFontFace>& layered_font_face_rule,
    bool) {
  if (!document || !document->GetExecutionContext() ||
      !layered_font_face_rule.value) {
    return nullptr;
  }

  const CSSValue* src = layered_font_face_rule.value->Properties()
                            .GetPropertyCSSValue(AtRuleDescriptorID::Src);
  const auto* src_list = DynamicTo<CSSValueList>(src);
  if (!src_list) {
    return nullptr;
  }

  for (wtf_size_t i = 0; i < src_list->length(); ++i) {
    const auto* font_src = DynamicTo<CSSFontFaceSrcValue>(&src_list->Item(i));
    if (!font_src || font_src->IsLocal() || !font_src->IsSupportedFormat()) {
      continue;
    }
    font_src->Fetch(document->GetExecutionContext(), nullptr);
  }

  // CSS @font-face provider routing is active, but downloadable font decoding
  // and live CSSFontFace rendering remain unsupported in this no-script build.
  return nullptr;
}

}  // namespace blink
