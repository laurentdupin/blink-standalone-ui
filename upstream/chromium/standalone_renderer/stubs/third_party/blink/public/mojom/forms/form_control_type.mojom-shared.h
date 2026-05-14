#ifndef STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FORMS_FORM_CONTROL_TYPE_MOJOM_SHARED_H_
#define STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FORMS_FORM_CONTROL_TYPE_MOJOM_SHARED_H_

namespace blink::mojom {

enum class FormControlType {
  kButtonButton,
  kButtonSubmit,
  kButtonReset,
  kButtonPopover,
  kFieldset,
  kInputButton,
  kInputCheckbox,
  kInputColor,
  kInputDate,
  kInputDatetimeLocal,
  kInputEmail,
  kInputFile,
  kInputHidden,
  kInputImage,
  kInputMonth,
  kInputNumber,
  kInputPassword,
  kInputRadio,
  kInputRange,
  kInputReset,
  kInputSearch,
  kInputSubmit,
  kInputTelephone,
  kInputText,
  kInputTime,
  kInputUrl,
  kInputWeek,
  kOutput,
  kSelectOne,
  kSelectMultiple,
  kTextArea,
  kMinValue = kButtonButton,
  kMaxValue = kTextArea,
};

}  // namespace blink::mojom

#endif  // STANDALONE_RENDERER_STUBS_THIRD_PARTY_BLINK_PUBLIC_MOJOM_FORMS_FORM_CONTROL_TYPE_MOJOM_SHARED_H_
