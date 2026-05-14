#include "src/ast/ast.h"
#include "src/builtins/builtins-array-gen.h"
#include "src/builtins/builtins-bigint-gen.h"
#include "src/builtins/builtins-call-gen.h"
#include "src/builtins/builtins-collections-gen.h"
#include "src/builtins/builtins-constructor-gen.h"
#include "src/builtins/builtins-data-view-gen.h"
#include "src/builtins/builtins-iterator-gen.h"
#include "src/builtins/builtins-object-gen.h"
#include "src/builtins/builtins-promise-gen.h"
#include "src/builtins/builtins-promise.h"
#include "src/builtins/builtins-proxy-gen.h"
#include "src/builtins/builtins-regexp-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-string-gen.h"
#include "src/builtins/builtins-typed-array-gen.h"
#include "src/builtins/builtins-utils-gen.h"
#include "src/builtins/builtins-wasm-gen.h"
#include "src/builtins/builtins.h"
#include "src/codegen/code-factory.h"
#include "src/debug/debug-wasm-objects.h"
#include "src/heap/factory-inl.h"
#include "src/ic/binary-op-assembler.h"
#include "src/ic/handler-configuration-inl.h"
#include "src/objects/arguments.h"
#include "src/objects/bigint.h"
#include "src/objects/call-site-info.h"
#include "src/objects/elements-kind.h"
#include "src/objects/free-space.h"
#include "src/objects/intl-objects.h"
#include "src/objects/js-atomics-synchronization.h"
#include "src/objects/js-break-iterator.h"
#include "src/objects/js-collator.h"
#include "src/objects/js-date-time-format.h"
#include "src/objects/js-display-names.h"
#include "src/objects/js-disposable-stack.h"
#include "src/objects/js-duration-format.h"
#include "src/objects/js-function.h"
#include "src/objects/js-generator.h"
#include "src/objects/js-iterator-helpers.h"
#include "src/objects/js-list-format.h"
#include "src/objects/js-locale.h"
#include "src/objects/js-number-format.h"
#include "src/objects/js-objects.h"
#include "src/objects/js-plural-rules.h"
#include "src/objects/js-promise.h"
#include "src/objects/js-raw-json.h"
#include "src/objects/js-regexp-string-iterator.h"
#include "src/objects/js-relative-time-format.h"
#include "src/objects/js-segment-iterator-inl.h"
#include "src/objects/js-segmenter.h"
#include "src/objects/js-segments.h"
#include "src/objects/js-shadow-realm.h"
#include "src/objects/js-shared-array.h"
#include "src/objects/js-struct.h"
#include "src/objects/js-weak-refs.h"
#include "src/objects/objects.h"
#include "src/objects/ordered-hash-table.h"
#include "src/objects/property-array.h"
#include "src/objects/property-descriptor-object.h"
#include "src/objects/sort-state.h"
#include "src/objects/source-text-module.h"
#include "src/objects/swiss-hash-table-helpers.h"
#include "src/objects/swiss-name-dictionary.h"
#include "src/objects/synthetic-module.h"
#include "src/objects/template-objects.h"
#include "src/objects/torque-defined-classes.h"
#include "src/objects/turbofan-types.h"
#include "src/objects/turboshaft-types.h"
#include "src/torque/runtime-support.h"
#include "src/wasm/value-type.h"
#include "src/wasm/wasm-linkage.h"
#include "src/wasm/wasm-module.h"
#include "src/codegen/code-stub-assembler-inl.h"
// Required Builtins:
#include "torque-generated/src/builtins/promise-all-element-closure-tq-csa.h"
#include "torque-generated/src/builtins/array-from-async-tq-csa.h"
#include "torque-generated/src/builtins/array-join-tq-csa.h"
#include "torque-generated/src/builtins/base-tq-csa.h"
#include "torque-generated/src/builtins/builtins-string-tq-csa.h"
#include "torque-generated/src/builtins/convert-tq-csa.h"
#include "torque-generated/src/builtins/promise-all-element-closure-tq-csa.h"
#include "torque-generated/src/builtins/promise-any-tq-csa.h"
#include "torque-generated/src/builtins/torque-internal-tq-csa.h"
#include "torque-generated/src/objects/contexts-tq-csa.h"
#include "torque-generated/src/objects/fixed-array-tq-csa.h"
#include "torque-generated/src/objects/js-array-tq-csa.h"
#include "torque-generated/src/objects/js-function-tq-csa.h"
#include "torque-generated/src/objects/js-objects-tq-csa.h"

namespace v8 {
namespace internal {

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementRemainingSlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementCapabilitySlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementValuesSlot_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementLength_0(compiler::CodeAssemblerState* state_, PromiseBuiltins::PromiseAllResolveElementContextSlots p_o) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<IntPtrT> tmp0;
  TNode<IntPtrT> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = ca_.IntPtrConstant(CastToUnderlyingTypeIfEnum(p_o));
    tmp1 = (TNode<IntPtrT>{tmp0});
    ca_.Goto(&block2);
  }

