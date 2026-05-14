#ifndef V8_GEN_TORQUE_GENERATED_THIRD_PARTY_V8_BUILTINS_ARRAY_SORT_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_THIRD_PARTY_V8_BUILTINS_ARRAY_SORT_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=24&c=1
TNode<SortState> Cast_SortState_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=80&c=1
TNode<Number> Compare_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<JSAny> p_x, TNode<JSAny> p_y);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=90&c=1
void CheckAccessor_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, compiler::CodeAssemblerLabel* label_Bailout);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=116&c=1
void ResetToGenericAccessor_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_sortState, bool p__isToSorted);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=126&c=1
TNode<IntPtrT> CalculateWorkArrayLength_0(compiler::CodeAssemblerState* state_, TNode<JSReceiver> p_receiver, TNode<Number> p_initialReceiverLength);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=158&c=1
TNode<SortState> NewSortState_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_receiver, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> p_comparefn, TNode<Number> p_initialReceiverLength, bool p_isToSorted);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=198&c=1
TNode<Smi> kSuccess_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=205&c=1
int31_t kMaxMergePending_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=209&c=1
int31_t kMinGallopWins_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=219&c=1
TNode<Smi> kSortStateTempSize_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=408&c=1
TNode<Smi> GetPendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_sortState);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=414&c=1
TNode<Smi> GetPendingRunBase_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=418&c=1
void SetPendingRunBase_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run, TNode<Smi> p_value);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=423&c=1
TNode<Smi> GetPendingRunLength_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=428&c=1
void SetPendingRunLength_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingRuns, TNode<Smi> p_run, TNode<Smi> p_value);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=433&c=1
TNode<Smi> GetPendingPower_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<FixedArray> p_pendingPowers, TNode<Smi> p_run);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=438&c=1
void SetPendingPower_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_pendingPowers, TNode<Smi> p_run, TNode<Smi> p_value);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=446&c=1
TNode<Smi> NodePower32_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Smi> p_s1, TNode<Smi> p_n1, TNode<Smi> p_n2, TNode<Smi> p_n);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=474&c=1
TNode<Smi> NodePower_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Smi> p_s1, TNode<Smi> p_n1, TNode<Smi> p_n2, TNode<Smi> p_n);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=505&c=1
void PushRun_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_base, TNode<Smi> p_length);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=521&c=1
TNode<FixedArray> GetTempArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_requestedSize);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=584&c=1
void BinaryInsertionSort_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_low, TNode<Smi> p_startArg, TNode<Smi> p_high);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=650&c=1
TNode<Smi> CountAndMakeRun_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_lowArg, TNode<Smi> p_high);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=693&c=1
void ReverseRange_0(compiler::CodeAssemblerState* state_, TNode<FixedArray> p_array, TNode<Smi> p_from, TNode<Smi> p_to);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=980&c=1
void MergeLow_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_baseA, TNode<Smi> p_lengthAArg, TNode<Smi> p_baseB, TNode<Smi> p_lengthBArg);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1111&c=1
void MergeHigh_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_baseA, TNode<Smi> p_lengthAArg, TNode<Smi> p_baseB, TNode<Smi> p_lengthBArg);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1260&c=1
void ArrayPowerSortImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_length);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1352&c=1
TNode<Smi> CompactReceiverElementsIntoWorkArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, bool p_isToSorted);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=1456&c=1
void CopyWorkArrayToReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<SortState> p_sortState, TNode<Smi> p_numberOfNonUndefined);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=27&c=3
TNode<JSReceiver> LoadSortStateReceiver_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=27&c=3
void StoreSortStateReceiver_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<JSReceiver> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=32&c=3
TNode<Map> LoadSortStateInitialReceiverMap_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=32&c=3
void StoreSortStateInitialReceiverMap_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Map> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=33&c=3
TNode<Number> LoadSortStateInitialReceiverLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=33&c=3
void StoreSortStateInitialReceiverLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Number> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=36&c=3
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> LoadSortStateUserCmpFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=36&c=3
void StoreSortStateUserCmpFn_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction, Undefined>> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=38&c=3
TNode<Boolean> LoadSortStateIsResetToGeneric_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=38&c=3
void StoreSortStateIsResetToGeneric_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Boolean> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=43&c=3
TNode<Smi> LoadSortStateMinGallop_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=43&c=3
void StoreSortStateMinGallop_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=55&c=3
TNode<Smi> LoadSortStatePendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=55&c=3
void StoreSortStatePendingRunsSize_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=56&c=3
TNode<FixedArray> LoadSortStatePendingRuns_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=56&c=3
void StoreSortStatePendingRuns_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=57&c=3
TNode<FixedArray> LoadSortStatePendingPowers_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=57&c=3
void StoreSortStatePendingPowers_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=62&c=3
TNode<FixedArray> LoadSortStateWorkArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=62&c=3
void StoreSortStateWorkArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=65&c=3
TNode<FixedArray> LoadSortStateTempArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=65&c=3
void StoreSortStateTempArray_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<FixedArray> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=68&c=3
TNode<Smi> LoadSortStateSortLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=68&c=3
void StoreSortStateSortLength_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=72&c=3
TNode<Smi> LoadSortStateNumberOfUndefined_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=72&c=3
void StoreSortStateNumberOfUndefined_0(compiler::CodeAssemblerState* state_, TNode<SortState> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=24&c=1
TNode<SortState> DownCastForTorqueClass_SortState_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=164&c=7
TNode<BoolT> Is_FastJSArray_JSReceiver_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=165&c=15
TNode<JSArray> UnsafeCast_FastJSArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/third_party/v8/builtins/array-sort.tq?l=243&c=18
TNode<JSObject> UnsafeCast_JSObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_THIRD_PARTY_V8_BUILTINS_ARRAY_SORT_TQ_CSA_H_
