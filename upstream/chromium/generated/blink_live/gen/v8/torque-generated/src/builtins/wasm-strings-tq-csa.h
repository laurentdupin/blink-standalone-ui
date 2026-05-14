#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_WASM_STRINGS_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_WASM_STRINGS_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/wasm-strings.tq?l=9&c=1
void Trap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, MessageTemplate p_error);

// https://crsrc.org/c/v8/src/builtins/wasm-strings.tq?l=79&c=1
TNode<JSAny> WebAssemblyStringIntoUtf8ArrayImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_stringArg, TNode<JSAny> p_arrayArg, TNode<JSAny> p_startArg, TNode<Smi> p_shared);

// https://crsrc.org/c/v8/src/builtins/wasm-strings.tq?l=129&c=1
TNode<JSAny> WebAssemblyStringToWtf16ArrayImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_stringArg, TNode<JSAny> p_arrayArg, TNode<JSAny> p_startArg, TNode<Smi> p_shared);

// https://crsrc.org/c/v8/src/builtins/wasm-strings.tq?l=62&c=10
TNode<BoolT> Is_String_String_OR_WasmNull_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Union<String, WasmNull>> p_o);

// https://crsrc.org/c/v8/src/builtins/wasm-strings.tq?l=216&c=12
TNode<Smi> SmiTag_char16_0(compiler::CodeAssemblerState* state_, TNode<Uint16T> p_value);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_WASM_STRINGS_TQ_CSA_H_