    ca_.Bind(&block2);
  return TNode<IntPtrT>{tmp1};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> kPromiseAllResolveElementRemainingSlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementRemainingSlot_0(state_, PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementRemainingSlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> kPromiseAllResolveElementCapabilitySlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementCapabilitySlot_0(state_, PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementCapabilitySlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=69&c=1
TNode<IntPtrT> kPromiseAllResolveElementValuesSlot_0(compiler::CodeAssemblerState* state_) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

    ca_.Bind(&block0);
  TNode<IntPtrT> tmp0;
    tmp0 = FromConstexpr_PromiseAllResolveElementContextSlots_constexpr_kPromiseAllResolveElementValuesSlot_0(state_, PromiseBuiltins::PromiseAllResolveElementContextSlots::kPromiseAllResolveElementValuesSlot);
  TNode<IntPtrT> tmp1;
    tmp1 = (TNode<IntPtrT>{tmp0});
  return TNode<IntPtrT>{tmp1};}

TF_BUILTIN(PromiseAllResolveElementClosure, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<JSAny> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = PromiseAllResolveElementClosure_PromiseAllWrapResultAsFulfilledFunctor_0(state_, TNode<Context>{tmp0}, TNode<JSAny>{parameter3}, TNode<JSFunction>{parameter2}, TorqueStructPromiseAllWrapResultAsFulfilledFunctor_0{});
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(PromiseAllSettledResolveElementClosure, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<JSAny> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsFulfilledFunctor_0(state_, TNode<Context>{tmp0}, TNode<JSAny>{parameter3}, TNode<JSFunction>{parameter2}, TorqueStructPromiseAllSettledWrapResultAsFulfilledFunctor_0{});
    CodeStubAssembler(state_).Return(tmp1);
  }
}

TF_BUILTIN(PromiseAllSettledRejectElementClosure, CodeStubAssembler) {
  compiler::CodeAssemblerState* state_ = state();  compiler::CodeAssembler ca_(state());
  TNode<NativeContext> parameter0 = UncheckedParameter<NativeContext>(Descriptor::kContext);
  USE(parameter0);
  TNode<JSAny> parameter1 = UncheckedParameter<JSAny>(Descriptor::kReceiver);
  USE(parameter1);
  TNode<JSFunction> parameter2 = UncheckedParameter<JSFunction>(Descriptor::kJSTarget);
  USE(parameter2);
  TNode<JSAny> parameter3 = UncheckedParameter<JSAny>(Descriptor::kValue);
  USE(parameter3);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Context> tmp0;
  TNode<JSAny> tmp1;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = (TNode<Context>{parameter0});
    tmp1 = PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsRejectedFunctor_0(state_, TNode<Context>{tmp0}, TNode<JSAny>{parameter3}, TNode<JSFunction>{parameter2}, TorqueStructPromiseAllSettledWrapResultAsRejectedFunctor_0{});
    CodeStubAssembler(state_).Return(tmp1);
  }
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=172&c=10
TNode<JSAny> PromiseAllResolveElementClosure_PromiseAllWrapResultAsFulfilledFunctor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_value, TNode<JSFunction> p_function, TorqueStructPromiseAllWrapResultAsFulfilledFunctor_0 p_wrapResultFunctor) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block26(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block25(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block31(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block32(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block38(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block39(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt31Equal(PropertyArray::kNoHashSentinel, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull))))));
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 94});
      CodeStubAssembler(state_).FailAssert("Torque assert 'kPropertyArrayNoHashSentinel == 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = CodeStubAssembler(state_).LoadJSReceiverIdentityHash(TNode<JSReceiver>{p_function}, &label2);
    ca_.Goto(&block6);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/promise-all-element-closure.tq:96:54");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp3 = CodeStubAssembler(state_).ChangeUint32ToWord(TNode<Uint32T>{tmp1});
    tmp4 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    tmp5 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    ca_.Branch(tmp5, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 97});
      CodeStubAssembler(state_).FailAssert("Torque assert 'ChangeUint32ToWord(identityHash) < kSmiMaxValue' failed", pos_stack);
    }
  }

  TNode<UintPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<BoolT> tmp15;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp6 = CodeStubAssembler(state_).ChangeUint32ToWord(TNode<Uint32T>{tmp1});
    tmp7 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp9 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp8});
    tmp10 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp11, tmp12) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    tmp13 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp12});
    tmp14 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp13}, TNode<Smi>{tmp14});
    ca_.Branch(tmp15, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp16 = Undefined_0(state_);
    ca_.Goto(&block1, tmp16);
  }

  TNode<IntPtrT> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<FixedArray> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<BoolT> tmp24;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp17 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp18, tmp19) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp22 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp21});
    tmp23 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    tmp24 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp23});
    ca_.Branch(tmp24, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{tmp20});
  }

  TNode<IntPtrT> tmp25;
  TNode<PromiseHole> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<FixedArray> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp25 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    tmp26 = PromiseHole_0(state_);
    tmp27 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp28 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp20}, TNode<IntPtrT>{tmp27}, TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp22}, TNode<Hole>{tmp26});
    tmp29 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp30, tmp31) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp29}).Flatten();
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp30, tmp31}, tmp28);
    ca_.Goto(&block13, tmp28);
  }

  TNode<FixedArray> phi_bb13_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<UintPtrT> tmp35;
  TNode<UintPtrT> tmp36;
  TNode<BoolT> tmp37;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    std::tie(tmp32, tmp33, tmp34) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb13_6}).Flatten();
    tmp35 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp36 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp34});
    tmp37 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp35}, TNode<UintPtrT>{tmp36});
    ca_.Branch(tmp37, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Union<HeapObject, TaggedIndex>> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<Object> tmp42;
  TNode<PromiseHole> tmp43;
  TNode<BoolT> tmp44;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp38 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp39 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{tmp38});
    std::tie(tmp40, tmp41) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp32}, TNode<IntPtrT>{tmp39}).Flatten();
    tmp42 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp40, tmp41});
    tmp43 = PromiseHole_0(state_);
    tmp44 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp42}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp43});
    ca_.Branch(tmp44, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Undefined> tmp45;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp45 = Undefined_0(state_);
    ca_.Goto(&block1, tmp45);
  }

  TNode<NativeContext> tmp46;
  TNode<PromiseHole> tmp47;
  TNode<BoolT> tmp48;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp46 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp47 = PromiseHole_0(state_);
    tmp48 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{p_value}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp47});
    ca_.Branch(tmp48, &block25, std::vector<compiler::Node*>{}, &block26, std::vector<compiler::Node*>{});
  }

  if (block26.is_used()) {
    ca_.Bind(&block26);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 15});
      CodeStubAssembler(state_).FailAssert("Torque assert 'value != PromiseHole' failed", pos_stack);
    }
  }

  TNode<Union<HeapObject, TaggedIndex>> tmp49;
  TNode<IntPtrT> tmp50;
  TNode<IntPtrT> tmp51;
  TNode<UintPtrT> tmp52;
  TNode<UintPtrT> tmp53;
  TNode<BoolT> tmp54;
  if (block25.is_used()) {
    ca_.Bind(&block25);
    std::tie(tmp49, tmp50, tmp51) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb13_6}).Flatten();
    tmp52 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp53 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp51});
    tmp54 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp52}, TNode<UintPtrT>{tmp53});
    ca_.Branch(tmp54, &block31, std::vector<compiler::Node*>{}, &block32, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp55;
  TNode<IntPtrT> tmp56;
  TNode<Union<HeapObject, TaggedIndex>> tmp57;
  TNode<IntPtrT> tmp58;
  TNode<Smi> tmp59;
  TNode<Smi> tmp60;
  TNode<Smi> tmp61;
  TNode<BoolT> tmp62;
  if (block31.is_used()) {
    ca_.Bind(&block31);
    tmp55 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp56 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp50}, TNode<IntPtrT>{tmp55});
    std::tie(tmp57, tmp58) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp49}, TNode<IntPtrT>{tmp56}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp57, tmp58}, p_value);
    tmp59 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp60 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp13}, TNode<Smi>{tmp59});
    tmp61 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp62 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp60}, TNode<Smi>{tmp61});
    ca_.Branch(tmp62, &block35, std::vector<compiler::Node*>{}, &block36, std::vector<compiler::Node*>{});
  }

  if (block32.is_used()) {
    ca_.Bind(&block32);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block36.is_used()) {
    ca_.Bind(&block36);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 140});
      CodeStubAssembler(state_).FailAssert("Torque assert 'remainingElementsCount >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp63;
  TNode<Union<HeapObject, TaggedIndex>> tmp64;
  TNode<IntPtrT> tmp65;
  TNode<Smi> tmp66;
  TNode<BoolT> tmp67;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp63 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp64, tmp65) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp63}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp64, tmp65}, tmp60);
    tmp66 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp67 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp60}, TNode<Smi>{tmp66});
    ca_.Branch(tmp67, &block37, std::vector<compiler::Node*>{}, &block38, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp68;
  TNode<Union<HeapObject, TaggedIndex>> tmp69;
  TNode<IntPtrT> tmp70;
  TNode<PromiseCapability> tmp71;
  TNode<IntPtrT> tmp72;
  TNode<JSAny> tmp73;
  TNode<JSAny> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<Union<HeapObject, TaggedIndex>> tmp76;
  TNode<IntPtrT> tmp77;
  TNode<Map> tmp78;
  TNode<IntPtrT> tmp79;
  TNode<Union<HeapObject, TaggedIndex>> tmp80;
  TNode<IntPtrT> tmp81;
  TNode<FixedArray> tmp82;
  TNode<JSArray> tmp83;
  TNode<Undefined> tmp84;
  TNode<JSAny> tmp85;
  if (block37.is_used()) {
    ca_.Bind(&block37);
    tmp68 = kPromiseAllResolveElementCapabilitySlot_0(state_);
    std::tie(tmp69, tmp70) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp68}).Flatten();
    tmp71 = CodeStubAssembler(state_).LoadReference<PromiseCapability>(CodeStubAssembler::Reference{tmp69, tmp70});
    tmp72 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp73 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp71, tmp72});
    tmp74 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp73});
    tmp75 = JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX_0(state_);
    std::tie(tmp76, tmp77) = NativeContextSlot_Map_1(state_, TNode<NativeContext>{tmp46}, TNode<IntPtrT>{tmp75}).Flatten();
    tmp78 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp76, tmp77});
    tmp79 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp80, tmp81) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp79}).Flatten();
    tmp82 = kEmptyFixedArray_0(state_);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp80, tmp81}, tmp82);
    tmp83 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp78}, TNode<FixedArrayBase>{phi_bb13_6});
    tmp84 = Undefined_0(state_);
    tmp85 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<JSAny>{tmp74}, TNode<JSAny>{tmp84}, TNode<JSAny>{tmp83});
    ca_.Goto(&block38);
  }

  TNode<Undefined> tmp86;
  if (block38.is_used()) {
    ca_.Bind(&block38);
    tmp86 = Undefined_0(state_);
    ca_.Goto(&block1, tmp86);
  }

  TNode<JSAny> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block39, phi_bb1_3);
  }

  TNode<JSAny> phi_bb39_3;
    ca_.Bind(&block39, &phi_bb39_3);
  return TNode<JSAny>{phi_bb39_3};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=180&c=10
