#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_INTL_OBJECTS_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_INTL_OBJECTS_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=13&c=1
TNode<Uint8T> IntlAsciiCollationWeightL1_0(compiler::CodeAssemblerState* state_, TNode<Uint8T> p_c, compiler::CodeAssemblerLabel* label__Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=17&c=1
TNode<Uint8T> IntlAsciiCollationWeightL1_1(compiler::CodeAssemblerState* state_, TNode<Uint16T> p_c, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=22&c=1
TNode<Uint8T> IntlAsciiCollationWeightL3_0(compiler::CodeAssemblerState* state_, TNode<Uint8T> p_c, compiler::CodeAssemblerLabel* label__Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=26&c=1
TNode<Uint8T> IntlAsciiCollationWeightL3_1(compiler::CodeAssemblerState* state_, TNode<Uint16T> p_c, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=32&c=1
void CheckNextIs1Byte_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_char8_ConstReference_char8_0 p__slice, TNode<IntPtrT> p__index, compiler::CodeAssemblerLabel* label__Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=36&c=1
void CheckNextIs1Byte_1(compiler::CodeAssemblerState* state_, TorqueStructSlice_char16_ConstReference_char16_0 p_slice, TNode<IntPtrT> p_index, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=18&c=7
TNode<Uint32T> Convert_uint32_char16_0(compiler::CodeAssemblerState* state_, TNode<Uint16T> p_i);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=145&c=20
TNode<Number> LocaleCompareFastPath_char8_char8_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_char8_ConstReference_char8_0 p_left, TorqueStructSlice_char8_ConstReference_char8_0 p_right, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=164&c=14
TNode<Number> LocaleCompareFastPath_char8_char16_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_char8_ConstReference_char8_0 p_left, TorqueStructSlice_char16_ConstReference_char16_0 p_right, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=171&c=14
TNode<Number> LocaleCompareFastPath_char16_char8_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_char16_ConstReference_char16_0 p_left, TorqueStructSlice_char8_ConstReference_char8_0 p_right, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=173&c=14
TNode<Number> LocaleCompareFastPath_char16_char16_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_char16_ConstReference_char16_0 p_left, TorqueStructSlice_char16_ConstReference_char16_0 p_right, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/objects/intl-objects.tq?l=63&c=9
TNode<Uint32T> Convert_uint32_char8_0(compiler::CodeAssemblerState* state_, TNode<Uint8T> p_i);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_INTL_OBJECTS_TQ_CSA_H_
