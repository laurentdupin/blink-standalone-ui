#ifndef STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_IME_TYPES_MOJOM_BLINK_FORWARD_H_
#define STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_IME_TYPES_MOJOM_BLINK_FORWARD_H_

namespace ui::mojom {

enum class TextInputMode {
  kDefault,
  kNone,
  kText,
  kTel,
  kUrl,
  kEmail,
  kNumeric,
  kDecimal,
  kSearch,
};

enum class TextInputAction {
  kDefault,
  kEnter,
  kDone,
  kGo,
  kNext,
  kPrevious,
  kSearch,
  kSend,
};

enum class TextInputType {
  NONE,
  TEXT,
  PASSWORD,
  SEARCH,
  EMAIL,
  NUMBER,
  TELEPHONE,
  URL,
  DATE,
  DATE_TIME,
  DATE_TIME_LOCAL,
  MONTH,
  TIME,
  WEEK,
  TEXT_AREA,
  CONTENT_EDITABLE,
  DATE_TIME_FIELD,
  TYPE_NULL,
  MAX = TYPE_NULL,
};

enum class ImeTextSpanType {
  kComposition,
  kSuggestion,
  kMisspellingSuggestion,
  kAutocorrect,
  kGrammarSuggestion,
};

enum class ImeTextSpanThickness {
  kNone,
  kThin,
  kThick,
};

enum class ImeTextSpanUnderlineStyle {
  kNone,
  kSolid,
  kDot,
  kDash,
  kSquiggle,
};

}  // namespace ui::mojom

#endif  // STANDALONE_RENDERER_STUBS_UI_BASE_IME_MOJOM_IME_TYPES_MOJOM_BLINK_FORWARD_H_
