#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_JS_ITERATOR_HELPERS_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_JS_ITERATOR_HELPERS_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=7&c=1
TNode<Uint32T> FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedStart_0(compiler::CodeAssemblerState* state_, JSIteratorHelperState p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=7&c=1
TNode<Uint32T> FromConstexpr_JSIteratorHelperState_constexpr_kSuspendedYield_0(compiler::CodeAssemblerState* state_, JSIteratorHelperState p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=7&c=1
TNode<Uint32T> FromConstexpr_JSIteratorHelperState_constexpr_kExecuting_0(compiler::CodeAssemblerState* state_, JSIteratorHelperState p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=7&c=1
TNode<Uint32T> FromConstexpr_JSIteratorHelperState_constexpr_kCompleted_0(compiler::CodeAssemblerState* state_, JSIteratorHelperState p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=14&c=1
TNode<JSIteratorHelper> Cast_JSIteratorHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=20&c=1
TNode<JSIteratorHelperSimple> Cast_JSIteratorHelperSimple_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=26&c=1
TNode<JSIteratorMapHelper> Cast_JSIteratorMapHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=32&c=1
TNode<JSIteratorFilterHelper> Cast_JSIteratorFilterHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=38&c=1
TNode<JSIteratorTakeHelper> Cast_JSIteratorTakeHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=43&c=1
TNode<JSIteratorDropHelper> Cast_JSIteratorDropHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=48&c=1
TNode<JSIteratorFlatMapHelper> Cast_JSIteratorFlatMapHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=55&c=1
TNode<JSIteratorConcatHelper> Cast_JSIteratorConcatHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=61&c=1
TNode<Uint32T> FromConstexpr_JSIteratorZipHelperMode_constexpr_kShortest_0(compiler::CodeAssemblerState* state_, JSIteratorZipHelperMode p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=61&c=1
TNode<Uint32T> FromConstexpr_JSIteratorZipHelperMode_constexpr_kLongest_0(compiler::CodeAssemblerState* state_, JSIteratorZipHelperMode p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=61&c=1
TNode<Uint32T> FromConstexpr_JSIteratorZipHelperMode_constexpr_kStrict_0(compiler::CodeAssemblerState* state_, JSIteratorZipHelperMode p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=67&c=1
TNode<JSIteratorZipHelper> Cast_JSIteratorZipHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=75&c=1
TNode<JSIteratorZipKeyedHelper> Cast_JSIteratorZipKeyedHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=17&c=3
TNode<Smi> LoadJSIteratorHelperState_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=17&c=3
void StoreJSIteratorHelperState_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelper> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=23&c=3
TorqueStructIteratorRecord LoadJSIteratorHelperSimpleUnderlyingIterator_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelperSimple> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=23&c=3
void StoreJSIteratorHelperSimpleUnderlyingIterator_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorHelperSimple> p_o, TorqueStructIteratorRecord p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=28&c=3
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> LoadJSIteratorMapHelperMapper_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorMapHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=28&c=3
void StoreJSIteratorMapHelperMapper_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorMapHelper> p_o, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=29&c=3
TNode<Number> LoadJSIteratorMapHelperCounter_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorMapHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=29&c=3
void StoreJSIteratorMapHelperCounter_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorMapHelper> p_o, TNode<Number> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=34&c=3
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> LoadJSIteratorFilterHelperPredicate_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFilterHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=34&c=3
void StoreJSIteratorFilterHelperPredicate_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFilterHelper> p_o, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=35&c=3
TNode<Number> LoadJSIteratorFilterHelperCounter_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFilterHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=35&c=3
void StoreJSIteratorFilterHelperCounter_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFilterHelper> p_o, TNode<Number> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=40&c=3
TNode<Number> LoadJSIteratorTakeHelperRemaining_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorTakeHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=40&c=3
void StoreJSIteratorTakeHelperRemaining_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorTakeHelper> p_o, TNode<Number> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=45&c=3
TNode<Number> LoadJSIteratorDropHelperRemaining_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorDropHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=45&c=3
void StoreJSIteratorDropHelperRemaining_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorDropHelper> p_o, TNode<Number> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=50&c=3
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> LoadJSIteratorFlatMapHelperMapper_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFlatMapHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=50&c=3
void StoreJSIteratorFlatMapHelperMapper_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFlatMapHelper> p_o, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=51&c=3
TNode<Number> LoadJSIteratorFlatMapHelperCounter_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFlatMapHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=51&c=3
void StoreJSIteratorFlatMapHelperCounter_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFlatMapHelper> p_o, TNode<Number> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=52&c=3
TorqueStructIteratorRecord LoadJSIteratorFlatMapHelperInnerIterator_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFlatMapHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=52&c=3
void StoreJSIteratorFlatMapHelperInnerIterator_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorFlatMapHelper> p_o, TorqueStructIteratorRecord p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=57&c=3
TNode<FixedArray> LoadJSIteratorConcatHelperIterables_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorConcatHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=57&c=3
void StoreJSIteratorConcatHelperIterables_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorConcatHelper> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=58&c=3
TNode<Smi> LoadJSIteratorConcatHelperCurrent_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorConcatHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=58&c=3
void StoreJSIteratorConcatHelperCurrent_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorConcatHelper> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=69&c=3
TNode<FixedArray> LoadJSIteratorZipHelperUnderlyingIterators_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=69&c=3
void StoreJSIteratorZipHelperUnderlyingIterators_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=70&c=3
TNode<Smi> LoadJSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=70&c=3
void StoreJSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=71&c=3
TNode<Smi> LoadJSIteratorZipHelperActiveCount_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=71&c=3
void StoreJSIteratorZipHelperActiveCount_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=72&c=3
TNode<FixedArray> LoadJSIteratorZipHelperPadding_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=72&c=3
void StoreJSIteratorZipHelperPadding_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipHelper> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=77&c=3
TNode<FixedArray> LoadJSIteratorZipKeyedHelperKeys_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipKeyedHelper> p_o);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=77&c=3
void StoreJSIteratorZipKeyedHelperKeys_0(compiler::CodeAssemblerState* state_, TNode<JSIteratorZipKeyedHelper> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=14&c=1
TNode<JSIteratorHelper> DownCastForTorqueClass_JSIteratorHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=20&c=1
TNode<JSIteratorHelperSimple> DownCastForTorqueClass_JSIteratorHelperSimple_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=26&c=1
TNode<JSIteratorMapHelper> DownCastForTorqueClass_JSIteratorMapHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=32&c=1
TNode<JSIteratorFilterHelper> DownCastForTorqueClass_JSIteratorFilterHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=38&c=1
TNode<JSIteratorTakeHelper> DownCastForTorqueClass_JSIteratorTakeHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=43&c=1
TNode<JSIteratorDropHelper> DownCastForTorqueClass_JSIteratorDropHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=48&c=1
TNode<JSIteratorFlatMapHelper> DownCastForTorqueClass_JSIteratorFlatMapHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=55&c=1
TNode<JSIteratorConcatHelper> DownCastForTorqueClass_JSIteratorConcatHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=67&c=1
TNode<JSIteratorZipHelper> DownCastForTorqueClass_JSIteratorZipHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/js-iterator-helpers.tq?l=75&c=1
TNode<JSIteratorZipKeyedHelper> DownCastForTorqueClass_JSIteratorZipKeyedHelper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_JS_ITERATOR_HELPERS_TQ_CSA_H_
