#ifndef V8_GEN_TORQUE_GENERATED_TEST_TORQUE_TEST_TORQUE_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_TEST_TORQUE_TEST_TORQUE_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=12&c=1
TNode<BoolT> ElementsKindTestHelper1_0(compiler::CodeAssemblerState* state_, ElementsKind p_kind);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=22&c=1
bool ElementsKindTestHelper2_0(compiler::CodeAssemblerState* state_, ElementsKind p_kind);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=27&c=1
void LabelTestHelper1_0(compiler::CodeAssemblerState* state_, compiler::CodeAssemblerLabel* label_Label1);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=32&c=1
void LabelTestHelper2_0(compiler::CodeAssemblerState* state_, compiler::CodeAssemblerLabel* label_Label2, compiler::TypedCodeAssemblerVariable<Smi>* label_Label2_parameter_0);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=37&c=1
void LabelTestHelper3_0(compiler::CodeAssemblerState* state_, compiler::CodeAssemblerLabel* label_Label3, compiler::TypedCodeAssemblerVariable<Oddball>* label_Label3_parameter_0, compiler::TypedCodeAssemblerVariable<Smi>* label_Label3_parameter_1);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=42&c=1
void TestConstexpr1_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=49&c=1
void TestConstexprIf_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=56&c=1
void TestConstexprReturn_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=71&c=1
TNode<Boolean> TestGotoLabel_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=80&c=1
TNode<Boolean> TestGotoLabelWithOneParameter_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=90&c=1
TNode<Boolean> TestGotoLabelWithTwoParameters_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=109&c=1
void TestBuiltinSpecialization_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=117&c=1
void LabelTestHelper4_0(compiler::CodeAssemblerState* state_, bool p_flag, compiler::CodeAssemblerLabel* label_Label4, compiler::CodeAssemblerLabel* label_Label5);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=126&c=1
TNode<BoolT> CallLabelTestHelper4_0(compiler::CodeAssemblerState* state_, bool p_flag);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=136&c=1
TNode<Boolean> TestPartiallyUnusedLabel_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=152&c=1
TNode<Object> GenericMacroTest_Object_0(compiler::CodeAssemblerState* state_, TNode<Object> p_param2);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=161&c=1
TNode<Object> GenericMacroTestWithLabels_Object_0(compiler::CodeAssemblerState* state_, TNode<Object> p_param2, compiler::CodeAssemblerLabel* label_Y);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=166&c=1
void TestMacroSpecialization_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=192&c=1
TNode<Boolean> TestFunctionPointers_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=201&c=1
TNode<Boolean> TestVariableRedeclaration_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=208&c=1
TNode<Smi> TestTernaryOperator_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_x);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=214&c=1
void TestFunctionPointerToGeneric_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=226&c=1
TNode<BuiltinPtr> TestTypeAlias_0(compiler::CodeAssemblerState* state_, TNode<BuiltinPtr> p_x);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=231&c=1
TNode<Boolean> TestUnsafeCast_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Number> p_n);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=242&c=1
void TestHexLiteral_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=248&c=1
void TestLargeIntegerLiterals_0(compiler::CodeAssemblerState* state_, TNode<Context> p_c);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=254&c=1
void TestMultilineAssert_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=262&c=1
void TestNewlineInString_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=267&c=1
int31_t kConstexprConst_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=268&c=1
TNode<IntPtrT> kIntptrConst_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=269&c=1
TNode<Smi> kSmiConst_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=271&c=1
void TestModuleConstBindings_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=278&c=1
void TestLocalConstBindings_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=304&c=1
TNode<Smi> TestStruct1_0(compiler::CodeAssemblerState* state_, TorqueStructTestStructA_0 p_i);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=309&c=1
TorqueStructTestStructA_0 TestStruct2_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=318&c=1
TorqueStructTestStructA_0 TestStruct3_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=344&c=1
TorqueStructTestStructC_0 TestStruct4_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=353&c=1
void CallTestStructInLabel_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=362&c=1
void TestForLoop_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=461&c=1
void TestSubtyping_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_x);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=478&c=1
TNode<Uint32T> TypeswitchExample_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Union<FixedArray, HeapNumber, Smi>> p_x);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=507&c=1
void TestTypeswitch_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=515&c=1
void TestTypeswitchAsanLsanFailure_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_obj);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=537&c=1
void TestGenericOverload_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=545&c=1
void TestEquality_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=555&c=1
TNode<BoolT> TestOrAnd_0(compiler::CodeAssemblerState* state_, TNode<BoolT> p_x, TNode<BoolT> p_y, TNode<BoolT> p_z);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=560&c=1
TNode<BoolT> TestAndOr_0(compiler::CodeAssemblerState* state_, TNode<BoolT> p_x, TNode<BoolT> p_y, TNode<BoolT> p_z);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=565&c=1
void TestLogicalOperators_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=585&c=1
TNode<Smi> TestCall_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_i, compiler::CodeAssemblerLabel* label_A);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=591&c=1
void TestOtherwiseWithCode1_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=603&c=1
void TestOtherwiseWithCode2_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=613&c=1
void TestOtherwiseWithCode3_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=622&c=1
void TestForwardLabel_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=633&c=1
void TestQualifiedAccess_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=639&c=1
TNode<Smi> TestCatch1_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=650&c=1
void TestCatch2Wrapper_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=655&c=1
TNode<Smi> TestCatch2_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=666&c=1
void TestCatch3WrapperWithLabel_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, compiler::CodeAssemblerLabel* label__Abort);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=672&c=1
TNode<Smi> TestCatch3_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=689&c=1
void TestIterator_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o, TNode<Map> p_map);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=708&c=1
void TestFrame1_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=724&c=1
void TestNew_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=748&c=1
void TestStructConstructor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=774&c=1
void TestConstInStructs_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=785&c=1
void TestParentFrameArguments_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=801&c=1
TNode<Object> TestNewFixedArrayFromSpread_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=812&c=1
void TestSlices_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=845&c=1
TNode<Undefined> TestSliceEnumeration_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=874&c=1
void TestStaticAssert_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=893&c=1
TNode<Smi> TestRedundantArrayElementCheck_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=908&c=1
TNode<Smi> TestRedundantSmiCheck_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=927&c=1
TNode<IntPtrT> TestGenericStruct1_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=948&c=1
TorqueStructTestTuple_TestTuple_intptr_Smi_TestTuple_Smi_intptr_0 TestGenericStruct2_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=967&c=1
void TestBitFieldLoad_0(compiler::CodeAssemblerState* state_, TNode<Uint8T> p_val, TNode<BoolT> p_expectedA, TNode<Uint16T> p_expectedB, TNode<Uint32T> p_expectedC, TNode<BoolT> p_expectedD);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=977&c=1
void TestBitFieldStore_0(compiler::CodeAssemblerState* state_, TNode<Uint8T> p_val);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=996&c=1
void TestBitFieldInit_0(compiler::CodeAssemblerState* state_, TNode<BoolT> p_a, TNode<Uint16T> p_b, TNode<Uint32T> p_c, TNode<BoolT> p_d);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1014&c=1
void TestBitFieldUintptrOps_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_val2, TNode<UintPtrT> p_val3);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1055&c=1
void TestBitFieldMultipleFlags_0(compiler::CodeAssemblerState* state_, TNode<BoolT> p_a, TNode<Int32T> p_b, TNode<BoolT> p_c);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1079&c=1
void TestWord8Phi_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1092&c=1
void TestOffHeapSlice_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_ptr, TNode<IntPtrT> p_length);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1115&c=1
void TestCallMultiReturnBuiltin_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1122&c=1
TNode<Smi> TestRunLazyTwice_0(compiler::CodeAssemblerState* state_, std::function<TNode<Smi>()> p_lazySmi);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1129&c=1
TNode<Smi> GetLazySmi_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1133&c=1
TNode<Smi> AddTwoSmiValues_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_a, TNode<Smi> p_b);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1137&c=1
TNode<Smi> AddSmiAndConstexprValues_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_a, int31_t p_b);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1141&c=1
void TestCreateLazyNodeFromTorque_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1165&c=1
void TestCellAccessors_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Cell> p_cell);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=170&c=11
TNode<Object> GenericMacroTest_Smi_0(compiler::CodeAssemblerState* state_, TNode<Smi> p__param);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=175&c=12
TNode<Object> GenericMacroTestWithLabels_Smi_0(compiler::CodeAssemblerState* state_, TNode<Smi> p__param, compiler::CodeAssemblerLabel* label__X);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=481&c=15
TNode<Union<FixedArray, HeapNumber, Smi>> IncrementIfSmi_NumberOrFixedArray_0(compiler::CodeAssemblerState* state_, TNode<Union<FixedArray, HeapNumber, Smi>> p_x);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=482&c=5
TNode<FixedArray> Cast_FixedArray_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=541&c=9
TNode<Smi> ExampleGenericOverload_Smi_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_o);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=542&c=25
TNode<Object> ExampleGenericOverload_Object_0(compiler::CodeAssemblerState* state_, TNode<Object> p_o);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=636&c=10
TNode<BoolT> Is_JSArray_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Smi> p_o);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=804&c=10
void InitializeFieldsFromIterator_Object_TestIterator_0(compiler::CodeAssemblerState* state_, TorqueStructSlice_Object_MutableReference_Object_0 p_target, TorqueStructTestIterator_0 p_originIterator);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=952&c=24
TorqueStructTestTuple_Smi_intptr_0 TupleSwap_intptr_Smi_0(compiler::CodeAssemblerState* state_, TorqueStructTestTuple_intptr_Smi_0 p_tuple);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1094&c=47
TNode<String> Convert_String_constexpr_string_0(compiler::CodeAssemblerState* state_, const char* p_i);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1094&c=18
TNode<SeqOneByteString> UnsafeCast_SeqOneByteString_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/test/torque/test-torque.tq?l=1096&c=10
TorqueStructReference_char8_0 NewOffHeapReference_char8_0(compiler::CodeAssemblerState* state_, TNode<RawPtrT> p_ptr);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_TEST_TORQUE_TEST_TORQUE_TQ_CSA_H_
