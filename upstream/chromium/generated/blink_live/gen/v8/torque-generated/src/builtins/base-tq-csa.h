#ifndef V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_BASE_TQ_CSA_H_
#define V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_BASE_TQ_CSA_H_

#include "src/builtins/torque-csa-header-includes.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/base.tq?l=81&c=1
TNode<HeapObject> MaybeObjectToStrong_0(compiler::CodeAssemblerState* state_, TNode<Union<HeapObject, Smi, Weak<HeapObject>>> p_maybeObject, compiler::CodeAssemblerLabel* label_IfCleared);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=212&c=1
TorqueStructfloat64_or_undefined_or_hole_0 kDoubleHole_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=215&c=1
TorqueStructfloat64_or_undefined_or_hole_0 kDoubleUndefined_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=266&c=1
TNode<OrderedHashMap> Cast_OrderedHashMap_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=267&c=1
TNode<OrderedHashSet> Cast_OrderedHashSet_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=268&c=1
TNode<OrderedNameDictionary> Cast_OrderedNameDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=269&c=1
TNode<NameToIndexHashTable> Cast_NameToIndexHashTable_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=270&c=1
TNode<RegisteredSymbolTable> Cast_RegisteredSymbolTable_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=271&c=1
TNode<NameDictionary> Cast_NameDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=272&c=1
TNode<GlobalDictionary> Cast_GlobalDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=273&c=1
TNode<SimpleNameDictionary> Cast_SimpleNameDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=274&c=1
TNode<SimpleNumberDictionary> Cast_SimpleNumberDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=275&c=1
TNode<EphemeronHashTable> Cast_EphemeronHashTable_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=278&c=1
TNode<NumberDictionary> Cast_NumberDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=279&c=1
TNode<DoubleStringCache> Cast_DoubleStringCache_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=293&c=1
TNode<InstructionStream> Cast_InstructionStream_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=299&c=1
TNode<TransitionArray> Cast_TransitionArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=331&c=1
TNode<Int32T> FromConstexpr_CallFeedbackContent_constexpr_kTarget_0(compiler::CodeAssemblerState* state_, CallFeedbackContent p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=331&c=1
TNode<Int32T> FromConstexpr_CallFeedbackContent_constexpr_kReceiver_0(compiler::CodeAssemblerState* state_, CallFeedbackContent p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=336&c=1
TNode<Int32T> FromConstexpr_PromiseState_constexpr_kPending_0(compiler::CodeAssemblerState* state_, Promise::PromiseState p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=336&c=1
TNode<Int32T> FromConstexpr_PromiseState_constexpr_kFulfilled_0(compiler::CodeAssemblerState* state_, Promise::PromiseState p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=336&c=1
TNode<Int32T> FromConstexpr_PromiseState_constexpr_kRejected_0(compiler::CodeAssemblerState* state_, Promise::PromiseState p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_NO_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_PACKED_SMI_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_HOLEY_SMI_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_PACKED_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_HOLEY_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_PACKED_DOUBLE_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_HOLEY_DOUBLE_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_LAST_ANY_NONEXTENSIBLE_ELEMENTS_KIND_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_DICTIONARY_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_UINT8_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_INT8_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_UINT16_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_INT16_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_UINT32_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_INT32_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_FLOAT16_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_FLOAT32_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_FLOAT64_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_UINT8_CLAMPED_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_BIGUINT64_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_BIGINT64_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT8_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_INT8_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT16_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_INT16_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT32_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_INT32_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_FLOAT16_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_FLOAT32_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_FLOAT64_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_UINT8_CLAMPED_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_BIGUINT64_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=354&c=1
TNode<Int32T> FromConstexpr_ElementsKind_constexpr_RAB_GSAB_BIGINT64_ELEMENTS_0(compiler::CodeAssemblerState* state_, ElementsKind p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=396&c=1
ElementsKind kFirstFixedTypedArrayElementsKind_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=398&c=1
ElementsKind kFirstRabGsabFixedTypedArrayElementsKind_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=401&c=1
TNode<Int32T> FromConstexpr_AllocationFlag_constexpr_kNone_0(compiler::CodeAssemblerState* state_, CodeStubAssembler::AllocationFlag p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=401&c=1
TNode<Int32T> FromConstexpr_AllocationFlag_constexpr_kDoubleAlignment_0(compiler::CodeAssemblerState* state_, CodeStubAssembler::AllocationFlag p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=401&c=1
TNode<Int32T> FromConstexpr_AllocationFlag_constexpr_kPretenured_0(compiler::CodeAssemblerState* state_, CodeStubAssembler::AllocationFlag p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=427&c=1
TNode<IntPtrT> kBigIntDigitBits_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=540&c=1
TNode<Int32T> FromConstexpr_PropertyAttributes_constexpr_NONE_0(compiler::CodeAssemblerState* state_, PropertyAttributes p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=540&c=1
TNode<Int32T> FromConstexpr_PropertyAttributes_constexpr_READ_ONLY_0(compiler::CodeAssemblerState* state_, PropertyAttributes p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=540&c=1
TNode<Int32T> FromConstexpr_PropertyAttributes_constexpr_DONT_ENUM_0(compiler::CodeAssemblerState* state_, PropertyAttributes p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=540&c=1
TNode<Int32T> FromConstexpr_PropertyAttributes_constexpr_DONT_DELETE_0(compiler::CodeAssemblerState* state_, PropertyAttributes p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=540&c=1
TNode<Int32T> FromConstexpr_PropertyAttributes_constexpr_ALL_ATTRIBUTES_MASK_0(compiler::CodeAssemblerState* state_, PropertyAttributes p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=540&c=1
TNode<Int32T> FromConstexpr_PropertyAttributes_constexpr_FROZEN_0(compiler::CodeAssemblerState* state_, PropertyAttributes p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=562&c=1
TNode<UintPtrT> kSmiMax_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=645&c=1
TNode<TheHole> TheHole_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=646&c=1
TNode<PromiseHole> PromiseHole_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=647&c=1
TNode<Null> Null_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=648&c=1
TNode<Undefined> Undefined_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=649&c=1
TNode<True> True_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=650&c=1
TNode<False> False_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=651&c=1
TNode<String> kEmptyString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=652&c=1
TNode<String> kLengthString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=653&c=1
TNode<String> kMessageString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=654&c=1
TNode<String> kNextString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=655&c=1
TNode<String> kReturnString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=656&c=1
TNode<String> kSizeString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=657&c=1
TNode<String> kHasString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=658&c=1
TNode<String> kKeysString_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=659&c=1
TNode<ContextCell> kUndefinedContextCell_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=661&c=1
TNode<HeapNumber> kNaN_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=662&c=1
TNode<Smi> kZero_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=663&c=1
TNode<TaggedIndex> kZeroBitPattern_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=669&c=1
TNode<BoolT> FromConstexpr_LanguageMode_constexpr_kStrict_0(compiler::CodeAssemblerState* state_, LanguageMode p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=669&c=1
TNode<BoolT> FromConstexpr_LanguageMode_constexpr_kSloppy_0(compiler::CodeAssemblerState* state_, LanguageMode p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=677&c=1
TNode<JSDispatchHandleT> kInvalidDispatchHandle_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=687&c=1
TNode<HeapObject> Cast_Filler_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=707&c=1
TNode<JSSpecialObject> Cast_JSSpecialApiObject_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=710&c=1
TNode<JSObject> Cast_JSContextExtensionObject_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=712&c=1
TNode<JSObject> Cast_JSError_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_obj, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=744&c=1
TNode<Number> ToIntegerImpl_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_input);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=776&c=1
TNode<Number> ToInteger_Inline_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_input);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=791&c=1
TNode<Int32T> FromConstexpr_BigIntHandling_constexpr_kConvertToNumber_0(compiler::CodeAssemblerState* state_, CodeStubAssembler::BigIntHandling p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=791&c=1
TNode<Int32T> FromConstexpr_BigIntHandling_constexpr_kThrow_0(compiler::CodeAssemblerState* state_, CodeStubAssembler::BigIntHandling p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=915&c=1
TNode<JSPrimitive> ToPrimitiveDefault_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_v);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=965&c=1
TNode<Boolean> Equal_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_left, TNode<JSAny> p_right);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1002&c=1
TNode<BoolT> ElementsKindNotEqual_0(compiler::CodeAssemblerState* state_, TNode<Int32T> p_k1, TNode<Int32T> p_k2);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1062&c=1
TNode<BoolT> IsNumberEqual_0(compiler::CodeAssemblerState* state_, TNode<Number> p_a, TNode<Number> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1065&c=1
TNode<BoolT> IsNumberNotEqual_0(compiler::CodeAssemblerState* state_, TNode<Number> p_a, TNode<Number> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1070&c=1
TNode<BoolT> NumberIsLessThan_0(compiler::CodeAssemblerState* state_, TNode<Number> p_a, TNode<Number> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1075&c=1
TNode<BoolT> NumberIsLessThanOrEqual_0(compiler::CodeAssemblerState* state_, TNode<Number> p_a, TNode<Number> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1079&c=1
TNode<BoolT> NumberIsGreaterThan_0(compiler::CodeAssemblerState* state_, TNode<Number> p_a, TNode<Number> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1082&c=1
TNode<BoolT> NumberIsGreaterThanOrEqual_0(compiler::CodeAssemblerState* state_, TNode<Number> p_a, TNode<Number> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1088&c=1
TNode<BoolT> Float64IsNaN_0(compiler::CodeAssemblerState* state_, TNode<Float64T> p_n);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1266&c=1
TNode<Number> Min_0(compiler::CodeAssemblerState* state_, TNode<Number> p_x, TNode<Number> p_y);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1269&c=1
TNode<Number> Max_0(compiler::CodeAssemblerState* state_, TNode<Number> p_x, TNode<Number> p_y);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1307&c=1
TNode<UintPtrT> LoadJSArrayLengthAsUintPtr_0(compiler::CodeAssemblerState* state_, TNode<JSArray> p_array);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1313&c=1
TNode<UintPtrT> LoadStringLengthAsUintPtr_0(compiler::CodeAssemblerState* state_, TNode<String> p_s);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1321&c=1
TNode<String> StringAdd_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<String> p_a, TNode<String> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1326&c=1
TNode<BoolT> PromiseStateEquals_0(compiler::CodeAssemblerState* state_, TNode<Int32T> p_s1, TNode<Int32T> p_s2);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1416&c=1
TNode<Int32T> Int32Constant_0(compiler::CodeAssemblerState* state_, IntegerLiteral p_i);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1431&c=1
TNode<Smi> SmiConstant_0(compiler::CodeAssemblerState* state_, IntegerLiteral p_il);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1438&c=1
TNode<IntPtrT> IntPtrConstant_0(compiler::CodeAssemblerState* state_, IntegerLiteral p_il);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1466&c=1
TNode<Map> kFixedArrayMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1467&c=1
TNode<Map> kFixedDoubleArrayMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1468&c=1
TNode<Map> kCOWMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1469&c=1
TNode<ByteArray> kEmptyByteArray_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1470&c=1
TNode<FixedArray> kEmptyFixedArray_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1471&c=1
TNode<Map> kPromiseCapabilityMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1473&c=1
TNode<Map> kSeqOneByteStringMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1475&c=1
TNode<Map> kSeqTwoByteStringMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1476&c=1
TNode<Map> kConsOneByteStringMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1477&c=1
TNode<Map> kConsTwoByteStringMap_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1486&c=1
TNode<Union<HeapObject, Smi, Weak<HeapObject>>> kPrototypeChainInvalid_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1512&c=1
void StoreFastJSArrayLength_0(compiler::CodeAssemblerState* state_, TNode<JSArray> p_array, TNode<Smi> p_length);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1532&c=1
TNode<Int32T> FastHoleyElementsKind_0(compiler::CodeAssemblerState* state_, TNode<Int32T> p_kind);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1547&c=1
TNode<Int32T> AllowDoubleElements_0(compiler::CodeAssemblerState* state_, TNode<Int32T> p_kind);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1556&c=1
TNode<Int32T> AllowNonNumberElements_0(compiler::CodeAssemblerState* state_, TNode<Int32T> p_kind);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1569&c=1
TNode<JSFunction> GetObjectFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1572&c=1
TNode<JSFunction> GetArrayFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1575&c=1
TNode<JSReceiver> GetArrayBufferFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1578&c=1
TNode<JSFunction> GetArrayBufferNoInitFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1581&c=1
TNode<JSFunction> GetIteratorFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1584&c=1
TNode<JSFunction> GetStringFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1587&c=1
TNode<Map> GetFastPackedElementsJSArrayMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1590&c=1
TNode<Map> GetFastPackedSmiElementsJSArrayMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1594&c=1
TNode<Map> GetProxyRevocableResultMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1597&c=1
TNode<Map> GetIteratorResultMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1600&c=1
TNode<Map> GetInitialStringIteratorMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1603&c=1
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> GetReflectApply_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1606&c=1
TNode<RegExpMatchInfo> GetRegExpLastMatchInfo_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1609&c=1
TNode<Map> GetStrictArgumentsMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1612&c=1
TNode<Map> GetSloppyArgumentsMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1615&c=1
TNode<Map> GetFastAliasedArgumentsMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1618&c=1
TNode<Map> GetWeakCellMap_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1621&c=1
TNode<JSFunction> GetPrototypeApplyFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1624&c=1
TNode<JSObject> GetIteratorPrototype_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1650&c=1
TNode<BoolT> NumberIsNaN_0(compiler::CodeAssemblerState* state_, TNode<Number> p_number);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1663&c=1
TNode<BoolT> IsForceSlowPath_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1675&c=1
TNode<BoolT> ToBoolean_0(compiler::CodeAssemblerState* state_, TNode<JSAny> p_obj);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1679&c=1
TNode<JSAny> RequireObjectCoercible_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_value, const char* p_name);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1691&c=1
TNode<BoolT> SameValue_0(compiler::CodeAssemblerState* state_, TNode<Union<BigInt, Context, FixedArrayBase, FunctionTemplateInfo, HeapNumber, Hole, JSReceiver, Map, Oddball, Smi, String, Symbol, WasmFuncRef, WasmNull, WeakCell>> p_a, TNode<Union<BigInt, Context, FixedArrayBase, FunctionTemplateInfo, HeapNumber, Hole, JSReceiver, Map, Oddball, Smi, String, Symbol, WasmFuncRef, WasmNull, WeakCell>> p_b);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1698&c=1
void CheckIntegerIndexAdditionOverflow_0(compiler::CodeAssemblerState* state_, TNode<UintPtrT> p_index1, TNode<UintPtrT> p_index2, TNode<UintPtrT> p_limit, compiler::CodeAssemblerLabel* label_IfOverflow);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1722&c=1
int31_t kModeValueIsSafeIntegerUintPtr_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1725&c=1
int31_t kModeValueIsSafeInteger_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1727&c=1
int31_t kModeValueIsAnyNumber_0(compiler::CodeAssemblerState* state_);
// https://crsrc.org/c/v8/src/builtins/base.tq?l=1729&c=1
TNode<UintPtrT> TryNumberToUintPtr_0(compiler::CodeAssemblerState* state_, TNode<Number> p_valueNumber, int31_t p_kMode, compiler::CodeAssemblerLabel* label_IfLessThanZero, compiler::CodeAssemblerLabel* label_IfUIntPtrOverflow, compiler::CodeAssemblerLabel* label_IfSafeIntegerOverflow);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1777&c=1
TNode<UintPtrT> ChangeUintPtrNumberToUintPtr_0(compiler::CodeAssemblerState* state_, TNode<Number> p_value);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1787&c=1
TNode<UintPtrT> ChangeSafeIntegerNumberToUintPtr_0(compiler::CodeAssemblerState* state_, TNode<Number> p_value, compiler::CodeAssemblerLabel* label_IfUIntPtrOverflow);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1798&c=1
TNode<UintPtrT> ToUintPtr_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_value, compiler::CodeAssemblerLabel* label_IfLessThanZero, compiler::CodeAssemblerLabel* label_IfUIntPtrOverflow, compiler::CodeAssemblerLabel* label_IfSafeIntegerOverflow);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1811&c=1
TNode<UintPtrT> ToIndex_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_value, compiler::CodeAssemblerLabel* label_IfRangeError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1822&c=1
TNode<Number> GetLengthProperty_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1844&c=1
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> GetMethod_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o, TNode<Union<String, Symbol>> p_name, compiler::CodeAssemblerLabel* label_IfNullOrUndefined, compiler::CodeAssemblerLabel* label_IfMethodNotCallable, compiler::TypedCodeAssemblerVariable<JSAny>* label_IfMethodNotCallable_parameter_0);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1859&c=1
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> GetMethod_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o, TNode<String> p_name, compiler::CodeAssemblerLabel* label_IfNullOrUndefined);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1872&c=1
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> GetMethod_2(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o, const char* p_name, compiler::CodeAssemblerLabel* label_IfNullOrUndefined);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1878&c=1
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> GetMethod_3(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_o, TNode<Symbol> p_symbol, compiler::CodeAssemblerLabel* label_IfNullOrUndefined);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1891&c=1
TNode<Union<JSBoundFunction, JSFunction, JSObject, JSProxy, JSWrappedFunction>> GetInterestingMethod_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSReceiver> p_o, TNode<String> p_name, compiler::CodeAssemblerLabel* label_IfNullOrUndefined);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1911&c=1
TNode<UintPtrT> ConvertAndClampRelativeIndex_1(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_index, TNode<UintPtrT> p_length);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1920&c=1
TNode<UintPtrT> ConvertAndClampRelativeIndex_2(compiler::CodeAssemblerState* state_, TNode<Number> p_indexNumber, TNode<UintPtrT> p_length);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1934&c=1
TNode<UintPtrT> ConvertRelativeIndex_1(compiler::CodeAssemblerState* state_, TNode<Number> p_indexNumber, TNode<UintPtrT> p_length, compiler::CodeAssemblerLabel* label_OutOfBoundsLow, compiler::CodeAssemblerLabel* label_OutOfBoundsHigh);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1979&c=1
TNode<UintPtrT> ClampToIndexRange_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_index, TNode<UintPtrT> p_limit);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1988&c=1
TNode<UintPtrT> ClampToIndexRange_1(compiler::CodeAssemblerState* state_, TNode<Number> p_indexNumber, TNode<UintPtrT> p_limit);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2025&c=1
TNode<BoolT> IsFastJSArray_0(compiler::CodeAssemblerState* state_, TNode<Object> p_o, TNode<Context> p_context);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2033&c=1
void BranchIfFastJSArray_0(compiler::CodeAssemblerState* state_, TNode<Object> p_o, TNode<Context> p_context, compiler::CodeAssemblerLabel* label_True, compiler::CodeAssemblerLabel* label_False);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2043&c=1
void BranchIfFastJSArrayForRead_0(compiler::CodeAssemblerState* state_, TNode<Object> p_o, TNode<Context> p_context, compiler::CodeAssemblerLabel* label_True, compiler::CodeAssemblerLabel* label_False);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2056&c=1
TNode<BoolT> IsFastJSArrayWithNoCustomIteration_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2061&c=1
TNode<BoolT> IsFastJSArrayForReadWithNoCustomIteration_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2159&c=1
void VerifiedUnreachable_0(compiler::CodeAssemblerState* state_);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2164&c=1
TNode<BoolT> Float64IsSomeInfinity_0(compiler::CodeAssemblerState* state_, TNode<Float64T> p_value);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2171&c=1
TNode<BoolT> IsIntegerOrSomeInfinity_0(compiler::CodeAssemblerState* state_, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2188&c=1
TNode<BoolT> NumberIsSomeInfinity_0(compiler::CodeAssemblerState* state_, TNode<Number> p_n);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2199&c=1
TNode<JSAny> ReplaceTheHoleWithUndefined_0(compiler::CodeAssemblerState* state_, TNode<Union<BigInt, Boolean, HeapNumber, JSReceiver, Null, Smi, String, Symbol, TheHole, Undefined>> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2234&c=1
TNode<Uint32T> FromConstexpr_HashFieldType_constexpr_kHash_0(compiler::CodeAssemblerState* state_, Name::HashFieldType p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2234&c=1
TNode<Uint32T> FromConstexpr_HashFieldType_constexpr_kIntegerIndex_0(compiler::CodeAssemblerState* state_, Name::HashFieldType p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2234&c=1
TNode<Uint32T> FromConstexpr_HashFieldType_constexpr_kForwardingIndex_0(compiler::CodeAssemblerState* state_, Name::HashFieldType p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2234&c=1
TNode<Uint32T> FromConstexpr_HashFieldType_constexpr_kEmpty_0(compiler::CodeAssemblerState* state_, Name::HashFieldType p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2241&c=1
TNode<BoolT> HashFieldTypeEquals_0(compiler::CodeAssemblerState* state_, TNode<Uint32T> p_s1, TNode<Uint32T> p_s2);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2257&c=1
TNode<Int32T> FromConstexpr_TypedArrayAccessMode_constexpr_kRead_0(compiler::CodeAssemblerState* state_, TypedArrayAccessMode p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2257&c=1
TNode<Int32T> FromConstexpr_TypedArrayAccessMode_constexpr_kWrite_0(compiler::CodeAssemblerState* state_, TypedArrayAccessMode p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2260&c=1
TNode<JSReceiver> GetOptionsObject_0(compiler::CodeAssemblerState* state_, TNode<NativeContext> p_context, TNode<JSAny> p_options);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=85&c=10
TNode<HeapObject> WeakToStrong_HeapObject_0(compiler::CodeAssemblerState* state_, TNode<Weak<HeapObject>> p_x, compiler::CodeAssemblerLabel* label_ClearedWeakPointer);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=266&c=1
TNode<OrderedHashMap> DownCastForTorqueClass_OrderedHashMap_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=267&c=1
TNode<OrderedHashSet> DownCastForTorqueClass_OrderedHashSet_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=268&c=1
TNode<OrderedNameDictionary> DownCastForTorqueClass_OrderedNameDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=269&c=1
TNode<NameToIndexHashTable> DownCastForTorqueClass_NameToIndexHashTable_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=270&c=1
TNode<RegisteredSymbolTable> DownCastForTorqueClass_RegisteredSymbolTable_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=271&c=1
TNode<NameDictionary> DownCastForTorqueClass_NameDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=272&c=1
TNode<GlobalDictionary> DownCastForTorqueClass_GlobalDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=273&c=1
TNode<SimpleNameDictionary> DownCastForTorqueClass_SimpleNameDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=274&c=1
TNode<SimpleNumberDictionary> DownCastForTorqueClass_SimpleNumberDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=275&c=1
TNode<EphemeronHashTable> DownCastForTorqueClass_EphemeronHashTable_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=278&c=1
TNode<NumberDictionary> DownCastForTorqueClass_NumberDictionary_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=279&c=1
TNode<DoubleStringCache> DownCastForTorqueClass_DoubleStringCache_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=293&c=1
TNode<InstructionStream> DownCastForTorqueClass_InstructionStream_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=299&c=1
TNode<TransitionArray> DownCastForTorqueClass_TransitionArray_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=664&c=47
TNode<IntPtrT> Convert_intptr_constexpr_IntegerLiteral_0(compiler::CodeAssemblerState* state_, IntegerLiteral p_i);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=664&c=5
TNode<MaybeObject> Convert_Tagged_Smi_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_i);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=687&c=1
TNode<HeapObject> DownCastForTorqueClass_Filler_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=707&c=1
TNode<JSSpecialObject> DownCastForTorqueClass_JSSpecialApiObject_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=710&c=1
TNode<JSObject> DownCastForTorqueClass_JSContextExtensionObject_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=712&c=1
TNode<JSObject> DownCastForTorqueClass_JSError_0(compiler::CodeAssemblerState* state_, TNode<HeapObject> p_o, compiler::CodeAssemblerLabel* label_CastError);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1570&c=11
TorqueStructReference_JSFunction_0 NativeContextSlot_Context_JSFunction_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1576&c=11
TorqueStructReference_Constructor_0 NativeContextSlot_Context_Constructor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1588&c=11
TorqueStructReference_Map_0 NativeContextSlot_Context_Map_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1604&c=11
TorqueStructReference_Callable_0 NativeContextSlot_Context_Callable_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1607&c=11
TorqueStructReference_RegExpMatchInfo_0 NativeContextSlot_Context_RegExpMatchInfo_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1625&c=11
TorqueStructReference_JSObject_0 NativeContextSlot_Context_JSObject_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2030&c=10
TNode<BoolT> Is_FastJSArray_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2049&c=7
TNode<BoolT> Is_FastJSArrayForRead_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2058&c=10
TNode<BoolT> Is_FastJSArrayWithNoCustomIteration_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2064&c=10
TNode<BoolT> Is_FastJSArrayForReadWithNoCustomIteration_Object_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<Object> p_o);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=2168&c=20
TNode<Float64T> Convert_float64_constexpr_IntegerLiteral_0(compiler::CodeAssemblerState* state_, IntegerLiteral p_i);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1370&c=46
TNode<Smi> Convert_Smi_SmiTagged_ArrayFromAsyncLabels_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_i);

// https://crsrc.org/c/v8/src/builtins/base.tq?l=1370&c=46
TNode<Smi> Convert_Smi_SmiTagged_JSIteratorZipHelperMode_0(compiler::CodeAssemblerState* state_, TNode<Smi> p_i);

} // namespace internal
} // namespace v8

#endif // V8_GEN_TORQUE_GENERATED_SRC_BUILTINS_BASE_TQ_CSA_H_