TNode<JSAny> PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsFulfilledFunctor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_value, TNode<JSFunction> p_function, TorqueStructPromiseAllSettledWrapResultAsFulfilledFunctor_0 p_wrapResultFunctor) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt31Equal(PropertyArray::kNoHashSentinel, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull))))));
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 94});
      CodeStubAssembler(state_).FailAssert("Torque assert 'kPropertyArrayNoHashSentinel == 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = CodeStubAssembler(state_).LoadJSReceiverIdentityHash(TNode<JSReceiver>{p_function}, &label2);
    ca_.Goto(&block6);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/promise-all-element-closure.tq:96:54");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp3 = CodeStubAssembler(state_).ChangeUint32ToWord(TNode<Uint32T>{tmp1});
    tmp4 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    tmp5 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    ca_.Branch(tmp5, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 97});
      CodeStubAssembler(state_).FailAssert("Torque assert 'ChangeUint32ToWord(identityHash) < kSmiMaxValue' failed", pos_stack);
    }
  }

  TNode<UintPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<BoolT> tmp15;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp6 = CodeStubAssembler(state_).ChangeUint32ToWord(TNode<Uint32T>{tmp1});
    tmp7 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp9 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp8});
    tmp10 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp11, tmp12) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    tmp13 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp12});
    tmp14 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp13}, TNode<Smi>{tmp14});
    ca_.Branch(tmp15, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp16 = Undefined_0(state_);
    ca_.Goto(&block1, tmp16);
  }

  TNode<IntPtrT> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<FixedArray> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<BoolT> tmp24;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp17 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp18, tmp19) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp22 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp21});
    tmp23 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    tmp24 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp23});
    ca_.Branch(tmp24, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{tmp20});
  }

  TNode<IntPtrT> tmp25;
  TNode<PromiseHole> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<FixedArray> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp25 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    tmp26 = PromiseHole_0(state_);
    tmp27 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp28 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp20}, TNode<IntPtrT>{tmp27}, TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp22}, TNode<Hole>{tmp26});
    tmp29 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp30, tmp31) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp29}).Flatten();
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp30, tmp31}, tmp28);
    ca_.Goto(&block13, tmp28);
  }

  TNode<FixedArray> phi_bb13_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<UintPtrT> tmp35;
  TNode<UintPtrT> tmp36;
  TNode<BoolT> tmp37;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    std::tie(tmp32, tmp33, tmp34) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb13_6}).Flatten();
    tmp35 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp36 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp34});
    tmp37 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp35}, TNode<UintPtrT>{tmp36});
    ca_.Branch(tmp37, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Union<HeapObject, TaggedIndex>> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<Object> tmp42;
  TNode<PromiseHole> tmp43;
  TNode<BoolT> tmp44;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp38 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp39 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{tmp38});
    std::tie(tmp40, tmp41) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp32}, TNode<IntPtrT>{tmp39}).Flatten();
    tmp42 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp40, tmp41});
    tmp43 = PromiseHole_0(state_);
    tmp44 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp42}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp43});
    ca_.Branch(tmp44, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Undefined> tmp45;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp45 = Undefined_0(state_);
    ca_.Goto(&block1, tmp45);
  }

  TNode<NativeContext> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Union<HeapObject, TaggedIndex>> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<JSFunction> tmp50;
  TNode<Union<JSReceiver, Map, TheHole>> tmp51;
  TNode<Map> tmp52;
  TNode<JSObject> tmp53;
  TNode<String> tmp54;
  TNode<String> tmp55;
  TNode<Object> tmp56;
  TNode<String> tmp57;
  TNode<Object> tmp58;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<UintPtrT> tmp62;
  TNode<UintPtrT> tmp63;
  TNode<BoolT> tmp64;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp46 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp47 = OBJECT_FUNCTION_INDEX_0(state_);
    std::tie(tmp48, tmp49) = NativeContextSlot_JSFunction_0(state_, TNode<NativeContext>{tmp46}, TNode<IntPtrT>{tmp47}).Flatten();
    tmp50 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp48, tmp49});
    tmp51 = CodeStubAssembler(state_).LoadJSFunctionPrototypeOrInitialMap(TNode<JSFunction>{tmp50});
    tmp52 = UnsafeCast_Map_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp51});
    tmp53 = CodeStubAssembler(state_).AllocateJSObjectFromMap(TNode<Map>{tmp52});
    tmp54 = CodeStubAssembler(state_).StringConstant("status");
    tmp55 = CodeStubAssembler(state_).StringConstant("fulfilled");
    tmp56 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, p_context, tmp53, tmp54, tmp55);
    tmp57 = CodeStubAssembler(state_).StringConstant("value");
    tmp58 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, p_context, tmp53, tmp57, p_value);
    std::tie(tmp59, tmp60, tmp61) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb13_6}).Flatten();
    tmp62 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp63 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp61});
    tmp64 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp62}, TNode<UintPtrT>{tmp63});
    ca_.Branch(tmp64, &block29, std::vector<compiler::Node*>{}, &block30, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<Union<HeapObject, TaggedIndex>> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<Smi> tmp69;
  TNode<Smi> tmp70;
  TNode<Smi> tmp71;
  TNode<BoolT> tmp72;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp65 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp66 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp65});
    std::tie(tmp67, tmp68) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp66}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp67, tmp68}, tmp53);
    tmp69 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp70 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp13}, TNode<Smi>{tmp69});
    tmp71 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp72 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp70}, TNode<Smi>{tmp71});
    ca_.Branch(tmp72, &block33, std::vector<compiler::Node*>{}, &block34, std::vector<compiler::Node*>{});
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 140});
      CodeStubAssembler(state_).FailAssert("Torque assert 'remainingElementsCount >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp73;
  TNode<Union<HeapObject, TaggedIndex>> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<Smi> tmp76;
  TNode<BoolT> tmp77;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp73 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp74, tmp75) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp73}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp74, tmp75}, tmp70);
    tmp76 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp77 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp70}, TNode<Smi>{tmp76});
    ca_.Branch(tmp77, &block35, std::vector<compiler::Node*>{}, &block36, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp78;
  TNode<Union<HeapObject, TaggedIndex>> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<PromiseCapability> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<JSAny> tmp83;
  TNode<JSAny> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<Union<HeapObject, TaggedIndex>> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<Map> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Union<HeapObject, TaggedIndex>> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<FixedArray> tmp92;
  TNode<JSArray> tmp93;
  TNode<Undefined> tmp94;
  TNode<JSAny> tmp95;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp78 = kPromiseAllResolveElementCapabilitySlot_0(state_);
    std::tie(tmp79, tmp80) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp78}).Flatten();
    tmp81 = CodeStubAssembler(state_).LoadReference<PromiseCapability>(CodeStubAssembler::Reference{tmp79, tmp80});
    tmp82 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp83 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp81, tmp82});
    tmp84 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp83});
    tmp85 = JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX_0(state_);
    std::tie(tmp86, tmp87) = NativeContextSlot_Map_1(state_, TNode<NativeContext>{tmp46}, TNode<IntPtrT>{tmp85}).Flatten();
    tmp88 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp86, tmp87});
    tmp89 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp90, tmp91) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp89}).Flatten();
    tmp92 = kEmptyFixedArray_0(state_);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp90, tmp91}, tmp92);
    tmp93 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp88}, TNode<FixedArrayBase>{phi_bb13_6});
    tmp94 = Undefined_0(state_);
    tmp95 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<JSAny>{tmp84}, TNode<JSAny>{tmp94}, TNode<JSAny>{tmp93});
    ca_.Goto(&block36);
  }

  TNode<Undefined> tmp96;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp96 = Undefined_0(state_);
    ca_.Goto(&block1, tmp96);
  }

  TNode<JSAny> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block37, phi_bb1_3);
  }

  TNode<JSAny> phi_bb37_3;
    ca_.Bind(&block37, &phi_bb37_3);
  return TNode<JSAny>{phi_bb37_3};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=188&c=10
