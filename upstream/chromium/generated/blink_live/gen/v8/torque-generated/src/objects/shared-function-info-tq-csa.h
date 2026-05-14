#ifndef V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_SHARED_FUNCTION_INFO_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_SHARED_FUNCTION_INFO_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=7&c=1
TNode<PreparseData> Cast_PreparseData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=14&c=1
TNode<InterpreterData> Cast_InterpreterData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=63&c=1
TNode<SharedFunctionInfo> Cast_SharedFunctionInfo_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=131&c=1
TNode<SharedFunctionInfoWrapper> Cast_SharedFunctionInfoWrapper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=139&c=1
TNode<Uint16T> LoadSharedFunctionInfoFormalParameterCountWithoutReceiver_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_sfi);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=150&c=1
TNode<Uint16T> LoadSharedFunctionInfoFormalParameterCountWithReceiver_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_sfi);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=156&c=1
TNode<BoolT> IsSharedFunctionInfoDontAdaptArguments_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_sfi);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=162&c=1
TNode<UncompiledData> Cast_UncompiledData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=170&c=1
TNode<UncompiledDataWithoutPreparseData> Cast_UncompiledDataWithoutPreparseData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=173&c=1
TNode<UncompiledDataWithPreparseData> Cast_UncompiledDataWithPreparseData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=178&c=1
TNode<UncompiledDataWithoutPreparseDataWithJob> Cast_UncompiledDataWithoutPreparseDataWithJob_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=184&c=1
TNode<UncompiledDataWithPreparseDataAndJob> Cast_UncompiledDataWithPreparseDataAndJob_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=200&c=1
TNode<OnHeapBasicBlockProfilerData> Cast_OnHeapBasicBlockProfilerData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=10&c=3
TNode<Int32T> LoadPreparseDataDataLength_0(compiler::CodeAssemblerState* state_, TNode<PreparseData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=10&c=3
void StorePreparseDataDataLength_0(compiler::CodeAssemblerState* state_, TNode<PreparseData> p_o, TNode<Int32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=11&c=3
TNode<Int32T> LoadPreparseDataChildrenLength_0(compiler::CodeAssemblerState* state_, TNode<PreparseData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=11&c=3
void StorePreparseDataChildrenLength_0(compiler::CodeAssemblerState* state_, TNode<PreparseData> p_o, TNode<Int32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=16&c=3
TNode<MaybeObject> LoadInterpreterDataBytecodeArray_0(compiler::CodeAssemblerState* state_, TNode<InterpreterData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=16&c=3
void StoreInterpreterDataBytecodeArray_0(compiler::CodeAssemblerState* state_, TNode<InterpreterData> p_o, TNode<MaybeObject> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=17&c=3
TNode<MaybeObject> LoadInterpreterDataInterpreterTrampoline_0(compiler::CodeAssemblerState* state_, TNode<InterpreterData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=17&c=3
void StoreInterpreterDataInterpreterTrampoline_0(compiler::CodeAssemblerState* state_, TNode<InterpreterData> p_o, TNode<MaybeObject> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=76&c=3
TNode<TrustedPointerT> LoadSharedFunctionInfoTrustedFunctionData_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=76&c=3
void StoreSharedFunctionInfoTrustedFunctionData_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<TrustedPointerT> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=80&c=3
TNode<Object> LoadSharedFunctionInfoUntrustedFunctionData_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=80&c=3
void StoreSharedFunctionInfoUntrustedFunctionData_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Object> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=81&c=3
TNode<Union<ScopeInfo, Smi, String>> LoadSharedFunctionInfoNameOrScopeInfo_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=81&c=3
void StoreSharedFunctionInfoNameOrScopeInfo_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Union<ScopeInfo, Smi, String>> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=82&c=3
TNode<Union<FeedbackMetadata, ScopeInfo, TheHole>> LoadSharedFunctionInfoOuterScopeInfoOrFeedbackMetadata_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=82&c=3
void StoreSharedFunctionInfoOuterScopeInfoOrFeedbackMetadata_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Union<FeedbackMetadata, ScopeInfo, TheHole>> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=83&c=3
TNode<Union<Script, Undefined>> LoadSharedFunctionInfoScript_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=83&c=3
void StoreSharedFunctionInfoScript_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Union<Script, Undefined>> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=87&c=3
TNode<Uint16T> LoadSharedFunctionInfoLength_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=87&c=3
void StoreSharedFunctionInfoLength_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint16T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=103&c=3
TNode<Uint16T> LoadSharedFunctionInfoFormalParameterCount_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=103&c=3
void StoreSharedFunctionInfoFormalParameterCount_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint16T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=104&c=3
TNode<Uint16T> LoadSharedFunctionInfoFunctionTokenOffset_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=104&c=3
void StoreSharedFunctionInfoFunctionTokenOffset_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint16T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=107&c=3
TNode<Uint8T> LoadSharedFunctionInfoExpectedNofProperties_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=107&c=3
void StoreSharedFunctionInfoExpectedNofProperties_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint8T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=108&c=3
TNode<Uint8T> LoadSharedFunctionInfoFlags2_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=108&c=3
void StoreSharedFunctionInfoFlags2_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint8T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=109&c=3
TNode<Uint32T> LoadSharedFunctionInfoFlags_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=109&c=3
void StoreSharedFunctionInfoFlags_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=113&c=3
TNode<Int32T> LoadSharedFunctionInfoFunctionLiteralId_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=113&c=3
void StoreSharedFunctionInfoFunctionLiteralId_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Int32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=117&c=3
TNode<Int32T> LoadSharedFunctionInfoUniqueId_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=117&c=3
void StoreSharedFunctionInfoUniqueId_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Int32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=120&c=3
TNode<Uint16T> LoadSharedFunctionInfoAge_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=120&c=3
void StoreSharedFunctionInfoAge_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint16T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=124&c=3
TNode<Uint16T> LoadSharedFunctionInfoFeedbackSlot_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=124&c=3
void StoreSharedFunctionInfoFeedbackSlot_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfo> p_o, TNode<Uint16T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=133&c=3
TNode<SharedFunctionInfo> LoadSharedFunctionInfoWrapperSharedInfo_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfoWrapper> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=133&c=3
void StoreSharedFunctionInfoWrapperSharedInfo_0(compiler::CodeAssemblerState* state_, TNode<SharedFunctionInfoWrapper> p_o, TNode<SharedFunctionInfo> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=165&c=3
TNode<String> LoadUncompiledDataInferredName_0(compiler::CodeAssemblerState* state_, TNode<UncompiledData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=165&c=3
void StoreUncompiledDataInferredName_0(compiler::CodeAssemblerState* state_, TNode<UncompiledData> p_o, TNode<String> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=166&c=3
TNode<Int32T> LoadUncompiledDataStartPosition_0(compiler::CodeAssemblerState* state_, TNode<UncompiledData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=166&c=3
void StoreUncompiledDataStartPosition_0(compiler::CodeAssemblerState* state_, TNode<UncompiledData> p_o, TNode<Int32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=167&c=3
TNode<Int32T> LoadUncompiledDataEndPosition_0(compiler::CodeAssemblerState* state_, TNode<UncompiledData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=167&c=3
void StoreUncompiledDataEndPosition_0(compiler::CodeAssemblerState* state_, TNode<UncompiledData> p_o, TNode<Int32T> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=175&c=3
TNode<PreparseData> LoadUncompiledDataWithPreparseDataPreparseData_0(compiler::CodeAssemblerState* state_, TNode<UncompiledDataWithPreparseData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=175&c=3
void StoreUncompiledDataWithPreparseDataPreparseData_0(compiler::CodeAssemblerState* state_, TNode<UncompiledDataWithPreparseData> p_o, TNode<PreparseData> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=181&c=3
TNode<RawPtrT> LoadUncompiledDataWithoutPreparseDataWithJobJob_0(compiler::CodeAssemblerState* state_, TNode<UncompiledDataWithoutPreparseDataWithJob> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=181&c=3
void StoreUncompiledDataWithoutPreparseDataWithJobJob_0(compiler::CodeAssemblerState* state_, TNode<UncompiledDataWithoutPreparseDataWithJob> p_o, TNode<RawPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=187&c=3
TNode<RawPtrT> LoadUncompiledDataWithPreparseDataAndJobJob_0(compiler::CodeAssemblerState* state_, TNode<UncompiledDataWithPreparseDataAndJob> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=187&c=3
void StoreUncompiledDataWithPreparseDataAndJobJob_0(compiler::CodeAssemblerState* state_, TNode<UncompiledDataWithPreparseDataAndJob> p_o, TNode<RawPtrT> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=202&c=3
TNode<ByteArray> LoadOnHeapBasicBlockProfilerDataBlockIds_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=202&c=3
void StoreOnHeapBasicBlockProfilerDataBlockIds_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<ByteArray> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=203&c=3
TNode<ByteArray> LoadOnHeapBasicBlockProfilerDataCounts_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=203&c=3
void StoreOnHeapBasicBlockProfilerDataCounts_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<ByteArray> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=204&c=3
TNode<ByteArray> LoadOnHeapBasicBlockProfilerDataBranches_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=204&c=3
void StoreOnHeapBasicBlockProfilerDataBranches_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<ByteArray> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=205&c=3
TNode<String> LoadOnHeapBasicBlockProfilerDataName_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=205&c=3
void StoreOnHeapBasicBlockProfilerDataName_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<String> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=206&c=3
TNode<String> LoadOnHeapBasicBlockProfilerDataSchedule_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=206&c=3
void StoreOnHeapBasicBlockProfilerDataSchedule_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<String> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=207&c=3
TNode<String> LoadOnHeapBasicBlockProfilerDataCode_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=207&c=3
void StoreOnHeapBasicBlockProfilerDataCode_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<String> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=208&c=3
TNode<Smi> LoadOnHeapBasicBlockProfilerDataHash_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=208&c=3
void StoreOnHeapBasicBlockProfilerDataHash_0(compiler::CodeAssemblerState* state_, TNode<OnHeapBasicBlockProfilerData> p_o, TNode<Smi> p_v);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=7&c=1
TNode<PreparseData> DownCastForTorqueClass_PreparseData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=14&c=1
TNode<InterpreterData> DownCastForTorqueClass_InterpreterData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=63&c=1
TNode<SharedFunctionInfo> DownCastForTorqueClass_SharedFunctionInfo_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=131&c=1
TNode<SharedFunctionInfoWrapper> DownCastForTorqueClass_SharedFunctionInfoWrapper_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=162&c=1
TNode<UncompiledData> DownCastForTorqueClass_UncompiledData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=170&c=1
TNode<UncompiledDataWithoutPreparseData> DownCastForTorqueClass_UncompiledDataWithoutPreparseData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=173&c=1
TNode<UncompiledDataWithPreparseData> DownCastForTorqueClass_UncompiledDataWithPreparseData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=178&c=1
TNode<UncompiledDataWithoutPreparseDataWithJob> DownCastForTorqueClass_UncompiledDataWithoutPreparseDataWithJob_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=184&c=1
TNode<UncompiledDataWithPreparseDataAndJob> DownCastForTorqueClass_UncompiledDataWithPreparseDataAndJob_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/objects/shared-function-info.tq?l=200&c=1
TNode<OnHeapBasicBlockProfilerData> DownCastForTorqueClass_OnHeapBasicBlockProfilerData_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_OBJECTS_SHARED_FUNCTION_INFO_TQ_CSA_H_
