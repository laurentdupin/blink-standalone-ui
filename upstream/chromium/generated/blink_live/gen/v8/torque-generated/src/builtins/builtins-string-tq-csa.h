#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_BUILTINS_STRING_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_BUILTINS_STRING_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=15&c=1
TNode<String> ToStringImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o);

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=69&c=1
TNode<String> ToString_Inline_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o);

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=127&c=1
void GenerateStringAt_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_receiver, TNode<JSAny> p_position, const char* p_methodName, compiler::CodeAssemblerLabel* label_IfInBounds, compiler::TypedCodeAssemblerVariable<String>* label_IfInBounds_parameter_0, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfInBounds_parameter_1, compiler::TypedCodeAssemblerVariable<UintPtrT>* label_IfInBounds_parameter_2, compiler::CodeAssemblerLabel* label_IfOutOfBounds);

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=60&c=5
TNode<Symbol> Cast_Symbol_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=217&c=26
TNode<IntPtrT> Convert_intptr_intptr_0(compiler::CodeAssemblerState* state_, TNode<IntPtrT> p_i);

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=276&c=22
TNode<Map> UnsafeCast_Map_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/builtins-string.tq?l=279&c=15
TNode<String> UnsafeCast_String_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_BUILTINS_STRING_TQ_CSA_H_
