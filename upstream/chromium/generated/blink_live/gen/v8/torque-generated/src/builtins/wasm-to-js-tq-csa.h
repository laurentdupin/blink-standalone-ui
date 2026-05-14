#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_WASM_TO_JS_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_WASM_TO_JS_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=36&c=1
void HandleF32Returns_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TorqueStructLocationAllocator_0 p_locationAllocator, TorqueStructReference_intptr_0 p_toRef, TNode<JSAny> p_retVal);

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=58&c=1
TorqueStructWasmToJSResult WasmToJSWrapper_0(compiler::CodeAssemblerState* state_, TNode<WasmImportData> p_data);

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=61&c=10
TNode<BoolT> Is_WasmImportData_WasmImportData_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<WasmImportData> p_o);

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=66&c=4
TorqueStructReference_RawPtr_0 GetRefAt_RawPtr_RawPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset);

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=86&c=30
TorqueStructReference_RawPtr_uint32_0 NewOffHeapReference_RawPtr_uint32_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_ptr);

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=194&c=4
TorqueStructReference_intptr_0 GetRefAt_intptr_RawPtr_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset);

// https://crsrc.org/c/v8/src/builtins/wasm-to-js.tq?l=313&c=15
TorqueStructReference_float64_0 GetRefAt_float64_RawPtr_float64_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_base, TNode<IntPtrT> p_offset);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_WASM_TO_JS_TQ_CSA_H_