TNode<JSAny> PromiseAllResolveElementClosure_PromiseAllSettledWrapResultAsRejectedFunctor_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<JSAny> p_value, TNode<JSFunction> p_function, TorqueStructPromiseAllSettledWrapResultAsRejectedFunctor_0 p_wrapResultFunctor) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block3(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block2(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block9(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block8(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block11(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block12(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<FixedArray> block13(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block20(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block21(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block14(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block15(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block29(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block30(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block34(&ca_, compiler::CodeAssemblerLabel::kDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block33(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block35(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block36(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block1(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<JSAny> block37(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<BoolT> tmp0;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    tmp0 = FromConstexpr_bool_constexpr_bool_0(state_, (CodeStubAssembler(state_).ConstexprInt31Equal(PropertyArray::kNoHashSentinel, (FromConstexpr_constexpr_int31_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull))))));
    ca_.Branch(tmp0, &block2, std::vector<compiler::Node*>{}, &block3, std::vector<compiler::Node*>{});
  }

  if (block3.is_used()) {
    ca_.Bind(&block3);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 94});
      CodeStubAssembler(state_).FailAssert("Torque assert 'kPropertyArrayNoHashSentinel == 0' failed", pos_stack);
    }
  }

  TNode<Uint32T> tmp1;
  if (block2.is_used()) {
    ca_.Bind(&block2);
    compiler::CodeAssemblerLabel label2(&ca_);
    tmp1 = CodeStubAssembler(state_).LoadJSReceiverIdentityHash(TNode<JSReceiver>{p_function}, &label2);
    ca_.Goto(&block6);
    if (label2.is_used()) {
      ca_.Bind(&label2);
      ca_.Goto(&block7);
    }
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/promise-all-element-closure.tq:96:54");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp3 = CodeStubAssembler(state_).ChangeUint32ToWord(TNode<Uint32T>{tmp1});
    tmp4 = FromConstexpr_uintptr_constexpr_uintptr_0(state_, kSmiMaxValue);
    tmp5 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    ca_.Branch(tmp5, &block8, std::vector<compiler::Node*>{}, &block9, std::vector<compiler::Node*>{});
  }

  if (block9.is_used()) {
    ca_.Bind(&block9);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 97});
      CodeStubAssembler(state_).FailAssert("Torque assert 'ChangeUint32ToWord(identityHash) < kSmiMaxValue' failed", pos_stack);
    }
  }

  TNode<UintPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<IntPtrT> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<IntPtrT> tmp10;
  TNode<Union<HeapObject, TaggedIndex>> tmp11;
  TNode<IntPtrT> tmp12;
  TNode<Smi> tmp13;
  TNode<Smi> tmp14;
  TNode<BoolT> tmp15;
  if (block8.is_used()) {
    ca_.Bind(&block8);
    tmp6 = CodeStubAssembler(state_).ChangeUint32ToWord(TNode<Uint32T>{tmp1});
    tmp7 = CodeStubAssembler(state_).Signed(TNode<UintPtrT>{tmp6});
    tmp8 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp9 = CodeStubAssembler(state_).IntPtrSub(TNode<IntPtrT>{tmp7}, TNode<IntPtrT>{tmp8});
    tmp10 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp11, tmp12) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp10}).Flatten();
    tmp13 = CodeStubAssembler(state_).LoadReference<Smi>(CodeStubAssembler::Reference{tmp11, tmp12});
    tmp14 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp15 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp13}, TNode<Smi>{tmp14});
    ca_.Branch(tmp15, &block10, std::vector<compiler::Node*>{}, &block11, std::vector<compiler::Node*>{});
  }

  TNode<Undefined> tmp16;
  if (block10.is_used()) {
    ca_.Bind(&block10);
    tmp16 = Undefined_0(state_);
    ca_.Goto(&block1, tmp16);
  }

  TNode<IntPtrT> tmp17;
  TNode<Union<HeapObject, TaggedIndex>> tmp18;
  TNode<IntPtrT> tmp19;
  TNode<FixedArray> tmp20;
  TNode<IntPtrT> tmp21;
  TNode<IntPtrT> tmp22;
  TNode<IntPtrT> tmp23;
  TNode<BoolT> tmp24;
  if (block11.is_used()) {
    ca_.Bind(&block11);
    tmp17 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp18, tmp19) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp17}).Flatten();
    tmp20 = CodeStubAssembler(state_).LoadReference<FixedArray>(CodeStubAssembler::Reference{tmp18, tmp19});
    tmp21 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp22 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp9}, TNode<IntPtrT>{tmp21});
    tmp23 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    tmp24 = CodeStubAssembler(state_).IntPtrGreaterThan(TNode<IntPtrT>{tmp22}, TNode<IntPtrT>{tmp23});
    ca_.Branch(tmp24, &block12, std::vector<compiler::Node*>{}, &block13, std::vector<compiler::Node*>{tmp20});
  }

  TNode<IntPtrT> tmp25;
  TNode<PromiseHole> tmp26;
  TNode<IntPtrT> tmp27;
  TNode<FixedArray> tmp28;
  TNode<IntPtrT> tmp29;
  TNode<Union<HeapObject, TaggedIndex>> tmp30;
  TNode<IntPtrT> tmp31;
  if (block12.is_used()) {
    ca_.Bind(&block12);
    tmp25 = LoadFixedArrayBaseLengthIntptr_0(state_, TNode<FixedArrayBase>{tmp20});
    tmp26 = PromiseHole_0(state_);
    tmp27 = FromConstexpr_intptr_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp28 = ExtractFixedArray_0(state_, TNode<FixedArray>{tmp20}, TNode<IntPtrT>{tmp27}, TNode<IntPtrT>{tmp25}, TNode<IntPtrT>{tmp22}, TNode<Hole>{tmp26});
    tmp29 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp30, tmp31) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp29}).Flatten();
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp30, tmp31}, tmp28);
    ca_.Goto(&block13, tmp28);
  }

  TNode<FixedArray> phi_bb13_6;
  TNode<Union<HeapObject, TaggedIndex>> tmp32;
  TNode<IntPtrT> tmp33;
  TNode<IntPtrT> tmp34;
  TNode<UintPtrT> tmp35;
  TNode<UintPtrT> tmp36;
  TNode<BoolT> tmp37;
  if (block13.is_used()) {
    ca_.Bind(&block13, &phi_bb13_6);
    std::tie(tmp32, tmp33, tmp34) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb13_6}).Flatten();
    tmp35 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp36 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp34});
    tmp37 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp35}, TNode<UintPtrT>{tmp36});
    ca_.Branch(tmp37, &block20, std::vector<compiler::Node*>{}, &block21, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp38;
  TNode<IntPtrT> tmp39;
  TNode<Union<HeapObject, TaggedIndex>> tmp40;
  TNode<IntPtrT> tmp41;
  TNode<Object> tmp42;
  TNode<PromiseHole> tmp43;
  TNode<BoolT> tmp44;
  if (block20.is_used()) {
    ca_.Bind(&block20);
    tmp38 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp39 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp33}, TNode<IntPtrT>{tmp38});
    std::tie(tmp40, tmp41) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp32}, TNode<IntPtrT>{tmp39}).Flatten();
    tmp42 = CodeStubAssembler(state_).LoadReference<Object>(CodeStubAssembler::Reference{tmp40, tmp41});
    tmp43 = PromiseHole_0(state_);
    tmp44 = CodeStubAssembler(state_).TaggedNotEqual(TNode<Object>{tmp42}, TNode<Union<Context, FixedArrayBase, FunctionTemplateInfo, Hole, JSReceiver, Map, Oddball, String, Symbol, WasmFuncRef, WasmNull, WeakCell>>{tmp43});
    ca_.Branch(tmp44, &block14, std::vector<compiler::Node*>{}, &block15, std::vector<compiler::Node*>{});
  }

  if (block21.is_used()) {
    ca_.Bind(&block21);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  TNode<Undefined> tmp45;
  if (block14.is_used()) {
    ca_.Bind(&block14);
    tmp45 = Undefined_0(state_);
    ca_.Goto(&block1, tmp45);
  }

  TNode<NativeContext> tmp46;
  TNode<IntPtrT> tmp47;
  TNode<Union<HeapObject, TaggedIndex>> tmp48;
  TNode<IntPtrT> tmp49;
  TNode<JSFunction> tmp50;
  TNode<Union<JSReceiver, Map, TheHole>> tmp51;
  TNode<Map> tmp52;
  TNode<JSObject> tmp53;
  TNode<String> tmp54;
  TNode<String> tmp55;
  TNode<Object> tmp56;
  TNode<String> tmp57;
  TNode<Object> tmp58;
  TNode<Union<HeapObject, TaggedIndex>> tmp59;
  TNode<IntPtrT> tmp60;
  TNode<IntPtrT> tmp61;
  TNode<UintPtrT> tmp62;
  TNode<UintPtrT> tmp63;
  TNode<BoolT> tmp64;
  if (block15.is_used()) {
    ca_.Bind(&block15);
    tmp46 = CodeStubAssembler(state_).LoadNativeContext(TNode<Context>{p_context});
    tmp47 = OBJECT_FUNCTION_INDEX_0(state_);
    std::tie(tmp48, tmp49) = NativeContextSlot_JSFunction_0(state_, TNode<NativeContext>{tmp46}, TNode<IntPtrT>{tmp47}).Flatten();
    tmp50 = CodeStubAssembler(state_).LoadReference<JSFunction>(CodeStubAssembler::Reference{tmp48, tmp49});
    tmp51 = CodeStubAssembler(state_).LoadJSFunctionPrototypeOrInitialMap(TNode<JSFunction>{tmp50});
    tmp52 = UnsafeCast_Map_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp51});
    tmp53 = CodeStubAssembler(state_).AllocateJSObjectFromMap(TNode<Map>{tmp52});
    tmp54 = CodeStubAssembler(state_).StringConstant("status");
    tmp55 = CodeStubAssembler(state_).StringConstant("rejected");
    tmp56 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, p_context, tmp53, tmp54, tmp55);
    tmp57 = CodeStubAssembler(state_).StringConstant("reason");
    tmp58 = ca_.CallBuiltin<Object>(Builtin::kFastCreateDataProperty, p_context, tmp53, tmp57, p_value);
    std::tie(tmp59, tmp60, tmp61) = FieldSliceFixedArrayObjects_0(state_, TNode<FixedArray>{phi_bb13_6}).Flatten();
    tmp62 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp9});
    tmp63 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp61});
    tmp64 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp62}, TNode<UintPtrT>{tmp63});
    ca_.Branch(tmp64, &block29, std::vector<compiler::Node*>{}, &block30, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp65;
  TNode<IntPtrT> tmp66;
  TNode<Union<HeapObject, TaggedIndex>> tmp67;
  TNode<IntPtrT> tmp68;
  TNode<Smi> tmp69;
  TNode<Smi> tmp70;
  TNode<Smi> tmp71;
  TNode<BoolT> tmp72;
  if (block29.is_used()) {
    ca_.Bind(&block29);
    tmp65 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{tmp9});
    tmp66 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp60}, TNode<IntPtrT>{tmp65});
    std::tie(tmp67, tmp68) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp59}, TNode<IntPtrT>{tmp66}).Flatten();
    CodeStubAssembler(state_).StoreReference<Object>(CodeStubAssembler::Reference{tmp67, tmp68}, tmp53);
    tmp69 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x1ull));
    tmp70 = CodeStubAssembler(state_).SmiSub(TNode<Smi>{tmp13}, TNode<Smi>{tmp69});
    tmp71 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp72 = CodeStubAssembler(state_).SmiGreaterThanOrEqual(TNode<Smi>{tmp70}, TNode<Smi>{tmp71});
    ca_.Branch(tmp72, &block33, std::vector<compiler::Node*>{}, &block34, std::vector<compiler::Node*>{});
  }

  if (block30.is_used()) {
    ca_.Bind(&block30);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

  if (block34.is_used()) {
    ca_.Bind(&block34);
    {
      auto pos_stack = ca_.GetMacroSourcePositionStack();
      pos_stack.push_back({"src/builtins/promise-all-element-closure.tq", 140});
      CodeStubAssembler(state_).FailAssert("Torque assert 'remainingElementsCount >= 0' failed", pos_stack);
    }
  }

  TNode<IntPtrT> tmp73;
  TNode<Union<HeapObject, TaggedIndex>> tmp74;
  TNode<IntPtrT> tmp75;
  TNode<Smi> tmp76;
  TNode<BoolT> tmp77;
  if (block33.is_used()) {
    ca_.Bind(&block33);
    tmp73 = kPromiseAllResolveElementRemainingSlot_0(state_);
    std::tie(tmp74, tmp75) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp73}).Flatten();
    CodeStubAssembler(state_).StoreReference<Smi>(CodeStubAssembler::Reference{tmp74, tmp75}, tmp70);
    tmp76 = FromConstexpr_Smi_constexpr_IntegerLiteral_0(state_, IntegerLiteral(false, 0x0ull));
    tmp77 = CodeStubAssembler(state_).SmiEqual(TNode<Smi>{tmp70}, TNode<Smi>{tmp76});
    ca_.Branch(tmp77, &block35, std::vector<compiler::Node*>{}, &block36, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp78;
  TNode<Union<HeapObject, TaggedIndex>> tmp79;
  TNode<IntPtrT> tmp80;
  TNode<PromiseCapability> tmp81;
  TNode<IntPtrT> tmp82;
  TNode<JSAny> tmp83;
  TNode<JSAny> tmp84;
  TNode<IntPtrT> tmp85;
  TNode<Union<HeapObject, TaggedIndex>> tmp86;
  TNode<IntPtrT> tmp87;
  TNode<Map> tmp88;
  TNode<IntPtrT> tmp89;
  TNode<Union<HeapObject, TaggedIndex>> tmp90;
  TNode<IntPtrT> tmp91;
  TNode<FixedArray> tmp92;
  TNode<JSArray> tmp93;
  TNode<Undefined> tmp94;
  TNode<JSAny> tmp95;
  if (block35.is_used()) {
    ca_.Bind(&block35);
    tmp78 = kPromiseAllResolveElementCapabilitySlot_0(state_);
    std::tie(tmp79, tmp80) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp78}).Flatten();
    tmp81 = CodeStubAssembler(state_).LoadReference<PromiseCapability>(CodeStubAssembler::Reference{tmp79, tmp80});
    tmp82 = FromConstexpr_intptr_constexpr_int31_0(state_, 8);
    tmp83 = CodeStubAssembler(state_).LoadReference<JSAny>(CodeStubAssembler::Reference{tmp81, tmp82});
    tmp84 = UnsafeCast_JSAny_0(state_, TNode<Context>{p_context}, TNode<Object>{tmp83});
    tmp85 = JS_ARRAY_PACKED_ELEMENTS_MAP_INDEX_0(state_);
    std::tie(tmp86, tmp87) = NativeContextSlot_Map_1(state_, TNode<NativeContext>{tmp46}, TNode<IntPtrT>{tmp85}).Flatten();
    tmp88 = CodeStubAssembler(state_).LoadReference<Map>(CodeStubAssembler::Reference{tmp86, tmp87});
    tmp89 = kPromiseAllResolveElementValuesSlot_0(state_);
    std::tie(tmp90, tmp91) = ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(state_, TNode<Context>{p_context}, TNode<IntPtrT>{tmp89}).Flatten();
    tmp92 = kEmptyFixedArray_0(state_);
    CodeStubAssembler(state_).StoreReference<FixedArray>(CodeStubAssembler::Reference{tmp90, tmp91}, tmp92);
    tmp93 = NewJSArray_0(state_, TNode<Context>{p_context}, TNode<Map>{tmp88}, TNode<FixedArrayBase>{phi_bb13_6});
    tmp94 = Undefined_0(state_);
    tmp95 = CodeStubAssembler(state_).Call(TNode<Context>{p_context}, TNode<JSAny>{tmp84}, TNode<JSAny>{tmp94}, TNode<JSAny>{tmp93});
    ca_.Goto(&block36);
  }

  TNode<Undefined> tmp96;
  if (block36.is_used()) {
    ca_.Bind(&block36);
    tmp96 = Undefined_0(state_);
    ca_.Goto(&block1, tmp96);
  }

  TNode<JSAny> phi_bb1_3;
  if (block1.is_used()) {
    ca_.Bind(&block1, &phi_bb1_3);
    ca_.Goto(&block37, phi_bb1_3);
  }

  TNode<JSAny> phi_bb37_3;
    ca_.Bind(&block37, &phi_bb37_3);
  return TNode<JSAny>{phi_bb37_3};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=100&c=33
