#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_ARRAY_SLICE_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_ARRAY_SLICE_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/array-slice.tq?l=10&c=1
TNode<JSArray> HandleSimpleArgumentsSlice_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<Union<JSArgumentsObject>> p_args, TNode<Smi> p_start, TNode<Smi> p_count, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/builtins/array-slice.tq?l=39&c=1
TNode<JSArray> HandleFastAliasedSloppyArgumentsSlice_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<Union<JSArgumentsObject>> p_args, TNode<Smi> p_start, TNode<Smi> p_count, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/builtins/array-slice.tq?l=99&c=1
TNode<JSArray> HandleFastSlice_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<JSAny> p_o, TNode<Number> p_startNumber, TNode<Number> p_countNumber, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/src/builtins/array-slice.tq?l=77&c=24
TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> UnsafeCast_Smi_OR_JSReceiver_OR_Undefined_OR_Null_OR_Boolean_OR_Symbol_OR_String_OR_BigInt_OR_HeapNumber_OR_TheHole_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/array-slice.tq?l=119&c=7
TNode<JSArgumentsObject> Cast_JSStrictArgumentsObject_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/array-slice.tq?l=122&c=7
TNode<JSArgumentsObject> Cast_JSSloppyArgumentsObject_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_ARRAY_SLICE_TQ_CSA_H_
