#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_ITERATOR_HELPERS_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_ITERATOR_HELPERS_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=9&c=1
TNode<BoolT> IsIteratorHelperExhausted_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=14&c=1
void MarkIteratorHelperAsExhausted_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=19&c=1
TNode<BoolT> IsIteratorHelperExecuting_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=27&c=1
void ThrowIfIteratorHelperExecuting_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=34&c=1
void MarkIteratorHelperAsExecuting_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=40&c=1
TNode<BoolT> IteratorHelperIsSuspendedStart_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=45&c=1
void MarkIteratorHelperAsFinishedExecuting_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_helper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=52&c=1
TorqueStructIteratorRecord GetIteratorDirect_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_obj);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=210&c=1
TNode<JSIteratorMapHelper> NewJSIteratorMapHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_mapper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=316&c=1
TNode<JSIteratorFilterHelper> NewJSIteratorFilterHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_predicate);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=430&c=1
TNode<JSIteratorTakeHelper> NewJSIteratorTakeHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Number> p_limit);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=551&c=1
TNode<JSIteratorDropHelper> NewJSIteratorDropHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Number> p_limit);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=672&c=1
const char* kFlatMapMethodName_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=674&c=1
TNode<JSIteratorFlatMapHelper> NewJSIteratorFlatMapHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TorqueStructIteratorRecord p_underlying, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_mapper);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1241&c=1
const char* kConcatMethodName_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1243&c=1
TNode<JSIteratorConcatHelper> NewJSIteratorConcatHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterables);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1459&c=1
void IteratorZipCloseAll_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterators, bool p_propagate);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1494&c=1
TNode<JSIteratorZipHelper> NewJSIteratorZipHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterators, TNode<FixedArray> p_padding, TNode<Uint32T> p_zipMode);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1686&c=1
TNode<FixedArray> IteratorZipHelperNextCommon_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSIteratorZipHelper> p_helper, const char* p_methodName, compiler::CodeAssemblerLabel* label_Done, compiler::CodeAssemblerLabel* label_DoneWithException, compiler::TypedCodeAssemblerVariable<JSAny>* label_DoneWithException_parameter_0, compiler::TypedCodeAssemblerVariable<Union<JSMessageObject, TheHole>>* label_DoneWithException_parameter_1);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1865&c=1
TNode<JSIteratorZipKeyedHelper> NewJSIteratorZipKeyedHelper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_iterators, TNode<FixedArray> p_padding, TNode<Uint32T> p_zipMode, TNode<FixedArray> p_keys);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=11&c=7
TNode<Smi> SmiTag_JSIteratorHelperState_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_value);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=72&c=18
TNode<JSIteratorHelper> Cast_JSIteratorHelper_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1272&c=10
TNode<BoolT> Is_JSReceiver_JSAny_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1505&c=11
TNode<Smi> SmiTag_JSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_value);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1615&c=40
TorqueStructConstantIterator_Undefined_0 ConstantIterator_Undefined_0(compiler::CodeAssemblerState* state_, TNode<Undefined> p_value);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1615&c=15
TNode<FixedArray> NewFixedArray_ConstantIterator_Undefined_0(compiler::CodeAssemblerState* state_, TNode<IntPtrT> p_length, TorqueStructConstantIterator_Undefined_0 p_it);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1698&c=16
TNode<Uint32T> SmiUntag_JSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_value);

// https://crsrc.org/c/v8/src/builtins/iterator-helpers.tq?l=1963&c=13
TNode<PropertyDescriptorObject> Cast_PropertyDescriptorObject_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_ITERATOR_HELPERS_TQ_CSA_H_