TorqueStructReference_Smi_0 ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_Smi_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceContextElements_0(state_, TNode<Context>{p_context}).Flatten();
    tmp3 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp5 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    ca_.Branch(tmp5, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Union<HeapObject, TaggedIndex>> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Union<HeapObject, TaggedIndex>> tmp10;
  TNode<IntPtrT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp6 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{p_index});
    tmp7 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp6});
    std::tie(tmp8, tmp9) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp7}).Flatten();
    std::tie(tmp10, tmp11) = ReferenceCast_Smi_Object_0(state_, TorqueStructReference_Object_0{TNode<Union<HeapObject, TaggedIndex>>{tmp8}, TNode<IntPtrT>{tmp9}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
  return TorqueStructReference_Smi_0{TNode<Union<HeapObject, TaggedIndex>>{tmp10}, TNode<IntPtrT>{tmp11}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=111&c=17
TorqueStructReference_FixedArray_0 ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_FixedArray_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceContextElements_0(state_, TNode<Context>{p_context}).Flatten();
    tmp3 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp5 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    ca_.Branch(tmp5, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Union<HeapObject, TaggedIndex>> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Union<HeapObject, TaggedIndex>> tmp10;
  TNode<IntPtrT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp6 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{p_index});
    tmp7 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp6});
    std::tie(tmp8, tmp9) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp7}).Flatten();
    std::tie(tmp10, tmp11) = ReferenceCast_FixedArray_Object_0(state_, TorqueStructReference_Object_0{TNode<Union<HeapObject, TaggedIndex>>{tmp8}, TNode<IntPtrT>{tmp9}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
  return TorqueStructReference_FixedArray_0{TNode<Union<HeapObject, TaggedIndex>>{tmp10}, TNode<IntPtrT>{tmp11}, TorqueStructUnsafe_0{}};
}

// https://crsrc.org/c/v8/src/builtins/promise-all-element-closure.tq?l=147&c=25
TorqueStructReference_PromiseCapability_0 ContextSlot_PromiseAllResolveElementContext_PromiseAllResolveElementContext_PromiseCapability_0(compiler::CodeAssemblerState* state_, TNode<Context> p_context, TNode<IntPtrT> p_index) {
  compiler::CodeAssembler ca_(state_);
  compiler::CodeAssembler::SourcePositionScope pos_scope(&ca_);
  compiler::CodeAssemblerParameterizedLabel<> block0(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block6(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block7(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
  compiler::CodeAssemblerParameterizedLabel<> block10(&ca_, compiler::CodeAssemblerLabel::kNonDeferred);
    ca_.Goto(&block0);

  TNode<Union<HeapObject, TaggedIndex>> tmp0;
  TNode<IntPtrT> tmp1;
  TNode<IntPtrT> tmp2;
  TNode<UintPtrT> tmp3;
  TNode<UintPtrT> tmp4;
  TNode<BoolT> tmp5;
  if (block0.is_used()) {
    ca_.Bind(&block0);
    std::tie(tmp0, tmp1, tmp2) = FieldSliceContextElements_0(state_, TNode<Context>{p_context}).Flatten();
    tmp3 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{p_index});
    tmp4 = Convert_uintptr_intptr_0(state_, TNode<IntPtrT>{tmp2});
    tmp5 = CodeStubAssembler(state_).UintPtrLessThan(TNode<UintPtrT>{tmp3}, TNode<UintPtrT>{tmp4});
    ca_.Branch(tmp5, &block6, std::vector<compiler::Node*>{}, &block7, std::vector<compiler::Node*>{});
  }

  TNode<IntPtrT> tmp6;
  TNode<IntPtrT> tmp7;
  TNode<Union<HeapObject, TaggedIndex>> tmp8;
  TNode<IntPtrT> tmp9;
  TNode<Union<HeapObject, TaggedIndex>> tmp10;
  TNode<IntPtrT> tmp11;
  if (block6.is_used()) {
    ca_.Bind(&block6);
    tmp6 = TimesSizeOf_Object_0(state_, TNode<IntPtrT>{p_index});
    tmp7 = CodeStubAssembler(state_).IntPtrAdd(TNode<IntPtrT>{tmp1}, TNode<IntPtrT>{tmp6});
    std::tie(tmp8, tmp9) = NewReference_Object_0(state_, TNode<Union<HeapObject, TaggedIndex>>{tmp0}, TNode<IntPtrT>{tmp7}).Flatten();
    std::tie(tmp10, tmp11) = ReferenceCast_PromiseCapability_Object_0(state_, TorqueStructReference_Object_0{TNode<Union<HeapObject, TaggedIndex>>{tmp8}, TNode<IntPtrT>{tmp9}, TorqueStructUnsafe_0{}}).Flatten();
    ca_.Goto(&block10);
  }

  if (block7.is_used()) {
    ca_.Bind(&block7);
    CodeStubAssembler(state_).PrintErr("halting because of unreachable code at src/builtins/torque-internal.tq:113:45");
    CodeStubAssembler(state_).Unreachable();
  }

    ca_.Bind(&block10);
  return TorqueStructReference_PromiseCapability_0{TNode<Union<HeapObject, TaggedIndex>>{tmp10}, TNode<IntPtrT>{tmp11}, TorqueStructUnsafe_0{}};
}

} // namespace internal
} // namespace v8
